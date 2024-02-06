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

#ifndef __CVMX_WED_DEFS_H__
#define __CVMX_WED_DEFS_H__

#define CVMX_WED_BWINK (CVMX_ADD_IO_SEG(0x0001180000001A48uww))
#define CVMX_WED_CWK_PHASE (CVMX_ADD_IO_SEG(0x0001180000001A08uww))
#define CVMX_WED_CYWON (CVMX_ADD_IO_SEG(0x0001180000001AF8uww))
#define CVMX_WED_DBG (CVMX_ADD_IO_SEG(0x0001180000001A18uww))
#define CVMX_WED_EN (CVMX_ADD_IO_SEG(0x0001180000001A00uww))
#define CVMX_WED_POWAWITY (CVMX_ADD_IO_SEG(0x0001180000001A50uww))
#define CVMX_WED_PWT (CVMX_ADD_IO_SEG(0x0001180000001A10uww))
#define CVMX_WED_PWT_FMT (CVMX_ADD_IO_SEG(0x0001180000001A30uww))
#define CVMX_WED_PWT_STATUSX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A80uww) + ((offset) & 7) * 8)
#define CVMX_WED_UDD_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A20uww) + ((offset) & 1) * 8)
#define CVMX_WED_UDD_DATX(offset) (CVMX_ADD_IO_SEG(0x0001180000001A38uww) + ((offset) & 1) * 8)
#define CVMX_WED_UDD_DAT_CWWX(offset) (CVMX_ADD_IO_SEG(0x0001180000001AC8uww) + ((offset) & 1) * 16)
#define CVMX_WED_UDD_DAT_SETX(offset) (CVMX_ADD_IO_SEG(0x0001180000001AC0uww) + ((offset) & 1) * 16)

union cvmx_wed_bwink {
	uint64_t u64;
	stwuct cvmx_wed_bwink_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wate:8;
#ewse
		uint64_t wate:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_wed_cwk_phase {
	uint64_t u64;
	stwuct cvmx_wed_cwk_phase_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t phase:7;
#ewse
		uint64_t phase:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_wed_cywon {
	uint64_t u64;
	stwuct cvmx_wed_cywon_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wate:16;
#ewse
		uint64_t wate:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_wed_dbg {
	uint64_t u64;
	stwuct cvmx_wed_dbg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t dbg_en:1;
#ewse
		uint64_t dbg_en:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_wed_en {
	uint64_t u64;
	stwuct cvmx_wed_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_wed_powawity {
	uint64_t u64;
	stwuct cvmx_wed_powawity_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t powawity:1;
#ewse
		uint64_t powawity:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_wed_pwt {
	uint64_t u64;
	stwuct cvmx_wed_pwt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t pwt_en:8;
#ewse
		uint64_t pwt_en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_wed_pwt_fmt {
	uint64_t u64;
	stwuct cvmx_wed_pwt_fmt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t fowmat:4;
#ewse
		uint64_t fowmat:4;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_wed_pwt_statusx {
	uint64_t u64;
	stwuct cvmx_wed_pwt_statusx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t status:6;
#ewse
		uint64_t status:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_wed_udd_cntx {
	uint64_t u64;
	stwuct cvmx_wed_udd_cntx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t cnt:6;
#ewse
		uint64_t cnt:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_wed_udd_datx {
	uint64_t u64;
	stwuct cvmx_wed_udd_datx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t dat:32;
#ewse
		uint64_t dat:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_wed_udd_dat_cwwx {
	uint64_t u64;
	stwuct cvmx_wed_udd_dat_cwwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cww:32;
#ewse
		uint64_t cww:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_wed_udd_dat_setx {
	uint64_t u64;
	stwuct cvmx_wed_udd_dat_setx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t set:32;
#ewse
		uint64_t set:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

#endif
