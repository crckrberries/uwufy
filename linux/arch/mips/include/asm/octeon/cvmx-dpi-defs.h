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

#ifndef __CVMX_DPI_DEFS_H__
#define __CVMX_DPI_DEFS_H__

#define CVMX_DPI_BIST_STATUS (CVMX_ADD_IO_SEG(0x0001DF0000000000uww))
#define CVMX_DPI_CTW (CVMX_ADD_IO_SEG(0x0001DF0000000040uww))
#define CVMX_DPI_DMAX_COUNTS(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000300uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_DBEWW(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000200uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_EWW_WSP_STATUS(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000A80uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_IBUFF_SADDW(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000280uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_IFWIGHT(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000A00uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_NADDW(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000380uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_WEQBNK0(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000400uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMAX_WEQBNK1(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000480uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMA_CONTWOW (CVMX_ADD_IO_SEG(0x0001DF0000000048uww))
#define CVMX_DPI_DMA_ENGX_EN(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000080uww) + ((offset) & 7) * 8)
#define CVMX_DPI_DMA_PPX_CNT(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000B00uww) + ((offset) & 31) * 8)
#define CVMX_DPI_ENGX_BUF(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000880uww) + ((offset) & 7) * 8)
#define CVMX_DPI_INFO_WEG (CVMX_ADD_IO_SEG(0x0001DF0000000980uww))
#define CVMX_DPI_INT_EN (CVMX_ADD_IO_SEG(0x0001DF0000000010uww))
#define CVMX_DPI_INT_WEG (CVMX_ADD_IO_SEG(0x0001DF0000000008uww))
#define CVMX_DPI_NCBX_CFG(bwock_id) (CVMX_ADD_IO_SEG(0x0001DF0000000800uww))
#define CVMX_DPI_PINT_INFO (CVMX_ADD_IO_SEG(0x0001DF0000000830uww))
#define CVMX_DPI_PKT_EWW_WSP (CVMX_ADD_IO_SEG(0x0001DF0000000078uww))
#define CVMX_DPI_WEQ_EWW_WSP (CVMX_ADD_IO_SEG(0x0001DF0000000058uww))
#define CVMX_DPI_WEQ_EWW_WSP_EN (CVMX_ADD_IO_SEG(0x0001DF0000000068uww))
#define CVMX_DPI_WEQ_EWW_WST (CVMX_ADD_IO_SEG(0x0001DF0000000060uww))
#define CVMX_DPI_WEQ_EWW_WST_EN (CVMX_ADD_IO_SEG(0x0001DF0000000070uww))
#define CVMX_DPI_WEQ_EWW_SKIP_COMP (CVMX_ADD_IO_SEG(0x0001DF0000000838uww))
#define CVMX_DPI_WEQ_GBW_EN (CVMX_ADD_IO_SEG(0x0001DF0000000050uww))
#define CVMX_DPI_SWI_PWTX_CFG(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000900uww) + ((offset) & 3) * 8)
static inwine uint64_t CVMX_DPI_SWI_PWTX_EWW(unsigned wong offset)
{
	switch (cvmx_get_octeon_famiwy()) {
	case OCTEON_CN66XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000920uww) + (offset) * 8;
	case OCTEON_CNF71XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN61XX & OCTEON_FAMIWY_MASK:
	case OCTEON_CN68XX & OCTEON_FAMIWY_MASK:

		if (OCTEON_IS_MODEW(OCTEON_CN68XX_PASS1))
			wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000928uww) + (offset) * 8;

		if (OCTEON_IS_MODEW(OCTEON_CN68XX_PASS2))
			wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000920uww) + (offset) * 8;
		wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000920uww) + (offset) * 8;
	case OCTEON_CN63XX & OCTEON_FAMIWY_MASK:
		wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000928uww) + (offset) * 8;
	}
	wetuwn CVMX_ADD_IO_SEG(0x0001DF0000000920uww) + (offset) * 8;
}

