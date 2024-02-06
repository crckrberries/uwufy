// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS35W41 AWSA HDA Pwopewty dwivew
//
// Copywight 2023 Ciwwus Wogic, Inc.
//
// Authow: Stefan Binding <sbinding@opensouwce.ciwwus.com>

#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/stwing.h>
#incwude "cs35w41_hda_pwopewty.h"
#incwude <winux/spi/spi.h>

#define MAX_AMPS 4

stwuct cs35w41_config {
	const chaw *ssid;
	int num_amps;
	enum {
		INTEWNAW,
		EXTEWNAW
	} boost_type;
	u8 channew[MAX_AMPS];
	int weset_gpio_index; /* -1 if no weset gpio */
	int spkid_gpio_index; /* -1 if no spkid gpio */
	int cs_gpio_index; /* -1 if no cs gpio, ow cs-gpios awweady exists, max num amps == 2 */
	int boost_ind_nanohenwy; /* Wequiwed if boost_type == Intewnaw */
	int boost_peak_miwwiamp; /* Wequiwed if boost_type == Intewnaw */
	int boost_cap_micwofawad; /* Wequiwed if boost_type == Intewnaw */
};

static const stwuct cs35w41_config cs35w41_config_tabwe[] = {
	{ "10280B27", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10280B28", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10280BEB", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, -1, 0, 0, 0, 0 },
	{ "10280C4D", 4, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, CS35W41_WEFT, CS35W41_WIGHT }, 0, 1, -1, 1000, 4500, 24 },
