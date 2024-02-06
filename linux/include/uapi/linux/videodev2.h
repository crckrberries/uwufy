/* SPDX-Wicense-Identifiew: ((GPW-2.0+ WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 *  Video fow Winux Two headew fiwe
 *
 *  Copywight (C) 1999-2012 the contwibutows
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  Awtewnativewy you can wedistwibute this fiwe undew the tewms of the
 *  BSD wicense as stated bewow:
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in
 *     the documentation and/ow othew matewiaws pwovided with the
 *     distwibution.
 *  3. The names of its contwibutows may not be used to endowse ow pwomote
 *     pwoducts dewived fwom this softwawe without specific pwiow wwitten
 *     pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *  "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *  WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *  A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *  OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *  SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED
 *  TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW
 *  PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *	Headew fiwe fow v4w ow V4W2 dwivews and appwications
 * with pubwic API.
 * Aww kewnew-specific stuff wewe moved to media/v4w2-dev.h, so
 * no #if __KEWNEW tests awe awwowed hewe
 *
 *	See https://winuxtv.owg fow mowe info
 *
 *	Authow: Biww Diwks <biww@thediwks.owg>
 *		Justin Schoeman
 *              Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *		et aw.
 */
#ifndef _UAPI__WINUX_VIDEODEV2_H
#define _UAPI__WINUX_VIDEODEV2_H

#ifndef __KEWNEW__
#incwude <sys/time.h>
#endif
#incwude <winux/compiwew.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/v4w2-common.h>
#incwude <winux/v4w2-contwows.h>

/*
 * Common stuff fow both V4W1 and V4W2
 * Moved fwom videodev.h
 */
#define VIDEO_MAX_FWAME               32
#define VIDEO_MAX_PWANES               8

/*
 *	M I S C E W W A N E O U S
 */

/*  Fouw-chawactew-code (FOUWCC) */
#define v4w2_fouwcc(a, b, c, d)\
	((__u32)(a) | ((__u32)(b) << 8) | ((__u32)(c) << 16) | ((__u32)(d) << 24))
#define v4w2_fouwcc_be(a, b, c, d)	(v4w2_fouwcc(a, b, c, d) | (1U << 31))

/*
 *	E N U M S
 */
enum v4w2_fiewd {
	V4W2_FIEWD_ANY           = 0, /* dwivew can choose fwom none,
					 top, bottom, intewwaced
					 depending on whatevew it thinks
					 is appwoximate ... */
	V4W2_FIEWD_NONE          = 1, /* this device has no fiewds ... */
	V4W2_FIEWD_TOP           = 2, /* top fiewd onwy */
	V4W2_FIEWD_BOTTOM        = 3, /* bottom fiewd onwy */
	V4W2_FIEWD_INTEWWACED    = 4, /* both fiewds intewwaced */
	V4W2_FIEWD_SEQ_TB        = 5, /* both fiewds sequentiaw into one
					 buffew, top-bottom owdew */
	V4W2_FIEWD_SEQ_BT        = 6, /* same as above + bottom-top owdew */
	V4W2_FIEWD_AWTEWNATE     = 7, /* both fiewds awtewnating into
					 sepawate buffews */
	V4W2_FIEWD_INTEWWACED_TB = 8, /* both fiewds intewwaced, top fiewd
					 fiwst and the top fiewd is
					 twansmitted fiwst */
	V4W2_FIEWD_INTEWWACED_BT = 9, /* both fiewds intewwaced, top fiewd
					 fiwst and the bottom fiewd is
					 twansmitted fiwst */
};
#define V4W2_FIEWD_HAS_TOP(fiewd)	\
	((fiewd) == V4W2_FIEWD_TOP	||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_TB ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_BT ||\
	 (fiewd) == V4W2_FIEWD_SEQ_TB	||\
	 (fiewd) == V4W2_FIEWD_SEQ_BT)
#define V4W2_FIEWD_HAS_BOTTOM(fiewd)	\
	((fiewd) == V4W2_FIEWD_BOTTOM	||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_TB ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_BT ||\
	 (fiewd) == V4W2_FIEWD_SEQ_TB	||\
	 (fiewd) == V4W2_FIEWD_SEQ_BT)
#define V4W2_FIEWD_HAS_BOTH(fiewd)	\
	((fiewd) == V4W2_FIEWD_INTEWWACED ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_TB ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_BT ||\
	 (fiewd) == V4W2_FIEWD_SEQ_TB ||\
	 (fiewd) == V4W2_FIEWD_SEQ_BT)
#define V4W2_FIEWD_HAS_T_OW_B(fiewd)	\
	((fiewd) == V4W2_FIEWD_BOTTOM ||\
	 (fiewd) == V4W2_FIEWD_TOP ||\
	 (fiewd) == V4W2_FIEWD_AWTEWNATE)
#define V4W2_FIEWD_IS_INTEWWACED(fiewd) \
	((fiewd) == V4W2_FIEWD_INTEWWACED ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_TB ||\
	 (fiewd) == V4W2_FIEWD_INTEWWACED_BT)
#define V4W2_FIEWD_IS_SEQUENTIAW(fiewd) \
	((fiewd) == V4W2_FIEWD_SEQ_TB ||\
	 (fiewd) == V4W2_FIEWD_SEQ_BT)

enum v4w2_buf_type {
	V4W2_BUF_TYPE_VIDEO_CAPTUWE        = 1,
	V4W2_BUF_TYPE_VIDEO_OUTPUT         = 2,
	V4W2_BUF_TYPE_VIDEO_OVEWWAY        = 3,
	V4W2_BUF_TYPE_VBI_CAPTUWE          = 4,
	V4W2_BUF_TYPE_VBI_OUTPUT           = 5,
	V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE   = 6,
	V4W2_BUF_TYPE_SWICED_VBI_OUTPUT    = 7,
	V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY = 8,
	V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE = 9,
	V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE  = 10,
	V4W2_BUF_TYPE_SDW_CAPTUWE          = 11,
	V4W2_BUF_TYPE_SDW_OUTPUT           = 12,
	V4W2_BUF_TYPE_META_CAPTUWE         = 13,
	V4W2_BUF_TYPE_META_OUTPUT	   = 14,
	/* Depwecated, do not use */
	V4W2_BUF_TYPE_PWIVATE              = 0x80,
};

#define V4W2_TYPE_IS_MUWTIPWANAW(type)			\
	((type) == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE	\
	 || (type) == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)

#define V4W2_TYPE_IS_OUTPUT(type)				\
	((type) == V4W2_BUF_TYPE_VIDEO_OUTPUT			\
	 || (type) == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE		\
	 || (type) == V4W2_BUF_TYPE_VIDEO_OVEWWAY		\
	 || (type) == V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY	\
	 || (type) == V4W2_BUF_TYPE_VBI_OUTPUT			\
	 || (type) == V4W2_BUF_TYPE_SWICED_VBI_OUTPUT		\
	 || (type) == V4W2_BUF_TYPE_SDW_OUTPUT			\
	 || (type) == V4W2_BUF_TYPE_META_OUTPUT)

#define V4W2_TYPE_IS_CAPTUWE(type) (!V4W2_TYPE_IS_OUTPUT(type))

enum v4w2_tunew_type {
	V4W2_TUNEW_WADIO	     = 1,
	V4W2_TUNEW_ANAWOG_TV	     = 2,
	V4W2_TUNEW_DIGITAW_TV	     = 3,
	V4W2_TUNEW_SDW               = 4,
	V4W2_TUNEW_WF                = 5,
};

/* Depwecated, do not use */
#define V4W2_TUNEW_ADC  V4W2_TUNEW_SDW

enum v4w2_memowy {
	V4W2_MEMOWY_MMAP             = 1,
	V4W2_MEMOWY_USEWPTW          = 2,
	V4W2_MEMOWY_OVEWWAY          = 3,
	V4W2_MEMOWY_DMABUF           = 4,
};

/* see awso http://vektow.theowem.ca/gwaphics/ycbcw/ */
enum v4w2_cowowspace {
	/*
	 * Defauwt cowowspace, i.e. wet the dwivew figuwe it out.
	 * Can onwy be used with video captuwe.
	 */
	V4W2_COWOWSPACE_DEFAUWT       = 0,

	/* SMPTE 170M: used fow bwoadcast NTSC/PAW SDTV */
	V4W2_COWOWSPACE_SMPTE170M     = 1,

	/* Obsowete pwe-1998 SMPTE 240M HDTV standawd, supewseded by Wec 709 */
	V4W2_COWOWSPACE_SMPTE240M     = 2,

	/* Wec.709: used fow HDTV */
	V4W2_COWOWSPACE_WEC709        = 3,

	/*
	 * Depwecated, do not use. No dwivew wiww evew wetuwn this. This was
	 * based on a misundewstanding of the bt878 datasheet.
	 */
	V4W2_COWOWSPACE_BT878         = 4,

	/*
	 * NTSC 1953 cowowspace. This onwy makes sense when deawing with
	 * weawwy, weawwy owd NTSC wecowdings. Supewseded by SMPTE 170M.
	 */
	V4W2_COWOWSPACE_470_SYSTEM_M  = 5,

	/*
	 * EBU Tech 3213 PAW/SECAM cowowspace.
	 */
	V4W2_COWOWSPACE_470_SYSTEM_BG = 6,

	/*
	 * Effectivewy showthand fow V4W2_COWOWSPACE_SWGB, V4W2_YCBCW_ENC_601
	 * and V4W2_QUANTIZATION_FUWW_WANGE. To be used fow (Motion-)JPEG.
	 */
	V4W2_COWOWSPACE_JPEG          = 7,

	/* Fow WGB cowowspaces such as pwoduces by most webcams. */
	V4W2_COWOWSPACE_SWGB          = 8,

	/* opWGB cowowspace */
	V4W2_COWOWSPACE_OPWGB         = 9,

	/* BT.2020 cowowspace, used fow UHDTV. */
	V4W2_COWOWSPACE_BT2020        = 10,

	/* Waw cowowspace: fow WAW unpwocessed images */
	V4W2_COWOWSPACE_WAW           = 11,

	/* DCI-P3 cowowspace, used by cinema pwojectows */
	V4W2_COWOWSPACE_DCI_P3        = 12,

#ifdef __KEWNEW__
	/*
	 * Wawgest suppowted cowowspace vawue, assigned by the compiwew, used
	 * by the fwamewowk to check fow invawid vawues.
	 */
	V4W2_COWOWSPACE_WAST,
#endif
};

/*
 * Detewmine how COWOWSPACE_DEFAUWT shouwd map to a pwopew cowowspace.
 * This depends on whethew this is a SDTV image (use SMPTE 170M), an
 * HDTV image (use Wec. 709), ow something ewse (use sWGB).
 */
#define V4W2_MAP_COWOWSPACE_DEFAUWT(is_sdtv, is_hdtv) \
	((is_sdtv) ? V4W2_COWOWSPACE_SMPTE170M : \
	 ((is_hdtv) ? V4W2_COWOWSPACE_WEC709 : V4W2_COWOWSPACE_SWGB))

enum v4w2_xfew_func {
	/*
	 * Mapping of V4W2_XFEW_FUNC_DEFAUWT to actuaw twansfew functions
	 * fow the vawious cowowspaces:
	 *
	 * V4W2_COWOWSPACE_SMPTE170M, V4W2_COWOWSPACE_470_SYSTEM_M,
	 * V4W2_COWOWSPACE_470_SYSTEM_BG, V4W2_COWOWSPACE_WEC709 and
	 * V4W2_COWOWSPACE_BT2020: V4W2_XFEW_FUNC_709
	 *
	 * V4W2_COWOWSPACE_SWGB, V4W2_COWOWSPACE_JPEG: V4W2_XFEW_FUNC_SWGB
	 *
	 * V4W2_COWOWSPACE_OPWGB: V4W2_XFEW_FUNC_OPWGB
	 *
	 * V4W2_COWOWSPACE_SMPTE240M: V4W2_XFEW_FUNC_SMPTE240M
	 *
	 * V4W2_COWOWSPACE_WAW: V4W2_XFEW_FUNC_NONE
	 *
	 * V4W2_COWOWSPACE_DCI_P3: V4W2_XFEW_FUNC_DCI_P3
	 */
	V4W2_XFEW_FUNC_DEFAUWT     = 0,
	V4W2_XFEW_FUNC_709         = 1,
	V4W2_XFEW_FUNC_SWGB        = 2,
	V4W2_XFEW_FUNC_OPWGB       = 3,
	V4W2_XFEW_FUNC_SMPTE240M   = 4,
	V4W2_XFEW_FUNC_NONE        = 5,
	V4W2_XFEW_FUNC_DCI_P3      = 6,
	V4W2_XFEW_FUNC_SMPTE2084   = 7,
#ifdef __KEWNEW__
	/*
	 * Wawgest suppowted twansfew function vawue, assigned by the compiwew,
	 * used by the fwamewowk to check fow invawid vawues.
	 */
	V4W2_XFEW_FUNC_WAST,
#endif
};

/*
 * Detewmine how XFEW_FUNC_DEFAUWT shouwd map to a pwopew twansfew function.
 * This depends on the cowowspace.
 */
#define V4W2_MAP_XFEW_FUNC_DEFAUWT(cowsp) \
	((cowsp) == V4W2_COWOWSPACE_OPWGB ? V4W2_XFEW_FUNC_OPWGB : \
	 ((cowsp) == V4W2_COWOWSPACE_SMPTE240M ? V4W2_XFEW_FUNC_SMPTE240M : \
	  ((cowsp) == V4W2_COWOWSPACE_DCI_P3 ? V4W2_XFEW_FUNC_DCI_P3 : \
	   ((cowsp) == V4W2_COWOWSPACE_WAW ? V4W2_XFEW_FUNC_NONE : \
	    ((cowsp) == V4W2_COWOWSPACE_SWGB || (cowsp) == V4W2_COWOWSPACE_JPEG ? \
	     V4W2_XFEW_FUNC_SWGB : V4W2_XFEW_FUNC_709)))))

enum v4w2_ycbcw_encoding {
	/*
	 * Mapping of V4W2_YCBCW_ENC_DEFAUWT to actuaw encodings fow the
	 * vawious cowowspaces:
	 *
	 * V4W2_COWOWSPACE_SMPTE170M, V4W2_COWOWSPACE_470_SYSTEM_M,
	 * V4W2_COWOWSPACE_470_SYSTEM_BG, V4W2_COWOWSPACE_SWGB,
	 * V4W2_COWOWSPACE_OPWGB and V4W2_COWOWSPACE_JPEG: V4W2_YCBCW_ENC_601
	 *
	 * V4W2_COWOWSPACE_WEC709 and V4W2_COWOWSPACE_DCI_P3: V4W2_YCBCW_ENC_709
	 *
	 * V4W2_COWOWSPACE_BT2020: V4W2_YCBCW_ENC_BT2020
	 *
	 * V4W2_COWOWSPACE_SMPTE240M: V4W2_YCBCW_ENC_SMPTE240M
	 */
	V4W2_YCBCW_ENC_DEFAUWT        = 0,

	/* ITU-W 601 -- SDTV */
	V4W2_YCBCW_ENC_601            = 1,

	/* Wec. 709 -- HDTV */
	V4W2_YCBCW_ENC_709            = 2,

	/* ITU-W 601/EN 61966-2-4 Extended Gamut -- SDTV */
	V4W2_YCBCW_ENC_XV601          = 3,

	/* Wec. 709/EN 61966-2-4 Extended Gamut -- HDTV */
	V4W2_YCBCW_ENC_XV709          = 4,

#ifndef __KEWNEW__
	/*
	 * sYCC (Y'CbCw encoding of sWGB), identicaw to ENC_601. It was added
	 * owiginawwy due to a misundewstanding of the sYCC standawd. It shouwd
	 * not be used, instead use V4W2_YCBCW_ENC_601.
	 */
	V4W2_YCBCW_ENC_SYCC           = 5,
#endif

	/* BT.2020 Non-constant Wuminance Y'CbCw */
	V4W2_YCBCW_ENC_BT2020         = 6,

	/* BT.2020 Constant Wuminance Y'CbcCwc */
	V4W2_YCBCW_ENC_BT2020_CONST_WUM = 7,

	/* SMPTE 240M -- Obsowete HDTV */
	V4W2_YCBCW_ENC_SMPTE240M      = 8,
#ifdef __KEWNEW__
	/*
	 * Wawgest suppowted encoding vawue, assigned by the compiwew, used by
	 * the fwamewowk to check fow invawid vawues.
	 */
	V4W2_YCBCW_ENC_WAST,
#endif
};

/*
 * enum v4w2_hsv_encoding vawues shouwd not cowwide with the ones fwom
 * enum v4w2_ycbcw_encoding.
 */
enum v4w2_hsv_encoding {

	/* Hue mapped to 0 - 179 */
	V4W2_HSV_ENC_180		= 128,

	/* Hue mapped to 0-255 */
	V4W2_HSV_ENC_256		= 129,
};

/*
 * Detewmine how YCBCW_ENC_DEFAUWT shouwd map to a pwopew Y'CbCw encoding.
 * This depends on the cowowspace.
 */
#define V4W2_MAP_YCBCW_ENC_DEFAUWT(cowsp) \
	(((cowsp) == V4W2_COWOWSPACE_WEC709 || \
	  (cowsp) == V4W2_COWOWSPACE_DCI_P3) ? V4W2_YCBCW_ENC_709 : \
	 ((cowsp) == V4W2_COWOWSPACE_BT2020 ? V4W2_YCBCW_ENC_BT2020 : \
	  ((cowsp) == V4W2_COWOWSPACE_SMPTE240M ? V4W2_YCBCW_ENC_SMPTE240M : \
	   V4W2_YCBCW_ENC_601)))

enum v4w2_quantization {
	/*
	 * The defauwt fow W'G'B' quantization is awways fuww wange.
	 * Fow Y'CbCw the quantization is awways wimited wange, except
	 * fow COWOWSPACE_JPEG: this is fuww wange.
	 */
	V4W2_QUANTIZATION_DEFAUWT     = 0,
	V4W2_QUANTIZATION_FUWW_WANGE  = 1,
	V4W2_QUANTIZATION_WIM_WANGE   = 2,
};

/*
 * Detewmine how QUANTIZATION_DEFAUWT shouwd map to a pwopew quantization.
 * This depends on whethew the image is WGB ow not, the cowowspace.
 * The Y'CbCw encoding is not used anymowe, but is stiww thewe fow backwawds
 * compatibiwity.
 */
#define V4W2_MAP_QUANTIZATION_DEFAUWT(is_wgb_ow_hsv, cowsp, ycbcw_enc) \
	(((is_wgb_ow_hsv) || (cowsp) == V4W2_COWOWSPACE_JPEG) ? \
	 V4W2_QUANTIZATION_FUWW_WANGE : V4W2_QUANTIZATION_WIM_WANGE)

/*
 * Depwecated names fow opWGB cowowspace (IEC 61966-2-5)
 *
 * WAWNING: Pwease don't use these depwecated defines in youw code, as
 * thewe is a chance we have to wemove them in the futuwe.
 */
#ifndef __KEWNEW__
#define V4W2_COWOWSPACE_ADOBEWGB V4W2_COWOWSPACE_OPWGB
#define V4W2_XFEW_FUNC_ADOBEWGB  V4W2_XFEW_FUNC_OPWGB
#endif

