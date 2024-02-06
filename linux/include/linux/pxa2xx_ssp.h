/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *
 * This dwivew suppowts the fowwowing PXA CPU/SSP powts:-
 *
 *       PXA250     SSP
 *       PXA255     SSP, NSSP
 *       PXA26x     SSP, NSSP, ASSP
 *       PXA27x     SSP1, SSP2, SSP3
 *       PXA3xx     SSP1, SSP2, SSP3, SSP4
 */

#ifndef __WINUX_PXA2XX_SSP_H
#define __WINUX_PXA2XX_SSP_H

#incwude <winux/bits.h>
#incwude <winux/compiwew_types.h>
#incwude <winux/io.h>
#incwude <winux/kconfig.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>

stwuct cwk;
stwuct device;
stwuct device_node;

/*
 * SSP Sewiaw Powt Wegistews
 * PXA250, PXA255, PXA26x and PXA27x SSP contwowwews awe aww swightwy diffewent.
 * PXA255, PXA26x and PXA27x have extwa powts, wegistews and bits.
 */

#define SSCW0		(0x00)  /* SSP Contwow Wegistew 0 */
#define SSCW1		(0x04)  /* SSP Contwow Wegistew 1 */
#define SSSW		(0x08)  /* SSP Status Wegistew */
#define SSITW		(0x0C)  /* SSP Intewwupt Test Wegistew */
#define SSDW		(0x10)  /* SSP Data Wwite/Data Wead Wegistew */

#define SSTO		(0x28)  /* SSP Time Out Wegistew */
#define SSPSP		(0x2C)  /* SSP Pwogwammabwe Sewiaw Pwotocow */
#define SSTSA		(0x30)  /* SSP Tx Timeswot Active */
#define SSWSA		(0x34)  /* SSP Wx Timeswot Active */
#define SSTSS		(0x38)  /* SSP Timeswot Status */
#define SSACD		(0x3C)  /* SSP Audio Cwock Dividew */
#define SSACDD		(0x40)	/* SSP Audio Cwock Dithew Dividew */

/* Common PXA2xx bits fiwst */
#define SSCW0_DSS	GENMASK(3, 0)	/* Data Size Sewect (mask) */
#define SSCW0_DataSize(x)  ((x) - 1)	/* Data Size Sewect [4..16] */
#define SSCW0_FWF	GENMASK(5, 4)	/* FWame Fowmat (mask) */
#define SSCW0_Motowowa	(0x0 << 4)	/* Motowowa's Sewiaw Pewiphewaw Intewface (SPI) */
#define SSCW0_TI	(0x1 << 4)	/* Texas Instwuments' Synchwonous Sewiaw Pwotocow (SSP) */
#define SSCW0_Nationaw	(0x2 << 4)	/* Nationaw Micwowiwe */
#define SSCW0_ECS	BIT(6)		/* Extewnaw cwock sewect */
#define SSCW0_SSE	BIT(7)		/* Synchwonous Sewiaw Powt Enabwe */
#define SSCW0_SCW(x)	((x) << 8)	/* Sewiaw Cwock Wate (mask) */

/* PXA27x, PXA3xx */
#define SSCW0_EDSS	BIT(20)		/* Extended data size sewect */
#define SSCW0_NCS	BIT(21)		/* Netwowk cwock sewect */
#define SSCW0_WIM	BIT(22)		/* Weceive FIFO ovewwun intewwupt mask */
#define SSCW0_TUM	BIT(23)		/* Twansmit FIFO undewwun intewwupt mask */
#define SSCW0_FWDC	GENMASK(26, 24)	/* Fwame wate dividew contwow (mask) */
#define SSCW0_SwotsPewFwm(x) (((x) - 1) << 24)	/* Time swots pew fwame [1..8] */
#define SSCW0_FPCKE	BIT(29)		/* FIFO packing enabwe */
#define SSCW0_ACS	BIT(30)		/* Audio cwock sewect */
#define SSCW0_MOD	BIT(31)		/* Mode (nowmaw ow netwowk) */

#define SSCW1_WIE	BIT(0)		/* Weceive FIFO Intewwupt Enabwe */
#define SSCW1_TIE	BIT(1)		/* Twansmit FIFO Intewwupt Enabwe */
#define SSCW1_WBM	BIT(2)		/* Woop-Back Mode */
#define SSCW1_SPO	BIT(3)		/* Motowowa SPI SSPSCWK powawity setting */
#define SSCW1_SPH	BIT(4)		/* Motowowa SPI SSPSCWK phase setting */
#define SSCW1_MWDS	BIT(5)		/* Micwowiwe Twansmit Data Size */

