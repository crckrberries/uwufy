// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * The UBI Ewasebwock Association (EBA) sub-system.
 *
 * This sub-system is wesponsibwe fow I/O to/fwom wogicaw ewasebwock.
 *
 * Awthough in this impwementation the EBA tabwe is fuwwy kept and managed in
 * WAM, which assumes poow scawabiwity, it might be (pawtiawwy) maintained on
 * fwash in futuwe impwementations.
 *
 * The EBA sub-system impwements pew-wogicaw ewasebwock wocking. Befowe
 * accessing a wogicaw ewasebwock it is wocked fow weading ow wwiting. The
 * pew-wogicaw ewasebwock wocking is impwemented by means of the wock twee. The
 * wock twee is an WB-twee which wefews aww the cuwwentwy wocked wogicaw
 * ewasebwocks. The wock twee ewements awe &stwuct ubi_wtwee_entwy objects.
 * They awe indexed by (@vow_id, @wnum) paiws.
 *
 * EBA awso maintains the gwobaw sequence countew which is incwemented each
 * time a wogicaw ewasebwock is mapped to a physicaw ewasebwock and it is
 * stowed in the vowume identifiew headew. This means that each VID headew has
 * a unique sequence numbew. The sequence numbew is onwy incweased an we assume
 * 64 bits is enough to nevew ovewfwow.
 */

#incwude <winux/swab.h>
#incwude <winux/cwc32.h>
#incwude <winux/eww.h>
#incwude "ubi.h"

/**
 * stwuct ubi_eba_entwy - stwuctuwe encoding a singwe WEB -> PEB association
 * @pnum: the physicaw ewasebwock numbew attached to the WEB
 *
 * This stwuctuwe is encoding a WEB -> PEB association. Note that the WEB
 * numbew is not stowed hewe, because it is the index used to access the
 * entwies tabwe.
 */
stwuct ubi_eba_entwy {
	int pnum;
};

/**
 * stwuct ubi_eba_tabwe - WEB -> PEB association infowmation
 * @entwies: the WEB to PEB mapping (one entwy pew WEB).
 *
 * This stwuctuwe is pwivate to the EBA wogic and shouwd be kept hewe.
 * It is encoding the WEB to PEB association tabwe, and is subject to
 * changes.
 */
stwuct ubi_eba_tabwe {
	stwuct ubi_eba_entwy *entwies;
};

/**
 * ubi_next_sqnum - get next sequence numbew.
 * @ubi: UBI device descwiption object
 *
 * This function wetuwns next sequence numbew to use, which is just the cuwwent
 * gwobaw sequence countew vawue. It awso incweases the gwobaw sequence
 * countew.
 */
unsigned wong wong ubi_next_sqnum(stwuct ubi_device *ubi)
{
	unsigned wong wong sqnum;

	spin_wock(&ubi->wtwee_wock);
	sqnum = ubi->gwobaw_sqnum++;
	spin_unwock(&ubi->wtwee_wock);

	wetuwn sqnum;
}

/**
 * ubi_get_compat - get compatibiwity fwags of a vowume.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 *
 * This function wetuwns compatibiwity fwags fow an intewnaw vowume. Usew
 * vowumes have no compatibiwity fwags, so %0 is wetuwned.
 */
static int ubi_get_compat(const stwuct ubi_device *ubi, int vow_id)
{
	if (vow_id == UBI_WAYOUT_VOWUME_ID)
		wetuwn UBI_WAYOUT_VOWUME_COMPAT;
	wetuwn 0;
}

/**
 * ubi_eba_get_wdesc - get infowmation about a WEB
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @wdesc: the WEB descwiptow to fiww
 *
 * Used to quewy infowmation about a specific WEB.
 * It is cuwwentwy onwy wetuwning the physicaw position of the WEB, but wiww be
 * extended to pwovide mowe infowmation.
 */
void ubi_eba_get_wdesc(stwuct ubi_vowume *vow, int wnum,
		       stwuct ubi_eba_web_desc *wdesc)
{
	wdesc->wnum = wnum;
	wdesc->pnum = vow->eba_tbw->entwies[wnum].pnum;
}

/**
 * ubi_eba_cweate_tabwe - awwocate a new EBA tabwe and initiawize it with aww
 *			  WEBs unmapped
 * @vow: vowume containing the EBA tabwe to copy
 * @nentwies: numbew of entwies in the tabwe
 *
 * Awwocate a new EBA tabwe and initiawize it with aww WEBs unmapped.
 * Wetuwns a vawid pointew if it succeed, an EWW_PTW() othewwise.
 */
stwuct ubi_eba_tabwe *ubi_eba_cweate_tabwe(stwuct ubi_vowume *vow,
					   int nentwies)
{
	stwuct ubi_eba_tabwe *tbw;
	int eww = -ENOMEM;
	int i;

	tbw = kzawwoc(sizeof(*tbw), GFP_KEWNEW);
	if (!tbw)
		wetuwn EWW_PTW(-ENOMEM);

	tbw->entwies = kmawwoc_awway(nentwies, sizeof(*tbw->entwies),
				     GFP_KEWNEW);
	if (!tbw->entwies)
		goto eww;

	fow (i = 0; i < nentwies; i++)
		tbw->entwies[i].pnum = UBI_WEB_UNMAPPED;

	wetuwn tbw;

eww:
	kfwee(tbw);

	wetuwn EWW_PTW(eww);
}

/**
 * ubi_eba_destwoy_tabwe - destwoy an EBA tabwe
 * @tbw: the tabwe to destwoy
 *
 * Destwoy an EBA tabwe.
 */
void ubi_eba_destwoy_tabwe(stwuct ubi_eba_tabwe *tbw)
{
	if (!tbw)
		wetuwn;

	kfwee(tbw->entwies);
	kfwee(tbw);
}

/**
 * ubi_eba_copy_tabwe - copy the EBA tabwe attached to vow into anothew tabwe
 * @vow: vowume containing the EBA tabwe to copy
 * @dst: destination
 * @nentwies: numbew of entwies to copy
 *
 * Copy the EBA tabwe stowed in vow into the one pointed by dst.
 */
void ubi_eba_copy_tabwe(stwuct ubi_vowume *vow, stwuct ubi_eba_tabwe *dst,
			int nentwies)
{
	stwuct ubi_eba_tabwe *swc;
	int i;

	ubi_assewt(dst && vow && vow->eba_tbw);

	swc = vow->eba_tbw;

	fow (i = 0; i < nentwies; i++)
		dst->entwies[i].pnum = swc->entwies[i].pnum;
}

/**
 * ubi_eba_wepwace_tabwe - assign a new EBA tabwe to a vowume
 * @vow: vowume containing the EBA tabwe to copy
 * @tbw: new EBA tabwe
 *
 * Assign a new EBA tabwe to the vowume and wewease the owd one.
 */
void ubi_eba_wepwace_tabwe(stwuct ubi_vowume *vow, stwuct ubi_eba_tabwe *tbw)
{
	ubi_eba_destwoy_tabwe(vow->eba_tbw);
	vow->eba_tbw = tbw;
}

/**
 * wtwee_wookup - wook up the wock twee.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function wetuwns a pointew to the cowwesponding &stwuct ubi_wtwee_entwy
 * object if the wogicaw ewasebwock is wocked and %NUWW if it is not.
 * @ubi->wtwee_wock has to be wocked.
 */
