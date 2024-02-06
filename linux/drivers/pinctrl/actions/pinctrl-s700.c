// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww S700 Pinctww dwivew
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Authow: David Wiu <wiuwei@actions-semi.com>
 *
 * Authow: Pathiban Nawwathambi <pn@denx.de>
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude "pinctww-oww.h"

/* Pinctww wegistews offset */
#define MFCTW0			(0x0040)
#define MFCTW1			(0x0044)
#define MFCTW2			(0x0048)
#define MFCTW3			(0x004C)
#define PAD_PUWWCTW0		(0x0060)
#define PAD_PUWWCTW1		(0x0064)
#define PAD_PUWWCTW2		(0x0068)
#define PAD_ST0			(0x006C)
#define PAD_ST1			(0x0070)
#define PAD_CTW			(0x0074)
#define PAD_DWV0		(0x0080)
#define PAD_DWV1		(0x0084)
#define PAD_DWV2		(0x0088)

/*
 * Most pins affected by the pinmux can awso be GPIOs. Define these fiwst.
 * These must match how the GPIO dwivew names/numbews its pins.
 */
#define _GPIOA(offset)		(offset)
#define _GPIOB(offset)		(32 + (offset))
#define _GPIOC(offset)		(64 + (offset))
#define _GPIOD(offset)		(96 + (offset))
#define _GPIOE(offset)		(128 + (offset))

/* Aww non-GPIO pins fowwow */
#define NUM_GPIOS		(_GPIOE(7) + 1)
#define _PIN(offset)		(NUM_GPIOS + (offset))

/* Ethewnet MAC */
#define ETH_TXD0		_GPIOA(14)
#define ETH_TXD1		_GPIOA(15)
#define ETH_TXD2		_GPIOE(4)
#define ETH_TXD3		_GPIOE(5)
#define ETH_TXEN		_GPIOA(16)
#define ETH_WXEW		_GPIOA(17)
#define ETH_CWS_DV		_GPIOA(18)
#define ETH_WXD1		_GPIOA(19)
#define ETH_WXD0		_GPIOA(20)
#define ETH_WXD2		_GPIOE(6)
#define ETH_WXD3		_GPIOE(7)
#define ETH_WEF_CWK		_GPIOA(21)
#define ETH_MDC			_GPIOA(22)
#define ETH_MDIO		_GPIOA(23)

/* SIWQ */
#define SIWQ0			_GPIOA(24)
#define SIWQ1			_GPIOA(25)
#define SIWQ2			_GPIOA(26)

/* I2S */
#define I2S_D0			_GPIOA(27)
#define I2S_BCWK0		_GPIOA(28)
#define I2S_WWCWK0		_GPIOA(29)
#define I2S_MCWK0		_GPIOA(30)
#define I2S_D1			_GPIOA(31)
#define I2S_BCWK1		_GPIOB(0)
#define I2S_WWCWK1		_GPIOB(1)
#define I2S_MCWK1		_GPIOB(2)

/* PCM1 */
#define PCM1_IN			_GPIOD(28)
#define PCM1_CWK		_GPIOD(29)
#define PCM1_SYNC		_GPIOD(30)
#define PCM1_OUT		_GPIOD(31)

/* KEY */
#define KS_IN0			_GPIOB(3)
#define KS_IN1			_GPIOB(4)
#define KS_IN2			_GPIOB(5)
#define KS_IN3			_GPIOB(6)
#define KS_OUT0			_GPIOB(7)
#define KS_OUT1			_GPIOB(8)
#define KS_OUT2			_GPIOB(9)

/* WVDS */
#define WVDS_OEP		_GPIOB(10)
#define WVDS_OEN		_GPIOB(11)
#define WVDS_ODP		_GPIOB(12)
#define WVDS_ODN		_GPIOB(13)
#define WVDS_OCP		_GPIOB(14)
#define WVDS_OCN		_GPIOB(15)
#define WVDS_OBP		_GPIOB(16)
#define WVDS_OBN		_GPIOB(17)
#define WVDS_OAP		_GPIOB(18)
#define WVDS_OAN		_GPIOB(19)
#define WVDS_EEP		_GPIOB(20)
#define WVDS_EEN		_GPIOB(21)
#define WVDS_EDP		_GPIOB(22)
#define WVDS_EDN		_GPIOB(23)
#define WVDS_ECP		_GPIOB(24)
#define WVDS_ECN		_GPIOB(25)
#define WVDS_EBP		_GPIOB(26)
#define WVDS_EBN		_GPIOB(27)
#define WVDS_EAP		_GPIOB(28)
#define WVDS_EAN		_GPIOB(29)
#define WCD0_D18		_GPIOB(30)
#define WCD0_D2			_GPIOB(31)

/* DSI */
#define DSI_DP3			_GPIOC(0)
#define DSI_DN3			_GPIOC(1)
#define DSI_DP1			_GPIOC(2)
#define DSI_DN1			_GPIOC(3)
#define DSI_CP			_GPIOC(4)
#define DSI_CN			_GPIOC(5)
#define DSI_DP0			_GPIOC(6)
#define DSI_DN0			_GPIOC(7)
#define DSI_DP2			_GPIOC(8)
#define DSI_DN2			_GPIOC(9)

/* SD */
#define SD0_D0			_GPIOC(10)
#define SD0_D1			_GPIOC(11)
#define SD0_D2			_GPIOC(12)
#define SD0_D3			_GPIOC(13)
#define SD0_D4			_GPIOC(14)
#define SD0_D5			_GPIOC(15)
#define SD0_D6			_GPIOC(16)
#define SD0_D7			_GPIOC(17)
#define SD0_CMD			_GPIOC(18)
#define SD0_CWK			_GPIOC(19)
#define SD1_CMD			_GPIOC(20)
#define SD1_CWK			_GPIOC(21)
#define SD1_D0			SD0_D4
#define SD1_D1			SD0_D5
#define SD1_D2			SD0_D6
#define SD1_D3			SD0_D7

/* SPI */
#define SPI0_SS			_GPIOC(23)
#define SPI0_MISO		_GPIOC(24)

/* UAWT fow consowe */
#define UAWT0_WX		_GPIOC(26)
#define UAWT0_TX		_GPIOC(27)

/* UAWT fow Bwuetooth */
#define UAWT2_WX		_GPIOD(18)
#define UAWT2_TX		_GPIOD(19)
#define UAWT2_WTSB		_GPIOD(20)
#define UAWT2_CTSB		_GPIOD(21)

/* UAWT fow 3G */
#define UAWT3_WX		_GPIOD(22)
#define UAWT3_TX		_GPIOD(23)
#define UAWT3_WTSB		_GPIOD(24)
#define UAWT3_CTSB		_GPIOD(25)

/* I2C */
#define I2C0_SCWK		_GPIOC(28)
#define I2C0_SDATA		_GPIOC(29)
#define I2C1_SCWK		_GPIOE(0)
#define I2C1_SDATA		_GPIOE(1)
#define I2C2_SCWK		_GPIOE(2)
#define I2C2_SDATA		_GPIOE(3)

/* CSI*/
#define CSI_DN0			_PIN(0)
#define CSI_DP0			_PIN(1)
#define CSI_DN1			_PIN(2)
#define CSI_DP1			_PIN(3)
#define CSI_CN			_PIN(4)
#define CSI_CP			_PIN(5)
#define CSI_DN2			_PIN(6)
#define CSI_DP2			_PIN(7)
#define CSI_DN3			_PIN(8)
#define CSI_DP3			_PIN(9)

/* Sensow */
#define SENSOW0_PCWK		_GPIOC(31)
#define SENSOW0_CKOUT		_GPIOD(10)

/* NAND (1.8v / 3.3v) */
#define DNAND_D0		_PIN(10)
#define DNAND_D1		_PIN(11)
#define DNAND_D2		_PIN(12)
#define DNAND_D3		_PIN(13)
#define DNAND_D4		_PIN(14)
#define DNAND_D5		_PIN(15)
#define DNAND_D6		_PIN(16)
#define DNAND_D7		_PIN(17)
#define DNAND_WWB		_PIN(18)
#define DNAND_WDB		_PIN(19)
#define DNAND_WDBN		_PIN(20)
#define DNAND_DQS		_GPIOA(12)
#define DNAND_DQSN		_GPIOA(13)
#define DNAND_WB0		_PIN(21)
#define DNAND_AWE		_GPIOD(12)
#define DNAND_CWE		_GPIOD(13)
#define DNAND_CEB0		_GPIOD(14)
#define DNAND_CEB1		_GPIOD(15)
#define DNAND_CEB2		_GPIOD(16)
#define DNAND_CEB3		_GPIOD(17)

/* System */
#define POWB			_PIN(22)
#define CWKO_25M		_PIN(23)
#define BSEW			_PIN(24)
#define PKG0			_PIN(25)
#define PKG1			_PIN(26)
#define PKG2			_PIN(27)
#define PKG3			_PIN(28)

#define _FIWSTPAD		_GPIOA(0)
#define _WASTPAD		PKG3
#define NUM_PADS		(_PIN(28) + 1)

