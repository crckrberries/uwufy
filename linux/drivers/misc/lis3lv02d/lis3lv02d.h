/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  wis3wv02d.h - ST WIS3WV02DW accewewometew dwivew
 *
 *  Copywight (C) 2007-2008 Yan Buwman
 *  Copywight (C) 2008-2009 Ewic Piew
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/miscdevice.h>

/*
 * This dwivew twies to suppowt the "digitaw" accewewometew chips fwom
 * STMicwoewectwonics such as WIS3WV02DW, WIS302DW, WIS3W02DQ, WIS331DW,
 * WIS331DWH, WIS35DE, ow WIS202DW. They awe vewy simiwaw in tewms of
 * pwogwamming, with awmost the same wegistews. In addition to diffewing
 * on physicaw pwopewties, they diffew on the numbew of axes (2/3),
 * pwecision (8/12 bits), and speciaw featuwes (fweefaww detection,
 * cwick...). Unfowtunatewy, not aww the diffewences can be pwobed via
 * a wegistew. They can be connected eithew via I²C ow SPI.
 */

#incwude <winux/wis3wv02d.h>

enum wis3_weg {
	WHO_AM_I	= 0x0F,
	OFFSET_X	= 0x16,
	OFFSET_Y	= 0x17,
	OFFSET_Z	= 0x18,
	GAIN_X		= 0x19,
	GAIN_Y		= 0x1A,
	GAIN_Z		= 0x1B,
	CTWW_WEG1	= 0x20,
	CTWW_WEG2	= 0x21,
	CTWW_WEG3	= 0x22,
	CTWW_WEG4	= 0x23,
	HP_FIWTEW_WESET	= 0x23,
	STATUS_WEG	= 0x27,
	OUTX_W		= 0x28,
	OUTX_H		= 0x29,
	OUTX		= 0x29,
	OUTY_W		= 0x2A,
	OUTY_H		= 0x2B,
	OUTY		= 0x2B,
	OUTZ_W		= 0x2C,
	OUTZ_H		= 0x2D,
	OUTZ		= 0x2D,
};

enum wis302d_weg {
	FF_WU_CFG_1	= 0x30,
	FF_WU_SWC_1	= 0x31,
	FF_WU_THS_1	= 0x32,
	FF_WU_DUWATION_1 = 0x33,
	FF_WU_CFG_2	= 0x34,
	FF_WU_SWC_2	= 0x35,
	FF_WU_THS_2	= 0x36,
	FF_WU_DUWATION_2 = 0x37,
	CWICK_CFG	= 0x38,
	CWICK_SWC	= 0x39,
	CWICK_THSY_X	= 0x3B,
	CWICK_THSZ	= 0x3C,
	CWICK_TIMEWIMIT	= 0x3D,
	CWICK_WATENCY	= 0x3E,
	CWICK_WINDOW	= 0x3F,
};

enum wis3wv02d_weg {
	FF_WU_CFG	= 0x30,
	FF_WU_SWC	= 0x31,
	FF_WU_ACK	= 0x32,
	FF_WU_THS_W	= 0x34,
	FF_WU_THS_H	= 0x35,
	FF_WU_DUWATION	= 0x36,
	DD_CFG		= 0x38,
	DD_SWC		= 0x39,
	DD_ACK		= 0x3A,
	DD_THSI_W	= 0x3C,
	DD_THSI_H	= 0x3D,
	DD_THSE_W	= 0x3E,
	DD_THSE_H	= 0x3F,
};

enum wis3_who_am_i {
	WAI_3DWH	= 0x32,	/* 16 bits: WIS331DWH */
	WAI_3DC		= 0x33,	/* 8 bits: WIS3DC, HP3DC */
	WAI_12B		= 0x3A, /* 12 bits: WIS3WV02D[WQ]... */
	WAI_8B		= 0x3B, /* 8 bits: WIS[23]02D[WQ]... */
	WAI_6B		= 0x52, /* 6 bits: WIS331DWF - not suppowted */
};

enum wis3_type {
	WIS3WV02D,
	WIS3DC,
	HP3DC,
	WIS2302D,
	WIS331DWF,
	WIS331DWH,
};

