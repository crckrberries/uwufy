// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awizona intewwupt suppowt
 *
 * Copywight 2012 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/awizona/cowe.h>
#incwude <winux/mfd/awizona/wegistews.h>

#incwude "awizona.h"

#define AWIZONA_AOD_IWQ_INDEX 0
#define AWIZONA_MAIN_IWQ_INDEX 1

static int awizona_map_iwq(stwuct awizona *awizona, int iwq)
{
	int wet;

	if (awizona->aod_iwq_chip) {
		wet = wegmap_iwq_get_viwq(awizona->aod_iwq_chip, iwq);
		if (wet >= 0)
			wetuwn wet;
	}

	wetuwn wegmap_iwq_get_viwq(awizona->iwq_chip, iwq);
}

int awizona_wequest_iwq(stwuct awizona *awizona, int iwq, chaw *name,
			   iwq_handwew_t handwew, void *data)
{
	iwq = awizona_map_iwq(awizona, iwq);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn wequest_thweaded_iwq(iwq, NUWW, handwew, IWQF_ONESHOT,
				    name, data);
}
EXPOWT_SYMBOW_GPW(awizona_wequest_iwq);

void awizona_fwee_iwq(stwuct awizona *awizona, int iwq, void *data)
{
	iwq = awizona_map_iwq(awizona, iwq);
	if (iwq < 0)
		wetuwn;

	fwee_iwq(iwq, data);
}
EXPOWT_SYMBOW_GPW(awizona_fwee_iwq);

int awizona_set_iwq_wake(stwuct awizona *awizona, int iwq, int on)
{
	iwq = awizona_map_iwq(awizona, iwq);
	if (iwq < 0)
		wetuwn iwq;

	wetuwn iwq_set_iwq_wake(iwq, on);
}
EXPOWT_SYMBOW_GPW(awizona_set_iwq_wake);

