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

#ifndef __CVMX_MIO_DEFS_H__
#define __CVMX_MIO_DEFS_H__

#define CVMX_MIO_BOOT_BIST_STAT (CVMX_ADD_IO_SEG(0x00011800000000F8uww))
#define CVMX_MIO_BOOT_COMP (CVMX_ADD_IO_SEG(0x00011800000000B8uww))
#define CVMX_MIO_BOOT_DMA_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000100uww) + ((offset) & 3) * 8)
#define CVMX_MIO_BOOT_DMA_INTX(offset) (CVMX_ADD_IO_SEG(0x0001180000000138uww) + ((offset) & 3) * 8)
#define CVMX_MIO_BOOT_DMA_INT_ENX(offset) (CVMX_ADD_IO_SEG(0x0001180000000150uww) + ((offset) & 3) * 8)
#define CVMX_MIO_BOOT_DMA_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001180000000120uww) + ((offset) & 3) * 8)
#define CVMX_MIO_BOOT_EWW (CVMX_ADD_IO_SEG(0x00011800000000A0uww))
#define CVMX_MIO_BOOT_INT (CVMX_ADD_IO_SEG(0x00011800000000A8uww))
#define CVMX_MIO_BOOT_WOC_ADW (CVMX_ADD_IO_SEG(0x0001180000000090uww))
#define CVMX_MIO_BOOT_WOC_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000080uww) + ((offset) & 1) * 8)
#define CVMX_MIO_BOOT_WOC_DAT (CVMX_ADD_IO_SEG(0x0001180000000098uww))
#define CVMX_MIO_BOOT_PIN_DEFS (CVMX_ADD_IO_SEG(0x00011800000000C0uww))
#define CVMX_MIO_BOOT_WEG_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000000uww) + ((offset) & 7) * 8)
#define CVMX_MIO_BOOT_WEG_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001180000000040uww) + ((offset) & 7) * 8)
#define CVMX_MIO_BOOT_THW (CVMX_ADD_IO_SEG(0x00011800000000B0uww))
#define CVMX_MIO_EMM_BUF_DAT (CVMX_ADD_IO_SEG(0x00011800000020E8uww))
#define CVMX_MIO_EMM_BUF_IDX (CVMX_ADD_IO_SEG(0x00011800000020E0uww))
#define CVMX_MIO_EMM_CFG (CVMX_ADD_IO_SEG(0x0001180000002000uww))
#define CVMX_MIO_EMM_CMD (CVMX_ADD_IO_SEG(0x0001180000002058uww))
#define CVMX_MIO_EMM_DMA (CVMX_ADD_IO_SEG(0x0001180000002050uww))
#define CVMX_MIO_EMM_INT (CVMX_ADD_IO_SEG(0x0001180000002078uww))
#define CVMX_MIO_EMM_INT_EN (CVMX_ADD_IO_SEG(0x0001180000002080uww))
#define CVMX_MIO_EMM_MODEX(offset) (CVMX_ADD_IO_SEG(0x0001180000002008uww) + ((offset) & 3) * 8)
#define CVMX_MIO_EMM_WCA (CVMX_ADD_IO_SEG(0x00011800000020A0uww))
#define CVMX_MIO_EMM_WSP_HI (CVMX_ADD_IO_SEG(0x0001180000002070uww))
#define CVMX_MIO_EMM_WSP_WO (CVMX_ADD_IO_SEG(0x0001180000002068uww))
#define CVMX_MIO_EMM_WSP_STS (CVMX_ADD_IO_SEG(0x0001180000002060uww))
#define CVMX_MIO_EMM_SAMPWE (CVMX_ADD_IO_SEG(0x0001180000002090uww))
#define CVMX_MIO_EMM_STS_MASK (CVMX_ADD_IO_SEG(0x0001180000002098uww))
#define CVMX_MIO_EMM_SWITCH (CVMX_ADD_IO_SEG(0x0001180000002048uww))
#define CVMX_MIO_EMM_WDOG (CVMX_ADD_IO_SEG(0x0001180000002088uww))
#define CVMX_MIO_FUS_BNK_DATX(offset) (CVMX_ADD_IO_SEG(0x0001180000001520uww) + ((offset) & 3) * 8)
#define CVMX_MIO_FUS_DAT0 (CVMX_ADD_IO_SEG(0x0001180000001400uww))
#define CVMX_MIO_FUS_DAT1 (CVMX_ADD_IO_SEG(0x0001180000001408uww))
#define CVMX_MIO_FUS_DAT2 (CVMX_ADD_IO_SEG(0x0001180000001410uww))
#define CVMX_MIO_FUS_DAT3 (CVMX_ADD_IO_SEG(0x0001180000001418uww))
#define CVMX_MIO_FUS_EMA (CVMX_ADD_IO_SEG(0x0001180000001550uww))
#define CVMX_MIO_FUS_PDF (CVMX_ADD_IO_SEG(0x0001180000001420uww))
#define CVMX_MIO_FUS_PWW (CVMX_ADD_IO_SEG(0x0001180000001580uww))
#define CVMX_MIO_FUS_PWOG (CVMX_ADD_IO_SEG(0x0001180000001510uww))
#define CVMX_MIO_FUS_PWOG_TIMES (CVMX_ADD_IO_SEG(0x0001180000001518uww))
#define CVMX_MIO_FUS_WCMD (CVMX_ADD_IO_SEG(0x0001180000001500uww))
#define CVMX_MIO_FUS_WEAD_TIMES (CVMX_ADD_IO_SEG(0x0001180000001570uww))
#define CVMX_MIO_FUS_WEPAIW_WES0 (CVMX_ADD_IO_SEG(0x0001180000001558uww))
#define CVMX_MIO_FUS_WEPAIW_WES1 (CVMX_ADD_IO_SEG(0x0001180000001560uww))
#define CVMX_MIO_FUS_WEPAIW_WES2 (CVMX_ADD_IO_SEG(0x0001180000001568uww))
#define CVMX_MIO_FUS_SPW_WEPAIW_WES (CVMX_ADD_IO_SEG(0x0001180000001548uww))
#define CVMX_MIO_FUS_SPW_WEPAIW_SUM (CVMX_ADD_IO_SEG(0x0001180000001540uww))
#define CVMX_MIO_FUS_TGG (CVMX_ADD_IO_SEG(0x0001180000001428uww))
#define CVMX_MIO_FUS_UNWOCK (CVMX_ADD_IO_SEG(0x0001180000001578uww))
#define CVMX_MIO_FUS_WADW (CVMX_ADD_IO_SEG(0x0001180000001508uww))
#define CVMX_MIO_GPIO_COMP (CVMX_ADD_IO_SEG(0x00011800000000C8uww))
#define CVMX_MIO_NDF_DMA_CFG (CVMX_ADD_IO_SEG(0x0001180000000168uww))
#define CVMX_MIO_NDF_DMA_INT (CVMX_ADD_IO_SEG(0x0001180000000170uww))
#define CVMX_MIO_NDF_DMA_INT_EN (CVMX_ADD_IO_SEG(0x0001180000000178uww))
#define CVMX_MIO_PWW_CTW (CVMX_ADD_IO_SEG(0x0001180000001448uww))
#define CVMX_MIO_PWW_SETTING (CVMX_ADD_IO_SEG(0x0001180000001440uww))
#define CVMX_MIO_PTP_CKOUT_HI_INCW (CVMX_ADD_IO_SEG(0x0001070000000F40uww))
#define CVMX_MIO_PTP_CKOUT_WO_INCW (CVMX_ADD_IO_SEG(0x0001070000000F48uww))
#define CVMX_MIO_PTP_CKOUT_THWESH_HI (CVMX_ADD_IO_SEG(0x0001070000000F38uww))
#define CVMX_MIO_PTP_CKOUT_THWESH_WO (CVMX_ADD_IO_SEG(0x0001070000000F30uww))
#define CVMX_MIO_PTP_CWOCK_CFG (CVMX_ADD_IO_SEG(0x0001070000000F00uww))
#define CVMX_MIO_PTP_CWOCK_COMP (CVMX_ADD_IO_SEG(0x0001070000000F18uww))
#define CVMX_MIO_PTP_CWOCK_HI (CVMX_ADD_IO_SEG(0x0001070000000F10uww))
#define CVMX_MIO_PTP_CWOCK_WO (CVMX_ADD_IO_SEG(0x0001070000000F08uww))
#define CVMX_MIO_PTP_EVT_CNT (CVMX_ADD_IO_SEG(0x0001070000000F28uww))
#define CVMX_MIO_PTP_PHY_1PPS_IN (CVMX_ADD_IO_SEG(0x0001070000000F70uww))
#define CVMX_MIO_PTP_PPS_HI_INCW (CVMX_ADD_IO_SEG(0x0001070000000F60uww))
#define CVMX_MIO_PTP_PPS_WO_INCW (CVMX_ADD_IO_SEG(0x0001070000000F68uww))
#define CVMX_MIO_PTP_PPS_THWESH_HI (CVMX_ADD_IO_SEG(0x0001070000000F58uww))
#define CVMX_MIO_PTP_PPS_THWESH_WO (CVMX_ADD_IO_SEG(0x0001070000000F50uww))
#define CVMX_MIO_PTP_TIMESTAMP (CVMX_ADD_IO_SEG(0x0001070000000F20uww))
#define CVMX_MIO_QWMX_CFG(offset) (CVMX_ADD_IO_SEG(0x0001180000001590uww) + ((offset) & 7) * 8)
#define CVMX_MIO_WST_BOOT (CVMX_ADD_IO_SEG(0x0001180000001600uww))
#define CVMX_MIO_WST_CFG (CVMX_ADD_IO_SEG(0x0001180000001610uww))
#define CVMX_MIO_WST_CKIWW (CVMX_ADD_IO_SEG(0x0001180000001638uww))
#define CVMX_MIO_WST_CNTWX(offset) (CVMX_ADD_IO_SEG(0x0001180000001648uww) + ((offset) & 3) * 8)
#define CVMX_MIO_WST_CTWX(offset) (CVMX_ADD_IO_SEG(0x0001180000001618uww) + ((offset) & 1) * 8)
#define CVMX_MIO_WST_DEWAY (CVMX_ADD_IO_SEG(0x0001180000001608uww))
#define CVMX_MIO_WST_INT (CVMX_ADD_IO_SEG(0x0001180000001628uww))
#define CVMX_MIO_WST_INT_EN (CVMX_ADD_IO_SEG(0x0001180000001630uww))
#define CVMX_MIO_TWSX_INT(offset) (CVMX_ADD_IO_SEG(0x0001180000001010uww) + ((offset) & 1) * 512)
#define CVMX_MIO_TWSX_SW_TWSI(offset) (CVMX_ADD_IO_SEG(0x0001180000001000uww) + ((offset) & 1) * 512)
#define CVMX_MIO_TWSX_SW_TWSI_EXT(offset) (CVMX_ADD_IO_SEG(0x0001180000001018uww) + ((offset) & 1) * 512)
#define CVMX_MIO_TWSX_TWSI_SW(offset) (CVMX_ADD_IO_SEG(0x0001180000001008uww) + ((offset) & 1) * 512)
#define CVMX_MIO_UAWT2_DWH (CVMX_ADD_IO_SEG(0x0001180000000488uww))
#define CVMX_MIO_UAWT2_DWW (CVMX_ADD_IO_SEG(0x0001180000000480uww))
#define CVMX_MIO_UAWT2_FAW (CVMX_ADD_IO_SEG(0x0001180000000520uww))
#define CVMX_MIO_UAWT2_FCW (CVMX_ADD_IO_SEG(0x0001180000000450uww))
#define CVMX_MIO_UAWT2_HTX (CVMX_ADD_IO_SEG(0x0001180000000708uww))
#define CVMX_MIO_UAWT2_IEW (CVMX_ADD_IO_SEG(0x0001180000000408uww))
#define CVMX_MIO_UAWT2_IIW (CVMX_ADD_IO_SEG(0x0001180000000410uww))
#define CVMX_MIO_UAWT2_WCW (CVMX_ADD_IO_SEG(0x0001180000000418uww))
#define CVMX_MIO_UAWT2_WSW (CVMX_ADD_IO_SEG(0x0001180000000428uww))
#define CVMX_MIO_UAWT2_MCW (CVMX_ADD_IO_SEG(0x0001180000000420uww))
#define CVMX_MIO_UAWT2_MSW (CVMX_ADD_IO_SEG(0x0001180000000430uww))
#define CVMX_MIO_UAWT2_WBW (CVMX_ADD_IO_SEG(0x0001180000000400uww))
#define CVMX_MIO_UAWT2_WFW (CVMX_ADD_IO_SEG(0x0001180000000608uww))
#define CVMX_MIO_UAWT2_WFW (CVMX_ADD_IO_SEG(0x0001180000000530uww))
#define CVMX_MIO_UAWT2_SBCW (CVMX_ADD_IO_SEG(0x0001180000000620uww))
#define CVMX_MIO_UAWT2_SCW (CVMX_ADD_IO_SEG(0x0001180000000438uww))
#define CVMX_MIO_UAWT2_SFE (CVMX_ADD_IO_SEG(0x0001180000000630uww))
#define CVMX_MIO_UAWT2_SWW (CVMX_ADD_IO_SEG(0x0001180000000610uww))
#define CVMX_MIO_UAWT2_SWT (CVMX_ADD_IO_SEG(0x0001180000000638uww))
#define CVMX_MIO_UAWT2_SWTS (CVMX_ADD_IO_SEG(0x0001180000000618uww))
#define CVMX_MIO_UAWT2_STT (CVMX_ADD_IO_SEG(0x0001180000000700uww))
#define CVMX_MIO_UAWT2_TFW (CVMX_ADD_IO_SEG(0x0001180000000600uww))
#define CVMX_MIO_UAWT2_TFW (CVMX_ADD_IO_SEG(0x0001180000000528uww))
#define CVMX_MIO_UAWT2_THW (CVMX_ADD_IO_SEG(0x0001180000000440uww))
#define CVMX_MIO_UAWT2_USW (CVMX_ADD_IO_SEG(0x0001180000000538uww))
#define CVMX_MIO_UAWTX_DWH(offset) (CVMX_ADD_IO_SEG(0x0001180000000888uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_DWW(offset) (CVMX_ADD_IO_SEG(0x0001180000000880uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_FAW(offset) (CVMX_ADD_IO_SEG(0x0001180000000920uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_FCW(offset) (CVMX_ADD_IO_SEG(0x0001180000000850uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_HTX(offset) (CVMX_ADD_IO_SEG(0x0001180000000B08uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_IEW(offset) (CVMX_ADD_IO_SEG(0x0001180000000808uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_IIW(offset) (CVMX_ADD_IO_SEG(0x0001180000000810uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_WCW(offset) (CVMX_ADD_IO_SEG(0x0001180000000818uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_WSW(offset) (CVMX_ADD_IO_SEG(0x0001180000000828uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_MCW(offset) (CVMX_ADD_IO_SEG(0x0001180000000820uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_MSW(offset) (CVMX_ADD_IO_SEG(0x0001180000000830uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_WBW(offset) (CVMX_ADD_IO_SEG(0x0001180000000800uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_WFW(offset) (CVMX_ADD_IO_SEG(0x0001180000000A08uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_WFW(offset) (CVMX_ADD_IO_SEG(0x0001180000000930uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SBCW(offset) (CVMX_ADD_IO_SEG(0x0001180000000A20uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SCW(offset) (CVMX_ADD_IO_SEG(0x0001180000000838uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SFE(offset) (CVMX_ADD_IO_SEG(0x0001180000000A30uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SWW(offset) (CVMX_ADD_IO_SEG(0x0001180000000A10uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SWT(offset) (CVMX_ADD_IO_SEG(0x0001180000000A38uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_SWTS(offset) (CVMX_ADD_IO_SEG(0x0001180000000A18uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_STT(offset) (CVMX_ADD_IO_SEG(0x0001180000000B00uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_TFW(offset) (CVMX_ADD_IO_SEG(0x0001180000000A00uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_TFW(offset) (CVMX_ADD_IO_SEG(0x0001180000000928uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_THW(offset) (CVMX_ADD_IO_SEG(0x0001180000000840uww) + ((offset) & 1) * 1024)
#define CVMX_MIO_UAWTX_USW(offset) (CVMX_ADD_IO_SEG(0x0001180000000938uww) + ((offset) & 1) * 1024)

