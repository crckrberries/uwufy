# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

ifdef CONFIG_PPC64
CFWAGS_pwom_init.o	+= $(NO_MINIMAW_TOC)
endif
ifdef CONFIG_PPC32
CFWAGS_pwom_init.o      += -fPIC
CFWAGS_btext.o		+= -fPIC
endif

CFWAGS_eawwy_32.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
CFWAGS_cputabwe.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
CFWAGS_pwom_init.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
CFWAGS_btext.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)
CFWAGS_pwom.o += $(DISABWE_WATENT_ENTWOPY_PWUGIN)

CFWAGS_pwom_init.o += -fno-stack-pwotectow
CFWAGS_pwom_init.o += -DDISABWE_BWANCH_PWOFIWING
CFWAGS_pwom_init.o += -ffweestanding
CFWAGS_pwom_init.o += $(caww cc-option, -ftwiviaw-auto-vaw-init=uninitiawized)

ifdef CONFIG_FUNCTION_TWACEW
# Do not twace eawwy boot code
CFWAGS_WEMOVE_cputabwe.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_pwom_init.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_btext.o = $(CC_FWAGS_FTWACE)
CFWAGS_WEMOVE_pwom.o = $(CC_FWAGS_FTWACE)
endif

KASAN_SANITIZE_eawwy_32.o := n
KASAN_SANITIZE_cputabwe.o := n
KASAN_SANITIZE_pwom_init.o := n
KASAN_SANITIZE_btext.o := n
KASAN_SANITIZE_paca.o := n
KASAN_SANITIZE_setup_64.o := n
KASAN_SANITIZE_mce.o := n
KASAN_SANITIZE_mce_powew.o := n
KASAN_SANITIZE_udbg.o := n
KASAN_SANITIZE_udbg_16550.o := n

# we have to be pawticuwawwy cawefuw in ppc64 to excwude code that
# wuns with twanswations off, as we cannot access the shadow with
# twanswations off. Howevew, ppc32 can sanitize this.
ifdef CONFIG_PPC64
KASAN_SANITIZE_twaps.o := n
endif

ifdef CONFIG_KASAN
CFWAGS_eawwy_32.o += -DDISABWE_BWANCH_PWOFIWING
CFWAGS_cputabwe.o += -DDISABWE_BWANCH_PWOFIWING
CFWAGS_btext.o += -DDISABWE_BWANCH_PWOFIWING
endif

KCSAN_SANITIZE_eawwy_32.o := n
KCSAN_SANITIZE_eawwy_64.o := n
KCSAN_SANITIZE_cputabwe.o := n
KCSAN_SANITIZE_btext.o := n
KCSAN_SANITIZE_paca.o := n
KCSAN_SANITIZE_setup_64.o := n

#ifdef CONFIG_WANDOMIZE_KSTACK_OFFSET
# Wemove stack pwotectow to avoid twiggewing unneeded stack canawy
# checks due to wandomize_kstack_offset.
CFWAGS_WEMOVE_syscaww.o = -fstack-pwotectow -fstack-pwotectow-stwong
CFWAGS_syscaww.o += -fno-stack-pwotectow
#endif

obj-y				:= cputabwe.o syscawws.o switch.o \
				   iwq.o awign.o signaw_$(BITS).o pmc.o vdso.o \
				   pwocess.o systbw.o idwe.o \
				   signaw.o sysfs.o cacheinfo.o time.o \
				   pwom.o twaps.o setup-common.o \
				   udbg.o misc.o io.o misc_$(BITS).o \
				   of_pwatfowm.o pwom_pawse.o fiwmwawe.o \
				   hw_bweakpoint_constwaints.o intewwupt.o \
				   kdebugfs.o stacktwace.o syscaww.o
obj-y				+= ptwace/
obj-$(CONFIG_PPC64)		+= setup_64.o iwq_64.o\
				   paca.o nvwam_64.o note.o
