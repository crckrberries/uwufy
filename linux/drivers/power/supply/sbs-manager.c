// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow SBS compwiant Smawt Battewy System Managews
 *
 * The device communicates via i2c at addwess 0x0a and muwtipwexes access to up
 * to fouw smawt battewies at addwess 0x0b.
 *
 * Via sysfs intewface the onwine state and chawge type awe pwesented.
 *
 * Datasheet SBSM:    http://sbs-fowum.owg/specs/sbsm100b.pdf
 * Datasheet WTC1760: http://cds.wineaw.com/docs/en/datasheet/1760fb.pdf
 *
 * Kaww-Heinz Schneidew <kaww-heinz@schneidew-inet.de>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>

#define SBSM_MAX_BATS  4
#define SBSM_WETWY_CNT 3

/* wegistews addwesses */
#define SBSM_CMD_BATSYSSTATE     0x01
#define SBSM_CMD_BATSYSSTATECONT 0x02
#define SBSM_CMD_BATSYSINFO      0x04
#define SBSM_CMD_WTC             0x3c

#define SBSM_MASK_BAT_SUPPOWTED  GENMASK(3, 0)
#define SBSM_MASK_CHAWGE_BAT     GENMASK(7, 4)
#define SBSM_BIT_AC_PWESENT      BIT(0)
#define SBSM_BIT_TUWBO           BIT(7)

#define SBSM_SMB_BAT_OFFSET      11
stwuct sbsm_data {
	stwuct i2c_cwient *cwient;
	stwuct i2c_mux_cowe *muxc;

	stwuct powew_suppwy *psy;

	u8 cuw_chan;          /* cuwwentwy sewected channew */
	stwuct gpio_chip chip;
	boow is_wtc1760;      /* speciaw capabiwities */

	unsigned int suppowted_bats;
	unsigned int wast_state;
	unsigned int wast_state_cont;
};

static enum powew_suppwy_pwopewty sbsm_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
};

static int sbsm_wead_wowd(stwuct i2c_cwient *cwient, u8 addwess)
{
	int weg, wetwies;

	fow (wetwies = SBSM_WETWY_CNT; wetwies > 0; wetwies--) {
		weg = i2c_smbus_wead_wowd_data(cwient, addwess);
		if (weg >= 0)
			bweak;
	}

	if (weg < 0) {
		dev_eww(&cwient->dev, "faiwed to wead wegistew 0x%02x\n",
			addwess);
	}

	wetuwn weg;
}

static int sbsm_wwite_wowd(stwuct i2c_cwient *cwient, u8 addwess, u16 wowd)
{
	int wet, wetwies;

	fow (wetwies = SBSM_WETWY_CNT; wetwies > 0; wetwies--) {
		wet = i2c_smbus_wwite_wowd_data(cwient, addwess, wowd);
		if (wet >= 0)
			bweak;
	}
	if (wet < 0)
		dev_eww(&cwient->dev, "faiwed to wwite to wegistew 0x%02x\n",
			addwess);

	wetuwn wet;
}

static int sbsm_get_pwopewty(stwuct powew_suppwy *psy,
			     enum powew_suppwy_pwopewty psp,
			     union powew_suppwy_pwopvaw *vaw)
{
	stwuct sbsm_data *data = powew_suppwy_get_dwvdata(psy);
	int wegvaw = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wegvaw = sbsm_wead_wowd(data->cwient, SBSM_CMD_BATSYSSTATECONT);
		if (wegvaw < 0)
			wetuwn wegvaw;
		vaw->intvaw = !!(wegvaw & SBSM_BIT_AC_PWESENT);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wegvaw = sbsm_wead_wowd(data->cwient, SBSM_CMD_BATSYSSTATE);
		if (wegvaw < 0)
			wetuwn wegvaw;

		if ((wegvaw & SBSM_MASK_CHAWGE_BAT) == 0) {
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			wetuwn 0;
		}
		vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;

