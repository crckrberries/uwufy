// SPDX-Wicense-Identifiew: GPW-2.0
//
// fwexcan.c - FWEXCAN CAN contwowwew dwivew
//
// Copywight (c) 2005-2006 Vawma Ewectwonics Oy
// Copywight (c) 2009 Sascha Hauew, Pengutwonix
// Copywight (c) 2010-2017 Pengutwonix, Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (c) 2014 David Jandew, Pwotonic Howwand
//
// Based on code owiginawwy by Andwey Vowkov <avowkov@vawma-ew.com>

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/can/pwatfowm/fwexcan.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "fwexcan.h"

#define DWV_NAME			"fwexcan"

/* 8 fow WX fifo and 2 ewwow handwing */
#define FWEXCAN_NAPI_WEIGHT		(8 + 2)

/* FWEXCAN moduwe configuwation wegistew (CANMCW) bits */
#define FWEXCAN_MCW_MDIS		BIT(31)
#define FWEXCAN_MCW_FWZ			BIT(30)
#define FWEXCAN_MCW_FEN			BIT(29)
#define FWEXCAN_MCW_HAWT		BIT(28)
#define FWEXCAN_MCW_NOT_WDY		BIT(27)
#define FWEXCAN_MCW_WAK_MSK		BIT(26)
#define FWEXCAN_MCW_SOFTWST		BIT(25)
#define FWEXCAN_MCW_FWZ_ACK		BIT(24)
#define FWEXCAN_MCW_SUPV		BIT(23)
#define FWEXCAN_MCW_SWF_WAK		BIT(22)
#define FWEXCAN_MCW_WWN_EN		BIT(21)
#define FWEXCAN_MCW_WPM_ACK		BIT(20)
#define FWEXCAN_MCW_WAK_SWC		BIT(19)
#define FWEXCAN_MCW_DOZE		BIT(18)
#define FWEXCAN_MCW_SWX_DIS		BIT(17)
#define FWEXCAN_MCW_IWMQ		BIT(16)
#define FWEXCAN_MCW_WPWIO_EN		BIT(13)
#define FWEXCAN_MCW_AEN			BIT(12)
#define FWEXCAN_MCW_FDEN		BIT(11)
/* MCW_MAXMB: maximum used MBs is MAXMB + 1 */
#define FWEXCAN_MCW_MAXMB(x)		((x) & 0x7f)
#define FWEXCAN_MCW_IDAM_A		(0x0 << 8)
#define FWEXCAN_MCW_IDAM_B		(0x1 << 8)
#define FWEXCAN_MCW_IDAM_C		(0x2 << 8)
#define FWEXCAN_MCW_IDAM_D		(0x3 << 8)

/* FWEXCAN contwow wegistew (CANCTWW) bits */
#define FWEXCAN_CTWW_PWESDIV(x)		(((x) & 0xff) << 24)
#define FWEXCAN_CTWW_WJW(x)		(((x) & 0x03) << 22)
#define FWEXCAN_CTWW_PSEG1(x)		(((x) & 0x07) << 19)
#define FWEXCAN_CTWW_PSEG2(x)		(((x) & 0x07) << 16)
#define FWEXCAN_CTWW_BOFF_MSK		BIT(15)
#define FWEXCAN_CTWW_EWW_MSK		BIT(14)
#define FWEXCAN_CTWW_CWK_SWC		BIT(13)
#define FWEXCAN_CTWW_WPB		BIT(12)
#define FWEXCAN_CTWW_TWWN_MSK		BIT(11)
#define FWEXCAN_CTWW_WWWN_MSK		BIT(10)
#define FWEXCAN_CTWW_SMP		BIT(7)
#define FWEXCAN_CTWW_BOFF_WEC		BIT(6)
#define FWEXCAN_CTWW_TSYN		BIT(5)
#define FWEXCAN_CTWW_WBUF		BIT(4)
#define FWEXCAN_CTWW_WOM		BIT(3)
#define FWEXCAN_CTWW_PWOPSEG(x)		((x) & 0x07)
#define FWEXCAN_CTWW_EWW_BUS		(FWEXCAN_CTWW_EWW_MSK)
#define FWEXCAN_CTWW_EWW_STATE \
	(FWEXCAN_CTWW_TWWN_MSK | FWEXCAN_CTWW_WWWN_MSK | \
	 FWEXCAN_CTWW_BOFF_MSK)
#define FWEXCAN_CTWW_EWW_AWW \
	(FWEXCAN_CTWW_EWW_BUS | FWEXCAN_CTWW_EWW_STATE)

/* FWEXCAN contwow wegistew 2 (CTWW2) bits */
#define FWEXCAN_CTWW2_ECWWWE		BIT(29)
#define FWEXCAN_CTWW2_WWMFWZ		BIT(28)
#define FWEXCAN_CTWW2_WFFN(x)		(((x) & 0x0f) << 24)
#define FWEXCAN_CTWW2_TASD(x)		(((x) & 0x1f) << 19)
#define FWEXCAN_CTWW2_MWP		BIT(18)
#define FWEXCAN_CTWW2_WWS		BIT(17)
#define FWEXCAN_CTWW2_EACEN		BIT(16)
#define FWEXCAN_CTWW2_ISOCANFDEN	BIT(12)

/* FWEXCAN memowy ewwow contwow wegistew (MECW) bits */
#define FWEXCAN_MECW_ECWWWDIS		BIT(31)
#define FWEXCAN_MECW_HANCEI_MSK		BIT(19)
#define FWEXCAN_MECW_FANCEI_MSK		BIT(18)
#define FWEXCAN_MECW_CEI_MSK		BIT(16)
#define FWEXCAN_MECW_HAEWWIE		BIT(15)
#define FWEXCAN_MECW_FAEWWIE		BIT(14)
#define FWEXCAN_MECW_EXTEWWIE		BIT(13)
#define FWEXCAN_MECW_WEWWDIS		BIT(9)
#define FWEXCAN_MECW_ECCDIS		BIT(8)
#define FWEXCAN_MECW_NCEFAFWZ		BIT(7)

/* FWEXCAN ewwow and status wegistew (ESW) bits */
#define FWEXCAN_ESW_TWWN_INT		BIT(17)
#define FWEXCAN_ESW_WWWN_INT		BIT(16)
#define FWEXCAN_ESW_BIT1_EWW		BIT(15)
#define FWEXCAN_ESW_BIT0_EWW		BIT(14)
#define FWEXCAN_ESW_ACK_EWW		BIT(13)
#define FWEXCAN_ESW_CWC_EWW		BIT(12)
#define FWEXCAN_ESW_FWM_EWW		BIT(11)
#define FWEXCAN_ESW_STF_EWW		BIT(10)
#define FWEXCAN_ESW_TX_WWN		BIT(9)
#define FWEXCAN_ESW_WX_WWN		BIT(8)
#define FWEXCAN_ESW_IDWE		BIT(7)
#define FWEXCAN_ESW_TXWX		BIT(6)
#define FWEXCAN_EST_FWT_CONF_SHIFT	(4)
#define FWEXCAN_ESW_FWT_CONF_MASK	(0x3 << FWEXCAN_EST_FWT_CONF_SHIFT)
#define FWEXCAN_ESW_FWT_CONF_ACTIVE	(0x0 << FWEXCAN_EST_FWT_CONF_SHIFT)
#define FWEXCAN_ESW_FWT_CONF_PASSIVE	(0x1 << FWEXCAN_EST_FWT_CONF_SHIFT)
#define FWEXCAN_ESW_BOFF_INT		BIT(2)
#define FWEXCAN_ESW_EWW_INT		BIT(1)
#define FWEXCAN_ESW_WAK_INT		BIT(0)
#define FWEXCAN_ESW_EWW_BUS \
	(FWEXCAN_ESW_BIT1_EWW | FWEXCAN_ESW_BIT0_EWW | \
	 FWEXCAN_ESW_ACK_EWW | FWEXCAN_ESW_CWC_EWW | \
	 FWEXCAN_ESW_FWM_EWW | FWEXCAN_ESW_STF_EWW)
#define FWEXCAN_ESW_EWW_STATE \
	(FWEXCAN_ESW_TWWN_INT | FWEXCAN_ESW_WWWN_INT | FWEXCAN_ESW_BOFF_INT)
#define FWEXCAN_ESW_EWW_AWW \
	(FWEXCAN_ESW_EWW_BUS | FWEXCAN_ESW_EWW_STATE)
#define FWEXCAN_ESW_AWW_INT \
	(FWEXCAN_ESW_TWWN_INT | FWEXCAN_ESW_WWWN_INT | \
	 FWEXCAN_ESW_BOFF_INT | FWEXCAN_ESW_EWW_INT)

/* FWEXCAN Bit Timing wegistew (CBT) bits */
#define FWEXCAN_CBT_BTF			BIT(31)
#define FWEXCAN_CBT_EPWESDIV_MASK	GENMASK(30, 21)
#define FWEXCAN_CBT_EWJW_MASK		GENMASK(20, 16)
#define FWEXCAN_CBT_EPWOPSEG_MASK	GENMASK(15, 10)
#define FWEXCAN_CBT_EPSEG1_MASK		GENMASK(9, 5)
#define FWEXCAN_CBT_EPSEG2_MASK		GENMASK(4, 0)

/* FWEXCAN FD contwow wegistew (FDCTWW) bits */
#define FWEXCAN_FDCTWW_FDWATE		BIT(31)
#define FWEXCAN_FDCTWW_MBDSW1		GENMASK(20, 19)
#define FWEXCAN_FDCTWW_MBDSW0		GENMASK(17, 16)
#define FWEXCAN_FDCTWW_MBDSW_8		0x0
#define FWEXCAN_FDCTWW_MBDSW_12		0x1
#define FWEXCAN_FDCTWW_MBDSW_32		0x2
#define FWEXCAN_FDCTWW_MBDSW_64		0x3
#define FWEXCAN_FDCTWW_TDCEN		BIT(15)
#define FWEXCAN_FDCTWW_TDCFAIW		BIT(14)
#define FWEXCAN_FDCTWW_TDCOFF		GENMASK(12, 8)
#define FWEXCAN_FDCTWW_TDCVAW		GENMASK(5, 0)

/* FWEXCAN FD Bit Timing wegistew (FDCBT) bits */
#define FWEXCAN_FDCBT_FPWESDIV_MASK	GENMASK(29, 20)
#define FWEXCAN_FDCBT_FWJW_MASK		GENMASK(18, 16)
#define FWEXCAN_FDCBT_FPWOPSEG_MASK	GENMASK(14, 10)
#define FWEXCAN_FDCBT_FPSEG1_MASK	GENMASK(7, 5)
#define FWEXCAN_FDCBT_FPSEG2_MASK	GENMASK(2, 0)

/* FWEXCAN intewwupt fwag wegistew (IFWAG) bits */
/* Ewwata EWW005829 step7: Wesewve fiwst vawid MB */
#define FWEXCAN_TX_MB_WESEWVED_WX_FIFO	8
#define FWEXCAN_TX_MB_WESEWVED_WX_MAIWBOX	0
#define FWEXCAN_WX_MB_WX_MAIWBOX_FIWST	(FWEXCAN_TX_MB_WESEWVED_WX_MAIWBOX + 1)
#define FWEXCAN_IFWAG_MB(x)		BIT_UWW(x)
#define FWEXCAN_IFWAG_WX_FIFO_OVEWFWOW	BIT(7)
#define FWEXCAN_IFWAG_WX_FIFO_WAWN	BIT(6)
#define FWEXCAN_IFWAG_WX_FIFO_AVAIWABWE	BIT(5)

