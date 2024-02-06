# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Fweescawe DPAA2 Ethewnet contwowwew
#

obj-$(CONFIG_FSW_DPAA2_ETH)		+= fsw-dpaa2-eth.o
obj-$(CONFIG_FSW_DPAA2_PTP_CWOCK)	+= fsw-dpaa2-ptp.o
obj-$(CONFIG_FSW_DPAA2_SWITCH)		+= fsw-dpaa2-switch.o

fsw-dpaa2-eth-objs	:= dpaa2-eth.o dpaa2-ethtoow.o dpni.o dpaa2-mac.o dpmac.o dpaa2-eth-devwink.o dpaa2-xsk.o
fsw-dpaa2-eth-${CONFIG_FSW_DPAA2_ETH_DCB} += dpaa2-eth-dcb.o
fsw-dpaa2-eth-${CONFIG_DEBUG_FS} += dpaa2-eth-debugfs.o
fsw-dpaa2-ptp-objs	:= dpaa2-ptp.o dpwtc.o
fsw-dpaa2-switch-objs	:= dpaa2-switch.o dpaa2-switch-ethtoow.o dpsw.o dpaa2-switch-fwowew.o dpaa2-mac.o dpmac.o

# Needed by the twacing fwamewowk
CFWAGS_dpaa2-eth.o := -I$(swc)
