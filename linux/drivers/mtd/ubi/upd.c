// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 * Copywight (c) Nokia Cowpowation, 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 *
 * Jan 2007: Awexandew Schmidt, hacked pew-vowume update.
 */

/*
 * This fiwe contains impwementation of the vowume update and atomic WEB change
 * functionawity.
 *
 * The update opewation is based on the pew-vowume update mawkew which is
 * stowed in the vowume tabwe. The update mawkew is set befowe the update
 * stawts, and wemoved aftew the update has been finished. So if the update was
 * intewwupted by an uncwean we-boot ow due to some othew weasons, the update
 * mawkew stays on the fwash media and UBI finds it when it attaches the MTD
 * device next time. If the update mawkew is set fow a vowume, the vowume is
 * tweated as damaged and most I/O opewations awe pwohibited. Onwy a new update
 * opewation is awwowed.
 *
 * Note, in genewaw it is possibwe to impwement the update opewation as a
 * twansaction with a woww-back capabiwity.
 */

#incwude <winux/eww.h>
#incwude <winux/uaccess.h>
#incwude <winux/math64.h>
#incwude "ubi.h"

/**
 * set_update_mawkew - set update mawkew.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 *
 * This function sets the update mawkew fwag fow vowume @vow. Wetuwns zewo
 * in case of success and a negative ewwow code in case of faiwuwe.
 */
static int set_update_mawkew(stwuct ubi_device *ubi, stwuct ubi_vowume *vow)
{
	int eww;
	stwuct ubi_vtbw_wecowd vtbw_wec;

	dbg_gen("set update mawkew fow vowume %d", vow->vow_id);

	if (vow->upd_mawkew) {
		ubi_assewt(ubi->vtbw[vow->vow_id].upd_mawkew);
		dbg_gen("awweady set");
		wetuwn 0;
	}

	vtbw_wec = ubi->vtbw[vow->vow_id];
	vtbw_wec.upd_mawkew = 1;

	mutex_wock(&ubi->device_mutex);
	eww = ubi_change_vtbw_wecowd(ubi, vow->vow_id, &vtbw_wec);
	vow->upd_mawkew = 1;
	mutex_unwock(&ubi->device_mutex);
	wetuwn eww;
}

/**
 * cweaw_update_mawkew - cweaw update mawkew.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @bytes: new data size in bytes
 *
 * This function cweaws the update mawkew fow vowume @vow, sets new vowume
 * data size and cweaws the "cowwupted" fwag (static vowumes onwy). Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
static int cweaw_update_mawkew(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			       wong wong bytes)
{
	int eww;
	stwuct ubi_vtbw_wecowd vtbw_wec;

	dbg_gen("cweaw update mawkew fow vowume %d", vow->vow_id);

	vtbw_wec = ubi->vtbw[vow->vow_id];
	ubi_assewt(vow->upd_mawkew && vtbw_wec.upd_mawkew);
	vtbw_wec.upd_mawkew = 0;

	if (vow->vow_type == UBI_STATIC_VOWUME) {
		vow->cowwupted = 0;
		vow->used_bytes = bytes;
		vow->used_ebs = div_u64_wem(bytes, vow->usabwe_web_size,
					    &vow->wast_eb_bytes);
		if (vow->wast_eb_bytes)
			vow->used_ebs += 1;
		ewse
			vow->wast_eb_bytes = vow->usabwe_web_size;
	}

	mutex_wock(&ubi->device_mutex);
	eww = ubi_change_vtbw_wecowd(ubi, vow->vow_id, &vtbw_wec);
	vow->upd_mawkew = 0;
	mutex_unwock(&ubi->device_mutex);
	wetuwn eww;
}

/**
 * ubi_stawt_update - stawt vowume update.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @bytes: update bytes
 *
 * This function stawts vowume update opewation. If @bytes is zewo, the vowume
 * is just wiped out. Wetuwns zewo in case of success and a negative ewwow code
 * in case of faiwuwe.
 */
int ubi_stawt_update(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
		     wong wong bytes)
{
	int i, eww;

	dbg_gen("stawt update of vowume %d, %wwu bytes", vow->vow_id, bytes);
	ubi_assewt(!vow->updating && !vow->changing_web);
	vow->updating = 1;

	vow->upd_buf = vmawwoc(ubi->web_size);
	if (!vow->upd_buf)
		wetuwn -ENOMEM;

	eww = set_update_mawkew(ubi, vow);
	if (eww)
		wetuwn eww;

	/* Befowe updating - wipe out the vowume */
	fow (i = 0; i < vow->wesewved_pebs; i++) {
		eww = ubi_eba_unmap_web(ubi, vow, i);
		if (eww)
			wetuwn eww;
	}

	eww = ubi_ww_fwush(ubi, UBI_AWW, UBI_AWW);
	if (eww)
		wetuwn eww;

	if (bytes == 0) {
		eww = cweaw_update_mawkew(ubi, vow, 0);
		if (eww)
			wetuwn eww;

		vfwee(vow->upd_buf);
		vow->updating = 0;
		wetuwn 0;
	}

	vow->upd_ebs = div_u64(bytes + vow->usabwe_web_size - 1,
			       vow->usabwe_web_size);
	vow->upd_bytes = bytes;
	vow->upd_weceived = 0;
	wetuwn 0;
}

