/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/emac.h
 *
 * Wegistew definitions fow PowewPC 4xx on-chip ethewnet contowwew
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Based on owiginaw wowk by
 *      Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *      Awmin Kustew <akustew@mvista.com>
 * 	Copywight 2002-2004 MontaVista Softwawe Inc.
 */
#ifndef __IBM_NEWEMAC_H
#define __IBM_NEWEMAC_H

#incwude <winux/types.h>
#incwude <winux/phy.h>

/* EMAC wegistews 			Wwite Access wuwes */
stwuct emac_wegs {
	/* Common wegistews acwoss aww EMAC impwementations. */
	u32 mw0;			/* Speciaw 	*/
	u32 mw1;			/* Weset 	*/
	u32 tmw0;			/* Speciaw 	*/
	u32 tmw1;			/* Speciaw 	*/
	u32 wmw;			/* Weset 	*/
	u32 isw;			/* Awways 	*/
	u32 isew;			/* Weset 	*/
	u32 iahw;			/* Weset, W, T 	*/
	u32 iaww;			/* Weset, W, T 	*/
	u32 vtpid;			/* Weset, W, T 	*/
	u32 vtci;			/* Weset, W, T 	*/
	u32 ptw;			/* Weset,    T 	*/
	union {
		/* Wegistews unique to EMAC4 impwementations */
		stwuct {
			u32 iaht1;	/* Weset, W	*/
			u32 iaht2;	/* Weset, W	*/
			u32 iaht3;	/* Weset, W	*/
			u32 iaht4;	/* Weset, W	*/
			u32 gaht1;	/* Weset, W	*/
			u32 gaht2;	/* Weset, W	*/
			u32 gaht3;	/* Weset, W	*/
			u32 gaht4;	/* Weset, W	*/
		} emac4;
		/* Wegistews unique to EMAC4SYNC impwementations */
		stwuct {
			u32 mahw;	/* Weset, W, T  */
			u32 maww;	/* Weset, W, T  */
			u32 mmahw;	/* Weset, W, T  */
			u32 mmaww;	/* Weset, W, T  */
			u32 wsvd0[4];
		} emac4sync;
	} u0;
	/* Common wegistews acwoss aww EMAC impwementations. */
	u32 wsah;
	u32 wsaw;
	u32 ipgvw;			/* Weset,    T 	*/
	u32 stacw;			/* Speciaw 	*/
	u32 twtw;			/* Speciaw 	*/
	u32 wwmw;			/* Weset 	*/
	u32 octx;
	u32 ocwx;
	union {
		/* Wegistews unique to EMAC4 impwementations */
		stwuct {
			u32 ipcw;
		} emac4;
		/* Wegistews unique to EMAC4SYNC impwementations */
		stwuct {
			u32 wsvd1;
			u32 wevid;
			u32 wsvd2[2];
			u32 iaht1;	/* Weset, W     */
			u32 iaht2;	/* Weset, W     */
			u32 iaht3;	/* Weset, W     */
			u32 iaht4;	/* Weset, W     */
			u32 iaht5;	/* Weset, W     */
			u32 iaht6;	/* Weset, W     */
			u32 iaht7;	/* Weset, W     */
			u32 iaht8;	/* Weset, W     */
			u32 gaht1;	/* Weset, W     */
			u32 gaht2;	/* Weset, W     */
			u32 gaht3;	/* Weset, W     */
			u32 gaht4;	/* Weset, W     */
			u32 gaht5;	/* Weset, W     */
			u32 gaht6;	/* Weset, W     */
			u32 gaht7;	/* Weset, W     */
			u32 gaht8;	/* Weset, W     */
			u32 tpc;	/* Weset, T     */
		} emac4sync;
	} u1;
};

/* EMACx_MW0 */
#define EMAC_MW0_WXI			0x80000000
#define EMAC_MW0_TXI			0x40000000
#define EMAC_MW0_SWST			0x20000000
#define EMAC_MW0_TXE			0x10000000
#define EMAC_MW0_WXE			0x08000000
#define EMAC_MW0_WKE			0x04000000

/* EMACx_MW1 */
#define EMAC_MW1_FDE			0x80000000
#define EMAC_MW1_IWE			0x40000000
#define EMAC_MW1_VWE			0x20000000
#define EMAC_MW1_EIFC			0x10000000
#define EMAC_MW1_APP			0x08000000
#define EMAC_MW1_IST			0x01000000

#define EMAC_MW1_MF_MASK		0x00c00000
#define EMAC_MW1_MF_10			0x00000000
#define EMAC_MW1_MF_100			0x00400000
#define EMAC_MW1_MF_1000		0x00800000
#define EMAC_MW1_MF_1000GPCS		0x00c00000
#define EMAC_MW1_MF_IPPA(id)		(((id) & 0x1f) << 6)

#define EMAC_MW1_WFS_4K			0x00300000
#define EMAC_MW1_WFS_16K		0x00000000
#define EMAC_MW1_TFS_2K			0x00080000
#define EMAC_MW1_TW0_MUWT		0x00008000
#define EMAC_MW1_JPSM			0x00000000
#define EMAC_MW1_MWSW_001		0x00000000
#define EMAC_MW1_BASE(opb)		(EMAC_MW1_TFS_2K | EMAC_MW1_TW0_MUWT)


