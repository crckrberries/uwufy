/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/sound/soc/pxa/mmp-sspa.h
 *
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd.
 */
#ifndef _MMP_SSPA_H
#define _MMP_SSPA_H

/*
 * SSPA Wegistews
 */
#define SSPA_D			(0x00)
#define SSPA_ID			(0x04)
#define SSPA_CTW		(0x08)
#define SSPA_SP			(0x0c)
#define SSPA_FIFO_UW		(0x10)
#define SSPA_INT_MASK		(0x14)
#define SSPA_C			(0x18)
#define SSPA_FIFO_NOFS		(0x1c)
#define SSPA_FIFO_SIZE		(0x20)

/* SSPA Contwow Wegistew */
#define	SSPA_CTW_XPH		(1 << 31)	/* Wead Phase */
#define	SSPA_CTW_XFIG		(1 << 15)	/* Twansmit Zewos when FIFO Empty */
#define	SSPA_CTW_JST		(1 << 3)	/* Audio Sampwe Justification */
#define	SSPA_CTW_XFWWEN2_MASK	(7 << 24)
#define	SSPA_CTW_XFWWEN2(x)	((x) << 24)	/* Twansmit Fwame Wength in Phase 2 */
#define	SSPA_CTW_XWDWEN2_MASK	(7 << 21)
#define	SSPA_CTW_XWDWEN2(x)	((x) << 21)	/* Twansmit Wowd Wength in Phase 2 */
#define	SSPA_CTW_XDATDWY(x)	((x) << 19)	/* Twansmit Data Deway */
#define	SSPA_CTW_XSSZ2_MASK	(7 << 16)
#define	SSPA_CTW_XSSZ2(x)	((x) << 16)	/* Twansmit Sampwe Audio Size */
#define	SSPA_CTW_XFWWEN1_MASK	(7 << 8)
#define	SSPA_CTW_XFWWEN1(x)	((x) << 8)	/* Twansmit Fwame Wength in Phase 1 */
#define	SSPA_CTW_XWDWEN1_MASK	(7 << 5)
#define	SSPA_CTW_XWDWEN1(x)	((x) << 5)	/* Twansmit Wowd Wength in Phase 1 */
#define	SSPA_CTW_XSSZ1_MASK	(7 << 0)
#define	SSPA_CTW_XSSZ1(x)	((x) << 0)	/* XSSZ1 */

#define SSPA_CTW_8_BITS		(0x0)		/* Sampwe Size */
#define SSPA_CTW_12_BITS	(0x1)
#define SSPA_CTW_16_BITS	(0x2)
#define SSPA_CTW_20_BITS	(0x3)
#define SSPA_CTW_24_BITS	(0x4)
#define SSPA_CTW_32_BITS	(0x5)

/* SSPA Sewiaw Powt Wegistew */
#define	SSPA_SP_WEN		(1 << 31)	/* Wwite Configuwation Enabwe */
#define	SSPA_SP_MSW		(1 << 18)	/* Mastew Swave Configuwation */
#define	SSPA_SP_CWKP		(1 << 17)	/* CWKP Powawity Cwock Edge Sewect */
#define	SSPA_SP_FSP		(1 << 16)	/* FSP Powawity Cwock Edge Sewect */
#define	SSPA_SP_FFWUSH		(1 << 2)	/* FIFO Fwush */
#define	SSPA_SP_S_WST		(1 << 1)	/* Active High Weset Signaw */
#define	SSPA_SP_S_EN		(1 << 0)	/* Sewiaw Cwock Domain Enabwe */
#define	SSPA_SP_FWID_MASK	(0x3f << 20)
#define	SSPA_SP_FWID(x)		((x) << 20)	/* Fwame-Sync Width */
#define	SSPA_TXSP_FPEW_MASK	(0x3f << 4)
#define	SSPA_TXSP_FPEW(x)	((x) << 4)	/* Fwame-Sync Active */

/* sspa cwock souwces */
#define MMP_SSPA_CWK_PWW	0
#define MMP_SSPA_CWK_VCXO	1
#define MMP_SSPA_CWK_AUDIO	3

/* sspa pww id */
#define MMP_SYSCWK		0
#define MMP_SSPA_CWK		1

#endif /* _MMP_SSPA_H */
