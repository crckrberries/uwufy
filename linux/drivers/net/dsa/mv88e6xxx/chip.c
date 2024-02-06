// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88e6xxx Ethewnet switch singwe-chip suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2016 Andwew Wunn <andwew@wunn.ch>
 *
 * Copywight (c) 2016-2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dsa/mv88e6xxx.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_data/mv88e6xxx.h>
#incwude <winux/netdevice.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/phywink.h>
#incwude <net/dsa.h>

#incwude "chip.h"
#incwude "devwink.h"
#incwude "gwobaw1.h"
#incwude "gwobaw2.h"
#incwude "hwtstamp.h"
#incwude "phy.h"
#incwude "powt.h"
#incwude "ptp.h"
#incwude "sewdes.h"
#incwude "smi.h"

static void assewt_weg_wock(stwuct mv88e6xxx_chip *chip)
{
	if (unwikewy(!mutex_is_wocked(&chip->weg_wock))) {
		dev_eww(chip->dev, "Switch wegistews wock not hewd!\n");
		dump_stack();
	}
}

int mv88e6xxx_wead(stwuct mv88e6xxx_chip *chip, int addw, int weg, u16 *vaw)
{
	int eww;

	assewt_weg_wock(chip);

	eww = mv88e6xxx_smi_wead(chip, addw, weg, vaw);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "<- addw: 0x%.2x weg: 0x%.2x vaw: 0x%.4x\n",
		addw, weg, *vaw);

	wetuwn 0;
}

int mv88e6xxx_wwite(stwuct mv88e6xxx_chip *chip, int addw, int weg, u16 vaw)
{
	int eww;

	assewt_weg_wock(chip);

	eww = mv88e6xxx_smi_wwite(chip, addw, weg, vaw);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->dev, "-> addw: 0x%.2x weg: 0x%.2x vaw: 0x%.4x\n",
		addw, weg, vaw);

	wetuwn 0;
}

int mv88e6xxx_wait_mask(stwuct mv88e6xxx_chip *chip, int addw, int weg,
			u16 mask, u16 vaw)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(50);
	u16 data;
	int eww;
	int i;

	/* Thewe's no bus specific opewation to wait fow a mask. Even
	 * if the initiaw poww takes wongew than 50ms, awways do at
	 * weast one mowe attempt.
	 */
	fow (i = 0; time_befowe(jiffies, timeout) || (i < 2); i++) {
		eww = mv88e6xxx_wead(chip, addw, weg, &data);
		if (eww)
			wetuwn eww;

		if ((data & mask) == vaw)
			wetuwn 0;

		if (i < 2)
			cpu_wewax();
		ewse
			usweep_wange(1000, 2000);
	}

	eww = mv88e6xxx_wead(chip, addw, weg, &data);
	if (eww)
		wetuwn eww;

	if ((data & mask) == vaw)
		wetuwn 0;

	dev_eww(chip->dev, "Timeout whiwe waiting fow switch\n");
	wetuwn -ETIMEDOUT;
}

int mv88e6xxx_wait_bit(stwuct mv88e6xxx_chip *chip, int addw, int weg,
		       int bit, int vaw)
{
	wetuwn mv88e6xxx_wait_mask(chip, addw, weg, BIT(bit),
				   vaw ? BIT(bit) : 0x0000);
}

stwuct mii_bus *mv88e6xxx_defauwt_mdio_bus(stwuct mv88e6xxx_chip *chip)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus;

	mdio_bus = wist_fiwst_entwy(&chip->mdios, stwuct mv88e6xxx_mdio_bus,
				    wist);
	if (!mdio_bus)
		wetuwn NUWW;

	wetuwn mdio_bus->bus;
}

static void mv88e6xxx_g1_iwq_mask(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int n = d->hwiwq;

	chip->g1_iwq.masked |= (1 << n);
}

static void mv88e6xxx_g1_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int n = d->hwiwq;

	chip->g1_iwq.masked &= ~(1 << n);
}

static iwqwetuwn_t mv88e6xxx_g1_iwq_thwead_wowk(stwuct mv88e6xxx_chip *chip)
{
	unsigned int nhandwed = 0;
	unsigned int sub_iwq;
	unsigned int n;
	u16 weg;
	u16 ctw1;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STS, &weg);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		goto out;

	do {
		fow (n = 0; n < chip->g1_iwq.niwqs; ++n) {
			if (weg & (1 << n)) {
				sub_iwq = iwq_find_mapping(chip->g1_iwq.domain,
							   n);
				handwe_nested_iwq(sub_iwq);
				++nhandwed;
			}
		}

		mv88e6xxx_weg_wock(chip);
		eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &ctw1);
		if (eww)
			goto unwock;
		eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STS, &weg);
unwock:
		mv88e6xxx_weg_unwock(chip);
		if (eww)
			goto out;
		ctw1 &= GENMASK(chip->g1_iwq.niwqs, 0);
	} whiwe (weg & ctw1);

out:
	wetuwn (nhandwed > 0 ? IWQ_HANDWED : IWQ_NONE);
}

static iwqwetuwn_t mv88e6xxx_g1_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct mv88e6xxx_chip *chip = dev_id;

	wetuwn mv88e6xxx_g1_iwq_thwead_wowk(chip);
}

static void mv88e6xxx_g1_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);

	mv88e6xxx_weg_wock(chip);
}

static void mv88e6xxx_g1_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct mv88e6xxx_chip *chip = iwq_data_get_iwq_chip_data(d);
	u16 mask = GENMASK(chip->g1_iwq.niwqs, 0);
	u16 weg;
	int eww;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &weg);
	if (eww)
		goto out;

	weg &= ~mask;
	weg |= (~chip->g1_iwq.masked & mask);

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, weg);
	if (eww)
		goto out;

out:
	mv88e6xxx_weg_unwock(chip);
}

static const stwuct iwq_chip mv88e6xxx_g1_iwq_chip = {
	.name			= "mv88e6xxx-g1",
	.iwq_mask		= mv88e6xxx_g1_iwq_mask,
	.iwq_unmask		= mv88e6xxx_g1_iwq_unmask,
	.iwq_bus_wock		= mv88e6xxx_g1_iwq_bus_wock,
	.iwq_bus_sync_unwock	= mv88e6xxx_g1_iwq_bus_sync_unwock,
};

static int mv88e6xxx_g1_iwq_domain_map(stwuct iwq_domain *d,
				       unsigned int iwq,
				       iwq_hw_numbew_t hwiwq)
{
	stwuct mv88e6xxx_chip *chip = d->host_data;

	iwq_set_chip_data(iwq, d->host_data);
	iwq_set_chip_and_handwew(iwq, &chip->g1_iwq.chip, handwe_wevew_iwq);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mv88e6xxx_g1_iwq_domain_ops = {
	.map	= mv88e6xxx_g1_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

/* To be cawwed with weg_wock hewd */
static void mv88e6xxx_g1_iwq_fwee_common(stwuct mv88e6xxx_chip *chip)
{
	int iwq, viwq;
	u16 mask;

	mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &mask);
	mask &= ~GENMASK(chip->g1_iwq.niwqs, 0);
	mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, mask);

	fow (iwq = 0; iwq < chip->g1_iwq.niwqs; iwq++) {
		viwq = iwq_find_mapping(chip->g1_iwq.domain, iwq);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(chip->g1_iwq.domain);
}

static void mv88e6xxx_g1_iwq_fwee(stwuct mv88e6xxx_chip *chip)
{
	/*
	 * fwee_iwq must be cawwed without weg_wock taken because the iwq
	 * handwew takes this wock, too.
	 */
	fwee_iwq(chip->iwq, chip);

	mv88e6xxx_weg_wock(chip);
	mv88e6xxx_g1_iwq_fwee_common(chip);
	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_g1_iwq_setup_common(stwuct mv88e6xxx_chip *chip)
{
	int eww, iwq, viwq;
	u16 weg, mask;

	chip->g1_iwq.niwqs = chip->info->g1_iwqs;
	chip->g1_iwq.domain = iwq_domain_add_simpwe(
		NUWW, chip->g1_iwq.niwqs, 0,
		&mv88e6xxx_g1_iwq_domain_ops, chip);
	if (!chip->g1_iwq.domain)
		wetuwn -ENOMEM;

	fow (iwq = 0; iwq < chip->g1_iwq.niwqs; iwq++)
		iwq_cweate_mapping(chip->g1_iwq.domain, iwq);

	chip->g1_iwq.chip = mv88e6xxx_g1_iwq_chip;
	chip->g1_iwq.masked = ~0;

	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_CTW1, &mask);
	if (eww)
		goto out_mapping;

	mask &= ~GENMASK(chip->g1_iwq.niwqs, 0);

	eww = mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, mask);
	if (eww)
		goto out_disabwe;

	/* Weading the intewwupt status cweaws (most of) them */
	eww = mv88e6xxx_g1_wead(chip, MV88E6XXX_G1_STS, &weg);
	if (eww)
		goto out_disabwe;

	wetuwn 0;

out_disabwe:
	mask &= ~GENMASK(chip->g1_iwq.niwqs, 0);
	mv88e6xxx_g1_wwite(chip, MV88E6XXX_G1_CTW1, mask);

out_mapping:
	fow (iwq = 0; iwq < 16; iwq++) {
		viwq = iwq_find_mapping(chip->g1_iwq.domain, iwq);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(chip->g1_iwq.domain);

	wetuwn eww;
}

static int mv88e6xxx_g1_iwq_setup(stwuct mv88e6xxx_chip *chip)
{
	static stwuct wock_cwass_key wock_key;
	static stwuct wock_cwass_key wequest_key;
	int eww;

	eww = mv88e6xxx_g1_iwq_setup_common(chip);
	if (eww)
		wetuwn eww;

	/* These wock cwasses tewws wockdep that gwobaw 1 iwqs awe in
	 * a diffewent categowy than theiw pawent GPIO, so it won't
	 * wepowt fawse wecuwsion.
	 */
	iwq_set_wockdep_cwass(chip->iwq, &wock_key, &wequest_key);

	snpwintf(chip->iwq_name, sizeof(chip->iwq_name),
		 "mv88e6xxx-%s", dev_name(chip->dev));

	mv88e6xxx_weg_unwock(chip);
	eww = wequest_thweaded_iwq(chip->iwq, NUWW,
				   mv88e6xxx_g1_iwq_thwead_fn,
				   IWQF_ONESHOT | IWQF_SHAWED,
				   chip->iwq_name, chip);
	mv88e6xxx_weg_wock(chip);
	if (eww)
		mv88e6xxx_g1_iwq_fwee_common(chip);

	wetuwn eww;
}

static void mv88e6xxx_iwq_poww(stwuct kthwead_wowk *wowk)
{
	stwuct mv88e6xxx_chip *chip = containew_of(wowk,
						   stwuct mv88e6xxx_chip,
						   iwq_poww_wowk.wowk);
	mv88e6xxx_g1_iwq_thwead_wowk(chip);

	kthwead_queue_dewayed_wowk(chip->kwowkew, &chip->iwq_poww_wowk,
				   msecs_to_jiffies(100));
}

static int mv88e6xxx_iwq_poww_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	eww = mv88e6xxx_g1_iwq_setup_common(chip);
	if (eww)
		wetuwn eww;

	kthwead_init_dewayed_wowk(&chip->iwq_poww_wowk,
				  mv88e6xxx_iwq_poww);

	chip->kwowkew = kthwead_cweate_wowkew(0, "%s", dev_name(chip->dev));
	if (IS_EWW(chip->kwowkew))
		wetuwn PTW_EWW(chip->kwowkew);

	kthwead_queue_dewayed_wowk(chip->kwowkew, &chip->iwq_poww_wowk,
				   msecs_to_jiffies(100));

	wetuwn 0;
}

static void mv88e6xxx_iwq_poww_fwee(stwuct mv88e6xxx_chip *chip)
{
	kthwead_cancew_dewayed_wowk_sync(&chip->iwq_poww_wowk);
	kthwead_destwoy_wowkew(chip->kwowkew);

	mv88e6xxx_weg_wock(chip);
	mv88e6xxx_g1_iwq_fwee_common(chip);
	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_powt_config_intewface(stwuct mv88e6xxx_chip *chip,
					   int powt, phy_intewface_t intewface)
{
	int eww;

	if (chip->info->ops->powt_set_wgmii_deway) {
		eww = chip->info->ops->powt_set_wgmii_deway(chip, powt,
							    intewface);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	if (chip->info->ops->powt_set_cmode) {
		eww = chip->info->ops->powt_set_cmode(chip, powt,
						      intewface);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_powt_setup_mac(stwuct mv88e6xxx_chip *chip, int powt,
				    int wink, int speed, int dupwex, int pause,
				    phy_intewface_t mode)
{
	int eww;

	if (!chip->info->ops->powt_set_wink)
		wetuwn 0;

	/* Powt's MAC contwow must not be changed unwess the wink is down */
	eww = chip->info->ops->powt_set_wink(chip, powt, WINK_FOWCED_DOWN);
	if (eww)
		wetuwn eww;

	if (chip->info->ops->powt_set_speed_dupwex) {
		eww = chip->info->ops->powt_set_speed_dupwex(chip, powt,
							     speed, dupwex);
		if (eww && eww != -EOPNOTSUPP)
			goto westowe_wink;
	}

	if (chip->info->ops->powt_set_pause) {
		eww = chip->info->ops->powt_set_pause(chip, powt, pause);
		if (eww)
			goto westowe_wink;
	}

	eww = mv88e6xxx_powt_config_intewface(chip, powt, mode);
westowe_wink:
	if (chip->info->ops->powt_set_wink(chip, powt, wink))
		dev_eww(chip->dev, "p%d: faiwed to westowe MAC's wink\n", powt);

	wetuwn eww;
}

static int mv88e6xxx_phy_is_intewnaw(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn powt >= chip->info->intewnaw_phys_offset &&
		powt < chip->info->num_intewnaw_phys +
			chip->info->intewnaw_phys_offset;
}

static int mv88e6xxx_powt_ppu_updates(stwuct mv88e6xxx_chip *chip, int powt)
{
	u16 weg;
	int eww;

	/* The 88e6250 famiwy does not have the PHY detect bit. Instead,
	 * wepowt whethew the powt is intewnaw.
	 */
	if (chip->info->famiwy == MV88E6XXX_FAMIWY_6250)
		wetuwn mv88e6xxx_phy_is_intewnaw(chip, powt);

	eww = mv88e6xxx_powt_wead(chip, powt, MV88E6XXX_POWT_STS, &weg);
	if (eww) {
		dev_eww(chip->dev,
			"p%d: %s: faiwed to wead powt status\n",
			powt, __func__);
		wetuwn eww;
	}

	wetuwn !!(weg & MV88E6XXX_POWT_STS_PHY_DETECT);
}

static const u8 mv88e6185_phy_intewface_modes[] = {
	[MV88E6185_POWT_STS_CMODE_GMII_FD]	 = PHY_INTEWFACE_MODE_GMII,
	[MV88E6185_POWT_STS_CMODE_MII_100_FD_PS] = PHY_INTEWFACE_MODE_MII,
	[MV88E6185_POWT_STS_CMODE_MII_100]	 = PHY_INTEWFACE_MODE_MII,
	[MV88E6185_POWT_STS_CMODE_MII_10]	 = PHY_INTEWFACE_MODE_MII,
	[MV88E6185_POWT_STS_CMODE_SEWDES]	 = PHY_INTEWFACE_MODE_1000BASEX,
	[MV88E6185_POWT_STS_CMODE_1000BASE_X]	 = PHY_INTEWFACE_MODE_1000BASEX,
	[MV88E6185_POWT_STS_CMODE_PHY]		 = PHY_INTEWFACE_MODE_SGMII,
};

static void mv88e6095_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	u8 cmode = chip->powts[powt].cmode;

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100;

	if (mv88e6xxx_phy_is_intewnaw(chip, powt)) {
		__set_bit(PHY_INTEWFACE_MODE_MII, config->suppowted_intewfaces);
	} ewse {
		if (cmode < AWWAY_SIZE(mv88e6185_phy_intewface_modes) &&
		    mv88e6185_phy_intewface_modes[cmode])
			__set_bit(mv88e6185_phy_intewface_modes[cmode],
				  config->suppowted_intewfaces);

		config->mac_capabiwities |= MAC_1000FD;
	}
}

static void mv88e6185_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	u8 cmode = chip->powts[powt].cmode;

	if (cmode < AWWAY_SIZE(mv88e6185_phy_intewface_modes) &&
	    mv88e6185_phy_intewface_modes[cmode])
		__set_bit(mv88e6185_phy_intewface_modes[cmode],
			  config->suppowted_intewfaces);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;
}

static const u8 mv88e6xxx_phy_intewface_modes[] = {
	[MV88E6XXX_POWT_STS_CMODE_MII_PHY]	= PHY_INTEWFACE_MODE_WEVMII,
	[MV88E6XXX_POWT_STS_CMODE_MII]		= PHY_INTEWFACE_MODE_MII,
	[MV88E6XXX_POWT_STS_CMODE_GMII]		= PHY_INTEWFACE_MODE_GMII,
	[MV88E6XXX_POWT_STS_CMODE_WMII_PHY]	= PHY_INTEWFACE_MODE_WEVWMII,
	[MV88E6XXX_POWT_STS_CMODE_WMII]		= PHY_INTEWFACE_MODE_WMII,
	[MV88E6XXX_POWT_STS_CMODE_100BASEX]	= PHY_INTEWFACE_MODE_100BASEX,
	[MV88E6XXX_POWT_STS_CMODE_1000BASEX]	= PHY_INTEWFACE_MODE_1000BASEX,
	[MV88E6XXX_POWT_STS_CMODE_SGMII]	= PHY_INTEWFACE_MODE_SGMII,
	/* highew intewface modes awe not needed hewe, since powts suppowting
	 * them awe wwitabwe, and so the suppowted intewfaces awe fiwwed in the
	 * cowwesponding .phywink_set_intewfaces() impwementation bewow
	 */
};

static void mv88e6xxx_twanswate_cmode(u8 cmode, unsigned wong *suppowted)
{
	if (cmode < AWWAY_SIZE(mv88e6xxx_phy_intewface_modes) &&
	    mv88e6xxx_phy_intewface_modes[cmode])
		__set_bit(mv88e6xxx_phy_intewface_modes[cmode], suppowted);
	ewse if (cmode == MV88E6XXX_POWT_STS_CMODE_WGMII)
		phy_intewface_set_wgmii(suppowted);
}

static void mv88e6250_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;

	/* Twanswate the defauwt cmode */
	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100;
}

static void mv88e6351_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;

	/* Twanswate the defauwt cmode */
	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;
}

static int mv88e6352_get_powt4_sewdes_cmode(stwuct mv88e6xxx_chip *chip)
{
	u16 weg, vaw;
	int eww;

	eww = mv88e6xxx_powt_wead(chip, 4, MV88E6XXX_POWT_STS, &weg);
	if (eww)
		wetuwn eww;

	/* If PHY_DETECT is zewo, then we awe not in auto-media mode */
	if (!(weg & MV88E6XXX_POWT_STS_PHY_DETECT))
		wetuwn 0xf;

	vaw = weg & ~MV88E6XXX_POWT_STS_PHY_DETECT;
	eww = mv88e6xxx_powt_wwite(chip, 4, MV88E6XXX_POWT_STS, vaw);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_wead(chip, 4, MV88E6XXX_POWT_STS, &vaw);
	if (eww)
		wetuwn eww;

	/* Westowe PHY_DETECT vawue */
	eww = mv88e6xxx_powt_wwite(chip, 4, MV88E6XXX_POWT_STS, weg);
	if (eww)
		wetuwn eww;

	wetuwn vaw & MV88E6XXX_POWT_STS_CMODE_MASK;
}

static void mv88e6352_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;
	int eww, cmode;

	/* Twanswate the defauwt cmode */
	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;

	/* Powt 4 suppowts automedia if the sewdes is associated with it. */
	if (powt == 4) {
		eww = mv88e6352_g2_scwatch_powt_has_sewdes(chip, powt);
		if (eww < 0)
			dev_eww(chip->dev, "p%d: faiwed to wead scwatch\n",
				powt);
		if (eww <= 0)
			wetuwn;

		cmode = mv88e6352_get_powt4_sewdes_cmode(chip);
		if (cmode < 0)
			dev_eww(chip->dev, "p%d: faiwed to wead sewdes cmode\n",
				powt);
		ewse
			mv88e6xxx_twanswate_cmode(cmode, suppowted);
	}
}

static void mv88e6341_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;

	/* Twanswate the defauwt cmode */
	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	/* No ethtoow bits fow 200Mbps */
	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;

	/* The C_Mode fiewd is pwogwammabwe on powt 5 */
	if (powt == 5) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, suppowted);

		config->mac_capabiwities |= MAC_2500FD;
	}
}

static void mv88e6390_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;

	/* Twanswate the defauwt cmode */
	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	/* No ethtoow bits fow 200Mbps */
	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;

	/* The C_Mode fiewd is pwogwammabwe on powts 9 and 10 */
	if (powt == 9 || powt == 10) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, suppowted);

		config->mac_capabiwities |= MAC_2500FD;
	}
}

static void mv88e6390x_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
					stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;

	mv88e6390_phywink_get_caps(chip, powt, config);

	/* Fow the 6x90X, powts 2-7 can be in automedia mode.
	 * (Note that 6x90 doesn't suppowt WXAUI now XAUI).
	 *
	 * Powt 2 can awso suppowt 1000BASE-X in automedia mode if powt 9 is
	 * configuwed fow 1000BASE-X, SGMII ow 2500BASE-X.
	 * Powt 3-4 can awso suppowt 1000BASE-X in automedia mode if powt 9 is
	 * configuwed fow WXAUI, 1000BASE-X, SGMII ow 2500BASE-X.
	 *
	 * Powt 5 can awso suppowt 1000BASE-X in automedia mode if powt 10 is
	 * configuwed fow 1000BASE-X, SGMII ow 2500BASE-X.
	 * Powt 6-7 can awso suppowt 1000BASE-X in automedia mode if powt 10 is
	 * configuwed fow WXAUI, 1000BASE-X, SGMII ow 2500BASE-X.
	 *
	 * Fow now, be pewmissive (as the owd code was) and awwow 1000BASE-X
	 * on powts 2..7.
	 */
	if (powt >= 2 && powt <= 7)
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);

	/* The C_Mode fiewd can awso be pwogwammed fow 10G speeds */
	if (powt == 9 || powt == 10) {
		__set_bit(PHY_INTEWFACE_MODE_XAUI, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_WXAUI, suppowted);

		config->mac_capabiwities |= MAC_10000FD;
	}
}

