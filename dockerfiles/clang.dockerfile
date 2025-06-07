FROM silkeh/clang:16

# Optional: Install tools
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    git \
    gdb \
    vim \
    pkg-config \
    ninja-build \
    libgtest-dev \
    clang-format \
    protobuf-compiler \
    libprotobuf-dev


    #     build-essential \
    # software-properties-common \
    # apt-utils \
    # wget \
    # make \
    # libssl-dev \
    # ninja-build \
    # ccache \
    # g++-13 \
    # gdb \
    # libgtest-dev \
    # cmake \
    # clang-format \
    # protobuf-compiler \
    # libprotobuf-dev


# Set working directory
WORKDIR /workspace

# Copy your source
COPY . .

# Default command
# CMD ["bash"]


# FROM ubuntu:focal

# ### Required OpenShift Labels
# LABEL   name="Simple App development Base Image" \
#     maintainer="felix.clap@gmail.com" \
#     vendor="ElixirTech" \
#     version=1.0.0 \
#     release=1.0.0 \
#     summary="Base Image of for simple app development" \
#     description="The base image required to build simple application."


# ENV SCRIPT_LOC="."

# COPY ${SCRIPT_LOC} /build

# WORKDIR /build

# RUN apt-get update

# # every other dependencies that comes from ubuntu directly
# RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
#     build-essential \
#     software-properties-common \
#     apt-utils \
#     wget \
#     make \
#     libssl-dev \
#     ninja-build \
#     ccache \
#     g++-13 \
#     gdb \
#     libgtest-dev \
#     cmake \
#     clang-format \
#     protobuf-compiler \
#     libprotobuf-dev

# Logger library
RUN apt-get install -y --no-install-recommends git; mkdir -p lib; cd lib; \
    git clone https://github.com/google/glog.git; cd glog; git checkout v0.5.0;\
    mkdir -p build; cd build; cmake ..; make; make install; cd ../..; rm -rf glog