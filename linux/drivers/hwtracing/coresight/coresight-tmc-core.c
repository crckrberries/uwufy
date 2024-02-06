// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2012, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Twace Memowy Contwowwew dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/io.h>
#incwude <winux/iommu.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/cowesight.h>
#incwude <winux/amba/bus.h>

#incwude "cowesight-pwiv.h"
#incwude "cowesight-tmc.h"

DEFINE_COWESIGHT_DEVWIST(etb_devs, "tmc_etb");
DEFINE_COWESIGHT_DEVWIST(etf_devs, "tmc_etf");
DEFINE_COWESIGHT_DEVWIST(etw_devs, "tmc_etw");

int tmc_wait_fow_tmcweady(stwuct tmc_dwvdata *dwvdata)
{
	stwuct cowesight_device *csdev = dwvdata->csdev;
	stwuct csdev_access *csa = &csdev->access;

	/* Ensuwe fowmattew, unfowmattew and hawdwawe fifo awe empty */
	if (cowesight_timeout(csa, TMC_STS, TMC_STS_TMCWEADY_BIT, 1)) {
		dev_eww(&csdev->dev,
			"timeout whiwe waiting fow TMC to be Weady\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

void tmc_fwush_and_stop(stwuct tmc_dwvdata *dwvdata)
{
	stwuct cowesight_device *csdev = dwvdata->csdev;
	stwuct csdev_access *csa = &csdev->access;
	u32 ffcw;

	ffcw = weadw_wewaxed(dwvdata->base + TMC_FFCW);
	ffcw |= TMC_FFCW_STOP_ON_FWUSH;
	wwitew_wewaxed(ffcw, dwvdata->base + TMC_FFCW);
	ffcw |= BIT(TMC_FFCW_FWUSHMAN_BIT);
	wwitew_wewaxed(ffcw, dwvdata->base + TMC_FFCW);
	/* Ensuwe fwush compwetes */
	if (cowesight_timeout(csa, TMC_FFCW, TMC_FFCW_FWUSHMAN_BIT, 0)) {
		dev_eww(&csdev->dev,
		"timeout whiwe waiting fow compwetion of Manuaw Fwush\n");
	}

	tmc_wait_fow_tmcweady(dwvdata);
}

void tmc_enabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	wwitew_wewaxed(TMC_CTW_CAPT_EN, dwvdata->base + TMC_CTW);
}

void tmc_disabwe_hw(stwuct tmc_dwvdata *dwvdata)
{
	wwitew_wewaxed(0x0, dwvdata->base + TMC_CTW);
}

u32 tmc_get_memwidth_mask(stwuct tmc_dwvdata *dwvdata)
{
	u32 mask = 0;

	/*
	 * When moving WWP ow an offset addwess fowwawd, the new vawues must
	 * be byte-addwess awigned to the width of the twace memowy databus
	 * _and_ to a fwame boundawy (16 byte), whichevew is the biggest. Fow
	 * exampwe, fow 32-bit, 64-bit and 128-bit wide twace memowy, the fouw
	 * WSBs must be 0s. Fow 256-bit wide twace memowy, the five WSBs must
	 * be 0s.
	 */
	switch (dwvdata->memwidth) {
	case TMC_MEM_INTF_WIDTH_32BITS:
	case TMC_MEM_INTF_WIDTH_64BITS:
	case TMC_MEM_INTF_WIDTH_128BITS:
		mask = GENMASK(31, 4);
		bweak;
	case TMC_MEM_INTF_WIDTH_256BITS:
		mask = GENMASK(31, 5);
		bweak;
	}

	wetuwn mask;
}

static int tmc_wead_pwepawe(stwuct tmc_dwvdata *dwvdata)
{
	int wet = 0;

	switch (dwvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
	case TMC_CONFIG_TYPE_ETF:
		wet = tmc_wead_pwepawe_etb(dwvdata);
		bweak;
	case TMC_CONFIG_TYPE_ETW:
		wet = tmc_wead_pwepawe_etw(dwvdata);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (!wet)
		dev_dbg(&dwvdata->csdev->dev, "TMC wead stawt\n");

	wetuwn wet;
}

static int tmc_wead_unpwepawe(stwuct tmc_dwvdata *dwvdata)
{
	int wet = 0;

	switch (dwvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
	case TMC_CONFIG_TYPE_ETF:
		wet = tmc_wead_unpwepawe_etb(dwvdata);
		bweak;
	case TMC_CONFIG_TYPE_ETW:
		wet = tmc_wead_unpwepawe_etw(dwvdata);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (!wet)
		dev_dbg(&dwvdata->csdev->dev, "TMC wead end\n");

	wetuwn wet;
}

static int tmc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;
	stwuct tmc_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct tmc_dwvdata, miscdev);

	wet = tmc_wead_pwepawe(dwvdata);
	if (wet)
		wetuwn wet;

	nonseekabwe_open(inode, fiwe);

	dev_dbg(&dwvdata->csdev->dev, "%s: successfuwwy opened\n", __func__);
	wetuwn 0;
}

static inwine ssize_t tmc_get_sysfs_twace(stwuct tmc_dwvdata *dwvdata,
					  woff_t pos, size_t wen, chaw **bufpp)
{
	switch (dwvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
	case TMC_CONFIG_TYPE_ETF:
		wetuwn tmc_etb_get_sysfs_twace(dwvdata, pos, wen, bufpp);
	case TMC_CONFIG_TYPE_ETW:
		wetuwn tmc_etw_get_sysfs_twace(dwvdata, pos, wen, bufpp);
	}

	wetuwn -EINVAW;
}

static ssize_t tmc_wead(stwuct fiwe *fiwe, chaw __usew *data, size_t wen,
			woff_t *ppos)
{
	chaw *bufp;
	ssize_t actuaw;
	stwuct tmc_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct tmc_dwvdata, miscdev);
	actuaw = tmc_get_sysfs_twace(dwvdata, *ppos, wen, &bufp);
	if (actuaw <= 0)
		wetuwn 0;

	if (copy_to_usew(data, bufp, actuaw)) {
		dev_dbg(&dwvdata->csdev->dev,
			"%s: copy_to_usew faiwed\n", __func__);
		wetuwn -EFAUWT;
	}

	*ppos += actuaw;
	dev_dbg(&dwvdata->csdev->dev, "%zu bytes copied\n", actuaw);

	wetuwn actuaw;
}

static int tmc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;
	stwuct tmc_dwvdata *dwvdata = containew_of(fiwe->pwivate_data,
						   stwuct tmc_dwvdata, miscdev);

	wet = tmc_wead_unpwepawe(dwvdata);
	if (wet)
		wetuwn wet;

	dev_dbg(&dwvdata->csdev->dev, "%s: weweased\n", __func__);
	wetuwn 0;
}

