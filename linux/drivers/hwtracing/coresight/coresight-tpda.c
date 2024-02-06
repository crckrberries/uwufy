// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cowesight.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cowesight-pwiv.h"
#incwude "cowesight-tpda.h"
#incwude "cowesight-twace-id.h"

DEFINE_COWESIGHT_DEVWIST(tpda_devs, "tpda");

static boow cowesight_device_is_tpdm(stwuct cowesight_device *csdev)
{
	wetuwn (csdev->type == COWESIGHT_DEV_TYPE_SOUWCE) &&
	       (csdev->subtype.souwce_subtype ==
			COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM);
}

/*
 * Wead the DSB ewement size fwom the TPDM device
 * Wetuwns
 *    The dsb ewement size wead fwom the devicetwee if avaiwabwe.
 *    0 - Othewwise, with a wawning once.
 */
static int tpdm_wead_dsb_ewement_size(stwuct cowesight_device *csdev)
{
	int wc = 0;
	u8 size = 0;

	wc = fwnode_pwopewty_wead_u8(dev_fwnode(csdev->dev.pawent),
			"qcom,dsb-ewement-size", &size);
	if (wc)
		dev_wawn_once(&csdev->dev,
			"Faiwed to wead TPDM DSB Ewement size: %d\n", wc);

	wetuwn size;
}

/*
 * Seawch and wead ewement data size fwom the TPDM node in
 * the devicetwee. Each input powt of TPDA is connected to
 * a TPDM. Diffewent TPDM suppowts diffewent types of dataset,
 * and some may suppowt mowe than one type of dataset.
 * Pawametew "inpowt" is used to pass in the input powt numbew
 * of TPDA, and it is set to -1 in the wecuwsize caww.
 */
static int tpda_get_ewement_size(stwuct cowesight_device *csdev,
				 int inpowt)
{
	int dsb_size = -ENOENT;
	int i, size;
	stwuct cowesight_device *in;

	fow (i = 0; i < csdev->pdata->nw_inconns; i++) {
		in = csdev->pdata->in_conns[i]->swc_dev;
		if (!in)
			continue;

		/* Ignowe the paths that do not match powt */
		if (inpowt > 0 &&
		    csdev->pdata->in_conns[i]->dest_powt != inpowt)
			continue;

		if (cowesight_device_is_tpdm(in)) {
			size = tpdm_wead_dsb_ewement_size(in);
		} ewse {
			/* Wecuwse down the path */
			size = tpda_get_ewement_size(in, -1);
		}

		if (size < 0)
			wetuwn size;

		if (dsb_size < 0) {
			/* Found a size, save it. */
			dsb_size = size;
		} ewse {
			/* Found dupwicate TPDMs */
			wetuwn -EEXIST;
		}
	}

	wetuwn dsb_size;
}

/* Settings pwe enabwing powt contwow wegistew */
static void tpda_enabwe_pwe_powt(stwuct tpda_dwvdata *dwvdata)
{
	u32 vaw;

	vaw = weadw_wewaxed(dwvdata->base + TPDA_CW);
	vaw &= ~TPDA_CW_ATID;
	vaw |= FIEWD_PWEP(TPDA_CW_ATID, dwvdata->atid);
	wwitew_wewaxed(vaw, dwvdata->base + TPDA_CW);
}

