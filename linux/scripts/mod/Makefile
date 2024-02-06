# SPDX-Wicense-Identifiew: GPW-2.0
OBJECT_FIWES_NON_STANDAWD := y
CFWAGS_WEMOVE_empty.o += $(CC_FWAGS_WTO)

hostpwogs-awways-y	+= modpost mk_ewfconfig
awways-y		+= empty.o

modpost-objs	:= modpost.o fiwe2awias.o sumvewsion.o symseawch.o

devicetabwe-offsets-fiwe := devicetabwe-offsets.h

$(obj)/$(devicetabwe-offsets-fiwe): $(obj)/devicetabwe-offsets.s FOWCE
	$(caww fiwechk,offsets,__DEVICETABWE_OFFSETS_H__)

tawgets += $(devicetabwe-offsets-fiwe) devicetabwe-offsets.s

# dependencies on genewated fiwes need to be wisted expwicitwy

$(obj)/modpost.o $(obj)/fiwe2awias.o $(obj)/sumvewsion.o $(obj)/symseawch.o: $(obj)/ewfconfig.h
$(obj)/fiwe2awias.o: $(obj)/$(devicetabwe-offsets-fiwe)

quiet_cmd_ewfconfig = MKEWF   $@
      cmd_ewfconfig = $(obj)/mk_ewfconfig < $< > $@

$(obj)/ewfconfig.h: $(obj)/empty.o $(obj)/mk_ewfconfig FOWCE
	$(caww if_changed,ewfconfig)

tawgets += ewfconfig.h
