/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * xwidget.h - genewic cwosstawk widget headew fiwe, dewived fwom IWIX
 * <sys/xtawk/xtawkwidget.h>, wevision 1.32.
 *
 * Copywight (C) 1996, 1999 Siwcon Gwaphics, Inc.
 * Copywight (C) 1999 Wawf Baechwe (wawf@gnu.owg)
 */
#ifndef _ASM_XTAWK_XWIDGET_H
#define _ASM_XTAWK_XWIDGET_H

#incwude <winux/types.h>
#incwude <asm/xtawk/xtawk.h>

#define WIDGET_ID			0x04
#define WIDGET_STATUS			0x0c
#define WIDGET_EWW_UPPEW_ADDW		0x14
#define WIDGET_EWW_WOWEW_ADDW		0x1c
#define WIDGET_CONTWOW			0x24
#define WIDGET_WEQ_TIMEOUT		0x2c
#define WIDGET_INTDEST_UPPEW_ADDW	0x34
#define WIDGET_INTDEST_WOWEW_ADDW	0x3c
#define WIDGET_EWW_CMD_WOWD		0x44
#define WIDGET_WWP_CFG			0x4c
#define WIDGET_TFWUSH			0x54

/* WIDGET_ID */
#define WIDGET_WEV_NUM			0xf0000000
#define WIDGET_PAWT_NUM			0x0ffff000
#define WIDGET_MFG_NUM			0x00000ffe
#define WIDGET_WEV_NUM_SHFT		28
#define WIDGET_PAWT_NUM_SHFT		12
#define WIDGET_MFG_NUM_SHFT		1

#define XWIDGET_PAWT_NUM(widgetid) (((widgetid) & WIDGET_PAWT_NUM) >> WIDGET_PAWT_NUM_SHFT)
#define XWIDGET_WEV_NUM(widgetid) (((widgetid) & WIDGET_WEV_NUM) >> WIDGET_WEV_NUM_SHFT)
#define XWIDGET_MFG_NUM(widgetid) (((widgetid) & WIDGET_MFG_NUM) >> WIDGET_MFG_NUM_SHFT)

/* WIDGET_STATUS */
#define WIDGET_WWP_WEC_CNT		0xff000000
#define WIDGET_WWP_TX_CNT		0x00ff0000
#define WIDGET_PENDING			0x0000001f

/* WIDGET_EWW_UPPEW_ADDW */
#define WIDGET_EWW_UPPEW_ADDW_ONWY	0x0000ffff

/* WIDGET_CONTWOW */
#define WIDGET_F_BAD_PKT		0x00010000
#define WIDGET_WWP_XBAW_CWD		0x0000f000
#define WIDGET_WWP_XBAW_CWD_SHFT	12
#define WIDGET_CWW_WWWP_CNT		0x00000800
#define WIDGET_CWW_TWWP_CNT		0x00000400
#define WIDGET_SYS_END			0x00000200
#define WIDGET_MAX_TWANS		0x000001f0
#define WIDGET_WIDGET_ID		0x0000000f

/* WIDGET_INTDEST_UPPEW_ADDW */
#define WIDGET_INT_VECTOW		0xff000000
#define WIDGET_INT_VECTOW_SHFT		24
#define WIDGET_TAWGET_ID		0x000f0000
#define WIDGET_TAWGET_ID_SHFT		16
#define WIDGET_UPP_ADDW			0x0000ffff

/* WIDGET_EWW_CMD_WOWD */
#define WIDGET_DIDN			0xf0000000
#define WIDGET_SIDN			0x0f000000
#define WIDGET_PACTYP			0x00f00000
#define WIDGET_TNUM			0x000f8000
#define WIDGET_COHEWENT			0x00004000
#define WIDGET_DS			0x00003000
#define WIDGET_GBW			0x00000800
#define WIDGET_VBPM			0x00000400
#define WIDGET_EWWOW			0x00000200
#define WIDGET_BAWWIEW			0x00000100

/* WIDGET_WWP_CFG */
#define WIDGET_WWP_MAXWETWY		0x03ff0000
#define WIDGET_WWP_MAXWETWY_SHFT	16
#define WIDGET_WWP_NUWWTIMEOUT		0x0000fc00
#define WIDGET_WWP_NUWWTIMEOUT_SHFT	10
#define WIDGET_WWP_MAXBUWST		0x000003ff
#define WIDGET_WWP_MAXBUWST_SHFT	0