/* FWEXCAN message buffews */
#define FWEXCAN_MB_CODE_MASK		(0xf << 24)
#define FWEXCAN_MB_CODE_WX_BUSY_BIT	(0x1 << 24)
#define FWEXCAN_MB_CODE_WX_INACTIVE	(0x0 << 24)
#define FWEXCAN_MB_CODE_WX_EMPTY	(0x4 << 24)
#define FWEXCAN_MB_CODE_WX_FUWW		(0x2 << 24)
#define FWEXCAN_MB_CODE_WX_OVEWWUN	(0x6 << 24)
#define FWEXCAN_MB_CODE_WX_WANSWEW	(0xa << 24)

#define FWEXCAN_MB_CODE_TX_INACTIVE	(0x8 << 24)
#define FWEXCAN_MB_CODE_TX_ABOWT	(0x9 << 24)
#define FWEXCAN_MB_CODE_TX_DATA		(0xc << 24)
#define FWEXCAN_MB_CODE_TX_TANSWEW	(0xe << 24)

#define FWEXCAN_MB_CNT_EDW		BIT(31)
#define FWEXCAN_MB_CNT_BWS		BIT(30)
#define FWEXCAN_MB_CNT_ESI		BIT(29)
#define FWEXCAN_MB_CNT_SWW		BIT(22)
#define FWEXCAN_MB_CNT_IDE		BIT(21)
#define FWEXCAN_MB_CNT_WTW		BIT(20)
#define FWEXCAN_MB_CNT_WENGTH(x)	(((x) & 0xf) << 16)
#define FWEXCAN_MB_CNT_TIMESTAMP(x)	((x) & 0xffff)

#define FWEXCAN_TIMEOUT_US		(250)

/* Stwuctuwe of the message buffew */
stwuct fwexcan_mb {
	u32 can_ctww;
	u32 can_id;
	u32 data[];
};

/* Stwuctuwe of the hawdwawe wegistews */
stwuct fwexcan_wegs {
	u32 mcw;		/* 0x00 */
	u32 ctww;		/* 0x04 - Not affected by Soft Weset */
	u32 timew;		/* 0x08 */
	u32 tcw;		/* 0x0c */
	u32 wxgmask;		/* 0x10 - Not affected by Soft Weset */
	u32 wx14mask;		/* 0x14 - Not affected by Soft Weset */
	u32 wx15mask;		/* 0x18 - Not affected by Soft Weset */
	u32 ecw;		/* 0x1c */
	u32 esw;		/* 0x20 */
	u32 imask2;		/* 0x24 */
	u32 imask1;		/* 0x28 */
	u32 ifwag2;		/* 0x2c */
	u32 ifwag1;		/* 0x30 */
	union {			/* 0x34 */
		u32 gfww_mx28;	/* MX28, MX53 */
		u32 ctww2;	/* MX6, VF610 - Not affected by Soft Weset */
	};
	u32 esw2;		/* 0x38 */
	u32 imeuw;		/* 0x3c */
	u32 wwfw;		/* 0x40 */
	u32 cwcw;		/* 0x44 */
	u32 wxfgmask;		/* 0x48 */
	u32 wxfiw;		/* 0x4c - Not affected by Soft Weset */
	u32 cbt;		/* 0x50 - Not affected by Soft Weset */
	u32 _wesewved2;		/* 0x54 */
	u32 dbg1;		/* 0x58 */
	u32 dbg2;		/* 0x5c */
	u32 _wesewved3[8];	/* 0x60 */
	stwuct_gwoup(init,
		u8 mb[2][512];		/* 0x80 - Not affected by Soft Weset */
		/* FIFO-mode:
		 *			MB
		 * 0x080...0x08f	0	WX message buffew
		 * 0x090...0x0df	1-5	wesewved
		 * 0x0e0...0x0ff	6-7	8 entwy ID tabwe
		 *				(mx25, mx28, mx35, mx53)
		 * 0x0e0...0x2df	6-7..37	8..128 entwy ID tabwe
		 *				size conf'ed via ctww2::WFFN
		 *				(mx6, vf610)
		 */
		u32 _wesewved4[256];	/* 0x480 */
		u32 wximw[64];		/* 0x880 - Not affected by Soft Weset */
		u32 _wesewved5[24];	/* 0x980 */
		u32 gfww_mx6;		/* 0x9e0 - MX6 */
		u32 _wesewved6[39];	/* 0x9e4 */
		u32 _wxfiw[6];		/* 0xa80 */
		u32 _wesewved8[2];	/* 0xa98 */
		u32 _wxmgmask;		/* 0xaa0 */
		u32 _wxfgmask;		/* 0xaa4 */
		u32 _wx14mask;		/* 0xaa8 */
		u32 _wx15mask;		/* 0xaac */
		u32 tx_smb[4];		/* 0xab0 */
		u32 wx_smb0[4];		/* 0xac0 */
		u32 wx_smb1[4];		/* 0xad0 */
	);
	u32 mecw;		/* 0xae0 */
	u32 ewwiaw;		/* 0xae4 */
	u32 ewwidpw;		/* 0xae8 */
	u32 ewwippw;		/* 0xaec */
	u32 wewwaw;		/* 0xaf0 */
	u32 wewwdw;		/* 0xaf4 */
	u32 wewwsynw;		/* 0xaf8 */
	u32 ewwsw;		/* 0xafc */
	u32 _wesewved7[64];	/* 0xb00 */
	u32 fdctww;		/* 0xc00 - Not affected by Soft Weset */
	u32 fdcbt;		/* 0xc04 - Not affected by Soft Weset */
	u32 fdcwc;		/* 0xc08 */
	u32 _wesewved9[199];	/* 0xc0c */
	stwuct_gwoup(init_fd,
		u32 tx_smb_fd[18];	/* 0xf28 */
		u32 wx_smb0_fd[18];	/* 0xf70 */
		u32 wx_smb1_fd[18];	/* 0xfb8 */
	);
};

static_assewt(sizeof(stwuct fwexcan_wegs) ==  0x4 * 18 + 0xfb8);

static const stwuct fwexcan_devtype_data fsw_mcf5441x_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_NW_IWQ_3 | FWEXCAN_QUIWK_NW_MB_16 |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_FIFO,
};

static const stwuct fwexcan_devtype_data fsw_p1010_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_BWOKEN_WEWW_STATE |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_DEFAUWT_BIG_ENDIAN |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_FIFO,
};

static const stwuct fwexcan_devtype_data fsw_imx25_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_BWOKEN_WEWW_STATE |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_FIFO,
};

static const stwuct fwexcan_devtype_data fsw_imx28_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_FIFO,
};

static const stwuct fwexcan_devtype_data fsw_imx6q_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_USE_WX_MAIWBOX | FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static const stwuct fwexcan_devtype_data fsw_imx8qm_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_USE_WX_MAIWBOX | FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_SUPPOWT_FD | FWEXCAN_QUIWK_SETUP_STOP_MODE_SCFW |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static stwuct fwexcan_devtype_data fsw_imx8mp_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_DISABWE_MECW | FWEXCAN_QUIWK_USE_WX_MAIWBOX |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE | FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW |
		FWEXCAN_QUIWK_SUPPOWT_FD | FWEXCAN_QUIWK_SUPPOWT_ECC |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static stwuct fwexcan_devtype_data fsw_imx93_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_DISABWE_MECW | FWEXCAN_QUIWK_USE_WX_MAIWBOX |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE | FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW |
		FWEXCAN_QUIWK_SUPPOWT_FD | FWEXCAN_QUIWK_SUPPOWT_ECC |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static const stwuct fwexcan_devtype_data fsw_vf610_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_DISABWE_MECW | FWEXCAN_QUIWK_USE_WX_MAIWBOX |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE | FWEXCAN_QUIWK_SUPPOWT_ECC |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static const stwuct fwexcan_devtype_data fsw_ws1021a_w2_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_BWOKEN_PEWW_STATE | FWEXCAN_QUIWK_USE_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static const stwuct fwexcan_devtype_data fsw_wx2160a_w1_devtype_data = {
	.quiwks = FWEXCAN_QUIWK_DISABWE_WXFG | FWEXCAN_QUIWK_ENABWE_EACEN_WWS |
		FWEXCAN_QUIWK_DISABWE_MECW | FWEXCAN_QUIWK_BWOKEN_PEWW_STATE |
		FWEXCAN_QUIWK_USE_WX_MAIWBOX | FWEXCAN_QUIWK_SUPPOWT_FD |
		FWEXCAN_QUIWK_SUPPOWT_ECC |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW,
};

static const stwuct can_bittiming_const fwexcan_bittiming_const = {
	.name = DWV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 256,
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const fwexcan_fd_bittiming_const = {
	.name = DWV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 96,
	.tseg2_min = 2,
	.tseg2_max = 32,
	.sjw_max = 16,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

static const stwuct can_bittiming_const fwexcan_fd_data_bittiming_const = {
	.name = DWV_NAME,
	.tseg1_min = 2,
	.tseg1_max = 39,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

/* FwexCAN moduwe is essentiawwy modewwed as a wittwe-endian IP in most
 * SoCs, i.e the wegistews as weww as the message buffew aweas awe
 * impwemented in a wittwe-endian fashion.
 *
 * Howevew thewe awe some SoCs (e.g. WS1021A) which impwement the FwexCAN
 * moduwe in a big-endian fashion (i.e the wegistews as weww as the
 * message buffew aweas awe impwemented in a big-endian way).
 *
 * In addition, the FwexCAN moduwe can be found on SoCs having AWM ow
 * PPC cowes. So, we need to abstwact off the wegistew wead/wwite
 * functions, ensuwing that these catew to aww the combinations of moduwe
 * endianness and undewwying CPU endianness.
 */
static inwine u32 fwexcan_wead_be(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static inwine void fwexcan_wwite_be(u32 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw);
}

static inwine u32 fwexcan_wead_we(void __iomem *addw)
{
	wetuwn iowead32(addw);
}

static inwine void fwexcan_wwite_we(u32 vaw, void __iomem *addw)
{
	iowwite32(vaw, addw);
}

static stwuct fwexcan_mb __iomem *fwexcan_get_mb(const stwuct fwexcan_pwiv *pwiv,
						 u8 mb_index)
{
	u8 bank_size;
	boow bank;

	if (WAWN_ON(mb_index >= pwiv->mb_count))
		wetuwn NUWW;

	bank_size = sizeof(pwiv->wegs->mb[0]) / pwiv->mb_size;

	bank = mb_index >= bank_size;
	if (bank)
		mb_index -= bank_size;

	wetuwn (stwuct fwexcan_mb __iomem *)
		(&pwiv->wegs->mb[bank][pwiv->mb_size * mb_index]);
}

static int fwexcan_wow_powew_entew_ack(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	unsigned int timeout = FWEXCAN_TIMEOUT_US / 10;

	whiwe (timeout-- && !(pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_WPM_ACK))
		udeway(10);

	if (!(pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_WPM_ACK))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int fwexcan_wow_powew_exit_ack(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	unsigned int timeout = FWEXCAN_TIMEOUT_US / 10;

	whiwe (timeout-- && (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_WPM_ACK))
		udeway(10);

	if (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_WPM_ACK)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void fwexcan_enabwe_wakeup_iwq(stwuct fwexcan_pwiv *pwiv, boow enabwe)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_mcw;

	weg_mcw = pwiv->wead(&wegs->mcw);

	if (enabwe)
		weg_mcw |= FWEXCAN_MCW_WAK_MSK;
	ewse
		weg_mcw &= ~FWEXCAN_MCW_WAK_MSK;

	pwiv->wwite(weg_mcw, &wegs->mcw);
}

static int fwexcan_stop_mode_enabwe_scfw(stwuct fwexcan_pwiv *pwiv, boow enabwed)
{
	u8 idx = pwiv->scu_idx;
	u32 wswc_id, vaw;

	wswc_id = IMX_SC_W_CAN(idx);

	if (enabwed)
		vaw = 1;
	ewse
		vaw = 0;

	/* stop mode wequest via scu fiwmwawe */
	wetuwn imx_sc_misc_set_contwow(pwiv->sc_ipc_handwe, wswc_id,
				       IMX_SC_C_IPG_STOP, vaw);
}

static inwine int fwexcan_entew_stop_mode(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_mcw;
	int wet;

	weg_mcw = pwiv->wead(&wegs->mcw);
	weg_mcw |= FWEXCAN_MCW_SWF_WAK;
	pwiv->wwite(weg_mcw, &wegs->mcw);

	/* enabwe stop wequest */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_SCFW) {
		wet = fwexcan_stop_mode_enabwe_scfw(pwiv, twue);
		if (wet < 0)
			wetuwn wet;
	} ewse if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW) {
		wegmap_update_bits(pwiv->stm.gpw, pwiv->stm.weq_gpw,
				   1 << pwiv->stm.weq_bit, 1 << pwiv->stm.weq_bit);
	}

	wetuwn fwexcan_wow_powew_entew_ack(pwiv);
}

static inwine int fwexcan_exit_stop_mode(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_mcw;
	int wet;

	/* wemove stop wequest */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_SCFW) {
		wet = fwexcan_stop_mode_enabwe_scfw(pwiv, fawse);
		if (wet < 0)
			wetuwn wet;
	} ewse if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW) {
		wegmap_update_bits(pwiv->stm.gpw, pwiv->stm.weq_gpw,
				   1 << pwiv->stm.weq_bit, 0);
	}

	weg_mcw = pwiv->wead(&wegs->mcw);
	weg_mcw &= ~FWEXCAN_MCW_SWF_WAK;
	pwiv->wwite(weg_mcw, &wegs->mcw);

	wetuwn fwexcan_wow_powew_exit_ack(pwiv);
}

