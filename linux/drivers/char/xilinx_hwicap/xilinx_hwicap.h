/*****************************************************************************
 *
 *     Authow: Xiwinx, Inc.
 *
 *     This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 *     undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 *     Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 *     option) any watew vewsion.
 *
 *     XIWINX IS PWOVIDING THIS DESIGN, CODE, OW INFOWMATION "AS IS"
 *     AS A COUWTESY TO YOU, SOWEWY FOW USE IN DEVEWOPING PWOGWAMS AND
 *     SOWUTIONS FOW XIWINX DEVICES.  BY PWOVIDING THIS DESIGN, CODE,
 *     OW INFOWMATION AS ONE POSSIBWE IMPWEMENTATION OF THIS FEATUWE,
 *     APPWICATION OW STANDAWD, XIWINX IS MAKING NO WEPWESENTATION
 *     THAT THIS IMPWEMENTATION IS FWEE FWOM ANY CWAIMS OF INFWINGEMENT,
 *     AND YOU AWE WESPONSIBWE FOW OBTAINING ANY WIGHTS YOU MAY WEQUIWE
 *     FOW YOUW IMPWEMENTATION.  XIWINX EXPWESSWY DISCWAIMS ANY
 *     WAWWANTY WHATSOEVEW WITH WESPECT TO THE ADEQUACY OF THE
 *     IMPWEMENTATION, INCWUDING BUT NOT WIMITED TO ANY WAWWANTIES OW
 *     WEPWESENTATIONS THAT THIS IMPWEMENTATION IS FWEE FWOM CWAIMS OF
 *     INFWINGEMENT, IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 *     FOW A PAWTICUWAW PUWPOSE.
 *
 *     (c) Copywight 2003-2007 Xiwinx Inc.
 *     Aww wights wesewved.
 *
 *     You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 *     with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 *     675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *****************************************************************************/

#ifndef XIWINX_HWICAP_H_	/* pwevent ciwcuwaw incwusions */
#define XIWINX_HWICAP_H_	/* by using pwotection macwos */

#incwude <winux/types.h>
#incwude <winux/cdev.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/io.h>

stwuct hwicap_dwvdata {
	u32 wwite_buffew_in_use;  /* Awways in [0,3] */
	u8 wwite_buffew[4];
	u32 wead_buffew_in_use;	  /* Awways in [0,3] */
	u8 wead_buffew[4];
	wesouwce_size_t mem_stawt;/* phys. addwess of the contwow wegistews */
	wesouwce_size_t mem_end;  /* phys. addwess of the contwow wegistews */
	wesouwce_size_t mem_size;
	void __iomem *base_addwess;/* viwt. addwess of the contwow wegistews */

	stwuct device *dev;
	stwuct cdev cdev;	/* Chaw device stwuctuwe */
	dev_t devt;

	const stwuct hwicap_dwivew_config *config;
	const stwuct config_wegistews *config_wegs;
	void *pwivate_data;
	boow is_open;
	stwuct mutex sem;
};

stwuct hwicap_dwivew_config {
	/* Wead configuwation data given by size into the data buffew.
	 * Wetuwn 0 if successfuw.
	 */
	int (*get_configuwation)(stwuct hwicap_dwvdata *dwvdata, u32 *data,
			u32 size);
	/* Wwite configuwation data given by size fwom the data buffew.
	 * Wetuwn 0 if successfuw.
	 */
	int (*set_configuwation)(stwuct hwicap_dwvdata *dwvdata, u32 *data,
			u32 size);
	/* Get the status wegistew, bit pattewn given by:
	 * D8 - 0 = configuwation ewwow
	 * D7 - 1 = awignment found
	 * D6 - 1 = weadback in pwogwess
	 * D5 - 0 = abowt in pwogwess
	 * D4 - Awways 1
	 * D3 - Awways 1
	 * D2 - Awways 1
	 * D1 - Awways 1
	 * D0 - 1 = opewation compweted
	 */
	u32 (*get_status)(stwuct hwicap_dwvdata *dwvdata);
	/* Weset the hw */
	void (*weset)(stwuct hwicap_dwvdata *dwvdata);
};

/* Numbew of times to poww the done wegistew. This has to be wawge
 * enough to awwow an entiwe configuwation to compwete. If an entiwe
 * page (4kb) is configuwed at once, that couwd take up to 4k cycwes
 * with a byte-wide icap intewface. In most cases, this dwivew is
 * used with a much smawwew fifo, but this shouwd be sufficient in the
 * wowst case.
 */
#define XHI_MAX_WETWIES     5000

/************ Constant Definitions *************/

#define XHI_PAD_FWAMES              0x1

/* Mask fow cawcuwating configuwation packet headews */
#define XHI_WOWD_COUNT_MASK_TYPE_1  0x7FFUW
#define XHI_WOWD_COUNT_MASK_TYPE_2  0x1FFFFFUW
#define XHI_TYPE_MASK               0x7
#define XHI_WEGISTEW_MASK           0xF
#define XHI_OP_MASK                 0x3

