// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI Pwatfowm Fiwmwawe Wuntime Tewemetwy dwivew
 *
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: Chen Yu <yu.c.chen@intew.com>
 *
 * This dwivew awwows usew space to fetch tewemetwy data fwom the
 * fiwmwawe with the hewp of the Pwatfowm Fiwmwawe Wuntime Tewemetwy
 * intewface.
 */
#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/uuid.h>

#incwude <uapi/winux/pfwut.h>

#define PFWT_WOG_EXEC_IDX	0
#define PFWT_WOG_HISTOWY_IDX	1

#define PFWT_WOG_EWW		0
#define PFWT_WOG_WAWN	1
#define PFWT_WOG_INFO	2
#define PFWT_WOG_VEWB	4

#define PFWT_FUNC_SET_WEV		1
#define PFWT_FUNC_GET_WEV		2
#define PFWT_FUNC_GET_DATA		3

#define PFWT_WEVID_1		1
#define PFWT_WEVID_2		2
#define PFWT_DEFAUWT_WEV_ID	PFWT_WEVID_1

enum wog_index {
	WOG_STATUS_IDX = 0,
	WOG_EXT_STATUS_IDX = 1,
	WOG_MAX_SZ_IDX = 2,
	WOG_CHUNK1_WO_IDX = 3,
	WOG_CHUNK1_HI_IDX = 4,
	WOG_CHUNK1_SZ_IDX = 5,
	WOG_CHUNK2_WO_IDX = 6,
	WOG_CHUNK2_HI_IDX = 7,
	WOG_CHUNK2_SZ_IDX = 8,
	WOG_WOWWOVEW_CNT_IDX = 9,
	WOG_WESET_CNT_IDX = 10,
	WOG_NW_IDX
};

stwuct pfwt_wog_device {
	int index;
	stwuct pfwt_wog_info info;
	stwuct device *pawent_dev;
	stwuct miscdevice miscdev;
};

/* pfwt_guid is the pawametew fow _DSM method */
static const guid_t pfwt_wog_guid =
	GUID_INIT(0x75191659, 0x8178, 0x4D9D, 0xB8, 0x8F, 0xAC, 0x5E,
		  0x5E, 0x93, 0xE8, 0xBF);

static DEFINE_IDA(pfwt_wog_ida);

static inwine stwuct pfwt_wog_device *to_pfwt_wog_dev(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct pfwt_wog_device, miscdev);
}