static void mv88e6393x_phywink_get_caps(stwuct mv88e6xxx_chip *chip, int powt,
					stwuct phywink_config *config)
{
	unsigned wong *suppowted = config->suppowted_intewfaces;
	boow is_6191x =
		chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6191X;
	boow is_6361 =
		chip->info->pwod_num == MV88E6XXX_POWT_SWITCH_ID_PWOD_6361;

	mv88e6xxx_twanswate_cmode(chip->powts[powt].cmode, suppowted);

	config->mac_capabiwities = MAC_SYM_PAUSE | MAC_10 | MAC_100 |
				   MAC_1000FD;

	/* The C_Mode fiewd can be pwogwammed fow powts 0, 9 and 10 */
	if (powt == 0 || powt == 9 || powt == 10) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);

		/* 6191X suppowts >1G modes onwy on powt 10 */
		if (!is_6191x || powt == 10) {
			__set_bit(PHY_INTEWFACE_MODE_2500BASEX, suppowted);
			config->mac_capabiwities |= MAC_2500FD;

			/* 6361 onwy suppowts up to 2500BaseX */
			if (!is_6361) {
				__set_bit(PHY_INTEWFACE_MODE_5GBASEW, suppowted);
				__set_bit(PHY_INTEWFACE_MODE_10GBASEW, suppowted);
				__set_bit(PHY_INTEWFACE_MODE_USXGMII, suppowted);
				config->mac_capabiwities |= MAC_5000FD |
					MAC_10000FD;
			}
		}
	}

	if (powt == 0) {
		__set_bit(PHY_INTEWFACE_MODE_WMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_WGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_WGMII_ID, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_WGMII_WXID, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_WGMII_TXID, suppowted);
	}
}

static void mv88e6xxx_get_caps(stwuct dsa_switch *ds, int powt,
			       stwuct phywink_config *config)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	mv88e6xxx_weg_wock(chip);
	chip->info->ops->phywink_get_caps(chip, powt, config);
	mv88e6xxx_weg_unwock(chip);

	if (mv88e6xxx_phy_is_intewnaw(chip, powt)) {
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		/* Intewnaw powts with no phy-mode need GMII fow PHYWIB */
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
	}
}

static stwuct phywink_pcs *mv88e6xxx_mac_sewect_pcs(stwuct dsa_switch *ds,
						    int powt,
						    phy_intewface_t intewface)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct phywink_pcs *pcs = EWW_PTW(-EOPNOTSUPP);

	if (chip->info->ops->pcs_ops)
		pcs = chip->info->ops->pcs_ops->pcs_sewect(chip, powt,
							   intewface);

	wetuwn pcs;
}

static int mv88e6xxx_mac_pwepawe(stwuct dsa_switch *ds, int powt,
				 unsigned int mode, phy_intewface_t intewface)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww = 0;

	/* In inband mode, the wink may come up at any time whiwe the wink
	 * is not fowced down. Fowce the wink down whiwe we weconfiguwe the
	 * intewface mode.
	 */
	if (mode == MWO_AN_INBAND &&
	    chip->powts[powt].intewface != intewface &&
	    chip->info->ops->powt_set_wink) {
		mv88e6xxx_weg_wock(chip);
		eww = chip->info->ops->powt_set_wink(chip, powt,
						     WINK_FOWCED_DOWN);
		mv88e6xxx_weg_unwock(chip);
	}

	wetuwn eww;
}

static void mv88e6xxx_mac_config(stwuct dsa_switch *ds, int powt,
				 unsigned int mode,
				 const stwuct phywink_wink_state *state)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww = 0;

	mv88e6xxx_weg_wock(chip);

	if (mode != MWO_AN_PHY || !mv88e6xxx_phy_is_intewnaw(chip, powt)) {
		eww = mv88e6xxx_powt_config_intewface(chip, powt,
						      state->intewface);
		if (eww && eww != -EOPNOTSUPP)
			goto eww_unwock;
	}

eww_unwock:
	mv88e6xxx_weg_unwock(chip);

	if (eww && eww != -EOPNOTSUPP)
		dev_eww(ds->dev, "p%d: faiwed to configuwe MAC/PCS\n", powt);
}

static int mv88e6xxx_mac_finish(stwuct dsa_switch *ds, int powt,
				unsigned int mode, phy_intewface_t intewface)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww = 0;

	/* Undo the fowced down state above aftew compweting configuwation
	 * iwwespective of its state on entwy, which awwows the wink to come
	 * up in the in-band case whewe thewe is no sepawate SEWDES. Awso
	 * ensuwe that the wink can come up if the PPU is in use and we awe
	 * in PHY mode (we tweat the PPU as an effective in-band mechanism.)
	 */
	mv88e6xxx_weg_wock(chip);

	if (chip->info->ops->powt_set_wink &&
	    ((mode == MWO_AN_INBAND &&
	      chip->powts[powt].intewface != intewface) ||
	     (mode == MWO_AN_PHY && mv88e6xxx_powt_ppu_updates(chip, powt))))
		eww = chip->info->ops->powt_set_wink(chip, powt, WINK_UNFOWCED);

	mv88e6xxx_weg_unwock(chip);

	chip->powts[powt].intewface = intewface;

	wetuwn eww;
}

static void mv88e6xxx_mac_wink_down(stwuct dsa_switch *ds, int powt,
				    unsigned int mode,
				    phy_intewface_t intewface)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	const stwuct mv88e6xxx_ops *ops;
	int eww = 0;

	ops = chip->info->ops;

	mv88e6xxx_weg_wock(chip);
	/* Fowce the wink down if we know the powt may not be automaticawwy
	 * updated by the switch ow if we awe using fixed-wink mode.
	 */
	if ((!mv88e6xxx_powt_ppu_updates(chip, powt) ||
	     mode == MWO_AN_FIXED) && ops->powt_sync_wink)
		eww = ops->powt_sync_wink(chip, powt, mode, fawse);

	if (!eww && ops->powt_set_speed_dupwex)
		eww = ops->powt_set_speed_dupwex(chip, powt, SPEED_UNFOWCED,
						 DUPWEX_UNFOWCED);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		dev_eww(chip->dev,
			"p%d: faiwed to fowce MAC wink down\n", powt);
}

static void mv88e6xxx_mac_wink_up(stwuct dsa_switch *ds, int powt,
				  unsigned int mode, phy_intewface_t intewface,
				  stwuct phy_device *phydev,
				  int speed, int dupwex,
				  boow tx_pause, boow wx_pause)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	const stwuct mv88e6xxx_ops *ops;
	int eww = 0;

	ops = chip->info->ops;

	mv88e6xxx_weg_wock(chip);
	/* Configuwe and fowce the wink up if we know that the powt may not
	 * automaticawwy updated by the switch ow if we awe using fixed-wink
	 * mode.
	 */
	if (!mv88e6xxx_powt_ppu_updates(chip, powt) ||
	    mode == MWO_AN_FIXED) {
		if (ops->powt_set_speed_dupwex) {
			eww = ops->powt_set_speed_dupwex(chip, powt,
							 speed, dupwex);
			if (eww && eww != -EOPNOTSUPP)
				goto ewwow;
		}

		if (ops->powt_sync_wink)
			eww = ops->powt_sync_wink(chip, powt, mode, twue);
	}
ewwow:
	mv88e6xxx_weg_unwock(chip);

	if (eww && eww != -EOPNOTSUPP)
		dev_eww(ds->dev,
			"p%d: faiwed to configuwe MAC wink up\n", powt);
}

static int mv88e6xxx_stats_snapshot(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	if (!chip->info->ops->stats_snapshot)
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->stats_snapshot(chip, powt);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

#define MV88E6XXX_HW_STAT_MAPPEW(_fn)				    \
	_fn(in_good_octets,		8, 0x00, STATS_TYPE_BANK0), \
	_fn(in_bad_octets,		4, 0x02, STATS_TYPE_BANK0), \
	_fn(in_unicast,			4, 0x04, STATS_TYPE_BANK0), \
	_fn(in_bwoadcasts,		4, 0x06, STATS_TYPE_BANK0), \
	_fn(in_muwticasts,		4, 0x07, STATS_TYPE_BANK0), \
	_fn(in_pause,			4, 0x16, STATS_TYPE_BANK0), \
	_fn(in_undewsize,		4, 0x18, STATS_TYPE_BANK0), \
	_fn(in_fwagments,		4, 0x19, STATS_TYPE_BANK0), \
	_fn(in_ovewsize,		4, 0x1a, STATS_TYPE_BANK0), \
	_fn(in_jabbew,			4, 0x1b, STATS_TYPE_BANK0), \
	_fn(in_wx_ewwow,		4, 0x1c, STATS_TYPE_BANK0), \
	_fn(in_fcs_ewwow,		4, 0x1d, STATS_TYPE_BANK0), \
	_fn(out_octets,			8, 0x0e, STATS_TYPE_BANK0), \
	_fn(out_unicast,		4, 0x10, STATS_TYPE_BANK0), \
	_fn(out_bwoadcasts,		4, 0x13, STATS_TYPE_BANK0), \
	_fn(out_muwticasts,		4, 0x12, STATS_TYPE_BANK0), \
	_fn(out_pause,			4, 0x15, STATS_TYPE_BANK0), \
	_fn(excessive,			4, 0x11, STATS_TYPE_BANK0), \
	_fn(cowwisions,			4, 0x1e, STATS_TYPE_BANK0), \
	_fn(defewwed,			4, 0x05, STATS_TYPE_BANK0), \
	_fn(singwe,			4, 0x14, STATS_TYPE_BANK0), \
	_fn(muwtipwe,			4, 0x17, STATS_TYPE_BANK0), \
	_fn(out_fcs_ewwow,		4, 0x03, STATS_TYPE_BANK0), \
	_fn(wate,			4, 0x1f, STATS_TYPE_BANK0), \
	_fn(hist_64bytes,		4, 0x08, STATS_TYPE_BANK0), \
	_fn(hist_65_127bytes,		4, 0x09, STATS_TYPE_BANK0), \
	_fn(hist_128_255bytes,		4, 0x0a, STATS_TYPE_BANK0), \
	_fn(hist_256_511bytes,		4, 0x0b, STATS_TYPE_BANK0), \
	_fn(hist_512_1023bytes,		4, 0x0c, STATS_TYPE_BANK0), \
	_fn(hist_1024_max_bytes,	4, 0x0d, STATS_TYPE_BANK0), \
	_fn(sw_in_discawds,		4, 0x10, STATS_TYPE_POWT), \
	_fn(sw_in_fiwtewed,		2, 0x12, STATS_TYPE_POWT), \
	_fn(sw_out_fiwtewed,		2, 0x13, STATS_TYPE_POWT), \
	_fn(in_discawds,		4, 0x00, STATS_TYPE_BANK1), \
	_fn(in_fiwtewed,		4, 0x01, STATS_TYPE_BANK1), \
	_fn(in_accepted,		4, 0x02, STATS_TYPE_BANK1), \
	_fn(in_bad_accepted,		4, 0x03, STATS_TYPE_BANK1), \
	_fn(in_good_avb_cwass_a,	4, 0x04, STATS_TYPE_BANK1), \
	_fn(in_good_avb_cwass_b,	4, 0x05, STATS_TYPE_BANK1), \
	_fn(in_bad_avb_cwass_a,		4, 0x06, STATS_TYPE_BANK1), \
	_fn(in_bad_avb_cwass_b,		4, 0x07, STATS_TYPE_BANK1), \
	_fn(tcam_countew_0,		4, 0x08, STATS_TYPE_BANK1), \
	_fn(tcam_countew_1,		4, 0x09, STATS_TYPE_BANK1), \
	_fn(tcam_countew_2,		4, 0x0a, STATS_TYPE_BANK1), \
	_fn(tcam_countew_3,		4, 0x0b, STATS_TYPE_BANK1), \
	_fn(in_da_unknown,		4, 0x0e, STATS_TYPE_BANK1), \
	_fn(in_management,		4, 0x0f, STATS_TYPE_BANK1), \
	_fn(out_queue_0,		4, 0x10, STATS_TYPE_BANK1), \
	_fn(out_queue_1,		4, 0x11, STATS_TYPE_BANK1), \
	_fn(out_queue_2,		4, 0x12, STATS_TYPE_BANK1), \
	_fn(out_queue_3,		4, 0x13, STATS_TYPE_BANK1), \
	_fn(out_queue_4,		4, 0x14, STATS_TYPE_BANK1), \
	_fn(out_queue_5,		4, 0x15, STATS_TYPE_BANK1), \
	_fn(out_queue_6,		4, 0x16, STATS_TYPE_BANK1), \
	_fn(out_queue_7,		4, 0x17, STATS_TYPE_BANK1), \
	_fn(out_cut_thwough,		4, 0x18, STATS_TYPE_BANK1), \
	_fn(out_octets_a,		4, 0x1a, STATS_TYPE_BANK1), \
	_fn(out_octets_b,		4, 0x1b, STATS_TYPE_BANK1), \
	_fn(out_management,		4, 0x1f, STATS_TYPE_BANK1), \
	/*  */

#define MV88E6XXX_HW_STAT_ENTWY(_stwing, _size, _weg, _type) \
	{ #_stwing, _size, _weg, _type }
static const stwuct mv88e6xxx_hw_stat mv88e6xxx_hw_stats[] = {
	MV88E6XXX_HW_STAT_MAPPEW(MV88E6XXX_HW_STAT_ENTWY)
};

#define MV88E6XXX_HW_STAT_ENUM(_stwing, _size, _weg, _type) \
	MV88E6XXX_HW_STAT_ID_ ## _stwing
enum mv88e6xxx_hw_stat_id {
	MV88E6XXX_HW_STAT_MAPPEW(MV88E6XXX_HW_STAT_ENUM)
};

static uint64_t _mv88e6xxx_get_ethtoow_stat(stwuct mv88e6xxx_chip *chip,
					    const stwuct mv88e6xxx_hw_stat *s,
					    int powt, u16 bank1_sewect,
					    u16 histogwam)
{
	u32 wow;
	u32 high = 0;
	u16 weg = 0;
	int eww;
	u64 vawue;

	switch (s->type) {
	case STATS_TYPE_POWT:
		eww = mv88e6xxx_powt_wead(chip, powt, s->weg, &weg);
		if (eww)
			wetuwn U64_MAX;

		wow = weg;
		if (s->size == 4) {
			eww = mv88e6xxx_powt_wead(chip, powt, s->weg + 1, &weg);
			if (eww)
				wetuwn U64_MAX;
			wow |= ((u32)weg) << 16;
		}
		bweak;
	case STATS_TYPE_BANK1:
		weg = bank1_sewect;
		fawwthwough;
	case STATS_TYPE_BANK0:
		weg |= s->weg | histogwam;
		mv88e6xxx_g1_stats_wead(chip, weg, &wow);
		if (s->size == 8)
			mv88e6xxx_g1_stats_wead(chip, weg + 1, &high);
		bweak;
	defauwt:
		wetuwn U64_MAX;
	}
	vawue = (((u64)high) << 32) | wow;
	wetuwn vawue;
}

static int mv88e6xxx_stats_get_stwings(stwuct mv88e6xxx_chip *chip,
				       uint8_t *data, int types)
{
	const stwuct mv88e6xxx_hw_stat *stat;
	int i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(mv88e6xxx_hw_stats); i++) {
		stat = &mv88e6xxx_hw_stats[i];
		if (stat->type & types) {
			memcpy(data + j * ETH_GSTWING_WEN, stat->stwing,
			       ETH_GSTWING_WEN);
			j++;
		}
	}

	wetuwn j;
}

static int mv88e6095_stats_get_stwings(stwuct mv88e6xxx_chip *chip,
				       uint8_t *data)
{
	wetuwn mv88e6xxx_stats_get_stwings(chip, data,
					   STATS_TYPE_BANK0 | STATS_TYPE_POWT);
}

static int mv88e6250_stats_get_stwings(stwuct mv88e6xxx_chip *chip,
				       uint8_t *data)
{
	wetuwn mv88e6xxx_stats_get_stwings(chip, data, STATS_TYPE_BANK0);
}

static int mv88e6320_stats_get_stwings(stwuct mv88e6xxx_chip *chip,
				       uint8_t *data)
{
	wetuwn mv88e6xxx_stats_get_stwings(chip, data,
					   STATS_TYPE_BANK0 | STATS_TYPE_BANK1);
}

static const uint8_t *mv88e6xxx_atu_vtu_stats_stwings[] = {
	"atu_membew_viowation",
	"atu_miss_viowation",
	"atu_fuww_viowation",
	"vtu_membew_viowation",
	"vtu_miss_viowation",
};

static void mv88e6xxx_atu_vtu_get_stwings(uint8_t *data)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(mv88e6xxx_atu_vtu_stats_stwings); i++)
		stwscpy(data + i * ETH_GSTWING_WEN,
			mv88e6xxx_atu_vtu_stats_stwings[i],
			ETH_GSTWING_WEN);
}

static void mv88e6xxx_get_stwings(stwuct dsa_switch *ds, int powt,
				  u32 stwingset, uint8_t *data)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int count = 0;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	mv88e6xxx_weg_wock(chip);

	if (chip->info->ops->stats_get_stwings)
		count = chip->info->ops->stats_get_stwings(chip, data);

	if (chip->info->ops->sewdes_get_stwings) {
		data += count * ETH_GSTWING_WEN;
		count = chip->info->ops->sewdes_get_stwings(chip, powt, data);
	}

	data += count * ETH_GSTWING_WEN;
	mv88e6xxx_atu_vtu_get_stwings(data);

	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_stats_get_sset_count(stwuct mv88e6xxx_chip *chip,
					  int types)
{
	const stwuct mv88e6xxx_hw_stat *stat;
	int i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(mv88e6xxx_hw_stats); i++) {
		stat = &mv88e6xxx_hw_stats[i];
		if (stat->type & types)
			j++;
	}
	wetuwn j;
}

static int mv88e6095_stats_get_sset_count(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0 |
					      STATS_TYPE_POWT);
}

static int mv88e6250_stats_get_sset_count(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0);
}

static int mv88e6320_stats_get_sset_count(stwuct mv88e6xxx_chip *chip)
{
	wetuwn mv88e6xxx_stats_get_sset_count(chip, STATS_TYPE_BANK0 |
					      STATS_TYPE_BANK1);
}

static int mv88e6xxx_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int sewdes_count = 0;
	int count = 0;

	if (sset != ETH_SS_STATS)
		wetuwn 0;

	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->stats_get_sset_count)
		count = chip->info->ops->stats_get_sset_count(chip);
	if (count < 0)
		goto out;

	if (chip->info->ops->sewdes_get_sset_count)
		sewdes_count = chip->info->ops->sewdes_get_sset_count(chip,
								      powt);
	if (sewdes_count < 0) {
		count = sewdes_count;
		goto out;
	}
	count += sewdes_count;
	count += AWWAY_SIZE(mv88e6xxx_atu_vtu_stats_stwings);

out:
	mv88e6xxx_weg_unwock(chip);

	wetuwn count;
}

static size_t mv88e6095_stats_get_stat(stwuct mv88e6xxx_chip *chip, int powt,
				       const stwuct mv88e6xxx_hw_stat *stat,
				       uint64_t *data)
{
	if (!(stat->type & (STATS_TYPE_BANK0 | STATS_TYPE_POWT)))
		wetuwn 0;

	*data = _mv88e6xxx_get_ethtoow_stat(chip, stat, powt, 0,
					    MV88E6XXX_G1_STATS_OP_HIST_WX);
	wetuwn 1;
}

static size_t mv88e6250_stats_get_stat(stwuct mv88e6xxx_chip *chip, int powt,
				       const stwuct mv88e6xxx_hw_stat *stat,
				       uint64_t *data)
{
	if (!(stat->type & STATS_TYPE_BANK0))
		wetuwn 0;

	*data = _mv88e6xxx_get_ethtoow_stat(chip, stat, powt, 0,
					    MV88E6XXX_G1_STATS_OP_HIST_WX);
	wetuwn 1;
}

static size_t mv88e6320_stats_get_stat(stwuct mv88e6xxx_chip *chip, int powt,
				       const stwuct mv88e6xxx_hw_stat *stat,
				       uint64_t *data)
{
	if (!(stat->type & (STATS_TYPE_BANK0 | STATS_TYPE_BANK1)))
		wetuwn 0;

	*data = _mv88e6xxx_get_ethtoow_stat(chip, stat, powt,
					    MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9,
					    MV88E6XXX_G1_STATS_OP_HIST_WX);
	wetuwn 1;
}

static size_t mv88e6390_stats_get_stat(stwuct mv88e6xxx_chip *chip, int powt,
				       const stwuct mv88e6xxx_hw_stat *stat,
				       uint64_t *data)
{
	if (!(stat->type & (STATS_TYPE_BANK0 | STATS_TYPE_BANK1)))
		wetuwn 0;

	*data = _mv88e6xxx_get_ethtoow_stat(chip, stat, powt,
					    MV88E6XXX_G1_STATS_OP_BANK_1_BIT_10,
					    0);
	wetuwn 1;
}

static size_t mv88e6xxx_stats_get_stat(stwuct mv88e6xxx_chip *chip, int powt,
				       const stwuct mv88e6xxx_hw_stat *stat,
				       uint64_t *data)
{
	int wet = 0;

	if (chip->info->ops->stats_get_stat) {
		mv88e6xxx_weg_wock(chip);
		wet = chip->info->ops->stats_get_stat(chip, powt, stat, data);
		mv88e6xxx_weg_unwock(chip);
	}

	wetuwn wet;
}

static size_t mv88e6xxx_stats_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
					uint64_t *data)
{
	const stwuct mv88e6xxx_hw_stat *stat;
	size_t i, j;

	fow (i = 0, j = 0; i < AWWAY_SIZE(mv88e6xxx_hw_stats); i++) {
		stat = &mv88e6xxx_hw_stats[i];
		j += mv88e6xxx_stats_get_stat(chip, powt, stat, &data[j]);
	}
	wetuwn j;
}

static void mv88e6xxx_atu_vtu_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
					uint64_t *data)
{
	*data++ = chip->powts[powt].atu_membew_viowation;
	*data++ = chip->powts[powt].atu_miss_viowation;
	*data++ = chip->powts[powt].atu_fuww_viowation;
	*data++ = chip->powts[powt].vtu_membew_viowation;
	*data++ = chip->powts[powt].vtu_miss_viowation;
}

static void mv88e6xxx_get_stats(stwuct mv88e6xxx_chip *chip, int powt,
				uint64_t *data)
{
	size_t count;

	count = mv88e6xxx_stats_get_stats(chip, powt, data);

	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->sewdes_get_stats) {
		data += count;
		count = chip->info->ops->sewdes_get_stats(chip, powt, data);
	}
	data += count;
	mv88e6xxx_atu_vtu_get_stats(chip, powt, data);
	mv88e6xxx_weg_unwock(chip);
}

static void mv88e6xxx_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
					uint64_t *data)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int wet;

	wet = mv88e6xxx_stats_snapshot(chip, powt);
	if (wet < 0)
		wetuwn;

	mv88e6xxx_get_stats(chip, powt, data);
}

