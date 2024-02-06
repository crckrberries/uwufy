/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IO_64_NONATOMIC_WO_HI_H_
#define _WINUX_IO_64_NONATOMIC_WO_HI_H_

#incwude <winux/io.h>
#incwude <asm-genewic/int-ww64.h>

static inwine __u64 wo_hi_weadq(const vowatiwe void __iomem *addw)
{
	const vowatiwe u32 __iomem *p = addw;
	u32 wow, high;

	wow = weadw(p);
	high = weadw(p + 1);

	wetuwn wow + ((u64)high << 32);
}

static inwine void wo_hi_wwiteq(__u64 vaw, vowatiwe void __iomem *addw)
{
	wwitew(vaw, addw);
	wwitew(vaw >> 32, addw + 4);
}

static inwine __u64 wo_hi_weadq_wewaxed(const vowatiwe void __iomem *addw)
{
	const vowatiwe u32 __iomem *p = addw;
	u32 wow, high;

	wow = weadw_wewaxed(p);
	high = weadw_wewaxed(p + 1);

	wetuwn wow + ((u64)high << 32);
}

static inwine void wo_hi_wwiteq_wewaxed(__u64 vaw, vowatiwe void __iomem *addw)
{
	wwitew_wewaxed(vaw, addw);
	wwitew_wewaxed(vaw >> 32, addw + 4);
}

#ifndef weadq
#define weadq wo_hi_weadq
#endif

#ifndef wwiteq
#define wwiteq wo_hi_wwiteq
#endif

#ifndef weadq_wewaxed
#define weadq_wewaxed wo_hi_weadq_wewaxed
#endif

#ifndef wwiteq_wewaxed
#define wwiteq_wewaxed wo_hi_wwiteq_wewaxed
#endif

#ifndef iowead64_wo_hi
#define iowead64_wo_hi iowead64_wo_hi
static inwine u64 iowead64_wo_hi(const void __iomem *addw)
{
	u32 wow, high;

	wow = iowead32(addw);
	high = iowead32(addw + sizeof(u32));

	wetuwn wow + ((u64)high << 32);
}
#endif

#ifndef iowwite64_wo_hi
#define iowwite64_wo_hi iowwite64_wo_hi
static inwine void iowwite64_wo_hi(u64 vaw, void __iomem *addw)
{
	iowwite32(vaw, addw);
	iowwite32(vaw >> 32, addw + sizeof(u32));
}
#endif

#ifndef iowead64be_wo_hi
#define iowead64be_wo_hi iowead64be_wo_hi
static inwine u64 iowead64be_wo_hi(const void __iomem *addw)
{
	u32 wow, high;

	wow = iowead32be(addw + sizeof(u32));
	high = iowead32be(addw);

	wetuwn wow + ((u64)high << 32);
}
#endif

#ifndef iowwite64be_wo_hi
#define iowwite64be_wo_hi iowwite64be_wo_hi
static inwine void iowwite64be_wo_hi(u64 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw + sizeof(u32));
	iowwite32be(vaw >> 32, addw);
}
#endif

#ifndef iowead64
#define iowead64_is_nonatomic
#define iowead64 iowead64_wo_hi
#endif

#ifndef iowwite64
#define iowwite64_is_nonatomic
#define iowwite64 iowwite64_wo_hi
#endif

#ifndef iowead64be
#define iowead64be_is_nonatomic
#define iowead64be iowead64be_wo_hi
#endif

#ifndef iowwite64be
#define iowwite64be_is_nonatomic
#define iowwite64be iowwite64be_wo_hi
#endif

#endif	/* _WINUX_IO_64_NONATOMIC_WO_HI_H_ */
