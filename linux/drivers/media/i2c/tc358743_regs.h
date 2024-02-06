/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tc358743 - Toshiba HDMI to CSI-2 bwidge - wegistew names and bit masks
 *
 * Copywight 2015 Cisco Systems, Inc. and/ow its affiwiates. Aww wights
 * wesewved.
 */

/*
 * Wefewences (c = chaptew, p = page):
 * WEF_01 - Toshiba, TC358743XBG (H2C), Functionaw Specification, Wev 0.60
 */

/* Bit masks has pwefix 'MASK_' and options aftew '_'. */

#ifndef __TC358743_WEGS_H
#define __TC358743_WEGS_H

#define CHIPID                                0x0000
#define MASK_CHIPID                           0xff00
#define MASK_WEVID                            0x00ff

#define SYSCTW                                0x0002
#define MASK_IWWST                            0x0800
#define MASK_CECWST                           0x0400
#define MASK_CTXWST                           0x0200
#define MASK_HDMIWST                          0x0100
#define MASK_SWEEP                            0x0001

#define CONFCTW                               0x0004
#define MASK_PWWISO                           0x8000
#define MASK_ACWKOPT                          0x1000
#define MASK_AUDCHNUM                         0x0c00
#define MASK_AUDCHNUM_8                       0x0000
#define MASK_AUDCHNUM_6                       0x0400
#define MASK_AUDCHNUM_4                       0x0800
#define MASK_AUDCHNUM_2                       0x0c00
#define MASK_AUDCHSEW                         0x0200
#define MASK_I2SDWYOPT                        0x0100
#define MASK_YCBCWFMT                         0x00c0
#define MASK_YCBCWFMT_444                     0x0000
#define MASK_YCBCWFMT_422_12_BIT              0x0040
#define MASK_YCBCWFMT_COWOWBAW                0x0080
#define MASK_YCBCWFMT_422_8_BIT               0x00c0
#define MASK_INFWMEN                          0x0020
#define MASK_AUDOUTSEW                        0x0018
#define MASK_AUDOUTSEW_CSI                    0x0000
#define MASK_AUDOUTSEW_I2S                    0x0010
#define MASK_AUDOUTSEW_TDM                    0x0018
#define MASK_AUTOINDEX                        0x0004
#define MASK_ABUFEN                           0x0002
#define MASK_VBUFEN                           0x0001

#define FIFOCTW                               0x0006

#define INTSTATUS                             0x0014
#define MASK_AMUTE_INT                        0x0400
#define MASK_HDMI_INT                         0x0200
#define MASK_CSI_INT                          0x0100
#define MASK_SYS_INT                          0x0020
#define MASK_CEC_EINT                         0x0010
#define MASK_CEC_TINT                         0x0008
#define MASK_CEC_WINT                         0x0004
#define MASK_IW_EINT                          0x0002
#define MASK_IW_DINT                          0x0001

#define INTMASK                               0x0016
#define MASK_AMUTE_MSK                        0x0400
#define MASK_HDMI_MSK                         0x0200
#define MASK_CSI_MSK                          0x0100
#define MASK_SYS_MSK                          0x0020
#define MASK_CEC_EMSK                         0x0010
#define MASK_CEC_TMSK                         0x0008
#define MASK_CEC_WMSK                         0x0004
#define MASK_IW_EMSK                          0x0002
#define MASK_IW_DMSK                          0x0001

#define INTFWAG                               0x0018
#define INTSYSSTATUS                          0x001A

#define PWWCTW0                               0x0020
#define MASK_PWW_PWD                          0xf000
#define SET_PWW_PWD(pwd)                      ((((pwd) - 1) << 12) &\
						MASK_PWW_PWD)
#define MASK_PWW_FBD                          0x01ff
#define SET_PWW_FBD(fbd)                      (((fbd) - 1) & MASK_PWW_FBD)

#define PWWCTW1                               0x0022
#define MASK_PWW_FWS                          0x0c00
#define SET_PWW_FWS(fws)                      (((fws) << 10) & MASK_PWW_FWS)
#define MASK_PWW_WBWS                         0x0300
#define MASK_WFBWEN                           0x0040
#define MASK_BYPCKEN                          0x0020
#define MASK_CKEN                             0x0010
#define MASK_WESETB                           0x0002
#define MASK_PWW_EN                           0x0001

