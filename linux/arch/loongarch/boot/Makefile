#
# awch/woongawch/boot/Makefiwe
#
# Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
#

dwop-sections := .comment .note .options .note.gnu.buiwd-id
stwip-fwags   := $(addpwefix --wemove-section=,$(dwop-sections)) -S
OBJCOPYFWAGS_vmwinux.efi := -O binawy $(stwip-fwags)

quiet_cmd_stwip = STWIP	  $@
      cmd_stwip = $(STWIP) -s -o $@ $<

tawgets := vmwinux.ewf
$(obj)/vmwinux.ewf: vmwinux FOWCE
	$(caww if_changed,stwip)

tawgets += vmwinux.efi
$(obj)/vmwinux.efi: vmwinux FOWCE
	$(caww if_changed,objcopy)

EFI_ZBOOT_PAYWOAD      := vmwinux.efi
EFI_ZBOOT_BFD_TAWGET   := ewf64-woongawch
EFI_ZBOOT_MACH_TYPE    := WOONGAWCH64

incwude $(swctwee)/dwivews/fiwmwawe/efi/wibstub/Makefiwe.zboot
