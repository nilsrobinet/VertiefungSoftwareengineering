#!/bin/bash

DEPLOY_HOST="localhost"

echo "#####################"
echo "Deployment Triggered"
echo "#####################"
echo ""
echo "ls of build directory"
echo `ls -la build`
echo ""
echo "deploying to $DEPLOY_HOST"
echo ""
echo "user identity:"
echo `id`
echo ""

# Escape from docker
rsync -e "ssh -o StrictHostKeyChecking=no" build/demo_docker.tar root@$DEPLOY_HOST:/tmp/demo_docker.tar
ssh -o StrictHostKeyChecking=no root@$DEPLOY_HOST -i /root/.ssh/id_ed25519 \
'echo "successfully connected" &&\
docker load -i "/tmp/demo_docker.tar" &&\
docker run -d --name --publish 8080:8080 webapp_demo_container webapp_demo_docker'

#$(docker images --format="{{.Repository}}:{{.ID}}" | grep "webapp_demo_docker" | awk "{print $2}")'
