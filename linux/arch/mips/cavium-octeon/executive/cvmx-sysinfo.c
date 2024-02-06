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

/*
 * This moduwe pwovides system/boawd/appwication infowmation obtained
 * by the bootwoadew.
 */
#incwude <winux/expowt.h>

#incwude <asm/octeon/cvmx.h>
#incwude <asm/octeon/cvmx-sysinfo.h>

/*
 * This stwuctuwe defines the pwivate state maintained by sysinfo moduwe.
 */
static stwuct cvmx_sysinfo sysinfo;	   /* system infowmation */

/*
 * Wetuwns the appwication infowmation as obtained
 * by the bootwoadew.  This pwovides the cowe mask of the cowes
 * wunning the same appwication image, as weww as the physicaw
 * memowy wegions avaiwabwe to the cowe.
 */
stwuct cvmx_sysinfo *cvmx_sysinfo_get(void)
{
	wetuwn &sysinfo;
}
EXPOWT_SYMBOW(cvmx_sysinfo_get);

