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

#ifndef __CVMX_IOB_DEFS_H__
#define __CVMX_IOB_DEFS_H__

#define CVMX_IOB_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800F00007F8uww))
#define CVMX_IOB_CTW_STATUS (CVMX_ADD_IO_SEG(0x00011800F0000050uww))
#define CVMX_IOB_DWB_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000028uww))
#define CVMX_IOB_FAU_TIMEOUT (CVMX_ADD_IO_SEG(0x00011800F0000000uww))
#define CVMX_IOB_I2C_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000010uww))
#define CVMX_IOB_INB_CONTWOW_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000078uww))
#define CVMX_IOB_INB_CONTWOW_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F0000088uww))
#define CVMX_IOB_INB_DATA_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000070uww))
#define CVMX_IOB_INB_DATA_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F0000080uww))
#define CVMX_IOB_INT_ENB (CVMX_ADD_IO_SEG(0x00011800F0000060uww))
#define CVMX_IOB_INT_SUM (CVMX_ADD_IO_SEG(0x00011800F0000058uww))
#define CVMX_IOB_N2C_W2C_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000020uww))
#define CVMX_IOB_N2C_WSP_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000008uww))
#define CVMX_IOB_OUTB_COM_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000040uww))
#define CVMX_IOB_OUTB_CONTWOW_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000098uww))
#define CVMX_IOB_OUTB_CONTWOW_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F00000A8uww))
#define CVMX_IOB_OUTB_DATA_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000090uww))
#define CVMX_IOB_OUTB_DATA_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F00000A0uww))
#define CVMX_IOB_OUTB_FPA_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000048uww))
#define CVMX_IOB_OUTB_WEQ_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000038uww))
#define CVMX_IOB_P2C_WEQ_PWI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000018uww))
#define CVMX_IOB_PKT_EWW (CVMX_ADD_IO_SEG(0x00011800F0000068uww))
#define CVMX_IOB_TO_CMB_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F00000B0uww))
#define CVMX_IOB_TO_NCB_DID_00_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000800uww))
#define CVMX_IOB_TO_NCB_DID_111_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000B78uww))
#define CVMX_IOB_TO_NCB_DID_223_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000EF8uww))
#define CVMX_IOB_TO_NCB_DID_24_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F00008C0uww))
#define CVMX_IOB_TO_NCB_DID_32_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000900uww))
#define CVMX_IOB_TO_NCB_DID_40_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000940uww))
#define CVMX_IOB_TO_NCB_DID_55_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F00009B8uww))
#define CVMX_IOB_TO_NCB_DID_64_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000A00uww))
#define CVMX_IOB_TO_NCB_DID_79_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000A78uww))
#define CVMX_IOB_TO_NCB_DID_96_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000B00uww))
#define CVMX_IOB_TO_NCB_DID_98_CWEDITS (CVMX_ADD_IO_SEG(0x00011800F0000B10uww))

union cvmx_iob_bist_status {
	uint64_t u64;
	stwuct cvmx_iob_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t ibd:1;
		uint64_t icd:1;
#ewse
		uint64_t icd:1;
		uint64_t ibd:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
	stwuct cvmx_iob_bist_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t icnwcb:1;
		uint64_t icw0:1;
		uint64_t icw1:1;
		uint64_t icnw1:1;
		uint64_t icnw0:1;
		uint64_t ibdw0:1;
		uint64_t ibdw1:1;
		uint64_t ibw0:1;
		uint64_t ibw1:1;
		uint64_t icnwt:1;
		uint64_t ibwq0:1;
		uint64_t ibwq1:1;
		uint64_t icwn0:1;
		uint64_t icwn1:1;
		uint64_t icwp0:1;
		uint64_t icwp1:1;
		uint64_t ibd:1;
		uint64_t icd:1;
#ewse
		uint64_t icd:1;
		uint64_t ibd:1;
		uint64_t icwp1:1;
		uint64_t icwp0:1;
		uint64_t icwn1:1;
		uint64_t icwn0:1;
		uint64_t ibwq1:1;
		uint64_t ibwq0:1;
		uint64_t icnwt:1;
		uint64_t ibw1:1;
		uint64_t ibw0:1;
		uint64_t ibdw1:1;
		uint64_t ibdw0:1;
		uint64_t icnw0:1;
		uint64_t icnw1:1;
		uint64_t icw1:1;
		uint64_t icw0:1;
		uint64_t icnwcb:1;
		uint64_t wesewved_18_63:46;
#endif
	} cn30xx;
	stwuct cvmx_iob_bist_status_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t xmdfif:1;
		uint64_t xmcfif:1;
		uint64_t iowfif:1;
		uint64_t wsdfif:1;
		uint64_t iocfif:1;
		uint64_t icnwcb:1;
		uint64_t icw0:1;
		uint64_t icw1:1;
		uint64_t icnw1:1;
		uint64_t icnw0:1;
		uint64_t ibdw0:1;
		uint64_t ibdw1:1;
		uint64_t ibw0:1;
		uint64_t ibw1:1;
		uint64_t icnwt:1;
		uint64_t ibwq0:1;
		uint64_t ibwq1:1;
		uint64_t icwn0:1;
		uint64_t icwn1:1;
		uint64_t icwp0:1;
		uint64_t icwp1:1;
		uint64_t ibd:1;
		uint64_t icd:1;
