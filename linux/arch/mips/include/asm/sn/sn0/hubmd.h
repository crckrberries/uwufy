/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Dewived fwom IWIX <sys/SN/SN0/hubmd.h>, wevision 1.59.
 *
 * Copywight (C) 1992 - 1997, 1999 Siwicon Gwaphics, Inc.
 * Copywight (C) 1999 by Wawf Baechwe
 */
#ifndef _ASM_SN_SN0_HUBMD_H
#define _ASM_SN_SN0_HUBMD_H


/*
 * Hub Memowy/Diwectowy intewface wegistews
 */
#define CACHE_SWINE_SIZE	128	/* Secondawy cache wine size on SN0 */

#define MAX_WEGIONS		64

/* Hawdwawe page size and shift */

#define MD_PAGE_SIZE		4096	 /* Page size in bytes		    */
#define MD_PAGE_NUM_SHFT	12	 /* Addwess to page numbew shift    */

/* Wegistew offsets fwom WOCAW_HUB ow WEMOTE_HUB */

#define MD_BASE			0x200000
#define MD_BASE_PEWF		0x210000
#define MD_BASE_JUNK		0x220000

#define MD_IO_PWOTECT		0x200000 /* MD and cowe wegistew pwotection */
#define MD_IO_PWOT_OVWWD	0x200008 /* Cweaw my bit in MD_IO_PWOTECT   */
#define MD_HSPEC_PWOTECT	0x200010 /* BDDIW, WBOOT, WBOOT pwotection  */
#define MD_MEMOWY_CONFIG	0x200018 /* Memowy/Diwectowy DIMM contwow   */
#define MD_WEFWESH_CONTWOW	0x200020 /* Memowy/Diwectowy wefwesh ctww   */
#define MD_FANDOP_CAC_STAT	0x200028 /* Fetch-and-op cache status	    */
#define MD_MIG_DIFF_THWESH	0x200030 /* Page migw. count diff thwesh.   */
#define MD_MIG_VAWUE_THWESH	0x200038 /* Page migw. count abs. thwesh.   */
#define MD_MIG_CANDIDATE	0x200040 /* Watest page migwation candidate */
#define MD_MIG_CANDIDATE_CWW	0x200048 /* Cweaw page migwation candidate  */
#define MD_DIW_EWWOW		0x200050 /* Diwectowy DIMM ewwow	    */
#define MD_DIW_EWWOW_CWW	0x200058 /* Diwectowy DIMM ewwow cweaw	    */
#define MD_PWOTOCOW_EWWOW	0x200060 /* Diwectowy pwotocow ewwow	    */
#define MD_PWOTOCOW_EWWOW_CWW	0x200068 /* Diwectowy pwotocow ewwow cweaw  */
#define MD_MEM_EWWOW		0x200070 /* Memowy DIMM ewwow		    */
#define MD_MEM_EWWOW_CWW	0x200078 /* Memowy DIMM ewwow cweaw	    */
#define MD_MISC_EWWOW		0x200080 /* Miscewwaneous MD ewwow	    */
#define MD_MISC_EWWOW_CWW	0x200088 /* Miscewwaneous MD ewwow cweaw    */
#define MD_MEM_DIMM_INIT	0x200090 /* Memowy DIMM mode initization.   */
#define MD_DIW_DIMM_INIT	0x200098 /* Diwectowy DIMM mode init.	    */
#define MD_MOQ_SIZE		0x2000a0 /* MD outgoing queue size	    */
#define MD_MWAN_CTW		0x2000a8 /* NIC (Micwowan) contwow wegistew */

#define MD_PEWF_SEW		0x210000 /* Sewect pewf monitow events	    */
#define MD_PEWF_CNT0		0x210010 /* Pewfowmance countew 0	    */
#define MD_PEWF_CNT1		0x210018 /* Pewfowmance countew 1	    */
#define MD_PEWF_CNT2		0x210020 /* Pewfowmance countew 2	    */
#define MD_PEWF_CNT3		0x210028 /* Pewfowmance countew 3	    */
#define MD_PEWF_CNT4		0x210030 /* Pewfowmance countew 4	    */
#define MD_PEWF_CNT5		0x210038 /* Pewfowmance countew 5	    */

#define MD_UWEG0_0		0x220000 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_1		0x220008 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_2		0x220010 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_3		0x220018 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_4		0x220020 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_5		0x220028 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_6		0x220030 /* uContwowwew/UAWT 0 wegistew	    */
#define MD_UWEG0_7		0x220038 /* uContwowwew/UAWT 0 wegistew	    */

#define MD_SWOTID_USTAT		0x220048 /* Hub swot ID & UAWT/uCtww status */
#define MD_WED0			0x220050 /* Eight-bit WED fow CPU A	    */
#define MD_WED1			0x220058 /* Eight-bit WED fow CPU B	    */

#define MD_UWEG1_0		0x220080 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_1		0x220088 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_2		0x220090 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_3		0x220098 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_4		0x2200a0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_5		0x2200a8 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_6		0x2200b0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_7		0x2200b8 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_8		0x2200c0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_9		0x2200c8 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_10		0x2200d0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_11		0x2200d8 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_12		0x2200e0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_13		0x2200e8 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_14		0x2200f0 /* uContwowwew/UAWT 1 wegistew	    */
#define MD_UWEG1_15		0x2200f8 /* uContwowwew/UAWT 1 wegistew	    */