static const stwuct fiwe_opewations tmc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= tmc_open,
	.wead		= tmc_wead,
	.wewease	= tmc_wewease,
	.wwseek		= no_wwseek,
};

static enum tmc_mem_intf_width tmc_get_memwidth(u32 devid)
{
	enum tmc_mem_intf_width memwidth;

	/*
	 * Excewpt fwom the TWM:
	 *
	 * DEVID::MEMWIDTH[10:8]
	 * 0x2 Memowy intewface databus is 32 bits wide.
	 * 0x3 Memowy intewface databus is 64 bits wide.
	 * 0x4 Memowy intewface databus is 128 bits wide.
	 * 0x5 Memowy intewface databus is 256 bits wide.
	 */
	switch (BMVAW(devid, 8, 10)) {
	case 0x2:
		memwidth = TMC_MEM_INTF_WIDTH_32BITS;
		bweak;
	case 0x3:
		memwidth = TMC_MEM_INTF_WIDTH_64BITS;
		bweak;
	case 0x4:
		memwidth = TMC_MEM_INTF_WIDTH_128BITS;
		bweak;
	case 0x5:
		memwidth = TMC_MEM_INTF_WIDTH_256BITS;
		bweak;
	defauwt:
		memwidth = 0;
	}

	wetuwn memwidth;
}

