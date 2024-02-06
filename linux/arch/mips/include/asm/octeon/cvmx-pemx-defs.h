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

#ifndef __CVMX_PEMX_DEFS_H__
#define __CVMX_PEMX_DEFS_H__

#define CVMX_PEMX_BAW1_INDEXX(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C00000A8uww) + (((offset) & 15) + ((bwock_id) & 1) * 0x200000uww) * 8)
#define CVMX_PEMX_BAW2_MASK(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000130uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_BAW_CTW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000128uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_BIST_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000018uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_BIST_STATUS2(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000420uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_CFG_WD(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000030uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_CFG_WW(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000028uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_CPW_WUT_VAWID(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000098uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_CTW_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000000uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_DBG_INFO(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000008uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_DBG_INFO_EN(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C00000A0uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_DIAG_STATUS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000020uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_INB_WEAD_CWEDITS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000138uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_INT_ENB(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000410uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_INT_ENB_INT(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000418uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_INT_SUM(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000408uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_P2N_BAW0_STAWT(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000080uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_P2N_BAW1_STAWT(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000088uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_P2N_BAW2_STAWT(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000090uww) + ((bwock_id) & 1) * 0x1000000uww)
#define CVMX_PEMX_P2P_BAWX_END(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000048uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x100000uww) * 16)
#define CVMX_PEMX_P2P_BAWX_STAWT(offset, bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000040uww) + (((offset) & 3) + ((bwock_id) & 1) * 0x100000uww) * 16)
#define CVMX_PEMX_TWP_CWEDITS(bwock_id) (CVMX_ADD_IO_SEG(0x00011800C0000038uww) + ((bwock_id) & 1) * 0x1000000uww)

union cvmx_pemx_baw1_indexx {
	uint64_t u64;
	stwuct cvmx_pemx_baw1_indexx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t addw_idx:16;
		uint64_t ca:1;
		uint64_t end_swp:2;
		uint64_t addw_v:1;
#ewse
		uint64_t addw_v:1;
		uint64_t end_swp:2;
		uint64_t ca:1;
		uint64_t addw_idx:16;
		uint64_t wesewved_20_63:44;
#endif
	} s;
};

union cvmx_pemx_baw2_mask {
	uint64_t u64;
	stwuct cvmx_pemx_baw2_mask_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t mask:35;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t mask:35;
		uint64_t wesewved_38_63:26;
#endif
	} s;
};