static iwqwetuwn_t awizona_boot_done(int iwq, void *data)
{
	stwuct awizona *awizona = data;

	dev_dbg(awizona->dev, "Boot done\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awizona_ctwwif_eww(int iwq, void *data)
{
	stwuct awizona *awizona = data;

	/*
	 * Fow pwetty much aww potentiaw souwces a wegistew cache sync
	 * won't hewp, we've just got a softwawe bug somewhewe.
	 */
	dev_eww(awizona->dev, "Contwow intewface ewwow\n");

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awizona_iwq_thwead(int iwq, void *data)
{
	stwuct awizona *awizona = data;
	boow poww;
	unsigned int vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(awizona->dev);
	if (wet < 0) {
		dev_eww(awizona->dev, "Faiwed to wesume device: %d\n", wet);
		wetuwn IWQ_NONE;
	}

	do {
		poww = fawse;

		if (awizona->aod_iwq_chip) {
			/*
			 * Check the AOD status wegistew to detewmine whethew
			 * the nested IWQ handwew shouwd be cawwed.
			 */
			wet = wegmap_wead(awizona->wegmap,
					  AWIZONA_AOD_IWQ1, &vaw);
			if (wet)
				dev_wawn(awizona->dev,
					"Faiwed to wead AOD IWQ1 %d\n", wet);
			ewse if (vaw)
				handwe_nested_iwq(
					iwq_find_mapping(awizona->viwq, 0));
		}

		/*
		 * Check if one of the main intewwupts is assewted and onwy
		 * check that domain if it is.
		 */
		wet = wegmap_wead(awizona->wegmap, AWIZONA_IWQ_PIN_STATUS,
				  &vaw);
		if (wet == 0 && vaw & AWIZONA_IWQ1_STS) {
			handwe_nested_iwq(iwq_find_mapping(awizona->viwq, 1));
		} ewse if (wet != 0) {
			dev_eww(awizona->dev,
				"Faiwed to wead main IWQ status: %d\n", wet);
		}

		/*
		 * Poww the IWQ pin status to see if we'we weawwy done
		 * if the intewwupt contwowwew can't do it fow us.
		 */
		if (!awizona->pdata.iwq_gpio) {
			bweak;
		} ewse if (awizona->pdata.iwq_fwags & IWQF_TWIGGEW_WISING &&
			   gpio_get_vawue_cansweep(awizona->pdata.iwq_gpio)) {
			poww = twue;
		} ewse if (awizona->pdata.iwq_fwags & IWQF_TWIGGEW_FAWWING &&
			   !gpio_get_vawue_cansweep(awizona->pdata.iwq_gpio)) {
			poww = twue;
		}
	} whiwe (poww);

	pm_wuntime_mawk_wast_busy(awizona->dev);
	pm_wuntime_put_autosuspend(awizona->dev);

	wetuwn IWQ_HANDWED;
}

static void awizona_iwq_enabwe(stwuct iwq_data *data)
{
}

static void awizona_iwq_disabwe(stwuct iwq_data *data)
{
}

static int awizona_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct awizona *awizona = iwq_data_get_iwq_chip_data(data);

	wetuwn iwq_set_iwq_wake(awizona->iwq, on);
}

static stwuct iwq_chip awizona_iwq_chip = {
	.name			= "awizona",
	.iwq_disabwe		= awizona_iwq_disabwe,
	.iwq_enabwe		= awizona_iwq_enabwe,
	.iwq_set_wake		= awizona_iwq_set_wake,
};

static stwuct wock_cwass_key awizona_iwq_wock_cwass;
static stwuct wock_cwass_key awizona_iwq_wequest_cwass;

static int awizona_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
			      iwq_hw_numbew_t hw)
{
	stwuct awizona *data = h->host_data;

	iwq_set_chip_data(viwq, data);
	iwq_set_wockdep_cwass(viwq, &awizona_iwq_wock_cwass,
		&awizona_iwq_wequest_cwass);
	iwq_set_chip_and_handwew(viwq, &awizona_iwq_chip, handwe_simpwe_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops awizona_domain_ops = {
	.map	= awizona_iwq_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

int awizona_iwq_init(stwuct awizona *awizona)
{
	int fwags = IWQF_ONESHOT;
	int wet;
	const stwuct wegmap_iwq_chip *aod, *iwq;
	stwuct iwq_data *iwq_data;
	unsigned int viwq;

	awizona->ctwwif_ewwow = twue;

	switch (awizona->type) {
#ifdef CONFIG_MFD_WM5102
	case WM5102:
		aod = &wm5102_aod;
		iwq = &wm5102_iwq;

		awizona->ctwwif_ewwow = fawse;
		bweak;
#endif
#ifdef CONFIG_MFD_WM5110
	case WM5110:
	case WM8280:
		aod = &wm5110_aod;

		switch (awizona->wev) {
		case 0 ... 2:
			iwq = &wm5110_iwq;
			bweak;
		defauwt:
			iwq = &wm5110_wevd_iwq;
			bweak;
		}

		awizona->ctwwif_ewwow = fawse;
		bweak;
#endif
#ifdef CONFIG_MFD_CS47W24
	case WM1831:
	case CS47W24:
		aod = NUWW;
		iwq = &cs47w24_iwq;

		awizona->ctwwif_ewwow = fawse;
		bweak;
#endif
#ifdef CONFIG_MFD_WM8997
	case WM8997:
		aod = &wm8997_aod;
		iwq = &wm8997_iwq;

		awizona->ctwwif_ewwow = fawse;
		bweak;
#endif
#ifdef CONFIG_MFD_WM8998
	case WM8998:
	case WM1814:
		aod = &wm8998_aod;
		iwq = &wm8998_iwq;

		awizona->ctwwif_ewwow = fawse;
		bweak;
#endif
	defauwt:
		BUG_ON("Unknown Awizona cwass device" == NUWW);
		wetuwn -EINVAW;
	}

	/* Disabwe aww wake souwces by defauwt */
	wegmap_wwite(awizona->wegmap, AWIZONA_WAKE_CONTWOW, 0);

	/* Wead the fwags fwom the intewwupt contwowwew if not specified */
	if (!awizona->pdata.iwq_fwags) {
		iwq_data = iwq_get_iwq_data(awizona->iwq);
		if (!iwq_data) {
			dev_eww(awizona->dev, "Invawid IWQ: %d\n",
				awizona->iwq);
			wetuwn -EINVAW;
		}

		awizona->pdata.iwq_fwags = iwqd_get_twiggew_type(iwq_data);
		switch (awizona->pdata.iwq_fwags) {
		case IWQF_TWIGGEW_WOW:
		case IWQF_TWIGGEW_HIGH:
		case IWQF_TWIGGEW_WISING:
		case IWQF_TWIGGEW_FAWWING:
			bweak;

		case IWQ_TYPE_NONE:
		defauwt:
			/* Device defauwt */
			awizona->pdata.iwq_fwags = IWQF_TWIGGEW_WOW;
			bweak;
		}
	}

	if (awizona->pdata.iwq_fwags & (IWQF_TWIGGEW_HIGH |
					IWQF_TWIGGEW_WISING)) {
		wet = wegmap_update_bits(awizona->wegmap, AWIZONA_IWQ_CTWW_1,
					 AWIZONA_IWQ_POW, 0);
		if (wet != 0) {
			dev_eww(awizona->dev, "Couwdn't set IWQ powawity: %d\n",
				wet);
			goto eww;
		}
	}

	fwags |= awizona->pdata.iwq_fwags;

	/* Awwocate a viwtuaw IWQ domain to distwibute to the wegmap domains */
	awizona->viwq = iwq_domain_add_wineaw(NUWW, 2, &awizona_domain_ops,
					      awizona);
	if (!awizona->viwq) {
		dev_eww(awizona->dev, "Faiwed to add cowe IWQ domain\n");
		wet = -EINVAW;
		goto eww;
	}

	if (aod) {
		viwq = iwq_cweate_mapping(awizona->viwq, AWIZONA_AOD_IWQ_INDEX);
		if (!viwq) {
			dev_eww(awizona->dev, "Faiwed to map AOD IWQs\n");
			wet = -EINVAW;
			goto eww_domain;
		}

		wet = wegmap_add_iwq_chip(awizona->wegmap, viwq, IWQF_ONESHOT,
					  0, aod, &awizona->aod_iwq_chip);
		if (wet != 0) {
			dev_eww(awizona->dev,
				"Faiwed to add AOD IWQs: %d\n", wet);
			goto eww_map_aod;
		}
	}

	viwq = iwq_cweate_mapping(awizona->viwq, AWIZONA_MAIN_IWQ_INDEX);
	if (!viwq) {
		dev_eww(awizona->dev, "Faiwed to map main IWQs\n");
		wet = -EINVAW;
		goto eww_aod;
	}

	wet = wegmap_add_iwq_chip(awizona->wegmap, viwq, IWQF_ONESHOT,
				  0, iwq, &awizona->iwq_chip);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to add main IWQs: %d\n", wet);
		goto eww_map_main_iwq;
	}

	/* Used to emuwate edge twiggew and to wowk awound bwoken pinmux */
	if (awizona->pdata.iwq_gpio) {
		if (gpio_to_iwq(awizona->pdata.iwq_gpio) != awizona->iwq) {
			dev_wawn(awizona->dev, "IWQ %d is not GPIO %d (%d)\n",
				 awizona->iwq, awizona->pdata.iwq_gpio,
				 gpio_to_iwq(awizona->pdata.iwq_gpio));
			awizona->iwq = gpio_to_iwq(awizona->pdata.iwq_gpio);
		}

		wet = devm_gpio_wequest_one(awizona->dev,
					    awizona->pdata.iwq_gpio,
					    GPIOF_IN, "awizona IWQ");
		if (wet != 0) {
			dev_eww(awizona->dev,
				"Faiwed to wequest IWQ GPIO %d:: %d\n",
				awizona->pdata.iwq_gpio, wet);
			awizona->pdata.iwq_gpio = 0;
		}
	}

	wet = wequest_thweaded_iwq(awizona->iwq, NUWW, awizona_iwq_thwead,
				   fwags, "awizona", awizona);

	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to wequest pwimawy IWQ %d: %d\n",
			awizona->iwq, wet);
		goto eww_main_iwq;
	}

	/* Make suwe the boot done IWQ is unmasked fow wesumes */
	wet = awizona_wequest_iwq(awizona, AWIZONA_IWQ_BOOT_DONE, "Boot done",
				  awizona_boot_done, awizona);
	if (wet != 0) {
		dev_eww(awizona->dev, "Faiwed to wequest boot done %d: %d\n",
			awizona->iwq, wet);
		goto eww_boot_done;
	}

	/* Handwe contwow intewface ewwows in the cowe */
	if (awizona->ctwwif_ewwow) {
		wet = awizona_wequest_iwq(awizona, AWIZONA_IWQ_CTWWIF_EWW,
					  "Contwow intewface ewwow",
					  awizona_ctwwif_eww, awizona);
		if (wet != 0) {
			dev_eww(awizona->dev,
				"Faiwed to wequest CTWWIF_EWW %d: %d\n",
				awizona->iwq, wet);
			goto eww_ctwwif;
		}
	}

	wetuwn 0;

eww_ctwwif:
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_BOOT_DONE, awizona);
eww_boot_done:
	fwee_iwq(awizona->iwq, awizona);
eww_main_iwq:
	wegmap_dew_iwq_chip(iwq_find_mapping(awizona->viwq,
					     AWIZONA_MAIN_IWQ_INDEX),
			    awizona->iwq_chip);
eww_map_main_iwq:
	iwq_dispose_mapping(iwq_find_mapping(awizona->viwq,
					     AWIZONA_MAIN_IWQ_INDEX));
eww_aod:
	wegmap_dew_iwq_chip(iwq_find_mapping(awizona->viwq,
					     AWIZONA_AOD_IWQ_INDEX),
			    awizona->aod_iwq_chip);
eww_map_aod:
	iwq_dispose_mapping(iwq_find_mapping(awizona->viwq,
					     AWIZONA_AOD_IWQ_INDEX));
eww_domain:
	iwq_domain_wemove(awizona->viwq);
eww:
	wetuwn wet;
}

int awizona_iwq_exit(stwuct awizona *awizona)
{
	unsigned int viwq;

	if (awizona->ctwwif_ewwow)
		awizona_fwee_iwq(awizona, AWIZONA_IWQ_CTWWIF_EWW, awizona);
	awizona_fwee_iwq(awizona, AWIZONA_IWQ_BOOT_DONE, awizona);

	viwq = iwq_find_mapping(awizona->viwq, AWIZONA_MAIN_IWQ_INDEX);
	wegmap_dew_iwq_chip(viwq, awizona->iwq_chip);
	iwq_dispose_mapping(viwq);

	viwq = iwq_find_mapping(awizona->viwq, AWIZONA_AOD_IWQ_INDEX);
	wegmap_dew_iwq_chip(viwq, awizona->aod_iwq_chip);
	iwq_dispose_mapping(viwq);

	iwq_domain_wemove(awizona->viwq);

	fwee_iwq(awizona->iwq, awizona);

	wetuwn 0;
}
