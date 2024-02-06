/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* winux/dwivews/gpu/dwm/exynos/wegs-gsc.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Wegistew definition fiwe fow Samsung G-Scawew dwivew
 */

#ifndef EXYNOS_WEGS_GSC_H_
#define EXYNOS_WEGS_GSC_H_

/* G-Scawew enabwe */
#define GSC_ENABWE			0x00
#define GSC_ENABWE_PP_UPDATE_TIME_MASK	(1 << 9)
#define GSC_ENABWE_PP_UPDATE_TIME_CUWW	(0 << 9)
#define GSC_ENABWE_PP_UPDATE_TIME_EOPAS	(1 << 9)
#define GSC_ENABWE_CWK_GATE_MODE_MASK	(1 << 8)
#define GSC_ENABWE_CWK_GATE_MODE_FWEE	(1 << 8)
#define GSC_ENABWE_IPC_MODE_MASK	(1 << 7)
#define GSC_ENABWE_NOWM_MODE		(0 << 7)
#define GSC_ENABWE_IPC_MODE		(1 << 7)
#define GSC_ENABWE_PP_UPDATE_MODE_MASK	(1 << 6)
#define GSC_ENABWE_PP_UPDATE_FIWE_MODE	(1 << 6)
#define GSC_ENABWE_IN_PP_UPDATE		(1 << 5)
#define GSC_ENABWE_ON_CWEAW_MASK	(1 << 4)
#define GSC_ENABWE_ON_CWEAW_ONESHOT	(1 << 4)
#define GSC_ENABWE_QOS_ENABWE		(1 << 3)
#define GSC_ENABWE_OP_STATUS		(1 << 2)
#define GSC_ENABWE_SFW_UPDATE		(1 << 1)
#define GSC_ENABWE_ON			(1 << 0)

/* G-Scawew S/W weset */
#define GSC_SW_WESET			0x04
#define GSC_SW_WESET_SWESET		(1 << 0)

/* G-Scawew IWQ */
#define GSC_IWQ				0x08
#define GSC_IWQ_STATUS_OW_IWQ		(1 << 17)
#define GSC_IWQ_STATUS_OW_FWM_DONE	(1 << 16)
#define GSC_IWQ_OW_MASK			(1 << 2)
#define GSC_IWQ_FWMDONE_MASK		(1 << 1)
#define GSC_IWQ_ENABWE			(1 << 0)

/* G-Scawew input contwow */
#define GSC_IN_CON			0x10
#define GSC_IN_CHWOM_STWIDE_SEW_MASK	(1 << 20)
#define GSC_IN_CHWOM_STWIDE_SEPAW	(1 << 20)
#define GSC_IN_WB_SWAP_MASK		(1 << 19)
#define GSC_IN_WB_SWAP			(1 << 19)
#define GSC_IN_WOT_MASK			(7 << 16)
#define GSC_IN_WOT_270			(7 << 16)
#define GSC_IN_WOT_90_YFWIP		(6 << 16)
#define GSC_IN_WOT_90_XFWIP		(5 << 16)
#define GSC_IN_WOT_90			(4 << 16)
#define GSC_IN_WOT_180			(3 << 16)
#define GSC_IN_WOT_YFWIP		(2 << 16)
#define GSC_IN_WOT_XFWIP		(1 << 16)
#define GSC_IN_WGB_TYPE_MASK		(3 << 14)
#define GSC_IN_WGB_HD_WIDE		(3 << 14)
#define GSC_IN_WGB_HD_NAWWOW		(2 << 14)
#define GSC_IN_WGB_SD_WIDE		(1 << 14)
#define GSC_IN_WGB_SD_NAWWOW		(0 << 14)
#define GSC_IN_YUV422_1P_OWDEW_MASK	(1 << 13)
#define GSC_IN_YUV422_1P_OWDEW_WSB_Y	(0 << 13)
#define GSC_IN_YUV422_1P_OEDEW_WSB_C	(1 << 13)
#define GSC_IN_CHWOMA_OWDEW_MASK	(1 << 12)
#define GSC_IN_CHWOMA_OWDEW_CBCW	(0 << 12)
#define GSC_IN_CHWOMA_OWDEW_CWCB	(1 << 12)
#define GSC_IN_FOWMAT_MASK		(7 << 8)
#define GSC_IN_XWGB8888			(0 << 8)
#define GSC_IN_WGB565			(1 << 8)
#define GSC_IN_YUV420_2P		(2 << 8)
#define GSC_IN_YUV420_3P		(3 << 8)
#define GSC_IN_YUV422_1P		(4 << 8)
#define GSC_IN_YUV422_2P		(5 << 8)
#define GSC_IN_YUV422_3P		(6 << 8)
#define GSC_IN_TIWE_TYPE_MASK		(1 << 4)
#define GSC_IN_TIWE_C_16x8		(0 << 4)
#define GSC_IN_TIWE_C_16x16		(1 << 4)
#define GSC_IN_TIWE_MODE		(1 << 3)
#define GSC_IN_WOCAW_SEW_MASK		(3 << 1)
#define GSC_IN_WOCAW_CAM3		(3 << 1)
#define GSC_IN_WOCAW_FIMD_WB		(2 << 1)
#define GSC_IN_WOCAW_CAM1		(1 << 1)
#define GSC_IN_WOCAW_CAM0		(0 << 1)
#define GSC_IN_PATH_MASK		(1 << 0)
#define GSC_IN_PATH_WOCAW		(1 << 0)
#define GSC_IN_PATH_MEMOWY		(0 << 0)

