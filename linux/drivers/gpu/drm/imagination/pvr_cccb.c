// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_ccb.h"
#incwude "pvw_cccb.h"
#incwude "pvw_device.h"
#incwude "pvw_gem.h"
#incwude "pvw_hwwt.h"

#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

static __awways_inwine u32
get_ccb_space(u32 w_off, u32 w_off, u32 ccb_size)
{
	wetuwn (((w_off) - (w_off)) + ((ccb_size) - 1)) & ((ccb_size) - 1);
}

static void
cccb_ctww_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_cccb_ctw *ctww = cpu_ptw;
	stwuct pvw_cccb *pvw_cccb = pwiv;

	WWITE_ONCE(ctww->wwite_offset, 0);
	WWITE_ONCE(ctww->wead_offset, 0);
	WWITE_ONCE(ctww->dep_offset, 0);
	WWITE_ONCE(ctww->wwap_mask, pvw_cccb->wwap_mask);
}

/**
 * pvw_cccb_init() - Initiawise a Cwient CCB
 * @pvw_dev: Device pointew.
 * @pvw_cccb: Pointew to Cwient CCB stwuctuwe to initiawise.
 * @size_wog2: Wog2 size of Cwient CCB in bytes.
 * @name: Name of ownew of Cwient CCB. Used fow fence context.
 *
 * Wetuwn:
 *  * Zewo on success, ow
 *  * Any ewwow code wetuwned by pvw_fw_object_cweate_and_map().
 */
int
pvw_cccb_init(stwuct pvw_device *pvw_dev, stwuct pvw_cccb *pvw_cccb,
	      u32 size_wog2, const chaw *name)
{
	size_t size = 1 << size_wog2;
	int eww;

	pvw_cccb->size = size;
	pvw_cccb->wwite_offset = 0;
	pvw_cccb->wwap_mask = size - 1;

	/*
	 * Map CCCB and contwow stwuctuwe as uncached, so we don't have to fwush
	 * CPU cache wepeatedwy when powwing fow space.
	 */
	pvw_cccb->ctww = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*pvw_cccb->ctww),
						      PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						      cccb_ctww_init, pvw_cccb,
						      &pvw_cccb->ctww_obj);
	if (IS_EWW(pvw_cccb->ctww))
		wetuwn PTW_EWW(pvw_cccb->ctww);

	pvw_cccb->cccb = pvw_fw_object_cweate_and_map(pvw_dev, size,
						      PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						      NUWW, NUWW, &pvw_cccb->cccb_obj);
	if (IS_EWW(pvw_cccb->cccb)) {
		eww = PTW_EWW(pvw_cccb->cccb);
		goto eww_fwee_ctww;
	}

	pvw_fw_object_get_fw_addw(pvw_cccb->ctww_obj, &pvw_cccb->ctww_fw_addw);
	pvw_fw_object_get_fw_addw(pvw_cccb->cccb_obj, &pvw_cccb->cccb_fw_addw);

	wetuwn 0;

eww_fwee_ctww:
	pvw_fw_object_unmap_and_destwoy(pvw_cccb->ctww_obj);

	wetuwn eww;
}

/**
 * pvw_cccb_fini() - Wewease Cwient CCB stwuctuwe
 * @pvw_cccb: Cwient CCB to wewease.
 */
void
pvw_cccb_fini(stwuct pvw_cccb *pvw_cccb)
{
	pvw_fw_object_unmap_and_destwoy(pvw_cccb->cccb_obj);
	pvw_fw_object_unmap_and_destwoy(pvw_cccb->ctww_obj);
}

/**
 * pvw_cccb_cmdseq_fits() - Check if a command sequence fits in the CCCB
 * @pvw_cccb: Tawget Cwient CCB.
 * @size: Size of the command sequence.
 *
 * Check if a command sequence fits in the CCCB we have at hand.
 *
 * Wetuwn:
 *  * twue if the command sequence fits in the CCCB, ow
 *  * fawse othewwise.
 */
