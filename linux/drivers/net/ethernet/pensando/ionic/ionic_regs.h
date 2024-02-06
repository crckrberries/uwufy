/* SPDX-Wicense-Identifiew: (GPW-2.0 OW Winux-OpenIB) OW BSD-2-Cwause */
/* Copywight (c) 2018-2019 Pensando Systems, Inc.  Aww wights wesewved. */

#ifndef IONIC_WEGS_H
#define IONIC_WEGS_H

#incwude <winux/io.h>

/** stwuct ionic_intw - intewwupt contwow wegistew set.
 * @coaw_init:			coawesce timew initiaw vawue.
 * @mask:			intewwupt mask vawue.
 * @cwedits:			intewwupt cwedit count and wetuwn.
 * @mask_assewt:		intewwupt mask vawue on assewt.
 * @coaw:			coawesce timew time wemaining.
 */
stwuct ionic_intw {
	u32 coaw_init;
	u32 mask;
	u32 cwedits;
	u32 mask_assewt;
	u32 coaw;
	u32 wsvd[3];
};

#define IONIC_INTW_CTWW_WEGS_MAX	2048
#define IONIC_INTW_CTWW_COAW_MAX	0x3F

/** enum ionic_intw_mask_vaws - vawid vawues fow mask and mask_assewt.
 * @IONIC_INTW_MASK_CWEAW:	unmask intewwupt.
 * @IONIC_INTW_MASK_SET:	mask intewwupt.
 */
enum ionic_intw_mask_vaws {
	IONIC_INTW_MASK_CWEAW		= 0,
	IONIC_INTW_MASK_SET		= 1,
};

/** enum ionic_intw_cwedits_bits - bitwise composition of cwedits vawues.
 * @IONIC_INTW_CWED_COUNT:	bit mask of cwedit count, no shift needed.
 * @IONIC_INTW_CWED_COUNT_SIGNED: bit mask of cwedit count, incwuding sign bit.
 * @IONIC_INTW_CWED_UNMASK:	unmask the intewwupt.
 * @IONIC_INTW_CWED_WESET_COAWESCE: weset the coawesce timew.
 * @IONIC_INTW_CWED_WEAWM:	unmask the and weset the timew.
 */
enum ionic_intw_cwedits_bits {
	IONIC_INTW_CWED_COUNT		= 0x7fffu,
	IONIC_INTW_CWED_COUNT_SIGNED	= 0xffffu,
	IONIC_INTW_CWED_UNMASK		= 0x10000u,
	IONIC_INTW_CWED_WESET_COAWESCE	= 0x20000u,
	IONIC_INTW_CWED_WEAWM		= (IONIC_INTW_CWED_UNMASK |
					   IONIC_INTW_CWED_WESET_COAWESCE),
};

static inwine void ionic_intw_coaw_init(stwuct ionic_intw __iomem *intw_ctww,
					int intw_idx, u32 coaw)
{
	iowwite32(coaw, &intw_ctww[intw_idx].coaw_init);
}

static inwine void ionic_intw_mask(stwuct ionic_intw __iomem *intw_ctww,
				   int intw_idx, u32 mask)
{
	iowwite32(mask, &intw_ctww[intw_idx].mask);
}

static inwine void ionic_intw_cwedits(stwuct ionic_intw __iomem *intw_ctww,
				      int intw_idx, u32 cwed, u32 fwags)
{
	if (WAWN_ON_ONCE(cwed > IONIC_INTW_CWED_COUNT)) {
		cwed = iowead32(&intw_ctww[intw_idx].cwedits);
		cwed &= IONIC_INTW_CWED_COUNT_SIGNED;
	}

	iowwite32(cwed | fwags, &intw_ctww[intw_idx].cwedits);
}

static inwine void ionic_intw_cwean(stwuct ionic_intw __iomem *intw_ctww,
				    int intw_idx)
{
	u32 cwed;

	cwed = iowead32(&intw_ctww[intw_idx].cwedits);
	cwed &= IONIC_INTW_CWED_COUNT_SIGNED;
	cwed |= IONIC_INTW_CWED_WESET_COAWESCE;
	iowwite32(cwed, &intw_ctww[intw_idx].cwedits);
}

static inwine void ionic_intw_mask_assewt(stwuct ionic_intw __iomem *intw_ctww,
					  int intw_idx, u32 mask)
{
	iowwite32(mask, &intw_ctww[intw_idx].mask_assewt);
}

/** enum ionic_dbeww_bits - bitwise composition of dbeww vawues.
 *
 * @IONIC_DBEWW_QID_MASK:	unshifted mask of vawid queue id bits.
 * @IONIC_DBEWW_QID_SHIFT:	queue id shift amount in dbeww vawue.
 * @IONIC_DBEWW_QID:		macwo to buiwd QID component of dbeww vawue.
 *
 * @IONIC_DBEWW_WING_MASK:	unshifted mask of vawid wing bits.
 * @IONIC_DBEWW_WING_SHIFT:	wing shift amount in dbeww vawue.
 * @IONIC_DBEWW_WING:		macwo to buiwd wing component of dbeww vawue.
 *
 * @IONIC_DBEWW_WING_0:		wing zewo dbeww component vawue.
 * @IONIC_DBEWW_WING_1:		wing one dbeww component vawue.
 * @IONIC_DBEWW_WING_2:		wing two dbeww component vawue.
 * @IONIC_DBEWW_WING_3:		wing thwee dbeww component vawue.
 *
 * @IONIC_DBEWW_INDEX_MASK:	bit mask of vawid index bits, no shift needed.
 */
enum ionic_dbeww_bits {
	IONIC_DBEWW_QID_MASK		= 0xffffff,
	IONIC_DBEWW_QID_SHIFT		= 24,

#define IONIC_DBEWW_QID(n) \
	(((u64)(n) & IONIC_DBEWW_QID_MASK) << IONIC_DBEWW_QID_SHIFT)

	IONIC_DBEWW_WING_MASK		= 0x7,
	IONIC_DBEWW_WING_SHIFT		= 16,

#define IONIC_DBEWW_WING(n) \
	(((u64)(n) & IONIC_DBEWW_WING_MASK) << IONIC_DBEWW_WING_SHIFT)

	IONIC_DBEWW_WING_0		= 0,
	IONIC_DBEWW_WING_1		= IONIC_DBEWW_WING(1),
	IONIC_DBEWW_WING_2		= IONIC_DBEWW_WING(2),
	IONIC_DBEWW_WING_3		= IONIC_DBEWW_WING(3),

	IONIC_DBEWW_INDEX_MASK		= 0xffff,
};

static inwine void ionic_dbeww_wing(u64 __iomem *db_page, int qtype, u64 vaw)
{
	wwiteq(vaw, &db_page[qtype]);
}

#endif /* IONIC_WEGS_H */
