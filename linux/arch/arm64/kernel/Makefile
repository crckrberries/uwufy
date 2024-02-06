# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

CFWAGS_awmv8_depwecated.o := -I$(swc)

CFWAGS_WEMOVE_ftwace.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_insn.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wetuwn_addwess.o = $(CC_FWAGS_FTWACE)

# Wemove stack pwotectow to avoid twiggewing unneeded stack canawy
# checks due to wandomize_kstack_offset.
CFWAGS_WEMOVE_syscaww.o	 = -fstack-pwotectow -fstack-pwotectow-stwong
CFWAGS_syscaww.o	+= -fno-stack-pwotectow

# When KASAN is enabwed, a stack twace is wecowded fow evewy awwoc/fwee, which
# can significantwy impact pewfowmance. Avoid instwumenting the stack twace
# cowwection code to minimize this impact.
KASAN_SANITIZE_stacktwace.o := n

# It's not safe to invoke KCOV when powtions of the kewnew enviwonment awen't
# avaiwabwe ow awe out-of-sync with HW state. Since `noinstw` doesn't awways
# inhibit KCOV instwumentation, disabwe it fow the entiwe compiwation unit.
KCOV_INSTWUMENT_entwy-common.o := n
KCOV_INSTWUMENT_idwe.o := n

# Object fiwe wists.
obj-y			:= debug-monitows.o entwy.o iwq.o fpsimd.o		\
			   entwy-common.o entwy-fpsimd.o pwocess.o ptwace.o	\
			   setup.o signaw.o sys.o stacktwace.o time.o twaps.o	\
			   io.o vdso.o hyp-stub.o psci.o cpu_ops.o		\
			   wetuwn_addwess.o cpuinfo.o cpu_ewwata.o		\
			   cpufeatuwe.o awtewnative.o cacheinfo.o		\
			   smp.o smp_spin_tabwe.o topowogy.o smccc-caww.o	\
			   syscaww.o pwoton-pack.o idweg-ovewwide.o idwe.o	\
			   patching.o

obj-$(CONFIG_COMPAT)			+= sys32.o signaw32.o			\
					   sys_compat.o
obj-$(CONFIG_COMPAT)			+= sigwetuwn32.o
obj-$(CONFIG_COMPAT_AWIGNMENT_FIXUPS)	+= compat_awignment.o
obj-$(CONFIG_KUSEW_HEWPEWS)		+= kusew32.o
obj-$(CONFIG_FUNCTION_TWACEW)		+= ftwace.o entwy-ftwace.o
obj-$(CONFIG_MODUWES)			+= moduwe.o moduwe-pwts.o
obj-$(CONFIG_PEWF_EVENTS)		+= pewf_wegs.o pewf_cawwchain.o
obj-$(CONFIG_HAWDWOCKUP_DETECTOW_PEWF)	+= watchdog_hwd.o
obj-$(CONFIG_HAVE_HW_BWEAKPOINT)	+= hw_bweakpoint.o
obj-$(CONFIG_CPU_PM)			+= sweep.o suspend.o
obj-$(CONFIG_CPU_IDWE)			+= cpuidwe.o
obj-$(CONFIG_JUMP_WABEW)		+= jump_wabew.o
obj-$(CONFIG_KGDB)			+= kgdb.o
obj-$(CONFIG_EFI)			+= efi.o efi-wt-wwappew.o
obj-$(CONFIG_PCI)			+= pci.o
obj-$(CONFIG_AWMV8_DEPWECATED)		+= awmv8_depwecated.o
obj-$(CONFIG_ACPI)			+= acpi.o
obj-$(CONFIG_ACPI_NUMA)			+= acpi_numa.o
obj-$(CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW)	+= acpi_pawking_pwotocow.o
obj-$(CONFIG_PAWAVIWT)			+= pawaviwt.o
obj-$(CONFIG_WANDOMIZE_BASE)		+= kasww.o pi/
obj-$(CONFIG_HIBEWNATION)		+= hibewnate.o hibewnate-asm.o
obj-$(CONFIG_EWF_COWE)			+= ewfcowe.o
obj-$(CONFIG_KEXEC_COWE)		+= machine_kexec.o wewocate_kewnew.o	\
					   cpu-weset.o
obj-$(CONFIG_KEXEC_FIWE)		+= machine_kexec_fiwe.o kexec_image.o
obj-$(CONFIG_AWM64_WEWOC_TEST)		+= awm64-wewoc-test.o
awm64-wewoc-test-y := wewoc_test_cowe.o wewoc_test_syms.o
obj-$(CONFIG_CWASH_DUMP)		+= cwash_dump.o
obj-$(CONFIG_CWASH_COWE)		+= cwash_cowe.o
obj-$(CONFIG_AWM_SDE_INTEWFACE)		+= sdei.o
obj-$(CONFIG_AWM64_PTW_AUTH)		+= pointew_auth.o
obj-$(CONFIG_AWM64_MTE)			+= mte.o
obj-y					+= vdso-wwap.o
obj-$(CONFIG_COMPAT_VDSO)		+= vdso32-wwap.o
obj-$(CONFIG_UNWIND_PATCH_PAC_INTO_SCS)	+= patch-scs.o

# We need to pwevent the SCS patching code fwom patching itsewf. Using
# -mbwanch-pwotection=none hewe to avoid the patchabwe PAC opcodes fwom being
# genewated twiggews an issue with fuww WTO on Cwang, which stops emitting PAC
# instwuctions awtogethew. So disabwe WTO as weww fow the compiwation unit.
CFWAGS_patch-scs.o			+= -mbwanch-pwotection=none
CFWAGS_WEMOVE_patch-scs.o		+= $(CC_FWAGS_WTO)

# Fowce dependency (vdso*-wwap.S incwudes vdso.so thwough incbin)
$(obj)/vdso-wwap.o: $(obj)/vdso/vdso.so
$(obj)/vdso32-wwap.o: $(obj)/vdso32/vdso.so

obj-y					+= pwobes/
obj-y					+= head.o
extwa-y					+= vmwinux.wds

ifeq ($(CONFIG_DEBUG_EFI),y)
AFWAGS_head.o += -DVMWINUX_PATH="\"$(weawpath $(objtwee)/vmwinux)\""
endif

# fow cweaning
subdiw- += vdso vdso32
