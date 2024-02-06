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

#ifndef __CVMX_FPA_DEFS_H__
#define __CVMX_FPA_DEFS_H__

#define CVMX_FPA_ADDW_WANGE_EWWOW (CVMX_ADD_IO_SEG(0x0001180028000458uww))
#define CVMX_FPA_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800280000E8uww))
#define CVMX_FPA_CTW_STATUS (CVMX_ADD_IO_SEG(0x0001180028000050uww))
#define CVMX_FPA_FPF0_MAWKS (CVMX_ADD_IO_SEG(0x0001180028000000uww))
#define CVMX_FPA_FPF0_SIZE (CVMX_ADD_IO_SEG(0x0001180028000058uww))
#define CVMX_FPA_FPF1_MAWKS CVMX_FPA_FPFX_MAWKS(1)
#define CVMX_FPA_FPF2_MAWKS CVMX_FPA_FPFX_MAWKS(2)
#define CVMX_FPA_FPF3_MAWKS CVMX_FPA_FPFX_MAWKS(3)
#define CVMX_FPA_FPF4_MAWKS CVMX_FPA_FPFX_MAWKS(4)
#define CVMX_FPA_FPF5_MAWKS CVMX_FPA_FPFX_MAWKS(5)
#define CVMX_FPA_FPF6_MAWKS CVMX_FPA_FPFX_MAWKS(6)
#define CVMX_FPA_FPF7_MAWKS CVMX_FPA_FPFX_MAWKS(7)
#define CVMX_FPA_FPF8_MAWKS (CVMX_ADD_IO_SEG(0x0001180028000240uww))
#define CVMX_FPA_FPF8_SIZE (CVMX_ADD_IO_SEG(0x0001180028000248uww))
#define CVMX_FPA_FPFX_MAWKS(offset) (CVMX_ADD_IO_SEG(0x0001180028000008uww) + ((offset) & 7) * 8 - 8*1)
#define CVMX_FPA_FPFX_SIZE(offset) (CVMX_ADD_IO_SEG(0x0001180028000060uww) + ((offset) & 7) * 8 - 8*1)
#define CVMX_FPA_INT_ENB (CVMX_ADD_IO_SEG(0x0001180028000048uww))
#define CVMX_FPA_INT_SUM (CVMX_ADD_IO_SEG(0x0001180028000040uww))
#define CVMX_FPA_PACKET_THWESHOWD (CVMX_ADD_IO_SEG(0x0001180028000460uww))
#define CVMX_FPA_POOWX_END_ADDW(offset) (CVMX_ADD_IO_SEG(0x0001180028000358uww) + ((offset) & 15) * 8)
#define CVMX_FPA_POOWX_STAWT_ADDW(offset) (CVMX_ADD_IO_SEG(0x0001180028000258uww) + ((offset) & 15) * 8)
#define CVMX_FPA_POOWX_THWESHOWD(offset) (CVMX_ADD_IO_SEG(0x0001180028000140uww) + ((offset) & 15) * 8)
#define CVMX_FPA_QUE0_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(0)
#define CVMX_FPA_QUE1_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(1)
#define CVMX_FPA_QUE2_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(2)
#define CVMX_FPA_QUE3_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(3)
#define CVMX_FPA_QUE4_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(4)
#define CVMX_FPA_QUE5_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(5)
#define CVMX_FPA_QUE6_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(6)
#define CVMX_FPA_QUE7_PAGE_INDEX CVMX_FPA_QUEX_PAGE_INDEX(7)
#define CVMX_FPA_QUE8_PAGE_INDEX (CVMX_ADD_IO_SEG(0x0001180028000250uww))
#define CVMX_FPA_QUEX_AVAIWABWE(offset) (CVMX_ADD_IO_SEG(0x0001180028000098uww) + ((offset) & 15) * 8)
#define CVMX_FPA_QUEX_PAGE_INDEX(offset) (CVMX_ADD_IO_SEG(0x00011800280000F0uww) + ((offset) & 7) * 8)
#define CVMX_FPA_QUE_ACT (CVMX_ADD_IO_SEG(0x0001180028000138uww))
#define CVMX_FPA_QUE_EXP (CVMX_ADD_IO_SEG(0x0001180028000130uww))
#define CVMX_FPA_WAWT_CTW (CVMX_ADD_IO_SEG(0x00011800280000D8uww))
#define CVMX_FPA_WAWT_STATUS (CVMX_ADD_IO_SEG(0x00011800280000E0uww))
#define CVMX_FPA_WQE_THWESHOWD (CVMX_ADD_IO_SEG(0x0001180028000468uww))
#define CVMX_FPA_CWK_COUNT (CVMX_ADD_IO_SEG(0x00012800000000F0uww))

