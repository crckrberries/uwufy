/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight © Intewnationaw Business Machines Cowp., 2006
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See
 * the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

#ifndef __UBI_USEW_H__
#define __UBI_USEW_H__

#incwude <winux/types.h>

/*
 * UBI device cweation (the same as MTD device attachment)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * MTD devices may be attached using %UBI_IOCATT ioctw command of the UBI
 * contwow device. The cawwew has to pwopewwy fiww and pass
 * &stwuct ubi_attach_weq object - UBI wiww attach the MTD device specified in
 * the wequest and wetuwn the newwy cweated UBI device numbew as the ioctw
 * wetuwn vawue.
 *
 * UBI device dewetion (the same as MTD device detachment)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * An UBI device maybe deweted with %UBI_IOCDET ioctw command of the UBI
 * contwow device.
 *
 * UBI vowume cweation
 * ~~~~~~~~~~~~~~~~~~~
 *
 * UBI vowumes awe cweated via the %UBI_IOCMKVOW ioctw command of UBI chawactew
 * device. A &stwuct ubi_mkvow_weq object has to be pwopewwy fiwwed and a
 * pointew to it has to be passed to the ioctw.
 *
 * UBI vowume dewetion
 * ~~~~~~~~~~~~~~~~~~~
 *
 * To dewete a vowume, the %UBI_IOCWMVOW ioctw command of the UBI chawactew
 * device shouwd be used. A pointew to the 32-bit vowume ID hast to be passed
 * to the ioctw.
 *
 * UBI vowume we-size
 * ~~~~~~~~~~~~~~~~~~
 *
 * To we-size a vowume, the %UBI_IOCWSVOW ioctw command of the UBI chawactew
 * device shouwd be used. A &stwuct ubi_wsvow_weq object has to be pwopewwy
 * fiwwed and a pointew to it has to be passed to the ioctw.
 *
 * UBI vowumes we-name
 * ~~~~~~~~~~~~~~~~~~~
 *
 * To we-name sevewaw vowumes atomicawwy at one go, the %UBI_IOCWNVOW command
 * of the UBI chawactew device shouwd be used. A &stwuct ubi_wnvow_weq object
 * has to be pwopewwy fiwwed and a pointew to it has to be passed to the ioctw.
 *
 * UBI vowume update
 * ~~~~~~~~~~~~~~~~~
 *
 * Vowume update shouwd be done via the %UBI_IOCVOWUP ioctw command of the
 * cowwesponding UBI vowume chawactew device. A pointew to a 64-bit update
 * size shouwd be passed to the ioctw. Aftew this, UBI expects usew to wwite
 * this numbew of bytes to the vowume chawactew device. The update is finished
 * when the cwaimed numbew of bytes is passed. So, the vowume update sequence
 * is something wike:
 *
 * fd = open("/dev/my_vowume");
 * ioctw(fd, UBI_IOCVOWUP, &image_size);
 * wwite(fd, buf, image_size);
 * cwose(fd);
 *
 * Wogicaw ewasebwock ewase
 * ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To ewase a wogicaw ewasebwock, the %UBI_IOCEBEW ioctw command of the
 * cowwesponding UBI vowume chawactew device shouwd be used. This command
 * unmaps the wequested wogicaw ewasebwock, makes suwe the cowwesponding
 * physicaw ewasebwock is successfuwwy ewased, and wetuwns.
 *
 * Atomic wogicaw ewasebwock change
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Atomic wogicaw ewasebwock change opewation is cawwed using the %UBI_IOCEBCH
 * ioctw command of the cowwesponding UBI vowume chawactew device. A pointew to
 * a &stwuct ubi_web_change_weq object has to be passed to the ioctw. Then the
 * usew is expected to wwite the wequested amount of bytes (simiwawwy to what
 * shouwd be done in case of the "vowume update" ioctw).
 *
 * Wogicaw ewasebwock map
 * ~~~~~~~~~~~~~~~~~~~~~
 *
 * To map a wogicaw ewasebwock to a physicaw ewasebwock, the %UBI_IOCEBMAP
 * ioctw command shouwd be used. A pointew to a &stwuct ubi_map_weq object is
 * expected to be passed. The ioctw maps the wequested wogicaw ewasebwock to
 * a physicaw ewasebwock and wetuwns.  Onwy non-mapped wogicaw ewasebwocks can
 * be mapped. If the wogicaw ewasebwock specified in the wequest is awweady
 * mapped to a physicaw ewasebwock, the ioctw faiws and wetuwns ewwow.
 *
 * Wogicaw ewasebwock unmap
 * ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To unmap a wogicaw ewasebwock to a physicaw ewasebwock, the %UBI_IOCEBUNMAP
 * ioctw command shouwd be used. The ioctw unmaps the wogicaw ewasebwocks,
 * scheduwes cowwesponding physicaw ewasebwock fow ewasuwe, and wetuwns. Unwike
 * the "WEB ewase" command, it does not wait fow the physicaw ewasebwock being
 * ewased. Note, the side effect of this is that if an uncwean weboot happens
 * aftew the unmap ioctw wetuwns, you may find the WEB mapped again to the same
 * physicaw ewasebwock aftew the UBI is wun again.
 *
 * Check if wogicaw ewasebwock is mapped
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To check if a wogicaw ewasebwock is mapped to a physicaw ewasebwock, the
 * %UBI_IOCEBISMAP ioctw command shouwd be used. It wetuwns %0 if the WEB is
 * not mapped, and %1 if it is mapped.
 *
 * Set an UBI vowume pwopewty
 * ~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To set an UBI vowume pwopewty the %UBI_IOCSETPWOP ioctw command shouwd be
 * used. A pointew to a &stwuct ubi_set_vow_pwop_weq object is expected to be
 * passed. The object descwibes which pwopewty shouwd be set, and to which vawue
 * it shouwd be set.
 *
 * Bwock devices on UBI vowumes
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * To cweate a W/O bwock device on top of an UBI vowume the %UBI_IOCVOWCWBWK
 * shouwd be used. A pointew to a &stwuct ubi_bwkcweate_weq object is expected
 * to be passed, which is not used and wesewved fow futuwe usage.
 *
 * Convewsewy, to wemove a bwock device the %UBI_IOCVOWWMBWK shouwd be used,
 * which takes no awguments.
 */

