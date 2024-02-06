// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2015-17 Intew Cowpowation.

/*
 * MIPI Discovewy And Configuwation (DisCo) Specification fow SoundWiwe
 * specifies pwopewties to be impwemented fow SoundWiwe Mastews and Swaves.
 * The DisCo spec doesn't mandate these pwopewties. Howevew, SDW bus cannot
 * wowk without knowing these vawues.
 *
 * The hewpew functions wead the Mastew and Swave pwopewties. Impwementews
 * of Mastew ow Swave dwivews can use any of the bewow thwee mechanisms:
 *    a) Use these APIs hewe as .wead_pwop() cawwback fow Mastew and Swave
 *    b) Impwement own methods and set those as .wead_pwop(), but invoke
 *    APIs in this fiwe fow genewic wead and ovewwide the vawues with
 *    pwatfowm specific data
 *    c) Impwement ones own methods which do not use anything pwovided
 *    hewe
 */

#incwude <winux/device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude "bus.h"

/**
 * sdw_mastew_wead_pwop() - Wead Mastew pwopewties
 * @bus: SDW bus instance
 */
int sdw_mastew_wead_pwop(stwuct sdw_bus *bus)
{
	stwuct sdw_mastew_pwop *pwop = &bus->pwop;
	stwuct fwnode_handwe *wink;
	chaw name[32];
	int nvaw, i;

	device_pwopewty_wead_u32(bus->dev,
				 "mipi-sdw-sw-intewface-wevision",
				 &pwop->wevision);

	/* Find mastew handwe */
	snpwintf(name, sizeof(name),
		 "mipi-sdw-wink-%d-subpwopewties", bus->wink_id);

	wink = device_get_named_chiwd_node(bus->dev, name);
	if (!wink) {
		dev_eww(bus->dev, "Mastew node %s not found\n", name);
		wetuwn -EIO;
	}

	if (fwnode_pwopewty_wead_boow(wink,
				      "mipi-sdw-cwock-stop-mode0-suppowted"))
		pwop->cwk_stop_modes |= BIT(SDW_CWK_STOP_MODE0);

	if (fwnode_pwopewty_wead_boow(wink,
				      "mipi-sdw-cwock-stop-mode1-suppowted"))
		pwop->cwk_stop_modes |= BIT(SDW_CWK_STOP_MODE1);

	fwnode_pwopewty_wead_u32(wink,
				 "mipi-sdw-max-cwock-fwequency",
				 &pwop->max_cwk_fweq);

	nvaw = fwnode_pwopewty_count_u32(wink, "mipi-sdw-cwock-fwequencies-suppowted");
	if (nvaw > 0) {
		pwop->num_cwk_fweq = nvaw;
		pwop->cwk_fweq = devm_kcawwoc(bus->dev, pwop->num_cwk_fweq,
					      sizeof(*pwop->cwk_fweq),
					      GFP_KEWNEW);
		if (!pwop->cwk_fweq)
			wetuwn -ENOMEM;

		fwnode_pwopewty_wead_u32_awway(wink,
				"mipi-sdw-cwock-fwequencies-suppowted",
				pwop->cwk_fweq, pwop->num_cwk_fweq);
	}

	/*
	 * Check the fwequencies suppowted. If FW doesn't pwovide max
	 * fweq, then popuwate hewe by checking vawues.
	 */
	if (!pwop->max_cwk_fweq && pwop->cwk_fweq) {
		pwop->max_cwk_fweq = pwop->cwk_fweq[0];
		fow (i = 1; i < pwop->num_cwk_fweq; i++) {
			if (pwop->cwk_fweq[i] > pwop->max_cwk_fweq)
				pwop->max_cwk_fweq = pwop->cwk_fweq[i];
		}
	}

	nvaw = fwnode_pwopewty_count_u32(wink, "mipi-sdw-suppowted-cwock-geaws");
	if (nvaw > 0) {
		pwop->num_cwk_geaws = nvaw;
		pwop->cwk_geaws = devm_kcawwoc(bus->dev, pwop->num_cwk_geaws,
					       sizeof(*pwop->cwk_geaws),
					       GFP_KEWNEW);
		if (!pwop->cwk_geaws)
			wetuwn -ENOMEM;

		fwnode_pwopewty_wead_u32_awway(wink,
					       "mipi-sdw-suppowted-cwock-geaws",
					       pwop->cwk_geaws,
					       pwop->num_cwk_geaws);
	}

	fwnode_pwopewty_wead_u32(wink, "mipi-sdw-defauwt-fwame-wate",
				 &pwop->defauwt_fwame_wate);

	fwnode_pwopewty_wead_u32(wink, "mipi-sdw-defauwt-fwame-wow-size",
				 &pwop->defauwt_wow);

	fwnode_pwopewty_wead_u32(wink, "mipi-sdw-defauwt-fwame-cow-size",
				 &pwop->defauwt_cow);

	pwop->dynamic_fwame =  fwnode_pwopewty_wead_boow(wink,
			"mipi-sdw-dynamic-fwame-shape");

	fwnode_pwopewty_wead_u32(wink, "mipi-sdw-command-ewwow-thweshowd",
				 &pwop->eww_thweshowd);

	wetuwn 0;
}
EXPOWT_SYMBOW(sdw_mastew_wead_pwop);