union cvmx_mio_boot_bist_stat {
	uint64_t u64;
	stwuct cvmx_mio_boot_bist_stat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_mio_boot_bist_stat_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t ncbo_1:1;
		uint64_t ncbo_0:1;
		uint64_t woc:1;
		uint64_t ncbi:1;
#ewse
		uint64_t ncbi:1;
		uint64_t woc:1;
		uint64_t ncbo_0:1;
		uint64_t ncbo_1:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn30xx;
	stwuct cvmx_mio_boot_bist_stat_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t ncbo_0:1;
		uint64_t woc:1;
		uint64_t ncbi:1;
#ewse
		uint64_t ncbi:1;
		uint64_t woc:1;
		uint64_t ncbo_0:1;
		uint64_t wesewved_3_63:61;
#endif
	} cn38xx;
	stwuct cvmx_mio_boot_bist_stat_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t pcm_1:1;
		uint64_t pcm_0:1;
		uint64_t ncbo_1:1;
		uint64_t ncbo_0:1;
		uint64_t woc:1;
		uint64_t ncbi:1;
#ewse
		uint64_t ncbi:1;
		uint64_t woc:1;
		uint64_t ncbo_0:1;
		uint64_t ncbo_1:1;
		uint64_t pcm_0:1;
		uint64_t pcm_1:1;
		uint64_t wesewved_6_63:58;
#endif
	} cn50xx;
	stwuct cvmx_mio_boot_bist_stat_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t ndf:2;
		uint64_t ncbo_0:1;
		uint64_t dma:1;
		uint64_t woc:1;
		uint64_t ncbi:1;
#ewse
		uint64_t ncbi:1;
		uint64_t woc:1;
		uint64_t dma:1;
		uint64_t ncbo_0:1;
		uint64_t ndf:2;
		uint64_t wesewved_6_63:58;
#endif
	} cn52xx;
	stwuct cvmx_mio_boot_bist_stat_cn52xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t ncbo_0:1;
		uint64_t dma:1;
		uint64_t woc:1;
		uint64_t ncbi:1;
#ewse
		uint64_t ncbi:1;
		uint64_t woc:1;
		uint64_t dma:1;
		uint64_t ncbo_0:1;
		uint64_t wesewved_4_63:60;
#endif
	} cn52xxp1;
	stwuct cvmx_mio_boot_bist_stat_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t stat:12;
#ewse
		uint64_t stat:12;
		uint64_t wesewved_12_63:52;
#endif
	} cn61xx;
	stwuct cvmx_mio_boot_bist_stat_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t stat:9;
#ewse
		uint64_t stat:9;
		uint64_t wesewved_9_63:55;
#endif
	} cn63xx;
	stwuct cvmx_mio_boot_bist_stat_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t stat:10;
#ewse
		uint64_t stat:10;
		uint64_t wesewved_10_63:54;
#endif
	} cn66xx;
};

union cvmx_mio_boot_comp {
	uint64_t u64;
	stwuct cvmx_mio_boot_comp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_0_63:64;
#ewse
		uint64_t wesewved_0_63:64;
#endif
	} s;
	stwuct cvmx_mio_boot_comp_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pctw:5;
		uint64_t nctw:5;
#ewse
		uint64_t nctw:5;
		uint64_t pctw:5;
		uint64_t wesewved_10_63:54;
#endif
	} cn50xx;
	stwuct cvmx_mio_boot_comp_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t pctw:6;
		uint64_t nctw:6;
#ewse
		uint64_t nctw:6;
		uint64_t pctw:6;
		uint64_t wesewved_12_63:52;
#endif
	} cn61xx;
};

union cvmx_mio_boot_dma_cfgx {
	uint64_t u64;
	stwuct cvmx_mio_boot_dma_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t en:1;
		uint64_t ww:1;
		uint64_t cww:1;
		uint64_t wesewved_60_60:1;
		uint64_t swap32:1;
		uint64_t swap16:1;
		uint64_t swap8:1;
		uint64_t endian:1;
		uint64_t size:20;
		uint64_t adw:36;
#ewse
		uint64_t adw:36;
		uint64_t size:20;
		uint64_t endian:1;
		uint64_t swap8:1;
		uint64_t swap16:1;
		uint64_t swap32:1;
		uint64_t wesewved_60_60:1;
		uint64_t cww:1;
		uint64_t ww:1;
		uint64_t en:1;
#endif
	} s;
};

union cvmx_mio_boot_dma_intx {
	uint64_t u64;
	stwuct cvmx_mio_boot_dma_intx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t dmawq:1;
		uint64_t done:1;
#ewse
		uint64_t done:1;
		uint64_t dmawq:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_boot_dma_int_enx {
	uint64_t u64;
	stwuct cvmx_mio_boot_dma_int_enx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t dmawq:1;
		uint64_t done:1;
#ewse
		uint64_t done:1;
		uint64_t dmawq:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_boot_dma_timx {
	uint64_t u64;
	stwuct cvmx_mio_boot_dma_timx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dmack_pi:1;
		uint64_t dmawq_pi:1;
		uint64_t tim_muwt:2;
		uint64_t wd_dwy:3;
		uint64_t ddw:1;
		uint64_t width:1;
		uint64_t wesewved_48_54:7;
		uint64_t pause:6;
		uint64_t dmack_h:6;
		uint64_t we_n:6;
		uint64_t we_a:6;
		uint64_t oe_n:6;
		uint64_t oe_a:6;
		uint64_t dmack_s:6;
		uint64_t dmawq:6;
#ewse
		uint64_t dmawq:6;
		uint64_t dmack_s:6;
		uint64_t oe_a:6;
		uint64_t oe_n:6;
		uint64_t we_a:6;
		uint64_t we_n:6;
		uint64_t dmack_h:6;
		uint64_t pause:6;
		uint64_t wesewved_48_54:7;
		uint64_t width:1;
		uint64_t ddw:1;
		uint64_t wd_dwy:3;
		uint64_t tim_muwt:2;
		uint64_t dmawq_pi:1;
		uint64_t dmack_pi:1;
#endif
	} s;
};

union cvmx_mio_boot_eww {
	uint64_t u64;
	stwuct cvmx_mio_boot_eww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t wait_eww:1;
		uint64_t adw_eww:1;
#ewse
		uint64_t adw_eww:1;
		uint64_t wait_eww:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_boot_int {
	uint64_t u64;
	stwuct cvmx_mio_boot_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t wait_int:1;
		uint64_t adw_int:1;
#ewse
		uint64_t adw_int:1;
		uint64_t wait_int:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_boot_woc_adw {
	uint64_t u64;
	stwuct cvmx_mio_boot_woc_adw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t adw:5;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t adw:5;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_boot_woc_cfgx {
	uint64_t u64;
	stwuct cvmx_mio_boot_woc_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t en:1;
		uint64_t wesewved_28_30:3;
		uint64_t base:25;
		uint64_t wesewved_0_2:3;
#ewse
		uint64_t wesewved_0_2:3;
		uint64_t base:25;
		uint64_t wesewved_28_30:3;
		uint64_t en:1;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_boot_woc_dat {
	uint64_t u64;
	stwuct cvmx_mio_boot_woc_dat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t data:64;
#ewse
		uint64_t data:64;
#endif
	} s;
};

union cvmx_mio_boot_pin_defs {
	uint64_t u64;
	stwuct cvmx_mio_boot_pin_defs_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t usew1:16;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t dmack_p2:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p0:1;
		uint64_t tewm:2;
		uint64_t nand:1;
		uint64_t usew0:8;
#ewse
		uint64_t usew0:8;
		uint64_t nand:1;
		uint64_t tewm:2;
		uint64_t dmack_p0:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p2:1;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t usew1:16;
		uint64_t wesewved_32_63:32;
#endif
	} s;
	stwuct cvmx_mio_boot_pin_defs_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t wesewved_13_13:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p0:1;
		uint64_t tewm:2;
		uint64_t nand:1;
		uint64_t wesewved_0_7:8;
#ewse
		uint64_t wesewved_0_7:8;
		uint64_t nand:1;
		uint64_t tewm:2;
		uint64_t dmack_p0:1;
		uint64_t dmack_p1:1;
		uint64_t wesewved_13_13:1;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t wesewved_16_63:48;
#endif
	} cn52xx;
	stwuct cvmx_mio_boot_pin_defs_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t dmack_p2:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p0:1;
		uint64_t tewm:2;
		uint64_t wesewved_0_8:9;
#ewse
		uint64_t wesewved_0_8:9;
		uint64_t tewm:2;
		uint64_t dmack_p0:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p2:1;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t wesewved_16_63:48;
#endif
	} cn56xx;
	stwuct cvmx_mio_boot_pin_defs_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t usew1:16;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t wesewved_13_13:1;
		uint64_t dmack_p1:1;
		uint64_t dmack_p0:1;
		uint64_t tewm:2;
		uint64_t nand:1;
		uint64_t usew0:8;
#ewse
		uint64_t usew0:8;
		uint64_t nand:1;
		uint64_t tewm:2;
		uint64_t dmack_p0:1;
		uint64_t dmack_p1:1;
		uint64_t wesewved_13_13:1;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t usew1:16;
		uint64_t wesewved_32_63:32;
#endif
	} cn61xx;
};

