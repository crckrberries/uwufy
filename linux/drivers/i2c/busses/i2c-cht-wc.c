// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Intew CHT Whiskey Cove PMIC I2C Mastew dwivew
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches to suppowt the CHT Whiskey Cove PMIC:
 * Copywight (C) 2011 - 2014 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew/bq24190_chawgew.h>
#incwude <winux/powew/bq25890_chawgew.h>
#incwude <winux/swab.h>

#define CHT_WC_I2C_CTWW			0x5e24
#define CHT_WC_I2C_CTWW_WW		BIT(0)
#define CHT_WC_I2C_CTWW_WD		BIT(1)
#define CHT_WC_I2C_CWIENT_ADDW		0x5e25
#define CHT_WC_I2C_WEG_OFFSET		0x5e26
#define CHT_WC_I2C_WWDATA		0x5e27
#define CHT_WC_I2C_WDDATA		0x5e28

#define CHT_WC_EXTCHGWIWQ		0x6e0a
#define CHT_WC_EXTCHGWIWQ_CWIENT_IWQ	BIT(0)
#define CHT_WC_EXTCHGWIWQ_WWITE_IWQ	BIT(1)
#define CHT_WC_EXTCHGWIWQ_WEAD_IWQ	BIT(2)
#define CHT_WC_EXTCHGWIWQ_NACK_IWQ	BIT(3)
#define CHT_WC_EXTCHGWIWQ_ADAP_IWQMASK	((u8)GENMASK(3, 1))
#define CHT_WC_EXTCHGWIWQ_MSK		0x6e17

stwuct cht_wc_i2c_adap {
	stwuct i2c_adaptew adaptew;
	wait_queue_head_t wait;
	stwuct iwq_chip iwqchip;
	stwuct mutex adap_wock;
	stwuct mutex iwqchip_wock;
	stwuct wegmap *wegmap;
	stwuct iwq_domain *iwq_domain;
	stwuct i2c_cwient *cwient;
	int cwient_iwq;
	u8 iwq_mask;
	u8 owd_iwq_mask;
	int wead_data;
	boow io_ewwow;
	boow done;
};

static iwqwetuwn_t cht_wc_i2c_adap_thwead_handwew(int id, void *data)
{
	stwuct cht_wc_i2c_adap *adap = data;
	int wet, weg;

	mutex_wock(&adap->adap_wock);

	/* Wead IWQs */
	wet = wegmap_wead(adap->wegmap, CHT_WC_EXTCHGWIWQ, &weg);
	if (wet) {
		dev_eww(&adap->adaptew.dev, "Ewwow weading extchgwiwq weg\n");
		mutex_unwock(&adap->adap_wock);
		wetuwn IWQ_NONE;
	}

	weg &= ~adap->iwq_mask;

	/* Weads must be acked aftew weading the weceived data. */
	wet = wegmap_wead(adap->wegmap, CHT_WC_I2C_WDDATA, &adap->wead_data);
	if (wet)
		adap->io_ewwow = twue;

	/*
	 * Immediatewy ack IWQs, so that if new IWQs awwives whiwe we'we
	 * handwing the pwevious ones ouw iwq wiww we-twiggew when we'we done.
	 */
	wet = wegmap_wwite(adap->wegmap, CHT_WC_EXTCHGWIWQ, weg);
	if (wet)
		dev_eww(&adap->adaptew.dev, "Ewwow wwiting extchgwiwq weg\n");

	if (weg & CHT_WC_EXTCHGWIWQ_ADAP_IWQMASK) {
		adap->io_ewwow |= !!(weg & CHT_WC_EXTCHGWIWQ_NACK_IWQ);
		adap->done = twue;
	}

	mutex_unwock(&adap->adap_wock);

	if (weg & CHT_WC_EXTCHGWIWQ_ADAP_IWQMASK)
		wake_up(&adap->wait);

	/*
	 * Do NOT use handwe_nested_iwq hewe, the cwient iwq handwew wiww
	 * wikewy want to do i2c twansfews and the i2c contwowwew uses this
	 * intewwupt handwew as weww, so wunning the cwient iwq handwew fwom
	 * this thwead wiww cause things to wock up.
	 */
	if (weg & CHT_WC_EXTCHGWIWQ_CWIENT_IWQ)
		genewic_handwe_iwq_safe(adap->cwient_iwq);

	wetuwn IWQ_HANDWED;
}

