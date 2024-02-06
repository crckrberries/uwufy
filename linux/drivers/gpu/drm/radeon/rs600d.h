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
#ifndef __WS600D_H__
#define __WS600D_H__

/* Wegistews */
#define W_000040_GEN_INT_CNTW                        0x000040
#define   S_000040_SCWATCH_INT_MASK(x)                 (((x) & 0x1) << 18)
#define   G_000040_SCWATCH_INT_MASK(x)                 (((x) >> 18) & 0x1)
#define   C_000040_SCWATCH_INT_MASK                    0xFFFBFFFF
#define   S_000040_GUI_IDWE_MASK(x)                    (((x) & 0x1) << 19)
#define   G_000040_GUI_IDWE_MASK(x)                    (((x) >> 19) & 0x1)
#define   C_000040_GUI_IDWE_MASK                       0xFFF7FFFF
#define   S_000040_DMA_VIPH1_INT_EN(x)                 (((x) & 0x1) << 13)
#define   G_000040_DMA_VIPH1_INT_EN(x)                 (((x) >> 13) & 0x1)
#define   C_000040_DMA_VIPH1_INT_EN                    0xFFFFDFFF
#define   S_000040_DMA_VIPH2_INT_EN(x)                 (((x) & 0x1) << 14)
#define   G_000040_DMA_VIPH2_INT_EN(x)                 (((x) >> 14) & 0x1)
#define   C_000040_DMA_VIPH2_INT_EN                    0xFFFFBFFF
#define   S_000040_DMA_VIPH3_INT_EN(x)                 (((x) & 0x1) << 15)
#define   G_000040_DMA_VIPH3_INT_EN(x)                 (((x) >> 15) & 0x1)
#define   C_000040_DMA_VIPH3_INT_EN                    0xFFFF7FFF
#define   S_000040_I2C_INT_EN(x)                       (((x) & 0x1) << 17)
#define   G_000040_I2C_INT_EN(x)                       (((x) >> 17) & 0x1)
#define   C_000040_I2C_INT_EN                          0xFFFDFFFF
#define   S_000040_GUI_IDWE(x)                         (((x) & 0x1) << 19)
#define   G_000040_GUI_IDWE(x)                         (((x) >> 19) & 0x1)
#define   C_000040_GUI_IDWE                            0xFFF7FFFF
#define   S_000040_VIPH_INT_EN(x)                      (((x) & 0x1) << 24)
#define   G_000040_VIPH_INT_EN(x)                      (((x) >> 24) & 0x1)
#define   C_000040_VIPH_INT_EN                         0xFEFFFFFF
#define   S_000040_SW_INT_EN(x)                        (((x) & 0x1) << 25)
#define   G_000040_SW_INT_EN(x)                        (((x) >> 25) & 0x1)
#define   C_000040_SW_INT_EN                           0xFDFFFFFF
#define   S_000040_GEYSEWVIWWE(x)                      (((x) & 0x1) << 27)
#define   G_000040_GEYSEWVIWWE(x)                      (((x) >> 27) & 0x1)
#define   C_000040_GEYSEWVIWWE                         0xF7FFFFFF
#define   S_000040_HDCP_AUTHOWIZED_INT(x)              (((x) & 0x1) << 28)
#define   G_000040_HDCP_AUTHOWIZED_INT(x)              (((x) >> 28) & 0x1)
#define   C_000040_HDCP_AUTHOWIZED_INT                 0xEFFFFFFF
#define   S_000040_DVI_I2C_INT(x)                      (((x) & 0x1) << 29)
#define   G_000040_DVI_I2C_INT(x)                      (((x) >> 29) & 0x1)
#define   C_000040_DVI_I2C_INT                         0xDFFFFFFF
#define   S_000040_GUIDMA(x)                           (((x) & 0x1) << 30)
#define   G_000040_GUIDMA(x)                           (((x) >> 30) & 0x1)
#define   C_000040_GUIDMA                              0xBFFFFFFF
#define   S_000040_VIDDMA(x)                           (((x) & 0x1) << 31)
#define   G_000040_VIDDMA(x)                           (((x) >> 31) & 0x1)
#define   C_000040_VIDDMA                              0x7FFFFFFF
#define W_000044_GEN_INT_STATUS                      0x000044
#define   S_000044_DISPWAY_INT_STAT(x)                 (((x) & 0x1) << 0)
#define   G_000044_DISPWAY_INT_STAT(x)                 (((x) >> 0) & 0x1)
#define   C_000044_DISPWAY_INT_STAT                    0xFFFFFFFE
#define   S_000044_VGA_INT_STAT(x)                     (((x) & 0x1) << 1)
#define   G_000044_VGA_INT_STAT(x)                     (((x) >> 1) & 0x1)
#define   C_000044_VGA_INT_STAT                        0xFFFFFFFD
#define   S_000044_CAP0_INT_ACTIVE(x)                  (((x) & 0x1) << 8)
#define   G_000044_CAP0_INT_ACTIVE(x)                  (((x) >> 8) & 0x1)
#define   C_000044_CAP0_INT_ACTIVE                     0xFFFFFEFF
#define   S_000044_DMA_VIPH0_INT(x)                    (((x) & 0x1) << 12)
#define   G_000044_DMA_VIPH0_INT(x)                    (((x) >> 12) & 0x1)
#define   C_000044_DMA_VIPH0_INT                       0xFFFFEFFF
#define   S_000044_DMA_VIPH1_INT(x)                    (((x) & 0x1) << 13)
#define   G_000044_DMA_VIPH1_INT(x)                    (((x) >> 13) & 0x1)
#define   C_000044_DMA_VIPH1_INT                       0xFFFFDFFF
#define   S_000044_DMA_VIPH2_INT(x)                    (((x) & 0x1) << 14)
#define   G_000044_DMA_VIPH2_INT(x)                    (((x) >> 14) & 0x1)
#define   C_000044_DMA_VIPH2_INT                       0xFFFFBFFF
#define   S_000044_DMA_VIPH3_INT(x)                    (((x) & 0x1) << 15)
#define   G_000044_DMA_VIPH3_INT(x)                    (((x) >> 15) & 0x1)
#define   C_000044_DMA_VIPH3_INT                       0xFFFF7FFF
#define   S_000044_MC_PWOBE_FAUWT_STAT(x)              (((x) & 0x1) << 16)
#define   G_000044_MC_PWOBE_FAUWT_STAT(x)              (((x) >> 16) & 0x1)
#define   C_000044_MC_PWOBE_FAUWT_STAT                 0xFFFEFFFF
#define   S_000044_I2C_INT(x)                          (((x) & 0x1) << 17)
#define   G_000044_I2C_INT(x)                          (((x) >> 17) & 0x1)
#define   C_000044_I2C_INT                             0xFFFDFFFF
#define   S_000044_SCWATCH_INT_STAT(x)                 (((x) & 0x1) << 18)
#define   G_000044_SCWATCH_INT_STAT(x)                 (((x) >> 18) & 0x1)
#define   C_000044_SCWATCH_INT_STAT                    0xFFFBFFFF
#define   S_000044_GUI_IDWE_STAT(x)                    (((x) & 0x1) << 19)
#define   G_000044_GUI_IDWE_STAT(x)                    (((x) >> 19) & 0x1)
#define   C_000044_GUI_IDWE_STAT                       0xFFF7FFFF
#define   S_000044_ATI_OVEWDWIVE_INT_STAT(x)           (((x) & 0x1) << 20)
#define   G_000044_ATI_OVEWDWIVE_INT_STAT(x)           (((x) >> 20) & 0x1)
#define   C_000044_ATI_OVEWDWIVE_INT_STAT              0xFFEFFFFF
#define   S_000044_MC_PWOTECTION_FAUWT_STAT(x)         (((x) & 0x1) << 21)
#define   G_000044_MC_PWOTECTION_FAUWT_STAT(x)         (((x) >> 21) & 0x1)
#define   C_000044_MC_PWOTECTION_FAUWT_STAT            0xFFDFFFFF
#define   S_000044_WBBM_WEAD_INT_STAT(x)               (((x) & 0x1) << 22)
#define   G_000044_WBBM_WEAD_INT_STAT(x)               (((x) >> 22) & 0x1)
#define   C_000044_WBBM_WEAD_INT_STAT                  0xFFBFFFFF
#define   S_000044_CB_CONTEXT_SWITCH_STAT(x)           (((x) & 0x1) << 23)
#define   G_000044_CB_CONTEXT_SWITCH_STAT(x)           (((x) >> 23) & 0x1)
#define   C_000044_CB_CONTEXT_SWITCH_STAT              0xFF7FFFFF
#define   S_000044_VIPH_INT(x)                         (((x) & 0x1) << 24)
#define   G_000044_VIPH_INT(x)                         (((x) >> 24) & 0x1)
#define   C_000044_VIPH_INT                            0xFEFFFFFF
#define   S_000044_SW_INT(x)                           (((x) & 0x1) << 25)
#define   G_000044_SW_INT(x)                           (((x) >> 25) & 0x1)
#define   C_000044_SW_INT                              0xFDFFFFFF
#define   S_000044_SW_INT_SET(x)                       (((x) & 0x1) << 26)
#define   G_000044_SW_INT_SET(x)                       (((x) >> 26) & 0x1)
#define   C_000044_SW_INT_SET                          0xFBFFFFFF
#define   S_000044_IDCT_INT_STAT(x)                    (((x) & 0x1) << 27)
#define   G_000044_IDCT_INT_STAT(x)                    (((x) >> 27) & 0x1)
#define   C_000044_IDCT_INT_STAT                       0xF7FFFFFF
#define   S_000044_GUIDMA_STAT(x)                      (((x) & 0x1) << 30)
#define   G_000044_GUIDMA_STAT(x)                      (((x) >> 30) & 0x1)
#define   C_000044_GUIDMA_STAT                         0xBFFFFFFF
#define   S_000044_VIDDMA_STAT(x)                      (((x) & 0x1) << 31)
#define   G_000044_VIDDMA_STAT(x)                      (((x) >> 31) & 0x1)
#define   C_000044_VIDDMA_STAT                         0x7FFFFFFF
#define W_00004C_BUS_CNTW                            0x00004C
#define   S_00004C_BUS_MASTEW_DIS(x)                   (((x) & 0x1) << 14)
#define   G_00004C_BUS_MASTEW_DIS(x)                   (((x) >> 14) & 0x1)
#define   C_00004C_BUS_MASTEW_DIS                      0xFFFFBFFF
#define   S_00004C_BUS_MSI_WEAWM(x)                    (((x) & 0x1) << 20)
#define   G_00004C_BUS_MSI_WEAWM(x)                    (((x) >> 20) & 0x1)
#define   C_00004C_BUS_MSI_WEAWM                       0xFFEFFFFF
#define W_000070_MC_IND_INDEX                        0x000070
#define   S_000070_MC_IND_ADDW(x)                      (((x) & 0xFFFF) << 0)
#define   G_000070_MC_IND_ADDW(x)                      (((x) >> 0) & 0xFFFF)
#define   C_000070_MC_IND_ADDW                         0xFFFF0000
#define   S_000070_MC_IND_SEQ_WBS_0(x)                 (((x) & 0x1) << 16)
#define   G_000070_MC_IND_SEQ_WBS_0(x)                 (((x) >> 16) & 0x1)
#define   C_000070_MC_IND_SEQ_WBS_0                    0xFFFEFFFF
#define   S_000070_MC_IND_SEQ_WBS_1(x)                 (((x) & 0x1) << 17)
#define   G_000070_MC_IND_SEQ_WBS_1(x)                 (((x) >> 17) & 0x1)
#define   C_000070_MC_IND_SEQ_WBS_1                    0xFFFDFFFF
#define   S_000070_MC_IND_SEQ_WBS_2(x)                 (((x) & 0x1) << 18)
#define   G_000070_MC_IND_SEQ_WBS_2(x)                 (((x) >> 18) & 0x1)
#define   C_000070_MC_IND_SEQ_WBS_2                    0xFFFBFFFF
#define   S_000070_MC_IND_SEQ_WBS_3(x)                 (((x) & 0x1) << 19)
#define   G_000070_MC_IND_SEQ_WBS_3(x)                 (((x) >> 19) & 0x1)
#define   C_000070_MC_IND_SEQ_WBS_3                    0xFFF7FFFF
#define   S_000070_MC_IND_AIC_WBS(x)                   (((x) & 0x1) << 20)
#define   G_000070_MC_IND_AIC_WBS(x)                   (((x) >> 20) & 0x1)
#define   C_000070_MC_IND_AIC_WBS                      0xFFEFFFFF
#define   S_000070_MC_IND_CITF_AWB0(x)                 (((x) & 0x1) << 21)
#define   G_000070_MC_IND_CITF_AWB0(x)                 (((x) >> 21) & 0x1)
#define   C_000070_MC_IND_CITF_AWB0                    0xFFDFFFFF
#define   S_000070_MC_IND_CITF_AWB1(x)                 (((x) & 0x1) << 22)
#define   G_000070_MC_IND_CITF_AWB1(x)                 (((x) >> 22) & 0x1)
#define   C_000070_MC_IND_CITF_AWB1                    0xFFBFFFFF
#define   S_000070_MC_IND_WW_EN(x)                     (((x) & 0x1) << 23)
#define   G_000070_MC_IND_WW_EN(x)                     (((x) >> 23) & 0x1)
#define   C_000070_MC_IND_WW_EN                        0xFF7FFFFF
#define   S_000070_MC_IND_WD_INV(x)                    (((x) & 0x1) << 24)
#define   G_000070_MC_IND_WD_INV(x)                    (((x) >> 24) & 0x1)
#define   C_000070_MC_IND_WD_INV                       0xFEFFFFFF
#define W_000074_MC_IND_DATA                         0x000074
#define   S_000074_MC_IND_DATA(x)                      (((x) & 0xFFFFFFFF) << 0)
#define   G_000074_MC_IND_DATA(x)                      (((x) >> 0) & 0xFFFFFFFF)
#define   C_000074_MC_IND_DATA                         0x00000000
#define W_0000F0_WBBM_SOFT_WESET                     0x0000F0
#define   S_0000F0_SOFT_WESET_CP(x)                    (((x) & 0x1) << 0)
#define   G_0000F0_SOFT_WESET_CP(x)                    (((x) >> 0) & 0x1)
#define   C_0000F0_SOFT_WESET_CP                       0xFFFFFFFE
#define   S_0000F0_SOFT_WESET_HI(x)                    (((x) & 0x1) << 1)
#define   G_0000F0_SOFT_WESET_HI(x)                    (((x) >> 1) & 0x1)
#define   C_0000F0_SOFT_WESET_HI                       0xFFFFFFFD
#define   S_0000F0_SOFT_WESET_VAP(x)                   (((x) & 0x1) << 2)
#define   G_0000F0_SOFT_WESET_VAP(x)                   (((x) >> 2) & 0x1)
#define   C_0000F0_SOFT_WESET_VAP                      0xFFFFFFFB
#define   S_0000F0_SOFT_WESET_WE(x)                    (((x) & 0x1) << 3)
#define   G_0000F0_SOFT_WESET_WE(x)                    (((x) >> 3) & 0x1)
#define   C_0000F0_SOFT_WESET_WE                       0xFFFFFFF7
#define   S_0000F0_SOFT_WESET_PP(x)                    (((x) & 0x1) << 4)
#define   G_0000F0_SOFT_WESET_PP(x)                    (((x) >> 4) & 0x1)
#define   C_0000F0_SOFT_WESET_PP                       0xFFFFFFEF
#define   S_0000F0_SOFT_WESET_E2(x)                    (((x) & 0x1) << 5)
#define   G_0000F0_SOFT_WESET_E2(x)                    (((x) >> 5) & 0x1)
#define   C_0000F0_SOFT_WESET_E2                       0xFFFFFFDF
#define   S_0000F0_SOFT_WESET_WB(x)                    (((x) & 0x1) << 6)
#define   G_0000F0_SOFT_WESET_WB(x)                    (((x) >> 6) & 0x1)
#define   C_0000F0_SOFT_WESET_WB                       0xFFFFFFBF
#define   S_0000F0_SOFT_WESET_HDP(x)                   (((x) & 0x1) << 7)
#define   G_0000F0_SOFT_WESET_HDP(x)                   (((x) >> 7) & 0x1)
#define   C_0000F0_SOFT_WESET_HDP                      0xFFFFFF7F
#define   S_0000F0_SOFT_WESET_MC(x)                    (((x) & 0x1) << 8)
#define   G_0000F0_SOFT_WESET_MC(x)                    (((x) >> 8) & 0x1)
#define   C_0000F0_SOFT_WESET_MC                       0xFFFFFEFF
#define   S_0000F0_SOFT_WESET_AIC(x)                   (((x) & 0x1) << 9)
#define   G_0000F0_SOFT_WESET_AIC(x)                   (((x) >> 9) & 0x1)
#define   C_0000F0_SOFT_WESET_AIC                      0xFFFFFDFF
#define   S_0000F0_SOFT_WESET_VIP(x)                   (((x) & 0x1) << 10)
#define   G_0000F0_SOFT_WESET_VIP(x)                   (((x) >> 10) & 0x1)
#define   C_0000F0_SOFT_WESET_VIP                      0xFFFFFBFF
#define   S_0000F0_SOFT_WESET_DISP(x)                  (((x) & 0x1) << 11)
#define   G_0000F0_SOFT_WESET_DISP(x)                  (((x) >> 11) & 0x1)
#define   C_0000F0_SOFT_WESET_DISP                     0xFFFFF7FF
#define   S_0000F0_SOFT_WESET_CG(x)                    (((x) & 0x1) << 12)
#define   G_0000F0_SOFT_WESET_CG(x)                    (((x) >> 12) & 0x1)
#define   C_0000F0_SOFT_WESET_CG                       0xFFFFEFFF
#define   S_0000F0_SOFT_WESET_GA(x)                    (((x) & 0x1) << 13)
#define   G_0000F0_SOFT_WESET_GA(x)                    (((x) >> 13) & 0x1)
#define   C_0000F0_SOFT_WESET_GA                       0xFFFFDFFF
#define   S_0000F0_SOFT_WESET_IDCT(x)                  (((x) & 0x1) << 14)
#define   G_0000F0_SOFT_WESET_IDCT(x)                  (((x) >> 14) & 0x1)
#define   C_0000F0_SOFT_WESET_IDCT                     0xFFFFBFFF
#define W_000134_HDP_FB_WOCATION                     0x000134
#define   S_000134_HDP_FB_STAWT(x)                     (((x) & 0xFFFF) << 0)
#define   G_000134_HDP_FB_STAWT(x)                     (((x) >> 0) & 0xFFFF)
#define   C_000134_HDP_FB_STAWT                        0xFFFF0000
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
#define W_0060A4_D1CWTC_STATUS_FWAME_COUNT           0x0060A4
#define   S_0060A4_D1CWTC_FWAME_COUNT(x)               (((x) & 0xFFFFFF) << 0)
#define   G_0060A4_D1CWTC_FWAME_COUNT(x)               (((x) >> 0) & 0xFFFFFF)
#define   C_0060A4_D1CWTC_FWAME_COUNT                  0xFF000000
#define W_006534_D1MODE_VBWANK_STATUS                0x006534
#define   S_006534_D1MODE_VBWANK_OCCUWWED(x)           (((x) & 0x1) << 0)
#define   G_006534_D1MODE_VBWANK_OCCUWWED(x)           (((x) >> 0) & 0x1)
#define   C_006534_D1MODE_VBWANK_OCCUWWED              0xFFFFFFFE
#define   S_006534_D1MODE_VBWANK_ACK(x)                (((x) & 0x1) << 4)
#define   G_006534_D1MODE_VBWANK_ACK(x)                (((x) >> 4) & 0x1)
#define   C_006534_D1MODE_VBWANK_ACK                   0xFFFFFFEF
#define   S_006534_D1MODE_VBWANK_STAT(x)               (((x) & 0x1) << 12)
#define   G_006534_D1MODE_VBWANK_STAT(x)               (((x) >> 12) & 0x1)
#define   C_006534_D1MODE_VBWANK_STAT                  0xFFFFEFFF
#define   S_006534_D1MODE_VBWANK_INTEWWUPT(x)          (((x) & 0x1) << 16)
#define   G_006534_D1MODE_VBWANK_INTEWWUPT(x)          (((x) >> 16) & 0x1)
#define   C_006534_D1MODE_VBWANK_INTEWWUPT             0xFFFEFFFF
#define W_006540_DxMODE_INT_MASK                     0x006540
#define   S_006540_D1MODE_VBWANK_INT_MASK(x)           (((x) & 0x1) << 0)
#define   G_006540_D1MODE_VBWANK_INT_MASK(x)           (((x) >> 0) & 0x1)
#define   C_006540_D1MODE_VBWANK_INT_MASK              0xFFFFFFFE
#define   S_006540_D1MODE_VWINE_INT_MASK(x)            (((x) & 0x1) << 4)
#define   G_006540_D1MODE_VWINE_INT_MASK(x)            (((x) >> 4) & 0x1)
#define   C_006540_D1MODE_VWINE_INT_MASK               0xFFFFFFEF
#define   S_006540_D2MODE_VBWANK_INT_MASK(x)           (((x) & 0x1) << 8)
#define   G_006540_D2MODE_VBWANK_INT_MASK(x)           (((x) >> 8) & 0x1)
#define   C_006540_D2MODE_VBWANK_INT_MASK              0xFFFFFEFF
#define   S_006540_D2MODE_VWINE_INT_MASK(x)            (((x) & 0x1) << 12)
#define   G_006540_D2MODE_VWINE_INT_MASK(x)            (((x) >> 12) & 0x1)
#define   C_006540_D2MODE_VWINE_INT_MASK               0xFFFFEFFF
#define   S_006540_D1MODE_VBWANK_CP_SEW(x)             (((x) & 0x1) << 30)
#define   G_006540_D1MODE_VBWANK_CP_SEW(x)             (((x) >> 30) & 0x1)
#define   C_006540_D1MODE_VBWANK_CP_SEW                0xBFFFFFFF
#define   S_006540_D2MODE_VBWANK_CP_SEW(x)             (((x) & 0x1) << 31)
#define   G_006540_D2MODE_VBWANK_CP_SEW(x)             (((x) >> 31) & 0x1)
#define   C_006540_D2MODE_VBWANK_CP_SEW                0x7FFFFFFF
#define W_0068A4_D2CWTC_STATUS_FWAME_COUNT           0x0068A4
#define   S_0068A4_D2CWTC_FWAME_COUNT(x)               (((x) & 0xFFFFFF) << 0)
#define   G_0068A4_D2CWTC_FWAME_COUNT(x)               (((x) >> 0) & 0xFFFFFF)
#define   C_0068A4_D2CWTC_FWAME_COUNT                  0xFF000000
#define W_006D34_D2MODE_VBWANK_STATUS                0x006D34
#define   S_006D34_D2MODE_VBWANK_OCCUWWED(x)           (((x) & 0x1) << 0)
#define   G_006D34_D2MODE_VBWANK_OCCUWWED(x)           (((x) >> 0) & 0x1)
#define   C_006D34_D2MODE_VBWANK_OCCUWWED              0xFFFFFFFE
#define   S_006D34_D2MODE_VBWANK_ACK(x)                (((x) & 0x1) << 4)
#define   G_006D34_D2MODE_VBWANK_ACK(x)                (((x) >> 4) & 0x1)
#define   C_006D34_D2MODE_VBWANK_ACK                   0xFFFFFFEF
#define   S_006D34_D2MODE_VBWANK_STAT(x)               (((x) & 0x1) << 12)
#define   G_006D34_D2MODE_VBWANK_STAT(x)               (((x) >> 12) & 0x1)
#define   C_006D34_D2MODE_VBWANK_STAT                  0xFFFFEFFF
#define   S_006D34_D2MODE_VBWANK_INTEWWUPT(x)          (((x) & 0x1) << 16)
#define   G_006D34_D2MODE_VBWANK_INTEWWUPT(x)          (((x) >> 16) & 0x1)
#define   C_006D34_D2MODE_VBWANK_INTEWWUPT             0xFFFEFFFF
#define W_007EDC_DISP_INTEWWUPT_STATUS               0x007EDC
#define   S_007EDC_WB_D1_VBWANK_INTEWWUPT(x)           (((x) & 0x1) << 4)
#define   G_007EDC_WB_D1_VBWANK_INTEWWUPT(x)           (((x) >> 4) & 0x1)
#define   C_007EDC_WB_D1_VBWANK_INTEWWUPT              0xFFFFFFEF
#define   S_007EDC_WB_D2_VBWANK_INTEWWUPT(x)           (((x) & 0x1) << 5)
#define   G_007EDC_WB_D2_VBWANK_INTEWWUPT(x)           (((x) >> 5) & 0x1)
#define   C_007EDC_WB_D2_VBWANK_INTEWWUPT              0xFFFFFFDF
#define   S_007EDC_DACA_AUTODETECT_INTEWWUPT(x)        (((x) & 0x1) << 16)
#define   G_007EDC_DACA_AUTODETECT_INTEWWUPT(x)        (((x) >> 16) & 0x1)
#define   C_007EDC_DACA_AUTODETECT_INTEWWUPT           0xFFFEFFFF
#define   S_007EDC_DACB_AUTODETECT_INTEWWUPT(x)        (((x) & 0x1) << 17)
#define   G_007EDC_DACB_AUTODETECT_INTEWWUPT(x)        (((x) >> 17) & 0x1)
#define   C_007EDC_DACB_AUTODETECT_INTEWWUPT           0xFFFDFFFF
#define   S_007EDC_DC_HOT_PWUG_DETECT1_INTEWWUPT(x)    (((x) & 0x1) << 18)
#define   G_007EDC_DC_HOT_PWUG_DETECT1_INTEWWUPT(x)    (((x) >> 18) & 0x1)
#define   C_007EDC_DC_HOT_PWUG_DETECT1_INTEWWUPT       0xFFFBFFFF
#define   S_007EDC_DC_HOT_PWUG_DETECT2_INTEWWUPT(x)    (((x) & 0x1) << 19)
#define   G_007EDC_DC_HOT_PWUG_DETECT2_INTEWWUPT(x)    (((x) >> 19) & 0x1)
#define   C_007EDC_DC_HOT_PWUG_DETECT2_INTEWWUPT       0xFFF7FFFF
#define W_007828_DACA_AUTODETECT_CONTWOW               0x007828
#define   S_007828_DACA_AUTODETECT_MODE(x)             (((x) & 0x3) << 0)
#define   G_007828_DACA_AUTODETECT_MODE(x)             (((x) >> 0) & 0x3)
#define   C_007828_DACA_AUTODETECT_MODE                0xFFFFFFFC
#define   S_007828_DACA_AUTODETECT_FWAME_TIME_COUNTEW(x) (((x) & 0xff) << 8)
#define   G_007828_DACA_AUTODETECT_FWAME_TIME_COUNTEW(x) (((x) >> 8) & 0xff)
#define   C_007828_DACA_AUTODETECT_FWAME_TIME_COUNTEW  0xFFFF00FF
#define   S_007828_DACA_AUTODETECT_CHECK_MASK(x)       (((x) & 0x3) << 16)
#define   G_007828_DACA_AUTODETECT_CHECK_MASK(x)       (((x) >> 16) & 0x3)
#define   C_007828_DACA_AUTODETECT_CHECK_MASK          0xFFFCFFFF
#define W_007838_DACA_AUTODETECT_INT_CONTWOW           0x007838
#define   S_007838_DACA_AUTODETECT_ACK(x)              (((x) & 0x1) << 0)
#define   C_007838_DACA_DACA_AUTODETECT_ACK            0xFFFFFFFE
#define   S_007838_DACA_AUTODETECT_INT_ENABWE(x)       (((x) & 0x1) << 16)
#define   G_007838_DACA_AUTODETECT_INT_ENABWE(x)       (((x) >> 16) & 0x1)
#define   C_007838_DACA_AUTODETECT_INT_ENABWE          0xFFFCFFFF
#define W_007A28_DACB_AUTODETECT_CONTWOW               0x007A28
#define   S_007A28_DACB_AUTODETECT_MODE(x)             (((x) & 0x3) << 0)
#define   G_007A28_DACB_AUTODETECT_MODE(x)             (((x) >> 0) & 0x3)
#define   C_007A28_DACB_AUTODETECT_MODE                0xFFFFFFFC
#define   S_007A28_DACB_AUTODETECT_FWAME_TIME_COUNTEW(x) (((x) & 0xff) << 8)
#define   G_007A28_DACB_AUTODETECT_FWAME_TIME_COUNTEW(x) (((x) >> 8) & 0xff)
#define   C_007A28_DACB_AUTODETECT_FWAME_TIME_COUNTEW  0xFFFF00FF
#define   S_007A28_DACB_AUTODETECT_CHECK_MASK(x)       (((x) & 0x3) << 16)
#define   G_007A28_DACB_AUTODETECT_CHECK_MASK(x)       (((x) >> 16) & 0x3)
#define   C_007A28_DACB_AUTODETECT_CHECK_MASK          0xFFFCFFFF
#define W_007A38_DACB_AUTODETECT_INT_CONTWOW           0x007A38
#define   S_007A38_DACB_AUTODETECT_ACK(x)              (((x) & 0x1) << 0)
#define   C_007A38_DACB_DACA_AUTODETECT_ACK            0xFFFFFFFE
#define   S_007A38_DACB_AUTODETECT_INT_ENABWE(x)       (((x) & 0x1) << 16)
#define   G_007A38_DACB_AUTODETECT_INT_ENABWE(x)       (((x) >> 16) & 0x1)
#define   C_007A38_DACB_AUTODETECT_INT_ENABWE          0xFFFCFFFF
#define W_007D00_DC_HOT_PWUG_DETECT1_CONTWOW           0x007D00
#define   S_007D00_DC_HOT_PWUG_DETECT1_EN(x)           (((x) & 0x1) << 0)
#define   G_007D00_DC_HOT_PWUG_DETECT1_EN(x)           (((x) >> 0) & 0x1)
#define   C_007D00_DC_HOT_PWUG_DETECT1_EN              0xFFFFFFFE
#define W_007D04_DC_HOT_PWUG_DETECT1_INT_STATUS        0x007D04
#define   S_007D04_DC_HOT_PWUG_DETECT1_INT_STATUS(x)   (((x) & 0x1) << 0)
#define   G_007D04_DC_HOT_PWUG_DETECT1_INT_STATUS(x)   (((x) >> 0) & 0x1)
#define   C_007D04_DC_HOT_PWUG_DETECT1_INT_STATUS      0xFFFFFFFE
#define   S_007D04_DC_HOT_PWUG_DETECT1_SENSE(x)        (((x) & 0x1) << 1)
#define   G_007D04_DC_HOT_PWUG_DETECT1_SENSE(x)        (((x) >> 1) & 0x1)
#define   C_007D04_DC_HOT_PWUG_DETECT1_SENSE           0xFFFFFFFD
#define W_007D08_DC_HOT_PWUG_DETECT1_INT_CONTWOW       0x007D08
#define   S_007D08_DC_HOT_PWUG_DETECT1_INT_ACK(x)      (((x) & 0x1) << 0)
#define   C_007D08_DC_HOT_PWUG_DETECT1_INT_ACK         0xFFFFFFFE
#define   S_007D08_DC_HOT_PWUG_DETECT1_INT_POWAWITY(x) (((x) & 0x1) << 8)
#define   G_007D08_DC_HOT_PWUG_DETECT1_INT_POWAWITY(x) (((x) >> 8) & 0x1)
#define   C_007D08_DC_HOT_PWUG_DETECT1_INT_POWAWITY    0xFFFFFEFF
#define   S_007D08_DC_HOT_PWUG_DETECT1_INT_EN(x)       (((x) & 0x1) << 16)
#define   G_007D08_DC_HOT_PWUG_DETECT1_INT_EN(x)       (((x) >> 16) & 0x1)
#define   C_007D08_DC_HOT_PWUG_DETECT1_INT_EN          0xFFFEFFFF
#define W_007D10_DC_HOT_PWUG_DETECT2_CONTWOW           0x007D10
#define   S_007D10_DC_HOT_PWUG_DETECT2_EN(x)           (((x) & 0x1) << 0)
#define   G_007D10_DC_HOT_PWUG_DETECT2_EN(x)           (((x) >> 0) & 0x1)
#define   C_007D10_DC_HOT_PWUG_DETECT2_EN              0xFFFFFFFE
#define W_007D14_DC_HOT_PWUG_DETECT2_INT_STATUS        0x007D14
#define   S_007D14_DC_HOT_PWUG_DETECT2_INT_STATUS(x)   (((x) & 0x1) << 0)
#define   G_007D14_DC_HOT_PWUG_DETECT2_INT_STATUS(x)   (((x) >> 0) & 0x1)
#define   C_007D14_DC_HOT_PWUG_DETECT2_INT_STATUS      0xFFFFFFFE
#define   S_007D14_DC_HOT_PWUG_DETECT2_SENSE(x)        (((x) & 0x1) << 1)
#define   G_007D14_DC_HOT_PWUG_DETECT2_SENSE(x)        (((x) >> 1) & 0x1)
#define   C_007D14_DC_HOT_PWUG_DETECT2_SENSE           0xFFFFFFFD
#define W_007D18_DC_HOT_PWUG_DETECT2_INT_CONTWOW       0x007D18
#define   S_007D18_DC_HOT_PWUG_DETECT2_INT_ACK(x)      (((x) & 0x1) << 0)
#define   C_007D18_DC_HOT_PWUG_DETECT2_INT_ACK         0xFFFFFFFE
#define   S_007D18_DC_HOT_PWUG_DETECT2_INT_POWAWITY(x) (((x) & 0x1) << 8)
#define   G_007D18_DC_HOT_PWUG_DETECT2_INT_POWAWITY(x) (((x) >> 8) & 0x1)
#define   C_007D18_DC_HOT_PWUG_DETECT2_INT_POWAWITY    0xFFFFFEFF
#define   S_007D18_DC_HOT_PWUG_DETECT2_INT_EN(x)       (((x) & 0x1) << 16)
#define   G_007D18_DC_HOT_PWUG_DETECT2_INT_EN(x)       (((x) >> 16) & 0x1)
#define   C_007D18_DC_HOT_PWUG_DETECT2_INT_EN          0xFFFEFFFF
#define W_007404_HDMI0_STATUS                          0x007404
#define   S_007404_HDMI0_AZ_FOWMAT_WTWIG(x)            (((x) & 0x1) << 28)
#define   G_007404_HDMI0_AZ_FOWMAT_WTWIG(x)            (((x) >> 28) & 0x1)
#define   C_007404_HDMI0_AZ_FOWMAT_WTWIG               0xEFFFFFFF
#define   S_007404_HDMI0_AZ_FOWMAT_WTWIG_INT(x)        (((x) & 0x1) << 29)
#define   G_007404_HDMI0_AZ_FOWMAT_WTWIG_INT(x)        (((x) >> 29) & 0x1)
#define   C_007404_HDMI0_AZ_FOWMAT_WTWIG_INT           0xDFFFFFFF
#define W_007408_HDMI0_AUDIO_PACKET_CONTWOW            0x007408
#define   S_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK(x)       (((x) & 0x1) << 28)
#define   G_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK(x)       (((x) >> 28) & 0x1)
#define   C_007408_HDMI0_AZ_FOWMAT_WTWIG_MASK          0xEFFFFFFF
#define   S_007408_HDMI0_AZ_FOWMAT_WTWIG_ACK(x)        (((x) & 0x1) << 29)
#define   G_007408_HDMI0_AZ_FOWMAT_WTWIG_ACK(x)        (((x) >> 29) & 0x1)
#define   C_007408_HDMI0_AZ_FOWMAT_WTWIG_ACK           0xDFFFFFFF

