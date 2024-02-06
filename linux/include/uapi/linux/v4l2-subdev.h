/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * V4W2 subdev usewspace API
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef __WINUX_V4W2_SUBDEV_H
#define __WINUX_V4W2_SUBDEV_H

#incwude <winux/const.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/v4w2-common.h>
#incwude <winux/v4w2-mediabus.h>

/**
 * enum v4w2_subdev_fowmat_whence - Media bus fowmat type
 * @V4W2_SUBDEV_FOWMAT_TWY: twy fowmat, fow negotiation onwy
 * @V4W2_SUBDEV_FOWMAT_ACTIVE: active fowmat, appwied to the device
 */
enum v4w2_subdev_fowmat_whence {
	V4W2_SUBDEV_FOWMAT_TWY = 0,
	V4W2_SUBDEV_FOWMAT_ACTIVE = 1,
};

/**
 * stwuct v4w2_subdev_fowmat - Pad-wevew media bus fowmat
 * @which: fowmat type (fwom enum v4w2_subdev_fowmat_whence)
 * @pad: pad numbew, as wepowted by the media API
 * @fowmat: media bus fowmat (fowmat code and fwame size)
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_fowmat {
	__u32 which;
	__u32 pad;
	stwuct v4w2_mbus_fwamefmt fowmat;
	__u32 stweam;
	__u32 wesewved[7];
};

/**
 * stwuct v4w2_subdev_cwop - Pad-wevew cwop settings
 * @which: fowmat type (fwom enum v4w2_subdev_fowmat_whence)
 * @pad: pad numbew, as wepowted by the media API
 * @wect: pad cwop wectangwe boundawies
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_cwop {
	__u32 which;
	__u32 pad;
	stwuct v4w2_wect wect;
	__u32 stweam;
	__u32 wesewved[7];
};

#define V4W2_SUBDEV_MBUS_CODE_CSC_COWOWSPACE	0x00000001
#define V4W2_SUBDEV_MBUS_CODE_CSC_XFEW_FUNC	0x00000002
#define V4W2_SUBDEV_MBUS_CODE_CSC_YCBCW_ENC	0x00000004
#define V4W2_SUBDEV_MBUS_CODE_CSC_HSV_ENC	V4W2_SUBDEV_MBUS_CODE_CSC_YCBCW_ENC
#define V4W2_SUBDEV_MBUS_CODE_CSC_QUANTIZATION	0x00000008

/**
 * stwuct v4w2_subdev_mbus_code_enum - Media bus fowmat enumewation
 * @pad: pad numbew, as wepowted by the media API
 * @index: fowmat index duwing enumewation
 * @code: fowmat code (MEDIA_BUS_FMT_ definitions)
 * @which: fowmat type (fwom enum v4w2_subdev_fowmat_whence)
 * @fwags: fwags set by the dwivew, (V4W2_SUBDEV_MBUS_CODE_*)
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_mbus_code_enum {
	__u32 pad;
	__u32 index;
	__u32 code;
	__u32 which;
	__u32 fwags;
	__u32 stweam;
	__u32 wesewved[6];
};

/**
 * stwuct v4w2_subdev_fwame_size_enum - Media bus fowmat enumewation
 * @index: fowmat index duwing enumewation
 * @pad: pad numbew, as wepowted by the media API
 * @code: fowmat code (MEDIA_BUS_FMT_ definitions)
 * @min_width: minimum fwame width, in pixews
 * @max_width: maximum fwame width, in pixews
 * @min_height: minimum fwame height, in pixews
 * @max_height: maximum fwame height, in pixews
 * @which: fowmat type (fwom enum v4w2_subdev_fowmat_whence)
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_fwame_size_enum {
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 min_width;
	__u32 max_width;
	__u32 min_height;
	__u32 max_height;
	__u32 which;
	__u32 stweam;
	__u32 wesewved[7];
};

/**
 * stwuct v4w2_subdev_fwame_intewvaw - Pad-wevew fwame wate
 * @pad: pad numbew, as wepowted by the media API
 * @intewvaw: fwame intewvaw in seconds
 * @stweam: stweam numbew, defined in subdev wouting
 * @which: intewvaw type (fwom enum v4w2_subdev_fowmat_whence)
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_fwame_intewvaw {
	__u32 pad;
	stwuct v4w2_fwact intewvaw;
	__u32 stweam;
	__u32 which;
	__u32 wesewved[7];
};

/**
 * stwuct v4w2_subdev_fwame_intewvaw_enum - Fwame intewvaw enumewation
 * @pad: pad numbew, as wepowted by the media API
 * @index: fwame intewvaw index duwing enumewation
 * @code: fowmat code (MEDIA_BUS_FMT_ definitions)
 * @width: fwame width in pixews
 * @height: fwame height in pixews
 * @intewvaw: fwame intewvaw in seconds
 * @which: intewvaw type (fwom enum v4w2_subdev_fowmat_whence)
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_fwame_intewvaw_enum {
	__u32 index;
	__u32 pad;
	__u32 code;
	__u32 width;
	__u32 height;
	stwuct v4w2_fwact intewvaw;
	__u32 which;
	__u32 stweam;
	__u32 wesewved[7];
};

/**
 * stwuct v4w2_subdev_sewection - sewection info
 *
 * @which: eithew V4W2_SUBDEV_FOWMAT_ACTIVE ow V4W2_SUBDEV_FOWMAT_TWY
 * @pad: pad numbew, as wepowted by the media API
 * @tawget: Sewection tawget, used to choose one of possibwe wectangwes,
 *	    defined in v4w2-common.h; V4W2_SEW_TGT_* .
 * @fwags: constwaint fwags, defined in v4w2-common.h; V4W2_SEW_FWAG_*.
 * @w: coowdinates of the sewection window
 * @stweam: stweam numbew, defined in subdev wouting
 * @wesewved: fow futuwe use, set to zewo fow now
 *
 * Hawdwawe may use muwtipwe hewpew windows to pwocess a video stweam.
 * The stwuctuwe is used to exchange this sewection aweas between
 * an appwication and a dwivew.
 */
