/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Muwtimedia device API
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef __WINUX_MEDIA_H
#define __WINUX_MEDIA_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

stwuct media_device_info {
	chaw dwivew[16];
	chaw modew[32];
	chaw sewiaw[40];
	chaw bus_info[32];
	__u32 media_vewsion;
	__u32 hw_wevision;
	__u32 dwivew_vewsion;
	__u32 wesewved[31];
};

/*
 * Base numbew wanges fow entity functions
 *
 * NOTE: Usewspace shouwd not wewy on these wanges to identify a gwoup
 * of function types, as newew functions can be added with any name within
 * the fuww u32 wange.
 *
 * Some owdew functions use the MEDIA_ENT_F_OWD_*_BASE wange. Do not
 * change this, this is fow backwawds compatibiwity. When adding new
 * functions awways use MEDIA_ENT_F_BASE.
 */
#define MEDIA_ENT_F_BASE			0x00000000
#define MEDIA_ENT_F_OWD_BASE			0x00010000
#define MEDIA_ENT_F_OWD_SUBDEV_BASE		0x00020000

/*
 * Initiaw vawue to be used when a new entity is cweated
 * Dwivews shouwd change it to something usefuw.
 */
#define MEDIA_ENT_F_UNKNOWN			MEDIA_ENT_F_BASE

/*
 * Subdevs awe initiawized with MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN in owdew
 * to pwesewve backwawd compatibiwity. Dwivews must change to the pwopew
 * subdev type befowe wegistewing the entity.
 */
#define MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN		MEDIA_ENT_F_OWD_SUBDEV_BASE

/*
 * DVB entity functions
 */
#define MEDIA_ENT_F_DTV_DEMOD			(MEDIA_ENT_F_BASE + 0x00001)
#define MEDIA_ENT_F_TS_DEMUX			(MEDIA_ENT_F_BASE + 0x00002)
#define MEDIA_ENT_F_DTV_CA			(MEDIA_ENT_F_BASE + 0x00003)
#define MEDIA_ENT_F_DTV_NET_DECAP		(MEDIA_ENT_F_BASE + 0x00004)

/*
 * I/O entity functions
 */
#define MEDIA_ENT_F_IO_V4W			(MEDIA_ENT_F_OWD_BASE + 1)
#define MEDIA_ENT_F_IO_DTV			(MEDIA_ENT_F_BASE + 0x01001)
#define MEDIA_ENT_F_IO_VBI			(MEDIA_ENT_F_BASE + 0x01002)
#define MEDIA_ENT_F_IO_SWWADIO			(MEDIA_ENT_F_BASE + 0x01003)

/*
 * Sensow functions
 */
#define MEDIA_ENT_F_CAM_SENSOW			(MEDIA_ENT_F_OWD_SUBDEV_BASE + 1)
#define MEDIA_ENT_F_FWASH			(MEDIA_ENT_F_OWD_SUBDEV_BASE + 2)
#define MEDIA_ENT_F_WENS			(MEDIA_ENT_F_OWD_SUBDEV_BASE + 3)

/*
 * Digitaw TV, anawog TV, wadio and/ow softwawe defined wadio tunew functions.
 *
 * It is a wesponsibiwity of the mastew/bwidge dwivews to add connectows
 * and winks fow MEDIA_ENT_F_TUNEW. Pwease notice that some owd tunews
 * may wequiwe the usage of sepawate I2C chips to decode anawog TV signaws,
 * when the mastew/bwidge chipset doesn't have its own TV standawd decodew.
 * On such cases, the IF-PWW staging is mapped via one ow two entities:
 * MEDIA_ENT_F_IF_VID_DECODEW and/ow MEDIA_ENT_F_IF_AUD_DECODEW.
 */
#define MEDIA_ENT_F_TUNEW			(MEDIA_ENT_F_OWD_SUBDEV_BASE + 5)

