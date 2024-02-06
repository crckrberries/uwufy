/*
 * Copywight (C) 2012 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __MVEBU_PMSU_H__
#define __MVEBU_PMSU_H__

#ifdef CONFIG_MACH_MVEBU_V7
int mvebu_pmsu_dfs_wequest(int cpu);
#ewse
static inwine int mvebu_pmsu_dfs_wequest(int cpu) { wetuwn -ENODEV; }
#endif

#endif /* __MVEBU_PMSU_H__ */