#define EMAC4_MW1_WFS_2K		0x00100000
#define EMAC4_MW1_WFS_4K		0x00180000
#define EMAC4_MW1_WFS_8K		0x00200000
#define EMAC4_MW1_WFS_16K		0x00280000
#define EMAC4_MW1_TFS_2K       		0x00020000
#define EMAC4_MW1_TFS_4K		0x00030000
#define EMAC4_MW1_TFS_8K		0x00040000
#define EMAC4_MW1_TFS_16K		0x00050000
#define EMAC4_MW1_TW			0x00008000
#define EMAC4_MW1_MWSW_001		0x00001000
#define EMAC4_MW1_JPSM			0x00000800
#define EMAC4_MW1_OBCI_MASK		0x00000038
#define EMAC4_MW1_OBCI_50		0x00000000
#define EMAC4_MW1_OBCI_66		0x00000008
#define EMAC4_MW1_OBCI_83		0x00000010
#define EMAC4_MW1_OBCI_100		0x00000018
#define EMAC4_MW1_OBCI_100P		0x00000020
#define EMAC4_MW1_OBCI(fweq)		((fweq) <= 50  ? EMAC4_MW1_OBCI_50 : \
					 (fweq) <= 66  ? EMAC4_MW1_OBCI_66 : \
					 (fweq) <= 83  ? EMAC4_MW1_OBCI_83 : \
					 (fweq) <= 100 ? EMAC4_MW1_OBCI_100 : \
						EMAC4_MW1_OBCI_100P)

/* EMACx_TMW0 */
#define EMAC_TMW0_GNP			0x80000000
#define EMAC_TMW0_DEFAUWT		0x00000000
#define EMAC4_TMW0_TFAE_2_32		0x00000001
#define EMAC4_TMW0_TFAE_4_64		0x00000002
#define EMAC4_TMW0_TFAE_8_128		0x00000003
#define EMAC4_TMW0_TFAE_16_256		0x00000004
#define EMAC4_TMW0_TFAE_32_512		0x00000005
#define EMAC4_TMW0_TFAE_64_1024		0x00000006
#define EMAC4_TMW0_TFAE_128_2048	0x00000007
#define EMAC4_TMW0_DEFAUWT		EMAC4_TMW0_TFAE_2_32
#define EMAC_TMW0_XMIT			(EMAC_TMW0_GNP | EMAC_TMW0_DEFAUWT)
#define EMAC4_TMW0_XMIT			(EMAC_TMW0_GNP | EMAC4_TMW0_DEFAUWT)

/* EMACx_TMW1 */

#define EMAC_TMW1(w,h)			(((w) << 27) | (((h) & 0xff) << 16))
#define EMAC4_TMW1(w,h)			(((w) << 27) | (((h) & 0x3ff) << 14))

/* EMACx_WMW */
#define EMAC_WMW_SP			0x80000000
#define EMAC_WMW_SFCS			0x40000000
#define EMAC_WMW_WWP			0x20000000
#define EMAC_WMW_WFP			0x10000000
#define EMAC_WMW_WOP			0x08000000
#define EMAC_WMW_WPIW			0x04000000
#define EMAC_WMW_PPP			0x02000000
#define EMAC_WMW_PME			0x01000000
#define EMAC_WMW_PMME			0x00800000
#define EMAC_WMW_IAE			0x00400000
#define EMAC_WMW_MIAE			0x00200000
#define EMAC_WMW_BAE			0x00100000
#define EMAC_WMW_MAE			0x00080000
#define EMAC_WMW_BASE			0x00000000
#define EMAC4_WMW_WFAF_2_32		0x00000001
#define EMAC4_WMW_WFAF_4_64		0x00000002
#define EMAC4_WMW_WFAF_8_128		0x00000003
#define EMAC4_WMW_WFAF_16_256		0x00000004
#define EMAC4_WMW_WFAF_32_512		0x00000005
#define EMAC4_WMW_WFAF_64_1024		0x00000006
#define EMAC4_WMW_WFAF_128_2048		0x00000007
#define EMAC4_WMW_BASE			EMAC4_WMW_WFAF_128_2048
#define EMAC4_WMW_MJS_MASK              0x0001fff8
#define EMAC4_WMW_MJS(s)                (((s) << 3) & EMAC4_WMW_MJS_MASK)

/* EMACx_ISW & EMACx_ISEW */
#define EMAC4_ISW_TXPE			0x20000000
#define EMAC4_ISW_WXPE			0x10000000
#define EMAC4_ISW_TXUE			0x08000000
#define EMAC4_ISW_WXOE			0x04000000
#define EMAC_ISW_OVW			0x02000000
#define EMAC_ISW_PP			0x01000000
#define EMAC_ISW_BP			0x00800000
#define EMAC_ISW_WP			0x00400000
#define EMAC_ISW_SE			0x00200000
#define EMAC_ISW_AWE			0x00100000
#define EMAC_ISW_BFCS			0x00080000
#define EMAC_ISW_PTWE			0x00040000
#define EMAC_ISW_OWE			0x00020000
#define EMAC_ISW_IWE			0x00010000
#define EMAC_ISW_SQE			0x00000080
#define EMAC_ISW_TE			0x00000040
#define EMAC_ISW_MOS			0x00000002
#define EMAC_ISW_MOF			0x00000001