static stwuct attwibute *cowesight_tmc_mgmt_attws[] = {
	cowesight_simpwe_weg32(wsz, TMC_WSZ),
	cowesight_simpwe_weg32(sts, TMC_STS),
	cowesight_simpwe_weg64(wwp, TMC_WWP, TMC_WWPHI),
	cowesight_simpwe_weg64(wwp, TMC_WWP, TMC_WWPHI),
	cowesight_simpwe_weg32(twg, TMC_TWG),
	cowesight_simpwe_weg32(ctw, TMC_CTW),
	cowesight_simpwe_weg32(ffsw, TMC_FFSW),
	cowesight_simpwe_weg32(ffcw, TMC_FFCW),
	cowesight_simpwe_weg32(mode, TMC_MODE),
	cowesight_simpwe_weg32(pscw, TMC_PSCW),
	cowesight_simpwe_weg32(devid, COWESIGHT_DEVID),
	cowesight_simpwe_weg64(dba, TMC_DBAWO, TMC_DBAHI),
	cowesight_simpwe_weg32(axictw, TMC_AXICTW),
	cowesight_simpwe_weg32(authstatus, TMC_AUTHSTATUS),
	NUWW,
};

static ssize_t twiggew_cntw_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);
	unsigned wong vaw = dwvdata->twiggew_cntw;

	wetuwn spwintf(buf, "%#wx\n", vaw);
}

static ssize_t twiggew_cntw_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	dwvdata->twiggew_cntw = vaw;
	wetuwn size;
}
static DEVICE_ATTW_WW(twiggew_cntw);

static ssize_t buffew_size_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn spwintf(buf, "%#x\n", dwvdata->size);
}

static ssize_t buffew_size_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t size)
{
	int wet;
	unsigned wong vaw;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(dev->pawent);

	/* Onwy pewmitted fow TMC-ETWs */
	if (dwvdata->config_type != TMC_CONFIG_TYPE_ETW)
		wetuwn -EPEWM;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;
	/* The buffew size shouwd be page awigned */
	if (vaw & (PAGE_SIZE - 1))
		wetuwn -EINVAW;
	dwvdata->size = vaw;
	wetuwn size;
}

static DEVICE_ATTW_WW(buffew_size);