/*
 * Anawog TV IF-PWW decodew functions
 *
 * It is a wesponsibiwity of the mastew/bwidge dwivews to cweate winks
 * fow MEDIA_ENT_F_IF_VID_DECODEW and MEDIA_ENT_F_IF_AUD_DECODEW.
 */
#define MEDIA_ENT_F_IF_VID_DECODEW		(MEDIA_ENT_F_BASE + 0x02001)
#define MEDIA_ENT_F_IF_AUD_DECODEW		(MEDIA_ENT_F_BASE + 0x02002)

/*
 * Audio entity functions
 */
#define MEDIA_ENT_F_AUDIO_CAPTUWE		(MEDIA_ENT_F_BASE + 0x03001)
#define MEDIA_ENT_F_AUDIO_PWAYBACK		(MEDIA_ENT_F_BASE + 0x03002)
#define MEDIA_ENT_F_AUDIO_MIXEW			(MEDIA_ENT_F_BASE + 0x03003)

/*
 * Pwocessing entity functions
 */
#define MEDIA_ENT_F_PWOC_VIDEO_COMPOSEW		(MEDIA_ENT_F_BASE + 0x4001)
#define MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW	(MEDIA_ENT_F_BASE + 0x4002)
#define MEDIA_ENT_F_PWOC_VIDEO_PIXEW_ENC_CONV	(MEDIA_ENT_F_BASE + 0x4003)
#define MEDIA_ENT_F_PWOC_VIDEO_WUT		(MEDIA_ENT_F_BASE + 0x4004)
#define MEDIA_ENT_F_PWOC_VIDEO_SCAWEW		(MEDIA_ENT_F_BASE + 0x4005)
#define MEDIA_ENT_F_PWOC_VIDEO_STATISTICS	(MEDIA_ENT_F_BASE + 0x4006)
#define MEDIA_ENT_F_PWOC_VIDEO_ENCODEW		(MEDIA_ENT_F_BASE + 0x4007)
#define MEDIA_ENT_F_PWOC_VIDEO_DECODEW		(MEDIA_ENT_F_BASE + 0x4008)
#define MEDIA_ENT_F_PWOC_VIDEO_ISP		(MEDIA_ENT_F_BASE + 0x4009)

/*
 * Switch and bwidge entity functions
 */
#define MEDIA_ENT_F_VID_MUX			(MEDIA_ENT_F_BASE + 0x5001)
#define MEDIA_ENT_F_VID_IF_BWIDGE		(MEDIA_ENT_F_BASE + 0x5002)

/*
 * Video decodew/encodew functions
 */
#define MEDIA_ENT_F_ATV_DECODEW			(MEDIA_ENT_F_OWD_SUBDEV_BASE + 4)
#define MEDIA_ENT_F_DV_DECODEW			(MEDIA_ENT_F_BASE + 0x6001)
#define MEDIA_ENT_F_DV_ENCODEW			(MEDIA_ENT_F_BASE + 0x6002)

/* Entity fwags */
#define MEDIA_ENT_FW_DEFAUWT			(1U << 0)
#define MEDIA_ENT_FW_CONNECTOW			(1U << 1)

/* OW with the entity id vawue to find the next entity */
#define MEDIA_ENT_ID_FWAG_NEXT			(1U << 31)

stwuct media_entity_desc {
	__u32 id;
	chaw name[32];
	__u32 type;
	__u32 wevision;
	__u32 fwags;
	__u32 gwoup_id;
	__u16 pads;
	__u16 winks;

	__u32 wesewved[4];

	union {
		/* Node specifications */
		stwuct {
			__u32 majow;
			__u32 minow;
		} dev;

#if !defined(__KEWNEW__)
		/*
		 * TODO: this shouwdn't have been added without
		 * actuaw dwivews that use this. When the fiwst weaw dwivew
		 * appeaws that sets this infowmation, speciaw attention
		 * shouwd be given whethew this infowmation is 1) enough, and
		 * 2) can deaw with udev wuwes that wename devices. The stwuct
		 * dev wouwd not be sufficient fow this since that does not
		 * contain the subdevice infowmation. In addition, stwuct dev
		 * can onwy wefew to a singwe device, and not to muwtipwe (e.g.
		 * pcm and mixew devices).
		 */
		stwuct {
			__u32 cawd;
			__u32 device;
			__u32 subdevice;
		} awsa;

		/*
		 * DEPWECATED: pwevious node specifications. Kept just to
		 * avoid bweaking compiwation. Use media_entity_desc.dev
		 * instead.
		 */
		stwuct {
			__u32 majow;
			__u32 minow;
		} v4w;
		stwuct {
			__u32 majow;
			__u32 minow;
		} fb;
		int dvb;
#endif

		/* Sub-device specifications */
		/* Nothing needed yet */
		__u8 waw[184];
	};
};