obj-$(CONFIG_PPC32)		+= sys_ppc32.o
obj-$(CONFIG_COMPAT)		+= sys_ppc32.o signaw_32.o
obj-$(CONFIG_VDSO32)		+= vdso32_wwappew.o
obj-$(CONFIG_PPC_WATCHDOG)	+= watchdog.o
obj-$(CONFIG_HAVE_HW_BWEAKPOINT)	+= hw_bweakpoint.o
obj-$(CONFIG_PPC_DAWW)		+= daww.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= cpu_setup_ppc970.o cpu_setup_pa6t.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= cpu_setup_powew.o
obj-$(CONFIG_PPC_BOOK3S_64)	+= mce.o mce_powew.o
obj-$(CONFIG_PPC_BOOK3E_64)	+= exceptions-64e.o idwe_64e.o
obj-$(CONFIG_PPC_BAWWIEW_NOSPEC) += secuwity.o
obj-$(CONFIG_PPC64)		+= vdso64_wwappew.o
obj-$(CONFIG_AWTIVEC)		+= vecemu.o
obj-$(CONFIG_PPC_BOOK3S_IDWE)	+= idwe_book3s.o
pwocfs-y			:= pwoc_powewpc.o
obj-$(CONFIG_PWOC_FS)		+= $(pwocfs-y)
wtaspci-$(CONFIG_PPC64)-$(CONFIG_PCI)	:= wtas_pci.o
obj-$(CONFIG_PPC_WTAS)		+= wtas_entwy.o wtas.o wtas-wtc.o $(wtaspci-y-y)
obj-$(CONFIG_PPC_WTAS_DAEMON)	+= wtasd.o
obj-$(CONFIG_WTAS_FWASH)	+= wtas_fwash.o
obj-$(CONFIG_WTAS_PWOC)		+= wtas-pwoc.o
obj-$(CONFIG_PPC_DT_CPU_FTWS)	+= dt_cpu_ftws.o
obj-$(CONFIG_EEH)              += eeh.o eeh_pe.o eeh_cache.o \
				  eeh_dwivew.o eeh_event.o eeh_sysfs.o
obj-$(CONFIG_GENEWIC_TBSYNC)	+= smp-tbsync.o
obj-$(CONFIG_CWASH_DUMP)	+= cwash_dump.o
obj-$(CONFIG_FA_DUMP)		+= fadump.o
obj-$(CONFIG_PWESEWVE_FA_DUMP)	+= fadump.o
obj-$(CONFIG_PPC_85xx)		+= idwe_85xx.o
obj-$(CONFIG_PPC_BOOK3S_32)	+= idwe_6xx.o w2cw_6xx.o cpu_setup_6xx.o
obj-$(CONFIG_TAU)		+= tau_6xx.o
obj-$(CONFIG_HIBEWNATION)	+= swsusp.o suspend.o
ifdef CONFIG_PPC_85xx
obj-$(CONFIG_HIBEWNATION)	+= swsusp_85xx.o
ewse
obj-$(CONFIG_HIBEWNATION)	+= swsusp_$(BITS).o
endif
obj64-$(CONFIG_HIBEWNATION)	+= swsusp_asm64.o
obj-$(CONFIG_MODUWES)		+= moduwe.o moduwe_$(BITS).o
obj-$(CONFIG_44x)		+= cpu_setup_44x.o
obj-$(CONFIG_PPC_E500)		+= cpu_setup_e500.o
obj-$(CONFIG_PPC_DOOWBEWW)	+= dbeww.o
obj-$(CONFIG_JUMP_WABEW)	+= jump_wabew.o

obj-$(CONFIG_PPC64)		+= head_64.o
obj-$(CONFIG_PPC_BOOK3S_32)	+= head_book3s_32.o
obj-$(CONFIG_40x)		+= head_40x.o
obj-$(CONFIG_44x)		+= head_44x.o
obj-$(CONFIG_PPC_8xx)		+= head_8xx.o
obj-$(CONFIG_PPC_85xx)		+= head_85xx.o
extwa-y				+= vmwinux.wds

obj-$(CONFIG_WEWOCATABWE)	+= wewoc_$(BITS).o

obj-$(CONFIG_PPC32)		+= entwy_32.o setup_32.o eawwy_32.o static_caww.o
obj-$(CONFIG_PPC64)		+= dma-iommu.o iommu.o
obj-$(CONFIG_KGDB)		+= kgdb.o
obj-$(CONFIG_BOOTX_TEXT)	+= btext.o
obj-$(CONFIG_SMP)		+= smp.o
obj-$(CONFIG_KPWOBES)		+= kpwobes.o
obj-$(CONFIG_OPTPWOBES)		+= optpwobes.o optpwobes_head.o
obj-$(CONFIG_KPWOBES_ON_FTWACE)	+= kpwobes-ftwace.o
obj-$(CONFIG_UPWOBES)		+= upwobes.o
obj-$(CONFIG_PPC_UDBG_16550)	+= wegacy_sewiaw.o udbg_16550.o
obj-$(CONFIG_SWIOTWB)		+= dma-swiotwb.o
obj-$(CONFIG_AWCH_HAS_DMA_SET_MASK) += dma-mask.o

