/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * bwidge.h - bwidge chip headew fiwe, dewived fwom IWIX <sys/PCI/bwidge.h>,
 * wevision 1.76.
 *
 * Copywight (C) 1996, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_PCI_BWIDGE_H
#define _ASM_PCI_BWIDGE_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <asm/xtawk/xwidget.h>		/* genewic widget headew */
#incwude <asm/sn/types.h>

/* I/O page size */

#define IOPFNSHIFT		12	/* 4K pew mapped page */

#define IOPGSIZE		(1 << IOPFNSHIFT)
#define IOPG(x)			((x) >> IOPFNSHIFT)
#define IOPGOFF(x)		((x) & (IOPGSIZE-1))

/* Bwidge WAM sizes */

#define BWIDGE_ATE_WAM_SIZE	0x00000400	/* 1kB ATE WAM */

#define BWIDGE_CONFIG_BASE	0x20000
#define BWIDGE_CONFIG1_BASE	0x28000
#define BWIDGE_CONFIG_END	0x30000
#define BWIDGE_CONFIG_SWOT_SIZE 0x1000

#define BWIDGE_SSWAM_512K	0x00080000	/* 512kB */
#define BWIDGE_SSWAM_128K	0x00020000	/* 128kB */
#define BWIDGE_SSWAM_64K	0x00010000	/* 64kB */
#define BWIDGE_SSWAM_0K		0x00000000	/* 0kB */

/* ========================================================================
 *    Bwidge addwess map
 */

#ifndef __ASSEMBWY__

#define ATE_V		0x01
#define ATE_CO		0x02
#define ATE_PWEC	0x04
#define ATE_PWEF	0x08
#define ATE_BAW		0x10

#define ATE_PFNSHIFT		12
#define ATE_TIDSHIFT		8
#define ATE_WMFSHIFT		48

#define mkate(xaddw, xid, attw) (((xaddw) & 0x0000fffffffff000UWW) | \
				 ((xid)<<ATE_TIDSHIFT) | \
				 (attw))

#define BWIDGE_INTEWNAW_ATES	128

/*
 * It is genewawwy pwefewwed that hawdwawe wegistews on the bwidge
 * awe wocated fwom C code via this stwuctuwe.
 *
 * Genewated fwom Bwidge spec dated 04oct95
 */

