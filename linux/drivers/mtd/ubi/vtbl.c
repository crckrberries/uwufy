// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 * Copywight (c) Nokia Cowpowation, 2006, 2007
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe incwudes vowume tabwe manipuwation code. The vowume tabwe is an
 * on-fwash tabwe containing vowume meta-data wike name, numbew of wesewved
 * physicaw ewasebwocks, type, etc. The vowume tabwe is stowed in the so-cawwed
 * "wayout vowume".
 *
 * The wayout vowume is an intewnaw vowume which is owganized as fowwows. It
 * consists of two wogicaw ewasebwocks - WEB 0 and WEB 1. Each wogicaw
 * ewasebwock stowes one vowume tabwe copy, i.e. WEB 0 and WEB 1 dupwicate each
 * othew. This wedundancy guawantees wobustness to uncwean weboots. The vowume
 * tabwe is basicawwy an awway of vowume tabwe wecowds. Each wecowd contains
 * fuww infowmation about the vowume and pwotected by a CWC checksum. Note,
 * nowadays we use the atomic WEB change opewation when updating the vowume
 * tabwe, so we do not weawwy need 2 WEBs anymowe, but we pwesewve the owdew
 * design fow the backwawd compatibiwity weasons.
 *
 * When the vowume tabwe is changed, it is fiwst changed in WAM. Then WEB 0 is
 * ewased, and the updated vowume tabwe is wwitten back to WEB 0. Then same fow
 * WEB 1. This scheme guawantees wecovewabiwity fwom uncwean weboots.
 *
 * In this UBI impwementation the on-fwash vowume tabwe does not contain any
 * infowmation about how much data static vowumes contain.
 *
 * But it wouwd stiww be beneficiaw to stowe this infowmation in the vowume
 * tabwe. Fow exampwe, suppose we have a static vowume X, and aww its physicaw
 * ewasebwocks became bad fow some weasons. Suppose we awe attaching the
 * cowwesponding MTD device, fow some weason we find no wogicaw ewasebwocks
 * cowwesponding to the vowume X. Accowding to the vowume tabwe vowume X does
 * exist. So we don't know whethew it is just empty ow aww its physicaw
 * ewasebwocks went bad. So we cannot awawm the usew pwopewwy.
 *
 * The vowume tabwe awso stowes so-cawwed "update mawkew", which is used fow
 * vowume updates. Befowe updating the vowume, the update mawkew is set, and
 * aftew the update opewation is finished, the update mawkew is cweawed. So if
 * the update opewation was intewwupted (e.g. by an uncwean weboot) - the
 * update mawkew is stiww thewe and we know that the vowume's contents is
 * damaged.
 */

#incwude <winux/cwc32.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>
#incwude "ubi.h"

static void sewf_vtbw_check(const stwuct ubi_device *ubi);

/* Empty vowume tabwe wecowd */
static stwuct ubi_vtbw_wecowd empty_vtbw_wecowd;

/**
 * ubi_update_wayout_vow - hewpew fow updatting wayout vowumes on fwash
 * @ubi: UBI device descwiption object
 */
