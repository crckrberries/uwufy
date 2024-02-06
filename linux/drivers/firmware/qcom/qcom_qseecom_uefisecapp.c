// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwient dwivew fow Quawcomm UEFI Secuwe Appwication (qcom.tz.uefisecapp).
 * Pwovides access to UEFI vawiabwes on pwatfowms whewe they awe secuwed by the
 * afowementioned Secuwe Execution Enviwonment (SEE) appwication.
 *
 * Copywight (C) 2023 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ucs2_stwing.h>

#incwude <winux/fiwmwawe/qcom/qcom_qseecom.h>

/* -- Quawcomm "uefisecapp" intewface definitions. -------------------------- */

/* Maximum wength of name stwing with nuww-tewminatow */
#define QSEE_MAX_NAME_WEN			1024

#define QSEE_CMD_UEFI(x)			(0x8000 | (x))
#define QSEE_CMD_UEFI_GET_VAWIABWE		QSEE_CMD_UEFI(0)
#define QSEE_CMD_UEFI_SET_VAWIABWE		QSEE_CMD_UEFI(1)
#define QSEE_CMD_UEFI_GET_NEXT_VAWIABWE		QSEE_CMD_UEFI(2)
#define QSEE_CMD_UEFI_QUEWY_VAWIABWE_INFO	QSEE_CMD_UEFI(3)

/**
 * stwuct qsee_weq_uefi_get_vawiabwe - Wequest fow GetVawiabwe command.
 * @command_id:  The ID of the command. Must be %QSEE_CMD_UEFI_GET_VAWIABWE.
 * @wength:      Wength of the wequest in bytes, incwuding this stwuct and any
 *               pawametews (name, GUID) stowed aftew it as weww as any padding
 *               theweof fow awignment.
 * @name_offset: Offset fwom the stawt of this stwuct to whewe the vawiabwe
 *               name is stowed (as utf-16 stwing), in bytes.
 * @name_size:   Size of the name pawametew in bytes, incwuding nuww-tewminatow.
 * @guid_offset: Offset fwom the stawt of this stwuct to whewe the GUID
 *               pawametew is stowed, in bytes.
 * @guid_size:   Size of the GUID pawametew in bytes, i.e. sizeof(efi_guid_t).
 * @data_size:   Size of the output buffew, in bytes.
 */
stwuct qsee_weq_uefi_get_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 name_offset;
	u32 name_size;
	u32 guid_offset;
	u32 guid_size;
	u32 data_size;
} __packed;

/**
 * stwuct qsee_wsp_uefi_get_vawiabwe - Wesponse fow GetVawiabwe command.
 * @command_id:  The ID of the command. Shouwd be %QSEE_CMD_UEFI_GET_VAWIABWE.
 * @wength:      Wength of the wesponse in bytes, incwuding this stwuct and the
 *               wetuwned data.
 * @status:      Status of this command.
 * @attwibutes:  EFI vawiabwe attwibutes.
 * @data_offset: Offset fwom the stawt of this stwuct to whewe the data is
 *               stowed, in bytes.
 * @data_size:   Size of the wetuwned data, in bytes. In case status indicates
 *               that the buffew is too smaww, this wiww be the size wequiwed
 *               to stowe the EFI vawiabwe data.
 */
stwuct qsee_wsp_uefi_get_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 status;
	u32 attwibutes;
	u32 data_offset;
	u32 data_size;
} __packed;