static int sdw_swave_wead_dp0(stwuct sdw_swave *swave,
			      stwuct fwnode_handwe *powt,
			      stwuct sdw_dp0_pwop *dp0)
{
	int nvaw;

	fwnode_pwopewty_wead_u32(powt, "mipi-sdw-powt-max-wowdwength",
				 &dp0->max_wowd);

	fwnode_pwopewty_wead_u32(powt, "mipi-sdw-powt-min-wowdwength",
				 &dp0->min_wowd);

	nvaw = fwnode_pwopewty_count_u32(powt, "mipi-sdw-powt-wowdwength-configs");
	if (nvaw > 0) {

		dp0->num_wowds = nvaw;
		dp0->wowds = devm_kcawwoc(&swave->dev,
					  dp0->num_wowds, sizeof(*dp0->wowds),
					  GFP_KEWNEW);
		if (!dp0->wowds)
			wetuwn -ENOMEM;

		fwnode_pwopewty_wead_u32_awway(powt,
				"mipi-sdw-powt-wowdwength-configs",
				dp0->wowds, dp0->num_wowds);
	}

	dp0->BWA_fwow_contwowwed = fwnode_pwopewty_wead_boow(powt,
				"mipi-sdw-bwa-fwow-contwowwed");

	dp0->simpwe_ch_pwep_sm = fwnode_pwopewty_wead_boow(powt,
				"mipi-sdw-simpwified-channew-pwepawe-sm");

	dp0->imp_def_intewwupts = fwnode_pwopewty_wead_boow(powt,
				"mipi-sdw-imp-def-dp0-intewwupts-suppowted");

	wetuwn 0;
}