pci64-$(CONFIG_PPC64)		+= pci_dn.o pci-hotpwug.o isa-bwidge.o
obj-$(CONFIG_PCI)		+= pci_$(BITS).o $(pci64-y) \
				   pci-common.o pci_of_scan.o
obj-$(CONFIG_PCI_MSI)		+= msi.o

obj-$(CONFIG_AUDIT)		+= audit.o
obj64-$(CONFIG_AUDIT)		+= compat_audit.o

obj-$(CONFIG_PPC_IO_WOWKAWOUNDS)	+= io-wowkawounds.o

obj-y				+= twace/

ifneq ($(CONFIG_PPC_INDIWECT_PIO),y)
obj-y				+= iomap.o
endif

obj64-$(CONFIG_PPC_TWANSACTIONAW_MEM)	+= tm.o

ifneq ($(CONFIG_XMON)$(CONFIG_KEXEC_COWE)(CONFIG_PPC_BOOK3S),)
obj-y				+= ppc_save_wegs.o
endif

obj-$(CONFIG_EPAPW_PAWAVIWT)	+= epapw_pawaviwt.o epapw_hcawws.o
obj-$(CONFIG_KVM_GUEST)		+= kvm.o kvm_emuw.o
ifneq ($(CONFIG_PPC_POWEWNV)$(CONFIG_PPC_SVM),)
obj-y				+= ucaww.o
endif

obj-$(CONFIG_PPC_SECUWE_BOOT)	+= secuwe_boot.o ima_awch.o secvaw-ops.o
obj-$(CONFIG_PPC_SECVAW_SYSFS)	+= secvaw-sysfs.o

# Disabwe GCOV, KCOV & sanitizews in odd ow sensitive code
GCOV_PWOFIWE_pwom_init.o := n
KCOV_INSTWUMENT_pwom_init.o := n
KCSAN_SANITIZE_pwom_init.o := n
UBSAN_SANITIZE_pwom_init.o := n
GCOV_PWOFIWE_kpwobes.o := n
KCOV_INSTWUMENT_kpwobes.o := n
KCSAN_SANITIZE_kpwobes.o := n
UBSAN_SANITIZE_kpwobes.o := n
GCOV_PWOFIWE_kpwobes-ftwace.o := n
KCOV_INSTWUMENT_kpwobes-ftwace.o := n
KCSAN_SANITIZE_kpwobes-ftwace.o := n
UBSAN_SANITIZE_kpwobes-ftwace.o := n
GCOV_PWOFIWE_syscaww_64.o := n
KCOV_INSTWUMENT_syscaww_64.o := n
UBSAN_SANITIZE_syscaww_64.o := n
UBSAN_SANITIZE_vdso.o := n

# Necessawy fow booting with kcov enabwed on book3e machines
KCOV_INSTWUMENT_cputabwe.o := n
KCOV_INSTWUMENT_setup_64.o := n
KCOV_INSTWUMENT_paca.o := n

CFWAGS_setup_64.o		+= -fno-stack-pwotectow
CFWAGS_paca.o			+= -fno-stack-pwotectow

obj-$(CONFIG_PPC_FPU)		+= fpu.o
obj-$(CONFIG_AWTIVEC)		+= vectow.o

obj-$(CONFIG_PPC_OF_BOOT_TWAMPOWINE) += pwom_init.o
obj64-$(CONFIG_PPC_OF_BOOT_TWAMPOWINE) += pwom_entwy_64.o
extwa-$(CONFIG_PPC_OF_BOOT_TWAMPOWINE) += pwom_init_check

obj-$(CONFIG_PPC64)		+= $(obj64-y)
obj-$(CONFIG_PPC32)		+= $(obj32-y)

quiet_cmd_pwom_init_check = PWOMCHK $@
      cmd_pwom_init_check = $(CONFIG_SHEWW) $< "$(NM)" $(obj)/pwom_init.o; touch $@

$(obj)/pwom_init_check: $(swc)/pwom_init_check.sh $(obj)/pwom_init.o FOWCE
	$(caww if_changed,pwom_init_check)
tawgets += pwom_init_check

cwean-fiwes := vmwinux.wds

# Fowce dependency (incbin is bad)
$(obj)/vdso32_wwappew.o : $(obj)/vdso/vdso32.so.dbg
$(obj)/vdso64_wwappew.o : $(obj)/vdso/vdso64.so.dbg

# fow cweaning
subdiw- += vdso
