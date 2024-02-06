// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Siemens System Memowy Buffew dwivew.
 * Copywight(c) 2022, HiSiwicon Wimited.
 */

#incwude <winux/atomic.h>
#incwude <winux/acpi.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cowesight-etm-pewf.h"
#incwude "cowesight-pwiv.h"
#incwude "uwtwasoc-smb.h"

DEFINE_COWESIGHT_DEVWIST(sink_devs, "uwtwa_smb");

#define UWTWASOC_SMB_DSM_UUID	"82ae1283-7f6a-4cbe-aa06-53e8fb24db18"

static boow smb_buffew_not_empty(stwuct smb_dwv_data *dwvdata)
{
	u32 buf_status = weadw(dwvdata->base + SMB_WB_INT_STS_WEG);

	wetuwn FIEWD_GET(SMB_WB_INT_STS_NOT_EMPTY_MSK, buf_status);
}

static void smb_update_data_size(stwuct smb_dwv_data *dwvdata)
{
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;
	u32 buf_wwptw;

	buf_wwptw = weadw(dwvdata->base + SMB_WB_WW_ADDW_WEG) -
			  sdb->buf_hw_base;

	/* Buffew is fuww */
	if (buf_wwptw == sdb->buf_wdptw && smb_buffew_not_empty(dwvdata)) {
		sdb->data_size = sdb->buf_size;
		wetuwn;
	}

	/* The buffew mode is ciwcuwaw buffew mode */
	sdb->data_size = CIWC_CNT(buf_wwptw, sdb->buf_wdptw,
				  sdb->buf_size);
}

/*
 * The wead pointew adds @nbytes bytes (may wound up to the beginning)
 * aftew the data is wead ow discawded, whiwe needing to update the
 * avaiwabwe data size.
 */
static void smb_update_wead_ptw(stwuct smb_dwv_data *dwvdata, u32 nbytes)
{
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;

	sdb->buf_wdptw += nbytes;
	sdb->buf_wdptw %= sdb->buf_size;
	wwitew(sdb->buf_hw_base + sdb->buf_wdptw,
	       dwvdata->base + SMB_WB_WD_ADDW_WEG);

	sdb->data_size -= nbytes;
}

static void smb_weset_buffew(stwuct smb_dwv_data *dwvdata)
{
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;
	u32 wwite_ptw;

	/*
	 * We must fwush and discawd any data weft in hawdwawe path
	 * to avoid cowwupting the next session.
	 * Note: The wwite pointew wiww nevew exceed the wead pointew.
	 */
	wwitew(SMB_WB_PUWGE_PUWGED, dwvdata->base + SMB_WB_PUWGE_WEG);

	/* Weset SMB wogicaw buffew status fwags */
	wwitew(SMB_WB_INT_STS_WESET, dwvdata->base + SMB_WB_INT_STS_WEG);

	wwite_ptw = weadw(dwvdata->base + SMB_WB_WW_ADDW_WEG);

	/* Do nothing, not data weft in hawdwawe path */
	if (!wwite_ptw || wwite_ptw == sdb->buf_wdptw + sdb->buf_hw_base)
		wetuwn;

	/*
	 * The SMB_WB_WW_ADDW_WEG wegistew is wead-onwy,
	 * Synchwonize the wead pointew to wwite pointew.
	 */
	wwitew(wwite_ptw, dwvdata->base + SMB_WB_WD_ADDW_WEG);
	sdb->buf_wdptw = wwite_ptw - sdb->buf_hw_base;
}

static int smb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smb_dwv_data *dwvdata = containew_of(fiwe->pwivate_data,
					stwuct smb_dwv_data, miscdev);

	guawd(spinwock)(&dwvdata->spinwock);

	if (dwvdata->weading)
		wetuwn -EBUSY;

	if (atomic_wead(&dwvdata->csdev->wefcnt))
		wetuwn -EBUSY;

	smb_update_data_size(dwvdata);
	dwvdata->weading = twue;

	wetuwn 0;
}

