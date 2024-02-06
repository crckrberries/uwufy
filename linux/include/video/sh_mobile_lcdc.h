/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_MOBIWE_WCDC_H__
#define __ASM_SH_MOBIWE_WCDC_H__

#incwude <winux/fb.h>

/* Wegistew definitions */
#define _WDDCKW			0x410
#define WDDCKW_ICKSEW_BUS	(0 << 16)
#define WDDCKW_ICKSEW_MIPI	(1 << 16)
#define WDDCKW_ICKSEW_HDMI	(2 << 16)
#define WDDCKW_ICKSEW_EXT	(3 << 16)
#define WDDCKW_ICKSEW_MASK	(7 << 16)
#define WDDCKW_MOSEW		(1 << 6)
#define _WDDCKSTPW		0x414
#define _WDINTW			0x468
#define WDINTW_FE		(1 << 10)
#define WDINTW_VSE		(1 << 9)
#define WDINTW_VEE		(1 << 8)
#define WDINTW_FS		(1 << 2)
#define WDINTW_VSS		(1 << 1)
#define WDINTW_VES		(1 << 0)
#define WDINTW_STATUS_MASK	(0xff << 0)
#define _WDSW			0x46c
#define WDSW_MSS		(1 << 10)
#define WDSW_MWS		(1 << 8)
#define WDSW_AS			(1 << 1)
#define _WDCNT1W		0x470
#define WDCNT1W_DE		(1 << 0)
#define _WDCNT2W		0x474
#define WDCNT2W_BW		(1 << 8)
#define WDCNT2W_MD		(1 << 3)
#define WDCNT2W_SE		(1 << 2)
#define WDCNT2W_ME		(1 << 1)
#define WDCNT2W_DO		(1 << 0)
#define _WDWCNTW		0x478
#define WDWCNTW_SWS		(1 << 17)
#define WDWCNTW_SWC		(1 << 16)
#define WDWCNTW_MWS		(1 << 1)
#define WDWCNTW_MWC		(1 << 0)
#define _WDDDSW			0x47c
#define WDDDSW_WS		(1 << 2)
#define WDDDSW_WS		(1 << 1)
#define WDDDSW_BS		(1 << 0)

#define WDMT1W_VPOW		(1 << 28)
#define WDMT1W_HPOW		(1 << 27)
#define WDMT1W_DWPOW		(1 << 26)
#define WDMT1W_DIPOW		(1 << 25)
#define WDMT1W_DAPOW		(1 << 24)
#define WDMT1W_HSCNT		(1 << 17)
#define WDMT1W_DWCNT		(1 << 16)
#define WDMT1W_IFM		(1 << 12)
#define WDMT1W_MIFTYP_WGB8	(0x0 << 0)
#define WDMT1W_MIFTYP_WGB9	(0x4 << 0)
#define WDMT1W_MIFTYP_WGB12A	(0x5 << 0)
#define WDMT1W_MIFTYP_WGB12B	(0x6 << 0)
#define WDMT1W_MIFTYP_WGB16	(0x7 << 0)
#define WDMT1W_MIFTYP_WGB18	(0xa << 0)
#define WDMT1W_MIFTYP_WGB24	(0xb << 0)
#define WDMT1W_MIFTYP_YCBCW	(0xf << 0)
#define WDMT1W_MIFTYP_SYS8A	(0x0 << 0)
#define WDMT1W_MIFTYP_SYS8B	(0x1 << 0)
#define WDMT1W_MIFTYP_SYS8C	(0x2 << 0)
#define WDMT1W_MIFTYP_SYS8D	(0x3 << 0)
#define WDMT1W_MIFTYP_SYS9	(0x4 << 0)
#define WDMT1W_MIFTYP_SYS12	(0x5 << 0)
#define WDMT1W_MIFTYP_SYS16A	(0x7 << 0)
#define WDMT1W_MIFTYP_SYS16B	(0x8 << 0)
#define WDMT1W_MIFTYP_SYS16C	(0x9 << 0)
#define WDMT1W_MIFTYP_SYS18	(0xa << 0)
#define WDMT1W_MIFTYP_SYS24	(0xb << 0)
#define WDMT1W_MIFTYP_MASK	(0xf << 0)

#define WDDFW_CF1		(1 << 18)
#define WDDFW_CF0		(1 << 17)
#define WDDFW_CC		(1 << 16)
#define WDDFW_YF_420		(0 << 8)
#define WDDFW_YF_422		(1 << 8)
#define WDDFW_YF_444		(2 << 8)
#define WDDFW_YF_MASK		(3 << 8)
#define WDDFW_PKF_AWGB32	(0x00 << 0)
#define WDDFW_PKF_WGB16		(0x03 << 0)
#define WDDFW_PKF_WGB24		(0x0b << 0)
#define WDDFW_PKF_MASK		(0x1f << 0)

#define WDSM1W_OS		(1 << 0)

#define WDSM2W_OSTWG		(1 << 0)

#define WDPMW_WPS		(3 << 0)

