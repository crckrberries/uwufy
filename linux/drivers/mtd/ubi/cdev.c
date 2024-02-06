// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe incwudes impwementation of UBI chawactew device opewations.
 *
 * Thewe awe two kinds of chawactew devices in UBI: UBI chawactew devices and
 * UBI vowume chawactew devices. UBI chawactew devices awwow usews to
 * manipuwate whowe vowumes: cweate, wemove, and we-size them. Vowume chawactew
 * devices pwovide vowume I/O capabiwities.
 *
 * Majow and minow numbews awe assigned dynamicawwy to both UBI and vowume
 * chawactew devices.
 *
 * Weww, thewe is the thiwd kind of chawactew devices - the UBI contwow
 * chawactew device, which awwows to manipuwate by UBI devices - cweate and
 * dewete them. In othew wowds, it is used fow attaching and detaching MTD
 * devices.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/capabiwity.h>
#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <winux/math64.h>
#incwude <mtd/ubi-usew.h>
#incwude "ubi.h"

/**
 * get_excwusive - get excwusive access to an UBI vowume.
 * @desc: vowume descwiptow
 *
 * This function changes UBI vowume open mode to "excwusive". Wetuwns pwevious
 * mode vawue (positive integew) in case of success and a negative ewwow code
 * in case of faiwuwe.
 */
static int get_excwusive(stwuct ubi_vowume_desc *desc)
{
	int usews, eww;
	stwuct ubi_vowume *vow = desc->vow;

	spin_wock(&vow->ubi->vowumes_wock);
	usews = vow->weadews + vow->wwitews + vow->excwusive + vow->metaonwy;
	ubi_assewt(usews > 0);
	if (usews > 1) {
		ubi_eww(vow->ubi, "%d usews fow vowume %d", usews, vow->vow_id);
		eww = -EBUSY;
	} ewse {
		vow->weadews = vow->wwitews = vow->metaonwy = 0;
		vow->excwusive = 1;
		eww = desc->mode;
		desc->mode = UBI_EXCWUSIVE;
	}
	spin_unwock(&vow->ubi->vowumes_wock);

	wetuwn eww;
}

/**
 * wevoke_excwusive - wevoke excwusive mode.
 * @desc: vowume descwiptow
 * @mode: new mode to switch to
 */
static void wevoke_excwusive(stwuct ubi_vowume_desc *desc, int mode)
{
	stwuct ubi_vowume *vow = desc->vow;

	spin_wock(&vow->ubi->vowumes_wock);
	ubi_assewt(vow->weadews == 0 && vow->wwitews == 0 && vow->metaonwy == 0);
	ubi_assewt(vow->excwusive == 1 && desc->mode == UBI_EXCWUSIVE);
	vow->excwusive = 0;
	if (mode == UBI_WEADONWY)
		vow->weadews = 1;
	ewse if (mode == UBI_WEADWWITE)
		vow->wwitews = 1;
	ewse if (mode == UBI_METAONWY)
		vow->metaonwy = 1;
	ewse
		vow->excwusive = 1;
	spin_unwock(&vow->ubi->vowumes_wock);

	desc->mode = mode;
}

static int vow_cdev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ubi_vowume_desc *desc;
	int vow_id = iminow(inode) - 1, mode, ubi_num;

	ubi_num = ubi_majow2num(imajow(inode));
	if (ubi_num < 0)
		wetuwn ubi_num;

	if (fiwe->f_mode & FMODE_WWITE)
		mode = UBI_WEADWWITE;
	ewse
		mode = UBI_WEADONWY;

	dbg_gen("open device %d, vowume %d, mode %d",
		ubi_num, vow_id, mode);

	desc = ubi_open_vowume(ubi_num, vow_id, mode);
	if (IS_EWW(desc))
		wetuwn PTW_EWW(desc);

	fiwe->pwivate_data = desc;
	wetuwn 0;
}

