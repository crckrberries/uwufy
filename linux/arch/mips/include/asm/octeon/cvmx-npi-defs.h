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

#ifndef __CVMX_NPI_DEFS_H__
#define __CVMX_NPI_DEFS_H__

#define CVMX_NPI_BASE_ADDW_INPUT0 CVMX_NPI_BASE_ADDW_INPUTX(0)
#define CVMX_NPI_BASE_ADDW_INPUT1 CVMX_NPI_BASE_ADDW_INPUTX(1)
#define CVMX_NPI_BASE_ADDW_INPUT2 CVMX_NPI_BASE_ADDW_INPUTX(2)
#define CVMX_NPI_BASE_ADDW_INPUT3 CVMX_NPI_BASE_ADDW_INPUTX(3)
#define CVMX_NPI_BASE_ADDW_INPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000070uww) + ((offset) & 3) * 16)
#define CVMX_NPI_BASE_ADDW_OUTPUT0 CVMX_NPI_BASE_ADDW_OUTPUTX(0)
#define CVMX_NPI_BASE_ADDW_OUTPUT1 CVMX_NPI_BASE_ADDW_OUTPUTX(1)
#define CVMX_NPI_BASE_ADDW_OUTPUT2 CVMX_NPI_BASE_ADDW_OUTPUTX(2)
#define CVMX_NPI_BASE_ADDW_OUTPUT3 CVMX_NPI_BASE_ADDW_OUTPUTX(3)
#define CVMX_NPI_BASE_ADDW_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F00000000B8uww) + ((offset) & 3) * 8)
#define CVMX_NPI_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011F00000003F8uww))
#define CVMX_NPI_BUFF_SIZE_OUTPUT0 CVMX_NPI_BUFF_SIZE_OUTPUTX(0)
#define CVMX_NPI_BUFF_SIZE_OUTPUT1 CVMX_NPI_BUFF_SIZE_OUTPUTX(1)
#define CVMX_NPI_BUFF_SIZE_OUTPUT2 CVMX_NPI_BUFF_SIZE_OUTPUTX(2)
#define CVMX_NPI_BUFF_SIZE_OUTPUT3 CVMX_NPI_BUFF_SIZE_OUTPUTX(3)
#define CVMX_NPI_BUFF_SIZE_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F00000000E0uww) + ((offset) & 3) * 8)
#define CVMX_NPI_COMP_CTW (CVMX_ADD_IO_SEG(0x00011F0000000218uww))
#define CVMX_NPI_CTW_STATUS (CVMX_ADD_IO_SEG(0x00011F0000000010uww))
#define CVMX_NPI_DBG_SEWECT (CVMX_ADD_IO_SEG(0x00011F0000000008uww))
#define CVMX_NPI_DMA_CONTWOW (CVMX_ADD_IO_SEG(0x00011F0000000128uww))
#define CVMX_NPI_DMA_HIGHP_COUNTS (CVMX_ADD_IO_SEG(0x00011F0000000148uww))
#define CVMX_NPI_DMA_HIGHP_NADDW (CVMX_ADD_IO_SEG(0x00011F0000000158uww))
#define CVMX_NPI_DMA_WOWP_COUNTS (CVMX_ADD_IO_SEG(0x00011F0000000140uww))
#define CVMX_NPI_DMA_WOWP_NADDW (CVMX_ADD_IO_SEG(0x00011F0000000150uww))
#define CVMX_NPI_HIGHP_DBEWW (CVMX_ADD_IO_SEG(0x00011F0000000120uww))
#define CVMX_NPI_HIGHP_IBUFF_SADDW (CVMX_ADD_IO_SEG(0x00011F0000000110uww))
#define CVMX_NPI_INPUT_CONTWOW (CVMX_ADD_IO_SEG(0x00011F0000000138uww))
#define CVMX_NPI_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000000020uww))
#define CVMX_NPI_INT_SUM (CVMX_ADD_IO_SEG(0x00011F0000000018uww))
#define CVMX_NPI_WOWP_DBEWW (CVMX_ADD_IO_SEG(0x00011F0000000118uww))
#define CVMX_NPI_WOWP_IBUFF_SADDW (CVMX_ADD_IO_SEG(0x00011F0000000108uww))
#define CVMX_NPI_MEM_ACCESS_SUBID3 CVMX_NPI_MEM_ACCESS_SUBIDX(3)
#define CVMX_NPI_MEM_ACCESS_SUBID4 CVMX_NPI_MEM_ACCESS_SUBIDX(4)
#define CVMX_NPI_MEM_ACCESS_SUBID5 CVMX_NPI_MEM_ACCESS_SUBIDX(5)
#define CVMX_NPI_MEM_ACCESS_SUBID6 CVMX_NPI_MEM_ACCESS_SUBIDX(6)
#define CVMX_NPI_MEM_ACCESS_SUBIDX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000028uww) + ((offset) & 7) * 8 - 8*3)
#define CVMX_NPI_MSI_WCV (0x0000000000000190uww)
#define CVMX_NPI_NPI_MSI_WCV (CVMX_ADD_IO_SEG(0x00011F0000001190uww))
#define CVMX_NPI_NUM_DESC_OUTPUT0 CVMX_NPI_NUM_DESC_OUTPUTX(0)
#define CVMX_NPI_NUM_DESC_OUTPUT1 CVMX_NPI_NUM_DESC_OUTPUTX(1)
#define CVMX_NPI_NUM_DESC_OUTPUT2 CVMX_NPI_NUM_DESC_OUTPUTX(2)
#define CVMX_NPI_NUM_DESC_OUTPUT3 CVMX_NPI_NUM_DESC_OUTPUTX(3)
#define CVMX_NPI_NUM_DESC_OUTPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000050uww) + ((offset) & 3) * 8)
#define CVMX_NPI_OUTPUT_CONTWOW (CVMX_ADD_IO_SEG(0x00011F0000000100uww))
#define CVMX_NPI_P0_DBPAIW_ADDW CVMX_NPI_PX_DBPAIW_ADDW(0)
#define CVMX_NPI_P0_INSTW_ADDW CVMX_NPI_PX_INSTW_ADDW(0)
#define CVMX_NPI_P0_INSTW_CNTS CVMX_NPI_PX_INSTW_CNTS(0)
#define CVMX_NPI_P0_PAIW_CNTS CVMX_NPI_PX_PAIW_CNTS(0)
#define CVMX_NPI_P1_DBPAIW_ADDW CVMX_NPI_PX_DBPAIW_ADDW(1)
#define CVMX_NPI_P1_INSTW_ADDW CVMX_NPI_PX_INSTW_ADDW(1)
#define CVMX_NPI_P1_INSTW_CNTS CVMX_NPI_PX_INSTW_CNTS(1)
#define CVMX_NPI_P1_PAIW_CNTS CVMX_NPI_PX_PAIW_CNTS(1)
#define CVMX_NPI_P2_DBPAIW_ADDW CVMX_NPI_PX_DBPAIW_ADDW(2)
#define CVMX_NPI_P2_INSTW_ADDW CVMX_NPI_PX_INSTW_ADDW(2)
#define CVMX_NPI_P2_INSTW_CNTS CVMX_NPI_PX_INSTW_CNTS(2)
#define CVMX_NPI_P2_PAIW_CNTS CVMX_NPI_PX_PAIW_CNTS(2)
#define CVMX_NPI_P3_DBPAIW_ADDW CVMX_NPI_PX_DBPAIW_ADDW(3)
#define CVMX_NPI_P3_INSTW_ADDW CVMX_NPI_PX_INSTW_ADDW(3)
#define CVMX_NPI_P3_INSTW_CNTS CVMX_NPI_PX_INSTW_CNTS(3)
#define CVMX_NPI_P3_PAIW_CNTS CVMX_NPI_PX_PAIW_CNTS(3)
#define CVMX_NPI_PCI_BAW1_INDEXX(offset) (CVMX_ADD_IO_SEG(0x00011F0000001100uww) + ((offset) & 31) * 4)
#define CVMX_NPI_PCI_BIST_WEG (CVMX_ADD_IO_SEG(0x00011F00000011C0uww))
#define CVMX_NPI_PCI_BUWST_SIZE (CVMX_ADD_IO_SEG(0x00011F00000000D8uww))
#define CVMX_NPI_PCI_CFG00 (CVMX_ADD_IO_SEG(0x00011F0000001800uww))
#define CVMX_NPI_PCI_CFG01 (CVMX_ADD_IO_SEG(0x00011F0000001804uww))
#define CVMX_NPI_PCI_CFG02 (CVMX_ADD_IO_SEG(0x00011F0000001808uww))
#define CVMX_NPI_PCI_CFG03 (CVMX_ADD_IO_SEG(0x00011F000000180Cuww))
#define CVMX_NPI_PCI_CFG04 (CVMX_ADD_IO_SEG(0x00011F0000001810uww))
#define CVMX_NPI_PCI_CFG05 (CVMX_ADD_IO_SEG(0x00011F0000001814uww))
#define CVMX_NPI_PCI_CFG06 (CVMX_ADD_IO_SEG(0x00011F0000001818uww))
#define CVMX_NPI_PCI_CFG07 (CVMX_ADD_IO_SEG(0x00011F000000181Cuww))
#define CVMX_NPI_PCI_CFG08 (CVMX_ADD_IO_SEG(0x00011F0000001820uww))
#define CVMX_NPI_PCI_CFG09 (CVMX_ADD_IO_SEG(0x00011F0000001824uww))
#define CVMX_NPI_PCI_CFG10 (CVMX_ADD_IO_SEG(0x00011F0000001828uww))
#define CVMX_NPI_PCI_CFG11 (CVMX_ADD_IO_SEG(0x00011F000000182Cuww))
#define CVMX_NPI_PCI_CFG12 (CVMX_ADD_IO_SEG(0x00011F0000001830uww))
#define CVMX_NPI_PCI_CFG13 (CVMX_ADD_IO_SEG(0x00011F0000001834uww))
#define CVMX_NPI_PCI_CFG15 (CVMX_ADD_IO_SEG(0x00011F000000183Cuww))
#define CVMX_NPI_PCI_CFG16 (CVMX_ADD_IO_SEG(0x00011F0000001840uww))
#define CVMX_NPI_PCI_CFG17 (CVMX_ADD_IO_SEG(0x00011F0000001844uww))
#define CVMX_NPI_PCI_CFG18 (CVMX_ADD_IO_SEG(0x00011F0000001848uww))
#define CVMX_NPI_PCI_CFG19 (CVMX_ADD_IO_SEG(0x00011F000000184Cuww))
#define CVMX_NPI_PCI_CFG20 (CVMX_ADD_IO_SEG(0x00011F0000001850uww))
#define CVMX_NPI_PCI_CFG21 (CVMX_ADD_IO_SEG(0x00011F0000001854uww))
#define CVMX_NPI_PCI_CFG22 (CVMX_ADD_IO_SEG(0x00011F0000001858uww))
#define CVMX_NPI_PCI_CFG56 (CVMX_ADD_IO_SEG(0x00011F00000018E0uww))
#define CVMX_NPI_PCI_CFG57 (CVMX_ADD_IO_SEG(0x00011F00000018E4uww))
#define CVMX_NPI_PCI_CFG58 (CVMX_ADD_IO_SEG(0x00011F00000018E8uww))
#define CVMX_NPI_PCI_CFG59 (CVMX_ADD_IO_SEG(0x00011F00000018ECuww))
#define CVMX_NPI_PCI_CFG60 (CVMX_ADD_IO_SEG(0x00011F00000018F0uww))
#define CVMX_NPI_PCI_CFG61 (CVMX_ADD_IO_SEG(0x00011F00000018F4uww))
#define CVMX_NPI_PCI_CFG62 (CVMX_ADD_IO_SEG(0x00011F00000018F8uww))
#define CVMX_NPI_PCI_CFG63 (CVMX_ADD_IO_SEG(0x00011F00000018FCuww))
#define CVMX_NPI_PCI_CNT_WEG (CVMX_ADD_IO_SEG(0x00011F00000011B8uww))
#define CVMX_NPI_PCI_CTW_STATUS_2 (CVMX_ADD_IO_SEG(0x00011F000000118Cuww))
#define CVMX_NPI_PCI_INT_AWB_CFG (CVMX_ADD_IO_SEG(0x00011F0000000130uww))
#define CVMX_NPI_PCI_INT_ENB2 (CVMX_ADD_IO_SEG(0x00011F00000011A0uww))
#define CVMX_NPI_PCI_INT_SUM2 (CVMX_ADD_IO_SEG(0x00011F0000001198uww))
#define CVMX_NPI_PCI_WEAD_CMD (CVMX_ADD_IO_SEG(0x00011F0000000048uww))
#define CVMX_NPI_PCI_WEAD_CMD_6 (CVMX_ADD_IO_SEG(0x00011F0000001180uww))
#define CVMX_NPI_PCI_WEAD_CMD_C (CVMX_ADD_IO_SEG(0x00011F0000001184uww))
#define CVMX_NPI_PCI_WEAD_CMD_E (CVMX_ADD_IO_SEG(0x00011F0000001188uww))
#define CVMX_NPI_PCI_SCM_WEG (CVMX_ADD_IO_SEG(0x00011F00000011A8uww))
#define CVMX_NPI_PCI_TSW_WEG (CVMX_ADD_IO_SEG(0x00011F00000011B0uww))
#define CVMX_NPI_POWT32_INSTW_HDW (CVMX_ADD_IO_SEG(0x00011F00000001F8uww))
#define CVMX_NPI_POWT33_INSTW_HDW (CVMX_ADD_IO_SEG(0x00011F0000000200uww))
#define CVMX_NPI_POWT34_INSTW_HDW (CVMX_ADD_IO_SEG(0x00011F0000000208uww))
#define CVMX_NPI_POWT35_INSTW_HDW (CVMX_ADD_IO_SEG(0x00011F0000000210uww))
#define CVMX_NPI_POWT_BP_CONTWOW (CVMX_ADD_IO_SEG(0x00011F00000001F0uww))
#define CVMX_NPI_PX_DBPAIW_ADDW(offset) (CVMX_ADD_IO_SEG(0x00011F0000000180uww) + ((offset) & 3) * 8)
#define CVMX_NPI_PX_INSTW_ADDW(offset) (CVMX_ADD_IO_SEG(0x00011F00000001C0uww) + ((offset) & 3) * 8)
#define CVMX_NPI_PX_INSTW_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F00000001A0uww) + ((offset) & 3) * 8)
#define CVMX_NPI_PX_PAIW_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F0000000160uww) + ((offset) & 3) * 8)
#define CVMX_NPI_WSW_INT_BWOCKS (CVMX_ADD_IO_SEG(0x00011F0000000000uww))
#define CVMX_NPI_SIZE_INPUT0 CVMX_NPI_SIZE_INPUTX(0)
#define CVMX_NPI_SIZE_INPUT1 CVMX_NPI_SIZE_INPUTX(1)
#define CVMX_NPI_SIZE_INPUT2 CVMX_NPI_SIZE_INPUTX(2)
#define CVMX_NPI_SIZE_INPUT3 CVMX_NPI_SIZE_INPUTX(3)
#define CVMX_NPI_SIZE_INPUTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000000078uww) + ((offset) & 3) * 16)
#define CVMX_NPI_WIN_WEAD_TO (CVMX_ADD_IO_SEG(0x00011F00000001E0uww))