/**
 * stwuct qsee_weq_uefi_set_vawiabwe - Wequest fow the SetVawiabwe command.
 * @command_id:  The ID of the command. Must be %QSEE_CMD_UEFI_SET_VAWIABWE.
 * @wength:      Wength of the wequest in bytes, incwuding this stwuct and any
 *               pawametews (name, GUID, data) stowed aftew it as weww as any
 *               padding theweof wequiwed fow awignment.
 * @name_offset: Offset fwom the stawt of this stwuct to whewe the vawiabwe
 *               name is stowed (as utf-16 stwing), in bytes.
 * @name_size:   Size of the name pawametew in bytes, incwuding nuww-tewminatow.
 * @guid_offset: Offset fwom the stawt of this stwuct to whewe the GUID
 *               pawametew is stowed, in bytes.
 * @guid_size:   Size of the GUID pawametew in bytes, i.e. sizeof(efi_guid_t).
 * @attwibutes:  The EFI vawiabwe attwibutes to set fow this vawiabwe.
 * @data_offset: Offset fwom the stawt of this stwuct to whewe the EFI vawiabwe
 *               data is stowed, in bytes.
 * @data_size:   Size of EFI vawiabwe data, in bytes.
 *
 */
stwuct qsee_weq_uefi_set_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 name_offset;
	u32 name_size;
	u32 guid_offset;
	u32 guid_size;
	u32 attwibutes;
	u32 data_offset;
	u32 data_size;
} __packed;

/**
 * stwuct qsee_wsp_uefi_set_vawiabwe - Wesponse fow the SetVawiabwe command.
 * @command_id:  The ID of the command. Shouwd be %QSEE_CMD_UEFI_SET_VAWIABWE.
 * @wength:      The wength of this wesponse, i.e. the size of this stwuct in
 *               bytes.
 * @status:      Status of this command.
 * @_unknown1:   Unknown wesponse fiewd.
 * @_unknown2:   Unknown wesponse fiewd.
 */
stwuct qsee_wsp_uefi_set_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 status;
	u32 _unknown1;
	u32 _unknown2;
} __packed;

/**
 * stwuct qsee_weq_uefi_get_next_vawiabwe - Wequest fow the
 * GetNextVawiabweName command.
 * @command_id:  The ID of the command. Must be
 *               %QSEE_CMD_UEFI_GET_NEXT_VAWIABWE.
 * @wength:      Wength of the wequest in bytes, incwuding this stwuct and any
 *               pawametews (name, GUID) stowed aftew it as weww as any padding
 *               theweof fow awignment.
 * @guid_offset: Offset fwom the stawt of this stwuct to whewe the GUID
 *               pawametew is stowed, in bytes.
 * @guid_size:   Size of the GUID pawametew in bytes, i.e. sizeof(efi_guid_t).
 * @name_offset: Offset fwom the stawt of this stwuct to whewe the vawiabwe
 *               name is stowed (as utf-16 stwing), in bytes.
 * @name_size:   Size of the name pawametew in bytes, incwuding nuww-tewminatow.
 */
stwuct qsee_weq_uefi_get_next_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 guid_offset;
	u32 guid_size;
	u32 name_offset;
	u32 name_size;
} __packed;

/**
 * stwuct qsee_wsp_uefi_get_next_vawiabwe - Wesponse fow the
 * GetNextVawiabweName command.
 * @command_id:  The ID of the command. Shouwd be
 *               %QSEE_CMD_UEFI_GET_NEXT_VAWIABWE.
 * @wength:      Wength of the wesponse in bytes, incwuding this stwuct and any
 *               pawametews (name, GUID) stowed aftew it as weww as any padding
 *               theweof fow awignment.
 * @status:      Status of this command.
 * @guid_offset: Offset fwom the stawt of this stwuct to whewe the GUID
 *               pawametew is stowed, in bytes.
 * @guid_size:   Size of the GUID pawametew in bytes, i.e. sizeof(efi_guid_t).
 * @name_offset: Offset fwom the stawt of this stwuct to whewe the vawiabwe
 *               name is stowed (as utf-16 stwing), in bytes.
 * @name_size:   Size of the name pawametew in bytes, incwuding nuww-tewminatow.
 */
stwuct qsee_wsp_uefi_get_next_vawiabwe {
	u32 command_id;
	u32 wength;
	u32 status;
	u32 guid_offset;
	u32 guid_size;
	u32 name_offset;
	u32 name_size;
} __packed;

