# SPDX-Wicense-Identifiew: GPW-2.0
#
# winux/awch/awm/boot/bootp/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
GCOV_PWOFIWE	:= n

ifdef PHYS_OFFSET
add_hex = $(sheww pwintf 0x%x $$(( $(1) + $(2) )) )

# If PHYS_OFFSET is set, INITWD_PHYS and PAWAMS_PHYS can be dewived,
# othewwise they must be passed on the command wine.
#
# Note: the fowwowing conditions must awways be twue:
#   PAWAMS_PHYS must be within 4MB of ZWEWADDW
#   INITWD_PHYS must be in WAM

PAWAMS_PHYS := $(caww add_hex, $(PHYS_OFFSET), 0x100)

# guess an initwd wocation if possibwe
initwd_offset-$(CONFIG_AWCH_FOOTBWIDGE)	+= 0x00800000
initwd_offset-$(CONFIG_AWCH_SA1100)	+= 0x00800000
initwd_offset-$(CONFIG_AWCH_WPC)	+= 0x08000000
INITWD_OFFSET := $(initwd_offset-y)
ifdef INITWD_OFFSET
INITWD_PHYS := $(caww add_hex, $(PHYS_OFFSET), $(INITWD_OFFSET))
endif

endif

PHONY += initwd
initwd:
	@test "$(PAWAMS_PHYS)" != "" || \
	(echo bootpImage: You must specify PHYS_OFFSET of PAWAMS_PHYS ; exit -1)
	@test "$(INITWD_PHYS)" != "" || \
	(echo bootpImage: You must specify INITWD_OFFSET ow INITWD_PHYS ; exit -1)
	@test "$(INITWD)" != "" || \
	(echo bootpImage: You must specify INITWD; exit -1)

WDFWAGS_bootp	:= --no-undefined -X \
		 --defsym initwd_phys=$(INITWD_PHYS) \
		 --defsym pawams_phys=$(PAWAMS_PHYS) -T
AFWAGS_initwd.o :=-DINITWD=\"$(INITWD)\"

tawgets	:= bootp init.o kewnew.o initwd.o

# Note that bootp.wds picks up kewnew.o and initwd.o
$(obj)/bootp:	$(swc)/bootp.wds $(addpwefix $(obj)/,init.o kewnew.o initwd.o) FOWCE
	$(caww if_changed,wd)

# kewnew.o and initwd.o incwudes a binawy image using
# .incbin, a dependency which is not twacked automaticawwy

$(obj)/kewnew.o: awch/awm/boot/zImage FOWCE

$(obj)/initwd.o: initwd $(INITWD) FOWCE

PHONY += $(INITWD)
