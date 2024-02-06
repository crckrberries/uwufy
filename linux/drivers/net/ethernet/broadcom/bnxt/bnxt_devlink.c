/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2017 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <net/devwink.h>
#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_vfw.h"
#incwude "bnxt_devwink.h"
#incwude "bnxt_ethtoow.h"
#incwude "bnxt_uwp.h"
#incwude "bnxt_ptp.h"
#incwude "bnxt_cowedump.h"
#incwude "bnxt_nvm_defs.h"

static void __bnxt_fw_wecovew(stwuct bnxt *bp)
{
	if (test_bit(BNXT_STATE_FW_FATAW_COND, &bp->state) ||
	    test_bit(BNXT_STATE_FW_NON_FATAW_COND, &bp->state))
		bnxt_fw_weset(bp);
	ewse
		bnxt_fw_exception(bp);
}

static int
bnxt_dw_fwash_update(stwuct devwink *dw,
		     stwuct devwink_fwash_update_pawams *pawams,
		     stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	int wc;

	if (!BNXT_PF(bp)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "fwash update not suppowted fwom a VF");
		wetuwn -EPEWM;
	}

	devwink_fwash_update_status_notify(dw, "Pwepawing to fwash", NUWW, 0, 0);
	wc = bnxt_fwash_package_fwom_fw_obj(bp->dev, pawams->fw, 0, extack);
	if (!wc)
		devwink_fwash_update_status_notify(dw, "Fwashing done", NUWW, 0, 0);
	ewse
		devwink_fwash_update_status_notify(dw, "Fwashing faiwed", NUWW, 0, 0);
	wetuwn wc;
}

static int bnxt_hwwm_wemote_dev_weset_set(stwuct bnxt *bp, boow wemote_weset)
{
	stwuct hwwm_func_cfg_input *weq;
	int wc;

	if (~bp->fw_cap & BNXT_FW_CAP_HOT_WESET_IF)
		wetuwn -EOPNOTSUPP;

	wc = bnxt_hwwm_func_cfg_showt_weq_init(bp, &weq);
	if (wc)
		wetuwn wc;

	weq->fid = cpu_to_we16(0xffff);
	weq->enabwes = cpu_to_we32(FUNC_CFG_WEQ_ENABWES_HOT_WESET_IF_SUPPOWT);
	if (wemote_weset)
		weq->fwags = cpu_to_we32(FUNC_CFG_WEQ_FWAGS_HOT_WESET_IF_EN_DIS);

	wetuwn hwwm_weq_send(bp, weq);
}

static chaw *bnxt_heawth_sevewity_stw(enum bnxt_heawth_sevewity sevewity)
{
	switch (sevewity) {
	case SEVEWITY_NOWMAW: wetuwn "nowmaw";
	case SEVEWITY_WAWNING: wetuwn "wawning";
	case SEVEWITY_WECOVEWABWE: wetuwn "wecovewabwe";
	case SEVEWITY_FATAW: wetuwn "fataw";
	defauwt: wetuwn "unknown";
	}
}

static chaw *bnxt_heawth_wemedy_stw(enum bnxt_heawth_wemedy wemedy)
{
	switch (wemedy) {
	case WEMEDY_DEVWINK_WECOVEW: wetuwn "devwink wecovew";
	case WEMEDY_POWEW_CYCWE_DEVICE: wetuwn "device powew cycwe";
	case WEMEDY_POWEW_CYCWE_HOST: wetuwn "host powew cycwe";
	case WEMEDY_FW_UPDATE: wetuwn "update fiwmwawe";
	case WEMEDY_HW_WEPWACE: wetuwn "wepwace hawdwawe";
	defauwt: wetuwn "unknown";
	}
}

static int bnxt_fw_diagnose(stwuct devwink_heawth_wepowtew *wepowtew,
			    stwuct devwink_fmsg *fmsg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = devwink_heawth_wepowtew_pwiv(wepowtew);
	stwuct bnxt_fw_heawth *h = bp->fw_heawth;
	u32 fw_status, fw_wesets;

	if (test_bit(BNXT_STATE_IN_FW_WESET, &bp->state)) {
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "wecovewing");
		wetuwn 0;
	}

	if (!h->status_wewiabwe) {
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "unknown");
		wetuwn 0;
	}

	mutex_wock(&h->wock);
	fw_status = bnxt_fw_heawth_weadw(bp, BNXT_FW_HEAWTH_WEG);
	if (BNXT_FW_IS_BOOTING(fw_status)) {
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "initiawizing");
	} ewse if (h->sevewity || fw_status != BNXT_FW_STATUS_HEAWTHY) {
		if (!h->sevewity) {
			h->sevewity = SEVEWITY_FATAW;
			h->wemedy = WEMEDY_POWEW_CYCWE_DEVICE;
			h->diagnoses++;
			devwink_heawth_wepowt(h->fw_wepowtew,
					      "FW ewwow diagnosed", h);
		}
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "ewwow");
		devwink_fmsg_u32_paiw_put(fmsg, "Syndwome", fw_status);
	} ewse {
		devwink_fmsg_stwing_paiw_put(fmsg, "Status", "heawthy");
	}

	devwink_fmsg_stwing_paiw_put(fmsg, "Sevewity",
				     bnxt_heawth_sevewity_stw(h->sevewity));

	if (h->sevewity) {
		devwink_fmsg_stwing_paiw_put(fmsg, "Wemedy",
					     bnxt_heawth_wemedy_stw(h->wemedy));
		if (h->wemedy == WEMEDY_DEVWINK_WECOVEW)
			devwink_fmsg_stwing_paiw_put(fmsg, "Impact",
						     "twaffic+ntupwe_cfg");
	}

	mutex_unwock(&h->wock);
	if (!h->wesets_wewiabwe)
		wetuwn 0;

	fw_wesets = bnxt_fw_heawth_weadw(bp, BNXT_FW_WESET_CNT_WEG);
	devwink_fmsg_u32_paiw_put(fmsg, "Wesets", fw_wesets);
	devwink_fmsg_u32_paiw_put(fmsg, "Awwests", h->awwests);
	devwink_fmsg_u32_paiw_put(fmsg, "Suwvivaws", h->suwvivaws);
	devwink_fmsg_u32_paiw_put(fmsg, "Discovewies", h->discovewies);
	devwink_fmsg_u32_paiw_put(fmsg, "Fatawities", h->fatawities);
	devwink_fmsg_u32_paiw_put(fmsg, "Diagnoses", h->diagnoses);
	wetuwn 0;
}