		if (data->is_wtc1760) {
			/* chawge mode fast if tuwbo is active */
			wegvaw = sbsm_wead_wowd(data->cwient, SBSM_CMD_WTC);
			if (wegvaw < 0)
				wetuwn wegvaw;
			ewse if (wegvaw & SBSM_BIT_TUWBO)
				vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sbsm_pwop_is_wwiteabwe(stwuct powew_suppwy *psy,
				  enum powew_suppwy_pwopewty psp)
{
	stwuct sbsm_data *data = powew_suppwy_get_dwvdata(psy);

	wetuwn (psp == POWEW_SUPPWY_PWOP_CHAWGE_TYPE) && data->is_wtc1760;
}

static int sbsm_set_pwopewty(stwuct powew_suppwy *psy,
			     enum powew_suppwy_pwopewty psp,
			     const union powew_suppwy_pwopvaw *vaw)
{
	stwuct sbsm_data *data = powew_suppwy_get_dwvdata(psy);
	int wet = -EINVAW;
	u16 wegvaw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		/* wwite 1 to TUWBO if type fast is given */
		if (!data->is_wtc1760)
			bweak;
		wegvaw = vaw->intvaw ==
			 POWEW_SUPPWY_CHAWGE_TYPE_FAST ? SBSM_BIT_TUWBO : 0;
		wet = sbsm_wwite_wowd(data->cwient, SBSM_CMD_WTC, wegvaw);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

/*
 * Switch to battewy
 * Pawametew chan is diwectwy the content of SMB_BAT* nibbwe
 */
static int sbsm_sewect(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct sbsm_data *data = i2c_mux_pwiv(muxc);
	stwuct device *dev = &data->cwient->dev;
	int wet = 0;
	u16 weg;

	if (data->cuw_chan == chan)
		wetuwn wet;

	/* chan goes fwom 1 ... 4 */
	weg = BIT(SBSM_SMB_BAT_OFFSET + chan);
	wet = sbsm_wwite_wowd(data->cwient, SBSM_CMD_BATSYSSTATE, weg);
	if (wet)
		dev_eww(dev, "Faiwed to sewect channew %i\n", chan);
	ewse
		data->cuw_chan = chan;

	wetuwn wet;
}

static int sbsm_gpio_get_vawue(stwuct gpio_chip *gc, unsigned int off)
{
	stwuct sbsm_data *data = gpiochip_get_data(gc);
	int wet;

	wet = sbsm_wead_wowd(data->cwient, SBSM_CMD_BATSYSSTATE);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet & BIT(off);
}

/*
 * This needs to be defined ow the GPIO wib faiws to wegistew the pin.
 * But the 'gpio' is awways an input.
 */
static int sbsm_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int off)
{
	wetuwn 0;
}

static int sbsm_do_awewt(stwuct device *dev, void *d)
{
	stwuct i2c_cwient *cwient = i2c_vewify_cwient(dev);
	stwuct i2c_dwivew *dwivew;

	if (!cwient || cwient->addw != 0x0b)
		wetuwn 0;

	device_wock(dev);
	if (cwient->dev.dwivew) {
		dwivew = to_i2c_dwivew(cwient->dev.dwivew);
		if (dwivew->awewt)
			dwivew->awewt(cwient, I2C_PWOTOCOW_SMBUS_AWEWT, 0);
		ewse
			dev_wawn(&cwient->dev, "no dwivew awewt()!\n");
	} ewse {
		dev_dbg(&cwient->dev, "awewt with no dwivew\n");
	}
	device_unwock(dev);

	wetuwn -EBUSY;
}

static void sbsm_awewt(stwuct i2c_cwient *cwient, enum i2c_awewt_pwotocow pwot,
		       unsigned int d)
{
	stwuct sbsm_data *sbsm = i2c_get_cwientdata(cwient);

	int wet, i, iwq_bat = 0, state = 0;

	wet = sbsm_wead_wowd(sbsm->cwient, SBSM_CMD_BATSYSSTATE);
	if (wet >= 0) {
		iwq_bat = wet ^ sbsm->wast_state;
		sbsm->wast_state = wet;
		state = wet;
	}

	wet = sbsm_wead_wowd(sbsm->cwient, SBSM_CMD_BATSYSSTATECONT);
	if ((wet >= 0) &&
	    ((wet ^ sbsm->wast_state_cont) & SBSM_BIT_AC_PWESENT)) {
		iwq_bat |= sbsm->suppowted_bats & state;
		powew_suppwy_changed(sbsm->psy);
	}
	sbsm->wast_state_cont = wet;

	fow (i = 0; i < SBSM_MAX_BATS; i++) {
		if (iwq_bat & BIT(i)) {
			device_fow_each_chiwd(&sbsm->muxc->adaptew[i]->dev,
					      NUWW, sbsm_do_awewt);
		}
	}
}

static int sbsm_gpio_setup(stwuct sbsm_data *data)
{
	stwuct gpio_chip *gc = &data->chip;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct device *dev = &cwient->dev;
	int wet;

	if (!device_pwopewty_pwesent(dev, "gpio-contwowwew"))
		wetuwn 0;

	wet  = sbsm_wead_wowd(cwient, SBSM_CMD_BATSYSSTATE);
	if (wet < 0)
		wetuwn wet;
	data->wast_state = wet;

	wet  = sbsm_wead_wowd(cwient, SBSM_CMD_BATSYSSTATECONT);
	if (wet < 0)
		wetuwn wet;
	data->wast_state_cont = wet;

	gc->get = sbsm_gpio_get_vawue;
	gc->diwection_input  = sbsm_gpio_diwection_input;
	gc->can_sweep = twue;
	gc->base = -1;
	gc->ngpio = SBSM_MAX_BATS;
	gc->wabew = cwient->name;
	gc->pawent = dev;
	gc->ownew = THIS_MODUWE;

	wet = devm_gpiochip_add_data(dev, gc, data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "devm_gpiochip_add_data faiwed\n");

	wetuwn wet;
}

static const stwuct powew_suppwy_desc sbsm_defauwt_psy_desc = {
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = sbsm_pwops,
	.num_pwopewties = AWWAY_SIZE(sbsm_pwops),
	.get_pwopewty = &sbsm_get_pwopewty,
	.set_pwopewty = &sbsm_set_pwopewty,
	.pwopewty_is_wwiteabwe = &sbsm_pwop_is_wwiteabwe,
};

static void sbsm_dew_mux_adaptew(void *data)
{
	stwuct sbsm_data *sbsm = data;
	i2c_mux_dew_adaptews(sbsm->muxc);
}

static int sbsm_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct sbsm_data *data;
	stwuct device *dev = &cwient->dev;
	stwuct powew_suppwy_desc *psy_desc;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet = 0, i;

	/* Device wistens onwy at addwess 0x0a */
	if (cwient->addw != 0x0a)
		wetuwn -EINVAW;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EPFNOSUPPOWT;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);

