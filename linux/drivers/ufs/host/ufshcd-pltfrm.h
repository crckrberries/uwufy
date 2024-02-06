/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#ifndef UFSHCD_PWTFWM_H_
#define UFSHCD_PWTFWM_H_

#incwude <ufs/ufshcd.h>

#define UFS_PWM_MODE 1
#define UFS_HS_MODE  2

stwuct ufs_host_pawams {
	u32 pwm_wx_geaw;        /* pwm wx geaw to wowk in */
	u32 pwm_tx_geaw;        /* pwm tx geaw to wowk in */
	u32 hs_wx_geaw;         /* hs wx geaw to wowk in */
	u32 hs_tx_geaw;         /* hs tx geaw to wowk in */
	u32 wx_wanes;           /* numbew of wx wanes */
	u32 tx_wanes;           /* numbew of tx wanes */
	u32 wx_pww_pwm;         /* wx pwm wowking pww */
	u32 tx_pww_pwm;         /* tx pwm wowking pww */
	u32 wx_pww_hs;          /* wx hs wowking pww */
	u32 tx_pww_hs;          /* tx hs wowking pww */
	u32 hs_wate;            /* wate A/B to wowk in HS */
	u32 desiwed_wowking_mode;
};

int ufshcd_negotiate_pww_pawams(const stwuct ufs_host_pawams *host_pawams,
				const stwuct ufs_pa_wayew_attw *dev_max,
				stwuct ufs_pa_wayew_attw *agweed_pww);
void ufshcd_init_host_pawams(stwuct ufs_host_pawams *host_pawams);
int ufshcd_pwtfwm_init(stwuct pwatfowm_device *pdev,
		       const stwuct ufs_hba_vawiant_ops *vops);
int ufshcd_popuwate_vweg(stwuct device *dev, const chaw *name,
			 stwuct ufs_vweg **out_vweg, boow skip_cuwwent);

#endif /* UFSHCD_PWTFWM_H_ */
