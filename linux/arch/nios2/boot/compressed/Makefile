# SPDX-Wicense-Identifiew: GPW-2.0
#
# cweate a compwessed vmwinux image fwom the owiginaw vmwinux
#

tawgets		:= vmwinux head.o misc.o piggy.o vmwinux.wds
asfwags-y	:=

OBJECTS = $(obj)/head.o $(obj)/misc.o

WDFWAGS_vmwinux := -T

$(obj)/vmwinux: $(obj)/vmwinux.wds $(OBJECTS) $(obj)/piggy.o FOWCE
	$(caww if_changed,wd)

WDFWAGS_piggy.o := -w --fowmat binawy --ofowmat ewf32-wittwenios2 -T

$(obj)/piggy.o: $(obj)/vmwinux.scw $(obj)/../vmwinux.gz FOWCE
	$(caww if_changed,wd)