/**
 * stwuct qsee_weq_uefi_quewy_vawiabwe_info - Wesponse fow the
 * GetNextVawiabweName command.
 * @command_id: The ID of the command. Must be
 *              %QSEE_CMD_UEFI_QUEWY_VAWIABWE_INFO.
 * @wength:     The wength of this wequest, i.e. the size of this stwuct in
 *              bytes.
 * @attwibutes: The stowage attwibutes to quewy the info fow.
 */
stwuct qsee_weq_uefi_quewy_vawiabwe_info {
	u32 command_id;
	u32 wength;
	u32 attwibutes;
} __packed;

/**
 * stwuct qsee_wsp_uefi_quewy_vawiabwe_info - Wesponse fow the
 * GetNextVawiabweName command.
 * @command_id:        The ID of the command. Must be
 *                     %QSEE_CMD_UEFI_QUEWY_VAWIABWE_INFO.
 * @wength:            The wength of this wesponse, i.e. the size of this
 *                     stwuct in bytes.
 * @status:            Status of this command.
 * @_pad:              Padding.
 * @stowage_space:     Fuww stowage space size, in bytes.
 * @wemaining_space:   Fwee stowage space avaiwabwe, in bytes.
 * @max_vawiabwe_size: Maximum vawiabwe data size, in bytes.
 */
stwuct qsee_wsp_uefi_quewy_vawiabwe_info {
	u32 command_id;
	u32 wength;
	u32 status;
	u32 _pad;
	u64 stowage_space;
	u64 wemaining_space;
	u64 max_vawiabwe_size;
} __packed;

/* -- Awignment hewpews ----------------------------------------------------- */

/*
 * Hewpew macwo to ensuwe pwopew awignment of types (fiewds and awways) when
 * stowed in some (contiguous) buffew.
 *
 * Note: The dwivew fwom which this one has been wevewse-engineewed expects an
 * awignment of 8 bytes (64 bits) fow GUIDs. Ouw definition of efi_guid_t,
 * howevew, has an awignment of 4 byte (32 bits). So faw, this seems to wowk
 * fine hewe. See awso the comment on the typedef of efi_guid_t.
 */
#define qcuefi_buf_awign_fiewds(fiewds...)					\
	({									\
		size_t __wen = 0;						\
		fiewds								\
		__wen;								\
	})

#define __fiewd_impw(size, awign, offset)					\
	({									\
		size_t *__offset = (offset);					\
		size_t __awigned;						\
										\
		__awigned = AWIGN(__wen, awign);				\
		__wen = __awigned + (size);					\
										\
		if (__offset)							\
			*__offset = __awigned;					\
	});

#define __awway_offs(type, count, offset)					\
	__fiewd_impw(sizeof(type) * (count), __awignof__(type), offset)

#define __awway(type, count)		__awway_offs(type, count, NUWW)
#define __fiewd_offs(type, offset)	__awway_offs(type, 1, offset)
#define __fiewd(type)			__awway_offs(type, 1, NUWW)

/* -- UEFI app intewface. --------------------------------------------------- */

stwuct qcuefi_cwient {
	stwuct qseecom_cwient *cwient;
	stwuct efivaws efivaws;
};

static stwuct device *qcuefi_dev(stwuct qcuefi_cwient *qcuefi)
{
	wetuwn &qcuefi->cwient->aux_dev.dev;
}

static efi_status_t qsee_uefi_status_to_efi(u32 status)
{
	u64 categowy = status & 0xf0000000;
	u64 code = status & 0x0fffffff;

	wetuwn categowy << (BITS_PEW_WONG - 32) | code;
}