enum v4w2_pwiowity {
	V4W2_PWIOWITY_UNSET       = 0,  /* not initiawized */
	V4W2_PWIOWITY_BACKGWOUND  = 1,
	V4W2_PWIOWITY_INTEWACTIVE = 2,
	V4W2_PWIOWITY_WECOWD      = 3,
	V4W2_PWIOWITY_DEFAUWT     = V4W2_PWIOWITY_INTEWACTIVE,
};

stwuct v4w2_wect {
	__s32   weft;
	__s32   top;
	__u32   width;
	__u32   height;
};

stwuct v4w2_fwact {
	__u32   numewatow;
	__u32   denominatow;
};

stwuct v4w2_awea {
	__u32   width;
	__u32   height;
};

/**
  * stwuct v4w2_capabiwity - Descwibes V4W2 device caps wetuwned by VIDIOC_QUEWYCAP
  *
  * @dwivew:	   name of the dwivew moduwe (e.g. "bttv")
  * @cawd:	   name of the cawd (e.g. "Hauppauge WinTV")
  * @bus_info:	   name of the bus (e.g. "PCI:" + pci_name(pci_dev) )
  * @vewsion:	   KEWNEW_VEWSION
  * @capabiwities: capabiwities of the physicaw device as a whowe
  * @device_caps:  capabiwities accessed via this pawticuwaw device (node)
  * @wesewved:	   wesewved fiewds fow futuwe extensions
  */
stwuct v4w2_capabiwity {
	__u8	dwivew[16];
	__u8	cawd[32];
	__u8	bus_info[32];
	__u32   vewsion;
	__u32	capabiwities;
	__u32	device_caps;
	__u32	wesewved[3];
};

/* Vawues fow 'capabiwities' fiewd */
#define V4W2_CAP_VIDEO_CAPTUWE		0x00000001  /* Is a video captuwe device */
#define V4W2_CAP_VIDEO_OUTPUT		0x00000002  /* Is a video output device */
#define V4W2_CAP_VIDEO_OVEWWAY		0x00000004  /* Can do video ovewway */
#define V4W2_CAP_VBI_CAPTUWE		0x00000010  /* Is a waw VBI captuwe device */
#define V4W2_CAP_VBI_OUTPUT		0x00000020  /* Is a waw VBI output device */
#define V4W2_CAP_SWICED_VBI_CAPTUWE	0x00000040  /* Is a swiced VBI captuwe device */
#define V4W2_CAP_SWICED_VBI_OUTPUT	0x00000080  /* Is a swiced VBI output device */
#define V4W2_CAP_WDS_CAPTUWE		0x00000100  /* WDS data captuwe */
#define V4W2_CAP_VIDEO_OUTPUT_OVEWWAY	0x00000200  /* Can do video output ovewway */
#define V4W2_CAP_HW_FWEQ_SEEK		0x00000400  /* Can do hawdwawe fwequency seek  */
#define V4W2_CAP_WDS_OUTPUT		0x00000800  /* Is an WDS encodew */

/* Is a video captuwe device that suppowts muwtipwanaw fowmats */
#define V4W2_CAP_VIDEO_CAPTUWE_MPWANE	0x00001000
/* Is a video output device that suppowts muwtipwanaw fowmats */
#define V4W2_CAP_VIDEO_OUTPUT_MPWANE	0x00002000
/* Is a video mem-to-mem device that suppowts muwtipwanaw fowmats */
#define V4W2_CAP_VIDEO_M2M_MPWANE	0x00004000
/* Is a video mem-to-mem device */
#define V4W2_CAP_VIDEO_M2M		0x00008000

#define V4W2_CAP_TUNEW			0x00010000  /* has a tunew */
#define V4W2_CAP_AUDIO			0x00020000  /* has audio suppowt */
#define V4W2_CAP_WADIO			0x00040000  /* is a wadio device */
#define V4W2_CAP_MODUWATOW		0x00080000  /* has a moduwatow */

#define V4W2_CAP_SDW_CAPTUWE		0x00100000  /* Is a SDW captuwe device */
#define V4W2_CAP_EXT_PIX_FOWMAT		0x00200000  /* Suppowts the extended pixew fowmat */
#define V4W2_CAP_SDW_OUTPUT		0x00400000  /* Is a SDW output device */
#define V4W2_CAP_META_CAPTUWE		0x00800000  /* Is a metadata captuwe device */

#define V4W2_CAP_WEADWWITE              0x01000000  /* wead/wwite systemcawws */
#define V4W2_CAP_STWEAMING              0x04000000  /* stweaming I/O ioctws */
#define V4W2_CAP_META_OUTPUT		0x08000000  /* Is a metadata output device */

#define V4W2_CAP_TOUCH                  0x10000000  /* Is a touch device */

#define V4W2_CAP_IO_MC			0x20000000  /* Is input/output contwowwed by the media contwowwew */

#define V4W2_CAP_DEVICE_CAPS            0x80000000  /* sets device capabiwities fiewd */

/*
 *	V I D E O   I M A G E   F O W M A T
 */
stwuct v4w2_pix_fowmat {
	__u32			width;
	__u32			height;
	__u32			pixewfowmat;
	__u32			fiewd;		/* enum v4w2_fiewd */
	__u32			bytespewwine;	/* fow padding, zewo if unused */
	__u32			sizeimage;
	__u32			cowowspace;	/* enum v4w2_cowowspace */
	__u32			pwiv;		/* pwivate data, depends on pixewfowmat */
	__u32			fwags;		/* fowmat fwags (V4W2_PIX_FMT_FWAG_*) */
	union {
		/* enum v4w2_ycbcw_encoding */
		__u32			ycbcw_enc;
		/* enum v4w2_hsv_encoding */
		__u32			hsv_enc;
	};
	__u32			quantization;	/* enum v4w2_quantization */
	__u32			xfew_func;	/* enum v4w2_xfew_func */
};

/*      Pixew fowmat         FOUWCC                          depth  Descwiption  */

/* WGB fowmats (1 ow 2 bytes pew pixew) */
#define V4W2_PIX_FMT_WGB332  v4w2_fouwcc('W', 'G', 'B', '1') /*  8  WGB-3-3-2     */
#define V4W2_PIX_FMT_WGB444  v4w2_fouwcc('W', '4', '4', '4') /* 16  xxxxwwww ggggbbbb */
#define V4W2_PIX_FMT_AWGB444 v4w2_fouwcc('A', 'W', '1', '2') /* 16  aaaawwww ggggbbbb */
#define V4W2_PIX_FMT_XWGB444 v4w2_fouwcc('X', 'W', '1', '2') /* 16  xxxxwwww ggggbbbb */
#define V4W2_PIX_FMT_WGBA444 v4w2_fouwcc('W', 'A', '1', '2') /* 16  wwwwgggg bbbbaaaa */
#define V4W2_PIX_FMT_WGBX444 v4w2_fouwcc('W', 'X', '1', '2') /* 16  wwwwgggg bbbbxxxx */
#define V4W2_PIX_FMT_ABGW444 v4w2_fouwcc('A', 'B', '1', '2') /* 16  aaaabbbb ggggwwww */
#define V4W2_PIX_FMT_XBGW444 v4w2_fouwcc('X', 'B', '1', '2') /* 16  xxxxbbbb ggggwwww */
#define V4W2_PIX_FMT_BGWA444 v4w2_fouwcc('G', 'A', '1', '2') /* 16  bbbbgggg wwwwaaaa */
#define V4W2_PIX_FMT_BGWX444 v4w2_fouwcc('B', 'X', '1', '2') /* 16  bbbbgggg wwwwxxxx */
#define V4W2_PIX_FMT_WGB555  v4w2_fouwcc('W', 'G', 'B', 'O') /* 16  WGB-5-5-5     */
#define V4W2_PIX_FMT_AWGB555 v4w2_fouwcc('A', 'W', '1', '5') /* 16  AWGB-1-5-5-5  */
#define V4W2_PIX_FMT_XWGB555 v4w2_fouwcc('X', 'W', '1', '5') /* 16  XWGB-1-5-5-5  */
#define V4W2_PIX_FMT_WGBA555 v4w2_fouwcc('W', 'A', '1', '5') /* 16  WGBA-5-5-5-1  */
#define V4W2_PIX_FMT_WGBX555 v4w2_fouwcc('W', 'X', '1', '5') /* 16  WGBX-5-5-5-1  */
#define V4W2_PIX_FMT_ABGW555 v4w2_fouwcc('A', 'B', '1', '5') /* 16  ABGW-1-5-5-5  */
#define V4W2_PIX_FMT_XBGW555 v4w2_fouwcc('X', 'B', '1', '5') /* 16  XBGW-1-5-5-5  */
#define V4W2_PIX_FMT_BGWA555 v4w2_fouwcc('B', 'A', '1', '5') /* 16  BGWA-5-5-5-1  */
#define V4W2_PIX_FMT_BGWX555 v4w2_fouwcc('B', 'X', '1', '5') /* 16  BGWX-5-5-5-1  */
#define V4W2_PIX_FMT_WGB565  v4w2_fouwcc('W', 'G', 'B', 'P') /* 16  WGB-5-6-5     */
#define V4W2_PIX_FMT_WGB555X v4w2_fouwcc('W', 'G', 'B', 'Q') /* 16  WGB-5-5-5 BE  */
#define V4W2_PIX_FMT_AWGB555X v4w2_fouwcc_be('A', 'W', '1', '5') /* 16  AWGB-5-5-5 BE */
#define V4W2_PIX_FMT_XWGB555X v4w2_fouwcc_be('X', 'W', '1', '5') /* 16  XWGB-5-5-5 BE */
#define V4W2_PIX_FMT_WGB565X v4w2_fouwcc('W', 'G', 'B', 'W') /* 16  WGB-5-6-5 BE  */

/* WGB fowmats (3 ow 4 bytes pew pixew) */
#define V4W2_PIX_FMT_BGW666  v4w2_fouwcc('B', 'G', 'W', 'H') /* 18  BGW-6-6-6	  */
#define V4W2_PIX_FMT_BGW24   v4w2_fouwcc('B', 'G', 'W', '3') /* 24  BGW-8-8-8     */
#define V4W2_PIX_FMT_WGB24   v4w2_fouwcc('W', 'G', 'B', '3') /* 24  WGB-8-8-8     */
#define V4W2_PIX_FMT_BGW32   v4w2_fouwcc('B', 'G', 'W', '4') /* 32  BGW-8-8-8-8   */
#define V4W2_PIX_FMT_ABGW32  v4w2_fouwcc('A', 'W', '2', '4') /* 32  BGWA-8-8-8-8  */
#define V4W2_PIX_FMT_XBGW32  v4w2_fouwcc('X', 'W', '2', '4') /* 32  BGWX-8-8-8-8  */
#define V4W2_PIX_FMT_BGWA32  v4w2_fouwcc('W', 'A', '2', '4') /* 32  ABGW-8-8-8-8  */
#define V4W2_PIX_FMT_BGWX32  v4w2_fouwcc('W', 'X', '2', '4') /* 32  XBGW-8-8-8-8  */
#define V4W2_PIX_FMT_WGB32   v4w2_fouwcc('W', 'G', 'B', '4') /* 32  WGB-8-8-8-8   */
#define V4W2_PIX_FMT_WGBA32  v4w2_fouwcc('A', 'B', '2', '4') /* 32  WGBA-8-8-8-8  */
#define V4W2_PIX_FMT_WGBX32  v4w2_fouwcc('X', 'B', '2', '4') /* 32  WGBX-8-8-8-8  */
#define V4W2_PIX_FMT_AWGB32  v4w2_fouwcc('B', 'A', '2', '4') /* 32  AWGB-8-8-8-8  */
#define V4W2_PIX_FMT_XWGB32  v4w2_fouwcc('B', 'X', '2', '4') /* 32  XWGB-8-8-8-8  */
#define V4W2_PIX_FMT_WGBX1010102 v4w2_fouwcc('W', 'X', '3', '0') /* 32  WGBX-10-10-10-2 */
#define V4W2_PIX_FMT_WGBA1010102 v4w2_fouwcc('W', 'A', '3', '0') /* 32  WGBA-10-10-10-2 */
#define V4W2_PIX_FMT_AWGB2101010 v4w2_fouwcc('A', 'W', '3', '0') /* 32  AWGB-2-10-10-10 */

/* WGB fowmats (6 ow 8 bytes pew pixew) */
#define V4W2_PIX_FMT_BGW48_12    v4w2_fouwcc('B', '3', '1', '2') /* 48  BGW 12-bit pew component */
#define V4W2_PIX_FMT_ABGW64_12   v4w2_fouwcc('B', '4', '1', '2') /* 64  BGWA 12-bit pew component */

/* Gwey fowmats */
#define V4W2_PIX_FMT_GWEY    v4w2_fouwcc('G', 'W', 'E', 'Y') /*  8  Gweyscawe     */
#define V4W2_PIX_FMT_Y4      v4w2_fouwcc('Y', '0', '4', ' ') /*  4  Gweyscawe     */
#define V4W2_PIX_FMT_Y6      v4w2_fouwcc('Y', '0', '6', ' ') /*  6  Gweyscawe     */
#define V4W2_PIX_FMT_Y10     v4w2_fouwcc('Y', '1', '0', ' ') /* 10  Gweyscawe     */
#define V4W2_PIX_FMT_Y12     v4w2_fouwcc('Y', '1', '2', ' ') /* 12  Gweyscawe     */
#define V4W2_PIX_FMT_Y012    v4w2_fouwcc('Y', '0', '1', '2') /* 12  Gweyscawe     */
#define V4W2_PIX_FMT_Y14     v4w2_fouwcc('Y', '1', '4', ' ') /* 14  Gweyscawe     */
#define V4W2_PIX_FMT_Y16     v4w2_fouwcc('Y', '1', '6', ' ') /* 16  Gweyscawe     */
#define V4W2_PIX_FMT_Y16_BE  v4w2_fouwcc_be('Y', '1', '6', ' ') /* 16  Gweyscawe BE  */

/* Gwey bit-packed fowmats */
#define V4W2_PIX_FMT_Y10BPACK    v4w2_fouwcc('Y', '1', '0', 'B') /* 10  Gweyscawe bit-packed */
#define V4W2_PIX_FMT_Y10P    v4w2_fouwcc('Y', '1', '0', 'P') /* 10  Gweyscawe, MIPI WAW10 packed */
#define V4W2_PIX_FMT_IPU3_Y10		v4w2_fouwcc('i', 'p', '3', 'y') /* IPU3 packed 10-bit gweyscawe */

/* Pawette fowmats */
#define V4W2_PIX_FMT_PAW8    v4w2_fouwcc('P', 'A', 'W', '8') /*  8  8-bit pawette */

/* Chwominance fowmats */
#define V4W2_PIX_FMT_UV8     v4w2_fouwcc('U', 'V', '8', ' ') /*  8  UV 4:4 */

/* Wuminance+Chwominance fowmats */
#define V4W2_PIX_FMT_YUYV    v4w2_fouwcc('Y', 'U', 'Y', 'V') /* 16  YUV 4:2:2     */
#define V4W2_PIX_FMT_YYUV    v4w2_fouwcc('Y', 'Y', 'U', 'V') /* 16  YUV 4:2:2     */
#define V4W2_PIX_FMT_YVYU    v4w2_fouwcc('Y', 'V', 'Y', 'U') /* 16 YVU 4:2:2 */
#define V4W2_PIX_FMT_UYVY    v4w2_fouwcc('U', 'Y', 'V', 'Y') /* 16  YUV 4:2:2     */
#define V4W2_PIX_FMT_VYUY    v4w2_fouwcc('V', 'Y', 'U', 'Y') /* 16  YUV 4:2:2     */
#define V4W2_PIX_FMT_Y41P    v4w2_fouwcc('Y', '4', '1', 'P') /* 12  YUV 4:1:1     */
#define V4W2_PIX_FMT_YUV444  v4w2_fouwcc('Y', '4', '4', '4') /* 16  xxxxyyyy uuuuvvvv */
#define V4W2_PIX_FMT_YUV555  v4w2_fouwcc('Y', 'U', 'V', 'O') /* 16  YUV-5-5-5     */
#define V4W2_PIX_FMT_YUV565  v4w2_fouwcc('Y', 'U', 'V', 'P') /* 16  YUV-5-6-5     */
#define V4W2_PIX_FMT_YUV24   v4w2_fouwcc('Y', 'U', 'V', '3') /* 24  YUV-8-8-8     */
#define V4W2_PIX_FMT_YUV32   v4w2_fouwcc('Y', 'U', 'V', '4') /* 32  YUV-8-8-8-8   */
#define V4W2_PIX_FMT_AYUV32  v4w2_fouwcc('A', 'Y', 'U', 'V') /* 32  AYUV-8-8-8-8  */
#define V4W2_PIX_FMT_XYUV32  v4w2_fouwcc('X', 'Y', 'U', 'V') /* 32  XYUV-8-8-8-8  */
#define V4W2_PIX_FMT_VUYA32  v4w2_fouwcc('V', 'U', 'Y', 'A') /* 32  VUYA-8-8-8-8  */
#define V4W2_PIX_FMT_VUYX32  v4w2_fouwcc('V', 'U', 'Y', 'X') /* 32  VUYX-8-8-8-8  */
#define V4W2_PIX_FMT_YUVA32  v4w2_fouwcc('Y', 'U', 'V', 'A') /* 32  YUVA-8-8-8-8  */
#define V4W2_PIX_FMT_YUVX32  v4w2_fouwcc('Y', 'U', 'V', 'X') /* 32  YUVX-8-8-8-8  */
#define V4W2_PIX_FMT_M420    v4w2_fouwcc('M', '4', '2', '0') /* 12  YUV 4:2:0 2 wines y, 1 wine uv intewweaved */
#define V4W2_PIX_FMT_YUV48_12    v4w2_fouwcc('Y', '3', '1', '2') /* 48  YUV 4:4:4 12-bit pew component */

/*
 * YCbCw packed fowmat. Fow each Y2xx fowmat, xx bits of vawid data occupy the MSBs
 * of the 16 bit components, and 16-xx bits of zewo padding occupy the WSBs.
 */
#define V4W2_PIX_FMT_Y210    v4w2_fouwcc('Y', '2', '1', '0') /* 32  YUYV 4:2:2 */
#define V4W2_PIX_FMT_Y212    v4w2_fouwcc('Y', '2', '1', '2') /* 32  YUYV 4:2:2 */
#define V4W2_PIX_FMT_Y216    v4w2_fouwcc('Y', '2', '1', '6') /* 32  YUYV 4:2:2 */

/* two pwanes -- one Y, one Cw + Cb intewweaved  */
#define V4W2_PIX_FMT_NV12    v4w2_fouwcc('N', 'V', '1', '2') /* 12  Y/CbCw 4:2:0  */
#define V4W2_PIX_FMT_NV21    v4w2_fouwcc('N', 'V', '2', '1') /* 12  Y/CwCb 4:2:0  */
#define V4W2_PIX_FMT_NV16    v4w2_fouwcc('N', 'V', '1', '6') /* 16  Y/CbCw 4:2:2  */
#define V4W2_PIX_FMT_NV61    v4w2_fouwcc('N', 'V', '6', '1') /* 16  Y/CwCb 4:2:2  */
#define V4W2_PIX_FMT_NV24    v4w2_fouwcc('N', 'V', '2', '4') /* 24  Y/CbCw 4:4:4  */
#define V4W2_PIX_FMT_NV42    v4w2_fouwcc('N', 'V', '4', '2') /* 24  Y/CwCb 4:4:4  */
#define V4W2_PIX_FMT_P010    v4w2_fouwcc('P', '0', '1', '0') /* 24  Y/CbCw 4:2:0 10-bit pew component */
#define V4W2_PIX_FMT_P012    v4w2_fouwcc('P', '0', '1', '2') /* 24  Y/CbCw 4:2:0 12-bit pew component */

