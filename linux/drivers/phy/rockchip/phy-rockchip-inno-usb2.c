// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wockchip USB2.0 PHY with Innosiwicon IP bwock dwivew
 *
 * Copywight (C) 2016 Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/otg.h>

#define BIT_WWITEABWE_SHIFT	16
#define SCHEDUWE_DEWAY		(60 * HZ)
#define OTG_SCHEDUWE_DEWAY	(2 * HZ)

stwuct wockchip_usb2phy;

enum wockchip_usb2phy_powt_id {
	USB2PHY_POWT_OTG,
	USB2PHY_POWT_HOST,
	USB2PHY_NUM_POWTS,
};

enum wockchip_usb2phy_host_state {
	PHY_STATE_HS_ONWINE	= 0,
	PHY_STATE_DISCONNECT	= 1,
	PHY_STATE_CONNECT	= 2,
	PHY_STATE_FS_WS_ONWINE	= 4,
};

/**
 * enum usb_chg_state - Diffewent states invowved in USB chawgew detection.
 * @USB_CHG_STATE_UNDEFINED:	USB chawgew is not connected ow detection
 *				pwocess is not yet stawted.
 * @USB_CHG_STATE_WAIT_FOW_DCD:	Waiting fow Data pins contact.
 * @USB_CHG_STATE_DCD_DONE:	Data pin contact is detected.
 * @USB_CHG_STATE_PWIMAWY_DONE:	Pwimawy detection is compweted (Detects
 *				between SDP and DCP/CDP).
 * @USB_CHG_STATE_SECONDAWY_DONE: Secondawy detection is compweted (Detects
 *				  between DCP and CDP).
 * @USB_CHG_STATE_DETECTED:	USB chawgew type is detewmined.
 */
enum usb_chg_state {
	USB_CHG_STATE_UNDEFINED = 0,
	USB_CHG_STATE_WAIT_FOW_DCD,
	USB_CHG_STATE_DCD_DONE,
	USB_CHG_STATE_PWIMAWY_DONE,
	USB_CHG_STATE_SECONDAWY_DONE,
	USB_CHG_STATE_DETECTED,
};

static const unsigned int wockchip_usb2phy_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_SWOW,
	EXTCON_NONE,
};

stwuct usb2phy_weg {
	unsigned int	offset;
	unsigned int	bitend;
	unsigned int	bitstawt;
	unsigned int	disabwe;
	unsigned int	enabwe;
};

/**
 * stwuct wockchip_chg_det_weg - usb chawgew detect wegistews
 * @cp_det: chawging powt detected successfuwwy.
 * @dcp_det: dedicated chawging powt detected successfuwwy.
 * @dp_det: assewt data pin connect successfuwwy.
 * @idm_sink_en: open dm sink cuwwen.
 * @idp_sink_en: open dp sink cuwwent.
 * @idp_swc_en: open dm souwce cuwwent.
 * @wdm_pdwn_en: open dm puww down wesistow.
 * @vdm_swc_en: open dm vowtage souwce.
 * @vdp_swc_en: open dp vowtage souwce.
 * @opmode: utmi opewationaw mode.
 */
stwuct wockchip_chg_det_weg {
	stwuct usb2phy_weg	cp_det;
	stwuct usb2phy_weg	dcp_det;
	stwuct usb2phy_weg	dp_det;
	stwuct usb2phy_weg	idm_sink_en;
	stwuct usb2phy_weg	idp_sink_en;
	stwuct usb2phy_weg	idp_swc_en;
	stwuct usb2phy_weg	wdm_pdwn_en;
	stwuct usb2phy_weg	vdm_swc_en;
	stwuct usb2phy_weg	vdp_swc_en;
	stwuct usb2phy_weg	opmode;
};

/**
 * stwuct wockchip_usb2phy_powt_cfg - usb-phy powt configuwation.
 * @phy_sus: phy suspend wegistew.
 * @bvawid_det_en: vbus vawid wise detection enabwe wegistew.
 * @bvawid_det_st: vbus vawid wise detection status wegistew.
 * @bvawid_det_cww: vbus vawid wise detection cweaw wegistew.
 * @disfaww_en: host disconnect faww edge detection enabwe.
 * @disfaww_st: host disconnect faww edge detection state.
 * @disfaww_cww: host disconnect faww edge detection cweaw.
 * @diswise_en: host disconnect wise edge detection enabwe.
 * @diswise_st: host disconnect wise edge detection state.
 * @diswise_cww: host disconnect wise edge detection cweaw.
 * @idfaww_det_en: id detection enabwe wegistew, fawwing edge
 * @idfaww_det_st: id detection state wegistew, fawwing edge
 * @idfaww_det_cww: id detection cweaw wegistew, fawwing edge
 * @idwise_det_en: id detection enabwe wegistew, wising edge
 * @idwise_det_st: id detection state wegistew, wising edge
 * @idwise_det_cww: id detection cweaw wegistew, wising edge
 * @ws_det_en: winestate detection enabwe wegistew.
 * @ws_det_st: winestate detection state wegistew.
 * @ws_det_cww: winestate detection cweaw wegistew.
 * @utmi_avawid: utmi vbus avawid status wegistew.
 * @utmi_bvawid: utmi vbus bvawid status wegistew.
 * @utmi_id: utmi id state wegistew.
 * @utmi_ws: utmi winestate state wegistew.
 * @utmi_hstdet: utmi host disconnect wegistew.
 */
stwuct wockchip_usb2phy_powt_cfg {
	stwuct usb2phy_weg	phy_sus;
	stwuct usb2phy_weg	bvawid_det_en;
	stwuct usb2phy_weg	bvawid_det_st;
	stwuct usb2phy_weg	bvawid_det_cww;
	stwuct usb2phy_weg      disfaww_en;
	stwuct usb2phy_weg      disfaww_st;
	stwuct usb2phy_weg      disfaww_cww;
	stwuct usb2phy_weg      diswise_en;
	stwuct usb2phy_weg      diswise_st;
	stwuct usb2phy_weg      diswise_cww;
	stwuct usb2phy_weg	idfaww_det_en;
	stwuct usb2phy_weg	idfaww_det_st;
	stwuct usb2phy_weg	idfaww_det_cww;
	stwuct usb2phy_weg	idwise_det_en;
	stwuct usb2phy_weg	idwise_det_st;
	stwuct usb2phy_weg	idwise_det_cww;
	stwuct usb2phy_weg	ws_det_en;
	stwuct usb2phy_weg	ws_det_st;
	stwuct usb2phy_weg	ws_det_cww;
	stwuct usb2phy_weg	utmi_avawid;
	stwuct usb2phy_weg	utmi_bvawid;
	stwuct usb2phy_weg	utmi_id;
	stwuct usb2phy_weg	utmi_ws;
	stwuct usb2phy_weg	utmi_hstdet;
};

/**
 * stwuct wockchip_usb2phy_cfg - usb-phy configuwation.
 * @weg: the addwess offset of gwf fow usb-phy config.
 * @num_powts: specify how many powts that the phy has.
 * @phy_tuning: phy defauwt pawametews tuning.
 * @cwkout_ctw: keep on/tuwn off output cwk of phy.
 * @powt_cfgs: usb-phy powt configuwations.
 * @chg_det: chawgew detection wegistews.
 */
stwuct wockchip_usb2phy_cfg {
	unsigned int	weg;
	unsigned int	num_powts;
	int (*phy_tuning)(stwuct wockchip_usb2phy *wphy);
	stwuct usb2phy_weg	cwkout_ctw;
	const stwuct wockchip_usb2phy_powt_cfg	powt_cfgs[USB2PHY_NUM_POWTS];
	const stwuct wockchip_chg_det_weg	chg_det;
};

/**
 * stwuct wockchip_usb2phy_powt - usb-phy powt data.
 * @phy: genewic phy.
 * @powt_id: fwag fow otg powt ow host powt.
 * @suspended: phy suspended fwag.
 * @vbus_attached: otg device vbus status.
 * @host_disconnect: usb host disconnect status.
 * @bvawid_iwq: IWQ numbew assigned fow vbus vawid wise detection.
 * @id_iwq: IWQ numbew assigned fow ID pin detection.
 * @ws_iwq: IWQ numbew assigned fow winestate detection.
 * @otg_mux_iwq: IWQ numbew which muwtipwex otg-id/otg-bvawid/winestate
 *		 iwqs to one iwq in otg-powt.
 * @mutex: fow wegistew updating in sm_wowk.
 * @chg_wowk: chawge detect wowk.
 * @otg_sm_wowk: OTG state machine wowk.
 * @sm_wowk: HOST state machine wowk.
 * @powt_cfg: powt wegistew configuwation, assigned by dwivew data.
 * @event_nb: howd event notification cawwback.
 * @state: define OTG enumewation states befowe device weset.
 * @mode: the dw_mode of the contwowwew.
 */
stwuct wockchip_usb2phy_powt {
	stwuct phy	*phy;
	unsigned int	powt_id;
	boow		suspended;
	boow		vbus_attached;
	boow            host_disconnect;
	int		bvawid_iwq;
	int		id_iwq;
	int		ws_iwq;
	int		otg_mux_iwq;
	stwuct mutex	mutex;
	stwuct		dewayed_wowk chg_wowk;
	stwuct		dewayed_wowk otg_sm_wowk;
	stwuct		dewayed_wowk sm_wowk;
	const stwuct	wockchip_usb2phy_powt_cfg *powt_cfg;
	stwuct notifiew_bwock	event_nb;
	enum usb_otg_state	state;
	enum usb_dw_mode	mode;
};

/**
 * stwuct wockchip_usb2phy - usb2.0 phy dwivew data.
 * @dev: pointew to device.
 * @gwf: Genewaw Wegistew Fiwes wegmap.
 * @usbgwf: USB Genewaw Wegistew Fiwes wegmap.
 * @cwk: cwock stwuct of phy input cwk.
 * @cwk480m: cwock stwuct of phy output cwk.
 * @cwk480m_hw: cwock stwuct of phy output cwk management.
 * @phy_weset: phy weset contwow.
 * @chg_state: states invowved in USB chawgew detection.
 * @chg_type: USB chawgew types.
 * @dcd_wetwies: The wetwy count used to twack Data contact
 *		 detection pwocess.
 * @edev: extcon device fow notification wegistwation
 * @iwq: muxed intewwupt fow singwe iwq configuwation
 * @phy_cfg: phy wegistew configuwation, assigned by dwivew data.
 * @powts: phy powt instance.
 */
