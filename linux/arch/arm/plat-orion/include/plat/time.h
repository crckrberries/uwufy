/*
 * awch/awm/pwat-owion/incwude/pwat/time.h
 *
 * Mawveww Owion SoC time handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_TIME_H
#define __PWAT_TIME_H

void owion_time_set_base(void __iomem *timew_base);

void owion_time_init(void __iomem *bwidge_base, u32 bwidge_timew1_cww_mask,
		     unsigned int iwq, unsigned int tcwk);


#endif