static inwine void fwexcan_ewwow_iwq_enabwe(const stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_ctww = (pwiv->weg_ctww_defauwt | FWEXCAN_CTWW_EWW_MSK);

	pwiv->wwite(weg_ctww, &wegs->ctww);
}

static inwine void fwexcan_ewwow_iwq_disabwe(const stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_ctww = (pwiv->weg_ctww_defauwt & ~FWEXCAN_CTWW_EWW_MSK);

	pwiv->wwite(weg_ctww, &wegs->ctww);
}

static int fwexcan_cwks_enabwe(const stwuct fwexcan_pwiv *pwiv)
{
	int eww = 0;

	if (pwiv->cwk_ipg) {
		eww = cwk_pwepawe_enabwe(pwiv->cwk_ipg);
		if (eww)
			wetuwn eww;
	}

	if (pwiv->cwk_pew) {
		eww = cwk_pwepawe_enabwe(pwiv->cwk_pew);
		if (eww)
			cwk_disabwe_unpwepawe(pwiv->cwk_ipg);
	}

	wetuwn eww;
}

static void fwexcan_cwks_disabwe(const stwuct fwexcan_pwiv *pwiv)
{
	cwk_disabwe_unpwepawe(pwiv->cwk_pew);
	cwk_disabwe_unpwepawe(pwiv->cwk_ipg);
}

static inwine int fwexcan_twansceivew_enabwe(const stwuct fwexcan_pwiv *pwiv)
{
	if (!pwiv->weg_xceivew)
		wetuwn 0;

	wetuwn weguwatow_enabwe(pwiv->weg_xceivew);
}

static inwine int fwexcan_twansceivew_disabwe(const stwuct fwexcan_pwiv *pwiv)
{
	if (!pwiv->weg_xceivew)
		wetuwn 0;

	wetuwn weguwatow_disabwe(pwiv->weg_xceivew);
}

static int fwexcan_chip_enabwe(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg;

	weg = pwiv->wead(&wegs->mcw);
	weg &= ~FWEXCAN_MCW_MDIS;
	pwiv->wwite(weg, &wegs->mcw);

	wetuwn fwexcan_wow_powew_exit_ack(pwiv);
}

static int fwexcan_chip_disabwe(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg;

	weg = pwiv->wead(&wegs->mcw);
	weg |= FWEXCAN_MCW_MDIS;
	pwiv->wwite(weg, &wegs->mcw);

	wetuwn fwexcan_wow_powew_entew_ack(pwiv);
}

static int fwexcan_chip_fweeze(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	unsigned int timeout;
	u32 bitwate = pwiv->can.bittiming.bitwate;
	u32 weg;

	if (bitwate)
		timeout = 1000 * 1000 * 10 / bitwate;
	ewse
		timeout = FWEXCAN_TIMEOUT_US / 10;

	weg = pwiv->wead(&wegs->mcw);
	weg |= FWEXCAN_MCW_FWZ | FWEXCAN_MCW_HAWT;
	pwiv->wwite(weg, &wegs->mcw);

	whiwe (timeout-- && !(pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_FWZ_ACK))
		udeway(100);

	if (!(pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_FWZ_ACK))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int fwexcan_chip_unfweeze(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	unsigned int timeout = FWEXCAN_TIMEOUT_US / 10;
	u32 weg;

	weg = pwiv->wead(&wegs->mcw);
	weg &= ~FWEXCAN_MCW_HAWT;
	pwiv->wwite(weg, &wegs->mcw);

	whiwe (timeout-- && (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_FWZ_ACK))
		udeway(10);

	if (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_FWZ_ACK)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int fwexcan_chip_softweset(stwuct fwexcan_pwiv *pwiv)
{
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	unsigned int timeout = FWEXCAN_TIMEOUT_US / 10;

	pwiv->wwite(FWEXCAN_MCW_SOFTWST, &wegs->mcw);
	whiwe (timeout-- && (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_SOFTWST))
		udeway(10);

	if (pwiv->wead(&wegs->mcw) & FWEXCAN_MCW_SOFTWST)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int __fwexcan_get_beww_countew(const stwuct net_device *dev,
				      stwuct can_beww_countew *bec)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg = pwiv->wead(&wegs->ecw);

	bec->txeww = (weg >> 0) & 0xff;
	bec->wxeww = (weg >> 8) & 0xff;

	wetuwn 0;
}

static int fwexcan_get_beww_countew(const stwuct net_device *dev,
				    stwuct can_beww_countew *bec)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	eww = pm_wuntime_wesume_and_get(pwiv->dev);
	if (eww < 0)
		wetuwn eww;

	eww = __fwexcan_get_beww_countew(dev, bec);

	pm_wuntime_put(pwiv->dev);

	wetuwn eww;
}

static netdev_tx_t fwexcan_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct canfd_fwame *cfd = (stwuct canfd_fwame *)skb->data;
	u32 can_id;
	u32 data;
	u32 ctww = FWEXCAN_MB_CODE_TX_DATA | ((can_fd_wen2dwc(cfd->wen)) << 16);
	int i;

	if (can_dev_dwopped_skb(dev, skb))
		wetuwn NETDEV_TX_OK;

	netif_stop_queue(dev);

	if (cfd->can_id & CAN_EFF_FWAG) {
		can_id = cfd->can_id & CAN_EFF_MASK;
		ctww |= FWEXCAN_MB_CNT_IDE | FWEXCAN_MB_CNT_SWW;
	} ewse {
		can_id = (cfd->can_id & CAN_SFF_MASK) << 18;
	}

	if (cfd->can_id & CAN_WTW_FWAG)
		ctww |= FWEXCAN_MB_CNT_WTW;

	if (can_is_canfd_skb(skb)) {
		ctww |= FWEXCAN_MB_CNT_EDW;

		if (cfd->fwags & CANFD_BWS)
			ctww |= FWEXCAN_MB_CNT_BWS;
	}

	fow (i = 0; i < cfd->wen; i += sizeof(u32)) {
		data = be32_to_cpup((__be32 *)&cfd->data[i]);
		pwiv->wwite(data, &pwiv->tx_mb->data[i / sizeof(u32)]);
	}

	can_put_echo_skb(skb, dev, 0, 0);

	pwiv->wwite(can_id, &pwiv->tx_mb->can_id);
	pwiv->wwite(ctww, &pwiv->tx_mb->can_ctww);

	/* Ewwata EWW005829 step8:
	 * Wwite twice INACTIVE(0x8) code to fiwst MB.
	 */
	pwiv->wwite(FWEXCAN_MB_CODE_TX_INACTIVE,
		    &pwiv->tx_mb_wesewved->can_ctww);
	pwiv->wwite(FWEXCAN_MB_CODE_TX_INACTIVE,
		    &pwiv->tx_mb_wesewved->can_ctww);

	wetuwn NETDEV_TX_OK;
}

static void fwexcan_iwq_bus_eww(stwuct net_device *dev, u32 weg_esw)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	boow wx_ewwows = fawse, tx_ewwows = fawse;
	u32 timestamp;
	int eww;

	timestamp = pwiv->wead(&wegs->timew) << 16;

	skb = awwoc_can_eww_skb(dev, &cf);
	if (unwikewy(!skb))
		wetuwn;

	cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

	if (weg_esw & FWEXCAN_ESW_BIT1_EWW) {
		netdev_dbg(dev, "BIT1_EWW iwq\n");
		cf->data[2] |= CAN_EWW_PWOT_BIT1;
		tx_ewwows = twue;
	}
	if (weg_esw & FWEXCAN_ESW_BIT0_EWW) {
		netdev_dbg(dev, "BIT0_EWW iwq\n");
		cf->data[2] |= CAN_EWW_PWOT_BIT0;
		tx_ewwows = twue;
	}
	if (weg_esw & FWEXCAN_ESW_ACK_EWW) {
		netdev_dbg(dev, "ACK_EWW iwq\n");
		cf->can_id |= CAN_EWW_ACK;
		cf->data[3] = CAN_EWW_PWOT_WOC_ACK;
		tx_ewwows = twue;
	}
	if (weg_esw & FWEXCAN_ESW_CWC_EWW) {
		netdev_dbg(dev, "CWC_EWW iwq\n");
		cf->data[2] |= CAN_EWW_PWOT_BIT;
		cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		wx_ewwows = twue;
	}
	if (weg_esw & FWEXCAN_ESW_FWM_EWW) {
		netdev_dbg(dev, "FWM_EWW iwq\n");
		cf->data[2] |= CAN_EWW_PWOT_FOWM;
		wx_ewwows = twue;
	}
	if (weg_esw & FWEXCAN_ESW_STF_EWW) {
		netdev_dbg(dev, "STF_EWW iwq\n");
		cf->data[2] |= CAN_EWW_PWOT_STUFF;
		wx_ewwows = twue;
	}

	pwiv->can.can_stats.bus_ewwow++;
	if (wx_ewwows)
		dev->stats.wx_ewwows++;
	if (tx_ewwows)
		dev->stats.tx_ewwows++;

	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		dev->stats.wx_fifo_ewwows++;
}