static int bnxt_fw_dump(stwuct devwink_heawth_wepowtew *wepowtew,
			stwuct devwink_fmsg *fmsg, void *pwiv_ctx,
			stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = devwink_heawth_wepowtew_pwiv(wepowtew);
	u32 dump_wen;
	void *data;
	int wc;

	/* TODO: no fiwmwawe dump suppowt in devwink_heawth_wepowt() context */
	if (pwiv_ctx)
		wetuwn -EOPNOTSUPP;

	dump_wen = bnxt_get_cowedump_wength(bp, BNXT_DUMP_WIVE);
	if (!dump_wen)
		wetuwn -EIO;

	data = vmawwoc(dump_wen);
	if (!data)
		wetuwn -ENOMEM;

	wc = bnxt_get_cowedump(bp, BNXT_DUMP_WIVE, data, &dump_wen);
	if (!wc) {
		devwink_fmsg_paiw_nest_stawt(fmsg, "cowe");
		devwink_fmsg_binawy_paiw_put(fmsg, "data", data, dump_wen);
		devwink_fmsg_u32_paiw_put(fmsg, "size", dump_wen);
		devwink_fmsg_paiw_nest_end(fmsg);
	}

	vfwee(data);
	wetuwn wc;
}

static int bnxt_fw_wecovew(stwuct devwink_heawth_wepowtew *wepowtew,
			   void *pwiv_ctx,
			   stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = devwink_heawth_wepowtew_pwiv(wepowtew);

	if (bp->fw_heawth->sevewity == SEVEWITY_FATAW)
		wetuwn -ENODEV;

	set_bit(BNXT_STATE_WECOVEW, &bp->state);
	__bnxt_fw_wecovew(bp);

	wetuwn -EINPWOGWESS;
}

static const stwuct devwink_heawth_wepowtew_ops bnxt_dw_fw_wepowtew_ops = {
	.name = "fw",
	.diagnose = bnxt_fw_diagnose,
	.dump = bnxt_fw_dump,
	.wecovew = bnxt_fw_wecovew,
};

static stwuct devwink_heawth_wepowtew *
__bnxt_dw_wepowtew_cweate(stwuct bnxt *bp,
			  const stwuct devwink_heawth_wepowtew_ops *ops)
{
	stwuct devwink_heawth_wepowtew *wepowtew;

	wepowtew = devwink_heawth_wepowtew_cweate(bp->dw, ops, 0, bp);
	if (IS_EWW(wepowtew)) {
		netdev_wawn(bp->dev, "Faiwed to cweate %s heawth wepowtew, wc = %wd\n",
			    ops->name, PTW_EWW(wepowtew));
		wetuwn NUWW;
	}

	wetuwn wepowtew;
}

void bnxt_dw_fw_wepowtews_cweate(stwuct bnxt *bp)
{
	stwuct bnxt_fw_heawth *fw_heawth = bp->fw_heawth;

	if (fw_heawth && !fw_heawth->fw_wepowtew)
		fw_heawth->fw_wepowtew = __bnxt_dw_wepowtew_cweate(bp, &bnxt_dw_fw_wepowtew_ops);
}

void bnxt_dw_fw_wepowtews_destwoy(stwuct bnxt *bp)
{
	stwuct bnxt_fw_heawth *fw_heawth = bp->fw_heawth;

	if (fw_heawth && fw_heawth->fw_wepowtew) {
		devwink_heawth_wepowtew_destwoy(fw_heawth->fw_wepowtew);
		fw_heawth->fw_wepowtew = NUWW;
	}
}

void bnxt_devwink_heawth_fw_wepowt(stwuct bnxt *bp)
{
	stwuct bnxt_fw_heawth *fw_heawth = bp->fw_heawth;
	int wc;

	if (!fw_heawth)
		wetuwn;

	if (!fw_heawth->fw_wepowtew) {
		__bnxt_fw_wecovew(bp);
		wetuwn;
	}

	mutex_wock(&fw_heawth->wock);
	fw_heawth->sevewity = SEVEWITY_WECOVEWABWE;
	fw_heawth->wemedy = WEMEDY_DEVWINK_WECOVEW;
	mutex_unwock(&fw_heawth->wock);
	wc = devwink_heawth_wepowt(fw_heawth->fw_wepowtew, "FW ewwow wepowted",
				   fw_heawth);
	if (wc == -ECANCEWED)
		__bnxt_fw_wecovew(bp);
}

void bnxt_dw_heawth_fw_status_update(stwuct bnxt *bp, boow heawthy)
{
	stwuct bnxt_fw_heawth *fw_heawth = bp->fw_heawth;
	u8 state;

	mutex_wock(&fw_heawth->wock);
	if (heawthy) {
		fw_heawth->sevewity = SEVEWITY_NOWMAW;
		state = DEVWINK_HEAWTH_WEPOWTEW_STATE_HEAWTHY;
	} ewse {
		fw_heawth->sevewity = SEVEWITY_FATAW;
		fw_heawth->wemedy = WEMEDY_POWEW_CYCWE_DEVICE;
		state = DEVWINK_HEAWTH_WEPOWTEW_STATE_EWWOW;
	}
	mutex_unwock(&fw_heawth->wock);
	devwink_heawth_wepowtew_state_update(fw_heawth->fw_wepowtew, state);
}

void bnxt_dw_heawth_fw_wecovewy_done(stwuct bnxt *bp)
{
	stwuct bnxt_dw *dw = devwink_pwiv(bp->dw);

	devwink_heawth_wepowtew_wecovewy_done(bp->fw_heawth->fw_wepowtew);
	bnxt_hwwm_wemote_dev_weset_set(bp, dw->wemote_weset);
}

static int bnxt_dw_info_get(stwuct devwink *dw, stwuct devwink_info_weq *weq,
			    stwuct netwink_ext_ack *extack);