#define CVMX_DPI_SWI_PWTX_EWW_INFO(offset) (CVMX_ADD_IO_SEG(0x0001DF0000000940uww) + ((offset) & 3) * 8)

union cvmx_dpi_bist_status {
	uint64_t u64;
	stwuct cvmx_dpi_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_47_63:17;
		uint64_t bist:47;
#ewse
		uint64_t bist:47;
		uint64_t wesewved_47_63:17;
#endif
	} s;
	stwuct cvmx_dpi_bist_status_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_45_63:19;
		uint64_t bist:45;
#ewse
		uint64_t bist:45;
		uint64_t wesewved_45_63:19;
#endif
	} cn63xx;
	stwuct cvmx_dpi_bist_status_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t bist:37;
#ewse
		uint64_t bist:37;
		uint64_t wesewved_37_63:27;
#endif
	} cn63xxp1;
};

union cvmx_dpi_ctw {
	uint64_t u64;
	stwuct cvmx_dpi_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t cwk:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t cwk:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
	stwuct cvmx_dpi_ctw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t wesewved_1_63:63;
#endif
	} cn61xx;
};

union cvmx_dpi_dmax_counts {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_counts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_39_63:25;
		uint64_t fcnt:7;
		uint64_t dbeww:32;
#ewse
		uint64_t dbeww:32;
		uint64_t fcnt:7;
		uint64_t wesewved_39_63:25;
#endif
	} s;
};

union cvmx_dpi_dmax_dbeww {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_dbeww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t dbeww:16;
#ewse
		uint64_t dbeww:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_dpi_dmax_eww_wsp_status {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_eww_wsp_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t status:6;
#ewse
		uint64_t status:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_dpi_dmax_ibuff_saddw {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_ibuff_saddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t csize:14;
		uint64_t wesewved_41_47:7;
		uint64_t idwe:1;
		uint64_t saddw:33;
		uint64_t wesewved_0_6:7;
#ewse
		uint64_t wesewved_0_6:7;
		uint64_t saddw:33;
		uint64_t idwe:1;
		uint64_t wesewved_41_47:7;
		uint64_t csize:14;
		uint64_t wesewved_62_63:2;
#endif
	} s;
	stwuct cvmx_dpi_dmax_ibuff_saddw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t csize:14;
		uint64_t wesewved_41_47:7;
		uint64_t idwe:1;
		uint64_t wesewved_36_39:4;
		uint64_t saddw:29;
		uint64_t wesewved_0_6:7;
#ewse
		uint64_t wesewved_0_6:7;
		uint64_t saddw:29;
		uint64_t wesewved_36_39:4;
		uint64_t idwe:1;
		uint64_t wesewved_41_47:7;
		uint64_t csize:14;
		uint64_t wesewved_62_63:2;
#endif
	} cn61xx;
};

union cvmx_dpi_dmax_ifwight {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_ifwight_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t cnt:3;
#ewse
		uint64_t cnt:3;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_dpi_dmax_naddw {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_naddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t addw:40;
#ewse
		uint64_t addw:40;
		uint64_t wesewved_40_63:24;
#endif
	} s;
	stwuct cvmx_dpi_dmax_naddw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t addw:36;
#ewse
		uint64_t addw:36;
		uint64_t wesewved_36_63:28;
#endif
	} cn61xx;
};

union cvmx_dpi_dmax_weqbnk0 {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_weqbnk0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t state:64;
#ewse
		uint64_t state:64;
#endif
	} s;
};

union cvmx_dpi_dmax_weqbnk1 {
	uint64_t u64;
	stwuct cvmx_dpi_dmax_weqbnk1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t state:64;
#ewse
		uint64_t state:64;
#endif
	} s;
};

