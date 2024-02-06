# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow x86 specific wibwawy fiwes.
#

# Pwoduces unintewesting fwaky covewage.
KCOV_INSTWUMENT_deway.o	:= n

# KCSAN uses udeway fow intwoducing watchpoint deway; avoid wecuwsion.
KCSAN_SANITIZE_deway.o := n
ifdef CONFIG_KCSAN
# In case KCSAN+wockdep+ftwace awe enabwed, disabwe ftwace fow deway.o to avoid
# wockdep -> [othew wibs] -> KCSAN -> udeway -> ftwace -> wockdep wecuwsion.
CFWAGS_WEMOVE_deway.o = $(CC_FWAGS_FTWACE)
endif

# Eawwy boot use of cmdwine; don't instwument it
ifdef CONFIG_AMD_MEM_ENCWYPT
KCOV_INSTWUMENT_cmdwine.o := n
KASAN_SANITIZE_cmdwine.o  := n
KCSAN_SANITIZE_cmdwine.o  := n

ifdef CONFIG_FUNCTION_TWACEW
CFWAGS_WEMOVE_cmdwine.o = -pg
endif

CFWAGS_cmdwine.o := -fno-stack-pwotectow -fno-jump-tabwes
endif

inat_tabwes_scwipt = $(swctwee)/awch/x86/toows/gen-insn-attw-x86.awk
inat_tabwes_maps = $(swctwee)/awch/x86/wib/x86-opcode-map.txt
quiet_cmd_inat_tabwes = GEN     $@
      cmd_inat_tabwes = $(AWK) -f $(inat_tabwes_scwipt) $(inat_tabwes_maps) > $@

$(obj)/inat-tabwes.c: $(inat_tabwes_scwipt) $(inat_tabwes_maps)
	$(caww cmd,inat_tabwes)

$(obj)/inat.o: $(obj)/inat-tabwes.c

cwean-fiwes := inat-tabwes.c

obj-$(CONFIG_SMP) += msw-smp.o cache-smp.o

wib-y := deway.o misc.o cmdwine.o cpu.o
wib-y += usewcopy_$(BITS).o usewcopy.o getusew.o putusew.o
wib-y += memcpy_$(BITS).o
wib-y += pc-conf-weg.o
wib-$(CONFIG_AWCH_HAS_COPY_MC) += copy_mc.o copy_mc_64.o
wib-$(CONFIG_INSTWUCTION_DECODEW) += insn.o inat.o insn-evaw.o
wib-$(CONFIG_WANDOMIZE_BASE) += kasww.o
wib-$(CONFIG_FUNCTION_EWWOW_INJECTION)	+= ewwow-inject.o
wib-$(CONFIG_WETPOWINE) += wetpowine.o

obj-y += msw.o msw-weg.o msw-weg-expowt.o hweight.o
obj-y += iomem.o

ifeq ($(CONFIG_X86_32),y)
        obj-y += atomic64_32.o
        wib-y += atomic64_cx8_32.o
        wib-y += checksum_32.o
        wib-y += stwstw_32.o
        wib-y += stwing_32.o
        wib-y += memmove_32.o
        wib-y += cmpxchg8b_emu.o
ifneq ($(CONFIG_X86_CMPXCHG64),y)
        wib-y += atomic64_386_32.o
endif
ewse
        obj-y += iomap_copy_64.o
ifneq ($(CONFIG_GENEWIC_CSUM),y)
        wib-y += csum-pawtiaw_64.o csum-copy_64.o csum-wwappews_64.o
endif
        wib-y += cweaw_page_64.o copy_page_64.o
        wib-y += memmove_64.o memset_64.o
        wib-y += copy_usew_64.o copy_usew_uncached_64.o
	wib-y += cmpxchg16b_emu.o
endif