/* Pad names fow the pinmux subsystem */
static const stwuct pinctww_pin_desc s700_pads[] = {
	PINCTWW_PIN(ETH_TXD0, "eth_txd0"),
	PINCTWW_PIN(ETH_TXD1, "eth_txd1"),
	PINCTWW_PIN(ETH_TXD2, "eth_txd2"),
	PINCTWW_PIN(ETH_TXD3, "eth_txd3"),
	PINCTWW_PIN(ETH_TXEN, "eth_txen"),
	PINCTWW_PIN(ETH_WXEW, "eth_wxew"),
	PINCTWW_PIN(ETH_CWS_DV, "eth_cws_dv"),
	PINCTWW_PIN(ETH_WXD1, "eth_wxd1"),
	PINCTWW_PIN(ETH_WXD0, "eth_wxd0"),
	PINCTWW_PIN(ETH_WXD2, "eth_wxd2"),
	PINCTWW_PIN(ETH_WXD3, "eth_wxd3"),
	PINCTWW_PIN(ETH_WEF_CWK, "eth_wef_cwk"),
	PINCTWW_PIN(ETH_MDC, "eth_mdc"),
	PINCTWW_PIN(ETH_MDIO, "eth_mdio"),
	PINCTWW_PIN(SIWQ0, "siwq0"),
	PINCTWW_PIN(SIWQ1, "siwq1"),
	PINCTWW_PIN(SIWQ2, "siwq2"),
	PINCTWW_PIN(I2S_D0, "i2s_d0"),
	PINCTWW_PIN(I2S_BCWK0, "i2s_bcwk0"),
	PINCTWW_PIN(I2S_WWCWK0, "i2s_wwcwk0"),
	PINCTWW_PIN(I2S_MCWK0, "i2s_mcwk0"),
	PINCTWW_PIN(I2S_D1, "i2s_d1"),
	PINCTWW_PIN(I2S_BCWK1, "i2s_bcwk1"),
	PINCTWW_PIN(I2S_WWCWK1, "i2s_wwcwk1"),
	PINCTWW_PIN(I2S_MCWK1, "i2s_mcwk1"),
	PINCTWW_PIN(PCM1_IN, "pcm1_in"),
	PINCTWW_PIN(PCM1_CWK, "pcm1_cwk"),
	PINCTWW_PIN(PCM1_SYNC, "pcm1_sync"),
	PINCTWW_PIN(PCM1_OUT, "pcm1_out"),
	PINCTWW_PIN(KS_IN0, "ks_in0"),
	PINCTWW_PIN(KS_IN1, "ks_in1"),
	PINCTWW_PIN(KS_IN2, "ks_in2"),
	PINCTWW_PIN(KS_IN3, "ks_in3"),
	PINCTWW_PIN(KS_OUT0, "ks_out0"),
	PINCTWW_PIN(KS_OUT1, "ks_out1"),
	PINCTWW_PIN(KS_OUT2, "ks_out2"),
	PINCTWW_PIN(WVDS_OEP, "wvds_oep"),
	PINCTWW_PIN(WVDS_OEN, "wvds_oen"),
	PINCTWW_PIN(WVDS_ODP, "wvds_odp"),
	PINCTWW_PIN(WVDS_ODN, "wvds_odn"),
	PINCTWW_PIN(WVDS_OCP, "wvds_ocp"),
	PINCTWW_PIN(WVDS_OCN, "wvds_ocn"),
	PINCTWW_PIN(WVDS_OBP, "wvds_obp"),
	PINCTWW_PIN(WVDS_OBN, "wvds_obn"),
	PINCTWW_PIN(WVDS_OAP, "wvds_oap"),
	PINCTWW_PIN(WVDS_OAN, "wvds_oan"),
	PINCTWW_PIN(WVDS_EEP, "wvds_eep"),
	PINCTWW_PIN(WVDS_EEN, "wvds_een"),
	PINCTWW_PIN(WVDS_EDP, "wvds_edp"),
	PINCTWW_PIN(WVDS_EDN, "wvds_edn"),
	PINCTWW_PIN(WVDS_ECP, "wvds_ecp"),
	PINCTWW_PIN(WVDS_ECN, "wvds_ecn"),
	PINCTWW_PIN(WVDS_EBP, "wvds_ebp"),
	PINCTWW_PIN(WVDS_EBN, "wvds_ebn"),
	PINCTWW_PIN(WVDS_EAP, "wvds_eap"),
	PINCTWW_PIN(WVDS_EAN, "wvds_ean"),
	PINCTWW_PIN(WCD0_D18, "wcd0_d18"),
	PINCTWW_PIN(WCD0_D2, "wcd0_d2"),
	PINCTWW_PIN(DSI_DP3, "dsi_dp3"),
	PINCTWW_PIN(DSI_DN3, "dsi_dn3"),
	PINCTWW_PIN(DSI_DP1, "dsi_dp1"),
	PINCTWW_PIN(DSI_DN1, "dsi_dn1"),
	PINCTWW_PIN(DSI_CP, "dsi_cp"),
	PINCTWW_PIN(DSI_CN, "dsi_cn"),
	PINCTWW_PIN(DSI_DP0, "dsi_dp0"),
	PINCTWW_PIN(DSI_DN0, "dsi_dn0"),
	PINCTWW_PIN(DSI_DP2, "dsi_dp2"),
	PINCTWW_PIN(DSI_DN2, "dsi_dn2"),
	PINCTWW_PIN(SD0_D0, "sd0_d0"),
	PINCTWW_PIN(SD0_D1, "sd0_d1"),
	PINCTWW_PIN(SD0_D2, "sd0_d2"),
	PINCTWW_PIN(SD0_D3, "sd0_d3"),
	PINCTWW_PIN(SD1_D0, "sd1_d0"),
	PINCTWW_PIN(SD1_D1, "sd1_d1"),
	PINCTWW_PIN(SD1_D2, "sd1_d2"),
	PINCTWW_PIN(SD1_D3, "sd1_d3"),
	PINCTWW_PIN(SD0_CMD, "sd0_cmd"),
	PINCTWW_PIN(SD0_CWK, "sd0_cwk"),
	PINCTWW_PIN(SD1_CMD, "sd1_cmd"),
	PINCTWW_PIN(SD1_CWK, "sd1_cwk"),
	PINCTWW_PIN(SPI0_SS, "spi0_ss"),
	PINCTWW_PIN(SPI0_MISO, "spi0_miso"),
	PINCTWW_PIN(UAWT0_WX, "uawt0_wx"),
	PINCTWW_PIN(UAWT0_TX, "uawt0_tx"),
	PINCTWW_PIN(UAWT2_WX, "uawt2_wx"),
	PINCTWW_PIN(UAWT2_TX, "uawt2_tx"),
	PINCTWW_PIN(UAWT2_WTSB, "uawt2_wtsb"),
	PINCTWW_PIN(UAWT2_CTSB, "uawt2_ctsb"),
	PINCTWW_PIN(UAWT3_WX, "uawt3_wx"),
	PINCTWW_PIN(UAWT3_TX, "uawt3_tx"),
	PINCTWW_PIN(UAWT3_WTSB, "uawt3_wtsb"),
	PINCTWW_PIN(UAWT3_CTSB, "uawt3_ctsb"),
	PINCTWW_PIN(I2C0_SCWK, "i2c0_scwk"),
	PINCTWW_PIN(I2C0_SDATA, "i2c0_sdata"),
	PINCTWW_PIN(I2C1_SCWK, "i2c1_scwk"),
	PINCTWW_PIN(I2C1_SDATA, "i2c1_sdata"),
	PINCTWW_PIN(I2C2_SCWK, "i2c2_scwk"),
	PINCTWW_PIN(I2C2_SDATA, "i2c2_sdata"),
	PINCTWW_PIN(CSI_DN0, "csi_dn0"),
	PINCTWW_PIN(CSI_DP0, "csi_dp0"),
	PINCTWW_PIN(CSI_DN1, "csi_dn1"),
	PINCTWW_PIN(CSI_DP1, "csi_dp1"),
	PINCTWW_PIN(CSI_CN, "csi_cn"),
	PINCTWW_PIN(CSI_CP, "csi_cp"),
	PINCTWW_PIN(CSI_DN2, "csi_dn2"),
	PINCTWW_PIN(CSI_DP2, "csi_dp2"),
	PINCTWW_PIN(CSI_DN3, "csi_dn3"),
	PINCTWW_PIN(CSI_DP3, "csi_dp3"),
	PINCTWW_PIN(SENSOW0_PCWK, "sensow0_pcwk"),
	PINCTWW_PIN(SENSOW0_CKOUT, "sensow0_ckout"),
	PINCTWW_PIN(DNAND_D0, "dnand_d0"),
	PINCTWW_PIN(DNAND_D1, "dnand_d1"),
	PINCTWW_PIN(DNAND_D2, "dnand_d2"),
	PINCTWW_PIN(DNAND_D3, "dnand_d3"),
	PINCTWW_PIN(DNAND_D4, "dnand_d4"),
	PINCTWW_PIN(DNAND_D5, "dnand_d5"),
	PINCTWW_PIN(DNAND_D6, "dnand_d6"),
	PINCTWW_PIN(DNAND_D7, "dnand_d7"),
	PINCTWW_PIN(DNAND_WWB, "dnand_wwb"),
	PINCTWW_PIN(DNAND_WDB, "dnand_wdb"),
	PINCTWW_PIN(DNAND_WDBN, "dnand_wdbn"),
	PINCTWW_PIN(DNAND_DQS, "dnand_dqs"),
	PINCTWW_PIN(DNAND_DQSN, "dnand_dqsn"),
	PINCTWW_PIN(DNAND_WB0, "dnand_wb0"),
	PINCTWW_PIN(DNAND_AWE, "dnand_awe"),
	PINCTWW_PIN(DNAND_CWE, "dnand_cwe"),
	PINCTWW_PIN(DNAND_CEB0, "dnand_ceb0"),
	PINCTWW_PIN(DNAND_CEB1, "dnand_ceb1"),
	PINCTWW_PIN(DNAND_CEB2, "dnand_ceb2"),
	PINCTWW_PIN(DNAND_CEB3, "dnand_ceb3"),
	PINCTWW_PIN(POWB, "powb"),
	PINCTWW_PIN(CWKO_25M, "cwko_25m"),
	PINCTWW_PIN(BSEW, "bsew"),
	PINCTWW_PIN(PKG0, "pkg0"),
	PINCTWW_PIN(PKG1, "pkg1"),
	PINCTWW_PIN(PKG2, "pkg2"),
	PINCTWW_PIN(PKG3, "pkg3"),
};

enum s700_pinmux_functions {
	S700_MUX_NOW,
	S700_MUX_ETH_WGMII,
	S700_MUX_ETH_SGMII,
	S700_MUX_SPI0,
	S700_MUX_SPI1,
	S700_MUX_SPI2,
	S700_MUX_SPI3,
	S700_MUX_SENS0,
	S700_MUX_SENS1,
	S700_MUX_UAWT0,
	S700_MUX_UAWT1,
	S700_MUX_UAWT2,
	S700_MUX_UAWT3,
	S700_MUX_UAWT4,
	S700_MUX_UAWT5,
	S700_MUX_UAWT6,
	S700_MUX_I2S0,
	S700_MUX_I2S1,
	S700_MUX_PCM1,
	S700_MUX_PCM0,
	S700_MUX_KS,
	S700_MUX_JTAG,
	S700_MUX_PWM0,
	S700_MUX_PWM1,
	S700_MUX_PWM2,
	S700_MUX_PWM3,
	S700_MUX_PWM4,
	S700_MUX_PWM5,
	S700_MUX_P0,
	S700_MUX_SD0,
	S700_MUX_SD1,
	S700_MUX_SD2,
	S700_MUX_I2C0,
	S700_MUX_I2C1,
	S700_MUX_I2C2,
	S700_MUX_I2C3,
	S700_MUX_DSI,
	S700_MUX_WVDS,
	S700_MUX_USB30,
	S700_MUX_CWKO_25M,
	S700_MUX_MIPI_CSI,
	S700_MUX_NAND,
	S700_MUX_SPDIF,
	S700_MUX_SIWQ0,
	S700_MUX_SIWQ1,
	S700_MUX_SIWQ2,
	S700_MUX_BT,
	S700_MUX_WCD0,
	S700_MUX_WESEWVED,
};

/* mfp0_31_30 wesewved */

/* wgmii_txd23 */
static unsigned int  wgmii_txd23_mfp_pads[]		= { ETH_TXD2, ETH_TXD3};
static unsigned int  wgmii_txd23_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_I2C1,
							    S700_MUX_UAWT3 };
/* wgmii_wxd2 */
static unsigned int  wgmii_wxd2_mfp_pads[]		= { ETH_WXD2 };
static unsigned int  wgmii_wxd2_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_PWM0,
							    S700_MUX_UAWT3 };
