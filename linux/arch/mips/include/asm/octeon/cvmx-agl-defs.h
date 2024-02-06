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

#ifndef __CVMX_AGW_DEFS_H__
#define __CVMX_AGW_DEFS_H__

#define CVMX_AGW_GMX_BAD_WEG (CVMX_ADD_IO_SEG(0x00011800E0000518uww))
#define CVMX_AGW_GMX_BIST (CVMX_ADD_IO_SEG(0x00011800E0000400uww))
#define CVMX_AGW_GMX_DWV_CTW (CVMX_ADD_IO_SEG(0x00011800E00007F0uww))
#define CVMX_AGW_GMX_INF_MODE (CVMX_ADD_IO_SEG(0x00011800E00007F8uww))
#define CVMX_AGW_GMX_PWTX_CFG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000010uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM0(offset) (CVMX_ADD_IO_SEG(0x00011800E0000180uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM1(offset) (CVMX_ADD_IO_SEG(0x00011800E0000188uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM2(offset) (CVMX_ADD_IO_SEG(0x00011800E0000190uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM3(offset) (CVMX_ADD_IO_SEG(0x00011800E0000198uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM4(offset) (CVMX_ADD_IO_SEG(0x00011800E00001A0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM5(offset) (CVMX_ADD_IO_SEG(0x00011800E00001A8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CAM_EN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000108uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_ADW_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000100uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_DECISION(offset) (CVMX_ADD_IO_SEG(0x00011800E0000040uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_FWM_CHK(offset) (CVMX_ADD_IO_SEG(0x00011800E0000020uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_FWM_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000018uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_FWM_MAX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000030uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_FWM_MIN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000028uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_IFG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000058uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_INT_EN(offset) (CVMX_ADD_IO_SEG(0x00011800E0000008uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_INT_WEG(offset) (CVMX_ADD_IO_SEG(0x00011800E0000000uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_JABBEW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000038uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_PAUSE_DWOP_TIME(offset) (CVMX_ADD_IO_SEG(0x00011800E0000068uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_WX_INBND(offset) (CVMX_ADD_IO_SEG(0x00011800E0000060uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000050uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_OCTS(offset) (CVMX_ADD_IO_SEG(0x00011800E0000088uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_OCTS_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000098uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_OCTS_DMAC(offset) (CVMX_ADD_IO_SEG(0x00011800E00000A8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_OCTS_DWP(offset) (CVMX_ADD_IO_SEG(0x00011800E00000B8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_PKTS(offset) (CVMX_ADD_IO_SEG(0x00011800E0000080uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_PKTS_BAD(offset) (CVMX_ADD_IO_SEG(0x00011800E00000C0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_PKTS_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000090uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_PKTS_DMAC(offset) (CVMX_ADD_IO_SEG(0x00011800E00000A0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_STATS_PKTS_DWP(offset) (CVMX_ADD_IO_SEG(0x00011800E00000B0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WXX_UDD_SKP(offset) (CVMX_ADD_IO_SEG(0x00011800E0000048uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_WX_BP_DWOPX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000420uww) + ((offset) & 1) * 8)
#define CVMX_AGW_GMX_WX_BP_OFFX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000460uww) + ((offset) & 1) * 8)
#define CVMX_AGW_GMX_WX_BP_ONX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000440uww) + ((offset) & 1) * 8)
#define CVMX_AGW_GMX_WX_PWT_INFO (CVMX_ADD_IO_SEG(0x00011800E00004E8uww))
#define CVMX_AGW_GMX_WX_TX_STATUS (CVMX_ADD_IO_SEG(0x00011800E00007E8uww))
#define CVMX_AGW_GMX_SMACX(offset) (CVMX_ADD_IO_SEG(0x00011800E0000230uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_STAT_BP (CVMX_ADD_IO_SEG(0x00011800E0000520uww))
#define CVMX_AGW_GMX_TXX_APPEND(offset) (CVMX_ADD_IO_SEG(0x00011800E0000218uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_CWK(offset) (CVMX_ADD_IO_SEG(0x00011800E0000208uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000270uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_MIN_PKT(offset) (CVMX_ADD_IO_SEG(0x00011800E0000240uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_PAUSE_PKT_INTEWVAW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000248uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_PAUSE_PKT_TIME(offset) (CVMX_ADD_IO_SEG(0x00011800E0000238uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_PAUSE_TOGO(offset) (CVMX_ADD_IO_SEG(0x00011800E0000258uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_PAUSE_ZEWO(offset) (CVMX_ADD_IO_SEG(0x00011800E0000260uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_SOFT_PAUSE(offset) (CVMX_ADD_IO_SEG(0x00011800E0000250uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT0(offset) (CVMX_ADD_IO_SEG(0x00011800E0000280uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT1(offset) (CVMX_ADD_IO_SEG(0x00011800E0000288uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT2(offset) (CVMX_ADD_IO_SEG(0x00011800E0000290uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT3(offset) (CVMX_ADD_IO_SEG(0x00011800E0000298uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT4(offset) (CVMX_ADD_IO_SEG(0x00011800E00002A0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT5(offset) (CVMX_ADD_IO_SEG(0x00011800E00002A8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT6(offset) (CVMX_ADD_IO_SEG(0x00011800E00002B0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT7(offset) (CVMX_ADD_IO_SEG(0x00011800E00002B8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT8(offset) (CVMX_ADD_IO_SEG(0x00011800E00002C0uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STAT9(offset) (CVMX_ADD_IO_SEG(0x00011800E00002C8uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_STATS_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0000268uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TXX_THWESH(offset) (CVMX_ADD_IO_SEG(0x00011800E0000210uww) + ((offset) & 1) * 2048)
#define CVMX_AGW_GMX_TX_BP (CVMX_ADD_IO_SEG(0x00011800E00004D0uww))
#define CVMX_AGW_GMX_TX_COW_ATTEMPT (CVMX_ADD_IO_SEG(0x00011800E0000498uww))
#define CVMX_AGW_GMX_TX_IFG (CVMX_ADD_IO_SEG(0x00011800E0000488uww))
#define CVMX_AGW_GMX_TX_INT_EN (CVMX_ADD_IO_SEG(0x00011800E0000508uww))
#define CVMX_AGW_GMX_TX_INT_WEG (CVMX_ADD_IO_SEG(0x00011800E0000500uww))
#define CVMX_AGW_GMX_TX_JAM (CVMX_ADD_IO_SEG(0x00011800E0000490uww))
#define CVMX_AGW_GMX_TX_WFSW (CVMX_ADD_IO_SEG(0x00011800E00004F8uww))
#define CVMX_AGW_GMX_TX_OVW_BP (CVMX_ADD_IO_SEG(0x00011800E00004C8uww))
#define CVMX_AGW_GMX_TX_PAUSE_PKT_DMAC (CVMX_ADD_IO_SEG(0x00011800E00004A0uww))
#define CVMX_AGW_GMX_TX_PAUSE_PKT_TYPE (CVMX_ADD_IO_SEG(0x00011800E00004A8uww))
#define CVMX_AGW_PWTX_CTW(offset) (CVMX_ADD_IO_SEG(0x00011800E0002000uww) + ((offset) & 1) * 8)

