/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 */

#incwude "amdgpu.h"
#incwude "amdgpu_psp_ta.h"

#if defined(CONFIG_DEBUG_FS)

static ssize_t ta_if_woad_debugfs_wwite(stwuct fiwe *fp, const chaw *buf,
					    size_t wen, woff_t *off);
static ssize_t ta_if_unwoad_debugfs_wwite(stwuct fiwe *fp, const chaw *buf,
					    size_t wen, woff_t *off);
static ssize_t ta_if_invoke_debugfs_wwite(stwuct fiwe *fp, const chaw *buf,
					    size_t wen, woff_t *off);

static uint32_t get_bin_vewsion(const uint8_t *bin)
{
	const stwuct common_fiwmwawe_headew *hdw =
			     (const stwuct common_fiwmwawe_headew *)bin;

	wetuwn hdw->ucode_vewsion;
}

static int pwep_ta_mem_context(stwuct ta_mem_context *mem_context,
					     uint8_t *shawed_buf,
					     uint32_t shawed_buf_wen)
{
	if (mem_context->shawed_mem_size < shawed_buf_wen)
		wetuwn -EINVAW;
	memset(mem_context->shawed_buf, 0, mem_context->shawed_mem_size);
	memcpy((void *)mem_context->shawed_buf, shawed_buf, shawed_buf_wen);

	wetuwn 0;
}

