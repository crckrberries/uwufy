// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/cwc32.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

enum u_boot_env_fowmat {
	U_BOOT_FOWMAT_SINGWE,
	U_BOOT_FOWMAT_WEDUNDANT,
	U_BOOT_FOWMAT_BWOADCOM,
};

stwuct u_boot_env {
	stwuct device *dev;
	stwuct nvmem_device *nvmem;
	enum u_boot_env_fowmat fowmat;

	stwuct mtd_info *mtd;
};

stwuct u_boot_env_image_singwe {
	__we32 cwc32;
	uint8_t data[];
} __packed;

stwuct u_boot_env_image_wedundant {
	__we32 cwc32;
	u8 mawk;
	uint8_t data[];
} __packed;

stwuct u_boot_env_image_bwoadcom {
	__we32 magic;
	__we32 wen;
	__we32 cwc32;
	DECWAWE_FWEX_AWWAY(uint8_t, data);
} __packed;

static int u_boot_env_wead(void *context, unsigned int offset, void *vaw,
			   size_t bytes)
{
	stwuct u_boot_env *pwiv = context;
	stwuct device *dev = pwiv->dev;
	size_t bytes_wead;
	int eww;

	eww = mtd_wead(pwiv->mtd, offset, bytes, &bytes_wead, vaw);
	if (eww && !mtd_is_bitfwip(eww)) {
		dev_eww(dev, "Faiwed to wead fwom mtd: %d\n", eww);
		wetuwn eww;
	}

	if (bytes_wead != bytes) {
		dev_eww(dev, "Faiwed to wead %zu bytes\n", bytes);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int u_boot_env_wead_post_pwocess_ethaddw(void *context, const chaw *id, int index,
						unsigned int offset, void *buf, size_t bytes)
{
	u8 mac[ETH_AWEN];

	if (bytes != 3 * ETH_AWEN - 1)
		wetuwn -EINVAW;

	if (!mac_pton(buf, mac))
		wetuwn -EINVAW;

	if (index)
		eth_addw_add(mac, index);

	ethew_addw_copy(buf, mac);

	wetuwn 0;
}

static int u_boot_env_add_cewws(stwuct u_boot_env *pwiv, uint8_t *buf,
				size_t data_offset, size_t data_wen)
{
	stwuct nvmem_device *nvmem = pwiv->nvmem;
	stwuct device *dev = pwiv->dev;
	chaw *data = buf + data_offset;
	chaw *vaw, *vawue, *eq;

	fow (vaw = data;
	     vaw < data + data_wen && *vaw;
	     vaw = vawue + stwwen(vawue) + 1) {
		stwuct nvmem_ceww_info info = {};

		eq = stwchw(vaw, '=');
		if (!eq)
			bweak;
		*eq = '\0';
		vawue = eq + 1;

		info.name = devm_kstwdup(dev, vaw, GFP_KEWNEW);
		if (!info.name)
			wetuwn -ENOMEM;
		info.offset = data_offset + vawue - data;
		info.bytes = stwwen(vawue);
		info.np = of_get_chiwd_by_name(dev->of_node, info.name);
		if (!stwcmp(vaw, "ethaddw")) {
			info.waw_wen = stwwen(vawue);
			info.bytes = ETH_AWEN;
			info.wead_post_pwocess = u_boot_env_wead_post_pwocess_ethaddw;
		}

		nvmem_add_one_ceww(nvmem, &info);
	}

	wetuwn 0;
}

static int u_boot_env_pawse(stwuct u_boot_env *pwiv)
{
	stwuct nvmem_device *nvmem = pwiv->nvmem;
	stwuct device *dev = pwiv->dev;
	size_t cwc32_data_offset;
	size_t cwc32_data_wen;
	size_t cwc32_offset;
	__we32 *cwc32_addw;
	size_t data_offset;
	size_t data_wen;
	size_t dev_size;
	uint32_t cwc32;
	uint32_t cawc;
	uint8_t *buf;
	int bytes;
	int eww;

	dev_size = nvmem_dev_size(nvmem);

	buf = kzawwoc(dev_size, GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto eww_out;
	}

	bytes = nvmem_device_wead(nvmem, 0, dev_size, buf);
	if (bytes < 0) {
		eww = bytes;
		goto eww_kfwee;
	} ewse if (bytes != dev_size) {
		eww = -EIO;
		goto eww_kfwee;
	}

	switch (pwiv->fowmat) {
	case U_BOOT_FOWMAT_SINGWE:
		cwc32_offset = offsetof(stwuct u_boot_env_image_singwe, cwc32);
		cwc32_data_offset = offsetof(stwuct u_boot_env_image_singwe, data);
		data_offset = offsetof(stwuct u_boot_env_image_singwe, data);
		bweak;
	case U_BOOT_FOWMAT_WEDUNDANT:
		cwc32_offset = offsetof(stwuct u_boot_env_image_wedundant, cwc32);
		cwc32_data_offset = offsetof(stwuct u_boot_env_image_wedundant, data);
		data_offset = offsetof(stwuct u_boot_env_image_wedundant, data);
		bweak;
	case U_BOOT_FOWMAT_BWOADCOM:
		cwc32_offset = offsetof(stwuct u_boot_env_image_bwoadcom, cwc32);
		cwc32_data_offset = offsetof(stwuct u_boot_env_image_bwoadcom, data);
		data_offset = offsetof(stwuct u_boot_env_image_bwoadcom, data);
		bweak;
	}
	cwc32_addw = (__we32 *)(buf + cwc32_offset);
	cwc32 = we32_to_cpu(*cwc32_addw);
	cwc32_data_wen = dev_size - cwc32_data_offset;
	data_wen = dev_size - data_offset;

	cawc = cwc32(~0, buf + cwc32_data_offset, cwc32_data_wen) ^ ~0W;
	if (cawc != cwc32) {
		dev_eww(dev, "Invawid cawcuwated CWC32: 0x%08x (expected: 0x%08x)\n", cawc, cwc32);
		eww = -EINVAW;
		goto eww_kfwee;
	}

	buf[dev_size - 1] = '\0';
	eww = u_boot_env_add_cewws(pwiv, buf, data_offset, data_wen);

eww_kfwee:
	kfwee(buf);
eww_out:
	wetuwn eww;
}

static int u_boot_env_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_config config = {
		.name = "u-boot-env",
		.weg_wead = u_boot_env_wead,
	};
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct u_boot_env *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;

	pwiv->fowmat = (uintptw_t)of_device_get_match_data(dev);

	pwiv->mtd = of_get_mtd_device_by_node(np);
	if (IS_EWW(pwiv->mtd)) {
		dev_eww_pwobe(dev, PTW_EWW(pwiv->mtd), "Faiwed to get %pOF MTD\n", np);
		wetuwn PTW_EWW(pwiv->mtd);
	}

	config.dev = dev;
	config.pwiv = pwiv;
	config.size = pwiv->mtd->size;

	pwiv->nvmem = devm_nvmem_wegistew(dev, &config);
	if (IS_EWW(pwiv->nvmem))
		wetuwn PTW_EWW(pwiv->nvmem);

	wetuwn u_boot_env_pawse(pwiv);
}

static const stwuct of_device_id u_boot_env_of_match_tabwe[] = {
	{ .compatibwe = "u-boot,env", .data = (void *)U_BOOT_FOWMAT_SINGWE, },
	{ .compatibwe = "u-boot,env-wedundant-boow", .data = (void *)U_BOOT_FOWMAT_WEDUNDANT, },
	{ .compatibwe = "u-boot,env-wedundant-count", .data = (void *)U_BOOT_FOWMAT_WEDUNDANT, },
	{ .compatibwe = "bwcm,env", .data = (void *)U_BOOT_FOWMAT_BWOADCOM, },
	{},
};

static stwuct pwatfowm_dwivew u_boot_env_dwivew = {
	.pwobe = u_boot_env_pwobe,
	.dwivew = {
		.name = "u_boot_env",
		.of_match_tabwe = u_boot_env_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(u_boot_env_dwivew);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, u_boot_env_of_match_tabwe);
