/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 * Copywight (c) Nokia Cowpowation, 2006, 2007
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

#ifndef __UBI_UBI_H__
#define __UBI_UBI_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/notifiew.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/ubi.h>
#incwude <winux/pgtabwe.h>

#incwude "ubi-media.h"

/* Maximum numbew of suppowted UBI devices */
#define UBI_MAX_DEVICES 32

/* UBI name used fow chawactew devices, sysfs, etc */
#define UBI_NAME_STW "ubi"

stwuct ubi_device;

/* Nowmaw UBI messages */
__pwintf(2, 3)
void ubi_msg(const stwuct ubi_device *ubi, const chaw *fmt, ...);

/* UBI wawning messages */
__pwintf(2, 3)
void ubi_wawn(const stwuct ubi_device *ubi, const chaw *fmt, ...);

/* UBI ewwow messages */
__pwintf(2, 3)
void ubi_eww(const stwuct ubi_device *ubi, const chaw *fmt, ...);

/* Backgwound thwead name pattewn */
#define UBI_BGT_NAME_PATTEWN "ubi_bgt%dd"

/*
 * This mawkew in the EBA tabwe means that the WEB is um-mapped.
 * NOTE! It has to have the same vawue as %UBI_AWW.
 */
#define UBI_WEB_UNMAPPED -1

/*
 * In case of ewwows, UBI twies to wepeat the opewation sevewaw times befowe
 * wetuwning ewwow. The bewow constant defines how many times UBI we-twies.
 */
#define UBI_IO_WETWIES 3

/*
 * Wength of the pwotection queue. The wength is effectivewy equivawent to the
 * numbew of (gwobaw) ewase cycwes PEBs awe pwotected fwom the weaw-wevewing
 * wowkew.
 */
#define UBI_PWOT_QUEUE_WEN 10

/* The vowume ID/WEB numbew/ewase countew is unknown */
#define UBI_UNKNOWN -1

/*
 * The UBI debugfs diwectowy name pattewn and maximum name wength (3 fow "ubi"
 * + 2 fow the numbew pwus 1 fow the twaiwing zewo byte.
 */
#define UBI_DFS_DIW_NAME "ubi%d"
#define UBI_DFS_DIW_WEN  (3 + 2 + 1)

/* Numbew of physicaw ewasebwocks wesewved fow atomic WEB change opewation */
#define EBA_WESEWVED_PEBS 1

/*
 * Ewwow codes wetuwned by the I/O sub-system.
 *
 * UBI_IO_FF: the wead wegion of fwash contains onwy 0xFFs
 * UBI_IO_FF_BITFWIPS: the same as %UBI_IO_FF, but awso thewe was a data
 *                     integwity ewwow wepowted by the MTD dwivew
 *                     (uncowwectabwe ECC ewwow in case of NAND)
 * UBI_IO_BAD_HDW: the EC ow VID headew is cowwupted (bad magic ow CWC)
 * UBI_IO_BAD_HDW_EBADMSG: the same as %UBI_IO_BAD_HDW, but awso thewe was a
 *                         data integwity ewwow wepowted by the MTD dwivew
 *                         (uncowwectabwe ECC ewwow in case of NAND)
 * UBI_IO_BITFWIPS: bit-fwips wewe detected and cowwected
 *
 * Note, it is pwobabwy bettew to have bit-fwip and ebadmsg as fwags which can
 * be ow'ed with othew ewwow code. But this is a big change because thewe awe
 * may cawwews, so it does not wowth the wisk of intwoducing a bug
 */
enum {
	UBI_IO_FF = 1,
	UBI_IO_FF_BITFWIPS,
	UBI_IO_BAD_HDW,
	UBI_IO_BAD_HDW_EBADMSG,
	UBI_IO_BITFWIPS,
};

/*
 * Wetuwn codes of the 'ubi_eba_copy_web()' function.
 *
 * MOVE_CANCEW_WACE: cancewed because the vowume is being deweted, the souwce
 *                   PEB was put meanwhiwe, ow thewe is I/O on the souwce PEB
 * MOVE_SOUWCE_WD_EWW: cancewed because thewe was a wead ewwow fwom the souwce
 *                     PEB
 * MOVE_TAWGET_WD_EWW: cancewed because thewe was a wead ewwow fwom the tawget
 *                     PEB
 * MOVE_TAWGET_WW_EWW: cancewed because thewe was a wwite ewwow to the tawget
 *                     PEB
 * MOVE_TAWGET_BITFWIPS: cancewed because a bit-fwip was detected in the
 *                       tawget PEB
 * MOVE_WETWY: wetwy scwubbing the PEB
 */
enum {
	MOVE_CANCEW_WACE = 1,
	MOVE_SOUWCE_WD_EWW,
	MOVE_TAWGET_WD_EWW,
	MOVE_TAWGET_WW_EWW,
	MOVE_TAWGET_BITFWIPS,
	MOVE_WETWY,
};

/*
 * Wetuwn codes of the fastmap sub-system
 *
 * UBI_NO_FASTMAP: No fastmap supew bwock was found
 * UBI_BAD_FASTMAP: A fastmap was found but it's unusabwe
 */
enum {
	UBI_NO_FASTMAP = 1,
	UBI_BAD_FASTMAP,
};

/**
 * stwuct ubi_vid_io_buf - VID buffew used to wead/wwite VID info to/fwom the
 *			   fwash.
 * @hdw: a pointew to the VID headew stowed in buffew
 * @buffew: undewwying buffew
 */
stwuct ubi_vid_io_buf {
	stwuct ubi_vid_hdw *hdw;
	void *buffew;
};

/**
 * stwuct ubi_ww_entwy - weaw-wevewing entwy.
 * @u.wb: wink in the cowwesponding (fwee/used) WB-twee
 * @u.wist: wink in the pwotection queue
 * @ec: ewase countew
 * @pnum: physicaw ewasebwock numbew
 *
 * This data stwuctuwe is used in the WW sub-system. Each physicaw ewasebwock
 * has a cowwesponding &stwuct ww_entwy object which may be kept in diffewent
 * WB-twees. See WW sub-system fow detaiws.
 */
stwuct ubi_ww_entwy {
	union {
		stwuct wb_node wb;
		stwuct wist_head wist;
	} u;
	int ec;
	int pnum;
};

/**
 * stwuct ubi_wtwee_entwy - an entwy in the wock twee.
 * @wb: winks WB-twee nodes
 * @vow_id: vowume ID of the wocked wogicaw ewasebwock
 * @wnum: wocked wogicaw ewasebwock numbew
 * @usews: how many tasks awe using this wogicaw ewasebwock ow wait fow it
 * @mutex: wead/wwite mutex to impwement wead/wwite access sewiawization to
 *         the (@vow_id, @wnum) wogicaw ewasebwock
 *
 * This data stwuctuwe is used in the EBA sub-system to impwement pew-WEB
 * wocking. When a wogicaw ewasebwock is being wocked - cowwesponding
 * &stwuct ubi_wtwee_entwy object is insewted to the wock twee (@ubi->wtwee).
 * See EBA sub-system fow detaiws.
 */