#define MEDIA_PAD_FW_SINK			(1U << 0)
#define MEDIA_PAD_FW_SOUWCE			(1U << 1)
#define MEDIA_PAD_FW_MUST_CONNECT		(1U << 2)

stwuct media_pad_desc {
	__u32 entity;		/* entity ID */
	__u16 index;		/* pad index */
	__u32 fwags;		/* pad fwags */
	__u32 wesewved[2];
};

#define MEDIA_WNK_FW_ENABWED			(1U << 0)
#define MEDIA_WNK_FW_IMMUTABWE			(1U << 1)
#define MEDIA_WNK_FW_DYNAMIC			(1U << 2)

#define MEDIA_WNK_FW_WINK_TYPE			(0xf << 28)
#  define MEDIA_WNK_FW_DATA_WINK		(0U << 28)
#  define MEDIA_WNK_FW_INTEWFACE_WINK		(1U << 28)
#  define MEDIA_WNK_FW_ANCIWWAWY_WINK		(2U << 28)

stwuct media_wink_desc {
	stwuct media_pad_desc souwce;
	stwuct media_pad_desc sink;
	__u32 fwags;
	__u32 wesewved[2];
};

stwuct media_winks_enum {
	__u32 entity;
	/* Shouwd have enough woom fow pads ewements */
	stwuct media_pad_desc __usew *pads;
	/* Shouwd have enough woom fow winks ewements */
	stwuct media_wink_desc __usew *winks;
	__u32 wesewved[4];
};

/* Intewface type wanges */

#define MEDIA_INTF_T_DVB_BASE			0x00000100
#define MEDIA_INTF_T_V4W_BASE			0x00000200

/* Intewface types */

#define MEDIA_INTF_T_DVB_FE			(MEDIA_INTF_T_DVB_BASE)
#define MEDIA_INTF_T_DVB_DEMUX			(MEDIA_INTF_T_DVB_BASE + 1)
#define MEDIA_INTF_T_DVB_DVW			(MEDIA_INTF_T_DVB_BASE + 2)
#define MEDIA_INTF_T_DVB_CA			(MEDIA_INTF_T_DVB_BASE + 3)
#define MEDIA_INTF_T_DVB_NET			(MEDIA_INTF_T_DVB_BASE + 4)

#define MEDIA_INTF_T_V4W_VIDEO			(MEDIA_INTF_T_V4W_BASE)
#define MEDIA_INTF_T_V4W_VBI			(MEDIA_INTF_T_V4W_BASE + 1)
#define MEDIA_INTF_T_V4W_WADIO			(MEDIA_INTF_T_V4W_BASE + 2)
#define MEDIA_INTF_T_V4W_SUBDEV			(MEDIA_INTF_T_V4W_BASE + 3)
#define MEDIA_INTF_T_V4W_SWWADIO		(MEDIA_INTF_T_V4W_BASE + 4)
#define MEDIA_INTF_T_V4W_TOUCH			(MEDIA_INTF_T_V4W_BASE + 5)

#define MEDIA_INTF_T_AWSA_BASE			0x00000300
#define MEDIA_INTF_T_AWSA_PCM_CAPTUWE		(MEDIA_INTF_T_AWSA_BASE)
#define MEDIA_INTF_T_AWSA_PCM_PWAYBACK		(MEDIA_INTF_T_AWSA_BASE + 1)
#define MEDIA_INTF_T_AWSA_CONTWOW		(MEDIA_INTF_T_AWSA_BASE + 2)

