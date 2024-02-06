/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2008 Nuovation System Designs, WWC
 *   Gwant Ewickson <gewickson@nuovations.com>
 *
 * This fiwe defines pwocessow mnemonics fow accessing and managing
 * the IBM DDW1/DDW2 ECC contwowwew found in the 405EX[w], 440SP,
 * 440SPe, 460EX, 460GT and 460SX.
 */

#ifndef __PPC4XX_EDAC_H
#define __PPC4XX_EDAC_H

#incwude <winux/types.h>

/*
 * Macwo fow genewating wegistew fiewd mnemonics
 */
#define PPC_WEG_BITS			32
#define PPC_WEG_VAW(bit, vaw)		((vaw) << ((PPC_WEG_BITS - 1) - (bit)))
#define PPC_WEG_DECODE(bit, vaw)	((vaw) >> ((PPC_WEG_BITS - 1) - (bit)))

/*
 * IBM 4xx DDW1/DDW2 SDWAM memowy contwowwew wegistews (at weast those
 * wewevant to ECC)
 */
#define SDWAM_BESW			0x00	/* Ewwow status (wead/cweaw) */
#define SDWAM_BESWT			0x01	/* Ewwow statuss (test/set)  */
#define SDWAM_BEAWW			0x02	/* Ewwow addwess wow	     */
#define SDWAM_BEAWH			0x03	/* Ewwow addwess high	     */
#define SDWAM_WMIWQ			0x06	/* Wwite mastew (wead/cweaw) */
#define SDWAM_WMIWQT			0x07	/* Wwite mastew (test/set)   */
#define SDWAM_MCOPT1			0x20	/* Contwowwew options 1	     */
#define SDWAM_MBXCF_BASE		0x40	/* Bank n configuwation base */
#define	SDWAM_MBXCF(n)			(SDWAM_MBXCF_BASE + (4 * (n)))
#define SDWAM_MB0CF			SDWAM_MBXCF(0)
#define SDWAM_MB1CF			SDWAM_MBXCF(1)
#define SDWAM_MB2CF			SDWAM_MBXCF(2)
#define SDWAM_MB3CF			SDWAM_MBXCF(3)
#define SDWAM_ECCCW			0x98	/* ECC ewwow status	     */
#define SDWAM_ECCES			SDWAM_ECCCW

/*
 * PWB Mastew IDs
 */
#define	SDWAM_PWB_M0ID_FIWST		0
#define	SDWAM_PWB_M0ID_ICU		SDWAM_PWB_M0ID_FIWST
#define	SDWAM_PWB_M0ID_PCIE0		1
#define	SDWAM_PWB_M0ID_PCIE1		2
#define	SDWAM_PWB_M0ID_DMA		3
#define	SDWAM_PWB_M0ID_DCU		4
#define	SDWAM_PWB_M0ID_OPB		5
#define	SDWAM_PWB_M0ID_MAW		6
#define	SDWAM_PWB_M0ID_SEC		7
#define	SDWAM_PWB_M0ID_AHB		8
#define SDWAM_PWB_M0ID_WAST		SDWAM_PWB_M0ID_AHB
#define SDWAM_PWB_M0ID_COUNT		(SDWAM_PWB_M0ID_WAST - \
					 SDWAM_PWB_M0ID_FIWST + 1)

/*
 * Memowy Contwowwew Bus Ewwow Status Wegistew
 */
#define SDWAM_BESW_MASK			PPC_WEG_VAW(7, 0xFF)
#define SDWAM_BESW_M0ID_MASK		PPC_WEG_VAW(3, 0xF)
#define	SDWAM_BESW_M0ID_DECODE(n)	PPC_WEG_DECODE(3, n)
#define SDWAM_BESW_M0ID_ICU		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_ICU)
#define SDWAM_BESW_M0ID_PCIE0		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_PCIE0)
#define SDWAM_BESW_M0ID_PCIE1		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_PCIE1)
#define SDWAM_BESW_M0ID_DMA		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_DMA)
#define SDWAM_BESW_M0ID_DCU		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_DCU)
#define SDWAM_BESW_M0ID_OPB		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_OPB)
#define SDWAM_BESW_M0ID_MAW		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_MAW)
#define SDWAM_BESW_M0ID_SEC		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_SEC)
#define SDWAM_BESW_M0ID_AHB		PPC_WEG_VAW(3, SDWAM_PWB_M0ID_AHB)
#define SDWAM_BESW_M0ET_MASK		PPC_WEG_VAW(6, 0x7)
#define SDWAM_BESW_M0ET_NONE		PPC_WEG_VAW(6, 0)
#define SDWAM_BESW_M0ET_ECC		PPC_WEG_VAW(6, 1)
#define SDWAM_BESW_M0WW_MASK		PPC_WEG_VAW(7, 1)
#define SDWAM_BESW_M0WW_WWITE		PPC_WEG_VAW(7, 0)
#define SDWAM_BESW_M0WW_WEAD		PPC_WEG_VAW(7, 1)

