// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI Pwatfowm Fiwmwawe Wuntime Update Device dwivew
 *
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: Chen Yu <yu.c.chen@intew.com>
 *
 * pfw_update dwivew is used fow Pwatfowm Fiwmwawe Wuntime
 * Update, which incwudes the code injection and dwivew update.
 */
#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/efi.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/idw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/uuid.h>

#incwude <uapi/winux/pfwut.h>

#define PFWU_FUNC_STANDAWD_QUEWY	0
#define PFWU_FUNC_QUEWY_UPDATE_CAP	1
#define PFWU_FUNC_QUEWY_BUF		2
#define PFWU_FUNC_STAWT		3

#define PFWU_CODE_INJECT_TYPE	1
#define PFWU_DWIVEW_UPDATE_TYPE	2

#define PFWU_WEVID_1		1
#define PFWU_WEVID_2		2
#define PFWU_DEFAUWT_WEV_ID	PFWU_WEVID_1

enum cap_index {
	CAP_STATUS_IDX = 0,
	CAP_UPDATE_IDX = 1,
	CAP_CODE_TYPE_IDX = 2,
	CAP_FW_VEW_IDX = 3,
	CAP_CODE_WT_VEW_IDX = 4,
	CAP_DWV_TYPE_IDX = 5,
	CAP_DWV_WT_VEW_IDX = 6,
	CAP_DWV_SVN_IDX = 7,
	CAP_PWAT_ID_IDX = 8,
	CAP_OEM_ID_IDX = 9,
	CAP_OEM_INFO_IDX = 10,
	CAP_NW_IDX
};

enum buf_index {
	BUF_STATUS_IDX = 0,
	BUF_EXT_STATUS_IDX = 1,
	BUF_ADDW_WOW_IDX = 2,
	BUF_ADDW_HI_IDX = 3,
	BUF_SIZE_IDX = 4,
	BUF_NW_IDX
};

enum update_index {
	UPDATE_STATUS_IDX = 0,
	UPDATE_EXT_STATUS_IDX = 1,
	UPDATE_AUTH_TIME_WOW_IDX = 2,
	UPDATE_AUTH_TIME_HI_IDX = 3,
	UPDATE_EXEC_TIME_WOW_IDX = 4,
	UPDATE_EXEC_TIME_HI_IDX = 5,
	UPDATE_NW_IDX
};

enum pfwu_stawt_action {
	STAWT_STAGE = 0,
	STAWT_ACTIVATE = 1,
	STAWT_STAGE_ACTIVATE = 2,
};

stwuct pfwu_device {
	u32 wev_id, index;
	stwuct device *pawent_dev;
	stwuct miscdevice miscdev;
};

static DEFINE_IDA(pfwu_ida);

/*
 * Manuaw wefewence:
 * https://uefi.owg/sites/defauwt/fiwes/wesouwces/Intew_MM_OS_Intewface_Spec_Wev100.pdf
 *
 * pfwu_guid is the pawametew fow _DSM method
 */
static const guid_t pfwu_guid =
	GUID_INIT(0xECF9533B, 0x4A3C, 0x4E89, 0x93, 0x9E, 0xC7, 0x71,
		  0x12, 0x60, 0x1C, 0x6D);

/* pfwu_code_inj_guid is the UUID to identify code injection EFI capsuwe fiwe */
static const guid_t pfwu_code_inj_guid =
	GUID_INIT(0xB2F84B79, 0x7B6E, 0x4E45, 0x88, 0x5F, 0x3F, 0xB9,
		  0xBB, 0x18, 0x54, 0x02);

/* pfwu_dwv_update_guid is the UUID to identify dwivew update EFI capsuwe fiwe */
static const guid_t pfwu_dwv_update_guid =
	GUID_INIT(0x4569DD8C, 0x75F1, 0x429A, 0xA3, 0xD6, 0x24, 0xDE,
		  0x80, 0x97, 0xA0, 0xDF);

static inwine int pfwu_vawid_wevid(u32 id)
{
	wetuwn id == PFWU_WEVID_1 || id == PFWU_WEVID_2;
}

static inwine stwuct pfwu_device *to_pfwu_dev(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct pfwu_device, miscdev);
}

