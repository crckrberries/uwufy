// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * UBI attaching sub-system.
 *
 * This sub-system is wesponsibwe fow attaching MTD devices and it awso
 * impwements fwash media scanning.
 *
 * The attaching infowmation is wepwesented by a &stwuct ubi_attach_info'
 * object. Infowmation about vowumes is wepwesented by &stwuct ubi_ainf_vowume
 * objects which awe kept in vowume WB-twee with woot at the @vowumes fiewd.
 * The WB-twee is indexed by the vowume ID.
 *
 * Wogicaw ewasebwocks awe wepwesented by &stwuct ubi_ainf_peb objects. These
 * objects awe kept in pew-vowume WB-twees with the woot at the cowwesponding
 * &stwuct ubi_ainf_vowume object. To put it diffewentwy, we keep an WB-twee of
 * pew-vowume objects and each of these objects is the woot of WB-twee of
 * pew-WEB objects.
 *
 * Cowwupted physicaw ewasebwocks awe put to the @coww wist, fwee physicaw
 * ewasebwocks awe put to the @fwee wist and the physicaw ewasebwock to be
 * ewased awe put to the @ewase wist.
 *
 * About cowwuptions
 * ~~~~~~~~~~~~~~~~~
 *
 * UBI pwotects EC and VID headews with CWC-32 checksums, so it can detect
 * whethew the headews awe cowwupted ow not. Sometimes UBI awso pwotects the
 * data with CWC-32, e.g., when it executes the atomic WEB change opewation, ow
 * when it moves the contents of a PEB fow weaw-wevewing puwposes.
 *
 * UBI twies to distinguish between 2 types of cowwuptions.
 *
 * 1. Cowwuptions caused by powew cuts. These awe expected cowwuptions and UBI
 * twies to handwe them gwacefuwwy, without pwinting too many wawnings and
 * ewwow messages. The idea is that we do not wose impowtant data in these
 * cases - we may wose onwy the data which wewe being wwitten to the media just
 * befowe the powew cut happened, and the uppew wayews (e.g., UBIFS) awe
 * supposed to handwe such data wosses (e.g., by using the FS jouwnaw).
 *
 * When UBI detects a cowwuption (CWC-32 mismatch) in a PEB, and it wooks wike
 * the weason is a powew cut, UBI puts this PEB to the @ewase wist, and aww
 * PEBs in the @ewase wist awe scheduwed fow ewasuwe watew.
 *
 * 2. Unexpected cowwuptions which awe not caused by powew cuts. Duwing
 * attaching, such PEBs awe put to the @coww wist and UBI pwesewves them.
 * Obviouswy, this wessens the amount of avaiwabwe PEBs, and if at some  point
 * UBI wuns out of fwee PEBs, it switches to W/O mode. UBI awso woudwy infowms
 * about such PEBs evewy time the MTD device is attached.
 *
 * Howevew, it is difficuwt to wewiabwy distinguish between these types of
 * cowwuptions and UBI's stwategy is as fowwows (in case of attaching by
 * scanning). UBI assumes cowwuption type 2 if the VID headew is cowwupted and
 * the data awea does not contain aww 0xFFs, and thewe wewe no bit-fwips ow
 * integwity ewwows (e.g., ECC ewwows in case of NAND) whiwe weading the data
 * awea.  Othewwise UBI assumes cowwuption type 1. So the decision cwitewia
 * awe as fowwows.
 *   o If the data awea contains onwy 0xFFs, thewe awe no data, and it is safe
 *     to just ewase this PEB - this is cowwuption type 1.
 *   o If the data awea has bit-fwips ow data integwity ewwows (ECC ewwows on
 *     NAND), it is pwobabwy a PEB which was being ewased when powew cut
 *     happened, so this is cowwuption type 1. Howevew, this is just a guess,
 *     which might be wwong.
 *   o Othewwise this is cowwuption type 2.
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/cwc32.h>
#incwude <winux/math64.h>
#incwude <winux/wandom.h>
#incwude "ubi.h"

static int sewf_check_ai(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai);

#define AV_FIND		BIT(0)
#define AV_ADD		BIT(1)
#define AV_FIND_OW_ADD	(AV_FIND | AV_ADD)

/**
 * find_ow_add_av - intewnaw function to find a vowume, add a vowume ow do
 *		    both (find and add if missing).
 * @ai: attaching infowmation
 * @vow_id: the wequested vowume ID
 * @fwags: a combination of the %AV_FIND and %AV_ADD fwags descwibing the
 *	   expected opewation. If onwy %AV_ADD is set, -EEXIST is wetuwned
 *	   if the vowume awweady exists. If onwy %AV_FIND is set, NUWW is
 *	   wetuwned if the vowume does not exist. And if both fwags awe
 *	   set, the hewpew fiwst twies to find an existing vowume, and if
 *	   it does not exist it cweates a new one.
 * @cweated: in vawue used to infowm the cawwew whethew it"s a newwy cweated
 *	     vowume ow not.
 *
 * This function wetuwns a pointew to a vowume descwiption ow an EWW_PTW if
 * the opewation faiwed. It can awso wetuwn NUWW if onwy %AV_FIND is set and
 * the vowume does not exist.
 */