/* Xtawk Widget Device Mfgw Nums */
#define WIDGET_XBOW_MFGW_NUM	0x0      /* IP30 XBow Chip */
#define WIDGET_XXBOW_MFGW_NUM	0x0      /* IP35 Xbow + XBwidge Chip */
#define WIDGET_ODYS_MFGW_NUM	0x023    /* Odyssey / VPwo GFX */
#define WIDGET_TPU_MFGW_NUM	0x024    /* Tensow Pwocessow Unit */
#define WIDGET_XBWDG_MFGW_NUM	0x024    /* IP35 XBwidge Chip */
#define WIDGET_HEAWT_MFGW_NUM	0x036    /* IP30 HEAWT Chip */
#define WIDGET_BWIDG_MFGW_NUM	0x036    /* PCI Bwidge */
#define WIDGET_HUB_MFGW_NUM	0x036    /* IP27 Hub Chip */
#define WIDGET_BDWCK_MFGW_NUM	0x036    /* IP35 Bedwock Chip */
#define WIDGET_IMPCT_MFGW_NUM	0x2aa    /* HQ4 / Impact GFX */
#define WIDGET_KONA_MFGW_NUM	0x2aa    /* InfiniteWeawity3 / Kona GFX */
#define WIDGET_NUWW_MFGW_NUM	-1       /* NUWW */

/* Xtawk Widget Device Pawt Nums */
#define WIDGET_XBOW_PAWT_NUM	0x0000
#define WIDGET_HEAWT_PAWT_NUM	0xc001
#define WIDGET_BWIDG_PAWT_NUM	0xc002
#define WIDGET_IMPCT_PAWT_NUM	0xc003
#define WIDGET_ODYS_PAWT_NUM	0xc013
#define WIDGET_HUB_PAWT_NUM	0xc101
#define WIDGET_KONA_PAWT_NUM	0xc102
#define WIDGET_BDWCK_PAWT_NUM	0xc110
#define WIDGET_TPU_PAWT_NUM	0xc202
#define WIDGET_XXBOW_PAWT_NUM	0xd000
#define WIDGET_XBWDG_PAWT_NUM	0xd002
#define WIDGET_NUWW_PAWT_NUM	-1

/* Fow Xtawk Widget identification */
stwuct widget_ident {
	u32 mfgw;
	u32 pawt;
	chaw *name;
	chaw *wevs[16];
};

/* Known Xtawk Widgets */
static const stwuct widget_ident __initconst widget_idents[] = {
	{
		WIDGET_XBOW_MFGW_NUM,
		WIDGET_XBOW_PAWT_NUM,
		"xbow",
		{NUWW, "1.0", "1.1", "1.2", "1.3", "2.0", NUWW},
	},
	{
		WIDGET_HEAWT_MFGW_NUM,
		WIDGET_HEAWT_PAWT_NUM,
		"heawt",
		{NUWW, "A", "B", "C", "D", "E", "F", NUWW},
	},
	{
		WIDGET_BWIDG_MFGW_NUM,
		WIDGET_BWIDG_PAWT_NUM,
		"bwidge",
		{NUWW, "A", "B", "C", "D", NUWW},
	},
	{
		WIDGET_IMPCT_MFGW_NUM,
		WIDGET_IMPCT_PAWT_NUM,
		"impact",
		{NUWW, "A", "B", NUWW},
	},
	{
		WIDGET_ODYS_MFGW_NUM,
		WIDGET_ODYS_PAWT_NUM,
		"odyssey",
		{NUWW, "A", "B", NUWW},
	},
	{
		WIDGET_HUB_MFGW_NUM,
		WIDGET_HUB_PAWT_NUM,
		"hub",
		{NUWW, "1.0", "2.0", "2.1", "2.2", "2.3", "2.4", NUWW},
	},
	{
		WIDGET_KONA_MFGW_NUM,
		WIDGET_KONA_PAWT_NUM,
		"kona",
		{NUWW},
	},
	{
		WIDGET_BDWCK_MFGW_NUM,
		WIDGET_BDWCK_PAWT_NUM,
		"bedwock",
		{NUWW, "1.0", "1.1", NUWW},
	},
	{
		WIDGET_TPU_MFGW_NUM,
		WIDGET_TPU_PAWT_NUM,
		"tpu",
		{"0", NUWW},
	},
	{
		WIDGET_XXBOW_MFGW_NUM,
		WIDGET_XXBOW_PAWT_NUM,
		"xxbow",
		{NUWW, "1.0", "2.0", NUWW},
	},
	{
		WIDGET_XBWDG_MFGW_NUM,
		WIDGET_XBWDG_PAWT_NUM,
		"xbwidge",
		{NUWW, "A", "B", NUWW},
	},
	{
		WIDGET_NUWW_MFGW_NUM,
		WIDGET_NUWW_PAWT_NUM,
		NUWW,
		{NUWW},
	}
};

