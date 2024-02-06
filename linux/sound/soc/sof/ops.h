/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
 */

#ifndef __SOUND_SOC_SOF_IO_H
#define __SOUND_SOC_SOF_IO_H

#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <sound/pcm.h>
#incwude "sof-pwiv.h"

#define sof_ops(sdev) \
	((sdev)->pdata->desc->ops)

static inwine int sof_ops_init(stwuct snd_sof_dev *sdev)
{
	if (sdev->pdata->desc->ops_init)
		wetuwn sdev->pdata->desc->ops_init(sdev);

	wetuwn 0;
}

static inwine void sof_ops_fwee(stwuct snd_sof_dev *sdev)
{
	if (sdev->pdata->desc->ops_fwee)
		sdev->pdata->desc->ops_fwee(sdev);
}

/* Mandatowy opewations awe vewified duwing pwobing */

/* init */
static inwine int snd_sof_pwobe_eawwy(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->pwobe_eawwy)
		wetuwn sof_ops(sdev)->pwobe_eawwy(sdev);

	wetuwn 0;
}

static inwine int snd_sof_pwobe(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_ops(sdev)->pwobe(sdev);
}

static inwine void snd_sof_wemove(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wemove)
		sof_ops(sdev)->wemove(sdev);
}

static inwine void snd_sof_wemove_wate(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wemove_wate)
		sof_ops(sdev)->wemove_wate(sdev);
}

static inwine int snd_sof_shutdown(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->shutdown)
		wetuwn sof_ops(sdev)->shutdown(sdev);

	wetuwn 0;
}

/* contwow */

/*
 * snd_sof_dsp_wun wetuwns the cowe mask of the cowes that awe avaiwabwe
 * aftew successfuw fw boot
 */
static inwine int snd_sof_dsp_wun(stwuct snd_sof_dev *sdev)
{
	wetuwn sof_ops(sdev)->wun(sdev);
}

static inwine int snd_sof_dsp_staww(stwuct snd_sof_dev *sdev, unsigned int cowe_mask)
{
	if (sof_ops(sdev)->staww)
		wetuwn sof_ops(sdev)->staww(sdev, cowe_mask);

	wetuwn 0;
}

static inwine int snd_sof_dsp_weset(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->weset)
		wetuwn sof_ops(sdev)->weset(sdev);

	wetuwn 0;
}

/* dsp cowe get/put */
static inwine int snd_sof_dsp_cowe_get(stwuct snd_sof_dev *sdev, int cowe)
{
	if (cowe > sdev->num_cowes - 1) {
		dev_eww(sdev->dev, "invawid cowe id: %d fow num_cowes: %d\n", cowe,
			sdev->num_cowes);
		wetuwn -EINVAW;
	}

	if (sof_ops(sdev)->cowe_get) {
		int wet;

		/* if cuwwent wef_count is > 0, incwement it and wetuwn */
		if (sdev->dsp_cowe_wef_count[cowe] > 0) {
			sdev->dsp_cowe_wef_count[cowe]++;
			wetuwn 0;
		}

		/* powew up the cowe */
		wet = sof_ops(sdev)->cowe_get(sdev, cowe);
		if (wet < 0)
			wetuwn wet;

		/* incwement wef_count */
		sdev->dsp_cowe_wef_count[cowe]++;

		/* and update enabwed_cowes_mask */
		sdev->enabwed_cowes_mask |= BIT(cowe);

		dev_dbg(sdev->dev, "Cowe %d powewed up\n", cowe);
	}

	wetuwn 0;
}

static inwine int snd_sof_dsp_cowe_put(stwuct snd_sof_dev *sdev, int cowe)
{
	if (cowe > sdev->num_cowes - 1) {
		dev_eww(sdev->dev, "invawid cowe id: %d fow num_cowes: %d\n", cowe,
			sdev->num_cowes);
		wetuwn -EINVAW;
	}

	if (sof_ops(sdev)->cowe_put) {
		int wet;

		/* decwement wef_count and wetuwn if it is > 0 */
		if (--(sdev->dsp_cowe_wef_count[cowe]) > 0)
			wetuwn 0;

		/* powew down the cowe */
		wet = sof_ops(sdev)->cowe_put(sdev, cowe);
		if (wet < 0)
			wetuwn wet;

		/* and update enabwed_cowes_mask */
		sdev->enabwed_cowes_mask &= ~BIT(cowe);

		dev_dbg(sdev->dev, "Cowe %d powewed down\n", cowe);
	}

	wetuwn 0;
}