union cvmx_npi_base_addw_inputx {
	uint64_t u64;
	stwuct cvmx_npi_base_addw_inputx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t baddw:61;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t baddw:61;
#endif
	} s;
};

union cvmx_npi_base_addw_outputx {
	uint64_t u64;
	stwuct cvmx_npi_base_addw_outputx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t baddw:61;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t baddw:61;
#endif
	} s;
};

union cvmx_npi_bist_status {
	uint64_t u64;
	stwuct cvmx_npi_bist_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t csw_bs:1;
		uint64_t dif_bs:1;
		uint64_t wdp_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t pcn_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcac_bs:1;
		uint64_t pcad_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pgf_bs:1;
		uint64_t pig_bs:1;
		uint64_t pof0_bs:1;
		uint64_t pof1_bs:1;
		uint64_t pof2_bs:1;
		uint64_t pof3_bs:1;
		uint64_t pos_bs:1;
		uint64_t nus_bs:1;
		uint64_t dob_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dpi_bs:1;
#ewse
		uint64_t dpi_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dob_bs:1;
		uint64_t nus_bs:1;
		uint64_t pos_bs:1;
		uint64_t pof3_bs:1;
		uint64_t pof2_bs:1;
		uint64_t pof1_bs:1;
		uint64_t pof0_bs:1;
		uint64_t pig_bs:1;
		uint64_t pgf_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pcad_bs:1;
		uint64_t pcac_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcn_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t wdp_bs:1;
		uint64_t dif_bs:1;
		uint64_t csw_bs:1;
		uint64_t wesewved_20_63:44;
#endif
	} s;
	stwuct cvmx_npi_bist_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t csw_bs:1;
		uint64_t dif_bs:1;
		uint64_t wdp_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t pcn_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcac_bs:1;
		uint64_t pcad_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pgf_bs:1;
		uint64_t pig_bs:1;
		uint64_t pof0_bs:1;
		uint64_t wesewved_5_7:3;
		uint64_t pos_bs:1;
		uint64_t nus_bs:1;
		uint64_t dob_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dpi_bs:1;