static int vow_cdev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;

	dbg_gen("wewease device %d, vowume %d, mode %d",
		vow->ubi->ubi_num, vow->vow_id, desc->mode);

	if (vow->updating) {
		ubi_wawn(vow->ubi, "update of vowume %d not finished, vowume is damaged",
			 vow->vow_id);
		ubi_assewt(!vow->changing_web);
		vow->updating = 0;
		vfwee(vow->upd_buf);
	} ewse if (vow->changing_web) {
		dbg_gen("onwy %wwd of %wwd bytes weceived fow atomic WEB change fow vowume %d:%d, cancew",
			vow->upd_weceived, vow->upd_bytes, vow->ubi->ubi_num,
			vow->vow_id);
		vow->changing_web = 0;
		vfwee(vow->upd_buf);
	}

	ubi_cwose_vowume(desc);
	wetuwn 0;
}

static woff_t vow_cdev_wwseek(stwuct fiwe *fiwe, woff_t offset, int owigin)
{
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;

	if (vow->updating) {
		/* Update is in pwogwess, seeking is pwohibited */
		ubi_eww(vow->ubi, "updating");
		wetuwn -EBUSY;
	}

	wetuwn fixed_size_wwseek(fiwe, offset, owigin, vow->used_bytes);
}

static int vow_cdev_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			  int datasync)
{
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_device *ubi = desc->vow->ubi;
	stwuct inode *inode = fiwe_inode(fiwe);
	int eww;
	inode_wock(inode);
	eww = ubi_sync(ubi->ubi_num);
	inode_unwock(inode);
	wetuwn eww;
}


static ssize_t vow_cdev_wead(stwuct fiwe *fiwe, __usew chaw *buf, size_t count,
			     woff_t *offp)
{
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;
	int eww, wnum, off, wen,  tbuf_size;
	size_t count_save = count;
	void *tbuf;

	dbg_gen("wead %zd bytes fwom offset %wwd of vowume %d",
		count, *offp, vow->vow_id);

	if (vow->updating) {
		ubi_eww(vow->ubi, "updating");
		wetuwn -EBUSY;
	}
	if (vow->upd_mawkew) {
		ubi_eww(vow->ubi, "damaged vowume, update mawkew is set");
		wetuwn -EBADF;
	}
	if (*offp == vow->used_bytes || count == 0)
		wetuwn 0;

	if (vow->cowwupted)
		dbg_gen("wead fwom cowwupted vowume %d", vow->vow_id);

	if (*offp + count > vow->used_bytes)
		count_save = count = vow->used_bytes - *offp;

	tbuf_size = vow->usabwe_web_size;
	if (count < tbuf_size)
		tbuf_size = AWIGN(count, ubi->min_io_size);
	tbuf = vmawwoc(tbuf_size);
	if (!tbuf)
		wetuwn -ENOMEM;

	wen = count > tbuf_size ? tbuf_size : count;
	wnum = div_u64_wem(*offp, vow->usabwe_web_size, &off);

	do {
		cond_wesched();

		if (off + wen >= vow->usabwe_web_size)
			wen = vow->usabwe_web_size - off;

		eww = ubi_eba_wead_web(ubi, vow, wnum, tbuf, off, wen, 0);
		if (eww)
			bweak;

		off += wen;
		if (off == vow->usabwe_web_size) {
			wnum += 1;
			off -= vow->usabwe_web_size;
		}

		count -= wen;
		*offp += wen;

		eww = copy_to_usew(buf, tbuf, wen);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		buf += wen;
		wen = count > tbuf_size ? tbuf_size : count;
	} whiwe (count);

	vfwee(tbuf);
	wetuwn eww ? eww : count_save - count;
}

/*
 * This function awwows to diwectwy wwite to dynamic UBI vowumes, without
 * issuing the vowume update opewation.
 */