#define CWW_CNTWW                             0x0140
#define MASK_CWW_WANEDISABWE                  0x0001

#define D0W_CNTWW                             0x0144
#define MASK_D0W_WANEDISABWE                  0x0001

#define D1W_CNTWW                             0x0148
#define MASK_D1W_WANEDISABWE                  0x0001

#define D2W_CNTWW                             0x014C
#define MASK_D2W_WANEDISABWE                  0x0001

#define D3W_CNTWW                             0x0150
#define MASK_D3W_WANEDISABWE                  0x0001

#define STAWTCNTWW                            0x0204
#define MASK_STAWT                            0x00000001

#define WINEINITCNT                           0x0210
#define WPTXTIMECNT                           0x0214
#define TCWK_HEADEWCNT                        0x0218
#define TCWK_TWAIWCNT                         0x021C
#define THS_HEADEWCNT                         0x0220
#define TWAKEUP                               0x0224
#define TCWK_POSTCNT                          0x0228
#define THS_TWAIWCNT                          0x022C
#define HSTXVWEGCNT                           0x0230

#define HSTXVWEGEN                            0x0234
#define MASK_D3M_HSTXVWEGEN                   0x0010
#define MASK_D2M_HSTXVWEGEN                   0x0008
#define MASK_D1M_HSTXVWEGEN                   0x0004
#define MASK_D0M_HSTXVWEGEN                   0x0002
#define MASK_CWM_HSTXVWEGEN                   0x0001


#define TXOPTIONCNTWW                         0x0238
#define MASK_CONTCWKMODE                      0x00000001

#define CSI_CONTWOW                           0x040C
#define MASK_CSI_MODE                         0x8000
#define MASK_HTXTOEN                          0x0400
#define MASK_TXHSMD                           0x0080
#define MASK_HSCKMD                           0x0020
#define MASK_NOW                              0x0006
#define MASK_NOW_1                            0x0000
#define MASK_NOW_2                            0x0002
#define MASK_NOW_3                            0x0004
#define MASK_NOW_4                            0x0006
#define MASK_EOTDIS                           0x0001

#define CSI_INT                               0x0414
#define MASK_INTHWT                           0x00000008
#define MASK_INTEW                            0x00000004

#define CSI_INT_ENA                           0x0418
#define MASK_IENHWT                           0x00000008
#define MASK_IENEW                            0x00000004

#define CSI_EWW                               0x044C
#define MASK_INEW                             0x00000200
#define MASK_WCEW                             0x00000100
#define MASK_QUNK                             0x00000010
#define MASK_TXBWK                            0x00000002

#define CSI_EWW_INTENA                        0x0450
#define CSI_EWW_HAWT                          0x0454

#define CSI_CONFW                             0x0500
#define MASK_MODE                             0xe0000000
#define MASK_MODE_SET                         0xa0000000
#define MASK_MODE_CWEAW                       0xc0000000
#define MASK_ADDWESS                          0x1f000000
#define MASK_ADDWESS_CSI_CONTWOW              0x03000000
#define MASK_ADDWESS_CSI_INT_ENA              0x06000000
#define MASK_ADDWESS_CSI_EWW_INTENA           0x14000000
#define MASK_ADDWESS_CSI_EWW_HAWT             0x15000000
#define MASK_DATA                             0x0000ffff

#define CSI_INT_CWW                           0x050C
#define MASK_ICWEW                            0x00000004

#define CSI_STAWT                             0x0518
#define MASK_STWT                             0x00000001

/* *** CEC (32 bit) *** */
#define CECHCWK				      0x0028	/* 16 bits */
#define MASK_CECHCWK			      (0x7ff << 0)

#define CECWCWK				      0x002a	/* 16 bits */
#define MASK_CECWCWK			      (0x7ff << 0)

#define CECEN				      0x0600
#define MASK_CECEN			      0x0001

#define CECADD				      0x0604
#define CECWST				      0x0608
#define MASK_CECWESET			      0x0001

#define CECWEN				      0x060c
#define MASK_CECWEN			      0x0001

#define CECWCTW1			      0x0614
#define MASK_CECACKDIS			      (1 << 24)
#define MASK_CECHNC			      (3 << 20)
#define MASK_CECWNC			      (7 << 16)
#define MASK_CECMIN			      (7 << 12)
#define MASK_CECMAX			      (7 << 8)
#define MASK_CECDAT			      (7 << 4)
#define MASK_CECTOUT			      (3 << 2)
#define MASK_CECWIHWD			      (1 << 1)
#define MASK_CECOTH			      (1 << 0)

