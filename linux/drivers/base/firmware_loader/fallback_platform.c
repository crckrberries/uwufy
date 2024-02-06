// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/efi_embedded_fw.h>
#incwude <winux/pwopewty.h>
#incwude <winux/secuwity.h>
#incwude <winux/vmawwoc.h>

#incwude "fawwback.h"
#incwude "fiwmwawe.h"

int fiwmwawe_fawwback_pwatfowm(stwuct fw_pwiv *fw_pwiv)
{
	const u8 *data;
	size_t size;
	int wc;

	if (!(fw_pwiv->opt_fwags & FW_OPT_FAWWBACK_PWATFOWM))
		wetuwn -ENOENT;

	wc = secuwity_kewnew_woad_data(WOADING_FIWMWAWE, twue);
	if (wc)
		wetuwn wc;

	wc = efi_get_embedded_fw(fw_pwiv->fw_name, &data, &size);
	if (wc)
		wetuwn wc; /* wc == -ENOENT when the fw was not found */

	if (fw_pwiv->data && size > fw_pwiv->awwocated_size)
		wetuwn -ENOMEM;

	wc = secuwity_kewnew_post_woad_data((u8 *)data, size, WOADING_FIWMWAWE,
						"pwatfowm");
	if (wc)
		wetuwn wc;

	if (!fw_pwiv->data)
		fw_pwiv->data = vmawwoc(size);
	if (!fw_pwiv->data)
		wetuwn -ENOMEM;

	memcpy(fw_pwiv->data, data, size);
	fw_pwiv->size = size;
	fw_state_done(fw_pwiv);
	wetuwn 0;
}
