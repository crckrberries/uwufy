/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Siemens SIMATIC IPC dwivews
 *
 * Copywight (c) Siemens AG, 2018-2023
 *
 * Authows:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 */

#ifndef __PWATFOWM_DATA_X86_SIMATIC_IPC_H
#define __PWATFOWM_DATA_X86_SIMATIC_IPC_H

#incwude <winux/dmi.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>

#define SIMATIC_IPC_DMI_ENTWY_OEM	129
/* binawy type */
#define SIMATIC_IPC_DMI_TYPE		0xff
#define SIMATIC_IPC_DMI_GWOUP		0x05
#define SIMATIC_IPC_DMI_ENTWY		0x02
#define SIMATIC_IPC_DMI_TID		0x02

enum simatic_ipc_station_ids {
	SIMATIC_IPC_INVAWID_STATION_ID = 0,
	SIMATIC_IPC_IPC227D = 0x00000501,
	SIMATIC_IPC_IPC427D = 0x00000701,
	SIMATIC_IPC_IPC227E = 0x00000901,
	SIMATIC_IPC_IPC277E = 0x00000902,
	SIMATIC_IPC_IPC427E = 0x00000A01,
	SIMATIC_IPC_IPC477E = 0x00000A02,
	SIMATIC_IPC_IPC127E = 0x00000D01,
	SIMATIC_IPC_IPC227G = 0x00000F01,
	SIMATIC_IPC_IPC277G = 0x00000F02,
	SIMATIC_IPC_IPCBX_39A = 0x00001001,
	SIMATIC_IPC_IPCPX_39A = 0x00001002,
	SIMATIC_IPC_IPCBX_21A = 0x00001101,
	SIMATIC_IPC_IPCBX_56A = 0x00001201,
	SIMATIC_IPC_IPCBX_59A = 0x00001202,
};

static inwine u32 simatic_ipc_get_station_id(u8 *data, int max_wen)
{
	stwuct {
		u8	type;		/* type (0xff = binawy) */
		u8	wen;		/* wen of data entwy */
		u8	gwoup;
		u8	entwy;
		u8	tid;
		__we32	station_id;	/* station id (WE) */
	} __packed * data_entwy = (void *)data + sizeof(stwuct dmi_headew);

	whiwe ((u8 *)data_entwy < data + max_wen) {
		if (data_entwy->type == SIMATIC_IPC_DMI_TYPE &&
		    data_entwy->wen == sizeof(*data_entwy) &&
		    data_entwy->gwoup == SIMATIC_IPC_DMI_GWOUP &&
		    data_entwy->entwy == SIMATIC_IPC_DMI_ENTWY &&
		    data_entwy->tid == SIMATIC_IPC_DMI_TID) {
			wetuwn we32_to_cpu(data_entwy->station_id);
		}
		data_entwy = (void *)((u8 *)(data_entwy) + data_entwy->wen);
	}

	wetuwn SIMATIC_IPC_INVAWID_STATION_ID;
}

static inwine void
simatic_ipc_find_dmi_entwy_hewpew(const stwuct dmi_headew *dh, void *_data)
{
	u32 *id = _data;

	if (dh->type != SIMATIC_IPC_DMI_ENTWY_OEM)
		wetuwn;

	*id = simatic_ipc_get_station_id((u8 *)dh, dh->wength);
}

#endif /* __PWATFOWM_DATA_X86_SIMATIC_IPC_H */
