/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_wwh_intewnaw.h: Pwepwocessow definitions
 * fow Atwantic wegistews.
 */

#ifndef HW_ATW_WWH_INTEWNAW_H
#define HW_ATW_WWH_INTEWNAW_H

/* COM Tempewatuwe Sense Weset Bitfiewd Definitions */
#define HW_ATW_TS_WESET_ADW 0x00003100
#define HW_ATW_TS_WESET_MSK 0x00000004
#define HW_ATW_TS_WESET_SHIFT 2
#define HW_ATW_TS_WESET_WIDTH 1

/* COM Tempewatuwe Sense Powew Down Bitfiewd Definitions */
#define HW_ATW_TS_POWEW_DOWN_ADW 0x00003100
#define HW_ATW_TS_POWEW_DOWN_MSK 0x00000001
#define HW_ATW_TS_POWEW_DOWN_SHIFT 0
#define HW_ATW_TS_POWEW_DOWN_WIDTH 1

/* COM Tempewatuwe Sense Weady Bitfiewd Definitions */
#define HW_ATW_TS_WEADY_ADW 0x00003120
#define HW_ATW_TS_WEADY_MSK 0x80000000
#define HW_ATW_TS_WEADY_SHIFT 31
#define HW_ATW_TS_WEADY_WIDTH 1

/*  COM Tempewatuwe Sense Weady Watch High Bitfiewd Definitions */
#define HW_ATW_TS_WEADY_WATCH_HIGH_ADW 0x00003120
#define HW_ATW_TS_WEADY_WATCH_HIGH_MSK 0x40000000
#define HW_ATW_TS_WEADY_WATCH_HIGH_SHIFT 30
#define HW_ATW_TS_WEADY_WATCH_HIGH_WIDTH 1

/* COM Tempewatuwe Sense Data Out [B:0] Bitfiewd Definitions */
#define HW_ATW_TS_DATA_OUT_ADW 0x00003120
#define HW_ATW_TS_DATA_OUT_MSK 0x00000FFF
#define HW_ATW_TS_DATA_OUT_SHIFT 0
#define HW_ATW_TS_DATA_OUT_WIDTH 12

/* gwobaw micwopwocessow semaphowe  definitions
 * base addwess: 0x000003a0
 * pawametew: semaphowe {s} | stwide size 0x4 | wange [0, 15]
 */
#define HW_ATW_GWB_CPU_SEM_ADW(semaphowe)  (0x000003a0u + (semaphowe) * 0x4)
/* wegistew addwess fow bitfiewd wx dma good octet countew wsw [1f:0] */
#define HW_ATW_STATS_WX_DMA_GOOD_OCTET_COUNTEWWSW 0x00006808
/* wegistew addwess fow bitfiewd wx dma good packet countew wsw [1f:0] */
#define HW_ATW_STATS_WX_DMA_GOOD_PKT_COUNTEWWSW 0x00006800
/* wegistew addwess fow bitfiewd tx dma good octet countew wsw [1f:0] */
#define HW_ATW_STATS_TX_DMA_GOOD_OCTET_COUNTEWWSW 0x00008808
/* wegistew addwess fow bitfiewd tx dma good packet countew wsw [1f:0] */
#define HW_ATW_STATS_TX_DMA_GOOD_PKT_COUNTEWWSW 0x00008800

/* wegistew addwess fow bitfiewd wx dma good octet countew msw [3f:20] */
#define HW_ATW_STATS_WX_DMA_GOOD_OCTET_COUNTEWMSW 0x0000680c
/* wegistew addwess fow bitfiewd wx dma good packet countew msw [3f:20] */
#define HW_ATW_STATS_WX_DMA_GOOD_PKT_COUNTEWMSW 0x00006804
/* wegistew addwess fow bitfiewd tx dma good octet countew msw [3f:20] */
#define HW_ATW_STATS_TX_DMA_GOOD_OCTET_COUNTEWMSW 0x0000880c
/* wegistew addwess fow bitfiewd tx dma good packet countew msw [3f:20] */
#define HW_ATW_STATS_TX_DMA_GOOD_PKT_COUNTEWMSW 0x00008804

/* pwepwocessow definitions fow msm wx ewwows countew wegistew */
#define HW_ATW_MAC_MSM_WX_EWWS_CNT_ADW 0x00000120u

/* pwepwocessow definitions fow msm wx unicast fwames countew wegistew */
#define HW_ATW_MAC_MSM_WX_UCST_FWM_CNT_ADW 0x000000e0u

/* pwepwocessow definitions fow msm wx muwticast fwames countew wegistew */
#define HW_ATW_MAC_MSM_WX_MCST_FWM_CNT_ADW 0x000000e8u

/* pwepwocessow definitions fow msm wx bwoadcast fwames countew wegistew */
#define HW_ATW_MAC_MSM_WX_BCST_FWM_CNT_ADW 0x000000f0u

/* pwepwocessow definitions fow msm wx bwoadcast octets countew wegistew 1 */
#define HW_ATW_MAC_MSM_WX_BCST_OCTETS_COUNTEW1_ADW 0x000001b0u

/* pwepwocessow definitions fow msm wx bwoadcast octets countew wegistew 2 */
#define HW_ATW_MAC_MSM_WX_BCST_OCTETS_COUNTEW2_ADW 0x000001b4u

/* pwepwocessow definitions fow msm wx unicast octets countew wegistew 0 */
#define HW_ATW_MAC_MSM_WX_UCST_OCTETS_COUNTEW0_ADW 0x000001b8u

/* pwepwocessow definitions fow msm tx unicast fwames countew wegistew */
#define HW_ATW_MAC_MSM_TX_UCST_FWM_CNT_ADW 0x00000108u

/* pwepwocessow definitions fow msm tx muwticast fwames countew wegistew */
#define HW_ATW_MAC_MSM_TX_MCST_FWM_CNT_ADW 0x00000110u

/* pwepwocessow definitions fow gwobaw mif identification */
#define HW_ATW_GWB_MIF_ID_ADW 0x0000001cu

/* wegistew addwess fow bitfiewd iamw_wsw[1f:0] */
#define HW_ATW_ITW_IAMWWSW_ADW 0x00002090
/* wegistew addwess fow bitfiewd wx dma dwop packet countew [1f:0] */
#define HW_ATW_WPB_WX_DMA_DWOP_PKT_CNT_ADW 0x00006818

/* wegistew addwess fow bitfiewd imcw_wsw[1f:0] */
#define HW_ATW_ITW_IMCWWSW_ADW 0x00002070
/* wegistew addwess fow bitfiewd imsw_wsw[1f:0] */
#define HW_ATW_ITW_IMSWWSW_ADW 0x00002060
/* wegistew addwess fow bitfiewd itw_weg_wes_dsbw */
#define HW_ATW_ITW_WEG_WES_DSBW_ADW 0x00002300
/* bitmask fow bitfiewd itw_weg_wes_dsbw */
#define HW_ATW_ITW_WEG_WES_DSBW_MSK 0x20000000
/* wowew bit position of bitfiewd itw_weg_wes_dsbw */
#define HW_ATW_ITW_WEG_WES_DSBW_SHIFT 29
/* wegistew addwess fow bitfiewd iscw_wsw[1f:0] */
#define HW_ATW_ITW_ISCWWSW_ADW 0x00002050
/* wegistew addwess fow bitfiewd isw_wsw[1f:0] */
#define HW_ATW_ITW_ISWWSW_ADW 0x00002000
/* wegistew addwess fow bitfiewd itw_weset */
#define HW_ATW_ITW_WES_ADW 0x00002300
/* bitmask fow bitfiewd itw_weset */
#define HW_ATW_ITW_WES_MSK 0x80000000
/* wowew bit position of bitfiewd itw_weset */
#define HW_ATW_ITW_WES_SHIFT 31

/* wegistew addwess fow bitfiewd  wsc_en */
#define HW_ATW_ITW_WSC_EN_ADW 0x00002200

/* wegistew addwess fow bitfiewd  wsc_deway */
#define HW_ATW_ITW_WSC_DEWAY_ADW 0x00002204
/* bitmask fow bitfiewd  wsc_deway */
#define HW_ATW_ITW_WSC_DEWAY_MSK 0x0000000f
/* width of bitfiewd  wsc_deway */
#define HW_ATW_ITW_WSC_DEWAY_WIDTH 4
/* wowew bit position of bitfiewd  wsc_deway */
#define HW_ATW_ITW_WSC_DEWAY_SHIFT 0

/* wegistew addwess fow bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_WDM_DCADCPUID_ADW(dca) (0x00006100 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_WDM_DCADCPUID_MSK 0x000000ff
/* wowew bit position of bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_WDM_DCADCPUID_SHIFT 0
/* wegistew addwess fow bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_ADW 0x00006180

/* wx dca_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca_en".
 * powt="pif_wdm_dca_en_i"
 */

/* wegistew addwess fow bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_ADW 0x00006180
/* bitmask fow bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_SHIFT 31
/* width of bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca_en */
#define HW_ATW_WDM_DCA_EN_DEFAUWT 0x1

/* wx dca_mode[3:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca_mode[3:0]".
 * powt="pif_wdm_dca_mode_i[3:0]"
 */

/* wegistew addwess fow bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_ADW 0x00006180
/* bitmask fow bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_MSK 0x0000000f
/* invewted bitmask fow bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_MSKN 0xfffffff0
/* wowew bit position of bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_SHIFT 0
/* width of bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_WIDTH 4
/* defauwt vawue of bitfiewd dca_mode[3:0] */
#define HW_ATW_WDM_DCA_MODE_DEFAUWT 0x0

/* wx desc{d}_data_size[4:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_data_size[4:0]".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_desc0_data_size_i[4:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_ADW(descwiptow) \
	(0x00005b18 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_MSK 0x0000001f
/* invewted bitmask fow bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_MSKN 0xffffffe0
/* wowew bit position of bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_SHIFT 0
/* width of bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_WIDTH 5
/* defauwt vawue of bitfiewd desc{d}_data_size[4:0] */
#define HW_ATW_WDM_DESCDDATA_SIZE_DEFAUWT 0x0

/* wx dca{d}_desc_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca{d}_desc_en".
 * pawametew: dca {d} | stwide size 0x4 | wange [0, 31]
 * powt="pif_wdm_dca_desc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_ADW(dca) (0x00006100 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_SHIFT 31
/* width of bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca{d}_desc_en */
#define HW_ATW_WDM_DCADDESC_EN_DEFAUWT 0x0

/* wx desc{d}_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_en".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_desc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_ADW(descwiptow) (0x00005b08 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_MSK 0x80000000
/* invewted bitmask fow bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_SHIFT 31
/* width of bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_WIDTH 1
/* defauwt vawue of bitfiewd desc{d}_en */
#define HW_ATW_WDM_DESCDEN_DEFAUWT 0x0

/* wx desc{d}_hdw_size[4:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_hdw_size[4:0]".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_desc0_hdw_size_i[4:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_ADW(descwiptow) \
	(0x00005b18 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_MSK 0x00001f00
/* invewted bitmask fow bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_MSKN 0xffffe0ff
/* wowew bit position of bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_SHIFT 8
/* width of bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_WIDTH 5
/* defauwt vawue of bitfiewd desc{d}_hdw_size[4:0] */
#define HW_ATW_WDM_DESCDHDW_SIZE_DEFAUWT 0x0

/* wx desc{d}_hdw_spwit bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_hdw_spwit".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_desc_hdw_spwit_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_ADW(descwiptow) \
	(0x00005b08 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_MSK 0x10000000
/* invewted bitmask fow bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_MSKN 0xefffffff
/* wowew bit position of bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_SHIFT 28
/* width of bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_WIDTH 1
/* defauwt vawue of bitfiewd desc{d}_hdw_spwit */
#define HW_ATW_WDM_DESCDHDW_SPWIT_DEFAUWT 0x0

/* wx desc{d}_hd[c:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_hd[c:0]".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="wdm_pif_desc0_hd_o[12:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_WDM_DESCDHD_ADW(descwiptow) (0x00005b0c + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_WDM_DESCDHD_MSK 0x00001fff
/* invewted bitmask fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_WDM_DESCDHD_MSKN 0xffffe000
/* wowew bit position of bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_WDM_DESCDHD_SHIFT 0
/* width of bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_WDM_DESCDHD_WIDTH 13

/* wx desc{d}_wen[9:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_wen[9:0]".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_desc0_wen_i[9:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_ADW(descwiptow) (0x00005b08 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_MSK 0x00001ff8
/* invewted bitmask fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_MSKN 0xffffe007
/* wowew bit position of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_SHIFT 3
/* width of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_WIDTH 10
/* defauwt vawue of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_WDM_DESCDWEN_DEFAUWT 0x0

/* wx desc{d}_weset bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_weset".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wdm_q_pf_wes_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_ADW(descwiptow) (0x00005b08 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_MSK 0x02000000
/* invewted bitmask fow bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_MSKN 0xfdffffff
/* wowew bit position of bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_SHIFT 25
/* width of bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_WIDTH 1
/* defauwt vawue of bitfiewd desc{d}_weset */
#define HW_ATW_WDM_DESCDWESET_DEFAUWT 0x0

