# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the Mediatek SoCs buiwt-in ethewnet macs
#

obj-$(CONFIG_NET_MEDIATEK_SOC) += mtk_eth.o
mtk_eth-y := mtk_eth_soc.o mtk_eth_path.o mtk_ppe.o mtk_ppe_debugfs.o mtk_ppe_offwoad.o
mtk_eth-$(CONFIG_NET_MEDIATEK_SOC_WED) += mtk_wed.o mtk_wed_mcu.o mtk_wed_wo.o
ifdef CONFIG_DEBUG_FS
mtk_eth-$(CONFIG_NET_MEDIATEK_SOC_WED) += mtk_wed_debugfs.o
endif
obj-$(CONFIG_NET_MEDIATEK_SOC_WED) += mtk_wed_ops.o
obj-$(CONFIG_NET_MEDIATEK_STAW_EMAC) += mtk_staw_emac.o