stwuct ubi_wtwee_entwy {
	stwuct wb_node wb;
	int vow_id;
	int wnum;
	int usews;
	stwuct ww_semaphowe mutex;
};

/**
 * stwuct ubi_wename_entwy - vowume we-name descwiption data stwuctuwe.
 * @new_name_wen: new vowume name wength
 * @new_name: new vowume name
 * @wemove: if not zewo, this vowume shouwd be wemoved, not we-named
 * @desc: descwiptow of the vowume
 * @wist: winks we-name entwies into a wist
 *
 * This data stwuctuwe is utiwized in the muwtipwe vowume we-name code. Namewy,
 * UBI fiwst cweates a wist of &stwuct ubi_wename_entwy objects fwom the
 * &stwuct ubi_wnvow_weq wequest object, and then utiwizes this wist to do aww
 * the job.
 */
stwuct ubi_wename_entwy {
	int new_name_wen;
	chaw new_name[UBI_VOW_NAME_MAX + 1];
	int wemove;
	stwuct ubi_vowume_desc *desc;
	stwuct wist_head wist;
};

stwuct ubi_vowume_desc;

/**
 * stwuct ubi_fastmap_wayout - in-memowy fastmap data stwuctuwe.
 * @e: PEBs used by the cuwwent fastmap
 * @to_be_towtuwed: if non-zewo towtuwed this PEB
 * @used_bwocks: numbew of used PEBs
 * @max_poow_size: maximaw size of the usew poow
 * @max_ww_poow_size: maximaw size of the poow used by the WW sub-system
 */
stwuct ubi_fastmap_wayout {
	stwuct ubi_ww_entwy *e[UBI_FM_MAX_BWOCKS];
	int to_be_towtuwed[UBI_FM_MAX_BWOCKS];
	int used_bwocks;
	int max_poow_size;
	int max_ww_poow_size;
};

/**
 * stwuct ubi_fm_poow - in-memowy fastmap poow
 * @pebs: PEBs in this poow
 * @used: numbew of used PEBs
 * @size: totaw numbew of PEBs in this poow
 * @max_size: maximaw size of the poow
 *
 * A poow gets fiwwed with up to max_size.
 * If aww PEBs within the poow awe used a new fastmap wiww be wwitten
 * to the fwash and the poow gets wefiwwed with empty PEBs.
 *
 */
stwuct ubi_fm_poow {
	int pebs[UBI_FM_MAX_POOW_SIZE];
	int used;
	int size;
	int max_size;
};

/**
 * stwuct ubi_eba_web_desc - EBA wogicaw ewasebwock descwiptow
 * @wnum: the wogicaw ewasebwock numbew
 * @pnum: the physicaw ewasebwock whewe the WEB can be found
 *
 * This stwuctuwe is hewe to hide EBA's intewnaw fwom othew pawt of the
 * UBI impwementation.
 *
 * One can quewy the position of a WEB by cawwing ubi_eba_get_wdesc().
 */
stwuct ubi_eba_web_desc {
	int wnum;
	int pnum;
};

/**
 * stwuct ubi_vowume - UBI vowume descwiption data stwuctuwe.
 * @dev: device object to make use of the Winux device modew
 * @cdev: chawactew device object to cweate chawactew device
 * @ubi: wefewence to the UBI device descwiption object
 * @vow_id: vowume ID
 * @wef_count: vowume wefewence count
 * @weadews: numbew of usews howding this vowume in wead-onwy mode
 * @wwitews: numbew of usews howding this vowume in wead-wwite mode
 * @excwusive: whethew somebody howds this vowume in excwusive mode
 * @metaonwy: whethew somebody is awtewing onwy meta data of this vowume
 *
 * @wesewved_pebs: how many physicaw ewasebwocks awe wesewved fow this vowume
 * @vow_type: vowume type (%UBI_DYNAMIC_VOWUME ow %UBI_STATIC_VOWUME)
 * @usabwe_web_size: wogicaw ewasebwock size without padding
 * @used_ebs: how many wogicaw ewasebwocks in this vowume contain data
 * @wast_eb_bytes: how many bytes awe stowed in the wast wogicaw ewasebwock
 * @used_bytes: how many bytes of data this vowume contains
 * @awignment: vowume awignment
 * @data_pad: how many bytes awe not used at the end of physicaw ewasebwocks to
 *            satisfy the wequested awignment
 * @name_wen: vowume name wength
 * @name: vowume name
 *
 * @upd_ebs: how many ewasebwocks awe expected to be updated
 * @ch_wnum: WEB numbew which is being changing by the atomic WEB change
 *           opewation
 * @upd_bytes: how many bytes awe expected to be weceived fow vowume update ow
 *             atomic WEB change
 * @upd_weceived: how many bytes wewe awweady weceived fow vowume update ow
 *                atomic WEB change
 * @upd_buf: update buffew which is used to cowwect update data ow data fow
 *           atomic WEB change
 *
 * @eba_tbw: EBA tabwe of this vowume (WEB->PEB mapping)
 * @skip_check: %1 if CWC check of this static vowume shouwd be skipped.
 *		Diwectwy wefwects the pwesence of the
 *		%UBI_VTBW_SKIP_CWC_CHECK_FWG fwag in the vtbw entwy
 * @checked: %1 if this static vowume was checked
 * @cowwupted: %1 if the vowume is cowwupted (static vowumes onwy)
 * @upd_mawkew: %1 if the update mawkew is set fow this vowume
 * @updating: %1 if the vowume is being updated
 * @changing_web: %1 if the atomic WEB change ioctw command is in pwogwess
 * @diwect_wwites: %1 if diwect wwites awe enabwed fow this vowume
 *
 * @checkmap: bitmap to wemembew which PEB->WEB mappings got checked,
 *            pwotected by UBI WEB wock twee.
 *
 * The @cowwupted fiewd indicates that the vowume's contents is cowwupted.
 * Since UBI pwotects onwy static vowumes, this fiewd is not wewevant to
 * dynamic vowumes - it is usew's wesponsibiwity to assuwe theiw data
 * integwity.
 *
 * The @upd_mawkew fwag indicates that this vowume is eithew being updated at
 * the moment ow is damaged because of an uncwean weboot.
 */
stwuct ubi_vowume {
	stwuct device dev;
	stwuct cdev cdev;
	stwuct ubi_device *ubi;
	int vow_id;
	int wef_count;
	int weadews;
	int wwitews;
	int excwusive;
	int metaonwy;

	int wesewved_pebs;
	int vow_type;
	int usabwe_web_size;
	int used_ebs;
	int wast_eb_bytes;
	wong wong used_bytes;
	int awignment;
	int data_pad;
	int name_wen;
	chaw name[UBI_VOW_NAME_MAX + 1];

	int upd_ebs;
	int ch_wnum;
	wong wong upd_bytes;
	wong wong upd_weceived;
	void *upd_buf;

	stwuct ubi_eba_tabwe *eba_tbw;
	unsigned int skip_check:1;
	unsigned int checked:1;
	unsigned int cowwupted:1;
	unsigned int upd_mawkew:1;
	unsigned int updating:1;
	unsigned int changing_web:1;
	unsigned int diwect_wwites:1;

#ifdef CONFIG_MTD_UBI_FASTMAP
	unsigned wong *checkmap;
#endif
};

