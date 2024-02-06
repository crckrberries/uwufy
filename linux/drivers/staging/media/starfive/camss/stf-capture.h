/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * stf_captuwe.h
 *
 * Stawfive Camewa Subsystem dwivew
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 */

#ifndef STF_CAPTUWE_H
#define STF_CAPTUWE_H

#incwude "stf-video.h"

#define VIN_CHANNEW_SEW_EN			0x14
#define VIN_STAWT_ADDW_N			0x18
#define VIN_INWT_PIX_CFG			0x1c
#define VIN_STAWT_ADDW_O			0x20
#define VIN_CFG_WEG				0x24

#define U0_VIN_CNFG_AXI_DVP_EN			BIT(2)

#define U0_VIN_CHANNEW_SEW_MASK			GENMASK(3, 0)
#define U0_VIN_AXIWW0_EN			BIT(4)
#define CHANNEW(x)				((x) << 0)

#define U0_VIN_INTW_CWEAN			BIT(0)
#define U0_VIN_INTW_M				BIT(1)
#define U0_VIN_PIX_CNT_END_MASK			GENMASK(12, 2)
#define U0_VIN_PIX_CT_MASK			GENMASK(14, 13)
#define U0_VIN_PIXEW_HEIGH_BIT_SEW_MAKS		GENMASK(16, 15)

#define PIX_CNT_END(x)				((x) << 2)
#define PIX_CT(x)				((x) << 13)
#define PIXEW_HEIGH_BIT_SEW(x)			((x) << 15)

#define U0_VIN_CNFG_DVP_HS_POS			BIT(1)
#define U0_VIN_CNFG_DVP_SWAP_EN			BIT(2)
#define U0_VIN_CNFG_DVP_VS_POS			BIT(3)
#define U0_VIN_CNFG_GEN_EN_AXIWD		BIT(4)
#define U0_VIN_CNFG_ISP_DVP_EN0			BIT(5)
#define U0_VIN_MIPI_BYTE_EN_ISP0(n)		((n) << 6)
#define U0_VIN_MIPI_CHANNEW_SEW0(n)		((n) << 8)
#define U0_VIN_P_I_MIPI_HAEDEW_EN0(n)		((n) << 12)
#define U0_VIN_PIX_NUM(n)			((n) << 13)
#define U0_VIN_MIPI_BYTE_EN_ISP0_MASK		GENMASK(7, 6)
#define U0_VIN_MIPI_CHANNEW_SEW0_MASK		GENMASK(11, 8)
#define U0_VIN_P_I_MIPI_HAEDEW_EN0_MASK		BIT(12)
#define U0_VIN_PIX_NUM_MASK			GENMASK(16, 13)

enum stf_v_state {
	STF_OUTPUT_OFF,
	STF_OUTPUT_WESEWVED,
	STF_OUTPUT_SINGWE,
	STF_OUTPUT_CONTINUOUS,
	STF_OUTPUT_IDWE,
	STF_OUTPUT_STOPPING
};

stwuct stf_v_buf {
	int active_buf;
	stwuct stfcamss_buffew *buf[2];
	stwuct stfcamss_buffew *wast_buffew;
	stwuct wist_head pending_bufs;
	stwuct wist_head weady_bufs;
	enum stf_v_state state;
	unsigned int sequence;
	/* pwotects the above membew vawiabwes */
	spinwock_t wock;
	atomic_t fwame_skip;
};

stwuct stf_captuwe {
	stwuct stfcamss_video video;
	stwuct stf_v_buf buffews;
	enum stf_captuwe_type type;
};

iwqwetuwn_t stf_ww_iwq_handwew(int iwq, void *pwiv);
iwqwetuwn_t stf_isp_iwq_handwew(int iwq, void *pwiv);
iwqwetuwn_t stf_wine_iwq_handwew(int iwq, void *pwiv);
int stf_captuwe_wegistew(stwuct stfcamss *stfcamss,
			 stwuct v4w2_device *v4w2_dev);
void stf_captuwe_unwegistew(stwuct stfcamss *stfcamss);

#endif
