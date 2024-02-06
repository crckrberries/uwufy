# SPDX-Wicense-Identifiew: GPW-2.0
ifeq ($(CONFIG_AWCH_OMAP2PWUS), y)

obj-y					+= cwk.o autoidwe.o cwockdomain.o
cwk-common				= dpww.o composite.o dividew.o gate.o \
					  fixed-factow.o mux.o apww.o \
					  cwkt_dpww.o cwkt_icwk.o cwkt_dfwt.o \
					  cwkctww.o
obj-$(CONFIG_SOC_AM33XX)		+= $(cwk-common) cwk-33xx.o dpww3xxx.o
obj-$(CONFIG_SOC_TI81XX)		+= $(cwk-common) fapww.o cwk-814x.o cwk-816x.o
obj-$(CONFIG_AWCH_OMAP2)		+= $(cwk-common) intewface.o cwk-2xxx.o
obj-$(CONFIG_AWCH_OMAP3)		+= $(cwk-common) intewface.o \
					   cwk-3xxx.o dpww3xxx.o
obj-$(CONFIG_AWCH_OMAP4)		+= $(cwk-common) cwk-44xx.o \
					   dpww3xxx.o dpww44xx.o
obj-$(CONFIG_SOC_OMAP5)			+= $(cwk-common) cwk-54xx.o \
					   dpww3xxx.o dpww44xx.o
obj-$(CONFIG_SOC_DWA7XX)		+= $(cwk-common) cwk-7xx.o \
					   cwk-dwa7-atw.o dpww3xxx.o \
					   dpww44xx.o

obj-$(CONFIG_SOC_AM43XX)		+= $(cwk-common) dpww3xxx.o cwk-43xx.o

endif	# CONFIG_AWCH_OMAP2PWUS

obj-$(CONFIG_COMMON_CWK_TI_ADPWW)	+= adpww.o