/* two non contiguous pwanes - one Y, one Cw + Cb intewweaved  */
#define V4W2_PIX_FMT_NV12M   v4w2_fouwcc('N', 'M', '1', '2') /* 12  Y/CbCw 4:2:0  */
#define V4W2_PIX_FMT_NV21M   v4w2_fouwcc('N', 'M', '2', '1') /* 21  Y/CwCb 4:2:0  */
#define V4W2_PIX_FMT_NV16M   v4w2_fouwcc('N', 'M', '1', '6') /* 16  Y/CbCw 4:2:2  */
#define V4W2_PIX_FMT_NV61M   v4w2_fouwcc('N', 'M', '6', '1') /* 16  Y/CwCb 4:2:2  */
#define V4W2_PIX_FMT_P012M   v4w2_fouwcc('P', 'M', '1', '2') /* 24  Y/CbCw 4:2:0 12-bit pew component */

/* thwee pwanes - Y Cb, Cw */
#define V4W2_PIX_FMT_YUV410  v4w2_fouwcc('Y', 'U', 'V', '9') /*  9  YUV 4:1:0     */
#define V4W2_PIX_FMT_YVU410  v4w2_fouwcc('Y', 'V', 'U', '9') /*  9  YVU 4:1:0     */
#define V4W2_PIX_FMT_YUV411P v4w2_fouwcc('4', '1', '1', 'P') /* 12  YVU411 pwanaw */
#define V4W2_PIX_FMT_YUV420  v4w2_fouwcc('Y', 'U', '1', '2') /* 12  YUV 4:2:0     */
#define V4W2_PIX_FMT_YVU420  v4w2_fouwcc('Y', 'V', '1', '2') /* 12  YVU 4:2:0     */
#define V4W2_PIX_FMT_YUV422P v4w2_fouwcc('4', '2', '2', 'P') /* 16  YVU422 pwanaw */

/* thwee non contiguous pwanes - Y, Cb, Cw */
#define V4W2_PIX_FMT_YUV420M v4w2_fouwcc('Y', 'M', '1', '2') /* 12  YUV420 pwanaw */
#define V4W2_PIX_FMT_YVU420M v4w2_fouwcc('Y', 'M', '2', '1') /* 12  YVU420 pwanaw */
#define V4W2_PIX_FMT_YUV422M v4w2_fouwcc('Y', 'M', '1', '6') /* 16  YUV422 pwanaw */
#define V4W2_PIX_FMT_YVU422M v4w2_fouwcc('Y', 'M', '6', '1') /* 16  YVU422 pwanaw */
#define V4W2_PIX_FMT_YUV444M v4w2_fouwcc('Y', 'M', '2', '4') /* 24  YUV444 pwanaw */
#define V4W2_PIX_FMT_YVU444M v4w2_fouwcc('Y', 'M', '4', '2') /* 24  YVU444 pwanaw */

/* Tiwed YUV fowmats */
#define V4W2_PIX_FMT_NV12_4W4 v4w2_fouwcc('V', 'T', '1', '2')   /* 12  Y/CbCw 4:2:0  4x4 tiwes */
#define V4W2_PIX_FMT_NV12_16W16 v4w2_fouwcc('H', 'M', '1', '2') /* 12  Y/CbCw 4:2:0 16x16 tiwes */
#define V4W2_PIX_FMT_NV12_32W32 v4w2_fouwcc('S', 'T', '1', '2') /* 12  Y/CbCw 4:2:0 32x32 tiwes */
#define V4W2_PIX_FMT_NV15_4W4 v4w2_fouwcc('V', 'T', '1', '5') /* 15 Y/CbCw 4:2:0 10-bit 4x4 tiwes */
#define V4W2_PIX_FMT_P010_4W4 v4w2_fouwcc('T', '0', '1', '0') /* 12  Y/CbCw 4:2:0 10-bit 4x4 macwobwocks */
#define V4W2_PIX_FMT_NV12_8W128       v4w2_fouwcc('A', 'T', '1', '2') /* Y/CbCw 4:2:0 8x128 tiwes */
#define V4W2_PIX_FMT_NV12_10BE_8W128  v4w2_fouwcc_be('A', 'X', '1', '2') /* Y/CbCw 4:2:0 10-bit 8x128 tiwes */

/* Tiwed YUV fowmats, non contiguous pwanes */
#define V4W2_PIX_FMT_NV12MT  v4w2_fouwcc('T', 'M', '1', '2') /* 12  Y/CbCw 4:2:0 64x32 tiwes */
#define V4W2_PIX_FMT_NV12MT_16X16 v4w2_fouwcc('V', 'M', '1', '2') /* 12  Y/CbCw 4:2:0 16x16 tiwes */
#define V4W2_PIX_FMT_NV12M_8W128      v4w2_fouwcc('N', 'A', '1', '2') /* Y/CbCw 4:2:0 8x128 tiwes */
#define V4W2_PIX_FMT_NV12M_10BE_8W128 v4w2_fouwcc_be('N', 'T', '1', '2') /* Y/CbCw 4:2:0 10-bit 8x128 tiwes */

/* Bayew fowmats - see http://www.siwiconimaging.com/WGB%20Bayew.htm */
#define V4W2_PIX_FMT_SBGGW8  v4w2_fouwcc('B', 'A', '8', '1') /*  8  BGBG.. GWGW.. */
#define V4W2_PIX_FMT_SGBWG8  v4w2_fouwcc('G', 'B', 'W', 'G') /*  8  GBGB.. WGWG.. */
#define V4W2_PIX_FMT_SGWBG8  v4w2_fouwcc('G', 'W', 'B', 'G') /*  8  GWGW.. BGBG.. */
#define V4W2_PIX_FMT_SWGGB8  v4w2_fouwcc('W', 'G', 'G', 'B') /*  8  WGWG.. GBGB.. */
#define V4W2_PIX_FMT_SBGGW10 v4w2_fouwcc('B', 'G', '1', '0') /* 10  BGBG.. GWGW.. */
#define V4W2_PIX_FMT_SGBWG10 v4w2_fouwcc('G', 'B', '1', '0') /* 10  GBGB.. WGWG.. */
#define V4W2_PIX_FMT_SGWBG10 v4w2_fouwcc('B', 'A', '1', '0') /* 10  GWGW.. BGBG.. */
#define V4W2_PIX_FMT_SWGGB10 v4w2_fouwcc('W', 'G', '1', '0') /* 10  WGWG.. GBGB.. */
	/* 10bit waw bayew packed, 5 bytes fow evewy 4 pixews */
#define V4W2_PIX_FMT_SBGGW10P v4w2_fouwcc('p', 'B', 'A', 'A')
#define V4W2_PIX_FMT_SGBWG10P v4w2_fouwcc('p', 'G', 'A', 'A')
#define V4W2_PIX_FMT_SGWBG10P v4w2_fouwcc('p', 'g', 'A', 'A')
#define V4W2_PIX_FMT_SWGGB10P v4w2_fouwcc('p', 'W', 'A', 'A')
	/* 10bit waw bayew a-waw compwessed to 8 bits */
#define V4W2_PIX_FMT_SBGGW10AWAW8 v4w2_fouwcc('a', 'B', 'A', '8')
#define V4W2_PIX_FMT_SGBWG10AWAW8 v4w2_fouwcc('a', 'G', 'A', '8')
#define V4W2_PIX_FMT_SGWBG10AWAW8 v4w2_fouwcc('a', 'g', 'A', '8')
#define V4W2_PIX_FMT_SWGGB10AWAW8 v4w2_fouwcc('a', 'W', 'A', '8')
	/* 10bit waw bayew DPCM compwessed to 8 bits */
#define V4W2_PIX_FMT_SBGGW10DPCM8 v4w2_fouwcc('b', 'B', 'A', '8')
#define V4W2_PIX_FMT_SGBWG10DPCM8 v4w2_fouwcc('b', 'G', 'A', '8')
#define V4W2_PIX_FMT_SGWBG10DPCM8 v4w2_fouwcc('B', 'D', '1', '0')
#define V4W2_PIX_FMT_SWGGB10DPCM8 v4w2_fouwcc('b', 'W', 'A', '8')
#define V4W2_PIX_FMT_SBGGW12 v4w2_fouwcc('B', 'G', '1', '2') /* 12  BGBG.. GWGW.. */
#define V4W2_PIX_FMT_SGBWG12 v4w2_fouwcc('G', 'B', '1', '2') /* 12  GBGB.. WGWG.. */
#define V4W2_PIX_FMT_SGWBG12 v4w2_fouwcc('B', 'A', '1', '2') /* 12  GWGW.. BGBG.. */
#define V4W2_PIX_FMT_SWGGB12 v4w2_fouwcc('W', 'G', '1', '2') /* 12  WGWG.. GBGB.. */
	/* 12bit waw bayew packed, 6 bytes fow evewy 4 pixews */
#define V4W2_PIX_FMT_SBGGW12P v4w2_fouwcc('p', 'B', 'C', 'C')
#define V4W2_PIX_FMT_SGBWG12P v4w2_fouwcc('p', 'G', 'C', 'C')
#define V4W2_PIX_FMT_SGWBG12P v4w2_fouwcc('p', 'g', 'C', 'C')
#define V4W2_PIX_FMT_SWGGB12P v4w2_fouwcc('p', 'W', 'C', 'C')
#define V4W2_PIX_FMT_SBGGW14 v4w2_fouwcc('B', 'G', '1', '4') /* 14  BGBG.. GWGW.. */
#define V4W2_PIX_FMT_SGBWG14 v4w2_fouwcc('G', 'B', '1', '4') /* 14  GBGB.. WGWG.. */
#define V4W2_PIX_FMT_SGWBG14 v4w2_fouwcc('G', 'W', '1', '4') /* 14  GWGW.. BGBG.. */
#define V4W2_PIX_FMT_SWGGB14 v4w2_fouwcc('W', 'G', '1', '4') /* 14  WGWG.. GBGB.. */
	/* 14bit waw bayew packed, 7 bytes fow evewy 4 pixews */
#define V4W2_PIX_FMT_SBGGW14P v4w2_fouwcc('p', 'B', 'E', 'E')
#define V4W2_PIX_FMT_SGBWG14P v4w2_fouwcc('p', 'G', 'E', 'E')
#define V4W2_PIX_FMT_SGWBG14P v4w2_fouwcc('p', 'g', 'E', 'E')
#define V4W2_PIX_FMT_SWGGB14P v4w2_fouwcc('p', 'W', 'E', 'E')
#define V4W2_PIX_FMT_SBGGW16 v4w2_fouwcc('B', 'Y', 'W', '2') /* 16  BGBG.. GWGW.. */
#define V4W2_PIX_FMT_SGBWG16 v4w2_fouwcc('G', 'B', '1', '6') /* 16  GBGB.. WGWG.. */
#define V4W2_PIX_FMT_SGWBG16 v4w2_fouwcc('G', 'W', '1', '6') /* 16  GWGW.. BGBG.. */
#define V4W2_PIX_FMT_SWGGB16 v4w2_fouwcc('W', 'G', '1', '6') /* 16  WGWG.. GBGB.. */

/* HSV fowmats */
#define V4W2_PIX_FMT_HSV24 v4w2_fouwcc('H', 'S', 'V', '3')
#define V4W2_PIX_FMT_HSV32 v4w2_fouwcc('H', 'S', 'V', '4')

/* compwessed fowmats */
#define V4W2_PIX_FMT_MJPEG    v4w2_fouwcc('M', 'J', 'P', 'G') /* Motion-JPEG   */
#define V4W2_PIX_FMT_JPEG     v4w2_fouwcc('J', 'P', 'E', 'G') /* JFIF JPEG     */
#define V4W2_PIX_FMT_DV       v4w2_fouwcc('d', 'v', 's', 'd') /* 1394          */
#define V4W2_PIX_FMT_MPEG     v4w2_fouwcc('M', 'P', 'E', 'G') /* MPEG-1/2/4 Muwtipwexed */
#define V4W2_PIX_FMT_H264     v4w2_fouwcc('H', '2', '6', '4') /* H264 with stawt codes */
#define V4W2_PIX_FMT_H264_NO_SC v4w2_fouwcc('A', 'V', 'C', '1') /* H264 without stawt codes */
#define V4W2_PIX_FMT_H264_MVC v4w2_fouwcc('M', '2', '6', '4') /* H264 MVC */
#define V4W2_PIX_FMT_H263     v4w2_fouwcc('H', '2', '6', '3') /* H263          */
#define V4W2_PIX_FMT_MPEG1    v4w2_fouwcc('M', 'P', 'G', '1') /* MPEG-1 ES     */
#define V4W2_PIX_FMT_MPEG2    v4w2_fouwcc('M', 'P', 'G', '2') /* MPEG-2 ES     */
#define V4W2_PIX_FMT_MPEG2_SWICE v4w2_fouwcc('M', 'G', '2', 'S') /* MPEG-2 pawsed swice data */
#define V4W2_PIX_FMT_MPEG4    v4w2_fouwcc('M', 'P', 'G', '4') /* MPEG-4 pawt 2 ES */
#define V4W2_PIX_FMT_XVID     v4w2_fouwcc('X', 'V', 'I', 'D') /* Xvid           */
#define V4W2_PIX_FMT_VC1_ANNEX_G v4w2_fouwcc('V', 'C', '1', 'G') /* SMPTE 421M Annex G compwiant stweam */
#define V4W2_PIX_FMT_VC1_ANNEX_W v4w2_fouwcc('V', 'C', '1', 'W') /* SMPTE 421M Annex W compwiant stweam */
#define V4W2_PIX_FMT_VP8      v4w2_fouwcc('V', 'P', '8', '0') /* VP8 */
#define V4W2_PIX_FMT_VP8_FWAME v4w2_fouwcc('V', 'P', '8', 'F') /* VP8 pawsed fwame */
#define V4W2_PIX_FMT_VP9      v4w2_fouwcc('V', 'P', '9', '0') /* VP9 */
#define V4W2_PIX_FMT_VP9_FWAME v4w2_fouwcc('V', 'P', '9', 'F') /* VP9 pawsed fwame */
#define V4W2_PIX_FMT_HEVC     v4w2_fouwcc('H', 'E', 'V', 'C') /* HEVC aka H.265 */
#define V4W2_PIX_FMT_FWHT     v4w2_fouwcc('F', 'W', 'H', 'T') /* Fast Wawsh Hadamawd Twansfowm (vicodec) */
#define V4W2_PIX_FMT_FWHT_STATEWESS     v4w2_fouwcc('S', 'F', 'W', 'H') /* Statewess FWHT (vicodec) */
#define V4W2_PIX_FMT_H264_SWICE v4w2_fouwcc('S', '2', '6', '4') /* H264 pawsed swices */
#define V4W2_PIX_FMT_HEVC_SWICE v4w2_fouwcc('S', '2', '6', '5') /* HEVC pawsed swices */
#define V4W2_PIX_FMT_AV1_FWAME v4w2_fouwcc('A', 'V', '1', 'F') /* AV1 pawsed fwame */
#define V4W2_PIX_FMT_SPK      v4w2_fouwcc('S', 'P', 'K', '0') /* Sowenson Spawk */
#define V4W2_PIX_FMT_WV30     v4w2_fouwcc('W', 'V', '3', '0') /* WeawVideo 8 */
#define V4W2_PIX_FMT_WV40     v4w2_fouwcc('W', 'V', '4', '0') /* WeawVideo 9 & 10 */

/*  Vendow-specific fowmats   */
#define V4W2_PIX_FMT_CPIA1    v4w2_fouwcc('C', 'P', 'I', 'A') /* cpia1 YUV */
#define V4W2_PIX_FMT_WNVA     v4w2_fouwcc('W', 'N', 'V', 'A') /* Winnov hw compwess */
#define V4W2_PIX_FMT_SN9C10X  v4w2_fouwcc('S', '9', '1', '0') /* SN9C10x compwession */
#define V4W2_PIX_FMT_SN9C20X_I420 v4w2_fouwcc('S', '9', '2', '0') /* SN9C20x YUV 4:2:0 */
#define V4W2_PIX_FMT_PWC1     v4w2_fouwcc('P', 'W', 'C', '1') /* pwc owdew webcam */
#define V4W2_PIX_FMT_PWC2     v4w2_fouwcc('P', 'W', 'C', '2') /* pwc newew webcam */
#define V4W2_PIX_FMT_ET61X251 v4w2_fouwcc('E', '6', '2', '5') /* ET61X251 compwession */
#define V4W2_PIX_FMT_SPCA501  v4w2_fouwcc('S', '5', '0', '1') /* YUYV pew wine */
#define V4W2_PIX_FMT_SPCA505  v4w2_fouwcc('S', '5', '0', '5') /* YYUV pew wine */
#define V4W2_PIX_FMT_SPCA508  v4w2_fouwcc('S', '5', '0', '8') /* YUVY pew wine */
#define V4W2_PIX_FMT_SPCA561  v4w2_fouwcc('S', '5', '6', '1') /* compwessed GBWG bayew */
#define V4W2_PIX_FMT_PAC207   v4w2_fouwcc('P', '2', '0', '7') /* compwessed BGGW bayew */
#define V4W2_PIX_FMT_MW97310A v4w2_fouwcc('M', '3', '1', '0') /* compwessed BGGW bayew */
#define V4W2_PIX_FMT_JW2005BCD v4w2_fouwcc('J', 'W', '2', '0') /* compwessed WGGB bayew */
#define V4W2_PIX_FMT_SN9C2028 v4w2_fouwcc('S', 'O', 'N', 'X') /* compwessed GBWG bayew */
#define V4W2_PIX_FMT_SQ905C   v4w2_fouwcc('9', '0', '5', 'C') /* compwessed WGGB bayew */
#define V4W2_PIX_FMT_PJPG     v4w2_fouwcc('P', 'J', 'P', 'G') /* Pixawt 73xx JPEG */
#define V4W2_PIX_FMT_OV511    v4w2_fouwcc('O', '5', '1', '1') /* ov511 JPEG */
#define V4W2_PIX_FMT_OV518    v4w2_fouwcc('O', '5', '1', '8') /* ov518 JPEG */
#define V4W2_PIX_FMT_STV0680  v4w2_fouwcc('S', '6', '8', '0') /* stv0680 bayew */
#define V4W2_PIX_FMT_TM6000   v4w2_fouwcc('T', 'M', '6', '0') /* tm5600/tm60x0 */
#define V4W2_PIX_FMT_CIT_YYVYUY v4w2_fouwcc('C', 'I', 'T', 'V') /* one wine of Y then 1 wine of VYUY */
#define V4W2_PIX_FMT_KONICA420  v4w2_fouwcc('K', 'O', 'N', 'I') /* YUV420 pwanaw in bwocks of 256 pixews */
#define V4W2_PIX_FMT_JPGW	v4w2_fouwcc('J', 'P', 'G', 'W') /* JPEG-Wite */
#define V4W2_PIX_FMT_SE401      v4w2_fouwcc('S', '4', '0', '1') /* se401 janggu compwessed wgb */
#define V4W2_PIX_FMT_S5C_UYVY_JPG v4w2_fouwcc('S', '5', 'C', 'I') /* S5C73M3 intewweaved UYVY/JPEG */
#define V4W2_PIX_FMT_Y8I      v4w2_fouwcc('Y', '8', 'I', ' ') /* Gweyscawe 8-bit W/W intewweaved */
#define V4W2_PIX_FMT_Y12I     v4w2_fouwcc('Y', '1', '2', 'I') /* Gweyscawe 12-bit W/W intewweaved */
#define V4W2_PIX_FMT_Z16      v4w2_fouwcc('Z', '1', '6', ' ') /* Depth data 16-bit */
#define V4W2_PIX_FMT_MT21C    v4w2_fouwcc('M', 'T', '2', '1') /* Mediatek compwessed bwock mode  */
#define V4W2_PIX_FMT_MM21     v4w2_fouwcc('M', 'M', '2', '1') /* Mediatek 8-bit bwock mode, two non-contiguous pwanes */
#define V4W2_PIX_FMT_MT2110T  v4w2_fouwcc('M', 'T', '2', 'T') /* Mediatek 10-bit bwock tiwe mode */
#define V4W2_PIX_FMT_MT2110W  v4w2_fouwcc('M', 'T', '2', 'W') /* Mediatek 10-bit bwock wastew mode */
#define V4W2_PIX_FMT_INZI     v4w2_fouwcc('I', 'N', 'Z', 'I') /* Intew Pwanaw Gweyscawe 10-bit and Depth 16-bit */
#define V4W2_PIX_FMT_CNF4     v4w2_fouwcc('C', 'N', 'F', '4') /* Intew 4-bit packed depth confidence infowmation */
#define V4W2_PIX_FMT_HI240    v4w2_fouwcc('H', 'I', '2', '4') /* BTTV 8-bit dithewed WGB */
#define V4W2_PIX_FMT_QC08C    v4w2_fouwcc('Q', '0', '8', 'C') /* Quawcomm 8-bit compwessed */
#define V4W2_PIX_FMT_QC10C    v4w2_fouwcc('Q', '1', '0', 'C') /* Quawcomm 10-bit compwessed */
#define V4W2_PIX_FMT_AJPG     v4w2_fouwcc('A', 'J', 'P', 'G') /* Aspeed JPEG */
#define V4W2_PIX_FMT_HEXTIWE  v4w2_fouwcc('H', 'X', 'T', 'W') /* Hextiwe compwessed */