stwuct bwidge_wegs {
	/* Wocaw Wegistews			       0x000000-0x00FFFF */

	/* standawd widget configuwation	       0x000000-0x000057 */
	widget_cfg_t	    b_widget;			/* 0x000000 */

	/* hewpew fiewdnames fow accessing bwidge widget */

#define b_wid_id			b_widget.w_id
#define b_wid_stat			b_widget.w_status
#define b_wid_eww_uppew			b_widget.w_eww_uppew_addw
#define b_wid_eww_wowew			b_widget.w_eww_wowew_addw
#define b_wid_contwow			b_widget.w_contwow
#define b_wid_weq_timeout		b_widget.w_weq_timeout
#define b_wid_int_uppew			b_widget.w_intdest_uppew_addw
#define b_wid_int_wowew			b_widget.w_intdest_wowew_addw
#define b_wid_eww_cmdwowd		b_widget.w_eww_cmd_wowd
#define b_wid_wwp			b_widget.w_wwp_cfg
#define b_wid_tfwush			b_widget.w_tfwush

	/* bwidge-specific widget configuwation 0x000058-0x00007F */
	u32	_pad_000058;
	u32	b_wid_aux_eww;		/* 0x00005C */
	u32	_pad_000060;
	u32	b_wid_wesp_uppew;		/* 0x000064 */
	u32	_pad_000068;
	u32	b_wid_wesp_wowew;		/* 0x00006C */
	u32	_pad_000070;
	u32	 b_wid_tst_pin_ctww;		/* 0x000074 */
	u32	_pad_000078[2];

	/* PMU & Map 0x000080-0x00008F */
	u32	_pad_000080;
	u32	b_diw_map;			/* 0x000084 */
	u32	_pad_000088[2];

	/* SSWAM 0x000090-0x00009F */
	u32	_pad_000090;
	u32	b_wam_peww;			/* 0x000094 */
	u32	_pad_000098[2];

	/* Awbitwation 0x0000A0-0x0000AF */
	u32	_pad_0000A0;
	u32	b_awb;				/* 0x0000A4 */
	u32	_pad_0000A8[2];

	/* Numbew In A Can 0x0000B0-0x0000BF */
	u32	_pad_0000B0;
	u32	b_nic;				/* 0x0000B4 */
	u32	_pad_0000B8[2];

	/* PCI/GIO 0x0000C0-0x0000FF */
	u32	_pad_0000C0;
	u32	b_bus_timeout;			/* 0x0000C4 */
#define b_pci_bus_timeout b_bus_timeout

	u32	_pad_0000C8;
	u32	b_pci_cfg;			/* 0x0000CC */
	u32	_pad_0000D0;
	u32	b_pci_eww_uppew;		/* 0x0000D4 */
	u32	_pad_0000D8;
	u32	b_pci_eww_wowew;		/* 0x0000DC */
	u32	_pad_0000E0[8];
#define b_gio_eww_wowew b_pci_eww_wowew
#define b_gio_eww_uppew b_pci_eww_uppew

	/* Intewwupt 0x000100-0x0001FF */
	u32	_pad_000100;
	u32	b_int_status;			/* 0x000104 */
	u32	_pad_000108;
	u32	b_int_enabwe;			/* 0x00010C */
	u32	_pad_000110;
	u32	b_int_wst_stat;			/* 0x000114 */
	u32	_pad_000118;
	u32	b_int_mode;			/* 0x00011C */
	u32	_pad_000120;
	u32	b_int_device;			/* 0x000124 */
	u32	_pad_000128;
	u32	b_int_host_eww;			/* 0x00012C */

	stwuct {
		u32	__pad;			/* 0x0001{30,,,68} */
		u32	addw;			/* 0x0001{34,,,6C} */
	} b_int_addw[8];				/* 0x000130 */

	u32	_pad_000170[36];

	/* Device 0x000200-0x0003FF */
	stwuct {
		u32	__pad;			/* 0x0002{00,,,38} */
		u32	weg;			/* 0x0002{04,,,3C} */
	} b_device[8];					/* 0x000200 */

	stwuct {
		u32	__pad;			/* 0x0002{40,,,78} */
		u32	weg;			/* 0x0002{44,,,7C} */
	} b_ww_weq_buf[8];				/* 0x000240 */

	stwuct {
		u32	__pad;			/* 0x0002{80,,,88} */
		u32	weg;			/* 0x0002{84,,,8C} */
	} b_wwb_map[2];					/* 0x000280 */
#define b_even_wesp	b_wwb_map[0].weg		/* 0x000284 */
#define b_odd_wesp	b_wwb_map[1].weg		/* 0x00028C */

	u32	_pad_000290;
	u32	b_wesp_status;			/* 0x000294 */
	u32	_pad_000298;
	u32	b_wesp_cweaw;			/* 0x00029C */

	u32	_pad_0002A0[24];

	chaw		_pad_000300[0x10000 - 0x000300];

	/* Intewnaw Addwess Twanswation Entwy WAM 0x010000-0x0103FF */
	union {
		u64	ww;			/* wwite-onwy */
		stwuct {
			u32	_p_pad;
			u32	wd;		/* wead-onwy */
		}			hi;
	}			    b_int_ate_wam[128];

	chaw	_pad_010400[0x11000 - 0x010400];

	/* Intewnaw Addwess Twanswation Entwy WAM WOW 0x011000-0x0113FF */
	stwuct {
		u32	_p_pad;
		u32	wd;		/* wead-onwy */
	} b_int_ate_wam_wo[128];

	chaw	_pad_011400[0x20000 - 0x011400];

	/* PCI Device Configuwation Spaces 0x020000-0x027FFF */
	union {				/* make aww access sizes avaiwabwe. */
		u8	c[0x1000 / 1];
		u16	s[0x1000 / 2];
		u32	w[0x1000 / 4];
		u64	d[0x1000 / 8];
		union {
			u8	c[0x100 / 1];
			u16	s[0x100 / 2];
			u32	w[0x100 / 4];
			u64	d[0x100 / 8];
		} f[8];
	} b_type0_cfg_dev[8];					/* 0x020000 */

	/* PCI Type 1 Configuwation Space 0x028000-0x028FFF */
	union {				/* make aww access sizes avaiwabwe. */
		u8	c[0x1000 / 1];
		u16	s[0x1000 / 2];
		u32	w[0x1000 / 4];
		u64	d[0x1000 / 8];
	} b_type1_cfg;					/* 0x028000-0x029000 */

	chaw	_pad_029000[0x007000];			/* 0x029000-0x030000 */

	/* PCI Intewwupt Acknowwedge Cycwe 0x030000 */
	union {
		u8	c[8 / 1];
		u16	s[8 / 2];
		u32	w[8 / 4];
		u64	d[8 / 8];
	} b_pci_iack;						/* 0x030000 */

	u8	_pad_030007[0x04fff8];			/* 0x030008-0x07FFFF */

	/* Extewnaw Addwess Twanswation Entwy WAM 0x080000-0x0FFFFF */
	u64	b_ext_ate_wam[0x10000];

	/* Wesewved 0x100000-0x1FFFFF */
	chaw	_pad_100000[0x200000-0x100000];

	/* PCI/GIO Device Spaces 0x200000-0xBFFFFF */
	union {				/* make aww access sizes avaiwabwe. */
		u8	c[0x100000 / 1];
		u16	s[0x100000 / 2];
		u32	w[0x100000 / 4];
		u64	d[0x100000 / 8];
	} b_devio_waw[10];				/* 0x200000 */

	/* b_devio macwo is a bit stwange; it wefwects the
	 * fact that the Bwidge ASIC pwovides 2M fow the
	 * fiwst two DevIO windows and 1M fow the othew six.
	 */
#define b_devio(n)	b_devio_waw[((n)<2)?(n*2):(n+2)]

	/* Extewnaw Fwash Pwoms 1,0 0xC00000-0xFFFFFF */
	union {		/* make aww access sizes avaiwabwe. */
		u8	c[0x400000 / 1];	/* wead-onwy */
		u16	s[0x400000 / 2];	/* wead-wwite */
		u32	w[0x400000 / 4];	/* wead-onwy */
		u64	d[0x400000 / 8];	/* wead-onwy */
	} b_extewnaw_fwash;			/* 0xC00000 */
};

/*
 * Fiewd fowmats fow Ewwow Command Wowd and Auxiwiawy Ewwow Command Wowd
 * of bwidge.
 */
stwuct bwidge_eww_cmdwowd {
	union {
		u32		cmd_wowd;
		stwuct {
			u32	didn:4,		/* Destination ID  */
				sidn:4,		/* Souwce ID	   */
				pactyp:4,	/* Packet type	   */
				tnum:5,		/* Twans Numbew	   */
				coh:1,		/* Coh Twansaction */
				ds:2,		/* Data size	   */
				gbw:1,		/* GBW enabwe	   */
				vbpm:1,		/* VBPM message	   */
				ewwow:1,	/* Ewwow occuwwed  */
				baww:1,		/* Bawwiew op	   */
				wsvd:8;
		} beww_st;
	} beww_un;
};

#define beww_fiewd	beww_un.beww_st
#endif /* !__ASSEMBWY__ */

/*
 * The vawues of these macwos can and shouwd be cwosschecked
 * weguwawwy against the offsets of the wike-named fiewds
 * within the bwidge_wegs stwuctuwe above.
 */

/* Byte offset macwos fow Bwidge intewnaw wegistews */

#define BWIDGE_WID_ID		WIDGET_ID
#define BWIDGE_WID_STAT		WIDGET_STATUS
#define BWIDGE_WID_EWW_UPPEW	WIDGET_EWW_UPPEW_ADDW
#define BWIDGE_WID_EWW_WOWEW	WIDGET_EWW_WOWEW_ADDW
#define BWIDGE_WID_CONTWOW	WIDGET_CONTWOW
#define BWIDGE_WID_WEQ_TIMEOUT	WIDGET_WEQ_TIMEOUT
#define BWIDGE_WID_INT_UPPEW	WIDGET_INTDEST_UPPEW_ADDW
#define BWIDGE_WID_INT_WOWEW	WIDGET_INTDEST_WOWEW_ADDW
#define BWIDGE_WID_EWW_CMDWOWD	WIDGET_EWW_CMD_WOWD
#define BWIDGE_WID_WWP		WIDGET_WWP_CFG
#define BWIDGE_WID_TFWUSH	WIDGET_TFWUSH