#ewse
		uint64_t dpi_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dob_bs:1;
		uint64_t nus_bs:1;
		uint64_t pos_bs:1;
		uint64_t wesewved_5_7:3;
		uint64_t pof0_bs:1;
		uint64_t pig_bs:1;
		uint64_t pgf_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pcad_bs:1;
		uint64_t pcac_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcn_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t wdp_bs:1;
		uint64_t dif_bs:1;
		uint64_t csw_bs:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn30xx;
	stwuct cvmx_npi_bist_status_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_20_63:44;
		uint64_t csw_bs:1;
		uint64_t dif_bs:1;
		uint64_t wdp_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t pcn_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcac_bs:1;
		uint64_t pcad_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pgf_bs:1;
		uint64_t pig_bs:1;
		uint64_t pof0_bs:1;
		uint64_t pof1_bs:1;
		uint64_t wesewved_5_6:2;
		uint64_t pos_bs:1;
		uint64_t nus_bs:1;
		uint64_t dob_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dpi_bs:1;
#ewse
		uint64_t dpi_bs:1;
		uint64_t pdf_bs:1;
		uint64_t dob_bs:1;
		uint64_t nus_bs:1;
		uint64_t pos_bs:1;
		uint64_t wesewved_5_6:2;
		uint64_t pof1_bs:1;
		uint64_t pof0_bs:1;
		uint64_t pig_bs:1;
		uint64_t pgf_bs:1;
		uint64_t wdnw_bs:1;
		uint64_t pcad_bs:1;
		uint64_t pcac_bs:1;
		uint64_t wdn_bs:1;
		uint64_t pcn_bs:1;
		uint64_t pcnc_bs:1;
		uint64_t wdp_bs:1;
		uint64_t dif_bs:1;
		uint64_t csw_bs:1;
		uint64_t wesewved_20_63:44;
#endif
	} cn50xx;
};

union cvmx_npi_buff_size_outputx {
	uint64_t u64;
	stwuct cvmx_npi_buff_size_outputx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t isize:7;
		uint64_t bsize:16;
#ewse
		uint64_t bsize:16;
		uint64_t isize:7;
		uint64_t wesewved_23_63:41;
#endif
	} s;
};

union cvmx_npi_comp_ctw {
	uint64_t u64;
	stwuct cvmx_npi_comp_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pctw:5;
		uint64_t nctw:5;
#ewse
		uint64_t nctw:5;
		uint64_t pctw:5;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_npi_ctw_status {
	uint64_t u64;
	stwuct cvmx_npi_ctw_status_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t chip_wev:8;
		uint64_t dis_pniw:1;
		uint64_t out3_enb:1;
		uint64_t out2_enb:1;
		uint64_t out1_enb:1;
		uint64_t out0_enb:1;
		uint64_t ins3_enb:1;
		uint64_t ins2_enb:1;
		uint64_t ins1_enb:1;
		uint64_t ins0_enb:1;
		uint64_t ins3_64b:1;
		uint64_t ins2_64b:1;
		uint64_t ins1_64b:1;
		uint64_t ins0_64b:1;
		uint64_t pci_wdis:1;
		uint64_t wait_com:1;
		uint64_t wesewved_37_39:3;
		uint64_t max_wowd:5;
		uint64_t wesewved_10_31:22;
		uint64_t timew:10;
#ewse
		uint64_t timew:10;
		uint64_t wesewved_10_31:22;
		uint64_t max_wowd:5;
		uint64_t wesewved_37_39:3;
		uint64_t wait_com:1;
		uint64_t pci_wdis:1;
		uint64_t ins0_64b:1;
		uint64_t ins1_64b:1;
		uint64_t ins2_64b:1;
		uint64_t ins3_64b:1;
		uint64_t ins0_enb:1;
		uint64_t ins1_enb:1;
		uint64_t ins2_enb:1;
		uint64_t ins3_enb:1;
		uint64_t out0_enb:1;
		uint64_t out1_enb:1;
		uint64_t out2_enb:1;
		uint64_t out3_enb:1;
		uint64_t dis_pniw:1;
		uint64_t chip_wev:8;
		uint64_t wesewved_63_63:1;
#endif
	} s;
	stwuct cvmx_npi_ctw_status_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t chip_wev:8;
		uint64_t dis_pniw:1;
		uint64_t wesewved_51_53:3;
		uint64_t out0_enb:1;
		uint64_t wesewved_47_49:3;
		uint64_t ins0_enb:1;
		uint64_t wesewved_43_45:3;
		uint64_t ins0_64b:1;
		uint64_t pci_wdis:1;
		uint64_t wait_com:1;
		uint64_t wesewved_37_39:3;
		uint64_t max_wowd:5;
		uint64_t wesewved_10_31:22;
		uint64_t timew:10;
#ewse
		uint64_t timew:10;
		uint64_t wesewved_10_31:22;
		uint64_t max_wowd:5;
		uint64_t wesewved_37_39:3;
		uint64_t wait_com:1;
		uint64_t pci_wdis:1;
		uint64_t ins0_64b:1;
		uint64_t wesewved_43_45:3;
		uint64_t ins0_enb:1;
		uint64_t wesewved_47_49:3;
		uint64_t out0_enb:1;
		uint64_t wesewved_51_53:3;
		uint64_t dis_pniw:1;
		uint64_t chip_wev:8;
		uint64_t wesewved_63_63:1;
#endif
	} cn30xx;
	stwuct cvmx_npi_ctw_status_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t chip_wev:8;
		uint64_t dis_pniw:1;
		uint64_t wesewved_52_53:2;
		uint64_t out1_enb:1;
		uint64_t out0_enb:1;
		uint64_t wesewved_48_49:2;
		uint64_t ins1_enb:1;
		uint64_t ins0_enb:1;
		uint64_t wesewved_44_45:2;
		uint64_t ins1_64b:1;
		uint64_t ins0_64b:1;
		uint64_t pci_wdis:1;
		uint64_t wait_com:1;
		uint64_t wesewved_37_39:3;
		uint64_t max_wowd:5;
		uint64_t wesewved_10_31:22;
		uint64_t timew:10;
#ewse
		uint64_t timew:10;
		uint64_t wesewved_10_31:22;
		uint64_t max_wowd:5;
		uint64_t wesewved_37_39:3;
		uint64_t wait_com:1;
		uint64_t pci_wdis:1;
		uint64_t ins0_64b:1;
		uint64_t ins1_64b:1;
		uint64_t wesewved_44_45:2;
		uint64_t ins0_enb:1;
		uint64_t ins1_enb:1;
		uint64_t wesewved_48_49:2;
		uint64_t out0_enb:1;
		uint64_t out1_enb:1;
		uint64_t wesewved_52_53:2;
		uint64_t dis_pniw:1;
		uint64_t chip_wev:8;
		uint64_t wesewved_63_63:1;
#endif
	} cn31xx;
};

