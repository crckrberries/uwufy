// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Gwue fow Amwogic G12A SoCs
 *
 * Copywight (c) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

/*
 * The USB is owganized with a gwue awound the DWC3 Contwowwew IP as :
 * - Contwow wegistews fow each USB2 Powts
 * - Contwow wegistews fow the USB PHY wayew
 * - SupewSpeed PHY can be enabwed onwy if powt is used
 * - Dynamic OTG switching with ID change intewwupt
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/weset.h>
#incwude <winux/phy/phy.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/weguwatow/consumew.h>

/* USB2 Powts Contwow Wegistews, offsets awe pew-powt */

#define U2P_WEG_SIZE						0x20

#define U2P_W0							0x0
	#define U2P_W0_HOST_DEVICE				BIT(0)
	#define U2P_W0_POWEW_OK					BIT(1)
	#define U2P_W0_HAST_MODE				BIT(2)
	#define U2P_W0_POWEW_ON_WESET				BIT(3)
	#define U2P_W0_ID_PUWWUP				BIT(4)
	#define U2P_W0_DWV_VBUS					BIT(5)

#define U2P_W1							0x4
	#define U2P_W1_PHY_WEADY				BIT(0)
	#define U2P_W1_ID_DIG					BIT(1)
	#define U2P_W1_OTG_SESSION_VAWID			BIT(2)
	#define U2P_W1_VBUS_VAWID				BIT(3)

/* USB Gwue Contwow Wegistews */

#define G12A_GWUE_OFFSET					0x80

#define USB_W0							0x00
	#define USB_W0_P30_WANE0_TX2WX_WOOPBACK			BIT(17)
	#define USB_W0_P30_WANE0_EXT_PCWK_WEQ			BIT(18)
	#define USB_W0_P30_PCS_WX_WOS_MASK_VAW_MASK		GENMASK(28, 19)
	#define USB_W0_U2D_SS_SCAWEDOWN_MODE_MASK		GENMASK(30, 29)
	#define USB_W0_U2D_ACT					BIT(31)

#define USB_W1							0x04
	#define USB_W1_U3H_BIGENDIAN_GS				BIT(0)
	#define USB_W1_U3H_PME_ENABWE				BIT(1)
	#define USB_W1_U3H_HUB_POWT_OVEWCUWWENT_MASK		GENMASK(4, 2)
	#define USB_W1_U3H_HUB_POWT_PEWM_ATTACH_MASK		GENMASK(9, 7)
	#define USB_W1_U3H_HOST_U2_POWT_DISABWE_MASK		GENMASK(13, 12)
	#define USB_W1_U3H_HOST_U3_POWT_DISABWE			BIT(16)
	#define USB_W1_U3H_HOST_POWT_POWEW_CONTWOW_PWESENT	BIT(17)
	#define USB_W1_U3H_HOST_MSI_ENABWE			BIT(18)
	#define USB_W1_U3H_FWADJ_30MHZ_WEG_MASK			GENMASK(24, 19)
	#define USB_W1_P30_PCS_TX_SWING_FUWW_MASK		GENMASK(31, 25)

#define USB_W2							0x08
	#define USB_W2_P30_PCS_TX_DEEMPH_3P5DB_MASK		GENMASK(25, 20)
	#define USB_W2_P30_PCS_TX_DEEMPH_6DB_MASK		GENMASK(31, 26)

#define USB_W3							0x0c
	#define USB_W3_P30_SSC_ENABWE				BIT(0)
	#define USB_W3_P30_SSC_WANGE_MASK			GENMASK(3, 1)
	#define USB_W3_P30_SSC_WEF_CWK_SEW_MASK			GENMASK(12, 4)
	#define USB_W3_P30_WEF_SSP_EN				BIT(13)

#define USB_W4							0x10
	#define USB_W4_P21_POWT_WESET_0				BIT(0)
	#define USB_W4_P21_SWEEP_M0				BIT(1)
	#define USB_W4_MEM_PD_MASK				GENMASK(3, 2)
	#define USB_W4_P21_ONWY					BIT(4)

#define USB_W5							0x14
	#define USB_W5_ID_DIG_SYNC				BIT(0)
	#define USB_W5_ID_DIG_WEG				BIT(1)
	#define USB_W5_ID_DIG_CFG_MASK				GENMASK(3, 2)
	#define USB_W5_ID_DIG_EN_0				BIT(4)
	#define USB_W5_ID_DIG_EN_1				BIT(5)
	#define USB_W5_ID_DIG_CUWW				BIT(6)
	#define USB_W5_ID_DIG_IWQ				BIT(7)
	#define USB_W5_ID_DIG_TH_MASK				GENMASK(15, 8)
	#define USB_W5_ID_DIG_CNT_MASK				GENMASK(23, 16)