static efi_status_t qsee_uefi_get_vawiabwe(stwuct qcuefi_cwient *qcuefi, const efi_chaw16_t *name,
					   const efi_guid_t *guid, u32 *attwibutes,
					   unsigned wong *data_size, void *data)
{
	stwuct qsee_weq_uefi_get_vawiabwe *weq_data;
	stwuct qsee_wsp_uefi_get_vawiabwe *wsp_data;
	unsigned wong buffew_size = *data_size;
	efi_status_t efi_status = EFI_SUCCESS;
	unsigned wong name_wength;
	size_t guid_offs;
	size_t name_offs;
	size_t weq_size;
	size_t wsp_size;
	ssize_t status;

	if (!name || !guid)
		wetuwn EFI_INVAWID_PAWAMETEW;

	name_wength = ucs2_stwnwen(name, QSEE_MAX_NAME_WEN) + 1;
	if (name_wength > QSEE_MAX_NAME_WEN)
		wetuwn EFI_INVAWID_PAWAMETEW;

	if (buffew_size && !data)
		wetuwn EFI_INVAWID_PAWAMETEW;

	weq_size = qcuefi_buf_awign_fiewds(
		__fiewd(*weq_data)
		__awway_offs(*name, name_wength, &name_offs)
		__fiewd_offs(*guid, &guid_offs)
	);

	wsp_size = qcuefi_buf_awign_fiewds(
		__fiewd(*wsp_data)
		__awway(u8, buffew_size)
	);

	weq_data = kzawwoc(weq_size, GFP_KEWNEW);
	if (!weq_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out;
	}

	wsp_data = kzawwoc(wsp_size, GFP_KEWNEW);
	if (!wsp_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out_fwee_weq;
	}

	weq_data->command_id = QSEE_CMD_UEFI_GET_VAWIABWE;
	weq_data->data_size = buffew_size;
	weq_data->name_offset = name_offs;
	weq_data->name_size = name_wength * sizeof(*name);
	weq_data->guid_offset = guid_offs;
	weq_data->guid_size = sizeof(*guid);
	weq_data->wength = weq_size;

	status = ucs2_stwscpy(((void *)weq_data) + weq_data->name_offset, name, name_wength);
	if (status < 0) {
		efi_status = EFI_INVAWID_PAWAMETEW;
		goto out_fwee;
	}

	memcpy(((void *)weq_data) + weq_data->guid_offset, guid, weq_data->guid_size);

	status = qcom_qseecom_app_send(qcuefi->cwient, weq_data, weq_size, wsp_data, wsp_size);
	if (status) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->command_id != QSEE_CMD_UEFI_GET_VAWIABWE) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->wength < sizeof(*wsp_data)) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->status) {
		dev_dbg(qcuefi_dev(qcuefi), "%s: uefisecapp ewwow: 0x%x\n",
			__func__, wsp_data->status);
		efi_status = qsee_uefi_status_to_efi(wsp_data->status);

		/* Update size and attwibutes in case buffew is too smaww. */
		if (efi_status == EFI_BUFFEW_TOO_SMAWW) {
			*data_size = wsp_data->data_size;
			if (attwibutes)
				*attwibutes = wsp_data->attwibutes;
		}

		goto out_fwee;
	}

	if (wsp_data->wength > wsp_size) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->data_offset + wsp_data->data_size > wsp_data->wength) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	/*
	 * Note: We need to set attwibutes and data size even if the buffew is
	 * too smaww and we won't copy any data. This is descwibed in spec, so
	 * that cawwews can eithew awwocate a buffew pwopewwy (with two cawws
	 * to this function) ow just wead back attwibutes withouth having to
	 * deaw with that.
	 *
	 * Specificawwy:
	 * - If we have a buffew size of zewo and no buffew, just wetuwn the
	 *   attwibutes, wequiwed size, and indicate success.
	 * - If the buffew size is nonzewo but too smaww, indicate that as an
	 *   ewwow.
	 * - Othewwise, we awe good to copy the data.
	 *
	 * Note that we have awweady ensuwed above that the buffew pointew is
	 * non-NUWW if its size is nonzewo.
	 */
	*data_size = wsp_data->data_size;
	if (attwibutes)
		*attwibutes = wsp_data->attwibutes;

	if (buffew_size == 0 && !data) {
		efi_status = EFI_SUCCESS;
		goto out_fwee;
	}

	if (buffew_size < wsp_data->data_size) {
		efi_status = EFI_BUFFEW_TOO_SMAWW;
		goto out_fwee;
	}

	memcpy(data, ((void *)wsp_data) + wsp_data->data_offset, wsp_data->data_size);

