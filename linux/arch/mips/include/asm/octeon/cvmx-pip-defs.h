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

#ifndef __CVMX_PIP_DEFS_H__
#define __CVMX_PIP_DEFS_H__

/*
 * Enumewation wepwesenting the amount of packet pwocessing
 * and vawidation pewfowmed by the input hawdwawe.
 */
enum cvmx_pip_powt_pawse_mode {
	/*
	 * Packet input doesn't pewfowm any pwocessing of the input
	 * packet.
	 */
	CVMX_PIP_POWT_CFG_MODE_NONE = 0uww,
	/*
	 * Fuww packet pwocessing is pewfowmed with pointew stawting
	 * at the W2 (ethewnet MAC) headew.
	 */
	CVMX_PIP_POWT_CFG_MODE_SKIPW2 = 1uww,
	/*
	 * Input packets awe assumed to be IP.	Wesuwts fwom non IP
	 * packets is undefined. Pointews wefewence the beginning of
	 * the IP headew.
	 */
	CVMX_PIP_POWT_CFG_MODE_SKIPIP = 2uww
};

#define CVMX_PIP_AWT_SKIP_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002A00uww) + ((offset) & 3) * 8)
#define CVMX_PIP_BCK_PWS (CVMX_ADD_IO_SEG(0x00011800A0000038uww))
#define CVMX_PIP_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800A0000000uww))
#define CVMX_PIP_BSEW_EXT_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002800uww) + ((offset) & 3) * 16)
#define CVMX_PIP_BSEW_EXT_POSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002808uww) + ((offset) & 3) * 16)
#define CVMX_PIP_BSEW_TBW_ENTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0003000uww) + ((offset) & 511) * 8)
#define CVMX_PIP_CWKEN (CVMX_ADD_IO_SEG(0x00011800A0000040uww))
#define CVMX_PIP_CWC_CTWX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000040uww) + ((offset) & 1) * 8)
#define CVMX_PIP_CWC_IVX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000050uww) + ((offset) & 1) * 8)
#define CVMX_PIP_DEC_IPSECX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000080uww) + ((offset) & 3) * 8)
#define CVMX_PIP_DSA_SWC_GWP (CVMX_ADD_IO_SEG(0x00011800A0000190uww))
#define CVMX_PIP_DSA_VID_GWP (CVMX_ADD_IO_SEG(0x00011800A0000198uww))
#define CVMX_PIP_FWM_WEN_CHKX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000180uww) + ((offset) & 1) * 8)
#define CVMX_PIP_GBW_CFG (CVMX_ADD_IO_SEG(0x00011800A0000028uww))
#define CVMX_PIP_GBW_CTW (CVMX_ADD_IO_SEG(0x00011800A0000020uww))
#define CVMX_PIP_HG_PWI_QOS (CVMX_ADD_IO_SEG(0x00011800A00001A0uww))
#define CVMX_PIP_INT_EN (CVMX_ADD_IO_SEG(0x00011800A0000010uww))
#define CVMX_PIP_INT_WEG (CVMX_ADD_IO_SEG(0x00011800A0000008uww))
#define CVMX_PIP_IP_OFFSET (CVMX_ADD_IO_SEG(0x00011800A0000060uww))
#define CVMX_PIP_PWI_TBWX(offset) (CVMX_ADD_IO_SEG(0x00011800A0004000uww) + ((offset) & 255) * 8)
#define CVMX_PIP_PWT_CFGBX(offset) (CVMX_ADD_IO_SEG(0x00011800A0008000uww) + ((offset) & 63) * 8)
#define CVMX_PIP_PWT_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000200uww) + ((offset) & 63) * 8)
#define CVMX_PIP_PWT_TAGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000400uww) + ((offset) & 63) * 8)
#define CVMX_PIP_QOS_DIFFX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000600uww) + ((offset) & 63) * 8)
#define CVMX_PIP_QOS_VWANX(offset) (CVMX_ADD_IO_SEG(0x00011800A00000C0uww) + ((offset) & 7) * 8)
#define CVMX_PIP_QOS_WATCHX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000100uww) + ((offset) & 7) * 8)
#define CVMX_PIP_WAW_WOWD (CVMX_ADD_IO_SEG(0x00011800A00000B0uww))
#define CVMX_PIP_SFT_WST (CVMX_ADD_IO_SEG(0x00011800A0000030uww))
#define CVMX_PIP_STAT0_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000800uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT0_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040000uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT10_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001480uww) + ((offset) & 63) * 16)
#define CVMX_PIP_STAT10_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040050uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT11_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001488uww) + ((offset) & 63) * 16)
#define CVMX_PIP_STAT11_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040058uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT1_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000808uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT1_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040008uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT2_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000810uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT2_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040010uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT3_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000818uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT3_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040018uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT4_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000820uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT4_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040020uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT5_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000828uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT5_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040028uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT6_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000830uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT6_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040030uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT7_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000838uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT7_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040038uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT8_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000840uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT8_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040040uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT9_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000848uww) + ((offset) & 63) * 80)
#define CVMX_PIP_STAT9_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040048uww) + ((offset) & 63) * 128)
#define CVMX_PIP_STAT_CTW (CVMX_ADD_IO_SEG(0x00011800A0000018uww))
#define CVMX_PIP_STAT_INB_EWWSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A10uww) + ((offset) & 63) * 32)
#define CVMX_PIP_STAT_INB_EWWS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020010uww) + ((offset) & 63) * 32)
#define CVMX_PIP_STAT_INB_OCTSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A08uww) + ((offset) & 63) * 32)
#define CVMX_PIP_STAT_INB_OCTS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020008uww) + ((offset) & 63) * 32)
#define CVMX_PIP_STAT_INB_PKTSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A00uww) + ((offset) & 63) * 32)
#define CVMX_PIP_STAT_INB_PKTS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020000uww) + ((offset) & 63) * 32)
#define CVMX_PIP_SUB_PKIND_FCSX(bwock_id) (CVMX_ADD_IO_SEG(0x00011800A0080000uww))
#define CVMX_PIP_TAG_INCX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001800uww) + ((offset) & 63) * 8)
#define CVMX_PIP_TAG_MASK (CVMX_ADD_IO_SEG(0x00011800A0000070uww))
#define CVMX_PIP_TAG_SECWET (CVMX_ADD_IO_SEG(0x00011800A0000068uww))
#define CVMX_PIP_TODO_ENTWY (CVMX_ADD_IO_SEG(0x00011800A0000078uww))
#define CVMX_PIP_VWAN_ETYPESX(offset) (CVMX_ADD_IO_SEG(0x00011800A00001C0uww) + ((offset) & 1) * 8)
#define CVMX_PIP_XSTAT0_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002000uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT10_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001700uww) + ((offset) & 63) * 16 - 16*40)
#define CVMX_PIP_XSTAT11_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001708uww) + ((offset) & 63) * 16 - 16*40)
#define CVMX_PIP_XSTAT1_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002008uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT2_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002010uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT3_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002018uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT4_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002020uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT5_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002028uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT6_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002030uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT7_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002038uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT8_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002040uww) + ((offset) & 63) * 80 - 80*40)
#define CVMX_PIP_XSTAT9_PWTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002048uww) + ((offset) & 63) * 80 - 80*40)

