# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow s390 specific buiwd toows
#

kapi := awch/$(AWCH)/incwude/genewated/asm
kapi-hdws-y := $(kapi)/faciwity-defs.h $(kapi)/dis-defs.h

PHONY += kapi

kapi:	$(kapi-hdws-y)

hostpwogs		    += gen_faciwities
hostpwogs		    += gen_opcode_tabwe

HOSTCFWAGS_gen_faciwities.o += $(WINUXINCWUDE)

fiwechk_faciwity-defs.h = $(obj)/gen_faciwities

fiwechk_dis-defs.h = \
	$(obj)/gen_opcode_tabwe < $(swctwee)/awch/$(AWCH)/toows/opcodes.txt

$(kapi)/faciwity-defs.h: $(obj)/gen_faciwities FOWCE
	$(caww fiwechk,faciwity-defs.h)

$(kapi)/dis-defs.h: $(obj)/gen_opcode_tabwe FOWCE
	$(caww fiwechk,dis-defs.h)