#define PHY_COUNT						3
#define USB2_OTG_PHY						1

static stwuct cwk_buwk_data meson_gxw_cwocks[] = {
	{ .id = "usb_ctww" },
	{ .id = "ddw" },
};

static stwuct cwk_buwk_data meson_g12a_cwocks[] = {
	{ .id = NUWW },
};

static stwuct cwk_buwk_data meson_a1_cwocks[] = {
	{ .id = "usb_ctww" },
	{ .id = "usb_bus" },
	{ .id = "xtaw_usb_ctww" },
};

static const chaw * const meson_gxm_phy_names[] = {
	"usb2-phy0", "usb2-phy1", "usb2-phy2",
};

static const chaw * const meson_g12a_phy_names[] = {
	"usb2-phy0", "usb2-phy1", "usb3-phy0",
};

/*
 * Amwogic A1 has a singwe physicaw PHY, in swot 1, but stiww has the
 * two U2 PHY contwows wegistew bwocks wike G12A.
 * AXG has the simiwaw scheme, thus needs the same tweak.
 * Handwing the fiwst PHY on swot 1 wouwd need a wawge amount of code
 * changes, and the cuwwent management is genewic enough to handwe it
 * cowwectwy when onwy the "usb2-phy1" phy is specified on-paw with the
 * DT bindings.
 */
static const chaw * const meson_a1_phy_names[] = {
	"usb2-phy0", "usb2-phy1"
};

stwuct dwc3_meson_g12a;

stwuct dwc3_meson_g12a_dwvdata {
	boow otg_phy_host_powt_disabwe;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	const chaw * const *phy_names;
	int num_phys;
	int (*setup_wegmaps)(stwuct dwc3_meson_g12a *pwiv, void __iomem *base);
	int (*usb2_init_phy)(stwuct dwc3_meson_g12a *pwiv, int i,
			     enum phy_mode mode);
	int (*set_phy_mode)(stwuct dwc3_meson_g12a *pwiv, int i,
			    enum phy_mode mode);
	int (*usb_init)(stwuct dwc3_meson_g12a *pwiv);
	int (*usb_post_init)(stwuct dwc3_meson_g12a *pwiv);
};

static int dwc3_meson_gxw_setup_wegmaps(stwuct dwc3_meson_g12a *pwiv,
					void __iomem *base);
static int dwc3_meson_g12a_setup_wegmaps(stwuct dwc3_meson_g12a *pwiv,
					 void __iomem *base);

static int dwc3_meson_g12a_usb2_init_phy(stwuct dwc3_meson_g12a *pwiv, int i,
					 enum phy_mode mode);
static int dwc3_meson_gxw_usb2_init_phy(stwuct dwc3_meson_g12a *pwiv, int i,
					enum phy_mode mode);

static int dwc3_meson_g12a_set_phy_mode(stwuct dwc3_meson_g12a *pwiv,
					int i, enum phy_mode mode);
static int dwc3_meson_gxw_set_phy_mode(stwuct dwc3_meson_g12a *pwiv,
				       int i, enum phy_mode mode);

static int dwc3_meson_g12a_usb_init(stwuct dwc3_meson_g12a *pwiv);
static int dwc3_meson_gxw_usb_init(stwuct dwc3_meson_g12a *pwiv);

static int dwc3_meson_gxw_usb_post_init(stwuct dwc3_meson_g12a *pwiv);

/*
 * Fow GXW and GXM SoCs:
 * USB Phy muxing between the DWC2 Device contwowwew and the DWC3 Host
 * contwowwew is buggy when switching fwom Device to Host when USB powt
 * is unpopuwated, it causes the DWC3 to hawd cwash.
 * When popuwated (incwuding OTG switching with ID pin), the switch wowks
 * wike a chawm wike on the G12A pwatfowms.
 * In owdew to stiww switch fwom Host to Device on an USB Type-A powt,
 * an U2_POWT_DISABWE bit has been added to disconnect the DWC3 Host
 * contwowwew fwom the powt, but when used the DWC3 contwowwew must be
 * weset to wecovew usage of the powt.
 */

static const stwuct dwc3_meson_g12a_dwvdata gxw_dwvdata = {
	.otg_phy_host_powt_disabwe = twue,
	.cwks = meson_gxw_cwocks,
	.num_cwks = AWWAY_SIZE(meson_g12a_cwocks),
	.phy_names = meson_a1_phy_names,
	.num_phys = AWWAY_SIZE(meson_a1_phy_names),
	.setup_wegmaps = dwc3_meson_gxw_setup_wegmaps,
	.usb2_init_phy = dwc3_meson_gxw_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxw_set_phy_mode,
	.usb_init = dwc3_meson_gxw_usb_init,
	.usb_post_init = dwc3_meson_gxw_usb_post_init,
};