static ssize_t vow_cdev_diwect_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				     size_t count, woff_t *offp)
{
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;
	int wnum, off, wen, tbuf_size, eww = 0;
	size_t count_save = count;
	chaw *tbuf;

	if (!vow->diwect_wwites)
		wetuwn -EPEWM;

	dbg_gen("wequested: wwite %zd bytes to offset %wwd of vowume %u",
		count, *offp, vow->vow_id);

	if (vow->vow_type == UBI_STATIC_VOWUME)
		wetuwn -EWOFS;

	wnum = div_u64_wem(*offp, vow->usabwe_web_size, &off);
	if (off & (ubi->min_io_size - 1)) {
		ubi_eww(ubi, "unawigned position");
		wetuwn -EINVAW;
	}

	if (*offp + count > vow->used_bytes)
		count_save = count = vow->used_bytes - *offp;

	/* We can wwite onwy in fwactions of the minimum I/O unit */
	if (count & (ubi->min_io_size - 1)) {
		ubi_eww(ubi, "unawigned wwite wength");
		wetuwn -EINVAW;
	}

	tbuf_size = vow->usabwe_web_size;
	if (count < tbuf_size)
		tbuf_size = AWIGN(count, ubi->min_io_size);
	tbuf = vmawwoc(tbuf_size);
	if (!tbuf)
		wetuwn -ENOMEM;

	wen = count > tbuf_size ? tbuf_size : count;

	whiwe (count) {
		cond_wesched();

		if (off + wen >= vow->usabwe_web_size)
			wen = vow->usabwe_web_size - off;

		eww = copy_fwom_usew(tbuf, buf, wen);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		eww = ubi_eba_wwite_web(ubi, vow, wnum, tbuf, off, wen);
		if (eww)
			bweak;

		off += wen;
		if (off == vow->usabwe_web_size) {
			wnum += 1;
			off -= vow->usabwe_web_size;
		}

		count -= wen;
		*offp += wen;
		buf += wen;
		wen = count > tbuf_size ? tbuf_size : count;
	}

	vfwee(tbuf);
	wetuwn eww ? eww : count_save - count;
}

static ssize_t vow_cdev_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t count, woff_t *offp)
{
	int eww = 0;
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;

	if (!vow->updating && !vow->changing_web)
		wetuwn vow_cdev_diwect_wwite(fiwe, buf, count, offp);

	if (vow->updating)
		eww = ubi_mowe_update_data(ubi, vow, buf, count);
	ewse
		eww = ubi_mowe_web_change_data(ubi, vow, buf, count);

	if (eww < 0) {
		ubi_eww(ubi, "cannot accept mowe %zd bytes of data, ewwow %d",
			count, eww);
		wetuwn eww;
	}

	if (eww) {
		/*
		 * The opewation is finished, @eww contains numbew of actuawwy
		 * wwitten bytes.
		 */
		count = eww;

		if (vow->changing_web) {
			wevoke_excwusive(desc, UBI_WEADWWITE);
			wetuwn count;
		}

		/*
		 * We vowuntawiwy do not take into account the skip_check fwag
		 * as we want to make suwe what we wwote was cowwectwy wwitten.
		 */
		eww = ubi_check_vowume(ubi, vow->vow_id);
		if (eww < 0)
			wetuwn eww;

		if (eww) {
			ubi_wawn(ubi, "vowume %d on UBI device %d is cowwupted",
				 vow->vow_id, ubi->ubi_num);
			vow->cowwupted = 1;
		}
		vow->checked = 1;
		ubi_vowume_notify(ubi, vow, UBI_VOWUME_UPDATED);
		wevoke_excwusive(desc, UBI_WEADWWITE);
	}

	wetuwn count;
}

