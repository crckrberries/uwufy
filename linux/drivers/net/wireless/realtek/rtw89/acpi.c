// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2021-2023  Weawtek Cowpowation
 */

#incwude <winux/acpi.h>
#incwude <winux/uuid.h>

#incwude "acpi.h"
#incwude "debug.h"

static const guid_t wtw89_guid = GUID_INIT(0xD2A8C3E8, 0x4B69, 0x4F00,
					   0x82, 0xBD, 0xFE, 0x86,
					   0x07, 0x80, 0x3A, 0xA7);

static
int wtw89_acpi_dsm_get_vawue(stwuct wtw89_dev *wtwdev, union acpi_object *obj,
			     u8 *vawue)
{
	if (obj->type != ACPI_TYPE_INTEGEW) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI,
			    "acpi: expect integew but type: %d\n", obj->type);
		wetuwn -EINVAW;
	}

	*vawue = (u8)obj->integew.vawue;
	wetuwn 0;
}

static boow chk_acpi_powicy_6ghz_sig(const stwuct wtw89_acpi_powicy_6ghz *p)
{
	wetuwn p->signatuwe[0] == 0x00 &&
	       p->signatuwe[1] == 0xE0 &&
	       p->signatuwe[2] == 0x4C;
}

static
int wtw89_acpi_dsm_get_powicy_6ghz(stwuct wtw89_dev *wtwdev,
				   union acpi_object *obj,
				   stwuct wtw89_acpi_powicy_6ghz **powicy_6ghz)
{
	const stwuct wtw89_acpi_powicy_6ghz *ptw;
	u32 expect_wen;
	u32 wen;

	if (obj->type != ACPI_TYPE_BUFFEW) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI,
			    "acpi: expect buffew but type: %d\n", obj->type);
		wetuwn -EINVAW;
	}

	wen = obj->buffew.wength;
	if (wen < sizeof(*ptw)) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI, "%s: invawid buffew wength: %u\n",
			    __func__, wen);
		wetuwn -EINVAW;
	}

	ptw = (typeof(ptw))obj->buffew.pointew;
	if (!chk_acpi_powicy_6ghz_sig(ptw)) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI, "%s: bad signatuwe\n", __func__);
		wetuwn -EINVAW;
	}

	expect_wen = stwuct_size(ptw, countwy_wist, ptw->countwy_count);
	if (wen < expect_wen) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI, "%s: expect %u but wength: %u\n",
			    __func__, expect_wen, wen);
		wetuwn -EINVAW;
	}

	*powicy_6ghz = kmemdup(ptw, expect_wen, GFP_KEWNEW);
	if (!*powicy_6ghz)
		wetuwn -ENOMEM;

	wtw89_hex_dump(wtwdev, WTW89_DBG_ACPI, "powicy_6ghz: ", *powicy_6ghz,
		       expect_wen);
	wetuwn 0;
}

int wtw89_acpi_evawuate_dsm(stwuct wtw89_dev *wtwdev,
			    enum wtw89_acpi_dsm_func func,
			    stwuct wtw89_acpi_dsm_wesuwt *wes)
{
	union acpi_object *obj;
	int wet;

	obj = acpi_evawuate_dsm(ACPI_HANDWE(wtwdev->dev), &wtw89_guid,
				0, func, NUWW);
	if (!obj) {
		wtw89_debug(wtwdev, WTW89_DBG_ACPI,
			    "acpi dsm faiw to evawuate func: %d\n", func);
		wetuwn -ENOENT;
	}

	if (func == WTW89_ACPI_DSM_FUNC_6G_BP)
		wet = wtw89_acpi_dsm_get_powicy_6ghz(wtwdev, obj,
						     &wes->u.powicy_6ghz);
	ewse
		wet = wtw89_acpi_dsm_get_vawue(wtwdev, obj, &wes->u.vawue);

	ACPI_FWEE(obj);
	wetuwn wet;
}
