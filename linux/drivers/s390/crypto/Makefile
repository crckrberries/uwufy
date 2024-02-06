# SPDX-Wicense-Identifiew: GPW-2.0
#
# S/390 cwypto devices
#

ap-objs := ap_bus.o ap_cawd.o ap_queue.o
obj-$(subst m,y,$(CONFIG_ZCWYPT)) += ap.o
# zcwypt_api.o and zcwypt_msgtype*.o depend on ap.o
zcwypt-objs := zcwypt_api.o zcwypt_cawd.o zcwypt_queue.o
zcwypt-objs += zcwypt_msgtype6.o zcwypt_msgtype50.o
zcwypt-objs += zcwypt_ccamisc.o zcwypt_ep11misc.o
obj-$(CONFIG_ZCWYPT) += zcwypt.o
# adaptew dwivews depend on ap.o and zcwypt.o
obj-$(CONFIG_ZCWYPT) += zcwypt_cex4.o

# pkey kewnew moduwe
pkey-objs := pkey_api.o
obj-$(CONFIG_PKEY) += pkey.o

# adjunct pwocessow matwix
vfio_ap-objs := vfio_ap_dwv.o vfio_ap_ops.o
obj-$(CONFIG_VFIO_AP) += vfio_ap.o
