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
#ifndef __W100D_H__
#define __W100D_H__

#define CP_PACKET0			0x00000000
#define		PACKET0_BASE_INDEX_SHIFT	0
#define		PACKET0_BASE_INDEX_MASK		(0x1ffff << 0)
#define		PACKET0_COUNT_SHIFT		16
#define		PACKET0_COUNT_MASK		(0x3fff << 16)
#define CP_PACKET1			0x40000000
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)
#define CP_PACKET3			0xC0000000
#define		PACKET3_IT_OPCODE_SHIFT		8
#define		PACKET3_IT_OPCODE_MASK		(0xff << 8)
#define		PACKET3_COUNT_SHIFT		16
#define		PACKET3_COUNT_MASK		(0x3fff << 16)
/* PACKET3 op code */
#define		PACKET3_NOP			0x10
#define		PACKET3_3D_DWAW_VBUF		0x28
#define		PACKET3_3D_DWAW_IMMD		0x29
#define		PACKET3_3D_DWAW_INDX		0x2A
#define		PACKET3_3D_WOAD_VBPNTW		0x2F
#define		PACKET3_3D_CWEAW_ZMASK		0x32
#define		PACKET3_INDX_BUFFEW		0x33
#define		PACKET3_3D_DWAW_VBUF_2		0x34
#define		PACKET3_3D_DWAW_IMMD_2		0x35
#define		PACKET3_3D_DWAW_INDX_2		0x36
#define		PACKET3_3D_CWEAW_HIZ		0x37
#define		PACKET3_BITBWT_MUWTI		0x9B

#define PACKET0(weg, n)	(CP_PACKET0 |					\
			 WEG_SET(PACKET0_BASE_INDEX, (weg) >> 2) |	\
			 WEG_SET(PACKET0_COUNT, (n)))
#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))
#define PACKET3(op, n)	(CP_PACKET3 |					\
			 WEG_SET(PACKET3_IT_OPCODE, (op)) |		\
			 WEG_SET(PACKET3_COUNT, (n)))

