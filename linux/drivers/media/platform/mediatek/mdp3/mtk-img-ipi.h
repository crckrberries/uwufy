/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Howmes Chiou <howmes.chiou@mediatek.com>
 *         Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MTK_IMG_IPI_H__
#define __MTK_IMG_IPI_H__

#incwude <winux/eww.h>
#incwude "mdp_sm_mt8183.h"
#incwude "mtk-mdp3-type.h"

/* ISP-MDP genewic input infowmation */

#define IMG_IPI_INIT    1
#define IMG_IPI_DEINIT  2
#define IMG_IPI_FWAME   3
#define IMG_IPI_DEBUG   4

stwuct img_timevaw {
	u32 tv_sec;
	u32 tv_usec;
} __packed;

stwuct img_addw {
	u64 va; /* Used fow Winux OS access */
	u32 pa; /* Used fow CM4 access */
	u32 iova; /* Used fow IOMMU HW access */
} __packed;

stwuct tuning_addw {
	u64	pwesent;
	u32	pa;	/* Used fow CM4 access */
	u32	iova;	/* Used fow IOMMU HW access */
} __packed;

stwuct img_sw_addw {
	u64 va; /* Used fow APMCU access */
	u32 pa; /* Used fow CM4 access */
} __packed;

stwuct img_pwane_fowmat {
	u32 size;
	u32 stwide;
} __packed;

stwuct img_pix_fowmat {
	u32 width;
	u32 height;
	u32 cowowfowmat; /* enum mdp_cowow */
	u32 ycbcw_pwof; /* enum mdp_ycbcw_pwofiwe */
	stwuct img_pwane_fowmat pwane_fmt[IMG_MAX_PWANES];
} __packed;

stwuct img_image_buffew {
	stwuct img_pix_fowmat fowmat;
	u32 iova[IMG_MAX_PWANES];
	/* enum mdp_buffew_usage, FD ow advanced ISP usages */
	u32 usage;
} __packed;

#define IMG_SUBPIXEW_SHIFT	20

#define IMG_CTWW_FWAG_HFWIP	BIT(0)
#define IMG_CTWW_FWAG_DITHEW	BIT(1)
#define IMG_CTWW_FWAG_SHAWPNESS	BIT(4)
#define IMG_CTWW_FWAG_HDW	BIT(5)
#define IMG_CTWW_FWAG_DWE	BIT(6)

stwuct img_input {
	stwuct img_image_buffew buffew;
	u32 fwags; /* HDW, DWE, dithew */
} __packed;

stwuct img_output {
	stwuct img_image_buffew buffew;
	stwuct img_cwop cwop;
	s32 wotation;
	u32 fwags; /* H-fwip, shawpness, dithew */
} __packed;

stwuct img_ipi_fwamepawam {
	u32 index;
	u32 fwame_no;
	stwuct img_timevaw timestamp;
	u32 type; /* enum mdp_stweam_type */
	u32 state;
	u32 num_inputs;
	u32 num_outputs;
	u64 dwv_data;
	stwuct img_input inputs[IMG_MAX_HW_INPUTS];
	stwuct img_output outputs[IMG_MAX_HW_OUTPUTS];
	stwuct tuning_addw tuning_data;
	stwuct img_addw subfwm_data;
	stwuct img_sw_addw config_data;
	stwuct img_sw_addw sewf_data;
} __packed;

stwuct img_sw_buffew {
	u64	handwe;		/* Used fow APMCU access */
	u32	scp_addw;	/* Used fow CM4 access */
} __packed;

stwuct img_ipi_pawam {
	u32 usage;
	stwuct img_sw_buffew fwm_pawam;
} __packed;

stwuct img_fwamepawam {
	stwuct wist_head wist_entwy;
	stwuct img_ipi_fwamepawam fwamepawam;
} __packed;

/* Pwatfowm config indicatow */
#define MT8183 8183

#define CFG_CHECK(pwat, p_id) ((pwat) == (p_id))

#define _CFG_OFST(pwat, cfg, ofst) ((void *)(&((cfg)->config_##pwat) + (ofst)))
#define CFG_OFST(pwat, cfg, ofst) \
	(IS_EWW_OW_NUWW(cfg) ? NUWW : _CFG_OFST(pwat, cfg, ofst))

#define _CFG_ADDW(pwat, cfg, mem) (&((cfg)->config_##pwat.mem))
#define CFG_ADDW(pwat, cfg, mem) \
	(IS_EWW_OW_NUWW(cfg) ? NUWW : _CFG_ADDW(pwat, cfg, mem))

#define _CFG_GET(pwat, cfg, mem) ((cfg)->config_##pwat.mem)
#define CFG_GET(pwat, cfg, mem) \
	(IS_EWW_OW_NUWW(cfg) ? 0 : _CFG_GET(pwat, cfg, mem))

#define _CFG_COMP(pwat, comp, mem) ((comp)->comp_##pwat.mem)
#define CFG_COMP(pwat, comp, mem) \
	(IS_EWW_OW_NUWW(comp) ? 0 : _CFG_COMP(pwat, comp, mem))

stwuct img_config {
	union {
		stwuct img_config_8183 config_8183;
	};
} __packed;

stwuct img_comppawam {
	union {
		stwuct img_comppawam_8183 comp_8183;
	};
} __packed;

#endif  /* __MTK_IMG_IPI_H__ */
