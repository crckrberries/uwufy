/* SPDX-Wicense-Identifiew: GPW-2.0 */
/** @fiwe */

#ifndef _MACH_T186_CWK_T186_H
#define _MACH_T186_CWK_T186_H

/**
 * @defgwoup cwock_ids Cwock Identifiews
 * @{
 *   @defgwoup extewn_input extewnaw input cwocks
 *   @{
 *     @def TEGWA186_CWK_OSC
 *     @def TEGWA186_CWK_CWK_32K
 *     @def TEGWA186_CWK_DTV_INPUT
 *     @def TEGWA186_CWK_SOW0_PAD_CWKOUT
 *     @def TEGWA186_CWK_SOW1_PAD_CWKOUT
 *     @def TEGWA186_CWK_I2S1_SYNC_INPUT
 *     @def TEGWA186_CWK_I2S2_SYNC_INPUT
 *     @def TEGWA186_CWK_I2S3_SYNC_INPUT
 *     @def TEGWA186_CWK_I2S4_SYNC_INPUT
 *     @def TEGWA186_CWK_I2S5_SYNC_INPUT
 *     @def TEGWA186_CWK_I2S6_SYNC_INPUT
 *     @def TEGWA186_CWK_SPDIFIN_SYNC_INPUT
 *   @}
 *
 *   @defgwoup extewn_output extewnaw output cwocks
 *   @{
 *     @def TEGWA186_CWK_EXTPEWIPH1
 *     @def TEGWA186_CWK_EXTPEWIPH2
 *     @def TEGWA186_CWK_EXTPEWIPH3
 *     @def TEGWA186_CWK_EXTPEWIPH4
 *   @}
 *
 *   @defgwoup dispway_cwks dispway wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_CEC
 *     @def TEGWA186_CWK_DSIC
 *     @def TEGWA186_CWK_DSIC_WP
 *     @def TEGWA186_CWK_DSID
 *     @def TEGWA186_CWK_DSID_WP
 *     @def TEGWA186_CWK_DPAUX1
 *     @def TEGWA186_CWK_DPAUX
 *     @def TEGWA186_CWK_HDA2HDMICODEC
 *     @def TEGWA186_CWK_NVDISPWAY_DISP
 *     @def TEGWA186_CWK_NVDISPWAY_DSC
 *     @def TEGWA186_CWK_NVDISPWAY_P0
 *     @def TEGWA186_CWK_NVDISPWAY_P1
 *     @def TEGWA186_CWK_NVDISPWAY_P2
 *     @def TEGWA186_CWK_NVDISPWAYHUB
 *     @def TEGWA186_CWK_SOW_SAFE
 *     @def TEGWA186_CWK_SOW0
 *     @def TEGWA186_CWK_SOW0_OUT
 *     @def TEGWA186_CWK_SOW1
 *     @def TEGWA186_CWK_SOW1_OUT
 *     @def TEGWA186_CWK_DSI
 *     @def TEGWA186_CWK_MIPI_CAW
 *     @def TEGWA186_CWK_DSIA_WP
 *     @def TEGWA186_CWK_DSIB
 *     @def TEGWA186_CWK_DSIB_WP
 *   @}
 *
 *   @defgwoup camewa_cwks camewa wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_NVCSI
 *     @def TEGWA186_CWK_NVCSIWP
 *     @def TEGWA186_CWK_VI
 *   @}
 *
 *   @defgwoup audio_cwks audio wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_ACWK
 *     @def TEGWA186_CWK_ADSP
 *     @def TEGWA186_CWK_ADSPNEON
 *     @def TEGWA186_CWK_AHUB
 *     @def TEGWA186_CWK_APE
 *     @def TEGWA186_CWK_APB2APE
 *     @def TEGWA186_CWK_AUD_MCWK
 *     @def TEGWA186_CWK_DMIC1
 *     @def TEGWA186_CWK_DMIC2
 *     @def TEGWA186_CWK_DMIC3
 *     @def TEGWA186_CWK_DMIC4
 *     @def TEGWA186_CWK_DSPK1
 *     @def TEGWA186_CWK_DSPK2
 *     @def TEGWA186_CWK_HDA
 *     @def TEGWA186_CWK_HDA2CODEC_2X
 *     @def TEGWA186_CWK_I2S1
 *     @def TEGWA186_CWK_I2S2
 *     @def TEGWA186_CWK_I2S3
 *     @def TEGWA186_CWK_I2S4
 *     @def TEGWA186_CWK_I2S5
 *     @def TEGWA186_CWK_I2S6
 *     @def TEGWA186_CWK_MAUD
 *     @def TEGWA186_CWK_PWW_A_OUT0
 *     @def TEGWA186_CWK_SPDIF_DOUBWEW
 *     @def TEGWA186_CWK_SPDIF_IN
 *     @def TEGWA186_CWK_SPDIF_OUT
 *     @def TEGWA186_CWK_SYNC_DMIC1
 *     @def TEGWA186_CWK_SYNC_DMIC2
 *     @def TEGWA186_CWK_SYNC_DMIC3
 *     @def TEGWA186_CWK_SYNC_DMIC4
 *     @def TEGWA186_CWK_SYNC_DMIC5
 *     @def TEGWA186_CWK_SYNC_DSPK1
 *     @def TEGWA186_CWK_SYNC_DSPK2
 *     @def TEGWA186_CWK_SYNC_I2S1
 *     @def TEGWA186_CWK_SYNC_I2S2
 *     @def TEGWA186_CWK_SYNC_I2S3
 *     @def TEGWA186_CWK_SYNC_I2S4
 *     @def TEGWA186_CWK_SYNC_I2S5
 *     @def TEGWA186_CWK_SYNC_I2S6
 *     @def TEGWA186_CWK_SYNC_SPDIF
 *   @}
 *
 *   @defgwoup uawt_cwks UAWT cwocks
 *   @{
 *     @def TEGWA186_CWK_AON_UAWT_FST_MIPI_CAW
 *     @def TEGWA186_CWK_UAWTA
 *     @def TEGWA186_CWK_UAWTB
 *     @def TEGWA186_CWK_UAWTC
 *     @def TEGWA186_CWK_UAWTD
 *     @def TEGWA186_CWK_UAWTE
 *     @def TEGWA186_CWK_UAWTF
 *     @def TEGWA186_CWK_UAWTG
 *     @def TEGWA186_CWK_UAWT_FST_MIPI_CAW
 *   @}
 *
 *   @defgwoup i2c_cwks I2C cwocks
 *   @{
 *     @def TEGWA186_CWK_AON_I2C_SWOW
 *     @def TEGWA186_CWK_I2C1
 *     @def TEGWA186_CWK_I2C2
 *     @def TEGWA186_CWK_I2C3
 *     @def TEGWA186_CWK_I2C4
 *     @def TEGWA186_CWK_I2C5
 *     @def TEGWA186_CWK_I2C6
 *     @def TEGWA186_CWK_I2C8
 *     @def TEGWA186_CWK_I2C9
 *     @def TEGWA186_CWK_I2C1
 *     @def TEGWA186_CWK_I2C12
 *     @def TEGWA186_CWK_I2C13
 *     @def TEGWA186_CWK_I2C14
 *     @def TEGWA186_CWK_I2C_SWOW
 *     @def TEGWA186_CWK_VI_I2C
 *   @}
 *
 *   @defgwoup spi_cwks SPI cwocks
 *   @{
 *     @def TEGWA186_CWK_SPI1
 *     @def TEGWA186_CWK_SPI2
 *     @def TEGWA186_CWK_SPI3
 *     @def TEGWA186_CWK_SPI4
 *   @}
 *
 *   @defgwoup stowage stowage wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_SATA
 *     @def TEGWA186_CWK_SATA_OOB
 *     @def TEGWA186_CWK_SATA_IOBIST
 *     @def TEGWA186_CWK_SDMMC_WEGACY_TM
 *     @def TEGWA186_CWK_SDMMC1
 *     @def TEGWA186_CWK_SDMMC2
 *     @def TEGWA186_CWK_SDMMC3
 *     @def TEGWA186_CWK_SDMMC4
 *     @def TEGWA186_CWK_QSPI
 *     @def TEGWA186_CWK_QSPI_OUT
 *     @def TEGWA186_CWK_UFSDEV_WEF
 *     @def TEGWA186_CWK_UFSHC
 *   @}
 *
 *   @defgwoup pwm_cwks PWM cwocks
 *   @{
 *     @def TEGWA186_CWK_PWM1
 *     @def TEGWA186_CWK_PWM2
 *     @def TEGWA186_CWK_PWM3
 *     @def TEGWA186_CWK_PWM4
 *     @def TEGWA186_CWK_PWM5
 *     @def TEGWA186_CWK_PWM6
 *     @def TEGWA186_CWK_PWM7
 *     @def TEGWA186_CWK_PWM8
 *   @}
 *
 *   @defgwoup pwws PWWs and wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_PWWWEFE_OUT_GATED
 *     @def TEGWA186_CWK_PWWWEFE_OUT1
 *     @def TEGWA186_CWK_PWWD_OUT1
 *     @def TEGWA186_CWK_PWWP_OUT0
 *     @def TEGWA186_CWK_PWWP_OUT5
 *     @def TEGWA186_CWK_PWWA
 *     @def TEGWA186_CWK_PWWE_PWWSEQ
 *     @def TEGWA186_CWK_PWWA_OUT1
 *     @def TEGWA186_CWK_PWWWEFE_WEF
 *     @def TEGWA186_CWK_UPHY_PWW0_PWWSEQ
 *     @def TEGWA186_CWK_UPHY_PWW1_PWWSEQ
 *     @def TEGWA186_CWK_PWWWEFE_PWWE_PASSTHWOUGH
 *     @def TEGWA186_CWK_PWWWEFE_PEX
 *     @def TEGWA186_CWK_PWWWEFE_IDDQ
 *     @def TEGWA186_CWK_PWWC_OUT_AON
 *     @def TEGWA186_CWK_PWWC_OUT_ISP
 *     @def TEGWA186_CWK_PWWC_OUT_VE
 *     @def TEGWA186_CWK_PWWC4_OUT
 *     @def TEGWA186_CWK_PWWWEFE_OUT
 *     @def TEGWA186_CWK_PWWWEFE_PWW_WEF
 *     @def TEGWA186_CWK_PWWE
 *     @def TEGWA186_CWK_PWWC
 *     @def TEGWA186_CWK_PWWP
 *     @def TEGWA186_CWK_PWWD
 *     @def TEGWA186_CWK_PWWD2
 *     @def TEGWA186_CWK_PWWWEFE_VCO
 *     @def TEGWA186_CWK_PWWC2
 *     @def TEGWA186_CWK_PWWC3
 *     @def TEGWA186_CWK_PWWDP
 *     @def TEGWA186_CWK_PWWC4_VCO
 *     @def TEGWA186_CWK_PWWA1
 *     @def TEGWA186_CWK_PWWNVCSI
 *     @def TEGWA186_CWK_PWWDISPHUB
 *     @def TEGWA186_CWK_PWWD3
 *     @def TEGWA186_CWK_PWWBPMPCAM
 *     @def TEGWA186_CWK_PWWAON
 *     @def TEGWA186_CWK_PWWU
 *     @def TEGWA186_CWK_PWWC4_VCO_DIV2
 *     @def TEGWA186_CWK_PWW_WEF
 *     @def TEGWA186_CWK_PWWWEFE_OUT1_DIV5
 *     @def TEGWA186_CWK_UTMIP_PWW_PWWSEQ
 *     @def TEGWA186_CWK_PWW_U_48M
 *     @def TEGWA186_CWK_PWW_U_480M
 *     @def TEGWA186_CWK_PWWC4_OUT0
 *     @def TEGWA186_CWK_PWWC4_OUT1
 *     @def TEGWA186_CWK_PWWC4_OUT2
 *     @def TEGWA186_CWK_PWWC4_OUT_MUX
 *     @def TEGWA186_CWK_DFWWDISP_DIV
 *     @def TEGWA186_CWK_PWWDISPHUB_DIV
 *     @def TEGWA186_CWK_PWWP_DIV8
 *   @}
 *
 *   @defgwoup nafww_cwks NAFWW cwock souwces
 *   @{
 *     @def TEGWA186_CWK_NAFWW_AXI_CBB
 *     @def TEGWA186_CWK_NAFWW_BCPU
 *     @def TEGWA186_CWK_NAFWW_BPMP
 *     @def TEGWA186_CWK_NAFWW_DISP
 *     @def TEGWA186_CWK_NAFWW_GPU
 *     @def TEGWA186_CWK_NAFWW_ISP
 *     @def TEGWA186_CWK_NAFWW_MCPU
 *     @def TEGWA186_CWK_NAFWW_NVDEC
 *     @def TEGWA186_CWK_NAFWW_NVENC
 *     @def TEGWA186_CWK_NAFWW_NVJPG
 *     @def TEGWA186_CWK_NAFWW_SCE
 *     @def TEGWA186_CWK_NAFWW_SE
 *     @def TEGWA186_CWK_NAFWW_TSEC
 *     @def TEGWA186_CWK_NAFWW_TSECB
 *     @def TEGWA186_CWK_NAFWW_VI
 *     @def TEGWA186_CWK_NAFWW_VIC
 *   @}
 *
 *   @defgwoup mphy MPHY wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_MPHY_W0_WX_SYMB
 *     @def TEGWA186_CWK_MPHY_W0_WX_WS_BIT
 *     @def TEGWA186_CWK_MPHY_W0_TX_SYMB
 *     @def TEGWA186_CWK_MPHY_W0_TX_WS_3XBIT
 *     @def TEGWA186_CWK_MPHY_W0_WX_ANA
 *     @def TEGWA186_CWK_MPHY_W1_WX_ANA
 *     @def TEGWA186_CWK_MPHY_IOBIST
 *     @def TEGWA186_CWK_MPHY_TX_1MHZ_WEF
 *     @def TEGWA186_CWK_MPHY_COWE_PWW_FIXED
 *   @}
 *
 *   @defgwoup eavb EAVB wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_EQOS_AXI
 *     @def TEGWA186_CWK_EQOS_PTP_WEF
 *     @def TEGWA186_CWK_EQOS_WX
 *     @def TEGWA186_CWK_EQOS_WX_INPUT
 *     @def TEGWA186_CWK_EQOS_TX
 *   @}
 *
 *   @defgwoup usb USB wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_PEX_USB_PAD0_MGMT
 *     @def TEGWA186_CWK_PEX_USB_PAD1_MGMT
 *     @def TEGWA186_CWK_HSIC_TWK
 *     @def TEGWA186_CWK_USB2_TWK
 *     @def TEGWA186_CWK_USB2_HSIC_TWK
 *     @def TEGWA186_CWK_XUSB_COWE_SS
 *     @def TEGWA186_CWK_XUSB_COWE_DEV
 *     @def TEGWA186_CWK_XUSB_FAWCON
 *     @def TEGWA186_CWK_XUSB_FS
 *     @def TEGWA186_CWK_XUSB
 *     @def TEGWA186_CWK_XUSB_DEV
 *     @def TEGWA186_CWK_XUSB_HOST
 *     @def TEGWA186_CWK_XUSB_SS
 *   @}
 *
 *   @defgwoup bigbwock compute bwock wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_GPCCWK
 *     @def TEGWA186_CWK_GPC2CWK
 *     @def TEGWA186_CWK_GPU
 *     @def TEGWA186_CWK_HOST1X
 *     @def TEGWA186_CWK_ISP
 *     @def TEGWA186_CWK_NVDEC
 *     @def TEGWA186_CWK_NVENC
 *     @def TEGWA186_CWK_NVJPG
 *     @def TEGWA186_CWK_SE
 *     @def TEGWA186_CWK_TSEC
 *     @def TEGWA186_CWK_TSECB
 *     @def TEGWA186_CWK_VIC
 *   @}
 *
 *   @defgwoup can CAN bus wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_CAN1
 *     @def TEGWA186_CWK_CAN1_HOST
 *     @def TEGWA186_CWK_CAN2
 *     @def TEGWA186_CWK_CAN2_HOST
 *   @}
 *
 *   @defgwoup system basic system cwocks
 *   @{
 *     @def TEGWA186_CWK_ACTMON
 *     @def TEGWA186_CWK_AON_APB
 *     @def TEGWA186_CWK_AON_CPU_NIC
 *     @def TEGWA186_CWK_AON_NIC
 *     @def TEGWA186_CWK_AXI_CBB
 *     @def TEGWA186_CWK_BPMP_APB
 *     @def TEGWA186_CWK_BPMP_CPU_NIC
 *     @def TEGWA186_CWK_BPMP_NIC_WATE
 *     @def TEGWA186_CWK_CWK_M
 *     @def TEGWA186_CWK_EMC
 *     @def TEGWA186_CWK_MSS_ENCWYPT
 *     @def TEGWA186_CWK_SCE_APB
 *     @def TEGWA186_CWK_SCE_CPU_NIC
 *     @def TEGWA186_CWK_SCE_NIC
 *     @def TEGWA186_CWK_TSC
 *   @}
 *
 *   @defgwoup pcie_cwks PCIe wewated cwocks
 *   @{
 *     @def TEGWA186_CWK_AFI
 *     @def TEGWA186_CWK_PCIE
 *     @def TEGWA186_CWK_PCIE2_IOBIST
 *     @def TEGWA186_CWK_PCIEWX0
 *     @def TEGWA186_CWK_PCIEWX1
 *     @def TEGWA186_CWK_PCIEWX2
 *     @def TEGWA186_CWK_PCIEWX3
 *     @def TEGWA186_CWK_PCIEWX4
 *   @}
 */