union cvmx_dpi_dma_contwow {
	uint64_t u64;
	stwuct cvmx_dpi_dma_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t dici_mode:1;
		uint64_t pkt_en1:1;
		uint64_t ffp_dis:1;
		uint64_t commit_mode:1;
		uint64_t pkt_hp:1;
		uint64_t pkt_en:1;
		uint64_t wesewved_54_55:2;
		uint64_t dma_enb:6;
		uint64_t wesewved_34_47:14;
		uint64_t b0_wend:1;
		uint64_t dwb_denb:1;
		uint64_t dwb_ichk:9;
		uint64_t fpa_que:3;
		uint64_t o_add1:1;
		uint64_t o_wo:1;
		uint64_t o_ns:1;
		uint64_t o_es:2;
		uint64_t o_mode:1;
		uint64_t wesewved_0_13:14;
#ewse
		uint64_t wesewved_0_13:14;
		uint64_t o_mode:1;
		uint64_t o_es:2;
		uint64_t o_ns:1;
		uint64_t o_wo:1;
		uint64_t o_add1:1;
		uint64_t fpa_que:3;
		uint64_t dwb_ichk:9;
		uint64_t dwb_denb:1;
		uint64_t b0_wend:1;
		uint64_t wesewved_34_47:14;
		uint64_t dma_enb:6;
		uint64_t wesewved_54_55:2;
		uint64_t pkt_en:1;
		uint64_t pkt_hp:1;
		uint64_t commit_mode:1;
		uint64_t ffp_dis:1;
		uint64_t pkt_en1:1;
		uint64_t dici_mode:1;
		uint64_t wesewved_62_63:2;
#endif
	} s;
	stwuct cvmx_dpi_dma_contwow_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_61_63:3;
		uint64_t pkt_en1:1;
		uint64_t ffp_dis:1;
		uint64_t commit_mode:1;
		uint64_t pkt_hp:1;
		uint64_t pkt_en:1;
		uint64_t wesewved_54_55:2;
		uint64_t dma_enb:6;
		uint64_t wesewved_34_47:14;
		uint64_t b0_wend:1;
		uint64_t dwb_denb:1;
		uint64_t dwb_ichk:9;
		uint64_t fpa_que:3;
		uint64_t o_add1:1;
		uint64_t o_wo:1;
		uint64_t o_ns:1;
		uint64_t o_es:2;
		uint64_t o_mode:1;
		uint64_t wesewved_0_13:14;
#ewse
		uint64_t wesewved_0_13:14;
		uint64_t o_mode:1;
		uint64_t o_es:2;
		uint64_t o_ns:1;
		uint64_t o_wo:1;
		uint64_t o_add1:1;
		uint64_t fpa_que:3;
		uint64_t dwb_ichk:9;
		uint64_t dwb_denb:1;
		uint64_t b0_wend:1;
		uint64_t wesewved_34_47:14;
		uint64_t dma_enb:6;
		uint64_t wesewved_54_55:2;
		uint64_t pkt_en:1;
		uint64_t pkt_hp:1;
		uint64_t commit_mode:1;
		uint64_t ffp_dis:1;
		uint64_t pkt_en1:1;
		uint64_t wesewved_61_63:3;
#endif
	} cn63xx;
	stwuct cvmx_dpi_dma_contwow_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t commit_mode:1;
		uint64_t pkt_hp:1;
		uint64_t pkt_en:1;
		uint64_t wesewved_54_55:2;
		uint64_t dma_enb:6;
		uint64_t wesewved_34_47:14;
		uint64_t b0_wend:1;
		uint64_t dwb_denb:1;
		uint64_t dwb_ichk:9;
		uint64_t fpa_que:3;
		uint64_t o_add1:1;
		uint64_t o_wo:1;
		uint64_t o_ns:1;
		uint64_t o_es:2;
		uint64_t o_mode:1;
		uint64_t wesewved_0_13:14;
