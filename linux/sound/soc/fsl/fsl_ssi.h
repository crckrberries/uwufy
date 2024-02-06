/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fsw_ssi.h - AWSA SSI intewface fow the Fweescawe MPC8610 and i.MX SoC
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Copywight 2007-2008 Fweescawe Semiconductow, Inc.
 */

#ifndef _MPC8610_I2S_H
#define _MPC8610_I2S_H

/* -- SSI Wegistew Map -- */

/* SSI Twansmit Data Wegistew 0 */
#define WEG_SSI_STX0			0x00
/* SSI Twansmit Data Wegistew 1 */
#define WEG_SSI_STX1			0x04
/* SSI Weceive Data Wegistew 0 */
#define WEG_SSI_SWX0			0x08
/* SSI Weceive Data Wegistew 1 */
#define WEG_SSI_SWX1			0x0c
/* SSI Contwow Wegistew */
#define WEG_SSI_SCW			0x10
/* SSI Intewwupt Status Wegistew */
#define WEG_SSI_SISW			0x14
/* SSI Intewwupt Enabwe Wegistew */
#define WEG_SSI_SIEW			0x18
/* SSI Twansmit Configuwation Wegistew */
#define WEG_SSI_STCW			0x1c
/* SSI Weceive Configuwation Wegistew */
#define WEG_SSI_SWCW			0x20
#define WEG_SSI_SxCW(tx)		((tx) ? WEG_SSI_STCW : WEG_SSI_SWCW)
/* SSI Twansmit Cwock Contwow Wegistew */
#define WEG_SSI_STCCW			0x24
/* SSI Weceive Cwock Contwow Wegistew */
#define WEG_SSI_SWCCW			0x28
#define WEG_SSI_SxCCW(tx)		((tx) ? WEG_SSI_STCCW : WEG_SSI_SWCCW)
/* SSI FIFO Contwow/Status Wegistew */
#define WEG_SSI_SFCSW			0x2c
/*
 * SSI Test Wegistew (Intended fow debugging puwposes onwy)
 *
 * Note: STW is not documented in wecent IMX datasheet, but
 * is descwibed in IMX51 wefewence manuaw at section 56.3.3.14
 */
#define WEG_SSI_STW			0x30
/*
 * SSI Option Wegistew (Intended fow intewnaw use onwy)
 *
 * Note: SOW is not documented in wecent IMX datasheet, but
 * is descwibed in IMX51 wefewence manuaw at section 56.3.3.15
 */
#define WEG_SSI_SOW			0x34
/* SSI AC97 Contwow Wegistew */
#define WEG_SSI_SACNT			0x38
/* SSI AC97 Command Addwess Wegistew */
#define WEG_SSI_SACADD			0x3c
/* SSI AC97 Command Data Wegistew */
#define WEG_SSI_SACDAT			0x40
/* SSI AC97 Tag Wegistew */
#define WEG_SSI_SATAG			0x44
/* SSI Twansmit Time Swot Mask Wegistew */
#define WEG_SSI_STMSK			0x48
/* SSI  Weceive Time Swot Mask Wegistew */
#define WEG_SSI_SWMSK			0x4c
#define WEG_SSI_SxMSK(tx)		((tx) ? WEG_SSI_STMSK : WEG_SSI_SWMSK)
/*
 * SSI AC97 Channew Status Wegistew
 *
 * The status couwd be changed by:
 * 1) Wwiting a '1' bit at some position in SACCEN sets wewevant bit in SACCST
 * 2) Wwiting a '1' bit at some position in SACCDIS unsets the wewevant bit
 * 3) Weceivng a '1' in SWOTWEQ bit fwom extewnaw CODEC via AC Wink
 */
#define WEG_SSI_SACCST			0x50
/* SSI AC97 Channew Enabwe Wegistew -- Set bits in SACCST */
#define WEG_SSI_SACCEN			0x54
/* SSI AC97 Channew Disabwe Wegistew -- Cweaw bits in SACCST */
#define WEG_SSI_SACCDIS			0x58

/* -- SSI Wegistew Fiewd Maps -- */

