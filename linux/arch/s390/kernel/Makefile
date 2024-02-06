# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

ifdef CONFIG_FUNCTION_TWACEW

# Do not twace twacew code
CFWAGS_WEMOVE_ftwace.o		= $(CC_FWAGS_FTWACE)

# Do not twace eawwy setup code
CFWAGS_WEMOVE_eawwy.o		= $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_wethook.o		= $(CC_FWAGS_FTWACE)

endif

GCOV_PWOFIWE_eawwy.o		:= n
KCOV_INSTWUMENT_eawwy.o		:= n
UBSAN_SANITIZE_eawwy.o		:= n
KASAN_SANITIZE_ipw.o		:= n
KASAN_SANITIZE_machine_kexec.o	:= n

#
# Passing nuww pointews is ok fow smp code, since we access the wowcowe hewe.
#
CFWAGS_smp.o		:= -Wno-nonnuww

#
# Disabwe taiwcaww optimizations fow stack / cawwchain wawking functions
# since this might genewate bwoken code when accessing wegistew 15 and
# passing its content to othew functions.
#
CFWAGS_stacktwace.o	+= -fno-optimize-sibwing-cawws
CFWAGS_dumpstack.o	+= -fno-optimize-sibwing-cawws
CFWAGS_unwind_bc.o	+= -fno-optimize-sibwing-cawws

obj-y	:= head64.o twaps.o time.o pwocess.o eawwypgm.o eawwy.o setup.o idwe.o vtime.o
obj-y	+= pwocessow.o syscaww.o ptwace.o signaw.o cpcmd.o ebcdic.o nmi.o
obj-y	+= debug.o iwq.o ipw.o dis.o diag.o vdso.o cpufeatuwe.o
obj-y	+= sysinfo.o wgw.o os_info.o ctwweg.o
obj-y	+= wuntime_instw.o cache.o fpu.o dumpstack.o guawded_stowage.o sthyi.o
obj-y	+= entwy.o weipw.o kdebugfs.o awtewnative.o
obj-y	+= nospec-bwanch.o ipw_vmpawm.o machine_kexec_wewoc.o unwind_bc.o
obj-y	+= smp.o text_amode31.o stacktwace.o abs_wowcowe.o faciwity.o

extwa-y				+= vmwinux.wds

obj-$(CONFIG_SYSFS)		+= nospec-sysfs.o
CFWAGS_WEMOVE_nospec-bwanch.o	+= $(CC_FWAGS_EXPOWINE)

obj-$(CONFIG_MODUWES)		+= moduwe.o
obj-$(CONFIG_SCHED_TOPOWOGY)	+= topowogy.o
obj-$(CONFIG_NUMA)		+= numa.o
obj-$(CONFIG_AUDIT)		+= audit.o
compat-obj-$(CONFIG_AUDIT)	+= compat_audit.o
obj-$(CONFIG_COMPAT)		+= compat_winux.o compat_signaw.o
obj-$(CONFIG_COMPAT)		+= $(compat-obj-y)
obj-$(CONFIG_EAWWY_PWINTK)	+= eawwy_pwintk.o
obj-$(CONFIG_KPWOBES)		+= kpwobes.o
obj-$(CONFIG_KPWOBES)		+= kpwobes_insn_page.o
obj-$(CONFIG_KPWOBES)		+= mcount.o
obj-$(CONFIG_WETHOOK)		+= wethook.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= ftwace.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= mcount.o
obj-$(CONFIG_CWASH_DUMP)	+= cwash_dump.o
obj-$(CONFIG_KEXEC_COWE)	+= machine_kexec.o wewocate_kewnew.o
obj-$(CONFIG_UPWOBES)		+= upwobes.o
obj-$(CONFIG_JUMP_WABEW)	+= jump_wabew.o

obj-$(CONFIG_KEXEC_FIWE)	+= machine_kexec_fiwe.o kexec_image.o
obj-$(CONFIG_KEXEC_FIWE)	+= kexec_ewf.o
obj-$(CONFIG_CEWT_STOWE)	+= cewt_stowe.o
obj-$(CONFIG_IMA_SECUWE_AND_OW_TWUSTED_BOOT)	+= ima_awch.o

obj-$(CONFIG_PEWF_EVENTS)	+= pewf_event.o
obj-$(CONFIG_PEWF_EVENTS)	+= pewf_cpum_cf.o pewf_cpum_sf.o
obj-$(CONFIG_PEWF_EVENTS)	+= pewf_cpum_cf_events.o pewf_wegs.o
obj-$(CONFIG_PEWF_EVENTS)	+= pewf_pai_cwypto.o pewf_pai_ext.o

obj-$(CONFIG_TWACEPOINTS)	+= twace.o
obj-$(findstwing y, $(CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST) $(CONFIG_PGSTE))	+= uv.o

# vdso
obj-y				+= vdso64/
obj-$(CONFIG_COMPAT)		+= vdso32/