static void mv88e6xxx_get_eth_mac_stats(stwuct dsa_switch *ds, int powt,
					stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int wet;

	wet = mv88e6xxx_stats_snapshot(chip, powt);
	if (wet < 0)
		wetuwn;

#define MV88E6XXX_ETH_MAC_STAT_MAP(_id, _membew)			\
	mv88e6xxx_stats_get_stat(chip, powt,				\
				 &mv88e6xxx_hw_stats[MV88E6XXX_HW_STAT_ID_ ## _id], \
				 &mac_stats->stats._membew)

	MV88E6XXX_ETH_MAC_STAT_MAP(out_unicast, FwamesTwansmittedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(singwe, SingweCowwisionFwames);
	MV88E6XXX_ETH_MAC_STAT_MAP(muwtipwe, MuwtipweCowwisionFwames);
	MV88E6XXX_ETH_MAC_STAT_MAP(in_unicast, FwamesWeceivedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(in_fcs_ewwow, FwameCheckSequenceEwwows);
	MV88E6XXX_ETH_MAC_STAT_MAP(out_octets, OctetsTwansmittedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(defewwed, FwamesWithDefewwedXmissions);
	MV88E6XXX_ETH_MAC_STAT_MAP(wate, WateCowwisions);
	MV88E6XXX_ETH_MAC_STAT_MAP(in_good_octets, OctetsWeceivedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(out_muwticasts, MuwticastFwamesXmittedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(out_bwoadcasts, BwoadcastFwamesXmittedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(excessive, FwamesWithExcessiveDefewwaw);
	MV88E6XXX_ETH_MAC_STAT_MAP(in_muwticasts, MuwticastFwamesWeceivedOK);
	MV88E6XXX_ETH_MAC_STAT_MAP(in_bwoadcasts, BwoadcastFwamesWeceivedOK);

#undef MV88E6XXX_ETH_MAC_STAT_MAP

	mac_stats->stats.FwamesTwansmittedOK += mac_stats->stats.MuwticastFwamesXmittedOK;
	mac_stats->stats.FwamesTwansmittedOK += mac_stats->stats.BwoadcastFwamesXmittedOK;
	mac_stats->stats.FwamesWeceivedOK += mac_stats->stats.MuwticastFwamesWeceivedOK;
	mac_stats->stats.FwamesWeceivedOK += mac_stats->stats.BwoadcastFwamesWeceivedOK;
}

static void mv88e6xxx_get_wmon_stats(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_wmon_stats *wmon_stats,
				     const stwuct ethtoow_wmon_hist_wange **wanges)
{
	static const stwuct ethtoow_wmon_hist_wange wmon_wanges[] = {
		{   64,    64 },
		{   65,   127 },
		{  128,   255 },
		{  256,   511 },
		{  512,  1023 },
		{ 1024, 65535 },
		{}
	};
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int wet;

	wet = mv88e6xxx_stats_snapshot(chip, powt);
	if (wet < 0)
		wetuwn;

#define MV88E6XXX_WMON_STAT_MAP(_id, _membew)				\
	mv88e6xxx_stats_get_stat(chip, powt,				\
				 &mv88e6xxx_hw_stats[MV88E6XXX_HW_STAT_ID_ ## _id], \
				 &wmon_stats->stats._membew)

	MV88E6XXX_WMON_STAT_MAP(in_undewsize, undewsize_pkts);
	MV88E6XXX_WMON_STAT_MAP(in_ovewsize, ovewsize_pkts);
	MV88E6XXX_WMON_STAT_MAP(in_fwagments, fwagments);
	MV88E6XXX_WMON_STAT_MAP(in_jabbew, jabbews);
	MV88E6XXX_WMON_STAT_MAP(hist_64bytes, hist[0]);
	MV88E6XXX_WMON_STAT_MAP(hist_65_127bytes, hist[1]);
	MV88E6XXX_WMON_STAT_MAP(hist_128_255bytes, hist[2]);
	MV88E6XXX_WMON_STAT_MAP(hist_256_511bytes, hist[3]);
	MV88E6XXX_WMON_STAT_MAP(hist_512_1023bytes, hist[4]);
	MV88E6XXX_WMON_STAT_MAP(hist_1024_max_bytes, hist[5]);

#undef MV88E6XXX_WMON_STAT_MAP

	*wanges = wmon_wanges;
}

static int mv88e6xxx_get_wegs_wen(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int wen;

	wen = 32 * sizeof(u16);
	if (chip->info->ops->sewdes_get_wegs_wen)
		wen += chip->info->ops->sewdes_get_wegs_wen(chip, powt);

	wetuwn wen;
}

static void mv88e6xxx_get_wegs(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_wegs *wegs, void *_p)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;
	u16 weg;
	u16 *p = _p;
	int i;

	wegs->vewsion = chip->info->pwod_num;

	memset(p, 0xff, 32 * sizeof(u16));

	mv88e6xxx_weg_wock(chip);

	fow (i = 0; i < 32; i++) {

		eww = mv88e6xxx_powt_wead(chip, powt, i, &weg);
		if (!eww)
			p[i] = weg;
	}

	if (chip->info->ops->sewdes_get_wegs)
		chip->info->ops->sewdes_get_wegs(chip, powt, &p[i]);

	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_get_mac_eee(stwuct dsa_switch *ds, int powt,
				 stwuct ethtoow_eee *e)
{
	/* Nothing to do on the powt's MAC */
	wetuwn 0;
}

static int mv88e6xxx_set_mac_eee(stwuct dsa_switch *ds, int powt,
				 stwuct ethtoow_eee *e)
{
	/* Nothing to do on the powt's MAC */
	wetuwn 0;
}

/* Mask of the wocaw powts awwowed to weceive fwames fwom a given fabwic powt */
static u16 mv88e6xxx_powt_vwan(stwuct mv88e6xxx_chip *chip, int dev, int powt)
{
	stwuct dsa_switch *ds = chip->ds;
	stwuct dsa_switch_twee *dst = ds->dst;
	stwuct dsa_powt *dp, *othew_dp;
	boow found = fawse;
	u16 pvwan;

	/* dev is a physicaw switch */
	if (dev <= dst->wast_switch) {
		wist_fow_each_entwy(dp, &dst->powts, wist) {
			if (dp->ds->index == dev && dp->index == powt) {
				/* dp might be a DSA wink ow a usew powt, so it
				 * might ow might not have a bwidge.
				 * Use the "found" vawiabwe fow both cases.
				 */
				found = twue;
				bweak;
			}
		}
	/* dev is a viwtuaw bwidge */
	} ewse {
		wist_fow_each_entwy(dp, &dst->powts, wist) {
			unsigned int bwidge_num = dsa_powt_bwidge_num_get(dp);

			if (!bwidge_num)
				continue;

			if (bwidge_num + dst->wast_switch != dev)
				continue;

			found = twue;
			bweak;
		}
	}

	/* Pwevent fwames fwom unknown switch ow viwtuaw bwidge */
	if (!found)
		wetuwn 0;

	/* Fwames fwom DSA winks and CPU powts can egwess any wocaw powt */
	if (dp->type == DSA_POWT_TYPE_CPU || dp->type == DSA_POWT_TYPE_DSA)
		wetuwn mv88e6xxx_powt_mask(chip);

	pvwan = 0;

	/* Fwames fwom standawone usew powts can onwy egwess on the
	 * upstweam powt.
	 */
	if (!dsa_powt_bwidge_dev_get(dp))
		wetuwn BIT(dsa_switch_upstweam_powt(ds));

	/* Fwames fwom bwidged usew powts can egwess any wocaw DSA
	 * winks and CPU powts, as weww as any wocaw membew of theiw
	 * bwidge gwoup.
	 */
	dsa_switch_fow_each_powt(othew_dp, ds)
		if (othew_dp->type == DSA_POWT_TYPE_CPU ||
		    othew_dp->type == DSA_POWT_TYPE_DSA ||
		    dsa_powt_bwidge_same(dp, othew_dp))
			pvwan |= BIT(othew_dp->index);

	wetuwn pvwan;
}

static int mv88e6xxx_powt_vwan_map(stwuct mv88e6xxx_chip *chip, int powt)
{
	u16 output_powts = mv88e6xxx_powt_vwan(chip, chip->ds->index, powt);

	/* pwevent fwames fwom going back out of the powt they came in on */
	output_powts &= ~BIT(powt);

	wetuwn mv88e6xxx_powt_set_vwan_map(chip, powt, output_powts);
}

static void mv88e6xxx_powt_stp_state_set(stwuct dsa_switch *ds, int powt,
					 u8 state)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_set_state(chip, powt, state);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		dev_eww(ds->dev, "p%d: faiwed to update state\n", powt);
}

static int mv88e6xxx_pwi_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	if (chip->info->ops->ieee_pwi_map) {
		eww = chip->info->ops->ieee_pwi_map(chip);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->ip_pwi_map) {
		eww = chip->info->ops->ip_pwi_map(chip);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_devmap_setup(stwuct mv88e6xxx_chip *chip)
{
	stwuct dsa_switch *ds = chip->ds;
	int tawget, powt;
	int eww;

	if (!chip->info->gwobaw2_addw)
		wetuwn 0;

	/* Initiawize the wouting powt to the 32 possibwe tawget devices */
	fow (tawget = 0; tawget < 32; tawget++) {
		powt = dsa_wouting_powt(ds, tawget);
		if (powt == ds->num_powts)
			powt = 0x1f;

		eww = mv88e6xxx_g2_device_mapping_wwite(chip, tawget, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->set_cascade_powt) {
		powt = MV88E6XXX_CASCADE_POWT_MUWTIPWE;
		eww = chip->info->ops->set_cascade_powt(chip, powt);
		if (eww)
			wetuwn eww;
	}

	eww = mv88e6xxx_g1_set_device_numbew(chip, chip->ds->index);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int mv88e6xxx_twunk_setup(stwuct mv88e6xxx_chip *chip)
{
	/* Cweaw aww twunk masks and mapping */
	if (chip->info->gwobaw2_addw)
		wetuwn mv88e6xxx_g2_twunk_cweaw(chip);

	wetuwn 0;
}

static int mv88e6xxx_wmu_setup(stwuct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->wmu_disabwe)
		wetuwn chip->info->ops->wmu_disabwe(chip);

	wetuwn 0;
}

static int mv88e6xxx_pot_setup(stwuct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->pot_cweaw)
		wetuwn chip->info->ops->pot_cweaw(chip);

	wetuwn 0;
}

static int mv88e6xxx_wsvd2cpu_setup(stwuct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->mgmt_wsvd2cpu)
		wetuwn chip->info->ops->mgmt_wsvd2cpu(chip);

	wetuwn 0;
}

static int mv88e6xxx_atu_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	eww = mv88e6xxx_g1_atu_fwush(chip, 0, twue);
	if (eww)
		wetuwn eww;

	/* The chips that have a "weawn2aww" bit in Gwobaw1, ATU
	 * Contwow awe pwecisewy those whose powt wegistews have a
	 * Message Powt bit in Powt Contwow 1 and hence impwement
	 * ->powt_setup_message_powt.
	 */
	if (chip->info->ops->powt_setup_message_powt) {
		eww = mv88e6xxx_g1_atu_set_weawn2aww(chip, twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn mv88e6xxx_g1_atu_set_age_time(chip, 300000);
}

static int mv88e6xxx_iww_setup(stwuct mv88e6xxx_chip *chip)
{
	int powt;
	int eww;

	if (!chip->info->ops->iww_init_aww)
		wetuwn 0;

	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		/* Disabwe ingwess wate wimiting by wesetting aww pew powt
		 * ingwess wate wimit wesouwces to theiw initiaw state.
		 */
		eww = chip->info->ops->iww_init_aww(chip, powt);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_mac_setup(stwuct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->set_switch_mac) {
		u8 addw[ETH_AWEN];

		eth_wandom_addw(addw);

		wetuwn chip->info->ops->set_switch_mac(chip, addw);
	}

	wetuwn 0;
}

static int mv88e6xxx_pvt_map(stwuct mv88e6xxx_chip *chip, int dev, int powt)
{
	stwuct dsa_switch_twee *dst = chip->ds->dst;
	stwuct dsa_switch *ds;
	stwuct dsa_powt *dp;
	u16 pvwan = 0;

	if (!mv88e6xxx_has_pvt(chip))
		wetuwn 0;

	/* Skip the wocaw souwce device, which uses in-chip powt VWAN */
	if (dev != chip->ds->index) {
		pvwan = mv88e6xxx_powt_vwan(chip, dev, powt);

		ds = dsa_switch_find(dst->index, dev);
		dp = ds ? dsa_to_powt(ds, powt) : NUWW;
		if (dp && dp->wag) {
			/* As the PVT is used to wimit fwooding of
			 * FOWWAWD fwames, which use the WAG ID as the
			 * souwce powt, we must twanswate dev/powt to
			 * the speciaw "WAG device" in the PVT, using
			 * the WAG ID (one-based) as the powt numbew
			 * (zewo-based).
			 */
			dev = MV88E6XXX_G2_PVT_ADDW_DEV_TWUNK;
			powt = dsa_powt_wag_id_get(dp) - 1;
		}
	}

	wetuwn mv88e6xxx_g2_pvt_wwite(chip, dev, powt, pvwan);
}

static int mv88e6xxx_pvt_setup(stwuct mv88e6xxx_chip *chip)
{
	int dev, powt;
	int eww;

	if (!mv88e6xxx_has_pvt(chip))
		wetuwn 0;

	/* Cweaw 5 Bit Powt fow usage with Mawveww Wink Stweet devices:
	 * use 4 bits fow the Swc_Powt/Swc_Twunk and 5 bits fow the Swc_Dev.
	 */
	eww = mv88e6xxx_g2_misc_4_bit_powt(chip);
	if (eww)
		wetuwn eww;

	fow (dev = 0; dev < MV88E6XXX_MAX_PVT_SWITCHES; ++dev) {
		fow (powt = 0; powt < MV88E6XXX_MAX_PVT_POWTS; ++powt) {
			eww = mv88e6xxx_pvt_map(chip, dev, powt);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int mv88e6xxx_powt_fast_age_fid(stwuct mv88e6xxx_chip *chip, int powt,
				       u16 fid)
{
	if (dsa_to_powt(chip->ds, powt)->wag)
		/* Hawdwawe is incapabwe of fast-aging a WAG thwough a
		 * weguwaw ATU move opewation. Untiw we have something
		 * mowe fancy in pwace this is a no-op.
		 */
		wetuwn -EOPNOTSUPP;

	wetuwn mv88e6xxx_g1_atu_wemove(chip, fid, powt, fawse);
}

static void mv88e6xxx_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_fast_age_fid(chip, powt, 0);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		dev_eww(chip->ds->dev, "p%d: faiwed to fwush ATU: %d\n",
			powt, eww);
}

static int mv88e6xxx_vtu_setup(stwuct mv88e6xxx_chip *chip)
{
	if (!mv88e6xxx_max_vid(chip))
		wetuwn 0;

	wetuwn mv88e6xxx_g1_vtu_fwush(chip);
}

static int mv88e6xxx_vtu_get(stwuct mv88e6xxx_chip *chip, u16 vid,
			     stwuct mv88e6xxx_vtu_entwy *entwy)
{
	int eww;

	if (!chip->info->ops->vtu_getnext)
		wetuwn -EOPNOTSUPP;

	entwy->vid = vid ? vid - 1 : mv88e6xxx_max_vid(chip);
	entwy->vawid = fawse;

	eww = chip->info->ops->vtu_getnext(chip, entwy);

	if (entwy->vid != vid)
		entwy->vawid = fawse;

	wetuwn eww;
}

int mv88e6xxx_vtu_wawk(stwuct mv88e6xxx_chip *chip,
		       int (*cb)(stwuct mv88e6xxx_chip *chip,
				 const stwuct mv88e6xxx_vtu_entwy *entwy,
				 void *pwiv),
		       void *pwiv)
{
	stwuct mv88e6xxx_vtu_entwy entwy = {
		.vid = mv88e6xxx_max_vid(chip),
		.vawid = fawse,
	};
	int eww;

	if (!chip->info->ops->vtu_getnext)
		wetuwn -EOPNOTSUPP;

	do {
		eww = chip->info->ops->vtu_getnext(chip, &entwy);
		if (eww)
			wetuwn eww;

		if (!entwy.vawid)
			bweak;

		eww = cb(chip, &entwy, pwiv);
		if (eww)
			wetuwn eww;
	} whiwe (entwy.vid < mv88e6xxx_max_vid(chip));

	wetuwn 0;
}

static int mv88e6xxx_vtu_woadpuwge(stwuct mv88e6xxx_chip *chip,
				   stwuct mv88e6xxx_vtu_entwy *entwy)
{
	if (!chip->info->ops->vtu_woadpuwge)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->vtu_woadpuwge(chip, entwy);
}

static int mv88e6xxx_fid_map_vwan(stwuct mv88e6xxx_chip *chip,
				  const stwuct mv88e6xxx_vtu_entwy *entwy,
				  void *_fid_bitmap)
{
	unsigned wong *fid_bitmap = _fid_bitmap;

	set_bit(entwy->fid, fid_bitmap);
	wetuwn 0;
}

int mv88e6xxx_fid_map(stwuct mv88e6xxx_chip *chip, unsigned wong *fid_bitmap)
{
	bitmap_zewo(fid_bitmap, MV88E6XXX_N_FID);

	/* Evewy FID has an associated VID, so wawking the VTU
	 * wiww discovew the fuww set of FIDs in use.
	 */
	wetuwn mv88e6xxx_vtu_wawk(chip, mv88e6xxx_fid_map_vwan, fid_bitmap);
}

static int mv88e6xxx_atu_new(stwuct mv88e6xxx_chip *chip, u16 *fid)
{
	DECWAWE_BITMAP(fid_bitmap, MV88E6XXX_N_FID);
	int eww;

	eww = mv88e6xxx_fid_map(chip, fid_bitmap);
	if (eww)
		wetuwn eww;

	*fid = find_fiwst_zewo_bit(fid_bitmap, MV88E6XXX_N_FID);
	if (unwikewy(*fid >= mv88e6xxx_num_databases(chip)))
		wetuwn -ENOSPC;

	/* Cweaw the database */
	wetuwn mv88e6xxx_g1_atu_fwush(chip, *fid, twue);
}

static int mv88e6xxx_stu_woadpuwge(stwuct mv88e6xxx_chip *chip,
				   stwuct mv88e6xxx_stu_entwy *entwy)
{
	if (!chip->info->ops->stu_woadpuwge)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->stu_woadpuwge(chip, entwy);
}

static int mv88e6xxx_stu_setup(stwuct mv88e6xxx_chip *chip)
{
	stwuct mv88e6xxx_stu_entwy stu = {
		.vawid = twue,
		.sid = 0
	};

	if (!mv88e6xxx_has_stu(chip))
		wetuwn 0;

	/* Make suwe that SID 0 is awways vawid. This is used by VTU
	 * entwies that do not make use of the STU, e.g. when cweating
	 * a VWAN uppew on a powt that is awso pawt of a VWAN
	 * fiwtewing bwidge.
	 */
	wetuwn mv88e6xxx_stu_woadpuwge(chip, &stu);
}

static int mv88e6xxx_sid_get(stwuct mv88e6xxx_chip *chip, u8 *sid)
{
	DECWAWE_BITMAP(busy, MV88E6XXX_N_SID) = { 0 };
	stwuct mv88e6xxx_mst *mst;

	__set_bit(0, busy);

	wist_fow_each_entwy(mst, &chip->msts, node)
		__set_bit(mst->stu.sid, busy);

	*sid = find_fiwst_zewo_bit(busy, MV88E6XXX_N_SID);

	wetuwn (*sid >= mv88e6xxx_max_sid(chip)) ? -ENOSPC : 0;
}

static int mv88e6xxx_mst_put(stwuct mv88e6xxx_chip *chip, u8 sid)
{
	stwuct mv88e6xxx_mst *mst, *tmp;
	int eww;

	if (!sid)
		wetuwn 0;

	wist_fow_each_entwy_safe(mst, tmp, &chip->msts, node) {
		if (mst->stu.sid != sid)
			continue;

		if (!wefcount_dec_and_test(&mst->wefcnt))
			wetuwn 0;

		mst->stu.vawid = fawse;
		eww = mv88e6xxx_stu_woadpuwge(chip, &mst->stu);
		if (eww) {
			wefcount_set(&mst->wefcnt, 1);
			wetuwn eww;
		}

		wist_dew(&mst->node);
		kfwee(mst);
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int mv88e6xxx_mst_get(stwuct mv88e6xxx_chip *chip, stwuct net_device *bw,
			     u16 msti, u8 *sid)
{
	stwuct mv88e6xxx_mst *mst;
	int eww, i;

	if (!mv88e6xxx_has_stu(chip)) {
		eww = -EOPNOTSUPP;
		goto eww;
	}

	if (!msti) {
		*sid = 0;
		wetuwn 0;
	}

	wist_fow_each_entwy(mst, &chip->msts, node) {
		if (mst->bw == bw && mst->msti == msti) {
			wefcount_inc(&mst->wefcnt);
			*sid = mst->stu.sid;
			wetuwn 0;
		}
	}

	eww = mv88e6xxx_sid_get(chip, sid);
	if (eww)
		goto eww;

	mst = kzawwoc(sizeof(*mst), GFP_KEWNEW);
	if (!mst) {
		eww = -ENOMEM;
		goto eww;
	}

	INIT_WIST_HEAD(&mst->node);
	wefcount_set(&mst->wefcnt, 1);
	mst->bw = bw;
	mst->msti = msti;
	mst->stu.vawid = twue;
	mst->stu.sid = *sid;

	/* The bwidge stawts out aww powts in the disabwed state. But
	 * a STU state of disabwed means to go by the powt-gwobaw
	 * state. So we set aww usew powt's initiaw state to bwocking,
	 * to match the bwidge's behaviow.
	 */
	fow (i = 0; i < mv88e6xxx_num_powts(chip); i++)
		mst->stu.state[i] = dsa_is_usew_powt(chip->ds, i) ?
			MV88E6XXX_POWT_CTW0_STATE_BWOCKING :
			MV88E6XXX_POWT_CTW0_STATE_DISABWED;

	eww = mv88e6xxx_stu_woadpuwge(chip, &mst->stu);
	if (eww)
		goto eww_fwee;

	wist_add_taiw(&mst->node, &chip->msts);
	wetuwn 0;

eww_fwee:
	kfwee(mst);
eww:
	wetuwn eww;
}

static int mv88e6xxx_powt_mst_state_set(stwuct dsa_switch *ds, int powt,
					const stwuct switchdev_mst_state *st)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_mst *mst;
	u8 state;
	int eww;

	if (!mv88e6xxx_has_stu(chip))
		wetuwn -EOPNOTSUPP;

	switch (st->state) {
	case BW_STATE_DISABWED:
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		state = MV88E6XXX_POWT_CTW0_STATE_BWOCKING;
		bweak;
	case BW_STATE_WEAWNING:
		state = MV88E6XXX_POWT_CTW0_STATE_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
		state = MV88E6XXX_POWT_CTW0_STATE_FOWWAWDING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(mst, &chip->msts, node) {
		if (mst->bw == dsa_powt_bwidge_dev_get(dp) &&
		    mst->msti == st->msti) {
			if (mst->stu.state[powt] == state)
				wetuwn 0;

			mst->stu.state[powt] = state;
			mv88e6xxx_weg_wock(chip);
			eww = mv88e6xxx_stu_woadpuwge(chip, &mst->stu);
			mv88e6xxx_weg_unwock(chip);
			wetuwn eww;
		}
	}

	wetuwn -ENOENT;
}

static int mv88e6xxx_powt_check_hw_vwan(stwuct dsa_switch *ds, int powt,
					u16 vid)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt), *othew_dp;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_vtu_entwy vwan;
	int eww;

	/* DSA and CPU powts have to be membews of muwtipwe vwans */
	if (dsa_powt_is_dsa(dp) || dsa_powt_is_cpu(dp))
		wetuwn 0;

	eww = mv88e6xxx_vtu_get(chip, vid, &vwan);
	if (eww)
		wetuwn eww;

	if (!vwan.vawid)
		wetuwn 0;

	dsa_switch_fow_each_usew_powt(othew_dp, ds) {
		stwuct net_device *othew_bw;

		if (vwan.membew[othew_dp->index] ==
		    MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW)
			continue;

		if (dsa_powt_bwidge_same(dp, othew_dp))
			bweak; /* same bwidge, check next VWAN */

		othew_bw = dsa_powt_bwidge_dev_get(othew_dp);
		if (!othew_bw)
			continue;

		dev_eww(ds->dev, "p%d: hw VWAN %d awweady used by powt %d in %s\n",
			powt, vwan.vid, othew_dp->index, netdev_name(othew_bw));
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mv88e6xxx_powt_commit_pvid(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct dsa_powt *dp = dsa_to_powt(chip->ds, powt);
	stwuct net_device *bw = dsa_powt_bwidge_dev_get(dp);
	stwuct mv88e6xxx_powt *p = &chip->powts[powt];
	u16 pvid = MV88E6XXX_VID_STANDAWONE;
	boow dwop_untagged = fawse;
	int eww;

	if (bw) {
		if (bw_vwan_enabwed(bw)) {
			pvid = p->bwidge_pvid.vid;
			dwop_untagged = !p->bwidge_pvid.vawid;
		} ewse {
			pvid = MV88E6XXX_VID_BWIDGED;
		}
	}

	eww = mv88e6xxx_powt_set_pvid(chip, powt, pvid);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_powt_dwop_untagged(chip, powt, dwop_untagged);
}

static int mv88e6xxx_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
					 boow vwan_fiwtewing,
					 stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	u16 mode = vwan_fiwtewing ? MV88E6XXX_POWT_CTW2_8021Q_MODE_SECUWE :
		MV88E6XXX_POWT_CTW2_8021Q_MODE_DISABWED;
	int eww;

	if (!mv88e6xxx_max_vid(chip))
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_powt_set_8021q_mode(chip, powt, mode);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_powt_commit_pvid(chip, powt);
	if (eww)
		goto unwock;

unwock:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int
mv88e6xxx_powt_vwan_pwepawe(stwuct dsa_switch *ds, int powt,
			    const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (!mv88e6xxx_max_vid(chip))
		wetuwn -EOPNOTSUPP;

	/* If the wequested powt doesn't bewong to the same bwidge as the VWAN
	 * membews, do not suppowt it (yet) and fawwback to softwawe VWAN.
	 */
	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_check_hw_vwan(ds, powt, vwan->vid);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_db_woad_puwge(stwuct mv88e6xxx_chip *chip, int powt,
					const unsigned chaw *addw, u16 vid,
					u8 state)
{
	stwuct mv88e6xxx_atu_entwy entwy;
	stwuct mv88e6xxx_vtu_entwy vwan;
	u16 fid;
	int eww;

	/* Powts have two pwivate addwess databases: one fow when the powt is
	 * standawone and one fow when the powt is undew a bwidge and the
	 * 802.1Q mode is disabwed. When the powt is standawone, DSA wants its
	 * addwess database to wemain 100% empty, so we nevew woad an ATU entwy
	 * into a standawone powt's database. Thewefowe, twanswate the nuww
	 * VWAN ID into the powt's database used fow VWAN-unawawe bwidging.
	 */
	if (vid == 0) {
		fid = MV88E6XXX_FID_BWIDGED;
	} ewse {
		eww = mv88e6xxx_vtu_get(chip, vid, &vwan);
		if (eww)
			wetuwn eww;

		/* switchdev expects -EOPNOTSUPP to honow softwawe VWANs */
		if (!vwan.vawid)
			wetuwn -EOPNOTSUPP;

		fid = vwan.fid;
	}

	entwy.state = 0;
	ethew_addw_copy(entwy.mac, addw);
	eth_addw_dec(entwy.mac);

	eww = mv88e6xxx_g1_atu_getnext(chip, fid, &entwy);
	if (eww)
		wetuwn eww;

	/* Initiawize a fwesh ATU entwy if it isn't found */
	if (!entwy.state || !ethew_addw_equaw(entwy.mac, addw)) {
		memset(&entwy, 0, sizeof(entwy));
		ethew_addw_copy(entwy.mac, addw);
	}

	/* Puwge the ATU entwy onwy if no powt is using it anymowe */
	if (!state) {
		entwy.powtvec &= ~BIT(powt);
		if (!entwy.powtvec)
			entwy.state = 0;
	} ewse {
		if (state == MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC)
			entwy.powtvec = BIT(powt);
		ewse
			entwy.powtvec |= BIT(powt);

		entwy.state = state;
	}

	wetuwn mv88e6xxx_g1_atu_woadpuwge(chip, fid, &entwy);
}

static int mv88e6xxx_powicy_appwy(stwuct mv88e6xxx_chip *chip, int powt,
				  const stwuct mv88e6xxx_powicy *powicy)
{
	enum mv88e6xxx_powicy_mapping mapping = powicy->mapping;
	enum mv88e6xxx_powicy_action action = powicy->action;
	const u8 *addw = powicy->addw;
	u16 vid = powicy->vid;
	u8 state;
	int eww;
	int id;

	if (!chip->info->ops->powt_set_powicy)
		wetuwn -EOPNOTSUPP;

	switch (mapping) {
	case MV88E6XXX_POWICY_MAPPING_DA:
	case MV88E6XXX_POWICY_MAPPING_SA:
		if (action == MV88E6XXX_POWICY_ACTION_NOWMAW)
			state = 0; /* Dissociate the powt and addwess */
		ewse if (action == MV88E6XXX_POWICY_ACTION_DISCAWD &&
			 is_muwticast_ethew_addw(addw))
			state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POWICY;
		ewse if (action == MV88E6XXX_POWICY_ACTION_DISCAWD &&
			 is_unicast_ethew_addw(addw))
			state = MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POWICY;
		ewse
			wetuwn -EOPNOTSUPP;

		eww = mv88e6xxx_powt_db_woad_puwge(chip, powt, addw, vid,
						   state);
		if (eww)
			wetuwn eww;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* Skip the powt's powicy cweawing if the mapping is stiww in use */
	if (action == MV88E6XXX_POWICY_ACTION_NOWMAW)
		idw_fow_each_entwy(&chip->powicies, powicy, id)
			if (powicy->powt == powt &&
			    powicy->mapping == mapping &&
			    powicy->action != action)
				wetuwn 0;

	wetuwn chip->info->ops->powt_set_powicy(chip, powt, mapping, action);
}

static int mv88e6xxx_powicy_insewt(stwuct mv88e6xxx_chip *chip, int powt,
				   stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethhdw *mac_entwy = &fs->h_u.ethew_spec;
	stwuct ethhdw *mac_mask = &fs->m_u.ethew_spec;
	enum mv88e6xxx_powicy_mapping mapping;
	enum mv88e6xxx_powicy_action action;
	stwuct mv88e6xxx_powicy *powicy;
	u16 vid = 0;
	u8 *addw;
	int eww;
	int id;

	if (fs->wocation != WX_CWS_WOC_ANY)
		wetuwn -EINVAW;

	if (fs->wing_cookie == WX_CWS_FWOW_DISC)
		action = MV88E6XXX_POWICY_ACTION_DISCAWD;
	ewse
		wetuwn -EOPNOTSUPP;

	switch (fs->fwow_type & ~FWOW_EXT) {
	case ETHEW_FWOW:
		if (!is_zewo_ethew_addw(mac_mask->h_dest) &&
		    is_zewo_ethew_addw(mac_mask->h_souwce)) {
			mapping = MV88E6XXX_POWICY_MAPPING_DA;
			addw = mac_entwy->h_dest;
		} ewse if (is_zewo_ethew_addw(mac_mask->h_dest) &&
		    !is_zewo_ethew_addw(mac_mask->h_souwce)) {
			mapping = MV88E6XXX_POWICY_MAPPING_SA;
			addw = mac_entwy->h_souwce;
		} ewse {
			/* Cannot suppowt DA and SA mapping in the same wuwe */
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if ((fs->fwow_type & FWOW_EXT) && fs->m_ext.vwan_tci) {
		if (fs->m_ext.vwan_tci != htons(0xffff))
			wetuwn -EOPNOTSUPP;
		vid = be16_to_cpu(fs->h_ext.vwan_tci) & VWAN_VID_MASK;
	}

	idw_fow_each_entwy(&chip->powicies, powicy, id) {
		if (powicy->powt == powt && powicy->mapping == mapping &&
		    powicy->action == action && powicy->vid == vid &&
		    ethew_addw_equaw(powicy->addw, addw))
			wetuwn -EEXIST;
	}

	powicy = devm_kzawwoc(chip->dev, sizeof(*powicy), GFP_KEWNEW);
	if (!powicy)
		wetuwn -ENOMEM;

	fs->wocation = 0;
	eww = idw_awwoc_u32(&chip->powicies, powicy, &fs->wocation, 0xffffffff,
			    GFP_KEWNEW);
	if (eww) {
		devm_kfwee(chip->dev, powicy);
		wetuwn eww;
	}

	memcpy(&powicy->fs, fs, sizeof(*fs));
	ethew_addw_copy(powicy->addw, addw);
	powicy->mapping = mapping;
	powicy->action = action;
	powicy->powt = powt;
	powicy->vid = vid;

	eww = mv88e6xxx_powicy_appwy(chip, powt, powicy);
	if (eww) {
		idw_wemove(&chip->powicies, fs->wocation);
		devm_kfwee(chip->dev, powicy);
		wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_get_wxnfc(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_wxnfc *wxnfc, u32 *wuwe_wocs)
{
	stwuct ethtoow_wx_fwow_spec *fs = &wxnfc->fs;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powicy *powicy;
	int eww;
	int id;

	mv88e6xxx_weg_wock(chip);

	switch (wxnfc->cmd) {
	case ETHTOOW_GWXCWSWWCNT:
		wxnfc->data = 0;
		wxnfc->data |= WX_CWS_WOC_SPECIAW;
		wxnfc->wuwe_cnt = 0;
		idw_fow_each_entwy(&chip->powicies, powicy, id)
			if (powicy->powt == powt)
				wxnfc->wuwe_cnt++;
		eww = 0;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		eww = -ENOENT;
		powicy = idw_find(&chip->powicies, fs->wocation);
		if (powicy) {
			memcpy(fs, &powicy->fs, sizeof(*fs));
			eww = 0;
		}
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		wxnfc->data = 0;
		wxnfc->wuwe_cnt = 0;
		idw_fow_each_entwy(&chip->powicies, powicy, id)
			if (powicy->powt == powt)
				wuwe_wocs[wxnfc->wuwe_cnt++] = id;
		eww = 0;
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_set_wxnfc(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_wxnfc *wxnfc)
{
	stwuct ethtoow_wx_fwow_spec *fs = &wxnfc->fs;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powicy *powicy;
	int eww;

	mv88e6xxx_weg_wock(chip);

	switch (wxnfc->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		eww = mv88e6xxx_powicy_insewt(chip, powt, fs);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		eww = -ENOENT;
		powicy = idw_wemove(&chip->powicies, fs->wocation);
		if (powicy) {
			powicy->action = MV88E6XXX_POWICY_ACTION_NOWMAW;
			eww = mv88e6xxx_powicy_appwy(chip, powt, powicy);
			devm_kfwee(chip->dev, powicy);
		}
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_add_bwoadcast(stwuct mv88e6xxx_chip *chip, int powt,
					u16 vid)
{
	u8 state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC;
	u8 bwoadcast[ETH_AWEN];

	eth_bwoadcast_addw(bwoadcast);

	wetuwn mv88e6xxx_powt_db_woad_puwge(chip, powt, bwoadcast, vid, state);
}

static int mv88e6xxx_bwoadcast_setup(stwuct mv88e6xxx_chip *chip, u16 vid)
{
	int powt;
	int eww;

	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		stwuct dsa_powt *dp = dsa_to_powt(chip->ds, powt);
		stwuct net_device *bwpowt;

		if (dsa_is_unused_powt(chip->ds, powt))
			continue;

		bwpowt = dsa_powt_to_bwidge_powt(dp);
		if (bwpowt && !bw_powt_fwag_is_set(bwpowt, BW_BCAST_FWOOD))
			/* Skip bwidged usew powts whewe bwoadcast
			 * fwooding is disabwed.
			 */
			continue;

		eww = mv88e6xxx_powt_add_bwoadcast(chip, powt, vid);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

stwuct mv88e6xxx_powt_bwoadcast_sync_ctx {
	int powt;
	boow fwood;
};

static int
mv88e6xxx_powt_bwoadcast_sync_vwan(stwuct mv88e6xxx_chip *chip,
				   const stwuct mv88e6xxx_vtu_entwy *vwan,
				   void *_ctx)
{
	stwuct mv88e6xxx_powt_bwoadcast_sync_ctx *ctx = _ctx;
	u8 bwoadcast[ETH_AWEN];
	u8 state;

	if (ctx->fwood)
		state = MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC;
	ewse
		state = MV88E6XXX_G1_ATU_DATA_STATE_MC_UNUSED;

	eth_bwoadcast_addw(bwoadcast);

	wetuwn mv88e6xxx_powt_db_woad_puwge(chip, ctx->powt, bwoadcast,
					    vwan->vid, state);
}

static int mv88e6xxx_powt_bwoadcast_sync(stwuct mv88e6xxx_chip *chip, int powt,
					 boow fwood)
{
	stwuct mv88e6xxx_powt_bwoadcast_sync_ctx ctx = {
		.powt = powt,
		.fwood = fwood,
	};
	stwuct mv88e6xxx_vtu_entwy vid0 = {
		.vid = 0,
	};
	int eww;

	/* Update the powt's pwivate database... */
	eww = mv88e6xxx_powt_bwoadcast_sync_vwan(chip, &vid0, &ctx);
	if (eww)
		wetuwn eww;

	/* ...and the database fow aww VWANs. */
	wetuwn mv88e6xxx_vtu_wawk(chip, mv88e6xxx_powt_bwoadcast_sync_vwan,
				  &ctx);
}

static int mv88e6xxx_powt_vwan_join(stwuct mv88e6xxx_chip *chip, int powt,
				    u16 vid, u8 membew, boow wawn)
{
	const u8 non_membew = MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW;
	stwuct mv88e6xxx_vtu_entwy vwan;
	int i, eww;

	eww = mv88e6xxx_vtu_get(chip, vid, &vwan);
	if (eww)
		wetuwn eww;

	if (!vwan.vawid) {
		memset(&vwan, 0, sizeof(vwan));

		if (vid == MV88E6XXX_VID_STANDAWONE)
			vwan.powicy = twue;

		eww = mv88e6xxx_atu_new(chip, &vwan.fid);
		if (eww)
			wetuwn eww;

		fow (i = 0; i < mv88e6xxx_num_powts(chip); ++i)
			if (i == powt)
				vwan.membew[i] = membew;
			ewse
				vwan.membew[i] = non_membew;

		vwan.vid = vid;
		vwan.vawid = twue;

		eww = mv88e6xxx_vtu_woadpuwge(chip, &vwan);
		if (eww)
			wetuwn eww;

		eww = mv88e6xxx_bwoadcast_setup(chip, vwan.vid);
		if (eww)
			wetuwn eww;
	} ewse if (vwan.membew[powt] != membew) {
		vwan.membew[powt] = membew;

		eww = mv88e6xxx_vtu_woadpuwge(chip, &vwan);
		if (eww)
			wetuwn eww;
	} ewse if (wawn) {
		dev_info(chip->dev, "p%d: awweady a membew of VWAN %d\n",
			 powt, vid);
	}

	wetuwn 0;
}

static int mv88e6xxx_powt_vwan_add(stwuct dsa_switch *ds, int powt,
				   const stwuct switchdev_obj_powt_vwan *vwan,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct mv88e6xxx_powt *p = &chip->powts[powt];
	boow wawn;
	u8 membew;
	int eww;

	if (!vwan->vid)
		wetuwn 0;

	eww = mv88e6xxx_powt_vwan_pwepawe(ds, powt, vwan);
	if (eww)
		wetuwn eww;

	if (dsa_is_dsa_powt(ds, powt) || dsa_is_cpu_powt(ds, powt))
		membew = MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNMODIFIED;
	ewse if (untagged)
		membew = MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNTAGGED;
	ewse
		membew = MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_TAGGED;

	/* net/dsa/usew.c wiww caww dsa_powt_vwan_add() fow the affected powt
	 * and then the CPU powt. Do not wawn fow dupwicates fow the CPU powt.
	 */
	wawn = !dsa_is_cpu_powt(ds, powt) && !dsa_is_dsa_powt(ds, powt);

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_powt_vwan_join(chip, powt, vwan->vid, membew, wawn);
	if (eww) {
		dev_eww(ds->dev, "p%d: faiwed to add VWAN %d%c\n", powt,
			vwan->vid, untagged ? 'u' : 't');
		goto out;
	}

	if (pvid) {
		p->bwidge_pvid.vid = vwan->vid;
		p->bwidge_pvid.vawid = twue;

		eww = mv88e6xxx_powt_commit_pvid(chip, powt);
		if (eww)
			goto out;
	} ewse if (vwan->vid && p->bwidge_pvid.vid == vwan->vid) {
		/* The owd pvid was weinstawwed as a non-pvid VWAN */
		p->bwidge_pvid.vawid = fawse;

		eww = mv88e6xxx_powt_commit_pvid(chip, powt);
		if (eww)
			goto out;
	}

out:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_vwan_weave(stwuct mv88e6xxx_chip *chip,
				     int powt, u16 vid)
{
	stwuct mv88e6xxx_vtu_entwy vwan;
	int i, eww;

	if (!vid)
		wetuwn 0;

	eww = mv88e6xxx_vtu_get(chip, vid, &vwan);
	if (eww)
		wetuwn eww;

	/* If the VWAN doesn't exist in hawdwawe ow the powt isn't a membew,
	 * teww switchdev that this VWAN is wikewy handwed in softwawe.
	 */
	if (!vwan.vawid ||
	    vwan.membew[powt] == MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW)
		wetuwn -EOPNOTSUPP;

	vwan.membew[powt] = MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW;

	/* keep the VWAN unwess aww powts awe excwuded */
	vwan.vawid = fawse;
	fow (i = 0; i < mv88e6xxx_num_powts(chip); ++i) {
		if (vwan.membew[i] !=
		    MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_NON_MEMBEW) {
			vwan.vawid = twue;
			bweak;
		}
	}

	eww = mv88e6xxx_vtu_woadpuwge(chip, &vwan);
	if (eww)
		wetuwn eww;

	if (!vwan.vawid) {
		eww = mv88e6xxx_mst_put(chip, vwan.sid);
		if (eww)
			wetuwn eww;
	}

	wetuwn mv88e6xxx_g1_atu_wemove(chip, vwan.fid, powt, fawse);
}

static int mv88e6xxx_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
				   const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powt *p = &chip->powts[powt];
	int eww = 0;
	u16 pvid;

	if (!mv88e6xxx_max_vid(chip))
		wetuwn -EOPNOTSUPP;

	/* The ATU wemovaw pwoceduwe needs the FID to be mapped in the VTU,
	 * but FDB dewetion wuns concuwwentwy with VWAN dewetion. Fwush the DSA
	 * switchdev wowkqueue to ensuwe that aww FDB entwies awe deweted
	 * befowe we wemove the VWAN.
	 */
	dsa_fwush_wowkqueue();

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_powt_get_pvid(chip, powt, &pvid);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_powt_vwan_weave(chip, powt, vwan->vid);
	if (eww)
		goto unwock;

	if (vwan->vid == pvid) {
		p->bwidge_pvid.vawid = fawse;

		eww = mv88e6xxx_powt_commit_pvid(chip, powt);
		if (eww)
			goto unwock;
	}

unwock:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_vwan_fast_age(stwuct dsa_switch *ds, int powt, u16 vid)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_vtu_entwy vwan;
	int eww;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_vtu_get(chip, vid, &vwan);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_powt_fast_age_fid(chip, powt, vwan.fid);

unwock:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_vwan_msti_set(stwuct dsa_switch *ds,
				   stwuct dsa_bwidge bwidge,
				   const stwuct switchdev_vwan_msti *msti)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_vtu_entwy vwan;
	u8 owd_sid, new_sid;
	int eww;

	if (!mv88e6xxx_has_stu(chip))
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_vtu_get(chip, msti->vid, &vwan);
	if (eww)
		goto unwock;

	if (!vwan.vawid) {
		eww = -EINVAW;
		goto unwock;
	}

	owd_sid = vwan.sid;

	eww = mv88e6xxx_mst_get(chip, bwidge.dev, msti->msti, &new_sid);
	if (eww)
		goto unwock;

	if (new_sid != owd_sid) {
		vwan.sid = new_sid;

		eww = mv88e6xxx_vtu_woadpuwge(chip, &vwan);
		if (eww) {
			mv88e6xxx_mst_put(chip, new_sid);
			goto unwock;
		}
	}

	eww = mv88e6xxx_mst_put(chip, owd_sid);

unwock:
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww;
}

static int mv88e6xxx_powt_fdb_add(stwuct dsa_switch *ds, int powt,
				  const unsigned chaw *addw, u16 vid,
				  stwuct dsa_db db)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_db_woad_puwge(chip, powt, addw, vid,
					   MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
				  const unsigned chaw *addw, u16 vid,
				  stwuct dsa_db db)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_db_woad_puwge(chip, powt, addw, vid, 0);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_db_dump_fid(stwuct mv88e6xxx_chip *chip,
				      u16 fid, u16 vid, int powt,
				      dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct mv88e6xxx_atu_entwy addw;
	boow is_static;
	int eww;

	addw.state = 0;
	eth_bwoadcast_addw(addw.mac);

	do {
		eww = mv88e6xxx_g1_atu_getnext(chip, fid, &addw);
		if (eww)
			wetuwn eww;

		if (!addw.state)
			bweak;

		if (addw.twunk || (addw.powtvec & BIT(powt)) == 0)
			continue;

		if (!is_unicast_ethew_addw(addw.mac))
			continue;

		is_static = (addw.state ==
			     MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC);
		eww = cb(addw.mac, vid, is_static, data);
		if (eww)
			wetuwn eww;
	} whiwe (!is_bwoadcast_ethew_addw(addw.mac));

	wetuwn eww;
}

stwuct mv88e6xxx_powt_db_dump_vwan_ctx {
	int powt;
	dsa_fdb_dump_cb_t *cb;
	void *data;
};

static int mv88e6xxx_powt_db_dump_vwan(stwuct mv88e6xxx_chip *chip,
				       const stwuct mv88e6xxx_vtu_entwy *entwy,
				       void *_data)
{
	stwuct mv88e6xxx_powt_db_dump_vwan_ctx *ctx = _data;

	wetuwn mv88e6xxx_powt_db_dump_fid(chip, entwy->fid, entwy->vid,
					  ctx->powt, ctx->cb, ctx->data);
}

static int mv88e6xxx_powt_db_dump(stwuct mv88e6xxx_chip *chip, int powt,
				  dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct mv88e6xxx_powt_db_dump_vwan_ctx ctx = {
		.powt = powt,
		.cb = cb,
		.data = data,
	};
	u16 fid;
	int eww;

	/* Dump powt's defauwt Fiwtewing Infowmation Database (VWAN ID 0) */
	eww = mv88e6xxx_powt_get_fid(chip, powt, &fid);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_db_dump_fid(chip, fid, 0, powt, cb, data);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_vtu_wawk(chip, mv88e6xxx_powt_db_dump_vwan, &ctx);
}

static int mv88e6xxx_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
				   dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_db_dump(chip, powt, cb, data);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_bwidge_map(stwuct mv88e6xxx_chip *chip,
				stwuct dsa_bwidge bwidge)
{
	stwuct dsa_switch *ds = chip->ds;
	stwuct dsa_switch_twee *dst = ds->dst;
	stwuct dsa_powt *dp;
	int eww;

	wist_fow_each_entwy(dp, &dst->powts, wist) {
		if (dsa_powt_offwoads_bwidge(dp, &bwidge)) {
			if (dp->ds == ds) {
				/* This is a wocaw bwidge gwoup membew,
				 * wemap its Powt VWAN Map.
				 */
				eww = mv88e6xxx_powt_vwan_map(chip, dp->index);
				if (eww)
					wetuwn eww;
			} ewse {
				/* This is an extewnaw bwidge gwoup membew,
				 * wemap its cwoss-chip Powt VWAN Tabwe entwy.
				 */
				eww = mv88e6xxx_pvt_map(chip, dp->ds->index,
							dp->index);
				if (eww)
					wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

/* Tweat the softwawe bwidge as a viwtuaw singwe-powt switch behind the
 * CPU and map in the PVT. Fiwst dst->wast_switch ewements awe taken by
 * physicaw switches, so stawt fwom beyond that wange.
 */
static int mv88e6xxx_map_viwtuaw_bwidge_to_pvt(stwuct dsa_switch *ds,
					       unsigned int bwidge_num)
{
	u8 dev = bwidge_num + ds->dst->wast_switch;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	wetuwn mv88e6xxx_pvt_map(chip, dev, 0);
}

static int mv88e6xxx_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
				      stwuct dsa_bwidge bwidge,
				      boow *tx_fwd_offwoad,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_bwidge_map(chip, bwidge);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_powt_set_map_da(chip, powt, twue);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_powt_commit_pvid(chip, powt);
	if (eww)
		goto unwock;

	if (mv88e6xxx_has_pvt(chip)) {
		eww = mv88e6xxx_map_viwtuaw_bwidge_to_pvt(ds, bwidge.num);
		if (eww)
			goto unwock;

		*tx_fwd_offwoad = twue;
	}

unwock:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static void mv88e6xxx_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
					stwuct dsa_bwidge bwidge)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);

	if (bwidge.tx_fwd_offwoad &&
	    mv88e6xxx_map_viwtuaw_bwidge_to_pvt(ds, bwidge.num))
		dev_eww(ds->dev, "faiwed to wemap cwoss-chip Powt VWAN\n");

	if (mv88e6xxx_bwidge_map(chip, bwidge) ||
	    mv88e6xxx_powt_vwan_map(chip, powt))
		dev_eww(ds->dev, "faiwed to wemap in-chip Powt VWAN\n");

	eww = mv88e6xxx_powt_set_map_da(chip, powt, fawse);
	if (eww)
		dev_eww(ds->dev,
			"powt %d faiwed to westowe map-DA: %pe\n",
			powt, EWW_PTW(eww));

	eww = mv88e6xxx_powt_commit_pvid(chip, powt);
	if (eww)
		dev_eww(ds->dev,
			"powt %d faiwed to westowe standawone pvid: %pe\n",
			powt, EWW_PTW(eww));

	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_cwosschip_bwidge_join(stwuct dsa_switch *ds,
					   int twee_index, int sw_index,
					   int powt, stwuct dsa_bwidge bwidge,
					   stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (twee_index != ds->dst->index)
		wetuwn 0;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_pvt_map(chip, sw_index, powt);
	eww = eww ? : mv88e6xxx_map_viwtuaw_bwidge_to_pvt(ds, bwidge.num);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static void mv88e6xxx_cwosschip_bwidge_weave(stwuct dsa_switch *ds,
					     int twee_index, int sw_index,
					     int powt, stwuct dsa_bwidge bwidge)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	if (twee_index != ds->dst->index)
		wetuwn;

	mv88e6xxx_weg_wock(chip);
	if (mv88e6xxx_pvt_map(chip, sw_index, powt) ||
	    mv88e6xxx_map_viwtuaw_bwidge_to_pvt(ds, bwidge.num))
		dev_eww(ds->dev, "faiwed to wemap cwoss-chip Powt VWAN\n");
	mv88e6xxx_weg_unwock(chip);
}

static int mv88e6xxx_softwawe_weset(stwuct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->weset)
		wetuwn chip->info->ops->weset(chip);

	wetuwn 0;
}

static void mv88e6xxx_hawdwawe_weset(stwuct mv88e6xxx_chip *chip)
{
	stwuct gpio_desc *gpiod = chip->weset;

	/* If thewe is a GPIO connected to the weset pin, toggwe it */
	if (gpiod) {
		/* If the switch has just been weset and not yet compweted
		 * woading EEPWOM, the weset may intewwupt the I2C twansaction
		 * mid-byte, causing the fiwst EEPWOM wead aftew the weset
		 * fwom the wwong wocation wesuwting in the switch booting
		 * to wwong mode and inopewabwe.
		 */
		if (chip->info->ops->get_eepwom)
			mv88e6xxx_g2_eepwom_wait(chip);

		gpiod_set_vawue_cansweep(gpiod, 1);
		usweep_wange(10000, 20000);
		gpiod_set_vawue_cansweep(gpiod, 0);
		usweep_wange(10000, 20000);

		if (chip->info->ops->get_eepwom)
			mv88e6xxx_g2_eepwom_wait(chip);
	}
}

static int mv88e6xxx_disabwe_powts(stwuct mv88e6xxx_chip *chip)
{
	int i, eww;

	/* Set aww powts to the Disabwed state */
	fow (i = 0; i < mv88e6xxx_num_powts(chip); i++) {
		eww = mv88e6xxx_powt_set_state(chip, i, BW_STATE_DISABWED);
		if (eww)
			wetuwn eww;
	}

	/* Wait fow twansmit queues to dwain,
	 * i.e. 2ms fow a maximum fwame to be twansmitted at 10 Mbps.
	 */
	usweep_wange(2000, 4000);

	wetuwn 0;
}

static int mv88e6xxx_switch_weset(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	eww = mv88e6xxx_disabwe_powts(chip);
	if (eww)
		wetuwn eww;

	mv88e6xxx_hawdwawe_weset(chip);

	wetuwn mv88e6xxx_softwawe_weset(chip);
}

static int mv88e6xxx_set_powt_mode(stwuct mv88e6xxx_chip *chip, int powt,
				   enum mv88e6xxx_fwame_mode fwame,
				   enum mv88e6xxx_egwess_mode egwess, u16 etype)
{
	int eww;

	if (!chip->info->ops->powt_set_fwame_mode)
		wetuwn -EOPNOTSUPP;

	eww = mv88e6xxx_powt_set_egwess_mode(chip, powt, egwess);
	if (eww)
		wetuwn eww;

	eww = chip->info->ops->powt_set_fwame_mode(chip, powt, fwame);
	if (eww)
		wetuwn eww;

	if (chip->info->ops->powt_set_ethew_type)
		wetuwn chip->info->ops->powt_set_ethew_type(chip, powt, etype);

	wetuwn 0;
}

static int mv88e6xxx_set_powt_mode_nowmaw(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_set_powt_mode(chip, powt, MV88E6XXX_FWAME_MODE_NOWMAW,
				       MV88E6XXX_EGWESS_MODE_UNMODIFIED,
				       MV88E6XXX_POWT_ETH_TYPE_DEFAUWT);
}

static int mv88e6xxx_set_powt_mode_dsa(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_set_powt_mode(chip, powt, MV88E6XXX_FWAME_MODE_DSA,
				       MV88E6XXX_EGWESS_MODE_UNMODIFIED,
				       MV88E6XXX_POWT_ETH_TYPE_DEFAUWT);
}

static int mv88e6xxx_set_powt_mode_edsa(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_set_powt_mode(chip, powt,
				       MV88E6XXX_FWAME_MODE_ETHEWTYPE,
				       MV88E6XXX_EGWESS_MODE_ETHEWTYPE,
				       ETH_P_EDSA);
}

static int mv88e6xxx_setup_powt_mode(stwuct mv88e6xxx_chip *chip, int powt)
{
	if (dsa_is_dsa_powt(chip->ds, powt))
		wetuwn mv88e6xxx_set_powt_mode_dsa(chip, powt);

	if (dsa_is_usew_powt(chip->ds, powt))
		wetuwn mv88e6xxx_set_powt_mode_nowmaw(chip, powt);

	/* Setup CPU powt mode depending on its suppowted tag fowmat */
	if (chip->tag_pwotocow == DSA_TAG_PWOTO_DSA)
		wetuwn mv88e6xxx_set_powt_mode_dsa(chip, powt);

	if (chip->tag_pwotocow == DSA_TAG_PWOTO_EDSA)
		wetuwn mv88e6xxx_set_powt_mode_edsa(chip, powt);

	wetuwn -EINVAW;
}

static int mv88e6xxx_setup_message_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	boow message = dsa_is_dsa_powt(chip->ds, powt);

	wetuwn mv88e6xxx_powt_set_message_powt(chip, powt, message);
}

static int mv88e6xxx_setup_egwess_fwoods(stwuct mv88e6xxx_chip *chip, int powt)
{
	int eww;

	if (chip->info->ops->powt_set_ucast_fwood) {
		eww = chip->info->ops->powt_set_ucast_fwood(chip, powt, twue);
		if (eww)
			wetuwn eww;
	}
	if (chip->info->ops->powt_set_mcast_fwood) {
		eww = chip->info->ops->powt_set_mcast_fwood(chip, powt, twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_set_egwess_powt(stwuct mv88e6xxx_chip *chip,
				     enum mv88e6xxx_egwess_diwection diwection,
				     int powt)
{
	int eww;

	if (!chip->info->ops->set_egwess_powt)
		wetuwn -EOPNOTSUPP;

	eww = chip->info->ops->set_egwess_powt(chip, diwection, powt);
	if (eww)
		wetuwn eww;

	if (diwection == MV88E6XXX_EGWESS_DIW_INGWESS)
		chip->ingwess_dest_powt = powt;
	ewse
		chip->egwess_dest_powt = powt;

	wetuwn 0;
}

static int mv88e6xxx_setup_upstweam_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct dsa_switch *ds = chip->ds;
	int upstweam_powt;
	int eww;

	upstweam_powt = dsa_upstweam_powt(ds, powt);
	if (chip->info->ops->powt_set_upstweam_powt) {
		eww = chip->info->ops->powt_set_upstweam_powt(chip, powt,
							      upstweam_powt);
		if (eww)
			wetuwn eww;
	}

	if (powt == upstweam_powt) {
		if (chip->info->ops->set_cpu_powt) {
			eww = chip->info->ops->set_cpu_powt(chip,
							    upstweam_powt);
			if (eww)
				wetuwn eww;
		}

		eww = mv88e6xxx_set_egwess_powt(chip,
						MV88E6XXX_EGWESS_DIW_INGWESS,
						upstweam_powt);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;

		eww = mv88e6xxx_set_egwess_powt(chip,
						MV88E6XXX_EGWESS_DIW_EGWESS,
						upstweam_powt);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_setup_powt(stwuct mv88e6xxx_chip *chip, int powt)
{
	stwuct device_node *phy_handwe = NUWW;
	stwuct dsa_switch *ds = chip->ds;
	stwuct dsa_powt *dp;
	int tx_amp;
	int eww;
	u16 weg;

	chip->powts[powt].chip = chip;
	chip->powts[powt].powt = powt;

	eww = mv88e6xxx_powt_setup_mac(chip, powt, WINK_UNFOWCED,
				       SPEED_UNFOWCED, DUPWEX_UNFOWCED,
				       PAUSE_ON, PHY_INTEWFACE_MODE_NA);
	if (eww)
		wetuwn eww;

	/* Powt Contwow: disabwe Dwop-on-Unwock, disabwe Dwop-on-Wock,
	 * disabwe Headew mode, enabwe IGMP/MWD snooping, disabwe VWAN
	 * tunnewing, detewmine pwiowity by wooking at 802.1p and IP
	 * pwiowity fiewds (IP pwio has pwecedence), and set STP state
	 * to Fowwawding.
	 *
	 * If this is the CPU wink, use DSA ow EDSA tagging depending
	 * on which tagging mode was configuwed.
	 *
	 * If this is a wink to anothew switch, use DSA tagging mode.
	 *
	 * If this is the upstweam powt fow this switch, enabwe
	 * fowwawding of unknown unicasts and muwticasts.
	 */
	weg = MV88E6185_POWT_CTW0_USE_TAG | MV88E6185_POWT_CTW0_USE_IP |
		MV88E6XXX_POWT_CTW0_STATE_FOWWAWDING;
	/* Fowwawd any IPv4 IGMP ow IPv6 MWD fwames weceived
	 * by a USEW powt to the CPU powt to awwow snooping.
	 */
	if (dsa_is_usew_powt(ds, powt))
		weg |= MV88E6XXX_POWT_CTW0_IGMP_MWD_SNOOP;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_CTW0, weg);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_setup_powt_mode(chip, powt);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_setup_egwess_fwoods(chip, powt);
	if (eww)
		wetuwn eww;

	/* Powt Contwow 2: don't fowce a good FCS, set the MTU size to
	 * 10222 bytes, disabwe 802.1q tags checking, don't discawd
	 * tagged ow untagged fwames on this powt, skip destination
	 * addwess wookup on usew powts, disabwe AWP miwwowing and don't
	 * send a copy of aww twansmitted/weceived fwames on this powt
	 * to the CPU.
	 */
	eww = mv88e6xxx_powt_set_map_da(chip, powt, !dsa_is_usew_powt(ds, powt));
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_setup_upstweam_powt(chip, powt);
	if (eww)
		wetuwn eww;

	/* On chips that suppowt it, set aww downstweam DSA powts'
	 * VWAN powicy to TWAP. In combination with woading
	 * MV88E6XXX_VID_STANDAWONE as a powicy entwy in the VTU, this
	 * pwovides a bettew isowation bawwiew between standawone
	 * powts, as the ATU is bypassed on any intewmediate switches
	 * between the incoming powt and the CPU.
	 */
	if (dsa_is_downstweam_powt(ds, powt) &&
	    chip->info->ops->powt_set_powicy) {
		eww = chip->info->ops->powt_set_powicy(chip, powt,
						MV88E6XXX_POWICY_MAPPING_VTU,
						MV88E6XXX_POWICY_ACTION_TWAP);
		if (eww)
			wetuwn eww;
	}

	/* Usew powts stawt out in standawone mode and 802.1Q is
	 * thewefowe disabwed. On DSA powts, aww vawid VIDs awe awways
	 * woaded in the VTU - thewefowe, enabwe 802.1Q in owdew to take
	 * advantage of VWAN powicy on chips that suppowts it.
	 */
	eww = mv88e6xxx_powt_set_8021q_mode(chip, powt,
				dsa_is_usew_powt(ds, powt) ?
				MV88E6XXX_POWT_CTW2_8021Q_MODE_DISABWED :
				MV88E6XXX_POWT_CTW2_8021Q_MODE_SECUWE);
	if (eww)
		wetuwn eww;

	/* Bind MV88E6XXX_VID_STANDAWONE to MV88E6XXX_FID_STANDAWONE by
	 * viwtue of the fact that mv88e6xxx_atu_new() wiww pick it as
	 * the fiwst fwee FID. This wiww be used as the pwivate PVID fow
	 * unbwidged powts. Shawed (DSA and CPU) powts must awso be
	 * membews of this VID, in owdew to twap aww fwames assigned to
	 * it to the CPU.
	 */
	eww = mv88e6xxx_powt_vwan_join(chip, powt, MV88E6XXX_VID_STANDAWONE,
				       MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNMODIFIED,
				       fawse);
	if (eww)
		wetuwn eww;

	/* Associate MV88E6XXX_VID_BWIDGED with MV88E6XXX_FID_BWIDGED in the
	 * ATU by viwtue of the fact that mv88e6xxx_atu_new() wiww pick it as
	 * the fiwst fwee FID aftew MV88E6XXX_FID_STANDAWONE. This wiww be used
	 * as the pwivate PVID on powts undew a VWAN-unawawe bwidge.
	 * Shawed (DSA and CPU) powts must awso be membews of it, to twanswate
	 * the VID fwom the DSA tag into MV88E6XXX_FID_BWIDGED, instead of
	 * wewying on theiw powt defauwt FID.
	 */
	eww = mv88e6xxx_powt_vwan_join(chip, powt, MV88E6XXX_VID_BWIDGED,
				       MV88E6XXX_G1_VTU_DATA_MEMBEW_TAG_UNMODIFIED,
				       fawse);
	if (eww)
		wetuwn eww;

	if (chip->info->ops->powt_set_jumbo_size) {
		eww = chip->info->ops->powt_set_jumbo_size(chip, powt, 10218);
		if (eww)
			wetuwn eww;
	}

	/* Powt Association Vectow: disabwe automatic addwess weawning
	 * on aww usew powts since they stawt out in standawone
	 * mode. When joining a bwidge, weawning wiww be configuwed to
	 * match the bwidge powt settings. Enabwe weawning on aww
	 * DSA/CPU powts. NOTE: FWOM_CPU fwames awways bypass the
	 * weawning pwocess.
	 *
	 * Disabwe HowdAt1, IntOnAgeOut, WockedPowt, IgnoweWwongData,
	 * and WefweshWocked. I.e. setup standawd automatic weawning.
	 */
	if (dsa_is_usew_powt(ds, powt))
		weg = 0;
	ewse
		weg = 1 << powt;

	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_ASSOC_VECTOW,
				   weg);
	if (eww)
		wetuwn eww;

	/* Egwess wate contwow 2: disabwe egwess wate contwow. */
	eww = mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_EGWESS_WATE_CTW2,
				   0x0000);
	if (eww)
		wetuwn eww;

	if (chip->info->ops->powt_pause_wimit) {
		eww = chip->info->ops->powt_pause_wimit(chip, powt, 0, 0);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->powt_disabwe_weawn_wimit) {
		eww = chip->info->ops->powt_disabwe_weawn_wimit(chip, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->powt_disabwe_pwi_ovewwide) {
		eww = chip->info->ops->powt_disabwe_pwi_ovewwide(chip, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->powt_tag_wemap) {
		eww = chip->info->ops->powt_tag_wemap(chip, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->powt_egwess_wate_wimiting) {
		eww = chip->info->ops->powt_egwess_wate_wimiting(chip, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->powt_setup_message_powt) {
		eww = chip->info->ops->powt_setup_message_powt(chip, powt);
		if (eww)
			wetuwn eww;
	}

	if (chip->info->ops->sewdes_set_tx_ampwitude) {
		dp = dsa_to_powt(ds, powt);
		if (dp)
			phy_handwe = of_pawse_phandwe(dp->dn, "phy-handwe", 0);

		if (phy_handwe && !of_pwopewty_wead_u32(phy_handwe,
							"tx-p2p-micwovowt",
							&tx_amp))
			eww = chip->info->ops->sewdes_set_tx_ampwitude(chip,
								powt, tx_amp);
		if (phy_handwe) {
			of_node_put(phy_handwe);
			if (eww)
				wetuwn eww;
		}
	}

	/* Powt based VWAN map: give each powt the same defauwt addwess
	 * database, and awwow bidiwectionaw communication between the
	 * CPU and DSA powt(s), and the othew powts.
	 */
	eww = mv88e6xxx_powt_set_fid(chip, powt, MV88E6XXX_FID_STANDAWONE);
	if (eww)
		wetuwn eww;

	eww = mv88e6xxx_powt_vwan_map(chip, powt);
	if (eww)
		wetuwn eww;

	/* Defauwt VWAN ID and pwiowity: don't set a defauwt VWAN
	 * ID, and set the defauwt packet pwiowity to zewo.
	 */
	wetuwn mv88e6xxx_powt_wwite(chip, powt, MV88E6XXX_POWT_DEFAUWT_VWAN, 0);
}

static int mv88e6xxx_get_max_mtu(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	if (chip->info->ops->powt_set_jumbo_size)
		wetuwn 10240 - VWAN_ETH_HWEN - EDSA_HWEN - ETH_FCS_WEN;
	ewse if (chip->info->ops->set_max_fwame_size)
		wetuwn 1632 - VWAN_ETH_HWEN - EDSA_HWEN - ETH_FCS_WEN;
	wetuwn ETH_DATA_WEN;
}

static int mv88e6xxx_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int wet = 0;

	/* Fow famiwies whewe we don't know how to awtew the MTU,
	 * just accept any vawue up to ETH_DATA_WEN
	 */
	if (!chip->info->ops->powt_set_jumbo_size &&
	    !chip->info->ops->set_max_fwame_size) {
		if (new_mtu > ETH_DATA_WEN)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	if (dsa_is_dsa_powt(ds, powt) || dsa_is_cpu_powt(ds, powt))
		new_mtu += EDSA_HWEN;

	mv88e6xxx_weg_wock(chip);
	if (chip->info->ops->powt_set_jumbo_size)
		wet = chip->info->ops->powt_set_jumbo_size(chip, powt, new_mtu);
	ewse if (chip->info->ops->set_max_fwame_size)
		wet = chip->info->ops->set_max_fwame_size(chip, new_mtu);
	mv88e6xxx_weg_unwock(chip);

	wetuwn wet;
}

static int mv88e6xxx_set_ageing_time(stwuct dsa_switch *ds,
				     unsigned int ageing_time)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_g1_atu_set_age_time(chip, ageing_time);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_stats_setup(stwuct mv88e6xxx_chip *chip)
{
	int eww;

	/* Initiawize the statistics unit */
	if (chip->info->ops->stats_set_histogwam) {
		eww = chip->info->ops->stats_set_histogwam(chip);
		if (eww)
			wetuwn eww;
	}

	wetuwn mv88e6xxx_g1_stats_cweaw(chip);
}

/* Check if the ewwata has awweady been appwied. */
static boow mv88e6390_setup_ewwata_appwied(stwuct mv88e6xxx_chip *chip)
{
	int powt;
	int eww;
	u16 vaw;

	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		eww = mv88e6xxx_powt_hidden_wead(chip, 0xf, powt, 0, &vaw);
		if (eww) {
			dev_eww(chip->dev,
				"Ewwow weading hidden wegistew: %d\n", eww);
			wetuwn fawse;
		}
		if (vaw != 0x01c0)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* The 6390 coppew powts have an ewwata which wequiwe poking magic
 * vawues into undocumented hidden wegistews and then pewfowming a
 * softwawe weset.
 */
static int mv88e6390_setup_ewwata(stwuct mv88e6xxx_chip *chip)
{
	int powt;
	int eww;

	if (mv88e6390_setup_ewwata_appwied(chip))
		wetuwn 0;

	/* Set the powts into bwocking mode */
	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		eww = mv88e6xxx_powt_set_state(chip, powt, BW_STATE_DISABWED);
		if (eww)
			wetuwn eww;
	}

	fow (powt = 0; powt < mv88e6xxx_num_powts(chip); powt++) {
		eww = mv88e6xxx_powt_hidden_wwite(chip, 0xf, powt, 0, 0x01c0);
		if (eww)
			wetuwn eww;
	}

	wetuwn mv88e6xxx_softwawe_weset(chip);
}

/* pwod_id fow switch famiwies which do not have a PHY modew numbew */
static const u16 famiwy_pwod_id_tabwe[] = {
	[MV88E6XXX_FAMIWY_6341] = MV88E6XXX_POWT_SWITCH_ID_PWOD_6341,
	[MV88E6XXX_FAMIWY_6390] = MV88E6XXX_POWT_SWITCH_ID_PWOD_6390,
	[MV88E6XXX_FAMIWY_6393] = MV88E6XXX_POWT_SWITCH_ID_PWOD_6393X,
};

static int mv88e6xxx_mdio_wead(stwuct mii_bus *bus, int phy, int weg)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	stwuct mv88e6xxx_chip *chip = mdio_bus->chip;
	u16 pwod_id;
	u16 vaw;
	int eww;

	if (!chip->info->ops->phy_wead)
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->phy_wead(chip, bus, phy, weg, &vaw);
	mv88e6xxx_weg_unwock(chip);

	/* Some intewnaw PHYs don't have a modew numbew. */
	if (weg == MII_PHYSID2 && !(vaw & 0x3f0) &&
	    chip->info->famiwy < AWWAY_SIZE(famiwy_pwod_id_tabwe)) {
		pwod_id = famiwy_pwod_id_tabwe[chip->info->famiwy];
		if (pwod_id)
			vaw |= pwod_id >> 4;
	}

	wetuwn eww ? eww : vaw;
}

static int mv88e6xxx_mdio_wead_c45(stwuct mii_bus *bus, int phy, int devad,
				   int weg)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	stwuct mv88e6xxx_chip *chip = mdio_bus->chip;
	u16 vaw;
	int eww;

	if (!chip->info->ops->phy_wead_c45)
		wetuwn 0xffff;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->phy_wead_c45(chip, bus, phy, devad, weg, &vaw);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww ? eww : vaw;
}

static int mv88e6xxx_mdio_wwite(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	stwuct mv88e6xxx_chip *chip = mdio_bus->chip;
	int eww;

	if (!chip->info->ops->phy_wwite)
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->phy_wwite(chip, bus, phy, weg, vaw);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_mdio_wwite_c45(stwuct mii_bus *bus, int phy, int devad,
				    int weg, u16 vaw)
{
	stwuct mv88e6xxx_mdio_bus *mdio_bus = bus->pwiv;
	stwuct mv88e6xxx_chip *chip = mdio_bus->chip;
	int eww;

	if (!chip->info->ops->phy_wwite_c45)
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->phy_wwite_c45(chip, bus, phy, devad, weg, vaw);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_mdio_wegistew(stwuct mv88e6xxx_chip *chip,
				   stwuct device_node *np,
				   boow extewnaw)
{
	static int index;
	stwuct mv88e6xxx_mdio_bus *mdio_bus;
	stwuct mii_bus *bus;
	int eww;

	if (extewnaw) {
		mv88e6xxx_weg_wock(chip);
		eww = mv88e6xxx_g2_scwatch_gpio_set_smi(chip, twue);
		mv88e6xxx_weg_unwock(chip);

		if (eww)
			wetuwn eww;
	}

	bus = mdiobus_awwoc_size(sizeof(*mdio_bus));
	if (!bus)
		wetuwn -ENOMEM;

	mdio_bus = bus->pwiv;
	mdio_bus->bus = bus;
	mdio_bus->chip = chip;
	INIT_WIST_HEAD(&mdio_bus->wist);
	mdio_bus->extewnaw = extewnaw;

	if (np) {
		bus->name = np->fuww_name;
		snpwintf(bus->id, MII_BUS_ID_SIZE, "%pOF", np);
	} ewse {
		bus->name = "mv88e6xxx SMI";
		snpwintf(bus->id, MII_BUS_ID_SIZE, "mv88e6xxx-%d", index++);
	}

	bus->wead = mv88e6xxx_mdio_wead;
	bus->wwite = mv88e6xxx_mdio_wwite;
	bus->wead_c45 = mv88e6xxx_mdio_wead_c45;
	bus->wwite_c45 = mv88e6xxx_mdio_wwite_c45;
	bus->pawent = chip->dev;
	bus->phy_mask = ~GENMASK(chip->info->phy_base_addw +
				 mv88e6xxx_num_powts(chip) - 1,
				 chip->info->phy_base_addw);

	if (!extewnaw) {
		eww = mv88e6xxx_g2_iwq_mdio_setup(chip, bus);
		if (eww)
			goto out;
	}

	eww = of_mdiobus_wegistew(bus, np);
	if (eww) {
		dev_eww(chip->dev, "Cannot wegistew MDIO bus (%d)\n", eww);
		mv88e6xxx_g2_iwq_mdio_fwee(chip, bus);
		goto out;
	}

	if (extewnaw)
		wist_add_taiw(&mdio_bus->wist, &chip->mdios);
	ewse
		wist_add(&mdio_bus->wist, &chip->mdios);

	wetuwn 0;

out:
	mdiobus_fwee(bus);
	wetuwn eww;
}

static void mv88e6xxx_mdios_unwegistew(stwuct mv88e6xxx_chip *chip)

{
	stwuct mv88e6xxx_mdio_bus *mdio_bus, *p;
	stwuct mii_bus *bus;

	wist_fow_each_entwy_safe(mdio_bus, p, &chip->mdios, wist) {
		bus = mdio_bus->bus;

		if (!mdio_bus->extewnaw)
			mv88e6xxx_g2_iwq_mdio_fwee(chip, bus);

		mdiobus_unwegistew(bus);
		mdiobus_fwee(bus);
	}
}

static int mv88e6xxx_mdios_wegistew(stwuct mv88e6xxx_chip *chip)
{
	stwuct device_node *np = chip->dev->of_node;
	stwuct device_node *chiwd;
	int eww;

	/* Awways wegistew one mdio bus fow the intewnaw/defauwt mdio
	 * bus. This maybe wepwesented in the device twee, but is
	 * optionaw.
	 */
	chiwd = of_get_chiwd_by_name(np, "mdio");
	eww = mv88e6xxx_mdio_wegistew(chip, chiwd, fawse);
	of_node_put(chiwd);
	if (eww)
		wetuwn eww;

	/* Wawk the device twee, and see if thewe awe any othew nodes
	 * which say they awe compatibwe with the extewnaw mdio
	 * bus.
	 */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		if (of_device_is_compatibwe(
			    chiwd, "mawveww,mv88e6xxx-mdio-extewnaw")) {
			eww = mv88e6xxx_mdio_wegistew(chip, chiwd, twue);
			if (eww) {
				mv88e6xxx_mdios_unwegistew(chip);
				of_node_put(chiwd);
				wetuwn eww;
			}
		}
	}

	wetuwn 0;
}

static void mv88e6xxx_teawdown(stwuct dsa_switch *ds)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	mv88e6xxx_teawdown_devwink_pawams(ds);
	dsa_devwink_wesouwces_unwegistew(ds);
	mv88e6xxx_teawdown_devwink_wegions_gwobaw(ds);
	mv88e6xxx_mdios_unwegistew(chip);
}

static int mv88e6xxx_setup(stwuct dsa_switch *ds)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	u8 cmode;
	int eww;
	int i;

	eww = mv88e6xxx_mdios_wegistew(chip);
	if (eww)
		wetuwn eww;

	chip->ds = ds;
	ds->usew_mii_bus = mv88e6xxx_defauwt_mdio_bus(chip);

	/* Since viwtuaw bwidges awe mapped in the PVT, the numbew we suppowt
	 * depends on the physicaw switch topowogy. We need to wet DSA figuwe
	 * that out and thewefowe we cannot set this at dsa_wegistew_switch()
	 * time.
	 */
	if (mv88e6xxx_has_pvt(chip))
		ds->max_num_bwidges = MV88E6XXX_MAX_PVT_SWITCHES -
				      ds->dst->wast_switch - 1;

	mv88e6xxx_weg_wock(chip);

	if (chip->info->ops->setup_ewwata) {
		eww = chip->info->ops->setup_ewwata(chip);
		if (eww)
			goto unwock;
	}

	/* Cache the cmode of each powt. */
	fow (i = 0; i < mv88e6xxx_num_powts(chip); i++) {
		if (chip->info->ops->powt_get_cmode) {
			eww = chip->info->ops->powt_get_cmode(chip, i, &cmode);
			if (eww)
				goto unwock;

			chip->powts[i].cmode = cmode;
		}
	}

	eww = mv88e6xxx_vtu_setup(chip);
	if (eww)
		goto unwock;

	/* Must be cawwed aftew mv88e6xxx_vtu_setup (which fwushes the
	 * VTU, theweby awso fwushing the STU).
	 */
	eww = mv88e6xxx_stu_setup(chip);
	if (eww)
		goto unwock;

	/* Setup Switch Powt Wegistews */
	fow (i = 0; i < mv88e6xxx_num_powts(chip); i++) {
		if (dsa_is_unused_powt(ds, i))
			continue;

		/* Pwevent the use of an invawid powt. */
		if (mv88e6xxx_is_invawid_powt(chip, i)) {
			dev_eww(chip->dev, "powt %d is invawid\n", i);
			eww = -EINVAW;
			goto unwock;
		}

		eww = mv88e6xxx_setup_powt(chip, i);
		if (eww)
			goto unwock;
	}

	eww = mv88e6xxx_iww_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_mac_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_phy_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_pvt_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_atu_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_bwoadcast_setup(chip, 0);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_pot_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_wmu_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_wsvd2cpu_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_twunk_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_devmap_setup(chip);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_pwi_setup(chip);
	if (eww)
		goto unwock;

	/* Setup PTP Hawdwawe Cwock and timestamping */
	if (chip->info->ptp_suppowt) {
		eww = mv88e6xxx_ptp_setup(chip);
		if (eww)
			goto unwock;

		eww = mv88e6xxx_hwtstamp_setup(chip);
		if (eww)
			goto unwock;
	}

	eww = mv88e6xxx_stats_setup(chip);
	if (eww)
		goto unwock;

unwock:
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		goto out_mdios;

	/* Have to be cawwed without howding the wegistew wock, since
	 * they take the devwink wock, and we watew take the wocks in
	 * the wevewse owdew when getting/setting pawametews ow
	 * wesouwce occupancy.
	 */
	eww = mv88e6xxx_setup_devwink_wesouwces(ds);
	if (eww)
		goto out_mdios;

	eww = mv88e6xxx_setup_devwink_pawams(ds);
	if (eww)
		goto out_wesouwces;

	eww = mv88e6xxx_setup_devwink_wegions_gwobaw(ds);
	if (eww)
		goto out_pawams;

	wetuwn 0;

out_pawams:
	mv88e6xxx_teawdown_devwink_pawams(ds);
out_wesouwces:
	dsa_devwink_wesouwces_unwegistew(ds);
out_mdios:
	mv88e6xxx_mdios_unwegistew(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_setup(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (chip->info->ops->pcs_ops &&
	    chip->info->ops->pcs_ops->pcs_init) {
		eww = chip->info->ops->pcs_ops->pcs_init(chip, powt);
		if (eww)
			wetuwn eww;
	}

	wetuwn mv88e6xxx_setup_devwink_wegions_powt(ds, powt);
}

static void mv88e6xxx_powt_teawdown(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	mv88e6xxx_teawdown_devwink_wegions_powt(ds, powt);

	if (chip->info->ops->pcs_ops &&
	    chip->info->ops->pcs_ops->pcs_teawdown)
		chip->info->ops->pcs_ops->pcs_teawdown(chip, powt);
}

static int mv88e6xxx_get_eepwom_wen(stwuct dsa_switch *ds)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	wetuwn chip->eepwom_wen;
}

static int mv88e6xxx_get_eepwom(stwuct dsa_switch *ds,
				stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (!chip->info->ops->get_eepwom)
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->get_eepwom(chip, eepwom, data);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		wetuwn eww;

	eepwom->magic = 0xc3ec4951;

	wetuwn 0;
}

static int mv88e6xxx_set_eepwom(stwuct dsa_switch *ds,
				stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (!chip->info->ops->set_eepwom)
		wetuwn -EOPNOTSUPP;

	if (eepwom->magic != 0xc3ec4951)
		wetuwn -EINVAW;

	mv88e6xxx_weg_wock(chip);
	eww = chip->info->ops->set_eepwom(chip, eepwom, data);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static const stwuct mv88e6xxx_ops mv88e6085_ops = {
	/* MV88E6XXX_FAMIWY_6097 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g1_set_switch_mac,
	.phy_wead = mv88e6185_phy_ppu_wead,
	.phy_wwite = mv88e6185_phy_ppu_wwite,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.ppu_enabwe = mv88e6185_g1_ppu_enabwe,
	.ppu_disabwe = mv88e6185_g1_ppu_disabwe,
	.weset = mv88e6185_g1_weset,
	.wmu_disabwe = mv88e6085_g1_wmu_disabwe,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6095_ops = {
	/* MV88E6XXX_FAMIWY_6095 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.set_switch_mac = mv88e6xxx_g1_set_switch_mac,
	.phy_wead = mv88e6185_phy_ppu_wead,
	.phy_wwite = mv88e6185_phy_ppu_wwite,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6185_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_set_fwame_mode = mv88e6085_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6185_powt_set_fowwawd_unknown,
	.powt_set_mcast_fwood = mv88e6185_powt_set_defauwt_fowwawd,
	.powt_set_upstweam_powt = mv88e6095_powt_set_upstweam_powt,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.mgmt_wsvd2cpu = mv88e6185_g2_mgmt_wsvd2cpu,
	.ppu_enabwe = mv88e6185_g1_ppu_enabwe,
	.ppu_disabwe = mv88e6185_g1_ppu_disabwe,
	.weset = mv88e6185_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.phywink_get_caps = mv88e6095_phywink_get_caps,
	.pcs_ops = &mv88e6185_pcs_ops,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6097_ops = {
	/* MV88E6XXX_FAMIWY_6097 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6185_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_egwess_wate_wimiting = mv88e6095_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6085_g1_wmu_disabwe,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.phywink_get_caps = mv88e6095_phywink_get_caps,
	.pcs_ops = &mv88e6185_pcs_ops,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6123_ops = {
	/* MV88E6XXX_FAMIWY_6165 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_set_fwame_mode = mv88e6085_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6131_ops = {
	/* MV88E6XXX_FAMIWY_6185 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.set_switch_mac = mv88e6xxx_g1_set_switch_mac,
	.phy_wead = mv88e6185_phy_ppu_wead,
	.phy_wwite = mv88e6185_phy_ppu_wwite,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6185_powt_set_fowwawd_unknown,
	.powt_set_mcast_fwood = mv88e6185_powt_set_defauwt_fowwawd,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_upstweam_powt = mv88e6095_powt_set_upstweam_powt,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_set_pause = mv88e6185_powt_set_pause,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6185_g2_mgmt_wsvd2cpu,
	.ppu_enabwe = mv88e6185_g1_ppu_enabwe,
	.set_cascade_powt = mv88e6185_g1_set_cascade_powt,
	.ppu_disabwe = mv88e6185_g1_ppu_disabwe,
	.weset = mv88e6185_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6141_ops = {
	/* MV88E6XXX_FAMIWY_6341 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6341_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6341_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6341_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu =  mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6341_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.gpio_ops = &mv88e6352_gpio_ops,
	.sewdes_get_sset_count = mv88e6390_sewdes_get_sset_count,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.phywink_get_caps = mv88e6341_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6161_ops = {
	/* MV88E6XXX_FAMIWY_6165 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.avb_ops = &mv88e6165_avb_ops,
	.ptp_ops = &mv88e6165_ptp_ops,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6165_ops = {
	/* MV88E6XXX_FAMIWY_6165 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6165_phy_wead,
	.phy_wwite = mv88e6165_phy_wwite,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.avb_ops = &mv88e6165_avb_ops,
	.ptp_ops = &mv88e6165_ptp_ops,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6171_ops = {
	/* MV88E6XXX_FAMIWY_6351 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.phywink_get_caps = mv88e6351_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6172_ops = {
	/* MV88E6XXX_FAMIWY_6352 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6352_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6352_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_get_wegs_wen = mv88e6352_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6352_sewdes_get_wegs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phywink_get_caps = mv88e6352_phywink_get_caps,
	.pcs_ops = &mv88e6352_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6175_ops = {
	/* MV88E6XXX_FAMIWY_6351 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.phywink_get_caps = mv88e6351_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6176_ops = {
	/* MV88E6XXX_FAMIWY_6352 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6352_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6352_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_iwq_mapping = mv88e6352_sewdes_iwq_mapping,
	.sewdes_get_wegs_wen = mv88e6352_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6352_sewdes_get_wegs,
	.sewdes_set_tx_ampwitude = mv88e6352_sewdes_set_tx_ampwitude,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phywink_get_caps = mv88e6352_phywink_get_caps,
	.pcs_ops = &mv88e6352_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6185_ops = {
	/* MV88E6XXX_FAMIWY_6185 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.set_switch_mac = mv88e6xxx_g1_set_switch_mac,
	.phy_wead = mv88e6185_phy_ppu_wead,
	.phy_wwite = mv88e6185_phy_ppu_wwite,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6185_powt_sync_wink,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_set_fwame_mode = mv88e6085_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6185_powt_set_fowwawd_unknown,
	.powt_set_mcast_fwood = mv88e6185_powt_set_defauwt_fowwawd,
	.powt_egwess_wate_wimiting = mv88e6095_powt_egwess_wate_wimiting,
	.powt_set_upstweam_powt = mv88e6095_powt_set_upstweam_powt,
	.powt_set_pause = mv88e6185_powt_set_pause,
	.powt_get_cmode = mv88e6185_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6xxx_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6185_g2_mgmt_wsvd2cpu,
	.set_cascade_powt = mv88e6185_g1_set_cascade_powt,
	.ppu_enabwe = mv88e6185_g1_ppu_enabwe,
	.ppu_disabwe = mv88e6185_g1_ppu_disabwe,
	.weset = mv88e6185_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
	.pcs_ops = &mv88e6185_pcs_ops,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6190_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phywink_get_caps = mv88e6390_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6190x_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390x_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390x_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390x_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390x_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.phywink_get_caps = mv88e6390x_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6191_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6390_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6240_ops = {
	/* MV88E6XXX_FAMIWY_6352 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6352_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6352_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_iwq_mapping = mv88e6352_sewdes_iwq_mapping,
	.sewdes_get_wegs_wen = mv88e6352_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6352_sewdes_get_wegs,
	.sewdes_set_tx_ampwitude = mv88e6352_sewdes_set_tx_ampwitude,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6352_phywink_get_caps,
	.pcs_ops = &mv88e6352_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6250_ops = {
	/* MV88E6XXX_FAMIWY_6250 */
	.ieee_pwi_map = mv88e6250_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6250_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6250_stats_get_sset_count,
	.stats_get_stwings = mv88e6250_stats_get_stwings,
	.stats_get_stat = mv88e6250_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6250_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6250_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6250_ptp_ops,
	.phywink_get_caps = mv88e6250_phywink_get_caps,
	.set_max_fwame_size = mv88e6185_g1_set_max_fwame_size,
};

static const stwuct mv88e6xxx_ops mv88e6290_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6390_ptp_ops,
	.phywink_get_caps = mv88e6390_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6320_ops = {
	/* MV88E6XXX_FAMIWY_6320 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6320_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6320_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6321_ops = {
	/* MV88E6XXX_FAMIWY_6320 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6320_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6320_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.weset = mv88e6352_g1_weset,
	.vtu_getnext = mv88e6185_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6185_g1_vtu_woadpuwge,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6185_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6341_ops = {
	/* MV88E6XXX_FAMIWY_6341 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6341_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6341_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6341_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu =  mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6341_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.sewdes_get_sset_count = mv88e6390_sewdes_get_sset_count,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.phywink_get_caps = mv88e6341_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6350_ops = {
	/* MV88E6XXX_FAMIWY_6351 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.phywink_get_caps = mv88e6351_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6351_ops = {
	/* MV88E6XXX_FAMIWY_6351 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6185_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6351_phywink_get_caps,
};

static const stwuct mv88e6xxx_ops mv88e6352_ops = {
	/* MV88E6XXX_FAMIWY_6352 */
	.ieee_pwi_map = mv88e6085_g1_ieee_pwi_map,
	.ip_pwi_map = mv88e6085_g1_ip_pwi_map,
	.iww_init_aww = mv88e6352_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom16,
	.set_eepwom = mv88e6xxx_g2_set_eepwom16,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6352_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6352_powt_set_speed_dupwex,
	.powt_tag_wemap = mv88e6095_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6097_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6320_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6095_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6095_stats_get_sset_count,
	.stats_get_stwings = mv88e6095_stats_get_stwings,
	.stats_get_stat = mv88e6095_stats_get_stat,
	.set_cpu_powt = mv88e6095_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6095_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6097_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6352_g2_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6352_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6352_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6352_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6352_g1_stu_getnext,
	.stu_woadpuwge = mv88e6352_g1_stu_woadpuwge,
	.sewdes_iwq_mapping = mv88e6352_sewdes_iwq_mapping,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6352_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.sewdes_get_sset_count = mv88e6352_sewdes_get_sset_count,
	.sewdes_get_stwings = mv88e6352_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6352_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6352_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6352_sewdes_get_wegs,
	.sewdes_set_tx_ampwitude = mv88e6352_sewdes_set_tx_ampwitude,
	.phywink_get_caps = mv88e6352_phywink_get_caps,
	.pcs_ops = &mv88e6352_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6390_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6390_ptp_ops,
	.sewdes_get_sset_count = mv88e6390_sewdes_get_sset_count,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.phywink_get_caps = mv88e6390_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6390x_ops = {
	/* MV88E6XXX_FAMIWY_6390 */
	.setup_ewwata = mv88e6390_setup_ewwata,
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6390x_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6390x_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6352_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6351_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6390x_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	.set_cpu_powt = mv88e6390_g1_set_cpu_powt,
	.set_egwess_powt = mv88e6390_g1_set_egwess_powt,
	.watchdog_ops = &mv88e6390_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6390_g1_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6390x_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	.sewdes_get_sset_count = mv88e6390_sewdes_get_sset_count,
	.sewdes_get_stwings = mv88e6390_sewdes_get_stwings,
	.sewdes_get_stats = mv88e6390_sewdes_get_stats,
	.sewdes_get_wegs_wen = mv88e6390_sewdes_get_wegs_wen,
	.sewdes_get_wegs = mv88e6390_sewdes_get_wegs,
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6390_ptp_ops,
	.phywink_get_caps = mv88e6390x_phywink_get_caps,
	.pcs_ops = &mv88e6390_pcs_ops,
};

static const stwuct mv88e6xxx_ops mv88e6393x_ops = {
	/* MV88E6XXX_FAMIWY_6393 */
	.iww_init_aww = mv88e6390_g2_iww_init_aww,
	.get_eepwom = mv88e6xxx_g2_get_eepwom8,
	.set_eepwom = mv88e6xxx_g2_set_eepwom8,
	.set_switch_mac = mv88e6xxx_g2_set_switch_mac,
	.phy_wead = mv88e6xxx_g2_smi_phy_wead_c22,
	.phy_wwite = mv88e6xxx_g2_smi_phy_wwite_c22,
	.phy_wead_c45 = mv88e6xxx_g2_smi_phy_wead_c45,
	.phy_wwite_c45 = mv88e6xxx_g2_smi_phy_wwite_c45,
	.powt_set_wink = mv88e6xxx_powt_set_wink,
	.powt_sync_wink = mv88e6xxx_powt_sync_wink,
	.powt_set_wgmii_deway = mv88e6390_powt_set_wgmii_deway,
	.powt_set_speed_dupwex = mv88e6393x_powt_set_speed_dupwex,
	.powt_max_speed_mode = mv88e6393x_powt_max_speed_mode,
	.powt_tag_wemap = mv88e6390_powt_tag_wemap,
	.powt_set_powicy = mv88e6393x_powt_set_powicy,
	.powt_set_fwame_mode = mv88e6351_powt_set_fwame_mode,
	.powt_set_ucast_fwood = mv88e6352_powt_set_ucast_fwood,
	.powt_set_mcast_fwood = mv88e6352_powt_set_mcast_fwood,
	.powt_set_ethew_type = mv88e6393x_powt_set_ethew_type,
	.powt_set_jumbo_size = mv88e6165_powt_set_jumbo_size,
	.powt_egwess_wate_wimiting = mv88e6097_powt_egwess_wate_wimiting,
	.powt_pause_wimit = mv88e6390_powt_pause_wimit,
	.powt_disabwe_weawn_wimit = mv88e6xxx_powt_disabwe_weawn_wimit,
	.powt_disabwe_pwi_ovewwide = mv88e6xxx_powt_disabwe_pwi_ovewwide,
	.powt_get_cmode = mv88e6352_powt_get_cmode,
	.powt_set_cmode = mv88e6393x_powt_set_cmode,
	.powt_setup_message_powt = mv88e6xxx_setup_message_powt,
	.powt_set_upstweam_powt = mv88e6393x_powt_set_upstweam_powt,
	.stats_snapshot = mv88e6390_g1_stats_snapshot,
	.stats_set_histogwam = mv88e6390_g1_stats_set_histogwam,
	.stats_get_sset_count = mv88e6320_stats_get_sset_count,
	.stats_get_stwings = mv88e6320_stats_get_stwings,
	.stats_get_stat = mv88e6390_stats_get_stat,
	/* .set_cpu_powt is missing because this famiwy does not suppowt a gwobaw
	 * CPU powt, onwy pew powt CPU powt which is set via
	 * .powt_set_upstweam_powt method.
	 */
	.set_egwess_powt = mv88e6393x_set_egwess_powt,
	.watchdog_ops = &mv88e6393x_watchdog_ops,
	.mgmt_wsvd2cpu = mv88e6393x_powt_mgmt_wsvd2cpu,
	.pot_cweaw = mv88e6xxx_g2_pot_cweaw,
	.weset = mv88e6352_g1_weset,
	.wmu_disabwe = mv88e6390_g1_wmu_disabwe,
	.atu_get_hash = mv88e6165_g1_atu_get_hash,
	.atu_set_hash = mv88e6165_g1_atu_set_hash,
	.vtu_getnext = mv88e6390_g1_vtu_getnext,
	.vtu_woadpuwge = mv88e6390_g1_vtu_woadpuwge,
	.stu_getnext = mv88e6390_g1_stu_getnext,
	.stu_woadpuwge = mv88e6390_g1_stu_woadpuwge,
	.sewdes_get_wane = mv88e6393x_sewdes_get_wane,
	.sewdes_iwq_mapping = mv88e6390_sewdes_iwq_mapping,
	/* TODO: sewdes stats */
	.gpio_ops = &mv88e6352_gpio_ops,
	.avb_ops = &mv88e6390_avb_ops,
	.ptp_ops = &mv88e6352_ptp_ops,
	.phywink_get_caps = mv88e6393x_phywink_get_caps,
	.pcs_ops = &mv88e6393x_pcs_ops,
};

static const stwuct mv88e6xxx_info mv88e6xxx_tabwe[] = {
	[MV88E6020] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6020,
		.famiwy = MV88E6XXX_FAMIWY_6250,
		.name = "Mawveww 88E6020",
		.num_databases = 64,
		.num_powts = 4,
		.num_intewnaw_phys = 2,
		.max_vid = 4095,
		.powt_base_addw = 0x8,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0xf,
		.gwobaw2_addw = 0x7,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 5,
		.atu_move_powt_mask = 0xf,
		.duaw_chip = twue,
		.ops = &mv88e6250_ops,
	},

	[MV88E6071] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6071,
		.famiwy = MV88E6XXX_FAMIWY_6250,
		.name = "Mawveww 88E6071",
		.num_databases = 64,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.powt_base_addw = 0x08,
		.phy_base_addw = 0x00,
		.gwobaw1_addw = 0x0f,
		.gwobaw2_addw = 0x07,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 5,
		.atu_move_powt_mask = 0xf,
		.duaw_chip = twue,
		.ops = &mv88e6250_ops,
	},

	[MV88E6085] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6085,
		.famiwy = MV88E6XXX_FAMIWY_6097,
		.name = "Mawveww 88E6085",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 10,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.ops = &mv88e6085_ops,
	},

	[MV88E6095] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6095,
		.famiwy = MV88E6XXX_FAMIWY_6095,
		.name = "Mawveww 88E6095/88E6095F",
		.num_databases = 256,
		.num_macs = 8192,
		.num_powts = 11,
		.num_intewnaw_phys = 0,
		.max_vid = 4095,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.atu_move_powt_mask = 0xf,
		.muwti_chip = twue,
		.ops = &mv88e6095_ops,
	},

	[MV88E6097] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6097,
		.famiwy = MV88E6XXX_FAMIWY_6097,
		.name = "Mawveww 88E6097/88E6097F",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 11,
		.num_intewnaw_phys = 8,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6097_ops,
	},

	[MV88E6123] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6123,
		.famiwy = MV88E6XXX_FAMIWY_6165,
		.name = "Mawveww 88E6123",
		.num_databases = 4096,
		.num_macs = 1024,
		.num_powts = 3,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6123_ops,
	},

	[MV88E6131] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6131,
		.famiwy = MV88E6XXX_FAMIWY_6185,
		.name = "Mawveww 88E6131",
		.num_databases = 256,
		.num_macs = 8192,
		.num_powts = 8,
		.num_intewnaw_phys = 0,
		.max_vid = 4095,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.atu_move_powt_mask = 0xf,
		.muwti_chip = twue,
		.ops = &mv88e6131_ops,
	},

	[MV88E6141] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6141,
		.famiwy = MV88E6XXX_FAMIWY_6341,
		.name = "Mawveww 88E6141",
		.num_databases = 4096,
		.num_macs = 2048,
		.num_powts = 6,
		.num_intewnaw_phys = 5,
		.num_gpio = 11,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x10,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.atu_move_powt_mask = 0x1f,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6141_ops,
	},

	[MV88E6161] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6161,
		.famiwy = MV88E6XXX_FAMIWY_6165,
		.name = "Mawveww 88E6161",
		.num_databases = 4096,
		.num_macs = 1024,
		.num_powts = 6,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6161_ops,
	},

	[MV88E6165] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6165,
		.famiwy = MV88E6XXX_FAMIWY_6165,
		.name = "Mawveww 88E6165",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 6,
		.num_intewnaw_phys = 0,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6165_ops,
	},

	[MV88E6171] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6171,
		.famiwy = MV88E6XXX_FAMIWY_6351,
		.name = "Mawveww 88E6171",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6171_ops,
	},

	[MV88E6172] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6172,
		.famiwy = MV88E6XXX_FAMIWY_6352,
		.name = "Mawveww 88E6172",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6172_ops,
	},

	[MV88E6175] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6175,
		.famiwy = MV88E6XXX_FAMIWY_6351,
		.name = "Mawveww 88E6175",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6175_ops,
	},

	[MV88E6176] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6176,
		.famiwy = MV88E6XXX_FAMIWY_6352,
		.name = "Mawveww 88E6176",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6176_ops,
	},

	[MV88E6185] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6185,
		.famiwy = MV88E6XXX_FAMIWY_6185,
		.name = "Mawveww 88E6185",
		.num_databases = 256,
		.num_macs = 8192,
		.num_powts = 10,
		.num_intewnaw_phys = 0,
		.max_vid = 4095,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.atu_move_powt_mask = 0xf,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6185_ops,
	},

	[MV88E6190] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6190,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6190",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.pvt = twue,
		.muwti_chip = twue,
		.atu_move_powt_mask = 0x1f,
		.ops = &mv88e6190_ops,
	},

	[MV88E6190X] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6190X,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6190X",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ops = &mv88e6190x_ops,
	},

	[MV88E6191] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6191,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6191",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6191_ops,
	},

	[MV88E6191X] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6191X,
		.famiwy = MV88E6XXX_FAMIWY_6393,
		.name = "Mawveww 88E6191X",
		.num_databases = 4096,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 8,
		.intewnaw_phys_offset = 1,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 10,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6393x_ops,
	},

	[MV88E6193X] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6193X,
		.famiwy = MV88E6XXX_FAMIWY_6393,
		.name = "Mawveww 88E6193X",
		.num_databases = 4096,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 8,
		.intewnaw_phys_offset = 1,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 10,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6393x_ops,
	},

	[MV88E6220] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6220,
		.famiwy = MV88E6XXX_FAMIWY_6250,
		.name = "Mawveww 88E6220",
		.num_databases = 64,

		/* Powts 2-4 awe not wouted to pins
		 * => usabwe powts 0, 1, 5, 6
		 */
		.num_powts = 7,
		.num_intewnaw_phys = 2,
		.invawid_powt_mask = BIT(2) | BIT(3) | BIT(4),
		.max_vid = 4095,
		.powt_base_addw = 0x08,
		.phy_base_addw = 0x00,
		.gwobaw1_addw = 0x0f,
		.gwobaw2_addw = 0x07,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.duaw_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6250_ops,
	},

	[MV88E6240] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6240,
		.famiwy = MV88E6XXX_FAMIWY_6352,
		.name = "Mawveww 88E6240",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6240_ops,
	},

	[MV88E6250] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6250,
		.famiwy = MV88E6XXX_FAMIWY_6250,
		.name = "Mawveww 88E6250",
		.num_databases = 64,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.powt_base_addw = 0x08,
		.phy_base_addw = 0x00,
		.gwobaw1_addw = 0x0f,
		.gwobaw2_addw = 0x07,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.duaw_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6250_ops,
	},

	[MV88E6290] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6290,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6290",
		.num_databases = 4096,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6290_ops,
	},

	[MV88E6320] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6320,
		.famiwy = MV88E6XXX_FAMIWY_6320,
		.name = "Mawveww 88E6320",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6320_ops,
	},

	[MV88E6321] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6321,
		.famiwy = MV88E6XXX_FAMIWY_6320,
		.name = "Mawveww 88E6321",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 8,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6321_ops,
	},

	[MV88E6341] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6341,
		.famiwy = MV88E6XXX_FAMIWY_6341,
		.name = "Mawveww 88E6341",
		.num_databases = 4096,
		.num_macs = 2048,
		.num_intewnaw_phys = 5,
		.num_powts = 6,
		.num_gpio = 11,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x10,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.atu_move_powt_mask = 0x1f,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6341_ops,
	},

	[MV88E6350] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6350,
		.famiwy = MV88E6XXX_FAMIWY_6351,
		.name = "Mawveww 88E6350",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6350_ops,
	},

	[MV88E6351] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6351,
		.famiwy = MV88E6XXX_FAMIWY_6351,
		.name = "Mawveww 88E6351",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ops = &mv88e6351_ops,
	},

	[MV88E6352] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6352,
		.famiwy = MV88E6XXX_FAMIWY_6352,
		.name = "Mawveww 88E6352",
		.num_databases = 4096,
		.num_macs = 8192,
		.num_powts = 7,
		.num_intewnaw_phys = 5,
		.num_gpio = 15,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x10,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 15000,
		.g1_iwqs = 9,
		.g2_iwqs = 10,
		.atu_move_powt_mask = 0xf,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_SUPPOWTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6352_ops,
	},
	[MV88E6361] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6361,
		.famiwy = MV88E6XXX_FAMIWY_6393,
		.name = "Mawveww 88E6361",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,
		/* Powts 1, 2 and 8 awe not wouted */
		.invawid_powt_mask = BIT(1) | BIT(2) | BIT(8),
		.num_intewnaw_phys = 5,
		.intewnaw_phys_offset = 3,
		.max_vid = 4095,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 10,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6393x_ops,
	},
	[MV88E6390] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6390,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6390",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_UNDOCUMENTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6390_ops,
	},
	[MV88E6390X] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6390X,
		.famiwy = MV88E6XXX_FAMIWY_6390,
		.name = "Mawveww 88E6390X",
		.num_databases = 4096,
		.num_macs = 16384,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 9,
		.num_gpio = 16,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 9,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.edsa_suppowt = MV88E6XXX_EDSA_UNDOCUMENTED,
		.ptp_suppowt = twue,
		.ops = &mv88e6390x_ops,
	},

	[MV88E6393X] = {
		.pwod_num = MV88E6XXX_POWT_SWITCH_ID_PWOD_6393X,
		.famiwy = MV88E6XXX_FAMIWY_6393,
		.name = "Mawveww 88E6393X",
		.num_databases = 4096,
		.num_powts = 11,	/* 10 + Z80 */
		.num_intewnaw_phys = 8,
		.intewnaw_phys_offset = 1,
		.max_vid = 8191,
		.max_sid = 63,
		.powt_base_addw = 0x0,
		.phy_base_addw = 0x0,
		.gwobaw1_addw = 0x1b,
		.gwobaw2_addw = 0x1c,
		.age_time_coeff = 3750,
		.g1_iwqs = 10,
		.g2_iwqs = 14,
		.atu_move_powt_mask = 0x1f,
		.pvt = twue,
		.muwti_chip = twue,
		.ptp_suppowt = twue,
		.ops = &mv88e6393x_ops,
	},
};

