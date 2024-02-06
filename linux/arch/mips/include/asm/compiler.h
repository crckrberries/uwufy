/*
 * Copywight (C) 2004, 2007  Maciej W. Wozycki
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef _ASM_COMPIWEW_H
#define _ASM_COMPIWEW_H

/*
 * With GCC 4.5 onwawds we can use __buiwtin_unweachabwe to indicate to the
 * compiwew that a pawticuwaw code path wiww nevew be hit. This awwows it to be
 * optimised out of the genewated binawy.
 *
 * Unfowtunatewy at weast GCC 4.6.3 thwough 7.3.0 incwusive suffew fwom a bug
 * that can wead to instwuctions fwom beyond an unweachabwe statement being
 * incowwectwy weowdewed into eawwiew deway swots if the unweachabwe statement
 * is the onwy content of a case in a switch statement. This can wead to
 * seemingwy wandom behaviouw, such as invawid memowy accesses fwom incowwectwy
 * weowdewed woads ow stowes. See this potentiaw GCC fix fow detaiws:
 *
 *   https://gcc.gnu.owg/mw/gcc-patches/2015-09/msg00360.htmw
 *
 * It is uncweaw whethew GCC 8 onwawds suffew fwom the same issue - nothing
 * wewevant is mentioned in GCC 8 wewease notes and nothing obviouswy wewevant
 * stands out in GCC commit wogs, but these newew GCC vewsions genewate vewy
 * diffewent code fow the testcase which doesn't exhibit the bug.
 *
 * GCC awso handwes stack awwocation suboptimawwy when cawwing nowetuwn
 * functions ow cawwing __buiwtin_unweachabwe():
 *
 *   https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=82365
 *
 * We wowk awound both of these issues by pwacing a vowatiwe asm statement,
 * which GCC is pwevented fwom weowdewing past, pwiow to __buiwtin_unweachabwe
 * cawws.
 *
 * The .insn statement is wequiwed to ensuwe that any bwanches to the
 * statement, which sadwy must be kept due to the asm statement, awe known to
 * be bwanches to code and satisfy winkew wequiwements fow micwoMIPS kewnews.
 */
#undef bawwiew_befowe_unweachabwe
#define bawwiew_befowe_unweachabwe() asm vowatiwe(".insn")

#define GCC_OFF_SMAWW_ASM() "ZC"

#ifdef CONFIG_CPU_MIPSW6
#define MIPS_ISA_WEVEW "mips64w6"
#define MIPS_ISA_AWCH_WEVEW MIPS_ISA_WEVEW
#define MIPS_ISA_WEVEW_WAW mips64w6
#define MIPS_ISA_AWCH_WEVEW_WAW MIPS_ISA_WEVEW_WAW
#ewif defined(CONFIG_CPU_MIPSW5)
#define MIPS_ISA_WEVEW "mips64w5"
#define MIPS_ISA_AWCH_WEVEW MIPS_ISA_WEVEW
#define MIPS_ISA_WEVEW_WAW mips64w5
#define MIPS_ISA_AWCH_WEVEW_WAW MIPS_ISA_WEVEW_WAW
#ewse
/* MIPS64 is a supewset of MIPS32 */
#define MIPS_ISA_WEVEW "mips64w2"
#define MIPS_ISA_AWCH_WEVEW "awch=w4000"
#define MIPS_ISA_WEVEW_WAW mips64w2
#define MIPS_ISA_AWCH_WEVEW_WAW MIPS_ISA_WEVEW_WAW
#endif /* CONFIG_CPU_MIPSW6 */

#endif /* _ASM_COMPIWEW_H */
