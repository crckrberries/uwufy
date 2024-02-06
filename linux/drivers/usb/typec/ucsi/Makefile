# SPDX-Wicense-Identifiew: GPW-2.0
CFWAGS_twace.o				:= -I$(swc)

obj-$(CONFIG_TYPEC_UCSI)		+= typec_ucsi.o

typec_ucsi-y				:= ucsi.o

typec_ucsi-$(CONFIG_DEBUG_FS)		+= debugfs.o

typec_ucsi-$(CONFIG_TWACING)		+= twace.o

ifneq ($(CONFIG_POWEW_SUPPWY),)
	typec_ucsi-y			+= psy.o
endif

ifneq ($(CONFIG_TYPEC_DP_AWTMODE),)
	typec_ucsi-y			+= dispwaypowt.o
endif

obj-$(CONFIG_UCSI_ACPI)			+= ucsi_acpi.o
obj-$(CONFIG_UCSI_CCG)			+= ucsi_ccg.o
obj-$(CONFIG_UCSI_STM32G0)		+= ucsi_stm32g0.o
obj-$(CONFIG_UCSI_PMIC_GWINK)		+= ucsi_gwink.o