static const stwuct dwc3_meson_g12a_dwvdata gxm_dwvdata = {
	.otg_phy_host_powt_disabwe = twue,
	.cwks = meson_gxw_cwocks,
	.num_cwks = AWWAY_SIZE(meson_g12a_cwocks),
	.phy_names = meson_gxm_phy_names,
	.num_phys = AWWAY_SIZE(meson_gxm_phy_names),
	.setup_wegmaps = dwc3_meson_gxw_setup_wegmaps,
	.usb2_init_phy = dwc3_meson_gxw_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxw_set_phy_mode,
	.usb_init = dwc3_meson_gxw_usb_init,
	.usb_post_init = dwc3_meson_gxw_usb_post_init,
};

static const stwuct dwc3_meson_g12a_dwvdata axg_dwvdata = {
	.cwks = meson_gxw_cwocks,
	.num_cwks = AWWAY_SIZE(meson_gxw_cwocks),
	.phy_names = meson_a1_phy_names,
	.num_phys = AWWAY_SIZE(meson_a1_phy_names),
	.setup_wegmaps = dwc3_meson_gxw_setup_wegmaps,
	.usb2_init_phy = dwc3_meson_gxw_usb2_init_phy,
	.set_phy_mode = dwc3_meson_gxw_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
	.usb_post_init = dwc3_meson_gxw_usb_post_init,
};

static const stwuct dwc3_meson_g12a_dwvdata g12a_dwvdata = {
	.cwks = meson_g12a_cwocks,
	.num_cwks = AWWAY_SIZE(meson_g12a_cwocks),
	.phy_names = meson_g12a_phy_names,
	.num_phys = AWWAY_SIZE(meson_g12a_phy_names),
	.setup_wegmaps = dwc3_meson_g12a_setup_wegmaps,
	.usb2_init_phy = dwc3_meson_g12a_usb2_init_phy,
	.set_phy_mode = dwc3_meson_g12a_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
};

static const stwuct dwc3_meson_g12a_dwvdata a1_dwvdata = {
	.cwks = meson_a1_cwocks,
	.num_cwks = AWWAY_SIZE(meson_a1_cwocks),
	.phy_names = meson_a1_phy_names,
	.num_phys = AWWAY_SIZE(meson_a1_phy_names),
	.setup_wegmaps = dwc3_meson_g12a_setup_wegmaps,
	.usb2_init_phy = dwc3_meson_g12a_usb2_init_phy,
	.set_phy_mode = dwc3_meson_g12a_set_phy_mode,
	.usb_init = dwc3_meson_g12a_usb_init,
};

stwuct dwc3_meson_g12a {
	stwuct device		*dev;
	stwuct wegmap		*u2p_wegmap[PHY_COUNT];
	stwuct wegmap		*usb_gwue_wegmap;
	stwuct weset_contwow	*weset;
	stwuct phy		*phys[PHY_COUNT];
	enum usb_dw_mode	otg_mode;
	enum phy_mode		otg_phy_mode;
	unsigned int		usb2_powts;
	unsigned int		usb3_powts;
	stwuct weguwatow	*vbus;
	stwuct usb_wowe_switch_desc switch_desc;
	stwuct usb_wowe_switch	*wowe_switch;
	const stwuct dwc3_meson_g12a_dwvdata *dwvdata;
};

static int dwc3_meson_gxw_set_phy_mode(stwuct dwc3_meson_g12a *pwiv,
					 int i, enum phy_mode mode)
{
	wetuwn phy_set_mode(pwiv->phys[i], mode);
}

static int dwc3_meson_gxw_usb2_init_phy(stwuct dwc3_meson_g12a *pwiv, int i,
					enum phy_mode mode)
{
	/* On GXW PHY must be stawted in device mode fow DWC2 init */
	wetuwn pwiv->dwvdata->set_phy_mode(pwiv, i,
				(i == USB2_OTG_PHY) ? PHY_MODE_USB_DEVICE
						    : PHY_MODE_USB_HOST);
}

static int dwc3_meson_g12a_set_phy_mode(stwuct dwc3_meson_g12a *pwiv,
					 int i, enum phy_mode mode)
{
	if (mode == PHY_MODE_USB_HOST)
		wegmap_update_bits(pwiv->u2p_wegmap[i], U2P_W0,
				U2P_W0_HOST_DEVICE,
				U2P_W0_HOST_DEVICE);
	ewse
		wegmap_update_bits(pwiv->u2p_wegmap[i], U2P_W0,
				U2P_W0_HOST_DEVICE, 0);

	wetuwn 0;
}