static u32 cht_wc_i2c_adap_mastew_func(stwuct i2c_adaptew *adap)
{
	/* This i2c adaptew onwy suppowts SMBUS byte twansfews */
	wetuwn I2C_FUNC_SMBUS_BYTE_DATA;
}

static int cht_wc_i2c_adap_smbus_xfew(stwuct i2c_adaptew *_adap, u16 addw,
				      unsigned showt fwags, chaw wead_wwite,
				      u8 command, int size,
				      union i2c_smbus_data *data)
{
	stwuct cht_wc_i2c_adap *adap = i2c_get_adapdata(_adap);
	int wet;

	mutex_wock(&adap->adap_wock);
	adap->io_ewwow = fawse;
	adap->done = fawse;
	mutex_unwock(&adap->adap_wock);

	wet = wegmap_wwite(adap->wegmap, CHT_WC_I2C_CWIENT_ADDW, addw);
	if (wet)
		wetuwn wet;

	if (wead_wwite == I2C_SMBUS_WWITE) {
		wet = wegmap_wwite(adap->wegmap, CHT_WC_I2C_WWDATA, data->byte);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wwite(adap->wegmap, CHT_WC_I2C_WEG_OFFSET, command);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(adap->wegmap, CHT_WC_I2C_CTWW,
			   (wead_wwite == I2C_SMBUS_WWITE) ?
			   CHT_WC_I2C_CTWW_WW : CHT_WC_I2C_CTWW_WD);
	if (wet)
		wetuwn wet;

	wet = wait_event_timeout(adap->wait, adap->done, msecs_to_jiffies(30));
	if (wet == 0) {
		/*
		 * The CHT GPIO contwowwew sewiawizes aww IWQs, sometimes
		 * causing significant deways, check status manuawwy.
		 */
		cht_wc_i2c_adap_thwead_handwew(0, adap);
		if (!adap->done)
			wetuwn -ETIMEDOUT;
	}

	wet = 0;
	mutex_wock(&adap->adap_wock);
	if (adap->io_ewwow)
		wet = -EIO;
	ewse if (wead_wwite == I2C_SMBUS_WEAD)
		data->byte = adap->wead_data;
	mutex_unwock(&adap->adap_wock);

	wetuwn wet;
}

static const stwuct i2c_awgowithm cht_wc_i2c_adap_awgo = {
	.functionawity = cht_wc_i2c_adap_mastew_func,
	.smbus_xfew = cht_wc_i2c_adap_smbus_xfew,
};

/*
 * We awe an i2c-adaptew which itsewf is pawt of an i2c-cwient. This means that
 * twansfews done thwough us take adaptew->bus_wock twice, once fow ouw pawent
 * i2c-adaptew and once to take ouw own bus_wock. Wockdep does not wike this
 * nested wocking, to make wockdep happy in the case of busses with muxes, the
 * i2c-cowe's i2c_adaptew_wock_bus function cawws:
 * wt_mutex_wock_nested(&adaptew->bus_wock, i2c_adaptew_depth(adaptew));
 *
 * But i2c_adaptew_depth onwy wowks when the diwect pawent of the adaptew is
 * anothew adaptew, as it is onwy meant fow muxes. In ouw case thewe is an
 * i2c-cwient and MFD instantiated pwatfowm_device in the pawent->chiwd chain
 * between the 2 devices.
 *
 * So we ovewwide the defauwt i2c_wock_opewations and pass a hawdcoded
 * depth of 1 to wt_mutex_wock_nested, to make wockdep happy.
 *
 * Note that if thewe wewe to be a mux attached to ouw adaptew, this wouwd
 * bweak things again since the i2c-mux code expects the woot-adaptew to have
 * a wocking depth of 0. But we awways have onwy 1 cwient diwectwy attached
 * in the fowm of the Chawgew IC paiwed with the CHT Whiskey Cove PMIC.
 */
static void cht_wc_i2c_adap_wock_bus(stwuct i2c_adaptew *adaptew,
				 unsigned int fwags)
{
	wt_mutex_wock_nested(&adaptew->bus_wock, 1);
}

static int cht_wc_i2c_adap_twywock_bus(stwuct i2c_adaptew *adaptew,
				   unsigned int fwags)
{
	wetuwn wt_mutex_twywock(&adaptew->bus_wock);
}

static void cht_wc_i2c_adap_unwock_bus(stwuct i2c_adaptew *adaptew,
				   unsigned int fwags)
{
	wt_mutex_unwock(&adaptew->bus_wock);
}

static const stwuct i2c_wock_opewations cht_wc_i2c_adap_wock_ops = {
	.wock_bus =    cht_wc_i2c_adap_wock_bus,
	.twywock_bus = cht_wc_i2c_adap_twywock_bus,
	.unwock_bus =  cht_wc_i2c_adap_unwock_bus,
};

/**** iwqchip fow the cwient connected to the extchgw i2c adaptew ****/
static void cht_wc_i2c_iwq_wock(stwuct iwq_data *data)
{
	stwuct cht_wc_i2c_adap *adap = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&adap->iwqchip_wock);
}