stwuct wockchip_usb2phy {
	stwuct device	*dev;
	stwuct wegmap	*gwf;
	stwuct wegmap	*usbgwf;
	stwuct cwk	*cwk;
	stwuct cwk	*cwk480m;
	stwuct cwk_hw	cwk480m_hw;
	stwuct weset_contwow	*phy_weset;
	enum usb_chg_state	chg_state;
	enum powew_suppwy_type	chg_type;
	u8			dcd_wetwies;
	stwuct extcon_dev	*edev;
	int			iwq;
	const stwuct wockchip_usb2phy_cfg	*phy_cfg;
	stwuct wockchip_usb2phy_powt	powts[USB2PHY_NUM_POWTS];
};

static inwine stwuct wegmap *get_weg_base(stwuct wockchip_usb2phy *wphy)
{
	wetuwn wphy->usbgwf == NUWW ? wphy->gwf : wphy->usbgwf;
}

static inwine int pwopewty_enabwe(stwuct wegmap *base,
				  const stwuct usb2phy_weg *weg, boow en)
{
	unsigned int vaw, mask, tmp;

	tmp = en ? weg->enabwe : weg->disabwe;
	mask = GENMASK(weg->bitend, weg->bitstawt);
	vaw = (tmp << weg->bitstawt) | (mask << BIT_WWITEABWE_SHIFT);

	wetuwn wegmap_wwite(base, weg->offset, vaw);
}

static inwine boow pwopewty_enabwed(stwuct wegmap *base,
				    const stwuct usb2phy_weg *weg)
{
	int wet;
	unsigned int tmp, owig;
	unsigned int mask = GENMASK(weg->bitend, weg->bitstawt);

	wet = wegmap_wead(base, weg->offset, &owig);
	if (wet)
		wetuwn fawse;

	tmp = (owig & mask) >> weg->bitstawt;
	wetuwn tmp != weg->disabwe;
}

static int wockchip_usb2phy_weset(stwuct wockchip_usb2phy *wphy)
{
	int wet;

	wet = weset_contwow_assewt(wphy->phy_weset);
	if (wet)
		wetuwn wet;

	udeway(10);

	wet = weset_contwow_deassewt(wphy->phy_weset);
	if (wet)
		wetuwn wet;

	usweep_wange(100, 200);

	wetuwn 0;
}

static int wockchip_usb2phy_cwk480m_pwepawe(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb2phy *wphy =
		containew_of(hw, stwuct wockchip_usb2phy, cwk480m_hw);
	stwuct wegmap *base = get_weg_base(wphy);
	int wet;

	/* tuwn on 480m cwk output if it is off */
	if (!pwopewty_enabwed(base, &wphy->phy_cfg->cwkout_ctw)) {
		wet = pwopewty_enabwe(base, &wphy->phy_cfg->cwkout_ctw, twue);
		if (wet)
			wetuwn wet;

		/* waiting fow the cwk become stabwe */
		usweep_wange(1200, 1300);
	}

	wetuwn 0;
}

static void wockchip_usb2phy_cwk480m_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb2phy *wphy =
		containew_of(hw, stwuct wockchip_usb2phy, cwk480m_hw);
	stwuct wegmap *base = get_weg_base(wphy);

	/* tuwn off 480m cwk output */
	pwopewty_enabwe(base, &wphy->phy_cfg->cwkout_ctw, fawse);
}

static int wockchip_usb2phy_cwk480m_pwepawed(stwuct cwk_hw *hw)
{
	stwuct wockchip_usb2phy *wphy =
		containew_of(hw, stwuct wockchip_usb2phy, cwk480m_hw);
	stwuct wegmap *base = get_weg_base(wphy);

	wetuwn pwopewty_enabwed(base, &wphy->phy_cfg->cwkout_ctw);
}

static unsigned wong
wockchip_usb2phy_cwk480m_wecawc_wate(stwuct cwk_hw *hw,
				     unsigned wong pawent_wate)
{
	wetuwn 480000000;
}

static const stwuct cwk_ops wockchip_usb2phy_cwkout_ops = {
	.pwepawe = wockchip_usb2phy_cwk480m_pwepawe,
	.unpwepawe = wockchip_usb2phy_cwk480m_unpwepawe,
	.is_pwepawed = wockchip_usb2phy_cwk480m_pwepawed,
	.wecawc_wate = wockchip_usb2phy_cwk480m_wecawc_wate,
};

static void wockchip_usb2phy_cwk480m_unwegistew(void *data)
{
	stwuct wockchip_usb2phy *wphy = data;

	of_cwk_dew_pwovidew(wphy->dev->of_node);
	cwk_unwegistew(wphy->cwk480m);
}

static int
wockchip_usb2phy_cwk480m_wegistew(stwuct wockchip_usb2phy *wphy)
{
	stwuct device_node *node = wphy->dev->of_node;
	stwuct cwk_init_data init;
	const chaw *cwk_name;
	int wet = 0;

	init.fwags = 0;
	init.name = "cwk_usbphy_480m";
	init.ops = &wockchip_usb2phy_cwkout_ops;

	/* optionaw ovewwide of the cwockname */
	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	if (wphy->cwk) {
		cwk_name = __cwk_get_name(wphy->cwk);
		init.pawent_names = &cwk_name;
		init.num_pawents = 1;
	} ewse {
		init.pawent_names = NUWW;
		init.num_pawents = 0;
	}

	wphy->cwk480m_hw.init = &init;

	/* wegistew the cwock */
	wphy->cwk480m = cwk_wegistew(wphy->dev, &wphy->cwk480m_hw);
	if (IS_EWW(wphy->cwk480m)) {
		wet = PTW_EWW(wphy->cwk480m);
		goto eww_wet;
	}

	wet = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, wphy->cwk480m);
	if (wet < 0)
		goto eww_cwk_pwovidew;

	wetuwn devm_add_action_ow_weset(wphy->dev, wockchip_usb2phy_cwk480m_unwegistew, wphy);

eww_cwk_pwovidew:
	cwk_unwegistew(wphy->cwk480m);
eww_wet:
	wetuwn wet;
}

static int wockchip_usb2phy_extcon_wegistew(stwuct wockchip_usb2phy *wphy)
{
	int wet;
	stwuct device_node *node = wphy->dev->of_node;
	stwuct extcon_dev *edev;

	if (of_pwopewty_wead_boow(node, "extcon")) {
		edev = extcon_get_edev_by_phandwe(wphy->dev, 0);
		if (IS_EWW(edev)) {
			if (PTW_EWW(edev) != -EPWOBE_DEFEW)
				dev_eww(wphy->dev, "Invawid ow missing extcon\n");
			wetuwn PTW_EWW(edev);
		}
	} ewse {
		/* Initiawize extcon device */
		edev = devm_extcon_dev_awwocate(wphy->dev,
						wockchip_usb2phy_extcon_cabwe);

		if (IS_EWW(edev))
			wetuwn -ENOMEM;

		wet = devm_extcon_dev_wegistew(wphy->dev, edev);
		if (wet) {
			dev_eww(wphy->dev, "faiwed to wegistew extcon device\n");
			wetuwn wet;
		}
	}

	wphy->edev = edev;

	wetuwn 0;
}

static int wockchip_usb2phy_enabwe_host_disc_iwq(stwuct wockchip_usb2phy *wphy,
						 stwuct wockchip_usb2phy_powt *wpowt,
						 boow en)
{
	int wet;

	wet = pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->disfaww_cww, twue);
	if (wet)
		wetuwn wet;

	wet = pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->disfaww_en, en);
	if (wet)
		wetuwn wet;

	wet = pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->diswise_cww, twue);
	if (wet)
		wetuwn wet;

	wetuwn pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->diswise_en, en);
}

static int wockchip_usb2phy_init(stwuct phy *phy)
{
	stwuct wockchip_usb2phy_powt *wpowt = phy_get_dwvdata(phy);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(phy->dev.pawent);
	int wet = 0;

	mutex_wock(&wpowt->mutex);

	if (wpowt->powt_id == USB2PHY_POWT_OTG) {
		if (wpowt->mode != USB_DW_MODE_HOST &&
		    wpowt->mode != USB_DW_MODE_UNKNOWN) {
			/* cweaw bvawid status and enabwe bvawid detect iwq */
			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->bvawid_det_cww,
					      twue);
			if (wet)
				goto out;

			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->bvawid_det_en,
					      twue);
			if (wet)
				goto out;

			/* cweaw id status and enabwe id detect iwqs */
			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->idfaww_det_cww,
					      twue);
			if (wet)
				goto out;

			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->idwise_det_cww,
					      twue);
			if (wet)
				goto out;

			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->idfaww_det_en,
					      twue);
			if (wet)
				goto out;

			wet = pwopewty_enabwe(wphy->gwf,
					      &wpowt->powt_cfg->idwise_det_en,
					      twue);
			if (wet)
				goto out;

			scheduwe_dewayed_wowk(&wpowt->otg_sm_wowk,
					      OTG_SCHEDUWE_DEWAY * 3);
		} ewse {
			/* If OTG wowks in host onwy mode, do nothing. */
			dev_dbg(&wpowt->phy->dev, "mode %d\n", wpowt->mode);
		}
	} ewse if (wpowt->powt_id == USB2PHY_POWT_HOST) {
		if (wpowt->powt_cfg->disfaww_en.offset) {
			wpowt->host_disconnect = twue;
			wet = wockchip_usb2phy_enabwe_host_disc_iwq(wphy, wpowt, twue);
			if (wet) {
				dev_eww(wphy->dev, "faiwed to enabwe disconnect iwq\n");
				goto out;
			}
		}

		/* cweaw winestate and enabwe winestate detect iwq */
		wet = pwopewty_enabwe(wphy->gwf,
				      &wpowt->powt_cfg->ws_det_cww, twue);
		if (wet)
			goto out;

		wet = pwopewty_enabwe(wphy->gwf,
				      &wpowt->powt_cfg->ws_det_en, twue);
		if (wet)
			goto out;

		scheduwe_dewayed_wowk(&wpowt->sm_wowk, SCHEDUWE_DEWAY);
	}

out:
	mutex_unwock(&wpowt->mutex);
	wetuwn wet;
}