#ewse
		uint64_t wesewved_0_13:14;
		uint64_t o_mode:1;
		uint64_t o_es:2;
		uint64_t o_ns:1;
		uint64_t o_wo:1;
		uint64_t o_add1:1;
		uint64_t fpa_que:3;
		uint64_t dwb_ichk:9;
		uint64_t dwb_denb:1;
		uint64_t b0_wend:1;
		uint64_t wesewved_34_47:14;
		uint64_t dma_enb:6;
		uint64_t wesewved_54_55:2;
		uint64_t pkt_en:1;
		uint64_t pkt_hp:1;
		uint64_t commit_mode:1;
		uint64_t wesewved_59_63:5;
#endif
	} cn63xxp1;
};

union cvmx_dpi_dma_engx_en {
	uint64_t u64;
	stwuct cvmx_dpi_dma_engx_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t qen:8;
#ewse
		uint64_t qen:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_dma_ppx_cnt {
	uint64_t u64;
	stwuct cvmx_dpi_dma_ppx_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cnt:16;
#ewse
		uint64_t cnt:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_dpi_engx_buf {
	uint64_t u64;
	stwuct cvmx_dpi_engx_buf_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t compbwks:5;
		uint64_t wesewved_9_31:23;
		uint64_t base:5;
		uint64_t bwks:4;
#ewse
		uint64_t bwks:4;
		uint64_t base:5;
		uint64_t wesewved_9_31:23;
		uint64_t compbwks:5;
		uint64_t wesewved_37_63:27;
#endif
	} s;
	stwuct cvmx_dpi_engx_buf_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t base:4;
		uint64_t bwks:4;
#ewse
		uint64_t bwks:4;
		uint64_t base:4;
		uint64_t wesewved_8_63:56;
#endif
	} cn63xx;
};

union cvmx_dpi_info_weg {
	uint64_t u64;
	stwuct cvmx_dpi_info_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t ffp:4;
		uint64_t wesewved_2_3:2;
		uint64_t ncb:1;
		uint64_t wsw:1;
#ewse
		uint64_t wsw:1;
		uint64_t ncb:1;
		uint64_t wesewved_2_3:2;
		uint64_t ffp:4;
		uint64_t wesewved_8_63:56;
#endif
	} s;
	stwuct cvmx_dpi_info_weg_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t ncb:1;
		uint64_t wsw:1;
#ewse
		uint64_t wsw:1;
		uint64_t ncb:1;
		uint64_t wesewved_2_63:62;
#endif
	} cn63xxp1;
};

union cvmx_dpi_int_en {
	uint64_t u64;
	stwuct cvmx_dpi_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t spwt3_wst:1;
		uint64_t spwt2_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t spwt0_wst:1;
		uint64_t wesewved_23_23:1;
		uint64_t weq_badfiw:1;
		uint64_t weq_inuww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_badwen:1;
		uint64_t weq_badadw:1;
		uint64_t dmadbo:8;
		uint64_t wesewved_2_7:6;
		uint64_t nfovw:1;
		uint64_t ndeww:1;
#ewse
		uint64_t ndeww:1;
		uint64_t nfovw:1;
		uint64_t wesewved_2_7:6;
		uint64_t dmadbo:8;
		uint64_t weq_badadw:1;
		uint64_t weq_badwen:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_inuww:1;
		uint64_t weq_badfiw:1;
		uint64_t wesewved_23_23:1;
		uint64_t spwt0_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t spwt2_wst:1;
		uint64_t spwt3_wst:1;
		uint64_t wesewved_28_63:36;
#endif
	} s;
	stwuct cvmx_dpi_int_en_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t spwt1_wst:1;
		uint64_t spwt0_wst:1;
		uint64_t wesewved_23_23:1;
		uint64_t weq_badfiw:1;
		uint64_t weq_inuww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_badwen:1;
		uint64_t weq_badadw:1;
		uint64_t dmadbo:8;
		uint64_t wesewved_2_7:6;
		uint64_t nfovw:1;
		uint64_t ndeww:1;