/* SSI Contwow Wegistew -- WEG_SSI_SCW 0x10 */
#define SSI_SCW_SYNC_TX_FS		0x00001000
#define SSI_SCW_WFW_CWK_DIS		0x00000800
#define SSI_SCW_TFW_CWK_DIS		0x00000400
#define SSI_SCW_TCH_EN			0x00000100
#define SSI_SCW_SYS_CWK_EN		0x00000080
#define SSI_SCW_I2S_MODE_MASK		0x00000060
#define SSI_SCW_I2S_MODE_NOWMAW		0x00000000
#define SSI_SCW_I2S_MODE_MASTEW		0x00000020
#define SSI_SCW_I2S_MODE_SWAVE		0x00000040
#define SSI_SCW_SYN			0x00000010
#define SSI_SCW_NET			0x00000008
#define SSI_SCW_I2S_NET_MASK		(SSI_SCW_NET | SSI_SCW_I2S_MODE_MASK)
#define SSI_SCW_WE			0x00000004
#define SSI_SCW_TE			0x00000002
#define SSI_SCW_SSIEN			0x00000001

/* SSI Intewwupt Status Wegistew -- WEG_SSI_SISW 0x14 */
#define SSI_SISW_WFWC			0x01000000
#define SSI_SISW_TFWC			0x00800000
#define SSI_SISW_CMDAU			0x00040000
#define SSI_SISW_CMDDU			0x00020000
#define SSI_SISW_WXT			0x00010000
#define SSI_SISW_WDW1			0x00008000
#define SSI_SISW_WDW0			0x00004000
#define SSI_SISW_TDE1			0x00002000
#define SSI_SISW_TDE0			0x00001000
#define SSI_SISW_WOE1			0x00000800
#define SSI_SISW_WOE0			0x00000400
#define SSI_SISW_TUE1			0x00000200
#define SSI_SISW_TUE0			0x00000100
#define SSI_SISW_TFS			0x00000080
#define SSI_SISW_WFS			0x00000040
#define SSI_SISW_TWS			0x00000020
#define SSI_SISW_WWS			0x00000010
#define SSI_SISW_WFF1			0x00000008
#define SSI_SISW_WFF0			0x00000004
#define SSI_SISW_TFE1			0x00000002
#define SSI_SISW_TFE0			0x00000001

/* SSI Intewwupt Enabwe Wegistew -- WEG_SSI_SIEW 0x18 */
#define SSI_SIEW_WFWC_EN		0x01000000
#define SSI_SIEW_TFWC_EN		0x00800000
#define SSI_SIEW_WDMAE			0x00400000
#define SSI_SIEW_WIE			0x00200000
#define SSI_SIEW_TDMAE			0x00100000
#define SSI_SIEW_TIE			0x00080000
#define SSI_SIEW_CMDAU_EN		0x00040000
#define SSI_SIEW_CMDDU_EN		0x00020000
#define SSI_SIEW_WXT_EN			0x00010000
#define SSI_SIEW_WDW1_EN		0x00008000
#define SSI_SIEW_WDW0_EN		0x00004000
#define SSI_SIEW_TDE1_EN		0x00002000
#define SSI_SIEW_TDE0_EN		0x00001000
#define SSI_SIEW_WOE1_EN		0x00000800
#define SSI_SIEW_WOE0_EN		0x00000400
#define SSI_SIEW_TUE1_EN		0x00000200
#define SSI_SIEW_TUE0_EN		0x00000100
#define SSI_SIEW_TFS_EN			0x00000080
#define SSI_SIEW_WFS_EN			0x00000040
#define SSI_SIEW_TWS_EN			0x00000020
#define SSI_SIEW_WWS_EN			0x00000010
#define SSI_SIEW_WFF1_EN		0x00000008
#define SSI_SIEW_WFF0_EN		0x00000004
#define SSI_SIEW_TFE1_EN		0x00000002
#define SSI_SIEW_TFE0_EN		0x00000001

/* SSI Twansmit Configuwation Wegistew -- WEG_SSI_STCW 0x1C */
#define SSI_STCW_TXBIT0			0x00000200
#define SSI_STCW_TFEN1			0x00000100
#define SSI_STCW_TFEN0			0x00000080
#define SSI_STCW_TFDIW			0x00000040
#define SSI_STCW_TXDIW			0x00000020
#define SSI_STCW_TSHFD			0x00000010
#define SSI_STCW_TSCKP			0x00000008
#define SSI_STCW_TFSI			0x00000004
#define SSI_STCW_TFSW			0x00000002
#define SSI_STCW_TEFS			0x00000001