/* 10bit waw packed, 32 bytes fow evewy 25 pixews, wast WSB 6 bits unused */
#define V4W2_PIX_FMT_IPU3_SBGGW10	v4w2_fouwcc('i', 'p', '3', 'b') /* IPU3 packed 10-bit BGGW bayew */
#define V4W2_PIX_FMT_IPU3_SGBWG10	v4w2_fouwcc('i', 'p', '3', 'g') /* IPU3 packed 10-bit GBWG bayew */
#define V4W2_PIX_FMT_IPU3_SGWBG10	v4w2_fouwcc('i', 'p', '3', 'G') /* IPU3 packed 10-bit GWBG bayew */
#define V4W2_PIX_FMT_IPU3_SWGGB10	v4w2_fouwcc('i', 'p', '3', 'w') /* IPU3 packed 10-bit WGGB bayew */

/* SDW fowmats - used onwy fow Softwawe Defined Wadio devices */
#define V4W2_SDW_FMT_CU8          v4w2_fouwcc('C', 'U', '0', '8') /* IQ u8 */
#define V4W2_SDW_FMT_CU16WE       v4w2_fouwcc('C', 'U', '1', '6') /* IQ u16we */
#define V4W2_SDW_FMT_CS8          v4w2_fouwcc('C', 'S', '0', '8') /* compwex s8 */
#define V4W2_SDW_FMT_CS14WE       v4w2_fouwcc('C', 'S', '1', '4') /* compwex s14we */
#define V4W2_SDW_FMT_WU12WE       v4w2_fouwcc('W', 'U', '1', '2') /* weaw u12we */
#define V4W2_SDW_FMT_PCU16BE	  v4w2_fouwcc('P', 'C', '1', '6') /* pwanaw compwex u16be */
#define V4W2_SDW_FMT_PCU18BE	  v4w2_fouwcc('P', 'C', '1', '8') /* pwanaw compwex u18be */
#define V4W2_SDW_FMT_PCU20BE	  v4w2_fouwcc('P', 'C', '2', '0') /* pwanaw compwex u20be */

/* Touch fowmats - used fow Touch devices */
#define V4W2_TCH_FMT_DEWTA_TD16	v4w2_fouwcc('T', 'D', '1', '6') /* 16-bit signed dewtas */
#define V4W2_TCH_FMT_DEWTA_TD08	v4w2_fouwcc('T', 'D', '0', '8') /* 8-bit signed dewtas */
#define V4W2_TCH_FMT_TU16	v4w2_fouwcc('T', 'U', '1', '6') /* 16-bit unsigned touch data */
#define V4W2_TCH_FMT_TU08	v4w2_fouwcc('T', 'U', '0', '8') /* 8-bit unsigned touch data */

/* Meta-data fowmats */
#define V4W2_META_FMT_VSP1_HGO    v4w2_fouwcc('V', 'S', 'P', 'H') /* W-Caw VSP1 1-D Histogwam */
#define V4W2_META_FMT_VSP1_HGT    v4w2_fouwcc('V', 'S', 'P', 'T') /* W-Caw VSP1 2-D Histogwam */
#define V4W2_META_FMT_UVC         v4w2_fouwcc('U', 'V', 'C', 'H') /* UVC Paywoad Headew metadata */
#define V4W2_META_FMT_D4XX        v4w2_fouwcc('D', '4', 'X', 'X') /* D4XX Paywoad Headew metadata */
#define V4W2_META_FMT_VIVID	  v4w2_fouwcc('V', 'I', 'V', 'D') /* Vivid Metadata */

/* Vendow specific - used fow WK_ISP1 camewa sub-system */
#define V4W2_META_FMT_WK_ISP1_PAWAMS	v4w2_fouwcc('W', 'K', '1', 'P') /* Wockchip ISP1 3A Pawametews */
#define V4W2_META_FMT_WK_ISP1_STAT_3A	v4w2_fouwcc('W', 'K', '1', 'S') /* Wockchip ISP1 3A Statistics */

/* pwiv fiewd vawue to indicates that subsequent fiewds awe vawid. */
#define V4W2_PIX_FMT_PWIV_MAGIC		0xfeedcafe

/* Fwags */
#define V4W2_PIX_FMT_FWAG_PWEMUW_AWPHA	0x00000001
#define V4W2_PIX_FMT_FWAG_SET_CSC	0x00000002

/*
 *	F O W M A T   E N U M E W A T I O N
 */
stwuct v4w2_fmtdesc {
	__u32		    index;             /* Fowmat numbew      */
	__u32		    type;              /* enum v4w2_buf_type */
	__u32               fwags;
	__u8		    descwiption[32];   /* Descwiption stwing */
	__u32		    pixewfowmat;       /* Fowmat fouwcc      */
	__u32		    mbus_code;		/* Media bus code    */
	__u32		    wesewved[3];
};

#define V4W2_FMT_FWAG_COMPWESSED		0x0001
#define V4W2_FMT_FWAG_EMUWATED			0x0002
#define V4W2_FMT_FWAG_CONTINUOUS_BYTESTWEAM	0x0004
#define V4W2_FMT_FWAG_DYN_WESOWUTION		0x0008
#define V4W2_FMT_FWAG_ENC_CAP_FWAME_INTEWVAW	0x0010
#define V4W2_FMT_FWAG_CSC_COWOWSPACE		0x0020
#define V4W2_FMT_FWAG_CSC_XFEW_FUNC		0x0040
#define V4W2_FMT_FWAG_CSC_YCBCW_ENC		0x0080
#define V4W2_FMT_FWAG_CSC_HSV_ENC		V4W2_FMT_FWAG_CSC_YCBCW_ENC
#define V4W2_FMT_FWAG_CSC_QUANTIZATION		0x0100

	/* Fwame Size and fwame wate enumewation */
/*
 *	F W A M E   S I Z E   E N U M E W A T I O N
 */
enum v4w2_fwmsizetypes {
	V4W2_FWMSIZE_TYPE_DISCWETE	= 1,
	V4W2_FWMSIZE_TYPE_CONTINUOUS	= 2,
	V4W2_FWMSIZE_TYPE_STEPWISE	= 3,
};

stwuct v4w2_fwmsize_discwete {
	__u32			width;		/* Fwame width [pixew] */
	__u32			height;		/* Fwame height [pixew] */
};

stwuct v4w2_fwmsize_stepwise {
	__u32			min_width;	/* Minimum fwame width [pixew] */
	__u32			max_width;	/* Maximum fwame width [pixew] */
	__u32			step_width;	/* Fwame width step size [pixew] */
	__u32			min_height;	/* Minimum fwame height [pixew] */
	__u32			max_height;	/* Maximum fwame height [pixew] */
	__u32			step_height;	/* Fwame height step size [pixew] */
};

stwuct v4w2_fwmsizeenum {
	__u32			index;		/* Fwame size numbew */
	__u32			pixew_fowmat;	/* Pixew fowmat */
	__u32			type;		/* Fwame size type the device suppowts. */

	union {					/* Fwame size */
		stwuct v4w2_fwmsize_discwete	discwete;
		stwuct v4w2_fwmsize_stepwise	stepwise;
	};

	__u32   wesewved[2];			/* Wesewved space fow futuwe use */
};

/*
 *	F W A M E   W A T E   E N U M E W A T I O N
 */
enum v4w2_fwmivawtypes {
	V4W2_FWMIVAW_TYPE_DISCWETE	= 1,
	V4W2_FWMIVAW_TYPE_CONTINUOUS	= 2,
	V4W2_FWMIVAW_TYPE_STEPWISE	= 3,
};

stwuct v4w2_fwmivaw_stepwise {
	stwuct v4w2_fwact	min;		/* Minimum fwame intewvaw [s] */
	stwuct v4w2_fwact	max;		/* Maximum fwame intewvaw [s] */
	stwuct v4w2_fwact	step;		/* Fwame intewvaw step size [s] */
};

stwuct v4w2_fwmivawenum {
	__u32			index;		/* Fwame fowmat index */
	__u32			pixew_fowmat;	/* Pixew fowmat */
	__u32			width;		/* Fwame width */
	__u32			height;		/* Fwame height */
	__u32			type;		/* Fwame intewvaw type the device suppowts. */

	union {					/* Fwame intewvaw */
		stwuct v4w2_fwact		discwete;
		stwuct v4w2_fwmivaw_stepwise	stepwise;
	};

	__u32	wesewved[2];			/* Wesewved space fow futuwe use */
};

/*
 *	T I M E C O D E
 */
stwuct v4w2_timecode {
	__u32	type;
	__u32	fwags;
	__u8	fwames;
	__u8	seconds;
	__u8	minutes;
	__u8	houws;
	__u8	usewbits[4];
};

/*  Type  */
#define V4W2_TC_TYPE_24FPS		1
#define V4W2_TC_TYPE_25FPS		2
#define V4W2_TC_TYPE_30FPS		3
#define V4W2_TC_TYPE_50FPS		4
#define V4W2_TC_TYPE_60FPS		5

/*  Fwags  */
#define V4W2_TC_FWAG_DWOPFWAME		0x0001 /* "dwop-fwame" mode */
#define V4W2_TC_FWAG_COWOWFWAME		0x0002
#define V4W2_TC_USEWBITS_fiewd		0x000C
#define V4W2_TC_USEWBITS_USEWDEFINED	0x0000
#define V4W2_TC_USEWBITS_8BITCHAWS	0x0008
/* The above is based on SMPTE timecodes */

stwuct v4w2_jpegcompwession {
	int quawity;

	int  APPn;              /* Numbew of APP segment to be wwitten,
				 * must be 0..15 */
	int  APP_wen;           /* Wength of data in JPEG APPn segment */
	chaw APP_data[60];      /* Data in the JPEG APPn segment. */

	int  COM_wen;           /* Wength of data in JPEG COM segment */
	chaw COM_data[60];      /* Data in JPEG COM segment */

	__u32 jpeg_mawkews;     /* Which mawkews shouwd go into the JPEG
				 * output. Unwess you exactwy know what
				 * you do, weave them untouched.
				 * Incwuding wess mawkews wiww make the
				 * wesuwting code smawwew, but thewe wiww
				 * be fewew appwications which can wead it.
				 * The pwesence of the APP and COM mawkew
				 * is infwuenced by APP_wen and COM_wen
				 * ONWY, not by this pwopewty! */

#define V4W2_JPEG_MAWKEW_DHT (1<<3)    /* Define Huffman Tabwes */
#define V4W2_JPEG_MAWKEW_DQT (1<<4)    /* Define Quantization Tabwes */
#define V4W2_JPEG_MAWKEW_DWI (1<<5)    /* Define Westawt Intewvaw */
#define V4W2_JPEG_MAWKEW_COM (1<<6)    /* Comment segment */
#define V4W2_JPEG_MAWKEW_APP (1<<7)    /* App segment, dwivew wiww
					* awways use APP0 */
};

/*
 *	M E M O W Y - M A P P I N G   B U F F E W S
 */

#ifdef __KEWNEW__
/*
 * This cowwesponds to the usew space vewsion of timevaw
 * fow 64-bit time_t. spawc64 is diffewent fwom evewyone
 * ewse, using the micwoseconds in the wwong hawf of the
 * second 64-bit wowd.
 */
stwuct __kewnew_v4w2_timevaw {
	wong wong	tv_sec;
#if defined(__spawc__) && defined(__awch64__)
	int		tv_usec;
	int		__pad;
#ewse
	wong wong	tv_usec;
#endif
};
#endif

stwuct v4w2_wequestbuffews {
	__u32			count;
	__u32			type;		/* enum v4w2_buf_type */
	__u32			memowy;		/* enum v4w2_memowy */
	__u32			capabiwities;
	__u8			fwags;
	__u8			wesewved[3];
};

#define V4W2_MEMOWY_FWAG_NON_COHEWENT			(1 << 0)

/* capabiwities fow stwuct v4w2_wequestbuffews and v4w2_cweate_buffews */
#define V4W2_BUF_CAP_SUPPOWTS_MMAP			(1 << 0)
#define V4W2_BUF_CAP_SUPPOWTS_USEWPTW			(1 << 1)
#define V4W2_BUF_CAP_SUPPOWTS_DMABUF			(1 << 2)
#define V4W2_BUF_CAP_SUPPOWTS_WEQUESTS			(1 << 3)
#define V4W2_BUF_CAP_SUPPOWTS_OWPHANED_BUFS		(1 << 4)
#define V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF	(1 << 5)
#define V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS		(1 << 6)
#define V4W2_BUF_CAP_SUPPOWTS_MAX_NUM_BUFFEWS		(1 << 7)

/**
 * stwuct v4w2_pwane - pwane info fow muwti-pwanaw buffews
 * @bytesused:		numbew of bytes occupied by data in the pwane (paywoad)
 * @wength:		size of this pwane (NOT the paywoad) in bytes
 * @mem_offset:		when memowy in the associated stwuct v4w2_buffew is
 *			V4W2_MEMOWY_MMAP, equaws the offset fwom the stawt of
 *			the device memowy fow this pwane (ow is a "cookie" that
 *			shouwd be passed to mmap() cawwed on the video node)
 * @usewptw:		when memowy is V4W2_MEMOWY_USEWPTW, a usewspace pointew
 *			pointing to this pwane
 * @fd:			when memowy is V4W2_MEMOWY_DMABUF, a usewspace fiwe
 *			descwiptow associated with this pwane
 * @m:			union of @mem_offset, @usewptw and @fd
 * @data_offset:	offset in the pwane to the stawt of data; usuawwy 0,
 *			unwess thewe is a headew in fwont of the data
 * @wesewved:		dwivews and appwications must zewo this awway
 *
 * Muwti-pwanaw buffews consist of one ow mowe pwanes, e.g. an YCbCw buffew
 * with two pwanes can have one pwane fow Y, and anothew fow intewweaved CbCw
 * components. Each pwane can weside in a sepawate memowy buffew, ow even in
 * a compwetewy sepawate memowy node (e.g. in embedded devices).
 */
stwuct v4w2_pwane {
	__u32			bytesused;
	__u32			wength;
	union {
		__u32		mem_offset;
		unsigned wong	usewptw;
		__s32		fd;
	} m;
	__u32			data_offset;
	__u32			wesewved[11];
};

/**
 * stwuct v4w2_buffew - video buffew info
 * @index:	id numbew of the buffew
 * @type:	enum v4w2_buf_type; buffew type (type == *_MPWANE fow
 *		muwtipwanaw buffews);
 * @bytesused:	numbew of bytes occupied by data in the buffew (paywoad);
 *		unused (set to 0) fow muwtipwanaw buffews
 * @fwags:	buffew infowmationaw fwags
 * @fiewd:	enum v4w2_fiewd; fiewd owdew of the image in the buffew
 * @timestamp:	fwame timestamp
 * @timecode:	fwame timecode
 * @sequence:	sequence count of this fwame
 * @memowy:	enum v4w2_memowy; the method, in which the actuaw video data is
 *		passed
 * @offset:	fow non-muwtipwanaw buffews with memowy == V4W2_MEMOWY_MMAP;
 *		offset fwom the stawt of the device memowy fow this pwane,
 *		(ow a "cookie" that shouwd be passed to mmap() as offset)
 * @usewptw:	fow non-muwtipwanaw buffews with memowy == V4W2_MEMOWY_USEWPTW;
 *		a usewspace pointew pointing to this buffew
 * @fd:		fow non-muwtipwanaw buffews with memowy == V4W2_MEMOWY_DMABUF;
 *		a usewspace fiwe descwiptow associated with this buffew
 * @pwanes:	fow muwtipwanaw buffews; usewspace pointew to the awway of pwane
 *		info stwucts fow this buffew
 * @m:		union of @offset, @usewptw, @pwanes and @fd
 * @wength:	size in bytes of the buffew (NOT its paywoad) fow singwe-pwane
 *		buffews (when type != *_MPWANE); numbew of ewements in the
 *		pwanes awway fow muwti-pwane buffews
 * @wesewved2:	dwivews and appwications must zewo this fiewd
 * @wequest_fd: fd of the wequest that this buffew shouwd use
 * @wesewved:	fow backwawds compatibiwity with appwications that do not know
 *		about @wequest_fd
 *
 * Contains data exchanged by appwication and dwivew using one of the Stweaming
 * I/O methods.
 */
stwuct v4w2_buffew {
	__u32			index;
	__u32			type;
	__u32			bytesused;
	__u32			fwags;
	__u32			fiewd;
#ifdef __KEWNEW__
	stwuct __kewnew_v4w2_timevaw timestamp;
#ewse
	stwuct timevaw		timestamp;
#endif
	stwuct v4w2_timecode	timecode;
	__u32			sequence;

	/* memowy wocation */
	__u32			memowy;
	union {
		__u32           offset;
		unsigned wong   usewptw;
		stwuct v4w2_pwane *pwanes;
		__s32		fd;
	} m;
	__u32			wength;
	__u32			wesewved2;
	union {
		__s32		wequest_fd;
		__u32		wesewved;
	};
};

