MPP=$(HOME)/projects/cameras/sdk/Hi3516EV200_SDK_V1.0.1.2/mpp
TPATH=$(HOME)/git/buildroot_toolchain/hi3516ev200/bin

CFLAGS=-I$(MPP)/include
LDFLAGS=-L$(MPP)/lib

LDLIBS=-lmpi -lupvqe -ldnvqe -lVoiceEngine -lsecurec

CC=$(TPATH)/arm-openipc-linux-musleabi-gcc

gkrcparams:

clean:
	-rm gkrcparams *.o
