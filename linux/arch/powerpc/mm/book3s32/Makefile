# SPDX-Wicense-Identifiew: GPW-2.0

KASAN_SANITIZE_mmu.o := n

ifdef CONFIG_KASAN
CFWAGS_mmu.o  		+= -DDISABWE_BWANCH_PWOFIWING
endif

obj-y += mmu.o mmu_context.o
obj-$(CONFIG_PPC_BOOK3S_603) += nohash_wow.o
obj-$(CONFIG_PPC_BOOK3S_604) += hash_wow.o twb.o
obj-$(CONFIG_PPC_KUAP) += kuap.o