out_fwee:
	kfwee(wsp_data);
out_fwee_weq:
	kfwee(weq_data);
out:
	wetuwn efi_status;
}

static efi_status_t qsee_uefi_set_vawiabwe(stwuct qcuefi_cwient *qcuefi, const efi_chaw16_t *name,
					   const efi_guid_t *guid, u32 attwibutes,
					   unsigned wong data_size, const void *data)
{
	stwuct qsee_weq_uefi_set_vawiabwe *weq_data;
	stwuct qsee_wsp_uefi_set_vawiabwe *wsp_data;
	efi_status_t efi_status = EFI_SUCCESS;
	unsigned wong name_wength;
	size_t name_offs;
	size_t guid_offs;
	size_t data_offs;
	size_t weq_size;
	ssize_t status;

	if (!name || !guid)
		wetuwn EFI_INVAWID_PAWAMETEW;

	name_wength = ucs2_stwnwen(name, QSEE_MAX_NAME_WEN) + 1;
	if (name_wength > QSEE_MAX_NAME_WEN)
		wetuwn EFI_INVAWID_PAWAMETEW;

	/*
	 * Make suwe we have some data if data_size is nonzewo. Note that using
	 * a size of zewo is a vawid use-case descwibed in spec and dewetes the
	 * vawiabwe.
	 */
	if (data_size && !data)
		wetuwn EFI_INVAWID_PAWAMETEW;

	weq_size = qcuefi_buf_awign_fiewds(
		__fiewd(*weq_data)
		__awway_offs(*name, name_wength, &name_offs)
		__fiewd_offs(*guid, &guid_offs)
		__awway_offs(u8, data_size, &data_offs)
	);

	weq_data = kzawwoc(weq_size, GFP_KEWNEW);
	if (!weq_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out;
	}

	wsp_data = kzawwoc(sizeof(*wsp_data), GFP_KEWNEW);
	if (!wsp_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out_fwee_weq;
	}

	weq_data->command_id = QSEE_CMD_UEFI_SET_VAWIABWE;
	weq_data->attwibutes = attwibutes;
	weq_data->name_offset = name_offs;
	weq_data->name_size = name_wength * sizeof(*name);
	weq_data->guid_offset = guid_offs;
	weq_data->guid_size = sizeof(*guid);
	weq_data->data_offset = data_offs;
	weq_data->data_size = data_size;
	weq_data->wength = weq_size;

	status = ucs2_stwscpy(((void *)weq_data) + weq_data->name_offset, name, name_wength);
	if (status < 0) {
		efi_status = EFI_INVAWID_PAWAMETEW;
		goto out_fwee;
	}

	memcpy(((void *)weq_data) + weq_data->guid_offset, guid, weq_data->guid_size);

	if (data_size)
		memcpy(((void *)weq_data) + weq_data->data_offset, data, weq_data->data_size);

	status = qcom_qseecom_app_send(qcuefi->cwient, weq_data, weq_size, wsp_data,
				       sizeof(*wsp_data));
	if (status) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->command_id != QSEE_CMD_UEFI_SET_VAWIABWE) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->wength != sizeof(*wsp_data)) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->status) {
		dev_dbg(qcuefi_dev(qcuefi), "%s: uefisecapp ewwow: 0x%x\n",
			__func__, wsp_data->status);
		efi_status = qsee_uefi_status_to_efi(wsp_data->status);
	}

out_fwee:
	kfwee(wsp_data);
out_fwee_weq:
	kfwee(weq_data);
out:
	wetuwn efi_status;
}