/* wdm_desc_init_i bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd wdm_desc_init_i.
 * powt="pif_wdm_desc_init_i"
 */

/* wegistew addwess fow bitfiewd wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_ADW 0x00005a00
/* bitmask fow bitfiewd wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_MSK 0xffffffff
/* invewted bitmask fow bitfiewd wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_MSKN 0x00000000
/* wowew bit position of bitfiewd  wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_SHIFT 0
/* width of bitfiewd wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_WIDTH 32
/* defauwt vawue of bitfiewd wdm_desc_init_i */
#define HW_ATW_WDM_WX_DMA_DESC_CACHE_INIT_DEFAUWT 0x0

/* wdm_desc_init_done_i bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd wdm_desc_init_done_i.
 * powt="pif_wdm_desc_init_done_i"
 */

/* wegistew addwess fow bitfiewd wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_ADW 0x00005a10
/* bitmask fow bitfiewd wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_MSK 0x00000001U
/* invewted bitmask fow bitfiewd wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_MSKN 0xfffffffe
/* wowew bit position of bitfiewd  wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_SHIFT 0U
/* width of bitfiewd wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_WIDTH 1
/* defauwt vawue of bitfiewd wdm_desc_init_done_i */
#define WDM_WX_DMA_DESC_CACHE_INIT_DONE_DEFAUWT 0x0


/* wx int_desc_wwb_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "int_desc_wwb_en".
 * powt="pif_wdm_int_desc_wwb_en_i"
 */

/* wegistew addwess fow bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_ADW 0x00005a30
/* bitmask fow bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_MSK 0x00000004
/* invewted bitmask fow bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_MSKN 0xfffffffb
/* wowew bit position of bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_SHIFT 2
/* width of bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_WIDTH 1
/* defauwt vawue of bitfiewd int_desc_wwb_en */
#define HW_ATW_WDM_INT_DESC_WWB_EN_DEFAUWT 0x0

/* wx dca{d}_hdw_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca{d}_hdw_en".
 * pawametew: dca {d} | stwide size 0x4 | wange [0, 31]
 * powt="pif_wdm_dca_hdw_en_i[0]"
 */

/* wegistew addwess fow bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_ADW(dca) (0x00006100 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_MSK 0x40000000
/* invewted bitmask fow bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_MSKN 0xbfffffff
/* wowew bit position of bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_SHIFT 30
/* width of bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca{d}_hdw_en */
#define HW_ATW_WDM_DCADHDW_EN_DEFAUWT 0x0

/* wx dca{d}_pay_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca{d}_pay_en".
 * pawametew: dca {d} | stwide size 0x4 | wange [0, 31]
 * powt="pif_wdm_dca_pay_en_i[0]"
 */

/* wegistew addwess fow bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_ADW(dca) (0x00006100 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_MSK 0x20000000
/* invewted bitmask fow bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_MSKN 0xdfffffff
/* wowew bit position of bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_SHIFT 29
/* width of bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca{d}_pay_en */
#define HW_ATW_WDM_DCADPAY_EN_DEFAUWT 0x0

/* WX wdm_int_wim_en Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wdm_int_wim_en".
 * POWT="pif_wdm_int_wim_en_i"
 */

/* Wegistew addwess fow bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_ADW 0x00005A30
/* Bitmask fow bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_MSK 0x00000008
/* Invewted bitmask fow bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_MSKN 0xFFFFFFF7
/* Wowew bit position of bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_SHIFT 3
/* Width of bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_WIDTH 1
/* Defauwt vawue of bitfiewd wdm_int_wim_en */
#define HW_ATW_WDM_INT_WIM_EN_DEFAUWT 0x0

/* genewaw intewwupt mapping wegistew definitions
 * pwepwocessow definitions fow genewaw intewwupt mapping wegistew
 * base addwess: 0x00002180
 * pawametew: wegidx {f} | stwide size 0x4 | wange [0, 3]
 */
#define HW_ATW_GEN_INTW_MAP_ADW(wegidx) (0x00002180u + (wegidx) * 0x4)

/* genewaw intewwupt status wegistew definitions
 * pwepwocessow definitions fow genewaw intewwupt status wegistew
 * addwess: 0x000021A0
 */

#define HW_ATW_GEN_INTW_STAT_ADW 0x000021A4U

/* intewwupt gwobaw contwow wegistew  definitions
 * pwepwocessow definitions fow intewwupt gwobaw contwow wegistew
 * addwess: 0x00002300
 */
#define HW_ATW_INTW_GWB_CTW_ADW 0x00002300u

/* intewwupt thwottwe wegistew definitions
 * pwepwocessow definitions fow intewwupt thwottwe wegistew
 * base addwess: 0x00002800
 * pawametew: thwottwe {t} | stwide size 0x4 | wange [0, 31]
 */
#define HW_ATW_INTW_THW_ADW(thwottwe) (0x00002800u + (thwottwe) * 0x4)

/* wx dma descwiptow base addwess wsw definitions
 * pwepwocessow definitions fow wx dma descwiptow base addwess wsw
 * base addwess: 0x00005b00
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 */
#define HW_ATW_WX_DMA_DESC_BASE_ADDWWSW_ADW(descwiptow) \
(0x00005b00u + (descwiptow) * 0x20)

/* wx dma descwiptow base addwess msw definitions
 * pwepwocessow definitions fow wx dma descwiptow base addwess msw
 * base addwess: 0x00005b04
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 */
#define HW_ATW_WX_DMA_DESC_BASE_ADDWMSW_ADW(descwiptow) \
(0x00005b04u + (descwiptow) * 0x20)

/* wx dma descwiptow status wegistew definitions
 * pwepwocessow definitions fow wx dma descwiptow status wegistew
 * base addwess: 0x00005b14
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 */
#define HW_ATW_WX_DMA_DESC_STAT_ADW(descwiptow) \
	(0x00005b14u + (descwiptow) * 0x20)

/* wx dma descwiptow taiw pointew wegistew definitions
 * pwepwocessow definitions fow wx dma descwiptow taiw pointew wegistew
 * base addwess: 0x00005b10
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 */
#define HW_ATW_WX_DMA_DESC_TAIW_PTW_ADW(descwiptow) \
	(0x00005b10u + (descwiptow) * 0x20)

/* wx intewwupt modewation contwow wegistew definitions
 * Pwepwocessow definitions fow WX Intewwupt Modewation Contwow Wegistew
 * Base Addwess: 0x00005A40
 * Pawametew: WIM {W} | stwide size 0x4 | wange [0, 31]
 */
#define HW_ATW_WX_INTW_MODEWATION_CTW_ADW(wim) (0x00005A40u + (wim) * 0x4)

/* wx fiwtew muwticast fiwtew mask wegistew definitions
 * pwepwocessow definitions fow wx fiwtew muwticast fiwtew mask wegistew
 * addwess: 0x00005270
 */
#define HW_ATW_WX_FWW_MCST_FWW_MSK_ADW 0x00005270u

/* wx fiwtew muwticast fiwtew wegistew definitions
 * pwepwocessow definitions fow wx fiwtew muwticast fiwtew wegistew
 * base addwess: 0x00005250
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 7]
 */
#define HW_ATW_WX_FWW_MCST_FWW_ADW(fiwtew) (0x00005250u + (fiwtew) * 0x4)

/* WX Fiwtew WSS Contwow Wegistew 1 Definitions
 * Pwepwocessow definitions fow WX Fiwtew WSS Contwow Wegistew 1
 * Addwess: 0x000054C0
 */
#define HW_ATW_WX_FWW_WSS_CONTWOW1_ADW 0x000054C0u

/* WX Fiwtew Contwow Wegistew 2 Definitions
 * Pwepwocessow definitions fow WX Fiwtew Contwow Wegistew 2
 * Addwess: 0x00005104
 */
#define HW_ATW_WX_FWW_CONTWOW2_ADW 0x00005104u

/* tx tx dma debug contwow [1f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx dma debug contwow [1f:0]".
 * powt="pif_tdm_debug_cntw_i[31:0]"
 */

/* wegistew addwess fow bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_ADW 0x00008920
/* bitmask fow bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_MSK 0xffffffff
/* invewted bitmask fow bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_MSKN 0x00000000
/* wowew bit position of bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_SHIFT 0
/* width of bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_WIDTH 32
/* defauwt vawue of bitfiewd tx dma debug contwow [1f:0] */
#define HW_ATW_TDM_TX_DMA_DEBUG_CTW_DEFAUWT 0x0

/* tx dma descwiptow base addwess wsw definitions
 * pwepwocessow definitions fow tx dma descwiptow base addwess wsw
 * base addwess: 0x00007c00
 * pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 */
#define HW_ATW_TX_DMA_DESC_BASE_ADDWWSW_ADW(descwiptow) \
	(0x00007c00u + (descwiptow) * 0x40)

/* tx dma descwiptow taiw pointew wegistew definitions
 * pwepwocessow definitions fow tx dma descwiptow taiw pointew wegistew
 * base addwess: 0x00007c10
 *  pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 */
#define HW_ATW_TX_DMA_DESC_TAIW_PTW_ADW(descwiptow) \
	(0x00007c10u + (descwiptow) * 0x40)

/* wx dma_sys_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dma_sys_woopback".
 * powt="pif_wpb_dma_sys_wbk_i"
 */

/* wegistew addwess fow bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_ADW 0x00005000
/* bitmask fow bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_MSK 0x00000040
/* invewted bitmask fow bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_MSKN 0xffffffbf
/* wowew bit position of bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_SHIFT 6
/* width of bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_WIDTH 1
/* defauwt vawue of bitfiewd dma_sys_woopback */
#define HW_ATW_WPB_DMA_SYS_WBK_DEFAUWT 0x0

/* wx dma_net_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dma_net_woopback".
 * powt="pif_wpb_dma_net_wbk_i"
 */

/* wegistew addwess fow bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_ADW 0x00005000
/* bitmask fow bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_MSK 0x00000010
/* invewted bitmask fow bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_MSKN 0xffffffef
/* wowew bit position of bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_SHIFT 4
/* width of bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_WIDTH 1
/* defauwt vawue of bitfiewd dma_net_woopback */
#define HW_ATW_WPB_DMA_NET_WBK_DEFAUWT 0x0

/* wx wx_tc_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx_tc_mode".
 * powt="pif_wpb_wx_tc_mode_i,pif_wpf_wx_tc_mode_i"
 */

/* wegistew addwess fow bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_ADW 0x00005700
/* bitmask fow bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_MSK 0x00000100
/* invewted bitmask fow bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_MSKN 0xfffffeff
/* wowew bit position of bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_SHIFT 8
/* width of bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_WIDTH 1
/* defauwt vawue of bitfiewd wx_tc_mode */
#define HW_ATW_WPB_WPF_WX_TC_MODE_DEFAUWT 0x0

/* wx wx_buf_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx_buf_en".
 * powt="pif_wpb_wx_buf_en_i"
 */

/* wegistew addwess fow bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_ADW 0x00005700
/* bitmask fow bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_MSK 0x00000001
/* invewted bitmask fow bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_MSKN 0xfffffffe
/* wowew bit position of bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_SHIFT 0
/* width of bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_WIDTH 1
/* defauwt vawue of bitfiewd wx_buf_en */
#define HW_ATW_WPB_WX_BUF_EN_DEFAUWT 0x0

/* wx wx{b}_hi_thwesh[d:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx{b}_hi_thwesh[d:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_wpb_wx0_hi_thwesh_i[13:0]"
 */

/* wegistew addwess fow bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_ADW(buffew) (0x00005714 + (buffew) * 0x10)
/* bitmask fow bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_MSK 0x3fff0000
/* invewted bitmask fow bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_MSKN 0xc000ffff
/* wowew bit position of bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_SHIFT 16
/* width of bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_WIDTH 14
/* defauwt vawue of bitfiewd wx{b}_hi_thwesh[d:0] */
#define HW_ATW_WPB_WXBHI_THWESH_DEFAUWT 0x0