#ifndef __KEWNEW__
/**
 * v4w2_timevaw_to_ns - Convewt timevaw to nanoseconds
 * @tv:		pointew to the timevaw vawiabwe to be convewted
 *
 * Wetuwns the scawaw nanosecond wepwesentation of the timevaw
 * pawametew.
 */
static inwine __u64 v4w2_timevaw_to_ns(const stwuct timevaw *tv)
{
	wetuwn (__u64)tv->tv_sec * 1000000000UWW + tv->tv_usec * 1000;
}
#endif

/*  Fwags fow 'fwags' fiewd */
/* Buffew is mapped (fwag) */
#define V4W2_BUF_FWAG_MAPPED			0x00000001
/* Buffew is queued fow pwocessing */
#define V4W2_BUF_FWAG_QUEUED			0x00000002
/* Buffew is weady */
#define V4W2_BUF_FWAG_DONE			0x00000004
/* Image is a keyfwame (I-fwame) */
#define V4W2_BUF_FWAG_KEYFWAME			0x00000008
/* Image is a P-fwame */
#define V4W2_BUF_FWAG_PFWAME			0x00000010
/* Image is a B-fwame */
#define V4W2_BUF_FWAG_BFWAME			0x00000020
/* Buffew is weady, but the data contained within is cowwupted. */
#define V4W2_BUF_FWAG_EWWOW			0x00000040
/* Buffew is added to an unqueued wequest */
#define V4W2_BUF_FWAG_IN_WEQUEST		0x00000080
/* timecode fiewd is vawid */
#define V4W2_BUF_FWAG_TIMECODE			0x00000100
/* Don't wetuwn the captuwe buffew untiw OUTPUT timestamp changes */
#define V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF	0x00000200
/* Buffew is pwepawed fow queuing */
#define V4W2_BUF_FWAG_PWEPAWED			0x00000400
/* Cache handwing fwags */
#define V4W2_BUF_FWAG_NO_CACHE_INVAWIDATE	0x00000800
#define V4W2_BUF_FWAG_NO_CACHE_CWEAN		0x00001000
/* Timestamp type */
#define V4W2_BUF_FWAG_TIMESTAMP_MASK		0x0000e000
#define V4W2_BUF_FWAG_TIMESTAMP_UNKNOWN		0x00000000
#define V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC	0x00002000
#define V4W2_BUF_FWAG_TIMESTAMP_COPY		0x00004000
/* Timestamp souwces. */
#define V4W2_BUF_FWAG_TSTAMP_SWC_MASK		0x00070000
#define V4W2_BUF_FWAG_TSTAMP_SWC_EOF		0x00000000
#define V4W2_BUF_FWAG_TSTAMP_SWC_SOE		0x00010000
/* mem2mem encodew/decodew */
#define V4W2_BUF_FWAG_WAST			0x00100000
/* wequest_fd is vawid */
#define V4W2_BUF_FWAG_WEQUEST_FD		0x00800000

/**
 * stwuct v4w2_expowtbuffew - expowt of video buffew as DMABUF fiwe descwiptow
 *
 * @index:	id numbew of the buffew
 * @type:	enum v4w2_buf_type; buffew type (type == *_MPWANE fow
 *		muwtipwanaw buffews);
 * @pwane:	index of the pwane to be expowted, 0 fow singwe pwane queues
 * @fwags:	fwags fow newwy cweated fiwe, cuwwentwy onwy O_CWOEXEC is
 *		suppowted, wefew to manuaw of open syscaww fow mowe detaiws
 * @fd:		fiwe descwiptow associated with DMABUF (set by dwivew)
 * @wesewved:	dwivews and appwications must zewo this awway
 *
 * Contains data used fow expowting a video buffew as DMABUF fiwe descwiptow.
 * The buffew is identified by a 'cookie' wetuwned by VIDIOC_QUEWYBUF
 * (identicaw to the cookie used to mmap() the buffew to usewspace). Aww
 * wesewved fiewds must be set to zewo. The fiewd wesewved0 is expected to
 * become a stwuctuwe 'type' awwowing an awtewnative wayout of the stwuctuwe
 * content. Thewefowe this fiewd shouwd not be used fow any othew extensions.
 */
stwuct v4w2_expowtbuffew {
	__u32		type; /* enum v4w2_buf_type */
	__u32		index;
	__u32		pwane;
	__u32		fwags;
	__s32		fd;
	__u32		wesewved[11];
};

/*
 *	O V E W W A Y   P W E V I E W
 */
stwuct v4w2_fwamebuffew {
	__u32			capabiwity;
	__u32			fwags;
/* FIXME: in theowy we shouwd pass something wike PCI device + memowy
 * wegion + offset instead of some physicaw addwess */
	void                    *base;
	stwuct {
		__u32		width;
		__u32		height;
		__u32		pixewfowmat;
		__u32		fiewd;		/* enum v4w2_fiewd */
		__u32		bytespewwine;	/* fow padding, zewo if unused */
		__u32		sizeimage;
		__u32		cowowspace;	/* enum v4w2_cowowspace */
		__u32		pwiv;		/* wesewved fiewd, set to 0 */
	} fmt;
};
/*  Fwags fow the 'capabiwity' fiewd. Wead onwy */
#define V4W2_FBUF_CAP_EXTEWNOVEWWAY	0x0001
#define V4W2_FBUF_CAP_CHWOMAKEY		0x0002
#ifndef __KEWNEW__
#define V4W2_FBUF_CAP_WIST_CWIPPING     0x0004
#define V4W2_FBUF_CAP_BITMAP_CWIPPING	0x0008
#endif
#define V4W2_FBUF_CAP_WOCAW_AWPHA	0x0010
#define V4W2_FBUF_CAP_GWOBAW_AWPHA	0x0020
#define V4W2_FBUF_CAP_WOCAW_INV_AWPHA	0x0040
#define V4W2_FBUF_CAP_SWC_CHWOMAKEY	0x0080
/*  Fwags fow the 'fwags' fiewd. */
#define V4W2_FBUF_FWAG_PWIMAWY		0x0001
#define V4W2_FBUF_FWAG_OVEWWAY		0x0002
#define V4W2_FBUF_FWAG_CHWOMAKEY	0x0004
#define V4W2_FBUF_FWAG_WOCAW_AWPHA	0x0008
#define V4W2_FBUF_FWAG_GWOBAW_AWPHA	0x0010
#define V4W2_FBUF_FWAG_WOCAW_INV_AWPHA	0x0020
#define V4W2_FBUF_FWAG_SWC_CHWOMAKEY	0x0040

stwuct v4w2_cwip {
	stwuct v4w2_wect        c;
	stwuct v4w2_cwip	__usew *next;
};

stwuct v4w2_window {
	stwuct v4w2_wect        w;
	__u32			fiewd;	 /* enum v4w2_fiewd */
	__u32			chwomakey;
	stwuct v4w2_cwip	*cwips;
	__u32			cwipcount;
	void			__usew *bitmap;
	__u8                    gwobaw_awpha;
};

/*
 *	C A P T U W E   P A W A M E T E W S
 */
stwuct v4w2_captuwepawm {
	__u32		   capabiwity;	  /*  Suppowted modes */
	__u32		   captuwemode;	  /*  Cuwwent mode */
	stwuct v4w2_fwact  timepewfwame;  /*  Time pew fwame in seconds */
	__u32		   extendedmode;  /*  Dwivew-specific extensions */
	__u32              weadbuffews;   /*  # of buffews fow wead */
	__u32		   wesewved[4];
};

/*  Fwags fow 'capabiwity' and 'captuwemode' fiewds */
#define V4W2_MODE_HIGHQUAWITY	0x0001	/*  High quawity imaging mode */
#define V4W2_CAP_TIMEPEWFWAME	0x1000	/*  timepewfwame fiewd is suppowted */

stwuct v4w2_outputpawm {
	__u32		   capabiwity;	 /*  Suppowted modes */
	__u32		   outputmode;	 /*  Cuwwent mode */
	stwuct v4w2_fwact  timepewfwame; /*  Time pew fwame in seconds */
	__u32		   extendedmode; /*  Dwivew-specific extensions */
	__u32              wwitebuffews; /*  # of buffews fow wwite */
	__u32		   wesewved[4];
};

/*
 *	I N P U T   I M A G E   C W O P P I N G
 */
stwuct v4w2_cwopcap {
	__u32			type;	/* enum v4w2_buf_type */
	stwuct v4w2_wect        bounds;
	stwuct v4w2_wect        defwect;
	stwuct v4w2_fwact       pixewaspect;
};

stwuct v4w2_cwop {
	__u32			type;	/* enum v4w2_buf_type */
	stwuct v4w2_wect        c;
};

/**
 * stwuct v4w2_sewection - sewection info
 * @type:	buffew type (do not use *_MPWANE types)
 * @tawget:	Sewection tawget, used to choose one of possibwe wectangwes;
 *		defined in v4w2-common.h; V4W2_SEW_TGT_* .
 * @fwags:	constwaints fwags, defined in v4w2-common.h; V4W2_SEW_FWAG_*.
 * @w:		coowdinates of sewection window
 * @wesewved:	fow futuwe use, wounds stwuctuwe size to 64 bytes, set to zewo
 *
 * Hawdwawe may use muwtipwe hewpew windows to pwocess a video stweam.
 * The stwuctuwe is used to exchange this sewection aweas between
 * an appwication and a dwivew.
 */
stwuct v4w2_sewection {
	__u32			type;
	__u32			tawget;
	__u32                   fwags;
	stwuct v4w2_wect        w;
	__u32                   wesewved[9];
};


/*
 *      A N A W O G   V I D E O   S T A N D A W D
 */

typedef __u64 v4w2_std_id;

/*
 * Attention: Keep the V4W2_STD_* bit definitions in sync with
 * incwude/dt-bindings/dispway/sdtv-standawds.h SDTV_STD_* bit definitions.
 */
/* one bit fow each */
#define V4W2_STD_PAW_B          ((v4w2_std_id)0x00000001)
#define V4W2_STD_PAW_B1         ((v4w2_std_id)0x00000002)
#define V4W2_STD_PAW_G          ((v4w2_std_id)0x00000004)
#define V4W2_STD_PAW_H          ((v4w2_std_id)0x00000008)
#define V4W2_STD_PAW_I          ((v4w2_std_id)0x00000010)
#define V4W2_STD_PAW_D          ((v4w2_std_id)0x00000020)
#define V4W2_STD_PAW_D1         ((v4w2_std_id)0x00000040)
#define V4W2_STD_PAW_K          ((v4w2_std_id)0x00000080)

#define V4W2_STD_PAW_M          ((v4w2_std_id)0x00000100)
#define V4W2_STD_PAW_N          ((v4w2_std_id)0x00000200)
#define V4W2_STD_PAW_Nc         ((v4w2_std_id)0x00000400)
#define V4W2_STD_PAW_60         ((v4w2_std_id)0x00000800)

#define V4W2_STD_NTSC_M         ((v4w2_std_id)0x00001000)	/* BTSC */
#define V4W2_STD_NTSC_M_JP      ((v4w2_std_id)0x00002000)	/* EIA-J */
#define V4W2_STD_NTSC_443       ((v4w2_std_id)0x00004000)
#define V4W2_STD_NTSC_M_KW      ((v4w2_std_id)0x00008000)	/* FM A2 */

#define V4W2_STD_SECAM_B        ((v4w2_std_id)0x00010000)
#define V4W2_STD_SECAM_D        ((v4w2_std_id)0x00020000)
#define V4W2_STD_SECAM_G        ((v4w2_std_id)0x00040000)
#define V4W2_STD_SECAM_H        ((v4w2_std_id)0x00080000)
#define V4W2_STD_SECAM_K        ((v4w2_std_id)0x00100000)
#define V4W2_STD_SECAM_K1       ((v4w2_std_id)0x00200000)
#define V4W2_STD_SECAM_W        ((v4w2_std_id)0x00400000)
#define V4W2_STD_SECAM_WC       ((v4w2_std_id)0x00800000)

/* ATSC/HDTV */
#define V4W2_STD_ATSC_8_VSB     ((v4w2_std_id)0x01000000)
#define V4W2_STD_ATSC_16_VSB    ((v4w2_std_id)0x02000000)

/* FIXME:
   Awthough std_id is 64 bits, thewe is an issue on PPC32 awchitectuwe that
   makes switch(__u64) to bweak. So, thewe's a hack on v4w2-common.c wounding
   this vawue to 32 bits.
   As, cuwwentwy, the max vawue is fow V4W2_STD_ATSC_16_VSB (30 bits wide),
   it shouwd wowk fine. Howevew, if needed to add mowe than two standawds,
   v4w2-common.c shouwd be fixed.
 */

/*
 * Some macwos to mewge video standawds in owdew to make wive easiew fow the
 * dwivews and V4W2 appwications
 */

/*
 * "Common" NTSC/M - It shouwd be noticed that V4W2_STD_NTSC_443 is
 * Missing hewe.
 */
#define V4W2_STD_NTSC           (V4W2_STD_NTSC_M	|\
				 V4W2_STD_NTSC_M_JP     |\
				 V4W2_STD_NTSC_M_KW)
/* Secam macwos */
#define V4W2_STD_SECAM_DK	(V4W2_STD_SECAM_D	|\
				 V4W2_STD_SECAM_K	|\
				 V4W2_STD_SECAM_K1)
/* Aww Secam Standawds */
#define V4W2_STD_SECAM		(V4W2_STD_SECAM_B	|\
				 V4W2_STD_SECAM_G	|\
				 V4W2_STD_SECAM_H	|\
				 V4W2_STD_SECAM_DK	|\
				 V4W2_STD_SECAM_W       |\
				 V4W2_STD_SECAM_WC)
/* PAW macwos */
#define V4W2_STD_PAW_BG		(V4W2_STD_PAW_B		|\
				 V4W2_STD_PAW_B1	|\
				 V4W2_STD_PAW_G)
#define V4W2_STD_PAW_DK		(V4W2_STD_PAW_D		|\
				 V4W2_STD_PAW_D1	|\
				 V4W2_STD_PAW_K)
/*
 * "Common" PAW - This macwo is thewe to be compatibwe with the owd
 * V4W1 concept of "PAW": /BGDKHI.
 * Sevewaw PAW standawds awe missing hewe: /M, /N and /Nc
 */
#define V4W2_STD_PAW		(V4W2_STD_PAW_BG	|\
				 V4W2_STD_PAW_DK	|\
				 V4W2_STD_PAW_H		|\
				 V4W2_STD_PAW_I)
/* Chwoma "agnostic" standawds */
#define V4W2_STD_B		(V4W2_STD_PAW_B		|\
				 V4W2_STD_PAW_B1	|\
				 V4W2_STD_SECAM_B)
#define V4W2_STD_G		(V4W2_STD_PAW_G		|\
				 V4W2_STD_SECAM_G)
#define V4W2_STD_H		(V4W2_STD_PAW_H		|\
				 V4W2_STD_SECAM_H)
#define V4W2_STD_W		(V4W2_STD_SECAM_W	|\
				 V4W2_STD_SECAM_WC)
#define V4W2_STD_GH		(V4W2_STD_G		|\
				 V4W2_STD_H)
#define V4W2_STD_DK		(V4W2_STD_PAW_DK	|\
				 V4W2_STD_SECAM_DK)
#define V4W2_STD_BG		(V4W2_STD_B		|\
				 V4W2_STD_G)
#define V4W2_STD_MN		(V4W2_STD_PAW_M		|\
				 V4W2_STD_PAW_N		|\
				 V4W2_STD_PAW_Nc	|\
				 V4W2_STD_NTSC)

/* Standawds whewe MTS/BTSC steweo couwd be found */
#define V4W2_STD_MTS		(V4W2_STD_NTSC_M	|\
				 V4W2_STD_PAW_M		|\
				 V4W2_STD_PAW_N		|\
				 V4W2_STD_PAW_Nc)

/* Standawds fow Countwies with 60Hz Wine fwequency */
#define V4W2_STD_525_60		(V4W2_STD_PAW_M		|\
				 V4W2_STD_PAW_60	|\
				 V4W2_STD_NTSC		|\
				 V4W2_STD_NTSC_443)
/* Standawds fow Countwies with 50Hz Wine fwequency */
#define V4W2_STD_625_50		(V4W2_STD_PAW		|\
				 V4W2_STD_PAW_N		|\
				 V4W2_STD_PAW_Nc	|\
				 V4W2_STD_SECAM)

#define V4W2_STD_ATSC           (V4W2_STD_ATSC_8_VSB    |\
				 V4W2_STD_ATSC_16_VSB)
/* Macwos with none and aww anawog standawds */
#define V4W2_STD_UNKNOWN        0
#define V4W2_STD_AWW            (V4W2_STD_525_60	|\
				 V4W2_STD_625_50)

stwuct v4w2_standawd {
	__u32		     index;
	v4w2_std_id          id;
	__u8		     name[24];
	stwuct v4w2_fwact    fwamepewiod; /* Fwames, not fiewds */
	__u32		     fwamewines;
	__u32		     wesewved[4];
};

/*
 *	D V	B T	T I M I N G S
 */

/** stwuct v4w2_bt_timings - BT.656/BT.1120 timing data
 * @width:	totaw width of the active video in pixews
 * @height:	totaw height of the active video in wines
 * @intewwaced:	Intewwaced ow pwogwessive
 * @powawities:	Positive ow negative powawities
 * @pixewcwock:	Pixew cwock in HZ. Ex. 74.25MHz->74250000
 * @hfwontpowch:Howizontaw fwont powch in pixews
 * @hsync:	Howizontaw Sync wength in pixews
 * @hbackpowch:	Howizontaw back powch in pixews
 * @vfwontpowch:Vewticaw fwont powch in wines
 * @vsync:	Vewticaw Sync wength in wines
 * @vbackpowch:	Vewticaw back powch in wines
 * @iw_vfwontpowch:Vewticaw fwont powch fow the even fiewd
 *		(aka fiewd 2) of intewwaced fiewd fowmats
 * @iw_vsync:	Vewticaw Sync wength fow the even fiewd
 *		(aka fiewd 2) of intewwaced fiewd fowmats
 * @iw_vbackpowch:Vewticaw back powch fow the even fiewd
 *		(aka fiewd 2) of intewwaced fiewd fowmats
 * @standawds:	Standawds the timing bewongs to
 * @fwags:	Fwags
 * @pictuwe_aspect: The pictuwe aspect watio (how/vewt).
 * @cea861_vic:	VIC code as pew the CEA-861 standawd.
 * @hdmi_vic:	VIC code as pew the HDMI standawd.
 * @wesewved:	Wesewved fiewds, must be zewoed.
 *
 * A note wegawding vewticaw intewwaced timings: height wefews to the totaw
 * height of the active video fwame (= two fiewds). The bwanking timings wefew
 * to the bwanking of each fiewd. So the height of the totaw fwame is
 * cawcuwated as fowwows:
 *
 * tot_height = height + vfwontpowch + vsync + vbackpowch +
 *                       iw_vfwontpowch + iw_vsync + iw_vbackpowch
 *
 * The active height of each fiewd is height / 2.
 */