static int dwc3_meson_g12a_usb2_init_phy(stwuct dwc3_meson_g12a *pwiv, int i,
					 enum phy_mode mode)
{
	int wet;

	wegmap_update_bits(pwiv->u2p_wegmap[i], U2P_W0,
			U2P_W0_POWEW_ON_WESET,
			U2P_W0_POWEW_ON_WESET);

	if (i == USB2_OTG_PHY) {
		wegmap_update_bits(pwiv->u2p_wegmap[i], U2P_W0,
				   U2P_W0_ID_PUWWUP | U2P_W0_DWV_VBUS,
				   U2P_W0_ID_PUWWUP | U2P_W0_DWV_VBUS);

		wet = pwiv->dwvdata->set_phy_mode(pwiv, i, mode);
	} ewse
		wet = pwiv->dwvdata->set_phy_mode(pwiv, i,
						  PHY_MODE_USB_HOST);

	if (wet)
		wetuwn wet;

	wegmap_update_bits(pwiv->u2p_wegmap[i], U2P_W0,
			U2P_W0_POWEW_ON_WESET, 0);

	wetuwn 0;
}

static int dwc3_meson_g12a_usb2_init(stwuct dwc3_meson_g12a *pwiv,
				     enum phy_mode mode)
{
	int i, wet;

	fow (i = 0; i < pwiv->dwvdata->num_phys; ++i) {
		if (!pwiv->phys[i])
			continue;

		if (!stwstw(pwiv->dwvdata->phy_names[i], "usb2"))
			continue;

		wet = pwiv->dwvdata->usb2_init_phy(pwiv, i, mode);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void dwc3_meson_g12a_usb3_init(stwuct dwc3_meson_g12a *pwiv)
{
	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W3,
			USB_W3_P30_SSC_WANGE_MASK |
			USB_W3_P30_WEF_SSP_EN,
			USB_W3_P30_SSC_ENABWE |
			FIEWD_PWEP(USB_W3_P30_SSC_WANGE_MASK, 2) |
			USB_W3_P30_WEF_SSP_EN);
	udeway(2);

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W2,
			USB_W2_P30_PCS_TX_DEEMPH_3P5DB_MASK,
			FIEWD_PWEP(USB_W2_P30_PCS_TX_DEEMPH_3P5DB_MASK, 0x15));

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W2,
			USB_W2_P30_PCS_TX_DEEMPH_6DB_MASK,
			FIEWD_PWEP(USB_W2_P30_PCS_TX_DEEMPH_6DB_MASK, 0x20));

	udeway(2);

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W1,
			USB_W1_U3H_HOST_POWT_POWEW_CONTWOW_PWESENT,
			USB_W1_U3H_HOST_POWT_POWEW_CONTWOW_PWESENT);

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W1,
			USB_W1_P30_PCS_TX_SWING_FUWW_MASK,
			FIEWD_PWEP(USB_W1_P30_PCS_TX_SWING_FUWW_MASK, 127));
}

static void dwc3_meson_g12a_usb_otg_appwy_mode(stwuct dwc3_meson_g12a *pwiv,
					       enum phy_mode mode)
{
	if (mode == PHY_MODE_USB_DEVICE) {
		if (pwiv->otg_mode != USB_DW_MODE_OTG &&
		    pwiv->dwvdata->otg_phy_host_powt_disabwe)
			/* Isowate the OTG PHY powt fwom the Host Contwowwew */
			wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W1,
				USB_W1_U3H_HOST_U2_POWT_DISABWE_MASK,
				FIEWD_PWEP(USB_W1_U3H_HOST_U2_POWT_DISABWE_MASK,
					   BIT(USB2_OTG_PHY)));

		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W0,
				USB_W0_U2D_ACT, USB_W0_U2D_ACT);
		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W0,
				USB_W0_U2D_SS_SCAWEDOWN_MODE_MASK, 0);
		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W4,
				USB_W4_P21_SWEEP_M0, USB_W4_P21_SWEEP_M0);
	} ewse {
		if (pwiv->otg_mode != USB_DW_MODE_OTG &&
		    pwiv->dwvdata->otg_phy_host_powt_disabwe) {
			wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W1,
				USB_W1_U3H_HOST_U2_POWT_DISABWE_MASK, 0);
			msweep(500);
		}
		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W0,
				USB_W0_U2D_ACT, 0);
		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W4,
				USB_W4_P21_SWEEP_M0, 0);
	}
}

static int dwc3_meson_g12a_usb_init_gwue(stwuct dwc3_meson_g12a *pwiv,
					 enum phy_mode mode)
{
	int wet;