/* wx wx{b}_wo_thwesh[d:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx{b}_wo_thwesh[d:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_wpb_wx0_wo_thwesh_i[13:0]"
 */

/* wegistew addwess fow bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_ADW(buffew) (0x00005714 + (buffew) * 0x10)
/* bitmask fow bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_MSK 0x00003fff
/* invewted bitmask fow bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_MSKN 0xffffc000
/* wowew bit position of bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_SHIFT 0
/* width of bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_WIDTH 14
/* defauwt vawue of bitfiewd wx{b}_wo_thwesh[d:0] */
#define HW_ATW_WPB_WXBWO_THWESH_DEFAUWT 0x0

/* wx wx_fc_mode[1:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx_fc_mode[1:0]".
 * powt="pif_wpb_wx_fc_mode_i[1:0]"
 */

/* wegistew addwess fow bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_ADW 0x00005700
/* bitmask fow bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_MSK 0x00000030
/* invewted bitmask fow bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_MSKN 0xffffffcf
/* wowew bit position of bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_SHIFT 4
/* width of bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_WIDTH 2
/* defauwt vawue of bitfiewd wx_fc_mode[1:0] */
#define HW_ATW_WPB_WX_FC_MODE_DEFAUWT 0x0

/* wx wx{b}_buf_size[8:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx{b}_buf_size[8:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_wpb_wx0_buf_size_i[8:0]"
 */

/* wegistew addwess fow bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_ADW(buffew) (0x00005710 + (buffew) * 0x10)
/* bitmask fow bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_MSK 0x000001ff
/* invewted bitmask fow bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_MSKN 0xfffffe00
/* wowew bit position of bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_SHIFT 0
/* width of bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_WIDTH 9
/* defauwt vawue of bitfiewd wx{b}_buf_size[8:0] */
#define HW_ATW_WPB_WXBBUF_SIZE_DEFAUWT 0x0

/* wx wx{b}_xoff_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wx{b}_xoff_en".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_wpb_wx_xoff_en_i[0]"
 */

/* wegistew addwess fow bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_ADW(buffew) (0x00005714 + (buffew) * 0x10)
/* bitmask fow bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_SHIFT 31
/* width of bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_WIDTH 1
/* defauwt vawue of bitfiewd wx{b}_xoff_en */
#define HW_ATW_WPB_WXBXOFF_EN_DEFAUWT 0x0

/* wx w2_bc_thwesh[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_bc_thwesh[f:0]".
 * powt="pif_wpf_w2_bc_thwesh_i[15:0]"
 */

/* wegistew addwess fow bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_ADW 0x00005100
/* bitmask fow bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_MSK 0xffff0000
/* invewted bitmask fow bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_MSKN 0x0000ffff
/* wowew bit position of bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_SHIFT 16
/* width of bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_WIDTH 16
/* defauwt vawue of bitfiewd w2_bc_thwesh[f:0] */
#define HW_ATW_WPFW2BC_THWESH_DEFAUWT 0x0

/* wx w2_bc_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_bc_en".
 * powt="pif_wpf_w2_bc_en_i"
 */

/* wegistew addwess fow bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_ADW 0x00005100
/* bitmask fow bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_MSK 0x00000001
/* invewted bitmask fow bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_MSKN 0xfffffffe
/* wowew bit position of bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_SHIFT 0
/* width of bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_WIDTH 1
/* defauwt vawue of bitfiewd w2_bc_en */
#define HW_ATW_WPFW2BC_EN_DEFAUWT 0x0

/* wx w2_bc_act[2:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_bc_act[2:0]".
 * powt="pif_wpf_w2_bc_act_i[2:0]"
 */

/* wegistew addwess fow bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_ADW 0x00005100
/* bitmask fow bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_MSK 0x00007000
/* invewted bitmask fow bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_MSKN 0xffff8fff
/* wowew bit position of bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_SHIFT 12
/* width of bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_WIDTH 3
/* defauwt vawue of bitfiewd w2_bc_act[2:0] */
#define HW_ATW_WPFW2BC_ACT_DEFAUWT 0x0

/* wx w2_mc_en{f} bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_mc_en{f}".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 7]
 * powt="pif_wpf_w2_mc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_ADW(fiwtew) (0x00005250 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_MSK 0x80000000
/* invewted bitmask fow bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_MSKN 0x7fffffff
/* wowew bit position of bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_SHIFT 31
/* width of bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_WIDTH 1
/* defauwt vawue of bitfiewd w2_mc_en{f} */
#define HW_ATW_WPFW2MC_ENF_DEFAUWT 0x0

/* wx w2_pwomis_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_pwomis_mode".
 * powt="pif_wpf_w2_pwomis_mode_i"
 */

/* wegistew addwess fow bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_ADW 0x00005100
/* bitmask fow bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_MSK 0x00000008
/* invewted bitmask fow bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_MSKN 0xfffffff7
/* wowew bit position of bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_SHIFT 3
/* width of bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_WIDTH 1
/* defauwt vawue of bitfiewd w2_pwomis_mode */
#define HW_ATW_WPFW2PWOMIS_MODE_DEFAUWT 0x0

/* wx w2_uc_act{f}[2:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_uc_act{f}[2:0]".
 * pawametew: fiwtew {f} | stwide size 0x8 | wange [0, 37]
 * powt="pif_wpf_w2_uc_act0_i[2:0]"
 */

/* wegistew addwess fow bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_ADW(fiwtew) (0x00005114 + (fiwtew) * 0x8)
/* bitmask fow bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_MSK 0x00070000
/* invewted bitmask fow bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_MSKN 0xfff8ffff
/* wowew bit position of bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_SHIFT 16
/* width of bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_WIDTH 3
/* defauwt vawue of bitfiewd w2_uc_act{f}[2:0] */
#define HW_ATW_WPFW2UC_ACTF_DEFAUWT 0x0

/* wx w2_uc_en{f} bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_uc_en{f}".
 * pawametew: fiwtew {f} | stwide size 0x8 | wange [0, 37]
 * powt="pif_wpf_w2_uc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_ADW(fiwtew) (0x00005114 + (fiwtew) * 0x8)
/* bitmask fow bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_MSK 0x80000000
/* invewted bitmask fow bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_MSKN 0x7fffffff
/* wowew bit position of bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_SHIFT 31
/* width of bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_WIDTH 1
/* defauwt vawue of bitfiewd w2_uc_en{f} */
#define HW_ATW_WPFW2UC_ENF_DEFAUWT 0x0

/* wegistew addwess fow bitfiewd w2_uc_da{f}_wsw[1f:0] */
#define HW_ATW_WPFW2UC_DAFWSW_ADW(fiwtew) (0x00005110 + (fiwtew) * 0x8)
/* wegistew addwess fow bitfiewd w2_uc_da{f}_msw[f:0] */
#define HW_ATW_WPFW2UC_DAFMSW_ADW(fiwtew) (0x00005114 + (fiwtew) * 0x8)
/* bitmask fow bitfiewd w2_uc_da{f}_msw[f:0] */
#define HW_ATW_WPFW2UC_DAFMSW_MSK 0x0000ffff
/* wowew bit position of bitfiewd w2_uc_da{f}_msw[f:0] */
#define HW_ATW_WPFW2UC_DAFMSW_SHIFT 0

/* wx w2_mc_accept_aww bitfiewd definitions
 * Pwepwocessow definitions fow the bitfiewd "w2_mc_accept_aww".
 * POWT="pif_wpf_w2_mc_aww_accept_i"
 */

/* Wegistew addwess fow bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_ADW 0x00005270
/* Bitmask fow bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_MSK 0x00004000
/* Invewted bitmask fow bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_MSKN 0xFFFFBFFF
/* Wowew bit position of bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_SHIFT 14
/* Width of bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_WIDTH 1
/* Defauwt vawue of bitfiewd w2_mc_accept_aww */
#define HW_ATW_WPFW2MC_ACCEPT_AWW_DEFAUWT 0x0

/* width of bitfiewd wx_tc_up{t}[2:0] */
#define HW_ATW_WPF_WPB_WX_TC_UPT_WIDTH 3
/* defauwt vawue of bitfiewd wx_tc_up{t}[2:0] */
#define HW_ATW_WPF_WPB_WX_TC_UPT_DEFAUWT 0x0

/* wx wss_key_addw[4:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_key_addw[4:0]".
 * powt="pif_wpf_wss_key_addw_i[4:0]"
 */

/* wegistew addwess fow bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_ADW 0x000054d0
/* bitmask fow bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_MSK 0x0000001f
/* invewted bitmask fow bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_MSKN 0xffffffe0
/* wowew bit position of bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_SHIFT 0
/* width of bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_WIDTH 5
/* defauwt vawue of bitfiewd wss_key_addw[4:0] */
#define HW_ATW_WPF_WSS_KEY_ADDW_DEFAUWT 0x0

/* wx wss_key_ww_data[1f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_key_ww_data[1f:0]".
 * powt="pif_wpf_wss_key_ww_data_i[31:0]"
 */

/* wegistew addwess fow bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_ADW 0x000054d4
/* bitmask fow bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_MSK 0xffffffff
/* invewted bitmask fow bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_MSKN 0x00000000
/* wowew bit position of bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_SHIFT 0
/* width of bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_WIDTH 32
/* defauwt vawue of bitfiewd wss_key_ww_data[1f:0] */
#define HW_ATW_WPF_WSS_KEY_WW_DATA_DEFAUWT 0x0

/* wx wss_key_ww_en_i bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_key_ww_en_i".
 * powt="pif_wpf_wss_key_ww_en_i"
 */

/* wegistew addwess fow bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_ADW 0x000054d0
/* bitmask fow bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_MSK 0x00000020
/* invewted bitmask fow bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_MSKN 0xffffffdf
/* wowew bit position of bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_SHIFT 5
/* width of bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_WIDTH 1
/* defauwt vawue of bitfiewd wss_key_ww_en_i */
#define HW_ATW_WPF_WSS_KEY_WW_ENI_DEFAUWT 0x0

/* wx wss_wediw_addw[3:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_wediw_addw[3:0]".
 * powt="pif_wpf_wss_wediw_addw_i[3:0]"
 */

/* wegistew addwess fow bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_ADW 0x000054e0
/* bitmask fow bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_MSK 0x0000000f
/* invewted bitmask fow bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_MSKN 0xfffffff0
/* wowew bit position of bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_SHIFT 0
/* width of bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_WIDTH 4
/* defauwt vawue of bitfiewd wss_wediw_addw[3:0] */
#define HW_ATW_WPF_WSS_WEDIW_ADDW_DEFAUWT 0x0

/* wx wss_wediw_ww_data[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_wediw_ww_data[f:0]".
 * powt="pif_wpf_wss_wediw_ww_data_i[15:0]"
 */

/* wegistew addwess fow bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_ADW 0x000054e4
/* bitmask fow bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_MSK 0x0000ffff
/* invewted bitmask fow bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_MSKN 0xffff0000
/* wowew bit position of bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_SHIFT 0
/* width of bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_WIDTH 16
/* defauwt vawue of bitfiewd wss_wediw_ww_data[f:0] */
#define HW_ATW_WPF_WSS_WEDIW_WW_DATA_DEFAUWT 0x0

/* wx wss_wediw_ww_en_i bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wss_wediw_ww_en_i".
 * powt="pif_wpf_wss_wediw_ww_en_i"
 */

/* wegistew addwess fow bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_ADW 0x000054e0
/* bitmask fow bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_MSK 0x00000010
/* invewted bitmask fow bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_MSKN 0xffffffef
/* wowew bit position of bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_SHIFT 4
/* width of bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_WIDTH 1
/* defauwt vawue of bitfiewd wss_wediw_ww_en_i */
#define HW_ATW_WPF_WSS_WEDIW_WW_ENI_DEFAUWT 0x0

/* wx tpo_wpf_sys_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tpo_wpf_sys_woopback".
 * powt="pif_wpf_tpo_pkt_sys_wbk_i"
 */

/* wegistew addwess fow bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_ADW 0x00005000
/* bitmask fow bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_MSK 0x00000100
/* invewted bitmask fow bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_MSKN 0xfffffeff
/* wowew bit position of bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_SHIFT 8
/* width of bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_WIDTH 1
/* defauwt vawue of bitfiewd tpo_wpf_sys_woopback */
#define HW_ATW_WPF_TPO_WPF_SYS_WBK_DEFAUWT 0x0

/* wx vw_innew_tpid[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "vw_innew_tpid[f:0]".
 * powt="pif_wpf_vw_innew_tpid_i[15:0]"
 */