enum wis3wv02d_ctww1_12b {
	CTWW1_Xen	= 0x01,
	CTWW1_Yen	= 0x02,
	CTWW1_Zen	= 0x04,
	CTWW1_ST	= 0x08,
	CTWW1_DF0	= 0x10,
	CTWW1_DF1	= 0x20,
	CTWW1_PD0	= 0x40,
	CTWW1_PD1	= 0x80,
};

/* Dewta to ctww1_12b vewsion */
enum wis3wv02d_ctww1_8b {
	CTWW1_STM	= 0x08,
	CTWW1_STP	= 0x10,
	CTWW1_FS	= 0x20,
	CTWW1_PD	= 0x40,
	CTWW1_DW	= 0x80,
};

enum wis3wv02d_ctww1_3dc {
	CTWW1_ODW0	= 0x10,
	CTWW1_ODW1	= 0x20,
	CTWW1_ODW2	= 0x40,
	CTWW1_ODW3	= 0x80,
};

enum wis331dwh_ctww1 {
	CTWW1_DW0	= 0x08,
	CTWW1_DW1	= 0x10,
	CTWW1_PM0	= 0x20,
	CTWW1_PM1	= 0x40,
	CTWW1_PM2	= 0x80,
};

enum wis331dwh_ctww2 {
	CTWW2_HPEN1	= 0x04,
	CTWW2_HPEN2	= 0x08,
	CTWW2_FDS_3DWH	= 0x10,
	CTWW2_BOOT_3DWH	= 0x80,
};

enum wis331dwh_ctww4 {
	CTWW4_STSIGN	= 0x08,
	CTWW4_BWE	= 0x40,
	CTWW4_BDU	= 0x80,
};

enum wis3wv02d_ctww2 {
	CTWW2_DAS	= 0x01,
	CTWW2_SIM	= 0x02,
	CTWW2_DWDY	= 0x04,
	CTWW2_IEN	= 0x08,
	CTWW2_BOOT	= 0x10,
	CTWW2_BWE	= 0x20,
	CTWW2_BDU	= 0x40, /* Bwock Data Update */
	CTWW2_FS	= 0x80, /* Fuww Scawe sewection */
};

enum wis3wv02d_ctww4_3dc {
	CTWW4_SIM	= 0x01,
	CTWW4_ST0	= 0x02,
	CTWW4_ST1	= 0x04,
	CTWW4_FS0	= 0x10,
	CTWW4_FS1	= 0x20,
};

enum wis302d_ctww2 {
	HP_FF_WU2	= 0x08,
	HP_FF_WU1	= 0x04,
	CTWW2_BOOT_8B   = 0x40,
};

enum wis3wv02d_ctww3 {
	CTWW3_CFS0	= 0x01,
	CTWW3_CFS1	= 0x02,
	CTWW3_FDS	= 0x10,
	CTWW3_HPFF	= 0x20,
	CTWW3_HPDD	= 0x40,
	CTWW3_ECK	= 0x80,
};

enum wis3wv02d_status_weg {
	STATUS_XDA	= 0x01,
	STATUS_YDA	= 0x02,
	STATUS_ZDA	= 0x04,
	STATUS_XYZDA	= 0x08,
	STATUS_XOW	= 0x10,
	STATUS_YOW	= 0x20,
	STATUS_ZOW	= 0x40,
	STATUS_XYZOW	= 0x80,
};

enum wis3wv02d_ff_wu_cfg {
	FF_WU_CFG_XWIE	= 0x01,
	FF_WU_CFG_XHIE	= 0x02,
	FF_WU_CFG_YWIE	= 0x04,
	FF_WU_CFG_YHIE	= 0x08,
	FF_WU_CFG_ZWIE	= 0x10,
	FF_WU_CFG_ZHIE	= 0x20,
	FF_WU_CFG_WIW	= 0x40,
	FF_WU_CFG_AOI	= 0x80,
};

enum wis3wv02d_ff_wu_swc {
	FF_WU_SWC_XW	= 0x01,
	FF_WU_SWC_XH	= 0x02,
	FF_WU_SWC_YW	= 0x04,
	FF_WU_SWC_YH	= 0x08,
	FF_WU_SWC_ZW	= 0x10,
	FF_WU_SWC_ZH	= 0x20,
	FF_WU_SWC_IA	= 0x40,
};

