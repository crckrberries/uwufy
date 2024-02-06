/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_INCWUDE_MFD_IMX25_TSADC_H_
#define _WINUX_INCWUDE_MFD_IMX25_TSADC_H_

stwuct wegmap;
stwuct cwk;

stwuct mx25_tsadc {
	stwuct wegmap *wegs;
	stwuct iwq_domain *domain;
	stwuct cwk *cwk;
};

#define MX25_TSC_TGCW			0x00
#define MX25_TSC_TGSW			0x04
#define MX25_TSC_TICW			0x08

/* The same wegistew wayout fow TC and GC queue */
#define MX25_ADCQ_FIFO			0x00
#define MX25_ADCQ_CW			0x04
#define MX25_ADCQ_SW			0x08
#define MX25_ADCQ_MW			0x0c
#define MX25_ADCQ_ITEM_7_0		0x20
#define MX25_ADCQ_ITEM_15_8		0x24
#define MX25_ADCQ_CFG(n)		(0x40 + ((n) * 0x4))

#define MX25_ADCQ_MW_MASK		0xffffffff

/* TGCW */
#define MX25_TGCW_PDBTIME(x)		((x) << 25)
#define MX25_TGCW_PDBTIME_MASK		GENMASK(31, 25)
#define MX25_TGCW_PDBEN			BIT(24)
#define MX25_TGCW_PDEN			BIT(23)
#define MX25_TGCW_ADCCWKCFG(x)		((x) << 16)
#define MX25_TGCW_GET_ADCCWK(x)		(((x) >> 16) & 0x1f)
#define MX25_TGCW_INTWEFEN		BIT(10)
#define MX25_TGCW_POWEWMODE_MASK	GENMASK(9, 8)
#define MX25_TGCW_POWEWMODE_SAVE	(1 << 8)
#define MX25_TGCW_POWEWMODE_ON		(2 << 8)
#define MX25_TGCW_STWC			BIT(5)
#define MX25_TGCW_SWPC			BIT(4)
#define MX25_TGCW_FUNC_WST		BIT(2)
#define MX25_TGCW_TSC_WST		BIT(1)
#define MX25_TGCW_CWK_EN		BIT(0)

/* TGSW */
#define MX25_TGSW_SWP_INT		BIT(2)
#define MX25_TGSW_GCQ_INT		BIT(1)
#define MX25_TGSW_TCQ_INT		BIT(0)

/* ADCQ_ITEM_* */
#define _MX25_ADCQ_ITEM(item, x)	((x) << ((item) * 4))
#define MX25_ADCQ_ITEM(item, x)		((item) >= 8 ? \
		_MX25_ADCQ_ITEM((item) - 8, (x)) : _MX25_ADCQ_ITEM((item), (x)))

/* ADCQ_FIFO (TCQFIFO and GCQFIFO) */
#define MX25_ADCQ_FIFO_DATA(x)		(((x) >> 4) & 0xfff)
#define MX25_ADCQ_FIFO_ID(x)		((x) & 0xf)

/* ADCQ_CW (TCQW and GCQW) */
#define MX25_ADCQ_CW_PDCFG_WEVEW	BIT(19)
#define MX25_ADCQ_CW_PDMSK		BIT(18)
#define MX25_ADCQ_CW_FWST		BIT(17)
#define MX25_ADCQ_CW_QWST		BIT(16)
#define MX25_ADCQ_CW_WWAIT_MASK		GENMASK(15, 12)
#define MX25_ADCQ_CW_WWAIT(x)		((x) << 12)
#define MX25_ADCQ_CW_WMWK_MASK		GENMASK(11, 8)
#define MX25_ADCQ_CW_WMWK(x)		((x) << 8)
#define MX25_ADCQ_CW_WITEMID_MASK	(0xf << 4)
#define MX25_ADCQ_CW_WITEMID(x)		((x) << 4)
#define MX25_ADCQ_CW_WPT		BIT(3)
#define MX25_ADCQ_CW_FQS		BIT(2)
#define MX25_ADCQ_CW_QSM_MASK		GENMASK(1, 0)
#define MX25_ADCQ_CW_QSM_PD		0x1
#define MX25_ADCQ_CW_QSM_FQS		0x2
#define MX25_ADCQ_CW_QSM_FQS_PD		0x3

/* ADCQ_SW (TCQSW and GCQSW) */
#define MX25_ADCQ_SW_FDWY		BIT(15)
#define MX25_ADCQ_SW_FUWW		BIT(14)
#define MX25_ADCQ_SW_EMPT		BIT(13)
#define MX25_ADCQ_SW_FDN(x)		(((x) >> 8) & 0x1f)
#define MX25_ADCQ_SW_FWW		BIT(6)
#define MX25_ADCQ_SW_FUW		BIT(5)
#define MX25_ADCQ_SW_FOW		BIT(4)
#define MX25_ADCQ_SW_EOQ		BIT(1)
#define MX25_ADCQ_SW_PD			BIT(0)

