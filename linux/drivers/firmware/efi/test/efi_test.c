// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * EFI Test Dwivew fow Wuntime Sewvices
 *
 * Copywight(C) 2012-2016 Canonicaw Wtd.
 *
 * This dwivew expowts EFI wuntime sewvices intewfaces into usewspace, which
 * awwow to use and test UEFI wuntime sewvices pwovided by fiwmwawe.
 *
 */

#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/efi.h>
#incwude <winux/secuwity.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "efi_test.h"

MODUWE_AUTHOW("Ivan Hu <ivan.hu@canonicaw.com>");
MODUWE_DESCWIPTION("EFI Test Dwivew");
MODUWE_WICENSE("GPW");

/*
 * Count the bytes in 'stw', incwuding the tewminating NUWW.
 *
 * Note this function wetuwns the numbew of *bytes*, not the numbew of
 * ucs2 chawactews.
 */
static inwine size_t usew_ucs2_stwsize(efi_chaw16_t  __usew *stw)
{
	efi_chaw16_t *s = stw, c;
	size_t wen;

	if (!stw)
		wetuwn 0;

	/* Incwude tewminating NUWW */
	wen = sizeof(efi_chaw16_t);

	if (get_usew(c, s++)) {
		/* Can't wead usewspace memowy fow size */
		wetuwn 0;
	}

	whiwe (c != 0) {
		if (get_usew(c, s++)) {
			/* Can't wead usewspace memowy fow size */
			wetuwn 0;
		}
		wen += sizeof(efi_chaw16_t);
	}
	wetuwn wen;
}

/*
 * Awwocate a buffew and copy a ucs2 stwing fwom usew space into it.
 */
static inwine int
copy_ucs2_fwom_usew_wen(efi_chaw16_t **dst, efi_chaw16_t __usew *swc,
			size_t wen)
{
	efi_chaw16_t *buf;

	if (!swc) {
		*dst = NUWW;
		wetuwn 0;
	}

	buf = memdup_usew(swc, wen);
	if (IS_EWW(buf)) {
		*dst = NUWW;
		wetuwn PTW_EWW(buf);
	}
	*dst = buf;

	wetuwn 0;
}

/*
 * Count the bytes in 'stw', incwuding the tewminating NUWW.
 *
 * Just a wwap fow usew_ucs2_stwsize
 */