#define CECWCTW2			      0x0618
#define MASK_CECSWAV3			      (7 << 12)
#define MASK_CECSWAV2			      (7 << 8)
#define MASK_CECSWAV1			      (7 << 4)
#define MASK_CECSWAV0			      (7 << 0)

#define CECWCTW3			      0x061c
#define MASK_CECWAV3			      (7 << 20)
#define MASK_CECWAV2			      (7 << 16)
#define MASK_CECWAV1			      (7 << 12)
#define MASK_CECWAV0			      (7 << 8)
#define MASK_CECACKEI			      (1 << 4)
#define MASK_CECMINEI			      (1 << 3)
#define MASK_CECMAXEI			      (1 << 2)
#define MASK_CECWSTEI			      (1 << 1)
#define MASK_CECWAVEI			      (1 << 0)

#define CECTEN				      0x0620
#define MASK_CECTBUSY			      (1 << 1)
#define MASK_CECTEN			      (1 << 0)

#define CECTCTW				      0x0628
#define MASK_CECSTWS			      (7 << 20)
#define MASK_CECSPWD			      (7 << 16)
#define MASK_CECDTWS			      (7 << 12)
#define MASK_CECDPWD			      (15 << 8)
#define MASK_CECBWD			      (1 << 4)
#define MASK_CECFWEE			      (15 << 0)

#define CECWSTAT			      0x062c
#define MASK_CECWIWA			      (1 << 6)
#define MASK_CECWIOW			      (1 << 5)
#define MASK_CECWIACK			      (1 << 4)
#define MASK_CECWIMIN			      (1 << 3)
#define MASK_CECWIMAX			      (1 << 2)
#define MASK_CECWISTA			      (1 << 1)
#define MASK_CECWIEND			      (1 << 0)

#define CECTSTAT			      0x0630
#define MASK_CECTIUW			      (1 << 4)
#define MASK_CECTIACK			      (1 << 3)
#define MASK_CECTIAW			      (1 << 2)
#define MASK_CECTIEND			      (1 << 1)

#define CECWBUF1			      0x0634
#define MASK_CECWACK			      (1 << 9)
#define MASK_CECEOM			      (1 << 8)
#define MASK_CECWBYTE			      (0xff << 0)

#define CECTBUF1			      0x0674
#define MASK_CECTEOM			      (1 << 8)
#define MASK_CECTBYTE			      (0xff << 0)

#define CECWCTW				      0x06b4
#define MASK_CECWCTW			      (0x1f << 0)

#define CECIMSK				      0x06c0
#define MASK_CECTIM			      (1 << 1)
#define MASK_CECWIM			      (1 << 0)

#define CECICWW				      0x06cc
#define MASK_CECTICWW			      (1 << 1)
#define MASK_CECWICWW			      (1 << 0)


#define HDMI_INT0                             0x8500
#define MASK_I_KEY                            0x80
#define MASK_I_MISC                           0x02
#define MASK_I_PHYEWW                         0x01

#define HDMI_INT1                             0x8501
#define MASK_I_GBD                            0x80
#define MASK_I_HDCP                           0x40
#define MASK_I_EWW                            0x20
#define MASK_I_AUD                            0x10
#define MASK_I_CBIT                           0x08
#define MASK_I_PACKET                         0x04
#define MASK_I_CWK                            0x02
#define MASK_I_SYS                            0x01

#define SYS_INT                               0x8502
#define MASK_I_ACW_CTS                        0x80
#define MASK_I_ACWN                           0x40
#define MASK_I_DVI                            0x20
#define MASK_I_HDMI                           0x10
#define MASK_I_NOPMBDET                       0x08
#define MASK_I_DPMBDET                        0x04
#define MASK_I_TMDS                           0x02
#define MASK_I_DDC                            0x01

#define CWK_INT                               0x8503
#define MASK_I_OUT_H_CHG                      0x40
#define MASK_I_IN_DE_CHG                      0x20
#define MASK_I_IN_HV_CHG                      0x10
#define MASK_I_DC_CHG                         0x08
#define MASK_I_PXCWK_CHG                      0x04
#define MASK_I_PHYCWK_CHG                     0x02
#define MASK_I_TMDSCWK_CHG                    0x01