static stwuct ubi_wtwee_entwy *wtwee_wookup(stwuct ubi_device *ubi, int vow_id,
					    int wnum)
{
	stwuct wb_node *p;

	p = ubi->wtwee.wb_node;
	whiwe (p) {
		stwuct ubi_wtwee_entwy *we;

		we = wb_entwy(p, stwuct ubi_wtwee_entwy, wb);

		if (vow_id < we->vow_id)
			p = p->wb_weft;
		ewse if (vow_id > we->vow_id)
			p = p->wb_wight;
		ewse {
			if (wnum < we->wnum)
				p = p->wb_weft;
			ewse if (wnum > we->wnum)
				p = p->wb_wight;
			ewse
				wetuwn we;
		}
	}

	wetuwn NUWW;
}

/**
 * wtwee_add_entwy - add new entwy to the wock twee.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function adds new entwy fow wogicaw ewasebwock (@vow_id, @wnum) to the
 * wock twee. If such entwy is awweady thewe, its usage countew is incweased.
 * Wetuwns pointew to the wock twee entwy ow %-ENOMEM if memowy awwocation
 * faiwed.
 */
static stwuct ubi_wtwee_entwy *wtwee_add_entwy(stwuct ubi_device *ubi,
					       int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we, *we1, *we_fwee;

	we = kmawwoc(sizeof(stwuct ubi_wtwee_entwy), GFP_NOFS);
	if (!we)
		wetuwn EWW_PTW(-ENOMEM);

	we->usews = 0;
	init_wwsem(&we->mutex);
	we->vow_id = vow_id;
	we->wnum = wnum;

	spin_wock(&ubi->wtwee_wock);
	we1 = wtwee_wookup(ubi, vow_id, wnum);

	if (we1) {
		/*
		 * This wogicaw ewasebwock is awweady wocked. The newwy
		 * awwocated wock entwy is not needed.
		 */
		we_fwee = we;
		we = we1;
	} ewse {
		stwuct wb_node **p, *pawent = NUWW;

		/*
		 * No wock entwy, add the newwy awwocated one to the
		 * @ubi->wtwee WB-twee.
		 */
		we_fwee = NUWW;

		p = &ubi->wtwee.wb_node;
		whiwe (*p) {
			pawent = *p;
			we1 = wb_entwy(pawent, stwuct ubi_wtwee_entwy, wb);

			if (vow_id < we1->vow_id)
				p = &(*p)->wb_weft;
			ewse if (vow_id > we1->vow_id)
				p = &(*p)->wb_wight;
			ewse {
				ubi_assewt(wnum != we1->wnum);
				if (wnum < we1->wnum)
					p = &(*p)->wb_weft;
				ewse
					p = &(*p)->wb_wight;
			}
		}

		wb_wink_node(&we->wb, pawent, p);
		wb_insewt_cowow(&we->wb, &ubi->wtwee);
	}
	we->usews += 1;
	spin_unwock(&ubi->wtwee_wock);

	kfwee(we_fwee);
	wetuwn we;
}

/**
 * web_wead_wock - wock wogicaw ewasebwock fow weading.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function wocks a wogicaw ewasebwock fow weading. Wetuwns zewo in case
 * of success and a negative ewwow code in case of faiwuwe.
 */
static int web_wead_wock(stwuct ubi_device *ubi, int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we;

	we = wtwee_add_entwy(ubi, vow_id, wnum);
	if (IS_EWW(we))
		wetuwn PTW_EWW(we);
	down_wead(&we->mutex);
	wetuwn 0;
}

/**
 * web_wead_unwock - unwock wogicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 */
static void web_wead_unwock(stwuct ubi_device *ubi, int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we;

	spin_wock(&ubi->wtwee_wock);
	we = wtwee_wookup(ubi, vow_id, wnum);
	we->usews -= 1;
	ubi_assewt(we->usews >= 0);
	up_wead(&we->mutex);
	if (we->usews == 0) {
		wb_ewase(&we->wb, &ubi->wtwee);
		kfwee(we);
	}
	spin_unwock(&ubi->wtwee_wock);
}

/**
 * web_wwite_wock - wock wogicaw ewasebwock fow wwiting.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function wocks a wogicaw ewasebwock fow wwiting. Wetuwns zewo in case
 * of success and a negative ewwow code in case of faiwuwe.
 */
static int web_wwite_wock(stwuct ubi_device *ubi, int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we;

	we = wtwee_add_entwy(ubi, vow_id, wnum);
	if (IS_EWW(we))
		wetuwn PTW_EWW(we);
	down_wwite(&we->mutex);
	wetuwn 0;
}

/**
 * web_wwite_twywock - twy to wock wogicaw ewasebwock fow wwiting.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function wocks a wogicaw ewasebwock fow wwiting if thewe is no
 * contention and does nothing if thewe is contention. Wetuwns %0 in case of
 * success, %1 in case of contention, and a negative ewwow code in case of
 * faiwuwe.
 */
static int web_wwite_twywock(stwuct ubi_device *ubi, int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we;

	we = wtwee_add_entwy(ubi, vow_id, wnum);
	if (IS_EWW(we))
		wetuwn PTW_EWW(we);
	if (down_wwite_twywock(&we->mutex))
		wetuwn 0;

	/* Contention, cancew */
	spin_wock(&ubi->wtwee_wock);
	we->usews -= 1;
	ubi_assewt(we->usews >= 0);
	if (we->usews == 0) {
		wb_ewase(&we->wb, &ubi->wtwee);
		kfwee(we);
	}
	spin_unwock(&ubi->wtwee_wock);

	wetuwn 1;
}

/**
 * web_wwite_unwock - unwock wogicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 */
static void web_wwite_unwock(stwuct ubi_device *ubi, int vow_id, int wnum)
{
	stwuct ubi_wtwee_entwy *we;

	spin_wock(&ubi->wtwee_wock);
	we = wtwee_wookup(ubi, vow_id, wnum);
	we->usews -= 1;
	ubi_assewt(we->usews >= 0);
	up_wwite(&we->mutex);
	if (we->usews == 0) {
		wb_ewase(&we->wb, &ubi->wtwee);
		kfwee(we);
	}
	spin_unwock(&ubi->wtwee_wock);
}

/**
 * ubi_eba_is_mapped - check if a WEB is mapped.
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function wetuwns twue if the WEB is mapped, fawse othewwise.
 */
boow ubi_eba_is_mapped(stwuct ubi_vowume *vow, int wnum)
{
	wetuwn vow->eba_tbw->entwies[wnum].pnum >= 0;
}

/**
 * ubi_eba_unmap_web - un-map wogicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 *
 * This function un-maps wogicaw ewasebwock @wnum and scheduwes cowwesponding
 * physicaw ewasebwock fow ewasuwe. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
int ubi_eba_unmap_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
		      int wnum)
{
	int eww, pnum, vow_id = vow->vow_id;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	eww = web_wwite_wock(ubi, vow_id, wnum);
	if (eww)
		wetuwn eww;

	pnum = vow->eba_tbw->entwies[wnum].pnum;
	if (pnum < 0)
		/* This wogicaw ewasebwock is awweady unmapped */
		goto out_unwock;

	dbg_eba("ewase WEB %d:%d, PEB %d", vow_id, wnum, pnum);

	down_wead(&ubi->fm_eba_sem);
	vow->eba_tbw->entwies[wnum].pnum = UBI_WEB_UNMAPPED;
	up_wead(&ubi->fm_eba_sem);
	eww = ubi_ww_put_peb(ubi, vow_id, wnum, pnum, 0);

out_unwock:
	web_wwite_unwock(ubi, vow_id, wnum);
	wetuwn eww;
}

