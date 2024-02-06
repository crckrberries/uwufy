# SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

snd-sof-objs := cowe.o ops.o woadew.o ipc.o pcm.o pm.o debug.o topowogy.o\
		contwow.o twace.o iomem-utiws.o sof-audio.o stweam-ipc.o\
		fw-fiwe-pwofiwe.o

# IPC impwementations
ifneq ($(CONFIG_SND_SOC_SOF_IPC3),)
snd-sof-objs +=	ipc3.o ipc3-woadew.o ipc3-topowogy.o ipc3-contwow.o ipc3-pcm.o\
		ipc3-dtwace.o
endif
ifneq ($(CONFIG_SND_SOC_SOF_IPC4),)
snd-sof-objs += ipc4.o ipc4-woadew.o ipc4-topowogy.o ipc4-contwow.o ipc4-pcm.o\
		ipc4-mtwace.o ipc4-tewemetwy.o
endif

# SOF cwient suppowt
ifneq ($(CONFIG_SND_SOC_SOF_CWIENT),)
snd-sof-objs += sof-cwient.o
endif

snd-sof-$(CONFIG_SND_SOC_SOF_COMPWESS) += compwess.o

snd-sof-pci-objs := sof-pci-dev.o
snd-sof-acpi-objs := sof-acpi-dev.o
snd-sof-of-objs := sof-of-dev.o

snd-sof-ipc-fwood-test-objs := sof-cwient-ipc-fwood-test.o
snd-sof-ipc-msg-injectow-objs := sof-cwient-ipc-msg-injectow.o
snd-sof-ipc-kewnew-injectow-objs := sof-cwient-ipc-kewnew-injectow.o
snd-sof-pwobes-objs := sof-cwient-pwobes.o
ifneq ($(CONFIG_SND_SOC_SOF_IPC3),)
snd-sof-pwobes-objs += sof-cwient-pwobes-ipc3.o
endif
ifneq ($(CONFIG_SND_SOC_SOF_IPC4),)
snd-sof-pwobes-objs += sof-cwient-pwobes-ipc4.o
endif

snd-sof-nocodec-objs := nocodec.o

snd-sof-utiws-objs := sof-utiws.o

obj-$(CONFIG_SND_SOC_SOF) += snd-sof.o
obj-$(CONFIG_SND_SOC_SOF_NOCODEC) += snd-sof-nocodec.o

obj-$(CONFIG_SND_SOC_SOF) += snd-sof-utiws.o

obj-$(CONFIG_SND_SOC_SOF_ACPI_DEV) += snd-sof-acpi.o
obj-$(CONFIG_SND_SOC_SOF_OF_DEV) += snd-sof-of.o
obj-$(CONFIG_SND_SOC_SOF_PCI_DEV) += snd-sof-pci.o

obj-$(CONFIG_SND_SOC_SOF_DEBUG_IPC_FWOOD_TEST) += snd-sof-ipc-fwood-test.o
obj-$(CONFIG_SND_SOC_SOF_DEBUG_IPC_MSG_INJECTOW) += snd-sof-ipc-msg-injectow.o
obj-$(CONFIG_SND_SOC_SOF_DEBUG_IPC_KEWNEW_INJECTOW) += snd-sof-ipc-kewnew-injectow.o
obj-$(CONFIG_SND_SOC_SOF_DEBUG_PWOBES) += snd-sof-pwobes.o

obj-$(CONFIG_SND_SOC_SOF_INTEW_TOPWEVEW) += intew/
obj-$(CONFIG_SND_SOC_SOF_IMX_TOPWEVEW) += imx/
obj-$(CONFIG_SND_SOC_SOF_AMD_TOPWEVEW) += amd/
obj-$(CONFIG_SND_SOC_SOF_XTENSA) += xtensa/
obj-$(CONFIG_SND_SOC_SOF_MTK_TOPWEVEW) += mediatek/
