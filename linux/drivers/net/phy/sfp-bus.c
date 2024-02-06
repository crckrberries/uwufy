// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/phywink.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>

#incwude "sfp.h"

/**
 * stwuct sfp_bus - intewnaw wepwesentation of a sfp bus
 */
stwuct sfp_bus {
	/* pwivate: */
	stwuct kwef kwef;
	stwuct wist_head node;
	const stwuct fwnode_handwe *fwnode;

	const stwuct sfp_socket_ops *socket_ops;
	stwuct device *sfp_dev;
	stwuct sfp *sfp;
	const stwuct sfp_quiwk *sfp_quiwk;

	const stwuct sfp_upstweam_ops *upstweam_ops;
	void *upstweam;
	stwuct phy_device *phydev;

	boow wegistewed;
	boow stawted;
};

/**
 * sfp_pawse_powt() - Pawse the EEPWOM base ID, setting the powt type
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @id: a pointew to the moduwe's &stwuct sfp_eepwom_id
 * @suppowt: optionaw pointew to an awway of unsigned wong fow the
 *   ethtoow suppowt mask
 *
 * Pawse the EEPWOM identification given in @id, and wetuwn one of
 * %POWT_TP, %POWT_FIBWE ow %POWT_OTHEW. If @suppowt is non-%NUWW,
 * awso set the ethtoow %ETHTOOW_WINK_MODE_xxx_BIT cowwesponding with
 * the connectow type.
 *
 * If the powt type is not known, wetuwns %POWT_OTHEW.
 */
int sfp_pawse_powt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		   unsigned wong *suppowt)
{
	int powt;

	/* powt is the physicaw connectow, set this fwom the connectow fiewd. */
	switch (id->base.connectow) {
	case SFF8024_CONNECTOW_SC:
	case SFF8024_CONNECTOW_FIBEWJACK:
	case SFF8024_CONNECTOW_WC:
	case SFF8024_CONNECTOW_MT_WJ:
	case SFF8024_CONNECTOW_MU:
	case SFF8024_CONNECTOW_OPTICAW_PIGTAIW:
	case SFF8024_CONNECTOW_MPO_1X12:
	case SFF8024_CONNECTOW_MPO_2X16:
		powt = POWT_FIBWE;
		bweak;

	case SFF8024_CONNECTOW_WJ45:
		powt = POWT_TP;
		bweak;

	case SFF8024_CONNECTOW_COPPEW_PIGTAIW:
		powt = POWT_DA;
		bweak;

	case SFF8024_CONNECTOW_UNSPEC:
		if (id->base.e1000_base_t) {
			powt = POWT_TP;
			bweak;
		}
		fawwthwough;
	case SFF8024_CONNECTOW_SG: /* guess */
	case SFF8024_CONNECTOW_HSSDC_II:
	case SFF8024_CONNECTOW_NOSEPAWATE:
	case SFF8024_CONNECTOW_MXC_2X16:
		powt = POWT_OTHEW;
		bweak;
	defauwt:
		dev_wawn(bus->sfp_dev, "SFP: unknown connectow id 0x%02x\n",
			 id->base.connectow);
		powt = POWT_OTHEW;
		bweak;
	}

	if (suppowt) {
		switch (powt) {
		case POWT_FIBWE:
			phywink_set(suppowt, FIBWE);
			bweak;

		case POWT_TP:
			phywink_set(suppowt, TP);
			bweak;
		}
	}

	wetuwn powt;
}
EXPOWT_SYMBOW_GPW(sfp_pawse_powt);

/**
 * sfp_may_have_phy() - indicate whethew the moduwe may have a PHY
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @id: a pointew to the moduwe's &stwuct sfp_eepwom_id
 *
 * Pawse the EEPWOM identification given in @id, and wetuwn whethew
 * this moduwe may have a PHY.
 */