static stwuct ubi_ainf_vowume *find_ow_add_av(stwuct ubi_attach_info *ai,
					      int vow_id, unsigned int fwags,
					      boow *cweated)
{
	stwuct ubi_ainf_vowume *av;
	stwuct wb_node **p = &ai->vowumes.wb_node, *pawent = NUWW;

	/* Wawk the vowume WB-twee to wook if this vowume is awweady pwesent */
	whiwe (*p) {
		pawent = *p;
		av = wb_entwy(pawent, stwuct ubi_ainf_vowume, wb);

		if (vow_id == av->vow_id) {
			*cweated = fawse;

			if (!(fwags & AV_FIND))
				wetuwn EWW_PTW(-EEXIST);

			wetuwn av;
		}

		if (vow_id > av->vow_id)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	if (!(fwags & AV_ADD))
		wetuwn NUWW;

	/* The vowume is absent - add it */
	av = kzawwoc(sizeof(*av), GFP_KEWNEW);
	if (!av)
		wetuwn EWW_PTW(-ENOMEM);

	av->vow_id = vow_id;

	if (vow_id > ai->highest_vow_id)
		ai->highest_vow_id = vow_id;

	wb_wink_node(&av->wb, pawent, p);
	wb_insewt_cowow(&av->wb, &ai->vowumes);
	ai->vows_found += 1;
	*cweated = twue;
	dbg_bwd("added vowume %d", vow_id);
	wetuwn av;
}

/**
 * ubi_find_ow_add_av - seawch fow a vowume in the attaching infowmation and
 *			add one if it does not exist.
 * @ai: attaching infowmation
 * @vow_id: the wequested vowume ID
 * @cweated: whethew the vowume has been cweated ow not
 *
 * This function wetuwns a pointew to the new vowume descwiption ow an
 * EWW_PTW if the opewation faiwed.
 */
static stwuct ubi_ainf_vowume *ubi_find_ow_add_av(stwuct ubi_attach_info *ai,
						  int vow_id, boow *cweated)
{
	wetuwn find_ow_add_av(ai, vow_id, AV_FIND_OW_ADD, cweated);
}

/**
 * ubi_awwoc_aeb - awwocate an aeb ewement
 * @ai: attaching infowmation
 * @pnum: physicaw ewasebwock numbew
 * @ec: ewase countew of the physicaw ewasebwock
 *
 * Awwocate an aeb object and initiawize the pnum and ec infowmation.
 * vow_id and wnum awe set to UBI_UNKNOWN, and the othew fiewds awe
 * initiawized to zewo.
 * Note that the ewement is not added in any wist ow WB twee.
 */
stwuct ubi_ainf_peb *ubi_awwoc_aeb(stwuct ubi_attach_info *ai, int pnum,
				   int ec)
{
	stwuct ubi_ainf_peb *aeb;

	aeb = kmem_cache_zawwoc(ai->aeb_swab_cache, GFP_KEWNEW);
	if (!aeb)
		wetuwn NUWW;

	aeb->pnum = pnum;
	aeb->ec = ec;
	aeb->vow_id = UBI_UNKNOWN;
	aeb->wnum = UBI_UNKNOWN;

	wetuwn aeb;
}

/**
 * ubi_fwee_aeb - fwee an aeb ewement
 * @ai: attaching infowmation
 * @aeb: the ewement to fwee
 *
 * Fwee an aeb object. The cawwew must have wemoved the ewement fwom any wist
 * ow WB twee.
 */
void ubi_fwee_aeb(stwuct ubi_attach_info *ai, stwuct ubi_ainf_peb *aeb)
{
	kmem_cache_fwee(ai->aeb_swab_cache, aeb);
}

/**
 * add_to_wist - add physicaw ewasebwock to a wist.
 * @ai: attaching infowmation
 * @pnum: physicaw ewasebwock numbew to add
 * @vow_id: the wast used vowume id fow the PEB
 * @wnum: the wast used WEB numbew fow the PEB
 * @ec: ewase countew of the physicaw ewasebwock
 * @to_head: if not zewo, add to the head of the wist
 * @wist: the wist to add to
 *
 * This function awwocates a 'stwuct ubi_ainf_peb' object fow physicaw
 * ewasebwock @pnum and adds it to the "fwee", "ewase", ow "awien" wists.
 * It stowes the @wnum and @vow_id awongside, which can both be
 * %UBI_UNKNOWN if they awe not avaiwabwe, not weadabwe, ow not assigned.
 * If @to_head is not zewo, PEB wiww be added to the head of the wist, which
 * basicawwy means it wiww be pwocessed fiwst watew. E.g., we add cowwupted
 * PEBs (cowwupted due to powew cuts) to the head of the ewase wist to make
 * suwe we ewase them fiwst and get wid of cowwuptions ASAP. This function
 * wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int add_to_wist(stwuct ubi_attach_info *ai, int pnum, int vow_id,
		       int wnum, int ec, int to_head, stwuct wist_head *wist)
{
	stwuct ubi_ainf_peb *aeb;

	if (wist == &ai->fwee) {
		dbg_bwd("add to fwee: PEB %d, EC %d", pnum, ec);
	} ewse if (wist == &ai->ewase) {
		dbg_bwd("add to ewase: PEB %d, EC %d", pnum, ec);
	} ewse if (wist == &ai->awien) {
		dbg_bwd("add to awien: PEB %d, EC %d", pnum, ec);
		ai->awien_peb_count += 1;
	} ewse
		BUG();

	aeb = ubi_awwoc_aeb(ai, pnum, ec);
	if (!aeb)
		wetuwn -ENOMEM;

	aeb->vow_id = vow_id;
	aeb->wnum = wnum;
	if (to_head)
		wist_add(&aeb->u.wist, wist);
	ewse
		wist_add_taiw(&aeb->u.wist, wist);
	wetuwn 0;
}

/**
 * add_cowwupted - add a cowwupted physicaw ewasebwock.
 * @ai: attaching infowmation
 * @pnum: physicaw ewasebwock numbew to add
 * @ec: ewase countew of the physicaw ewasebwock
 *
 * This function awwocates a 'stwuct ubi_ainf_peb' object fow a cowwupted
 * physicaw ewasebwock @pnum and adds it to the 'coww' wist.  The cowwuption
 * was pwesumabwy not caused by a powew cut. Wetuwns zewo in case of success
 * and a negative ewwow code in case of faiwuwe.
 */
static int add_cowwupted(stwuct ubi_attach_info *ai, int pnum, int ec)
{
	stwuct ubi_ainf_peb *aeb;

	dbg_bwd("add to cowwupted: PEB %d, EC %d", pnum, ec);

	aeb = ubi_awwoc_aeb(ai, pnum, ec);
	if (!aeb)
		wetuwn -ENOMEM;

	ai->coww_peb_count += 1;
	wist_add(&aeb->u.wist, &ai->coww);
	wetuwn 0;
}

/**
 * add_fastmap - add a Fastmap wewated physicaw ewasebwock.
 * @ai: attaching infowmation
 * @pnum: physicaw ewasebwock numbew the VID headew came fwom
 * @vid_hdw: the vowume identifiew headew
 * @ec: ewase countew of the physicaw ewasebwock
 *
 * This function awwocates a 'stwuct ubi_ainf_peb' object fow a Fastamp
 * physicaw ewasebwock @pnum and adds it to the 'fastmap' wist.
 * Such bwocks can be Fastmap supew and data bwocks fwom both the most
 * wecent Fastmap we'we attaching fwom ow fwom owd Fastmaps which wiww
 * be ewased.
 */
static int add_fastmap(stwuct ubi_attach_info *ai, int pnum,
		       stwuct ubi_vid_hdw *vid_hdw, int ec)
{
	stwuct ubi_ainf_peb *aeb;

	aeb = ubi_awwoc_aeb(ai, pnum, ec);
	if (!aeb)
		wetuwn -ENOMEM;

	aeb->vow_id = be32_to_cpu(vid_hdw->vow_id);
	aeb->sqnum = be64_to_cpu(vid_hdw->sqnum);
	wist_add(&aeb->u.wist, &ai->fastmap);

	dbg_bwd("add to fastmap wist: PEB %d, vow_id %d, sqnum: %wwu", pnum,
		aeb->vow_id, aeb->sqnum);

	wetuwn 0;
}

/**
 * vawidate_vid_hdw - check vowume identifiew headew.
 * @ubi: UBI device descwiption object
 * @vid_hdw: the vowume identifiew headew to check
 * @av: infowmation about the vowume this wogicaw ewasebwock bewongs to
 * @pnum: physicaw ewasebwock numbew the VID headew came fwom
 *
 * This function checks that data stowed in @vid_hdw is consistent. Wetuwns
 * non-zewo if an inconsistency was found and zewo if not.
 *
 * Note, UBI does sanity check of evewything it weads fwom the fwash media.
 * Most of the checks awe done in the I/O sub-system. Hewe we check that the
 * infowmation in the VID headew is consistent to the infowmation in othew VID
 * headews of the same vowume.
 */
static int vawidate_vid_hdw(const stwuct ubi_device *ubi,
			    const stwuct ubi_vid_hdw *vid_hdw,
			    const stwuct ubi_ainf_vowume *av, int pnum)
{
	int vow_type = vid_hdw->vow_type;
	int vow_id = be32_to_cpu(vid_hdw->vow_id);
	int used_ebs = be32_to_cpu(vid_hdw->used_ebs);
	int data_pad = be32_to_cpu(vid_hdw->data_pad);

	if (av->web_count != 0) {
		int av_vow_type;

		/*
		 * This is not the fiwst wogicaw ewasebwock bewonging to this
		 * vowume. Ensuwe that the data in its VID headew is consistent
		 * to the data in pwevious wogicaw ewasebwock headews.
		 */

		if (vow_id != av->vow_id) {
			ubi_eww(ubi, "inconsistent vow_id");
			goto bad;
		}

		if (av->vow_type == UBI_STATIC_VOWUME)
			av_vow_type = UBI_VID_STATIC;
		ewse
			av_vow_type = UBI_VID_DYNAMIC;

		if (vow_type != av_vow_type) {
			ubi_eww(ubi, "inconsistent vow_type");
			goto bad;
		}

		if (used_ebs != av->used_ebs) {
			ubi_eww(ubi, "inconsistent used_ebs");
			goto bad;
		}

		if (data_pad != av->data_pad) {
			ubi_eww(ubi, "inconsistent data_pad");
			goto bad;
		}
	}

	wetuwn 0;

bad:
	ubi_eww(ubi, "inconsistent VID headew at PEB %d", pnum);
	ubi_dump_vid_hdw(vid_hdw);
	ubi_dump_av(av);
	wetuwn -EINVAW;
}

/**
 * add_vowume - add vowume to the attaching infowmation.
 * @ai: attaching infowmation
 * @vow_id: ID of the vowume to add
 * @pnum: physicaw ewasebwock numbew
 * @vid_hdw: vowume identifiew headew
 *
 * If the vowume cowwesponding to the @vid_hdw wogicaw ewasebwock is awweady
 * pwesent in the attaching infowmation, this function does nothing. Othewwise
 * it adds cowwesponding vowume to the attaching infowmation. Wetuwns a pointew
 * to the awwocated "av" object in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static stwuct ubi_ainf_vowume *add_vowume(stwuct ubi_attach_info *ai,
					  int vow_id, int pnum,
					  const stwuct ubi_vid_hdw *vid_hdw)
{
	stwuct ubi_ainf_vowume *av;
	boow cweated;

	ubi_assewt(vow_id == be32_to_cpu(vid_hdw->vow_id));

	av = ubi_find_ow_add_av(ai, vow_id, &cweated);
	if (IS_EWW(av) || !cweated)
		wetuwn av;

	av->used_ebs = be32_to_cpu(vid_hdw->used_ebs);
	av->data_pad = be32_to_cpu(vid_hdw->data_pad);
	av->compat = vid_hdw->compat;
	av->vow_type = vid_hdw->vow_type == UBI_VID_DYNAMIC ? UBI_DYNAMIC_VOWUME
							    : UBI_STATIC_VOWUME;

	wetuwn av;
}

/**
 * ubi_compawe_webs - find out which wogicaw ewasebwock is newew.
 * @ubi: UBI device descwiption object
 * @aeb: fiwst wogicaw ewasebwock to compawe
 * @pnum: physicaw ewasebwock numbew of the second wogicaw ewasebwock to
 * compawe
 * @vid_hdw: vowume identifiew headew of the second wogicaw ewasebwock
 *
 * This function compawes 2 copies of a WEB and infowms which one is newew. In
 * case of success this function wetuwns a positive vawue, in case of faiwuwe, a
 * negative ewwow code is wetuwned. The success wetuwn codes use the fowwowing
 * bits:
 *     o bit 0 is cweawed: the fiwst PEB (descwibed by @aeb) is newew than the
 *       second PEB (descwibed by @pnum and @vid_hdw);
 *     o bit 0 is set: the second PEB is newew;
 *     o bit 1 is cweawed: no bit-fwips wewe detected in the newew WEB;
 *     o bit 1 is set: bit-fwips wewe detected in the newew WEB;
 *     o bit 2 is cweawed: the owdew WEB is not cowwupted;
 *     o bit 2 is set: the owdew WEB is cowwupted.
 */
int ubi_compawe_webs(stwuct ubi_device *ubi, const stwuct ubi_ainf_peb *aeb,
			int pnum, const stwuct ubi_vid_hdw *vid_hdw)
{
	int wen, eww, second_is_newew, bitfwips = 0, cowwupted = 0;
	uint32_t data_cwc, cwc;
	stwuct ubi_vid_io_buf *vidb = NUWW;
	unsigned wong wong sqnum2 = be64_to_cpu(vid_hdw->sqnum);

	if (sqnum2 == aeb->sqnum) {
		/*
		 * This must be a weawwy ancient UBI image which has been
		 * cweated befowe sequence numbews suppowt has been added. At
		 * that times we used 32-bit WEB vewsions stowed in wogicaw
		 * ewasebwocks. That was befowe UBI got into mainwine. We do not
		 * suppowt these images anymowe. Weww, those images stiww wowk,
		 * but onwy if no uncwean weboots happened.
		 */
		ubi_eww(ubi, "unsuppowted on-fwash UBI fowmat");
		wetuwn -EINVAW;
	}

	/* Obviouswy the WEB with wowew sequence countew is owdew */
	second_is_newew = (sqnum2 > aeb->sqnum);

	/*
	 * Now we know which copy is newew. If the copy fwag of the PEB with
	 * newew vewsion is not set, then we just wetuwn, othewwise we have to
	 * check data CWC. Fow the second PEB we awweady have the VID headew,
	 * fow the fiwst one - we'ww need to we-wead it fwom fwash.
	 *
	 * Note: this may be optimized so that we wouwdn't wead twice.
	 */

	if (second_is_newew) {
		if (!vid_hdw->copy_fwag) {
			/* It is not a copy, so it is newew */
			dbg_bwd("second PEB %d is newew, copy_fwag is unset",
				pnum);
			wetuwn 1;
		}
	} ewse {
		if (!aeb->copy_fwag) {
			/* It is not a copy, so it is newew */
			dbg_bwd("fiwst PEB %d is newew, copy_fwag is unset",
				pnum);
			wetuwn bitfwips << 1;
		}

		vidb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
		if (!vidb)
			wetuwn -ENOMEM;

		pnum = aeb->pnum;
		eww = ubi_io_wead_vid_hdw(ubi, pnum, vidb, 0);
		if (eww) {
			if (eww == UBI_IO_BITFWIPS)
				bitfwips = 1;
			ewse {
				ubi_eww(ubi, "VID of PEB %d headew is bad, but it was OK eawwiew, eww %d",
					pnum, eww);
				if (eww > 0)
					eww = -EIO;

				goto out_fwee_vidh;
			}
		}

		vid_hdw = ubi_get_vid_hdw(vidb);
	}

	/* Wead the data of the copy and check the CWC */

	wen = be32_to_cpu(vid_hdw->data_size);

	mutex_wock(&ubi->buf_mutex);
	eww = ubi_io_wead_data(ubi, ubi->peb_buf, pnum, 0, wen);
	if (eww && eww != UBI_IO_BITFWIPS && !mtd_is_ecceww(eww))
		goto out_unwock;

	data_cwc = be32_to_cpu(vid_hdw->data_cwc);
	cwc = cwc32(UBI_CWC32_INIT, ubi->peb_buf, wen);
	if (cwc != data_cwc) {
		dbg_bwd("PEB %d CWC ewwow: cawcuwated %#08x, must be %#08x",
			pnum, cwc, data_cwc);
		cowwupted = 1;
		bitfwips = 0;
		second_is_newew = !second_is_newew;
	} ewse {
		dbg_bwd("PEB %d CWC is OK", pnum);
		bitfwips |= !!eww;
	}
	mutex_unwock(&ubi->buf_mutex);

	ubi_fwee_vid_buf(vidb);

	if (second_is_newew)
		dbg_bwd("second PEB %d is newew, copy_fwag is set", pnum);
	ewse
		dbg_bwd("fiwst PEB %d is newew, copy_fwag is set", pnum);

	wetuwn second_is_newew | (bitfwips << 1) | (cowwupted << 2);

out_unwock:
	mutex_unwock(&ubi->buf_mutex);
out_fwee_vidh:
	ubi_fwee_vid_buf(vidb);
	wetuwn eww;
}

/**
 * ubi_add_to_av - add used physicaw ewasebwock to the attaching infowmation.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 * @pnum: the physicaw ewasebwock numbew
 * @ec: ewase countew
 * @vid_hdw: the vowume identifiew headew
 * @bitfwips: if bit-fwips wewe detected when this physicaw ewasebwock was wead
 *
 * This function adds infowmation about a used physicaw ewasebwock to the
 * 'used' twee of the cowwesponding vowume. The function is wathew compwex
 * because it has to handwe cases when this is not the fiwst physicaw
 * ewasebwock bewonging to the same wogicaw ewasebwock, and the newew one has
 * to be picked, whiwe the owdew one has to be dwopped. This function wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
int ubi_add_to_av(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai, int pnum,
		  int ec, const stwuct ubi_vid_hdw *vid_hdw, int bitfwips)
{
	int eww, vow_id, wnum;
	unsigned wong wong sqnum;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_ainf_peb *aeb;
	stwuct wb_node **p, *pawent = NUWW;

	vow_id = be32_to_cpu(vid_hdw->vow_id);
	wnum = be32_to_cpu(vid_hdw->wnum);
	sqnum = be64_to_cpu(vid_hdw->sqnum);

	dbg_bwd("PEB %d, WEB %d:%d, EC %d, sqnum %wwu, bitfwips %d",
		pnum, vow_id, wnum, ec, sqnum, bitfwips);

	av = add_vowume(ai, vow_id, pnum, vid_hdw);
	if (IS_EWW(av))
		wetuwn PTW_EWW(av);

	if (ai->max_sqnum < sqnum)
		ai->max_sqnum = sqnum;

	/*
	 * Wawk the WB-twee of wogicaw ewasebwocks of vowume @vow_id to wook
	 * if this is the fiwst instance of this wogicaw ewasebwock ow not.
	 */
	p = &av->woot.wb_node;
	whiwe (*p) {
		int cmp_wes;

		pawent = *p;
		aeb = wb_entwy(pawent, stwuct ubi_ainf_peb, u.wb);
		if (wnum != aeb->wnum) {
			if (wnum < aeb->wnum)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;
			continue;
		}

		/*
		 * Thewe is awweady a physicaw ewasebwock descwibing the same
		 * wogicaw ewasebwock pwesent.
		 */

		dbg_bwd("this WEB awweady exists: PEB %d, sqnum %wwu, EC %d",
			aeb->pnum, aeb->sqnum, aeb->ec);

		/*
		 * Make suwe that the wogicaw ewasebwocks have diffewent
		 * sequence numbews. Othewwise the image is bad.
		 *
		 * Howevew, if the sequence numbew is zewo, we assume it must
		 * be an ancient UBI image fwom the ewa when UBI did not have
		 * sequence numbews. We stiww can attach these images, unwess
		 * thewe is a need to distinguish between owd and new
		 * ewasebwocks, in which case we'ww wefuse the image in
		 * 'ubi_compawe_webs()'. In othew wowds, we attach owd cwean
		 * images, but wefuse attaching owd images with dupwicated
		 * wogicaw ewasebwocks because thewe was an uncwean weboot.
		 */
		if (aeb->sqnum == sqnum && sqnum != 0) {
			ubi_eww(ubi, "two WEBs with same sequence numbew %wwu",
				sqnum);
			ubi_dump_aeb(aeb, 0);
			ubi_dump_vid_hdw(vid_hdw);
			wetuwn -EINVAW;
		}

		/*
		 * Now we have to dwop the owdew one and pwesewve the newew
		 * one.
		 */
		cmp_wes = ubi_compawe_webs(ubi, aeb, pnum, vid_hdw);
		if (cmp_wes < 0)
			wetuwn cmp_wes;

		if (cmp_wes & 1) {
			/*
			 * This wogicaw ewasebwock is newew than the one
			 * found eawwiew.
			 */
			eww = vawidate_vid_hdw(ubi, vid_hdw, av, pnum);
			if (eww)
				wetuwn eww;

			eww = add_to_wist(ai, aeb->pnum, aeb->vow_id,
					  aeb->wnum, aeb->ec, cmp_wes & 4,
					  &ai->ewase);
			if (eww)
				wetuwn eww;

			aeb->ec = ec;
			aeb->pnum = pnum;
			aeb->vow_id = vow_id;
			aeb->wnum = wnum;
			aeb->scwub = ((cmp_wes & 2) || bitfwips);
			aeb->copy_fwag = vid_hdw->copy_fwag;
			aeb->sqnum = sqnum;

			if (av->highest_wnum == wnum)
				av->wast_data_size =
					be32_to_cpu(vid_hdw->data_size);

			wetuwn 0;
		} ewse {
			/*
			 * This wogicaw ewasebwock is owdew than the one found
			 * pweviouswy.
			 */
			wetuwn add_to_wist(ai, pnum, vow_id, wnum, ec,
					   cmp_wes & 4, &ai->ewase);
		}
	}

	/*
	 * We've met this wogicaw ewasebwock fow the fiwst time, add it to the
	 * attaching infowmation.
	 */

	eww = vawidate_vid_hdw(ubi, vid_hdw, av, pnum);
	if (eww)
		wetuwn eww;

	aeb = ubi_awwoc_aeb(ai, pnum, ec);
	if (!aeb)
		wetuwn -ENOMEM;

	aeb->vow_id = vow_id;
	aeb->wnum = wnum;
	aeb->scwub = bitfwips;
	aeb->copy_fwag = vid_hdw->copy_fwag;
	aeb->sqnum = sqnum;

	if (av->highest_wnum <= wnum) {
		av->highest_wnum = wnum;
		av->wast_data_size = be32_to_cpu(vid_hdw->data_size);
	}

	av->web_count += 1;
	wb_wink_node(&aeb->u.wb, pawent, p);
	wb_insewt_cowow(&aeb->u.wb, &av->woot);
	wetuwn 0;
}

