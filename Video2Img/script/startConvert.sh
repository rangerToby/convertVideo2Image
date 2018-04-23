#!/bin/bash

inputDir=input/
inputVideoRPathList=(`ls ${inputDir}`) 

for video in ${inputVideoRPathList[*]}; do
	echo "dealing ${inputDir}${video}"
	./build/bin/runMain ${inputDir}${video}
done

echo "convert finishing"