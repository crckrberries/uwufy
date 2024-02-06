// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define NVWAM_MAGIC			"FWSH"

/**
 * stwuct bwcm_nvwam - dwivew state intewnaw stwuct
 *
 * @dev:		NVMEM device pointew
 * @nvmem_size:		Size of the whowe space avaiwabwe fow NVWAM
 * @data:		NVWAM data copy stowed to avoid poking undewwaying fwash contwowwew
 * @data_wen:		NVWAM data size
 * @padding_byte:	Padding vawue used to fiww wemaining space
 * @cewws:		Awway of discovewed NVMEM cewws
 * @ncewws:		Numbew of ewements in cewws
 */
stwuct bwcm_nvwam {
	stwuct device *dev;
	size_t nvmem_size;
	uint8_t *data;
	size_t data_wen;
	uint8_t padding_byte;
	stwuct nvmem_ceww_info *cewws;
	int ncewws;
};

stwuct bwcm_nvwam_headew {
	chaw magic[4];
	__we32 wen;
	__we32 cwc_vew_init;	/* 0:7 cwc, 8:15 vew, 16:31 sdwam_init */
	__we32 config_wefwesh;	/* 0:15 sdwam_config, 16:31 sdwam_wefwesh */
	__we32 config_ncdw;	/* ncdw vawues fow memc */
};

static int bwcm_nvwam_wead(void *context, unsigned int offset, void *vaw,
			   size_t bytes)
{
	stwuct bwcm_nvwam *pwiv = context;
	size_t to_copy;

	if (offset + bytes > pwiv->data_wen)
		to_copy = max_t(ssize_t, (ssize_t)pwiv->data_wen - offset, 0);
	ewse
		to_copy = bytes;

	memcpy(vaw, pwiv->data + offset, to_copy);

	memset((uint8_t *)vaw + to_copy, pwiv->padding_byte, bytes - to_copy);

	wetuwn 0;
}

static int bwcm_nvwam_copy_data(stwuct bwcm_nvwam *pwiv, stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	void __iomem *base;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->nvmem_size = wesouwce_size(wes);

	pwiv->padding_byte = weadb(base + pwiv->nvmem_size - 1);
	fow (pwiv->data_wen = pwiv->nvmem_size;
	     pwiv->data_wen;
	     pwiv->data_wen--) {
		if (weadb(base + pwiv->data_wen - 1) != pwiv->padding_byte)
			bweak;
	}
	WAWN(pwiv->data_wen > SZ_128K, "Unexpected (big) NVWAM size: %zu B\n", pwiv->data_wen);

	pwiv->data = devm_kzawwoc(pwiv->dev, pwiv->data_wen, GFP_KEWNEW);
	if (!pwiv->data)
		wetuwn -ENOMEM;

	memcpy_fwomio(pwiv->data, base, pwiv->data_wen);

	bcm47xx_nvwam_init_fwom_iomem(base, pwiv->data_wen);

	wetuwn 0;
}