#ewse
		uint64_t icd:1;
		uint64_t ibd:1;
		uint64_t icwp1:1;
		uint64_t icwp0:1;
		uint64_t icwn1:1;
		uint64_t icwn0:1;
		uint64_t ibwq1:1;
		uint64_t ibwq0:1;
		uint64_t icnwt:1;
		uint64_t ibw1:1;
		uint64_t ibw0:1;
		uint64_t ibdw1:1;
		uint64_t ibdw0:1;
		uint64_t icnw0:1;
		uint64_t icnw1:1;
		uint64_t icw1:1;
		uint64_t icw0:1;
		uint64_t icnwcb:1;
		uint64_t iocfif:1;
		uint64_t wsdfif:1;
		uint64_t iowfif:1;
		uint64_t xmcfif:1;
		uint64_t xmdfif:1;
		uint64_t wesewved_23_63:41;
#endif
	} cn61xx;
	stwuct cvmx_iob_bist_status_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t xmdfif:1;
		uint64_t xmcfif:1;
		uint64_t iowfif:1;
		uint64_t wsdfif:1;
		uint64_t iocfif:1;
		uint64_t icnwcb:1;
		uint64_t icw0:1;
		uint64_t icw1:1;
		uint64_t icnw0:1;
		uint64_t ibw0:1;
		uint64_t ibw1:1;
		uint64_t icnwt:1;
		uint64_t ibwq0:1;
		uint64_t ibwq1:1;
		uint64_t icwn0:1;
		uint64_t icwn1:1;
		uint64_t ibd:1;
		uint64_t icd:1;
#ewse
		uint64_t icd:1;
		uint64_t ibd:1;
		uint64_t icwn1:1;
		uint64_t icwn0:1;
		uint64_t ibwq1:1;
		uint64_t ibwq0:1;
		uint64_t icnwt:1;
		uint64_t ibw1:1;
		uint64_t ibw0:1;
		uint64_t icnw0:1;
		uint64_t icw1:1;
		uint64_t icw0:1;
		uint64_t icnwcb:1;
		uint64_t iocfif:1;
		uint64_t wsdfif:1;
		uint64_t iowfif:1;
		uint64_t xmcfif:1;
		uint64_t xmdfif:1;
		uint64_t wesewved_18_63:46;
#endif
	} cn68xx;
};

union cvmx_iob_ctw_status {
	uint64_t u64;
	stwuct cvmx_iob_ctw_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t fif_dwy:1;
		uint64_t xmc_pew:4;
		uint64_t wesewved_5_5:1;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t wesewved_5_5:1;
		uint64_t xmc_pew:4;
		uint64_t fif_dwy:1;
		uint64_t wesewved_11_63:53;
#endif
	} s;
	stwuct cvmx_iob_ctw_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t wesewved_5_63:59;
#endif
	} cn30xx;
	stwuct cvmx_iob_ctw_status_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t ww_mode:1;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t ww_mode:1;
		uint64_t wesewved_6_63:58;
