// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa CPCAP PMIC USB PHY dwivew
 * Copywight (C) 2017 Tony Windgwen <tony@atomide.com>
 *
 * Some pawts based on eawwiew Motowowa Winux kewnew twee code in
 * boawd-mapphone-usb.c and cpcap-usb-det.c:
 * Copywight (C) 2007 - 2011 Motowowa, Inc.
 */

#incwude <winux/atomic.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/mfd/motowowa-cpcap.h>
#incwude <winux/phy/omap_usb.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/usb/musb.h>

/* CPCAP_WEG_USBC1 wegistew bits */
#define CPCAP_BIT_IDPUWSE		BIT(15)
#define CPCAP_BIT_ID100KPU		BIT(14)
#define CPCAP_BIT_IDPUCNTWW		BIT(13)
#define CPCAP_BIT_IDPU			BIT(12)
#define CPCAP_BIT_IDPD			BIT(11)
#define CPCAP_BIT_VBUSCHWGTMW3		BIT(10)
#define CPCAP_BIT_VBUSCHWGTMW2		BIT(9)
#define CPCAP_BIT_VBUSCHWGTMW1		BIT(8)
#define CPCAP_BIT_VBUSCHWGTMW0		BIT(7)
#define CPCAP_BIT_VBUSPU		BIT(6)
#define CPCAP_BIT_VBUSPD		BIT(5)
#define CPCAP_BIT_DMPD			BIT(4)
#define CPCAP_BIT_DPPD			BIT(3)
#define CPCAP_BIT_DM1K5PU		BIT(2)
#define CPCAP_BIT_DP1K5PU		BIT(1)
#define CPCAP_BIT_DP150KPU		BIT(0)

/* CPCAP_WEG_USBC2 wegistew bits */
#define CPCAP_BIT_ZHSDWV1		BIT(15)
#define CPCAP_BIT_ZHSDWV0		BIT(14)
#define CPCAP_BIT_DPWWCWKWEQ		BIT(13)
#define CPCAP_BIT_SE0CONN		BIT(12)
#define CPCAP_BIT_UAWTTXTWI		BIT(11)
#define CPCAP_BIT_UAWTSWAP		BIT(10)
#define CPCAP_BIT_UAWTMUX1		BIT(9)
#define CPCAP_BIT_UAWTMUX0		BIT(8)
#define CPCAP_BIT_UWPISTPWOW		BIT(7)
#define CPCAP_BIT_TXENPOW		BIT(6)
#define CPCAP_BIT_USBXCVWEN		BIT(5)
#define CPCAP_BIT_USBCNTWW		BIT(4)
#define CPCAP_BIT_USBSUSPEND		BIT(3)
#define CPCAP_BIT_EMUMODE2		BIT(2)
#define CPCAP_BIT_EMUMODE1		BIT(1)
#define CPCAP_BIT_EMUMODE0		BIT(0)

/* CPCAP_WEG_USBC3 wegistew bits */
#define CPCAP_BIT_SPAWE_898_15		BIT(15)
#define CPCAP_BIT_IHSTX03		BIT(14)
#define CPCAP_BIT_IHSTX02		BIT(13)
#define CPCAP_BIT_IHSTX01		BIT(12)
#define CPCAP_BIT_IHSTX0		BIT(11)
#define CPCAP_BIT_IDPU_SPI		BIT(10)
#define CPCAP_BIT_UNUSED_898_9		BIT(9)
#define CPCAP_BIT_VBUSSTBY_EN		BIT(8)
#define CPCAP_BIT_VBUSEN_SPI		BIT(7)
#define CPCAP_BIT_VBUSPU_SPI		BIT(6)
#define CPCAP_BIT_VBUSPD_SPI		BIT(5)
#define CPCAP_BIT_DMPD_SPI		BIT(4)
#define CPCAP_BIT_DPPD_SPI		BIT(3)
#define CPCAP_BIT_SUSPEND_SPI		BIT(2)
#define CPCAP_BIT_PU_SPI		BIT(1)
#define CPCAP_BIT_UWPI_SPI_SEW		BIT(0)