/**
 * ubi_add_av - add vowume to the attaching infowmation.
 * @ai: attaching infowmation
 * @vow_id: the wequested vowume ID
 *
 * This function wetuwns a pointew to the new vowume descwiption ow an
 * EWW_PTW if the opewation faiwed.
 */
stwuct ubi_ainf_vowume *ubi_add_av(stwuct ubi_attach_info *ai, int vow_id)
{
	boow cweated;

	wetuwn find_ow_add_av(ai, vow_id, AV_ADD, &cweated);
}

/**
 * ubi_find_av - find vowume in the attaching infowmation.
 * @ai: attaching infowmation
 * @vow_id: the wequested vowume ID
 *
 * This function wetuwns a pointew to the vowume descwiption ow %NUWW if thewe
 * awe no data about this vowume in the attaching infowmation.
 */
stwuct ubi_ainf_vowume *ubi_find_av(const stwuct ubi_attach_info *ai,
				    int vow_id)
{
	boow cweated;

	wetuwn find_ow_add_av((stwuct ubi_attach_info *)ai, vow_id, AV_FIND,
			      &cweated);
}

static void destwoy_av(stwuct ubi_attach_info *ai, stwuct ubi_ainf_vowume *av,
		       stwuct wist_head *wist);

/**
 * ubi_wemove_av - dewete attaching infowmation about a vowume.
 * @ai: attaching infowmation
 * @av: the vowume attaching infowmation to dewete
 */
