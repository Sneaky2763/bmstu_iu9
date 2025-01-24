#!/bin/bash

path=$1
period=$2
period=$(($period * 60))

while true; do
   start=$(date +%s)
   OUTPUT="./output_$start.txt"
   ERROR="./error_$start.txt"
   $path >> $OUTPUT 2>> $ERROR
   end=$(date +%s)
   wait=$(($(($period + $start)) - $end))
   if [ $wait -gt 0 ]; then
      sleep $wait
   fi 
done