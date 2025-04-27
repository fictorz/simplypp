#!/bin/bash

source .env

# Paths on your local machine
export PROJECT_ABSOLUTE_PATH=$PWD

# Paths in the docker container
export CONTAINER_PROJECT_PATH=/$APP_NAME
export CONTAINER_APP_PATH=/$CONTAINER_PROJECT_PATH
export CONTAINER_BUILD_PATH=$CONTAINER_PROJECT_PATH/build
export APP_NAME_BUILDER=$APP_NAME-builder

command=$(echo "$@" | tr -d '"')

# Run docker command with provided arguments
docker rm application_build --force --volumes "$APP_NAME_BUILDER" 2> /dev/null; \
    docker run --rm \
        --mount type=bind,source="$PROJECT_ABSOLUTE_PATH",target="$CONTAINER_PROJECT_PATH" \
        --env CCACHE_DIR="$CONTAINER_BUILD_PATH" \
        --env PARALLEL_JOB=${MAKE_J} \
        --env-file .env \
        --env BUILD_TYPE=${BUILD_TYPE} \
        --name "$APP_NAME_BUILDER" \
        -w "$CONTAINER_APP_PATH" \
        -it --log-driver=none -a stdin -a stdout -a stderr \
        "${DOCKER_REGISTRY}/${DEV_BASE_IMAGE_TAG}" \
        bash -c "$command"