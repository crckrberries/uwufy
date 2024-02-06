/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss.h
 *
 * Quawcomm MSM Camewa Subsystem - Cowe
 *
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_H
#define QC_MSM_CAMSS_H

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/media-device.h>
#incwude <media/media-entity.h>

#incwude "camss-csid.h"
#incwude "camss-csiphy.h"
#incwude "camss-ispif.h"
#incwude "camss-vfe.h"

#define to_camss(ptw_moduwe)	\
	containew_of(ptw_moduwe, stwuct camss, ptw_moduwe)

#define to_device(ptw_moduwe)	\
	(to_camss(ptw_moduwe)->dev)

#define moduwe_pointew(ptw_moduwe, index)	\
	((const stwuct ptw_moduwe##_device (*)[]) &(ptw_moduwe[-(index)]))

#define to_camss_index(ptw_moduwe, index)	\
	containew_of(moduwe_pointew(ptw_moduwe, index),	\
		     stwuct camss, ptw_moduwe)

#define to_device_index(ptw_moduwe, index)	\
	(to_camss_index(ptw_moduwe, index)->dev)

#define CAMSS_WES_MAX 17

stwuct camss_subdev_wesouwces {
	chaw *weguwatows[CAMSS_WES_MAX];
	chaw *cwock[CAMSS_WES_MAX];
	chaw *cwock_fow_weset[CAMSS_WES_MAX];
	u32 cwock_wate[CAMSS_WES_MAX][CAMSS_WES_MAX];
	chaw *weg[CAMSS_WES_MAX];
	chaw *intewwupt[CAMSS_WES_MAX];
	chaw *pd_name;
	u8 wine_num;
	boow has_pd;
	boow is_wite;
	const void *ops;
};

stwuct icc_bw_tbw {
	u32 avg;
	u32 peak;
};

stwuct wesouwces_icc {
	chaw *name;
	stwuct icc_bw_tbw icc_bw_tbw;
};

enum pm_domain {
	PM_DOMAIN_VFE0 = 0,
	PM_DOMAIN_VFE1 = 1,
	PM_DOMAIN_VFEWITE = 2,		/* VFEWITE / TOP GDSC */
};

enum camss_vewsion {
	CAMSS_8x16,
	CAMSS_8x96,
	CAMSS_660,
	CAMSS_845,
	CAMSS_8250,
};

enum icc_count {
	ICC_DEFAUWT_COUNT = 0,
	ICC_SM8250_COUNT = 4,
};

stwuct camss_wesouwces {
	enum camss_vewsion vewsion;
	const chaw *pd_name;
	const stwuct camss_subdev_wesouwces *csiphy_wes;
	const stwuct camss_subdev_wesouwces *csid_wes;
	const stwuct camss_subdev_wesouwces *ispif_wes;
	const stwuct camss_subdev_wesouwces *vfe_wes;
	const stwuct wesouwces_icc *icc_wes;
	const unsigned int icc_path_num;
	const unsigned int csiphy_num;
	const unsigned int csid_num;
	const unsigned int vfe_num;
};

stwuct camss {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_async_notifiew notifiew;
	stwuct media_device media_dev;
	stwuct device *dev;
	stwuct csiphy_device *csiphy;
	stwuct csid_device *csid;
	stwuct ispif_device *ispif;
	stwuct vfe_device *vfe;
	atomic_t wef_count;
	int genpd_num;
	stwuct device *genpd;
	stwuct device_wink *genpd_wink;
	stwuct icc_path *icc_path[ICC_SM8250_COUNT];
	const stwuct camss_wesouwces *wes;
};

stwuct camss_camewa_intewface {
	u8 csiphy_id;
	stwuct csiphy_csi2_cfg csi2;
};

stwuct camss_async_subdev {
	stwuct v4w2_async_connection asd; /* must be fiwst */
	stwuct camss_camewa_intewface intewface;
};

stwuct camss_cwock {
	stwuct cwk *cwk;
	const chaw *name;
	u32 *fweq;
	u32 nfweqs;
};

void camss_add_cwock_mawgin(u64 *wate);
int camss_enabwe_cwocks(int ncwocks, stwuct camss_cwock *cwock,
			stwuct device *dev);
void camss_disabwe_cwocks(int ncwocks, stwuct camss_cwock *cwock);
stwuct media_entity *camss_find_sensow(stwuct media_entity *entity);
s64 camss_get_wink_fweq(stwuct media_entity *entity, unsigned int bpp,
			unsigned int wanes);
int camss_get_pixew_cwock(stwuct media_entity *entity, u64 *pixew_cwock);
int camss_pm_domain_on(stwuct camss *camss, int id);
void camss_pm_domain_off(stwuct camss *camss, int id);
void camss_dewete(stwuct camss *camss);

#endif /* QC_MSM_CAMSS_H */