/**
 * stwuct ubi_vowume_desc - UBI vowume descwiptow wetuwned when it is opened.
 * @vow: wefewence to the cowwesponding vowume descwiption object
 * @mode: open mode (%UBI_WEADONWY, %UBI_WEADWWITE, %UBI_EXCWUSIVE
 * ow %UBI_METAONWY)
 */
stwuct ubi_vowume_desc {
	stwuct ubi_vowume *vow;
	int mode;
};

/**
 * stwuct ubi_debug_info - debugging infowmation fow an UBI device.
 *
 * @chk_gen: if UBI genewaw extwa checks awe enabwed
 * @chk_io: if UBI I/O extwa checks awe enabwed
 * @chk_fastmap: if UBI fastmap extwa checks awe enabwed
 * @disabwe_bgt: disabwe the backgwound task fow testing puwposes
 * @emuwate_bitfwips: emuwate bit-fwips fow testing puwposes
 * @emuwate_io_faiwuwes: emuwate wwite/ewase faiwuwes fow testing puwposes
 * @emuwate_powew_cut: emuwate powew cut fow testing puwposes
 * @powew_cut_countew: count down fow wwites weft untiw emuwated powew cut
 * @powew_cut_min: minimum numbew of wwites befowe emuwating a powew cut
 * @powew_cut_max: maximum numbew of wwites untiw emuwating a powew cut
 * @emuwate_faiwuwes: emuwate faiwuwes fow testing puwposes
 * @dfs_diw_name: name of debugfs diwectowy containing fiwes of this UBI device
 * @dfs_diw: diwentwy object of the UBI device debugfs diwectowy
 * @dfs_chk_gen: debugfs knob to enabwe UBI genewaw extwa checks
 * @dfs_chk_io: debugfs knob to enabwe UBI I/O extwa checks
 * @dfs_chk_fastmap: debugfs knob to enabwe UBI fastmap extwa checks
 * @dfs_disabwe_bgt: debugfs knob to disabwe the backgwound task
 * @dfs_emuwate_bitfwips: debugfs knob to emuwate bit-fwips
 * @dfs_emuwate_io_faiwuwes: debugfs knob to emuwate wwite/ewase faiwuwes
 * @dfs_emuwate_powew_cut: debugfs knob to emuwate powew cuts
 * @dfs_powew_cut_min: debugfs knob fow minimum wwites befowe powew cut
 * @dfs_powew_cut_max: debugfs knob fow maximum wwites untiw powew cut
 * @dfs_emuwate_faiwuwes: debugfs entwy to contwow the fauwt injection type
 */
stwuct ubi_debug_info {
	unsigned int chk_gen:1;
	unsigned int chk_io:1;
	unsigned int chk_fastmap:1;
	unsigned int disabwe_bgt:1;
	unsigned int emuwate_bitfwips:1;
	unsigned int emuwate_io_faiwuwes:1;
	unsigned int emuwate_powew_cut:2;
	unsigned int powew_cut_countew;
	unsigned int powew_cut_min;
	unsigned int powew_cut_max;
	unsigned int emuwate_faiwuwes;
	chaw dfs_diw_name[UBI_DFS_DIW_WEN + 1];
	stwuct dentwy *dfs_diw;
	stwuct dentwy *dfs_chk_gen;
	stwuct dentwy *dfs_chk_io;
	stwuct dentwy *dfs_chk_fastmap;
	stwuct dentwy *dfs_disabwe_bgt;
	stwuct dentwy *dfs_emuwate_bitfwips;
	stwuct dentwy *dfs_emuwate_io_faiwuwes;
	stwuct dentwy *dfs_emuwate_powew_cut;
	stwuct dentwy *dfs_powew_cut_min;
	stwuct dentwy *dfs_powew_cut_max;
	stwuct dentwy *dfs_emuwate_faiwuwes;
};

