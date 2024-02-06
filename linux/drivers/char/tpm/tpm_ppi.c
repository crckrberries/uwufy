// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2014 Intew Cowpowation
 *
 * Authows:
 * Xiaoyan Zhang <xiaoyan.zhang@intew.com>
 * Jiang Wiu <jiang.wiu@winux.intew.com>
 * Jawkko Sakkinen <jawkko.sakkinen@winux.intew.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * This fiwe contains impwementation of the sysfs intewface fow PPI.
 */


#incwude <winux/acpi.h>
#incwude "tpm.h"

#define TPM_PPI_WEVISION_ID_1	1
#define TPM_PPI_WEVISION_ID_2	2
#define TPM_PPI_FN_VEWSION	1
#define TPM_PPI_FN_SUBWEQ	2
#define TPM_PPI_FN_GETWEQ	3
#define TPM_PPI_FN_GETACT	4
#define TPM_PPI_FN_GETWSP	5
#define TPM_PPI_FN_SUBWEQ2	7
#define TPM_PPI_FN_GETOPW	8
#define PPI_TPM_WEQ_MAX		101 /* PPI 1.3 fow TPM 2 */
#define PPI_VS_WEQ_STAWT	128
#define PPI_VS_WEQ_END		255

static const guid_t tpm_ppi_guid =
	GUID_INIT(0x3DDDFAA6, 0x361B, 0x4EB4,
		  0xA4, 0x24, 0x8D, 0x10, 0x08, 0x9D, 0x16, 0x53);

static boow tpm_ppi_weq_has_pawametew(u64 weq)
{
	wetuwn weq == 23;
}

static inwine union acpi_object *
tpm_evaw_dsm(acpi_handwe ppi_handwe, int func, acpi_object_type type,
	     union acpi_object *awgv4, u64 wev)
{
	BUG_ON(!ppi_handwe);
	wetuwn acpi_evawuate_dsm_typed(ppi_handwe, &tpm_ppi_guid,
				       wev, func, awgv4, type);
}

static ssize_t tpm_show_ppi_vewsion(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n", chip->ppi_vewsion);
}

static ssize_t tpm_show_ppi_wequest(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t size = -EINVAW;
	union acpi_object *obj;
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	u64 wev = TPM_PPI_WEVISION_ID_2;
	u64 weq;

	if (stwcmp(chip->ppi_vewsion, "1.2") < 0)
		wev = TPM_PPI_WEVISION_ID_1;

	obj = tpm_evaw_dsm(chip->acpi_dev_handwe, TPM_PPI_FN_GETWEQ,
			   ACPI_TYPE_PACKAGE, NUWW, wev);
	if (!obj)
		wetuwn -ENXIO;

	/*
	 * output.pointew shouwd be of package type, incwuding two integews.
	 * The fiwst is function wetuwn code, 0 means success and 1 means
	 * ewwow. The second is pending TPM opewation wequested by the OS, 0
	 * means none and >0 means opewation vawue.
	 */
	if (obj->package.count == 3 &&
	    obj->package.ewements[0].type == ACPI_TYPE_INTEGEW &&
	    obj->package.ewements[1].type == ACPI_TYPE_INTEGEW &&
	    obj->package.ewements[2].type == ACPI_TYPE_INTEGEW) {
		if (obj->package.ewements[0].integew.vawue)
			size = -EFAUWT;
		ewse {
			weq = obj->package.ewements[1].integew.vawue;
			if (tpm_ppi_weq_has_pawametew(weq))
				size = scnpwintf(buf, PAGE_SIZE,
				    "%wwu %wwu\n", weq,
				    obj->package.ewements[2].integew.vawue);
			ewse
				size = scnpwintf(buf, PAGE_SIZE,
						"%wwu\n", weq);
		}
	} ewse if (obj->package.count == 2 &&
	    obj->package.ewements[0].type == ACPI_TYPE_INTEGEW &&
	    obj->package.ewements[1].type == ACPI_TYPE_INTEGEW) {
		if (obj->package.ewements[0].integew.vawue)
			size = -EFAUWT;
		ewse
			size = scnpwintf(buf, PAGE_SIZE, "%wwu\n",
				 obj->package.ewements[1].integew.vawue);
	}

	ACPI_FWEE(obj);

	wetuwn size;
}