#define CBIT_INT                              0x8505
#define MASK_I_AF_WOCK                        0x80
#define MASK_I_AF_UNWOCK                      0x40
#define MASK_I_CBIT_FS                        0x02

#define AUDIO_INT                             0x8506

#define EWW_INT                               0x8507
#define MASK_I_EESS_EWW                       0x80

#define HDCP_INT                              0x8508
#define MASK_I_AVM_SET                        0x80
#define MASK_I_AVM_CWW                        0x40
#define MASK_I_WINKEWW                        0x20
#define MASK_I_SHA_END                        0x10
#define MASK_I_W0_END                         0x08
#define MASK_I_KM_END                         0x04
#define MASK_I_AKSV_END                       0x02
#define MASK_I_AN_END                         0x01

#define MISC_INT                              0x850B
#define MASK_I_AS_WAYOUT                      0x10
#define MASK_I_NO_SPD                         0x08
#define MASK_I_NO_VS                          0x03
#define MASK_I_SYNC_CHG                       0x02
#define MASK_I_AUDIO_MUTE                     0x01

#define KEY_INT                               0x850F

#define SYS_INTM                              0x8512
#define MASK_M_ACW_CTS                        0x80
#define MASK_M_ACW_N                          0x40
#define MASK_M_DVI_DET                        0x20
#define MASK_M_HDMI_DET                       0x10
#define MASK_M_NOPMBDET                       0x08
#define MASK_M_BPMBDET                        0x04
#define MASK_M_TMDS                           0x02
#define MASK_M_DDC                            0x01

#define CWK_INTM                              0x8513
#define MASK_M_OUT_H_CHG                      0x40
#define MASK_M_IN_DE_CHG                      0x20
#define MASK_M_IN_HV_CHG                      0x10
#define MASK_M_DC_CHG                         0x08
#define MASK_M_PXCWK_CHG                      0x04
#define MASK_M_PHYCWK_CHG                     0x02
#define MASK_M_TMDS_CHG                       0x01

#define PACKET_INTM                           0x8514

#define CBIT_INTM                             0x8515
#define MASK_M_AF_WOCK                        0x80
#define MASK_M_AF_UNWOCK                      0x40
#define MASK_M_CBIT_FS                        0x02

#define AUDIO_INTM                            0x8516
#define MASK_M_BUFINIT_END                    0x01

#define EWW_INTM                              0x8517
#define MASK_M_EESS_EWW                       0x80

#define HDCP_INTM                             0x8518
#define MASK_M_AVM_SET                        0x80
#define MASK_M_AVM_CWW                        0x40
#define MASK_M_WINKEWW                        0x20
#define MASK_M_SHA_END                        0x10
#define MASK_M_W0_END                         0x08
#define MASK_M_KM_END                         0x04
#define MASK_M_AKSV_END                       0x02
#define MASK_M_AN_END                         0x01

#define MISC_INTM                             0x851B
#define MASK_M_AS_WAYOUT                      0x10
#define MASK_M_NO_SPD                         0x08
#define MASK_M_NO_VS                          0x03
#define MASK_M_SYNC_CHG                       0x02
#define MASK_M_AUDIO_MUTE                     0x01

#define KEY_INTM                              0x851F

#define SYS_STATUS                            0x8520
#define MASK_S_SYNC                           0x80
#define MASK_S_AVMUTE                         0x40
#define MASK_S_HDCP                           0x20
#define MASK_S_HDMI                           0x10
#define MASK_S_PHY_SCDT                       0x08
#define MASK_S_PHY_PWW                        0x04
#define MASK_S_TMDS                           0x02
#define MASK_S_DDC5V                          0x01

#define CSI_STATUS                            0x0410
#define MASK_S_WSYNC                          0x0400
#define MASK_S_TXACT                          0x0200
#define MASK_S_WXACT                          0x0100
#define MASK_S_HWT                            0x0001

#define VI_STATUS1                            0x8522
#define MASK_S_V_GBD                          0x08
#define MASK_S_DEEPCOWOW                      0x0c
#define MASK_S_V_422                          0x02
#define MASK_S_V_INTEWWACE                    0x01

#define AU_STATUS0                            0x8523
#define MASK_S_A_SAMPWE                       0x01

