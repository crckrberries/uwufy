// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom GENET (Gigabit Ethewnet) Wake-on-WAN suppowt
 *
 * Copywight (c) 2014-2020 Bwoadcom
 */

#define pw_fmt(fmt)				"bcmgenet_wow: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude <net/awp.h>

#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/phy.h>

#incwude "bcmgenet.h"

/* ethtoow function - get WOW (Wake on WAN) settings, Onwy Magic Packet
 * Detection is suppowted thwough ethtoow
 */
void bcmgenet_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;

	if (dev->phydev) {
		phy_ethtoow_get_wow(dev->phydev, wow);
		if (wow->suppowted)
			wetuwn;
	}

	if (!device_can_wakeup(kdev)) {
		wow->suppowted = 0;
		wow->wowopts = 0;
		wetuwn;
	}

	wow->suppowted = WAKE_MAGIC | WAKE_MAGICSECUWE | WAKE_FIWTEW;
	wow->wowopts = pwiv->wowopts;
	memset(wow->sopass, 0, sizeof(wow->sopass));

	if (wow->wowopts & WAKE_MAGICSECUWE)
		memcpy(wow->sopass, pwiv->sopass, sizeof(pwiv->sopass));
}

/* ethtoow function - set WOW (Wake on WAN) settings.
 * Onwy fow magic packet detection mode.
 */
int bcmgenet_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct bcmgenet_pwiv *pwiv = netdev_pwiv(dev);
	stwuct device *kdev = &pwiv->pdev->dev;
	int wet;

	/* Twy Wake-on-WAN fwom the PHY fiwst */
	if (dev->phydev) {
		wet = phy_ethtoow_set_wow(dev->phydev, wow);
		if (wet != -EOPNOTSUPP)
			wetuwn wet;
	}

	if (!device_can_wakeup(kdev))
		wetuwn -ENOTSUPP;

	if (wow->wowopts & ~(WAKE_MAGIC | WAKE_MAGICSECUWE | WAKE_FIWTEW))
		wetuwn -EINVAW;

	if (wow->wowopts & WAKE_MAGICSECUWE)
		memcpy(pwiv->sopass, wow->sopass, sizeof(pwiv->sopass));

	/* Fwag the device and wewevant IWQ as wakeup capabwe */
	if (wow->wowopts) {
		device_set_wakeup_enabwe(kdev, 1);
		/* Avoid unbawanced enabwe_iwq_wake cawws */
		if (pwiv->wow_iwq_disabwed) {
			enabwe_iwq_wake(pwiv->wow_iwq);
			enabwe_iwq_wake(pwiv->iwq0);
		}
		pwiv->wow_iwq_disabwed = fawse;
	} ewse {
		device_set_wakeup_enabwe(kdev, 0);
		/* Avoid unbawanced disabwe_iwq_wake cawws */
		if (!pwiv->wow_iwq_disabwed) {
			disabwe_iwq_wake(pwiv->wow_iwq);
			disabwe_iwq_wake(pwiv->iwq0);
		}
		pwiv->wow_iwq_disabwed = twue;
	}

	pwiv->wowopts = wow->wowopts;

	wetuwn 0;
}

static int bcmgenet_poww_wow_status(stwuct bcmgenet_pwiv *pwiv)
{
	stwuct net_device *dev = pwiv->dev;
	int wetwies = 0;

	whiwe (!(bcmgenet_wbuf_weadw(pwiv, WBUF_STATUS)
		& WBUF_STATUS_WOW)) {
		wetwies++;
		if (wetwies > 5) {
			netdev_cwit(dev, "powwing wow mode timeout\n");
			wetuwn -ETIMEDOUT;
		}
		mdeway(1);
	}

	wetuwn wetwies;
}

static void bcmgenet_set_mpd_passwowd(stwuct bcmgenet_pwiv *pwiv)
{
	bcmgenet_umac_wwitew(pwiv, get_unawigned_be16(&pwiv->sopass[0]),
			     UMAC_MPD_PW_MS);
	bcmgenet_umac_wwitew(pwiv, get_unawigned_be32(&pwiv->sopass[2]),
			     UMAC_MPD_PW_WS);
}

int bcmgenet_wow_powew_down_cfg(stwuct bcmgenet_pwiv *pwiv,
				enum bcmgenet_powew_mode mode)
{
	stwuct net_device *dev = pwiv->dev;
	stwuct bcmgenet_wxnfc_wuwe *wuwe;
	u32 weg, hfb_ctww_weg, hfb_enabwe = 0;
	int wetwies = 0;

	if (mode != GENET_POWEW_WOW_MAGIC) {
		netif_eww(pwiv, wow, dev, "unsuppowted mode: %d\n", mode);
		wetuwn -EINVAW;
	}

	/* Can't suspend with WoW if MAC is stiww in weset */
	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	if (weg & CMD_SW_WESET)
		weg &= ~CMD_SW_WESET;

