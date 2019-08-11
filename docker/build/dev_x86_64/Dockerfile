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
    libssl-dev \
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
    git clone --branch 3.4 https://github.com/opencv/opencv_contrib.git && \
    cd opencv_contrib && \
    cd .. && \
    git clone --branch 3.4 https://github.com/opencv/opencv.git && \
    cd opencv && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_GENERATE_PKGCONFIG=ON .. && \
    make -j7 && \
    make install && \
    echo '\n\n\nStage 2 completed\n\n\n'

# Install QT
RUN apt update -y && \
    apt-get install -y libx11-dev \
    xorg-dev \
    libglu1-mesa-dev \
    freeglut3-dev \
    libglew1.5 \
    libglew1.5-dev \
    libglu1-mesa \
    libglu1-mesa-dev \
    libgl1-mesa-glx \
    libgl1-mesa-dev && \
    cd /third_party && \
    git clone --branch=5.13.1 git://code.qt.io/qt/qt5.git && \
    cd qt5 && \
    ./init-repository && \
    mkdir build && \
    cd build && \
    ../configure -nomake examples -nomake tests -opensource --confirm-license && \
    make -j7 && \
    make install && \
    echo '\n\n\nStage 3 completed\n\n\n'
ENV PATH=/usr/local/Qt-5.13.1/bin:$PATH

# Install Fast-RTPS
COPY binary/eProsima_FastRTPS-1.7.2-Linux.tar.gz /third_party/eProsima_FastRTPS-1.7.2-Linux.tar.gz
RUN cd /third_party && \
    mkdir eProsima_FastRTPS-1.7.2-Linux && \
    cd eProsima_FastRTPS-1.7.2-Linux && \
    tar -xf ../eProsima_FastRTPS-1.7.2-Linux.tar.gz && \
    rm ../eProsima_FastRTPS-1.7.2-Linux.tar.gz && \
    cd requiredcomponents && \
    tar -xf eProsima_FastCDR-1.0.8-Linux.tar.gz && \
    rm eProsima_FastCDR-1.0.8-Linux.tar.gz && \
    cd eProsima_FastCDR-1.0.8-Linux && \
    ./configure && \
    make -j7 && \
    make install && \
    cd ../../eProsima_FastRTPS-1.7.2-Linux && \
    ./configure && \
    make -j7 && \
    make install && \
    cd /third_party && \
    git clone https://github.com/foonathan/memory.git && \
    cd memory && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_SHARED_LIBS=ON .. && \
    cmake --build . --target install && \
    echo '\n\n\nStage 4 completed (except copying cmake files)\n\n\n'
COPY binary/fastcdr /usr/local/share/fastcdr/cmake
COPY binary/fastrtps /usr/local/share/fastrtps/cmake

# Configure screens
RUN apt update -y && \
    apt-get install -y iputils-ping \
    xauth \
    x11-apps && \
    echo '\n\n\nStage 5 completed\n\n\n'

WORKDIR /remote_control

# RUN groupadd -r dev && useradd -r -g dev remote
# USER remote
