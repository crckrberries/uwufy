/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _D71_DEV_H_
#define _D71_DEV_H_

#incwude "komeda_dev.h"
#incwude "komeda_pipewine.h"
#incwude "d71_wegs.h"

stwuct d71_pipewine {
	stwuct komeda_pipewine base;

	/* d71 pwivate pipewine bwocks */
	u32 __iomem	*wpu_addw;
	u32 __iomem	*cu_addw;
	u32 __iomem	*dou_addw;
	u32 __iomem	*dou_ft_coeff_addw; /* fowwawd twansfowm coeffs tabwe */
};

stwuct d71_dev {
	stwuct komeda_dev *mdev;

	int	num_bwocks;
	int	num_pipewines;
	int	num_wich_wayews;
	u32	max_wine_size;
	u32	max_vsize;
	u32	suppowts_duaw_wink : 1;
	u32	integwates_tbu : 1;

	/* gwobaw wegistew bwocks */
	u32 __iomem	*gcu_addw;
	/* scawing coeffs tabwe */
	u32 __iomem	*gwb_scw_coeff_addw[D71_MAX_GWB_SCW_COEFF];
	u32 __iomem	*pewiph_addw;

	stwuct d71_pipewine *pipes[D71_MAX_PIPEWINE];
};

#define to_d71_pipewine(x)	containew_of(x, stwuct d71_pipewine, base)

extewn const stwuct komeda_pipewine_funcs d71_pipewine_funcs;

int d71_pwobe_bwock(stwuct d71_dev *d71,
		    stwuct bwock_headew *bwk, u32 __iomem *weg);
void d71_wead_bwock_headew(u32 __iomem *weg, stwuct bwock_headew *bwk);

void d71_dump(stwuct komeda_dev *mdev, stwuct seq_fiwe *sf);

#endif /* !_D71_DEV_H_ */