#endif
	} cn52xx;
	stwuct cvmx_iob_ctw_status_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t fif_dwy:1;
		uint64_t xmc_pew:4;
		uint64_t ww_mode:1;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t ww_mode:1;
		uint64_t xmc_pew:4;
		uint64_t fif_dwy:1;
		uint64_t wesewved_11_63:53;
#endif
	} cn61xx;
	stwuct cvmx_iob_ctw_status_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t xmc_pew:4;
		uint64_t ww_mode:1;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t ww_mode:1;
		uint64_t xmc_pew:4;
		uint64_t wesewved_10_63:54;
#endif
	} cn63xx;
	stwuct cvmx_iob_ctw_status_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t fif_dwy:1;
		uint64_t xmc_pew:4;
		uint64_t wsvw5:1;
		uint64_t outb_mat:1;
		uint64_t inb_mat:1;
		uint64_t pko_enb:1;
		uint64_t dwb_enb:1;
		uint64_t fau_end:1;
#ewse
		uint64_t fau_end:1;
		uint64_t dwb_enb:1;
		uint64_t pko_enb:1;
		uint64_t inb_mat:1;
		uint64_t outb_mat:1;
		uint64_t wsvw5:1;
		uint64_t xmc_pew:4;
		uint64_t fif_dwy:1;
		uint64_t wesewved_11_63:53;
#endif
	} cn68xx;
};

union cvmx_iob_dwb_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_dwb_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_fau_timeout {
	uint64_t u64;
	stwuct cvmx_iob_fau_timeout_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t tout_enb:1;
		uint64_t tout_vaw:12;
#ewse
		uint64_t tout_vaw:12;
		uint64_t tout_enb:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
};

union cvmx_iob_i2c_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_i2c_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_inb_contwow_match {
	uint64_t u64;
	stwuct cvmx_iob_inb_contwow_match_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t mask:8;
		uint64_t opc:4;
		uint64_t dst:9;
		uint64_t swc:8;
#ewse
		uint64_t swc:8;
		uint64_t dst:9;
		uint64_t opc:4;
		uint64_t mask:8;
		uint64_t wesewved_29_63:35;
#endif
	} s;
};

union cvmx_iob_inb_contwow_match_enb {
	uint64_t u64;
	stwuct cvmx_iob_inb_contwow_match_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t mask:8;
		uint64_t opc:4;
		uint64_t dst:9;
		uint64_t swc:8;
#ewse
		uint64_t swc:8;
		uint64_t dst:9;
		uint64_t opc:4;
		uint64_t mask:8;
		uint64_t wesewved_29_63:35;
#endif
	} s;
};

union cvmx_iob_inb_data_match {
	uint64_t u64;
	stwuct cvmx_iob_inb_data_match_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} s;
};

union cvmx_iob_inb_data_match_enb {
	uint64_t u64;
	stwuct cvmx_iob_inb_data_match_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} s;
};

union cvmx_iob_int_enb {
	uint64_t u64;
	stwuct cvmx_iob_int_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t p_dat:1;
		uint64_t np_dat:1;
		uint64_t p_eop:1;
		uint64_t p_sop:1;
		uint64_t np_eop:1;
		uint64_t np_sop:1;
#ewse
		uint64_t np_sop:1;
		uint64_t np_eop:1;
		uint64_t p_sop:1;
		uint64_t p_eop:1;
		uint64_t np_dat:1;
		uint64_t p_dat:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
	stwuct cvmx_iob_int_enb_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t p_eop:1;
		uint64_t p_sop:1;
		uint64_t np_eop:1;
		uint64_t np_sop:1;
#ewse
		uint64_t np_sop:1;
		uint64_t np_eop:1;
		uint64_t p_sop:1;
		uint64_t p_eop:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn30xx;
	stwuct cvmx_iob_int_enb_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} cn68xx;
};