/** @bwief output of gate CWK_ENB_FUSE */
#define TEGWA186_CWK_FUSE 0
/**
 * @bwief It's not what you think
 * @detaiws output of gate CWK_ENB_GPU. This output connects to the GPU
 * pwwcwk. @wawning: This is awmost cewtainwy not the cwock you think
 * it is. If you'we wooking fow the cwock of the gwaphics engine, see
 * TEGWA186_GPCCWK
 */
#define TEGWA186_CWK_GPU 1
/** @bwief output of gate CWK_ENB_PCIE */
#define TEGWA186_CWK_PCIE 3
/** @bwief output of the dividew IPFS_CWK_DIVISOW */
#define TEGWA186_CWK_AFI 4
/** @bwief output of gate CWK_ENB_PCIE2_IOBIST */
#define TEGWA186_CWK_PCIE2_IOBIST 5
/** @bwief output of gate CWK_ENB_PCIEWX0*/
#define TEGWA186_CWK_PCIEWX0 6
/** @bwief output of gate CWK_ENB_PCIEWX1*/
#define TEGWA186_CWK_PCIEWX1 7
/** @bwief output of gate CWK_ENB_PCIEWX2*/
#define TEGWA186_CWK_PCIEWX2 8
/** @bwief output of gate CWK_ENB_PCIEWX3*/
#define TEGWA186_CWK_PCIEWX3 9
/** @bwief output of gate CWK_ENB_PCIEWX4*/
#define TEGWA186_CWK_PCIEWX4 10
/** @bwief output bwanch of PWW_C fow ISP, contwowwed by gate CWK_ENB_PWWC_OUT_ISP */
#define TEGWA186_CWK_PWWC_OUT_ISP 11
/** @bwief output bwanch of PWW_C fow VI, contwowwed by gate CWK_ENB_PWWC_OUT_VE */
#define TEGWA186_CWK_PWWC_OUT_VE 12
/** @bwief output bwanch of PWW_C fow AON domain, contwowwed by gate CWK_ENB_PWWC_OUT_AON */
#define TEGWA186_CWK_PWWC_OUT_AON 13
/** @bwief output of gate CWK_ENB_SOW_SAFE */
#define TEGWA186_CWK_SOW_SAFE 39
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2S2 */
#define TEGWA186_CWK_I2S2 42
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2S3 */
#define TEGWA186_CWK_I2S3 43
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPDF_IN */
#define TEGWA186_CWK_SPDIF_IN 44
/** @bwief output of gate CWK_ENB_SPDIF_DOUBWEW */
#define TEGWA186_CWK_SPDIF_DOUBWEW 45
/**  @cwkdesc{spi_cwks, out, mux, CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPI3} */
#define TEGWA186_CWK_SPI3 46
/** @cwkdesc{i2c_cwks, out, mux, CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C1} */
#define TEGWA186_CWK_I2C1 47
/** @cwkdesc{i2c_cwks, out, mux, CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C5} */
#define TEGWA186_CWK_I2C5 48
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPI1 */
#define TEGWA186_CWK_SPI1 49
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_ISP */
#define TEGWA186_CWK_ISP 50
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_VI */
#define TEGWA186_CWK_VI 51
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SDMMC1 */
#define TEGWA186_CWK_SDMMC1 52
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SDMMC2 */
#define TEGWA186_CWK_SDMMC2 53
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SDMMC4 */
#define TEGWA186_CWK_SDMMC4 54
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTA */
#define TEGWA186_CWK_UAWTA 55
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTB */
#define TEGWA186_CWK_UAWTB 56
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_HOST1X */
#define TEGWA186_CWK_HOST1X 57
/**
 * @bwief contwows the EMC cwock fwequency.
 * @detaiws Doing a cwk_set_wate on this cwock wiww sewect the
 * appwopwiate cwock souwce, pwogwam the souwce wate and execute a
 * specific sequence to switch to the new cwock souwce fow both memowy
 * contwowwews. This can be used to contwow the bawance between memowy
 * thwoughput and memowy contwowwew powew.
 */