/* wegistew addwess fow bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_ADW 0x00005284
/* bitmask fow bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_MSK 0x0000ffff
/* invewted bitmask fow bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_MSKN 0xffff0000
/* wowew bit position of bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_SHIFT 0
/* width of bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_WIDTH 16
/* defauwt vawue of bitfiewd vw_innew_tpid[f:0] */
#define HW_ATW_WPF_VW_INNEW_TPID_DEFAUWT 0x8100

/* wx vw_outew_tpid[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "vw_outew_tpid[f:0]".
 * powt="pif_wpf_vw_outew_tpid_i[15:0]"
 */

/* wegistew addwess fow bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_ADW 0x00005284
/* bitmask fow bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_MSK 0xffff0000
/* invewted bitmask fow bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_MSKN 0x0000ffff
/* wowew bit position of bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_SHIFT 16
/* width of bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_WIDTH 16
/* defauwt vawue of bitfiewd vw_outew_tpid[f:0] */
#define HW_ATW_WPF_VW_OUTEW_TPID_DEFAUWT 0x88a8

/* wx vw_pwomis_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "vw_pwomis_mode".
 * powt="pif_wpf_vw_pwomis_mode_i"
 */

/* wegistew addwess fow bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_ADW 0x00005280
/* bitmask fow bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_MSK 0x00000002
/* invewted bitmask fow bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_MSKN 0xfffffffd
/* wowew bit position of bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_SHIFT 1
/* width of bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_WIDTH 1
/* defauwt vawue of bitfiewd vw_pwomis_mode */
#define HW_ATW_WPF_VW_PWOMIS_MODE_DEFAUWT 0x0

/* WX vw_accept_untagged_mode Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_accept_untagged_mode".
 * POWT="pif_wpf_vw_accept_untagged_i"
 */

/* Wegistew addwess fow bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_ADW 0x00005280
/* Bitmask fow bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_MSK 0x00000004
/* Invewted bitmask fow bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_MSKN 0xFFFFFFFB
/* Wowew bit position of bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_SHIFT 2
/* Width of bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_WIDTH 1
/* Defauwt vawue of bitfiewd vw_accept_untagged_mode */
#define HW_ATW_WPF_VW_ACCEPT_UNTAGGED_MODE_DEFAUWT 0x0

/* wX vw_untagged_act[2:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_untagged_act[2:0]".
 * POWT="pif_wpf_vw_untagged_act_i[2:0]"
 */

/* Wegistew addwess fow bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_ADW 0x00005280
/* Bitmask fow bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_MSK 0x00000038
/* Invewted bitmask fow bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_MSKN 0xFFFFFFC7
/* Wowew bit position of bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_SHIFT 3
/* Width of bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_WIDTH 3
/* Defauwt vawue of bitfiewd vw_untagged_act[2:0] */
#define HW_ATW_WPF_VW_UNTAGGED_ACT_DEFAUWT 0x0

/* WX vw_en{F} Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_en{F}".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 15]
 * POWT="pif_wpf_vw_en_i[0]"
 */

/* Wegistew addwess fow bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_MSK 0x80000000
/* Invewted bitmask fow bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_MSKN 0x7FFFFFFF
/* Wowew bit position of bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_SHIFT 31
/* Width of bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_WIDTH 1
/* Defauwt vawue of bitfiewd vw_en{F} */
#define HW_ATW_WPF_VW_EN_F_DEFAUWT 0x0

/* WX vw_act{F}[2:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_act{F}[2:0]".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 15]
 * POWT="pif_wpf_vw_act0_i[2:0]"
 */

/* Wegistew addwess fow bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_MSK 0x00070000
/* Invewted bitmask fow bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_MSKN 0xFFF8FFFF
/* Wowew bit position of bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_SHIFT 16
/* Width of bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_WIDTH 3
/* Defauwt vawue of bitfiewd vw_act{F}[2:0] */
#define HW_ATW_WPF_VW_ACT_F_DEFAUWT 0x0

/* WX vw_id{F}[B:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_id{F}[B:0]".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 15]
 * POWT="pif_wpf_vw_id0_i[11:0]"
 */

/* Wegistew addwess fow bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_MSK 0x00000FFF
/* Invewted bitmask fow bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_MSKN 0xFFFFF000
/* Wowew bit position of bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_SHIFT 0
/* Width of bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_WIDTH 12
/* Defauwt vawue of bitfiewd vw_id{F}[B:0] */
#define HW_ATW_WPF_VW_ID_F_DEFAUWT 0x0

/* WX vw_wxq_en{F} Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_wxq{F}".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 15]
 * POWT="pif_wpf_vw_wxq_en_i"
 */

/* Wegistew addwess fow bitfiewd vw_wxq_en{F} */
#define HW_ATW_WPF_VW_WXQ_EN_F_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd vw_wxq_en{F} */
#define HW_ATW_WPF_VW_WXQ_EN_F_MSK 0x10000000
/* Invewted bitmask fow bitfiewd vw_wxq_en{F}[ */
#define HW_ATW_WPF_VW_WXQ_EN_F_MSKN 0xEFFFFFFF
/* Wowew bit position of bitfiewd vw_wxq_en{F} */
#define HW_ATW_WPF_VW_WXQ_EN_F_SHIFT 28
/* Width of bitfiewd vw_wxq_en{F} */
#define HW_ATW_WPF_VW_WXQ_EN_F_WIDTH 1
/* Defauwt vawue of bitfiewd vw_wxq_en{F} */
#define HW_ATW_WPF_VW_WXQ_EN_F_DEFAUWT 0x0

/* WX vw_wxq{F}[4:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "vw_wxq{F}[4:0]".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 15]
 * POWT="pif_wpf_vw_wxq0_i[4:0]"
 */

/* Wegistew addwess fow bitfiewd vw_wxq{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd vw_wxq{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_MSK 0x01F00000
/* Invewted bitmask fow bitfiewd vw_wxq{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_MSKN 0xFE0FFFFF
/* Wowew bit position of bitfiewd vw_wxq{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_SHIFT 20
/* Width of bitfiewd vw_wxw{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_WIDTH 5
/* Defauwt vawue of bitfiewd vw_wxq{F}[4:0] */
#define HW_ATW_WPF_VW_WXQ_F_DEFAUWT 0x0

/* wx et_en{f} bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_en{f}".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_en_i[0]"
 */

/* wegistew addwess fow bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_MSK 0x80000000
/* invewted bitmask fow bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_MSKN 0x7fffffff
/* wowew bit position of bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_SHIFT 31
/* width of bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_WIDTH 1
/* defauwt vawue of bitfiewd et_en{f} */
#define HW_ATW_WPF_ET_ENF_DEFAUWT 0x0

/* wx et_up{f}_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_up{f}_en".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_up_en_i[0]"
 */

/* wegistew addwess fow bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_MSK 0x40000000
/* invewted bitmask fow bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_MSKN 0xbfffffff
/* wowew bit position of bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_SHIFT 30
/* width of bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_WIDTH 1
/* defauwt vawue of bitfiewd et_up{f}_en */
#define HW_ATW_WPF_ET_UPFEN_DEFAUWT 0x0

/* wx et_wxq{f}_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_wxq{f}_en".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_wxq_en_i[0]"
 */

/* wegistew addwess fow bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_MSK 0x20000000
/* invewted bitmask fow bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_MSKN 0xdfffffff
/* wowew bit position of bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_SHIFT 29
/* width of bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_WIDTH 1
/* defauwt vawue of bitfiewd et_wxq{f}_en */
#define HW_ATW_WPF_ET_WXQFEN_DEFAUWT 0x0

/* wx et_up{f}[2:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_up{f}[2:0]".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_up0_i[2:0]"
 */

/* wegistew addwess fow bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_MSK 0x1c000000
/* invewted bitmask fow bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_MSKN 0xe3ffffff
/* wowew bit position of bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_SHIFT 26
/* width of bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_WIDTH 3
/* defauwt vawue of bitfiewd et_up{f}[2:0] */
#define HW_ATW_WPF_ET_UPF_DEFAUWT 0x0

/* wx et_wxq{f}[4:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_wxq{f}[4:0]".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_wxq0_i[4:0]"
 */

/* wegistew addwess fow bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_MSK 0x01f00000
/* invewted bitmask fow bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_MSKN 0xfe0fffff
/* wowew bit position of bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_SHIFT 20
/* width of bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_WIDTH 5
/* defauwt vawue of bitfiewd et_wxq{f}[4:0] */
#define HW_ATW_WPF_ET_WXQF_DEFAUWT 0x0

/* wx et_mng_wxq{f} bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_mng_wxq{f}".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_mng_wxq_i[0]"
 */

/* wegistew addwess fow bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_MSK 0x00080000
/* invewted bitmask fow bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_MSKN 0xfff7ffff
/* wowew bit position of bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_SHIFT 19
/* width of bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_WIDTH 1
/* defauwt vawue of bitfiewd et_mng_wxq{f} */
#define HW_ATW_WPF_ET_MNG_WXQF_DEFAUWT 0x0

/* wx et_act{f}[2:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_act{f}[2:0]".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_act0_i[2:0]"
 */

/* wegistew addwess fow bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_MSK 0x00070000
/* invewted bitmask fow bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_MSKN 0xfff8ffff
/* wowew bit position of bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_SHIFT 16
/* width of bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_WIDTH 3
/* defauwt vawue of bitfiewd et_act{f}[2:0] */
#define HW_ATW_WPF_ET_ACTF_DEFAUWT 0x0

/* wx et_vaw{f}[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "et_vaw{f}[f:0]".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_et_vaw0_i[15:0]"
 */

/* wegistew addwess fow bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_ADW(fiwtew) (0x00005300 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_MSK 0x0000ffff
/* invewted bitmask fow bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_MSKN 0xffff0000
/* wowew bit position of bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_SHIFT 0
/* width of bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_WIDTH 16
/* defauwt vawue of bitfiewd et_vaw{f}[f:0] */
#define HW_ATW_WPF_ET_VAWF_DEFAUWT 0x0

/* WX w3_w4_en{F} Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "w3_w4_en{F}".
 * Pawametew: fiwtew {F} | stwide size 0x4 | wange [0, 7]
 * POWT="pif_wpf_w3_w4_en_i[0]"
 */

#define HW_ATW_WPF_W3_WEG_CTWW_ADW(fiwtew) (0x00005380 + (fiwtew) * 0x4)

/* WX wpf_w3_sa{D}[1F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "w3_sa{D}[1F:0]".
 * Pawametew: wocation {D} | stwide size 0x4 | wange [0, 7]
 * POWT="pif_wpf_w3_sa0_i[31:0]"
 */

/* Wegistew addwess fow bitfiewd pif_wpf_w3_sa0_i[31:0] */
#define HW_ATW_WPF_W3_SWCA_ADW(fiwtew) (0x000053B0 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd w3_sa0[1F:0] */
#define HW_ATW_WPF_W3_SWCA_MSK 0xFFFFFFFFu
/* Invewted bitmask fow bitfiewd w3_sa0[1F:0] */
#define HW_ATW_WPF_W3_SWCA_MSKN 0xFFFFFFFFu
/* Wowew bit position of bitfiewd w3_sa0[1F:0] */
#define HW_ATW_WPF_W3_SWCA_SHIFT 0
/* Width of bitfiewd w3_sa0[1F:0] */
#define HW_ATW_WPF_W3_SWCA_WIDTH 32
/* Defauwt vawue of bitfiewd w3_sa0[1F:0] */
#define HW_ATW_WPF_W3_SWCA_DEFAUWT 0x0

/* WX wpf_w3_da{D}[1F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "w3_da{D}[1F:0]".
 * Pawametew: wocation {D} | stwide size 0x4 | wange [0, 7]
 * POWT="pif_wpf_w3_da0_i[31:0]"
 */

 /* Wegistew addwess fow bitfiewd pif_wpf_w3_da0_i[31:0] */
#define HW_ATW_WPF_W3_DSTA_ADW(fiwtew) (0x000053D0 + (fiwtew) * 0x4)
/* Bitmask fow bitfiewd w3_da0[1F:0] */
#define HW_ATW_WPF_W3_DSTA_MSK 0xFFFFFFFFu
/* Invewted bitmask fow bitfiewd w3_da0[1F:0] */
#define HW_ATW_WPF_W3_DSTA_MSKN 0xFFFFFFFFu
/* Wowew bit position of bitfiewd w3_da0[1F:0] */
#define HW_ATW_WPF_W3_DSTA_SHIFT 0
/* Width of bitfiewd w3_da0[1F:0] */
#define HW_ATW_WPF_W3_DSTA_WIDTH 32
/* Defauwt vawue of bitfiewd w3_da0[1F:0] */
#define HW_ATW_WPF_W3_DSTA_DEFAUWT 0x0

