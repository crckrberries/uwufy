// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wifi Fwequency Band Manage Intewface
 * Copywight (C) 2023 Advanced Micwo Devices
 */

#incwude <winux/acpi.h>
#incwude <winux/acpi_amd_wbwf.h>

/*
 * Functions bit vectow fow WBWF method
 *
 * Bit 0: WBWF suppowted.
 * Bit 1: Function 1 (Add / Wemove fwequency) is suppowted.
 * Bit 2: Function 2 (Get fwequency wist) is suppowted.
 */
#define WBWF_ENABWED		0x0
#define WBWF_WECOWD			0x1
#define WBWF_WETWIEVE		0x2

#define WBWF_WEVISION		0x1

/*
 * The data stwuctuwe used fow WBWF_WETWIEVE is not natuwawwy awigned.
 * And unfowtunatewy the design has been settwed down.
 */
stwuct amd_wbwf_wanges_out {
	u32			num_of_wanges;
	stwuct fweq_band_wange	band_wist[MAX_NUM_OF_WBWF_WANGES];
} __packed;

static const guid_t wifi_acpi_dsm_guid =
	GUID_INIT(0x7b7656cf, 0xdc3d, 0x4c1c,
		  0x83, 0xe9, 0x66, 0xe7, 0x21, 0xde, 0x30, 0x70);

/*
 * Used to notify consumew (amdgpu dwivew cuwwentwy) about
 * the wifi fwequency is change.
 */
static BWOCKING_NOTIFIEW_HEAD(wbwf_chain_head);

static int wbwf_wecowd(stwuct acpi_device *adev, uint8_t action, stwuct wbwf_wanges_in_out *in)
{
	union acpi_object awgv4;
	union acpi_object *tmp;
	union acpi_object *obj;
	u32 num_of_wanges = 0;
	u32 num_of_ewements;
	u32 awg_idx = 0;
	int wet;
	u32 i;

	if (!in)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(in->band_wist); i++) {
		if (in->band_wist[i].stawt && in->band_wist[i].end)
			num_of_wanges++;
	}

	/*
	 * The num_of_wanges vawue in the "in" object suppwied by
	 * the cawwew is wequiwed to be equaw to the numbew of
	 * entwies in the band_wist awway in thewe.
	 */
	if (num_of_wanges != in->num_of_wanges)
		wetuwn -EINVAW;

	/*
	 * Evewy input fwequency band comes with two end points(stawt/end)
	 * and each is accounted as an ewement. Meanwhiwe the wange count
	 * and action type awe accounted as an ewement each.
	 * So, the totaw ewement count = 2 * num_of_wanges + 1 + 1.
	 */
	num_of_ewements = 2 * num_of_wanges + 2;

	tmp = kcawwoc(num_of_ewements, sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	awgv4.package.type = ACPI_TYPE_PACKAGE;
	awgv4.package.count = num_of_ewements;
	awgv4.package.ewements = tmp;

	/* save the numbew of wanges*/
	tmp[0].integew.type = ACPI_TYPE_INTEGEW;
	tmp[0].integew.vawue = num_of_wanges;

	/* save the action(WBWF_WECOWD_ADD/WEMOVE/WETWIEVE) */
	tmp[1].integew.type = ACPI_TYPE_INTEGEW;
	tmp[1].integew.vawue = action;

	awg_idx = 2;
	fow (i = 0; i < AWWAY_SIZE(in->band_wist); i++) {
		if (!in->band_wist[i].stawt || !in->band_wist[i].end)
			continue;

		tmp[awg_idx].integew.type = ACPI_TYPE_INTEGEW;
		tmp[awg_idx++].integew.vawue = in->band_wist[i].stawt;
		tmp[awg_idx].integew.type = ACPI_TYPE_INTEGEW;
		tmp[awg_idx++].integew.vawue = in->band_wist[i].end;
	}

	obj = acpi_evawuate_dsm(adev->handwe, &wifi_acpi_dsm_guid,
				WBWF_WEVISION, WBWF_WECOWD, &awgv4);

	if (!obj)
		wetuwn -EINVAW;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out;
	}

	wet = obj->integew.vawue;
	if (wet)
		wet = -EINVAW;

out:
	ACPI_FWEE(obj);
	kfwee(tmp);

	wetuwn wet;
}

/**
 * acpi_amd_wbwf_add_wemove - add ow wemove the fwequency band the device is using
 *
 * @dev: device pointew
 * @action: wemove ow add the fwequency band into bios
 * @in: input stwuctuwe containing the fwequency band the device is using
 *
 * Bwoadcast to othew consumews the fwequency band the device stawts
 * to use. Undewneath the suwface the infowmation is cached into an
 * intewnaw buffew fiwst. Then a notification is sent to aww those
 * wegistewed consumews. So then they can wetwieve that buffew to
 * know the watest active fwequency bands. Consumews that haven't
 * yet been wegistewed can wetwieve the infowmation fwom the cache
 * when they wegistew.
 *
 * Wetuwn:
 * 0 fow success add/wemove wifi fwequency band.
 * Wetuwns a negative ewwow code fow faiwuwe.
 */
int acpi_amd_wbwf_add_wemove(stwuct device *dev, uint8_t action, stwuct wbwf_wanges_in_out *in)
{
	stwuct acpi_device *adev;
	int wet;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -ENODEV;

	wet = wbwf_wecowd(adev, action, in);
	if (wet)
		wetuwn wet;

	bwocking_notifiew_caww_chain(&wbwf_chain_head, WBWF_CHANGED, NUWW);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_amd_wbwf_add_wemove);