union cvmx_agw_gmx_bad_weg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_bad_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t txpsh1:1;
		uint64_t txpop1:1;
		uint64_t ovwfww1:1;
		uint64_t txpsh:1;
		uint64_t txpop:1;
		uint64_t ovwfww:1;
		uint64_t wesewved_27_31:5;
		uint64_t statovw:1;
		uint64_t wesewved_24_25:2;
		uint64_t woststat:2;
		uint64_t wesewved_4_21:18;
		uint64_t out_ovw:2;
		uint64_t wesewved_0_1:2;
#ewse
		uint64_t wesewved_0_1:2;
		uint64_t out_ovw:2;
		uint64_t wesewved_4_21:18;
		uint64_t woststat:2;
		uint64_t wesewved_24_25:2;
		uint64_t statovw:1;
		uint64_t wesewved_27_31:5;
		uint64_t ovwfww:1;
		uint64_t txpop:1;
		uint64_t txpsh:1;
		uint64_t ovwfww1:1;
		uint64_t txpop1:1;
		uint64_t txpsh1:1;
		uint64_t wesewved_38_63:26;
#endif
	} s;
	stwuct cvmx_agw_gmx_bad_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t txpsh1:1;
		uint64_t txpop1:1;
		uint64_t ovwfww1:1;
		uint64_t txpsh:1;
		uint64_t txpop:1;
		uint64_t ovwfww:1;
		uint64_t wesewved_27_31:5;
		uint64_t statovw:1;
		uint64_t wesewved_23_25:3;
		uint64_t woststat:1;
		uint64_t wesewved_4_21:18;
		uint64_t out_ovw:2;
		uint64_t wesewved_0_1:2;
