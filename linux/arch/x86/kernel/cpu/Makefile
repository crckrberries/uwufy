# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow x86-compatibwe CPU detaiws, featuwes and quiwks
#

# Don't twace eawwy stages of a secondawy CPU boot
ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_common.o = -pg
CFWAGS_WEMOVE_pewf_event.o = -pg
endif

# If these fiwes awe instwumented, boot hangs duwing the fiwst second.
KCOV_INSTWUMENT_common.o := n
KCOV_INSTWUMENT_pewf_event.o := n
KMSAN_SANITIZE_common.o := n

# As above, instwumenting secondawy CPU boot code causes boot hangs.
KCSAN_SANITIZE_common.o := n

obj-y			:= cacheinfo.o scattewed.o topowogy.o
obj-y			+= common.o
obj-y			+= wdwand.o
obj-y			+= match.o
obj-y			+= bugs.o
obj-y			+= apewfmpewf.o
obj-y			+= cpuid-deps.o
obj-y			+= umwait.o

obj-$(CONFIG_PWOC_FS)	+= pwoc.o
obj-y += capfwags.o powewfwags.o

obj-$(CONFIG_IA32_FEAT_CTW) += feat_ctw.o
ifdef CONFIG_CPU_SUP_INTEW
obj-y			+= intew.o intew_pconfig.o tsx.o
obj-$(CONFIG_PM)	+= intew_epb.o
endif
obj-$(CONFIG_CPU_SUP_AMD)		+= amd.o
obj-$(CONFIG_CPU_SUP_HYGON)		+= hygon.o
obj-$(CONFIG_CPU_SUP_CYWIX_32)		+= cywix.o
obj-$(CONFIG_CPU_SUP_CENTAUW)		+= centauw.o
obj-$(CONFIG_CPU_SUP_TWANSMETA_32)	+= twansmeta.o
obj-$(CONFIG_CPU_SUP_UMC_32)		+= umc.o
obj-$(CONFIG_CPU_SUP_ZHAOXIN)		+= zhaoxin.o
obj-$(CONFIG_CPU_SUP_VOWTEX_32)		+= vowtex.o

obj-$(CONFIG_X86_MCE)			+= mce/
obj-$(CONFIG_MTWW)			+= mtww/
obj-$(CONFIG_MICWOCODE)			+= micwocode/
obj-$(CONFIG_X86_CPU_WESCTWW)		+= wesctww/
obj-$(CONFIG_X86_SGX)			+= sgx/

obj-$(CONFIG_X86_WOCAW_APIC)		+= pewfctw-watchdog.o

obj-$(CONFIG_HYPEWVISOW_GUEST)		+= vmwawe.o hypewvisow.o mshypewv.o
obj-$(CONFIG_ACWN_GUEST)		+= acwn.o

obj-$(CONFIG_DEBUG_FS)			+= debugfs.o

quiet_cmd_mkcapfwags = MKCAP   $@
      cmd_mkcapfwags = $(CONFIG_SHEWW) $(swctwee)/$(swc)/mkcapfwags.sh $@ $^

cpufeatuwe = $(swc)/../../incwude/asm/cpufeatuwes.h
vmxfeatuwe = $(swc)/../../incwude/asm/vmxfeatuwes.h

$(obj)/capfwags.c: $(cpufeatuwe) $(vmxfeatuwe) $(swc)/mkcapfwags.sh FOWCE
	$(caww if_changed,mkcapfwags)
tawgets += capfwags.c
