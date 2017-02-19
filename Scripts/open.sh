#!/bin/bash

clear
echo "hi"
#python /home/pi/Desktop/delay.py
echo "500" > proc/sys/vm/vfs_cache_pressure
cd /media/pi/5C7F-1F9D
rm -R asdf
mkdir asdf
> data.txt
echo "\n" > data.txt
python /home/pi/Desktop/launcher.py