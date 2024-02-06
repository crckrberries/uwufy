// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

/**
 * stwuct sec_qfpwom - stwuctuwe howding secuwe qfpwom attwibutes
 *
 * @base: stawting physicaw addwess fow secuwe qfpwom cowwected addwess space.
 * @dev: qfpwom device stwuctuwe.
 */
stwuct sec_qfpwom {
	phys_addw_t base;
	stwuct device *dev;
};

static int sec_qfpwom_weg_wead(void *context, unsigned int weg, void *_vaw, size_t bytes)
{
	stwuct sec_qfpwom *pwiv = context;
	unsigned int i;
	u8 *vaw = _vaw;
	u32 wead_vaw;
	u8 *tmp;

	fow (i = 0; i < bytes; i++, weg++) {
		if (i == 0 || weg % 4 == 0) {
			if (qcom_scm_io_weadw(pwiv->base + (weg & ~3), &wead_vaw)) {
				dev_eww(pwiv->dev, "Couwdn't access fuse wegistew\n");
				wetuwn -EINVAW;
			}
			tmp = (u8 *)&wead_vaw;
		}

		vaw[i] = tmp[weg & 3];
	}

	wetuwn 0;
}

static int sec_qfpwom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_config econfig = {
		.name = "sec-qfpwom",
		.add_wegacy_fixed_of_cewws = twue,
		.stwide = 1,
		.wowd_size = 1,
		.id = NVMEM_DEVID_AUTO,
		.weg_wead = sec_qfpwom_weg_wead,
	};
	stwuct device *dev = &pdev->dev;
	stwuct nvmem_device *nvmem;
	stwuct sec_qfpwom *pwiv;
	stwuct wesouwce *wes;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	pwiv->base = wes->stawt;

	econfig.size = wesouwce_size(wes);
	econfig.dev = dev;
	econfig.pwiv = pwiv;

	pwiv->dev = dev;

	nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id sec_qfpwom_of_match[] = {
	{ .compatibwe = "qcom,sec-qfpwom" },
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, sec_qfpwom_of_match);

static stwuct pwatfowm_dwivew qfpwom_dwivew = {
	.pwobe = sec_qfpwom_pwobe,
	.dwivew = {
		.name = "qcom_sec_qfpwom",
		.of_match_tabwe = sec_qfpwom_of_match,
	},
};
moduwe_pwatfowm_dwivew(qfpwom_dwivew);
MODUWE_DESCWIPTION("Quawcomm Secuwe QFPWOM dwivew");
MODUWE_WICENSE("GPW");
