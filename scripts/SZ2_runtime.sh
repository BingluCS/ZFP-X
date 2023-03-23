
rm -rf ../experiment_data/SZ2/CESM/* ../experiment_data/SZ2/Miranda/* ../experiment_data/SZ2/Hu/* ../experiment_data/SZ2/NYX/* 
rm -rf ../experiment_data/SZ2/SCALE/*

while read line
do
  A=($line)
  echo ${A[0]}
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[1]} >> ../experiment_data/SZ2/CESM/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[2]} >> ../experiment_data/SZ2/CESM/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[3]} >> ../experiment_data/SZ2/CESM/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[4]} >> ../experiment_data/SZ2/CESM/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[5]} >> ../experiment_data/SZ2/CESM/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[6]} >> ../experiment_data/SZ2/CESM/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[7]} >> ../experiment_data/SZ2/CESM/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -2 3600 1800 -M ABS -A ${A[8]} >> ../experiment_data/SZ2/CESM/1E-8
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -2 3600 1800 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/CESM/1E-8
done < ./ZFP-X/CESM

while read line
do
  A=($line)
  echo ${A[0]}
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[1]} >> ../experiment_data/SZ2/NYX/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[2]} >> ../experiment_data/SZ2/NYX/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[3]} >> ../experiment_data/SZ2/NYX/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[4]} >> ../experiment_data/SZ2/NYX/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[5]} >> ../experiment_data/SZ2/NYX/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[6]} >> ../experiment_data/SZ2/NYX/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[7]} >> ../experiment_data/SZ2/NYX/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 512 512 512 -M ABS -A ${A[8]} >> ../experiment_data/SZ2/NYX/1E-8
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 512 512 512 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/NYX/1E-8
done < ./ZFP-X/NYX

while read line
do
  A=($line)
  echo ${A[0]}
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[1]} >> ../experiment_data/SZ2/Miranda/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[2]} >> ../experiment_data/SZ2/Miranda/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[3]} >> ../experiment_data/SZ2/Miranda/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[4]} >> ../experiment_data/SZ2/Miranda/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[5]} >> ../experiment_data/SZ2/Miranda/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[6]} >> ../experiment_data/SZ2/Miranda/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[7]} >> ../experiment_data/SZ2/Miranda/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -d -i ${A[0]} -3 384 384 256 -M ABS -A ${A[8]} >> ../experiment_data/SZ2/Miranda/1E-8
  /home/thinker/lb/compressor/SZ/example/sz -x -d -i ${A[0]} -3 384 384 256 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Miranda/1E-8
done < ./ZFP-X/Mi


while read line
do
  A=($line)
  echo ${A[0]}
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[1]} >> ../experiment_data/SZ2/Hu/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[2]} >> ../experiment_data/SZ2/Hu/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[3]} >> ../experiment_data/SZ2/Hu/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[4]} >> ../experiment_data/SZ2/Hu/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[5]} >> ../experiment_data/SZ2/Hu/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[6]} >> ../experiment_data/SZ2/Hu/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[7]} >> ../experiment_data/SZ2/Hu/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 500 500 100 -M ABS -A ${A[8]} >> ../experiment_data/SZ2/Hu/1E-8
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 500 500 100 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/Hu/1E-8
done < ./ZFP-X/Hu

while read line
do
  A=($line)
  echo ${A[0]}
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[1]} >> ../experiment_data/SZ2/SCALE/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-1
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[2]} >> ../experiment_data/SZ2/SCALE/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-2
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[3]} >> ../experiment_data/SZ2/SCALE/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-3
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[4]} >> ../experiment_data/SZ2/SCALE/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-4
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[5]} >> ../experiment_data/SZ2/SCALE/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-5
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[6]} >> ../experiment_data/SZ2/SCALE/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-6
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[7]} >> ../experiment_data/SZ2/SCALE/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-7
  /home/thinker/lb/compressor/SZ/example/sz -z ../decompress_file/SZ2${A[0]:7}.sz -f -i ${A[0]} -3 1200 1200 98 -M ABS -A ${A[8]} >> ../experiment_data/SZ2/SCALE/1E-8
  /home/thinker/lb/compressor/SZ/example/sz -x -f -i ${A[0]} -3 1200 1200 98 -s ../decompress_file/SZ2${A[0]:7}.sz -a  >> ../experiment_data/SZ2/SCALE/1E-8
done < ./ZFP-X/SCALE