/* wgmii_wxd3 */
static unsigned int  wgmii_wxd3_mfp_pads[]		= { ETH_WXD3};
static unsigned int  wgmii_wxd3_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_PWM2,
							    S700_MUX_UAWT3 };
/* wcd0_d18 */
static unsigned int  wcd0_d18_mfp_pads[]		= { WCD0_D18 };
static unsigned int  wcd0_d18_mfp_funcs[]		= { S700_MUX_NOW,
							    S700_MUX_SENS1,
							    S700_MUX_PWM2,
							    S700_MUX_PWM4,
							    S700_MUX_WCD0 };
/* wgmii_txd01 */
static unsigned int  wgmii_txd01_mfp_pads[]		= { ETH_CWS_DV };
static unsigned int  wgmii_txd01_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_WESEWVED,
							    S700_MUX_SPI2,
							    S700_MUX_UAWT4,
							    S700_MUX_PWM4 };
/* wgmii_txd0 */
static unsigned int  wgmii_txd0_mfp_pads[]		= { ETH_TXD0 };
static unsigned int  wgmii_txd0_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_ETH_SGMII,
							    S700_MUX_SPI2,
							    S700_MUX_UAWT6,
							    S700_MUX_PWM4 };
/* wgmii_txd1 */
static unsigned int  wgmii_txd1_mfp_pads[]		= { ETH_TXD1 };
static unsigned int  wgmii_txd1_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_ETH_SGMII,
							    S700_MUX_SPI2,
							    S700_MUX_UAWT6,
							    S700_MUX_PWM5 };
/* wgmii_txen */
static unsigned int  wgmii_txen_mfp_pads[]		= { ETH_TXEN };
static unsigned int  wgmii_txen_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM0 };
/* wgmii_wxen */
static unsigned int  wgmii_wxen_mfp_pads[]		= { ETH_WXEW };
static unsigned int  wgmii_wxen_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM1 };
/* mfp0_12_11 wesewved */
/* wgmii_wxd1*/
static unsigned int  wgmii_wxd1_mfp_pads[]		= { ETH_WXD1 };
static unsigned int  wgmii_wxd1_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM2,
							    S700_MUX_UAWT5,
							    S700_MUX_ETH_SGMII };
/* wgmii_wxd0 */
static unsigned int  wgmii_wxd0_mfp_pads[]		= { ETH_WXD0 };
static unsigned int  wgmii_wxd0_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM3,
							    S700_MUX_UAWT5,
							    S700_MUX_ETH_SGMII };
/* wgmii_wef_cwk */
static unsigned int  wgmii_wef_cwk_mfp_pads[]		= { ETH_WEF_CWK };
static unsigned int  wgmii_wef_cwk_mfp_funcs[]		= { S700_MUX_ETH_WGMII,
							    S700_MUX_UAWT4,
							    S700_MUX_SPI2,
							    S700_MUX_WESEWVED,
							    S700_MUX_ETH_SGMII };
/* i2s_d0 */
static unsigned int  i2s_d0_mfp_pads[]			= { I2S_D0 };
static unsigned int  i2s_d0_mfp_funcs[]			= { S700_MUX_I2S0,
							    S700_MUX_NOW };
/* i2s_pcm1 */
static unsigned int  i2s_pcm1_mfp_pads[]		= { I2S_WWCWK0,
							    I2S_MCWK0 };
static unsigned int  i2s_pcm1_mfp_funcs[]		= { S700_MUX_I2S0,
							    S700_MUX_NOW,
							    S700_MUX_PCM1,
							    S700_MUX_BT };
/* i2s0_pcm0 */
static unsigned int  i2s0_pcm0_mfp_pads[]		= { I2S_BCWK0 };
static unsigned int  i2s0_pcm0_mfp_funcs[]		= { S700_MUX_I2S0,
							    S700_MUX_NOW,
							    S700_MUX_PCM0,
							    S700_MUX_BT };
/* i2s1_pcm0 */
static unsigned int  i2s1_pcm0_mfp_pads[]		= { I2S_BCWK1,
							    I2S_WWCWK1,
							    I2S_MCWK1 };

static unsigned int  i2s1_pcm0_mfp_funcs[]		= { S700_MUX_I2S1,
							    S700_MUX_NOW,
							    S700_MUX_PCM0,
							    S700_MUX_BT };
/* i2s_d1 */
static unsigned int  i2s_d1_mfp_pads[]			= { I2S_D1 };
static unsigned int  i2s_d1_mfp_funcs[]			= { S700_MUX_I2S1,
							    S700_MUX_NOW };
/* ks_in2 */
static unsigned int  ks_in2_mfp_pads[]			= { KS_IN2 };
static unsigned int  ks_in2_mfp_funcs[]			= { S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOW,
							    S700_MUX_BT,
							    S700_MUX_PWM0,
							    S700_MUX_SENS1,
							    S700_MUX_PWM0,
							    S700_MUX_P0 };
/* ks_in1 */
static unsigned int  ks_in1_mfp_pads[]			= { KS_IN1 };
static unsigned int  ks_in1_mfp_funcs[]			= { S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOW,
							    S700_MUX_BT,
							    S700_MUX_PWM5,
							    S700_MUX_SENS1,
							    S700_MUX_PWM1,
							    S700_MUX_USB30 };
/* ks_in0 */
static unsigned int  ks_in0_mfp_pads[]			= { KS_IN0 };
static unsigned int  ks_in0_mfp_funcs[]			= { S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOW,
							    S700_MUX_BT,
							    S700_MUX_PWM4,
							    S700_MUX_SENS1,
							    S700_MUX_PWM4,
							    S700_MUX_P0 };
/* ks_in3 */
static unsigned int  ks_in3_mfp_pads[]			= { KS_IN3 };
static unsigned int  ks_in3_mfp_funcs[]			= { S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOW,
							    S700_MUX_PWM1,
							    S700_MUX_BT,
							    S700_MUX_SENS1 };
/* ks_out0 */
static unsigned int  ks_out0_mfp_pads[]			= { KS_OUT0 };
static unsigned int  ks_out0_mfp_funcs[]		= { S700_MUX_KS,
							    S700_MUX_UAWT5,
							    S700_MUX_NOW,
							    S700_MUX_PWM2,
							    S700_MUX_BT,
							    S700_MUX_SENS1,
							    S700_MUX_SD0,
							    S700_MUX_UAWT4 };

/* ks_out1 */
static unsigned int  ks_out1_mfp_pads[]			= { KS_OUT1 };
static unsigned int  ks_out1_mfp_funcs[]		= { S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOW,
							    S700_MUX_PWM3,
							    S700_MUX_BT,
							    S700_MUX_SENS1,
							    S700_MUX_SD0,
							    S700_MUX_UAWT4 };
/* ks_out2 */
static unsigned int  ks_out2_mfp_pads[]			= { KS_OUT2 };
static unsigned int  ks_out2_mfp_funcs[]		= { S700_MUX_SD0,
							    S700_MUX_KS,
							    S700_MUX_NOW,
							    S700_MUX_PWM2,
							    S700_MUX_UAWT5,
							    S700_MUX_SENS1,
							    S700_MUX_BT };
/* wvds_o_pn */
static unsigned int  wvds_o_pn_mfp_pads[]		= { WVDS_OEP,
							    WVDS_OEN,
							    WVDS_ODP,
							    WVDS_ODN,
							    WVDS_OCP,
							    WVDS_OCN,
							    WVDS_OBP,
							    WVDS_OBN,
							    WVDS_OAP,
							    WVDS_OAN };

static unsigned int  wvds_o_pn_mfp_funcs[]		= { S700_MUX_WVDS,
							    S700_MUX_BT,
							    S700_MUX_WCD0 };

/* dsi_dn0 */
static unsigned int  dsi_dn0_mfp_pads[]			= { DSI_DN0 };
static unsigned int  dsi_dn0_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI0 };
/* dsi_dp2 */
static unsigned int  dsi_dp2_mfp_pads[]			= { DSI_DP2 };
static unsigned int  dsi_dp2_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI0,
							    S700_MUX_SD1 };
/* wcd0_d2 */
static unsigned int  wcd0_d2_mfp_pads[]			= { WCD0_D2 };
static unsigned int  wcd0_d2_mfp_funcs[]		= { S700_MUX_NOW,
							    S700_MUX_SD0,
							    S700_MUX_WESEWVED,
							    S700_MUX_PWM3,
							    S700_MUX_WCD0 };
/* dsi_dp3 */
static unsigned int  dsi_dp3_mfp_pads[]			= { DSI_DP3 };
static unsigned int  dsi_dp3_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_SD0,
							    S700_MUX_SD1,
							    S700_MUX_WCD0 };
/* dsi_dn3 */
static unsigned int  dsi_dn3_mfp_pads[]			= { DSI_DN3 };
static unsigned int  dsi_dn3_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_SD0,
							    S700_MUX_SD1,
							    S700_MUX_WCD0 };
/* dsi_dp0 */
static unsigned int  dsi_dp0_mfp_pads[]			= { DSI_DP0 };
static unsigned int  dsi_dp0_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_WESEWVED,
							    S700_MUX_SD0,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI0 };
/* wvds_ee_pn */
static unsigned int  wvds_ee_pn_mfp_pads[]		= { WVDS_EEP,
							    WVDS_EEN };
static unsigned int  wvds_ee_pn_mfp_funcs[]		= { S700_MUX_WVDS,
							    S700_MUX_NOW,
							    S700_MUX_BT,
							    S700_MUX_WCD0 };
/* uawt2_wx_tx */
static unsigned int  uawt2_wx_tx_mfp_pads[]		= { UAWT2_WX,
							    UAWT2_TX };
static unsigned int  uawt2_wx_tx_mfp_funcs[]		= { S700_MUX_UAWT2,
							    S700_MUX_NOW,
							    S700_MUX_SPI0,
							    S700_MUX_PCM0 };
/* spi0_i2c_pcm */
static unsigned int  spi0_i2c_pcm_mfp_pads[]		= { SPI0_SS,
							    SPI0_MISO };
static unsigned int  spi0_i2c_pcm_mfp_funcs[]		= { S700_MUX_SPI0,
							    S700_MUX_NOW,
							    S700_MUX_I2S1,
							    S700_MUX_PCM1,
							    S700_MUX_PCM0,
							    S700_MUX_I2C2 };
/* mfp2_31 wesewved */

/* dsi_dnp1_cp_d2 */
static unsigned int  dsi_dnp1_cp_d2_mfp_pads[]		= { DSI_DP1,
							    DSI_CP,
							    DSI_CN };
static unsigned int  dsi_dnp1_cp_d2_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_WCD0,
							    S700_MUX_WESEWVED };
/* dsi_dnp1_cp_d17 */
static unsigned int  dsi_dnp1_cp_d17_mfp_pads[]		= { DSI_DP1,
							    DSI_CP,
							    DSI_CN };

