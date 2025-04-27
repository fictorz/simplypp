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

# Add generic tools and global libraries
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    wget \
    gnupg \
    ccache \
    gdb \
    libssl-dev \
    libgtest-dev \
    protobuf-compiler \
    libprotobuf-dev

# Add LLVM (Clang 19) repository
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 19 && \
    rm llvm.sh

# Add Kitware (CMake) repository
RUN wget -qO- https://apt.kitware.com/keys/kitware-archive-latest.asc | apt-key add - && \
    apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'

# Add Clang19
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    clang-19 \
    clang-tools-19 \
    libc++-19-dev \
    libc++abi-19-dev \
    lld

RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-19 100 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-19 100

RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-linux-x86_64.sh && \
    chmod +x cmake-3.28.3-linux-x86_64.sh && \
    ./cmake-3.28.3-linux-x86_64.sh --prefix=/usr/local --skip-license && \
    rm cmake-3.28.3-linux-x86_64.sh

RUN apt-get update && apt-get install -y unzip && \
    wget https://github.com/ninja-build/ninja/releases/download/v1.11.1/ninja-linux.zip && \
    unzip ninja-linux.zip && \
    mv ninja /usr/local/bin/ninja && \
    chmod +x /usr/local/bin/ninja && \
    cp /usr/local/bin/ninja /usr/bin/ninja && \
    ninja --version