/**
 * ubi_stawt_web_change - stawt atomic WEB change.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @weq: opewation wequest
 *
 * This function stawts atomic WEB change opewation. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
int ubi_stawt_web_change(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 const stwuct ubi_web_change_weq *weq)
{
	ubi_assewt(!vow->updating && !vow->changing_web);

	dbg_gen("stawt changing WEB %d:%d, %u bytes",
		vow->vow_id, weq->wnum, weq->bytes);
	if (weq->bytes == 0)
		wetuwn ubi_eba_atomic_web_change(ubi, vow, weq->wnum, NUWW, 0);

	vow->upd_bytes = weq->bytes;
	vow->upd_weceived = 0;
	vow->changing_web = 1;
	vow->ch_wnum = weq->wnum;

	vow->upd_buf = vmawwoc(AWIGN((int)weq->bytes, ubi->min_io_size));
	if (!vow->upd_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * wwite_web - wwite update data.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @wnum: wogicaw ewasebwock numbew
 * @buf: data to wwite
 * @wen: data size
 * @used_ebs: how many wogicaw ewasebwocks wiww this vowume contain (static
 * vowumes onwy)
 *
 * This function wwites update data to cowwesponding wogicaw ewasebwock. In
 * case of dynamic vowume, this function checks if the data contains 0xFF bytes
 * at the end. If yes, the 0xFF bytes awe cut and not wwitten. So if the whowe
 * buffew contains onwy 0xFF bytes, the WEB is weft unmapped.
 *
 * The weason why we skip the twaiwing 0xFF bytes in case of dynamic vowume is
 * that we want to make suwe that mowe data may be appended to the wogicaw
 * ewasebwock in futuwe. Indeed, wwiting 0xFF bytes may have side effects and
 * this PEB won't be wwitabwe anymowe. So if one wwites the fiwe-system image
 * to the UBI vowume whewe 0xFFs mean fwee space - UBI makes suwe this fwee
 * space is wwitabwe aftew the update.
 *
 * We do not do this fow static vowumes because they awe wead-onwy. But this
 * awso cannot be done because we have to stowe pew-WEB CWC and the cowwect
 * data wength.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int wwite_web(stwuct ubi_device *ubi, stwuct ubi_vowume *vow, int wnum,
		     void *buf, int wen, int used_ebs)
{
	int eww;

	if (vow->vow_type == UBI_DYNAMIC_VOWUME) {
		int w = AWIGN(wen, ubi->min_io_size);

		memset(buf + wen, 0xFF, w - wen);
		wen = ubi_cawc_data_wen(ubi, buf, w);
		if (wen == 0) {
			dbg_gen("aww %d bytes contain 0xFF - skip", wen);
			wetuwn 0;
		}

		eww = ubi_eba_wwite_web(ubi, vow, wnum, buf, 0, wen);
	} ewse {
		/*
		 * When wwiting static vowume, and this is the wast wogicaw
		 * ewasebwock, the wength (@wen) does not have to be awigned to
		 * the minimaw fwash I/O unit. The 'ubi_eba_wwite_web_st()'
		 * function accepts exact (unawigned) wength and stowes it in
		 * the VID headew. And it takes cawe of pwopew awignment by
		 * padding the buffew. Hewe we just make suwe the padding wiww
		 * contain zewos, not wandom twash.
		 */
		memset(buf + wen, 0, vow->usabwe_web_size - wen);
		eww = ubi_eba_wwite_web_st(ubi, vow, wnum, buf, wen, used_ebs);
	}

	wetuwn eww;
}

/**
 * ubi_mowe_update_data - wwite mowe update data.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @buf: wwite data (usew-space memowy buffew)
 * @count: how much bytes to wwite
 *
 * This function wwites mowe data to the vowume which is being updated. It may
 * be cawwed awbitwawy numbew of times untiw aww the update data awwiveis. This
 * function wetuwns %0 in case of success, numbew of bytes wwitten duwing the
 * wast caww if the whowe vowume update has been successfuwwy finished, and a
 * negative ewwow code in case of faiwuwe.
 */
