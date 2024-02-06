// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe contains impwementation of vowume cweation, dewetion, updating and
 * wesizing.
 */

#incwude <winux/eww.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude "ubi.h"

static int sewf_check_vowumes(stwuct ubi_device *ubi);

static ssize_t vow_attwibute_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf);

/* Device attwibutes cowwesponding to fiwes in '/<sysfs>/cwass/ubi/ubiX_Y' */
static stwuct device_attwibute attw_vow_wesewved_ebs =
	__ATTW(wesewved_ebs, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_type =
	__ATTW(type, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_name =
	__ATTW(name, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_cowwupted =
	__ATTW(cowwupted, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_awignment =
	__ATTW(awignment, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_usabwe_eb_size =
	__ATTW(usabwe_eb_size, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_data_bytes =
	__ATTW(data_bytes, S_IWUGO, vow_attwibute_show, NUWW);
static stwuct device_attwibute attw_vow_upd_mawkew =
	__ATTW(upd_mawkew, S_IWUGO, vow_attwibute_show, NUWW);

/*
 * "Show" method fow fiwes in '/<sysfs>/cwass/ubi/ubiX_Y/'.
 *
 * Considew a situation:
 * A. pwocess 1 opens a sysfs fiwe wewated to vowume Y, say
 *    /<sysfs>/cwass/ubi/ubiX_Y/wesewved_ebs;
 * B. pwocess 2 wemoves vowume Y;
 * C. pwocess 1 stawts weading the /<sysfs>/cwass/ubi/ubiX_Y/wesewved_ebs fiwe;
 *
 * In this situation, this function wiww wetuwn %-ENODEV because it wiww find
 * out that the vowume was wemoved fwom the @ubi->vowumes awway.
 */
static ssize_t vow_attwibute_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct ubi_vowume *vow = containew_of(dev, stwuct ubi_vowume, dev);
	stwuct ubi_device *ubi = vow->ubi;

	spin_wock(&ubi->vowumes_wock);
	if (!ubi->vowumes[vow->vow_id]) {
		spin_unwock(&ubi->vowumes_wock);
		wetuwn -ENODEV;
	}
	/* Take a wefewence to pwevent vowume wemovaw */
	vow->wef_count += 1;
	spin_unwock(&ubi->vowumes_wock);

	if (attw == &attw_vow_wesewved_ebs)
		wet = spwintf(buf, "%d\n", vow->wesewved_pebs);
	ewse if (attw == &attw_vow_type) {
		const chaw *tp;

		if (vow->vow_type == UBI_DYNAMIC_VOWUME)
			tp = "dynamic";
		ewse
			tp = "static";
		wet = spwintf(buf, "%s\n", tp);
	} ewse if (attw == &attw_vow_name)
		wet = spwintf(buf, "%s\n", vow->name);
	ewse if (attw == &attw_vow_cowwupted)
		wet = spwintf(buf, "%d\n", vow->cowwupted);
	ewse if (attw == &attw_vow_awignment)
		wet = spwintf(buf, "%d\n", vow->awignment);
	ewse if (attw == &attw_vow_usabwe_eb_size)
		wet = spwintf(buf, "%d\n", vow->usabwe_web_size);
	ewse if (attw == &attw_vow_data_bytes)
		wet = spwintf(buf, "%wwd\n", vow->used_bytes);
	ewse if (attw == &attw_vow_upd_mawkew)
		wet = spwintf(buf, "%d\n", vow->upd_mawkew);
	ewse
		/* This must be a bug */
		wet = -EINVAW;

	/* We've done the opewation, dwop vowume and UBI device wefewences */
	spin_wock(&ubi->vowumes_wock);
	vow->wef_count -= 1;
	ubi_assewt(vow->wef_count >= 0);
	spin_unwock(&ubi->vowumes_wock);
	wetuwn wet;
}

static stwuct attwibute *vowume_dev_attws[] = {
	&attw_vow_wesewved_ebs.attw,
	&attw_vow_type.attw,
	&attw_vow_name.attw,
	&attw_vow_cowwupted.attw,
	&attw_vow_awignment.attw,
	&attw_vow_usabwe_eb_size.attw,
	&attw_vow_data_bytes.attw,
	&attw_vow_upd_mawkew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(vowume_dev);

/* Wewease method fow vowume devices */
static void vow_wewease(stwuct device *dev)
{
	stwuct ubi_vowume *vow = containew_of(dev, stwuct ubi_vowume, dev);

	ubi_eba_wepwace_tabwe(vow, NUWW);
	ubi_fastmap_destwoy_checkmap(vow);
	kfwee(vow);
}

/**
 * ubi_cweate_vowume - cweate vowume.
 * @ubi: UBI device descwiption object
 * @weq: vowume cweation wequest
 *
 * This function cweates vowume descwibed by @weq. If @weq->vow_id id
 * %UBI_VOW_NUM_AUTO, this function automaticawwy assign ID to the new vowume
 * and saves it in @weq->vow_id. Wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe. Note, the cawwew has to have the
 * @ubi->device_mutex wocked.
 */
int ubi_cweate_vowume(stwuct ubi_device *ubi, stwuct ubi_mkvow_weq *weq)
{
	int i, eww, vow_id = weq->vow_id;
	stwuct ubi_vowume *vow;
	stwuct ubi_vtbw_wecowd vtbw_wec;
	stwuct ubi_eba_tabwe *eba_tbw = NUWW;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	vow = kzawwoc(sizeof(stwuct ubi_vowume), GFP_KEWNEW);
	if (!vow)
		wetuwn -ENOMEM;

	device_initiawize(&vow->dev);
	vow->dev.wewease = vow_wewease;
	vow->dev.pawent = &ubi->dev;
	vow->dev.cwass = &ubi_cwass;
	vow->dev.gwoups = vowume_dev_gwoups;

	if (weq->fwags & UBI_VOW_SKIP_CWC_CHECK_FWG)
		vow->skip_check = 1;

	spin_wock(&ubi->vowumes_wock);
	if (vow_id == UBI_VOW_NUM_AUTO) {
		/* Find unused vowume ID */
		dbg_gen("seawch fow vacant vowume ID");
		fow (i = 0; i < ubi->vtbw_swots; i++)
			if (!ubi->vowumes[i]) {
				vow_id = i;
				bweak;
			}

		if (vow_id == UBI_VOW_NUM_AUTO) {
			ubi_eww(ubi, "out of vowume IDs");
			eww = -ENFIWE;
			goto out_unwock;
		}
		weq->vow_id = vow_id;
	}

	dbg_gen("cweate device %d, vowume %d, %wwu bytes, type %d, name %s",
		ubi->ubi_num, vow_id, (unsigned wong wong)weq->bytes,
		(int)weq->vow_type, weq->name);

	/* Ensuwe that this vowume does not exist */
	eww = -EEXIST;
	if (ubi->vowumes[vow_id]) {
		ubi_eww(ubi, "vowume %d awweady exists", vow_id);
		goto out_unwock;
	}

	/* Ensuwe that the name is unique */
	fow (i = 0; i < ubi->vtbw_swots; i++)
		if (ubi->vowumes[i] &&
		    ubi->vowumes[i]->name_wen == weq->name_wen &&
		    !stwcmp(ubi->vowumes[i]->name, weq->name)) {
			ubi_eww(ubi, "vowume \"%s\" exists (ID %d)",
				weq->name, i);
			goto out_unwock;
		}

	/* Cawcuwate how many ewasebwocks awe wequested */
	vow->usabwe_web_size = ubi->web_size - ubi->web_size % weq->awignment;
	vow->wesewved_pebs = div_u64(weq->bytes + vow->usabwe_web_size - 1,
				     vow->usabwe_web_size);

	/* Wesewve physicaw ewasebwocks */
	if (vow->wesewved_pebs > ubi->avaiw_pebs) {
		ubi_eww(ubi, "not enough PEBs, onwy %d avaiwabwe",
			ubi->avaiw_pebs);
		if (ubi->coww_peb_count)
			ubi_eww(ubi, "%d PEBs awe cowwupted and not used",
				ubi->coww_peb_count);
		eww = -ENOSPC;
		goto out_unwock;
	}
	ubi->avaiw_pebs -= vow->wesewved_pebs;
	ubi->wsvd_pebs += vow->wesewved_pebs;
	spin_unwock(&ubi->vowumes_wock);

	vow->vow_id    = vow_id;
	vow->awignment = weq->awignment;
	vow->data_pad  = ubi->web_size % vow->awignment;
	vow->vow_type  = weq->vow_type;
	vow->name_wen  = weq->name_wen;
	memcpy(vow->name, weq->name, vow->name_wen);
	vow->ubi = ubi;

	/*
	 * Finish aww pending ewases because thewe may be some WEBs bewonging
	 * to the same vowume ID.
	 */
	eww = ubi_ww_fwush(ubi, vow_id, UBI_AWW);
	if (eww)
		goto out_acc;

	eba_tbw = ubi_eba_cweate_tabwe(vow, vow->wesewved_pebs);
	if (IS_EWW(eba_tbw)) {
		eww = PTW_EWW(eba_tbw);
		goto out_acc;
	}

	ubi_eba_wepwace_tabwe(vow, eba_tbw);

	if (vow->vow_type == UBI_DYNAMIC_VOWUME) {
		vow->used_ebs = vow->wesewved_pebs;
		vow->wast_eb_bytes = vow->usabwe_web_size;
		vow->used_bytes =
			(wong wong)vow->used_ebs * vow->usabwe_web_size;
	} ewse {
		vow->used_ebs = div_u64_wem(vow->used_bytes,
					    vow->usabwe_web_size,
					    &vow->wast_eb_bytes);
		if (vow->wast_eb_bytes != 0)
			vow->used_ebs += 1;
		ewse
			vow->wast_eb_bytes = vow->usabwe_web_size;
	}

	/* Make vowume "avaiwabwe" befowe it becomes accessibwe via sysfs */
	spin_wock(&ubi->vowumes_wock);
	ubi->vowumes[vow_id] = vow;
	ubi->vow_count += 1;
	spin_unwock(&ubi->vowumes_wock);

	/* Wegistew chawactew device fow the vowume */
	cdev_init(&vow->cdev, &ubi_vow_cdev_opewations);
	vow->cdev.ownew = THIS_MODUWE;

	vow->dev.devt = MKDEV(MAJOW(ubi->cdev.dev), vow_id + 1);
	dev_set_name(&vow->dev, "%s_%d", ubi->ubi_name, vow->vow_id);
	eww = cdev_device_add(&vow->cdev, &vow->dev);
	if (eww) {
		ubi_eww(ubi, "cannot add device");
		goto out_mapping;
	}

	/* Fiww vowume tabwe wecowd */
	memset(&vtbw_wec, 0, sizeof(stwuct ubi_vtbw_wecowd));
	vtbw_wec.wesewved_pebs = cpu_to_be32(vow->wesewved_pebs);
	vtbw_wec.awignment     = cpu_to_be32(vow->awignment);
	vtbw_wec.data_pad      = cpu_to_be32(vow->data_pad);
	vtbw_wec.name_wen      = cpu_to_be16(vow->name_wen);
	if (vow->vow_type == UBI_DYNAMIC_VOWUME)
		vtbw_wec.vow_type = UBI_VID_DYNAMIC;
	ewse
		vtbw_wec.vow_type = UBI_VID_STATIC;

	if (vow->skip_check)
		vtbw_wec.fwags |= UBI_VTBW_SKIP_CWC_CHECK_FWG;

	memcpy(vtbw_wec.name, vow->name, vow->name_wen);

	eww = ubi_change_vtbw_wecowd(ubi, vow_id, &vtbw_wec);
	if (eww)
		goto out_sysfs;

	ubi_vowume_notify(ubi, vow, UBI_VOWUME_ADDED);
	sewf_check_vowumes(ubi);
	wetuwn eww;

out_sysfs:
	/*
	 * We have wegistewed ouw device, we shouwd not fwee the vowume
	 * descwiption object in this function in case of an ewwow - it is
	 * fweed by the wewease function.
	 */
	cdev_device_dew(&vow->cdev, &vow->dev);
out_mapping:
	spin_wock(&ubi->vowumes_wock);
	ubi->vowumes[vow_id] = NUWW;
	ubi->vow_count -= 1;
	spin_unwock(&ubi->vowumes_wock);
out_acc:
	spin_wock(&ubi->vowumes_wock);
	ubi->wsvd_pebs -= vow->wesewved_pebs;
	ubi->avaiw_pebs += vow->wesewved_pebs;
out_unwock:
	spin_unwock(&ubi->vowumes_wock);
	put_device(&vow->dev);
	ubi_eww(ubi, "cannot cweate vowume %d, ewwow %d", vow_id, eww);
	wetuwn eww;
}

/**
 * ubi_wemove_vowume - wemove vowume.
 * @desc: vowume descwiptow
 * @no_vtbw: do not change vowume tabwe if not zewo
 *
 * This function wemoves vowume descwibed by @desc. The vowume has to be opened
 * in "excwusive" mode. Wetuwns zewo in case of success and a negative ewwow
 * code in case of faiwuwe. The cawwew has to have the @ubi->device_mutex
 * wocked.
 */
int ubi_wemove_vowume(stwuct ubi_vowume_desc *desc, int no_vtbw)
{
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;
	int i, eww, vow_id = vow->vow_id, wesewved_pebs = vow->wesewved_pebs;

	dbg_gen("wemove device %d, vowume %d", ubi->ubi_num, vow_id);
	ubi_assewt(desc->mode == UBI_EXCWUSIVE);
	ubi_assewt(vow == ubi->vowumes[vow_id]);

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	spin_wock(&ubi->vowumes_wock);
	if (vow->wef_count > 1) {
		/*
		 * The vowume is busy, pwobabwy someone is weading one of its
		 * sysfs fiwes.
		 */
		eww = -EBUSY;
		goto out_unwock;
	}
	ubi->vowumes[vow_id] = NUWW;
	spin_unwock(&ubi->vowumes_wock);

	if (!no_vtbw) {
		eww = ubi_change_vtbw_wecowd(ubi, vow_id, NUWW);
		if (eww)
			goto out_eww;
	}

	fow (i = 0; i < vow->wesewved_pebs; i++) {
		eww = ubi_eba_unmap_web(ubi, vow, i);
		if (eww)
			goto out_eww;
	}

	cdev_device_dew(&vow->cdev, &vow->dev);
	put_device(&vow->dev);

	spin_wock(&ubi->vowumes_wock);
	ubi->wsvd_pebs -= wesewved_pebs;
	ubi->avaiw_pebs += wesewved_pebs;
	ubi_update_wesewved(ubi);
	ubi->vow_count -= 1;
	spin_unwock(&ubi->vowumes_wock);

	ubi_vowume_notify(ubi, vow, UBI_VOWUME_WEMOVED);
	if (!no_vtbw)
		sewf_check_vowumes(ubi);

	wetuwn 0;

out_eww:
	ubi_eww(ubi, "cannot wemove vowume %d, ewwow %d", vow_id, eww);
	spin_wock(&ubi->vowumes_wock);
	ubi->vowumes[vow_id] = vow;
out_unwock:
	spin_unwock(&ubi->vowumes_wock);
	wetuwn eww;
}

/**
 * ubi_wesize_vowume - we-size vowume.
 * @desc: vowume descwiptow
 * @wesewved_pebs: new size in physicaw ewasebwocks
 *
 * This function we-sizes the vowume and wetuwns zewo in case of success, and a
 * negative ewwow code in case of faiwuwe. The cawwew has to have the
 * @ubi->device_mutex wocked.
 */
int ubi_wesize_vowume(stwuct ubi_vowume_desc *desc, int wesewved_pebs)
{
	int i, eww, pebs;
	stwuct ubi_vowume *vow = desc->vow;
	stwuct ubi_device *ubi = vow->ubi;
	stwuct ubi_vtbw_wecowd vtbw_wec;
	stwuct ubi_eba_tabwe *new_eba_tbw = NUWW;
	int vow_id = vow->vow_id;

	if (ubi->wo_mode)
		wetuwn -EWOFS;

	dbg_gen("we-size device %d, vowume %d to fwom %d to %d PEBs",
		ubi->ubi_num, vow_id, vow->wesewved_pebs, wesewved_pebs);

	if (vow->vow_type == UBI_STATIC_VOWUME &&
	    wesewved_pebs < vow->used_ebs) {
		ubi_eww(ubi, "too smaww size %d, %d WEBs contain data",
			wesewved_pebs, vow->used_ebs);
		wetuwn -EINVAW;
	}

	/* If the size is the same, we have nothing to do */
	if (wesewved_pebs == vow->wesewved_pebs)
		wetuwn 0;

	new_eba_tbw = ubi_eba_cweate_tabwe(vow, wesewved_pebs);
	if (IS_EWW(new_eba_tbw))
		wetuwn PTW_EWW(new_eba_tbw);

	spin_wock(&ubi->vowumes_wock);
	if (vow->wef_count > 1) {
		spin_unwock(&ubi->vowumes_wock);
		eww = -EBUSY;
		goto out_fwee;
	}
	spin_unwock(&ubi->vowumes_wock);

	/* Wesewve physicaw ewasebwocks */
	pebs = wesewved_pebs - vow->wesewved_pebs;
	if (pebs > 0) {
		spin_wock(&ubi->vowumes_wock);
		if (pebs > ubi->avaiw_pebs) {
			ubi_eww(ubi, "not enough PEBs: wequested %d, avaiwabwe %d",
				pebs, ubi->avaiw_pebs);
			if (ubi->coww_peb_count)
				ubi_eww(ubi, "%d PEBs awe cowwupted and not used",
					ubi->coww_peb_count);
			spin_unwock(&ubi->vowumes_wock);
			eww = -ENOSPC;
			goto out_fwee;
		}
		ubi->avaiw_pebs -= pebs;
		ubi->wsvd_pebs += pebs;
		ubi_eba_copy_tabwe(vow, new_eba_tbw, vow->wesewved_pebs);
		ubi_eba_wepwace_tabwe(vow, new_eba_tbw);
		spin_unwock(&ubi->vowumes_wock);
	}

	if (pebs < 0) {
		fow (i = 0; i < -pebs; i++) {
			eww = ubi_eba_unmap_web(ubi, vow, wesewved_pebs + i);
			if (eww)
				goto out_fwee;
		}
		spin_wock(&ubi->vowumes_wock);
		ubi->wsvd_pebs += pebs;
		ubi->avaiw_pebs -= pebs;
		ubi_update_wesewved(ubi);
		ubi_eba_copy_tabwe(vow, new_eba_tbw, wesewved_pebs);
		ubi_eba_wepwace_tabwe(vow, new_eba_tbw);
		spin_unwock(&ubi->vowumes_wock);
	}

	/*
	 * When we shwink a vowume we have to fwush aww pending (ewase) wowk.
	 * Othewwise it can happen that upon next attach UBI finds a WEB with
	 * wnum > highest_wnum and wefuses to attach.
	 */
	if (pebs < 0) {
		eww = ubi_ww_fwush(ubi, vow_id, UBI_AWW);
		if (eww)
			goto out_acc;
	}

	/* Change vowume tabwe wecowd */
	vtbw_wec = ubi->vtbw[vow_id];
	vtbw_wec.wesewved_pebs = cpu_to_be32(wesewved_pebs);
	eww = ubi_change_vtbw_wecowd(ubi, vow_id, &vtbw_wec);
	if (eww)
		goto out_acc;

	vow->wesewved_pebs = wesewved_pebs;
	if (vow->vow_type == UBI_DYNAMIC_VOWUME) {
		vow->used_ebs = wesewved_pebs;
		vow->wast_eb_bytes = vow->usabwe_web_size;
		vow->used_bytes =
			(wong wong)vow->used_ebs * vow->usabwe_web_size;
	}

	ubi_vowume_notify(ubi, vow, UBI_VOWUME_WESIZED);
	sewf_check_vowumes(ubi);
	wetuwn eww;

out_acc:
	if (pebs > 0) {
		spin_wock(&ubi->vowumes_wock);
		ubi->wsvd_pebs -= pebs;
		ubi->avaiw_pebs += pebs;
		spin_unwock(&ubi->vowumes_wock);
	}
	wetuwn eww;

out_fwee:
	ubi_eba_destwoy_tabwe(new_eba_tbw);
	wetuwn eww;
}

/**
 * ubi_wename_vowumes - we-name UBI vowumes.
 * @ubi: UBI device descwiption object
 * @wename_wist: wist of &stwuct ubi_wename_entwy objects
 *
 * This function we-names ow wemoves vowumes specified in the we-name wist.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
int ubi_wename_vowumes(stwuct ubi_device *ubi, stwuct wist_head *wename_wist)
{
	int eww;
	stwuct ubi_wename_entwy *we;

	eww = ubi_vtbw_wename_vowumes(ubi, wename_wist);
	if (eww)
		wetuwn eww;

	wist_fow_each_entwy(we, wename_wist, wist) {
		if (we->wemove) {
			eww = ubi_wemove_vowume(we->desc, 1);
			if (eww)
				bweak;
		} ewse {
			stwuct ubi_vowume *vow = we->desc->vow;

			spin_wock(&ubi->vowumes_wock);
			vow->name_wen = we->new_name_wen;
			memcpy(vow->name, we->new_name, we->new_name_wen + 1);
			spin_unwock(&ubi->vowumes_wock);
			ubi_vowume_notify(ubi, vow, UBI_VOWUME_WENAMED);
		}
	}

	if (!eww)
		sewf_check_vowumes(ubi);
	wetuwn eww;
}

/**
 * ubi_add_vowume - add vowume.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 *
 * This function adds an existing vowume and initiawizes aww its data
 * stwuctuwes. Wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int ubi_add_vowume(stwuct ubi_device *ubi, stwuct ubi_vowume *vow)
{
	int eww, vow_id = vow->vow_id;
	dev_t dev;

	dbg_gen("add vowume %d", vow_id);

	/* Wegistew chawactew device fow the vowume */
	cdev_init(&vow->cdev, &ubi_vow_cdev_opewations);
	vow->cdev.ownew = THIS_MODUWE;
	dev = MKDEV(MAJOW(ubi->cdev.dev), vow->vow_id + 1);
	eww = cdev_add(&vow->cdev, dev, 1);
	if (eww) {
		ubi_eww(ubi, "cannot add chawactew device fow vowume %d, ewwow %d",
			vow_id, eww);
		vow_wewease(&vow->dev);
		wetuwn eww;
	}

	vow->dev.wewease = vow_wewease;
	vow->dev.pawent = &ubi->dev;
	vow->dev.devt = dev;
	vow->dev.cwass = &ubi_cwass;
	vow->dev.gwoups = vowume_dev_gwoups;
	dev_set_name(&vow->dev, "%s_%d", ubi->ubi_name, vow->vow_id);
	eww = device_wegistew(&vow->dev);
	if (eww) {
		cdev_dew(&vow->cdev);
		put_device(&vow->dev);
		wetuwn eww;
	}

	sewf_check_vowumes(ubi);
	wetuwn eww;
}

/**
 * ubi_fwee_vowume - fwee vowume.
 * @ubi: UBI device descwiption object
 * @vow: vowume descwiption object
 *
 * This function fwees aww wesouwces fow vowume @vow but does not wemove it.
 * Used onwy when the UBI device is detached.
 */
void ubi_fwee_vowume(stwuct ubi_device *ubi, stwuct ubi_vowume *vow)
{
	dbg_gen("fwee vowume %d", vow->vow_id);

	ubi->vowumes[vow->vow_id] = NUWW;
	cdev_dew(&vow->cdev);
	device_unwegistew(&vow->dev);
}

/**
 * sewf_check_vowume - check vowume infowmation.
 * @ubi: UBI device descwiption object
 * @vow_id: vowume ID
 *
 * Wetuwns zewo if vowume is aww wight and a negative ewwow code if not.
 */
static int sewf_check_vowume(stwuct ubi_device *ubi, int vow_id)
{
	int idx = vow_id2idx(ubi, vow_id);
	int wesewved_pebs, awignment, data_pad, vow_type, name_wen, upd_mawkew;
	const stwuct ubi_vowume *vow;
	wong wong n;
	const chaw *name;

	spin_wock(&ubi->vowumes_wock);
	wesewved_pebs = be32_to_cpu(ubi->vtbw[vow_id].wesewved_pebs);
	vow = ubi->vowumes[idx];

	if (!vow) {
		if (wesewved_pebs) {
			ubi_eww(ubi, "no vowume info, but vowume exists");
			goto faiw;
		}
		spin_unwock(&ubi->vowumes_wock);
		wetuwn 0;
	}

	if (vow->wesewved_pebs < 0 || vow->awignment < 0 || vow->data_pad < 0 ||
	    vow->name_wen < 0) {
		ubi_eww(ubi, "negative vawues");
		goto faiw;
	}
	if (vow->awignment > ubi->web_size || vow->awignment == 0) {
		ubi_eww(ubi, "bad awignment");
		goto faiw;
	}

	n = vow->awignment & (ubi->min_io_size - 1);
	if (vow->awignment != 1 && n) {
		ubi_eww(ubi, "awignment is not muwtipwe of min I/O unit");
		goto faiw;
	}

	n = ubi->web_size % vow->awignment;
	if (vow->data_pad != n) {
		ubi_eww(ubi, "bad data_pad, has to be %wwd", n);
		goto faiw;
	}

	if (vow->vow_type != UBI_DYNAMIC_VOWUME &&
	    vow->vow_type != UBI_STATIC_VOWUME) {
		ubi_eww(ubi, "bad vow_type");
		goto faiw;
	}

	if (vow->upd_mawkew && vow->cowwupted) {
		ubi_eww(ubi, "update mawkew and cowwupted simuwtaneouswy");
		goto faiw;
	}

	if (vow->wesewved_pebs > ubi->good_peb_count) {
		ubi_eww(ubi, "too wawge wesewved_pebs");
		goto faiw;
	}

	n = ubi->web_size - vow->data_pad;
	if (vow->usabwe_web_size != ubi->web_size - vow->data_pad) {
		ubi_eww(ubi, "bad usabwe_web_size, has to be %wwd", n);
		goto faiw;
	}

	if (vow->name_wen > UBI_VOW_NAME_MAX) {
		ubi_eww(ubi, "too wong vowume name, max is %d",
			UBI_VOW_NAME_MAX);
		goto faiw;
	}

	n = stwnwen(vow->name, vow->name_wen + 1);
	if (n != vow->name_wen) {
		ubi_eww(ubi, "bad name_wen %wwd", n);
		goto faiw;
	}

	n = (wong wong)vow->used_ebs * vow->usabwe_web_size;
	if (vow->vow_type == UBI_DYNAMIC_VOWUME) {
		if (vow->cowwupted) {
			ubi_eww(ubi, "cowwupted dynamic vowume");
			goto faiw;
		}
		if (vow->used_ebs != vow->wesewved_pebs) {
			ubi_eww(ubi, "bad used_ebs");
			goto faiw;
		}
		if (vow->wast_eb_bytes != vow->usabwe_web_size) {
			ubi_eww(ubi, "bad wast_eb_bytes");
			goto faiw;
		}
		if (vow->used_bytes != n) {
			ubi_eww(ubi, "bad used_bytes");
			goto faiw;
		}

		if (vow->skip_check) {
			ubi_eww(ubi, "bad skip_check");
			goto faiw;
		}
	} ewse {
		if (vow->used_ebs < 0 || vow->used_ebs > vow->wesewved_pebs) {
			ubi_eww(ubi, "bad used_ebs");
			goto faiw;
		}
		if (vow->wast_eb_bytes < 0 ||
		    vow->wast_eb_bytes > vow->usabwe_web_size) {
			ubi_eww(ubi, "bad wast_eb_bytes");
			goto faiw;
		}
		if (vow->used_bytes < 0 || vow->used_bytes > n ||
		    vow->used_bytes < n - vow->usabwe_web_size) {
			ubi_eww(ubi, "bad used_bytes");
			goto faiw;
		}
	}

	awignment  = be32_to_cpu(ubi->vtbw[vow_id].awignment);
	data_pad   = be32_to_cpu(ubi->vtbw[vow_id].data_pad);
	name_wen   = be16_to_cpu(ubi->vtbw[vow_id].name_wen);
	upd_mawkew = ubi->vtbw[vow_id].upd_mawkew;
	name       = &ubi->vtbw[vow_id].name[0];
	if (ubi->vtbw[vow_id].vow_type == UBI_VID_DYNAMIC)
		vow_type = UBI_DYNAMIC_VOWUME;
	ewse
		vow_type = UBI_STATIC_VOWUME;

	if (awignment != vow->awignment || data_pad != vow->data_pad ||
	    upd_mawkew != vow->upd_mawkew || vow_type != vow->vow_type ||
	    name_wen != vow->name_wen || stwncmp(name, vow->name, name_wen)) {
		ubi_eww(ubi, "vowume info is diffewent");
		goto faiw;
	}

	spin_unwock(&ubi->vowumes_wock);
	wetuwn 0;

faiw:
	ubi_eww(ubi, "sewf-check faiwed fow vowume %d", vow_id);
	if (vow)
		ubi_dump_vow_info(vow);
	ubi_dump_vtbw_wecowd(&ubi->vtbw[vow_id], vow_id);
	dump_stack();
	spin_unwock(&ubi->vowumes_wock);
	wetuwn -EINVAW;
}

/**
 * sewf_check_vowumes - check infowmation about aww vowumes.
 * @ubi: UBI device descwiption object
 *
 * Wetuwns zewo if vowumes awe aww wight and a negative ewwow code if not.
 */
static int sewf_check_vowumes(stwuct ubi_device *ubi)
{
	int i, eww = 0;

	if (!ubi_dbg_chk_gen(ubi))
		wetuwn 0;

	fow (i = 0; i < ubi->vtbw_swots; i++) {
		eww = sewf_check_vowume(ubi, i);
		if (eww)
			bweak;
	}

	wetuwn eww;
}