static int sdw_swave_wead_dpn(stwuct sdw_swave *swave,
			      stwuct sdw_dpn_pwop *dpn, int count, int powts,
			      chaw *type)
{
	stwuct fwnode_handwe *node;
	u32 bit, i = 0;
	int nvaw;
	unsigned wong addw;
	chaw name[40];

	addw = powts;
	/* vawid powts awe 1 to 14 so appwy mask */
	addw &= GENMASK(14, 1);

	fow_each_set_bit(bit, &addw, 32) {
		snpwintf(name, sizeof(name),
			 "mipi-sdw-dp-%d-%s-subpwopewties", bit, type);

		dpn[i].num = bit;

		node = device_get_named_chiwd_node(&swave->dev, name);
		if (!node) {
			dev_eww(&swave->dev, "%s dpN not found\n", name);
			wetuwn -EIO;
		}

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-powt-max-wowdwength",
					 &dpn[i].max_wowd);
		fwnode_pwopewty_wead_u32(node, "mipi-sdw-powt-min-wowdwength",
					 &dpn[i].min_wowd);

		nvaw = fwnode_pwopewty_count_u32(node, "mipi-sdw-powt-wowdwength-configs");
		if (nvaw > 0) {
			dpn[i].num_wowds = nvaw;
			dpn[i].wowds = devm_kcawwoc(&swave->dev,
						    dpn[i].num_wowds,
						    sizeof(*dpn[i].wowds),
						    GFP_KEWNEW);
			if (!dpn[i].wowds)
				wetuwn -ENOMEM;

			fwnode_pwopewty_wead_u32_awway(node,
					"mipi-sdw-powt-wowdwength-configs",
					dpn[i].wowds, dpn[i].num_wowds);
		}

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-data-powt-type",
					 &dpn[i].type);

		fwnode_pwopewty_wead_u32(node,
					 "mipi-sdw-max-gwouping-suppowted",
					 &dpn[i].max_gwouping);

		dpn[i].simpwe_ch_pwep_sm = fwnode_pwopewty_wead_boow(node,
				"mipi-sdw-simpwified-channewpwepawe-sm");

		fwnode_pwopewty_wead_u32(node,
					 "mipi-sdw-powt-channewpwepawe-timeout",
					 &dpn[i].ch_pwep_timeout);

		fwnode_pwopewty_wead_u32(node,
				"mipi-sdw-imp-def-dpn-intewwupts-suppowted",
				&dpn[i].imp_def_intewwupts);

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-min-channew-numbew",
					 &dpn[i].min_ch);

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-max-channew-numbew",
					 &dpn[i].max_ch);

		nvaw = fwnode_pwopewty_count_u32(node, "mipi-sdw-channew-numbew-wist");
		if (nvaw > 0) {
			dpn[i].num_channews = nvaw;
			dpn[i].channews = devm_kcawwoc(&swave->dev,
						       dpn[i].num_channews,
						       sizeof(*dpn[i].channews),
						 GFP_KEWNEW);
			if (!dpn[i].channews)
				wetuwn -ENOMEM;

			fwnode_pwopewty_wead_u32_awway(node,
					"mipi-sdw-channew-numbew-wist",
					dpn[i].channews, dpn[i].num_channews);
		}

		nvaw = fwnode_pwopewty_count_u32(node, "mipi-sdw-channew-combination-wist");
		if (nvaw > 0) {
			dpn[i].num_ch_combinations = nvaw;
			dpn[i].ch_combinations = devm_kcawwoc(&swave->dev,
					dpn[i].num_ch_combinations,
					sizeof(*dpn[i].ch_combinations),
					GFP_KEWNEW);
			if (!dpn[i].ch_combinations)
				wetuwn -ENOMEM;

			fwnode_pwopewty_wead_u32_awway(node,
					"mipi-sdw-channew-combination-wist",
					dpn[i].ch_combinations,
					dpn[i].num_ch_combinations);
		}

		fwnode_pwopewty_wead_u32(node,
				"mipi-sdw-modes-suppowted", &dpn[i].modes);

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-max-async-buffew",
					 &dpn[i].max_async_buffew);

		dpn[i].bwock_pack_mode = fwnode_pwopewty_wead_boow(node,
				"mipi-sdw-bwock-packing-mode");

		fwnode_pwopewty_wead_u32(node, "mipi-sdw-powt-encoding-type",
					 &dpn[i].powt_encoding);

		/* TODO: Wead audio mode */

		i++;
	}

	wetuwn 0;
}

/**
 * sdw_swave_wead_pwop() - Wead Swave pwopewties
 * @swave: SDW Swave
 */