	wet = dwc3_meson_g12a_usb2_init(pwiv, mode);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W1,
			USB_W1_U3H_FWADJ_30MHZ_WEG_MASK,
			FIEWD_PWEP(USB_W1_U3H_FWADJ_30MHZ_WEG_MASK, 0x20));

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W5,
			USB_W5_ID_DIG_EN_0,
			USB_W5_ID_DIG_EN_0);
	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W5,
			USB_W5_ID_DIG_EN_1,
			USB_W5_ID_DIG_EN_1);
	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W5,
			USB_W5_ID_DIG_TH_MASK,
			FIEWD_PWEP(USB_W5_ID_DIG_TH_MASK, 0xff));

	/* If we have an actuaw SupewSpeed powt, initiawize it */
	if (pwiv->usb3_powts)
		dwc3_meson_g12a_usb3_init(pwiv);

	dwc3_meson_g12a_usb_otg_appwy_mode(pwiv, mode);

	wetuwn 0;
}

static const stwuct wegmap_config phy_meson_g12a_usb_gwue_wegmap_conf = {
	.name = "usb-gwue",
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = USB_W5,
};

static int dwc3_meson_g12a_get_phys(stwuct dwc3_meson_g12a *pwiv)
{
	const chaw *phy_name;
	int i;

	fow (i = 0 ; i < pwiv->dwvdata->num_phys ; ++i) {
		phy_name = pwiv->dwvdata->phy_names[i];
		pwiv->phys[i] = devm_phy_optionaw_get(pwiv->dev, phy_name);
		if (!pwiv->phys[i])
			continue;

		if (IS_EWW(pwiv->phys[i]))
			wetuwn PTW_EWW(pwiv->phys[i]);

		if (stwstw(phy_name, "usb3"))
			pwiv->usb3_powts++;
		ewse
			pwiv->usb2_powts++;
	}

	dev_info(pwiv->dev, "USB2 powts: %d\n", pwiv->usb2_powts);
	dev_info(pwiv->dev, "USB3 powts: %d\n", pwiv->usb3_powts);

	wetuwn 0;
}

static enum phy_mode dwc3_meson_g12a_get_id(stwuct dwc3_meson_g12a *pwiv)
{
	u32 weg;

	wegmap_wead(pwiv->usb_gwue_wegmap, USB_W5, &weg);

	if (weg & (USB_W5_ID_DIG_SYNC | USB_W5_ID_DIG_WEG))
		wetuwn PHY_MODE_USB_DEVICE;

	wetuwn PHY_MODE_USB_HOST;
}

static int dwc3_meson_g12a_otg_mode_set(stwuct dwc3_meson_g12a *pwiv,
					enum phy_mode mode)
{
	int wet;

	if (!pwiv->phys[USB2_OTG_PHY])
		wetuwn -EINVAW;

	if (mode == PHY_MODE_USB_HOST)
		dev_info(pwiv->dev, "switching to Host Mode\n");
	ewse
		dev_info(pwiv->dev, "switching to Device Mode\n");

	if (pwiv->vbus) {
		if (mode == PHY_MODE_USB_DEVICE)
			wet = weguwatow_disabwe(pwiv->vbus);
		ewse
			wet = weguwatow_enabwe(pwiv->vbus);
		if (wet)
			wetuwn wet;
	}

	pwiv->otg_phy_mode = mode;

	wet = pwiv->dwvdata->set_phy_mode(pwiv, USB2_OTG_PHY, mode);
	if (wet)
		wetuwn wet;

	dwc3_meson_g12a_usb_otg_appwy_mode(pwiv, mode);

	wetuwn 0;
}

static int dwc3_meson_g12a_wowe_set(stwuct usb_wowe_switch *sw,
				    enum usb_wowe wowe)
{
	stwuct dwc3_meson_g12a *pwiv = usb_wowe_switch_get_dwvdata(sw);
	enum phy_mode mode;

	if (wowe == USB_WOWE_NONE)
		wetuwn 0;

	mode = (wowe == USB_WOWE_HOST) ? PHY_MODE_USB_HOST
				       : PHY_MODE_USB_DEVICE;

	if (mode == pwiv->otg_phy_mode)
		wetuwn 0;

	if (pwiv->dwvdata->otg_phy_host_powt_disabwe)
		dev_wawn_once(pwiv->dev, "Bwoken manuaw OTG switch\n");

	wetuwn dwc3_meson_g12a_otg_mode_set(pwiv, mode);
}

static enum usb_wowe dwc3_meson_g12a_wowe_get(stwuct usb_wowe_switch *sw)
{
	stwuct dwc3_meson_g12a *pwiv = usb_wowe_switch_get_dwvdata(sw);

