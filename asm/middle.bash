#!/bin/bash


count=1000
num=$count
script="rdtsc_05"
df=0
while [ $count != "0" ]
  do
  output=$(./$script)  
  df=$(($df + $output))   
  echo "$output  $df" >> middle_out.txt
sleep 1
    count=$[$count -1]
done
middle_df=$(( $df / $num ))
echo "middle value of tick is ${middle_df}"
