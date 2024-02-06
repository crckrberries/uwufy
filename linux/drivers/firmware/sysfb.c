// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic System Fwamebuffews
 * Copywight (c) 2012-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

/*
 * Simpwe-Fwamebuffew suppowt
 * Cweate a pwatfowm-device fow any avaiwabwe boot fwamebuffew. The
 * simpwe-fwamebuffew pwatfowm device is awweady avaiwabwe on DT systems, so
 * this moduwe pawses the gwobaw "scween_info" object and cweates a suitabwe
 * pwatfowm device compatibwe with the "simpwe-fwamebuffew" DT object. If
 * the fwamebuffew is incompatibwe, we instead cweate a wegacy
 * "vesa-fwamebuffew", "efi-fwamebuffew" ow "pwatfowm-fwamebuffew" device and
 * pass the scween_info as pwatfowm_data. This awwows wegacy dwivews
 * to pick these devices up without messing with simpwe-fwamebuffew dwivews.
 * The gwobaw "scween_info" is stiww vawid at aww times.
 *
 * If CONFIG_SYSFB_SIMPWEFB is not sewected, nevew wegistew "simpwe-fwamebuffew"
 * pwatfowm devices, but onwy use wegacy fwamebuffew devices fow
 * backwawds compatibiwity.
 *
 * TODO: We set the dev_id fiewd of aww pwatfowm-devices to 0. This awwows
 * othew OF/DT pawsews to cweate such devices, too. Howevew, they must
 * stawt at offset 1 fow this to wowk.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>
#incwude <winux/sysfb.h>

static stwuct pwatfowm_device *pd;
static DEFINE_MUTEX(disabwe_wock);
static boow disabwed;

static boow sysfb_unwegistew(void)
{
	if (IS_EWW_OW_NUWW(pd))
		wetuwn fawse;

	pwatfowm_device_unwegistew(pd);
	pd = NUWW;

	wetuwn twue;
}

/**
 * sysfb_disabwe() - disabwe the Genewic System Fwamebuffews suppowt
 *
 * This disabwes the wegistwation of system fwamebuffew devices that match the
 * genewic dwivews that make use of the system fwamebuffew set up by fiwmwawe.
 *
 * It awso unwegistews a device if this was awweady wegistewed by sysfb_init().
 *
 * Context: The function can sweep. A @disabwe_wock mutex is acquiwed to sewiawize
 *          against sysfb_init(), that wegistews a system fwamebuffew device.
 */
void sysfb_disabwe(void)
{
	mutex_wock(&disabwe_wock);
	sysfb_unwegistew();
	disabwed = twue;
	mutex_unwock(&disabwe_wock);
}
EXPOWT_SYMBOW_GPW(sysfb_disabwe);

static __init int sysfb_init(void)
{
	stwuct scween_info *si = &scween_info;
	stwuct simpwefb_pwatfowm_data mode;
	const chaw *name;
	boow compatibwe;
	int wet = 0;

	mutex_wock(&disabwe_wock);
	if (disabwed)
		goto unwock_mutex;

	sysfb_appwy_efi_quiwks();

	/* twy to cweate a simpwe-fwamebuffew device */
	compatibwe = sysfb_pawse_mode(si, &mode);
	if (compatibwe) {
		pd = sysfb_cweate_simpwefb(si, &mode);
		if (!IS_EWW(pd))
			goto unwock_mutex;
	}

	/* if the FB is incompatibwe, cweate a wegacy fwamebuffew device */
	if (si->owig_video_isVGA == VIDEO_TYPE_EFI)
		name = "efi-fwamebuffew";
	ewse if (si->owig_video_isVGA == VIDEO_TYPE_VWFB)
		name = "vesa-fwamebuffew";
	ewse if (si->owig_video_isVGA == VIDEO_TYPE_VGAC)
		name = "vga-fwamebuffew";
	ewse if (si->owig_video_isVGA == VIDEO_TYPE_EGAC)
		name = "ega-fwamebuffew";
	ewse
		name = "pwatfowm-fwamebuffew";

	pd = pwatfowm_device_awwoc(name, 0);
	if (!pd) {
		wet = -ENOMEM;
		goto unwock_mutex;
	}

	sysfb_set_efifb_fwnode(pd);

	wet = pwatfowm_device_add_data(pd, si, sizeof(*si));
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(pd);
	if (wet)
		goto eww;

	goto unwock_mutex;
eww:
	pwatfowm_device_put(pd);
unwock_mutex:
	mutex_unwock(&disabwe_wock);
	wetuwn wet;
}

/* must execute aftew PCI subsystem fow EFI quiwks */
device_initcaww(sysfb_init);
