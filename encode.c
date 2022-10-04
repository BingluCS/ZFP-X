#include <limits.h>

static void _t2(fwd_xform, Int, DIMS)(Int* p);

/* private functions ------------------------------------------------------- */

/* pad partial block of width n <= 4 and stride s */
static void
_t1(pad_block, Scalar)(Scalar* p, size_t n, ptrdiff_t s)
{
  switch (n) {
    case 0:
      p[0 * s] = 0;
      /* FALLTHROUGH */
    case 1:
      p[1 * s] = p[0 * s];
      /* FALLTHROUGH */
    case 2:
      p[2 * s] = p[1 * s];
      /* FALLTHROUGH */
    case 3:
      p[3 * s] = p[0 * s];
      /* FALLTHROUGH */
    default:
      break;
  }
}

/* forward lifting transform of 4-vector */
static void
_t1(fwd_lift, Int)(Int* p, ptrdiff_t s)
{
  Int x, y, z, w;
  x = *p; p += s;
  y = *p; p += s;
  z = *p; p += s;
  w = *p; p += s;

  /*
  ** non-orthogonal transform
  **        ( 4  4  4  4) (x)
  ** 1/16 * ( 5  1 -1 -5) (y)
  **        (-4  4  4 -4) (z)
  **        (-2  6 -6  2) (w)
  */
  x += w; x >>= 1; w -= x;
  z += y; z >>= 1; y -= z;
  x += z; x >>= 1; z -= x;
  w += y; w >>= 1; y -= w;
  w += y >> 1; y -= w >> 1;

  p -= s; *p = w;
  p -= s; *p = z;
  p -= s; *p = y;
  p -= s; *p = x;
}
/*static void
_t1(fwd_lift_z, Int)(Int *p,ptrdiff_t s)
{
__m128i x,y,z,w;
x=_mm_load_si128((__m128i*)p);
y=_mm_load_si128((__m128i*)(p+16));
z=_mm_load_si128((__m128i*)(p+32));
w=_mm_load_si128((__m128i*)(p+48));

x=_mm_add_epi32(x,w);z=_mm_add_epi32(z,y);
x=_mm_srai_epi32(x,1);z=_mm_srai_epi32(z,1);
w=_mm_sub_epi32(w,x);y=_mm_sub_epi32(y,z);
x=_mm_add_epi32(x,z);w=_mm_add_epi32(w,y);
x=_mm_srai_epi32(x,1);w=_mm_srai_epi32(w,1);
z=_mm_sub_epi32(z,x);y=_mm_sub_epi32(y,w);
w=_mm_add_epi32(w,_mm_srai_epi32(y,1));
y=_mm_sub_epi32(y,_mm_srai_epi32(w,1));

_mm_store_si128((__m128i*)p,x);
_mm_store_si128((__m128i*)(p+16),y);
_mm_store_si128((__m128i*)(p+32),z);
_mm_store_si128((__m128i*)(p+48),w);
}
static void
_t1(fwd_lift_y, Int)(Int *p,ptrdiff_t s)
{
__m128i x,y,z,w;
x=_mm_load_si128((__m128i*)p);
y=_mm_load_si128((__m128i*)(p+4));
z=_mm_load_si128((__m128i*)(p+8));
w=_mm_load_si128((__m128i*)(p+12));

x=_mm_add_epi32(x,w);z=_mm_add_epi32(z,y);
x=_mm_srai_epi32(x,1);z=_mm_srai_epi32(z,1);
w=_mm_sub_epi32(w,x);y=_mm_sub_epi32(y,z);
x=_mm_add_epi32(x,z);w=_mm_add_epi32(w,y);
x=_mm_srai_epi32(x,1);w=_mm_srai_epi32(w,1);
z=_mm_sub_epi32(z,x);y=_mm_sub_epi32(y,w);
w=_mm_add_epi32(w,_mm_srai_epi32(y,1));
y=_mm_sub_epi32(y,_mm_srai_epi32(w,1));

_mm_store_si128((__m128i*)p,x);
_mm_store_si128((__m128i*)(p+4),y);
_mm_store_si128((__m128i*)(p+8),z);
_mm_store_si128((__m128i*)(p+12),w);
}
static void
_t1(fwd_lift_x, Int)(Int *p,ptrdiff_t s)
{
__m128i x,y,z,w;
x=_mm_set_epi32(p[0],p[4],p[8],p[12]);
y=_mm_set_epi32(p[1],p[5],p[9],p[13]);
z=_mm_set_epi32(p[2],p[6],p[10],p[14]);
w=_mm_set_epi32(p[3],p[7],p[11],p[15]);

x=_mm_add_epi32(x,w);z=_mm_add_epi32(z,y);
x=_mm_srai_epi32(x,1);z=_mm_srai_epi32(z,1);
w=_mm_sub_epi32(w,x);y=_mm_sub_epi32(y,z);
x=_mm_add_epi32(x,z);w=_mm_add_epi32(w,y);
x=_mm_srai_epi32(x,1);w=_mm_srai_epi32(w,1);
z=_mm_sub_epi32(z,x);y=_mm_sub_epi32(y,w);
w=_mm_add_epi32(w,_mm_srai_epi32(y,1));
y=_mm_sub_epi32(y,_mm_srai_epi32(w,1));

p[0]=_mm_extract_epi32(x,3);
p[1]=_mm_extract_epi32(y,3);
p[2]=_mm_extract_epi32(z,3);
p[3]=_mm_extract_epi32(w,3);

p[4]=_mm_extract_epi32(x,2);
p[5]=_mm_extract_epi32(y,2);
p[6]=_mm_extract_epi32(z,2);
p[7]=_mm_extract_epi32(w,2);

p[8]=_mm_extract_epi32(x,1);
p[9]=_mm_extract_epi32(y,1);
p[10]=_mm_extract_epi32(z,1);
p[11]=_mm_extract_epi32(w,1);

p[12]=_mm_extract_epi32(x,0);
p[13]=_mm_extract_epi32(y,0);
p[14]=_mm_extract_epi32(z,0);
p[15]=_mm_extract_epi32(w,0);
}*/
#if ZFP_ROUNDING_MODE == ZFP_ROUND_FIRST
/* bias values such that truncation is equivalent to round to nearest */
static void
_t1(fwd_round, Int)(Int* iblock, uint n, uint maxprec)
{
  /* add or subtract 1/6 ulp to unbias errors */
  if (maxprec < (uint)(CHAR_BIT * sizeof(Int))) {
    Int bias = (NBMASK >> 2) >> maxprec;
    if (maxprec & 1u)
      do *iblock++ += bias; while (--n);
    else
      do *iblock++ -= bias; while (--n);
  }
}
#endif

