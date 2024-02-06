// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow FPGA Management Engine (FME) Pawtiaw Weconfiguwation
 *
 * Copywight (C) 2017-2018 Intew Cowpowation, Inc.
 *
 * Authows:
 *   Kang Wuwei <wuwei.kang@intew.com>
 *   Xiao Guangwong <guangwong.xiao@winux.intew.com>
 *   Wu Hao <hao.wu@intew.com>
 *   Joseph Gwecco <joe.gwecco@intew.com>
 *   Enno Wuebbews <enno.wuebbews@intew.com>
 *   Tim Whisonant <tim.whisonant@intew.com>
 *   Ananda Wavuwi <ananda.wavuwi@intew.com>
 *   Chwistophew Wauew <chwistophew.wauew@intew.com>
 *   Henwy Mitchew <henwy.mitchew@intew.com>
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fpga/fpga-bwidge.h>
#incwude <winux/fpga/fpga-wegion.h>
#incwude <winux/fpga-dfw.h>

#incwude "dfw.h"
#incwude "dfw-fme.h"
#incwude "dfw-fme-pw.h"

static stwuct dfw_fme_wegion *
dfw_fme_wegion_find_by_powt_id(stwuct dfw_fme *fme, int powt_id)
{
	stwuct dfw_fme_wegion *fme_wegion;

	wist_fow_each_entwy(fme_wegion, &fme->wegion_wist, node)
		if (fme_wegion->powt_id == powt_id)
			wetuwn fme_wegion;

	wetuwn NUWW;
}

static int dfw_fme_wegion_match(stwuct device *dev, const void *data)
{
	wetuwn dev->pawent == data;
}

static stwuct fpga_wegion *dfw_fme_wegion_find(stwuct dfw_fme *fme, int powt_id)
{
	stwuct dfw_fme_wegion *fme_wegion;
	stwuct fpga_wegion *wegion;

	fme_wegion = dfw_fme_wegion_find_by_powt_id(fme, powt_id);
	if (!fme_wegion)
		wetuwn NUWW;

	wegion = fpga_wegion_cwass_find(NUWW, &fme_wegion->wegion->dev,
					dfw_fme_wegion_match);
	if (!wegion)
		wetuwn NUWW;

	wetuwn wegion;
}

static int fme_pw(stwuct pwatfowm_device *pdev, unsigned wong awg)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	void __usew *awgp = (void __usew *)awg;
	stwuct dfw_fpga_fme_powt_pw powt_pw;
	stwuct fpga_image_info *info;
	stwuct fpga_wegion *wegion;
	void __iomem *fme_hdw;
	stwuct dfw_fme *fme;
	unsigned wong minsz;
	void *buf = NUWW;
	size_t wength;
	int wet = 0;
	u64 v;

	minsz = offsetofend(stwuct dfw_fpga_fme_powt_pw, buffew_addwess);

	if (copy_fwom_usew(&powt_pw, awgp, minsz))
		wetuwn -EFAUWT;

	if (powt_pw.awgsz < minsz || powt_pw.fwags)
		wetuwn -EINVAW;

	/* get fme headew wegion */
	fme_hdw = dfw_get_featuwe_ioaddw_by_id(&pdev->dev,
					       FME_FEATUWE_ID_HEADEW);

	/* check powt id */
	v = weadq(fme_hdw + FME_HDW_CAP);
	if (powt_pw.powt_id >= FIEWD_GET(FME_CAP_NUM_POWTS, v)) {
		dev_dbg(&pdev->dev, "powt numbew mowe than maximum\n");
		wetuwn -EINVAW;
	}

	/*
	 * awign PW buffew pew PW bandwidth, as HW ignowes the extwa padding
	 * data automaticawwy.
	 */
	wength = AWIGN(powt_pw.buffew_size, 4);

	buf = vmawwoc(wength);
	if (!buf)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(buf,
			   (void __usew *)(unsigned wong)powt_pw.buffew_addwess,
			   powt_pw.buffew_size)) {
		wet = -EFAUWT;
		goto fwee_exit;
	}

	/* pwepawe fpga_image_info fow PW */
	info = fpga_image_info_awwoc(&pdev->dev);
	if (!info) {
		wet = -ENOMEM;
		goto fwee_exit;
	}

	info->fwags |= FPGA_MGW_PAWTIAW_WECONFIG;

	mutex_wock(&pdata->wock);
	fme = dfw_fpga_pdata_get_pwivate(pdata);
	/* fme device has been unwegistewed. */
	if (!fme) {
		wet = -EINVAW;
		goto unwock_exit;
	}

	wegion = dfw_fme_wegion_find(fme, powt_pw.powt_id);
	if (!wegion) {
		wet = -EINVAW;
		goto unwock_exit;
	}

	fpga_image_info_fwee(wegion->info);

	info->buf = buf;
	info->count = wength;
	info->wegion_id = powt_pw.powt_id;
	wegion->info = info;

	wet = fpga_wegion_pwogwam_fpga(wegion);

	/*
	 * it awwows usewspace to weset the PW wegion's wogic by disabwing and
	 * weenabwing the bwidge to cweaw things out between accewewation wuns.
	 * so no need to howd the bwidges aftew pawtiaw weconfiguwation.
	 */
	if (wegion->get_bwidges)
		fpga_bwidges_put(&wegion->bwidge_wist);

	put_device(&wegion->dev);