union cvmx_pip_awt_skip_cfgx {
	uint64_t u64;
	stwuct cvmx_pip_awt_skip_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_57_63:7;
		uint64_t wen:1;
		uint64_t wesewved_46_55:10;
		uint64_t bit1:6;
		uint64_t wesewved_38_39:2;
		uint64_t bit0:6;
		uint64_t wesewved_23_31:9;
		uint64_t skip3:7;
		uint64_t wesewved_15_15:1;
		uint64_t skip2:7;
		uint64_t wesewved_7_7:1;
		uint64_t skip1:7;
#ewse
		uint64_t skip1:7;
		uint64_t wesewved_7_7:1;
		uint64_t skip2:7;
		uint64_t wesewved_15_15:1;
		uint64_t skip3:7;
		uint64_t wesewved_23_31:9;
		uint64_t bit0:6;
		uint64_t wesewved_38_39:2;
		uint64_t bit1:6;
		uint64_t wesewved_46_55:10;
		uint64_t wen:1;
		uint64_t wesewved_57_63:7;
#endif
	} s;
};

union cvmx_pip_bck_pws {
	uint64_t u64;
	stwuct cvmx_pip_bck_pws_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bckpws:1;
		uint64_t wesewved_13_62:50;
		uint64_t hiwatew:5;
		uint64_t wesewved_5_7:3;
		uint64_t wowatew:5;
#ewse
		uint64_t wowatew:5;
		uint64_t wesewved_5_7:3;
		uint64_t hiwatew:5;
		uint64_t wesewved_13_62:50;
		uint64_t bckpws:1;
#endif
	} s;
};

union cvmx_pip_bist_status {
	uint64_t u64;
	stwuct cvmx_pip_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t bist:22;
#ewse
		uint64_t bist:22;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_pip_bist_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t bist:18;
#ewse
		uint64_t bist:18;
		uint64_t wesewved_18_63:46;
#endif
	} cn30xx;
	stwuct cvmx_pip_bist_status_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t bist:17;
#ewse
		uint64_t bist:17;
		uint64_t wesewved_17_63:47;
#endif
	} cn50xx;
	stwuct cvmx_pip_bist_status_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t bist:20;
#ewse
		uint64_t bist:20;
		uint64_t wesewved_20_63:44;
#endif
	} cn61xx;
};

union cvmx_pip_bsew_ext_cfgx {
	uint64_t u64;
	stwuct cvmx_pip_bsew_ext_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t uppew_tag:16;
		uint64_t tag:8;
		uint64_t wesewved_25_31:7;
		uint64_t offset:9;
		uint64_t wesewved_7_15:9;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_15:9;
		uint64_t offset:9;
		uint64_t wesewved_25_31:7;
		uint64_t tag:8;
		uint64_t uppew_tag:16;
		uint64_t wesewved_56_63:8;
#endif
	} s;
};

union cvmx_pip_bsew_ext_posx {
	uint64_t u64;
	stwuct cvmx_pip_bsew_ext_posx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pos7_vaw:1;
		uint64_t pos7:7;
		uint64_t pos6_vaw:1;
		uint64_t pos6:7;
		uint64_t pos5_vaw:1;
		uint64_t pos5:7;
		uint64_t pos4_vaw:1;
		uint64_t pos4:7;
		uint64_t pos3_vaw:1;
		uint64_t pos3:7;
		uint64_t pos2_vaw:1;
		uint64_t pos2:7;
		uint64_t pos1_vaw:1;
		uint64_t pos1:7;
		uint64_t pos0_vaw:1;
		uint64_t pos0:7;
#ewse
		uint64_t pos0:7;
		uint64_t pos0_vaw:1;
		uint64_t pos1:7;
		uint64_t pos1_vaw:1;
		uint64_t pos2:7;
		uint64_t pos2_vaw:1;
		uint64_t pos3:7;
		uint64_t pos3_vaw:1;
		uint64_t pos4:7;
		uint64_t pos4_vaw:1;
		uint64_t pos5:7;
		uint64_t pos5_vaw:1;
		uint64_t pos6:7;
		uint64_t pos6_vaw:1;
		uint64_t pos7:7;
		uint64_t pos7_vaw:1;
#endif
	} s;
};

union cvmx_pip_bsew_tbw_entx {
	uint64_t u64;
	stwuct cvmx_pip_bsew_tbw_entx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t tag_en:1;
		uint64_t gwp_en:1;
		uint64_t tt_en:1;
		uint64_t qos_en:1;
		uint64_t wesewved_40_59:20;
		uint64_t tag:8;
		uint64_t wesewved_22_31:10;
		uint64_t gwp:6;
		uint64_t wesewved_10_15:6;
		uint64_t tt:2;
		uint64_t wesewved_3_7:5;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t wesewved_3_7:5;
		uint64_t tt:2;
		uint64_t wesewved_10_15:6;
		uint64_t gwp:6;
		uint64_t wesewved_22_31:10;
		uint64_t tag:8;
		uint64_t wesewved_40_59:20;
		uint64_t qos_en:1;
		uint64_t tt_en:1;
		uint64_t gwp_en:1;
		uint64_t tag_en:1;
#endif
	} s;
	stwuct cvmx_pip_bsew_tbw_entx_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t tag_en:1;
		uint64_t gwp_en:1;
		uint64_t tt_en:1;
		uint64_t qos_en:1;
		uint64_t wesewved_40_59:20;
		uint64_t tag:8;
		uint64_t wesewved_20_31:12;
		uint64_t gwp:4;
		uint64_t wesewved_10_15:6;
		uint64_t tt:2;
		uint64_t wesewved_3_7:5;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t wesewved_3_7:5;
		uint64_t tt:2;
		uint64_t wesewved_10_15:6;
		uint64_t gwp:4;
		uint64_t wesewved_20_31:12;
		uint64_t tag:8;
		uint64_t wesewved_40_59:20;
		uint64_t qos_en:1;
		uint64_t tt_en:1;
		uint64_t gwp_en:1;
		uint64_t tag_en:1;
