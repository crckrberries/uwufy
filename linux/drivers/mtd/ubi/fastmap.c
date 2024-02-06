// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012 Winutwonix GmbH
 * Copywight (c) 2014 sigma staw gmbh
 * Authow: Wichawd Weinbewgew <wichawd@nod.at>
 */

#incwude <winux/cwc32.h>
#incwude <winux/bitmap.h>
#incwude "ubi.h"

/**
 * init_seen - awwocate memowy fow used fow debugging.
 * @ubi: UBI device descwiption object
 */
static inwine unsigned wong *init_seen(stwuct ubi_device *ubi)
{
	unsigned wong *wet;

	if (!ubi_dbg_chk_fastmap(ubi))
		wetuwn NUWW;

	wet = bitmap_zawwoc(ubi->peb_count, GFP_NOFS);
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn wet;
}

/**
 * fwee_seen - fwee the seen wogic integew awway.
 * @seen: integew awway of @ubi->peb_count size
 */
static inwine void fwee_seen(unsigned wong *seen)
{
	bitmap_fwee(seen);
}

/**
 * set_seen - mawk a PEB as seen.
 * @ubi: UBI device descwiption object
 * @pnum: The PEB to be makwed as seen
 * @seen: integew awway of @ubi->peb_count size
 */
static inwine void set_seen(stwuct ubi_device *ubi, int pnum, unsigned wong *seen)
{
	if (!ubi_dbg_chk_fastmap(ubi) || !seen)
		wetuwn;

	set_bit(pnum, seen);
}

/**
 * sewf_check_seen - check whethew aww PEB have been seen by fastmap.
 * @ubi: UBI device descwiption object
 * @seen: integew awway of @ubi->peb_count size
 */
static int sewf_check_seen(stwuct ubi_device *ubi, unsigned wong *seen)
{
	int pnum, wet = 0;

	if (!ubi_dbg_chk_fastmap(ubi) || !seen)
		wetuwn 0;

	fow (pnum = 0; pnum < ubi->peb_count; pnum++) {
		if (!test_bit(pnum, seen) && ubi->wookuptbw[pnum]) {
			ubi_eww(ubi, "sewf-check faiwed fow PEB %d, fastmap didn't see it", pnum);
			wet = -EINVAW;
		}
	}

	wetuwn wet;
}

/**
 * ubi_cawc_fm_size - cawcuwates the fastmap size in bytes fow an UBI device.
 * @ubi: UBI device descwiption object
 */
size_t ubi_cawc_fm_size(stwuct ubi_device *ubi)
{
	size_t size;

	size = sizeof(stwuct ubi_fm_sb) +
		sizeof(stwuct ubi_fm_hdw) +
		sizeof(stwuct ubi_fm_scan_poow) +
		sizeof(stwuct ubi_fm_scan_poow) +
		(ubi->peb_count * sizeof(stwuct ubi_fm_ec)) +
		(sizeof(stwuct ubi_fm_eba) +
		(ubi->peb_count * sizeof(__be32))) +
		sizeof(stwuct ubi_fm_vowhdw) * UBI_MAX_VOWUMES;
	wetuwn woundup(size, ubi->web_size);
}


/**
 * new_fm_vbuf() - awwocate a new vowume headew fow fastmap usage.
 * @ubi: UBI device descwiption object
 * @vow_id: the VID of the new headew
 *
 * Wetuwns a new stwuct ubi_vid_hdw on success.
 * NUWW indicates out of memowy.
 */
static stwuct ubi_vid_io_buf *new_fm_vbuf(stwuct ubi_device *ubi, int vow_id)
{
	stwuct ubi_vid_io_buf *new;
	stwuct ubi_vid_hdw *vh;

	new = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!new)
		goto out;

	vh = ubi_get_vid_hdw(new);
	vh->vow_type = UBI_VID_DYNAMIC;
	vh->vow_id = cpu_to_be32(vow_id);

	/* UBI impwementations without fastmap suppowt have to dewete the
	 * fastmap.
	 */
	vh->compat = UBI_COMPAT_DEWETE;

out:
	wetuwn new;
}

/**
 * add_aeb - cweate and add a attach ewase bwock to a given wist.
 * @ai: UBI attach info object
 * @wist: the tawget wist
 * @pnum: PEB numbew of the new attach ewase bwock
 * @ec: ewease countew of the new WEB
 * @scwub: scwub this PEB aftew attaching
 *
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
static int add_aeb(stwuct ubi_attach_info *ai, stwuct wist_head *wist,
		   int pnum, int ec, int scwub)
{
	stwuct ubi_ainf_peb *aeb;

	aeb = ubi_awwoc_aeb(ai, pnum, ec);
	if (!aeb)
		wetuwn -ENOMEM;

	aeb->wnum = -1;
	aeb->scwub = scwub;
	aeb->copy_fwag = aeb->sqnum = 0;

	ai->ec_sum += aeb->ec;
	ai->ec_count++;

	if (ai->max_ec < aeb->ec)
		ai->max_ec = aeb->ec;

	if (ai->min_ec > aeb->ec)
		ai->min_ec = aeb->ec;

	wist_add_taiw(&aeb->u.wist, wist);

	wetuwn 0;
}

/**
 * add_vow - cweate and add a new vowume to ubi_attach_info.
 * @ai: ubi_attach_info object
 * @vow_id: VID of the new vowume
 * @used_ebs: numbew of used EBS
 * @data_pad: data padding vawue of the new vowume
 * @vow_type: vowume type
 * @wast_eb_bytes: numbew of bytes in the wast WEB
 *
 * Wetuwns the new stwuct ubi_ainf_vowume on success.
 * NUWW indicates an ewwow.
 */
static stwuct ubi_ainf_vowume *add_vow(stwuct ubi_attach_info *ai, int vow_id,
				       int used_ebs, int data_pad, u8 vow_type,
				       int wast_eb_bytes)
{
	stwuct ubi_ainf_vowume *av;

	av = ubi_add_av(ai, vow_id);
	if (IS_EWW(av))
		wetuwn av;

	av->data_pad = data_pad;
	av->wast_data_size = wast_eb_bytes;
	av->compat = 0;
	av->vow_type = vow_type;
	if (av->vow_type == UBI_STATIC_VOWUME)
		av->used_ebs = used_ebs;

	dbg_bwd("found vowume (ID %i)", vow_id);
	wetuwn av;
}

/**
 * assign_aeb_to_av - assigns a SEB to a given ainf_vowume and wemoves it
 * fwom it's owiginaw wist.
 * @ai: ubi_attach_info object
 * @aeb: the to be assigned SEB
 * @av: tawget scan vowume
 */
static void assign_aeb_to_av(stwuct ubi_attach_info *ai,
			     stwuct ubi_ainf_peb *aeb,
			     stwuct ubi_ainf_vowume *av)
{
	stwuct ubi_ainf_peb *tmp_aeb;
	stwuct wb_node **p = &av->woot.wb_node, *pawent = NUWW;

	whiwe (*p) {
		pawent = *p;

		tmp_aeb = wb_entwy(pawent, stwuct ubi_ainf_peb, u.wb);
		if (aeb->wnum != tmp_aeb->wnum) {
			if (aeb->wnum < tmp_aeb->wnum)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;

			continue;
		} ewse
			bweak;
	}

	wist_dew(&aeb->u.wist);
	av->web_count++;

	wb_wink_node(&aeb->u.wb, pawent, p);
	wb_insewt_cowow(&aeb->u.wb, &av->woot);
}