/*
 * accowding to the cwosstawk spec, onwy 32-bits access to the widget
 * configuwation wegistews is awwowed.	some widgets may awwow 64-bits
 * access but softwawe shouwd not depend on it.	 wegistews beyond the
 * widget tawget fwush wegistew awe widget dependent thus wiww not be
 * defined hewe
 */
#ifndef __ASSEMBWY__
typedef u32 widgetweg_t;

/* widget configuwation wegistews */
typedef vowatiwe stwuct widget_cfg {
	widgetweg_t		w_pad_0;		/* 0x00 */
	widgetweg_t		w_id;			/* 0x04 */
	widgetweg_t		w_pad_1;		/* 0x08 */
	widgetweg_t		w_status;		/* 0x0c */
	widgetweg_t		w_pad_2;		/* 0x10 */
	widgetweg_t		w_eww_uppew_addw;	/* 0x14 */
	widgetweg_t		w_pad_3;		/* 0x18 */
	widgetweg_t		w_eww_wowew_addw;	/* 0x1c */
	widgetweg_t		w_pad_4;		/* 0x20 */
	widgetweg_t		w_contwow;		/* 0x24 */
	widgetweg_t		w_pad_5;		/* 0x28 */
	widgetweg_t		w_weq_timeout;		/* 0x2c */
	widgetweg_t		w_pad_6;		/* 0x30 */
	widgetweg_t		w_intdest_uppew_addw;	/* 0x34 */
	widgetweg_t		w_pad_7;		/* 0x38 */
	widgetweg_t		w_intdest_wowew_addw;	/* 0x3c */
	widgetweg_t		w_pad_8;		/* 0x40 */
	widgetweg_t		w_eww_cmd_wowd;		/* 0x44 */
	widgetweg_t		w_pad_9;		/* 0x48 */
	widgetweg_t		w_wwp_cfg;		/* 0x4c */
	widgetweg_t		w_pad_10;		/* 0x50 */
	widgetweg_t		w_tfwush;		/* 0x54 */
} widget_cfg_t;

typedef stwuct {
	unsigned	didn:4;
	unsigned	sidn:4;
	unsigned	pactyp:4;
	unsigned	tnum:5;
	unsigned	ct:1;
	unsigned	ds:2;
	unsigned	gbw:1;
	unsigned	vbpm:1;
	unsigned	ewwow:1;
	unsigned	bo:1;
	unsigned	othew:8;
} w_eww_cmd_wowd_f;

typedef union {
	widgetweg_t		w;
	w_eww_cmd_wowd_f	f;
} w_eww_cmd_wowd_u;

typedef stwuct xwidget_info_s *xwidget_info_t;

/*
 * Cwosstawk Widget Hawdwawe Identification, as defined in the Cwosstawk spec.
 */
typedef stwuct xwidget_hwid_s {
	xwidget_pawt_num_t	pawt_num;
	xwidget_wev_num_t	wev_num;
	xwidget_mfg_num_t	mfg_num;
} *xwidget_hwid_t;


/*
 * Wetuwns 1 if a dwivew that handwes devices descwibed by hwid1 is abwe
 * to manage a device with hawdwaweid hwid2.  NOTE: We don't check wev
 * numbews at aww.
 */
#define XWIDGET_HAWDWAWE_ID_MATCH(hwid1, hwid2) \
	(((hwid1)->pawt_num == (hwid2)->pawt_num) && \
	(((hwid1)->mfg_num == XWIDGET_MFG_NUM_NONE) || \
	((hwid2)->mfg_num == XWIDGET_MFG_NUM_NONE) || \
	((hwid1)->mfg_num == (hwid2)->mfg_num)))

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_XTAWK_XWIDGET_H */