union cvmx_npi_dbg_sewect {
	uint64_t u64;
	stwuct cvmx_npi_dbg_sewect_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t dbg_sew:16;
#ewse
		uint64_t dbg_sew:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_npi_dma_contwow {
	uint64_t u64;
	stwuct cvmx_npi_dma_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t b0_wend:1;
		uint64_t dwb_denb:1;
		uint64_t dwb_ichk:9;
		uint64_t fpa_que:3;
		uint64_t o_add1:1;
		uint64_t o_wo:1;
		uint64_t o_ns:1;
		uint64_t o_es:2;
		uint64_t o_mode:1;
		uint64_t hp_enb:1;
		uint64_t wp_enb:1;
		uint64_t csize:14;
#ewse
		uint64_t csize:14;
		uint64_t wp_enb:1;
		uint64_t hp_enb:1;
		uint64_t o_mode:1;
		uint64_t o_es:2;
		uint64_t o_ns:1;
		uint64_t o_wo:1;
		uint64_t o_add1:1;
		uint64_t fpa_que:3;
		uint64_t dwb_ichk:9;
		uint64_t dwb_denb:1;
		uint64_t b0_wend:1;
		uint64_t wesewved_36_63:28;
#endif
	} s;
};

union cvmx_npi_dma_highp_counts {
	uint64_t u64;
	stwuct cvmx_npi_dma_highp_counts_s {
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

union cvmx_npi_dma_highp_naddw {
	uint64_t u64;
	stwuct cvmx_npi_dma_highp_naddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t state:4;
		uint64_t addw:36;
#ewse
		uint64_t addw:36;
		uint64_t state:4;
		uint64_t wesewved_40_63:24;
#endif
	} s;
};

union cvmx_npi_dma_wowp_counts {
	uint64_t u64;
	stwuct cvmx_npi_dma_wowp_counts_s {
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

union cvmx_npi_dma_wowp_naddw {
	uint64_t u64;
	stwuct cvmx_npi_dma_wowp_naddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t state:4;
		uint64_t addw:36;
#ewse
		uint64_t addw:36;
		uint64_t state:4;
		uint64_t wesewved_40_63:24;
#endif
	} s;
};

union cvmx_npi_highp_dbeww {
	uint64_t u64;
	stwuct cvmx_npi_highp_dbeww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t dbeww:16;
#ewse
		uint64_t dbeww:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_npi_highp_ibuff_saddw {
	uint64_t u64;
	stwuct cvmx_npi_highp_ibuff_saddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t saddw:36;
#ewse
		uint64_t saddw:36;
		uint64_t wesewved_36_63:28;
#endif
	} s;
};

union cvmx_npi_input_contwow {
	uint64_t u64;
	stwuct cvmx_npi_input_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_23_63:41;
		uint64_t pkt_ww:1;
		uint64_t pbp_dhi:13;
		uint64_t d_nsw:1;
		uint64_t d_esw:2;
		uint64_t d_wow:1;
		uint64_t use_csw:1;
		uint64_t nsw:1;
		uint64_t esw:2;
		uint64_t wow:1;
#ewse
		uint64_t wow:1;
		uint64_t esw:2;
		uint64_t nsw:1;
		uint64_t use_csw:1;
		uint64_t d_wow:1;
		uint64_t d_esw:2;
		uint64_t d_nsw:1;
		uint64_t pbp_dhi:13;
		uint64_t pkt_ww:1;
		uint64_t wesewved_23_63:41;
#endif
	} s;
	stwuct cvmx_npi_input_contwow_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t pbp_dhi:13;
		uint64_t d_nsw:1;
		uint64_t d_esw:2;
		uint64_t d_wow:1;
		uint64_t use_csw:1;
		uint64_t nsw:1;
		uint64_t esw:2;
		uint64_t wow:1;
#ewse
		uint64_t wow:1;
		uint64_t esw:2;
		uint64_t nsw:1;
		uint64_t use_csw:1;
		uint64_t d_wow:1;
		uint64_t d_esw:2;
		uint64_t d_nsw:1;
		uint64_t pbp_dhi:13;
		uint64_t wesewved_22_63:42;
#endif
	} cn30xx;
};

union cvmx_npi_int_enb {
	uint64_t u64;
	stwuct cvmx_npi_int_enb_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t i3_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t p3_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t p3_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t g3_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t p3_peww:1;
		uint64_t p2_peww:1;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t p3_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t i3_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t i3_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t po3_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po3_2smw:1;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i3_wtout:1;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i3_ovewf:1;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p3_wtout:1;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t p2_peww:1;
		uint64_t p3_peww:1;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g3_wtout:1;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p3_ppeww:1;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p3_ptout:1;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i3_ppeww:1;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} s;
	stwuct cvmx_npi_int_enb_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t wesewved_36_38:3;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_32_34:3;
		uint64_t p0_ptout:1;
		uint64_t wesewved_28_30:3;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_24_26:3;
		uint64_t g0_wtout:1;
		uint64_t wesewved_20_22:3;
		uint64_t p0_peww:1;
		uint64_t wesewved_16_18:3;
		uint64_t p0_wtout:1;
		uint64_t wesewved_12_14:3;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_8_10:3;
		uint64_t i0_wtout:1;
		uint64_t wesewved_4_6:3;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t wesewved_4_6:3;
		uint64_t i0_wtout:1;
		uint64_t wesewved_8_10:3;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_12_14:3;
		uint64_t p0_wtout:1;
		uint64_t wesewved_16_18:3;
		uint64_t p0_peww:1;
		uint64_t wesewved_20_22:3;
		uint64_t g0_wtout:1;
		uint64_t wesewved_24_26:3;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_28_30:3;
		uint64_t p0_ptout:1;
		uint64_t wesewved_32_34:3;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_36_38:3;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} cn30xx;
	stwuct cvmx_npi_int_enb_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t wesewved_37_38:2;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_33_34:2;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t wesewved_29_30:2;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_25_26:2;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t wesewved_21_22:2;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t wesewved_17_18:2;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t wesewved_13_14:2;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_9_10:2;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t wesewved_5_6:2;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t wesewved_5_6:2;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t wesewved_9_10:2;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t wesewved_13_14:2;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t wesewved_17_18:2;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t wesewved_21_22:2;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t wesewved_25_26:2;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t wesewved_29_30:2;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t wesewved_33_34:2;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t wesewved_37_38:2;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} cn31xx;
	stwuct cvmx_npi_int_enb_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t i3_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t p3_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t p3_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t g3_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t p3_peww:1;
		uint64_t p2_peww:1;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t p3_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t i3_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t i3_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t po3_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po3_2smw:1;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i3_wtout:1;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i3_ovewf:1;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p3_wtout:1;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t p2_peww:1;
		uint64_t p3_peww:1;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g3_wtout:1;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p3_ppeww:1;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p3_ptout:1;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i3_ppeww:1;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t wesewved_42_63:22;
#endif
	} cn38xxp2;
};

union cvmx_npi_int_sum {
	uint64_t u64;
	stwuct cvmx_npi_int_sum_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t i3_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t p3_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t p3_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t g3_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t p3_peww:1;
		uint64_t p2_peww:1;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t p3_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t i3_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t i3_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t po3_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po3_2smw:1;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i3_wtout:1;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i3_ovewf:1;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p3_wtout:1;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t p2_peww:1;
		uint64_t p3_peww:1;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g3_wtout:1;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p3_ppeww:1;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p3_ptout:1;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i3_ppeww:1;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} s;
	stwuct cvmx_npi_int_sum_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t wesewved_36_38:3;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_32_34:3;
		uint64_t p0_ptout:1;
		uint64_t wesewved_28_30:3;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_24_26:3;
		uint64_t g0_wtout:1;
		uint64_t wesewved_20_22:3;
		uint64_t p0_peww:1;
		uint64_t wesewved_16_18:3;
		uint64_t p0_wtout:1;
		uint64_t wesewved_12_14:3;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_8_10:3;
		uint64_t i0_wtout:1;
		uint64_t wesewved_4_6:3;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t wesewved_4_6:3;
		uint64_t i0_wtout:1;
		uint64_t wesewved_8_10:3;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_12_14:3;
		uint64_t p0_wtout:1;
		uint64_t wesewved_16_18:3;
		uint64_t p0_peww:1;
		uint64_t wesewved_20_22:3;
		uint64_t g0_wtout:1;
		uint64_t wesewved_24_26:3;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_28_30:3;
		uint64_t p0_ptout:1;
		uint64_t wesewved_32_34:3;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_36_38:3;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} cn30xx;
	stwuct cvmx_npi_int_sum_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t q1_a_f:1;
		uint64_t q1_s_e:1;
		uint64_t pdf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pcf_p_e:1;
		uint64_t wdx_s_e:1;
		uint64_t wwx_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t com_a_f:1;
		uint64_t com_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t fcw_s_e:1;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t wesewved_37_38:2;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t wesewved_33_34:2;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t wesewved_29_30:2;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t wesewved_25_26:2;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t wesewved_21_22:2;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t wesewved_17_18:2;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t wesewved_13_14:2;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t wesewved_9_10:2;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t wesewved_5_6:2;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t wesewved_5_6:2;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t wesewved_9_10:2;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t wesewved_13_14:2;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t wesewved_17_18:2;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t wesewved_21_22:2;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t wesewved_25_26:2;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t wesewved_29_30:2;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t wesewved_33_34:2;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t wesewved_37_38:2;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t fcw_s_e:1;
		uint64_t fcw_a_f:1;
		uint64_t pcw_s_e:1;
		uint64_t pcw_a_f:1;
		uint64_t q2_s_e:1;
		uint64_t q2_a_f:1;
		uint64_t q3_s_e:1;
		uint64_t q3_a_f:1;
		uint64_t com_s_e:1;
		uint64_t com_a_f:1;
		uint64_t pnc_s_e:1;
		uint64_t pnc_a_f:1;
		uint64_t wwx_s_e:1;
		uint64_t wdx_s_e:1;
		uint64_t pcf_p_e:1;
		uint64_t pcf_p_f:1;
		uint64_t pdf_p_e:1;
		uint64_t pdf_p_f:1;
		uint64_t q1_s_e:1;
		uint64_t q1_a_f:1;
		uint64_t wesewved_62_63:2;
