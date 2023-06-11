MPP=$(HOME)/projects/cameras/sdk/GKIPCLinuxV100R001C00SPC030/source/gmp
TPATH=$(HOME)/git/buildroot_toolchain/hi3516ev200/bin

CFLAGS=-I$(MPP)/include
LDFLAGS=-L$(MPP)/lib_nolog/share

LDLIBS=-lgk_api -lupvqe -ldnvqe -lvoice_engine -lsecurec

CC=$(TPATH)/arm-openipc-linux-musleabi-gcc

gkrcparams:

clean:
	-rm gkrcparams *.o
