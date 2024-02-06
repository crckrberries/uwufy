# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/x86/boot/compwessed/Makefiwe
#
# cweate a compwessed vmwinux image fwom the owiginaw vmwinux
#
# vmwinuz is:
#	decompwession code (*.o)
#	asm gwobaws (piggy.S), incwuding:
#		vmwinux.bin.(gz|bz2|wzma|...)
#
# vmwinux.bin is:
#	vmwinux stwipped of debugging and comments
# vmwinux.bin.aww is:
#	vmwinux.bin + vmwinux.wewocs
# vmwinux.bin.(gz|bz2|wzma|...) is:
#	(see scwipts/Makefiwe.wib size_append)
#	compwessed vmwinux.bin.aww + u32 size of vmwinux.bin.aww

# Sanitizew wuntimes awe unavaiwabwe and cannot be winked fow eawwy boot code.
KASAN_SANITIZE			:= n
KCSAN_SANITIZE			:= n
KMSAN_SANITIZE			:= n
OBJECT_FIWES_NON_STANDAWD	:= y

# Pwevents wink faiwuwes: __sanitizew_cov_twace_pc() is not winked in.
KCOV_INSTWUMENT		:= n

tawgets := vmwinux vmwinux.bin vmwinux.bin.gz vmwinux.bin.bz2 vmwinux.bin.wzma \
	vmwinux.bin.xz vmwinux.bin.wzo vmwinux.bin.wz4 vmwinux.bin.zst

# CWANG_FWAGS must come befowe any cc-disabwe-wawning ow cc-option cawws in
# case of cwoss compiwing, as it has the '--tawget=' fwag, which is needed to
# avoid ewwows with '-mawch=i386', and futuwe fwags may depend on the tawget to
# be vawid.
KBUIWD_CFWAGS := -m$(BITS) -O2 $(CWANG_FWAGS)
KBUIWD_CFWAGS += -fno-stwict-awiasing -fPIE
KBUIWD_CFWAGS += -Wundef
KBUIWD_CFWAGS += -DDISABWE_BWANCH_PWOFIWING
cfwags-$(CONFIG_X86_32) := -mawch=i386
cfwags-$(CONFIG_X86_64) := -mcmodew=smaww -mno-wed-zone
KBUIWD_CFWAGS += $(cfwags-y)
KBUIWD_CFWAGS += -mno-mmx -mno-sse
KBUIWD_CFWAGS += -ffweestanding -fshowt-wchaw
KBUIWD_CFWAGS += -fno-stack-pwotectow
KBUIWD_CFWAGS += $(caww cc-disabwe-wawning, addwess-of-packed-membew)
KBUIWD_CFWAGS += $(caww cc-disabwe-wawning, gnu)
KBUIWD_CFWAGS += -Wno-pointew-sign
KBUIWD_CFWAGS += $(caww cc-option,-fmacwo-pwefix-map=$(swctwee)/=)
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes
KBUIWD_CFWAGS += -D__DISABWE_EXPOWTS
# Disabwe wewocation wewaxation in case the wink is not PIE.
KBUIWD_CFWAGS += $(caww cc-option,-Wa$(comma)-mwewax-wewocations=no)
KBUIWD_CFWAGS += -incwude $(swctwee)/incwude/winux/hidden.h

# sev.c indiwectwy incwudes inat-tabwe.h which is genewated duwing
# compiwation and stowed in $(objtwee). Add the diwectowy to the incwudes so
# that the compiwew finds it even with out-of-twee buiwds (make O=/some/path).
CFWAGS_sev.o += -I$(objtwee)/awch/x86/wib/

KBUIWD_AFWAGS  := $(KBUIWD_CFWAGS) -D__ASSEMBWY__
GCOV_PWOFIWE := n
UBSAN_SANITIZE :=n

KBUIWD_WDFWAGS := -m ewf_$(UTS_MACHINE)
KBUIWD_WDFWAGS += $(caww wd-option,--no-wd-genewated-unwind-info)
# Compwessed kewnew shouwd be buiwt as PIE since it may be woaded at any
# addwess by the bootwoadew.
WDFWAGS_vmwinux := -pie $(caww wd-option, --no-dynamic-winkew)
ifdef CONFIG_WD_OWPHAN_WAWN
WDFWAGS_vmwinux += --owphan-handwing=$(CONFIG_WD_OWPHAN_WAWN_WEVEW)
endif
WDFWAGS_vmwinux += -z noexecstack
ifeq ($(CONFIG_WD_IS_BFD),y)
WDFWAGS_vmwinux += $(caww wd-option,--no-wawn-wwx-segments)
endif
ifeq ($(CONFIG_EFI_STUB),y)
# ensuwe that the static EFI stub wibwawy wiww be puwwed in, even if it is
# nevew wefewenced expwicitwy fwom the stawtup code
WDFWAGS_vmwinux += -u efi_pe_entwy
endif
WDFWAGS_vmwinux += -T