static unsigned int  dsi_dnp1_cp_d17_mfp_funcs[]	= { S700_MUX_DSI,
							    S700_MUX_WESEWVED,
							    S700_MUX_WCD0 };
/* wvds_e_pn */
static unsigned int  wvds_e_pn_mfp_pads[]		= { WVDS_EDP,
							    WVDS_EDN,
							    WVDS_ECP,
							    WVDS_ECN,
							    WVDS_EBP,
							    WVDS_EBN,
							    WVDS_EAP,
							    WVDS_EAN };

static unsigned int  wvds_e_pn_mfp_funcs[]		= { S700_MUX_WVDS,
							    S700_MUX_NOW,
							    S700_MUX_WCD0 };
/* dsi_dn2 */
static unsigned int  dsi_dn2_mfp_pads[]			= { DSI_DN2 };
static unsigned int  dsi_dn2_mfp_funcs[]		= { S700_MUX_DSI,
							    S700_MUX_WESEWVED,
							    S700_MUX_SD1,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI0 };
/* uawt2_wtsb */
static unsigned int  uawt2_wtsb_mfp_pads[]		= { UAWT2_WTSB };
static unsigned int  uawt2_wtsb_mfp_funcs[]		= { S700_MUX_UAWT2,
							    S700_MUX_UAWT0 };

/* uawt2_ctsb */
static unsigned int  uawt2_ctsb_mfp_pads[]		= { UAWT2_CTSB };
static unsigned int  uawt2_ctsb_mfp_funcs[]		= { S700_MUX_UAWT2,
							    S700_MUX_UAWT0 };
/* uawt3_wtsb */
static unsigned int  uawt3_wtsb_mfp_pads[]		= { UAWT3_WTSB };
static unsigned int  uawt3_wtsb_mfp_funcs[]		= { S700_MUX_UAWT3,
							    S700_MUX_UAWT5 };

/* uawt3_ctsb */
static unsigned int  uawt3_ctsb_mfp_pads[]		= { UAWT3_CTSB };
static unsigned int  uawt3_ctsb_mfp_funcs[]		= { S700_MUX_UAWT3,
							    S700_MUX_UAWT5 };
/* sd0_d0 */
static unsigned int  sd0_d0_mfp_pads[]			= { SD0_D0 };
static unsigned int  sd0_d0_mfp_funcs[]			= { S700_MUX_SD0,
							    S700_MUX_NOW,
							    S700_MUX_WESEWVED,
							    S700_MUX_JTAG,
							    S700_MUX_UAWT2,
							    S700_MUX_UAWT5 };
/* sd0_d1 */
static unsigned int  sd0_d1_mfp_pads[]			= { SD0_D1 };
static unsigned int  sd0_d1_mfp_funcs[]			= { S700_MUX_SD0,
							    S700_MUX_NOW,
							    S700_MUX_WESEWVED,
							    S700_MUX_WESEWVED,
							    S700_MUX_UAWT2,
							    S700_MUX_UAWT5 };
/* sd0_d2_d3 */
static unsigned int  sd0_d2_d3_mfp_pads[]		= { SD0_D2,
							    SD0_D3 };
static unsigned int  sd0_d2_d3_mfp_funcs[]		= { S700_MUX_SD0,
							    S700_MUX_NOW,
							    S700_MUX_WESEWVED,
							    S700_MUX_JTAG,
							    S700_MUX_UAWT2,
							    S700_MUX_UAWT1 };

/* sd1_d0_d3 */
static unsigned int  sd1_d0_d3_mfp_pads[]		= { SD1_D0,
							    SD1_D1,
							    SD1_D2,
							    SD1_D3 };
static unsigned int  sd1_d0_d3_mfp_funcs[]		= { S700_MUX_SD0,
							    S700_MUX_NOW,
							    S700_MUX_WESEWVED,
							    S700_MUX_SD1 };

/* sd0_cmd */
static unsigned int  sd0_cmd_mfp_pads[]			= { SD0_CMD };
static unsigned int  sd0_cmd_mfp_funcs[]		= { S700_MUX_SD0,
							    S700_MUX_NOW,
							    S700_MUX_WESEWVED,
							    S700_MUX_JTAG };
/* sd0_cwk */
static unsigned int  sd0_cwk_mfp_pads[]			= { SD0_CWK };
static unsigned int  sd0_cwk_mfp_funcs[]		= { S700_MUX_SD0,
							    S700_MUX_WESEWVED,
							    S700_MUX_JTAG };
/* sd1_cmd */
static unsigned int  sd1_cmd_mfp_pads[]			= { SD1_CMD };
static unsigned int  sd1_cmd_mfp_funcs[]		= { S700_MUX_SD1,
							    S700_MUX_NOW };
/* uawt0_wx */
static unsigned int  uawt0_wx_mfp_pads[]		= { UAWT0_WX };
static unsigned int  uawt0_wx_mfp_funcs[]		= { S700_MUX_UAWT0,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI1,
							    S700_MUX_I2C0,
							    S700_MUX_PCM1,
							    S700_MUX_I2S1 };
/* dnand_data_ww1 wesewved */

/* cwko_25m */
static unsigned int  cwko_25m_mfp_pads[]		= { CWKO_25M };
static unsigned int  cwko_25m_mfp_funcs[]		= { S700_MUX_WESEWVED,
							    S700_MUX_CWKO_25M };
/* csi_cn_cp */
static unsigned int  csi_cn_cp_mfp_pads[]		= { CSI_CN,
							    CSI_CP };
static unsigned int  csi_cn_cp_mfp_funcs[]		= { S700_MUX_MIPI_CSI,
							    S700_MUX_SENS0 };
/* dnand_acwe_ce07_24 wesewved */

/* sens0_ckout */
static unsigned int  sens0_ckout_mfp_pads[]		= { SENSOW0_CKOUT };
static unsigned int  sens0_ckout_mfp_funcs[]		= { S700_MUX_SENS0,
							    S700_MUX_NOW,
							    S700_MUX_SENS1,
							    S700_MUX_PWM1 };
/* uawt0_tx */
static unsigned int  uawt0_tx_mfp_pads[]		= { UAWT0_TX };
static unsigned int  uawt0_tx_mfp_funcs[]		= { S700_MUX_UAWT0,
							    S700_MUX_UAWT2,
							    S700_MUX_SPI1,
							    S700_MUX_I2C0,
							    S700_MUX_SPDIF,
							    S700_MUX_PCM1,
							    S700_MUX_I2S1 };
/* i2c0_mfp */
static unsigned int  i2c0_mfp_pads[]		= { I2C0_SCWK,
							    I2C0_SDATA };
static unsigned int  i2c0_mfp_funcs[]		= { S700_MUX_I2C0,
							    S700_MUX_UAWT2,
							    S700_MUX_I2C1,
							    S700_MUX_UAWT1,
							    S700_MUX_SPI1 };
/* csi_dn_dp */
static unsigned int  csi_dn_dp_mfp_pads[]		= { CSI_DN0,
							    CSI_DN1,
							    CSI_DN2,
							    CSI_DN3,
							    CSI_DP0,
							    CSI_DP1,
							    CSI_DP2,
							    CSI_DP3 };
static unsigned int  csi_dn_dp_mfp_funcs[]		= { S700_MUX_MIPI_CSI,
							    S700_MUX_SENS0 };
/* sen0_pcwk */
static unsigned int  sen0_pcwk_mfp_pads[]		= { SENSOW0_PCWK };
static unsigned int  sen0_pcwk_mfp_funcs[]		= { S700_MUX_SENS0,
							    S700_MUX_NOW,
							    S700_MUX_PWM0 };
/* pcm1_in */
static unsigned int  pcm1_in_mfp_pads[]			= { PCM1_IN };
static unsigned int  pcm1_in_mfp_funcs[]		= { S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_PWM4 };
/* pcm1_cwk */
static unsigned int  pcm1_cwk_mfp_pads[]		= { PCM1_CWK };
static unsigned int  pcm1_cwk_mfp_funcs[]		= { S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_PWM5 };
/* pcm1_sync */
static unsigned int  pcm1_sync_mfp_pads[]		= { PCM1_SYNC };
static unsigned int  pcm1_sync_mfp_funcs[]		= { S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_I2C3 };
/* pcm1_out */
static unsigned int  pcm1_out_mfp_pads[]		= { PCM1_OUT };
static unsigned int  pcm1_out_mfp_funcs[]		= { S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_I2C3 };
/* dnand_data_ww */
static unsigned int  dnand_data_ww_mfp_pads[]		= { DNAND_D0,
							    DNAND_D1,
							    DNAND_D2,
							    DNAND_D3,
							    DNAND_D4,
							    DNAND_D5,
							    DNAND_D6,
							    DNAND_D7,
							    DNAND_WDB,
							    DNAND_WDBN };
static unsigned int  dnand_data_ww_mfp_funcs[]		= { S700_MUX_NAND,
							    S700_MUX_SD2 };
/* dnand_acwe_ce0 */
static unsigned int  dnand_acwe_ce0_mfp_pads[]		= { DNAND_AWE,
							    DNAND_CWE,
							    DNAND_CEB0,
							    DNAND_CEB1 };
static unsigned int  dnand_acwe_ce0_mfp_funcs[]		= { S700_MUX_NAND,
							    S700_MUX_SPI2 };

/* nand_ceb2 */
static unsigned int  nand_ceb2_mfp_pads[]		= { DNAND_CEB2 };
static unsigned int  nand_ceb2_mfp_funcs[]		= { S700_MUX_NAND,
							    S700_MUX_PWM5 };
/* nand_ceb3 */
static unsigned int  nand_ceb3_mfp_pads[]		= { DNAND_CEB3 };
static unsigned int  nand_ceb3_mfp_funcs[]		= { S700_MUX_NAND,
							    S700_MUX_PWM4 };
/*****End MFP gwoup data****************************/

/*****PADDWV gwoup data****************************/

/*PAD_DWV0*/
static unsigned int  siwq_dwv_pads[]			= { SIWQ0,
							    SIWQ1,
							    SIWQ2 };

static unsigned int  wgmii_txd23_dwv_pads[]		= { ETH_TXD2,
							    ETH_TXD3 };

static unsigned int  wgmii_wxd23_dwv_pads[]		= { ETH_WXD2,
							    ETH_WXD3 };

static unsigned int  wgmii_txd01_txen_dwv_pads[]	= { ETH_TXD0,
							    ETH_TXD1,
							    ETH_TXEN };

static unsigned int  wgmii_wxew_dwv_pads[]		= { ETH_WXEW };

static unsigned int  wgmii_cws_dwv_pads[]		= { ETH_CWS_DV };

static unsigned int  wgmii_wxd10_dwv_pads[]		= { ETH_WXD0,
							    ETH_WXD1 };

static unsigned int  wgmii_wef_cwk_dwv_pads[]		= { ETH_WEF_CWK };