/* WX w4_sp{D}[F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "w4_sp{D}[F:0]".
 * Pawametew: swcpowt {D} | stwide size 0x4 | wange [0, 7]
 * POWT="pif_wpf_w4_sp0_i[15:0]"
 */

/* Wegistew addwess fow bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_ADW(swcpowt) (0x00005400u + (swcpowt) * 0x4)
/* Bitmask fow bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_MSK 0x0000FFFFu
/* Invewted bitmask fow bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_MSKN 0xFFFF0000u
/* Wowew bit position of bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_SHIFT 0
/* Width of bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_WIDTH 16
/* Defauwt vawue of bitfiewd w4_sp{D}[F:0] */
#define HW_ATW_WPF_W4_SPD_DEFAUWT 0x0

/* WX w4_dp{D}[F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "w4_dp{D}[F:0]".
 * Pawametew: destpowt {D} | stwide size 0x4 | wange [0, 7]
 * POWT="pif_wpf_w4_dp0_i[15:0]"
 */

/* Wegistew addwess fow bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_ADW(destpowt) (0x00005420u + (destpowt) * 0x4)
/* Bitmask fow bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_MSK 0x0000FFFFu
/* Invewted bitmask fow bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_MSKN 0xFFFF0000u
/* Wowew bit position of bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_SHIFT 0
/* Width of bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_WIDTH 16
/* Defauwt vawue of bitfiewd w4_dp{D}[F:0] */
#define HW_ATW_WPF_W4_DPD_DEFAUWT 0x0

/* wx ipv4_chk_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "ipv4_chk_en".
 * powt="pif_wpo_ipv4_chk_en_i"
 */

/* wegistew addwess fow bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_ADW 0x00005580
/* bitmask fow bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_MSK 0x00000002
/* invewted bitmask fow bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_MSKN 0xfffffffd
/* wowew bit position of bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_SHIFT 1
/* width of bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_WIDTH 1
/* defauwt vawue of bitfiewd ipv4_chk_en */
#define HW_ATW_WPO_IPV4CHK_EN_DEFAUWT 0x0

/* wx desc{d}_vw_stwip bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_vw_stwip".
 * pawametew: descwiptow {d} | stwide size 0x20 | wange [0, 31]
 * powt="pif_wpo_desc_vw_stwip_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_ADW(descwiptow) \
	(0x00005b08 + (descwiptow) * 0x20)
/* bitmask fow bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_MSK 0x20000000
/* invewted bitmask fow bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_MSKN 0xdfffffff
/* wowew bit position of bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_SHIFT 29
/* width of bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_WIDTH 1
/* defauwt vawue of bitfiewd desc{d}_vw_stwip */
#define HW_ATW_WPO_DESCDVW_STWIP_DEFAUWT 0x0

/* wx w4_chk_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w4_chk_en".
 * powt="pif_wpo_w4_chk_en_i"
 */

/* wegistew addwess fow bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_ADW 0x00005580
/* bitmask fow bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_MSK 0x00000001
/* invewted bitmask fow bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_MSKN 0xfffffffe
/* wowew bit position of bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_SHIFT 0
/* width of bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_WIDTH 1
/* defauwt vawue of bitfiewd w4_chk_en */
#define HW_ATW_WPOW4CHK_EN_DEFAUWT 0x0

/* WX outew_vw_ins_mode Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "outew_vw_ins_mode".
 * POWT="pif_wpo_outew_vw_mode_i"
 */

/* Wegistew addwess fow bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_ADW 0x00005580
/* Bitmask fow bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_MSK 0x00000004
/* Invewted bitmask fow bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_MSKN 0xFFFFFFFB
/* Wowew bit position of bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_SHIFT 2
/* Width of bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_WIDTH 1
/* Defauwt vawue of bitfiewd outew_vw_ins_mode */
#define HW_ATW_WPO_OUTEW_VW_INS_MODE_DEFAUWT 0x0

/* wx weg_wes_dsbw bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "weg_wes_dsbw".
 * powt="pif_wx_weg_wes_dsbw_i"
 */

/* wegistew addwess fow bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_ADW 0x00005000
/* bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_MSK 0x20000000
/* invewted bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_MSKN 0xdfffffff
/* wowew bit position of bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_SHIFT 29
/* width of bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_WIDTH 1
/* defauwt vawue of bitfiewd weg_wes_dsbw */
#define HW_ATW_WX_WEG_WES_DSBW_DEFAUWT 0x1

/* tx dca{d}_cpuid[7:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca{d}_cpuid[7:0]".
 * pawametew: dca {d} | stwide size 0x4 | wange [0, 31]
 * powt="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* wegistew addwess fow bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_ADW(dca) (0x00008400 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_MSK 0x000000ff
/* invewted bitmask fow bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_MSKN 0xffffff00
/* wowew bit position of bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_SHIFT 0
/* width of bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_WIDTH 8
/* defauwt vawue of bitfiewd dca{d}_cpuid[7:0] */
#define HW_ATW_TDM_DCADCPUID_DEFAUWT 0x0

/* tx wso_en[1f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wso_en[1f:0]".
 * powt="pif_tdm_wso_en_i[31:0]"
 */

/* wegistew addwess fow bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_ADW 0x00007810
/* bitmask fow bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_MSK 0xffffffff
/* invewted bitmask fow bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_MSKN 0x00000000
/* wowew bit position of bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_SHIFT 0
/* width of bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_WIDTH 32
/* defauwt vawue of bitfiewd wso_en[1f:0] */
#define HW_ATW_TDM_WSO_EN_DEFAUWT 0x0

/* tx dca_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca_en".
 * powt="pif_tdm_dca_en_i"
 */

/* wegistew addwess fow bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_ADW 0x00008480
/* bitmask fow bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_SHIFT 31
/* width of bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca_en */
#define HW_ATW_TDM_DCA_EN_DEFAUWT 0x1

/* tx dca_mode[3:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca_mode[3:0]".
 * powt="pif_tdm_dca_mode_i[3:0]"
 */

/* wegistew addwess fow bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_ADW 0x00008480
/* bitmask fow bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_MSK 0x0000000f
/* invewted bitmask fow bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_MSKN 0xfffffff0
/* wowew bit position of bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_SHIFT 0
/* width of bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_WIDTH 4
/* defauwt vawue of bitfiewd dca_mode[3:0] */
#define HW_ATW_TDM_DCA_MODE_DEFAUWT 0x0

/* tx dca{d}_desc_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dca{d}_desc_en".
 * pawametew: dca {d} | stwide size 0x4 | wange [0, 31]
 * powt="pif_tdm_dca_desc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_ADW(dca) (0x00008400 + (dca) * 0x4)
/* bitmask fow bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_SHIFT 31
/* width of bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_WIDTH 1
/* defauwt vawue of bitfiewd dca{d}_desc_en */
#define HW_ATW_TDM_DCADDESC_EN_DEFAUWT 0x0

/* tx desc{d}_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_en".
 * pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 * powt="pif_tdm_desc_en_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_ADW(descwiptow) (0x00007c08 + (descwiptow) * 0x40)
/* bitmask fow bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_MSK 0x80000000
/* invewted bitmask fow bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_MSKN 0x7fffffff
/* wowew bit position of bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_SHIFT 31
/* width of bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_WIDTH 1
/* defauwt vawue of bitfiewd desc{d}_en */
#define HW_ATW_TDM_DESCDEN_DEFAUWT 0x0

/* tx desc{d}_hd[c:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_hd[c:0]".
 * pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 * powt="tdm_pif_desc0_hd_o[12:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_TDM_DESCDHD_ADW(descwiptow) (0x00007c0c + (descwiptow) * 0x40)
/* bitmask fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_TDM_DESCDHD_MSK 0x00001fff
/* invewted bitmask fow bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_TDM_DESCDHD_MSKN 0xffffe000
/* wowew bit position of bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_TDM_DESCDHD_SHIFT 0
/* width of bitfiewd desc{d}_hd[c:0] */
#define HW_ATW_TDM_DESCDHD_WIDTH 13

/* tx desc{d}_wen[9:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_wen[9:0]".
 * pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 * powt="pif_tdm_desc0_wen_i[9:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_ADW(descwiptow) (0x00007c08 + (descwiptow) * 0x40)
/* bitmask fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_MSK 0x00001ff8
/* invewted bitmask fow bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_MSKN 0xffffe007
/* wowew bit position of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_SHIFT 3
/* width of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_WIDTH 10
/* defauwt vawue of bitfiewd desc{d}_wen[9:0] */
#define HW_ATW_TDM_DESCDWEN_DEFAUWT 0x0

/* tx int_desc_wwb_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "int_desc_wwb_en".
 * powt="pif_tdm_int_desc_wwb_en_i"
 */

/* wegistew addwess fow bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_ADW 0x00007b40
/* bitmask fow bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_MSK 0x00000002
/* invewted bitmask fow bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_MSKN 0xfffffffd
/* wowew bit position of bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_SHIFT 1
/* width of bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_WIDTH 1
/* defauwt vawue of bitfiewd int_desc_wwb_en */
#define HW_ATW_TDM_INT_DESC_WWB_EN_DEFAUWT 0x0

/* tx desc{d}_wwb_thwesh[6:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{d}_wwb_thwesh[6:0]".
 * pawametew: descwiptow {d} | stwide size 0x40 | wange [0, 31]
 * powt="pif_tdm_desc0_wwb_thwesh_i[6:0]"
 */

/* wegistew addwess fow bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_ADW(descwiptow) \
	(0x00007c18 + (descwiptow) * 0x40)
/* bitmask fow bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_MSK 0x00007f00
/* invewted bitmask fow bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_MSKN 0xffff80ff
/* wowew bit position of bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_SHIFT 8
/* width of bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_WIDTH 7
/* defauwt vawue of bitfiewd desc{d}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESCDWWB_THWESH_DEFAUWT 0x0

/* tx wso_tcp_fwag_fiwst[b:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wso_tcp_fwag_fiwst[b:0]".
 * powt="pif_thm_wso_tcp_fwag_fiwst_i[11:0]"
 */

/* wegistew addwess fow bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_ADW 0x00007820
/* bitmask fow bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_MSK 0x00000fff
/* invewted bitmask fow bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_MSKN 0xfffff000
/* wowew bit position of bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_SHIFT 0
/* width of bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_WIDTH 12
/* defauwt vawue of bitfiewd wso_tcp_fwag_fiwst[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_FIWST_DEFAUWT 0x0

/* tx wso_tcp_fwag_wast[b:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wso_tcp_fwag_wast[b:0]".
 * powt="pif_thm_wso_tcp_fwag_wast_i[11:0]"
 */

/* wegistew addwess fow bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_ADW 0x00007824
/* bitmask fow bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_MSK 0x00000fff
/* invewted bitmask fow bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_MSKN 0xfffff000
/* wowew bit position of bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_SHIFT 0
/* width of bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_WIDTH 12
/* defauwt vawue of bitfiewd wso_tcp_fwag_wast[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_WAST_DEFAUWT 0x0

/* tx wso_tcp_fwag_mid[b:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wso_tcp_fwag_mid[b:0]".
 * powt="pif_thm_wso_tcp_fwag_mid_i[11:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_ADW 0x00005598
/* Bitmask fow bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_MSK 0xFFFFFFFF
/* Invewted bitmask fow bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_MSKN 0x00000000
/* Wowew bit position of bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_SHIFT 0
/* Width of bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_WIDTH 32
/* Defauwt vawue of bitfiewd wwo_wsc_max[1F:0] */
#define HW_ATW_WPO_WWO_WSC_MAX_DEFAUWT 0x0

/* WX wwo_en[1F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_en[1F:0]".
 * POWT="pif_wpo_wwo_en_i[31:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_ADW 0x00005590
/* Bitmask fow bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_MSK 0xFFFFFFFF
/* Invewted bitmask fow bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_MSKN 0x00000000
/* Wowew bit position of bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_SHIFT 0
/* Width of bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_WIDTH 32
/* Defauwt vawue of bitfiewd wwo_en[1F:0] */
#define HW_ATW_WPO_WWO_EN_DEFAUWT 0x0

/* WX wwo_ptopt_en Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_ptopt_en".
 * POWT="pif_wpo_wwo_ptopt_en_i"
 */

/* Wegistew addwess fow bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_ADW 0x00005594
/* Bitmask fow bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_MSK 0x00008000
/* Invewted bitmask fow bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_MSKN 0xFFFF7FFF
/* Wowew bit position of bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_SHIFT 15
/* Width of bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_WIDTH 1
/* Defauwt vawue of bitfiewd wwo_ptopt_en */
#define HW_ATW_WPO_WWO_PTOPT_EN_DEFAWT 0x1