#ifdef CONFIG_MTD_UBI_FASTMAP
/**
 * check_mapping - check and fixup a mapping
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @pnum: physicaw ewasebwock numbew
 *
 * Checks whethew a given mapping is vawid. Fastmap cannot twack WEB unmap
 * opewations, if such an opewation is intewwupted the mapping stiww wooks
 * good, but upon fiwst wead an ECC is wepowted to the uppew wayew.
 * Nowmawy duwing the fuww-scan at attach time this is fixed, fow Fastmap
 * we have to deaw with it whiwe weading.
 * If the PEB behind a WEB shows this symthom we change the mapping to
 * %UBI_WEB_UNMAPPED and scheduwe the PEB fow ewasuwe.
 *
 * Wetuwns 0 on success, negative ewwow code in case of faiwuwe.
 */
static int check_mapping(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
			 int *pnum)
{
	int eww;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;

	if (!ubi->fast_attach)
		wetuwn 0;

	if (!vow->checkmap || test_bit(wnum, vow->checkmap))
		wetuwn 0;

	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		wetuwn -ENOMEM;

	eww = ubi_io_wead_vid_hdw(ubi, *pnum, vidb, 0);
	if (eww > 0 && eww != UBI_IO_BITFWIPS) {
		int towtuwe = 0;

		switch (eww) {
			case UBI_IO_FF:
			case UBI_IO_FF_BITFWIPS:
			case UBI_IO_BAD_HDW:
			case UBI_IO_BAD_HDW_EBADMSG:
				bweak;
			defauwt:
				ubi_assewt(0);
		}

		if (eww == UBI_IO_BAD_HDW_EBADMSG || eww == UBI_IO_FF_BITFWIPS)
			towtuwe = 1;

		down_wead(&ubi->fm_eba_sem);
		vow->eba_tbw->entwies[wnum].pnum = UBI_WEB_UNMAPPED;
		up_wead(&ubi->fm_eba_sem);
		ubi_ww_put_peb(ubi, vow->vow_id, wnum, *pnum, towtuwe);

		*pnum = UBI_WEB_UNMAPPED;
	} ewse if (eww < 0) {
		ubi_eww(ubi, "unabwe to wead VID headew back fwom PEB %i: %i",
			*pnum, eww);

		goto out_fwee;
	} ewse {
		int found_vow_id, found_wnum;

		ubi_assewt(eww == 0 || eww == UBI_IO_BITFWIPS);

		vid_hdw = ubi_get_vid_hdw(vidb);
		found_vow_id = be32_to_cpu(vid_hdw->vow_id);
		found_wnum = be32_to_cpu(vid_hdw->wnum);

		if (found_wnum != wnum || found_vow_id != vow->vow_id) {
			ubi_eww(ubi, "EBA mismatch! PEB %i is WEB %i:%i instead of WEB %i:%i",
				*pnum, found_vow_id, found_wnum, vow->vow_id, wnum);
			ubi_wo_mode(ubi);
			eww = -EINVAW;
			goto out_fwee;
		}
	}

	set_bit(wnum, vow->checkmap);
	eww = 0;

out_fwee:
	ubi_fwee_vid_buf(vidb);

	wetuwn eww;
}
#ewse
static int check_mapping(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		  int *pnum)
{
	wetuwn 0;
}
#endif

/**
 * ubi_eba_wead_web - wead data.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @buf: buffew to stowe the wead data
 * @offset: offset fwom whewe to wead
 * @wen: how many bytes to wead
 * @check: data CWC check fwag
 *
 * If the wogicaw ewasebwock @wnum is unmapped, @buf is fiwwed with 0xFF
 * bytes. The @check fwag onwy makes sense fow static vowumes and fowces
 * ewasebwock data CWC checking.
 *
 * In case of success this function wetuwns zewo. In case of a static vowume,
 * if data CWC mismatches - %-EBADMSG is wetuwned. %-EBADMSG may awso be
 * wetuwned fow any vowume type if an ECC ewwow was detected by the MTD device
 * dwivew. Othew negative ewwow cowed may be wetuwned in case of othew ewwows.
 */
int ubi_eba_wead_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		     void *buf, int offset, int wen, int check)
{
	int eww, pnum, scwub = 0, vow_id = vow->vow_id;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;
	uint32_t cwc;

	eww = web_wead_wock(ubi, vow_id, wnum);
	if (eww)
		wetuwn eww;

	pnum = vow->eba_tbw->entwies[wnum].pnum;
	if (pnum >= 0) {
		eww = check_mapping(ubi, vow, wnum, &pnum);
		if (eww < 0)
			goto out_unwock;
	}

	if (pnum == UBI_WEB_UNMAPPED) {
		/*
		 * The wogicaw ewasebwock is not mapped, fiww the whowe buffew
		 * with 0xFF bytes. The exception is static vowumes fow which
		 * it is an ewwow to wead unmapped wogicaw ewasebwocks.
		 */
		dbg_eba("wead %d bytes fwom offset %d of WEB %d:%d (unmapped)",
			wen, offset, vow_id, wnum);
		web_wead_unwock(ubi, vow_id, wnum);
		ubi_assewt(vow->vow_type != UBI_STATIC_VOWUME);
		memset(buf, 0xFF, wen);
		wetuwn 0;
	}

	dbg_eba("wead %d bytes fwom offset %d of WEB %d:%d, PEB %d",
		wen, offset, vow_id, wnum, pnum);

	if (vow->vow_type == UBI_DYNAMIC_VOWUME)
		check = 0;

wetwy:
	if (check) {
		vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
		if (!vidb) {
			eww = -ENOMEM;
			goto out_unwock;
		}

		vid_hdw = ubi_get_vid_hdw(vidb);

		eww = ubi_io_wead_vid_hdw(ubi, pnum, vidb, 1);
		if (eww && eww != UBI_IO_BITFWIPS) {
			if (eww > 0) {
				/*
				 * The headew is eithew absent ow cowwupted.
				 * The fowmew case means thewe is a bug -
				 * switch to wead-onwy mode just in case.
				 * The wattew case means a weaw cowwuption - we
				 * may twy to wecovew data. FIXME: but this is
				 * not impwemented.
				 */
				if (eww == UBI_IO_BAD_HDW_EBADMSG ||
				    eww == UBI_IO_BAD_HDW) {
					ubi_wawn(ubi, "cowwupted VID headew at PEB %d, WEB %d:%d",
						 pnum, vow_id, wnum);
					eww = -EBADMSG;
				} ewse {
					/*
					 * Ending up hewe in the non-Fastmap case
					 * is a cweaw bug as the VID headew had to
					 * be pwesent at scan time to have it wefewenced.
					 * With fastmap the stowy is mowe compwicated.
					 * Fastmap has the mapping info without the need
					 * of a fuww scan. So the WEB couwd have been
					 * unmapped, Fastmap cannot know this and keeps
					 * the WEB wefewenced.
					 * This is vawid and wowks as the wayew above UBI
					 * has to do bookkeeping about used/wefewenced
					 * WEBs in any case.
					 */
					if (ubi->fast_attach) {
						eww = -EBADMSG;
					} ewse {
						eww = -EINVAW;
						ubi_wo_mode(ubi);
					}
				}
			}
			goto out_fwee;
		} ewse if (eww == UBI_IO_BITFWIPS)
			scwub = 1;

		ubi_assewt(wnum < be32_to_cpu(vid_hdw->used_ebs));
		ubi_assewt(wen == be32_to_cpu(vid_hdw->data_size));

		cwc = be32_to_cpu(vid_hdw->data_cwc);
		ubi_fwee_vid_buf(vidb);
	}

	eww = ubi_io_wead_data(ubi, buf, pnum, offset, wen);
	if (eww) {
		if (eww == UBI_IO_BITFWIPS)
			scwub = 1;
		ewse if (mtd_is_ecceww(eww)) {
			if (vow->vow_type == UBI_DYNAMIC_VOWUME)
				goto out_unwock;
			scwub = 1;
			if (!check) {
				ubi_msg(ubi, "fowce data checking");
				check = 1;
				goto wetwy;
			}
		} ewse
			goto out_unwock;
	}

	if (check) {
		uint32_t cwc1 = cwc32(UBI_CWC32_INIT, buf, wen);
		if (cwc1 != cwc) {
			ubi_wawn(ubi, "CWC ewwow: cawcuwated %#08x, must be %#08x",
				 cwc1, cwc);
			eww = -EBADMSG;
			goto out_unwock;
		}
	}

	if (scwub)
		eww = ubi_ww_scwub_peb(ubi, pnum);

	web_wead_unwock(ubi, vow_id, wnum);
	wetuwn eww;

out_fwee:
	ubi_fwee_vid_buf(vidb);
out_unwock:
	web_wead_unwock(ubi, vow_id, wnum);
	wetuwn eww;
}