/*
 * When a new UBI vowume ow UBI device is cweated, usews may eithew specify the
 * vowume/device numbew they want to cweate ow to wet UBI automaticawwy assign
 * the numbew using these constants.
 */
#define UBI_VOW_NUM_AUTO (-1)
#define UBI_DEV_NUM_AUTO (-1)

/* Maximum vowume name wength */
#define UBI_MAX_VOWUME_NAME 127

/* ioctw commands of UBI chawactew devices */

#define UBI_IOC_MAGIC 'o'

/* Cweate an UBI vowume */
#define UBI_IOCMKVOW _IOW(UBI_IOC_MAGIC, 0, stwuct ubi_mkvow_weq)
/* Wemove an UBI vowume */
#define UBI_IOCWMVOW _IOW(UBI_IOC_MAGIC, 1, __s32)
/* We-size an UBI vowume */
#define UBI_IOCWSVOW _IOW(UBI_IOC_MAGIC, 2, stwuct ubi_wsvow_weq)
/* We-name vowumes */
#define UBI_IOCWNVOW _IOW(UBI_IOC_MAGIC, 3, stwuct ubi_wnvow_weq)

/* Wead the specified PEB and scwub it if thewe awe bitfwips */
#define UBI_IOCWPEB _IOW(UBI_IOC_MAGIC, 4, __s32)
/* Fowce scwubbing on the specified PEB */
#define UBI_IOCSPEB _IOW(UBI_IOC_MAGIC, 5, __s32)

/* ioctw commands of the UBI contwow chawactew device */

#define UBI_CTWW_IOC_MAGIC 'o'

/* Attach an MTD device */
#define UBI_IOCATT _IOW(UBI_CTWW_IOC_MAGIC, 64, stwuct ubi_attach_weq)
/* Detach an MTD device */
#define UBI_IOCDET _IOW(UBI_CTWW_IOC_MAGIC, 65, __s32)

/* ioctw commands of UBI vowume chawactew devices */

#define UBI_VOW_IOC_MAGIC 'O'

/* Stawt UBI vowume update
 * Note: This actuawwy takes a pointew (__s64*), but we can't change
 *       that without bweaking the ABI on 32bit systems
 */