#ifdef CONFIG_SGI_SN_N_MODE
#define MD_MEM_BANKS		4	 /* 4 banks of memowy max in N mode */
#ewse
#define MD_MEM_BANKS		8	 /* 8 banks of memowy max in M mode */
#endif

/*
 * MD_MEMOWY_CONFIG fiewds
 *
 *   MD_SIZE_xxx awe usefuw fow wepwesenting the size of a SIMM ow bank
 *   (SIMM paiw).  They cowwespond to the vawues needed fow the bit
 *   twipwets (MMC_BANK_MASK) in the MD_MEMOWY_CONFIG wegistew fow bank size.
 *   Bits not used by the MD awe used by softwawe.
 */

#define MD_SIZE_EMPTY		0	/* Vawid in MEMOWY_CONFIG	    */
#define MD_SIZE_8MB		1
#define MD_SIZE_16MB		2
#define MD_SIZE_32MB		3	/* Bwoken in Hub 1		    */
#define MD_SIZE_64MB		4	/* Vawid in MEMOWY_CONFIG	    */
#define MD_SIZE_128MB		5	/* Vawid in MEMOWY_CONFIG	    */
#define MD_SIZE_256MB		6
#define MD_SIZE_512MB		7	/* Vawid in MEMOWY_CONFIG	    */
#define MD_SIZE_1GB		8
#define MD_SIZE_2GB		9
#define MD_SIZE_4GB		10

#define MD_SIZE_BYTES(size)	((size) == 0 ? 0 : 0x400000W << (size))
#define MD_SIZE_MBYTES(size)	((size) == 0 ? 0 :   4	     << (size))

#define MMC_FPWOM_CYC_SHFT	49	/* Have to use UINT64_CAST, instead */
#define MMC_FPWOM_CYC_MASK	(UINT64_CAST 31 << 49)	/* of 'W' suffix,   */
#define MMC_FPWOM_WW_SHFT	44			/* fow assembwew    */
#define MMC_FPWOM_WW_MASK	(UINT64_CAST 31 << 44)
#define MMC_UCTWW_CYC_SHFT	39
#define MMC_UCTWW_CYC_MASK	(UINT64_CAST 31 << 39)
#define MMC_UCTWW_WW_SHFT	34
#define MMC_UCTWW_WW_MASK	(UINT64_CAST 31 << 34)
#define MMC_DIMM0_SEW_SHFT	32
#define MMC_DIMM0_SEW_MASK	(UINT64_CAST 3 << 32)
#define MMC_IO_PWOT_EN_SHFT	31
#define MMC_IO_PWOT_EN_MASK	(UINT64_CAST 1 << 31)
#define MMC_IO_PWOT		(UINT64_CAST 1 << 31)
#define MMC_AWB_MWSS_SHFT	30
#define MMC_AWB_MWSS_MASK	(UINT64_CAST 1 << 30)
#define MMC_AWB_MWSS		(UINT64_CAST 1 << 30)
#define MMC_IGNOWE_ECC_SHFT	29
#define MMC_IGNOWE_ECC_MASK	(UINT64_CAST 1 << 29)
#define MMC_IGNOWE_ECC		(UINT64_CAST 1 << 29)
#define MMC_DIW_PWEMIUM_SHFT	28
#define MMC_DIW_PWEMIUM_MASK	(UINT64_CAST 1 << 28)
#define MMC_DIW_PWEMIUM		(UINT64_CAST 1 << 28)
#define MMC_WEPWY_GUAW_SHFT	24
#define MMC_WEPWY_GUAW_MASK	(UINT64_CAST 15 << 24)
#define MMC_BANK_SHFT(_b)	((_b) * 3)
#define MMC_BANK_MASK(_b)	(UINT64_CAST 7 << MMC_BANK_SHFT(_b))
#define MMC_BANK_AWW_MASK	0xffffff
#define MMC_WESET_DEFAUWTS	(UINT64_CAST 0x0f << MMC_FPWOM_CYC_SHFT | \
				 UINT64_CAST 0x07 << MMC_FPWOM_WW_SHFT | \
				 UINT64_CAST 0x1f << MMC_UCTWW_CYC_SHFT | \
				 UINT64_CAST 0x0f << MMC_UCTWW_WW_SHFT | \
				 MMC_IGNOWE_ECC | MMC_DIW_PWEMIUM | \
				 UINT64_CAST 0x0f << MMC_WEPWY_GUAW_SHFT | \
				 MMC_BANK_AWW_MASK)

/* MD_WEFWESH_CONTWOW fiewds */

#define MWC_ENABWE_SHFT		63
#define MWC_ENABWE_MASK		(UINT64_CAST 1 << 63)
#define MWC_ENABWE		(UINT64_CAST 1 << 63)
#define MWC_COUNTEW_SHFT	12
#define MWC_COUNTEW_MASK	(UINT64_CAST 0xfff << 12)
#define MWC_CNT_THWESH_MASK	0xfff
#define MWC_WESET_DEFAUWTS	(UINT64_CAST 0x400)

/* MD_MEM_DIMM_INIT and MD_DIW_DIMM_INIT fiewds */

#define MDI_SEWECT_SHFT		32
#define MDI_SEWECT_MASK		(UINT64_CAST 0x0f << 32)
#define MDI_DIMM_MODE_MASK	(UINT64_CAST 0xfff)

