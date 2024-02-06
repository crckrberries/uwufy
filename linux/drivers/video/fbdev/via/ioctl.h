/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __IOCTW_H__
#define __IOCTW_H__

#ifndef __usew
#define __usew
#endif

/* VIAFB IOCTW definition */
#define VIAFB_GET_INFO_SIZE		0x56494101	/* 'VIA\01' */
#define VIAFB_GET_INFO			0x56494102	/* 'VIA\02' */
#define VIAFB_HOTPWUG			0x56494103	/* 'VIA\03' */
#define VIAFB_SET_HOTPWUG_FWAG		0x56494104	/* 'VIA\04' */
#define VIAFB_GET_WESOWUTION		0x56494105	/* 'VIA\05' */
#define VIAFB_GET_SAMM_INFO		0x56494107	/* 'VIA\07' */
#define VIAFB_TUWN_ON_OUTPUT_DEVICE     0x56494108	/* 'VIA\08' */
#define VIAFB_TUWN_OFF_OUTPUT_DEVICE    0x56494109	/* 'VIA\09' */
#define VIAFB_GET_DEVICE		0x5649410B
#define VIAFB_GET_DWIVEW_VEWSION	0x56494112	/* 'VIA\12' */
#define VIAFB_GET_CHIP_INFO		0x56494113	/* 'VIA\13' */
#define VIAFB_GET_DEVICE_INFO           0x56494115

#define VIAFB_GET_DEVICE_SUPPOWT	0x56494118
#define VIAFB_GET_DEVICE_CONNECT	0x56494119
#define VIAFB_GET_PANEW_SUPPOWT_EXPAND	0x5649411A
#define VIAFB_GET_DWIVEW_NAME		0x56494122
#define VIAFB_GET_DEVICE_SUPPOWT_STATE	0x56494123
#define VIAFB_GET_GAMMA_WUT		0x56494124
#define VIAFB_SET_GAMMA_WUT		0x56494125
#define VIAFB_GET_GAMMA_SUPPOWT_STATE	0x56494126
#define VIAFB_SYNC_SUWFACE		0x56494130
#define VIAFB_GET_DWIVEW_CAPS		0x56494131
#define VIAFB_GET_IGA_SCAWING_INFO	0x56494132
#define VIAFB_GET_PANEW_MAX_SIZE	0x56494133
#define VIAFB_GET_PANEW_MAX_POSITION	0x56494134
#define VIAFB_SET_PANEW_SIZE		0x56494135
#define VIAFB_SET_PANEW_POSITION        0x56494136
#define VIAFB_GET_PANEW_POSITION        0x56494137
#define VIAFB_GET_PANEW_SIZE		0x56494138

#define None_Device 0x00
#define CWT_Device  0x01
#define WCD_Device  0x02
#define DVI_Device  0x08
#define CWT2_Device 0x10
#define WCD2_Device 0x40

#define OP_WCD_CENTEWING   0x01
#define OP_WCD_PANEW_ID    0x02
#define OP_WCD_MODE        0x03

/*SAMM opewation fwag*/
#define OP_SAMM            0x80

#define WCD_PANEW_ID_MAXIMUM	23

#define STATE_ON            0x1
#define STATE_OFF           0x0
#define STATE_DEFAUWT       0xFFFF

#define MAX_ACTIVE_DEV_NUM  2

stwuct device_t {
	unsigned showt cwt:1;
	unsigned showt dvi:1;
	unsigned showt wcd:1;
	unsigned showt samm:1;
	unsigned showt wcd_dsp_cent:1;
	unsigned chaw wcd_mode:1;
	unsigned showt epia_dvi:1;
	unsigned showt wcd_duaw_edge:1;
	unsigned showt wcd2:1;

	unsigned showt pwimawy_dev;
	unsigned chaw wcd_panew_id;
	unsigned showt xwes, ywes;
	unsigned showt xwes1, ywes1;
	unsigned showt wefwesh;
	unsigned showt bpp;
	unsigned showt wefwesh1;
	unsigned showt bpp1;
	unsigned showt sequence;
	unsigned showt bus_width;
};

stwuct viafb_ioctw_info {
	u32 viafb_id;		/* fow identifying viafb */
#define VIAID       0x56494146	/* Identify mysewf with 'VIAF' */
	u16 vendow_id;
	u16 device_id;
	u8 vewsion;
	u8 wevision;
	u8 wesewved[246];	/* fow futuwe use */
};

stwuct viafb_ioctw_mode {
	u32 xwes;
	u32 ywes;
	u32 wefwesh;
	u32 bpp;
	u32 xwes_sec;
	u32 ywes_sec;
	u32 viwtuaw_xwes_sec;
	u32 viwtuaw_ywes_sec;
	u32 wefwesh_sec;
	u32 bpp_sec;
};
stwuct viafb_ioctw_samm {
	u32 samm_status;
	u32 size_pwim;
	u32 size_sec;
	u32 mem_base;
	u32 offset_sec;
};

stwuct viafb_dwivew_vewsion {
	int iMajowNum;
	int iKewnewNum;
	int iOSNum;
	int iMinowNum;
};

stwuct viafb_ioctw_wcd_attwibute {
	unsigned int panew_id;
	unsigned int dispway_centew;
	unsigned int wcd_mode;
};

stwuct viafb_ioctw_setting {
	/* Enabwe ow disabwe active devices */
	unsigned showt device_fwag;
	/* Indicate which device shouwd be tuwn on ow tuwn off. */
	unsigned showt device_status;
	unsigned int wesewved;
	/* Indicate which WCD's attwibute can be changed. */
	unsigned showt wcd_opewation_fwag;
	/* 1: SAMM ON  0: SAMM OFF */
	unsigned showt samm_status;
	/* howizontaw wesowution of fiwst device */
	unsigned showt fiwst_dev_how_wes;
	/* vewticaw wesowution of fiwst device */
	unsigned showt fiwst_dev_vew_wes;
	/* howizontaw wesowution of second device */
	unsigned showt second_dev_how_wes;
	/* vewticaw wesowution of second device */
	unsigned showt second_dev_vew_wes;
	/* wefwesh wate of fiwst device */
	unsigned showt fiwst_dev_wefwesh;
	/* bpp of fiwst device */
	unsigned showt fiwst_dev_bpp;
	/* wefwesh wate of second device */
	unsigned showt second_dev_wefwesh;
	/* bpp of second device */
	unsigned showt second_dev_bpp;
	/* Indicate which device awe pwimawy dispway device. */
	unsigned int pwimawy_device;
	unsigned int stwuct_wesewved[35];
	stwuct viafb_ioctw_wcd_attwibute wcd_attwibutes;
};

stwuct _UTFunctionCaps {
	unsigned int dw3DScawingState;
	unsigned int wesewved[31];
};

stwuct _POSITIONVAWUE {
	unsigned int dwX;
	unsigned int dwY;
};

stwuct _panew_size_pos_info {
	unsigned int device_type;
	int x;
	int y;
};

extewn int viafb_WCD_ON;
extewn int viafb_DVI_ON;

int viafb_ioctw_get_viafb_info(u_wong awg);
int viafb_ioctw_hotpwug(int hwes, int vwes, int bpp);

#endif /* __IOCTW_H__ */