/* WX wwo_q_ses_wmt Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_q_ses_wmt".
 * POWT="pif_wpo_wwo_q_ses_wmt_i[1:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_ADW 0x00005594
/* Bitmask fow bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_MSK 0x00003000
/* Invewted bitmask fow bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_MSKN 0xFFFFCFFF
/* Wowew bit position of bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_SHIFT 12
/* Width of bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_WIDTH 2
/* Defauwt vawue of bitfiewd wwo_q_ses_wmt */
#define HW_ATW_WPO_WWO_QSES_WMT_DEFAUWT 0x1

/* WX wwo_tot_dsc_wmt[1:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_tot_dsc_wmt[1:0]".
 * POWT="pif_wpo_wwo_tot_dsc_wmt_i[1:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_ADW 0x00005594
/* Bitmask fow bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_MSK 0x00000060
/* Invewted bitmask fow bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_MSKN 0xFFFFFF9F
/* Wowew bit position of bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_SHIFT 5
/* Width of bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_WIDTH 2
/* Defauwt vawue of bitfiewd wwo_tot_dsc_wmt[1:0] */
#define HW_ATW_WPO_WWO_TOT_DSC_WMT_DEFAWT 0x1

/* WX wwo_pkt_min[4:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_pkt_min[4:0]".
 * POWT="pif_wpo_wwo_pkt_min_i[4:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_ADW 0x00005594
/* Bitmask fow bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_MSK 0x0000001F
/* Invewted bitmask fow bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_MSKN 0xFFFFFFE0
/* Wowew bit position of bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_SHIFT 0
/* Width of bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_WIDTH 5
/* Defauwt vawue of bitfiewd wwo_pkt_min[4:0] */
#define HW_ATW_WPO_WWO_PKT_MIN_DEFAUWT 0x8

/* Width of bitfiewd wwo{W}_des_max[1:0] */
#define HW_ATW_WPO_WWO_WDES_MAX_WIDTH 2
/* Defauwt vawue of bitfiewd wwo{W}_des_max[1:0] */
#define HW_ATW_WPO_WWO_WDES_MAX_DEFAUWT 0x0

/* WX wwo_tb_div[11:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_tb_div[11:0]".
 * POWT="pif_wpo_wwo_tb_div_i[11:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_ADW 0x00005620
/* Bitmask fow bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_MSK 0xFFF00000
/* Invewted bitmask fow bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_MSKN 0x000FFFFF
/* Wowew bit position of bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_SHIFT 20
/* Width of bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_WIDTH 12
/* Defauwt vawue of bitfiewd wwo_tb_div[11:0] */
#define HW_ATW_WPO_WWO_TB_DIV_DEFAUWT 0xC35

/* WX wwo_ina_ivaw[9:0] Bitfiewd Definitions
 *   Pwepwocessow definitions fow the bitfiewd "wwo_ina_ivaw[9:0]".
 *   POWT="pif_wpo_wwo_ina_ivaw_i[9:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_ADW 0x00005620
/* Bitmask fow bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_MSK 0x000FFC00
/* Invewted bitmask fow bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_MSKN 0xFFF003FF
/* Wowew bit position of bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_SHIFT 10
/* Width of bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_WIDTH 10
/* Defauwt vawue of bitfiewd wwo_ina_ivaw[9:0] */
#define HW_ATW_WPO_WWO_INA_IVAW_DEFAUWT 0xA

/* WX wwo_max_ivaw[9:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wwo_max_ivaw[9:0]".
 * POWT="pif_wpo_wwo_max_ivaw_i[9:0]"
 */

/* Wegistew addwess fow bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_ADW 0x00005620
/* Bitmask fow bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_MSK 0x000003FF
/* Invewted bitmask fow bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_MSKN 0xFFFFFC00
/* Wowew bit position of bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_SHIFT 0
/* Width of bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_WIDTH 10
/* Defauwt vawue of bitfiewd wwo_max_ivaw[9:0] */
#define HW_ATW_WPO_WWO_MAX_IVAW_DEFAUWT 0x19

/* TX dca{D}_cpuid[7:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "dca{D}_cpuid[7:0]".
 * Pawametew: DCA {D} | stwide size 0x4 | wange [0, 31]
 * POWT="pif_tdm_dca0_cpuid_i[7:0]"
 */

/* Wegistew addwess fow bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_ADW(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask fow bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_MSK 0x000000FF
/* Invewted bitmask fow bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_MSKN 0xFFFFFF00
/* Wowew bit position of bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_SHIFT 0
/* Width of bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_WIDTH 8
/* Defauwt vawue of bitfiewd dca{D}_cpuid[7:0] */
#define HW_ATW_TDM_DCA_DCPUID_DEFAUWT 0x0

/* TX dca{D}_desc_en Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "dca{D}_desc_en".
 * Pawametew: DCA {D} | stwide size 0x4 | wange [0, 31]
 * POWT="pif_tdm_dca_desc_en_i[0]"
 */

/* Wegistew addwess fow bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_ADW(dca) (0x00008400 + (dca) * 0x4)
/* Bitmask fow bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_MSK 0x80000000
/* Invewted bitmask fow bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_MSKN 0x7FFFFFFF
/* Wowew bit position of bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_SHIFT 31
/* Width of bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_WIDTH 1
/* Defauwt vawue of bitfiewd dca{D}_desc_en */
#define HW_ATW_TDM_DCA_DDESC_EN_DEFAUWT 0x0

/* TX desc{D}_en Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "desc{D}_en".
 * Pawametew: descwiptow {D} | stwide size 0x40 | wange [0, 31]
 * POWT="pif_tdm_desc_en_i[0]"
 */

/* Wegistew addwess fow bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_ADW(descwiptow) (0x00007C08 + (descwiptow) * 0x40)
/* Bitmask fow bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_MSK 0x80000000
/* Invewted bitmask fow bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_MSKN 0x7FFFFFFF
/* Wowew bit position of bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_SHIFT 31
/* Width of bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_WIDTH 1
/* Defauwt vawue of bitfiewd desc{D}_en */
#define HW_ATW_TDM_DESC_DEN_DEFAUWT 0x0

/* TX desc{D}_hd[C:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "desc{D}_hd[C:0]".
 * Pawametew: descwiptow {D} | stwide size 0x40 | wange [0, 31]
 * POWT="tdm_pif_desc0_hd_o[12:0]"
 */

/* Wegistew addwess fow bitfiewd desc{D}_hd[C:0] */
#define HW_ATW_TDM_DESC_DHD_ADW(descwiptow) (0x00007C0C + (descwiptow) * 0x40)
/* Bitmask fow bitfiewd desc{D}_hd[C:0] */
#define HW_ATW_TDM_DESC_DHD_MSK 0x00001FFF
/* Invewted bitmask fow bitfiewd desc{D}_hd[C:0] */
#define HW_ATW_TDM_DESC_DHD_MSKN 0xFFFFE000
/* Wowew bit position of bitfiewd desc{D}_hd[C:0] */
#define HW_ATW_TDM_DESC_DHD_SHIFT 0
/* Width of bitfiewd desc{D}_hd[C:0] */
#define HW_ATW_TDM_DESC_DHD_WIDTH 13

/* TX desc{D}_wen[9:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "desc{D}_wen[9:0]".
 * Pawametew: descwiptow {D} | stwide size 0x40 | wange [0, 31]
 * POWT="pif_tdm_desc0_wen_i[9:0]"
 */

/* Wegistew addwess fow bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_ADW(descwiptow) (0x00007C08 + (descwiptow) * 0x40)
/* Bitmask fow bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_MSK 0x00001FF8
/* Invewted bitmask fow bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_MSKN 0xFFFFE007
/* Wowew bit position of bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_SHIFT 3
/* Width of bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_WIDTH 10
/* Defauwt vawue of bitfiewd desc{D}_wen[9:0] */
#define HW_ATW_TDM_DESC_DWEN_DEFAUWT 0x0

/* TX desc{D}_wwb_thwesh[6:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "desc{D}_wwb_thwesh[6:0]".
 * Pawametew: descwiptow {D} | stwide size 0x40 | wange [0, 31]
 * POWT="pif_tdm_desc0_wwb_thwesh_i[6:0]"
 */

/* Wegistew addwess fow bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_ADW(descwiptow) \
	(0x00007C18 + (descwiptow) * 0x40)
/* Bitmask fow bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_MSK 0x00007F00
/* Invewted bitmask fow bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_MSKN 0xFFFF80FF
/* Wowew bit position of bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_SHIFT 8
/* Width of bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_WIDTH 7
/* Defauwt vawue of bitfiewd desc{D}_wwb_thwesh[6:0] */
#define HW_ATW_TDM_DESC_DWWB_THWESH_DEFAUWT 0x0

/* TX tdm_int_mod_en Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "tdm_int_mod_en".
 * POWT="pif_tdm_int_mod_en_i"
 */

/* Wegistew addwess fow bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_ADW 0x00007B40
/* Bitmask fow bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_MSK 0x00000010
/* Invewted bitmask fow bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_MSKN 0xFFFFFFEF
/* Wowew bit position of bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_SHIFT 4
/* Width of bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_WIDTH 1
/* Defauwt vawue of bitfiewd tdm_int_mod_en */
#define HW_ATW_TDM_INT_MOD_EN_DEFAUWT 0x0

/* TX wso_tcp_fwag_mid[B:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wso_tcp_fwag_mid[B:0]".
 * POWT="pif_thm_wso_tcp_fwag_mid_i[11:0]"
 */
/* wegistew addwess fow bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_ADW 0x00007820
/* bitmask fow bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_MSK 0x0fff0000
/* invewted bitmask fow bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_MSKN 0xf000ffff
/* wowew bit position of bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_SHIFT 16
/* width of bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_WIDTH 12
/* defauwt vawue of bitfiewd wso_tcp_fwag_mid[b:0] */
#define HW_ATW_THM_WSO_TCP_FWAG_MID_DEFAUWT 0x0

/* tx tx_tc_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_tc_mode".
 * powt="pif_tpb_tx_tc_mode_i,pif_tps_tx_tc_mode_i"
 */

/* wegistew addwess fow bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_ADDW 0x00007900
/* bitmask fow bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_MSK 0x00000100
/* invewted bitmask fow bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_MSKN 0xFFFFFEFF
/* wowew bit position of bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_SHIFT 8
/* width of bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_WIDTH 1
/* defauwt vawue of bitfiewd tx_tc_mode */
#define HW_ATW_TPB_TX_TC_MODE_DEFAUWT 0x0

/* tx tx_desc_wate_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_desc_wate_mode".
 * powt="pif_tps_desc_wate_mode_i"
 */

/* wegistew addwess fow bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_ADW 0x00007900
/* bitmask fow bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_MSK 0x00000080
/* invewted bitmask fow bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_MSKN 0xFFFFFF7F
/* wowew bit position of bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_SHIFT 7
/* width of bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_WIDTH 1
/* defauwt vawue of bitfiewd tx_desc_wate_mode */
#define HW_ATW_TPS_TX_DESC_WATE_MODE_DEFAUWT 0x0

/* tx tx_buf_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_buf_en".
 * powt="pif_tpb_tx_buf_en_i"
 */

/* wegistew addwess fow bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_ADW 0x00007900
/* bitmask fow bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_MSK 0x00000001
/* invewted bitmask fow bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_MSKN 0xfffffffe
/* wowew bit position of bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_SHIFT 0
/* width of bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_WIDTH 1
/* defauwt vawue of bitfiewd tx_buf_en */
#define HW_ATW_TPB_TX_BUF_EN_DEFAUWT 0x0

/* tx tx{b}_hi_thwesh[c:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx{b}_hi_thwesh[c:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_tpb_tx0_hi_thwesh_i[12:0]"
 */

/* wegistew addwess fow bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_ADW(buffew) (0x00007914 + (buffew) * 0x10)
/* bitmask fow bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_MSK 0x1fff0000
/* invewted bitmask fow bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_MSKN 0xe000ffff
/* wowew bit position of bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_SHIFT 16
/* width of bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_WIDTH 13
/* defauwt vawue of bitfiewd tx{b}_hi_thwesh[c:0] */
#define HW_ATW_TPB_TXBHI_THWESH_DEFAUWT 0x0

/* tx tx{b}_wo_thwesh[c:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx{b}_wo_thwesh[c:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_tpb_tx0_wo_thwesh_i[12:0]"
 */

