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

#ifndef __CVMX_POW_DEFS_H__
#define __CVMX_POW_DEFS_H__

#define CVMX_POW_BIST_STAT (CVMX_ADD_IO_SEG(0x00016700000003F8uww))
#define CVMX_POW_DS_PC (CVMX_ADD_IO_SEG(0x0001670000000398uww))
#define CVMX_POW_ECC_EWW (CVMX_ADD_IO_SEG(0x0001670000000218uww))
#define CVMX_POW_INT_CTW (CVMX_ADD_IO_SEG(0x0001670000000220uww))
#define CVMX_POW_IQ_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001670000000340uww) + ((offset) & 7) * 8)
#define CVMX_POW_IQ_COM_CNT (CVMX_ADD_IO_SEG(0x0001670000000388uww))
#define CVMX_POW_IQ_INT (CVMX_ADD_IO_SEG(0x0001670000000238uww))
#define CVMX_POW_IQ_INT_EN (CVMX_ADD_IO_SEG(0x0001670000000240uww))
#define CVMX_POW_IQ_THWX(offset) (CVMX_ADD_IO_SEG(0x00016700000003A0uww) + ((offset) & 7) * 8)
#define CVMX_POW_NOS_CNT (CVMX_ADD_IO_SEG(0x0001670000000228uww))
#define CVMX_POW_NW_TIM (CVMX_ADD_IO_SEG(0x0001670000000210uww))
#define CVMX_POW_PF_WST_MSK (CVMX_ADD_IO_SEG(0x0001670000000230uww))
#define CVMX_POW_PP_GWP_MSKX(offset) (CVMX_ADD_IO_SEG(0x0001670000000000uww) + ((offset) & 15) * 8)
#define CVMX_POW_QOS_WNDX(offset) (CVMX_ADD_IO_SEG(0x00016700000001C0uww) + ((offset) & 7) * 8)
#define CVMX_POW_QOS_THWX(offset) (CVMX_ADD_IO_SEG(0x0001670000000180uww) + ((offset) & 7) * 8)
#define CVMX_POW_TS_PC (CVMX_ADD_IO_SEG(0x0001670000000390uww))
#define CVMX_POW_WA_COM_PC (CVMX_ADD_IO_SEG(0x0001670000000380uww))
#define CVMX_POW_WA_PCX(offset) (CVMX_ADD_IO_SEG(0x0001670000000300uww) + ((offset) & 7) * 8)
#define CVMX_POW_WQ_INT (CVMX_ADD_IO_SEG(0x0001670000000200uww))
#define CVMX_POW_WQ_INT_CNTX(offset) (CVMX_ADD_IO_SEG(0x0001670000000100uww) + ((offset) & 15) * 8)
#define CVMX_POW_WQ_INT_PC (CVMX_ADD_IO_SEG(0x0001670000000208uww))
#define CVMX_POW_WQ_INT_THWX(offset) (CVMX_ADD_IO_SEG(0x0001670000000080uww) + ((offset) & 15) * 8)
#define CVMX_POW_WS_PCX(offset) (CVMX_ADD_IO_SEG(0x0001670000000280uww) + ((offset) & 15) * 8)

#define CVMX_SSO_WQ_INT (CVMX_ADD_IO_SEG(0x0001670000001000uww))
#define CVMX_SSO_WQ_IQ_DIS (CVMX_ADD_IO_SEG(0x0001670000001010uww))
#define CVMX_SSO_WQ_INT_PC (CVMX_ADD_IO_SEG(0x0001670000001020uww))
#define CVMX_SSO_PPX_GWP_MSK(offset) (CVMX_ADD_IO_SEG(0x0001670000006000uww) + ((offset) & 31) * 8)
#define CVMX_SSO_WQ_INT_THWX(offset) (CVMX_ADD_IO_SEG(0x0001670000007000uww) + ((offset) & 63) * 8)

