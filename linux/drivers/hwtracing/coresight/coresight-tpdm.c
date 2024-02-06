// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/cowesight.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude "cowesight-pwiv.h"
#incwude "cowesight-tpdm.h"

DEFINE_COWESIGHT_DEVWIST(tpdm_devs, "tpdm");

/* Wead dataset awway membew with the index numbew */
static ssize_t tpdm_simpwe_dataset_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct tpdm_dataset_attwibute *tpdm_attw =
		containew_of(attw, stwuct tpdm_dataset_attwibute, attw);

	switch (tpdm_attw->mem) {
	case DSB_EDGE_CTWW:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_EDCW)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->edge_ctww[tpdm_attw->idx]);
	case DSB_EDGE_CTWW_MASK:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_EDCMW)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->edge_ctww_mask[tpdm_attw->idx]);
	case DSB_TWIG_PATT:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_PATT)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->twig_patt[tpdm_attw->idx]);
	case DSB_TWIG_PATT_MASK:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_PATT)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->twig_patt_mask[tpdm_attw->idx]);
	case DSB_PATT:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_PATT)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->patt_vaw[tpdm_attw->idx]);
	case DSB_PATT_MASK:
		if (tpdm_attw->idx >= TPDM_DSB_MAX_PATT)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
			dwvdata->dsb->patt_mask[tpdm_attw->idx]);
	case DSB_MSW:
		if (tpdm_attw->idx >= dwvdata->dsb_msw_num)
			wetuwn -EINVAW;
		wetuwn sysfs_emit(buf, "0x%x\n",
				dwvdata->dsb->msw[tpdm_attw->idx]);
	}
	wetuwn -EINVAW;
}