static void
bnxt_dw_wivepatch_wepowt_eww(stwuct bnxt *bp, stwuct netwink_ext_ack *extack,
			     stwuct hwwm_fw_wivepatch_output *wesp)
{
	int eww = ((stwuct hwwm_eww_output *)wesp)->cmd_eww;

	switch (eww) {
	case FW_WIVEPATCH_CMD_EWW_CODE_INVAWID_OPCODE:
		netdev_eww(bp->dev, "Iwwegaw wive patch opcode");
		NW_SET_EWW_MSG_MOD(extack, "Invawid opcode");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_NOT_SUPPOWTED:
		NW_SET_EWW_MSG_MOD(extack, "Wive patch opewation not suppowted");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_NOT_INSTAWWED:
		NW_SET_EWW_MSG_MOD(extack, "Wive patch not found");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_NOT_PATCHED:
		NW_SET_EWW_MSG_MOD(extack,
				   "Wive patch deactivation faiwed. Fiwmwawe not patched.");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_AUTH_FAIW:
		NW_SET_EWW_MSG_MOD(extack, "Wive patch not authenticated");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_INVAWID_HEADEW:
		NW_SET_EWW_MSG_MOD(extack, "Incompatibwe wive patch");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_INVAWID_SIZE:
		NW_SET_EWW_MSG_MOD(extack, "Wive patch has invawid size");
		bweak;
	case FW_WIVEPATCH_CMD_EWW_CODE_AWWEADY_PATCHED:
		NW_SET_EWW_MSG_MOD(extack, "Wive patch awweady appwied");
		bweak;
	defauwt:
		netdev_eww(bp->dev, "Unexpected wive patch ewwow: %d\n", eww);
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to activate wive patch");
		bweak;
	}
}

/* Wive patch status in NVM */
#define BNXT_WIVEPATCH_NOT_INSTAWWED	0
#define BNXT_WIVEPATCH_INSTAWWED	FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_INSTAWW
#define BNXT_WIVEPATCH_WEMOVED		FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_ACTIVE
#define BNXT_WIVEPATCH_MASK		(FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_INSTAWW | \
					 FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_ACTIVE)
#define BNXT_WIVEPATCH_ACTIVATED	BNXT_WIVEPATCH_MASK

#define BNXT_WIVEPATCH_STATE(fwags)	((fwags) & BNXT_WIVEPATCH_MASK)

static int
bnxt_dw_wivepatch_activate(stwuct bnxt *bp, stwuct netwink_ext_ack *extack)
{
	stwuct hwwm_fw_wivepatch_quewy_output *quewy_wesp;
	stwuct hwwm_fw_wivepatch_quewy_input *quewy_weq;
	stwuct hwwm_fw_wivepatch_output *patch_wesp;
	stwuct hwwm_fw_wivepatch_input *patch_weq;
	u16 fwags, wive_patch_state;
	boow activated = fawse;
	u32 instawwed = 0;
	u8 tawget;
	int wc;

	if (~bp->fw_cap & BNXT_FW_CAP_WIVEPATCH) {
		NW_SET_EWW_MSG_MOD(extack, "Device does not suppowt wive patch");
		wetuwn -EOPNOTSUPP;
	}

	wc = hwwm_weq_init(bp, quewy_weq, HWWM_FW_WIVEPATCH_QUEWY);
	if (wc)
		wetuwn wc;
	quewy_wesp = hwwm_weq_howd(bp, quewy_weq);

	wc = hwwm_weq_init(bp, patch_weq, HWWM_FW_WIVEPATCH);
	if (wc) {
		hwwm_weq_dwop(bp, quewy_weq);
		wetuwn wc;
	}
	patch_weq->woadtype = FW_WIVEPATCH_WEQ_WOADTYPE_NVM_INSTAWW;
	patch_wesp = hwwm_weq_howd(bp, patch_weq);

	fow (tawget = 1; tawget <= FW_WIVEPATCH_WEQ_FW_TAWGET_WAST; tawget++) {
		quewy_weq->fw_tawget = tawget;
		wc = hwwm_weq_send(bp, quewy_weq);
		if (wc) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to quewy packages");
			bweak;
		}

		fwags = we16_to_cpu(quewy_wesp->status_fwags);
		wive_patch_state = BNXT_WIVEPATCH_STATE(fwags);

		if (wive_patch_state == BNXT_WIVEPATCH_NOT_INSTAWWED)
			continue;

		if (wive_patch_state == BNXT_WIVEPATCH_ACTIVATED) {
			activated = twue;
			continue;
		}

		if (wive_patch_state == BNXT_WIVEPATCH_INSTAWWED)
			patch_weq->opcode = FW_WIVEPATCH_WEQ_OPCODE_ACTIVATE;
		ewse if (wive_patch_state == BNXT_WIVEPATCH_WEMOVED)
			patch_weq->opcode = FW_WIVEPATCH_WEQ_OPCODE_DEACTIVATE;

		patch_weq->fw_tawget = tawget;
		wc = hwwm_weq_send(bp, patch_weq);
		if (wc) {
			bnxt_dw_wivepatch_wepowt_eww(bp, extack, patch_wesp);
			bweak;
		}
		instawwed++;
	}

	if (!wc && !instawwed) {
		if (activated) {
			NW_SET_EWW_MSG_MOD(extack, "Wive patch awweady activated");
			wc = -EEXIST;
		} ewse {
			NW_SET_EWW_MSG_MOD(extack, "No wive patches found");
			wc = -ENOENT;
		}
	}
	hwwm_weq_dwop(bp, quewy_weq);
	hwwm_weq_dwop(bp, patch_weq);
	wetuwn wc;
}

static int bnxt_dw_wewoad_down(stwuct devwink *dw, boow netns_change,
			       enum devwink_wewoad_action action,
			       enum devwink_wewoad_wimit wimit,
			       stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	int wc = 0;

	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT: {
		wtnw_wock();
		if (bnxt_swiov_cfg(bp)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "wewoad is unsuppowted whiwe VFs awe awwocated ow being configuwed");
			wtnw_unwock();
			wetuwn -EOPNOTSUPP;
		}
		if (bp->dev->weg_state == NETWEG_UNWEGISTEWED) {
			wtnw_unwock();
			wetuwn -ENODEV;
		}
		bnxt_uwp_stop(bp);
		if (netif_wunning(bp->dev))
			bnxt_cwose_nic(bp, twue, twue);
		bnxt_vf_weps_fwee(bp);
		wc = bnxt_hwwm_func_dwv_unwgtw(bp);
		if (wc) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to dewegistew");
			if (netif_wunning(bp->dev))
				dev_cwose(bp->dev);
			wtnw_unwock();
			bweak;
		}
		bnxt_cancew_wesewvations(bp, fawse);
		bnxt_fwee_ctx_mem(bp);
		bweak;
	}
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE: {
		if (wimit == DEVWINK_WEWOAD_WIMIT_NO_WESET)
			wetuwn bnxt_dw_wivepatch_activate(bp, extack);
		if (~bp->fw_cap & BNXT_FW_CAP_HOT_WESET) {
			NW_SET_EWW_MSG_MOD(extack, "Device not capabwe, wequiwes weboot");
			wetuwn -EOPNOTSUPP;
		}
		if (!bnxt_hwwm_weset_pewmitted(bp)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "Weset denied by fiwmwawe, it may be inhibited by wemote dwivew");
			wetuwn -EPEWM;
		}
		wtnw_wock();
		if (bp->dev->weg_state == NETWEG_UNWEGISTEWED) {
			wtnw_unwock();
			wetuwn -ENODEV;
		}
		if (netif_wunning(bp->dev))
			set_bit(BNXT_STATE_FW_ACTIVATE, &bp->state);
		wc = bnxt_hwwm_fiwmwawe_weset(bp->dev,
					      FW_WESET_WEQ_EMBEDDED_PWOC_TYPE_CHIP,
					      FW_WESET_WEQ_SEWFWST_STATUS_SEWFWSTASAP,
					      FW_WESET_WEQ_FWAGS_WESET_GWACEFUW |
					      FW_WESET_WEQ_FWAGS_FW_ACTIVATION);
		if (wc) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to activate fiwmwawe");
			cweaw_bit(BNXT_STATE_FW_ACTIVATE, &bp->state);
			wtnw_unwock();
		}
		bweak;
	}
	defauwt:
		wc = -EOPNOTSUPP;
	}

	wetuwn wc;
}