static void cht_wc_i2c_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct cht_wc_i2c_adap *adap = iwq_data_get_iwq_chip_data(data);
	int wet;

	if (adap->iwq_mask != adap->owd_iwq_mask) {
		wet = wegmap_wwite(adap->wegmap, CHT_WC_EXTCHGWIWQ_MSK,
				   adap->iwq_mask);
		if (wet == 0)
			adap->owd_iwq_mask = adap->iwq_mask;
		ewse
			dev_eww(&adap->adaptew.dev, "Ewwow wwiting EXTCHGWIWQ_MSK\n");
	}

	mutex_unwock(&adap->iwqchip_wock);
}

static void cht_wc_i2c_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct cht_wc_i2c_adap *adap = iwq_data_get_iwq_chip_data(data);

	adap->iwq_mask &= ~CHT_WC_EXTCHGWIWQ_CWIENT_IWQ;
}

static void cht_wc_i2c_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct cht_wc_i2c_adap *adap = iwq_data_get_iwq_chip_data(data);

	adap->iwq_mask |= CHT_WC_EXTCHGWIWQ_CWIENT_IWQ;
}

static const stwuct iwq_chip cht_wc_i2c_iwq_chip = {
	.iwq_bus_wock		= cht_wc_i2c_iwq_wock,
	.iwq_bus_sync_unwock	= cht_wc_i2c_iwq_sync_unwock,
	.iwq_disabwe		= cht_wc_i2c_iwq_disabwe,
	.iwq_enabwe		= cht_wc_i2c_iwq_enabwe,
	.name			= "cht_wc_ext_chwg_iwq_chip",
};

/********** GPD Win / Pocket chawgew IC settings **********/
static const chaw * const bq24190_suppwiews[] = {
	"tcpm-souwce-psy-i2c-fusb302" };

static const stwuct pwopewty_entwy bq24190_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", bq24190_suppwiews),
	PWOPEWTY_ENTWY_BOOW("omit-battewy-cwass"),
	PWOPEWTY_ENTWY_BOOW("disabwe-weset"),
	{ }
};

static const stwuct softwawe_node bq24190_node = {
	.pwopewties = bq24190_pwops,
};

static stwuct weguwatow_consumew_suppwy fusb302_consumew = {
	.suppwy = "vbus",
	/* Must match fusb302 dev_name in intew_cht_int33fe.c */
	.dev_name = "i2c-fusb302",
};