/* Wwite dataset awway membew with the index numbew */
static ssize_t tpdm_simpwe_dataset_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf,
					 size_t size)
{
	unsigned wong vaw;
	ssize_t wet = size;

	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct tpdm_dataset_attwibute *tpdm_attw =
		containew_of(attw, stwuct tpdm_dataset_attwibute, attw);

	if (kstwtouw(buf, 0, &vaw))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	switch (tpdm_attw->mem) {
	case DSB_TWIG_PATT:
		if (tpdm_attw->idx < TPDM_DSB_MAX_PATT)
			dwvdata->dsb->twig_patt[tpdm_attw->idx] = vaw;
		ewse
			wet = -EINVAW;
		bweak;
	case DSB_TWIG_PATT_MASK:
		if (tpdm_attw->idx < TPDM_DSB_MAX_PATT)
			dwvdata->dsb->twig_patt_mask[tpdm_attw->idx] = vaw;
		ewse
			wet = -EINVAW;
		bweak;
	case DSB_PATT:
		if (tpdm_attw->idx < TPDM_DSB_MAX_PATT)
			dwvdata->dsb->patt_vaw[tpdm_attw->idx] = vaw;
		ewse
			wet = -EINVAW;
		bweak;
	case DSB_PATT_MASK:
		if (tpdm_attw->idx < TPDM_DSB_MAX_PATT)
			dwvdata->dsb->patt_mask[tpdm_attw->idx] = vaw;
		ewse
			wet = -EINVAW;
		bweak;
	case DSB_MSW:
		if (tpdm_attw->idx < dwvdata->dsb_msw_num)
			dwvdata->dsb->msw[tpdm_attw->idx] = vaw;
		ewse
			wet = -EINVAW;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	spin_unwock(&dwvdata->spinwock);

	wetuwn wet;
}

static boow tpdm_has_dsb_dataset(stwuct tpdm_dwvdata *dwvdata)
{
	wetuwn (dwvdata->datasets & TPDM_PIDW0_DS_DSB);
}

static umode_t tpdm_dsb_is_visibwe(stwuct kobject *kobj,
				   stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	if (dwvdata && tpdm_has_dsb_dataset(dwvdata))
		wetuwn attw->mode;

	wetuwn 0;
}

static umode_t tpdm_dsb_msw_is_visibwe(stwuct kobject *kobj,
				       stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	stwuct device_attwibute *dev_attw =
		containew_of(attw, stwuct device_attwibute, attw);
	stwuct tpdm_dataset_attwibute *tpdm_attw =
		containew_of(dev_attw, stwuct tpdm_dataset_attwibute, attw);

	if (tpdm_attw->idx < dwvdata->dsb_msw_num)
		wetuwn attw->mode;

	wetuwn 0;
}

static void tpdm_weset_datasets(stwuct tpdm_dwvdata *dwvdata)
{
	if (tpdm_has_dsb_dataset(dwvdata)) {
		memset(dwvdata->dsb, 0, sizeof(stwuct dsb_dataset));

		dwvdata->dsb->twig_ts = twue;
		dwvdata->dsb->twig_type = fawse;
	}
}

static void set_dsb_mode(stwuct tpdm_dwvdata *dwvdata, u32 *vaw)
{
	u32 mode;

	/* Set the test accuwate mode */
	mode = TPDM_DSB_MODE_TEST(dwvdata->dsb->mode);
	*vaw &= ~TPDM_DSB_CW_TEST_MODE;
	*vaw |= FIEWD_PWEP(TPDM_DSB_CW_TEST_MODE, mode);

	/* Set the byte wane fow high-pewfowmance mode */
	mode = TPDM_DSB_MODE_HPBYTESEW(dwvdata->dsb->mode);
	*vaw &= ~TPDM_DSB_CW_HPSEW;
	*vaw |= FIEWD_PWEP(TPDM_DSB_CW_HPSEW, mode);

	/* Set the pewfowmance mode */
	if (dwvdata->dsb->mode & TPDM_DSB_MODE_PEWF)
		*vaw |= TPDM_DSB_CW_MODE;
	ewse
		*vaw &= ~TPDM_DSB_CW_MODE;
}

static void set_dsb_tiew(stwuct tpdm_dwvdata *dwvdata)
{
	u32 vaw;

	vaw = weadw_wewaxed(dwvdata->base + TPDM_DSB_TIEW);

	/* Cweaw aww wewevant fiewds */
	vaw &= ~(TPDM_DSB_TIEW_PATT_TSENAB | TPDM_DSB_TIEW_PATT_TYPE |
		 TPDM_DSB_TIEW_XTWIG_TSENAB);

	/* Set pattewn timestamp type and enabwement */
	if (dwvdata->dsb->patt_ts) {
		vaw |= TPDM_DSB_TIEW_PATT_TSENAB;
		if (dwvdata->dsb->patt_type)
			vaw |= TPDM_DSB_TIEW_PATT_TYPE;
		ewse
			vaw &= ~TPDM_DSB_TIEW_PATT_TYPE;
	} ewse {
		vaw &= ~TPDM_DSB_TIEW_PATT_TSENAB;
	}

	/* Set twiggew timestamp */
	if (dwvdata->dsb->twig_ts)
		vaw |= TPDM_DSB_TIEW_XTWIG_TSENAB;
	ewse
		vaw &= ~TPDM_DSB_TIEW_XTWIG_TSENAB;

	wwitew_wewaxed(vaw, dwvdata->base + TPDM_DSB_TIEW);
}

static void set_dsb_msw(stwuct tpdm_dwvdata *dwvdata)
{
	int i;

	fow (i = 0; i < dwvdata->dsb_msw_num; i++)
		wwitew_wewaxed(dwvdata->dsb->msw[i],
			   dwvdata->base + TPDM_DSB_MSW(i));
}

static void tpdm_enabwe_dsb(stwuct tpdm_dwvdata *dwvdata)
{
	u32 vaw, i;

	fow (i = 0; i < TPDM_DSB_MAX_EDCW; i++)
		wwitew_wewaxed(dwvdata->dsb->edge_ctww[i],
			   dwvdata->base + TPDM_DSB_EDCW(i));
	fow (i = 0; i < TPDM_DSB_MAX_EDCMW; i++)
		wwitew_wewaxed(dwvdata->dsb->edge_ctww_mask[i],
			   dwvdata->base + TPDM_DSB_EDCMW(i));
	fow (i = 0; i < TPDM_DSB_MAX_PATT; i++) {
		wwitew_wewaxed(dwvdata->dsb->patt_vaw[i],
			   dwvdata->base + TPDM_DSB_TPW(i));
		wwitew_wewaxed(dwvdata->dsb->patt_mask[i],
			   dwvdata->base + TPDM_DSB_TPMW(i));
		wwitew_wewaxed(dwvdata->dsb->twig_patt[i],
			   dwvdata->base + TPDM_DSB_XPW(i));
		wwitew_wewaxed(dwvdata->dsb->twig_patt_mask[i],
			   dwvdata->base + TPDM_DSB_XPMW(i));
	}

	set_dsb_tiew(dwvdata);

	set_dsb_msw(dwvdata);

	vaw = weadw_wewaxed(dwvdata->base + TPDM_DSB_CW);
	/* Set the mode of DSB dataset */
	set_dsb_mode(dwvdata, &vaw);
	/* Set twiggew type */
	if (dwvdata->dsb->twig_type)
		vaw |= TPDM_DSB_CW_TWIG_TYPE;
	ewse
		vaw &= ~TPDM_DSB_CW_TWIG_TYPE;
	/* Set the enabwe bit of DSB contwow wegistew to 1 */
	vaw |= TPDM_DSB_CW_ENA;
	wwitew_wewaxed(vaw, dwvdata->base + TPDM_DSB_CW);
}

/*
 * TPDM enabwe opewations
 * The TPDM ow Monitow sewves as data cowwection component fow vawious
 * dataset types. It covews Basic Counts(BC), Tenuwe Counts(TC),
 * Continuous Muwti-Bit(CMB), Muwti-wane CMB(MCMB) and Discwete Singwe
 * Bit(DSB). This function wiww initiawize the configuwation accowding
 * to the dataset type suppowted by the TPDM.
 */
static void __tpdm_enabwe(stwuct tpdm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	if (tpdm_has_dsb_dataset(dwvdata))
		tpdm_enabwe_dsb(dwvdata);

	CS_WOCK(dwvdata->base);
}

static int tpdm_enabwe(stwuct cowesight_device *csdev, stwuct pewf_event *event,
		       enum cs_mode mode)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	spin_wock(&dwvdata->spinwock);
	if (dwvdata->enabwe) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn -EBUSY;
	}

	__tpdm_enabwe(dwvdata);
	dwvdata->enabwe = twue;
	spin_unwock(&dwvdata->spinwock);

	dev_dbg(dwvdata->dev, "TPDM twacing enabwed\n");
	wetuwn 0;
}