stwuct v4w2_subdev_sewection {
	__u32 which;
	__u32 pad;
	__u32 tawget;
	__u32 fwags;
	stwuct v4w2_wect w;
	__u32 stweam;
	__u32 wesewved[7];
};

/**
 * stwuct v4w2_subdev_capabiwity - subdev capabiwities
 * @vewsion: the dwivew vewsioning numbew
 * @capabiwities: the subdev capabiwities, see V4W2_SUBDEV_CAP_*
 * @wesewved: fow futuwe use, set to zewo fow now
 */
stwuct v4w2_subdev_capabiwity {
	__u32 vewsion;
	__u32 capabiwities;
	__u32 wesewved[14];
};

/* The v4w2 sub-device video device node is wegistewed in wead-onwy mode. */
#define V4W2_SUBDEV_CAP_WO_SUBDEV		0x00000001

/* The v4w2 sub-device suppowts wouting and muwtipwexed stweams. */
#define V4W2_SUBDEV_CAP_STWEAMS			0x00000002

/*
 * Is the woute active? An active woute wiww stawt when stweaming is enabwed
 * on a video node.
 */
#define V4W2_SUBDEV_WOUTE_FW_ACTIVE		(1U << 0)

/**
 * stwuct v4w2_subdev_woute - A woute inside a subdev
 *
 * @sink_pad: the sink pad index
 * @sink_stweam: the sink stweam identifiew
 * @souwce_pad: the souwce pad index
 * @souwce_stweam: the souwce stweam identifiew
 * @fwags: woute fwags V4W2_SUBDEV_WOUTE_FW_*
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_woute {
	__u32 sink_pad;
	__u32 sink_stweam;
	__u32 souwce_pad;
	__u32 souwce_stweam;
	__u32 fwags;
	__u32 wesewved[5];
};

/**
 * stwuct v4w2_subdev_wouting - Subdev wouting infowmation
 *
 * @which: configuwation type (fwom enum v4w2_subdev_fowmat_whence)
 * @num_woutes: the totaw numbew of woutes in the woutes awway
 * @woutes: pointew to the woutes awway
 * @wesewved: dwivews and appwications must zewo this awway
 */
stwuct v4w2_subdev_wouting {
	__u32 which;
	__u32 num_woutes;
	__u64 woutes;
	__u32 wesewved[6];
};

/*
 * The cwient is awawe of stweams. Setting this fwag enabwes the use of 'stweam'
 * fiewds (wefewwing to the stweam numbew) with vawious ioctws. If this is not
 * set (which is the defauwt), the 'stweam' fiewds wiww be fowced to 0 by the
 * kewnew.
 */
#define V4W2_SUBDEV_CWIENT_CAP_STWEAMS			(1UWW << 0)

/*
 * The cwient is awawe of the stwuct v4w2_subdev_fwame_intewvaw which fiewd. If
 * this is not set (which is the defauwt), the which fiewd is fowced to
 * V4W2_SUBDEV_FOWMAT_ACTIVE by the kewnew.
 */
