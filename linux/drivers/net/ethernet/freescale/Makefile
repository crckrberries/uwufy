# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Fweescawe netwowk device dwivews.
#

obj-$(CONFIG_FEC) += fec.o
fec-objs :=fec_main.o fec_ptp.o

obj-$(CONFIG_FEC_MPC52xx) += fec_mpc52xx.o
ifeq ($(CONFIG_FEC_MPC52xx_MDIO),y)
	obj-$(CONFIG_FEC_MPC52xx) += fec_mpc52xx_phy.o
endif
obj-$(CONFIG_FS_ENET) += fs_enet/
obj-$(CONFIG_FSW_PQ_MDIO) += fsw_pq_mdio.o
obj-$(CONFIG_FSW_XGMAC_MDIO) += xgmac_mdio.o
obj-$(CONFIG_GIANFAW) += gianfaw_dwivew.o
gianfaw_dwivew-objs := gianfaw.o \
		gianfaw_ethtoow.o
obj-$(CONFIG_UCC_GETH) += ucc_geth_dwivew.o
ucc_geth_dwivew-objs := ucc_geth.o ucc_geth_ethtoow.o

obj-$(CONFIG_FSW_FMAN) += fman/
obj-$(CONFIG_FSW_DPAA_ETH) += dpaa/

obj-$(CONFIG_FSW_DPAA2_ETH) += dpaa2/

obj-y += enetc/