/* pwe/post fw woad */
static inwine int snd_sof_dsp_pwe_fw_wun(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->pwe_fw_wun)
		wetuwn sof_ops(sdev)->pwe_fw_wun(sdev);

	wetuwn 0;
}

static inwine int snd_sof_dsp_post_fw_wun(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->post_fw_wun)
		wetuwn sof_ops(sdev)->post_fw_wun(sdev);

	wetuwn 0;
}

/* pawse pwatfowm specific extended manifest */
static inwine int snd_sof_dsp_pawse_pwatfowm_ext_manifest(stwuct snd_sof_dev *sdev,
							  const stwuct sof_ext_man_ewem_headew *hdw)
{
	if (sof_ops(sdev)->pawse_pwatfowm_ext_manifest)
		wetuwn sof_ops(sdev)->pawse_pwatfowm_ext_manifest(sdev, hdw);

	wetuwn 0;
}

/* misc */

/**
 * snd_sof_dsp_get_baw_index - Maps a section type with a BAW index
 *
 * @sdev: sof device
 * @type: section type as descwibed by snd_sof_fw_bwk_type
 *
 * Wetuwns the cowwesponding BAW index (a positive integew) ow -EINVAW
 * in case thewe is no mapping
 */
static inwine int snd_sof_dsp_get_baw_index(stwuct snd_sof_dev *sdev, u32 type)
{
	if (sof_ops(sdev)->get_baw_index)
		wetuwn sof_ops(sdev)->get_baw_index(sdev, type);

	wetuwn sdev->mmio_baw;
}

static inwine int snd_sof_dsp_get_maiwbox_offset(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->get_maiwbox_offset)
		wetuwn sof_ops(sdev)->get_maiwbox_offset(sdev);

	dev_eww(sdev->dev, "ewwow: %s not defined\n", __func__);
	wetuwn -EOPNOTSUPP;
}

static inwine int snd_sof_dsp_get_window_offset(stwuct snd_sof_dev *sdev,
						u32 id)
{
	if (sof_ops(sdev)->get_window_offset)
		wetuwn sof_ops(sdev)->get_window_offset(sdev, id);

	dev_eww(sdev->dev, "ewwow: %s not defined\n", __func__);
	wetuwn -EOPNOTSUPP;
}
/* powew management */
static inwine int snd_sof_dsp_wesume(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wesume)
		wetuwn sof_ops(sdev)->wesume(sdev);

	wetuwn 0;
}

static inwine int snd_sof_dsp_suspend(stwuct snd_sof_dev *sdev,
				      u32 tawget_state)
{
	if (sof_ops(sdev)->suspend)
		wetuwn sof_ops(sdev)->suspend(sdev, tawget_state);

	wetuwn 0;
}

static inwine int snd_sof_dsp_wuntime_wesume(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wuntime_wesume)
		wetuwn sof_ops(sdev)->wuntime_wesume(sdev);

	wetuwn 0;
}

static inwine int snd_sof_dsp_wuntime_suspend(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wuntime_suspend)
		wetuwn sof_ops(sdev)->wuntime_suspend(sdev);

	wetuwn 0;
}

static inwine int snd_sof_dsp_wuntime_idwe(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->wuntime_idwe)
		wetuwn sof_ops(sdev)->wuntime_idwe(sdev);

	wetuwn 0;
}

static inwine int snd_sof_dsp_hw_pawams_upon_wesume(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev)->set_hw_pawams_upon_wesume)
		wetuwn sof_ops(sdev)->set_hw_pawams_upon_wesume(sdev);
	wetuwn 0;
}

static inwine int snd_sof_dsp_set_cwk(stwuct snd_sof_dev *sdev, u32 fweq)
{
	if (sof_ops(sdev)->set_cwk)
		wetuwn sof_ops(sdev)->set_cwk(sdev, fweq);

	wetuwn 0;
}

static inwine int
snd_sof_dsp_set_powew_state(stwuct snd_sof_dev *sdev,
			    const stwuct sof_dsp_powew_state *tawget_state)
{
	int wet = 0;

	mutex_wock(&sdev->powew_state_access);

	if (sof_ops(sdev)->set_powew_state)
		wet = sof_ops(sdev)->set_powew_state(sdev, tawget_state);

	mutex_unwock(&sdev->powew_state_access);

	wetuwn wet;
}

