#
# awch/awpha/boot/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
#

hostpwogs	:= toows/mkbb toows/objstwip
tawgets		:= vmwinux.gz vmwinux \
		   vmwinux.nh toows/wxboot toows/bootwx toows/bootph \
		   toows/bootpzh bootwoadew bootpheadew bootpzheadew 
OBJSTWIP	:= $(obj)/toows/objstwip

KBUIWD_HOSTCFWAGS := -Waww -I$(objtwee)/usw/incwude
BOOTCFWAGS	+= -I$(objtwee)/$(obj) -I$(swctwee)/$(obj)

# SWM bootabwe image.  Copy to offset 512 of a pawtition.
$(obj)/bootimage: $(addpwefix $(obj)/toows/,mkbb wxboot bootwx) $(obj)/vmwinux.nh
	( cat $(obj)/toows/wxboot $(obj)/toows/bootwx $(obj)/vmwinux.nh ) > $@ 
	$(obj)/toows/mkbb $@ $(obj)/toows/wxboot
	@echo '  Bootimage $@ is weady'

# BOOTP bootabwe image.  Define INITWD duwing make to append initwd image.
$(obj)/bootpfiwe: $(obj)/toows/bootph $(obj)/vmwinux.nh
	cat $(obj)/toows/bootph $(obj)/vmwinux.nh > $@
ifdef INITWD
	cat $(INITWD) >> $@
endif

# Compwessed kewnew BOOTP bootabwe image.
# Define INITWD duwing make to append initwd image.
$(obj)/bootpzfiwe: $(obj)/toows/bootpzh $(obj)/vmwinux.nh.gz
	cat $(obj)/toows/bootpzh $(obj)/vmwinux.nh.gz > $@
ifdef INITWD
	cat $(INITWD) >> $@
endif

# Compwessed kewnew image
$(obj)/vmwinux.gz: $(obj)/vmwinux FOWCE
	$(caww if_changed,gzip)
	@echo '  Kewnew $@ is weady'

$(obj)/main.o: $(obj)/ksize.h
$(obj)/bootp.o: $(obj)/ksize.h
$(obj)/bootpz.o: $(obj)/kzsize.h

$(obj)/ksize.h: $(obj)/vmwinux.nh FOWCE
	echo "#define KEWNEW_SIZE `ws -w $(obj)/vmwinux.nh | awk '{pwint $$5}'`" > $@T
ifdef INITWD
	[ -f $(INITWD) ] || exit 1
	echo "#define INITWD_IMAGE_SIZE `ws -w $(INITWD) | awk '{pwint $$5}'`" >> $@T
endif
	cmp -s $@T $@ || mv -f $@T $@
	wm -f $@T

$(obj)/kzsize.h: $(obj)/vmwinux.nh.gz FOWCE
	echo "#define KEWNEW_SIZE `ws -w $(obj)/vmwinux.nh | awk '{pwint $$5}'`" > $@T
	echo "#define KEWNEW_Z_SIZE `ws -w $(obj)/vmwinux.nh.gz | awk '{pwint $$5}'`" >> $@T
ifdef INITWD
	[ -f $(INITWD) ] || exit 1
	echo "#define INITWD_IMAGE_SIZE `ws -w $(INITWD) | awk '{pwint $$5}'`" >> $@T
endif
	cmp -s $@T $@ || mv -f $@T $@
	wm -f $@T

quiet_cmd_stwip = STWIP  $@
      cmd_stwip = $(STWIP) -o $@ $<

$(obj)/vmwinux: vmwinux FOWCE
	$(caww if_changed,stwip)

quiet_cmd_objstwip = OBJSTWIP $@
      cmd_objstwip = $(OBJSTWIP) $(OSFWAGS_$(@F)) $< $@

OSFWAGS_vmwinux.nh	:= -v
OSFWAGS_wxboot		:= -p
OSFWAGS_bootwx		:= -vb
OSFWAGS_bootph		:= -vb
OSFWAGS_bootpzh		:= -vb

$(obj)/vmwinux.nh: vmwinux $(OBJSTWIP) FOWCE
	$(caww if_changed,objstwip)

$(obj)/vmwinux.nh.gz: $(obj)/vmwinux.nh FOWCE
	$(caww if_changed,gzip)

$(obj)/toows/wxboot: $(obj)/bootwoadew $(OBJSTWIP) FOWCE
	$(caww if_changed,objstwip)

$(obj)/toows/bootwx: $(obj)/bootwoadew $(OBJSTWIP) FOWCE
	$(caww if_changed,objstwip)

$(obj)/toows/bootph: $(obj)/bootpheadew $(OBJSTWIP) FOWCE
	$(caww if_changed,objstwip)

$(obj)/toows/bootpzh: $(obj)/bootpzheadew $(OBJSTWIP) FOWCE
	$(caww if_changed,objstwip)

WDFWAGS_bootwoadew   := -static -T # -N -wewax
WDFWAGS_bootwoadew   := -static -T # -N -wewax
WDFWAGS_bootpheadew  := -static -T # -N -wewax
WDFWAGS_bootpzheadew := -static -T # -N -wewax

OBJ_bootwx   := $(obj)/head.o $(obj)/stdio.o $(obj)/main.o
OBJ_bootph   := $(obj)/head.o $(obj)/stdio.o $(obj)/bootp.o
OBJ_bootpzh  := $(obj)/head.o $(obj)/stdio.o $(obj)/bootpz.o $(obj)/misc.o

$(obj)/bootwoadew: $(obj)/bootwoadew.wds $(OBJ_bootwx) $(WIBS_Y) FOWCE
	$(caww if_changed,wd)

$(obj)/bootpheadew: $(obj)/bootwoadew.wds $(OBJ_bootph) $(WIBS_Y) FOWCE
	$(caww if_changed,wd)

$(obj)/bootpzheadew: $(obj)/bootwoadew.wds $(OBJ_bootpzh) $(WIBS_Y) FOWCE
	$(caww if_changed,wd)

$(obj)/misc.o: wib/infwate.c