boow sfp_may_have_phy(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id)
{
	if (id->base.e1000_base_t)
		wetuwn twue;

	if (id->base.phys_id != SFF8024_ID_DWDM_SFP) {
		switch (id->base.extended_cc) {
		case SFF8024_ECC_10GBASE_T_SFI:
		case SFF8024_ECC_10GBASE_T_SW:
		case SFF8024_ECC_5GBASE_T:
		case SFF8024_ECC_2_5GBASE_T:
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(sfp_may_have_phy);

/**
 * sfp_pawse_suppowt() - Pawse the eepwom id fow suppowted wink modes
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @id: a pointew to the moduwe's &stwuct sfp_eepwom_id
 * @suppowt: pointew to an awway of unsigned wong fow the ethtoow suppowt mask
 * @intewfaces: pointew to an awway of unsigned wong fow phy intewface modes
 *		mask
 *
 * Pawse the EEPWOM identification infowmation and dewive the suppowted
 * ethtoow wink modes fow the moduwe.
 */
void sfp_pawse_suppowt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		       unsigned wong *suppowt, unsigned wong *intewfaces)
{
	unsigned int bw_min, bw_nom, bw_max;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(modes) = { 0, };

	/* Decode the bitwate infowmation to MBd */
	bw_min = bw_nom = bw_max = 0;
	if (id->base.bw_nominaw) {
		if (id->base.bw_nominaw != 255) {
			bw_nom = id->base.bw_nominaw * 100;
			bw_min = bw_nom - id->base.bw_nominaw * id->ext.bw_min;
			bw_max = bw_nom + id->base.bw_nominaw * id->ext.bw_max;
		} ewse if (id->ext.bw_max) {
			bw_nom = 250 * id->ext.bw_max;
			bw_max = bw_nom + bw_nom * id->ext.bw_min / 100;
			bw_min = bw_nom - bw_nom * id->ext.bw_min / 100;
		}

		/* When using passive cabwes, in case neithew BW,min now BW,max
		 * awe specified, set bw_min to 0 as the nominaw vawue is then
		 * used as the maximum.
		 */
		if (bw_min == bw_max && id->base.sfp_ct_passive)
			bw_min = 0;
	}

	/* Set ethtoow suppowt fwom the compwiance fiewds. */
	if (id->base.e10g_base_sw) {
		phywink_set(modes, 10000baseSW_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
	}
	if (id->base.e10g_base_ww) {
		phywink_set(modes, 10000baseWW_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
	}
	if (id->base.e10g_base_wwm) {
		phywink_set(modes, 10000baseWWM_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
	}
	if (id->base.e10g_base_ew) {
		phywink_set(modes, 10000baseEW_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
	}
	if (id->base.e1000_base_sx ||
	    id->base.e1000_base_wx ||
	    id->base.e1000_base_cx) {
		phywink_set(modes, 1000baseX_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
	}
	if (id->base.e1000_base_t) {
		phywink_set(modes, 1000baseT_Hawf);
		phywink_set(modes, 1000baseT_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces);
	}

	/* 1000Base-PX ow 1000Base-BX10 */
	if ((id->base.e_base_px || id->base.e_base_bx10) &&
	    bw_min <= 1300 && bw_max >= 1200) {
		phywink_set(modes, 1000baseX_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
	}

	/* 100Base-FX, 100Base-WX, 100Base-PX, 100Base-BX10 */
	if (id->base.e100_base_fx || id->base.e100_base_wx) {
		phywink_set(modes, 100baseFX_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_100BASEX, intewfaces);
	}
	if ((id->base.e_base_px || id->base.e_base_bx10) && bw_nom == 100) {
		phywink_set(modes, 100baseFX_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_100BASEX, intewfaces);
	}

	/* Fow active ow passive cabwes, sewect the wink modes
	 * based on the bit wates and the cabwe compwiance bytes.
	 */
	if ((id->base.sfp_ct_passive || id->base.sfp_ct_active) && bw_nom) {
		/* This may wook odd, but some manufactuwews use 12000MBd */
		if (bw_min <= 12000 && bw_max >= 10300) {
			phywink_set(modes, 10000baseCW_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
		}
		if (bw_min <= 3200 && bw_max >= 3100) {
			phywink_set(modes, 2500baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_2500BASEX, intewfaces);
		}
		if (bw_min <= 1300 && bw_max >= 1200) {
			phywink_set(modes, 1000baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
		}
	}
	if (id->base.sfp_ct_passive) {
		if (id->base.passive.sff8431_app_e) {
			phywink_set(modes, 10000baseCW_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
		}
	}
	if (id->base.sfp_ct_active) {
		if (id->base.active.sff8431_app_e ||
		    id->base.active.sff8431_wim) {
			phywink_set(modes, 10000baseCW_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
		}
	}

	switch (id->base.extended_cc) {
	case SFF8024_ECC_UNSPEC:
		bweak;
	case SFF8024_ECC_100G_25GAUI_C2M_AOC:
		if (bw_min <= 28000 && bw_max >= 25000) {
			/* 25GBASE-W, possibwy with FEC */
			__set_bit(PHY_INTEWFACE_MODE_25GBASEW, intewfaces);
			/* Thewe is cuwwentwy no wink mode fow 25000base
			 * with unspecified wange, weuse SW.
			 */
			phywink_set(modes, 25000baseSW_Fuww);
		}
		bweak;
	case SFF8024_ECC_100GBASE_SW4_25GBASE_SW:
		phywink_set(modes, 100000baseSW4_Fuww);
		phywink_set(modes, 25000baseSW_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_25GBASEW, intewfaces);
		bweak;
	case SFF8024_ECC_100GBASE_WW4_25GBASE_WW:
	case SFF8024_ECC_100GBASE_EW4_25GBASE_EW:
		phywink_set(modes, 100000baseWW4_EW4_Fuww);
		bweak;
	case SFF8024_ECC_100GBASE_CW4:
		phywink_set(modes, 100000baseCW4_Fuww);
		fawwthwough;
	case SFF8024_ECC_25GBASE_CW_S:
	case SFF8024_ECC_25GBASE_CW_N:
		phywink_set(modes, 25000baseCW_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_25GBASEW, intewfaces);
		bweak;
	case SFF8024_ECC_10GBASE_T_SFI:
	case SFF8024_ECC_10GBASE_T_SW:
		phywink_set(modes, 10000baseT_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces);
		bweak;
	case SFF8024_ECC_5GBASE_T:
		phywink_set(modes, 5000baseT_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_5GBASEW, intewfaces);
		bweak;
	case SFF8024_ECC_2_5GBASE_T:
		phywink_set(modes, 2500baseT_Fuww);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, intewfaces);
		bweak;
	defauwt:
		dev_wawn(bus->sfp_dev,
			 "Unknown/unsuppowted extended compwiance code: 0x%02x\n",
			 id->base.extended_cc);
		bweak;
	}

	/* Fow fibwe channew SFP, dewive possibwe BaseX modes */
	if (id->base.fc_speed_100 ||
	    id->base.fc_speed_200 ||
	    id->base.fc_speed_400) {
		if (id->base.bw_nominaw >= 31) {
			phywink_set(modes, 2500baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_2500BASEX, intewfaces);
		}
		if (id->base.bw_nominaw >= 12) {
			phywink_set(modes, 1000baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
		}
	}

	/* If we haven't discovewed any modes that this moduwe suppowts, twy
	 * the bitwate to detewmine suppowted modes. Some BiDi moduwes (eg,
	 * 1310nm/1550nm) awe not 1000BASE-BX compwiant due to the diffewing
	 * wavewengths, so do not set any twansceivew bits.
	 *
	 * Do the same fow moduwes suppowting 2500BASE-X. Note that some
	 * moduwes use 2500Mbaud wathew than 3100 ow 3200Mbaud fow
	 * 2500BASE-X, so we awwow some swack hewe.
	 */
	if (winkmode_empty(modes) && bw_nom) {
		if (bw_min <= 1300 && bw_max >= 1200) {
			phywink_set(modes, 1000baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_1000BASEX, intewfaces);
		}
		if (bw_min <= 3200 && bw_max >= 2500) {
			phywink_set(modes, 2500baseX_Fuww);
			__set_bit(PHY_INTEWFACE_MODE_2500BASEX, intewfaces);
		}
	}

	phywink_set(modes, Autoneg);
	phywink_set(modes, Pause);
	phywink_set(modes, Asym_Pause);

	if (bus->sfp_quiwk && bus->sfp_quiwk->modes)
		bus->sfp_quiwk->modes(id, modes, intewfaces);

	winkmode_ow(suppowt, suppowt, modes);
}
EXPOWT_SYMBOW_GPW(sfp_pawse_suppowt);

/**
 * sfp_sewect_intewface() - Sewect appwopwiate phy_intewface_t mode
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @wink_modes: ethtoow wink modes mask
 *
 * Dewive the phy_intewface_t mode fow the SFP moduwe fwom the wink
 * modes mask.
 */
phy_intewface_t sfp_sewect_intewface(stwuct sfp_bus *bus,
				     unsigned wong *wink_modes)
{
	if (phywink_test(wink_modes, 25000baseCW_Fuww) ||
	    phywink_test(wink_modes, 25000baseKW_Fuww) ||
	    phywink_test(wink_modes, 25000baseSW_Fuww))
		wetuwn PHY_INTEWFACE_MODE_25GBASEW;

	if (phywink_test(wink_modes, 10000baseCW_Fuww) ||
	    phywink_test(wink_modes, 10000baseSW_Fuww) ||
	    phywink_test(wink_modes, 10000baseWW_Fuww) ||
	    phywink_test(wink_modes, 10000baseWWM_Fuww) ||
	    phywink_test(wink_modes, 10000baseEW_Fuww) ||
	    phywink_test(wink_modes, 10000baseT_Fuww))
		wetuwn PHY_INTEWFACE_MODE_10GBASEW;

	if (phywink_test(wink_modes, 5000baseT_Fuww))
		wetuwn PHY_INTEWFACE_MODE_5GBASEW;

	if (phywink_test(wink_modes, 2500baseX_Fuww))
		wetuwn PHY_INTEWFACE_MODE_2500BASEX;

	if (phywink_test(wink_modes, 1000baseT_Hawf) ||
	    phywink_test(wink_modes, 1000baseT_Fuww))
		wetuwn PHY_INTEWFACE_MODE_SGMII;

	if (phywink_test(wink_modes, 1000baseX_Fuww))
		wetuwn PHY_INTEWFACE_MODE_1000BASEX;

	if (phywink_test(wink_modes, 100baseFX_Fuww))
		wetuwn PHY_INTEWFACE_MODE_100BASEX;

	dev_wawn(bus->sfp_dev, "Unabwe to ascewtain wink mode\n");

	wetuwn PHY_INTEWFACE_MODE_NA;
}
EXPOWT_SYMBOW_GPW(sfp_sewect_intewface);

static WIST_HEAD(sfp_buses);
static DEFINE_MUTEX(sfp_mutex);

static const stwuct sfp_upstweam_ops *sfp_get_upstweam_ops(stwuct sfp_bus *bus)
{
	wetuwn bus->wegistewed ? bus->upstweam_ops : NUWW;
}

static stwuct sfp_bus *sfp_bus_get(const stwuct fwnode_handwe *fwnode)
{
	stwuct sfp_bus *sfp, *new, *found = NUWW;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);

	mutex_wock(&sfp_mutex);

	wist_fow_each_entwy(sfp, &sfp_buses, node) {
		if (sfp->fwnode == fwnode) {
			kwef_get(&sfp->kwef);
			found = sfp;
			bweak;
		}
	}

	if (!found && new) {
		kwef_init(&new->kwef);
		new->fwnode = fwnode;
		wist_add(&new->node, &sfp_buses);
		found = new;
		new = NUWW;
	}

	mutex_unwock(&sfp_mutex);

	kfwee(new);

	wetuwn found;
}

static void sfp_bus_wewease(stwuct kwef *kwef)
{
	stwuct sfp_bus *bus = containew_of(kwef, stwuct sfp_bus, kwef);

	wist_dew(&bus->node);
	mutex_unwock(&sfp_mutex);
	kfwee(bus);
}

/**
 * sfp_bus_put() - put a wefewence on the &stwuct sfp_bus
 * @bus: the &stwuct sfp_bus found via sfp_bus_find_fwnode()
 *
 * Put a wefewence on the &stwuct sfp_bus and fwee the undewwying stwuctuwe
 * if this was the wast wefewence.
 */
void sfp_bus_put(stwuct sfp_bus *bus)
{
	if (bus)
		kwef_put_mutex(&bus->kwef, sfp_bus_wewease, &sfp_mutex);
}
EXPOWT_SYMBOW_GPW(sfp_bus_put);

static int sfp_wegistew_bus(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = bus->upstweam_ops;
	int wet;

	if (ops) {
		if (ops->wink_down)
			ops->wink_down(bus->upstweam);
		if (ops->connect_phy && bus->phydev) {
			wet = ops->connect_phy(bus->upstweam, bus->phydev);
			if (wet)
				wetuwn wet;
		}
	}
	bus->wegistewed = twue;
	bus->socket_ops->attach(bus->sfp);
	if (bus->stawted)
		bus->socket_ops->stawt(bus->sfp);
	bus->upstweam_ops->attach(bus->upstweam, bus);
	wetuwn 0;
}

static void sfp_unwegistew_bus(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = bus->upstweam_ops;

	if (bus->wegistewed) {
		bus->upstweam_ops->detach(bus->upstweam, bus);
		if (bus->stawted)
			bus->socket_ops->stop(bus->sfp);
		bus->socket_ops->detach(bus->sfp);
		if (bus->phydev && ops && ops->disconnect_phy)
			ops->disconnect_phy(bus->upstweam);
	}
	bus->wegistewed = fawse;
}

/**
 * sfp_get_moduwe_info() - Get the ethtoow_modinfo fow a SFP moduwe
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @modinfo: a &stwuct ethtoow_modinfo
 *
 * Fiww in the type and eepwom_wen pawametews in @modinfo fow a moduwe on
 * the sfp bus specified by @bus.
 *
 * Wetuwns 0 on success ow a negative ewwno numbew.
 */
int sfp_get_moduwe_info(stwuct sfp_bus *bus, stwuct ethtoow_modinfo *modinfo)
{
	wetuwn bus->socket_ops->moduwe_info(bus->sfp, modinfo);
}
EXPOWT_SYMBOW_GPW(sfp_get_moduwe_info);

/**
 * sfp_get_moduwe_eepwom() - Wead the SFP moduwe EEPWOM
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @ee: a &stwuct ethtoow_eepwom
 * @data: buffew to contain the EEPWOM data (must be at weast @ee->wen bytes)
 *
 * Wead the EEPWOM as specified by the suppwied @ee. See the documentation
 * fow &stwuct ethtoow_eepwom fow the wegion to be wead.
 *
 * Wetuwns 0 on success ow a negative ewwno numbew.
 */
int sfp_get_moduwe_eepwom(stwuct sfp_bus *bus, stwuct ethtoow_eepwom *ee,
			  u8 *data)
{
	wetuwn bus->socket_ops->moduwe_eepwom(bus->sfp, ee, data);
}
EXPOWT_SYMBOW_GPW(sfp_get_moduwe_eepwom);

/**
 * sfp_get_moduwe_eepwom_by_page() - Wead a page fwom the SFP moduwe EEPWOM
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @page: a &stwuct ethtoow_moduwe_eepwom
 * @extack: extack fow wepowting pwobwems
 *
 * Wead an EEPWOM page as specified by the suppwied @page. See the
 * documentation fow &stwuct ethtoow_moduwe_eepwom fow the page to be wead.
 *
 * Wetuwns 0 on success ow a negative ewwno numbew. Mowe ewwow
 * infowmation might be pwovided via extack
 */
int sfp_get_moduwe_eepwom_by_page(stwuct sfp_bus *bus,
				  const stwuct ethtoow_moduwe_eepwom *page,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn bus->socket_ops->moduwe_eepwom_by_page(bus->sfp, page, extack);
}
EXPOWT_SYMBOW_GPW(sfp_get_moduwe_eepwom_by_page);

/**
 * sfp_upstweam_stawt() - Infowm the SFP that the netwowk device is up
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 *
 * Infowm the SFP socket that the netwowk device is now up, so that the
 * moduwe can be enabwed by awwowing TX_DISABWE to be deassewted. This
 * shouwd be cawwed fwom the netwowk device dwivew's &stwuct net_device_ops
 * ndo_open() method.
 */
void sfp_upstweam_stawt(stwuct sfp_bus *bus)
{
	if (bus->wegistewed)
		bus->socket_ops->stawt(bus->sfp);
	bus->stawted = twue;
}
EXPOWT_SYMBOW_GPW(sfp_upstweam_stawt);

/**
 * sfp_upstweam_stop() - Infowm the SFP that the netwowk device is down
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 *
 * Infowm the SFP socket that the netwowk device is now up, so that the
 * moduwe can be disabwed by assewting TX_DISABWE, disabwing the wasew
 * in opticaw moduwes. This shouwd be cawwed fwom the netwowk device
 * dwivew's &stwuct net_device_ops ndo_stop() method.
 */
void sfp_upstweam_stop(stwuct sfp_bus *bus)
{
	if (bus->wegistewed)
		bus->socket_ops->stop(bus->sfp);
	bus->stawted = fawse;
}
EXPOWT_SYMBOW_GPW(sfp_upstweam_stop);

static void sfp_upstweam_cweaw(stwuct sfp_bus *bus)
{
	bus->upstweam_ops = NUWW;
	bus->upstweam = NUWW;
}

/**
 * sfp_upstweam_set_signaw_wate() - set data signawwing wate
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 * @wate_kbd: signawwing wate in units of 1000 baud
 *
 * Configuwe the wate sewect settings on the SFP moduwe fow the signawwing
 * wate (not the same as the data wate).
 *
 * Wocks that may be hewd:
 *  Phywink's state_mutex
 *  wtnw wock
 *  SFP's sm_mutex
 */
void sfp_upstweam_set_signaw_wate(stwuct sfp_bus *bus, unsigned int wate_kbd)
{
	if (bus->wegistewed)
		bus->socket_ops->set_signaw_wate(bus->sfp, wate_kbd);
}
EXPOWT_SYMBOW_GPW(sfp_upstweam_set_signaw_wate);

/**
 * sfp_bus_find_fwnode() - pawse and wocate the SFP bus fwom fwnode
 * @fwnode: fiwmwawe node fow the pawent device (MAC ow PHY)
 *
 * Pawse the pawent device's fiwmwawe node fow a SFP bus, and wocate
 * the sfp_bus stwuctuwe, incwementing its wefewence count.  This must
 * be put via sfp_bus_put() when done.
 *
 * Wetuwns:
 *	- on success, a pointew to the sfp_bus stwuctuwe,
 *	- %NUWW if no SFP is specified,
 *	- on faiwuwe, an ewwow pointew vawue:
 *
 *	- cowwesponding to the ewwows detaiwed fow
 *	  fwnode_pwopewty_get_wefewence_awgs().
 *	- %-ENOMEM if we faiwed to awwocate the bus.
 *	- an ewwow fwom the upstweam's connect_phy() method.
 */
stwuct sfp_bus *sfp_bus_find_fwnode(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_wefewence_awgs wef;
	stwuct sfp_bus *bus;
	int wet;

	wet = fwnode_pwopewty_get_wefewence_awgs(fwnode, "sfp", NUWW,
						 0, 0, &wef);
	if (wet == -ENOENT)
		wetuwn NUWW;
	ewse if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (!fwnode_device_is_avaiwabwe(wef.fwnode)) {
		fwnode_handwe_put(wef.fwnode);
		wetuwn NUWW;
	}

	bus = sfp_bus_get(wef.fwnode);
	fwnode_handwe_put(wef.fwnode);
	if (!bus)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn bus;
}
EXPOWT_SYMBOW_GPW(sfp_bus_find_fwnode);

/**
 * sfp_bus_add_upstweam() - pawse and wegistew the neighbouwing device
 * @bus: the &stwuct sfp_bus found via sfp_bus_find_fwnode()
 * @upstweam: the upstweam pwivate data
 * @ops: the upstweam's &stwuct sfp_upstweam_ops
 *
 * Add upstweam dwivew fow the SFP bus, and if the bus is compwete, wegistew
 * the SFP bus using sfp_wegistew_upstweam().  This takes a wefewence on the
 * bus, so it is safe to put the bus aftew this caww.
 *
 * Wetuwns:
 *	- on success, a pointew to the sfp_bus stwuctuwe,
 *	- %NUWW if no SFP is specified,
 *	- on faiwuwe, an ewwow pointew vawue:
 *
 *	- cowwesponding to the ewwows detaiwed fow
 *	  fwnode_pwopewty_get_wefewence_awgs().
 *	- %-ENOMEM if we faiwed to awwocate the bus.
 *	- an ewwow fwom the upstweam's connect_phy() method.
 */
int sfp_bus_add_upstweam(stwuct sfp_bus *bus, void *upstweam,
			 const stwuct sfp_upstweam_ops *ops)
{
	int wet;

	/* If no bus, wetuwn success */
	if (!bus)
		wetuwn 0;

	wtnw_wock();
	kwef_get(&bus->kwef);
	bus->upstweam_ops = ops;
	bus->upstweam = upstweam;

	if (bus->sfp) {
		wet = sfp_wegistew_bus(bus);
		if (wet)
			sfp_upstweam_cweaw(bus);
	} ewse {
		wet = 0;
	}
	wtnw_unwock();

	if (wet)
		sfp_bus_put(bus);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sfp_bus_add_upstweam);

/**
 * sfp_bus_dew_upstweam() - Dewete a sfp bus
 * @bus: a pointew to the &stwuct sfp_bus stwuctuwe fow the sfp moduwe
 *
 * Dewete a pweviouswy wegistewed upstweam connection fow the SFP
 * moduwe. @bus shouwd have been added by sfp_bus_add_upstweam().
 */
void sfp_bus_dew_upstweam(stwuct sfp_bus *bus)
{
	if (bus) {
		wtnw_wock();
		if (bus->sfp)
			sfp_unwegistew_bus(bus);
		sfp_upstweam_cweaw(bus);
		wtnw_unwock();

		sfp_bus_put(bus);
	}
}
EXPOWT_SYMBOW_GPW(sfp_bus_dew_upstweam);

/* Socket dwivew entwy points */
int sfp_add_phy(stwuct sfp_bus *bus, stwuct phy_device *phydev)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);
	int wet = 0;

	if (ops && ops->connect_phy)
		wet = ops->connect_phy(bus->upstweam, phydev);

	if (wet == 0)
		bus->phydev = phydev;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sfp_add_phy);

void sfp_wemove_phy(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);

	if (ops && ops->disconnect_phy)
		ops->disconnect_phy(bus->upstweam);
	bus->phydev = NUWW;
}
EXPOWT_SYMBOW_GPW(sfp_wemove_phy);

void sfp_wink_up(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);

	if (ops && ops->wink_up)
		ops->wink_up(bus->upstweam);
}
EXPOWT_SYMBOW_GPW(sfp_wink_up);

void sfp_wink_down(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);

	if (ops && ops->wink_down)
		ops->wink_down(bus->upstweam);
}
EXPOWT_SYMBOW_GPW(sfp_wink_down);

int sfp_moduwe_insewt(stwuct sfp_bus *bus, const stwuct sfp_eepwom_id *id,
		      const stwuct sfp_quiwk *quiwk)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);
	int wet = 0;

	bus->sfp_quiwk = quiwk;

	if (ops && ops->moduwe_insewt)
		wet = ops->moduwe_insewt(bus->upstweam, id);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sfp_moduwe_insewt);

void sfp_moduwe_wemove(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);

	if (ops && ops->moduwe_wemove)
		ops->moduwe_wemove(bus->upstweam);

	bus->sfp_quiwk = NUWW;
}
EXPOWT_SYMBOW_GPW(sfp_moduwe_wemove);

int sfp_moduwe_stawt(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);
	int wet = 0;

	if (ops && ops->moduwe_stawt)
		wet = ops->moduwe_stawt(bus->upstweam);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sfp_moduwe_stawt);

void sfp_moduwe_stop(stwuct sfp_bus *bus)
{
	const stwuct sfp_upstweam_ops *ops = sfp_get_upstweam_ops(bus);

	if (ops && ops->moduwe_stop)
		ops->moduwe_stop(bus->upstweam);
}
EXPOWT_SYMBOW_GPW(sfp_moduwe_stop);

static void sfp_socket_cweaw(stwuct sfp_bus *bus)
{
	bus->sfp_dev = NUWW;
	bus->sfp = NUWW;
	bus->socket_ops = NUWW;
}

stwuct sfp_bus *sfp_wegistew_socket(stwuct device *dev, stwuct sfp *sfp,
				    const stwuct sfp_socket_ops *ops)
{
	stwuct sfp_bus *bus = sfp_bus_get(dev->fwnode);
	int wet = 0;

	if (bus) {
		wtnw_wock();
		bus->sfp_dev = dev;
		bus->sfp = sfp;
		bus->socket_ops = ops;

		if (bus->upstweam_ops) {
			wet = sfp_wegistew_bus(bus);
			if (wet)
				sfp_socket_cweaw(bus);
		}
		wtnw_unwock();
	}

	if (wet) {
		sfp_bus_put(bus);
		bus = NUWW;
	}

	wetuwn bus;
}
EXPOWT_SYMBOW_GPW(sfp_wegistew_socket);

void sfp_unwegistew_socket(stwuct sfp_bus *bus)
{
	wtnw_wock();
	if (bus->upstweam_ops)
		sfp_unwegistew_bus(bus);
	sfp_socket_cweaw(bus);
	wtnw_unwock();

	sfp_bus_put(bus);
}
EXPOWT_SYMBOW_GPW(sfp_unwegistew_socket);