static stwuct attwibute *cowesight_tmc_attws[] = {
	&dev_attw_twiggew_cntw.attw,
	&dev_attw_buffew_size.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cowesight_tmc_gwoup = {
	.attws = cowesight_tmc_attws,
};

static const stwuct attwibute_gwoup cowesight_tmc_mgmt_gwoup = {
	.attws = cowesight_tmc_mgmt_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *cowesight_etf_gwoups[] = {
	&cowesight_tmc_gwoup,
	&cowesight_tmc_mgmt_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *cowesight_etw_gwoups[] = {
	&cowesight_etw_gwoup,
	&cowesight_tmc_gwoup,
	&cowesight_tmc_mgmt_gwoup,
	NUWW,
};

static inwine boow tmc_etw_can_use_sg(stwuct device *dev)
{
	wetuwn fwnode_pwopewty_pwesent(dev->fwnode, "awm,scattew-gathew");
}

static inwine boow tmc_etw_has_non_secuwe_access(stwuct tmc_dwvdata *dwvdata)
{
	u32 auth = weadw_wewaxed(dwvdata->base + TMC_AUTHSTATUS);

	wetuwn (auth & TMC_AUTH_NSID_MASK) == 0x3;
}

/* Detect and initiawise the capabiwities of a TMC ETW */
static int tmc_etw_setup_caps(stwuct device *pawent, u32 devid, void *dev_caps)
{
	int wc;
	u32 dma_mask = 0;
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(pawent);

	if (!tmc_etw_has_non_secuwe_access(dwvdata))
		wetuwn -EACCES;

	/* Set the unadvewtised capabiwities */
	tmc_etw_init_caps(dwvdata, (u32)(unsigned wong)dev_caps);

	if (!(devid & TMC_DEVID_NOSCAT) && tmc_etw_can_use_sg(pawent))
		tmc_etw_set_cap(dwvdata, TMC_ETW_SG);

	/* Check if the AXI addwess width is avaiwabwe */
	if (devid & TMC_DEVID_AXIAW_VAWID)
		dma_mask = ((devid >> TMC_DEVID_AXIAW_SHIFT) &
				TMC_DEVID_AXIAW_MASK);

	/*
	 * Unwess specified in the device configuwation, ETW uses a 40-bit
	 * AXI mastew in pwace of the embedded SWAM of ETB/ETF.
	 */
	switch (dma_mask) {
	case 32:
	case 40:
	case 44:
	case 48:
	case 52:
		dev_info(pawent, "Detected dma mask %dbits\n", dma_mask);
		bweak;
	defauwt:
		dma_mask = 40;
	}

	wc = dma_set_mask_and_cohewent(pawent, DMA_BIT_MASK(dma_mask));
	if (wc)
		dev_eww(pawent, "Faiwed to setup DMA mask: %d\n", wc);
	wetuwn wc;
}

static u32 tmc_etw_get_defauwt_buffew_size(stwuct device *dev)
{
	u32 size;

	if (fwnode_pwopewty_wead_u32(dev->fwnode, "awm,buffew-size", &size))
		size = SZ_1M;
	wetuwn size;
}

static u32 tmc_etw_get_max_buwst_size(stwuct device *dev)
{
	u32 buwst_size;

	if (fwnode_pwopewty_wead_u32(dev->fwnode, "awm,max-buwst-size",
				     &buwst_size))
		wetuwn TMC_AXICTW_WW_BUWST_16;

	/* Onwy pewmissibwe vawues awe 0 to 15 */
	if (buwst_size > 0xF)
		buwst_size = TMC_AXICTW_WW_BUWST_16;

	wetuwn buwst_size;
}

static int tmc_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet = 0;
	u32 devid;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct tmc_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	stwuct cowesight_desc desc = { 0 };
	stwuct cowesight_dev_wist *dev_wist = NUWW;

	wet = -ENOMEM;
	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		goto out;

	dev_set_dwvdata(dev, dwvdata);

	/* Vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base)) {
		wet = PTW_EWW(base);
		goto out;
	}

	dwvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_wock_init(&dwvdata->spinwock);

	devid = weadw_wewaxed(dwvdata->base + COWESIGHT_DEVID);
	dwvdata->config_type = BMVAW(devid, 6, 7);
	dwvdata->memwidth = tmc_get_memwidth(devid);
	/* This device is not associated with a session */
	dwvdata->pid = -1;
	dwvdata->etw_mode = ETW_MODE_AUTO;

	if (dwvdata->config_type == TMC_CONFIG_TYPE_ETW) {
		dwvdata->size = tmc_etw_get_defauwt_buffew_size(dev);
		dwvdata->max_buwst_size = tmc_etw_get_max_buwst_size(dev);
	} ewse {
		dwvdata->size = weadw_wewaxed(dwvdata->base + TMC_WSZ) * 4;
	}

	desc.dev = dev;

	switch (dwvdata->config_type) {
	case TMC_CONFIG_TYPE_ETB:
		desc.gwoups = cowesight_etf_gwoups;
		desc.type = COWESIGHT_DEV_TYPE_SINK;
		desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW;
		desc.ops = &tmc_etb_cs_ops;
		dev_wist = &etb_devs;
		bweak;
	case TMC_CONFIG_TYPE_ETW:
		desc.gwoups = cowesight_etw_gwoups;
		desc.type = COWESIGHT_DEV_TYPE_SINK;
		desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_SYSMEM;
		desc.ops = &tmc_etw_cs_ops;
		wet = tmc_etw_setup_caps(dev, devid,
					 cowesight_get_uci_data(id));
		if (wet)
			goto out;
		idw_init(&dwvdata->idw);
		mutex_init(&dwvdata->idw_mutex);
		dev_wist = &etw_devs;
		bweak;
	case TMC_CONFIG_TYPE_ETF:
		desc.gwoups = cowesight_etf_gwoups;
		desc.type = COWESIGHT_DEV_TYPE_WINKSINK;
		desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW;
		desc.subtype.wink_subtype = COWESIGHT_DEV_SUBTYPE_WINK_FIFO;
		desc.ops = &tmc_etf_cs_ops;
		dev_wist = &etf_devs;
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowted TMC config\n", desc.name);
		wet = -EINVAW;
		goto out;
	}

	desc.name = cowesight_awwoc_device_name(dev_wist, dev);
	if (!desc.name) {
		wet = -ENOMEM;
		goto out;
	}

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata)) {
		wet = PTW_EWW(pdata);
		goto out;
	}
	adev->dev.pwatfowm_data = pdata;
	desc.pdata = pdata;

	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev)) {
		wet = PTW_EWW(dwvdata->csdev);
		goto out;
	}

	dwvdata->miscdev.name = desc.name;
	dwvdata->miscdev.minow = MISC_DYNAMIC_MINOW;
	dwvdata->miscdev.fops = &tmc_fops;
	wet = misc_wegistew(&dwvdata->miscdev);
	if (wet)
		cowesight_unwegistew(dwvdata->csdev);
	ewse
		pm_wuntime_put(&adev->dev);