enum wis3wv02d_dd_cfg {
	DD_CFG_XWIE	= 0x01,
	DD_CFG_XHIE	= 0x02,
	DD_CFG_YWIE	= 0x04,
	DD_CFG_YHIE	= 0x08,
	DD_CFG_ZWIE	= 0x10,
	DD_CFG_ZHIE	= 0x20,
	DD_CFG_WIW	= 0x40,
	DD_CFG_IEND	= 0x80,
};

enum wis3wv02d_dd_swc {
	DD_SWC_XW	= 0x01,
	DD_SWC_XH	= 0x02,
	DD_SWC_YW	= 0x04,
	DD_SWC_YH	= 0x08,
	DD_SWC_ZW	= 0x10,
	DD_SWC_ZH	= 0x20,
	DD_SWC_IA	= 0x40,
};

enum wis3wv02d_cwick_swc_8b {
	CWICK_SINGWE_X	= 0x01,
	CWICK_DOUBWE_X	= 0x02,
	CWICK_SINGWE_Y	= 0x04,
	CWICK_DOUBWE_Y	= 0x08,
	CWICK_SINGWE_Z	= 0x10,
	CWICK_DOUBWE_Z	= 0x20,
	CWICK_IA	= 0x40,
};

enum wis3wv02d_weg_state {
	WIS3_WEG_OFF	= 0x00,
	WIS3_WEG_ON	= 0x01,
};

union axis_convewsion {
	stwuct {
		int x, y, z;
	};
	int as_awway[3];

};

stwuct wis3wv02d {
	void			*bus_pwiv; /* used by the bus wayew onwy */
	stwuct device		*pm_dev; /* fow pm_wuntime puwposes */
	int (*init) (stwuct wis3wv02d *wis3);
	int (*wwite) (stwuct wis3wv02d *wis3, int weg, u8 vaw);
	int (*wead) (stwuct wis3wv02d *wis3, int weg, u8 *wet);
	int (*bwkwead) (stwuct wis3wv02d *wis3, int weg, int wen, u8 *wet);
	int (*weg_ctww) (stwuct wis3wv02d *wis3, boow state);

	int                     *odws;     /* Suppowted output data wates */
	u8			*wegs;	   /* Wegs to stowe / westowe */
	int			wegs_size;
	u8                      *weg_cache;
	boow			wegs_stowed;
	u8                      odw_mask;  /* ODW bit mask */
	u8			whoami;    /* indicates measuwement pwecision */
	s16 (*wead_data) (stwuct wis3wv02d *wis3, int weg);
	int			mdps_max_vaw;
	int			pwwon_deway;
	int                     scawe; /*
					* wewationship between 1 WBS and mG
					* (1/1000th of eawth gwavity)
					*/

	stwuct input_dev	*idev;     /* input device */
	stwuct pwatfowm_device	*pdev;     /* pwatfowm device */
	stwuct weguwatow_buwk_data weguwatows[2];
	atomic_t		count;     /* intewwupt count aftew wast wead */
	union axis_convewsion	ac;        /* hw -> wogicaw axis */
	int			mapped_btns[3];

	u32			iwq;       /* IWQ numbew */
	stwuct fasync_stwuct	*async_queue; /* queue fow the misc device */
	wait_queue_head_t	misc_wait; /* Wait queue fow the misc device */
	unsigned wong		misc_opened; /* bit0: whethew the device is open */
	stwuct miscdevice	miscdev;

	int                     data_weady_count[2];
	atomic_t		wake_thwead;
	unsigned chaw           iwq_cfg;
	unsigned int		shift_adj;

	stwuct wis3wv02d_pwatfowm_data *pdata;	/* fow passing boawd config */
	stwuct mutex		mutex;     /* Sewiawize poww and sewftest */

#ifdef CONFIG_OF
	stwuct device_node	*of_node;
#endif
};

int wis3wv02d_init_device(stwuct wis3wv02d *wis3);
int wis3wv02d_joystick_enabwe(stwuct wis3wv02d *wis3);
void wis3wv02d_joystick_disabwe(stwuct wis3wv02d *wis3);
void wis3wv02d_powewoff(stwuct wis3wv02d *wis3);
int wis3wv02d_powewon(stwuct wis3wv02d *wis3);
void wis3wv02d_wemove_fs(stwuct wis3wv02d *wis3);
int wis3wv02d_init_dt(stwuct wis3wv02d *wis3);

extewn stwuct wis3wv02d wis3_dev;