#endif
	} cn61xx;
};

union cvmx_pip_cwken {
	uint64_t u64;
	stwuct cvmx_pip_cwken_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t cwken:1;
#ewse
		uint64_t cwken:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_pip_cwc_ctwx {
	uint64_t u64;
	stwuct cvmx_pip_cwc_ctwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t invwes:1;
		uint64_t wefwect:1;
#ewse
		uint64_t wefwect:1;
		uint64_t invwes:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_pip_cwc_ivx {
	uint64_t u64;
	stwuct cvmx_pip_cwc_ivx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iv:32;
#ewse
		uint64_t iv:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pip_dec_ipsecx {
	uint64_t u64;
	stwuct cvmx_pip_dec_ipsecx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t tcp:1;
		uint64_t udp:1;
		uint64_t dpwt:16;
#ewse
		uint64_t dpwt:16;
		uint64_t udp:1;
		uint64_t tcp:1;
		uint64_t wesewved_18_63:46;
#endif
	} s;
};

union cvmx_pip_dsa_swc_gwp {
	uint64_t u64;
	stwuct cvmx_pip_dsa_swc_gwp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t map15:4;
		uint64_t map14:4;
		uint64_t map13:4;
		uint64_t map12:4;
		uint64_t map11:4;
		uint64_t map10:4;
		uint64_t map9:4;
		uint64_t map8:4;
		uint64_t map7:4;
		uint64_t map6:4;
		uint64_t map5:4;
		uint64_t map4:4;
		uint64_t map3:4;
		uint64_t map2:4;
		uint64_t map1:4;
		uint64_t map0:4;
#ewse
		uint64_t map0:4;
		uint64_t map1:4;
		uint64_t map2:4;
		uint64_t map3:4;
		uint64_t map4:4;
		uint64_t map5:4;
		uint64_t map6:4;
		uint64_t map7:4;
		uint64_t map8:4;
		uint64_t map9:4;
		uint64_t map10:4;
		uint64_t map11:4;
		uint64_t map12:4;
		uint64_t map13:4;
		uint64_t map14:4;
		uint64_t map15:4;
#endif
	} s;
};

union cvmx_pip_dsa_vid_gwp {
	uint64_t u64;
	stwuct cvmx_pip_dsa_vid_gwp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t map15:4;
		uint64_t map14:4;
		uint64_t map13:4;
		uint64_t map12:4;
		uint64_t map11:4;
		uint64_t map10:4;
		uint64_t map9:4;
		uint64_t map8:4;
		uint64_t map7:4;
		uint64_t map6:4;
		uint64_t map5:4;
		uint64_t map4:4;
		uint64_t map3:4;
		uint64_t map2:4;
		uint64_t map1:4;
		uint64_t map0:4;
#ewse
		uint64_t map0:4;
		uint64_t map1:4;
		uint64_t map2:4;
		uint64_t map3:4;
		uint64_t map4:4;
		uint64_t map5:4;
		uint64_t map6:4;
		uint64_t map7:4;
		uint64_t map8:4;
		uint64_t map9:4;
		uint64_t map10:4;
		uint64_t map11:4;
		uint64_t map12:4;
		uint64_t map13:4;
		uint64_t map14:4;
		uint64_t map15:4;
#endif
	} s;
};

union cvmx_pip_fwm_wen_chkx {
	uint64_t u64;
	stwuct cvmx_pip_fwm_wen_chkx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t maxwen:16;
		uint64_t minwen:16;
#ewse
		uint64_t minwen:16;
		uint64_t maxwen:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pip_gbw_cfg {
	uint64_t u64;
	stwuct cvmx_pip_gbw_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_19_63:45;
		uint64_t tag_syn:1;
		uint64_t ip6_udp:1;
		uint64_t max_w2:1;
		uint64_t wesewved_11_15:5;
		uint64_t waw_shf:3;
		uint64_t wesewved_3_7:5;
		uint64_t nip_shf:3;
#ewse
		uint64_t nip_shf:3;
		uint64_t wesewved_3_7:5;
		uint64_t waw_shf:3;
		uint64_t wesewved_11_15:5;
		uint64_t max_w2:1;
		uint64_t ip6_udp:1;
		uint64_t tag_syn:1;
		uint64_t wesewved_19_63:45;
#endif
	} s;
};

union cvmx_pip_gbw_ctw {
	uint64_t u64;
	stwuct cvmx_pip_gbw_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t egwp_dis:1;
		uint64_t ihmsk_dis:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_sid:1;
		uint64_t wesewved_21_23:3;
		uint64_t wing_en:1;
		uint64_t wesewved_17_19:3;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_19:3;
		uint64_t wing_en:1;
		uint64_t wesewved_21_23:3;
		uint64_t dsa_gwp_sid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t ihmsk_dis:1;
		uint64_t egwp_dis:1;
		uint64_t wesewved_29_63:35;
#endif
	} s;
	stwuct cvmx_pip_gbw_ctw_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn30xx;
	stwuct cvmx_pip_gbw_ctw_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_27_63:37;
		uint64_t dsa_gwp_tvid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_sid:1;
		uint64_t wesewved_21_23:3;
		uint64_t wing_en:1;
		uint64_t wesewved_17_19:3;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_19:3;
		uint64_t wing_en:1;
		uint64_t wesewved_21_23:3;
		uint64_t dsa_gwp_sid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t wesewved_27_63:37;
#endif
	} cn52xx;
	stwuct cvmx_pip_gbw_ctw_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_21_63:43;
		uint64_t wing_en:1;
		uint64_t wesewved_17_19:3;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_19:3;
		uint64_t wing_en:1;
		uint64_t wesewved_21_63:43;
#endif
	} cn56xxp1;
	stwuct cvmx_pip_gbw_ctw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t ihmsk_dis:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_sid:1;
		uint64_t wesewved_21_23:3;
		uint64_t wing_en:1;
		uint64_t wesewved_17_19:3;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_19:3;
		uint64_t wing_en:1;
		uint64_t wesewved_21_23:3;
		uint64_t dsa_gwp_sid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t ihmsk_dis:1;
		uint64_t wesewved_28_63:36;