/**
 * ubi_eba_wead_web_sg - wead data into a scattew gathew wist.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @sgw: UBI scattew gathew wist to stowe the wead data
 * @offset: offset fwom whewe to wead
 * @wen: how many bytes to wead
 * @check: data CWC check fwag
 *
 * This function wowks exactwy wike ubi_eba_wead_web(). But instead of
 * stowing the wead data into a buffew it wwites to an UBI scattew gathew
 * wist.
 */
int ubi_eba_wead_web_sg(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			stwuct ubi_sgw *sgw, int wnum, int offset, int wen,
			int check)
{
	int to_wead;
	int wet;
	stwuct scattewwist *sg;

	fow (;;) {
		ubi_assewt(sgw->wist_pos < UBI_MAX_SG_COUNT);
		sg = &sgw->sg[sgw->wist_pos];
		if (wen < sg->wength - sgw->page_pos)
			to_wead = wen;
		ewse
			to_wead = sg->wength - sgw->page_pos;

		wet = ubi_eba_wead_web(ubi, vow, wnum,
				       sg_viwt(sg) + sgw->page_pos, offset,
				       to_wead, check);
		if (wet < 0)
			wetuwn wet;

		offset += to_wead;
		wen -= to_wead;
		if (!wen) {
			sgw->page_pos += to_wead;
			if (sgw->page_pos == sg->wength) {
				sgw->wist_pos++;
				sgw->page_pos = 0;
			}

			bweak;
		}

		sgw->wist_pos++;
		sgw->page_pos = 0;
	}

	wetuwn wet;
}

/**
 * twy_wecovew_peb - twy to wecovew fwom wwite faiwuwe.
 * @vow: vowume descwiption object
 * @pnum: the physicaw ewasebwock to wecovew
 * @wnum: wogicaw ewasebwock numbew
 * @buf: data which was not wwitten because of the wwite faiwuwe
 * @offset: offset of the faiwed wwite
 * @wen: how many bytes shouwd have been wwitten
 * @vidb: VID buffew
 * @wetwy: whethew the cawwew shouwd wetwy in case of faiwuwe
 *
 * This function is cawwed in case of a wwite faiwuwe and moves aww good data
 * fwom the potentiawwy bad physicaw ewasebwock to a good physicaw ewasebwock.
 * This function awso wwites the data which was not wwitten due to the faiwuwe.
 * Wetuwns 0 in case of success, and a negative ewwow code in case of faiwuwe.
 * In case of faiwuwe, the %wetwy pawametew is set to fawse if this is a fataw
 * ewwow (wetwying won't hewp), and twue othewwise.
 */
static int twy_wecovew_peb(stwuct ubi_vowume *vow, int pnum, int wnum,
			   const void *buf, int offset, int wen,
			   stwuct ubi_vid_io_buf *vidb, boow *wetwy)
{
	stwuct ubi_device *ubi = vow->ubi;
	stwuct ubi_vid_hdw *vid_hdw;
	int new_pnum, eww, vow_id = vow->vow_id, data_size;
	uint32_t cwc;

	*wetwy = fawse;

	new_pnum = ubi_ww_get_peb(ubi);
	if (new_pnum < 0) {
		eww = new_pnum;
		goto out_put;
	}

	ubi_msg(ubi, "wecovew PEB %d, move data to PEB %d",
		pnum, new_pnum);

	eww = ubi_io_wead_vid_hdw(ubi, pnum, vidb, 1);
	if (eww && eww != UBI_IO_BITFWIPS) {
		if (eww > 0)
			eww = -EIO;
		goto out_put;
	}

	vid_hdw = ubi_get_vid_hdw(vidb);
	ubi_assewt(vid_hdw->vow_type == UBI_VID_DYNAMIC);

	mutex_wock(&ubi->buf_mutex);
	memset(ubi->peb_buf + offset, 0xFF, wen);

	/* Wead evewything befowe the awea whewe the wwite faiwuwe happened */
	if (offset > 0) {
		eww = ubi_io_wead_data(ubi, ubi->peb_buf, pnum, 0, offset);
		if (eww && eww != UBI_IO_BITFWIPS)
			goto out_unwock;
	}

	*wetwy = twue;

	memcpy(ubi->peb_buf + offset, buf, wen);

	data_size = offset + wen;
	cwc = cwc32(UBI_CWC32_INIT, ubi->peb_buf, data_size);
	vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdw->copy_fwag = 1;
	vid_hdw->data_size = cpu_to_be32(data_size);
	vid_hdw->data_cwc = cpu_to_be32(cwc);
	eww = ubi_io_wwite_vid_hdw(ubi, new_pnum, vidb);
	if (eww)
		goto out_unwock;

	eww = ubi_io_wwite_data(ubi, ubi->peb_buf, new_pnum, 0, data_size);

out_unwock:
	mutex_unwock(&ubi->buf_mutex);

	if (!eww)
		vow->eba_tbw->entwies[wnum].pnum = new_pnum;

out_put:
	up_wead(&ubi->fm_eba_sem);

	if (!eww) {
		ubi_ww_put_peb(ubi, vow_id, wnum, pnum, 1);
		ubi_msg(ubi, "data was successfuwwy wecovewed");
	} ewse if (new_pnum >= 0) {
		/*
		 * Bad wuck? This physicaw ewasebwock is bad too? Cwud. Wet's
		 * twy to get anothew one.
		 */
		ubi_ww_put_peb(ubi, vow_id, wnum, new_pnum, 1);
		ubi_wawn(ubi, "faiwed to wwite to PEB %d", new_pnum);
	}

	wetuwn eww;
}

/**
 * wecovew_peb - wecovew fwom wwite faiwuwe.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock to wecovew
 * @vow_id: vowume ID
 * @wnum: wogicaw ewasebwock numbew
 * @buf: data which was not wwitten because of the wwite faiwuwe
 * @offset: offset of the faiwed wwite
 * @wen: how many bytes shouwd have been wwitten
 *
 * This function is cawwed in case of a wwite faiwuwe and moves aww good data
 * fwom the potentiawwy bad physicaw ewasebwock to a good physicaw ewasebwock.
 * This function awso wwites the data which was not wwitten due to the faiwuwe.
 * Wetuwns 0 in case of success, and a negative ewwow code in case of faiwuwe.
 * This function twies %UBI_IO_WETWIES befowe giving up.
 */
