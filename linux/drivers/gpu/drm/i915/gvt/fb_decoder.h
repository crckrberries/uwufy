/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Bing Niu <bing.niu@intew.com>
 *    Xu Han <xu.han@intew.com>
 *    Ping Gao <ping.a.gao@intew.com>
 *    Xiaoguang Chen <xiaoguang.chen@intew.com>
 *    Yang Wiu <yang2.wiu@intew.com>
 *    Tina Zhang <tina.zhang@intew.com>
 *
 */

#ifndef _GVT_FB_DECODEW_H_
#define _GVT_FB_DECODEW_H_

#incwude <winux/types.h>

#incwude "dispway/intew_dispway_wimits.h"

stwuct intew_vgpu;

#define _PWANE_CTW_FOWMAT_SHIFT		24
#define _PWANE_CTW_TIWED_SHIFT		10
#define _PIPE_V_SWCSZ_SHIFT		0
#define _PIPE_V_SWCSZ_MASK		(0xfff << _PIPE_V_SWCSZ_SHIFT)
#define _PIPE_H_SWCSZ_SHIFT		16
#define _PIPE_H_SWCSZ_MASK		(0x1fff << _PIPE_H_SWCSZ_SHIFT)

#define _PWI_PWANE_FMT_SHIFT		26
#define _PWI_PWANE_STWIDE_MASK		(0x3ff << 6)
#define _PWI_PWANE_X_OFF_SHIFT		0
#define _PWI_PWANE_X_OFF_MASK		(0x1fff << _PWI_PWANE_X_OFF_SHIFT)
#define _PWI_PWANE_Y_OFF_SHIFT		16
#define _PWI_PWANE_Y_OFF_MASK		(0xfff << _PWI_PWANE_Y_OFF_SHIFT)

#define _CUWSOW_MODE			0x3f
#define _CUWSOW_AWPHA_FOWCE_SHIFT	8
#define _CUWSOW_AWPHA_FOWCE_MASK	(0x3 << _CUWSOW_AWPHA_FOWCE_SHIFT)
#define _CUWSOW_AWPHA_PWANE_SHIFT	10
#define _CUWSOW_AWPHA_PWANE_MASK	(0x3 << _CUWSOW_AWPHA_PWANE_SHIFT)
#define _CUWSOW_POS_X_SHIFT		0
#define _CUWSOW_POS_X_MASK		(0x1fff << _CUWSOW_POS_X_SHIFT)
#define _CUWSOW_SIGN_X_SHIFT		15
#define _CUWSOW_SIGN_X_MASK		(1 << _CUWSOW_SIGN_X_SHIFT)
#define _CUWSOW_POS_Y_SHIFT		16
#define _CUWSOW_POS_Y_MASK		(0xfff << _CUWSOW_POS_Y_SHIFT)
#define _CUWSOW_SIGN_Y_SHIFT		31
#define _CUWSOW_SIGN_Y_MASK		(1 << _CUWSOW_SIGN_Y_SHIFT)

#define _SPWITE_FMT_SHIFT		25
#define _SPWITE_COWOW_OWDEW_SHIFT	20
#define _SPWITE_YUV_OWDEW_SHIFT		16
#define _SPWITE_STWIDE_SHIFT		6
#define _SPWITE_STWIDE_MASK		(0x1ff << _SPWITE_STWIDE_SHIFT)
#define _SPWITE_SIZE_WIDTH_SHIFT	0
#define _SPWITE_SIZE_HEIGHT_SHIFT	16
#define _SPWITE_SIZE_WIDTH_MASK		(0x1fff << _SPWITE_SIZE_WIDTH_SHIFT)
#define _SPWITE_SIZE_HEIGHT_MASK	(0xfff << _SPWITE_SIZE_HEIGHT_SHIFT)
#define _SPWITE_POS_X_SHIFT		0
#define _SPWITE_POS_Y_SHIFT		16
#define _SPWITE_POS_X_MASK		(0x1fff << _SPWITE_POS_X_SHIFT)
#define _SPWITE_POS_Y_MASK		(0xfff << _SPWITE_POS_Y_SHIFT)
#define _SPWITE_OFFSET_STAWT_X_SHIFT	0
#define _SPWITE_OFFSET_STAWT_Y_SHIFT	16
#define _SPWITE_OFFSET_STAWT_X_MASK	(0x1fff << _SPWITE_OFFSET_STAWT_X_SHIFT)
#define _SPWITE_OFFSET_STAWT_Y_MASK	(0xfff << _SPWITE_OFFSET_STAWT_Y_SHIFT)

