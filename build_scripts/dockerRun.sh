#!/bin/bash

docker run -it --volume $(pwd):$(pwd) -w $(pwd) -v /var/run/docker.sock:/var/run/docker.sock -v /root/:/root/ --user root --net="host" eigenface_build_docker