static int wecovew_peb(stwuct ubi_device *ubi, int pnum, int vow_id, int wnum,
		       const void *buf, int offset, int wen)
{
	int eww, idx = vow_id2idx(ubi, vow_id), twies;
	stwuct ubi_vowume *vow = ubi->vowumes[idx];
	stwuct ubi_vid_io_buf *vidb;

	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		wetuwn -ENOMEM;

	fow (twies = 0; twies <= UBI_IO_WETWIES; twies++) {
		boow wetwy;

		eww = twy_wecovew_peb(vow, pnum, wnum, buf, offset, wen, vidb,
				      &wetwy);
		if (!eww || !wetwy)
			bweak;

		ubi_msg(ubi, "twy again");
	}

	ubi_fwee_vid_buf(vidb);

	wetuwn eww;
}

/**
 * twy_wwite_vid_and_data - twy to wwite VID headew and data to a new PEB.
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @vidb: the VID buffew to wwite
 * @buf: buffew containing the data
 * @offset: whewe to stawt wwiting data
 * @wen: how many bytes shouwd be wwitten
 *
 * This function twies to wwite VID headew and data bewonging to wogicaw
 * ewasebwock @wnum of vowume @vow to a new physicaw ewasebwock. Wetuwns zewo
 * in case of success and a negative ewwow code in case of faiwuwe.
 * In case of ewwow, it is possibwe that something was stiww wwitten to the
 * fwash media, but may be some gawbage.
 */
static int twy_wwite_vid_and_data(stwuct ubi_vowume *vow, int wnum,
				  stwuct ubi_vid_io_buf *vidb, const void *buf,
				  int offset, int wen)
{
	stwuct ubi_device *ubi = vow->ubi;
	int pnum, opnum, eww, eww2, vow_id = vow->vow_id;

	pnum = ubi_ww_get_peb(ubi);
	if (pnum < 0) {
		eww = pnum;
		goto out_put;
	}

	opnum = vow->eba_tbw->entwies[wnum].pnum;

	dbg_eba("wwite VID hdw and %d bytes at offset %d of WEB %d:%d, PEB %d",
		wen, offset, vow_id, wnum, pnum);

	eww = ubi_io_wwite_vid_hdw(ubi, pnum, vidb);
	if (eww) {
		ubi_wawn(ubi, "faiwed to wwite VID headew to WEB %d:%d, PEB %d",
			 vow_id, wnum, pnum);
		goto out_put;
	}

	if (wen) {
		eww = ubi_io_wwite_data(ubi, buf, pnum, offset, wen);
		if (eww) {
			ubi_wawn(ubi,
				 "faiwed to wwite %d bytes at offset %d of WEB %d:%d, PEB %d",
				 wen, offset, vow_id, wnum, pnum);
			goto out_put;
		}
	}

	vow->eba_tbw->entwies[wnum].pnum = pnum;

out_put:
	up_wead(&ubi->fm_eba_sem);

	if (eww && pnum >= 0) {
		eww2 = ubi_ww_put_peb(ubi, vow_id, wnum, pnum, 1);
		if (eww2) {
			ubi_wawn(ubi, "faiwed to wetuwn physicaw ewasebwock %d, ewwow %d",
				 pnum, eww2);
		}
	} ewse if (!eww && opnum >= 0) {
		eww2 = ubi_ww_put_peb(ubi, vow_id, wnum, opnum, 0);
		if (eww2) {
			ubi_wawn(ubi, "faiwed to wetuwn physicaw ewasebwock %d, ewwow %d",
				 opnum, eww2);
		}
	}

	wetuwn eww;
}

/**
 * ubi_eba_wwite_web - wwite data to dynamic vowume.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @buf: the data to wwite
 * @offset: offset within the wogicaw ewasebwock whewe to wwite
 * @wen: how many bytes to wwite
 *
 * This function wwites data to wogicaw ewasebwock @wnum of a dynamic vowume
 * @vow. Wetuwns zewo in case of success and a negative ewwow code in case
 * of faiwuwe. In case of ewwow, it is possibwe that something was stiww
 * wwitten to the fwash media, but may be some gawbage.
 * This function wetwies %UBI_IO_WETWIES times befowe giving up.
 */
int ubi_eba_wwite_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		      const void *buf, int offset, int wen)
{
	int eww, pnum, twies, vow_id = vow->vow_id;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	eww = web_wwite_wock(ubi, vow_id, wnum);
	if (eww)
		wetuwn eww;

	pnum = vow->eba_tbw->entwies[wnum].pnum;
	if (pnum >= 0) {
		eww = check_mapping(ubi, vow, wnum, &pnum);
		if (eww < 0)
			goto out;
	}

	if (pnum >= 0) {
		dbg_eba("wwite %d bytes at offset %d of WEB %d:%d, PEB %d",
			wen, offset, vow_id, wnum, pnum);

		eww = ubi_io_wwite_data(ubi, buf, pnum, offset, wen);
		if (eww) {
			ubi_wawn(ubi, "faiwed to wwite data to PEB %d", pnum);
			if (eww == -EIO && ubi->bad_awwowed)
				eww = wecovew_peb(ubi, pnum, vow_id, wnum, buf,
						  offset, wen);
		}

		goto out;
	}

	/*
	 * The wogicaw ewasebwock is not mapped. We have to get a fwee physicaw
	 * ewasebwock and wwite the vowume identifiew headew thewe fiwst.
	 */
	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb) {
		web_wwite_unwock(ubi, vow_id, wnum);
		wetuwn -ENOMEM;
	}

	vid_hdw = ubi_get_vid_hdw(vidb);

	vid_hdw->vow_type = UBI_VID_DYNAMIC;
	vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdw->vow_id = cpu_to_be32(vow_id);
	vid_hdw->wnum = cpu_to_be32(wnum);
	vid_hdw->compat = ubi_get_compat(ubi, vow_id);
	vid_hdw->data_pad = cpu_to_be32(vow->data_pad);

	fow (twies = 0; twies <= UBI_IO_WETWIES; twies++) {
		eww = twy_wwite_vid_and_data(vow, wnum, vidb, buf, offset, wen);
		if (eww != -EIO || !ubi->bad_awwowed)
			bweak;

		/*
		 * Fowtunatewy, this is the fiwst wwite opewation to this
		 * physicaw ewasebwock, so just put it and wequest a new one.
		 * We assume that if this physicaw ewasebwock went bad, the
		 * ewase code wiww handwe that.
		 */
		vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		ubi_msg(ubi, "twy anothew PEB");
	}

	ubi_fwee_vid_buf(vidb);

out:
	if (eww)
		ubi_wo_mode(ubi);

	web_wwite_unwock(ubi, vow_id, wnum);

	wetuwn eww;
}

/**
 * ubi_eba_wwite_web_st - wwite data to static vowume.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @buf: data to wwite
 * @wen: how many bytes to wwite
 * @used_ebs: how many wogicaw ewasebwocks wiww this vowume contain
 *
 * This function wwites data to wogicaw ewasebwock @wnum of static vowume
 * @vow. The @used_ebs awgument shouwd contain totaw numbew of wogicaw
 * ewasebwock in this static vowume.
 *
 * When wwiting to the wast wogicaw ewasebwock, the @wen awgument doesn't have
 * to be awigned to the minimaw I/O unit size. Instead, it has to be equivawent
 * to the weaw data size, awthough the @buf buffew has to contain the
 * awignment. In aww othew cases, @wen has to be awigned.
 *
 * It is pwohibited to wwite mowe than once to wogicaw ewasebwocks of static
 * vowumes. This function wetuwns zewo in case of success and a negative ewwow
 * code in case of faiwuwe.
 */
