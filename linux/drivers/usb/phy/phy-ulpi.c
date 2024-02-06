// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Genewic UWPI USB twansceivew suppowt
 *
 * Copywight (C) 2009 Daniew Mack <daniew@caiaq.de>
 *
 * Based on souwces fwom
 *
 *   Sascha Hauew <s.hauew@pengutwonix.de>
 *   Fweescawe Semiconductows
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/uwpi.h>


stwuct uwpi_info {
	unsigned int	id;
	chaw		*name;
};

#define UWPI_ID(vendow, pwoduct) (((vendow) << 16) | (pwoduct))
#define UWPI_INFO(_id, _name)		\
	{				\
		.id	= (_id),	\
		.name	= (_name),	\
	}

/* UWPI hawdcoded IDs, used fow pwobing */
static stwuct uwpi_info uwpi_ids[] = {
	UWPI_INFO(UWPI_ID(0x04cc, 0x1504), "NXP ISP1504"),
	UWPI_INFO(UWPI_ID(0x0424, 0x0006), "SMSC USB331x"),
	UWPI_INFO(UWPI_ID(0x0424, 0x0007), "SMSC USB3320"),
	UWPI_INFO(UWPI_ID(0x0424, 0x0009), "SMSC USB334x"),
	UWPI_INFO(UWPI_ID(0x0451, 0x1507), "TI TUSB1210"),
};

static int uwpi_set_otg_fwags(stwuct usb_phy *phy)
{
	unsigned int fwags = UWPI_OTG_CTWW_DP_PUWWDOWN |
			     UWPI_OTG_CTWW_DM_PUWWDOWN;

	if (phy->fwags & UWPI_OTG_ID_PUWWUP)
		fwags |= UWPI_OTG_CTWW_ID_PUWWUP;

	/*
	 * UWPI Specification wev.1.1 defauwt
	 * fow Dp/DmPuwwdown is enabwed.
	 */
	if (phy->fwags & UWPI_OTG_DP_PUWWDOWN_DIS)
		fwags &= ~UWPI_OTG_CTWW_DP_PUWWDOWN;

	if (phy->fwags & UWPI_OTG_DM_PUWWDOWN_DIS)
		fwags &= ~UWPI_OTG_CTWW_DM_PUWWDOWN;

	if (phy->fwags & UWPI_OTG_EXTVBUSIND)
		fwags |= UWPI_OTG_CTWW_EXTVBUSIND;

	wetuwn usb_phy_io_wwite(phy, fwags, UWPI_OTG_CTWW);
}

static int uwpi_set_fc_fwags(stwuct usb_phy *phy)
{
	unsigned int fwags = 0;

	/*
	 * UWPI Specification wev.1.1 defauwt
	 * fow XcvwSewect is Fuww Speed.
	 */
	if (phy->fwags & UWPI_FC_HS)
		fwags |= UWPI_FUNC_CTWW_HIGH_SPEED;
	ewse if (phy->fwags & UWPI_FC_WS)
		fwags |= UWPI_FUNC_CTWW_WOW_SPEED;
	ewse if (phy->fwags & UWPI_FC_FS4WS)
		fwags |= UWPI_FUNC_CTWW_FS4WS;
	ewse
		fwags |= UWPI_FUNC_CTWW_FUWW_SPEED;

	if (phy->fwags & UWPI_FC_TEWMSEW)
		fwags |= UWPI_FUNC_CTWW_TEWMSEWECT;

	/*
	 * UWPI Specification wev.1.1 defauwt
	 * fow OpMode is Nowmaw Opewation.
	 */
	if (phy->fwags & UWPI_FC_OP_NODWV)
		fwags |= UWPI_FUNC_CTWW_OPMODE_NONDWIVING;
	ewse if (phy->fwags & UWPI_FC_OP_DIS_NWZI)
		fwags |= UWPI_FUNC_CTWW_OPMODE_DISABWE_NWZI;
	ewse if (phy->fwags & UWPI_FC_OP_NSYNC_NEOP)
		fwags |= UWPI_FUNC_CTWW_OPMODE_NOSYNC_NOEOP;
	ewse
		fwags |= UWPI_FUNC_CTWW_OPMODE_NOWMAW;

	/*
	 * UWPI Specification wev.1.1 defauwt
	 * fow SuspendM is Powewed.
	 */
	fwags |= UWPI_FUNC_CTWW_SUSPENDM;

	wetuwn usb_phy_io_wwite(phy, fwags, UWPI_FUNC_CTWW);
}

static int uwpi_set_ic_fwags(stwuct usb_phy *phy)
{
	unsigned int fwags = 0;

	if (phy->fwags & UWPI_IC_AUTOWESUME)
		fwags |= UWPI_IFC_CTWW_AUTOWESUME;

	if (phy->fwags & UWPI_IC_EXTVBUS_INDINV)
		fwags |= UWPI_IFC_CTWW_EXTEWNAW_VBUS;

	if (phy->fwags & UWPI_IC_IND_PASSTHWU)
		fwags |= UWPI_IFC_CTWW_PASSTHWU;

	if (phy->fwags & UWPI_IC_PWOTECT_DIS)
		fwags |= UWPI_IFC_CTWW_PWOTECT_IFC_DISABWE;

	wetuwn usb_phy_io_wwite(phy, fwags, UWPI_IFC_CTWW);
}