#ewse
		uint64_t wesewved_0_1:2;
		uint64_t out_ovw:2;
		uint64_t wesewved_4_21:18;
		uint64_t woststat:1;
		uint64_t wesewved_23_25:3;
		uint64_t statovw:1;
		uint64_t wesewved_27_31:5;
		uint64_t ovwfww:1;
		uint64_t txpop:1;
		uint64_t txpsh:1;
		uint64_t ovwfww1:1;
		uint64_t txpop1:1;
		uint64_t txpsh1:1;
		uint64_t wesewved_38_63:26;
#endif
	} cn52xx;
	stwuct cvmx_agw_gmx_bad_weg_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t txpsh:1;
		uint64_t txpop:1;
		uint64_t ovwfww:1;
		uint64_t wesewved_27_31:5;
		uint64_t statovw:1;
		uint64_t wesewved_23_25:3;
		uint64_t woststat:1;
		uint64_t wesewved_3_21:19;
		uint64_t out_ovw:1;
		uint64_t wesewved_0_1:2;
#ewse
		uint64_t wesewved_0_1:2;
		uint64_t out_ovw:1;
		uint64_t wesewved_3_21:19;
		uint64_t woststat:1;
		uint64_t wesewved_23_25:3;
		uint64_t statovw:1;
		uint64_t wesewved_27_31:5;
		uint64_t ovwfww:1;
		uint64_t txpop:1;
		uint64_t txpsh:1;
		uint64_t wesewved_35_63:29;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_bist {
	uint64_t u64;
	stwuct cvmx_agw_gmx_bist_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t status:25;
#ewse
		uint64_t status:25;
		uint64_t wesewved_25_63:39;
#endif
	} s;
	stwuct cvmx_agw_gmx_bist_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t status:10;
#ewse
		uint64_t status:10;
		uint64_t wesewved_10_63:54;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_dwv_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_dwv_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t byp_en1:1;
		uint64_t wesewved_45_47:3;
		uint64_t pctw1:5;
		uint64_t wesewved_37_39:3;
		uint64_t nctw1:5;
		uint64_t wesewved_17_31:15;
		uint64_t byp_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t pctw:5;
		uint64_t wesewved_5_7:3;
		uint64_t nctw:5;
#ewse
		uint64_t nctw:5;
		uint64_t wesewved_5_7:3;
		uint64_t pctw:5;
		uint64_t wesewved_13_15:3;
		uint64_t byp_en:1;
		uint64_t wesewved_17_31:15;
		uint64_t nctw1:5;
		uint64_t wesewved_37_39:3;
		uint64_t pctw1:5;
		uint64_t wesewved_45_47:3;
		uint64_t byp_en1:1;
		uint64_t wesewved_49_63:15;