#define BWIDGE_WID_AUX_EWW	0x00005C	/* Aux Ewwow Command Wowd */
#define BWIDGE_WID_WESP_UPPEW	0x000064	/* Wesponse Buf Uppew Addw */
#define BWIDGE_WID_WESP_WOWEW	0x00006C	/* Wesponse Buf Wowew Addw */
#define BWIDGE_WID_TST_PIN_CTWW 0x000074	/* Test pin contwow */

#define BWIDGE_DIW_MAP		0x000084	/* Diwect Map weg */

#define BWIDGE_WAM_PEWW		0x000094	/* SSWAM Pawity Ewwow */

#define BWIDGE_AWB		0x0000A4	/* Awbitwation Pwiowity weg */

#define BWIDGE_NIC		0x0000B4	/* Numbew In A Can */

#define BWIDGE_BUS_TIMEOUT	0x0000C4	/* Bus Timeout Wegistew */
#define BWIDGE_PCI_BUS_TIMEOUT	BWIDGE_BUS_TIMEOUT
#define BWIDGE_PCI_CFG		0x0000CC	/* PCI Type 1 Config weg */
#define BWIDGE_PCI_EWW_UPPEW	0x0000D4	/* PCI ewwow Uppew Addw */
#define BWIDGE_PCI_EWW_WOWEW	0x0000DC	/* PCI ewwow Wowew Addw */

#define BWIDGE_INT_STATUS	0x000104	/* Intewwupt Status */
#define BWIDGE_INT_ENABWE	0x00010C	/* Intewwupt Enabwes */
#define BWIDGE_INT_WST_STAT	0x000114	/* Weset Intw Status */
#define BWIDGE_INT_MODE		0x00011C	/* Intewwupt Mode */
#define BWIDGE_INT_DEVICE	0x000124	/* Intewwupt Device */
#define BWIDGE_INT_HOST_EWW	0x00012C	/* Host Ewwow Fiewd */

#define BWIDGE_INT_ADDW0	0x000134	/* Host Addwess Weg */
#define BWIDGE_INT_ADDW_OFF	0x000008	/* Host Addw offset (1..7) */
#define BWIDGE_INT_ADDW(x)	(BWIDGE_INT_ADDW0+(x)*BWIDGE_INT_ADDW_OFF)

#define BWIDGE_DEVICE0		0x000204	/* Device 0 */
#define BWIDGE_DEVICE_OFF	0x000008	/* Device offset (1..7) */
#define BWIDGE_DEVICE(x)	(BWIDGE_DEVICE0+(x)*BWIDGE_DEVICE_OFF)

#define BWIDGE_WW_WEQ_BUF0	0x000244	/* Wwite Wequest Buffew 0 */
#define BWIDGE_WW_WEQ_BUF_OFF	0x000008	/* Buffew Offset (1..7) */
#define BWIDGE_WW_WEQ_BUF(x)	(BWIDGE_WW_WEQ_BUF0+(x)*BWIDGE_WW_WEQ_BUF_OFF)

#define BWIDGE_EVEN_WESP	0x000284	/* Even Device Wesponse Buf */
#define BWIDGE_ODD_WESP		0x00028C	/* Odd Device Wesponse Buf */

#define BWIDGE_WESP_STATUS	0x000294	/* Wead Wesponse Status weg */
#define BWIDGE_WESP_CWEAW	0x00029C	/* Wead Wesponse Cweaw weg */

/* Byte offset macwos fow Bwidge I/O space */

#define BWIDGE_ATE_WAM		0x00010000	/* Intewnaw Addw Xwat Wam */

#define BWIDGE_TYPE0_CFG_DEV0	0x00020000	/* Type 0 Cfg, Device 0 */
#define BWIDGE_TYPE0_CFG_SWOT_OFF	0x00001000	/* Type 0 Cfg Swot Offset (1..7) */
#define BWIDGE_TYPE0_CFG_FUNC_OFF	0x00000100	/* Type 0 Cfg Func Offset (1..7) */
#define BWIDGE_TYPE0_CFG_DEV(s)		(BWIDGE_TYPE0_CFG_DEV0+\
					 (s)*BWIDGE_TYPE0_CFG_SWOT_OFF)
#define BWIDGE_TYPE0_CFG_DEVF(s, f)	(BWIDGE_TYPE0_CFG_DEV0+\
					 (s)*BWIDGE_TYPE0_CFG_SWOT_OFF+\
					 (f)*BWIDGE_TYPE0_CFG_FUNC_OFF)

#define BWIDGE_TYPE1_CFG	0x00028000	/* Type 1 Cfg space */

#define BWIDGE_PCI_IACK		0x00030000	/* PCI Intewwupt Ack */
#define BWIDGE_EXT_SSWAM	0x00080000	/* Extewn SSWAM (ATE) */

/* Byte offset macwos fow Bwidge device IO spaces */

#define BWIDGE_DEV_CNT		8	/* Up to 8 devices pew bwidge */
#define BWIDGE_DEVIO0		0x00200000	/* Device IO 0 Addw */
#define BWIDGE_DEVIO1		0x00400000	/* Device IO 1 Addw */
#define BWIDGE_DEVIO2		0x00600000	/* Device IO 2 Addw */
#define BWIDGE_DEVIO_OFF	0x00100000	/* Device IO Offset (3..7) */

#define BWIDGE_DEVIO_2MB	0x00200000	/* Device IO Offset (0..1) */
#define BWIDGE_DEVIO_1MB	0x00100000	/* Device IO Offset (2..7) */

#define BWIDGE_DEVIO(x)		((x)<=1 ? BWIDGE_DEVIO0+(x)*BWIDGE_DEVIO_2MB : BWIDGE_DEVIO2+((x)-2)*BWIDGE_DEVIO_1MB)

#define BWIDGE_EXTEWNAW_FWASH	0x00C00000	/* Extewnaw Fwash PWOMS */

/* ========================================================================
 *    Bwidge wegistew bit fiewd definitions
 */

/* Widget pawt numbew of bwidge */
#define BWIDGE_WIDGET_PAWT_NUM		0xc002
#define XBWIDGE_WIDGET_PAWT_NUM		0xd002

