#!/usr/bin/env bash

function stop_containers()
{
running_containers=$(docker ps --format "{{.Names}}")

for i in ${running_containers[*]}
do
  if [[ "$i" =~ apollo_* ]];then
    printf %-*s 70 "stopping container: $i ..."
    docker stop $i > /dev/null
    if [ $? -eq 0 ];then
      printf "\033[32m[DONE]\033[0m\n"
    else
      printf "\033[31m[FAILED]\033[0m\n"
    fi
  fi
done
}

function local_volumes() {
    set +x
    ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd -P )"
    volumes="-v $ROOT_DIR:/remote_control \
             -v $HOME/.cache:${DOCKER_HOME}/.cache \
             -v /dev:/dev \
             -v /media:/media \
             -v /tmp/.X11-unix:/tmp/.X11-unix \
             -v /tmp/.docker.xauth:/tmp/.docker.xauth \
             -v /etc/localtime:/etc/localtime"
    echo "${volumes}"
    set -x
}

function main(){
    stop_containers

    IMG="licaili193/remote_control:latest"
    info "Start docker container based on local image : $IMG"

    DEV_NAME="remote-dev"
    docker ps -a --format "{{.Names}}" | grep "$DEV_NAME" 1>/dev/null
    if [ $? == 0 ]; then
        docker stop $DEV_NAME 1>/dev/null
        docker rm -v -f $DEV_NAME 1>/dev/null
    fi

    XAUTH=/tmp/.docker.xauth
    rm $XAUTH 2> /dev/null
    touch $XAUTH
    xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
    docker run --gpus all -it -d \
        --name=$DEV_NAME \
        $(local_volumes) \
        -e DISPLAY=$DISPLAY \
        -e XAUTHORITY=$XAUTH \
        --net=host \
        ${IMG}
    set +x
    if [ $? -ne 0 ]; then
        error "Failed to start docker container \"$DEV_NAME\" based on image: $IMG"
        exit 1
    fi
    docker exec remote-dev chmod a+rwx /tmp/.X11-unix
    docker exec remote-dev chmod a+rwx /tmp/.docker.xauth
    set -x
}

main