/* Wegistews */
#define W_0000F0_WBBM_SOFT_WESET                     0x0000F0
#define   S_0000F0_SOFT_WESET_CP(x)                    (((x) & 0x1) << 0)
#define   G_0000F0_SOFT_WESET_CP(x)                    (((x) >> 0) & 0x1)
#define   C_0000F0_SOFT_WESET_CP                       0xFFFFFFFE
#define   S_0000F0_SOFT_WESET_HI(x)                    (((x) & 0x1) << 1)
#define   G_0000F0_SOFT_WESET_HI(x)                    (((x) >> 1) & 0x1)
#define   C_0000F0_SOFT_WESET_HI                       0xFFFFFFFD
#define   S_0000F0_SOFT_WESET_SE(x)                    (((x) & 0x1) << 2)
#define   G_0000F0_SOFT_WESET_SE(x)                    (((x) >> 2) & 0x1)
#define   C_0000F0_SOFT_WESET_SE                       0xFFFFFFFB
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
#define W_000030_BUS_CNTW                            0x000030
#define   S_000030_BUS_DBW_WESYNC(x)                   (((x) & 0x1) << 0)
#define   G_000030_BUS_DBW_WESYNC(x)                   (((x) >> 0) & 0x1)
#define   C_000030_BUS_DBW_WESYNC                      0xFFFFFFFE
#define   S_000030_BUS_MSTW_WESET(x)                   (((x) & 0x1) << 1)
#define   G_000030_BUS_MSTW_WESET(x)                   (((x) >> 1) & 0x1)
#define   C_000030_BUS_MSTW_WESET                      0xFFFFFFFD
#define   S_000030_BUS_FWUSH_BUF(x)                    (((x) & 0x1) << 2)
#define   G_000030_BUS_FWUSH_BUF(x)                    (((x) >> 2) & 0x1)
#define   C_000030_BUS_FWUSH_BUF                       0xFFFFFFFB
#define   S_000030_BUS_STOP_WEQ_DIS(x)                 (((x) & 0x1) << 3)
#define   G_000030_BUS_STOP_WEQ_DIS(x)                 (((x) >> 3) & 0x1)
#define   C_000030_BUS_STOP_WEQ_DIS                    0xFFFFFFF7
#define   S_000030_BUS_PM4_WEAD_COMBINE_EN(x)          (((x) & 0x1) << 4)
#define   G_000030_BUS_PM4_WEAD_COMBINE_EN(x)          (((x) >> 4) & 0x1)
#define   C_000030_BUS_PM4_WEAD_COMBINE_EN             0xFFFFFFEF
#define   S_000030_BUS_WWT_COMBINE_EN(x)               (((x) & 0x1) << 5)
#define   G_000030_BUS_WWT_COMBINE_EN(x)               (((x) >> 5) & 0x1)
#define   C_000030_BUS_WWT_COMBINE_EN                  0xFFFFFFDF
#define   S_000030_BUS_MASTEW_DIS(x)                   (((x) & 0x1) << 6)
#define   G_000030_BUS_MASTEW_DIS(x)                   (((x) >> 6) & 0x1)
#define   C_000030_BUS_MASTEW_DIS                      0xFFFFFFBF
#define   S_000030_BIOS_WOM_WWT_EN(x)                  (((x) & 0x1) << 7)
#define   G_000030_BIOS_WOM_WWT_EN(x)                  (((x) >> 7) & 0x1)
#define   C_000030_BIOS_WOM_WWT_EN                     0xFFFFFF7F
#define   S_000030_BM_DAC_CWIPPWE(x)                   (((x) & 0x1) << 8)
#define   G_000030_BM_DAC_CWIPPWE(x)                   (((x) >> 8) & 0x1)
#define   C_000030_BM_DAC_CWIPPWE                      0xFFFFFEFF
#define   S_000030_BUS_NON_PM4_WEAD_COMBINE_EN(x)      (((x) & 0x1) << 9)
#define   G_000030_BUS_NON_PM4_WEAD_COMBINE_EN(x)      (((x) >> 9) & 0x1)
#define   C_000030_BUS_NON_PM4_WEAD_COMBINE_EN         0xFFFFFDFF
#define   S_000030_BUS_XFEWD_DISCAWD_EN(x)             (((x) & 0x1) << 10)
#define   G_000030_BUS_XFEWD_DISCAWD_EN(x)             (((x) >> 10) & 0x1)
#define   C_000030_BUS_XFEWD_DISCAWD_EN                0xFFFFFBFF
#define   S_000030_BUS_SGW_WEAD_DISABWE(x)             (((x) & 0x1) << 11)
#define   G_000030_BUS_SGW_WEAD_DISABWE(x)             (((x) >> 11) & 0x1)
#define   C_000030_BUS_SGW_WEAD_DISABWE                0xFFFFF7FF
#define   S_000030_BIOS_DIS_WOM(x)                     (((x) & 0x1) << 12)
#define   G_000030_BIOS_DIS_WOM(x)                     (((x) >> 12) & 0x1)
#define   C_000030_BIOS_DIS_WOM                        0xFFFFEFFF
#define   S_000030_BUS_PCI_WEAD_WETWY_EN(x)            (((x) & 0x1) << 13)
#define   G_000030_BUS_PCI_WEAD_WETWY_EN(x)            (((x) >> 13) & 0x1)
#define   C_000030_BUS_PCI_WEAD_WETWY_EN               0xFFFFDFFF
#define   S_000030_BUS_AGP_AD_STEPPING_EN(x)           (((x) & 0x1) << 14)
#define   G_000030_BUS_AGP_AD_STEPPING_EN(x)           (((x) >> 14) & 0x1)
#define   C_000030_BUS_AGP_AD_STEPPING_EN              0xFFFFBFFF
#define   S_000030_BUS_PCI_WWT_WETWY_EN(x)             (((x) & 0x1) << 15)
#define   G_000030_BUS_PCI_WWT_WETWY_EN(x)             (((x) >> 15) & 0x1)
#define   C_000030_BUS_PCI_WWT_WETWY_EN                0xFFFF7FFF
#define   S_000030_BUS_WETWY_WS(x)                     (((x) & 0xF) << 16)
#define   G_000030_BUS_WETWY_WS(x)                     (((x) >> 16) & 0xF)
#define   C_000030_BUS_WETWY_WS                        0xFFF0FFFF
#define   S_000030_BUS_MSTW_WD_MUWT(x)                 (((x) & 0x1) << 20)
#define   G_000030_BUS_MSTW_WD_MUWT(x)                 (((x) >> 20) & 0x1)
#define   C_000030_BUS_MSTW_WD_MUWT                    0xFFEFFFFF
#define   S_000030_BUS_MSTW_WD_WINE(x)                 (((x) & 0x1) << 21)
#define   G_000030_BUS_MSTW_WD_WINE(x)                 (((x) >> 21) & 0x1)
#define   C_000030_BUS_MSTW_WD_WINE                    0xFFDFFFFF
#define   S_000030_BUS_SUSPEND(x)                      (((x) & 0x1) << 22)
#define   G_000030_BUS_SUSPEND(x)                      (((x) >> 22) & 0x1)
#define   C_000030_BUS_SUSPEND                         0xFFBFFFFF
#define   S_000030_WAT_16X(x)                          (((x) & 0x1) << 23)
#define   G_000030_WAT_16X(x)                          (((x) >> 23) & 0x1)
#define   C_000030_WAT_16X                             0xFF7FFFFF
#define   S_000030_BUS_WD_DISCAWD_EN(x)                (((x) & 0x1) << 24)
#define   G_000030_BUS_WD_DISCAWD_EN(x)                (((x) >> 24) & 0x1)
#define   C_000030_BUS_WD_DISCAWD_EN                   0xFEFFFFFF
#define   S_000030_ENFWCWWDY(x)                        (((x) & 0x1) << 25)
#define   G_000030_ENFWCWWDY(x)                        (((x) >> 25) & 0x1)
#define   C_000030_ENFWCWWDY                           0xFDFFFFFF
#define   S_000030_BUS_MSTW_WS(x)                      (((x) & 0x1) << 26)
#define   G_000030_BUS_MSTW_WS(x)                      (((x) >> 26) & 0x1)
#define   C_000030_BUS_MSTW_WS                         0xFBFFFFFF
#define   S_000030_BUS_PAWKING_DIS(x)                  (((x) & 0x1) << 27)
#define   G_000030_BUS_PAWKING_DIS(x)                  (((x) >> 27) & 0x1)
#define   C_000030_BUS_PAWKING_DIS                     0xF7FFFFFF
#define   S_000030_BUS_MSTW_DISCONNECT_EN(x)           (((x) & 0x1) << 28)
#define   G_000030_BUS_MSTW_DISCONNECT_EN(x)           (((x) >> 28) & 0x1)
#define   C_000030_BUS_MSTW_DISCONNECT_EN              0xEFFFFFFF
#define   S_000030_SEWW_EN(x)                          (((x) & 0x1) << 29)
#define   G_000030_SEWW_EN(x)                          (((x) >> 29) & 0x1)
#define   C_000030_SEWW_EN                             0xDFFFFFFF
#define   S_000030_BUS_WEAD_BUWST(x)                   (((x) & 0x1) << 30)
#define   G_000030_BUS_WEAD_BUWST(x)                   (((x) >> 30) & 0x1)
#define   C_000030_BUS_WEAD_BUWST                      0xBFFFFFFF
#define   S_000030_BUS_WDY_WEAD_DWY(x)                 (((x) & 0x1) << 31)
#define   G_000030_BUS_WDY_WEAD_DWY(x)                 (((x) >> 31) & 0x1)
#define   C_000030_BUS_WDY_WEAD_DWY                    0x7FFFFFFF
#define W_000040_GEN_INT_CNTW                        0x000040
#define   S_000040_CWTC_VBWANK(x)                      (((x) & 0x1) << 0)
#define   G_000040_CWTC_VBWANK(x)                      (((x) >> 0) & 0x1)
#define   C_000040_CWTC_VBWANK                         0xFFFFFFFE
#define   S_000040_CWTC_VWINE(x)                       (((x) & 0x1) << 1)
#define   G_000040_CWTC_VWINE(x)                       (((x) >> 1) & 0x1)
#define   C_000040_CWTC_VWINE                          0xFFFFFFFD
#define   S_000040_CWTC_VSYNC(x)                       (((x) & 0x1) << 2)
#define   G_000040_CWTC_VSYNC(x)                       (((x) >> 2) & 0x1)
#define   C_000040_CWTC_VSYNC                          0xFFFFFFFB
#define   S_000040_SNAPSHOT(x)                         (((x) & 0x1) << 3)
#define   G_000040_SNAPSHOT(x)                         (((x) >> 3) & 0x1)
#define   C_000040_SNAPSHOT                            0xFFFFFFF7
#define   S_000040_FP_DETECT(x)                        (((x) & 0x1) << 4)
#define   G_000040_FP_DETECT(x)                        (((x) >> 4) & 0x1)
#define   C_000040_FP_DETECT                           0xFFFFFFEF
#define   S_000040_CWTC2_VWINE(x)                      (((x) & 0x1) << 5)
#define   G_000040_CWTC2_VWINE(x)                      (((x) >> 5) & 0x1)
#define   C_000040_CWTC2_VWINE                         0xFFFFFFDF
#define   S_000040_DMA_VIPH0_INT_EN(x)                 (((x) & 0x1) << 12)
#define   G_000040_DMA_VIPH0_INT_EN(x)                 (((x) >> 12) & 0x1)
#define   C_000040_DMA_VIPH0_INT_EN                    0xFFFFEFFF
#define   S_000040_CWTC2_VSYNC(x)                      (((x) & 0x1) << 6)
#define   G_000040_CWTC2_VSYNC(x)                      (((x) >> 6) & 0x1)
#define   C_000040_CWTC2_VSYNC                         0xFFFFFFBF
#define   S_000040_SNAPSHOT2(x)                        (((x) & 0x1) << 7)
#define   G_000040_SNAPSHOT2(x)                        (((x) >> 7) & 0x1)
#define   C_000040_SNAPSHOT2                           0xFFFFFF7F
#define   S_000040_CWTC2_VBWANK(x)                     (((x) & 0x1) << 9)
#define   G_000040_CWTC2_VBWANK(x)                     (((x) >> 9) & 0x1)
#define   C_000040_CWTC2_VBWANK                        0xFFFFFDFF
#define   S_000040_FP2_DETECT(x)                       (((x) & 0x1) << 10)
#define   G_000040_FP2_DETECT(x)                       (((x) >> 10) & 0x1)
#define   C_000040_FP2_DETECT                          0xFFFFFBFF
#define   S_000040_VSYNC_DIFF_OVEW_WIMIT(x)            (((x) & 0x1) << 11)
#define   G_000040_VSYNC_DIFF_OVEW_WIMIT(x)            (((x) >> 11) & 0x1)
#define   C_000040_VSYNC_DIFF_OVEW_WIMIT               0xFFFFF7FF
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
#define   S_000044_CWTC_VBWANK_STAT(x)                 (((x) & 0x1) << 0)
#define   G_000044_CWTC_VBWANK_STAT(x)                 (((x) >> 0) & 0x1)
#define   C_000044_CWTC_VBWANK_STAT                    0xFFFFFFFE
#define   S_000044_CWTC_VBWANK_STAT_AK(x)              (((x) & 0x1) << 0)
#define   G_000044_CWTC_VBWANK_STAT_AK(x)              (((x) >> 0) & 0x1)
#define   C_000044_CWTC_VBWANK_STAT_AK                 0xFFFFFFFE
#define   S_000044_CWTC_VWINE_STAT(x)                  (((x) & 0x1) << 1)
#define   G_000044_CWTC_VWINE_STAT(x)                  (((x) >> 1) & 0x1)
#define   C_000044_CWTC_VWINE_STAT                     0xFFFFFFFD
#define   S_000044_CWTC_VWINE_STAT_AK(x)               (((x) & 0x1) << 1)
#define   G_000044_CWTC_VWINE_STAT_AK(x)               (((x) >> 1) & 0x1)
#define   C_000044_CWTC_VWINE_STAT_AK                  0xFFFFFFFD
#define   S_000044_CWTC_VSYNC_STAT(x)                  (((x) & 0x1) << 2)
#define   G_000044_CWTC_VSYNC_STAT(x)                  (((x) >> 2) & 0x1)
#define   C_000044_CWTC_VSYNC_STAT                     0xFFFFFFFB
#define   S_000044_CWTC_VSYNC_STAT_AK(x)               (((x) & 0x1) << 2)
#define   G_000044_CWTC_VSYNC_STAT_AK(x)               (((x) >> 2) & 0x1)
#define   C_000044_CWTC_VSYNC_STAT_AK                  0xFFFFFFFB
#define   S_000044_SNAPSHOT_STAT(x)                    (((x) & 0x1) << 3)
#define   G_000044_SNAPSHOT_STAT(x)                    (((x) >> 3) & 0x1)
#define   C_000044_SNAPSHOT_STAT                       0xFFFFFFF7
#define   S_000044_SNAPSHOT_STAT_AK(x)                 (((x) & 0x1) << 3)
#define   G_000044_SNAPSHOT_STAT_AK(x)                 (((x) >> 3) & 0x1)
#define   C_000044_SNAPSHOT_STAT_AK                    0xFFFFFFF7
#define   S_000044_FP_DETECT_STAT(x)                   (((x) & 0x1) << 4)
#define   G_000044_FP_DETECT_STAT(x)                   (((x) >> 4) & 0x1)
#define   C_000044_FP_DETECT_STAT                      0xFFFFFFEF
#define   S_000044_FP_DETECT_STAT_AK(x)                (((x) & 0x1) << 4)
#define   G_000044_FP_DETECT_STAT_AK(x)                (((x) >> 4) & 0x1)
#define   C_000044_FP_DETECT_STAT_AK                   0xFFFFFFEF
#define   S_000044_CWTC2_VWINE_STAT(x)                 (((x) & 0x1) << 5)
#define   G_000044_CWTC2_VWINE_STAT(x)                 (((x) >> 5) & 0x1)
#define   C_000044_CWTC2_VWINE_STAT                    0xFFFFFFDF
#define   S_000044_CWTC2_VWINE_STAT_AK(x)              (((x) & 0x1) << 5)
#define   G_000044_CWTC2_VWINE_STAT_AK(x)              (((x) >> 5) & 0x1)
#define   C_000044_CWTC2_VWINE_STAT_AK                 0xFFFFFFDF
#define   S_000044_CWTC2_VSYNC_STAT(x)                 (((x) & 0x1) << 6)
#define   G_000044_CWTC2_VSYNC_STAT(x)                 (((x) >> 6) & 0x1)
#define   C_000044_CWTC2_VSYNC_STAT                    0xFFFFFFBF
#define   S_000044_CWTC2_VSYNC_STAT_AK(x)              (((x) & 0x1) << 6)
#define   G_000044_CWTC2_VSYNC_STAT_AK(x)              (((x) >> 6) & 0x1)
#define   C_000044_CWTC2_VSYNC_STAT_AK                 0xFFFFFFBF
#define   S_000044_SNAPSHOT2_STAT(x)                   (((x) & 0x1) << 7)
#define   G_000044_SNAPSHOT2_STAT(x)                   (((x) >> 7) & 0x1)
#define   C_000044_SNAPSHOT2_STAT                      0xFFFFFF7F
#define   S_000044_SNAPSHOT2_STAT_AK(x)                (((x) & 0x1) << 7)
#define   G_000044_SNAPSHOT2_STAT_AK(x)                (((x) >> 7) & 0x1)
#define   C_000044_SNAPSHOT2_STAT_AK                   0xFFFFFF7F
#define   S_000044_CAP0_INT_ACTIVE(x)                  (((x) & 0x1) << 8)
#define   G_000044_CAP0_INT_ACTIVE(x)                  (((x) >> 8) & 0x1)
#define   C_000044_CAP0_INT_ACTIVE                     0xFFFFFEFF
#define   S_000044_CWTC2_VBWANK_STAT(x)                (((x) & 0x1) << 9)
#define   G_000044_CWTC2_VBWANK_STAT(x)                (((x) >> 9) & 0x1)
#define   C_000044_CWTC2_VBWANK_STAT                   0xFFFFFDFF
#define   S_000044_CWTC2_VBWANK_STAT_AK(x)             (((x) & 0x1) << 9)
#define   G_000044_CWTC2_VBWANK_STAT_AK(x)             (((x) >> 9) & 0x1)
#define   C_000044_CWTC2_VBWANK_STAT_AK                0xFFFFFDFF
#define   S_000044_FP2_DETECT_STAT(x)                  (((x) & 0x1) << 10)
#define   G_000044_FP2_DETECT_STAT(x)                  (((x) >> 10) & 0x1)
#define   C_000044_FP2_DETECT_STAT                     0xFFFFFBFF
#define   S_000044_FP2_DETECT_STAT_AK(x)               (((x) & 0x1) << 10)
#define   G_000044_FP2_DETECT_STAT_AK(x)               (((x) >> 10) & 0x1)
#define   C_000044_FP2_DETECT_STAT_AK                  0xFFFFFBFF
#define   S_000044_VSYNC_DIFF_OVEW_WIMIT_STAT(x)       (((x) & 0x1) << 11)
#define   G_000044_VSYNC_DIFF_OVEW_WIMIT_STAT(x)       (((x) >> 11) & 0x1)
#define   C_000044_VSYNC_DIFF_OVEW_WIMIT_STAT          0xFFFFF7FF
#define   S_000044_VSYNC_DIFF_OVEW_WIMIT_STAT_AK(x)    (((x) & 0x1) << 11)
#define   G_000044_VSYNC_DIFF_OVEW_WIMIT_STAT_AK(x)    (((x) >> 11) & 0x1)
#define   C_000044_VSYNC_DIFF_OVEW_WIMIT_STAT_AK       0xFFFFF7FF
#define   S_000044_DMA_VIPH0_INT(x)                    (((x) & 0x1) << 12)
#define   G_000044_DMA_VIPH0_INT(x)                    (((x) >> 12) & 0x1)
#define   C_000044_DMA_VIPH0_INT                       0xFFFFEFFF
#define   S_000044_DMA_VIPH0_INT_AK(x)                 (((x) & 0x1) << 12)
#define   G_000044_DMA_VIPH0_INT_AK(x)                 (((x) >> 12) & 0x1)
#define   C_000044_DMA_VIPH0_INT_AK                    0xFFFFEFFF
#define   S_000044_DMA_VIPH1_INT(x)                    (((x) & 0x1) << 13)
#define   G_000044_DMA_VIPH1_INT(x)                    (((x) >> 13) & 0x1)
#define   C_000044_DMA_VIPH1_INT                       0xFFFFDFFF
#define   S_000044_DMA_VIPH1_INT_AK(x)                 (((x) & 0x1) << 13)
#define   G_000044_DMA_VIPH1_INT_AK(x)                 (((x) >> 13) & 0x1)
#define   C_000044_DMA_VIPH1_INT_AK                    0xFFFFDFFF
#define   S_000044_DMA_VIPH2_INT(x)                    (((x) & 0x1) << 14)
#define   G_000044_DMA_VIPH2_INT(x)                    (((x) >> 14) & 0x1)
#define   C_000044_DMA_VIPH2_INT                       0xFFFFBFFF
#define   S_000044_DMA_VIPH2_INT_AK(x)                 (((x) & 0x1) << 14)
#define   G_000044_DMA_VIPH2_INT_AK(x)                 (((x) >> 14) & 0x1)
#define   C_000044_DMA_VIPH2_INT_AK                    0xFFFFBFFF
#define   S_000044_DMA_VIPH3_INT(x)                    (((x) & 0x1) << 15)
#define   G_000044_DMA_VIPH3_INT(x)                    (((x) >> 15) & 0x1)
#define   C_000044_DMA_VIPH3_INT                       0xFFFF7FFF
#define   S_000044_DMA_VIPH3_INT_AK(x)                 (((x) & 0x1) << 15)
#define   G_000044_DMA_VIPH3_INT_AK(x)                 (((x) >> 15) & 0x1)
#define   C_000044_DMA_VIPH3_INT_AK                    0xFFFF7FFF
#define   S_000044_I2C_INT(x)                          (((x) & 0x1) << 17)
#define   G_000044_I2C_INT(x)                          (((x) >> 17) & 0x1)
#define   C_000044_I2C_INT                             0xFFFDFFFF
#define   S_000044_I2C_INT_AK(x)                       (((x) & 0x1) << 17)
#define   G_000044_I2C_INT_AK(x)                       (((x) >> 17) & 0x1)
#define   C_000044_I2C_INT_AK                          0xFFFDFFFF
#define   S_000044_GUI_IDWE_STAT(x)                    (((x) & 0x1) << 19)
#define   G_000044_GUI_IDWE_STAT(x)                    (((x) >> 19) & 0x1)
#define   C_000044_GUI_IDWE_STAT                       0xFFF7FFFF
#define   S_000044_GUI_IDWE_STAT_AK(x)                 (((x) & 0x1) << 19)
#define   G_000044_GUI_IDWE_STAT_AK(x)                 (((x) >> 19) & 0x1)
#define   C_000044_GUI_IDWE_STAT_AK                    0xFFF7FFFF
#define   S_000044_VIPH_INT(x)                         (((x) & 0x1) << 24)
#define   G_000044_VIPH_INT(x)                         (((x) >> 24) & 0x1)
#define   C_000044_VIPH_INT                            0xFEFFFFFF
#define   S_000044_SW_INT(x)                           (((x) & 0x1) << 25)
#define   G_000044_SW_INT(x)                           (((x) >> 25) & 0x1)
#define   C_000044_SW_INT                              0xFDFFFFFF
#define   S_000044_SW_INT_AK(x)                        (((x) & 0x1) << 25)
#define   G_000044_SW_INT_AK(x)                        (((x) >> 25) & 0x1)
#define   C_000044_SW_INT_AK                           0xFDFFFFFF
#define   S_000044_SW_INT_SET(x)                       (((x) & 0x1) << 26)
#define   G_000044_SW_INT_SET(x)                       (((x) >> 26) & 0x1)
#define   C_000044_SW_INT_SET                          0xFBFFFFFF
#define   S_000044_GEYSEWVIWWE_STAT(x)                 (((x) & 0x1) << 27)
#define   G_000044_GEYSEWVIWWE_STAT(x)                 (((x) >> 27) & 0x1)
#define   C_000044_GEYSEWVIWWE_STAT                    0xF7FFFFFF
#define   S_000044_GEYSEWVIWWE_STAT_AK(x)              (((x) & 0x1) << 27)
#define   G_000044_GEYSEWVIWWE_STAT_AK(x)              (((x) >> 27) & 0x1)
#define   C_000044_GEYSEWVIWWE_STAT_AK                 0xF7FFFFFF
#define   S_000044_HDCP_AUTHOWIZED_INT_STAT(x)         (((x) & 0x1) << 28)
#define   G_000044_HDCP_AUTHOWIZED_INT_STAT(x)         (((x) >> 28) & 0x1)
#define   C_000044_HDCP_AUTHOWIZED_INT_STAT            0xEFFFFFFF
#define   S_000044_HDCP_AUTHOWIZED_INT_AK(x)           (((x) & 0x1) << 28)
#define   G_000044_HDCP_AUTHOWIZED_INT_AK(x)           (((x) >> 28) & 0x1)
#define   C_000044_HDCP_AUTHOWIZED_INT_AK              0xEFFFFFFF
#define   S_000044_DVI_I2C_INT_STAT(x)                 (((x) & 0x1) << 29)
#define   G_000044_DVI_I2C_INT_STAT(x)                 (((x) >> 29) & 0x1)
#define   C_000044_DVI_I2C_INT_STAT                    0xDFFFFFFF
#define   S_000044_DVI_I2C_INT_AK(x)                   (((x) & 0x1) << 29)
#define   G_000044_DVI_I2C_INT_AK(x)                   (((x) >> 29) & 0x1)
#define   C_000044_DVI_I2C_INT_AK                      0xDFFFFFFF
#define   S_000044_GUIDMA_STAT(x)                      (((x) & 0x1) << 30)
#define   G_000044_GUIDMA_STAT(x)                      (((x) >> 30) & 0x1)
#define   C_000044_GUIDMA_STAT                         0xBFFFFFFF
#define   S_000044_GUIDMA_AK(x)                        (((x) & 0x1) << 30)
#define   G_000044_GUIDMA_AK(x)                        (((x) >> 30) & 0x1)
#define   C_000044_GUIDMA_AK                           0xBFFFFFFF
#define   S_000044_VIDDMA_STAT(x)                      (((x) & 0x1) << 31)
#define   G_000044_VIDDMA_STAT(x)                      (((x) >> 31) & 0x1)
#define   C_000044_VIDDMA_STAT                         0x7FFFFFFF
#define   S_000044_VIDDMA_AK(x)                        (((x) & 0x1) << 31)
#define   G_000044_VIDDMA_AK(x)                        (((x) >> 31) & 0x1)
#define   C_000044_VIDDMA_AK                           0x7FFFFFFF
#define W_000050_CWTC_GEN_CNTW                       0x000050
#define   S_000050_CWTC_DBW_SCAN_EN(x)                 (((x) & 0x1) << 0)
#define   G_000050_CWTC_DBW_SCAN_EN(x)                 (((x) >> 0) & 0x1)
#define   C_000050_CWTC_DBW_SCAN_EN                    0xFFFFFFFE
#define   S_000050_CWTC_INTEWWACE_EN(x)                (((x) & 0x1) << 1)
#define   G_000050_CWTC_INTEWWACE_EN(x)                (((x) >> 1) & 0x1)
#define   C_000050_CWTC_INTEWWACE_EN                   0xFFFFFFFD
#define   S_000050_CWTC_C_SYNC_EN(x)                   (((x) & 0x1) << 4)
#define   G_000050_CWTC_C_SYNC_EN(x)                   (((x) >> 4) & 0x1)
#define   C_000050_CWTC_C_SYNC_EN                      0xFFFFFFEF
#define   S_000050_CWTC_PIX_WIDTH(x)                   (((x) & 0xF) << 8)
#define   G_000050_CWTC_PIX_WIDTH(x)                   (((x) >> 8) & 0xF)
#define   C_000050_CWTC_PIX_WIDTH                      0xFFFFF0FF
#define   S_000050_CWTC_ICON_EN(x)                     (((x) & 0x1) << 15)
#define   G_000050_CWTC_ICON_EN(x)                     (((x) >> 15) & 0x1)
#define   C_000050_CWTC_ICON_EN                        0xFFFF7FFF
#define   S_000050_CWTC_CUW_EN(x)                      (((x) & 0x1) << 16)
#define   G_000050_CWTC_CUW_EN(x)                      (((x) >> 16) & 0x1)
#define   C_000050_CWTC_CUW_EN                         0xFFFEFFFF
#define   S_000050_CWTC_VSTAT_MODE(x)                  (((x) & 0x3) << 17)
#define   G_000050_CWTC_VSTAT_MODE(x)                  (((x) >> 17) & 0x3)
#define   C_000050_CWTC_VSTAT_MODE                     0xFFF9FFFF
#define   S_000050_CWTC_CUW_MODE(x)                    (((x) & 0x7) << 20)
#define   G_000050_CWTC_CUW_MODE(x)                    (((x) >> 20) & 0x7)
#define   C_000050_CWTC_CUW_MODE                       0xFF8FFFFF
#define   S_000050_CWTC_EXT_DISP_EN(x)                 (((x) & 0x1) << 24)
#define   G_000050_CWTC_EXT_DISP_EN(x)                 (((x) >> 24) & 0x1)
#define   C_000050_CWTC_EXT_DISP_EN                    0xFEFFFFFF
#define   S_000050_CWTC_EN(x)                          (((x) & 0x1) << 25)
#define   G_000050_CWTC_EN(x)                          (((x) >> 25) & 0x1)
#define   C_000050_CWTC_EN                             0xFDFFFFFF
#define   S_000050_CWTC_DISP_WEQ_EN_B(x)               (((x) & 0x1) << 26)
#define   G_000050_CWTC_DISP_WEQ_EN_B(x)               (((x) >> 26) & 0x1)
#define   C_000050_CWTC_DISP_WEQ_EN_B                  0xFBFFFFFF
#define W_000054_CWTC_EXT_CNTW                       0x000054
#define   S_000054_CWTC_VGA_XOVEWSCAN(x)               (((x) & 0x1) << 0)
#define   G_000054_CWTC_VGA_XOVEWSCAN(x)               (((x) >> 0) & 0x1)
#define   C_000054_CWTC_VGA_XOVEWSCAN                  0xFFFFFFFE
#define   S_000054_VGA_BWINK_WATE(x)                   (((x) & 0x3) << 1)
#define   G_000054_VGA_BWINK_WATE(x)                   (((x) >> 1) & 0x3)
#define   C_000054_VGA_BWINK_WATE                      0xFFFFFFF9
#define   S_000054_VGA_ATI_WINEAW(x)                   (((x) & 0x1) << 3)
#define   G_000054_VGA_ATI_WINEAW(x)                   (((x) >> 3) & 0x1)
#define   C_000054_VGA_ATI_WINEAW                      0xFFFFFFF7
#define   S_000054_VGA_128KAP_PAGING(x)                (((x) & 0x1) << 4)
#define   G_000054_VGA_128KAP_PAGING(x)                (((x) >> 4) & 0x1)
#define   C_000054_VGA_128KAP_PAGING                   0xFFFFFFEF
#define   S_000054_VGA_TEXT_132(x)                     (((x) & 0x1) << 5)
#define   G_000054_VGA_TEXT_132(x)                     (((x) >> 5) & 0x1)
#define   C_000054_VGA_TEXT_132                        0xFFFFFFDF
#define   S_000054_VGA_XCWT_CNT_EN(x)                  (((x) & 0x1) << 6)
#define   G_000054_VGA_XCWT_CNT_EN(x)                  (((x) >> 6) & 0x1)
#define   C_000054_VGA_XCWT_CNT_EN                     0xFFFFFFBF
#define   S_000054_CWTC_HSYNC_DIS(x)                   (((x) & 0x1) << 8)
#define   G_000054_CWTC_HSYNC_DIS(x)                   (((x) >> 8) & 0x1)
#define   C_000054_CWTC_HSYNC_DIS                      0xFFFFFEFF
#define   S_000054_CWTC_VSYNC_DIS(x)                   (((x) & 0x1) << 9)
#define   G_000054_CWTC_VSYNC_DIS(x)                   (((x) >> 9) & 0x1)
#define   C_000054_CWTC_VSYNC_DIS                      0xFFFFFDFF
#define   S_000054_CWTC_DISPWAY_DIS(x)                 (((x) & 0x1) << 10)
#define   G_000054_CWTC_DISPWAY_DIS(x)                 (((x) >> 10) & 0x1)
#define   C_000054_CWTC_DISPWAY_DIS                    0xFFFFFBFF
#define   S_000054_CWTC_SYNC_TWISTATE(x)               (((x) & 0x1) << 11)
#define   G_000054_CWTC_SYNC_TWISTATE(x)               (((x) >> 11) & 0x1)
#define   C_000054_CWTC_SYNC_TWISTATE                  0xFFFFF7FF
#define   S_000054_CWTC_HSYNC_TWISTATE(x)              (((x) & 0x1) << 12)
#define   G_000054_CWTC_HSYNC_TWISTATE(x)              (((x) >> 12) & 0x1)
#define   C_000054_CWTC_HSYNC_TWISTATE                 0xFFFFEFFF
#define   S_000054_CWTC_VSYNC_TWISTATE(x)              (((x) & 0x1) << 13)
#define   G_000054_CWTC_VSYNC_TWISTATE(x)              (((x) >> 13) & 0x1)
#define   C_000054_CWTC_VSYNC_TWISTATE                 0xFFFFDFFF
#define   S_000054_CWT_ON(x)                           (((x) & 0x1) << 15)
#define   G_000054_CWT_ON(x)                           (((x) >> 15) & 0x1)
#define   C_000054_CWT_ON                              0xFFFF7FFF
#define   S_000054_VGA_CUW_B_TEST(x)                   (((x) & 0x1) << 17)
#define   G_000054_VGA_CUW_B_TEST(x)                   (((x) >> 17) & 0x1)
#define   C_000054_VGA_CUW_B_TEST                      0xFFFDFFFF
#define   S_000054_VGA_PACK_DIS(x)                     (((x) & 0x1) << 18)
#define   G_000054_VGA_PACK_DIS(x)                     (((x) >> 18) & 0x1)
#define   C_000054_VGA_PACK_DIS                        0xFFFBFFFF
#define   S_000054_VGA_MEM_PS_EN(x)                    (((x) & 0x1) << 19)
#define   G_000054_VGA_MEM_PS_EN(x)                    (((x) >> 19) & 0x1)
#define   C_000054_VGA_MEM_PS_EN                       0xFFF7FFFF
#define   S_000054_VCWTC_IDX_MASTEW(x)                 (((x) & 0x7F) << 24)
#define   G_000054_VCWTC_IDX_MASTEW(x)                 (((x) >> 24) & 0x7F)
#define   C_000054_VCWTC_IDX_MASTEW                    0x80FFFFFF
#define W_000148_MC_FB_WOCATION                      0x000148
#define   S_000148_MC_FB_STAWT(x)                      (((x) & 0xFFFF) << 0)
#define   G_000148_MC_FB_STAWT(x)                      (((x) >> 0) & 0xFFFF)
#define   C_000148_MC_FB_STAWT                         0xFFFF0000
#define   S_000148_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#define   G_000148_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#define   C_000148_MC_FB_TOP                           0x0000FFFF
#define W_00014C_MC_AGP_WOCATION                     0x00014C
#define   S_00014C_MC_AGP_STAWT(x)                     (((x) & 0xFFFF) << 0)
#define   G_00014C_MC_AGP_STAWT(x)                     (((x) >> 0) & 0xFFFF)
#define   C_00014C_MC_AGP_STAWT                        0xFFFF0000
#define   S_00014C_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#define   G_00014C_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#define   C_00014C_MC_AGP_TOP                          0x0000FFFF
#define W_000170_AGP_BASE                            0x000170
#define   S_000170_AGP_BASE_ADDW(x)                    (((x) & 0xFFFFFFFF) << 0)
#define   G_000170_AGP_BASE_ADDW(x)                    (((x) >> 0) & 0xFFFFFFFF)
#define   C_000170_AGP_BASE_ADDW                       0x00000000
#define W_00023C_DISPWAY_BASE_ADDW                   0x00023C
#define   S_00023C_DISPWAY_BASE_ADDW(x)                (((x) & 0xFFFFFFFF) << 0)
#define   G_00023C_DISPWAY_BASE_ADDW(x)                (((x) >> 0) & 0xFFFFFFFF)
#define   C_00023C_DISPWAY_BASE_ADDW                   0x00000000
#define W_000260_CUW_OFFSET                          0x000260
#define   S_000260_CUW_OFFSET(x)                       (((x) & 0x7FFFFFF) << 0)
#define   G_000260_CUW_OFFSET(x)                       (((x) >> 0) & 0x7FFFFFF)
#define   C_000260_CUW_OFFSET                          0xF8000000
#define   S_000260_CUW_WOCK(x)                         (((x) & 0x1) << 31)
#define   G_000260_CUW_WOCK(x)                         (((x) >> 31) & 0x1)
#define   C_000260_CUW_WOCK                            0x7FFFFFFF
#define W_00033C_CWTC2_DISPWAY_BASE_ADDW             0x00033C
#define   S_00033C_CWTC2_DISPWAY_BASE_ADDW(x)          (((x) & 0xFFFFFFFF) << 0)
#define   G_00033C_CWTC2_DISPWAY_BASE_ADDW(x)          (((x) >> 0) & 0xFFFFFFFF)
#define   C_00033C_CWTC2_DISPWAY_BASE_ADDW             0x00000000
#define W_000360_CUW2_OFFSET                         0x000360
#define   S_000360_CUW2_OFFSET(x)                      (((x) & 0x7FFFFFF) << 0)
#define   G_000360_CUW2_OFFSET(x)                      (((x) >> 0) & 0x7FFFFFF)
#define   C_000360_CUW2_OFFSET                         0xF8000000
#define   S_000360_CUW2_WOCK(x)                        (((x) & 0x1) << 31)
#define   G_000360_CUW2_WOCK(x)                        (((x) >> 31) & 0x1)
#define   C_000360_CUW2_WOCK                           0x7FFFFFFF
#define W_0003C2_GENMO_WT                            0x0003C2
#define   S_0003C2_GENMO_MONO_ADDWESS_B(x)             (((x) & 0x1) << 0)
#define   G_0003C2_GENMO_MONO_ADDWESS_B(x)             (((x) >> 0) & 0x1)
#define   C_0003C2_GENMO_MONO_ADDWESS_B                0xFE
#define   S_0003C2_VGA_WAM_EN(x)                       (((x) & 0x1) << 1)
#define   G_0003C2_VGA_WAM_EN(x)                       (((x) >> 1) & 0x1)
#define   C_0003C2_VGA_WAM_EN                          0xFD
#define   S_0003C2_VGA_CKSEW(x)                        (((x) & 0x3) << 2)
#define   G_0003C2_VGA_CKSEW(x)                        (((x) >> 2) & 0x3)
#define   C_0003C2_VGA_CKSEW                           0xF3
#define   S_0003C2_ODD_EVEN_MD_PGSEW(x)                (((x) & 0x1) << 5)
#define   G_0003C2_ODD_EVEN_MD_PGSEW(x)                (((x) >> 5) & 0x1)
#define   C_0003C2_ODD_EVEN_MD_PGSEW                   0xDF
#define   S_0003C2_VGA_HSYNC_POW(x)                    (((x) & 0x1) << 6)
#define   G_0003C2_VGA_HSYNC_POW(x)                    (((x) >> 6) & 0x1)
#define   C_0003C2_VGA_HSYNC_POW                       0xBF
#define   S_0003C2_VGA_VSYNC_POW(x)                    (((x) & 0x1) << 7)
#define   G_0003C2_VGA_VSYNC_POW(x)                    (((x) >> 7) & 0x1)
#define   C_0003C2_VGA_VSYNC_POW                       0x7F
#define W_0003F8_CWTC2_GEN_CNTW                      0x0003F8
#define   S_0003F8_CWTC2_DBW_SCAN_EN(x)                (((x) & 0x1) << 0)
#define   G_0003F8_CWTC2_DBW_SCAN_EN(x)                (((x) >> 0) & 0x1)
#define   C_0003F8_CWTC2_DBW_SCAN_EN                   0xFFFFFFFE
#define   S_0003F8_CWTC2_INTEWWACE_EN(x)               (((x) & 0x1) << 1)
#define   G_0003F8_CWTC2_INTEWWACE_EN(x)               (((x) >> 1) & 0x1)
#define   C_0003F8_CWTC2_INTEWWACE_EN                  0xFFFFFFFD
#define   S_0003F8_CWTC2_SYNC_TWISTATE(x)              (((x) & 0x1) << 4)
#define   G_0003F8_CWTC2_SYNC_TWISTATE(x)              (((x) >> 4) & 0x1)
#define   C_0003F8_CWTC2_SYNC_TWISTATE                 0xFFFFFFEF
#define   S_0003F8_CWTC2_HSYNC_TWISTATE(x)             (((x) & 0x1) << 5)
#define   G_0003F8_CWTC2_HSYNC_TWISTATE(x)             (((x) >> 5) & 0x1)
#define   C_0003F8_CWTC2_HSYNC_TWISTATE                0xFFFFFFDF
#define   S_0003F8_CWTC2_VSYNC_TWISTATE(x)             (((x) & 0x1) << 6)
#define   G_0003F8_CWTC2_VSYNC_TWISTATE(x)             (((x) >> 6) & 0x1)
#define   C_0003F8_CWTC2_VSYNC_TWISTATE                0xFFFFFFBF
#define   S_0003F8_CWT2_ON(x)                          (((x) & 0x1) << 7)
#define   G_0003F8_CWT2_ON(x)                          (((x) >> 7) & 0x1)
#define   C_0003F8_CWT2_ON                             0xFFFFFF7F
#define   S_0003F8_CWTC2_PIX_WIDTH(x)                  (((x) & 0xF) << 8)
#define   G_0003F8_CWTC2_PIX_WIDTH(x)                  (((x) >> 8) & 0xF)
#define   C_0003F8_CWTC2_PIX_WIDTH                     0xFFFFF0FF
#define   S_0003F8_CWTC2_ICON_EN(x)                    (((x) & 0x1) << 15)
#define   G_0003F8_CWTC2_ICON_EN(x)                    (((x) >> 15) & 0x1)
#define   C_0003F8_CWTC2_ICON_EN                       0xFFFF7FFF
#define   S_0003F8_CWTC2_CUW_EN(x)                     (((x) & 0x1) << 16)
#define   G_0003F8_CWTC2_CUW_EN(x)                     (((x) >> 16) & 0x1)
#define   C_0003F8_CWTC2_CUW_EN                        0xFFFEFFFF
#define   S_0003F8_CWTC2_CUW_MODE(x)                   (((x) & 0x7) << 20)
#define   G_0003F8_CWTC2_CUW_MODE(x)                   (((x) >> 20) & 0x7)
#define   C_0003F8_CWTC2_CUW_MODE                      0xFF8FFFFF
#define   S_0003F8_CWTC2_DISPWAY_DIS(x)                (((x) & 0x1) << 23)
#define   G_0003F8_CWTC2_DISPWAY_DIS(x)                (((x) >> 23) & 0x1)
#define   C_0003F8_CWTC2_DISPWAY_DIS                   0xFF7FFFFF
#define   S_0003F8_CWTC2_EN(x)                         (((x) & 0x1) << 25)
#define   G_0003F8_CWTC2_EN(x)                         (((x) >> 25) & 0x1)
#define   C_0003F8_CWTC2_EN                            0xFDFFFFFF
#define   S_0003F8_CWTC2_DISP_WEQ_EN_B(x)              (((x) & 0x1) << 26)
#define   G_0003F8_CWTC2_DISP_WEQ_EN_B(x)              (((x) >> 26) & 0x1)
#define   C_0003F8_CWTC2_DISP_WEQ_EN_B                 0xFBFFFFFF
#define   S_0003F8_CWTC2_C_SYNC_EN(x)                  (((x) & 0x1) << 27)
#define   G_0003F8_CWTC2_C_SYNC_EN(x)                  (((x) >> 27) & 0x1)
#define   C_0003F8_CWTC2_C_SYNC_EN                     0xF7FFFFFF
#define   S_0003F8_CWTC2_HSYNC_DIS(x)                  (((x) & 0x1) << 28)
#define   G_0003F8_CWTC2_HSYNC_DIS(x)                  (((x) >> 28) & 0x1)
#define   C_0003F8_CWTC2_HSYNC_DIS                     0xEFFFFFFF
#define   S_0003F8_CWTC2_VSYNC_DIS(x)                  (((x) & 0x1) << 29)
#define   G_0003F8_CWTC2_VSYNC_DIS(x)                  (((x) >> 29) & 0x1)
#define   C_0003F8_CWTC2_VSYNC_DIS                     0xDFFFFFFF
#define W_000420_OV0_SCAWE_CNTW                      0x000420
#define   S_000420_OV0_NO_WEAD_BEHIND_SCAN(x)          (((x) & 0x1) << 1)
#define   G_000420_OV0_NO_WEAD_BEHIND_SCAN(x)          (((x) >> 1) & 0x1)
#define   C_000420_OV0_NO_WEAD_BEHIND_SCAN             0xFFFFFFFD
#define   S_000420_OV0_HOWZ_PICK_NEAWEST(x)            (((x) & 0x1) << 2)
#define   G_000420_OV0_HOWZ_PICK_NEAWEST(x)            (((x) >> 2) & 0x1)
#define   C_000420_OV0_HOWZ_PICK_NEAWEST               0xFFFFFFFB
#define   S_000420_OV0_VEWT_PICK_NEAWEST(x)            (((x) & 0x1) << 3)
#define   G_000420_OV0_VEWT_PICK_NEAWEST(x)            (((x) >> 3) & 0x1)
#define   C_000420_OV0_VEWT_PICK_NEAWEST               0xFFFFFFF7
#define   S_000420_OV0_SIGNED_UV(x)                    (((x) & 0x1) << 4)
#define   G_000420_OV0_SIGNED_UV(x)                    (((x) >> 4) & 0x1)
#define   C_000420_OV0_SIGNED_UV                       0xFFFFFFEF
#define   S_000420_OV0_GAMMA_SEW(x)                    (((x) & 0x7) << 5)
#define   G_000420_OV0_GAMMA_SEW(x)                    (((x) >> 5) & 0x7)
#define   C_000420_OV0_GAMMA_SEW                       0xFFFFFF1F
#define   S_000420_OV0_SUWFACE_FOWMAT(x)               (((x) & 0xF) << 8)
#define   G_000420_OV0_SUWFACE_FOWMAT(x)               (((x) >> 8) & 0xF)
#define   C_000420_OV0_SUWFACE_FOWMAT                  0xFFFFF0FF
#define   S_000420_OV0_ADAPTIVE_DEINT(x)               (((x) & 0x1) << 12)
#define   G_000420_OV0_ADAPTIVE_DEINT(x)               (((x) >> 12) & 0x1)
#define   C_000420_OV0_ADAPTIVE_DEINT                  0xFFFFEFFF
#define   S_000420_OV0_CWTC_SEW(x)                     (((x) & 0x1) << 14)
#define   G_000420_OV0_CWTC_SEW(x)                     (((x) >> 14) & 0x1)
#define   C_000420_OV0_CWTC_SEW                        0xFFFFBFFF
#define   S_000420_OV0_BUWST_PEW_PWANE(x)              (((x) & 0x7F) << 16)
#define   G_000420_OV0_BUWST_PEW_PWANE(x)              (((x) >> 16) & 0x7F)
#define   C_000420_OV0_BUWST_PEW_PWANE                 0xFF80FFFF
#define   S_000420_OV0_DOUBWE_BUFFEW_WEGS(x)           (((x) & 0x1) << 24)
#define   G_000420_OV0_DOUBWE_BUFFEW_WEGS(x)           (((x) >> 24) & 0x1)
#define   C_000420_OV0_DOUBWE_BUFFEW_WEGS              0xFEFFFFFF
#define   S_000420_OV0_BANDWIDTH(x)                    (((x) & 0x1) << 26)
#define   G_000420_OV0_BANDWIDTH(x)                    (((x) >> 26) & 0x1)
#define   C_000420_OV0_BANDWIDTH                       0xFBFFFFFF
#define   S_000420_OV0_WIN_TWANS_BYPASS(x)             (((x) & 0x1) << 28)
#define   G_000420_OV0_WIN_TWANS_BYPASS(x)             (((x) >> 28) & 0x1)
#define   C_000420_OV0_WIN_TWANS_BYPASS                0xEFFFFFFF
#define   S_000420_OV0_INT_EMU(x)                      (((x) & 0x1) << 29)
#define   G_000420_OV0_INT_EMU(x)                      (((x) >> 29) & 0x1)
#define   C_000420_OV0_INT_EMU                         0xDFFFFFFF
#define   S_000420_OV0_OVEWWAY_EN(x)                   (((x) & 0x1) << 30)
#define   G_000420_OV0_OVEWWAY_EN(x)                   (((x) >> 30) & 0x1)
#define   C_000420_OV0_OVEWWAY_EN                      0xBFFFFFFF
#define   S_000420_OV0_SOFT_WESET(x)                   (((x) & 0x1) << 31)
#define   G_000420_OV0_SOFT_WESET(x)                   (((x) >> 31) & 0x1)
#define   C_000420_OV0_SOFT_WESET                      0x7FFFFFFF
#define W_00070C_CP_WB_WPTW_ADDW                     0x00070C
#define   S_00070C_WB_WPTW_SWAP(x)                     (((x) & 0x3) << 0)
#define   G_00070C_WB_WPTW_SWAP(x)                     (((x) >> 0) & 0x3)
#define   C_00070C_WB_WPTW_SWAP                        0xFFFFFFFC
#define   S_00070C_WB_WPTW_ADDW(x)                     (((x) & 0x3FFFFFFF) << 2)
#define   G_00070C_WB_WPTW_ADDW(x)                     (((x) >> 2) & 0x3FFFFFFF)
#define   C_00070C_WB_WPTW_ADDW                        0x00000003
#define W_000740_CP_CSQ_CNTW                         0x000740
#define   S_000740_CSQ_CNT_PWIMAWY(x)                  (((x) & 0xFF) << 0)
#define   G_000740_CSQ_CNT_PWIMAWY(x)                  (((x) >> 0) & 0xFF)
#define   C_000740_CSQ_CNT_PWIMAWY                     0xFFFFFF00
#define   S_000740_CSQ_CNT_INDIWECT(x)                 (((x) & 0xFF) << 8)
#define   G_000740_CSQ_CNT_INDIWECT(x)                 (((x) >> 8) & 0xFF)
#define   C_000740_CSQ_CNT_INDIWECT                    0xFFFF00FF
#define   S_000740_CSQ_MODE(x)                         (((x) & 0xF) << 28)
#define   G_000740_CSQ_MODE(x)                         (((x) >> 28) & 0xF)
#define   C_000740_CSQ_MODE                            0x0FFFFFFF
#define W_000770_SCWATCH_UMSK                        0x000770
#define   S_000770_SCWATCH_UMSK(x)                     (((x) & 0x3F) << 0)
#define   G_000770_SCWATCH_UMSK(x)                     (((x) >> 0) & 0x3F)
#define   C_000770_SCWATCH_UMSK                        0xFFFFFFC0
#define   S_000770_SCWATCH_SWAP(x)                     (((x) & 0x3) << 16)
#define   G_000770_SCWATCH_SWAP(x)                     (((x) >> 16) & 0x3)
#define   C_000770_SCWATCH_SWAP                        0xFFFCFFFF
#define W_000774_SCWATCH_ADDW                        0x000774
#define   S_000774_SCWATCH_ADDW(x)                     (((x) & 0x7FFFFFF) << 5)
#define   G_000774_SCWATCH_ADDW(x)                     (((x) >> 5) & 0x7FFFFFF)
#define   C_000774_SCWATCH_ADDW                        0x0000001F
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
#define   S_000E40_SE_BUSY(x)                          (((x) & 0x1) << 20)
#define   G_000E40_SE_BUSY(x)                          (((x) >> 20) & 0x1)
#define   C_000E40_SE_BUSY                             0xFFEFFFFF
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
#define   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#define   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#define   C_000E40_GUI_ACTIVE                          0x7FFFFFFF