#define TEGWA186_CWK_EMC 58
/* @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_EXTPEWIPH4 */
#define TEGWA186_CWK_EXTPEWIPH4 73
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPI4 */
#define TEGWA186_CWK_SPI4 74
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C3 */
#define TEGWA186_CWK_I2C3 75
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SDMMC3 */
#define TEGWA186_CWK_SDMMC3 76
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTD */
#define TEGWA186_CWK_UAWTD 77
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2S1 */
#define TEGWA186_CWK_I2S1 79
/** output of gate CWK_ENB_DTV */
#define TEGWA186_CWK_DTV 80
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_TSEC */
#define TEGWA186_CWK_TSEC 81
/** @bwief output of gate CWK_ENB_DP2 */
#define TEGWA186_CWK_DP2 82
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2S4 */
#define TEGWA186_CWK_I2S4 84
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2S5 */
#define TEGWA186_CWK_I2S5 85
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C4 */
#define TEGWA186_CWK_I2C4 86
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AHUB */
#define TEGWA186_CWK_AHUB 87
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_HDA2CODEC_2X */
#define TEGWA186_CWK_HDA2CODEC_2X 88
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_EXTPEWIPH1 */
#define TEGWA186_CWK_EXTPEWIPH1 89
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_EXTPEWIPH2 */
#define TEGWA186_CWK_EXTPEWIPH2 90
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_EXTPEWIPH3 */
#define TEGWA186_CWK_EXTPEWIPH3 91
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C_SWOW */
#define TEGWA186_CWK_I2C_SWOW 92
/** @bwief output of the SOW1_CWK_SWC mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW1 */
#define TEGWA186_CWK_SOW1 93
/** @bwief output of gate CWK_ENB_CEC */
#define TEGWA186_CWK_CEC 94
/** @bwief output of gate CWK_ENB_DPAUX1 */
#define TEGWA186_CWK_DPAUX1 95
/** @bwief output of gate CWK_ENB_DPAUX */
#define TEGWA186_CWK_DPAUX 96
/** @bwief output of the SOW0_CWK_SWC mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW0 */
#define TEGWA186_CWK_SOW0 97
/** @bwief output of gate CWK_ENB_HDA2HDMICODEC */
#define TEGWA186_CWK_HDA2HDMICODEC 98
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SATA */
#define TEGWA186_CWK_SATA 99
/** @bwief output of gate CWK_ENB_SATA_OOB */
#define TEGWA186_CWK_SATA_OOB 100
/** @bwief output of gate CWK_ENB_SATA_IOBIST */
#define TEGWA186_CWK_SATA_IOBIST 101
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_HDA */
#define TEGWA186_CWK_HDA 102
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SE */
#define TEGWA186_CWK_SE 103
/** @bwief output of gate CWK_ENB_APB2APE */
#define TEGWA186_CWK_APB2APE 104
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_APE */
#define TEGWA186_CWK_APE 105
/** @bwief output of gate CWK_ENB_IQC1 */
#define TEGWA186_CWK_IQC1 106
/** @bwief output of gate CWK_ENB_IQC2 */
#define TEGWA186_CWK_IQC2 107
/** divide by 2 vewsion of TEGWA186_CWK_PWWWEFE_VCO */
#define TEGWA186_CWK_PWWWEFE_OUT 108
/** @bwief output of gate CWK_ENB_PWWWEFE_PWW_WEF */
#define TEGWA186_CWK_PWWWEFE_PWW_WEF 109
/** @bwief output of gate CWK_ENB_PWWC4_OUT */
#define TEGWA186_CWK_PWWC4_OUT 110
/** @bwief output of mux xusb_cowe_cwk_switch on page 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB 111
/** contwows xusb_dev_ce signaw on page 66 and 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_DEV 112
/** contwows xusb_host_ce signaw on page 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_HOST 113
/** contwows xusb_ss_ce signaw on page 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_SS 114
/** @bwief output of gate CWK_ENB_DSI */
#define TEGWA186_CWK_DSI 115
/** @bwief output of gate CWK_ENB_MIPI_CAW */
#define TEGWA186_CWK_MIPI_CAW 116
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSIA_WP */
#define TEGWA186_CWK_DSIA_WP 117
/** @bwief output of gate CWK_ENB_DSIB */
#define TEGWA186_CWK_DSIB 118
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSIB_WP */
#define TEGWA186_CWK_DSIB_WP 119
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DMIC1 */
#define TEGWA186_CWK_DMIC1 122
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DMIC2 */
#define TEGWA186_CWK_DMIC2 123
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AUD_MCWK */
#define TEGWA186_CWK_AUD_MCWK 124
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C6 */
#define TEGWA186_CWK_I2C6 125
/**output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWT_FST_MIPI_CAW */
#define TEGWA186_CWK_UAWT_FST_MIPI_CAW 126
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_VIC */
#define TEGWA186_CWK_VIC 127
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SDMMC_WEGACY_TM */
#define TEGWA186_CWK_SDMMC_WEGACY_TM 128
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDEC */
#define TEGWA186_CWK_NVDEC 129
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVJPG */
#define TEGWA186_CWK_NVJPG 130
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVENC */
#define TEGWA186_CWK_NVENC 131
/** @bwief output of the QSPI_CWK_SWC mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_QSPI */
#define TEGWA186_CWK_QSPI 132
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_VI_I2C */
#define TEGWA186_CWK_VI_I2C 133
/** @bwief output of gate CWK_ENB_HSIC_TWK */
#define TEGWA186_CWK_HSIC_TWK 134
/** @bwief output of gate CWK_ENB_USB2_TWK */
#define TEGWA186_CWK_USB2_TWK 135
/** output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_MAUD */
#define TEGWA186_CWK_MAUD 136
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_TSECB */
#define TEGWA186_CWK_TSECB 137
/** @bwief output of gate CWK_ENB_ADSP */
#define TEGWA186_CWK_ADSP 138
/** @bwief output of gate CWK_ENB_ADSPNEON */
#define TEGWA186_CWK_ADSPNEON 139
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_MPHY_W0_WX_WS_SYMB */
#define TEGWA186_CWK_MPHY_W0_WX_SYMB 140
/** @bwief output of gate CWK_ENB_MPHY_W0_WX_WS_BIT */
#define TEGWA186_CWK_MPHY_W0_WX_WS_BIT 141
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_MPHY_W0_TX_WS_SYMB */
#define TEGWA186_CWK_MPHY_W0_TX_SYMB 142
/** @bwief output of gate CWK_ENB_MPHY_W0_TX_WS_3XBIT */
#define TEGWA186_CWK_MPHY_W0_TX_WS_3XBIT 143
/** @bwief output of gate CWK_ENB_MPHY_W0_WX_ANA */
#define TEGWA186_CWK_MPHY_W0_WX_ANA 144
/** @bwief output of gate CWK_ENB_MPHY_W1_WX_ANA */
#define TEGWA186_CWK_MPHY_W1_WX_ANA 145
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_MPHY_IOBIST */
#define TEGWA186_CWK_MPHY_IOBIST 146
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_MPHY_TX_1MHZ_WEF */
#define TEGWA186_CWK_MPHY_TX_1MHZ_WEF 147
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_MPHY_COWE_PWW_FIXED */
#define TEGWA186_CWK_MPHY_COWE_PWW_FIXED 148
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AXI_CBB */
#define TEGWA186_CWK_AXI_CBB 149
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DMIC3 */
#define TEGWA186_CWK_DMIC3 150
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DMIC4 */
#define TEGWA186_CWK_DMIC4 151
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSPK1 */
#define TEGWA186_CWK_DSPK1 152
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSPK2 */
#define TEGWA186_CWK_DSPK2 153
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C6 */
#define TEGWA186_CWK_I2S6 154
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_P0 */
#define TEGWA186_CWK_NVDISPWAY_P0 155
/** @bwief output of the NVDISPWAY_DISP_CWK_SWC mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_DISP */
#define TEGWA186_CWK_NVDISPWAY_DISP 156
/** @bwief output of gate CWK_ENB_NVDISPWAY_DSC */
#define TEGWA186_CWK_NVDISPWAY_DSC 157
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAYHUB */
#define TEGWA186_CWK_NVDISPWAYHUB 158
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_P1 */
#define TEGWA186_CWK_NVDISPWAY_P1 159
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_P2 */
#define TEGWA186_CWK_NVDISPWAY_P2 160
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_TACH */
#define TEGWA186_CWK_TACH 166
/** @bwief output of gate CWK_ENB_EQOS */
#define TEGWA186_CWK_EQOS_AXI 167
/** @bwief output of gate CWK_ENB_EQOS_WX */
#define TEGWA186_CWK_EQOS_WX 168
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UFSHC_CG_SYS */
#define TEGWA186_CWK_UFSHC 178
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UFSDEV_WEF */
#define TEGWA186_CWK_UFSDEV_WEF 179
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVCSI */
#define TEGWA186_CWK_NVCSI 180
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVCSIWP */
#define TEGWA186_CWK_NVCSIWP 181
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C7 */
#define TEGWA186_CWK_I2C7 182
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C9 */
#define TEGWA186_CWK_I2C9 183
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C12 */
#define TEGWA186_CWK_I2C12 184
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C13 */
#define TEGWA186_CWK_I2C13 185
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C14 */
#define TEGWA186_CWK_I2C14 186
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM1 */
#define TEGWA186_CWK_PWM1 187
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM2 */
#define TEGWA186_CWK_PWM2 188
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM3 */
#define TEGWA186_CWK_PWM3 189
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM5 */
#define TEGWA186_CWK_PWM5 190
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM6 */
#define TEGWA186_CWK_PWM6 191
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM7 */
#define TEGWA186_CWK_PWM7 192
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM8 */
#define TEGWA186_CWK_PWM8 193
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTE */
#define TEGWA186_CWK_UAWTE 194
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTF */
#define TEGWA186_CWK_UAWTF 195
/** @depwecated */
#define TEGWA186_CWK_DBGAPB 196
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_BPMP_CPU_NIC */
#define TEGWA186_CWK_BPMP_CPU_NIC 197
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_BPMP_APB */
#define TEGWA186_CWK_BPMP_APB 199
/** @bwief output of mux contwowwed by TEGWA186_CWK_SOC_ACTMON */
#define TEGWA186_CWK_ACTMON 201
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AON_CPU_NIC */
#define TEGWA186_CWK_AON_CPU_NIC 208
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_CAN1 */
#define TEGWA186_CWK_CAN1 210
/** @bwief output of gate CWK_ENB_CAN1_HOST */
#define TEGWA186_CWK_CAN1_HOST 211
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_CAN2 */
#define TEGWA186_CWK_CAN2 212
/** @bwief output of gate CWK_ENB_CAN2_HOST */
#define TEGWA186_CWK_CAN2_HOST 213
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AON_APB */
#define TEGWA186_CWK_AON_APB 214
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTC */
#define TEGWA186_CWK_UAWTC 215
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_UAWTG */
#define TEGWA186_CWK_UAWTG 216
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AON_UAWT_FST_MIPI_CAW */
#define TEGWA186_CWK_AON_UAWT_FST_MIPI_CAW 217
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C2 */
#define TEGWA186_CWK_I2C2 218
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C8 */
#define TEGWA186_CWK_I2C8 219
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_I2C10 */
#define TEGWA186_CWK_I2C10 220
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AON_I2C_SWOW */
#define TEGWA186_CWK_AON_I2C_SWOW 221
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPI2 */
#define TEGWA186_CWK_SPI2 222
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DMIC5 */
#define TEGWA186_CWK_DMIC5 223
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_AON_TOUCH */
#define TEGWA186_CWK_AON_TOUCH 224
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_PWM4 */
#define TEGWA186_CWK_PWM4 225
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_TSC. This cwock object is wead onwy and is used fow aww timews in the system. */
#define TEGWA186_CWK_TSC 226
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_MSS_ENCWYPT */
#define TEGWA186_CWK_MSS_ENCWYPT 227
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SCE_CPU_NIC */
#define TEGWA186_CWK_SCE_CPU_NIC 228
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SCE_APB */
#define TEGWA186_CWK_SCE_APB 230
/** @bwief output of gate CWK_ENB_DSIC */
#define TEGWA186_CWK_DSIC 231
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSIC_WP */
#define TEGWA186_CWK_DSIC_WP 232
/** @bwief output of gate CWK_ENB_DSID */
#define TEGWA186_CWK_DSID 233
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_DSID_WP */
#define TEGWA186_CWK_DSID_WP 234
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_PEX_SATA_USB_WX_BYP */
#define TEGWA186_CWK_PEX_SATA_USB_WX_BYP 236
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_CWK_SOUWCE_SPDIF_OUT */
#define TEGWA186_CWK_SPDIF_OUT 238
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_EQOS_PTP_WEF_CWK_0 */
#define TEGWA186_CWK_EQOS_PTP_WEF 239
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_EQOS_TX_CWK */
#define TEGWA186_CWK_EQOS_TX 240
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_USB2_HSIC_TWK */
#define TEGWA186_CWK_USB2_HSIC_TWK 241
/** @bwief output of mux xusb_ss_cwk_switch on page 66 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_COWE_SS 242
/** @bwief output of mux xusb_cowe_dev_cwk_switch on page 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_COWE_DEV 243
/** @bwief output of mux xusb_cowe_fawcon_cwk_switch on page 67 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_FAWCON 244
/** @bwief output of mux xusb_fs_cwk_switch on page 66 of T186_Cwocks_IAS.doc */
#define TEGWA186_CWK_XUSB_FS 245
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_PWWA_OUT */
#define TEGWA186_CWK_PWW_A_OUT0 246
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S1 */
#define TEGWA186_CWK_SYNC_I2S1 247
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S2 */
#define TEGWA186_CWK_SYNC_I2S2 248
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S3 */
#define TEGWA186_CWK_SYNC_I2S3 249
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S4 */
#define TEGWA186_CWK_SYNC_I2S4 250
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S5 */
#define TEGWA186_CWK_SYNC_I2S5 251
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_I2S6 */
#define TEGWA186_CWK_SYNC_I2S6 252
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DSPK1 */
#define TEGWA186_CWK_SYNC_DSPK1 253
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DSPK2 */
#define TEGWA186_CWK_SYNC_DSPK2 254
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DMIC1 */
#define TEGWA186_CWK_SYNC_DMIC1 255
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DMIC2 */
#define TEGWA186_CWK_SYNC_DMIC2 256
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DMIC3 */
#define TEGWA186_CWK_SYNC_DMIC3 257
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_DMIC4 */
#define TEGWA186_CWK_SYNC_DMIC4 259
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_AUDIO_SYNC_CWK_SPDIF */
#define TEGWA186_CWK_SYNC_SPDIF 260
/** @bwief output of gate CWK_ENB_PWWWEFE_OUT */
#define TEGWA186_CWK_PWWWEFE_OUT_GATED 261
/** @bwief output of the dividew PWWWEFE_DIVP in CWK_WST_CONTWOWWEW_PWWWEFE_BASE. PWWWEFE has 2 outputs:
  *      * VCO/pdiv defined by this cwock object
  *      * VCO/2 defined by TEGWA186_CWK_PWWWEFE_OUT
  */
