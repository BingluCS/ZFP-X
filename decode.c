#include <limits.h>

static void _t2(inv_xform, Int, DIMS)(Int* p);

/* private functions ------------------------------------------------------- */

/* inverse lifting transform of 4-vector */
static void
_t1(inv_lift, Int)(Int* p, ptrdiff_t s)
{
  Int x, y, z, w;
  x = *p; p += s;
  y = *p; p += s;
  z = *p; p += s;
  w = *p; p += s;

  /*
  ** non-orthogonal transform
  **       ( 4  6 -4 -1) (x)
  ** 1/4 * ( 4  2  4  5) (y)
  **       ( 4 -2  4 -5) (z)
  **       ( 4 -6 -4  1) (w)
  */
  y += w >> 1; w -= y >> 1;
  y += w; w <<= 1; w -= y;
  z += x; x <<= 1; x -= z;
  y += z; z <<= 1; z -= y;
  w += x; x <<= 1; x -= w;

  p -= s; *p = w;
  p -= s; *p = z;
  p -= s; *p = y;
  p -= s; *p = x;
}

#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST
/* bias values such that truncation is equivalent to round to nearest */
static void
_t1(inv_round, UInt)(UInt* ublock, uint n, uint m, uint prec)
{
  /* add 1/6 ulp to unbias errors */
  if (prec < (uint)(CHAR_BIT * sizeof(UInt) - 1)) {
    /* the first m values (0 <= m <= n) have one more bit of precision */
    n -= m;
    while (m--) *ublock++ += ((NBMASK >> 2) >> prec);
    while (n--) *ublock++ += ((NBMASK >> 1) >> prec);
  }
}
#endif

/* map two's complement signed integer to negabinary unsigned integer */
static Int
_t1(uint2int, UInt)(UInt x)
{
  return (Int)((x ^ NBMASK) - NBMASK);
}

/* reorder unsigned coefficients and convert to signed integer */
static void
_t1(inv_order, Int)(const UInt* ublock, Int* iblock, const uchar* perm, uint n)
{
  do
    iblock[*perm++] = _t1(uint2int, UInt)(*ublock++);
  while (--n);
}

/* decompress sequence of size <= 64 unsigned integers */
static uint
_t1(decode_few_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint bits = maxbits;
  uint i, k, m, n;
  uint64 x;

  /* initialize data array to all zeros */
  for (i = 0; i < size; i++)
    data[i] = 0;

  /* decode one bit plane at a time from MSB to LSB */
  for (k = intprec, m = n = 0; bits && (m = 0, k-- > kmin);) {
    /* step 1: decode first n bits of bit plane #k */
    m = MIN(n, bits);
    bits -= m;
    x = stream_read_bits(&s, m);
    /* step 2: unary run-length decode remainder of bit plane */
    for (; bits && n < size; n++, m = n) {
      bits--;
      if (stream_read_bit(&s)) {
        /* positive group test; scan for next one-bit */
        for (; bits && n < size - 1; n++) {
          bits--;
          if (stream_read_bit(&s))
            break;
        }
        /* set bit and continue decoding bit plane */
        x += (uint64)1 << n;
      }
      else {
        /* negative group test; done with bit plane */
        m = size;
        break;
      }
    }
    /* step 3: deposit bit plane from x */
    for (i = 0; x; i++, x >>= 1)
      data[i] += (UInt)(x & 1u) << k;
  }

#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST
  /* bias values to achieve proper rounding */
  _t1(inv_round, UInt)(data, size, m, intprec - k);
#endif

  *stream = s;
  return maxbits - bits;
}

/* decompress sequence of size > 64 unsigned integers */
static uint
_t1(decode_many_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint bits = maxbits;
  uint i, k, m, n;

  /* initialize data array to all zeros */
  for (i = 0; i < size; i++)
    data[i] = 0;

  /* decode one bit plane at a time from MSB to LSB */
  for (k = intprec, m = n = 0; bits && (m = 0, k-- > kmin);) {
    /* step 1: decode first n bits of bit plane #k */
    m = MIN(n, bits);
    bits -= m;
    for (i = 0; i < m; i++)
      if (stream_read_bit(&s))
        data[i] += (UInt)1 << k;
    /* step 2: unary run-length decode remainder of bit plane */
    for (; bits && n < size; n++, m = n) {
      bits--;
      if (stream_read_bit(&s)) {
        /* positive group test; scan for next one-bit */
        for (; bits && n < size - 1; n++) {
          bits--;
          if (stream_read_bit(&s))
            break;
        }
        /* set bit and continue decoding bit plane */
        data[n] += (UInt)1 << k;
      }
      else {
        /* negative group test; done with bit plane */
        m = size;
        break;
      }
    }
  }

#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST
  /* bias values to achieve proper rounding */
  _t1(inv_round, UInt)(data, size, m, intprec - k);
#endif

  *stream = s;
  return maxbits - bits;
}