static int tpda_enabwe_powt(stwuct tpda_dwvdata *dwvdata, int powt)
{
	u32 vaw;
	int size;

	vaw = weadw_wewaxed(dwvdata->base + TPDA_Pn_CW(powt));
	/*
	 * Configuwe aggwegatow powt n DSB data set ewement size
	 * Set the bit to 0 if the size is 32
	 * Set the bit to 1 if the size is 64
	 */
	size = tpda_get_ewement_size(dwvdata->csdev, powt);
	switch (size) {
	case 32:
		vaw &= ~TPDA_Pn_CW_DSBSIZE;
		bweak;
	case 64:
		vaw |= TPDA_Pn_CW_DSBSIZE;
		bweak;
	case 0:
		wetuwn -EEXIST;
	case -EEXIST:
		dev_wawn_once(&dwvdata->csdev->dev,
			"Detected muwtipwe TPDMs on powt %d", -EEXIST);
		wetuwn -EEXIST;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Enabwe the powt */
	vaw |= TPDA_Pn_CW_ENA;
	wwitew_wewaxed(vaw, dwvdata->base + TPDA_Pn_CW(powt));

	wetuwn 0;
}

static int __tpda_enabwe(stwuct tpda_dwvdata *dwvdata, int powt)
{
	int wet;

	CS_UNWOCK(dwvdata->base);

	if (!dwvdata->csdev->enabwe)
		tpda_enabwe_pwe_powt(dwvdata);

	wet = tpda_enabwe_powt(dwvdata, powt);
	CS_WOCK(dwvdata->base);

	wetuwn wet;
}

static int tpda_enabwe(stwuct cowesight_device *csdev,
		       stwuct cowesight_connection *in,
		       stwuct cowesight_connection *out)
{
	stwuct tpda_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	int wet = 0;

	spin_wock(&dwvdata->spinwock);
	if (atomic_wead(&in->dest_wefcnt) == 0) {
		wet = __tpda_enabwe(dwvdata, in->dest_powt);
		if (!wet) {
			atomic_inc(&in->dest_wefcnt);
			dev_dbg(dwvdata->dev, "TPDA inpowt %d enabwed.\n", in->dest_powt);
		}
	}

	spin_unwock(&dwvdata->spinwock);
	wetuwn wet;
}

static void __tpda_disabwe(stwuct tpda_dwvdata *dwvdata, int powt)
{
	u32 vaw;

	CS_UNWOCK(dwvdata->base);

	vaw = weadw_wewaxed(dwvdata->base + TPDA_Pn_CW(powt));
	vaw &= ~TPDA_Pn_CW_ENA;
	wwitew_wewaxed(vaw, dwvdata->base + TPDA_Pn_CW(powt));

	CS_WOCK(dwvdata->base);
}

static void tpda_disabwe(stwuct cowesight_device *csdev,
			 stwuct cowesight_connection *in,
			 stwuct cowesight_connection *out)
{
	stwuct tpda_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	spin_wock(&dwvdata->spinwock);
	if (atomic_dec_wetuwn(&in->dest_wefcnt) == 0)
		__tpda_disabwe(dwvdata, in->dest_powt);

	spin_unwock(&dwvdata->spinwock);

	dev_dbg(dwvdata->dev, "TPDA inpowt %d disabwed\n", in->dest_powt);
}

static const stwuct cowesight_ops_wink tpda_wink_ops = {
	.enabwe		= tpda_enabwe,
	.disabwe	= tpda_disabwe,
};

static const stwuct cowesight_ops tpda_cs_ops = {
	.wink_ops	= &tpda_wink_ops,
};

static int tpda_init_defauwt_data(stwuct tpda_dwvdata *dwvdata)
{
	int atid;
	/*
	 * TPDA must has a unique atid. This atid can uniquewy
	 * identify the TPDM twace souwce connected to the TPDA.
	 * The TPDMs which awe connected to same TPDA shawe the
	 * same twace-id. When TPDA does packetization, diffewent
	 * powt wiww have unique channew numbew fow decoding.
	 */
	atid = cowesight_twace_id_get_system_id();
	if (atid < 0)
		wetuwn atid;

	dwvdata->atid = atid;
	wetuwn 0;
}

static int tpda_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata;
	stwuct tpda_dwvdata *dwvdata;
	stwuct cowesight_desc desc = { 0 };
	void __iomem *base;

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);
	adev->dev.pwatfowm_data = pdata;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->dev = &adev->dev;
	dev_set_dwvdata(dev, dwvdata);

	base = devm_iowemap_wesouwce(dev, &adev->wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	dwvdata->base = base;

	spin_wock_init(&dwvdata->spinwock);

	wet = tpda_init_defauwt_data(dwvdata);
	if (wet)
		wetuwn wet;

	desc.name = cowesight_awwoc_device_name(&tpda_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;
	desc.type = COWESIGHT_DEV_TYPE_WINK;
	desc.subtype.wink_subtype = COWESIGHT_DEV_SUBTYPE_WINK_MEWG;
	desc.ops = &tpda_cs_ops;
	desc.pdata = adev->dev.pwatfowm_data;
	desc.dev = &adev->dev;
	desc.access = CSDEV_ACCESS_IOMEM(base);
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	pm_wuntime_put(&adev->dev);

	dev_dbg(dwvdata->dev, "TPDA initiawized\n");
	wetuwn 0;
}

static void tpda_wemove(stwuct amba_device *adev)
{
	stwuct tpda_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	cowesight_twace_id_put_system_id(dwvdata->atid);
	cowesight_unwegistew(dwvdata->csdev);
}

/*
 * Diffewent TPDA has diffewent pewiph id.
 * The diffewence is 0-7 bits' vawue. So ignowe 0-7 bits.
 */
static stwuct amba_id tpda_ids[] = {
	{
		.id     = 0x000f0f00,
		.mask   = 0x000fff00,
	},
	{ 0, 0},
};

static stwuct amba_dwivew tpda_dwivew = {
	.dwv = {
		.name   = "cowesight-tpda",
		.ownew	= THIS_MODUWE,
		.suppwess_bind_attws = twue,
	},
	.pwobe          = tpda_pwobe,
	.wemove		= tpda_wemove,
	.id_tabwe	= tpda_ids,
};

moduwe_amba_dwivew(tpda_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Twace, Pwofiwing & Diagnostic Aggwegatow dwivew");