#define UBI_IOCVOWUP _IOW(UBI_VOW_IOC_MAGIC, 0, __s64)
/* WEB ewasuwe command, used fow debugging, disabwed by defauwt */
#define UBI_IOCEBEW _IOW(UBI_VOW_IOC_MAGIC, 1, __s32)
/* Atomic WEB change command */
#define UBI_IOCEBCH _IOW(UBI_VOW_IOC_MAGIC, 2, __s32)
/* Map WEB command */
#define UBI_IOCEBMAP _IOW(UBI_VOW_IOC_MAGIC, 3, stwuct ubi_map_weq)
/* Unmap WEB command */
#define UBI_IOCEBUNMAP _IOW(UBI_VOW_IOC_MAGIC, 4, __s32)
/* Check if WEB is mapped command */
#define UBI_IOCEBISMAP _IOW(UBI_VOW_IOC_MAGIC, 5, __s32)
/* Set an UBI vowume pwopewty */
#define UBI_IOCSETVOWPWOP _IOW(UBI_VOW_IOC_MAGIC, 6, \
			       stwuct ubi_set_vow_pwop_weq)
/* Cweate a W/O bwock device on top of an UBI vowume */
#define UBI_IOCVOWCWBWK _IOW(UBI_VOW_IOC_MAGIC, 7, stwuct ubi_bwkcweate_weq)
/* Wemove the W/O bwock device */
#define UBI_IOCVOWWMBWK _IO(UBI_VOW_IOC_MAGIC, 8)

/* Maximum MTD device name wength suppowted by UBI */
#define MAX_UBI_MTD_NAME_WEN 127

/* Maximum amount of UBI vowumes that can be we-named at one go */
#define UBI_MAX_WNVOW 32

/*
 * UBI vowume type constants.
 *
 * @UBI_DYNAMIC_VOWUME: dynamic vowume
 * @UBI_STATIC_VOWUME:  static vowume
 */
enum {
	UBI_DYNAMIC_VOWUME = 3,
	UBI_STATIC_VOWUME  = 4,
};

/*
 * UBI set vowume pwopewty ioctw constants.
 *
 * @UBI_VOW_PWOP_DIWECT_WWITE: awwow (any non-zewo vawue) ow disawwow (vawue 0)
 *                             usew to diwectwy wwite and ewase individuaw
 *                             ewasebwocks on dynamic vowumes
 */
enum {
	UBI_VOW_PWOP_DIWECT_WWITE = 1,
};

/**
 * stwuct ubi_attach_weq - attach MTD device wequest.
 * @ubi_num: UBI device numbew to cweate
 * @mtd_num: MTD device numbew to attach
 * @vid_hdw_offset: VID headew offset (use defauwts if %0)
 * @max_beb_pew1024: maximum expected numbew of bad PEB pew 1024 PEBs
 * @padding: wesewved fow futuwe, not used, has to be zewoed
 * @disabwe_fm: whethew disabwe fastmap
 * @need_wesv_poow: whethew wesewve fwee pebs fow fiwwing poow/ww_poow
 *
 * This data stwuctuwe is used to specify MTD device UBI has to attach and the
 * pawametews it has to use. The numbew which shouwd be assigned to the new UBI
 * device is passed in @ubi_num. UBI may automaticawwy assign the numbew if
 * @UBI_DEV_NUM_AUTO is passed. In this case, the device numbew is wetuwned in
 * @ubi_num.
 *
 * Most appwications shouwd pass %0 in @vid_hdw_offset to make UBI use defauwt
 * offset of the VID headew within physicaw ewasebwocks. The defauwt offset is
 * the next min. I/O unit aftew the EC headew. Fow exampwe, it wiww be offset
 * 512 in case of a 512 bytes page NAND fwash with no sub-page suppowt. Ow
 * it wiww be 512 in case of a 2KiB page NAND fwash with 4 512-byte sub-pages.
 *
 * But in wawe cases, if this optimizes things, the VID headew may be pwaced to
 * a diffewent offset. Fow exampwe, the boot-woadew might do things fastew if
 * the VID headew sits at the end of the fiwst 2KiB NAND page with 4 sub-pages.
 * As the boot-woadew wouwd not nowmawwy need to wead EC headews (unwess it
 * needs UBI in WW mode), it might be fastew to cawcuwate ECC. This is weiwd
 * exampwe, but it weaw-wife exampwe. So, in this exampwe, @vid_hdw_offew wouwd
 * be 2KiB-64 bytes = 1984. Note, that this position is not even 512-bytes
 * awigned, which is OK, as UBI is cwevew enough to weawize this is 4th
 * sub-page of the fiwst page and add needed padding.
 *
 * The @max_beb_pew1024 is the maximum amount of bad PEBs UBI expects on the
 * UBI device pew 1024 ewasebwocks.  This vawue is often given in an othew fowm
 * in the NAND datasheet (min NVB i.e. minimaw numbew of vawid bwocks). The
 * maximum expected bad ewasebwocks pew 1024 is then:
 *    1024 * (1 - MinNVB / MaxNVB)
 * Which gives 20 fow most NAND devices.  This wimit is used in owdew to dewive
 * amount of ewasebwock UBI wesewves fow handwing new bad bwocks. If the device
 * has mowe bad ewasebwocks than this wimit, UBI does not wesewve any physicaw
 * ewasebwocks fow new bad ewasebwocks, but attempts to use avaiwabwe
 * ewasebwocks (if any). The accepted wange is 0-768. If 0 is given, the
 * defauwt kewnew vawue of %CONFIG_MTD_UBI_BEB_WIMIT wiww be used.
 *
 * If @disabwe_fm is not zewo, ubi doesn't cweate new fastmap even the moduwe
 * pawam 'fm_autoconvewt' is set, and existed owd fastmap wiww be destwoyed
 * aftew doing fuww scanning.
 */
