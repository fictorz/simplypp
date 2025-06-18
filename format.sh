#!/bin/bash

source .env
# export $(shell sed 's/=.*//' .env) 

# Paths on your local machine
export PROJECT_ABSOLUTE_PATH=$PWD

# Paths in the docker container
export CONTAINER_PROJECT_PATH=/$APP_NAME
export CONTAINER_APP_PATH=$CONTAINER_PROJECT_PATH/$APP_PATH
export CONTAINER_BUILD_PATH=$CONTAINER_PROJECT_PATH/build
export APP_NAME_BUILDER=$APP_NAME-builder

command=$(echo "$@" | tr -d '"')

# echo "$command"
# Run docker command with provided arguments

if ! command -v clang-format &> /dev/null
then
    echo "clang-format could not be found"
    exit
fi

find src -iname *.h -o -iname *.cc | xargs clang-format -i
find test -iname *.h -o -iname *.cc | xargs clang-format -i

echo "File format completed."


# docker rm application_build --force --volumes "$APP_NAME_BUILDER" 2> /dev/null; \
#     docker run --rm \
#         --mount type=bind,source="$PROJECT_ABSOLUTE_PATH",target="$CONTAINER_PROJECT_PATH" \
#         --env CCACHE_DIR="$CONTAINER_BUILD_PATH" \
#         --env PARALLEL_JOB=${MAKE_J} \
#         --env-file .env \
#         --env BUILD_TYPE=${BUILD_TYPE} \
#         --name "$APP_NAME_BUILDER" \
#         -w "$CONTAINER_APP_PATH" \
#         -it --log-driver=none -a stdin -a stdout -a stderr \
#         "${DOCKER_REGISTRY}/${DEV_BASE_IMAGE_TAG}" \
#         /bin/bash -c "$command"