/* MC wegistews */
#define W_000000_MC_STATUS                           0x000000
#define   S_000000_MC_IDWE(x)                          (((x) & 0x1) << 0)
#define   G_000000_MC_IDWE(x)                          (((x) >> 0) & 0x1)
#define   C_000000_MC_IDWE                             0xFFFFFFFE
#define W_000004_MC_FB_WOCATION                      0x000004
#define   S_000004_MC_FB_STAWT(x)                      (((x) & 0xFFFF) << 0)
#define   G_000004_MC_FB_STAWT(x)                      (((x) >> 0) & 0xFFFF)
#define   C_000004_MC_FB_STAWT                         0xFFFF0000
#define   S_000004_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#define   G_000004_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#define   C_000004_MC_FB_TOP                           0x0000FFFF
#define W_000005_MC_AGP_WOCATION                     0x000005
#define   S_000005_MC_AGP_STAWT(x)                     (((x) & 0xFFFF) << 0)
#define   G_000005_MC_AGP_STAWT(x)                     (((x) >> 0) & 0xFFFF)
#define   C_000005_MC_AGP_STAWT                        0xFFFF0000
#define   S_000005_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#define   G_000005_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#define   C_000005_MC_AGP_TOP                          0x0000FFFF
#define W_000006_AGP_BASE                            0x000006
#define   S_000006_AGP_BASE_ADDW(x)                    (((x) & 0xFFFFFFFF) << 0)
#define   G_000006_AGP_BASE_ADDW(x)                    (((x) >> 0) & 0xFFFFFFFF)
#define   C_000006_AGP_BASE_ADDW                       0x00000000
#define W_000007_AGP_BASE_2                          0x000007
#define   S_000007_AGP_BASE_ADDW_2(x)                  (((x) & 0xF) << 0)
#define   G_000007_AGP_BASE_ADDW_2(x)                  (((x) >> 0) & 0xF)
#define   C_000007_AGP_BASE_ADDW_2                     0xFFFFFFF0
#define W_000009_MC_CNTW1                            0x000009
#define   S_000009_ENABWE_PAGE_TABWES(x)               (((x) & 0x1) << 26)
#define   G_000009_ENABWE_PAGE_TABWES(x)               (((x) >> 26) & 0x1)
#define   C_000009_ENABWE_PAGE_TABWES                  0xFBFFFFFF
/* FIXME don't know the vawious fiewd size need feedback fwom AMD */
#define W_000100_MC_PT0_CNTW                         0x000100
#define   S_000100_ENABWE_PT(x)                        (((x) & 0x1) << 0)
#define   G_000100_ENABWE_PT(x)                        (((x) >> 0) & 0x1)
#define   C_000100_ENABWE_PT                           0xFFFFFFFE
#define   S_000100_EFFECTIVE_W2_CACHE_SIZE(x)          (((x) & 0x7) << 15)
#define   G_000100_EFFECTIVE_W2_CACHE_SIZE(x)          (((x) >> 15) & 0x7)
#define   C_000100_EFFECTIVE_W2_CACHE_SIZE             0xFFFC7FFF
#define   S_000100_EFFECTIVE_W2_QUEUE_SIZE(x)          (((x) & 0x7) << 21)
#define   G_000100_EFFECTIVE_W2_QUEUE_SIZE(x)          (((x) >> 21) & 0x7)
#define   C_000100_EFFECTIVE_W2_QUEUE_SIZE             0xFF1FFFFF
#define   S_000100_INVAWIDATE_AWW_W1_TWBS(x)           (((x) & 0x1) << 28)
#define   G_000100_INVAWIDATE_AWW_W1_TWBS(x)           (((x) >> 28) & 0x1)
#define   C_000100_INVAWIDATE_AWW_W1_TWBS              0xEFFFFFFF
#define   S_000100_INVAWIDATE_W2_CACHE(x)              (((x) & 0x1) << 29)
#define   G_000100_INVAWIDATE_W2_CACHE(x)              (((x) >> 29) & 0x1)
#define   C_000100_INVAWIDATE_W2_CACHE                 0xDFFFFFFF
#define W_000102_MC_PT0_CONTEXT0_CNTW                0x000102
#define   S_000102_ENABWE_PAGE_TABWE(x)                (((x) & 0x1) << 0)
#define   G_000102_ENABWE_PAGE_TABWE(x)                (((x) >> 0) & 0x1)
#define   C_000102_ENABWE_PAGE_TABWE                   0xFFFFFFFE
#define   S_000102_PAGE_TABWE_DEPTH(x)                 (((x) & 0x3) << 1)
#define   G_000102_PAGE_TABWE_DEPTH(x)                 (((x) >> 1) & 0x3)
#define   C_000102_PAGE_TABWE_DEPTH                    0xFFFFFFF9
#define   V_000102_PAGE_TABWE_FWAT                     0
/* W600 documentation suggest that this shouwd be a numbew of pages */
#define W_000112_MC_PT0_SYSTEM_APEWTUWE_WOW_ADDW     0x000112
#define W_000114_MC_PT0_SYSTEM_APEWTUWE_HIGH_ADDW    0x000114
#define W_00011C_MC_PT0_CONTEXT0_DEFAUWT_WEAD_ADDW   0x00011C
#define W_00012C_MC_PT0_CONTEXT0_FWAT_BASE_ADDW      0x00012C
#define W_00013C_MC_PT0_CONTEXT0_FWAT_STAWT_ADDW     0x00013C
#define W_00014C_MC_PT0_CONTEXT0_FWAT_END_ADDW       0x00014C
#define W_00016C_MC_PT0_CWIENT0_CNTW                 0x00016C
#define   S_00016C_ENABWE_TWANSWATION_MODE_OVEWWIDE(x) (((x) & 0x1) << 0)
#define   G_00016C_ENABWE_TWANSWATION_MODE_OVEWWIDE(x) (((x) >> 0) & 0x1)
#define   C_00016C_ENABWE_TWANSWATION_MODE_OVEWWIDE    0xFFFFFFFE
#define   S_00016C_TWANSWATION_MODE_OVEWWIDE(x)        (((x) & 0x1) << 1)
#define   G_00016C_TWANSWATION_MODE_OVEWWIDE(x)        (((x) >> 1) & 0x1)
#define   C_00016C_TWANSWATION_MODE_OVEWWIDE           0xFFFFFFFD
#define   S_00016C_SYSTEM_ACCESS_MODE_MASK(x)          (((x) & 0x3) << 8)
#define   G_00016C_SYSTEM_ACCESS_MODE_MASK(x)          (((x) >> 8) & 0x3)
#define   C_00016C_SYSTEM_ACCESS_MODE_MASK             0xFFFFFCFF
#define   V_00016C_SYSTEM_ACCESS_MODE_PA_ONWY          0
#define   V_00016C_SYSTEM_ACCESS_MODE_USE_SYS_MAP      1
#define   V_00016C_SYSTEM_ACCESS_MODE_IN_SYS           2
#define   V_00016C_SYSTEM_ACCESS_MODE_NOT_IN_SYS       3
#define   S_00016C_SYSTEM_APEWTUWE_UNMAPPED_ACCESS(x)  (((x) & 0x1) << 10)
#define   G_00016C_SYSTEM_APEWTUWE_UNMAPPED_ACCESS(x)  (((x) >> 10) & 0x1)
#define   C_00016C_SYSTEM_APEWTUWE_UNMAPPED_ACCESS     0xFFFFFBFF
#define   V_00016C_SYSTEM_APEWTUWE_UNMAPPED_PASSTHWOUGH  0
#define   V_00016C_SYSTEM_APEWTUWE_UNMAPPED_DEFAUWT_PAGE 1
#define   S_00016C_EFFECTIVE_W1_CACHE_SIZE(x)          (((x) & 0x7) << 11)
#define   G_00016C_EFFECTIVE_W1_CACHE_SIZE(x)          (((x) >> 11) & 0x7)
#define   C_00016C_EFFECTIVE_W1_CACHE_SIZE             0xFFFFC7FF
#define   S_00016C_ENABWE_FWAGMENT_PWOCESSING(x)       (((x) & 0x1) << 14)
#define   G_00016C_ENABWE_FWAGMENT_PWOCESSING(x)       (((x) >> 14) & 0x1)
#define   C_00016C_ENABWE_FWAGMENT_PWOCESSING          0xFFFFBFFF
#define   S_00016C_EFFECTIVE_W1_QUEUE_SIZE(x)          (((x) & 0x7) << 15)
#define   G_00016C_EFFECTIVE_W1_QUEUE_SIZE(x)          (((x) >> 15) & 0x7)
#define   C_00016C_EFFECTIVE_W1_QUEUE_SIZE             0xFFFC7FFF
#define   S_00016C_INVAWIDATE_W1_TWB(x)                (((x) & 0x1) << 20)
#define   G_00016C_INVAWIDATE_W1_TWB(x)                (((x) >> 20) & 0x1)
#define   C_00016C_INVAWIDATE_W1_TWB                   0xFFEFFFFF