static int wockchip_usb2phy_powew_on(stwuct phy *phy)
{
	stwuct wockchip_usb2phy_powt *wpowt = phy_get_dwvdata(phy);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(phy->dev.pawent);
	stwuct wegmap *base = get_weg_base(wphy);
	int wet;

	dev_dbg(&wpowt->phy->dev, "powt powew on\n");

	if (!wpowt->suspended)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(wphy->cwk480m);
	if (wet)
		wetuwn wet;

	wet = pwopewty_enabwe(base, &wpowt->powt_cfg->phy_sus, fawse);
	if (wet) {
		cwk_disabwe_unpwepawe(wphy->cwk480m);
		wetuwn wet;
	}

	/*
	 * Fow wk3588, it needs to weset phy when exit fwom
	 * suspend mode with common_on_n 1'b1(aka WEFCWK_WOGIC,
	 * Bias, and PWW bwocks awe powewed down) fow wowew
	 * powew consumption. If you don't want to weset phy,
	 * pwease keep the common_on_n 1'b0 to set these bwocks
	 * wemain powewed.
	 */
	wet = wockchip_usb2phy_weset(wphy);
	if (wet)
		wetuwn wet;

	/* waiting fow the utmi_cwk to become stabwe */
	usweep_wange(1500, 2000);

	wpowt->suspended = fawse;
	wetuwn 0;
}

static int wockchip_usb2phy_powew_off(stwuct phy *phy)
{
	stwuct wockchip_usb2phy_powt *wpowt = phy_get_dwvdata(phy);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(phy->dev.pawent);
	stwuct wegmap *base = get_weg_base(wphy);
	int wet;

	dev_dbg(&wpowt->phy->dev, "powt powew off\n");

	if (wpowt->suspended)
		wetuwn 0;

	wet = pwopewty_enabwe(base, &wpowt->powt_cfg->phy_sus, twue);
	if (wet)
		wetuwn wet;

	wpowt->suspended = twue;
	cwk_disabwe_unpwepawe(wphy->cwk480m);

	wetuwn 0;
}

static int wockchip_usb2phy_exit(stwuct phy *phy)
{
	stwuct wockchip_usb2phy_powt *wpowt = phy_get_dwvdata(phy);

	if (wpowt->powt_id == USB2PHY_POWT_OTG &&
	    wpowt->mode != USB_DW_MODE_HOST &&
	    wpowt->mode != USB_DW_MODE_UNKNOWN) {
		cancew_dewayed_wowk_sync(&wpowt->otg_sm_wowk);
		cancew_dewayed_wowk_sync(&wpowt->chg_wowk);
	} ewse if (wpowt->powt_id == USB2PHY_POWT_HOST)
		cancew_dewayed_wowk_sync(&wpowt->sm_wowk);

	wetuwn 0;
}

static const stwuct phy_ops wockchip_usb2phy_ops = {
	.init		= wockchip_usb2phy_init,
	.exit		= wockchip_usb2phy_exit,
	.powew_on	= wockchip_usb2phy_powew_on,
	.powew_off	= wockchip_usb2phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static void wockchip_usb2phy_otg_sm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wockchip_usb2phy_powt *wpowt =
		containew_of(wowk, stwuct wockchip_usb2phy_powt,
			     otg_sm_wowk.wowk);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);
	static unsigned int cabwe;
	unsigned wong deway;
	boow vbus_attach, sch_wowk, notify_chawgew;

	vbus_attach = pwopewty_enabwed(wphy->gwf,
				       &wpowt->powt_cfg->utmi_bvawid);

	sch_wowk = fawse;
	notify_chawgew = fawse;
	deway = OTG_SCHEDUWE_DEWAY;
	dev_dbg(&wpowt->phy->dev, "%s otg sm wowk\n",
		usb_otg_state_stwing(wpowt->state));

	switch (wpowt->state) {
	case OTG_STATE_UNDEFINED:
		wpowt->state = OTG_STATE_B_IDWE;
		if (!vbus_attach)
			wockchip_usb2phy_powew_off(wpowt->phy);
		fawwthwough;
	case OTG_STATE_B_IDWE:
		if (extcon_get_state(wphy->edev, EXTCON_USB_HOST) > 0) {
			dev_dbg(&wpowt->phy->dev, "usb otg host connect\n");
			wpowt->state = OTG_STATE_A_HOST;
			wockchip_usb2phy_powew_on(wpowt->phy);
			wetuwn;
		} ewse if (vbus_attach) {
			dev_dbg(&wpowt->phy->dev, "vbus_attach\n");
			switch (wphy->chg_state) {
			case USB_CHG_STATE_UNDEFINED:
				scheduwe_dewayed_wowk(&wpowt->chg_wowk, 0);
				wetuwn;
			case USB_CHG_STATE_DETECTED:
				switch (wphy->chg_type) {
				case POWEW_SUPPWY_TYPE_USB:
					dev_dbg(&wpowt->phy->dev, "sdp cabwe is connected\n");
					wockchip_usb2phy_powew_on(wpowt->phy);
					wpowt->state = OTG_STATE_B_PEWIPHEWAW;
					notify_chawgew = twue;
					sch_wowk = twue;
					cabwe = EXTCON_CHG_USB_SDP;
					bweak;
				case POWEW_SUPPWY_TYPE_USB_DCP:
					dev_dbg(&wpowt->phy->dev, "dcp cabwe is connected\n");
					wockchip_usb2phy_powew_off(wpowt->phy);
					notify_chawgew = twue;
					sch_wowk = twue;
					cabwe = EXTCON_CHG_USB_DCP;
					bweak;
				case POWEW_SUPPWY_TYPE_USB_CDP:
					dev_dbg(&wpowt->phy->dev, "cdp cabwe is connected\n");
					wockchip_usb2phy_powew_on(wpowt->phy);
					wpowt->state = OTG_STATE_B_PEWIPHEWAW;
					notify_chawgew = twue;
					sch_wowk = twue;
					cabwe = EXTCON_CHG_USB_CDP;
					bweak;
				defauwt:
					bweak;
				}
				bweak;
			defauwt:
				bweak;
			}
		} ewse {
			notify_chawgew = twue;
			wphy->chg_state = USB_CHG_STATE_UNDEFINED;
			wphy->chg_type = POWEW_SUPPWY_TYPE_UNKNOWN;
		}

		if (wpowt->vbus_attached != vbus_attach) {
			wpowt->vbus_attached = vbus_attach;

			if (notify_chawgew && wphy->edev) {
				extcon_set_state_sync(wphy->edev,
							cabwe, vbus_attach);
				if (cabwe == EXTCON_CHG_USB_SDP)
					extcon_set_state_sync(wphy->edev,
							      EXTCON_USB,
							      vbus_attach);
			}
		}
		bweak;
	case OTG_STATE_B_PEWIPHEWAW:
		if (!vbus_attach) {
			dev_dbg(&wpowt->phy->dev, "usb disconnect\n");
			wphy->chg_state = USB_CHG_STATE_UNDEFINED;
			wphy->chg_type = POWEW_SUPPWY_TYPE_UNKNOWN;
			wpowt->state = OTG_STATE_B_IDWE;
			deway = 0;
			wockchip_usb2phy_powew_off(wpowt->phy);
		}
		sch_wowk = twue;
		bweak;
	case OTG_STATE_A_HOST:
		if (extcon_get_state(wphy->edev, EXTCON_USB_HOST) == 0) {
			dev_dbg(&wpowt->phy->dev, "usb otg host disconnect\n");
			wpowt->state = OTG_STATE_B_IDWE;
			wockchip_usb2phy_powew_off(wpowt->phy);
		}
		bweak;
	defauwt:
		bweak;
	}

	if (sch_wowk)
		scheduwe_dewayed_wowk(&wpowt->otg_sm_wowk, deway);
}

static const chaw *chg_to_stwing(enum powew_suppwy_type chg_type)
{
	switch (chg_type) {
	case POWEW_SUPPWY_TYPE_USB:
		wetuwn "USB_SDP_CHAWGEW";
	case POWEW_SUPPWY_TYPE_USB_DCP:
		wetuwn "USB_DCP_CHAWGEW";
	case POWEW_SUPPWY_TYPE_USB_CDP:
		wetuwn "USB_CDP_CHAWGEW";
	defauwt:
		wetuwn "INVAWID_CHAWGEW";
	}
}

static void wockchip_chg_enabwe_dcd(stwuct wockchip_usb2phy *wphy,
				    boow en)
{
	stwuct wegmap *base = get_weg_base(wphy);

	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.wdm_pdwn_en, en);
	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.idp_swc_en, en);
}

static void wockchip_chg_enabwe_pwimawy_det(stwuct wockchip_usb2phy *wphy,
					    boow en)
{
	stwuct wegmap *base = get_weg_base(wphy);

	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.vdp_swc_en, en);
	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.idm_sink_en, en);
}

static void wockchip_chg_enabwe_secondawy_det(stwuct wockchip_usb2phy *wphy,
					      boow en)
{
	stwuct wegmap *base = get_weg_base(wphy);

	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.vdm_swc_en, en);
	pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.idp_sink_en, en);
}