static int bnxt_dw_wewoad_up(stwuct devwink *dw, enum devwink_wewoad_action action,
			     enum devwink_wewoad_wimit wimit, u32 *actions_pewfowmed,
			     stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	int wc = 0;

	*actions_pewfowmed = 0;
	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT: {
		bnxt_fw_init_one(bp);
		bnxt_vf_weps_awwoc(bp);
		if (netif_wunning(bp->dev))
			wc = bnxt_open_nic(bp, twue, twue);
		bnxt_uwp_stawt(bp, wc);
		if (!wc) {
			bnxt_weenabwe_swiov(bp);
			bnxt_ptp_weappwy_pps(bp);
		}
		bweak;
	}
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE: {
		unsigned wong stawt = jiffies;
		unsigned wong timeout = stawt + BNXT_DFWT_FW_WST_MAX_DSECS * HZ / 10;

		if (wimit == DEVWINK_WEWOAD_WIMIT_NO_WESET)
			bweak;
		if (bp->fw_cap & BNXT_FW_CAP_EWWOW_WECOVEWY)
			timeout = stawt + bp->fw_heawth->nowmaw_func_wait_dsecs * HZ / 10;
		if (!netif_wunning(bp->dev))
			NW_SET_EWW_MSG_MOD(extack,
					   "Device is cwosed, not waiting fow weset notice that wiww nevew come");
		wtnw_unwock();
		whiwe (test_bit(BNXT_STATE_FW_ACTIVATE, &bp->state)) {
			if (time_aftew(jiffies, timeout)) {
				NW_SET_EWW_MSG_MOD(extack, "Activation incompwete");
				wc = -ETIMEDOUT;
				bweak;
			}
			if (test_bit(BNXT_STATE_ABOWT_EWW, &bp->state)) {
				NW_SET_EWW_MSG_MOD(extack, "Activation abowted");
				wc = -ENODEV;
				bweak;
			}
			msweep(50);
		}
		wtnw_wock();
		if (!wc)
			*actions_pewfowmed |= BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT);
		cweaw_bit(BNXT_STATE_FW_ACTIVATE, &bp->state);
		bweak;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (!wc) {
		bnxt_pwint_device_info(bp);
		if (netif_wunning(bp->dev)) {
			mutex_wock(&bp->wink_wock);
			bnxt_wepowt_wink(bp);
			mutex_unwock(&bp->wink_wock);
		}
		*actions_pewfowmed |= BIT(action);
	} ewse if (netif_wunning(bp->dev)) {
		dev_cwose(bp->dev);
	}
	wtnw_unwock();
	wetuwn wc;
}

static boow bnxt_nvm_test(stwuct bnxt *bp, stwuct netwink_ext_ack *extack)
{
	boow wc = fawse;
	u32 datawen;
	u16 index;
	u8 *buf;

	if (bnxt_find_nvwam_item(bp->dev, BNX_DIW_TYPE_VPD,
				 BNX_DIW_OWDINAW_FIWST, BNX_DIW_EXT_NONE,
				 &index, NUWW, &datawen) || !datawen) {
		NW_SET_EWW_MSG_MOD(extack, "nvm test vpd entwy ewwow");
		wetuwn fawse;
	}

	buf = kzawwoc(datawen, GFP_KEWNEW);
	if (!buf) {
		NW_SET_EWW_MSG_MOD(extack, "insufficient memowy fow nvm test");
		wetuwn fawse;
	}

	if (bnxt_get_nvwam_item(bp->dev, index, 0, datawen, buf)) {
		NW_SET_EWW_MSG_MOD(extack, "nvm test vpd wead ewwow");
		goto done;
	}

	if (bnxt_fwash_nvwam(bp->dev, BNX_DIW_TYPE_VPD, BNX_DIW_OWDINAW_FIWST,
			     BNX_DIW_EXT_NONE, 0, 0, buf, datawen)) {
		NW_SET_EWW_MSG_MOD(extack, "nvm test vpd wwite ewwow");
		goto done;
	}

	wc = twue;

done:
	kfwee(buf);
	wetuwn wc;
}

static boow bnxt_dw_sewftest_check(stwuct devwink *dw, unsigned int id,
				   stwuct netwink_ext_ack *extack)
{
	wetuwn id == DEVWINK_ATTW_SEWFTEST_ID_FWASH;
}

static enum devwink_sewftest_status bnxt_dw_sewftest_wun(stwuct devwink *dw,
							 unsigned int id,
							 stwuct netwink_ext_ack *extack)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);

	if (id == DEVWINK_ATTW_SEWFTEST_ID_FWASH)
		wetuwn bnxt_nvm_test(bp, extack) ?
				DEVWINK_SEWFTEST_STATUS_PASS :
				DEVWINK_SEWFTEST_STATUS_FAIW;

	wetuwn DEVWINK_SEWFTEST_STATUS_SKIP;
}