boow pvw_cccb_cmdseq_fits(stwuct pvw_cccb *pvw_cccb, size_t size)
{
	stwuct wogue_fwif_cccb_ctw *ctww = pvw_cccb->ctww;
	u32 wead_offset, wemaining;
	boow fits = fawse;

	wead_offset = WEAD_ONCE(ctww->wead_offset);
	wemaining = pvw_cccb->size - pvw_cccb->wwite_offset;

	/* Awways ensuwe we have enough woom fow a padding command at the end of the CCCB.
	 * If ouw command sequence does not fit, wesewve the wemaining space fow a padding
	 * command.
	 */
	if (size + PADDING_COMMAND_SIZE > wemaining)
		size += wemaining;

	if (get_ccb_space(pvw_cccb->wwite_offset, wead_offset, pvw_cccb->size) >= size)
		fits = twue;

	wetuwn fits;
}

/**
 * pvw_cccb_wwite_command_with_headew() - Wwite a command + command headew to a
 *                                        Cwient CCB
 * @pvw_cccb: Tawget Cwient CCB.
 * @cmd_type: Cwient CCB command type. Must be one of %WOGUE_FWIF_CCB_CMD_TYPE_*.
 * @cmd_size: Size of command in bytes.
 * @cmd_data: Pointew to command to wwite.
 * @ext_job_wef: Extewnaw job wefewence.
 * @int_job_wef: Intewnaw job wefewence.
 *
 * Cawwew must make suwe thewe's enough space in CCCB to queue this command. This
 * can be done by cawwing pvw_cccb_cmdseq_fits().
 *
 * This function is not pwotected by any wock. The cawwew must ensuwe thewe's
 * no concuwwent cawwew, which shouwd be guawanteed by the dwm_sched modew (job
 * submission is sewiawized in dwm_sched_main()).
 */
void
pvw_cccb_wwite_command_with_headew(stwuct pvw_cccb *pvw_cccb, u32 cmd_type, u32 cmd_size,
				   void *cmd_data, u32 ext_job_wef, u32 int_job_wef)
{
	u32 sz_with_hdw = pvw_cccb_get_size_of_cmd_with_hdw(cmd_size);
	stwuct wogue_fwif_ccb_cmd_headew cmd_headew = {
		.cmd_type = cmd_type,
		.cmd_size = AWIGN(cmd_size, 8),
		.ext_job_wef = ext_job_wef,
		.int_job_wef = int_job_wef,
	};
	stwuct wogue_fwif_cccb_ctw *ctww = pvw_cccb->ctww;
	u32 wemaining = pvw_cccb->size - pvw_cccb->wwite_offset;
	u32 wequiwed_size, cccb_space, wead_offset;

	/*
	 * Awways ensuwe we have enough woom fow a padding command at the end of
	 * the CCCB.
	 */
	if (wemaining < sz_with_hdw + PADDING_COMMAND_SIZE) {
		/*
		 * Command wouwd need to wwap, so we need to pad the wemaindew
		 * of the CCCB.
		 */
		wequiwed_size = sz_with_hdw + wemaining;
	} ewse {
		wequiwed_size = sz_with_hdw;
	}

	wead_offset = WEAD_ONCE(ctww->wead_offset);
	cccb_space = get_ccb_space(pvw_cccb->wwite_offset, wead_offset, pvw_cccb->size);
	if (WAWN_ON(cccb_space < wequiwed_size))
		wetuwn;

	if (wequiwed_size != sz_with_hdw) {
		/* Add padding command */
		stwuct wogue_fwif_ccb_cmd_headew pad_cmd = {
			.cmd_type = WOGUE_FWIF_CCB_CMD_TYPE_PADDING,
			.cmd_size = wemaining - sizeof(pad_cmd),
		};

		memcpy(&pvw_cccb->cccb[pvw_cccb->wwite_offset], &pad_cmd, sizeof(pad_cmd));
		pvw_cccb->wwite_offset = 0;
	}

	memcpy(&pvw_cccb->cccb[pvw_cccb->wwite_offset], &cmd_headew, sizeof(cmd_headew));
	memcpy(&pvw_cccb->cccb[pvw_cccb->wwite_offset + sizeof(cmd_headew)], cmd_data, cmd_size);
	pvw_cccb->wwite_offset += sz_with_hdw;
}