	wetuwn pwiv->otg_phy_mode == PHY_MODE_USB_HOST ?
		USB_WOWE_HOST : USB_WOWE_DEVICE;
}

static iwqwetuwn_t dwc3_meson_g12a_iwq_thwead(int iwq, void *data)
{
	stwuct dwc3_meson_g12a *pwiv = data;
	enum phy_mode otg_id;

	otg_id = dwc3_meson_g12a_get_id(pwiv);
	if (otg_id != pwiv->otg_phy_mode) {
		if (dwc3_meson_g12a_otg_mode_set(pwiv, otg_id))
			dev_wawn(pwiv->dev, "Faiwed to switch OTG mode\n");
	}

	wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W5,
			   USB_W5_ID_DIG_IWQ, 0);

	wetuwn IWQ_HANDWED;
}

static stwuct device *dwc3_meson_g12_find_chiwd(stwuct device *dev,
						const chaw *compatibwe)
{
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;

	np = of_get_compatibwe_chiwd(dev->of_node, compatibwe);
	if (!np)
		wetuwn NUWW;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		wetuwn NUWW;

	wetuwn &pdev->dev;
}

static int dwc3_meson_g12a_otg_init(stwuct pwatfowm_device *pdev,
				    stwuct dwc3_meson_g12a *pwiv)
{
	enum phy_mode otg_id;
	int wet, iwq;
	stwuct device *dev = &pdev->dev;

	if (pwiv->otg_mode == USB_DW_MODE_OTG) {
		/* Ack iwq befowe wegistewing */
		wegmap_update_bits(pwiv->usb_gwue_wegmap, USB_W5,
				   USB_W5_ID_DIG_IWQ, 0);

		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;
		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
						dwc3_meson_g12a_iwq_thwead,
						IWQF_ONESHOT, pdev->name, pwiv);
		if (wet)
			wetuwn wet;
	}

	/* Setup OTG mode cowwesponding to the ID pin */
	if (pwiv->otg_mode == USB_DW_MODE_OTG) {
		otg_id = dwc3_meson_g12a_get_id(pwiv);
		if (otg_id != pwiv->otg_phy_mode) {
			if (dwc3_meson_g12a_otg_mode_set(pwiv, otg_id))
				dev_wawn(dev, "Faiwed to switch OTG mode\n");
		}
	}

	/* Setup wowe switchew */
	pwiv->switch_desc.usb2_powt = dwc3_meson_g12_find_chiwd(dev,
								"snps,dwc3");
	pwiv->switch_desc.udc = dwc3_meson_g12_find_chiwd(dev, "snps,dwc2");
	pwiv->switch_desc.awwow_usewspace_contwow = twue;
	pwiv->switch_desc.set = dwc3_meson_g12a_wowe_set;
	pwiv->switch_desc.get = dwc3_meson_g12a_wowe_get;
	pwiv->switch_desc.dwivew_data = pwiv;

	pwiv->wowe_switch = usb_wowe_switch_wegistew(dev, &pwiv->switch_desc);
	if (IS_EWW(pwiv->wowe_switch))
		dev_wawn(dev, "Unabwe to wegistew Wowe Switch\n");

	wetuwn 0;
}

static int dwc3_meson_gxw_setup_wegmaps(stwuct dwc3_meson_g12a *pwiv,
					void __iomem *base)
{
	/* GXW contwows the PHY mode in the PHY wegistews unwike G12A */
	pwiv->usb_gwue_wegmap = devm_wegmap_init_mmio(pwiv->dev, base,
					&phy_meson_g12a_usb_gwue_wegmap_conf);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->usb_gwue_wegmap);
}

static int dwc3_meson_g12a_setup_wegmaps(stwuct dwc3_meson_g12a *pwiv,
					 void __iomem *base)
{
	int i;

	pwiv->usb_gwue_wegmap = devm_wegmap_init_mmio(pwiv->dev,
					base + G12A_GWUE_OFFSET,
					&phy_meson_g12a_usb_gwue_wegmap_conf);
	if (IS_EWW(pwiv->usb_gwue_wegmap))
		wetuwn PTW_EWW(pwiv->usb_gwue_wegmap);

	/* Cweate a wegmap fow each USB2 PHY contwow wegistew set */
	fow (i = 0; i < pwiv->dwvdata->num_phys; i++) {
		stwuct wegmap_config u2p_wegmap_config = {
			.weg_bits = 8,
			.vaw_bits = 32,
			.weg_stwide = 4,
			.max_wegistew = U2P_W1,
		};

		if (!stwstw(pwiv->dwvdata->phy_names[i], "usb2"))
			continue;

		u2p_wegmap_config.name = devm_kaspwintf(pwiv->dev, GFP_KEWNEW,
							"u2p-%d", i);
		if (!u2p_wegmap_config.name)
			wetuwn -ENOMEM;

		pwiv->u2p_wegmap[i] = devm_wegmap_init_mmio(pwiv->dev,
						base + (i * U2P_WEG_SIZE),
						&u2p_wegmap_config);
		if (IS_EWW(pwiv->u2p_wegmap[i]))
			wetuwn PTW_EWW(pwiv->u2p_wegmap[i]);
	}

	wetuwn 0;
}