/* decompress sequence of size <= 64 unsigned integers with no rate constraint */
static uint
_t1(decode_few_ints_prec_f, UInt)(bitstream* restrict_ stream, uint maxprec, UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_rtell(&s);
  int intprec = (uint)(CHAR_BIT * sizeof(UInt));
  int kmin = intprec > maxprec ? intprec - maxprec : 0;
  int i, k, n;
  uint64 num;
  /* initialize data array to all zeros */
  for (i = 0; i < size; i++)
    data[i] = 0;

  /* decode one bit plane at a time from MSB to LSB */
  for (k = intprec-2, n = 0; k >= kmin;k-=2) {
    /* step 1: decode first n bits of bit plane #k */
    uint64 x = stream_read_bits(&s, n);
  for (; n < size && stream_read_bit(&s); x += (uint64)1 << n, n++)
      for (; n < size - 1 && !stream_read_bit(&s); n++)
      ;
    /* step 2: unary run-length decode remainder of bit plane */
    /*for (; n < size && stream_read_bit(&s); x += num << n, n+=2)
      for (; n < size - 1 &&(num= stream_read_bits(&s,2)); n+=2)
        ;*/
    /* step 3: deposit bit plane from x */
    for (i = 0; x; i++, x >>= 2)
      data[i] += (UInt)(x & 3u) << k;
      
  }
 
   for (k = intprec-2, n = 0; k >= kmin; k-=2) {
    /* step 1: decode first n bits of bit plane #k */
    uint64 x = stream_read_bits(&s, n);
        /*if(n==0&&stream_read_bit(&s))
    {
    	n=size;
    	x=stream_read_bits(&s, n);
    }*/
    
      
   for (; n < size && stream_read_bit(&s); x += (uint64)1 << n, n++)
      for (; n < size - 1 && !stream_read_bit(&s); n++)
        ;
        
      for (i = 0; x; i++, x >>= 2)
      data[i+size/2] += (UInt)(x & 3u) << k;
     
  }
   if(kmin%2==1){
      uint64 x=stream_read_bits(&s, size);
    for (i = 0; x; i++, x >>= 1)
      data[i] += (UInt)(x & 1u) << kmin;
      
  }
#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST
  /* bias values to achieve proper rounding */
  _t1(inv_round, UInt)(data, size, 0, intprec - k);
#endif

  *stream = s;
  return (uint)(stream_rtell(&s) - offset);
}
static uint
_t1(decode_few_ints_prec, UInt)(bitstream* restrict_ stream, uint maxprec, UInt* restrict_ data, uint size)
{

  bitstream s = *stream;
  bitstream_offset offset = stream_rtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  int  k,n,i;
  uint64 x,pre=0;
  /* initialize data array to all zeros */
  for (i = 0; i < size; i++)
    data[i] = 0;
  //decode the leading zero and calculate the number of bit the first to be read
  for(n=0;n<intprec-kmin&&!stream_read_bit(&s);n++)
	  ;
  n=intprec-kmin-n;
  for(i=0;i<size-1&&n>0;i++){
  	x=0;
	x=stream_read_bits(&s,n);
	pre=x>>(n-1);
        //it indicates the data may be a turning point if the highest decoded data is 1 
	if(pre)
	    for(;n>0&&!stream_read_bit(&s);n--)
	    ;
	data[i]=(UInt)(x)<<kmin;
  }
  //decode the last data
  if(n>0){
  x=stream_read_bits(&s,n-1);
  data[i]=((UInt)(x)<<kmin)+((UInt)1u<<n-1<<kmin);
  }
#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST

  _t1(inv_round, UInt)(data, size, 0, intprec - k);
#endif

  *stream = s;
  return (uint)(stream_rtell(&s) - offset);
}
static uint
_t1(decode_few_ints_prec_z, UInt)(bitstream* restrict_ stream, uint maxprec, UInt* restrict_ data, uint size)
{

  bitstream s = *stream;
  bitstream_offset offset = stream_rtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint i, k, n;


  for (i = 0; i < size; i++)
    data[i] = 0;

  
  for (k = intprec, n = 0; k-- > kmin;) {
  
    uint64 x = stream_read_bits(&s, n);
  
    for (; n < size && stream_read_bit(&s); x += (uint64)1 << n, n++)
      for (; n < size - 1 && !stream_read_bit(&s); n++)
        ;

    for (i = 0; x; i++, x >>= 1)
      data[i] += (UInt)(x & 1u) << k;
        
  }
#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST

  _t1(inv_round, UInt)(data, size, 0, intprec - k);
#endif

  *stream = s;
  return (uint)(stream_rtell(&s) - offset);
}

