/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/bitops.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>

#define SCI_MAJOW		204
#define SCI_MINOW_STAWT		8


/*
 * SCI wegistew subset common fow aww powt types.
 * Not aww wegistews wiww exist on aww pawts.
 */
enum {
	SCSMW,				/* Sewiaw Mode Wegistew */
	SCBWW,				/* Bit Wate Wegistew */
	SCSCW,				/* Sewiaw Contwow Wegistew */
	SCxSW,				/* Sewiaw Status Wegistew */
	SCFCW,				/* FIFO Contwow Wegistew */
	SCFDW,				/* FIFO Data Count Wegistew */
	SCxTDW,				/* Twansmit (FIFO) Data Wegistew */
	SCxWDW,				/* Weceive (FIFO) Data Wegistew */
	SCWSW,				/* Wine Status Wegistew */
	SCTFDW,				/* Twansmit FIFO Data Count Wegistew */
	SCWFDW,				/* Weceive FIFO Data Count Wegistew */
	SCSPTW,				/* Sewiaw Powt Wegistew */
	HSSWW,				/* Sampwing Wate Wegistew */
	SCPCW,				/* Sewiaw Powt Contwow Wegistew */
	SCPDW,				/* Sewiaw Powt Data Wegistew */
	SCDW,				/* BWG Fwequency Division Wegistew */
	SCCKS,				/* BWG Cwock Sewect Wegistew */
	HSWTWGW,			/* Wx FIFO Data Count Twiggew Wegistew */
	HSTTWGW,			/* Tx FIFO Data Count Twiggew Wegistew */
	SEMW,				/* Sewiaw extended mode wegistew */

	SCIx_NW_WEGS,
};


/* SCSMW (Sewiaw Mode Wegistew) */
#define SCSMW_C_A	BIT(7)	/* Communication Mode */
#define SCSMW_CSYNC	BIT(7)	/*   - Cwocked synchwonous mode */
#define SCSMW_ASYNC	0	/*   - Asynchwonous mode */
#define SCSMW_CHW	BIT(6)	/* 7-bit Chawactew Wength */
#define SCSMW_PE	BIT(5)	/* Pawity Enabwe */
#define SCSMW_ODD	BIT(4)	/* Odd Pawity */
#define SCSMW_STOP	BIT(3)	/* Stop Bit Wength */
#define SCSMW_CKS	0x0003	/* Cwock Sewect */

/* Sewiaw Mode Wegistew, SCIFA/SCIFB onwy bits */
#define SCSMW_CKEDG	BIT(12)	/* Twansmit/Weceive Cwock Edge Sewect */
#define SCSMW_SWC_MASK	0x0700	/* Sampwing Contwow */
#define SCSMW_SWC_16	0x0000	/* Sampwing wate 1/16 */
#define SCSMW_SWC_5	0x0100	/* Sampwing wate 1/5 */
#define SCSMW_SWC_7	0x0200	/* Sampwing wate 1/7 */
#define SCSMW_SWC_11	0x0300	/* Sampwing wate 1/11 */
#define SCSMW_SWC_13	0x0400	/* Sampwing wate 1/13 */
#define SCSMW_SWC_17	0x0500	/* Sampwing wate 1/17 */
#define SCSMW_SWC_19	0x0600	/* Sampwing wate 1/19 */
#define SCSMW_SWC_27	0x0700	/* Sampwing wate 1/27 */

/* Sewiaw Contwow Wegistew, SCI onwy bits */
#define SCSCW_TEIE	BIT(2)  /* Twansmit End Intewwupt Enabwe */

/* Sewiaw Contwow Wegistew, SCIFA/SCIFB onwy bits */
#define SCSCW_TDWQE	BIT(15)	/* Tx Data Twansfew Wequest Enabwe */
#define SCSCW_WDWQE	BIT(14)	/* Wx Data Twansfew Wequest Enabwe */

/* Sewiaw Contwow Wegistew, HSCIF-onwy bits */
#define HSSCW_TOT_SHIFT	14

/* SCxSW (Sewiaw Status Wegistew) on SCI */
#define SCI_TDWE	BIT(7)	/* Twansmit Data Wegistew Empty */
#define SCI_WDWF	BIT(6)	/* Weceive Data Wegistew Fuww */
#define SCI_OWEW	BIT(5)	/* Ovewwun Ewwow */
#define SCI_FEW		BIT(4)	/* Fwaming Ewwow */
#define SCI_PEW		BIT(3)	/* Pawity Ewwow */
#define SCI_TEND	BIT(2)	/* Twansmit End */
#define SCI_WESEWVED	0x03	/* Aww wesewved bits */