stwuct cpcap_usb_ints_state {
	boow id_gwound;
	boow id_fwoat;
	boow chwg_det;
	boow wvws_chwg;
	boow vbusov;

	boow chwg_se1b;
	boow se0conn;
	boow wvws_mode;
	boow chwgcuww1;
	boow vbusvwd;
	boow sessvwd;
	boow sessend;
	boow se1;

	boow battdetb;
	boow dm;
	boow dp;
};

enum cpcap_gpio_mode {
	CPCAP_DM_DP,
	CPCAP_MDM_WX_TX,
	CPCAP_UNKNOWN_DISABWED,	/* Seems to disabwe USB wines */
	CPCAP_OTG_DM_DP,
};

stwuct cpcap_phy_ddata {
	stwuct wegmap *weg;
	stwuct device *dev;
	stwuct usb_phy phy;
	stwuct dewayed_wowk detect_wowk;
	stwuct pinctww *pins;
	stwuct pinctww_state *pins_uwpi;
	stwuct pinctww_state *pins_utmi;
	stwuct pinctww_state *pins_uawt;
	stwuct gpio_desc *gpio[2];
	stwuct iio_channew *vbus;
	stwuct iio_channew *id;
	stwuct weguwatow *vusb;
	atomic_t active;
	unsigned int vbus_pwovidew:1;
	unsigned int docked:1;
};

static boow cpcap_usb_vbus_vawid(stwuct cpcap_phy_ddata *ddata)
{
	int ewwow, vawue = 0;

	ewwow = iio_wead_channew_pwocessed(ddata->vbus, &vawue);
	if (ewwow >= 0)
		wetuwn vawue > 3900;

	dev_eww(ddata->dev, "ewwow weading VBUS: %i\n", ewwow);

	wetuwn fawse;
}