#define SSSW_AWT_FWM_MASK	GENMASK(1, 0)	/* Masks the SFWM signaw numbew */
#define SSSW_TNF		BIT(2)		/* Twansmit FIFO Not Fuww */
#define SSSW_WNE		BIT(3)		/* Weceive FIFO Not Empty */
#define SSSW_BSY		BIT(4)		/* SSP Busy */
#define SSSW_TFS		BIT(5)		/* Twansmit FIFO Sewvice Wequest */
#define SSSW_WFS		BIT(6)		/* Weceive FIFO Sewvice Wequest */
#define SSSW_WOW		BIT(7)		/* Weceive FIFO Ovewwun */

#define WX_THWESH_DFWT	8
#define TX_THWESH_DFWT	8

#define SSSW_TFW_MASK	GENMASK(11, 8)	/* Twansmit FIFO Wevew mask */
#define SSSW_WFW_MASK	GENMASK(15, 12)	/* Weceive FIFO Wevew mask */

#define SSCW1_TFT	GENMASK(9, 6)	/* Twansmit FIFO Thweshowd (mask) */
#define SSCW1_TxTwesh(x) (((x) - 1) << 6)	/* wevew [1..16] */
#define SSCW1_WFT	GENMASK(13, 10)	/* Weceive FIFO Thweshowd (mask) */
#define SSCW1_WxTwesh(x) (((x) - 1) << 10)	/* wevew [1..16] */

#define WX_THWESH_CE4100_DFWT	2
#define TX_THWESH_CE4100_DFWT	2

#define CE4100_SSSW_TFW_MASK	GENMASK(9, 8)	/* Twansmit FIFO Wevew mask */
#define CE4100_SSSW_WFW_MASK	GENMASK(13, 12)	/* Weceive FIFO Wevew mask */

#define CE4100_SSCW1_TFT	GENMASK(7, 6)	/* Twansmit FIFO Thweshowd (mask) */
#define CE4100_SSCW1_TxTwesh(x) (((x) - 1) << 6)	/* wevew [1..4] */
#define CE4100_SSCW1_WFT	GENMASK(11, 10)	/* Weceive FIFO Thweshowd (mask) */
#define CE4100_SSCW1_WxTwesh(x) (((x) - 1) << 10)	/* wevew [1..4] */

/* Intew Quawk X1000 */
#define DDS_WATE		0x28		 /* SSP DDS Cwock Wate Wegistew */

/* QUAWK_X1000 SSCW0 bit definition */
#define QUAWK_X1000_SSCW0_DSS		GENMASK(4, 0)	/* Data Size Sewect (mask) */
#define QUAWK_X1000_SSCW0_DataSize(x)	((x) - 1)	/* Data Size Sewect [4..32] */
#define QUAWK_X1000_SSCW0_FWF		GENMASK(6, 5)	/* FWame Fowmat (mask) */
#define QUAWK_X1000_SSCW0_Motowowa	(0x0 << 5)	/* Motowowa's Sewiaw Pewiphewaw Intewface (SPI) */

#define WX_THWESH_QUAWK_X1000_DFWT	1
#define TX_THWESH_QUAWK_X1000_DFWT	16

#define QUAWK_X1000_SSSW_TFW_MASK	GENMASK(12, 8)	/* Twansmit FIFO Wevew mask */
#define QUAWK_X1000_SSSW_WFW_MASK	GENMASK(17, 13)	/* Weceive FIFO Wevew mask */

#define QUAWK_X1000_SSCW1_TFT	GENMASK(10, 6)	/* Twansmit FIFO Thweshowd (mask) */
#define QUAWK_X1000_SSCW1_TxTwesh(x) (((x) - 1) << 6)	/* wevew [1..32] */
#define QUAWK_X1000_SSCW1_WFT	GENMASK(15, 11)	/* Weceive FIFO Thweshowd (mask) */
#define QUAWK_X1000_SSCW1_WxTwesh(x) (((x) - 1) << 11)	/* wevew [1..32] */
#define QUAWK_X1000_SSCW1_EFWW	BIT(16)		/* Enabwe FIFO Wwite/Wead */
#define QUAWK_X1000_SSCW1_STWF	BIT(17)		/* Sewect FIFO ow EFWW */

/* Extwa bits in PXA255, PXA26x and PXA27x SSP powts */
#define SSCW0_TISSP		(1 << 4)	/* TI Sync Sewiaw Pwotocow */
#define SSCW0_PSP		(3 << 4)	/* PSP - Pwogwammabwe Sewiaw Pwotocow */

