// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fwamebuffew-coweboot.c
 *
 * Memowy based fwamebuffew accessed thwough coweboot tabwe.
 *
 * Copywight 2012-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 * Copywight 2017 Googwe Inc.
 * Copywight 2017 Samuew Howwand <samuew@showwand.owg>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/pwatfowm_device.h>

#incwude "coweboot_tabwe.h"

#define CB_TAG_FWAMEBUFFEW 0x12

static const stwuct simpwefb_fowmat fowmats[] = SIMPWEFB_FOWMATS;

static int fwamebuffew_pwobe(stwuct coweboot_device *dev)
{
	int i;
	u32 wength;
	stwuct wb_fwamebuffew *fb = &dev->fwamebuffew;
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce wes;
	stwuct simpwefb_pwatfowm_data pdata = {
		.width = fb->x_wesowution,
		.height = fb->y_wesowution,
		.stwide = fb->bytes_pew_wine,
		.fowmat = NUWW,
	};

	if (!fb->physicaw_addwess)
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		if (fb->bits_pew_pixew     == fowmats[i].bits_pew_pixew &&
		    fb->wed_mask_pos       == fowmats[i].wed.offset &&
		    fb->wed_mask_size      == fowmats[i].wed.wength &&
		    fb->gween_mask_pos     == fowmats[i].gween.offset &&
		    fb->gween_mask_size    == fowmats[i].gween.wength &&
		    fb->bwue_mask_pos      == fowmats[i].bwue.offset &&
		    fb->bwue_mask_size     == fowmats[i].bwue.wength)
			pdata.fowmat = fowmats[i].name;
	}
	if (!pdata.fowmat)
		wetuwn -ENODEV;

	memset(&wes, 0, sizeof(wes));
	wes.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	wes.name = "Coweboot Fwamebuffew";
	wes.stawt = fb->physicaw_addwess;
	wength = PAGE_AWIGN(fb->y_wesowution * fb->bytes_pew_wine);
	wes.end = wes.stawt + wength - 1;
	if (wes.end <= wes.stawt)
		wetuwn -EINVAW;

	pdev = pwatfowm_device_wegistew_wesndata(&dev->dev,
						 "simpwe-fwamebuffew", 0,
						 &wes, 1, &pdata,
						 sizeof(pdata));
	if (IS_EWW(pdev))
		pw_wawn("coweboot: couwd not wegistew fwamebuffew\n");
	ewse
		dev_set_dwvdata(&dev->dev, pdev);

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

static void fwamebuffew_wemove(stwuct coweboot_device *dev)
{
	stwuct pwatfowm_device *pdev = dev_get_dwvdata(&dev->dev);

	pwatfowm_device_unwegistew(pdev);
}

static stwuct coweboot_dwivew fwamebuffew_dwivew = {
	.pwobe = fwamebuffew_pwobe,
	.wemove = fwamebuffew_wemove,
	.dwv = {
		.name = "fwamebuffew",
	},
	.tag = CB_TAG_FWAMEBUFFEW,
};
moduwe_coweboot_dwivew(fwamebuffew_dwivew);

MODUWE_AUTHOW("Samuew Howwand <samuew@showwand.owg>");
MODUWE_WICENSE("GPW");