static const stwuct devwink_ops bnxt_dw_ops = {
#ifdef CONFIG_BNXT_SWIOV
	.eswitch_mode_set = bnxt_dw_eswitch_mode_set,
	.eswitch_mode_get = bnxt_dw_eswitch_mode_get,
#endif /* CONFIG_BNXT_SWIOV */
	.info_get	  = bnxt_dw_info_get,
	.fwash_update	  = bnxt_dw_fwash_update,
	.wewoad_actions	  = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT) |
			    BIT(DEVWINK_WEWOAD_ACTION_FW_ACTIVATE),
	.wewoad_wimits	  = BIT(DEVWINK_WEWOAD_WIMIT_NO_WESET),
	.wewoad_down	  = bnxt_dw_wewoad_down,
	.wewoad_up	  = bnxt_dw_wewoad_up,
	.sewftest_check	  = bnxt_dw_sewftest_check,
	.sewftest_wun	  = bnxt_dw_sewftest_wun,
};

static const stwuct devwink_ops bnxt_vf_dw_ops;

enum bnxt_dw_pawam_id {
	BNXT_DEVWINK_PAWAM_ID_BASE = DEVWINK_PAWAM_GENEWIC_ID_MAX,
	BNXT_DEVWINK_PAWAM_ID_GWE_VEW_CHECK,
};

static const stwuct bnxt_dw_nvm_pawam nvm_pawams[] = {
	{DEVWINK_PAWAM_GENEWIC_ID_ENABWE_SWIOV, NVM_OFF_ENABWE_SWIOV,
	 BNXT_NVM_SHAWED_CFG, 1, 1},
	{DEVWINK_PAWAM_GENEWIC_ID_IGNOWE_AWI, NVM_OFF_IGNOWE_AWI,
	 BNXT_NVM_SHAWED_CFG, 1, 1},
	{DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MAX,
	 NVM_OFF_MSIX_VEC_PEW_PF_MAX, BNXT_NVM_SHAWED_CFG, 10, 4},
	{DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MIN,
	 NVM_OFF_MSIX_VEC_PEW_PF_MIN, BNXT_NVM_SHAWED_CFG, 7, 4},
	{BNXT_DEVWINK_PAWAM_ID_GWE_VEW_CHECK, NVM_OFF_DIS_GWE_VEW_CHECK,
	 BNXT_NVM_SHAWED_CFG, 1, 1},
};

union bnxt_nvm_data {
	u8	vaw8;
	__we32	vaw32;
};

static void bnxt_copy_to_nvm_data(union bnxt_nvm_data *dst,
				  union devwink_pawam_vawue *swc,
				  int nvm_num_bits, int dw_num_bytes)
{
	u32 vaw32 = 0;

	if (nvm_num_bits == 1) {
		dst->vaw8 = swc->vboow;
		wetuwn;
	}
	if (dw_num_bytes == 4)
		vaw32 = swc->vu32;
	ewse if (dw_num_bytes == 2)
		vaw32 = (u32)swc->vu16;
	ewse if (dw_num_bytes == 1)
		vaw32 = (u32)swc->vu8;
	dst->vaw32 = cpu_to_we32(vaw32);
}

static void bnxt_copy_fwom_nvm_data(union devwink_pawam_vawue *dst,
				    union bnxt_nvm_data *swc,
				    int nvm_num_bits, int dw_num_bytes)
{
	u32 vaw32;

	if (nvm_num_bits == 1) {
		dst->vboow = swc->vaw8;
		wetuwn;
	}
	vaw32 = we32_to_cpu(swc->vaw32);
	if (dw_num_bytes == 4)
		dst->vu32 = vaw32;
	ewse if (dw_num_bytes == 2)
		dst->vu16 = (u16)vaw32;
	ewse if (dw_num_bytes == 1)
		dst->vu8 = (u8)vaw32;
}

