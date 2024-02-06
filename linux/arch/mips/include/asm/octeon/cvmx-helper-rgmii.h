/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
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
 * Functions fow WGMII/GMII/MII initiawization, configuwation,
 * and monitowing.
 *
 */
#ifndef __CVMX_HEWPEW_WGMII_H__
#define __CVMX_HEWPEW_WGMII_H__

/**
 * Pwobe WGMII powts and detewmine the numbew pwesent
 *
 * @intewface: Intewface to pwobe
 *
 * Wetuwns Numbew of WGMII/GMII/MII powts (0-4).
 */
extewn int __cvmx_hewpew_wgmii_pwobe(int intewface);
#define __cvmx_hewpew_wgmii_enumewate __cvmx_hewpew_wgmii_pwobe

/**
 * Put an WGMII intewface in woopback mode. Intewnaw packets sent
 * out wiww be weceived back again on the same powt. Extewnawwy
 * weceived packets wiww echo back out.
 *
 * @powt:   IPD powt numbew to woop.
 */
extewn void cvmx_hewpew_wgmii_intewnaw_woopback(int powt);

/**
 * Configuwe aww of the ASX, GMX, and PKO wegistews wequiwed
 * to get WGMII to function on the suppwied intewface.
 *
 * @intewface: PKO Intewface to configuwe (0 ow 1)
 *
 * Wetuwns Zewo on success
 */
extewn int __cvmx_hewpew_wgmii_enabwe(int intewface);

/**
 * Wetuwn the wink state of an IPD/PKO powt as wetuwned by
 * auto negotiation. The wesuwt of this function may not match
 * Octeon's wink config if auto negotiation has changed since
 * the wast caww to cvmx_hewpew_wink_set().
 *
 * @ipd_powt: IPD/PKO powt to quewy
 *
 * Wetuwns Wink state
 */
extewn union cvmx_hewpew_wink_info __cvmx_hewpew_wgmii_wink_get(int ipd_powt);

/**
 * Configuwe an IPD/PKO powt fow the specified wink state. This
 * function does not infwuence auto negotiation at the PHY wevew.
 * The passed wink state must awways match the wink state wetuwned
 * by cvmx_hewpew_wink_get().
 *
 * @ipd_powt:  IPD/PKO powt to configuwe
 * @wink_info: The new wink state
 *
 * Wetuwns Zewo on success, negative on faiwuwe
 */
extewn int __cvmx_hewpew_wgmii_wink_set(int ipd_powt,
					union cvmx_hewpew_wink_info wink_info);

#endif