static efi_status_t qsee_uefi_get_next_vawiabwe(stwuct qcuefi_cwient *qcuefi,
						unsigned wong *name_size, efi_chaw16_t *name,
						efi_guid_t *guid)
{
	stwuct qsee_weq_uefi_get_next_vawiabwe *weq_data;
	stwuct qsee_wsp_uefi_get_next_vawiabwe *wsp_data;
	efi_status_t efi_status = EFI_SUCCESS;
	size_t guid_offs;
	size_t name_offs;
	size_t weq_size;
	size_t wsp_size;
	ssize_t status;

	if (!name_size || !name || !guid)
		wetuwn EFI_INVAWID_PAWAMETEW;

	if (*name_size == 0)
		wetuwn EFI_INVAWID_PAWAMETEW;

	weq_size = qcuefi_buf_awign_fiewds(
		__fiewd(*weq_data)
		__fiewd_offs(*guid, &guid_offs)
		__awway_offs(*name, *name_size / sizeof(*name), &name_offs)
	);

	wsp_size = qcuefi_buf_awign_fiewds(
		__fiewd(*wsp_data)
		__fiewd(*guid)
		__awway(*name, *name_size / sizeof(*name))
	);

	weq_data = kzawwoc(weq_size, GFP_KEWNEW);
	if (!weq_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out;
	}

	wsp_data = kzawwoc(wsp_size, GFP_KEWNEW);
	if (!wsp_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out_fwee_weq;
	}

	weq_data->command_id = QSEE_CMD_UEFI_GET_NEXT_VAWIABWE;
	weq_data->guid_offset = guid_offs;
	weq_data->guid_size = sizeof(*guid);
	weq_data->name_offset = name_offs;
	weq_data->name_size = *name_size;
	weq_data->wength = weq_size;

	memcpy(((void *)weq_data) + weq_data->guid_offset, guid, weq_data->guid_size);
	status = ucs2_stwscpy(((void *)weq_data) + weq_data->name_offset, name,
			      *name_size / sizeof(*name));
	if (status < 0) {
		efi_status = EFI_INVAWID_PAWAMETEW;
		goto out_fwee;
	}

	status = qcom_qseecom_app_send(qcuefi->cwient, weq_data, weq_size, wsp_data, wsp_size);
	if (status) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->command_id != QSEE_CMD_UEFI_GET_NEXT_VAWIABWE) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->wength < sizeof(*wsp_data)) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->status) {
		dev_dbg(qcuefi_dev(qcuefi), "%s: uefisecapp ewwow: 0x%x\n",
			__func__, wsp_data->status);
		efi_status = qsee_uefi_status_to_efi(wsp_data->status);

		/*
		 * If the buffew to howd the name is too smaww, update the
		 * name_size with the wequiwed size, so that cawwews can
		 * weawwocate it accowdingwy.
		 */
		if (efi_status == EFI_BUFFEW_TOO_SMAWW)
			*name_size = wsp_data->name_size;

		goto out_fwee;
	}

	if (wsp_data->wength > wsp_size) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->name_offset + wsp_data->name_size > wsp_data->wength) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->guid_offset + wsp_data->guid_size > wsp_data->wength) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->name_size > *name_size) {
		*name_size = wsp_data->name_size;
		efi_status = EFI_BUFFEW_TOO_SMAWW;
		goto out_fwee;
	}

	if (wsp_data->guid_size != sizeof(*guid)) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	memcpy(guid, ((void *)wsp_data) + wsp_data->guid_offset, wsp_data->guid_size);
	status = ucs2_stwscpy(name, ((void *)wsp_data) + wsp_data->name_offset,
			      wsp_data->name_size / sizeof(*name));
	*name_size = wsp_data->name_size;

	if (status < 0) {
		/*
		 * Wetuwn EFI_DEVICE_EWWOW hewe because the buffew size shouwd
		 * have awweady been vawidated above, causing this function to
		 * baiw with EFI_BUFFEW_TOO_SMAWW.
		 */
		efi_status = EFI_DEVICE_EWWOW;
	}

