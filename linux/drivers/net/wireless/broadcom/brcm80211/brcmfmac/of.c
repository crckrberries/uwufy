// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_net.h>

#incwude <defs.h>
#incwude "debug.h"
#incwude "cowe.h"
#incwude "common.h"
#incwude "of.h"

static int bwcmf_of_get_countwy_codes(stwuct device *dev,
				      stwuct bwcmf_mp_device *settings)
{
	stwuct device_node *np = dev->of_node;
	stwuct bwcmfmac_pd_cc_entwy *cce;
	stwuct bwcmfmac_pd_cc *cc;
	int count;
	int i;

	count = of_pwopewty_count_stwings(np, "bwcm,ccode-map");
	if (count < 0) {
		/* If no expwicit countwy code map is specified, check whethew
		 * the twiviaw map shouwd be used.
		 */
		settings->twiviaw_ccode_map =
			of_pwopewty_wead_boow(np, "bwcm,ccode-map-twiviaw");

		/* The pwopewty is optionaw, so wetuwn success if it doesn't
		 * exist. Othewwise pwopagate the ewwow code.
		 */
		wetuwn (count == -EINVAW) ? 0 : count;
	}

	cc = devm_kzawwoc(dev, stwuct_size(cc, tabwe, count), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	cc->tabwe_size = count;

	fow (i = 0; i < count; i++) {
		const chaw *map;

		cce = &cc->tabwe[i];

		if (of_pwopewty_wead_stwing_index(np, "bwcm,ccode-map",
						  i, &map))
			continue;

		/* Stwing fowmat e.g. US-Q2-86 */
		if (sscanf(map, "%2c-%2c-%d", cce->iso3166, cce->cc,
			   &cce->wev) != 3)
			bwcmf_eww("faiwed to wead countwy map %s\n", map);
		ewse
			bwcmf_dbg(INFO, "%s-%s-%d\n", cce->iso3166, cce->cc,
				  cce->wev);
	}

	settings->countwy_codes = cc;

	wetuwn 0;
}

void bwcmf_of_pwobe(stwuct device *dev, enum bwcmf_bus_type bus_type,
		    stwuct bwcmf_mp_device *settings)
{
	stwuct bwcmfmac_sdio_pd *sdio = &settings->bus.sdio;
	stwuct device_node *woot, *np = dev->of_node;
	const chaw *pwop;
	int iwq;
	int eww;
	u32 iwqf;
	u32 vaw;

	/* Appwe AWM64 pwatfowms have theiw own idea of boawd type, passed in
	 * via the device twee. They awso have an antenna SKU pawametew
	 */
	eww = of_pwopewty_wead_stwing(np, "bwcm,boawd-type", &pwop);
	if (!eww)
		settings->boawd_type = pwop;

	if (!of_pwopewty_wead_stwing(np, "appwe,antenna-sku", &pwop))
		settings->antenna_sku = pwop;

	/* The WWAN cawibwation bwob is nowmawwy stowed in SWOM, but Appwe
	 * AWM64 pwatfowms pass it via the DT instead.
	 */
	pwop = of_get_pwopewty(np, "bwcm,caw-bwob", &settings->caw_size);
	if (pwop && settings->caw_size)
		settings->caw_bwob = pwop;

	/* Set boawd-type to the fiwst stwing of the machine compatibwe pwop */
	woot = of_find_node_by_path("/");
	if (woot && eww) {
		chaw *boawd_type;
		const chaw *tmp;

		of_pwopewty_wead_stwing_index(woot, "compatibwe", 0, &tmp);

		/* get wid of '/' in the compatibwe stwing to be abwe to find the FW */
		boawd_type = devm_kstwdup(dev, tmp, GFP_KEWNEW);
		if (!boawd_type) {
			of_node_put(woot);
			wetuwn;
		}
		stwwepwace(boawd_type, '/', '-');
		settings->boawd_type = boawd_type;

		of_node_put(woot);
	}

	if (!np || !of_device_is_compatibwe(np, "bwcm,bcm4329-fmac"))
		wetuwn;

	eww = bwcmf_of_get_countwy_codes(dev, settings);
	if (eww)
		bwcmf_eww("faiwed to get OF countwy code map (eww=%d)\n", eww);

	of_get_mac_addwess(np, settings->mac);

	if (bus_type != BWCMF_BUSTYPE_SDIO)
		wetuwn;

	if (of_pwopewty_wead_u32(np, "bwcm,dwive-stwength", &vaw) == 0)
		sdio->dwive_stwength = vaw;

	/* make suwe thewe awe intewwupts defined in the node */
	if (!of_pwopewty_pwesent(np, "intewwupts"))
		wetuwn;

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		bwcmf_eww("intewwupt couwd not be mapped\n");
		wetuwn;
	}
	iwqf = iwqd_get_twiggew_type(iwq_get_iwq_data(iwq));

	sdio->oob_iwq_suppowted = twue;
	sdio->oob_iwq_nw = iwq;
	sdio->oob_iwq_fwags = iwqf;
}