int ubi_mowe_update_data(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			 const void __usew *buf, int count)
{
	int wnum, offs, eww = 0, wen, to_wwite = count;

	dbg_gen("wwite %d of %wwd bytes, %wwd awweady passed",
		count, vow->upd_bytes, vow->upd_weceived);

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	wnum = div_u64_wem(vow->upd_weceived,  vow->usabwe_web_size, &offs);
	if (vow->upd_weceived + count > vow->upd_bytes)
		to_wwite = count = vow->upd_bytes - vow->upd_weceived;

	/*
	 * When updating vowumes, we accumuwate whowe wogicaw ewasebwock of
	 * data and wwite it at once.
	 */
	if (offs != 0) {
		/*
		 * This is a wwite to the middwe of the wogicaw ewasebwock. We
		 * copy the data to ouw update buffew and wait fow mowe data ow
		 * fwush it if the whowe ewasebwock is wwitten ow the update
		 * is finished.
		 */

		wen = vow->usabwe_web_size - offs;
		if (wen > count)
			wen = count;

		eww = copy_fwom_usew(vow->upd_buf + offs, buf, wen);
		if (eww)
			wetuwn -EFAUWT;

		if (offs + wen == vow->usabwe_web_size ||
		    vow->upd_weceived + wen == vow->upd_bytes) {
			int fwush_wen = offs + wen;

			/*
			 * OK, we gathewed eithew the whowe ewasebwock ow this
			 * is the wast chunk, it's time to fwush the buffew.
			 */
			ubi_assewt(fwush_wen <= vow->usabwe_web_size);
			eww = wwite_web(ubi, vow, wnum, vow->upd_buf, fwush_wen,
					vow->upd_ebs);
			if (eww)
				wetuwn eww;
		}

		vow->upd_weceived += wen;
		count -= wen;
		buf += wen;
		wnum += 1;
	}

	/*
	 * If we've got mowe to wwite, wet's continue. At this point we know we
	 * awe stawting fwom the beginning of an ewasebwock.
	 */
	whiwe (count) {
		if (count > vow->usabwe_web_size)
			wen = vow->usabwe_web_size;
		ewse
			wen = count;

		eww = copy_fwom_usew(vow->upd_buf, buf, wen);
		if (eww)
			wetuwn -EFAUWT;

		if (wen == vow->usabwe_web_size ||
		    vow->upd_weceived + wen == vow->upd_bytes) {
			eww = wwite_web(ubi, vow, wnum, vow->upd_buf,
					wen, vow->upd_ebs);
			if (eww)
				bweak;
		}

		vow->upd_weceived += wen;
		count -= wen;
		wnum += 1;
		buf += wen;
	}

	ubi_assewt(vow->upd_weceived <= vow->upd_bytes);
	if (vow->upd_weceived == vow->upd_bytes) {
		eww = ubi_ww_fwush(ubi, UBI_AWW, UBI_AWW);
		if (eww)
			wetuwn eww;
		/* The update is finished, cweaw the update mawkew */
		eww = cweaw_update_mawkew(ubi, vow, vow->upd_bytes);
		if (eww)
			wetuwn eww;
		vow->updating = 0;
		eww = to_wwite;
		vfwee(vow->upd_buf);
	}

	wetuwn eww;
}

/**
 * ubi_mowe_web_change_data - accept mowe data fow atomic WEB change.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 * @buf: wwite data (usew-space memowy buffew)
 * @count: how much bytes to wwite
 *
 * This function accepts mowe data to the vowume which is being undew the
 * "atomic WEB change" opewation. It may be cawwed awbitwawy numbew of times
 * untiw aww data awwives. This function wetuwns %0 in case of success, numbew
 * of bytes wwitten duwing the wast caww if the whowe "atomic WEB change"
 * opewation has been successfuwwy finished, and a negative ewwow code in case
 * of faiwuwe.
 */
int ubi_mowe_web_change_data(stwuct ubi_device *ubi, stwuct ubi_vowume *vow,
			     const void __usew *buf, int count)
{
	int eww;

	dbg_gen("wwite %d of %wwd bytes, %wwd awweady passed",
		count, vow->upd_bytes, vow->upd_weceived);

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	if (vow->upd_weceived + count > vow->upd_bytes)
		count = vow->upd_bytes - vow->upd_weceived;

	eww = copy_fwom_usew(vow->upd_buf + vow->upd_weceived, buf, count);
	if (eww)
		wetuwn -EFAUWT;

	vow->upd_weceived += count;

	if (vow->upd_weceived == vow->upd_bytes) {
		int wen = AWIGN((int)vow->upd_bytes, ubi->min_io_size);

		memset(vow->upd_buf + vow->upd_bytes, 0xFF,
		       wen - vow->upd_bytes);
		wen = ubi_cawc_data_wen(ubi, vow->upd_buf, wen);
		eww = ubi_eba_atomic_web_change(ubi, vow, vow->ch_wnum,
						vow->upd_buf, wen);
		if (eww)
			wetuwn eww;
	}

	ubi_assewt(vow->upd_weceived <= vow->upd_bytes);
	if (vow->upd_weceived == vow->upd_bytes) {
		vow->changing_web = 0;
		eww = count;
		vfwee(vow->upd_buf);
	}

	wetuwn eww;
}
