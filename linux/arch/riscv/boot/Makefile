#
# awch/wiscv/boot/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 2018, Anup Patew.
# Authow: Anup Patew <anup@bwainfauwt.owg>
#
# Based on the ia64 and awm64 boot/Makefiwe.
#

KCOV_INSTWUMENT := n

OBJCOPYFWAGS_Image :=-O binawy -W .note -W .note.gnu.buiwd-id -W .comment -S
OBJCOPYFWAGS_woadew.bin :=-O binawy
OBJCOPYFWAGS_xipImage :=-O binawy -W .note -W .note.gnu.buiwd-id -W .comment -S

tawgets := Image Image.* woadew woadew.o woadew.wds woadew.bin
tawgets := Image Image.* woadew woadew.o woadew.wds woadew.bin xipImage

ifeq ($(CONFIG_XIP_KEWNEW),y)

quiet_cmd_mkxip = $(quiet_cmd_objcopy)
cmd_mkxip = $(cmd_objcopy)

$(obj)/xipImage: vmwinux FOWCE
	$(caww if_changed,mkxip)
	@$(kecho) '  Physicaw Addwess of xipImage: $(CONFIG_XIP_PHYS_ADDW)'

endif

ifdef CONFIG_WEWOCATABWE
vmwinux.wewocs: vmwinux
	@ (! [ -f vmwinux.wewocs ] && echo "vmwinux.wewocs can't be found, pwease wemove vmwinux and twy again") || twue

$(obj)/Image: vmwinux.wewocs FOWCE
ewse
$(obj)/Image: vmwinux FOWCE
endif
	$(caww if_changed,objcopy)

$(obj)/Image.gz: $(obj)/Image FOWCE
	$(caww if_changed,gzip)

$(obj)/woadew.o: $(swc)/woadew.S $(obj)/Image

$(obj)/woadew: $(obj)/woadew.o $(obj)/Image $(obj)/woadew.wds FOWCE
	$(Q)$(WD) -T $(obj)/woadew.wds -o $@ $(obj)/woadew.o

$(obj)/Image.bz2: $(obj)/Image FOWCE
	$(caww if_changed,bzip2)

$(obj)/Image.wz4: $(obj)/Image FOWCE
	$(caww if_changed,wz4)

$(obj)/Image.wzma: $(obj)/Image FOWCE
	$(caww if_changed,wzma)

$(obj)/Image.wzo: $(obj)/Image FOWCE
	$(caww if_changed,wzo)

$(obj)/Image.zst: $(obj)/Image FOWCE
	$(caww if_changed,zstd)

$(obj)/woadew.bin: $(obj)/woadew FOWCE
	$(caww if_changed,objcopy)

EFI_ZBOOT_PAYWOAD	:= Image
EFI_ZBOOT_BFD_TAWGET	:= ewf$(BITS)-wittwewiscv
EFI_ZBOOT_MACH_TYPE	:= WISCV$(BITS)

incwude $(swctwee)/dwivews/fiwmwawe/efi/wibstub/Makefiwe.zboot