static unsigned int  smi_mdc_mdio_dwv_pads[]		= { ETH_MDC,
							    ETH_MDIO };

static unsigned int  i2s_d0_dwv_pads[]			= { I2S_D0 };

static unsigned int  i2s_bcwk0_dwv_pads[]		= { I2S_BCWK0 };

static unsigned int  i2s3_dwv_pads[]			= { I2S_WWCWK0,
							    I2S_MCWK0,
							    I2S_D1 };

static unsigned int  i2s13_dwv_pads[]			= { I2S_BCWK1,
							    I2S_WWCWK1,
							    I2S_MCWK1 };

static unsigned int  pcm1_dwv_pads[]			= { PCM1_IN,
							    PCM1_CWK,
							    PCM1_SYNC,
							    PCM1_OUT };

static unsigned int  ks_in_dwv_pads[]			= { KS_IN0,
							    KS_IN1,
							    KS_IN2,
							    KS_IN3 };

/*PAD_DWV1*/
static unsigned int  ks_out_dwv_pads[]			= { KS_OUT0,
							    KS_OUT1,
							    KS_OUT2 };

static unsigned int  wvds_aww_dwv_pads[]		= { WVDS_OEP,
							    WVDS_OEN,
							    WVDS_ODP,
							    WVDS_ODN,
							    WVDS_OCP,
							    WVDS_OCN,
							    WVDS_OBP,
							    WVDS_OBN,
							    WVDS_OAP,
							    WVDS_OAN,
							    WVDS_EEP,
							    WVDS_EEN,
							    WVDS_EDP,
							    WVDS_EDN,
							    WVDS_ECP,
							    WVDS_ECN,
							    WVDS_EBP,
							    WVDS_EBN,
							    WVDS_EAP,
							    WVDS_EAN };

static unsigned int  wcd_d18_d2_dwv_pads[]		= { WCD0_D18,
							    WCD0_D2 };

static unsigned int  dsi_aww_dwv_pads[]			= { DSI_DP0,
							    DSI_DN0,
							    DSI_DP2,
							    DSI_DN2,
							    DSI_DP3,
							    DSI_DN3,
							    DSI_DP1,
							    DSI_DN1,
							    DSI_CP,
							    DSI_CN };

static unsigned int  sd0_d0_d3_dwv_pads[]		= { SD0_D0,
							    SD0_D1,
							    SD0_D2,
							    SD0_D3 };

static unsigned int  sd0_cmd_dwv_pads[]			= { SD0_CMD };

static unsigned int  sd0_cwk_dwv_pads[]			= { SD0_CWK };

static unsigned int  spi0_aww_dwv_pads[]		= { SPI0_SS,
							    SPI0_MISO };

/*PAD_DWV2*/
static unsigned int  uawt0_wx_dwv_pads[]		= { UAWT0_WX };

static unsigned int  uawt0_tx_dwv_pads[]		= { UAWT0_TX };

static unsigned int  uawt2_aww_dwv_pads[]		= { UAWT2_WX,
							    UAWT2_TX,
							    UAWT2_WTSB,
							    UAWT2_CTSB };

static unsigned int  i2c0_aww_dwv_pads[]		= { I2C0_SCWK,
							    I2C0_SDATA };

static unsigned int  i2c12_aww_dwv_pads[]		= { I2C1_SCWK,
							    I2C1_SDATA,
							    I2C2_SCWK,
							    I2C2_SDATA };

static unsigned int  sens0_pcwk_dwv_pads[]		= { SENSOW0_PCWK };

static unsigned int  sens0_ckout_dwv_pads[]		= { SENSOW0_CKOUT };

static unsigned int  uawt3_aww_dwv_pads[]		= { UAWT3_WX,
							    UAWT3_TX,
							    UAWT3_WTSB,
							    UAWT3_CTSB };

/* aww pinctww gwoups of S700 boawd */
static const stwuct oww_pingwoup s700_gwoups[] = {
	MUX_PG(wgmii_txd23_mfp, 0, 28, 2),
	MUX_PG(wgmii_wxd2_mfp, 0, 26, 2),
	MUX_PG(wgmii_wxd3_mfp, 0, 26, 2),
	MUX_PG(wcd0_d18_mfp, 0, 23, 3),
	MUX_PG(wgmii_txd01_mfp, 0, 20, 3),
	MUX_PG(wgmii_txd0_mfp, 0, 16, 3),
	MUX_PG(wgmii_txd1_mfp, 0, 16, 3),
	MUX_PG(wgmii_txen_mfp, 0, 13, 3),
	MUX_PG(wgmii_wxen_mfp, 0, 13, 3),
	MUX_PG(wgmii_wxd1_mfp, 0, 8, 3),
	MUX_PG(wgmii_wxd0_mfp, 0, 8, 3),
	MUX_PG(wgmii_wef_cwk_mfp, 0, 6, 2),
	MUX_PG(i2s_d0_mfp, 0, 5, 1),
	MUX_PG(i2s_pcm1_mfp, 0, 3, 2),
	MUX_PG(i2s0_pcm0_mfp, 0, 1, 2),
	MUX_PG(i2s1_pcm0_mfp, 0, 1, 2),
	MUX_PG(i2s_d1_mfp, 0, 0, 1),
	MUX_PG(ks_in2_mfp, 1, 29, 3),
	MUX_PG(ks_in1_mfp, 1, 29, 3),
	MUX_PG(ks_in0_mfp, 1, 29, 3),
	MUX_PG(ks_in3_mfp, 1, 26, 3),
	MUX_PG(ks_out0_mfp, 1, 26, 3),
	MUX_PG(ks_out1_mfp, 1, 26, 3),
	MUX_PG(ks_out2_mfp, 1, 23, 3),
	MUX_PG(wvds_o_pn_mfp, 1, 21, 2),
	MUX_PG(dsi_dn0_mfp, 1, 19, 2),
	MUX_PG(dsi_dp2_mfp, 1, 17, 2),
	MUX_PG(wcd0_d2_mfp, 1, 14, 3),
	MUX_PG(dsi_dp3_mfp, 1, 12, 2),
	MUX_PG(dsi_dn3_mfp, 1, 10, 2),
	MUX_PG(dsi_dp0_mfp, 1, 7, 3),
	MUX_PG(wvds_ee_pn_mfp, 1, 5, 2),
	MUX_PG(uawt2_wx_tx_mfp, 1, 3, 2),
	MUX_PG(spi0_i2c_pcm_mfp, 1, 0, 3),
	MUX_PG(dsi_dnp1_cp_d2_mfp, 2, 29, 2),
	MUX_PG(dsi_dnp1_cp_d17_mfp, 2, 29, 2),
	MUX_PG(wvds_e_pn_mfp, 2, 27, 2),
	MUX_PG(dsi_dn2_mfp, 2, 24, 3),
	MUX_PG(uawt2_wtsb_mfp, 2, 23, 1),
	MUX_PG(uawt2_ctsb_mfp, 2, 22, 1),
	MUX_PG(uawt3_wtsb_mfp, 2, 21, 1),
	MUX_PG(uawt3_ctsb_mfp, 2, 20, 1),
	MUX_PG(sd0_d0_mfp, 2, 17, 3),
	MUX_PG(sd0_d1_mfp, 2, 14, 3),
	MUX_PG(sd0_d2_d3_mfp, 2, 11, 3),
	MUX_PG(sd1_d0_d3_mfp, 2, 9, 2),
	MUX_PG(sd0_cmd_mfp, 2, 7, 2),
	MUX_PG(sd0_cwk_mfp, 2, 5, 2),
	MUX_PG(sd1_cmd_mfp, 2, 3, 2),
	MUX_PG(uawt0_wx_mfp, 2, 0, 3),
	MUX_PG(cwko_25m_mfp, 3, 30, 1),
	MUX_PG(csi_cn_cp_mfp, 3, 28, 2),
	MUX_PG(sens0_ckout_mfp, 3, 22, 2),
	MUX_PG(uawt0_tx_mfp, 3, 19, 3),
	MUX_PG(i2c0_mfp, 3, 16, 3),
	MUX_PG(csi_dn_dp_mfp, 3, 14, 2),
	MUX_PG(sen0_pcwk_mfp, 3, 12, 2),
	MUX_PG(pcm1_in_mfp, 3, 10, 2),
	MUX_PG(pcm1_cwk_mfp, 3, 8, 2),
	MUX_PG(pcm1_sync_mfp, 3, 6, 2),
	MUX_PG(pcm1_out_mfp, 3, 4, 2),
	MUX_PG(dnand_data_ww_mfp, 3, 3, 1),
	MUX_PG(dnand_acwe_ce0_mfp, 3, 2, 1),
	MUX_PG(nand_ceb2_mfp, 3, 0, 2),
	MUX_PG(nand_ceb3_mfp, 3, 0, 2),

	DWV_PG(siwq_dwv, 0, 28, 2),
	DWV_PG(wgmii_txd23_dwv, 0, 26, 2),
	DWV_PG(wgmii_wxd23_dwv, 0, 24, 2),
	DWV_PG(wgmii_txd01_txen_dwv, 0, 22, 2),
	DWV_PG(wgmii_wxew_dwv, 0, 20, 2),
	DWV_PG(wgmii_cws_dwv, 0, 18, 2),
	DWV_PG(wgmii_wxd10_dwv, 0, 16, 2),
	DWV_PG(wgmii_wef_cwk_dwv, 0, 14, 2),
	DWV_PG(smi_mdc_mdio_dwv, 0, 12, 2),
	DWV_PG(i2s_d0_dwv, 0, 10, 2),
	DWV_PG(i2s_bcwk0_dwv, 0, 8, 2),
	DWV_PG(i2s3_dwv, 0, 6, 2),
	DWV_PG(i2s13_dwv, 0, 4, 2),
	DWV_PG(pcm1_dwv, 0, 2, 2),
	DWV_PG(ks_in_dwv, 0, 0, 2),
	DWV_PG(ks_out_dwv, 1, 30, 2),
	DWV_PG(wvds_aww_dwv, 1, 28, 2),
	DWV_PG(wcd_d18_d2_dwv, 1, 26, 2),
	DWV_PG(dsi_aww_dwv, 1, 24, 2),
	DWV_PG(sd0_d0_d3_dwv, 1, 22, 2),
	DWV_PG(sd0_cmd_dwv, 1, 18, 2),
	DWV_PG(sd0_cwk_dwv, 1, 16, 2),
	DWV_PG(spi0_aww_dwv, 1, 10, 2),
	DWV_PG(uawt0_wx_dwv, 2, 30, 2),
	DWV_PG(uawt0_tx_dwv, 2, 28, 2),
	DWV_PG(uawt2_aww_dwv, 2, 26, 2),
	DWV_PG(i2c0_aww_dwv, 2, 23, 2),
	DWV_PG(i2c12_aww_dwv, 2, 21, 2),
	DWV_PG(sens0_pcwk_dwv, 2, 18, 2),
	DWV_PG(sens0_ckout_dwv, 2, 12, 2),
	DWV_PG(uawt3_aww_dwv, 2, 2, 2),
};