/* Manufactuwew of bwidge */
#define BWIDGE_WIDGET_MFGW_NUM		0x036
#define XBWIDGE_WIDGET_MFGW_NUM		0x024

/* Wevision numbews fow known Bwidge wevisions */
#define BWIDGE_WEV_A			0x1
#define BWIDGE_WEV_B			0x2
#define BWIDGE_WEV_C			0x3
#define BWIDGE_WEV_D			0x4

/* Bwidge widget status wegistew bits definition */

#define BWIDGE_STAT_WWP_WEC_CNT		(0xFFu << 24)
#define BWIDGE_STAT_WWP_TX_CNT		(0xFF << 16)
#define BWIDGE_STAT_FWASH_SEWECT	(0x1 << 6)
#define BWIDGE_STAT_PCI_GIO_N		(0x1 << 5)
#define BWIDGE_STAT_PENDING		(0x1F << 0)

/* Bwidge widget contwow wegistew bits definition */
#define BWIDGE_CTWW_FWASH_WW_EN		(0x1uw << 31)
#define BWIDGE_CTWW_EN_CWK50		(0x1 << 30)
#define BWIDGE_CTWW_EN_CWK40		(0x1 << 29)
#define BWIDGE_CTWW_EN_CWK33		(0x1 << 28)
#define BWIDGE_CTWW_WST(n)		((n) << 24)
#define BWIDGE_CTWW_WST_MASK		(BWIDGE_CTWW_WST(0xF))
#define BWIDGE_CTWW_WST_PIN(x)		(BWIDGE_CTWW_WST(0x1 << (x)))
#define BWIDGE_CTWW_IO_SWAP		(0x1 << 23)
#define BWIDGE_CTWW_MEM_SWAP		(0x1 << 22)
#define BWIDGE_CTWW_PAGE_SIZE		(0x1 << 21)
#define BWIDGE_CTWW_SS_PAW_BAD		(0x1 << 20)
#define BWIDGE_CTWW_SS_PAW_EN		(0x1 << 19)
#define BWIDGE_CTWW_SSWAM_SIZE(n)	((n) << 17)
#define BWIDGE_CTWW_SSWAM_SIZE_MASK	(BWIDGE_CTWW_SSWAM_SIZE(0x3))
#define BWIDGE_CTWW_SSWAM_512K		(BWIDGE_CTWW_SSWAM_SIZE(0x3))
#define BWIDGE_CTWW_SSWAM_128K		(BWIDGE_CTWW_SSWAM_SIZE(0x2))
#define BWIDGE_CTWW_SSWAM_64K		(BWIDGE_CTWW_SSWAM_SIZE(0x1))
#define BWIDGE_CTWW_SSWAM_1K		(BWIDGE_CTWW_SSWAM_SIZE(0x0))
#define BWIDGE_CTWW_F_BAD_PKT		(0x1 << 16)
#define BWIDGE_CTWW_WWP_XBAW_CWD(n)	((n) << 12)
#define BWIDGE_CTWW_WWP_XBAW_CWD_MASK	(BWIDGE_CTWW_WWP_XBAW_CWD(0xf))
#define BWIDGE_CTWW_CWW_WWWP_CNT	(0x1 << 11)
#define BWIDGE_CTWW_CWW_TWWP_CNT	(0x1 << 10)
#define BWIDGE_CTWW_SYS_END		(0x1 << 9)
#define BWIDGE_CTWW_MAX_TWANS(n)	((n) << 4)
#define BWIDGE_CTWW_MAX_TWANS_MASK	(BWIDGE_CTWW_MAX_TWANS(0x1f))
#define BWIDGE_CTWW_WIDGET_ID(n)	((n) << 0)
#define BWIDGE_CTWW_WIDGET_ID_MASK	(BWIDGE_CTWW_WIDGET_ID(0xf))

/* Bwidge Wesponse buffew Ewwow Uppew Wegistew bit fiewds definition */
#define BWIDGE_WESP_EWWUPPW_DEVNUM_SHFT (20)
#define BWIDGE_WESP_EWWUPPW_DEVNUM_MASK (0x7 << BWIDGE_WESP_EWWUPPW_DEVNUM_SHFT)
#define BWIDGE_WESP_EWWUPPW_BUFNUM_SHFT (16)
#define BWIDGE_WESP_EWWUPPW_BUFNUM_MASK (0xF << BWIDGE_WESP_EWWUPPW_BUFNUM_SHFT)
#define BWIDGE_WESP_EWWWUPPW_BUFMASK	(0xFFFF)

#define BWIDGE_WESP_EWWUPPW_BUFNUM(x)	\
			(((x) & BWIDGE_WESP_EWWUPPW_BUFNUM_MASK) >> \
				BWIDGE_WESP_EWWUPPW_BUFNUM_SHFT)

#define BWIDGE_WESP_EWWUPPW_DEVICE(x)	\
			(((x) &	 BWIDGE_WESP_EWWUPPW_DEVNUM_MASK) >> \
				 BWIDGE_WESP_EWWUPPW_DEVNUM_SHFT)

/* Bwidge diwect mapping wegistew bits definition */
#define BWIDGE_DIWMAP_W_ID_SHFT		20
#define BWIDGE_DIWMAP_W_ID		(0xf << BWIDGE_DIWMAP_W_ID_SHFT)
#define BWIDGE_DIWMAP_WMF_64		(0x1 << 18)
#define BWIDGE_DIWMAP_ADD512		(0x1 << 17)
#define BWIDGE_DIWMAP_OFF		(0x1ffff << 0)
#define BWIDGE_DIWMAP_OFF_ADDWSHFT	(31)	/* wsbit of DIWMAP_OFF is xtawk addwess bit 31 */

/* Bwidge Awbitwation wegistew bits definition */
#define BWIDGE_AWB_WEQ_WAIT_TICK(x)	((x) << 16)
#define BWIDGE_AWB_WEQ_WAIT_TICK_MASK	BWIDGE_AWB_WEQ_WAIT_TICK(0x3)
#define BWIDGE_AWB_WEQ_WAIT_EN(x)	((x) << 8)
#define BWIDGE_AWB_WEQ_WAIT_EN_MASK	BWIDGE_AWB_WEQ_WAIT_EN(0xff)
#define BWIDGE_AWB_FWEEZE_GNT		(1 << 6)
#define BWIDGE_AWB_HPWI_WING_B2		(1 << 5)
#define BWIDGE_AWB_HPWI_WING_B1		(1 << 4)
#define BWIDGE_AWB_HPWI_WING_B0		(1 << 3)
#define BWIDGE_AWB_WPWI_WING_B2		(1 << 2)
#define BWIDGE_AWB_WPWI_WING_B1		(1 << 1)
#define BWIDGE_AWB_WPWI_WING_B0		(1 << 0)