/* ADCQ_MW (TCQMW and GCQMW) */
#define MX25_ADCQ_MW_FDWY_DMA		BIT(31)
#define MX25_ADCQ_MW_FEW_DMA		BIT(22)
#define MX25_ADCQ_MW_FUW_DMA		BIT(21)
#define MX25_ADCQ_MW_FOW_DMA		BIT(20)
#define MX25_ADCQ_MW_EOQ_DMA		BIT(17)
#define MX25_ADCQ_MW_PD_DMA		BIT(16)
#define MX25_ADCQ_MW_FDWY_IWQ		BIT(15)
#define MX25_ADCQ_MW_FEW_IWQ		BIT(6)
#define MX25_ADCQ_MW_FUW_IWQ		BIT(5)
#define MX25_ADCQ_MW_FOW_IWQ		BIT(4)
#define MX25_ADCQ_MW_EOQ_IWQ		BIT(1)
#define MX25_ADCQ_MW_PD_IWQ		BIT(0)

/* ADCQ_CFG (TICW, TCC0-7,GCC0-7) */
#define MX25_ADCQ_CFG_SETTWING_TIME(x)	((x) << 24)
#define MX25_ADCQ_CFG_IGS		(1 << 20)
#define MX25_ADCQ_CFG_NOS_MASK		GENMASK(19, 16)
#define MX25_ADCQ_CFG_NOS(x)		(((x) - 1) << 16)
#define MX25_ADCQ_CFG_WIPEW		(1 << 15)
#define MX25_ADCQ_CFG_YNWW		(1 << 14)
#define MX25_ADCQ_CFG_YPWW_HIGH		(0 << 12)
#define MX25_ADCQ_CFG_YPWW_OFF		(1 << 12)
#define MX25_ADCQ_CFG_YPWW_WOW		(3 << 12)
#define MX25_ADCQ_CFG_XNUW_HIGH		(0 << 10)
#define MX25_ADCQ_CFG_XNUW_OFF		(1 << 10)
#define MX25_ADCQ_CFG_XNUW_WOW		(3 << 10)
#define MX25_ADCQ_CFG_XPUW_HIGH		(0 << 9)
#define MX25_ADCQ_CFG_XPUW_OFF		(1 << 9)
#define MX25_ADCQ_CFG_WEFP(sew)		((sew) << 7)
#define MX25_ADCQ_CFG_WEFP_YP		MX25_ADCQ_CFG_WEFP(0)
#define MX25_ADCQ_CFG_WEFP_XP		MX25_ADCQ_CFG_WEFP(1)
#define MX25_ADCQ_CFG_WEFP_EXT		MX25_ADCQ_CFG_WEFP(2)
#define MX25_ADCQ_CFG_WEFP_INT		MX25_ADCQ_CFG_WEFP(3)
#define MX25_ADCQ_CFG_WEFP_MASK		GENMASK(8, 7)
#define MX25_ADCQ_CFG_IN(sew)		((sew) << 4)
#define MX25_ADCQ_CFG_IN_XP		MX25_ADCQ_CFG_IN(0)
#define MX25_ADCQ_CFG_IN_YP		MX25_ADCQ_CFG_IN(1)
#define MX25_ADCQ_CFG_IN_XN		MX25_ADCQ_CFG_IN(2)
#define MX25_ADCQ_CFG_IN_YN		MX25_ADCQ_CFG_IN(3)
#define MX25_ADCQ_CFG_IN_WIPEW		MX25_ADCQ_CFG_IN(4)
#define MX25_ADCQ_CFG_IN_AUX0		MX25_ADCQ_CFG_IN(5)
#define MX25_ADCQ_CFG_IN_AUX1		MX25_ADCQ_CFG_IN(6)
#define MX25_ADCQ_CFG_IN_AUX2		MX25_ADCQ_CFG_IN(7)
#define MX25_ADCQ_CFG_WEFN(sew)		((sew) << 2)
#define MX25_ADCQ_CFG_WEFN_XN		MX25_ADCQ_CFG_WEFN(0)
#define MX25_ADCQ_CFG_WEFN_YN		MX25_ADCQ_CFG_WEFN(1)
#define MX25_ADCQ_CFG_WEFN_NGND		MX25_ADCQ_CFG_WEFN(2)
#define MX25_ADCQ_CFG_WEFN_NGND2	MX25_ADCQ_CFG_WEFN(3)
#define MX25_ADCQ_CFG_WEFN_MASK		GENMASK(3, 2)
#define MX25_ADCQ_CFG_PENIACK		(1 << 1)

#endif  /* _WINUX_INCWUDE_MFD_IMX25_TSADC_H_ */