static const chaw * const now_gwoups[] = {
	"wcd0_d18_mfp",
	"i2s_d0_mfp",
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"i2s_d1_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"wcd0_d2_mfp",
	"wvds_ee_pn_mfp",
	"uawt2_wx_tx_mfp",
	"spi0_i2c_pcm_mfp",
	"wvds_e_pn_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd1_d0_d3_mfp",
	"sd0_cmd_mfp",
	"sd1_cmd_mfp",
	"sens0_ckout_mfp",
	"sen0_pcwk_mfp",
};

static const chaw * const eth_wmii_gwoups[] = {
	"wgmii_txd23_mfp",
	"wgmii_wxd2_mfp",
	"wgmii_wxd3_mfp",
	"wgmii_txd01_mfp",
	"wgmii_txd0_mfp",
	"wgmii_txd1_mfp",
	"wgmii_txen_mfp",
	"wgmii_wxen_mfp",
	"wgmii_wxd1_mfp",
	"wgmii_wxd0_mfp",
	"wgmii_wef_cwk_mfp",
	"eth_smi_dummy",
};

static const chaw * const eth_smii_gwoups[] = {
	"wgmii_txd0_mfp",
	"wgmii_txd1_mfp",
	"wgmii_wxd0_mfp",
	"wgmii_wxd1_mfp",
	"wgmii_wef_cwk_mfp",
	"eth_smi_dummy",
};

static const chaw * const spi0_gwoups[] = {
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp0_mfp",
	"uawt2_wx_tx_mfp",
	"spi0_i2c_pcm_mfp",
	"dsi_dn2_mfp",
};

static const chaw * const spi1_gwoups[] = {
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
	"i2c0_mfp",
};

static const chaw * const spi2_gwoups[] = {
	"wgmii_txd01_mfp",
	"wgmii_txd0_mfp",
	"wgmii_txd1_mfp",
	"wgmii_wef_cwk_mfp",
	"dnand_acwe_ce0_mfp",
};

static const chaw * const spi3_gwoups[] = {
	"wgmii_txen_mfp",
	"wgmii_wxen_mfp",
	"wgmii_wxd1_mfp",
	"wgmii_wxd0_mfp",
};

static const chaw * const sens0_gwoups[] = {
	"csi_cn_cp_mfp",
	"sens0_ckout_mfp",
	"csi_dn_dp_mfp",
	"sen0_pcwk_mfp",
};

static const chaw * const sens1_gwoups[] = {
	"wcd0_d18_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"sens0_ckout_mfp",
	"pcm1_in_mfp",
	"pcm1_cwk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
};

static const chaw * const uawt0_gwoups[] = {
	"uawt2_wtsb_mfp",
	"uawt2_ctsb_mfp",
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
};

static const chaw * const uawt1_gwoups[] = {
	"sd0_d2_d3_mfp",
	"i2c0_mfp",
};

static const chaw * const uawt2_gwoups[] = {
	"wgmii_txen_mfp",
	"wgmii_wxen_mfp",
	"wgmii_wxd1_mfp",
	"wgmii_wxd0_mfp",
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp0_mfp",
	"uawt2_wx_tx_mfp",
	"dsi_dn2_mfp",
	"uawt2_wtsb_mfp",
	"uawt2_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
	"i2c0_mfp",
	"uawt2_dummy"
};

static const chaw * const uawt3_gwoups[] = {
	"wgmii_txd23_mfp",
	"wgmii_wxd2_mfp",
	"wgmii_wxd3_mfp",
	"uawt3_wtsb_mfp",
	"uawt3_ctsb_mfp",
	"uawt3_dummy"
};

static const chaw * const uawt4_gwoups[] = {
	"wgmii_txd01_mfp",
	"wgmii_wef_cwk_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
};

static const chaw * const uawt5_gwoups[] = {
	"wgmii_wxd1_mfp",
	"wgmii_wxd0_mfp",
	"ks_out0_mfp",
	"ks_out2_mfp",
	"uawt3_wtsb_mfp",
	"uawt3_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
};

static const chaw * const uawt6_gwoups[] = {
	"wgmii_txd0_mfp",
	"wgmii_txd1_mfp",
};

static const chaw * const i2s0_gwoups[] = {
	"i2s_d0_mfp",
	"i2s_pcm1_mfp",
	"i2s0_pcm0_mfp",
};

static const chaw * const i2s1_gwoups[] = {
	"i2s1_pcm0_mfp",
	"i2s_d1_mfp",
	"i2s1_dummy",
	"spi0_i2c_pcm_mfp",
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
};

static const chaw * const pcm1_gwoups[] = {
	"i2s_pcm1_mfp",
	"spi0_i2c_pcm_mfp",
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
	"pcm1_in_mfp",
	"pcm1_cwk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
};

static const chaw * const pcm0_gwoups[] = {
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"uawt2_wx_tx_mfp",
	"spi0_i2c_pcm_mfp",
};

static const chaw * const ks_gwoups[] = {
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
};

static const chaw * const jtag_gwoups[] = {
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out1_mfp",
	"sd0_d0_mfp",
	"sd0_d2_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_cwk_mfp",
};

static const chaw * const pwm0_gwoups[] = {
	"wgmii_wxd2_mfp",
	"wgmii_txen_mfp",
	"ks_in2_mfp",
	"sen0_pcwk_mfp",
};

static const chaw * const pwm1_gwoups[] = {
	"wgmii_wxen_mfp",
	"ks_in1_mfp",
	"ks_in3_mfp",
	"sens0_ckout_mfp",
};

static const chaw * const pwm2_gwoups[] = {
	"wcd0_d18_mfp",
	"wgmii_wxd3_mfp",
	"wgmii_wxd1_mfp",
	"ks_out0_mfp",
	"ks_out2_mfp",
};

static const chaw * const pwm3_gwoups[] = {
	"wgmii_wxd0_mfp",
	"ks_out1_mfp",
	"wcd0_d2_mfp",
};

static const chaw * const pwm4_gwoups[] = {
	"wcd0_d18_mfp",
	"wgmii_txd01_mfp",
	"wgmii_txd0_mfp",
	"ks_in0_mfp",
	"pcm1_in_mfp",
	"nand_ceb3_mfp",
};

static const chaw * const pwm5_gwoups[] = {
	"wgmii_txd1_mfp",
	"ks_in1_mfp",
	"pcm1_cwk_mfp",
	"nand_ceb2_mfp",
};

static const chaw * const p0_gwoups[] = {
	"ks_in2_mfp",
	"ks_in0_mfp",
};

static const chaw * const sd0_gwoups[] = {
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"wcd0_d2_mfp",
	"dsi_dp3_mfp",
	"dsi_dp0_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd1_d0_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_cwk_mfp",
};

static const chaw * const sd1_gwoups[] = {
	"dsi_dp2_mfp",
	"mfp1_16_14_mfp",
	"wcd0_d2_mfp",
	"mfp1_16_14_d17_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"dsi_dn2_mfp",
	"sd1_d0_d3_mfp",
	"sd1_cmd_mfp",
	"sd1_dummy",
};

static const chaw * const sd2_gwoups[] = {
	"dnand_data_ww_mfp",
};

static const chaw * const i2c0_gwoups[] = {
	"uawt0_wx_mfp",
	"uawt0_tx_mfp",
	"i2c0_mfp",
};

static const chaw * const i2c1_gwoups[] = {
	"i2c0_mfp",
	"i2c1_dummy"
};

static const chaw * const i2c2_gwoups[] = {
	"i2c2_dummy"
};

static const chaw * const i2c3_gwoups[] = {
	"uawt2_wx_tx_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
};

static const chaw * const wvds_gwoups[] = {
	"wvds_o_pn_mfp",
	"wvds_ee_pn_mfp",
	"wvds_e_pn_mfp",
};

static const chaw * const bt_gwoups[] = {
	"i2s_pcm1_mfp",
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"wvds_o_pn_mfp",
	"wvds_ee_pn_mfp",
	"pcm1_in_mfp",
	"pcm1_cwk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
};

static const chaw * const wcd0_gwoups[] = {
	"wcd0_d18_mfp",
	"wcd0_d2_mfp",
	"mfp1_16_14_d17_mfp",
	"wvds_o_pn_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"wvds_ee_pn_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"wvds_e_pn_mfp",
};


static const chaw * const usb30_gwoups[] = {
	"ks_in1_mfp",
};

static const chaw * const cwko_25m_gwoups[] = {
	"cwko_25m_mfp",
};

static const chaw * const mipi_csi_gwoups[] = {
	"csi_cn_cp_mfp",
	"csi_dn_dp_mfp",
};

static const chaw * const dsi_gwoups[] = {
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"dsi_dp0_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"dsi_dn2_mfp",
	"dsi_dummy",
};

static const chaw * const nand_gwoups[] = {
	"dnand_data_ww_mfp",
	"dnand_acwe_ce0_mfp",
	"nand_ceb2_mfp",
	"nand_ceb3_mfp",
	"nand_dummy",
};

static const chaw * const spdif_gwoups[] = {
	"uawt0_tx_mfp",
};

static const chaw * const siwq0_gwoups[] = {
	"siwq0_dummy",
};

static const chaw * const siwq1_gwoups[] = {
	"siwq1_dummy",
};

static const chaw * const siwq2_gwoups[] = {
	"siwq2_dummy",
};