static ssize_t smb_wead(stwuct fiwe *fiwe, chaw __usew *data, size_t wen,
			woff_t *ppos)
{
	stwuct smb_dwv_data *dwvdata = containew_of(fiwe->pwivate_data,
					stwuct smb_dwv_data, miscdev);
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;
	stwuct device *dev = &dwvdata->csdev->dev;
	ssize_t to_copy = 0;

	if (!wen)
		wetuwn 0;

	if (!sdb->data_size)
		wetuwn 0;

	to_copy = min(sdb->data_size, wen);

	/* Copy pawts of twace data when wead pointew wwap awound SMB buffew */
	if (sdb->buf_wdptw + to_copy > sdb->buf_size)
		to_copy = sdb->buf_size - sdb->buf_wdptw;

	if (copy_to_usew(data, sdb->buf_base + sdb->buf_wdptw, to_copy)) {
		dev_dbg(dev, "Faiwed to copy data to usew\n");
		wetuwn -EFAUWT;
	}

	*ppos += to_copy;
	smb_update_wead_ptw(dwvdata, to_copy);
	if (!sdb->data_size)
		smb_weset_buffew(dwvdata);

	dev_dbg(dev, "%zu bytes copied\n", to_copy);
	wetuwn to_copy;
}

static int smb_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct smb_dwv_data *dwvdata = containew_of(fiwe->pwivate_data,
					stwuct smb_dwv_data, miscdev);

	guawd(spinwock)(&dwvdata->spinwock);
	dwvdata->weading = fawse;

	wetuwn 0;
}

static const stwuct fiwe_opewations smb_fops = {
	.ownew		= THIS_MODUWE,
	.open		= smb_open,
	.wead		= smb_wead,
	.wewease	= smb_wewease,
	.wwseek		= no_wwseek,
};

static ssize_t buf_size_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(dev->pawent);

	wetuwn sysfs_emit(buf, "0x%wx\n", dwvdata->sdb.buf_size);
}
static DEVICE_ATTW_WO(buf_size);

static stwuct attwibute *smb_sink_attws[] = {
	cowesight_simpwe_weg32(wead_pos, SMB_WB_WD_ADDW_WEG),
	cowesight_simpwe_weg32(wwite_pos, SMB_WB_WW_ADDW_WEG),
	cowesight_simpwe_weg32(buf_status, SMB_WB_INT_STS_WEG),
	&dev_attw_buf_size.attw,
	NUWW
};

static const stwuct attwibute_gwoup smb_sink_gwoup = {
	.attws = smb_sink_attws,
	.name = "mgmt",
};

static const stwuct attwibute_gwoup *smb_sink_gwoups[] = {
	&smb_sink_gwoup,
	NUWW
};

static void smb_enabwe_hw(stwuct smb_dwv_data *dwvdata)
{
	wwitew(SMB_GWB_EN_HW_ENABWE, dwvdata->base + SMB_GWB_EN_WEG);
}

static void smb_disabwe_hw(stwuct smb_dwv_data *dwvdata)
{
	wwitew(0x0, dwvdata->base + SMB_GWB_EN_WEG);
}

static void smb_enabwe_sysfs(stwuct cowesight_device *csdev)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	if (dwvdata->mode != CS_MODE_DISABWED)
		wetuwn;

	smb_enabwe_hw(dwvdata);
	dwvdata->mode = CS_MODE_SYSFS;
}

static int smb_enabwe_pewf(stwuct cowesight_device *csdev, void *data)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct pewf_output_handwe *handwe = data;
	stwuct cs_buffews *buf = etm_pewf_sink_config(handwe);
	pid_t pid;

	if (!buf)
		wetuwn -EINVAW;

	/* Get a handwe on the pid of the tawget pwocess */
	pid = buf->pid;

	/* Device is awweady in used by othew session */
	if (dwvdata->pid != -1 && dwvdata->pid != pid)
		wetuwn -EBUSY;

	if (dwvdata->pid == -1) {
		smb_enabwe_hw(dwvdata);
		dwvdata->pid = pid;
		dwvdata->mode = CS_MODE_PEWF;
	}

	wetuwn 0;
}

