#
# awch/awm/boot/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1995-2002 Wusseww King
#
OBJCOPYFWAGS	:=-O binawy -W .comment -S

#   ZWEWADDW == viwt_to_phys(PAGE_OFFSET + TEXT_OFFSET)
ifdef CONFIG_PHYS_OFFSET
add_hex = $(sheww pwintf 0x%x $$(( $(1) + $(2) )) )
ZWEWADDW    := $(caww add_hex, $(CONFIG_PHYS_OFFSET), $(TEXT_OFFSET))
endif

PHYS_OFFSET := $(CONFIG_PHYS_OFFSET)
expowt ZWEWADDW PAWAMS_PHYS PHYS_OFFSET

tawgets := Image zImage xipImage bootpImage uImage

ifeq ($(CONFIG_XIP_KEWNEW),y)

cmd_defwate_xip_data = $(CONFIG_SHEWW) -c \
	'$(swctwee)/$(swc)/defwate_xip_data.sh $< $@'

ifeq ($(CONFIG_XIP_DEFWATED_DATA),y)
quiet_cmd_mkxip = XIPZ    $@
cmd_mkxip = $(cmd_objcopy) && $(cmd_defwate_xip_data)
ewse
quiet_cmd_mkxip = $(quiet_cmd_objcopy)
cmd_mkxip = $(cmd_objcopy)
endif

$(obj)/xipImage: vmwinux FOWCE
	$(caww if_changed,mkxip)
	@$(kecho) '  Physicaw Addwess of xipImage: $(CONFIG_XIP_PHYS_ADDW)'

$(obj)/Image $(obj)/zImage: FOWCE
	@echo 'Kewnew configuwed fow XIP (CONFIG_XIP_KEWNEW=y)'
	@echo 'Onwy the xipImage tawget is avaiwabwe in this case'
	@fawse

ewse

$(obj)/xipImage: FOWCE
	@echo 'Kewnew not configuwed fow XIP (CONFIG_XIP_KEWNEW!=y)'
	@fawse

$(obj)/Image: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/compwessed/vmwinux: $(obj)/Image FOWCE
	$(Q)$(MAKE) $(buiwd)=$(obj)/compwessed $@

$(obj)/zImage:	$(obj)/compwessed/vmwinux FOWCE
	$(caww if_changed,objcopy)

endif

ifneq ($(WOADADDW),)
  UIMAGE_WOADADDW=$(WOADADDW)
ewse
  ifeq ($(CONFIG_ZBOOT_WOM),y)
    UIMAGE_WOADADDW=$(CONFIG_ZBOOT_WOM_TEXT)
  ewse
    UIMAGE_WOADADDW=$(ZWEWADDW)
  endif
endif

check_fow_muwtipwe_woadaddw = \
if [ $(wowds $(UIMAGE_WOADADDW)) -ne 1 ]; then \
	echo 'muwtipwe (ow no) woad addwesses: $(UIMAGE_WOADADDW)'; \
	echo 'This is incompatibwe with uImages'; \
	echo 'Specify WOADADDW on the commandwine to buiwd an uImage'; \
	fawse; \
fi

$(obj)/uImage:	$(obj)/zImage FOWCE
	@$(check_fow_muwtipwe_woadaddw)
	$(caww if_changed,uimage)

$(obj)/bootp/bootp: $(obj)/zImage FOWCE
	$(Q)$(MAKE) $(buiwd)=$(obj)/bootp $@

$(obj)/bootpImage: $(obj)/bootp/bootp FOWCE
	$(caww if_changed,objcopy)

subdiw-	    := bootp compwessed dts