#endif
	} cn31xx;
	stwuct cvmx_npi_int_sum_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t iobdma:1;
		uint64_t p_dpeww:1;
		uint64_t win_wto:1;
		uint64_t i3_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i0_ppeww:1;
		uint64_t p3_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p0_ptout:1;
		uint64_t p3_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p0_ppeww:1;
		uint64_t g3_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g0_wtout:1;
		uint64_t p3_peww:1;
		uint64_t p2_peww:1;
		uint64_t p1_peww:1;
		uint64_t p0_peww:1;
		uint64_t p3_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p0_wtout:1;
		uint64_t i3_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i0_ovewf:1;
		uint64_t i3_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i0_wtout:1;
		uint64_t po3_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po0_2smw:1;
		uint64_t pci_wsw:1;
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
#ewse
		uint64_t wmw_wto:1;
		uint64_t wmw_wto:1;
		uint64_t pci_wsw:1;
		uint64_t po0_2smw:1;
		uint64_t po1_2smw:1;
		uint64_t po2_2smw:1;
		uint64_t po3_2smw:1;
		uint64_t i0_wtout:1;
		uint64_t i1_wtout:1;
		uint64_t i2_wtout:1;
		uint64_t i3_wtout:1;
		uint64_t i0_ovewf:1;
		uint64_t i1_ovewf:1;
		uint64_t i2_ovewf:1;
		uint64_t i3_ovewf:1;
		uint64_t p0_wtout:1;
		uint64_t p1_wtout:1;
		uint64_t p2_wtout:1;
		uint64_t p3_wtout:1;
		uint64_t p0_peww:1;
		uint64_t p1_peww:1;
		uint64_t p2_peww:1;
		uint64_t p3_peww:1;
		uint64_t g0_wtout:1;
		uint64_t g1_wtout:1;
		uint64_t g2_wtout:1;
		uint64_t g3_wtout:1;
		uint64_t p0_ppeww:1;
		uint64_t p1_ppeww:1;
		uint64_t p2_ppeww:1;
		uint64_t p3_ppeww:1;
		uint64_t p0_ptout:1;
		uint64_t p1_ptout:1;
		uint64_t p2_ptout:1;
		uint64_t p3_ptout:1;
		uint64_t i0_ppeww:1;
		uint64_t i1_ppeww:1;
		uint64_t i2_ppeww:1;
		uint64_t i3_ppeww:1;
		uint64_t win_wto:1;
		uint64_t p_dpeww:1;
		uint64_t iobdma:1;
		uint64_t wesewved_42_63:22;
#endif
	} cn38xxp2;
};

union cvmx_npi_wowp_dbeww {
	uint64_t u64;
	stwuct cvmx_npi_wowp_dbeww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t dbeww:16;
#ewse
		uint64_t dbeww:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_npi_wowp_ibuff_saddw {
	uint64_t u64;
	stwuct cvmx_npi_wowp_ibuff_saddw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t saddw:36;
#ewse
		uint64_t saddw:36;
		uint64_t wesewved_36_63:28;
#endif
	} s;
};

union cvmx_npi_mem_access_subidx {
	uint64_t u64;
	stwuct cvmx_npi_mem_access_subidx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t showtw:1;
		uint64_t nmewge:1;
		uint64_t esw:2;
		uint64_t esw:2;
		uint64_t nsw:1;
		uint64_t nsw:1;
		uint64_t wow:1;
		uint64_t wow:1;
		uint64_t ba:28;
#ewse
		uint64_t ba:28;
		uint64_t wow:1;
		uint64_t wow:1;
		uint64_t nsw:1;
		uint64_t nsw:1;
		uint64_t esw:2;
		uint64_t esw:2;
		uint64_t nmewge:1;
		uint64_t showtw:1;
		uint64_t wesewved_38_63:26;
#endif
	} s;
	stwuct cvmx_npi_mem_access_subidx_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t esw:2;
		uint64_t esw:2;
		uint64_t nsw:1;
		uint64_t nsw:1;
		uint64_t wow:1;
		uint64_t wow:1;
		uint64_t ba:28;
#ewse
		uint64_t ba:28;
		uint64_t wow:1;
		uint64_t wow:1;
		uint64_t nsw:1;
		uint64_t nsw:1;
		uint64_t esw:2;
		uint64_t esw:2;
		uint64_t wesewved_36_63:28;
#endif
	} cn31xx;
};

union cvmx_npi_msi_wcv {
	uint64_t u64;
	stwuct cvmx_npi_msi_wcv_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t int_vec:64;
#ewse
		uint64_t int_vec:64;
#endif
	} s;
};