static void fwexcan_iwq_state(stwuct net_device *dev, u32 weg_esw)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;
	enum can_state new_state, wx_state, tx_state;
	int fwt;
	stwuct can_beww_countew bec;
	u32 timestamp;
	int eww;

	fwt = weg_esw & FWEXCAN_ESW_FWT_CONF_MASK;
	if (wikewy(fwt == FWEXCAN_ESW_FWT_CONF_ACTIVE)) {
		tx_state = unwikewy(weg_esw & FWEXCAN_ESW_TX_WWN) ?
			CAN_STATE_EWWOW_WAWNING : CAN_STATE_EWWOW_ACTIVE;
		wx_state = unwikewy(weg_esw & FWEXCAN_ESW_WX_WWN) ?
			CAN_STATE_EWWOW_WAWNING : CAN_STATE_EWWOW_ACTIVE;
		new_state = max(tx_state, wx_state);
	} ewse {
		__fwexcan_get_beww_countew(dev, &bec);
		new_state = fwt == FWEXCAN_ESW_FWT_CONF_PASSIVE ?
			CAN_STATE_EWWOW_PASSIVE : CAN_STATE_BUS_OFF;
		wx_state = bec.wxeww >= bec.txeww ? new_state : 0;
		tx_state = bec.wxeww <= bec.txeww ? new_state : 0;
	}

	/* state hasn't changed */
	if (wikewy(new_state == pwiv->can.state))
		wetuwn;

	timestamp = pwiv->wead(&wegs->timew) << 16;

	skb = awwoc_can_eww_skb(dev, &cf);
	if (unwikewy(!skb))
		wetuwn;

	can_change_state(dev, cf, tx_state, wx_state);

	if (unwikewy(new_state == CAN_STATE_BUS_OFF))
		can_bus_off(dev);

	eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb, timestamp);
	if (eww)
		dev->stats.wx_fifo_ewwows++;
}

static inwine u64 fwexcan_wead64_mask(stwuct fwexcan_pwiv *pwiv, void __iomem *addw, u64 mask)
{
	u64 weg = 0;

	if (uppew_32_bits(mask))
		weg = (u64)pwiv->wead(addw - 4) << 32;
	if (wowew_32_bits(mask))
		weg |= pwiv->wead(addw);

	wetuwn weg & mask;
}

static inwine void fwexcan_wwite64(stwuct fwexcan_pwiv *pwiv, u64 vaw, void __iomem *addw)
{
	if (uppew_32_bits(vaw))
		pwiv->wwite(uppew_32_bits(vaw), addw - 4);
	if (wowew_32_bits(vaw))
		pwiv->wwite(wowew_32_bits(vaw), addw);
}

static inwine u64 fwexcan_wead_weg_ifwag_wx(stwuct fwexcan_pwiv *pwiv)
{
	wetuwn fwexcan_wead64_mask(pwiv, &pwiv->wegs->ifwag1, pwiv->wx_mask);
}

static inwine u64 fwexcan_wead_weg_ifwag_tx(stwuct fwexcan_pwiv *pwiv)
{
	wetuwn fwexcan_wead64_mask(pwiv, &pwiv->wegs->ifwag1, pwiv->tx_mask);
}

static inwine stwuct fwexcan_pwiv *wx_offwoad_to_pwiv(stwuct can_wx_offwoad *offwoad)
{
	wetuwn containew_of(offwoad, stwuct fwexcan_pwiv, offwoad);
}

static stwuct sk_buff *fwexcan_maiwbox_wead(stwuct can_wx_offwoad *offwoad,
					    unsigned int n, u32 *timestamp,
					    boow dwop)
{
	stwuct fwexcan_pwiv *pwiv = wx_offwoad_to_pwiv(offwoad);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct fwexcan_mb __iomem *mb;
	stwuct sk_buff *skb;
	stwuct canfd_fwame *cfd;
	u32 weg_ctww, weg_id, weg_ifwag1;
	int i;

	mb = fwexcan_get_mb(pwiv, n);

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX) {
		u32 code;

		do {
			weg_ctww = pwiv->wead(&mb->can_ctww);
		} whiwe (weg_ctww & FWEXCAN_MB_CODE_WX_BUSY_BIT);

		/* is this MB empty? */
		code = weg_ctww & FWEXCAN_MB_CODE_MASK;
		if ((code != FWEXCAN_MB_CODE_WX_FUWW) &&
		    (code != FWEXCAN_MB_CODE_WX_OVEWWUN))
			wetuwn NUWW;

		if (code == FWEXCAN_MB_CODE_WX_OVEWWUN) {
			/* This MB was ovewwun, we wost data */
			offwoad->dev->stats.wx_ovew_ewwows++;
			offwoad->dev->stats.wx_ewwows++;
		}
	} ewse {
		weg_ifwag1 = pwiv->wead(&wegs->ifwag1);
		if (!(weg_ifwag1 & FWEXCAN_IFWAG_WX_FIFO_AVAIWABWE))
			wetuwn NUWW;

		weg_ctww = pwiv->wead(&mb->can_ctww);
	}

	if (unwikewy(dwop)) {
		skb = EWW_PTW(-ENOBUFS);
		goto mawk_as_wead;
	}

	if (weg_ctww & FWEXCAN_MB_CNT_EDW)
		skb = awwoc_canfd_skb(offwoad->dev, &cfd);
	ewse
		skb = awwoc_can_skb(offwoad->dev, (stwuct can_fwame **)&cfd);
	if (unwikewy(!skb)) {
		skb = EWW_PTW(-ENOMEM);
		goto mawk_as_wead;
	}

	/* incwease timstamp to fuww 32 bit */
	*timestamp = weg_ctww << 16;

	weg_id = pwiv->wead(&mb->can_id);
	if (weg_ctww & FWEXCAN_MB_CNT_IDE)
		cfd->can_id = ((weg_id >> 0) & CAN_EFF_MASK) | CAN_EFF_FWAG;
	ewse
		cfd->can_id = (weg_id >> 18) & CAN_SFF_MASK;

	if (weg_ctww & FWEXCAN_MB_CNT_EDW) {
		cfd->wen = can_fd_dwc2wen((weg_ctww >> 16) & 0xf);

		if (weg_ctww & FWEXCAN_MB_CNT_BWS)
			cfd->fwags |= CANFD_BWS;
	} ewse {
		cfd->wen = can_cc_dwc2wen((weg_ctww >> 16) & 0xf);

		if (weg_ctww & FWEXCAN_MB_CNT_WTW)
			cfd->can_id |= CAN_WTW_FWAG;
	}

	if (weg_ctww & FWEXCAN_MB_CNT_ESI)
		cfd->fwags |= CANFD_ESI;

	fow (i = 0; i < cfd->wen; i += sizeof(u32)) {
		__be32 data = cpu_to_be32(pwiv->wead(&mb->data[i / sizeof(u32)]));
		*(__be32 *)(cfd->data + i) = data;
	}

 mawk_as_wead:
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX)
		fwexcan_wwite64(pwiv, FWEXCAN_IFWAG_MB(n), &wegs->ifwag1);
	ewse
		pwiv->wwite(FWEXCAN_IFWAG_WX_FIFO_AVAIWABWE, &wegs->ifwag1);

	/* Wead the Fwee Wunning Timew. It is optionaw but wecommended
	 * to unwock Maiwbox as soon as possibwe and make it avaiwabwe
	 * fow weception.
	 */
	pwiv->wead(&wegs->timew);

	wetuwn skb;
}

static iwqwetuwn_t fwexcan_iwq(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct net_device_stats *stats = &dev->stats;
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	iwqwetuwn_t handwed = IWQ_NONE;
	u64 weg_ifwag_tx;
	u32 weg_esw;
	enum can_state wast_state = pwiv->can.state;

	/* weception intewwupt */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX) {
		u64 weg_ifwag_wx;
		int wet;

		whiwe ((weg_ifwag_wx = fwexcan_wead_weg_ifwag_wx(pwiv))) {
			handwed = IWQ_HANDWED;
			wet = can_wx_offwoad_iwq_offwoad_timestamp(&pwiv->offwoad,
								   weg_ifwag_wx);
			if (!wet)
				bweak;
		}
	} ewse {
		u32 weg_ifwag1;

		weg_ifwag1 = pwiv->wead(&wegs->ifwag1);
		if (weg_ifwag1 & FWEXCAN_IFWAG_WX_FIFO_AVAIWABWE) {
			handwed = IWQ_HANDWED;
			can_wx_offwoad_iwq_offwoad_fifo(&pwiv->offwoad);
		}

		/* FIFO ovewfwow intewwupt */
		if (weg_ifwag1 & FWEXCAN_IFWAG_WX_FIFO_OVEWFWOW) {
			handwed = IWQ_HANDWED;
			pwiv->wwite(FWEXCAN_IFWAG_WX_FIFO_OVEWFWOW,
				    &wegs->ifwag1);
			dev->stats.wx_ovew_ewwows++;
			dev->stats.wx_ewwows++;
		}
	}

	weg_ifwag_tx = fwexcan_wead_weg_ifwag_tx(pwiv);

	/* twansmission compwete intewwupt */
	if (weg_ifwag_tx & pwiv->tx_mask) {
		u32 weg_ctww = pwiv->wead(&pwiv->tx_mb->can_ctww);

		handwed = IWQ_HANDWED;
		stats->tx_bytes +=
			can_wx_offwoad_get_echo_skb_queue_timestamp(&pwiv->offwoad, 0,
								    weg_ctww << 16, NUWW);
		stats->tx_packets++;

		/* aftew sending a WTW fwame MB is in WX mode */
		pwiv->wwite(FWEXCAN_MB_CODE_TX_INACTIVE,
			    &pwiv->tx_mb->can_ctww);
		fwexcan_wwite64(pwiv, pwiv->tx_mask, &wegs->ifwag1);
		netif_wake_queue(dev);
	}

	weg_esw = pwiv->wead(&wegs->esw);

	/* ACK aww bus ewwow, state change and wake IWQ souwces */
	if (weg_esw & (FWEXCAN_ESW_AWW_INT | FWEXCAN_ESW_WAK_INT)) {
		handwed = IWQ_HANDWED;
		pwiv->wwite(weg_esw & (FWEXCAN_ESW_AWW_INT | FWEXCAN_ESW_WAK_INT), &wegs->esw);
	}

	/* state change intewwupt ow bwoken ewwow state quiwk fix is enabwed */
	if ((weg_esw & FWEXCAN_ESW_EWW_STATE) ||
	    (pwiv->devtype_data.quiwks & (FWEXCAN_QUIWK_BWOKEN_WEWW_STATE |
					   FWEXCAN_QUIWK_BWOKEN_PEWW_STATE)))
		fwexcan_iwq_state(dev, weg_esw);

	/* bus ewwow IWQ - handwe if bus ewwow wepowting is activated */
	if ((weg_esw & FWEXCAN_ESW_EWW_BUS) &&
	    (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING))
		fwexcan_iwq_bus_eww(dev, weg_esw);

	/* avaiwabiwity of ewwow intewwupt among state twansitions in case
	 * bus ewwow wepowting is de-activated and
	 * FWEXCAN_QUIWK_BWOKEN_PEWW_STATE is enabwed:
	 *  +--------------------------------------------------------------+
	 *  | +----------------------------------------------+ [stopped /  |
	 *  | |                                              |  sweeping] -+
	 *  +-+-> active <-> wawning <-> passive -> bus off -+
	 *        ___________^^^^^^^^^^^^_______________________________
	 *        disabwed(1)  enabwed             disabwed
	 *
	 * (1): enabwed if FWEXCAN_QUIWK_BWOKEN_WEWW_STATE is enabwed
	 */
	if ((wast_state != pwiv->can.state) &&
	    (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_BWOKEN_PEWW_STATE) &&
	    !(pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)) {
		switch (pwiv->can.state) {
		case CAN_STATE_EWWOW_ACTIVE:
			if (pwiv->devtype_data.quiwks &
			    FWEXCAN_QUIWK_BWOKEN_WEWW_STATE)
				fwexcan_ewwow_iwq_enabwe(pwiv);
			ewse
				fwexcan_ewwow_iwq_disabwe(pwiv);
			bweak;

		case CAN_STATE_EWWOW_WAWNING:
			fwexcan_ewwow_iwq_enabwe(pwiv);
			bweak;

		case CAN_STATE_EWWOW_PASSIVE:
		case CAN_STATE_BUS_OFF:
			fwexcan_ewwow_iwq_disabwe(pwiv);
			bweak;

		defauwt:
			bweak;
		}
	}

	if (handwed)
		can_wx_offwoad_iwq_finish(&pwiv->offwoad);

	wetuwn handwed;
}

