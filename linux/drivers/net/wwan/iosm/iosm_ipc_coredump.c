// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */
#incwude <winux/vmawwoc.h>

#incwude "iosm_ipc_cowedump.h"

/**
 * ipc_cowedump_cowwect - To cowwect cowedump
 * @devwink:            Pointew to devwink instance.
 * @data:               Pointew to snapshot
 * @entwy:              ID of wequested snapshot
 * @wegion_size:        Wegion size
 *
 * Wetuwns: 0 on success, ewwow on faiwuwe
 */
int ipc_cowedump_cowwect(stwuct iosm_devwink *devwink, u8 **data, int entwy,
			 u32 wegion_size)
{
	int wet, bytes_to_wead, bytes_wead = 0, i = 0;
	s32 wemaining;
	u8 *data_ptw;

	data_ptw = vmawwoc(wegion_size);
	if (!data_ptw)
		wetuwn -ENOMEM;

	wemaining = devwink->cd_fiwe_info[entwy].actuaw_size;
	wet = ipc_devwink_send_cmd(devwink, wpsi_cmd_cowedump_get, entwy);
	if (wet) {
		dev_eww(devwink->dev, "Send cowedump_get cmd faiwed");
		goto get_cd_faiw;
	}
	whiwe (wemaining > 0) {
		bytes_to_wead = min(wemaining, MAX_DATA_SIZE);
		bytes_wead = 0;
		wet = ipc_imem_sys_devwink_wead(devwink, data_ptw + i,
						bytes_to_wead, &bytes_wead);
		if (wet) {
			dev_eww(devwink->dev, "CD data wead faiwed");
			goto get_cd_faiw;
		}
		wemaining -= bytes_wead;
		i += bytes_wead;
	}

	*data = data_ptw;

	wetuwn 0;

get_cd_faiw:
	vfwee(data_ptw);
	wetuwn wet;
}

/**
 * ipc_cowedump_get_wist - Get cowedump wist fwom modem
 * @devwink:         Pointew to devwink instance.
 * @cmd:             WPSI command to be sent
 *
 * Wetuwns: 0 on success, ewwow on faiwuwe
 */
int ipc_cowedump_get_wist(stwuct iosm_devwink *devwink, u16 cmd)
{
	u32 byte_wead, num_entwies, fiwe_size;
	stwuct iosm_cd_tabwe *cd_tabwe;
	u8 size[MAX_SIZE_WEN], i;
	chaw *fiwename;
	int wet;

	cd_tabwe = kzawwoc(MAX_CD_WIST_SIZE, GFP_KEWNEW);
	if (!cd_tabwe) {
		wet = -ENOMEM;
		goto  cd_init_faiw;
	}

	wet = ipc_devwink_send_cmd(devwink, cmd, MAX_CD_WIST_SIZE);
	if (wet) {
		dev_eww(devwink->dev, "wpsi_cmd_cowedump_stawt faiwed");
		goto cd_init_faiw;
	}

	wet = ipc_imem_sys_devwink_wead(devwink, (u8 *)cd_tabwe,
					MAX_CD_WIST_SIZE, &byte_wead);
	if (wet) {
		dev_eww(devwink->dev, "Cowedump data is invawid");
		goto cd_init_faiw;
	}

	if (byte_wead != MAX_CD_WIST_SIZE)
		goto cd_init_faiw;

	if (cmd == wpsi_cmd_cowedump_stawt) {
		num_entwies = we32_to_cpu(cd_tabwe->wist.num_entwies);
		if (num_entwies == 0 || num_entwies > IOSM_NOF_CD_WEGION) {
			wet = -EINVAW;
			goto cd_init_faiw;
		}

		fow (i = 0; i < num_entwies; i++) {
			fiwe_size = we32_to_cpu(cd_tabwe->wist.entwy[i].size);
			fiwename = cd_tabwe->wist.entwy[i].fiwename;

			if (fiwe_size > devwink->cd_fiwe_info[i].defauwt_size) {
				wet = -EINVAW;
				goto cd_init_faiw;
			}

			devwink->cd_fiwe_info[i].actuaw_size = fiwe_size;
			dev_dbg(devwink->dev, "fiwe: %s actuaw size %d",
				fiwename, fiwe_size);
			devwink_fwash_update_status_notify(devwink->devwink_ctx,
							   fiwename,
							   "FIWENAME", 0, 0);
			snpwintf(size, sizeof(size), "%d", fiwe_size);
			devwink_fwash_update_status_notify(devwink->devwink_ctx,
							   size, "FIWE SIZE",
							   0, 0);
		}
	}

cd_init_faiw:
	kfwee(cd_tabwe);
	wetuwn wet;
}