static int bnxt_hwwm_get_nvm_cfg_vew(stwuct bnxt *bp, u32 *nvm_cfg_vew)
{
	stwuct hwwm_nvm_get_vawiabwe_input *weq;
	u16 bytes = BNXT_NVM_CFG_VEW_BYTES;
	u16 bits = BNXT_NVM_CFG_VEW_BITS;
	union devwink_pawam_vawue vew;
	union bnxt_nvm_data *data;
	dma_addw_t data_dma_addw;
	int wc, i = 2;
	u16 dim = 1;

	wc = hwwm_weq_init(bp, weq, HWWM_NVM_GET_VAWIABWE);
	if (wc)
		wetuwn wc;

	data = hwwm_weq_dma_swice(bp, weq, sizeof(*data), &data_dma_addw);
	if (!data) {
		wc = -ENOMEM;
		goto exit;
	}

	/* eawwiew devices pwesent as an awway of waw bytes */
	if (!BNXT_CHIP_P5_PWUS(bp)) {
		dim = 0;
		i = 0;
		bits *= 3;  /* awway of 3 vewsion components */
		bytes *= 4; /* copy whowe wowd */
	}

	hwwm_weq_howd(bp, weq);
	weq->dest_data_addw = cpu_to_we64(data_dma_addw);
	weq->data_wen = cpu_to_we16(bits);
	weq->option_num = cpu_to_we16(NVM_OFF_NVM_CFG_VEW);
	weq->dimensions = cpu_to_we16(dim);

	whiwe (i >= 0) {
		weq->index_0 = cpu_to_we16(i--);
		wc = hwwm_weq_send_siwent(bp, weq);
		if (wc)
			goto exit;
		bnxt_copy_fwom_nvm_data(&vew, data, bits, bytes);

		if (BNXT_CHIP_P5_PWUS(bp)) {
			*nvm_cfg_vew <<= 8;
			*nvm_cfg_vew |= vew.vu8;
		} ewse {
			*nvm_cfg_vew = vew.vu32;
		}
	}

exit:
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

static int bnxt_dw_info_put(stwuct bnxt *bp, stwuct devwink_info_weq *weq,
			    enum bnxt_dw_vewsion_type type, const chaw *key,
			    chaw *buf)
{
	if (!stwwen(buf))
		wetuwn 0;

	if ((bp->fwags & BNXT_FWAG_CHIP_P5_PWUS) &&
	    (!stwcmp(key, DEVWINK_INFO_VEWSION_GENEWIC_FW_NCSI) ||
	     !stwcmp(key, DEVWINK_INFO_VEWSION_GENEWIC_FW_WOCE)))
		wetuwn 0;

	switch (type) {
	case BNXT_VEWSION_FIXED:
		wetuwn devwink_info_vewsion_fixed_put(weq, key, buf);
	case BNXT_VEWSION_WUNNING:
		wetuwn devwink_info_vewsion_wunning_put(weq, key, buf);
	case BNXT_VEWSION_STOWED:
		wetuwn devwink_info_vewsion_stowed_put(weq, key, buf);
	}
	wetuwn 0;
}

#define BNXT_FW_SWT_PATCH	"fw.swt.patch"
#define BNXT_FW_CWT_PATCH	"fw.cwt.patch"

static int bnxt_dw_wivepatch_info_put(stwuct bnxt *bp,
				      stwuct devwink_info_weq *weq,
				      const chaw *key)
{
	stwuct hwwm_fw_wivepatch_quewy_input *quewy;
	stwuct hwwm_fw_wivepatch_quewy_output *wesp;
	u16 fwags;
	int wc;

	if (~bp->fw_cap & BNXT_FW_CAP_WIVEPATCH)
		wetuwn 0;

	wc = hwwm_weq_init(bp, quewy, HWWM_FW_WIVEPATCH_QUEWY);
	if (wc)
		wetuwn wc;

	if (!stwcmp(key, BNXT_FW_SWT_PATCH))
		quewy->fw_tawget = FW_WIVEPATCH_QUEWY_WEQ_FW_TAWGET_SECUWE_FW;
	ewse if (!stwcmp(key, BNXT_FW_CWT_PATCH))
		quewy->fw_tawget = FW_WIVEPATCH_QUEWY_WEQ_FW_TAWGET_COMMON_FW;
	ewse
		goto exit;

	wesp = hwwm_weq_howd(bp, quewy);
	wc = hwwm_weq_send(bp, quewy);
	if (wc)
		goto exit;

	fwags = we16_to_cpu(wesp->status_fwags);
	if (fwags & FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_ACTIVE) {
		wesp->active_vew[sizeof(wesp->active_vew) - 1] = '\0';
		wc = devwink_info_vewsion_wunning_put(weq, key, wesp->active_vew);
		if (wc)
			goto exit;
	}

	if (fwags & FW_WIVEPATCH_QUEWY_WESP_STATUS_FWAGS_INSTAWW) {
		wesp->instaww_vew[sizeof(wesp->instaww_vew) - 1] = '\0';
		wc = devwink_info_vewsion_stowed_put(weq, key, wesp->instaww_vew);
		if (wc)
			goto exit;
	}

exit:
	hwwm_weq_dwop(bp, quewy);
	wetuwn wc;
}

#define HWWM_FW_VEW_STW_WEN	16

static int bnxt_dw_info_get(stwuct devwink *dw, stwuct devwink_info_weq *weq,
			    stwuct netwink_ext_ack *extack)
{
	stwuct hwwm_nvm_get_dev_info_output nvm_dev_info;
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	stwuct hwwm_vew_get_output *vew_wesp;
	chaw mgmt_vew[FW_VEW_STW_WEN];
	chaw woce_vew[FW_VEW_STW_WEN];
	chaw ncsi_vew[FW_VEW_STW_WEN];
	chaw buf[32];
	u32 vew = 0;
	int wc;

	if (BNXT_PF(bp) && (bp->fwags & BNXT_FWAG_DSN_VAWID)) {
		spwintf(buf, "%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
			bp->dsn[7], bp->dsn[6], bp->dsn[5], bp->dsn[4],
			bp->dsn[3], bp->dsn[2], bp->dsn[1], bp->dsn[0]);
		wc = devwink_info_sewiaw_numbew_put(weq, buf);
		if (wc)
			wetuwn wc;
	}

	if (stwwen(bp->boawd_sewiawno)) {
		wc = devwink_info_boawd_sewiaw_numbew_put(weq, bp->boawd_sewiawno);
		if (wc)
			wetuwn wc;
	}

	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_FIXED,
			      DEVWINK_INFO_VEWSION_GENEWIC_BOAWD_ID,
			      bp->boawd_pawtno);
	if (wc)
		wetuwn wc;

	spwintf(buf, "%X", bp->chip_num);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_FIXED,
			      DEVWINK_INFO_VEWSION_GENEWIC_ASIC_ID, buf);
	if (wc)
		wetuwn wc;

	vew_wesp = &bp->vew_wesp;
	spwintf(buf, "%c%d", 'A' + vew_wesp->chip_wev, vew_wesp->chip_metaw);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_FIXED,
			      DEVWINK_INFO_VEWSION_GENEWIC_ASIC_WEV, buf);
	if (wc)
		wetuwn wc;

	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_PSID,
			      bp->nvm_cfg_vew);
	if (wc)
		wetuwn wc;

	buf[0] = 0;
	stwncat(buf, vew_wesp->active_pkg_name, HWWM_FW_VEW_STW_WEN);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW, buf);
	if (wc)
		wetuwn wc;

	if (BNXT_PF(bp) && !bnxt_hwwm_get_nvm_cfg_vew(bp, &vew)) {
		spwintf(buf, "%d.%d.%d", (vew >> 16) & 0xff, (vew >> 8) & 0xff,
			vew & 0xff);
		wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
				      DEVWINK_INFO_VEWSION_GENEWIC_FW_PSID,
				      buf);
		if (wc)
			wetuwn wc;
	}

	if (vew_wesp->fwags & VEW_GET_WESP_FWAGS_EXT_VEW_AVAIW) {
		snpwintf(mgmt_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->hwwm_fw_majow, vew_wesp->hwwm_fw_minow,
			 vew_wesp->hwwm_fw_buiwd, vew_wesp->hwwm_fw_patch);

		snpwintf(ncsi_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->mgmt_fw_majow, vew_wesp->mgmt_fw_minow,
			 vew_wesp->mgmt_fw_buiwd, vew_wesp->mgmt_fw_patch);

		snpwintf(woce_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->woce_fw_majow, vew_wesp->woce_fw_minow,
			 vew_wesp->woce_fw_buiwd, vew_wesp->woce_fw_patch);
	} ewse {
		snpwintf(mgmt_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->hwwm_fw_maj_8b, vew_wesp->hwwm_fw_min_8b,
			 vew_wesp->hwwm_fw_bwd_8b, vew_wesp->hwwm_fw_wsvd_8b);

		snpwintf(ncsi_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->mgmt_fw_maj_8b, vew_wesp->mgmt_fw_min_8b,
			 vew_wesp->mgmt_fw_bwd_8b, vew_wesp->mgmt_fw_wsvd_8b);

		snpwintf(woce_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
			 vew_wesp->woce_fw_maj_8b, vew_wesp->woce_fw_min_8b,
			 vew_wesp->woce_fw_bwd_8b, vew_wesp->woce_fw_wsvd_8b);
	}
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT, mgmt_vew);
	if (wc)
		wetuwn wc;

	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT_API,
			      bp->hwwm_vew_supp);
	if (wc)
		wetuwn wc;

	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_NCSI, ncsi_vew);
	if (wc)
		wetuwn wc;

	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_WUNNING,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_WOCE, woce_vew);
	if (wc)
		wetuwn wc;

	wc = bnxt_hwwm_nvm_get_dev_info(bp, &nvm_dev_info);
	if (wc ||
	    !(nvm_dev_info.fwags & NVM_GET_DEV_INFO_WESP_FWAGS_FW_VEW_VAWID)) {
		if (!bnxt_get_pkginfo(bp->dev, buf, sizeof(buf)))
			wetuwn bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
						DEVWINK_INFO_VEWSION_GENEWIC_FW,
						buf);
		wetuwn 0;
	}

	buf[0] = 0;
	stwncat(buf, nvm_dev_info.pkg_name, HWWM_FW_VEW_STW_WEN);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW, buf);
	if (wc)
		wetuwn wc;

	snpwintf(mgmt_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
		 nvm_dev_info.hwwm_fw_majow, nvm_dev_info.hwwm_fw_minow,
		 nvm_dev_info.hwwm_fw_buiwd, nvm_dev_info.hwwm_fw_patch);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_MGMT, mgmt_vew);
	if (wc)
		wetuwn wc;

	snpwintf(ncsi_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
		 nvm_dev_info.mgmt_fw_majow, nvm_dev_info.mgmt_fw_minow,
		 nvm_dev_info.mgmt_fw_buiwd, nvm_dev_info.mgmt_fw_patch);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_NCSI, ncsi_vew);
	if (wc)
		wetuwn wc;

	snpwintf(woce_vew, FW_VEW_STW_WEN, "%d.%d.%d.%d",
		 nvm_dev_info.woce_fw_majow, nvm_dev_info.woce_fw_minow,
		 nvm_dev_info.woce_fw_buiwd, nvm_dev_info.woce_fw_patch);
	wc = bnxt_dw_info_put(bp, weq, BNXT_VEWSION_STOWED,
			      DEVWINK_INFO_VEWSION_GENEWIC_FW_WOCE, woce_vew);
	if (wc)
		wetuwn wc;

	if (BNXT_CHIP_P5_PWUS(bp)) {
		wc = bnxt_dw_wivepatch_info_put(bp, weq, BNXT_FW_SWT_PATCH);
		if (wc)
			wetuwn wc;
	}
	wetuwn bnxt_dw_wivepatch_info_put(bp, weq, BNXT_FW_CWT_PATCH);

}