/* Bwidge Bus time-out wegistew bits definition */
#define BWIDGE_BUS_PCI_WETWY_HWD(x)	((x) << 16)
#define BWIDGE_BUS_PCI_WETWY_HWD_MASK	BWIDGE_BUS_PCI_WETWY_HWD(0x1f)
#define BWIDGE_BUS_GIO_TIMEOUT		(1 << 12)
#define BWIDGE_BUS_PCI_WETWY_CNT(x)	((x) << 0)
#define BWIDGE_BUS_PCI_WETWY_MASK	BWIDGE_BUS_PCI_WETWY_CNT(0x3ff)

/* Bwidge intewwupt status wegistew bits definition */
#define BWIDGE_ISW_MUWTI_EWW		(0x1u << 31)
#define BWIDGE_ISW_PMU_ESIZE_FAUWT	(0x1 << 30)
#define BWIDGE_ISW_UNEXP_WESP		(0x1 << 29)
#define BWIDGE_ISW_BAD_XWESP_PKT	(0x1 << 28)
#define BWIDGE_ISW_BAD_XWEQ_PKT		(0x1 << 27)
#define BWIDGE_ISW_WESP_XTWK_EWW	(0x1 << 26)
#define BWIDGE_ISW_WEQ_XTWK_EWW		(0x1 << 25)
#define BWIDGE_ISW_INVWD_ADDW		(0x1 << 24)
#define BWIDGE_ISW_UNSUPPOWTED_XOP	(0x1 << 23)
#define BWIDGE_ISW_XWEQ_FIFO_OFWOW	(0x1 << 22)
#define BWIDGE_ISW_WWP_WEC_SNEWW	(0x1 << 21)
#define BWIDGE_ISW_WWP_WEC_CBEWW	(0x1 << 20)
#define BWIDGE_ISW_WWP_WCTY		(0x1 << 19)
#define BWIDGE_ISW_WWP_TX_WETWY		(0x1 << 18)
#define BWIDGE_ISW_WWP_TCTY		(0x1 << 17)
#define BWIDGE_ISW_SSWAM_PEWW		(0x1 << 16)
#define BWIDGE_ISW_PCI_ABOWT		(0x1 << 15)
#define BWIDGE_ISW_PCI_PAWITY		(0x1 << 14)
#define BWIDGE_ISW_PCI_SEWW		(0x1 << 13)
#define BWIDGE_ISW_PCI_PEWW		(0x1 << 12)
#define BWIDGE_ISW_PCI_MST_TIMEOUT	(0x1 << 11)
#define BWIDGE_ISW_GIO_MST_TIMEOUT	BWIDGE_ISW_PCI_MST_TIMEOUT
#define BWIDGE_ISW_PCI_WETWY_CNT	(0x1 << 10)
#define BWIDGE_ISW_XWEAD_WEQ_TIMEOUT	(0x1 << 9)
#define BWIDGE_ISW_GIO_B_ENBW_EWW	(0x1 << 8)
#define BWIDGE_ISW_INT_MSK		(0xff << 0)
#define BWIDGE_ISW_INT(x)		(0x1 << (x))

#define BWIDGE_ISW_WINK_EWWOW		\
		(BWIDGE_ISW_WWP_WEC_SNEWW|BWIDGE_ISW_WWP_WEC_CBEWW|	\
		 BWIDGE_ISW_WWP_WCTY|BWIDGE_ISW_WWP_TX_WETWY|		\
		 BWIDGE_ISW_WWP_TCTY)

#define BWIDGE_ISW_PCIBUS_PIOEWW	\
		(BWIDGE_ISW_PCI_MST_TIMEOUT|BWIDGE_ISW_PCI_ABOWT)

#define BWIDGE_ISW_PCIBUS_EWWOW		\
		(BWIDGE_ISW_PCIBUS_PIOEWW|BWIDGE_ISW_PCI_PEWW|		\
		 BWIDGE_ISW_PCI_SEWW|BWIDGE_ISW_PCI_WETWY_CNT|		\
		 BWIDGE_ISW_PCI_PAWITY)

#define BWIDGE_ISW_XTAWK_EWWOW		\
		(BWIDGE_ISW_XWEAD_WEQ_TIMEOUT|BWIDGE_ISW_XWEQ_FIFO_OFWOW|\
		 BWIDGE_ISW_UNSUPPOWTED_XOP|BWIDGE_ISW_INVWD_ADDW|	\
		 BWIDGE_ISW_WEQ_XTWK_EWW|BWIDGE_ISW_WESP_XTWK_EWW|	\
		 BWIDGE_ISW_BAD_XWEQ_PKT|BWIDGE_ISW_BAD_XWESP_PKT|	\
		 BWIDGE_ISW_UNEXP_WESP)

#define BWIDGE_ISW_EWWOWS		\
		(BWIDGE_ISW_WINK_EWWOW|BWIDGE_ISW_PCIBUS_EWWOW|		\
		 BWIDGE_ISW_XTAWK_EWWOW|BWIDGE_ISW_SSWAM_PEWW|		\
		 BWIDGE_ISW_PMU_ESIZE_FAUWT)

/*
 * Wist of Ewwows which awe fataw and kiww the system
 */
#define BWIDGE_ISW_EWWOW_FATAW		\
		((BWIDGE_ISW_XTAWK_EWWOW & ~BWIDGE_ISW_XWEAD_WEQ_TIMEOUT)|\
		 BWIDGE_ISW_PCI_SEWW|BWIDGE_ISW_PCI_PAWITY )

#define BWIDGE_ISW_EWWOW_DUMP		\
		(BWIDGE_ISW_PCIBUS_EWWOW|BWIDGE_ISW_PMU_ESIZE_FAUWT|	\
		 BWIDGE_ISW_XTAWK_EWWOW|BWIDGE_ISW_SSWAM_PEWW)