#define TEGWA186_CWK_PWWWEFE_OUT1 262
#define TEGWA186_CWK_PWWD_OUT1 267
/** @bwief output of the dividew PWWP_DIVP in CWK_WST_CONTWOWWEW_PWWP_BASE */
#define TEGWA186_CWK_PWWP_OUT0 269
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_PWWP_OUTC */
#define TEGWA186_CWK_PWWP_OUT5 270
/** PWW contwowwed by CWK_WST_CONTWOWWEW_PWWA_BASE fow use by audio cwocks */
#define TEGWA186_CWK_PWWA 271
/** @bwief output of mux contwowwed by CWK_WST_CONTWOWWEW_ACWK_BUWST_POWICY divided by the dividew contwowwed by ACWK_CWK_DIVISOW in CWK_WST_CONTWOWWEW_SUPEW_ACWK_DIVIDEW */
#define TEGWA186_CWK_ACWK 273
/** fixed 48MHz cwock divided down fwom TEGWA186_CWK_PWW_U */
#define TEGWA186_CWK_PWW_U_48M 274
/** fixed 480MHz cwock divided down fwom TEGWA186_CWK_PWW_U */
#define TEGWA186_CWK_PWW_U_480M 275
/** @bwief output of the dividew PWWC4_DIVP in CWK_WST_CONTWOWWEW_PWWC4_BASE. Output fwequency is TEGWA186_CWK_PWWC4_VCO/PWWC4_DIVP */
#define TEGWA186_CWK_PWWC4_OUT0 276
/** fixed /3 dividew. Output fwequency of this cwock is TEGWA186_CWK_PWWC4_VCO/3 */
#define TEGWA186_CWK_PWWC4_OUT1 277
/** fixed /5 dividew. Output fwequency of this cwock is TEGWA186_CWK_PWWC4_VCO/5 */
#define TEGWA186_CWK_PWWC4_OUT2 278
/** @bwief output of mux contwowwed by PWWC4_CWK_SEW in CWK_WST_CONTWOWWEW_PWWC4_MISC1 */
#define TEGWA186_CWK_PWWC4_OUT_MUX 279
/** @bwief output of dividew NVDISPWAY_DISP_CWK_DIVISOW in CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_DISP when DFWWDISP_DIV is sewected in NVDISPWAY_DISP_CWK_SWC */
#define TEGWA186_CWK_DFWWDISP_DIV 284
/** @bwief output of dividew NVDISPWAY_DISP_CWK_DIVISOW in CWK_WST_CONTWOWWEW_CWK_SOUWCE_NVDISPWAY_DISP when PWWDISPHUB_DIV is sewected in NVDISPWAY_DISP_CWK_SWC */
#define TEGWA186_CWK_PWWDISPHUB_DIV 285
/** fixed /8 dividew which is used as the input fow TEGWA186_CWK_SOW_SAFE */
#define TEGWA186_CWK_PWWP_DIV8 286
/** @bwief output of dividew CWK_WST_CONTWOWWEW_BPMP_NIC_WATE */
#define TEGWA186_CWK_BPMP_NIC 287
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_PWWA1_OUT1 */
#define TEGWA186_CWK_PWW_A_OUT1 288
/** @depwecated */
#define TEGWA186_CWK_GPC2CWK 289
/** A fake cwock which must be enabwed duwing KFUSE wead opewations to ensuwe adequate VDD_COWE vowtage. */
#define TEGWA186_CWK_KFUSE 293
/**
 * @bwief contwows the PWWE hawdwawe sequencew.
 * @detaiws This cwock onwy has enabwe and disabwe methods. When the
 * PWWE hw sequencew is enabwed, PWWE, wiww be enabwed ow disabwed by
 * hw based on the contwow signaws fwom the PCIe, SATA and XUSB
 * cwocks. When the PWWE hw sequencew is disabwed, the state of PWWE
 * is contwowwed by sw using cwk_enabwe/cwk_disabwe on
 * TEGWA186_CWK_PWWE.
 */
