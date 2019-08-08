FROM nvidia/cuda:10.1-base-ubuntu18.04

# ENV DEBIAN_FRONTEND=noninteractive

# Install base packages
RUN apt-get update -y && \
    apt-get install -y \
    build-essential \
    cmake \
    curl \
    gdb \
    git \
    libgtest-dev \
    libgflags-dev \
    libgoogle-glog-dev \
    libyaml-cpp-dev \
    software-properties-common \
    unzip \
    v4l-utils \
    vim \
    wget \
    zip && \
    apt-get clean && rm -rf /var/lib/apt/lists/* && \
    echo '\n\n\nStage 1 completed\n\n\n'

# Install opencv
RUN add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main" && \
    apt update -y && \
    apt install -y libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    python-dev \
    python-numpy \
    libtbb2 \
    libtbb-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libjasper1\
    libjasper-dev \
    libdc1394-22-dev && \
    mkdir third_party && \
    cd third_party && \
    git clone https://github.com/opencv/opencv_contrib.git && \
    cd opencv_contrib && \
    git checkout -b 3.4 4ae44739a55683aa652bc8f63cf2af7572b3766a && \
    cd .. && \
    git clone https://github.com/opencv/opencv.git && \
    cd opencv && \
    git checkout -b 3.4 d513fb4c8e5a51093ba53e3953ab06d419a37fac && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_GENERATE_PKGCONFIG=ON .. && \
    make -j7 && \
    make install && \
    echo '\n\n\nStage 2 completed\n\n\n'