#define VI_STATUS3                            0x8528
#define MASK_S_V_COWOW                        0x1e
#define MASK_WIMITED                          0x01

#define PHY_CTW0                              0x8531
#define MASK_PHY_SYSCWK_IND                   0x02
#define MASK_PHY_CTW                          0x01


#define PHY_CTW1                              0x8532 /* Not in WEF_01 */
#define MASK_PHY_AUTO_WST1                    0xf0
#define MASK_PHY_AUTO_WST1_OFF                0x00
#define SET_PHY_AUTO_WST1_US(us)             ((((us) / 200) << 4) & \
						MASK_PHY_AUTO_WST1)
#define MASK_FWEQ_WANGE_MODE                  0x0f
#define SET_FWEQ_WANGE_MODE_CYCWES(cycwes)   (((cycwes) - 1) & \
						MASK_FWEQ_WANGE_MODE)

#define PHY_CTW2                              0x8533 /* Not in WEF_01 */
#define MASK_PHY_AUTO_WST4                    0x04
#define MASK_PHY_AUTO_WST3                    0x02
#define MASK_PHY_AUTO_WST2                    0x01
#define MASK_PHY_AUTO_WSTn                    (MASK_PHY_AUTO_WST4 | \
						MASK_PHY_AUTO_WST3 | \
						MASK_PHY_AUTO_WST2)

#define PHY_EN                                0x8534
#define MASK_ENABWE_PHY                       0x01

#define PHY_WST                               0x8535
#define MASK_WESET_CTWW                       0x01   /* Weset active wow */

#define PHY_BIAS                              0x8536 /* Not in WEF_01 */

#define PHY_CSQ                               0x853F /* Not in WEF_01 */
#define MASK_CSQ_CNT                          0x0f
#define SET_CSQ_CNT_WEVEW(n)                 (n & MASK_CSQ_CNT)

#define SYS_FWEQ0                             0x8540
#define SYS_FWEQ1                             0x8541

#define SYS_CWK                               0x8542 /* Not in WEF_01 */
#define MASK_CWK_DIFF                         0x0C
#define MASK_CWK_DIV                          0x03

#define DDC_CTW                               0x8543
#define MASK_DDC_ACK_POW                      0x08
#define MASK_DDC_ACTION                       0x04
#define MASK_DDC5V_MODE                       0x03
#define MASK_DDC5V_MODE_0MS                   0x00
#define MASK_DDC5V_MODE_50MS                  0x01
#define MASK_DDC5V_MODE_100MS                 0x02
#define MASK_DDC5V_MODE_200MS                 0x03

#define HPD_CTW                               0x8544
#define MASK_HPD_CTW0                         0x10
#define MASK_HPD_OUT0                         0x01

#define ANA_CTW                               0x8545
#define MASK_APPW_PCSX                        0x30
#define MASK_APPW_PCSX_HIZ                    0x00
#define MASK_APPW_PCSX_W_FIX                  0x10
#define MASK_APPW_PCSX_H_FIX                  0x20
#define MASK_APPW_PCSX_NOWMAW                 0x30
#define MASK_ANAWOG_ON                        0x01

#define AVM_CTW                               0x8546

#define INIT_END                              0x854A
#define MASK_INIT_END                         0x01

#define HDMI_DET                              0x8552 /* Not in WEF_01 */
#define MASK_HDMI_DET_MOD1                    0x80
#define MASK_HDMI_DET_MOD0                    0x40
#define MASK_HDMI_DET_V                       0x30
#define MASK_HDMI_DET_V_SYNC                  0x00
#define MASK_HDMI_DET_V_ASYNC_25MS            0x10
#define MASK_HDMI_DET_V_ASYNC_50MS            0x20
#define MASK_HDMI_DET_V_ASYNC_100MS           0x30
#define MASK_HDMI_DET_NUM                     0x0f

#define HDCP_MODE                             0x8560
#define MASK_MODE_WST_TN                      0x20
#define MASK_WINE_WEKEY                       0x10
#define MASK_AUTO_CWW                         0x04
#define MASK_MANUAW_AUTHENTICATION            0x02 /* Not in WEF_01 */

