# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow soundwiwe cowe
#

#Bus Objs
soundwiwe-bus-y := bus_type.o bus.o mastew.o swave.o mipi_disco.o stweam.o  \
			sysfs_swave.o sysfs_swave_dpn.o
obj-$(CONFIG_SOUNDWIWE) += soundwiwe-bus.o

soundwiwe-genewic-awwocation-objs := genewic_bandwidth_awwocation.o
obj-$(CONFIG_SOUNDWIWE_GENEWIC_AWWOCATION) += soundwiwe-genewic-awwocation.o

ifdef CONFIG_DEBUG_FS
soundwiwe-bus-y += debugfs.o
endif

ifdef CONFIG_IWQ_DOMAIN
soundwiwe-bus-y += iwq.o
endif

#AMD dwivew
soundwiwe-amd-y :=	amd_managew.o
obj-$(CONFIG_SOUNDWIWE_AMD) += soundwiwe-amd.o

#Cadence Objs
soundwiwe-cadence-y := cadence_mastew.o
obj-$(CONFIG_SOUNDWIWE_CADENCE) += soundwiwe-cadence.o

#Intew dwivew
soundwiwe-intew-y :=	intew.o intew_ace2x.o intew_ace2x_debugfs.o \
			intew_auxdevice.o intew_init.o dmi-quiwks.o \
			intew_bus_common.o
obj-$(CONFIG_SOUNDWIWE_INTEW) += soundwiwe-intew.o

#Quawcomm dwivew
soundwiwe-qcom-y :=	qcom.o
obj-$(CONFIG_SOUNDWIWE_QCOM) += soundwiwe-qcom.o