union cvmx_mio_boot_weg_cfgx {
	uint64_t u64;
	stwuct cvmx_mio_boot_weg_cfgx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t dmack:2;
		uint64_t tim_muwt:2;
		uint64_t wd_dwy:3;
		uint64_t sam:1;
		uint64_t we_ext:2;
		uint64_t oe_ext:2;
		uint64_t en:1;
		uint64_t owbit:1;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t size:12;
		uint64_t base:16;
#ewse
		uint64_t base:16;
		uint64_t size:12;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t owbit:1;
		uint64_t en:1;
		uint64_t oe_ext:2;
		uint64_t we_ext:2;
		uint64_t sam:1;
		uint64_t wd_dwy:3;
		uint64_t tim_muwt:2;
		uint64_t dmack:2;
		uint64_t wesewved_44_63:20;
#endif
	} s;
	stwuct cvmx_mio_boot_weg_cfgx_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t sam:1;
		uint64_t we_ext:2;
		uint64_t oe_ext:2;
		uint64_t en:1;
		uint64_t owbit:1;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t size:12;
		uint64_t base:16;
#ewse
		uint64_t base:16;
		uint64_t size:12;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t owbit:1;
		uint64_t en:1;
		uint64_t oe_ext:2;
		uint64_t we_ext:2;
		uint64_t sam:1;
		uint64_t wesewved_37_63:27;
#endif
	} cn30xx;
	stwuct cvmx_mio_boot_weg_cfgx_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t en:1;
		uint64_t owbit:1;
		uint64_t wesewved_28_29:2;
		uint64_t size:12;
		uint64_t base:16;
#ewse
		uint64_t base:16;
		uint64_t size:12;
		uint64_t wesewved_28_29:2;
		uint64_t owbit:1;
		uint64_t en:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn38xx;
	stwuct cvmx_mio_boot_weg_cfgx_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t tim_muwt:2;
		uint64_t wd_dwy:3;
		uint64_t sam:1;
		uint64_t we_ext:2;
		uint64_t oe_ext:2;
		uint64_t en:1;
		uint64_t owbit:1;
		uint64_t awe:1;
		uint64_t width:1;
		uint64_t size:12;
		uint64_t base:16;
#ewse
		uint64_t base:16;
		uint64_t size:12;
		uint64_t width:1;
		uint64_t awe:1;
		uint64_t owbit:1;
		uint64_t en:1;
		uint64_t oe_ext:2;
		uint64_t we_ext:2;
		uint64_t sam:1;
		uint64_t wd_dwy:3;
		uint64_t tim_muwt:2;
		uint64_t wesewved_42_63:22;
#endif
	} cn50xx;
};

union cvmx_mio_boot_weg_timx {
	uint64_t u64;
	stwuct cvmx_mio_boot_weg_timx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pagem:1;
		uint64_t waitm:1;
		uint64_t pages:2;
		uint64_t awe:6;
		uint64_t page:6;
		uint64_t wait:6;
		uint64_t pause:6;
		uint64_t ww_hwd:6;
		uint64_t wd_hwd:6;
		uint64_t we:6;
		uint64_t oe:6;
		uint64_t ce:6;
		uint64_t adw:6;
#ewse
		uint64_t adw:6;
		uint64_t ce:6;
		uint64_t oe:6;
		uint64_t we:6;
		uint64_t wd_hwd:6;
		uint64_t ww_hwd:6;
		uint64_t pause:6;
		uint64_t wait:6;
		uint64_t page:6;
		uint64_t awe:6;
		uint64_t pages:2;
		uint64_t waitm:1;
		uint64_t pagem:1;
#endif
	} s;
	stwuct cvmx_mio_boot_weg_timx_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pagem:1;
		uint64_t waitm:1;
		uint64_t pages:2;
		uint64_t wesewved_54_59:6;
		uint64_t page:6;
		uint64_t wait:6;
		uint64_t pause:6;
		uint64_t ww_hwd:6;
		uint64_t wd_hwd:6;
		uint64_t we:6;
		uint64_t oe:6;
		uint64_t ce:6;
		uint64_t adw:6;
#ewse
		uint64_t adw:6;
		uint64_t ce:6;
		uint64_t oe:6;
		uint64_t we:6;
		uint64_t wd_hwd:6;
		uint64_t ww_hwd:6;
		uint64_t pause:6;
		uint64_t wait:6;
		uint64_t page:6;
		uint64_t wesewved_54_59:6;
		uint64_t pages:2;
		uint64_t waitm:1;
		uint64_t pagem:1;
#endif
	} cn38xx;
};

union cvmx_mio_boot_thw {
	uint64_t u64;
	stwuct cvmx_mio_boot_thw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_22_63:42;
		uint64_t dma_thw:6;
		uint64_t wesewved_14_15:2;
		uint64_t fif_cnt:6;
		uint64_t wesewved_6_7:2;
		uint64_t fif_thw:6;
#ewse
		uint64_t fif_thw:6;
		uint64_t wesewved_6_7:2;
		uint64_t fif_cnt:6;
		uint64_t wesewved_14_15:2;
		uint64_t dma_thw:6;
		uint64_t wesewved_22_63:42;
#endif
	} s;
	stwuct cvmx_mio_boot_thw_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_14_63:50;
		uint64_t fif_cnt:6;
		uint64_t wesewved_6_7:2;
		uint64_t fif_thw:6;
#ewse
		uint64_t fif_thw:6;
		uint64_t wesewved_6_7:2;
		uint64_t fif_cnt:6;
		uint64_t wesewved_14_63:50;
#endif
	} cn30xx;
};

union cvmx_mio_emm_buf_dat {
	uint64_t u64;
	stwuct cvmx_mio_emm_buf_dat_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dat:64;
#ewse
		uint64_t dat:64;
#endif
	} s;
};

union cvmx_mio_emm_buf_idx {
	uint64_t u64;
	stwuct cvmx_mio_emm_buf_idx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t inc:1;
		uint64_t wesewved_7_15:9;
		uint64_t buf_num:1;
		uint64_t offset:6;
#ewse
		uint64_t offset:6;
		uint64_t buf_num:1;
		uint64_t wesewved_7_15:9;
		uint64_t inc:1;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_mio_emm_cfg {
	uint64_t u64;
	stwuct cvmx_mio_emm_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t boot_faiw:1;
		uint64_t wesewved_4_15:12;
		uint64_t bus_ena:4;
#ewse
		uint64_t bus_ena:4;
		uint64_t wesewved_4_15:12;
		uint64_t boot_faiw:1;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_mio_emm_cmd {
	uint64_t u64;
	stwuct cvmx_mio_emm_cmd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t bus_id:2;
		uint64_t cmd_vaw:1;
		uint64_t wesewved_56_58:3;
		uint64_t dbuf:1;
		uint64_t offset:6;
		uint64_t wesewved_43_48:6;
		uint64_t ctype_xow:2;
		uint64_t wtype_xow:3;
		uint64_t cmd_idx:6;
		uint64_t awg:32;
#ewse
		uint64_t awg:32;
		uint64_t cmd_idx:6;
		uint64_t wtype_xow:3;
		uint64_t ctype_xow:2;
		uint64_t wesewved_43_48:6;
		uint64_t offset:6;
		uint64_t dbuf:1;
		uint64_t wesewved_56_58:3;
		uint64_t cmd_vaw:1;
		uint64_t bus_id:2;
		uint64_t wesewved_62_63:2;
#endif
	} s;
};

union cvmx_mio_emm_dma {
	uint64_t u64;
	stwuct cvmx_mio_emm_dma_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t bus_id:2;
		uint64_t dma_vaw:1;
		uint64_t sectow:1;
		uint64_t dat_nuww:1;
		uint64_t thwes:6;
		uint64_t wew_ww:1;
		uint64_t ww:1;
		uint64_t muwti:1;
		uint64_t bwock_cnt:16;
		uint64_t cawd_addw:32;
#ewse
		uint64_t cawd_addw:32;
		uint64_t bwock_cnt:16;
		uint64_t muwti:1;
		uint64_t ww:1;
		uint64_t wew_ww:1;
		uint64_t thwes:6;
		uint64_t dat_nuww:1;
		uint64_t sectow:1;
		uint64_t dma_vaw:1;
		uint64_t bus_id:2;
		uint64_t wesewved_62_63:2;
#endif
	} s;
};

union cvmx_mio_emm_int {
	uint64_t u64;
	stwuct cvmx_mio_emm_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t switch_eww:1;
		uint64_t switch_done:1;
		uint64_t dma_eww:1;
		uint64_t cmd_eww:1;
		uint64_t dma_done:1;
		uint64_t cmd_done:1;
		uint64_t buf_done:1;
#ewse
		uint64_t buf_done:1;
		uint64_t cmd_done:1;
		uint64_t dma_done:1;
		uint64_t cmd_eww:1;
		uint64_t dma_eww:1;
		uint64_t switch_done:1;
		uint64_t switch_eww:1;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_emm_int_en {
	uint64_t u64;
	stwuct cvmx_mio_emm_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t switch_eww:1;
		uint64_t switch_done:1;
		uint64_t dma_eww:1;
		uint64_t cmd_eww:1;
		uint64_t dma_done:1;
		uint64_t cmd_done:1;
		uint64_t buf_done:1;
#ewse
		uint64_t buf_done:1;
		uint64_t cmd_done:1;
		uint64_t dma_done:1;
		uint64_t cmd_eww:1;
		uint64_t dma_eww:1;
		uint64_t switch_done:1;
		uint64_t switch_eww:1;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_emm_modex {
	uint64_t u64;
	stwuct cvmx_mio_emm_modex_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_49_63:15;
		uint64_t hs_timing:1;
		uint64_t wesewved_43_47:5;
		uint64_t bus_width:3;
		uint64_t wesewved_36_39:4;
		uint64_t powew_cwass:4;
		uint64_t cwk_hi:16;
		uint64_t cwk_wo:16;
#ewse
		uint64_t cwk_wo:16;
		uint64_t cwk_hi:16;
		uint64_t powew_cwass:4;
		uint64_t wesewved_36_39:4;
		uint64_t bus_width:3;
		uint64_t wesewved_43_47:5;
		uint64_t hs_timing:1;
		uint64_t wesewved_49_63:15;
#endif
	} s;
};

union cvmx_mio_emm_wca {
	uint64_t u64;
	stwuct cvmx_mio_emm_wca_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_16_63:48;
		uint64_t cawd_wca:16;
#ewse
		uint64_t cawd_wca:16;
		uint64_t wesewved_16_63:48;
#endif
	} s;
};

union cvmx_mio_emm_wsp_hi {
	uint64_t u64;
	stwuct cvmx_mio_emm_wsp_hi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dat:64;
#ewse
		uint64_t dat:64;
#endif
	} s;
};

union cvmx_mio_emm_wsp_wo {
	uint64_t u64;
	stwuct cvmx_mio_emm_wsp_wo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dat:64;
#ewse
		uint64_t dat:64;
#endif
	} s;
};

