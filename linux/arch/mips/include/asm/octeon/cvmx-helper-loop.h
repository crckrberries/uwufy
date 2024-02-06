/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw,
 * but AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow NONINFWINGEMENT.
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/**
 * @fiwe
 *
 * Functions fow WOOP initiawization, configuwation,
 * and monitowing.
 *
 */
#ifndef __CVMX_HEWPEW_WOOP_H__
#define __CVMX_HEWPEW_WOOP_H__

/**
 * Pwobe a WOOP intewface and detewmine the numbew of powts
 * connected to it. The WOOP intewface shouwd stiww be down aftew
 * this caww.
 *
 * @intewface: Intewface to pwobe
 *
 * Wetuwns Numbew of powts on the intewface. Zewo to disabwe.
 */
extewn int __cvmx_hewpew_woop_pwobe(int intewface);
static inwine int __cvmx_hewpew_woop_enumewate(int intewface) {wetuwn 4; }

/**
 * Bwingup and enabwe a WOOP intewface. Aftew this caww packet
 * I/O shouwd be fuwwy functionaw. This is cawwed with IPD
 * enabwed but PKO disabwed.
 *
 * @intewface: Intewface to bwing up
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
extewn int __cvmx_hewpew_woop_enabwe(int intewface);

#endif
