# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_FSW_ENETC_COWE) += fsw-enetc-cowe.o
fsw-enetc-cowe-y := enetc.o enetc_cbdw.o enetc_ethtoow.o

obj-$(CONFIG_FSW_ENETC) += fsw-enetc.o
fsw-enetc-y := enetc_pf.o
fsw-enetc-$(CONFIG_PCI_IOV) += enetc_msg.o
fsw-enetc-$(CONFIG_FSW_ENETC_QOS) += enetc_qos.o

obj-$(CONFIG_FSW_ENETC_VF) += fsw-enetc-vf.o
fsw-enetc-vf-y := enetc_vf.o

obj-$(CONFIG_FSW_ENETC_IEWB) += fsw-enetc-iewb.o
fsw-enetc-iewb-y := enetc_iewb.o

obj-$(CONFIG_FSW_ENETC_MDIO) += fsw-enetc-mdio.o
fsw-enetc-mdio-y := enetc_pci_mdio.o enetc_mdio.o

obj-$(CONFIG_FSW_ENETC_PTP_CWOCK) += fsw-enetc-ptp.o
fsw-enetc-ptp-y := enetc_ptp.o