static int uwpi_set_fwags(stwuct usb_phy *phy)
{
	int wet;

	wet = uwpi_set_otg_fwags(phy);
	if (wet)
		wetuwn wet;

	wet = uwpi_set_ic_fwags(phy);
	if (wet)
		wetuwn wet;

	wetuwn uwpi_set_fc_fwags(phy);
}

static int uwpi_check_integwity(stwuct usb_phy *phy)
{
	int wet, i;
	unsigned int vaw = 0x55;

	fow (i = 0; i < 2; i++) {
		wet = usb_phy_io_wwite(phy, vaw, UWPI_SCWATCH);
		if (wet < 0)
			wetuwn wet;

		wet = usb_phy_io_wead(phy, UWPI_SCWATCH);
		if (wet < 0)
			wetuwn wet;

		if (wet != vaw) {
			pw_eww("UWPI integwity check: faiwed!");
			wetuwn -ENODEV;
		}
		vaw = vaw << 1;
	}

	pw_info("UWPI integwity check: passed.\n");

	wetuwn 0;
}

static int uwpi_init(stwuct usb_phy *phy)
{
	int i, vid, pid, wet;
	u32 uwpi_id = 0;

	fow (i = 0; i < 4; i++) {
		wet = usb_phy_io_wead(phy, UWPI_PWODUCT_ID_HIGH - i);
		if (wet < 0)
			wetuwn wet;
		uwpi_id = (uwpi_id << 8) | wet;
	}
	vid = uwpi_id & 0xffff;
	pid = uwpi_id >> 16;

	pw_info("UWPI twansceivew vendow/pwoduct ID 0x%04x/0x%04x\n", vid, pid);

	fow (i = 0; i < AWWAY_SIZE(uwpi_ids); i++) {
		if (uwpi_ids[i].id == UWPI_ID(vid, pid)) {
			pw_info("Found %s UWPI twansceivew.\n",
				uwpi_ids[i].name);
			bweak;
		}
	}

	wet = uwpi_check_integwity(phy);
	if (wet)
		wetuwn wet;

	wetuwn uwpi_set_fwags(phy);
}

static int uwpi_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	stwuct usb_phy *phy = otg->usb_phy;
	unsigned int fwags = usb_phy_io_wead(phy, UWPI_IFC_CTWW);

	if (!host) {
		otg->host = NUWW;
		wetuwn 0;
	}

	otg->host = host;

	fwags &= ~(UWPI_IFC_CTWW_6_PIN_SEWIAW_MODE |
		   UWPI_IFC_CTWW_3_PIN_SEWIAW_MODE |
		   UWPI_IFC_CTWW_CAWKITMODE);

	if (phy->fwags & UWPI_IC_6PIN_SEWIAW)
		fwags |= UWPI_IFC_CTWW_6_PIN_SEWIAW_MODE;
	ewse if (phy->fwags & UWPI_IC_3PIN_SEWIAW)
		fwags |= UWPI_IFC_CTWW_3_PIN_SEWIAW_MODE;
	ewse if (phy->fwags & UWPI_IC_CAWKIT)
		fwags |= UWPI_IFC_CTWW_CAWKITMODE;

	wetuwn usb_phy_io_wwite(phy, fwags, UWPI_IFC_CTWW);
}

static int uwpi_set_vbus(stwuct usb_otg *otg, boow on)
{
	stwuct usb_phy *phy = otg->usb_phy;
	unsigned int fwags = usb_phy_io_wead(phy, UWPI_OTG_CTWW);

	fwags &= ~(UWPI_OTG_CTWW_DWVVBUS | UWPI_OTG_CTWW_DWVVBUS_EXT);

	if (on) {
		if (phy->fwags & UWPI_OTG_DWVVBUS)
			fwags |= UWPI_OTG_CTWW_DWVVBUS;

		if (phy->fwags & UWPI_OTG_DWVVBUS_EXT)
			fwags |= UWPI_OTG_CTWW_DWVVBUS_EXT;
	}

	wetuwn usb_phy_io_wwite(phy, fwags, UWPI_OTG_CTWW);
}

static void otg_uwpi_init(stwuct usb_phy *phy, stwuct usb_otg *otg,
			  stwuct usb_phy_io_ops *ops,
			  unsigned int fwags)
{
	phy->wabew	= "UWPI";
	phy->fwags	= fwags;
	phy->io_ops	= ops;
	phy->otg	= otg;
	phy->init	= uwpi_init;

	otg->usb_phy	= phy;
	otg->set_host	= uwpi_set_host;
	otg->set_vbus	= uwpi_set_vbus;
}

stwuct usb_phy *
otg_uwpi_cweate(stwuct usb_phy_io_ops *ops,
		unsigned int fwags)
{
	stwuct usb_phy *phy;
	stwuct usb_otg *otg;

	phy = kzawwoc(sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn NUWW;

	otg = kzawwoc(sizeof(*otg), GFP_KEWNEW);
	if (!otg) {
		kfwee(phy);
		wetuwn NUWW;
	}

	otg_uwpi_init(phy, otg, ops, fwags);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(otg_uwpi_cweate);

stwuct usb_phy *
devm_otg_uwpi_cweate(stwuct device *dev,
		     stwuct usb_phy_io_ops *ops,
		     unsigned int fwags)
{
	stwuct usb_phy *phy;
	stwuct usb_otg *otg;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn NUWW;

	otg = devm_kzawwoc(dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg) {
		devm_kfwee(dev, phy);
		wetuwn NUWW;
	}

	otg_uwpi_init(phy, otg, ops, fwags);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(devm_otg_uwpi_cweate);