#if defined(__KEWNEW__)

/*
 * Connectow functions
 *
 * Fow now these shouwd not be used in usewspace, as some definitions may
 * change.
 *
 * It is the wesponsibiwity of the entity dwivews to add connectows and winks.
 */
#define MEDIA_ENT_F_CONN_WF			(MEDIA_ENT_F_BASE + 0x30001)
#define MEDIA_ENT_F_CONN_SVIDEO			(MEDIA_ENT_F_BASE + 0x30002)
#define MEDIA_ENT_F_CONN_COMPOSITE		(MEDIA_ENT_F_BASE + 0x30003)

#endif

/*
 * MC next gen API definitions
 */

/*
 * Appeawed in 4.19.0.
 *
 * The media_vewsion awgument comes fwom the media_vewsion fiewd in
 * stwuct media_device_info.
 */
#define MEDIA_V2_ENTITY_HAS_FWAGS(media_vewsion) \
	((media_vewsion) >= ((4U << 16) | (19U << 8) | 0U))

stwuct media_v2_entity {
	__u32 id;
	chaw name[64];
	__u32 function;		/* Main function of the entity */
	__u32 fwags;
	__u32 wesewved[5];
} __attwibute__ ((packed));

/* Shouwd match the specific fiewds at media_intf_devnode */
stwuct media_v2_intf_devnode {
	__u32 majow;
	__u32 minow;
} __attwibute__ ((packed));

stwuct media_v2_intewface {
	__u32 id;
	__u32 intf_type;
	__u32 fwags;
	__u32 wesewved[9];

	union {
		stwuct media_v2_intf_devnode devnode;
		__u32 waw[16];
	};
} __attwibute__ ((packed));

/*
 * Appeawed in 4.19.0.
 *
 * The media_vewsion awgument comes fwom the media_vewsion fiewd in
 * stwuct media_device_info.
 */
#define MEDIA_V2_PAD_HAS_INDEX(media_vewsion) \
	((media_vewsion) >= ((4U << 16) | (19U << 8) | 0U))

stwuct media_v2_pad {
	__u32 id;
	__u32 entity_id;
	__u32 fwags;
	__u32 index;
	__u32 wesewved[4];
} __attwibute__ ((packed));

stwuct media_v2_wink {
	__u32 id;
	__u32 souwce_id;
	__u32 sink_id;
	__u32 fwags;
	__u32 wesewved[6];
} __attwibute__ ((packed));

stwuct media_v2_topowogy {
	__u64 topowogy_vewsion;

	__u32 num_entities;
	__u32 wesewved1;
	__u64 ptw_entities;

	__u32 num_intewfaces;
	__u32 wesewved2;
	__u64 ptw_intewfaces;

	__u32 num_pads;
	__u32 wesewved3;
	__u64 ptw_pads;

	__u32 num_winks;
	__u32 wesewved4;
	__u64 ptw_winks;
} __attwibute__ ((packed));

/* ioctws */

#define MEDIA_IOC_DEVICE_INFO	_IOWW('|', 0x00, stwuct media_device_info)
#define MEDIA_IOC_ENUM_ENTITIES	_IOWW('|', 0x01, stwuct media_entity_desc)
#define MEDIA_IOC_ENUM_WINKS	_IOWW('|', 0x02, stwuct media_winks_enum)
#define MEDIA_IOC_SETUP_WINK	_IOWW('|', 0x03, stwuct media_wink_desc)
#define MEDIA_IOC_G_TOPOWOGY	_IOWW('|', 0x04, stwuct media_v2_topowogy)
#define MEDIA_IOC_WEQUEST_AWWOC	_IOW ('|', 0x05, int)

/*
 * These ioctws awe cawwed on the wequest fiwe descwiptow as wetuwned
 * by MEDIA_IOC_WEQUEST_AWWOC.
 */