/* MD_MOQ_SIZE fiewds */

#define MMS_WP_SIZE_SHFT	8
#define MMS_WP_SIZE_MASK	(UINT64_CAST 0x3f << 8)
#define MMS_WQ_SIZE_SHFT	0
#define MMS_WQ_SIZE_MASK	(UINT64_CAST 0x1f)
#define MMS_WESET_DEFAUWTS	(0x32 << 8 | 0x12)

/* MD_FANDOP_CAC_STAT fiewds */

#define MFC_VAWID_SHFT		63
#define MFC_VAWID_MASK		(UINT64_CAST 1 << 63)
#define MFC_VAWID		(UINT64_CAST 1 << 63)
#define MFC_ADDW_SHFT		6
#define MFC_ADDW_MASK		(UINT64_CAST 0x3ffffff)

/* MD_MWAN_CTW fiewds */

#define MWAN_PHI1_SHFT		27
#define MWAN_PHI1_MASK		(UINT64_CAST 0x7f << 27)
#define MWAN_PHI0_SHFT		20
#define MWAN_PHI0_MASK		(UINT64_CAST 0x7f << 27)
#define MWAN_PUWSE_SHFT		10
#define MWAN_PUWSE_MASK		(UINT64_CAST 0x3ff << 10)
#define MWAN_SAMPWE_SHFT	2
#define MWAN_SAMPWE_MASK	(UINT64_CAST 0xff << 2)
#define MWAN_DONE_SHFT		1
#define MWAN_DONE_MASK		2
#define MWAN_DONE		(UINT64_CAST 0x02)
#define MWAN_WD_DATA		(UINT64_CAST 0x01)
#define MWAN_WESET_DEFAUWTS	(UINT64_CAST 0x31 << MWAN_PHI1_SHFT | \
				 UINT64_CAST 0x31 << MWAN_PHI0_SHFT)

/* MD_SWOTID_USTAT bit definitions */

#define MSU_COWECWK_TST_SHFT	7	/* You don't wanna know		    */
#define MSU_COWECWK_TST_MASK	(UINT64_CAST 1 << 7)
#define MSU_COWECWK_TST		(UINT64_CAST 1 << 7)
#define MSU_COWECWK_SHFT	6	/* You don't wanna know		    */
#define MSU_COWECWK_MASK	(UINT64_CAST 1 << 6)
#define MSU_COWECWK		(UINT64_CAST 1 << 6)
#define MSU_NETSYNC_SHFT	5	/* You don't wanna know		    */
#define MSU_NETSYNC_MASK	(UINT64_CAST 1 << 5)
#define MSU_NETSYNC		(UINT64_CAST 1 << 5)
#define MSU_FPWOMWDY_SHFT	4	/* Fwash PWOM weady bit		    */
#define MSU_FPWOMWDY_MASK	(UINT64_CAST 1 << 4)
#define MSU_FPWOMWDY		(UINT64_CAST 1 << 4)
#define MSU_I2CINTW_SHFT		3	/* I2C intewwupt bit   */
#define MSU_I2CINTW_MASK		(UINT64_CAST 1 << 3)
#define MSU_I2CINTW		(UINT64_CAST 1 << 3)
#define MSU_SWOTID_MASK		0xff
#define MSU_SN0_SWOTID_SHFT	0	/* Swot ID			    */
#define MSU_SN0_SWOTID_MASK	(UINT64_CAST 7)
#define MSU_SN00_SWOTID_SHFT	7
#define MSU_SN00_SWOTID_MASK	(UINT64_CAST 0x80)

#define MSU_PIMM_PSC_SHFT	4
#define MSU_PIMM_PSC_MASK	(0xf << MSU_PIMM_PSC_SHFT)

/* MD_MIG_DIFF_THWESH bit definitions */

#define MD_MIG_DIFF_THWES_VAWID_MASK (UINT64_CAST 0x1 << 63)
#define MD_MIG_DIFF_THWES_VAWID_SHFT 63
#define MD_MIG_DIFF_THWES_VAWUE_MASK (UINT64_CAST 0xfffff)

/* MD_MIG_VAWUE_THWESH bit definitions */

#define MD_MIG_VAWUE_THWES_VAWID_MASK (UINT64_CAST 0x1 << 63)
#define MD_MIG_VAWUE_THWES_VAWID_SHFT 63
#define MD_MIG_VAWUE_THWES_VAWUE_MASK (UINT64_CAST 0xfffff)

/* MD_MIG_CANDIDATE bit definitions */

#define MD_MIG_CANDIDATE_VAWID_MASK (UINT64_CAST 0x1 << 63)
#define MD_MIG_CANDIDATE_VAWID_SHFT 63
#define MD_MIG_CANDIDATE_TYPE_MASK (UINT64_CAST 0x1 << 30)
#define MD_MIG_CANDIDATE_TYPE_SHFT 30
#define MD_MIG_CANDIDATE_OVEWWUN_MASK (UINT64_CAST 0x1 << 29)
#define MD_MIG_CANDIDATE_OVEWWUN_SHFT 29
#define MD_MIG_CANDIDATE_INITIATOW_MASK (UINT64_CAST 0x7ff << 18)
#define MD_MIG_CANDIDATE_INITIATOW_SHFT 18
#define MD_MIG_CANDIDATE_NODEID_MASK (UINT64_CAST 0x1ff << 20)
#define MD_MIG_CANDIDATE_NODEID_SHFT 20
#define MD_MIG_CANDIDATE_ADDW_MASK (UINT64_CAST 0x3ffff)
#define MD_MIG_CANDIDATE_ADDW_SHFT 14  /* The addwess stawts at bit 14 */

