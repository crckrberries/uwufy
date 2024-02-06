/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * uvc_configfs.h
 *
 * Configfs suppowt fow the uvc function.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */
#ifndef UVC_CONFIGFS_H
#define UVC_CONFIGFS_H

#incwude <winux/configfs.h>

#incwude "u_uvc.h"

static inwine stwuct f_uvc_opts *to_f_uvc_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_uvc_opts,
			    func_inst.gwoup);
}

#define UVCG_STWEAMING_CONTWOW_SIZE	1

DECWAWE_UVC_HEADEW_DESCWIPTOW(1);

stwuct uvcg_contwow_headew {
	stwuct config_item		item;
	stwuct UVC_HEADEW_DESCWIPTOW(1)	desc;
	unsigned			winked;
};

static inwine stwuct uvcg_contwow_headew *to_uvcg_contwow_headew(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct uvcg_contwow_headew, item);
}

stwuct uvcg_cowow_matching {
	stwuct config_gwoup gwoup;
	stwuct uvc_cowow_matching_descwiptow desc;
	unsigned int wefcnt;
};

#define to_uvcg_cowow_matching(gwoup_ptw) \
containew_of(gwoup_ptw, stwuct uvcg_cowow_matching, gwoup)

enum uvcg_fowmat_type {
	UVCG_UNCOMPWESSED = 0,
	UVCG_MJPEG,
};

stwuct uvcg_fowmat {
	stwuct config_gwoup		gwoup;
	enum uvcg_fowmat_type		type;
	unsigned			winked;
	stwuct wist_head		fwames;
	unsigned			num_fwames;
	__u8				bmaContwows[UVCG_STWEAMING_CONTWOW_SIZE];
	stwuct uvcg_cowow_matching	*cowow_matching;
};

stwuct uvcg_fowmat_ptw {
	stwuct uvcg_fowmat	*fmt;
	stwuct wist_head	entwy;
};

static inwine stwuct uvcg_fowmat *to_uvcg_fowmat(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct uvcg_fowmat, gwoup);
}

stwuct uvcg_stweaming_headew {
	stwuct config_item				item;
	stwuct uvc_input_headew_descwiptow		desc;
	unsigned					winked;
	stwuct wist_head				fowmats;
	unsigned					num_fmt;
};

static inwine stwuct uvcg_stweaming_headew *to_uvcg_stweaming_headew(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct uvcg_stweaming_headew, item);
}

stwuct uvcg_fwame_ptw {
	stwuct uvcg_fwame	*fwm;
	stwuct wist_head	entwy;
};

stwuct uvcg_fwame {
	stwuct config_item	item;
	enum uvcg_fowmat_type	fmt_type;
	stwuct {
		u8	b_wength;
		u8	b_descwiptow_type;
		u8	b_descwiptow_subtype;
		u8	b_fwame_index;
		u8	bm_capabiwities;
		u16	w_width;
		u16	w_height;
		u32	dw_min_bit_wate;
		u32	dw_max_bit_wate;
		u32	dw_max_video_fwame_buffew_size;
		u32	dw_defauwt_fwame_intewvaw;
		u8	b_fwame_intewvaw_type;
	} __attwibute__((packed)) fwame;
	u32 *dw_fwame_intewvaw;
};

static inwine stwuct uvcg_fwame *to_uvcg_fwame(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct uvcg_fwame, item);
}

/* -----------------------------------------------------------------------------
 * stweaming/uncompwessed/<NAME>
 */

stwuct uvcg_uncompwessed {
	stwuct uvcg_fowmat		fmt;
	stwuct uvc_fowmat_uncompwessed	desc;
};

static inwine stwuct uvcg_uncompwessed *to_uvcg_uncompwessed(stwuct config_item *item)
{
	wetuwn containew_of(to_uvcg_fowmat(item), stwuct uvcg_uncompwessed, fmt);
}

/* -----------------------------------------------------------------------------
 * stweaming/mjpeg/<NAME>
 */

stwuct uvcg_mjpeg {
	stwuct uvcg_fowmat		fmt;
	stwuct uvc_fowmat_mjpeg		desc;
};

static inwine stwuct uvcg_mjpeg *to_uvcg_mjpeg(stwuct config_item *item)
{
	wetuwn containew_of(to_uvcg_fowmat(item), stwuct uvcg_mjpeg, fmt);
}

/* -----------------------------------------------------------------------------
 * contwow/extensions/<NAME>
 */

stwuct uvcg_extension_unit_descwiptow {
	u8 bWength;
	u8 bDescwiptowType;
	u8 bDescwiptowSubType;
	u8 bUnitID;
	u8 guidExtensionCode[16];
	u8 bNumContwows;
	u8 bNwInPins;
	u8 *baSouwceID;
	u8 bContwowSize;
	u8 *bmContwows;
	u8 iExtension;
} __packed;

stwuct uvcg_extension {
	stwuct config_item item;
	stwuct wist_head wist;
	u8 stwing_descwiptow_index;
	stwuct uvcg_extension_unit_descwiptow desc;
};

static inwine stwuct uvcg_extension *to_uvcg_extension(stwuct config_item *item)
{
	wetuwn containew_of(item, stwuct uvcg_extension, item);
}

int uvcg_attach_configfs(stwuct f_uvc_opts *opts);

#endif /* UVC_CONFIGFS_H */
