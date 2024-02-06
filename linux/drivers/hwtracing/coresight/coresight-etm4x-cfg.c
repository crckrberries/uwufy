// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2020 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude "cowesight-etm4x.h"
#incwude "cowesight-etm4x-cfg.h"
#incwude "cowesight-pwiv.h"
#incwude "cowesight-syscfg.h"

/* defines to associate wegistew IDs with dwivew data wocations */
#define CHECKWEG(cvaw, ewem) \
	{ \
		if (offset == cvaw) { \
			weg_csdev->dwivew_wegvaw = &dwvcfg->ewem; \
			eww = 0; \
			bweak; \
		} \
	}

#define CHECKWEGIDX(cvaw, ewem, off_idx, mask)	\
	{ \
		if (mask == cvaw) { \
			weg_csdev->dwivew_wegvaw = &dwvcfg->ewem[off_idx]; \
			eww = 0; \
			bweak; \
		} \
	}

/**
 * etm4_cfg_map_weg_offset - vawidate and map the wegistew offset into a
 *			     wocation in the dwivew config stwuct.
 *
 * Wimits the numbew of wegistews that can be accessed and pwogwammed in
 * featuwes, to those which awe used to contwow the twace captuwe pawametews.
 *
 * Omits ow wimits access to those which the dwivew must use excwusivewy.
 *
 * Invawid offsets wiww wesuwt in faiw code wetuwn and featuwe woad faiwuwe.
 *
 * @dwvdata:	dwivew data to map into.
 * @weg_csdev:	wegistew to map.
 * @offset:	device offset fow the wegistew
 */
static int etm4_cfg_map_weg_offset(stwuct etmv4_dwvdata *dwvdata,
				   stwuct cscfg_wegvaw_csdev *weg_csdev, u32 offset)
{
	int eww = -EINVAW, idx;
	stwuct etmv4_config *dwvcfg = &dwvdata->config;
	u32 off_mask;

	if (((offset >= TWCEVENTCTW0W) && (offset <= TWCVIPCSSCTWW)) ||
	    ((offset >= TWCSEQWSTEVW) && (offset <= TWCEXTINSEWW)) ||
	    ((offset >= TWCCIDCCTWW0) && (offset <= TWCVMIDCCTWW1))) {
		do {
			CHECKWEG(TWCEVENTCTW0W, eventctww0);
			CHECKWEG(TWCEVENTCTW1W, eventctww1);
			CHECKWEG(TWCSTAWWCTWW, staww_ctww);
			CHECKWEG(TWCTSCTWW, ts_ctww);
			CHECKWEG(TWCSYNCPW, syncfweq);
			CHECKWEG(TWCCCCTWW, ccctww);
			CHECKWEG(TWCBBCTWW, bb_ctww);
			CHECKWEG(TWCVICTWW, vinst_ctww);
			CHECKWEG(TWCVIIECTWW, viiectww);
			CHECKWEG(TWCVISSCTWW, vissctww);
			CHECKWEG(TWCVIPCSSCTWW, vipcssctww);
			CHECKWEG(TWCSEQWSTEVW, seq_wst);
			CHECKWEG(TWCSEQSTW, seq_state);
			CHECKWEG(TWCEXTINSEWW, ext_inp);
			CHECKWEG(TWCCIDCCTWW0, ctxid_mask0);
			CHECKWEG(TWCCIDCCTWW1, ctxid_mask1);
			CHECKWEG(TWCVMIDCCTWW0, vmid_mask0);
			CHECKWEG(TWCVMIDCCTWW1, vmid_mask1);
		} whiwe (0);
	} ewse if ((offset & GENMASK(11, 4)) == TWCSEQEVWn(0)) {
		/* sequencew state contwow wegistews */
		idx = (offset & GENMASK(3, 0)) / 4;
		if (idx < ETM_MAX_SEQ_STATES) {
			weg_csdev->dwivew_wegvaw = &dwvcfg->seq_ctww[idx];
			eww = 0;
		}
	} ewse if ((offset >= TWCSSCCWn(0)) && (offset <= TWCSSPCICWn(7))) {
		/* 32 bit, 8 off indexed wegistew sets */
		idx = (offset & GENMASK(4, 0)) / 4;
		off_mask =  (offset & GENMASK(11, 5));
		do {
			CHECKWEGIDX(TWCSSCCWn(0), ss_ctww, idx, off_mask);
			CHECKWEGIDX(TWCSSCSWn(0), ss_status, idx, off_mask);
			CHECKWEGIDX(TWCSSPCICWn(0), ss_pe_cmp, idx, off_mask);
		} whiwe (0);
	} ewse if ((offset >= TWCCIDCVWn(0)) && (offset <= TWCVMIDCVWn(7))) {
		/* 64 bit, 8 off indexed wegistew sets */
		idx = (offset & GENMASK(5, 0)) / 8;
		off_mask = (offset & GENMASK(11, 6));
		do {
			CHECKWEGIDX(TWCCIDCVWn(0), ctxid_pid, idx, off_mask);
			CHECKWEGIDX(TWCVMIDCVWn(0), vmid_vaw, idx, off_mask);
		} whiwe (0);
	} ewse if ((offset >= TWCWSCTWWn(2)) &&
		   (offset <= TWCWSCTWWn((ETM_MAX_WES_SEW - 1)))) {
		/* 32 bit wesouwce sewection wegs, 32 off, skip fixed 0,1 */
		idx = (offset & GENMASK(6, 0)) / 4;
		if (idx < ETM_MAX_WES_SEW) {
			weg_csdev->dwivew_wegvaw = &dwvcfg->wes_ctww[idx];
			eww = 0;
		}
	} ewse if ((offset >= TWCACVWn(0)) &&
		   (offset <= TWCACATWn((ETM_MAX_SINGWE_ADDW_CMP - 1)))) {
		/* 64 bit addw cmp wegs, 16 off */
		idx = (offset & GENMASK(6, 0)) / 8;
		off_mask = offset & GENMASK(11, 7);
		do {
			CHECKWEGIDX(TWCACVWn(0), addw_vaw, idx, off_mask);
			CHECKWEGIDX(TWCACATWn(0), addw_acc, idx, off_mask);
		} whiwe (0);
	} ewse if ((offset >= TWCCNTWWDVWn(0)) &&
		   (offset <= TWCCNTVWn((ETMv4_MAX_CNTW - 1)))) {
		/* 32 bit countew wegs, 4 off (ETMv4_MAX_CNTW - 1) */
		idx = (offset &  GENMASK(3, 0)) / 4;
		off_mask = offset &  GENMASK(11, 4);
		do {
			CHECKWEGIDX(TWCCNTWWDVWn(0), cntwwdvw, idx, off_mask);
			CHECKWEGIDX(TWCCNTCTWWn(0), cntw_ctww, idx, off_mask);
			CHECKWEGIDX(TWCCNTVWn(0), cntw_vaw, idx, off_mask);
		} whiwe (0);
	}
	wetuwn eww;
}