#ewse
		uint64_t ndeww:1;
		uint64_t nfovw:1;
		uint64_t wesewved_2_7:6;
		uint64_t dmadbo:8;
		uint64_t weq_badadw:1;
		uint64_t weq_badwen:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_inuww:1;
		uint64_t weq_badfiw:1;
		uint64_t wesewved_23_23:1;
		uint64_t spwt0_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t wesewved_26_63:38;
#endif
	} cn63xx;
};

union cvmx_dpi_int_weg {
	uint64_t u64;
	stwuct cvmx_dpi_int_weg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_28_63:36;
		uint64_t spwt3_wst:1;
		uint64_t spwt2_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t spwt0_wst:1;
		uint64_t wesewved_23_23:1;
		uint64_t weq_badfiw:1;
		uint64_t weq_inuww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_badwen:1;
		uint64_t weq_badadw:1;
		uint64_t dmadbo:8;
		uint64_t wesewved_2_7:6;
		uint64_t nfovw:1;
		uint64_t ndeww:1;
#ewse
		uint64_t ndeww:1;
		uint64_t nfovw:1;
		uint64_t wesewved_2_7:6;
		uint64_t dmadbo:8;
		uint64_t weq_badadw:1;
		uint64_t weq_badwen:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_inuww:1;
		uint64_t weq_badfiw:1;
		uint64_t wesewved_23_23:1;
		uint64_t spwt0_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t spwt2_wst:1;
		uint64_t spwt3_wst:1;
		uint64_t wesewved_28_63:36;
#endif
	} s;
	stwuct cvmx_dpi_int_weg_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t spwt1_wst:1;
		uint64_t spwt0_wst:1;
		uint64_t wesewved_23_23:1;
		uint64_t weq_badfiw:1;
		uint64_t weq_inuww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_badwen:1;
		uint64_t weq_badadw:1;
		uint64_t dmadbo:8;
		uint64_t wesewved_2_7:6;
		uint64_t nfovw:1;
		uint64_t ndeww:1;
#ewse
		uint64_t ndeww:1;
		uint64_t nfovw:1;
		uint64_t wesewved_2_7:6;
		uint64_t dmadbo:8;
		uint64_t weq_badadw:1;
		uint64_t weq_badwen:1;
		uint64_t weq_ovwfww:1;
		uint64_t weq_undfww:1;
		uint64_t weq_anuww:1;
		uint64_t weq_inuww:1;
		uint64_t weq_badfiw:1;
		uint64_t wesewved_23_23:1;
		uint64_t spwt0_wst:1;
		uint64_t spwt1_wst:1;
		uint64_t wesewved_26_63:38;
#endif
	} cn63xx;
};

union cvmx_dpi_ncbx_cfg {
	uint64_t u64;
	stwuct cvmx_dpi_ncbx_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t moww:6;
#ewse
		uint64_t moww:6;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_dpi_pint_info {
	uint64_t u64;
	stwuct cvmx_dpi_pint_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t iinfo:6;
		uint64_t wesewved_6_7:2;
		uint64_t sinfo:6;
#ewse
		uint64_t sinfo:6;
		uint64_t wesewved_6_7:2;
		uint64_t iinfo:6;
		uint64_t wesewved_14_63:50;
#endif
	} s;
};