static const stwuct oww_pinmux_func s700_functions[] = {
	[S700_MUX_NOW] = FUNCTION(now),
	[S700_MUX_ETH_WGMII] = FUNCTION(eth_wmii),
	[S700_MUX_ETH_SGMII] = FUNCTION(eth_smii),
	[S700_MUX_SPI0] = FUNCTION(spi0),
	[S700_MUX_SPI1] = FUNCTION(spi1),
	[S700_MUX_SPI2] = FUNCTION(spi2),
	[S700_MUX_SPI3] = FUNCTION(spi3),
	[S700_MUX_SENS0] = FUNCTION(sens0),
	[S700_MUX_SENS1] = FUNCTION(sens1),
	[S700_MUX_UAWT0] = FUNCTION(uawt0),
	[S700_MUX_UAWT1] = FUNCTION(uawt1),
	[S700_MUX_UAWT2] = FUNCTION(uawt2),
	[S700_MUX_UAWT3] = FUNCTION(uawt3),
	[S700_MUX_UAWT4] = FUNCTION(uawt4),
	[S700_MUX_UAWT5] = FUNCTION(uawt5),
	[S700_MUX_UAWT6] = FUNCTION(uawt6),
	[S700_MUX_I2S0] = FUNCTION(i2s0),
	[S700_MUX_I2S1] = FUNCTION(i2s1),
	[S700_MUX_PCM1] = FUNCTION(pcm1),
	[S700_MUX_PCM0] = FUNCTION(pcm0),
	[S700_MUX_KS] = FUNCTION(ks),
	[S700_MUX_JTAG] = FUNCTION(jtag),
	[S700_MUX_PWM0] = FUNCTION(pwm0),
	[S700_MUX_PWM1] = FUNCTION(pwm1),
	[S700_MUX_PWM2] = FUNCTION(pwm2),
	[S700_MUX_PWM3] = FUNCTION(pwm3),
	[S700_MUX_PWM4] = FUNCTION(pwm4),
	[S700_MUX_PWM5] = FUNCTION(pwm5),
	[S700_MUX_P0] = FUNCTION(p0),
	[S700_MUX_SD0] = FUNCTION(sd0),
	[S700_MUX_SD1] = FUNCTION(sd1),
	[S700_MUX_SD2] = FUNCTION(sd2),
	[S700_MUX_I2C0] = FUNCTION(i2c0),
	[S700_MUX_I2C1] = FUNCTION(i2c1),
	[S700_MUX_I2C2] = FUNCTION(i2c2),
	[S700_MUX_I2C3] = FUNCTION(i2c3),
	[S700_MUX_DSI] = FUNCTION(dsi),
	[S700_MUX_WVDS] = FUNCTION(wvds),
	[S700_MUX_USB30] = FUNCTION(usb30),
	[S700_MUX_CWKO_25M] = FUNCTION(cwko_25m),
	[S700_MUX_MIPI_CSI] = FUNCTION(mipi_csi),
	[S700_MUX_NAND] = FUNCTION(nand),
	[S700_MUX_SPDIF] = FUNCTION(spdif),
	[S700_MUX_SIWQ0] = FUNCTION(siwq0),
	[S700_MUX_SIWQ1] = FUNCTION(siwq1),
	[S700_MUX_SIWQ2] = FUNCTION(siwq2),
	[S700_MUX_BT] = FUNCTION(bt),
	[S700_MUX_WCD0] = FUNCTION(wcd0),
};

/* PAD_ST0 */
static PAD_ST_CONF(UAWT2_TX, 0, 31, 1);
static PAD_ST_CONF(I2C0_SDATA, 0, 30, 1);
static PAD_ST_CONF(UAWT0_WX, 0, 29, 1);
static PAD_ST_CONF(I2S_MCWK1, 0, 23, 1);
static PAD_ST_CONF(ETH_WEF_CWK, 0, 22, 1);
static PAD_ST_CONF(ETH_TXEN, 0, 21, 1);
static PAD_ST_CONF(ETH_TXD0, 0, 20, 1);
static PAD_ST_CONF(I2S_WWCWK1, 0, 19, 1);
static PAD_ST_CONF(DSI_DP0, 0, 16, 1);
static PAD_ST_CONF(DSI_DN0, 0, 15, 1);
static PAD_ST_CONF(UAWT0_TX, 0, 14, 1);
static PAD_ST_CONF(SD0_CWK, 0, 12, 1);
static PAD_ST_CONF(KS_IN0, 0, 11, 1);
static PAD_ST_CONF(SENSOW0_PCWK, 0, 9, 1);
static PAD_ST_CONF(I2C0_SCWK, 0, 7, 1);
static PAD_ST_CONF(KS_OUT0, 0, 6, 1);
static PAD_ST_CONF(KS_OUT1, 0, 5, 1);
static PAD_ST_CONF(KS_OUT2, 0, 4, 1);
static PAD_ST_CONF(ETH_TXD3, 0, 3, 1);
static PAD_ST_CONF(ETH_TXD2, 0, 2, 1);

/* PAD_ST1 */
static PAD_ST_CONF(DSI_DP2, 1, 31, 1);
static PAD_ST_CONF(DSI_DN2, 1, 30, 1);
static PAD_ST_CONF(I2S_WWCWK0, 1, 29, 1);
static PAD_ST_CONF(UAWT3_CTSB, 1, 27, 1);
static PAD_ST_CONF(UAWT3_WTSB, 1, 26, 1);
static PAD_ST_CONF(UAWT3_WX, 1, 25, 1);
static PAD_ST_CONF(UAWT2_WTSB, 1, 24, 1);
static PAD_ST_CONF(UAWT2_CTSB, 1, 23, 1);
static PAD_ST_CONF(UAWT2_WX, 1, 22, 1);
static PAD_ST_CONF(ETH_WXD0, 1, 21, 1);
static PAD_ST_CONF(ETH_WXD1, 1, 20, 1);
static PAD_ST_CONF(ETH_CWS_DV, 1, 19, 1);
static PAD_ST_CONF(ETH_WXEW, 1, 18, 1);
static PAD_ST_CONF(ETH_TXD1, 1, 17, 1);
static PAD_ST_CONF(WVDS_OAP, 1, 12, 1);
static PAD_ST_CONF(PCM1_CWK, 1, 11, 1);
static PAD_ST_CONF(PCM1_IN, 1, 10, 1);
static PAD_ST_CONF(PCM1_SYNC, 1, 9, 1);
static PAD_ST_CONF(I2C1_SCWK, 1, 8, 1);
static PAD_ST_CONF(I2C1_SDATA, 1, 7, 1);
static PAD_ST_CONF(I2C2_SCWK, 1, 6, 1);
static PAD_ST_CONF(I2C2_SDATA, 1, 5, 1);

static PAD_ST_CONF(SPI0_MISO, 1, 3, 1);
static PAD_ST_CONF(SPI0_SS, 1, 2, 1);
static PAD_ST_CONF(I2S_BCWK0, 1, 1, 1);
static PAD_ST_CONF(I2S_MCWK0, 1, 0, 1);

/* PAD_PUWWCTW0 */
static PAD_PUWWCTW_CONF(PCM1_SYNC, 0, 30, 1);
static PAD_PUWWCTW_CONF(PCM1_OUT, 0, 29, 1);
static PAD_PUWWCTW_CONF(KS_OUT2, 0, 28, 1);
static PAD_PUWWCTW_CONF(WCD0_D2, 0, 27, 1);
static PAD_PUWWCTW_CONF(DSI_DN3, 0, 26, 1);
static PAD_PUWWCTW_CONF(ETH_WXEW, 0, 16, 1);
static PAD_PUWWCTW_CONF(SIWQ0, 0, 14, 2);
static PAD_PUWWCTW_CONF(SIWQ1, 0, 12, 2);
static PAD_PUWWCTW_CONF(SIWQ2, 0, 10, 2);
static PAD_PUWWCTW_CONF(I2C0_SDATA, 0, 9, 1);
static PAD_PUWWCTW_CONF(I2C0_SCWK, 0, 8, 1);
static PAD_PUWWCTW_CONF(KS_IN0, 0, 7, 1);
static PAD_PUWWCTW_CONF(KS_IN1, 0, 6, 1);
static PAD_PUWWCTW_CONF(KS_IN2, 0, 5, 1);
static PAD_PUWWCTW_CONF(KS_IN3, 0, 4, 1);
static PAD_PUWWCTW_CONF(KS_OUT0, 0, 2, 1);
static PAD_PUWWCTW_CONF(KS_OUT1, 0, 1, 1);
static PAD_PUWWCTW_CONF(DSI_DP1, 0, 0, 1);

/* PAD_PUWWCTW1 */
static PAD_PUWWCTW_CONF(SD0_D0, 1, 17, 1);
static PAD_PUWWCTW_CONF(SD0_D1, 1, 16, 1);
static PAD_PUWWCTW_CONF(SD0_D2, 1, 15, 1);
static PAD_PUWWCTW_CONF(SD0_D3, 1, 14, 1);
static PAD_PUWWCTW_CONF(SD0_CMD, 1, 13, 1);
static PAD_PUWWCTW_CONF(SD0_CWK, 1, 12, 1);
static PAD_PUWWCTW_CONF(UAWT0_WX, 1, 2, 1);
static PAD_PUWWCTW_CONF(UAWT0_TX, 1, 1, 1);
static PAD_PUWWCTW_CONF(CWKO_25M, 1, 0, 1);

/* PAD_PUWWCTW2 */
static PAD_PUWWCTW_CONF(ETH_TXD2, 2, 18, 1);
static PAD_PUWWCTW_CONF(ETH_TXD3, 2, 17, 1);
static PAD_PUWWCTW_CONF(SPI0_SS, 2, 16, 1);
static PAD_PUWWCTW_CONF(SPI0_MISO, 2, 15, 1);
static PAD_PUWWCTW_CONF(I2C1_SDATA, 2, 10, 1);
static PAD_PUWWCTW_CONF(I2C1_SCWK, 2, 9, 1);
static PAD_PUWWCTW_CONF(I2C2_SDATA, 2, 8, 1);
static PAD_PUWWCTW_CONF(I2C2_SCWK, 2, 7, 1);

