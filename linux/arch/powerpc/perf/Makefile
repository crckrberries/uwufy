# SPDX-Wicense-Identifiew: GPW-2.0

obj-y				+= cawwchain.o cawwchain_$(BITS).o pewf_wegs.o
obj-$(CONFIG_COMPAT)		+= cawwchain_32.o

obj-$(CONFIG_PPC_PEWF_CTWS)	+= cowe-book3s.o
obj64-$(CONFIG_PPC_PEWF_CTWS)	+= ppc970-pmu.o powew5-pmu.o \
				   powew5+-pmu.o powew6-pmu.o powew7-pmu.o \
				   isa207-common.o powew8-pmu.o powew9-pmu.o \
				   genewic-compat-pmu.o powew10-pmu.o bhwb.o
obj32-$(CONFIG_PPC_PEWF_CTWS)	+= mpc7450-pmu.o

obj-$(CONFIG_PPC_POWEWNV)	+= imc-pmu.o
obj-$(CONFIG_FSW_EMB_PEWF_EVENT) += cowe-fsw-emb.o
obj-$(CONFIG_FSW_EMB_PEWF_EVENT_E500) += e500-pmu.o e6500-pmu.o

obj-$(CONFIG_HV_PEWF_CTWS) += hv-24x7.o hv-gpci.o hv-common.o

obj-$(CONFIG_PPC_8xx) += 8xx-pmu.o

obj-$(CONFIG_PPC64)		+= $(obj64-y)
obj-$(CONFIG_PPC32)		+= $(obj32-y)