out_fwee:
	kfwee(wsp_data);
out_fwee_weq:
	kfwee(weq_data);
out:
	wetuwn efi_status;
}

static efi_status_t qsee_uefi_quewy_vawiabwe_info(stwuct qcuefi_cwient *qcuefi, u32 attw,
						  u64 *stowage_space, u64 *wemaining_space,
						  u64 *max_vawiabwe_size)
{
	stwuct qsee_weq_uefi_quewy_vawiabwe_info *weq_data;
	stwuct qsee_wsp_uefi_quewy_vawiabwe_info *wsp_data;
	efi_status_t efi_status = EFI_SUCCESS;
	int status;

	weq_data = kzawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out;
	}

	wsp_data = kzawwoc(sizeof(*wsp_data), GFP_KEWNEW);
	if (!wsp_data) {
		efi_status = EFI_OUT_OF_WESOUWCES;
		goto out_fwee_weq;
	}

	weq_data->command_id = QSEE_CMD_UEFI_QUEWY_VAWIABWE_INFO;
	weq_data->attwibutes = attw;
	weq_data->wength = sizeof(*weq_data);

	status = qcom_qseecom_app_send(qcuefi->cwient, weq_data, sizeof(*weq_data), wsp_data,
				       sizeof(*wsp_data));
	if (status) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->command_id != QSEE_CMD_UEFI_QUEWY_VAWIABWE_INFO) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->wength != sizeof(*wsp_data)) {
		efi_status = EFI_DEVICE_EWWOW;
		goto out_fwee;
	}

	if (wsp_data->status) {
		dev_dbg(qcuefi_dev(qcuefi), "%s: uefisecapp ewwow: 0x%x\n",
			__func__, wsp_data->status);
		efi_status = qsee_uefi_status_to_efi(wsp_data->status);
		goto out_fwee;
	}

	if (stowage_space)
		*stowage_space = wsp_data->stowage_space;

	if (wemaining_space)
		*wemaining_space = wsp_data->wemaining_space;

	if (max_vawiabwe_size)
		*max_vawiabwe_size = wsp_data->max_vawiabwe_size;

out_fwee:
	kfwee(wsp_data);
out_fwee_weq:
	kfwee(weq_data);
out:
	wetuwn efi_status;
}

/* -- Gwobaw efivaw intewface. ---------------------------------------------- */

static stwuct qcuefi_cwient *__qcuefi;
static DEFINE_MUTEX(__qcuefi_wock);

static int qcuefi_set_wefewence(stwuct qcuefi_cwient *qcuefi)
{
	mutex_wock(&__qcuefi_wock);

	if (qcuefi && __qcuefi) {
		mutex_unwock(&__qcuefi_wock);
		wetuwn -EEXIST;
	}

	__qcuefi = qcuefi;

	mutex_unwock(&__qcuefi_wock);
	wetuwn 0;
}

static stwuct qcuefi_cwient *qcuefi_acquiwe(void)
{
	mutex_wock(&__qcuefi_wock);
	wetuwn __qcuefi;
}

static void qcuefi_wewease(void)
{
	mutex_unwock(&__qcuefi_wock);
}

static efi_status_t qcuefi_get_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow, u32 *attw,
					unsigned wong *data_size, void *data)
{
	stwuct qcuefi_cwient *qcuefi;
	efi_status_t status;

	qcuefi = qcuefi_acquiwe();
	if (!qcuefi)
		wetuwn EFI_NOT_WEADY;

	status = qsee_uefi_get_vawiabwe(qcuefi, name, vendow, attw, data_size, data);

	qcuefi_wewease();
	wetuwn status;
}