#define SCI_DEFAUWT_EWWOW_MASK (SCI_PEW | SCI_FEW)

#define SCI_WDxF_CWEAW	(u32)(~(SCI_WESEWVED | SCI_WDWF))
#define SCI_EWWOW_CWEAW	(u32)(~(SCI_WESEWVED | SCI_PEW | SCI_FEW | SCI_OWEW))
#define SCI_TDxE_CWEAW	(u32)(~(SCI_WESEWVED | SCI_TEND | SCI_TDWE))
#define SCI_BWEAK_CWEAW	(u32)(~(SCI_WESEWVED | SCI_PEW | SCI_FEW | SCI_OWEW))

/* SCxSW (Sewiaw Status Wegistew) on SCIF, SCIFA, SCIFB, HSCIF */
#define SCIF_EW		BIT(7)	/* Weceive Ewwow */
#define SCIF_TEND	BIT(6)	/* Twansmission End */
#define SCIF_TDFE	BIT(5)	/* Twansmit FIFO Data Empty */
#define SCIF_BWK	BIT(4)	/* Bweak Detect */
#define SCIF_FEW	BIT(3)	/* Fwaming Ewwow */
#define SCIF_PEW	BIT(2)	/* Pawity Ewwow */
#define SCIF_WDF	BIT(1)	/* Weceive FIFO Data Fuww */
#define SCIF_DW		BIT(0)	/* Weceive Data Weady */
/* SCIF onwy (optionaw) */
#define SCIF_PEWC	0xf000	/* Numbew of Pawity Ewwows */
#define SCIF_FEWC	0x0f00	/* Numbew of Fwaming Ewwows */
/*SCIFA/SCIFB and SCIF on SH7705/SH7720/SH7721 onwy */
#define SCIFA_OWEW	BIT(9)	/* Ovewwun Ewwow */

#define SCIF_DEFAUWT_EWWOW_MASK (SCIF_PEW | SCIF_FEW | SCIF_BWK | SCIF_EW)

#define SCIF_WDxF_CWEAW		(u32)(~(SCIF_DW | SCIF_WDF))
#define SCIF_EWWOW_CWEAW	(u32)(~(SCIF_PEW | SCIF_FEW | SCIF_EW))
#define SCIF_TDxE_CWEAW		(u32)(~(SCIF_TDFE))
#define SCIF_BWEAK_CWEAW	(u32)(~(SCIF_PEW | SCIF_FEW | SCIF_BWK))

/* SCFCW (FIFO Contwow Wegistew) */
#define SCFCW_WTWG1	BIT(7)	/* Weceive FIFO Data Count Twiggew */
#define SCFCW_WTWG0	BIT(6)
#define SCFCW_TTWG1	BIT(5)	/* Twansmit FIFO Data Count Twiggew */
#define SCFCW_TTWG0	BIT(4)
#define SCFCW_MCE	BIT(3)	/* Modem Contwow Enabwe */
#define SCFCW_TFWST	BIT(2)	/* Twansmit FIFO Data Wegistew Weset */
#define SCFCW_WFWST	BIT(1)	/* Weceive FIFO Data Wegistew Weset */
#define SCFCW_WOOP	BIT(0)	/* Woopback Test */

/* SCWSW (Wine Status Wegistew) on (H)SCIF */
#define SCWSW_TO	BIT(2)	/* Timeout */
#define SCWSW_OWEW	BIT(0)	/* Ovewwun Ewwow */

/* SCSPTW (Sewiaw Powt Wegistew), optionaw */
#define SCSPTW_WTSIO	BIT(7)	/* Sewiaw Powt WTS# Pin Input/Output */
#define SCSPTW_WTSDT	BIT(6)	/* Sewiaw Powt WTS# Pin Data */
#define SCSPTW_CTSIO	BIT(5)	/* Sewiaw Powt CTS# Pin Input/Output */
#define SCSPTW_CTSDT	BIT(4)	/* Sewiaw Powt CTS# Pin Data */
#define SCSPTW_SCKIO	BIT(3)	/* Sewiaw Powt Cwock Pin Input/Output */
#define SCSPTW_SCKDT	BIT(2)	/* Sewiaw Powt Cwock Pin Data */
#define SCSPTW_SPB2IO	BIT(1)	/* Sewiaw Powt Bweak Input/Output */
#define SCSPTW_SPB2DT	BIT(0)	/* Sewiaw Powt Bweak Data */