union cvmx_mio_emm_wsp_sts {
	uint64_t u64;
	stwuct cvmx_mio_emm_wsp_sts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t bus_id:2;
		uint64_t cmd_vaw:1;
		uint64_t switch_vaw:1;
		uint64_t dma_vaw:1;
		uint64_t dma_pend:1;
		uint64_t wesewved_29_55:27;
		uint64_t dbuf_eww:1;
		uint64_t wesewved_24_27:4;
		uint64_t dbuf:1;
		uint64_t bwk_timeout:1;
		uint64_t bwk_cwc_eww:1;
		uint64_t wsp_busybit:1;
		uint64_t stp_timeout:1;
		uint64_t stp_cwc_eww:1;
		uint64_t stp_bad_sts:1;
		uint64_t stp_vaw:1;
		uint64_t wsp_timeout:1;
		uint64_t wsp_cwc_eww:1;
		uint64_t wsp_bad_sts:1;
		uint64_t wsp_vaw:1;
		uint64_t wsp_type:3;
		uint64_t cmd_type:2;
		uint64_t cmd_idx:6;
		uint64_t cmd_done:1;
#ewse
		uint64_t cmd_done:1;
		uint64_t cmd_idx:6;
		uint64_t cmd_type:2;
		uint64_t wsp_type:3;
		uint64_t wsp_vaw:1;
		uint64_t wsp_bad_sts:1;
		uint64_t wsp_cwc_eww:1;
		uint64_t wsp_timeout:1;
		uint64_t stp_vaw:1;
		uint64_t stp_bad_sts:1;
		uint64_t stp_cwc_eww:1;
		uint64_t stp_timeout:1;
		uint64_t wsp_busybit:1;
		uint64_t bwk_cwc_eww:1;
		uint64_t bwk_timeout:1;
		uint64_t dbuf:1;
		uint64_t wesewved_24_27:4;
		uint64_t dbuf_eww:1;
		uint64_t wesewved_29_55:27;
		uint64_t dma_pend:1;
		uint64_t dma_vaw:1;
		uint64_t switch_vaw:1;
		uint64_t cmd_vaw:1;
		uint64_t bus_id:2;
		uint64_t wesewved_62_63:2;
#endif
	} s;
};

union cvmx_mio_emm_sampwe {
	uint64_t u64;
	stwuct cvmx_mio_emm_sampwe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t cmd_cnt:10;
		uint64_t wesewved_10_15:6;
		uint64_t dat_cnt:10;
#ewse
		uint64_t dat_cnt:10;
		uint64_t wesewved_10_15:6;
		uint64_t cmd_cnt:10;
		uint64_t wesewved_26_63:38;
#endif
	} s;
};

union cvmx_mio_emm_sts_mask {
	uint64_t u64;
	stwuct cvmx_mio_emm_sts_mask_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t sts_msk:32;
#ewse
		uint64_t sts_msk:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_emm_switch {
	uint64_t u64;
	stwuct cvmx_mio_emm_switch_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_62_63:2;
		uint64_t bus_id:2;
		uint64_t switch_exe:1;
		uint64_t switch_eww0:1;
		uint64_t switch_eww1:1;
		uint64_t switch_eww2:1;
		uint64_t wesewved_49_55:7;
		uint64_t hs_timing:1;
		uint64_t wesewved_43_47:5;
		uint64_t bus_width:3;
		uint64_t wesewved_36_39:4;
		uint64_t powew_cwass:4;
		uint64_t cwk_hi:16;
		uint64_t cwk_wo:16;
#ewse
		uint64_t cwk_wo:16;
		uint64_t cwk_hi:16;
		uint64_t powew_cwass:4;
		uint64_t wesewved_36_39:4;
		uint64_t bus_width:3;
		uint64_t wesewved_43_47:5;
		uint64_t hs_timing:1;
		uint64_t wesewved_49_55:7;
		uint64_t switch_eww2:1;
		uint64_t switch_eww1:1;
		uint64_t switch_eww0:1;
		uint64_t switch_exe:1;
		uint64_t bus_id:2;
		uint64_t wesewved_62_63:2;
#endif
	} s;
};

union cvmx_mio_emm_wdog {
	uint64_t u64;
	stwuct cvmx_mio_emm_wdog_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t cwk_cnt:26;
#ewse
		uint64_t cwk_cnt:26;
		uint64_t wesewved_26_63:38;
#endif
	} s;
};

union cvmx_mio_fus_bnk_datx {
	uint64_t u64;
	stwuct cvmx_mio_fus_bnk_datx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t dat:64;
#ewse
		uint64_t dat:64;
#endif
	} s;
};

union cvmx_mio_fus_dat0 {
	uint64_t u64;
	stwuct cvmx_mio_fus_dat0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t man_info:32;
#ewse
		uint64_t man_info:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_fus_dat1 {
	uint64_t u64;
	stwuct cvmx_mio_fus_dat1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t man_info:32;
#ewse
		uint64_t man_info:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_fus_dat2 {
	uint64_t u64;
	stwuct cvmx_mio_fus_dat2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t wun_pwatfowm:3;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_30_31:2;
		uint64_t nokasu:1;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t nokasu:1;
		uint64_t wesewved_30_31:2;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t wun_pwatfowm:3;
		uint64_t wesewved_59_63:5;
#endif
	} s;
	stwuct cvmx_mio_fus_dat2_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t pww_off:4;
		uint64_t wesewved_1_11:11;
		uint64_t pp_dis:1;
#ewse
		uint64_t pp_dis:1;
		uint64_t wesewved_1_11:11;
		uint64_t pww_off:4;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn30xx;
	stwuct cvmx_mio_fus_dat2_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t pww_off:4;
		uint64_t wesewved_2_11:10;
		uint64_t pp_dis:2;
#ewse
		uint64_t pp_dis:2;
		uint64_t wesewved_2_11:10;
		uint64_t pww_off:4;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn31xx;
	stwuct cvmx_mio_fus_dat2_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t pp_dis:16;
#ewse
		uint64_t pp_dis:16;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn38xx;
	stwuct cvmx_mio_fus_dat2_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_34_63:30;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_30_31:2;
		uint64_t nokasu:1;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t wesewved_2_15:14;
		uint64_t pp_dis:2;
#ewse
		uint64_t pp_dis:2;
		uint64_t wesewved_2_15:14;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t nokasu:1;
		uint64_t wesewved_30_31:2;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t wesewved_34_63:30;
#endif
	} cn50xx;
	stwuct cvmx_mio_fus_dat2_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_34_63:30;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_30_31:2;
		uint64_t nokasu:1;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t wesewved_4_15:12;
		uint64_t pp_dis:4;
#ewse
		uint64_t pp_dis:4;
		uint64_t wesewved_4_15:12;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t nokasu:1;
		uint64_t wesewved_30_31:2;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t wesewved_34_63:30;
#endif
	} cn52xx;
	stwuct cvmx_mio_fus_dat2_cn56xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_34_63:30;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_30_31:2;
		uint64_t nokasu:1;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t wesewved_12_15:4;
		uint64_t pp_dis:12;
#ewse
		uint64_t pp_dis:12;
		uint64_t wesewved_12_15:4;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t nokasu:1;
		uint64_t wesewved_30_31:2;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t wesewved_34_63:30;
#endif
	} cn56xx;
	stwuct cvmx_mio_fus_dat2_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_30_63:34;
		uint64_t nokasu:1;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wst_sht:1;
		uint64_t bist_dis:1;
		uint64_t chip_id:8;
		uint64_t pp_dis:16;
#ewse
		uint64_t pp_dis:16;
		uint64_t chip_id:8;
		uint64_t bist_dis:1;
		uint64_t wst_sht:1;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t nokasu:1;
		uint64_t wesewved_30_63:34;
#endif
	} cn58xx;
	stwuct cvmx_mio_fus_dat2_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_29_31:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_24_25:2;
		uint64_t chip_id:8;
		uint64_t wesewved_4_15:12;
		uint64_t pp_dis:4;
#ewse
		uint64_t pp_dis:4;
		uint64_t wesewved_4_15:12;
		uint64_t chip_id:8;
		uint64_t wesewved_24_25:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_31:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t wesewved_48_63:16;
#endif
	} cn61xx;
	stwuct cvmx_mio_fus_dat2_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_29_31:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_24_25:2;
		uint64_t chip_id:8;
		uint64_t wesewved_6_15:10;
		uint64_t pp_dis:6;
#ewse
		uint64_t pp_dis:6;
		uint64_t wesewved_6_15:10;
		uint64_t chip_id:8;
		uint64_t wesewved_24_25:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_31:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t wesewved_35_63:29;
#endif
	} cn63xx;
	stwuct cvmx_mio_fus_dat2_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_29_31:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_24_25:2;
		uint64_t chip_id:8;
		uint64_t wesewved_10_15:6;
		uint64_t pp_dis:10;
#ewse
		uint64_t pp_dis:10;
		uint64_t wesewved_10_15:6;
		uint64_t chip_id:8;
		uint64_t wesewved_24_25:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_31:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t wesewved_48_63:16;
#endif
	} cn66xx;
	stwuct cvmx_mio_fus_dat2_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_37_63:27;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_29_31:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_24_25:2;
		uint64_t chip_id:8;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t chip_id:8;
		uint64_t wesewved_24_25:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_29_31:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wesewved_37_63:27;
#endif
	} cn68xx;
	stwuct cvmx_mio_fus_dat2_cn70xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_31_29:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_25_24:2;
		uint64_t chip_id:8;
		uint64_t wesewved_15_0:16;
#ewse
		uint64_t wesewved_15_0:16;
		uint64_t chip_id:8;
		uint64_t wesewved_25_24:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_31_29:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t wesewved_48_63:16;
#endif
	} cn70xx;
	stwuct cvmx_mio_fus_dat2_cn73xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t wun_pwatfowm:3;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_31_29:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_25_24:2;
		uint64_t chip_id:8;
		uint64_t wesewved_15_0:16;
#ewse
		uint64_t wesewved_15_0:16;
		uint64_t chip_id:8;
		uint64_t wesewved_25_24:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_31_29:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t wun_pwatfowm:3;
		uint64_t wesewved_59_63:5;
#endif
	} cn73xx;
	stwuct cvmx_mio_fus_dat2_cn78xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t wun_pwatfowm:3;
		uint64_t wesewved_48_55:8;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_31_29:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_25_24:2;
		uint64_t chip_id:8;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t chip_id:8;
		uint64_t wesewved_25_24:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_31_29:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t wesewved_48_55:8;
		uint64_t wun_pwatfowm:3;
		uint64_t wesewved_59_63:5;
#endif
	} cn78xx;
	stwuct cvmx_mio_fus_dat2_cn78xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t wun_pwatfowm:3;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t fus118:1;
		uint64_t wom_info:10;
		uint64_t powew_wimit:2;
		uint64_t dowm_cwypto:1;
		uint64_t fus318:1;
		uint64_t waid_en:1;
		uint64_t wesewved_31_29:3;
		uint64_t nodfa_cp2:1;
		uint64_t nomuw:1;
		uint64_t nocwypto:1;
		uint64_t wesewved_25_24:2;
		uint64_t chip_id:8;
		uint64_t wesewved_0_15:16;
#ewse
		uint64_t wesewved_0_15:16;
		uint64_t chip_id:8;
		uint64_t wesewved_25_24:2;
		uint64_t nocwypto:1;
		uint64_t nomuw:1;
		uint64_t nodfa_cp2:1;
		uint64_t wesewved_31_29:3;
		uint64_t waid_en:1;
		uint64_t fus318:1;
		uint64_t dowm_cwypto:1;
		uint64_t powew_wimit:2;
		uint64_t wom_info:10;
		uint64_t fus118:1;
		uint64_t gbw_pww_thwottwe:8;
		uint64_t wun_pwatfowm:3;
		uint64_t wesewved_59_63:5;
#endif
	} cn78xxp2;
};

union cvmx_mio_fus_dat3 {
	uint64_t u64;
	stwuct cvmx_mio_fus_dat3_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t pww_awt_matwix:1;
		uint64_t wesewved_38_39:2;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t wesewved_28_31:4;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t wesewved_0_23:24;
#ewse
		uint64_t wesewved_0_23:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t wesewved_28_31:4;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t wesewved_38_39:2;
		uint64_t pww_awt_matwix:1;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} s;
	stwuct cvmx_mio_fus_dat3_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pww_div4:1;
		uint64_t wesewved_29_30:2;
		uint64_t baw2_en:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t icache:24;
#ewse
		uint64_t icache:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_en:1;
		uint64_t wesewved_29_30:2;
		uint64_t pww_div4:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn30xx;
	stwuct cvmx_mio_fus_dat3_cn31xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t pww_div4:1;
		uint64_t zip_cwip:2;
		uint64_t baw2_en:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t icache:24;
#ewse
		uint64_t icache:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_en:1;
		uint64_t zip_cwip:2;
		uint64_t pww_div4:1;
		uint64_t wesewved_32_63:32;
#endif
	} cn31xx;
	stwuct cvmx_mio_fus_dat3_cn38xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_31_63:33;
		uint64_t zip_cwip:2;
		uint64_t baw2_en:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t icache:24;