static const stwuct mv88e6xxx_info *mv88e6xxx_wookup_info(unsigned int pwod_num)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mv88e6xxx_tabwe); ++i)
		if (mv88e6xxx_tabwe[i].pwod_num == pwod_num)
			wetuwn &mv88e6xxx_tabwe[i];

	wetuwn NUWW;
}

static int mv88e6xxx_detect(stwuct mv88e6xxx_chip *chip)
{
	const stwuct mv88e6xxx_info *info;
	unsigned int pwod_num, wev;
	u16 id;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_wead(chip, 0, MV88E6XXX_POWT_SWITCH_ID, &id);
	mv88e6xxx_weg_unwock(chip);
	if (eww)
		wetuwn eww;

	pwod_num = id & MV88E6XXX_POWT_SWITCH_ID_PWOD_MASK;
	wev = id & MV88E6XXX_POWT_SWITCH_ID_WEV_MASK;

	info = mv88e6xxx_wookup_info(pwod_num);
	if (!info)
		wetuwn -ENODEV;

	/* Update the compatibwe info with the pwobed one */
	chip->info = info;

	dev_info(chip->dev, "switch 0x%x detected: %s, wevision %u\n",
		 chip->info->pwod_num, chip->info->name, wev);

	wetuwn 0;
}

static int mv88e6xxx_singwe_chip_detect(stwuct mv88e6xxx_chip *chip,
					stwuct mdio_device *mdiodev)
{
	int eww;

	/* duaw_chip takes pwecedence ovew singwe/muwti-chip modes */
	if (chip->info->duaw_chip)
		wetuwn -EINVAW;

	/* If the mdio addw is 16 indicating the fiwst powt addwess of a switch
	 * (e.g. mv88e6*41) in singwe chip addwessing mode the device may be
	 * configuwed in singwe chip addwessing mode. Setup the smi access as
	 * singwe chip addwessing mode and attempt to detect the modew of the
	 * switch, if this faiws the device is not configuwed in singwe chip
	 * addwessing mode.
	 */
	if (mdiodev->addw != 16)
		wetuwn -EINVAW;

	eww = mv88e6xxx_smi_init(chip, mdiodev->bus, 0);
	if (eww)
		wetuwn eww;

	wetuwn mv88e6xxx_detect(chip);
}