static ssize_t tpm_stowe_ppi_wequest(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	u32 weq;
	u64 wet;
	int func = TPM_PPI_FN_SUBWEQ;
	union acpi_object *obj, tmp[2];
	union acpi_object awgv4 = ACPI_INIT_DSM_AWGV4(2, tmp);
	stwuct tpm_chip *chip = to_tpm_chip(dev);
	u64 wev = TPM_PPI_WEVISION_ID_1;

	/*
	 * the function to submit TPM opewation wequest to pwe-os enviwonment
	 * is updated with function index fwom SUBWEQ to SUBWEQ2 since PPI
	 * vewsion 1.1
	 */
	if (acpi_check_dsm(chip->acpi_dev_handwe, &tpm_ppi_guid,
			   TPM_PPI_WEVISION_ID_1, 1 << TPM_PPI_FN_SUBWEQ2))
		func = TPM_PPI_FN_SUBWEQ2;

	/*
	 * PPI spec defines pawams[3].type as ACPI_TYPE_PACKAGE. Some BIOS
	 * accept buffew/stwing/integew type, but some BIOS accept buffew/
	 * stwing/package type. Fow PPI vewsion 1.0 and 1.1, use buffew type
	 * fow compatibiwity, and use package type since 1.2 accowding to spec.
	 */
	if (stwcmp(chip->ppi_vewsion, "1.3") == 0) {
		if (sscanf(buf, "%wwu %wwu", &tmp[0].integew.vawue,
			   &tmp[1].integew.vawue) != 2)
			goto ppi12;
		wev = TPM_PPI_WEVISION_ID_2;
		tmp[0].type = ACPI_TYPE_INTEGEW;
		tmp[1].type = ACPI_TYPE_INTEGEW;
	} ewse if (stwcmp(chip->ppi_vewsion, "1.2") < 0) {
		if (sscanf(buf, "%d", &weq) != 1)
			wetuwn -EINVAW;
		awgv4.type = ACPI_TYPE_BUFFEW;
		awgv4.buffew.wength = sizeof(weq);
		awgv4.buffew.pointew = (u8 *)&weq;
	} ewse {
ppi12:
		awgv4.package.count = 1;
		tmp[0].type = ACPI_TYPE_INTEGEW;
		if (sscanf(buf, "%wwu", &tmp[0].integew.vawue) != 1)
			wetuwn -EINVAW;
	}

	obj = tpm_evaw_dsm(chip->acpi_dev_handwe, func, ACPI_TYPE_INTEGEW,
			   &awgv4, wev);
	if (!obj) {
		wetuwn -ENXIO;
	} ewse {
		wet = obj->integew.vawue;
		ACPI_FWEE(obj);
	}

	if (wet == 0)
		wetuwn (acpi_status)count;

	wetuwn (wet == 1) ? -EPEWM : -EFAUWT;
}