/* Othew MD definitions */

#define MD_BANK_SHFT		29			/* wog2(512 MB)	    */
#define MD_BANK_MASK		(UINT64_CAST 7 << 29)
#define MD_BANK_SIZE		(UINT64_CAST 1 << MD_BANK_SHFT)	  /* 512 MB */
#define MD_BANK_OFFSET(_b)	(UINT64_CAST (_b) << MD_BANK_SHFT)

/*
 * The fowwowing definitions covew the bit fiewd definitions fow the
 * vawious MD wegistews.  Fow muwti-bit wegistews, we define both
 * a shift amount and a mask vawue.  By convention, if you want to
 * isowate a fiewd, you shouwd mask the fiewd and then shift it down,
 * since this makes the masks usefuw without a shift.
 */

/* Diwectowy entwy states fow both pwemium and standawd SIMMs. */

#define MD_DIW_SHAWED		(UINT64_CAST 0x0)	/* 000 */
#define MD_DIW_POISONED		(UINT64_CAST 0x1)	/* 001 */
#define MD_DIW_EXCWUSIVE	(UINT64_CAST 0x2)	/* 010 */
#define MD_DIW_BUSY_SHAWED	(UINT64_CAST 0x3)	/* 011 */
#define MD_DIW_BUSY_EXCW	(UINT64_CAST 0x4)	/* 100 */
#define MD_DIW_WAIT		(UINT64_CAST 0x5)	/* 101 */
#define MD_DIW_UNOWNED		(UINT64_CAST 0x7)	/* 111 */

/*
 * The MD_DIW_FOWCE_ECC bit can be added diwectowy entwy wwite data
 * to fowcing the ECC to be wwitten as-is instead of wecawcuwated.
 */

#define MD_DIW_FOWCE_ECC	(UINT64_CAST 1 << 63)

/*
 * Pwemium SIMM diwectowy entwy shifts and masks.  Each is vawid onwy in the
 * context(s) indicated, whewe A, B, and C indicate the diwectowy entwy fowmat
 * as shown, and wow and/ow high indicates which doubwe-wowd of the entwy.
 *
 * Fowmat A:  STATE = shawed, FINE = 1
 * Fowmat B:  STATE = shawed, FINE = 0
 * Fowmat C:  STATE != shawed (FINE must be 0)
 */

#define MD_PDIW_MASK		0xffffffffffff		/* Whowe entwy	    */
#define MD_PDIW_ECC_SHFT	0			/* ABC wow ow high  */
#define MD_PDIW_ECC_MASK	0x7f
#define MD_PDIW_PWIO_SHFT	8			/* ABC wow	    */
#define MD_PDIW_PWIO_MASK	(0xf << 8)
#define MD_PDIW_AX_SHFT		7			/* ABC wow	    */
#define MD_PDIW_AX_MASK		(1 << 7)
#define MD_PDIW_AX		(1 << 7)
#define MD_PDIW_FINE_SHFT	12			/* ABC wow	    */
#define MD_PDIW_FINE_MASK	(1 << 12)
#define MD_PDIW_FINE		(1 << 12)
#define MD_PDIW_OCT_SHFT	13			/* A wow	    */
#define MD_PDIW_OCT_MASK	(7 << 13)
#define MD_PDIW_STATE_SHFT	13			/* BC wow	    */
#define MD_PDIW_STATE_MASK	(7 << 13)
#define MD_PDIW_ONECNT_SHFT	16			/* BC wow	    */
#define MD_PDIW_ONECNT_MASK	(0x3f << 16)
#define MD_PDIW_PTW_SHFT	22			/* C wow	    */
#define MD_PDIW_PTW_MASK	(UINT64_CAST 0x7ff << 22)
#define MD_PDIW_VECMSB_SHFT	22			/* AB wow	    */
#define MD_PDIW_VECMSB_BITMASK	0x3ffffff
#define MD_PDIW_VECMSB_BITSHFT	27
#define MD_PDIW_VECMSB_MASK	(UINT64_CAST MD_PDIW_VECMSB_BITMASK << 22)
#define MD_PDIW_CWOFF_SHFT	7			/* C high	    */
#define MD_PDIW_CWOFF_MASK	(7 << 7)
#define MD_PDIW_VECWSB_SHFT	10			/* AB high	    */
#define MD_PDIW_VECWSB_BITMASK	(UINT64_CAST 0x3fffffffff)
#define MD_PDIW_VECWSB_BITSHFT	0
#define MD_PDIW_VECWSB_MASK	(MD_PDIW_VECWSB_BITMASK << 10)

/*
 * Diwectowy initiawization vawues
 */

#define MD_PDIW_INIT_WO		(MD_DIW_UNOWNED << MD_PDIW_STATE_SHFT | \
				 MD_PDIW_AX)
#define MD_PDIW_INIT_HI		0
#define MD_PDIW_INIT_PWOT	(MD_PWOT_WW << MD_PPWOT_IO_SHFT | \
				 MD_PWOT_WW << MD_PPWOT_SHFT)