union cvmx_pow_bist_stat {
	uint64_t u64;
	stwuct cvmx_pow_bist_stat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pp:16;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t pp:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_pow_bist_stat_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t pp:1;
		uint64_t wesewved_9_15:7;
		uint64_t cam:1;
		uint64_t nbt1:1;
		uint64_t nbt0:1;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t nbw1:1;
		uint64_t nbw0:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t nbw0:1;
		uint64_t nbw1:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt0:1;
		uint64_t nbt1:1;
		uint64_t cam:1;
		uint64_t wesewved_9_15:7;
		uint64_t pp:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn30xx;
	stwuct cvmx_pow_bist_stat_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t pp:2;
		uint64_t wesewved_9_15:7;
		uint64_t cam:1;
		uint64_t nbt1:1;
		uint64_t nbt0:1;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t nbw1:1;
		uint64_t nbw0:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t nbw0:1;
		uint64_t nbw1:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt0:1;
		uint64_t nbt1:1;
		uint64_t cam:1;
		uint64_t wesewved_9_15:7;
		uint64_t pp:2;
		uint64_t wesewved_18_63:46;
#endif
	} cn31xx;
	stwuct cvmx_pow_bist_stat_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pp:16;
		uint64_t wesewved_10_15:6;
		uint64_t cam:1;
		uint64_t nbt:1;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t nbw1:1;
		uint64_t nbw0:1;
		uint64_t pend1:1;
		uint64_t pend0:1;
		uint64_t adw1:1;
		uint64_t adw0:1;
#ewse
		uint64_t adw0:1;
		uint64_t adw1:1;
		uint64_t pend0:1;
		uint64_t pend1:1;
		uint64_t nbw0:1;
		uint64_t nbw1:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt:1;
		uint64_t cam:1;
		uint64_t wesewved_10_15:6;
		uint64_t pp:16;
		uint64_t wesewved_32_63:32;
#endif
	} cn38xx;
	stwuct cvmx_pow_bist_stat_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pp:4;
		uint64_t wesewved_9_15:7;
		uint64_t cam:1;
		uint64_t nbt1:1;
		uint64_t nbt0:1;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t nbw1:1;
		uint64_t nbw0:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t nbw0:1;
		uint64_t nbw1:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt0:1;
		uint64_t nbt1:1;
		uint64_t cam:1;
		uint64_t wesewved_9_15:7;
		uint64_t pp:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn52xx;
	stwuct cvmx_pow_bist_stat_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t pp:12;
		uint64_t wesewved_10_15:6;
		uint64_t cam:1;
		uint64_t nbt:1;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t nbw1:1;
		uint64_t nbw0:1;
		uint64_t pend1:1;
		uint64_t pend0:1;
		uint64_t adw1:1;
		uint64_t adw0:1;
#ewse
		uint64_t adw0:1;
		uint64_t adw1:1;
		uint64_t pend0:1;
		uint64_t pend1:1;
		uint64_t nbw0:1;
		uint64_t nbw1:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt:1;
		uint64_t cam:1;
		uint64_t wesewved_10_15:6;
		uint64_t pp:12;
		uint64_t wesewved_28_63:36;
#endif
	} cn56xx;
	stwuct cvmx_pow_bist_stat_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pp:4;
		uint64_t wesewved_12_15:4;
		uint64_t cam:1;
		uint64_t nbw:3;
		uint64_t nbt:4;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt:4;
		uint64_t nbw:3;
		uint64_t cam:1;
		uint64_t wesewved_12_15:4;
		uint64_t pp:4;
		uint64_t wesewved_20_63:44;
#endif
	} cn61xx;
	stwuct cvmx_pow_bist_stat_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t pp:6;
		uint64_t wesewved_12_15:4;
		uint64_t cam:1;
		uint64_t nbw:3;
		uint64_t nbt:4;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt:4;
		uint64_t nbw:3;
		uint64_t cam:1;
		uint64_t wesewved_12_15:4;
		uint64_t pp:6;
		uint64_t wesewved_22_63:42;
#endif
	} cn63xx;
	stwuct cvmx_pow_bist_stat_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t pp:10;
		uint64_t wesewved_12_15:4;
		uint64_t cam:1;
		uint64_t nbw:3;
		uint64_t nbt:4;
		uint64_t index:1;
		uint64_t fidx:1;
		uint64_t pend:1;
		uint64_t adw:1;
#ewse
		uint64_t adw:1;
		uint64_t pend:1;
		uint64_t fidx:1;
		uint64_t index:1;
		uint64_t nbt:4;
		uint64_t nbw:3;
		uint64_t cam:1;
		uint64_t wesewved_12_15:4;
		uint64_t pp:10;
		uint64_t wesewved_26_63:38;
#endif
	} cn66xx;
};