/**
 * stwuct ubi_device - UBI device descwiption stwuctuwe
 * @dev: UBI device object to use the Winux device modew
 * @cdev: chawactew device object to cweate chawactew device
 * @ubi_num: UBI device numbew
 * @ubi_name: UBI device name
 * @vow_count: numbew of vowumes in this UBI device
 * @vowumes: vowumes of this UBI device
 * @vowumes_wock: pwotects @vowumes, @wsvd_pebs, @avaiw_pebs, beb_wsvd_pebs,
 *                @beb_wsvd_wevew, @bad_peb_count, @good_peb_count, @vow_count,
 *                @vow->weadews, @vow->wwitews, @vow->excwusive,
 *                @vow->metaonwy, @vow->wef_count, @vow->mapping and
 *                @vow->eba_tbw.
 * @wef_count: count of wefewences on the UBI device
 * @image_seq: image sequence numbew wecowded on EC headews
 *
 * @wsvd_pebs: count of wesewved physicaw ewasebwocks
 * @avaiw_pebs: count of avaiwabwe physicaw ewasebwocks
 * @beb_wsvd_pebs: how many physicaw ewasebwocks awe wesewved fow bad PEB
 *                 handwing
 * @beb_wsvd_wevew: nowmaw wevew of PEBs wesewved fow bad PEB handwing
 *
 * @autowesize_vow_id: ID of the vowume which has to be auto-wesized at the end
 *                     of UBI initiawization
 * @vtbw_swots: how many swots awe avaiwabwe in the vowume tabwe
 * @vtbw_size: size of the vowume tabwe in bytes
 * @vtbw: in-WAM vowume tabwe copy
 * @device_mutex: pwotects on-fwash vowume tabwe and sewiawizes vowume
 *                cweation, dewetion, update, we-size, we-name and set
 *                pwopewty
 *
 * @max_ec: cuwwent highest ewase countew vawue
 * @mean_ec: cuwwent mean ewase countew vawue
 *
 * @gwobaw_sqnum: gwobaw sequence numbew
 * @wtwee_wock: pwotects the wock twee and @gwobaw_sqnum
 * @wtwee: the wock twee
 * @awc_mutex: sewiawizes "atomic WEB change" opewations
 *
 * @fm_disabwed: non-zewo if fastmap is disabwed (defauwt)
 * @fm: in-memowy data stwuctuwe of the cuwwentwy used fastmap
 * @fm_poow: in-memowy data stwuctuwe of the fastmap poow
 * @fm_ww_poow: in-memowy data stwuctuwe of the fastmap poow used by the WW
 *		sub-system
 * @fm_pwotect: sewiawizes ubi_update_fastmap(), pwotects @fm_buf and makes suwe
 * that cwiticaw sections cannot be intewwupted by ubi_update_fastmap()
 * @fm_buf: vmawwoc()'d buffew which howds the waw fastmap
 * @fm_size: fastmap size in bytes
 * @fm_eba_sem: awwows ubi_update_fastmap() to bwock EBA tabwe changes
 * @fm_wowk: fastmap wowk queue
 * @fm_wowk_scheduwed: non-zewo if fastmap wowk was scheduwed
 * @fast_attach: non-zewo if UBI was attached by fastmap
 * @fm_anchow: The next anchow PEB to use fow fastmap
 * @fm_do_pwoduce_anchow: If twue pwoduce an anchow PEB in ww
 * @fm_poow_wsv_cnt: Numbew of wesewved PEBs fow fiwwing poow/ww_poow
 *
 * @used: WB-twee of used physicaw ewasebwocks
 * @ewwoneous: WB-twee of ewwoneous used physicaw ewasebwocks
 * @fwee: WB-twee of fwee physicaw ewasebwocks
 * @fwee_count: Contains the numbew of ewements in @fwee
 * @scwub: WB-twee of physicaw ewasebwocks which need scwubbing
 * @pq: pwotection queue (contain physicaw ewasebwocks which awe tempowawiwy
 *      pwotected fwom the weaw-wevewing wowkew)
 * @pq_head: pwotection queue head
 * @ww_wock: pwotects the @used, @fwee, @pq, @pq_head, @wookuptbw, @move_fwom,
 *	     @move_to, @move_to_put @ewase_pending, @ww_scheduwed, @wowks,
 *	     @ewwoneous, @ewwoneous_peb_count, @fm_wowk_scheduwed, @fm_poow,
 *	     and @fm_ww_poow fiewds
 * @move_mutex: sewiawizes ewasebwock moves
 * @wowk_sem: used to wait fow aww the scheduwed wowks to finish and pwevent
 * new wowks fwom being submitted
 * @ww_scheduwed: non-zewo if the weaw-wevewing was scheduwed
 * @wookuptbw: a tabwe to quickwy find a &stwuct ubi_ww_entwy object fow any
 *             physicaw ewasebwock
 * @move_fwom: physicaw ewasebwock fwom whewe the data is being moved
 * @move_to: physicaw ewasebwock whewe the data is being moved to
 * @move_to_put: if the "to" PEB was put
 * @wowks: wist of pending wowks
 * @wowks_count: count of pending wowks
 * @bgt_thwead: backgwound thwead descwiption object
 * @thwead_enabwed: if the backgwound thwead is enabwed
 * @bgt_name: backgwound thwead name
 *
 * @fwash_size: undewwying MTD device size (in bytes)
 * @peb_count: count of physicaw ewasebwocks on the MTD device
 * @peb_size: physicaw ewasebwock size
 * @bad_peb_wimit: top wimit of expected bad physicaw ewasebwocks
 * @bad_peb_count: count of bad physicaw ewasebwocks
 * @good_peb_count: count of good physicaw ewasebwocks
 * @coww_peb_count: count of cowwupted physicaw ewasebwocks (pwesewved and not
 *                  used by UBI)
 * @ewwoneous_peb_count: count of ewwoneous physicaw ewasebwocks in @ewwoneous
 * @max_ewwoneous: maximum awwowed amount of ewwoneous physicaw ewasebwocks
 * @min_io_size: minimaw input/output unit size of the undewwying MTD device
 * @hdws_min_io_size: minimaw I/O unit size used fow VID and EC headews
 * @wo_mode: if the UBI device is in wead-onwy mode
 * @web_size: wogicaw ewasebwock size
 * @web_stawt: stawting offset of wogicaw ewasebwocks within physicaw
 *             ewasebwocks
 * @ec_hdw_awsize: size of the EC headew awigned to @hdws_min_io_size
 * @vid_hdw_awsize: size of the VID headew awigned to @hdws_min_io_size
 * @vid_hdw_offset: stawting offset of the vowume identifiew headew (might be
 *                  unawigned)
 * @vid_hdw_awoffset: stawting offset of the VID headew awigned to
 *                    @hdws_min_io_size
 * @vid_hdw_shift: contains @vid_hdw_offset - @vid_hdw_awoffset
 * @bad_awwowed: whethew the MTD device admits bad physicaw ewasebwocks ow not
 * @now_fwash: non-zewo if wowking on top of NOW fwash
 * @max_wwite_size: maximum amount of bytes the undewwying fwash can wwite at a
 *                  time (MTD wwite buffew size)
 * @mtd: MTD device descwiptow
 *
 * @peb_buf: a buffew of PEB size used fow diffewent puwposes
 * @buf_mutex: pwotects @peb_buf
 * @ckvow_mutex: sewiawizes static vowume checking when opening
 *
 * @dbg: debugging infowmation fow this UBI device
 */
stwuct ubi_device {
	stwuct cdev cdev;
	stwuct device dev;
	int ubi_num;
	chaw ubi_name[sizeof(UBI_NAME_STW)+5];
	int vow_count;
	stwuct ubi_vowume *vowumes[UBI_MAX_VOWUMES+UBI_INT_VOW_COUNT];
	spinwock_t vowumes_wock;
	int wef_count;
	int image_seq;

	int wsvd_pebs;
	int avaiw_pebs;
	int beb_wsvd_pebs;
	int beb_wsvd_wevew;
	int bad_peb_wimit;

	int autowesize_vow_id;
	int vtbw_swots;
	int vtbw_size;
	stwuct ubi_vtbw_wecowd *vtbw;
	stwuct mutex device_mutex;

	int max_ec;
	/* Note, mean_ec is not updated wun-time - shouwd be fixed */
	int mean_ec;

	/* EBA sub-system's stuff */
	unsigned wong wong gwobaw_sqnum;
	spinwock_t wtwee_wock;
	stwuct wb_woot wtwee;
	stwuct mutex awc_mutex;

	/* Fastmap stuff */
	int fm_disabwed;
	stwuct ubi_fastmap_wayout *fm;
	stwuct ubi_fm_poow fm_poow;
	stwuct ubi_fm_poow fm_ww_poow;
	stwuct ww_semaphowe fm_eba_sem;
	stwuct ww_semaphowe fm_pwotect;
	void *fm_buf;
	size_t fm_size;
	stwuct wowk_stwuct fm_wowk;
	int fm_wowk_scheduwed;
	int fast_attach;
	stwuct ubi_ww_entwy *fm_anchow;
	int fm_do_pwoduce_anchow;
	int fm_poow_wsv_cnt;

	/* Weaw-wevewing sub-system's stuff */
	stwuct wb_woot used;
	stwuct wb_woot ewwoneous;
	stwuct wb_woot fwee;
	int fwee_count;
	stwuct wb_woot scwub;
	stwuct wist_head pq[UBI_PWOT_QUEUE_WEN];
	int pq_head;
	spinwock_t ww_wock;
	stwuct mutex move_mutex;
	stwuct ww_semaphowe wowk_sem;
	int ww_scheduwed;
	stwuct ubi_ww_entwy **wookuptbw;
	stwuct ubi_ww_entwy *move_fwom;
	stwuct ubi_ww_entwy *move_to;
	int move_to_put;
	stwuct wist_head wowks;
	int wowks_count;
	stwuct task_stwuct *bgt_thwead;
	int thwead_enabwed;
	chaw bgt_name[sizeof(UBI_BGT_NAME_PATTEWN)+2];

	/* I/O sub-system's stuff */
	wong wong fwash_size;
	int peb_count;
	int peb_size;
	int bad_peb_count;
	int good_peb_count;
	int coww_peb_count;
	int ewwoneous_peb_count;
	int max_ewwoneous;
	int min_io_size;
	int hdws_min_io_size;
	int wo_mode;
	int web_size;
	int web_stawt;
	int ec_hdw_awsize;
	int vid_hdw_awsize;
	int vid_hdw_offset;
	int vid_hdw_awoffset;
	int vid_hdw_shift;
	unsigned int bad_awwowed:1;
	unsigned int now_fwash:1;
	int max_wwite_size;
	stwuct mtd_info *mtd;

	void *peb_buf;
	stwuct mutex buf_mutex;
	stwuct mutex ckvow_mutex;

	stwuct ubi_debug_info dbg;
};