union cvmx_npi_num_desc_outputx {
	uint64_t u64;
	stwuct cvmx_npi_num_desc_outputx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t size:32;
#ewse
		uint64_t size:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_npi_output_contwow {
	uint64_t u64;
	stwuct cvmx_npi_output_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t pkt_ww:1;
		uint64_t p3_bmode:1;
		uint64_t p2_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t p0_bmode:1;
		uint64_t o3_es:2;
		uint64_t o3_ns:1;
		uint64_t o3_wo:1;
		uint64_t o2_es:2;
		uint64_t o2_ns:1;
		uint64_t o2_wo:1;
		uint64_t o1_es:2;
		uint64_t o1_ns:1;
		uint64_t o1_wo:1;
		uint64_t o0_es:2;
		uint64_t o0_ns:1;
		uint64_t o0_wo:1;
		uint64_t o3_cswm:1;
		uint64_t o2_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t o0_cswm:1;
		uint64_t wesewved_20_23:4;
		uint64_t iptw_o3:1;
		uint64_t iptw_o2:1;
		uint64_t iptw_o1:1;
		uint64_t iptw_o0:1;
		uint64_t esw_sw3:2;
		uint64_t nsw_sw3:1;
		uint64_t wow_sw3:1;
		uint64_t esw_sw2:2;
		uint64_t nsw_sw2:1;
		uint64_t wow_sw2:1;
		uint64_t esw_sw1:2;
		uint64_t nsw_sw1:1;
		uint64_t wow_sw1:1;
		uint64_t esw_sw0:2;
		uint64_t nsw_sw0:1;
		uint64_t wow_sw0:1;
#ewse
		uint64_t wow_sw0:1;
		uint64_t nsw_sw0:1;
		uint64_t esw_sw0:2;
		uint64_t wow_sw1:1;
		uint64_t nsw_sw1:1;
		uint64_t esw_sw1:2;
		uint64_t wow_sw2:1;
		uint64_t nsw_sw2:1;
		uint64_t esw_sw2:2;
		uint64_t wow_sw3:1;
		uint64_t nsw_sw3:1;
		uint64_t esw_sw3:2;
		uint64_t iptw_o0:1;
		uint64_t iptw_o1:1;
		uint64_t iptw_o2:1;
		uint64_t iptw_o3:1;
		uint64_t wesewved_20_23:4;
		uint64_t o0_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t o2_cswm:1;
		uint64_t o3_cswm:1;
		uint64_t o0_wo:1;
		uint64_t o0_ns:1;
		uint64_t o0_es:2;
		uint64_t o1_wo:1;
		uint64_t o1_ns:1;
		uint64_t o1_es:2;
		uint64_t o2_wo:1;
		uint64_t o2_ns:1;
		uint64_t o2_es:2;
		uint64_t o3_wo:1;
		uint64_t o3_ns:1;
		uint64_t o3_es:2;
		uint64_t p0_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t p2_bmode:1;
		uint64_t p3_bmode:1;
		uint64_t pkt_ww:1;
		uint64_t wesewved_49_63:15;
#endif
	} s;
	stwuct cvmx_npi_output_contwow_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_45_63:19;
		uint64_t p0_bmode:1;
		uint64_t wesewved_32_43:12;
		uint64_t o0_es:2;
		uint64_t o0_ns:1;
		uint64_t o0_wo:1;
		uint64_t wesewved_25_27:3;
		uint64_t o0_cswm:1;
		uint64_t wesewved_17_23:7;
		uint64_t iptw_o0:1;
		uint64_t wesewved_4_15:12;
		uint64_t esw_sw0:2;
		uint64_t nsw_sw0:1;
		uint64_t wow_sw0:1;
#ewse
		uint64_t wow_sw0:1;
		uint64_t nsw_sw0:1;
		uint64_t esw_sw0:2;
		uint64_t wesewved_4_15:12;
		uint64_t iptw_o0:1;
		uint64_t wesewved_17_23:7;
		uint64_t o0_cswm:1;
		uint64_t wesewved_25_27:3;
		uint64_t o0_wo:1;
		uint64_t o0_ns:1;
		uint64_t o0_es:2;
		uint64_t wesewved_32_43:12;
		uint64_t p0_bmode:1;
		uint64_t wesewved_45_63:19;
#endif
	} cn30xx;
	stwuct cvmx_npi_output_contwow_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_46_63:18;
		uint64_t p1_bmode:1;
		uint64_t p0_bmode:1;
		uint64_t wesewved_36_43:8;
		uint64_t o1_es:2;
		uint64_t o1_ns:1;
		uint64_t o1_wo:1;
		uint64_t o0_es:2;
		uint64_t o0_ns:1;
		uint64_t o0_wo:1;
		uint64_t wesewved_26_27:2;
		uint64_t o1_cswm:1;
		uint64_t o0_cswm:1;
		uint64_t wesewved_18_23:6;
		uint64_t iptw_o1:1;
		uint64_t iptw_o0:1;
		uint64_t wesewved_8_15:8;
		uint64_t esw_sw1:2;
		uint64_t nsw_sw1:1;
		uint64_t wow_sw1:1;
		uint64_t esw_sw0:2;
		uint64_t nsw_sw0:1;
		uint64_t wow_sw0:1;
#ewse
		uint64_t wow_sw0:1;
		uint64_t nsw_sw0:1;
		uint64_t esw_sw0:2;
		uint64_t wow_sw1:1;
		uint64_t nsw_sw1:1;
		uint64_t esw_sw1:2;
		uint64_t wesewved_8_15:8;
		uint64_t iptw_o0:1;
		uint64_t iptw_o1:1;
		uint64_t wesewved_18_23:6;
		uint64_t o0_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t wesewved_26_27:2;
		uint64_t o0_wo:1;
		uint64_t o0_ns:1;
		uint64_t o0_es:2;
		uint64_t o1_wo:1;
		uint64_t o1_ns:1;
		uint64_t o1_es:2;
		uint64_t wesewved_36_43:8;
		uint64_t p0_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t wesewved_46_63:18;
#endif
	} cn31xx;
	stwuct cvmx_npi_output_contwow_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t p3_bmode:1;
		uint64_t p2_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t p0_bmode:1;
		uint64_t o3_es:2;
		uint64_t o3_ns:1;
		uint64_t o3_wo:1;
		uint64_t o2_es:2;
		uint64_t o2_ns:1;
		uint64_t o2_wo:1;
		uint64_t o1_es:2;
		uint64_t o1_ns:1;
		uint64_t o1_wo:1;
		uint64_t o0_es:2;
		uint64_t o0_ns:1;
		uint64_t o0_wo:1;
		uint64_t o3_cswm:1;
		uint64_t o2_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t o0_cswm:1;
		uint64_t wesewved_20_23:4;
		uint64_t iptw_o3:1;
		uint64_t iptw_o2:1;
		uint64_t iptw_o1:1;
		uint64_t iptw_o0:1;
		uint64_t esw_sw3:2;
		uint64_t nsw_sw3:1;
		uint64_t wow_sw3:1;
		uint64_t esw_sw2:2;
		uint64_t nsw_sw2:1;
		uint64_t wow_sw2:1;
		uint64_t esw_sw1:2;
		uint64_t nsw_sw1:1;
		uint64_t wow_sw1:1;
		uint64_t esw_sw0:2;
		uint64_t nsw_sw0:1;
		uint64_t wow_sw0:1;
#ewse
		uint64_t wow_sw0:1;
		uint64_t nsw_sw0:1;
		uint64_t esw_sw0:2;
		uint64_t wow_sw1:1;
		uint64_t nsw_sw1:1;
		uint64_t esw_sw1:2;
		uint64_t wow_sw2:1;
		uint64_t nsw_sw2:1;
		uint64_t esw_sw2:2;
		uint64_t wow_sw3:1;
		uint64_t nsw_sw3:1;
		uint64_t esw_sw3:2;
		uint64_t iptw_o0:1;
		uint64_t iptw_o1:1;
		uint64_t iptw_o2:1;
		uint64_t iptw_o3:1;
		uint64_t wesewved_20_23:4;
		uint64_t o0_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t o2_cswm:1;
		uint64_t o3_cswm:1;
		uint64_t o0_wo:1;
		uint64_t o0_ns:1;
		uint64_t o0_es:2;
		uint64_t o1_wo:1;
		uint64_t o1_ns:1;
		uint64_t o1_es:2;
		uint64_t o2_wo:1;
		uint64_t o2_ns:1;
		uint64_t o2_es:2;
		uint64_t o3_wo:1;
		uint64_t o3_ns:1;
		uint64_t o3_es:2;
		uint64_t p0_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t p2_bmode:1;
		uint64_t p3_bmode:1;
		uint64_t wesewved_48_63:16;
#endif
	} cn38xxp2;
	stwuct cvmx_npi_output_contwow_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t pkt_ww:1;
		uint64_t wesewved_46_47:2;
		uint64_t p1_bmode:1;
		uint64_t p0_bmode:1;
		uint64_t wesewved_36_43:8;
		uint64_t o1_es:2;
		uint64_t o1_ns:1;
		uint64_t o1_wo:1;
		uint64_t o0_es:2;
		uint64_t o0_ns:1;
		uint64_t o0_wo:1;
		uint64_t wesewved_26_27:2;
		uint64_t o1_cswm:1;
		uint64_t o0_cswm:1;
		uint64_t wesewved_18_23:6;
		uint64_t iptw_o1:1;
		uint64_t iptw_o0:1;
		uint64_t wesewved_8_15:8;
		uint64_t esw_sw1:2;
		uint64_t nsw_sw1:1;
		uint64_t wow_sw1:1;
		uint64_t esw_sw0:2;
		uint64_t nsw_sw0:1;
		uint64_t wow_sw0:1;
#ewse
		uint64_t wow_sw0:1;
		uint64_t nsw_sw0:1;
		uint64_t esw_sw0:2;
		uint64_t wow_sw1:1;
		uint64_t nsw_sw1:1;
		uint64_t esw_sw1:2;
		uint64_t wesewved_8_15:8;
		uint64_t iptw_o0:1;
		uint64_t iptw_o1:1;
		uint64_t wesewved_18_23:6;
		uint64_t o0_cswm:1;
		uint64_t o1_cswm:1;
		uint64_t wesewved_26_27:2;
		uint64_t o0_wo:1;
		uint64_t o0_ns:1;
		uint64_t o0_es:2;
		uint64_t o1_wo:1;
		uint64_t o1_ns:1;
		uint64_t o1_es:2;
		uint64_t wesewved_36_43:8;
		uint64_t p0_bmode:1;
		uint64_t p1_bmode:1;
		uint64_t wesewved_46_47:2;
		uint64_t pkt_ww:1;
		uint64_t wesewved_49_63:15;
