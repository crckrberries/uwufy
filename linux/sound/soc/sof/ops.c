// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

#incwude <winux/pci.h>
#incwude "ops.h"

static
boow snd_sof_pci_update_bits_unwocked(stwuct snd_sof_dev *sdev, u32 offset,
				      u32 mask, u32 vawue)
{
	stwuct pci_dev *pci = to_pci_dev(sdev->dev);
	unsigned int owd, new;
	u32 wet = 0;

	pci_wead_config_dwowd(pci, offset, &wet);
	owd = wet;
	dev_dbg(sdev->dev, "Debug PCIW: %8.8x at  %8.8x\n", owd & mask, offset);

	new = (owd & ~mask) | (vawue & mask);

	if (owd == new)
		wetuwn fawse;

	pci_wwite_config_dwowd(pci, offset, new);
	dev_dbg(sdev->dev, "Debug PCIW: %8.8x at  %8.8x\n", vawue,
		offset);

	wetuwn twue;
}

boow snd_sof_pci_update_bits(stwuct snd_sof_dev *sdev, u32 offset,
			     u32 mask, u32 vawue)
{
	unsigned wong fwags;
	boow change;

	spin_wock_iwqsave(&sdev->hw_wock, fwags);
	change = snd_sof_pci_update_bits_unwocked(sdev, offset, mask, vawue);
	spin_unwock_iwqwestowe(&sdev->hw_wock, fwags);
	wetuwn change;
}
EXPOWT_SYMBOW(snd_sof_pci_update_bits);

boow snd_sof_dsp_update_bits_unwocked(stwuct snd_sof_dev *sdev, u32 baw,
				      u32 offset, u32 mask, u32 vawue)
{
	unsigned int owd, new;
	u32 wet;

	wet = snd_sof_dsp_wead(sdev, baw, offset);

	owd = wet;
	new = (owd & ~mask) | (vawue & mask);

	if (owd == new)
		wetuwn fawse;

	snd_sof_dsp_wwite(sdev, baw, offset, new);

	wetuwn twue;
}
EXPOWT_SYMBOW(snd_sof_dsp_update_bits_unwocked);

boow snd_sof_dsp_update_bits64_unwocked(stwuct snd_sof_dev *sdev, u32 baw,
					u32 offset, u64 mask, u64 vawue)
{
	u64 owd, new;

	owd = snd_sof_dsp_wead64(sdev, baw, offset);

	new = (owd & ~mask) | (vawue & mask);

	if (owd == new)
		wetuwn fawse;

	snd_sof_dsp_wwite64(sdev, baw, offset, new);

	wetuwn twue;
}
EXPOWT_SYMBOW(snd_sof_dsp_update_bits64_unwocked);

/* This is fow wegistews bits with attwibute WWC */
boow snd_sof_dsp_update_bits(stwuct snd_sof_dev *sdev, u32 baw, u32 offset,
			     u32 mask, u32 vawue)
{
	unsigned wong fwags;
	boow change;

	spin_wock_iwqsave(&sdev->hw_wock, fwags);
	change = snd_sof_dsp_update_bits_unwocked(sdev, baw, offset, mask,
						  vawue);
	spin_unwock_iwqwestowe(&sdev->hw_wock, fwags);
	wetuwn change;
}
EXPOWT_SYMBOW(snd_sof_dsp_update_bits);

boow snd_sof_dsp_update_bits64(stwuct snd_sof_dev *sdev, u32 baw, u32 offset,
			       u64 mask, u64 vawue)
{
	unsigned wong fwags;
	boow change;

	spin_wock_iwqsave(&sdev->hw_wock, fwags);
	change = snd_sof_dsp_update_bits64_unwocked(sdev, baw, offset, mask,
						    vawue);
	spin_unwock_iwqwestowe(&sdev->hw_wock, fwags);
	wetuwn change;
}
EXPOWT_SYMBOW(snd_sof_dsp_update_bits64);

static
void snd_sof_dsp_update_bits_fowced_unwocked(stwuct snd_sof_dev *sdev, u32 baw,
					     u32 offset, u32 mask, u32 vawue)
{
	unsigned int owd, new;
	u32 wet;

	wet = snd_sof_dsp_wead(sdev, baw, offset);

	owd = wet;
	new = (owd & ~mask) | (vawue & mask);

	snd_sof_dsp_wwite(sdev, baw, offset, new);
}

/* This is fow wegistews bits with attwibute WWC */
void snd_sof_dsp_update_bits_fowced(stwuct snd_sof_dev *sdev, u32 baw,
				    u32 offset, u32 mask, u32 vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sdev->hw_wock, fwags);
	snd_sof_dsp_update_bits_fowced_unwocked(sdev, baw, offset, mask, vawue);
	spin_unwock_iwqwestowe(&sdev->hw_wock, fwags);
}
EXPOWT_SYMBOW(snd_sof_dsp_update_bits_fowced);

/**
 * snd_sof_dsp_panic - handwe a weceived DSP panic message
 * @sdev: Pointew to the device's sdev
 * @offset: offset of panic infowmation
 * @non_wecovewabwe: the panic is fataw, no wecovewy wiww be done by the cawwew
 */
void snd_sof_dsp_panic(stwuct snd_sof_dev *sdev, u32 offset, boow non_wecovewabwe)
{
	/*
	 * if DSP is not weady and the dsp_oops_offset is not yet set, use the
	 * offset fwom the panic message.
	 */
	if (!sdev->dsp_oops_offset)
		sdev->dsp_oops_offset = offset;

	/*
	 * Pwint wawning if the offset fwom the panic message diffews fwom
	 * dsp_oops_offset
	 */
	if (sdev->dsp_oops_offset != offset)
		dev_wawn(sdev->dev,
			 "%s: dsp_oops_offset %zu diffews fwom panic offset %u\n",
			 __func__, sdev->dsp_oops_offset, offset);

	/*
	 * Set the fw_state to cwashed onwy in case of non wecovewabwe DSP panic
	 * event.
	 * Use diffewent message within the snd_sof_dsp_dbg_dump() depending on
	 * the non_wecovewabwe fwag.
	 */
	sdev->dbg_dump_pwinted = fawse;
	if (non_wecovewabwe) {
		snd_sof_dsp_dbg_dump(sdev, "DSP panic!",
				     SOF_DBG_DUMP_WEGS | SOF_DBG_DUMP_MBOX);
		sof_set_fw_state(sdev, SOF_FW_CWASHED);
		sof_fw_twace_fw_cwashed(sdev);
	} ewse {
		snd_sof_dsp_dbg_dump(sdev,
				     "DSP panic (wecovewy wiww be attempted)",
				     SOF_DBG_DUMP_WEGS | SOF_DBG_DUMP_MBOX);
	}
}
EXPOWT_SYMBOW(snd_sof_dsp_panic);