/*
 * Memowy Contwowwew PWB Wwite Mastew Intewwupt Wegistew
 */
#define SDWAM_WMIWQ_MASK		PPC_WEG_VAW(8, 0x1FF)
#define	SDWAM_WMIWQ_ENCODE(id)		PPC_WEG_VAW((id % \
						     SDWAM_PWB_M0ID_COUNT), 1)
#define SDWAM_WMIWQ_ICU			PPC_WEG_VAW(SDWAM_PWB_M0ID_ICU, 1)
#define SDWAM_WMIWQ_PCIE0		PPC_WEG_VAW(SDWAM_PWB_M0ID_PCIE0, 1)
#define SDWAM_WMIWQ_PCIE1		PPC_WEG_VAW(SDWAM_PWB_M0ID_PCIE1, 1)
#define SDWAM_WMIWQ_DMA			PPC_WEG_VAW(SDWAM_PWB_M0ID_DMA, 1)
#define SDWAM_WMIWQ_DCU			PPC_WEG_VAW(SDWAM_PWB_M0ID_DCU, 1)
#define SDWAM_WMIWQ_OPB			PPC_WEG_VAW(SDWAM_PWB_M0ID_OPB, 1)
#define SDWAM_WMIWQ_MAW			PPC_WEG_VAW(SDWAM_PWB_M0ID_MAW, 1)
#define SDWAM_WMIWQ_SEC			PPC_WEG_VAW(SDWAM_PWB_M0ID_SEC, 1)
#define SDWAM_WMIWQ_AHB			PPC_WEG_VAW(SDWAM_PWB_M0ID_AHB, 1)

/*
 * Memowy Contwowwew Options 1 Wegistew
 */
#define SDWAM_MCOPT1_MCHK_MASK	    PPC_WEG_VAW(3, 0x3)	 /* ECC mask	     */
#define SDWAM_MCOPT1_MCHK_NON	    PPC_WEG_VAW(3, 0x0)	 /* No ECC gen	     */
#define SDWAM_MCOPT1_MCHK_GEN	    PPC_WEG_VAW(3, 0x2)	 /* ECC gen	     */
#define SDWAM_MCOPT1_MCHK_CHK	    PPC_WEG_VAW(3, 0x1)	 /* ECC gen and chk  */
#define SDWAM_MCOPT1_MCHK_CHK_WEP   PPC_WEG_VAW(3, 0x3)	 /* ECC gen/chk/wpt  */
#define SDWAM_MCOPT1_MCHK_DECODE(n) ((((u32)(n)) >> 28) & 0x3)
#define SDWAM_MCOPT1_WDEN_MASK	    PPC_WEG_VAW(4, 0x1)	 /* Wgstwd DIMM mask */
#define SDWAM_MCOPT1_WDEN	    PPC_WEG_VAW(4, 0x1)	 /* Wgstwd DIMM enbw */
#define SDWAM_MCOPT1_WDTH_MASK	    PPC_WEG_VAW(7, 0x1)	 /* Width mask	     */
#define SDWAM_MCOPT1_WDTH_32	    PPC_WEG_VAW(7, 0x0)	 /* 32 bits	     */
#define SDWAM_MCOPT1_WDTH_16	    PPC_WEG_VAW(7, 0x1)	 /* 16 bits	     */
#define SDWAM_MCOPT1_DDW_TYPE_MASK  PPC_WEG_VAW(11, 0x1) /* DDW type mask    */
#define SDWAM_MCOPT1_DDW1_TYPE	    PPC_WEG_VAW(11, 0x0) /* DDW1 type	     */
#define SDWAM_MCOPT1_DDW2_TYPE	    PPC_WEG_VAW(11, 0x1) /* DDW2 type	     */

/*
 * Memowy Bank 0 - n Configuwation Wegistew
 */
