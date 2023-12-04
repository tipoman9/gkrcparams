
#TPATH=$(HOME)/git/buildroot_toolchain/hi3516ev200/bin
TPATH=$(HOME)/src/openipc-firmware/output/host/bin

#MPP=$(HOME)/src/openipc-firmware/output/build/hisilicon-opensdk-c033009fa4551650480604dababcb5a852983593
MPP=$(HOME)/src/silicon_research/sdk/gk7205v300/gmp

CFLAGS=-I$(MPP)/include

LDFLAGS=-L$(MPP)/lib_nolog/static
#LDFLAGS=-L/home/home/src/openipc-firmware/output/per-package/hisilicon-osdrv-hi3516ev200/target/usr/lib

LDLIBS=-lgk_api -lupvqe -ldnvqe -lvoice_engine -lsecurec

CC=$(TPATH)/arm-openipc-linux-musleabi-gcc

gkrcparams:

clean:
	-rm gkrcparams *.o