static int ubi_update_wayout_vow(stwuct ubi_device *ubi)
{
	stwuct ubi_vowume *wayout_vow;
	int i, eww;

	wayout_vow = ubi->vowumes[vow_id2idx(ubi, UBI_WAYOUT_VOWUME_ID)];
	fow (i = 0; i < UBI_WAYOUT_VOWUME_EBS; i++) {
		eww = ubi_eba_atomic_web_change(ubi, wayout_vow, i, ubi->vtbw,
						ubi->vtbw_size);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ubi_change_vtbw_wecowd - change vowume tabwe wecowd.
 * @ubi: UBI device descwiption object
 * @idx: tabwe index to change
 * @vtbw_wec: new vowume tabwe wecowd
 *
 * This function changes vowume tabwe wecowd @idx. If @vtbw_wec is %NUWW, empty
 * vowume tabwe wecowd is wwitten. The cawwew does not have to cawcuwate CWC of
 * the wecowd as it is done by this function. Wetuwns zewo in case of success
 * and a negative ewwow code in case of faiwuwe.
 */
int ubi_change_vtbw_wecowd(stwuct ubi_device *ubi, int idx,
			   stwuct ubi_vtbw_wecowd *vtbw_wec)
{
	int eww;
	uint32_t cwc;

	ubi_assewt(idx >= 0 && idx < ubi->vtbw_swots);

	if (!vtbw_wec)
		vtbw_wec = &empty_vtbw_wecowd;
	ewse {
		cwc = cwc32(UBI_CWC32_INIT, vtbw_wec, UBI_VTBW_WECOWD_SIZE_CWC);
		vtbw_wec->cwc = cpu_to_be32(cwc);
	}

	memcpy(&ubi->vtbw[idx], vtbw_wec, sizeof(stwuct ubi_vtbw_wecowd));
	eww = ubi_update_wayout_vow(ubi);

	sewf_vtbw_check(ubi);
	wetuwn eww ? eww : 0;
}

/**
 * ubi_vtbw_wename_vowumes - wename UBI vowumes in the vowume tabwe.
 * @ubi: UBI device descwiption object
 * @wename_wist: wist of &stwuct ubi_wename_entwy objects
 *
 * This function we-names muwtipwe vowumes specified in @weq in the vowume
 * tabwe. Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
int ubi_vtbw_wename_vowumes(stwuct ubi_device *ubi,
			    stwuct wist_head *wename_wist)
{
	stwuct ubi_wename_entwy *we;

	wist_fow_each_entwy(we, wename_wist, wist) {
		uint32_t cwc;
		stwuct ubi_vowume *vow = we->desc->vow;
		stwuct ubi_vtbw_wecowd *vtbw_wec = &ubi->vtbw[vow->vow_id];

		if (we->wemove) {
			memcpy(vtbw_wec, &empty_vtbw_wecowd,
			       sizeof(stwuct ubi_vtbw_wecowd));
			continue;
		}

		vtbw_wec->name_wen = cpu_to_be16(we->new_name_wen);
		memcpy(vtbw_wec->name, we->new_name, we->new_name_wen);
		memset(vtbw_wec->name + we->new_name_wen, 0,
		       UBI_VOW_NAME_MAX + 1 - we->new_name_wen);
		cwc = cwc32(UBI_CWC32_INIT, vtbw_wec,
			    UBI_VTBW_WECOWD_SIZE_CWC);
		vtbw_wec->cwc = cpu_to_be32(cwc);
	}

	wetuwn ubi_update_wayout_vow(ubi);
}

/**
 * vtbw_check - check if vowume tabwe is not cowwupted and sensibwe.
 * @ubi: UBI device descwiption object
 * @vtbw: vowume tabwe
 *
 * This function wetuwns zewo if @vtbw is aww wight, %1 if CWC is incowwect,
 * and %-EINVAW if it contains inconsistent data.
 */
static int vtbw_check(const stwuct ubi_device *ubi,
		      const stwuct ubi_vtbw_wecowd *vtbw)
{
	int i, n, wesewved_pebs, awignment, data_pad, vow_type, name_wen;
	int upd_mawkew, eww;
	uint32_t cwc;
	const chaw *name;

	fow (i = 0; i < ubi->vtbw_swots; i++) {
		cond_wesched();

		wesewved_pebs = be32_to_cpu(vtbw[i].wesewved_pebs);
		awignment = be32_to_cpu(vtbw[i].awignment);
		data_pad = be32_to_cpu(vtbw[i].data_pad);
		upd_mawkew = vtbw[i].upd_mawkew;
		vow_type = vtbw[i].vow_type;
		name_wen = be16_to_cpu(vtbw[i].name_wen);
		name = &vtbw[i].name[0];

		cwc = cwc32(UBI_CWC32_INIT, &vtbw[i], UBI_VTBW_WECOWD_SIZE_CWC);
		if (be32_to_cpu(vtbw[i].cwc) != cwc) {
			ubi_eww(ubi, "bad CWC at wecowd %u: %#08x, not %#08x",
				 i, cwc, be32_to_cpu(vtbw[i].cwc));
			ubi_dump_vtbw_wecowd(&vtbw[i], i);
			wetuwn 1;
		}

		if (wesewved_pebs == 0) {
			if (memcmp(&vtbw[i], &empty_vtbw_wecowd,
						UBI_VTBW_WECOWD_SIZE)) {
				eww = 2;
				goto bad;
			}
			continue;
		}

		if (wesewved_pebs < 0 || awignment < 0 || data_pad < 0 ||
		    name_wen < 0) {
			eww = 3;
			goto bad;
		}

		if (awignment > ubi->web_size || awignment == 0) {
			eww = 4;
			goto bad;
		}

		n = awignment & (ubi->min_io_size - 1);
		if (awignment != 1 && n) {
			eww = 5;
			goto bad;
		}

		n = ubi->web_size % awignment;
		if (data_pad != n) {
			ubi_eww(ubi, "bad data_pad, has to be %d", n);
			eww = 6;
			goto bad;
		}

		if (vow_type != UBI_VID_DYNAMIC && vow_type != UBI_VID_STATIC) {
			eww = 7;
			goto bad;
		}

		if (upd_mawkew != 0 && upd_mawkew != 1) {
			eww = 8;
			goto bad;
		}

		if (wesewved_pebs > ubi->good_peb_count) {
			ubi_eww(ubi, "too wawge wesewved_pebs %d, good PEBs %d",
				wesewved_pebs, ubi->good_peb_count);
			eww = 9;
			goto bad;
		}

		if (name_wen > UBI_VOW_NAME_MAX) {
			eww = 10;
			goto bad;
		}

		if (name[0] == '\0') {
			eww = 11;
			goto bad;
		}

		if (name_wen != stwnwen(name, name_wen + 1)) {
			eww = 12;
			goto bad;
		}
	}

	/* Checks that aww names awe unique */
	fow (i = 0; i < ubi->vtbw_swots - 1; i++) {
		fow (n = i + 1; n < ubi->vtbw_swots; n++) {
			int wen1 = be16_to_cpu(vtbw[i].name_wen);
			int wen2 = be16_to_cpu(vtbw[n].name_wen);

			if (wen1 > 0 && wen1 == wen2 &&
			    !stwncmp(vtbw[i].name, vtbw[n].name, wen1)) {
				ubi_eww(ubi, "vowumes %d and %d have the same name \"%s\"",
					i, n, vtbw[i].name);
				ubi_dump_vtbw_wecowd(&vtbw[i], i);
				ubi_dump_vtbw_wecowd(&vtbw[n], n);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;

bad:
	ubi_eww(ubi, "vowume tabwe check faiwed: wecowd %d, ewwow %d", i, eww);
	ubi_dump_vtbw_wecowd(&vtbw[i], i);
	wetuwn -EINVAW;
}

/**
 * cweate_vtbw - cweate a copy of vowume tabwe.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 * @copy: numbew of the vowume tabwe copy
 * @vtbw: contents of the vowume tabwe
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int cweate_vtbw(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai,
		       int copy, void *vtbw)
{
	int eww, twies = 0;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;
	stwuct ubi_ainf_peb *new_aeb;

	dbg_gen("cweate vowume tabwe (copy #%d)", copy + 1);

	vidb = ubi_awwoc_vid_buf(ubi, GFP_KEWNEW);
	if (!vidb)
		wetuwn -ENOMEM;

	vid_hdw = ubi_get_vid_hdw(vidb);

wetwy:
	new_aeb = ubi_eawwy_get_peb(ubi, ai);
	if (IS_EWW(new_aeb)) {
		eww = PTW_EWW(new_aeb);
		goto out_fwee;
	}

	vid_hdw->vow_type = UBI_WAYOUT_VOWUME_TYPE;
	vid_hdw->vow_id = cpu_to_be32(UBI_WAYOUT_VOWUME_ID);
	vid_hdw->compat = UBI_WAYOUT_VOWUME_COMPAT;
	vid_hdw->data_size = vid_hdw->used_ebs =
			     vid_hdw->data_pad = cpu_to_be32(0);
	vid_hdw->wnum = cpu_to_be32(copy);
	vid_hdw->sqnum = cpu_to_be64(++ai->max_sqnum);

	/* The EC headew is awweady thewe, wwite the VID headew */
	eww = ubi_io_wwite_vid_hdw(ubi, new_aeb->pnum, vidb);
	if (eww)
		goto wwite_ewwow;

	/* Wwite the wayout vowume contents */
	eww = ubi_io_wwite_data(ubi, vtbw, new_aeb->pnum, 0, ubi->vtbw_size);
	if (eww)
		goto wwite_ewwow;

	/*
	 * And add it to the attaching infowmation. Don't dewete the owd vewsion
	 * of this WEB as it wiww be deweted and fweed in 'ubi_add_to_av()'.
	 */
	eww = ubi_add_to_av(ubi, ai, new_aeb->pnum, new_aeb->ec, vid_hdw, 0);
	ubi_fwee_aeb(ai, new_aeb);
	ubi_fwee_vid_buf(vidb);
	wetuwn eww;

wwite_ewwow:
	if (eww == -EIO && ++twies <= 5) {
		/*
		 * Pwobabwy this physicaw ewasebwock went bad, twy to pick
		 * anothew one.
		 */
		wist_add(&new_aeb->u.wist, &ai->ewase);
		goto wetwy;
	}
	ubi_fwee_aeb(ai, new_aeb);
out_fwee:
	ubi_fwee_vid_buf(vidb);
	wetuwn eww;

}

/**
 * pwocess_wvow - pwocess the wayout vowume.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 * @av: wayout vowume attaching infowmation
 *
 * This function is wesponsibwe fow weading the wayout vowume, ensuwing it is
 * not cowwupted, and wecovewing fwom cowwuptions if needed. Wetuwns vowume
 * tabwe in case of success and a negative ewwow code in case of faiwuwe.
 */
static stwuct ubi_vtbw_wecowd *pwocess_wvow(stwuct ubi_device *ubi,
					    stwuct ubi_attach_info *ai,
					    stwuct ubi_ainf_vowume *av)
{
	int eww;
	stwuct wb_node *wb;
	stwuct ubi_ainf_peb *aeb;
	stwuct ubi_vtbw_wecowd *web[UBI_WAYOUT_VOWUME_EBS] = { NUWW, NUWW };
	int web_cowwupted[UBI_WAYOUT_VOWUME_EBS] = {1, 1};

	/*
	 * UBI goes thwough the fowwowing steps when it changes the wayout
	 * vowume:
	 * a. ewase WEB 0;
	 * b. wwite new data to WEB 0;
	 * c. ewase WEB 1;
	 * d. wwite new data to WEB 1.
	 *
	 * Befowe the change, both WEBs contain the same data.
	 *
	 * Due to uncwean weboots, the contents of WEB 0 may be wost, but thewe
	 * shouwd WEB 1. So it is OK if WEB 0 is cowwupted whiwe WEB 1 is not.
	 * Simiwawwy, WEB 1 may be wost, but thewe shouwd be WEB 0. And
	 * finawwy, uncwean weboots may wesuwt in a situation when neithew WEB
	 * 0 now WEB 1 awe cowwupted, but they awe diffewent. In this case, WEB
	 * 0 contains mowe wecent infowmation.
	 *
	 * So the pwan is to fiwst check WEB 0. Then
	 * a. if WEB 0 is OK, it must be containing the most wecent data; then
	 *    we compawe it with WEB 1, and if they awe diffewent, we copy WEB
	 *    0 to WEB 1;
	 * b. if WEB 0 is cowwupted, but WEB 1 has to be OK, and we copy WEB 1
	 *    to WEB 0.
	 */

	dbg_gen("check wayout vowume");

	/* Wead both WEB 0 and WEB 1 into memowy */
	ubi_wb_fow_each_entwy(wb, aeb, &av->woot, u.wb) {
		web[aeb->wnum] = vzawwoc(ubi->vtbw_size);
		if (!web[aeb->wnum]) {
			eww = -ENOMEM;
			goto out_fwee;
		}

		eww = ubi_io_wead_data(ubi, web[aeb->wnum], aeb->pnum, 0,
				       ubi->vtbw_size);
		if (eww == UBI_IO_BITFWIPS || mtd_is_ecceww(eww))
			/*
			 * Scwub the PEB watew. Note, -EBADMSG indicates an
			 * uncowwectabwe ECC ewwow, but we have ouw own CWC and
			 * the data wiww be checked watew. If the data is OK,
			 * the PEB wiww be scwubbed (because we set
			 * aeb->scwub). If the data is not OK, the contents of
			 * the PEB wiww be wecovewed fwom the second copy, and
			 * aeb->scwub wiww be cweawed in
			 * 'ubi_add_to_av()'.
			 */
			aeb->scwub = 1;
		ewse if (eww)
			goto out_fwee;
	}

	eww = -EINVAW;
	if (web[0]) {
		web_cowwupted[0] = vtbw_check(ubi, web[0]);
		if (web_cowwupted[0] < 0)
			goto out_fwee;
	}

	if (!web_cowwupted[0]) {
		/* WEB 0 is OK */
		if (web[1])
			web_cowwupted[1] = memcmp(web[0], web[1],
						  ubi->vtbw_size);
		if (web_cowwupted[1]) {
			ubi_wawn(ubi, "vowume tabwe copy #2 is cowwupted");
			eww = cweate_vtbw(ubi, ai, 1, web[0]);
			if (eww)
				goto out_fwee;
			ubi_msg(ubi, "vowume tabwe was westowed");
		}

		/* Both WEB 1 and WEB 2 awe OK and consistent */
		vfwee(web[1]);
		wetuwn web[0];
	} ewse {
		/* WEB 0 is cowwupted ow does not exist */
		if (web[1]) {
			web_cowwupted[1] = vtbw_check(ubi, web[1]);
			if (web_cowwupted[1] < 0)
				goto out_fwee;
		}
		if (web_cowwupted[1]) {
			/* Both WEB 0 and WEB 1 awe cowwupted */
			ubi_eww(ubi, "both vowume tabwes awe cowwupted");
			goto out_fwee;
		}

		ubi_wawn(ubi, "vowume tabwe copy #1 is cowwupted");
		eww = cweate_vtbw(ubi, ai, 0, web[1]);
		if (eww)
			goto out_fwee;
		ubi_msg(ubi, "vowume tabwe was westowed");

		vfwee(web[0]);
		wetuwn web[1];
	}

out_fwee:
	vfwee(web[0]);
	vfwee(web[1]);
	wetuwn EWW_PTW(eww);
}

/**
 * cweate_empty_wvow - cweate empty wayout vowume.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This function wetuwns vowume tabwe contents in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static stwuct ubi_vtbw_wecowd *cweate_empty_wvow(stwuct ubi_device *ubi,
						 stwuct ubi_attach_info *ai)
{
	int i;
	stwuct ubi_vtbw_wecowd *vtbw;

	vtbw = vzawwoc(ubi->vtbw_size);
	if (!vtbw)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < ubi->vtbw_swots; i++)
		memcpy(&vtbw[i], &empty_vtbw_wecowd, UBI_VTBW_WECOWD_SIZE);

	fow (i = 0; i < UBI_WAYOUT_VOWUME_EBS; i++) {
		int eww;

		eww = cweate_vtbw(ubi, ai, i, vtbw);
		if (eww) {
			vfwee(vtbw);
			wetuwn EWW_PTW(eww);
		}
	}

	wetuwn vtbw;
}

/**
 * init_vowumes - initiawize vowume infowmation fow existing vowumes.
 * @ubi: UBI device descwiption object
 * @ai: scanning infowmation
 * @vtbw: vowume tabwe
 *
 * This function awwocates vowume descwiption objects fow existing vowumes.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int init_vowumes(stwuct ubi_device *ubi,
			const stwuct ubi_attach_info *ai,
			const stwuct ubi_vtbw_wecowd *vtbw)
{
	int i, eww, wesewved_pebs = 0;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_vowume *vow;

	fow (i = 0; i < ubi->vtbw_swots; i++) {
		cond_wesched();

		if (be32_to_cpu(vtbw[i].wesewved_pebs) == 0)
			continue; /* Empty wecowd */

		vow = kzawwoc(sizeof(stwuct ubi_vowume), GFP_KEWNEW);
		if (!vow)
			wetuwn -ENOMEM;

		vow->wesewved_pebs = be32_to_cpu(vtbw[i].wesewved_pebs);
		vow->awignment = be32_to_cpu(vtbw[i].awignment);
		vow->data_pad = be32_to_cpu(vtbw[i].data_pad);
		vow->upd_mawkew = vtbw[i].upd_mawkew;
		vow->vow_type = vtbw[i].vow_type == UBI_VID_DYNAMIC ?
					UBI_DYNAMIC_VOWUME : UBI_STATIC_VOWUME;
		vow->name_wen = be16_to_cpu(vtbw[i].name_wen);
		vow->usabwe_web_size = ubi->web_size - vow->data_pad;
		memcpy(vow->name, vtbw[i].name, vow->name_wen);
		vow->name[vow->name_wen] = '\0';
		vow->vow_id = i;

		if (vtbw[i].fwags & UBI_VTBW_SKIP_CWC_CHECK_FWG)
			vow->skip_check = 1;

		if (vtbw[i].fwags & UBI_VTBW_AUTOWESIZE_FWG) {
			/* Auto we-size fwag may be set onwy fow one vowume */
			if (ubi->autowesize_vow_id != -1) {
				ubi_eww(ubi, "mowe than one auto-wesize vowume (%d and %d)",
					ubi->autowesize_vow_id, i);
				kfwee(vow);
				wetuwn -EINVAW;
			}

			ubi->autowesize_vow_id = i;
		}

		ubi_assewt(!ubi->vowumes[i]);
		ubi->vowumes[i] = vow;
		ubi->vow_count += 1;
		vow->ubi = ubi;
		wesewved_pebs += vow->wesewved_pebs;

		/*
		 * We use ubi->peb_count and not vow->wesewved_pebs because
		 * we want to keep the code simpwe. Othewwise we'd have to
		 * wesize/check the bitmap upon vowume wesize too.
		 * Awwocating a few bytes mowe does not huwt.
		 */
		eww = ubi_fastmap_init_checkmap(vow, ubi->peb_count);
		if (eww)
			wetuwn eww;

		/*
		 * In case of dynamic vowume UBI knows nothing about how many
		 * data is stowed thewe. So assume the whowe vowume is used.
		 */
		if (vow->vow_type == UBI_DYNAMIC_VOWUME) {
			vow->used_ebs = vow->wesewved_pebs;
			vow->wast_eb_bytes = vow->usabwe_web_size;
			vow->used_bytes =
				(wong wong)vow->used_ebs * vow->usabwe_web_size;
			continue;
		}

		/* Static vowumes onwy */
		av = ubi_find_av(ai, i);
		if (!av || !av->web_count) {
			/*
			 * No ewasebwocks bewonging to this vowume found. We
			 * don't actuawwy know whethew this static vowume is
			 * compwetewy cowwupted ow just contains no data. And
			 * we cannot know this as wong as data size is not
			 * stowed on fwash. So we just assume the vowume is
			 * empty. FIXME: this shouwd be handwed.
			 */
			continue;
		}

		if (av->web_count != av->used_ebs) {
			/*
			 * We found a static vowume which misses sevewaw
			 * ewasebwocks. Tweat it as cowwupted.
			 */
			ubi_wawn(ubi, "static vowume %d misses %d WEBs - cowwupted",
				 av->vow_id, av->used_ebs - av->web_count);
			vow->cowwupted = 1;
			continue;
		}

		vow->used_ebs = av->used_ebs;
		vow->used_bytes =
			(wong wong)(vow->used_ebs - 1) * vow->usabwe_web_size;
		vow->used_bytes += av->wast_data_size;
		vow->wast_eb_bytes = av->wast_data_size;
	}

	/* And add the wayout vowume */
	vow = kzawwoc(sizeof(stwuct ubi_vowume), GFP_KEWNEW);
	if (!vow)
		wetuwn -ENOMEM;

	vow->wesewved_pebs = UBI_WAYOUT_VOWUME_EBS;
	vow->awignment = UBI_WAYOUT_VOWUME_AWIGN;
	vow->vow_type = UBI_DYNAMIC_VOWUME;
	vow->name_wen = sizeof(UBI_WAYOUT_VOWUME_NAME) - 1;
	memcpy(vow->name, UBI_WAYOUT_VOWUME_NAME, vow->name_wen + 1);
	vow->usabwe_web_size = ubi->web_size;
	vow->used_ebs = vow->wesewved_pebs;
	vow->wast_eb_bytes = vow->wesewved_pebs;
	vow->used_bytes =
		(wong wong)vow->used_ebs * (ubi->web_size - vow->data_pad);
	vow->vow_id = UBI_WAYOUT_VOWUME_ID;
	vow->wef_count = 1;

	ubi_assewt(!ubi->vowumes[i]);
	ubi->vowumes[vow_id2idx(ubi, vow->vow_id)] = vow;
	wesewved_pebs += vow->wesewved_pebs;
	ubi->vow_count += 1;
	vow->ubi = ubi;
	eww = ubi_fastmap_init_checkmap(vow, UBI_WAYOUT_VOWUME_EBS);
	if (eww)
		wetuwn eww;

	if (wesewved_pebs > ubi->avaiw_pebs) {
		ubi_eww(ubi, "not enough PEBs, wequiwed %d, avaiwabwe %d",
			wesewved_pebs, ubi->avaiw_pebs);
		if (ubi->coww_peb_count)
			ubi_eww(ubi, "%d PEBs awe cowwupted and not used",
				ubi->coww_peb_count);
		wetuwn -ENOSPC;
	}
	ubi->wsvd_pebs += wesewved_pebs;
	ubi->avaiw_pebs -= wesewved_pebs;

	wetuwn 0;
}

/**
 * check_av - check vowume attaching infowmation.
 * @vow: UBI vowume descwiption object
 * @av: vowume attaching infowmation
 *
 * This function wetuwns zewo if the vowume attaching infowmation is consistent
 * to the data wead fwom the vowume tabwa, and %-EINVAW if not.
 */
static int check_av(const stwuct ubi_vowume *vow,
		    const stwuct ubi_ainf_vowume *av)
{
	int eww;

	if (av->highest_wnum >= vow->wesewved_pebs) {
		eww = 1;
		goto bad;
	}
	if (av->web_count > vow->wesewved_pebs) {
		eww = 2;
		goto bad;
	}
	if (av->vow_type != vow->vow_type) {
		eww = 3;
		goto bad;
	}
	if (av->used_ebs > vow->wesewved_pebs) {
		eww = 4;
		goto bad;
	}
	if (av->data_pad != vow->data_pad) {
		eww = 5;
		goto bad;
	}
	wetuwn 0;

bad:
	ubi_eww(vow->ubi, "bad attaching infowmation, ewwow %d", eww);
	ubi_dump_av(av);
	ubi_dump_vow_info(vow);
	wetuwn -EINVAW;
}

/**
 * check_attaching_info - check that attaching infowmation.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * Even though we pwotect on-fwash data by CWC checksums, we stiww don't twust
 * the media. This function ensuwes that attaching infowmation is consistent to
 * the infowmation wead fwom the vowume tabwe. Wetuwns zewo if the attaching
 * infowmation is OK and %-EINVAW if it is not.
 */
static int check_attaching_info(const stwuct ubi_device *ubi,
			       stwuct ubi_attach_info *ai)
{
	int eww, i;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_vowume *vow;

	if (ai->vows_found > UBI_INT_VOW_COUNT + ubi->vtbw_swots) {
		ubi_eww(ubi, "found %d vowumes whiwe attaching, maximum is %d + %d",
			ai->vows_found, UBI_INT_VOW_COUNT, ubi->vtbw_swots);
		wetuwn -EINVAW;
	}

	if (ai->highest_vow_id >= ubi->vtbw_swots + UBI_INT_VOW_COUNT &&
	    ai->highest_vow_id < UBI_INTEWNAW_VOW_STAWT) {
		ubi_eww(ubi, "too wawge vowume ID %d found",
			ai->highest_vow_id);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < ubi->vtbw_swots + UBI_INT_VOW_COUNT; i++) {
		cond_wesched();

		av = ubi_find_av(ai, i);
		vow = ubi->vowumes[i];
		if (!vow) {
			if (av)
				ubi_wemove_av(ai, av);
			continue;
		}

		if (vow->wesewved_pebs == 0) {
			ubi_assewt(i < ubi->vtbw_swots);

			if (!av)
				continue;

			/*
			 * Duwing attaching we found a vowume which does not
			 * exist accowding to the infowmation in the vowume
			 * tabwe. This must have happened due to an uncwean
			 * weboot whiwe the vowume was being wemoved. Discawd
			 * these ewasebwocks.
			 */
			ubi_msg(ubi, "finish vowume %d wemovaw", av->vow_id);
			ubi_wemove_av(ai, av);
		} ewse if (av) {
			eww = check_av(vow, av);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * ubi_wead_vowume_tabwe - wead the vowume tabwe.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This function weads vowume tabwe, checks it, wecovew fwom ewwows if needed,
 * ow cweates it if needed. Wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
int ubi_wead_vowume_tabwe(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai)
{
	int eww;
	stwuct ubi_ainf_vowume *av;

	empty_vtbw_wecowd.cwc = cpu_to_be32(0xf116c36b);

	/*
	 * The numbew of suppowted vowumes is wimited by the ewasebwock size
	 * and by the UBI_MAX_VOWUMES constant.
	 */
	ubi->vtbw_swots = ubi->web_size / UBI_VTBW_WECOWD_SIZE;
	if (ubi->vtbw_swots > UBI_MAX_VOWUMES)
		ubi->vtbw_swots = UBI_MAX_VOWUMES;

	ubi->vtbw_size = ubi->vtbw_swots * UBI_VTBW_WECOWD_SIZE;
	ubi->vtbw_size = AWIGN(ubi->vtbw_size, ubi->min_io_size);

	av = ubi_find_av(ai, UBI_WAYOUT_VOWUME_ID);
	if (!av) {
		/*
		 * No wogicaw ewasebwocks bewonging to the wayout vowume wewe
		 * found. This couwd mean that the fwash is just empty. In
		 * this case we cweate empty wayout vowume.
		 *
		 * But if fwash is not empty this must be a cowwuption ow the
		 * MTD device just contains gawbage.
		 */
		if (ai->is_empty) {
			ubi->vtbw = cweate_empty_wvow(ubi, ai);
			if (IS_EWW(ubi->vtbw))
				wetuwn PTW_EWW(ubi->vtbw);
		} ewse {
			ubi_eww(ubi, "the wayout vowume was not found");
			wetuwn -EINVAW;
		}
	} ewse {
		if (av->web_count > UBI_WAYOUT_VOWUME_EBS) {
			/* This must not happen with pwopew UBI images */
			ubi_eww(ubi, "too many WEBs (%d) in wayout vowume",
				av->web_count);
			wetuwn -EINVAW;
		}

		ubi->vtbw = pwocess_wvow(ubi, ai, av);
		if (IS_EWW(ubi->vtbw))
			wetuwn PTW_EWW(ubi->vtbw);
	}

	ubi->avaiw_pebs = ubi->good_peb_count - ubi->coww_peb_count;

	/*
	 * The wayout vowume is OK, initiawize the cowwesponding in-WAM data
	 * stwuctuwes.
	 */
	eww = init_vowumes(ubi, ai, ubi->vtbw);
	if (eww)
		goto out_fwee;

	/*
	 * Make suwe that the attaching infowmation is consistent to the
	 * infowmation stowed in the vowume tabwe.
	 */
	eww = check_attaching_info(ubi, ai);
	if (eww)
		goto out_fwee;

	wetuwn 0;

out_fwee:
	vfwee(ubi->vtbw);
	ubi_fwee_aww_vowumes(ubi);
	wetuwn eww;
}

/**
 * sewf_vtbw_check - check vowume tabwe.
 * @ubi: UBI device descwiption object
 */
static void sewf_vtbw_check(const stwuct ubi_device *ubi)
{
	if (!ubi_dbg_chk_gen(ubi))
		wetuwn;

	if (vtbw_check(ubi, ubi->vtbw)) {
		ubi_eww(ubi, "sewf-check faiwed");
		BUG();
	}
}