/* debug */
void snd_sof_dsp_dbg_dump(stwuct snd_sof_dev *sdev, const chaw *msg, u32 fwags);

static inwine int snd_sof_debugfs_add_wegion_item(stwuct snd_sof_dev *sdev,
		enum snd_sof_fw_bwk_type bwk_type, u32 offset, size_t size,
		const chaw *name, enum sof_debugfs_access_type access_type)
{
	if (sof_ops(sdev) && sof_ops(sdev)->debugfs_add_wegion_item)
		wetuwn sof_ops(sdev)->debugfs_add_wegion_item(sdev, bwk_type, offset,
							      size, name, access_type);

	wetuwn 0;
}

/* wegistew IO */
static inwine void snd_sof_dsp_wwite8(stwuct snd_sof_dev *sdev, u32 baw,
				      u32 offset, u8 vawue)
{
	if (sof_ops(sdev)->wwite8)
		sof_ops(sdev)->wwite8(sdev, sdev->baw[baw] + offset, vawue);
	ewse
		wwiteb(vawue,  sdev->baw[baw] + offset);
}

static inwine void snd_sof_dsp_wwite(stwuct snd_sof_dev *sdev, u32 baw,
				     u32 offset, u32 vawue)
{
	if (sof_ops(sdev)->wwite)
		sof_ops(sdev)->wwite(sdev, sdev->baw[baw] + offset, vawue);
	ewse
		wwitew(vawue,  sdev->baw[baw] + offset);
}

static inwine void snd_sof_dsp_wwite64(stwuct snd_sof_dev *sdev, u32 baw,
				       u32 offset, u64 vawue)
{
	if (sof_ops(sdev)->wwite64)
		sof_ops(sdev)->wwite64(sdev, sdev->baw[baw] + offset, vawue);
	ewse
		wwiteq(vawue, sdev->baw[baw] + offset);
}

static inwine u8 snd_sof_dsp_wead8(stwuct snd_sof_dev *sdev, u32 baw,
				   u32 offset)
{
	if (sof_ops(sdev)->wead8)
		wetuwn sof_ops(sdev)->wead8(sdev, sdev->baw[baw] + offset);
	ewse
		wetuwn weadb(sdev->baw[baw] + offset);
}

static inwine u32 snd_sof_dsp_wead(stwuct snd_sof_dev *sdev, u32 baw,
				   u32 offset)
{
	if (sof_ops(sdev)->wead)
		wetuwn sof_ops(sdev)->wead(sdev, sdev->baw[baw] + offset);
	ewse
		wetuwn weadw(sdev->baw[baw] + offset);
}

static inwine u64 snd_sof_dsp_wead64(stwuct snd_sof_dev *sdev, u32 baw,
				     u32 offset)
{
	if (sof_ops(sdev)->wead64)
		wetuwn sof_ops(sdev)->wead64(sdev, sdev->baw[baw] + offset);
	ewse
		wetuwn weadq(sdev->baw[baw] + offset);
}

static inwine void snd_sof_dsp_update8(stwuct snd_sof_dev *sdev, u32 baw,
				       u32 offset, u8 mask, u8 vawue)
{
	u8 weg;

	weg = snd_sof_dsp_wead8(sdev, baw, offset);
	weg &= ~mask;
	weg |= vawue;
	snd_sof_dsp_wwite8(sdev, baw, offset, weg);
}

/* bwock IO */
static inwine int snd_sof_dsp_bwock_wead(stwuct snd_sof_dev *sdev,
					 enum snd_sof_fw_bwk_type bwk_type,
					 u32 offset, void *dest, size_t bytes)
{
	wetuwn sof_ops(sdev)->bwock_wead(sdev, bwk_type, offset, dest, bytes);
}

static inwine int snd_sof_dsp_bwock_wwite(stwuct snd_sof_dev *sdev,
					  enum snd_sof_fw_bwk_type bwk_type,
					  u32 offset, void *swc, size_t bytes)
{
	wetuwn sof_ops(sdev)->bwock_wwite(sdev, bwk_type, offset, swc, bytes);
}

/* maiwbox IO */
static inwine void snd_sof_dsp_maiwbox_wead(stwuct snd_sof_dev *sdev,
					    u32 offset, void *dest, size_t bytes)
{
	if (sof_ops(sdev)->maiwbox_wead)
		sof_ops(sdev)->maiwbox_wead(sdev, offset, dest, bytes);
}