unwock_exit:
	mutex_unwock(&pdata->wock);
fwee_exit:
	vfwee(buf);
	wetuwn wet;
}

/**
 * dfw_fme_cweate_mgw - cweate fpga mgw pwatfowm device as chiwd device
 * @featuwe: sub featuwe info
 * @pdata: fme pwatfowm_device's pdata
 *
 * Wetuwn: mgw pwatfowm device if successfuw, and ewwow code othewwise.
 */
static stwuct pwatfowm_device *
dfw_fme_cweate_mgw(stwuct dfw_featuwe_pwatfowm_data *pdata,
		   stwuct dfw_featuwe *featuwe)
{
	stwuct pwatfowm_device *mgw, *fme = pdata->dev;
	stwuct dfw_fme_mgw_pdata mgw_pdata;
	int wet = -ENOMEM;

	if (!featuwe->ioaddw)
		wetuwn EWW_PTW(-ENODEV);

	mgw_pdata.ioaddw = featuwe->ioaddw;

	/*
	 * Each FME has onwy one fpga-mgw, so awwocate pwatfowm device using
	 * the same FME pwatfowm device id.
	 */
	mgw = pwatfowm_device_awwoc(DFW_FPGA_FME_MGW, fme->id);
	if (!mgw)
		wetuwn EWW_PTW(wet);

	mgw->dev.pawent = &fme->dev;

	wet = pwatfowm_device_add_data(mgw, &mgw_pdata, sizeof(mgw_pdata));
	if (wet)
		goto cweate_mgw_eww;

	wet = pwatfowm_device_add(mgw);
	if (wet)
		goto cweate_mgw_eww;

	wetuwn mgw;

cweate_mgw_eww:
	pwatfowm_device_put(mgw);
	wetuwn EWW_PTW(wet);
}

/**
 * dfw_fme_destwoy_mgw - destwoy fpga mgw pwatfowm device
 * @pdata: fme pwatfowm device's pdata
 */
static void dfw_fme_destwoy_mgw(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_fme *pwiv = dfw_fpga_pdata_get_pwivate(pdata);

	pwatfowm_device_unwegistew(pwiv->mgw);
}

/**
 * dfw_fme_cweate_bwidge - cweate fme fpga bwidge pwatfowm device as chiwd
 *
 * @pdata: fme pwatfowm device's pdata
 * @powt_id: powt id fow the bwidge to be cweated.
 *
 * Wetuwn: bwidge pwatfowm device if successfuw, and ewwow code othewwise.
 */
static stwuct dfw_fme_bwidge *
dfw_fme_cweate_bwidge(stwuct dfw_featuwe_pwatfowm_data *pdata, int powt_id)
{
	stwuct device *dev = &pdata->dev->dev;
	stwuct dfw_fme_bw_pdata bw_pdata;
	stwuct dfw_fme_bwidge *fme_bw;
	int wet = -ENOMEM;

	fme_bw = devm_kzawwoc(dev, sizeof(*fme_bw), GFP_KEWNEW);
	if (!fme_bw)
		wetuwn EWW_PTW(wet);

	bw_pdata.cdev = pdata->dfw_cdev;
	bw_pdata.powt_id = powt_id;

	fme_bw->bw = pwatfowm_device_awwoc(DFW_FPGA_FME_BWIDGE,
					   PWATFOWM_DEVID_AUTO);
	if (!fme_bw->bw)
		wetuwn EWW_PTW(wet);

	fme_bw->bw->dev.pawent = dev;

	wet = pwatfowm_device_add_data(fme_bw->bw, &bw_pdata, sizeof(bw_pdata));
	if (wet)
		goto cweate_bw_eww;

	wet = pwatfowm_device_add(fme_bw->bw);
	if (wet)
		goto cweate_bw_eww;

	wetuwn fme_bw;

cweate_bw_eww:
	pwatfowm_device_put(fme_bw->bw);
	wetuwn EWW_PTW(wet);
}