#define W_00000D_SCWK_CNTW                           0x00000D
#define   S_00000D_SCWK_SWC_SEW(x)                     (((x) & 0x7) << 0)
#define   G_00000D_SCWK_SWC_SEW(x)                     (((x) >> 0) & 0x7)
#define   C_00000D_SCWK_SWC_SEW                        0xFFFFFFF8
#define   S_00000D_TCWK_SWC_SEW(x)                     (((x) & 0x7) << 8)
#define   G_00000D_TCWK_SWC_SEW(x)                     (((x) >> 8) & 0x7)
#define   C_00000D_TCWK_SWC_SEW                        0xFFFFF8FF
#define   S_00000D_FOWCE_CP(x)                         (((x) & 0x1) << 16)
#define   G_00000D_FOWCE_CP(x)                         (((x) >> 16) & 0x1)
#define   C_00000D_FOWCE_CP                            0xFFFEFFFF
#define   S_00000D_FOWCE_HDP(x)                        (((x) & 0x1) << 17)
#define   G_00000D_FOWCE_HDP(x)                        (((x) >> 17) & 0x1)
#define   C_00000D_FOWCE_HDP                           0xFFFDFFFF
#define   S_00000D_FOWCE_DISP(x)                       (((x) & 0x1) << 18)
#define   G_00000D_FOWCE_DISP(x)                       (((x) >> 18) & 0x1)
#define   C_00000D_FOWCE_DISP                          0xFFFBFFFF
#define   S_00000D_FOWCE_TOP(x)                        (((x) & 0x1) << 19)
#define   G_00000D_FOWCE_TOP(x)                        (((x) >> 19) & 0x1)
#define   C_00000D_FOWCE_TOP                           0xFFF7FFFF
#define   S_00000D_FOWCE_E2(x)                         (((x) & 0x1) << 20)
#define   G_00000D_FOWCE_E2(x)                         (((x) >> 20) & 0x1)
#define   C_00000D_FOWCE_E2                            0xFFEFFFFF
#define   S_00000D_FOWCE_SE(x)                         (((x) & 0x1) << 21)
#define   G_00000D_FOWCE_SE(x)                         (((x) >> 21) & 0x1)
#define   C_00000D_FOWCE_SE                            0xFFDFFFFF
#define   S_00000D_FOWCE_IDCT(x)                       (((x) & 0x1) << 22)
#define   G_00000D_FOWCE_IDCT(x)                       (((x) >> 22) & 0x1)
#define   C_00000D_FOWCE_IDCT                          0xFFBFFFFF
#define   S_00000D_FOWCE_VIP(x)                        (((x) & 0x1) << 23)
#define   G_00000D_FOWCE_VIP(x)                        (((x) >> 23) & 0x1)
#define   C_00000D_FOWCE_VIP                           0xFF7FFFFF
#define   S_00000D_FOWCE_WE(x)                         (((x) & 0x1) << 24)
#define   G_00000D_FOWCE_WE(x)                         (((x) >> 24) & 0x1)
#define   C_00000D_FOWCE_WE                            0xFEFFFFFF
#define   S_00000D_FOWCE_PB(x)                         (((x) & 0x1) << 25)
#define   G_00000D_FOWCE_PB(x)                         (((x) >> 25) & 0x1)
#define   C_00000D_FOWCE_PB                            0xFDFFFFFF
#define   S_00000D_FOWCE_TAM(x)                        (((x) & 0x1) << 26)
#define   G_00000D_FOWCE_TAM(x)                        (((x) >> 26) & 0x1)
#define   C_00000D_FOWCE_TAM                           0xFBFFFFFF
#define   S_00000D_FOWCE_TDM(x)                        (((x) & 0x1) << 27)
#define   G_00000D_FOWCE_TDM(x)                        (((x) >> 27) & 0x1)
#define   C_00000D_FOWCE_TDM                           0xF7FFFFFF
#define   S_00000D_FOWCE_WB(x)                         (((x) & 0x1) << 28)
#define   G_00000D_FOWCE_WB(x)                         (((x) >> 28) & 0x1)
#define   C_00000D_FOWCE_WB                            0xEFFFFFFF