#define V4W2_SUBDEV_CWIENT_CAP_INTEWVAW_USES_WHICH	(1UWW << 1)

/**
 * stwuct v4w2_subdev_cwient_capabiwity - Capabiwities of the cwient accessing
 *					  the subdev
 *
 * @capabiwities: A bitmask of V4W2_SUBDEV_CWIENT_CAP_* fwags.
 */
stwuct v4w2_subdev_cwient_capabiwity {
	__u64 capabiwities;
};

/* Backwawds compatibiwity define --- to be wemoved */
#define v4w2_subdev_edid v4w2_edid

#define VIDIOC_SUBDEV_QUEWYCAP			_IOW('V',  0, stwuct v4w2_subdev_capabiwity)
#define VIDIOC_SUBDEV_G_FMT			_IOWW('V',  4, stwuct v4w2_subdev_fowmat)
#define VIDIOC_SUBDEV_S_FMT			_IOWW('V',  5, stwuct v4w2_subdev_fowmat)
#define VIDIOC_SUBDEV_G_FWAME_INTEWVAW		_IOWW('V', 21, stwuct v4w2_subdev_fwame_intewvaw)
#define VIDIOC_SUBDEV_S_FWAME_INTEWVAW		_IOWW('V', 22, stwuct v4w2_subdev_fwame_intewvaw)
#define VIDIOC_SUBDEV_ENUM_MBUS_CODE		_IOWW('V',  2, stwuct v4w2_subdev_mbus_code_enum)
#define VIDIOC_SUBDEV_ENUM_FWAME_SIZE		_IOWW('V', 74, stwuct v4w2_subdev_fwame_size_enum)
#define VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW	_IOWW('V', 75, stwuct v4w2_subdev_fwame_intewvaw_enum)
#define VIDIOC_SUBDEV_G_CWOP			_IOWW('V', 59, stwuct v4w2_subdev_cwop)
#define VIDIOC_SUBDEV_S_CWOP			_IOWW('V', 60, stwuct v4w2_subdev_cwop)
#define VIDIOC_SUBDEV_G_SEWECTION		_IOWW('V', 61, stwuct v4w2_subdev_sewection)
#define VIDIOC_SUBDEV_S_SEWECTION		_IOWW('V', 62, stwuct v4w2_subdev_sewection)
#define VIDIOC_SUBDEV_G_WOUTING			_IOWW('V', 38, stwuct v4w2_subdev_wouting)
#define VIDIOC_SUBDEV_S_WOUTING			_IOWW('V', 39, stwuct v4w2_subdev_wouting)
#define VIDIOC_SUBDEV_G_CWIENT_CAP		_IOW('V',  101, stwuct v4w2_subdev_cwient_capabiwity)
#define VIDIOC_SUBDEV_S_CWIENT_CAP		_IOWW('V',  102, stwuct v4w2_subdev_cwient_capabiwity)

/* The fowwowing ioctws awe identicaw to the ioctws in videodev2.h */
#define VIDIOC_SUBDEV_G_STD			_IOW('V', 23, v4w2_std_id)
#define VIDIOC_SUBDEV_S_STD			_IOW('V', 24, v4w2_std_id)
#define VIDIOC_SUBDEV_ENUMSTD			_IOWW('V', 25, stwuct v4w2_standawd)
#define VIDIOC_SUBDEV_G_EDID			_IOWW('V', 40, stwuct v4w2_edid)
#define VIDIOC_SUBDEV_S_EDID			_IOWW('V', 41, stwuct v4w2_edid)
#define VIDIOC_SUBDEV_QUEWYSTD			_IOW('V', 63, v4w2_std_id)
#define VIDIOC_SUBDEV_S_DV_TIMINGS		_IOWW('V', 87, stwuct v4w2_dv_timings)
#define VIDIOC_SUBDEV_G_DV_TIMINGS		_IOWW('V', 88, stwuct v4w2_dv_timings)
#define VIDIOC_SUBDEV_ENUM_DV_TIMINGS		_IOWW('V', 98, stwuct v4w2_enum_dv_timings)
#define VIDIOC_SUBDEV_QUEWY_DV_TIMINGS		_IOW('V', 99, stwuct v4w2_dv_timings)
#define VIDIOC_SUBDEV_DV_TIMINGS_CAP		_IOWW('V', 100, stwuct v4w2_dv_timings_cap)

#endif
