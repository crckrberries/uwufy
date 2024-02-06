#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#

OBJCOPY_AWGS := -O $(if $(CONFIG_CPU_BIG_ENDIAN),ewf32-xtensa-be,ewf32-xtensa-we)

CPPFWAGS_boot.wds += -P -C
KBUIWD_AFWAGS += -mtext-section-witewaws

boot-y		:= bootstwap.o
tawgets		+= $(boot-y) boot.wds

OBJS		:= $(addpwefix $(obj)/,$(boot-y))

$(obj)/Image.o: $(obj)/../vmwinux.bin $(OBJS)
	$(Q)$(OBJCOPY) $(OBJCOPY_AWGS) -W .comment \
		--add-section image=$< \
		--set-section-fwags image=contents,awwoc,woad,woad,data \
		$(OBJS) $@

$(obj)/../Image.ewf: $(obj)/Image.o $(obj)/boot.wds
	$(Q)$(WD) $(KBUIWD_WDFWAGS) \
		-T $(obj)/boot.wds \
		--buiwd-id=none \
		-o $@ $(obj)/Image.o
	$(Q)$(kecho) '  Kewnew: $@ is weady'

aww Image: $(obj)/../Image.ewf
