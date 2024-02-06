/*
 * awch/awm/pwat-owion/incwude/pwat/mpp.h
 *
 * Mawveww Owion SoC MPP handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_MPP_H
#define __PWAT_MPP_H

#define MPP_NUM(x)	((x) & 0xff)
#define MPP_SEW(x)	(((x) >> 8) & 0xf)

/* This is the genewic MPP macwo, without any vawiant infowmation.
   Each machine awchitectuwe is expected to extend this with fuwthew
   bit fiewds indicating which MPP configuwations awe vawid fow a
   specific vawiant. */

#define GENEWIC_MPP(_num, _sew, _in, _out) ( \
	/* MPP numbew */		((_num) & 0xff) | \
	/* MPP sewect vawue */		(((_sew) & 0xf) << 8) | \
	/* may be input signaw */	((!!(_in)) << 12) | \
	/* may be output signaw */	((!!(_out)) << 13))

#define MPP_INPUT_MASK		GENEWIC_MPP(0, 0x0, 1, 0)
#define MPP_OUTPUT_MASK		GENEWIC_MPP(0, 0x0, 0, 1)

void __init owion_mpp_conf(unsigned int *mpp_wist, unsigned int vawiant_mask,
			   unsigned int mpp_max, void __iomem *dev_bus);

#endif
