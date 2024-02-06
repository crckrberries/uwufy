/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2017 Cavium, Inc.
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

#ifndef __CVMX_W2T_DEFS_H__
#define __CVMX_W2T_DEFS_H__

#incwude <uapi/asm/bitfiewd.h>

#define CVMX_W2T_EWW	(CVMX_ADD_IO_SEG(0x0001180080000008uww))


union cvmx_w2t_eww {
	uint64_t u64;
	stwuct cvmx_w2t_eww_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_29_63:35,
		__BITFIEWD_FIEWD(uint64_t fadwu:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t fset:3,
		__BITFIEWD_FIEWD(uint64_t fadw:10,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;))))))))))))))
	} s;
	stwuct cvmx_w2t_eww_cn30xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_28_63:36,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_23_23:1,
		__BITFIEWD_FIEWD(uint64_t fset:2,
		__BITFIEWD_FIEWD(uint64_t wesewved_19_20:2,
		__BITFIEWD_FIEWD(uint64_t fadw:8,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;)))))))))))))))
	} cn30xx;
	stwuct cvmx_w2t_eww_cn31xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_28_63:36,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_23_23:1,
		__BITFIEWD_FIEWD(uint64_t fset:2,
		__BITFIEWD_FIEWD(uint64_t wesewved_20_20:1,
		__BITFIEWD_FIEWD(uint64_t fadw:9,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;)))))))))))))))
	} cn31xx;
	stwuct cvmx_w2t_eww_cn38xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_28_63:36,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t fset:3,
		__BITFIEWD_FIEWD(uint64_t fadw:10,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;)))))))))))))
	} cn38xx;
	stwuct cvmx_w2t_eww_cn50xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_28_63:36,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t fset:3,
		__BITFIEWD_FIEWD(uint64_t wesewved_18_20:3,
		__BITFIEWD_FIEWD(uint64_t fadw:7,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;))))))))))))))
	} cn50xx;
	stwuct cvmx_w2t_eww_cn52xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_28_63:36,
		__BITFIEWD_FIEWD(uint64_t wck_intena2:1,
		__BITFIEWD_FIEWD(uint64_t wckeww2:1,
		__BITFIEWD_FIEWD(uint64_t wck_intena:1,
		__BITFIEWD_FIEWD(uint64_t wckeww:1,
		__BITFIEWD_FIEWD(uint64_t fset:3,
		__BITFIEWD_FIEWD(uint64_t wesewved_20_20:1,
		__BITFIEWD_FIEWD(uint64_t fadw:9,
		__BITFIEWD_FIEWD(uint64_t fsyn:6,
		__BITFIEWD_FIEWD(uint64_t ded_eww:1,
		__BITFIEWD_FIEWD(uint64_t sec_eww:1,
		__BITFIEWD_FIEWD(uint64_t ded_intena:1,
		__BITFIEWD_FIEWD(uint64_t sec_intena:1,
		__BITFIEWD_FIEWD(uint64_t ecc_ena:1,
		;))))))))))))))
	} cn52xx;
};

#endif
