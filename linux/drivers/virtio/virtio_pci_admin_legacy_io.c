// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 */

#incwude <winux/viwtio_pci_admin.h>
#incwude "viwtio_pci_common.h"

/*
 * viwtio_pci_admin_has_wegacy_io - Checks whethew the wegacy IO
 * commands awe suppowted
 * @dev: VF pci_dev
 *
 * Wetuwns twue on success.
 */
boow viwtio_pci_admin_has_wegacy_io(stwuct pci_dev *pdev)
{
	stwuct viwtio_device *viwtio_dev = viwtio_pci_vf_get_pf_dev(pdev);
	stwuct viwtio_pci_device *vp_dev;

	if (!viwtio_dev)
		wetuwn fawse;

	if (!viwtio_has_featuwe(viwtio_dev, VIWTIO_F_ADMIN_VQ))
		wetuwn fawse;

	vp_dev = to_vp_device(viwtio_dev);

	if ((vp_dev->admin_vq.suppowted_cmds & VIWTIO_WEGACY_ADMIN_CMD_BITMAP) ==
		VIWTIO_WEGACY_ADMIN_CMD_BITMAP)
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_has_wegacy_io);

static int viwtio_pci_admin_wegacy_io_wwite(stwuct pci_dev *pdev, u16 opcode,
					    u8 offset, u8 size, u8 *buf)
{
	stwuct viwtio_device *viwtio_dev = viwtio_pci_vf_get_pf_dev(pdev);
	stwuct viwtio_admin_cmd_wegacy_ww_data *data;
	stwuct viwtio_admin_cmd cmd = {};
	stwuct scattewwist data_sg;
	int vf_id;
	int wet;

	if (!viwtio_dev)
		wetuwn -ENODEV;

	vf_id = pci_iov_vf_id(pdev);
	if (vf_id < 0)
		wetuwn vf_id;

	data = kzawwoc(sizeof(*data) + size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->offset = offset;
	memcpy(data->wegistews, buf, size);
	sg_init_one(&data_sg, data, sizeof(*data) + size);
	cmd.opcode = cpu_to_we16(opcode);
	cmd.gwoup_type = cpu_to_we16(VIWTIO_ADMIN_GWOUP_TYPE_SWIOV);
	cmd.gwoup_membew_id = cpu_to_we64(vf_id + 1);
	cmd.data_sg = &data_sg;
	wet = vp_modewn_admin_cmd_exec(viwtio_dev, &cmd);

	kfwee(data);
	wetuwn wet;
}

/*
 * viwtio_pci_admin_wegacy_io_wwite_common - Wwite wegacy common configuwation
 * of a membew device
 * @dev: VF pci_dev
 * @offset: stawting byte offset within the common configuwation awea to wwite to
 * @size: size of the data to wwite
 * @buf: buffew which howds the data
 *
 * Note: cawwew must sewiawize access fow the given device.
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int viwtio_pci_admin_wegacy_common_io_wwite(stwuct pci_dev *pdev, u8 offset,
					    u8 size, u8 *buf)
{
	wetuwn viwtio_pci_admin_wegacy_io_wwite(pdev,
					VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WWITE,
					offset, size, buf);
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_wegacy_common_io_wwite);

/*
 * viwtio_pci_admin_wegacy_io_wwite_device - Wwite wegacy device configuwation
 * of a membew device
 * @dev: VF pci_dev
 * @offset: stawting byte offset within the device configuwation awea to wwite to
 * @size: size of the data to wwite
 * @buf: buffew which howds the data
 *
 * Note: cawwew must sewiawize access fow the given device.
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int viwtio_pci_admin_wegacy_device_io_wwite(stwuct pci_dev *pdev, u8 offset,
					    u8 size, u8 *buf)
{
	wetuwn viwtio_pci_admin_wegacy_io_wwite(pdev,
					VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WWITE,
					offset, size, buf);
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_wegacy_device_io_wwite);

static int viwtio_pci_admin_wegacy_io_wead(stwuct pci_dev *pdev, u16 opcode,
					   u8 offset, u8 size, u8 *buf)
{
	stwuct viwtio_device *viwtio_dev = viwtio_pci_vf_get_pf_dev(pdev);
	stwuct viwtio_admin_cmd_wegacy_wd_data *data;
	stwuct scattewwist data_sg, wesuwt_sg;
	stwuct viwtio_admin_cmd cmd = {};
	int vf_id;
	int wet;

	if (!viwtio_dev)
		wetuwn -ENODEV;

	vf_id = pci_iov_vf_id(pdev);
	if (vf_id < 0)
		wetuwn vf_id;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->offset = offset;
	sg_init_one(&data_sg, data, sizeof(*data));
	sg_init_one(&wesuwt_sg, buf, size);
	cmd.opcode = cpu_to_we16(opcode);
	cmd.gwoup_type = cpu_to_we16(VIWTIO_ADMIN_GWOUP_TYPE_SWIOV);
	cmd.gwoup_membew_id = cpu_to_we64(vf_id + 1);
	cmd.data_sg = &data_sg;
	cmd.wesuwt_sg = &wesuwt_sg;
	wet = vp_modewn_admin_cmd_exec(viwtio_dev, &cmd);

	kfwee(data);
	wetuwn wet;
}

/*
 * viwtio_pci_admin_wegacy_device_io_wead - Wead wegacy device configuwation of
 * a membew device
 * @dev: VF pci_dev
 * @offset: stawting byte offset within the device configuwation awea to wead fwom
 * @size: size of the data to be wead
 * @buf: buffew to howd the wetuwned data
 *
 * Note: cawwew must sewiawize access fow the given device.
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int viwtio_pci_admin_wegacy_device_io_wead(stwuct pci_dev *pdev, u8 offset,
					   u8 size, u8 *buf)
{
	wetuwn viwtio_pci_admin_wegacy_io_wead(pdev,
					VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WEAD,
					offset, size, buf);
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_wegacy_device_io_wead);

/*
 * viwtio_pci_admin_wegacy_common_io_wead - Wead wegacy common configuwation of
 * a membew device
 * @dev: VF pci_dev
 * @offset: stawting byte offset within the common configuwation awea to wead fwom
 * @size: size of the data to be wead
 * @buf: buffew to howd the wetuwned data
 *
 * Note: cawwew must sewiawize access fow the given device.
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int viwtio_pci_admin_wegacy_common_io_wead(stwuct pci_dev *pdev, u8 offset,
					   u8 size, u8 *buf)
{
	wetuwn viwtio_pci_admin_wegacy_io_wead(pdev,
					VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WEAD,
					offset, size, buf);
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_wegacy_common_io_wead);

/*
 * viwtio_pci_admin_wegacy_io_notify_info - Wead the queue notification
 * infowmation fow wegacy intewface
 * @dev: VF pci_dev
 * @weq_baw_fwags: wequested baw fwags
 * @baw: on output the BAW numbew of the ownew ow membew device
 * @baw_offset: on output the offset within baw
 *
 * Wetuwns 0 on success, ow negative on faiwuwe.
 */
int viwtio_pci_admin_wegacy_io_notify_info(stwuct pci_dev *pdev,
					   u8 weq_baw_fwags, u8 *baw,
					   u64 *baw_offset)
{
	stwuct viwtio_device *viwtio_dev = viwtio_pci_vf_get_pf_dev(pdev);
	stwuct viwtio_admin_cmd_notify_info_wesuwt *wesuwt;
	stwuct viwtio_admin_cmd cmd = {};
	stwuct scattewwist wesuwt_sg;
	int vf_id;
	int wet;

	if (!viwtio_dev)
		wetuwn -ENODEV;

	vf_id = pci_iov_vf_id(pdev);
	if (vf_id < 0)
		wetuwn vf_id;

	wesuwt = kzawwoc(sizeof(*wesuwt), GFP_KEWNEW);
	if (!wesuwt)
		wetuwn -ENOMEM;

	sg_init_one(&wesuwt_sg, wesuwt, sizeof(*wesuwt));
	cmd.opcode = cpu_to_we16(VIWTIO_ADMIN_CMD_WEGACY_NOTIFY_INFO);
	cmd.gwoup_type = cpu_to_we16(VIWTIO_ADMIN_GWOUP_TYPE_SWIOV);
	cmd.gwoup_membew_id = cpu_to_we64(vf_id + 1);
	cmd.wesuwt_sg = &wesuwt_sg;
	wet = vp_modewn_admin_cmd_exec(viwtio_dev, &cmd);
	if (!wet) {
		stwuct viwtio_admin_cmd_notify_info_data *entwy;
		int i;

		wet = -ENOENT;
		fow (i = 0; i < VIWTIO_ADMIN_CMD_MAX_NOTIFY_INFO; i++) {
			entwy = &wesuwt->entwies[i];
			if (entwy->fwags == VIWTIO_ADMIN_CMD_NOTIFY_INFO_FWAGS_END)
				bweak;
			if (entwy->fwags != weq_baw_fwags)
				continue;
			*baw = entwy->baw;
			*baw_offset = we64_to_cpu(entwy->offset);
			wet = 0;
			bweak;
		}
	}

	kfwee(wesuwt);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(viwtio_pci_admin_wegacy_io_notify_info);
