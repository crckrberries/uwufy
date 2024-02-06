/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef W420D_H
#define W420D_H

#define W_0001F8_MC_IND_INDEX                        0x0001F8
#define   S_0001F8_MC_IND_ADDW(x)                      (((x) & 0x7F) << 0)
#define   G_0001F8_MC_IND_ADDW(x)                      (((x) >> 0) & 0x7F)
#define   C_0001F8_MC_IND_ADDW                         0xFFFFFF80
#define   S_0001F8_MC_IND_WW_EN(x)                     (((x) & 0x1) << 8)
#define   G_0001F8_MC_IND_WW_EN(x)                     (((x) >> 8) & 0x1)
#define   C_0001F8_MC_IND_WW_EN                        0xFFFFFEFF
#define W_0001FC_MC_IND_DATA                         0x0001FC
#define   S_0001FC_MC_IND_DATA(x)                      (((x) & 0xFFFFFFFF) << 0)
#define   G_0001FC_MC_IND_DATA(x)                      (((x) >> 0) & 0xFFFFFFFF)
#define   C_0001FC_MC_IND_DATA                         0x00000000
#define W_0007C0_CP_STAT                             0x0007C0
#define   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 0)
#define   G_0007C0_MWU_BUSY(x)                         (((x) >> 0) & 0x1)
#define   C_0007C0_MWU_BUSY                            0xFFFFFFFE
#define   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 1)
#define   G_0007C0_MWU_BUSY(x)                         (((x) >> 1) & 0x1)
#define   C_0007C0_MWU_BUSY                            0xFFFFFFFD
#define   S_0007C0_WSIU_BUSY(x)                        (((x) & 0x1) << 2)
#define   G_0007C0_WSIU_BUSY(x)                        (((x) >> 2) & 0x1)
#define   C_0007C0_WSIU_BUSY                           0xFFFFFFFB
#define   S_0007C0_WCIU_BUSY(x)                        (((x) & 0x1) << 3)
#define   G_0007C0_WCIU_BUSY(x)                        (((x) >> 3) & 0x1)
#define   C_0007C0_WCIU_BUSY                           0xFFFFFFF7
#define   S_0007C0_CSF_PWIMAWY_BUSY(x)                 (((x) & 0x1) << 9)
#define   G_0007C0_CSF_PWIMAWY_BUSY(x)                 (((x) >> 9) & 0x1)
#define   C_0007C0_CSF_PWIMAWY_BUSY                    0xFFFFFDFF
#define   S_0007C0_CSF_INDIWECT_BUSY(x)                (((x) & 0x1) << 10)
#define   G_0007C0_CSF_INDIWECT_BUSY(x)                (((x) >> 10) & 0x1)
#define   C_0007C0_CSF_INDIWECT_BUSY                   0xFFFFFBFF
#define   S_0007C0_CSQ_PWIMAWY_BUSY(x)                 (((x) & 0x1) << 11)
#define   G_0007C0_CSQ_PWIMAWY_BUSY(x)                 (((x) >> 11) & 0x1)
#define   C_0007C0_CSQ_PWIMAWY_BUSY                    0xFFFFF7FF
#define   S_0007C0_CSQ_INDIWECT_BUSY(x)                (((x) & 0x1) << 12)
#define   G_0007C0_CSQ_INDIWECT_BUSY(x)                (((x) >> 12) & 0x1)
#define   C_0007C0_CSQ_INDIWECT_BUSY                   0xFFFFEFFF
#define   S_0007C0_CSI_BUSY(x)                         (((x) & 0x1) << 13)
#define   G_0007C0_CSI_BUSY(x)                         (((x) >> 13) & 0x1)
#define   C_0007C0_CSI_BUSY                            0xFFFFDFFF
#define   S_0007C0_CSF_INDIWECT2_BUSY(x)               (((x) & 0x1) << 14)
#define   G_0007C0_CSF_INDIWECT2_BUSY(x)               (((x) >> 14) & 0x1)
#define   C_0007C0_CSF_INDIWECT2_BUSY                  0xFFFFBFFF
#define   S_0007C0_CSQ_INDIWECT2_BUSY(x)               (((x) & 0x1) << 15)
#define   G_0007C0_CSQ_INDIWECT2_BUSY(x)               (((x) >> 15) & 0x1)
#define   C_0007C0_CSQ_INDIWECT2_BUSY                  0xFFFF7FFF
#define   S_0007C0_GUIDMA_BUSY(x)                      (((x) & 0x1) << 28)
#define   G_0007C0_GUIDMA_BUSY(x)                      (((x) >> 28) & 0x1)
#define   C_0007C0_GUIDMA_BUSY                         0xEFFFFFFF
#define   S_0007C0_VIDDMA_BUSY(x)                      (((x) & 0x1) << 29)
#define   G_0007C0_VIDDMA_BUSY(x)                      (((x) >> 29) & 0x1)
#define   C_0007C0_VIDDMA_BUSY                         0xDFFFFFFF
#define   S_0007C0_CMDSTWM_BUSY(x)                     (((x) & 0x1) << 30)
#define   G_0007C0_CMDSTWM_BUSY(x)                     (((x) >> 30) & 0x1)
#define   C_0007C0_CMDSTWM_BUSY                        0xBFFFFFFF
#define   S_0007C0_CP_BUSY(x)                          (((x) & 0x1) << 31)
#define   G_0007C0_CP_BUSY(x)                          (((x) >> 31) & 0x1)
#define   C_0007C0_CP_BUSY                             0x7FFFFFFF
#define W_000E40_WBBM_STATUS                         0x000E40
#define   S_000E40_CMDFIFO_AVAIW(x)                    (((x) & 0x7F) << 0)
#define   G_000E40_CMDFIFO_AVAIW(x)                    (((x) >> 0) & 0x7F)
#define   C_000E40_CMDFIFO_AVAIW                       0xFFFFFF80
#define   S_000E40_HIWQ_ON_WBB(x)                      (((x) & 0x1) << 8)
#define   G_000E40_HIWQ_ON_WBB(x)                      (((x) >> 8) & 0x1)
#define   C_000E40_HIWQ_ON_WBB                         0xFFFFFEFF
#define   S_000E40_CPWQ_ON_WBB(x)                      (((x) & 0x1) << 9)
#define   G_000E40_CPWQ_ON_WBB(x)                      (((x) >> 9) & 0x1)
#define   C_000E40_CPWQ_ON_WBB                         0xFFFFFDFF
#define   S_000E40_CFWQ_ON_WBB(x)                      (((x) & 0x1) << 10)
#define   G_000E40_CFWQ_ON_WBB(x)                      (((x) >> 10) & 0x1)
#define   C_000E40_CFWQ_ON_WBB                         0xFFFFFBFF
#define   S_000E40_HIWQ_IN_WTBUF(x)                    (((x) & 0x1) << 11)
#define   G_000E40_HIWQ_IN_WTBUF(x)                    (((x) >> 11) & 0x1)
#define   C_000E40_HIWQ_IN_WTBUF                       0xFFFFF7FF
#define   S_000E40_CPWQ_IN_WTBUF(x)                    (((x) & 0x1) << 12)
#define   G_000E40_CPWQ_IN_WTBUF(x)                    (((x) >> 12) & 0x1)
#define   C_000E40_CPWQ_IN_WTBUF                       0xFFFFEFFF
#define   S_000E40_CFWQ_IN_WTBUF(x)                    (((x) & 0x1) << 13)
#define   G_000E40_CFWQ_IN_WTBUF(x)                    (((x) >> 13) & 0x1)
#define   C_000E40_CFWQ_IN_WTBUF                       0xFFFFDFFF
#define   S_000E40_CF_PIPE_BUSY(x)                     (((x) & 0x1) << 14)
#define   G_000E40_CF_PIPE_BUSY(x)                     (((x) >> 14) & 0x1)
#define   C_000E40_CF_PIPE_BUSY                        0xFFFFBFFF
#define   S_000E40_ENG_EV_BUSY(x)                      (((x) & 0x1) << 15)
#define   G_000E40_ENG_EV_BUSY(x)                      (((x) >> 15) & 0x1)
#define   C_000E40_ENG_EV_BUSY                         0xFFFF7FFF
#define   S_000E40_CP_CMDSTWM_BUSY(x)                  (((x) & 0x1) << 16)
#define   G_000E40_CP_CMDSTWM_BUSY(x)                  (((x) >> 16) & 0x1)
#define   C_000E40_CP_CMDSTWM_BUSY                     0xFFFEFFFF
#define   S_000E40_E2_BUSY(x)                          (((x) & 0x1) << 17)
#define   G_000E40_E2_BUSY(x)                          (((x) >> 17) & 0x1)
#define   C_000E40_E2_BUSY                             0xFFFDFFFF
#define   S_000E40_WB2D_BUSY(x)                        (((x) & 0x1) << 18)
#define   G_000E40_WB2D_BUSY(x)                        (((x) >> 18) & 0x1)
#define   C_000E40_WB2D_BUSY                           0xFFFBFFFF
#define   S_000E40_WB3D_BUSY(x)                        (((x) & 0x1) << 19)
#define   G_000E40_WB3D_BUSY(x)                        (((x) >> 19) & 0x1)
#define   C_000E40_WB3D_BUSY                           0xFFF7FFFF
#define   S_000E40_VAP_BUSY(x)                         (((x) & 0x1) << 20)
#define   G_000E40_VAP_BUSY(x)                         (((x) >> 20) & 0x1)
#define   C_000E40_VAP_BUSY                            0xFFEFFFFF
#define   S_000E40_WE_BUSY(x)                          (((x) & 0x1) << 21)
#define   G_000E40_WE_BUSY(x)                          (((x) >> 21) & 0x1)
#define   C_000E40_WE_BUSY                             0xFFDFFFFF
#define   S_000E40_TAM_BUSY(x)                         (((x) & 0x1) << 22)
#define   G_000E40_TAM_BUSY(x)                         (((x) >> 22) & 0x1)
#define   C_000E40_TAM_BUSY                            0xFFBFFFFF
#define   S_000E40_TDM_BUSY(x)                         (((x) & 0x1) << 23)
#define   G_000E40_TDM_BUSY(x)                         (((x) >> 23) & 0x1)
#define   C_000E40_TDM_BUSY                            0xFF7FFFFF
#define   S_000E40_PB_BUSY(x)                          (((x) & 0x1) << 24)
#define   G_000E40_PB_BUSY(x)                          (((x) >> 24) & 0x1)
#define   C_000E40_PB_BUSY                             0xFEFFFFFF
#define   S_000E40_TIM_BUSY(x)                         (((x) & 0x1) << 25)
#define   G_000E40_TIM_BUSY(x)                         (((x) >> 25) & 0x1)
#define   C_000E40_TIM_BUSY                            0xFDFFFFFF
#define   S_000E40_GA_BUSY(x)                          (((x) & 0x1) << 26)
#define   G_000E40_GA_BUSY(x)                          (((x) >> 26) & 0x1)
#define   C_000E40_GA_BUSY                             0xFBFFFFFF
#define   S_000E40_CBA2D_BUSY(x)                       (((x) & 0x1) << 27)
#define   G_000E40_CBA2D_BUSY(x)                       (((x) >> 27) & 0x1)
#define   C_000E40_CBA2D_BUSY                          0xF7FFFFFF
#define   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#define   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#define   C_000E40_GUI_ACTIVE                          0x7FFFFFFF