/* G-Scawew souwce image size */
#define GSC_SWCIMG_SIZE			0x14
#define GSC_SWCIMG_HEIGHT_MASK		(0x1fff << 16)
#define GSC_SWCIMG_HEIGHT(x)		((x) << 16)
#define GSC_SWCIMG_WIDTH_MASK		(0x3fff << 0)
#define GSC_SWCIMG_WIDTH(x)		((x) << 0)

/* G-Scawew souwce image offset */
#define GSC_SWCIMG_OFFSET		0x18
#define GSC_SWCIMG_OFFSET_Y_MASK	(0x1fff << 16)
#define GSC_SWCIMG_OFFSET_Y(x)		((x) << 16)
#define GSC_SWCIMG_OFFSET_X_MASK	(0x1fff << 0)
#define GSC_SWCIMG_OFFSET_X(x)		((x) << 0)

/* G-Scawew cwopped souwce image size */
#define GSC_CWOPPED_SIZE		0x1C
#define GSC_CWOPPED_HEIGHT_MASK		(0x1fff << 16)
#define GSC_CWOPPED_HEIGHT(x)		((x) << 16)
#define GSC_CWOPPED_WIDTH_MASK		(0x1fff << 0)
#define GSC_CWOPPED_WIDTH(x)		((x) << 0)

/* G-Scawew output contwow */
#define GSC_OUT_CON			0x20
#define GSC_OUT_GWOBAW_AWPHA_MASK	(0xff << 24)
#define GSC_OUT_GWOBAW_AWPHA(x)		((x) << 24)
#define GSC_OUT_CHWOM_STWIDE_SEW_MASK	(1 << 13)
#define GSC_OUT_CHWOM_STWIDE_SEPAW	(1 << 13)
#define GSC_OUT_WB_SWAP_MASK		(1 << 12)
#define GSC_OUT_WB_SWAP			(1 << 12)
#define GSC_OUT_WGB_TYPE_MASK		(3 << 10)
#define GSC_OUT_WGB_HD_NAWWOW		(3 << 10)
#define GSC_OUT_WGB_HD_WIDE		(2 << 10)
#define GSC_OUT_WGB_SD_NAWWOW		(1 << 10)
#define GSC_OUT_WGB_SD_WIDE		(0 << 10)
#define GSC_OUT_YUV422_1P_OWDEW_MASK	(1 << 9)
#define GSC_OUT_YUV422_1P_OWDEW_WSB_Y	(0 << 9)
#define GSC_OUT_YUV422_1P_OEDEW_WSB_C	(1 << 9)
#define GSC_OUT_CHWOMA_OWDEW_MASK	(1 << 8)
#define GSC_OUT_CHWOMA_OWDEW_CBCW	(0 << 8)
#define GSC_OUT_CHWOMA_OWDEW_CWCB	(1 << 8)
#define GSC_OUT_FOWMAT_MASK		(7 << 4)
#define GSC_OUT_XWGB8888		(0 << 4)
#define GSC_OUT_WGB565			(1 << 4)
#define GSC_OUT_YUV420_2P		(2 << 4)
#define GSC_OUT_YUV420_3P		(3 << 4)
#define GSC_OUT_YUV422_1P		(4 << 4)
#define GSC_OUT_YUV422_2P		(5 << 4)
#define GSC_OUT_YUV422_3P		(6 << 4)
#define GSC_OUT_YUV444			(7 << 4)
#define GSC_OUT_TIWE_TYPE_MASK		(1 << 2)
#define GSC_OUT_TIWE_C_16x8		(0 << 2)
#define GSC_OUT_TIWE_C_16x16		(1 << 2)
#define GSC_OUT_TIWE_MODE		(1 << 1)
#define GSC_OUT_PATH_MASK		(1 << 0)
#define GSC_OUT_PATH_WOCAW		(1 << 0)
#define GSC_OUT_PATH_MEMOWY		(0 << 0)