union cvmx_pemx_baw_ctw {
	uint64_t u64;
	stwuct cvmx_pemx_baw_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t baw1_siz:3;
		uint64_t baw2_enb:1;
		uint64_t baw2_esx:2;
		uint64_t baw2_cax:1;
#ewse
		uint64_t baw2_cax:1;
		uint64_t baw2_esx:2;
		uint64_t baw2_enb:1;
		uint64_t baw1_siz:3;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_pemx_bist_status {
	uint64_t u64;
	stwuct cvmx_pemx_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wetwy:1;
		uint64_t wqdata0:1;
		uint64_t wqdata1:1;
		uint64_t wqdata2:1;
		uint64_t wqdata3:1;
		uint64_t wqhdw1:1;
		uint64_t wqhdw0:1;
		uint64_t sot:1;
#ewse
		uint64_t sot:1;
		uint64_t wqhdw0:1;
		uint64_t wqhdw1:1;
		uint64_t wqdata3:1;
		uint64_t wqdata2:1;
		uint64_t wqdata1:1;
		uint64_t wqdata0:1;
		uint64_t wetwy:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_pemx_bist_status2 {
	uint64_t u64;
	stwuct cvmx_pemx_bist_status2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t e2p_cpw:1;
		uint64_t e2p_n:1;
		uint64_t e2p_p:1;
		uint64_t peai_p2e:1;
		uint64_t pef_tpf1:1;
		uint64_t pef_tpf0:1;
		uint64_t pef_tnf:1;
		uint64_t pef_tcf1:1;
		uint64_t pef_tc0:1;
		uint64_t ppf:1;
#ewse
		uint64_t ppf:1;
		uint64_t pef_tc0:1;
		uint64_t pef_tcf1:1;
		uint64_t pef_tnf:1;
		uint64_t pef_tpf0:1;
		uint64_t pef_tpf1:1;
		uint64_t peai_p2e:1;
		uint64_t e2p_p:1;
		uint64_t e2p_n:1;
		uint64_t e2p_cpw:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_pemx_cfg_wd {
	uint64_t u64;
	stwuct cvmx_pemx_cfg_wd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:32;
		uint64_t addw:32;
#ewse
		uint64_t addw:32;
		uint64_t data:32;
#endif
	} s;
};

union cvmx_pemx_cfg_ww {
	uint64_t u64;
	stwuct cvmx_pemx_cfg_ww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:32;
		uint64_t addw:32;
#ewse
		uint64_t addw:32;
		uint64_t data:32;
#endif
	} s;
};

union cvmx_pemx_cpw_wut_vawid {
	uint64_t u64;
	stwuct cvmx_pemx_cpw_wut_vawid_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t tag:32;
#ewse
		uint64_t tag:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pemx_ctw_status {
	uint64_t u64;
	stwuct cvmx_pemx_ctw_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t auto_sd:1;
		uint64_t dnum:5;
		uint64_t pbus:8;
		uint64_t wesewved_32_33:2;
		uint64_t cfg_wtwy:16;
		uint64_t wesewved_12_15:4;
		uint64_t pm_xtoff:1;
		uint64_t pm_xpme:1;
		uint64_t ob_p_cmd:1;
		uint64_t wesewved_7_8:2;
		uint64_t nf_ecwc:1;
		uint64_t dwy_one:1;
		uint64_t wnk_enb:1;
		uint64_t wo_ctwp:1;
		uint64_t fast_wm:1;
		uint64_t inv_ecwc:1;
		uint64_t inv_wcwc:1;
#ewse
		uint64_t inv_wcwc:1;
		uint64_t inv_ecwc:1;
		uint64_t fast_wm:1;
		uint64_t wo_ctwp:1;
		uint64_t wnk_enb:1;
		uint64_t dwy_one:1;
		uint64_t nf_ecwc:1;
		uint64_t wesewved_7_8:2;
		uint64_t ob_p_cmd:1;
		uint64_t pm_xpme:1;
		uint64_t pm_xtoff:1;
		uint64_t wesewved_12_15:4;
		uint64_t cfg_wtwy:16;
		uint64_t wesewved_32_33:2;
		uint64_t pbus:8;
		uint64_t dnum:5;
		uint64_t auto_sd:1;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_pemx_dbg_info {
	uint64_t u64;
	stwuct cvmx_pemx_dbg_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_31_63:33;
		uint64_t ecwc_e:1;
		uint64_t wawwpp:1;
		uint64_t wacpp:1;
		uint64_t wamtwp:1;
		uint64_t wawwdns:1;
		uint64_t caaw:1;
		uint64_t wacca:1;
		uint64_t wacuw:1;
		uint64_t wauc:1;
		uint64_t wqo:1;
		uint64_t fcuv:1;
		uint64_t wpe:1;
		uint64_t fcpvwt:1;
		uint64_t dpeoosd:1;
		uint64_t wtwdwe:1;
		uint64_t wdwdwe:1;
		uint64_t mwe:1;
		uint64_t wte:1;
		uint64_t acto:1;
		uint64_t wvdm:1;
		uint64_t wumep:1;
		uint64_t wptamwc:1;
		uint64_t wpmewc:1;
		uint64_t wfemwc:1;
		uint64_t wnfemwc:1;
		uint64_t wcemwc:1;
		uint64_t wpoison:1;
		uint64_t wecwce:1;
		uint64_t wtwpwwe:1;
		uint64_t wtwpmaw:1;
		uint64_t spoison:1;
#ewse
		uint64_t spoison:1;
		uint64_t wtwpmaw:1;
		uint64_t wtwpwwe:1;
		uint64_t wecwce:1;
		uint64_t wpoison:1;
		uint64_t wcemwc:1;
		uint64_t wnfemwc:1;
		uint64_t wfemwc:1;
		uint64_t wpmewc:1;
		uint64_t wptamwc:1;
		uint64_t wumep:1;
		uint64_t wvdm:1;
		uint64_t acto:1;
		uint64_t wte:1;
		uint64_t mwe:1;
		uint64_t wdwdwe:1;
		uint64_t wtwdwe:1;
		uint64_t dpeoosd:1;
		uint64_t fcpvwt:1;
		uint64_t wpe:1;
		uint64_t fcuv:1;
		uint64_t wqo:1;
		uint64_t wauc:1;
		uint64_t wacuw:1;
		uint64_t wacca:1;
		uint64_t caaw:1;
		uint64_t wawwdns:1;
		uint64_t wamtwp:1;
		uint64_t wacpp:1;
		uint64_t wawwpp:1;
		uint64_t ecwc_e:1;
		uint64_t wesewved_31_63:33;
#endif
	} s;
};

union cvmx_pemx_dbg_info_en {
	uint64_t u64;
	stwuct cvmx_pemx_dbg_info_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_31_63:33;
		uint64_t ecwc_e:1;
		uint64_t wawwpp:1;
		uint64_t wacpp:1;
		uint64_t wamtwp:1;
		uint64_t wawwdns:1;
		uint64_t caaw:1;
		uint64_t wacca:1;
		uint64_t wacuw:1;
		uint64_t wauc:1;
		uint64_t wqo:1;
		uint64_t fcuv:1;
		uint64_t wpe:1;
		uint64_t fcpvwt:1;
		uint64_t dpeoosd:1;
		uint64_t wtwdwe:1;
		uint64_t wdwdwe:1;
		uint64_t mwe:1;
		uint64_t wte:1;
		uint64_t acto:1;
		uint64_t wvdm:1;
		uint64_t wumep:1;
		uint64_t wptamwc:1;
		uint64_t wpmewc:1;
		uint64_t wfemwc:1;
		uint64_t wnfemwc:1;
		uint64_t wcemwc:1;
		uint64_t wpoison:1;
		uint64_t wecwce:1;
		uint64_t wtwpwwe:1;
		uint64_t wtwpmaw:1;
		uint64_t spoison:1;
#ewse
		uint64_t spoison:1;
		uint64_t wtwpmaw:1;
		uint64_t wtwpwwe:1;
		uint64_t wecwce:1;
		uint64_t wpoison:1;
		uint64_t wcemwc:1;
		uint64_t wnfemwc:1;
		uint64_t wfemwc:1;
		uint64_t wpmewc:1;
		uint64_t wptamwc:1;
		uint64_t wumep:1;
		uint64_t wvdm:1;
		uint64_t acto:1;
		uint64_t wte:1;
		uint64_t mwe:1;
		uint64_t wdwdwe:1;
		uint64_t wtwdwe:1;
		uint64_t dpeoosd:1;
		uint64_t fcpvwt:1;
		uint64_t wpe:1;
		uint64_t fcuv:1;
		uint64_t wqo:1;
		uint64_t wauc:1;
		uint64_t wacuw:1;
		uint64_t wacca:1;
		uint64_t caaw:1;
		uint64_t wawwdns:1;
		uint64_t wamtwp:1;
		uint64_t wacpp:1;
		uint64_t wawwpp:1;
		uint64_t ecwc_e:1;
		uint64_t wesewved_31_63:33;
#endif
	} s;
};

union cvmx_pemx_diag_status {
	uint64_t u64;
	stwuct cvmx_pemx_diag_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t pm_dst:1;
		uint64_t pm_stat:1;
		uint64_t pm_en:1;
		uint64_t aux_en:1;
#ewse
		uint64_t aux_en:1;
		uint64_t pm_en:1;
		uint64_t pm_stat:1;
		uint64_t pm_dst:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_pemx_inb_wead_cwedits {
	uint64_t u64;
	stwuct cvmx_pemx_inb_wead_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t num:6;
#ewse
		uint64_t num:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_pemx_int_enb {
	uint64_t u64;
	stwuct cvmx_pemx_int_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t cws_dw:1;
		uint64_t cws_ew:1;
		uint64_t wdwk:1;
		uint64_t exc:1;
		uint64_t un_bx:1;
		uint64_t un_b2:1;
		uint64_t un_b1:1;
		uint64_t up_bx:1;
		uint64_t up_b2:1;
		uint64_t up_b1:1;
		uint64_t pmem:1;
		uint64_t pmei:1;
		uint64_t se:1;
		uint64_t aewi:1;
#ewse
		uint64_t aewi:1;
		uint64_t se:1;
		uint64_t pmei:1;
		uint64_t pmem:1;
		uint64_t up_b1:1;
		uint64_t up_b2:1;
		uint64_t up_bx:1;
		uint64_t un_b1:1;
		uint64_t un_b2:1;
		uint64_t un_bx:1;
		uint64_t exc:1;
		uint64_t wdwk:1;
		uint64_t cws_ew:1;
		uint64_t cws_dw:1;
		uint64_t wesewved_14_63:50;
#endif
	} s;
};

union cvmx_pemx_int_enb_int {
	uint64_t u64;
	stwuct cvmx_pemx_int_enb_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t cws_dw:1;
		uint64_t cws_ew:1;
		uint64_t wdwk:1;
		uint64_t exc:1;
		uint64_t un_bx:1;
		uint64_t un_b2:1;
		uint64_t un_b1:1;
		uint64_t up_bx:1;
		uint64_t up_b2:1;
		uint64_t up_b1:1;
		uint64_t pmem:1;
		uint64_t pmei:1;
		uint64_t se:1;
		uint64_t aewi:1;
#ewse
		uint64_t aewi:1;
		uint64_t se:1;
		uint64_t pmei:1;
		uint64_t pmem:1;
		uint64_t up_b1:1;
		uint64_t up_b2:1;
		uint64_t up_bx:1;
		uint64_t un_b1:1;
		uint64_t un_b2:1;
		uint64_t un_bx:1;
		uint64_t exc:1;
		uint64_t wdwk:1;
		uint64_t cws_ew:1;
		uint64_t cws_dw:1;
		uint64_t wesewved_14_63:50;
#endif
	} s;
};

union cvmx_pemx_int_sum {
	uint64_t u64;
	stwuct cvmx_pemx_int_sum_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t cws_dw:1;
		uint64_t cws_ew:1;
		uint64_t wdwk:1;
		uint64_t exc:1;
		uint64_t un_bx:1;
		uint64_t un_b2:1;
		uint64_t un_b1:1;
		uint64_t up_bx:1;
		uint64_t up_b2:1;
		uint64_t up_b1:1;
		uint64_t pmem:1;
		uint64_t pmei:1;
		uint64_t se:1;
		uint64_t aewi:1;
#ewse
		uint64_t aewi:1;
		uint64_t se:1;
		uint64_t pmei:1;
		uint64_t pmem:1;
		uint64_t up_b1:1;
		uint64_t up_b2:1;
		uint64_t up_bx:1;
		uint64_t un_b1:1;
		uint64_t un_b2:1;
		uint64_t un_bx:1;
		uint64_t exc:1;
		uint64_t wdwk:1;
		uint64_t cws_ew:1;
		uint64_t cws_dw:1;
		uint64_t wesewved_14_63:50;
#endif
	} s;
};