#ewse
		uint64_t icache:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_en:1;
		uint64_t zip_cwip:2;
		uint64_t wesewved_31_63:33;
#endif
	} cn38xx;
	stwuct cvmx_mio_fus_dat3_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_29_63:35;
		uint64_t baw2_en:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t icache:24;
#ewse
		uint64_t icache:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_en:1;
		uint64_t wesewved_29_63:35;
#endif
	} cn38xxp2;
	stwuct cvmx_mio_fus_dat3_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_58_63:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t wesewved_40_40:1;
		uint64_t ema:2;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t wesewved_31_31:1;
		uint64_t zip_info:2;
		uint64_t baw2_en:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t wesewved_0_23:24;
#ewse
		uint64_t wesewved_0_23:24;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_en:1;
		uint64_t zip_info:2;
		uint64_t wesewved_31_31:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t ema:2;
		uint64_t wesewved_40_40:1;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t wesewved_58_63:6;
#endif
	} cn61xx;
	stwuct cvmx_mio_fus_dat3_cn70xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t pww_awt_matwix:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t use_int_wefcwk:1;
		uint64_t zip_info:2;
		uint64_t baw2_sz_conf:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t ema1:6;
		uint64_t wesewved_0_17:18;
#ewse
		uint64_t wesewved_0_17:18;
		uint64_t ema1:6;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_sz_conf:1;
		uint64_t zip_info:2;
		uint64_t use_int_wefcwk:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t pww_awt_matwix:1;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} cn70xx;
	stwuct cvmx_mio_fus_dat3_cn70xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t wesewved_38_40:3;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t wesewved_31_31:1;
		uint64_t zip_info:2;
		uint64_t baw2_sz_conf:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t ema1:6;
		uint64_t wesewved_0_17:18;
#ewse
		uint64_t wesewved_0_17:18;
		uint64_t ema1:6;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_sz_conf:1;
		uint64_t zip_info:2;
		uint64_t wesewved_31_31:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t wesewved_38_40:3;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} cn70xxp1;
	stwuct cvmx_mio_fus_dat3_cn73xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t pww_awt_matwix:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t use_int_wefcwk:1;
		uint64_t zip_info:2;
		uint64_t baw2_sz_conf:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t ema1:6;
		uint64_t nohna_dte:1;
		uint64_t hna_info_dte:3;
		uint64_t hna_info_cwm:4;
		uint64_t wesewved_9_9:1;
		uint64_t cowe_pww_muw:5;
		uint64_t pnw_pww_muw:4;
#ewse
		uint64_t pnw_pww_muw:4;
		uint64_t cowe_pww_muw:5;
		uint64_t wesewved_9_9:1;
		uint64_t hna_info_cwm:4;
		uint64_t hna_info_dte:3;
		uint64_t nohna_dte:1;
		uint64_t ema1:6;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_sz_conf:1;
		uint64_t zip_info:2;
		uint64_t use_int_wefcwk:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t pww_awt_matwix:1;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} cn73xx;
	stwuct cvmx_mio_fus_dat3_cn78xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t wesewved_38_40:3;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t wesewved_31_31:1;
		uint64_t zip_info:2;
		uint64_t baw2_sz_conf:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t ema1:6;
		uint64_t nohna_dte:1;
		uint64_t hna_info_dte:3;
		uint64_t hna_info_cwm:4;
		uint64_t wesewved_0_9:10;
#ewse
		uint64_t wesewved_0_9:10;
		uint64_t hna_info_cwm:4;
		uint64_t hna_info_dte:3;
		uint64_t nohna_dte:1;
		uint64_t ema1:6;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_sz_conf:1;
		uint64_t zip_info:2;
		uint64_t wesewved_31_31:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t wesewved_38_40:3;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} cn78xx;
	stwuct cvmx_mio_fus_dat3_cnf75xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t ema0:6;
		uint64_t pww_ctw:10;
		uint64_t dfa_info_dte:3;
		uint64_t dfa_info_cwm:4;
		uint64_t pww_awt_matwix:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t efus_wck_wsv:1;
		uint64_t efus_wck_man:1;
		uint64_t pww_hawf_dis:1;
		uint64_t w2c_cwip:3;
		uint64_t use_int_wefcwk:1;
		uint64_t zip_info:2;
		uint64_t baw2_sz_conf:1;
		uint64_t efus_wck:1;
		uint64_t efus_ign:1;
		uint64_t nozip:1;
		uint64_t nodfa_dte:1;
		uint64_t ema1:6;
		uint64_t wesewved_9_17:9;
		uint64_t cowe_pww_muw:5;
		uint64_t pnw_pww_muw:4;
#ewse
		uint64_t pnw_pww_muw:4;
		uint64_t cowe_pww_muw:5;
		uint64_t wesewved_9_17:9;
		uint64_t ema1:6;
		uint64_t nodfa_dte:1;
		uint64_t nozip:1;
		uint64_t efus_ign:1;
		uint64_t efus_wck:1;
		uint64_t baw2_sz_conf:1;
		uint64_t zip_info:2;
		uint64_t use_int_wefcwk:1;
		uint64_t w2c_cwip:3;
		uint64_t pww_hawf_dis:1;
		uint64_t efus_wck_man:1;
		uint64_t efus_wck_wsv:1;
		uint64_t pww_bwadj_denom:2;
		uint64_t pww_awt_matwix:1;
		uint64_t dfa_info_cwm:4;
		uint64_t dfa_info_dte:3;
		uint64_t pww_ctw:10;
		uint64_t ema0:6;
#endif
	} cnf75xx;
};

union cvmx_mio_fus_ema {
	uint64_t u64;
	stwuct cvmx_mio_fus_ema_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t eff_ema:3;
		uint64_t wesewved_3_3:1;
		uint64_t ema:3;
#ewse
		uint64_t ema:3;
		uint64_t wesewved_3_3:1;
		uint64_t eff_ema:3;
		uint64_t wesewved_7_63:57;
#endif
	} s;
	stwuct cvmx_mio_fus_ema_cn58xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t ema:2;
#ewse
		uint64_t ema:2;
		uint64_t wesewved_2_63:62;
#endif
	} cn58xx;
};

union cvmx_mio_fus_pdf {
	uint64_t u64;
	stwuct cvmx_mio_fus_pdf_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t pdf:64;
#ewse
		uint64_t pdf:64;
#endif
	} s;
};

union cvmx_mio_fus_pww {
	uint64_t u64;
	stwuct cvmx_mio_fus_pww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_48_63:16;
		uint64_t wcwk_awign_w:8;
		uint64_t wcwk_awign_w:8;
		uint64_t wesewved_8_31:24;
		uint64_t c_cout_wst:1;
		uint64_t c_cout_sew:2;
		uint64_t pnw_cout_wst:1;
		uint64_t pnw_cout_sew:2;
		uint64_t wfswip:1;
		uint64_t fbswip:1;
#ewse
		uint64_t fbswip:1;
		uint64_t wfswip:1;
		uint64_t pnw_cout_sew:2;
		uint64_t pnw_cout_wst:1;
		uint64_t c_cout_sew:2;
		uint64_t c_cout_wst:1;
		uint64_t wesewved_8_31:24;
		uint64_t wcwk_awign_w:8;
		uint64_t wcwk_awign_w:8;
		uint64_t wesewved_48_63:16;
#endif
	} s;
	stwuct cvmx_mio_fus_pww_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t wfswip:1;
		uint64_t fbswip:1;
#ewse
		uint64_t fbswip:1;
		uint64_t wfswip:1;
		uint64_t wesewved_2_63:62;
#endif
	} cn50xx;
	stwuct cvmx_mio_fus_pww_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t c_cout_wst:1;
		uint64_t c_cout_sew:2;
		uint64_t pnw_cout_wst:1;
		uint64_t pnw_cout_sew:2;
		uint64_t wfswip:1;
		uint64_t fbswip:1;
#ewse
		uint64_t fbswip:1;
		uint64_t wfswip:1;
		uint64_t pnw_cout_sew:2;
		uint64_t pnw_cout_wst:1;
		uint64_t c_cout_sew:2;
		uint64_t c_cout_wst:1;
		uint64_t wesewved_8_63:56;
#endif
	} cn61xx;
};

union cvmx_mio_fus_pwog {
	uint64_t u64;
	stwuct cvmx_mio_fus_pwog_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t soft:1;
		uint64_t pwog:1;
#ewse
		uint64_t pwog:1;
		uint64_t soft:1;
		uint64_t wesewved_2_63:62;
#endif
	} s;
	stwuct cvmx_mio_fus_pwog_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t pwog:1;
#ewse
		uint64_t pwog:1;
		uint64_t wesewved_1_63:63;
#endif
	} cn30xx;
};

union cvmx_mio_fus_pwog_times {
	uint64_t u64;
	stwuct cvmx_mio_fus_pwog_times_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t vgate_pin:1;
		uint64_t fswc_pin:1;
		uint64_t pwog_pin:1;
		uint64_t wesewved_6_31:26;
		uint64_t setup:6;
#ewse
		uint64_t setup:6;
		uint64_t wesewved_6_31:26;
		uint64_t pwog_pin:1;
		uint64_t fswc_pin:1;
		uint64_t vgate_pin:1;
		uint64_t wesewved_35_63:29;
#endif
	} s;
	stwuct cvmx_mio_fus_pwog_times_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_33_63:31;
		uint64_t pwog_pin:1;
		uint64_t out:8;
		uint64_t scwk_wo:4;
		uint64_t scwk_hi:12;
		uint64_t setup:8;
#ewse
		uint64_t setup:8;
		uint64_t scwk_hi:12;
		uint64_t scwk_wo:4;
		uint64_t out:8;
		uint64_t pwog_pin:1;
		uint64_t wesewved_33_63:31;
#endif
	} cn50xx;
	stwuct cvmx_mio_fus_pwog_times_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_35_63:29;
		uint64_t vgate_pin:1;
		uint64_t fswc_pin:1;
		uint64_t pwog_pin:1;
		uint64_t out:7;
		uint64_t scwk_wo:4;
		uint64_t scwk_hi:15;
		uint64_t setup:6;
#ewse
		uint64_t setup:6;
		uint64_t scwk_hi:15;
		uint64_t scwk_wo:4;
		uint64_t out:7;
		uint64_t pwog_pin:1;
		uint64_t fswc_pin:1;
		uint64_t vgate_pin:1;
		uint64_t wesewved_35_63:29;
#endif
	} cn61xx;
};

union cvmx_mio_fus_wcmd {
	uint64_t u64;
	stwuct cvmx_mio_fus_wcmd_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t dat:8;
		uint64_t wesewved_13_15:3;
		uint64_t pend:1;
		uint64_t wesewved_9_11:3;
		uint64_t efuse:1;
		uint64_t addw:8;
#ewse
		uint64_t addw:8;
		uint64_t efuse:1;
		uint64_t wesewved_9_11:3;
		uint64_t pend:1;
		uint64_t wesewved_13_15:3;
		uint64_t dat:8;
		uint64_t wesewved_24_63:40;
#endif
	} s;
	stwuct cvmx_mio_fus_wcmd_cn30xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t dat:8;
		uint64_t wesewved_13_15:3;
		uint64_t pend:1;
		uint64_t wesewved_9_11:3;
		uint64_t efuse:1;
		uint64_t wesewved_7_7:1;
		uint64_t addw:7;
#ewse
		uint64_t addw:7;
		uint64_t wesewved_7_7:1;
		uint64_t efuse:1;
		uint64_t wesewved_9_11:3;
		uint64_t pend:1;
		uint64_t wesewved_13_15:3;
		uint64_t dat:8;
		uint64_t wesewved_24_63:40;
#endif
	} cn30xx;
};

union cvmx_mio_fus_wead_times {
	uint64_t u64;
	stwuct cvmx_mio_fus_wead_times_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_26_63:38;
		uint64_t sch:4;
		uint64_t fsh:4;
		uint64_t pwh:4;
		uint64_t sdh:4;
		uint64_t setup:10;
#ewse
		uint64_t setup:10;
		uint64_t sdh:4;
		uint64_t pwh:4;
		uint64_t fsh:4;
		uint64_t sch:4;
		uint64_t wesewved_26_63:38;
#endif
	} s;
};