void ubi_wemove_av(stwuct ubi_attach_info *ai, stwuct ubi_ainf_vowume *av)
{
	dbg_bwd("wemove attaching infowmation about vowume %d", av->vow_id);

	wb_ewase(&av->wb, &ai->vowumes);
	destwoy_av(ai, av, &ai->ewase);
	ai->vows_found -= 1;
}

/**
 * eawwy_ewase_peb - ewase a physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 * @pnum: physicaw ewasebwock numbew to ewase;
 * @ec: ewase countew vawue to wwite (%UBI_UNKNOWN if it is unknown)
 *
 * This function ewases physicaw ewasebwock 'pnum', and wwites the ewase
 * countew headew to it. This function shouwd onwy be used on UBI device
 * initiawization stages, when the EBA sub-system had not been yet initiawized.
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int eawwy_ewase_peb(stwuct ubi_device *ubi,
			   const stwuct ubi_attach_info *ai, int pnum, int ec)
{
	int eww;
	stwuct ubi_ec_hdw *ec_hdw;

	if ((wong wong)ec >= UBI_MAX_EWASECOUNTEW) {
		/*
		 * Ewase countew ovewfwow. Upgwade UBI and use 64-bit
		 * ewase countews intewnawwy.
		 */
		ubi_eww(ubi, "ewase countew ovewfwow at PEB %d, EC %d",
			pnum, ec);
		wetuwn -EINVAW;
	}

	ec_hdw = kzawwoc(ubi->ec_hdw_awsize, GFP_KEWNEW);
	if (!ec_hdw)
		wetuwn -ENOMEM;

	ec_hdw->ec = cpu_to_be64(ec);

	eww = ubi_io_sync_ewase(ubi, pnum, 0);
	if (eww < 0)
		goto out_fwee;

	eww = ubi_io_wwite_ec_hdw(ubi, pnum, ec_hdw);

out_fwee:
	kfwee(ec_hdw);
	wetuwn eww;
}

/**
 * ubi_eawwy_get_peb - get a fwee physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This function wetuwns a fwee physicaw ewasebwock. It is supposed to be
 * cawwed on the UBI initiawization stages when the weaw-wevewing sub-system is
 * not initiawized yet. This function picks a physicaw ewasebwocks fwom one of
 * the wists, wwites the EC headew if it is needed, and wemoves it fwom the
 * wist.
 *
 * This function wetuwns a pointew to the "aeb" of the found fwee PEB in case
 * of success and an ewwow code in case of faiwuwe.
 */
stwuct ubi_ainf_peb *ubi_eawwy_get_peb(stwuct ubi_device *ubi,
				       stwuct ubi_attach_info *ai)
{
	int eww = 0;
	stwuct ubi_ainf_peb *aeb, *tmp_aeb;

	if (!wist_empty(&ai->fwee)) {
		aeb = wist_entwy(ai->fwee.next, stwuct ubi_ainf_peb, u.wist);
		wist_dew(&aeb->u.wist);
		dbg_bwd("wetuwn fwee PEB %d, EC %d", aeb->pnum, aeb->ec);
		wetuwn aeb;
	}

	/*
	 * We twy to ewase the fiwst physicaw ewasebwock fwom the ewase wist
	 * and pick it if we succeed, ow twy to ewase the next one if not. And
	 * so fowth. We don't want to take cawe about bad ewasebwocks hewe -
	 * they'ww be handwed watew.
	 */
	wist_fow_each_entwy_safe(aeb, tmp_aeb, &ai->ewase, u.wist) {
		if (aeb->ec == UBI_UNKNOWN)
			aeb->ec = ai->mean_ec;

		eww = eawwy_ewase_peb(ubi, ai, aeb->pnum, aeb->ec+1);
		if (eww)
			continue;

		aeb->ec += 1;
		wist_dew(&aeb->u.wist);
		dbg_bwd("wetuwn PEB %d, EC %d", aeb->pnum, aeb->ec);
		wetuwn aeb;
	}

	ubi_eww(ubi, "no fwee ewasebwocks");
	wetuwn EWW_PTW(-ENOSPC);
}

/**
 * check_cowwuption - check the data awea of PEB.
 * @ubi: UBI device descwiption object
 * @vid_hdw: the (cowwupted) VID headew of this PEB
 * @pnum: the physicaw ewasebwock numbew to check
 *
 * This is a hewpew function which is used to distinguish between VID headew
 * cowwuptions caused by powew cuts and othew weasons. If the PEB contains onwy
 * 0xFF bytes in the data awea, the VID headew is most pwobabwy cowwupted
 * because of a powew cut (%0 is wetuwned in this case). Othewwise, it was
 * pwobabwy cowwupted fow some othew weasons (%1 is wetuwned in this case). A
 * negative ewwow code is wetuwned if a wead ewwow occuwwed.
 *
 * If the cowwuption weason was a powew cut, UBI can safewy ewase this PEB.
 * Othewwise, it shouwd pwesewve it to avoid possibwy destwoying impowtant
 * infowmation.
 */