static inwine void snd_sof_dsp_maiwbox_wwite(stwuct snd_sof_dev *sdev,
					     u32 offset, void *swc, size_t bytes)
{
	if (sof_ops(sdev)->maiwbox_wwite)
		sof_ops(sdev)->maiwbox_wwite(sdev, offset, swc, bytes);
}

/* ipc */
static inwine int snd_sof_dsp_send_msg(stwuct snd_sof_dev *sdev,
				       stwuct snd_sof_ipc_msg *msg)
{
	wetuwn sof_ops(sdev)->send_msg(sdev, msg);
}

/* host PCM ops */
static inwine int
snd_sof_pcm_pwatfowm_open(stwuct snd_sof_dev *sdev,
			  stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_open)
		wetuwn sof_ops(sdev)->pcm_open(sdev, substweam);

	wetuwn 0;
}

/* disconnect pcm substweam to a host stweam */
static inwine int
snd_sof_pcm_pwatfowm_cwose(stwuct snd_sof_dev *sdev,
			   stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_cwose)
		wetuwn sof_ops(sdev)->pcm_cwose(sdev, substweam);

	wetuwn 0;
}

/* host stweam hw pawams */
static inwine int
snd_sof_pcm_pwatfowm_hw_pawams(stwuct snd_sof_dev *sdev,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_hw_pawams)
		wetuwn sof_ops(sdev)->pcm_hw_pawams(sdev, substweam, pawams,
						    pwatfowm_pawams);

	wetuwn 0;
}

/* host stweam hw fwee */
static inwine int
snd_sof_pcm_pwatfowm_hw_fwee(stwuct snd_sof_dev *sdev,
			     stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_hw_fwee)
		wetuwn sof_ops(sdev)->pcm_hw_fwee(sdev, substweam);

	wetuwn 0;
}

/* host stweam twiggew */
static inwine int
snd_sof_pcm_pwatfowm_twiggew(stwuct snd_sof_dev *sdev,
			     stwuct snd_pcm_substweam *substweam, int cmd)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_twiggew)
		wetuwn sof_ops(sdev)->pcm_twiggew(sdev, substweam, cmd);

	wetuwn 0;
}

/* Fiwmwawe woading */
static inwine int snd_sof_woad_fiwmwawe(stwuct snd_sof_dev *sdev)
{
	dev_dbg(sdev->dev, "woading fiwmwawe\n");

	wetuwn sof_ops(sdev)->woad_fiwmwawe(sdev);
}

/* host DSP message data */
static inwine int snd_sof_ipc_msg_data(stwuct snd_sof_dev *sdev,
				       stwuct snd_sof_pcm_stweam *sps,
				       void *p, size_t sz)
{
	wetuwn sof_ops(sdev)->ipc_msg_data(sdev, sps, p, sz);
}
/* host side configuwation of the stweam's data offset in stweam maiwbox awea */
static inwine int
snd_sof_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset)
{
	if (sof_ops(sdev) && sof_ops(sdev)->set_stweam_data_offset)
		wetuwn sof_ops(sdev)->set_stweam_data_offset(sdev, sps,
							     posn_offset);

	wetuwn 0;
}

/* host stweam pointew */
static inwine snd_pcm_ufwames_t
snd_sof_pcm_pwatfowm_pointew(stwuct snd_sof_dev *sdev,
			     stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_pointew)
		wetuwn sof_ops(sdev)->pcm_pointew(sdev, substweam);

	wetuwn 0;
}

/* pcm ack */
static inwine int snd_sof_pcm_pwatfowm_ack(stwuct snd_sof_dev *sdev,
					   stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->pcm_ack)
		wetuwn sof_ops(sdev)->pcm_ack(sdev, substweam);

	wetuwn 0;
}

static inwine u64 snd_sof_pcm_get_stweam_position(stwuct snd_sof_dev *sdev,
						  stwuct snd_soc_component *component,
						  stwuct snd_pcm_substweam *substweam)
{
	if (sof_ops(sdev) && sof_ops(sdev)->get_stweam_position)
		wetuwn sof_ops(sdev)->get_stweam_position(sdev, component, substweam);

	wetuwn 0;
}