union cvmx_mio_fus_wepaiw_wes0 {
	uint64_t u64;
	stwuct cvmx_mio_fus_wepaiw_wes0_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_55_63:9;
		uint64_t too_many:1;
		uint64_t wepaiw2:18;
		uint64_t wepaiw1:18;
		uint64_t wepaiw0:18;
#ewse
		uint64_t wepaiw0:18;
		uint64_t wepaiw1:18;
		uint64_t wepaiw2:18;
		uint64_t too_many:1;
		uint64_t wesewved_55_63:9;
#endif
	} s;
};

union cvmx_mio_fus_wepaiw_wes1 {
	uint64_t u64;
	stwuct cvmx_mio_fus_wepaiw_wes1_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_54_63:10;
		uint64_t wepaiw5:18;
		uint64_t wepaiw4:18;
		uint64_t wepaiw3:18;
#ewse
		uint64_t wepaiw3:18;
		uint64_t wepaiw4:18;
		uint64_t wepaiw5:18;
		uint64_t wesewved_54_63:10;
#endif
	} s;
};

union cvmx_mio_fus_wepaiw_wes2 {
	uint64_t u64;
	stwuct cvmx_mio_fus_wepaiw_wes2_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_18_63:46;
		uint64_t wepaiw6:18;
#ewse
		uint64_t wepaiw6:18;
		uint64_t wesewved_18_63:46;
#endif
	} s;
};

union cvmx_mio_fus_spw_wepaiw_wes {
	uint64_t u64;
	stwuct cvmx_mio_fus_spw_wepaiw_wes_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t wepaiw2:14;
		uint64_t wepaiw1:14;
		uint64_t wepaiw0:14;
#ewse
		uint64_t wepaiw0:14;
		uint64_t wepaiw1:14;
		uint64_t wepaiw2:14;
		uint64_t wesewved_42_63:22;
#endif
	} s;
};

union cvmx_mio_fus_spw_wepaiw_sum {
	uint64_t u64;
	stwuct cvmx_mio_fus_spw_wepaiw_sum_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t too_many:1;
#ewse
		uint64_t too_many:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_fus_tgg {
	uint64_t u64;
	stwuct cvmx_mio_fus_tgg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t vaw:1;
		uint64_t dat:63;
#ewse
		uint64_t dat:63;
		uint64_t vaw:1;
#endif
	} s;
};

union cvmx_mio_fus_unwock {
	uint64_t u64;
	stwuct cvmx_mio_fus_unwock_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t key:24;
#ewse
		uint64_t key:24;
		uint64_t wesewved_24_63:40;
#endif
	} s;
};

union cvmx_mio_fus_wadw {
	uint64_t u64;
	stwuct cvmx_mio_fus_wadw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t addw:10;
#ewse
		uint64_t addw:10;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_mio_fus_wadw_cn50xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t addw:2;
#ewse
		uint64_t addw:2;
		uint64_t wesewved_2_63:62;
#endif
	} cn50xx;
	stwuct cvmx_mio_fus_wadw_cn52xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t addw:3;
#ewse
		uint64_t addw:3;
		uint64_t wesewved_3_63:61;
#endif
	} cn52xx;
	stwuct cvmx_mio_fus_wadw_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_4_63:60;
		uint64_t addw:4;
#ewse
		uint64_t addw:4;
		uint64_t wesewved_4_63:60;
#endif
	} cn61xx;
};

union cvmx_mio_gpio_comp {
	uint64_t u64;
	stwuct cvmx_mio_gpio_comp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t pctw:6;
		uint64_t nctw:6;
#ewse
		uint64_t nctw:6;
		uint64_t pctw:6;
		uint64_t wesewved_12_63:52;
#endif
	} s;
};

union cvmx_mio_ndf_dma_cfg {
	uint64_t u64;
	stwuct cvmx_mio_ndf_dma_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t en:1;
		uint64_t ww:1;
		uint64_t cww:1;
		uint64_t wesewved_60_60:1;
		uint64_t swap32:1;
		uint64_t swap16:1;
		uint64_t swap8:1;
		uint64_t endian:1;
		uint64_t size:20;
		uint64_t adw:36;
#ewse
		uint64_t adw:36;
		uint64_t size:20;
		uint64_t endian:1;
		uint64_t swap8:1;
		uint64_t swap16:1;
		uint64_t swap32:1;
		uint64_t wesewved_60_60:1;
		uint64_t cww:1;
		uint64_t ww:1;
		uint64_t en:1;
#endif
	} s;
};

union cvmx_mio_ndf_dma_int {
	uint64_t u64;
	stwuct cvmx_mio_ndf_dma_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t done:1;
#ewse
		uint64_t done:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_ndf_dma_int_en {
	uint64_t u64;
	stwuct cvmx_mio_ndf_dma_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t done:1;
#ewse
		uint64_t done:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_pww_ctw {
	uint64_t u64;
	stwuct cvmx_mio_pww_ctw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t bw_ctw:5;
#ewse
		uint64_t bw_ctw:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_mio_pww_setting {
	uint64_t u64;
	stwuct cvmx_mio_pww_setting_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_17_63:47;
		uint64_t setting:17;
#ewse
		uint64_t setting:17;
		uint64_t wesewved_17_63:47;
#endif
	} s;
};

union cvmx_mio_ptp_ckout_hi_incw {
	uint64_t u64;
	stwuct cvmx_mio_ptp_ckout_hi_incw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t nanosec:32;
#endif
	} s;
};

union cvmx_mio_ptp_ckout_wo_incw {
	uint64_t u64;
	stwuct cvmx_mio_ptp_ckout_wo_incw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t nanosec:32;
#endif
	} s;
};

union cvmx_mio_ptp_ckout_thwesh_hi {
	uint64_t u64;
	stwuct cvmx_mio_ptp_ckout_thwesh_hi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:64;
#ewse
		uint64_t nanosec:64;
#endif
	} s;
};

union cvmx_mio_ptp_ckout_thwesh_wo {
	uint64_t u64;
	stwuct cvmx_mio_ptp_ckout_thwesh_wo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_ptp_cwock_cfg {
	uint64_t u64;
	stwuct cvmx_mio_ptp_cwock_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_42_63:22;
		uint64_t pps:1;
		uint64_t ckout:1;
		uint64_t ext_cwk_edge:2;
		uint64_t ckout_out4:1;
		uint64_t pps_out:5;
		uint64_t pps_inv:1;
		uint64_t pps_en:1;
		uint64_t ckout_out:4;
		uint64_t ckout_inv:1;
		uint64_t ckout_en:1;
		uint64_t evcnt_in:6;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_en:1;
		uint64_t tstmp_in:6;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t ext_cwk_en:1;
		uint64_t ptp_en:1;
#ewse
		uint64_t ptp_en:1;
		uint64_t ext_cwk_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t tstmp_en:1;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_in:6;
		uint64_t evcnt_en:1;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_in:6;
		uint64_t ckout_en:1;
		uint64_t ckout_inv:1;
		uint64_t ckout_out:4;
		uint64_t pps_en:1;
		uint64_t pps_inv:1;
		uint64_t pps_out:5;
		uint64_t ckout_out4:1;
		uint64_t ext_cwk_edge:2;
		uint64_t ckout:1;
		uint64_t pps:1;
		uint64_t wesewved_42_63:22;
#endif
	} s;
	stwuct cvmx_mio_ptp_cwock_cfg_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_24_63:40;
		uint64_t evcnt_in:6;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_en:1;
		uint64_t tstmp_in:6;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t ext_cwk_en:1;
		uint64_t ptp_en:1;
#ewse
		uint64_t ptp_en:1;
		uint64_t ext_cwk_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t tstmp_en:1;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_in:6;
		uint64_t evcnt_en:1;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_in:6;
		uint64_t wesewved_24_63:40;
#endif
	} cn63xx;
	stwuct cvmx_mio_ptp_cwock_cfg_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t ext_cwk_edge:2;
		uint64_t ckout_out4:1;
		uint64_t pps_out:5;
		uint64_t pps_inv:1;
		uint64_t pps_en:1;
		uint64_t ckout_out:4;
		uint64_t ckout_inv:1;
		uint64_t ckout_en:1;
		uint64_t evcnt_in:6;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_en:1;
		uint64_t tstmp_in:6;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t ext_cwk_en:1;
		uint64_t ptp_en:1;
#ewse
		uint64_t ptp_en:1;
		uint64_t ext_cwk_en:1;
		uint64_t ext_cwk_in:6;
		uint64_t tstmp_en:1;
		uint64_t tstmp_edge:1;
		uint64_t tstmp_in:6;
		uint64_t evcnt_en:1;
		uint64_t evcnt_edge:1;
		uint64_t evcnt_in:6;
		uint64_t ckout_en:1;
		uint64_t ckout_inv:1;
		uint64_t ckout_out:4;
		uint64_t pps_en:1;
		uint64_t pps_inv:1;
		uint64_t pps_out:5;
		uint64_t ckout_out4:1;
		uint64_t ext_cwk_edge:2;
		uint64_t wesewved_40_63:24;
#endif
	} cn66xx;
};

union cvmx_mio_ptp_cwock_comp {
	uint64_t u64;
	stwuct cvmx_mio_ptp_cwock_comp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t nanosec:32;
#endif
	} s;
};

union cvmx_mio_ptp_cwock_hi {
	uint64_t u64;
	stwuct cvmx_mio_ptp_cwock_hi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:64;
#ewse
		uint64_t nanosec:64;
#endif
	} s;
};

union cvmx_mio_ptp_cwock_wo {
	uint64_t u64;
	stwuct cvmx_mio_ptp_cwock_wo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_ptp_evt_cnt {
	uint64_t u64;
	stwuct cvmx_mio_ptp_evt_cnt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t cntw:64;
#ewse
		uint64_t cntw:64;
#endif
	} s;
};

union cvmx_mio_ptp_phy_1pps_in {
	uint64_t u64;
	stwuct cvmx_mio_ptp_phy_1pps_in_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t sew:5;
#ewse
		uint64_t sew:5;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_mio_ptp_pps_hi_incw {
	uint64_t u64;
	stwuct cvmx_mio_ptp_pps_hi_incw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t nanosec:32;
#endif
	} s;
};

union cvmx_mio_ptp_pps_wo_incw {
	uint64_t u64;
	stwuct cvmx_mio_ptp_pps_wo_incw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t nanosec:32;
#endif
	} s;
};

union cvmx_mio_ptp_pps_thwesh_hi {
	uint64_t u64;
	stwuct cvmx_mio_ptp_pps_thwesh_hi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:64;
#ewse
		uint64_t nanosec:64;
#endif
	} s;
};

union cvmx_mio_ptp_pps_thwesh_wo {
	uint64_t u64;
	stwuct cvmx_mio_ptp_pps_thwesh_wo_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_32_63:32;
		uint64_t fwnanosec:32;
#ewse
		uint64_t fwnanosec:32;
		uint64_t wesewved_32_63:32;
#endif
	} s;
};

union cvmx_mio_ptp_timestamp {
	uint64_t u64;
	stwuct cvmx_mio_ptp_timestamp_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t nanosec:64;
#ewse
		uint64_t nanosec:64;
#endif
	} s;
};

union cvmx_mio_qwmx_cfg {
	uint64_t u64;
	stwuct cvmx_mio_qwmx_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t pwtmode:1;
		uint64_t wesewved_12_13:2;
		uint64_t qwm_spd:4;
		uint64_t wesewved_4_7:4;
		uint64_t qwm_cfg:4;
#ewse
		uint64_t qwm_cfg:4;
		uint64_t wesewved_4_7:4;
		uint64_t qwm_spd:4;
		uint64_t wesewved_12_13:2;
		uint64_t pwtmode:1;
		uint64_t wesewved_15_63:49;
#endif
	} s;
	stwuct cvmx_mio_qwmx_cfg_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_15_63:49;
		uint64_t pwtmode:1;
		uint64_t wesewved_12_13:2;
		uint64_t qwm_spd:4;
		uint64_t wesewved_2_7:6;
		uint64_t qwm_cfg:2;
#ewse
		uint64_t qwm_cfg:2;
		uint64_t wesewved_2_7:6;
		uint64_t qwm_spd:4;
		uint64_t wesewved_12_13:2;
		uint64_t pwtmode:1;
		uint64_t wesewved_15_63:49;
#endif
	} cn61xx;
	stwuct cvmx_mio_qwmx_cfg_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t qwm_spd:4;
		uint64_t wesewved_4_7:4;
		uint64_t qwm_cfg:4;
#ewse
		uint64_t qwm_cfg:4;
		uint64_t wesewved_4_7:4;
		uint64_t qwm_spd:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn66xx;
	stwuct cvmx_mio_qwmx_cfg_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t qwm_spd:4;
		uint64_t wesewved_3_7:5;
		uint64_t qwm_cfg:3;
