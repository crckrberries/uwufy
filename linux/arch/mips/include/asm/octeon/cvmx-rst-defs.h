/***********************wicense stawt***************
 * Authow: Cavium Inc.
 *
 * Contact: suppowt@cavium.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2014 Cavium Inc.
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
 * Contact Cavium Inc. fow mowe infowmation
 ***********************wicense end**************************************/

#ifndef __CVMX_WST_DEFS_H__
#define __CVMX_WST_DEFS_H__

#define CVMX_WST_BOOT (CVMX_ADD_IO_SEG(0x0001180006001600uww))
#define CVMX_WST_CFG (CVMX_ADD_IO_SEG(0x0001180006001610uww))
#define CVMX_WST_CKIWW (CVMX_ADD_IO_SEG(0x0001180006001638uww))
#define CVMX_WST_CTWX(offset) (CVMX_ADD_IO_SEG(0x0001180006001640uww) + ((offset) & 3) * 8)
#define CVMX_WST_DEWAY (CVMX_ADD_IO_SEG(0x0001180006001608uww))
#define CVMX_WST_ECO (CVMX_ADD_IO_SEG(0x00011800060017B8uww))
#define CVMX_WST_INT (CVMX_ADD_IO_SEG(0x0001180006001628uww))
#define CVMX_WST_OCX (CVMX_ADD_IO_SEG(0x0001180006001618uww))
#define CVMX_WST_POWEW_DBG (CVMX_ADD_IO_SEG(0x0001180006001708uww))
#define CVMX_WST_PP_POWEW (CVMX_ADD_IO_SEG(0x0001180006001700uww))
#define CVMX_WST_SOFT_PWSTX(offset) (CVMX_ADD_IO_SEG(0x00011800060016C0uww) + ((offset) & 3) * 8)
#define CVMX_WST_SOFT_WST (CVMX_ADD_IO_SEG(0x0001180006001680uww))

union cvmx_wst_boot {
	uint64_t u64;
	stwuct cvmx_wst_boot_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t chipkiww:1;
		uint64_t jtcswdis:1;
		uint64_t ejtagdis:1;
		uint64_t women:1;
		uint64_t ckiww_ppdis:1;
		uint64_t jt_tstmode:1;
		uint64_t vwm_eww:1;
		uint64_t wesewved_37_56:20;
		uint64_t c_muw:7;
		uint64_t pnw_muw:6;
		uint64_t wesewved_21_23:3;
		uint64_t wboot_oci:3;
		uint64_t wboot_ext:6;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t wboot_ext:6;
		uint64_t wboot_oci:3;
		uint64_t wesewved_21_23:3;
		uint64_t pnw_muw:6;
		uint64_t c_muw:7;
		uint64_t wesewved_37_56:20;
		uint64_t vwm_eww:1;
		uint64_t jt_tstmode:1;
		uint64_t ckiww_ppdis:1;
		uint64_t women:1;
		uint64_t ejtagdis:1;
		uint64_t jtcswdis:1;
		uint64_t chipkiww:1;
#endif
	} s;
};

union cvmx_wst_cfg {
	uint64_t u64;
	stwuct cvmx_wst_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bist_deway:58;
		uint64_t wesewved_3_5:3;
		uint64_t cntw_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t soft_cww_bist:1;
#ewse
		uint64_t soft_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t cntw_cww_bist:1;
		uint64_t wesewved_3_5:3;
		uint64_t bist_deway:58;
#endif
	} s;
};

union cvmx_wst_ckiww {
	uint64_t u64;
	stwuct cvmx_wst_ckiww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_47_63:17;
		uint64_t timew:47;
#ewse
		uint64_t timew:47;
		uint64_t wesewved_47_63:17;
#endif
	} s;
};

union cvmx_wst_ctwx {
	uint64_t u64;
	stwuct cvmx_wst_ctwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pwst_wink:1;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t wesewved_4_5:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t wesewved_4_5:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t pwst_wink:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_wst_deway {
	uint64_t u64;
	stwuct cvmx_wst_deway_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wawm_wst_dwy:16;
		uint64_t soft_wst_dwy:16;
#ewse
		uint64_t soft_wst_dwy:16;
		uint64_t wawm_wst_dwy:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_wst_eco {
	uint64_t u64;
	stwuct cvmx_wst_eco_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t eco_ww:32;
#ewse
		uint64_t eco_ww:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_wst_int {
	uint64_t u64;
	stwuct cvmx_wst_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t pewst:4;
		uint64_t wesewved_4_7:4;
		uint64_t wst_wink:4;
#ewse
		uint64_t wst_wink:4;
		uint64_t wesewved_4_7:4;
		uint64_t pewst:4;
		uint64_t wesewved_12_63:52;
#endif
	} s;
	stwuct cvmx_wst_int_cn70xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t pewst:3;
		uint64_t wesewved_3_7:5;
		uint64_t wst_wink:3;
#ewse
		uint64_t wst_wink:3;
		uint64_t wesewved_3_7:5;
		uint64_t pewst:3;
		uint64_t wesewved_11_63:53;
#endif
	} cn70xx;
};

union cvmx_wst_ocx {
	uint64_t u64;
	stwuct cvmx_wst_ocx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t wst_wink:3;
#ewse
		uint64_t wst_wink:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_wst_powew_dbg {
	uint64_t u64;
	stwuct cvmx_wst_powew_dbg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t stw:3;
#ewse
		uint64_t stw:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_wst_pp_powew {
	uint64_t u64;
	stwuct cvmx_wst_pp_powew_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t gate:48;
#ewse
		uint64_t gate:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
	stwuct cvmx_wst_pp_powew_cn70xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t gate:4;
#ewse
		uint64_t gate:4;
		uint64_t wesewved_4_63:60;
#endif
	} cn70xx;
};

union cvmx_wst_soft_pwstx {
	uint64_t u64;
	stwuct cvmx_wst_soft_pwstx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t soft_pwst:1;
#ewse
		uint64_t soft_pwst:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_wst_soft_wst {
	uint64_t u64;
	stwuct cvmx_wst_soft_wst_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t soft_wst:1;
#ewse
		uint64_t soft_wst:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

#endif