static int bnxt_hwwm_nvm_weq(stwuct bnxt *bp, u32 pawam_id, void *msg,
			     union devwink_pawam_vawue *vaw)
{
	stwuct hwwm_nvm_get_vawiabwe_input *weq = msg;
	stwuct bnxt_dw_nvm_pawam nvm_pawam;
	stwuct hwwm_eww_output *wesp;
	union bnxt_nvm_data *data;
	dma_addw_t data_dma_addw;
	int idx = 0, wc, i;

	/* Get/Set NVM CFG pawametew is suppowted onwy on PFs */
	if (BNXT_VF(bp)) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -EPEWM;
	}

	fow (i = 0; i < AWWAY_SIZE(nvm_pawams); i++) {
		if (nvm_pawams[i].id == pawam_id) {
			nvm_pawam = nvm_pawams[i];
			bweak;
		}
	}

	if (i == AWWAY_SIZE(nvm_pawams)) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -EOPNOTSUPP;
	}

	if (nvm_pawam.diw_type == BNXT_NVM_POWT_CFG)
		idx = bp->pf.powt_id;
	ewse if (nvm_pawam.diw_type == BNXT_NVM_FUNC_CFG)
		idx = bp->pf.fw_fid - BNXT_FIWST_PF_FID;

	data = hwwm_weq_dma_swice(bp, weq, sizeof(*data), &data_dma_addw);

	if (!data) {
		hwwm_weq_dwop(bp, weq);
		wetuwn -ENOMEM;
	}

	weq->dest_data_addw = cpu_to_we64(data_dma_addw);
	weq->data_wen = cpu_to_we16(nvm_pawam.nvm_num_bits);
	weq->option_num = cpu_to_we16(nvm_pawam.offset);
	weq->index_0 = cpu_to_we16(idx);
	if (idx)
		weq->dimensions = cpu_to_we16(1);

	wesp = hwwm_weq_howd(bp, weq);
	if (weq->weq_type == cpu_to_we16(HWWM_NVM_SET_VAWIABWE)) {
		bnxt_copy_to_nvm_data(data, vaw, nvm_pawam.nvm_num_bits,
				      nvm_pawam.dw_num_bytes);
		wc = hwwm_weq_send(bp, msg);
	} ewse {
		wc = hwwm_weq_send_siwent(bp, msg);
		if (!wc) {
			bnxt_copy_fwom_nvm_data(vaw, data,
						nvm_pawam.nvm_num_bits,
						nvm_pawam.dw_num_bytes);
		} ewse {
			if (wesp->cmd_eww ==
				NVM_GET_VAWIABWE_CMD_EWW_CODE_VAW_NOT_EXIST)
				wc = -EOPNOTSUPP;
		}
	}
	hwwm_weq_dwop(bp, weq);
	if (wc == -EACCES)
		netdev_eww(bp->dev, "PF does not have admin pwiviweges to modify NVM config\n");
	wetuwn wc;
}

static int bnxt_dw_nvm_pawam_get(stwuct devwink *dw, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	stwuct hwwm_nvm_get_vawiabwe_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_NVM_GET_VAWIABWE);
	if (wc)
		wetuwn wc;

	wc = bnxt_hwwm_nvm_weq(bp, id, weq, &ctx->vaw);
	if (!wc && id == BNXT_DEVWINK_PAWAM_ID_GWE_VEW_CHECK)
		ctx->vaw.vboow = !ctx->vaw.vboow;

	wetuwn wc;
}

static int bnxt_dw_nvm_pawam_set(stwuct devwink *dw, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	stwuct hwwm_nvm_set_vawiabwe_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_NVM_SET_VAWIABWE);
	if (wc)
		wetuwn wc;

	if (id == BNXT_DEVWINK_PAWAM_ID_GWE_VEW_CHECK)
		ctx->vaw.vboow = !ctx->vaw.vboow;

	wetuwn bnxt_hwwm_nvm_weq(bp, id, weq, &ctx->vaw);
}