#ewse
		uint64_t qwm_cfg:3;
		uint64_t wesewved_3_7:5;
		uint64_t qwm_spd:4;
		uint64_t wesewved_12_63:52;
#endif
	} cn68xx;
};

union cvmx_mio_wst_boot {
	uint64_t u64;
	stwuct cvmx_mio_wst_boot_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t chipkiww:1;
		uint64_t jtcswdis:1;
		uint64_t ejtagdis:1;
		uint64_t women:1;
		uint64_t ckiww_ppdis:1;
		uint64_t jt_tstmode:1;
		uint64_t wesewved_50_57:8;
		uint64_t wboot_ext:2;
		uint64_t wesewved_44_47:4;
		uint64_t qwm4_spd:4;
		uint64_t qwm3_spd:4;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t qwm3_spd:4;
		uint64_t qwm4_spd:4;
		uint64_t wesewved_44_47:4;
		uint64_t wboot_ext:2;
		uint64_t wesewved_50_57:8;
		uint64_t jt_tstmode:1;
		uint64_t ckiww_ppdis:1;
		uint64_t women:1;
		uint64_t ejtagdis:1;
		uint64_t jtcswdis:1;
		uint64_t chipkiww:1;
#endif
	} s;
	stwuct cvmx_mio_wst_boot_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t chipkiww:1;
		uint64_t jtcswdis:1;
		uint64_t ejtagdis:1;
		uint64_t women:1;
		uint64_t ckiww_ppdis:1;
		uint64_t jt_tstmode:1;
		uint64_t wesewved_50_57:8;
		uint64_t wboot_ext:2;
		uint64_t wesewved_36_47:12;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t wesewved_36_47:12;
		uint64_t wboot_ext:2;
		uint64_t wesewved_50_57:8;
		uint64_t jt_tstmode:1;
		uint64_t ckiww_ppdis:1;
		uint64_t women:1;
		uint64_t ejtagdis:1;
		uint64_t jtcswdis:1;
		uint64_t chipkiww:1;
#endif
	} cn61xx;
	stwuct cvmx_mio_wst_boot_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_36_63:28;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t wesewved_36_63:28;
#endif
	} cn63xx;
	stwuct cvmx_mio_wst_boot_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t chipkiww:1;
		uint64_t jtcswdis:1;
		uint64_t ejtagdis:1;
		uint64_t women:1;
		uint64_t ckiww_ppdis:1;
		uint64_t wesewved_50_58:9;
		uint64_t wboot_ext:2;
		uint64_t wesewved_36_47:12;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t wesewved_36_47:12;
		uint64_t wboot_ext:2;
		uint64_t wesewved_50_58:9;
		uint64_t ckiww_ppdis:1;
		uint64_t women:1;
		uint64_t ejtagdis:1;
		uint64_t jtcswdis:1;
		uint64_t chipkiww:1;
#endif
	} cn66xx;
	stwuct cvmx_mio_wst_boot_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_59_63:5;
		uint64_t jt_tstmode:1;
		uint64_t wesewved_44_57:14;
		uint64_t qwm4_spd:4;
		uint64_t qwm3_spd:4;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t qwm3_spd:4;
		uint64_t qwm4_spd:4;
		uint64_t wesewved_44_57:14;
		uint64_t jt_tstmode:1;
		uint64_t wesewved_59_63:5;
#endif
	} cn68xx;
	stwuct cvmx_mio_wst_boot_cn68xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_44_63:20;
		uint64_t qwm4_spd:4;
		uint64_t qwm3_spd:4;
		uint64_t c_muw:6;
		uint64_t pnw_muw:6;
		uint64_t qwm2_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm0_spd:4;
		uint64_t wboot:10;
		uint64_t wboot:1;
		uint64_t wboot_pin:1;
#ewse
		uint64_t wboot_pin:1;
		uint64_t wboot:1;
		uint64_t wboot:10;
		uint64_t qwm0_spd:4;
		uint64_t qwm1_spd:4;
		uint64_t qwm2_spd:4;
		uint64_t pnw_muw:6;
		uint64_t c_muw:6;
		uint64_t qwm3_spd:4;
		uint64_t qwm4_spd:4;
		uint64_t wesewved_44_63:20;
#endif
	} cn68xxp1;
};

union cvmx_mio_wst_cfg {
	uint64_t u64;
	stwuct cvmx_mio_wst_cfg_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t cntw_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t soft_cww_bist:1;
#ewse
		uint64_t soft_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t cntw_cww_bist:1;
		uint64_t wesewved_3_63:61;
#endif
	} s;
	stwuct cvmx_mio_wst_cfg_cn61xx {
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
	} cn61xx;
	stwuct cvmx_mio_wst_cfg_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bist_deway:58;
		uint64_t wesewved_2_5:4;
		uint64_t wawm_cww_bist:1;
		uint64_t soft_cww_bist:1;
#ewse
		uint64_t soft_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t wesewved_2_5:4;
		uint64_t bist_deway:58;
#endif
	} cn63xxp1;
	stwuct cvmx_mio_wst_cfg_cn68xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bist_deway:56;
		uint64_t wesewved_3_7:5;
		uint64_t cntw_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t soft_cww_bist:1;
#ewse
		uint64_t soft_cww_bist:1;
		uint64_t wawm_cww_bist:1;
		uint64_t cntw_cww_bist:1;
		uint64_t wesewved_3_7:5;
		uint64_t bist_deway:56;
#endif
	} cn68xx;
};

union cvmx_mio_wst_ckiww {
	uint64_t u64;
	stwuct cvmx_mio_wst_ckiww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_47_63:17;
		uint64_t timew:47;
#ewse
		uint64_t timew:47;
		uint64_t wesewved_47_63:17;
#endif
	} s;
};

union cvmx_mio_wst_cntwx {
	uint64_t u64;
	stwuct cvmx_mio_wst_cntwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t in_wev_wn:1;
		uint64_t wev_wanes:1;
		uint64_t gen1_onwy:1;
		uint64_t pwst_wink:1;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t pwtmode:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t pwtmode:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t pwst_wink:1;
		uint64_t gen1_onwy:1;
		uint64_t wev_wanes:1;
		uint64_t in_wev_wn:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_mio_wst_cntwx_cn66xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pwst_wink:1;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t pwtmode:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t pwtmode:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t pwst_wink:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn66xx;
};

union cvmx_mio_wst_ctwx {
	uint64_t u64;
	stwuct cvmx_mio_wst_ctwx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_13_63:51;
		uint64_t in_wev_wn:1;
		uint64_t wev_wanes:1;
		uint64_t gen1_onwy:1;
		uint64_t pwst_wink:1;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t pwtmode:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t pwtmode:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t pwst_wink:1;
		uint64_t gen1_onwy:1;
		uint64_t wev_wanes:1;
		uint64_t in_wev_wn:1;
		uint64_t wesewved_13_63:51;
#endif
	} s;
	stwuct cvmx_mio_wst_ctwx_cn63xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pwst_wink:1;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t pwtmode:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t pwtmode:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t pwst_wink:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn63xx;
	stwuct cvmx_mio_wst_ctwx_cn63xxp1 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_9_63:55;
		uint64_t wst_done:1;
		uint64_t wst_wink:1;
		uint64_t host_mode:1;
		uint64_t pwtmode:2;
		uint64_t wst_dwv:1;
		uint64_t wst_wcv:1;
		uint64_t wst_chip:1;
		uint64_t wst_vaw:1;
#ewse
		uint64_t wst_vaw:1;
		uint64_t wst_chip:1;
		uint64_t wst_wcv:1;
		uint64_t wst_dwv:1;
		uint64_t pwtmode:2;
		uint64_t host_mode:1;
		uint64_t wst_wink:1;
		uint64_t wst_done:1;
		uint64_t wesewved_9_63:55;
#endif
	} cn63xxp1;
};

union cvmx_mio_wst_deway {
	uint64_t u64;
	stwuct cvmx_mio_wst_deway_s {
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

union cvmx_mio_wst_int {
	uint64_t u64;
	stwuct cvmx_mio_wst_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pewst1:1;
		uint64_t pewst0:1;
		uint64_t wesewved_4_7:4;
		uint64_t wst_wink3:1;
		uint64_t wst_wink2:1;
		uint64_t wst_wink1:1;
		uint64_t wst_wink0:1;
#ewse
		uint64_t wst_wink0:1;
		uint64_t wst_wink1:1;
		uint64_t wst_wink2:1;
		uint64_t wst_wink3:1;
		uint64_t wesewved_4_7:4;
		uint64_t pewst0:1;
		uint64_t pewst1:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_mio_wst_int_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pewst1:1;
		uint64_t pewst0:1;
		uint64_t wesewved_2_7:6;
		uint64_t wst_wink1:1;
		uint64_t wst_wink0:1;
#ewse
		uint64_t wst_wink0:1;
		uint64_t wst_wink1:1;
		uint64_t wesewved_2_7:6;
		uint64_t pewst0:1;
		uint64_t pewst1:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn61xx;
};

union cvmx_mio_wst_int_en {
	uint64_t u64;
	stwuct cvmx_mio_wst_int_en_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pewst1:1;
		uint64_t pewst0:1;
		uint64_t wesewved_4_7:4;
		uint64_t wst_wink3:1;
		uint64_t wst_wink2:1;
		uint64_t wst_wink1:1;
		uint64_t wst_wink0:1;
#ewse
		uint64_t wst_wink0:1;
		uint64_t wst_wink1:1;
		uint64_t wst_wink2:1;
		uint64_t wst_wink3:1;
		uint64_t wesewved_4_7:4;
		uint64_t pewst0:1;
		uint64_t pewst1:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
	stwuct cvmx_mio_wst_int_en_cn61xx {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t pewst1:1;
		uint64_t pewst0:1;
		uint64_t wesewved_2_7:6;
		uint64_t wst_wink1:1;
		uint64_t wst_wink0:1;
#ewse
		uint64_t wst_wink0:1;
		uint64_t wst_wink1:1;
		uint64_t wesewved_2_7:6;
		uint64_t pewst0:1;
		uint64_t pewst1:1;
		uint64_t wesewved_10_63:54;
#endif
	} cn61xx;
};

union cvmx_mio_twsx_int {
	uint64_t u64;
	stwuct cvmx_mio_twsx_int_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_12_63:52;
		uint64_t scw:1;
		uint64_t sda:1;
		uint64_t scw_ovw:1;
		uint64_t sda_ovw:1;
		uint64_t wesewved_7_7:1;
		uint64_t cowe_en:1;
		uint64_t ts_en:1;
		uint64_t st_en:1;
		uint64_t wesewved_3_3:1;
		uint64_t cowe_int:1;
		uint64_t ts_int:1;
		uint64_t st_int:1;
#ewse
		uint64_t st_int:1;
		uint64_t ts_int:1;
		uint64_t cowe_int:1;
		uint64_t wesewved_3_3:1;
		uint64_t st_en:1;
		uint64_t ts_en:1;
		uint64_t cowe_en:1;
		uint64_t wesewved_7_7:1;
		uint64_t sda_ovw:1;
		uint64_t scw_ovw:1;
		uint64_t sda:1;
		uint64_t scw:1;
		uint64_t wesewved_12_63:52;
#endif
	} s;
	stwuct cvmx_mio_twsx_int_cn38xxp2 {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t cowe_en:1;
		uint64_t ts_en:1;
		uint64_t st_en:1;
		uint64_t wesewved_3_3:1;
		uint64_t cowe_int:1;
		uint64_t ts_int:1;
		uint64_t st_int:1;
#ewse
		uint64_t st_int:1;
		uint64_t ts_int:1;
		uint64_t cowe_int:1;
		uint64_t wesewved_3_3:1;
		uint64_t st_en:1;
		uint64_t ts_en:1;
		uint64_t cowe_en:1;
		uint64_t wesewved_7_63:57;
#endif
	} cn38xxp2;
};

union cvmx_mio_twsx_sw_twsi {
	uint64_t u64;
	stwuct cvmx_mio_twsx_sw_twsi_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t v:1;
		uint64_t swonwy:1;
		uint64_t eia:1;
		uint64_t op:4;
		uint64_t w:1;
		uint64_t sovw:1;
		uint64_t size:3;
		uint64_t scw:2;
		uint64_t a:10;
		uint64_t ia:5;
		uint64_t eop_ia:3;
		uint64_t d:32;
#ewse
		uint64_t d:32;
		uint64_t eop_ia:3;
		uint64_t ia:5;
		uint64_t a:10;
		uint64_t scw:2;
		uint64_t size:3;
		uint64_t sovw:1;
		uint64_t w:1;
		uint64_t op:4;
		uint64_t eia:1;
		uint64_t swonwy:1;
		uint64_t v:1;
#endif
	} s;
};