/* CWK wegistews */
#define W_00000D_SCWK_CNTW                           0x00000D
#define   S_00000D_SCWK_SWC_SEW(x)                     (((x) & 0x7) << 0)
#define   G_00000D_SCWK_SWC_SEW(x)                     (((x) >> 0) & 0x7)
#define   C_00000D_SCWK_SWC_SEW                        0xFFFFFFF8
#define   S_00000D_CP_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 3)
#define   G_00000D_CP_MAX_DYN_STOP_WAT(x)              (((x) >> 3) & 0x1)
#define   C_00000D_CP_MAX_DYN_STOP_WAT                 0xFFFFFFF7
#define   S_00000D_HDP_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 4)
#define   G_00000D_HDP_MAX_DYN_STOP_WAT(x)             (((x) >> 4) & 0x1)
#define   C_00000D_HDP_MAX_DYN_STOP_WAT                0xFFFFFFEF
#define   S_00000D_TV_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 5)
#define   G_00000D_TV_MAX_DYN_STOP_WAT(x)              (((x) >> 5) & 0x1)
#define   C_00000D_TV_MAX_DYN_STOP_WAT                 0xFFFFFFDF
#define   S_00000D_E2_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 6)
#define   G_00000D_E2_MAX_DYN_STOP_WAT(x)              (((x) >> 6) & 0x1)
#define   C_00000D_E2_MAX_DYN_STOP_WAT                 0xFFFFFFBF
#define   S_00000D_SE_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 7)
#define   G_00000D_SE_MAX_DYN_STOP_WAT(x)              (((x) >> 7) & 0x1)
#define   C_00000D_SE_MAX_DYN_STOP_WAT                 0xFFFFFF7F
#define   S_00000D_IDCT_MAX_DYN_STOP_WAT(x)            (((x) & 0x1) << 8)
#define   G_00000D_IDCT_MAX_DYN_STOP_WAT(x)            (((x) >> 8) & 0x1)
#define   C_00000D_IDCT_MAX_DYN_STOP_WAT               0xFFFFFEFF
#define   S_00000D_VIP_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 9)
#define   G_00000D_VIP_MAX_DYN_STOP_WAT(x)             (((x) >> 9) & 0x1)
#define   C_00000D_VIP_MAX_DYN_STOP_WAT                0xFFFFFDFF
#define   S_00000D_WE_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 10)
#define   G_00000D_WE_MAX_DYN_STOP_WAT(x)              (((x) >> 10) & 0x1)
#define   C_00000D_WE_MAX_DYN_STOP_WAT                 0xFFFFFBFF
#define   S_00000D_PB_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 11)
#define   G_00000D_PB_MAX_DYN_STOP_WAT(x)              (((x) >> 11) & 0x1)
#define   C_00000D_PB_MAX_DYN_STOP_WAT                 0xFFFFF7FF
#define   S_00000D_TAM_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 12)
#define   G_00000D_TAM_MAX_DYN_STOP_WAT(x)             (((x) >> 12) & 0x1)
#define   C_00000D_TAM_MAX_DYN_STOP_WAT                0xFFFFEFFF
#define   S_00000D_TDM_MAX_DYN_STOP_WAT(x)             (((x) & 0x1) << 13)
#define   G_00000D_TDM_MAX_DYN_STOP_WAT(x)             (((x) >> 13) & 0x1)
#define   C_00000D_TDM_MAX_DYN_STOP_WAT                0xFFFFDFFF
#define   S_00000D_WB_MAX_DYN_STOP_WAT(x)              (((x) & 0x1) << 14)
#define   G_00000D_WB_MAX_DYN_STOP_WAT(x)              (((x) >> 14) & 0x1)
#define   C_00000D_WB_MAX_DYN_STOP_WAT                 0xFFFFBFFF
#define   S_00000D_FOWCE_DISP2(x)                      (((x) & 0x1) << 15)
#define   G_00000D_FOWCE_DISP2(x)                      (((x) >> 15) & 0x1)
#define   C_00000D_FOWCE_DISP2                         0xFFFF7FFF
#define   S_00000D_FOWCE_CP(x)                         (((x) & 0x1) << 16)
#define   G_00000D_FOWCE_CP(x)                         (((x) >> 16) & 0x1)
#define   C_00000D_FOWCE_CP                            0xFFFEFFFF
#define   S_00000D_FOWCE_HDP(x)                        (((x) & 0x1) << 17)
#define   G_00000D_FOWCE_HDP(x)                        (((x) >> 17) & 0x1)
#define   C_00000D_FOWCE_HDP                           0xFFFDFFFF
#define   S_00000D_FOWCE_DISP1(x)                      (((x) & 0x1) << 18)
#define   G_00000D_FOWCE_DISP1(x)                      (((x) >> 18) & 0x1)
#define   C_00000D_FOWCE_DISP1                         0xFFFBFFFF
#define   S_00000D_FOWCE_TOP(x)                        (((x) & 0x1) << 19)
#define   G_00000D_FOWCE_TOP(x)                        (((x) >> 19) & 0x1)
#define   C_00000D_FOWCE_TOP                           0xFFF7FFFF
#define   S_00000D_FOWCE_E2(x)                         (((x) & 0x1) << 20)
#define   G_00000D_FOWCE_E2(x)                         (((x) >> 20) & 0x1)
#define   C_00000D_FOWCE_E2                            0xFFEFFFFF
#define   S_00000D_FOWCE_VAP(x)                        (((x) & 0x1) << 21)
#define   G_00000D_FOWCE_VAP(x)                        (((x) >> 21) & 0x1)
#define   C_00000D_FOWCE_VAP                           0xFFDFFFFF
#define   S_00000D_FOWCE_IDCT(x)                       (((x) & 0x1) << 22)
#define   G_00000D_FOWCE_IDCT(x)                       (((x) >> 22) & 0x1)
#define   C_00000D_FOWCE_IDCT                          0xFFBFFFFF
#define   S_00000D_FOWCE_VIP(x)                        (((x) & 0x1) << 23)
#define   G_00000D_FOWCE_VIP(x)                        (((x) >> 23) & 0x1)
#define   C_00000D_FOWCE_VIP                           0xFF7FFFFF
#define   S_00000D_FOWCE_WE(x)                         (((x) & 0x1) << 24)
#define   G_00000D_FOWCE_WE(x)                         (((x) >> 24) & 0x1)
#define   C_00000D_FOWCE_WE                            0xFEFFFFFF
#define   S_00000D_FOWCE_SW(x)                         (((x) & 0x1) << 25)
#define   G_00000D_FOWCE_SW(x)                         (((x) >> 25) & 0x1)
#define   C_00000D_FOWCE_SW                            0xFDFFFFFF
#define   S_00000D_FOWCE_PX(x)                         (((x) & 0x1) << 26)
#define   G_00000D_FOWCE_PX(x)                         (((x) >> 26) & 0x1)
#define   C_00000D_FOWCE_PX                            0xFBFFFFFF
#define   S_00000D_FOWCE_TX(x)                         (((x) & 0x1) << 27)
#define   G_00000D_FOWCE_TX(x)                         (((x) >> 27) & 0x1)
#define   C_00000D_FOWCE_TX                            0xF7FFFFFF
#define   S_00000D_FOWCE_US(x)                         (((x) & 0x1) << 28)
#define   G_00000D_FOWCE_US(x)                         (((x) >> 28) & 0x1)
#define   C_00000D_FOWCE_US                            0xEFFFFFFF
#define   S_00000D_FOWCE_TV_SCWK(x)                    (((x) & 0x1) << 29)
#define   G_00000D_FOWCE_TV_SCWK(x)                    (((x) >> 29) & 0x1)
#define   C_00000D_FOWCE_TV_SCWK                       0xDFFFFFFF
#define   S_00000D_FOWCE_SU(x)                         (((x) & 0x1) << 30)
#define   G_00000D_FOWCE_SU(x)                         (((x) >> 30) & 0x1)
#define   C_00000D_FOWCE_SU                            0xBFFFFFFF
#define   S_00000D_FOWCE_OV0(x)                        (((x) & 0x1) << 31)
#define   G_00000D_FOWCE_OV0(x)                        (((x) >> 31) & 0x1)
#define   C_00000D_FOWCE_OV0                           0x7FFFFFFF

#endif