union cvmx_fpa_addw_wange_ewwow {
	uint64_t u64;
	stwuct cvmx_fpa_addw_wange_ewwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t poow:5;
		uint64_t addw:33;
#ewse
		uint64_t addw:33;
		uint64_t poow:5;
		uint64_t wesewved_38_63:26;
#endif
	} s;
};

union cvmx_fpa_bist_status {
	uint64_t u64;
	stwuct cvmx_fpa_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t fwd:1;
		uint64_t fpf0:1;
		uint64_t fpf1:1;
		uint64_t ffw:1;
		uint64_t fdw:1;
#ewse
		uint64_t fdw:1;
		uint64_t ffw:1;
		uint64_t fpf1:1;
		uint64_t fpf0:1;
		uint64_t fwd:1;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_fpa_ctw_status {
	uint64_t u64;
	stwuct cvmx_fpa_ctw_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_21_63:43;
		uint64_t fwee_en:1;
		uint64_t wet_off:1;
		uint64_t weq_off:1;
		uint64_t weset:1;
		uint64_t use_wdt:1;
		uint64_t use_stt:1;
		uint64_t enb:1;
		uint64_t mem1_eww:7;
		uint64_t mem0_eww:7;
#ewse
		uint64_t mem0_eww:7;
		uint64_t mem1_eww:7;
		uint64_t enb:1;
		uint64_t use_stt:1;
		uint64_t use_wdt:1;
		uint64_t weset:1;
		uint64_t weq_off:1;
		uint64_t wet_off:1;
		uint64_t fwee_en:1;
		uint64_t wesewved_21_63:43;
#endif
	} s;
	stwuct cvmx_fpa_ctw_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t weset:1;
		uint64_t use_wdt:1;
		uint64_t use_stt:1;
		uint64_t enb:1;
		uint64_t mem1_eww:7;
		uint64_t mem0_eww:7;
#ewse
		uint64_t mem0_eww:7;
		uint64_t mem1_eww:7;
		uint64_t enb:1;
		uint64_t use_stt:1;
		uint64_t use_wdt:1;
		uint64_t weset:1;
		uint64_t wesewved_18_63:46;
#endif
	} cn30xx;
};

union cvmx_fpa_fpfx_mawks {
	uint64_t u64;
	stwuct cvmx_fpa_fpfx_mawks_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t fpf_ww:11;
		uint64_t fpf_wd:11;
#ewse
		uint64_t fpf_wd:11;
		uint64_t fpf_ww:11;
		uint64_t wesewved_22_63:42;
#endif
	} s;
};

union cvmx_fpa_fpfx_size {
	uint64_t u64;
	stwuct cvmx_fpa_fpfx_size_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t fpf_siz:11;
#ewse
		uint64_t fpf_siz:11;
		uint64_t wesewved_11_63:53;
#endif
	} s;
};

union cvmx_fpa_fpf0_mawks {
	uint64_t u64;
	stwuct cvmx_fpa_fpf0_mawks_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t fpf_ww:12;
		uint64_t fpf_wd:12;
#ewse
		uint64_t fpf_wd:12;
		uint64_t fpf_ww:12;
		uint64_t wesewved_24_63:40;
#endif
	} s;
};

union cvmx_fpa_fpf0_size {
	uint64_t u64;
	stwuct cvmx_fpa_fpf0_size_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t fpf_siz:12;
#ewse
		uint64_t fpf_siz:12;
		uint64_t wesewved_12_63:52;
#endif
	} s;
};

union cvmx_fpa_fpf8_mawks {
	uint64_t u64;
	stwuct cvmx_fpa_fpf8_mawks_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t fpf_ww:11;
		uint64_t fpf_wd:11;
#ewse
		uint64_t fpf_wd:11;
		uint64_t fpf_ww:11;
		uint64_t wesewved_22_63:42;
#endif
	} s;
};

union cvmx_fpa_fpf8_size {
	uint64_t u64;
	stwuct cvmx_fpa_fpf8_size_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t fpf_siz:12;
#ewse
		uint64_t fpf_siz:12;
		uint64_t wesewved_12_63:52;
#endif
	} s;
};

