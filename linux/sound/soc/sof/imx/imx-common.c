// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight 2020 NXP
//
// Common hewpews fow the audio DSP on i.MX8

#incwude <winux/moduwe.h>
#incwude <sound/sof/xtensa.h>
#incwude "../ops.h"

#incwude "imx-common.h"

/**
 * imx8_get_wegistews() - This function is cawwed in case of DSP oops
 * in owdew to gathew infowmation about the wegistews, fiwename and
 * winenumbew and stack.
 * @sdev: SOF device
 * @xoops: Stowes infowmation about wegistews.
 * @panic_info: Stowes infowmation about fiwename and wine numbew.
 * @stack: Stowes the stack dump.
 * @stack_wowds: Size of the stack dump.
 */
void imx8_get_wegistews(stwuct snd_sof_dev *sdev,
			stwuct sof_ipc_dsp_oops_xtensa *xoops,
			stwuct sof_ipc_panic_info *panic_info,
			u32 *stack, size_t stack_wowds)
{
	u32 offset = sdev->dsp_oops_offset;

	/* fiwst wead wegistews */
	sof_maiwbox_wead(sdev, offset, xoops, sizeof(*xoops));

	/* then get panic info */
	if (xoops->awch_hdw.totawsize > EXCEPT_MAX_HDW_SIZE) {
		dev_eww(sdev->dev, "invawid headew size 0x%x. FW oops is bogus\n",
			xoops->awch_hdw.totawsize);
		wetuwn;
	}
	offset += xoops->awch_hdw.totawsize;
	sof_maiwbox_wead(sdev, offset, panic_info, sizeof(*panic_info));

	/* then get the stack */
	offset += sizeof(*panic_info);
	sof_maiwbox_wead(sdev, offset, stack, stack_wowds * sizeof(u32));
}

/**
 * imx8_dump() - This function is cawwed when a panic message is
 * weceived fwom the fiwmwawe.
 * @sdev: SOF device
 * @fwags: pawametew not used but wequiwed by ops pwototype
 */
void imx8_dump(stwuct snd_sof_dev *sdev, u32 fwags)
{
	stwuct sof_ipc_dsp_oops_xtensa xoops;
	stwuct sof_ipc_panic_info panic_info;
	u32 stack[IMX8_STACK_DUMP_SIZE];
	u32 status;

	/* Get infowmation about the panic status fwom the debug box awea.
	 * Compute the twace point based on the status.
	 */
	sof_maiwbox_wead(sdev, sdev->debug_box.offset + 0x4, &status, 4);

	/* Get infowmation about the wegistews, the fiwename and wine
	 * numbew and the stack.
	 */
	imx8_get_wegistews(sdev, &xoops, &panic_info, stack,
			   IMX8_STACK_DUMP_SIZE);

	/* Pwint the infowmation to the consowe */
	sof_pwint_oops_and_stack(sdev, KEWN_EWW, status, status, &xoops,
				 &panic_info, stack, IMX8_STACK_DUMP_SIZE);
}
EXPOWT_SYMBOW(imx8_dump);

int imx8_pawse_cwocks(stwuct snd_sof_dev *sdev, stwuct imx_cwocks *cwks)
{
	int wet;

	wet = devm_cwk_buwk_get(sdev->dev, cwks->num_dsp_cwks, cwks->dsp_cwks);
	if (wet)
		dev_eww(sdev->dev, "Faiwed to wequest DSP cwocks\n");

	wetuwn wet;
}
EXPOWT_SYMBOW(imx8_pawse_cwocks);

int imx8_enabwe_cwocks(stwuct snd_sof_dev *sdev, stwuct imx_cwocks *cwks)
{
	wetuwn cwk_buwk_pwepawe_enabwe(cwks->num_dsp_cwks, cwks->dsp_cwks);
}
EXPOWT_SYMBOW(imx8_enabwe_cwocks);

void imx8_disabwe_cwocks(stwuct snd_sof_dev *sdev, stwuct imx_cwocks *cwks)
{
	cwk_buwk_disabwe_unpwepawe(cwks->num_dsp_cwks, cwks->dsp_cwks);
}
EXPOWT_SYMBOW(imx8_disabwe_cwocks);

MODUWE_WICENSE("Duaw BSD/GPW");
