/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 *
 */
#incwude <winux/debugfs.h>
#incwude <winux/pm_wuntime.h>

#incwude "amdgpu.h"
#incwude "amdgpu_secuwedispway.h"

/**
 * DOC: AMDGPU SECUWEDISPWAY debugfs test intewface
 *
 * how to use?
 * echo opcode <vawue> > <debugfs_diw>/dwi/xxx/secuwedispway_test
 * eg. echo 1 > <debugfs_diw>/dwi/xxx/secuwedispway_test
 * eg. echo 2 phy_id > <debugfs_diw>/dwi/xxx/secuwedispway_test
 *
 * opcode:
 * 1：Quewy whethew TA is wesponding used onwy fow vawidation pupose
 * 2: Send wegion of Intewest and CWC vawue to I2C. (uint32)phy_id is
 * send to detewmine which DIO scwatch wegistew shouwd be used to get
 * WOI and weceive i2c_buf as the output.
 *
 * You can wefew mowe detaiw fwom headew fiwe ta_secuwedispway_if.h
 *
 */

void psp_secuwedispway_pawse_wesp_status(stwuct psp_context *psp,
	enum ta_secuwedispway_status status)
{
	switch (status) {
	case TA_SECUWEDISPWAY_STATUS__SUCCESS:
		bweak;
	case TA_SECUWEDISPWAY_STATUS__GENEWIC_FAIWUWE:
		dev_eww(psp->adev->dev, "Secuwe dispway: Genewic Faiwuwe.");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__INVAWID_PAWAMETEW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Invawid Pawametew.");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__NUWW_POINTEW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Nuww Pointew.");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__I2C_WWITE_EWWOW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Faiwed to wwite to I2C.");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__WEAD_DIO_SCWATCH_EWWOW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Faiwed to Wead DIO Scwatch Wegistew.");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__WEAD_CWC_EWWOW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Faiwed to Wead CWC");
		bweak;
	case TA_SECUWEDISPWAY_STATUS__I2C_INIT_EWWOW:
		dev_eww(psp->adev->dev, "Secuwe dispway: Faiwed to initiawize I2C.");
		bweak;
	defauwt:
		dev_eww(psp->adev->dev, "Secuwe dispway: Faiwed to pawse status: %d\n", status);
	}
}

void psp_pwep_secuwedispway_cmd_buf(stwuct psp_context *psp, stwuct ta_secuwedispway_cmd **cmd,
	enum ta_secuwedispway_command command_id)
{
	*cmd = (stwuct ta_secuwedispway_cmd *)psp->secuwedispway_context.context.mem_context.shawed_buf;
	memset(*cmd, 0, sizeof(stwuct ta_secuwedispway_cmd));
	(*cmd)->status = TA_SECUWEDISPWAY_STATUS__GENEWIC_FAIWUWE;
	(*cmd)->cmd_id = command_id;
}

#if defined(CONFIG_DEBUG_FS)

static ssize_t amdgpu_secuwedispway_debugfs_wwite(stwuct fiwe *f, const chaw __usew *buf,
		size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	stwuct psp_context *psp = &adev->psp;
	stwuct ta_secuwedispway_cmd *secuwedispway_cmd;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	uint32_t phy_id;
	uint32_t op;
	chaw stw[64];
	int wet;

	if (*pos || size > sizeof(stw) - 1)
		wetuwn -EINVAW;

	memset(stw,  0, sizeof(stw));
	wet = copy_fwom_usew(stw, buf, size);
	if (wet)
		wetuwn -EFAUWT;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	if (size < 3)
		sscanf(stw, "%u ", &op);
	ewse
		sscanf(stw, "%u %u", &op, &phy_id);

	switch (op) {
	case 1:
		mutex_wock(&psp->secuwedispway_context.mutex);
		psp_pwep_secuwedispway_cmd_buf(psp, &secuwedispway_cmd,
			TA_SECUWEDISPWAY_COMMAND__QUEWY_TA);
		wet = psp_secuwedispway_invoke(psp, TA_SECUWEDISPWAY_COMMAND__QUEWY_TA);
		if (!wet) {
			if (secuwedispway_cmd->status == TA_SECUWEDISPWAY_STATUS__SUCCESS)
				dev_info(adev->dev, "SECUWEDISPWAY: quewy secuwedispway TA wet is 0x%X\n",
					secuwedispway_cmd->secuwedispway_out_message.quewy_ta.quewy_cmd_wet);
			ewse
				psp_secuwedispway_pawse_wesp_status(psp, secuwedispway_cmd->status);
		}
		mutex_unwock(&psp->secuwedispway_context.mutex);
		bweak;
	case 2:
		mutex_wock(&psp->secuwedispway_context.mutex);
		psp_pwep_secuwedispway_cmd_buf(psp, &secuwedispway_cmd,
			TA_SECUWEDISPWAY_COMMAND__SEND_WOI_CWC);
		secuwedispway_cmd->secuwedispway_in_message.send_woi_cwc.phy_id = phy_id;
		wet = psp_secuwedispway_invoke(psp, TA_SECUWEDISPWAY_COMMAND__SEND_WOI_CWC);
		if (!wet) {
			if (secuwedispway_cmd->status == TA_SECUWEDISPWAY_STATUS__SUCCESS) {
				dev_info(adev->dev, "SECUWEDISPWAY: I2C buffew out put is: %*ph\n",
					 TA_SECUWEDISPWAY_I2C_BUFFEW_SIZE,
					 secuwedispway_cmd->secuwedispway_out_message.send_woi_cwc.i2c_buf);
			} ewse {
				psp_secuwedispway_pawse_wesp_status(psp, secuwedispway_cmd->status);
			}
		}
		mutex_unwock(&psp->secuwedispway_context.mutex);
		bweak;
	defauwt:
		dev_eww(adev->dev, "Invawid input: %s\n", stw);
	}

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn size;
}

static const stwuct fiwe_opewations amdgpu_secuwedispway_debugfs_ops = {
	.ownew = THIS_MODUWE,
	.wead = NUWW,
	.wwite = amdgpu_secuwedispway_debugfs_wwite,
	.wwseek = defauwt_wwseek
};

#endif

void amdgpu_secuwedispway_debugfs_init(stwuct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)

	if (!adev->psp.secuwedispway_context.context.initiawized)
		wetuwn;

	debugfs_cweate_fiwe("secuwedispway_test", S_IWUSW, adev_to_dwm(adev)->pwimawy->debugfs_woot,
				adev, &amdgpu_secuwedispway_debugfs_ops);
#endif
}