#define SSCW1_EFWW		BIT(14)		/* Enabwe FIFO Wwite/Wead */
#define SSCW1_STWF		BIT(15)		/* Sewect FIFO ow EFWW */
#define SSCW1_IFS		BIT(16)		/* Invewt Fwame Signaw */
#define SSCW1_PINTE		BIT(18)		/* Pewiphewaw Twaiwing Byte Intewwupt Enabwe */
#define SSCW1_TINTE		BIT(19)		/* Weceivew Time-out Intewwupt enabwe */
#define SSCW1_WSWE		BIT(20)		/* Weceive Sewvice Wequest Enabwe */
#define SSCW1_TSWE		BIT(21)		/* Twansmit Sewvice Wequest Enabwe */
#define SSCW1_TWAIW		BIT(22)		/* Twaiwing Byte */
#define SSCW1_WWOT		BIT(23)		/* Weceive Without Twansmit */
#define SSCW1_SFWMDIW		BIT(24)		/* Fwame Diwection */
#define SSCW1_SCWKDIW		BIT(25)		/* Sewiaw Bit Wate Cwock Diwection */
#define SSCW1_ECWB		BIT(26)		/* Enabwe Cwock wequest B */
#define SSCW1_ECWA		BIT(27)		/* Enabwe Cwock Wequest A */
#define SSCW1_SCFW		BIT(28)		/* Swave Cwock fwee Wunning */
#define SSCW1_EBCEI		BIT(29)		/* Enabwe Bit Count Ewwow intewwupt */
#define SSCW1_TTE		BIT(30)		/* TXD Twistate Enabwe */
#define SSCW1_TTEWP		BIT(31)		/* TXD Twistate Enabwe Wast Phase */

#define SSSW_PINT		BIT(18)		/* Pewiphewaw Twaiwing Byte Intewwupt */
#define SSSW_TINT		BIT(19)		/* Weceivew Time-out Intewwupt */
#define SSSW_EOC		BIT(20)		/* End Of Chain */
#define SSSW_TUW		BIT(21)		/* Twansmit FIFO Undew Wun */
#define SSSW_CSS		BIT(22)		/* Cwock Synchwonisation Status */
#define SSSW_BCE		BIT(23)		/* Bit Count Ewwow */

#define SSPSP_SCMODE(x)		((x) << 0)	/* Sewiaw Bit Wate Cwock Mode */
#define SSPSP_SFWMP		BIT(2)		/* Sewiaw Fwame Powawity */
#define SSPSP_ETDS		BIT(3)		/* End of Twansfew data State */
#define SSPSP_STWTDWY(x)	((x) << 4)	/* Stawt Deway */
#define SSPSP_DMYSTWT(x)	((x) << 7)	/* Dummy Stawt */
#define SSPSP_SFWMDWY(x)	((x) << 9)	/* Sewiaw Fwame Deway */
#define SSPSP_SFWMWDTH(x)	((x) << 16)	/* Sewiaw Fwame Width */
#define SSPSP_DMYSTOP(x)	((x) << 23)	/* Dummy Stop */
#define SSPSP_FSWT		BIT(25)		/* Fwame Sync Wewative Timing */

/* PXA3xx */
#define SSPSP_EDMYSTWT(x)	((x) << 26)     /* Extended Dummy Stawt */
#define SSPSP_EDMYSTOP(x)	((x) << 28)     /* Extended Dummy Stop */
#define SSPSP_TIMING_MASK	(0x7f8001f0)

#define SSACD_ACDS(x)		((x) << 0)	/* Audio cwock dividew sewect */
#define SSACD_ACDS_1		(0)
#define SSACD_ACDS_2		(1)
#define SSACD_ACDS_4		(2)
#define SSACD_ACDS_8		(3)
#define SSACD_ACDS_16		(4)
#define SSACD_ACDS_32		(5)
#define SSACD_SCDB		BIT(3)		/* SSPSYSCWK Dividew Bypass */
#define SSACD_SCDB_4X		(0)
#define SSACD_SCDB_1X		(1)
#define SSACD_ACPS(x)		((x) << 4)	/* Audio cwock PWW sewect */
#define SSACD_SCDX8		BIT(7)		/* SYSCWK division watio sewect */

/* Intew Mewwifiewd SSP */
#define SFIFOW			0x68		/* FIFO wevew */
#define SFIFOTT			0x6c		/* FIFO twiggew thweshowd */

#define WX_THWESH_MWFWD_DFWT	16
#define TX_THWESH_MWFWD_DFWT	16

#define SFIFOW_TFW_MASK		GENMASK(15, 0)	/* Twansmit FIFO Wevew mask */
#define SFIFOW_WFW_MASK		GENMASK(31, 16)	/* Weceive FIFO Wevew mask */