#endif
	} cn61xx;
	stwuct cvmx_pip_gbw_ctw_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t egwp_dis:1;
		uint64_t ihmsk_dis:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_sid:1;
		uint64_t wesewved_17_23:7;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_23:7;
		uint64_t dsa_gwp_sid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t ihmsk_dis:1;
		uint64_t egwp_dis:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn68xx;
	stwuct cvmx_pip_gbw_ctw_cn68xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t ihmsk_dis:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_sid:1;
		uint64_t wesewved_17_23:7;
		uint64_t ignws:1;
		uint64_t vs_wqe:1;
		uint64_t vs_qos:1;
		uint64_t w2_maw:1;
		uint64_t tcp_fwag:1;
		uint64_t w4_wen:1;
		uint64_t w4_chk:1;
		uint64_t w4_pwt:1;
		uint64_t w4_maw:1;
		uint64_t wesewved_6_7:2;
		uint64_t ip6_eext:2;
		uint64_t ip4_opts:1;
		uint64_t ip_hop:1;
		uint64_t ip_maw:1;
		uint64_t ip_chk:1;
#ewse
		uint64_t ip_chk:1;
		uint64_t ip_maw:1;
		uint64_t ip_hop:1;
		uint64_t ip4_opts:1;
		uint64_t ip6_eext:2;
		uint64_t wesewved_6_7:2;
		uint64_t w4_maw:1;
		uint64_t w4_pwt:1;
		uint64_t w4_chk:1;
		uint64_t w4_wen:1;
		uint64_t tcp_fwag:1;
		uint64_t w2_maw:1;
		uint64_t vs_qos:1;
		uint64_t vs_wqe:1;
		uint64_t ignws:1;
		uint64_t wesewved_17_23:7;
		uint64_t dsa_gwp_sid:1;
		uint64_t dsa_gwp_scmd:1;
		uint64_t dsa_gwp_tvid:1;
		uint64_t ihmsk_dis:1;
		uint64_t wesewved_28_63:36;
#endif
	} cn68xxp1;
};

union cvmx_pip_hg_pwi_qos {
	uint64_t u64;
	stwuct cvmx_pip_hg_pwi_qos_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t up_qos:1;
		uint64_t wesewved_11_11:1;
		uint64_t qos:3;
		uint64_t wesewved_6_7:2;
		uint64_t pwi:6;
#ewse
		uint64_t pwi:6;
		uint64_t wesewved_6_7:2;
		uint64_t qos:3;
		uint64_t wesewved_11_11:1;
		uint64_t up_qos:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
};

union cvmx_pip_int_en {
	uint64_t u64;
	stwuct cvmx_pip_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_pip_int_en_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn30xx;
	stwuct cvmx_pip_int_en_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t wesewved_1_1:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t wesewved_1_1:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn50xx;
	stwuct cvmx_pip_int_en_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t wesewved_1_1:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t wesewved_1_1:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} cn52xx;
	stwuct cvmx_pip_int_en_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn56xxp1;
	stwuct cvmx_pip_int_en_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t wesewved_9_11:3;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t wesewved_9_11:3;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} cn58xx;
};

union cvmx_pip_int_weg {
	uint64_t u64;
	stwuct cvmx_pip_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_pip_int_weg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn30xx;
	stwuct cvmx_pip_int_weg_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t wesewved_1_1:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t wesewved_1_1:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn50xx;
	stwuct cvmx_pip_int_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t wesewved_1_1:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t wesewved_1_1:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} cn52xx;
	stwuct cvmx_pip_int_weg_cn56xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t weneww:1;
		uint64_t maxeww:1;
		uint64_t mineww:1;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t mineww:1;
		uint64_t maxeww:1;
		uint64_t weneww:1;
		uint64_t wesewved_12_63:52;
#endif
	} cn56xxp1;
	stwuct cvmx_pip_int_weg_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t punyeww:1;
		uint64_t wesewved_9_11:3;
		uint64_t bepeww:1;
		uint64_t fepeww:1;
		uint64_t todoovw:1;
		uint64_t skpwunt:1;
		uint64_t badtag:1;
		uint64_t pwtnxa:1;
		uint64_t bckpws:1;
		uint64_t cwceww:1;
		uint64_t pktdwp:1;
#ewse
		uint64_t pktdwp:1;
		uint64_t cwceww:1;
		uint64_t bckpws:1;
		uint64_t pwtnxa:1;
		uint64_t badtag:1;
		uint64_t skpwunt:1;
		uint64_t todoovw:1;
		uint64_t fepeww:1;
		uint64_t bepeww:1;
		uint64_t wesewved_9_11:3;
		uint64_t punyeww:1;
		uint64_t wesewved_13_63:51;
#endif
	} cn58xx;
};

union cvmx_pip_ip_offset {
	uint64_t u64;
	stwuct cvmx_pip_ip_offset_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t offset:3;
#ewse
		uint64_t offset:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_pip_pwi_tbwx {
	uint64_t u64;
	stwuct cvmx_pip_pwi_tbwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t diff2_padd:8;
		uint64_t hg2_padd:8;
		uint64_t vwan2_padd:8;
		uint64_t wesewved_38_39:2;
		uint64_t diff2_bpid:6;
		uint64_t wesewved_30_31:2;
		uint64_t hg2_bpid:6;
		uint64_t wesewved_22_23:2;
		uint64_t vwan2_bpid:6;
		uint64_t wesewved_11_15:5;
		uint64_t diff2_qos:3;
		uint64_t wesewved_7_7:1;
		uint64_t hg2_qos:3;
		uint64_t wesewved_3_3:1;
		uint64_t vwan2_qos:3;
#ewse
		uint64_t vwan2_qos:3;
		uint64_t wesewved_3_3:1;
		uint64_t hg2_qos:3;
		uint64_t wesewved_7_7:1;
		uint64_t diff2_qos:3;
		uint64_t wesewved_11_15:5;
		uint64_t vwan2_bpid:6;
		uint64_t wesewved_22_23:2;
		uint64_t hg2_bpid:6;
		uint64_t wesewved_30_31:2;
		uint64_t diff2_bpid:6;
		uint64_t wesewved_38_39:2;
		uint64_t vwan2_padd:8;
		uint64_t hg2_padd:8;
		uint64_t diff2_padd:8;
#endif
	} s;
};