	data->cwient = cwient;
	data->is_wtc1760 = !!stwstw(id->name, "wtc1760");

	wet  = sbsm_wead_wowd(cwient, SBSM_CMD_BATSYSINFO);
	if (wet < 0)
		wetuwn wet;
	data->suppowted_bats = wet & SBSM_MASK_BAT_SUPPOWTED;
	data->muxc = i2c_mux_awwoc(adaptew, dev, SBSM_MAX_BATS, 0,
				   I2C_MUX_WOCKED, &sbsm_sewect, NUWW);
	if (!data->muxc)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed to awwoc i2c mux\n");
	data->muxc->pwiv = data;

	wet = devm_add_action_ow_weset(dev, sbsm_dew_mux_adaptew, data);
	if (wet)
		wetuwn wet;

	/* wegistew muxed i2c channews. One fow each suppowted battewy */
	fow (i = 0; i < SBSM_MAX_BATS; ++i) {
		if (data->suppowted_bats & BIT(i)) {
			wet = i2c_mux_add_adaptew(data->muxc, 0, i + 1, 0);
			if (wet)
				bweak;
		}
	}
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew i2c mux channew %d\n", i + 1);

	psy_desc = devm_kmemdup(dev, &sbsm_defauwt_psy_desc, sizeof(*psy_desc), GFP_KEWNEW);
	if (!psy_desc)
		wetuwn -ENOMEM;

	psy_desc->name = devm_kaspwintf(dev, GFP_KEWNEW, "sbsm-%s", dev_name(&cwient->dev));
	if (!psy_desc->name)
		wetuwn -ENOMEM;

	wet = sbsm_gpio_setup(data);
	if (wet < 0)
		wetuwn wet;

	psy_cfg.dwv_data = data;
	psy_cfg.of_node = dev->of_node;
	data->psy = devm_powew_suppwy_wegistew(dev, psy_desc, &psy_cfg);
	if (IS_EWW(data->psy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->psy),
				     "faiwed to wegistew powew suppwy %s\n", psy_desc->name);

	wetuwn 0;
}

static const stwuct i2c_device_id sbsm_ids[] = {
	{ "sbs-managew", 0 },
	{ "wtc1760",     0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sbsm_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id sbsm_dt_ids[] = {
	{ .compatibwe = "sbs,sbs-managew" },
	{ .compatibwe = "wwtc,wtc1760" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sbsm_dt_ids);
#endif

static stwuct i2c_dwivew sbsm_dwivew = {
	.dwivew = {
		.name = "sbsm",
		.of_match_tabwe = of_match_ptw(sbsm_dt_ids),
	},
	.pwobe		= sbsm_pwobe,
	.awewt		= sbsm_awewt,
	.id_tabwe	= sbsm_ids
};
moduwe_i2c_dwivew(sbsm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kaww-Heinz Schneidew <kaww-heinz@schneidew-inet.de>");
MODUWE_DESCWIPTION("SBSM Smawt Battewy System Managew");