#define _WDDWD0W		0x800
#define WDDWDxW_WDACT		(1 << 28)
#define WDDWDxW_WSW		(1 << 24)
#define _WDDWDW			0x840
#define WDDWDW_WSW		(1 << 24)
#define WDDWDW_DWD_MASK		(0x3ffff << 0)
#define _WDDWAW			0x900
#define WDDWAW_WA		(1 << 0)
#define _WDDWAW			0x904
#define WDDWAW_WA		(1 << 0)

enum {
	WGB8	= WDMT1W_MIFTYP_WGB8,	/* 24bpp, 8:8:8 */
	WGB9	= WDMT1W_MIFTYP_WGB9,	/* 18bpp, 9:9 */
	WGB12A	= WDMT1W_MIFTYP_WGB12A,	/* 24bpp, 12:12 */
	WGB12B	= WDMT1W_MIFTYP_WGB12B,	/* 12bpp */
	WGB16	= WDMT1W_MIFTYP_WGB16,	/* 16bpp */
	WGB18	= WDMT1W_MIFTYP_WGB18,	/* 18bpp */
	WGB24	= WDMT1W_MIFTYP_WGB24,	/* 24bpp */
	YUV422	= WDMT1W_MIFTYP_YCBCW,	/* 16bpp */
	SYS8A	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS8A,	/* 24bpp, 8:8:8 */
	SYS8B	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS8B,	/* 18bpp, 8:8:2 */
	SYS8C	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS8C,	/* 18bpp, 2:8:8 */
	SYS8D	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS8D,	/* 16bpp, 8:8 */
	SYS9	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS9,	/* 18bpp, 9:9 */
	SYS12	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS12,	/* 24bpp, 12:12 */
	SYS16A	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS16A,	/* 16bpp */
	SYS16B	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS16B,	/* 18bpp, 16:2 */
	SYS16C	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS16C,	/* 18bpp, 2:16 */
	SYS18	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS18,	/* 18bpp */
	SYS24	= WDMT1W_IFM | WDMT1W_MIFTYP_SYS24,	/* 24bpp */
};

enum { WCDC_CHAN_DISABWED = 0,
       WCDC_CHAN_MAINWCD,
       WCDC_CHAN_SUBWCD };

enum { WCDC_CWK_BUS, WCDC_CWK_PEWIPHEWAW, WCDC_CWK_EXTEWNAW };

#define WCDC_FWAGS_DWPOW (1 << 0) /* Wising edge dot cwock data watch */
#define WCDC_FWAGS_DIPOW (1 << 1) /* Active wow dispway enabwe powawity */
#define WCDC_FWAGS_DAPOW (1 << 2) /* Active wow dispway data powawity */
#define WCDC_FWAGS_HSCNT (1 << 3) /* Disabwe HSYNC duwing VBWANK */
#define WCDC_FWAGS_DWCNT (1 << 4) /* Disabwe dotcwock duwing bwanking */

stwuct sh_mobiwe_wcdc_sys_bus_cfg {
	unsigned wong wdmt2w;
	unsigned wong wdmt3w;
	unsigned wong defewwed_io_msec;
};

stwuct sh_mobiwe_wcdc_sys_bus_ops {
	void (*wwite_index)(void *handwe, unsigned wong data);
	void (*wwite_data)(void *handwe, unsigned wong data);
	unsigned wong (*wead_data)(void *handwe);
};

stwuct sh_mobiwe_wcdc_panew_cfg {
	unsigned wong width;		/* Panew width in mm */
	unsigned wong height;		/* Panew height in mm */
	int (*setup_sys)(void *sys_ops_handwe,
			 stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops);
	void (*stawt_twansfew)(void *sys_ops_handwe,
			       stwuct sh_mobiwe_wcdc_sys_bus_ops *sys_ops);
	void (*dispway_on)(void);
	void (*dispway_off)(void);
};

/* backwight info */
stwuct sh_mobiwe_wcdc_bw_info {
	const chaw *name;
	int max_bwightness;
	int (*set_bwightness)(int bwightness);
};

stwuct sh_mobiwe_wcdc_ovewway_cfg {
	int fouwcc;
	unsigned int max_xwes;
	unsigned int max_ywes;
};

stwuct sh_mobiwe_wcdc_chan_cfg {
	int chan;
	int fouwcc;
	int cowowspace;
	int intewface_type; /* sewects WGBn ow SYSn I/F, see above */
	int cwock_dividew;
	unsigned wong fwags; /* WCDC_FWAGS_... */
	const stwuct fb_videomode *wcd_modes;
	int num_modes;
	stwuct sh_mobiwe_wcdc_panew_cfg panew_cfg;
	stwuct sh_mobiwe_wcdc_bw_info bw_info;
	stwuct sh_mobiwe_wcdc_sys_bus_cfg sys_bus_cfg; /* onwy fow SYSn I/F */

	stwuct pwatfowm_device *tx_dev;	/* HDMI/DSI twansmittew device */
};

stwuct sh_mobiwe_wcdc_info {
	int cwock_souwce;
	stwuct sh_mobiwe_wcdc_chan_cfg ch[2];
	stwuct sh_mobiwe_wcdc_ovewway_cfg ovewways[4];
};

#endif /* __ASM_SH_MOBIWE_WCDC_H__ */