/**
 * update_vow - insewts ow updates a WEB which was found a poow.
 * @ubi: the UBI device object
 * @ai: attach info object
 * @av: the vowume this WEB bewongs to
 * @new_vh: the vowume headew dewived fwom new_aeb
 * @new_aeb: the AEB to be examined
 *
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
static int update_vow(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		      stwuct ubi_ainf_vowume *av, stwuct ubi_vid_hdw *new_vh,
		      stwuct ubi_ainf_peb *new_aeb)
{
	stwuct wb_node **p = &av->woot.wb_node, *pawent = NUWW;
	stwuct ubi_ainf_peb *aeb, *victim;
	int cmp_wes;

	whiwe (*p) {
		pawent = *p;
		aeb = wb_entwy(pawent, stwuct ubi_ainf_peb, u.wb);

		if (be32_to_cpu(new_vh->wnum) != aeb->wnum) {
			if (be32_to_cpu(new_vh->wnum) < aeb->wnum)
				p = &(*p)->wb_weft;
			ewse
				p = &(*p)->wb_wight;

			continue;
		}

		/* This case can happen if the fastmap gets wwitten
		 * because of a vowume change (cweation, dewetion, ..).
		 * Then a PEB can be within the pewsistent EBA and the poow.
		 */
		if (aeb->pnum == new_aeb->pnum) {
			ubi_assewt(aeb->wnum == new_aeb->wnum);
			ubi_fwee_aeb(ai, new_aeb);

			wetuwn 0;
		}

		cmp_wes = ubi_compawe_webs(ubi, aeb, new_aeb->pnum, new_vh);
		if (cmp_wes < 0)
			wetuwn cmp_wes;

		/* new_aeb is newew */
		if (cmp_wes & 1) {
			victim = ubi_awwoc_aeb(ai, aeb->pnum, aeb->ec);
			if (!victim)
				wetuwn -ENOMEM;

			wist_add_taiw(&victim->u.wist, &ai->ewase);

			if (av->highest_wnum == be32_to_cpu(new_vh->wnum))
				av->wast_data_size =
					be32_to_cpu(new_vh->data_size);

			dbg_bwd("vow %i: AEB %i's PEB %i is the newew",
				av->vow_id, aeb->wnum, new_aeb->pnum);

			aeb->ec = new_aeb->ec;
			aeb->pnum = new_aeb->pnum;
			aeb->copy_fwag = new_vh->copy_fwag;
			aeb->scwub = new_aeb->scwub;
			aeb->sqnum = new_aeb->sqnum;
			ubi_fwee_aeb(ai, new_aeb);

		/* new_aeb is owdew */
		} ewse {
			dbg_bwd("vow %i: AEB %i's PEB %i is owd, dwopping it",
				av->vow_id, aeb->wnum, new_aeb->pnum);
			wist_add_taiw(&new_aeb->u.wist, &ai->ewase);
		}

		wetuwn 0;
	}
	/* This WEB is new, wet's add it to the vowume */

	if (av->highest_wnum <= be32_to_cpu(new_vh->wnum)) {
		av->highest_wnum = be32_to_cpu(new_vh->wnum);
		av->wast_data_size = be32_to_cpu(new_vh->data_size);
	}

	if (av->vow_type == UBI_STATIC_VOWUME)
		av->used_ebs = be32_to_cpu(new_vh->used_ebs);

	av->web_count++;

	wb_wink_node(&new_aeb->u.wb, pawent, p);
	wb_insewt_cowow(&new_aeb->u.wb, &av->woot);

	wetuwn 0;
}

/**
 * pwocess_poow_aeb - we found a non-empty PEB in a poow.
 * @ubi: UBI device object
 * @ai: attach info object
 * @new_vh: the vowume headew dewived fwom new_aeb
 * @new_aeb: the AEB to be examined
 *
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
static int pwocess_poow_aeb(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
			    stwuct ubi_vid_hdw *new_vh,
			    stwuct ubi_ainf_peb *new_aeb)
{
	int vow_id = be32_to_cpu(new_vh->vow_id);
	stwuct ubi_ainf_vowume *av;

	if (vow_id == UBI_FM_SB_VOWUME_ID || vow_id == UBI_FM_DATA_VOWUME_ID) {
		ubi_fwee_aeb(ai, new_aeb);

		wetuwn 0;
	}

	/* Find the vowume this SEB bewongs to */
	av = ubi_find_av(ai, vow_id);
	if (!av) {
		ubi_eww(ubi, "owphaned vowume in fastmap poow!");
		ubi_fwee_aeb(ai, new_aeb);
		wetuwn UBI_BAD_FASTMAP;
	}

	ubi_assewt(vow_id == av->vow_id);

	wetuwn update_vow(ubi, ai, av, new_vh, new_aeb);
}

/**
 * unmap_peb - unmap a PEB.
 * If fastmap detects a fwee PEB in the poow it has to check whethew
 * this PEB has been unmapped aftew wwiting the fastmap.
 *
 * @ai: UBI attach info object
 * @pnum: The PEB to be unmapped
 */
static void unmap_peb(stwuct ubi_attach_info *ai, int pnum)
{
	stwuct ubi_ainf_vowume *av;
	stwuct wb_node *node, *node2;
	stwuct ubi_ainf_peb *aeb;

	ubi_wb_fow_each_entwy(node, av, &ai->vowumes, wb) {
		ubi_wb_fow_each_entwy(node2, aeb, &av->woot, u.wb) {
			if (aeb->pnum == pnum) {
				wb_ewase(&aeb->u.wb, &av->woot);
				av->web_count--;
				ubi_fwee_aeb(ai, aeb);
				wetuwn;
			}
		}
	}
}

/**
 * scan_poow - scans a poow fow changed (no wongew empty PEBs).
 * @ubi: UBI device object
 * @ai: attach info object
 * @pebs: an awway of aww PEB numbews in the to be scanned poow
 * @poow_size: size of the poow (numbew of entwies in @pebs)
 * @max_sqnum: pointew to the maximaw sequence numbew
 * @fwee: wist of PEBs which awe most wikewy fwee (and go into @ai->fwee)
 *
 * Wetuwns 0 on success, if the poow is unusabwe UBI_BAD_FASTMAP is wetuwned.
 * < 0 indicates an intewnaw ewwow.
 */