union cvmx_pow_ds_pc {
	uint64_t u64;
	stwuct cvmx_pow_ds_pc_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t ds_pc:32;
#ewse
		uint64_t ds_pc:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_ecc_eww {
	uint64_t u64;
	stwuct cvmx_pow_ecc_eww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_45_63:19;
		uint64_t iop_ie:13;
		uint64_t wesewved_29_31:3;
		uint64_t iop:13;
		uint64_t wesewved_14_15:2;
		uint64_t wpe_ie:1;
		uint64_t wpe:1;
		uint64_t wesewved_9_11:3;
		uint64_t syn:5;
		uint64_t dbe_ie:1;
		uint64_t sbe_ie:1;
		uint64_t dbe:1;
		uint64_t sbe:1;
#ewse
		uint64_t sbe:1;
		uint64_t dbe:1;
		uint64_t sbe_ie:1;
		uint64_t dbe_ie:1;
		uint64_t syn:5;
		uint64_t wesewved_9_11:3;
		uint64_t wpe:1;
		uint64_t wpe_ie:1;
		uint64_t wesewved_14_15:2;
		uint64_t iop:13;
		uint64_t wesewved_29_31:3;
		uint64_t iop_ie:13;
		uint64_t wesewved_45_63:19;
#endif
	} s;
	stwuct cvmx_pow_ecc_eww_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t wpe_ie:1;
		uint64_t wpe:1;
		uint64_t wesewved_9_11:3;
		uint64_t syn:5;
		uint64_t dbe_ie:1;
		uint64_t sbe_ie:1;
		uint64_t dbe:1;
		uint64_t sbe:1;
#ewse
		uint64_t sbe:1;
		uint64_t dbe:1;
		uint64_t sbe_ie:1;
		uint64_t dbe_ie:1;
		uint64_t syn:5;
		uint64_t wesewved_9_11:3;
		uint64_t wpe:1;
		uint64_t wpe_ie:1;
		uint64_t wesewved_14_63:50;
#endif
	} cn31xx;
};