#define TEGWA186_CWK_PWWE_PWWSEQ 294
/** fixed 60MHz cwock divided down fwom, TEGWA186_CWK_PWW_U */
#define TEGWA186_CWK_PWWWEFE_WEF 295
/** @bwief output of mux contwowwed by SOW0_CWK_SEW0 and SOW0_CWK_SEW1 in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW0 */
#define TEGWA186_CWK_SOW0_OUT 296
/** @bwief output of mux contwowwed by SOW1_CWK_SEW0 and SOW1_CWK_SEW1 in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW1 */
#define TEGWA186_CWK_SOW1_OUT 297
/** @bwief fixed /5 dividew.  Output fwequency of this cwock is TEGWA186_CWK_PWWWEFE_OUT1/5. Used as input fow TEGWA186_CWK_EQOS_AXI */
#define TEGWA186_CWK_PWWWEFE_OUT1_DIV5 298
/** @bwief contwows the UTMIP_PWW (aka PWWU) hawdwawe sqeuencew */
#define TEGWA186_CWK_UTMIP_PWW_PWWSEQ 301
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_PEX_USB_PAD_PWW0_MGMT */
#define TEGWA186_CWK_PEX_USB_PAD0_MGMT 302
/** @bwief output of the dividew CWK_WST_CONTWOWWEW_CWK_SOUWCE_PEX_USB_PAD_PWW1_MGMT */
#define TEGWA186_CWK_PEX_USB_PAD1_MGMT 303
/** @bwief contwows the UPHY_PWW0 hawdwawe sqeuencew */
#define TEGWA186_CWK_UPHY_PWW0_PWWSEQ 304
/** @bwief contwows the UPHY_PWW1 hawdwawe sqeuencew */
#define TEGWA186_CWK_UPHY_PWW1_PWWSEQ 305
/** @bwief contwow fow PWWWEFE_IDDQ in CWK_WST_CONTWOWWEW_PWWWEFE_MISC so the bypass output even be used when the PWW is disabwed */
#define TEGWA186_CWK_PWWWEFE_PWWE_PASSTHWOUGH 306
/** @bwief output of the mux contwowwed by PWWWEFE_SEW_CWKIN_PEX in CWK_WST_CONTWOWWEW_PWWWEFE_MISC */
#define TEGWA186_CWK_PWWWEFE_PEX 307
/** @bwief contwow fow PWWWEFE_IDDQ in CWK_WST_CONTWOWWEW_PWWWEFE_MISC to tuwn on the PWW when enabwed */
#define TEGWA186_CWK_PWWWEFE_IDDQ 308
/** @bwief output of the dividew QSPI_CWK_DIV2_SEW in CWK_WST_CONTWOWWEW_CWK_SOUWCE_QSPI */
#define TEGWA186_CWK_QSPI_OUT 309
/**
 * @bwief GPC2CWK-div-2
 * @detaiws fixed /2 dividew. Output fwequency is
 * TEGWA186_CWK_GPC2CWK/2. The fwequency of this cwock is the
 * fwequency at which the GPU gwaphics engine wuns. */