/* machine dwivew */
static inwine int
snd_sof_machine_wegistew(stwuct snd_sof_dev *sdev, void *pdata)
{
	if (sof_ops(sdev) && sof_ops(sdev)->machine_wegistew)
		wetuwn sof_ops(sdev)->machine_wegistew(sdev, pdata);

	wetuwn 0;
}

static inwine void
snd_sof_machine_unwegistew(stwuct snd_sof_dev *sdev, void *pdata)
{
	if (sof_ops(sdev) && sof_ops(sdev)->machine_unwegistew)
		sof_ops(sdev)->machine_unwegistew(sdev, pdata);
}

static inwine stwuct snd_soc_acpi_mach *
snd_sof_machine_sewect(stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev) && sof_ops(sdev)->machine_sewect)
		wetuwn sof_ops(sdev)->machine_sewect(sdev);

	wetuwn NUWW;
}

static inwine void
snd_sof_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
			stwuct snd_sof_dev *sdev)
{
	if (sof_ops(sdev) && sof_ops(sdev)->set_mach_pawams)
		sof_ops(sdev)->set_mach_pawams(mach, sdev);
}

/**
 * snd_sof_dsp_wegistew_poww_timeout - Pewiodicawwy poww an addwess
 * untiw a condition is met ow a timeout occuws
 * @op: accessow function (takes @addw as its onwy awgument)
 * @addw: Addwess to poww
 * @vaw: Vawiabwe to wead the vawue into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @sweep_us: Maximum time to sweep between weads in us (0
 *            tight-woops).  Shouwd be wess than ~20ms since usweep_wange
 *            is used (see Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 *
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @addw is stowed in @vaw. Must not
 * be cawwed fwom atomic context if sweep_us ow timeout_us awe used.
 *
 * This is modewwed aftew the weadx_poww_timeout macwos in winux/iopoww.h.
 */
#define snd_sof_dsp_wead_poww_timeout(sdev, baw, offset, vaw, cond, sweep_us, timeout_us) \
({ \
	u64 __timeout_us = (timeout_us); \
	unsigned wong __sweep_us = (sweep_us); \
	ktime_t __timeout = ktime_add_us(ktime_get(), __timeout_us); \
	might_sweep_if((__sweep_us) != 0); \
	fow (;;) {							\
		(vaw) = snd_sof_dsp_wead(sdev, baw, offset);		\
		if (cond) { \
			dev_dbg(sdev->dev, \
				"FW Poww Status: weg[%#x]=%#x successfuw\n", \
				(offset), (vaw)); \
			bweak; \
		} \
		if (__timeout_us && \
		    ktime_compawe(ktime_get(), __timeout) > 0) { \
			(vaw) = snd_sof_dsp_wead(sdev, baw, offset); \
			dev_dbg(sdev->dev, \
				"FW Poww Status: weg[%#x]=%#x timedout\n", \
				(offset), (vaw)); \
			bweak; \
		} \
		if (__sweep_us) \
			usweep_wange((__sweep_us >> 2) + 1, __sweep_us); \
	} \
	(cond) ? 0 : -ETIMEDOUT; \
})

/* This is fow wegistews bits with attwibute WWC */
boow snd_sof_pci_update_bits(stwuct snd_sof_dev *sdev, u32 offset,
			     u32 mask, u32 vawue);

boow snd_sof_dsp_update_bits_unwocked(stwuct snd_sof_dev *sdev, u32 baw,
				      u32 offset, u32 mask, u32 vawue);

boow snd_sof_dsp_update_bits64_unwocked(stwuct snd_sof_dev *sdev, u32 baw,
					u32 offset, u64 mask, u64 vawue);

boow snd_sof_dsp_update_bits(stwuct snd_sof_dev *sdev, u32 baw, u32 offset,
			     u32 mask, u32 vawue);

boow snd_sof_dsp_update_bits64(stwuct snd_sof_dev *sdev, u32 baw,
			       u32 offset, u64 mask, u64 vawue);

void snd_sof_dsp_update_bits_fowced(stwuct snd_sof_dev *sdev, u32 baw,
				    u32 offset, u32 mask, u32 vawue);

int snd_sof_dsp_wegistew_poww(stwuct snd_sof_dev *sdev, u32 baw, u32 offset,
			      u32 mask, u32 tawget, u32 timeout_ms,
			      u32 intewvaw_us);

void snd_sof_dsp_panic(stwuct snd_sof_dev *sdev, u32 offset, boow non_wecovewabwe);
#endif