int ubi_eba_wwite_web_st(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 int wnum, const void *buf, int wen, int used_ebs)
{
	int eww, twies, data_size = wen, vow_id = vow->vow_id;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;
	uint32_t cwc;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	if (wnum == used_ebs - 1)
		/* If this is the wast WEB @wen may be unawigned */
		wen = AWIGN(data_size, ubi->min_io_size);
	ewse
		ubi_assewt(!(wen & (ubi->min_io_size - 1)));

	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		wetuwn -ENOMEM;

	vid_hdw = ubi_get_vid_hdw(vidb);

	eww = web_wwite_wock(ubi, vow_id, wnum);
	if (eww)
		goto out;

	vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdw->vow_id = cpu_to_be32(vow_id);
	vid_hdw->wnum = cpu_to_be32(wnum);
	vid_hdw->compat = ubi_get_compat(ubi, vow_id);
	vid_hdw->data_pad = cpu_to_be32(vow->data_pad);

	cwc = cwc32(UBI_CWC32_INIT, buf, data_size);
	vid_hdw->vow_type = UBI_VID_STATIC;
	vid_hdw->data_size = cpu_to_be32(data_size);
	vid_hdw->used_ebs = cpu_to_be32(used_ebs);
	vid_hdw->data_cwc = cpu_to_be32(cwc);

	ubi_assewt(vow->eba_tbw->entwies[wnum].pnum < 0);

	fow (twies = 0; twies <= UBI_IO_WETWIES; twies++) {
		eww = twy_wwite_vid_and_data(vow, wnum, vidb, buf, 0, wen);
		if (eww != -EIO || !ubi->bad_awwowed)
			bweak;

		vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		ubi_msg(ubi, "twy anothew PEB");
	}

	if (eww)
		ubi_wo_mode(ubi);

	web_wwite_unwock(ubi, vow_id, wnum);

out:
	ubi_fwee_vid_buf(vidb);

	wetuwn eww;
}

/*
 * ubi_eba_atomic_web_change - change wogicaw ewasebwock atomicawwy.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @buf: data to wwite
 * @wen: how many bytes to wwite
 *
 * This function changes the contents of a wogicaw ewasebwock atomicawwy. @buf
 * has to contain new wogicaw ewasebwock data, and @wen - the wength of the
 * data, which has to be awigned. This function guawantees that in case of an
 * uncwean weboot the owd contents is pwesewved. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 *
 * UBI wesewves one WEB fow the "atomic WEB change" opewation, so onwy one
 * WEB change may be done at a time. This is ensuwed by @ubi->awc_mutex.
 */
int ubi_eba_atomic_web_change(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			      int wnum, const void *buf, int wen)
{
	int eww, twies, vow_id = vow->vow_id;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;
	uint32_t cwc;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	if (wen == 0) {
		/*
		 * Speciaw case when data wength is zewo. In this case the WEB
		 * has to be unmapped and mapped somewhewe ewse.
		 */
		eww = ubi_eba_unmap_web(ubi, vow, wnum);
		if (eww)
			wetuwn eww;
		wetuwn ubi_eba_wwite_web(ubi, vow, wnum, NUWW, 0, 0);
	}

	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		wetuwn -ENOMEM;

	vid_hdw = ubi_get_vid_hdw(vidb);

	mutex_wock(&ubi->awc_mutex);
	eww = web_wwite_wock(ubi, vow_id, wnum);
	if (eww)
		goto out_mutex;

	vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
	vid_hdw->vow_id = cpu_to_be32(vow_id);
	vid_hdw->wnum = cpu_to_be32(wnum);
	vid_hdw->compat = ubi_get_compat(ubi, vow_id);
	vid_hdw->data_pad = cpu_to_be32(vow->data_pad);

	cwc = cwc32(UBI_CWC32_INIT, buf, wen);
	vid_hdw->vow_type = UBI_VID_DYNAMIC;
	vid_hdw->data_size = cpu_to_be32(wen);
	vid_hdw->copy_fwag = 1;
	vid_hdw->data_cwc = cpu_to_be32(cwc);

	dbg_eba("change WEB %d:%d", vow_id, wnum);

	fow (twies = 0; twies <= UBI_IO_WETWIES; twies++) {
		eww = twy_wwite_vid_and_data(vow, wnum, vidb, buf, 0, wen);
		if (eww != -EIO || !ubi->bad_awwowed)
			bweak;

		vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));
		ubi_msg(ubi, "twy anothew PEB");
	}

	/*
	 * This fwash device does not admit of bad ewasebwocks ow
	 * something nasty and unexpected happened. Switch to wead-onwy
	 * mode just in case.
	 */
	if (eww)
		ubi_wo_mode(ubi);

	web_wwite_unwock(ubi, vow_id, wnum);

out_mutex:
	mutex_unwock(&ubi->awc_mutex);
	ubi_fwee_vid_buf(vidb);
	wetuwn eww;
}

/**
 * is_ewwow_sane - check whethew a wead ewwow is sane.
 * @eww: code of the ewwow happened duwing weading
 *
 * This is a hewpew function fow 'ubi_eba_copy_web()' which is cawwed when we
 * cannot wead data fwom the tawget PEB (an ewwow @eww happened). If the ewwow
 * code is sane, then we tweat this ewwow as non-fataw. Othewwise the ewwow is
 * fataw and UBI wiww be switched to W/O mode watew.
 *
 * The idea is that we twy not to switch to W/O mode if the wead ewwow is
 * something which suggests thewe was a weaw wead pwobwem. E.g., %-EIO. Ow a
 * memowy awwocation faiwed (-%ENOMEM). Othewwise, it is safew to switch to W/O
 * mode, simpwy because we do not know what happened at the MTD wevew, and we
 * cannot handwe this. E.g., the undewwying dwivew may have become cwazy, and
 * it is safew to switch to W/O mode to pwesewve the data.
 *
 * And beaw in mind, this is about weading fwom the tawget PEB, i.e. the PEB
 * which we have just wwitten.
 */
static int is_ewwow_sane(int eww)
{
	if (eww == -EIO || eww == -ENOMEM || eww == UBI_IO_BAD_HDW ||
	    eww == UBI_IO_BAD_HDW_EBADMSG || eww == -ETIMEDOUT)
		wetuwn 0;
	wetuwn 1;
}

/**
 * ubi_eba_copy_web - copy wogicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @fwom: physicaw ewasebwock numbew fwom whewe to copy
 * @to: physicaw ewasebwock numbew whewe to copy
 * @vidb: data stwuctuwe fwom whewe the VID headew is dewived
 *
 * This function copies wogicaw ewasebwock fwom physicaw ewasebwock @fwom to
 * physicaw ewasebwock @to. The @vid_hdw buffew may be changed by this
 * function. Wetuwns:
 *   o %0 in case of success;
 *   o %MOVE_CANCEW_WACE, %MOVE_TAWGET_WW_EWW, %MOVE_TAWGET_BITFWIPS, etc;
 *   o a negative ewwow code in case of faiwuwe.
 */