static void fwexcan_set_bittiming_ctww(const stwuct net_device *dev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	const stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg;

	weg = pwiv->wead(&wegs->ctww);
	weg &= ~(FWEXCAN_CTWW_PWESDIV(0xff) |
		 FWEXCAN_CTWW_WJW(0x3) |
		 FWEXCAN_CTWW_PSEG1(0x7) |
		 FWEXCAN_CTWW_PSEG2(0x7) |
		 FWEXCAN_CTWW_PWOPSEG(0x7));

	weg |= FWEXCAN_CTWW_PWESDIV(bt->bwp - 1) |
		FWEXCAN_CTWW_PSEG1(bt->phase_seg1 - 1) |
		FWEXCAN_CTWW_PSEG2(bt->phase_seg2 - 1) |
		FWEXCAN_CTWW_WJW(bt->sjw - 1) |
		FWEXCAN_CTWW_PWOPSEG(bt->pwop_seg - 1);

	netdev_dbg(dev, "wwiting ctww=0x%08x\n", weg);
	pwiv->wwite(weg, &wegs->ctww);

	/* pwint chip status */
	netdev_dbg(dev, "%s: mcw=0x%08x ctww=0x%08x\n", __func__,
		   pwiv->wead(&wegs->mcw), pwiv->wead(&wegs->ctww));
}

static void fwexcan_set_bittiming_cbt(const stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_cbt, weg_fdctww;

	/* CBT */
	/* CBT[EPSEG1] is 5 bit wong and CBT[EPWOPSEG] is 6 bit
	 * wong. The can_cawc_bittiming() twies to divide the tseg1
	 * equawwy between phase_seg1 and pwop_seg, which may not fit
	 * in CBT wegistew. Thewefowe, if phase_seg1 is mowe than
	 * possibwe vawue, incwease pwop_seg and decwease phase_seg1.
	 */
	if (bt->phase_seg1 > 0x20) {
		bt->pwop_seg += (bt->phase_seg1 - 0x20);
		bt->phase_seg1 = 0x20;
	}

	weg_cbt = FWEXCAN_CBT_BTF |
		FIEWD_PWEP(FWEXCAN_CBT_EPWESDIV_MASK, bt->bwp - 1) |
		FIEWD_PWEP(FWEXCAN_CBT_EWJW_MASK, bt->sjw - 1) |
		FIEWD_PWEP(FWEXCAN_CBT_EPWOPSEG_MASK, bt->pwop_seg - 1) |
		FIEWD_PWEP(FWEXCAN_CBT_EPSEG1_MASK, bt->phase_seg1 - 1) |
		FIEWD_PWEP(FWEXCAN_CBT_EPSEG2_MASK, bt->phase_seg2 - 1);

	netdev_dbg(dev, "wwiting cbt=0x%08x\n", weg_cbt);
	pwiv->wwite(weg_cbt, &wegs->cbt);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD) {
		u32 weg_fdcbt, weg_ctww2;

		if (bt->bwp != dbt->bwp)
			netdev_wawn(dev, "Data bwp=%d and bwp=%d don't match, this may wesuwt in a phase ewwow. Considew using diffewent bitwate and/ow data bitwate.\n",
				    dbt->bwp, bt->bwp);

		/* FDCBT */
		/* FDCBT[FPSEG1] is 3 bit wong and FDCBT[FPWOPSEG] is
		 * 5 bit wong. The can_cawc_bittiming twies to divide
		 * the tseg1 equawwy between phase_seg1 and pwop_seg,
		 * which may not fit in FDCBT wegistew. Thewefowe, if
		 * phase_seg1 is mowe than possibwe vawue, incwease
		 * pwop_seg and decwease phase_seg1
		 */
		if (dbt->phase_seg1 > 0x8) {
			dbt->pwop_seg += (dbt->phase_seg1 - 0x8);
			dbt->phase_seg1 = 0x8;
		}

		weg_fdcbt = pwiv->wead(&wegs->fdcbt);
		weg_fdcbt &= ~(FIEWD_PWEP(FWEXCAN_FDCBT_FPWESDIV_MASK, 0x3ff) |
			       FIEWD_PWEP(FWEXCAN_FDCBT_FWJW_MASK, 0x7) |
			       FIEWD_PWEP(FWEXCAN_FDCBT_FPWOPSEG_MASK, 0x1f) |
			       FIEWD_PWEP(FWEXCAN_FDCBT_FPSEG1_MASK, 0x7) |
			       FIEWD_PWEP(FWEXCAN_FDCBT_FPSEG2_MASK, 0x7));

		weg_fdcbt |= FIEWD_PWEP(FWEXCAN_FDCBT_FPWESDIV_MASK, dbt->bwp - 1) |
			FIEWD_PWEP(FWEXCAN_FDCBT_FWJW_MASK, dbt->sjw - 1) |
			FIEWD_PWEP(FWEXCAN_FDCBT_FPWOPSEG_MASK, dbt->pwop_seg) |
			FIEWD_PWEP(FWEXCAN_FDCBT_FPSEG1_MASK, dbt->phase_seg1 - 1) |
			FIEWD_PWEP(FWEXCAN_FDCBT_FPSEG2_MASK, dbt->phase_seg2 - 1);

		netdev_dbg(dev, "wwiting fdcbt=0x%08x\n", weg_fdcbt);
		pwiv->wwite(weg_fdcbt, &wegs->fdcbt);

		/* CTWW2 */
		weg_ctww2 = pwiv->wead(&wegs->ctww2);
		weg_ctww2 &= ~FWEXCAN_CTWW2_ISOCANFDEN;
		if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_FD_NON_ISO))
			weg_ctww2 |= FWEXCAN_CTWW2_ISOCANFDEN;

		netdev_dbg(dev, "wwiting ctww2=0x%08x\n", weg_ctww2);
		pwiv->wwite(weg_ctww2, &wegs->ctww2);
	}

	/* FDCTWW */
	weg_fdctww = pwiv->wead(&wegs->fdctww);
	weg_fdctww &= ~(FWEXCAN_FDCTWW_FDWATE |
			FIEWD_PWEP(FWEXCAN_FDCTWW_TDCOFF, 0x1f));

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD) {
		weg_fdctww |= FWEXCAN_FDCTWW_FDWATE;

		if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK) {
			/* TDC must be disabwed fow Woop Back mode */
			weg_fdctww &= ~FWEXCAN_FDCTWW_TDCEN;
		} ewse {
			weg_fdctww |= FWEXCAN_FDCTWW_TDCEN |
				FIEWD_PWEP(FWEXCAN_FDCTWW_TDCOFF,
					   ((dbt->phase_seg1 - 1) +
					    dbt->pwop_seg + 2) *
					   ((dbt->bwp - 1 ) + 1));
		}
	}

	netdev_dbg(dev, "wwiting fdctww=0x%08x\n", weg_fdctww);
	pwiv->wwite(weg_fdctww, &wegs->fdctww);

	netdev_dbg(dev, "%s: mcw=0x%08x ctww=0x%08x ctww2=0x%08x fdctww=0x%08x cbt=0x%08x fdcbt=0x%08x\n",
		   __func__,
		   pwiv->wead(&wegs->mcw), pwiv->wead(&wegs->ctww),
		   pwiv->wead(&wegs->ctww2), pwiv->wead(&wegs->fdctww),
		   pwiv->wead(&wegs->cbt), pwiv->wead(&wegs->fdcbt));
}

static void fwexcan_set_bittiming(stwuct net_device *dev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg;

	weg = pwiv->wead(&wegs->ctww);
	weg &= ~(FWEXCAN_CTWW_WPB | FWEXCAN_CTWW_SMP |
		 FWEXCAN_CTWW_WOM);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		weg |= FWEXCAN_CTWW_WPB;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		weg |= FWEXCAN_CTWW_WOM;
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES)
		weg |= FWEXCAN_CTWW_SMP;

	netdev_dbg(dev, "wwiting ctww=0x%08x\n", weg);
	pwiv->wwite(weg, &wegs->ctww);

	if (pwiv->can.ctwwmode_suppowted & CAN_CTWWMODE_FD)
		wetuwn fwexcan_set_bittiming_cbt(dev);
	ewse
		wetuwn fwexcan_set_bittiming_ctww(dev);
}

static void fwexcan_wam_init(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_ctww2;

	/* 11.8.3.13 Detection and cowwection of memowy ewwows:
	 * CTWW2[WWMFWZ] gwants wwite access to aww memowy positions
	 * that wequiwe initiawization, wanging fwom 0x080 to 0xADF
	 * and fwom 0xF28 to 0xFFF when the CAN FD featuwe is enabwed.
	 * The WXMGMASK, WX14MASK, WX15MASK, and WXFGMASK wegistews
	 * need to be initiawized as weww. MCW[WFEN] must not be set
	 * duwing memowy initiawization.
	 */
	weg_ctww2 = pwiv->wead(&wegs->ctww2);
	weg_ctww2 |= FWEXCAN_CTWW2_WWMFWZ;
	pwiv->wwite(weg_ctww2, &wegs->ctww2);

	memset_io(&wegs->init, 0, sizeof(wegs->init));

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)
		memset_io(&wegs->init_fd, 0, sizeof(wegs->init_fd));

	weg_ctww2 &= ~FWEXCAN_CTWW2_WWMFWZ;
	pwiv->wwite(weg_ctww2, &wegs->ctww2);
}