static uint
_t1(decode_many_ints_prec, UInt)(bitstream* restrict_ stream, uint maxprec, UInt* restrict_ data, uint size)
{

  bitstream s = *stream;
  bitstream_offset offset = stream_rtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  int  k,n,i;
  uint64 x,pre=0;
  for (i = 0; i < size; i++)
    data[i] = 0;
  for(n=0;n<intprec-kmin&&!stream_read_bit(&s);n++)
	  ;
  n=intprec-kmin-n;
  for(i=0;i<size-1&&n>0;i++){
  	x=0;
	x=stream_read_bits(&s,n);
	pre=x>>(n-1);
	if(pre)
	    for(;n>0&&!stream_read_bit(&s);n--)
	    ;
	data[i]=(UInt)(x)<<kmin;
  }
  if(n>0){
  x=stream_read_bits(&s,n-1);
  data[i]=((UInt)(x)<<kmin)+((UInt)1u<<n-1<<kmin);
  }
#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST

  _t1(inv_round, UInt)(data, size, 0, intprec - k);
#endif

  *stream = s;
  return (uint)(stream_rtell(&s) - offset);
}
/* decompress sequence of size > 64 unsigned integers with no rate constraint */
static uint
_t1(decode_many_ints_prec_z, UInt)(bitstream* restrict_ stream, uint maxprec, UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_rtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint i, k, n;

  /* initialize data array to all zeros */
  for (i = 0; i < size; i++)
    data[i] = 0;

  /* decode one bit plane at a time from MSB to LSB */
  for (k = intprec, n = 0; k-- > kmin;) {
    /* step 1: decode first n bits of bit plane #k */
    for (i = 0; i < n; i++)
      if (stream_read_bit(&s))
        data[i] += (UInt)1 << k;
    /* step 2: unary run-length decode remainder of bit plane */
    for (; n < size && stream_read_bit(&s); data[n] += (UInt)1 << k, n++)
      for (; n < size - 1 && !stream_read_bit(&s); n++)
        ;
  }

#if ZFP_ROUNDING_MODE == ZFP_ROUND_LAST
  /* bias values to achieve proper rounding */
  _t1(inv_round, UInt)(data, size, 0, intprec - k);
#endif

  *stream = s;
  return (uint)(stream_rtell(&s) - offset);
}

/* decompress sequence of size unsigned integers */
static uint
_t1(decode_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, UInt* restrict_ data, uint size)
{
  /* use fastest available decoder implementation */
  if (with_maxbits(maxbits, maxprec, size)) {
    /* rate constrained path: decode partial bit planes */
    if (size <= 64)
      return _t1(decode_few_ints, UInt)(stream, maxbits, maxprec, data, size); /* 1D, 2D, 3D blocks */
    else
      return _t1(decode_many_ints, UInt)(stream, maxbits, maxprec, data, size); /* 4D blocks */
  }
  else {
    /* variable-rate path: decode whole bit planes */
    //_t1(decode_ints_prec, UInt)(stream, maxprec, data, size);
    if (size <= 64)
      return _t1(decode_few_ints_prec, UInt)(stream, maxprec, data, size); /* 1D, 2D, 3D blocks */
    else
      return _t1(decode_many_ints_prec, UInt)(stream, maxprec, data, size); /* 4D blocks */
  }
}

/* decode block of integers */
static uint
_t2(decode_block, Int, DIMS)(bitstream* stream, int minbits, int maxbits, int maxprec, Int* iblock)
{
  int bits;
  cache_align_(UInt ublock[BLOCK_SIZE]);
  /* decode integer coefficients */
 // struct timespec t1,t2; 
 // clock_gettime(CLOCK_REALTIME, &t1); 
  bits = _t1(decode_ints, UInt)(stream, maxbits, maxprec, ublock, BLOCK_SIZE);
  //clock_gettime(CLOCK_REALTIME, &t2);
  //printf("%.5G\n",(double)(t2.tv_sec - t1.tv_sec)*1000000000.0 + (double)(t2.tv_nsec - t1.tv_nsec));
  //stream->encode_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;

  /* read at least minbits bits */
  if (bits < minbits) {
    stream_skip(stream, minbits - bits);
    bits = minbits;
  }
  /* reorder unsigned coefficients and convert to signed integer */
  //clock_gettime(CLOCK_REALTIME, &t1); 
  _t1(inv_order, Int)(ublock, iblock, PERM, BLOCK_SIZE);
  //clock_gettime(CLOCK_REALTIME, &t2); 
  //stream->order_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;
  ///* perform decorrelating transform */
  
  //clock_gettime(CLOCK_REALTIME, &t1); 
  _t2(inv_xform, Int, DIMS)(iblock);
  //clock_gettime(CLOCK_REALTIME, &t2); 
  //stream->trans_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;
  //printf("%.5G\n",(double)(t2.tv_sec - t1.tv_sec)*1000000000.0 + (double)(t2.tv_nsec - t1.tv_nsec));
  return bits;
}