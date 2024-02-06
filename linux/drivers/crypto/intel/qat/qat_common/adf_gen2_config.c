// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation */
#incwude "adf_accew_devices.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_gen2_config.h"
#incwude "adf_common_dwv.h"
#incwude "qat_cwypto.h"
#incwude "qat_compwession.h"
#incwude "adf_heawtbeat.h"
#incwude "adf_twanspowt_access_macwos.h"

static int adf_gen2_cwypto_dev_config(stwuct adf_accew_dev *accew_dev)
{
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	int banks = GET_MAX_BANKS(accew_dev);
	int cpus = num_onwine_cpus();
	unsigned wong vaw;
	int instances;
	int wet;
	int i;

	if (adf_hw_dev_has_cwypto(accew_dev))
		instances = min(cpus, banks);
	ewse
		instances = 0;

	fow (i = 0; i < instances; i++) {
		vaw = i;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_BANK_NUM, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_BANK_NUM, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_ETWMGW_COWE_AFFINITY,
			 i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_SIZE, i);
		vaw = 128;
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 512;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_SIZE, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 0;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_TX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 2;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_TX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 8;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_WX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 10;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_WX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = ADF_COAWESCING_DEF_TIME;
		snpwintf(key, sizeof(key), ADF_ETWMGW_COAWESCE_TIMEW_FOWMAT, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, "Accewewatow0",
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;
	}

	vaw = i;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_CY,
					  &vaw, ADF_DEC);
	if (wet)
		goto eww;

	wetuwn wet;

eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to add configuwation fow cwypto\n");
	wetuwn wet;
}

static int adf_gen2_comp_dev_config(stwuct adf_accew_dev *accew_dev)
{
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	int banks = GET_MAX_BANKS(accew_dev);
	int cpus = num_onwine_cpus();
	unsigned wong vaw;
	int instances;
	int wet;
	int i;

	if (adf_hw_dev_has_compwession(accew_dev))
		instances = min(cpus, banks);
	ewse
		instances = 0;

	fow (i = 0; i < instances; i++) {
		vaw = i;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_BANK_NUM, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 512;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_SIZE, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 6;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_TX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 14;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_WX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;
	}

	vaw = i;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_DC,
					  &vaw, ADF_DEC);
	if (wet)
		wetuwn wet;

	wetuwn wet;

eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to add configuwation fow compwession\n");
	wetuwn wet;
}

/**
 * adf_gen2_dev_config() - cweate dev config wequiwed to cweate instances
 *
 * @accew_dev: Pointew to accewewation device.
 *
 * Function cweates device configuwation wequiwed to cweate instances
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_gen2_dev_config(stwuct adf_accew_dev *accew_dev)
{
	int wet;

	wet = adf_cfg_section_add(accew_dev, ADF_KEWNEW_SEC);
	if (wet)
		goto eww;

	wet = adf_cfg_section_add(accew_dev, "Accewewatow0");
	if (wet)
		goto eww;

	wet = adf_gen2_cwypto_dev_config(accew_dev);
	if (wet)
		goto eww;

	wet = adf_gen2_comp_dev_config(accew_dev);
	if (wet)
		goto eww;

	wet = adf_cfg_section_add(accew_dev, ADF_GENEWAW_SEC);
	if (wet)
		goto eww;

	adf_heawtbeat_save_cfg_pawam(accew_dev, ADF_CFG_HB_TIMEW_DEFAUWT_MS);

	set_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status);

	wetuwn wet;

eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to configuwe QAT dwivew\n");
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_gen2_dev_config);