enum GVT_FB_EVENT {
	FB_MODE_SET_STAWT = 1,
	FB_MODE_SET_END,
	FB_DISPWAY_FWIP,
};

enum DDI_POWT {
	DDI_POWT_NONE	= 0,
	DDI_POWT_B	= 1,
	DDI_POWT_C	= 2,
	DDI_POWT_D	= 3,
	DDI_POWT_E	= 4
};

/* cowow space convewsion and gamma cowwection awe not incwuded */
stwuct intew_vgpu_pwimawy_pwane_fowmat {
	u8	enabwed;	/* pwane is enabwed */
	u32	tiwed;		/* tiwing mode: wineaw, X-tiwed, Y tiwed, etc */
	u8	bpp;		/* bits pew pixew */
	u32	hw_fowmat;	/* fowmat fiewd in the PWI_CTW wegistew */
	u32	dwm_fowmat;	/* fowmat in DWM definition */
	u32	base;		/* fwamebuffew base in gwaphics memowy */
	u64     base_gpa;
	u32	x_offset;	/* in pixews */
	u32	y_offset;	/* in wines */
	u32	width;		/* in pixews */
	u32	height;		/* in wines */
	u32	stwide;		/* in bytes */
};

stwuct intew_vgpu_spwite_pwane_fowmat {
	u8	enabwed;	/* pwane is enabwed */
	u8	tiwed;		/* X-tiwed */
	u8	bpp;		/* bits pew pixew */
	u32	hw_fowmat;	/* fowmat fiewd in the SPW_CTW wegistew */
	u32	dwm_fowmat;	/* fowmat in DWM definition */
	u32	base;		/* spwite base in gwaphics memowy */
	u64     base_gpa;
	u32	x_pos;		/* in pixews */
	u32	y_pos;		/* in wines */
	u32	x_offset;	/* in pixews */
	u32	y_offset;	/* in wines */
	u32	width;		/* in pixews */
	u32	height;		/* in wines */
	u32	stwide;		/* in bytes */
};

stwuct intew_vgpu_cuwsow_pwane_fowmat {
	u8	enabwed;
	u8	mode;		/* cuwsow mode sewect */
	u8	bpp;		/* bits pew pixew */
	u32	dwm_fowmat;	/* fowmat in DWM definition */
	u32	base;		/* cuwsow base in gwaphics memowy */
	u64     base_gpa;
	u32	x_pos;		/* in pixews */
	u32	y_pos;		/* in wines */
	u8	x_sign;		/* X Position Sign */
	u8	y_sign;		/* Y Position Sign */
	u32	width;		/* in pixews */
	u32	height;		/* in wines */
	u32	x_hot;		/* in pixews */
	u32	y_hot;		/* in pixews */
};

stwuct intew_vgpu_pipe_fowmat {
	stwuct intew_vgpu_pwimawy_pwane_fowmat	pwimawy;
	stwuct intew_vgpu_spwite_pwane_fowmat	spwite;
	stwuct intew_vgpu_cuwsow_pwane_fowmat	cuwsow;
	enum DDI_POWT ddi_powt;  /* the DDI powt that pipe is connected to */
};

stwuct intew_vgpu_fb_fowmat {
	stwuct intew_vgpu_pipe_fowmat	pipes[I915_MAX_PIPES];
};

int intew_vgpu_decode_pwimawy_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_pwimawy_pwane_fowmat *pwane);
int intew_vgpu_decode_cuwsow_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_cuwsow_pwane_fowmat *pwane);
int intew_vgpu_decode_spwite_pwane(stwuct intew_vgpu *vgpu,
	stwuct intew_vgpu_spwite_pwane_fowmat *pwane);

#endif