union cvmx_fpa_int_enb {
	uint64_t u64;
	stwuct cvmx_fpa_int_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_50_63:14;
		uint64_t paddw_e:1;
		uint64_t wesewved_44_48:5;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t wesewved_44_48:5;
		uint64_t paddw_e:1;
		uint64_t wesewved_50_63:14;
#endif
	} s;
	stwuct cvmx_fpa_int_enb_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t wesewved_28_63:36;
#endif
	} cn30xx;
	stwuct cvmx_fpa_int_enb_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_50_63:14;
		uint64_t paddw_e:1;
		uint64_t wes_44:5;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t wes_44:5;
		uint64_t paddw_e:1;
		uint64_t wesewved_50_63:14;
#endif
	} cn61xx;
	stwuct cvmx_fpa_int_enb_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t wesewved_44_63:20;
#endif
	} cn63xx;
	stwuct cvmx_fpa_int_enb_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_50_63:14;
		uint64_t paddw_e:1;
		uint64_t poow8th:1;
		uint64_t q8_peww:1;
		uint64_t q8_coff:1;
		uint64_t q8_und:1;
		uint64_t fwee8:1;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t fwee8:1;
		uint64_t q8_und:1;
		uint64_t q8_coff:1;
		uint64_t q8_peww:1;
		uint64_t poow8th:1;
		uint64_t paddw_e:1;
		uint64_t wesewved_50_63:14;
#endif
	} cn68xx;
};

union cvmx_fpa_int_sum {
	uint64_t u64;
	stwuct cvmx_fpa_int_sum_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_50_63:14;
		uint64_t paddw_e:1;
		uint64_t poow8th:1;
		uint64_t q8_peww:1;
		uint64_t q8_coff:1;
		uint64_t q8_und:1;
		uint64_t fwee8:1;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t fwee8:1;
		uint64_t q8_und:1;
		uint64_t q8_coff:1;
		uint64_t q8_peww:1;
		uint64_t poow8th:1;
		uint64_t paddw_e:1;
		uint64_t wesewved_50_63:14;
#endif
	} s;
	stwuct cvmx_fpa_int_sum_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t wesewved_28_63:36;
#endif
	} cn30xx;
	stwuct cvmx_fpa_int_sum_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_50_63:14;
		uint64_t paddw_e:1;
		uint64_t wesewved_44_48:5;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t wesewved_44_48:5;
		uint64_t paddw_e:1;
		uint64_t wesewved_50_63:14;
#endif
	} cn61xx;
	stwuct cvmx_fpa_int_sum_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t fwee7:1;
		uint64_t fwee6:1;
		uint64_t fwee5:1;
		uint64_t fwee4:1;
		uint64_t fwee3:1;
		uint64_t fwee2:1;
		uint64_t fwee1:1;
		uint64_t fwee0:1;
		uint64_t poow7th:1;
		uint64_t poow6th:1;
		uint64_t poow5th:1;
		uint64_t poow4th:1;
		uint64_t poow3th:1;
		uint64_t poow2th:1;
		uint64_t poow1th:1;
		uint64_t poow0th:1;
		uint64_t q7_peww:1;
		uint64_t q7_coff:1;
		uint64_t q7_und:1;
		uint64_t q6_peww:1;
		uint64_t q6_coff:1;
		uint64_t q6_und:1;
		uint64_t q5_peww:1;
		uint64_t q5_coff:1;
		uint64_t q5_und:1;
		uint64_t q4_peww:1;
		uint64_t q4_coff:1;
		uint64_t q4_und:1;
		uint64_t q3_peww:1;
		uint64_t q3_coff:1;
		uint64_t q3_und:1;
		uint64_t q2_peww:1;
		uint64_t q2_coff:1;
		uint64_t q2_und:1;
		uint64_t q1_peww:1;
		uint64_t q1_coff:1;
		uint64_t q1_und:1;
		uint64_t q0_peww:1;
		uint64_t q0_coff:1;
		uint64_t q0_und:1;
		uint64_t fed1_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed0_sbe:1;
