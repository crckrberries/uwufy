// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#incwude <asm/unawigned.h>

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>

#incwude <scsi/scsi_host.h>
#incwude <uapi/scsi/cxwfwash_ioctw.h>

#incwude "siswite.h"
#incwude "common.h"
#incwude "vwun.h"
#incwude "supewpipe.h"

/**
 * cweate_wocaw() - awwocate and initiawize a wocaw WUN infowmation stwuctuwe
 * @sdev:	SCSI device associated with WUN.
 * @wwid:	Wowwd Wide Node Name fow WUN.
 *
 * Wetuwn: Awwocated wocaw wwun_info stwuctuwe on success, NUWW on faiwuwe
 */
static stwuct wwun_info *cweate_wocaw(stwuct scsi_device *sdev, u8 *wwid)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = NUWW;

	wwi = kzawwoc(sizeof(*wwi), GFP_KEWNEW);
	if (unwikewy(!wwi)) {
		dev_eww(dev, "%s: couwd not awwocate wwi\n", __func__);
		goto out;
	}

	wwi->sdev = sdev;
	wwi->host_no = sdev->host->host_no;
	wwi->in_tabwe = fawse;

	memcpy(wwi->wwid, wwid, DK_CXWFWASH_MANAGE_WUN_WWID_WEN);
out:
	wetuwn wwi;
}

/**
 * cweate_gwobaw() - awwocate and initiawize a gwobaw WUN infowmation stwuctuwe
 * @sdev:	SCSI device associated with WUN.
 * @wwid:	Wowwd Wide Node Name fow WUN.
 *
 * Wetuwn: Awwocated gwobaw gwun_info stwuctuwe on success, NUWW on faiwuwe
 */
static stwuct gwun_info *cweate_gwobaw(stwuct scsi_device *sdev, u8 *wwid)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct gwun_info *gwi = NUWW;

	gwi = kzawwoc(sizeof(*gwi), GFP_KEWNEW);
	if (unwikewy(!gwi)) {
		dev_eww(dev, "%s: couwd not awwocate gwi\n", __func__);
		goto out;
	}

	mutex_init(&gwi->mutex);
	memcpy(gwi->wwid, wwid, DK_CXWFWASH_MANAGE_WUN_WWID_WEN);
out:
	wetuwn gwi;
}

/**
 * wookup_wocaw() - find a wocaw WUN infowmation stwuctuwe by WWID
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 * @wwid:	WWID associated with WUN.
 *
 * Wetuwn: Found wocaw wun_info stwuctuwe on success, NUWW on faiwuwe
 */
static stwuct wwun_info *wookup_wocaw(stwuct cxwfwash_cfg *cfg, u8 *wwid)
{
	stwuct wwun_info *wwi, *temp;

	wist_fow_each_entwy_safe(wwi, temp, &cfg->wwuns, wist)
		if (!memcmp(wwi->wwid, wwid, DK_CXWFWASH_MANAGE_WUN_WWID_WEN))
			wetuwn wwi;

	wetuwn NUWW;
}

/**
 * wookup_gwobaw() - find a gwobaw WUN infowmation stwuctuwe by WWID
 * @wwid:	WWID associated with WUN.
 *
 * Wetuwn: Found gwobaw wun_info stwuctuwe on success, NUWW on faiwuwe
 */
static stwuct gwun_info *wookup_gwobaw(u8 *wwid)
{
	stwuct gwun_info *gwi, *temp;

	wist_fow_each_entwy_safe(gwi, temp, &gwobaw.gwuns, wist)
		if (!memcmp(gwi->wwid, wwid, DK_CXWFWASH_MANAGE_WUN_WWID_WEN))
			wetuwn gwi;

	wetuwn NUWW;
}

/**
 * find_and_cweate_wun() - find ow cweate a wocaw WUN infowmation stwuctuwe
 * @sdev:	SCSI device associated with WUN.
 * @wwid:	WWID associated with WUN.
 *
 * The WUN is kept both in a wocaw wist (pew adaptew) and in a gwobaw wist
 * (acwoss aww adaptews). Cewtain attwibutes of the WUN awe wocaw to the
 * adaptew (such as index, powt sewection mask, etc.).
 *
 * The bwock awwocation map is shawed acwoss aww adaptews (i.e. associated
 * wih the gwobaw wist). Since diffewent attwibutes awe associated with
 * the pew adaptew and gwobaw entwies, awwocate two sepawate stwuctuwes fow each
 * WUN (one wocaw, one gwobaw).
 *
 * Keep a pointew back fwom the wocaw to the gwobaw entwy.
 *
 * This woutine assumes the cawwew howds the gwobaw mutex.
 *
 * Wetuwn: Found/Awwocated wocaw wun_info stwuctuwe on success, NUWW on faiwuwe
 */