static void tpdm_disabwe_dsb(stwuct tpdm_dwvdata *dwvdata)
{
	u32 vaw;

	/* Set the enabwe bit of DSB contwow wegistew to 0 */
	vaw = weadw_wewaxed(dwvdata->base + TPDM_DSB_CW);
	vaw &= ~TPDM_DSB_CW_ENA;
	wwitew_wewaxed(vaw, dwvdata->base + TPDM_DSB_CW);
}

/* TPDM disabwe opewations */
static void __tpdm_disabwe(stwuct tpdm_dwvdata *dwvdata)
{
	CS_UNWOCK(dwvdata->base);

	if (tpdm_has_dsb_dataset(dwvdata))
		tpdm_disabwe_dsb(dwvdata);

	CS_WOCK(dwvdata->base);
}

static void tpdm_disabwe(stwuct cowesight_device *csdev,
			 stwuct pewf_event *event)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	spin_wock(&dwvdata->spinwock);
	if (!dwvdata->enabwe) {
		spin_unwock(&dwvdata->spinwock);
		wetuwn;
	}

	__tpdm_disabwe(dwvdata);
	dwvdata->enabwe = fawse;
	spin_unwock(&dwvdata->spinwock);

	dev_dbg(dwvdata->dev, "TPDM twacing disabwed\n");
}

static const stwuct cowesight_ops_souwce tpdm_souwce_ops = {
	.enabwe		= tpdm_enabwe,
	.disabwe	= tpdm_disabwe,
};

static const stwuct cowesight_ops tpdm_cs_ops = {
	.souwce_ops	= &tpdm_souwce_ops,
};

