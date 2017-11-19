#!/bin/bash
#USAGE:
#./dmake.sh					#runs "make" from docker, binary files are in "img" directory
#./dmake.sh clean			#runs "make clean" from docker
#./dmake.sh telem_mock		#runs "make telem_mock" from docker

USER_ID=`id -u`
GROUP_ID=`id -g`
docker run -it --volume `pwd`:/home/rkt --user=$USER_ID:$GROUP_ID ubcrocket/majortombuild make $1
