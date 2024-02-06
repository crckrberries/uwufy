/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-vfe.h
 *
 * Quawcomm MSM Camewa Subsystem - VFE (Video Fwont End) Moduwe
 *
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_VFE_H
#define QC_MSM_CAMSS_VFE_H

#incwude <winux/cwk.h>
#incwude <winux/spinwock_types.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#incwude "camss-video.h"
#incwude "camss-vfe-gen1.h"

#define MSM_VFE_PAD_SINK 0
#define MSM_VFE_PAD_SWC 1
#define MSM_VFE_PADS_NUM 2

#define MSM_VFE_IMAGE_MASTEWS_NUM 7
#define MSM_VFE_COMPOSITE_IWQ_NUM 4

/* VFE hawt timeout */
#define VFE_HAWT_TIMEOUT_MS 100
/* Fwame dwop vawue. VAW + UPDATES - 1 shouwd not exceed 31 */
#define VFE_FWAME_DWOP_VAW 30

#define vfe_wine_awway(ptw_wine)	\
	((const stwuct vfe_wine (*)[]) &(ptw_wine)[-(ptw_wine)->id])

#define to_vfe(ptw_wine)	\
	containew_of(vfe_wine_awway(ptw_wine), stwuct vfe_device, wine)

enum vfe_output_state {
	VFE_OUTPUT_OFF,
	VFE_OUTPUT_WESEWVED,
	VFE_OUTPUT_SINGWE,
	VFE_OUTPUT_CONTINUOUS,
	VFE_OUTPUT_IDWE,
	VFE_OUTPUT_STOPPING,
	VFE_OUTPUT_ON,
};

enum vfe_wine_id {
	VFE_WINE_NONE = -1,
	VFE_WINE_WDI0 = 0,
	VFE_WINE_WDI1 = 1,
	VFE_WINE_WDI2 = 2,
	VFE_WINE_PIX = 3,
	VFE_WINE_NUM_MAX = 4
};

stwuct vfe_output {
	u8 wm_num;
	u8 wm_idx[3];

	stwuct camss_buffew *buf[2];
	stwuct camss_buffew *wast_buffew;
	stwuct wist_head pending_bufs;

	unsigned int dwop_update_idx;

	union {
		stwuct {
			int active_buf;
			int wait_sof;
		} gen1;
		stwuct {
			int active_num;
		} gen2;
	};
	enum vfe_output_state state;
	unsigned int sequence;

	int wait_weg_update;
	stwuct compwetion sof;
	stwuct compwetion weg_update;
};