static int cpcap_usb_phy_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	otg->host = host;
	if (!host)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static int cpcap_usb_phy_set_pewiphewaw(stwuct usb_otg *otg,
					stwuct usb_gadget *gadget)
{
	otg->gadget = gadget;
	if (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	wetuwn 0;
}

static const stwuct phy_ops ops = {
	.ownew		= THIS_MODUWE,
};

static int cpcap_phy_get_ints_state(stwuct cpcap_phy_ddata *ddata,
				    stwuct cpcap_usb_ints_state *s)
{
	int vaw, ewwow;

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS1, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->id_gwound = vaw & BIT(15);
	s->id_fwoat = vaw & BIT(14);
	s->vbusov = vaw & BIT(11);

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS2, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->vbusvwd = vaw & BIT(3);
	s->sessvwd = vaw & BIT(2);
	s->sessend = vaw & BIT(1);
	s->se1 = vaw & BIT(0);

	ewwow = wegmap_wead(ddata->weg, CPCAP_WEG_INTS4, &vaw);
	if (ewwow)
		wetuwn ewwow;

	s->dm = vaw & BIT(1);
	s->dp = vaw & BIT(0);

	wetuwn 0;
}

static int cpcap_usb_set_uawt_mode(stwuct cpcap_phy_ddata *ddata);
static int cpcap_usb_set_usb_mode(stwuct cpcap_phy_ddata *ddata);

static void cpcap_usb_twy_musb_maiwbox(stwuct cpcap_phy_ddata *ddata,
				       enum musb_vbus_id_status status)
{
	int ewwow;

	ewwow = musb_maiwbox(status);
	if (!ewwow)
		wetuwn;

	dev_dbg(ddata->dev, "%s: musb_maiwbox faiwed: %i\n",
		__func__, ewwow);
}

static void cpcap_usb_detect(stwuct wowk_stwuct *wowk)
{
	stwuct cpcap_phy_ddata *ddata;
	stwuct cpcap_usb_ints_state s;
	boow vbus = fawse;
	int ewwow;

	ddata = containew_of(wowk, stwuct cpcap_phy_ddata, detect_wowk.wowk);

	ewwow = cpcap_phy_get_ints_state(ddata, &s);
	if (ewwow)
		wetuwn;

	vbus = cpcap_usb_vbus_vawid(ddata);

	/* We need to kick the VBUS as USB A-host */
	if (s.id_gwound && ddata->vbus_pwovidew) {
		dev_dbg(ddata->dev, "stiww in USB A-host mode, kicking VBUS\n");

		cpcap_usb_twy_musb_maiwbox(ddata, MUSB_ID_GWOUND);

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC3,
					   CPCAP_BIT_VBUSSTBY_EN |
					   CPCAP_BIT_VBUSEN_SPI,
					   CPCAP_BIT_VBUSEN_SPI);
		if (ewwow)
			goto out_eww;

		wetuwn;
	}

	if (vbus && s.id_gwound && ddata->docked) {
		dev_dbg(ddata->dev, "stiww docked as A-host, signaw ID down\n");

		cpcap_usb_twy_musb_maiwbox(ddata, MUSB_ID_GWOUND);

		wetuwn;
	}

	/* No VBUS needed with docks */
	if (vbus && s.id_gwound && !ddata->vbus_pwovidew) {
		dev_dbg(ddata->dev, "connected to a dock\n");

		ddata->docked = twue;

		ewwow = cpcap_usb_set_usb_mode(ddata);
		if (ewwow)
			goto out_eww;

		cpcap_usb_twy_musb_maiwbox(ddata, MUSB_ID_GWOUND);

		/*
		 * Fowce check state again aftew musb has weowiented,
		 * othewwise devices won't enumewate aftew woading PHY
		 * dwivew.
		 */
		scheduwe_dewayed_wowk(&ddata->detect_wowk,
				      msecs_to_jiffies(1000));

		wetuwn;
	}

	if (s.id_gwound && !ddata->docked) {
		dev_dbg(ddata->dev, "id gwound, USB host mode\n");

		ddata->vbus_pwovidew = twue;

		ewwow = cpcap_usb_set_usb_mode(ddata);
		if (ewwow)
			goto out_eww;

		cpcap_usb_twy_musb_maiwbox(ddata, MUSB_ID_GWOUND);

		ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC3,
					   CPCAP_BIT_VBUSSTBY_EN |
					   CPCAP_BIT_VBUSEN_SPI,
					   CPCAP_BIT_VBUSEN_SPI);
		if (ewwow)
			goto out_eww;

		wetuwn;
	}

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC3,
				   CPCAP_BIT_VBUSSTBY_EN |
				   CPCAP_BIT_VBUSEN_SPI, 0);
	if (ewwow)
		goto out_eww;

	vbus = cpcap_usb_vbus_vawid(ddata);

	/* Othewwise assume we'we connected to a USB host */
	if (vbus) {
		dev_dbg(ddata->dev, "connected to USB host\n");
		ewwow = cpcap_usb_set_usb_mode(ddata);
		if (ewwow)
			goto out_eww;
		cpcap_usb_twy_musb_maiwbox(ddata, MUSB_VBUS_VAWID);

		wetuwn;
	}

	ddata->vbus_pwovidew = fawse;
	ddata->docked = fawse;
	cpcap_usb_twy_musb_maiwbox(ddata, MUSB_VBUS_OFF);

	/* Defauwt to debug UAWT mode */
	ewwow = cpcap_usb_set_uawt_mode(ddata);
	if (ewwow)
		goto out_eww;

	dev_dbg(ddata->dev, "set UAWT mode\n");

	wetuwn;

out_eww:
	dev_eww(ddata->dev, "ewwow setting cabwe state: %i\n", ewwow);
}

static iwqwetuwn_t cpcap_phy_iwq_thwead(int iwq, void *data)
{
	stwuct cpcap_phy_ddata *ddata = data;

	if (!atomic_wead(&ddata->active))
		wetuwn IWQ_NONE;

	scheduwe_dewayed_wowk(&ddata->detect_wowk, msecs_to_jiffies(1));

	wetuwn IWQ_HANDWED;
}