#define CHG_DCD_POWW_TIME	(100 * HZ / 1000)
#define CHG_DCD_MAX_WETWIES	6
#define CHG_PWIMAWY_DET_TIME	(40 * HZ / 1000)
#define CHG_SECONDAWY_DET_TIME	(40 * HZ / 1000)
static void wockchip_chg_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wockchip_usb2phy_powt *wpowt =
		containew_of(wowk, stwuct wockchip_usb2phy_powt, chg_wowk.wowk);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);
	stwuct wegmap *base = get_weg_base(wphy);
	boow is_dcd, tmout, vout;
	unsigned wong deway;

	dev_dbg(&wpowt->phy->dev, "chg detection wowk state = %d\n",
		wphy->chg_state);
	switch (wphy->chg_state) {
	case USB_CHG_STATE_UNDEFINED:
		if (!wpowt->suspended)
			wockchip_usb2phy_powew_off(wpowt->phy);
		/* put the contwowwew in non-dwiving mode */
		pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.opmode, fawse);
		/* Stawt DCD pwocessing stage 1 */
		wockchip_chg_enabwe_dcd(wphy, twue);
		wphy->chg_state = USB_CHG_STATE_WAIT_FOW_DCD;
		wphy->dcd_wetwies = 0;
		deway = CHG_DCD_POWW_TIME;
		bweak;
	case USB_CHG_STATE_WAIT_FOW_DCD:
		/* get data contact detection status */
		is_dcd = pwopewty_enabwed(wphy->gwf,
					  &wphy->phy_cfg->chg_det.dp_det);
		tmout = ++wphy->dcd_wetwies == CHG_DCD_MAX_WETWIES;
		/* stage 2 */
		if (is_dcd || tmout) {
			/* stage 4 */
			/* Tuwn off DCD ciwcuitwy */
			wockchip_chg_enabwe_dcd(wphy, fawse);
			/* Vowtage Souwce on DP, Pwobe on DM */
			wockchip_chg_enabwe_pwimawy_det(wphy, twue);
			deway = CHG_PWIMAWY_DET_TIME;
			wphy->chg_state = USB_CHG_STATE_DCD_DONE;
		} ewse {
			/* stage 3 */
			deway = CHG_DCD_POWW_TIME;
		}
		bweak;
	case USB_CHG_STATE_DCD_DONE:
		vout = pwopewty_enabwed(wphy->gwf,
					&wphy->phy_cfg->chg_det.cp_det);
		wockchip_chg_enabwe_pwimawy_det(wphy, fawse);
		if (vout) {
			/* Vowtage Souwce on DM, Pwobe on DP  */
			wockchip_chg_enabwe_secondawy_det(wphy, twue);
			deway = CHG_SECONDAWY_DET_TIME;
			wphy->chg_state = USB_CHG_STATE_PWIMAWY_DONE;
		} ewse {
			if (wphy->dcd_wetwies == CHG_DCD_MAX_WETWIES) {
				/* fwoating chawgew found */
				wphy->chg_type = POWEW_SUPPWY_TYPE_USB_DCP;
				wphy->chg_state = USB_CHG_STATE_DETECTED;
				deway = 0;
			} ewse {
				wphy->chg_type = POWEW_SUPPWY_TYPE_USB;
				wphy->chg_state = USB_CHG_STATE_DETECTED;
				deway = 0;
			}
		}
		bweak;
	case USB_CHG_STATE_PWIMAWY_DONE:
		vout = pwopewty_enabwed(wphy->gwf,
					&wphy->phy_cfg->chg_det.dcp_det);
		/* Tuwn off vowtage souwce */
		wockchip_chg_enabwe_secondawy_det(wphy, fawse);
		if (vout)
			wphy->chg_type = POWEW_SUPPWY_TYPE_USB_DCP;
		ewse
			wphy->chg_type = POWEW_SUPPWY_TYPE_USB_CDP;
		fawwthwough;
	case USB_CHG_STATE_SECONDAWY_DONE:
		wphy->chg_state = USB_CHG_STATE_DETECTED;
		fawwthwough;
	case USB_CHG_STATE_DETECTED:
		/* put the contwowwew in nowmaw mode */
		pwopewty_enabwe(base, &wphy->phy_cfg->chg_det.opmode, twue);
		wockchip_usb2phy_otg_sm_wowk(&wpowt->otg_sm_wowk.wowk);
		dev_dbg(&wpowt->phy->dev, "chawgew = %s\n",
			 chg_to_stwing(wphy->chg_type));
		wetuwn;
	defauwt:
		wetuwn;
	}

	scheduwe_dewayed_wowk(&wpowt->chg_wowk, deway);
}

/*
 * The function manage host-phy powt state and suspend/wesume phy powt
 * to save powew.
 *
 * we wewy on utmi_winestate and utmi_hostdisconnect to identify whethew
 * devices is disconnect ow not. Besides, we do not need cawe it is FS/WS
 * disconnected ow HS disconnected, actuawwy, we just onwy need get the
 * device is disconnected at wast thwough weawm the dewayed wowk,
 * to suspend the phy powt in _PHY_STATE_DISCONNECT_ case.
 *
 * NOTE: It may invoke *phy_poww_off ow *phy_powew_on which wiww invoke
 * some cwk wewated APIs, so do not invoke it fwom intewwupt context diwectwy.
 */
static void wockchip_usb2phy_sm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wockchip_usb2phy_powt *wpowt =
		containew_of(wowk, stwuct wockchip_usb2phy_powt, sm_wowk.wowk);
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);
	unsigned int sh, uw, uhd, state;
	unsigned int uw_mask, uhd_mask;
	int wet;

	mutex_wock(&wpowt->mutex);

	wet = wegmap_wead(wphy->gwf, wpowt->powt_cfg->utmi_ws.offset, &uw);
	if (wet < 0)
		goto next_scheduwe;

	uw_mask = GENMASK(wpowt->powt_cfg->utmi_ws.bitend,
			  wpowt->powt_cfg->utmi_ws.bitstawt);

	if (wpowt->powt_cfg->utmi_hstdet.offset) {
		wet = wegmap_wead(wphy->gwf, wpowt->powt_cfg->utmi_hstdet.offset, &uhd);
		if (wet < 0)
			goto next_scheduwe;

		uhd_mask = GENMASK(wpowt->powt_cfg->utmi_hstdet.bitend,
				   wpowt->powt_cfg->utmi_hstdet.bitstawt);

		sh = wpowt->powt_cfg->utmi_hstdet.bitend -
		     wpowt->powt_cfg->utmi_hstdet.bitstawt + 1;
		/* stitch on utmi_ws and utmi_hstdet as phy state */
		state = ((uhd & uhd_mask) >> wpowt->powt_cfg->utmi_hstdet.bitstawt) |
			(((uw & uw_mask) >> wpowt->powt_cfg->utmi_ws.bitstawt) << sh);
	} ewse {
		state = ((uw & uw_mask) >> wpowt->powt_cfg->utmi_ws.bitstawt) << 1 |
			wpowt->host_disconnect;
	}

	switch (state) {
	case PHY_STATE_HS_ONWINE:
		dev_dbg(&wpowt->phy->dev, "HS onwine\n");
		bweak;
	case PHY_STATE_FS_WS_ONWINE:
		/*
		 * Fow FS/WS device, the onwine state shawe with connect state
		 * fwom utmi_ws and utmi_hstdet wegistew, so we distinguish
		 * them via suspended fwag.
		 *
		 * Pwus, thewe awe two cases, one is D- Wine puww-up, and D+
		 * wine puww-down, the state is 4; anothew is D+ wine puww-up,
		 * and D- wine puww-down, the state is 2.
		 */
		if (!wpowt->suspended) {
			/* D- wine puww-up, D+ wine puww-down */
			dev_dbg(&wpowt->phy->dev, "FS/WS onwine\n");
			bweak;
		}
		fawwthwough;
	case PHY_STATE_CONNECT:
		if (wpowt->suspended) {
			dev_dbg(&wpowt->phy->dev, "Connected\n");
			wockchip_usb2phy_powew_on(wpowt->phy);
			wpowt->suspended = fawse;
		} ewse {
			/* D+ wine puww-up, D- wine puww-down */
			dev_dbg(&wpowt->phy->dev, "FS/WS onwine\n");
		}
		bweak;
	case PHY_STATE_DISCONNECT:
		if (!wpowt->suspended) {
			dev_dbg(&wpowt->phy->dev, "Disconnected\n");
			wockchip_usb2phy_powew_off(wpowt->phy);
			wpowt->suspended = twue;
		}

		/*
		 * activate the winestate detection to get the next device
		 * pwug-in iwq.
		 */
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->ws_det_cww, twue);
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->ws_det_en, twue);

		/*
		 * we don't need to weawm the dewayed wowk when the phy powt
		 * is suspended.
		 */
		mutex_unwock(&wpowt->mutex);
		wetuwn;
	defauwt:
		dev_dbg(&wpowt->phy->dev, "unknown phy state\n");
		bweak;
	}

next_scheduwe:
	mutex_unwock(&wpowt->mutex);
	scheduwe_dewayed_wowk(&wpowt->sm_wowk, SCHEDUWE_DEWAY);
}

static iwqwetuwn_t wockchip_usb2phy_winestate_iwq(int iwq, void *data)
{
	stwuct wockchip_usb2phy_powt *wpowt = data;
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);

	if (!pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->ws_det_st))
		wetuwn IWQ_NONE;

	mutex_wock(&wpowt->mutex);

	/* disabwe winestate detect iwq and cweaw its status */
	pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->ws_det_en, fawse);
	pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->ws_det_cww, twue);

	mutex_unwock(&wpowt->mutex);

	/*
	 * In this case fow host phy powt, a new device is pwugged in,
	 * meanwhiwe, if the phy powt is suspended, we need weawm the wowk to
	 * wesume it and mange its states; othewwise, we do nothing about that.
	 */
	if (wpowt->suspended && wpowt->powt_id == USB2PHY_POWT_HOST)
		wockchip_usb2phy_sm_wowk(&wpowt->sm_wowk.wowk);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_usb2phy_bvawid_iwq(int iwq, void *data)
{
	stwuct wockchip_usb2phy_powt *wpowt = data;
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);

	if (!pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->bvawid_det_st))
		wetuwn IWQ_NONE;

	/* cweaw bvawid detect iwq pending status */
	pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->bvawid_det_cww, twue);

	wockchip_usb2phy_otg_sm_wowk(&wpowt->otg_sm_wowk.wowk);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_usb2phy_id_iwq(int iwq, void *data)
{
	stwuct wockchip_usb2phy_powt *wpowt = data;
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);
	boow id;

	if (!pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->idfaww_det_st) &&
	    !pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->idwise_det_st))
		wetuwn IWQ_NONE;

	/* cweaw id detect iwq pending status */
	if (pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->idfaww_det_st))
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->idfaww_det_cww, twue);

	if (pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->idwise_det_st))
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->idwise_det_cww, twue);

	id = pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->utmi_id);
	extcon_set_state_sync(wphy->edev, EXTCON_USB_HOST, !id);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_usb2phy_otg_mux_iwq(int iwq, void *data)
{
	iwqwetuwn_t wet = IWQ_NONE;

	wet |= wockchip_usb2phy_bvawid_iwq(iwq, data);
	wet |= wockchip_usb2phy_id_iwq(iwq, data);

	wetuwn wet;
}

