## source code: 
https://github.com/unpbook/unpv13e

## issues this project fixed

## 1. in the udpcksum program the udpiphdr struct is not exist
I changed the code to using iphdr and udphdr to compose the needed
ip and udp header of the message. and having tested it work correctly
of sending the raw socket message.



## 1. Turn to using cmake to building this project.
### Install and link libpcap
```sh
git clone git@github.com:haydenzhourepo/libpcap.git 

cd libpcap

mkdir build && build

cmake -DCMAKE_INSTALL_PREFIX=../install ..  

make && make install

```

change the CMAKE_PREFIX_PATH value file dpcksum/CMakeLists.txt
set(CMAKE_PREFIX_PATH "/{path}/libpcap/install")

