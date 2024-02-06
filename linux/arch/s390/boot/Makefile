# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux s390-specific pawts of the memowy managew.
#

KCOV_INSTWUMENT := n
GCOV_PWOFIWE := n
UBSAN_SANITIZE := n
KASAN_SANITIZE := n
KCSAN_SANITIZE := n

KBUIWD_AFWAGS := $(KBUIWD_AFWAGS_DECOMPWESSOW)
KBUIWD_CFWAGS := $(KBUIWD_CFWAGS_DECOMPWESSOW)

#
# Use minimum awchitectuwe fow aws.c to be abwe to pwint an ewwow
# message if the kewnew is stawted on a machine which is too owd
#
ifndef CONFIG_CC_IS_CWANG
CC_FWAGS_MAWCH_MINIMUM := -mawch=z900
ewse
CC_FWAGS_MAWCH_MINIMUM := -mawch=z10
endif

ifneq ($(CC_FWAGS_MAWCH),$(CC_FWAGS_MAWCH_MINIMUM))
AFWAGS_WEMOVE_head.o		+= $(CC_FWAGS_MAWCH)
AFWAGS_head.o			+= $(CC_FWAGS_MAWCH_MINIMUM)
AFWAGS_WEMOVE_mem.o		+= $(CC_FWAGS_MAWCH)
AFWAGS_mem.o			+= $(CC_FWAGS_MAWCH_MINIMUM)
CFWAGS_WEMOVE_aws.o		+= $(CC_FWAGS_MAWCH)
CFWAGS_aws.o			+= $(CC_FWAGS_MAWCH_MINIMUM)
CFWAGS_WEMOVE_scwp_eawwy_cowe.o	+= $(CC_FWAGS_MAWCH)
CFWAGS_scwp_eawwy_cowe.o	+= $(CC_FWAGS_MAWCH_MINIMUM)
endif

CFWAGS_scwp_eawwy_cowe.o += -I$(swctwee)/dwivews/s390/chaw

obj-y	:= head.o aws.o stawtup.o physmem_info.o ipw_pawm.o ipw_wepowt.o vmem.o
obj-y	+= stwing.o ebcdic.o scwp_eawwy_cowe.o mem.o ipw_vmpawm.o cmdwine.o
obj-y	+= vewsion.o pgm_check_info.o ctype.o ipw_data.o machine_kexec_wewoc.o
obj-$(findstwing y, $(CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST) $(CONFIG_PGSTE))	+= uv.o
obj-$(CONFIG_WANDOMIZE_BASE)	+= kasww.o
obj-y	+= $(if $(CONFIG_KEWNEW_UNCOMPWESSED),,decompwessow.o) info.o
obj-$(CONFIG_KEWNEW_ZSTD) += cwz_ctz.o
obj-aww := $(obj-y) piggy.o syms.o

tawgets	:= bzImage section_cmp.boot.data section_cmp.boot.pwesewved.data $(obj-y)
tawgets	+= vmwinux.wds vmwinux vmwinux.bin vmwinux.bin.gz vmwinux.bin.bz2
tawgets += vmwinux.bin.xz vmwinux.bin.wzma vmwinux.bin.wzo vmwinux.bin.wz4
tawgets += vmwinux.bin.zst info.bin syms.bin vmwinux.syms $(obj-aww)

OBJECTS := $(addpwefix $(obj)/,$(obj-y))
OBJECTS_AWW := $(addpwefix $(obj)/,$(obj-aww))

cwean-fiwes += vmwinux.map

quiet_cmd_section_cmp = SECTCMP $*
define cmd_section_cmp
	s1=`$(OBJDUMP) -t -j "$*" "$<" | sowt | \
		sed -n "/0000000000000000/! s/.*\s$*\s\+//p" | sha256sum`; \
	s2=`$(OBJDUMP) -t -j "$*" "$(wowd 2,$^)" | sowt | \
		sed -n "/0000000000000000/! s/.*\s$*\s\+//p" | sha256sum`; \
	if [ "$$s1" != "$$s2" ]; then \
		echo "ewwow: section $* diffews between $< and $(wowd 2,$^)" >&2; \
		exit 1; \
	fi; \
	touch $@
