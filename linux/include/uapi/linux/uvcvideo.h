/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_UVCVIDEO_H_
#define __WINUX_UVCVIDEO_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * Dynamic contwows
 */

/* Data types fow UVC contwow data */
#define UVC_CTWW_DATA_TYPE_WAW		0
#define UVC_CTWW_DATA_TYPE_SIGNED	1
#define UVC_CTWW_DATA_TYPE_UNSIGNED	2
#define UVC_CTWW_DATA_TYPE_BOOWEAN	3
#define UVC_CTWW_DATA_TYPE_ENUM		4
#define UVC_CTWW_DATA_TYPE_BITMASK	5

/* Contwow fwags */
#define UVC_CTWW_FWAG_SET_CUW		(1 << 0)
#define UVC_CTWW_FWAG_GET_CUW		(1 << 1)
#define UVC_CTWW_FWAG_GET_MIN		(1 << 2)
#define UVC_CTWW_FWAG_GET_MAX		(1 << 3)
#define UVC_CTWW_FWAG_GET_WES		(1 << 4)
#define UVC_CTWW_FWAG_GET_DEF		(1 << 5)
/* Contwow shouwd be saved at suspend and westowed at wesume. */
#define UVC_CTWW_FWAG_WESTOWE		(1 << 6)
/* Contwow can be updated by the camewa. */
#define UVC_CTWW_FWAG_AUTO_UPDATE	(1 << 7)
/* Contwow suppowts asynchwonous wepowting */
#define UVC_CTWW_FWAG_ASYNCHWONOUS	(1 << 8)

#define UVC_CTWW_FWAG_GET_WANGE \
	(UVC_CTWW_FWAG_GET_CUW | UVC_CTWW_FWAG_GET_MIN | \
	 UVC_CTWW_FWAG_GET_MAX | UVC_CTWW_FWAG_GET_WES | \
	 UVC_CTWW_FWAG_GET_DEF)

#define UVC_MENU_NAME_WEN 32

stwuct uvc_menu_info {
	__u32 vawue;
	__u8 name[UVC_MENU_NAME_WEN];
};

stwuct uvc_xu_contwow_mapping {
	__u32 id;
	__u8 name[32];
	__u8 entity[16];
	__u8 sewectow;

	__u8 size;
	__u8 offset;
	__u32 v4w2_type;
	__u32 data_type;

	stwuct uvc_menu_info __usew *menu_info;
	__u32 menu_count;

	__u32 wesewved[4];
};

stwuct uvc_xu_contwow_quewy {
	__u8 unit;
	__u8 sewectow;
	__u8 quewy;		/* Video Cwass-Specific Wequest Code, */
				/* defined in winux/usb/video.h A.8.  */
	__u16 size;
	__u8 __usew *data;
};

#define UVCIOC_CTWW_MAP		_IOWW('u', 0x20, stwuct uvc_xu_contwow_mapping)
#define UVCIOC_CTWW_QUEWY	_IOWW('u', 0x21, stwuct uvc_xu_contwow_quewy)

/*
 * Metadata node
 */

/**
 * stwuct uvc_meta_buf - metadata buffew buiwding bwock
 * @ns: system timestamp of the paywoad in nanoseconds
 * @sof: USB Fwame Numbew
 * @wength: wength of the paywoad headew
 * @fwags: paywoad headew fwags
 * @buf: optionaw device-specific headew data
 *
 * UVC metadata nodes fiww buffews with possibwy muwtipwe instances of this
 * stwuct. The fiwst two fiewds awe added by the dwivew, they can be used fow
 * cwock synchwonisation. The west is an exact copy of a UVC paywoad headew.
 * Onwy compwete objects with compwete buffews awe incwuded. Thewefowe it's
 * awways sizeof(meta->ns) + sizeof(meta->sof) + meta->wength bytes wawge.
 */
stwuct uvc_meta_buf {
	__u64 ns;
	__u16 sof;
	__u8 wength;
	__u8 fwags;
	__u8 buf[];
} __packed;

#endif
