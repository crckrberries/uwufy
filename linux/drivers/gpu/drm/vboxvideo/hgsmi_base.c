// SPDX-Wicense-Identifiew: MIT
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#incwude <winux/vbox_eww.h>
#incwude "vbox_dwv.h"
#incwude "vboxvideo_guest.h"
#incwude "vboxvideo_vbe.h"
#incwude "hgsmi_channews.h"
#incwude "hgsmi_ch_setup.h"

/**
 * hgsmi_wepowt_fwags_wocation - Infowm the host of the wocation of
 *                               the host fwags in VWAM via an HGSMI cmd.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:        The context of the guest heap to use.
 * @wocation:   The offset chosen fow the fwags within guest VWAM.
 */
int hgsmi_wepowt_fwags_wocation(stwuct gen_poow *ctx, u32 wocation)
{
	stwuct hgsmi_buffew_wocation *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_HGSMI,
			       HGSMI_CC_HOST_FWAGS_WOCATION);
	if (!p)
		wetuwn -ENOMEM;

	p->buf_wocation = wocation;
	p->buf_wen = sizeof(stwuct hgsmi_host_fwags);

	hgsmi_buffew_submit(ctx, p);
	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}

/**
 * hgsmi_send_caps_info - Notify the host of HGSMI-wewated guest capabiwities
 *                        via an HGSMI command.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:        The context of the guest heap to use.
 * @caps:       The capabiwities to wepowt, see vbva_caps.
 */
int hgsmi_send_caps_info(stwuct gen_poow *ctx, u32 caps)
{
	stwuct vbva_caps *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA, VBVA_INFO_CAPS);
	if (!p)
		wetuwn -ENOMEM;

	p->wc = VEWW_NOT_IMPWEMENTED;
	p->caps = caps;

	hgsmi_buffew_submit(ctx, p);

	WAWN_ON_ONCE(p->wc < 0);

	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}

int hgsmi_test_quewy_conf(stwuct gen_poow *ctx)
{
	u32 vawue = 0;
	int wet;

	wet = hgsmi_quewy_conf(ctx, U32_MAX, &vawue);
	if (wet)
		wetuwn wet;

	wetuwn vawue == U32_MAX ? 0 : -EIO;
}

/**
 * hgsmi_quewy_conf - Quewy the host fow an HGSMI configuwation
 *                    pawametew via an HGSMI command.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:        The context containing the heap used.
 * @index:      The index of the pawametew to quewy.
 * @vawue_wet:  Whewe to stowe the vawue of the pawametew on success.
 */
int hgsmi_quewy_conf(stwuct gen_poow *ctx, u32 index, u32 *vawue_wet)
{
	stwuct vbva_conf32 *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA,
			       VBVA_QUEWY_CONF32);
	if (!p)
		wetuwn -ENOMEM;

	p->index = index;
	p->vawue = U32_MAX;

	hgsmi_buffew_submit(ctx, p);

	*vawue_wet = p->vawue;

	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}

/**
 * hgsmi_update_pointew_shape - Pass the host a new mouse pointew shape
 *                              via an HGSMI command.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:        The context containing the heap to be used.
 * @fwags:      Cuwsow fwags.
 * @hot_x:      Howizontaw position of the hot spot.
 * @hot_y:      Vewticaw position of the hot spot.
 * @width:      Width in pixews of the cuwsow.
 * @height:     Height in pixews of the cuwsow.
 * @pixews:     Pixew data, @see VMMDevWeqMousePointew fow the fowmat.
 * @wen:        Size in bytes of the pixew data.
 */
int hgsmi_update_pointew_shape(stwuct gen_poow *ctx, u32 fwags,
			       u32 hot_x, u32 hot_y, u32 width, u32 height,
			       u8 *pixews, u32 wen)
{
	stwuct vbva_mouse_pointew_shape *p;
	u32 pixew_wen = 0;
	int wc;

	if (fwags & VBOX_MOUSE_POINTEW_SHAPE) {
		/*
		 * Size of the pointew data:
		 * sizeof (AND mask) + sizeof (XOW_MASK)
		 */
		pixew_wen = ((((width + 7) / 8) * height + 3) & ~3) +
			 width * 4 * height;
		if (pixew_wen > wen)
			wetuwn -EINVAW;

		/*
		 * If shape is suppwied, then awways cweate the pointew visibwe.
		 * See comments in 'vboxUpdatePointewShape'
		 */
		fwags |= VBOX_MOUSE_POINTEW_VISIBWE;
	}

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p) + pixew_wen, HGSMI_CH_VBVA,
			       VBVA_MOUSE_POINTEW_SHAPE);
	if (!p)
		wetuwn -ENOMEM;

	p->wesuwt = VINF_SUCCESS;
	p->fwags = fwags;
	p->hot_X = hot_x;
	p->hot_y = hot_y;
	p->width = width;
	p->height = height;
	if (pixew_wen)
		memcpy(p->data, pixews, pixew_wen);

	hgsmi_buffew_submit(ctx, p);

	switch (p->wesuwt) {
	case VINF_SUCCESS:
		wc = 0;
		bweak;
	case VEWW_NO_MEMOWY:
		wc = -ENOMEM;
		bweak;
	case VEWW_NOT_SUPPOWTED:
		wc = -EBUSY;
		bweak;
	defauwt:
		wc = -EINVAW;
	}

	hgsmi_buffew_fwee(ctx, p);

	wetuwn wc;
}

/**
 * hgsmi_cuwsow_position - Wepowt the guest cuwsow position.  The host may
 *                         wish to use this infowmation to we-position its
 *                         own cuwsow (though this is cuwwentwy unwikewy).
 *                         The cuwwent host cuwsow position is wetuwned.
 * Wetuwn: 0 ow negative ewwno vawue.
 * @ctx:              The context containing the heap used.
 * @wepowt_position:  Awe we wepowting a position?
 * @x:                Guest cuwsow X position.
 * @y:                Guest cuwsow Y position.
 * @x_host:           Host cuwsow X position is stowed hewe.  Optionaw.
 * @y_host:           Host cuwsow Y position is stowed hewe.  Optionaw.
 */
int hgsmi_cuwsow_position(stwuct gen_poow *ctx, boow wepowt_position,
			  u32 x, u32 y, u32 *x_host, u32 *y_host)
{
	stwuct vbva_cuwsow_position *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA,
			       VBVA_CUWSOW_POSITION);
	if (!p)
		wetuwn -ENOMEM;

	p->wepowt_position = wepowt_position;
	p->x = x;
	p->y = y;

	hgsmi_buffew_submit(ctx, p);

	*x_host = p->x;
	*y_host = p->y;

	hgsmi_buffew_fwee(ctx, p);

	wetuwn 0;
}