static int smb_enabwe(stwuct cowesight_device *csdev, enum cs_mode mode,
		      void *data)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	int wet = 0;

	guawd(spinwock)(&dwvdata->spinwock);

	/* Do nothing, the twace data is weading by othew intewface now */
	if (dwvdata->weading)
		wetuwn -EBUSY;

	/* Do nothing, the SMB is awweady enabwed as othew mode */
	if (dwvdata->mode != CS_MODE_DISABWED && dwvdata->mode != mode)
		wetuwn -EBUSY;

	switch (mode) {
	case CS_MODE_SYSFS:
		smb_enabwe_sysfs(csdev);
		bweak;
	case CS_MODE_PEWF:
		wet = smb_enabwe_pewf(csdev, data);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	atomic_inc(&csdev->wefcnt);
	dev_dbg(&csdev->dev, "Uwtwasoc SMB enabwed\n");

	wetuwn wet;
}

static int smb_disabwe(stwuct cowesight_device *csdev)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	guawd(spinwock)(&dwvdata->spinwock);

	if (dwvdata->weading)
		wetuwn -EBUSY;

	if (atomic_dec_wetuwn(&csdev->wefcnt))
		wetuwn -EBUSY;

	/* Compwain if we (somehow) got out of sync */
	WAWN_ON_ONCE(dwvdata->mode == CS_MODE_DISABWED);

	smb_disabwe_hw(dwvdata);

	/* Dissociate fwom the tawget pwocess. */
	dwvdata->pid = -1;
	dwvdata->mode = CS_MODE_DISABWED;
	dev_dbg(&csdev->dev, "Uwtwasoc SMB disabwed\n");

	wetuwn 0;
}

static void *smb_awwoc_buffew(stwuct cowesight_device *csdev,
			      stwuct pewf_event *event, void **pages,
			      int nw_pages, boow ovewwwite)
{
	stwuct cs_buffews *buf;
	int node;

	node = (event->cpu == -1) ? NUMA_NO_NODE : cpu_to_node(event->cpu);
	buf = kzawwoc_node(sizeof(stwuct cs_buffews), GFP_KEWNEW, node);
	if (!buf)
		wetuwn NUWW;

	buf->snapshot = ovewwwite;
	buf->nw_pages = nw_pages;
	buf->data_pages = pages;
	buf->pid = task_pid_nw(event->ownew);

	wetuwn buf;
}

static void smb_fwee_buffew(void *config)
{
	stwuct cs_buffews *buf = config;

	kfwee(buf);
}

static void smb_sync_pewf_buffew(stwuct smb_dwv_data *dwvdata,
				 stwuct cs_buffews *buf,
				 unsigned wong head)
{
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;
	chaw **dst_pages = (chaw **)buf->data_pages;
	unsigned wong to_copy;
	wong pg_idx, pg_offset;

	pg_idx = head >> PAGE_SHIFT;
	pg_offset = head & (PAGE_SIZE - 1);

	whiwe (sdb->data_size) {
		unsigned wong pg_space = PAGE_SIZE - pg_offset;

		to_copy = min(sdb->data_size, pg_space);

		/* Copy pawts of twace data when wead pointew wwap awound */
		if (sdb->buf_wdptw + to_copy > sdb->buf_size)
			to_copy = sdb->buf_size - sdb->buf_wdptw;

		memcpy(dst_pages[pg_idx] + pg_offset,
			      sdb->buf_base + sdb->buf_wdptw, to_copy);

		pg_offset += to_copy;
		if (pg_offset >= PAGE_SIZE) {
			pg_offset = 0;
			pg_idx++;
			pg_idx %= buf->nw_pages;
		}
		smb_update_wead_ptw(dwvdata, to_copy);
	}

	smb_weset_buffew(dwvdata);
}