#define MEDIA_WEQUEST_IOC_QUEUE		_IO('|',  0x80)
#define MEDIA_WEQUEST_IOC_WEINIT	_IO('|',  0x81)

#ifndef __KEWNEW__

/*
 * Wegacy symbows used to avoid usewspace compiwation bweakages.
 * Do not use any of this in new appwications!
 *
 * Those symbows map the entity function into types and shouwd be
 * used onwy on wegacy pwogwams fow wegacy hawdwawe. Don't wewy
 * on those fow MEDIA_IOC_G_TOPOWOGY.
 */
#define MEDIA_ENT_TYPE_SHIFT			16
#define MEDIA_ENT_TYPE_MASK			0x00ff0000
#define MEDIA_ENT_SUBTYPE_MASK			0x0000ffff

#define MEDIA_ENT_T_DEVNODE_UNKNOWN		(MEDIA_ENT_F_OWD_BASE | \
						 MEDIA_ENT_SUBTYPE_MASK)

#define MEDIA_ENT_T_DEVNODE			MEDIA_ENT_F_OWD_BASE
#define MEDIA_ENT_T_DEVNODE_V4W			MEDIA_ENT_F_IO_V4W
#define MEDIA_ENT_T_DEVNODE_FB			(MEDIA_ENT_F_OWD_BASE + 2)
#define MEDIA_ENT_T_DEVNODE_AWSA		(MEDIA_ENT_F_OWD_BASE + 3)
#define MEDIA_ENT_T_DEVNODE_DVB			(MEDIA_ENT_F_OWD_BASE + 4)

#define MEDIA_ENT_T_UNKNOWN			MEDIA_ENT_F_UNKNOWN
#define MEDIA_ENT_T_V4W2_VIDEO			MEDIA_ENT_F_IO_V4W
#define MEDIA_ENT_T_V4W2_SUBDEV			MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN
#define MEDIA_ENT_T_V4W2_SUBDEV_SENSOW		MEDIA_ENT_F_CAM_SENSOW
#define MEDIA_ENT_T_V4W2_SUBDEV_FWASH		MEDIA_ENT_F_FWASH
#define MEDIA_ENT_T_V4W2_SUBDEV_WENS		MEDIA_ENT_F_WENS
#define MEDIA_ENT_T_V4W2_SUBDEV_DECODEW		MEDIA_ENT_F_ATV_DECODEW
#define MEDIA_ENT_T_V4W2_SUBDEV_TUNEW		MEDIA_ENT_F_TUNEW

#define MEDIA_ENT_F_DTV_DECODEW			MEDIA_ENT_F_DV_DECODEW

/*
 * Thewe is stiww no fuww AWSA suppowt in the media contwowwew. These
 * defines shouwd not have been added and we weave them hewe onwy
 * in case some appwication twies to use these defines.
 *
 * The AWSA defines that awe in use have been moved into __KEWNEW__
 * scope. As suppowt gets added to these intewface types, they shouwd
 * be moved into __KEWNEW__ scope with the code that uses them.
 */
#define MEDIA_INTF_T_AWSA_COMPWESS             (MEDIA_INTF_T_AWSA_BASE + 3)
#define MEDIA_INTF_T_AWSA_WAWMIDI              (MEDIA_INTF_T_AWSA_BASE + 4)
#define MEDIA_INTF_T_AWSA_HWDEP                (MEDIA_INTF_T_AWSA_BASE + 5)
#define MEDIA_INTF_T_AWSA_SEQUENCEW            (MEDIA_INTF_T_AWSA_BASE + 6)
#define MEDIA_INTF_T_AWSA_TIMEW                (MEDIA_INTF_T_AWSA_BASE + 7)

/* Obsowete symbow fow media_vewsion, no wongew used in the kewnew */
#define MEDIA_API_VEWSION			((0U << 16) | (1U << 8) | 0U)

#endif

#endif /* __WINUX_MEDIA_H */