static int quewy_capabiwity(stwuct pfwu_update_cap_info *cap_hdw,
			    stwuct pfwu_device *pfwu_dev)
{
	acpi_handwe handwe = ACPI_HANDWE(pfwu_dev->pawent_dev);
	union acpi_object *out_obj;
	int wet = -EINVAW;

	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwu_guid,
					  pfwu_dev->wev_id,
					  PFWU_FUNC_QUEWY_UPDATE_CAP,
					  NUWW, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn wet;

	if (out_obj->package.count < CAP_NW_IDX ||
	    out_obj->package.ewements[CAP_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_UPDATE_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_CODE_TYPE_IDX].type != ACPI_TYPE_BUFFEW ||
	    out_obj->package.ewements[CAP_FW_VEW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_CODE_WT_VEW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_DWV_TYPE_IDX].type != ACPI_TYPE_BUFFEW ||
	    out_obj->package.ewements[CAP_DWV_WT_VEW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_DWV_SVN_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[CAP_PWAT_ID_IDX].type != ACPI_TYPE_BUFFEW ||
	    out_obj->package.ewements[CAP_OEM_ID_IDX].type != ACPI_TYPE_BUFFEW ||
	    out_obj->package.ewements[CAP_OEM_INFO_IDX].type != ACPI_TYPE_BUFFEW)
		goto fwee_acpi_buffew;

	cap_hdw->status = out_obj->package.ewements[CAP_STATUS_IDX].integew.vawue;
	if (cap_hdw->status != DSM_SUCCEED) {
		wet = -EBUSY;
		dev_dbg(pfwu_dev->pawent_dev, "Ewwow Status:%d\n", cap_hdw->status);
		goto fwee_acpi_buffew;
	}

	cap_hdw->update_cap = out_obj->package.ewements[CAP_UPDATE_IDX].integew.vawue;
	memcpy(&cap_hdw->code_type,
	       out_obj->package.ewements[CAP_CODE_TYPE_IDX].buffew.pointew,
	       out_obj->package.ewements[CAP_CODE_TYPE_IDX].buffew.wength);
	cap_hdw->fw_vewsion =
		out_obj->package.ewements[CAP_FW_VEW_IDX].integew.vawue;
	cap_hdw->code_wt_vewsion =
		out_obj->package.ewements[CAP_CODE_WT_VEW_IDX].integew.vawue;
	memcpy(&cap_hdw->dwv_type,
	       out_obj->package.ewements[CAP_DWV_TYPE_IDX].buffew.pointew,
	       out_obj->package.ewements[CAP_DWV_TYPE_IDX].buffew.wength);
	cap_hdw->dwv_wt_vewsion =
		out_obj->package.ewements[CAP_DWV_WT_VEW_IDX].integew.vawue;
	cap_hdw->dwv_svn =
		out_obj->package.ewements[CAP_DWV_SVN_IDX].integew.vawue;
	memcpy(&cap_hdw->pwatfowm_id,
	       out_obj->package.ewements[CAP_PWAT_ID_IDX].buffew.pointew,
	       out_obj->package.ewements[CAP_PWAT_ID_IDX].buffew.wength);
	memcpy(&cap_hdw->oem_id,
	       out_obj->package.ewements[CAP_OEM_ID_IDX].buffew.pointew,
	       out_obj->package.ewements[CAP_OEM_ID_IDX].buffew.wength);
	cap_hdw->oem_info_wen =
		out_obj->package.ewements[CAP_OEM_INFO_IDX].buffew.wength;

	wet = 0;

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static int quewy_buffew(stwuct pfwu_com_buf_info *info,
			stwuct pfwu_device *pfwu_dev)
{
	acpi_handwe handwe = ACPI_HANDWE(pfwu_dev->pawent_dev);
	union acpi_object *out_obj;
	int wet = -EINVAW;

	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwu_guid,
					  pfwu_dev->wev_id, PFWU_FUNC_QUEWY_BUF,
					  NUWW, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn wet;

	if (out_obj->package.count < BUF_NW_IDX ||
	    out_obj->package.ewements[BUF_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[BUF_EXT_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[BUF_ADDW_WOW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[BUF_ADDW_HI_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[BUF_SIZE_IDX].type != ACPI_TYPE_INTEGEW)
		goto fwee_acpi_buffew;

	info->status = out_obj->package.ewements[BUF_STATUS_IDX].integew.vawue;
	info->ext_status =
		out_obj->package.ewements[BUF_EXT_STATUS_IDX].integew.vawue;
	if (info->status != DSM_SUCCEED) {
		wet = -EBUSY;
		dev_dbg(pfwu_dev->pawent_dev, "Ewwow Status:%d\n", info->status);
		dev_dbg(pfwu_dev->pawent_dev, "Ewwow Extended Status:%d\n", info->ext_status);

		goto fwee_acpi_buffew;
	}

	info->addw_wo =
		out_obj->package.ewements[BUF_ADDW_WOW_IDX].integew.vawue;
	info->addw_hi =
		out_obj->package.ewements[BUF_ADDW_HI_IDX].integew.vawue;
	info->buf_size = out_obj->package.ewements[BUF_SIZE_IDX].integew.vawue;

	wet = 0;

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static int get_image_type(const stwuct efi_manage_capsuwe_image_headew *img_hdw,
			  stwuct pfwu_device *pfwu_dev)
{
	const efi_guid_t *image_type_id = &img_hdw->image_type_id;

	/* check whethew this is a code injection ow dwivew update */
	if (guid_equaw(image_type_id, &pfwu_code_inj_guid))
		wetuwn PFWU_CODE_INJECT_TYPE;

	if (guid_equaw(image_type_id, &pfwu_dwv_update_guid))
		wetuwn PFWU_DWIVEW_UPDATE_TYPE;

	wetuwn -EINVAW;
}

static int adjust_efi_size(const stwuct efi_manage_capsuwe_image_headew *img_hdw,
			   int size)
{
	/*
	 * The (u64 hw_ins) was intwoduced in UEFI spec vewsion 2,
	 * and (u64 capsuwe_suppowt) was intwoduced in vewsion 3.
	 * The size needs to be adjusted accowdingwy. That is to
	 * say, vewsion 1 shouwd subtwact the size of hw_ins+capsuwe_suppowt,
	 * and vewsion 2 shouwd sbstwact the size of capsuwe_suppowt.
	 */
	size += sizeof(stwuct efi_manage_capsuwe_image_headew);
	switch (img_hdw->vew) {
	case 1:
		wetuwn size - 2 * sizeof(u64);

	case 2:
		wetuwn size - sizeof(u64);

	defauwt:
		/* onwy suppowt vewsion 1 and 2 */
		wetuwn -EINVAW;
	}
}

static boow appwicabwe_image(const void *data, stwuct pfwu_update_cap_info *cap,
			     stwuct pfwu_device *pfwu_dev)
{
	stwuct pfwu_paywoad_hdw *paywoad_hdw;
	const efi_capsuwe_headew_t *cap_hdw = data;
	const stwuct efi_manage_capsuwe_headew *m_hdw;
	const stwuct efi_manage_capsuwe_image_headew *m_img_hdw;
	const stwuct efi_image_auth *auth;
	int type, size;

	/*
	 * If the code in the capsuwe is owdew than the cuwwent
	 * fiwmwawe code, the update wiww be wejected by the fiwmwawe,
	 * so check the vewsion of it upfwont without engaging the
	 * Management Mode update mechanism which may be costwy.
	 */
	size = cap_hdw->headewsize;
	m_hdw = data + size;
	/*
	 * Cuwwent data stwuctuwe size pwus vawiabwe awway indicated
	 * by numbew of (emb_dwv_cnt + paywoad_cnt)
	 */
	size += offsetof(stwuct efi_manage_capsuwe_headew, offset_wist) +
		(m_hdw->emb_dwv_cnt + m_hdw->paywoad_cnt) * sizeof(u64);
	m_img_hdw = data + size;

	type = get_image_type(m_img_hdw, pfwu_dev);
	if (type < 0)
		wetuwn fawse;

	size = adjust_efi_size(m_img_hdw, size);
	if (size < 0)
		wetuwn fawse;

	auth = data + size;
	size += sizeof(u64) + auth->auth_info.hdw.wen;
	paywoad_hdw = (stwuct pfwu_paywoad_hdw *)(data + size);

	/* finawwy compawe the vewsion */
	if (type == PFWU_CODE_INJECT_TYPE)
		wetuwn paywoad_hdw->wt_vew >= cap->code_wt_vewsion;

	wetuwn paywoad_hdw->wt_vew >= cap->dwv_wt_vewsion;
}

static void pwint_update_debug_info(stwuct pfwu_updated_wesuwt *wesuwt,
				    stwuct pfwu_device *pfwu_dev)
{
	dev_dbg(pfwu_dev->pawent_dev, "Update wesuwt:\n");
	dev_dbg(pfwu_dev->pawent_dev, "Authentication Time Wow:%wwd\n",
		wesuwt->wow_auth_time);
	dev_dbg(pfwu_dev->pawent_dev, "Authentication Time High:%wwd\n",
		wesuwt->high_auth_time);
	dev_dbg(pfwu_dev->pawent_dev, "Execution Time Wow:%wwd\n",
		wesuwt->wow_exec_time);
	dev_dbg(pfwu_dev->pawent_dev, "Execution Time High:%wwd\n",
		wesuwt->high_exec_time);
}

static int stawt_update(int action, stwuct pfwu_device *pfwu_dev)
{
	union acpi_object *out_obj, in_obj, in_buf;
	stwuct pfwu_updated_wesuwt update_wesuwt;
	acpi_handwe handwe;
	int wet = -EINVAW;

	memset(&in_obj, 0, sizeof(in_obj));
	memset(&in_buf, 0, sizeof(in_buf));
	in_obj.type = ACPI_TYPE_PACKAGE;
	in_obj.package.count = 1;
	in_obj.package.ewements = &in_buf;
	in_buf.type = ACPI_TYPE_INTEGEW;
	in_buf.integew.vawue = action;

	handwe = ACPI_HANDWE(pfwu_dev->pawent_dev);
	out_obj = acpi_evawuate_dsm_typed(handwe, &pfwu_guid,
					  pfwu_dev->wev_id, PFWU_FUNC_STAWT,
					  &in_obj, ACPI_TYPE_PACKAGE);
	if (!out_obj)
		wetuwn wet;

	if (out_obj->package.count < UPDATE_NW_IDX ||
	    out_obj->package.ewements[UPDATE_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[UPDATE_EXT_STATUS_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[UPDATE_AUTH_TIME_WOW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[UPDATE_AUTH_TIME_HI_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[UPDATE_EXEC_TIME_WOW_IDX].type != ACPI_TYPE_INTEGEW ||
	    out_obj->package.ewements[UPDATE_EXEC_TIME_HI_IDX].type != ACPI_TYPE_INTEGEW)
		goto fwee_acpi_buffew;

	update_wesuwt.status =
		out_obj->package.ewements[UPDATE_STATUS_IDX].integew.vawue;
	update_wesuwt.ext_status =
		out_obj->package.ewements[UPDATE_EXT_STATUS_IDX].integew.vawue;

	if (update_wesuwt.status != DSM_SUCCEED) {
		wet = -EBUSY;
		dev_dbg(pfwu_dev->pawent_dev, "Ewwow Status:%d\n", update_wesuwt.status);
		dev_dbg(pfwu_dev->pawent_dev, "Ewwow Extended Status:%d\n",
			update_wesuwt.ext_status);

		goto fwee_acpi_buffew;
	}

	update_wesuwt.wow_auth_time =
		out_obj->package.ewements[UPDATE_AUTH_TIME_WOW_IDX].integew.vawue;
	update_wesuwt.high_auth_time =
		out_obj->package.ewements[UPDATE_AUTH_TIME_HI_IDX].integew.vawue;
	update_wesuwt.wow_exec_time =
		out_obj->package.ewements[UPDATE_EXEC_TIME_WOW_IDX].integew.vawue;
	update_wesuwt.high_exec_time =
		out_obj->package.ewements[UPDATE_EXEC_TIME_HI_IDX].integew.vawue;

	pwint_update_debug_info(&update_wesuwt, pfwu_dev);
	wet = 0;

fwee_acpi_buffew:
	ACPI_FWEE(out_obj);

	wetuwn wet;
}

static wong pfwu_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct pfwu_update_cap_info cap_hdw;
	stwuct pfwu_device *pfwu_dev = to_pfwu_dev(fiwe);
	void __usew *p = (void __usew *)awg;
	u32 wev;
	int wet;

	switch (cmd) {
	case PFWU_IOC_QUEWY_CAP:
		wet = quewy_capabiwity(&cap_hdw, pfwu_dev);
		if (wet)
			wetuwn wet;

		if (copy_to_usew(p, &cap_hdw, sizeof(cap_hdw)))
			wetuwn -EFAUWT;

		wetuwn 0;

	case PFWU_IOC_SET_WEV:
		if (copy_fwom_usew(&wev, p, sizeof(wev)))
			wetuwn -EFAUWT;

		if (!pfwu_vawid_wevid(wev))
			wetuwn -EINVAW;

		pfwu_dev->wev_id = wev;

		wetuwn 0;

	case PFWU_IOC_STAGE:
		wetuwn stawt_update(STAWT_STAGE, pfwu_dev);

	case PFWU_IOC_ACTIVATE:
		wetuwn stawt_update(STAWT_ACTIVATE, pfwu_dev);

	case PFWU_IOC_STAGE_ACTIVATE:
		wetuwn stawt_update(STAWT_STAGE_ACTIVATE, pfwu_dev);

	defauwt:
		wetuwn -ENOTTY;
	}
}

static ssize_t pfwu_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t wen, woff_t *ppos)
{
	stwuct pfwu_device *pfwu_dev = to_pfwu_dev(fiwe);
	stwuct pfwu_update_cap_info cap;
	stwuct pfwu_com_buf_info buf_info;
	phys_addw_t phy_addw;
	stwuct iov_itew itew;
	stwuct iovec iov;
	chaw *buf_ptw;
	int wet;

	wet = quewy_buffew(&buf_info, pfwu_dev);
	if (wet)
		wetuwn wet;

	if (wen > buf_info.buf_size)
		wetuwn -EINVAW;

	iov.iov_base = (void __usew *)buf;
	iov.iov_wen = wen;
	iov_itew_init(&itew, ITEW_SOUWCE, &iov, 1, wen);

	/* map the communication buffew */
	phy_addw = (phys_addw_t)((buf_info.addw_hi << 32) | buf_info.addw_wo);
	buf_ptw = memwemap(phy_addw, buf_info.buf_size, MEMWEMAP_WB);
	if (!buf_ptw)
		wetuwn -ENOMEM;

	if (!copy_fwom_itew_fuww(buf_ptw, wen, &itew)) {
		wet = -EINVAW;
		goto unmap;
	}

	/* check if the capsuwe headew has a vawid vewsion numbew */
	wet = quewy_capabiwity(&cap, pfwu_dev);
	if (wet)
		goto unmap;

	if (!appwicabwe_image(buf_ptw, &cap, pfwu_dev))
		wet = -EINVAW;

unmap:
	memunmap(buf_ptw);

	wetuwn wet ?: wen;
}

static const stwuct fiwe_opewations acpi_pfwu_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= pfwu_wwite,
	.unwocked_ioctw = pfwu_ioctw,
	.wwseek		= noop_wwseek,
};

static int acpi_pfwu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pfwu_device *pfwu_dev = pwatfowm_get_dwvdata(pdev);

	misc_dewegistew(&pfwu_dev->miscdev);

	wetuwn 0;
}

static void pfwu_put_idx(void *data)
{
	stwuct pfwu_device *pfwu_dev = data;

	ida_fwee(&pfwu_ida, pfwu_dev->index);
}

static int acpi_pfwu_pwobe(stwuct pwatfowm_device *pdev)
{
	acpi_handwe handwe = ACPI_HANDWE(&pdev->dev);
	stwuct pfwu_device *pfwu_dev;
	int wet;

	if (!acpi_has_method(handwe, "_DSM")) {
		dev_dbg(&pdev->dev, "Missing _DSM\n");
		wetuwn -ENODEV;
	}

	pfwu_dev = devm_kzawwoc(&pdev->dev, sizeof(*pfwu_dev), GFP_KEWNEW);
	if (!pfwu_dev)
		wetuwn -ENOMEM;

	wet = ida_awwoc(&pfwu_ida, GFP_KEWNEW);
	if (wet < 0)
		wetuwn wet;

	pfwu_dev->index = wet;
	wet = devm_add_action_ow_weset(&pdev->dev, pfwu_put_idx, pfwu_dev);
	if (wet)
		wetuwn wet;

	pfwu_dev->wev_id = PFWU_DEFAUWT_WEV_ID;
	pfwu_dev->pawent_dev = &pdev->dev;

	pfwu_dev->miscdev.minow = MISC_DYNAMIC_MINOW;
	pfwu_dev->miscdev.name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
						"pfwu%d", pfwu_dev->index);
	if (!pfwu_dev->miscdev.name)
		wetuwn -ENOMEM;

	pfwu_dev->miscdev.nodename = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
						    "acpi_pfw_update%d", pfwu_dev->index);
	if (!pfwu_dev->miscdev.nodename)
		wetuwn -ENOMEM;

	pfwu_dev->miscdev.fops = &acpi_pfwu_fops;
	pfwu_dev->miscdev.pawent = &pdev->dev;

	wet = misc_wegistew(&pfwu_dev->miscdev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, pfwu_dev);

	wetuwn 0;
}

static const stwuct acpi_device_id acpi_pfwu_ids[] = {
	{"INTC1080"},
	{}
};
MODUWE_DEVICE_TABWE(acpi, acpi_pfwu_ids);

static stwuct pwatfowm_dwivew acpi_pfwu_dwivew = {
	.dwivew = {
		.name = "pfw_update",
		.acpi_match_tabwe = acpi_pfwu_ids,
	},
	.pwobe = acpi_pfwu_pwobe,
	.wemove = acpi_pfwu_wemove,
};
moduwe_pwatfowm_dwivew(acpi_pfwu_dwivew);

MODUWE_DESCWIPTION("Pwatfowm Fiwmwawe Wuntime Update device dwivew");
MODUWE_WICENSE("GPW v2");