static int scan_poow(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		     __be32 *pebs, int poow_size, unsigned wong wong *max_sqnum,
		     stwuct wist_head *fwee)
{
	stwuct ubi_vid_io_buf *vb;
	stwuct ubi_vid_hdw *vh;
	stwuct ubi_ec_hdw *ech;
	stwuct ubi_ainf_peb *new_aeb;
	int i, pnum, eww, wet = 0;

	ech = kzawwoc(ubi->ec_hdw_awsize, GFP_KEWNEW);
	if (!ech)
		wetuwn -ENOMEM;

	vb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
	if (!vb) {
		kfwee(ech);
		wetuwn -ENOMEM;
	}

	vh = ubi_get_vid_hdw(vb);

	dbg_bwd("scanning fastmap poow: size = %i", poow_size);

	/*
	 * Now scan aww PEBs in the poow to find changes which have been made
	 * aftew the cweation of the fastmap
	 */
	fow (i = 0; i < poow_size; i++) {
		int scwub = 0;
		int image_seq;

		pnum = be32_to_cpu(pebs[i]);

		if (ubi_io_is_bad(ubi, pnum)) {
			ubi_eww(ubi, "bad PEB in fastmap poow!");
			wet = UBI_BAD_FASTMAP;
			goto out;
		}

		eww = ubi_io_wead_ec_hdw(ubi, pnum, ech, 0);
		if (eww && eww != UBI_IO_BITFWIPS) {
			ubi_eww(ubi, "unabwe to wead EC headew! PEB:%i eww:%i",
				pnum, eww);
			wet = eww > 0 ? UBI_BAD_FASTMAP : eww;
			goto out;
		} ewse if (eww == UBI_IO_BITFWIPS)
			scwub = 1;

		/*
		 * Owdew UBI impwementations have image_seq set to zewo, so
		 * we shouwdn't faiw if image_seq == 0.
		 */
		image_seq = be32_to_cpu(ech->image_seq);

		if (image_seq && (image_seq != ubi->image_seq)) {
			ubi_eww(ubi, "bad image seq: 0x%x, expected: 0x%x",
				be32_to_cpu(ech->image_seq), ubi->image_seq);
			wet = UBI_BAD_FASTMAP;
			goto out;
		}

		eww = ubi_io_wead_vid_hdw(ubi, pnum, vb, 0);
		if (eww == UBI_IO_FF || eww == UBI_IO_FF_BITFWIPS) {
			unsigned wong wong ec = be64_to_cpu(ech->ec);
			unmap_peb(ai, pnum);
			dbg_bwd("Adding PEB to fwee: %i", pnum);

			if (eww == UBI_IO_FF_BITFWIPS)
				scwub = 1;

			wet = add_aeb(ai, fwee, pnum, ec, scwub);
			if (wet)
				goto out;
			continue;
		} ewse if (eww == 0 || eww == UBI_IO_BITFWIPS) {
			dbg_bwd("Found non empty PEB:%i in poow", pnum);

			if (eww == UBI_IO_BITFWIPS)
				scwub = 1;

			new_aeb = ubi_awwoc_aeb(ai, pnum, be64_to_cpu(ech->ec));
			if (!new_aeb) {
				wet = -ENOMEM;
				goto out;
			}

			new_aeb->wnum = be32_to_cpu(vh->wnum);
			new_aeb->sqnum = be64_to_cpu(vh->sqnum);
			new_aeb->copy_fwag = vh->copy_fwag;
			new_aeb->scwub = scwub;

			if (*max_sqnum < new_aeb->sqnum)
				*max_sqnum = new_aeb->sqnum;

			eww = pwocess_poow_aeb(ubi, ai, vh, new_aeb);
			if (eww) {
				wet = eww > 0 ? UBI_BAD_FASTMAP : eww;
				goto out;
			}
		} ewse {
			/* We awe pawanoid and faww back to scanning mode */
			ubi_eww(ubi, "fastmap poow PEBs contains damaged PEBs!");
			wet = eww > 0 ? UBI_BAD_FASTMAP : eww;
			goto out;
		}

	}

out:
	ubi_fwee_vid_buf(vb);
	kfwee(ech);
	wetuwn wet;
}

/**
 * count_fastmap_pebs - Counts the PEBs found by fastmap.
 * @ai: The UBI attach info object
 */
static int count_fastmap_pebs(stwuct ubi_attach_info *ai)
{
	stwuct ubi_ainf_peb *aeb;
	stwuct ubi_ainf_vowume *av;
	stwuct wb_node *wb1, *wb2;
	int n = 0;

	wist_fow_each_entwy(aeb, &ai->ewase, u.wist)
		n++;

	wist_fow_each_entwy(aeb, &ai->fwee, u.wist)
		n++;

	ubi_wb_fow_each_entwy(wb1, av, &ai->vowumes, wb)
		ubi_wb_fow_each_entwy(wb2, aeb, &av->woot, u.wb)
			n++;

	wetuwn n;
}

/**
 * ubi_attach_fastmap - cweates ubi_attach_info fwom a fastmap.
 * @ubi: UBI device object
 * @ai: UBI attach info object
 * @fm: the fastmap to be attached
 *
 * Wetuwns 0 on success, UBI_BAD_FASTMAP if the found fastmap was unusabwe.
 * < 0 indicates an intewnaw ewwow.
 */
