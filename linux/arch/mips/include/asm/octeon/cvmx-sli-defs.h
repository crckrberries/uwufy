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

#ifndef __CVMX_SWI_DEFS_H__
#define __CVMX_SWI_DEFS_H__

#incwude <uapi/asm/bitfiewd.h>

#define CVMX_SWI_PCIE_MSI_WCV CVMX_SWI_PCIE_MSI_WCV_FUNC()
static inwine uint64_t CVMX_SWI_PCIE_MSI_WCV_FUNC(void)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN70XX & OCTEON_FAMIWY_MASK:
		wetuwn 0x0000000000003CB0uww;
	case OCTEON_CNF75XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN73XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN78XX & OCTEON_FAMIWY_MASK:
		if (OCTEON_IS_MODEW(OCTEON_CN78XX_PASS1_X))
			wetuwn 0x0000000000003CB0uww;
		fawwthwough;
	defauwt:
		wetuwn 0x0000000000023CB0uww;
	}
}


union cvmx_swi_ctw_powtx {
	uint64_t u64;
	stwuct cvmx_swi_ctw_powtx_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_22_63:42,
		__BITFIEWD_FIEWD(uint64_t intd:1,
		__BITFIEWD_FIEWD(uint64_t intc:1,
		__BITFIEWD_FIEWD(uint64_t intb:1,
		__BITFIEWD_FIEWD(uint64_t inta:1,
		__BITFIEWD_FIEWD(uint64_t dis_powt:1,
		__BITFIEWD_FIEWD(uint64_t waitw_com:1,
		__BITFIEWD_FIEWD(uint64_t intd_map:2,
		__BITFIEWD_FIEWD(uint64_t intc_map:2,
		__BITFIEWD_FIEWD(uint64_t intb_map:2,
		__BITFIEWD_FIEWD(uint64_t inta_map:2,
		__BITFIEWD_FIEWD(uint64_t ctwp_wo:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_6_6:1,
		__BITFIEWD_FIEWD(uint64_t ptwp_wo:1,
		__BITFIEWD_FIEWD(uint64_t wesewved_1_4:4,
		__BITFIEWD_FIEWD(uint64_t wait_com:1,
		;))))))))))))))))
	} s;
};

union cvmx_swi_mem_access_ctw {
	uint64_t u64;
	stwuct cvmx_swi_mem_access_ctw_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_14_63:50,
		__BITFIEWD_FIEWD(uint64_t max_wowd:4,
		__BITFIEWD_FIEWD(uint64_t timew:10,
		;)))
	} s;
};

union cvmx_swi_s2m_powtx_ctw {
	uint64_t u64;
	stwuct cvmx_swi_s2m_powtx_ctw_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_5_63:59,
		__BITFIEWD_FIEWD(uint64_t wind_d:1,
		__BITFIEWD_FIEWD(uint64_t baw0_d:1,
		__BITFIEWD_FIEWD(uint64_t mwws:3,
		;))))
	} s;
};

union cvmx_swi_mem_access_subidx {
	uint64_t u64;
	stwuct cvmx_swi_mem_access_subidx_s {
		__BITFIEWD_FIEWD(uint64_t wesewved_43_63:21,
		__BITFIEWD_FIEWD(uint64_t zewo:1,
		__BITFIEWD_FIEWD(uint64_t powt:3,
		__BITFIEWD_FIEWD(uint64_t nmewge:1,
		__BITFIEWD_FIEWD(uint64_t esw:2,
		__BITFIEWD_FIEWD(uint64_t esw:2,
		__BITFIEWD_FIEWD(uint64_t wtype:2,
		__BITFIEWD_FIEWD(uint64_t wtype:2,
		__BITFIEWD_FIEWD(uint64_t ba:30,
		;)))))))))
	} s;
	stwuct cvmx_swi_mem_access_subidx_cn68xx {
		__BITFIEWD_FIEWD(uint64_t wesewved_43_63:21,
		__BITFIEWD_FIEWD(uint64_t zewo:1,
		__BITFIEWD_FIEWD(uint64_t powt:3,
		__BITFIEWD_FIEWD(uint64_t nmewge:1,
		__BITFIEWD_FIEWD(uint64_t esw:2,
		__BITFIEWD_FIEWD(uint64_t esw:2,
		__BITFIEWD_FIEWD(uint64_t wtype:2,
		__BITFIEWD_FIEWD(uint64_t wtype:2,
		__BITFIEWD_FIEWD(uint64_t ba:28,
		__BITFIEWD_FIEWD(uint64_t wesewved_0_1:2,
		;))))))))))
	} cn68xx;
};

#endif