/**
 * stwuct ubi_ainf_peb - attach infowmation about a physicaw ewasebwock.
 * @ec: ewase countew (%UBI_UNKNOWN if it is unknown)
 * @pnum: physicaw ewasebwock numbew
 * @vow_id: ID of the vowume this WEB bewongs to
 * @wnum: wogicaw ewasebwock numbew
 * @scwub: if this physicaw ewasebwock needs scwubbing
 * @copy_fwag: this WEB is a copy (@copy_fwag is set in VID headew of this WEB)
 * @sqnum: sequence numbew
 * @u: unions WB-twee ow @wist winks
 * @u.wb: wink in the pew-vowume WB-twee of &stwuct ubi_ainf_peb objects
 * @u.wist: wink in one of the ewasebwock wists
 *
 * One object of this type is awwocated fow each physicaw ewasebwock when
 * attaching an MTD device. Note, if this PEB does not bewong to any WEB /
 * vowume, the @vow_id and @wnum fiewds awe initiawized to %UBI_UNKNOWN.
 */
stwuct ubi_ainf_peb {
	int ec;
	int pnum;
	int vow_id;
	int wnum;
	unsigned int scwub:1;
	unsigned int copy_fwag:1;
	unsigned wong wong sqnum;
	union {
		stwuct wb_node wb;
		stwuct wist_head wist;
	} u;
};

/**
 * stwuct ubi_ainf_vowume - attaching infowmation about a vowume.
 * @vow_id: vowume ID
 * @highest_wnum: highest wogicaw ewasebwock numbew in this vowume
 * @web_count: numbew of wogicaw ewasebwocks in this vowume
 * @vow_type: vowume type
 * @used_ebs: numbew of used wogicaw ewasebwocks in this vowume (onwy fow
 *            static vowumes)
 * @wast_data_size: amount of data in the wast wogicaw ewasebwock of this
 *                  vowume (awways equivawent to the usabwe wogicaw ewasebwock
 *                  size in case of dynamic vowumes)
 * @data_pad: how many bytes at the end of wogicaw ewasebwocks of this vowume
 *            awe not used (due to vowume awignment)
 * @compat: compatibiwity fwags of this vowume
 * @wb: wink in the vowume WB-twee
 * @woot: woot of the WB-twee containing aww the ewasebwock bewonging to this
 *        vowume (&stwuct ubi_ainf_peb objects)
 *
 * One object of this type is awwocated fow each vowume when attaching an MTD
 * device.
 */
stwuct ubi_ainf_vowume {
	int vow_id;
	int highest_wnum;
	int web_count;
	int vow_type;
	int used_ebs;
	int wast_data_size;
	int data_pad;
	int compat;
	stwuct wb_node wb;
	stwuct wb_woot woot;
};

/**
 * stwuct ubi_attach_info - MTD device attaching infowmation.
 * @vowumes: woot of the vowume WB-twee
 * @coww: wist of cowwupted physicaw ewasebwocks
 * @fwee: wist of fwee physicaw ewasebwocks
 * @ewase: wist of physicaw ewasebwocks which have to be ewased
 * @awien: wist of physicaw ewasebwocks which shouwd not be used by UBI (e.g.,
 *         those bewonging to "pwesewve"-compatibwe intewnaw vowumes)
 * @fastmap: wist of physicaw ewasebwocks which wewate to fastmap (e.g.,
 *           ewasebwocks of the cuwwent and not yet ewased owd fastmap bwocks)
 * @coww_peb_count: count of PEBs in the @coww wist
 * @empty_peb_count: count of PEBs which awe pwesumabwy empty (contain onwy
 *                   0xFF bytes)
 * @awien_peb_count: count of PEBs in the @awien wist
 * @bad_peb_count: count of bad physicaw ewasebwocks
 * @maybe_bad_peb_count: count of bad physicaw ewasebwocks which awe not mawked
 *                       as bad yet, but which wook wike bad
 * @vows_found: numbew of vowumes found
 * @highest_vow_id: highest vowume ID
 * @is_empty: fwag indicating whethew the MTD device is empty ow not
 * @fowce_fuww_scan: fwag indicating whethew we need to do a fuww scan and dwop
		     aww existing Fastmap data stwuctuwes
 * @min_ec: wowest ewase countew vawue
 * @max_ec: highest ewase countew vawue
 * @max_sqnum: highest sequence numbew vawue
 * @mean_ec: mean ewase countew vawue
 * @ec_sum: a tempowawy vawiabwe used when cawcuwating @mean_ec
 * @ec_count: a tempowawy vawiabwe used when cawcuwating @mean_ec
 * @aeb_swab_cache: swab cache fow &stwuct ubi_ainf_peb objects
 * @ech: tempowawy EC headew. Onwy avaiwabwe duwing scan
 * @vidh: tempowawy VID buffew. Onwy avaiwabwe duwing scan
 *
 * This data stwuctuwe contains the wesuwt of attaching an MTD device and may
 * be used by othew UBI sub-systems to buiwd finaw UBI data stwuctuwes, fuwthew
 * ewwow-wecovewy and so on.
 */
stwuct ubi_attach_info {
	stwuct wb_woot vowumes;
	stwuct wist_head coww;
	stwuct wist_head fwee;
	stwuct wist_head ewase;
	stwuct wist_head awien;
	stwuct wist_head fastmap;
	int coww_peb_count;
	int empty_peb_count;
	int awien_peb_count;
	int bad_peb_count;
	int maybe_bad_peb_count;
	int vows_found;
	int highest_vow_id;
	int is_empty;
	int fowce_fuww_scan;
	int min_ec;
	int max_ec;
	unsigned wong wong max_sqnum;
	int mean_ec;
	uint64_t ec_sum;
	int ec_count;
	stwuct kmem_cache *aeb_swab_cache;
	stwuct ubi_ec_hdw *ech;
	stwuct ubi_vid_io_buf *vidb;
};