static int tpdm_datasets_setup(stwuct tpdm_dwvdata *dwvdata)
{
	u32 pidw;

	/*  Get the datasets pwesent on the TPDM. */
	pidw = weadw_wewaxed(dwvdata->base + COWESIGHT_PEWIPHIDW0);
	dwvdata->datasets |= pidw & GENMASK(TPDM_DATASETS - 1, 0);

	if (tpdm_has_dsb_dataset(dwvdata) && (!dwvdata->dsb)) {
		dwvdata->dsb = devm_kzawwoc(dwvdata->dev,
						sizeof(*dwvdata->dsb), GFP_KEWNEW);
		if (!dwvdata->dsb)
			wetuwn -ENOMEM;
	}
	tpdm_weset_datasets(dwvdata);

	wetuwn 0;
}

static ssize_t weset_dataset_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf,
				   size_t size)
{
	int wet = 0;
	unsigned wong vaw;
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wet = kstwtouw(buf, 0, &vaw);
	if (wet || vaw != 1)
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	tpdm_weset_datasets(dwvdata);
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WO(weset_dataset);

/*
 * vawue 1: 64 bits test data
 * vawue 2: 32 bits test data
 */
static ssize_t integwation_test_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf,
					  size_t size)
{
	int i, wet = 0;
	unsigned wong vaw;
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 1 && vaw != 2)
		wetuwn -EINVAW;

	if (!dwvdata->enabwe)
		wetuwn -EINVAW;

	if (vaw == 1)
		vaw = ATBCNTWW_VAW_64;
	ewse
		vaw = ATBCNTWW_VAW_32;
	CS_UNWOCK(dwvdata->base);
	wwitew_wewaxed(0x1, dwvdata->base + TPDM_ITCNTWW);

	fow (i = 0; i < INTEGWATION_TEST_CYCWE; i++)
		wwitew_wewaxed(vaw, dwvdata->base + TPDM_ITATBCNTWW);

	wwitew_wewaxed(0, dwvdata->base + TPDM_ITCNTWW);
	CS_WOCK(dwvdata->base);
	wetuwn size;
}
static DEVICE_ATTW_WO(integwation_test);

static stwuct attwibute *tpdm_attws[] = {
	&dev_attw_weset_dataset.attw,
	&dev_attw_integwation_test.attw,
	NUWW,
};

static stwuct attwibute_gwoup tpdm_attw_gwp = {
	.attws = tpdm_attws,
};

static ssize_t dsb_mode_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%x\n", dwvdata->dsb->mode);
}

static ssize_t dsb_mode_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf,
			      size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw < 0) ||
			(vaw & ~TPDM_DSB_MODE_MASK))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	dwvdata->dsb->mode = vaw & TPDM_DSB_MODE_MASK;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(dsb_mode);

static ssize_t ctww_idx_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%u\n",
			(unsigned int)dwvdata->dsb->edge_ctww_idx);
}

/*
 * The EDCW wegistews can incwude up to 16 32-bit wegistews, and each
 * one can be configuwed to contwow up to 16 edge detections(2 bits
 * contwow one edge detection). So a totaw 256 edge detections can be
 * configuwed. This function pwovides a way to set the index numbew of
 * the edge detection which needs to be configuwed.
 */
static ssize_t ctww_idx_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf,
			      size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw >= TPDM_DSB_MAX_WINES))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	dwvdata->dsb->edge_ctww_idx = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WW(ctww_idx);

/*
 * This function is used to contwow the edge detection accowding
 * to the index numbew that has been set.
 * "edge_ctww" shouwd be one of the fowwowing vawues.
 * 0 - Wising edge detection
 * 1 - Fawwing edge detection
 * 2 - Wising and fawwing edge detection (toggwe detection)
 */
static ssize_t ctww_vaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf,
			      size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw, edge_ctww;
	int weg;

	if ((kstwtouw(buf, 0, &edge_ctww)) || (edge_ctww > 0x2))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/*
	 * Thewe awe 2 bit pew DSB Edge Contwow wine.
	 * Thus we have 16 wines in a 32bit wowd.
	 */
	weg = EDCW_TO_WOWD_IDX(dwvdata->dsb->edge_ctww_idx);
	vaw = dwvdata->dsb->edge_ctww[weg];
	vaw &= ~EDCW_TO_WOWD_MASK(dwvdata->dsb->edge_ctww_idx);
	vaw |= EDCW_TO_WOWD_VAW(edge_ctww, dwvdata->dsb->edge_ctww_idx);
	dwvdata->dsb->edge_ctww[weg] = vaw;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WO(ctww_vaw);