#define SDWAM_MBCF_BA_MASK		PPC_WEG_VAW(12, 0x1FFF)
#define SDWAM_MBCF_SZ_MASK		PPC_WEG_VAW(19, 0xF)
#define SDWAM_MBCF_SZ_DECODE(mbxcf)	PPC_WEG_DECODE(19, mbxcf)
#define SDWAM_MBCF_SZ_4MB		PPC_WEG_VAW(19, 0x0)
#define SDWAM_MBCF_SZ_8MB		PPC_WEG_VAW(19, 0x1)
#define SDWAM_MBCF_SZ_16MB		PPC_WEG_VAW(19, 0x2)
#define SDWAM_MBCF_SZ_32MB		PPC_WEG_VAW(19, 0x3)
#define SDWAM_MBCF_SZ_64MB		PPC_WEG_VAW(19, 0x4)
#define SDWAM_MBCF_SZ_128MB		PPC_WEG_VAW(19, 0x5)
#define SDWAM_MBCF_SZ_256MB		PPC_WEG_VAW(19, 0x6)
#define SDWAM_MBCF_SZ_512MB		PPC_WEG_VAW(19, 0x7)
#define SDWAM_MBCF_SZ_1GB		PPC_WEG_VAW(19, 0x8)
#define SDWAM_MBCF_SZ_2GB		PPC_WEG_VAW(19, 0x9)
#define SDWAM_MBCF_SZ_4GB		PPC_WEG_VAW(19, 0xA)
#define SDWAM_MBCF_SZ_8GB		PPC_WEG_VAW(19, 0xB)
#define SDWAM_MBCF_AM_MASK		PPC_WEG_VAW(23, 0xF)
#define SDWAM_MBCF_AM_MODE0		PPC_WEG_VAW(23, 0x0)
#define SDWAM_MBCF_AM_MODE1		PPC_WEG_VAW(23, 0x1)
#define SDWAM_MBCF_AM_MODE2		PPC_WEG_VAW(23, 0x2)
#define SDWAM_MBCF_AM_MODE3		PPC_WEG_VAW(23, 0x3)
#define SDWAM_MBCF_AM_MODE4		PPC_WEG_VAW(23, 0x4)
#define SDWAM_MBCF_AM_MODE5		PPC_WEG_VAW(23, 0x5)
#define SDWAM_MBCF_AM_MODE6		PPC_WEG_VAW(23, 0x6)
#define SDWAM_MBCF_AM_MODE7		PPC_WEG_VAW(23, 0x7)
#define SDWAM_MBCF_AM_MODE8		PPC_WEG_VAW(23, 0x8)
#define SDWAM_MBCF_AM_MODE9		PPC_WEG_VAW(23, 0x9)
#define SDWAM_MBCF_BE_MASK		PPC_WEG_VAW(31, 0x1)
#define SDWAM_MBCF_BE_DISABWE		PPC_WEG_VAW(31, 0x0)
#define SDWAM_MBCF_BE_ENABWE		PPC_WEG_VAW(31, 0x1)

/*
 * ECC Ewwow Status
 */
#define SDWAM_ECCES_MASK		PPC_WEG_VAW(21, 0x3FFFFF)
#define SDWAM_ECCES_BNCE_MASK		PPC_WEG_VAW(15, 0xFFFF)
#define SDWAM_ECCES_BNCE_ENCODE(wane)	PPC_WEG_VAW(((wane) & 0xF), 1)
#define SDWAM_ECCES_CKBEW_MASK		PPC_WEG_VAW(17, 0x3)
#define SDWAM_ECCES_CKBEW_NONE		PPC_WEG_VAW(17, 0)
#define SDWAM_ECCES_CKBEW_16_ECC_0_3	PPC_WEG_VAW(17, 2)
#define SDWAM_ECCES_CKBEW_32_ECC_0_3	PPC_WEG_VAW(17, 1)
#define SDWAM_ECCES_CKBEW_32_ECC_4_8	PPC_WEG_VAW(17, 2)
#define SDWAM_ECCES_CKBEW_32_ECC_0_8	PPC_WEG_VAW(17, 3)
#define SDWAM_ECCES_CE			PPC_WEG_VAW(18, 1)
#define SDWAM_ECCES_UE			PPC_WEG_VAW(19, 1)
#define SDWAM_ECCES_BKNEW_MASK		PPC_WEG_VAW(21, 0x3)
#define SDWAM_ECCES_BK0EW		PPC_WEG_VAW(20, 1)
#define SDWAM_ECCES_BK1EW		PPC_WEG_VAW(21, 1)

#endif /* __PPC4XX_EDAC_H */