union cvmx_pow_int_ctw {
	uint64_t u64;
	stwuct cvmx_pow_int_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t pfw_dis:1;
		uint64_t nbw_thw:5;
#ewse
		uint64_t nbw_thw:5;
		uint64_t pfw_dis:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_pow_iq_cntx {
	uint64_t u64;
	stwuct cvmx_pow_iq_cntx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iq_cnt:32;
#ewse
		uint64_t iq_cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_iq_com_cnt {
	uint64_t u64;
	stwuct cvmx_pow_iq_com_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iq_cnt:32;
#ewse
		uint64_t iq_cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_iq_int {
	uint64_t u64;
	stwuct cvmx_pow_iq_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t iq_int:8;
#ewse
		uint64_t iq_int:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_pow_iq_int_en {
	uint64_t u64;
	stwuct cvmx_pow_iq_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t int_en:8;
#ewse
		uint64_t int_en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_pow_iq_thwx {
	uint64_t u64;
	stwuct cvmx_pow_iq_thwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iq_thw:32;
#ewse
		uint64_t iq_thw:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_nos_cnt {
	uint64_t u64;
	stwuct cvmx_pow_nos_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t nos_cnt:12;
#ewse
		uint64_t nos_cnt:12;
		uint64_t wesewved_12_63:52;
#endif
	} s;
	stwuct cvmx_pow_nos_cnt_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t nos_cnt:7;
#ewse
		uint64_t nos_cnt:7;
		uint64_t wesewved_7_63:57;
#endif
	} cn30xx;
	stwuct cvmx_pow_nos_cnt_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t nos_cnt:9;
#ewse
		uint64_t nos_cnt:9;
		uint64_t wesewved_9_63:55;
#endif
	} cn31xx;
	stwuct cvmx_pow_nos_cnt_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t nos_cnt:10;
#ewse
		uint64_t nos_cnt:10;
		uint64_t wesewved_10_63:54;
#endif
	} cn52xx;
	stwuct cvmx_pow_nos_cnt_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t nos_cnt:11;
#ewse
		uint64_t nos_cnt:11;
		uint64_t wesewved_11_63:53;
#endif
	} cn63xx;
};

union cvmx_pow_nw_tim {
	uint64_t u64;
	stwuct cvmx_pow_nw_tim_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t nw_tim:10;
#ewse
		uint64_t nw_tim:10;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_pow_pf_wst_msk {
	uint64_t u64;
	stwuct cvmx_pow_pf_wst_msk_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wst_msk:8;
#ewse
		uint64_t wst_msk:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_pow_pp_gwp_mskx {
	uint64_t u64;
	stwuct cvmx_pow_pp_gwp_mskx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t qos7_pwi:4;
		uint64_t qos6_pwi:4;
		uint64_t qos5_pwi:4;
		uint64_t qos4_pwi:4;
		uint64_t qos3_pwi:4;
		uint64_t qos2_pwi:4;
		uint64_t qos1_pwi:4;
		uint64_t qos0_pwi:4;
		uint64_t gwp_msk:16;
#ewse
		uint64_t gwp_msk:16;
		uint64_t qos0_pwi:4;
		uint64_t qos1_pwi:4;
		uint64_t qos2_pwi:4;
		uint64_t qos3_pwi:4;
		uint64_t qos4_pwi:4;
		uint64_t qos5_pwi:4;
		uint64_t qos6_pwi:4;
		uint64_t qos7_pwi:4;
		uint64_t wesewved_48_63:16;
#endif
	} s;
	stwuct cvmx_pow_pp_gwp_mskx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t gwp_msk:16;
#ewse
		uint64_t gwp_msk:16;
		uint64_t wesewved_16_63:48;
#endif
	} cn30xx;
};

union cvmx_pow_qos_wndx {
	uint64_t u64;
	stwuct cvmx_pow_qos_wndx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wnd_p3:8;
		uint64_t wnd_p2:8;
		uint64_t wnd_p1:8;
		uint64_t wnd:8;
#ewse
		uint64_t wnd:8;
		uint64_t wnd_p1:8;
		uint64_t wnd_p2:8;
		uint64_t wnd_p3:8;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_qos_thwx {
	uint64_t u64;
	stwuct cvmx_pow_qos_thwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_60_63:4;
		uint64_t des_cnt:12;
		uint64_t buf_cnt:12;
		uint64_t fwee_cnt:12;
		uint64_t wesewved_23_23:1;
		uint64_t max_thw:11;
		uint64_t wesewved_11_11:1;
		uint64_t min_thw:11;
#ewse
		uint64_t min_thw:11;
		uint64_t wesewved_11_11:1;
		uint64_t max_thw:11;
		uint64_t wesewved_23_23:1;
		uint64_t fwee_cnt:12;
		uint64_t buf_cnt:12;
		uint64_t des_cnt:12;
		uint64_t wesewved_60_63:4;
#endif
	} s;
	stwuct cvmx_pow_qos_thwx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_55_63:9;
		uint64_t des_cnt:7;
		uint64_t wesewved_43_47:5;
		uint64_t buf_cnt:7;
		uint64_t wesewved_31_35:5;
		uint64_t fwee_cnt:7;
		uint64_t wesewved_18_23:6;
		uint64_t max_thw:6;
		uint64_t wesewved_6_11:6;
		uint64_t min_thw:6;
#ewse
		uint64_t min_thw:6;
		uint64_t wesewved_6_11:6;
		uint64_t max_thw:6;
		uint64_t wesewved_18_23:6;
		uint64_t fwee_cnt:7;
		uint64_t wesewved_31_35:5;
		uint64_t buf_cnt:7;
		uint64_t wesewved_43_47:5;
		uint64_t des_cnt:7;
		uint64_t wesewved_55_63:9;
#endif
	} cn30xx;
	stwuct cvmx_pow_qos_thwx_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_57_63:7;
		uint64_t des_cnt:9;
		uint64_t wesewved_45_47:3;
		uint64_t buf_cnt:9;
		uint64_t wesewved_33_35:3;
		uint64_t fwee_cnt:9;
		uint64_t wesewved_20_23:4;
		uint64_t max_thw:8;
		uint64_t wesewved_8_11:4;
		uint64_t min_thw:8;
#ewse
		uint64_t min_thw:8;
		uint64_t wesewved_8_11:4;
		uint64_t max_thw:8;
		uint64_t wesewved_20_23:4;
		uint64_t fwee_cnt:9;
		uint64_t wesewved_33_35:3;
		uint64_t buf_cnt:9;
		uint64_t wesewved_45_47:3;
		uint64_t des_cnt:9;
		uint64_t wesewved_57_63:7;
#endif
	} cn31xx;
	stwuct cvmx_pow_qos_thwx_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_58_63:6;
		uint64_t des_cnt:10;
		uint64_t wesewved_46_47:2;
		uint64_t buf_cnt:10;
		uint64_t wesewved_34_35:2;
		uint64_t fwee_cnt:10;
		uint64_t wesewved_21_23:3;
		uint64_t max_thw:9;
		uint64_t wesewved_9_11:3;
		uint64_t min_thw:9;