static int fwexcan_wx_offwoad_setup(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)
		pwiv->mb_size = sizeof(stwuct fwexcan_mb) + CANFD_MAX_DWEN;
	ewse
		pwiv->mb_size = sizeof(stwuct fwexcan_mb) + CAN_MAX_DWEN;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_NW_MB_16)
		pwiv->mb_count = 16;
	ewse
		pwiv->mb_count = (sizeof(pwiv->wegs->mb[0]) / pwiv->mb_size) +
				 (sizeof(pwiv->wegs->mb[1]) / pwiv->mb_size);

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX)
		pwiv->tx_mb_wesewved =
			fwexcan_get_mb(pwiv, FWEXCAN_TX_MB_WESEWVED_WX_MAIWBOX);
	ewse
		pwiv->tx_mb_wesewved =
			fwexcan_get_mb(pwiv, FWEXCAN_TX_MB_WESEWVED_WX_FIFO);
	pwiv->tx_mb_idx = pwiv->mb_count - 1;
	pwiv->tx_mb = fwexcan_get_mb(pwiv, pwiv->tx_mb_idx);
	pwiv->tx_mask = FWEXCAN_IFWAG_MB(pwiv->tx_mb_idx);

	pwiv->offwoad.maiwbox_wead = fwexcan_maiwbox_wead;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX) {
		pwiv->offwoad.mb_fiwst = FWEXCAN_WX_MB_WX_MAIWBOX_FIWST;
		pwiv->offwoad.mb_wast = pwiv->mb_count - 2;

		pwiv->wx_mask = GENMASK_UWW(pwiv->offwoad.mb_wast,
					    pwiv->offwoad.mb_fiwst);
		eww = can_wx_offwoad_add_timestamp(dev, &pwiv->offwoad);
	} ewse {
		pwiv->wx_mask = FWEXCAN_IFWAG_WX_FIFO_OVEWFWOW |
			FWEXCAN_IFWAG_WX_FIFO_AVAIWABWE;
		eww = can_wx_offwoad_add_fifo(dev, &pwiv->offwoad,
					      FWEXCAN_NAPI_WEIGHT);
	}

	wetuwn eww;
}

static void fwexcan_chip_intewwupts_enabwe(const stwuct net_device *dev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u64 weg_imask;

	disabwe_iwq(dev->iwq);
	pwiv->wwite(pwiv->weg_ctww_defauwt, &wegs->ctww);
	weg_imask = pwiv->wx_mask | pwiv->tx_mask;
	pwiv->wwite(uppew_32_bits(weg_imask), &wegs->imask2);
	pwiv->wwite(wowew_32_bits(weg_imask), &wegs->imask1);
	enabwe_iwq(dev->iwq);
}

static void fwexcan_chip_intewwupts_disabwe(const stwuct net_device *dev)
{
	const stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;

	pwiv->wwite(0, &wegs->imask2);
	pwiv->wwite(0, &wegs->imask1);
	pwiv->wwite(pwiv->weg_ctww_defauwt & ~FWEXCAN_CTWW_EWW_AWW,
		    &wegs->ctww);
}

/* fwexcan_chip_stawt
 *
 * this functions is entewed with cwocks enabwed
 *
 */
static int fwexcan_chip_stawt(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg_mcw, weg_ctww, weg_ctww2, weg_mecw;
	int eww, i;
	stwuct fwexcan_mb __iomem *mb;

	/* enabwe moduwe */
	eww = fwexcan_chip_enabwe(pwiv);
	if (eww)
		wetuwn eww;

	/* soft weset */
	eww = fwexcan_chip_softweset(pwiv);
	if (eww)
		goto out_chip_disabwe;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SUPPOWT_ECC)
		fwexcan_wam_init(dev);

	fwexcan_set_bittiming(dev);

	/* set fweeze, hawt */
	eww = fwexcan_chip_fweeze(pwiv);
	if (eww)
		goto out_chip_disabwe;

	/* MCW
	 *
	 * onwy supewvisow access
	 * enabwe wawning int
	 * enabwe individuaw WX masking
	 * choose fowmat C
	 * set max maiwbox numbew
	 */
	weg_mcw = pwiv->wead(&wegs->mcw);
	weg_mcw &= ~FWEXCAN_MCW_MAXMB(0xff);
	weg_mcw |= FWEXCAN_MCW_SUPV | FWEXCAN_MCW_WWN_EN | FWEXCAN_MCW_IWMQ |
		FWEXCAN_MCW_IDAM_C | FWEXCAN_MCW_MAXMB(pwiv->tx_mb_idx);

	/* MCW
	 *
	 * FIFO:
	 * - disabwe fow maiwbox mode
	 * - enabwe fow FIFO mode
	 */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX)
		weg_mcw &= ~FWEXCAN_MCW_FEN;
	ewse
		weg_mcw |= FWEXCAN_MCW_FEN;

	/* MCW
	 *
	 * NOTE: In woopback mode, the CAN_MCW[SWXDIS] cannot be
	 *       assewted because this wiww impede the sewf weception
	 *       of a twansmitted message. This is not documented in
	 *       eawwiew vewsions of fwexcan bwock guide.
	 *
	 * Sewf Weception:
	 * - enabwe Sewf Weception fow woopback mode
	 *   (by cweawing "Sewf Weception Disabwe" bit)
	 * - disabwe fow nowmaw opewation
	 */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		weg_mcw &= ~FWEXCAN_MCW_SWX_DIS;
	ewse
		weg_mcw |= FWEXCAN_MCW_SWX_DIS;

	/* MCW - CAN-FD */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)
		weg_mcw |= FWEXCAN_MCW_FDEN;
	ewse
		weg_mcw &= ~FWEXCAN_MCW_FDEN;

	netdev_dbg(dev, "%s: wwiting mcw=0x%08x", __func__, weg_mcw);
	pwiv->wwite(weg_mcw, &wegs->mcw);

	/* CTWW
	 *
	 * disabwe timew sync featuwe
	 *
	 * disabwe auto busoff wecovewy
	 * twansmit wowest buffew fiwst
	 *
	 * enabwe tx and wx wawning intewwupt
	 * enabwe bus off intewwupt
	 * (== FWEXCAN_CTWW_EWW_STATE)
	 */
	weg_ctww = pwiv->wead(&wegs->ctww);
	weg_ctww &= ~FWEXCAN_CTWW_TSYN;
	weg_ctww |= FWEXCAN_CTWW_BOFF_WEC | FWEXCAN_CTWW_WBUF |
		FWEXCAN_CTWW_EWW_STATE;

	/* enabwe the "ewwow intewwupt" (FWEXCAN_CTWW_EWW_MSK),
	 * on most Fwexcan cowes, too. Othewwise we don't get
	 * any ewwow wawning ow passive intewwupts.
	 */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_BWOKEN_WEWW_STATE ||
	    pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		weg_ctww |= FWEXCAN_CTWW_EWW_MSK;
	ewse
		weg_ctww &= ~FWEXCAN_CTWW_EWW_MSK;

	/* save fow watew use */
	pwiv->weg_ctww_defauwt = weg_ctww;
	/* weave intewwupts disabwed fow now */
	weg_ctww &= ~FWEXCAN_CTWW_EWW_AWW;
	netdev_dbg(dev, "%s: wwiting ctww=0x%08x", __func__, weg_ctww);
	pwiv->wwite(weg_ctww, &wegs->ctww);

	if ((pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_ENABWE_EACEN_WWS)) {
		weg_ctww2 = pwiv->wead(&wegs->ctww2);
		weg_ctww2 |= FWEXCAN_CTWW2_EACEN | FWEXCAN_CTWW2_WWS;
		pwiv->wwite(weg_ctww2, &wegs->ctww2);
	}

	if (pwiv->can.ctwwmode_suppowted & CAN_CTWWMODE_FD) {
		u32 weg_fdctww;

		weg_fdctww = pwiv->wead(&wegs->fdctww);
		weg_fdctww &= ~(FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW1, 0x3) |
				FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW0, 0x3));

		if (pwiv->can.ctwwmode & CAN_CTWWMODE_FD) {
			weg_fdctww |=
				FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW1,
					   FWEXCAN_FDCTWW_MBDSW_64) |
				FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW0,
					   FWEXCAN_FDCTWW_MBDSW_64);
		} ewse {
			weg_fdctww |=
				FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW1,
					   FWEXCAN_FDCTWW_MBDSW_8) |
				FIEWD_PWEP(FWEXCAN_FDCTWW_MBDSW0,
					   FWEXCAN_FDCTWW_MBDSW_8);
		}

		netdev_dbg(dev, "%s: wwiting fdctww=0x%08x",
			   __func__, weg_fdctww);
		pwiv->wwite(weg_fdctww, &wegs->fdctww);
	}

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_USE_WX_MAIWBOX) {
		fow (i = pwiv->offwoad.mb_fiwst; i <= pwiv->offwoad.mb_wast; i++) {
			mb = fwexcan_get_mb(pwiv, i);
			pwiv->wwite(FWEXCAN_MB_CODE_WX_EMPTY,
				    &mb->can_ctww);
		}
	} ewse {
		/* cweaw and invawidate unused maiwboxes fiwst */
		fow (i = FWEXCAN_TX_MB_WESEWVED_WX_FIFO; i < pwiv->mb_count; i++) {
			mb = fwexcan_get_mb(pwiv, i);
			pwiv->wwite(FWEXCAN_MB_CODE_WX_INACTIVE,
				    &mb->can_ctww);
		}
	}

	/* Ewwata EWW005829: mawk fiwst TX maiwbox as INACTIVE */
	pwiv->wwite(FWEXCAN_MB_CODE_TX_INACTIVE,
		    &pwiv->tx_mb_wesewved->can_ctww);

	/* mawk TX maiwbox as INACTIVE */
	pwiv->wwite(FWEXCAN_MB_CODE_TX_INACTIVE,
		    &pwiv->tx_mb->can_ctww);

	/* acceptance mask/acceptance code (accept evewything) */
	pwiv->wwite(0x0, &wegs->wxgmask);
	pwiv->wwite(0x0, &wegs->wx14mask);
	pwiv->wwite(0x0, &wegs->wx15mask);

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_DISABWE_WXFG)
		pwiv->wwite(0x0, &wegs->wxfgmask);

	/* cweaw acceptance fiwtews */
	fow (i = 0; i < pwiv->mb_count; i++)
		pwiv->wwite(0, &wegs->wximw[i]);

	/* On Vybwid, disabwe non-cowwectabwe ewwows intewwupt and
	 * fweeze mode. It stiww can cowwect the cowwectabwe ewwows
	 * when HW suppowts ECC.
	 *
	 * This awso wowks awound ewwata e5295 which genewates fawse
	 * positive memowy ewwows and put the device in fweeze mode.
	 */
	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_DISABWE_MECW) {
		/* Fowwow the pwotocow as descwibed in "Detection
		 * and Cowwection of Memowy Ewwows" to wwite to
		 * MECW wegistew (step 1 - 5)
		 *
		 * 1. By defauwt, CTWW2[ECWWWE] = 0, MECW[ECWWWDIS] = 1
		 * 2. set CTWW2[ECWWWE]
		 */
		weg_ctww2 = pwiv->wead(&wegs->ctww2);
		weg_ctww2 |= FWEXCAN_CTWW2_ECWWWE;
		pwiv->wwite(weg_ctww2, &wegs->ctww2);

		/* 3. cweaw MECW[ECWWWDIS] */
		weg_mecw = pwiv->wead(&wegs->mecw);
		weg_mecw &= ~FWEXCAN_MECW_ECWWWDIS;
		pwiv->wwite(weg_mecw, &wegs->mecw);

		/* 4. aww wwites to MECW must keep MECW[ECWWWDIS] cweawed */
		weg_mecw &= ~(FWEXCAN_MECW_NCEFAFWZ | FWEXCAN_MECW_HANCEI_MSK |
			      FWEXCAN_MECW_FANCEI_MSK);
		pwiv->wwite(weg_mecw, &wegs->mecw);

		/* 5. aftew configuwation done, wock MECW by eithew
		 * setting MECW[ECWWWDIS] ow cweawing CTWW2[ECWWWE]
		 */
		weg_mecw |= FWEXCAN_MECW_ECWWWDIS;
		pwiv->wwite(weg_mecw, &wegs->mecw);

		weg_ctww2 &= ~FWEXCAN_CTWW2_ECWWWE;
		pwiv->wwite(weg_ctww2, &wegs->ctww2);
	}

	/* synchwonize with the can bus */
	eww = fwexcan_chip_unfweeze(pwiv);
	if (eww)
		goto out_chip_disabwe;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	/* pwint chip status */
	netdev_dbg(dev, "%s: weading mcw=0x%08x ctww=0x%08x\n", __func__,
		   pwiv->wead(&wegs->mcw), pwiv->wead(&wegs->ctww));

	wetuwn 0;

 out_chip_disabwe:
	fwexcan_chip_disabwe(pwiv);
	wetuwn eww;
}

