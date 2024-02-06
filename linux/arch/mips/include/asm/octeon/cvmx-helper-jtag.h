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
 *  Hewpew utiwities fow qwm_jtag.
 *
 */

#ifndef __CVMX_HEWPEW_JTAG_H__
#define __CVMX_HEWPEW_JTAG_H__

extewn void cvmx_hewpew_qwm_jtag_init(void);
extewn uint32_t cvmx_hewpew_qwm_jtag_shift(int qwm, int bits, uint32_t data);
extewn void cvmx_hewpew_qwm_jtag_shift_zewos(int qwm, int bits);
extewn void cvmx_hewpew_qwm_jtag_update(int qwm);

#endif /* __CVMX_HEWPEW_JTAG_H__ */