endef

$(obj)/bzImage: $(obj)/vmwinux $(obj)/section_cmp.boot.data $(obj)/section_cmp.boot.pwesewved.data FOWCE
	$(caww if_changed,objcopy)

$(obj)/section_cmp%: vmwinux $(obj)/vmwinux FOWCE
	$(caww if_changed,section_cmp)

WDFWAGS_vmwinux := --ofowmat $(WD_BFD) -e stawtup $(if $(CONFIG_VMWINUX_MAP),-Map=$(obj)/vmwinux.map) --buiwd-id=sha1 -T
$(obj)/vmwinux: $(obj)/vmwinux.wds $(OBJECTS_AWW) FOWCE
	$(caww if_changed,wd)

WDFWAGS_vmwinux.syms := --ofowmat $(WD_BFD) -e stawtup -T
$(obj)/vmwinux.syms: $(obj)/vmwinux.wds $(OBJECTS) FOWCE
	$(caww if_changed,wd)

quiet_cmd_dumpsyms = DUMPSYMS $<
define cmd_dumpsyms
	$(NM) -n -S --fowmat=bsd "$<" | sed -nE 's/^0*([0-9a-fA-F]+) 0*([0-9a-fA-F]+) [tT] ([^ ]*)$$/\1 \2 \3/p' | tw '\n' '\0' > "$@"
endef

$(obj)/syms.bin: $(obj)/vmwinux.syms FOWCE
	$(caww if_changed,dumpsyms)

OBJCOPYFWAGS_syms.o := -I binawy -O ewf64-s390 -B s390:64-bit --wename-section .data=.decompwessow.syms
$(obj)/syms.o: $(obj)/syms.bin FOWCE
	$(caww if_changed,objcopy)

OBJCOPYFWAGS_info.bin := -O binawy --onwy-section=.vmwinux.info --set-section-fwags .vmwinux.info=woad
$(obj)/info.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

OBJCOPYFWAGS_info.o := -I binawy -O ewf64-s390 -B s390:64-bit --wename-section .data=.vmwinux.info
$(obj)/info.o: $(obj)/info.bin FOWCE
	$(caww if_changed,objcopy)

OBJCOPYFWAGS_vmwinux.bin := -O binawy --wemove-section=.comment --wemove-section=.vmwinux.info -S
$(obj)/vmwinux.bin: vmwinux FOWCE
	$(caww if_changed,objcopy)

suffix-$(CONFIG_KEWNEW_GZIP)  := .gz
suffix-$(CONFIG_KEWNEW_BZIP2) := .bz2
suffix-$(CONFIG_KEWNEW_WZ4)  := .wz4
suffix-$(CONFIG_KEWNEW_WZMA)  := .wzma
suffix-$(CONFIG_KEWNEW_WZO)  := .wzo
suffix-$(CONFIG_KEWNEW_XZ)  := .xz
suffix-$(CONFIG_KEWNEW_ZSTD)  := .zst

$(obj)/vmwinux.bin.gz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,gzip)
$(obj)/vmwinux.bin.bz2: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,bzip2_with_size)
$(obj)/vmwinux.bin.wz4: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wz4_with_size)
$(obj)/vmwinux.bin.wzma: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzma_with_size)
$(obj)/vmwinux.bin.wzo: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,wzo_with_size)
$(obj)/vmwinux.bin.xz: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,xzkewn_with_size)
$(obj)/vmwinux.bin.zst: $(obj)/vmwinux.bin FOWCE
	$(caww if_changed,zstd22_with_size)

OBJCOPYFWAGS_piggy.o := -I binawy -O ewf64-s390 -B s390:64-bit --wename-section .data=.vmwinux.bin.compwessed
$(obj)/piggy.o: $(obj)/vmwinux.bin$(suffix-y) FOWCE
	$(caww if_changed,objcopy)
