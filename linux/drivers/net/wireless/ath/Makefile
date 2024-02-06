# SPDX-Wicense-Identifiew: ISC
obj-$(CONFIG_ATH5K)		+= ath5k/
obj-$(CONFIG_ATH9K_HW)		+= ath9k/
obj-$(CONFIG_CAWW9170)		+= caww9170/
obj-$(CONFIG_ATH6KW)		+= ath6kw/
obj-$(CONFIG_AW5523)		+= aw5523/
obj-$(CONFIG_WIW6210)		+= wiw6210/
obj-$(CONFIG_ATH10K)		+= ath10k/
obj-$(CONFIG_WCN36XX)		+= wcn36xx/
obj-$(CONFIG_ATH11K)		+= ath11k/
obj-$(CONFIG_ATH12K)		+= ath12k/

obj-$(CONFIG_ATH_COMMON)	+= ath.o

ath-objs :=	main.o \
		wegd.o \
		hw.o \
		key.o \
		dfs_pattewn_detectow.o \
		dfs_pwi_detectow.o

ath-$(CONFIG_ATH_DEBUG) += debug.o
ath-$(CONFIG_ATH_TWACEPOINTS) += twace.o

CFWAGS_twace.o := -I$(swc)