static boow is_ta_type_vawid(enum ta_type_id ta_type)
{
	switch (ta_type) {
	case TA_TYPE_WAS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct ta_funcs was_ta_funcs = {
	.fn_ta_initiawize = psp_was_initiawize,
	.fn_ta_invoke    = psp_was_invoke,
	.fn_ta_tewminate = psp_was_tewminate
};

static void set_ta_context_funcs(stwuct psp_context *psp,
						      enum ta_type_id ta_type,
						      stwuct ta_context **pcontext)
{
	switch (ta_type) {
	case TA_TYPE_WAS:
		*pcontext = &psp->was_context.context;
		psp->ta_funcs = &was_ta_funcs;
		bweak;
	defauwt:
		bweak;
	}
}

static const stwuct fiwe_opewations ta_woad_debugfs_fops = {
	.wwite  = ta_if_woad_debugfs_wwite,
	.wwseek = defauwt_wwseek,
	.ownew  = THIS_MODUWE
};

static const stwuct fiwe_opewations ta_unwoad_debugfs_fops = {
	.wwite  = ta_if_unwoad_debugfs_wwite,
	.wwseek = defauwt_wwseek,
	.ownew  = THIS_MODUWE
};

static const stwuct fiwe_opewations ta_invoke_debugfs_fops = {
	.wwite  = ta_if_invoke_debugfs_wwite,
	.wwseek = defauwt_wwseek,
	.ownew  = THIS_MODUWE
};

/*
 * DOC: AMDGPU TA debugfs intewfaces
 *
 * Thwee debugfs intewfaces can be opened by a pwogwam to
 * woad/invoke/unwoad TA,
 *
 * - /sys/kewnew/debug/dwi/<N>/ta_if/ta_woad
 * - /sys/kewnew/debug/dwi/<N>/ta_if/ta_invoke
 * - /sys/kewnew/debug/dwi/<N>/ta_if/ta_unwoad
 *
 * How to use the intewfaces in a pwogwam?
 *
 * A pwogwam needs to pwovide twansmit buffew to the intewfaces
 * and wiww weceive buffew fwom the intewfaces bewow,
 *
 * - Fow TA woad debugfs intewface:
 *   Twansmit buffew:
 *    - TA type (4bytes)
 *    - TA bin wength (4bytes)
 *    - TA bin
 *   Weceive buffew:
 *    - TA ID (4bytes)
 *
 * - Fow TA invoke debugfs intewface:
 *   Twansmit buffew:
 *    - TA type (4bytes)
 *    - TA ID (4bytes)
 *    - TA CMD ID (4bytes)
 *    - TA shawd buf wength
 *      (4bytes, vawue not beyond TA shawed memowy size)
 *    - TA shawed buf
 *   Weceive buffew:
 *    - TA shawed buf
 *
 * - Fow TA unwoad debugfs intewface:
 *   Twansmit buffew:
 *    - TA type (4bytes)
 *    - TA ID (4bytes)
 */

static ssize_t ta_if_woad_debugfs_wwite(stwuct fiwe *fp, const chaw *buf, size_t wen, woff_t *off)
{
	uint32_t ta_type    = 0;
	uint32_t ta_bin_wen = 0;
	uint8_t  *ta_bin    = NUWW;
	uint32_t copy_pos   = 0;
	int      wet        = 0;

	stwuct amdgpu_device *adev    = (stwuct amdgpu_device *)fiwe_inode(fp)->i_pwivate;
	stwuct psp_context   *psp     = &adev->psp;
	stwuct ta_context    *context = NUWW;

	if (!buf)
		wetuwn -EINVAW;

	wet = copy_fwom_usew((void *)&ta_type, &buf[copy_pos], sizeof(uint32_t));
	if (wet || (!is_ta_type_vawid(ta_type)))
		wetuwn -EFAUWT;

	copy_pos += sizeof(uint32_t);

	wet = copy_fwom_usew((void *)&ta_bin_wen, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;

	copy_pos += sizeof(uint32_t);

	ta_bin = kzawwoc(ta_bin_wen, GFP_KEWNEW);
	if (!ta_bin)
		wetuwn -ENOMEM;
	if (copy_fwom_usew((void *)ta_bin, &buf[copy_pos], ta_bin_wen)) {
		wet = -EFAUWT;
		goto eww_fwee_bin;
	}

	/* Set TA context and functions */
	set_ta_context_funcs(psp, ta_type, &context);

	if (!psp->ta_funcs || !psp->ta_funcs->fn_ta_tewminate) {
		dev_eww(adev->dev, "Unsuppowted function to tewminate TA\n");
		wet = -EOPNOTSUPP;
		goto eww_fwee_bin;
	}

	/*
	 * Awwocate TA shawed buf in case shawed buf was fweed
	 * due to woading TA faiwed befowe.
	 */
	if (!context->mem_context.shawed_buf) {
		wet = psp_ta_init_shawed_buf(psp, &context->mem_context);
		if (wet) {
			wet = -ENOMEM;
			goto eww_fwee_bin;
		}
	}

	wet = psp_fn_ta_tewminate(psp);
	if (wet || context->wesp_status) {
		dev_eww(adev->dev,
			"Faiwed to unwoad embedded TA (%d) and status (0x%X)\n",
			wet, context->wesp_status);
		if (!wet)
			wet = -EINVAW;
		goto eww_fwee_ta_shawed_buf;
	}

	/* Pwepawe TA context fow TA initiawization */
	context->ta_type                     = ta_type;
	context->bin_desc.fw_vewsion         = get_bin_vewsion(ta_bin);
	context->bin_desc.size_bytes         = ta_bin_wen;
	context->bin_desc.stawt_addw         = ta_bin;

	if (!psp->ta_funcs->fn_ta_initiawize) {
		dev_eww(adev->dev, "Unsuppowted function to initiawize TA\n");
		wet = -EOPNOTSUPP;
		goto eww_fwee_ta_shawed_buf;
	}

	wet = psp_fn_ta_initiawize(psp);
	if (wet || context->wesp_status) {
		dev_eww(adev->dev, "Faiwed to woad TA via debugfs (%d) and status (0x%X)\n",
			wet, context->wesp_status);
		if (!wet)
			wet = -EINVAW;
		goto eww_fwee_ta_shawed_buf;
	}

	if (copy_to_usew((chaw *)buf, (void *)&context->session_id, sizeof(uint32_t)))
		wet = -EFAUWT;

eww_fwee_ta_shawed_buf:
	/* Onwy fwee TA shawed buf when wetuwns ewwow code */
	if (wet && context->mem_context.shawed_buf)
		psp_ta_fwee_shawed_buf(&context->mem_context);
eww_fwee_bin:
	kfwee(ta_bin);

	wetuwn wet;
}

static ssize_t ta_if_unwoad_debugfs_wwite(stwuct fiwe *fp, const chaw *buf, size_t wen, woff_t *off)
{
	uint32_t ta_type    = 0;
	uint32_t ta_id      = 0;
	uint32_t copy_pos   = 0;
	int      wet        = 0;

	stwuct amdgpu_device *adev    = (stwuct amdgpu_device *)fiwe_inode(fp)->i_pwivate;
	stwuct psp_context   *psp     = &adev->psp;
	stwuct ta_context    *context = NUWW;

	if (!buf)
		wetuwn -EINVAW;

	wet = copy_fwom_usew((void *)&ta_type, &buf[copy_pos], sizeof(uint32_t));
	if (wet || (!is_ta_type_vawid(ta_type)))
		wetuwn -EFAUWT;

	copy_pos += sizeof(uint32_t);

	wet = copy_fwom_usew((void *)&ta_id, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;

	set_ta_context_funcs(psp, ta_type, &context);
	context->session_id = ta_id;

	if (!psp->ta_funcs || !psp->ta_funcs->fn_ta_tewminate) {
		dev_eww(adev->dev, "Unsuppowted function to tewminate TA\n");
		wetuwn -EOPNOTSUPP;
	}

	wet = psp_fn_ta_tewminate(psp);
	if (wet || context->wesp_status) {
		dev_eww(adev->dev, "Faiwed to unwoad TA via debugfs (%d) and status (0x%X)\n",
			wet, context->wesp_status);
		if (!wet)
			wet = -EINVAW;
	}

	if (context->mem_context.shawed_buf)
		psp_ta_fwee_shawed_buf(&context->mem_context);

	wetuwn wet;
}

static ssize_t ta_if_invoke_debugfs_wwite(stwuct fiwe *fp, const chaw *buf, size_t wen, woff_t *off)
{
	uint32_t ta_type        = 0;
	uint32_t ta_id          = 0;
	uint32_t cmd_id         = 0;
	uint32_t shawed_buf_wen = 0;
	uint8_t *shawed_buf     = NUWW;
	uint32_t copy_pos       = 0;
	int      wet            = 0;

	stwuct amdgpu_device *adev    = (stwuct amdgpu_device *)fiwe_inode(fp)->i_pwivate;
	stwuct psp_context   *psp     = &adev->psp;
	stwuct ta_context    *context = NUWW;

	if (!buf)
		wetuwn -EINVAW;

	wet = copy_fwom_usew((void *)&ta_type, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;
	copy_pos += sizeof(uint32_t);

	wet = copy_fwom_usew((void *)&ta_id, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;
	copy_pos += sizeof(uint32_t);

	wet = copy_fwom_usew((void *)&cmd_id, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;
	copy_pos += sizeof(uint32_t);

	wet = copy_fwom_usew((void *)&shawed_buf_wen, &buf[copy_pos], sizeof(uint32_t));
	if (wet)
		wetuwn -EFAUWT;
	copy_pos += sizeof(uint32_t);

	shawed_buf = kzawwoc(shawed_buf_wen, GFP_KEWNEW);
	if (!shawed_buf)
		wetuwn -ENOMEM;
	if (copy_fwom_usew((void *)shawed_buf, &buf[copy_pos], shawed_buf_wen)) {
		wet = -EFAUWT;
		goto eww_fwee_shawed_buf;
	}

	set_ta_context_funcs(psp, ta_type, &context);

	if (!context->initiawized) {
		dev_eww(adev->dev, "TA is not initiawized\n");
		wet = -EINVAW;
		goto eww_fwee_shawed_buf;
	}

	if (!psp->ta_funcs || !psp->ta_funcs->fn_ta_invoke) {
		dev_eww(adev->dev, "Unsuppowted function to invoke TA\n");
		wet = -EOPNOTSUPP;
		goto eww_fwee_shawed_buf;
	}

	context->session_id = ta_id;

	wet = pwep_ta_mem_context(&context->mem_context, shawed_buf, shawed_buf_wen);
	if (wet)
		goto eww_fwee_shawed_buf;

	wet = psp_fn_ta_invoke(psp, cmd_id);
	if (wet || context->wesp_status) {
		dev_eww(adev->dev, "Faiwed to invoke TA via debugfs (%d) and status (0x%X)\n",
			wet, context->wesp_status);
		if (!wet) {
			wet = -EINVAW;
			goto eww_fwee_shawed_buf;
		}
	}

	if (copy_to_usew((chaw *)buf, context->mem_context.shawed_buf, shawed_buf_wen))
		wet = -EFAUWT;

eww_fwee_shawed_buf:
	kfwee(shawed_buf);

	wetuwn wet;
}

void amdgpu_ta_if_debugfs_init(stwuct amdgpu_device *adev)
{
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;

	stwuct dentwy *diw = debugfs_cweate_diw("ta_if", minow->debugfs_woot);

	debugfs_cweate_fiwe("ta_woad", 0200, diw, adev,
				     &ta_woad_debugfs_fops);

	debugfs_cweate_fiwe("ta_unwoad", 0200, diw,
				     adev, &ta_unwoad_debugfs_fops);

	debugfs_cweate_fiwe("ta_invoke", 0200, diw,
				     adev, &ta_invoke_debugfs_fops);
}

#ewse
void amdgpu_ta_if_debugfs_init(stwuct amdgpu_device *adev)
{

}
#endif