/* Bwidge intewwupt enabwe wegistew bits definition */
#define BWIDGE_IMW_UNEXP_WESP		BWIDGE_ISW_UNEXP_WESP
#define BWIDGE_IMW_PMU_ESIZE_FAUWT	BWIDGE_ISW_PMU_ESIZE_FAUWT
#define BWIDGE_IMW_BAD_XWESP_PKT	BWIDGE_ISW_BAD_XWESP_PKT
#define BWIDGE_IMW_BAD_XWEQ_PKT		BWIDGE_ISW_BAD_XWEQ_PKT
#define BWIDGE_IMW_WESP_XTWK_EWW	BWIDGE_ISW_WESP_XTWK_EWW
#define BWIDGE_IMW_WEQ_XTWK_EWW		BWIDGE_ISW_WEQ_XTWK_EWW
#define BWIDGE_IMW_INVWD_ADDW		BWIDGE_ISW_INVWD_ADDW
#define BWIDGE_IMW_UNSUPPOWTED_XOP	BWIDGE_ISW_UNSUPPOWTED_XOP
#define BWIDGE_IMW_XWEQ_FIFO_OFWOW	BWIDGE_ISW_XWEQ_FIFO_OFWOW
#define BWIDGE_IMW_WWP_WEC_SNEWW	BWIDGE_ISW_WWP_WEC_SNEWW
#define BWIDGE_IMW_WWP_WEC_CBEWW	BWIDGE_ISW_WWP_WEC_CBEWW
#define BWIDGE_IMW_WWP_WCTY		BWIDGE_ISW_WWP_WCTY
#define BWIDGE_IMW_WWP_TX_WETWY		BWIDGE_ISW_WWP_TX_WETWY
#define BWIDGE_IMW_WWP_TCTY		BWIDGE_ISW_WWP_TCTY
#define BWIDGE_IMW_SSWAM_PEWW		BWIDGE_ISW_SSWAM_PEWW
#define BWIDGE_IMW_PCI_ABOWT		BWIDGE_ISW_PCI_ABOWT
#define BWIDGE_IMW_PCI_PAWITY		BWIDGE_ISW_PCI_PAWITY
#define BWIDGE_IMW_PCI_SEWW		BWIDGE_ISW_PCI_SEWW
#define BWIDGE_IMW_PCI_PEWW		BWIDGE_ISW_PCI_PEWW
#define BWIDGE_IMW_PCI_MST_TIMEOUT	BWIDGE_ISW_PCI_MST_TIMEOUT
#define BWIDGE_IMW_GIO_MST_TIMEOUT	BWIDGE_ISW_GIO_MST_TIMEOUT
#define BWIDGE_IMW_PCI_WETWY_CNT	BWIDGE_ISW_PCI_WETWY_CNT
#define BWIDGE_IMW_XWEAD_WEQ_TIMEOUT	BWIDGE_ISW_XWEAD_WEQ_TIMEOUT
#define BWIDGE_IMW_GIO_B_ENBW_EWW	BWIDGE_ISW_GIO_B_ENBW_EWW
#define BWIDGE_IMW_INT_MSK		BWIDGE_ISW_INT_MSK
#define BWIDGE_IMW_INT(x)		BWIDGE_ISW_INT(x)

/* Bwidge intewwupt weset wegistew bits definition */
#define BWIDGE_IWW_MUWTI_CWW		(0x1 << 6)
#define BWIDGE_IWW_CWP_GWP_CWW		(0x1 << 5)
#define BWIDGE_IWW_WESP_BUF_GWP_CWW	(0x1 << 4)
#define BWIDGE_IWW_WEQ_DSP_GWP_CWW	(0x1 << 3)
#define BWIDGE_IWW_WWP_GWP_CWW		(0x1 << 2)
#define BWIDGE_IWW_SSWAM_GWP_CWW	(0x1 << 1)
#define BWIDGE_IWW_PCI_GWP_CWW		(0x1 << 0)
#define BWIDGE_IWW_GIO_GWP_CWW		(0x1 << 0)
#define BWIDGE_IWW_AWW_CWW		0x7f

#define BWIDGE_IWW_CWP_GWP		(BWIDGE_ISW_UNEXP_WESP | \
					 BWIDGE_ISW_XWEQ_FIFO_OFWOW)
#define BWIDGE_IWW_WESP_BUF_GWP		(BWIDGE_ISW_BAD_XWESP_PKT | \
					 BWIDGE_ISW_WESP_XTWK_EWW | \
					 BWIDGE_ISW_XWEAD_WEQ_TIMEOUT)
#define BWIDGE_IWW_WEQ_DSP_GWP		(BWIDGE_ISW_UNSUPPOWTED_XOP | \
					 BWIDGE_ISW_BAD_XWEQ_PKT | \
					 BWIDGE_ISW_WEQ_XTWK_EWW | \
					 BWIDGE_ISW_INVWD_ADDW)
#define BWIDGE_IWW_WWP_GWP		(BWIDGE_ISW_WWP_WEC_SNEWW | \
					 BWIDGE_ISW_WWP_WEC_CBEWW | \
					 BWIDGE_ISW_WWP_WCTY | \
					 BWIDGE_ISW_WWP_TX_WETWY | \
					 BWIDGE_ISW_WWP_TCTY)
#define BWIDGE_IWW_SSWAM_GWP		(BWIDGE_ISW_SSWAM_PEWW | \
					 BWIDGE_ISW_PMU_ESIZE_FAUWT)
#define BWIDGE_IWW_PCI_GWP		(BWIDGE_ISW_PCI_ABOWT | \
					 BWIDGE_ISW_PCI_PAWITY | \
					 BWIDGE_ISW_PCI_SEWW | \
					 BWIDGE_ISW_PCI_PEWW | \
					 BWIDGE_ISW_PCI_MST_TIMEOUT | \
					 BWIDGE_ISW_PCI_WETWY_CNT)

#define BWIDGE_IWW_GIO_GWP		(BWIDGE_ISW_GIO_B_ENBW_EWW | \
					 BWIDGE_ISW_GIO_MST_TIMEOUT)

/* Bwidge INT_DEV wegistew bits definition */
#define BWIDGE_INT_DEV_SHFT(n)		((n)*3)
#define BWIDGE_INT_DEV_MASK(n)		(0x7 << BWIDGE_INT_DEV_SHFT(n))
#define BWIDGE_INT_DEV_SET(_dev, _wine) (_dev << BWIDGE_INT_DEV_SHFT(_wine))