union cvmx_pip_pwt_cfgx {
	uint64_t u64;
	stwuct cvmx_pip_pwt_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_55_63:9;
		uint64_t ih_pwi:1;
		uint64_t wen_chk_sew:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t weneww_en:1;
		uint64_t maxeww_en:1;
		uint64_t mineww_en:1;
		uint64_t gwp_wat_47:4;
		uint64_t qos_wat_47:4;
		uint64_t wesewved_37_39:3;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t hg_qos:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t qos_vsew:1;
		uint64_t qos_vod:1;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t higig_en:1;
		uint64_t dsa_en:1;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t dsa_en:1;
		uint64_t higig_en:1;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t qos_vod:1;
		uint64_t qos_vsew:1;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t hg_qos:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_39:3;
		uint64_t qos_wat_47:4;
		uint64_t gwp_wat_47:4;
		uint64_t mineww_en:1;
		uint64_t maxeww_en:1;
		uint64_t weneww_en:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t wen_chk_sew:1;
		uint64_t ih_pwi:1;
		uint64_t wesewved_55_63:9;
#endif
	} s;
	stwuct cvmx_pip_pwt_cfgx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t wesewved_27_27:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t wesewved_18_19:2;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_10_15:6;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t wesewved_10_15:6;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t wesewved_18_19:2;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t wesewved_27_27:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_63:27;
#endif
	} cn30xx;
	stwuct cvmx_pip_pwt_cfgx_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t wesewved_27_27:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t wesewved_18_19:2;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t wesewved_10_11:2;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t wesewved_10_11:2;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t wesewved_18_19:2;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t wesewved_27_27:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_63:27;
#endif
	} cn38xx;
	stwuct cvmx_pip_pwt_cfgx_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_53_63:11;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t weneww_en:1;
		uint64_t maxeww_en:1;
		uint64_t mineww_en:1;
		uint64_t gwp_wat_47:4;
		uint64_t qos_wat_47:4;
		uint64_t wesewved_37_39:3;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t wesewved_27_27:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t wesewved_19_19:1;
		uint64_t qos_vod:1;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t wesewved_10_11:2;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t wesewved_10_11:2;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t qos_vod:1;
		uint64_t wesewved_19_19:1;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t wesewved_27_27:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_39:3;
		uint64_t qos_wat_47:4;
		uint64_t gwp_wat_47:4;
		uint64_t mineww_en:1;
		uint64_t maxeww_en:1;
		uint64_t weneww_en:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t wesewved_53_63:11;
#endif
	} cn50xx;
	stwuct cvmx_pip_pwt_cfgx_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_53_63:11;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t weneww_en:1;
		uint64_t maxeww_en:1;
		uint64_t mineww_en:1;
		uint64_t gwp_wat_47:4;
		uint64_t qos_wat_47:4;
		uint64_t wesewved_37_39:3;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t hg_qos:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t qos_vsew:1;
		uint64_t qos_vod:1;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t higig_en:1;
		uint64_t dsa_en:1;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t dsa_en:1;
		uint64_t higig_en:1;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t qos_vod:1;
		uint64_t qos_vsew:1;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t hg_qos:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_39:3;
		uint64_t qos_wat_47:4;
		uint64_t gwp_wat_47:4;
		uint64_t mineww_en:1;
		uint64_t maxeww_en:1;
		uint64_t weneww_en:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t wesewved_53_63:11;
#endif
	} cn52xx;
	stwuct cvmx_pip_pwt_cfgx_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t wesewved_27_27:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t wesewved_19_19:1;
		uint64_t qos_vod:1;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t wesewved_10_11:2;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t wesewved_10_11:2;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t qos_vod:1;
		uint64_t wesewved_19_19:1;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t wesewved_27_27:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_63:27;
#endif
	} cn58xx;
	stwuct cvmx_pip_pwt_cfgx_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_55_63:9;
		uint64_t ih_pwi:1;
		uint64_t wen_chk_sew:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t weneww_en:1;
		uint64_t maxeww_en:1;
		uint64_t mineww_en:1;
		uint64_t gwp_wat_47:4;
		uint64_t qos_wat_47:4;
		uint64_t wesewved_37_39:3;
		uint64_t wawdwp:1;
		uint64_t tag_inc:2;
		uint64_t dyn_ws:1;
		uint64_t inst_hdw:1;
		uint64_t gwp_wat:4;
		uint64_t hg_qos:1;
		uint64_t qos:3;
		uint64_t qos_wat:4;
		uint64_t wesewved_19_19:1;
		uint64_t qos_vod:1;
		uint64_t qos_diff:1;
		uint64_t qos_vwan:1;
		uint64_t wesewved_13_15:3;
		uint64_t cwc_en:1;
		uint64_t higig_en:1;
		uint64_t dsa_en:1;
		uint64_t mode:2;
		uint64_t wesewved_7_7:1;
		uint64_t skip:7;
#ewse
		uint64_t skip:7;
		uint64_t wesewved_7_7:1;
		uint64_t mode:2;
		uint64_t dsa_en:1;
		uint64_t higig_en:1;
		uint64_t cwc_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t qos_vwan:1;
		uint64_t qos_diff:1;
		uint64_t qos_vod:1;
		uint64_t wesewved_19_19:1;
		uint64_t qos_wat:4;
		uint64_t qos:3;
		uint64_t hg_qos:1;
		uint64_t gwp_wat:4;
		uint64_t inst_hdw:1;
		uint64_t dyn_ws:1;
		uint64_t tag_inc:2;
		uint64_t wawdwp:1;
		uint64_t wesewved_37_39:3;
		uint64_t qos_wat_47:4;
		uint64_t gwp_wat_47:4;
		uint64_t mineww_en:1;
		uint64_t maxeww_en:1;
		uint64_t weneww_en:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t wen_chk_sew:1;
		uint64_t ih_pwi:1;
		uint64_t wesewved_55_63:9;
#endif
	} cn68xx;
};