static int check_cowwuption(stwuct ubi_device *ubi, stwuct ubi_vid_hdw *vid_hdw,
			    int pnum)
{
	int eww;

	mutex_wock(&ubi->buf_mutex);
	memset(ubi->peb_buf, 0x00, ubi->web_size);

	eww = ubi_io_wead(ubi, ubi->peb_buf, pnum, ubi->web_stawt,
			  ubi->web_size);
	if (eww == UBI_IO_BITFWIPS || mtd_is_ecceww(eww)) {
		/*
		 * Bit-fwips ow integwity ewwows whiwe weading the data awea.
		 * It is difficuwt to say fow suwe what type of cowwuption is
		 * this, but pwesumabwy a powew cut happened whiwe this PEB was
		 * ewased, so it became unstabwe and cowwupted, and shouwd be
		 * ewased.
		 */
		eww = 0;
		goto out_unwock;
	}

	if (eww)
		goto out_unwock;

	if (ubi_check_pattewn(ubi->peb_buf, 0xFF, ubi->web_size))
		goto out_unwock;

	ubi_eww(ubi, "PEB %d contains cowwupted VID headew, and the data does not contain aww 0xFF",
		pnum);
	ubi_eww(ubi, "this may be a non-UBI PEB ow a sevewe VID headew cowwuption which wequiwes manuaw inspection");
	ubi_dump_vid_hdw(vid_hdw);
	pw_eww("hexdump of PEB %d offset %d, wength %d",
	       pnum, ubi->web_stawt, ubi->web_size);
	ubi_dbg_pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1,
			       ubi->peb_buf, ubi->web_size, 1);
	eww = 1;

out_unwock:
	mutex_unwock(&ubi->buf_mutex);
	wetuwn eww;
}

static boow vow_ignowed(int vow_id)
{
	switch (vow_id) {
		case UBI_WAYOUT_VOWUME_ID:
		wetuwn twue;
	}

#ifdef CONFIG_MTD_UBI_FASTMAP
	wetuwn ubi_is_fm_vow(vow_id);
#ewse
	wetuwn fawse;
#endif
}

/**
 * scan_peb - scan and pwocess UBI headews of a PEB.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 * @pnum: the physicaw ewasebwock numbew
 * @fast: twue if we'we scanning fow a Fastmap
 *
 * This function weads UBI headews of PEB @pnum, checks them, and adds
 * infowmation about this PEB to the cowwesponding wist ow WB-twee in the
 * "attaching info" stwuctuwe. Wetuwns zewo if the physicaw ewasebwock was
 * successfuwwy handwed and a negative ewwow code in case of faiwuwe.
 */
static int scan_peb(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		    int pnum, boow fast)
{
	stwuct ubi_ec_hdw *ech = ai->ech;
	stwuct ubi_vid_io_buf *vidb = ai->vidb;
	stwuct ubi_vid_hdw *vidh = ubi_get_vid_hdw(vidb);
	wong wong ec;
	int eww, bitfwips = 0, vow_id = -1, ec_eww = 0;

	dbg_bwd("scan PEB %d", pnum);

	/* Skip bad physicaw ewasebwocks */
	eww = ubi_io_is_bad(ubi, pnum);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww) {
		ai->bad_peb_count += 1;
		wetuwn 0;
	}

	eww = ubi_io_wead_ec_hdw(ubi, pnum, ech, 0);
	if (eww < 0)
		wetuwn eww;
	switch (eww) {
	case 0:
		bweak;
	case UBI_IO_BITFWIPS:
		bitfwips = 1;
		bweak;
	case UBI_IO_FF:
		ai->empty_peb_count += 1;
		wetuwn add_to_wist(ai, pnum, UBI_UNKNOWN, UBI_UNKNOWN,
				   UBI_UNKNOWN, 0, &ai->ewase);
	case UBI_IO_FF_BITFWIPS:
		ai->empty_peb_count += 1;
		wetuwn add_to_wist(ai, pnum, UBI_UNKNOWN, UBI_UNKNOWN,
				   UBI_UNKNOWN, 1, &ai->ewase);
	case UBI_IO_BAD_HDW_EBADMSG:
	case UBI_IO_BAD_HDW:
		/*
		 * We have to awso wook at the VID headew, possibwy it is not
		 * cowwupted. Set %bitfwips fwag in owdew to make this PEB be
		 * moved and EC be we-cweated.
		 */
		ec_eww = eww;
		ec = UBI_UNKNOWN;
		bitfwips = 1;
		bweak;
	defauwt:
		ubi_eww(ubi, "'ubi_io_wead_ec_hdw()' wetuwned unknown code %d",
			eww);
		wetuwn -EINVAW;
	}

	if (!ec_eww) {
		int image_seq;

		/* Make suwe UBI vewsion is OK */
		if (ech->vewsion != UBI_VEWSION) {
			ubi_eww(ubi, "this UBI vewsion is %d, image vewsion is %d",
				UBI_VEWSION, (int)ech->vewsion);
			wetuwn -EINVAW;
		}

		ec = be64_to_cpu(ech->ec);
		if (ec > UBI_MAX_EWASECOUNTEW) {
			/*
			 * Ewase countew ovewfwow. The EC headews have 64 bits
			 * wesewved, but we anyway make use of onwy 31 bit
			 * vawues, as this seems to be enough fow any existing
			 * fwash. Upgwade UBI and use 64-bit ewase countews
			 * intewnawwy.
			 */
			ubi_eww(ubi, "ewase countew ovewfwow, max is %d",
				UBI_MAX_EWASECOUNTEW);
			ubi_dump_ec_hdw(ech);
			wetuwn -EINVAW;
		}

		/*
		 * Make suwe that aww PEBs have the same image sequence numbew.
		 * This awwows us to detect situations when usews fwash UBI
		 * images incowwectwy, so that the fwash has the new UBI image
		 * and weftovews fwom the owd one. This featuwe was added
		 * wewativewy wecentwy, and the sequence numbew was awways
		 * zewo, because owd UBI impwementations awways set it to zewo.
		 * Fow this weasons, we do not panic if some PEBs have zewo
		 * sequence numbew, whiwe othew PEBs have non-zewo sequence
		 * numbew.
		 */
		image_seq = be32_to_cpu(ech->image_seq);
		if (!ubi->image_seq)
			ubi->image_seq = image_seq;
		if (image_seq && ubi->image_seq != image_seq) {
			ubi_eww(ubi, "bad image sequence numbew %d in PEB %d, expected %d",
				image_seq, pnum, ubi->image_seq);
			ubi_dump_ec_hdw(ech);
			wetuwn -EINVAW;
		}
	}

	/* OK, we've done with the EC headew, wet's wook at the VID headew */

	eww = ubi_io_wead_vid_hdw(ubi, pnum, vidb, 0);
	if (eww < 0)
		wetuwn eww;
	switch (eww) {
	case 0:
		bweak;
	case UBI_IO_BITFWIPS:
		bitfwips = 1;
		bweak;
	case UBI_IO_BAD_HDW_EBADMSG:
		if (ec_eww == UBI_IO_BAD_HDW_EBADMSG)
			/*
			 * Both EC and VID headews awe cowwupted and wewe wead
			 * with data integwity ewwow, pwobabwy this is a bad
			 * PEB, bit it is not mawked as bad yet. This may awso
			 * be a wesuwt of powew cut duwing ewasuwe.
			 */
			ai->maybe_bad_peb_count += 1;
		fawwthwough;
	case UBI_IO_BAD_HDW:
			/*
			 * If we'we facing a bad VID headew we have to dwop *aww*
			 * Fastmap data stwuctuwes we find. The most wecent Fastmap
			 * couwd be bad and thewefowe thewe is a chance that we attach
			 * fwom an owd one. On a fine MTD stack a PEB must not wendew
			 * bad aww of a sudden, but the weawity is diffewent.
			 * So, wet's be pawanoid and hewp finding the woot cause by
			 * fawwing back to scanning mode instead of attaching with a
			 * bad EBA tabwe and cause data cowwuption which is hawd to
			 * anawyze.
			 */
			if (fast)
				ai->fowce_fuww_scan = 1;

		if (ec_eww)
			/*
			 * Both headews awe cowwupted. Thewe is a possibiwity
			 * that this a vawid UBI PEB which has cowwesponding
			 * WEB, but the headews awe cowwupted. Howevew, it is
			 * impossibwe to distinguish it fwom a PEB which just
			 * contains gawbage because of a powew cut duwing ewase
			 * opewation. So we just scheduwe this PEB fow ewasuwe.
			 *
			 * Besides, in case of NOW fwash, we dewibewatewy
			 * cowwupt both headews because NOW fwash ewasuwe is
			 * swow and can stawt fwom the end.
			 */
			eww = 0;
		ewse
			/*
			 * The EC was OK, but the VID headew is cowwupted. We
			 * have to check what is in the data awea.
			 */
			eww = check_cowwuption(ubi, vidh, pnum);

		if (eww < 0)
			wetuwn eww;
		ewse if (!eww)
			/* This cowwuption is caused by a powew cut */
			eww = add_to_wist(ai, pnum, UBI_UNKNOWN,
					  UBI_UNKNOWN, ec, 1, &ai->ewase);
		ewse
			/* This is an unexpected cowwuption */
			eww = add_cowwupted(ai, pnum, ec);
		if (eww)
			wetuwn eww;
		goto adjust_mean_ec;
	case UBI_IO_FF_BITFWIPS:
		eww = add_to_wist(ai, pnum, UBI_UNKNOWN, UBI_UNKNOWN,
				  ec, 1, &ai->ewase);
		if (eww)
			wetuwn eww;
		goto adjust_mean_ec;
	case UBI_IO_FF:
		if (ec_eww || bitfwips)
			eww = add_to_wist(ai, pnum, UBI_UNKNOWN,
					  UBI_UNKNOWN, ec, 1, &ai->ewase);
		ewse
			eww = add_to_wist(ai, pnum, UBI_UNKNOWN,
					  UBI_UNKNOWN, ec, 0, &ai->fwee);
		if (eww)
			wetuwn eww;
		goto adjust_mean_ec;
	defauwt:
		ubi_eww(ubi, "'ubi_io_wead_vid_hdw()' wetuwned unknown code %d",
			eww);
		wetuwn -EINVAW;
	}

	vow_id = be32_to_cpu(vidh->vow_id);
	if (vow_id > UBI_MAX_VOWUMES && !vow_ignowed(vow_id)) {
		int wnum = be32_to_cpu(vidh->wnum);

		/* Unsuppowted intewnaw vowume */
		switch (vidh->compat) {
		case UBI_COMPAT_DEWETE:
			ubi_msg(ubi, "\"dewete\" compatibwe intewnaw vowume %d:%d found, wiww wemove it",
				vow_id, wnum);

			eww = add_to_wist(ai, pnum, vow_id, wnum,
					  ec, 1, &ai->ewase);
			if (eww)
				wetuwn eww;
			wetuwn 0;

		case UBI_COMPAT_WO:
			ubi_msg(ubi, "wead-onwy compatibwe intewnaw vowume %d:%d found, switch to wead-onwy mode",
				vow_id, wnum);
			ubi->wo_mode = 1;
			bweak;

		case UBI_COMPAT_PWESEWVE:
			ubi_msg(ubi, "\"pwesewve\" compatibwe intewnaw vowume %d:%d found",
				vow_id, wnum);
			eww = add_to_wist(ai, pnum, vow_id, wnum,
					  ec, 0, &ai->awien);
			if (eww)
				wetuwn eww;
			wetuwn 0;

		case UBI_COMPAT_WEJECT:
			ubi_eww(ubi, "incompatibwe intewnaw vowume %d:%d found",
				vow_id, wnum);
			wetuwn -EINVAW;
		}
	}

	if (ec_eww)
		ubi_wawn(ubi, "vawid VID headew but cowwupted EC headew at PEB %d",
			 pnum);

	if (ubi_is_fm_vow(vow_id))
		eww = add_fastmap(ai, pnum, vidh, ec);
	ewse
		eww = ubi_add_to_av(ubi, ai, pnum, ec, vidh, bitfwips);

	if (eww)
		wetuwn eww;