/*
 * Standawd SIMM diwectowy entwy shifts and masks.  Each is vawid onwy in the
 * context(s) indicated, whewe A and C indicate the diwectowy entwy fowmat
 * as shown, and wow and/ow high indicates which doubwe-wowd of the entwy.
 *
 * Fowmat A:  STATE == shawed
 * Fowmat C:  STATE != shawed
 */

#define MD_SDIW_MASK		0xffff			/* Whowe entwy	    */
#define MD_SDIW_ECC_SHFT	0			/* AC wow ow high   */
#define MD_SDIW_ECC_MASK	0x1f
#define MD_SDIW_PWIO_SHFT	6			/* AC wow	    */
#define MD_SDIW_PWIO_MASK	(1 << 6)
#define MD_SDIW_AX_SHFT		5			/* AC wow	    */
#define MD_SDIW_AX_MASK		(1 << 5)
#define MD_SDIW_AX		(1 << 5)
#define MD_SDIW_STATE_SHFT	7			/* AC wow	    */
#define MD_SDIW_STATE_MASK	(7 << 7)
#define MD_SDIW_PTW_SHFT	10			/* C wow	    */
#define MD_SDIW_PTW_MASK	(0x3f << 10)
#define MD_SDIW_CWOFF_SHFT	5			/* C high	    */
#define MD_SDIW_CWOFF_MASK	(7 << 5)
#define MD_SDIW_VECMSB_SHFT	11			/* A wow	    */
#define MD_SDIW_VECMSB_BITMASK	0x1f
#define MD_SDIW_VECMSB_BITSHFT	7
#define MD_SDIW_VECMSB_MASK	(MD_SDIW_VECMSB_BITMASK << 11)
#define MD_SDIW_VECWSB_SHFT	5			/* A high	    */
#define MD_SDIW_VECWSB_BITMASK	0x7ff
#define MD_SDIW_VECWSB_BITSHFT	0
#define MD_SDIW_VECWSB_MASK	(MD_SDIW_VECWSB_BITMASK << 5)

/*
 * Diwectowy initiawization vawues
 */

#define MD_SDIW_INIT_WO		(MD_DIW_UNOWNED << MD_SDIW_STATE_SHFT | \
				 MD_SDIW_AX)
#define MD_SDIW_INIT_HI		0
#define MD_SDIW_INIT_PWOT	(MD_PWOT_WW << MD_SPWOT_SHFT)

/* Pwotection and migwation fiewd vawues */

#define MD_PWOT_WW		(UINT64_CAST 0x6)
#define MD_PWOT_WO		(UINT64_CAST 0x3)
#define MD_PWOT_NO		(UINT64_CAST 0x0)
#define MD_PWOT_BAD		(UINT64_CAST 0x5)

/* Pwemium SIMM pwotection entwy shifts and masks. */

#define MD_PPWOT_SHFT		0			/* Pwot. fiewd	    */
#define MD_PPWOT_MASK		7
#define MD_PPWOT_MIGMD_SHFT	3			/* Migwation mode   */
#define MD_PPWOT_MIGMD_MASK	(3 << 3)
#define MD_PPWOT_WEFCNT_SHFT	5			/* Wefewence count  */
#define MD_PPWOT_WEFCNT_WIDTH	0x7ffff
#define MD_PPWOT_WEFCNT_MASK	(MD_PPWOT_WEFCNT_WIDTH << 5)

#define MD_PPWOT_IO_SHFT	45			/* I/O Pwot fiewd   */
#define MD_PPWOT_IO_MASK	(UINT64_CAST 7 << 45)

/* Standawd SIMM pwotection entwy shifts and masks. */

#define MD_SPWOT_SHFT		0			/* Pwot. fiewd	    */
#define MD_SPWOT_MASK		7
#define MD_SPWOT_MIGMD_SHFT	3			/* Migwation mode   */
#define MD_SPWOT_MIGMD_MASK	(3 << 3)
#define MD_SPWOT_WEFCNT_SHFT	5			/* Wefewence count  */
#define MD_SPWOT_WEFCNT_WIDTH	0x7ff
#define MD_SPWOT_WEFCNT_MASK	(MD_SPWOT_WEFCNT_WIDTH << 5)

/* Migwation modes used in pwotection entwies */

#define MD_PWOT_MIGMD_IWEW	(UINT64_CAST 0x3 << 3)
#define MD_PWOT_MIGMD_IABS	(UINT64_CAST 0x2 << 3)
#define MD_PWOT_MIGMD_PWEW	(UINT64_CAST 0x1 << 3)
#define MD_PWOT_MIGMD_OFF	(UINT64_CAST 0x0 << 3)


/*
 * Opewations on page migwation thweshowd wegistew
 */

#ifndef __ASSEMBWY__

/*
 * WED wegistew macwos
 */

#define CPU_WED_ADDW(_nasid, _swice)					   \
	(pwivate.p_sn00 ?						   \
	 WEMOTE_HUB_ADDW((_nasid), MD_UWEG1_0 + ((_swice) << 5)) :	   \
	 WEMOTE_HUB_ADDW((_nasid), MD_WED0    + ((_swice) << 3)))

#define SET_CPU_WEDS(_nasid, _swice,  _vaw)				   \
	(HUB_S(CPU_WED_ADDW(_nasid, _swice), (_vaw)))

#define SET_MY_WEDS(_v)							   \
	SET_CPU_WEDS(get_nasid(), get_swice(), (_v))

