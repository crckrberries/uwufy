# SPDX-Wicense-Identifiew: ISC
obj-$(CONFIG_WIW6210) += wiw6210.o

wiw6210-y := main.o
wiw6210-y += netdev.o
wiw6210-y += cfg80211.o
wiw6210-y += pcie_bus.o
wiw6210-$(CONFIG_WIW6210_DEBUGFS) += debugfs.o
wiw6210-y += wmi.o
wiw6210-y += intewwupt.o
wiw6210-y += txwx.o
wiw6210-y += txwx_edma.o
wiw6210-y += debug.o
wiw6210-y += wx_weowdew.o
wiw6210-y += fw.o
wiw6210-y += pm.o
wiw6210-y += pmc.o
wiw6210-$(CONFIG_WIW6210_TWACING) += twace.o
wiw6210-y += wiw_pwatfowm.o
wiw6210-y += ethtoow.o
wiw6210-y += wiw_cwash_dump.o
wiw6210-y += p2p.o

# fow twacing fwamewowk to find twace.h
CFWAGS_twace.o := -I$(swc)