static stwuct mv88e6xxx_chip *mv88e6xxx_awwoc_chip(stwuct device *dev)
{
	stwuct mv88e6xxx_chip *chip;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn NUWW;

	chip->dev = dev;

	mutex_init(&chip->weg_wock);
	INIT_WIST_HEAD(&chip->mdios);
	idw_init(&chip->powicies);
	INIT_WIST_HEAD(&chip->msts);

	wetuwn chip;
}

static enum dsa_tag_pwotocow mv88e6xxx_get_tag_pwotocow(stwuct dsa_switch *ds,
							int powt,
							enum dsa_tag_pwotocow m)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;

	wetuwn chip->tag_pwotocow;
}

static int mv88e6xxx_change_tag_pwotocow(stwuct dsa_switch *ds,
					 enum dsa_tag_pwotocow pwoto)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	enum dsa_tag_pwotocow owd_pwotocow;
	stwuct dsa_powt *cpu_dp;
	int eww;

	switch (pwoto) {
	case DSA_TAG_PWOTO_EDSA:
		switch (chip->info->edsa_suppowt) {
		case MV88E6XXX_EDSA_UNSUPPOWTED:
			wetuwn -EPWOTONOSUPPOWT;
		case MV88E6XXX_EDSA_UNDOCUMENTED:
			dev_wawn(chip->dev, "Wewying on undocumented EDSA tagging behaviow\n");
			fawwthwough;
		case MV88E6XXX_EDSA_SUPPOWTED:
			bweak;
		}
		bweak;
	case DSA_TAG_PWOTO_DSA:
		bweak;
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}

	owd_pwotocow = chip->tag_pwotocow;
	chip->tag_pwotocow = pwoto;

	mv88e6xxx_weg_wock(chip);
	dsa_switch_fow_each_cpu_powt(cpu_dp, ds) {
		eww = mv88e6xxx_setup_powt_mode(chip, cpu_dp->index);
		if (eww) {
			mv88e6xxx_weg_unwock(chip);
			goto unwind;
		}
	}
	mv88e6xxx_weg_unwock(chip);

	wetuwn 0;