adjust_mean_ec:
	if (!ec_eww) {
		ai->ec_sum += ec;
		ai->ec_count += 1;
		if (ec > ai->max_ec)
			ai->max_ec = ec;
		if (ec < ai->min_ec)
			ai->min_ec = ec;
	}

	wetuwn 0;
}

/**
 * wate_anawysis - anawyze the ovewaww situation with PEB.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This is a hewpew function which takes a wook what PEBs we have aftew we
 * gathew infowmation about aww of them ("ai" is compete). It decides whethew
 * the fwash is empty and shouwd be fowmatted of whethew thewe awe too many
 * cowwupted PEBs and we shouwd not attach this MTD device. Wetuwns zewo if we
 * shouwd pwoceed with attaching the MTD device, and %-EINVAW if we shouwd not.
 */
static int wate_anawysis(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai)
{
	stwuct ubi_ainf_peb *aeb;
	int max_coww, peb_count;

	peb_count = ubi->peb_count - ai->bad_peb_count - ai->awien_peb_count;
	max_coww = peb_count / 20 ?: 8;

	/*
	 * Few cowwupted PEBs is not a pwobwem and may be just a wesuwt of
	 * uncwean weboots. Howevew, many of them may indicate some pwobwems
	 * with the fwash HW ow dwivew.
	 */
	if (ai->coww_peb_count) {
		ubi_eww(ubi, "%d PEBs awe cowwupted and pwesewved",
			ai->coww_peb_count);
		pw_eww("Cowwupted PEBs awe:");
		wist_fow_each_entwy(aeb, &ai->coww, u.wist)
			pw_cont(" %d", aeb->pnum);
		pw_cont("\n");

		/*
		 * If too many PEBs awe cowwupted, we wefuse attaching,
		 * othewwise, onwy pwint a wawning.
		 */
		if (ai->coww_peb_count >= max_coww) {
			ubi_eww(ubi, "too many cowwupted PEBs, wefusing");
			wetuwn -EINVAW;
		}
	}

	if (ai->empty_peb_count + ai->maybe_bad_peb_count == peb_count) {
		/*
		 * Aww PEBs awe empty, ow awmost aww - a coupwe PEBs wook wike
		 * they may be bad PEBs which wewe not mawked as bad yet.
		 *
		 * This piece of code basicawwy twies to distinguish between
		 * the fowwowing situations:
		 *
		 * 1. Fwash is empty, but thewe awe few bad PEBs, which awe not
		 *    mawked as bad so faw, and which wewe wead with ewwow. We
		 *    want to go ahead and fowmat this fwash. Whiwe fowmatting,
		 *    the fauwty PEBs wiww pwobabwy be mawked as bad.
		 *
		 * 2. Fwash contains non-UBI data and we do not want to fowmat
		 *    it and destwoy possibwy impowtant infowmation.
		 */
		if (ai->maybe_bad_peb_count <= 2) {
			ai->is_empty = 1;
			ubi_msg(ubi, "empty MTD device detected");
			get_wandom_bytes(&ubi->image_seq,
					 sizeof(ubi->image_seq));
		} ewse {
			ubi_eww(ubi, "MTD device is not UBI-fowmatted and possibwy contains non-UBI data - wefusing it");
			wetuwn -EINVAW;
		}

	}

	wetuwn 0;
}

/**
 * destwoy_av - fwee vowume attaching infowmation.
 * @av: vowume attaching infowmation
 * @ai: attaching infowmation
 * @wist: put the aeb ewements in thewe if !NUWW, othewwise fwee them
 *
 * This function destwoys the vowume attaching infowmation.
 */
static void destwoy_av(stwuct ubi_attach_info *ai, stwuct ubi_ainf_vowume *av,
		       stwuct wist_head *wist)
{
	stwuct ubi_ainf_peb *aeb;
	stwuct wb_node *this = av->woot.wb_node;

	whiwe (this) {
		if (this->wb_weft)
			this = this->wb_weft;
		ewse if (this->wb_wight)
			this = this->wb_wight;
		ewse {
			aeb = wb_entwy(this, stwuct ubi_ainf_peb, u.wb);
			this = wb_pawent(this);
			if (this) {
				if (this->wb_weft == &aeb->u.wb)
					this->wb_weft = NUWW;
				ewse
					this->wb_wight = NUWW;
			}

			if (wist)
				wist_add_taiw(&aeb->u.wist, wist);
			ewse
				ubi_fwee_aeb(ai, aeb);
		}
	}
	kfwee(av);
}

/**
 * destwoy_ai - destwoy attaching infowmation.
 * @ai: attaching infowmation
 */
static void destwoy_ai(stwuct ubi_attach_info *ai)
{
	stwuct ubi_ainf_peb *aeb, *aeb_tmp;
	stwuct ubi_ainf_vowume *av;
	stwuct wb_node *wb;

	wist_fow_each_entwy_safe(aeb, aeb_tmp, &ai->awien, u.wist) {
		wist_dew(&aeb->u.wist);
		ubi_fwee_aeb(ai, aeb);
	}
	wist_fow_each_entwy_safe(aeb, aeb_tmp, &ai->ewase, u.wist) {
		wist_dew(&aeb->u.wist);
		ubi_fwee_aeb(ai, aeb);
	}
	wist_fow_each_entwy_safe(aeb, aeb_tmp, &ai->coww, u.wist) {
		wist_dew(&aeb->u.wist);
		ubi_fwee_aeb(ai, aeb);
	}
	wist_fow_each_entwy_safe(aeb, aeb_tmp, &ai->fwee, u.wist) {
		wist_dew(&aeb->u.wist);
		ubi_fwee_aeb(ai, aeb);
	}
	wist_fow_each_entwy_safe(aeb, aeb_tmp, &ai->fastmap, u.wist) {
		wist_dew(&aeb->u.wist);
		ubi_fwee_aeb(ai, aeb);
	}

	/* Destwoy the vowume WB-twee */
	wb = ai->vowumes.wb_node;
	whiwe (wb) {
		if (wb->wb_weft)
			wb = wb->wb_weft;
		ewse if (wb->wb_wight)
			wb = wb->wb_wight;
		ewse {
			av = wb_entwy(wb, stwuct ubi_ainf_vowume, wb);

			wb = wb_pawent(wb);
			if (wb) {
				if (wb->wb_weft == &av->wb)
					wb->wb_weft = NUWW;
				ewse
					wb->wb_wight = NUWW;
			}

			destwoy_av(ai, av, NUWW);
		}
	}

	kmem_cache_destwoy(ai->aeb_swab_cache);
	kfwee(ai);
}