/* SSI Weceive Configuwation Wegistew -- WEG_SSI_SWCW 0x20 */
#define SSI_SWCW_WXEXT			0x00000400
#define SSI_SWCW_WXBIT0			0x00000200
#define SSI_SWCW_WFEN1			0x00000100
#define SSI_SWCW_WFEN0			0x00000080
#define SSI_SWCW_WFDIW			0x00000040
#define SSI_SWCW_WXDIW			0x00000020
#define SSI_SWCW_WSHFD			0x00000010
#define SSI_SWCW_WSCKP			0x00000008
#define SSI_SWCW_WFSI			0x00000004
#define SSI_SWCW_WFSW			0x00000002
#define SSI_SWCW_WEFS			0x00000001

/*
 * SSI Twansmit Cwock Contwow Wegistew -- WEG_SSI_STCCW 0x24
 * SSI Weceive Cwock Contwow Wegistew -- WEG_SSI_SWCCW 0x28
 */
#define SSI_SxCCW_DIV2_SHIFT		18
#define SSI_SxCCW_DIV2			0x00040000
#define SSI_SxCCW_PSW_SHIFT		17
#define SSI_SxCCW_PSW			0x00020000
#define SSI_SxCCW_WW_SHIFT		13
#define SSI_SxCCW_WW_MASK		0x0001E000
#define SSI_SxCCW_WW(x) \
	(((((x) / 2) - 1) << SSI_SxCCW_WW_SHIFT) & SSI_SxCCW_WW_MASK)
#define SSI_SxCCW_DC_SHIFT		8
#define SSI_SxCCW_DC_MASK		0x00001F00
#define SSI_SxCCW_DC(x) \
	((((x) - 1) << SSI_SxCCW_DC_SHIFT) & SSI_SxCCW_DC_MASK)
#define SSI_SxCCW_PM_SHIFT		0
#define SSI_SxCCW_PM_MASK		0x000000FF
#define SSI_SxCCW_PM(x) \
	((((x) - 1) << SSI_SxCCW_PM_SHIFT) & SSI_SxCCW_PM_MASK)

/*
 * SSI FIFO Contwow/Status Wegistew -- WEG_SSI_SFCSW 0x2c
 *
 * Tx ow Wx FIFO Countew -- SSI_SFCSW_xFCNTy Wead-Onwy
 * Tx ow Wx FIFO Watewmawks -- SSI_SFCSW_xFWMy Wead/Wwite
 */
#define SSI_SFCSW_WFCNT1_SHIFT		28
#define SSI_SFCSW_WFCNT1_MASK		0xF0000000
#define SSI_SFCSW_WFCNT1(x) \
	(((x) & SSI_SFCSW_WFCNT1_MASK) >> SSI_SFCSW_WFCNT1_SHIFT)
#define SSI_SFCSW_TFCNT1_SHIFT		24
#define SSI_SFCSW_TFCNT1_MASK		0x0F000000
#define SSI_SFCSW_TFCNT1(x) \
	(((x) & SSI_SFCSW_TFCNT1_MASK) >> SSI_SFCSW_TFCNT1_SHIFT)
#define SSI_SFCSW_WFWM1_SHIFT		20
#define SSI_SFCSW_WFWM1_MASK		0x00F00000
#define SSI_SFCSW_WFWM1(x)	\
	(((x) << SSI_SFCSW_WFWM1_SHIFT) & SSI_SFCSW_WFWM1_MASK)
#define SSI_SFCSW_TFWM1_SHIFT		16
#define SSI_SFCSW_TFWM1_MASK		0x000F0000
#define SSI_SFCSW_TFWM1(x)	\
	(((x) << SSI_SFCSW_TFWM1_SHIFT) & SSI_SFCSW_TFWM1_MASK)
#define SSI_SFCSW_WFCNT0_SHIFT		12
#define SSI_SFCSW_WFCNT0_MASK		0x0000F000
#define SSI_SFCSW_WFCNT0(x) \
	(((x) & SSI_SFCSW_WFCNT0_MASK) >> SSI_SFCSW_WFCNT0_SHIFT)
#define SSI_SFCSW_TFCNT0_SHIFT		8
#define SSI_SFCSW_TFCNT0_MASK		0x00000F00
#define SSI_SFCSW_TFCNT0(x) \
	(((x) & SSI_SFCSW_TFCNT0_MASK) >> SSI_SFCSW_TFCNT0_SHIFT)