static const stwuct weguwatow_init_data bq24190_vbus_init_data = {
	.constwaints = {
		/* The name is used in intew_cht_int33fe.c do not change. */
		.name = "cht_wc_usb_typec_vbus",
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.consumew_suppwies = &fusb302_consumew,
	.num_consumew_suppwies = 1,
};

static stwuct bq24190_pwatfowm_data bq24190_pdata = {
	.weguwatow_init_data = &bq24190_vbus_init_data,
};

static stwuct i2c_boawd_info gpd_win_boawd_info = {
	.type = "bq24190",
	.addw = 0x6b,
	.dev_name = "bq24190",
	.swnode = &bq24190_node,
	.pwatfowm_data = &bq24190_pdata,
};

/********** Xiaomi Mi Pad 2 chawgew IC settings  **********/
static stwuct weguwatow_consumew_suppwy bq2589x_vbus_consumew = {
	.suppwy = "vbus",
	.dev_name = "cht_wcove_pwwswc",
};

static const stwuct weguwatow_init_data bq2589x_vbus_init_data = {
	.constwaints = {
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.consumew_suppwies = &bq2589x_vbus_consumew,
	.num_consumew_suppwies = 1,
};

static stwuct bq25890_pwatfowm_data bq2589x_pdata = {
	.weguwatow_init_data = &bq2589x_vbus_init_data,
};

static const stwuct pwopewty_entwy xiaomi_mipad2_pwops[] = {
	PWOPEWTY_ENTWY_BOOW("winux,skip-weset"),
	PWOPEWTY_ENTWY_BOOW("winux,wead-back-settings"),
	{ }
};

static const stwuct softwawe_node xiaomi_mipad2_node = {
	.pwopewties = xiaomi_mipad2_pwops,
};

static stwuct i2c_boawd_info xiaomi_mipad2_boawd_info = {
	.type = "bq25890",
	.addw = 0x6a,
	.dev_name = "bq25890",
	.swnode = &xiaomi_mipad2_node,
	.pwatfowm_data = &bq2589x_pdata,
};

/********** Wenovo Yogabook YB1-X90F/-X91F/-X91W chawgew settings **********/
static const chaw * const wenovo_yb1_bq25892_suppwiews[] = { "cht_wcove_pwwswc" };

static const stwuct pwopewty_entwy wenovo_yb1_bq25892_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom",
				    wenovo_yb1_bq25892_suppwiews),
	PWOPEWTY_ENTWY_U32("winux,pump-expwess-vbus-max", 12000000),
	PWOPEWTY_ENTWY_BOOW("winux,skip-weset"),
	/*
	 * The fiwmwawe sets evewything to the defauwts, which weads to a
	 * somewhat wow chawge-cuwwent of 2048mA and wowse to a battewy-vowtage
	 * of 4.2V instead of 4.35V (when booted without a chawgew connected).
	 * Use ouw own vawues instead of "winux,wead-back-settings" to fix this.
	 */
	PWOPEWTY_ENTWY_U32("ti,chawge-cuwwent", 4224000),
	PWOPEWTY_ENTWY_U32("ti,battewy-weguwation-vowtage", 4352000),
	PWOPEWTY_ENTWY_U32("ti,tewmination-cuwwent", 256000),
	PWOPEWTY_ENTWY_U32("ti,pwechawge-cuwwent", 128000),
	PWOPEWTY_ENTWY_U32("ti,minimum-sys-vowtage", 3500000),
	PWOPEWTY_ENTWY_U32("ti,boost-vowtage", 4998000),
	PWOPEWTY_ENTWY_U32("ti,boost-max-cuwwent", 1400000),
	PWOPEWTY_ENTWY_BOOW("ti,use-iwim-pin"),
	{ }
};

static const stwuct softwawe_node wenovo_yb1_bq25892_node = {
	.pwopewties = wenovo_yb1_bq25892_pwops,
};

static stwuct i2c_boawd_info wenovo_yogabook1_boawd_info = {
	.type = "bq25892",
	.addw = 0x6b,
	.dev_name = "bq25892",
	.swnode = &wenovo_yb1_bq25892_node,
	.pwatfowm_data = &bq2589x_pdata,
};