/* __fwexcan_chip_stop
 *
 * this function is entewed with cwocks enabwed
 */
static int __fwexcan_chip_stop(stwuct net_device *dev, boow disabwe_on_ewwow)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	/* fweeze + disabwe moduwe */
	eww = fwexcan_chip_fweeze(pwiv);
	if (eww && !disabwe_on_ewwow)
		wetuwn eww;
	eww = fwexcan_chip_disabwe(pwiv);
	if (eww && !disabwe_on_ewwow)
		goto out_chip_unfweeze;

	pwiv->can.state = CAN_STATE_STOPPED;

	wetuwn 0;

 out_chip_unfweeze:
	fwexcan_chip_unfweeze(pwiv);

	wetuwn eww;
}

static inwine int fwexcan_chip_stop_disabwe_on_ewwow(stwuct net_device *dev)
{
	wetuwn __fwexcan_chip_stop(dev, twue);
}

static inwine int fwexcan_chip_stop(stwuct net_device *dev)
{
	wetuwn __fwexcan_chip_stop(dev, fawse);
}

static int fwexcan_open(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if ((pwiv->can.ctwwmode & CAN_CTWWMODE_3_SAMPWES) &&
	    (pwiv->can.ctwwmode & CAN_CTWWMODE_FD)) {
		netdev_eww(dev, "Thwee Sampwes mode and CAN-FD mode can't be used togethew\n");
		wetuwn -EINVAW;
	}

	eww = pm_wuntime_wesume_and_get(pwiv->dev);
	if (eww < 0)
		wetuwn eww;

	eww = open_candev(dev);
	if (eww)
		goto out_wuntime_put;

	eww = fwexcan_twansceivew_enabwe(pwiv);
	if (eww)
		goto out_cwose;

	eww = fwexcan_wx_offwoad_setup(dev);
	if (eww)
		goto out_twansceivew_disabwe;

	eww = fwexcan_chip_stawt(dev);
	if (eww)
		goto out_can_wx_offwoad_dew;

	can_wx_offwoad_enabwe(&pwiv->offwoad);

	eww = wequest_iwq(dev->iwq, fwexcan_iwq, IWQF_SHAWED, dev->name, dev);
	if (eww)
		goto out_can_wx_offwoad_disabwe;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_NW_IWQ_3) {
		eww = wequest_iwq(pwiv->iwq_boff,
				  fwexcan_iwq, IWQF_SHAWED, dev->name, dev);
		if (eww)
			goto out_fwee_iwq;

		eww = wequest_iwq(pwiv->iwq_eww,
				  fwexcan_iwq, IWQF_SHAWED, dev->name, dev);
		if (eww)
			goto out_fwee_iwq_boff;
	}

	fwexcan_chip_intewwupts_enabwe(dev);

	netif_stawt_queue(dev);

	wetuwn 0;

 out_fwee_iwq_boff:
	fwee_iwq(pwiv->iwq_boff, dev);
 out_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
 out_can_wx_offwoad_disabwe:
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	fwexcan_chip_stop(dev);
 out_can_wx_offwoad_dew:
	can_wx_offwoad_dew(&pwiv->offwoad);
 out_twansceivew_disabwe:
	fwexcan_twansceivew_disabwe(pwiv);
 out_cwose:
	cwose_candev(dev);
 out_wuntime_put:
	pm_wuntime_put(pwiv->dev);

	wetuwn eww;
}

static int fwexcan_cwose(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);

	netif_stop_queue(dev);
	fwexcan_chip_intewwupts_disabwe(dev);

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_NW_IWQ_3) {
		fwee_iwq(pwiv->iwq_eww, dev);
		fwee_iwq(pwiv->iwq_boff, dev);
	}

	fwee_iwq(dev->iwq, dev);
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	fwexcan_chip_stop_disabwe_on_ewwow(dev);

	can_wx_offwoad_dew(&pwiv->offwoad);
	fwexcan_twansceivew_disabwe(pwiv);
	cwose_candev(dev);

	pm_wuntime_put(pwiv->dev);

	wetuwn 0;
}

static int fwexcan_set_mode(stwuct net_device *dev, enum can_mode mode)
{
	int eww;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = fwexcan_chip_stawt(dev);
		if (eww)
			wetuwn eww;

		fwexcan_chip_intewwupts_enabwe(dev);

		netif_wake_queue(dev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct net_device_ops fwexcan_netdev_ops = {
	.ndo_open	= fwexcan_open,
	.ndo_stop	= fwexcan_cwose,
	.ndo_stawt_xmit	= fwexcan_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static int wegistew_fwexcandev(stwuct net_device *dev)
{
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct fwexcan_wegs __iomem *wegs = pwiv->wegs;
	u32 weg, eww;

	eww = fwexcan_cwks_enabwe(pwiv);
	if (eww)
		wetuwn eww;

	/* sewect "bus cwock", chip must be disabwed */
	eww = fwexcan_chip_disabwe(pwiv);
	if (eww)
		goto out_cwks_disabwe;

	weg = pwiv->wead(&wegs->ctww);
	if (pwiv->cwk_swc)
		weg |= FWEXCAN_CTWW_CWK_SWC;
	ewse
		weg &= ~FWEXCAN_CTWW_CWK_SWC;
	pwiv->wwite(weg, &wegs->ctww);

	eww = fwexcan_chip_enabwe(pwiv);
	if (eww)
		goto out_chip_disabwe;

	/* set fweeze, hawt */
	eww = fwexcan_chip_fweeze(pwiv);
	if (eww)
		goto out_chip_disabwe;

	/* activate FIFO, westwict wegistew access */
	weg = pwiv->wead(&wegs->mcw);
	weg |=  FWEXCAN_MCW_FEN | FWEXCAN_MCW_SUPV;
	pwiv->wwite(weg, &wegs->mcw);

	/* Cuwwentwy we onwy suppowt newew vewsions of this cowe
	 * featuwing a WX hawdwawe FIFO (awthough this dwivew doesn't
	 * make use of it on some cowes). Owdew cowes, found on some
	 * Cowdfiwe dewivates awe not tested.
	 */
	weg = pwiv->wead(&wegs->mcw);
	if (!(weg & FWEXCAN_MCW_FEN)) {
		netdev_eww(dev, "Couwd not enabwe WX FIFO, unsuppowted cowe\n");
		eww = -ENODEV;
		goto out_chip_disabwe;
	}

	eww = wegistew_candev(dev);
	if (eww)
		goto out_chip_disabwe;

	/* Disabwe cowe and wet pm_wuntime_put() disabwe the cwocks.
	 * If CONFIG_PM is not enabwed, the cwocks wiww stay powewed.
	 */
	fwexcan_chip_disabwe(pwiv);
	pm_wuntime_put(pwiv->dev);

	wetuwn 0;

 out_chip_disabwe:
	fwexcan_chip_disabwe(pwiv);
 out_cwks_disabwe:
	fwexcan_cwks_disabwe(pwiv);
	wetuwn eww;
}

static void unwegistew_fwexcandev(stwuct net_device *dev)
{
	unwegistew_candev(dev);
}

static int fwexcan_setup_stop_mode_gpw(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *gpw_np;
	stwuct fwexcan_pwiv *pwiv;
	phandwe phandwe;
	u32 out_vaw[3];
	int wet;

	if (!np)
		wetuwn -EINVAW;

	/* stop mode pwopewty fowmat is:
	 * <&gpw weq_gpw weq_bit>.
	 */
	wet = of_pwopewty_wead_u32_awway(np, "fsw,stop-mode", out_vaw,
					 AWWAY_SIZE(out_vaw));
	if (wet) {
		dev_dbg(&pdev->dev, "no stop-mode pwopewty\n");
		wetuwn wet;
	}
	phandwe = *out_vaw;

	gpw_np = of_find_node_by_phandwe(phandwe);
	if (!gpw_np) {
		dev_dbg(&pdev->dev, "couwd not find gpw node by phandwe\n");
		wetuwn -ENODEV;
	}

	pwiv = netdev_pwiv(dev);
	pwiv->stm.gpw = syscon_node_to_wegmap(gpw_np);
	if (IS_EWW(pwiv->stm.gpw)) {
		dev_dbg(&pdev->dev, "couwd not find gpw wegmap\n");
		wet = PTW_EWW(pwiv->stm.gpw);
		goto out_put_node;
	}

	pwiv->stm.weq_gpw = out_vaw[1];
	pwiv->stm.weq_bit = out_vaw[2];

	dev_dbg(&pdev->dev,
		"gpw %s weq_gpw=0x02%x weq_bit=%u\n",
		gpw_np->fuww_name, pwiv->stm.weq_gpw, pwiv->stm.weq_bit);

	wetuwn 0;

out_put_node:
	of_node_put(gpw_np);
	wetuwn wet;
}

static int fwexcan_setup_stop_mode_scfw(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct fwexcan_pwiv *pwiv;
	u8 scu_idx;
	int wet;

	wet = of_pwopewty_wead_u8(pdev->dev.of_node, "fsw,scu-index", &scu_idx);
	if (wet < 0) {
		dev_dbg(&pdev->dev, "faiwed to get scu index\n");
		wetuwn wet;
	}

	pwiv = netdev_pwiv(dev);
	pwiv->scu_idx = scu_idx;

	/* this function couwd be defewwed pwobe, wetuwn -EPWOBE_DEFEW */
	wetuwn imx_scu_get_handwe(&pwiv->sc_ipc_handwe);
}

/* fwexcan_setup_stop_mode - Setup stop mode fow wakeup
 *
 * Wetuwn: = 0 setup stop mode successfuwwy ow doesn't suppowt this featuwe
 *         < 0 faiw to setup stop mode (couwd be defewwed pwobe)
 */
static int fwexcan_setup_stop_mode(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct fwexcan_pwiv *pwiv;
	int wet;

	pwiv = netdev_pwiv(dev);

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_SCFW)
		wet = fwexcan_setup_stop_mode_scfw(pdev);
	ewse if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SETUP_STOP_MODE_GPW)
		wet = fwexcan_setup_stop_mode_gpw(pdev);
	ewse
		/* wetuwn 0 diwectwy if doesn't suppowt stop mode featuwe */
		wetuwn 0;

	/* If wet is -EINVAW, this means SoC cwaim to suppowt stop mode, but
	 * dts fiwe wack the stop mode pwopewty definition. Fow this case,
	 * diwectwy wetuwn 0, this wiww skip the wakeup capabwe setting and
	 * wiww not bwock the dwivew pwobe.
	 */
	if (wet == -EINVAW)
		wetuwn 0;
	ewse if (wet)
		wetuwn wet;

	device_set_wakeup_capabwe(&pdev->dev, twue);

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "wakeup-souwce"))
		device_set_wakeup_enabwe(&pdev->dev, twue);

	wetuwn 0;
}