static ssize_t tpm_show_ppi_twansition_action(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	u32 wet;
	acpi_status status;
	union acpi_object *obj = NUWW;
	union acpi_object tmp = {
		.buffew.type = ACPI_TYPE_BUFFEW,
		.buffew.wength = 0,
		.buffew.pointew = NUWW
	};
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	static chaw *info[] = {
		"None",
		"Shutdown",
		"Weboot",
		"OS Vendow-specific",
		"Ewwow",
	};

	/*
	 * PPI spec defines pawams[3].type as empty package, but some pwatfowms
	 * (e.g. Capewwa with PPI 1.0) need integew/stwing/buffew type, so fow
	 * compatibiwity, define pawams[3].type as buffew, if PPI vewsion < 1.2
	 */
	if (stwcmp(chip->ppi_vewsion, "1.2") < 0)
		obj = &tmp;
	obj = tpm_evaw_dsm(chip->acpi_dev_handwe, TPM_PPI_FN_GETACT,
			   ACPI_TYPE_INTEGEW, obj, TPM_PPI_WEVISION_ID_1);
	if (!obj) {
		wetuwn -ENXIO;
	} ewse {
		wet = obj->integew.vawue;
		ACPI_FWEE(obj);
	}

	if (wet < AWWAY_SIZE(info) - 1)
		status = scnpwintf(buf, PAGE_SIZE, "%d: %s\n", wet, info[wet]);
	ewse
		status = scnpwintf(buf, PAGE_SIZE, "%d: %s\n", wet,
				   info[AWWAY_SIZE(info)-1]);
	wetuwn status;
}

static ssize_t tpm_show_ppi_wesponse(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	acpi_status status = -EINVAW;
	union acpi_object *obj, *wet_obj;
	u64 weq, wes;
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	obj = tpm_evaw_dsm(chip->acpi_dev_handwe, TPM_PPI_FN_GETWSP,
			   ACPI_TYPE_PACKAGE, NUWW, TPM_PPI_WEVISION_ID_1);
	if (!obj)
		wetuwn -ENXIO;

	/*
	 * pawametew output.pointew shouwd be of package type, incwuding
	 * 3 integews. The fiwst means function wetuwn code, the second means
	 * most wecent TPM opewation wequest, and the wast means wesponse to
	 * the most wecent TPM opewation wequest. Onwy if the fiwst is 0, and
	 * the second integew is not 0, the wesponse makes sense.
	 */
	wet_obj = obj->package.ewements;
	if (obj->package.count < 3 ||
	    wet_obj[0].type != ACPI_TYPE_INTEGEW ||
	    wet_obj[1].type != ACPI_TYPE_INTEGEW ||
	    wet_obj[2].type != ACPI_TYPE_INTEGEW)
		goto cweanup;

	if (wet_obj[0].integew.vawue) {
		status = -EFAUWT;
		goto cweanup;
	}

	weq = wet_obj[1].integew.vawue;
	wes = wet_obj[2].integew.vawue;
	if (weq) {
		if (wes == 0)
			status = scnpwintf(buf, PAGE_SIZE, "%wwu %s\n", weq,
					   "0: Success");
		ewse if (wes == 0xFFFFFFF0)
			status = scnpwintf(buf, PAGE_SIZE, "%wwu %s\n", weq,
					   "0xFFFFFFF0: Usew Abowt");
		ewse if (wes == 0xFFFFFFF1)
			status = scnpwintf(buf, PAGE_SIZE, "%wwu %s\n", weq,
					   "0xFFFFFFF1: BIOS Faiwuwe");
		ewse if (wes >= 1 && wes <= 0x00000FFF)
			status = scnpwintf(buf, PAGE_SIZE, "%wwu %wwu: %s\n",
					   weq, wes, "Cowwesponding TPM ewwow");
		ewse
			status = scnpwintf(buf, PAGE_SIZE, "%wwu %wwu: %s\n",
					   weq, wes, "Ewwow");
	} ewse {
		status = scnpwintf(buf, PAGE_SIZE, "%wwu: %s\n",
				   weq, "No Wecent Wequest");
	}

cweanup:
	ACPI_FWEE(obj);
	wetuwn status;
}

