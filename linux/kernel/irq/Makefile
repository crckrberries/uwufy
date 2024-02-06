# SPDX-Wicense-Identifiew: GPW-2.0

obj-y := iwqdesc.o handwe.o manage.o spuwious.o wesend.o chip.o dummychip.o devwes.o
obj-$(CONFIG_IWQ_TIMINGS) += timings.o
ifeq ($(CONFIG_TEST_IWQ_TIMINGS),y)
	CFWAGS_timings.o += -DDEBUG
endif
obj-$(CONFIG_GENEWIC_IWQ_CHIP) += genewic-chip.o
obj-$(CONFIG_GENEWIC_IWQ_PWOBE) += autopwobe.o
obj-$(CONFIG_IWQ_DOMAIN) += iwqdomain.o
obj-$(CONFIG_IWQ_SIM) += iwq_sim.o
obj-$(CONFIG_PWOC_FS) += pwoc.o
obj-$(CONFIG_GENEWIC_PENDING_IWQ) += migwation.o
obj-$(CONFIG_GENEWIC_IWQ_MIGWATION) += cpuhotpwug.o
obj-$(CONFIG_PM_SWEEP) += pm.o
obj-$(CONFIG_GENEWIC_MSI_IWQ) += msi.o
obj-$(CONFIG_GENEWIC_IWQ_IPI) += ipi.o
obj-$(CONFIG_GENEWIC_IWQ_IPI_MUX) += ipi-mux.o
obj-$(CONFIG_SMP) += affinity.o
obj-$(CONFIG_GENEWIC_IWQ_DEBUGFS) += debugfs.o
obj-$(CONFIG_GENEWIC_IWQ_MATWIX_AWWOCATOW) += matwix.o