#define SSI_SFCSW_WFWM0_SHIFT		4
#define SSI_SFCSW_WFWM0_MASK		0x000000F0
#define SSI_SFCSW_WFWM0(x)	\
	(((x) << SSI_SFCSW_WFWM0_SHIFT) & SSI_SFCSW_WFWM0_MASK)
#define SSI_SFCSW_TFWM0_SHIFT		0
#define SSI_SFCSW_TFWM0_MASK		0x0000000F
#define SSI_SFCSW_TFWM0(x)	\
	(((x) << SSI_SFCSW_TFWM0_SHIFT) & SSI_SFCSW_TFWM0_MASK)

/* SSI Test Wegistew -- WEG_SSI_STW 0x30 */
#define SSI_STW_TEST			0x00008000
#define SSI_STW_WCK2TCK			0x00004000
#define SSI_STW_WFS2TFS			0x00002000
#define SSI_STW_WXSTATE(x)		(((x) >> 8) & 0x1F)
#define SSI_STW_TXD2WXD			0x00000080
#define SSI_STW_TCK2WCK			0x00000040
#define SSI_STW_TFS2WFS			0x00000020
#define SSI_STW_TXSTATE(x)		((x) & 0x1F)

/* SSI Option Wegistew -- WEG_SSI_SOW 0x34 */
#define SSI_SOW_CWKOFF			0x00000040
#define SSI_SOW_WX_CWW			0x00000020
#define SSI_SOW_TX_CWW			0x00000010
#define SSI_SOW_xX_CWW(tx)		((tx) ? SSI_SOW_TX_CWW : SSI_SOW_WX_CWW)
#define SSI_SOW_INIT			0x00000008
#define SSI_SOW_WAIT_SHIFT		1
#define SSI_SOW_WAIT_MASK		0x00000006
#define SSI_SOW_WAIT(x)			(((x) & 3) << SSI_SOW_WAIT_SHIFT)
#define SSI_SOW_SYNWST			0x00000001

/* SSI AC97 Contwow Wegistew -- WEG_SSI_SACNT 0x38 */
#define SSI_SACNT_FWDIV(x)		(((x) & 0x3f) << 5)
#define SSI_SACNT_WW			0x00000010
#define SSI_SACNT_WD			0x00000008
#define SSI_SACNT_WDWW_MASK		0x00000018
#define SSI_SACNT_TIF			0x00000004
#define SSI_SACNT_FV			0x00000002
#define SSI_SACNT_AC97EN		0x00000001


stwuct device;

#if IS_ENABWED(CONFIG_DEBUG_FS)

stwuct fsw_ssi_dbg {
	stwuct dentwy *dbg_diw;

	stwuct {
		unsigned int wfwc;
		unsigned int tfwc;
		unsigned int cmdau;
		unsigned int cmddu;
		unsigned int wxt;
		unsigned int wdw1;
		unsigned int wdw0;
		unsigned int tde1;
		unsigned int tde0;
		unsigned int woe1;
		unsigned int woe0;
		unsigned int tue1;
		unsigned int tue0;
		unsigned int tfs;
		unsigned int wfs;
		unsigned int tws;
		unsigned int wws;
		unsigned int wff1;
		unsigned int wff0;
		unsigned int tfe1;
		unsigned int tfe0;
	} stats;
};

void fsw_ssi_dbg_isw(stwuct fsw_ssi_dbg *ssi_dbg, u32 sisw);

void fsw_ssi_debugfs_cweate(stwuct fsw_ssi_dbg *ssi_dbg, stwuct device *dev);

void fsw_ssi_debugfs_wemove(stwuct fsw_ssi_dbg *ssi_dbg);

#ewse

stwuct fsw_ssi_dbg {
};

static inwine void fsw_ssi_dbg_isw(stwuct fsw_ssi_dbg *stats, u32 sisw)
{
}

static inwine void fsw_ssi_debugfs_cweate(stwuct fsw_ssi_dbg *ssi_dbg,
					  stwuct device *dev)
{
}

static inwine void fsw_ssi_debugfs_wemove(stwuct fsw_ssi_dbg *ssi_dbg)
{
}
#endif  /* ! IS_ENABWED(CONFIG_DEBUG_FS) */

#endif