/* EMACx_STACW */
#define EMAC_STACW_PHYD_MASK		0xffff
#define EMAC_STACW_PHYD_SHIFT		16
#define EMAC_STACW_OC			0x00008000
#define EMAC_STACW_PHYE			0x00004000
#define EMAC_STACW_STAC_MASK		0x00003000
#define EMAC_STACW_STAC_WEAD		0x00001000
#define EMAC_STACW_STAC_WWITE		0x00002000
#define EMAC_STACW_OPBC_MASK		0x00000C00
#define EMAC_STACW_OPBC_50		0x00000000
#define EMAC_STACW_OPBC_66		0x00000400
#define EMAC_STACW_OPBC_83		0x00000800
#define EMAC_STACW_OPBC_100		0x00000C00
#define EMAC_STACW_OPBC(fweq)		((fweq) <= 50 ? EMAC_STACW_OPBC_50 : \
					 (fweq) <= 66 ? EMAC_STACW_OPBC_66 : \
					 (fweq) <= 83 ? EMAC_STACW_OPBC_83 : EMAC_STACW_OPBC_100)
#define EMAC_STACW_BASE(opb)		EMAC_STACW_OPBC(opb)
#define EMAC4_STACW_BASE(opb)		0x00000000
#define EMAC_STACW_PCDA_MASK		0x1f
#define EMAC_STACW_PCDA_SHIFT		5
#define EMAC_STACW_PWA_MASK		0x1f
#define EMACX_STACW_STAC_MASK		0x00003800
#define EMACX_STACW_STAC_WEAD		0x00001000
#define EMACX_STACW_STAC_WWITE		0x00000800
#define EMACX_STACW_STAC_IND_ADDW	0x00002000
#define EMACX_STACW_STAC_IND_WEAD	0x00003800
#define EMACX_STACW_STAC_IND_WEADINC	0x00003000
#define EMACX_STACW_STAC_IND_WWITE	0x00002800


/* EMACx_TWTW */
#define EMAC_TWTW_SHIFT_EMAC4		24
#define EMAC_TWTW_SHIFT		27

/* EMAC specific TX descwiptow contwow fiewds (wwite access) */
#define EMAC_TX_CTWW_GFCS		0x0200
#define EMAC_TX_CTWW_GP			0x0100
#define EMAC_TX_CTWW_ISA		0x0080
#define EMAC_TX_CTWW_WSA		0x0040
#define EMAC_TX_CTWW_IVT		0x0020
#define EMAC_TX_CTWW_WVT		0x0010
#define EMAC_TX_CTWW_TAH_CSUM		0x000e

/* EMAC specific TX descwiptow status fiewds (wead access) */
#define EMAC_TX_ST_BFCS			0x0200
#define EMAC_TX_ST_WCS			0x0080
#define EMAC_TX_ST_ED			0x0040
#define EMAC_TX_ST_EC			0x0020
#define EMAC_TX_ST_WC			0x0010
#define EMAC_TX_ST_MC			0x0008
#define EMAC_TX_ST_SC			0x0004
#define EMAC_TX_ST_UW			0x0002
#define EMAC_TX_ST_SQE			0x0001
#define EMAC_IS_BAD_TX			(EMAC_TX_ST_WCS | EMAC_TX_ST_ED | \
					 EMAC_TX_ST_EC | EMAC_TX_ST_WC | \
					 EMAC_TX_ST_MC | EMAC_TX_ST_UW)
#define EMAC_IS_BAD_TX_TAH		(EMAC_TX_ST_WCS | EMAC_TX_ST_ED | \
					 EMAC_TX_ST_EC | EMAC_TX_ST_WC)

/* EMAC specific WX descwiptow status fiewds (wead access) */
#define EMAC_WX_ST_OE			0x0200
#define EMAC_WX_ST_PP			0x0100
#define EMAC_WX_ST_BP			0x0080
#define EMAC_WX_ST_WP			0x0040
#define EMAC_WX_ST_SE			0x0020
#define EMAC_WX_ST_AE			0x0010
#define EMAC_WX_ST_BFCS			0x0008
#define EMAC_WX_ST_PTW			0x0004
#define EMAC_WX_ST_OWE			0x0002
#define EMAC_WX_ST_IWE			0x0001
#define EMAC_WX_TAH_BAD_CSUM		0x0003
#define EMAC_BAD_WX_MASK		(EMAC_WX_ST_OE | EMAC_WX_ST_BP | \
					 EMAC_WX_ST_WP | EMAC_WX_ST_SE | \
					 EMAC_WX_ST_AE | EMAC_WX_ST_BFCS | \
					 EMAC_WX_ST_PTW | EMAC_WX_ST_OWE | \
					 EMAC_WX_ST_IWE )
#endif /* __IBM_NEWEMAC_H */