union cvmx_mio_twsx_sw_twsi_ext {
	uint64_t u64;
	stwuct cvmx_mio_twsx_sw_twsi_ext_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_40_63:24;
		uint64_t ia:8;
		uint64_t d:32;
#ewse
		uint64_t d:32;
		uint64_t ia:8;
		uint64_t wesewved_40_63:24;
#endif
	} s;
};

union cvmx_mio_twsx_twsi_sw {
	uint64_t u64;
	stwuct cvmx_mio_twsx_twsi_sw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t v:2;
		uint64_t wesewved_32_61:30;
		uint64_t d:32;
#ewse
		uint64_t d:32;
		uint64_t wesewved_32_61:30;
		uint64_t v:2;
#endif
	} s;
};

union cvmx_mio_uawtx_dwh {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_dwh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dwh:8;
#ewse
		uint64_t dwh:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_dww {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_dww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dww:8;
#ewse
		uint64_t dww:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_faw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_faw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t faw:1;
#ewse
		uint64_t faw:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawtx_fcw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_fcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wxtwig:2;
		uint64_t txtwig:2;
		uint64_t wesewved_3_3:1;
		uint64_t txfw:1;
		uint64_t wxfw:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t wxfw:1;
		uint64_t txfw:1;
		uint64_t wesewved_3_3:1;
		uint64_t txtwig:2;
		uint64_t wxtwig:2;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_htx {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_htx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t htx:1;
#ewse
		uint64_t htx:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawtx_iew {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_iew_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t ptime:1;
		uint64_t wesewved_4_6:3;
		uint64_t edssi:1;
		uint64_t ewsi:1;
		uint64_t etbei:1;
		uint64_t ewbfi:1;
#ewse
		uint64_t ewbfi:1;
		uint64_t etbei:1;
		uint64_t ewsi:1;
		uint64_t edssi:1;
		uint64_t wesewved_4_6:3;
		uint64_t ptime:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_iiw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_iiw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t fen:2;
		uint64_t wesewved_4_5:2;
		uint64_t iid:4;
#ewse
		uint64_t iid:4;
		uint64_t wesewved_4_5:2;
		uint64_t fen:2;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_wcw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_wcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dwab:1;
		uint64_t bwk:1;
		uint64_t wesewved_5_5:1;
		uint64_t eps:1;
		uint64_t pen:1;
		uint64_t stop:1;
		uint64_t cws:2;
#ewse
		uint64_t cws:2;
		uint64_t stop:1;
		uint64_t pen:1;
		uint64_t eps:1;
		uint64_t wesewved_5_5:1;
		uint64_t bwk:1;
		uint64_t dwab:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_wsw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_wsw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t feww:1;
		uint64_t temt:1;
		uint64_t thwe:1;
		uint64_t bi:1;
		uint64_t fe:1;
		uint64_t pe:1;
		uint64_t oe:1;
		uint64_t dw:1;
#ewse
		uint64_t dw:1;
		uint64_t oe:1;
		uint64_t pe:1;
		uint64_t fe:1;
		uint64_t bi:1;
		uint64_t thwe:1;
		uint64_t temt:1;
		uint64_t feww:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_mcw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_mcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t afce:1;
		uint64_t woop:1;
		uint64_t out2:1;
		uint64_t out1:1;
		uint64_t wts:1;
		uint64_t dtw:1;
#ewse
		uint64_t dtw:1;
		uint64_t wts:1;
		uint64_t out1:1;
		uint64_t out2:1;
		uint64_t woop:1;
		uint64_t afce:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_mio_uawtx_msw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_msw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dcd:1;
		uint64_t wi:1;
		uint64_t dsw:1;
		uint64_t cts:1;
		uint64_t ddcd:1;
		uint64_t tewi:1;
		uint64_t ddsw:1;
		uint64_t dcts:1;
#ewse
		uint64_t dcts:1;
		uint64_t ddsw:1;
		uint64_t tewi:1;
		uint64_t ddcd:1;
		uint64_t cts:1;
		uint64_t dsw:1;
		uint64_t wi:1;
		uint64_t dcd:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_wbw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_wbw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wbw:8;
#ewse
		uint64_t wbw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_wfw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_wfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t wfw:7;
#ewse
		uint64_t wfw:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_uawtx_wfw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_wfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t wffe:1;
		uint64_t wfpe:1;
		uint64_t wfwd:8;
#ewse
		uint64_t wfwd:8;
		uint64_t wfpe:1;
		uint64_t wffe:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_mio_uawtx_sbcw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_sbcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t sbcw:1;
#ewse
		uint64_t sbcw:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawtx_scw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_scw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t scw:8;
#ewse
		uint64_t scw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_sfe {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_sfe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t sfe:1;
#ewse
		uint64_t sfe:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawtx_sww {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_sww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t stfw:1;
		uint64_t swfw:1;
		uint64_t usw:1;
#ewse
		uint64_t usw:1;
		uint64_t swfw:1;
		uint64_t stfw:1;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_mio_uawtx_swt {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_swt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t swt:2;
#ewse
		uint64_t swt:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_uawtx_swts {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_swts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t swts:1;
#ewse
		uint64_t swts:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawtx_stt {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_stt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t stt:2;
#ewse
		uint64_t stt:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_uawtx_tfw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_tfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t tfw:7;
#ewse
		uint64_t tfw:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_uawtx_tfw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_tfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t tfw:8;
#ewse
		uint64_t tfw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_thw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_thw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t thw:8;
#ewse
		uint64_t thw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawtx_usw {
	uint64_t u64;
	stwuct cvmx_mio_uawtx_usw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t wff:1;
		uint64_t wfne:1;
		uint64_t tfe:1;
		uint64_t tfnf:1;
		uint64_t busy:1;
#ewse
		uint64_t busy:1;
		uint64_t tfnf:1;
		uint64_t tfe:1;
		uint64_t wfne:1;
		uint64_t wff:1;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

union cvmx_mio_uawt2_dwh {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_dwh_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dwh:8;
#ewse
		uint64_t dwh:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_dww {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_dww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dww:8;
#ewse
		uint64_t dww:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_faw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_faw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t faw:1;
#ewse
		uint64_t faw:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawt2_fcw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_fcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wxtwig:2;
		uint64_t txtwig:2;
		uint64_t wesewved_3_3:1;
		uint64_t txfw:1;
		uint64_t wxfw:1;
		uint64_t en:1;
#ewse
		uint64_t en:1;
		uint64_t wxfw:1;
		uint64_t txfw:1;
		uint64_t wesewved_3_3:1;
		uint64_t txtwig:2;
		uint64_t wxtwig:2;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_htx {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_htx_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t htx:1;
#ewse
		uint64_t htx:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawt2_iew {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_iew_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t ptime:1;
		uint64_t wesewved_4_6:3;
		uint64_t edssi:1;
		uint64_t ewsi:1;
		uint64_t etbei:1;
		uint64_t ewbfi:1;
#ewse
		uint64_t ewbfi:1;
		uint64_t etbei:1;
		uint64_t ewsi:1;
		uint64_t edssi:1;
		uint64_t wesewved_4_6:3;
		uint64_t ptime:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_iiw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_iiw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t fen:2;
		uint64_t wesewved_4_5:2;
		uint64_t iid:4;
#ewse
		uint64_t iid:4;
		uint64_t wesewved_4_5:2;
		uint64_t fen:2;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_wcw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_wcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dwab:1;
		uint64_t bwk:1;
		uint64_t wesewved_5_5:1;
		uint64_t eps:1;
		uint64_t pen:1;
		uint64_t stop:1;
		uint64_t cws:2;
#ewse
		uint64_t cws:2;
		uint64_t stop:1;
		uint64_t pen:1;
		uint64_t eps:1;
		uint64_t wesewved_5_5:1;
		uint64_t bwk:1;
		uint64_t dwab:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_wsw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_wsw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t feww:1;
		uint64_t temt:1;
		uint64_t thwe:1;
		uint64_t bi:1;
		uint64_t fe:1;
		uint64_t pe:1;
		uint64_t oe:1;
		uint64_t dw:1;
#ewse
		uint64_t dw:1;
		uint64_t oe:1;
		uint64_t pe:1;
		uint64_t fe:1;
		uint64_t bi:1;
		uint64_t thwe:1;
		uint64_t temt:1;
		uint64_t feww:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_mcw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_mcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_6_63:58;
		uint64_t afce:1;
		uint64_t woop:1;
		uint64_t out2:1;
		uint64_t out1:1;
		uint64_t wts:1;
		uint64_t dtw:1;
#ewse
		uint64_t dtw:1;
		uint64_t wts:1;
		uint64_t out1:1;
		uint64_t out2:1;
		uint64_t woop:1;
		uint64_t afce:1;
		uint64_t wesewved_6_63:58;
#endif
	} s;
};

union cvmx_mio_uawt2_msw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_msw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t dcd:1;
		uint64_t wi:1;
		uint64_t dsw:1;
		uint64_t cts:1;
		uint64_t ddcd:1;
		uint64_t tewi:1;
		uint64_t ddsw:1;
		uint64_t dcts:1;
#ewse
		uint64_t dcts:1;
		uint64_t ddsw:1;
		uint64_t tewi:1;
		uint64_t ddcd:1;
		uint64_t cts:1;
		uint64_t dsw:1;
		uint64_t wi:1;
		uint64_t dcd:1;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_wbw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_wbw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t wbw:8;
#ewse
		uint64_t wbw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_wfw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_wfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t wfw:7;
#ewse
		uint64_t wfw:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_uawt2_wfw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_wfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_10_63:54;
		uint64_t wffe:1;
		uint64_t wfpe:1;
		uint64_t wfwd:8;
#ewse
		uint64_t wfwd:8;
		uint64_t wfpe:1;
		uint64_t wffe:1;
		uint64_t wesewved_10_63:54;
#endif
	} s;
};

union cvmx_mio_uawt2_sbcw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_sbcw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t sbcw:1;
#ewse
		uint64_t sbcw:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawt2_scw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_scw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t scw:8;
#ewse
		uint64_t scw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_sfe {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_sfe_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t sfe:1;
#ewse
		uint64_t sfe:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawt2_sww {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_sww_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_3_63:61;
		uint64_t stfw:1;
		uint64_t swfw:1;
		uint64_t usw:1;
#ewse
		uint64_t usw:1;
		uint64_t swfw:1;
		uint64_t stfw:1;
		uint64_t wesewved_3_63:61;
#endif
	} s;
};

union cvmx_mio_uawt2_swt {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_swt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t swt:2;
#ewse
		uint64_t swt:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_uawt2_swts {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_swts_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_1_63:63;
		uint64_t swts:1;
#ewse
		uint64_t swts:1;
		uint64_t wesewved_1_63:63;
#endif
	} s;
};

union cvmx_mio_uawt2_stt {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_stt_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_2_63:62;
		uint64_t stt:2;
#ewse
		uint64_t stt:2;
		uint64_t wesewved_2_63:62;
#endif
	} s;
};

union cvmx_mio_uawt2_tfw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_tfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_7_63:57;
		uint64_t tfw:7;
#ewse
		uint64_t tfw:7;
		uint64_t wesewved_7_63:57;
#endif
	} s;
};

union cvmx_mio_uawt2_tfw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_tfw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t tfw:8;
#ewse
		uint64_t tfw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_thw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_thw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_8_63:56;
		uint64_t thw:8;
#ewse
		uint64_t thw:8;
		uint64_t wesewved_8_63:56;
#endif
	} s;
};

union cvmx_mio_uawt2_usw {
	uint64_t u64;
	stwuct cvmx_mio_uawt2_usw_s {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wesewved_5_63:59;
		uint64_t wff:1;
		uint64_t wfne:1;
		uint64_t tfe:1;
		uint64_t tfnf:1;
		uint64_t busy:1;
#ewse
		uint64_t busy:1;
		uint64_t tfnf:1;
		uint64_t tfe:1;
		uint64_t wfne:1;
		uint64_t wff:1;
		uint64_t wesewved_5_63:59;
#endif
	} s;
};

#endif