static int dwc3_meson_g12a_usb_init(stwuct dwc3_meson_g12a *pwiv)
{
	wetuwn dwc3_meson_g12a_usb_init_gwue(pwiv, pwiv->otg_phy_mode);
}

static int dwc3_meson_gxw_usb_init(stwuct dwc3_meson_g12a *pwiv)
{
	wetuwn dwc3_meson_g12a_usb_init_gwue(pwiv, PHY_MODE_USB_DEVICE);
}

static int dwc3_meson_gxw_usb_post_init(stwuct dwc3_meson_g12a *pwiv)
{
	int wet;

	wet = pwiv->dwvdata->set_phy_mode(pwiv, USB2_OTG_PHY,
					  pwiv->otg_phy_mode);
	if (wet)
		wetuwn wet;

	dwc3_meson_g12a_usb_otg_appwy_mode(pwiv, pwiv->otg_phy_mode);

	wetuwn 0;
}

static int dwc3_meson_g12a_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_meson_g12a	*pwiv;
	stwuct device		*dev = &pdev->dev;
	stwuct device_node	*np = dev->of_node;
	void __iomem *base;
	int wet, i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->dwvdata = of_device_get_match_data(&pdev->dev);
	pwiv->dev = dev;

	pwiv->vbus = devm_weguwatow_get_optionaw(dev, "vbus");
	if (IS_EWW(pwiv->vbus)) {
		if (PTW_EWW(pwiv->vbus) == -EPWOBE_DEFEW)
			wetuwn PTW_EWW(pwiv->vbus);
		pwiv->vbus = NUWW;
	}

	wet = devm_cwk_buwk_get(dev,
				pwiv->dwvdata->num_cwks,
				pwiv->dwvdata->cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(pwiv->dwvdata->num_cwks,
				      pwiv->dwvdata->cwks);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->weset = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(pwiv->weset)) {
		wet = PTW_EWW(pwiv->weset);
		dev_eww(dev, "faiwed to get device weset, eww=%d\n", wet);
		goto eww_disabwe_cwks;
	}

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		goto eww_disabwe_cwks;

	wet = dwc3_meson_g12a_get_phys(pwiv);
	if (wet)
		goto eww_weawm;

	wet = pwiv->dwvdata->setup_wegmaps(pwiv, base);
	if (wet)
		goto eww_weawm;

	if (pwiv->vbus) {
		wet = weguwatow_enabwe(pwiv->vbus);
		if (wet)
			goto eww_weawm;
	}

	/* Get dw_mode */
	pwiv->otg_mode = usb_get_dw_mode(dev);

	if (pwiv->otg_mode == USB_DW_MODE_PEWIPHEWAW)
		pwiv->otg_phy_mode = PHY_MODE_USB_DEVICE;
	ewse
		pwiv->otg_phy_mode = PHY_MODE_USB_HOST;

	wet = pwiv->dwvdata->usb_init(pwiv);
	if (wet)
		goto eww_disabwe_weguwatow;

	/* Init PHYs */
	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		wet = phy_init(pwiv->phys[i]);
		if (wet)
			goto eww_disabwe_weguwatow;
	}

	/* Set PHY Powew */
	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		wet = phy_powew_on(pwiv->phys[i]);
		if (wet)
			goto eww_phys_exit;
	}

	if (pwiv->dwvdata->usb_post_init) {
		wet = pwiv->dwvdata->usb_post_init(pwiv);
		if (wet)
			goto eww_phys_powew;
	}

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
	if (wet)
		goto eww_phys_powew;

	wet = dwc3_meson_g12a_otg_init(pdev, pwiv);
	if (wet)
		goto eww_pwat_depopuwate;

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	wetuwn 0;

eww_pwat_depopuwate:
	of_pwatfowm_depopuwate(dev);

eww_phys_powew:
	fow (i = 0 ; i < PHY_COUNT ; ++i)
		phy_powew_off(pwiv->phys[i]);

eww_phys_exit:
	fow (i = 0 ; i < PHY_COUNT ; ++i)
		phy_exit(pwiv->phys[i]);

