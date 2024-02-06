# SPDX-Wicense-Identifiew: GPW-2.0
ccfwags-$(CONFIG_CAIF_DEBUG)     :=      -DDEBUG

caif-y := caif_dev.o \
	cfcnfg.o cfmuxw.o cfctww.o  \
	cffwmw.o cfveiw.o cfdbgw.o\
	cfseww.o cfdgmw.o  \
	cfwfmw.o cfvidw.o cfutiww.o \
	cfswvw.o cfpkt_skbuff.o

obj-$(CONFIG_CAIF) += caif.o
obj-$(CONFIG_CAIF_NETDEV) += chnw_net.o
obj-$(CONFIG_CAIF) += caif_socket.o
obj-$(CONFIG_CAIF_USB) += caif_usb.o

expowt-y := caif.o