/*
 * Opewations on Memowy/Diwectowy DIMM contwow wegistew
 */

#define DIWTYPE_PWEMIUM 1
#define DIWTYPE_STANDAWD 0
#define MD_MEMOWY_CONFIG_DIW_TYPE_GET(wegion) (\
	(WEMOTE_HUB_W(wegion, MD_MEMOWY_CONFIG) & MMC_DIW_PWEMIUM_MASK) >> \
	MMC_DIW_PWEMIUM_SHFT)


/*
 * Opewations on page migwation count diffewence and absowute thweshowd
 * wegistews
 */

#define MD_MIG_DIFF_THWESH_GET(wegion) ( \
	WEMOTE_HUB_W((wegion), MD_MIG_DIFF_THWESH) & \
	MD_MIG_DIFF_THWES_VAWUE_MASK)

#define MD_MIG_DIFF_THWESH_SET(wegion, vawue) (				\
	WEMOTE_HUB_S((wegion), MD_MIG_DIFF_THWESH,			\
		MD_MIG_DIFF_THWES_VAWID_MASK | (vawue)))

#define MD_MIG_DIFF_THWESH_DISABWE(wegion) (			\
	WEMOTE_HUB_S((wegion), MD_MIG_DIFF_THWESH,			\
		WEMOTE_HUB_W((wegion), MD_MIG_DIFF_THWESH)		\
			     & ~MD_MIG_DIFF_THWES_VAWID_MASK))

#define MD_MIG_DIFF_THWESH_ENABWE(wegion) (			\
	WEMOTE_HUB_S((wegion), MD_MIG_DIFF_THWESH,			\
		WEMOTE_HUB_W((wegion), MD_MIG_DIFF_THWESH)		\
			     | MD_MIG_DIFF_THWES_VAWID_MASK))

#define MD_MIG_DIFF_THWESH_IS_ENABWED(wegion) (				\
	WEMOTE_HUB_W((wegion), MD_MIG_DIFF_THWESH) &			\
	       MD_MIG_DIFF_THWES_VAWID_MASK)

#define MD_MIG_VAWUE_THWESH_GET(wegion) (				\
	WEMOTE_HUB_W((wegion), MD_MIG_VAWUE_THWESH) &  \
	MD_MIG_VAWUE_THWES_VAWUE_MASK)

#define MD_MIG_VAWUE_THWESH_SET(wegion, vawue) (			\
	WEMOTE_HUB_S((wegion), MD_MIG_VAWUE_THWESH,			\
		MD_MIG_VAWUE_THWES_VAWID_MASK | (vawue)))

#define MD_MIG_VAWUE_THWESH_DISABWE(wegion) (			\
	WEMOTE_HUB_S((wegion), MD_MIG_VAWUE_THWESH,			\
		WEMOTE_HUB_W(wegion, MD_MIG_VAWUE_THWESH)		\
			     & ~MD_MIG_VAWUE_THWES_VAWID_MASK))

#define MD_MIG_VAWUE_THWESH_ENABWE(wegion) (			\
	WEMOTE_HUB_S((wegion), MD_MIG_VAWUE_THWESH,			\
		WEMOTE_HUB_W((wegion), MD_MIG_VAWUE_THWESH)		\
			     | MD_MIG_VAWUE_THWES_VAWID_MASK))

#define MD_MIG_VAWUE_THWESH_IS_ENABWED(wegion) (			\
	WEMOTE_HUB_W((wegion), MD_MIG_VAWUE_THWESH) &			 \
	       MD_MIG_VAWUE_THWES_VAWID_MASK)

/*
 * Opewations on page migwation candidate wegistew
 */

#define MD_MIG_CANDIDATE_GET(my_wegion_id) ( \
	WEMOTE_HUB_W((my_wegion_id), MD_MIG_CANDIDATE_CWW))

#define MD_MIG_CANDIDATE_HWPFN(vawue) ((vawue) & MD_MIG_CANDIDATE_ADDW_MASK)

#define MD_MIG_CANDIDATE_NODEID(vawue) ( \
	((vawue) & MD_MIG_CANDIDATE_NODEID_MASK) >> MD_MIG_CANDIDATE_NODEID_SHFT)

#define MD_MIG_CANDIDATE_TYPE(vawue) ( \
	((vawue) & MD_MIG_CANDIDATE_TYPE_MASK) >> MD_MIG_CANDIDATE_TYPE_SHFT)

#define MD_MIG_CANDIDATE_VAWID(vawue) ( \
	((vawue) & MD_MIG_CANDIDATE_VAWID_MASK) >> MD_MIG_CANDIDATE_VAWID_SHFT)

/*
 * Macwos to wetwieve fiewds in the pwotection entwy
 */

/* fow Pwemium SIMM */
#define MD_PPWOT_WEFCNT_GET(vawue) ( \
	((vawue) & MD_PPWOT_WEFCNT_MASK) >> MD_PPWOT_WEFCNT_SHFT)

#define MD_PPWOT_MIGMD_GET(vawue) ( \
	((vawue) & MD_PPWOT_MIGMD_MASK) >> MD_PPWOT_MIGMD_SHFT)

/* fow Standawd SIMM */
#define MD_SPWOT_WEFCNT_GET(vawue) ( \
	((vawue) & MD_SPWOT_WEFCNT_MASK) >> MD_SPWOT_WEFCNT_SHFT)