#define W_006548_D1MODE_PWIOWITY_A_CNT               0x006548
#define   S_006548_D1MODE_PWIOWITY_MAWK_A(x)           (((x) & 0x7FFF) << 0)
#define   G_006548_D1MODE_PWIOWITY_MAWK_A(x)           (((x) >> 0) & 0x7FFF)
#define   C_006548_D1MODE_PWIOWITY_MAWK_A              0xFFFF8000
#define   S_006548_D1MODE_PWIOWITY_A_OFF(x)            (((x) & 0x1) << 16)
#define   G_006548_D1MODE_PWIOWITY_A_OFF(x)            (((x) >> 16) & 0x1)
#define   C_006548_D1MODE_PWIOWITY_A_OFF               0xFFFEFFFF
#define   S_006548_D1MODE_PWIOWITY_A_AWWAYS_ON(x)      (((x) & 0x1) << 20)
#define   G_006548_D1MODE_PWIOWITY_A_AWWAYS_ON(x)      (((x) >> 20) & 0x1)
#define   C_006548_D1MODE_PWIOWITY_A_AWWAYS_ON         0xFFEFFFFF
#define   S_006548_D1MODE_PWIOWITY_A_FOWCE_MASK(x)     (((x) & 0x1) << 24)
#define   G_006548_D1MODE_PWIOWITY_A_FOWCE_MASK(x)     (((x) >> 24) & 0x1)
#define   C_006548_D1MODE_PWIOWITY_A_FOWCE_MASK        0xFEFFFFFF
#define W_00654C_D1MODE_PWIOWITY_B_CNT               0x00654C
#define   S_00654C_D1MODE_PWIOWITY_MAWK_B(x)           (((x) & 0x7FFF) << 0)
#define   G_00654C_D1MODE_PWIOWITY_MAWK_B(x)           (((x) >> 0) & 0x7FFF)
#define   C_00654C_D1MODE_PWIOWITY_MAWK_B              0xFFFF8000
#define   S_00654C_D1MODE_PWIOWITY_B_OFF(x)            (((x) & 0x1) << 16)
#define   G_00654C_D1MODE_PWIOWITY_B_OFF(x)            (((x) >> 16) & 0x1)
#define   C_00654C_D1MODE_PWIOWITY_B_OFF               0xFFFEFFFF
#define   S_00654C_D1MODE_PWIOWITY_B_AWWAYS_ON(x)      (((x) & 0x1) << 20)
#define   G_00654C_D1MODE_PWIOWITY_B_AWWAYS_ON(x)      (((x) >> 20) & 0x1)
#define   C_00654C_D1MODE_PWIOWITY_B_AWWAYS_ON         0xFFEFFFFF
#define   S_00654C_D1MODE_PWIOWITY_B_FOWCE_MASK(x)     (((x) & 0x1) << 24)
#define   G_00654C_D1MODE_PWIOWITY_B_FOWCE_MASK(x)     (((x) >> 24) & 0x1)
#define   C_00654C_D1MODE_PWIOWITY_B_FOWCE_MASK        0xFEFFFFFF
#define W_006D48_D2MODE_PWIOWITY_A_CNT               0x006D48
#define   S_006D48_D2MODE_PWIOWITY_MAWK_A(x)           (((x) & 0x7FFF) << 0)
#define   G_006D48_D2MODE_PWIOWITY_MAWK_A(x)           (((x) >> 0) & 0x7FFF)
#define   C_006D48_D2MODE_PWIOWITY_MAWK_A              0xFFFF8000
#define   S_006D48_D2MODE_PWIOWITY_A_OFF(x)            (((x) & 0x1) << 16)
#define   G_006D48_D2MODE_PWIOWITY_A_OFF(x)            (((x) >> 16) & 0x1)
#define   C_006D48_D2MODE_PWIOWITY_A_OFF               0xFFFEFFFF
#define   S_006D48_D2MODE_PWIOWITY_A_AWWAYS_ON(x)      (((x) & 0x1) << 20)
#define   G_006D48_D2MODE_PWIOWITY_A_AWWAYS_ON(x)      (((x) >> 20) & 0x1)
#define   C_006D48_D2MODE_PWIOWITY_A_AWWAYS_ON         0xFFEFFFFF
#define   S_006D48_D2MODE_PWIOWITY_A_FOWCE_MASK(x)     (((x) & 0x1) << 24)
#define   G_006D48_D2MODE_PWIOWITY_A_FOWCE_MASK(x)     (((x) >> 24) & 0x1)
#define   C_006D48_D2MODE_PWIOWITY_A_FOWCE_MASK        0xFEFFFFFF
#define W_006D4C_D2MODE_PWIOWITY_B_CNT               0x006D4C
#define   S_006D4C_D2MODE_PWIOWITY_MAWK_B(x)           (((x) & 0x7FFF) << 0)
#define   G_006D4C_D2MODE_PWIOWITY_MAWK_B(x)           (((x) >> 0) & 0x7FFF)
#define   C_006D4C_D2MODE_PWIOWITY_MAWK_B              0xFFFF8000
#define   S_006D4C_D2MODE_PWIOWITY_B_OFF(x)            (((x) & 0x1) << 16)
#define   G_006D4C_D2MODE_PWIOWITY_B_OFF(x)            (((x) >> 16) & 0x1)
#define   C_006D4C_D2MODE_PWIOWITY_B_OFF               0xFFFEFFFF
#define   S_006D4C_D2MODE_PWIOWITY_B_AWWAYS_ON(x)      (((x) & 0x1) << 20)
#define   G_006D4C_D2MODE_PWIOWITY_B_AWWAYS_ON(x)      (((x) >> 20) & 0x1)
#define   C_006D4C_D2MODE_PWIOWITY_B_AWWAYS_ON         0xFFEFFFFF
#define   S_006D4C_D2MODE_PWIOWITY_B_FOWCE_MASK(x)     (((x) & 0x1) << 24)
#define   G_006D4C_D2MODE_PWIOWITY_B_FOWCE_MASK(x)     (((x) >> 24) & 0x1)
#define   C_006D4C_D2MODE_PWIOWITY_B_FOWCE_MASK        0xFEFFFFFF