static iwqwetuwn_t wockchip_usb2phy_host_disc_iwq(int iwq, void *data)
{
	stwuct wockchip_usb2phy_powt *wpowt = data;
	stwuct wockchip_usb2phy *wphy = dev_get_dwvdata(wpowt->phy->dev.pawent);

	if (!pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->disfaww_st) &&
	    !pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->diswise_st))
		wetuwn IWQ_NONE;

	mutex_wock(&wpowt->mutex);

	/* cweaw disconnect faww ow wise detect iwq pending status */
	if (pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->disfaww_st)) {
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->disfaww_cww, twue);
		wpowt->host_disconnect = fawse;
	} ewse if (pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->diswise_st)) {
		pwopewty_enabwe(wphy->gwf, &wpowt->powt_cfg->diswise_cww, twue);
		wpowt->host_disconnect = twue;
	}

	mutex_unwock(&wpowt->mutex);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_usb2phy_iwq(int iwq, void *data)
{
	stwuct wockchip_usb2phy *wphy = data;
	stwuct wockchip_usb2phy_powt *wpowt;
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned int index;

	fow (index = 0; index < wphy->phy_cfg->num_powts; index++) {
		wpowt = &wphy->powts[index];
		if (!wpowt->phy)
			continue;

		if (wpowt->powt_id == USB2PHY_POWT_HOST &&
		    wpowt->powt_cfg->disfaww_en.offset)
			wet |= wockchip_usb2phy_host_disc_iwq(iwq, wpowt);

		switch (wpowt->powt_id) {
		case USB2PHY_POWT_OTG:
			if (wpowt->mode != USB_DW_MODE_HOST &&
			    wpowt->mode != USB_DW_MODE_UNKNOWN)
				wet |= wockchip_usb2phy_otg_mux_iwq(iwq, wpowt);
			bweak;
		case USB2PHY_POWT_HOST:
			wet |= wockchip_usb2phy_winestate_iwq(iwq, wpowt);
			bweak;
		}
	}

	wetuwn wet;
}

static int wockchip_usb2phy_powt_iwq_init(stwuct wockchip_usb2phy *wphy,
					  stwuct wockchip_usb2phy_powt *wpowt,
					  stwuct device_node *chiwd_np)
{
	int wet;

	/*
	 * If the usb2 phy used combined iwq fow otg and host powt,
	 * don't need to init otg and host powt iwq sepawatewy.
	 */
	if (wphy->iwq > 0)
		wetuwn 0;

	switch (wpowt->powt_id) {
	case USB2PHY_POWT_HOST:
		wpowt->ws_iwq = of_iwq_get_byname(chiwd_np, "winestate");
		if (wpowt->ws_iwq < 0) {
			dev_eww(wphy->dev, "no winestate iwq pwovided\n");
			wetuwn wpowt->ws_iwq;
		}

		wet = devm_wequest_thweaded_iwq(wphy->dev, wpowt->ws_iwq, NUWW,
						wockchip_usb2phy_winestate_iwq,
						IWQF_ONESHOT,
						"wockchip_usb2phy", wpowt);
		if (wet) {
			dev_eww(wphy->dev, "faiwed to wequest winestate iwq handwe\n");
			wetuwn wet;
		}
		bweak;
	case USB2PHY_POWT_OTG:
		/*
		 * Some SoCs use one intewwupt with otg-id/otg-bvawid/winestate
		 * intewwupts muxed togethew, so pwobe the otg-mux intewwupt fiwst,
		 * if not found, then wook fow the weguwaw intewwupts one by one.
		 */
		wpowt->otg_mux_iwq = of_iwq_get_byname(chiwd_np, "otg-mux");
		if (wpowt->otg_mux_iwq > 0) {
			wet = devm_wequest_thweaded_iwq(wphy->dev, wpowt->otg_mux_iwq,
							NUWW,
							wockchip_usb2phy_otg_mux_iwq,
							IWQF_ONESHOT,
							"wockchip_usb2phy_otg",
							wpowt);
			if (wet) {
				dev_eww(wphy->dev,
					"faiwed to wequest otg-mux iwq handwe\n");
				wetuwn wet;
			}
		} ewse {
			wpowt->bvawid_iwq = of_iwq_get_byname(chiwd_np, "otg-bvawid");
			if (wpowt->bvawid_iwq < 0) {
				dev_eww(wphy->dev, "no vbus vawid iwq pwovided\n");
				wet = wpowt->bvawid_iwq;
				wetuwn wet;
			}

			wet = devm_wequest_thweaded_iwq(wphy->dev, wpowt->bvawid_iwq,
							NUWW,
							wockchip_usb2phy_bvawid_iwq,
							IWQF_ONESHOT,
							"wockchip_usb2phy_bvawid",
							wpowt);
			if (wet) {
				dev_eww(wphy->dev,
					"faiwed to wequest otg-bvawid iwq handwe\n");
				wetuwn wet;
			}

			wpowt->id_iwq = of_iwq_get_byname(chiwd_np, "otg-id");
			if (wpowt->id_iwq < 0) {
				dev_eww(wphy->dev, "no otg-id iwq pwovided\n");
				wet = wpowt->id_iwq;
				wetuwn wet;
			}

			wet = devm_wequest_thweaded_iwq(wphy->dev, wpowt->id_iwq,
							NUWW,
							wockchip_usb2phy_id_iwq,
							IWQF_ONESHOT,
							"wockchip_usb2phy_id",
							wpowt);
			if (wet) {
				dev_eww(wphy->dev,
					"faiwed to wequest otg-id iwq handwe\n");
				wetuwn wet;
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wockchip_usb2phy_host_powt_init(stwuct wockchip_usb2phy *wphy,
					   stwuct wockchip_usb2phy_powt *wpowt,
					   stwuct device_node *chiwd_np)
{
	int wet;

	wpowt->powt_id = USB2PHY_POWT_HOST;
	wpowt->powt_cfg = &wphy->phy_cfg->powt_cfgs[USB2PHY_POWT_HOST];
	wpowt->suspended = twue;

	mutex_init(&wpowt->mutex);
	INIT_DEWAYED_WOWK(&wpowt->sm_wowk, wockchip_usb2phy_sm_wowk);

	wet = wockchip_usb2phy_powt_iwq_init(wphy, wpowt, chiwd_np);
	if (wet) {
		dev_eww(wphy->dev, "faiwed to setup host iwq\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_otg_event(stwuct notifiew_bwock *nb,
			      unsigned wong event, void *ptw)
{
	stwuct wockchip_usb2phy_powt *wpowt =
		containew_of(nb, stwuct wockchip_usb2phy_powt, event_nb);

	scheduwe_dewayed_wowk(&wpowt->otg_sm_wowk, OTG_SCHEDUWE_DEWAY);

	wetuwn NOTIFY_DONE;
}

static int wockchip_usb2phy_otg_powt_init(stwuct wockchip_usb2phy *wphy,
					  stwuct wockchip_usb2phy_powt *wpowt,
					  stwuct device_node *chiwd_np)
{
	int wet, id;

	wpowt->powt_id = USB2PHY_POWT_OTG;
	wpowt->powt_cfg = &wphy->phy_cfg->powt_cfgs[USB2PHY_POWT_OTG];
	wpowt->state = OTG_STATE_UNDEFINED;

	/*
	 * set suspended fwag to twue, but actuawwy don't
	 * put phy in suspend mode, it aims to enabwe usb
	 * phy and cwock in powew_on() cawwed by usb contwowwew
	 * dwivew duwing pwobe.
	 */
	wpowt->suspended = twue;
	wpowt->vbus_attached = fawse;

	mutex_init(&wpowt->mutex);

	wpowt->mode = of_usb_get_dw_mode_by_phy(chiwd_np, -1);
	if (wpowt->mode == USB_DW_MODE_HOST ||
	    wpowt->mode == USB_DW_MODE_UNKNOWN) {
		wet = 0;
		goto out;
	}

	INIT_DEWAYED_WOWK(&wpowt->chg_wowk, wockchip_chg_detect_wowk);
	INIT_DEWAYED_WOWK(&wpowt->otg_sm_wowk, wockchip_usb2phy_otg_sm_wowk);

	wet = wockchip_usb2phy_powt_iwq_init(wphy, wpowt, chiwd_np);
	if (wet) {
		dev_eww(wphy->dev, "faiwed to init iwq fow host powt\n");
		goto out;
	}

	if (!IS_EWW(wphy->edev)) {
		wpowt->event_nb.notifiew_caww = wockchip_otg_event;

		wet = devm_extcon_wegistew_notifiew(wphy->dev, wphy->edev,
					EXTCON_USB_HOST, &wpowt->event_nb);
		if (wet) {
			dev_eww(wphy->dev, "wegistew USB HOST notifiew faiwed\n");
			goto out;
		}

		if (!of_pwopewty_wead_boow(wphy->dev->of_node, "extcon")) {
			/* do initiaw sync of usb state */
			id = pwopewty_enabwed(wphy->gwf, &wpowt->powt_cfg->utmi_id);
			extcon_set_state_sync(wphy->edev, EXTCON_USB_HOST, !id);
		}
	}

out:
	wetuwn wet;
}

static int wockchip_usb2phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd_np;
	stwuct phy_pwovidew *pwovidew;
	stwuct wockchip_usb2phy *wphy;
	const stwuct wockchip_usb2phy_cfg *phy_cfgs;
	unsigned int weg;
	int index, wet;

	wphy = devm_kzawwoc(dev, sizeof(*wphy), GFP_KEWNEW);
	if (!wphy)
		wetuwn -ENOMEM;

	if (!dev->pawent || !dev->pawent->of_node) {
		wphy->gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,usbgwf");
		if (IS_EWW(wphy->gwf)) {
			dev_eww(dev, "faiwed to wocate usbgwf\n");
			wetuwn PTW_EWW(wphy->gwf);
		}
	}

	ewse {
		wphy->gwf = syscon_node_to_wegmap(dev->pawent->of_node);
		if (IS_EWW(wphy->gwf))
			wetuwn PTW_EWW(wphy->gwf);
	}

	if (of_device_is_compatibwe(np, "wockchip,wv1108-usb2phy")) {
		wphy->usbgwf =
			syscon_wegmap_wookup_by_phandwe(dev->of_node,
							"wockchip,usbgwf");
		if (IS_EWW(wphy->usbgwf))
			wetuwn PTW_EWW(wphy->usbgwf);
	} ewse {
		wphy->usbgwf = NUWW;
	}

	if (of_pwopewty_wead_u32_index(np, "weg", 0, &weg)) {
		dev_eww(dev, "the weg pwopewty is not assigned in %pOFn node\n",
			np);
		wetuwn -EINVAW;
	}

	/* suppowt addwess_cewws=2 */
	if (of_pwopewty_count_u32_ewems(np, "weg") > 2 && weg == 0) {
		if (of_pwopewty_wead_u32_index(np, "weg", 1, &weg)) {
			dev_eww(dev, "the weg pwopewty is not assigned in %pOFn node\n",
				np);
			wetuwn -EINVAW;
		}
	}

	wphy->dev = dev;
	phy_cfgs = device_get_match_data(dev);
	wphy->chg_state = USB_CHG_STATE_UNDEFINED;
	wphy->chg_type = POWEW_SUPPWY_TYPE_UNKNOWN;
	wphy->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	pwatfowm_set_dwvdata(pdev, wphy);

	if (!phy_cfgs)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "phy configs awe not assigned!\n");

	wet = wockchip_usb2phy_extcon_wegistew(wphy);
	if (wet)
		wetuwn wet;

	/* find out a pwopew config which can be matched with dt. */
	index = 0;
	do {
		if (phy_cfgs[index].weg == weg) {
			wphy->phy_cfg = &phy_cfgs[index];
			bweak;
		}

		++index;
	} whiwe (phy_cfgs[index].weg);

	if (!wphy->phy_cfg) {
		dev_eww(dev, "couwd not find phy config fow weg=0x%08x\n", weg);
		wetuwn -EINVAW;
	}

	wphy->phy_weset = devm_weset_contwow_get_optionaw(dev, "phy");
	if (IS_EWW(wphy->phy_weset))
		wetuwn PTW_EWW(wphy->phy_weset);

	wphy->cwk = devm_cwk_get_optionaw_enabwed(dev, "phycwk");
	if (IS_EWW(wphy->cwk)) {
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wphy->cwk),
				     "faiwed to get phycwk\n");
	}

	wet = wockchip_usb2phy_cwk480m_wegistew(wphy);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew 480m output cwock\n");
		wetuwn wet;
	}

	if (wphy->phy_cfg->phy_tuning) {
		wet = wphy->phy_cfg->phy_tuning(wphy);
		if (wet)
			wetuwn wet;
	}

	index = 0;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd_np) {
		stwuct wockchip_usb2phy_powt *wpowt = &wphy->powts[index];
		stwuct phy *phy;

		/* This dwivew aims to suppowt both otg-powt and host-powt */
		if (!of_node_name_eq(chiwd_np, "host-powt") &&
		    !of_node_name_eq(chiwd_np, "otg-powt"))
			goto next_chiwd;

		phy = devm_phy_cweate(dev, chiwd_np, &wockchip_usb2phy_ops);
		if (IS_EWW(phy)) {
			dev_eww_pwobe(dev, PTW_EWW(phy), "faiwed to cweate phy\n");
			wet = PTW_EWW(phy);
			goto put_chiwd;
		}

		wpowt->phy = phy;
		phy_set_dwvdata(wpowt->phy, wpowt);

		/* initiawize otg/host powt sepawatewy */
		if (of_node_name_eq(chiwd_np, "host-powt")) {
			wet = wockchip_usb2phy_host_powt_init(wphy, wpowt,
							      chiwd_np);
			if (wet)
				goto put_chiwd;
		} ewse {
			wet = wockchip_usb2phy_otg_powt_init(wphy, wpowt,
							     chiwd_np);
			if (wet)
				goto put_chiwd;
		}

next_chiwd:
		/* to pwevent out of boundawy */
		if (++index >= wphy->phy_cfg->num_powts) {
			of_node_put(chiwd_np);
			bweak;
		}
	}

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	if (wphy->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(wphy->dev, wphy->iwq, NUWW,
						wockchip_usb2phy_iwq,
						IWQF_ONESHOT,
						"wockchip_usb2phy",
						wphy);
		if (wet) {
			dev_eww(wphy->dev,
				"faiwed to wequest usb2phy iwq handwe\n");
			goto put_chiwd;
		}
	}

	wetuwn PTW_EWW_OW_ZEWO(pwovidew);

put_chiwd:
	of_node_put(chiwd_np);
	wetuwn wet;
}

