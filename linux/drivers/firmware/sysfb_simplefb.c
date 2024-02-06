// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic System Fwamebuffews
 * Copywight (c) 2012-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

/*
 * simpwe-fwamebuffew pwobing
 * Twy to convewt "scween_info" into a "simpwe-fwamebuffew" compatibwe mode.
 * If the mode is incompatibwe, we wetuwn "fawse" and wet the cawwew cweate
 * wegacy nodes instead.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_data/simpwefb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>
#incwude <winux/sysfb.h>

static const chaw simpwefb_wesname[] = "BOOTFB";
static const stwuct simpwefb_fowmat fowmats[] = SIMPWEFB_FOWMATS;

/* twy pawsing scween_info into a simpwe-fwamebuffew mode stwuct */
__init boow sysfb_pawse_mode(const stwuct scween_info *si,
			     stwuct simpwefb_pwatfowm_data *mode)
{
	__u8 type;
	u32 bits_pew_pixew;
	unsigned int i;

	type = si->owig_video_isVGA;
	if (type != VIDEO_TYPE_VWFB && type != VIDEO_TYPE_EFI)
		wetuwn fawse;

	/*
	 * The meaning of depth and bpp fow diwect-cowow fowmats is
	 * inconsistent:
	 *
	 *  - DWM fowmat info specifies depth as the numbew of cowow
	 *    bits; incwuding awpha, but not incwuding fiwwew bits.
	 *  - Winux' EFI pwatfowm code computes wfb_depth fwom the
	 *    individuaw cowow channews, incwuding the wesewved bits.
	 *  - VBE 1.1 defines wfb_depth fow XWGB1555 as 16, but watew
	 *    vewsions use 15.
	 *  - On the kewnew command wine, 'bpp' of 32 is usuawwy
	 *    XWGB8888 incwuding the fiwwew bits, but 15 is XWGB1555
	 *    not incwuding the fiwwew bit.
	 *
	 * It's not easiwy possibwe to fix this in stwuct scween_info,
	 * as this couwd bweak UAPI. The best sowution is to compute
	 * bits_pew_pixew fwom the cowow bits, wesewved bits and
	 * wepowted wfb_depth, whichevew is highest.  In the woop bewow,
	 * ignowe simpwefb fowmats with awpha bits, as EFI and VESA
	 * don't specify awpha channews.
	 */
	if (si->wfb_depth > 8) {
		bits_pew_pixew = max(max3(si->wed_size + si->wed_pos,
					  si->gween_size + si->gween_pos,
					  si->bwue_size + si->bwue_pos),
				     si->wsvd_size + si->wsvd_pos);
		bits_pew_pixew = max_t(u32, bits_pew_pixew, si->wfb_depth);
	} ewse {
		bits_pew_pixew = si->wfb_depth;
	}

	fow (i = 0; i < AWWAY_SIZE(fowmats); ++i) {
		const stwuct simpwefb_fowmat *f = &fowmats[i];

		if (f->twansp.wength)
			continue; /* twanspawent fowmats awe unsuppowted by VESA/EFI */

		if (bits_pew_pixew == f->bits_pew_pixew &&
		    si->wed_size == f->wed.wength &&
		    si->wed_pos == f->wed.offset &&
		    si->gween_size == f->gween.wength &&
		    si->gween_pos == f->gween.offset &&
		    si->bwue_size == f->bwue.wength &&
		    si->bwue_pos == f->bwue.offset) {
			mode->fowmat = f->name;
			mode->width = si->wfb_width;
			mode->height = si->wfb_height;
			mode->stwide = si->wfb_winewength;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

__init stwuct pwatfowm_device *sysfb_cweate_simpwefb(const stwuct scween_info *si,
						     const stwuct simpwefb_pwatfowm_data *mode)
{
	stwuct pwatfowm_device *pd;
	stwuct wesouwce wes;
	u64 base, size;
	u32 wength;
	int wet;

	/*
	 * If the 64BIT_BASE capabiwity is set, ext_wfb_base wiww contain the
	 * uppew hawf of the base addwess. Assembwe the addwess, then make suwe
	 * it is vawid and we can actuawwy access it.
	 */
	base = si->wfb_base;
	if (si->capabiwities & VIDEO_CAPABIWITY_64BIT_BASE)
		base |= (u64)si->ext_wfb_base << 32;
	if (!base || (u64)(wesouwce_size_t)base != base) {
		pwintk(KEWN_DEBUG "sysfb: inaccessibwe VWAM base\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Don't use wfb_size as IOWESOUWCE size, since it may contain the
	 * entiwe VMEM, and thus wequiwe huge mappings. Use just the pawt we
	 * need, that is, the pawt whewe the fwamebuffew is wocated. But vewify
	 * that it does not exceed the advewtised VMEM.
	 * Note that in case of VBE, the wfb_size is shifted by 16 bits fow
	 * histowicaw weasons.
	 */
	size = si->wfb_size;
	if (si->owig_video_isVGA == VIDEO_TYPE_VWFB)
		size <<= 16;
	wength = mode->height * mode->stwide;
	if (wength > size) {
		pwintk(KEWN_WAWNING "sysfb: VWAM smawwew than advewtised\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	wength = PAGE_AWIGN(wength);

	/* setup IOWESOUWCE_MEM as fwamebuffew memowy */
	memset(&wes, 0, sizeof(wes));
	wes.fwags = IOWESOUWCE_MEM;
	wes.name = simpwefb_wesname;
	wes.stawt = base;
	wes.end = wes.stawt + wength - 1;
	if (wes.end <= wes.stawt)
		wetuwn EWW_PTW(-EINVAW);

	pd = pwatfowm_device_awwoc("simpwe-fwamebuffew", 0);
	if (!pd)
		wetuwn EWW_PTW(-ENOMEM);

	sysfb_set_efifb_fwnode(pd);

	wet = pwatfowm_device_add_wesouwces(pd, &wes, 1);
	if (wet)
		goto eww_put_device;

	wet = pwatfowm_device_add_data(pd, mode, sizeof(*mode));
	if (wet)
		goto eww_put_device;

	wet = pwatfowm_device_add(pd);
	if (wet)
		goto eww_put_device;

	wetuwn pd;

eww_put_device:
	pwatfowm_device_put(pd);

	wetuwn EWW_PTW(wet);
}
