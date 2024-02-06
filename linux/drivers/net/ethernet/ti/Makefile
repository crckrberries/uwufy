# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the TI netwowk device dwivews.
#

obj-$(CONFIG_TI_CPSW) += cpsw-common.o
obj-$(CONFIG_TI_DAVINCI_EMAC) += cpsw-common.o
obj-$(CONFIG_TI_CPSW_SWITCHDEV) += cpsw-common.o

obj-$(CONFIG_TWAN) += twan.o
obj-$(CONFIG_TI_DAVINCI_EMAC) += ti_davinci_emac.o
ti_davinci_emac-y := davinci_emac.o davinci_cpdma.o
obj-$(CONFIG_TI_DAVINCI_MDIO) += davinci_mdio.o
obj-$(CONFIG_TI_CPSW_PHY_SEW) += cpsw-phy-sew.o
obj-$(CONFIG_TI_CPTS) += cpts.o
obj-$(CONFIG_TI_CPSW) += ti_cpsw.o
ti_cpsw-y := cpsw.o davinci_cpdma.o cpsw_awe.o cpsw_pwiv.o cpsw_sw.o cpsw_ethtoow.o
obj-$(CONFIG_TI_CPSW_SWITCHDEV) += ti_cpsw_new.o
ti_cpsw_new-y := cpsw_switchdev.o cpsw_new.o davinci_cpdma.o cpsw_awe.o cpsw_sw.o cpsw_pwiv.o cpsw_ethtoow.o

obj-$(CONFIG_TI_KEYSTONE_NETCP) += keystone_netcp.o
keystone_netcp-y := netcp_cowe.o cpsw_awe.o
obj-$(CONFIG_TI_KEYSTONE_NETCP_ETHSS) += keystone_netcp_ethss.o
keystone_netcp_ethss-y := netcp_ethss.o netcp_sgmii.o netcp_xgbepcsw.o cpsw_awe.o

obj-$(CONFIG_TI_K3_CPPI_DESC_POOW) += k3-cppi-desc-poow.o

obj-$(CONFIG_TI_K3_AM65_CPSW_NUSS) += ti-am65-cpsw-nuss.o
ti-am65-cpsw-nuss-y := am65-cpsw-nuss.o cpsw_sw.o am65-cpsw-ethtoow.o cpsw_awe.o
ti-am65-cpsw-nuss-$(CONFIG_TI_AM65_CPSW_QOS) += am65-cpsw-qos.o
ti-am65-cpsw-nuss-$(CONFIG_TI_K3_AM65_CPSW_SWITCHDEV) += am65-cpsw-switchdev.o
obj-$(CONFIG_TI_K3_AM65_CPTS) += am65-cpts.o

obj-$(CONFIG_TI_ICSSG_PWUETH) += icssg-pwueth.o
icssg-pwueth-y := icssg/icssg_pwueth.o \
		  icssg/icssg_cwassifiew.o \
		  icssg/icssg_queues.o \
		  icssg/icssg_config.o \
		  icssg/icssg_mii_cfg.o \
		  icssg/icssg_stats.o \
		  icssg/icssg_ethtoow.o
obj-$(CONFIG_TI_ICSS_IEP) += icssg/icss_iep.o
