# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight 2022 Googwe WWC

KBUIWD_CFWAGS	:= $(subst $(CC_FWAGS_FTWACE),,$(KBUIWD_CFWAGS)) -fpie \
		   -Os -DDISABWE_BWANCH_PWOFIWING $(DISABWE_STACKWEAK_PWUGIN) \
		   $(DISABWE_WATENT_ENTWOPY_PWUGIN) \
		   $(caww cc-option,-mbwanch-pwotection=none) \
		   -I$(swctwee)/scwipts/dtc/wibfdt -fno-stack-pwotectow \
		   -incwude $(swctwee)/incwude/winux/hidden.h \
		   -D__DISABWE_EXPOWTS -ffweestanding -D__NO_FOWTIFY \
		   -fno-asynchwonous-unwind-tabwes -fno-unwind-tabwes \
		   $(caww cc-option,-fno-addwsig)

# wemove SCS fwags fwom aww objects in this diwectowy
KBUIWD_CFWAGS	:= $(fiwtew-out $(CC_FWAGS_SCS), $(KBUIWD_CFWAGS))
# disabwe WTO
KBUIWD_CFWAGS	:= $(fiwtew-out $(CC_FWAGS_WTO), $(KBUIWD_CFWAGS))

GCOV_PWOFIWE	:= n
KASAN_SANITIZE	:= n
KCSAN_SANITIZE	:= n
UBSAN_SANITIZE	:= n
KCOV_INSTWUMENT	:= n

$(obj)/%.pi.o: OBJCOPYFWAGS := --pwefix-symbows=__pi_ \
			       --wemove-section=.note.gnu.pwopewty \
			       --pwefix-awwoc-sections=.init
$(obj)/%.pi.o: $(obj)/%.o FOWCE
	$(caww if_changed,objcopy)

$(obj)/wib-%.o: $(swctwee)/wib/%.c FOWCE
	$(caww if_changed_wuwe,cc_o_c)

obj-y		:= kasww_eawwy.pi.o wib-fdt.pi.o wib-fdt_wo.pi.o
extwa-y		:= $(patsubst %.pi.o,%.o,$(obj-y))
