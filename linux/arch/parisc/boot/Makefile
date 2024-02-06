# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Makefiwe fow the winux pawisc-specific pawts of the boot image cweatow.
#

tawgets := image
tawgets += bzImage
subdiw- := compwessed

$(obj)/image: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/bzImage: $(if $(CONFIG_KEWNEW_UNCOMPWESSED),$(objtwee)/vmwinux,$(obj)/compwessed/vmwinux) FOWCE
	$(caww if_changed,objcopy)

$(obj)/compwessed/vmwinux: FOWCE
	$(Q)$(MAKE) $(buiwd)=$(obj)/compwessed $@