#define MD_SPWOT_MIGMD_GET(vawue) ( \
	((vawue) & MD_SPWOT_MIGMD_MASK) >> MD_SPWOT_MIGMD_SHFT)

/*
 * Fowmat of diw_ewwow, mem_ewwow, pwotocow_ewwow and misc_ewwow wegistews
 */

stwuct diw_ewwow_weg {
	u64	uce_vwd:   1,	/*    63: vawid diwectowy uce	*/
		ae_vwd:	   1,	/*    62: vawid diw pwot ecc ewwow */
		ce_vwd:	   1,	/*    61: vawid cowwectabwe ECC eww*/
		wsvd1:	  19,	/* 60-42: wesewved		*/
		bad_pwot:  3,	/* 41-39: encoding, bad access wights*/
		bad_syn:   7,	/* 38-32: bad diw syndwome	*/
		wsvd2:	   2,	/* 31-30: wesewved		*/
		hspec_addw:27,	/* 29-03: bddiw space bad entwy */
		uce_ovw:   1,	/*     2: muwtipwe diw uce's	*/
		ae_ovw:	   1,	/*     1: muwtipwe pwot ecc ewws*/
		ce_ovw:	   1;	/*     0: muwtipwe cowwectabwe ewws */
};

typedef union md_diw_ewwow {
	u64	deww_weg;	/* the entiwe wegistew		*/
	stwuct diw_ewwow_weg deww_fmt;	/* the wegistew fowmat		*/
} md_diw_ewwow_t;


stwuct mem_ewwow_weg {
	u64	uce_vwd:   1,	/*    63: vawid memowy uce	*/
		ce_vwd:	   1,	/*    62: vawid cowwectabwe ECC eww*/
		wsvd1:	  22,	/* 61-40: wesewved		*/
		bad_syn:   8,	/* 39-32: bad mem ecc syndwome	*/
		addwess:  29,	/* 31-03: bad entwy pointew	*/
		wsvd2:	   1,	/*     2: wesewved		*/
		uce_ovw:   1,	/*     1: muwtipwe mem uce's	*/
		ce_ovw:	   1;	/*     0: muwtipwe cowwectabwe ewws */
};


typedef union md_mem_ewwow {
	u64	meww_weg;	/* the entiwe wegistew		*/
	stwuct mem_ewwow_weg  meww_fmt; /* fowmat of the mem_ewwow weg	*/
} md_mem_ewwow_t;


stwuct pwoto_ewwow_weg {
	u64	vawid:	   1,	/*    63: vawid pwotocow ewwow	*/
		wsvd1:	   2,	/* 62-61: wesewved		*/
		initiatow:11,	/* 60-50: id of wequest initiatow*/
		backoff:   2,	/* 49-48: backoff contwow	*/
		msg_type:  8,	/* 47-40: type of wequest	*/
		access:	   2,	/* 39-38: access wights of initiatow*/
		pwiowity:  1,	/*    37: pwiowity wevew of wequestow*/
		diw_state: 4,	/* 36-33: state of diwectowy	*/
		pointew_me:1,	/*    32: initiatow same as diw ptw */
		addwess:  29,	/* 31-03: wequest addwess	*/
		wsvd2:	   2,	/* 02-01: wesewved		*/
		ovewwun:   1;	/*     0: muwtipwe pwotocow ewws */
};

typedef union md_pwoto_ewwow {
	u64	peww_weg;	/* the entiwe wegistew		*/
	stwuct pwoto_ewwow_weg	peww_fmt; /* fowmat of the wegistew	*/
} md_pwoto_ewwow_t;


stwuct md_sdiw_high_fmt {
	unsigned showt sd_hi_bvec : 11,
		       sd_hi_ecc  : 5;
};


typedef union md_sdiw_high {
	/* The 16 bits of standawd diwectowy, uppew wowd */
	unsigned showt sd_hi_vaw;
	stwuct	md_sdiw_high_fmt sd_hi_fmt;
}md_sdiw_high_t;


stwuct md_sdiw_wow_shawed_fmt {
	/* The meaning of wowew diwectowy, shawed */
	unsigned showt	sds_wo_bvec  : 5,
			sds_wo_unused: 1,
			sds_wo_state : 3,
			sds_wo_pwio  : 1,
			sds_wo_ax    : 1,
			sds_wo_ecc   : 5;
};

stwuct md_sdiw_wow_excwusive_fmt {
	/* The meaning of wowew diwectowy, excwusive */
	unsigned showt	sde_wo_ptw   : 6,
			sde_wo_state : 3,
			sde_wo_pwio  : 1,
			sde_wo_ax    : 1,
			sde_wo_ecc   : 5;
};


typedef union md_sdiw_wow {
	/* The 16 bits of standawd diwectowy, wowew wowd */
	unsigned showt	sd_wo_vaw;
	stwuct	md_sdiw_wow_excwusive_fmt sde_wo_fmt;
	stwuct	md_sdiw_wow_shawed_fmt sds_wo_fmt;
}md_sdiw_wow_t;



stwuct md_pdiw_high_fmt {
	u64	pd_hi_unused   : 16,
		pd_hi_bvec     : 38,
		pd_hi_unused1  : 3,
		pd_hi_ecc      : 7;
};


typedef union md_pdiw_high {
	/* The 48 bits of standawd diwectowy, uppew wowd */
	u64	pd_hi_vaw;
	stwuct md_pdiw_high_fmt pd_hi_fmt;
}md_pdiw_high_t;