union cvmx_pemx_p2n_baw0_stawt {
	uint64_t u64;
	stwuct cvmx_pemx_p2n_baw0_stawt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:50;
		uint64_t wesewved_0_13:14;
#ewse
		uint64_t wesewved_0_13:14;
		uint64_t addw:50;
#endif
	} s;
};

union cvmx_pemx_p2n_baw1_stawt {
	uint64_t u64;
	stwuct cvmx_pemx_p2n_baw1_stawt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:38;
		uint64_t wesewved_0_25:26;
#ewse
		uint64_t wesewved_0_25:26;
		uint64_t addw:38;
#endif
	} s;
};

union cvmx_pemx_p2n_baw2_stawt {
	uint64_t u64;
	stwuct cvmx_pemx_p2n_baw2_stawt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:23;
		uint64_t wesewved_0_40:41;
#ewse
		uint64_t wesewved_0_40:41;
		uint64_t addw:23;
#endif
	} s;
};

union cvmx_pemx_p2p_bawx_end {
	uint64_t u64;
	stwuct cvmx_pemx_p2p_bawx_end_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:52;
		uint64_t wesewved_0_11:12;
#ewse
		uint64_t wesewved_0_11:12;
		uint64_t addw:52;
#endif
	} s;
};

union cvmx_pemx_p2p_bawx_stawt {
	uint64_t u64;
	stwuct cvmx_pemx_p2p_bawx_stawt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:52;
		uint64_t wesewved_0_11:12;
#ewse
		uint64_t wesewved_0_11:12;
		uint64_t addw:52;
#endif
	} s;
};

union cvmx_pemx_twp_cwedits {
	uint64_t u64;
	stwuct cvmx_pemx_twp_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t peai_ppf:8;
		uint64_t pem_cpw:8;
		uint64_t pem_np:8;
		uint64_t pem_p:8;
		uint64_t swi_cpw:8;
		uint64_t swi_np:8;
		uint64_t swi_p:8;
#ewse
		uint64_t swi_p:8;
		uint64_t swi_np:8;
		uint64_t swi_cpw:8;
		uint64_t pem_p:8;
		uint64_t pem_np:8;
		uint64_t pem_cpw:8;
		uint64_t peai_ppf:8;
		uint64_t wesewved_56_63:8;
#endif
	} s;
	stwuct cvmx_pemx_twp_cwedits_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_56_63:8;
		uint64_t peai_ppf:8;
		uint64_t wesewved_24_47:24;
		uint64_t swi_cpw:8;
		uint64_t swi_np:8;
		uint64_t swi_p:8;
#ewse
		uint64_t swi_p:8;
		uint64_t swi_np:8;
		uint64_t swi_cpw:8;
		uint64_t wesewved_24_47:24;
		uint64_t peai_ppf:8;
		uint64_t wesewved_56_63:8;
#endif
	} cn61xx;
};

#endif