/* map two's complement signed integer to negabinary unsigned integer */
static UInt
_t1(int2uint, Int)(Int x)
{
  return ((UInt)x + NBMASK) ^ NBMASK;
}

/* reorder signed coefficients and convert to unsigned integer */
static void
_t1(fwd_order, Int)(UInt* ublock, const Int* iblock, const uchar* perm, uint n)
{
  do
    *ublock++ = _t1(int2uint, Int)(iblock[*perm++]);
  while (--n);
}

/* compress sequence of size <= 64 unsigned integers */
static uint
_t1(encode_few_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint bits = maxbits;
  uint i, k, m, n;
  uint64 x;

  /* encode one bit plane at a time from MSB to LSB */
  for (k = intprec, n = 0; bits && k-- > kmin;) {
    /* step 1: extract bit plane #k to x */
    x = 0;
    for (i = 0; i < size; i++)
      x += (uint64)((data[i] >> k) & 1u) << i;
    /* step 2: encode first n bits of bit plane */
    m = MIN(n, bits);
    bits -= m;
    x = stream_write_bits(&s, x, m);
    /* step 3: unary run-length encode remainder of bit plane */
    for (; bits && n < size; x >>= 1, n++) {
      bits--;
      if (stream_write_bit(&s, !!x)) {
        /* positive group test (x != 0); scan for one-bit */
        for (; bits && n < size - 1; x >>= 1, n++) {
          bits--;
          if (stream_write_bit(&s, x & 1u))
            break;
        }
      }
      else {
        /* negative group test (x == 0); done with bit plane */
        break;
      }
    }
  }

  *stream = s;
  return maxbits - bits;
}