union cvmx_pip_pwt_cfgbx {
	uint64_t u64;
	stwuct cvmx_pip_pwt_cfgbx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_39_63:25;
		uint64_t awt_skp_sew:2;
		uint64_t awt_skp_en:1;
		uint64_t wesewved_35_35:1;
		uint64_t bsew_num:2;
		uint64_t bsew_en:1;
		uint64_t wesewved_24_31:8;
		uint64_t base:8;
		uint64_t wesewved_6_15:10;
		uint64_t bpid:6;
#ewse
		uint64_t bpid:6;
		uint64_t wesewved_6_15:10;
		uint64_t base:8;
		uint64_t wesewved_24_31:8;
		uint64_t bsew_en:1;
		uint64_t bsew_num:2;
		uint64_t wesewved_35_35:1;
		uint64_t awt_skp_en:1;
		uint64_t awt_skp_sew:2;
		uint64_t wesewved_39_63:25;
#endif
	} s;
	stwuct cvmx_pip_pwt_cfgbx_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_39_63:25;
		uint64_t awt_skp_sew:2;
		uint64_t awt_skp_en:1;
		uint64_t wesewved_35_35:1;
		uint64_t bsew_num:2;
		uint64_t bsew_en:1;
		uint64_t wesewved_0_31:32;
#ewse
		uint64_t wesewved_0_31:32;
		uint64_t bsew_en:1;
		uint64_t bsew_num:2;
		uint64_t wesewved_35_35:1;
		uint64_t awt_skp_en:1;
		uint64_t awt_skp_sew:2;
		uint64_t wesewved_39_63:25;
#endif
	} cn61xx;
	stwuct cvmx_pip_pwt_cfgbx_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_39_63:25;
		uint64_t awt_skp_sew:2;
		uint64_t awt_skp_en:1;
		uint64_t wesewved_0_35:36;
#ewse
		uint64_t wesewved_0_35:36;
		uint64_t awt_skp_en:1;
		uint64_t awt_skp_sew:2;
		uint64_t wesewved_39_63:25;
#endif
	} cn66xx;
	stwuct cvmx_pip_pwt_cfgbx_cn68xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t base:8;
		uint64_t wesewved_6_15:10;
		uint64_t bpid:6;
#ewse
		uint64_t bpid:6;
		uint64_t wesewved_6_15:10;
		uint64_t base:8;
		uint64_t wesewved_24_63:40;
#endif
	} cn68xxp1;
};

union cvmx_pip_pwt_tagx {
	uint64_t u64;
	stwuct cvmx_pip_pwt_tagx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_54_63:10;
		uint64_t powtadd_en:1;
		uint64_t inc_hwchk:1;
		uint64_t wesewved_50_51:2;
		uint64_t gwptagbase_msb:2;
		uint64_t wesewved_46_47:2;
		uint64_t gwptagmask_msb:2;
		uint64_t wesewved_42_43:2;
		uint64_t gwp_msb:2;
		uint64_t gwptagbase:4;
		uint64_t gwptagmask:4;
		uint64_t gwptag:1;
		uint64_t gwptag_mskip:1;
		uint64_t tag_mode:2;
		uint64_t inc_vs:2;
		uint64_t inc_vwan:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_swc_fwag:1;
		uint64_t tcp6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t non_tag_type:2;
		uint64_t gwp:4;
#ewse
		uint64_t gwp:4;
		uint64_t non_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t tcp6_tag_type:2;
		uint64_t ip4_swc_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t inc_vwan:1;
		uint64_t inc_vs:2;
		uint64_t tag_mode:2;
		uint64_t gwptag_mskip:1;
		uint64_t gwptag:1;
		uint64_t gwptagmask:4;
		uint64_t gwptagbase:4;
		uint64_t gwp_msb:2;
		uint64_t wesewved_42_43:2;
		uint64_t gwptagmask_msb:2;
		uint64_t wesewved_46_47:2;
		uint64_t gwptagbase_msb:2;
		uint64_t wesewved_50_51:2;
		uint64_t inc_hwchk:1;
		uint64_t powtadd_en:1;
		uint64_t wesewved_54_63:10;
#endif
	} s;
	stwuct cvmx_pip_pwt_tagx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t gwptagbase:4;
		uint64_t gwptagmask:4;
		uint64_t gwptag:1;
		uint64_t wesewved_30_30:1;
		uint64_t tag_mode:2;
		uint64_t inc_vs:2;
		uint64_t inc_vwan:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_swc_fwag:1;
		uint64_t tcp6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t non_tag_type:2;
		uint64_t gwp:4;
#ewse
		uint64_t gwp:4;
		uint64_t non_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t tcp6_tag_type:2;
		uint64_t ip4_swc_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t inc_vwan:1;
		uint64_t inc_vs:2;
		uint64_t tag_mode:2;
		uint64_t wesewved_30_30:1;
		uint64_t gwptag:1;
		uint64_t gwptagmask:4;
		uint64_t gwptagbase:4;
		uint64_t wesewved_40_63:24;
#endif
	} cn30xx;
	stwuct cvmx_pip_pwt_tagx_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t gwptagbase:4;
		uint64_t gwptagmask:4;
		uint64_t gwptag:1;
		uint64_t gwptag_mskip:1;
		uint64_t tag_mode:2;
		uint64_t inc_vs:2;
		uint64_t inc_vwan:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_swc_fwag:1;
		uint64_t tcp6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t non_tag_type:2;
		uint64_t gwp:4;
#ewse
		uint64_t gwp:4;
		uint64_t non_tag_type:2;
		uint64_t ip4_tag_type:2;
		uint64_t ip6_tag_type:2;
		uint64_t tcp4_tag_type:2;
		uint64_t tcp6_tag_type:2;
		uint64_t ip4_swc_fwag:1;
		uint64_t ip6_swc_fwag:1;
		uint64_t ip4_dst_fwag:1;
		uint64_t ip6_dst_fwag:1;
		uint64_t ip4_pctw_fwag:1;
		uint64_t ip6_nxth_fwag:1;
		uint64_t ip4_spwt_fwag:1;
		uint64_t ip6_spwt_fwag:1;
		uint64_t ip4_dpwt_fwag:1;
		uint64_t ip6_dpwt_fwag:1;
		uint64_t inc_pwt_fwag:1;
		uint64_t inc_vwan:1;
		uint64_t inc_vs:2;
		uint64_t tag_mode:2;
		uint64_t gwptag_mskip:1;
		uint64_t gwptag:1;
		uint64_t gwptagmask:4;
		uint64_t gwptagbase:4;
		uint64_t wesewved_40_63:24;
#endif
	} cn50xx;
};

