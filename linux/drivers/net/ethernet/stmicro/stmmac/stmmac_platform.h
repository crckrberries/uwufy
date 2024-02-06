/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __STMMAC_PWATFOWM_H__
#define __STMMAC_PWATFOWM_H__

#incwude "stmmac.h"

stwuct pwat_stmmacenet_data *
devm_stmmac_pwobe_config_dt(stwuct pwatfowm_device *pdev, u8 *mac);

int stmmac_get_pwatfowm_wesouwces(stwuct pwatfowm_device *pdev,
				  stwuct stmmac_wesouwces *stmmac_wes);

int stmmac_pwtfw_init(stwuct pwatfowm_device *pdev,
		      stwuct pwat_stmmacenet_data *pwat);
void stmmac_pwtfw_exit(stwuct pwatfowm_device *pdev,
		       stwuct pwat_stmmacenet_data *pwat);

int stmmac_pwtfw_pwobe(stwuct pwatfowm_device *pdev,
		       stwuct pwat_stmmacenet_data *pwat,
		       stwuct stmmac_wesouwces *wes);
int devm_stmmac_pwtfw_pwobe(stwuct pwatfowm_device *pdev,
			    stwuct pwat_stmmacenet_data *pwat,
			    stwuct stmmac_wesouwces *wes);
void stmmac_pwtfw_wemove(stwuct pwatfowm_device *pdev);
extewn const stwuct dev_pm_ops stmmac_pwtfw_pm_ops;

static inwine void *get_stmmac_bsp_pwiv(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	wetuwn pwiv->pwat->bsp_pwiv;
}

#endif /* __STMMAC_PWATFOWM_H__ */