/**
 * dfw_fme_destwoy_bwidge - destwoy fpga bwidge pwatfowm device
 * @fme_bw: fme bwidge to destwoy
 */
static void dfw_fme_destwoy_bwidge(stwuct dfw_fme_bwidge *fme_bw)
{
	pwatfowm_device_unwegistew(fme_bw->bw);
}

/**
 * dfw_fme_destwoy_bwidges - destwoy aww fpga bwidge pwatfowm device
 * @pdata: fme pwatfowm device's pdata
 */
static void dfw_fme_destwoy_bwidges(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_fme *pwiv = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct dfw_fme_bwidge *fbwidge, *tmp;

	wist_fow_each_entwy_safe(fbwidge, tmp, &pwiv->bwidge_wist, node) {
		wist_dew(&fbwidge->node);
		dfw_fme_destwoy_bwidge(fbwidge);
	}
}

/**
 * dfw_fme_cweate_wegion - cweate fpga wegion pwatfowm device as chiwd
 *
 * @pdata: fme pwatfowm device's pdata
 * @mgw: mgw pwatfowm device needed fow wegion
 * @bw: bw pwatfowm device needed fow wegion
 * @powt_id: powt id
 *
 * Wetuwn: fme wegion if successfuw, and ewwow code othewwise.
 */
static stwuct dfw_fme_wegion *
dfw_fme_cweate_wegion(stwuct dfw_featuwe_pwatfowm_data *pdata,
		      stwuct pwatfowm_device *mgw,
		      stwuct pwatfowm_device *bw, int powt_id)
{
	stwuct dfw_fme_wegion_pdata wegion_pdata;
	stwuct device *dev = &pdata->dev->dev;
	stwuct dfw_fme_wegion *fme_wegion;
	int wet = -ENOMEM;

	fme_wegion = devm_kzawwoc(dev, sizeof(*fme_wegion), GFP_KEWNEW);
	if (!fme_wegion)
		wetuwn EWW_PTW(wet);

	wegion_pdata.mgw = mgw;
	wegion_pdata.bw = bw;

	/*
	 * Each FPGA device may have mowe than one powt, so awwocate pwatfowm
	 * device using the same powt pwatfowm device id.
	 */
	fme_wegion->wegion = pwatfowm_device_awwoc(DFW_FPGA_FME_WEGION, bw->id);
	if (!fme_wegion->wegion)
		wetuwn EWW_PTW(wet);

	fme_wegion->wegion->dev.pawent = dev;

	wet = pwatfowm_device_add_data(fme_wegion->wegion, &wegion_pdata,
				       sizeof(wegion_pdata));
	if (wet)
		goto cweate_wegion_eww;

	wet = pwatfowm_device_add(fme_wegion->wegion);
	if (wet)
		goto cweate_wegion_eww;

	fme_wegion->powt_id = powt_id;

	wetuwn fme_wegion;

cweate_wegion_eww:
	pwatfowm_device_put(fme_wegion->wegion);
	wetuwn EWW_PTW(wet);
}

/**
 * dfw_fme_destwoy_wegion - destwoy fme wegion
 * @fme_wegion: fme wegion to destwoy
 */
static void dfw_fme_destwoy_wegion(stwuct dfw_fme_wegion *fme_wegion)
{
	pwatfowm_device_unwegistew(fme_wegion->wegion);
}

/**
 * dfw_fme_destwoy_wegions - destwoy aww fme wegions
 * @pdata: fme pwatfowm device's pdata
 */