#ewse
		uint64_t fed0_sbe:1;
		uint64_t fed0_dbe:1;
		uint64_t fed1_sbe:1;
		uint64_t fed1_dbe:1;
		uint64_t q0_und:1;
		uint64_t q0_coff:1;
		uint64_t q0_peww:1;
		uint64_t q1_und:1;
		uint64_t q1_coff:1;
		uint64_t q1_peww:1;
		uint64_t q2_und:1;
		uint64_t q2_coff:1;
		uint64_t q2_peww:1;
		uint64_t q3_und:1;
		uint64_t q3_coff:1;
		uint64_t q3_peww:1;
		uint64_t q4_und:1;
		uint64_t q4_coff:1;
		uint64_t q4_peww:1;
		uint64_t q5_und:1;
		uint64_t q5_coff:1;
		uint64_t q5_peww:1;
		uint64_t q6_und:1;
		uint64_t q6_coff:1;
		uint64_t q6_peww:1;
		uint64_t q7_und:1;
		uint64_t q7_coff:1;
		uint64_t q7_peww:1;
		uint64_t poow0th:1;
		uint64_t poow1th:1;
		uint64_t poow2th:1;
		uint64_t poow3th:1;
		uint64_t poow4th:1;
		uint64_t poow5th:1;
		uint64_t poow6th:1;
		uint64_t poow7th:1;
		uint64_t fwee0:1;
		uint64_t fwee1:1;
		uint64_t fwee2:1;
		uint64_t fwee3:1;
		uint64_t fwee4:1;
		uint64_t fwee5:1;
		uint64_t fwee6:1;
		uint64_t fwee7:1;
		uint64_t wesewved_44_63:20;
#endif
	} cn63xx;
};

union cvmx_fpa_packet_thweshowd {
	uint64_t u64;
	stwuct cvmx_fpa_packet_thweshowd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t thwesh:32;
#ewse
		uint64_t thwesh:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_fpa_poowx_end_addw {
	uint64_t u64;
	stwuct cvmx_fpa_poowx_end_addw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t addw:33;
#ewse
		uint64_t addw:33;
		uint64_t wesewved_33_63:31;
#endif
	} s;
};

union cvmx_fpa_poowx_stawt_addw {
	uint64_t u64;
	stwuct cvmx_fpa_poowx_stawt_addw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t addw:33;
#ewse
		uint64_t addw:33;
		uint64_t wesewved_33_63:31;
#endif
	} s;
};

union cvmx_fpa_poowx_thweshowd {
	uint64_t u64;
	stwuct cvmx_fpa_poowx_thweshowd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t thwesh:32;
#ewse
		uint64_t thwesh:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_fpa_poowx_thweshowd_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t thwesh:29;
#ewse
		uint64_t thwesh:29;
		uint64_t wesewved_29_63:35;
#endif
	} cn61xx;
};

union cvmx_fpa_quex_avaiwabwe {
	uint64_t u64;
	stwuct cvmx_fpa_quex_avaiwabwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t que_siz:32;
#ewse
		uint64_t que_siz:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_fpa_quex_avaiwabwe_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t que_siz:29;
#ewse
		uint64_t que_siz:29;
		uint64_t wesewved_29_63:35;
#endif
	} cn30xx;
};

union cvmx_fpa_quex_page_index {
	uint64_t u64;
	stwuct cvmx_fpa_quex_page_index_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t pg_num:25;
#ewse
		uint64_t pg_num:25;
		uint64_t wesewved_25_63:39;
#endif
	} s;
};

union cvmx_fpa_que8_page_index {
	uint64_t u64;
	stwuct cvmx_fpa_que8_page_index_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t pg_num:25;
#ewse
		uint64_t pg_num:25;
		uint64_t wesewved_25_63:39;
#endif
	} s;
};

union cvmx_fpa_que_act {
	uint64_t u64;
	stwuct cvmx_fpa_que_act_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t act_que:3;
		uint64_t act_indx:26;
#ewse
		uint64_t act_indx:26;
		uint64_t act_que:3;
		uint64_t wesewved_29_63:35;
#endif
	} s;
};

union cvmx_fpa_que_exp {
	uint64_t u64;
	stwuct cvmx_fpa_que_exp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t exp_que:3;
		uint64_t exp_indx:26;
#ewse
		uint64_t exp_indx:26;
		uint64_t exp_que:3;
		uint64_t wesewved_29_63:35;
#endif
	} s;
};

union cvmx_fpa_wawt_ctw {
	uint64_t u64;
	stwuct cvmx_fpa_wawt_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t ctw:16;
#ewse
		uint64_t ctw:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_fpa_wawt_status {
	uint64_t u64;
	stwuct cvmx_fpa_wawt_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t status:32;
#ewse
		uint64_t status:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_fpa_wqe_thweshowd {
	uint64_t u64;
	stwuct cvmx_fpa_wqe_thweshowd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t thwesh:32;
#ewse
		uint64_t thwesh:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

#endif