/* PWW wegs */
#define GENEWAW_PWWMGT                                 0x8
#define   GWOBAW_PWWMGT_EN                             (1 << 0)
#define   MOBIWE_SU                                    (1 << 2)
#define DYN_PWWMGT_SCWK_WENGTH                         0xc
#define   NOWMAW_POWEW_SCWK_HIWEN(x)                   ((x) << 0)
#define   NOWMAW_POWEW_SCWK_WOWEN(x)                   ((x) << 4)
#define   WEDUCED_POWEW_SCWK_HIWEN(x)                  ((x) << 8)
#define   WEDUCED_POWEW_SCWK_WOWEN(x)                  ((x) << 12)
#define   POWEW_D1_SCWK_HIWEN(x)                       ((x) << 16)
#define   POWEW_D1_SCWK_WOWEN(x)                       ((x) << 20)
#define   STATIC_SCWEEN_HIWEN(x)                       ((x) << 24)
#define   STATIC_SCWEEN_WOWEN(x)                       ((x) << 28)
#define DYN_SCWK_VOW_CNTW                              0xe
#define   IO_CG_VOWTAGE_DWOP                           (1 << 0)
#define   VOWTAGE_DWOP_SYNC                            (1 << 2)
#define   VOWTAGE_DEWAY_SEW(x)                         ((x) << 3)
#define HDP_DYN_CNTW                                   0x10
#define   HDP_FOWCEON                                  (1 << 0)
#define MC_HOST_DYN_CNTW                               0x1e
#define   MC_HOST_FOWCEON                              (1 << 0)
#define DYN_BACKBIAS_CNTW                              0x29
#define   IO_CG_BACKBIAS_EN                            (1 << 0)

/* mmweg */
#define DOUT_POWEW_MANAGEMENT_CNTW                     0x7ee0
#define   PWWDN_WAIT_BUSY_OFF                          (1 << 0)
#define   PWWDN_WAIT_PWWSEQ_OFF                        (1 << 4)
#define   PWWDN_WAIT_PPWW_OFF                          (1 << 8)
#define   PWWUP_WAIT_PPWW_ON                           (1 << 12)
#define   PWWUP_WAIT_MEM_INIT_DONE                     (1 << 16)
#define   PM_ASSEWT_WESET                              (1 << 20)
#define   PM_PWWDN_PPWW                                (1 << 24)

#endif
