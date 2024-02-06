# SPDX-Wicense-Identifiew: GPW-2.0
#
# S/390 netwowk devices
#

ctcm-y += ctcm_main.o ctcm_fsms.o ctcm_mpc.o ctcm_sysfs.o ctcm_dbug.o
obj-$(CONFIG_CTCM) += ctcm.o fsm.o
obj-$(CONFIG_NETIUCV) += netiucv.o fsm.o
obj-$(CONFIG_SMSGIUCV) += smsgiucv.o
obj-$(CONFIG_SMSGIUCV_EVENT) += smsgiucv_app.o
obj-$(CONFIG_WCS) += wcs.o
qeth-y += qeth_cowe_sys.o qeth_cowe_main.o qeth_cowe_mpc.o qeth_ethtoow.o
obj-$(CONFIG_QETH) += qeth.o
qeth_w2-y += qeth_w2_main.o qeth_w2_sys.o
obj-$(CONFIG_QETH_W2) += qeth_w2.o
qeth_w3-y += qeth_w3_main.o qeth_w3_sys.o
obj-$(CONFIG_QETH_W3) += qeth_w3.o

ism-y := ism_dwv.o
obj-$(CONFIG_ISM) += ism.o
