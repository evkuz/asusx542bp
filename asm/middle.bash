#!/bin/bash

mid="/home/evkuz/asm/mid_val.txt"

#echo "rdtsc started at $(date)" >> $mid

result="/home/evkuz/asm/middle_out.txt"
touch $result
cp /dev/null $result
count=50
num=$count
script="/home/evkuz/asm/rdtsc_05"
df=0 # хранитель суммы
while [ $count != "0" ]
  do
  output=$($script)  
  df=$(($df + $output))   
  echo "$output" >> $result # $df
  sleep 1
   count=$[$count -1]
done
middle_df=$(( $df / $num ))
#echo "middle value of tick is ${middle_df}" >> $mid
echo ${middle_df} >> $mid
#echo "rdtsc finished at $(date)" >> $mid