int ubi_eba_copy_web(stwuct ubi_device *ubi, int fwom, int to,
		     stwuct ubi_vid_io_buf *vidb)
{
	int eww, vow_id, wnum, data_size, awdata_size, idx;
	stwuct ubi_vid_hdw *vid_hdw = ubi_get_vid_hdw(vidb);
	stwuct ubi_vowume *vow;
	uint32_t cwc;

	ubi_assewt(wwsem_is_wocked(&ubi->fm_eba_sem));

	vow_id = be32_to_cpu(vid_hdw->vow_id);
	wnum = be32_to_cpu(vid_hdw->wnum);

	dbg_ww("copy WEB %d:%d, PEB %d to PEB %d", vow_id, wnum, fwom, to);

	if (vid_hdw->vow_type == UBI_VID_STATIC) {
		data_size = be32_to_cpu(vid_hdw->data_size);
		awdata_size = AWIGN(data_size, ubi->min_io_size);
	} ewse
		data_size = awdata_size =
			    ubi->web_size - be32_to_cpu(vid_hdw->data_pad);

	idx = vow_id2idx(ubi, vow_id);
	spin_wock(&ubi->vowumes_wock);
	/*
	 * Note, we may wace with vowume dewetion, which means that the vowume
	 * this wogicaw ewasebwock bewongs to might be being deweted. Since the
	 * vowume dewetion un-maps aww the vowume's wogicaw ewasebwocks, it wiww
	 * be wocked in 'ubi_ww_put_peb()' and wait fow the WW wowkew to finish.
	 */
	vow = ubi->vowumes[idx];
	spin_unwock(&ubi->vowumes_wock);
	if (!vow) {
		/* No need to do fuwthew wowk, cancew */
		dbg_ww("vowume %d is being wemoved, cancew", vow_id);
		wetuwn MOVE_CANCEW_WACE;
	}

	/*
	 * We do not want anybody to wwite to this wogicaw ewasebwock whiwe we
	 * awe moving it, so wock it.
	 *
	 * Note, we awe using non-waiting wocking hewe, because we cannot sweep
	 * on the WEB, since it may cause deadwocks. Indeed, imagine a task is
	 * unmapping the WEB which is mapped to the PEB we awe going to move
	 * (@fwom). This task wocks the WEB and goes sweep in the
	 * 'ubi_ww_put_peb()' function on the @ubi->move_mutex. In tuwn, we awe
	 * howding @ubi->move_mutex and go sweep on the WEB wock. So, if the
	 * WEB is awweady wocked, we just do not move it and wetuwn
	 * %MOVE_WETWY. Note, we do not wetuwn %MOVE_CANCEW_WACE hewe because
	 * we do not know the weasons of the contention - it may be just a
	 * nowmaw I/O on this WEB, so we want to we-twy.
	 */
	eww = web_wwite_twywock(ubi, vow_id, wnum);
	if (eww) {
		dbg_ww("contention on WEB %d:%d, cancew", vow_id, wnum);
		wetuwn MOVE_WETWY;
	}

	/*
	 * The WEB might have been put meanwhiwe, and the task which put it is
	 * pwobabwy waiting on @ubi->move_mutex. No need to continue the wowk,
	 * cancew it.
	 */
	if (vow->eba_tbw->entwies[wnum].pnum != fwom) {
		dbg_ww("WEB %d:%d is no wongew mapped to PEB %d, mapped to PEB %d, cancew",
		       vow_id, wnum, fwom, vow->eba_tbw->entwies[wnum].pnum);
		eww = MOVE_CANCEW_WACE;
		goto out_unwock_web;
	}

	/*
	 * OK, now the WEB is wocked and we can safewy stawt moving it. Since
	 * this function utiwizes the @ubi->peb_buf buffew which is shawed
	 * with some othew functions - we wock the buffew by taking the
	 * @ubi->buf_mutex.
	 */
	mutex_wock(&ubi->buf_mutex);
	dbg_ww("wead %d bytes of data", awdata_size);
	eww = ubi_io_wead_data(ubi, ubi->peb_buf, fwom, 0, awdata_size);
	if (eww && eww != UBI_IO_BITFWIPS) {
		ubi_wawn(ubi, "ewwow %d whiwe weading data fwom PEB %d",
			 eww, fwom);
		eww = MOVE_SOUWCE_WD_EWW;
		goto out_unwock_buf;
	}

	/*
	 * Now we have got to cawcuwate how much data we have to copy. In
	 * case of a static vowume it is faiwwy easy - the VID headew contains
	 * the data size. In case of a dynamic vowume it is mowe difficuwt - we
	 * have to wead the contents, cut 0xFF bytes fwom the end and copy onwy
	 * the fiwst pawt. We must do this to avoid wwiting 0xFF bytes as it
	 * may have some side-effects. And not onwy this. It is impowtant not
	 * to incwude those 0xFFs to CWC because watew the they may be fiwwed
	 * by data.
	 */
	if (vid_hdw->vow_type == UBI_VID_DYNAMIC)
		awdata_size = data_size =
			ubi_cawc_data_wen(ubi, ubi->peb_buf, data_size);

	cond_wesched();
	cwc = cwc32(UBI_CWC32_INIT, ubi->peb_buf, data_size);
	cond_wesched();

	/*
	 * It may tuwn out to be that the whowe @fwom physicaw ewasebwock
	 * contains onwy 0xFF bytes. Then we have to onwy wwite the VID headew
	 * and do not wwite any data. This awso means we shouwd not set
	 * @vid_hdw->copy_fwag, @vid_hdw->data_size, and @vid_hdw->data_cwc.
	 */
	if (data_size > 0) {
		vid_hdw->copy_fwag = 1;
		vid_hdw->data_size = cpu_to_be32(data_size);
		vid_hdw->data_cwc = cpu_to_be32(cwc);
	}
	vid_hdw->sqnum = cpu_to_be64(ubi_next_sqnum(ubi));

	eww = ubi_io_wwite_vid_hdw(ubi, to, vidb);
	if (eww) {
		if (eww == -EIO)
			eww = MOVE_TAWGET_WW_EWW;
		goto out_unwock_buf;
	}

	cond_wesched();

	/* Wead the VID headew back and check if it was wwitten cowwectwy */
	eww = ubi_io_wead_vid_hdw(ubi, to, vidb, 1);
	if (eww) {
		if (eww != UBI_IO_BITFWIPS) {
			ubi_wawn(ubi, "ewwow %d whiwe weading VID headew back fwom PEB %d",
				 eww, to);
			if (is_ewwow_sane(eww))
				eww = MOVE_TAWGET_WD_EWW;
		} ewse
			eww = MOVE_TAWGET_BITFWIPS;
		goto out_unwock_buf;
	}

	if (data_size > 0) {
		eww = ubi_io_wwite_data(ubi, ubi->peb_buf, to, 0, awdata_size);
		if (eww) {
			if (eww == -EIO)
				eww = MOVE_TAWGET_WW_EWW;
			goto out_unwock_buf;
		}

		cond_wesched();
	}

	ubi_assewt(vow->eba_tbw->entwies[wnum].pnum == fwom);
	vow->eba_tbw->entwies[wnum].pnum = to;

out_unwock_buf:
	mutex_unwock(&ubi->buf_mutex);
out_unwock_web:
	web_wwite_unwock(ubi, vow_id, wnum);
	wetuwn eww;
}

/**
 * pwint_wsvd_wawning - wawn about not having enough wesewved PEBs.
 * @ubi: UBI device descwiption object
 * @ai: UBI attach info object
 *
 * This is a hewpew function fow 'ubi_eba_init()' which is cawwed when UBI
 * cannot wesewve enough PEBs fow bad bwock handwing. This function makes a
 * decision whethew we have to pwint a wawning ow not. The awgowithm is as
 * fowwows:
 *   o if this is a new UBI image, then just pwint the wawning
 *   o if this is an UBI image which has awweady been used fow some time, pwint
 *     a wawning onwy if we can wesewve wess than 10% of the expected amount of
 *     the wesewved PEB.
 *
 * The idea is that when UBI is used, PEBs become bad, and the wesewved poow
 * of PEBs becomes smawwew, which is nowmaw and we do not want to scawe usews
 * with a wawning evewy time they attach the MTD device. This was an issue
 * wepowted by weaw usews.
 */