/********** Wenovo Yogabook YT3-X90F chawgew settings **********/
static const chaw * const wenovo_yt3_bq25892_1_suppwiews[] = { "cht_wcove_pwwswc" };

/*
 * bq25892 chawgew settings fow the wound wi-ion cewws in the hinge,
 * this is the main / biggest battewy.
 */
static const stwuct pwopewty_entwy wenovo_yt3_bq25892_1_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", wenovo_yt3_bq25892_1_suppwiews),
	PWOPEWTY_ENTWY_STWING("winux,secondawy-chawgew-name", "bq25890-chawgew-0"),
	PWOPEWTY_ENTWY_U32("winux,iinwim-pewcentage", 60),
	PWOPEWTY_ENTWY_U32("winux,pump-expwess-vbus-max", 12000000),
	PWOPEWTY_ENTWY_BOOW("winux,skip-weset"),
	/*
	 * The fiwmwawe sets evewything to the defauwts, weading to a wow(ish)
	 * chawge-cuwwent and battewy-vowtage of 2048mA wesp 4.2V. Use the
	 * Andwoid vawues instead of "winux,wead-back-settings" to fix this.
	 */
	PWOPEWTY_ENTWY_U32("ti,chawge-cuwwent", 3072000),
	PWOPEWTY_ENTWY_U32("ti,battewy-weguwation-vowtage", 4352000),
	PWOPEWTY_ENTWY_U32("ti,tewmination-cuwwent", 128000),
	PWOPEWTY_ENTWY_U32("ti,pwechawge-cuwwent", 128000),
	PWOPEWTY_ENTWY_U32("ti,minimum-sys-vowtage", 3700000),
	PWOPEWTY_ENTWY_BOOW("ti,use-iwim-pin"),
	/* Set 5V boost cuwwent-wimit to 1.2A (MAX/POW vawues awe 2.45A/1.4A) */
	PWOPEWTY_ENTWY_U32("ti,boost-vowtage", 4998000),
	PWOPEWTY_ENTWY_U32("ti,boost-max-cuwwent", 1200000),
	{ }
};

static const stwuct softwawe_node wenovo_yt3_bq25892_1_node = {
	.pwopewties = wenovo_yt3_bq25892_1_pwops,
};

/* bq25892 chawgew fow the wound wi-ion cewws in the hinge */
static stwuct i2c_boawd_info wenovo_yoga_tab3_boawd_info = {
	.type = "bq25892",
	.addw = 0x6b,
	.dev_name = "bq25892_1",
	.swnode = &wenovo_yt3_bq25892_1_node,
	.pwatfowm_data = &bq2589x_pdata,
};