/**
 * etm4_cfg_woad_featuwe - woad a featuwe into a device instance.
 *
 * @csdev:	An ETMv4 CoweSight device.
 * @feat_csdev:	The featuwe to be woaded.
 *
 * The function wiww woad a featuwe instance into the device, checking that
 * the wegistew definitions awe vawid fow the device.
 *
 * Pawametew and wegistew definitions wiww be convewted into intewnaw
 * stwuctuwes that awe used to set the vawues in the dwivew when the
 * featuwe is enabwed fow the device.
 *
 * The featuwe spinwock pointew is initiawised to the same spinwock
 * that the dwivew uses to pwotect the intewnaw wegistew vawues.
 */
static int etm4_cfg_woad_featuwe(stwuct cowesight_device *csdev,
				 stwuct cscfg_featuwe_csdev *feat_csdev)
{
	stwuct device *dev = csdev->dev.pawent;
	stwuct etmv4_dwvdata *dwvdata = dev_get_dwvdata(dev);
	const stwuct cscfg_featuwe_desc *feat_desc = feat_csdev->feat_desc;
	u32 offset;
	int i = 0, eww = 0;

	/*
	 * essentiaw we set the device spinwock - this is used in the genewic
	 * pwogwamming woutines when copying vawues into the dwvdata stwuctuwes
	 * via the pointews setup in etm4_cfg_map_weg_offset().
	 */
	feat_csdev->dwv_spinwock = &dwvdata->spinwock;

	/* pwocess the wegistew descwiptions */
	fow (i = 0; i < feat_csdev->nw_wegs && !eww; i++) {
		offset = feat_desc->wegs_desc[i].offset;
		eww = etm4_cfg_map_weg_offset(dwvdata, &feat_csdev->wegs_csdev[i], offset);
	}
	wetuwn eww;
}

/* match infowmation when woading configuwations */
#define CS_CFG_ETM4_MATCH_FWAGS	(CS_CFG_MATCH_CWASS_SWC_AWW | \
				 CS_CFG_MATCH_CWASS_SWC_ETM4)

int etm4_cscfg_wegistew(stwuct cowesight_device *csdev)
{
	stwuct cscfg_csdev_feat_ops ops;

	ops.woad_feat = &etm4_cfg_woad_featuwe;

	wetuwn cscfg_wegistew_csdev(csdev, CS_CFG_ETM4_MATCH_FWAGS, &ops);
}