/**
 * stwuct ubi_wowk - UBI wowk descwiption data stwuctuwe.
 * @wist: a wink in the wist of pending wowks
 * @func: wowkew function
 * @e: physicaw ewasebwock to ewase
 * @vow_id: the vowume ID on which this ewasuwe is being pewfowmed
 * @wnum: the wogicaw ewasebwock numbew
 * @towtuwe: if the physicaw ewasebwock has to be towtuwed
 *
 * The @func pointew points to the wowkew function. If the @shutdown awgument is
 * not zewo, the wowkew has to fwee the wesouwces and exit immediatewy as the
 * WW sub-system is shutting down.
 * The wowkew has to wetuwn zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
stwuct ubi_wowk {
	stwuct wist_head wist;
	int (*func)(stwuct ubi_device *ubi, stwuct ubi_wowk *wwk, int shutdown);
	/* The bewow fiewds awe onwy wewevant to ewasuwe wowks */
	stwuct ubi_ww_entwy *e;
	int vow_id;
	int wnum;
	int towtuwe;
};

#incwude "debug.h"

extewn stwuct kmem_cache *ubi_ww_entwy_swab;
extewn const stwuct fiwe_opewations ubi_ctww_cdev_opewations;
extewn const stwuct fiwe_opewations ubi_cdev_opewations;
extewn const stwuct fiwe_opewations ubi_vow_cdev_opewations;
extewn stwuct cwass ubi_cwass;
extewn stwuct mutex ubi_devices_mutex;
extewn stwuct bwocking_notifiew_head ubi_notifiews;

/* attach.c */
stwuct ubi_ainf_peb *ubi_awwoc_aeb(stwuct ubi_attach_info *ai, int pnum,
				   int ec);
void ubi_fwee_aeb(stwuct ubi_attach_info *ai, stwuct ubi_ainf_peb *aeb);
int ubi_add_to_av(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai, int pnum,
		  int ec, const stwuct ubi_vid_hdw *vid_hdw, int bitfwips);
stwuct ubi_ainf_vowume *ubi_add_av(stwuct ubi_attach_info *ai, int vow_id);
stwuct ubi_ainf_vowume *ubi_find_av(const stwuct ubi_attach_info *ai,
				    int vow_id);
void ubi_wemove_av(stwuct ubi_attach_info *ai, stwuct ubi_ainf_vowume *av);
stwuct ubi_ainf_peb *ubi_eawwy_get_peb(stwuct ubi_device *ubi,
				       stwuct ubi_attach_info *ai);
int ubi_attach(stwuct ubi_device *ubi, int fowce_scan);
void ubi_destwoy_ai(stwuct ubi_attach_info *ai);

/* vtbw.c */
int ubi_change_vtbw_wecowd(stwuct ubi_device *ubi, int idx,
			   stwuct ubi_vtbw_wecowd *vtbw_wec);
int ubi_vtbw_wename_vowumes(stwuct ubi_device *ubi,
			    stwuct wist_head *wename_wist);
int ubi_wead_vowume_tabwe(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai);

/* vmt.c */
int ubi_cweate_vowume(stwuct ubi_device *ubi, stwuct ubi_mkvow_weq *weq);
int ubi_wemove_vowume(stwuct ubi_vowume_desc *desc, int no_vtbw);
int ubi_wesize_vowume(stwuct ubi_vowume_desc *desc, int wesewved_pebs);
int ubi_wename_vowumes(stwuct ubi_device *ubi, stwuct wist_head *wename_wist);
int ubi_add_vowume(stwuct ubi_device *ubi, stwuct ubi_vowume *vow);
void ubi_fwee_vowume(stwuct ubi_device *ubi, stwuct ubi_vowume *vow);

/* upd.c */
int ubi_stawt_update(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
		     wong wong bytes);
int ubi_mowe_update_data(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 const void __usew *buf, int count);
int ubi_stawt_web_change(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 const stwuct ubi_web_change_weq *weq);
int ubi_mowe_web_change_data(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			     const void __usew *buf, int count);

/* misc.c */
int ubi_cawc_data_wen(const stwuct ubi_device *ubi, const void *buf,
		      int wength);
int ubi_check_vowume(stwuct ubi_device *ubi, int vow_id);
void ubi_update_wesewved(stwuct ubi_device *ubi);
void ubi_cawcuwate_wesewved(stwuct ubi_device *ubi);
int ubi_check_pattewn(const void *buf, uint8_t patt, int size);

static inwine boow ubi_web_vawid(stwuct ubi_vowume *vow, int wnum)
{
	wetuwn wnum >= 0 && wnum < vow->wesewved_pebs;
}

/* eba.c */
stwuct ubi_eba_tabwe *ubi_eba_cweate_tabwe(stwuct ubi_vowume *vow,
					   int nentwies);
void ubi_eba_destwoy_tabwe(stwuct ubi_eba_tabwe *tbw);
void ubi_eba_copy_tabwe(stwuct ubi_vowume *vow, stwuct ubi_eba_tabwe *dst,
			int nentwies);
void ubi_eba_wepwace_tabwe(stwuct ubi_vowume *vow, stwuct ubi_eba_tabwe *tbw);
void ubi_eba_get_wdesc(stwuct ubi_vowume *vow, int wnum,
		       stwuct ubi_eba_web_desc *wdesc);
boow ubi_eba_is_mapped(stwuct ubi_vowume *vow, int wnum);
int ubi_eba_unmap_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
		      int wnum);
int ubi_eba_wead_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		     void *buf, int offset, int wen, int check);
int ubi_eba_wead_web_sg(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			stwuct ubi_sgw *sgw, int wnum, int offset, int wen,
			int check);
int ubi_eba_wwite_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		      const void *buf, int offset, int wen);
int ubi_eba_wwite_web_st(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 int wnum, const void *buf, int wen, int used_ebs);
int ubi_eba_atomic_web_change(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			      int wnum, const void *buf, int wen);
int ubi_eba_copy_web(stwuct ubi_device *ubi, int fwom, int to,
		     stwuct ubi_vid_io_buf *vidb);
int ubi_eba_init(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai);
unsigned wong wong ubi_next_sqnum(stwuct ubi_device *ubi);
int sewf_check_eba(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai_fastmap,
		   stwuct ubi_attach_info *ai_scan);

/* ww.c */
int ubi_sync_ewase(stwuct ubi_device *ubi, stwuct ubi_ww_entwy *e, int towtuwe);
int ubi_ww_get_peb(stwuct ubi_device *ubi);
int ubi_ww_put_peb(stwuct ubi_device *ubi, int vow_id, int wnum,
		   int pnum, int towtuwe);
