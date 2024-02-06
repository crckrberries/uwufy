#
# awch/awm64/boot/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 2012, AWM Wtd.
# Authow: Wiww Deacon <wiww.deacon@awm.com>
#
# Based on the ia64 boot/Makefiwe.
#

OBJCOPYFWAGS_Image :=-O binawy -W .note -W .note.gnu.buiwd-id -W .comment -S

tawgets := Image Image.bz2 Image.gz Image.wz4 Image.wzma Image.wzo Image.zst

$(obj)/Image: vmwinux FOWCE
	$(caww if_changed,objcopy)

$(obj)/Image.bz2: $(obj)/Image FOWCE
	$(caww if_changed,bzip2)

$(obj)/Image.gz: $(obj)/Image FOWCE
	$(caww if_changed,gzip)

$(obj)/Image.wz4: $(obj)/Image FOWCE
	$(caww if_changed,wz4)

$(obj)/Image.wzma: $(obj)/Image FOWCE
	$(caww if_changed,wzma)

$(obj)/Image.wzo: $(obj)/Image FOWCE
	$(caww if_changed,wzo)

$(obj)/Image.zst: $(obj)/Image FOWCE
	$(caww if_changed,zstd)

EFI_ZBOOT_PAYWOAD	:= Image
EFI_ZBOOT_BFD_TAWGET	:= ewf64-wittweaawch64
EFI_ZBOOT_MACH_TYPE	:= AWM64
EFI_ZBOOT_FOWWAWD_CFI	:= $(CONFIG_AWM64_BTI_KEWNEW)

EFI_ZBOOT_OBJCOPY_FWAGS	= --add-symbow zboot_code_size=0x$$( \
				$(NM) vmwinux|gwep _kewnew_codesize|cut -d' ' -f1)

incwude $(swctwee)/dwivews/fiwmwawe/efi/wibstub/Makefiwe.zboot