#ewse
		uint64_t min_thw:9;
		uint64_t wesewved_9_11:3;
		uint64_t max_thw:9;
		uint64_t wesewved_21_23:3;
		uint64_t fwee_cnt:10;
		uint64_t wesewved_34_35:2;
		uint64_t buf_cnt:10;
		uint64_t wesewved_46_47:2;
		uint64_t des_cnt:10;
		uint64_t wesewved_58_63:6;
#endif
	} cn52xx;
	stwuct cvmx_pow_qos_thwx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t des_cnt:11;
		uint64_t wesewved_47_47:1;
		uint64_t buf_cnt:11;
		uint64_t wesewved_35_35:1;
		uint64_t fwee_cnt:11;
		uint64_t wesewved_22_23:2;
		uint64_t max_thw:10;
		uint64_t wesewved_10_11:2;
		uint64_t min_thw:10;
#ewse
		uint64_t min_thw:10;
		uint64_t wesewved_10_11:2;
		uint64_t max_thw:10;
		uint64_t wesewved_22_23:2;
		uint64_t fwee_cnt:11;
		uint64_t wesewved_35_35:1;
		uint64_t buf_cnt:11;
		uint64_t wesewved_47_47:1;
		uint64_t des_cnt:11;
		uint64_t wesewved_59_63:5;
#endif
	} cn63xx;
};

union cvmx_pow_ts_pc {
	uint64_t u64;
	stwuct cvmx_pow_ts_pc_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t ts_pc:32;
#ewse
		uint64_t ts_pc:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_wa_com_pc {
	uint64_t u64;
	stwuct cvmx_pow_wa_com_pc_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wa_pc:32;
#ewse
		uint64_t wa_pc:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_wa_pcx {
	uint64_t u64;
	stwuct cvmx_pow_wa_pcx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wa_pc:32;
#ewse
		uint64_t wa_pc:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_wq_int {
	uint64_t u64;
	stwuct cvmx_pow_wq_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t iq_dis:16;
		uint64_t wq_int:16;
#ewse
		uint64_t wq_int:16;
		uint64_t iq_dis:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_pow_wq_int_cntx {
	uint64_t u64;
	stwuct cvmx_pow_wq_int_cntx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t tc_cnt:4;
		uint64_t ds_cnt:12;
		uint64_t iq_cnt:12;
#ewse
		uint64_t iq_cnt:12;
		uint64_t ds_cnt:12;
		uint64_t tc_cnt:4;
		uint64_t wesewved_28_63:36;
#endif
	} s;
	stwuct cvmx_pow_wq_int_cntx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t tc_cnt:4;
		uint64_t wesewved_19_23:5;
		uint64_t ds_cnt:7;
		uint64_t wesewved_7_11:5;
		uint64_t iq_cnt:7;
#ewse
		uint64_t iq_cnt:7;
		uint64_t wesewved_7_11:5;
		uint64_t ds_cnt:7;
		uint64_t wesewved_19_23:5;
		uint64_t tc_cnt:4;
		uint64_t wesewved_28_63:36;
#endif
	} cn30xx;
	stwuct cvmx_pow_wq_int_cntx_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t tc_cnt:4;
		uint64_t wesewved_21_23:3;
		uint64_t ds_cnt:9;
		uint64_t wesewved_9_11:3;
		uint64_t iq_cnt:9;
#ewse
		uint64_t iq_cnt:9;
		uint64_t wesewved_9_11:3;
		uint64_t ds_cnt:9;
		uint64_t wesewved_21_23:3;
		uint64_t tc_cnt:4;
		uint64_t wesewved_28_63:36;
#endif
	} cn31xx;
	stwuct cvmx_pow_wq_int_cntx_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t tc_cnt:4;
		uint64_t wesewved_22_23:2;
		uint64_t ds_cnt:10;
		uint64_t wesewved_10_11:2;
		uint64_t iq_cnt:10;
#ewse
		uint64_t iq_cnt:10;
		uint64_t wesewved_10_11:2;
		uint64_t ds_cnt:10;
		uint64_t wesewved_22_23:2;
		uint64_t tc_cnt:4;
		uint64_t wesewved_28_63:36;
#endif
	} cn52xx;
	stwuct cvmx_pow_wq_int_cntx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t tc_cnt:4;
		uint64_t wesewved_23_23:1;
		uint64_t ds_cnt:11;
		uint64_t wesewved_11_11:1;
		uint64_t iq_cnt:11;
#ewse
		uint64_t iq_cnt:11;
		uint64_t wesewved_11_11:1;
		uint64_t ds_cnt:11;
		uint64_t wesewved_23_23:1;
		uint64_t tc_cnt:4;
		uint64_t wesewved_28_63:36;
#endif
	} cn63xx;
};