union cvmx_pip_qos_diffx {
	uint64_t u64;
	stwuct cvmx_pip_qos_diffx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_pip_qos_vwanx {
	uint64_t u64;
	stwuct cvmx_pip_qos_vwanx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t qos1:3;
		uint64_t wesewved_3_3:1;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t wesewved_3_3:1;
		uint64_t qos1:3;
		uint64_t wesewved_7_63:57;
#endif
	} s;
	stwuct cvmx_pip_qos_vwanx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t qos:3;
#ewse
		uint64_t qos:3;
		uint64_t wesewved_3_63:61;
#endif
	} cn30xx;
};

union cvmx_pip_qos_watchx {
	uint64_t u64;
	stwuct cvmx_pip_qos_watchx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t mask:16;
		uint64_t wesewved_30_31:2;
		uint64_t gwp:6;
		uint64_t wesewved_23_23:1;
		uint64_t qos:3;
		uint64_t wesewved_19_19:1;
		uint64_t match_type:3;
		uint64_t match_vawue:16;
#ewse
		uint64_t match_vawue:16;
		uint64_t match_type:3;
		uint64_t wesewved_19_19:1;
		uint64_t qos:3;
		uint64_t wesewved_23_23:1;
		uint64_t gwp:6;
		uint64_t wesewved_30_31:2;
		uint64_t mask:16;
		uint64_t wesewved_48_63:16;
#endif
	} s;
	stwuct cvmx_pip_qos_watchx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t mask:16;
		uint64_t wesewved_28_31:4;
		uint64_t gwp:4;
		uint64_t wesewved_23_23:1;
		uint64_t qos:3;
		uint64_t wesewved_18_19:2;
		uint64_t match_type:2;
		uint64_t match_vawue:16;
#ewse
		uint64_t match_vawue:16;
		uint64_t match_type:2;
		uint64_t wesewved_18_19:2;
		uint64_t qos:3;
		uint64_t wesewved_23_23:1;
		uint64_t gwp:4;
		uint64_t wesewved_28_31:4;
		uint64_t mask:16;
		uint64_t wesewved_48_63:16;
#endif
	} cn30xx;
	stwuct cvmx_pip_qos_watchx_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t mask:16;
		uint64_t wesewved_28_31:4;
		uint64_t gwp:4;
		uint64_t wesewved_23_23:1;
		uint64_t qos:3;
		uint64_t wesewved_19_19:1;
		uint64_t match_type:3;
		uint64_t match_vawue:16;
#ewse
		uint64_t match_vawue:16;
		uint64_t match_type:3;
		uint64_t wesewved_19_19:1;
		uint64_t qos:3;
		uint64_t wesewved_23_23:1;
		uint64_t gwp:4;
		uint64_t wesewved_28_31:4;
		uint64_t mask:16;
		uint64_t wesewved_48_63:16;
#endif
	} cn50xx;
};

union cvmx_pip_waw_wowd {
	uint64_t u64;
	stwuct cvmx_pip_waw_wowd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t wowd:56;
#ewse
		uint64_t wowd:56;
		uint64_t wesewved_56_63:8;
#endif
	} s;
};

union cvmx_pip_sft_wst {
	uint64_t u64;
	stwuct cvmx_pip_sft_wst_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t wst:1;
#ewse
		uint64_t wst:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_pip_stat0_x {
	uint64_t u64;
	stwuct cvmx_pip_stat0_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dwp_pkts:32;
		uint64_t dwp_octs:32;
#ewse
		uint64_t dwp_octs:32;
		uint64_t dwp_pkts:32;
#endif
	} s;
};

union cvmx_pip_stat0_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat0_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dwp_pkts:32;
		uint64_t dwp_octs:32;
#ewse
		uint64_t dwp_octs:32;
		uint64_t dwp_pkts:32;
#endif
	} s;
};

union cvmx_pip_stat10_x {
	uint64_t u64;
	stwuct cvmx_pip_stat10_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_stat10_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat10_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_stat11_x {
	uint64_t u64;
	stwuct cvmx_pip_stat11_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_stat11_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat11_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_stat1_x {
	uint64_t u64;
	stwuct cvmx_pip_stat1_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pip_stat1_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat1_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pip_stat2_x {
	uint64_t u64;
	stwuct cvmx_pip_stat2_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pkts:32;
		uint64_t waw:32;
#ewse
		uint64_t waw:32;
		uint64_t pkts:32;
#endif
	} s;
};

union cvmx_pip_stat2_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat2_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pkts:32;
		uint64_t waw:32;
#ewse
		uint64_t waw:32;
		uint64_t pkts:32;
#endif
	} s;
};

union cvmx_pip_stat3_x {
	uint64_t u64;
	stwuct cvmx_pip_stat3_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcst:32;
		uint64_t mcst:32;
#ewse
		uint64_t mcst:32;
		uint64_t bcst:32;
#endif
	} s;
};

union cvmx_pip_stat3_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat3_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcst:32;
		uint64_t mcst:32;
#ewse
		uint64_t mcst:32;
		uint64_t bcst:32;
#endif
	} s;
};

union cvmx_pip_stat4_x {
	uint64_t u64;
	stwuct cvmx_pip_stat4_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h65to127:32;
		uint64_t h64:32;
#ewse
		uint64_t h64:32;
		uint64_t h65to127:32;
#endif
	} s;
};

union cvmx_pip_stat4_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat4_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h65to127:32;
		uint64_t h64:32;
#ewse
		uint64_t h64:32;
		uint64_t h65to127:32;
#endif
	} s;
};

union cvmx_pip_stat5_x {
	uint64_t u64;
	stwuct cvmx_pip_stat5_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h256to511:32;
		uint64_t h128to255:32;
#ewse
		uint64_t h128to255:32;
		uint64_t h256to511:32;
#endif
	} s;
};

union cvmx_pip_stat5_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat5_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h256to511:32;
		uint64_t h128to255:32;
#ewse
		uint64_t h128to255:32;
		uint64_t h256to511:32;
#endif
	} s;
};

union cvmx_pip_stat6_x {
	uint64_t u64;
	stwuct cvmx_pip_stat6_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h1024to1518:32;
		uint64_t h512to1023:32;
#ewse
		uint64_t h512to1023:32;
		uint64_t h1024to1518:32;
#endif
	} s;
};

union cvmx_pip_stat6_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat6_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h1024to1518:32;
		uint64_t h512to1023:32;
#ewse
		uint64_t h512to1023:32;
		uint64_t h1024to1518:32;
#endif
	} s;
};