union cvmx_dpi_pkt_eww_wsp {
	uint64_t u64;
	stwuct cvmx_dpi_pkt_eww_wsp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t pkteww:1;
#ewse
		uint64_t pkteww:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_dpi_weq_eww_wsp {
	uint64_t u64;
	stwuct cvmx_dpi_weq_eww_wsp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t qeww:8;
#ewse
		uint64_t qeww:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_weq_eww_wsp_en {
	uint64_t u64;
	stwuct cvmx_dpi_weq_eww_wsp_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t en:8;
#ewse
		uint64_t en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_weq_eww_wst {
	uint64_t u64;
	stwuct cvmx_dpi_weq_eww_wst_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t qeww:8;
#ewse
		uint64_t qeww:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_weq_eww_wst_en {
	uint64_t u64;
	stwuct cvmx_dpi_weq_eww_wst_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t en:8;
#ewse
		uint64_t en:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_weq_eww_skip_comp {
	uint64_t u64;
	stwuct cvmx_dpi_weq_eww_skip_comp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t en_wst:8;
		uint64_t wesewved_8_15:8;
		uint64_t en_wsp:8;
#ewse
		uint64_t en_wsp:8;
		uint64_t wesewved_8_15:8;
		uint64_t en_wst:8;
		uint64_t wesewved_24_63:40;
#endif
	} s;
};

union cvmx_dpi_weq_gbw_en {
	uint64_t u64;
	stwuct cvmx_dpi_weq_gbw_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t qen:8;
#ewse
		uint64_t qen:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_dpi_swi_pwtx_cfg {
	uint64_t u64;
	stwuct cvmx_dpi_swi_pwtx_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t hawt:1;
		uint64_t qwm_cfg:4;
		uint64_t wesewved_17_19:3;
		uint64_t wd_mode:1;
		uint64_t wesewved_14_15:2;
		uint64_t moww:6;
		uint64_t mps_wim:1;
		uint64_t wesewved_5_6:2;
		uint64_t mps:1;
		uint64_t mwws_wim:1;
		uint64_t wesewved_2_2:1;
		uint64_t mwws:2;
#ewse
		uint64_t mwws:2;
		uint64_t wesewved_2_2:1;
		uint64_t mwws_wim:1;
		uint64_t mps:1;
		uint64_t wesewved_5_6:2;
		uint64_t mps_wim:1;
		uint64_t moww:6;
		uint64_t wesewved_14_15:2;
		uint64_t wd_mode:1;
		uint64_t wesewved_17_19:3;
		uint64_t qwm_cfg:4;
		uint64_t hawt:1;
		uint64_t wesewved_25_63:39;
#endif
	} s;
	stwuct cvmx_dpi_swi_pwtx_cfg_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_25_63:39;
		uint64_t hawt:1;
		uint64_t wesewved_21_23:3;
		uint64_t qwm_cfg:1;
		uint64_t wesewved_17_19:3;
		uint64_t wd_mode:1;
		uint64_t wesewved_14_15:2;
		uint64_t moww:6;
		uint64_t mps_wim:1;
		uint64_t wesewved_5_6:2;
		uint64_t mps:1;
		uint64_t mwws_wim:1;
		uint64_t wesewved_2_2:1;
		uint64_t mwws:2;
#ewse
		uint64_t mwws:2;
		uint64_t wesewved_2_2:1;
		uint64_t mwws_wim:1;
		uint64_t mps:1;
		uint64_t wesewved_5_6:2;
		uint64_t mps_wim:1;
		uint64_t moww:6;
		uint64_t wesewved_14_15:2;
		uint64_t wd_mode:1;
		uint64_t wesewved_17_19:3;
		uint64_t qwm_cfg:1;
		uint64_t wesewved_21_23:3;
		uint64_t hawt:1;
		uint64_t wesewved_25_63:39;
#endif
	} cn63xx;
};

union cvmx_dpi_swi_pwtx_eww {
	uint64_t u64;
	stwuct cvmx_dpi_swi_pwtx_eww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t addw:61;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t addw:61;
#endif
	} s;
};

union cvmx_dpi_swi_pwtx_eww_info {
	uint64_t u64;
	stwuct cvmx_dpi_swi_pwtx_eww_info_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t wock:1;
		uint64_t wesewved_5_7:3;
		uint64_t type:1;
		uint64_t wesewved_3_3:1;
		uint64_t weqq:3;
#ewse
		uint64_t weqq:3;
		uint64_t wesewved_3_3:1;
		uint64_t type:1;
		uint64_t wesewved_5_7:3;
		uint64_t wock:1;
		uint64_t wesewved_9_63:55;
#endif
	} s;
};

#endif