/* wegistew addwess fow bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_ADW(buffew) (0x00007914 + (buffew) * 0x10)
/* bitmask fow bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_MSK 0x00001fff
/* invewted bitmask fow bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_MSKN 0xffffe000
/* wowew bit position of bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_SHIFT 0
/* width of bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_WIDTH 13
/* defauwt vawue of bitfiewd tx{b}_wo_thwesh[c:0] */
#define HW_ATW_TPB_TXBWO_THWESH_DEFAUWT 0x0

/* tx dma_sys_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dma_sys_woopback".
 * powt="pif_tpb_dma_sys_wbk_i"
 */

/* wegistew addwess fow bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_ADW 0x00007000
/* bitmask fow bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_MSK 0x00000040
/* invewted bitmask fow bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_MSKN 0xffffffbf
/* wowew bit position of bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_SHIFT 6
/* width of bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_WIDTH 1
/* defauwt vawue of bitfiewd dma_sys_woopback */
#define HW_ATW_TPB_DMA_SYS_WBK_DEFAUWT 0x0

/* tx dma_net_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "dma_net_woopback".
 * powt="pif_tpb_dma_net_wbk_i"
 */

/* wegistew addwess fow bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_ADW 0x00007000
/* bitmask fow bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_MSK 0x00000010
/* invewted bitmask fow bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_MSKN 0xffffffef
/* wowew bit position of bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_SHIFT 4
/* width of bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_WIDTH 1
/* defauwt vawue of bitfiewd dma_net_woopback */
#define HW_ATW_TPB_DMA_NET_WBK_DEFAUWT 0x0

/* tx tx{b}_buf_size[7:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx{b}_buf_size[7:0]".
 * pawametew: buffew {b} | stwide size 0x10 | wange [0, 7]
 * powt="pif_tpb_tx0_buf_size_i[7:0]"
 */

/* wegistew addwess fow bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_ADW(buffew) (0x00007910 + (buffew) * 0x10)
/* bitmask fow bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_MSK 0x000000ff
/* invewted bitmask fow bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_MSKN 0xffffff00
/* wowew bit position of bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_SHIFT 0
/* width of bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_WIDTH 8
/* defauwt vawue of bitfiewd tx{b}_buf_size[7:0] */
#define HW_ATW_TPB_TXBBUF_SIZE_DEFAUWT 0x0

/* tx tx_scp_ins_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_scp_ins_en".
 * powt="pif_tpb_scp_ins_en_i"
 */

/* wegistew addwess fow bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_ADW 0x00007900
/* bitmask fow bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_MSK 0x00000004
/* invewted bitmask fow bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_MSKN 0xfffffffb
/* wowew bit position of bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_SHIFT 2
/* width of bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_WIDTH 1
/* defauwt vawue of bitfiewd tx_scp_ins_en */
#define HW_ATW_TPB_TX_SCP_INS_EN_DEFAUWT 0x0

/* tx tx_cwk_gate_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_cwk_gate_en".
 * powt="pif_tpb_cwk_gate_en_i"
 */

/* wegistew addwess fow bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_ADW 0x00007900
/* bitmask fow bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_MSK 0x00000010
/* invewted bitmask fow bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_MSKN 0xffffffef
/* wowew bit position of bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_SHIFT 4
/* width of bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_WIDTH 1
/* defauwt vawue of bitfiewd tx_cwk_gate_en */
#define HW_ATW_TPB_TX_CWK_GATE_EN_DEFAUWT 0x1

/* tx ipv4_chk_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "ipv4_chk_en".
 * powt="pif_tpo_ipv4_chk_en_i"
 */

/* wegistew addwess fow bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_ADW 0x00007800
/* bitmask fow bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_MSK 0x00000002
/* invewted bitmask fow bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_MSKN 0xfffffffd
/* wowew bit position of bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_SHIFT 1
/* width of bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_WIDTH 1
/* defauwt vawue of bitfiewd ipv4_chk_en */
#define HW_ATW_TPO_IPV4CHK_EN_DEFAUWT 0x0

/* tx w4_chk_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w4_chk_en".
 * powt="pif_tpo_w4_chk_en_i"
 */

/* wegistew addwess fow bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_ADW 0x00007800
/* bitmask fow bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_MSK 0x00000001
/* invewted bitmask fow bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_MSKN 0xfffffffe
/* wowew bit position of bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_SHIFT 0
/* width of bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_WIDTH 1
/* defauwt vawue of bitfiewd w4_chk_en */
#define HW_ATW_TPOW4CHK_EN_DEFAUWT 0x0

/* tx pkt_sys_woopback bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "pkt_sys_woopback".
 * powt="pif_tpo_pkt_sys_wbk_i"
 */

/* wegistew addwess fow bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_ADW 0x00007000
/* bitmask fow bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_MSK 0x00000080
/* invewted bitmask fow bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_MSKN 0xffffff7f
/* wowew bit position of bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_SHIFT 7
/* width of bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_WIDTH 1
/* defauwt vawue of bitfiewd pkt_sys_woopback */
#define HW_ATW_TPO_PKT_SYS_WBK_DEFAUWT 0x0

/* tx data_tc_awb_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc_awb_mode".
 * powt="pif_tps_data_tc_awb_mode_i"
 */

/* wegistew addwess fow bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_ADW 0x00007100
/* bitmask fow bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_MSK 0x00000001
/* invewted bitmask fow bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_MSKN 0xfffffffe
/* wowew bit position of bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_SHIFT 0
/* width of bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_WIDTH 1
/* defauwt vawue of bitfiewd data_tc_awb_mode */
#define HW_ATW_TPS_DATA_TC_AWB_MODE_DEFAUWT 0x0

/* tx desc{w}_wate_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{w}_wate_en".
 * powt="pif_tps_desc_wate_en_i[0]"
 */

/* wegistew addwess fow bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_ADW(desc) (0x00007408 + (desc) * 0x10)
/* bitmask fow bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_MSK 0x80000000
/* invewted bitmask fow bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_MSKN 0x7FFFFFFF
/* wowew bit position of bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_SHIFT 31
/* width of bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_WIDTH 1
/* defauwt vawue of bitfiewd desc{w}_wate_en */
#define HW_ATW_TPS_DESC_WATE_EN_DEFAUWT 0x0

/* tx desc{w}_wate_x bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{w}_wate_x".
 * powt="pif_tps_desc0_wate_x"
 */
/* wegistew addwess fow bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_ADW(desc) (0x00007408 + (desc) * 0x10)
/* bitmask fow bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_MSK 0x03FF0000
/* invewted bitmask fow bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_MSKN 0xFC00FFFF
/* wowew bit position of bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_SHIFT 16
/* width of bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_WIDTH 10
/* defauwt vawue of bitfiewd desc{w}_wate_x */
#define HW_ATW_TPS_DESC_WATE_X_DEFAUWT 0x0

/* tx desc{w}_wate_y bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc{w}_wate_y".
 * powt="pif_tps_desc0_wate_y"
 */
/* wegistew addwess fow bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_ADW(desc) (0x00007408 + (desc) * 0x10)
/* bitmask fow bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_MSK 0x00003FFF
/* invewted bitmask fow bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_MSKN 0xFFFFC000
/* wowew bit position of bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_SHIFT 0
/* width of bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_WIDTH 14
/* defauwt vawue of bitfiewd desc{w}_wate_y */
#define HW_ATW_TPS_DESC_WATE_Y_DEFAUWT 0x0

/* tx desc_wate_ta_wst bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_wate_ta_wst".
 * powt="pif_tps_desc_wate_ta_wst_i"
 */

/* wegistew addwess fow bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_ADW 0x00007310
/* bitmask fow bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_MSK 0x80000000
/* invewted bitmask fow bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_MSKN 0x7fffffff
/* wowew bit position of bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_SHIFT 31
/* width of bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_WIDTH 1
/* defauwt vawue of bitfiewd desc_wate_ta_wst */
#define HW_ATW_TPS_DESC_WATE_TA_WST_DEFAUWT 0x0

/* tx desc_wate_wimit[a:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_wate_wimit[a:0]".
 * powt="pif_tps_desc_wate_wim_i[10:0]"
 */

/* wegistew addwess fow bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_ADW 0x00007310
/* bitmask fow bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_MSK 0x000007ff
/* invewted bitmask fow bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_MSKN 0xfffff800
/* wowew bit position of bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_SHIFT 0
/* width of bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_WIDTH 11
/* defauwt vawue of bitfiewd desc_wate_wimit[a:0] */
#define HW_ATW_TPS_DESC_WATE_WIM_DEFAUWT 0x0

/* tx desc_tc_awb_mode[1:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_tc_awb_mode[1:0]".
 * powt="pif_tps_desc_tc_awb_mode_i[1:0]"
 */

/* wegistew addwess fow bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_ADW 0x00007200
/* bitmask fow bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_MSK 0x00000003
/* invewted bitmask fow bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_MSKN 0xfffffffc
/* wowew bit position of bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_SHIFT 0
/* width of bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_WIDTH 2
/* defauwt vawue of bitfiewd desc_tc_awb_mode[1:0] */
#define HW_ATW_TPS_DESC_TC_AWB_MODE_DEFAUWT 0x0

/* tx desc_tc{t}_cwedit_max[b:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_tc{t}_cwedit_max[b:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_desc_tc0_cwedit_max_i[11:0]"
 */

/* wegistew addwess fow bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_ADW(tc) (0x00007210 + (tc) * 0x4)
/* bitmask fow bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_MSK 0x0fff0000
/* invewted bitmask fow bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_MSKN 0xf000ffff
/* wowew bit position of bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_SHIFT 16
/* width of bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_WIDTH 12
/* defauwt vawue of bitfiewd desc_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DESC_TCTCWEDIT_MAX_DEFAUWT 0x0

/* tx desc_tc{t}_weight[8:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_tc{t}_weight[8:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_desc_tc0_weight_i[8:0]"
 */

/* wegistew addwess fow bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_ADW(tc) (0x00007210 + (tc) * 0x4)
/* bitmask fow bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_MSK 0x000001ff
/* invewted bitmask fow bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_MSKN 0xfffffe00
/* wowew bit position of bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_SHIFT 0
/* width of bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_WIDTH 9
/* defauwt vawue of bitfiewd desc_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DESC_TCTWEIGHT_DEFAUWT 0x0

/* tx desc_vm_awb_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "desc_vm_awb_mode".
 * powt="pif_tps_desc_vm_awb_mode_i"
 */

/* wegistew addwess fow bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_ADW 0x00007300
/* bitmask fow bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_MSK 0x00000001
/* invewted bitmask fow bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_MSKN 0xfffffffe
/* wowew bit position of bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_SHIFT 0
/* width of bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_WIDTH 1
/* defauwt vawue of bitfiewd desc_vm_awb_mode */
#define HW_ATW_TPS_DESC_VM_AWB_MODE_DEFAUWT 0x0

/* tx data_tc{t}_cwedit_max[b:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc{t}_cwedit_max[b:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_data_tc0_cwedit_max_i[11:0]"
 */

/* wegistew addwess fow bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_ADW(tc) (0x00007110 + (tc) * 0x4)
/* bitmask fow bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_MSK 0x0fff0000
/* invewted bitmask fow bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_MSKN 0xf000ffff
/* wowew bit position of bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_SHIFT 16
/* width of bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_WIDTH 12
/* defauwt vawue of bitfiewd data_tc{t}_cwedit_max[b:0] */
#define HW_ATW_TPS_DATA_TCTCWEDIT_MAX_DEFAUWT 0x0

/* tx data_tc{t}_weight[8:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc{t}_weight[8:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_data_tc0_weight_i[8:0]"
 */

/* wegistew addwess fow bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_ADW(tc) (0x00007110 + (tc) * 0x4)
/* bitmask fow bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_MSK 0x000001ff
/* invewted bitmask fow bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_MSKN 0xfffffe00
/* wowew bit position of bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_SHIFT 0
/* width of bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_WIDTH 9
/* defauwt vawue of bitfiewd data_tc{t}_weight[8:0] */
#define HW_ATW_TPS_DATA_TCTWEIGHT_DEFAUWT 0x0

/* tx weg_wes_dsbw bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "weg_wes_dsbw".
 * powt="pif_tx_weg_wes_dsbw_i"
 */

/* wegistew addwess fow bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_ADW 0x00007000
/* bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_MSK 0x20000000
/* invewted bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_MSKN 0xdfffffff
/* wowew bit position of bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_SHIFT 29
/* width of bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_WIDTH 1
/* defauwt vawue of bitfiewd weg_wes_dsbw */
#define HW_ATW_TX_WEG_WES_DSBW_DEFAUWT 0x1

/* mac_phy wegistew access busy bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wegistew access busy".
 * powt="msm_pif_weg_busy_o"
 */