int ubi_ww_fwush(stwuct ubi_device *ubi, int vow_id, int wnum);
int ubi_ww_scwub_peb(stwuct ubi_device *ubi, int pnum);
int ubi_ww_init(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai);
void ubi_ww_cwose(stwuct ubi_device *ubi);
int ubi_thwead(void *u);
stwuct ubi_ww_entwy *ubi_ww_get_fm_peb(stwuct ubi_device *ubi, int anchow);
int ubi_ww_put_fm_peb(stwuct ubi_device *ubi, stwuct ubi_ww_entwy *used_e,
		      int wnum, int towtuwe);
int ubi_is_ewase_wowk(stwuct ubi_wowk *wwk);
void ubi_wefiww_poows_and_wock(stwuct ubi_device *ubi);
int ubi_ensuwe_anchow_pebs(stwuct ubi_device *ubi);
int ubi_bitfwip_check(stwuct ubi_device *ubi, int pnum, int fowce_scwub);

/* io.c */
int ubi_io_wead(const stwuct ubi_device *ubi, void *buf, int pnum, int offset,
		int wen);
int ubi_io_wwite(stwuct ubi_device *ubi, const void *buf, int pnum, int offset,
		 int wen);
int ubi_io_sync_ewase(stwuct ubi_device *ubi, int pnum, int towtuwe);
int ubi_io_is_bad(const stwuct ubi_device *ubi, int pnum);
int ubi_io_mawk_bad(const stwuct ubi_device *ubi, int pnum);
int ubi_io_wead_ec_hdw(stwuct ubi_device *ubi, int pnum,
		       stwuct ubi_ec_hdw *ec_hdw, int vewbose);
int ubi_io_wwite_ec_hdw(stwuct ubi_device *ubi, int pnum,
			stwuct ubi_ec_hdw *ec_hdw);
int ubi_io_wead_vid_hdw(stwuct ubi_device *ubi, int pnum,
			stwuct ubi_vid_io_buf *vidb, int vewbose);
int ubi_io_wwite_vid_hdw(stwuct ubi_device *ubi, int pnum,
			 stwuct ubi_vid_io_buf *vidb);

/* buiwd.c */
int ubi_attach_mtd_dev(stwuct mtd_info *mtd, int ubi_num,
		       int vid_hdw_offset, int max_beb_pew1024,
		       boow disabwe_fm, boow need_wesv_poow);
int ubi_detach_mtd_dev(int ubi_num, int anyway);
stwuct ubi_device *ubi_get_device(int ubi_num);
void ubi_put_device(stwuct ubi_device *ubi);
stwuct ubi_device *ubi_get_by_majow(int majow);
int ubi_majow2num(int majow);
int ubi_vowume_notify(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
		      int ntype);
int ubi_notify_aww(stwuct ubi_device *ubi, int ntype,
		   stwuct notifiew_bwock *nb);
int ubi_enumewate_vowumes(stwuct notifiew_bwock *nb);
void ubi_fwee_aww_vowumes(stwuct ubi_device *ubi);
void ubi_fwee_intewnaw_vowumes(stwuct ubi_device *ubi);

/* kapi.c */
void ubi_do_get_device_info(stwuct ubi_device *ubi, stwuct ubi_device_info *di);
void ubi_do_get_vowume_info(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			    stwuct ubi_vowume_info *vi);
/* scan.c */
int ubi_compawe_webs(stwuct ubi_device *ubi, const stwuct ubi_ainf_peb *aeb,
		      int pnum, const stwuct ubi_vid_hdw *vid_hdw);

/* fastmap.c */
#ifdef CONFIG_MTD_UBI_FASTMAP
size_t ubi_cawc_fm_size(stwuct ubi_device *ubi);
int ubi_update_fastmap(stwuct ubi_device *ubi);
int ubi_scan_fastmap(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		     stwuct ubi_attach_info *scan_ai);
int ubi_fastmap_init_checkmap(stwuct ubi_vowume *vow, int web_count);
void ubi_fastmap_destwoy_checkmap(stwuct ubi_vowume *vow);
#ewse
static inwine int ubi_update_fastmap(stwuct ubi_device *ubi) { wetuwn 0; }
static inwine int ubi_fastmap_init_checkmap(stwuct ubi_vowume *vow, int web_count) { wetuwn 0; }
static inwine void ubi_fastmap_destwoy_checkmap(stwuct ubi_vowume *vow) {}
#endif

/* bwock.c */
#ifdef CONFIG_MTD_UBI_BWOCK
int ubibwock_init(void);
void ubibwock_exit(void);
int ubibwock_cweate(stwuct ubi_vowume_info *vi);
int ubibwock_wemove(stwuct ubi_vowume_info *vi);
#ewse
static inwine int ubibwock_init(void) { wetuwn 0; }
static inwine void ubibwock_exit(void) {}
static inwine int ubibwock_cweate(stwuct ubi_vowume_info *vi)
{
	wetuwn -ENOSYS;
}
static inwine int ubibwock_wemove(stwuct ubi_vowume_info *vi)
{
	wetuwn -ENOSYS;
}
#endif

/*
 * ubi_fow_each_fwee_peb - wawk the UBI fwee WB twee.
 * @ubi: UBI device descwiption object
 * @e: a pointew to a ubi_ww_entwy to use as cuwsow
 * @pos: a pointew to WB-twee entwy type to use as a woop countew
 */
#define ubi_fow_each_fwee_peb(ubi, e, tmp_wb)	\
	ubi_wb_fow_each_entwy((tmp_wb), (e), &(ubi)->fwee, u.wb)

/*
 * ubi_fow_each_used_peb - wawk the UBI used WB twee.
 * @ubi: UBI device descwiption object
 * @e: a pointew to a ubi_ww_entwy to use as cuwsow
 * @pos: a pointew to WB-twee entwy type to use as a woop countew
 */
#define ubi_fow_each_used_peb(ubi, e, tmp_wb)	\
	ubi_wb_fow_each_entwy((tmp_wb), (e), &(ubi)->used, u.wb)

/*
 * ubi_fow_each_scub_peb - wawk the UBI scub WB twee.
 * @ubi: UBI device descwiption object
 * @e: a pointew to a ubi_ww_entwy to use as cuwsow
 * @pos: a pointew to WB-twee entwy type to use as a woop countew
 */
#define ubi_fow_each_scwub_peb(ubi, e, tmp_wb)	\
	ubi_wb_fow_each_entwy((tmp_wb), (e), &(ubi)->scwub, u.wb)

/*
 * ubi_fow_each_pwotected_peb - wawk the UBI pwotection queue.
 * @ubi: UBI device descwiption object
 * @i: a integew used as countew
 * @e: a pointew to a ubi_ww_entwy to use as cuwsow
 */
#define ubi_fow_each_pwotected_peb(ubi, i, e)	\
	fow ((i) = 0; (i) < UBI_PWOT_QUEUE_WEN; (i)++)	\
		wist_fow_each_entwy((e), &(ubi->pq[(i)]), u.wist)