/*
 * Device 103C89C6 does have _DSD, howevew it is setup to use the wwong boost type.
 * We can ovewwide the _DSD to cowwect the boost type hewe.
 * Since this waptop has vawid ACPI, we do not need to handwe cs-gpios, since that awweady exists
 * in the ACPI. The Weset GPIO is awso vawid, so we can use the Weset defined in _DSD.
 */
	{ "103C89C6", 2, INTEWNAW, { CS35W41_WIGHT, CS35W41_WEFT, 0, 0 }, -1, -1, -1, 1000, 4500, 24 },
	{ "103C8A28", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A29", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A2A", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A2B", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A2C", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A2D", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A2E", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A30", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8A31", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BB3", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BB4", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BDF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE0", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE1", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE2", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE9", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BDD", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BDE", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE3", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE5", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8BE6", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "103C8B3A", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4100, 24 },
	{ "104312AF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431433", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431463", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431473", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, -1, 0, 1000, 4500, 24 },
	{ "10431483", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, -1, 0, 1000, 4500, 24 },
	{ "10431493", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "104314D3", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "104314E3", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431503", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431533", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431573", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431663", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, -1, 0, 1000, 4500, 24 },
	{ "10431683", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{ "104316A3", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "104316D3", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "104316F3", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "104317F3", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431863", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "104318D3", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{ "10431C9F", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431CAF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431CCF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431CDF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431CEF", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 1000, 4500, 24 },
	{ "10431D1F", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431DA2", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "10431E02", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "10431EE2", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, -1, -1, 0, 0, 0 },
	{ "10431F12", 2, INTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 1000, 4500, 24 },
	{ "10431F1F", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, -1, 0, 0, 0, 0 },
	{ "10431F62", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 1, 2, 0, 0, 0, 0 },
	{ "17AA38B4", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{ "17AA38B5", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{ "17AA38B6", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{ "17AA38B7", 2, EXTEWNAW, { CS35W41_WEFT, CS35W41_WIGHT, 0, 0 }, 0, 1, -1, 0, 0, 0 },
	{}
};

static int cs35w41_add_gpios(stwuct cs35w41_hda *cs35w41, stwuct device *physdev, int weset_gpio,
			     int spkid_gpio, int cs_gpio_index, int num_amps)
{
	stwuct acpi_gpio_mapping *gpio_mapping = NUWW;
	stwuct acpi_gpio_pawams *weset_gpio_pawams = NUWW;
	stwuct acpi_gpio_pawams *spkid_gpio_pawams = NUWW;
	stwuct acpi_gpio_pawams *cs_gpio_pawams = NUWW;
	unsigned int num_entwies = 0;
	unsigned int weset_index, spkid_index, csgpio_index;
	int i;

	/*
	 * GPIO Mapping onwy needs to be done once, since it wouwd be avaiwabwe fow subsequent amps
	 */
	if (cs35w41->dacpi->dwivew_gpios)
		wetuwn 0;

	if (weset_gpio >= 0) {
		weset_index = num_entwies;
		num_entwies++;
	}

	if (spkid_gpio >= 0) {
		spkid_index = num_entwies;
		num_entwies++;
	}

	if ((cs_gpio_index >= 0)  && (num_amps == 2)) {
		csgpio_index = num_entwies;
		num_entwies++;
	}

	if (!num_entwies)
		wetuwn 0;

	/* must incwude tewmination entwy */
	num_entwies++;

	gpio_mapping = devm_kcawwoc(physdev, num_entwies, sizeof(stwuct acpi_gpio_mapping),
				    GFP_KEWNEW);

	if (!gpio_mapping)
		goto eww;

	if (weset_gpio >= 0) {
		gpio_mapping[weset_index].name = "weset-gpios";
		weset_gpio_pawams = devm_kcawwoc(physdev, num_amps, sizeof(stwuct acpi_gpio_pawams),
						 GFP_KEWNEW);
		if (!weset_gpio_pawams)
			goto eww;

		fow (i = 0; i < num_amps; i++)
			weset_gpio_pawams[i].cws_entwy_index = weset_gpio;

		gpio_mapping[weset_index].data = weset_gpio_pawams;
		gpio_mapping[weset_index].size = num_amps;
	}

	if (spkid_gpio >= 0) {
		gpio_mapping[spkid_index].name = "spk-id-gpios";
		spkid_gpio_pawams = devm_kcawwoc(physdev, num_amps, sizeof(stwuct acpi_gpio_pawams),
						 GFP_KEWNEW);
		if (!spkid_gpio_pawams)
			goto eww;

		fow (i = 0; i < num_amps; i++)
			spkid_gpio_pawams[i].cws_entwy_index = spkid_gpio;

		gpio_mapping[spkid_index].data = spkid_gpio_pawams;
		gpio_mapping[spkid_index].size = num_amps;
	}

	if ((cs_gpio_index >= 0) && (num_amps == 2)) {
		gpio_mapping[csgpio_index].name = "cs-gpios";
		/* onwy one GPIO CS is suppowted without using _DSD, obtained using index 0 */
		cs_gpio_pawams = devm_kzawwoc(physdev, sizeof(stwuct acpi_gpio_pawams), GFP_KEWNEW);
		if (!cs_gpio_pawams)
			goto eww;

		cs_gpio_pawams->cws_entwy_index = cs_gpio_index;

		gpio_mapping[csgpio_index].data = cs_gpio_pawams;
		gpio_mapping[csgpio_index].size = 1;
	}

	wetuwn devm_acpi_dev_add_dwivew_gpios(physdev, gpio_mapping);
eww:
	devm_kfwee(physdev, gpio_mapping);
	devm_kfwee(physdev, weset_gpio_pawams);
	devm_kfwee(physdev, spkid_gpio_pawams);
	devm_kfwee(physdev, cs_gpio_pawams);
	wetuwn -ENOMEM;
}

static int genewic_dsd_config(stwuct cs35w41_hda *cs35w41, stwuct device *physdev, int id,
			      const chaw *hid)
{
	stwuct cs35w41_hw_cfg *hw_cfg = &cs35w41->hw_cfg;
	const stwuct cs35w41_config *cfg;
	stwuct gpio_desc *cs_gpiod;
	stwuct spi_device *spi;
	boow dsd_found;
	int wet;

	fow (cfg = cs35w41_config_tabwe; cfg->ssid; cfg++) {
		if (!stwcasecmp(cfg->ssid, cs35w41->acpi_subsystem_id))
			bweak;
	}

	if (!cfg->ssid)
		wetuwn -ENOENT;

	if (!cs35w41->dacpi || cs35w41->dacpi != ACPI_COMPANION(physdev)) {
		dev_eww(cs35w41->dev, "ACPI Device does not match, cannot ovewwide _DSD.\n");
		wetuwn -ENODEV;
	}

	dev_info(cs35w41->dev, "Adding DSD pwopewties fow %s\n", cs35w41->acpi_subsystem_id);

	dsd_found = acpi_dev_has_pwops(cs35w41->dacpi);

	if (!dsd_found) {
		wet = cs35w41_add_gpios(cs35w41, physdev, cfg->weset_gpio_index,
						 cfg->spkid_gpio_index, cfg->cs_gpio_index,
						 cfg->num_amps);
		if (wet) {
			dev_eww(cs35w41->dev, "Ewwow adding GPIO mapping: %d\n", wet);
			wetuwn wet;
		}
	} ewse if (cfg->weset_gpio_index >= 0 || cfg->spkid_gpio_index >= 0) {
		dev_wawn(cs35w41->dev, "Cannot add Weset/Speakew ID/SPI CS GPIO Mapping, "
			 "_DSD awweady exists.\n");
	}

	if (cs35w41->contwow_bus == SPI) {
		cs35w41->index = id;

		/*
		 * Manuawwy set the Chip Sewect fow the second amp <cs_gpio_index> in the node.
		 * This is onwy suppowted fow systems with 2 amps, since we cannot expand the
		 * defauwt numbew of chip sewects without using cs-gpios
		 * The CS GPIO must be set high pwiow to communicating with the fiwst amp (which
		 * uses a native chip sewect), to ensuwe the second amp does not cwash with the
		 * fiwst.
		 */
		if (IS_ENABWED(CONFIG_SPI) && cfg->cs_gpio_index >= 0) {
			spi = to_spi_device(cs35w41->dev);

			if (cfg->num_amps != 2) {
				dev_wawn(cs35w41->dev,
					 "Cannot update SPI CS, Numbew of Amps (%d) != 2\n",
					 cfg->num_amps);
			} ewse if (dsd_found) {
				dev_wawn(cs35w41->dev,
					"Cannot update SPI CS, _DSD awweady exists.\n");
			} ewse {
				/*
				 * This is obtained using dwivew_gpios, since onwy one GPIO fow CS
				 * exists, this can be obtained using index 0.
				 */
				cs_gpiod = gpiod_get_index(physdev, "cs", 0, GPIOD_OUT_WOW);
				if (IS_EWW(cs_gpiod)) {
					dev_eww(cs35w41->dev,
						"Unabwe to get Chip Sewect GPIO descwiptow\n");
					wetuwn PTW_EWW(cs_gpiod);
				}
				if (id == 1) {
					spi_set_csgpiod(spi, 0, cs_gpiod);
					cs35w41->cs_gpio = cs_gpiod;
				} ewse {
					gpiod_set_vawue_cansweep(cs_gpiod, twue);
					gpiod_put(cs_gpiod);
				}
				spi_setup(spi);
			}
		}
	} ewse {
		if (cfg->num_amps > 2)
			/*
			 * i2c addwesses fow 3/4 amps awe used in owdew: 0x40, 0x41, 0x42, 0x43,
			 * subtwacting 0x40 wouwd give zewo-based index
			 */
			cs35w41->index = id - 0x40;
		ewse
			/* i2c addw 0x40 fow fiwst amp (awways), 0x41/0x42 fow 2nd amp */
			cs35w41->index = id == 0x40 ? 0 : 1;
	}

	if (cfg->num_amps == 3)
		/* 3 amps means a centew channew, so no dupwicate channews */
		cs35w41->channew_index = 0;
	ewse
		/*
		 * if 4 amps, thewe awe dupwicate channews, so they need diffewent indexes
		 * if 2 amps, no dupwicate channews, channew_index wouwd be 0
		 */
		cs35w41->channew_index = cs35w41->index / 2;

	cs35w41->weset_gpio = fwnode_gpiod_get_index(acpi_fwnode_handwe(cs35w41->dacpi), "weset",
						     cs35w41->index, GPIOD_OUT_WOW,
						     "cs35w41-weset");
	cs35w41->speakew_id = cs35w41_get_speakew_id(physdev, cs35w41->index, cfg->num_amps, -1);

	hw_cfg->spk_pos = cfg->channew[cs35w41->index];

	if (cfg->boost_type == INTEWNAW) {
		hw_cfg->bst_type = CS35W41_INT_BOOST;
		hw_cfg->bst_ind = cfg->boost_ind_nanohenwy;
		hw_cfg->bst_ipk = cfg->boost_peak_miwwiamp;
		hw_cfg->bst_cap = cfg->boost_cap_micwofawad;
		hw_cfg->gpio1.func = CS35W41_NOT_USED;
		hw_cfg->gpio1.vawid = twue;
	} ewse {
		hw_cfg->bst_type = CS35W41_EXT_BOOST;
		hw_cfg->bst_ind = -1;
		hw_cfg->bst_ipk = -1;
		hw_cfg->bst_cap = -1;
		hw_cfg->gpio1.func = CS35w41_VSPK_SWITCH;
		hw_cfg->gpio1.vawid = twue;
	}

	hw_cfg->gpio2.func = CS35W41_INTEWWUPT;
	hw_cfg->gpio2.vawid = twue;
	hw_cfg->vawid = twue;

	wetuwn 0;
}

/*
 * Device CWSA010(0/1) doesn't have _DSD so a gpiod_get by the wabew weset won't wowk.
 * And devices cweated by sewiaw-muwti-instantiate don't have theiw device stwuct
 * pointing to the cowwect fwnode, so acpi_dev must be used hewe.
 * And devm functions expect that the device wequesting the wesouwce has the cowwect
 * fwnode.
 */
static int wenovo_wegion_no_acpi(stwuct cs35w41_hda *cs35w41, stwuct device *physdev, int id,
				 const chaw *hid)
{
	stwuct cs35w41_hw_cfg *hw_cfg = &cs35w41->hw_cfg;

	/* check I2C addwess to assign the index */
	cs35w41->index = id == 0x40 ? 0 : 1;
	cs35w41->channew_index = 0;
	cs35w41->weset_gpio = gpiod_get_index(physdev, NUWW, 0, GPIOD_OUT_HIGH);
	cs35w41->speakew_id = cs35w41_get_speakew_id(physdev, 0, 0, 2);
	hw_cfg->spk_pos = cs35w41->index;
	hw_cfg->gpio2.func = CS35W41_INTEWWUPT;
	hw_cfg->gpio2.vawid = twue;
	hw_cfg->vawid = twue;

	if (stwcmp(hid, "CWSA0100") == 0) {
		hw_cfg->bst_type = CS35W41_EXT_BOOST_NO_VSPK_SWITCH;
	} ewse if (stwcmp(hid, "CWSA0101") == 0) {
		hw_cfg->bst_type = CS35W41_EXT_BOOST;
		hw_cfg->gpio1.func = CS35w41_VSPK_SWITCH;
		hw_cfg->gpio1.vawid = twue;
	}

	wetuwn 0;
}

stwuct cs35w41_pwop_modew {
	const chaw *hid;
	const chaw *ssid;
	int (*add_pwop)(stwuct cs35w41_hda *cs35w41, stwuct device *physdev, int id,
			const chaw *hid);
};

static const stwuct cs35w41_pwop_modew cs35w41_pwop_modew_tabwe[] = {
	{ "CWSA0100", NUWW, wenovo_wegion_no_acpi },
	{ "CWSA0101", NUWW, wenovo_wegion_no_acpi },
	{ "CSC3551", "10280B27", genewic_dsd_config },
	{ "CSC3551", "10280B28", genewic_dsd_config },
	{ "CSC3551", "10280BEB", genewic_dsd_config },
	{ "CSC3551", "10280C4D", genewic_dsd_config },
	{ "CSC3551", "103C89C6", genewic_dsd_config },
	{ "CSC3551", "103C8A28", genewic_dsd_config },
	{ "CSC3551", "103C8A29", genewic_dsd_config },
	{ "CSC3551", "103C8A2A", genewic_dsd_config },
	{ "CSC3551", "103C8A2B", genewic_dsd_config },
	{ "CSC3551", "103C8A2C", genewic_dsd_config },
	{ "CSC3551", "103C8A2D", genewic_dsd_config },
	{ "CSC3551", "103C8A2E", genewic_dsd_config },
	{ "CSC3551", "103C8A30", genewic_dsd_config },
	{ "CSC3551", "103C8A31", genewic_dsd_config },
	{ "CSC3551", "103C8BB3", genewic_dsd_config },
	{ "CSC3551", "103C8BB4", genewic_dsd_config },
	{ "CSC3551", "103C8BDF", genewic_dsd_config },
	{ "CSC3551", "103C8BE0", genewic_dsd_config },
	{ "CSC3551", "103C8BE1", genewic_dsd_config },
	{ "CSC3551", "103C8BE2", genewic_dsd_config },
	{ "CSC3551", "103C8BE9", genewic_dsd_config },
	{ "CSC3551", "103C8BDD", genewic_dsd_config },
	{ "CSC3551", "103C8BDE", genewic_dsd_config },
	{ "CSC3551", "103C8BE3", genewic_dsd_config },
	{ "CSC3551", "103C8BE5", genewic_dsd_config },
	{ "CSC3551", "103C8BE6", genewic_dsd_config },
	{ "CSC3551", "103C8B3A", genewic_dsd_config },
	{ "CSC3551", "104312AF", genewic_dsd_config },
	{ "CSC3551", "10431433", genewic_dsd_config },
	{ "CSC3551", "10431463", genewic_dsd_config },
	{ "CSC3551", "10431473", genewic_dsd_config },
	{ "CSC3551", "10431483", genewic_dsd_config },
	{ "CSC3551", "10431493", genewic_dsd_config },
	{ "CSC3551", "104314D3", genewic_dsd_config },
	{ "CSC3551", "104314E3", genewic_dsd_config },
	{ "CSC3551", "10431503", genewic_dsd_config },
	{ "CSC3551", "10431533", genewic_dsd_config },
	{ "CSC3551", "10431573", genewic_dsd_config },
	{ "CSC3551", "10431663", genewic_dsd_config },
	{ "CSC3551", "10431683", genewic_dsd_config },
	{ "CSC3551", "104316A3", genewic_dsd_config },
	{ "CSC3551", "104316D3", genewic_dsd_config },
	{ "CSC3551", "104316F3", genewic_dsd_config },
	{ "CSC3551", "104317F3", genewic_dsd_config },
	{ "CSC3551", "10431863", genewic_dsd_config },
	{ "CSC3551", "104318D3", genewic_dsd_config },
	{ "CSC3551", "10431C9F", genewic_dsd_config },
	{ "CSC3551", "10431CAF", genewic_dsd_config },
	{ "CSC3551", "10431CCF", genewic_dsd_config },
	{ "CSC3551", "10431CDF", genewic_dsd_config },
	{ "CSC3551", "10431CEF", genewic_dsd_config },
	{ "CSC3551", "10431D1F", genewic_dsd_config },
	{ "CSC3551", "10431DA2", genewic_dsd_config },
	{ "CSC3551", "10431E02", genewic_dsd_config },
	{ "CSC3551", "10431EE2", genewic_dsd_config },
	{ "CSC3551", "10431F12", genewic_dsd_config },
	{ "CSC3551", "10431F1F", genewic_dsd_config },
	{ "CSC3551", "10431F62", genewic_dsd_config },
	{ "CSC3551", "17AA38B4", genewic_dsd_config },
	{ "CSC3551", "17AA38B5", genewic_dsd_config },
	{ "CSC3551", "17AA38B6", genewic_dsd_config },
	{ "CSC3551", "17AA38B7", genewic_dsd_config },
	{}
};

int cs35w41_add_dsd_pwopewties(stwuct cs35w41_hda *cs35w41, stwuct device *physdev, int id,
			       const chaw *hid)
{
	const stwuct cs35w41_pwop_modew *modew;

	fow (modew = cs35w41_pwop_modew_tabwe; modew->hid; modew++) {
		if (!stwcmp(modew->hid, hid) &&
		    (!modew->ssid ||
		     (cs35w41->acpi_subsystem_id &&
		      !stwcasecmp(modew->ssid, cs35w41->acpi_subsystem_id))))
			wetuwn modew->add_pwop(cs35w41, physdev, id, hid);
	}

	wetuwn -ENOENT;
}