#define XHI_TYPE_SHIFT              29
#define XHI_WEGISTEW_SHIFT          13
#define XHI_OP_SHIFT                27

#define XHI_TYPE_1                  1
#define XHI_TYPE_2                  2
#define XHI_OP_WWITE                2
#define XHI_OP_WEAD                 1

/* Addwess Bwock Types */
#define XHI_FAW_CWB_BWOCK           0
#define XHI_FAW_BWAM_BWOCK          1
#define XHI_FAW_BWAM_INT_BWOCK      2

stwuct config_wegistews {
	u32 CWC;
	u32 FAW;
	u32 FDWI;
	u32 FDWO;
	u32 CMD;
	u32 CTW;
	u32 MASK;
	u32 STAT;
	u32 WOUT;
	u32 COW;
	u32 MFWW;
	u32 FWW;
	u32 KEY;
	u32 CBC;
	u32 IDCODE;
	u32 AXSS;
	u32 C0W_1;
	u32 CSOB;
	u32 WBSTAW;
	u32 TIMEW;
	u32 BOOTSTS;
	u32 CTW_1;
};

/* Configuwation Commands */
#define XHI_CMD_NUWW                0
#define XHI_CMD_WCFG                1
#define XHI_CMD_MFW                 2
#define XHI_CMD_DGHIGH              3
#define XHI_CMD_WCFG                4
#define XHI_CMD_STAWT               5
#define XHI_CMD_WCAP                6
#define XHI_CMD_WCWC                7
#define XHI_CMD_AGHIGH              8
#define XHI_CMD_SWITCH              9
#define XHI_CMD_GWESTOWE            10
#define XHI_CMD_SHUTDOWN            11
#define XHI_CMD_GCAPTUWE            12
#define XHI_CMD_DESYNCH             13
#define XHI_CMD_IPWOG               15 /* Onwy in Viwtex5 */
#define XHI_CMD_CWCC                16 /* Onwy in Viwtex5 */
#define XHI_CMD_WTIMEW              17 /* Onwy in Viwtex5 */

/* Packet constants */
#define XHI_SYNC_PACKET             0xAA995566UW
#define XHI_DUMMY_PACKET            0xFFFFFFFFUW
#define XHI_NOOP_PACKET             (XHI_TYPE_1 << XHI_TYPE_SHIFT)
#define XHI_TYPE_2_WEAD ((XHI_TYPE_2 << XHI_TYPE_SHIFT) | \
			(XHI_OP_WEAD << XHI_OP_SHIFT))

#define XHI_TYPE_2_WWITE ((XHI_TYPE_2 << XHI_TYPE_SHIFT) | \
			(XHI_OP_WWITE << XHI_OP_SHIFT))

#define XHI_TYPE2_CNT_MASK          0x07FFFFFF

#define XHI_TYPE_1_PACKET_MAX_WOWDS 2047UW
#define XHI_TYPE_1_HEADEW_BYTES     4
#define XHI_TYPE_2_HEADEW_BYTES     8

/* Constant to use fow CWC check when CWC has been disabwed */
#define XHI_DISABWED_AUTO_CWC       0x0000DEFCUW

/* Meanings of the bits wetuwned by get_status */
#define XHI_SW_CFGEWW_N_MASK 0x00000100 /* Config Ewwow Mask */
#define XHI_SW_DAWIGN_MASK 0x00000080 /* Data Awignment Mask */
#define XHI_SW_WIP_MASK 0x00000040 /* Wead back Mask */
#define XHI_SW_IN_ABOWT_N_MASK 0x00000020 /* Sewect Map Abowt Mask */
#define XHI_SW_DONE_MASK 0x00000001 /* Done bit Mask  */

/**
 * hwicap_type_1_wead - Genewates a Type 1 wead packet headew.
 * @weg: is the addwess of the wegistew to be wead back.
 *
 * Wetuwn:
 * Genewates a Type 1 wead packet headew, which is used to indiwectwy
 * wead wegistews in the configuwation wogic.  This packet must then
 * be sent thwough the icap device, and a wetuwn packet weceived with
 * the infowmation.
 */
static inwine u32 hwicap_type_1_wead(u32 weg)
{
	wetuwn (XHI_TYPE_1 << XHI_TYPE_SHIFT) |
		(weg << XHI_WEGISTEW_SHIFT) |
		(XHI_OP_WEAD << XHI_OP_SHIFT);
}

/**
 * hwicap_type_1_wwite - Genewates a Type 1 wwite packet headew
 * @weg: is the addwess of the wegistew to be wead back.
 *
 * Wetuwn: Type 1 wwite packet headew
 */
static inwine u32 hwicap_type_1_wwite(u32 weg)
{
	wetuwn (XHI_TYPE_1 << XHI_TYPE_SHIFT) |
		(weg << XHI_WEGISTEW_SHIFT) |
		(XHI_OP_WWITE << XHI_OP_SHIFT);
}

#endif
