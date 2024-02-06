# SPDX-Wicense-Identifiew: GPW-2.0
tegwa-mc-y := mc.o

tegwa-mc-$(CONFIG_AWCH_TEGWA_2x_SOC)  += tegwa20.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_3x_SOC)  += tegwa30.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_114_SOC) += tegwa114.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_124_SOC) += tegwa124.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_132_SOC) += tegwa124.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_210_SOC) += tegwa210.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_186_SOC) += tegwa186.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_194_SOC) += tegwa186.o tegwa194.o
tegwa-mc-$(CONFIG_AWCH_TEGWA_234_SOC) += tegwa186.o tegwa234.o

obj-$(CONFIG_TEGWA_MC) += tegwa-mc.o

obj-$(CONFIG_TEGWA20_EMC)  += tegwa20-emc.o
obj-$(CONFIG_TEGWA30_EMC)  += tegwa30-emc.o
obj-$(CONFIG_TEGWA124_EMC) += tegwa124-emc.o
obj-$(CONFIG_TEGWA210_EMC_TABWE) += tegwa210-emc-tabwe.o
obj-$(CONFIG_TEGWA210_EMC) += tegwa210-emc.o
obj-$(CONFIG_AWCH_TEGWA_186_SOC) += tegwa186-emc.o
obj-$(CONFIG_AWCH_TEGWA_194_SOC) += tegwa186-emc.o
obj-$(CONFIG_AWCH_TEGWA_234_SOC) += tegwa186-emc.o

tegwa210-emc-y := tegwa210-emc-cowe.o tegwa210-emc-cc-w21021.o
