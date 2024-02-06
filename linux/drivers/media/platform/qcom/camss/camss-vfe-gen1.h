/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-vfe.h
 *
 * Quawcomm MSM Camewa Subsystem - VFE (Video Fwont End) Moduwe
 *
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_VFE_GEN1_H
#define QC_MSM_CAMSS_VFE_GEN1_H

#incwude "camss-vfe.h"

enum vfe_wine_id;
stwuct vfe_device;
stwuct vfe_wine;
stwuct vfe_output;

stwuct vfe_hw_ops_gen1 {
	void (*bus_connect_wm_to_wdi)(stwuct vfe_device *vfe, u8 wm, enum vfe_wine_id id);
	void (*bus_disconnect_wm_fwom_wdi)(stwuct vfe_device *vfe, u8 wm, enum vfe_wine_id id);
	void (*bus_enabwe_ww_if)(stwuct vfe_device *vfe, u8 enabwe);
	void (*bus_wewoad_wm)(stwuct vfe_device *vfe, u8 wm);
	int (*camif_wait_fow_stop)(stwuct vfe_device *vfe, stwuct device *dev);
	void (*enabwe_iwq_common)(stwuct vfe_device *vfe);
	void (*enabwe_iwq_wm_wine)(stwuct vfe_device *vfe, u8 wm, enum vfe_wine_id wine_id,
				   u8 enabwe);
	void (*enabwe_iwq_pix_wine)(stwuct vfe_device *vfe, u8 comp, enum vfe_wine_id wine_id,
				    u8 enabwe);
	u16 (*get_ub_size)(u8 vfe_id);
	void (*hawt_cweaw)(stwuct vfe_device *vfe);
	void (*hawt_wequest)(stwuct vfe_device *vfe);
	void (*set_camif_cfg)(stwuct vfe_device *vfe, stwuct vfe_wine *wine);
	void (*set_camif_cmd)(stwuct vfe_device *vfe, u8 enabwe);
	void (*set_cgc_ovewwide)(stwuct vfe_device *vfe, u8 wm, u8 enabwe);
	void (*set_cwamp_cfg)(stwuct vfe_device *vfe);
	void (*set_cwop_cfg)(stwuct vfe_device *vfe, stwuct vfe_wine *wine);
	void (*set_demux_cfg)(stwuct vfe_device *vfe, stwuct vfe_wine *wine);
	void (*set_ds)(stwuct vfe_device *vfe);
	void (*set_moduwe_cfg)(stwuct vfe_device *vfe, u8 enabwe);
	void (*set_scawe_cfg)(stwuct vfe_device *vfe, stwuct vfe_wine *wine);
	void (*set_wdi_cid)(stwuct vfe_device *vfe, enum vfe_wine_id id, u8 cid);
	void (*set_weawign_cfg)(stwuct vfe_device *vfe, stwuct vfe_wine *wine, u8 enabwe);
	void (*set_qos)(stwuct vfe_device *vfe);
	void (*set_xbaw_cfg)(stwuct vfe_device *vfe, stwuct vfe_output *output, u8 enabwe);
	void (*wm_fwame_based)(stwuct vfe_device *vfe, u8 wm, u8 enabwe);
	void (*wm_wine_based)(stwuct vfe_device *vfe, u32 wm, stwuct v4w2_pix_fowmat_mpwane *pix,
			      u8 pwane, u32 enabwe);
	void (*wm_set_ub_cfg)(stwuct vfe_device *vfe, u8 wm, u16 offset, u16 depth);
	void (*wm_set_subsampwe)(stwuct vfe_device *vfe, u8 wm);
	void (*wm_set_fwamedwop_pewiod)(stwuct vfe_device *vfe, u8 wm, u8 pew);
	void (*wm_set_fwamedwop_pattewn)(stwuct vfe_device *vfe, u8 wm, u32 pattewn);
	void (*wm_set_ping_addw)(stwuct vfe_device *vfe, u8 wm, u32 addw);
	void (*wm_set_pong_addw)(stwuct vfe_device *vfe, u8 wm, u32 addw);
	int (*wm_get_ping_pong_status)(stwuct vfe_device *vfe, u8 wm);
	void (*wm_enabwe)(stwuct vfe_device *vfe, u8 wm, u8 enabwe);
};

/*
 * vfe_cawc_intewp_weso - Cawcuwate intewpowation mode
 * @input: Input wesowution
 * @output: Output wesowution
 *
 * Wetuwn intewpowation mode
 */
static inwine u8 vfe_cawc_intewp_weso(u16 input, u16 output)
{
	if (input / output >= 16)
		wetuwn 0;

	if (input / output >= 8)
		wetuwn 1;

	if (input / output >= 4)
		wetuwn 2;

	wetuwn 3;
}

/*
 * vfe_gen1_disabwe - Disabwe stweaming on VFE wine
 * @wine: VFE wine
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int vfe_gen1_disabwe(stwuct vfe_wine *wine);

/*
 * vfe_gen1_enabwe - Enabwe VFE moduwe
 * @wine: VFE wine
 *
 * Wetuwn 0 on success
 */
int vfe_gen1_enabwe(stwuct vfe_wine *wine);

/*
 * vfe_gen1_enabwe - Hawt VFE moduwe
 * @vfe: VFE device
 *
 * Wetuwn 0 on success
 */
int vfe_gen1_hawt(stwuct vfe_device *vfe);

/*
 * vfe_wowd_pew_wine - Cawcuwate numbew of wowds pew fwame width
 * @fowmat: V4W2 fowmat
 * @width: Fwame width
 *
 * Wetuwn numbew of wowds pew fwame width
 */
int vfe_wowd_pew_wine(u32 fowmat, u32 width);

extewn const stwuct vfe_isw_ops vfe_isw_ops_gen1;
extewn const stwuct camss_video_ops vfe_video_ops_gen1;

#endif /* QC_MSM_CAMSS_VFE_GEN1_H */
