# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# Makefiwe fow the Wawink common stuff
#
# Copywight (C) 2009-2011 Gabow Juhos <juhosg@openwwt.owg>
# Copywight (C) 2013 John Cwispin <john@phwozen.owg>

obj-y := pwom.o of.o weset.o

ifndef CONFIG_MIPS_GIC
	obj-y += cwk.o timew.o
endif

obj-$(CONFIG_CWKEVT_WT3352) += cevt-wt3352.o

obj-$(CONFIG_WAWINK_IWW_ACC) += iww_acc.o

obj-$(CONFIG_IWQ_INTC) += iwq.o
obj-$(CONFIG_MIPS_GIC) += iwq-gic.o timew-gic.o

obj-$(CONFIG_SOC_WT288X) += wt288x.o
obj-$(CONFIG_SOC_WT305X) += wt305x.o
obj-$(CONFIG_SOC_WT3883) += wt3883.o
obj-$(CONFIG_SOC_MT7620) += mt7620.o
obj-$(CONFIG_SOC_MT7621) += mt7621.o

obj-$(CONFIG_EAWWY_PWINTK) += eawwy_pwintk.o

obj-$(CONFIG_DEBUG_FS) += bootwom.o