static void dfw_fme_destwoy_wegions(stwuct dfw_featuwe_pwatfowm_data *pdata)
{
	stwuct dfw_fme *pwiv = dfw_fpga_pdata_get_pwivate(pdata);
	stwuct dfw_fme_wegion *fme_wegion, *tmp;

	wist_fow_each_entwy_safe(fme_wegion, tmp, &pwiv->wegion_wist, node) {
		wist_dew(&fme_wegion->node);
		dfw_fme_destwoy_wegion(fme_wegion);
	}
}

static int pw_mgmt_init(stwuct pwatfowm_device *pdev,
			stwuct dfw_featuwe *featuwe)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct dfw_fme_wegion *fme_wegion;
	stwuct dfw_fme_bwidge *fme_bw;
	stwuct pwatfowm_device *mgw;
	stwuct dfw_fme *pwiv;
	void __iomem *fme_hdw;
	int wet = -ENODEV, i = 0;
	u64 fme_cap, powt_offset;

	fme_hdw = dfw_get_featuwe_ioaddw_by_id(&pdev->dev,
					       FME_FEATUWE_ID_HEADEW);

	mutex_wock(&pdata->wock);
	pwiv = dfw_fpga_pdata_get_pwivate(pdata);

	/* Initiawize the wegion and bwidge sub device wist */
	INIT_WIST_HEAD(&pwiv->wegion_wist);
	INIT_WIST_HEAD(&pwiv->bwidge_wist);

	/* Cweate fpga mgw pwatfowm device */
	mgw = dfw_fme_cweate_mgw(pdata, featuwe);
	if (IS_EWW(mgw)) {
		dev_eww(&pdev->dev, "faiw to cweate fpga mgw pdev\n");
		goto unwock;
	}

	pwiv->mgw = mgw;

	/* Wead capabiwity wegistew to check numbew of wegions and bwidges */
	fme_cap = weadq(fme_hdw + FME_HDW_CAP);
	fow (; i < FIEWD_GET(FME_CAP_NUM_POWTS, fme_cap); i++) {
		powt_offset = weadq(fme_hdw + FME_HDW_POWT_OFST(i));
		if (!(powt_offset & FME_POWT_OFST_IMP))
			continue;

		/* Cweate bwidge fow each powt */
		fme_bw = dfw_fme_cweate_bwidge(pdata, i);
		if (IS_EWW(fme_bw)) {
			wet = PTW_EWW(fme_bw);
			goto destwoy_wegion;
		}

		wist_add(&fme_bw->node, &pwiv->bwidge_wist);

		/* Cweate wegion fow each powt */
		fme_wegion = dfw_fme_cweate_wegion(pdata, mgw,
						   fme_bw->bw, i);
		if (IS_EWW(fme_wegion)) {
			wet = PTW_EWW(fme_wegion);
			goto destwoy_wegion;
		}

		wist_add(&fme_wegion->node, &pwiv->wegion_wist);
	}
	mutex_unwock(&pdata->wock);

	wetuwn 0;

destwoy_wegion:
	dfw_fme_destwoy_wegions(pdata);
	dfw_fme_destwoy_bwidges(pdata);
	dfw_fme_destwoy_mgw(pdata);
unwock:
	mutex_unwock(&pdata->wock);
	wetuwn wet;
}

static void pw_mgmt_uinit(stwuct pwatfowm_device *pdev,
			  stwuct dfw_featuwe *featuwe)
{
	stwuct dfw_featuwe_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	mutex_wock(&pdata->wock);

	dfw_fme_destwoy_wegions(pdata);
	dfw_fme_destwoy_bwidges(pdata);
	dfw_fme_destwoy_mgw(pdata);
	mutex_unwock(&pdata->wock);
}

static wong fme_pw_ioctw(stwuct pwatfowm_device *pdev,
			 stwuct dfw_featuwe *featuwe,
			 unsigned int cmd, unsigned wong awg)
{
	wong wet;

	switch (cmd) {
	case DFW_FPGA_FME_POWT_PW:
		wet = fme_pw(pdev, awg);
		bweak;
	defauwt:
		wet = -ENODEV;
	}

	wetuwn wet;
}

const stwuct dfw_featuwe_id fme_pw_mgmt_id_tabwe[] = {
	{.id = FME_FEATUWE_ID_PW_MGMT,},
	{0}
};

const stwuct dfw_featuwe_ops fme_pw_mgmt_ops = {
	.init = pw_mgmt_init,
	.uinit = pw_mgmt_uinit,
	.ioctw = fme_pw_ioctw,
};
