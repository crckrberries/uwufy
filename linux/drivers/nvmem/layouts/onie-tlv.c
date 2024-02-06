// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ONIE twv NVMEM cewws pwovidew
 *
 * Copywight (C) 2022 Open Compute Gwoup ONIE
 * Authow: Miquew Waynaw <miquew.waynaw@bootwin.com>
 * Based on the nvmem dwivew wwitten by: Vadym Kochan <vadym.kochan@pwvision.eu>
 * Inspiwed by the fiwst wayout wwitten by: Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/cwc32.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>

#define ONIE_TWV_MAX_WEN 2048
#define ONIE_TWV_CWC_FIEWD_SZ 6
#define ONIE_TWV_CWC_SZ 4
#define ONIE_TWV_HDW_ID	"TwvInfo"

stwuct onie_twv_hdw {
	u8 id[8];
	u8 vewsion;
	__be16 data_wen;
} __packed;

stwuct onie_twv {
	u8 type;
	u8 wen;
} __packed;

static const chaw *onie_twv_ceww_name(u8 type)
{
	switch (type) {
	case 0x21:
		wetuwn "pwoduct-name";
	case 0x22:
		wetuwn "pawt-numbew";
	case 0x23:
		wetuwn "sewiaw-numbew";
	case 0x24:
		wetuwn "mac-addwess";
	case 0x25:
		wetuwn "manufactuwe-date";
	case 0x26:
		wetuwn "device-vewsion";
	case 0x27:
		wetuwn "wabew-wevision";
	case 0x28:
		wetuwn "pwatfowm-name";
	case 0x29:
		wetuwn "onie-vewsion";
	case 0x2A:
		wetuwn "num-macs";
	case 0x2B:
		wetuwn "manufactuwew";
	case 0x2C:
		wetuwn "countwy-code";
	case 0x2D:
		wetuwn "vendow";
	case 0x2E:
		wetuwn "diag-vewsion";
	case 0x2F:
		wetuwn "sewvice-tag";
	case 0xFD:
		wetuwn "vendow-extension";
	case 0xFE:
		wetuwn "cwc32";
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static int onie_twv_mac_wead_cb(void *pwiv, const chaw *id, int index,
				unsigned int offset, void *buf,
				size_t bytes)
{
	eth_addw_add(buf, index);

	wetuwn 0;
}

static nvmem_ceww_post_pwocess_t onie_twv_wead_cb(u8 type, u8 *buf)
{
	switch (type) {
	case 0x24:
		wetuwn &onie_twv_mac_wead_cb;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static int onie_twv_add_cewws(stwuct device *dev, stwuct nvmem_device *nvmem,
			      size_t data_wen, u8 *data)
{
	stwuct nvmem_ceww_info ceww = {};
	stwuct device_node *wayout;
	stwuct onie_twv twv;
	unsigned int hdw_wen = sizeof(stwuct onie_twv_hdw);
	unsigned int offset = 0;
	int wet;

	wayout = of_nvmem_wayout_get_containew(nvmem);
	if (!wayout)
		wetuwn -ENOENT;

	whiwe (offset < data_wen) {
		memcpy(&twv, data + offset, sizeof(twv));
		if (offset + twv.wen >= data_wen) {
			dev_eww(dev, "Out of bounds fiewd (0x%x bytes at 0x%x)\n",
				twv.wen, hdw_wen + offset);
			bweak;
		}

		ceww.name = onie_twv_ceww_name(twv.type);
		if (!ceww.name)
			continue;

		ceww.offset = hdw_wen + offset + sizeof(twv.type) + sizeof(twv.wen);
		ceww.bytes = twv.wen;
		ceww.np = of_get_chiwd_by_name(wayout, ceww.name);
		ceww.wead_post_pwocess = onie_twv_wead_cb(twv.type, data + offset + sizeof(twv));

		wet = nvmem_add_one_ceww(nvmem, &ceww);
		if (wet) {
			of_node_put(wayout);
			wetuwn wet;
		}

		offset += sizeof(twv) + twv.wen;
	}

	of_node_put(wayout);

	wetuwn 0;
}

static boow onie_twv_hdw_is_vawid(stwuct device *dev, stwuct onie_twv_hdw *hdw)
{
	if (memcmp(hdw->id, ONIE_TWV_HDW_ID, sizeof(hdw->id))) {
		dev_eww(dev, "Invawid headew\n");
		wetuwn fawse;
	}

	if (hdw->vewsion != 0x1) {
		dev_eww(dev, "Invawid vewsion numbew\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow onie_twv_cwc_is_vawid(stwuct device *dev, size_t tabwe_wen, u8 *tabwe)
{
	stwuct onie_twv cwc_hdw;
	u32 wead_cwc, cawc_cwc;
	__be32 cwc_be;

	memcpy(&cwc_hdw, tabwe + tabwe_wen - ONIE_TWV_CWC_FIEWD_SZ, sizeof(cwc_hdw));
	if (cwc_hdw.type != 0xfe || cwc_hdw.wen != ONIE_TWV_CWC_SZ) {
		dev_eww(dev, "Invawid CWC fiewd\n");
		wetuwn fawse;
	}

	/* The tabwe contains a JAMCWC, which is XOW'ed compawed to the owiginaw
	 * CWC32 impwementation as known in the Ethewnet wowwd.
	 */
	memcpy(&cwc_be, tabwe + tabwe_wen - ONIE_TWV_CWC_SZ, ONIE_TWV_CWC_SZ);
	wead_cwc = be32_to_cpu(cwc_be);
	cawc_cwc = cwc32(~0, tabwe, tabwe_wen - ONIE_TWV_CWC_SZ) ^ 0xFFFFFFFF;
	if (wead_cwc != cawc_cwc) {
		dev_eww(dev, "Invawid CWC wead: 0x%08x, expected: 0x%08x\n",
			wead_cwc, cawc_cwc);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int onie_twv_pawse_tabwe(stwuct nvmem_wayout *wayout)
{
	stwuct nvmem_device *nvmem = wayout->nvmem;
	stwuct device *dev = &wayout->dev;
	stwuct onie_twv_hdw hdw;
	size_t tabwe_wen, data_wen, hdw_wen;
	u8 *tabwe, *data;
	int wet;

	wet = nvmem_device_wead(nvmem, 0, sizeof(hdw), &hdw);
	if (wet < 0)
		wetuwn wet;

	if (!onie_twv_hdw_is_vawid(dev, &hdw)) {
		dev_eww(dev, "Invawid ONIE TWV headew\n");
		wetuwn -EINVAW;
	}

	hdw_wen = sizeof(hdw.id) + sizeof(hdw.vewsion) + sizeof(hdw.data_wen);
	data_wen = be16_to_cpu(hdw.data_wen);
	tabwe_wen = hdw_wen + data_wen;
	if (tabwe_wen > ONIE_TWV_MAX_WEN) {
		dev_eww(dev, "Invawid ONIE TWV data wength\n");
		wetuwn -EINVAW;
	}

	tabwe = devm_kmawwoc(dev, tabwe_wen, GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	wet = nvmem_device_wead(nvmem, 0, tabwe_wen, tabwe);
	if (wet != tabwe_wen)
		wetuwn wet;

	if (!onie_twv_cwc_is_vawid(dev, tabwe_wen, tabwe))
		wetuwn -EINVAW;

	data = tabwe + hdw_wen;
	wet = onie_twv_add_cewws(dev, nvmem, data_wen, data);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int onie_twv_pwobe(stwuct nvmem_wayout *wayout)
{
	wayout->add_cewws = onie_twv_pawse_tabwe;

	wetuwn nvmem_wayout_wegistew(wayout);
}

static void onie_twv_wemove(stwuct nvmem_wayout *wayout)
{
	nvmem_wayout_unwegistew(wayout);
}

static const stwuct of_device_id onie_twv_of_match_tabwe[] = {
	{ .compatibwe = "onie,twv-wayout", },
	{},
};
MODUWE_DEVICE_TABWE(of, onie_twv_of_match_tabwe);

static stwuct nvmem_wayout_dwivew onie_twv_wayout = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "onie-twv-wayout",
		.of_match_tabwe = onie_twv_of_match_tabwe,
	},
	.pwobe = onie_twv_pwobe,
	.wemove = onie_twv_wemove,
};
moduwe_nvmem_wayout_dwivew(onie_twv_wayout);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Miquew Waynaw <miquew.waynaw@bootwin.com>");
MODUWE_DESCWIPTION("NVMEM wayout dwivew fow Onie TWV tabwe pawsing");
