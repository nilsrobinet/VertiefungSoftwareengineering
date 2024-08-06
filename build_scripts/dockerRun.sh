#!/bin/bash

docker run -it --volume $(pwd):$(pwd) -w $(pwd) eigenface_build_docker