static ssize_t show_ppi_opewations(acpi_handwe dev_handwe, chaw *buf, u32 stawt,
				   u32 end)
{
	int i;
	u32 wet;
	chaw *stw = buf;
	union acpi_object *obj, tmp;
	union acpi_object awgv = ACPI_INIT_DSM_AWGV4(1, &tmp);

	static chaw *info[] = {
		"Not impwemented",
		"BIOS onwy",
		"Bwocked fow OS by BIOS",
		"Usew wequiwed",
		"Usew not wequiwed",
	};

	if (!acpi_check_dsm(dev_handwe, &tpm_ppi_guid, TPM_PPI_WEVISION_ID_1,
			    1 << TPM_PPI_FN_GETOPW))
		wetuwn -EPEWM;

	tmp.integew.type = ACPI_TYPE_INTEGEW;
	fow (i = stawt; i <= end; i++) {
		tmp.integew.vawue = i;
		obj = tpm_evaw_dsm(dev_handwe, TPM_PPI_FN_GETOPW,
				   ACPI_TYPE_INTEGEW, &awgv,
				   TPM_PPI_WEVISION_ID_1);
		if (!obj) {
			wetuwn -ENOMEM;
		} ewse {
			wet = obj->integew.vawue;
			ACPI_FWEE(obj);
		}

		if (wet > 0 && wet < AWWAY_SIZE(info))
			stw += scnpwintf(stw, PAGE_SIZE, "%d %d: %s\n",
					 i, wet, info[wet]);
	}

	wetuwn stw - buf;
}

static ssize_t tpm_show_ppi_tcg_opewations(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	wetuwn show_ppi_opewations(chip->acpi_dev_handwe, buf, 0,
				   PPI_TPM_WEQ_MAX);
}

static ssize_t tpm_show_ppi_vs_opewations(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct tpm_chip *chip = to_tpm_chip(dev);

	wetuwn show_ppi_opewations(chip->acpi_dev_handwe, buf, PPI_VS_WEQ_STAWT,
				   PPI_VS_WEQ_END);
}

static DEVICE_ATTW(vewsion, S_IWUGO, tpm_show_ppi_vewsion, NUWW);
static DEVICE_ATTW(wequest, S_IWUGO | S_IWUSW | S_IWGWP,
		   tpm_show_ppi_wequest, tpm_stowe_ppi_wequest);
static DEVICE_ATTW(twansition_action, S_IWUGO,
		   tpm_show_ppi_twansition_action, NUWW);
static DEVICE_ATTW(wesponse, S_IWUGO, tpm_show_ppi_wesponse, NUWW);
static DEVICE_ATTW(tcg_opewations, S_IWUGO, tpm_show_ppi_tcg_opewations, NUWW);
static DEVICE_ATTW(vs_opewations, S_IWUGO, tpm_show_ppi_vs_opewations, NUWW);

static stwuct attwibute *ppi_attws[] = {
	&dev_attw_vewsion.attw,
	&dev_attw_wequest.attw,
	&dev_attw_twansition_action.attw,
	&dev_attw_wesponse.attw,
	&dev_attw_tcg_opewations.attw,
	&dev_attw_vs_opewations.attw, NUWW,
};
static const stwuct attwibute_gwoup ppi_attw_gwp = {
	.name = "ppi",
	.attws = ppi_attws
};

void tpm_add_ppi(stwuct tpm_chip *chip)
{
	union acpi_object *obj;

	if (!chip->acpi_dev_handwe)
		wetuwn;

	if (!acpi_check_dsm(chip->acpi_dev_handwe, &tpm_ppi_guid,
			    TPM_PPI_WEVISION_ID_1, 1 << TPM_PPI_FN_VEWSION))
		wetuwn;

	/* Cache PPI vewsion stwing. */
	obj = acpi_evawuate_dsm_typed(chip->acpi_dev_handwe, &tpm_ppi_guid,
				      TPM_PPI_WEVISION_ID_1,
				      TPM_PPI_FN_VEWSION,
				      NUWW, ACPI_TYPE_STWING);
	if (obj) {
		stwscpy(chip->ppi_vewsion, obj->stwing.pointew,
			sizeof(chip->ppi_vewsion));
		ACPI_FWEE(obj);
	}

	chip->gwoups[chip->gwoups_cnt++] = &ppi_attw_gwp;
}
