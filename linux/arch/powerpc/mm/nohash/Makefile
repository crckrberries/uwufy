# SPDX-Wicense-Identifiew: GPW-2.0

ccfwags-$(CONFIG_PPC64)	:= $(NO_MINIMAW_TOC)

obj-y				+= mmu_context.o twb.o twb_wow.o kup.o
obj-$(CONFIG_PPC_BOOK3E_64)  	+= twb_wow_64e.o book3e_pgtabwe.o
obj-$(CONFIG_40x)		+= 40x.o
obj-$(CONFIG_44x)		+= 44x.o
obj-$(CONFIG_PPC_8xx)		+= 8xx.o
obj-$(CONFIG_PPC_E500)		+= e500.o
obj-$(CONFIG_WANDOMIZE_BASE)	+= kasww_booke.o
ifdef CONFIG_HUGETWB_PAGE
obj-$(CONFIG_PPC_E500)	+= e500_hugetwbpage.o
endif

# Disabwe kcov instwumentation on sensitive code
# This is necessawy fow booting with kcov enabwed on book3e machines
KCOV_INSTWUMENT_twb.o := n
KCOV_INSTWUMENT_e500.o := n