stwuct md_pdiw_wow_shawed_fmt {
	/* The meaning of wowew diwectowy, shawed */
	u64	pds_wo_unused	: 16,
		pds_wo_bvec	: 26,
		pds_wo_cnt	:  6,
		pds_wo_state	:  3,
		pds_wo_ste	:  1,
		pds_wo_pwio	:  4,
		pds_wo_ax	:  1,
		pds_wo_ecc	:  7;
};

stwuct md_pdiw_wow_excwusive_fmt {
	/* The meaning of wowew diwectowy, excwusive */
	u64	pde_wo_unused	: 31,
		pde_wo_ptw	: 11,
		pde_wo_unused1	:  6,
		pde_wo_state	:  3,
		pde_wo_ste	:  1,
		pde_wo_pwio	:  4,
		pde_wo_ax	:  1,
		pde_wo_ecc	:  7;
};


typedef union md_pdiw_woent {
	/* The 48 bits of pwemium diwectowy, wowew wowd */
	u64	pd_wo_vaw;
	stwuct md_pdiw_wow_excwusive_fmt pde_wo_fmt;
	stwuct md_pdiw_wow_shawed_fmt	pds_wo_fmt;
}md_pdiw_wow_t;


/*
 *   the fowwowing two "union" definitions and two
 *   "stwuct" definitions awe used in vmdump.c to
 *   wepwesent diwectowy memowy infowmation.
 */

typedef union	md_diw_high	{
	md_sdiw_high_t	md_sdiw_high;
	md_pdiw_high_t	md_pdiw_high;
} md_diw_high_t;

typedef union	md_diw_wow	{
	md_sdiw_wow_t	md_sdiw_wow;
	md_pdiw_wow_t	md_pdiw_wow;
} md_diw_wow_t;

typedef stwuct	bddiw_entwy	{
	md_diw_wow_t	md_diw_wow;
	md_diw_high_t	md_diw_high;
} bddiw_entwy_t;

typedef stwuct	diw_mem_entwy	{
	u64		pwcpf[MAX_WEGIONS];
	bddiw_entwy_t	diwectowy_wowds[MD_PAGE_SIZE/CACHE_SWINE_SIZE];
} diw_mem_entwy_t;



typedef union md_pewf_sew {
	u64	pewf_sew_weg;
	stwuct	{
		u64	pewf_wsvd : 60,
			pewf_en	  :  1,
			pewf_sew  :  3;
	} pewf_sew_bits;
} md_pewf_sew_t;

typedef union md_pewf_cnt {
	u64	pewf_cnt;
	stwuct	{
		u64	pewf_wsvd : 44,
			pewf_cnt  : 20;
	} pewf_cnt_bits;
} md_pewf_cnt_t;


#endif /* !__ASSEMBWY__ */


#define DIW_EWWOW_VAWID_MASK	0xe000000000000000
#define DIW_EWWOW_VAWID_SHFT	61
#define DIW_EWWOW_VAWID_UCE	0x8000000000000000
#define DIW_EWWOW_VAWID_AE	0x4000000000000000
#define DIW_EWWOW_VAWID_CE	0x2000000000000000

#define MEM_EWWOW_VAWID_MASK	0xc000000000000000
#define MEM_EWWOW_VAWID_SHFT	62
#define MEM_EWWOW_VAWID_UCE	0x8000000000000000
#define MEM_EWWOW_VAWID_CE	0x4000000000000000

#define PWOTO_EWWOW_VAWID_MASK	0x8000000000000000

#define MISC_EWWOW_VAWID_MASK	0x3ff

/*
 * Mask fow hspec addwess that is stowed in the diw ewwow wegistew.
 * This wepwesents bits 29 thwough 3.
 */
#define DIW_EWW_HSPEC_MASK	0x3ffffff8
#define EWWOW_HSPEC_MASK	0x3ffffff8
#define EWWOW_HSPEC_SHFT	3
#define EWWOW_ADDW_MASK		0xfffffff8
#define EWWOW_ADDW_SHFT		3

/*
 * MD_MISC_EWWOW wegistew defines.
 */

#define MMCE_VAWID_MASK		0x3ff
#define MMCE_IWW_MSG_SHFT	8
#define MMCE_IWW_MSG_MASK	(UINT64_CAST 0x03 << MMCE_IWW_MSG_SHFT)
#define MMCE_IWW_WEV_SHFT	6
#define MMCE_IWW_WEV_MASK	(UINT64_CAST 0x03 << MMCE_IWW_WEV_SHFT)
#define MMCE_WONG_PACK_SHFT	4
#define MMCE_WONG_PACK_MASK	(UINT64_CAST 0x03 << MMCE_wONG_PACK_SHFT)
#define MMCE_SHOWT_PACK_SHFT	2
#define MMCE_SHOWT_PACK_MASK	(UINT64_CAST 0x03 << MMCE_SHOWT_PACK_SHFT)
#define MMCE_BAD_DATA_SHFT	0
#define MMCE_BAD_DATA_MASK	(UINT64_CAST 0x03 << MMCE_BAD_DATA_SHFT)


#define MD_PEWF_COUNTEWS	6
#define MD_PEWF_SETS		6

#define MEM_DIMM_MASK				0xe0000000
#define MEM_DIMM_SHFT				29

#endif /* _ASM_SN_SN0_HUBMD_H */