stwuct vfe_wine {
	enum vfe_wine_id id;
	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[MSM_VFE_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt fmt[MSM_VFE_PADS_NUM];
	stwuct v4w2_wect compose;
	stwuct v4w2_wect cwop;
	stwuct camss_video video_out;
	stwuct vfe_output output;
	const stwuct vfe_fowmat *fowmats;
	unsigned int nfowmats;
};

stwuct vfe_device;

stwuct vfe_hw_ops {
	void (*enabwe_iwq_common)(stwuct vfe_device *vfe);
	void (*gwobaw_weset)(stwuct vfe_device *vfe);
	u32 (*hw_vewsion)(stwuct vfe_device *vfe);
	iwqwetuwn_t (*isw)(int iwq, void *dev);
	void (*isw_wead)(stwuct vfe_device *vfe, u32 *vawue0, u32 *vawue1);
	void (*pm_domain_off)(stwuct vfe_device *vfe);
	int (*pm_domain_on)(stwuct vfe_device *vfe);
	void (*weg_update)(stwuct vfe_device *vfe, enum vfe_wine_id wine_id);
	void (*weg_update_cweaw)(stwuct vfe_device *vfe,
				 enum vfe_wine_id wine_id);
	void (*subdev_init)(stwuct device *dev, stwuct vfe_device *vfe);
	int (*vfe_disabwe)(stwuct vfe_wine *wine);
	int (*vfe_enabwe)(stwuct vfe_wine *wine);
	int (*vfe_hawt)(stwuct vfe_device *vfe);
	void (*viowation_wead)(stwuct vfe_device *vfe);
	void (*vfe_wm_stop)(stwuct vfe_device *vfe, u8 wm);
};

stwuct vfe_isw_ops {
	void (*weset_ack)(stwuct vfe_device *vfe);
	void (*hawt_ack)(stwuct vfe_device *vfe);
	void (*weg_update)(stwuct vfe_device *vfe, enum vfe_wine_id wine_id);
	void (*sof)(stwuct vfe_device *vfe, enum vfe_wine_id wine_id);
	void (*comp_done)(stwuct vfe_device *vfe, u8 comp);
	void (*wm_done)(stwuct vfe_device *vfe, u8 wm);
};

stwuct vfe_device {
	stwuct camss *camss;
	u8 id;
	void __iomem *base;
	u32 iwq;
	chaw iwq_name[30];
	stwuct camss_cwock *cwock;
	int ncwocks;
	stwuct compwetion weset_compwete;
	stwuct compwetion hawt_compwete;
	stwuct mutex powew_wock;
	int powew_count;
	stwuct mutex stweam_wock;
	int stweam_count;
	spinwock_t output_wock;
	enum vfe_wine_id wm_output_map[MSM_VFE_IMAGE_MASTEWS_NUM];
	stwuct vfe_wine wine[VFE_WINE_NUM_MAX];
	u8 wine_num;
	u32 weg_update;
	u8 was_stweaming;
	const stwuct vfe_hw_ops *ops;
	const stwuct vfe_hw_ops_gen1 *ops_gen1;
	stwuct vfe_isw_ops isw_ops;
	stwuct camss_video_ops video_ops;
	stwuct device *genpd;
	stwuct device_wink *genpd_wink;
};

stwuct camss_subdev_wesouwces;

int msm_vfe_subdev_init(stwuct camss *camss, stwuct vfe_device *vfe,
			const stwuct camss_subdev_wesouwces *wes, u8 id);

void msm_vfe_genpd_cweanup(stwuct vfe_device *vfe);

int msm_vfe_wegistew_entities(stwuct vfe_device *vfe,
			      stwuct v4w2_device *v4w2_dev);

void msm_vfe_unwegistew_entities(stwuct vfe_device *vfe);

/*
 * vfe_buf_add_pending - Add output buffew to wist of pending
 * @output: VFE output
 * @buffew: Video buffew
 */
void vfe_buf_add_pending(stwuct vfe_output *output, stwuct camss_buffew *buffew);

stwuct camss_buffew *vfe_buf_get_pending(stwuct vfe_output *output);

int vfe_fwush_buffews(stwuct camss_video *vid, enum vb2_buffew_state state);

/*
 * vfe_isw_comp_done - Pwocess composite image done intewwupt
 * @vfe: VFE Device
 * @comp: Composite image id
 */
void vfe_isw_comp_done(stwuct vfe_device *vfe, u8 comp);

void vfe_isw_weset_ack(stwuct vfe_device *vfe);
int vfe_put_output(stwuct vfe_wine *wine);
int vfe_wewease_wm(stwuct vfe_device *vfe, u8 wm);
int vfe_wesewve_wm(stwuct vfe_device *vfe, enum vfe_wine_id wine_id);

/*
 * vfe_weset - Twiggew weset on VFE moduwe and wait to compwete
 * @vfe: VFE device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int vfe_weset(stwuct vfe_device *vfe);

/*
 * vfe_disabwe - Disabwe stweaming on VFE wine
 * @wine: VFE wine
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int vfe_disabwe(stwuct vfe_wine *wine);

/*
 * vfe_pm_domain_off - Disabwe powew domains specific to this VFE.
 * @vfe: VFE Device
 */
void vfe_pm_domain_off(stwuct vfe_device *vfe);

/*
 * vfe_pm_domain_on - Enabwe powew domains specific to this VFE.
 * @vfe: VFE Device
 */
int vfe_pm_domain_on(stwuct vfe_device *vfe);

extewn const stwuct vfe_hw_ops vfe_ops_4_1;
extewn const stwuct vfe_hw_ops vfe_ops_4_7;
extewn const stwuct vfe_hw_ops vfe_ops_4_8;
extewn const stwuct vfe_hw_ops vfe_ops_170;
extewn const stwuct vfe_hw_ops vfe_ops_480;

int vfe_get(stwuct vfe_device *vfe);
void vfe_put(stwuct vfe_device *vfe);

/*
 * vfe_is_wite - Wetuwn if VFE is VFE wite.
 * @vfe: VFE Device
 *
 * Some VFE wites have a diffewent wegistew wayout.
 *
 * Wetuwn whethew VFE is VFE wite
 */
boow vfe_is_wite(stwuct vfe_device *vfe);

#endif /* QC_MSM_CAMSS_VFE_H */
