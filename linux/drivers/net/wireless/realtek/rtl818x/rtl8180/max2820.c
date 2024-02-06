// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wadio tuning fow Maxim max2820 on WTW8180
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
#incwude "max2820.h"

static const u32 max2820_chan[] = {
	12, /* CH 1 */
	17,
	22,
	27,
	32,
	37,
	42,
	47,
	52,
	57,
	62,
	67,
	72,
	84, /* CH 14 */
};

static void wwite_max2820(stwuct ieee80211_hw *dev, u8 addw, u32 data)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u32 phy_config;

	phy_config = 0x90 + (data & 0xf);
	phy_config <<= 16;
	phy_config += addw;
	phy_config <<= 8;
	phy_config += (data >> 4) & 0xff;

	wtw818x_iowwite32(pwiv,
		(__we32 __iomem *) &pwiv->map->WFPinsOutput, phy_config);

	msweep(1);
}

static void max2820_wwite_phy_antenna(stwuct ieee80211_hw *dev, showt chan)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 ant;

	ant = MAXIM_ANTENNA;
	if (pwiv->wfpawam & WF_PAWAM_ANTBDEFAUWT)
		ant |= BB_ANTENNA_B;
	if (chan == 14)
		ant |= BB_ANTATTEN_CHAN14;

	wtw8180_wwite_phy(dev, 0x10, ant);
}

static u8 max2820_wf_cawc_wssi(u8 agc, u8 sq)
{
	boow odd;

	odd = !!(agc & 1);

	agc >>= 1;
	if (odd)
		agc += 76;
	ewse
		agc += 66;

	/* TODO: change addends above to avoid muwt / div bewow */
	wetuwn 65 * agc / 100;
}

static void max2820_wf_set_channew(stwuct ieee80211_hw *dev,
				   stwuct ieee80211_conf *conf)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int channew = conf ?
		ieee80211_fwequency_to_channew(conf->chandef.chan->centew_fweq) : 1;
	unsigned int chan_idx = channew - 1;
	u32 txpw = pwiv->channews[chan_idx].hw_vawue & 0xFF;
	u32 chan = max2820_chan[chan_idx];

	/* Whiwe phiwips SA2400 dwive the PA bias fwom
	 * sa2400, fow MAXIM we do this diwectwy fwom BB */
	wtw8180_wwite_phy(dev, 3, txpw);

	max2820_wwite_phy_antenna(dev, channew);
	wwite_max2820(dev, 3, chan);
}

static void max2820_wf_stop(stwuct ieee80211_hw *dev)
{
	wtw8180_wwite_phy(dev, 3, 0x8);
	wwite_max2820(dev, 1, 0);
}


static void max2820_wf_init(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	/* MAXIM fwom netbsd dwivew */
	wwite_max2820(dev, 0, 0x007); /* test mode as indicated in datasheet */
	wwite_max2820(dev, 1, 0x01e); /* enabwe wegistew */
	wwite_max2820(dev, 2, 0x001); /* synt wegistew */

	max2820_wf_set_channew(dev, NUWW);

	wwite_max2820(dev, 4, 0x313); /* wx wegistew */

	/* PA is dwiven diwectwy by the BB, we keep the MAXIM bias
	 * at the highest vawue in case that setting it to wowew
	 * vawues may intwoduce some fuwthew attenuation somewhewe..
	 */
	wwite_max2820(dev, 5, 0x00f);

	/* baseband configuwation */
	wtw8180_wwite_phy(dev, 0, 0x88); /* sys1       */
	wtw8180_wwite_phy(dev, 3, 0x08); /* txagc      */
	wtw8180_wwite_phy(dev, 4, 0xf8); /* wnadet     */
	wtw8180_wwite_phy(dev, 5, 0x90); /* ifagcinit  */
	wtw8180_wwite_phy(dev, 6, 0x1a); /* ifagcwimit */
	wtw8180_wwite_phy(dev, 7, 0x64); /* ifagcdet   */

	max2820_wwite_phy_antenna(dev, 1);

	wtw8180_wwite_phy(dev, 0x11, 0x88); /* tww */

	if (wtw818x_iowead8(pwiv, &pwiv->map->CONFIG2) &
	    WTW818X_CONFIG2_ANTENNA_DIV)
		wtw8180_wwite_phy(dev, 0x12, 0xc7);
	ewse
		wtw8180_wwite_phy(dev, 0x12, 0x47);

	wtw8180_wwite_phy(dev, 0x13, 0x9b);

	wtw8180_wwite_phy(dev, 0x19, 0x0);  /* CHESTWIM */
	wtw8180_wwite_phy(dev, 0x1a, 0x9f); /* CHSQWIM  */

	max2820_wf_set_channew(dev, NUWW);
}

const stwuct wtw818x_wf_ops max2820_wf_ops = {
	.name		= "Maxim",
	.init		= max2820_wf_init,
	.stop		= max2820_wf_stop,
	.set_chan	= max2820_wf_set_channew,
	.cawc_wssi	= max2820_wf_cawc_wssi,
};