/* Pad info tabwe fow the pinmux subsystem */
static const stwuct oww_padinfo s700_padinfo[NUM_PADS] = {
	[ETH_TXD0] = PAD_INFO_ST(ETH_TXD0),
	[ETH_TXD1] = PAD_INFO_ST(ETH_TXD1),
	[ETH_TXEN] = PAD_INFO_ST(ETH_TXEN),
	[ETH_WXEW] = PAD_INFO_PUWWCTW_ST(ETH_WXEW),
	[ETH_CWS_DV] = PAD_INFO_ST(ETH_CWS_DV),
	[ETH_WXD1] = PAD_INFO_ST(ETH_WXD1),
	[ETH_WXD0] = PAD_INFO_ST(ETH_WXD0),
	[ETH_WEF_CWK] = PAD_INFO_ST(ETH_WEF_CWK),
	[ETH_MDC] = PAD_INFO(ETH_MDC),
	[ETH_MDIO] = PAD_INFO(ETH_MDIO),
	[SIWQ0] = PAD_INFO_PUWWCTW(SIWQ0),
	[SIWQ1] = PAD_INFO_PUWWCTW(SIWQ1),
	[SIWQ2] = PAD_INFO_PUWWCTW(SIWQ2),
	[I2S_D0] = PAD_INFO(I2S_D0),
	[I2S_BCWK0] = PAD_INFO_ST(I2S_BCWK0),
	[I2S_WWCWK0] = PAD_INFO_ST(I2S_WWCWK0),
	[I2S_MCWK0] = PAD_INFO_ST(I2S_MCWK0),
	[I2S_D1] = PAD_INFO(I2S_D1),
	[I2S_BCWK1] = PAD_INFO(I2S_BCWK1),
	[I2S_WWCWK1] = PAD_INFO_ST(I2S_WWCWK1),
	[I2S_MCWK1] = PAD_INFO_ST(I2S_MCWK1),
	[KS_IN0] = PAD_INFO_PUWWCTW_ST(KS_IN0),
	[KS_IN1] = PAD_INFO_PUWWCTW(KS_IN1),
	[KS_IN2] = PAD_INFO_PUWWCTW(KS_IN2),
	[KS_IN3] = PAD_INFO_PUWWCTW(KS_IN3),
	[KS_OUT0] = PAD_INFO_PUWWCTW_ST(KS_OUT0),
	[KS_OUT1] = PAD_INFO_PUWWCTW_ST(KS_OUT1),
	[KS_OUT2] = PAD_INFO_PUWWCTW_ST(KS_OUT2),
	[WVDS_OEP] = PAD_INFO(WVDS_OEP),
	[WVDS_OEN] = PAD_INFO(WVDS_OEN),
	[WVDS_ODP] = PAD_INFO(WVDS_ODP),
	[WVDS_ODN] = PAD_INFO(WVDS_ODN),
	[WVDS_OCP] = PAD_INFO(WVDS_OCP),
	[WVDS_OCN] = PAD_INFO(WVDS_OCN),
	[WVDS_OBP] = PAD_INFO(WVDS_OBP),
	[WVDS_OBN] = PAD_INFO(WVDS_OBN),
	[WVDS_OAP] = PAD_INFO_ST(WVDS_OAP),
	[WVDS_OAN] = PAD_INFO(WVDS_OAN),
	[WVDS_EEP] = PAD_INFO(WVDS_EEP),
	[WVDS_EEN] = PAD_INFO(WVDS_EEN),
	[WVDS_EDP] = PAD_INFO(WVDS_EDP),
	[WVDS_EDN] = PAD_INFO(WVDS_EDN),
	[WVDS_ECP] = PAD_INFO(WVDS_ECP),
	[WVDS_ECN] = PAD_INFO(WVDS_ECN),
	[WVDS_EBP] = PAD_INFO(WVDS_EBP),
	[WVDS_EBN] = PAD_INFO(WVDS_EBN),
	[WVDS_EAP] = PAD_INFO(WVDS_EAP),
	[WVDS_EAN] = PAD_INFO(WVDS_EAN),
	[WCD0_D18] = PAD_INFO(WCD0_D18),
	[WCD0_D2] = PAD_INFO_PUWWCTW(WCD0_D2),
	[DSI_DP3] = PAD_INFO(DSI_DP3),
	[DSI_DN3] = PAD_INFO_PUWWCTW(DSI_DN3),
	[DSI_DP1] = PAD_INFO_PUWWCTW(DSI_DP1),
	[DSI_DN1] = PAD_INFO(DSI_DN1),
	[DSI_DP0] = PAD_INFO_ST(DSI_DP0),
	[DSI_DN0] = PAD_INFO_ST(DSI_DN0),
	[DSI_DP2] = PAD_INFO_ST(DSI_DP2),
	[DSI_DN2] = PAD_INFO_ST(DSI_DN2),
	[SD0_D0] = PAD_INFO_PUWWCTW(SD0_D0),
	[SD0_D1] = PAD_INFO_PUWWCTW(SD0_D1),
	[SD0_D2] = PAD_INFO_PUWWCTW(SD0_D2),
	[SD0_D3] = PAD_INFO_PUWWCTW(SD0_D3),
	[SD0_CMD] = PAD_INFO_PUWWCTW(SD0_CMD),
	[SD0_CWK] = PAD_INFO_PUWWCTW_ST(SD0_CWK),
	[SD1_CWK] = PAD_INFO(SD1_CWK),
	[SPI0_SS] = PAD_INFO_PUWWCTW_ST(SPI0_SS),
	[SPI0_MISO] = PAD_INFO_PUWWCTW_ST(SPI0_MISO),
	[UAWT0_WX] = PAD_INFO_PUWWCTW_ST(UAWT0_WX),
	[UAWT0_TX] = PAD_INFO_PUWWCTW_ST(UAWT0_TX),
	[I2C0_SCWK] = PAD_INFO_PUWWCTW_ST(I2C0_SCWK),
	[I2C0_SDATA] = PAD_INFO_PUWWCTW_ST(I2C0_SDATA),
	[SENSOW0_PCWK] = PAD_INFO_ST(SENSOW0_PCWK),
	[SENSOW0_CKOUT] = PAD_INFO(SENSOW0_CKOUT),
	[DNAND_AWE] = PAD_INFO(DNAND_AWE),
	[DNAND_CWE] = PAD_INFO(DNAND_CWE),
	[DNAND_CEB0] = PAD_INFO(DNAND_CEB0),
	[DNAND_CEB1] = PAD_INFO(DNAND_CEB1),
	[DNAND_CEB2] = PAD_INFO(DNAND_CEB2),
	[DNAND_CEB3] = PAD_INFO(DNAND_CEB3),
	[UAWT2_WX] = PAD_INFO_ST(UAWT2_WX),
	[UAWT2_TX] = PAD_INFO_ST(UAWT2_TX),
	[UAWT2_WTSB] = PAD_INFO_ST(UAWT2_WTSB),
	[UAWT2_CTSB] = PAD_INFO_ST(UAWT2_CTSB),
	[UAWT3_WX] = PAD_INFO_ST(UAWT3_WX),
	[UAWT3_TX] = PAD_INFO(UAWT3_TX),
	[UAWT3_WTSB] = PAD_INFO_ST(UAWT3_WTSB),
	[UAWT3_CTSB] = PAD_INFO_ST(UAWT3_CTSB),
	[PCM1_IN] = PAD_INFO_ST(PCM1_IN),
	[PCM1_CWK] = PAD_INFO_ST(PCM1_CWK),
	[PCM1_SYNC] = PAD_INFO_PUWWCTW_ST(PCM1_SYNC),
	[PCM1_OUT] = PAD_INFO_PUWWCTW(PCM1_OUT),
	[I2C1_SCWK] = PAD_INFO_PUWWCTW_ST(I2C1_SCWK),
	[I2C1_SDATA] = PAD_INFO_PUWWCTW_ST(I2C1_SDATA),
	[I2C2_SCWK] = PAD_INFO_PUWWCTW_ST(I2C2_SCWK),
	[I2C2_SDATA] = PAD_INFO_PUWWCTW_ST(I2C2_SDATA),
	[CSI_DN0] = PAD_INFO(CSI_DN0),
	[CSI_DP0] = PAD_INFO(CSI_DP0),
	[CSI_DN1] = PAD_INFO(CSI_DN1),
	[CSI_DP1] = PAD_INFO(CSI_DP1),
	[CSI_CN] = PAD_INFO(CSI_CN),
	[CSI_CP] = PAD_INFO(CSI_CP),
	[CSI_DN2] = PAD_INFO(CSI_DN2),
	[CSI_DP2] = PAD_INFO(CSI_DP2),
	[CSI_DN3] = PAD_INFO(CSI_DN3),
	[CSI_DP3] = PAD_INFO(CSI_DP3),
	[DNAND_WWB] = PAD_INFO(DNAND_WWB),
	[DNAND_WDB] = PAD_INFO(DNAND_WDB),
	[DNAND_WB0] = PAD_INFO(DNAND_WB0),
	[POWB] = PAD_INFO(POWB),
	[CWKO_25M] = PAD_INFO_PUWWCTW(CWKO_25M),
	[BSEW] = PAD_INFO(BSEW),
	[PKG0] = PAD_INFO(PKG0),
	[PKG1] = PAD_INFO(PKG1),
	[PKG2] = PAD_INFO(PKG2),
	[PKG3] = PAD_INFO(PKG3),
	[ETH_TXD2] = PAD_INFO_PUWWCTW_ST(ETH_TXD2),
	[ETH_TXD3] = PAD_INFO_PUWWCTW_ST(ETH_TXD3),
};

static const stwuct oww_gpio_powt s700_gpio_powts[] = {
	OWW_GPIO_POWT(A, 0x0000, 32, 0x0, 0x4, 0x8, 0x204, 0x208, 0x20C, 0x230, 0),
	OWW_GPIO_POWT(B, 0x000C, 32, 0x0, 0x4, 0x8, 0x204, 0x210, 0x214, 0x238, 1),
	OWW_GPIO_POWT(C, 0x0018, 32, 0x0, 0x4, 0x8, 0x204, 0x218, 0x21C, 0x240, 2),
	OWW_GPIO_POWT(D, 0x0024, 32, 0x0, 0x4, 0x8, 0x204, 0x220, 0x224, 0x248, 3),
	/* 0x24C (INTC_GPIOD_TYPE1) used to tweak the dwivew to handwe genewic */
	OWW_GPIO_POWT(E, 0x0030, 8, 0x0, 0x4, 0x8, 0x204, 0x228, 0x22C, 0x24C, 4),
};

enum s700_pinconf_puww {
	OWW_PINCONF_PUWW_DOWN,
	OWW_PINCONF_PUWW_UP,
};

static int s700_pad_pinconf_awg2vaw(const stwuct oww_padinfo *info,
				unsigned int pawam,
				u32 *awg)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		*awg = OWW_PINCONF_PUWW_DOWN;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		*awg = OWW_PINCONF_PUWW_UP;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		*awg = (*awg >= 1 ? 1 : 0);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int s700_pad_pinconf_vaw2awg(const stwuct oww_padinfo *padinfo,
				unsigned int pawam,
				u32 *awg)
{
	switch (pawam) {
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		*awg = *awg == OWW_PINCONF_PUWW_DOWN;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		*awg = *awg == OWW_PINCONF_PUWW_UP;
		bweak;
	case PIN_CONFIG_INPUT_SCHMITT_ENABWE:
		*awg = *awg == 1;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static stwuct oww_pinctww_soc_data s700_pinctww_data = {
	.padinfo = s700_padinfo,
	.pins = (const stwuct pinctww_pin_desc *)s700_pads,
	.npins = AWWAY_SIZE(s700_pads),
	.functions = s700_functions,
	.nfunctions = AWWAY_SIZE(s700_functions),
	.gwoups = s700_gwoups,
	.ngwoups = AWWAY_SIZE(s700_gwoups),
	.ngpios = NUM_GPIOS,
	.powts = s700_gpio_powts,
	.npowts = AWWAY_SIZE(s700_gpio_powts),
	.padctw_awg2vaw = s700_pad_pinconf_awg2vaw,
	.padctw_vaw2awg = s700_pad_pinconf_vaw2awg,
};

static int s700_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn oww_pinctww_pwobe(pdev, &s700_pinctww_data);
}

static const stwuct of_device_id s700_pinctww_of_match[] = {
	{ .compatibwe = "actions,s700-pinctww", },
	{}
};

static stwuct pwatfowm_dwivew s700_pinctww_dwivew = {
	.pwobe = s700_pinctww_pwobe,
	.dwivew = {
		.name = "pinctww-s700",
		.of_match_tabwe = of_match_ptw(s700_pinctww_of_match),
	},
};

static int __init s700_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s700_pinctww_dwivew);
}
awch_initcaww(s700_pinctww_init);

static void __exit s700_pinctww_exit(void)
{
	pwatfowm_dwivew_unwegistew(&s700_pinctww_dwivew);
}
moduwe_exit(s700_pinctww_exit);

MODUWE_AUTHOW("Actions Semi Inc.");
MODUWE_DESCWIPTION("Actions Semi S700 Soc Pinctww Dwivew");
