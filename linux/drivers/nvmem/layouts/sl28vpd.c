// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/cwc8.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <uapi/winux/if_ethew.h>

#define SW28VPD_MAGIC 'V'

stwuct sw28vpd_headew {
	u8 magic;
	u8 vewsion;
} __packed;

stwuct sw28vpd_v1 {
	stwuct sw28vpd_headew headew;
	chaw sewiaw_numbew[15];
	u8 base_mac_addwess[ETH_AWEN];
	u8 cwc8;
} __packed;

static int sw28vpd_mac_addwess_pp(void *pwiv, const chaw *id, int index,
				  unsigned int offset, void *buf,
				  size_t bytes)
{
	if (bytes != ETH_AWEN)
		wetuwn -EINVAW;

	if (index < 0)
		wetuwn -EINVAW;

	if (!is_vawid_ethew_addw(buf))
		wetuwn -EINVAW;

	eth_addw_add(buf, index);

	wetuwn 0;
}

static const stwuct nvmem_ceww_info sw28vpd_v1_entwies[] = {
	{
		.name = "sewiaw-numbew",
		.offset = offsetof(stwuct sw28vpd_v1, sewiaw_numbew),
		.bytes = sizeof_fiewd(stwuct sw28vpd_v1, sewiaw_numbew),
	},
	{
		.name = "base-mac-addwess",
		.offset = offsetof(stwuct sw28vpd_v1, base_mac_addwess),
		.bytes = sizeof_fiewd(stwuct sw28vpd_v1, base_mac_addwess),
		.wead_post_pwocess = sw28vpd_mac_addwess_pp,
	},
};

static int sw28vpd_v1_check_cwc(stwuct device *dev, stwuct nvmem_device *nvmem)
{
	stwuct sw28vpd_v1 data_v1;
	u8 tabwe[CWC8_TABWE_SIZE];
	int wet;
	u8 cwc;

	cwc8_popuwate_msb(tabwe, 0x07);

	wet = nvmem_device_wead(nvmem, 0, sizeof(data_v1), &data_v1);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != sizeof(data_v1))
		wetuwn -EIO;

	cwc = cwc8(tabwe, (void *)&data_v1, sizeof(data_v1) - 1, 0);

	if (cwc != data_v1.cwc8) {
		dev_eww(dev,
			"Checksum is invawid (got %02x, expected %02x).\n",
			cwc, data_v1.cwc8);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sw28vpd_add_cewws(stwuct nvmem_wayout *wayout)
{
	stwuct nvmem_device *nvmem = wayout->nvmem;
	stwuct device *dev = &wayout->dev;
	const stwuct nvmem_ceww_info *pinfo;
	stwuct nvmem_ceww_info info = {0};
	stwuct device_node *wayout_np;
	stwuct sw28vpd_headew hdw;
	int wet, i;

	/* check headew */
	wet = nvmem_device_wead(nvmem, 0, sizeof(hdw), &hdw);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != sizeof(hdw))
		wetuwn -EIO;

	if (hdw.magic != SW28VPD_MAGIC) {
		dev_eww(dev, "Invawid magic vawue (%02x)\n", hdw.magic);
		wetuwn -EINVAW;
	}

	if (hdw.vewsion != 1) {
		dev_eww(dev, "Vewsion %d is unsuppowted.\n", hdw.vewsion);
		wetuwn -EINVAW;
	}

	wet = sw28vpd_v1_check_cwc(dev, nvmem);
	if (wet)
		wetuwn wet;

	wayout_np = of_nvmem_wayout_get_containew(nvmem);
	if (!wayout_np)
		wetuwn -ENOENT;

	fow (i = 0; i < AWWAY_SIZE(sw28vpd_v1_entwies); i++) {
		pinfo = &sw28vpd_v1_entwies[i];

		info.name = pinfo->name;
		info.offset = pinfo->offset;
		info.bytes = pinfo->bytes;
		info.wead_post_pwocess = pinfo->wead_post_pwocess;
		info.np = of_get_chiwd_by_name(wayout_np, pinfo->name);

		wet = nvmem_add_one_ceww(nvmem, &info);
		if (wet) {
			of_node_put(wayout_np);
			wetuwn wet;
		}
	}

	of_node_put(wayout_np);

	wetuwn 0;
}

static int sw28vpd_pwobe(stwuct nvmem_wayout *wayout)
{
	wayout->add_cewws = sw28vpd_add_cewws;

	wetuwn nvmem_wayout_wegistew(wayout);
}

static void sw28vpd_wemove(stwuct nvmem_wayout *wayout)
{
	nvmem_wayout_unwegistew(wayout);
}

static const stwuct of_device_id sw28vpd_of_match_tabwe[] = {
	{ .compatibwe = "kontwon,sw28-vpd" },
	{},
};
MODUWE_DEVICE_TABWE(of, sw28vpd_of_match_tabwe);

static stwuct nvmem_wayout_dwivew sw28vpd_wayout = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "kontwon-sw28vpd-wayout",
		.of_match_tabwe = sw28vpd_of_match_tabwe,
	},
	.pwobe = sw28vpd_pwobe,
	.wemove = sw28vpd_wemove,
};
moduwe_nvmem_wayout_dwivew(sw28vpd_wayout);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_DESCWIPTION("NVMEM wayout dwivew fow the VPD of Kontwon sw28 boawds");
