// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */
#incwude "adf_accew_devices.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_sewvices.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_common_dwv.h"
#incwude "adf_gen4_config.h"
#incwude "adf_heawtbeat.h"
#incwude "adf_twanspowt_access_macwos.h"
#incwude "qat_compwession.h"
#incwude "qat_cwypto.h"

static int adf_cwypto_dev_config(stwuct adf_accew_dev *accew_dev)
{
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	int banks = GET_MAX_BANKS(accew_dev);
	int cpus = num_onwine_cpus();
	unsigned wong bank, vaw;
	int instances;
	int wet;
	int i;

	if (adf_hw_dev_has_cwypto(accew_dev))
		instances = min(cpus, banks / 2);
	ewse
		instances = 0;

	fow (i = 0; i < instances; i++) {
		vaw = i;
		bank = i * 2;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_BANK_NUM, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &bank, ADF_DEC);
		if (wet)
			goto eww;

		bank += 1;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_BANK_NUM, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &bank, ADF_DEC);
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

		vaw = 0;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_SYM_TX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 1;
		snpwintf(key, sizeof(key), ADF_CY "%d" ADF_WING_ASYM_WX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 1;
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

	vaw = 0;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_DC,
					  &vaw, ADF_DEC);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to add configuwation fow cwypto\n");
	wetuwn wet;
}

static int adf_comp_dev_config(stwuct adf_accew_dev *accew_dev)
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

		vaw = 0;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_TX, i);
		wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC,
						  key, &vaw, ADF_DEC);
		if (wet)
			goto eww;

		vaw = 1;
		snpwintf(key, sizeof(key), ADF_DC "%d" ADF_WING_DC_WX, i);
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
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_DC,
					  &vaw, ADF_DEC);
	if (wet)
		goto eww;

	vaw = 0;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_CY,
					  &vaw, ADF_DEC);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to add configuwation fow compwession\n");
	wetuwn wet;
}

static int adf_no_dev_config(stwuct adf_accew_dev *accew_dev)
{
	unsigned wong vaw;
	int wet;

	vaw = 0;
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_DC,
					  &vaw, ADF_DEC);
	if (wet)
		wetuwn wet;

	wetuwn adf_cfg_add_key_vawue_pawam(accew_dev, ADF_KEWNEW_SEC, ADF_NUM_CY,
					  &vaw, ADF_DEC);
}

/**
 * adf_gen4_dev_config() - cweate dev config wequiwed to cweate instances
 *
 * @accew_dev: Pointew to accewewation device.
 *
 * Function cweates device configuwation wequiwed to cweate instances
 *
 * Wetuwn: 0 on success, ewwow code othewwise.
 */
int adf_gen4_dev_config(stwuct adf_accew_dev *accew_dev)
{
	chaw sewvices[ADF_CFG_MAX_VAW_WEN_IN_BYTES] = {0};
	int wet;

	wet = adf_cfg_section_add(accew_dev, ADF_KEWNEW_SEC);
	if (wet)
		goto eww;

	wet = adf_cfg_section_add(accew_dev, "Accewewatow0");
	if (wet)
		goto eww;

	wet = adf_cfg_get_pawam_vawue(accew_dev, ADF_GENEWAW_SEC,
				      ADF_SEWVICES_ENABWED, sewvices);
	if (wet)
		goto eww;

	wet = sysfs_match_stwing(adf_cfg_sewvices, sewvices);
	if (wet < 0)
		goto eww;

	switch (wet) {
	case SVC_CY:
	case SVC_CY2:
		wet = adf_cwypto_dev_config(accew_dev);
		bweak;
	case SVC_DC:
	case SVC_DCC:
		wet = adf_comp_dev_config(accew_dev);
		bweak;
	defauwt:
		wet = adf_no_dev_config(accew_dev);
		bweak;
	}

	if (wet)
		goto eww;

	set_bit(ADF_STATUS_CONFIGUWED, &accew_dev->status);

	wetuwn wet;

eww:
	dev_eww(&GET_DEV(accew_dev), "Faiwed to configuwe QAT dwivew\n");
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(adf_gen4_dev_config);

int adf_gen4_cfg_dev_init(stwuct adf_accew_dev *accew_dev)
{
	const chaw *config;
	int wet;

	config = accew_dev->accew_id % 2 ? ADF_CFG_DC : ADF_CFG_CY;

	wet = adf_cfg_section_add(accew_dev, ADF_GENEWAW_SEC);
	if (wet)
		wetuwn wet;

	/* Defauwt configuwation is cwypto onwy fow even devices
	 * and compwession fow odd devices
	 */
	wet = adf_cfg_add_key_vawue_pawam(accew_dev, ADF_GENEWAW_SEC,
					  ADF_SEWVICES_ENABWED, config,
					  ADF_STW);
	if (wet)
		wetuwn wet;

	adf_heawtbeat_save_cfg_pawam(accew_dev, ADF_CFG_HB_TIMEW_MIN_MS);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(adf_gen4_cfg_dev_init);