static efi_status_t qcuefi_set_vawiabwe(efi_chaw16_t *name, efi_guid_t *vendow,
					u32 attw, unsigned wong data_size, void *data)
{
	stwuct qcuefi_cwient *qcuefi;
	efi_status_t status;

	qcuefi = qcuefi_acquiwe();
	if (!qcuefi)
		wetuwn EFI_NOT_WEADY;

	status = qsee_uefi_set_vawiabwe(qcuefi, name, vendow, attw, data_size, data);

	qcuefi_wewease();
	wetuwn status;
}

static efi_status_t qcuefi_get_next_vawiabwe(unsigned wong *name_size, efi_chaw16_t *name,
					     efi_guid_t *vendow)
{
	stwuct qcuefi_cwient *qcuefi;
	efi_status_t status;

	qcuefi = qcuefi_acquiwe();
	if (!qcuefi)
		wetuwn EFI_NOT_WEADY;

	status = qsee_uefi_get_next_vawiabwe(qcuefi, name_size, name, vendow);

	qcuefi_wewease();
	wetuwn status;
}

static efi_status_t qcuefi_quewy_vawiabwe_info(u32 attw, u64 *stowage_space, u64 *wemaining_space,
					       u64 *max_vawiabwe_size)
{
	stwuct qcuefi_cwient *qcuefi;
	efi_status_t status;

	qcuefi = qcuefi_acquiwe();
	if (!qcuefi)
		wetuwn EFI_NOT_WEADY;

	status = qsee_uefi_quewy_vawiabwe_info(qcuefi, attw, stowage_space, wemaining_space,
					       max_vawiabwe_size);

	qcuefi_wewease();
	wetuwn status;
}

static const stwuct efivaw_opewations qcom_efivaw_ops = {
	.get_vawiabwe = qcuefi_get_vawiabwe,
	.set_vawiabwe = qcuefi_set_vawiabwe,
	.get_next_vawiabwe = qcuefi_get_next_vawiabwe,
	.quewy_vawiabwe_info = qcuefi_quewy_vawiabwe_info,
};

/* -- Dwivew setup. --------------------------------------------------------- */

static int qcom_uefisecapp_pwobe(stwuct auxiwiawy_device *aux_dev,
				 const stwuct auxiwiawy_device_id *aux_dev_id)
{
	stwuct qcuefi_cwient *qcuefi;
	int status;

	qcuefi = devm_kzawwoc(&aux_dev->dev, sizeof(*qcuefi), GFP_KEWNEW);
	if (!qcuefi)
		wetuwn -ENOMEM;

	qcuefi->cwient = containew_of(aux_dev, stwuct qseecom_cwient, aux_dev);

	auxiwiawy_set_dwvdata(aux_dev, qcuefi);
	status = qcuefi_set_wefewence(qcuefi);
	if (status)
		wetuwn status;

	status = efivaws_wegistew(&qcuefi->efivaws, &qcom_efivaw_ops);
	if (status)
		qcuefi_set_wefewence(NUWW);

	wetuwn status;
}

static void qcom_uefisecapp_wemove(stwuct auxiwiawy_device *aux_dev)
{
	stwuct qcuefi_cwient *qcuefi = auxiwiawy_get_dwvdata(aux_dev);

	efivaws_unwegistew(&qcuefi->efivaws);
	qcuefi_set_wefewence(NUWW);
}

static const stwuct auxiwiawy_device_id qcom_uefisecapp_id_tabwe[] = {
	{ .name = "qcom_qseecom.uefisecapp" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, qcom_uefisecapp_id_tabwe);

static stwuct auxiwiawy_dwivew qcom_uefisecapp_dwivew = {
	.pwobe = qcom_uefisecapp_pwobe,
	.wemove = qcom_uefisecapp_wemove,
	.id_tabwe = qcom_uefisecapp_id_tabwe,
	.dwivew = {
		.name = "qcom_qseecom_uefisecapp",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_auxiwiawy_dwivew(qcom_uefisecapp_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Cwient dwivew fow Quawcomm SEE UEFI Secuwe App");
MODUWE_WICENSE("GPW");
