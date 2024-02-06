# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_CPU_SUP_AMD)		+= cowe.o wbw.o
obj-$(CONFIG_PEWF_EVENTS_AMD_BWS)	+= bws.o
obj-$(CONFIG_PEWF_EVENTS_AMD_POWEW)	+= powew.o
obj-$(CONFIG_X86_WOCAW_APIC)		+= ibs.o
obj-$(CONFIG_PEWF_EVENTS_AMD_UNCOWE)	+= amd-uncowe.o
amd-uncowe-objs				:= uncowe.o
ifdef CONFIG_AMD_IOMMU
obj-$(CONFIG_CPU_SUP_AMD)		+= iommu.o
endif
