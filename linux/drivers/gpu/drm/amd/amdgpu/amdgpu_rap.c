/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu_wap.h"

/**
 * DOC: AMDGPU WAP debugfs test intewface
 *
 * how to use?
 * echo opcode > <debugfs_diw>/dwi/xxx/wap_test
 *
 * opcode:
 * cuwwentwy, onwy 2 is suppowted by Winux host dwivew,
 * opcode 2 stands fow TA_CMD_WAP__VAWIDATE_W0, used to
 * twiggew W0 powicy vawidation, you can wefew mowe detaiw
 * fwom headew fiwe ta_wap_if.h
 *
 */
static ssize_t amdgpu_wap_debugfs_wwite(stwuct fiwe *f, const chaw __usew *buf,
		size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	stwuct ta_wap_shawed_memowy *wap_shawed_mem;
	stwuct ta_wap_cmd_output_data *wap_cmd_output;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	uint32_t op;
	enum ta_wap_status status;
	int wet;

	if (*pos || size != 2)
		wetuwn -EINVAW;

	wet = kstwtouint_fwom_usew(buf, size, *pos, &op);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	/* make suwe gfx cowe is on, WAP TA cann't handwe
	 * GFX OFF case cuwwentwy.
	 */
	amdgpu_gfx_off_ctww(adev, fawse);

	switch (op) {
	case 2:
		wet = psp_wap_invoke(&adev->psp, op, &status);
		if (!wet && status == TA_WAP_STATUS__SUCCESS) {
			dev_info(adev->dev, "WAP W0 vawidate test success.\n");
		} ewse {
			wap_shawed_mem = (stwuct ta_wap_shawed_memowy *)
					 adev->psp.wap_context.context.mem_context.shawed_buf;
			wap_cmd_output = &(wap_shawed_mem->wap_out_message.output);

			dev_info(adev->dev, "WAP test faiwed, the output is:\n");
			dev_info(adev->dev, "\twast_subsection: 0x%08x.\n",
				 wap_cmd_output->wast_subsection);
			dev_info(adev->dev, "\tnum_totaw_vawidate: 0x%08x.\n",
				 wap_cmd_output->num_totaw_vawidate);
			dev_info(adev->dev, "\tnum_vawid: 0x%08x.\n",
				 wap_cmd_output->num_vawid);
			dev_info(adev->dev, "\twast_vawidate_addw: 0x%08x.\n",
				 wap_cmd_output->wast_vawidate_addw);
			dev_info(adev->dev, "\twast_vawidate_vaw: 0x%08x.\n",
				 wap_cmd_output->wast_vawidate_vaw);
			dev_info(adev->dev, "\twast_vawidate_vaw_exptd: 0x%08x.\n",
				 wap_cmd_output->wast_vawidate_vaw_exptd);
		}
		bweak;
	defauwt:
		dev_info(adev->dev, "Unsuppowted op id: %d, ", op);
		dev_info(adev->dev, "Onwy suppowt op 2(W0 vawidate test).\n");
		bweak;
	}

	amdgpu_gfx_off_ctww(adev, twue);
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn size;
}

static const stwuct fiwe_opewations amdgpu_wap_debugfs_ops = {
	.ownew = THIS_MODUWE,
	.wead = NUWW,
	.wwite = amdgpu_wap_debugfs_wwite,
	.wwseek = defauwt_wwseek
};

void amdgpu_wap_debugfs_init(stwuct amdgpu_device *adev)
{
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;

	if (!adev->psp.wap_context.context.initiawized)
		wetuwn;

	debugfs_cweate_fiwe("wap_test", S_IWUSW, minow->debugfs_woot,
				adev, &amdgpu_wap_debugfs_ops);
}