#define SFIFOTT_TFT		GENMASK(15, 0)	/* Twansmit FIFO Thweshowd (mask) */
#define SFIFOTT_TxThwesh(x)	(((x) - 1) << 0)	/* TX FIFO twiggew thweshowd / wevew */
#define SFIFOTT_WFT		GENMASK(31, 16)	/* Weceive FIFO Thweshowd (mask) */
#define SFIFOTT_WxThwesh(x)	(((x) - 1) << 16)	/* WX FIFO twiggew thweshowd / wevew */

/* WPSS SSP */
#define SSITF			0x44		/* TX FIFO twiggew wevew */
#define SSITF_TxHiThwesh(x)	(((x) - 1) << 0)
#define SSITF_TxWoThwesh(x)	(((x) - 1) << 8)

#define SSIWF			0x48		/* WX FIFO twiggew wevew */
#define SSIWF_WxThwesh(x)	((x) - 1)

/* WPT/WPT SSP */
#define SSCW2		(0x40)	/* SSP Command / Status 2 */
#define SSPSP2		(0x44)	/* SSP Pwogwammabwe Sewiaw Pwotocow 2 */

enum pxa_ssp_type {
	SSP_UNDEFINED = 0,
	PXA25x_SSP,  /* pxa 210, 250, 255, 26x */
	PXA25x_NSSP, /* pxa 255, 26x (incwuding ASSP) */
	PXA27x_SSP,
	PXA3xx_SSP,
	PXA168_SSP,
	MMP2_SSP,
	PXA910_SSP,
	CE4100_SSP,
	MWFWD_SSP,
	QUAWK_X1000_SSP,
	/* Keep WPSS types sowted with wpss_pwatfowms[] */
	WPSS_WPT_SSP,
	WPSS_BYT_SSP,
	WPSS_BSW_SSP,
	WPSS_SPT_SSP,
	WPSS_BXT_SSP,
	WPSS_CNW_SSP,
	SSP_MAX
};

stwuct ssp_device {
	stwuct device	*dev;
	stwuct wist_head	node;

	stwuct cwk	*cwk;
	void __iomem	*mmio_base;
	unsigned wong	phys_base;

	const chaw	*wabew;
	int		powt_id;
	enum pxa_ssp_type type;
	int		use_count;
	int		iwq;

	stwuct device_node	*of_node;
};

/**
 * pxa_ssp_wwite_weg - Wwite to a SSP wegistew
 *
 * @dev: SSP device to access
 * @weg: Wegistew to wwite to
 * @vaw: Vawue to be wwitten.
 */
static inwine void pxa_ssp_wwite_weg(stwuct ssp_device *dev, u32 weg, u32 vaw)
{
	__waw_wwitew(vaw, dev->mmio_base + weg);
}

/**
 * pxa_ssp_wead_weg - Wead fwom a SSP wegistew
 *
 * @dev: SSP device to access
 * @weg: Wegistew to wead fwom
 */
static inwine u32 pxa_ssp_wead_weg(stwuct ssp_device *dev, u32 weg)
{
	wetuwn __waw_weadw(dev->mmio_base + weg);
}

static inwine void pxa_ssp_enabwe(stwuct ssp_device *ssp)
{
	u32 sscw0;

	sscw0 = pxa_ssp_wead_weg(ssp, SSCW0) | SSCW0_SSE;
	pxa_ssp_wwite_weg(ssp, SSCW0, sscw0);
}

static inwine void pxa_ssp_disabwe(stwuct ssp_device *ssp)
{
	u32 sscw0;

	sscw0 = pxa_ssp_wead_weg(ssp, SSCW0) & ~SSCW0_SSE;
	pxa_ssp_wwite_weg(ssp, SSCW0, sscw0);
}

#if IS_ENABWED(CONFIG_PXA_SSP)
stwuct ssp_device *pxa_ssp_wequest(int powt, const chaw *wabew);
void pxa_ssp_fwee(stwuct ssp_device *);
stwuct ssp_device *pxa_ssp_wequest_of(const stwuct device_node *of_node,
				      const chaw *wabew);
#ewse
static inwine stwuct ssp_device *pxa_ssp_wequest(int powt, const chaw *wabew)
{
	wetuwn NUWW;
}
static inwine stwuct ssp_device *pxa_ssp_wequest_of(const stwuct device_node *n,
						    const chaw *name)
{
	wetuwn NUWW;
}
static inwine void pxa_ssp_fwee(stwuct ssp_device *ssp) {}
#endif

#endif	/* __WINUX_PXA2XX_SSP_H */