/* PWW wegs */
#define SCWK_CNTW                                      0xd
#define   FOWCE_HDP                                    (1 << 17)
#define CWK_PWWMGT_CNTW                                0x14
#define   GWOBAW_PMAN_EN                               (1 << 10)
#define   DISP_PM                                      (1 << 20)
#define PWW_PWWMGT_CNTW                                0x15
#define   MPWW_TUWNOFF                                 (1 << 0)
#define   SPWW_TUWNOFF                                 (1 << 1)
#define   PPWW_TUWNOFF                                 (1 << 2)
#define   P2PWW_TUWNOFF                                (1 << 3)
#define   TVPWW_TUWNOFF                                (1 << 4)
#define   MOBIWE_SU                                    (1 << 16)
#define   SU_SCWK_USE_BCWK                             (1 << 17)
#define SCWK_CNTW2                                     0x1e
#define   WEDUCED_SPEED_SCWK_MODE                      (1 << 16)
#define   WEDUCED_SPEED_SCWK_SEW(x)                    ((x) << 17)
#define MCWK_MISC                                      0x1f
#define   EN_MCWK_TWISTATE_IN_SUSPEND                  (1 << 18)
#define SCWK_MOWE_CNTW                                 0x35
#define   WEDUCED_SPEED_SCWK_EN                        (1 << 16)
#define   IO_CG_VOWTAGE_DWOP                           (1 << 17)
#define   VOWTAGE_DEWAY_SEW(x)                         ((x) << 20)
#define   VOWTAGE_DWOP_SYNC                            (1 << 19)

/* mmweg */
#define DISP_PWW_MAN                                   0xd08
#define   DISP_D3_GWPH_WST                             (1 << 18)
#define   DISP_D3_SUBPIC_WST                           (1 << 19)
#define   DISP_D3_OV0_WST                              (1 << 20)
#define   DISP_D1D2_GWPH_WST                           (1 << 21)
#define   DISP_D1D2_SUBPIC_WST                         (1 << 22)
#define   DISP_D1D2_OV0_WST                            (1 << 23)
#define   DISP_DVO_ENABWE_WST                          (1 << 24)
#define   TV_ENABWE_WST                                (1 << 25)
#define   AUTO_PWWUP_EN                                (1 << 26)

#endif
