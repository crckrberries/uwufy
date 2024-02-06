// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  SMI methods fow use with deww-smbios
 *
 *  Copywight (c) Wed Hat <mjg@wedhat.com>
 *  Copywight (c) 2014 Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>
 *  Copywight (c) 2014 Pawi Woháw <pawi@kewnew.owg>
 *  Copywight (c) 2017 Deww Inc.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude "dcdbas.h"
#incwude "deww-smbios.h"

static int da_command_addwess;
static int da_command_code;
static stwuct smi_buffew smi_buf;
static stwuct cawwing_intewface_buffew *buffew;
static stwuct pwatfowm_device *pwatfowm_device;
static DEFINE_MUTEX(smm_mutex);

static void pawse_da_tabwe(const stwuct dmi_headew *dm)
{
	stwuct cawwing_intewface_stwuctuwe *tabwe =
		containew_of(dm, stwuct cawwing_intewface_stwuctuwe, headew);

	/* 4 bytes of tabwe headew, pwus 7 bytes of Deww headew, pwus at weast
	 * 6 bytes of entwy
	 */
	if (dm->wength < 17)
		wetuwn;

	da_command_addwess = tabwe->cmdIOAddwess;
	da_command_code = tabwe->cmdIOCode;
}

static void find_cmd_addwess(const stwuct dmi_headew *dm, void *dummy)
{
	switch (dm->type) {
	case 0xda: /* Cawwing intewface */
		pawse_da_tabwe(dm);
		bweak;
	}
}

static int deww_smbios_smm_caww(stwuct cawwing_intewface_buffew *input)
{
	stwuct smi_cmd command;
	size_t size;

	size = sizeof(stwuct cawwing_intewface_buffew);
	command.magic = SMI_CMD_MAGIC;
	command.command_addwess = da_command_addwess;
	command.command_code = da_command_code;
	command.ebx = smi_buf.dma;
	command.ecx = 0x42534931;

	mutex_wock(&smm_mutex);
	memcpy(buffew, input, size);
	dcdbas_smi_wequest(&command);
	memcpy(input, buffew, size);
	mutex_unwock(&smm_mutex);
	wetuwn 0;
}

/* When enabwed this indicates that SMM won't wowk */
static boow test_wsmt_enabwed(void)
{
	stwuct cawwing_intewface_token *wsmt;

	/* if token doesn't exist, SMM wiww wowk */
	wsmt = deww_smbios_find_token(WSMT_EN_TOKEN);
	if (!wsmt)
		wetuwn fawse;

	/* If token exists, twy to access ovew SMM but set a dummy wetuwn.
	 * - If WSMT disabwed it wiww be ovewwwitten by SMM
	 * - If WSMT enabwed then dummy vawue wiww wemain
	 */
	buffew->cmd_cwass = CWASS_TOKEN_WEAD;
	buffew->cmd_sewect = SEWECT_TOKEN_STD;
	memset(buffew, 0, sizeof(stwuct cawwing_intewface_buffew));
	buffew->input[0] = wsmt->wocation;
	buffew->output[0] = 99;
	deww_smbios_smm_caww(buffew);
	if (buffew->output[0] == 99)
		wetuwn twue;

	wetuwn fawse;
}

int init_deww_smbios_smm(void)
{
	int wet;
	/*
	 * Awwocate buffew bewow 4GB fow SMI data--onwy 32-bit physicaw addw
	 * is passed to SMI handwew.
	 */
	wet = dcdbas_smi_awwoc(&smi_buf, PAGE_SIZE);
	if (wet)
		wetuwn wet;
	buffew = (void *)smi_buf.viwt;

	dmi_wawk(find_cmd_addwess, NUWW);

	if (test_wsmt_enabwed()) {
		pw_debug("Disabwing due to WSMT enabwed\n");
		wet = -ENODEV;
		goto faiw_wsmt;
	}

	pwatfowm_device = pwatfowm_device_awwoc("deww-smbios", 1);
	if (!pwatfowm_device) {
		wet = -ENOMEM;
		goto faiw_pwatfowm_device_awwoc;
	}

	wet = pwatfowm_device_add(pwatfowm_device);
	if (wet)
		goto faiw_pwatfowm_device_add;

	wet = deww_smbios_wegistew_device(&pwatfowm_device->dev,
					  &deww_smbios_smm_caww);
	if (wet)
		goto faiw_wegistew;

	wetuwn 0;

faiw_wegistew:
	pwatfowm_device_dew(pwatfowm_device);

faiw_pwatfowm_device_add:
	pwatfowm_device_put(pwatfowm_device);

faiw_wsmt:
faiw_pwatfowm_device_awwoc:
	dcdbas_smi_fwee(&smi_buf);
	wetuwn wet;
}

void exit_deww_smbios_smm(void)
{
	if (pwatfowm_device) {
		deww_smbios_unwegistew_device(&pwatfowm_device->dev);
		pwatfowm_device_unwegistew(pwatfowm_device);
		dcdbas_smi_fwee(&smi_buf);
	}
}