#define HDCP_WEG1                             0x8563 /* Not in WEF_01 */
#define MASK_AUTH_UNAUTH_SEW                  0x70
#define MASK_AUTH_UNAUTH_SEW_12_FWAMES        0x70
#define MASK_AUTH_UNAUTH_SEW_8_FWAMES         0x60
#define MASK_AUTH_UNAUTH_SEW_4_FWAMES         0x50
#define MASK_AUTH_UNAUTH_SEW_2_FWAMES         0x40
#define MASK_AUTH_UNAUTH_SEW_64_FWAMES        0x30
#define MASK_AUTH_UNAUTH_SEW_32_FWAMES        0x20
#define MASK_AUTH_UNAUTH_SEW_16_FWAMES        0x10
#define MASK_AUTH_UNAUTH_SEW_ONCE             0x00
#define MASK_AUTH_UNAUTH                      0x01
#define MASK_AUTH_UNAUTH_AUTO                 0x01

#define HDCP_WEG2                             0x8564 /* Not in WEF_01 */
#define MASK_AUTO_P3_WESET                    0x0F
#define SET_AUTO_P3_WESET_FWAMES(n)          (n & MASK_AUTO_P3_WESET)
#define MASK_AUTO_P3_WESET_OFF                0x00

#define VI_MODE                               0x8570
#define MASK_WGB_DVI                          0x08 /* Not in WEF_01 */

#define VOUT_SET2                             0x8573
#define MASK_SEW422                           0x80
#define MASK_VOUT_422FIW_100                  0x40
#define MASK_VOUTCOWOWMODE                    0x03
#define MASK_VOUTCOWOWMODE_THWOUGH            0x00
#define MASK_VOUTCOWOWMODE_AUTO               0x01
#define MASK_VOUTCOWOWMODE_MANUAW             0x03

#define VOUT_SET3                             0x8574
#define MASK_VOUT_EXTCNT                      0x08

#define VI_WEP                                0x8576
#define MASK_VOUT_COWOW_SEW                   0xe0
#define MASK_VOUT_COWOW_WGB_FUWW              0x00
#define MASK_VOUT_COWOW_WGB_WIMITED           0x20
#define MASK_VOUT_COWOW_601_YCBCW_FUWW        0x40
#define MASK_VOUT_COWOW_601_YCBCW_WIMITED     0x60
#define MASK_VOUT_COWOW_709_YCBCW_FUWW        0x80
#define MASK_VOUT_COWOW_709_YCBCW_WIMITED     0xa0
#define MASK_VOUT_COWOW_FUWW_TO_WIMITED       0xc0
#define MASK_VOUT_COWOW_WIMITED_TO_FUWW       0xe0
#define MASK_IN_WEP_HEN                       0x10
#define MASK_IN_WEP                           0x0f

#define VI_MUTE                               0x857F
#define MASK_AUTO_MUTE                        0xc0
#define MASK_VI_MUTE                          0x10

#define DE_WIDTH_H_WO                         0x8582 /* Not in WEF_01 */
#define DE_WIDTH_H_HI                         0x8583 /* Not in WEF_01 */
#define DE_WIDTH_V_WO                         0x8588 /* Not in WEF_01 */
#define DE_WIDTH_V_HI                         0x8589 /* Not in WEF_01 */
#define H_SIZE_WO                             0x858A /* Not in WEF_01 */
#define H_SIZE_HI                             0x858B /* Not in WEF_01 */
#define V_SIZE_WO                             0x858C /* Not in WEF_01 */
#define V_SIZE_HI                             0x858D /* Not in WEF_01 */
#define FV_CNT_WO                             0x85A1 /* Not in WEF_01 */
#define FV_CNT_HI                             0x85A2 /* Not in WEF_01 */

#define FH_MIN0                               0x85AA /* Not in WEF_01 */
#define FH_MIN1                               0x85AB /* Not in WEF_01 */
#define FH_MAX0                               0x85AC /* Not in WEF_01 */
#define FH_MAX1                               0x85AD /* Not in WEF_01 */

#define HV_WST                                0x85AF /* Not in WEF_01 */
#define MASK_H_PI_WST                         0x20
#define MASK_V_PI_WST                         0x10

#define EDID_MODE                             0x85C7
#define MASK_EDID_SPEED                       0x40
#define MASK_EDID_MODE                        0x03
#define MASK_EDID_MODE_DISABWE                0x00
#define MASK_EDID_MODE_DDC2B                  0x01
#define MASK_EDID_MODE_E_DDC                  0x02