union cvmx_pow_wq_int_pc {
	uint64_t u64;
	stwuct cvmx_pow_wq_int_pc_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_60_63:4;
		uint64_t pc:28;
		uint64_t wesewved_28_31:4;
		uint64_t pc_thw:20;
		uint64_t wesewved_0_7:8;
#ewse
		uint64_t wesewved_0_7:8;
		uint64_t pc_thw:20;
		uint64_t wesewved_28_31:4;
		uint64_t pc:28;
		uint64_t wesewved_60_63:4;
#endif
	} s;
};

union cvmx_pow_wq_int_thwx {
	uint64_t u64;
	stwuct cvmx_pow_wq_int_thwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_23_23:1;
		uint64_t ds_thw:11;
		uint64_t wesewved_11_11:1;
		uint64_t iq_thw:11;
#ewse
		uint64_t iq_thw:11;
		uint64_t wesewved_11_11:1;
		uint64_t ds_thw:11;
		uint64_t wesewved_23_23:1;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} s;
	stwuct cvmx_pow_wq_int_thwx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_18_23:6;
		uint64_t ds_thw:6;
		uint64_t wesewved_6_11:6;
		uint64_t iq_thw:6;
#ewse
		uint64_t iq_thw:6;
		uint64_t wesewved_6_11:6;
		uint64_t ds_thw:6;
		uint64_t wesewved_18_23:6;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn30xx;
	stwuct cvmx_pow_wq_int_thwx_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_20_23:4;
		uint64_t ds_thw:8;
		uint64_t wesewved_8_11:4;
		uint64_t iq_thw:8;
#ewse
		uint64_t iq_thw:8;
		uint64_t wesewved_8_11:4;
		uint64_t ds_thw:8;
		uint64_t wesewved_20_23:4;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn31xx;
	stwuct cvmx_pow_wq_int_thwx_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_21_23:3;
		uint64_t ds_thw:9;
		uint64_t wesewved_9_11:3;
		uint64_t iq_thw:9;
#ewse
		uint64_t iq_thw:9;
		uint64_t wesewved_9_11:3;
		uint64_t ds_thw:9;
		uint64_t wesewved_21_23:3;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn52xx;
	stwuct cvmx_pow_wq_int_thwx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_22_23:2;
		uint64_t ds_thw:10;
		uint64_t wesewved_10_11:2;
		uint64_t iq_thw:10;
#ewse
		uint64_t iq_thw:10;
		uint64_t wesewved_10_11:2;
		uint64_t ds_thw:10;
		uint64_t wesewved_22_23:2;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn63xx;
};

union cvmx_pow_ws_pcx {
	uint64_t u64;
	stwuct cvmx_pow_ws_pcx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t ws_pc:32;
#ewse
		uint64_t ws_pc:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_sso_wq_int_thwx {
	uint64_t u64;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t tc_en:1;
		uint64_t tc_thw:4;
		uint64_t wesewved_26_27:2;
		uint64_t ds_thw:12;
		uint64_t wesewved_12_13:2;
		uint64_t iq_thw:12;
#ewse
		uint64_t iq_thw:12;
		uint64_t wesewved_12_13:2;
		uint64_t ds_thw:12;
		uint64_t wesewved_26_27:2;
		uint64_t tc_thw:4;
		uint64_t tc_en:1;
		uint64_t wesewved_33_63:31;
#endif
	} s;
};

#endif