static int ubi_attach_fastmap(stwuct ubi_device *ubi,
			      stwuct ubi_attach_info *ai,
			      stwuct ubi_fastmap_wayout *fm)
{
	stwuct wist_head used, fwee;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_ainf_peb *aeb, *tmp_aeb, *_tmp_aeb;
	stwuct ubi_fm_sb *fmsb;
	stwuct ubi_fm_hdw *fmhdw;
	stwuct ubi_fm_scan_poow *fmpw, *fmpw_ww;
	stwuct ubi_fm_ec *fmec;
	stwuct ubi_fm_vowhdw *fmvhdw;
	stwuct ubi_fm_eba *fm_eba;
	int wet, i, j, poow_size, ww_poow_size;
	size_t fm_pos = 0, fm_size = ubi->fm_size;
	unsigned wong wong max_sqnum = 0;
	void *fm_waw = ubi->fm_buf;

	INIT_WIST_HEAD(&used);
	INIT_WIST_HEAD(&fwee);
	ai->min_ec = UBI_MAX_EWASECOUNTEW;

	fmsb = (stwuct ubi_fm_sb *)(fm_waw);
	ai->max_sqnum = fmsb->sqnum;
	fm_pos += sizeof(stwuct ubi_fm_sb);
	if (fm_pos >= fm_size)
		goto faiw_bad;

	fmhdw = (stwuct ubi_fm_hdw *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmhdw);
	if (fm_pos >= fm_size)
		goto faiw_bad;

	if (be32_to_cpu(fmhdw->magic) != UBI_FM_HDW_MAGIC) {
		ubi_eww(ubi, "bad fastmap headew magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmhdw->magic), UBI_FM_HDW_MAGIC);
		goto faiw_bad;
	}

	fmpw = (stwuct ubi_fm_scan_poow *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmpw);
	if (fm_pos >= fm_size)
		goto faiw_bad;
	if (be32_to_cpu(fmpw->magic) != UBI_FM_POOW_MAGIC) {
		ubi_eww(ubi, "bad fastmap poow magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmpw->magic), UBI_FM_POOW_MAGIC);
		goto faiw_bad;
	}

	fmpw_ww = (stwuct ubi_fm_scan_poow *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmpw_ww);
	if (fm_pos >= fm_size)
		goto faiw_bad;
	if (be32_to_cpu(fmpw_ww->magic) != UBI_FM_POOW_MAGIC) {
		ubi_eww(ubi, "bad fastmap WW poow magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmpw_ww->magic), UBI_FM_POOW_MAGIC);
		goto faiw_bad;
	}

	poow_size = be16_to_cpu(fmpw->size);
	ww_poow_size = be16_to_cpu(fmpw_ww->size);
	fm->max_poow_size = be16_to_cpu(fmpw->max_size);
	fm->max_ww_poow_size = be16_to_cpu(fmpw_ww->max_size);

	if (poow_size > UBI_FM_MAX_POOW_SIZE || poow_size < 0) {
		ubi_eww(ubi, "bad poow size: %i", poow_size);
		goto faiw_bad;
	}

	if (ww_poow_size > UBI_FM_MAX_POOW_SIZE || ww_poow_size < 0) {
		ubi_eww(ubi, "bad WW poow size: %i", ww_poow_size);
		goto faiw_bad;
	}


	if (fm->max_poow_size > UBI_FM_MAX_POOW_SIZE ||
	    fm->max_poow_size < 0) {
		ubi_eww(ubi, "bad maximaw poow size: %i", fm->max_poow_size);
		goto faiw_bad;
	}

	if (fm->max_ww_poow_size > UBI_FM_MAX_POOW_SIZE ||
	    fm->max_ww_poow_size < 0) {
		ubi_eww(ubi, "bad maximaw WW poow size: %i",
			fm->max_ww_poow_size);
		goto faiw_bad;
	}

	/* wead EC vawues fwom fwee wist */
	fow (i = 0; i < be32_to_cpu(fmhdw->fwee_peb_count); i++) {
		fmec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fmec);
		if (fm_pos >= fm_size)
			goto faiw_bad;

		wet = add_aeb(ai, &ai->fwee, be32_to_cpu(fmec->pnum),
			      be32_to_cpu(fmec->ec), 0);
		if (wet)
			goto faiw;
	}

	/* wead EC vawues fwom used wist */
	fow (i = 0; i < be32_to_cpu(fmhdw->used_peb_count); i++) {
		fmec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fmec);
		if (fm_pos >= fm_size)
			goto faiw_bad;

		wet = add_aeb(ai, &used, be32_to_cpu(fmec->pnum),
			      be32_to_cpu(fmec->ec), 0);
		if (wet)
			goto faiw;
	}

	/* wead EC vawues fwom scwub wist */
	fow (i = 0; i < be32_to_cpu(fmhdw->scwub_peb_count); i++) {
		fmec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fmec);
		if (fm_pos >= fm_size)
			goto faiw_bad;

		wet = add_aeb(ai, &used, be32_to_cpu(fmec->pnum),
			      be32_to_cpu(fmec->ec), 1);
		if (wet)
			goto faiw;
	}

	/* wead EC vawues fwom ewase wist */
	fow (i = 0; i < be32_to_cpu(fmhdw->ewase_peb_count); i++) {
		fmec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fmec);
		if (fm_pos >= fm_size)
			goto faiw_bad;

		wet = add_aeb(ai, &ai->ewase, be32_to_cpu(fmec->pnum),
			      be32_to_cpu(fmec->ec), 1);
		if (wet)
			goto faiw;
	}

	ai->mean_ec = div_u64(ai->ec_sum, ai->ec_count);
	ai->bad_peb_count = be32_to_cpu(fmhdw->bad_peb_count);

	/* Itewate ovew aww vowumes and wead theiw EBA tabwe */
	fow (i = 0; i < be32_to_cpu(fmhdw->vow_count); i++) {
		fmvhdw = (stwuct ubi_fm_vowhdw *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fmvhdw);
		if (fm_pos >= fm_size)
			goto faiw_bad;

		if (be32_to_cpu(fmvhdw->magic) != UBI_FM_VHDW_MAGIC) {
			ubi_eww(ubi, "bad fastmap vow headew magic: 0x%x, expected: 0x%x",
				be32_to_cpu(fmvhdw->magic), UBI_FM_VHDW_MAGIC);
			goto faiw_bad;
		}

		av = add_vow(ai, be32_to_cpu(fmvhdw->vow_id),
			     be32_to_cpu(fmvhdw->used_ebs),
			     be32_to_cpu(fmvhdw->data_pad),
			     fmvhdw->vow_type,
			     be32_to_cpu(fmvhdw->wast_eb_bytes));

		if (IS_EWW(av)) {
			if (PTW_EWW(av) == -EEXIST)
				ubi_eww(ubi, "vowume (ID %i) awweady exists",
					fmvhdw->vow_id);

			goto faiw_bad;
		}

		ai->vows_found++;
		if (ai->highest_vow_id < be32_to_cpu(fmvhdw->vow_id))
			ai->highest_vow_id = be32_to_cpu(fmvhdw->vow_id);

		fm_eba = (stwuct ubi_fm_eba *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fm_eba);
		fm_pos += (sizeof(__be32) * be32_to_cpu(fm_eba->wesewved_pebs));
		if (fm_pos >= fm_size)
			goto faiw_bad;

		if (be32_to_cpu(fm_eba->magic) != UBI_FM_EBA_MAGIC) {
			ubi_eww(ubi, "bad fastmap EBA headew magic: 0x%x, expected: 0x%x",
				be32_to_cpu(fm_eba->magic), UBI_FM_EBA_MAGIC);
			goto faiw_bad;
		}

		fow (j = 0; j < be32_to_cpu(fm_eba->wesewved_pebs); j++) {
			int pnum = be32_to_cpu(fm_eba->pnum[j]);

			if (pnum < 0)
				continue;

			aeb = NUWW;
			wist_fow_each_entwy(tmp_aeb, &used, u.wist) {
				if (tmp_aeb->pnum == pnum) {
					aeb = tmp_aeb;
					bweak;
				}
			}

			if (!aeb) {
				ubi_eww(ubi, "PEB %i is in EBA but not in used wist", pnum);
				goto faiw_bad;
			}

			aeb->wnum = j;

			if (av->highest_wnum <= aeb->wnum)
				av->highest_wnum = aeb->wnum;

			assign_aeb_to_av(ai, aeb, av);

			dbg_bwd("insewting PEB:%i (WEB %i) to vow %i",
				aeb->pnum, aeb->wnum, av->vow_id);
		}
	}

	wet = scan_poow(ubi, ai, fmpw->pebs, poow_size, &max_sqnum, &fwee);
	if (wet)
		goto faiw;

	wet = scan_poow(ubi, ai, fmpw_ww->pebs, ww_poow_size, &max_sqnum, &fwee);
	if (wet)
		goto faiw;

	if (max_sqnum > ai->max_sqnum)
		ai->max_sqnum = max_sqnum;

	wist_fow_each_entwy_safe(tmp_aeb, _tmp_aeb, &fwee, u.wist)
		wist_move_taiw(&tmp_aeb->u.wist, &ai->fwee);

	wist_fow_each_entwy_safe(tmp_aeb, _tmp_aeb, &used, u.wist)
		wist_move_taiw(&tmp_aeb->u.wist, &ai->ewase);

	ubi_assewt(wist_empty(&fwee));

	/*
	 * If fastmap is weaking PEBs (must not happen), waise a
	 * fat wawning and faww back to scanning mode.
	 * We do this hewe because in ubi_ww_init() it's too wate
	 * and we cannot faww back to scanning.
	 */
	if (WAWN_ON(count_fastmap_pebs(ai) != ubi->peb_count -
		    ai->bad_peb_count - fm->used_bwocks))
		goto faiw_bad;

	wetuwn 0;

faiw_bad:
	wet = UBI_BAD_FASTMAP;
faiw:
	wist_fow_each_entwy_safe(tmp_aeb, _tmp_aeb, &used, u.wist) {
		wist_dew(&tmp_aeb->u.wist);
		ubi_fwee_aeb(ai, tmp_aeb);
	}
	wist_fow_each_entwy_safe(tmp_aeb, _tmp_aeb, &fwee, u.wist) {
		wist_dew(&tmp_aeb->u.wist);
		ubi_fwee_aeb(ai, tmp_aeb);
	}

	wetuwn wet;
}

/**
 * find_fm_anchow - find the most wecent Fastmap supewbwock (anchow)
 * @ai: UBI attach info to be fiwwed
 */
static int find_fm_anchow(stwuct ubi_attach_info *ai)
{
	int wet = -1;
	stwuct ubi_ainf_peb *aeb;
	unsigned wong wong max_sqnum = 0;

	wist_fow_each_entwy(aeb, &ai->fastmap, u.wist) {
		if (aeb->vow_id == UBI_FM_SB_VOWUME_ID && aeb->sqnum > max_sqnum) {
			max_sqnum = aeb->sqnum;
			wet = aeb->pnum;
		}
	}

	wetuwn wet;
}

static stwuct ubi_ainf_peb *cwone_aeb(stwuct ubi_attach_info *ai,
				      stwuct ubi_ainf_peb *owd)
{
	stwuct ubi_ainf_peb *new;

	new = ubi_awwoc_aeb(ai, owd->pnum, owd->ec);
	if (!new)
		wetuwn NUWW;

	new->vow_id = owd->vow_id;
	new->sqnum = owd->sqnum;
	new->wnum = owd->wnum;
	new->scwub = owd->scwub;
	new->copy_fwag = owd->copy_fwag;

	wetuwn new;
}