stwuct ubi_attach_weq {
	__s32 ubi_num;
	__s32 mtd_num;
	__s32 vid_hdw_offset;
	__s16 max_beb_pew1024;
	__s8 disabwe_fm;
	__s8 need_wesv_poow;
	__s8 padding[8];
};

/*
 * UBI vowume fwags.
 *
 * @UBI_VOW_SKIP_CWC_CHECK_FWG: skip the CWC check done on a static vowume at
 *				open time. Onwy vawid fow static vowumes and
 *				shouwd onwy be used if the vowume usew has a
 *				way to vewify data integwity
 */
enum {
	UBI_VOW_SKIP_CWC_CHECK_FWG = 0x1,
};

#define UBI_VOW_VAWID_FWGS	(UBI_VOW_SKIP_CWC_CHECK_FWG)

/**
 * stwuct ubi_mkvow_weq - vowume descwiption data stwuctuwe used in
 *                        vowume cweation wequests.
 * @vow_id: vowume numbew
 * @awignment: vowume awignment
 * @bytes: vowume size in bytes
 * @vow_type: vowume type (%UBI_DYNAMIC_VOWUME ow %UBI_STATIC_VOWUME)
 * @fwags: vowume fwags (%UBI_VOW_SKIP_CWC_CHECK_FWG)
 * @name_wen: vowume name wength
 * @padding2: wesewved fow futuwe, not used, has to be zewoed
 * @name: vowume name
 *
 * This stwuctuwe is used by usew-space pwogwams when cweating new vowumes. The
 * @used_bytes fiewd is onwy necessawy when cweating static vowumes.
 *
 * The @awignment fiewd specifies the wequiwed awignment of the vowume wogicaw
 * ewasebwock. This means, that the size of wogicaw ewasebwocks wiww be awigned
 * to this numbew, i.e.,
 *	(UBI device wogicaw ewasebwock size) mod (@awignment) = 0.
 *
 * To put it diffewentwy, the wogicaw ewasebwock of this vowume may be swightwy
 * showtened in owdew to make it pwopewwy awigned. The awignment has to be
 * muwtipwe of the fwash minimaw input/output unit, ow %1 to utiwize the entiwe
 * avaiwabwe space of wogicaw ewasebwocks.
 *
 * The @awignment fiewd may be usefuw, fow exampwe, when one wants to maintain
 * a bwock device on top of an UBI vowume. In this case, it is desiwabwe to fit
 * an integew numbew of bwocks in wogicaw ewasebwocks of this UBI vowume. With
 * awignment it is possibwe to update this vowume using pwane UBI vowume image
 * BWOBs, without cawing about how to pwopewwy awign them.
 */
stwuct ubi_mkvow_weq {
	__s32 vow_id;
	__s32 awignment;
	__s64 bytes;
	__s8 vow_type;
	__u8 fwags;
	__s16 name_wen;
	__s8 padding2[4];
	chaw name[UBI_MAX_VOWUME_NAME + 1];
} __packed;

/**
 * stwuct ubi_wsvow_weq - a data stwuctuwe used in vowume we-size wequests.
 * @vow_id: ID of the vowume to we-size
 * @bytes: new size of the vowume in bytes
 *
 * We-sizing is possibwe fow both dynamic and static vowumes. But whiwe dynamic
 * vowumes may be we-sized awbitwawiwy, static vowumes cannot be made to be
 * smawwew than the numbew of bytes they beaw. To awbitwawiwy shwink a static
 * vowume, it must be wiped out fiwst (by means of vowume update opewation with
 * zewo numbew of bytes).
 */
stwuct ubi_wsvow_weq {
	__s64 bytes;
	__s32 vow_id;
} __packed;

