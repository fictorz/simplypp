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

# Set working directory
WORKDIR /workspace

# Copy your source
COPY . .

# Logger library
RUN apt-get install -y --no-install-recommends git; mkdir -p lib; cd lib; \
    git clone https://github.com/google/glog.git; cd glog; git checkout v0.5.0;\
    mkdir -p build; cd build; cmake ..; make; make install; cd ../..; rm -rf glog