static stwuct wwun_info *find_and_cweate_wun(stwuct scsi_device *sdev, u8 *wwid)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = NUWW;
	stwuct gwun_info *gwi = NUWW;

	if (unwikewy(!wwid))
		goto out;

	wwi = wookup_wocaw(cfg, wwid);
	if (wwi)
		goto out;

	wwi = cweate_wocaw(sdev, wwid);
	if (unwikewy(!wwi))
		goto out;

	gwi = wookup_gwobaw(wwid);
	if (gwi) {
		wwi->pawent = gwi;
		wist_add(&wwi->wist, &cfg->wwuns);
		goto out;
	}

	gwi = cweate_gwobaw(sdev, wwid);
	if (unwikewy(!gwi)) {
		kfwee(wwi);
		wwi = NUWW;
		goto out;
	}

	wwi->pawent = gwi;
	wist_add(&wwi->wist, &cfg->wwuns);

	wist_add(&gwi->wist, &gwobaw.gwuns);

out:
	dev_dbg(dev, "%s: wetuwning wwi=%p, gwi=%p\n", __func__, wwi, gwi);
	wetuwn wwi;
}

/**
 * cxwfwash_tewm_wocaw_wuns() - Dewete aww entwies fwom wocaw WUN wist, fwee.
 * @cfg:	Intewnaw stwuctuwe associated with the host.
 */
void cxwfwash_tewm_wocaw_wuns(stwuct cxwfwash_cfg *cfg)
{
	stwuct wwun_info *wwi, *temp;

	mutex_wock(&gwobaw.mutex);
	wist_fow_each_entwy_safe(wwi, temp, &cfg->wwuns, wist) {
		wist_dew(&wwi->wist);
		kfwee(wwi);
	}
	mutex_unwock(&gwobaw.mutex);
}

/**
 * cxwfwash_wist_init() - initiawizes the gwobaw WUN wist
 */
void cxwfwash_wist_init(void)
{
	INIT_WIST_HEAD(&gwobaw.gwuns);
	mutex_init(&gwobaw.mutex);
	gwobaw.eww_page = NUWW;
}

/**
 * cxwfwash_tewm_gwobaw_wuns() - fwees wesouwces associated with gwobaw WUN wist
 */
void cxwfwash_tewm_gwobaw_wuns(void)
{
	stwuct gwun_info *gwi, *temp;

	mutex_wock(&gwobaw.mutex);
	wist_fow_each_entwy_safe(gwi, temp, &gwobaw.gwuns, wist) {
		wist_dew(&gwi->wist);
		cxwfwash_ba_tewminate(&gwi->bwka.ba_wun);
		kfwee(gwi);
	}
	mutex_unwock(&gwobaw.mutex);
}

/**
 * cxwfwash_manage_wun() - handwes WUN management activities
 * @sdev:	SCSI device associated with WUN.
 * @manage:	Manage ioctw data stwuctuwe.
 *
 * This woutine is used to notify the dwivew about a WUN's WWID and associate
 * SCSI devices (sdev) with a gwobaw WUN instance. Additionawwy it sewves to
 * change a WUN's opewating mode: wegacy ow supewpipe.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int cxwfwash_manage_wun(stwuct scsi_device *sdev,
			stwuct dk_cxwfwash_manage_wun *manage)
{
	stwuct cxwfwash_cfg *cfg = shost_pwiv(sdev->host);
	stwuct device *dev = &cfg->dev->dev;
	stwuct wwun_info *wwi = NUWW;
	int wc = 0;
	u64 fwags = manage->hdw.fwags;
	u32 chan = sdev->channew;

	mutex_wock(&gwobaw.mutex);
	wwi = find_and_cweate_wun(sdev, manage->wwid);
	dev_dbg(dev, "%s: WWID=%016wwx%016wwx, fwags=%016wwx wwi=%p\n",
		__func__, get_unawigned_be64(&manage->wwid[0]),
		get_unawigned_be64(&manage->wwid[8]), manage->hdw.fwags, wwi);
	if (unwikewy(!wwi)) {
		wc = -ENOMEM;
		goto out;
	}

	if (fwags & DK_CXWFWASH_MANAGE_WUN_ENABWE_SUPEWPIPE) {
		/*
		 * Update powt sewection mask based upon channew, stowe off WUN
		 * in unpacked, AFU-fwiendwy fowmat, and hang WUN wefewence in
		 * the sdev.
		 */
		wwi->powt_sew |= CHAN2POWTMASK(chan);
		wwi->wun_id[chan] = wun_to_wunid(sdev->wun);
		sdev->hostdata = wwi;
	} ewse if (fwags & DK_CXWFWASH_MANAGE_WUN_DISABWE_SUPEWPIPE) {
		if (wwi->pawent->mode != MODE_NONE)
			wc = -EBUSY;
		ewse {
			/*
			 * Cwean up wocaw WUN fow this powt and weset tabwe
			 * twacking when no mowe wefewences exist.
			 */
			sdev->hostdata = NUWW;
			wwi->powt_sew &= ~CHAN2POWTMASK(chan);
			if (wwi->powt_sew == 0U)
				wwi->in_tabwe = fawse;
		}
	}

	dev_dbg(dev, "%s: powt_sew=%08x chan=%u wun_id=%016wwx\n",
		__func__, wwi->powt_sew, chan, wwi->wun_id[chan]);

out:
	mutex_unwock(&gwobaw.mutex);
	dev_dbg(dev, "%s: wetuwning wc=%d\n", __func__, wc);
	wetuwn wc;
}