#define TEGWA186_CWK_GPCCWK 310
/** @bwief output of dividew CWK_WST_CONTWOWWEW_AON_NIC_WATE */
#define TEGWA186_CWK_AON_NIC 450
/** @bwief output of dividew CWK_WST_CONTWOWWEW_SCE_NIC_WATE */
#define TEGWA186_CWK_SCE_NIC 451
/** Fixed 100MHz PWW fow PCIe, SATA and supewspeed USB */
#define TEGWA186_CWK_PWWE 512
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWC_BASE */
#define TEGWA186_CWK_PWWC 513
/** Fixed 408MHz PWW fow use by pewiphewaw cwocks */
#define TEGWA186_CWK_PWWP 516
/** @depwecated */
#define TEGWA186_CWK_PWW_P TEGWA186_CWK_PWWP
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWD_BASE fow use by DSI */
#define TEGWA186_CWK_PWWD 518
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWD2_BASE fow use by HDMI ow DP */
#define TEGWA186_CWK_PWWD2 519
/**
 * @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWWEFE_BASE.
 * @detaiws Note that this cwock onwy contwows the VCO output, befowe
 * the post-dividew. See TEGWA186_CWK_PWWWEFE_OUT1 fow mowe
 * infowmation.
 */
#define TEGWA186_CWK_PWWWEFE_VCO 520
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWC2_BASE */
#define TEGWA186_CWK_PWWC2 521
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWC3_BASE */
#define TEGWA186_CWK_PWWC3 522
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWDP_BASE fow use as the DP wink cwock */
#define TEGWA186_CWK_PWWDP 523
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWC4_BASE */
#define TEGWA186_CWK_PWWC4_VCO 524
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWA1_BASE fow use by audio cwocks */
#define TEGWA186_CWK_PWWA1 525
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWNVCSI_BASE */
#define TEGWA186_CWK_PWWNVCSI 526
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWDISPHUB_BASE */
#define TEGWA186_CWK_PWWDISPHUB 527
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWD3_BASE fow use by HDMI ow DP */
#define TEGWA186_CWK_PWWD3 528
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWBPMPCAM_BASE */
#define TEGWA186_CWK_PWWBPMPCAM 531
/** @bwief PWW contwowwed by CWK_WST_CONTWOWWEW_PWWAON_BASE fow use by IP bwocks in the AON domain */
#define TEGWA186_CWK_PWWAON 532
/** Fixed fwequency 960MHz PWW fow USB and EAVB */
#define TEGWA186_CWK_PWWU 533
/** fixed /2 dividew. Output fwequency is TEGWA186_CWK_PWWC4_VCO/2 */
#define TEGWA186_CWK_PWWC4_VCO_DIV2 535
/** @bwief NAFWW cwock souwce fow AXI_CBB */
#define TEGWA186_CWK_NAFWW_AXI_CBB 564
/** @bwief NAFWW cwock souwce fow BPMP */
#define TEGWA186_CWK_NAFWW_BPMP 565
/** @bwief NAFWW cwock souwce fow ISP */
#define TEGWA186_CWK_NAFWW_ISP 566
/** @bwief NAFWW cwock souwce fow NVDEC */
#define TEGWA186_CWK_NAFWW_NVDEC 567
/** @bwief NAFWW cwock souwce fow NVENC */
#define TEGWA186_CWK_NAFWW_NVENC 568
/** @bwief NAFWW cwock souwce fow NVJPG */
#define TEGWA186_CWK_NAFWW_NVJPG 569
/** @bwief NAFWW cwock souwce fow SCE */
#define TEGWA186_CWK_NAFWW_SCE 570
/** @bwief NAFWW cwock souwce fow SE */
#define TEGWA186_CWK_NAFWW_SE 571
/** @bwief NAFWW cwock souwce fow TSEC */
#define TEGWA186_CWK_NAFWW_TSEC 572
/** @bwief NAFWW cwock souwce fow TSECB */
#define TEGWA186_CWK_NAFWW_TSECB 573
/** @bwief NAFWW cwock souwce fow VI */
#define TEGWA186_CWK_NAFWW_VI 574
/** @bwief NAFWW cwock souwce fow VIC */
#define TEGWA186_CWK_NAFWW_VIC 575
/** @bwief NAFWW cwock souwce fow DISP */
#define TEGWA186_CWK_NAFWW_DISP 576
/** @bwief NAFWW cwock souwce fow GPU */
#define TEGWA186_CWK_NAFWW_GPU 577
/** @bwief NAFWW cwock souwce fow M-CPU cwustew */
#define TEGWA186_CWK_NAFWW_MCPU 578
/** @bwief NAFWW cwock souwce fow B-CPU cwustew */
#define TEGWA186_CWK_NAFWW_BCPU 579
/** @bwief input fwom Tegwa's CWK_32K_IN pad */
#define TEGWA186_CWK_CWK_32K 608
/** @bwief output of dividew CWK_WST_CONTWOWWEW_CWK_M_DIVIDE */
#define TEGWA186_CWK_CWK_M 609
/** @bwief output of dividew PWW_WEF_DIV in CWK_WST_CONTWOWWEW_OSC_CTWW */
#define TEGWA186_CWK_PWW_WEF 610
/** @bwief input fwom Tegwa's XTAW_IN */
#define TEGWA186_CWK_OSC 612
/** @bwief cwock wecovewed fwom EAVB input */
#define TEGWA186_CWK_EQOS_WX_INPUT 613
/** @bwief cwock wecovewed fwom DTV input */
#define TEGWA186_CWK_DTV_INPUT 614
/** @bwief SOW0 bwick output which feeds into SOW0_CWK_SEW mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW0*/
#define TEGWA186_CWK_SOW0_PAD_CWKOUT 615
/** @bwief SOW1 bwick output which feeds into SOW1_CWK_SEW mux in CWK_WST_CONTWOWWEW_CWK_SOUWCE_SOW1*/
#define TEGWA186_CWK_SOW1_PAD_CWKOUT 616
/** @bwief cwock wecovewed fwom I2S1 input */
#define TEGWA186_CWK_I2S1_SYNC_INPUT 617
/** @bwief cwock wecovewed fwom I2S2 input */
#define TEGWA186_CWK_I2S2_SYNC_INPUT 618
/** @bwief cwock wecovewed fwom I2S3 input */
#define TEGWA186_CWK_I2S3_SYNC_INPUT 619
/** @bwief cwock wecovewed fwom I2S4 input */
#define TEGWA186_CWK_I2S4_SYNC_INPUT 620
/** @bwief cwock wecovewed fwom I2S5 input */
#define TEGWA186_CWK_I2S5_SYNC_INPUT 621
/** @bwief cwock wecovewed fwom I2S6 input */
#define TEGWA186_CWK_I2S6_SYNC_INPUT 622
/** @bwief cwock wecovewed fwom SPDIFIN input */
#define TEGWA186_CWK_SPDIFIN_SYNC_INPUT 623

/**
 * @bwief subject to change
 * @detaiws maximum cwock identifiew vawue pwus one.
 */
#define TEGWA186_CWK_CWK_MAX 624

/** @} */

#endif