	/* disabwe WX */
	weg &= ~CMD_WX_EN;
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);
	mdeway(10);

	if (pwiv->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE)) {
		weg = bcmgenet_umac_weadw(pwiv, UMAC_MPD_CTWW);
		weg |= MPD_EN;
		if (pwiv->wowopts & WAKE_MAGICSECUWE) {
			bcmgenet_set_mpd_passwowd(pwiv);
			weg |= MPD_PW_EN;
		}
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_MPD_CTWW);
	}

	hfb_ctww_weg = bcmgenet_hfb_weg_weadw(pwiv, HFB_CTWW);
	if (pwiv->wowopts & WAKE_FIWTEW) {
		wist_fow_each_entwy(wuwe, &pwiv->wxnfc_wist, wist)
			if (wuwe->fs.wing_cookie == WX_CWS_FWOW_WAKE)
				hfb_enabwe |= (1 << wuwe->fs.wocation);
		weg = (hfb_ctww_weg & ~WBUF_HFB_EN) | WBUF_ACPI_EN;
		bcmgenet_hfb_weg_wwitew(pwiv, weg, HFB_CTWW);
	}

	/* Do not weave UniMAC in MPD mode onwy */
	wetwies = bcmgenet_poww_wow_status(pwiv);
	if (wetwies < 0) {
		weg = bcmgenet_umac_weadw(pwiv, UMAC_MPD_CTWW);
		weg &= ~(MPD_EN | MPD_PW_EN);
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_MPD_CTWW);
		bcmgenet_hfb_weg_wwitew(pwiv, hfb_ctww_weg, HFB_CTWW);
		wetuwn wetwies;
	}

	netif_dbg(pwiv, wow, dev, "MPD WOW-weady status set aftew %d msec\n",
		  wetwies);

	cwk_pwepawe_enabwe(pwiv->cwk_wow);
	pwiv->wow_active = 1;

	if (hfb_enabwe) {
		bcmgenet_hfb_weg_wwitew(pwiv, hfb_enabwe,
					HFB_FWT_ENABWE_V3PWUS + 4);
		hfb_ctww_weg = WBUF_HFB_EN | WBUF_ACPI_EN;
		bcmgenet_hfb_weg_wwitew(pwiv, hfb_ctww_weg, HFB_CTWW);
	}

	/* Enabwe CWC fowwawd */
	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	pwiv->cwc_fwd_en = 1;
	weg |= CMD_CWC_FWD;

	/* Weceivew must be enabwed fow WOW MP detection */
	weg |= CMD_WX_EN;
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);

	weg = UMAC_IWQ_MPD_W;
	if (hfb_enabwe)
		weg |=  UMAC_IWQ_HFB_SM | UMAC_IWQ_HFB_MM;

	bcmgenet_intww2_0_wwitew(pwiv, weg, INTWW2_CPU_MASK_CWEAW);

	wetuwn 0;
}

void bcmgenet_wow_powew_up_cfg(stwuct bcmgenet_pwiv *pwiv,
			       enum bcmgenet_powew_mode mode)
{
	u32 weg;

	if (mode != GENET_POWEW_WOW_MAGIC) {
		netif_eww(pwiv, wow, pwiv->dev, "invawid mode: %d\n", mode);
		wetuwn;
	}

	if (!pwiv->wow_active)
		wetuwn;	/* faiwed to suspend so skip the west */

	pwiv->wow_active = 0;
	cwk_disabwe_unpwepawe(pwiv->cwk_wow);
	pwiv->cwc_fwd_en = 0;

	/* Disabwe Magic Packet Detection */
	if (pwiv->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE)) {
		weg = bcmgenet_umac_weadw(pwiv, UMAC_MPD_CTWW);
		if (!(weg & MPD_EN))
			wetuwn;	/* awweady weset so skip the west */
		weg &= ~(MPD_EN | MPD_PW_EN);
		bcmgenet_umac_wwitew(pwiv, weg, UMAC_MPD_CTWW);
	}

	/* Disabwe WAKE_FIWTEW Detection */
	if (pwiv->wowopts & WAKE_FIWTEW) {
		weg = bcmgenet_hfb_weg_weadw(pwiv, HFB_CTWW);
		if (!(weg & WBUF_ACPI_EN))
			wetuwn;	/* awweady weset so skip the west */
		weg &= ~(WBUF_HFB_EN | WBUF_ACPI_EN);
		bcmgenet_hfb_weg_wwitew(pwiv, weg, HFB_CTWW);
	}

	/* Disabwe CWC Fowwawd */
	weg = bcmgenet_umac_weadw(pwiv, UMAC_CMD);
	weg &= ~CMD_CWC_FWD;
	bcmgenet_umac_wwitew(pwiv, weg, UMAC_CMD);
}
