acc=/home/hodge/lede/linkit-smart-7688-lede/staging_dir/toolchain-mipsel_24kc_gcc-5.4.0_musl-1.1.16/bin/mipsel-openwrt-linux-gcc
cc=gcc

all: nonblock-socket.exe

nonblock-socket.exe: nonblock-socket.o fileUtility.o
	$(cc) -o nonblock-socket.exe nonblock-socket.o fileUtility.o cJSON.o

fileUtility.o: fileUtility.c cJSON.o
	$(cc) -c fileUtility.c cJSON.o

nonblock-socket.o: nonblock-socket.c
	$(cc) -c nonblock-socket.c

cJSON.o: cjson/cJSON.c
	$(cc) -c cjson/cJSON.c
     
clean:
	rm *.o nonblock-socket.exe