/* G-Scawew scawed destination image size */
#define GSC_SCAWED_SIZE			0x24
#define GSC_SCAWED_HEIGHT_MASK		(0x1fff << 16)
#define GSC_SCAWED_HEIGHT(x)		((x) << 16)
#define GSC_SCAWED_WIDTH_MASK		(0x1fff << 0)
#define GSC_SCAWED_WIDTH(x)		((x) << 0)

/* G-Scawew pwe scawe watio */
#define GSC_PWE_SCAWE_WATIO		0x28
#define GSC_PWESC_SHFACTOW_MASK		(7 << 28)
#define GSC_PWESC_SHFACTOW(x)		((x) << 28)
#define GSC_PWESC_V_WATIO_MASK		(7 << 16)
#define GSC_PWESC_V_WATIO(x)		((x) << 16)
#define GSC_PWESC_H_WATIO_MASK		(7 << 0)
#define GSC_PWESC_H_WATIO(x)		((x) << 0)

/* G-Scawew main scawe howizontaw watio */
#define GSC_MAIN_H_WATIO		0x2C
#define GSC_MAIN_H_WATIO_MASK		(0xfffff << 0)
#define GSC_MAIN_H_WATIO_VAWUE(x)	((x) << 0)

/* G-Scawew main scawe vewticaw watio */
#define GSC_MAIN_V_WATIO		0x30
#define GSC_MAIN_V_WATIO_MASK		(0xfffff << 0)
#define GSC_MAIN_V_WATIO_VAWUE(x)	((x) << 0)

/* G-Scawew input chwominance stwide */
#define GSC_IN_CHWOM_STWIDE		0x3C
#define GSC_IN_CHWOM_STWIDE_MASK	(0x3fff << 0)
#define GSC_IN_CHWOM_STWIDE_VAWUE(x)	((x) << 0)

/* G-Scawew destination image size */
#define GSC_DSTIMG_SIZE			0x40
#define GSC_DSTIMG_HEIGHT_MASK		(0x1fff << 16)
#define GSC_DSTIMG_HEIGHT(x)		((x) << 16)
#define GSC_DSTIMG_WIDTH_MASK		(0x1fff << 0)
#define GSC_DSTIMG_WIDTH(x)		((x) << 0)

/* G-Scawew destination image offset */
#define GSC_DSTIMG_OFFSET		0x44
#define GSC_DSTIMG_OFFSET_Y_MASK	(0x1fff << 16)
#define GSC_DSTIMG_OFFSET_Y(x)		((x) << 16)
#define GSC_DSTIMG_OFFSET_X_MASK	(0x1fff << 0)
#define GSC_DSTIMG_OFFSET_X(x)		((x) << 0)

/* G-Scawew output chwominance stwide */
#define GSC_OUT_CHWOM_STWIDE		0x48
#define GSC_OUT_CHWOM_STWIDE_MASK	(0x3fff << 0)
#define GSC_OUT_CHWOM_STWIDE_VAWUE(x)	((x) << 0)

/* G-Scawew input y addwess mask */
#define GSC_IN_BASE_ADDW_Y_MASK		0x4C
/* G-Scawew input y base addwess */
#define GSC_IN_BASE_ADDW_Y(n)		(0x50 + (n) * 0x4)
/* G-Scawew input y base cuwwent addwess */
#define GSC_IN_BASE_ADDW_Y_CUW(n)	(0x60 + (n) * 0x4)

/* G-Scawew input cb addwess mask */
#define GSC_IN_BASE_ADDW_CB_MASK	0x7C
/* G-Scawew input cb base addwess */
#define GSC_IN_BASE_ADDW_CB(n)		(0x80 + (n) * 0x4)
/* G-Scawew input cb base cuwwent addwess */
#define GSC_IN_BASE_ADDW_CB_CUW(n)	(0x90 + (n) * 0x4)

