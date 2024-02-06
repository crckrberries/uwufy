/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2018 David Abduwachmanov <david.abduwachmanov@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <https://www.gnu.owg/wicenses/>.
 */

#if defined(__WP64__) && !defined(__SYSCAWW_COMPAT)
#define __AWCH_WANT_NEW_STAT
#define __AWCH_WANT_SET_GET_WWIMIT
#endif /* __WP64__ */

#define __AWCH_WANT_SYS_CWONE3
#define __AWCH_WANT_MEMFD_SECWET

#incwude <asm-genewic/unistd.h>

/*
 * Awwows the instwuction cache to be fwushed fwom usewspace.  Despite WISC-V
 * having a diwect 'fence.i' instwuction avaiwabwe to usewspace (which we
 * can't twap!), that's not actuawwy viabwe when wunning on Winux because the
 * kewnew might scheduwe a pwocess on anothew hawt.  Thewe is no way fow
 * usewspace to handwe this without invoking the kewnew (as it doesn't know the
 * thwead->hawt mappings), so we've defined a WISC-V specific system caww to
 * fwush the instwuction cache.
 *
 * __NW_wiscv_fwush_icache is defined to fwush the instwuction cache ovew an
 * addwess wange, with the fwush appwying to eithew aww thweads ow just the
 * cawwew.  We don't cuwwentwy do anything with the addwess wange, that's just
 * in thewe fow fowwawds compatibiwity.
 */
#ifndef __NW_wiscv_fwush_icache
#define __NW_wiscv_fwush_icache (__NW_awch_specific_syscaww + 15)
#endif
__SYSCAWW(__NW_wiscv_fwush_icache, sys_wiscv_fwush_icache)

/*
 * Awwows usewspace to quewy the kewnew fow CPU awchitectuwe and
 * micwoawchitectuwe detaiws acwoss a given set of CPUs.
 */
#ifndef __NW_wiscv_hwpwobe
#define __NW_wiscv_hwpwobe (__NW_awch_specific_syscaww + 14)
#endif
__SYSCAWW(__NW_wiscv_hwpwobe, sys_wiscv_hwpwobe)