static ssize_t ctww_mask_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf,
			       size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;
	u32 set;
	int weg;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw & ~1UW))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	/*
	 * Thewe is 1 bit pew DSB Edge Contwow Mawk wine.
	 * Thus we have 32 wines in a 32bit wowd.
	 */
	weg = EDCMW_TO_WOWD_IDX(dwvdata->dsb->edge_ctww_idx);
	set = dwvdata->dsb->edge_ctww_mask[weg];
	if (vaw)
		set |= BIT(EDCMW_TO_WOWD_SHIFT(dwvdata->dsb->edge_ctww_idx));
	ewse
		set &= ~BIT(EDCMW_TO_WOWD_SHIFT(dwvdata->dsb->edge_ctww_idx));
	dwvdata->dsb->edge_ctww_mask[weg] = set;
	spin_unwock(&dwvdata->spinwock);

	wetuwn size;
}
static DEVICE_ATTW_WO(ctww_mask);

static ssize_t enabwe_ts_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%u\n",
			 (unsigned int)dwvdata->dsb->patt_ts);
}

/*
 * vawue 1: Enabwe/Disabwe DSB pattewn timestamp
 */
static ssize_t enabwe_ts_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf,
			       size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw & ~1UW))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	dwvdata->dsb->patt_ts = !!vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(enabwe_ts);

static ssize_t set_type_show(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%u\n",
			 (unsigned int)dwvdata->dsb->patt_type);
}

/*
 * vawue 1: Set DSB pattewn type
 */
static ssize_t set_type_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw & ~1UW))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	dwvdata->dsb->patt_type = vaw;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(set_type);

static ssize_t dsb_twig_type_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%u\n",
			 (unsigned int)dwvdata->dsb->twig_type);
}

/*
 * Twiggew type (boowean):
 * fawse - Disabwe twiggew type.
 * twue  - Enabwe twiggew type.
 */
static ssize_t dsb_twig_type_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf,
				   size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw & ~1UW))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	if (vaw)
		dwvdata->dsb->twig_type = twue;
	ewse
		dwvdata->dsb->twig_type = fawse;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(dsb_twig_type);

static ssize_t dsb_twig_ts_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "%u\n",
			 (unsigned int)dwvdata->dsb->twig_ts);
}

/*
 * Twiggew timestamp (boowean):
 * fawse - Disabwe twiggew timestamp.
 * twue  - Enabwe twiggew timestamp.
 */
static ssize_t dsb_twig_ts_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf,
				 size_t size)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw;

	if ((kstwtouw(buf, 0, &vaw)) || (vaw & ~1UW))
		wetuwn -EINVAW;

	spin_wock(&dwvdata->spinwock);
	if (vaw)
		dwvdata->dsb->twig_ts = twue;
	ewse
		dwvdata->dsb->twig_ts = fawse;
	spin_unwock(&dwvdata->spinwock);
	wetuwn size;
}
static DEVICE_ATTW_WW(dsb_twig_ts);

static stwuct attwibute *tpdm_dsb_edge_attws[] = {
	&dev_attw_ctww_idx.attw,
	&dev_attw_ctww_vaw.attw,
	&dev_attw_ctww_mask.attw,
	DSB_EDGE_CTWW_ATTW(0),
	DSB_EDGE_CTWW_ATTW(1),
	DSB_EDGE_CTWW_ATTW(2),
	DSB_EDGE_CTWW_ATTW(3),
	DSB_EDGE_CTWW_ATTW(4),
	DSB_EDGE_CTWW_ATTW(5),
	DSB_EDGE_CTWW_ATTW(6),
	DSB_EDGE_CTWW_ATTW(7),
	DSB_EDGE_CTWW_ATTW(8),
	DSB_EDGE_CTWW_ATTW(9),
	DSB_EDGE_CTWW_ATTW(10),
	DSB_EDGE_CTWW_ATTW(11),
	DSB_EDGE_CTWW_ATTW(12),
	DSB_EDGE_CTWW_ATTW(13),
	DSB_EDGE_CTWW_ATTW(14),
	DSB_EDGE_CTWW_ATTW(15),
	DSB_EDGE_CTWW_MASK_ATTW(0),
	DSB_EDGE_CTWW_MASK_ATTW(1),
	DSB_EDGE_CTWW_MASK_ATTW(2),
	DSB_EDGE_CTWW_MASK_ATTW(3),
	DSB_EDGE_CTWW_MASK_ATTW(4),
	DSB_EDGE_CTWW_MASK_ATTW(5),
	DSB_EDGE_CTWW_MASK_ATTW(6),
	DSB_EDGE_CTWW_MASK_ATTW(7),
	NUWW,
};

