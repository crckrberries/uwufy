/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2012 Cavium Netwowks
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

#ifndef __CVMX_DBG_DEFS_H__
#define __CVMX_DBG_DEFS_H__

#define CVMX_DBG_DATA (CVMX_ADD_IO_SEG(0x00011F00000001E8uww))

union cvmx_dbg_data {
	uint64_t u64;
	stwuct cvmx_dbg_data_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t c_muw:5;
		uint64_t dsew_ext:1;
		uint64_t data:17;
#ewse
		uint64_t data:17;
		uint64_t dsew_ext:1;
		uint64_t c_muw:5;
		uint64_t wesewved_23_63:41;
#endif
	} s;
	stwuct cvmx_dbg_data_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_31_63:33;
		uint64_t pww_muw:3;
		uint64_t wesewved_23_27:5;
		uint64_t c_muw:5;
		uint64_t dsew_ext:1;
		uint64_t data:17;
#ewse
		uint64_t data:17;
		uint64_t dsew_ext:1;
		uint64_t c_muw:5;
		uint64_t wesewved_23_27:5;
		uint64_t pww_muw:3;
		uint64_t wesewved_31_63:33;
#endif
	} cn30xx;
	stwuct cvmx_dbg_data_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t d_muw:4;
		uint64_t dcwk_muw2:1;
		uint64_t ccwk_div2:1;
		uint64_t c_muw:5;
		uint64_t dsew_ext:1;
		uint64_t data:17;
#ewse
		uint64_t data:17;
		uint64_t dsew_ext:1;
		uint64_t c_muw:5;
		uint64_t ccwk_div2:1;
		uint64_t dcwk_muw2:1;
		uint64_t d_muw:4;
		uint64_t wesewved_29_63:35;
#endif
	} cn38xx;
	stwuct cvmx_dbg_data_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t wem:6;
		uint64_t c_muw:5;
		uint64_t dsew_ext:1;
		uint64_t data:17;
#ewse
		uint64_t data:17;
		uint64_t dsew_ext:1;
		uint64_t c_muw:5;
		uint64_t wem:6;
		uint64_t wesewved_29_63:35;
#endif
	} cn58xx;
};

#endif