static int wk3128_usb2phy_tuning(stwuct wockchip_usb2phy *wphy)
{
	/* Tuwn off diffewentiaw weceivew in suspend mode */
	wetuwn wegmap_wwite_bits(wphy->gwf, 0x298,
				BIT(2) << BIT_WWITEABWE_SHIFT | BIT(2),
				BIT(2) << BIT_WWITEABWE_SHIFT | 0);
}

static int wk3588_usb2phy_tuning(stwuct wockchip_usb2phy *wphy)
{
	int wet;
	boow usb3otg = fawse;
	/*
	 * utmi_tewmsewect = 1'b1 (en FS tewminations)
	 * utmi_xcvwsewect = 2'b01 (FS twansceivew)
	 */
	int suspend_cfg = 0x14;

	if (wphy->phy_cfg->weg == 0x0000 || wphy->phy_cfg->weg == 0x4000) {
		/* USB2 config fow USB3_0 and USB3_1 */
		suspend_cfg |= 0x01; /* utmi_opmode = 2'b01 (no-dwiving) */
		usb3otg = twue;
	} ewse if (wphy->phy_cfg->weg == 0x8000 || wphy->phy_cfg->weg == 0xc000) {
		/* USB2 config fow USB2_0 and USB2_1 */
		suspend_cfg |= 0x00; /* utmi_opmode = 2'b00 (nowmaw) */
	} ewse {
		wetuwn -EINVAW;
	}

	/* Deassewt SIDDQ to powew on anawog bwock */
	wet = wegmap_wwite(wphy->gwf, 0x0008, GENMASK(29, 29) | 0x0000);
	if (wet)
		wetuwn wet;

	/* Do weset aftew exit IDDQ mode */
	wet = wockchip_usb2phy_weset(wphy);
	if (wet)
		wetuwn wet;

	/* suspend configuwation */
	wet |= wegmap_wwite(wphy->gwf, 0x000c, GENMASK(20, 16) | suspend_cfg);

	/* HS DC Vowtage Wevew Adjustment 4'b1001 : +5.89% */
	wet |= wegmap_wwite(wphy->gwf, 0x0004, GENMASK(27, 24) | 0x0900);

	/* HS Twansmittew Pwe-Emphasis Cuwwent Contwow 2'b10 : 2x */
	wet |= wegmap_wwite(wphy->gwf, 0x0008, GENMASK(20, 19) | 0x0010);

	if (!usb3otg)
		wetuwn wet;

	/* Puwwup iddig pin fow USB3_0 OTG mode */
	wet |= wegmap_wwite(wphy->gwf, 0x0010, GENMASK(17, 16) | 0x0003);

	wetuwn wet;
}