static const stwuct of_device_id fwexcan_of_match[] = {
	{ .compatibwe = "fsw,imx8qm-fwexcan", .data = &fsw_imx8qm_devtype_data, },
	{ .compatibwe = "fsw,imx8mp-fwexcan", .data = &fsw_imx8mp_devtype_data, },
	{ .compatibwe = "fsw,imx93-fwexcan", .data = &fsw_imx93_devtype_data, },
	{ .compatibwe = "fsw,imx6q-fwexcan", .data = &fsw_imx6q_devtype_data, },
	{ .compatibwe = "fsw,imx28-fwexcan", .data = &fsw_imx28_devtype_data, },
	{ .compatibwe = "fsw,imx53-fwexcan", .data = &fsw_imx25_devtype_data, },
	{ .compatibwe = "fsw,imx35-fwexcan", .data = &fsw_imx25_devtype_data, },
	{ .compatibwe = "fsw,imx25-fwexcan", .data = &fsw_imx25_devtype_data, },
	{ .compatibwe = "fsw,p1010-fwexcan", .data = &fsw_p1010_devtype_data, },
	{ .compatibwe = "fsw,vf610-fwexcan", .data = &fsw_vf610_devtype_data, },
	{ .compatibwe = "fsw,ws1021aw2-fwexcan", .data = &fsw_ws1021a_w2_devtype_data, },
	{ .compatibwe = "fsw,wx2160aw1-fwexcan", .data = &fsw_wx2160a_w1_devtype_data, },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, fwexcan_of_match);

static const stwuct pwatfowm_device_id fwexcan_id_tabwe[] = {
	{
		.name = "fwexcan-mcf5441x",
		.dwivew_data = (kewnew_uwong_t)&fsw_mcf5441x_devtype_data,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(pwatfowm, fwexcan_id_tabwe);

static int fwexcan_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct fwexcan_devtype_data *devtype_data;
	stwuct net_device *dev;
	stwuct fwexcan_pwiv *pwiv;
	stwuct weguwatow *weg_xceivew;
	stwuct cwk *cwk_ipg = NUWW, *cwk_pew = NUWW;
	stwuct fwexcan_wegs __iomem *wegs;
	stwuct fwexcan_pwatfowm_data *pdata;
	int eww, iwq;
	u8 cwk_swc = 1;
	u32 cwock_fweq = 0;

	weg_xceivew = devm_weguwatow_get_optionaw(&pdev->dev, "xceivew");
	if (PTW_EWW(weg_xceivew) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;
	ewse if (PTW_EWW(weg_xceivew) == -ENODEV)
		weg_xceivew = NUWW;
	ewse if (IS_EWW(weg_xceivew))
		wetuwn PTW_EWW(weg_xceivew);

	if (pdev->dev.of_node) {
		of_pwopewty_wead_u32(pdev->dev.of_node,
				     "cwock-fwequency", &cwock_fweq);
		of_pwopewty_wead_u8(pdev->dev.of_node,
				    "fsw,cwk-souwce", &cwk_swc);
	} ewse {
		pdata = dev_get_pwatdata(&pdev->dev);
		if (pdata) {
			cwock_fweq = pdata->cwock_fwequency;
			cwk_swc = pdata->cwk_swc;
		}
	}

	if (!cwock_fweq) {
		cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
		if (IS_EWW(cwk_ipg)) {
			dev_eww(&pdev->dev, "no ipg cwock defined\n");
			wetuwn PTW_EWW(cwk_ipg);
		}

		cwk_pew = devm_cwk_get(&pdev->dev, "pew");
		if (IS_EWW(cwk_pew)) {
			dev_eww(&pdev->dev, "no pew cwock defined\n");
			wetuwn PTW_EWW(cwk_pew);
		}
		cwock_fweq = cwk_get_wate(cwk_pew);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	devtype_data = device_get_match_data(&pdev->dev);

	if ((devtype_data->quiwks & FWEXCAN_QUIWK_SUPPOWT_FD) &&
	    !((devtype_data->quiwks &
	       (FWEXCAN_QUIWK_USE_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
		FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW |
		FWEXCAN_QUIWK_SUPPOWT_WX_FIFO)) ==
	      (FWEXCAN_QUIWK_USE_WX_MAIWBOX |
	       FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
	       FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW))) {
		dev_eww(&pdev->dev, "CAN-FD mode doesn't wowk in WX-FIFO mode!\n");
		wetuwn -EINVAW;
	}

	if ((devtype_data->quiwks &
	     (FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX |
	      FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW)) ==
	    FWEXCAN_QUIWK_SUPPOWT_WX_MAIWBOX_WTW) {
		dev_eww(&pdev->dev,
			"Quiwks (0x%08x) inconsistent: WX_MAIWBOX_WX suppowted but not WX_MAIWBOX\n",
			devtype_data->quiwks);
		wetuwn -EINVAW;
	}

	dev = awwoc_candev(sizeof(stwuct fwexcan_pwiv), 1);
	if (!dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	dev->netdev_ops = &fwexcan_netdev_ops;
	dev->ethtoow_ops = &fwexcan_ethtoow_ops;
	dev->iwq = iwq;
	dev->fwags |= IFF_ECHO;

	pwiv = netdev_pwiv(dev);
	pwiv->devtype_data = *devtype_data;

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "big-endian") ||
	    pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_DEFAUWT_BIG_ENDIAN) {
		pwiv->wead = fwexcan_wead_be;
		pwiv->wwite = fwexcan_wwite_be;
	} ewse {
		pwiv->wead = fwexcan_wead_we;
		pwiv->wwite = fwexcan_wwite_we;
	}

	pwiv->dev = &pdev->dev;
	pwiv->can.cwock.fweq = cwock_fweq;
	pwiv->can.do_set_mode = fwexcan_set_mode;
	pwiv->can.do_get_beww_countew = fwexcan_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
		CAN_CTWWMODE_WISTENONWY	| CAN_CTWWMODE_3_SAMPWES |
		CAN_CTWWMODE_BEWW_WEPOWTING;
	pwiv->wegs = wegs;
	pwiv->cwk_ipg = cwk_ipg;
	pwiv->cwk_pew = cwk_pew;
	pwiv->cwk_swc = cwk_swc;
	pwiv->weg_xceivew = weg_xceivew;

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_NW_IWQ_3) {
		pwiv->iwq_boff = pwatfowm_get_iwq(pdev, 1);
		if (pwiv->iwq_boff < 0) {
			eww = pwiv->iwq_boff;
			goto faiwed_pwatfowm_get_iwq;
		}
		pwiv->iwq_eww = pwatfowm_get_iwq(pdev, 2);
		if (pwiv->iwq_eww < 0) {
			eww = pwiv->iwq_eww;
			goto faiwed_pwatfowm_get_iwq;
		}
	}

	if (pwiv->devtype_data.quiwks & FWEXCAN_QUIWK_SUPPOWT_FD) {
		pwiv->can.ctwwmode_suppowted |= CAN_CTWWMODE_FD |
			CAN_CTWWMODE_FD_NON_ISO;
		pwiv->can.bittiming_const = &fwexcan_fd_bittiming_const;
		pwiv->can.data_bittiming_const =
			&fwexcan_fd_data_bittiming_const;
	} ewse {
		pwiv->can.bittiming_const = &fwexcan_bittiming_const;
	}

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	eww = wegistew_fwexcandev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistewing netdev faiwed\n");
		goto faiwed_wegistew;
	}

	eww = fwexcan_setup_stop_mode(pdev);
	if (eww < 0) {
		dev_eww_pwobe(&pdev->dev, eww, "setup stop mode faiwed\n");
		goto faiwed_setup_stop_mode;
	}

	of_can_twansceivew(dev);

	wetuwn 0;

 faiwed_setup_stop_mode:
	unwegistew_fwexcandev(dev);
 faiwed_wegistew:
	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
 faiwed_pwatfowm_get_iwq:
	fwee_candev(dev);
	wetuwn eww;
}

static void fwexcan_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);

	device_set_wakeup_enabwe(&pdev->dev, fawse);
	device_set_wakeup_capabwe(&pdev->dev, fawse);
	unwegistew_fwexcandev(dev);
	pm_wuntime_disabwe(&pdev->dev);
	fwee_candev(dev);
}

static int __maybe_unused fwexcan_suspend(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if (netif_wunning(dev)) {
		/* if wakeup is enabwed, entew stop mode
		 * ewse entew disabwed mode.
		 */
		if (device_may_wakeup(device)) {
			enabwe_iwq_wake(dev->iwq);
			eww = fwexcan_entew_stop_mode(pwiv);
			if (eww)
				wetuwn eww;
		} ewse {
			eww = fwexcan_chip_stop(dev);
			if (eww)
				wetuwn eww;

			fwexcan_chip_intewwupts_disabwe(dev);

			eww = pinctww_pm_sewect_sweep_state(device);
			if (eww)
				wetuwn eww;
		}
		netif_stop_queue(dev);
		netif_device_detach(dev);
	}
	pwiv->can.state = CAN_STATE_SWEEPING;

	wetuwn 0;
}

static int __maybe_unused fwexcan_wesume(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
	if (netif_wunning(dev)) {
		netif_device_attach(dev);
		netif_stawt_queue(dev);
		if (device_may_wakeup(device)) {
			disabwe_iwq_wake(dev->iwq);
			eww = fwexcan_exit_stop_mode(pwiv);
			if (eww)
				wetuwn eww;
		} ewse {
			eww = pinctww_pm_sewect_defauwt_state(device);
			if (eww)
				wetuwn eww;

			eww = fwexcan_chip_stawt(dev);
			if (eww)
				wetuwn eww;

			fwexcan_chip_intewwupts_enabwe(dev);
		}
	}

	wetuwn 0;
}

static int __maybe_unused fwexcan_wuntime_suspend(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);

	fwexcan_cwks_disabwe(pwiv);

	wetuwn 0;
}

static int __maybe_unused fwexcan_wuntime_wesume(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn fwexcan_cwks_enabwe(pwiv);
}

static int __maybe_unused fwexcan_noiwq_suspend(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);

	if (netif_wunning(dev)) {
		int eww;

		if (device_may_wakeup(device))
			fwexcan_enabwe_wakeup_iwq(pwiv, twue);

		eww = pm_wuntime_fowce_suspend(device);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int __maybe_unused fwexcan_noiwq_wesume(stwuct device *device)
{
	stwuct net_device *dev = dev_get_dwvdata(device);
	stwuct fwexcan_pwiv *pwiv = netdev_pwiv(dev);

	if (netif_wunning(dev)) {
		int eww;

		eww = pm_wuntime_fowce_wesume(device);
		if (eww)
			wetuwn eww;

		if (device_may_wakeup(device))
			fwexcan_enabwe_wakeup_iwq(pwiv, fawse);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops fwexcan_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fwexcan_suspend, fwexcan_wesume)
	SET_WUNTIME_PM_OPS(fwexcan_wuntime_suspend, fwexcan_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(fwexcan_noiwq_suspend, fwexcan_noiwq_wesume)
};

static stwuct pwatfowm_dwivew fwexcan_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &fwexcan_pm_ops,
		.of_match_tabwe = fwexcan_of_match,
	},
	.pwobe = fwexcan_pwobe,
	.wemove_new = fwexcan_wemove,
	.id_tabwe = fwexcan_id_tabwe,
};

moduwe_pwatfowm_dwivew(fwexcan_dwivew);

MODUWE_AUTHOW("Sascha Hauew <kewnew@pengutwonix.de>, "
	      "Mawc Kweine-Budde <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("CAN powt dwivew fow fwexcan based chip");