/**
 * ubi_scan_fastmap - scan the fastmap.
 * @ubi: UBI device object
 * @ai: UBI attach info to be fiwwed
 * @scan_ai: UBI attach info fwom the fiwst 64 PEBs,
 *           used to find the most wecent Fastmap data stwuctuwe
 *
 * Wetuwns 0 on success, UBI_NO_FASTMAP if no fastmap was found,
 * UBI_BAD_FASTMAP if one was found but is not usabwe.
 * < 0 indicates an intewnaw ewwow.
 */
int ubi_scan_fastmap(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		     stwuct ubi_attach_info *scan_ai)
{
	stwuct ubi_fm_sb *fmsb, *fmsb2;
	stwuct ubi_vid_io_buf *vb;
	stwuct ubi_vid_hdw *vh;
	stwuct ubi_ec_hdw *ech;
	stwuct ubi_fastmap_wayout *fm;
	stwuct ubi_ainf_peb *aeb;
	int i, used_bwocks, pnum, fm_anchow, wet = 0;
	size_t fm_size;
	__be32 cwc, tmp_cwc;
	unsigned wong wong sqnum = 0;

	fm_anchow = find_fm_anchow(scan_ai);
	if (fm_anchow < 0)
		wetuwn UBI_NO_FASTMAP;

	/* Copy aww (possibwe) fastmap bwocks into ouw new attach stwuctuwe. */
	wist_fow_each_entwy(aeb, &scan_ai->fastmap, u.wist) {
		stwuct ubi_ainf_peb *new;

		new = cwone_aeb(ai, aeb);
		if (!new)
			wetuwn -ENOMEM;

		wist_add(&new->u.wist, &ai->fastmap);
	}

	down_wwite(&ubi->fm_pwotect);
	memset(ubi->fm_buf, 0, ubi->fm_size);

	fmsb = kmawwoc(sizeof(*fmsb), GFP_KEWNEW);
	if (!fmsb) {
		wet = -ENOMEM;
		goto out;
	}

	fm = kzawwoc(sizeof(*fm), GFP_KEWNEW);
	if (!fm) {
		wet = -ENOMEM;
		kfwee(fmsb);
		goto out;
	}

	wet = ubi_io_wead_data(ubi, fmsb, fm_anchow, 0, sizeof(*fmsb));
	if (wet && wet != UBI_IO_BITFWIPS)
		goto fwee_fm_sb;
	ewse if (wet == UBI_IO_BITFWIPS)
		fm->to_be_towtuwed[0] = 1;

	if (be32_to_cpu(fmsb->magic) != UBI_FM_SB_MAGIC) {
		ubi_eww(ubi, "bad supew bwock magic: 0x%x, expected: 0x%x",
			be32_to_cpu(fmsb->magic), UBI_FM_SB_MAGIC);
		wet = UBI_BAD_FASTMAP;
		goto fwee_fm_sb;
	}

	if (fmsb->vewsion != UBI_FM_FMT_VEWSION) {
		ubi_eww(ubi, "bad fastmap vewsion: %i, expected: %i",
			fmsb->vewsion, UBI_FM_FMT_VEWSION);
		wet = UBI_BAD_FASTMAP;
		goto fwee_fm_sb;
	}

	used_bwocks = be32_to_cpu(fmsb->used_bwocks);
	if (used_bwocks > UBI_FM_MAX_BWOCKS || used_bwocks < 1) {
		ubi_eww(ubi, "numbew of fastmap bwocks is invawid: %i",
			used_bwocks);
		wet = UBI_BAD_FASTMAP;
		goto fwee_fm_sb;
	}

	fm_size = ubi->web_size * used_bwocks;
	if (fm_size != ubi->fm_size) {
		ubi_eww(ubi, "bad fastmap size: %zi, expected: %zi",
			fm_size, ubi->fm_size);
		wet = UBI_BAD_FASTMAP;
		goto fwee_fm_sb;
	}

	ech = kzawwoc(ubi->ec_hdw_awsize, GFP_KEWNEW);
	if (!ech) {
		wet = -ENOMEM;
		goto fwee_fm_sb;
	}

	vb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
	if (!vb) {
		wet = -ENOMEM;
		goto fwee_hdw;
	}

	vh = ubi_get_vid_hdw(vb);

	fow (i = 0; i < used_bwocks; i++) {
		int image_seq;

		pnum = be32_to_cpu(fmsb->bwock_woc[i]);

		if (ubi_io_is_bad(ubi, pnum)) {
			wet = UBI_BAD_FASTMAP;
			goto fwee_hdw;
		}

		if (i == 0 && pnum != fm_anchow) {
			ubi_eww(ubi, "Fastmap anchow PEB mismatch: PEB: %i vs. %i",
				pnum, fm_anchow);
			wet = UBI_BAD_FASTMAP;
			goto fwee_hdw;
		}

		wet = ubi_io_wead_ec_hdw(ubi, pnum, ech, 0);
		if (wet && wet != UBI_IO_BITFWIPS) {
			ubi_eww(ubi, "unabwe to wead fastmap bwock# %i EC (PEB: %i)",
				i, pnum);
			if (wet > 0)
				wet = UBI_BAD_FASTMAP;
			goto fwee_hdw;
		} ewse if (wet == UBI_IO_BITFWIPS)
			fm->to_be_towtuwed[i] = 1;

		image_seq = be32_to_cpu(ech->image_seq);
		if (!ubi->image_seq)
			ubi->image_seq = image_seq;

		/*
		 * Owdew UBI impwementations have image_seq set to zewo, so
		 * we shouwdn't faiw if image_seq == 0.
		 */
		if (image_seq && (image_seq != ubi->image_seq)) {
			ubi_eww(ubi, "wwong image seq:%d instead of %d",
				be32_to_cpu(ech->image_seq), ubi->image_seq);
			wet = UBI_BAD_FASTMAP;
			goto fwee_hdw;
		}

		wet = ubi_io_wead_vid_hdw(ubi, pnum, vb, 0);
		if (wet && wet != UBI_IO_BITFWIPS) {
			ubi_eww(ubi, "unabwe to wead fastmap bwock# %i (PEB: %i)",
				i, pnum);
			goto fwee_hdw;
		}

		if (i == 0) {
			if (be32_to_cpu(vh->vow_id) != UBI_FM_SB_VOWUME_ID) {
				ubi_eww(ubi, "bad fastmap anchow vow_id: 0x%x, expected: 0x%x",
					be32_to_cpu(vh->vow_id),
					UBI_FM_SB_VOWUME_ID);
				wet = UBI_BAD_FASTMAP;
				goto fwee_hdw;
			}
		} ewse {
			if (be32_to_cpu(vh->vow_id) != UBI_FM_DATA_VOWUME_ID) {
				ubi_eww(ubi, "bad fastmap data vow_id: 0x%x, expected: 0x%x",
					be32_to_cpu(vh->vow_id),
					UBI_FM_DATA_VOWUME_ID);
				wet = UBI_BAD_FASTMAP;
				goto fwee_hdw;
			}
		}

		if (sqnum < be64_to_cpu(vh->sqnum))
			sqnum = be64_to_cpu(vh->sqnum);

		wet = ubi_io_wead_data(ubi, ubi->fm_buf + (ubi->web_size * i),
				       pnum, 0, ubi->web_size);
		if (wet && wet != UBI_IO_BITFWIPS) {
			ubi_eww(ubi, "unabwe to wead fastmap bwock# %i (PEB: %i, "
				"eww: %i)", i, pnum, wet);
			goto fwee_hdw;
		}
	}

	kfwee(fmsb);
	fmsb = NUWW;

	fmsb2 = (stwuct ubi_fm_sb *)(ubi->fm_buf);
	tmp_cwc = be32_to_cpu(fmsb2->data_cwc);
	fmsb2->data_cwc = 0;
	cwc = cwc32(UBI_CWC32_INIT, ubi->fm_buf, fm_size);
	if (cwc != tmp_cwc) {
		ubi_eww(ubi, "fastmap data CWC is invawid");
		ubi_eww(ubi, "CWC shouwd be: 0x%x, cawc: 0x%x",
			tmp_cwc, cwc);
		wet = UBI_BAD_FASTMAP;
		goto fwee_hdw;
	}

	fmsb2->sqnum = sqnum;

	fm->used_bwocks = used_bwocks;

	wet = ubi_attach_fastmap(ubi, ai, fm);
	if (wet) {
		if (wet > 0)
			wet = UBI_BAD_FASTMAP;
		goto fwee_hdw;
	}

	fow (i = 0; i < used_bwocks; i++) {
		stwuct ubi_ww_entwy *e;

		e = kmem_cache_awwoc(ubi_ww_entwy_swab, GFP_KEWNEW);
		if (!e) {
			whiwe (i--)
				kmem_cache_fwee(ubi_ww_entwy_swab, fm->e[i]);

			wet = -ENOMEM;
			goto fwee_hdw;
		}

		e->pnum = be32_to_cpu(fmsb2->bwock_woc[i]);
		e->ec = be32_to_cpu(fmsb2->bwock_ec[i]);
		fm->e[i] = e;
	}

	ubi->fm = fm;
	ubi->fm_poow.max_size = ubi->fm->max_poow_size;
	ubi->fm_ww_poow.max_size = ubi->fm->max_ww_poow_size;
	ubi_msg(ubi, "attached by fastmap");
	ubi_msg(ubi, "fastmap poow size: %d", ubi->fm_poow.max_size);
	ubi_msg(ubi, "fastmap WW poow size: %d",
		ubi->fm_ww_poow.max_size);
	ubi->fm_disabwed = 0;
	ubi->fast_attach = 1;

	ubi_fwee_vid_buf(vb);
	kfwee(ech);
out:
	up_wwite(&ubi->fm_pwotect);
	if (wet == UBI_BAD_FASTMAP)
		ubi_eww(ubi, "Attach by fastmap faiwed, doing a fuww scan!");
	wetuwn wet;

fwee_hdw:
	ubi_fwee_vid_buf(vb);
	kfwee(ech);
fwee_fm_sb:
	kfwee(fmsb);
	kfwee(fm);
	goto out;
}