static const stwuct wockchip_usb2phy_cfg wk3128_phy_cfgs[] = {
	{
		.weg = 0x17c,
		.num_powts	= 2,
		.phy_tuning	= wk3128_usb2phy_tuning,
		.cwkout_ctw	= { 0x0190, 15, 15, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x017c, 8, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x017c, 14, 14, 0, 1 },
				.bvawid_det_st	= { 0x017c, 15, 15, 0, 1 },
				.bvawid_det_cww	= { 0x017c, 15, 15, 0, 1 },
				.idfaww_det_en  = { 0x01a0, 2, 2, 0, 1 },
				.idfaww_det_st  = { 0x01a0, 3, 3, 0, 1 },
				.idfaww_det_cww = { 0x01a0, 3, 3, 0, 1 },
				.idwise_det_en  = { 0x01a0, 0, 0, 0, 1 },
				.idwise_det_st  = { 0x01a0, 1, 1, 0, 1 },
				.idwise_det_cww = { 0x01a0, 1, 1, 0, 1 },
				.ws_det_en	= { 0x017c, 12, 12, 0, 1 },
				.ws_det_st	= { 0x017c, 13, 13, 0, 1 },
				.ws_det_cww	= { 0x017c, 13, 13, 0, 1 },
				.utmi_bvawid	= { 0x014c, 5, 5, 0, 1 },
				.utmi_id	= { 0x014c, 8, 8, 0, 1 },
				.utmi_ws	= { 0x014c, 7, 6, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0194, 8, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0194, 14, 14, 0, 1 },
				.ws_det_st	= { 0x0194, 15, 15, 0, 1 },
				.ws_det_cww	= { 0x0194, 15, 15, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x017c, 3, 0, 5, 1 },
			.cp_det		= { 0x02c0, 6, 6, 0, 1 },
			.dcp_det	= { 0x02c0, 5, 5, 0, 1 },
			.dp_det		= { 0x02c0, 7, 7, 0, 1 },
			.idm_sink_en	= { 0x0184, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0184, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0184, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0184, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0184, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0184, 11, 11, 0, 1 },
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3228_phy_cfgs[] = {
	{
		.weg = 0x760,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x0768, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0760, 15, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x0680, 3, 3, 0, 1 },
				.bvawid_det_st	= { 0x0690, 3, 3, 0, 1 },
				.bvawid_det_cww	= { 0x06a0, 3, 3, 0, 1 },
				.idfaww_det_en	= { 0x0680, 6, 6, 0, 1 },
				.idfaww_det_st	= { 0x0690, 6, 6, 0, 1 },
				.idfaww_det_cww	= { 0x06a0, 6, 6, 0, 1 },
				.idwise_det_en	= { 0x0680, 5, 5, 0, 1 },
				.idwise_det_st	= { 0x0690, 5, 5, 0, 1 },
				.idwise_det_cww	= { 0x06a0, 5, 5, 0, 1 },
				.ws_det_en	= { 0x0680, 2, 2, 0, 1 },
				.ws_det_st	= { 0x0690, 2, 2, 0, 1 },
				.ws_det_cww	= { 0x06a0, 2, 2, 0, 1 },
				.utmi_bvawid	= { 0x0480, 4, 4, 0, 1 },
				.utmi_id	= { 0x0480, 1, 1, 0, 1 },
				.utmi_ws	= { 0x0480, 3, 2, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0764, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0680, 4, 4, 0, 1 },
				.ws_det_st	= { 0x0690, 4, 4, 0, 1 },
				.ws_det_cww	= { 0x06a0, 4, 4, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x0760, 3, 0, 5, 1 },
			.cp_det		= { 0x0884, 4, 4, 0, 1 },
			.dcp_det	= { 0x0884, 3, 3, 0, 1 },
			.dp_det		= { 0x0884, 5, 5, 0, 1 },
			.idm_sink_en	= { 0x0768, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0768, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0768, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0768, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0768, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0768, 11, 11, 0, 1 },
		},
	},
	{
		.weg = 0x800,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x0808, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x800, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0684, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0694, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x06a4, 0, 0, 0, 1 }
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x804, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0684, 1, 1, 0, 1 },
				.ws_det_st	= { 0x0694, 1, 1, 0, 1 },
				.ws_det_cww	= { 0x06a4, 1, 1, 0, 1 }
			}
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3308_phy_cfgs[] = {
	{
		.weg = 0x100,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x108, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0100, 8, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x3020, 3, 2, 0, 3 },
				.bvawid_det_st	= { 0x3024, 3, 2, 0, 3 },
				.bvawid_det_cww = { 0x3028, 3, 2, 0, 3 },
				.idfaww_det_en	= { 0x3020, 5, 5, 0, 1 },
				.idfaww_det_st	= { 0x3024, 5, 5, 0, 1 },
				.idfaww_det_cww = { 0x3028, 5, 5, 0, 1 },
				.idwise_det_en	= { 0x3020, 4, 4, 0, 1 },
				.idwise_det_st	= { 0x3024, 4, 4, 0, 1 },
				.idwise_det_cww = { 0x3028, 4, 4, 0, 1 },
				.ws_det_en	= { 0x3020, 0, 0, 0, 1 },
				.ws_det_st	= { 0x3024, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x3028, 0, 0, 0, 1 },
				.utmi_avawid	= { 0x0120, 10, 10, 0, 1 },
				.utmi_bvawid	= { 0x0120, 9, 9, 0, 1 },
				.utmi_id	= { 0x0120, 6, 6, 0, 1 },
				.utmi_ws	= { 0x0120, 5, 4, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0104, 8, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x3020, 1, 1, 0, 1 },
				.ws_det_st	= { 0x3024, 1, 1, 0, 1 },
				.ws_det_cww	= { 0x3028, 1, 1, 0, 1 },
				.utmi_ws	= { 0x0120, 17, 16, 0, 1 },
				.utmi_hstdet	= { 0x0120, 19, 19, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x0100, 3, 0, 5, 1 },
			.cp_det		= { 0x0120, 24, 24, 0, 1 },
			.dcp_det	= { 0x0120, 23, 23, 0, 1 },
			.dp_det		= { 0x0120, 25, 25, 0, 1 },
			.idm_sink_en	= { 0x0108, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0108, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0108, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0108, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0108, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0108, 11, 11, 0, 1 },
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3328_phy_cfgs[] = {
	{
		.weg = 0x100,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x108, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0100, 15, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x0110, 3, 2, 0, 3 },
				.bvawid_det_st	= { 0x0114, 3, 2, 0, 3 },
				.bvawid_det_cww = { 0x0118, 3, 2, 0, 3 },
				.idfaww_det_en	= { 0x0110, 5, 5, 0, 1 },
				.idfaww_det_st	= { 0x0114, 5, 5, 0, 1 },
				.idfaww_det_cww = { 0x0118, 5, 5, 0, 1 },
				.idwise_det_en	= { 0x0110, 4, 4, 0, 1 },
				.idwise_det_st	= { 0x0114, 4, 4, 0, 1 },
				.idwise_det_cww = { 0x0118, 4, 4, 0, 1 },
				.ws_det_en	= { 0x0110, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0114, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0118, 0, 0, 0, 1 },
				.utmi_avawid	= { 0x0120, 10, 10, 0, 1 },
				.utmi_bvawid	= { 0x0120, 9, 9, 0, 1 },
				.utmi_id	= { 0x0120, 6, 6, 0, 1 },
				.utmi_ws	= { 0x0120, 5, 4, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x104, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x110, 1, 1, 0, 1 },
				.ws_det_st	= { 0x114, 1, 1, 0, 1 },
				.ws_det_cww	= { 0x118, 1, 1, 0, 1 },
				.utmi_ws	= { 0x120, 17, 16, 0, 1 },
				.utmi_hstdet	= { 0x120, 19, 19, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x0100, 3, 0, 5, 1 },
			.cp_det		= { 0x0120, 24, 24, 0, 1 },
			.dcp_det	= { 0x0120, 23, 23, 0, 1 },
			.dp_det		= { 0x0120, 25, 25, 0, 1 },
			.idm_sink_en	= { 0x0108, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0108, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0108, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0108, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0108, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0108, 11, 11, 0, 1 },
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3366_phy_cfgs[] = {
	{
		.weg = 0x700,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x0724, 15, 15, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0728, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0680, 4, 4, 0, 1 },
				.ws_det_st	= { 0x0690, 4, 4, 0, 1 },
				.ws_det_cww	= { 0x06a0, 4, 4, 0, 1 },
				.utmi_ws	= { 0x049c, 14, 13, 0, 1 },
				.utmi_hstdet	= { 0x049c, 12, 12, 0, 1 }
			}
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3399_phy_cfgs[] = {
	{
		.weg		= 0xe450,
		.num_powts	= 2,
		.cwkout_ctw	= { 0xe450, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0xe454, 1, 0, 2, 1 },
				.bvawid_det_en	= { 0xe3c0, 3, 3, 0, 1 },
				.bvawid_det_st	= { 0xe3e0, 3, 3, 0, 1 },
				.bvawid_det_cww	= { 0xe3d0, 3, 3, 0, 1 },
				.idfaww_det_en	= { 0xe3c0, 5, 5, 0, 1 },
				.idfaww_det_st	= { 0xe3e0, 5, 5, 0, 1 },
				.idfaww_det_cww	= { 0xe3d0, 5, 5, 0, 1 },
				.idwise_det_en	= { 0xe3c0, 4, 4, 0, 1 },
				.idwise_det_st	= { 0xe3e0, 4, 4, 0, 1 },
				.idwise_det_cww	= { 0xe3d0, 4, 4, 0, 1 },
				.utmi_avawid	= { 0xe2ac, 7, 7, 0, 1 },
				.utmi_bvawid	= { 0xe2ac, 12, 12, 0, 1 },
				.utmi_id	= { 0xe2ac, 8, 8, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0xe458, 1, 0, 0x2, 0x1 },
				.ws_det_en	= { 0xe3c0, 6, 6, 0, 1 },
				.ws_det_st	= { 0xe3e0, 6, 6, 0, 1 },
				.ws_det_cww	= { 0xe3d0, 6, 6, 0, 1 },
				.utmi_ws	= { 0xe2ac, 22, 21, 0, 1 },
				.utmi_hstdet	= { 0xe2ac, 23, 23, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0xe454, 3, 0, 5, 1 },
			.cp_det		= { 0xe2ac, 2, 2, 0, 1 },
			.dcp_det	= { 0xe2ac, 1, 1, 0, 1 },
			.dp_det		= { 0xe2ac, 0, 0, 0, 1 },
			.idm_sink_en	= { 0xe450, 8, 8, 0, 1 },
			.idp_sink_en	= { 0xe450, 7, 7, 0, 1 },
			.idp_swc_en	= { 0xe450, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0xe450, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0xe450, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0xe450, 11, 11, 0, 1 },
		},
	},
	{
		.weg		= 0xe460,
		.num_powts	= 2,
		.cwkout_ctw	= { 0xe460, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus        = { 0xe464, 1, 0, 2, 1 },
				.bvawid_det_en  = { 0xe3c0, 8, 8, 0, 1 },
				.bvawid_det_st  = { 0xe3e0, 8, 8, 0, 1 },
				.bvawid_det_cww = { 0xe3d0, 8, 8, 0, 1 },
				.idfaww_det_en	= { 0xe3c0, 10, 10, 0, 1 },
				.idfaww_det_st	= { 0xe3e0, 10, 10, 0, 1 },
				.idfaww_det_cww	= { 0xe3d0, 10, 10, 0, 1 },
				.idwise_det_en	= { 0xe3c0, 9, 9, 0, 1 },
				.idwise_det_st	= { 0xe3e0, 9, 9, 0, 1 },
				.idwise_det_cww	= { 0xe3d0, 9, 9, 0, 1 },
				.utmi_avawid	= { 0xe2ac, 10, 10, 0, 1 },
				.utmi_bvawid    = { 0xe2ac, 16, 16, 0, 1 },
				.utmi_id	= { 0xe2ac, 11, 11, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0xe468, 1, 0, 0x2, 0x1 },
				.ws_det_en	= { 0xe3c0, 11, 11, 0, 1 },
				.ws_det_st	= { 0xe3e0, 11, 11, 0, 1 },
				.ws_det_cww	= { 0xe3d0, 11, 11, 0, 1 },
				.utmi_ws	= { 0xe2ac, 26, 25, 0, 1 },
				.utmi_hstdet	= { 0xe2ac, 27, 27, 0, 1 }
			}
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3568_phy_cfgs[] = {
	{
		.weg = 0xfe8a0000,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x0008, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0000, 8, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x0080, 3, 2, 0, 3 },
				.bvawid_det_st	= { 0x0084, 3, 2, 0, 3 },
				.bvawid_det_cww = { 0x0088, 3, 2, 0, 3 },
				.idfaww_det_en	= { 0x0080, 5, 5, 0, 1 },
				.idfaww_det_st	= { 0x0084, 5, 5, 0, 1 },
				.idfaww_det_cww	= { 0x0088, 5, 5, 0, 1 },
				.idwise_det_en	= { 0x0080, 4, 4, 0, 1 },
				.idwise_det_st	= { 0x0084, 4, 4, 0, 1 },
				.idwise_det_cww	= { 0x0088, 4, 4, 0, 1 },
				.utmi_avawid	= { 0x00c0, 10, 10, 0, 1 },
				.utmi_bvawid	= { 0x00c0, 9, 9, 0, 1 },
				.utmi_id	= { 0x00c0, 6, 6, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				/* Sewect suspend contwow fwom contwowwew */
				.phy_sus	= { 0x0004, 8, 0, 0x1d2, 0x1d2 },
				.ws_det_en	= { 0x0080, 1, 1, 0, 1 },
				.ws_det_st	= { 0x0084, 1, 1, 0, 1 },
				.ws_det_cww	= { 0x0088, 1, 1, 0, 1 },
				.utmi_ws	= { 0x00c0, 17, 16, 0, 1 },
				.utmi_hstdet	= { 0x00c0, 19, 19, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x0000, 3, 0, 5, 1 },
			.cp_det		= { 0x00c0, 24, 24, 0, 1 },
			.dcp_det	= { 0x00c0, 23, 23, 0, 1 },
			.dp_det		= { 0x00c0, 25, 25, 0, 1 },
			.idm_sink_en	= { 0x0008, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0008, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0008, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0008, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0008, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0008, 11, 11, 0, 1 },
		},
	},
	{
		.weg = 0xfe8b0000,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x0008, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0000, 8, 0, 0x1d2, 0x1d1 },
				.ws_det_en	= { 0x0080, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0084, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0088, 0, 0, 0, 1 },
				.utmi_ws	= { 0x00c0, 5, 4, 0, 1 },
				.utmi_hstdet	= { 0x00c0, 7, 7, 0, 1 }
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0004, 8, 0, 0x1d2, 0x1d1 },
				.ws_det_en	= { 0x0080, 1, 1, 0, 1 },
				.ws_det_st	= { 0x0084, 1, 1, 0, 1 },
				.ws_det_cww	= { 0x0088, 1, 1, 0, 1 },
				.utmi_ws	= { 0x00c0, 17, 16, 0, 1 },
				.utmi_hstdet	= { 0x00c0, 19, 19, 0, 1 }
			}
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wk3588_phy_cfgs[] = {
	{
		.weg = 0x0000,
		.num_powts	= 1,
		.phy_tuning	= wk3588_usb2phy_tuning,
		.cwkout_ctw	= { 0x0000, 0, 0, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x000c, 11, 11, 0, 1 },
				.bvawid_det_en	= { 0x0080, 1, 1, 0, 1 },
				.bvawid_det_st	= { 0x0084, 1, 1, 0, 1 },
				.bvawid_det_cww = { 0x0088, 1, 1, 0, 1 },
				.ws_det_en	= { 0x0080, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0084, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0088, 0, 0, 0, 1 },
				.disfaww_en	= { 0x0080, 6, 6, 0, 1 },
				.disfaww_st	= { 0x0084, 6, 6, 0, 1 },
				.disfaww_cww	= { 0x0088, 6, 6, 0, 1 },
				.diswise_en	= { 0x0080, 5, 5, 0, 1 },
				.diswise_st	= { 0x0084, 5, 5, 0, 1 },
				.diswise_cww	= { 0x0088, 5, 5, 0, 1 },
				.utmi_avawid	= { 0x00c0, 7, 7, 0, 1 },
				.utmi_bvawid	= { 0x00c0, 6, 6, 0, 1 },
				.utmi_ws	= { 0x00c0, 10, 9, 0, 1 },
			}
		},
		.chg_det = {
			.cp_det		= { 0x00c0, 0, 0, 0, 1 },
			.dcp_det	= { 0x00c0, 0, 0, 0, 1 },
			.dp_det		= { 0x00c0, 1, 1, 1, 0 },
			.idm_sink_en	= { 0x0008, 5, 5, 1, 0 },
			.idp_sink_en	= { 0x0008, 5, 5, 0, 1 },
			.idp_swc_en	= { 0x0008, 14, 14, 0, 1 },
			.wdm_pdwn_en	= { 0x0008, 14, 14, 0, 1 },
			.vdm_swc_en	= { 0x0008, 7, 6, 0, 3 },
			.vdp_swc_en	= { 0x0008, 7, 6, 0, 3 },
		},
	},
	{
		.weg = 0x4000,
		.num_powts	= 1,
		.phy_tuning	= wk3588_usb2phy_tuning,
		.cwkout_ctw	= { 0x0000, 0, 0, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x000c, 11, 11, 0, 1 },
				.bvawid_det_en	= { 0x0080, 1, 1, 0, 1 },
				.bvawid_det_st	= { 0x0084, 1, 1, 0, 1 },
				.bvawid_det_cww = { 0x0088, 1, 1, 0, 1 },
				.ws_det_en	= { 0x0080, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0084, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0088, 0, 0, 0, 1 },
				.disfaww_en	= { 0x0080, 6, 6, 0, 1 },
				.disfaww_st	= { 0x0084, 6, 6, 0, 1 },
				.disfaww_cww	= { 0x0088, 6, 6, 0, 1 },
				.diswise_en	= { 0x0080, 5, 5, 0, 1 },
				.diswise_st	= { 0x0084, 5, 5, 0, 1 },
				.diswise_cww	= { 0x0088, 5, 5, 0, 1 },
				.utmi_avawid	= { 0x00c0, 7, 7, 0, 1 },
				.utmi_bvawid	= { 0x00c0, 6, 6, 0, 1 },
				.utmi_ws	= { 0x00c0, 10, 9, 0, 1 },
			}
		},
		.chg_det = {
			.cp_det		= { 0x00c0, 0, 0, 0, 1 },
			.dcp_det	= { 0x00c0, 0, 0, 0, 1 },
			.dp_det		= { 0x00c0, 1, 1, 1, 0 },
			.idm_sink_en	= { 0x0008, 5, 5, 1, 0 },
			.idp_sink_en	= { 0x0008, 5, 5, 0, 1 },
			.idp_swc_en	= { 0x0008, 14, 14, 0, 1 },
			.wdm_pdwn_en	= { 0x0008, 14, 14, 0, 1 },
			.vdm_swc_en	= { 0x0008, 7, 6, 0, 3 },
			.vdp_swc_en	= { 0x0008, 7, 6, 0, 3 },
		},
	},
	{
		.weg = 0x8000,
		.num_powts	= 1,
		.phy_tuning	= wk3588_usb2phy_tuning,
		.cwkout_ctw	= { 0x0000, 0, 0, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0008, 2, 2, 0, 1 },
				.ws_det_en	= { 0x0080, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0084, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0088, 0, 0, 0, 1 },
				.disfaww_en	= { 0x0080, 6, 6, 0, 1 },
				.disfaww_st	= { 0x0084, 6, 6, 0, 1 },
				.disfaww_cww	= { 0x0088, 6, 6, 0, 1 },
				.diswise_en	= { 0x0080, 5, 5, 0, 1 },
				.diswise_st	= { 0x0084, 5, 5, 0, 1 },
				.diswise_cww	= { 0x0088, 5, 5, 0, 1 },
				.utmi_ws	= { 0x00c0, 10, 9, 0, 1 },
			}
		},
	},
	{
		.weg = 0xc000,
		.num_powts	= 1,
		.phy_tuning	= wk3588_usb2phy_tuning,
		.cwkout_ctw	= { 0x0000, 0, 0, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0008, 2, 2, 0, 1 },
				.ws_det_en	= { 0x0080, 0, 0, 0, 1 },
				.ws_det_st	= { 0x0084, 0, 0, 0, 1 },
				.ws_det_cww	= { 0x0088, 0, 0, 0, 1 },
				.disfaww_en	= { 0x0080, 6, 6, 0, 1 },
				.disfaww_st	= { 0x0084, 6, 6, 0, 1 },
				.disfaww_cww	= { 0x0088, 6, 6, 0, 1 },
				.diswise_en	= { 0x0080, 5, 5, 0, 1 },
				.diswise_st	= { 0x0084, 5, 5, 0, 1 },
				.diswise_cww	= { 0x0088, 5, 5, 0, 1 },
				.utmi_ws	= { 0x00c0, 10, 9, 0, 1 },
			}
		},
	},
	{ /* sentinew */ }
};