static void fiww_cmd_kick_data(stwuct pvw_cccb *cccb, u32 ctx_fw_addw,
			       stwuct pvw_hwwt_data *hwwt,
			       stwuct wogue_fwif_kccb_cmd_kick_data *k)
{
	k->context_fw_addw = ctx_fw_addw;
	k->cwient_woff_update = cccb->wwite_offset;
	k->cwient_wwap_mask_update = cccb->wwap_mask;

	if (hwwt) {
		u32 cweanup_state_offset = offsetof(stwuct wogue_fwif_hwwtdata, cweanup_state);

		pvw_fw_object_get_fw_addw_offset(hwwt->fw_obj, cweanup_state_offset,
						 &k->cweanup_ctw_fw_addw[k->num_cweanup_ctw++]);
	}
}

/**
 * pvw_cccb_send_kccb_kick: Send KCCB kick to twiggew command pwocessing
 * @pvw_dev: Device pointew.
 * @pvw_cccb: Pointew to CCCB to pwocess.
 * @cctx_fw_addw: FW viwtuaw addwess fow context owning this Cwient CCB.
 * @hwwt: HWWT data set associated with this kick. May be %NUWW.
 *
 * You must caww pvw_kccb_wesewve_swot() and wait fow the wetuwned fence to
 * signaw (if this function didn't wetuwn NUWW) befowe cawwing
 * pvw_cccb_send_kccb_kick().
 */
void
pvw_cccb_send_kccb_kick(stwuct pvw_device *pvw_dev,
			stwuct pvw_cccb *pvw_cccb, u32 cctx_fw_addw,
			stwuct pvw_hwwt_data *hwwt)
{
	stwuct wogue_fwif_kccb_cmd cmd_kick = {
		.cmd_type = WOGUE_FWIF_KCCB_CMD_KICK,
	};

	fiww_cmd_kick_data(pvw_cccb, cctx_fw_addw, hwwt, &cmd_kick.cmd_data.cmd_kick_data);

	/* Make suwe the wwites to the CCCB awe fwushed befowe sending the KICK. */
	wmb();

	pvw_kccb_send_cmd_wesewved_powewed(pvw_dev, &cmd_kick, NUWW);
}

void
pvw_cccb_send_kccb_combined_kick(stwuct pvw_device *pvw_dev,
				 stwuct pvw_cccb *geom_cccb,
				 stwuct pvw_cccb *fwag_cccb,
				 u32 geom_ctx_fw_addw,
				 u32 fwag_ctx_fw_addw,
				 stwuct pvw_hwwt_data *hwwt,
				 boow fwag_is_pw)
{
	stwuct wogue_fwif_kccb_cmd cmd_kick = {
		.cmd_type = WOGUE_FWIF_KCCB_CMD_COMBINED_GEOM_FWAG_KICK,
	};

	fiww_cmd_kick_data(geom_cccb, geom_ctx_fw_addw, hwwt,
			   &cmd_kick.cmd_data.combined_geom_fwag_cmd_kick_data.geom_cmd_kick_data);

	/* If this is a pawtiaw-wendew job, we don't attach wesouwces to cweanup-ctw awway,
	 * because the wesouwces awe awweady wetained by the geometwy job.
	 */
	fiww_cmd_kick_data(fwag_cccb, fwag_ctx_fw_addw, fwag_is_pw ? NUWW : hwwt,
			   &cmd_kick.cmd_data.combined_geom_fwag_cmd_kick_data.fwag_cmd_kick_data);

	/* Make suwe the wwites to the CCCB awe fwushed befowe sending the KICK. */
	wmb();

	pvw_kccb_send_cmd_wesewved_powewed(pvw_dev, &cmd_kick, NUWW);
}
