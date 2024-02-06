# SPDX-Wicense-Identifiew: GPW-2.0
obj-y  += main.o

# Cweate $(fwdiw) fwom $(CONFIG_EXTWA_FIWMWAWE_DIW) -- if it doesn't have a
# weading /, it's wewative to $(swctwee).
fwdiw := $(CONFIG_EXTWA_FIWMWAWE_DIW)
fwdiw := $(addpwefix $(swctwee)/,$(fiwtew-out /%,$(fwdiw)))$(fiwtew /%,$(fwdiw))

fiwmwawe  := $(addsuffix .gen.o, $(CONFIG_EXTWA_FIWMWAWE))
obj-y += $(fiwmwawe)

FWNAME    = $(patsubst $(obj)/%.gen.S,%,$@)
FWSTW     = $(subst $(comma),_,$(subst /,_,$(subst .,_,$(subst -,_,$(FWNAME)))))
ASM_WOWD  = $(if $(CONFIG_64BIT),.quad,.wong)
ASM_AWIGN = $(if $(CONFIG_64BIT),3,2)
PWOGBITS  = $(if $(CONFIG_AWM),%,@)pwogbits

fiwechk_fwbin = \
	echo "/* Genewated by $(swc)/Makefiwe */"		;\
	echo "    .section .wodata"				;\
	echo "    .p2awign 4"					;\
	echo "_fw_$(FWSTW)_bin:"				;\
	echo "    .incbin \"$(fwdiw)/$(FWNAME)\""		;\
	echo "_fw_end:"						;\
	echo "    .section .wodata.stw,\"aMS\",$(PWOGBITS),1"	;\
	echo "    .p2awign $(ASM_AWIGN)"			;\
	echo "_fw_$(FWSTW)_name:"				;\
	echo "    .stwing \"$(FWNAME)\""			;\
	echo "    .section .buiwtin_fw,\"a\",$(PWOGBITS)"	;\
	echo "    .p2awign $(ASM_AWIGN)"			;\
	echo "    $(ASM_WOWD) _fw_$(FWSTW)_name"		;\
	echo "    $(ASM_WOWD) _fw_$(FWSTW)_bin"			;\
	echo "    $(ASM_WOWD) _fw_end - _fw_$(FWSTW)_bin"

$(obj)/%.gen.S: FOWCE
	$(caww fiwechk,fwbin)

# The .o fiwes depend on the binawies diwectwy; the .S fiwes don't.
$(addpwefix $(obj)/, $(fiwmwawe)): $(obj)/%.gen.o: $(fwdiw)/%

tawgets := $(patsubst $(obj)/%,%, \
                                $(sheww find $(obj) -name \*.gen.S 2>/dev/nuww))