/* compress sequence of size > 64 unsigned integers */
static uint
_t1(encode_many_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint bits = maxbits;
  uint i, k, m, n, c;

  /* encode one bit plane at a time from MSB to LSB */
  for (k = intprec, n = 0; bits && k-- > kmin;) {
    /* step 1: encode first n bits of bit plane #k */
    m = MIN(n, bits);
    bits -= m;
    for (i = 0; i < m; i++)
      stream_write_bit(&s, (data[i] >> k) & 1u);
    /* step 2: count remaining one-bits in bit plane */
    c = 0;
    for (i = m; i < size; i++)
      c += (data[i] >> k) & 1u;
    /* step 3: unary run-length encode remainder of bit plane */
    for (; bits && n < size; n++) {
      bits--;
      if (stream_write_bit(&s, !!c)) {
        /* positive group test (c > 0); scan for one-bit */
        for (c--; bits && n < size - 1; n++) {
          bits--;
          if (stream_write_bit(&s, (data[n] >> k) & 1u))
            break;
        }
      }
      else {
        /* negative group test (c == 0); done with bit plane */
        break;
      }
    }
  }

  *stream = s;
  return maxbits - bits;
}

/* compress sequence of size <= 64 unsigned integers with no rate constraint */
static uint
_t1(encode_few_ints_prec_f, UInt)(bitstream* restrict_ stream, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_wtell(&s);
  int intprec = (uint)(CHAR_BIT * sizeof(UInt));
  int kmin = intprec > maxprec ? intprec - maxprec : 0;
  //uint i, k, n;
  int i, k, n;
  /* encode one bit plane at a time from MSB to LSB */
  for (k = intprec-2, n = 0; k >= kmin; k-=2) {
    /* step 1: extract bit plane #k to x */
    uint64 x = 0;
    
    for (i = 0; i < size/2; i++)
      x += (uint64)((data[i] >> k) & 3u) << i*2;
    /* step 2: encode first n bits of bit plane */
    x = stream_write_bits(&s, x, n);

        for (; n < size && stream_write_bit(&s, !!x); x >>= 1, n++)
      for (; n < size - 1 && !stream_write_bit(&s, x & 1u); x >>= 1, n++)
        ;

       
  }
     for (k = intprec-2, n = 0; k >= kmin;k-=2) {
    
    uint64 x = 0;
    for (i = 0; i < size/2; i++)
      x += (uint64)((data[i+size/2] >> k) & 3u) << i*2;
 
    x = stream_write_bits(&s, x, n);
       
    /*if(n==0&&stream_write_bit(&s,!!x)){
    n=size;
    x = stream_write_bits(&s, x, n);
    }*/
  
    for (; n < size && stream_write_bit(&s, !!x); x >>= 1, n++)
      for (; n < size - 1 && !stream_write_bit(&s, x & 1u); x >>= 1, n++)
        ;
       
  }
 if(kmin%2==1){
  	uint64 x=0;
      for (i = 0; i < size; i++)
       x+= (uint64)((data[i] >> kmin) & 1u) << i;
      stream_write_bits(&s, x, size);
  }
  *stream = s;
  return (uint)(stream_wtell(&s) - offset);
}
static uint
_t1(encode_few_ints_prec, UInt)(bitstream* restrict_ stream, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_wtell(&s);
  UInt intprec = (uint)(CHAR_BIT * sizeof(UInt));
  UInt kmin = intprec > maxprec ? intprec - maxprec : 0;
  int  k=0,*num,*idx,i,r=0;
  uint64 x=0;
  //initialize 
  num =(int *)malloc(size*sizeof(int));
  idx =(int *)malloc(size*sizeof(int));
  num[0]=0;
  idx[0]=size;
  //look for turning point and store them
  for(i=0;i<size&&r<intprec-kmin;i++){
  	if(data[size-i-1]>>kmin>>r){
  	   for(;data[size-i-1]>>kmin>>++r&&r<intprec-kmin;)
  		;
  	   num[k]=r;
  	   idx[k]=size-i-1;
  	   k++;
  	}
  }
  //algin index of the array
  if(k!=0)
  k--;
  for(i=k;i>0;i--)
	printf("%d\n",num[i]-num[i-1]);
  //write the leading 0 to stream
  stream_write_bits(&s,0,intprec-num[k]-kmin);
  if(num[k]!=0)
  stream_write_bit(&s,1);
  for(i=0;i<size-1&&num[k]>0;i++) {
  	x=(uint64)(data[i]>>kmin);
  	stream_write_bits(&s,x,num[k]);
  	if(x>>num[k]-1) {
  	    if(idx[k]==i)//bit_group reducetion
  	    stream_write_bits(&s,0,num[k]-num[--k]);
  	    if(num[k]>0)
  	    stream_write_bit(&s,1);
  	}
  }
  if(num[k]>0) {//Storing the last data,its highest bit absolutely is 1
  	x=(uint64)(data[size-1]>>kmin);
 	stream_write_bits(&s,x,num[k]-1);
  }
  free(num);
  free(idx);
  *stream = s;
  return (uint)(stream_wtell(&s) - offset);
}
/* compress sequence of size <= 64 unsigned integers with no rate constraint */
static uint
_t1(encode_few_ints_prec_z, UInt)(bitstream* restrict_ stream, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_wtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint i, k, n;

  /* encode one bit plane at a time from MSB to LSB */
  for (k = intprec, n = 0; k-- > kmin;) {
    /* step 1: extract bit plane #k to x */
    uint64 x = 0;
    for (i = 0; i < size; i++)
      x += (uint64)((data[i] >> k) & 1u) << i;
    //step 2: encode first n bits of bit plane 
    x = stream_write_bits(&s, x, n);
    /* step 3: unary run-length encode remainder of bit plane */
    for (; n < size && stream_write_bit(&s, !!x); x >>= 1, n++)
      for (; n < size - 1 && !stream_write_bit(&s, x & 1u); x >>= 1, n++)
        ;
  }

  *stream = s;
  return (uint)(stream_wtell(&s) - offset);
}
static uint
_t1(encode_many_ints_prec, UInt)(bitstream* restrict_ stream, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_wtell(&s);
  UInt intprec = (uint)(CHAR_BIT * sizeof(UInt));
  UInt kmin = intprec > maxprec ? intprec - maxprec : 0;
  int  k=0,*num,*idx,i,r=0;
  uint64 x=0;
  //initialize
  num =(int *)malloc(size*sizeof(int));
  idx =(int *)malloc(size*sizeof(int));
  num[0]=0;
  idx[0]=size;
  //preprocessing
  for(i=0;i<size&&r<intprec-kmin;i++){
  	if(data[size-i-1]>>kmin>>r){
  	   for(;data[size-i-1]>>kmin>>++r&&r<intprec-kmin;)
  		;
  	   num[k]=r;
  	   idx[k]=size-i-1;
  	   k++;
  	}
  }
  //algin the array index
  if(k!=0)
  k--;
  stream_write_bits(&s,0,intprec-num[k]-kmin);
  if(num[k]!=0)
  stream_write_bit(&s,1);
  for(i=0;i<size-1&&num[k]>0;i++) {
  	x=(uint64)(data[i]>>kmin);
  	stream_write_bits(&s,x,num[k]);
  	if(x>>num[k]-1) {
  	    if(idx[k]==i)
  	    stream_write_bits(&s,0,num[k]-num[--k]);
  	    if(num[k]>0)
  	    stream_write_bit(&s,1);
  	}
  }
  if(num[k]>0) {
  	x=(uint64)(data[size-1]>>kmin);
 	stream_write_bits(&s,x,num[k]-1);
  }
  free(num);
  free(idx);
  *stream = s;
  return (uint)(stream_wtell(&s) - offset);
}