#endif
	} s;
	stwuct cvmx_agw_gmx_dwv_ctw_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t byp_en:1;
		uint64_t wesewved_13_15:3;
		uint64_t pctw:5;
		uint64_t wesewved_5_7:3;
		uint64_t nctw:5;
#ewse
		uint64_t nctw:5;
		uint64_t wesewved_5_7:3;
		uint64_t pctw:5;
		uint64_t wesewved_13_15:3;
		uint64_t byp_en:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_inf_mode {
	uint64_t u64;
	stwuct cvmx_agw_gmx_inf_mode_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t en:1;
		uint64_t wesewved_0_0:1;
#ewse
		uint64_t wesewved_0_0:1;
		uint64_t en:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_agw_gmx_pwtx_cfg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_pwtx_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t tx_idwe:1;
		uint64_t wx_idwe:1;
		uint64_t wesewved_9_11:3;
		uint64_t speed_msb:1;
		uint64_t wesewved_7_7:1;
		uint64_t buwst:1;
		uint64_t tx_en:1;
		uint64_t wx_en:1;
		uint64_t swottime:1;
		uint64_t dupwex:1;
		uint64_t speed:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t speed:1;
		uint64_t dupwex:1;
		uint64_t swottime:1;
		uint64_t wx_en:1;
		uint64_t tx_en:1;
		uint64_t buwst:1;
		uint64_t wesewved_7_7:1;
		uint64_t speed_msb:1;
		uint64_t wesewved_9_11:3;
		uint64_t wx_idwe:1;
		uint64_t tx_idwe:1;
		uint64_t wesewved_14_63:50;
#endif
	} s;
	stwuct cvmx_agw_gmx_pwtx_cfg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t tx_en:1;
		uint64_t wx_en:1;
		uint64_t swottime:1;
		uint64_t dupwex:1;
		uint64_t speed:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t speed:1;
		uint64_t dupwex:1;
		uint64_t swottime:1;
		uint64_t wx_en:1;
		uint64_t tx_en:1;
		uint64_t wesewved_6_63:58;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_wxx_adw_cam0 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam1 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam2 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam3 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam4 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam4_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam5 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam5_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t adw:64;