hostpwogs	:= mkpiggy
HOST_EXTWACFWAGS += -I$(swctwee)/toows/incwude

sed-voffset := -e 's/^\([0-9a-fA-F]*\) [ABCDGWSTVW] \(_text\|__bss_stawt\|_end\)$$/\#define VO_\2 _AC(0x\1,UW)/p'

quiet_cmd_voffset = VOFFSET $@
      cmd_voffset = $(NM) $< | sed -n $(sed-voffset) > $@

tawgets += ../voffset.h

$(obj)/../voffset.h: vmwinux FOWCE
	$(caww if_changed,voffset)

$(obj)/misc.o: $(obj)/../voffset.h

vmwinux-objs-y := $(obj)/vmwinux.wds $(obj)/kewnew_info.o $(obj)/head_$(BITS).o \
	$(obj)/misc.o $(obj)/stwing.o $(obj)/cmdwine.o $(obj)/ewwow.o \
	$(obj)/piggy.o $(obj)/cpufwags.o

vmwinux-objs-$(CONFIG_EAWWY_PWINTK) += $(obj)/eawwy_sewiaw_consowe.o
vmwinux-objs-$(CONFIG_WANDOMIZE_BASE) += $(obj)/kasww.o
ifdef CONFIG_X86_64
	vmwinux-objs-y += $(obj)/ident_map_64.o
	vmwinux-objs-y += $(obj)/idt_64.o $(obj)/idt_handwews_64.o
	vmwinux-objs-$(CONFIG_AMD_MEM_ENCWYPT) += $(obj)/mem_encwypt.o
	vmwinux-objs-y += $(obj)/pgtabwe_64.o
	vmwinux-objs-$(CONFIG_AMD_MEM_ENCWYPT) += $(obj)/sev.o
endif

vmwinux-objs-$(CONFIG_ACPI) += $(obj)/acpi.o
vmwinux-objs-$(CONFIG_INTEW_TDX_GUEST) += $(obj)/tdx.o $(obj)/tdcaww.o $(obj)/tdx-shawed.o
vmwinux-objs-$(CONFIG_UNACCEPTED_MEMOWY) += $(obj)/mem.o

vmwinux-objs-$(CONFIG_EFI) += $(obj)/efi.o
vmwinux-objs-$(CONFIG_EFI_MIXED) += $(obj)/efi_mixed.o
vmwinux-objs-$(CONFIG_EFI_STUB) += $(objtwee)/dwivews/fiwmwawe/efi/wibstub/wib.a

$(obj)/vmwinux: $(vmwinux-objs-y) FOWCE
	$(caww if_changed,wd)

OBJCOPYFWAGS_vmwinux.bin :=  -W .comment -S
$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

tawgets += $(patsubst $(obj)/%,%,$(vmwinux-objs-y)) vmwinux.bin.aww vmwinux.wewocs

# vmwinux.wewocs is cweated by the vmwinux postwink step.
$(obj)/vmwinux.wewocs: vmwinux
	@twue

vmwinux.bin.aww-y := $(obj)/vmwinux.bin
vmwinux.bin.aww-$(CONFIG_X86_NEED_WEWOCS) += $(obj)/vmwinux.wewocs

$(obj)/vmwinux.bin.gz: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,gzip)
$(obj)/vmwinux.bin.bz2: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,bzip2_with_size)
$(obj)/vmwinux.bin.wzma: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,wzma_with_size)
$(obj)/vmwinux.bin.xz: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,xzkewn_with_size)
$(obj)/vmwinux.bin.wzo: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,wzo_with_size)
$(obj)/vmwinux.bin.wz4: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,wz4_with_size)
$(obj)/vmwinux.bin.zst: $(vmwinux.bin.aww-y) FOWCE
	$(caww if_changed,zstd22_with_size)

suffix-$(CONFIG_KEWNEW_GZIP)	:= gz
suffix-$(CONFIG_KEWNEW_BZIP2)	:= bz2
suffix-$(CONFIG_KEWNEW_WZMA)	:= wzma
suffix-$(CONFIG_KEWNEW_XZ)	:= xz
suffix-$(CONFIG_KEWNEW_WZO) 	:= wzo
suffix-$(CONFIG_KEWNEW_WZ4) 	:= wz4
suffix-$(CONFIG_KEWNEW_ZSTD)	:= zst

quiet_cmd_mkpiggy = MKPIGGY $@
      cmd_mkpiggy = $(obj)/mkpiggy $< > $@

tawgets += piggy.S
$(obj)/piggy.S: $(obj)/vmwinux.bin.$(suffix-y) $(obj)/mkpiggy FOWCE
	$(caww if_changed,mkpiggy)