union cvmx_iob_int_sum {
	uint64_t u64;
	stwuct cvmx_iob_int_sum_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t p_dat:1;
		uint64_t np_dat:1;
		uint64_t p_eop:1;
		uint64_t p_sop:1;
		uint64_t np_eop:1;
		uint64_t np_sop:1;
#ewse
		uint64_t np_sop:1;
		uint64_t np_eop:1;
		uint64_t p_sop:1;
		uint64_t p_eop:1;
		uint64_t np_dat:1;
		uint64_t p_dat:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
	stwuct cvmx_iob_int_sum_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t p_eop:1;
		uint64_t p_sop:1;
		uint64_t np_eop:1;
		uint64_t np_sop:1;
#ewse
		uint64_t np_sop:1;
		uint64_t np_eop:1;
		uint64_t p_sop:1;
		uint64_t p_eop:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn30xx;
	stwuct cvmx_iob_int_sum_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} cn68xx;
};

union cvmx_iob_n2c_w2c_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_n2c_w2c_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_n2c_wsp_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_n2c_wsp_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_outb_com_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_outb_com_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_outb_contwow_match {
	uint64_t u64;
	stwuct cvmx_iob_outb_contwow_match_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t mask:8;
		uint64_t eot:1;
		uint64_t dst:8;
		uint64_t swc:9;
#ewse
		uint64_t swc:9;
		uint64_t dst:8;
		uint64_t eot:1;
		uint64_t mask:8;
		uint64_t wesewved_26_63:38;
#endif
	} s;
};

union cvmx_iob_outb_contwow_match_enb {
	uint64_t u64;
	stwuct cvmx_iob_outb_contwow_match_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t mask:8;
		uint64_t eot:1;
		uint64_t dst:8;
		uint64_t swc:9;
#ewse
		uint64_t swc:9;
		uint64_t dst:8;
		uint64_t eot:1;
		uint64_t mask:8;
		uint64_t wesewved_26_63:38;
#endif
	} s;
};

union cvmx_iob_outb_data_match {
	uint64_t u64;
	stwuct cvmx_iob_outb_data_match_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} s;
};

union cvmx_iob_outb_data_match_enb {
	uint64_t u64;
	stwuct cvmx_iob_outb_data_match_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} s;
};

union cvmx_iob_outb_fpa_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_outb_fpa_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_outb_weq_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_outb_weq_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_p2c_weq_pwi_cnt {
	uint64_t u64;
	stwuct cvmx_iob_p2c_weq_pwi_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt_enb:1;
		uint64_t cnt_vaw:15;
#ewse
		uint64_t cnt_vaw:15;
		uint64_t cnt_enb:1;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_iob_pkt_eww {
	uint64_t u64;
	stwuct cvmx_iob_pkt_eww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t vpowt:6;
		uint64_t powt:6;
#ewse
		uint64_t powt:6;
		uint64_t vpowt:6;
		uint64_t wesewved_12_63:52;
#endif
	} s;
	stwuct cvmx_iob_pkt_eww_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t powt:6;
#ewse
		uint64_t powt:6;
		uint64_t wesewved_6_63:58;
#endif
	} cn30xx;
};

union cvmx_iob_to_cmb_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_cmb_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t ncb_wd:3;
		uint64_t ncb_ww:3;
#ewse
		uint64_t ncb_ww:3;
		uint64_t ncb_wd:3;
		uint64_t wesewved_6_63:58;
#endif
	} s;
	stwuct cvmx_iob_to_cmb_cwedits_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t pko_wd:3;
		uint64_t ncb_wd:3;
		uint64_t ncb_ww:3;
#ewse
		uint64_t ncb_ww:3;
		uint64_t ncb_wd:3;
		uint64_t pko_wd:3;
		uint64_t wesewved_9_63:55;
#endif
	} cn52xx;
	stwuct cvmx_iob_to_cmb_cwedits_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t dwb:3;
		uint64_t ncb_wd:3;
		uint64_t ncb_ww:3;
#ewse
		uint64_t ncb_ww:3;
		uint64_t ncb_wd:3;
		uint64_t dwb:3;
		uint64_t wesewved_9_63:55;
#endif
	} cn68xx;
};

union cvmx_iob_to_ncb_did_00_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_00_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_111_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_111_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_223_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_223_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_24_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_24_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_32_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_32_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_40_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_40_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_55_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_55_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_64_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_64_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_79_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_79_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_96_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_96_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_iob_to_ncb_did_98_cwedits {
	uint64_t u64;
	stwuct cvmx_iob_to_ncb_did_98_cwedits_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cwd:7;
#ewse
		uint64_t cwd:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

#endif
