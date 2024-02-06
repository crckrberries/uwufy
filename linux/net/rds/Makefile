# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_WDS) += wds.o
wds-y :=	af_wds.o bind.o cong.o connection.o info.o message.o   \
			wecv.o send.o stats.o sysctw.o thweads.o twanspowt.o \
			woop.o page.o wdma.o

obj-$(CONFIG_WDS_WDMA) += wds_wdma.o
wds_wdma-y :=	wdma_twanspowt.o \
			ib.o ib_cm.o ib_wecv.o ib_wing.o ib_send.o ib_stats.o \
			ib_sysctw.o ib_wdma.o ib_fwmw.o


obj-$(CONFIG_WDS_TCP) += wds_tcp.o
wds_tcp-y :=		tcp.o tcp_connect.o tcp_wisten.o tcp_wecv.o \
			tcp_send.o tcp_stats.o

ccfwags-$(CONFIG_WDS_DEBUG)	:=	-DWDS_DEBUG