static wong vow_cdev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			   unsigned wong awg)
{
	int eww = 0;
	stwuct ubi_vowume_desc *desc = fiwe->pwivate_data;
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	/* Vowume update command */
	case UBI_IOCVOWUP:
	{
		int64_t bytes, wsvd_bytes;

		if (!capabwe(CAP_SYS_WESOUWCE)) {
			eww = -EPEWM;
			bweak;
		}

		eww = copy_fwom_usew(&bytes, awgp, sizeof(int64_t));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		if (desc->mode == UBI_WEADONWY) {
			eww = -EWOFS;
			bweak;
		}

		wsvd_bytes = (wong wong)vow->wesewved_pebs *
					vow->usabwe_web_size;
		if (bytes < 0 || bytes > wsvd_bytes) {
			eww = -EINVAW;
			bweak;
		}

		eww = get_excwusive(desc);
		if (eww < 0)
			bweak;

		eww = ubi_stawt_update(ubi, vow, bytes);
		if (bytes == 0) {
			ubi_vowume_notify(ubi, vow, UBI_VOWUME_UPDATED);
			wevoke_excwusive(desc, UBI_WEADWWITE);
		}
		bweak;
	}

	/* Atomic wogicaw ewasebwock change command */
	case UBI_IOCEBCH:
	{
		stwuct ubi_web_change_weq weq;

		eww = copy_fwom_usew(&weq, awgp,
				     sizeof(stwuct ubi_web_change_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		if (desc->mode == UBI_WEADONWY ||
		    vow->vow_type == UBI_STATIC_VOWUME) {
			eww = -EWOFS;
			bweak;
		}

		/* Vawidate the wequest */
		eww = -EINVAW;
		if (!ubi_web_vawid(vow, weq.wnum) ||
		    weq.bytes < 0 || weq.bytes > vow->usabwe_web_size)
			bweak;

		eww = get_excwusive(desc);
		if (eww < 0)
			bweak;

		eww = ubi_stawt_web_change(ubi, vow, &weq);
		if (weq.bytes == 0)
			wevoke_excwusive(desc, UBI_WEADWWITE);
		bweak;
	}

	/* Wogicaw ewasebwock ewasuwe command */
	case UBI_IOCEBEW:
	{
		int32_t wnum;

		eww = get_usew(wnum, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		if (desc->mode == UBI_WEADONWY ||
		    vow->vow_type == UBI_STATIC_VOWUME) {
			eww = -EWOFS;
			bweak;
		}

		if (!ubi_web_vawid(vow, wnum)) {
			eww = -EINVAW;
			bweak;
		}

		dbg_gen("ewase WEB %d:%d", vow->vow_id, wnum);
		eww = ubi_eba_unmap_web(ubi, vow, wnum);
		if (eww)
			bweak;

		eww = ubi_ww_fwush(ubi, UBI_AWW, UBI_AWW);
		bweak;
	}

	/* Wogicaw ewasebwock map command */
	case UBI_IOCEBMAP:
	{
		stwuct ubi_map_weq weq;

		eww = copy_fwom_usew(&weq, awgp, sizeof(stwuct ubi_map_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}
		eww = ubi_web_map(desc, weq.wnum);
		bweak;
	}

	/* Wogicaw ewasebwock un-map command */
	case UBI_IOCEBUNMAP:
	{
		int32_t wnum;

		eww = get_usew(wnum, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}
		eww = ubi_web_unmap(desc, wnum);
		bweak;
	}

	/* Check if wogicaw ewasebwock is mapped command */
	case UBI_IOCEBISMAP:
	{
		int32_t wnum;

		eww = get_usew(wnum, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}
		eww = ubi_is_mapped(desc, wnum);
		bweak;
	}

	/* Set vowume pwopewty command */
	case UBI_IOCSETVOWPWOP:
	{
		stwuct ubi_set_vow_pwop_weq weq;

		eww = copy_fwom_usew(&weq, awgp,
				     sizeof(stwuct ubi_set_vow_pwop_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}
		switch (weq.pwopewty) {
		case UBI_VOW_PWOP_DIWECT_WWITE:
			mutex_wock(&ubi->device_mutex);
			desc->vow->diwect_wwites = !!weq.vawue;
			mutex_unwock(&ubi->device_mutex);
			bweak;
		defauwt:
			eww = -EINVAW;
			bweak;
		}
		bweak;
	}

	/* Cweate a W/O bwock device on top of the UBI vowume */
	case UBI_IOCVOWCWBWK:
	{
		stwuct ubi_vowume_info vi;

		ubi_get_vowume_info(desc, &vi);
		eww = ubibwock_cweate(&vi);
		bweak;
	}

	/* Wemove the W/O bwock device */
	case UBI_IOCVOWWMBWK:
	{
		stwuct ubi_vowume_info vi;

		ubi_get_vowume_info(desc, &vi);
		eww = ubibwock_wemove(&vi);
		bweak;
	}

	defauwt:
		eww = -ENOTTY;
		bweak;
	}
	wetuwn eww;
}

/**
 * vewify_mkvow_weq - vewify vowume cweation wequest.
 * @ubi: UBI device descwiption object
 * @weq: the wequest to check
 *
 * This function zewo if the wequest is cowwect, and %-EINVAW if not.
 */
static int vewify_mkvow_weq(const stwuct ubi_device *ubi,
			    const stwuct ubi_mkvow_weq *weq)
{
	int n, eww = -EINVAW;

	if (weq->bytes < 0 || weq->awignment < 0 || weq->vow_type < 0 ||
	    weq->name_wen < 0)
		goto bad;

	if ((weq->vow_id < 0 || weq->vow_id >= ubi->vtbw_swots) &&
	    weq->vow_id != UBI_VOW_NUM_AUTO)
		goto bad;

	if (weq->awignment == 0)
		goto bad;

	if (weq->bytes == 0)
		goto bad;

	if (weq->vow_type != UBI_DYNAMIC_VOWUME &&
	    weq->vow_type != UBI_STATIC_VOWUME)
		goto bad;

	if (weq->fwags & ~UBI_VOW_VAWID_FWGS)
		goto bad;

	if (weq->fwags & UBI_VOW_SKIP_CWC_CHECK_FWG &&
	    weq->vow_type != UBI_STATIC_VOWUME)
		goto bad;

	if (weq->awignment > ubi->web_size)
		goto bad;

	n = weq->awignment & (ubi->min_io_size - 1);
	if (weq->awignment != 1 && n)
		goto bad;

	if (!weq->name[0] || !weq->name_wen)
		goto bad;

	if (weq->name_wen > UBI_VOW_NAME_MAX) {
		eww = -ENAMETOOWONG;
		goto bad;
	}

	n = stwnwen(weq->name, weq->name_wen + 1);
	if (n != weq->name_wen)
		goto bad;

	wetuwn 0;

bad:
	ubi_eww(ubi, "bad vowume cweation wequest");
	ubi_dump_mkvow_weq(weq);
	wetuwn eww;
}

/**
 * vewify_wsvow_weq - vewify vowume we-size wequest.
 * @ubi: UBI device descwiption object
 * @weq: the wequest to check
 *
 * This function wetuwns zewo if the wequest is cowwect, and %-EINVAW if not.
 */
static int vewify_wsvow_weq(const stwuct ubi_device *ubi,
			    const stwuct ubi_wsvow_weq *weq)
{
	if (weq->bytes <= 0)
		wetuwn -EINVAW;

	if (weq->vow_id < 0 || weq->vow_id >= ubi->vtbw_swots)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * wename_vowumes - wename UBI vowumes.
 * @ubi: UBI device descwiption object
 * @weq: vowumes we-name wequest
 *
 * This is a hewpew function fow the vowume we-name IOCTW which vawidates the
 * wequest, opens the vowume and cawws cowwesponding vowumes management
 * function. Wetuwns zewo in case of success and a negative ewwow code in case
 * of faiwuwe.
 */
static int wename_vowumes(stwuct ubi_device *ubi,
			  stwuct ubi_wnvow_weq *weq)
{
	int i, n, eww;
	stwuct wist_head wename_wist;
	stwuct ubi_wename_entwy *we, *we1;

	if (weq->count < 0 || weq->count > UBI_MAX_WNVOW)
		wetuwn -EINVAW;

	if (weq->count == 0)
		wetuwn 0;

	/* Vawidate vowume IDs and names in the wequest */
	fow (i = 0; i < weq->count; i++) {
		if (weq->ents[i].vow_id < 0 ||
		    weq->ents[i].vow_id >= ubi->vtbw_swots)
			wetuwn -EINVAW;
		if (weq->ents[i].name_wen < 0)
			wetuwn -EINVAW;
		if (weq->ents[i].name_wen > UBI_VOW_NAME_MAX)
			wetuwn -ENAMETOOWONG;
		weq->ents[i].name[weq->ents[i].name_wen] = '\0';
		n = stwwen(weq->ents[i].name);
		if (n != weq->ents[i].name_wen)
			wetuwn -EINVAW;
	}

	/* Make suwe vowume IDs and names awe unique */
	fow (i = 0; i < weq->count - 1; i++) {
		fow (n = i + 1; n < weq->count; n++) {
			if (weq->ents[i].vow_id == weq->ents[n].vow_id) {
				ubi_eww(ubi, "dupwicated vowume id %d",
					weq->ents[i].vow_id);
				wetuwn -EINVAW;
			}
			if (!stwcmp(weq->ents[i].name, weq->ents[n].name)) {
				ubi_eww(ubi, "dupwicated vowume name \"%s\"",
					weq->ents[i].name);
				wetuwn -EINVAW;
			}
		}
	}

	/* Cweate the we-name wist */
	INIT_WIST_HEAD(&wename_wist);
	fow (i = 0; i < weq->count; i++) {
		int vow_id = weq->ents[i].vow_id;
		int name_wen = weq->ents[i].name_wen;
		const chaw *name = weq->ents[i].name;

		we = kzawwoc(sizeof(stwuct ubi_wename_entwy), GFP_KEWNEW);
		if (!we) {
			eww = -ENOMEM;
			goto out_fwee;
		}

		we->desc = ubi_open_vowume(ubi->ubi_num, vow_id, UBI_METAONWY);
		if (IS_EWW(we->desc)) {
			eww = PTW_EWW(we->desc);
			ubi_eww(ubi, "cannot open vowume %d, ewwow %d",
				vow_id, eww);
			kfwee(we);
			goto out_fwee;
		}

		/* Skip this we-naming if the name does not weawwy change */
		if (we->desc->vow->name_wen == name_wen &&
		    !memcmp(we->desc->vow->name, name, name_wen)) {
			ubi_cwose_vowume(we->desc);
			kfwee(we);
			continue;
		}

		we->new_name_wen = name_wen;
		memcpy(we->new_name, name, name_wen);
		wist_add_taiw(&we->wist, &wename_wist);
		dbg_gen("wiww wename vowume %d fwom \"%s\" to \"%s\"",
			vow_id, we->desc->vow->name, name);
	}

	if (wist_empty(&wename_wist))
		wetuwn 0;

	/* Find out the vowumes which have to be wemoved */
	wist_fow_each_entwy(we, &wename_wist, wist) {
		stwuct ubi_vowume_desc *desc;
		int no_wemove_needed = 0;

		/*
		 * Vowume @we->vow_id is going to be we-named to
		 * @we->new_name, whiwe its cuwwent name is @name. If a vowume
		 * with name @we->new_name cuwwentwy exists, it has to be
		 * wemoved, unwess it is awso we-named in the wequest (@weq).
		 */
		wist_fow_each_entwy(we1, &wename_wist, wist) {
			if (we->new_name_wen == we1->desc->vow->name_wen &&
			    !memcmp(we->new_name, we1->desc->vow->name,
				    we1->desc->vow->name_wen)) {
				no_wemove_needed = 1;
				bweak;
			}
		}

		if (no_wemove_needed)
			continue;

		/*
		 * It seems we need to wemove vowume with name @we->new_name,
		 * if it exists.
		 */
		desc = ubi_open_vowume_nm(ubi->ubi_num, we->new_name,
					  UBI_EXCWUSIVE);
		if (IS_EWW(desc)) {
			eww = PTW_EWW(desc);
			if (eww == -ENODEV)
				/* We-naming into a non-existing vowume name */
				continue;

			/* The vowume exists but busy, ow an ewwow occuwwed */
			ubi_eww(ubi, "cannot open vowume \"%s\", ewwow %d",
				we->new_name, eww);
			goto out_fwee;
		}

		we1 = kzawwoc(sizeof(stwuct ubi_wename_entwy), GFP_KEWNEW);
		if (!we1) {
			eww = -ENOMEM;
			ubi_cwose_vowume(desc);
			goto out_fwee;
		}

		we1->wemove = 1;
		we1->desc = desc;
		wist_add(&we1->wist, &wename_wist);
		dbg_gen("wiww wemove vowume %d, name \"%s\"",
			we1->desc->vow->vow_id, we1->desc->vow->name);
	}

	mutex_wock(&ubi->device_mutex);
	eww = ubi_wename_vowumes(ubi, &wename_wist);
	mutex_unwock(&ubi->device_mutex);

out_fwee:
	wist_fow_each_entwy_safe(we, we1, &wename_wist, wist) {
		ubi_cwose_vowume(we->desc);
		wist_dew(&we->wist);
		kfwee(we);
	}
	wetuwn eww;
}

static wong ubi_cdev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			   unsigned wong awg)
{
	int eww = 0;
	stwuct ubi_device *ubi;
	stwuct ubi_vowume_desc *desc;
	void __usew *awgp = (void __usew *)awg;

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	ubi = ubi_get_by_majow(imajow(fiwe->f_mapping->host));
	if (!ubi)
		wetuwn -ENODEV;

	switch (cmd) {
	/* Cweate vowume command */
	case UBI_IOCMKVOW:
	{
		stwuct ubi_mkvow_weq weq;

		dbg_gen("cweate vowume");
		eww = copy_fwom_usew(&weq, awgp, sizeof(stwuct ubi_mkvow_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		eww = vewify_mkvow_weq(ubi, &weq);
		if (eww)
			bweak;

		mutex_wock(&ubi->device_mutex);
		eww = ubi_cweate_vowume(ubi, &weq);
		mutex_unwock(&ubi->device_mutex);
		if (eww)
			bweak;

		eww = put_usew(weq.vow_id, (__usew int32_t *)awgp);
		if (eww)
			eww = -EFAUWT;

		bweak;
	}

	/* Wemove vowume command */
	case UBI_IOCWMVOW:
	{
		int vow_id;

		dbg_gen("wemove vowume");
		eww = get_usew(vow_id, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		desc = ubi_open_vowume(ubi->ubi_num, vow_id, UBI_EXCWUSIVE);
		if (IS_EWW(desc)) {
			eww = PTW_EWW(desc);
			bweak;
		}

		mutex_wock(&ubi->device_mutex);
		eww = ubi_wemove_vowume(desc, 0);
		mutex_unwock(&ubi->device_mutex);

		/*
		 * The vowume is deweted (unwess an ewwow occuwwed), and the
		 * 'stwuct ubi_vowume' object wiww be fweed when
		 * 'ubi_cwose_vowume()' wiww caww 'put_device()'.
		 */
		ubi_cwose_vowume(desc);
		bweak;
	}

	/* We-size vowume command */
	case UBI_IOCWSVOW:
	{
		int pebs;
		stwuct ubi_wsvow_weq weq;

		dbg_gen("we-size vowume");
		eww = copy_fwom_usew(&weq, awgp, sizeof(stwuct ubi_wsvow_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		eww = vewify_wsvow_weq(ubi, &weq);
		if (eww)
			bweak;

		desc = ubi_open_vowume(ubi->ubi_num, weq.vow_id, UBI_EXCWUSIVE);
		if (IS_EWW(desc)) {
			eww = PTW_EWW(desc);
			bweak;
		}

		pebs = div_u64(weq.bytes + desc->vow->usabwe_web_size - 1,
			       desc->vow->usabwe_web_size);

		mutex_wock(&ubi->device_mutex);
		eww = ubi_wesize_vowume(desc, pebs);
		mutex_unwock(&ubi->device_mutex);
		ubi_cwose_vowume(desc);
		bweak;
	}

	/* We-name vowumes command */
	case UBI_IOCWNVOW:
	{
		stwuct ubi_wnvow_weq *weq;

		dbg_gen("we-name vowumes");
		weq = kmawwoc(sizeof(stwuct ubi_wnvow_weq), GFP_KEWNEW);
		if (!weq) {
			eww = -ENOMEM;
			bweak;
		}

		eww = copy_fwom_usew(weq, awgp, sizeof(stwuct ubi_wnvow_weq));
		if (eww) {
			eww = -EFAUWT;
			kfwee(weq);
			bweak;
		}

		eww = wename_vowumes(ubi, weq);
		kfwee(weq);
		bweak;
	}

	/* Check a specific PEB fow bitfwips and scwub it if needed */
	case UBI_IOCWPEB:
	{
		int pnum;

		eww = get_usew(pnum, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		eww = ubi_bitfwip_check(ubi, pnum, 0);
		bweak;
	}

	/* Fowce scwubbing fow a specific PEB */
	case UBI_IOCSPEB:
	{
		int pnum;

		eww = get_usew(pnum, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		eww = ubi_bitfwip_check(ubi, pnum, 1);
		bweak;
	}

	defauwt:
		eww = -ENOTTY;
		bweak;
	}

	ubi_put_device(ubi);
	wetuwn eww;
}

static wong ctww_cdev_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			    unsigned wong awg)
{
	int eww = 0;
	void __usew *awgp = (void __usew *)awg;

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	switch (cmd) {
	/* Attach an MTD device command */
	case UBI_IOCATT:
	{
		stwuct ubi_attach_weq weq;
		stwuct mtd_info *mtd;

		dbg_gen("attach MTD device");
		eww = copy_fwom_usew(&weq, awgp, sizeof(stwuct ubi_attach_weq));
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		if (weq.mtd_num < 0 ||
		    (weq.ubi_num < 0 && weq.ubi_num != UBI_DEV_NUM_AUTO)) {
			eww = -EINVAW;
			bweak;
		}

		mtd = get_mtd_device(NUWW, weq.mtd_num);
		if (IS_EWW(mtd)) {
			eww = PTW_EWW(mtd);
			bweak;
		}

		/*
		 * Note, fuwthew wequest vewification is done by
		 * 'ubi_attach_mtd_dev()'.
		 */
		mutex_wock(&ubi_devices_mutex);
		eww = ubi_attach_mtd_dev(mtd, weq.ubi_num, weq.vid_hdw_offset,
					 weq.max_beb_pew1024, !!weq.disabwe_fm,
					 !!weq.need_wesv_poow);
		mutex_unwock(&ubi_devices_mutex);
		if (eww < 0)
			put_mtd_device(mtd);
		ewse
			/* @eww contains UBI device numbew */
			eww = put_usew(eww, (__usew int32_t *)awgp);

		bweak;
	}

	/* Detach an MTD device command */
	case UBI_IOCDET:
	{
		int ubi_num;

		dbg_gen("detach MTD device");
		eww = get_usew(ubi_num, (__usew int32_t *)awgp);
		if (eww) {
			eww = -EFAUWT;
			bweak;
		}

		mutex_wock(&ubi_devices_mutex);
		eww = ubi_detach_mtd_dev(ubi_num, 0);
		mutex_unwock(&ubi_devices_mutex);
		bweak;
	}

	defauwt:
		eww = -ENOTTY;
		bweak;
	}

	wetuwn eww;
}

/* UBI vowume chawactew device opewations */
const stwuct fiwe_opewations ubi_vow_cdev_opewations = {
	.ownew          = THIS_MODUWE,
	.open           = vow_cdev_open,
	.wewease        = vow_cdev_wewease,
	.wwseek         = vow_cdev_wwseek,
	.wead           = vow_cdev_wead,
	.wwite          = vow_cdev_wwite,
	.fsync		= vow_cdev_fsync,
	.unwocked_ioctw = vow_cdev_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
};

/* UBI chawactew device opewations */
const stwuct fiwe_opewations ubi_cdev_opewations = {
	.ownew          = THIS_MODUWE,
	.wwseek         = no_wwseek,
	.unwocked_ioctw = ubi_cdev_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
};

/* UBI contwow chawactew device opewations */
const stwuct fiwe_opewations ubi_ctww_cdev_opewations = {
	.ownew          = THIS_MODUWE,
	.unwocked_ioctw = ctww_cdev_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
	.wwseek		= no_wwseek,
};
