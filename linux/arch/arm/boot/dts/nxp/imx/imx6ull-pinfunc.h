/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 */

#ifndef __DTS_IMX6UWW_PINFUNC_H
#define __DTS_IMX6UWW_PINFUNC_H

#incwude "imx6uw-pinfunc.h"
/*
 * The pin function ID is a tupwe of
 * <mux_weg conf_weg input_weg mux_mode input_vaw>
 */
/* signaws common fow i.MX6UW and i.MX6UWW */
#undef MX6UW_PAD_UAWT5_TX_DATA__UAWT5_DTE_WX
#define MX6UW_PAD_UAWT5_TX_DATA__UAWT5_DTE_WX                    0x00BC 0x0348 0x0644 0x0 0x6
#undef MX6UW_PAD_UAWT5_WX_DATA__UAWT5_DCE_WX
#define MX6UW_PAD_UAWT5_WX_DATA__UAWT5_DCE_WX                    0x00C0 0x034C 0x0644 0x0 0x7
#undef MX6UW_PAD_ENET1_WX_EN__UAWT5_DCE_WTS
#define MX6UW_PAD_ENET1_WX_EN__UAWT5_DCE_WTS                     0x00CC 0x0358 0x0640 0x1 0x5
#undef MX6UW_PAD_ENET1_TX_DATA0__UAWT5_DTE_WTS
#define MX6UW_PAD_ENET1_TX_DATA0__UAWT5_DTE_WTS                  0x00D0 0x035C 0x0640 0x1 0x6
#undef MX6UW_PAD_CSI_DATA02__UAWT5_DCE_WTS
#define MX6UW_PAD_CSI_DATA02__UAWT5_DCE_WTS                      0x01EC 0x0478 0x0640 0x8 0x7

/* signaws fow i.MX6UWW onwy */
#define MX6UWW_PAD_UAWT1_TX_DATA__UAWT5_DCE_TX                    0x0084 0x0310 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT1_TX_DATA__UAWT5_DTE_WX                    0x0084 0x0310 0x0644 0x9 0x4
#define MX6UWW_PAD_UAWT1_WX_DATA__UAWT5_DCE_WX                    0x0088 0x0314 0x0644 0x9 0x5
#define MX6UWW_PAD_UAWT1_WX_DATA__UAWT5_DTE_TX                    0x0088 0x0314 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT1_CTS_B__UAWT5_DCE_CTS                     0x008C 0x0318 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT1_CTS_B__UAWT5_DTE_WTS                     0x008C 0x0318 0x0640 0x9 0x3
#define MX6UWW_PAD_UAWT1_WTS_B__UAWT5_DCE_WTS                     0x0090 0x031C 0x0640 0x9 0x4
#define MX6UWW_PAD_UAWT1_WTS_B__UAWT5_DTE_CTS                     0x0090 0x031C 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT4_WX_DATA__EPDC_PWWCTWW01                  0x00B8 0x0344 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT5_TX_DATA__EPDC_PWWCTWW02                  0x00BC 0x0348 0x0000 0x9 0x0
#define MX6UWW_PAD_UAWT5_WX_DATA__EPDC_PWWCTWW03                  0x00C0 0x034C 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_WX_DATA0__EPDC_SDCE04                    0x00C4 0x0350 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_WX_DATA1__EPDC_SDCE05                    0x00C8 0x0354 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_WX_EN__EPDC_SDCE06                       0x00CC 0x0358 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_TX_DATA0__EPDC_SDCE07                    0x00D0 0x035C 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_TX_DATA1__EPDC_SDCE08                    0x00D4 0x0360 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_TX_EN__EPDC_SDCE09                       0x00D8 0x0364 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_TX_CWK__EPDC_SDOED                       0x00DC 0x0368 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET1_WX_EW__EPDC_SDOEZ                        0x00E0 0x036C 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_WX_DATA0__EPDC_SDDO08                    0x00E4 0x0370 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_WX_DATA1__EPDC_SDDO09                    0x00E8 0x0374 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_WX_EN__EPDC_SDDO10                       0x00EC 0x0378 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_TX_DATA0__EPDC_SDDO11                    0x00F0 0x037C 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_TX_DATA1__EPDC_SDDO12                    0x00F4 0x0380 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_TX_EN__EPDC_SDDO13                       0x00F8 0x0384 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_TX_CWK__EPDC_SDDO14                      0x00FC 0x0388 0x0000 0x9 0x0
#define MX6UWW_PAD_ENET2_WX_EW__EPDC_SDDO15                       0x0100 0x038C 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_CWK__EPDC_SDCWK                            0x0104 0x0390 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_ENABWE__EPDC_SDWE                          0x0108 0x0394 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_HSYNC__EPDC_SDOE                           0x010C 0x0398 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_VSYNC__EPDC_SDCE0                          0x0110 0x039C 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_WESET__EPDC_GDOE                           0x0114 0x03A0 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA00__EPDC_SDDO00                        0x0118 0x03A4 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA01__EPDC_SDDO01                        0x011C 0x03A8 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA02__EPDC_SDDO02                        0x0120 0x03AC 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA03__EPDC_SDDO03                        0x0124 0x03B0 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA04__EPDC_SDDO04                        0x0128 0x03B4 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA05__EPDC_SDDO05                        0x012C 0x03B8 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA06__EPDC_SDDO06                        0x0130 0x03BC 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA07__EPDC_SDDO07                        0x0134 0x03C0 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA14__EPDC_SDSHW                         0x0150 0x03DC 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA15__EPDC_GDWW                          0x0154 0x03E0 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA16__EPDC_GDCWK                         0x0158 0x03E4 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA17__EPDC_GDSP                          0x015C 0x03E8 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA21__EPDC_SDCE1                         0x016C 0x03F8 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA22__EPDC_SDCE02                        0x0170 0x03FC 0x0000 0x9 0x0
#define MX6UWW_PAD_WCD_DATA23__EPDC_SDCE03                        0x0174 0x0400 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_MCWK__ESAI_TX3_WX2                         0x01D4 0x0460 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_PIXCWK__ESAI_TX2_WX3                       0x01D8 0x0464 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_VSYNC__ESAI_TX4_WX1                        0x01DC 0x0468 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_HSYNC__ESAI_TX1                            0x01E0 0x046C 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA00__ESAI_TX_HF_CWK                     0x01E4 0x0470 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA01__ESAI_WX_HF_CWK                     0x01E8 0x0474 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA02__ESAI_WX_FS                         0x01EC 0x0478 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA03__ESAI_WX_CWK                        0x01F0 0x047C 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA04__ESAI_TX_FS                         0x01F4 0x0480 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA05__ESAI_TX_CWK                        0x01F8 0x0484 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA06__ESAI_TX5_WX0                       0x01FC 0x0488 0x0000 0x9 0x0
#define MX6UWW_PAD_CSI_DATA07__ESAI_TX0                           0x0200 0x048C 0x0000 0x9 0x0

#endif /* __DTS_IMX6UWW_PINFUNC_H */
