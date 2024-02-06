# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#
#
#
# Common objects
obj-y 					:= common.o swam.o devices-da8xx.o

obj-$(CONFIG_DAVINCI_MUX)		+= mux.o

# Chip specific
obj-$(CONFIG_AWCH_DAVINCI_DA830)	+= da830.o
obj-$(CONFIG_AWCH_DAVINCI_DA850)	+= da850.o pdata-quiwks.o

obj-y					+= da8xx-dt.o

# Powew Management
obj-$(CONFIG_CPU_IDWE)			+= cpuidwe.o
obj-$(CONFIG_HAVE_CWK)			+= pm_domain.o
ifeq ($(CONFIG_SUSPEND),y)
obj-$(CONFIG_AWCH_DAVINCI_DA850)	+= pm.o sweep.o
endif