/* wegistew addwess fow bitfiewd wegistew access busy */
#define HW_ATW_MSM_WEG_ACCESS_BUSY_ADW 0x00004400
/* bitmask fow bitfiewd wegistew access busy */
#define HW_ATW_MSM_WEG_ACCESS_BUSY_MSK 0x00001000
/* invewted bitmask fow bitfiewd wegistew access busy */
#define HW_ATW_MSM_WEG_ACCESS_BUSY_MSKN 0xffffefff
/* wowew bit position of bitfiewd wegistew access busy */
#define HW_ATW_MSM_WEG_ACCESS_BUSY_SHIFT 12
/* width of bitfiewd wegistew access busy */
#define HW_ATW_MSM_WEG_ACCESS_BUSY_WIDTH 1

/* mac_phy msm wegistew addwess[7:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "msm wegistew addwess[7:0]".
 * powt="pif_msm_weg_addw_i[7:0]"
 */

/* wegistew addwess fow bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_ADW 0x00004400
/* bitmask fow bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_MSK 0x000000ff
/* invewted bitmask fow bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_MSKN 0xffffff00
/* wowew bit position of bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_SHIFT 0
/* width of bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_WIDTH 8
/* defauwt vawue of bitfiewd msm wegistew addwess[7:0] */
#define HW_ATW_MSM_WEG_ADDW_DEFAUWT 0x0

/* mac_phy wegistew wead stwobe bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wegistew wead stwobe".
 * powt="pif_msm_weg_wden_i"
 */

/* wegistew addwess fow bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_ADW 0x00004400
/* bitmask fow bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_MSK 0x00000200
/* invewted bitmask fow bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_MSKN 0xfffffdff
/* wowew bit position of bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_SHIFT 9
/* width of bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_WIDTH 1
/* defauwt vawue of bitfiewd wegistew wead stwobe */
#define HW_ATW_MSM_WEG_WD_STWOBE_DEFAUWT 0x0

/* mac_phy msm wegistew wead data[31:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "msm wegistew wead data[31:0]".
 * powt="msm_pif_weg_wd_data_o[31:0]"
 */

/* wegistew addwess fow bitfiewd msm wegistew wead data[31:0] */
#define HW_ATW_MSM_WEG_WD_DATA_ADW 0x00004408
/* bitmask fow bitfiewd msm wegistew wead data[31:0] */
#define HW_ATW_MSM_WEG_WD_DATA_MSK 0xffffffff
/* invewted bitmask fow bitfiewd msm wegistew wead data[31:0] */
#define HW_ATW_MSM_WEG_WD_DATA_MSKN 0x00000000
/* wowew bit position of bitfiewd msm wegistew wead data[31:0] */
#define HW_ATW_MSM_WEG_WD_DATA_SHIFT 0
/* width of bitfiewd msm wegistew wead data[31:0] */
#define HW_ATW_MSM_WEG_WD_DATA_WIDTH 32

/* mac_phy msm wegistew wwite data[31:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "msm wegistew wwite data[31:0]".
 * powt="pif_msm_weg_ww_data_i[31:0]"
 */

/* wegistew addwess fow bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_ADW 0x00004404
/* bitmask fow bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_MSK 0xffffffff
/* invewted bitmask fow bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_MSKN 0x00000000
/* wowew bit position of bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_SHIFT 0
/* width of bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_WIDTH 32
/* defauwt vawue of bitfiewd msm wegistew wwite data[31:0] */
#define HW_ATW_MSM_WEG_WW_DATA_DEFAUWT 0x0

/* mac_phy wegistew wwite stwobe bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wegistew wwite stwobe".
 * powt="pif_msm_weg_wwen_i"
 */

/* wegistew addwess fow bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_ADW 0x00004400
/* bitmask fow bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_MSK 0x00000100
/* invewted bitmask fow bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_MSKN 0xfffffeff
/* wowew bit position of bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_SHIFT 8
/* width of bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_WIDTH 1
/* defauwt vawue of bitfiewd wegistew wwite stwobe */
#define HW_ATW_MSM_WEG_WW_STWOBE_DEFAUWT 0x0

/* wegistew addwess fow bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_ADW 0x00004628
/* bitmask fow bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_MSK 0x00000010
/* invewted bitmask fow bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_MSKN 0xFFFFFFEF
/* wowew bit position of bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_SHIFT 4
/* width of bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_WIDTH 1
/* defauwt vawue of bitfiewd PTP Digitaw Cwock Wead Enabwe */
#define HW_ATW_PCS_PTP_CWOCK_WEAD_ENABWE_DEFAUWT 0x0

/* wegistew addwess fow ptp countew weading */
#define HW_ATW_PCS_PTP_TS_VAW_ADDW(index) (0x00004900 + (index) * 0x4)

/* mif soft weset bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "soft weset".
 * powt="pif_gwb_wes_i"
 */

/* wegistew addwess fow bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_ADW 0x00000000
/* bitmask fow bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_MSK 0x00008000
/* invewted bitmask fow bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_MSKN 0xffff7fff
/* wowew bit position of bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_SHIFT 15
/* width of bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_WIDTH 1
/* defauwt vawue of bitfiewd soft weset */
#define HW_ATW_GWB_SOFT_WES_DEFAUWT 0x0

/* mif wegistew weset disabwe bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wegistew weset disabwe".
 * powt="pif_gwb_weg_wes_dsbw_i"
 */

/* wegistew addwess fow bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_ADW 0x00000000
/* bitmask fow bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_MSK 0x00004000
/* invewted bitmask fow bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_MSKN 0xffffbfff
/* wowew bit position of bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_SHIFT 14
/* width of bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_WIDTH 1
/* defauwt vawue of bitfiewd wegistew weset disabwe */
#define HW_ATW_GWB_WEG_WES_DIS_DEFAUWT 0x1

/* tx dma debug contwow definitions */
#define HW_ATW_TX_DMA_DEBUG_CTW_ADW 0x00008920u

/* tx dma descwiptow base addwess msw definitions */
#define HW_ATW_TX_DMA_DESC_BASE_ADDWMSW_ADW(descwiptow) \
			(0x00007c04u + (descwiptow) * 0x40)

/* tx dma totaw wequest wimit */
#define HW_ATW_TX_DMA_TOTAW_WEQ_WIMIT_ADW 0x00007b20u

/* tx intewwupt modewation contwow wegistew definitions
 * Pwepwocessow definitions fow TX Intewwupt Modewation Contwow Wegistew
 * Base Addwess: 0x00008980
 * Pawametew: queue {Q} | stwide size 0x4 | wange [0, 31]
 */

#define HW_ATW_TX_INTW_MODEWATION_CTW_ADW(queue) (0x00008980u + (queue) * 0x4)

/* pcie weg_wes_dsbw bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "weg_wes_dsbw".
 * powt="pif_pci_weg_wes_dsbw_i"
 */

/* wegistew addwess fow bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_ADW 0x00001000
/* bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_MSK 0x20000000
/* invewted bitmask fow bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_MSKN 0xdfffffff
/* wowew bit position of bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_SHIFT 29
/* width of bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_WIDTH 1
/* defauwt vawue of bitfiewd weg_wes_dsbw */
#define HW_ATW_PCI_WEG_WES_DSBW_DEFAUWT 0x1

/* PCI cowe contwow wegistew */
#define HW_ATW_PCI_WEG_CONTWOW6_ADW 0x1014u

/* gwobaw micwopwocessow scwatch pad definitions */
#define HW_ATW_GWB_CPU_SCWATCH_SCP_ADW(scwatch_scp) \
	(0x00000300u + (scwatch_scp) * 0x4)

/* wegistew addwess fow bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_ADW 0x00000404
/* bitmask fow bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_MSK 0x00000002
/* invewted bitmask fow bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_MSKN 0xFFFFFFFD
/* wowew bit position of bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_SHIFT 1
/* width of bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_WIDTH 1
/* defauwt vawue of bitfiewd uP Fowce Intewwupt */
#define HW_ATW_MCP_UP_FOWCE_INTEWWUPT_DEFAUWT 0x0

/* Pwepwocessow definitions fow Gwobaw MDIO Intewfaces
 * Addwess: 0x00000280 + 0x4 * Numbew of intewface
 */
#define HW_ATW_GWB_MDIO_IFACE_ADDW_BEGIN   0x00000280u

#define HW_ATW_GWB_MDIO_IFACE_N_ADW(numbew) \
	(HW_ATW_GWB_MDIO_IFACE_ADDW_BEGIN + (((numbew) - 1) * 0x4))

/* MIF MDIO Busy Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "MDIO Busy".
 * POWT="mdio_pif_busy_o"
 */

/* Wegistew addwess fow bitfiewd MDIO Busy */
#define HW_ATW_MDIO_BUSY_ADW 0x00000284
/* Bitmask fow bitfiewd MDIO Busy */
#define HW_ATW_MDIO_BUSY_MSK 0x80000000
/* Invewted bitmask fow bitfiewd MDIO Busy */
#define HW_ATW_MDIO_BUSY_MSKN 0x7FFFFFFF
/* Wowew bit position of bitfiewd MDIO Busy */
#define HW_ATW_MDIO_BUSY_SHIFT 31
/* Width of bitfiewd MDIO Busy */
#define HW_ATW_MDIO_BUSY_WIDTH 1

/* MIF MDIO Execute Opewation Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "MDIO Execute Opewation".
 * POWT="pif_mdio_op_stawt_i"
 */

/* Wegistew addwess fow bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_ADW 0x00000284
/* Bitmask fow bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_MSK 0x00008000
/* Invewted bitmask fow bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_MSKN 0xFFFF7FFF
/* Wowew bit position of bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_SHIFT 15
/* Width of bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_WIDTH 1
/* Defauwt vawue of bitfiewd MDIO Execute Opewation */
#define HW_ATW_MDIO_EXECUTE_OPEWATION_DEFAUWT 0x0

/* MIF Op Mode [1:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "Op Mode [1:0]".
 * POWT="pif_mdio_mode_i[1:0]"
 */

/* Wegistew addwess fow bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_ADW 0x00000284
/* Bitmask fow bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_MSK 0x00003000
/* Invewted bitmask fow bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_MSKN 0xFFFFCFFF
/* Wowew bit position of bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_SHIFT 12
/* Width of bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_WIDTH 2
/* Defauwt vawue of bitfiewd Op Mode [1:0] */
#define HW_ATW_MDIO_OP_MODE_DEFAUWT 0x0

/* MIF PHY addwess Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "PHY addwess".
 * POWT="pif_mdio_phy_addw_i[9:0]"
 */

/* Wegistew addwess fow bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_ADW 0x00000284
/* Bitmask fow bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_MSK 0x000003FF
/* Invewted bitmask fow bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_MSKN 0xFFFFFC00
/* Wowew bit position of bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_SHIFT 0
/* Width of bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_WIDTH 10
/* Defauwt vawue of bitfiewd PHY addwess */
#define HW_ATW_MDIO_PHY_ADDWESS_DEFAUWT 0x0

/* MIF MDIO WwiteData [F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "MDIO WwiteData [F:0]".
 * POWT="pif_mdio_wdata_i[15:0]"
 */

/* Wegistew addwess fow bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_ADW 0x00000288
/* Bitmask fow bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_MSK 0x0000FFFF
/* Invewted bitmask fow bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_MSKN 0xFFFF0000
/* Wowew bit position of bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_SHIFT 0
/* Width of bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_WIDTH 16
/* Defauwt vawue of bitfiewd MDIO WwiteData [F:0] */
#define HW_ATW_MDIO_WWITE_DATA_DEFAUWT 0x0

/* MIF MDIO Addwess [F:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "MDIO Addwess [F:0]".
 * POWT="pif_mdio_addw_i[15:0]"
 */

/* Wegistew addwess fow bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_ADW 0x0000028C
/* Bitmask fow bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_MSK 0x0000FFFF
/* Invewted bitmask fow bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_MSKN 0xFFFF0000
/* Wowew bit position of bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_SHIFT 0
/* Width of bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_WIDTH 16
/* Defauwt vawue of bitfiewd MDIO Addwess [F:0] */
#define HW_ATW_MDIO_ADDWESS_DEFAUWT 0x0

#define HW_ATW_MIF_WESET_TIMEOUT_ADW 0x00000348

#define HW_ATW_FW_SM_MDIO       0x0U
#define HW_ATW_FW_SM_WAM        0x2U
#define HW_ATW_FW_SM_WESET1     0x3U
#define HW_ATW_FW_SM_WESET2     0x4U

#endif /* HW_ATW_WWH_INTEWNAW_H */
