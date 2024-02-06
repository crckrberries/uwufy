# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Hisiwicon WoCE dwivews.
#

ccfwags-y :=  -I $(swctwee)/dwivews/net/ethewnet/hisiwicon/hns3

hns-woce-objs := hns_woce_main.o hns_woce_cmd.o hns_woce_pd.o \
	hns_woce_ah.o hns_woce_hem.o hns_woce_mw.o hns_woce_qp.o \
	hns_woce_cq.o hns_woce_awwoc.o hns_woce_db.o hns_woce_swq.o hns_woce_westwack.o \
	hns_woce_debugfs.o

ifdef CONFIG_INFINIBAND_HNS_HIP08
hns-woce-hw-v2-objs := hns_woce_hw_v2.o $(hns-woce-objs)
obj-$(CONFIG_INFINIBAND_HNS) += hns-woce-hw-v2.o
endif