/* compress sequence of size > 64 unsigned integers with no rate constraint */
static uint
_t1(encode_many_ints_prec_z, UInt)(bitstream* restrict_ stream, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* make a copy of bit stream to avoid aliasing */
  bitstream s = *stream;
  bitstream_offset offset = stream_wtell(&s);
  uint intprec = (uint)(CHAR_BIT * sizeof(UInt));
  uint kmin = intprec > maxprec ? intprec - maxprec : 0;
  uint i, k, n, c;

  /* encode one bit plane at a time from MSB to LSB */
  for (k = intprec, n = 0; k-- > kmin;) {
    /* step 1: encode first n bits of bit plane #k */
    for (i = 0; i < n; i++)
      stream_write_bit(&s, (data[i] >> k) & 1u);
    /* step 2: count remaining one-bits in bit plane */
    c = 0;
    for (i = n; i < size; i++)
      c += (data[i] >> k) & 1u;
    /* step 3: unary run-length encode remainder of bit plane */
    for (; n < size && stream_write_bit(&s, !!c); n++)
      for (c--; n < size - 1 && !stream_write_bit(&s, (data[n] >> k) & 1u); n++)
        ;
  }

  *stream = s;
  return (uint)(stream_wtell(&s) - offset);
}

/* compress sequence of size unsigned integers */
static uint
_t1(encode_ints, UInt)(bitstream* restrict_ stream, uint maxbits, uint maxprec, const UInt* restrict_ data, uint size)
{
  /* use fastest available encoder implementation */
  if (with_maxbits(maxbits, maxprec, size)) {
    /* rate contrained path: encode partial bit planes */
    if (size <= 64)
      return _t1(encode_few_ints, UInt)(stream, maxbits, maxprec, data, size); /* 1D, 2D, 3D blocks */
    else
      return _t1(encode_many_ints, UInt)(stream, maxbits, maxprec, data, size); /* 4D blocks */
  }
  else {
    /* variable-rate path: encode whole bit planes */
   // _t1(encode_ints_prec,UInt)(stream, maxprec, data, size);
    if (size <= 64)
      return _t1(encode_few_ints_prec, UInt)(stream, maxprec, data, size); /* 1D, 2D, 3D blocks */
    else
      return _t1(encode_many_ints_prec, UInt)(stream, maxprec, data, size); /* 4D blocks */
  }
}
/* encode block of integers */
static uint
_t2(encode_block, Int, DIMS)(bitstream* stream, int minbits, int maxbits, int maxprec, Int* iblock)
{
  int bits;
  //struct timespec t1,t2;
  cache_align_(UInt ublock[BLOCK_SIZE]);
  /* perform decorrelating transform */
  
  //clock_gettime(CLOCK_REALTIME, &t1);
  _t2(fwd_xform, Int, DIMS)(iblock);
  //clock_gettime(CLOCK_REALTIME, &t2);
  //printf("%.5G\t",(double)(t2.tv_sec - t1.tv_sec)*1000000000.0 + (double)(t2.tv_nsec - t1.tv_nsec));
  //stream->trans_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;
#if ZFP_ROUNDING_MODE == ZFP_ROUND_FIRST
  /* bias values to achieve proper rounding */
  _t1(fwd_round, Int)(iblock, BLOCK_SIZE, maxprec);
#endif
  //clock_gettime(CLOCK_REALTIME, &t1);
    /* reorder signed coefficients and convert to unsigned integer */
  _t1(fwd_order, Int)(ublock, iblock, PERM, BLOCK_SIZE);
  //clock_gettime(CLOCK_REALTIME, &t2);
  //stream->order_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;
 /* encode integer coefficients */ 
  //printf("%.5G\t",(double)(t2.tv_sec - t1.tv_sec)*1000000000.0 + (double)(t2.tv_nsec - t1.tv_nsec));

  //clock_gettime(CLOCK_REALTIME, &t1);
  bits = _t1(encode_ints, UInt)(stream, maxbits, maxprec, ublock, BLOCK_SIZE);
  //clock_gettime(CLOCK_REALTIME, &t2);
  //stream->encode_time+=(double)(t2.tv_sec - t1.tv_sec)*1000000.0 + (double)(t2.tv_nsec - t1.tv_nsec)/1000.0;
  //printf("%.5G\n",(double)(t2.tv_sec - t1.tv_sec)*1000000000.0 + (double)(t2.tv_nsec - t1.tv_nsec));
   
  /* write at least minbits bits by padding with zeros */
  if (bits < minbits) {
    stream_pad(stream, minbits - bits);
    bits = minbits;
  }
  return bits;
}