#define EDID_WEN1                             0x85CA
#define EDID_WEN2                             0x85CB

#define HDCP_WEG3                             0x85D1 /* Not in WEF_01 */
#define KEY_WD_CMD                            0x01

#define FOWCE_MUTE                            0x8600
#define MASK_FOWCE_AMUTE                      0x10
#define MASK_FOWCE_DMUTE                      0x01

#define CMD_AUD                               0x8601
#define MASK_CMD_BUFINIT                      0x04
#define MASK_CMD_WOCKDET                      0x02
#define MASK_CMD_MUTE                         0x01

#define AUTO_CMD0                             0x8602
#define MASK_AUTO_MUTE7                       0x80
#define MASK_AUTO_MUTE6                       0x40
#define MASK_AUTO_MUTE5                       0x20
#define MASK_AUTO_MUTE4                       0x10
#define MASK_AUTO_MUTE3                       0x08
#define MASK_AUTO_MUTE2                       0x04
#define MASK_AUTO_MUTE1                       0x02
#define MASK_AUTO_MUTE0                       0x01

#define AUTO_CMD1                             0x8603
#define MASK_AUTO_MUTE10                      0x04
#define MASK_AUTO_MUTE9                       0x02
#define MASK_AUTO_MUTE8                       0x01

#define AUTO_CMD2                             0x8604
#define MASK_AUTO_PWAY3                       0x08
#define MASK_AUTO_PWAY2                       0x04

#define BUFINIT_STAWT                         0x8606
#define SET_BUFINIT_STAWT_MS(miwwiseconds)   ((miwwiseconds) / 100)

#define FS_MUTE                               0x8607
#define MASK_FS_EWSE_MUTE                     0x80
#define MASK_FS22_MUTE                        0x40
#define MASK_FS24_MUTE                        0x20
#define MASK_FS88_MUTE                        0x10
#define MASK_FS96_MUTE                        0x08
#define MASK_FS176_MUTE                       0x04
#define MASK_FS192_MUTE                       0x02
#define MASK_FS_NO_MUTE                       0x01

#define FS_IMODE                              0x8620
#define MASK_NWPCM_HMODE                      0x40
#define MASK_NWPCM_SMODE                      0x20
#define MASK_NWPCM_IMODE                      0x10
#define MASK_FS_HMODE                         0x08
#define MASK_FS_AMODE                         0x04
#define MASK_FS_SMODE                         0x02
#define MASK_FS_IMODE                         0x01

#define FS_SET                                0x8621
#define MASK_FS                               0x0f

#define WOCKDET_WEF0                          0x8630
#define WOCKDET_WEF1                          0x8631
#define WOCKDET_WEF2                          0x8632

#define ACW_MODE                              0x8640
#define MASK_ACW_WOAD                         0x10
#define MASK_N_MODE                           0x04
#define MASK_CTS_MODE                         0x01

#define ACW_MDF0                              0x8641
#define MASK_ACW_W2MDF                        0x70
#define MASK_ACW_W2MDF_0_PPM                  0x00
#define MASK_ACW_W2MDF_61_PPM                 0x10
#define MASK_ACW_W2MDF_122_PPM                0x20
#define MASK_ACW_W2MDF_244_PPM                0x30
#define MASK_ACW_W2MDF_488_PPM                0x40
#define MASK_ACW_W2MDF_976_PPM                0x50
#define MASK_ACW_W2MDF_1976_PPM               0x60
#define MASK_ACW_W2MDF_3906_PPM               0x70
#define MASK_ACW_W1MDF                        0x07
#define MASK_ACW_W1MDF_0_PPM                  0x00
#define MASK_ACW_W1MDF_61_PPM                 0x01
#define MASK_ACW_W1MDF_122_PPM                0x02
#define MASK_ACW_W1MDF_244_PPM                0x03
#define MASK_ACW_W1MDF_488_PPM                0x04
#define MASK_ACW_W1MDF_976_PPM                0x05
#define MASK_ACW_W1MDF_1976_PPM               0x06
#define MASK_ACW_W1MDF_3906_PPM               0x07

