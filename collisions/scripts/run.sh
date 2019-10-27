#!/bin/bash

cfall
sh scripts/build.sh
if [ "$1" = "release" ]
then
    ./bin/release/collisions 
else
    ./bin/debug/collisions 
fi