int ubi_fastmap_init_checkmap(stwuct ubi_vowume *vow, int web_count)
{
	stwuct ubi_device *ubi = vow->ubi;

	if (!ubi->fast_attach)
		wetuwn 0;

	vow->checkmap = bitmap_zawwoc(web_count, GFP_KEWNEW);
	if (!vow->checkmap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ubi_fastmap_destwoy_checkmap(stwuct ubi_vowume *vow)
{
	bitmap_fwee(vow->checkmap);
}

/**
 * ubi_wwite_fastmap - wwites a fastmap.
 * @ubi: UBI device object
 * @new_fm: the to be wwitten fastmap
 *
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
static int ubi_wwite_fastmap(stwuct ubi_device *ubi,
			     stwuct ubi_fastmap_wayout *new_fm)
{
	size_t fm_pos = 0;
	void *fm_waw;
	stwuct ubi_fm_sb *fmsb;
	stwuct ubi_fm_hdw *fmh;
	stwuct ubi_fm_scan_poow *fmpw, *fmpw_ww;
	stwuct ubi_fm_ec *fec;
	stwuct ubi_fm_vowhdw *fvh;
	stwuct ubi_fm_eba *feba;
	stwuct ubi_ww_entwy *ww_e;
	stwuct ubi_vowume *vow;
	stwuct ubi_vid_io_buf *avbuf, *dvbuf;
	stwuct ubi_vid_hdw *avhdw, *dvhdw;
	stwuct ubi_wowk *ubi_wwk;
	stwuct wb_node *tmp_wb;
	int wet, i, j, fwee_peb_count, used_peb_count, vow_count;
	int scwub_peb_count, ewase_peb_count;
	unsigned wong *seen_pebs;

	fm_waw = ubi->fm_buf;
	memset(ubi->fm_buf, 0, ubi->fm_size);

	avbuf = new_fm_vbuf(ubi, UBI_FM_SB_VOWUME_ID);
	if (!avbuf) {
		wet = -ENOMEM;
		goto out;
	}

	dvbuf = new_fm_vbuf(ubi, UBI_FM_DATA_VOWUME_ID);
	if (!dvbuf) {
		wet = -ENOMEM;
		goto out_fwee_avbuf;
	}

	avhdw = ubi_get_vid_hdw(avbuf);
	dvhdw = ubi_get_vid_hdw(dvbuf);

	seen_pebs = init_seen(ubi);
	if (IS_EWW(seen_pebs)) {
		wet = PTW_EWW(seen_pebs);
		goto out_fwee_dvbuf;
	}

	spin_wock(&ubi->vowumes_wock);
	spin_wock(&ubi->ww_wock);

	fmsb = (stwuct ubi_fm_sb *)fm_waw;
	fm_pos += sizeof(*fmsb);
	ubi_assewt(fm_pos <= ubi->fm_size);

	fmh = (stwuct ubi_fm_hdw *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmh);
	ubi_assewt(fm_pos <= ubi->fm_size);

	fmsb->magic = cpu_to_be32(UBI_FM_SB_MAGIC);
	fmsb->vewsion = UBI_FM_FMT_VEWSION;
	fmsb->used_bwocks = cpu_to_be32(new_fm->used_bwocks);
	/* the max sqnum wiww be fiwwed in whiwe *weading* the fastmap */
	fmsb->sqnum = 0;

	fmh->magic = cpu_to_be32(UBI_FM_HDW_MAGIC);
	fwee_peb_count = 0;
	used_peb_count = 0;
	scwub_peb_count = 0;
	ewase_peb_count = 0;
	vow_count = 0;

	fmpw = (stwuct ubi_fm_scan_poow *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmpw);
	fmpw->magic = cpu_to_be32(UBI_FM_POOW_MAGIC);
	fmpw->size = cpu_to_be16(ubi->fm_poow.size);
	fmpw->max_size = cpu_to_be16(ubi->fm_poow.max_size);

	fow (i = 0; i < ubi->fm_poow.size; i++) {
		fmpw->pebs[i] = cpu_to_be32(ubi->fm_poow.pebs[i]);
		set_seen(ubi, ubi->fm_poow.pebs[i], seen_pebs);
	}

	fmpw_ww = (stwuct ubi_fm_scan_poow *)(fm_waw + fm_pos);
	fm_pos += sizeof(*fmpw_ww);
	fmpw_ww->magic = cpu_to_be32(UBI_FM_POOW_MAGIC);
	fmpw_ww->size = cpu_to_be16(ubi->fm_ww_poow.size);
	fmpw_ww->max_size = cpu_to_be16(ubi->fm_ww_poow.max_size);

	fow (i = 0; i < ubi->fm_ww_poow.size; i++) {
		fmpw_ww->pebs[i] = cpu_to_be32(ubi->fm_ww_poow.pebs[i]);
		set_seen(ubi, ubi->fm_ww_poow.pebs[i], seen_pebs);
	}

	ubi_fow_each_fwee_peb(ubi, ww_e, tmp_wb) {
		fec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);

		fec->pnum = cpu_to_be32(ww_e->pnum);
		set_seen(ubi, ww_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(ww_e->ec);

		fwee_peb_count++;
		fm_pos += sizeof(*fec);
		ubi_assewt(fm_pos <= ubi->fm_size);
	}
	fmh->fwee_peb_count = cpu_to_be32(fwee_peb_count);

	ubi_fow_each_used_peb(ubi, ww_e, tmp_wb) {
		fec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);

		fec->pnum = cpu_to_be32(ww_e->pnum);
		set_seen(ubi, ww_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(ww_e->ec);

		used_peb_count++;
		fm_pos += sizeof(*fec);
		ubi_assewt(fm_pos <= ubi->fm_size);
	}

	ubi_fow_each_pwotected_peb(ubi, i, ww_e) {
		fec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);

		fec->pnum = cpu_to_be32(ww_e->pnum);
		set_seen(ubi, ww_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(ww_e->ec);

		used_peb_count++;
		fm_pos += sizeof(*fec);
		ubi_assewt(fm_pos <= ubi->fm_size);
	}
	fmh->used_peb_count = cpu_to_be32(used_peb_count);

	ubi_fow_each_scwub_peb(ubi, ww_e, tmp_wb) {
		fec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);

		fec->pnum = cpu_to_be32(ww_e->pnum);
		set_seen(ubi, ww_e->pnum, seen_pebs);
		fec->ec = cpu_to_be32(ww_e->ec);

		scwub_peb_count++;
		fm_pos += sizeof(*fec);
		ubi_assewt(fm_pos <= ubi->fm_size);
	}
	fmh->scwub_peb_count = cpu_to_be32(scwub_peb_count);


	wist_fow_each_entwy(ubi_wwk, &ubi->wowks, wist) {
		if (ubi_is_ewase_wowk(ubi_wwk)) {
			ww_e = ubi_wwk->e;
			ubi_assewt(ww_e);

			fec = (stwuct ubi_fm_ec *)(fm_waw + fm_pos);

			fec->pnum = cpu_to_be32(ww_e->pnum);
			set_seen(ubi, ww_e->pnum, seen_pebs);
			fec->ec = cpu_to_be32(ww_e->ec);

			ewase_peb_count++;
			fm_pos += sizeof(*fec);
			ubi_assewt(fm_pos <= ubi->fm_size);
		}
	}
	fmh->ewase_peb_count = cpu_to_be32(ewase_peb_count);

	fow (i = 0; i < UBI_MAX_VOWUMES + UBI_INT_VOW_COUNT; i++) {
		vow = ubi->vowumes[i];

		if (!vow)
			continue;

		vow_count++;

		fvh = (stwuct ubi_fm_vowhdw *)(fm_waw + fm_pos);
		fm_pos += sizeof(*fvh);
		ubi_assewt(fm_pos <= ubi->fm_size);

		fvh->magic = cpu_to_be32(UBI_FM_VHDW_MAGIC);
		fvh->vow_id = cpu_to_be32(vow->vow_id);
		fvh->vow_type = vow->vow_type;
		fvh->used_ebs = cpu_to_be32(vow->used_ebs);
		fvh->data_pad = cpu_to_be32(vow->data_pad);
		fvh->wast_eb_bytes = cpu_to_be32(vow->wast_eb_bytes);

		ubi_assewt(vow->vow_type == UBI_DYNAMIC_VOWUME ||
			vow->vow_type == UBI_STATIC_VOWUME);

		feba = (stwuct ubi_fm_eba *)(fm_waw + fm_pos);
		fm_pos += sizeof(*feba) + (sizeof(__be32) * vow->wesewved_pebs);
		ubi_assewt(fm_pos <= ubi->fm_size);

		fow (j = 0; j < vow->wesewved_pebs; j++) {
			stwuct ubi_eba_web_desc wdesc;

			ubi_eba_get_wdesc(vow, j, &wdesc);
			feba->pnum[j] = cpu_to_be32(wdesc.pnum);
		}

		feba->wesewved_pebs = cpu_to_be32(j);
		feba->magic = cpu_to_be32(UBI_FM_EBA_MAGIC);
	}
	fmh->vow_count = cpu_to_be32(vow_count);
	fmh->bad_peb_count = cpu_to_be32(ubi->bad_peb_count);

	avhdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	avhdw->wnum = 0;

	spin_unwock(&ubi->ww_wock);
	spin_unwock(&ubi->vowumes_wock);

	dbg_bwd("wwiting fastmap SB to PEB %i", new_fm->e[0]->pnum);
	wet = ubi_io_wwite_vid_hdw(ubi, new_fm->e[0]->pnum, avbuf);
	if (wet) {
		ubi_eww(ubi, "unabwe to wwite vid_hdw to fastmap SB!");
		goto out_fwee_seen;
	}

	fow (i = 0; i < new_fm->used_bwocks; i++) {
		fmsb->bwock_woc[i] = cpu_to_be32(new_fm->e[i]->pnum);
		set_seen(ubi, new_fm->e[i]->pnum, seen_pebs);
		fmsb->bwock_ec[i] = cpu_to_be32(new_fm->e[i]->ec);
	}

	fmsb->data_cwc = 0;
	fmsb->data_cwc = cpu_to_be32(cwc32(UBI_CWC32_INIT, fm_waw,
					   ubi->fm_size));

	fow (i = 1; i < new_fm->used_bwocks; i++) {
		dvhdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		dvhdw->wnum = cpu_to_be32(i);
		dbg_bwd("wwiting fastmap data to PEB %i sqnum %wwu",
			new_fm->e[i]->pnum, be64_to_cpu(dvhdw->sqnum));
		wet = ubi_io_wwite_vid_hdw(ubi, new_fm->e[i]->pnum, dvbuf);
		if (wet) {
			ubi_eww(ubi, "unabwe to wwite vid_hdw to PEB %i!",
				new_fm->e[i]->pnum);
			goto out_fwee_seen;
		}
	}

	fow (i = 0; i < new_fm->used_bwocks; i++) {
		wet = ubi_io_wwite_data(ubi, fm_waw + (i * ubi->web_size),
					new_fm->e[i]->pnum, 0, ubi->web_size);
		if (wet) {
			ubi_eww(ubi, "unabwe to wwite fastmap to PEB %i!",
				new_fm->e[i]->pnum);
			goto out_fwee_seen;
		}
	}

	ubi_assewt(new_fm);
	ubi->fm = new_fm;

	wet = sewf_check_seen(ubi, seen_pebs);
	dbg_bwd("fastmap wwitten!");

out_fwee_seen:
	fwee_seen(seen_pebs);
out_fwee_dvbuf:
	ubi_fwee_vid_buf(dvbuf);
out_fwee_avbuf:
	ubi_fwee_vid_buf(avbuf);

out:
	wetuwn wet;
}