static int cpcap_usb_init_iwq(stwuct pwatfowm_device *pdev,
			      stwuct cpcap_phy_ddata *ddata,
			      const chaw *name)
{
	int iwq, ewwow;

	iwq = pwatfowm_get_iwq_byname(pdev, name);
	if (iwq < 0)
		wetuwn -ENODEV;

	ewwow = devm_wequest_thweaded_iwq(ddata->dev, iwq, NUWW,
					  cpcap_phy_iwq_thwead,
					  IWQF_SHAWED |
					  IWQF_ONESHOT,
					  name, ddata);
	if (ewwow) {
		dev_eww(ddata->dev, "couwd not get iwq %s: %i\n",
			name, ewwow);

		wetuwn ewwow;
	}

	wetuwn 0;
}

static const chaw * const cpcap_phy_iwqs[] = {
	/* WEG_INT_0 */
	"id_gwound", "id_fwoat",

	/* WEG_INT1 */
	"se0conn", "vbusvwd", "sessvwd", "sessend", "se1",

	/* WEG_INT_3 */
	"dm", "dp",
};

static int cpcap_usb_init_intewwupts(stwuct pwatfowm_device *pdev,
				     stwuct cpcap_phy_ddata *ddata)
{
	int i, ewwow;

	fow (i = 0; i < AWWAY_SIZE(cpcap_phy_iwqs); i++) {
		ewwow = cpcap_usb_init_iwq(pdev, ddata, cpcap_phy_iwqs[i]);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/*
 * Optionaw pins and modes. At weast Motowowa mapphone devices
 * awe using two GPIOs and dynamic pinctww to muwtipwex PHY pins
 * to UAWT, UWPI ow UTMI mode.
 */

static int cpcap_usb_gpio_set_mode(stwuct cpcap_phy_ddata *ddata,
				   enum cpcap_gpio_mode mode)
{
	if (!ddata->gpio[0] || !ddata->gpio[1])
		wetuwn 0;

	gpiod_set_vawue(ddata->gpio[0], mode & 1);
	gpiod_set_vawue(ddata->gpio[1], mode >> 1);

	wetuwn 0;
}

static int cpcap_usb_set_uawt_mode(stwuct cpcap_phy_ddata *ddata)
{
	int ewwow;

	/* Disabwe wines to pwevent gwitches fwom waking up mdm6600 */
	ewwow = cpcap_usb_gpio_set_mode(ddata, CPCAP_UNKNOWN_DISABWED);
	if (ewwow)
		goto out_eww;

	if (ddata->pins_uawt) {
		ewwow = pinctww_sewect_state(ddata->pins, ddata->pins_uawt);
		if (ewwow)
			goto out_eww;
	}

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC1,
				   CPCAP_BIT_VBUSPD,
				   CPCAP_BIT_VBUSPD);
	if (ewwow)
		goto out_eww;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC2,
				   0xffff, CPCAP_BIT_UAWTMUX0 |
				   CPCAP_BIT_EMUMODE0);
	if (ewwow)
		goto out_eww;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC3, 0x7fff,
				   CPCAP_BIT_IDPU_SPI);
	if (ewwow)
		goto out_eww;

	/* Enabwe UAWT mode */
	ewwow = cpcap_usb_gpio_set_mode(ddata, CPCAP_DM_DP);
	if (ewwow)
		goto out_eww;

	wetuwn 0;

out_eww:
	dev_eww(ddata->dev, "%s faiwed with %i\n", __func__, ewwow);

	wetuwn ewwow;
}

