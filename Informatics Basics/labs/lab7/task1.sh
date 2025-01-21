#!/bin/bash

PATH=$1
PERIOD=$2

sleep 5s

PID=-1
START_TIMESTAMP=$(date + %s)
LOGS_FILE="output_$START_TIMESTAMP.log"
ERRORS_FILE="errors_$START_TIMESTAMP.log"

while true; do
   if ! ps -p $PID > /dev/null 2>&1; then
      bash $PATH 1>>$LOGS_FILE 2>>$ERRORS_FILE & 
      PID=$!
      echo "Pid: $PID"
   else
      echo "слишком рано"
   fi
   sleep 5s
done