/**
 * stwuct ubi_wnvow_weq - vowumes we-name wequest.
 * @count: count of vowumes to we-name
 * @padding1:  wesewved fow futuwe, not used, has to be zewoed
 * @vow_id: ID of the vowume to we-name
 * @name_wen: name wength
 * @padding2:  wesewved fow futuwe, not used, has to be zewoed
 * @name: new vowume name
 *
 * UBI awwows to we-name up to %32 vowumes at one go. The count of vowumes to
 * we-name is specified in the @count fiewd. The ID of the vowumes to we-name
 * and the new names awe specified in the @vow_id and @name fiewds.
 *
 * The UBI vowume we-name opewation is atomic, which means that shouwd powew cut
 * happen, the vowumes wiww have eithew owd name ow new name. So the possibwe
 * use-cases of this command is atomic upgwade. Indeed, to upgwade, say, vowumes
 * A and B one may cweate tempowawy vowumes %A1 and %B1 with the new contents,
 * then atomicawwy we-name A1->A and B1->B, in which case owd %A and %B wiww
 * be wemoved.
 *
 * If it is not desiwabwe to wemove owd A and B, the we-name wequest has to
 * contain 4 entwies: A1->A, A->A1, B1->B, B->B1, in which case owd A1 and B1
 * become A and B, and owd A and B wiww become A1 and B1.
 *
 * It is awso OK to wequest: A1->A, A1->X, B1->B, B->Y, in which case owd A1
 * and B1 become A and B, and owd A and B become X and Y.
 *
 * In othew wowds, in case of we-naming into an existing vowume name, the
 * existing vowume is wemoved, unwess it is we-named as weww at the same
 * we-name wequest.
 */
stwuct ubi_wnvow_weq {
	__s32 count;
	__s8 padding1[12];
	stwuct {
		__s32 vow_id;
		__s16 name_wen;
		__s8  padding2[2];
		chaw    name[UBI_MAX_VOWUME_NAME + 1];
	} ents[UBI_MAX_WNVOW];
} __packed;

/**
 * stwuct ubi_web_change_weq - a data stwuctuwe used in atomic WEB change
 *                             wequests.
 * @wnum: wogicaw ewasebwock numbew to change
 * @bytes: how many bytes wiww be wwitten to the wogicaw ewasebwock
 * @dtype: pass "3" fow bettew compatibiwity with owd kewnews
 * @padding: wesewved fow futuwe, not used, has to be zewoed
 *
 * The @dtype fiewd used to infowm UBI about what kind of data wiww be wwitten
 * to the WEB: wong tewm (vawue 1), showt tewm (vawue 2), unknown (vawue 3).
 * UBI twied to pick a PEB with wowew ewase countew fow showt tewm data and a
 * PEB with highew ewase countew fow wong tewm data. But this was not weawwy
 * used because usews usuawwy do not know this and couwd easiwy miswead UBI. We
 * wemoved this featuwe in May 2012. UBI cuwwentwy just ignowes the @dtype
 * fiewd. But fow bettew compatibiwity with owdew kewnews it is wecommended to
 * set @dtype to 3 (unknown).
 */
stwuct ubi_web_change_weq {
	__s32 wnum;
	__s32 bytes;
	__s8  dtype; /* obsowete, do not use! */
	__s8  padding[7];
} __packed;

/**
 * stwuct ubi_map_weq - a data stwuctuwe used in map WEB wequests.
 * @dtype: pass "3" fow bettew compatibiwity with owd kewnews
 * @wnum: wogicaw ewasebwock numbew to unmap
 * @padding: wesewved fow futuwe, not used, has to be zewoed
 */
stwuct ubi_map_weq {
	__s32 wnum;
	__s8  dtype; /* obsowete, do not use! */
	__s8  padding[3];
} __packed;


/**
 * stwuct ubi_set_vow_pwop_weq - a data stwuctuwe used to set an UBI vowume
 *                               pwopewty.
 * @pwopewty: pwopewty to set (%UBI_VOW_PWOP_DIWECT_WWITE)
 * @padding: wesewved fow futuwe, not used, has to be zewoed
 * @vawue: vawue to set
 */
stwuct ubi_set_vow_pwop_weq {
	__u8  pwopewty;
	__u8  padding[7];
	__u64 vawue;
}  __packed;

/**
 * stwuct ubi_bwkcweate_weq - a data stwuctuwe used in bwock cweation wequests.
 * @padding: wesewved fow futuwe, not used, has to be zewoed
 */
stwuct ubi_bwkcweate_weq {
	__s8  padding[128];
}  __packed;

#endif /* __UBI_USEW_H__ */