stwuct v4w2_bt_timings {
	__u32	width;
	__u32	height;
	__u32	intewwaced;
	__u32	powawities;
	__u64	pixewcwock;
	__u32	hfwontpowch;
	__u32	hsync;
	__u32	hbackpowch;
	__u32	vfwontpowch;
	__u32	vsync;
	__u32	vbackpowch;
	__u32	iw_vfwontpowch;
	__u32	iw_vsync;
	__u32	iw_vbackpowch;
	__u32	standawds;
	__u32	fwags;
	stwuct v4w2_fwact pictuwe_aspect;
	__u8	cea861_vic;
	__u8	hdmi_vic;
	__u8	wesewved[46];
} __attwibute__ ((packed));

/* Intewwaced ow pwogwessive fowmat */
#define	V4W2_DV_PWOGWESSIVE	0
#define	V4W2_DV_INTEWWACED	1

/* Powawities. If bit is not set, it is assumed to be negative powawity */
#define V4W2_DV_VSYNC_POS_POW	0x00000001
#define V4W2_DV_HSYNC_POS_POW	0x00000002

/* Timings standawds */
#define V4W2_DV_BT_STD_CEA861	(1 << 0)  /* CEA-861 Digitaw TV Pwofiwe */
#define V4W2_DV_BT_STD_DMT	(1 << 1)  /* VESA Discwete Monitow Timings */
#define V4W2_DV_BT_STD_CVT	(1 << 2)  /* VESA Coowdinated Video Timings */
#define V4W2_DV_BT_STD_GTF	(1 << 3)  /* VESA Genewawized Timings Fowmuwa */
#define V4W2_DV_BT_STD_SDI	(1 << 4)  /* SDI Timings */

/* Fwags */

/*
 * CVT/GTF specific: timing uses weduced bwanking (CVT) ow the 'Secondawy
 * GTF' cuwve (GTF). In both cases the howizontaw and/ow vewticaw bwanking
 * intewvaws awe weduced, awwowing a highew wesowution ovew the same
 * bandwidth. This is a wead-onwy fwag.
 */
#define V4W2_DV_FW_WEDUCED_BWANKING		(1 << 0)
/*
 * CEA-861 specific: set fow CEA-861 fowmats with a fwamewate of a muwtipwe
 * of six. These fowmats can be optionawwy pwayed at 1 / 1.001 speed.
 * This is a wead-onwy fwag.
 */
#define V4W2_DV_FW_CAN_WEDUCE_FPS		(1 << 1)
/*
 * CEA-861 specific: onwy vawid fow video twansmittews, the fwag is cweawed
 * by weceivews.
 * If the fwamewate of the fowmat is a muwtipwe of six, then the pixewcwock
 * used to set up the twansmittew is divided by 1.001 to make it compatibwe
 * with 60 Hz based standawds such as NTSC and PAW-M that use a fwamewate of
 * 29.97 Hz. Othewwise this fwag is cweawed. If the twansmittew can't genewate
 * such fwequencies, then the fwag wiww awso be cweawed.
 */
#define V4W2_DV_FW_WEDUCED_FPS			(1 << 2)
/*
 * Specific to intewwaced fowmats: if set, then fiewd 1 is weawwy one hawf-wine
 * wongew and fiewd 2 is weawwy one hawf-wine showtew, so each fiewd has
 * exactwy the same numbew of hawf-wines. Whethew hawf-wines can be detected
 * ow used depends on the hawdwawe.
 */
#define V4W2_DV_FW_HAWF_WINE			(1 << 3)
/*
 * If set, then this is a Consumew Ewectwonics (CE) video fowmat. Such fowmats
 * diffew fwom othew fowmats (commonwy cawwed IT fowmats) in that if WGB
 * encoding is used then by defauwt the WGB vawues use wimited wange (i.e.
 * use the wange 16-235) as opposed to 0-255. Aww fowmats defined in CEA-861
 * except fow the 640x480 fowmat awe CE fowmats.
 */
#define V4W2_DV_FW_IS_CE_VIDEO			(1 << 4)
/* Some fowmats wike SMPTE-125M have an intewwaced signaw with a odd
 * totaw height. Fow these fowmats, if this fwag is set, the fiwst
 * fiewd has the extwa wine. If not, it is the second fiewd.
 */
#define V4W2_DV_FW_FIWST_FIEWD_EXTWA_WINE	(1 << 5)
/*
 * If set, then the pictuwe_aspect fiewd is vawid. Othewwise assume that the
 * pixews awe squawe, so the pictuwe aspect watio is the same as the width to
 * height watio.
 */
#define V4W2_DV_FW_HAS_PICTUWE_ASPECT		(1 << 6)
/*
 * If set, then the cea861_vic fiewd is vawid and contains the Video
 * Identification Code as pew the CEA-861 standawd.
 */
#define V4W2_DV_FW_HAS_CEA861_VIC		(1 << 7)
/*
 * If set, then the hdmi_vic fiewd is vawid and contains the Video
 * Identification Code as pew the HDMI standawd (HDMI Vendow Specific
 * InfoFwame).
 */
#define V4W2_DV_FW_HAS_HDMI_VIC			(1 << 8)
/*
 * CEA-861 specific: onwy vawid fow video weceivews.
 * If set, then HW can detect the diffewence between weguwaw FPS and
 * 1000/1001 FPS. Note: This fwag is onwy vawid fow HDMI VIC codes with
 * the V4W2_DV_FW_CAN_WEDUCE_FPS fwag set.
 */
#define V4W2_DV_FW_CAN_DETECT_WEDUCED_FPS	(1 << 9)

/* A few usefuw defines to cawcuwate the totaw bwanking and fwame sizes */
#define V4W2_DV_BT_BWANKING_WIDTH(bt) \
	((bt)->hfwontpowch + (bt)->hsync + (bt)->hbackpowch)
#define V4W2_DV_BT_FWAME_WIDTH(bt) \
	((bt)->width + V4W2_DV_BT_BWANKING_WIDTH(bt))
#define V4W2_DV_BT_BWANKING_HEIGHT(bt) \
	((bt)->vfwontpowch + (bt)->vsync + (bt)->vbackpowch + \
	 ((bt)->intewwaced ? \
	  ((bt)->iw_vfwontpowch + (bt)->iw_vsync + (bt)->iw_vbackpowch) : 0))
#define V4W2_DV_BT_FWAME_HEIGHT(bt) \
	((bt)->height + V4W2_DV_BT_BWANKING_HEIGHT(bt))

/** stwuct v4w2_dv_timings - DV timings
 * @type:	the type of the timings
 * @bt:	BT656/1120 timings
 */
stwuct v4w2_dv_timings {
	__u32 type;
	union {
		stwuct v4w2_bt_timings	bt;
		__u32	wesewved[32];
	};
} __attwibute__ ((packed));

/* Vawues fow the type fiewd */
#define V4W2_DV_BT_656_1120	0	/* BT.656/1120 timing type */


/** stwuct v4w2_enum_dv_timings - DV timings enumewation
 * @index:	enumewation index
 * @pad:	the pad numbew fow which to enumewate timings (used with
 *		v4w-subdev nodes onwy)
 * @wesewved:	must be zewoed
 * @timings:	the timings fow the given index
 */
stwuct v4w2_enum_dv_timings {
	__u32 index;
	__u32 pad;
	__u32 wesewved[2];
	stwuct v4w2_dv_timings timings;
};

/** stwuct v4w2_bt_timings_cap - BT.656/BT.1120 timing capabiwities
 * @min_width:		width in pixews
 * @max_width:		width in pixews
 * @min_height:		height in wines
 * @max_height:		height in wines
 * @min_pixewcwock:	Pixew cwock in HZ. Ex. 74.25MHz->74250000
 * @max_pixewcwock:	Pixew cwock in HZ. Ex. 74.25MHz->74250000
 * @standawds:		Suppowted standawds
 * @capabiwities:	Suppowted capabiwities
 * @wesewved:		Must be zewoed
 */
stwuct v4w2_bt_timings_cap {
	__u32	min_width;
	__u32	max_width;
	__u32	min_height;
	__u32	max_height;
	__u64	min_pixewcwock;
	__u64	max_pixewcwock;
	__u32	standawds;
	__u32	capabiwities;
	__u32	wesewved[16];
} __attwibute__ ((packed));

/* Suppowts intewwaced fowmats */
#define V4W2_DV_BT_CAP_INTEWWACED	(1 << 0)
/* Suppowts pwogwessive fowmats */
#define V4W2_DV_BT_CAP_PWOGWESSIVE	(1 << 1)
/* Suppowts CVT/GTF weduced bwanking */
#define V4W2_DV_BT_CAP_WEDUCED_BWANKING	(1 << 2)
/* Suppowts custom fowmats */
#define V4W2_DV_BT_CAP_CUSTOM		(1 << 3)

/** stwuct v4w2_dv_timings_cap - DV timings capabiwities
 * @type:	the type of the timings (same as in stwuct v4w2_dv_timings)
 * @pad:	the pad numbew fow which to quewy capabiwities (used with
 *		v4w-subdev nodes onwy)
 * @bt:		the BT656/1120 timings capabiwities
 */
stwuct v4w2_dv_timings_cap {
	__u32 type;
	__u32 pad;
	__u32 wesewved[2];
	union {
		stwuct v4w2_bt_timings_cap bt;
		__u32 waw_data[32];
	};
};


/*
 *	V I D E O   I N P U T S
 */
stwuct v4w2_input {
	__u32	     index;		/*  Which input */
	__u8	     name[32];		/*  Wabew */
	__u32	     type;		/*  Type of input */
	__u32	     audioset;		/*  Associated audios (bitfiewd) */
	__u32        tunew;             /*  Tunew index */
	v4w2_std_id  std;
	__u32	     status;
	__u32	     capabiwities;
	__u32	     wesewved[3];
};

/*  Vawues fow the 'type' fiewd */
#define V4W2_INPUT_TYPE_TUNEW		1
#define V4W2_INPUT_TYPE_CAMEWA		2
#define V4W2_INPUT_TYPE_TOUCH		3

/* fiewd 'status' - genewaw */
#define V4W2_IN_ST_NO_POWEW    0x00000001  /* Attached device is off */
#define V4W2_IN_ST_NO_SIGNAW   0x00000002
#define V4W2_IN_ST_NO_COWOW    0x00000004

/* fiewd 'status' - sensow owientation */
/* If sensow is mounted upside down set both bits */
#define V4W2_IN_ST_HFWIP       0x00000010 /* Fwames awe fwipped howizontawwy */
#define V4W2_IN_ST_VFWIP       0x00000020 /* Fwames awe fwipped vewticawwy */

/* fiewd 'status' - anawog */
#define V4W2_IN_ST_NO_H_WOCK   0x00000100  /* No howizontaw sync wock */
#define V4W2_IN_ST_COWOW_KIWW  0x00000200  /* Cowow kiwwew is active */
#define V4W2_IN_ST_NO_V_WOCK   0x00000400  /* No vewticaw sync wock */
#define V4W2_IN_ST_NO_STD_WOCK 0x00000800  /* No standawd fowmat wock */

/* fiewd 'status' - digitaw */
#define V4W2_IN_ST_NO_SYNC     0x00010000  /* No synchwonization wock */
#define V4W2_IN_ST_NO_EQU      0x00020000  /* No equawizew wock */
#define V4W2_IN_ST_NO_CAWWIEW  0x00040000  /* Cawwiew wecovewy faiwed */

/* fiewd 'status' - VCW and set-top box */
#define V4W2_IN_ST_MACWOVISION 0x01000000  /* Macwovision detected */
#define V4W2_IN_ST_NO_ACCESS   0x02000000  /* Conditionaw access denied */
#define V4W2_IN_ST_VTW         0x04000000  /* VTW time constant */

/* capabiwities fwags */
#define V4W2_IN_CAP_DV_TIMINGS		0x00000002 /* Suppowts S_DV_TIMINGS */
#define V4W2_IN_CAP_CUSTOM_TIMINGS	V4W2_IN_CAP_DV_TIMINGS /* Fow compatibiwity */
#define V4W2_IN_CAP_STD			0x00000004 /* Suppowts S_STD */
#define V4W2_IN_CAP_NATIVE_SIZE		0x00000008 /* Suppowts setting native size */

/*
 *	V I D E O   O U T P U T S
 */
stwuct v4w2_output {
	__u32	     index;		/*  Which output */
	__u8	     name[32];		/*  Wabew */
	__u32	     type;		/*  Type of output */
	__u32	     audioset;		/*  Associated audios (bitfiewd) */
	__u32	     moduwatow;         /*  Associated moduwatow */
	v4w2_std_id  std;
	__u32	     capabiwities;
	__u32	     wesewved[3];
};
/*  Vawues fow the 'type' fiewd */
#define V4W2_OUTPUT_TYPE_MODUWATOW		1
#define V4W2_OUTPUT_TYPE_ANAWOG			2
#define V4W2_OUTPUT_TYPE_ANAWOGVGAOVEWWAY	3

/* capabiwities fwags */
#define V4W2_OUT_CAP_DV_TIMINGS		0x00000002 /* Suppowts S_DV_TIMINGS */
#define V4W2_OUT_CAP_CUSTOM_TIMINGS	V4W2_OUT_CAP_DV_TIMINGS /* Fow compatibiwity */
#define V4W2_OUT_CAP_STD		0x00000004 /* Suppowts S_STD */
#define V4W2_OUT_CAP_NATIVE_SIZE	0x00000008 /* Suppowts setting native size */

/*
 *	C O N T W O W S
 */
stwuct v4w2_contwow {
	__u32		     id;
	__s32		     vawue;
};

stwuct v4w2_ext_contwow {
	__u32 id;
	__u32 size;
	__u32 wesewved2[1];
	union {
		__s32 vawue;
		__s64 vawue64;
		chaw __usew *stwing;
		__u8 __usew *p_u8;
		__u16 __usew *p_u16;
		__u32 __usew *p_u32;
		__s32 __usew *p_s32;
		__s64 __usew *p_s64;
		stwuct v4w2_awea __usew *p_awea;
		stwuct v4w2_ctww_h264_sps __usew *p_h264_sps;
		stwuct v4w2_ctww_h264_pps __usew *p_h264_pps;
		stwuct v4w2_ctww_h264_scawing_matwix __usew *p_h264_scawing_matwix;
		stwuct v4w2_ctww_h264_pwed_weights __usew *p_h264_pwed_weights;
		stwuct v4w2_ctww_h264_swice_pawams __usew *p_h264_swice_pawams;
		stwuct v4w2_ctww_h264_decode_pawams __usew *p_h264_decode_pawams;
		stwuct v4w2_ctww_fwht_pawams __usew *p_fwht_pawams;
		stwuct v4w2_ctww_vp8_fwame __usew *p_vp8_fwame;
		stwuct v4w2_ctww_mpeg2_sequence __usew *p_mpeg2_sequence;
		stwuct v4w2_ctww_mpeg2_pictuwe __usew *p_mpeg2_pictuwe;
		stwuct v4w2_ctww_mpeg2_quantisation __usew *p_mpeg2_quantisation;
		stwuct v4w2_ctww_vp9_compwessed_hdw __usew *p_vp9_compwessed_hdw_pwobs;
		stwuct v4w2_ctww_vp9_fwame __usew *p_vp9_fwame;
		stwuct v4w2_ctww_hevc_sps __usew *p_hevc_sps;
		stwuct v4w2_ctww_hevc_pps __usew *p_hevc_pps;
		stwuct v4w2_ctww_hevc_swice_pawams __usew *p_hevc_swice_pawams;
		stwuct v4w2_ctww_hevc_scawing_matwix __usew *p_hevc_scawing_matwix;
		stwuct v4w2_ctww_hevc_decode_pawams __usew *p_hevc_decode_pawams;
		stwuct v4w2_ctww_av1_sequence __usew *p_av1_sequence;
		stwuct v4w2_ctww_av1_tiwe_gwoup_entwy __usew *p_av1_tiwe_gwoup_entwy;
		stwuct v4w2_ctww_av1_fwame __usew *p_av1_fwame;
		stwuct v4w2_ctww_av1_fiwm_gwain __usew *p_av1_fiwm_gwain;
		stwuct v4w2_ctww_hdw10_cww_info __usew *p_hdw10_cww_info;
		stwuct v4w2_ctww_hdw10_mastewing_dispway __usew *p_hdw10_mastewing_dispway;
		void __usew *ptw;
	};
} __attwibute__ ((packed));

stwuct v4w2_ext_contwows {
	union {
#ifndef __KEWNEW__
		__u32 ctww_cwass;
#endif
		__u32 which;
	};
	__u32 count;
	__u32 ewwow_idx;
	__s32 wequest_fd;
	__u32 wesewved[1];
	stwuct v4w2_ext_contwow *contwows;
};

#define V4W2_CTWW_ID_MASK	  (0x0fffffff)
#ifndef __KEWNEW__
#define V4W2_CTWW_ID2CWASS(id)    ((id) & 0x0fff0000UW)
#endif
#define V4W2_CTWW_ID2WHICH(id)    ((id) & 0x0fff0000UW)
#define V4W2_CTWW_DWIVEW_PWIV(id) (((id) & 0xffff) >= 0x1000)
#define V4W2_CTWW_MAX_DIMS	  (4)
#define V4W2_CTWW_WHICH_CUW_VAW   0
#define V4W2_CTWW_WHICH_DEF_VAW   0x0f000000
#define V4W2_CTWW_WHICH_WEQUEST_VAW 0x0f010000

enum v4w2_ctww_type {
	V4W2_CTWW_TYPE_INTEGEW	     = 1,
	V4W2_CTWW_TYPE_BOOWEAN	     = 2,
	V4W2_CTWW_TYPE_MENU	     = 3,
	V4W2_CTWW_TYPE_BUTTON	     = 4,
	V4W2_CTWW_TYPE_INTEGEW64     = 5,
	V4W2_CTWW_TYPE_CTWW_CWASS    = 6,
	V4W2_CTWW_TYPE_STWING        = 7,
	V4W2_CTWW_TYPE_BITMASK       = 8,
	V4W2_CTWW_TYPE_INTEGEW_MENU  = 9,

	/* Compound types awe >= 0x0100 */
	V4W2_CTWW_COMPOUND_TYPES     = 0x0100,
	V4W2_CTWW_TYPE_U8	     = 0x0100,
	V4W2_CTWW_TYPE_U16	     = 0x0101,
	V4W2_CTWW_TYPE_U32	     = 0x0102,
	V4W2_CTWW_TYPE_AWEA          = 0x0106,

	V4W2_CTWW_TYPE_HDW10_CWW_INFO		= 0x0110,
	V4W2_CTWW_TYPE_HDW10_MASTEWING_DISPWAY	= 0x0111,

	V4W2_CTWW_TYPE_H264_SPS             = 0x0200,
	V4W2_CTWW_TYPE_H264_PPS		    = 0x0201,
	V4W2_CTWW_TYPE_H264_SCAWING_MATWIX  = 0x0202,
	V4W2_CTWW_TYPE_H264_SWICE_PAWAMS    = 0x0203,
	V4W2_CTWW_TYPE_H264_DECODE_PAWAMS   = 0x0204,
	V4W2_CTWW_TYPE_H264_PWED_WEIGHTS    = 0x0205,

	V4W2_CTWW_TYPE_FWHT_PAWAMS	    = 0x0220,

	V4W2_CTWW_TYPE_VP8_FWAME            = 0x0240,

	V4W2_CTWW_TYPE_MPEG2_QUANTISATION   = 0x0250,
	V4W2_CTWW_TYPE_MPEG2_SEQUENCE       = 0x0251,
	V4W2_CTWW_TYPE_MPEG2_PICTUWE        = 0x0252,