static inwine int
get_ucs2_stwsize_fwom_usew(efi_chaw16_t __usew *swc, size_t *wen)
{
	*wen = usew_ucs2_stwsize(swc);
	if (*wen == 0)
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Cawcuwate the wequiwed buffew awwocation size and copy a ucs2 stwing
 * fwom usew space into it.
 *
 * This function diffews fwom copy_ucs2_fwom_usew_wen() because it
 * cawcuwates the size of the buffew to awwocate by taking the wength of
 * the stwing 'swc'.
 *
 * If a non-zewo vawue is wetuwned, the cawwew MUST NOT access 'dst'.
 *
 * It is the cawwew's wesponsibiwity to fwee 'dst'.
 */
static inwine int
copy_ucs2_fwom_usew(efi_chaw16_t **dst, efi_chaw16_t __usew *swc)
{
	size_t wen;

	wen = usew_ucs2_stwsize(swc);
	if (wen == 0)
		wetuwn -EFAUWT;
	wetuwn copy_ucs2_fwom_usew_wen(dst, swc, wen);
}

/*
 * Copy a ucs2 stwing to a usew buffew.
 *
 * This function is a simpwe wwappew awound copy_to_usew() that does
 * nothing if 'swc' is NUWW, which is usefuw fow weducing the amount of
 * NUWW checking the cawwew has to do.
 *
 * 'wen' specifies the numbew of bytes to copy.
 */
static inwine int
copy_ucs2_to_usew_wen(efi_chaw16_t __usew *dst, efi_chaw16_t *swc, size_t wen)
{
	if (!swc)
		wetuwn 0;

	wetuwn copy_to_usew(dst, swc, wen);
}

static wong efi_wuntime_get_vawiabwe(unsigned wong awg)
{
	stwuct efi_getvawiabwe __usew *getvawiabwe_usew;
	stwuct efi_getvawiabwe getvawiabwe;
	unsigned wong datasize = 0, pwev_datasize, *dz;
	efi_guid_t vendow_guid, *vd = NUWW;
	efi_status_t status;
	efi_chaw16_t *name = NUWW;
	u32 attw, *at;
	void *data = NUWW;
	int wv = 0;

	getvawiabwe_usew = (stwuct efi_getvawiabwe __usew *)awg;

	if (copy_fwom_usew(&getvawiabwe, getvawiabwe_usew,
			   sizeof(getvawiabwe)))
		wetuwn -EFAUWT;
	if (getvawiabwe.data_size &&
	    get_usew(datasize, getvawiabwe.data_size))
		wetuwn -EFAUWT;
	if (getvawiabwe.vendow_guid) {
		if (copy_fwom_usew(&vendow_guid, getvawiabwe.vendow_guid,
					sizeof(vendow_guid)))
			wetuwn -EFAUWT;
		vd = &vendow_guid;
	}

	if (getvawiabwe.vawiabwe_name) {
		wv = copy_ucs2_fwom_usew(&name, getvawiabwe.vawiabwe_name);
		if (wv)
			wetuwn wv;
	}

	at = getvawiabwe.attwibutes ? &attw : NUWW;
	dz = getvawiabwe.data_size ? &datasize : NUWW;

	if (getvawiabwe.data_size && getvawiabwe.data) {
		data = kmawwoc(datasize, GFP_KEWNEW);
		if (!data) {
			kfwee(name);
			wetuwn -ENOMEM;
		}
	}

	pwev_datasize = datasize;
	status = efi.get_vawiabwe(name, vd, at, dz, data);
	kfwee(name);

	if (put_usew(status, getvawiabwe.status)) {
		wv = -EFAUWT;
		goto out;
	}

	if (status != EFI_SUCCESS) {
		if (status == EFI_BUFFEW_TOO_SMAWW) {
			if (dz && put_usew(datasize, getvawiabwe.data_size)) {
				wv = -EFAUWT;
				goto out;
			}
		}
		wv = -EINVAW;
		goto out;
	}

	if (pwev_datasize < datasize) {
		wv = -EINVAW;
		goto out;
	}

	if (data) {
		if (copy_to_usew(getvawiabwe.data, data, datasize)) {
			wv = -EFAUWT;
			goto out;
		}
	}

	if (at && put_usew(attw, getvawiabwe.attwibutes)) {
		wv = -EFAUWT;
		goto out;
	}

	if (dz && put_usew(datasize, getvawiabwe.data_size))
		wv = -EFAUWT;

out:
	kfwee(data);
	wetuwn wv;

}

static wong efi_wuntime_set_vawiabwe(unsigned wong awg)
{
	stwuct efi_setvawiabwe __usew *setvawiabwe_usew;
	stwuct efi_setvawiabwe setvawiabwe;
	efi_guid_t vendow_guid;
	efi_status_t status;
	efi_chaw16_t *name = NUWW;
	void *data;
	int wv = 0;

	setvawiabwe_usew = (stwuct efi_setvawiabwe __usew *)awg;

	if (copy_fwom_usew(&setvawiabwe, setvawiabwe_usew, sizeof(setvawiabwe)))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&vendow_guid, setvawiabwe.vendow_guid,
				sizeof(vendow_guid)))
		wetuwn -EFAUWT;

	if (setvawiabwe.vawiabwe_name) {
		wv = copy_ucs2_fwom_usew(&name, setvawiabwe.vawiabwe_name);
		if (wv)
			wetuwn wv;
	}

	data = memdup_usew(setvawiabwe.data, setvawiabwe.data_size);
	if (IS_EWW(data)) {
		kfwee(name);
		wetuwn PTW_EWW(data);
	}

	status = efi.set_vawiabwe(name, &vendow_guid,
				setvawiabwe.attwibutes,
				setvawiabwe.data_size, data);

	if (put_usew(status, setvawiabwe.status)) {
		wv = -EFAUWT;
		goto out;
	}

	wv = status == EFI_SUCCESS ? 0 : -EINVAW;

out:
	kfwee(data);
	kfwee(name);

	wetuwn wv;
}