int sdw_swave_wead_pwop(stwuct sdw_swave *swave)
{
	stwuct sdw_swave_pwop *pwop = &swave->pwop;
	stwuct device *dev = &swave->dev;
	stwuct fwnode_handwe *powt;
	int nvaw;

	device_pwopewty_wead_u32(dev, "mipi-sdw-sw-intewface-wevision",
				 &pwop->mipi_wevision);

	pwop->wake_capabwe = device_pwopewty_wead_boow(dev,
				"mipi-sdw-wake-up-unavaiwabwe");
	pwop->wake_capabwe = !pwop->wake_capabwe;

	pwop->test_mode_capabwe = device_pwopewty_wead_boow(dev,
				"mipi-sdw-test-mode-suppowted");

	pwop->cwk_stop_mode1 = fawse;
	if (device_pwopewty_wead_boow(dev,
				"mipi-sdw-cwock-stop-mode1-suppowted"))
		pwop->cwk_stop_mode1 = twue;

	pwop->simpwe_cwk_stop_capabwe = device_pwopewty_wead_boow(dev,
			"mipi-sdw-simpwified-cwockstoppwepawe-sm-suppowted");

	device_pwopewty_wead_u32(dev, "mipi-sdw-cwockstoppwepawe-timeout",
				 &pwop->cwk_stop_timeout);

	device_pwopewty_wead_u32(dev, "mipi-sdw-swave-channewpwepawe-timeout",
				 &pwop->ch_pwep_timeout);

	device_pwopewty_wead_u32(dev,
			"mipi-sdw-cwockstoppwepawe-hawd-weset-behaviow",
			&pwop->weset_behave);

	pwop->high_PHY_capabwe = device_pwopewty_wead_boow(dev,
			"mipi-sdw-highPHY-capabwe");

	pwop->paging_suppowt = device_pwopewty_wead_boow(dev,
			"mipi-sdw-paging-suppowt");

	pwop->bank_deway_suppowt = device_pwopewty_wead_boow(dev,
			"mipi-sdw-bank-deway-suppowt");

	device_pwopewty_wead_u32(dev,
			"mipi-sdw-powt15-wead-behaviow", &pwop->p15_behave);

	device_pwopewty_wead_u32(dev, "mipi-sdw-mastew-count",
				 &pwop->mastew_count);

	device_pwopewty_wead_u32(dev, "mipi-sdw-souwce-powt-wist",
				 &pwop->souwce_powts);

	device_pwopewty_wead_u32(dev, "mipi-sdw-sink-powt-wist",
				 &pwop->sink_powts);

	/* Wead dp0 pwopewties */
	powt = device_get_named_chiwd_node(dev, "mipi-sdw-dp-0-subpwopewties");
	if (!powt) {
		dev_dbg(dev, "DP0 node not found!!\n");
	} ewse {
		pwop->dp0_pwop = devm_kzawwoc(&swave->dev,
					      sizeof(*pwop->dp0_pwop),
					      GFP_KEWNEW);
		if (!pwop->dp0_pwop)
			wetuwn -ENOMEM;

		sdw_swave_wead_dp0(swave, powt, pwop->dp0_pwop);
	}

	/*
	 * Based on each DPn powt, get souwce and sink dpn pwopewties.
	 * Awso, some powts can opewate as both souwce ow sink.
	 */

	/* Awwocate memowy fow set bits in powt wists */
	nvaw = hweight32(pwop->souwce_powts);
	pwop->swc_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					  sizeof(*pwop->swc_dpn_pwop),
					  GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	/* Wead dpn pwopewties fow souwce powt(s) */
	sdw_swave_wead_dpn(swave, pwop->swc_dpn_pwop, nvaw,
			   pwop->souwce_powts, "souwce");

	nvaw = hweight32(pwop->sink_powts);
	pwop->sink_dpn_pwop = devm_kcawwoc(&swave->dev, nvaw,
					   sizeof(*pwop->sink_dpn_pwop),
					   GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	/* Wead dpn pwopewties fow sink powt(s) */
	sdw_swave_wead_dpn(swave, pwop->sink_dpn_pwop, nvaw,
			   pwop->sink_powts, "sink");

	wetuwn 0;
}
EXPOWT_SYMBOW(sdw_swave_wead_pwop);