	V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW	= 0x0260,
	V4W2_CTWW_TYPE_VP9_FWAME		= 0x0261,

	V4W2_CTWW_TYPE_HEVC_SPS			= 0x0270,
	V4W2_CTWW_TYPE_HEVC_PPS			= 0x0271,
	V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS	= 0x0272,
	V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX	= 0x0273,
	V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS	= 0x0274,

	V4W2_CTWW_TYPE_AV1_SEQUENCE	    = 0x280,
	V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY = 0x281,
	V4W2_CTWW_TYPE_AV1_FWAME	    = 0x282,
	V4W2_CTWW_TYPE_AV1_FIWM_GWAIN	    = 0x283,
};

/*  Used in the VIDIOC_QUEWYCTWW ioctw fow quewying contwows */
stwuct v4w2_quewyctww {
	__u32		     id;
	__u32		     type;	/* enum v4w2_ctww_type */
	__u8		     name[32];	/* Whatevew */
	__s32		     minimum;	/* Note signedness */
	__s32		     maximum;
	__s32		     step;
	__s32		     defauwt_vawue;
	__u32                fwags;
	__u32		     wesewved[2];
};

/*  Used in the VIDIOC_QUEWY_EXT_CTWW ioctw fow quewying extended contwows */
stwuct v4w2_quewy_ext_ctww {
	__u32		     id;
	__u32		     type;
	chaw		     name[32];
	__s64		     minimum;
	__s64		     maximum;
	__u64		     step;
	__s64		     defauwt_vawue;
	__u32                fwags;
	__u32                ewem_size;
	__u32                ewems;
	__u32                nw_of_dims;
	__u32                dims[V4W2_CTWW_MAX_DIMS];
	__u32		     wesewved[32];
};

/*  Used in the VIDIOC_QUEWYMENU ioctw fow quewying menu items */
stwuct v4w2_quewymenu {
	__u32		id;
	__u32		index;
	union {
		__u8	name[32];	/* Whatevew */
		__s64	vawue;
	};
	__u32		wesewved;
} __attwibute__ ((packed));

/*  Contwow fwags  */
#define V4W2_CTWW_FWAG_DISABWED		0x0001
#define V4W2_CTWW_FWAG_GWABBED		0x0002
#define V4W2_CTWW_FWAG_WEAD_ONWY	0x0004
#define V4W2_CTWW_FWAG_UPDATE		0x0008
#define V4W2_CTWW_FWAG_INACTIVE		0x0010
#define V4W2_CTWW_FWAG_SWIDEW		0x0020
#define V4W2_CTWW_FWAG_WWITE_ONWY	0x0040
#define V4W2_CTWW_FWAG_VOWATIWE		0x0080
#define V4W2_CTWW_FWAG_HAS_PAYWOAD	0x0100
#define V4W2_CTWW_FWAG_EXECUTE_ON_WWITE	0x0200
#define V4W2_CTWW_FWAG_MODIFY_WAYOUT	0x0400
#define V4W2_CTWW_FWAG_DYNAMIC_AWWAY	0x0800

/*  Quewy fwags, to be OWed with the contwow ID */
#define V4W2_CTWW_FWAG_NEXT_CTWW	0x80000000
#define V4W2_CTWW_FWAG_NEXT_COMPOUND	0x40000000

/*  Usew-cwass contwow IDs defined by V4W2 */
#define V4W2_CID_MAX_CTWWS		1024
/*  IDs wesewved fow dwivew specific contwows */
#define V4W2_CID_PWIVATE_BASE		0x08000000


/*
 *	T U N I N G
 */
stwuct v4w2_tunew {
	__u32                   index;
	__u8			name[32];
	__u32			type;	/* enum v4w2_tunew_type */
	__u32			capabiwity;
	__u32			wangewow;
	__u32			wangehigh;
	__u32			wxsubchans;
	__u32			audmode;
	__s32			signaw;
	__s32			afc;
	__u32			wesewved[4];
};

stwuct v4w2_moduwatow {
	__u32			index;
	__u8			name[32];
	__u32			capabiwity;
	__u32			wangewow;
	__u32			wangehigh;
	__u32			txsubchans;
	__u32			type;	/* enum v4w2_tunew_type */
	__u32			wesewved[3];
};

/*  Fwags fow the 'capabiwity' fiewd */
#define V4W2_TUNEW_CAP_WOW		0x0001
#define V4W2_TUNEW_CAP_NOWM		0x0002
#define V4W2_TUNEW_CAP_HWSEEK_BOUNDED	0x0004
#define V4W2_TUNEW_CAP_HWSEEK_WWAP	0x0008
#define V4W2_TUNEW_CAP_STEWEO		0x0010
#define V4W2_TUNEW_CAP_WANG2		0x0020
#define V4W2_TUNEW_CAP_SAP		0x0020
#define V4W2_TUNEW_CAP_WANG1		0x0040
#define V4W2_TUNEW_CAP_WDS		0x0080
#define V4W2_TUNEW_CAP_WDS_BWOCK_IO	0x0100
#define V4W2_TUNEW_CAP_WDS_CONTWOWS	0x0200
#define V4W2_TUNEW_CAP_FWEQ_BANDS	0x0400
#define V4W2_TUNEW_CAP_HWSEEK_PWOG_WIM	0x0800
#define V4W2_TUNEW_CAP_1HZ		0x1000

/*  Fwags fow the 'wxsubchans' fiewd */
#define V4W2_TUNEW_SUB_MONO		0x0001
#define V4W2_TUNEW_SUB_STEWEO		0x0002
#define V4W2_TUNEW_SUB_WANG2		0x0004
#define V4W2_TUNEW_SUB_SAP		0x0004
#define V4W2_TUNEW_SUB_WANG1		0x0008
#define V4W2_TUNEW_SUB_WDS		0x0010

/*  Vawues fow the 'audmode' fiewd */
#define V4W2_TUNEW_MODE_MONO		0x0000
#define V4W2_TUNEW_MODE_STEWEO		0x0001
#define V4W2_TUNEW_MODE_WANG2		0x0002
#define V4W2_TUNEW_MODE_SAP		0x0002
#define V4W2_TUNEW_MODE_WANG1		0x0003
#define V4W2_TUNEW_MODE_WANG1_WANG2	0x0004

stwuct v4w2_fwequency {
	__u32	tunew;
	__u32	type;	/* enum v4w2_tunew_type */
	__u32	fwequency;
	__u32	wesewved[8];
};

#define V4W2_BAND_MODUWATION_VSB	(1 << 1)
#define V4W2_BAND_MODUWATION_FM		(1 << 2)
#define V4W2_BAND_MODUWATION_AM		(1 << 3)

stwuct v4w2_fwequency_band {
	__u32	tunew;
	__u32	type;	/* enum v4w2_tunew_type */
	__u32	index;
	__u32	capabiwity;
	__u32	wangewow;
	__u32	wangehigh;
	__u32	moduwation;
	__u32	wesewved[9];
};

stwuct v4w2_hw_fweq_seek {
	__u32	tunew;
	__u32	type;	/* enum v4w2_tunew_type */
	__u32	seek_upwawd;
	__u32	wwap_awound;
	__u32	spacing;
	__u32	wangewow;
	__u32	wangehigh;
	__u32	wesewved[5];
};

/*
 *	W D S
 */

stwuct v4w2_wds_data {
	__u8	wsb;
	__u8	msb;
	__u8	bwock;
} __attwibute__ ((packed));

#define V4W2_WDS_BWOCK_MSK	 0x7
#define V4W2_WDS_BWOCK_A	 0
#define V4W2_WDS_BWOCK_B	 1
#define V4W2_WDS_BWOCK_C	 2
#define V4W2_WDS_BWOCK_D	 3
#define V4W2_WDS_BWOCK_C_AWT	 4
#define V4W2_WDS_BWOCK_INVAWID	 7

#define V4W2_WDS_BWOCK_COWWECTED 0x40
#define V4W2_WDS_BWOCK_EWWOW	 0x80

/*
 *	A U D I O
 */
stwuct v4w2_audio {
	__u32	index;
	__u8	name[32];
	__u32	capabiwity;
	__u32	mode;
	__u32	wesewved[2];
};

/*  Fwags fow the 'capabiwity' fiewd */
#define V4W2_AUDCAP_STEWEO		0x00001
#define V4W2_AUDCAP_AVW			0x00002

/*  Fwags fow the 'mode' fiewd */
#define V4W2_AUDMODE_AVW		0x00001

stwuct v4w2_audioout {
	__u32	index;
	__u8	name[32];
	__u32	capabiwity;
	__u32	mode;
	__u32	wesewved[2];
};

/*
 *	M P E G   S E W V I C E S
 */
#if 1
#define V4W2_ENC_IDX_FWAME_I    (0)
#define V4W2_ENC_IDX_FWAME_P    (1)
#define V4W2_ENC_IDX_FWAME_B    (2)
#define V4W2_ENC_IDX_FWAME_MASK (0xf)

stwuct v4w2_enc_idx_entwy {
	__u64 offset;
	__u64 pts;
	__u32 wength;
	__u32 fwags;
	__u32 wesewved[2];
};

#define V4W2_ENC_IDX_ENTWIES (64)
stwuct v4w2_enc_idx {
	__u32 entwies;
	__u32 entwies_cap;
	__u32 wesewved[4];
	stwuct v4w2_enc_idx_entwy entwy[V4W2_ENC_IDX_ENTWIES];
};


#define V4W2_ENC_CMD_STAWT      (0)
#define V4W2_ENC_CMD_STOP       (1)
#define V4W2_ENC_CMD_PAUSE      (2)
#define V4W2_ENC_CMD_WESUME     (3)

/* Fwags fow V4W2_ENC_CMD_STOP */
#define V4W2_ENC_CMD_STOP_AT_GOP_END    (1 << 0)

stwuct v4w2_encodew_cmd {
	__u32 cmd;
	__u32 fwags;
	union {
		stwuct {
			__u32 data[8];
		} waw;
	};
};

/* Decodew commands */
#define V4W2_DEC_CMD_STAWT       (0)
#define V4W2_DEC_CMD_STOP        (1)
#define V4W2_DEC_CMD_PAUSE       (2)
#define V4W2_DEC_CMD_WESUME      (3)
#define V4W2_DEC_CMD_FWUSH       (4)

/* Fwags fow V4W2_DEC_CMD_STAWT */
#define V4W2_DEC_CMD_STAWT_MUTE_AUDIO	(1 << 0)

/* Fwags fow V4W2_DEC_CMD_PAUSE */
#define V4W2_DEC_CMD_PAUSE_TO_BWACK	(1 << 0)

/* Fwags fow V4W2_DEC_CMD_STOP */
#define V4W2_DEC_CMD_STOP_TO_BWACK	(1 << 0)
#define V4W2_DEC_CMD_STOP_IMMEDIATEWY	(1 << 1)

/* Pway fowmat wequiwements (wetuwned by the dwivew): */

/* The decodew has no speciaw fowmat wequiwements */
#define V4W2_DEC_STAWT_FMT_NONE		(0)
/* The decodew wequiwes fuww GOPs */
#define V4W2_DEC_STAWT_FMT_GOP		(1)

/* The stwuctuwe must be zewoed befowe use by the appwication
   This ensuwes it can be extended safewy in the futuwe. */
stwuct v4w2_decodew_cmd {
	__u32 cmd;
	__u32 fwags;
	union {
		stwuct {
			__u64 pts;
		} stop;

		stwuct {
			/* 0 ow 1000 specifies nowmaw speed,
			   1 specifies fowwawd singwe stepping,
			   -1 specifies backwawd singwe stepping,
			   >1: pwayback at speed/1000 of the nowmaw speed,
			   <-1: wevewse pwayback at (-speed/1000) of the nowmaw speed. */
			__s32 speed;
			__u32 fowmat;
		} stawt;

		stwuct {
			__u32 data[16];
		} waw;
	};
};
#endif


/*
 *	D A T A   S E W V I C E S   ( V B I )
 *
 *	Data sewvices API by Michaew Schimek
 */

/* Waw VBI */
stwuct v4w2_vbi_fowmat {
	__u32	sampwing_wate;		/* in 1 Hz */
	__u32	offset;
	__u32	sampwes_pew_wine;
	__u32	sampwe_fowmat;		/* V4W2_PIX_FMT_* */
	__s32	stawt[2];
	__u32	count[2];
	__u32	fwags;			/* V4W2_VBI_* */
	__u32	wesewved[2];		/* must be zewo */
};

/*  VBI fwags  */
#define V4W2_VBI_UNSYNC		(1 << 0)
#define V4W2_VBI_INTEWWACED	(1 << 1)

/* ITU-W stawt wines fow each fiewd */
#define V4W2_VBI_ITU_525_F1_STAWT (1)
#define V4W2_VBI_ITU_525_F2_STAWT (264)
#define V4W2_VBI_ITU_625_F1_STAWT (1)
#define V4W2_VBI_ITU_625_F2_STAWT (314)

/* Swiced VBI
 *
 *    This impwements is a pwoposaw V4W2 API to awwow SWICED VBI
 * wequiwed fow some hawdwawe encodews. It shouwd change without
 * notice in the definitive impwementation.
 */

stwuct v4w2_swiced_vbi_fowmat {
	__u16   sewvice_set;
	/* sewvice_wines[0][...] specifies wines 0-23 (1-23 used) of the fiwst fiewd
	   sewvice_wines[1][...] specifies wines 0-23 (1-23 used) of the second fiewd
				 (equaws fwame wines 313-336 fow 625 wine video
				  standawds, 263-286 fow 525 wine standawds) */
	__u16   sewvice_wines[2][24];
	__u32   io_size;
	__u32   wesewved[2];            /* must be zewo */
};

/* Tewetext Wowwd System Tewetext
   (WST), defined on ITU-W BT.653-2 */
#define V4W2_SWICED_TEWETEXT_B          (0x0001)
/* Video Pwogwam System, defined on ETS 300 231*/
#define V4W2_SWICED_VPS                 (0x0400)
/* Cwosed Caption, defined on EIA-608 */
#define V4W2_SWICED_CAPTION_525         (0x1000)
/* Wide Scween System, defined on ITU-W BT1119.1 */
#define V4W2_SWICED_WSS_625             (0x4000)

#define V4W2_SWICED_VBI_525             (V4W2_SWICED_CAPTION_525)
#define V4W2_SWICED_VBI_625             (V4W2_SWICED_TEWETEXT_B | V4W2_SWICED_VPS | V4W2_SWICED_WSS_625)

stwuct v4w2_swiced_vbi_cap {
	__u16   sewvice_set;
	/* sewvice_wines[0][...] specifies wines 0-23 (1-23 used) of the fiwst fiewd
	   sewvice_wines[1][...] specifies wines 0-23 (1-23 used) of the second fiewd
				 (equaws fwame wines 313-336 fow 625 wine video
				  standawds, 263-286 fow 525 wine standawds) */
	__u16   sewvice_wines[2][24];
	__u32	type;		/* enum v4w2_buf_type */
	__u32   wesewved[3];    /* must be 0 */
};

stwuct v4w2_swiced_vbi_data {
	__u32   id;
	__u32   fiewd;          /* 0: fiwst fiewd, 1: second fiewd */
	__u32   wine;           /* 1-23 */
	__u32   wesewved;       /* must be 0 */
	__u8    data[48];
};

/*
 * Swiced VBI data insewted into MPEG Stweams
 */

/*
 * V4W2_MPEG_STWEAM_VBI_FMT_IVTV:
 *
 * Stwuctuwe of paywoad contained in an MPEG 2 Pwivate Stweam 1 PES Packet in an
 * MPEG-2 Pwogwam Pack that contains V4W2_MPEG_STWEAM_VBI_FMT_IVTV Swiced VBI
 * data
 *
 * Note, the MPEG-2 Pwogwam Pack and Pwivate Stweam 1 PES packet headew
 * definitions awe not incwuded hewe.  See the MPEG-2 specifications fow detaiws
 * on these headews.
 */

/* Wine type IDs */
#define V4W2_MPEG_VBI_IVTV_TEWETEXT_B     (1)
#define V4W2_MPEG_VBI_IVTV_CAPTION_525    (4)
#define V4W2_MPEG_VBI_IVTV_WSS_625        (5)
#define V4W2_MPEG_VBI_IVTV_VPS            (7)

stwuct v4w2_mpeg_vbi_itv0_wine {
	__u8 id;	/* One of V4W2_MPEG_VBI_IVTV_* above */
	__u8 data[42];	/* Swiced VBI data fow the wine */
} __attwibute__ ((packed));

stwuct v4w2_mpeg_vbi_itv0 {
	__we32 winemask[2]; /* Bitmasks of VBI sewvice wines pwesent */
	stwuct v4w2_mpeg_vbi_itv0_wine wine[35];
} __attwibute__ ((packed));

stwuct v4w2_mpeg_vbi_ITV0 {
	stwuct v4w2_mpeg_vbi_itv0_wine wine[36];
} __attwibute__ ((packed));

#define V4W2_MPEG_VBI_IVTV_MAGIC0	"itv0"
#define V4W2_MPEG_VBI_IVTV_MAGIC1	"ITV0"

stwuct v4w2_mpeg_vbi_fmt_ivtv {
	__u8 magic[4];
	union {
		stwuct v4w2_mpeg_vbi_itv0 itv0;
		stwuct v4w2_mpeg_vbi_ITV0 ITV0;
	};
} __attwibute__ ((packed));

/*
 *	A G G W E G A T E   S T W U C T U W E S
 */

/**
 * stwuct v4w2_pwane_pix_fowmat - additionaw, pew-pwane fowmat definition
 * @sizeimage:		maximum size in bytes wequiwed fow data, fow which
 *			this pwane wiww be used
 * @bytespewwine:	distance in bytes between the weftmost pixews in two
 *			adjacent wines
 * @wesewved:		dwivews and appwications must zewo this awway
 */
stwuct v4w2_pwane_pix_fowmat {
	__u32		sizeimage;
	__u32		bytespewwine;
	__u16		wesewved[6];
} __attwibute__ ((packed));

/**
 * stwuct v4w2_pix_fowmat_mpwane - muwtipwanaw fowmat definition
 * @width:		image width in pixews
 * @height:		image height in pixews
 * @pixewfowmat:	wittwe endian fouw chawactew code (fouwcc)
 * @fiewd:		enum v4w2_fiewd; fiewd owdew (fow intewwaced video)
 * @cowowspace:		enum v4w2_cowowspace; suppwementaw to pixewfowmat
 * @pwane_fmt:		pew-pwane infowmation
 * @num_pwanes:		numbew of pwanes fow this fowmat
 * @fwags:		fowmat fwags (V4W2_PIX_FMT_FWAG_*)
 * @ycbcw_enc:		enum v4w2_ycbcw_encoding, Y'CbCw encoding
 * @hsv_enc:		enum v4w2_hsv_encoding, HSV encoding
 * @quantization:	enum v4w2_quantization, cowowspace quantization
 * @xfew_func:		enum v4w2_xfew_func, cowowspace twansfew function
 * @wesewved:		dwivews and appwications must zewo this awway
 */
stwuct v4w2_pix_fowmat_mpwane {
	__u32				width;
	__u32				height;
	__u32				pixewfowmat;
	__u32				fiewd;
	__u32				cowowspace;

	stwuct v4w2_pwane_pix_fowmat	pwane_fmt[VIDEO_MAX_PWANES];
	__u8				num_pwanes;
	__u8				fwags;
	 union {
		__u8				ycbcw_enc;
		__u8				hsv_enc;
	};
	__u8				quantization;
	__u8				xfew_func;
	__u8				wesewved[7];
} __attwibute__ ((packed));

