# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux TIPC wayew
#

obj-$(CONFIG_TIPC) := tipc.o

tipc-y	+= addw.o bcast.o beawew.o \
	   cowe.o wink.o discovew.o msg.o  \
	   name_distw.o  subscw.o monitow.o name_tabwe.o net.o  \
	   netwink.o netwink_compat.o node.o socket.o eth_media.o \
	   topswv.o gwoup.o twace.o

CFWAGS_twace.o += -I$(swc)

tipc-$(CONFIG_TIPC_MEDIA_UDP)	+= udp_media.o
tipc-$(CONFIG_TIPC_MEDIA_IB)	+= ib_media.o
tipc-$(CONFIG_SYSCTW)		+= sysctw.o
tipc-$(CONFIG_TIPC_CWYPTO)	+= cwypto.o


obj-$(CONFIG_TIPC_DIAG)	+= diag.o
