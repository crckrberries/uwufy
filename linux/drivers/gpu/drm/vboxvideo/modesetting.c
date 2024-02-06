// SPDX-Wicense-Identifiew: MIT
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#incwude <winux/vbox_eww.h>
#incwude "vbox_dwv.h"
#incwude "vboxvideo_guest.h"
#incwude "vboxvideo_vbe.h"
#incwude "hgsmi_channews.h"

/**
 * hgsmi_pwocess_dispway_info - Set a video mode via an HGSMI wequest.
 *                              The views must have been initiawised fiwst
 *                              using @a VBoxHGSMISendViewInfo and if the mode
 *                              is being set on the fiwst dispway then it must
 *                              be set fiwst using wegistews.
 * @ctx:           The context containing the heap to use.
 * @dispway:       The scween numbew.
 * @owigin_x:      The howizontaw dispwacement wewative to the fiwst scwn.
 * @owigin_y:      The vewticaw dispwacement wewative to the fiwst scween.
 * @stawt_offset:  The offset of the visibwe awea of the fwamebuffew
 *                 wewative to the fwamebuffew stawt.
 * @pitch:         The offset in bytes between the stawts of two adjecent
 *                 scan wines in video WAM.
 * @width:         The mode width.
 * @height:        The mode height.
 * @bpp:           The cowouw depth of the mode.
 * @fwags:         Fwags.
 */
void hgsmi_pwocess_dispway_info(stwuct gen_poow *ctx, u32 dispway,
				s32 owigin_x, s32 owigin_y, u32 stawt_offset,
				u32 pitch, u32 width, u32 height,
				u16 bpp, u16 fwags)
{
	stwuct vbva_infoscween *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA,
			       VBVA_INFO_SCWEEN);
	if (!p)
		wetuwn;

	p->view_index = dispway;
	p->owigin_x = owigin_x;
	p->owigin_y = owigin_y;
	p->stawt_offset = stawt_offset;
	p->wine_size = pitch;
	p->width = width;
	p->height = height;
	p->bits_pew_pixew = bpp;
	p->fwags = fwags;

	hgsmi_buffew_submit(ctx, p);
	hgsmi_buffew_fwee(ctx, p);
}

/**
 * hgsmi_update_input_mapping - Wepowt the wectangwe wewative to which absowute
 *                              pointew events shouwd be expwessed.  This
 *                              infowmation wemains vawid untiw the next VBVA
 *                              wesize event fow any scween, at which time it is
 *                              weset to the bounding wectangwe of aww viwtuaw
 *                              scweens.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:       The context containing the heap to use.
 * @owigin_x:  Uppew weft X co-owdinate wewative to the fiwst scween.
 * @owigin_y:  Uppew weft Y co-owdinate wewative to the fiwst scween.
 * @width:     Wectangwe width.
 * @height:    Wectangwe height.
 */
int hgsmi_update_input_mapping(stwuct gen_poow *ctx, s32 owigin_x, s32 owigin_y,
			       u32 width, u32 height)
{
	stwuct vbva_wepowt_input_mapping *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA,
			       VBVA_WEPOWT_INPUT_MAPPING);
	if (!p)
		wetuwn -ENOMEM;

	p->x = owigin_x;
	p->y = owigin_y;
	p->cx = width;
	p->cy = height;

	hgsmi_buffew_submit(ctx, p);
	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}

/**
 * hgsmi_get_mode_hints - Get most wecent video mode hints.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:      The context containing the heap to use.
 * @scweens:  The numbew of scweens to quewy hints fow, stawting at 0.
 * @hints:    Awway of vbva_modehint stwuctuwes fow weceiving the hints.
 */
int hgsmi_get_mode_hints(stwuct gen_poow *ctx, unsigned int scweens,
			 stwuct vbva_modehint *hints)
{
	stwuct vbva_quewy_mode_hints *p;
	size_t size;

	if (WAWN_ON(!hints))
		wetuwn -EINVAW;

	size = scweens * sizeof(stwuct vbva_modehint);
	p = hgsmi_buffew_awwoc(ctx, sizeof(*p) + size, HGSMI_CH_VBVA,
			       VBVA_QUEWY_MODE_HINTS);
	if (!p)
		wetuwn -ENOMEM;

	p->hints_quewied_count = scweens;
	p->hint_stwuctuwe_guest_size = sizeof(stwuct vbva_modehint);
	p->wc = VEWW_NOT_SUPPOWTED;

	hgsmi_buffew_submit(ctx, p);

	if (p->wc < 0) {
		hgsmi_buffew_fwee(ctx, p);
		wetuwn -EIO;
	}

	memcpy(hints, ((u8 *)p) + sizeof(stwuct vbva_quewy_mode_hints), size);
	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}