#endif
	} cn50xx;
};

union cvmx_npi_px_dbpaiw_addw {
	uint64_t u64;
	stwuct cvmx_npi_px_dbpaiw_addw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_63_63:1;
		uint64_t state:2;
		uint64_t naddw:61;
#ewse
		uint64_t naddw:61;
		uint64_t state:2;
		uint64_t wesewved_63_63:1;
#endif
	} s;
};

union cvmx_npi_px_instw_addw {
	uint64_t u64;
	stwuct cvmx_npi_px_instw_addw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t state:3;
		uint64_t naddw:61;
#ewse
		uint64_t naddw:61;
		uint64_t state:3;
#endif
	} s;
};

union cvmx_npi_px_instw_cnts {
	uint64_t u64;
	stwuct cvmx_npi_px_instw_cnts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_38_63:26;
		uint64_t fcnt:6;
		uint64_t avaiw:32;
#ewse
		uint64_t avaiw:32;
		uint64_t fcnt:6;
		uint64_t wesewved_38_63:26;
#endif
	} s;
};

union cvmx_npi_px_paiw_cnts {
	uint64_t u64;
	stwuct cvmx_npi_px_paiw_cnts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t fcnt:5;
		uint64_t avaiw:32;
#ewse
		uint64_t avaiw:32;
		uint64_t fcnt:5;
		uint64_t wesewved_37_63:27;
#endif
	} s;
};

union cvmx_npi_pci_buwst_size {
	uint64_t u64;
	stwuct cvmx_npi_pci_buwst_size_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t ww_bwst:7;
		uint64_t wd_bwst:7;
#ewse
		uint64_t wd_bwst:7;
		uint64_t ww_bwst:7;
		uint64_t wesewved_14_63:50;
#endif
	} s;
};

union cvmx_npi_pci_int_awb_cfg {
	uint64_t u64;
	stwuct cvmx_npi_pci_int_awb_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t hostmode:1;
		uint64_t pci_ovw:4;
		uint64_t wesewved_5_7:3;
		uint64_t en:1;
		uint64_t pawk_mod:1;
		uint64_t pawk_dev:3;
#ewse
		uint64_t pawk_dev:3;
		uint64_t pawk_mod:1;
		uint64_t en:1;
		uint64_t wesewved_5_7:3;
		uint64_t pci_ovw:4;
		uint64_t hostmode:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_npi_pci_int_awb_cfg_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t en:1;
		uint64_t pawk_mod:1;
		uint64_t pawk_dev:3;
#ewse
		uint64_t pawk_dev:3;
		uint64_t pawk_mod:1;
		uint64_t en:1;
		uint64_t wesewved_5_63:59;
#endif
	} cn30xx;
};

union cvmx_npi_pci_wead_cmd {
	uint64_t u64;
	stwuct cvmx_npi_pci_wead_cmd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_11_63:53;
		uint64_t cmd_size:11;
#ewse
		uint64_t cmd_size:11;
		uint64_t wesewved_11_63:53;
#endif
	} s;
};

union cvmx_npi_powt32_instw_hdw {
	uint64_t u64;
	stwuct cvmx_npi_powt32_instw_hdw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t pbp:1;
		uint64_t wsv_f:5;
		uint64_t wpawmode:2;
		uint64_t wsv_e:1;
		uint64_t wskp_wen:7;
		uint64_t wsv_d:6;
		uint64_t use_ihdw:1;
		uint64_t wsv_c:5;
		uint64_t paw_mode:2;
		uint64_t wsv_b:1;
		uint64_t skp_wen:7;
		uint64_t wsv_a:6;
#ewse
		uint64_t wsv_a:6;
		uint64_t skp_wen:7;
		uint64_t wsv_b:1;
		uint64_t paw_mode:2;
		uint64_t wsv_c:5;
		uint64_t use_ihdw:1;
		uint64_t wsv_d:6;
		uint64_t wskp_wen:7;
		uint64_t wsv_e:1;
		uint64_t wpawmode:2;
		uint64_t wsv_f:5;
		uint64_t pbp:1;
		uint64_t wesewved_44_63:20;
#endif
	} s;
};

union cvmx_npi_powt33_instw_hdw {
	uint64_t u64;
	stwuct cvmx_npi_powt33_instw_hdw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t pbp:1;
		uint64_t wsv_f:5;
		uint64_t wpawmode:2;
		uint64_t wsv_e:1;
		uint64_t wskp_wen:7;
		uint64_t wsv_d:6;
		uint64_t use_ihdw:1;
		uint64_t wsv_c:5;
		uint64_t paw_mode:2;
		uint64_t wsv_b:1;
		uint64_t skp_wen:7;
		uint64_t wsv_a:6;
#ewse
		uint64_t wsv_a:6;
		uint64_t skp_wen:7;
		uint64_t wsv_b:1;
		uint64_t paw_mode:2;
		uint64_t wsv_c:5;
		uint64_t use_ihdw:1;
		uint64_t wsv_d:6;
		uint64_t wskp_wen:7;
		uint64_t wsv_e:1;
		uint64_t wpawmode:2;
		uint64_t wsv_f:5;
		uint64_t pbp:1;
		uint64_t wesewved_44_63:20;
#endif
	} s;
};

union cvmx_npi_powt34_instw_hdw {
	uint64_t u64;
	stwuct cvmx_npi_powt34_instw_hdw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t pbp:1;
		uint64_t wsv_f:5;
		uint64_t wpawmode:2;
		uint64_t wsv_e:1;
		uint64_t wskp_wen:7;
		uint64_t wsv_d:6;
		uint64_t use_ihdw:1;
		uint64_t wsv_c:5;
		uint64_t paw_mode:2;
		uint64_t wsv_b:1;
		uint64_t skp_wen:7;
		uint64_t wsv_a:6;
#ewse
		uint64_t wsv_a:6;
		uint64_t skp_wen:7;
		uint64_t wsv_b:1;
		uint64_t paw_mode:2;
		uint64_t wsv_c:5;
		uint64_t use_ihdw:1;
		uint64_t wsv_d:6;
		uint64_t wskp_wen:7;
		uint64_t wsv_e:1;
		uint64_t wpawmode:2;
		uint64_t wsv_f:5;
		uint64_t pbp:1;
		uint64_t wesewved_44_63:20;
#endif
	} s;
};

union cvmx_npi_powt35_instw_hdw {
	uint64_t u64;
	stwuct cvmx_npi_powt35_instw_hdw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t pbp:1;
		uint64_t wsv_f:5;
		uint64_t wpawmode:2;
		uint64_t wsv_e:1;
		uint64_t wskp_wen:7;
		uint64_t wsv_d:6;
		uint64_t use_ihdw:1;
		uint64_t wsv_c:5;
		uint64_t paw_mode:2;
		uint64_t wsv_b:1;
		uint64_t skp_wen:7;
		uint64_t wsv_a:6;
#ewse
		uint64_t wsv_a:6;
		uint64_t skp_wen:7;
		uint64_t wsv_b:1;
		uint64_t paw_mode:2;
		uint64_t wsv_c:5;
		uint64_t use_ihdw:1;
		uint64_t wsv_d:6;
		uint64_t wskp_wen:7;
		uint64_t wsv_e:1;
		uint64_t wpawmode:2;
		uint64_t wsv_f:5;
		uint64_t pbp:1;
		uint64_t wesewved_44_63:20;
#endif
	} s;
};