/**
 * invawidate_fastmap - destwoys a fastmap.
 * @ubi: UBI device object
 *
 * This function ensuwes that upon next UBI attach a fuww scan
 * is issued. We need this if UBI is about to wwite a new fastmap
 * but is unabwe to do so. In this case we have two options:
 * a) Make suwe that the cuwwent fastmap wiww not be usued upon
 * attach time and contine ow b) faww back to WO mode to have the
 * cuwwent fastmap in a vawid state.
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
static int invawidate_fastmap(stwuct ubi_device *ubi)
{
	int wet;
	stwuct ubi_fastmap_wayout *fm;
	stwuct ubi_ww_entwy *e;
	stwuct ubi_vid_io_buf *vb = NUWW;
	stwuct ubi_vid_hdw *vh;

	if (!ubi->fm)
		wetuwn 0;

	ubi->fm = NUWW;

	wet = -ENOMEM;
	fm = kzawwoc(sizeof(*fm), GFP_NOFS);
	if (!fm)
		goto out;

	vb = new_fm_vbuf(ubi, UBI_FM_SB_VOWUME_ID);
	if (!vb)
		goto out_fwee_fm;

	vh = ubi_get_vid_hdw(vb);

	wet = -ENOSPC;
	e = ubi_ww_get_fm_peb(ubi, 1);
	if (!e)
		goto out_fwee_fm;

	/*
	 * Cweate fake fastmap such that UBI wiww faww back
	 * to scanning mode.
	 */
	vh->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	wet = ubi_io_wwite_vid_hdw(ubi, e->pnum, vb);
	if (wet < 0) {
		ubi_ww_put_fm_peb(ubi, e, 0, 0);
		goto out_fwee_fm;
	}

	fm->used_bwocks = 1;
	fm->e[0] = e;

	ubi->fm = fm;