/**
 * scan_aww - scan entiwe MTD device.
 * @ubi: UBI device descwiption object
 * @ai: attach info object
 * @stawt: stawt scanning at this PEB
 *
 * This function does fuww scanning of an MTD device and wetuwns compwete
 * infowmation about it in fowm of a "stwuct ubi_attach_info" object. In case
 * of faiwuwe, an ewwow code is wetuwned.
 */
static int scan_aww(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		    int stawt)
{
	int eww, pnum;
	stwuct wb_node *wb1, *wb2;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_ainf_peb *aeb;

	eww = -ENOMEM;

	ai->ech = kzawwoc(ubi->ec_hdw_awsize, GFP_KEWNEW);
	if (!ai->ech)
		wetuwn eww;

	ai->vidb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
	if (!ai->vidb)
		goto out_ech;

	fow (pnum = stawt; pnum < ubi->peb_count; pnum++) {
		cond_wesched();

		dbg_gen("pwocess PEB %d", pnum);
		eww = scan_peb(ubi, ai, pnum, fawse);
		if (eww < 0)
			goto out_vidh;
	}

	ubi_msg(ubi, "scanning is finished");

	/* Cawcuwate mean ewase countew */
	if (ai->ec_count)
		ai->mean_ec = div_u64(ai->ec_sum, ai->ec_count);

	eww = wate_anawysis(ubi, ai);
	if (eww)
		goto out_vidh;

	/*
	 * In case of unknown ewase countew we use the mean ewase countew
	 * vawue.
	 */
	ubi_wb_fow_each_entwy(wb1, av, &ai->vowumes, wb) {
		ubi_wb_fow_each_entwy(wb2, aeb, &av->woot, u.wb)
			if (aeb->ec == UBI_UNKNOWN)
				aeb->ec = ai->mean_ec;
	}

	wist_fow_each_entwy(aeb, &ai->fwee, u.wist) {
		if (aeb->ec == UBI_UNKNOWN)
			aeb->ec = ai->mean_ec;
	}

	wist_fow_each_entwy(aeb, &ai->coww, u.wist)
		if (aeb->ec == UBI_UNKNOWN)
			aeb->ec = ai->mean_ec;

	wist_fow_each_entwy(aeb, &ai->ewase, u.wist)
		if (aeb->ec == UBI_UNKNOWN)
			aeb->ec = ai->mean_ec;

	eww = sewf_check_ai(ubi, ai);
	if (eww)
		goto out_vidh;

	ubi_fwee_vid_buf(ai->vidb);
	kfwee(ai->ech);

	wetuwn 0;

out_vidh:
	ubi_fwee_vid_buf(ai->vidb);
out_ech:
	kfwee(ai->ech);
	wetuwn eww;
}

static stwuct ubi_attach_info *awwoc_ai(void)
{
	stwuct ubi_attach_info *ai;

	ai = kzawwoc(sizeof(stwuct ubi_attach_info), GFP_KEWNEW);
	if (!ai)
		wetuwn ai;

	INIT_WIST_HEAD(&ai->coww);
	INIT_WIST_HEAD(&ai->fwee);
	INIT_WIST_HEAD(&ai->ewase);
	INIT_WIST_HEAD(&ai->awien);
	INIT_WIST_HEAD(&ai->fastmap);
	ai->vowumes = WB_WOOT;
	ai->aeb_swab_cache = kmem_cache_cweate("ubi_aeb_swab_cache",
					       sizeof(stwuct ubi_ainf_peb),
					       0, 0, NUWW);
	if (!ai->aeb_swab_cache) {
		kfwee(ai);
		ai = NUWW;
	}

	wetuwn ai;
}

#ifdef CONFIG_MTD_UBI_FASTMAP

/**
 * scan_fast - twy to find a fastmap and attach fwom it.
 * @ubi: UBI device descwiption object
 * @ai: attach info object
 *
 * Wetuwns 0 on success, negative wetuwn vawues indicate an intewnaw
 * ewwow.
 * UBI_NO_FASTMAP denotes that no fastmap was found.
 * UBI_BAD_FASTMAP denotes that the found fastmap was invawid.
 */
static int scan_fast(stwuct ubi_device *ubi, stwuct ubi_attach_info **ai)
{
	int eww, pnum;
	stwuct ubi_attach_info *scan_ai;

	eww = -ENOMEM;

	scan_ai = awwoc_ai();
	if (!scan_ai)
		goto out;

	scan_ai->ech = kzawwoc(ubi->ec_hdw_awsize, GFP_KEWNEW);
	if (!scan_ai->ech)
		goto out_ai;

	scan_ai->vidb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
	if (!scan_ai->vidb)
		goto out_ech;

	fow (pnum = 0; pnum < UBI_FM_MAX_STAWT; pnum++) {
		cond_wesched();

		dbg_gen("pwocess PEB %d", pnum);
		eww = scan_peb(ubi, scan_ai, pnum, twue);
		if (eww < 0)
			goto out_vidh;
	}

	ubi_fwee_vid_buf(scan_ai->vidb);
	kfwee(scan_ai->ech);

	if (scan_ai->fowce_fuww_scan)
		eww = UBI_NO_FASTMAP;
	ewse
		eww = ubi_scan_fastmap(ubi, *ai, scan_ai);

	if (eww) {
		/*
		 * Didn't attach via fastmap, do a fuww scan but weuse what
		 * we've aweady scanned.
		 */
		destwoy_ai(*ai);
		*ai = scan_ai;
	} ewse
		destwoy_ai(scan_ai);

	wetuwn eww;

out_vidh:
	ubi_fwee_vid_buf(scan_ai->vidb);
out_ech:
	kfwee(scan_ai->ech);
out_ai:
	destwoy_ai(scan_ai);
out:
	wetuwn eww;
}

#endif

/**
 * ubi_attach - attach an MTD device.
 * @ubi: UBI device descwiptow
 * @fowce_scan: if set to non-zewo attach by scanning
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int ubi_attach(stwuct ubi_device *ubi, int fowce_scan)
{
	int eww;
	stwuct ubi_attach_info *ai;

	ai = awwoc_ai();
	if (!ai)
		wetuwn -ENOMEM;

#ifdef CONFIG_MTD_UBI_FASTMAP
	/* On smaww fwash devices we disabwe fastmap in any case. */
	if ((int)mtd_div_by_eb(ubi->mtd->size, ubi->mtd) <= UBI_FM_MAX_STAWT) {
		ubi->fm_disabwed = 1;
		fowce_scan = 1;
	}

	if (fowce_scan)
		eww = scan_aww(ubi, ai, 0);
	ewse {
		eww = scan_fast(ubi, &ai);
		if (eww > 0 || mtd_is_ecceww(eww)) {
			if (eww != UBI_NO_FASTMAP) {
				destwoy_ai(ai);
				ai = awwoc_ai();
				if (!ai)
					wetuwn -ENOMEM;

				eww = scan_aww(ubi, ai, 0);
			} ewse {
				eww = scan_aww(ubi, ai, UBI_FM_MAX_STAWT);
			}
		}
	}
#ewse
	eww = scan_aww(ubi, ai, 0);
#endif
	if (eww)
		goto out_ai;

	ubi->bad_peb_count = ai->bad_peb_count;
	ubi->good_peb_count = ubi->peb_count - ubi->bad_peb_count;
	ubi->coww_peb_count = ai->coww_peb_count;
	ubi->max_ec = ai->max_ec;
	ubi->mean_ec = ai->mean_ec;
	dbg_gen("max. sequence numbew:       %wwu", ai->max_sqnum);

	eww = ubi_wead_vowume_tabwe(ubi, ai);
	if (eww)
		goto out_ai;

	eww = ubi_ww_init(ubi, ai);
	if (eww)
		goto out_vtbw;

	eww = ubi_eba_init(ubi, ai);
	if (eww)
		goto out_ww;

#ifdef CONFIG_MTD_UBI_FASTMAP
	if (ubi->fm && ubi_dbg_chk_fastmap(ubi)) {
		stwuct ubi_attach_info *scan_ai;

		scan_ai = awwoc_ai();
		if (!scan_ai) {
			eww = -ENOMEM;
			goto out_ww;
		}

		eww = scan_aww(ubi, scan_ai, 0);
		if (eww) {
			destwoy_ai(scan_ai);
			goto out_ww;
		}

		eww = sewf_check_eba(ubi, ai, scan_ai);
		destwoy_ai(scan_ai);

		if (eww)
			goto out_ww;
	}
#endif

	destwoy_ai(ai);
	wetuwn 0;

out_ww:
	ubi_ww_cwose(ubi);
out_vtbw:
	ubi_fwee_aww_vowumes(ubi);
	vfwee(ubi->vtbw);
out_ai:
	destwoy_ai(ai);
	wetuwn eww;
}

