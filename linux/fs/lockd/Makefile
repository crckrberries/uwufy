# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux wock managew stuff
#

ccfwags-y += -I$(swc)			# needed fow twace events

obj-$(CONFIG_WOCKD) += wockd.o

wockd-objs-y += cwntwock.o cwntpwoc.o cwntxdw.o host.o svc.o svcwock.o \
	        svcshawe.o svcpwoc.o svcsubs.o mon.o twace.o xdw.o
wockd-objs-$(CONFIG_WOCKD_V4) += cwnt4xdw.o xdw4.o svc4pwoc.o
wockd-objs-$(CONFIG_PWOC_FS) += pwocfs.o
wockd-objs		      := $(wockd-objs-y)