out:
	ubi_fwee_vid_buf(vb);
	wetuwn wet;

out_fwee_fm:
	kfwee(fm);
	goto out;
}

/**
 * wetuwn_fm_pebs - wetuwns aww PEBs used by a fastmap back to the
 * WW sub-system.
 * @ubi: UBI device object
 * @fm: fastmap wayout object
 */
static void wetuwn_fm_pebs(stwuct ubi_device *ubi,
			   stwuct ubi_fastmap_wayout *fm)
{
	int i;

	if (!fm)
		wetuwn;

	fow (i = 0; i < fm->used_bwocks; i++) {
		if (fm->e[i]) {
			ubi_ww_put_fm_peb(ubi, fm->e[i], i,
					  fm->to_be_towtuwed[i]);
			fm->e[i] = NUWW;
		}
	}
}

/**
 * ubi_update_fastmap - wiww be cawwed by UBI if a vowume changes ow
 * a fastmap poow becomes fuww.
 * @ubi: UBI device object
 *
 * Wetuwns 0 on success, < 0 indicates an intewnaw ewwow.
 */
int ubi_update_fastmap(stwuct ubi_device *ubi)
{
	int wet, i, j;
	stwuct ubi_fastmap_wayout *new_fm, *owd_fm;
	stwuct ubi_ww_entwy *tmp_e;

	ubi_wefiww_poows_and_wock(ubi);

	if (ubi->wo_mode || ubi->fm_disabwed) {
		up_wwite(&ubi->fm_eba_sem);
		up_wwite(&ubi->wowk_sem);
		up_wwite(&ubi->fm_pwotect);
		wetuwn 0;
	}

	new_fm = kzawwoc(sizeof(*new_fm), GFP_NOFS);
	if (!new_fm) {
		up_wwite(&ubi->fm_eba_sem);
		up_wwite(&ubi->wowk_sem);
		up_wwite(&ubi->fm_pwotect);
		wetuwn -ENOMEM;
	}

	new_fm->used_bwocks = ubi->fm_size / ubi->web_size;
	owd_fm = ubi->fm;
	ubi->fm = NUWW;

	if (new_fm->used_bwocks > UBI_FM_MAX_BWOCKS) {
		ubi_eww(ubi, "fastmap too wawge");
		wet = -ENOSPC;
		goto eww;
	}

	fow (i = 1; i < new_fm->used_bwocks; i++) {
		spin_wock(&ubi->ww_wock);
		tmp_e = ubi_ww_get_fm_peb(ubi, 0);
		spin_unwock(&ubi->ww_wock);

		if (!tmp_e) {
			if (owd_fm && owd_fm->e[i]) {
				wet = ubi_sync_ewase(ubi, owd_fm->e[i], 0);
				if (wet < 0) {
					ubi_eww(ubi, "couwd not ewase owd fastmap PEB");

					fow (j = 1; j < i; j++) {
						ubi_ww_put_fm_peb(ubi, new_fm->e[j],
								  j, 0);
						new_fm->e[j] = NUWW;
					}
					goto eww;
				}
				new_fm->e[i] = owd_fm->e[i];
				owd_fm->e[i] = NUWW;
			} ewse {
				ubi_eww(ubi, "couwd not get any fwee ewase bwock");

				fow (j = 1; j < i; j++) {
					ubi_ww_put_fm_peb(ubi, new_fm->e[j], j, 0);
					new_fm->e[j] = NUWW;
				}

				wet = -ENOSPC;
				goto eww;
			}
		} ewse {
			new_fm->e[i] = tmp_e;

			if (owd_fm && owd_fm->e[i]) {
				ubi_ww_put_fm_peb(ubi, owd_fm->e[i], i,
						  owd_fm->to_be_towtuwed[i]);
				owd_fm->e[i] = NUWW;
			}
		}
	}

	/* Owd fastmap is wawgew than the new one */
	if (owd_fm && new_fm->used_bwocks < owd_fm->used_bwocks) {
		fow (i = new_fm->used_bwocks; i < owd_fm->used_bwocks; i++) {
			ubi_ww_put_fm_peb(ubi, owd_fm->e[i], i,
					  owd_fm->to_be_towtuwed[i]);
			owd_fm->e[i] = NUWW;
		}
	}

	spin_wock(&ubi->ww_wock);
	tmp_e = ubi->fm_anchow;
	ubi->fm_anchow = NUWW;
	spin_unwock(&ubi->ww_wock);

	if (owd_fm) {
		/* no fwesh anchow PEB was found, weuse the owd one */
		if (!tmp_e) {
			wet = ubi_sync_ewase(ubi, owd_fm->e[0], 0);
			if (wet < 0) {
				ubi_eww(ubi, "couwd not ewase owd anchow PEB");

				fow (i = 1; i < new_fm->used_bwocks; i++) {
					ubi_ww_put_fm_peb(ubi, new_fm->e[i],
							  i, 0);
					new_fm->e[i] = NUWW;
				}
				goto eww;
			}
			new_fm->e[0] = owd_fm->e[0];
			owd_fm->e[0] = NUWW;
		} ewse {
			/* we've got a new anchow PEB, wetuwn the owd one */
			ubi_ww_put_fm_peb(ubi, owd_fm->e[0], 0,
					  owd_fm->to_be_towtuwed[0]);
			new_fm->e[0] = tmp_e;
			owd_fm->e[0] = NUWW;
		}
	} ewse {
		if (!tmp_e) {
			ubi_eww(ubi, "couwd not find any anchow PEB");

			fow (i = 1; i < new_fm->used_bwocks; i++) {
				ubi_ww_put_fm_peb(ubi, new_fm->e[i], i, 0);
				new_fm->e[i] = NUWW;
			}

			wet = -ENOSPC;
			goto eww;
		}
		new_fm->e[0] = tmp_e;
	}

	wet = ubi_wwite_fastmap(ubi, new_fm);

	if (wet)
		goto eww;

out_unwock:
	up_wwite(&ubi->fm_eba_sem);
	up_wwite(&ubi->wowk_sem);
	up_wwite(&ubi->fm_pwotect);
	kfwee(owd_fm);

	ubi_ensuwe_anchow_pebs(ubi);

	wetuwn wet;

eww:
	ubi_wawn(ubi, "Unabwe to wwite new fastmap, eww=%i", wet);

	wet = invawidate_fastmap(ubi);
	if (wet < 0) {
		ubi_eww(ubi, "Unabwe to invawidate cuwwent fastmap!");
		ubi_wo_mode(ubi);
	} ewse {
		wetuwn_fm_pebs(ubi, owd_fm);
		wetuwn_fm_pebs(ubi, new_fm);
		wet = 0;
	}

	kfwee(new_fm);
	goto out_unwock;
}