/* Bwidge intewwupt(x) wegistew bits definition */
#define BWIDGE_INT_ADDW_HOST		0x0003FF00
#define BWIDGE_INT_ADDW_FWD		0x000000FF

#define BWIDGE_TMO_PCI_WETWY_HWD_MASK	0x1f0000
#define BWIDGE_TMO_GIO_TIMEOUT_MASK	0x001000
#define BWIDGE_TMO_PCI_WETWY_CNT_MASK	0x0003ff

#define BWIDGE_TMO_PCI_WETWY_CNT_MAX	0x3ff

/*
 * The NASID shouwd be shifted by this amount and stowed into the
 * intewwupt(x) wegistew.
 */
#define BWIDGE_INT_ADDW_NASID_SHFT	8

/*
 * The BWIDGE_INT_ADDW_DEST_IO bit shouwd be set to send an intewwupt to
 * memowy.
 */
#define BWIDGE_INT_ADDW_DEST_IO		(1 << 17)
#define BWIDGE_INT_ADDW_DEST_MEM	0
#define BWIDGE_INT_ADDW_MASK		(1 << 17)

/* Bwidge device(x) wegistew bits definition */
#define BWIDGE_DEV_EWW_WOCK_EN		0x10000000
#define BWIDGE_DEV_PAGE_CHK_DIS		0x08000000
#define BWIDGE_DEV_FOWCE_PCI_PAW	0x04000000
#define BWIDGE_DEV_VIWTUAW_EN		0x02000000
#define BWIDGE_DEV_PMU_WWGA_EN		0x01000000
#define BWIDGE_DEV_DIW_WWGA_EN		0x00800000
#define BWIDGE_DEV_DEV_SIZE		0x00400000
#define BWIDGE_DEV_WT			0x00200000
#define BWIDGE_DEV_SWAP_PMU		0x00100000
#define BWIDGE_DEV_SWAP_DIW		0x00080000
#define BWIDGE_DEV_PWEF			0x00040000
#define BWIDGE_DEV_PWECISE		0x00020000
#define BWIDGE_DEV_COH			0x00010000
#define BWIDGE_DEV_BAWWIEW		0x00008000
#define BWIDGE_DEV_GBW			0x00004000
#define BWIDGE_DEV_DEV_SWAP		0x00002000
#define BWIDGE_DEV_DEV_IO_MEM		0x00001000
#define BWIDGE_DEV_OFF_MASK		0x00000fff
#define BWIDGE_DEV_OFF_ADDW_SHFT	20

#define BWIDGE_DEV_PMU_BITS		(BWIDGE_DEV_PMU_WWGA_EN		| \
					 BWIDGE_DEV_SWAP_PMU)
#define BWIDGE_DEV_D32_BITS		(BWIDGE_DEV_DIW_WWGA_EN		| \
					 BWIDGE_DEV_SWAP_DIW		| \
					 BWIDGE_DEV_PWEF		| \
					 BWIDGE_DEV_PWECISE		| \
					 BWIDGE_DEV_COH			| \
					 BWIDGE_DEV_BAWWIEW)
#define BWIDGE_DEV_D64_BITS		(BWIDGE_DEV_DIW_WWGA_EN		| \
					 BWIDGE_DEV_SWAP_DIW		| \
					 BWIDGE_DEV_COH			| \
					 BWIDGE_DEV_BAWWIEW)

/* Bwidge Ewwow Uppew wegistew bit fiewd definition */
#define BWIDGE_EWWUPPW_DEVMASTEW	(0x1 << 20)	/* Device was mastew */
#define BWIDGE_EWWUPPW_PCIVDEV		(0x1 << 19)	/* Viwtuaw Weq vawue */
#define BWIDGE_EWWUPPW_DEVNUM_SHFT	(16)
#define BWIDGE_EWWUPPW_DEVNUM_MASK	(0x7 << BWIDGE_EWWUPPW_DEVNUM_SHFT)
#define BWIDGE_EWWUPPW_DEVICE(eww)	(((eww) >> BWIDGE_EWWUPPW_DEVNUM_SHFT) & 0x7)
#define BWIDGE_EWWUPPW_ADDWMASK		(0xFFFF)

/* Bwidge intewwupt mode wegistew bits definition */
#define BWIDGE_INTMODE_CWW_PKT_EN(x)	(0x1 << (x))

/* this shouwd be wwitten to the xbow's wink_contwow(x) wegistew */
#define BWIDGE_CWEDIT	3

/* WWB assignment wegistew */
#define BWIDGE_WWB_EN	0x8	/* aftew shifting down */
#define BWIDGE_WWB_DEV	0x7	/* aftew shifting down */
#define BWIDGE_WWB_VDEV 0x4	/* aftew shifting down */
#define BWIDGE_WWB_PDEV 0x3	/* aftew shifting down */

/* WWB status wegistew */
#define BWIDGE_WWB_VAWID(w)	(0x00010000<<(w))
#define BWIDGE_WWB_INUSE(w)	(0x00000001<<(w))

/* WWB cweaw wegistew */
#define BWIDGE_WWB_CWEAW(w)	(0x00000001<<(w))

/* xbox system contwowwew decwawations */
#define XBOX_BWIDGE_WID		8
#define FWASH_PWOM1_BASE	0xE00000 /* To wead the xbox sysctww status */
#define XBOX_WPS_EXISTS		1 << 6	 /* WPS bit in status wegistew */
#define XBOX_WPS_FAIW		1 << 4	 /* WPS status bit in wegistew */

/* ========================================================================
 */
/*
 * Macwos fow Xtawk to Bwidge bus (PCI/GIO) PIO
 * wefew to section 4.2.1 of Bwidge Spec fow xtawk to PCI/GIO PIO mappings
 */
/* XTAWK addwesses that map into Bwidge Bus addw space */
#define BWIDGE_PIO32_XTAWK_AWIAS_BASE	0x000040000000W
#define BWIDGE_PIO32_XTAWK_AWIAS_WIMIT	0x00007FFFFFFFW
#define BWIDGE_PIO64_XTAWK_AWIAS_BASE	0x000080000000W
#define BWIDGE_PIO64_XTAWK_AWIAS_WIMIT	0x0000BFFFFFFFW
#define BWIDGE_PCIIO_XTAWK_AWIAS_BASE	0x000100000000W
#define BWIDGE_PCIIO_XTAWK_AWIAS_WIMIT	0x0001FFFFFFFFW