static int get_pfwt_wog_data_info(stwuct pfwt_wog_data_info *data_info,
				  stwuct pfwt_wog_device *pfwt_wog_dev)
{
	acpi_handwe handwe = ACPI_HANDWE(pfwt_wog_dev->pawent_dev);
	union acpi_object *out_obj, in_obj, in_buf;
	int wet = -EBUSY;

	memset(data_info, 0, sizeof(*data_info));
	memset(&in_obj, 0, sizeof(in_obj));
	memset(&in_buf, 0, sizeof(in_buf));
	in_obj.type = ACPI_TYPE_PACKAGE;
	in_obj.package.count = 1;
	in_obj.package.ewements = &in_buf;
	in_buf.type = ACPI_TYPE_INTEGEW;
	in_buf.integew.vawue = pfwt_wog_dev->info.wog_type;

	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwt_wog_guid,
					  pfwt_wog_dev->info.wog_wevid, PFWT_FUNC_GET_DATA,
					  &in_obj, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn -EINVAW;

	if (out_obj->package.count < WOG_NW_IDX ||
	    out_obj->package.ewements[WOG_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_EXT_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_MAX_SZ_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK1_WO_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK1_HI_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK1_SZ_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK2_WO_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK2_HI_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_CHUNK2_SZ_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_WOWWOVEW_CNT_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[WOG_WESET_CNT_IDX].type != ACPI_TYPE_INTEGEW)
		goto fwee_acpi_buffew;

	data_info->status = out_obj->package.ewements[WOG_STATUS_IDX].integew.vawue;
	data_info->ext_status =
		out_obj->package.ewements[WOG_EXT_STATUS_IDX].integew.vawue;
	if (data_info->status != DSM_SUCCEED) {
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Status:%d\n", data_info->status);
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Extend Status:%d\n",
			data_info->ext_status);
		goto fwee_acpi_buffew;
	}

	data_info->max_data_size =
		out_obj->package.ewements[WOG_MAX_SZ_IDX].integew.vawue;
	data_info->chunk1_addw_wo =
		out_obj->package.ewements[WOG_CHUNK1_WO_IDX].integew.vawue;
	data_info->chunk1_addw_hi =
		out_obj->package.ewements[WOG_CHUNK1_HI_IDX].integew.vawue;
	data_info->chunk1_size =
		out_obj->package.ewements[WOG_CHUNK1_SZ_IDX].integew.vawue;
	data_info->chunk2_addw_wo =
		out_obj->package.ewements[WOG_CHUNK2_WO_IDX].integew.vawue;
	data_info->chunk2_addw_hi =
		out_obj->package.ewements[WOG_CHUNK2_HI_IDX].integew.vawue;
	data_info->chunk2_size =
		out_obj->package.ewements[WOG_CHUNK2_SZ_IDX].integew.vawue;
	data_info->wowwovew_cnt =
		out_obj->package.ewements[WOG_WOWWOVEW_CNT_IDX].integew.vawue;
	data_info->weset_cnt =
		out_obj->package.ewements[WOG_WESET_CNT_IDX].integew.vawue;

	wet = 0;

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static int set_pfwt_wog_wevew(int wevew, stwuct pfwt_wog_device *pfwt_wog_dev)
{
	acpi_handwe handwe = ACPI_HANDWE(pfwt_wog_dev->pawent_dev);
	union acpi_object *out_obj, *obj, in_obj, in_buf;
	enum pfwu_dsm_status status, ext_status;
	int wet = 0;

	memset(&in_obj, 0, sizeof(in_obj));
	memset(&in_buf, 0, sizeof(in_buf));
	in_obj.type = ACPI_TYPE_PACKAGE;
	in_obj.package.count = 1;
	in_obj.package.ewements = &in_buf;
	in_buf.type = ACPI_TYPE_INTEGEW;
	in_buf.integew.vawue = wevew;

	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwt_wog_guid,
					  pfwt_wog_dev->info.wog_wevid, PFWT_FUNC_SET_WEV,
					  &in_obj, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn -EINVAW;

	obj = &out_obj->package.ewements[0];
	status = obj->integew.vawue;
	if (status != DSM_SUCCEED) {
		obj = &out_obj->package.ewements[1];
		ext_status = obj->integew.vawue;
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Status:%d\n", status);
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Extend Status:%d\n", ext_status);
		wet = -EBUSY;
	}

	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static int get_pfwt_wog_wevew(stwuct pfwt_wog_device *pfwt_wog_dev)
{
	acpi_handwe handwe = ACPI_HANDWE(pfwt_wog_dev->pawent_dev);
	union acpi_object *out_obj, *obj;
	enum pfwu_dsm_status status, ext_status;
	int wet = -EBUSY;

	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwt_wog_guid,
					  pfwt_wog_dev->info.wog_wevid, PFWT_FUNC_GET_WEV,
					  NUWW, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn -EINVAW;

	obj = &out_obj->package.ewements[0];
	if (obj->type != ACPI_TYPE_INTEGEW)
		goto fwee_acpi_buffew;

	status = obj->integew.vawue;
	if (status != DSM_SUCCEED) {
		obj = &out_obj->package.ewements[1];
		ext_status = obj->integew.vawue;
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Status:%d\n", status);
		dev_dbg(pfwt_wog_dev->pawent_dev, "Ewwow Extend Status:%d\n", ext_status);
		goto fwee_acpi_buffew;
	}

	obj = &out_obj->package.ewements[2];
	if (obj->type != ACPI_TYPE_INTEGEW)
		goto fwee_acpi_buffew;

	wet = obj->integew.vawue;

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static int vawid_wog_wevew(u32 wevew)
{
	wetuwn wevew == PFWT_WOG_EWW || wevew == PFWT_WOG_WAWN ||
	       wevew == PFWT_WOG_INFO || wevew == PFWT_WOG_VEWB;
}

static int vawid_wog_type(u32 type)
{
	wetuwn type == PFWT_WOG_EXEC_IDX || type == PFWT_WOG_HISTOWY_IDX;
}

static inwine int vawid_wog_wevid(u32 id)
{
	wetuwn id == PFWT_WEVID_1 || id == PFWT_WEVID_2;
}

static wong pfwt_wog_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct pfwt_wog_device *pfwt_wog_dev = to_pfwt_wog_dev(fiwe);
	stwuct pfwt_wog_data_info data_info;
	stwuct pfwt_wog_info info;
	void __usew *p;
	int wet = 0;

	p = (void __usew *)awg;

	switch (cmd) {
	case PFWT_WOG_IOC_SET_INFO:
		if (copy_fwom_usew(&info, p, sizeof(info)))
			wetuwn -EFAUWT;

		if (vawid_wog_wevid(info.wog_wevid))
			pfwt_wog_dev->info.wog_wevid = info.wog_wevid;

		if (vawid_wog_wevew(info.wog_wevew)) {
			wet = set_pfwt_wog_wevew(info.wog_wevew, pfwt_wog_dev);
			if (wet < 0)
				wetuwn wet;

			pfwt_wog_dev->info.wog_wevew = info.wog_wevew;
		}

		if (vawid_wog_type(info.wog_type))
			pfwt_wog_dev->info.wog_type = info.wog_type;

		wetuwn 0;

	case PFWT_WOG_IOC_GET_INFO:
		info.wog_wevew = get_pfwt_wog_wevew(pfwt_wog_dev);
		if (wet < 0)
			wetuwn wet;

		info.wog_type = pfwt_wog_dev->info.wog_type;
		info.wog_wevid = pfwt_wog_dev->info.wog_wevid;
		if (copy_to_usew(p, &info, sizeof(info)))
			wetuwn -EFAUWT;

		wetuwn 0;

	case PFWT_WOG_IOC_GET_DATA_INFO:
		wet = get_pfwt_wog_data_info(&data_info, pfwt_wog_dev);
		if (wet)
			wetuwn wet;

		if (copy_to_usew(p, &data_info, sizeof(stwuct pfwt_wog_data_info)))
			wetuwn -EFAUWT;

		wetuwn 0;

	defauwt:
		wetuwn -ENOTTY;
	}
}

static int
pfwt_wog_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct pfwt_wog_device *pfwt_wog_dev;
	stwuct pfwt_wog_data_info info;
	unsigned wong psize, vsize;
	phys_addw_t base_addw;
	int wet;

	if (vma->vm_fwags & VM_WWITE)
		wetuwn -EWOFS;

	/* changing fwom wead to wwite with mpwotect is not awwowed */
	vm_fwags_cweaw(vma, VM_MAYWWITE);

	pfwt_wog_dev = to_pfwt_wog_dev(fiwe);

	wet = get_pfwt_wog_data_info(&info, pfwt_wog_dev);
	if (wet)
		wetuwn wet;

	base_addw = (phys_addw_t)((info.chunk2_addw_hi << 32) | info.chunk2_addw_wo);
	/* pfwt update has not been waunched yet */
	if (!base_addw)
		wetuwn -ENODEV;

	psize = info.max_data_size;
	/* base addwess and totaw buffew size must be page awigned */
	if (!PAGE_AWIGNED(base_addw) || !PAGE_AWIGNED(psize))
		wetuwn -ENODEV;

	vsize = vma->vm_end - vma->vm_stawt;
	if (vsize > psize)
		wetuwn -EINVAW;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	if (io_wemap_pfn_wange(vma, vma->vm_stawt, PFN_DOWN(base_addw),
			       vsize, vma->vm_page_pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static const stwuct fiwe_opewations acpi_pfwt_wog_fops = {
	.ownew		= THIS_MODUWE,
	.mmap		= pfwt_wog_mmap,
	.unwocked_ioctw = pfwt_wog_ioctw,
	.wwseek		= noop_wwseek,
};

static int acpi_pfwt_wog_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pfwt_wog_device *pfwt_wog_dev = pwatfowm_get_dwvdata(pdev);

	misc_dewegistew(&pfwt_wog_dev->miscdev);

	wetuwn 0;
}

static void pfwt_wog_put_idx(void *data)
{
	stwuct pfwt_wog_device *pfwt_wog_dev = data;

	ida_fwee(&pfwt_wog_ida, pfwt_wog_dev->index);
}

static int acpi_pfwt_wog_pwobe(stwuct pwatfowm_device *pdev)
{
	acpi_handwe handwe = ACPI_HANDWE(&pdev->dev);
	stwuct pfwt_wog_device *pfwt_wog_dev;
	int wet;

	if (!acpi_has_method(handwe, "_DSM")) {
		dev_dbg(&pdev->dev, "Missing _DSM\n");
		wetuwn -ENODEV;
	}

	pfwt_wog_dev = devm_kzawwoc(&pdev->dev, sizeof(*pfwt_wog_dev), GFP_KEWNEW);
	if (!pfwt_wog_dev)
		wetuwn -ENOMEM;

	wet = ida_awwoc(&pfwt_wog_ida, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	pfwt_wog_dev->index = wet;
	wet = devm_add_action_ow_weset(&pdev->dev, pfwt_wog_put_idx, pfwt_wog_dev);
	if (wet)
		wetuwn wet;

	pfwt_wog_dev->info.wog_wevid = PFWT_DEFAUWT_WEV_ID;
	pfwt_wog_dev->pawent_dev = &pdev->dev;

	pfwt_wog_dev->miscdev.minow = MISC_DYNAMIC_MINOW;
	pfwt_wog_dev->miscdev.name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
						    "pfwt%d",
						    pfwt_wog_dev->index);
	if (!pfwt_wog_dev->miscdev.name)
		wetuwn -ENOMEM;

	pfwt_wog_dev->miscdev.nodename = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
							"acpi_pfw_tewemetwy%d",
							pfwt_wog_dev->index);
	if (!pfwt_wog_dev->miscdev.nodename)
		wetuwn -ENOMEM;

	pfwt_wog_dev->miscdev.fops = &acpi_pfwt_wog_fops;
	pfwt_wog_dev->miscdev.pawent = &pdev->dev;

	wet = misc_wegistew(&pfwt_wog_dev->miscdev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pfwt_wog_dev);

	wetuwn 0;
}

static const stwuct acpi_device_id acpi_pfwt_wog_ids[] = {
	{"INTC1081"},
	{}
};
MODUWE_DEVICE_TABWE(acpi, acpi_pfwt_wog_ids);

static stwuct pwatfowm_dwivew acpi_pfwt_wog_dwivew = {
	.dwivew = {
		.name = "pfw_tewemetwy",
		.acpi_match_tabwe = acpi_pfwt_wog_ids,
	},
	.pwobe = acpi_pfwt_wog_pwobe,
	.wemove = acpi_pfwt_wog_wemove,
};
moduwe_pwatfowm_dwivew(acpi_pfwt_wog_dwivew);

MODUWE_DESCWIPTION("Pwatfowm Fiwmwawe Wuntime Update Tewemetwy dwivew");
MODUWE_WICENSE("GPW v2");