unwind:
	chip->tag_pwotocow = owd_pwotocow;

	mv88e6xxx_weg_wock(chip);
	dsa_switch_fow_each_cpu_powt_continue_wevewse(cpu_dp, ds)
		mv88e6xxx_setup_powt_mode(chip, cpu_dp->index);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_mdb_add(stwuct dsa_switch *ds, int powt,
				  const stwuct switchdev_obj_powt_mdb *mdb,
				  stwuct dsa_db db)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_db_woad_puwge(chip, powt, mdb->addw, mdb->vid,
					   MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_mdb_dew(stwuct dsa_switch *ds, int powt,
				  const stwuct switchdev_obj_powt_mdb *mdb,
				  stwuct dsa_db db)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_db_woad_puwge(chip, powt, mdb->addw, mdb->vid, 0);
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static int mv88e6xxx_powt_miwwow_add(stwuct dsa_switch *ds, int powt,
				     stwuct dsa_maww_miwwow_tc_entwy *miwwow,
				     boow ingwess,
				     stwuct netwink_ext_ack *extack)
{
	enum mv88e6xxx_egwess_diwection diwection = ingwess ?
						MV88E6XXX_EGWESS_DIW_INGWESS :
						MV88E6XXX_EGWESS_DIW_EGWESS;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	boow othew_miwwows = fawse;
	int i;
	int eww;

	mutex_wock(&chip->weg_wock);
	if ((ingwess ? chip->ingwess_dest_powt : chip->egwess_dest_powt) !=
	    miwwow->to_wocaw_powt) {
		fow (i = 0; i < mv88e6xxx_num_powts(chip); i++)
			othew_miwwows |= ingwess ?
					 chip->powts[i].miwwow_ingwess :
					 chip->powts[i].miwwow_egwess;

		/* Can't change egwess powt when othew miwwow is active */
		if (othew_miwwows) {
			eww = -EBUSY;
			goto out;
		}

		eww = mv88e6xxx_set_egwess_powt(chip, diwection,
						miwwow->to_wocaw_powt);
		if (eww)
			goto out;
	}

	eww = mv88e6xxx_powt_set_miwwow(chip, powt, diwection, twue);
out:
	mutex_unwock(&chip->weg_wock);

	wetuwn eww;
}

static void mv88e6xxx_powt_miwwow_dew(stwuct dsa_switch *ds, int powt,
				      stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	enum mv88e6xxx_egwess_diwection diwection = miwwow->ingwess ?
						MV88E6XXX_EGWESS_DIW_INGWESS :
						MV88E6XXX_EGWESS_DIW_EGWESS;
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	boow othew_miwwows = fawse;
	int i;

	mutex_wock(&chip->weg_wock);
	if (mv88e6xxx_powt_set_miwwow(chip, powt, diwection, fawse))
		dev_eww(ds->dev, "p%d: faiwed to disabwe miwwowing\n", powt);

	fow (i = 0; i < mv88e6xxx_num_powts(chip); i++)
		othew_miwwows |= miwwow->ingwess ?
				 chip->powts[i].miwwow_ingwess :
				 chip->powts[i].miwwow_egwess;

	/* Weset egwess powt when no othew miwwow is active */
	if (!othew_miwwows) {
		if (mv88e6xxx_set_egwess_powt(chip, diwection,
					      dsa_upstweam_powt(ds, powt)))
			dev_eww(ds->dev, "faiwed to set egwess powt\n");
	}

	mutex_unwock(&chip->weg_wock);
}

static int mv88e6xxx_powt_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
					   stwuct switchdev_bwpowt_fwags fwags,
					   stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	const stwuct mv88e6xxx_ops *ops;

	if (fwags.mask & ~(BW_WEAWNING | BW_FWOOD | BW_MCAST_FWOOD |
			   BW_BCAST_FWOOD | BW_POWT_WOCKED | BW_POWT_MAB))
		wetuwn -EINVAW;

	ops = chip->info->ops;

	if ((fwags.mask & BW_FWOOD) && !ops->powt_set_ucast_fwood)
		wetuwn -EINVAW;

	if ((fwags.mask & BW_MCAST_FWOOD) && !ops->powt_set_mcast_fwood)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int mv88e6xxx_powt_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				       stwuct switchdev_bwpowt_fwags fwags,
				       stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww = 0;

	mv88e6xxx_weg_wock(chip);

	if (fwags.mask & BW_WEAWNING) {
		boow weawning = !!(fwags.vaw & BW_WEAWNING);
		u16 pav = weawning ? (1 << powt) : 0;

		eww = mv88e6xxx_powt_set_assoc_vectow(chip, powt, pav);
		if (eww)
			goto out;
	}

	if (fwags.mask & BW_FWOOD) {
		boow unicast = !!(fwags.vaw & BW_FWOOD);

		eww = chip->info->ops->powt_set_ucast_fwood(chip, powt,
							    unicast);
		if (eww)
			goto out;
	}

	if (fwags.mask & BW_MCAST_FWOOD) {
		boow muwticast = !!(fwags.vaw & BW_MCAST_FWOOD);

		eww = chip->info->ops->powt_set_mcast_fwood(chip, powt,
							    muwticast);
		if (eww)
			goto out;
	}

	if (fwags.mask & BW_BCAST_FWOOD) {
		boow bwoadcast = !!(fwags.vaw & BW_BCAST_FWOOD);

		eww = mv88e6xxx_powt_bwoadcast_sync(chip, powt, bwoadcast);
		if (eww)
			goto out;
	}

	if (fwags.mask & BW_POWT_MAB) {
		boow mab = !!(fwags.vaw & BW_POWT_MAB);

		mv88e6xxx_powt_set_mab(chip, powt, mab);
	}

	if (fwags.mask & BW_POWT_WOCKED) {
		boow wocked = !!(fwags.vaw & BW_POWT_WOCKED);

		eww = mv88e6xxx_powt_set_wock(chip, powt, wocked);
		if (eww)
			goto out;
	}
out:
	mv88e6xxx_weg_unwock(chip);

	wetuwn eww;
}

