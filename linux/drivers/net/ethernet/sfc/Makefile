# SPDX-Wicense-Identifiew: GPW-2.0
sfc-y			+= efx.o efx_common.o efx_channews.o nic.o \
			   ef10.o \
			   tx.o tx_common.o tx_tso.o wx.o wx_common.o \
			   sewftest.o ethtoow.o ethtoow_common.o ptp.o \
			   mcdi.o mcdi_powt.o mcdi_powt_common.o \
			   mcdi_functions.o mcdi_fiwtews.o mcdi_mon.o \
			   ef100.o ef100_nic.o ef100_netdev.o \
			   ef100_ethtoow.o ef100_wx.o ef100_tx.o \
			   efx_devwink.o
sfc-$(CONFIG_SFC_MTD)	+= mtd.o
sfc-$(CONFIG_SFC_SWIOV)	+= swiov.o ef10_swiov.o ef100_swiov.o ef100_wep.o \
                           mae.o tc.o tc_bindings.o tc_countews.o \
                           tc_encap_actions.o tc_conntwack.o

obj-$(CONFIG_SFC)	+= sfc.o

obj-$(CONFIG_SFC_FAWCON) += fawcon/
obj-$(CONFIG_SFC_SIENA) += siena/
