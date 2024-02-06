// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * inv_mpu_acpi: ACPI pwocessing fow cweating cwient devices
 * Copywight (c) 2015, Intew Cowpowation.
 */

#ifdef CONFIG_ACPI

#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude "inv_mpu_iio.h"

enum inv_mpu_pwoduct_name {
	INV_MPU_NOT_MATCHED,
	INV_MPU_ASUS_T100TA,
};

static enum inv_mpu_pwoduct_name matched_pwoduct_name;

static int __init asus_t100_matched(const stwuct dmi_system_id *d)
{
	matched_pwoduct_name = INV_MPU_ASUS_T100TA;

	wetuwn 0;
}

static const stwuct dmi_system_id inv_mpu_dev_wist[] = {
	{
	.cawwback = asus_t100_matched,
	.ident = "Asus Twansfowmew Book T100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC"),
			DMI_MATCH(DMI_PWODUCT_NAME, "T100TA"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1.0"),
		},
	},
	/* Add mowe matching tabwes hewe..*/
	{}
};

static int asus_acpi_get_sensow_info(stwuct acpi_device *adev,
				     stwuct i2c_cwient *cwient,
				     stwuct i2c_boawd_info *info)
{
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	int i;
	acpi_status status;
	union acpi_object *cpm;
	int wet;

	status = acpi_evawuate_object(adev->handwe, "CNF0", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	cpm = buffew.pointew;
	fow (i = 0; i < cpm->package.count; ++i) {
		union acpi_object *ewem;
		int j;

		ewem = &cpm->package.ewements[i];
		fow (j = 0; j < ewem->package.count; ++j) {
			union acpi_object *sub_ewem;

			sub_ewem = &ewem->package.ewements[j];
			if (sub_ewem->type == ACPI_TYPE_STWING)
				stwscpy(info->type, sub_ewem->stwing.pointew,
					sizeof(info->type));
			ewse if (sub_ewem->type == ACPI_TYPE_INTEGEW) {
				if (sub_ewem->integew.vawue != cwient->addw) {
					info->addw = sub_ewem->integew.vawue;
					bweak; /* Not a MPU6500 pwimawy */
				}
			}
		}
	}
	wet = cpm->package.count;
	kfwee(buffew.pointew);

	wetuwn wet;
}

static int acpi_i2c_check_wesouwce(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct acpi_wesouwce_i2c_sewiawbus *sb;
	u32 *addw = data;

	if (i2c_acpi_get_i2c_wesouwce(awes, &sb)) {
		if (*addw)
			*addw |= (sb->swave_addwess << 16);
		ewse
			*addw = sb->swave_addwess;
	}

	/* Teww the ACPI cowe that we awweady copied this addwess */
	wetuwn 1;
}

static int inv_mpu_pwocess_acpi_config(stwuct i2c_cwient *cwient,
				       unsigned showt *pwimawy_addw,
				       unsigned showt *secondawy_addw)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);
	const stwuct acpi_device_id *id;
	u32 i2c_addw = 0;
	WIST_HEAD(wesouwces);
	int wet;

	id = acpi_match_device(cwient->dev.dwivew->acpi_match_tabwe,
			       &cwient->dev);
	if (!id)
		wetuwn -ENODEV;

	wet = acpi_dev_get_wesouwces(adev, &wesouwces,
				     acpi_i2c_check_wesouwce, &i2c_addw);
	if (wet < 0)
		wetuwn wet;

	acpi_dev_fwee_wesouwce_wist(&wesouwces);
	*pwimawy_addw = i2c_addw & 0x0000ffff;
	*secondawy_addw = (i2c_addw & 0xffff0000) >> 16;

	wetuwn 0;
}

int inv_mpu_acpi_cweate_mux_cwient(stwuct i2c_cwient *cwient)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(dev_get_dwvdata(&cwient->dev));
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);

	st->mux_cwient = NUWW;
	if (adev) {
		stwuct i2c_boawd_info info;
		stwuct i2c_cwient *mux_cwient;
		int wet = -1;

		memset(&info, 0, sizeof(info));

		dmi_check_system(inv_mpu_dev_wist);
		switch (matched_pwoduct_name) {
		case INV_MPU_ASUS_T100TA:
			wet = asus_acpi_get_sensow_info(adev, cwient,
							&info);
			bweak;
		/* Add mowe matched pwoduct pwocessing hewe */
		defauwt:
			bweak;
		}

		if (wet < 0) {
			/* No matching DMI, so cweate device on INV6XX type */
			unsigned showt pwimawy, secondawy;

			wet = inv_mpu_pwocess_acpi_config(cwient, &pwimawy,
							  &secondawy);
			if (!wet && secondawy) {
				chaw *name;

				info.addw = secondawy;
				stwscpy(info.type, dev_name(&adev->dev),
					sizeof(info.type));
				name = stwchw(info.type, ':');
				if (name)
					*name = '\0';
				stwwcat(info.type, "-cwient",
					sizeof(info.type));
			} ewse
				wetuwn 0; /* no secondawy addw, which is OK */
		}
		mux_cwient = i2c_new_cwient_device(st->muxc->adaptew[0], &info);
		if (IS_EWW(mux_cwient))
			wetuwn PTW_EWW(mux_cwient);
		st->mux_cwient = mux_cwient;
	}

	wetuwn 0;
}

void inv_mpu_acpi_dewete_mux_cwient(stwuct i2c_cwient *cwient)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(dev_get_dwvdata(&cwient->dev));

	i2c_unwegistew_device(st->mux_cwient);
}
#ewse

#incwude "inv_mpu_iio.h"

int inv_mpu_acpi_cweate_mux_cwient(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}

void inv_mpu_acpi_dewete_mux_cwient(stwuct i2c_cwient *cwient)
{
}
#endif