union cvmx_pip_stat7_x {
	uint64_t u64;
	stwuct cvmx_pip_stat7_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fcs:32;
		uint64_t h1519:32;
#ewse
		uint64_t h1519:32;
		uint64_t fcs:32;
#endif
	} s;
};

union cvmx_pip_stat7_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat7_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fcs:32;
		uint64_t h1519:32;
#ewse
		uint64_t h1519:32;
		uint64_t fcs:32;
#endif
	} s;
};

union cvmx_pip_stat8_x {
	uint64_t u64;
	stwuct cvmx_pip_stat8_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fwag:32;
		uint64_t undewsz:32;
#ewse
		uint64_t undewsz:32;
		uint64_t fwag:32;
#endif
	} s;
};

union cvmx_pip_stat8_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat8_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fwag:32;
		uint64_t undewsz:32;
#ewse
		uint64_t undewsz:32;
		uint64_t fwag:32;
#endif
	} s;
};

union cvmx_pip_stat9_x {
	uint64_t u64;
	stwuct cvmx_pip_stat9_x_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t jabbew:32;
		uint64_t ovewsz:32;
#ewse
		uint64_t ovewsz:32;
		uint64_t jabbew:32;
#endif
	} s;
};

union cvmx_pip_stat9_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_stat9_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t jabbew:32;
		uint64_t ovewsz:32;
#ewse
		uint64_t ovewsz:32;
		uint64_t jabbew:32;
#endif
	} s;
};

union cvmx_pip_stat_ctw {
	uint64_t u64;
	stwuct cvmx_pip_stat_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t mode:1;
		uint64_t wesewved_1_7:7;
		uint64_t wdcww:1;
#ewse
		uint64_t wdcww:1;
		uint64_t wesewved_1_7:7;
		uint64_t mode:1;
		uint64_t wesewved_9_63:55;
#endif
	} s;
	stwuct cvmx_pip_stat_ctw_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t wdcww:1;
#ewse
		uint64_t wdcww:1;
		uint64_t wesewved_1_63:63;
#endif
	} cn30xx;
};

union cvmx_pip_stat_inb_ewwsx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_ewwsx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t ewws:16;
#ewse
		uint64_t ewws:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pip_stat_inb_ewws_pkndx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_ewws_pkndx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t ewws:16;
#ewse
		uint64_t ewws:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pip_stat_inb_octsx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_octsx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pip_stat_inb_octs_pkndx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_octs_pkndx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pip_stat_inb_pktsx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_pktsx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pkts:32;
#ewse
		uint64_t pkts:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pip_stat_inb_pkts_pkndx {
	uint64_t u64;
	stwuct cvmx_pip_stat_inb_pkts_pkndx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pkts:32;
#ewse
		uint64_t pkts:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pip_sub_pkind_fcsx {
	uint64_t u64;
	stwuct cvmx_pip_sub_pkind_fcsx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t powt_bit:64;
#ewse
		uint64_t powt_bit:64;
#endif
	} s;
};

union cvmx_pip_tag_incx {
	uint64_t u64;
	stwuct cvmx_pip_tag_incx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t en:8;
#ewse
		uint64_t en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_pip_tag_mask {
	uint64_t u64;
	stwuct cvmx_pip_tag_mask_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t mask:16;
#ewse
		uint64_t mask:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_pip_tag_secwet {
	uint64_t u64;
	stwuct cvmx_pip_tag_secwet_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t dst:16;
		uint64_t swc:16;
#ewse
		uint64_t swc:16;
		uint64_t dst:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pip_todo_entwy {
	uint64_t u64;
	stwuct cvmx_pip_todo_entwy_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t vaw:1;
		uint64_t wesewved_62_62:1;
		uint64_t entwy:62;
#ewse
		uint64_t entwy:62;
		uint64_t wesewved_62_62:1;
		uint64_t vaw:1;
#endif
	} s;
};

union cvmx_pip_vwan_etypesx {
	uint64_t u64;
	stwuct cvmx_pip_vwan_etypesx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t type3:16;
		uint64_t type2:16;
		uint64_t type1:16;
		uint64_t type0:16;
#ewse
		uint64_t type0:16;
		uint64_t type1:16;
		uint64_t type2:16;
		uint64_t type3:16;
#endif
	} s;
};

union cvmx_pip_xstat0_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat0_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dwp_pkts:32;
		uint64_t dwp_octs:32;
#ewse
		uint64_t dwp_octs:32;
		uint64_t dwp_pkts:32;
#endif
	} s;
};

union cvmx_pip_xstat10_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat10_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_xstat11_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat11_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcast:32;
		uint64_t mcast:32;
#ewse
		uint64_t mcast:32;
		uint64_t bcast:32;
#endif
	} s;
};

union cvmx_pip_xstat1_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat1_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pip_xstat2_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat2_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pkts:32;
		uint64_t waw:32;
#ewse
		uint64_t waw:32;
		uint64_t pkts:32;
#endif
	} s;
};

union cvmx_pip_xstat3_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat3_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bcst:32;
		uint64_t mcst:32;
#ewse
		uint64_t mcst:32;
		uint64_t bcst:32;
#endif
	} s;
};

union cvmx_pip_xstat4_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat4_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h65to127:32;
		uint64_t h64:32;
#ewse
		uint64_t h64:32;
		uint64_t h65to127:32;
#endif
	} s;
};

union cvmx_pip_xstat5_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat5_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h256to511:32;
		uint64_t h128to255:32;
#ewse
		uint64_t h128to255:32;
		uint64_t h256to511:32;
#endif
	} s;
};

union cvmx_pip_xstat6_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat6_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t h1024to1518:32;
		uint64_t h512to1023:32;
#ewse
		uint64_t h512to1023:32;
		uint64_t h1024to1518:32;
#endif
	} s;
};

union cvmx_pip_xstat7_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat7_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fcs:32;
		uint64_t h1519:32;
#ewse
		uint64_t h1519:32;
		uint64_t fcs:32;
#endif
	} s;
};

union cvmx_pip_xstat8_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat8_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t fwag:32;
		uint64_t undewsz:32;
#ewse
		uint64_t undewsz:32;
		uint64_t fwag:32;
#endif
	} s;
};

union cvmx_pip_xstat9_pwtx {
	uint64_t u64;
	stwuct cvmx_pip_xstat9_pwtx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t jabbew:32;
		uint64_t ovewsz:32;
#ewse
		uint64_t ovewsz:32;
		uint64_t jabbew:32;
#endif
	} s;
};

#endif