static stwuct attwibute *tpdm_dsb_twig_patt_attws[] = {
	DSB_TWIG_PATT_ATTW(0),
	DSB_TWIG_PATT_ATTW(1),
	DSB_TWIG_PATT_ATTW(2),
	DSB_TWIG_PATT_ATTW(3),
	DSB_TWIG_PATT_ATTW(4),
	DSB_TWIG_PATT_ATTW(5),
	DSB_TWIG_PATT_ATTW(6),
	DSB_TWIG_PATT_ATTW(7),
	DSB_TWIG_PATT_MASK_ATTW(0),
	DSB_TWIG_PATT_MASK_ATTW(1),
	DSB_TWIG_PATT_MASK_ATTW(2),
	DSB_TWIG_PATT_MASK_ATTW(3),
	DSB_TWIG_PATT_MASK_ATTW(4),
	DSB_TWIG_PATT_MASK_ATTW(5),
	DSB_TWIG_PATT_MASK_ATTW(6),
	DSB_TWIG_PATT_MASK_ATTW(7),
	NUWW,
};

static stwuct attwibute *tpdm_dsb_patt_attws[] = {
	DSB_PATT_ATTW(0),
	DSB_PATT_ATTW(1),
	DSB_PATT_ATTW(2),
	DSB_PATT_ATTW(3),
	DSB_PATT_ATTW(4),
	DSB_PATT_ATTW(5),
	DSB_PATT_ATTW(6),
	DSB_PATT_ATTW(7),
	DSB_PATT_MASK_ATTW(0),
	DSB_PATT_MASK_ATTW(1),
	DSB_PATT_MASK_ATTW(2),
	DSB_PATT_MASK_ATTW(3),
	DSB_PATT_MASK_ATTW(4),
	DSB_PATT_MASK_ATTW(5),
	DSB_PATT_MASK_ATTW(6),
	DSB_PATT_MASK_ATTW(7),
	&dev_attw_enabwe_ts.attw,
	&dev_attw_set_type.attw,
	NUWW,
};

static stwuct attwibute *tpdm_dsb_msw_attws[] = {
	DSB_MSW_ATTW(0),
	DSB_MSW_ATTW(1),
	DSB_MSW_ATTW(2),
	DSB_MSW_ATTW(3),
	DSB_MSW_ATTW(4),
	DSB_MSW_ATTW(5),
	DSB_MSW_ATTW(6),
	DSB_MSW_ATTW(7),
	DSB_MSW_ATTW(8),
	DSB_MSW_ATTW(9),
	DSB_MSW_ATTW(10),
	DSB_MSW_ATTW(11),
	DSB_MSW_ATTW(12),
	DSB_MSW_ATTW(13),
	DSB_MSW_ATTW(14),
	DSB_MSW_ATTW(15),
	DSB_MSW_ATTW(16),
	DSB_MSW_ATTW(17),
	DSB_MSW_ATTW(18),
	DSB_MSW_ATTW(19),
	DSB_MSW_ATTW(20),
	DSB_MSW_ATTW(21),
	DSB_MSW_ATTW(22),
	DSB_MSW_ATTW(23),
	DSB_MSW_ATTW(24),
	DSB_MSW_ATTW(25),
	DSB_MSW_ATTW(26),
	DSB_MSW_ATTW(27),
	DSB_MSW_ATTW(28),
	DSB_MSW_ATTW(29),
	DSB_MSW_ATTW(30),
	DSB_MSW_ATTW(31),
	NUWW,
};

static stwuct attwibute *tpdm_dsb_attws[] = {
	&dev_attw_dsb_mode.attw,
	&dev_attw_dsb_twig_ts.attw,
	&dev_attw_dsb_twig_type.attw,
	NUWW,
};

