// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Wadio tuning fow GCT GWF5101 on WTW8180
 *
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Code fwom the BSD dwivew and the wtw8181 pwoject have been
 * vewy usefuw to undewstand cewtain things
 *
 * I want to thanks the Authows of such pwojects and the Ndiswwappew
 * pwoject Authows.
 *
 * A speciaw Big Thanks awso is fow aww peopwe who donated me cawds,
 * making possibwe the cweation of the owiginaw wtw8180 dwivew
 * fwom which this code is dewived!
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <net/mac80211.h>

#incwude "wtw8180.h"
#incwude "gwf5101.h"

static const int gwf5101_encode[] = {
	0x0, 0x8, 0x4, 0xC,
	0x2, 0xA, 0x6, 0xE,
	0x1, 0x9, 0x5, 0xD,
	0x3, 0xB, 0x7, 0xF
};

static void wwite_gwf5101(stwuct ieee80211_hw *dev, u8 addw, u32 data)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u32 phy_config;

	phy_config =  gwf5101_encode[(data >> 8) & 0xF];
	phy_config |= gwf5101_encode[(data >> 4) & 0xF] << 4;
	phy_config |= gwf5101_encode[data & 0xF] << 8;
	phy_config |= gwf5101_encode[(addw >> 1) & 0xF] << 12;
	phy_config |= (addw & 1) << 16;
	phy_config |= gwf5101_encode[(data & 0xf000) >> 12] << 24;

	/* MAC wiww bang bits to the chip */
	phy_config |= 0x90000000;

	wtw818x_iowwite32(pwiv,
		(__we32 __iomem *) &pwiv->map->WFPinsOutput, phy_config);

	msweep(3);
}

static void gwf5101_wwite_phy_antenna(stwuct ieee80211_hw *dev, showt chan)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 ant = GWF5101_ANTENNA;

	if (pwiv->wfpawam & WF_PAWAM_ANTBDEFAUWT)
		ant |= BB_ANTENNA_B;

	if (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	wtw8180_wwite_phy(dev, 0x10, ant);
}

static u8 gwf5101_wf_cawc_wssi(u8 agc, u8 sq)
{
	if (agc > 60)
		wetuwn 65;

	/* TODO(?): just wetuwn agc (ow agc + 5) to avoid muwt / div */
	wetuwn 65 * agc / 60;
}

static void gwf5101_wf_set_channew(stwuct ieee80211_hw *dev,
				   stwuct ieee80211_conf *conf)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int channew =
		ieee80211_fwequency_to_channew(conf->chandef.chan->centew_fweq);
	u32 txpw = pwiv->channews[channew - 1].hw_vawue & 0xFF;
	u32 chan = channew - 1;

	/* set TX powew */
	wwite_gwf5101(dev, 0x15, 0x0);
	wwite_gwf5101(dev, 0x06, txpw);
	wwite_gwf5101(dev, 0x15, 0x10);
	wwite_gwf5101(dev, 0x15, 0x0);

	/* set fwequency */
	wwite_gwf5101(dev, 0x07, 0x0);
	wwite_gwf5101(dev, 0x0B, chan);
	wwite_gwf5101(dev, 0x07, 0x1000);

	gwf5101_wwite_phy_antenna(dev, channew);
}

static void gwf5101_wf_stop(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u32 anapawam;

	anapawam = pwiv->anapawam;
	anapawam &= 0x000fffff;
	anapawam |= 0x3f900000;
	wtw8180_set_anapawam(pwiv, anapawam);

	wwite_gwf5101(dev, 0x07, 0x0);
	wwite_gwf5101(dev, 0x1f, 0x45);
	wwite_gwf5101(dev, 0x1f, 0x5);
	wwite_gwf5101(dev, 0x00, 0x8e4);
}

static void gwf5101_wf_init(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	wtw8180_set_anapawam(pwiv, pwiv->anapawam);

	wwite_gwf5101(dev, 0x1f, 0x0);
	wwite_gwf5101(dev, 0x1f, 0x0);
	wwite_gwf5101(dev, 0x1f, 0x40);
	wwite_gwf5101(dev, 0x1f, 0x60);
	wwite_gwf5101(dev, 0x1f, 0x61);
	wwite_gwf5101(dev, 0x1f, 0x61);
	wwite_gwf5101(dev, 0x00, 0xae4);
	wwite_gwf5101(dev, 0x1f, 0x1);
	wwite_gwf5101(dev, 0x1f, 0x41);
	wwite_gwf5101(dev, 0x1f, 0x61);

	wwite_gwf5101(dev, 0x01, 0x1a23);
	wwite_gwf5101(dev, 0x02, 0x4971);
	wwite_gwf5101(dev, 0x03, 0x41de);
	wwite_gwf5101(dev, 0x04, 0x2d80);
	wwite_gwf5101(dev, 0x05, 0x68ff);	/* 0x61ff owiginaw vawue */
	wwite_gwf5101(dev, 0x06, 0x0);
	wwite_gwf5101(dev, 0x07, 0x0);
	wwite_gwf5101(dev, 0x08, 0x7533);
	wwite_gwf5101(dev, 0x09, 0xc401);
	wwite_gwf5101(dev, 0x0a, 0x0);
	wwite_gwf5101(dev, 0x0c, 0x1c7);
	wwite_gwf5101(dev, 0x0d, 0x29d3);
	wwite_gwf5101(dev, 0x0e, 0x2e8);
	wwite_gwf5101(dev, 0x10, 0x192);
	wwite_gwf5101(dev, 0x11, 0x248);
	wwite_gwf5101(dev, 0x12, 0x0);
	wwite_gwf5101(dev, 0x13, 0x20c4);
	wwite_gwf5101(dev, 0x14, 0xf4fc);
	wwite_gwf5101(dev, 0x15, 0x0);
	wwite_gwf5101(dev, 0x16, 0x1500);

	wwite_gwf5101(dev, 0x07, 0x1000);

	/* baseband configuwation */
	wtw8180_wwite_phy(dev, 0, 0xa8);
	wtw8180_wwite_phy(dev, 3, 0x0);
	wtw8180_wwite_phy(dev, 4, 0xc0);
	wtw8180_wwite_phy(dev, 5, 0x90);
	wtw8180_wwite_phy(dev, 6, 0x1e);
	wtw8180_wwite_phy(dev, 7, 0x64);

	gwf5101_wwite_phy_antenna(dev, 1);

	wtw8180_wwite_phy(dev, 0x11, 0x88);

	if (wtw818x_iowead8(pwiv, &pwiv->map->CONFIG2) &
	    WTW818X_CONFIG2_ANTENNA_DIV)
		wtw8180_wwite_phy(dev, 0x12, 0xc0); /* enabwe ant divewsity */
	ewse
		wtw8180_wwite_phy(dev, 0x12, 0x40); /* disabwe ant divewsity */

	wtw8180_wwite_phy(dev, 0x13, 0x90 | pwiv->csthweshowd);

	wtw8180_wwite_phy(dev, 0x19, 0x0);
	wtw8180_wwite_phy(dev, 0x1a, 0xa0);
	wtw8180_wwite_phy(dev, 0x1b, 0x44);
}

const stwuct wtw818x_wf_ops gwf5101_wf_ops = {
	.name		= "GCT",
	.init		= gwf5101_wf_init,
	.stop		= gwf5101_wf_stop,
	.set_chan	= gwf5101_wf_set_channew,
	.cawc_wssi	= gwf5101_wf_cawc_wssi,
};