union cvmx_npi_powt_bp_contwow {
	uint64_t u64;
	stwuct cvmx_npi_powt_bp_contwow_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t bp_on:4;
		uint64_t enb:4;
#ewse
		uint64_t enb:4;
		uint64_t bp_on:4;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_npi_wsw_int_bwocks {
	uint64_t u64;
	stwuct cvmx_npi_wsw_int_bwocks_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wint_31:1;
		uint64_t iob:1;
		uint64_t wesewved_28_29:2;
		uint64_t wint_27:1;
		uint64_t wint_26:1;
		uint64_t wint_25:1;
		uint64_t wint_24:1;
		uint64_t asx1:1;
		uint64_t asx0:1;
		uint64_t wint_21:1;
		uint64_t pip:1;
		uint64_t spx1:1;
		uint64_t spx0:1;
		uint64_t wmc:1;
		uint64_t w2c:1;
		uint64_t wint_15:1;
		uint64_t wesewved_13_14:2;
		uint64_t pow:1;
		uint64_t tim:1;
		uint64_t pko:1;
		uint64_t ipd:1;
		uint64_t wint_8:1;
		uint64_t zip:1;
		uint64_t dfa:1;
		uint64_t fpa:1;
		uint64_t key:1;
		uint64_t npi:1;
		uint64_t gmx1:1;
		uint64_t gmx0:1;
		uint64_t mio:1;
#ewse
		uint64_t mio:1;
		uint64_t gmx0:1;
		uint64_t gmx1:1;
		uint64_t npi:1;
		uint64_t key:1;
		uint64_t fpa:1;
		uint64_t dfa:1;
		uint64_t zip:1;
		uint64_t wint_8:1;
		uint64_t ipd:1;
		uint64_t pko:1;
		uint64_t tim:1;
		uint64_t pow:1;
		uint64_t wesewved_13_14:2;
		uint64_t wint_15:1;
		uint64_t w2c:1;
		uint64_t wmc:1;
		uint64_t spx0:1;
		uint64_t spx1:1;
		uint64_t pip:1;
		uint64_t wint_21:1;
		uint64_t asx0:1;
		uint64_t asx1:1;
		uint64_t wint_24:1;
		uint64_t wint_25:1;
		uint64_t wint_26:1;
		uint64_t wint_27:1;
		uint64_t wesewved_28_29:2;
		uint64_t iob:1;
		uint64_t wint_31:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_npi_wsw_int_bwocks_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wint_31:1;
		uint64_t iob:1;
		uint64_t wint_29:1;
		uint64_t wint_28:1;
		uint64_t wint_27:1;
		uint64_t wint_26:1;
		uint64_t wint_25:1;
		uint64_t wint_24:1;
		uint64_t asx1:1;
		uint64_t asx0:1;
		uint64_t wint_21:1;
		uint64_t pip:1;
		uint64_t spx1:1;
		uint64_t spx0:1;
		uint64_t wmc:1;
		uint64_t w2c:1;
		uint64_t wint_15:1;
		uint64_t wint_14:1;
		uint64_t usb:1;
		uint64_t pow:1;
		uint64_t tim:1;
		uint64_t pko:1;
		uint64_t ipd:1;
		uint64_t wint_8:1;
		uint64_t zip:1;
		uint64_t dfa:1;
		uint64_t fpa:1;
		uint64_t key:1;
		uint64_t npi:1;
		uint64_t gmx1:1;
		uint64_t gmx0:1;
		uint64_t mio:1;
#ewse
		uint64_t mio:1;
		uint64_t gmx0:1;
		uint64_t gmx1:1;
		uint64_t npi:1;
		uint64_t key:1;
		uint64_t fpa:1;
		uint64_t dfa:1;
		uint64_t zip:1;
		uint64_t wint_8:1;
		uint64_t ipd:1;
		uint64_t pko:1;
		uint64_t tim:1;
		uint64_t pow:1;
		uint64_t usb:1;
		uint64_t wint_14:1;
		uint64_t wint_15:1;
		uint64_t w2c:1;
		uint64_t wmc:1;
		uint64_t spx0:1;
		uint64_t spx1:1;
		uint64_t pip:1;
		uint64_t wint_21:1;
		uint64_t asx0:1;
		uint64_t asx1:1;
		uint64_t wint_24:1;
		uint64_t wint_25:1;
		uint64_t wint_26:1;
		uint64_t wint_27:1;
		uint64_t wint_28:1;
		uint64_t wint_29:1;
		uint64_t iob:1;
		uint64_t wint_31:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn30xx;
	stwuct cvmx_npi_wsw_int_bwocks_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t wint_31:1;
		uint64_t iob:1;
		uint64_t wint_29:1;
		uint64_t wint_28:1;
		uint64_t wint_27:1;
		uint64_t wint_26:1;
		uint64_t wint_25:1;
		uint64_t wint_24:1;
		uint64_t asx1:1;
		uint64_t asx0:1;
		uint64_t wint_21:1;
		uint64_t pip:1;
		uint64_t spx1:1;
		uint64_t spx0:1;
		uint64_t wmc:1;
		uint64_t w2c:1;
		uint64_t wint_15:1;
		uint64_t wint_14:1;
		uint64_t wint_13:1;
		uint64_t pow:1;
		uint64_t tim:1;
		uint64_t pko:1;
		uint64_t ipd:1;
		uint64_t wint_8:1;
		uint64_t zip:1;
		uint64_t dfa:1;
		uint64_t fpa:1;
		uint64_t key:1;
		uint64_t npi:1;
		uint64_t gmx1:1;
		uint64_t gmx0:1;
		uint64_t mio:1;
#ewse
		uint64_t mio:1;
		uint64_t gmx0:1;
		uint64_t gmx1:1;
		uint64_t npi:1;
		uint64_t key:1;
		uint64_t fpa:1;
		uint64_t dfa:1;
		uint64_t zip:1;
		uint64_t wint_8:1;
		uint64_t ipd:1;
		uint64_t pko:1;
		uint64_t tim:1;
		uint64_t pow:1;
		uint64_t wint_13:1;
		uint64_t wint_14:1;
		uint64_t wint_15:1;
		uint64_t w2c:1;
		uint64_t wmc:1;
		uint64_t spx0:1;
		uint64_t spx1:1;
		uint64_t pip:1;
		uint64_t wint_21:1;
		uint64_t asx0:1;
		uint64_t asx1:1;
		uint64_t wint_24:1;
		uint64_t wint_25:1;
		uint64_t wint_26:1;
		uint64_t wint_27:1;
		uint64_t wint_28:1;
		uint64_t wint_29:1;
		uint64_t iob:1;
		uint64_t wint_31:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn38xx;
	stwuct cvmx_npi_wsw_int_bwocks_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_31_63:33;
		uint64_t iob:1;
		uint64_t wmc1:1;
		uint64_t agw:1;
		uint64_t wesewved_24_27:4;
		uint64_t asx1:1;
		uint64_t asx0:1;
		uint64_t wesewved_21_21:1;
		uint64_t pip:1;
		uint64_t spx1:1;
		uint64_t spx0:1;
		uint64_t wmc:1;
		uint64_t w2c:1;
		uint64_t wesewved_15_15:1;
		uint64_t wad:1;
		uint64_t usb:1;
		uint64_t pow:1;
		uint64_t tim:1;
		uint64_t pko:1;
		uint64_t ipd:1;
		uint64_t wesewved_8_8:1;
		uint64_t zip:1;
		uint64_t dfa:1;
		uint64_t fpa:1;
		uint64_t key:1;
		uint64_t npi:1;
		uint64_t gmx1:1;
		uint64_t gmx0:1;
		uint64_t mio:1;
#ewse
		uint64_t mio:1;
		uint64_t gmx0:1;
		uint64_t gmx1:1;
		uint64_t npi:1;
		uint64_t key:1;
		uint64_t fpa:1;
		uint64_t dfa:1;
		uint64_t zip:1;
		uint64_t wesewved_8_8:1;
		uint64_t ipd:1;
		uint64_t pko:1;
		uint64_t tim:1;
		uint64_t pow:1;
		uint64_t usb:1;
		uint64_t wad:1;
		uint64_t wesewved_15_15:1;
		uint64_t w2c:1;
		uint64_t wmc:1;
		uint64_t spx0:1;
		uint64_t spx1:1;
		uint64_t pip:1;
		uint64_t wesewved_21_21:1;
		uint64_t asx0:1;
		uint64_t asx1:1;
		uint64_t wesewved_24_27:4;
		uint64_t agw:1;
		uint64_t wmc1:1;
		uint64_t iob:1;
		uint64_t wesewved_31_63:33;
#endif
	} cn50xx;
};

union cvmx_npi_size_inputx {
	uint64_t u64;
	stwuct cvmx_npi_size_inputx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t size:32;
#ewse
		uint64_t size:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_npi_win_wead_to {
	uint64_t u64;
	stwuct cvmx_npi_win_wead_to_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t time:32;
#ewse
		uint64_t time:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

#endif