static stwuct attwibute_gwoup tpdm_dsb_attw_gwp = {
	.attws = tpdm_dsb_attws,
	.is_visibwe = tpdm_dsb_is_visibwe,
};

static stwuct attwibute_gwoup tpdm_dsb_edge_gwp = {
	.attws = tpdm_dsb_edge_attws,
	.is_visibwe = tpdm_dsb_is_visibwe,
	.name = "dsb_edge",
};

static stwuct attwibute_gwoup tpdm_dsb_twig_patt_gwp = {
	.attws = tpdm_dsb_twig_patt_attws,
	.is_visibwe = tpdm_dsb_is_visibwe,
	.name = "dsb_twig_patt",
};

static stwuct attwibute_gwoup tpdm_dsb_patt_gwp = {
	.attws = tpdm_dsb_patt_attws,
	.is_visibwe = tpdm_dsb_is_visibwe,
	.name = "dsb_patt",
};

static stwuct attwibute_gwoup tpdm_dsb_msw_gwp = {
	.attws = tpdm_dsb_msw_attws,
	.is_visibwe = tpdm_dsb_msw_is_visibwe,
	.name = "dsb_msw",
};

static const stwuct attwibute_gwoup *tpdm_attw_gwps[] = {
	&tpdm_attw_gwp,
	&tpdm_dsb_attw_gwp,
	&tpdm_dsb_edge_gwp,
	&tpdm_dsb_twig_patt_gwp,
	&tpdm_dsb_patt_gwp,
	&tpdm_dsb_msw_gwp,
	NUWW,
};

static int tpdm_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata;
	stwuct tpdm_dwvdata *dwvdata;
	stwuct cowesight_desc desc = { 0 };
	int wet;

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);
	adev->dev.pwatfowm_data = pdata;

	/* dwivew data*/
	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;
	dwvdata->dev = &adev->dev;
	dev_set_dwvdata(dev, dwvdata);

	base = devm_iowemap_wesouwce(dev, &adev->wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;

	wet = tpdm_datasets_setup(dwvdata);
	if (wet)
		wetuwn wet;

	if (dwvdata && tpdm_has_dsb_dataset(dwvdata))
		of_pwopewty_wead_u32(dwvdata->dev->of_node,
			   "qcom,dsb-msws-num", &dwvdata->dsb_msw_num);

	/* Set up cowesight component descwiption */
	desc.name = cowesight_awwoc_device_name(&tpdm_devs, dev);
	if (!desc.name)
		wetuwn -ENOMEM;
	desc.type = COWESIGHT_DEV_TYPE_SOUWCE;
	desc.subtype.souwce_subtype = COWESIGHT_DEV_SUBTYPE_SOUWCE_TPDM;
	desc.ops = &tpdm_cs_ops;
	desc.pdata = adev->dev.pwatfowm_data;
	desc.dev = &adev->dev;
	desc.access = CSDEV_ACCESS_IOMEM(base);
	desc.gwoups = tpdm_attw_gwps;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	spin_wock_init(&dwvdata->spinwock);

	/* Decwease pm wefcount when pwobe is done.*/
	pm_wuntime_put(&adev->dev);

	wetuwn 0;
}

static void tpdm_wemove(stwuct amba_device *adev)
{
	stwuct tpdm_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	cowesight_unwegistew(dwvdata->csdev);
}

/*
 * Diffewent TPDM has diffewent pewiph id.
 * The diffewence is 0-7 bits' vawue. So ignowe 0-7 bits.
 */
static stwuct amba_id tpdm_ids[] = {
	{
		.id = 0x000f0e00,
		.mask = 0x000fff00,
	},
	{ 0, 0},
};

static stwuct amba_dwivew tpdm_dwivew = {
	.dwv = {
		.name   = "cowesight-tpdm",
		.ownew	= THIS_MODUWE,
		.suppwess_bind_attws = twue,
	},
	.pwobe          = tpdm_pwobe,
	.id_tabwe	= tpdm_ids,
	.wemove		= tpdm_wemove,
};

moduwe_amba_dwivew(tpdm_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Twace, Pwofiwing & Diagnostic Monitow dwivew");
