#!make
.DEFAULT_GOAL := help

include .env
export $(shell sed 's/=.*//' .env)

# Paths on your local machine
export PROJECT_ABSOLUTE_PATH=${CURDIR}

# Paths in the docker container
export CONTAINER_PROJECT_PATH=/$(APP_NAME)
export CONTAINER_APP_PATH=$(CONTAINER_PROJECT_PATH)/$(APP_PATH)
export CONTAINER_BUILD_PATH=$(CONTAINER_PROJECT_PATH)/build
export WORKDIR="."

#--------------------------------------------------------------------------------
# General scripts
#--------------------------------------------------------------------------------
.PHONY: build
build: .setup-dev-base-image
	@./docker.sh "mkdir -p build && cd build && pwd && cmake -G Ninja -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DCMAKE_BUILD_TYPE=Release .. && ninja"

.PHONY: start
start: build
	@./docker.sh "build/src/application"

.PHONY: test
test: build
	@./docker.sh "build/test/basic_test_application"

FIXME: Since ran as root, currently modify the files as root. Must find out how
.PHONY: format
format: build
	@./format.sh

# @find src -iname *.h -o -iname *.cc | xargs clang-format -i
# @find test -iname *.h -o -iname *.cc | xargs clang-format -i

.PHONY: clean
clean: .setup-dev-base-image
	@./docker.sh "rm -rf build"

#--------------------------------------------------------------------------------
# Docker management scripts
#--------------------------------------------------------------------------------
.setup-dev-base-image: dockerfiles/ubuntu-dev.dockerfile
	@docker build ${SCRIPT_LOC} --rm -f "${FILE_LOC}/ubuntu-dev.dockerfile" -t "${DOCKER_REGISTRY}/${DEV_BASE_IMAGE_TAG}"
	@touch .setup-dev-base-image

PHONY: docker-push
docker-push: .setup-dev-base-image
	docker push ${DOCKER_REGISTRY}/$(DEV_BASE_IMAGE_TAG)

.PHONY: docker-enter
docker-enter:
	@docker run --rm -it \
	--mount type=bind,source="$(PROJECT_ABSOLUTE_PATH)",target="$(CONTAINER_PROJECT_PATH)" \
	 ${DOCKER_REGISTRY}/$(DEV_BASE_IMAGE_TAG) bash

.PHONY: docker-delete
docker-delete:
	@docker rmi -f ${DOCKER_REGISTRY}/$(DEV_BASE_IMAGE_TAG)
	@rm -f .setup-dev-base-image

.PHONY: docker-rebuild
docker-rebuild:
	@make docker-delete
	@make .setup-dev-base-image