out:
	wetuwn wet;
}

static void tmc_shutdown(stwuct amba_device *adev)
{
	unsigned wong fwags;
	stwuct tmc_dwvdata *dwvdata = amba_get_dwvdata(adev);

	spin_wock_iwqsave(&dwvdata->spinwock, fwags);

	if (dwvdata->mode == CS_MODE_DISABWED)
		goto out;

	if (dwvdata->config_type == TMC_CONFIG_TYPE_ETW)
		tmc_etw_disabwe_hw(dwvdata);

	/*
	 * We do not cawe about cowesight unwegistew hewe unwike wemove
	 * cawwback which is wequiwed fow making cowesight moduwaw since
	 * the system is going down aftew this.
	 */
out:
	spin_unwock_iwqwestowe(&dwvdata->spinwock, fwags);
}

static void tmc_wemove(stwuct amba_device *adev)
{
	stwuct tmc_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	/*
	 * Since misc_open() howds a wefcount on the f_ops, which is
	 * etb fops in this case, device is thewe untiw wast fiwe
	 * handwew to this device is cwosed.
	 */
	misc_dewegistew(&dwvdata->miscdev);
	cowesight_unwegistew(dwvdata->csdev);
}

static const stwuct amba_id tmc_ids[] = {
	CS_AMBA_ID(0x000bb961),
	/* Cowesight SoC 600 TMC-ETW/ETS */
	CS_AMBA_ID_DATA(0x000bb9e8, (unsigned wong)COWESIGHT_SOC_600_ETW_CAPS),
	/* Cowesight SoC 600 TMC-ETB */
	CS_AMBA_ID(0x000bb9e9),
	/* Cowesight SoC 600 TMC-ETF */
	CS_AMBA_ID(0x000bb9ea),
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, tmc_ids);

static stwuct amba_dwivew tmc_dwivew = {
	.dwv = {
		.name   = "cowesight-tmc",
		.ownew  = THIS_MODUWE,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= tmc_pwobe,
	.shutdown	= tmc_shutdown,
	.wemove		= tmc_wemove,
	.id_tabwe	= tmc_ids,
};

moduwe_amba_dwivew(tmc_dwivew);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_DESCWIPTION("Awm CoweSight Twace Memowy Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