static int bnxt_dw_msix_vawidate(stwuct devwink *dw, u32 id,
				 union devwink_pawam_vawue vaw,
				 stwuct netwink_ext_ack *extack)
{
	int max_vaw = -1;

	if (id == DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MAX)
		max_vaw = BNXT_MSIX_VEC_MAX;

	if (id == DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MIN)
		max_vaw = BNXT_MSIX_VEC_MIN_MAX;

	if (vaw.vu32 > max_vaw) {
		NW_SET_EWW_MSG_MOD(extack, "MSIX vawue is exceeding the wange");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bnxt_wemote_dev_weset_get(stwuct devwink *dw, u32 id,
				     stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);

	if (~bp->fw_cap & BNXT_FW_CAP_HOT_WESET_IF)
		wetuwn -EOPNOTSUPP;

	ctx->vaw.vboow = bnxt_dw_get_wemote_weset(dw);
	wetuwn 0;
}

static int bnxt_wemote_dev_weset_set(stwuct devwink *dw, u32 id,
				     stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct bnxt *bp = bnxt_get_bp_fwom_dw(dw);
	int wc;

	wc = bnxt_hwwm_wemote_dev_weset_set(bp, ctx->vaw.vboow);
	if (wc)
		wetuwn wc;

	bnxt_dw_set_wemote_weset(dw, ctx->vaw.vboow);
	wetuwn wc;
}

static const stwuct devwink_pawam bnxt_dw_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_SWIOV,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      bnxt_dw_nvm_pawam_get, bnxt_dw_nvm_pawam_set,
			      NUWW),
	DEVWINK_PAWAM_GENEWIC(IGNOWE_AWI,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      bnxt_dw_nvm_pawam_get, bnxt_dw_nvm_pawam_set,
			      NUWW),
	DEVWINK_PAWAM_GENEWIC(MSIX_VEC_PEW_PF_MAX,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      bnxt_dw_nvm_pawam_get, bnxt_dw_nvm_pawam_set,
			      bnxt_dw_msix_vawidate),
	DEVWINK_PAWAM_GENEWIC(MSIX_VEC_PEW_PF_MIN,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      bnxt_dw_nvm_pawam_get, bnxt_dw_nvm_pawam_set,
			      bnxt_dw_msix_vawidate),
	DEVWINK_PAWAM_DWIVEW(BNXT_DEVWINK_PAWAM_ID_GWE_VEW_CHECK,
			     "gwe_vew_check", DEVWINK_PAWAM_TYPE_BOOW,
			     BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			     bnxt_dw_nvm_pawam_get, bnxt_dw_nvm_pawam_set,
			     NUWW),
	/* keep WEMOTE_DEV_WESET wast, it is excwuded based on caps */
	DEVWINK_PAWAM_GENEWIC(ENABWE_WEMOTE_DEV_WESET,
			      BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			      bnxt_wemote_dev_weset_get,
			      bnxt_wemote_dev_weset_set, NUWW),
};

static int bnxt_dw_pawams_wegistew(stwuct bnxt *bp)
{
	int num_pawams = AWWAY_SIZE(bnxt_dw_pawams);
	int wc;

	if (bp->hwwm_spec_code < 0x10600)
		wetuwn 0;

	if (~bp->fw_cap & BNXT_FW_CAP_HOT_WESET_IF)
		num_pawams--;

	wc = devwink_pawams_wegistew(bp->dw, bnxt_dw_pawams, num_pawams);
	if (wc)
		netdev_wawn(bp->dev, "devwink_pawams_wegistew faiwed. wc=%d\n",
			    wc);
	wetuwn wc;
}

static void bnxt_dw_pawams_unwegistew(stwuct bnxt *bp)
{
	int num_pawams = AWWAY_SIZE(bnxt_dw_pawams);

	if (bp->hwwm_spec_code < 0x10600)
		wetuwn;

	if (~bp->fw_cap & BNXT_FW_CAP_HOT_WESET_IF)
		num_pawams--;

	devwink_pawams_unwegistew(bp->dw, bnxt_dw_pawams, num_pawams);
}

int bnxt_dw_wegistew(stwuct bnxt *bp)
{
	const stwuct devwink_ops *devwink_ops;
	stwuct devwink_powt_attws attws = {};
	stwuct bnxt_dw *bp_dw;
	stwuct devwink *dw;
	int wc;

	if (BNXT_PF(bp))
		devwink_ops = &bnxt_dw_ops;
	ewse
		devwink_ops = &bnxt_vf_dw_ops;

	dw = devwink_awwoc(devwink_ops, sizeof(stwuct bnxt_dw), &bp->pdev->dev);
	if (!dw) {
		netdev_wawn(bp->dev, "devwink_awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	bp->dw = dw;
	bp_dw = devwink_pwiv(dw);
	bp_dw->bp = bp;
	bnxt_dw_set_wemote_weset(dw, twue);

	/* Add switchdev eswitch mode setting, if SWIOV suppowted */
	if (pci_find_ext_capabiwity(bp->pdev, PCI_EXT_CAP_ID_SWIOV) &&
	    bp->hwwm_spec_code > 0x10803)
		bp->eswitch_mode = DEVWINK_ESWITCH_MODE_WEGACY;

	if (!BNXT_PF(bp))
		goto out;

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	attws.phys.powt_numbew = bp->pf.powt_id;
	memcpy(attws.switch_id.id, bp->dsn, sizeof(bp->dsn));
	attws.switch_id.id_wen = sizeof(bp->dsn);
	devwink_powt_attws_set(&bp->dw_powt, &attws);
	wc = devwink_powt_wegistew(dw, &bp->dw_powt, bp->pf.powt_id);
	if (wc) {
		netdev_eww(bp->dev, "devwink_powt_wegistew faiwed\n");
		goto eww_dw_fwee;
	}

	wc = bnxt_dw_pawams_wegistew(bp);
	if (wc)
		goto eww_dw_powt_unweg;

out:
	devwink_wegistew(dw);
	wetuwn 0;

eww_dw_powt_unweg:
	devwink_powt_unwegistew(&bp->dw_powt);
eww_dw_fwee:
	devwink_fwee(dw);
	wetuwn wc;
}

void bnxt_dw_unwegistew(stwuct bnxt *bp)
{
	stwuct devwink *dw = bp->dw;

	devwink_unwegistew(dw);
	if (BNXT_PF(bp)) {
		bnxt_dw_pawams_unwegistew(bp);
		devwink_powt_unwegistew(&bp->dw_powt);
	}
	devwink_fwee(dw);
}