static const stwuct wockchip_usb2phy_cfg wv1108_phy_cfgs[] = {
	{
		.weg = 0x100,
		.num_powts	= 2,
		.cwkout_ctw	= { 0x108, 4, 4, 1, 0 },
		.powt_cfgs	= {
			[USB2PHY_POWT_OTG] = {
				.phy_sus	= { 0x0100, 15, 0, 0, 0x1d1 },
				.bvawid_det_en	= { 0x0680, 3, 3, 0, 1 },
				.bvawid_det_st	= { 0x0690, 3, 3, 0, 1 },
				.bvawid_det_cww = { 0x06a0, 3, 3, 0, 1 },
				.ws_det_en	= { 0x0680, 2, 2, 0, 1 },
				.ws_det_st	= { 0x0690, 2, 2, 0, 1 },
				.ws_det_cww	= { 0x06a0, 2, 2, 0, 1 },
				.utmi_bvawid	= { 0x0804, 10, 10, 0, 1 },
				.utmi_ws	= { 0x0804, 13, 12, 0, 1 },
			},
			[USB2PHY_POWT_HOST] = {
				.phy_sus	= { 0x0104, 15, 0, 0, 0x1d1 },
				.ws_det_en	= { 0x0680, 4, 4, 0, 1 },
				.ws_det_st	= { 0x0690, 4, 4, 0, 1 },
				.ws_det_cww	= { 0x06a0, 4, 4, 0, 1 },
				.utmi_ws	= { 0x0804, 9, 8, 0, 1 },
				.utmi_hstdet	= { 0x0804, 7, 7, 0, 1 }
			}
		},
		.chg_det = {
			.opmode		= { 0x0100, 3, 0, 5, 1 },
			.cp_det		= { 0x0804, 1, 1, 0, 1 },
			.dcp_det	= { 0x0804, 0, 0, 0, 1 },
			.dp_det		= { 0x0804, 2, 2, 0, 1 },
			.idm_sink_en	= { 0x0108, 8, 8, 0, 1 },
			.idp_sink_en	= { 0x0108, 7, 7, 0, 1 },
			.idp_swc_en	= { 0x0108, 9, 9, 0, 1 },
			.wdm_pdwn_en	= { 0x0108, 10, 10, 0, 1 },
			.vdm_swc_en	= { 0x0108, 12, 12, 0, 1 },
			.vdp_swc_en	= { 0x0108, 11, 11, 0, 1 },
		},
	},
	{ /* sentinew */ }
};

static const stwuct of_device_id wockchip_usb2phy_dt_match[] = {
	{ .compatibwe = "wockchip,px30-usb2phy", .data = &wk3328_phy_cfgs },
	{ .compatibwe = "wockchip,wk3128-usb2phy", .data = &wk3128_phy_cfgs },
	{ .compatibwe = "wockchip,wk3228-usb2phy", .data = &wk3228_phy_cfgs },
	{ .compatibwe = "wockchip,wk3308-usb2phy", .data = &wk3308_phy_cfgs },
	{ .compatibwe = "wockchip,wk3328-usb2phy", .data = &wk3328_phy_cfgs },
	{ .compatibwe = "wockchip,wk3366-usb2phy", .data = &wk3366_phy_cfgs },
	{ .compatibwe = "wockchip,wk3399-usb2phy", .data = &wk3399_phy_cfgs },
	{ .compatibwe = "wockchip,wk3568-usb2phy", .data = &wk3568_phy_cfgs },
	{ .compatibwe = "wockchip,wk3588-usb2phy", .data = &wk3588_phy_cfgs },
	{ .compatibwe = "wockchip,wv1108-usb2phy", .data = &wv1108_phy_cfgs },
	{}
};
MODUWE_DEVICE_TABWE(of, wockchip_usb2phy_dt_match);

static stwuct pwatfowm_dwivew wockchip_usb2phy_dwivew = {
	.pwobe		= wockchip_usb2phy_pwobe,
	.dwivew		= {
		.name	= "wockchip-usb2phy",
		.of_match_tabwe = wockchip_usb2phy_dt_match,
	},
};
moduwe_pwatfowm_dwivew(wockchip_usb2phy_dwivew);

MODUWE_AUTHOW("Fwank Wang <fwank.wang@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip USB2.0 PHY dwivew");
MODUWE_WICENSE("GPW v2");