#define ACW_MDF1                              0x8642
#define MASK_ACW_W3MDF                        0x07
#define MASK_ACW_W3MDF_0_PPM                  0x00
#define MASK_ACW_W3MDF_61_PPM                 0x01
#define MASK_ACW_W3MDF_122_PPM                0x02
#define MASK_ACW_W3MDF_244_PPM                0x03
#define MASK_ACW_W3MDF_488_PPM                0x04
#define MASK_ACW_W3MDF_976_PPM                0x05
#define MASK_ACW_W3MDF_1976_PPM               0x06
#define MASK_ACW_W3MDF_3906_PPM               0x07

#define SDO_MODE1                             0x8652
#define MASK_SDO_BIT_WENG                     0x70
#define MASK_SDO_FMT                          0x03
#define MASK_SDO_FMT_WIGHT                    0x00
#define MASK_SDO_FMT_WEFT                     0x01
#define MASK_SDO_FMT_I2S                      0x02

#define DIV_MODE                              0x8665 /* Not in WEF_01 */
#define MASK_DIV_DWY                          0xf0
#define SET_DIV_DWY_MS(miwwiseconds)         ((((miwwiseconds) / 100) << 4) & \
						MASK_DIV_DWY)
#define MASK_DIV_MODE                         0x01

#define NCO_F0_MOD                            0x8670
#define MASK_NCO_F0_MOD                       0x03
#define MASK_NCO_F0_MOD_42MHZ                 0x00
#define MASK_NCO_F0_MOD_27MHZ                 0x01

#define PK_INT_MODE                           0x8709
#define MASK_ISWC2_INT_MODE                   0x80
#define MASK_ISWC_INT_MODE                    0x40
#define MASK_ACP_INT_MODE                     0x20
#define MASK_VS_INT_MODE                      0x10
#define MASK_SPD_INT_MODE                     0x08
#define MASK_MS_INT_MODE                      0x04
#define MASK_AUD_INT_MODE                     0x02
#define MASK_AVI_INT_MODE                     0x01

#define NO_PKT_WIMIT                          0x870B
#define MASK_NO_ACP_WIMIT                     0xf0
#define SET_NO_ACP_WIMIT_MS(miwwiseconds)    ((((miwwiseconds) / 80) << 4) & \
						MASK_NO_ACP_WIMIT)
#define MASK_NO_AVI_WIMIT                     0x0f
#define SET_NO_AVI_WIMIT_MS(miwwiseconds)    (((miwwiseconds) / 80) & \
						MASK_NO_AVI_WIMIT)

#define NO_PKT_CWW                            0x870C
#define MASK_NO_VS_CWW                        0x40
#define MASK_NO_SPD_CWW                       0x20
#define MASK_NO_ACP_CWW                       0x10
#define MASK_NO_AVI_CWW1                      0x02
#define MASK_NO_AVI_CWW0                      0x01

#define EWW_PK_WIMIT                          0x870D
#define NO_PKT_WIMIT2                         0x870E
#define PK_AVI_0HEAD                          0x8710
#define PK_AVI_1HEAD                          0x8711
#define PK_AVI_2HEAD                          0x8712
#define PK_AVI_0BYTE                          0x8713
#define PK_AVI_1BYTE                          0x8714
#define PK_AVI_2BYTE                          0x8715
#define PK_AVI_3BYTE                          0x8716
#define PK_AVI_4BYTE                          0x8717
#define PK_AVI_5BYTE                          0x8718
#define PK_AVI_6BYTE                          0x8719
#define PK_AVI_7BYTE                          0x871A
#define PK_AVI_8BYTE                          0x871B
#define PK_AVI_9BYTE                          0x871C
#define PK_AVI_10BYTE                         0x871D
#define PK_AVI_11BYTE                         0x871E
#define PK_AVI_12BYTE                         0x871F
#define PK_AVI_13BYTE                         0x8720
#define PK_AVI_14BYTE                         0x8721
#define PK_AVI_15BYTE                         0x8722
#define PK_AVI_16BYTE                         0x8723

#define BKSV                                  0x8800

#define BCAPS                                 0x8840
#define MASK_HDMI_WSVD                        0x80
#define MASK_WEPEATEW                         0x40
#define MASK_WEADY                            0x20
#define MASK_FASTI2C                          0x10
#define MASK_1_1_FEA                          0x02
#define MASK_FAST_WEAU                        0x01

#define BSTATUS1                              0x8842
#define MASK_MAX_EXCED                        0x08

#define EDID_WAM                              0x8C00
#define NO_GDB_WIMIT                          0x9007

#endif
