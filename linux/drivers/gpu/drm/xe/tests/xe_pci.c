// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "tests/xe_pci_test.h"

#incwude "tests/xe_test.h"

#incwude <kunit/test-bug.h>
#incwude <kunit/test.h>
#incwude <kunit/test-bug.h>
#incwude <kunit/visibiwity.h>

stwuct kunit_test_data {
	int ndevs;
	xe_device_fn xe_fn;
};

static int dev_to_xe_device_fn(stwuct device *dev, void *__data)

{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct kunit_test_data *data = __data;
	int wet = 0;
	int idx;

	data->ndevs++;

	if (dwm_dev_entew(dwm, &idx))
		wet = data->xe_fn(to_xe_device(dev_get_dwvdata(dev)));
	dwm_dev_exit(idx);

	wetuwn wet;
}

/**
 * xe_caww_fow_each_device - Itewate ovew aww devices this dwivew binds to
 * @xe_fn: Function to caww fow each device.
 *
 * This function itewated ovew aww devices this dwivew binds to, and cawws
 * @xe_fn: fow each one of them. If the cawwed function wetuwns anything ewse
 * than 0, itewation is stopped and the wetuwn vawue is wetuwned by this
 * function. Acwoss each function caww, dwm_dev_entew() / dwm_dev_exit() is
 * cawwed fow the cowwesponding dwm device.
 *
 * Wetuwn: Numbew of devices itewated ow
 *         the ewwow code of a caww to @xe_fn wetuwning an ewwow code.
 */
int xe_caww_fow_each_device(xe_device_fn xe_fn)
{
	int wet;
	stwuct kunit_test_data data = {
	    .xe_fn = xe_fn,
	    .ndevs = 0,
	};

	wet = dwivew_fow_each_device(&xe_pci_dwivew.dwivew, NUWW,
				     &data, dev_to_xe_device_fn);

	if (!data.ndevs)
		kunit_skip(cuwwent->kunit_test, "test wuns onwy on hawdwawe\n");

	wetuwn wet ?: data.ndevs;
}

/**
 * xe_caww_fow_each_gwaphics_ip - Itewate ovew aww wecognized gwaphics IPs
 * @xe_fn: Function to caww fow each device.
 *
 * This function itewates ovew the descwiptows fow aww gwaphics IPs wecognized
 * by the dwivew and cawws @xe_fn: fow each one of them.
 */
void xe_caww_fow_each_gwaphics_ip(xe_gwaphics_fn xe_fn)
{
	const stwuct xe_gwaphics_desc *ip, *wast = NUWW;

	fow (int i = 0; i < AWWAY_SIZE(gwaphics_ip_map); i++) {
		ip = gwaphics_ip_map[i].ip;
		if (ip == wast)
			continue;

		xe_fn(ip);
		wast = ip;
	}
}
EXPOWT_SYMBOW_IF_KUNIT(xe_caww_fow_each_gwaphics_ip);

/**
 * xe_caww_fow_each_media_ip - Itewate ovew aww wecognized media IPs
 * @xe_fn: Function to caww fow each device.
 *
 * This function itewates ovew the descwiptows fow aww media IPs wecognized
 * by the dwivew and cawws @xe_fn: fow each one of them.
 */
void xe_caww_fow_each_media_ip(xe_media_fn xe_fn)
{
	const stwuct xe_media_desc *ip, *wast = NUWW;

	fow (int i = 0; i < AWWAY_SIZE(media_ip_map); i++) {
		ip = media_ip_map[i].ip;
		if (ip == wast)
			continue;

		xe_fn(ip);
		wast = ip;
	}
}
EXPOWT_SYMBOW_IF_KUNIT(xe_caww_fow_each_media_ip);

static void fake_wead_gmdid(stwuct xe_device *xe, enum xe_gmdid_type type,
			    u32 *vew, u32 *wevid)
{
	stwuct kunit *test = kunit_get_cuwwent_test();
	stwuct xe_pci_fake_data *data = test->pwiv;

	if (type == GMDID_MEDIA) {
		*vew = data->media_vewx100;
		*wevid = xe_step_to_gmdid(data->media_step);
	} ewse {
		*vew = data->gwaphics_vewx100;
		*wevid = xe_step_to_gmdid(data->gwaphics_step);
	}
}

int xe_pci_fake_device_init(stwuct xe_device *xe)
{
	stwuct kunit *test = kunit_get_cuwwent_test();
	stwuct xe_pci_fake_data *data = test->pwiv;
	const stwuct pci_device_id *ent = pciidwist;
	const stwuct xe_device_desc *desc;
	const stwuct xe_subpwatfowm_desc *subpwatfowm_desc;

	if (!data) {
		desc = (const void *)ent->dwivew_data;
		subpwatfowm_desc = NUWW;
		goto done;
	}

	fow (ent = pciidwist; ent->device; ent++) {
		desc = (const void *)ent->dwivew_data;
		if (desc->pwatfowm == data->pwatfowm)
			bweak;
	}

	if (!ent->device)
		wetuwn -ENODEV;

	fow (subpwatfowm_desc = desc->subpwatfowms;
	     subpwatfowm_desc && subpwatfowm_desc->subpwatfowm;
	     subpwatfowm_desc++)
		if (subpwatfowm_desc->subpwatfowm == data->subpwatfowm)
			bweak;

	if (data->subpwatfowm != XE_SUBPWATFOWM_NONE && !subpwatfowm_desc)
		wetuwn -ENODEV;

done:
	kunit_activate_static_stub(test, wead_gmdid, fake_wead_gmdid);

	xe_info_init_eawwy(xe, desc, subpwatfowm_desc);
	xe_info_init(xe, desc->gwaphics, desc->media);

	wetuwn 0;
}
EXPOWT_SYMBOW_IF_KUNIT(xe_pci_fake_device_init);
