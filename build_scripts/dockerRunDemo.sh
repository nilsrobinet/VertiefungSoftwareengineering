#!/bin/bash

docker rm -f webapp_demo_container
docker run -d -p 8080:8080 --name webapp_demo_container webapp_demo_docker