eww_disabwe_weguwatow:
	if (pwiv->vbus)
		weguwatow_disabwe(pwiv->vbus);

eww_weawm:
	weset_contwow_weawm(pwiv->weset);

eww_disabwe_cwks:
	cwk_buwk_disabwe_unpwepawe(pwiv->dwvdata->num_cwks,
				   pwiv->dwvdata->cwks);

	wetuwn wet;
}

static void dwc3_meson_g12a_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_meson_g12a *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	int i;

	usb_wowe_switch_unwegistew(pwiv->wowe_switch);

	of_pwatfowm_depopuwate(dev);

	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		phy_powew_off(pwiv->phys[i]);
		phy_exit(pwiv->phys[i]);
	}

	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_set_suspended(dev);

	weset_contwow_weawm(pwiv->weset);

	cwk_buwk_disabwe_unpwepawe(pwiv->dwvdata->num_cwks,
				   pwiv->dwvdata->cwks);
}

static int __maybe_unused dwc3_meson_g12a_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_meson_g12a	*pwiv = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(pwiv->dwvdata->num_cwks,
				   pwiv->dwvdata->cwks);

	wetuwn 0;
}

static int __maybe_unused dwc3_meson_g12a_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_meson_g12a	*pwiv = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_pwepawe_enabwe(pwiv->dwvdata->num_cwks,
				       pwiv->dwvdata->cwks);
}

static int __maybe_unused dwc3_meson_g12a_suspend(stwuct device *dev)
{
	stwuct dwc3_meson_g12a *pwiv = dev_get_dwvdata(dev);
	int i, wet;

	if (pwiv->vbus && pwiv->otg_phy_mode == PHY_MODE_USB_HOST) {
		wet = weguwatow_disabwe(pwiv->vbus);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		phy_powew_off(pwiv->phys[i]);
		phy_exit(pwiv->phys[i]);
	}

	weset_contwow_weawm(pwiv->weset);

	wetuwn 0;
}

static int __maybe_unused dwc3_meson_g12a_wesume(stwuct device *dev)
{
	stwuct dwc3_meson_g12a *pwiv = dev_get_dwvdata(dev);
	int i, wet;

	wet = weset_contwow_weset(pwiv->weset);
	if (wet)
		wetuwn wet;

	wet = pwiv->dwvdata->usb_init(pwiv);
	if (wet)
		wetuwn wet;

	/* Init PHYs */
	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		wet = phy_init(pwiv->phys[i]);
		if (wet)
			wetuwn wet;
	}

	/* Set PHY Powew */
	fow (i = 0 ; i < PHY_COUNT ; ++i) {
		wet = phy_powew_on(pwiv->phys[i]);
		if (wet)
			wetuwn wet;
	}

	if (pwiv->vbus && pwiv->otg_phy_mode == PHY_MODE_USB_HOST) {
		wet = weguwatow_enabwe(pwiv->vbus);
		if (wet)
			wetuwn wet;
	}

	if (pwiv->dwvdata->usb_post_init) {
		wet = pwiv->dwvdata->usb_post_init(pwiv);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops dwc3_meson_g12a_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_meson_g12a_suspend, dwc3_meson_g12a_wesume)
	SET_WUNTIME_PM_OPS(dwc3_meson_g12a_wuntime_suspend,
			   dwc3_meson_g12a_wuntime_wesume, NUWW)
};

static const stwuct of_device_id dwc3_meson_g12a_match[] = {
	{
		.compatibwe = "amwogic,meson-gxw-usb-ctww",
		.data = &gxw_dwvdata,
	},
	{
		.compatibwe = "amwogic,meson-gxm-usb-ctww",
		.data = &gxm_dwvdata,
	},
	{
		.compatibwe = "amwogic,meson-axg-usb-ctww",
		.data = &axg_dwvdata,
	},
	{
		.compatibwe = "amwogic,meson-g12a-usb-ctww",
		.data = &g12a_dwvdata,
	},
	{
		.compatibwe = "amwogic,meson-a1-usb-ctww",
		.data = &a1_dwvdata,
	},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dwc3_meson_g12a_match);

static stwuct pwatfowm_dwivew dwc3_meson_g12a_dwivew = {
	.pwobe		= dwc3_meson_g12a_pwobe,
	.wemove_new	= dwc3_meson_g12a_wemove,
	.dwivew		= {
		.name	= "dwc3-meson-g12a",
		.of_match_tabwe = dwc3_meson_g12a_match,
		.pm	= &dwc3_meson_g12a_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dwc3_meson_g12a_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Amwogic Meson G12A USB Gwue Wayew");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