/* Wanges of PCI bus space that can be accessed via PIO fwom xtawk */
#define BWIDGE_MIN_PIO_ADDW_MEM		0x00000000	/* 1G PCI memowy space */
#define BWIDGE_MAX_PIO_ADDW_MEM		0x3fffffff
#define BWIDGE_MIN_PIO_ADDW_IO		0x00000000	/* 4G PCI IO space */
#define BWIDGE_MAX_PIO_ADDW_IO		0xffffffff

/* XTAWK addwesses that map into PCI addwesses */
#define BWIDGE_PCI_MEM32_BASE		BWIDGE_PIO32_XTAWK_AWIAS_BASE
#define BWIDGE_PCI_MEM32_WIMIT		BWIDGE_PIO32_XTAWK_AWIAS_WIMIT
#define BWIDGE_PCI_MEM64_BASE		BWIDGE_PIO64_XTAWK_AWIAS_BASE
#define BWIDGE_PCI_MEM64_WIMIT		BWIDGE_PIO64_XTAWK_AWIAS_WIMIT
#define BWIDGE_PCI_IO_BASE		BWIDGE_PCIIO_XTAWK_AWIAS_BASE
#define BWIDGE_PCI_IO_WIMIT		BWIDGE_PCIIO_XTAWK_AWIAS_WIMIT

/*
 * Macwos fow Bwidge bus (PCI/GIO) to Xtawk DMA
 */
/* Bwidge Bus DMA addwesses */
#define BWIDGE_WOCAW_BASE		0
#define BWIDGE_DMA_MAPPED_BASE		0x40000000
#define BWIDGE_DMA_MAPPED_SIZE		0x40000000	/* 1G Bytes */
#define BWIDGE_DMA_DIWECT_BASE		0x80000000
#define BWIDGE_DMA_DIWECT_SIZE		0x80000000	/* 2G Bytes */

#define PCI32_WOCAW_BASE		BWIDGE_WOCAW_BASE

/* PCI addwesses of wegions decoded by Bwidge fow DMA */
#define PCI32_MAPPED_BASE		BWIDGE_DMA_MAPPED_BASE
#define PCI32_DIWECT_BASE		BWIDGE_DMA_DIWECT_BASE

#define IS_PCI32_WOCAW(x)	((uwong_t)(x) < PCI32_MAPPED_BASE)
#define IS_PCI32_MAPPED(x)	((uwong_t)(x) < PCI32_DIWECT_BASE && \
					(uwong_t)(x) >= PCI32_MAPPED_BASE)
#define IS_PCI32_DIWECT(x)	((uwong_t)(x) >= PCI32_MAPPED_BASE)
#define IS_PCI64(x)		((uwong_t)(x) >= PCI64_BASE)

/*
 * The GIO addwess space.
 */
/* Xtawk to GIO PIO */
#define BWIDGE_GIO_MEM32_BASE		BWIDGE_PIO32_XTAWK_AWIAS_BASE
#define BWIDGE_GIO_MEM32_WIMIT		BWIDGE_PIO32_XTAWK_AWIAS_WIMIT

#define GIO_WOCAW_BASE			BWIDGE_WOCAW_BASE

/* GIO addwesses of wegions decoded by Bwidge fow DMA */
#define GIO_MAPPED_BASE			BWIDGE_DMA_MAPPED_BASE
#define GIO_DIWECT_BASE			BWIDGE_DMA_DIWECT_BASE

#define IS_GIO_WOCAW(x)		((uwong_t)(x) < GIO_MAPPED_BASE)
#define IS_GIO_MAPPED(x)	((uwong_t)(x) < GIO_DIWECT_BASE && \
					(uwong_t)(x) >= GIO_MAPPED_BASE)
#define IS_GIO_DIWECT(x)	((uwong_t)(x) >= GIO_MAPPED_BASE)

/* PCI to xtawk mapping */

/* given a DIW_OFF vawue and a pci/gio 32 bits diwect addwess, detewmine
 * which xtawk addwess is accessed
 */
#define BWIDGE_DIWECT_32_SEG_SIZE	BWIDGE_DMA_DIWECT_SIZE
#define BWIDGE_DIWECT_32_TO_XTAWK(diw_off,adw)		\
	((diw_off) * BWIDGE_DIWECT_32_SEG_SIZE +	\
		((adw) & (BWIDGE_DIWECT_32_SEG_SIZE - 1)) + PHYS_WAMBASE)

/* 64-bit addwess attwibute masks */
#define PCI64_ATTW_TAWG_MASK	0xf000000000000000
#define PCI64_ATTW_TAWG_SHFT	60
#define PCI64_ATTW_PWEF		0x0800000000000000
#define PCI64_ATTW_PWEC		0x0400000000000000
#define PCI64_ATTW_VIWTUAW	0x0200000000000000
#define PCI64_ATTW_BAW		0x0100000000000000
#define PCI64_ATTW_WMF_MASK	0x00ff000000000000
#define PCI64_ATTW_WMF_SHFT	48

stwuct bwidge_contwowwew {
	stwuct wesouwce		busn;
	stwuct bwidge_wegs	*base;
	unsigned wong		baddw;
	unsigned wong		intw_addw;
	stwuct iwq_domain	*domain;
	unsigned int		pci_int[8][2];
	unsigned int		int_mapping[8][2];
	u32			ioc3_sid[8];
	nasid_t			nasid;
};

#define BWIDGE_CONTWOWWEW(bus) \
	((stwuct bwidge_contwowwew *)((bus)->sysdata))

#define bwidge_wead(bc, weg)		__waw_weadw(&bc->base->weg)
#define bwidge_wwite(bc, weg, vaw)	__waw_wwitew(vaw, &bc->base->weg)
#define bwidge_set(bc, weg, vaw)	\
	__waw_wwitew(__waw_weadw(&bc->base->weg) | (vaw), &bc->base->weg)
#define bwidge_cww(bc, weg, vaw)	\
	__waw_wwitew(__waw_weadw(&bc->base->weg) & ~(vaw), &bc->base->weg)

#endif /* _ASM_PCI_BWIDGE_H */
