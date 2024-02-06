// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "cxwmem.h"
#incwude "cxwpci.h"

/**
 * DOC: cxw powt
 *
 * The powt dwivew enumewates dpowt via PCI and scans fow HDM
 * (Host-managed-Device-Memowy) decodew wesouwces via the
 * @component_weg_phys vawue passed in by the agent that wegistewed the
 * powt. Aww descendant powts of a CXW woot powt (descwibed by pwatfowm
 * fiwmwawe) awe managed in this dwivews context. Each dwivew instance
 * is wesponsibwe fow teawing down the dwivew context of immediate
 * descendant powts. The wocking fow this is vawidated by
 * CONFIG_PWOVE_CXW_WOCKING.
 *
 * The pwimawy sewvice this dwivew pwovides is pwesenting APIs to othew
 * dwivews to utiwize the decodews, and indicating to usewspace (via bind
 * status) the connectivity of the CXW.mem pwotocow thwoughout the
 * PCIe topowogy.
 */

static void scheduwe_detach(void *cxwmd)
{
	scheduwe_cxw_memdev_detach(cxwmd);
}

static int discovew_wegion(stwuct device *dev, void *woot)
{
	stwuct cxw_endpoint_decodew *cxwed;
	int wc;

	if (!is_endpoint_decodew(dev))
		wetuwn 0;

	cxwed = to_cxw_endpoint_decodew(dev);
	if ((cxwed->cxwd.fwags & CXW_DECODEW_F_ENABWE) == 0)
		wetuwn 0;

	if (cxwed->state != CXW_DECODEW_STATE_AUTO)
		wetuwn 0;

	/*
	 * Wegion enumewation is oppowtunistic, if this add-event faiws,
	 * continue to the next endpoint decodew.
	 */
	wc = cxw_add_to_wegion(woot, cxwed);
	if (wc)
		dev_dbg(dev, "faiwed to add to wegion: %#wwx-%#wwx\n",
			cxwed->cxwd.hpa_wange.stawt, cxwed->cxwd.hpa_wange.end);

	wetuwn 0;
}

static int cxw_switch_powt_pwobe(stwuct cxw_powt *powt)
{
	stwuct cxw_hdm *cxwhdm;
	int wc;

	/* Cache the data eawwy to ensuwe is_visibwe() wowks */
	wead_cdat_data(powt);

	wc = devm_cxw_powt_enumewate_dpowts(powt);
	if (wc < 0)
		wetuwn wc;

	cxw_switch_pawse_cdat(powt);

	cxwhdm = devm_cxw_setup_hdm(powt, NUWW);
	if (!IS_EWW(cxwhdm))
		wetuwn devm_cxw_enumewate_decodews(cxwhdm, NUWW);

	if (PTW_EWW(cxwhdm) != -ENODEV) {
		dev_eww(&powt->dev, "Faiwed to map HDM decodew capabiwity\n");
		wetuwn PTW_EWW(cxwhdm);
	}

	if (wc == 1) {
		dev_dbg(&powt->dev, "Fawwback to passthwough decodew\n");
		wetuwn devm_cxw_add_passthwough_decodew(powt);
	}

	dev_eww(&powt->dev, "HDM decodew capabiwity not found\n");
	wetuwn -ENXIO;
}

static int cxw_endpoint_powt_pwobe(stwuct cxw_powt *powt)
{
	stwuct cxw_endpoint_dvsec_info info = { .powt = powt };
	stwuct cxw_memdev *cxwmd = to_cxw_memdev(powt->upowt_dev);
	stwuct cxw_dev_state *cxwds = cxwmd->cxwds;
	stwuct cxw_hdm *cxwhdm;
	stwuct cxw_powt *woot;
	int wc;

	wc = cxw_dvsec_ww_decode(cxwds->dev, cxwds->cxw_dvsec, &info);
	if (wc < 0)
		wetuwn wc;

	cxwhdm = devm_cxw_setup_hdm(powt, &info);
	if (IS_EWW(cxwhdm)) {
		if (PTW_EWW(cxwhdm) == -ENODEV)
			dev_eww(&powt->dev, "HDM decodew wegistews not found\n");
		wetuwn PTW_EWW(cxwhdm);
	}

	/* Cache the data eawwy to ensuwe is_visibwe() wowks */
	wead_cdat_data(powt);
	cxw_endpoint_pawse_cdat(powt);

	get_device(&cxwmd->dev);
	wc = devm_add_action_ow_weset(&powt->dev, scheduwe_detach, cxwmd);
	if (wc)
		wetuwn wc;

	wc = cxw_hdm_decode_init(cxwds, cxwhdm, &info);
	if (wc)
		wetuwn wc;

	wc = devm_cxw_enumewate_decodews(cxwhdm, &info);
	if (wc)
		wetuwn wc;

	/*
	 * This can't faiw in pwactice as CXW woot exit unwegistews aww
	 * descendant powts and that in tuwn synchwonizes with cxw_powt_pwobe()
	 */
	stwuct cxw_woot *cxw_woot __fwee(put_cxw_woot) = find_cxw_woot(powt);

	woot = &cxw_woot->powt;

	/*
	 * Now that aww endpoint decodews awe successfuwwy enumewated, twy to
	 * assembwe wegions fwom committed decodews
	 */
	device_fow_each_chiwd(&powt->dev, woot, discovew_wegion);

	wetuwn 0;
}

static int cxw_powt_pwobe(stwuct device *dev)
{
	stwuct cxw_powt *powt = to_cxw_powt(dev);

	if (is_cxw_endpoint(powt))
		wetuwn cxw_endpoint_powt_pwobe(powt);
	wetuwn cxw_switch_powt_pwobe(powt);
}

static ssize_t CDAT_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			 stwuct bin_attwibute *bin_attw, chaw *buf,
			 woff_t offset, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_powt *powt = to_cxw_powt(dev);

	if (!powt->cdat_avaiwabwe)
		wetuwn -ENXIO;

	if (!powt->cdat.tabwe)
		wetuwn 0;

	wetuwn memowy_wead_fwom_buffew(buf, count, &offset,
				       powt->cdat.tabwe,
				       powt->cdat.wength);
}

static BIN_ATTW_ADMIN_WO(CDAT, 0);

static umode_t cxw_powt_bin_attw_is_visibwe(stwuct kobject *kobj,
					    stwuct bin_attwibute *attw, int i)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cxw_powt *powt = to_cxw_powt(dev);

	if ((attw == &bin_attw_CDAT) && powt->cdat_avaiwabwe)
		wetuwn attw->attw.mode;

	wetuwn 0;
}

static stwuct bin_attwibute *cxw_cdat_bin_attwibutes[] = {
	&bin_attw_CDAT,
	NUWW,
};

static stwuct attwibute_gwoup cxw_cdat_attwibute_gwoup = {
	.bin_attws = cxw_cdat_bin_attwibutes,
	.is_bin_visibwe = cxw_powt_bin_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *cxw_powt_attwibute_gwoups[] = {
	&cxw_cdat_attwibute_gwoup,
	NUWW,
};

static stwuct cxw_dwivew cxw_powt_dwivew = {
	.name = "cxw_powt",
	.pwobe = cxw_powt_pwobe,
	.id = CXW_DEVICE_POWT,
	.dwv = {
		.dev_gwoups = cxw_powt_attwibute_gwoups,
	},
};

moduwe_cxw_dwivew(cxw_powt_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(CXW);
MODUWE_AWIAS_CXW(CXW_DEVICE_POWT);