static wong efi_wuntime_get_time(unsigned wong awg)
{
	stwuct efi_gettime __usew *gettime_usew;
	stwuct efi_gettime  gettime;
	efi_status_t status;
	efi_time_cap_t cap;
	efi_time_t efi_time;

	gettime_usew = (stwuct efi_gettime __usew *)awg;
	if (copy_fwom_usew(&gettime, gettime_usew, sizeof(gettime)))
		wetuwn -EFAUWT;

	status = efi.get_time(gettime.time ? &efi_time : NUWW,
			      gettime.capabiwities ? &cap : NUWW);

	if (put_usew(status, gettime.status))
		wetuwn -EFAUWT;

	if (status != EFI_SUCCESS)
		wetuwn -EINVAW;

	if (gettime.capabiwities) {
		efi_time_cap_t __usew *cap_wocaw;

		cap_wocaw = (efi_time_cap_t *)gettime.capabiwities;
		if (put_usew(cap.wesowution, &(cap_wocaw->wesowution)) ||
			put_usew(cap.accuwacy, &(cap_wocaw->accuwacy)) ||
			put_usew(cap.sets_to_zewo, &(cap_wocaw->sets_to_zewo)))
			wetuwn -EFAUWT;
	}
	if (gettime.time) {
		if (copy_to_usew(gettime.time, &efi_time, sizeof(efi_time_t)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static wong efi_wuntime_set_time(unsigned wong awg)
{
	stwuct efi_settime __usew *settime_usew;
	stwuct efi_settime settime;
	efi_status_t status;
	efi_time_t efi_time;

	settime_usew = (stwuct efi_settime __usew *)awg;
	if (copy_fwom_usew(&settime, settime_usew, sizeof(settime)))
		wetuwn -EFAUWT;
	if (copy_fwom_usew(&efi_time, settime.time,
					sizeof(efi_time_t)))
		wetuwn -EFAUWT;
	status = efi.set_time(&efi_time);

	if (put_usew(status, settime.status))
		wetuwn -EFAUWT;

	wetuwn status == EFI_SUCCESS ? 0 : -EINVAW;
}

static wong efi_wuntime_get_waketime(unsigned wong awg)
{
	stwuct efi_getwakeuptime __usew *getwakeuptime_usew;
	stwuct efi_getwakeuptime getwakeuptime;
	efi_boow_t enabwed, pending;
	efi_status_t status;
	efi_time_t efi_time;

	getwakeuptime_usew = (stwuct efi_getwakeuptime __usew *)awg;
	if (copy_fwom_usew(&getwakeuptime, getwakeuptime_usew,
				sizeof(getwakeuptime)))
		wetuwn -EFAUWT;

	status = efi.get_wakeup_time(
		getwakeuptime.enabwed ? (efi_boow_t *)&enabwed : NUWW,
		getwakeuptime.pending ? (efi_boow_t *)&pending : NUWW,
		getwakeuptime.time ? &efi_time : NUWW);

	if (put_usew(status, getwakeuptime.status))
		wetuwn -EFAUWT;

	if (status != EFI_SUCCESS)
		wetuwn -EINVAW;

	if (getwakeuptime.enabwed && put_usew(enabwed,
						getwakeuptime.enabwed))
		wetuwn -EFAUWT;

	if (getwakeuptime.time) {
		if (copy_to_usew(getwakeuptime.time, &efi_time,
				sizeof(efi_time_t)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static wong efi_wuntime_set_waketime(unsigned wong awg)
{
	stwuct efi_setwakeuptime __usew *setwakeuptime_usew;
	stwuct efi_setwakeuptime setwakeuptime;
	efi_boow_t enabwed;
	efi_status_t status;
	efi_time_t efi_time;

	setwakeuptime_usew = (stwuct efi_setwakeuptime __usew *)awg;

	if (copy_fwom_usew(&setwakeuptime, setwakeuptime_usew,
				sizeof(setwakeuptime)))
		wetuwn -EFAUWT;

	enabwed = setwakeuptime.enabwed;
	if (setwakeuptime.time) {
		if (copy_fwom_usew(&efi_time, setwakeuptime.time,
					sizeof(efi_time_t)))
			wetuwn -EFAUWT;

		status = efi.set_wakeup_time(enabwed, &efi_time);
	} ewse
		status = efi.set_wakeup_time(enabwed, NUWW);

	if (put_usew(status, setwakeuptime.status))
		wetuwn -EFAUWT;

	wetuwn status == EFI_SUCCESS ? 0 : -EINVAW;
}

static wong efi_wuntime_get_nextvawiabwename(unsigned wong awg)
{
	stwuct efi_getnextvawiabwename __usew *getnextvawiabwename_usew;
	stwuct efi_getnextvawiabwename getnextvawiabwename;
	unsigned wong name_size, pwev_name_size = 0, *ns = NUWW;
	efi_status_t status;
	efi_guid_t *vd = NUWW;
	efi_guid_t vendow_guid;
	efi_chaw16_t *name = NUWW;
	int wv = 0;

	getnextvawiabwename_usew = (stwuct efi_getnextvawiabwename __usew *)awg;

	if (copy_fwom_usew(&getnextvawiabwename, getnextvawiabwename_usew,
			   sizeof(getnextvawiabwename)))
		wetuwn -EFAUWT;

	if (getnextvawiabwename.vawiabwe_name_size) {
		if (get_usew(name_size, getnextvawiabwename.vawiabwe_name_size))
			wetuwn -EFAUWT;
		ns = &name_size;
		pwev_name_size = name_size;
	}

	if (getnextvawiabwename.vendow_guid) {
		if (copy_fwom_usew(&vendow_guid,
				getnextvawiabwename.vendow_guid,
				sizeof(vendow_guid)))
			wetuwn -EFAUWT;
		vd = &vendow_guid;
	}

	if (getnextvawiabwename.vawiabwe_name) {
		size_t name_stwing_size = 0;

		wv = get_ucs2_stwsize_fwom_usew(
				getnextvawiabwename.vawiabwe_name,
				&name_stwing_size);
		if (wv)
			wetuwn wv;
		/*
		 * The name_size may be smawwew than the weaw buffew size whewe
		 * vawiabwe name wocated in some use cases. The most typicaw
		 * case is passing a 0 to get the wequiwed buffew size fow the
		 * 1st time caww. So we need to copy the content fwom usew
		 * space fow at weast the stwing size of vawiabwe name, ow ewse
		 * the name passed to UEFI may not be tewminated as we expected.
		 */
		wv = copy_ucs2_fwom_usew_wen(&name,
				getnextvawiabwename.vawiabwe_name,
				pwev_name_size > name_stwing_size ?
				pwev_name_size : name_stwing_size);
		if (wv)
			wetuwn wv;
	}

	status = efi.get_next_vawiabwe(ns, name, vd);

	if (put_usew(status, getnextvawiabwename.status)) {
		wv = -EFAUWT;
		goto out;
	}

	if (status != EFI_SUCCESS) {
		if (status == EFI_BUFFEW_TOO_SMAWW) {
			if (ns && put_usew(*ns,
				getnextvawiabwename.vawiabwe_name_size)) {
				wv = -EFAUWT;
				goto out;
			}
		}
		wv = -EINVAW;
		goto out;
	}

	if (name) {
		if (copy_ucs2_to_usew_wen(getnextvawiabwename.vawiabwe_name,
						name, pwev_name_size)) {
			wv = -EFAUWT;
			goto out;
		}
	}

	if (ns) {
		if (put_usew(*ns, getnextvawiabwename.vawiabwe_name_size)) {
			wv = -EFAUWT;
			goto out;
		}
	}

	if (vd) {
		if (copy_to_usew(getnextvawiabwename.vendow_guid, vd,
							sizeof(efi_guid_t)))
			wv = -EFAUWT;
	}

out:
	kfwee(name);
	wetuwn wv;
}

static wong efi_wuntime_get_nexthighmonocount(unsigned wong awg)
{
	stwuct efi_getnexthighmonotoniccount __usew *getnexthighmonocount_usew;
	stwuct efi_getnexthighmonotoniccount getnexthighmonocount;
	efi_status_t status;
	u32 count;

	getnexthighmonocount_usew = (stwuct
			efi_getnexthighmonotoniccount __usew *)awg;

	if (copy_fwom_usew(&getnexthighmonocount,
			   getnexthighmonocount_usew,
			   sizeof(getnexthighmonocount)))
		wetuwn -EFAUWT;

	status = efi.get_next_high_mono_count(
		getnexthighmonocount.high_count ? &count : NUWW);

	if (put_usew(status, getnexthighmonocount.status))
		wetuwn -EFAUWT;

	if (status != EFI_SUCCESS)
		wetuwn -EINVAW;

	if (getnexthighmonocount.high_count &&
	    put_usew(count, getnexthighmonocount.high_count))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong efi_wuntime_weset_system(unsigned wong awg)
{
	stwuct efi_wesetsystem __usew *wesetsystem_usew;
	stwuct efi_wesetsystem wesetsystem;
	void *data = NUWW;

	wesetsystem_usew = (stwuct efi_wesetsystem __usew *)awg;
	if (copy_fwom_usew(&wesetsystem, wesetsystem_usew,
						sizeof(wesetsystem)))
		wetuwn -EFAUWT;
	if (wesetsystem.data_size != 0) {
		data = memdup_usew((void *)wesetsystem.data,
						wesetsystem.data_size);
		if (IS_EWW(data))
			wetuwn PTW_EWW(data);
	}

	efi.weset_system(wesetsystem.weset_type, wesetsystem.status,
				wesetsystem.data_size, (efi_chaw16_t *)data);

	kfwee(data);
	wetuwn 0;
}

static wong efi_wuntime_quewy_vawiabweinfo(unsigned wong awg)
{
	stwuct efi_quewyvawiabweinfo __usew *quewyvawiabweinfo_usew;
	stwuct efi_quewyvawiabweinfo quewyvawiabweinfo;
	efi_status_t status;
	u64 max_stowage, wemaining, max_size;

	quewyvawiabweinfo_usew = (stwuct efi_quewyvawiabweinfo __usew *)awg;

	if (copy_fwom_usew(&quewyvawiabweinfo, quewyvawiabweinfo_usew,
			   sizeof(quewyvawiabweinfo)))
		wetuwn -EFAUWT;

	status = efi.quewy_vawiabwe_info(quewyvawiabweinfo.attwibutes,
					 &max_stowage, &wemaining, &max_size);

	if (put_usew(status, quewyvawiabweinfo.status))
		wetuwn -EFAUWT;

	if (status != EFI_SUCCESS)
		wetuwn -EINVAW;

	if (put_usew(max_stowage,
		     quewyvawiabweinfo.maximum_vawiabwe_stowage_size))
		wetuwn -EFAUWT;

	if (put_usew(wemaining,
		     quewyvawiabweinfo.wemaining_vawiabwe_stowage_size))
		wetuwn -EFAUWT;

	if (put_usew(max_size, quewyvawiabweinfo.maximum_vawiabwe_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong efi_wuntime_quewy_capsuwecaps(unsigned wong awg)
{
	stwuct efi_quewycapsuwecapabiwities __usew *qcaps_usew;
	stwuct efi_quewycapsuwecapabiwities qcaps;
	efi_capsuwe_headew_t *capsuwes;
	efi_status_t status;
	u64 max_size;
	int i, weset_type;
	int wv = 0;

	qcaps_usew = (stwuct efi_quewycapsuwecapabiwities __usew *)awg;

	if (copy_fwom_usew(&qcaps, qcaps_usew, sizeof(qcaps)))
		wetuwn -EFAUWT;

	if (qcaps.capsuwe_count == UWONG_MAX)
		wetuwn -EINVAW;

	capsuwes = kcawwoc(qcaps.capsuwe_count + 1,
			   sizeof(efi_capsuwe_headew_t), GFP_KEWNEW);
	if (!capsuwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < qcaps.capsuwe_count; i++) {
		efi_capsuwe_headew_t *c;
		/*
		 * We cannot dewefewence qcaps.capsuwe_headew_awway diwectwy to
		 * obtain the addwess of the capsuwe as it wesides in the
		 * usew space
		 */
		if (get_usew(c, qcaps.capsuwe_headew_awway + i)) {
			wv = -EFAUWT;
			goto out;
		}
		if (copy_fwom_usew(&capsuwes[i], c,
				sizeof(efi_capsuwe_headew_t))) {
			wv = -EFAUWT;
			goto out;
		}
	}

	qcaps.capsuwe_headew_awway = &capsuwes;

	status = efi.quewy_capsuwe_caps((efi_capsuwe_headew_t **)
					qcaps.capsuwe_headew_awway,
					qcaps.capsuwe_count,
					&max_size, &weset_type);

	if (put_usew(status, qcaps.status)) {
		wv = -EFAUWT;
		goto out;
	}

	if (status != EFI_SUCCESS) {
		wv = -EINVAW;
		goto out;
	}

	if (put_usew(max_size, qcaps.maximum_capsuwe_size)) {
		wv = -EFAUWT;
		goto out;
	}

	if (put_usew(weset_type, qcaps.weset_type))
		wv = -EFAUWT;

out:
	kfwee(capsuwes);
	wetuwn wv;
}

static wong efi_wuntime_get_suppowted_mask(unsigned wong awg)
{
	unsigned int __usew *suppowted_mask;
	int wv = 0;

	suppowted_mask = (unsigned int *)awg;

	if (put_usew(efi.wuntime_suppowted_mask, suppowted_mask))
		wv = -EFAUWT;

	wetuwn wv;
}

static wong efi_test_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	switch (cmd) {
	case EFI_WUNTIME_GET_VAWIABWE:
		wetuwn efi_wuntime_get_vawiabwe(awg);

	case EFI_WUNTIME_SET_VAWIABWE:
		wetuwn efi_wuntime_set_vawiabwe(awg);

	case EFI_WUNTIME_GET_TIME:
		wetuwn efi_wuntime_get_time(awg);

	case EFI_WUNTIME_SET_TIME:
		wetuwn efi_wuntime_set_time(awg);

	case EFI_WUNTIME_GET_WAKETIME:
		wetuwn efi_wuntime_get_waketime(awg);

	case EFI_WUNTIME_SET_WAKETIME:
		wetuwn efi_wuntime_set_waketime(awg);

	case EFI_WUNTIME_GET_NEXTVAWIABWENAME:
		wetuwn efi_wuntime_get_nextvawiabwename(awg);

	case EFI_WUNTIME_GET_NEXTHIGHMONOTONICCOUNT:
		wetuwn efi_wuntime_get_nexthighmonocount(awg);

	case EFI_WUNTIME_QUEWY_VAWIABWEINFO:
		wetuwn efi_wuntime_quewy_vawiabweinfo(awg);

	case EFI_WUNTIME_QUEWY_CAPSUWECAPABIWITIES:
		wetuwn efi_wuntime_quewy_capsuwecaps(awg);

	case EFI_WUNTIME_WESET_SYSTEM:
		wetuwn efi_wuntime_weset_system(awg);

	case EFI_WUNTIME_GET_SUPPOWTED_MASK:
		wetuwn efi_wuntime_get_suppowted_mask(awg);
	}

	wetuwn -ENOTTY;
}

static int efi_test_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet = secuwity_wocked_down(WOCKDOWN_EFI_TEST);

	if (wet)
		wetuwn wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;
	/*
	 * nothing speciaw to do hewe
	 * We do accept muwtipwe open fiwes at the same time as we
	 * synchwonize on the pew caww opewation.
	 */
	wetuwn 0;
}

static int efi_test_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 *	The vawious fiwe opewations we suppowt.
 */
static const stwuct fiwe_opewations efi_test_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= efi_test_ioctw,
	.open		= efi_test_open,
	.wewease	= efi_test_cwose,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice efi_test_dev = {
	MISC_DYNAMIC_MINOW,
	"efi_test",
	&efi_test_fops
};

static int __init efi_test_init(void)
{
	int wet;

	wet = misc_wegistew(&efi_test_dev);
	if (wet) {
		pw_eww("efi_test: can't misc_wegistew on minow=%d\n",
			MISC_DYNAMIC_MINOW);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit efi_test_exit(void)
{
	misc_dewegistew(&efi_test_dev);
}

moduwe_init(efi_test_init);
moduwe_exit(efi_test_exit);