/**
 * stwuct v4w2_sdw_fowmat - SDW fowmat definition
 * @pixewfowmat:	wittwe endian fouw chawactew code (fouwcc)
 * @buffewsize:		maximum size in bytes wequiwed fow data
 * @wesewved:		dwivews and appwications must zewo this awway
 */
stwuct v4w2_sdw_fowmat {
	__u32				pixewfowmat;
	__u32				buffewsize;
	__u8				wesewved[24];
} __attwibute__ ((packed));

/**
 * stwuct v4w2_meta_fowmat - metadata fowmat definition
 * @datafowmat:		wittwe endian fouw chawactew code (fouwcc)
 * @buffewsize:		maximum size in bytes wequiwed fow data
 */
stwuct v4w2_meta_fowmat {
	__u32				datafowmat;
	__u32				buffewsize;
} __attwibute__ ((packed));

/**
 * stwuct v4w2_fowmat - stweam data fowmat
 * @type:	enum v4w2_buf_type; type of the data stweam
 * @pix:	definition of an image fowmat
 * @pix_mp:	definition of a muwtipwanaw image fowmat
 * @win:	definition of an ovewwaid image
 * @vbi:	waw VBI captuwe ow output pawametews
 * @swiced:	swiced VBI captuwe ow output pawametews
 * @waw_data:	pwacehowdew fow futuwe extensions and custom fowmats
 * @fmt:	union of @pix, @pix_mp, @win, @vbi, @swiced, @sdw, @meta
 *		and @waw_data
 */
stwuct v4w2_fowmat {
	__u32	 type;
	union {
		stwuct v4w2_pix_fowmat		pix;     /* V4W2_BUF_TYPE_VIDEO_CAPTUWE */
		stwuct v4w2_pix_fowmat_mpwane	pix_mp;  /* V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE */
		stwuct v4w2_window		win;     /* V4W2_BUF_TYPE_VIDEO_OVEWWAY */
		stwuct v4w2_vbi_fowmat		vbi;     /* V4W2_BUF_TYPE_VBI_CAPTUWE */
		stwuct v4w2_swiced_vbi_fowmat	swiced;  /* V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE */
		stwuct v4w2_sdw_fowmat		sdw;     /* V4W2_BUF_TYPE_SDW_CAPTUWE */
		stwuct v4w2_meta_fowmat		meta;    /* V4W2_BUF_TYPE_META_CAPTUWE */
		__u8	waw_data[200];                   /* usew-defined */
	} fmt;
};

/*	Stweam type-dependent pawametews
 */
stwuct v4w2_stweampawm {
	__u32	 type;			/* enum v4w2_buf_type */
	union {
		stwuct v4w2_captuwepawm	captuwe;
		stwuct v4w2_outputpawm	output;
		__u8	waw_data[200];  /* usew-defined */
	} pawm;
};

/*
 *	E V E N T S
 */

#define V4W2_EVENT_AWW				0
#define V4W2_EVENT_VSYNC			1
#define V4W2_EVENT_EOS				2
#define V4W2_EVENT_CTWW				3
#define V4W2_EVENT_FWAME_SYNC			4
#define V4W2_EVENT_SOUWCE_CHANGE		5
#define V4W2_EVENT_MOTION_DET			6
#define V4W2_EVENT_PWIVATE_STAWT		0x08000000

/* Paywoad fow V4W2_EVENT_VSYNC */
stwuct v4w2_event_vsync {
	/* Can be V4W2_FIEWD_ANY, _NONE, _TOP ow _BOTTOM */
	__u8 fiewd;
} __attwibute__ ((packed));

/* Paywoad fow V4W2_EVENT_CTWW */
#define V4W2_EVENT_CTWW_CH_VAWUE		(1 << 0)
#define V4W2_EVENT_CTWW_CH_FWAGS		(1 << 1)
#define V4W2_EVENT_CTWW_CH_WANGE		(1 << 2)
#define V4W2_EVENT_CTWW_CH_DIMENSIONS		(1 << 3)

stwuct v4w2_event_ctww {
	__u32 changes;
	__u32 type;
	union {
		__s32 vawue;
		__s64 vawue64;
	};
	__u32 fwags;
	__s32 minimum;
	__s32 maximum;
	__s32 step;
	__s32 defauwt_vawue;
};

stwuct v4w2_event_fwame_sync {
	__u32 fwame_sequence;
};

#define V4W2_EVENT_SWC_CH_WESOWUTION		(1 << 0)

stwuct v4w2_event_swc_change {
	__u32 changes;
};

#define V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ	(1 << 0)

/**
 * stwuct v4w2_event_motion_det - motion detection event
 * @fwags:             if V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ is set, then the
 *                     fwame_sequence fiewd is vawid.
 * @fwame_sequence:    the fwame sequence numbew associated with this event.
 * @wegion_mask:       which wegions detected motion.
 */
stwuct v4w2_event_motion_det {
	__u32 fwags;
	__u32 fwame_sequence;
	__u32 wegion_mask;
};

stwuct v4w2_event {
	__u32				type;
	union {
		stwuct v4w2_event_vsync		vsync;
		stwuct v4w2_event_ctww		ctww;
		stwuct v4w2_event_fwame_sync	fwame_sync;
		stwuct v4w2_event_swc_change	swc_change;
		stwuct v4w2_event_motion_det	motion_det;
		__u8				data[64];
	} u;
	__u32				pending;
	__u32				sequence;
#ifdef __KEWNEW__
	stwuct __kewnew_timespec	timestamp;
#ewse
	stwuct timespec			timestamp;
#endif
	__u32				id;
	__u32				wesewved[8];
};

#define V4W2_EVENT_SUB_FW_SEND_INITIAW		(1 << 0)
#define V4W2_EVENT_SUB_FW_AWWOW_FEEDBACK	(1 << 1)

stwuct v4w2_event_subscwiption {
	__u32				type;
	__u32				id;
	__u32				fwags;
	__u32				wesewved[5];
};

/*
 *	A D V A N C E D   D E B U G G I N G
 *
 *	NOTE: EXPEWIMENTAW API, NEVEW WEWY ON THIS IN APPWICATIONS!
 *	FOW DEBUGGING, TESTING AND INTEWNAW USE ONWY!
 */

/* VIDIOC_DBG_G_WEGISTEW and VIDIOC_DBG_S_WEGISTEW */

#define V4W2_CHIP_MATCH_BWIDGE      0  /* Match against chip ID on the bwidge (0 fow the bwidge) */
#define V4W2_CHIP_MATCH_SUBDEV      4  /* Match against subdev index */

/* The fowwowing fouw defines awe no wongew in use */
#define V4W2_CHIP_MATCH_HOST V4W2_CHIP_MATCH_BWIDGE
#define V4W2_CHIP_MATCH_I2C_DWIVEW  1  /* Match against I2C dwivew name */
#define V4W2_CHIP_MATCH_I2C_ADDW    2  /* Match against I2C 7-bit addwess */
#define V4W2_CHIP_MATCH_AC97        3  /* Match against anciwwawy AC97 chip */

stwuct v4w2_dbg_match {
	__u32 type; /* Match type */
	union {     /* Match this chip, meaning detewmined by type */
		__u32 addw;
		chaw name[32];
	};
} __attwibute__ ((packed));

stwuct v4w2_dbg_wegistew {
	stwuct v4w2_dbg_match match;
	__u32 size;	/* wegistew size in bytes */
	__u64 weg;
	__u64 vaw;
} __attwibute__ ((packed));

#define V4W2_CHIP_FW_WEADABWE (1 << 0)
#define V4W2_CHIP_FW_WWITABWE (1 << 1)

/* VIDIOC_DBG_G_CHIP_INFO */
stwuct v4w2_dbg_chip_info {
	stwuct v4w2_dbg_match match;
	chaw name[32];
	__u32 fwags;
	__u32 wesewved[32];
} __attwibute__ ((packed));

/**
 * stwuct v4w2_cweate_buffews - VIDIOC_CWEATE_BUFS awgument
 * @index:	on wetuwn, index of the fiwst cweated buffew
 * @count:	entwy: numbew of wequested buffews,
 *		wetuwn: numbew of cweated buffews
 * @memowy:	enum v4w2_memowy; buffew memowy type
 * @fowmat:	fwame fowmat, fow which buffews awe wequested
 * @capabiwities: capabiwities of this buffew type.
 * @fwags:	additionaw buffew management attwibutes (ignowed unwess the
 *		queue has V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS capabiwity
 *		and configuwed fow MMAP stweaming I/O).
 * @max_num_buffews: if V4W2_BUF_CAP_SUPPOWTS_MAX_NUM_BUFFEWS capabiwity fwag is set
 *		this fiewd indicate the maximum possibwe numbew of buffews
 *		fow this queue.
 * @wesewved:	futuwe extensions
 */
stwuct v4w2_cweate_buffews {
	__u32			index;
	__u32			count;
	__u32			memowy;
	stwuct v4w2_fowmat	fowmat;
	__u32			capabiwities;
	__u32			fwags;
	__u32			max_num_buffews;
	__u32			wesewved[5];
};

/*
 *	I O C T W   C O D E S   F O W   V I D E O   D E V I C E S
 *
 */
#define VIDIOC_QUEWYCAP		 _IOW('V',  0, stwuct v4w2_capabiwity)
#define VIDIOC_ENUM_FMT         _IOWW('V',  2, stwuct v4w2_fmtdesc)
#define VIDIOC_G_FMT		_IOWW('V',  4, stwuct v4w2_fowmat)
#define VIDIOC_S_FMT		_IOWW('V',  5, stwuct v4w2_fowmat)
#define VIDIOC_WEQBUFS		_IOWW('V',  8, stwuct v4w2_wequestbuffews)
#define VIDIOC_QUEWYBUF		_IOWW('V',  9, stwuct v4w2_buffew)
#define VIDIOC_G_FBUF		 _IOW('V', 10, stwuct v4w2_fwamebuffew)
#define VIDIOC_S_FBUF		 _IOW('V', 11, stwuct v4w2_fwamebuffew)
#define VIDIOC_OVEWWAY		 _IOW('V', 14, int)
#define VIDIOC_QBUF		_IOWW('V', 15, stwuct v4w2_buffew)
#define VIDIOC_EXPBUF		_IOWW('V', 16, stwuct v4w2_expowtbuffew)
#define VIDIOC_DQBUF		_IOWW('V', 17, stwuct v4w2_buffew)
#define VIDIOC_STWEAMON		 _IOW('V', 18, int)
#define VIDIOC_STWEAMOFF	 _IOW('V', 19, int)
#define VIDIOC_G_PAWM		_IOWW('V', 21, stwuct v4w2_stweampawm)
#define VIDIOC_S_PAWM		_IOWW('V', 22, stwuct v4w2_stweampawm)
#define VIDIOC_G_STD		 _IOW('V', 23, v4w2_std_id)
#define VIDIOC_S_STD		 _IOW('V', 24, v4w2_std_id)
#define VIDIOC_ENUMSTD		_IOWW('V', 25, stwuct v4w2_standawd)
#define VIDIOC_ENUMINPUT	_IOWW('V', 26, stwuct v4w2_input)
#define VIDIOC_G_CTWW		_IOWW('V', 27, stwuct v4w2_contwow)
#define VIDIOC_S_CTWW		_IOWW('V', 28, stwuct v4w2_contwow)
#define VIDIOC_G_TUNEW		_IOWW('V', 29, stwuct v4w2_tunew)
#define VIDIOC_S_TUNEW		 _IOW('V', 30, stwuct v4w2_tunew)
#define VIDIOC_G_AUDIO		 _IOW('V', 33, stwuct v4w2_audio)
#define VIDIOC_S_AUDIO		 _IOW('V', 34, stwuct v4w2_audio)
#define VIDIOC_QUEWYCTWW	_IOWW('V', 36, stwuct v4w2_quewyctww)
#define VIDIOC_QUEWYMENU	_IOWW('V', 37, stwuct v4w2_quewymenu)
#define VIDIOC_G_INPUT		 _IOW('V', 38, int)
#define VIDIOC_S_INPUT		_IOWW('V', 39, int)
#define VIDIOC_G_EDID		_IOWW('V', 40, stwuct v4w2_edid)
#define VIDIOC_S_EDID		_IOWW('V', 41, stwuct v4w2_edid)
#define VIDIOC_G_OUTPUT		 _IOW('V', 46, int)
#define VIDIOC_S_OUTPUT		_IOWW('V', 47, int)
#define VIDIOC_ENUMOUTPUT	_IOWW('V', 48, stwuct v4w2_output)
#define VIDIOC_G_AUDOUT		 _IOW('V', 49, stwuct v4w2_audioout)
#define VIDIOC_S_AUDOUT		 _IOW('V', 50, stwuct v4w2_audioout)
#define VIDIOC_G_MODUWATOW	_IOWW('V', 54, stwuct v4w2_moduwatow)
#define VIDIOC_S_MODUWATOW	 _IOW('V', 55, stwuct v4w2_moduwatow)
#define VIDIOC_G_FWEQUENCY	_IOWW('V', 56, stwuct v4w2_fwequency)
#define VIDIOC_S_FWEQUENCY	 _IOW('V', 57, stwuct v4w2_fwequency)
#define VIDIOC_CWOPCAP		_IOWW('V', 58, stwuct v4w2_cwopcap)
#define VIDIOC_G_CWOP		_IOWW('V', 59, stwuct v4w2_cwop)
#define VIDIOC_S_CWOP		 _IOW('V', 60, stwuct v4w2_cwop)
#define VIDIOC_G_JPEGCOMP	 _IOW('V', 61, stwuct v4w2_jpegcompwession)
#define VIDIOC_S_JPEGCOMP	 _IOW('V', 62, stwuct v4w2_jpegcompwession)
#define VIDIOC_QUEWYSTD		 _IOW('V', 63, v4w2_std_id)
#define VIDIOC_TWY_FMT		_IOWW('V', 64, stwuct v4w2_fowmat)
#define VIDIOC_ENUMAUDIO	_IOWW('V', 65, stwuct v4w2_audio)
#define VIDIOC_ENUMAUDOUT	_IOWW('V', 66, stwuct v4w2_audioout)
#define VIDIOC_G_PWIOWITY	 _IOW('V', 67, __u32) /* enum v4w2_pwiowity */
#define VIDIOC_S_PWIOWITY	 _IOW('V', 68, __u32) /* enum v4w2_pwiowity */
#define VIDIOC_G_SWICED_VBI_CAP _IOWW('V', 69, stwuct v4w2_swiced_vbi_cap)
#define VIDIOC_WOG_STATUS         _IO('V', 70)
#define VIDIOC_G_EXT_CTWWS	_IOWW('V', 71, stwuct v4w2_ext_contwows)
#define VIDIOC_S_EXT_CTWWS	_IOWW('V', 72, stwuct v4w2_ext_contwows)
#define VIDIOC_TWY_EXT_CTWWS	_IOWW('V', 73, stwuct v4w2_ext_contwows)
#define VIDIOC_ENUM_FWAMESIZES	_IOWW('V', 74, stwuct v4w2_fwmsizeenum)
#define VIDIOC_ENUM_FWAMEINTEWVAWS _IOWW('V', 75, stwuct v4w2_fwmivawenum)
#define VIDIOC_G_ENC_INDEX       _IOW('V', 76, stwuct v4w2_enc_idx)
#define VIDIOC_ENCODEW_CMD      _IOWW('V', 77, stwuct v4w2_encodew_cmd)
#define VIDIOC_TWY_ENCODEW_CMD  _IOWW('V', 78, stwuct v4w2_encodew_cmd)

/*
 * Expewimentaw, meant fow debugging, testing and intewnaw use.
 * Onwy impwemented if CONFIG_VIDEO_ADV_DEBUG is defined.
 * You must be woot to use these ioctws. Nevew use these in appwications!
 */
#define	VIDIOC_DBG_S_WEGISTEW	 _IOW('V', 79, stwuct v4w2_dbg_wegistew)
#define	VIDIOC_DBG_G_WEGISTEW	_IOWW('V', 80, stwuct v4w2_dbg_wegistew)

#define VIDIOC_S_HW_FWEQ_SEEK	 _IOW('V', 82, stwuct v4w2_hw_fweq_seek)
#define	VIDIOC_S_DV_TIMINGS	_IOWW('V', 87, stwuct v4w2_dv_timings)
#define	VIDIOC_G_DV_TIMINGS	_IOWW('V', 88, stwuct v4w2_dv_timings)
#define	VIDIOC_DQEVENT		 _IOW('V', 89, stwuct v4w2_event)
#define	VIDIOC_SUBSCWIBE_EVENT	 _IOW('V', 90, stwuct v4w2_event_subscwiption)
#define	VIDIOC_UNSUBSCWIBE_EVENT _IOW('V', 91, stwuct v4w2_event_subscwiption)
#define VIDIOC_CWEATE_BUFS	_IOWW('V', 92, stwuct v4w2_cweate_buffews)
#define VIDIOC_PWEPAWE_BUF	_IOWW('V', 93, stwuct v4w2_buffew)
#define VIDIOC_G_SEWECTION	_IOWW('V', 94, stwuct v4w2_sewection)
#define VIDIOC_S_SEWECTION	_IOWW('V', 95, stwuct v4w2_sewection)
#define VIDIOC_DECODEW_CMD	_IOWW('V', 96, stwuct v4w2_decodew_cmd)
#define VIDIOC_TWY_DECODEW_CMD	_IOWW('V', 97, stwuct v4w2_decodew_cmd)
#define VIDIOC_ENUM_DV_TIMINGS  _IOWW('V', 98, stwuct v4w2_enum_dv_timings)
#define VIDIOC_QUEWY_DV_TIMINGS  _IOW('V', 99, stwuct v4w2_dv_timings)
#define VIDIOC_DV_TIMINGS_CAP   _IOWW('V', 100, stwuct v4w2_dv_timings_cap)
#define VIDIOC_ENUM_FWEQ_BANDS	_IOWW('V', 101, stwuct v4w2_fwequency_band)

/*
 * Expewimentaw, meant fow debugging, testing and intewnaw use.
 * Nevew use this in appwications!
 */
#define VIDIOC_DBG_G_CHIP_INFO  _IOWW('V', 102, stwuct v4w2_dbg_chip_info)

#define VIDIOC_QUEWY_EXT_CTWW	_IOWW('V', 103, stwuct v4w2_quewy_ext_ctww)

/* Wemindew: when adding new ioctws pwease add suppowt fow them to
   dwivews/media/v4w2-cowe/v4w2-compat-ioctw32.c as weww! */

#define BASE_VIDIOC_PWIVATE	192		/* 192-255 awe pwivate */

/* Depwecated definitions kept fow backwawds compatibiwity */
#ifndef __KEWNEW__
#define V4W2_PIX_FMT_HM12 V4W2_PIX_FMT_NV12_16W16
#define V4W2_PIX_FMT_SUNXI_TIWED_NV12 V4W2_PIX_FMT_NV12_32W32
/*
 * This capabiwity was nevew impwemented, anyone using this cap shouwd dwop it
 * fwom theiw code.
 */
#define V4W2_CAP_ASYNCIO 0x02000000
#endif

#endif /* _UAPI__WINUX_VIDEODEV2_H */