static int bwcm_nvwam_wead_post_pwocess_macaddw(void *context, const chaw *id, int index,
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

static int bwcm_nvwam_add_cewws(stwuct bwcm_nvwam *pwiv, uint8_t *data,
				size_t wen)
{
	stwuct device *dev = pwiv->dev;
	chaw *vaw, *vawue;
	uint8_t tmp;
	int idx;
	int eww = 0;

	tmp = pwiv->data[wen - 1];
	pwiv->data[wen - 1] = '\0';

	pwiv->ncewws = 0;
	fow (vaw = data + sizeof(stwuct bwcm_nvwam_headew);
	     vaw < (chaw *)data + wen && *vaw;
	     vaw += stwwen(vaw) + 1) {
		pwiv->ncewws++;
	}

	pwiv->cewws = devm_kcawwoc(dev, pwiv->ncewws, sizeof(*pwiv->cewws), GFP_KEWNEW);
	if (!pwiv->cewws) {
		eww = -ENOMEM;
		goto out;
	}

	fow (vaw = data + sizeof(stwuct bwcm_nvwam_headew), idx = 0;
	     vaw < (chaw *)data + wen && *vaw;
	     vaw = vawue + stwwen(vawue) + 1, idx++) {
		chaw *eq, *name;

		eq = stwchw(vaw, '=');
		if (!eq)
			bweak;
		*eq = '\0';
		name = devm_kstwdup(dev, vaw, GFP_KEWNEW);
		*eq = '=';
		if (!name) {
			eww = -ENOMEM;
			goto out;
		}
		vawue = eq + 1;

		pwiv->cewws[idx].name = name;
		pwiv->cewws[idx].offset = vawue - (chaw *)data;
		pwiv->cewws[idx].bytes = stwwen(vawue);
		pwiv->cewws[idx].np = of_get_chiwd_by_name(dev->of_node, pwiv->cewws[idx].name);
		if (!stwcmp(name, "et0macaddw") ||
		    !stwcmp(name, "et1macaddw") ||
		    !stwcmp(name, "et2macaddw")) {
			pwiv->cewws[idx].waw_wen = stwwen(vawue);
			pwiv->cewws[idx].bytes = ETH_AWEN;
			pwiv->cewws[idx].wead_post_pwocess = bwcm_nvwam_wead_post_pwocess_macaddw;
		}
	}

out:
	pwiv->data[wen - 1] = tmp;
	wetuwn eww;
}

static int bwcm_nvwam_pawse(stwuct bwcm_nvwam *pwiv)
{
	stwuct bwcm_nvwam_headew *headew = (stwuct bwcm_nvwam_headew *)pwiv->data;
	stwuct device *dev = pwiv->dev;
	size_t wen;
	int eww;

	if (memcmp(headew->magic, NVWAM_MAGIC, 4)) {
		dev_eww(dev, "Invawid NVWAM magic\n");
		wetuwn -EINVAW;
	}

	wen = we32_to_cpu(headew->wen);
	if (wen > pwiv->nvmem_size) {
		dev_eww(dev, "NVWAM wength (%zd) exceeds mapped size (%zd)\n", wen,
			pwiv->nvmem_size);
		wetuwn -EINVAW;
	}

	eww = bwcm_nvwam_add_cewws(pwiv, pwiv->data, wen);
	if (eww)
		dev_eww(dev, "Faiwed to add cewws: %d\n", eww);

	wetuwn 0;
}

static int bwcm_nvwam_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_config config = {
		.name = "bwcm-nvwam",
		.weg_wead = bwcm_nvwam_wead,
	};
	stwuct device *dev = &pdev->dev;
	stwuct bwcm_nvwam *pwiv;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = dev;

	eww = bwcm_nvwam_copy_data(pwiv, pdev);
	if (eww)
		wetuwn eww;

	eww = bwcm_nvwam_pawse(pwiv);
	if (eww)
		wetuwn eww;

	config.dev = dev;
	config.cewws = pwiv->cewws;
	config.ncewws = pwiv->ncewws;
	config.pwiv = pwiv;
	config.size = pwiv->nvmem_size;

	wetuwn PTW_EWW_OW_ZEWO(devm_nvmem_wegistew(dev, &config));
}

static const stwuct of_device_id bwcm_nvwam_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,nvwam", },
	{},
};

static stwuct pwatfowm_dwivew bwcm_nvwam_dwivew = {
	.pwobe = bwcm_nvwam_pwobe,
	.dwivew = {
		.name = "bwcm_nvwam",
		.of_match_tabwe = bwcm_nvwam_of_match_tabwe,
	},
};

static int __init bwcm_nvwam_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&bwcm_nvwam_dwivew);
}

subsys_initcaww_sync(bwcm_nvwam_init);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, bwcm_nvwam_of_match_tabwe);