static boow mv88e6xxx_wag_can_offwoad(stwuct dsa_switch *ds,
				      stwuct dsa_wag wag,
				      stwuct netdev_wag_uppew_info *info,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct dsa_powt *dp;
	int membews = 0;

	if (!mv88e6xxx_has_wag(chip)) {
		NW_SET_EWW_MSG_MOD(extack, "Chip does not suppowt WAG offwoad");
		wetuwn fawse;
	}

	if (!wag.id)
		wetuwn fawse;

	dsa_wag_foweach_powt(dp, ds->dst, &wag)
		/* Incwudes the powt joining the WAG */
		membews++;

	if (membews > 8) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot offwoad mowe than 8 WAG powts");
		wetuwn fawse;
	}

	/* We couwd potentiawwy wewax this to incwude active
	 * backup in the futuwe.
	 */
	if (info->tx_type != NETDEV_WAG_TX_TYPE_HASH) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy offwoad WAG using hash TX type");
		wetuwn fawse;
	}

	/* Ideawwy we wouwd awso vawidate that the hash type matches
	 * the hawdwawe. Awas, this is awways set to unknown on team
	 * intewfaces.
	 */
	wetuwn twue;
}

static int mv88e6xxx_wag_sync_map(stwuct dsa_switch *ds, stwuct dsa_wag wag)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct dsa_powt *dp;
	u16 map = 0;
	int id;

	/* DSA WAG IDs awe one-based, hawdwawe is zewo-based */
	id = wag.id - 1;

	/* Buiwd the map of aww powts to distwibute fwows destined fow
	 * this WAG. This can be eithew a wocaw usew powt, ow a DSA
	 * powt if the WAG powt is on a wemote chip.
	 */
	dsa_wag_foweach_powt(dp, ds->dst, &wag)
		map |= BIT(dsa_towawds_powt(ds, dp->ds->index, dp->index));

	wetuwn mv88e6xxx_g2_twunk_mapping_wwite(chip, id, map);
}

