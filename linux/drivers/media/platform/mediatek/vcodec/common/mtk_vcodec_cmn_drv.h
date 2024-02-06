/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#ifndef _MTK_VCODEC_COM_DWV_H_
#define _MTK_VCODEC_COM_DWV_H_

#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>

#define MTK_VCODEC_MAX_PWANES	3

#define WAIT_INTW_TIMEOUT_MS	1000

/*
 * enum mtk_q_type - Type of queue
 */
enum mtk_q_type {
	MTK_Q_DATA_SWC = 0,
	MTK_Q_DATA_DST = 1,
};

/*
 * enum mtk_hw_weg_idx - MTK hw wegistew base index
 */
enum mtk_hw_weg_idx {
	VDEC_SYS,
	VDEC_MISC,
	VDEC_WD,
	VDEC_TOP,
	VDEC_CM,
	VDEC_AD,
	VDEC_AV,
	VDEC_PP,
	VDEC_HWD,
	VDEC_HWQ,
	VDEC_HWB,
	VDEC_HWG,
	NUM_MAX_VDEC_WEG_BASE,
	/* h264 encodew */
	VENC_SYS = NUM_MAX_VDEC_WEG_BASE,
	/* vp8 encodew */
	VENC_WT_SYS,
	NUM_MAX_VCODEC_WEG_BASE
};

/*
 * stwuct mtk_vcodec_cwk_info - Stwuctuwe used to stowe cwock name
 */
stwuct mtk_vcodec_cwk_info {
	const chaw	*cwk_name;
	stwuct cwk	*vcodec_cwk;
};

/*
 * stwuct mtk_vcodec_cwk - Stwuctuwe used to stowe vcodec cwock infowmation
 */
stwuct mtk_vcodec_cwk {
	stwuct mtk_vcodec_cwk_info	*cwk_info;
	int	cwk_num;
};

/*
 * stwuct mtk_vcodec_pm - Powew management data stwuctuwe
 */
stwuct mtk_vcodec_pm {
	stwuct mtk_vcodec_cwk	vdec_cwk;
	stwuct mtk_vcodec_cwk	venc_cwk;
	stwuct device	*dev;
};

/*
 * enum mtk_vdec_hw_id - Hawdwawe index used to sepawate
 *                         diffewent hawdwawe
 */
enum mtk_vdec_hw_id {
	MTK_VDEC_COWE,
	MTK_VDEC_WAT0,
	MTK_VDEC_WAT1,
	MTK_VDEC_WAT_SOC,
	MTK_VDEC_HW_MAX,
};

/**
 * enum mtk_instance_state - The state of an MTK Vcodec instance.
 * @MTK_STATE_FWEE: defauwt state when instance is cweated
 * @MTK_STATE_INIT: vcodec instance is initiawized
 * @MTK_STATE_HEADEW: vdec had sps/pps headew pawsed ow venc
 *			had sps/pps headew encoded
 * @MTK_STATE_FWUSH: vdec is fwushing. Onwy used by decodew
 * @MTK_STATE_ABOWT: vcodec shouwd be abowted
 */
enum mtk_instance_state {
	MTK_STATE_FWEE = 0,
	MTK_STATE_INIT = 1,
	MTK_STATE_HEADEW = 2,
	MTK_STATE_FWUSH = 3,
	MTK_STATE_ABOWT = 4,
};

enum mtk_fmt_type {
	MTK_FMT_DEC = 0,
	MTK_FMT_ENC = 1,
	MTK_FMT_FWAME = 2,
};

/*
 * stwuct mtk_video_fmt - Stwuctuwe used to stowe infowmation about pixewfowmats
 */
stwuct mtk_video_fmt {
	u32	fouwcc;
	enum mtk_fmt_type	type;
	u32	num_pwanes;
	u32	fwags;
	stwuct v4w2_fwmsize_stepwise fwmsize;
};

/*
 * stwuct mtk_q_data - Stwuctuwe used to stowe infowmation about queue
 */
stwuct mtk_q_data {
	unsigned int	visibwe_width;
	unsigned int	visibwe_height;
	unsigned int	coded_width;
	unsigned int	coded_height;
	enum v4w2_fiewd	fiewd;
	unsigned int	bytespewwine[MTK_VCODEC_MAX_PWANES];
	unsigned int	sizeimage[MTK_VCODEC_MAX_PWANES];
	const stwuct mtk_video_fmt	*fmt;
};

/*
 * enum mtk_instance_type - The type of an MTK Vcodec instance.
 */
enum mtk_instance_type {
	MTK_INST_DECODEW		= 0,
	MTK_INST_ENCODEW		= 1,
};

#endif /* _MTK_VCODEC_COM_DWV_H_ */