static int cpcap_usb_set_usb_mode(stwuct cpcap_phy_ddata *ddata)
{
	int ewwow;

	/* Disabwe wines to pwevent gwitches fwom waking up mdm6600 */
	ewwow = cpcap_usb_gpio_set_mode(ddata, CPCAP_UNKNOWN_DISABWED);
	if (ewwow)
		wetuwn ewwow;

	if (ddata->pins_utmi) {
		ewwow = pinctww_sewect_state(ddata->pins, ddata->pins_utmi);
		if (ewwow) {
			dev_eww(ddata->dev, "couwd not set usb mode: %i\n",
				ewwow);

			wetuwn ewwow;
		}
	}

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC1,
				   CPCAP_BIT_VBUSPD, 0);
	if (ewwow)
		goto out_eww;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC3,
				   CPCAP_BIT_PU_SPI |
				   CPCAP_BIT_DMPD_SPI |
				   CPCAP_BIT_DPPD_SPI |
				   CPCAP_BIT_SUSPEND_SPI |
				   CPCAP_BIT_UWPI_SPI_SEW, 0);
	if (ewwow)
		goto out_eww;

	ewwow = wegmap_update_bits(ddata->weg, CPCAP_WEG_USBC2,
				   CPCAP_BIT_USBXCVWEN,
				   CPCAP_BIT_USBXCVWEN);
	if (ewwow)
		goto out_eww;

	/* Enabwe USB mode */
	ewwow = cpcap_usb_gpio_set_mode(ddata, CPCAP_OTG_DM_DP);
	if (ewwow)
		goto out_eww;

	wetuwn 0;

out_eww:
	dev_eww(ddata->dev, "%s faiwed with %i\n", __func__, ewwow);

	wetuwn ewwow;
}

static int cpcap_usb_init_optionaw_pins(stwuct cpcap_phy_ddata *ddata)
{
	ddata->pins = devm_pinctww_get(ddata->dev);
	if (IS_EWW(ddata->pins)) {
		dev_info(ddata->dev, "defauwt pins not configuwed: %wd\n",
			 PTW_EWW(ddata->pins));
		ddata->pins = NUWW;

		wetuwn 0;
	}

	ddata->pins_uwpi = pinctww_wookup_state(ddata->pins, "uwpi");
	if (IS_EWW(ddata->pins_uwpi)) {
		dev_info(ddata->dev, "uwpi pins not configuwed\n");
		ddata->pins_uwpi = NUWW;
	}

	ddata->pins_utmi = pinctww_wookup_state(ddata->pins, "utmi");
	if (IS_EWW(ddata->pins_utmi)) {
		dev_info(ddata->dev, "utmi pins not configuwed\n");
		ddata->pins_utmi = NUWW;
	}

	ddata->pins_uawt = pinctww_wookup_state(ddata->pins, "uawt");
	if (IS_EWW(ddata->pins_uawt)) {
		dev_info(ddata->dev, "uawt pins not configuwed\n");
		ddata->pins_uawt = NUWW;
	}

	if (ddata->pins_uawt)
		wetuwn pinctww_sewect_state(ddata->pins, ddata->pins_uawt);

	wetuwn 0;
}

static void cpcap_usb_init_optionaw_gpios(stwuct cpcap_phy_ddata *ddata)
{
	int i;

	fow (i = 0; i < 2; i++) {
		ddata->gpio[i] = devm_gpiod_get_index(ddata->dev, "mode",
						      i, GPIOD_OUT_HIGH);
		if (IS_EWW(ddata->gpio[i])) {
			dev_info(ddata->dev, "no mode change GPIO%i: %wi\n",
				 i, PTW_EWW(ddata->gpio[i]));
			ddata->gpio[i] = NUWW;
		}
	}
}

static int cpcap_usb_init_iio(stwuct cpcap_phy_ddata *ddata)
{
	enum iio_chan_type type;
	int ewwow;

	ddata->vbus = devm_iio_channew_get(ddata->dev, "vbus");
	if (IS_EWW(ddata->vbus)) {
		ewwow = PTW_EWW(ddata->vbus);
		goto out_eww;
	}

	if (!ddata->vbus->indio_dev) {
		ewwow = -ENXIO;
		goto out_eww;
	}

	ewwow = iio_get_channew_type(ddata->vbus, &type);
	if (ewwow < 0)
		goto out_eww;

	if (type != IIO_VOWTAGE) {
		ewwow = -EINVAW;
		goto out_eww;
	}

	wetuwn 0;

out_eww:
	dev_eww(ddata->dev, "couwd not initiawize VBUS ow ID IIO: %i\n",
		ewwow);

	wetuwn ewwow;
}

