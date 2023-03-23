
rm -rf ../experiment_data/ZFP/CESM/* ../experiment_data/ZFP/Miranda/* ../experiment_data/ZFP/Hu/* ../experiment_data/ZFP/NYX/* 
rm -rf ../experiment_data/ZFP/SCALE/*
while read line
do
  A=($line)
  echo ${A[0]}
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[1]} >> ../experiment_data/ZFP/CESM/1E-1
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[2]} >> ../experiment_data/ZFP/CESM/1E-2
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[3]} >> ../experiment_data/ZFP/CESM/1E-3
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[4]} >> ../experiment_data/ZFP/CESM/1E-4
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[5]} >> ../experiment_data/ZFP/CESM/1E-5
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[6]} >> ../experiment_data/ZFP/CESM/1E-6
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[7]} >> ../experiment_data/ZFP/CESM/1E-7
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -2 3600 1800 -s -a ${A[8]} >> ../experiment_data/ZFP/CESM/1E-8
done < ./ZFP-X/CESM

while read line
do
  A=($line)
  echo ${A[0]}
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[1]} >> ../experiment_data/ZFP/NYX/1E-1
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[2]} >> ../experiment_data/ZFP/NYX/1E-2
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[3]} >> ../experiment_data/ZFP/NYX/1E-3
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[4]} >> ../experiment_data/ZFP/NYX/1E-4
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[5]} >> ../experiment_data/ZFP/NYX/1E-5
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[6]} >> ../experiment_data/ZFP/NYX/1E-6
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[7]} >> ../experiment_data/ZFP/NYX/1E-7
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 512 512 512 -s -a ${A[8]} >> ../experiment_data/ZFP/NYX/1E-8
done < ./ZFP-X/NYX
while read line
do
  A=($line)
  echo ${A[0]}
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[1]} >> ../experiment_data/ZFP/Miranda/1E-1
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[2]} >> ../experiment_data/ZFP/Miranda/1E-2
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[3]} >> ../experiment_data/ZFP/Miranda/1E-3
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[4]} >> ../experiment_data/ZFP/Miranda/1E-4
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[5]} >> ../experiment_data/ZFP/Miranda/1E-5
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[6]} >> ../experiment_data/ZFP/Miranda/1E-6
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[7]} >> ../experiment_data/ZFP/Miranda/1E-7
  ../raw_zfp/bin/zfp -d -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 384 384 256 -s -a ${A[8]} >> ../experiment_data/ZFP/Miranda/1E-8
done < ./ZFP-X/Mi


while read line
do
  A=($line)
  echo ${A[0]}
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[1]} >> ../experiment_data/ZFP/Hu/1E-1
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[2]} >> ../experiment_data/ZFP/Hu/1E-2
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[3]} >> ../experiment_data/ZFP/Hu/1E-3
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[4]} >> ../experiment_data/ZFP/Hu/1E-4
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[5]} >> ../experiment_data/ZFP/Hu/1E-5
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[6]} >> ../experiment_data/ZFP/Hu/1E-6
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[7]} >> ../experiment_data/ZFP/Hu/1E-7
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 500 500 100 -s -a ${A[8]} >> ../experiment_data/ZFP/Hu/1E-8
done < ./ZFP-X/Hu

while read line
do
  A=($line)
  echo ${A[0]}
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[1]} >> ../experiment_data/ZFP/SCALE/1E-1
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[2]} >> ../experiment_data/ZFP/SCALE/1E-2
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[3]} >> ../experiment_data/ZFP/SCALE/1E-3
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[4]} >> ../experiment_data/ZFP/SCALE/1E-4
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[5]} >> ../experiment_data/ZFP/SCALE/1E-5
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[6]} >> ../experiment_data/ZFP/SCALE/1E-6
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[7]} >> ../experiment_data/ZFP/SCALE/1E-7
  ../raw_zfp/bin/zfp -f -i ${A[0]} -z ../decompress_file/ZFP${A[0]:7}.zfp -o ../decompress_file/ZFP-X${A[0]:7}.zfp.out -3 1200 1200 98 -s -a ${A[8]} >> ../experiment_data/ZFP/SCALE/1E-8
done < ./ZFP-X/SCALE