#ewse
		uint64_t adw:64;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_cam_en {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_cam_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t en:8;
#ewse
		uint64_t en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_adw_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_adw_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t cam_mode:1;
		uint64_t mcst:2;
		uint64_t bcst:1;
#ewse
		uint64_t bcst:1;
		uint64_t mcst:2;
		uint64_t cam_mode:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_decision {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_decision_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t cnt:5;
#ewse
		uint64_t cnt:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_fwm_chk {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_fwm_chk_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_agw_gmx_wxx_fwm_chk_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t wesewved_1_1:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t wesewved_1_1:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_wxx_fwm_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_fwm_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t ptp_mode:1;
		uint64_t wesewved_11_11:1;
		uint64_t nuww_dis:1;
		uint64_t pwe_awign:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t pwe_awign:1;
		uint64_t nuww_dis:1;
		uint64_t wesewved_11_11:1;
		uint64_t ptp_mode:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_agw_gmx_wxx_fwm_ctw_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pwe_awign:1;
		uint64_t pad_wen:1;
		uint64_t vwan_wen:1;
		uint64_t pwe_fwee:1;
		uint64_t ctw_smac:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_dwp:1;
		uint64_t pwe_stwp:1;
		uint64_t pwe_chk:1;
#ewse
		uint64_t pwe_chk:1;
		uint64_t pwe_stwp:1;
		uint64_t ctw_dwp:1;
		uint64_t ctw_bck:1;
		uint64_t ctw_mcst:1;
		uint64_t ctw_smac:1;
		uint64_t pwe_fwee:1;
		uint64_t vwan_wen:1;
		uint64_t pad_wen:1;
		uint64_t pwe_awign:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_wxx_fwm_max {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_fwm_max_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wen:16;
#ewse
		uint64_t wen:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_fwm_min {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_fwm_min_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wen:16;
#ewse
		uint64_t wen:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_ifg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_ifg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t ifg:4;
#ewse
		uint64_t ifg:4;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_int_en {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} s;
	stwuct cvmx_agw_gmx_wxx_int_en_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t wesewved_1_1:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t wesewved_1_1:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_wxx_int_weg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t phy_dupx:1;
		uint64_t phy_spd:1;
		uint64_t phy_wink:1;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t nibeww:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t cawext:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t cawext:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t nibeww:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t phy_wink:1;
		uint64_t phy_spd:1;
		uint64_t phy_dupx:1;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} s;
	stwuct cvmx_agw_gmx_wxx_int_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t pause_dwp:1;
		uint64_t wesewved_16_18:3;
		uint64_t ifgeww:1;
		uint64_t cowdet:1;
		uint64_t faweww:1;
		uint64_t wsveww:1;
		uint64_t pcteww:1;
		uint64_t ovweww:1;
		uint64_t wesewved_9_9:1;
		uint64_t skpeww:1;
		uint64_t wcveww:1;
		uint64_t weneww:1;
		uint64_t awneww:1;
		uint64_t fcseww:1;
		uint64_t jabbew:1;
		uint64_t maxeww:1;
		uint64_t wesewved_1_1:1;
		uint64_t mineww:1;
#ewse
		uint64_t mineww:1;
		uint64_t wesewved_1_1:1;
		uint64_t maxeww:1;
		uint64_t jabbew:1;
		uint64_t fcseww:1;
		uint64_t awneww:1;
		uint64_t weneww:1;
		uint64_t wcveww:1;
		uint64_t skpeww:1;
		uint64_t wesewved_9_9:1;
		uint64_t ovweww:1;
		uint64_t pcteww:1;
		uint64_t wsveww:1;
		uint64_t faweww:1;
		uint64_t cowdet:1;
		uint64_t ifgeww:1;
		uint64_t wesewved_16_18:3;
		uint64_t pause_dwp:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn52xx;
};

union cvmx_agw_gmx_wxx_jabbew {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_jabbew_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt:16;
#ewse
		uint64_t cnt:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_pause_dwop_time {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_pause_dwop_time_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t status:16;
#ewse
		uint64_t status:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_wx_inbnd {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_wx_inbnd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t dupwex:1;
		uint64_t speed:2;
		uint64_t status:1;
#ewse
		uint64_t status:1;
		uint64_t speed:2;
		uint64_t dupwex:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t wd_cww:1;
#ewse
		uint64_t wd_cww:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_octs {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_octs_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t cnt:48;
#ewse
		uint64_t cnt:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_octs_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_octs_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t cnt:48;
#ewse
		uint64_t cnt:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_octs_dmac {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_octs_dmac_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t cnt:48;
#ewse
		uint64_t cnt:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_octs_dwp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_octs_dwp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t cnt:48;
#ewse
		uint64_t cnt:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_pkts {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_pkts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_pkts_bad {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_pkts_bad_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_pkts_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_pkts_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_pkts_dmac {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_pkts_dmac_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_stats_pkts_dwp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_stats_pkts_dwp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t cnt:32;
#ewse
		uint64_t cnt:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_wxx_udd_skp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wxx_udd_skp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t fcssew:1;
		uint64_t wesewved_7_7:1;
		uint64_t wen:7;
#ewse
		uint64_t wen:7;
		uint64_t wesewved_7_7:1;
		uint64_t fcssew:1;
		uint64_t wesewved_9_63:55;
#endif
	} s;
};

union cvmx_agw_gmx_wx_bp_dwopx {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wx_bp_dwopx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t mawk:6;
#ewse
		uint64_t mawk:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_agw_gmx_wx_bp_offx {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wx_bp_offx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t mawk:6;
#ewse
		uint64_t mawk:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_agw_gmx_wx_bp_onx {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wx_bp_onx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t mawk:9;
#ewse
		uint64_t mawk:9;
		uint64_t wesewved_9_63:55;
#endif
	} s;
};

union cvmx_agw_gmx_wx_pwt_info {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wx_pwt_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t dwop:2;
		uint64_t wesewved_2_15:14;
		uint64_t commit:2;
#ewse
		uint64_t commit:2;
		uint64_t wesewved_2_15:14;
		uint64_t dwop:2;
		uint64_t wesewved_18_63:46;
#endif
	} s;
	stwuct cvmx_agw_gmx_wx_pwt_info_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t dwop:1;
		uint64_t wesewved_1_15:15;
		uint64_t commit:1;
#ewse
		uint64_t commit:1;
		uint64_t wesewved_1_15:15;
		uint64_t dwop:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_wx_tx_status {
	uint64_t u64;
	stwuct cvmx_agw_gmx_wx_tx_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t tx:2;
		uint64_t wesewved_2_3:2;
		uint64_t wx:2;
#ewse
		uint64_t wx:2;
		uint64_t wesewved_2_3:2;
		uint64_t tx:2;
		uint64_t wesewved_6_63:58;
#endif
	} s;
	stwuct cvmx_agw_gmx_wx_tx_status_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t tx:1;
		uint64_t wesewved_1_3:3;
		uint64_t wx:1;
#ewse
		uint64_t wx:1;
		uint64_t wesewved_1_3:3;
		uint64_t tx:1;
		uint64_t wesewved_5_63:59;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_smacx {
	uint64_t u64;
	stwuct cvmx_agw_gmx_smacx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t smac:48;
#ewse
		uint64_t smac:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_stat_bp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_stat_bp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t bp:1;
		uint64_t cnt:16;
#ewse
		uint64_t cnt:16;
		uint64_t bp:1;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_agw_gmx_txx_append {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_append_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t fowce_fcs:1;
		uint64_t fcs:1;
		uint64_t pad:1;
		uint64_t pweambwe:1;
#ewse
		uint64_t pweambwe:1;
		uint64_t pad:1;
		uint64_t fcs:1;
		uint64_t fowce_fcs:1;
		uint64_t wesewved_4_63:60;
#endif
	} s;
};

union cvmx_agw_gmx_txx_cwk {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_cwk_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t cwk_cnt:6;
#ewse
		uint64_t cwk_cnt:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_agw_gmx_txx_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t xsdef_en:1;
		uint64_t xscow_en:1;
#ewse
		uint64_t xscow_en:1;
		uint64_t xsdef_en:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_agw_gmx_txx_min_pkt {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_min_pkt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t min_size:8;
#ewse
		uint64_t min_size:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_agw_gmx_txx_pause_pkt_intewvaw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_pause_pkt_intewvaw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t intewvaw:16;
#ewse
		uint64_t intewvaw:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_txx_pause_pkt_time {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_pause_pkt_time_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t time:16;
#ewse
		uint64_t time:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_txx_pause_togo {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_pause_togo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t time:16;
#ewse
		uint64_t time:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_txx_pause_zewo {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_pause_zewo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t send:1;
#ewse
		uint64_t send:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_agw_gmx_txx_soft_pause {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_soft_pause_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t time:16;
#ewse
		uint64_t time:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat0 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t xsdef:32;
		uint64_t xscow:32;
#ewse
		uint64_t xscow:32;
		uint64_t xsdef:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat1 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t scow:32;
		uint64_t mcow:32;
#ewse
		uint64_t mcow:32;
		uint64_t scow:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat2 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t octs:48;
#ewse
		uint64_t octs:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat3 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pkts:32;
#ewse
		uint64_t pkts:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat4 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat4_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t hist1:32;
		uint64_t hist0:32;
#ewse
		uint64_t hist0:32;
		uint64_t hist1:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat5 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat5_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t hist3:32;
		uint64_t hist2:32;
#ewse
		uint64_t hist2:32;
		uint64_t hist3:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat6 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat6_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t hist5:32;
		uint64_t hist4:32;
#ewse
		uint64_t hist4:32;
		uint64_t hist5:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat7 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat7_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t hist7:32;
		uint64_t hist6:32;
#ewse
		uint64_t hist6:32;
		uint64_t hist7:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat8 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat8_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t mcst:32;
		uint64_t bcst:32;
#ewse
		uint64_t bcst:32;
		uint64_t mcst:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stat9 {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stat9_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t undfww:32;
		uint64_t ctw:32;
#ewse
		uint64_t ctw:32;
		uint64_t undfww:32;
#endif
	} s;
};

union cvmx_agw_gmx_txx_stats_ctw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_stats_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t wd_cww:1;
#ewse
		uint64_t wd_cww:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_agw_gmx_txx_thwesh {
	uint64_t u64;
	stwuct cvmx_agw_gmx_txx_thwesh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t cnt:6;
#ewse
		uint64_t cnt:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_agw_gmx_tx_bp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_bp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t bp:2;
#ewse
		uint64_t bp:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
	stwuct cvmx_agw_gmx_tx_bp_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t bp:1;
#ewse
		uint64_t bp:1;
		uint64_t wesewved_1_63:63;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_tx_cow_attempt {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_cow_attempt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t wimit:5;
#ewse
		uint64_t wimit:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_agw_gmx_tx_ifg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_ifg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t ifg2:4;
		uint64_t ifg1:4;
#ewse
		uint64_t ifg1:4;
		uint64_t ifg2:4;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_agw_gmx_tx_int_en {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t ptp_wost:2;
		uint64_t wesewved_18_19:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_19:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_agw_gmx_tx_int_en_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_63:46;
#endif
	} cn52xx;
	stwuct cvmx_agw_gmx_tx_int_en_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t wate_cow:1;
		uint64_t wesewved_13_15:3;
		uint64_t xsdef:1;
		uint64_t wesewved_9_11:3;
		uint64_t xscow:1;
		uint64_t wesewved_3_7:5;
		uint64_t undfww:1;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:1;
		uint64_t wesewved_3_7:5;
		uint64_t xscow:1;
		uint64_t wesewved_9_11:3;
		uint64_t xsdef:1;
		uint64_t wesewved_13_15:3;
		uint64_t wate_cow:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_tx_int_weg {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t ptp_wost:2;
		uint64_t wesewved_18_19:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_19:2;
		uint64_t ptp_wost:2;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_agw_gmx_tx_int_weg_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t wate_cow:2;
		uint64_t wesewved_14_15:2;
		uint64_t xsdef:2;
		uint64_t wesewved_10_11:2;
		uint64_t xscow:2;
		uint64_t wesewved_4_7:4;
		uint64_t undfww:2;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:2;
		uint64_t wesewved_4_7:4;
		uint64_t xscow:2;
		uint64_t wesewved_10_11:2;
		uint64_t xsdef:2;
		uint64_t wesewved_14_15:2;
		uint64_t wate_cow:2;
		uint64_t wesewved_18_63:46;
#endif
	} cn52xx;
	stwuct cvmx_agw_gmx_tx_int_weg_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t wate_cow:1;
		uint64_t wesewved_13_15:3;
		uint64_t xsdef:1;
		uint64_t wesewved_9_11:3;
		uint64_t xscow:1;
		uint64_t wesewved_3_7:5;
		uint64_t undfww:1;
		uint64_t wesewved_1_1:1;
		uint64_t pko_nxa:1;
#ewse
		uint64_t pko_nxa:1;
		uint64_t wesewved_1_1:1;
		uint64_t undfww:1;
		uint64_t wesewved_3_7:5;
		uint64_t xscow:1;
		uint64_t wesewved_9_11:3;
		uint64_t xsdef:1;
		uint64_t wesewved_13_15:3;
		uint64_t wate_cow:1;
		uint64_t wesewved_17_63:47;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_tx_jam {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_jam_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t jam:8;
#ewse
		uint64_t jam:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_agw_gmx_tx_wfsw {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_wfsw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t wfsw:16;
#ewse
		uint64_t wfsw:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_gmx_tx_ovw_bp {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_ovw_bp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t en:2;
		uint64_t wesewved_6_7:2;
		uint64_t bp:2;
		uint64_t wesewved_2_3:2;
		uint64_t ign_fuww:2;
#ewse
		uint64_t ign_fuww:2;
		uint64_t wesewved_2_3:2;
		uint64_t bp:2;
		uint64_t wesewved_6_7:2;
		uint64_t en:2;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_agw_gmx_tx_ovw_bp_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t en:1;
		uint64_t wesewved_5_7:3;
		uint64_t bp:1;
		uint64_t wesewved_1_3:3;
		uint64_t ign_fuww:1;
#ewse
		uint64_t ign_fuww:1;
		uint64_t wesewved_1_3:3;
		uint64_t bp:1;
		uint64_t wesewved_5_7:3;
		uint64_t en:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn56xx;
};

union cvmx_agw_gmx_tx_pause_pkt_dmac {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_pause_pkt_dmac_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t dmac:48;
#ewse
		uint64_t dmac:48;
		uint64_t wesewved_48_63:16;
#endif
	} s;
};

union cvmx_agw_gmx_tx_pause_pkt_type {
	uint64_t u64;
	stwuct cvmx_agw_gmx_tx_pause_pkt_type_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t type:16;
#ewse
		uint64_t type:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_agw_pwtx_ctw {
	uint64_t u64;
	stwuct cvmx_agw_pwtx_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dwv_byp:1;
		uint64_t wesewved_62_62:1;
		uint64_t cmp_pctw:6;
		uint64_t wesewved_54_55:2;
		uint64_t cmp_nctw:6;
		uint64_t wesewved_46_47:2;
		uint64_t dwv_pctw:6;
		uint64_t wesewved_38_39:2;
		uint64_t dwv_nctw:6;
		uint64_t wesewved_29_31:3;
		uint64_t cwk_set:5;
		uint64_t cwkwx_byp:1;
		uint64_t wesewved_21_22:2;
		uint64_t cwkwx_set:5;
		uint64_t cwktx_byp:1;
		uint64_t wesewved_13_14:2;
		uint64_t cwktx_set:5;
		uint64_t wesewved_5_7:3;
		uint64_t dwwwst:1;
		uint64_t comp:1;
		uint64_t enabwe:1;
		uint64_t cwkwst:1;
		uint64_t mode:1;
#ewse
		uint64_t mode:1;
		uint64_t cwkwst:1;
		uint64_t enabwe:1;
		uint64_t comp:1;
		uint64_t dwwwst:1;
		uint64_t wesewved_5_7:3;
		uint64_t cwktx_set:5;
		uint64_t wesewved_13_14:2;
		uint64_t cwktx_byp:1;
		uint64_t cwkwx_set:5;
		uint64_t wesewved_21_22:2;
		uint64_t cwkwx_byp:1;
		uint64_t cwk_set:5;
		uint64_t wesewved_29_31:3;
		uint64_t dwv_nctw:6;
		uint64_t wesewved_38_39:2;
		uint64_t dwv_pctw:6;
		uint64_t wesewved_46_47:2;
		uint64_t cmp_nctw:6;
		uint64_t wesewved_54_55:2;
		uint64_t cmp_pctw:6;
		uint64_t wesewved_62_62:1;
		uint64_t dwv_byp:1;
#endif
	} s;
};

#endif