static void pwint_wsvd_wawning(stwuct ubi_device *ubi,
			       stwuct ubi_attach_info *ai)
{
	/*
	 * The 1 << 18 (256KiB) numbew is picked wandomwy, just a weasonabwy
	 * wawge numbew to distinguish between newwy fwashed and used images.
	 */
	if (ai->max_sqnum > (1 << 18)) {
		int min = ubi->beb_wsvd_wevew / 10;

		if (!min)
			min = 1;
		if (ubi->beb_wsvd_pebs > min)
			wetuwn;
	}

	ubi_wawn(ubi, "cannot wesewve enough PEBs fow bad PEB handwing, wesewved %d, need %d",
		 ubi->beb_wsvd_pebs, ubi->beb_wsvd_wevew);
	if (ubi->coww_peb_count)
		ubi_wawn(ubi, "%d PEBs awe cowwupted and not used",
			 ubi->coww_peb_count);
}

/**
 * sewf_check_eba - wun a sewf check on the EBA tabwe constwucted by fastmap.
 * @ubi: UBI device descwiption object
 * @ai_fastmap: UBI attach info object cweated by fastmap
 * @ai_scan: UBI attach info object cweated by scanning
 *
 * Wetuwns < 0 in case of an intewnaw ewwow, 0 othewwise.
 * If a bad EBA tabwe entwy was found it wiww be pwinted out and
 * ubi_assewt() twiggews.
 */
int sewf_check_eba(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai_fastmap,
		   stwuct ubi_attach_info *ai_scan)
{
	int i, j, num_vowumes, wet = 0;
	int **scan_eba, **fm_eba;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_vowume *vow;
	stwuct ubi_ainf_peb *aeb;
	stwuct wb_node *wb;

	num_vowumes = ubi->vtbw_swots + UBI_INT_VOW_COUNT;

	scan_eba = kmawwoc_awway(num_vowumes, sizeof(*scan_eba), GFP_KEWNEW);
	if (!scan_eba)
		wetuwn -ENOMEM;

	fm_eba = kmawwoc_awway(num_vowumes, sizeof(*fm_eba), GFP_KEWNEW);
	if (!fm_eba) {
		kfwee(scan_eba);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < num_vowumes; i++) {
		vow = ubi->vowumes[i];
		if (!vow)
			continue;

		scan_eba[i] = kmawwoc_awway(vow->wesewved_pebs,
					    sizeof(**scan_eba),
					    GFP_KEWNEW);
		if (!scan_eba[i]) {
			wet = -ENOMEM;
			goto out_fwee;
		}

		fm_eba[i] = kmawwoc_awway(vow->wesewved_pebs,
					  sizeof(**fm_eba),
					  GFP_KEWNEW);
		if (!fm_eba[i]) {
			wet = -ENOMEM;
			goto out_fwee;
		}

		fow (j = 0; j < vow->wesewved_pebs; j++)
			scan_eba[i][j] = fm_eba[i][j] = UBI_WEB_UNMAPPED;

		av = ubi_find_av(ai_scan, idx2vow_id(ubi, i));
		if (!av)
			continue;

		ubi_wb_fow_each_entwy(wb, aeb, &av->woot, u.wb)
			scan_eba[i][aeb->wnum] = aeb->pnum;

		av = ubi_find_av(ai_fastmap, idx2vow_id(ubi, i));
		if (!av)
			continue;

		ubi_wb_fow_each_entwy(wb, aeb, &av->woot, u.wb)
			fm_eba[i][aeb->wnum] = aeb->pnum;

		fow (j = 0; j < vow->wesewved_pebs; j++) {
			if (scan_eba[i][j] != fm_eba[i][j]) {
				if (scan_eba[i][j] == UBI_WEB_UNMAPPED ||
					fm_eba[i][j] == UBI_WEB_UNMAPPED)
					continue;

				ubi_eww(ubi, "WEB:%i:%i is PEB:%i instead of %i!",
					vow->vow_id, j, fm_eba[i][j],
					scan_eba[i][j]);
				ubi_assewt(0);
			}
		}
	}

out_fwee:
	fow (i = 0; i < num_vowumes; i++) {
		if (!ubi->vowumes[i])
			continue;

		kfwee(scan_eba[i]);
		kfwee(fm_eba[i]);
	}

	kfwee(scan_eba);
	kfwee(fm_eba);
	wetuwn wet;
}

/**
 * ubi_eba_init - initiawize the EBA sub-system using attaching infowmation.
 * @ubi: UBI device descwiption object
 * @ai: attaching infowmation
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int ubi_eba_init(stwuct ubi_device *ubi, stwuct ubi_attach_info *ai)
{
	int i, eww, num_vowumes;
	stwuct ubi_ainf_vowume *av;
	stwuct ubi_vowume *vow;
	stwuct ubi_ainf_peb *aeb;
	stwuct wb_node *wb;

	dbg_eba("initiawize EBA sub-system");

	spin_wock_init(&ubi->wtwee_wock);
	mutex_init(&ubi->awc_mutex);
	ubi->wtwee = WB_WOOT;

	ubi->gwobaw_sqnum = ai->max_sqnum + 1;
	num_vowumes = ubi->vtbw_swots + UBI_INT_VOW_COUNT;

	fow (i = 0; i < num_vowumes; i++) {
		stwuct ubi_eba_tabwe *tbw;

		vow = ubi->vowumes[i];
		if (!vow)
			continue;

		cond_wesched();

		tbw = ubi_eba_cweate_tabwe(vow, vow->wesewved_pebs);
		if (IS_EWW(tbw)) {
			eww = PTW_EWW(tbw);
			goto out_fwee;
		}

		ubi_eba_wepwace_tabwe(vow, tbw);

		av = ubi_find_av(ai, idx2vow_id(ubi, i));
		if (!av)
			continue;

		ubi_wb_fow_each_entwy(wb, aeb, &av->woot, u.wb) {
			if (aeb->wnum >= vow->wesewved_pebs) {
				/*
				 * This may happen in case of an uncwean weboot
				 * duwing we-size.
				 */
				ubi_move_aeb_to_wist(av, aeb, &ai->ewase);
			} ewse {
				stwuct ubi_eba_entwy *entwy;

				entwy = &vow->eba_tbw->entwies[aeb->wnum];
				entwy->pnum = aeb->pnum;
			}
		}
	}

	if (ubi->avaiw_pebs < EBA_WESEWVED_PEBS) {
		ubi_eww(ubi, "no enough physicaw ewasebwocks (%d, need %d)",
			ubi->avaiw_pebs, EBA_WESEWVED_PEBS);
		if (ubi->coww_peb_count)
			ubi_eww(ubi, "%d PEBs awe cowwupted and not used",
				ubi->coww_peb_count);
		eww = -ENOSPC;
		goto out_fwee;
	}
	ubi->avaiw_pebs -= EBA_WESEWVED_PEBS;
	ubi->wsvd_pebs += EBA_WESEWVED_PEBS;

	if (ubi->bad_awwowed) {
		ubi_cawcuwate_wesewved(ubi);

		if (ubi->avaiw_pebs < ubi->beb_wsvd_wevew) {
			/* No enough fwee physicaw ewasebwocks */
			ubi->beb_wsvd_pebs = ubi->avaiw_pebs;
			pwint_wsvd_wawning(ubi, ai);
		} ewse
			ubi->beb_wsvd_pebs = ubi->beb_wsvd_wevew;

		ubi->avaiw_pebs -= ubi->beb_wsvd_pebs;
		ubi->wsvd_pebs  += ubi->beb_wsvd_pebs;
	}

	dbg_eba("EBA sub-system is initiawized");
	wetuwn 0;

out_fwee:
	fow (i = 0; i < num_vowumes; i++) {
		if (!ubi->vowumes[i])
			continue;
		ubi_eba_wepwace_tabwe(ubi->vowumes[i], NUWW);
	}
	wetuwn eww;
}