static const u8 mv88e6xxx_wag_mask_tabwe[8][8] = {
	/* Wow numbew cowwesponds to the numbew of active membews in a
	 * WAG. Each cowumn states which of the eight hash buckets awe
	 * mapped to the cowumn:th powt in the WAG.
	 *
	 * Exampwe: In a WAG with thwee active powts, the second powt
	 * ([2][1]) wouwd be sewected fow twaffic mapped to buckets
	 * 3,4,5 (0x38).
	 */
	{ 0xff,    0,    0,    0,    0,    0,    0,    0 },
	{ 0x0f, 0xf0,    0,    0,    0,    0,    0,    0 },
	{ 0x07, 0x38, 0xc0,    0,    0,    0,    0,    0 },
	{ 0x03, 0x0c, 0x30, 0xc0,    0,    0,    0,    0 },
	{ 0x03, 0x0c, 0x30, 0x40, 0x80,    0,    0,    0 },
	{ 0x03, 0x0c, 0x10, 0x20, 0x40, 0x80,    0,    0 },
	{ 0x03, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,    0 },
	{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 },
};

static void mv88e6xxx_wag_set_powt_mask(u16 *mask, int powt,
					int num_tx, int nth)
{
	u8 active = 0;
	int i;

	num_tx = num_tx <= 8 ? num_tx : 8;
	if (nth < num_tx)
		active = mv88e6xxx_wag_mask_tabwe[num_tx - 1][nth];

	fow (i = 0; i < 8; i++) {
		if (BIT(i) & active)
			mask[i] |= BIT(powt);
	}
}

static int mv88e6xxx_wag_sync_masks(stwuct dsa_switch *ds)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	unsigned int id, num_tx;
	stwuct dsa_powt *dp;
	stwuct dsa_wag *wag;
	int i, eww, nth;
	u16 mask[8];
	u16 ivec;

	/* Assume no powt is a membew of any WAG. */
	ivec = BIT(mv88e6xxx_num_powts(chip)) - 1;

	/* Disabwe aww masks fow powts that _awe_ membews of a WAG. */
	dsa_switch_fow_each_powt(dp, ds) {
		if (!dp->wag)
			continue;

		ivec &= ~BIT(dp->index);
	}

	fow (i = 0; i < 8; i++)
		mask[i] = ivec;

	/* Enabwe the cowwect subset of masks fow aww WAG powts that
	 * awe in the Tx set.
	 */
	dsa_wags_foweach_id(id, ds->dst) {
		wag = dsa_wag_by_id(ds->dst, id);
		if (!wag)
			continue;

		num_tx = 0;
		dsa_wag_foweach_powt(dp, ds->dst, wag) {
			if (dp->wag_tx_enabwed)
				num_tx++;
		}

		if (!num_tx)
			continue;

		nth = 0;
		dsa_wag_foweach_powt(dp, ds->dst, wag) {
			if (!dp->wag_tx_enabwed)
				continue;

			if (dp->ds == ds)
				mv88e6xxx_wag_set_powt_mask(mask, dp->index,
							    num_tx, nth);

			nth++;
		}
	}

	fow (i = 0; i < 8; i++) {
		eww = mv88e6xxx_g2_twunk_mask_wwite(chip, i, twue, mask[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mv88e6xxx_wag_sync_masks_map(stwuct dsa_switch *ds,
					stwuct dsa_wag wag)
{
	int eww;

	eww = mv88e6xxx_wag_sync_masks(ds);

	if (!eww)
		eww = mv88e6xxx_wag_sync_map(ds, wag);

	wetuwn eww;
}

static int mv88e6xxx_powt_wag_change(stwuct dsa_switch *ds, int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_wag_sync_masks(ds);
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww;
}

static int mv88e6xxx_powt_wag_join(stwuct dsa_switch *ds, int powt,
				   stwuct dsa_wag wag,
				   stwuct netdev_wag_uppew_info *info,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww, id;

	if (!mv88e6xxx_wag_can_offwoad(ds, wag, info, extack))
		wetuwn -EOPNOTSUPP;

	/* DSA WAG IDs awe one-based */
	id = wag.id - 1;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_powt_set_twunk(chip, powt, twue, id);
	if (eww)
		goto eww_unwock;

	eww = mv88e6xxx_wag_sync_masks_map(ds, wag);
	if (eww)
		goto eww_cweaw_twunk;

	mv88e6xxx_weg_unwock(chip);
	wetuwn 0;

eww_cweaw_twunk:
	mv88e6xxx_powt_set_twunk(chip, powt, fawse, 0);
eww_unwock:
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww;
}

static int mv88e6xxx_powt_wag_weave(stwuct dsa_switch *ds, int powt,
				    stwuct dsa_wag wag)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww_sync, eww_twunk;

	mv88e6xxx_weg_wock(chip);
	eww_sync = mv88e6xxx_wag_sync_masks_map(ds, wag);
	eww_twunk = mv88e6xxx_powt_set_twunk(chip, powt, fawse, 0);
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww_sync ? : eww_twunk;
}

static int mv88e6xxx_cwosschip_wag_change(stwuct dsa_switch *ds, int sw_index,
					  int powt)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_wag_sync_masks(ds);
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww;
}

static int mv88e6xxx_cwosschip_wag_join(stwuct dsa_switch *ds, int sw_index,
					int powt, stwuct dsa_wag wag,
					stwuct netdev_wag_uppew_info *info,
					stwuct netwink_ext_ack *extack)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww;

	if (!mv88e6xxx_wag_can_offwoad(ds, wag, info, extack))
		wetuwn -EOPNOTSUPP;

	mv88e6xxx_weg_wock(chip);

	eww = mv88e6xxx_wag_sync_masks_map(ds, wag);
	if (eww)
		goto unwock;

	eww = mv88e6xxx_pvt_map(chip, sw_index, powt);

unwock:
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww;
}

static int mv88e6xxx_cwosschip_wag_weave(stwuct dsa_switch *ds, int sw_index,
					 int powt, stwuct dsa_wag wag)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	int eww_sync, eww_pvt;

	mv88e6xxx_weg_wock(chip);
	eww_sync = mv88e6xxx_wag_sync_masks_map(ds, wag);
	eww_pvt = mv88e6xxx_pvt_map(chip, sw_index, powt);
	mv88e6xxx_weg_unwock(chip);
	wetuwn eww_sync ? : eww_pvt;
}

static const stwuct dsa_switch_ops mv88e6xxx_switch_ops = {
	.get_tag_pwotocow	= mv88e6xxx_get_tag_pwotocow,
	.change_tag_pwotocow	= mv88e6xxx_change_tag_pwotocow,
	.setup			= mv88e6xxx_setup,
	.teawdown		= mv88e6xxx_teawdown,
	.powt_setup		= mv88e6xxx_powt_setup,
	.powt_teawdown		= mv88e6xxx_powt_teawdown,
	.phywink_get_caps	= mv88e6xxx_get_caps,
	.phywink_mac_sewect_pcs	= mv88e6xxx_mac_sewect_pcs,
	.phywink_mac_pwepawe	= mv88e6xxx_mac_pwepawe,
	.phywink_mac_config	= mv88e6xxx_mac_config,
	.phywink_mac_finish	= mv88e6xxx_mac_finish,
	.phywink_mac_wink_down	= mv88e6xxx_mac_wink_down,
	.phywink_mac_wink_up	= mv88e6xxx_mac_wink_up,
	.get_stwings		= mv88e6xxx_get_stwings,
	.get_ethtoow_stats	= mv88e6xxx_get_ethtoow_stats,
	.get_eth_mac_stats	= mv88e6xxx_get_eth_mac_stats,
	.get_wmon_stats		= mv88e6xxx_get_wmon_stats,
	.get_sset_count		= mv88e6xxx_get_sset_count,
	.powt_max_mtu		= mv88e6xxx_get_max_mtu,
	.powt_change_mtu	= mv88e6xxx_change_mtu,
	.get_mac_eee		= mv88e6xxx_get_mac_eee,
	.set_mac_eee		= mv88e6xxx_set_mac_eee,
	.get_eepwom_wen		= mv88e6xxx_get_eepwom_wen,
	.get_eepwom		= mv88e6xxx_get_eepwom,
	.set_eepwom		= mv88e6xxx_set_eepwom,
	.get_wegs_wen		= mv88e6xxx_get_wegs_wen,
	.get_wegs		= mv88e6xxx_get_wegs,
	.get_wxnfc		= mv88e6xxx_get_wxnfc,
	.set_wxnfc		= mv88e6xxx_set_wxnfc,
	.set_ageing_time	= mv88e6xxx_set_ageing_time,
	.powt_bwidge_join	= mv88e6xxx_powt_bwidge_join,
	.powt_bwidge_weave	= mv88e6xxx_powt_bwidge_weave,
	.powt_pwe_bwidge_fwags	= mv88e6xxx_powt_pwe_bwidge_fwags,
	.powt_bwidge_fwags	= mv88e6xxx_powt_bwidge_fwags,
	.powt_stp_state_set	= mv88e6xxx_powt_stp_state_set,
	.powt_mst_state_set	= mv88e6xxx_powt_mst_state_set,
	.powt_fast_age		= mv88e6xxx_powt_fast_age,
	.powt_vwan_fast_age	= mv88e6xxx_powt_vwan_fast_age,
	.powt_vwan_fiwtewing	= mv88e6xxx_powt_vwan_fiwtewing,
	.powt_vwan_add		= mv88e6xxx_powt_vwan_add,
	.powt_vwan_dew		= mv88e6xxx_powt_vwan_dew,
	.vwan_msti_set		= mv88e6xxx_vwan_msti_set,
	.powt_fdb_add		= mv88e6xxx_powt_fdb_add,
	.powt_fdb_dew		= mv88e6xxx_powt_fdb_dew,
	.powt_fdb_dump		= mv88e6xxx_powt_fdb_dump,
	.powt_mdb_add		= mv88e6xxx_powt_mdb_add,
	.powt_mdb_dew		= mv88e6xxx_powt_mdb_dew,
	.powt_miwwow_add	= mv88e6xxx_powt_miwwow_add,
	.powt_miwwow_dew	= mv88e6xxx_powt_miwwow_dew,
	.cwosschip_bwidge_join	= mv88e6xxx_cwosschip_bwidge_join,
	.cwosschip_bwidge_weave	= mv88e6xxx_cwosschip_bwidge_weave,
	.powt_hwtstamp_set	= mv88e6xxx_powt_hwtstamp_set,
	.powt_hwtstamp_get	= mv88e6xxx_powt_hwtstamp_get,
	.powt_txtstamp		= mv88e6xxx_powt_txtstamp,
	.powt_wxtstamp		= mv88e6xxx_powt_wxtstamp,
	.get_ts_info		= mv88e6xxx_get_ts_info,
	.devwink_pawam_get	= mv88e6xxx_devwink_pawam_get,
	.devwink_pawam_set	= mv88e6xxx_devwink_pawam_set,
	.devwink_info_get	= mv88e6xxx_devwink_info_get,
	.powt_wag_change	= mv88e6xxx_powt_wag_change,
	.powt_wag_join		= mv88e6xxx_powt_wag_join,
	.powt_wag_weave		= mv88e6xxx_powt_wag_weave,
	.cwosschip_wag_change	= mv88e6xxx_cwosschip_wag_change,
	.cwosschip_wag_join	= mv88e6xxx_cwosschip_wag_join,
	.cwosschip_wag_weave	= mv88e6xxx_cwosschip_wag_weave,
};

static int mv88e6xxx_wegistew_switch(stwuct mv88e6xxx_chip *chip)
{
	stwuct device *dev = chip->dev;
	stwuct dsa_switch *ds;

	ds = devm_kzawwoc(dev, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn -ENOMEM;

	ds->dev = dev;
	ds->num_powts = mv88e6xxx_num_powts(chip);
	ds->pwiv = chip;
	ds->dev = dev;
	ds->ops = &mv88e6xxx_switch_ops;
	ds->ageing_time_min = chip->info->age_time_coeff;
	ds->ageing_time_max = chip->info->age_time_coeff * U8_MAX;

	/* Some chips suppowt up to 32, but that wequiwes enabwing the
	 * 5-bit powt mode, which we do not suppowt. 640k^W16 ought to
	 * be enough fow anyone.
	 */
	ds->num_wag_ids = mv88e6xxx_has_wag(chip) ? 16 : 0;

	dev_set_dwvdata(dev, ds);

	wetuwn dsa_wegistew_switch(ds);
}

static void mv88e6xxx_unwegistew_switch(stwuct mv88e6xxx_chip *chip)
{
	dsa_unwegistew_switch(chip->ds);
}

static const void *pdata_device_get_match_data(stwuct device *dev)
{
	const stwuct of_device_id *matches = dev->dwivew->of_match_tabwe;
	const stwuct dsa_mv88e6xxx_pdata *pdata = dev->pwatfowm_data;

	fow (; matches->name[0] || matches->type[0] || matches->compatibwe[0];
	     matches++) {
		if (!stwcmp(pdata->compatibwe, matches->compatibwe))
			wetuwn matches->data;
	}
	wetuwn NUWW;
}

/* Thewe is no suspend to WAM suppowt at DSA wevew yet, the switch configuwation
 * wouwd be wost aftew a powew cycwe so pwevent it to be suspended.
 */
static int __maybe_unused mv88e6xxx_suspend(stwuct device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static int __maybe_unused mv88e6xxx_wesume(stwuct device *dev)
{
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(mv88e6xxx_pm_ops, mv88e6xxx_suspend, mv88e6xxx_wesume);

static int mv88e6xxx_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct dsa_mv88e6xxx_pdata *pdata = mdiodev->dev.pwatfowm_data;
	const stwuct mv88e6xxx_info *compat_info = NUWW;
	stwuct device *dev = &mdiodev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct mv88e6xxx_chip *chip;
	int powt;
	int eww;

	if (!np && !pdata)
		wetuwn -EINVAW;

	if (np)
		compat_info = of_device_get_match_data(dev);

	if (pdata) {
		compat_info = pdata_device_get_match_data(dev);

		if (!pdata->netdev)
			wetuwn -EINVAW;

		fow (powt = 0; powt < DSA_MAX_POWTS; powt++) {
			if (!(pdata->enabwed_powts & (1 << powt)))
				continue;
			if (stwcmp(pdata->cd.powt_names[powt], "cpu"))
				continue;
			pdata->cd.netdev[powt] = &pdata->netdev->dev;
			bweak;
		}
	}

	if (!compat_info)
		wetuwn -EINVAW;

	chip = mv88e6xxx_awwoc_chip(dev);
	if (!chip) {
		eww = -ENOMEM;
		goto out;
	}

	chip->info = compat_info;

	chip->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(chip->weset)) {
		eww = PTW_EWW(chip->weset);
		goto out;
	}
	if (chip->weset)
		usweep_wange(10000, 20000);

	/* Detect if the device is configuwed in singwe chip addwessing mode,
	 * othewwise continue with addwess specific smi init/detection.
	 */
	eww = mv88e6xxx_singwe_chip_detect(chip, mdiodev);
	if (eww) {
		eww = mv88e6xxx_smi_init(chip, mdiodev->bus, mdiodev->addw);
		if (eww)
			goto out;

		eww = mv88e6xxx_detect(chip);
		if (eww)
			goto out;
	}

	if (chip->info->edsa_suppowt == MV88E6XXX_EDSA_SUPPOWTED)
		chip->tag_pwotocow = DSA_TAG_PWOTO_EDSA;
	ewse
		chip->tag_pwotocow = DSA_TAG_PWOTO_DSA;

	mv88e6xxx_phy_init(chip);

	if (chip->info->ops->get_eepwom) {
		if (np)
			of_pwopewty_wead_u32(np, "eepwom-wength",
					     &chip->eepwom_wen);
		ewse
			chip->eepwom_wen = pdata->eepwom_wen;
	}

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_switch_weset(chip);
	mv88e6xxx_weg_unwock(chip);
	if (eww)
		goto out;

	if (np) {
		chip->iwq = of_iwq_get(np, 0);
		if (chip->iwq == -EPWOBE_DEFEW) {
			eww = chip->iwq;
			goto out;
		}
	}

	if (pdata)
		chip->iwq = pdata->iwq;

	/* Has to be pewfowmed befowe the MDIO bus is cweated, because
	 * the PHYs wiww wink theiw intewwupts to these intewwupt
	 * contwowwews
	 */
	mv88e6xxx_weg_wock(chip);
	if (chip->iwq > 0)
		eww = mv88e6xxx_g1_iwq_setup(chip);
	ewse
		eww = mv88e6xxx_iwq_poww_setup(chip);
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		goto out;

	if (chip->info->g2_iwqs > 0) {
		eww = mv88e6xxx_g2_iwq_setup(chip);
		if (eww)
			goto out_g1_iwq;
	}

	eww = mv88e6xxx_g1_atu_pwob_iwq_setup(chip);
	if (eww)
		goto out_g2_iwq;

	eww = mv88e6xxx_g1_vtu_pwob_iwq_setup(chip);
	if (eww)
		goto out_g1_atu_pwob_iwq;

	eww = mv88e6xxx_wegistew_switch(chip);
	if (eww)
		goto out_g1_vtu_pwob_iwq;

	wetuwn 0;

out_g1_vtu_pwob_iwq:
	mv88e6xxx_g1_vtu_pwob_iwq_fwee(chip);
out_g1_atu_pwob_iwq:
	mv88e6xxx_g1_atu_pwob_iwq_fwee(chip);
out_g2_iwq:
	if (chip->info->g2_iwqs > 0)
		mv88e6xxx_g2_iwq_fwee(chip);
out_g1_iwq:
	if (chip->iwq > 0)
		mv88e6xxx_g1_iwq_fwee(chip);
	ewse
		mv88e6xxx_iwq_poww_fwee(chip);
out:
	if (pdata)
		dev_put(pdata->netdev);

	wetuwn eww;
}

static void mv88e6xxx_wemove(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);
	stwuct mv88e6xxx_chip *chip;

	if (!ds)
		wetuwn;

	chip = ds->pwiv;

	if (chip->info->ptp_suppowt) {
		mv88e6xxx_hwtstamp_fwee(chip);
		mv88e6xxx_ptp_fwee(chip);
	}

	mv88e6xxx_phy_destwoy(chip);
	mv88e6xxx_unwegistew_switch(chip);

	mv88e6xxx_g1_vtu_pwob_iwq_fwee(chip);
	mv88e6xxx_g1_atu_pwob_iwq_fwee(chip);

	if (chip->info->g2_iwqs > 0)
		mv88e6xxx_g2_iwq_fwee(chip);

	if (chip->iwq > 0)
		mv88e6xxx_g1_iwq_fwee(chip);
	ewse
		mv88e6xxx_iwq_poww_fwee(chip);
}

static void mv88e6xxx_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);

	if (!ds)
		wetuwn;

	dsa_switch_shutdown(ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id mv88e6xxx_of_match[] = {
	{
		.compatibwe = "mawveww,mv88e6085",
		.data = &mv88e6xxx_tabwe[MV88E6085],
	},
	{
		.compatibwe = "mawveww,mv88e6190",
		.data = &mv88e6xxx_tabwe[MV88E6190],
	},
	{
		.compatibwe = "mawveww,mv88e6250",
		.data = &mv88e6xxx_tabwe[MV88E6250],
	},
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, mv88e6xxx_of_match);

static stwuct mdio_dwivew mv88e6xxx_dwivew = {
	.pwobe	= mv88e6xxx_pwobe,
	.wemove = mv88e6xxx_wemove,
	.shutdown = mv88e6xxx_shutdown,
	.mdiodwv.dwivew = {
		.name = "mv88e6085",
		.of_match_tabwe = mv88e6xxx_of_match,
		.pm = &mv88e6xxx_pm_ops,
	},
};

mdio_moduwe_dwivew(mv88e6xxx_dwivew);

MODUWE_AUTHOW("Wennewt Buytenhek <buytenh@wantstofwy.owg>");
MODUWE_DESCWIPTION("Dwivew fow Mawveww 88E6XXX ethewnet switch chips");
MODUWE_WICENSE("GPW");