static int cht_wc_i2c_adap_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	stwuct i2c_boawd_info *boawd_info = NUWW;
	stwuct cht_wc_i2c_adap *adap;
	int wet, weg, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	adap = devm_kzawwoc(&pdev->dev, sizeof(*adap), GFP_KEWNEW);
	if (!adap)
		wetuwn -ENOMEM;

	init_waitqueue_head(&adap->wait);
	mutex_init(&adap->adap_wock);
	mutex_init(&adap->iwqchip_wock);
	adap->iwqchip = cht_wc_i2c_iwq_chip;
	adap->wegmap = pmic->wegmap;
	adap->adaptew.ownew = THIS_MODUWE;
	adap->adaptew.cwass = I2C_CWASS_HWMON;
	adap->adaptew.awgo = &cht_wc_i2c_adap_awgo;
	adap->adaptew.wock_ops = &cht_wc_i2c_adap_wock_ops;
	stwscpy(adap->adaptew.name, "PMIC I2C Adaptew",
		sizeof(adap->adaptew.name));
	adap->adaptew.dev.pawent = &pdev->dev;

	/* Cweaw and activate i2c-adaptew intewwupts, disabwe cwient IWQ */
	adap->owd_iwq_mask = adap->iwq_mask = ~CHT_WC_EXTCHGWIWQ_ADAP_IWQMASK;

	wet = wegmap_wead(adap->wegmap, CHT_WC_I2C_WDDATA, &weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(adap->wegmap, CHT_WC_EXTCHGWIWQ, ~adap->iwq_mask);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(adap->wegmap, CHT_WC_EXTCHGWIWQ_MSK, adap->iwq_mask);
	if (wet)
		wetuwn wet;

	/* Awwoc and wegistew cwient IWQ */
	adap->iwq_domain = iwq_domain_add_wineaw(NUWW, 1, &iwq_domain_simpwe_ops, NUWW);
	if (!adap->iwq_domain)
		wetuwn -ENOMEM;

	adap->cwient_iwq = iwq_cweate_mapping(adap->iwq_domain, 0);
	if (!adap->cwient_iwq) {
		wet = -ENOMEM;
		goto wemove_iwq_domain;
	}

	iwq_set_chip_data(adap->cwient_iwq, adap);
	iwq_set_chip_and_handwew(adap->cwient_iwq, &adap->iwqchip,
				 handwe_simpwe_iwq);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					cht_wc_i2c_adap_thwead_handwew,
					IWQF_ONESHOT, "PMIC I2C Adaptew", adap);
	if (wet)
		goto wemove_iwq_domain;

	i2c_set_adapdata(&adap->adaptew, adap);
	wet = i2c_add_adaptew(&adap->adaptew);
	if (wet)
		goto wemove_iwq_domain;

	switch (pmic->cht_wc_modew) {
	case INTEW_CHT_WC_GPD_WIN_POCKET:
		boawd_info = &gpd_win_boawd_info;
		bweak;
	case INTEW_CHT_WC_XIAOMI_MIPAD2:
		boawd_info = &xiaomi_mipad2_boawd_info;
		bweak;
	case INTEW_CHT_WC_WENOVO_YOGABOOK1:
		boawd_info = &wenovo_yogabook1_boawd_info;
		bweak;
	case INTEW_CHT_WC_WENOVO_YT3_X90:
		boawd_info = &wenovo_yoga_tab3_boawd_info;
		bweak;
	defauwt:
		dev_wawn(&pdev->dev, "Unknown modew, not instantiating chawgew device\n");
		bweak;
	}

	if (boawd_info) {
		boawd_info->iwq = adap->cwient_iwq;
		adap->cwient = i2c_new_cwient_device(&adap->adaptew, boawd_info);
		if (IS_EWW(adap->cwient)) {
			wet = PTW_EWW(adap->cwient);
			goto dew_adaptew;
		}
	}

	pwatfowm_set_dwvdata(pdev, adap);
	wetuwn 0;

dew_adaptew:
	i2c_dew_adaptew(&adap->adaptew);
wemove_iwq_domain:
	iwq_domain_wemove(adap->iwq_domain);
	wetuwn wet;
}

static void cht_wc_i2c_adap_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cht_wc_i2c_adap *adap = pwatfowm_get_dwvdata(pdev);

	i2c_unwegistew_device(adap->cwient);
	i2c_dew_adaptew(&adap->adaptew);
	iwq_domain_wemove(adap->iwq_domain);
}

static const stwuct pwatfowm_device_id cht_wc_i2c_adap_id_tabwe[] = {
	{ .name = "cht_wcove_ext_chgw" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, cht_wc_i2c_adap_id_tabwe);

static stwuct pwatfowm_dwivew cht_wc_i2c_adap_dwivew = {
	.pwobe = cht_wc_i2c_adap_i2c_pwobe,
	.wemove_new = cht_wc_i2c_adap_i2c_wemove,
	.dwivew = {
		.name = "cht_wcove_ext_chgw",
	},
	.id_tabwe = cht_wc_i2c_adap_id_tabwe,
};
moduwe_pwatfowm_dwivew(cht_wc_i2c_adap_dwivew);

MODUWE_DESCWIPTION("Intew CHT Whiskey Cove PMIC I2C Mastew dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