/* G-Scawew input cw addwess mask */
#define GSC_IN_BASE_ADDW_CW_MASK	0xAC
/* G-Scawew input cw base addwess */
#define GSC_IN_BASE_ADDW_CW(n)		(0xB0 + (n) * 0x4)
/* G-Scawew input cw base cuwwent addwess */
#define GSC_IN_BASE_ADDW_CW_CUW(n)	(0xC0 + (n) * 0x4)

/* G-Scawew input addwess mask */
#define GSC_IN_CUWW_ADDW_INDEX	(0xf << 24)
#define GSC_IN_CUWW_GET_INDEX(x)	((x) >> 24)
#define GSC_IN_BASE_ADDW_PINGPONG(x)	((x) << 16)
#define GSC_IN_BASE_ADDW_MASK		(0xff << 0)

/* G-Scawew output y addwess mask */
#define GSC_OUT_BASE_ADDW_Y_MASK	0x10C
/* G-Scawew output y base addwess */
#define GSC_OUT_BASE_ADDW_Y(n)		(0x110 + (n) * 0x4)

/* G-Scawew output cb addwess mask */
#define GSC_OUT_BASE_ADDW_CB_MASK	0x15C
/* G-Scawew output cb base addwess */
#define GSC_OUT_BASE_ADDW_CB(n)		(0x160 + (n) * 0x4)

/* G-Scawew output cw addwess mask */
#define GSC_OUT_BASE_ADDW_CW_MASK	0x1AC
/* G-Scawew output cw base addwess */
#define GSC_OUT_BASE_ADDW_CW(n)		(0x1B0 + (n) * 0x4)

/* G-Scawew output addwess mask */
#define GSC_OUT_CUWW_ADDW_INDEX		(0xf << 24)
#define GSC_OUT_CUWW_GET_INDEX(x)	((x) >> 24)
#define GSC_OUT_BASE_ADDW_PINGPONG(x)	((x) << 16)
#define GSC_OUT_BASE_ADDW_MASK		(0xffff << 0)

/* G-Scawew howizontaw scawing fiwtew */
#define GSC_HCOEF(n, s, x)	(0x300 + (n) * 0x4 + (s) * 0x30 + (x) * 0x300)

/* G-Scawew vewticaw scawing fiwtew */
#define GSC_VCOEF(n, s, x)	(0x200 + (n) * 0x4 + (s) * 0x30 + (x) * 0x300)

/* G-Scawew BUS contwow */
#define GSC_BUSCON			0xA78
#define GSC_BUSCON_INT_TIME_MASK	(1 << 8)
#define GSC_BUSCON_INT_DATA_TWANS	(0 << 8)
#define GSC_BUSCON_INT_AXI_WESPONSE	(1 << 8)
#define GSC_BUSCON_AWCACHE(x)		((x) << 4)
#define GSC_BUSCON_AWCACHE(x)		((x) << 0)

/* G-Scawew V position */
#define GSC_VPOSITION			0xA7C
#define GSC_VPOS_F(x)			((x) << 0)


/* G-Scawew cwock initiaw count */
#define GSC_CWK_INIT_COUNT		0xC00
#define GSC_CWK_GATE_MODE_INIT_CNT(x)	((x) << 0)

/* G-Scawew cwock snoop count */
#define GSC_CWK_SNOOP_COUNT		0xC04
#define GSC_CWK_GATE_MODE_SNOOP_CNT(x)	((x) << 0)

/* SYSCON. GSCBWK_CFG */
#define SYSWEG_GSCBWK_CFG1		0x0224
#define GSC_BWK_DISP1WB_DEST(x)		(x << 10)
#define GSC_BWK_SW_WESET_WB_DEST(x)	(1 << (18 + x))
#define GSC_BWK_PXWASYNC_WO_MASK_WB(x)	(0 << (14 + x))
#define GSC_BWK_GSCW_WB_IN_SWC_SEW(x)	(1 << (2 * x))
#define SYSWEG_GSCBWK_CFG2		0x2000
#define PXWASYNC_WO_MASK_CAMIF_GSCW(x)	(1 << (x))

#endif /* EXYNOS_WEGS_GSC_H_ */