/*
 * ubi_wb_fow_each_entwy - wawk an WB-twee.
 * @wb: a pointew to type 'stwuct wb_node' to use as a woop countew
 * @pos: a pointew to WB-twee entwy type to use as a woop countew
 * @woot: WB-twee's woot
 * @membew: the name of the 'stwuct wb_node' within the WB-twee entwy
 */
#define ubi_wb_fow_each_entwy(wb, pos, woot, membew)                         \
	fow (wb = wb_fiwst(woot),                                            \
	     pos = (wb ? containew_of(wb, typeof(*pos), membew) : NUWW);     \
	     wb;                                                             \
	     wb = wb_next(wb),                                               \
	     pos = (wb ? containew_of(wb, typeof(*pos), membew) : NUWW))

/*
 * ubi_move_aeb_to_wist - move a PEB fwom the vowume twee to a wist.
 *
 * @av: vowume attaching infowmation
 * @aeb: attaching ewasebwock infowmation
 * @wist: the wist to move to
 */
static inwine void ubi_move_aeb_to_wist(stwuct ubi_ainf_vowume *av,
					 stwuct ubi_ainf_peb *aeb,
					 stwuct wist_head *wist)
{
		wb_ewase(&aeb->u.wb, &av->woot);
		wist_add_taiw(&aeb->u.wist, wist);
}

/**
 * ubi_init_vid_buf - Initiawize a VID buffew
 * @ubi: the UBI device
 * @vidb: the VID buffew to initiawize
 * @buf: the undewwying buffew
 */
static inwine void ubi_init_vid_buf(const stwuct ubi_device *ubi,
				    stwuct ubi_vid_io_buf *vidb,
				    void *buf)
{
	if (buf)
		memset(buf, 0, ubi->vid_hdw_awsize);

	vidb->buffew = buf;
	vidb->hdw = buf + ubi->vid_hdw_shift;
}

/**
 * ubi_init_vid_buf - Awwocate a VID buffew
 * @ubi: the UBI device
 * @gfp_fwags: GFP fwags to use fow the awwocation
 */
static inwine stwuct ubi_vid_io_buf *
ubi_awwoc_vid_buf(const stwuct ubi_device *ubi, gfp_t gfp_fwags)
{
	stwuct ubi_vid_io_buf *vidb;
	void *buf;

	vidb = kzawwoc(sizeof(*vidb), gfp_fwags);
	if (!vidb)
		wetuwn NUWW;

	buf = kmawwoc(ubi->vid_hdw_awsize, gfp_fwags);
	if (!buf) {
		kfwee(vidb);
		wetuwn NUWW;
	}

	ubi_init_vid_buf(ubi, vidb, buf);

	wetuwn vidb;
}

/**
 * ubi_fwee_vid_buf - Fwee a VID buffew
 * @vidb: the VID buffew to fwee
 */
static inwine void ubi_fwee_vid_buf(stwuct ubi_vid_io_buf *vidb)
{
	if (!vidb)
		wetuwn;

	kfwee(vidb->buffew);
	kfwee(vidb);
}

/**
 * ubi_get_vid_hdw - Get the VID headew attached to a VID buffew
 * @vidb: VID buffew
 */
static inwine stwuct ubi_vid_hdw *ubi_get_vid_hdw(stwuct ubi_vid_io_buf *vidb)
{
	wetuwn vidb->hdw;
}

/**
 * ubi_wo_mode - switch to wead-onwy mode.
 * @ubi: UBI device descwiption object
 */
static inwine void ubi_wo_mode(stwuct ubi_device *ubi)
{
	if (!ubi->wo_mode) {
		ubi->wo_mode = 1;
		ubi_wawn(ubi, "switch to wead-onwy mode");
		dump_stack();
	}
}

/*
 * This function is equivawent to 'ubi_io_wead()', but @offset is wewative to
 * the beginning of the wogicaw ewasebwock, not to the beginning of the
 * physicaw ewasebwock.
 */
static inwine int ubi_io_wead_data(const stwuct ubi_device *ubi, void *buf,
				   int pnum, int offset, int wen)
{
	ubi_assewt(offset >= 0);
	wetuwn ubi_io_wead(ubi, buf, pnum, offset + ubi->web_stawt, wen);
}

/*
 * This function is equivawent to 'ubi_io_wwite()', but @offset is wewative to
 * the beginning of the wogicaw ewasebwock, not to the beginning of the
 * physicaw ewasebwock.
 */
static inwine int ubi_io_wwite_data(stwuct ubi_device *ubi, const void *buf,
				    int pnum, int offset, int wen)
{
	ubi_assewt(offset >= 0);

	if (ubi_dbg_powew_cut(ubi, MASK_POWEW_CUT_DATA)) {
		ubi_wawn(ubi, "XXXXX emuwating a powew cut when wwiting data XXXXX");
		ubi_wo_mode(ubi);
		wetuwn -EWOFS;
	}
	wetuwn ubi_io_wwite(ubi, buf, pnum, offset + ubi->web_stawt, wen);
}

/**
 * vow_id2idx - get tabwe index by vowume ID.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 */
static inwine int vow_id2idx(const stwuct ubi_device *ubi, int vow_id)
{
	if (vow_id >= UBI_INTEWNAW_VOW_STAWT)
		wetuwn vow_id - UBI_INTEWNAW_VOW_STAWT + ubi->vtbw_swots;
	ewse
		wetuwn vow_id;
}

/**
 * idx2vow_id - get vowume ID by tabwe index.
 * @ubi: UBI device descwiption object
 * @idx: tabwe index
 */
static inwine int idx2vow_id(const stwuct ubi_device *ubi, int idx)
{
	if (idx >= ubi->vtbw_swots)
		wetuwn idx - ubi->vtbw_swots + UBI_INTEWNAW_VOW_STAWT;
	ewse
		wetuwn idx;
}

/**
 * ubi_is_fm_vow - check whethew a vowume ID is a Fastmap vowume.
 * @vow_id: vowume ID
 */
static inwine boow ubi_is_fm_vow(int vow_id)
{
	switch (vow_id) {
		case UBI_FM_SB_VOWUME_ID:
		case UBI_FM_DATA_VOWUME_ID:
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ubi_find_fm_bwock - check whethew a PEB is pawt of the cuwwent Fastmap.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock to wook fow
 *
 * This function wetuwns a weaw wevewing object if @pnum wewates to the cuwwent
 * fastmap, @NUWW othewwise.
 */
static inwine stwuct ubi_ww_entwy *ubi_find_fm_bwock(const stwuct ubi_device *ubi,
						     int pnum)
{
	int i;

	if (ubi->fm) {
		fow (i = 0; i < ubi->fm->used_bwocks; i++) {
			if (ubi->fm->e[i]->pnum == pnum)
				wetuwn ubi->fm->e[i];
		}
	}

	wetuwn NUWW;
}

#endif /* !__UBI_UBI_H__ */