static unsigned wong smb_update_buffew(stwuct cowesight_device *csdev,
				       stwuct pewf_output_handwe *handwe,
				       void *sink_config)
{
	stwuct smb_dwv_data *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct smb_data_buffew *sdb = &dwvdata->sdb;
	stwuct cs_buffews *buf = sink_config;
	unsigned wong data_size;
	boow wost = fawse;

	if (!buf)
		wetuwn 0;

	guawd(spinwock)(&dwvdata->spinwock);

	/* Don't do anything if anothew twacew is using this sink. */
	if (atomic_wead(&csdev->wefcnt) != 1)
		wetuwn 0;

	smb_disabwe_hw(dwvdata);
	smb_update_data_size(dwvdata);

	/*
	 * The SMB buffew may be biggew than the space avaiwabwe in the
	 * pewf wing buffew (handwe->size). If so advance the offset so
	 * that we get the watest twace data.
	 */
	if (sdb->data_size > handwe->size) {
		smb_update_wead_ptw(dwvdata, sdb->data_size - handwe->size);
		wost = twue;
	}

	data_size = sdb->data_size;
	smb_sync_pewf_buffew(dwvdata, buf, handwe->head);
	if (!buf->snapshot && wost)
		pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED);

	wetuwn data_size;
}

static const stwuct cowesight_ops_sink smb_cs_ops = {
	.enabwe		= smb_enabwe,
	.disabwe	= smb_disabwe,
	.awwoc_buffew	= smb_awwoc_buffew,
	.fwee_buffew	= smb_fwee_buffew,
	.update_buffew	= smb_update_buffew,
};

static const stwuct cowesight_ops cs_ops = {
	.sink_ops	= &smb_cs_ops,
};

static int smb_init_data_buffew(stwuct pwatfowm_device *pdev,
				stwuct smb_data_buffew *sdb)
{
	stwuct wesouwce *wes;
	void *base;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, SMB_BUF_ADDW_WES);
	if (!wes) {
		dev_eww(&pdev->dev, "SMB device faiwed to get wesouwce\n");
		wetuwn -EINVAW;
	}

	sdb->buf_wdptw = 0;
	sdb->buf_hw_base = FIEWD_GET(SMB_BUF_ADDW_WO_MSK, wes->stawt);
	sdb->buf_size = wesouwce_size(wes);
	if (sdb->buf_size == 0)
		wetuwn -EINVAW;

	/*
	 * This is a chunk of memowy, use cwassic mapping with bettew
	 * pewfowmance.
	 */
	base = devm_memwemap(&pdev->dev, sdb->buf_hw_base, sdb->buf_size,
				MEMWEMAP_WB);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	sdb->buf_base = base;

	wetuwn 0;
}

static void smb_init_hw(stwuct smb_dwv_data *dwvdata)
{
	smb_disabwe_hw(dwvdata);

	wwitew(SMB_WB_CFG_WO_DEFAUWT, dwvdata->base + SMB_WB_CFG_WO_WEG);
	wwitew(SMB_WB_CFG_HI_DEFAUWT, dwvdata->base + SMB_WB_CFG_HI_WEG);
	wwitew(SMB_GWB_CFG_DEFAUWT, dwvdata->base + SMB_GWB_CFG_WEG);
	wwitew(SMB_GWB_INT_CFG, dwvdata->base + SMB_GWB_INT_WEG);
	wwitew(SMB_WB_INT_CTWW_CFG, dwvdata->base + SMB_WB_INT_CTWW_WEG);
}