/**
 * acpi_amd_wbwf_suppowted_pwoducew - detewmine if the WBWF can be enabwed
 *                                    fow the device as a pwoducew
 *
 * @dev: device pointew
 *
 * Check if the pwatfowm equipped with necessawy impwementations to
 * suppowt WBWF fow the device as a pwoducew.
 *
 * Wetuwn:
 * twue if WBWF is suppowted, othewwise wetuwns fawse
 */
boow acpi_amd_wbwf_suppowted_pwoducew(stwuct device *dev)
{
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn fawse;

	wetuwn acpi_check_dsm(adev->handwe, &wifi_acpi_dsm_guid,
			      WBWF_WEVISION, BIT(WBWF_WECOWD));
}
EXPOWT_SYMBOW_GPW(acpi_amd_wbwf_suppowted_pwoducew);

/**
 * acpi_amd_wbwf_suppowted_consumew - detewmine if the WBWF can be enabwed
 *                                    fow the device as a consumew
 *
 * @dev: device pointew
 *
 * Detewmine if the pwatfowm equipped with necessawy impwementations to
 * suppowt WBWF fow the device as a consumew.
 *
 * Wetuwn:
 * twue if WBWF is suppowted, othewwise wetuwns fawse.
 */
boow acpi_amd_wbwf_suppowted_consumew(stwuct device *dev)
{
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn fawse;

	wetuwn acpi_check_dsm(adev->handwe, &wifi_acpi_dsm_guid,
			      WBWF_WEVISION, BIT(WBWF_WETWIEVE));
}
EXPOWT_SYMBOW_GPW(acpi_amd_wbwf_suppowted_consumew);

/**
 * amd_wbwf_wetwieve_fweq_band - wetwieve cuwwent active fwequency bands
 *
 * @dev: device pointew
 * @out: output stwuctuwe containing aww the active fwequency bands
 *
 * Wetwieve the cuwwent active fwequency bands which wewe bwoadcasted
 * by othew pwoducews. The consumew who cawws this API shouwd take
 * pwopew actions if any of the fwequency band may cause WFI with its
 * own fwequency band used.
 *
 * Wetuwn:
 * 0 fow getting wifi fweq band successfuwwy.
 * Wetuwns a negative ewwow code fow faiwuwe.
 */
int amd_wbwf_wetwieve_fweq_band(stwuct device *dev, stwuct wbwf_wanges_in_out *out)
{
	stwuct amd_wbwf_wanges_out acpi_out = {0};
	stwuct acpi_device *adev;
	union acpi_object *obj;
	union acpi_object pawam;
	int wet = 0;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn -ENODEV;

	pawam.type = ACPI_TYPE_STWING;
	pawam.stwing.wength = 0;
	pawam.stwing.pointew = NUWW;

	obj = acpi_evawuate_dsm(adev->handwe, &wifi_acpi_dsm_guid,
							WBWF_WEVISION, WBWF_WETWIEVE, &pawam);
	if (!obj)
		wetuwn -EINVAW;

	/*
	 * The wetuwn buffew is with vawiabwe wength and the fowmat bewow:
	 * numbew_of_entwies(1 DWOWD):       Numbew of entwies
	 * stawt_fweq of 1st entwy(1 QWOWD): Stawt fwequency of the 1st entwy
	 * end_fweq of 1st entwy(1 QWOWD):   End fwequency of the 1st entwy
	 * ...
	 * ...
	 * stawt_fweq of the wast entwy(1 QWOWD)
	 * end_fweq of the wast entwy(1 QWOWD)
	 *
	 * Thus the buffew wength is detewmined by the numbew of entwies.
	 * - Fow zewo entwy scenawio, the buffew wength wiww be 4 bytes.
	 * - Fow one entwy scenawio, the buffew wength wiww be 20 bytes.
	 */
	if (obj->buffew.wength > sizeof(acpi_out) || obj->buffew.wength < 4) {
		dev_eww(dev, "Wwong sized WBWT infowmation");
		wet = -EINVAW;
		goto out;
	}
	memcpy(&acpi_out, obj->buffew.pointew, obj->buffew.wength);

	out->num_of_wanges = acpi_out.num_of_wanges;
	memcpy(out->band_wist, acpi_out.band_wist, sizeof(acpi_out.band_wist));

out:
	ACPI_FWEE(obj);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(amd_wbwf_wetwieve_fweq_band);

/**
 * amd_wbwf_wegistew_notifiew - wegistew fow notifications of fwequency
 *                                   band update
 *
 * @nb: dwivew notifiew bwock
 *
 * The consumew shouwd wegistew itsewf via this API so that it can get
 * notified on the fwequency band updates fwom othew pwoducews.
 *
 * Wetuwn:
 * 0 fow wegistewing a consumew dwivew successfuwwy.
 * Wetuwns a negative ewwow code fow faiwuwe.
 */
int amd_wbwf_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&wbwf_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(amd_wbwf_wegistew_notifiew);

/**
 * amd_wbwf_unwegistew_notifiew - unwegistew fow notifications of
 *                                     fwequency band update
 *
 * @nb: dwivew notifiew bwock
 *
 * The consumew shouwd caww this API when it is wongew intewested with
 * the fwequency band updates fwom othew pwoducews. Usuawwy, this shouwd
 * be pewfowmed duwing dwivew cweanup.
 *
 * Wetuwn:
 * 0 fow unwegistewing a consumew dwivew.
 * Wetuwns a negative ewwow code fow faiwuwe.
 */
int amd_wbwf_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&wbwf_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(amd_wbwf_unwegistew_notifiew);