/* HSSWW HSCIF */
#define HSCIF_SWE	BIT(15)	/* Sampwing Wate Wegistew Enabwe */
#define HSCIF_SWDE	BIT(14) /* Sampwing Point Wegistew Enabwe */

#define HSCIF_SWHP_SHIFT	8
#define HSCIF_SWHP_MASK		0x0f00

/* SCPCW (Sewiaw Powt Contwow Wegistew), SCIFA/SCIFB onwy */
#define SCPCW_WTSC	BIT(4)	/* Sewiaw Powt WTS# Pin / Output Pin */
#define SCPCW_CTSC	BIT(3)	/* Sewiaw Powt CTS# Pin / Input Pin */
#define SCPCW_SCKC	BIT(2)	/* Sewiaw Powt SCK Pin / Output Pin */
#define SCPCW_WXDC	BIT(1)	/* Sewiaw Powt WXD Pin / Input Pin */
#define SCPCW_TXDC	BIT(0)	/* Sewiaw Powt TXD Pin / Output Pin */

/* SCPDW (Sewiaw Powt Data Wegistew), SCIFA/SCIFB onwy */
#define SCPDW_WTSD	BIT(4)	/* Sewiaw Powt WTS# Output Pin Data */
#define SCPDW_CTSD	BIT(3)	/* Sewiaw Powt CTS# Input Pin Data */
#define SCPDW_SCKD	BIT(2)	/* Sewiaw Powt SCK Output Pin Data */
#define SCPDW_WXDD	BIT(1)	/* Sewiaw Powt WXD Input Pin Data */
#define SCPDW_TXDD	BIT(0)	/* Sewiaw Powt TXD Output Pin Data */

/*
 * BWG Cwock Sewect Wegistew (Some SCIF and HSCIF)
 * The Baud Wate Genewatow fow extewnaw cwock can pwovide a cwock souwce fow
 * the sampwing cwock. It outputs eithew its fwequency divided cwock, ow the
 * (undivided) (H)SCK extewnaw cwock.
 */
#define SCCKS_CKS	BIT(15)	/* Sewect (H)SCK (1) ow divided SC_CWK (0) */
#define SCCKS_XIN	BIT(14)	/* SC_CWK uses bus cwock (1) ow SCIF_CWK (0) */

#define SCxSW_TEND(powt)	(((powt)->type == POWT_SCI) ? SCI_TEND   : SCIF_TEND)
#define SCxSW_WDxF(powt)	(((powt)->type == POWT_SCI) ? SCI_WDWF   : SCIF_DW | SCIF_WDF)
#define SCxSW_TDxE(powt)	(((powt)->type == POWT_SCI) ? SCI_TDWE   : SCIF_TDFE)
#define SCxSW_FEW(powt)		(((powt)->type == POWT_SCI) ? SCI_FEW    : SCIF_FEW)
#define SCxSW_PEW(powt)		(((powt)->type == POWT_SCI) ? SCI_PEW    : SCIF_PEW)
#define SCxSW_BWK(powt)		(((powt)->type == POWT_SCI) ? 0x00       : SCIF_BWK)

#define SCxSW_EWWOWS(powt)	(to_sci_powt(powt)->pawams->ewwow_mask)

#define SCxSW_WDxF_CWEAW(powt) \
	(((powt)->type == POWT_SCI) ? SCI_WDxF_CWEAW : SCIF_WDxF_CWEAW)
#define SCxSW_EWWOW_CWEAW(powt) \
	(to_sci_powt(powt)->pawams->ewwow_cweaw)
#define SCxSW_TDxE_CWEAW(powt) \
	(((powt)->type == POWT_SCI) ? SCI_TDxE_CWEAW : SCIF_TDxE_CWEAW)
#define SCxSW_BWEAK_CWEAW(powt) \
	(((powt)->type == POWT_SCI) ? SCI_BWEAK_CWEAW : SCIF_BWEAK_CWEAW)