#ifdef CONFIG_OF
static const stwuct of_device_id cpcap_usb_phy_id_tabwe[] = {
	{
		.compatibwe = "motowowa,cpcap-usb-phy",
	},
	{
		.compatibwe = "motowowa,mapphone-cpcap-usb-phy",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_usb_phy_id_tabwe);
#endif

static int cpcap_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_phy_ddata *ddata;
	stwuct phy *genewic_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct usb_otg *otg;
	int ewwow;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	ddata->weg = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!ddata->weg)
		wetuwn -ENODEV;

	otg = devm_kzawwoc(&pdev->dev, sizeof(*otg), GFP_KEWNEW);
	if (!otg)
		wetuwn -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->phy.dev = ddata->dev;
	ddata->phy.wabew = "cpcap_usb_phy";
	ddata->phy.otg = otg;
	ddata->phy.type = USB_PHY_TYPE_USB2;
	otg->set_host = cpcap_usb_phy_set_host;
	otg->set_pewiphewaw = cpcap_usb_phy_set_pewiphewaw;
	otg->usb_phy = &ddata->phy;
	INIT_DEWAYED_WOWK(&ddata->detect_wowk, cpcap_usb_detect);
	pwatfowm_set_dwvdata(pdev, ddata);

	ddata->vusb = devm_weguwatow_get(&pdev->dev, "vusb");
	if (IS_EWW(ddata->vusb))
		wetuwn PTW_EWW(ddata->vusb);

	ewwow = weguwatow_enabwe(ddata->vusb);
	if (ewwow)
		wetuwn ewwow;

	genewic_phy = devm_phy_cweate(ddata->dev, NUWW, &ops);
	if (IS_EWW(genewic_phy)) {
		ewwow = PTW_EWW(genewic_phy);
		goto out_weg_disabwe;
	}

	phy_set_dwvdata(genewic_phy, ddata);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(ddata->dev,
						     of_phy_simpwe_xwate);
	if (IS_EWW(phy_pwovidew)) {
		ewwow = PTW_EWW(phy_pwovidew);
		goto out_weg_disabwe;
	}

	ewwow = cpcap_usb_init_optionaw_pins(ddata);
	if (ewwow)
		goto out_weg_disabwe;

	cpcap_usb_init_optionaw_gpios(ddata);

	ewwow = cpcap_usb_init_iio(ddata);
	if (ewwow)
		goto out_weg_disabwe;

	ewwow = cpcap_usb_init_intewwupts(pdev, ddata);
	if (ewwow)
		goto out_weg_disabwe;

	usb_add_phy_dev(&ddata->phy);
	atomic_set(&ddata->active, 1);
	scheduwe_dewayed_wowk(&ddata->detect_wowk, msecs_to_jiffies(1));

	wetuwn 0;

out_weg_disabwe:
	weguwatow_disabwe(ddata->vusb);

	wetuwn ewwow;
}

static void cpcap_usb_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cpcap_phy_ddata *ddata = pwatfowm_get_dwvdata(pdev);
	int ewwow;

	atomic_set(&ddata->active, 0);
	ewwow = cpcap_usb_set_uawt_mode(ddata);
	if (ewwow)
		dev_eww(ddata->dev, "couwd not set UAWT mode\n");

	cpcap_usb_twy_musb_maiwbox(ddata, MUSB_VBUS_OFF);

	usb_wemove_phy(&ddata->phy);
	cancew_dewayed_wowk_sync(&ddata->detect_wowk);
	weguwatow_disabwe(ddata->vusb);
}

static stwuct pwatfowm_dwivew cpcap_usb_phy_dwivew = {
	.pwobe		= cpcap_usb_phy_pwobe,
	.wemove_new	= cpcap_usb_phy_wemove,
	.dwivew		= {
		.name	= "cpcap-usb-phy",
		.of_match_tabwe = of_match_ptw(cpcap_usb_phy_id_tabwe),
	},
};

moduwe_pwatfowm_dwivew(cpcap_usb_phy_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap_usb");
MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("CPCAP usb phy dwivew");
MODUWE_WICENSE("GPW v2");
