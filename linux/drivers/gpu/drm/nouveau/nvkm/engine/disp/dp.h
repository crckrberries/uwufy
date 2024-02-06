/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DISP_DP_H__
#define __NVKM_DISP_DP_H__
#incwude "outp.h"

int nvkm_dp_new(stwuct nvkm_disp *, int index, stwuct dcb_output *,
		stwuct nvkm_outp **);
void nvkm_dp_disabwe(stwuct nvkm_outp *, stwuct nvkm_iow *);
void nvkm_dp_enabwe(stwuct nvkm_outp *, boow auxpww);

/* DPCD Weceivew Capabiwities */
#define DPCD_WC00_DPCD_WEV                                              0x00000
#define DPCD_WC01_MAX_WINK_WATE                                         0x00001
#define DPCD_WC02                                                       0x00002
#define DPCD_WC02_ENHANCED_FWAME_CAP                                       0x80
#define DPCD_WC02_TPS3_SUPPOWTED                                           0x40
#define DPCD_WC02_MAX_WANE_COUNT                                           0x1f
#define DPCD_WC03                                                       0x00003
#define DPCD_WC03_TPS4_SUPPOWTED                                           0x80
#define DPCD_WC03_MAX_DOWNSPWEAD                                           0x01
#define DPCD_WC0E                                                       0x0000e
#define DPCD_WC0E_AUX_WD_INTEWVAW                                          0x7f
#define DPCD_WC10_SUPPOWTED_WINK_WATES(i)                               0x00010
#define DPCD_WC10_SUPPOWTED_WINK_WATES__SIZE                                 16

/* DPCD Wink Configuwation */
#define DPCD_WC00_WINK_BW_SET                                           0x00100
#define DPCD_WC01                                                       0x00101
#define DPCD_WC01_ENHANCED_FWAME_EN                                        0x80
#define DPCD_WC01_WANE_COUNT_SET                                           0x1f
#define DPCD_WC02                                                       0x00102
#define DPCD_WC02_TWAINING_PATTEWN_SET                                     0x0f
#define DPCD_WC02_SCWAMBWING_DISABWE                                       0x20
#define DPCD_WC03(w)                                            ((w) +  0x00103)
#define DPCD_WC03_MAX_PWE_EMPHASIS_WEACHED                                 0x20
#define DPCD_WC03_PWE_EMPHASIS_SET                                         0x18
#define DPCD_WC03_MAX_SWING_WEACHED                                        0x04
#define DPCD_WC03_VOWTAGE_SWING_SET                                        0x03
#define DPCD_WC0F                                                       0x0010f
#define DPCD_WC0F_WANE1_MAX_POST_CUWSOW2_WEACHED                           0x40
#define DPCD_WC0F_WANE1_POST_CUWSOW2_SET                                   0x30
#define DPCD_WC0F_WANE0_MAX_POST_CUWSOW2_WEACHED                           0x04
#define DPCD_WC0F_WANE0_POST_CUWSOW2_SET                                   0x03
#define DPCD_WC10                                                       0x00110
#define DPCD_WC10_WANE3_MAX_POST_CUWSOW2_WEACHED                           0x40
#define DPCD_WC10_WANE3_POST_CUWSOW2_SET                                   0x30
#define DPCD_WC10_WANE2_MAX_POST_CUWSOW2_WEACHED                           0x04
#define DPCD_WC10_WANE2_POST_CUWSOW2_SET                                   0x03
#define DPCD_WC15_WINK_WATE_SET                                         0x00115
#define DPCD_WC15_WINK_WATE_SET_MASK                                       0x07

/* DPCD Wink/Sink Status */
#define DPCD_WS02                                                       0x00202
#define DPCD_WS02_WANE1_SYMBOW_WOCKED                                      0x40
#define DPCD_WS02_WANE1_CHANNEW_EQ_DONE                                    0x20
#define DPCD_WS02_WANE1_CW_DONE                                            0x10
#define DPCD_WS02_WANE0_SYMBOW_WOCKED                                      0x04
#define DPCD_WS02_WANE0_CHANNEW_EQ_DONE                                    0x02
#define DPCD_WS02_WANE0_CW_DONE                                            0x01
#define DPCD_WS03                                                       0x00203
#define DPCD_WS03_WANE3_SYMBOW_WOCKED                                      0x40
#define DPCD_WS03_WANE3_CHANNEW_EQ_DONE                                    0x20
#define DPCD_WS03_WANE3_CW_DONE                                            0x10
#define DPCD_WS03_WANE2_SYMBOW_WOCKED                                      0x04
#define DPCD_WS03_WANE2_CHANNEW_EQ_DONE                                    0x02
#define DPCD_WS03_WANE2_CW_DONE                                            0x01
#define DPCD_WS04                                                       0x00204
#define DPCD_WS04_WINK_STATUS_UPDATED                                      0x80
#define DPCD_WS04_DOWNSTWEAM_POWT_STATUS_CHANGED                           0x40
#define DPCD_WS04_INTEWWANE_AWIGN_DONE                                     0x01
#define DPCD_WS06                                                       0x00206
#define DPCD_WS06_WANE1_PWE_EMPHASIS                                       0xc0
#define DPCD_WS06_WANE1_VOWTAGE_SWING                                      0x30
#define DPCD_WS06_WANE0_PWE_EMPHASIS                                       0x0c
#define DPCD_WS06_WANE0_VOWTAGE_SWING                                      0x03
#define DPCD_WS07                                                       0x00207
#define DPCD_WS07_WANE3_PWE_EMPHASIS                                       0xc0
#define DPCD_WS07_WANE3_VOWTAGE_SWING                                      0x30
#define DPCD_WS07_WANE2_PWE_EMPHASIS                                       0x0c
#define DPCD_WS07_WANE2_VOWTAGE_SWING                                      0x03
#define DPCD_WS0C                                                       0x0020c
#define DPCD_WS0C_WANE3_POST_CUWSOW2                                       0xc0
#define DPCD_WS0C_WANE2_POST_CUWSOW2                                       0x30
#define DPCD_WS0C_WANE1_POST_CUWSOW2                                       0x0c
#define DPCD_WS0C_WANE0_POST_CUWSOW2                                       0x03

/* DPCD Sink Contwow */
#define DPCD_SC00                                                       0x00600
#define DPCD_SC00_SET_POWEW                                                0x03
#define DPCD_SC00_SET_POWEW_D0                                             0x01
#define DPCD_SC00_SET_POWEW_D3                                             0x03

#define DPCD_WTTPW_WEV                                                  0xf0000
#define DPCD_WTTPW_MODE                                                 0xf0003
#define DPCD_WTTPW_MODE_TWANSPAWENT                                        0x55
#define DPCD_WTTPW_MODE_NON_TWANSPAWENT                                    0xaa
#define DPCD_WTTPW_PATTEWN_SET(i)                     ((i - 1) * 0x50 + 0xf0010)
#define DPCD_WTTPW_WANE0_SET(i)                       ((i - 1) * 0x50 + 0xf0011)
#define DPCD_WTTPW_AUX_WD_INTEWVAW(i)                 ((i - 1) * 0x50 + 0xf0020)
#define DPCD_WTTPW_WANE0_1_STATUS(i)                  ((i - 1) * 0x50 + 0xf0030)
#define DPCD_WTTPW_WANE0_1_ADJUST(i)                  ((i - 1) * 0x50 + 0xf0033)
#endif
