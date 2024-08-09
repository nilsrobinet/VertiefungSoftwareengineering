#!/bin/bash
DOCKERFILE_ROOT="$(dirname "$0")/../WebappDemo"

# Docker image bauen und verpacken
echo "Buildding docker image with:"
echo "docker build $DOCKERFILE_ROOT --tag webapp_demo_docker"
echo `id`
docker build $DOCKERFILE_ROOT --tag webapp_demo_docker
#docker save -o build/demo_docker.tar webapp_demo_docker
#
#chmod 755 build/demo_docker.tar
