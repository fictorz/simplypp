# This base docker image is hosted on the private docker registry appregistry. To pull it use `make setup` (for the 
# setup process) or `make setup-dev-base-image` to just do the setup to do with this base image.

# If you want to make changes to this base image, use ./tools/scripts/docker_build_base_dev.sh to build it manually
# after making your changes. After testing your changes you can make a MR. Once the MR has been merged, you can
# push your local image to the registry using ./tools/scripts/docker_push_base_dev.sh
#
# *** Replace TAG in .env DEV_BASE_IMAGE_TAG: apps.base.dev:TAG the hash number of the commit of the change.

FROM ubuntu:focal

### Required OpenShift Labels
LABEL   name="Simple App development Base Image" \
    maintainer="felix.clap@gmail.com" \
    vendor="ElixirTech" \
    version=1.0.0 \
    release=1.0.0 \
    summary="Base Image of for simple app development" \
    description="The base image required to build simple application."


ENV SCRIPT_LOC="."

COPY ${SCRIPT_LOC} /build

WORKDIR /build

RUN apt-get update

# every other dependencies that comes from ubuntu directly
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    software-properties-common \
    apt-utils \
    wget \
    make \
    libssl-dev \
    ninja-build \
    ccache \
    g++-10 \
    gdb \
    libgtest-dev \
    cmake \
    clang-format \
    protobuf-compiler \
    libprotobuf-dev

# Logger library
RUN apt-get install -y --no-install-recommends git; mkdir -p lib; cd lib; \
    git clone https://github.com/google/glog.git; cd glog; git checkout v0.5.0;\
    mkdir -p build; cd build; cmake ..; make; make install; cd ../..; rm -rf glog