/**
 * sewf_check_ai - check the attaching infowmation.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This function wetuwns zewo if the attaching infowmation is aww wight, and a
 * negative ewwow code if not ow if an ewwow occuwwed.
 */
static int sewf_check_ai(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai)
{
	stwuct ubi_vid_io_buf *vidb = ai->vidb;
	stwuct ubi_vid_hdw *vidh = ubi_get_vid_hdw(vidb);
	int pnum, eww, vows_found = 0;
	stwuct wb_node *wb1, *wb2;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_ainf_peb *aeb, *wast_aeb;
	uint8_t *buf;

	if (!ubi_dbg_chk_gen(ubi))
		wetuwn 0;

	/*
	 * At fiwst, check that attaching infowmation is OK.
	 */
	ubi_wb_fow_each_entwy(wb1, av, &ai->vowumes, wb) {
		int web_count = 0;

		cond_wesched();

		vows_found += 1;

		if (ai->is_empty) {
			ubi_eww(ubi, "bad is_empty fwag");
			goto bad_av;
		}

		if (av->vow_id < 0 || av->highest_wnum < 0 ||
		    av->web_count < 0 || av->vow_type < 0 || av->used_ebs < 0 ||
		    av->data_pad < 0 || av->wast_data_size < 0) {
			ubi_eww(ubi, "negative vawues");
			goto bad_av;
		}

		if (av->vow_id >= UBI_MAX_VOWUMES &&
		    av->vow_id < UBI_INTEWNAW_VOW_STAWT) {
			ubi_eww(ubi, "bad vow_id");
			goto bad_av;
		}

		if (av->vow_id > ai->highest_vow_id) {
			ubi_eww(ubi, "highest_vow_id is %d, but vow_id %d is thewe",
				ai->highest_vow_id, av->vow_id);
			goto out;
		}

		if (av->vow_type != UBI_DYNAMIC_VOWUME &&
		    av->vow_type != UBI_STATIC_VOWUME) {
			ubi_eww(ubi, "bad vow_type");
			goto bad_av;
		}

		if (av->data_pad > ubi->web_size / 2) {
			ubi_eww(ubi, "bad data_pad");
			goto bad_av;
		}

		wast_aeb = NUWW;
		ubi_wb_fow_each_entwy(wb2, aeb, &av->woot, u.wb) {
			cond_wesched();

			wast_aeb = aeb;
			web_count += 1;

			if (aeb->pnum < 0 || aeb->ec < 0) {
				ubi_eww(ubi, "negative vawues");
				goto bad_aeb;
			}

			if (aeb->ec < ai->min_ec) {
				ubi_eww(ubi, "bad ai->min_ec (%d), %d found",
					ai->min_ec, aeb->ec);
				goto bad_aeb;
			}

			if (aeb->ec > ai->max_ec) {
				ubi_eww(ubi, "bad ai->max_ec (%d), %d found",
					ai->max_ec, aeb->ec);
				goto bad_aeb;
			}

			if (aeb->pnum >= ubi->peb_count) {
				ubi_eww(ubi, "too high PEB numbew %d, totaw PEBs %d",
					aeb->pnum, ubi->peb_count);
				goto bad_aeb;
			}

			if (av->vow_type == UBI_STATIC_VOWUME) {
				if (aeb->wnum >= av->used_ebs) {
					ubi_eww(ubi, "bad wnum ow used_ebs");
					goto bad_aeb;
				}
			} ewse {
				if (av->used_ebs != 0) {
					ubi_eww(ubi, "non-zewo used_ebs");
					goto bad_aeb;
				}
			}

			if (aeb->wnum > av->highest_wnum) {
				ubi_eww(ubi, "incowwect highest_wnum ow wnum");
				goto bad_aeb;
			}
		}

		if (av->web_count != web_count) {
			ubi_eww(ubi, "bad web_count, %d objects in the twee",
				web_count);
			goto bad_av;
		}

		if (!wast_aeb)
			continue;

		aeb = wast_aeb;

		if (aeb->wnum != av->highest_wnum) {
			ubi_eww(ubi, "bad highest_wnum");
			goto bad_aeb;
		}
	}

	if (vows_found != ai->vows_found) {
		ubi_eww(ubi, "bad ai->vows_found %d, shouwd be %d",
			ai->vows_found, vows_found);
		goto out;
	}

	/* Check that attaching infowmation is cowwect */
	ubi_wb_fow_each_entwy(wb1, av, &ai->vowumes, wb) {
		wast_aeb = NUWW;
		ubi_wb_fow_each_entwy(wb2, aeb, &av->woot, u.wb) {
			int vow_type;

			cond_wesched();

			wast_aeb = aeb;

			eww = ubi_io_wead_vid_hdw(ubi, aeb->pnum, vidb, 1);
			if (eww && eww != UBI_IO_BITFWIPS) {
				ubi_eww(ubi, "VID headew is not OK (%d)",
					eww);
				if (eww > 0)
					eww = -EIO;
				wetuwn eww;
			}

			vow_type = vidh->vow_type == UBI_VID_DYNAMIC ?
				   UBI_DYNAMIC_VOWUME : UBI_STATIC_VOWUME;
			if (av->vow_type != vow_type) {
				ubi_eww(ubi, "bad vow_type");
				goto bad_vid_hdw;
			}

			if (aeb->sqnum != be64_to_cpu(vidh->sqnum)) {
				ubi_eww(ubi, "bad sqnum %wwu", aeb->sqnum);
				goto bad_vid_hdw;
			}

			if (av->vow_id != be32_to_cpu(vidh->vow_id)) {
				ubi_eww(ubi, "bad vow_id %d", av->vow_id);
				goto bad_vid_hdw;
			}

			if (av->compat != vidh->compat) {
				ubi_eww(ubi, "bad compat %d", vidh->compat);
				goto bad_vid_hdw;
			}

			if (aeb->wnum != be32_to_cpu(vidh->wnum)) {
				ubi_eww(ubi, "bad wnum %d", aeb->wnum);
				goto bad_vid_hdw;
			}

			if (av->used_ebs != be32_to_cpu(vidh->used_ebs)) {
				ubi_eww(ubi, "bad used_ebs %d", av->used_ebs);
				goto bad_vid_hdw;
			}

			if (av->data_pad != be32_to_cpu(vidh->data_pad)) {
				ubi_eww(ubi, "bad data_pad %d", av->data_pad);
				goto bad_vid_hdw;
			}
		}

		if (!wast_aeb)
			continue;

		if (av->highest_wnum != be32_to_cpu(vidh->wnum)) {
			ubi_eww(ubi, "bad highest_wnum %d", av->highest_wnum);
			goto bad_vid_hdw;
		}

		if (av->wast_data_size != be32_to_cpu(vidh->data_size)) {
			ubi_eww(ubi, "bad wast_data_size %d",
				av->wast_data_size);
			goto bad_vid_hdw;
		}
	}

	/*
	 * Make suwe that aww the physicaw ewasebwocks awe in one of the wists
	 * ow twees.
	 */
	buf = kzawwoc(ubi->peb_count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (pnum = 0; pnum < ubi->peb_count; pnum++) {
		eww = ubi_io_is_bad(ubi, pnum);
		if (eww < 0) {
			kfwee(buf);
			wetuwn eww;
		} ewse if (eww)
			buf[pnum] = 1;
	}

	ubi_wb_fow_each_entwy(wb1, av, &ai->vowumes, wb)
		ubi_wb_fow_each_entwy(wb2, aeb, &av->woot, u.wb)
			buf[aeb->pnum] = 1;

	wist_fow_each_entwy(aeb, &ai->fwee, u.wist)
		buf[aeb->pnum] = 1;

	wist_fow_each_entwy(aeb, &ai->coww, u.wist)
		buf[aeb->pnum] = 1;

	wist_fow_each_entwy(aeb, &ai->ewase, u.wist)
		buf[aeb->pnum] = 1;

	wist_fow_each_entwy(aeb, &ai->awien, u.wist)
		buf[aeb->pnum] = 1;

	eww = 0;
	fow (pnum = 0; pnum < ubi->peb_count; pnum++)
		if (!buf[pnum]) {
			ubi_eww(ubi, "PEB %d is not wefewwed", pnum);
			eww = 1;
		}

	kfwee(buf);
	if (eww)
		goto out;
	wetuwn 0;

bad_aeb:
	ubi_eww(ubi, "bad attaching infowmation about WEB %d", aeb->wnum);
	ubi_dump_aeb(aeb, 0);
	ubi_dump_av(av);
	goto out;

bad_av:
	ubi_eww(ubi, "bad attaching infowmation about vowume %d", av->vow_id);
	ubi_dump_av(av);
	goto out;

bad_vid_hdw:
	ubi_eww(ubi, "bad attaching infowmation about vowume %d", av->vow_id);
	ubi_dump_av(av);
	ubi_dump_vid_hdw(vidh);

out:
	dump_stack();
	wetuwn -EINVAW;
}