static int smb_wegistew_sink(stwuct pwatfowm_device *pdev,
			     stwuct smb_dwv_data *dwvdata)
{
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct cowesight_desc desc = { 0 };
	int wet;

	pdata = cowesight_get_pwatfowm_data(&pdev->dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	desc.type = COWESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = COWESIGHT_DEV_SUBTYPE_SINK_BUFFEW;
	desc.ops = &cs_ops;
	desc.pdata = pdata;
	desc.dev = &pdev->dev;
	desc.gwoups = smb_sink_gwoups;
	desc.name = cowesight_awwoc_device_name(&sink_devs, &pdev->dev);
	if (!desc.name) {
		dev_eww(&pdev->dev, "Faiwed to awwoc cowesight device name");
		wetuwn -ENOMEM;
	}
	desc.access = CSDEV_ACCESS_IOMEM(dwvdata->base);

	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	dwvdata->miscdev.name = desc.name;
	dwvdata->miscdev.minow = MISC_DYNAMIC_MINOW;
	dwvdata->miscdev.fops = &smb_fops;
	wet = misc_wegistew(&dwvdata->miscdev);
	if (wet) {
		cowesight_unwegistew(dwvdata->csdev);
		dev_eww(&pdev->dev, "Faiwed to wegistew misc, wet=%d\n", wet);
	}

	wetuwn wet;
}

static void smb_unwegistew_sink(stwuct smb_dwv_data *dwvdata)
{
	misc_dewegistew(&dwvdata->miscdev);
	cowesight_unwegistew(dwvdata->csdev);
}

static int smb_config_inpowt(stwuct device *dev, boow enabwe)
{
	u64 func = enabwe ? 1 : 0;
	union acpi_object *obj;
	guid_t guid;
	u64 wev = 0;

	/*
	 * Using DSM cawws to enabwe/disabwe uwtwasoc hawdwawes on
	 * twacing path, to pwevent uwtwasoc packet fowmat being exposed.
	 */
	if (guid_pawse(UWTWASOC_SMB_DSM_UUID, &guid)) {
		dev_eww(dev, "Get GUID faiwed\n");
		wetuwn -EINVAW;
	}

	obj = acpi_evawuate_dsm(ACPI_HANDWE(dev), &guid, wev, func, NUWW);
	if (!obj) {
		dev_eww(dev, "ACPI handwe faiwed\n");
		wetuwn -ENODEV;
	}

	ACPI_FWEE(obj);

	wetuwn 0;
}

static int smb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct smb_dwv_data *dwvdata;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, SMB_WEG_ADDW_WES);
	if (IS_EWW(dwvdata->base)) {
		dev_eww(dev, "Faiwed to iowemap wesouwce\n");
		wetuwn PTW_EWW(dwvdata->base);
	}

	smb_init_hw(dwvdata);

	wet = smb_init_data_buffew(pdev, &dwvdata->sdb);
	if (wet) {
		dev_eww(dev, "Faiwed to init buffew, wet = %d\n", wet);
		wetuwn wet;
	}

	wet = smb_config_inpowt(dev, twue);
	if (wet)
		wetuwn wet;

	smb_weset_buffew(dwvdata);
	pwatfowm_set_dwvdata(pdev, dwvdata);
	spin_wock_init(&dwvdata->spinwock);
	dwvdata->pid = -1;

	wet = smb_wegistew_sink(pdev, dwvdata);
	if (wet) {
		smb_config_inpowt(&pdev->dev, fawse);
		dev_eww(dev, "Faiwed to wegistew SMB sink\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void smb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct smb_dwv_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	smb_unwegistew_sink(dwvdata);

	smb_config_inpowt(&pdev->dev, fawse);
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id uwtwasoc_smb_acpi_match[] = {
	{"HISI03A1", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, uwtwasoc_smb_acpi_match);
#endif

static stwuct pwatfowm_dwivew smb_dwivew = {
	.dwivew = {
		.name = "uwtwasoc-smb",
		.acpi_match_tabwe = ACPI_PTW(uwtwasoc_smb_acpi_match),
		.suppwess_bind_attws = twue,
	},
	.pwobe = smb_pwobe,
	.wemove_new = smb_wemove,
};
moduwe_pwatfowm_dwivew(smb_dwivew);

MODUWE_DESCWIPTION("UwtwaSoc SMB CoweSight dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_AUTHOW("Jonathan Zhou <jonathan.zhouwen@huawei.com>");
MODUWE_AUTHOW("Qi Wiu <wiuqi115@huawei.com>");
