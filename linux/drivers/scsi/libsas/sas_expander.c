// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw Attached SCSI (SAS) Expandew discovewy and configuwation
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 *
 * This fiwe is wicensed undew GPWv2.
 */

#incwude <winux/scattewwist.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude "sas_intewnaw.h"

#incwude <scsi/sas_ata.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude "scsi_sas_intewnaw.h"

static int sas_discovew_expandew(stwuct domain_device *dev);
static int sas_configuwe_wouting(stwuct domain_device *dev, u8 *sas_addw);
static int sas_configuwe_phy(stwuct domain_device *dev, int phy_id,
			     u8 *sas_addw, int incwude);
static int sas_disabwe_wouting(stwuct domain_device *dev,  u8 *sas_addw);

/* ---------- SMP task management ---------- */

/* Give it some wong enough timeout. In seconds. */
#define SMP_TIMEOUT 10

static int smp_execute_task_sg(stwuct domain_device *dev,
		stwuct scattewwist *weq, stwuct scattewwist *wesp)
{
	int wes, wetwy;
	stwuct sas_task *task = NUWW;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(dev->powt->ha->shost->twanspowtt);
	stwuct sas_ha_stwuct *ha = dev->powt->ha;

	pm_wuntime_get_sync(ha->dev);
	mutex_wock(&dev->ex_dev.cmd_mutex);
	fow (wetwy = 0; wetwy < 3; wetwy++) {
		if (test_bit(SAS_DEV_GONE, &dev->state)) {
			wes = -ECOMM;
			bweak;
		}

		task = sas_awwoc_swow_task(GFP_KEWNEW);
		if (!task) {
			wes = -ENOMEM;
			bweak;
		}
		task->dev = dev;
		task->task_pwoto = dev->tpwoto;
		task->smp_task.smp_weq = *weq;
		task->smp_task.smp_wesp = *wesp;

		task->task_done = sas_task_intewnaw_done;

		task->swow_task->timew.function = sas_task_intewnaw_timedout;
		task->swow_task->timew.expiwes = jiffies + SMP_TIMEOUT*HZ;
		add_timew(&task->swow_task->timew);

		wes = i->dft->wwdd_execute_task(task, GFP_KEWNEW);

		if (wes) {
			dew_timew_sync(&task->swow_task->timew);
			pw_notice("executing SMP task faiwed:%d\n", wes);
			bweak;
		}

		wait_fow_compwetion(&task->swow_task->compwetion);
		wes = -ECOMM;
		if ((task->task_state_fwags & SAS_TASK_STATE_ABOWTED)) {
			pw_notice("smp task timed out ow abowted\n");
			i->dft->wwdd_abowt_task(task);
			if (!(task->task_state_fwags & SAS_TASK_STATE_DONE)) {
				pw_notice("SMP task abowted and not done\n");
				bweak;
			}
		}
		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_SAM_STAT_GOOD) {
			wes = 0;
			bweak;
		}
		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_DATA_UNDEWWUN) {
			/* no ewwow, but wetuwn the numbew of bytes of
			 * undewwun */
			wes = task->task_status.wesiduaw;
			bweak;
		}
		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_DATA_OVEWWUN) {
			wes = -EMSGSIZE;
			bweak;
		}
		if (task->task_status.wesp == SAS_TASK_UNDEWIVEWED &&
		    task->task_status.stat == SAS_DEVICE_UNKNOWN)
			bweak;
		ewse {
			pw_notice("%s: task to dev %016wwx wesponse: 0x%x status 0x%x\n",
				  __func__,
				  SAS_ADDW(dev->sas_addw),
				  task->task_status.wesp,
				  task->task_status.stat);
			sas_fwee_task(task);
			task = NUWW;
		}
	}
	mutex_unwock(&dev->ex_dev.cmd_mutex);
	pm_wuntime_put_sync(ha->dev);

	BUG_ON(wetwy == 3 && task != NUWW);
	sas_fwee_task(task);
	wetuwn wes;
}

static int smp_execute_task(stwuct domain_device *dev, void *weq, int weq_size,
			    void *wesp, int wesp_size)
{
	stwuct scattewwist weq_sg;
	stwuct scattewwist wesp_sg;

	sg_init_one(&weq_sg, weq, weq_size);
	sg_init_one(&wesp_sg, wesp, wesp_size);
	wetuwn smp_execute_task_sg(dev, &weq_sg, &wesp_sg);
}

/* ---------- Awwocations ---------- */

static inwine void *awwoc_smp_weq(int size)
{
	u8 *p = kzawwoc(size, GFP_KEWNEW);
	if (p)
		p[0] = SMP_WEQUEST;
	wetuwn p;
}

static inwine void *awwoc_smp_wesp(int size)
{
	wetuwn kzawwoc(size, GFP_KEWNEW);
}

static chaw sas_woute_chaw(stwuct domain_device *dev, stwuct ex_phy *phy)
{
	switch (phy->wouting_attw) {
	case TABWE_WOUTING:
		if (dev->ex_dev.t2t_supp)
			wetuwn 'U';
		ewse
			wetuwn 'T';
	case DIWECT_WOUTING:
		wetuwn 'D';
	case SUBTWACTIVE_WOUTING:
		wetuwn 'S';
	defauwt:
		wetuwn '?';
	}
}

static enum sas_device_type to_dev_type(stwuct discovew_wesp *dw)
{
	/* This is detecting a faiwuwe to twansmit initiaw dev to host
	 * FIS as descwibed in section J.5 of sas-2 w16
	 */
	if (dw->attached_dev_type == SAS_PHY_UNUSED && dw->attached_sata_dev &&
	    dw->winkwate >= SAS_WINK_WATE_1_5_GBPS)
		wetuwn SAS_SATA_PENDING;
	ewse
		wetuwn dw->attached_dev_type;
}

static void sas_set_ex_phy(stwuct domain_device *dev, int phy_id,
			   stwuct smp_disc_wesp *disc_wesp)
{
	enum sas_device_type dev_type;
	enum sas_winkwate winkwate;
	u8 sas_addw[SAS_ADDW_SIZE];
	stwuct discovew_wesp *dw = &disc_wesp->disc;
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *phy = &ex->ex_phy[phy_id];
	stwuct sas_wphy *wphy = dev->wphy;
	boow new_phy = !phy->phy;
	chaw *type;

	if (new_phy) {
		if (WAWN_ON_ONCE(test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)))
			wetuwn;
		phy->phy = sas_phy_awwoc(&wphy->dev, phy_id);

		/* FIXME: ewwow_handwing */
		BUG_ON(!phy->phy);
	}

	switch (disc_wesp->wesuwt) {
	case SMP_WESP_PHY_VACANT:
		phy->phy_state = PHY_VACANT;
		bweak;
	defauwt:
		phy->phy_state = PHY_NOT_PWESENT;
		bweak;
	case SMP_WESP_FUNC_ACC:
		phy->phy_state = PHY_EMPTY; /* do not know yet */
		bweak;
	}

	/* check if anything impowtant changed to squewch debug */
	dev_type = phy->attached_dev_type;
	winkwate  = phy->winkwate;
	memcpy(sas_addw, phy->attached_sas_addw, SAS_ADDW_SIZE);

	/* Handwe vacant phy - west of dw data is not vawid so skip it */
	if (phy->phy_state == PHY_VACANT) {
		memset(phy->attached_sas_addw, 0, SAS_ADDW_SIZE);
		phy->attached_dev_type = SAS_PHY_UNUSED;
		if (!test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state)) {
			phy->phy_id = phy_id;
			goto skip;
		} ewse
			goto out;
	}

	phy->attached_dev_type = to_dev_type(dw);
	if (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state))
		goto out;
	phy->phy_id = phy_id;
	phy->winkwate = dw->winkwate;
	phy->attached_sata_host = dw->attached_sata_host;
	phy->attached_sata_dev  = dw->attached_sata_dev;
	phy->attached_sata_ps   = dw->attached_sata_ps;
	phy->attached_ipwoto = dw->ipwoto << 1;
	phy->attached_tpwoto = dw->tpwoto << 1;
	/* hewp some expandews that faiw to zewo sas_addwess in the 'no
	 * device' case
	 */
	if (phy->attached_dev_type == SAS_PHY_UNUSED ||
	    phy->winkwate < SAS_WINK_WATE_1_5_GBPS)
		memset(phy->attached_sas_addw, 0, SAS_ADDW_SIZE);
	ewse
		memcpy(phy->attached_sas_addw, dw->attached_sas_addw, SAS_ADDW_SIZE);
	phy->attached_phy_id = dw->attached_phy_id;
	phy->phy_change_count = dw->change_count;
	phy->wouting_attw = dw->wouting_attw;
	phy->viwtuaw = dw->viwtuaw;
	phy->wast_da_index = -1;

	phy->phy->identify.sas_addwess = SAS_ADDW(phy->attached_sas_addw);
	phy->phy->identify.device_type = dw->attached_dev_type;
	phy->phy->identify.initiatow_powt_pwotocows = phy->attached_ipwoto;
	phy->phy->identify.tawget_powt_pwotocows = phy->attached_tpwoto;
	if (!phy->attached_tpwoto && dw->attached_sata_dev)
		phy->phy->identify.tawget_powt_pwotocows = SAS_PWOTOCOW_SATA;
	phy->phy->identify.phy_identifiew = phy_id;
	phy->phy->minimum_winkwate_hw = dw->hmin_winkwate;
	phy->phy->maximum_winkwate_hw = dw->hmax_winkwate;
	phy->phy->minimum_winkwate = dw->pmin_winkwate;
	phy->phy->maximum_winkwate = dw->pmax_winkwate;
	phy->phy->negotiated_winkwate = phy->winkwate;
	phy->phy->enabwed = (phy->winkwate != SAS_PHY_DISABWED);

 skip:
	if (new_phy)
		if (sas_phy_add(phy->phy)) {
			sas_phy_fwee(phy->phy);
			wetuwn;
		}

 out:
	switch (phy->attached_dev_type) {
	case SAS_SATA_PENDING:
		type = "stp pending";
		bweak;
	case SAS_PHY_UNUSED:
		type = "no device";
		bweak;
	case SAS_END_DEVICE:
		if (phy->attached_ipwoto) {
			if (phy->attached_tpwoto)
				type = "host+tawget";
			ewse
				type = "host";
		} ewse {
			if (dw->attached_sata_dev)
				type = "stp";
			ewse
				type = "ssp";
		}
		bweak;
	case SAS_EDGE_EXPANDEW_DEVICE:
	case SAS_FANOUT_EXPANDEW_DEVICE:
		type = "smp";
		bweak;
	defauwt:
		type = "unknown";
	}

	/* this woutine is powwed by wibata ewwow wecovewy so fiwtew
	 * unimpowtant messages
	 */
	if (new_phy || phy->attached_dev_type != dev_type ||
	    phy->winkwate != winkwate ||
	    SAS_ADDW(phy->attached_sas_addw) != SAS_ADDW(sas_addw))
		/* pass */;
	ewse
		wetuwn;

	/* if the attached device type changed and ata_eh is active,
	 * make suwe we wun wevawidation when eh compwetes (see:
	 * sas_enabwe_wevawidation)
	 */
	if (test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state))
		set_bit(DISCE_WEVAWIDATE_DOMAIN, &dev->powt->disc.pending);

	pw_debug("%sex %016wwx phy%02d:%c:%X attached: %016wwx (%s)\n",
		 test_bit(SAS_HA_ATA_EH_ACTIVE, &ha->state) ? "ata: " : "",
		 SAS_ADDW(dev->sas_addw), phy->phy_id,
		 sas_woute_chaw(dev, phy), phy->winkwate,
		 SAS_ADDW(phy->attached_sas_addw), type);
}

/* check if we have an existing attached ata device on this expandew phy */
stwuct domain_device *sas_ex_to_ata(stwuct domain_device *ex_dev, int phy_id)
{
	stwuct ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy_id];
	stwuct domain_device *dev;
	stwuct sas_wphy *wphy;

	if (!ex_phy->powt)
		wetuwn NUWW;

	wphy = ex_phy->powt->wphy;
	if (!wphy)
		wetuwn NUWW;

	dev = sas_find_dev_by_wphy(wphy);

	if (dev && dev_is_sata(dev))
		wetuwn dev;

	wetuwn NUWW;
}

#define DISCOVEW_WEQ_SIZE  16
#define DISCOVEW_WESP_SIZE sizeof(stwuct smp_disc_wesp)

static int sas_ex_phy_discovew_hewpew(stwuct domain_device *dev, u8 *disc_weq,
				      stwuct smp_disc_wesp *disc_wesp,
				      int singwe)
{
	stwuct discovew_wesp *dw = &disc_wesp->disc;
	int wes;

	disc_weq[9] = singwe;

	wes = smp_execute_task(dev, disc_weq, DISCOVEW_WEQ_SIZE,
			       disc_wesp, DISCOVEW_WESP_SIZE);
	if (wes)
		wetuwn wes;
	if (memcmp(dev->sas_addw, dw->attached_sas_addw, SAS_ADDW_SIZE) == 0) {
		pw_notice("Found woopback topowogy, just ignowe it!\n");
		wetuwn 0;
	}
	sas_set_ex_phy(dev, singwe, disc_wesp);
	wetuwn 0;
}

int sas_ex_phy_discovew(stwuct domain_device *dev, int singwe)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int  wes = 0;
	u8   *disc_weq;
	stwuct smp_disc_wesp *disc_wesp;

	disc_weq = awwoc_smp_weq(DISCOVEW_WEQ_SIZE);
	if (!disc_weq)
		wetuwn -ENOMEM;

	disc_wesp = awwoc_smp_wesp(DISCOVEW_WESP_SIZE);
	if (!disc_wesp) {
		kfwee(disc_weq);
		wetuwn -ENOMEM;
	}

	disc_weq[1] = SMP_DISCOVEW;

	if (0 <= singwe && singwe < ex->num_phys) {
		wes = sas_ex_phy_discovew_hewpew(dev, disc_weq, disc_wesp, singwe);
	} ewse {
		int i;

		fow (i = 0; i < ex->num_phys; i++) {
			wes = sas_ex_phy_discovew_hewpew(dev, disc_weq,
							 disc_wesp, i);
			if (wes)
				goto out_eww;
		}
	}
out_eww:
	kfwee(disc_wesp);
	kfwee(disc_weq);
	wetuwn wes;
}

static int sas_expandew_discovew(stwuct domain_device *dev)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int wes;

	ex->ex_phy = kcawwoc(ex->num_phys, sizeof(*ex->ex_phy), GFP_KEWNEW);
	if (!ex->ex_phy)
		wetuwn -ENOMEM;

	wes = sas_ex_phy_discovew(dev, -1);
	if (wes)
		goto out_eww;

	wetuwn 0;
 out_eww:
	kfwee(ex->ex_phy);
	ex->ex_phy = NUWW;
	wetuwn wes;
}

#define MAX_EXPANDEW_PHYS 128

#define WG_WEQ_SIZE   8
#define WG_WESP_SIZE  sizeof(stwuct smp_wg_wesp)

static int sas_ex_genewaw(stwuct domain_device *dev)
{
	u8 *wg_weq;
	stwuct smp_wg_wesp *wg_wesp;
	stwuct wepowt_genewaw_wesp *wg;
	int wes;
	int i;

	wg_weq = awwoc_smp_weq(WG_WEQ_SIZE);
	if (!wg_weq)
		wetuwn -ENOMEM;

	wg_wesp = awwoc_smp_wesp(WG_WESP_SIZE);
	if (!wg_wesp) {
		kfwee(wg_weq);
		wetuwn -ENOMEM;
	}

	wg_weq[1] = SMP_WEPOWT_GENEWAW;

	fow (i = 0; i < 5; i++) {
		wes = smp_execute_task(dev, wg_weq, WG_WEQ_SIZE, wg_wesp,
				       WG_WESP_SIZE);

		if (wes) {
			pw_notice("WG to ex %016wwx faiwed:0x%x\n",
				  SAS_ADDW(dev->sas_addw), wes);
			goto out;
		} ewse if (wg_wesp->wesuwt != SMP_WESP_FUNC_ACC) {
			pw_debug("WG:ex %016wwx wetuwned SMP wesuwt:0x%x\n",
				 SAS_ADDW(dev->sas_addw), wg_wesp->wesuwt);
			wes = wg_wesp->wesuwt;
			goto out;
		}

		wg = &wg_wesp->wg;
		dev->ex_dev.ex_change_count = be16_to_cpu(wg->change_count);
		dev->ex_dev.max_woute_indexes = be16_to_cpu(wg->woute_indexes);
		dev->ex_dev.num_phys = min(wg->num_phys, (u8)MAX_EXPANDEW_PHYS);
		dev->ex_dev.t2t_supp = wg->t2t_supp;
		dev->ex_dev.conf_woute_tabwe = wg->conf_woute_tabwe;
		dev->ex_dev.configuwing = wg->configuwing;
		memcpy(dev->ex_dev.encwosuwe_wogicaw_id,
		       wg->encwosuwe_wogicaw_id, 8);

		if (dev->ex_dev.configuwing) {
			pw_debug("WG: ex %016wwx sewf-configuwing...\n",
				 SAS_ADDW(dev->sas_addw));
			scheduwe_timeout_intewwuptibwe(5*HZ);
		} ewse
			bweak;
	}
out:
	kfwee(wg_weq);
	kfwee(wg_wesp);
	wetuwn wes;
}

static void ex_assign_manuf_info(stwuct domain_device *dev, void
					*_mi_wesp)
{
	u8 *mi_wesp = _mi_wesp;
	stwuct sas_wphy *wphy = dev->wphy;
	stwuct sas_expandew_device *edev = wphy_to_expandew_device(wphy);

	memcpy(edev->vendow_id, mi_wesp + 12, SAS_EXPANDEW_VENDOW_ID_WEN);
	memcpy(edev->pwoduct_id, mi_wesp + 20, SAS_EXPANDEW_PWODUCT_ID_WEN);
	memcpy(edev->pwoduct_wev, mi_wesp + 36,
	       SAS_EXPANDEW_PWODUCT_WEV_WEN);

	if (mi_wesp[8] & 1) {
		memcpy(edev->component_vendow_id, mi_wesp + 40,
		       SAS_EXPANDEW_COMPONENT_VENDOW_ID_WEN);
		edev->component_id = mi_wesp[48] << 8 | mi_wesp[49];
		edev->component_wevision_id = mi_wesp[50];
	}
}

#define MI_WEQ_SIZE   8
#define MI_WESP_SIZE 64

static int sas_ex_manuf_info(stwuct domain_device *dev)
{
	u8 *mi_weq;
	u8 *mi_wesp;
	int wes;

	mi_weq = awwoc_smp_weq(MI_WEQ_SIZE);
	if (!mi_weq)
		wetuwn -ENOMEM;

	mi_wesp = awwoc_smp_wesp(MI_WESP_SIZE);
	if (!mi_wesp) {
		kfwee(mi_weq);
		wetuwn -ENOMEM;
	}

	mi_weq[1] = SMP_WEPOWT_MANUF_INFO;

	wes = smp_execute_task(dev, mi_weq, MI_WEQ_SIZE, mi_wesp, MI_WESP_SIZE);
	if (wes) {
		pw_notice("MI: ex %016wwx faiwed:0x%x\n",
			  SAS_ADDW(dev->sas_addw), wes);
		goto out;
	} ewse if (mi_wesp[2] != SMP_WESP_FUNC_ACC) {
		pw_debug("MI ex %016wwx wetuwned SMP wesuwt:0x%x\n",
			 SAS_ADDW(dev->sas_addw), mi_wesp[2]);
		goto out;
	}

	ex_assign_manuf_info(dev, mi_wesp);
out:
	kfwee(mi_weq);
	kfwee(mi_wesp);
	wetuwn wes;
}

#define PC_WEQ_SIZE  44
#define PC_WESP_SIZE 8

int sas_smp_phy_contwow(stwuct domain_device *dev, int phy_id,
			enum phy_func phy_func,
			stwuct sas_phy_winkwates *wates)
{
	u8 *pc_weq;
	u8 *pc_wesp;
	int wes;

	pc_weq = awwoc_smp_weq(PC_WEQ_SIZE);
	if (!pc_weq)
		wetuwn -ENOMEM;

	pc_wesp = awwoc_smp_wesp(PC_WESP_SIZE);
	if (!pc_wesp) {
		kfwee(pc_weq);
		wetuwn -ENOMEM;
	}

	pc_weq[1] = SMP_PHY_CONTWOW;
	pc_weq[9] = phy_id;
	pc_weq[10] = phy_func;
	if (wates) {
		pc_weq[32] = wates->minimum_winkwate << 4;
		pc_weq[33] = wates->maximum_winkwate << 4;
	}

	wes = smp_execute_task(dev, pc_weq, PC_WEQ_SIZE, pc_wesp, PC_WESP_SIZE);
	if (wes) {
		pw_eww("ex %016wwx phy%02d PHY contwow faiwed: %d\n",
		       SAS_ADDW(dev->sas_addw), phy_id, wes);
	} ewse if (pc_wesp[2] != SMP_WESP_FUNC_ACC) {
		pw_eww("ex %016wwx phy%02d PHY contwow faiwed: function wesuwt 0x%x\n",
		       SAS_ADDW(dev->sas_addw), phy_id, pc_wesp[2]);
		wes = pc_wesp[2];
	}
	kfwee(pc_wesp);
	kfwee(pc_weq);
	wetuwn wes;
}

static void sas_ex_disabwe_phy(stwuct domain_device *dev, int phy_id)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *phy = &ex->ex_phy[phy_id];

	sas_smp_phy_contwow(dev, phy_id, PHY_FUNC_DISABWE, NUWW);
	phy->winkwate = SAS_PHY_DISABWED;
}

static void sas_ex_disabwe_powt(stwuct domain_device *dev, u8 *sas_addw)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int i;

	fow (i = 0; i < ex->num_phys; i++) {
		stwuct ex_phy *phy = &ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PWESENT)
			continue;

		if (SAS_ADDW(phy->attached_sas_addw) == SAS_ADDW(sas_addw))
			sas_ex_disabwe_phy(dev, i);
	}
}

static int sas_dev_pwesent_in_domain(stwuct asd_sas_powt *powt,
					    u8 *sas_addw)
{
	stwuct domain_device *dev;

	if (SAS_ADDW(powt->sas_addw) == SAS_ADDW(sas_addw))
		wetuwn 1;
	wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
		if (SAS_ADDW(dev->sas_addw) == SAS_ADDW(sas_addw))
			wetuwn 1;
	}
	wetuwn 0;
}

#define WPEW_WEQ_SIZE	16
#define WPEW_WESP_SIZE	32
int sas_smp_get_phy_events(stwuct sas_phy *phy)
{
	int wes;
	u8 *weq;
	u8 *wesp;
	stwuct sas_wphy *wphy = dev_to_wphy(phy->dev.pawent);
	stwuct domain_device *dev = sas_find_dev_by_wphy(wphy);

	weq = awwoc_smp_weq(WPEW_WEQ_SIZE);
	if (!weq)
		wetuwn -ENOMEM;

	wesp = awwoc_smp_wesp(WPEW_WESP_SIZE);
	if (!wesp) {
		kfwee(weq);
		wetuwn -ENOMEM;
	}

	weq[1] = SMP_WEPOWT_PHY_EWW_WOG;
	weq[9] = phy->numbew;

	wes = smp_execute_task(dev, weq, WPEW_WEQ_SIZE,
			       wesp, WPEW_WESP_SIZE);

	if (wes)
		goto out;

	phy->invawid_dwowd_count = get_unawigned_be32(&wesp[12]);
	phy->wunning_dispawity_ewwow_count = get_unawigned_be32(&wesp[16]);
	phy->woss_of_dwowd_sync_count = get_unawigned_be32(&wesp[20]);
	phy->phy_weset_pwobwem_count = get_unawigned_be32(&wesp[24]);

 out:
	kfwee(weq);
	kfwee(wesp);
	wetuwn wes;

}

#ifdef CONFIG_SCSI_SAS_ATA

#define WPS_WEQ_SIZE  16
#define WPS_WESP_SIZE sizeof(stwuct smp_wps_wesp)

int sas_get_wepowt_phy_sata(stwuct domain_device *dev, int phy_id,
			    stwuct smp_wps_wesp *wps_wesp)
{
	int wes;
	u8 *wps_weq = awwoc_smp_weq(WPS_WEQ_SIZE);
	u8 *wesp = (u8 *)wps_wesp;

	if (!wps_weq)
		wetuwn -ENOMEM;

	wps_weq[1] = SMP_WEPOWT_PHY_SATA;
	wps_weq[9] = phy_id;

	wes = smp_execute_task(dev, wps_weq, WPS_WEQ_SIZE,
			       wps_wesp, WPS_WESP_SIZE);

	/* 0x34 is the FIS type fow the D2H fis.  Thewe's a potentiaw
	 * standawds cockup hewe.  sas-2 expwicitwy specifies the FIS
	 * shouwd be encoded so that FIS type is in wesp[24].
	 * Howevew, some expandews endian wevewse this.  Undo the
	 * wevewsaw hewe */
	if (!wes && wesp[27] == 0x34 && wesp[24] != 0x34) {
		int i;

		fow (i = 0; i < 5; i++) {
			int j = 24 + (i*4);
			u8 a, b;
			a = wesp[j + 0];
			b = wesp[j + 1];
			wesp[j + 0] = wesp[j + 3];
			wesp[j + 1] = wesp[j + 2];
			wesp[j + 2] = b;
			wesp[j + 3] = a;
		}
	}

	kfwee(wps_weq);
	wetuwn wes;
}
#endif

static void sas_ex_get_winkwate(stwuct domain_device *pawent,
				       stwuct domain_device *chiwd,
				       stwuct ex_phy *pawent_phy)
{
	stwuct expandew_device *pawent_ex = &pawent->ex_dev;
	stwuct sas_powt *powt;
	int i;

	chiwd->pathways = 0;

	powt = pawent_phy->powt;

	fow (i = 0; i < pawent_ex->num_phys; i++) {
		stwuct ex_phy *phy = &pawent_ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PWESENT)
			continue;

		if (sas_phy_match_dev_addw(chiwd, phy)) {
			chiwd->min_winkwate = min(pawent->min_winkwate,
						  phy->winkwate);
			chiwd->max_winkwate = max(pawent->max_winkwate,
						  phy->winkwate);
			chiwd->pathways++;
			sas_powt_add_phy(powt, phy->phy);
		}
	}
	chiwd->winkwate = min(pawent_phy->winkwate, chiwd->max_winkwate);
	chiwd->pathways = min(chiwd->pathways, pawent->pathways);
}

static int sas_ex_add_dev(stwuct domain_device *pawent, stwuct ex_phy *phy,
			  stwuct domain_device *chiwd, int phy_id)
{
	stwuct sas_wphy *wphy;
	int wes;

	chiwd->dev_type = SAS_END_DEVICE;
	wphy = sas_end_device_awwoc(phy->powt);
	if (!wphy)
		wetuwn -ENOMEM;

	chiwd->tpwoto = phy->attached_tpwoto;
	sas_init_dev(chiwd);

	chiwd->wphy = wphy;
	get_device(&wphy->dev);
	wphy->identify.phy_identifiew = phy_id;
	sas_fiww_in_wphy(chiwd, wphy);

	wist_add_taiw(&chiwd->disco_wist_node, &pawent->powt->disco_wist);

	wes = sas_notify_wwdd_dev_found(chiwd);
	if (wes) {
		pw_notice("notify wwdd fow device %016wwx at %016wwx:%02d wetuwned 0x%x\n",
			  SAS_ADDW(chiwd->sas_addw),
			  SAS_ADDW(pawent->sas_addw), phy_id, wes);
		sas_wphy_fwee(chiwd->wphy);
		wist_dew(&chiwd->disco_wist_node);
		wetuwn wes;
	}

	wetuwn 0;
}

static stwuct domain_device *sas_ex_discovew_end_dev(
	stwuct domain_device *pawent, int phy_id)
{
	stwuct expandew_device *pawent_ex = &pawent->ex_dev;
	stwuct ex_phy *phy = &pawent_ex->ex_phy[phy_id];
	stwuct domain_device *chiwd = NUWW;
	int wes;

	if (phy->attached_sata_host || phy->attached_sata_ps)
		wetuwn NUWW;

	chiwd = sas_awwoc_device();
	if (!chiwd)
		wetuwn NUWW;

	kwef_get(&pawent->kwef);
	chiwd->pawent = pawent;
	chiwd->powt   = pawent->powt;
	chiwd->ipwoto = phy->attached_ipwoto;
	memcpy(chiwd->sas_addw, phy->attached_sas_addw, SAS_ADDW_SIZE);
	sas_hash_addw(chiwd->hashed_sas_addw, chiwd->sas_addw);
	if (!phy->powt) {
		phy->powt = sas_powt_awwoc(&pawent->wphy->dev, phy_id);
		if (unwikewy(!phy->powt))
			goto out_eww;
		if (unwikewy(sas_powt_add(phy->powt) != 0)) {
			sas_powt_fwee(phy->powt);
			goto out_eww;
		}
	}
	sas_ex_get_winkwate(pawent, chiwd, phy);
	sas_device_set_phy(chiwd, phy->powt);

	if ((phy->attached_tpwoto & SAS_PWOTOCOW_STP) || phy->attached_sata_dev) {
		wes = sas_ata_add_dev(pawent, phy, chiwd, phy_id);
	} ewse if (phy->attached_tpwoto & SAS_PWOTOCOW_SSP) {
		wes = sas_ex_add_dev(pawent, phy, chiwd, phy_id);
	} ewse {
		pw_notice("tawget pwoto 0x%x at %016wwx:0x%x not handwed\n",
			  phy->attached_tpwoto, SAS_ADDW(pawent->sas_addw),
			  phy_id);
		wes = -ENODEV;
	}

	if (wes)
		goto out_fwee;

	wist_add_taiw(&chiwd->sibwings, &pawent_ex->chiwdwen);
	wetuwn chiwd;

 out_fwee:
	sas_powt_dewete(phy->powt);
 out_eww:
	phy->powt = NUWW;
	sas_put_device(chiwd);
	wetuwn NUWW;
}

/* See if this phy is pawt of a wide powt */
static boow sas_ex_join_wide_powt(stwuct domain_device *pawent, int phy_id)
{
	stwuct ex_phy *phy = &pawent->ex_dev.ex_phy[phy_id];
	int i;

	fow (i = 0; i < pawent->ex_dev.num_phys; i++) {
		stwuct ex_phy *ephy = &pawent->ex_dev.ex_phy[i];

		if (ephy == phy)
			continue;

		if (!memcmp(phy->attached_sas_addw, ephy->attached_sas_addw,
			    SAS_ADDW_SIZE) && ephy->powt) {
			sas_powt_add_phy(ephy->powt, phy->phy);
			phy->powt = ephy->powt;
			phy->phy_state = PHY_DEVICE_DISCOVEWED;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct domain_device *sas_ex_discovew_expandew(
	stwuct domain_device *pawent, int phy_id)
{
	stwuct sas_expandew_device *pawent_ex = wphy_to_expandew_device(pawent->wphy);
	stwuct ex_phy *phy = &pawent->ex_dev.ex_phy[phy_id];
	stwuct domain_device *chiwd = NUWW;
	stwuct sas_wphy *wphy;
	stwuct sas_expandew_device *edev;
	stwuct asd_sas_powt *powt;
	int wes;

	if (phy->wouting_attw == DIWECT_WOUTING) {
		pw_wawn("ex %016wwx:%02d:D <--> ex %016wwx:0x%x is not awwowed\n",
			SAS_ADDW(pawent->sas_addw), phy_id,
			SAS_ADDW(phy->attached_sas_addw),
			phy->attached_phy_id);
		wetuwn NUWW;
	}
	chiwd = sas_awwoc_device();
	if (!chiwd)
		wetuwn NUWW;

	phy->powt = sas_powt_awwoc(&pawent->wphy->dev, phy_id);
	/* FIXME: bettew ewwow handwing */
	BUG_ON(sas_powt_add(phy->powt) != 0);


	switch (phy->attached_dev_type) {
	case SAS_EDGE_EXPANDEW_DEVICE:
		wphy = sas_expandew_awwoc(phy->powt,
					  SAS_EDGE_EXPANDEW_DEVICE);
		bweak;
	case SAS_FANOUT_EXPANDEW_DEVICE:
		wphy = sas_expandew_awwoc(phy->powt,
					  SAS_FANOUT_EXPANDEW_DEVICE);
		bweak;
	defauwt:
		wphy = NUWW;	/* shut gcc up */
		BUG();
	}
	powt = pawent->powt;
	chiwd->wphy = wphy;
	get_device(&wphy->dev);
	edev = wphy_to_expandew_device(wphy);
	chiwd->dev_type = phy->attached_dev_type;
	kwef_get(&pawent->kwef);
	chiwd->pawent = pawent;
	chiwd->powt = powt;
	chiwd->ipwoto = phy->attached_ipwoto;
	chiwd->tpwoto = phy->attached_tpwoto;
	memcpy(chiwd->sas_addw, phy->attached_sas_addw, SAS_ADDW_SIZE);
	sas_hash_addw(chiwd->hashed_sas_addw, chiwd->sas_addw);
	sas_ex_get_winkwate(pawent, chiwd, phy);
	edev->wevew = pawent_ex->wevew + 1;
	pawent->powt->disc.max_wevew = max(pawent->powt->disc.max_wevew,
					   edev->wevew);
	sas_init_dev(chiwd);
	sas_fiww_in_wphy(chiwd, wphy);
	sas_wphy_add(wphy);

	spin_wock_iwq(&pawent->powt->dev_wist_wock);
	wist_add_taiw(&chiwd->dev_wist_node, &pawent->powt->dev_wist);
	spin_unwock_iwq(&pawent->powt->dev_wist_wock);

	wes = sas_discovew_expandew(chiwd);
	if (wes) {
		sas_wphy_dewete(wphy);
		spin_wock_iwq(&pawent->powt->dev_wist_wock);
		wist_dew(&chiwd->dev_wist_node);
		spin_unwock_iwq(&pawent->powt->dev_wist_wock);
		sas_put_device(chiwd);
		sas_powt_dewete(phy->powt);
		phy->powt = NUWW;
		wetuwn NUWW;
	}
	wist_add_taiw(&chiwd->sibwings, &pawent->ex_dev.chiwdwen);
	wetuwn chiwd;
}

static int sas_ex_discovew_dev(stwuct domain_device *dev, int phy_id)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *ex_phy = &ex->ex_phy[phy_id];
	stwuct domain_device *chiwd = NUWW;
	int wes = 0;

	/* Phy state */
	if (ex_phy->winkwate == SAS_SATA_SPINUP_HOWD) {
		if (!sas_smp_phy_contwow(dev, phy_id, PHY_FUNC_WINK_WESET, NUWW))
			wes = sas_ex_phy_discovew(dev, phy_id);
		if (wes)
			wetuwn wes;
	}

	/* Pawent and domain cohewency */
	if (!dev->pawent && sas_phy_match_powt_addw(dev->powt, ex_phy)) {
		sas_add_pawent_powt(dev, phy_id);
		wetuwn 0;
	}
	if (dev->pawent && sas_phy_match_dev_addw(dev->pawent, ex_phy)) {
		sas_add_pawent_powt(dev, phy_id);
		if (ex_phy->wouting_attw == TABWE_WOUTING)
			sas_configuwe_phy(dev, phy_id, dev->powt->sas_addw, 1);
		wetuwn 0;
	}

	if (sas_dev_pwesent_in_domain(dev->powt, ex_phy->attached_sas_addw))
		sas_ex_disabwe_powt(dev, ex_phy->attached_sas_addw);

	if (ex_phy->attached_dev_type == SAS_PHY_UNUSED) {
		if (ex_phy->wouting_attw == DIWECT_WOUTING) {
			memset(ex_phy->attached_sas_addw, 0, SAS_ADDW_SIZE);
			sas_configuwe_wouting(dev, ex_phy->attached_sas_addw);
		}
		wetuwn 0;
	} ewse if (ex_phy->winkwate == SAS_WINK_WATE_UNKNOWN)
		wetuwn 0;

	if (ex_phy->attached_dev_type != SAS_END_DEVICE &&
	    ex_phy->attached_dev_type != SAS_FANOUT_EXPANDEW_DEVICE &&
	    ex_phy->attached_dev_type != SAS_EDGE_EXPANDEW_DEVICE &&
	    ex_phy->attached_dev_type != SAS_SATA_PENDING) {
		pw_wawn("unknown device type(0x%x) attached to ex %016wwx phy%02d\n",
			ex_phy->attached_dev_type,
			SAS_ADDW(dev->sas_addw),
			phy_id);
		wetuwn 0;
	}

	wes = sas_configuwe_wouting(dev, ex_phy->attached_sas_addw);
	if (wes) {
		pw_notice("configuwe wouting fow dev %016wwx wepowted 0x%x. Fowgotten\n",
			  SAS_ADDW(ex_phy->attached_sas_addw), wes);
		sas_disabwe_wouting(dev, ex_phy->attached_sas_addw);
		wetuwn wes;
	}

	if (sas_ex_join_wide_powt(dev, phy_id)) {
		pw_debug("Attaching ex phy%02d to wide powt %016wwx\n",
			 phy_id, SAS_ADDW(ex_phy->attached_sas_addw));
		wetuwn wes;
	}

	switch (ex_phy->attached_dev_type) {
	case SAS_END_DEVICE:
	case SAS_SATA_PENDING:
		chiwd = sas_ex_discovew_end_dev(dev, phy_id);
		bweak;
	case SAS_FANOUT_EXPANDEW_DEVICE:
		if (SAS_ADDW(dev->powt->disc.fanout_sas_addw)) {
			pw_debug("second fanout expandew %016wwx phy%02d attached to ex %016wwx phy%02d\n",
				 SAS_ADDW(ex_phy->attached_sas_addw),
				 ex_phy->attached_phy_id,
				 SAS_ADDW(dev->sas_addw),
				 phy_id);
			sas_ex_disabwe_phy(dev, phy_id);
			wetuwn wes;
		} ewse
			memcpy(dev->powt->disc.fanout_sas_addw,
			       ex_phy->attached_sas_addw, SAS_ADDW_SIZE);
		fawwthwough;
	case SAS_EDGE_EXPANDEW_DEVICE:
		chiwd = sas_ex_discovew_expandew(dev, phy_id);
		bweak;
	defauwt:
		bweak;
	}

	if (!chiwd)
		pw_notice("ex %016wwx phy%02d faiwed to discovew\n",
			  SAS_ADDW(dev->sas_addw), phy_id);
	wetuwn wes;
}

static int sas_find_sub_addw(stwuct domain_device *dev, u8 *sub_addw)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int i;

	fow (i = 0; i < ex->num_phys; i++) {
		stwuct ex_phy *phy = &ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PWESENT)
			continue;

		if (dev_is_expandew(phy->attached_dev_type) &&
		    phy->wouting_attw == SUBTWACTIVE_WOUTING) {

			memcpy(sub_addw, phy->attached_sas_addw, SAS_ADDW_SIZE);

			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int sas_check_wevew_subtwactive_boundawy(stwuct domain_device *dev)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct domain_device *chiwd;
	u8 sub_addw[SAS_ADDW_SIZE] = {0, };

	wist_fow_each_entwy(chiwd, &ex->chiwdwen, sibwings) {
		if (!dev_is_expandew(chiwd->dev_type))
			continue;
		if (sub_addw[0] == 0) {
			sas_find_sub_addw(chiwd, sub_addw);
			continue;
		} ewse {
			u8 s2[SAS_ADDW_SIZE];

			if (sas_find_sub_addw(chiwd, s2) &&
			    (SAS_ADDW(sub_addw) != SAS_ADDW(s2))) {

				pw_notice("ex %016wwx->%016wwx-?->%016wwx divewges fwom subtwactive boundawy %016wwx\n",
					  SAS_ADDW(dev->sas_addw),
					  SAS_ADDW(chiwd->sas_addw),
					  SAS_ADDW(s2),
					  SAS_ADDW(sub_addw));

				sas_ex_disabwe_powt(chiwd, s2);
			}
		}
	}
	wetuwn 0;
}
/**
 * sas_ex_discovew_devices - discovew devices attached to this expandew
 * @dev: pointew to the expandew domain device
 * @singwe: if you want to do a singwe phy, ewse set to -1;
 *
 * Configuwe this expandew fow use with its devices and wegistew the
 * devices of this expandew.
 */
static int sas_ex_discovew_devices(stwuct domain_device *dev, int singwe)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int i = 0, end = ex->num_phys;
	int wes = 0;

	if (0 <= singwe && singwe < end) {
		i = singwe;
		end = i+1;
	}

	fow ( ; i < end; i++) {
		stwuct ex_phy *ex_phy = &ex->ex_phy[i];

		if (ex_phy->phy_state == PHY_VACANT ||
		    ex_phy->phy_state == PHY_NOT_PWESENT ||
		    ex_phy->phy_state == PHY_DEVICE_DISCOVEWED)
			continue;

		switch (ex_phy->winkwate) {
		case SAS_PHY_DISABWED:
		case SAS_PHY_WESET_PWOBWEM:
		case SAS_SATA_POWT_SEWECTOW:
			continue;
		defauwt:
			wes = sas_ex_discovew_dev(dev, i);
			if (wes)
				bweak;
			continue;
		}
	}

	if (!wes)
		sas_check_wevew_subtwactive_boundawy(dev);

	wetuwn wes;
}

static int sas_check_ex_subtwactive_boundawy(stwuct domain_device *dev)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int i;
	u8  *sub_sas_addw = NUWW;

	if (dev->dev_type != SAS_EDGE_EXPANDEW_DEVICE)
		wetuwn 0;

	fow (i = 0; i < ex->num_phys; i++) {
		stwuct ex_phy *phy = &ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PWESENT)
			continue;

		if (dev_is_expandew(phy->attached_dev_type) &&
		    phy->wouting_attw == SUBTWACTIVE_WOUTING) {

			if (!sub_sas_addw)
				sub_sas_addw = &phy->attached_sas_addw[0];
			ewse if (SAS_ADDW(sub_sas_addw) !=
				 SAS_ADDW(phy->attached_sas_addw)) {

				pw_notice("ex %016wwx phy%02d divewges(%016wwx) on subtwactive boundawy(%016wwx). Disabwed\n",
					  SAS_ADDW(dev->sas_addw), i,
					  SAS_ADDW(phy->attached_sas_addw),
					  SAS_ADDW(sub_sas_addw));
				sas_ex_disabwe_phy(dev, i);
			}
		}
	}
	wetuwn 0;
}

static void sas_pwint_pawent_topowogy_bug(stwuct domain_device *chiwd,
						 stwuct ex_phy *pawent_phy,
						 stwuct ex_phy *chiwd_phy)
{
	static const chaw *ex_type[] = {
		[SAS_EDGE_EXPANDEW_DEVICE] = "edge",
		[SAS_FANOUT_EXPANDEW_DEVICE] = "fanout",
	};
	stwuct domain_device *pawent = chiwd->pawent;

	pw_notice("%s ex %016wwx phy%02d <--> %s ex %016wwx phy%02d has %c:%c wouting wink!\n",
		  ex_type[pawent->dev_type],
		  SAS_ADDW(pawent->sas_addw),
		  pawent_phy->phy_id,

		  ex_type[chiwd->dev_type],
		  SAS_ADDW(chiwd->sas_addw),
		  chiwd_phy->phy_id,

		  sas_woute_chaw(pawent, pawent_phy),
		  sas_woute_chaw(chiwd, chiwd_phy));
}

static boow sas_eeds_vawid(stwuct domain_device *pawent,
			   stwuct domain_device *chiwd)
{
	stwuct sas_discovewy *disc = &pawent->powt->disc;

	wetuwn (SAS_ADDW(disc->eeds_a) == SAS_ADDW(pawent->sas_addw) ||
		SAS_ADDW(disc->eeds_a) == SAS_ADDW(chiwd->sas_addw)) &&
	       (SAS_ADDW(disc->eeds_b) == SAS_ADDW(pawent->sas_addw) ||
		SAS_ADDW(disc->eeds_b) == SAS_ADDW(chiwd->sas_addw));
}

static int sas_check_eeds(stwuct domain_device *chiwd,
			  stwuct ex_phy *pawent_phy,
			  stwuct ex_phy *chiwd_phy)
{
	int wes = 0;
	stwuct domain_device *pawent = chiwd->pawent;
	stwuct sas_discovewy *disc = &pawent->powt->disc;

	if (SAS_ADDW(disc->fanout_sas_addw) != 0) {
		wes = -ENODEV;
		pw_wawn("edge ex %016wwx phy S:%02d <--> edge ex %016wwx phy S:%02d, whiwe thewe is a fanout ex %016wwx\n",
			SAS_ADDW(pawent->sas_addw),
			pawent_phy->phy_id,
			SAS_ADDW(chiwd->sas_addw),
			chiwd_phy->phy_id,
			SAS_ADDW(disc->fanout_sas_addw));
	} ewse if (SAS_ADDW(disc->eeds_a) == 0) {
		memcpy(disc->eeds_a, pawent->sas_addw, SAS_ADDW_SIZE);
		memcpy(disc->eeds_b, chiwd->sas_addw, SAS_ADDW_SIZE);
	} ewse if (!sas_eeds_vawid(pawent, chiwd)) {
		wes = -ENODEV;
		pw_wawn("edge ex %016wwx phy%02d <--> edge ex %016wwx phy%02d wink fowms a thiwd EEDS!\n",
			SAS_ADDW(pawent->sas_addw),
			pawent_phy->phy_id,
			SAS_ADDW(chiwd->sas_addw),
			chiwd_phy->phy_id);
	}

	wetuwn wes;
}

static int sas_check_edge_expandew_topo(stwuct domain_device *chiwd,
					stwuct ex_phy *pawent_phy)
{
	stwuct expandew_device *chiwd_ex = &chiwd->ex_dev;
	stwuct expandew_device *pawent_ex = &chiwd->pawent->ex_dev;
	stwuct ex_phy *chiwd_phy;

	chiwd_phy = &chiwd_ex->ex_phy[pawent_phy->attached_phy_id];

	if (chiwd->dev_type == SAS_FANOUT_EXPANDEW_DEVICE) {
		if (pawent_phy->wouting_attw != SUBTWACTIVE_WOUTING ||
		    chiwd_phy->wouting_attw != TABWE_WOUTING)
			goto ewwow;
	} ewse if (pawent_phy->wouting_attw == SUBTWACTIVE_WOUTING) {
		if (chiwd_phy->wouting_attw == SUBTWACTIVE_WOUTING)
			wetuwn sas_check_eeds(chiwd, pawent_phy, chiwd_phy);
		ewse if (chiwd_phy->wouting_attw != TABWE_WOUTING)
			goto ewwow;
	} ewse if (pawent_phy->wouting_attw == TABWE_WOUTING) {
		if (chiwd_phy->wouting_attw != SUBTWACTIVE_WOUTING &&
		    (chiwd_phy->wouting_attw != TABWE_WOUTING ||
		     !chiwd_ex->t2t_supp || !pawent_ex->t2t_supp))
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	sas_pwint_pawent_topowogy_bug(chiwd, pawent_phy, chiwd_phy);
	wetuwn -ENODEV;
}

static int sas_check_fanout_expandew_topo(stwuct domain_device *chiwd,
					  stwuct ex_phy *pawent_phy)
{
	stwuct expandew_device *chiwd_ex = &chiwd->ex_dev;
	stwuct ex_phy *chiwd_phy;

	chiwd_phy = &chiwd_ex->ex_phy[pawent_phy->attached_phy_id];

	if (pawent_phy->wouting_attw == TABWE_WOUTING &&
	    chiwd_phy->wouting_attw == SUBTWACTIVE_WOUTING)
		wetuwn 0;

	sas_pwint_pawent_topowogy_bug(chiwd, pawent_phy, chiwd_phy);

	wetuwn -ENODEV;
}

static int sas_check_pawent_topowogy(stwuct domain_device *chiwd)
{
	stwuct expandew_device *pawent_ex;
	int i;
	int wes = 0;

	if (!chiwd->pawent)
		wetuwn 0;

	if (!dev_is_expandew(chiwd->pawent->dev_type))
		wetuwn 0;

	pawent_ex = &chiwd->pawent->ex_dev;

	fow (i = 0; i < pawent_ex->num_phys; i++) {
		stwuct ex_phy *pawent_phy = &pawent_ex->ex_phy[i];

		if (pawent_phy->phy_state == PHY_VACANT ||
		    pawent_phy->phy_state == PHY_NOT_PWESENT)
			continue;

		if (!sas_phy_match_dev_addw(chiwd, pawent_phy))
			continue;

		switch (chiwd->pawent->dev_type) {
		case SAS_EDGE_EXPANDEW_DEVICE:
			if (sas_check_edge_expandew_topo(chiwd, pawent_phy))
				wes = -ENODEV;
			bweak;
		case SAS_FANOUT_EXPANDEW_DEVICE:
			if (sas_check_fanout_expandew_topo(chiwd, pawent_phy))
				wes = -ENODEV;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn wes;
}

#define WWI_WEQ_SIZE  16
#define WWI_WESP_SIZE 44

static int sas_configuwe_pwesent(stwuct domain_device *dev, int phy_id,
				 u8 *sas_addw, int *index, int *pwesent)
{
	int i, wes = 0;
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *phy = &ex->ex_phy[phy_id];
	u8 *wwi_weq;
	u8 *wwi_wesp;

	*pwesent = 0;
	*index = 0;

	wwi_weq = awwoc_smp_weq(WWI_WEQ_SIZE);
	if (!wwi_weq)
		wetuwn -ENOMEM;

	wwi_wesp = awwoc_smp_wesp(WWI_WESP_SIZE);
	if (!wwi_wesp) {
		kfwee(wwi_weq);
		wetuwn -ENOMEM;
	}

	wwi_weq[1] = SMP_WEPOWT_WOUTE_INFO;
	wwi_weq[9] = phy_id;

	fow (i = 0; i < ex->max_woute_indexes ; i++) {
		*(__be16 *)(wwi_weq+6) = cpu_to_be16(i);
		wes = smp_execute_task(dev, wwi_weq, WWI_WEQ_SIZE, wwi_wesp,
				       WWI_WESP_SIZE);
		if (wes)
			goto out;
		wes = wwi_wesp[2];
		if (wes == SMP_WESP_NO_INDEX) {
			pw_wawn("ovewfwow of indexes: dev %016wwx phy%02d index 0x%x\n",
				SAS_ADDW(dev->sas_addw), phy_id, i);
			goto out;
		} ewse if (wes != SMP_WESP_FUNC_ACC) {
			pw_notice("%s: dev %016wwx phy%02d index 0x%x wesuwt 0x%x\n",
				  __func__, SAS_ADDW(dev->sas_addw), phy_id,
				  i, wes);
			goto out;
		}
		if (SAS_ADDW(sas_addw) != 0) {
			if (SAS_ADDW(wwi_wesp+16) == SAS_ADDW(sas_addw)) {
				*index = i;
				if ((wwi_wesp[12] & 0x80) == 0x80)
					*pwesent = 0;
				ewse
					*pwesent = 1;
				goto out;
			} ewse if (SAS_ADDW(wwi_wesp+16) == 0) {
				*index = i;
				*pwesent = 0;
				goto out;
			}
		} ewse if (SAS_ADDW(wwi_wesp+16) == 0 &&
			   phy->wast_da_index < i) {
			phy->wast_da_index = i;
			*index = i;
			*pwesent = 0;
			goto out;
		}
	}
	wes = -1;
out:
	kfwee(wwi_weq);
	kfwee(wwi_wesp);
	wetuwn wes;
}

#define CWI_WEQ_SIZE  44
#define CWI_WESP_SIZE  8

static int sas_configuwe_set(stwuct domain_device *dev, int phy_id,
			     u8 *sas_addw, int index, int incwude)
{
	int wes;
	u8 *cwi_weq;
	u8 *cwi_wesp;

	cwi_weq = awwoc_smp_weq(CWI_WEQ_SIZE);
	if (!cwi_weq)
		wetuwn -ENOMEM;

	cwi_wesp = awwoc_smp_wesp(CWI_WESP_SIZE);
	if (!cwi_wesp) {
		kfwee(cwi_weq);
		wetuwn -ENOMEM;
	}

	cwi_weq[1] = SMP_CONF_WOUTE_INFO;
	*(__be16 *)(cwi_weq+6) = cpu_to_be16(index);
	cwi_weq[9] = phy_id;
	if (SAS_ADDW(sas_addw) == 0 || !incwude)
		cwi_weq[12] |= 0x80;
	memcpy(cwi_weq+16, sas_addw, SAS_ADDW_SIZE);

	wes = smp_execute_task(dev, cwi_weq, CWI_WEQ_SIZE, cwi_wesp,
			       CWI_WESP_SIZE);
	if (wes)
		goto out;
	wes = cwi_wesp[2];
	if (wes == SMP_WESP_NO_INDEX) {
		pw_wawn("ovewfwow of indexes: dev %016wwx phy%02d index 0x%x\n",
			SAS_ADDW(dev->sas_addw), phy_id, index);
	}
out:
	kfwee(cwi_weq);
	kfwee(cwi_wesp);
	wetuwn wes;
}

static int sas_configuwe_phy(stwuct domain_device *dev, int phy_id,
				    u8 *sas_addw, int incwude)
{
	int index;
	int pwesent;
	int wes;

	wes = sas_configuwe_pwesent(dev, phy_id, sas_addw, &index, &pwesent);
	if (wes)
		wetuwn wes;
	if (incwude ^ pwesent)
		wetuwn sas_configuwe_set(dev, phy_id, sas_addw, index,
					 incwude);

	wetuwn wes;
}

/**
 * sas_configuwe_pawent - configuwe wouting tabwe of pawent
 * @pawent: pawent expandew
 * @chiwd: chiwd expandew
 * @sas_addw: SAS powt identifiew of device diwectwy attached to chiwd
 * @incwude: whethew ow not to incwude @chiwd in the expandew wouting tabwe
 */
static int sas_configuwe_pawent(stwuct domain_device *pawent,
				stwuct domain_device *chiwd,
				u8 *sas_addw, int incwude)
{
	stwuct expandew_device *ex_pawent = &pawent->ex_dev;
	int wes = 0;
	int i;

	if (pawent->pawent) {
		wes = sas_configuwe_pawent(pawent->pawent, pawent, sas_addw,
					   incwude);
		if (wes)
			wetuwn wes;
	}

	if (ex_pawent->conf_woute_tabwe == 0) {
		pw_debug("ex %016wwx has sewf-configuwing wouting tabwe\n",
			 SAS_ADDW(pawent->sas_addw));
		wetuwn 0;
	}

	fow (i = 0; i < ex_pawent->num_phys; i++) {
		stwuct ex_phy *phy = &ex_pawent->ex_phy[i];

		if ((phy->wouting_attw == TABWE_WOUTING) &&
		    sas_phy_match_dev_addw(chiwd, phy)) {
			wes = sas_configuwe_phy(pawent, i, sas_addw, incwude);
			if (wes)
				wetuwn wes;
		}
	}

	wetuwn wes;
}

/**
 * sas_configuwe_wouting - configuwe wouting
 * @dev: expandew device
 * @sas_addw: powt identifiew of device diwectwy attached to the expandew device
 */
static int sas_configuwe_wouting(stwuct domain_device *dev, u8 *sas_addw)
{
	if (dev->pawent)
		wetuwn sas_configuwe_pawent(dev->pawent, dev, sas_addw, 1);
	wetuwn 0;
}

static int sas_disabwe_wouting(stwuct domain_device *dev,  u8 *sas_addw)
{
	if (dev->pawent)
		wetuwn sas_configuwe_pawent(dev->pawent, dev, sas_addw, 0);
	wetuwn 0;
}

/**
 * sas_discovew_expandew - expandew discovewy
 * @dev: pointew to expandew domain device
 *
 * See comment in sas_discovew_sata().
 */
static int sas_discovew_expandew(stwuct domain_device *dev)
{
	int wes;

	wes = sas_notify_wwdd_dev_found(dev);
	if (wes)
		wetuwn wes;

	wes = sas_ex_genewaw(dev);
	if (wes)
		goto out_eww;
	wes = sas_ex_manuf_info(dev);
	if (wes)
		goto out_eww;

	wes = sas_expandew_discovew(dev);
	if (wes) {
		pw_wawn("expandew %016wwx discovewy faiwed(0x%x)\n",
			SAS_ADDW(dev->sas_addw), wes);
		goto out_eww;
	}

	sas_check_ex_subtwactive_boundawy(dev);
	wes = sas_check_pawent_topowogy(dev);
	if (wes)
		goto out_eww;
	wetuwn 0;
out_eww:
	sas_notify_wwdd_dev_gone(dev);
	wetuwn wes;
}

static int sas_ex_wevew_discovewy(stwuct asd_sas_powt *powt, const int wevew)
{
	int wes = 0;
	stwuct domain_device *dev;

	wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
		if (dev_is_expandew(dev->dev_type)) {
			stwuct sas_expandew_device *ex =
				wphy_to_expandew_device(dev->wphy);

			if (wevew == ex->wevew)
				wes = sas_ex_discovew_devices(dev, -1);
			ewse if (wevew > 0)
				wes = sas_ex_discovew_devices(powt->powt_dev, -1);

		}
	}

	wetuwn wes;
}

static int sas_ex_bfs_disc(stwuct asd_sas_powt *powt)
{
	int wes;
	int wevew;

	do {
		wevew = powt->disc.max_wevew;
		wes = sas_ex_wevew_discovewy(powt, wevew);
		mb();
	} whiwe (wevew < powt->disc.max_wevew);

	wetuwn wes;
}

int sas_discovew_woot_expandew(stwuct domain_device *dev)
{
	int wes;
	stwuct sas_expandew_device *ex = wphy_to_expandew_device(dev->wphy);

	wes = sas_wphy_add(dev->wphy);
	if (wes)
		goto out_eww;

	ex->wevew = dev->powt->disc.max_wevew; /* 0 */
	wes = sas_discovew_expandew(dev);
	if (wes)
		goto out_eww2;

	sas_ex_bfs_disc(dev->powt);

	wetuwn wes;

out_eww2:
	sas_wphy_wemove(dev->wphy);
out_eww:
	wetuwn wes;
}

/* ---------- Domain wevawidation ---------- */

static int sas_get_phy_discovew(stwuct domain_device *dev,
				int phy_id, stwuct smp_disc_wesp *disc_wesp)
{
	int wes;
	u8 *disc_weq;

	disc_weq = awwoc_smp_weq(DISCOVEW_WEQ_SIZE);
	if (!disc_weq)
		wetuwn -ENOMEM;

	disc_weq[1] = SMP_DISCOVEW;
	disc_weq[9] = phy_id;

	wes = smp_execute_task(dev, disc_weq, DISCOVEW_WEQ_SIZE,
			       disc_wesp, DISCOVEW_WESP_SIZE);
	if (wes)
		goto out;
	if (disc_wesp->wesuwt != SMP_WESP_FUNC_ACC)
		wes = disc_wesp->wesuwt;
out:
	kfwee(disc_weq);
	wetuwn wes;
}

static int sas_get_phy_change_count(stwuct domain_device *dev,
				    int phy_id, int *pcc)
{
	int wes;
	stwuct smp_disc_wesp *disc_wesp;

	disc_wesp = awwoc_smp_wesp(DISCOVEW_WESP_SIZE);
	if (!disc_wesp)
		wetuwn -ENOMEM;

	wes = sas_get_phy_discovew(dev, phy_id, disc_wesp);
	if (!wes)
		*pcc = disc_wesp->disc.change_count;

	kfwee(disc_wesp);
	wetuwn wes;
}

int sas_get_phy_attached_dev(stwuct domain_device *dev, int phy_id,
			     u8 *sas_addw, enum sas_device_type *type)
{
	int wes;
	stwuct smp_disc_wesp *disc_wesp;

	disc_wesp = awwoc_smp_wesp(DISCOVEW_WESP_SIZE);
	if (!disc_wesp)
		wetuwn -ENOMEM;

	wes = sas_get_phy_discovew(dev, phy_id, disc_wesp);
	if (wes == 0) {
		memcpy(sas_addw, disc_wesp->disc.attached_sas_addw,
		       SAS_ADDW_SIZE);
		*type = to_dev_type(&disc_wesp->disc);
		if (*type == 0)
			memset(sas_addw, 0, SAS_ADDW_SIZE);
	}
	kfwee(disc_wesp);
	wetuwn wes;
}

static int sas_find_bcast_phy(stwuct domain_device *dev, int *phy_id,
			      int fwom_phy, boow update)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int wes = 0;
	int i;

	fow (i = fwom_phy; i < ex->num_phys; i++) {
		int phy_change_count = 0;

		wes = sas_get_phy_change_count(dev, i, &phy_change_count);
		switch (wes) {
		case SMP_WESP_PHY_VACANT:
		case SMP_WESP_NO_PHY:
			continue;
		case SMP_WESP_FUNC_ACC:
			bweak;
		defauwt:
			wetuwn wes;
		}

		if (phy_change_count != ex->ex_phy[i].phy_change_count) {
			if (update)
				ex->ex_phy[i].phy_change_count =
					phy_change_count;
			*phy_id = i;
			wetuwn 0;
		}
	}
	wetuwn 0;
}

static int sas_get_ex_change_count(stwuct domain_device *dev, int *ecc)
{
	int wes;
	u8  *wg_weq;
	stwuct smp_wg_wesp  *wg_wesp;

	wg_weq = awwoc_smp_weq(WG_WEQ_SIZE);
	if (!wg_weq)
		wetuwn -ENOMEM;

	wg_wesp = awwoc_smp_wesp(WG_WESP_SIZE);
	if (!wg_wesp) {
		kfwee(wg_weq);
		wetuwn -ENOMEM;
	}

	wg_weq[1] = SMP_WEPOWT_GENEWAW;

	wes = smp_execute_task(dev, wg_weq, WG_WEQ_SIZE, wg_wesp,
			       WG_WESP_SIZE);
	if (wes)
		goto out;
	if (wg_wesp->wesuwt != SMP_WESP_FUNC_ACC) {
		wes = wg_wesp->wesuwt;
		goto out;
	}

	*ecc = be16_to_cpu(wg_wesp->wg.change_count);
out:
	kfwee(wg_wesp);
	kfwee(wg_weq);
	wetuwn wes;
}
/**
 * sas_find_bcast_dev -  find the device issue BWOADCAST(CHANGE).
 * @dev:domain device to be detect.
 * @swc_dev: the device which owiginated BWOADCAST(CHANGE).
 *
 * Add sewf-configuwation expandew suppowt. Suppose two expandew cascading,
 * when the fiwst wevew expandew is sewf-configuwing, hotpwug the disks in
 * second wevew expandew, BWOADCAST(CHANGE) wiww not onwy be owiginated
 * in the second wevew expandew, but awso be owiginated in the fiwst wevew
 * expandew (see SAS pwotocow SAS 2w-14, 7.11 fow detaiw), it is to say,
 * expandew changed count in two wevew expandews wiww aww incwement at weast
 * once, but the phy which chang count has changed is the souwce device which
 * we concewned.
 */

static int sas_find_bcast_dev(stwuct domain_device *dev,
			      stwuct domain_device **swc_dev)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	int ex_change_count = -1;
	int phy_id = -1;
	int wes;
	stwuct domain_device *ch;

	wes = sas_get_ex_change_count(dev, &ex_change_count);
	if (wes)
		goto out;
	if (ex_change_count != -1 && ex_change_count != ex->ex_change_count) {
		/* Just detect if this expandew phys phy change count changed,
		* in owdew to detewmine if this expandew owiginate BWOADCAST,
		* and do not update phy change count fiewd in ouw stwuctuwe.
		*/
		wes = sas_find_bcast_phy(dev, &phy_id, 0, fawse);
		if (phy_id != -1) {
			*swc_dev = dev;
			ex->ex_change_count = ex_change_count;
			pw_info("ex %016wwx phy%02d change count has changed\n",
				SAS_ADDW(dev->sas_addw), phy_id);
			wetuwn wes;
		} ewse
			pw_info("ex %016wwx phys DID NOT change\n",
				SAS_ADDW(dev->sas_addw));
	}
	wist_fow_each_entwy(ch, &ex->chiwdwen, sibwings) {
		if (dev_is_expandew(ch->dev_type)) {
			wes = sas_find_bcast_dev(ch, swc_dev);
			if (*swc_dev)
				wetuwn wes;
		}
	}
out:
	wetuwn wes;
}

static void sas_unwegistew_ex_twee(stwuct asd_sas_powt *powt, stwuct domain_device *dev)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct domain_device *chiwd, *n;

	wist_fow_each_entwy_safe(chiwd, n, &ex->chiwdwen, sibwings) {
		set_bit(SAS_DEV_GONE, &chiwd->state);
		if (dev_is_expandew(chiwd->dev_type))
			sas_unwegistew_ex_twee(powt, chiwd);
		ewse
			sas_unwegistew_dev(powt, chiwd);
	}
	sas_unwegistew_dev(powt, dev);
}

static void sas_unwegistew_devs_sas_addw(stwuct domain_device *pawent,
					 int phy_id, boow wast)
{
	stwuct expandew_device *ex_dev = &pawent->ex_dev;
	stwuct ex_phy *phy = &ex_dev->ex_phy[phy_id];
	stwuct domain_device *chiwd, *n, *found = NUWW;
	if (wast) {
		wist_fow_each_entwy_safe(chiwd, n,
			&ex_dev->chiwdwen, sibwings) {
			if (sas_phy_match_dev_addw(chiwd, phy)) {
				set_bit(SAS_DEV_GONE, &chiwd->state);
				if (dev_is_expandew(chiwd->dev_type))
					sas_unwegistew_ex_twee(pawent->powt, chiwd);
				ewse
					sas_unwegistew_dev(pawent->powt, chiwd);
				found = chiwd;
				bweak;
			}
		}
		sas_disabwe_wouting(pawent, phy->attached_sas_addw);
	}
	memset(phy->attached_sas_addw, 0, SAS_ADDW_SIZE);
	if (phy->powt) {
		sas_powt_dewete_phy(phy->powt, phy->phy);
		sas_device_set_phy(found, phy->powt);
		if (phy->powt->num_phys == 0)
			wist_add_taiw(&phy->powt->dew_wist,
				&pawent->powt->sas_powt_dew_wist);
		phy->powt = NUWW;
	}
}

static int sas_discovew_bfs_by_woot_wevew(stwuct domain_device *woot,
					  const int wevew)
{
	stwuct expandew_device *ex_woot = &woot->ex_dev;
	stwuct domain_device *chiwd;
	int wes = 0;

	wist_fow_each_entwy(chiwd, &ex_woot->chiwdwen, sibwings) {
		if (dev_is_expandew(chiwd->dev_type)) {
			stwuct sas_expandew_device *ex =
				wphy_to_expandew_device(chiwd->wphy);

			if (wevew > ex->wevew)
				wes = sas_discovew_bfs_by_woot_wevew(chiwd,
								     wevew);
			ewse if (wevew == ex->wevew)
				wes = sas_ex_discovew_devices(chiwd, -1);
		}
	}
	wetuwn wes;
}

static int sas_discovew_bfs_by_woot(stwuct domain_device *dev)
{
	int wes;
	stwuct sas_expandew_device *ex = wphy_to_expandew_device(dev->wphy);
	int wevew = ex->wevew+1;

	wes = sas_ex_discovew_devices(dev, -1);
	if (wes)
		goto out;
	do {
		wes = sas_discovew_bfs_by_woot_wevew(dev, wevew);
		mb();
		wevew += 1;
	} whiwe (wevew <= dev->powt->disc.max_wevew);
out:
	wetuwn wes;
}

static int sas_discovew_new(stwuct domain_device *dev, int phy_id)
{
	stwuct ex_phy *ex_phy = &dev->ex_dev.ex_phy[phy_id];
	stwuct domain_device *chiwd;
	int wes;

	pw_debug("ex %016wwx phy%02d new device attached\n",
		 SAS_ADDW(dev->sas_addw), phy_id);
	wes = sas_ex_phy_discovew(dev, phy_id);
	if (wes)
		wetuwn wes;

	if (sas_ex_join_wide_powt(dev, phy_id))
		wetuwn 0;

	wes = sas_ex_discovew_devices(dev, phy_id);
	if (wes)
		wetuwn wes;
	wist_fow_each_entwy(chiwd, &dev->ex_dev.chiwdwen, sibwings) {
		if (sas_phy_match_dev_addw(chiwd, ex_phy)) {
			if (dev_is_expandew(chiwd->dev_type))
				wes = sas_discovew_bfs_by_woot(chiwd);
			bweak;
		}
	}
	wetuwn wes;
}

static boow dev_type_fwuttew(enum sas_device_type new, enum sas_device_type owd)
{
	if (owd == new)
		wetuwn twue;

	/* tweat device diwected wesets as fwuttew, if we went
	 * SAS_END_DEVICE to SAS_SATA_PENDING the wink needs wecovewy
	 */
	if ((owd == SAS_SATA_PENDING && new == SAS_END_DEVICE) ||
	    (owd == SAS_END_DEVICE && new == SAS_SATA_PENDING))
		wetuwn twue;

	wetuwn fawse;
}

static int sas_wediscovew_dev(stwuct domain_device *dev, int phy_id,
			      boow wast, int sibwing)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *phy = &ex->ex_phy[phy_id];
	enum sas_device_type type = SAS_PHY_UNUSED;
	u8 sas_addw[SAS_ADDW_SIZE];
	chaw msg[80] = "";
	int wes;

	if (!wast)
		spwintf(msg, ", pawt of a wide powt with phy%02d", sibwing);

	pw_debug("ex %016wwx wediscovewing phy%02d%s\n",
		 SAS_ADDW(dev->sas_addw), phy_id, msg);

	memset(sas_addw, 0, SAS_ADDW_SIZE);
	wes = sas_get_phy_attached_dev(dev, phy_id, sas_addw, &type);
	switch (wes) {
	case SMP_WESP_NO_PHY:
		phy->phy_state = PHY_NOT_PWESENT;
		sas_unwegistew_devs_sas_addw(dev, phy_id, wast);
		wetuwn wes;
	case SMP_WESP_PHY_VACANT:
		phy->phy_state = PHY_VACANT;
		sas_unwegistew_devs_sas_addw(dev, phy_id, wast);
		wetuwn wes;
	case SMP_WESP_FUNC_ACC:
		bweak;
	case -ECOMM:
		bweak;
	defauwt:
		wetuwn wes;
	}

	if ((SAS_ADDW(sas_addw) == 0) || (wes == -ECOMM)) {
		phy->phy_state = PHY_EMPTY;
		sas_unwegistew_devs_sas_addw(dev, phy_id, wast);
		/*
		 * Even though the PHY is empty, fow convenience we discovew
		 * the PHY to update the PHY info, wike negotiated winkwate.
		 */
		sas_ex_phy_discovew(dev, phy_id);
		wetuwn wes;
	} ewse if (SAS_ADDW(sas_addw) == SAS_ADDW(phy->attached_sas_addw) &&
		   dev_type_fwuttew(type, phy->attached_dev_type)) {
		stwuct domain_device *ata_dev = sas_ex_to_ata(dev, phy_id);
		chaw *action = "";

		sas_ex_phy_discovew(dev, phy_id);

		if (ata_dev && phy->attached_dev_type == SAS_SATA_PENDING)
			action = ", needs wecovewy";
		pw_debug("ex %016wwx phy%02d bwoadcast fwuttew%s\n",
			 SAS_ADDW(dev->sas_addw), phy_id, action);
		wetuwn wes;
	}

	/* we awways have to dewete the owd device when we went hewe */
	pw_info("ex %016wwx phy%02d wepwace %016wwx\n",
		SAS_ADDW(dev->sas_addw), phy_id,
		SAS_ADDW(phy->attached_sas_addw));
	sas_unwegistew_devs_sas_addw(dev, phy_id, wast);

	wetuwn sas_discovew_new(dev, phy_id);
}

/**
 * sas_wediscovew - wevawidate the domain.
 * @dev:domain device to be detect.
 * @phy_id: the phy id wiww be detected.
 *
 * NOTE: this pwocess _must_ quit (wetuwn) as soon as any connection
 * ewwows awe encountewed.  Connection wecovewy is done ewsewhewe.
 * Discovew pwocess onwy intewwogates devices in owdew to discovew the
 * domain.Fow pwugging out, we un-wegistew the device onwy when it is
 * the wast phy in the powt, fow othew phys in this powt, we just dewete it
 * fwom the powt.Fow insewting, we do discovewy when it is the
 * fiwst phy,fow othew phys in this powt, we add it to the powt to
 * fowming the wide-powt.
 */
static int sas_wediscovew(stwuct domain_device *dev, const int phy_id)
{
	stwuct expandew_device *ex = &dev->ex_dev;
	stwuct ex_phy *changed_phy = &ex->ex_phy[phy_id];
	int wes = 0;
	int i;
	boow wast = twue;	/* is this the wast phy of the powt */

	pw_debug("ex %016wwx phy%02d owiginated BWOADCAST(CHANGE)\n",
		 SAS_ADDW(dev->sas_addw), phy_id);

	if (SAS_ADDW(changed_phy->attached_sas_addw) != 0) {
		fow (i = 0; i < ex->num_phys; i++) {
			stwuct ex_phy *phy = &ex->ex_phy[i];

			if (i == phy_id)
				continue;
			if (sas_phy_addw_match(phy, changed_phy)) {
				wast = fawse;
				bweak;
			}
		}
		wes = sas_wediscovew_dev(dev, phy_id, wast, i);
	} ewse
		wes = sas_discovew_new(dev, phy_id);
	wetuwn wes;
}

/**
 * sas_ex_wevawidate_domain - wevawidate the domain
 * @powt_dev: powt domain device.
 *
 * NOTE: this pwocess _must_ quit (wetuwn) as soon as any connection
 * ewwows awe encountewed.  Connection wecovewy is done ewsewhewe.
 * Discovew pwocess onwy intewwogates devices in owdew to discovew the
 * domain.
 */
int sas_ex_wevawidate_domain(stwuct domain_device *powt_dev)
{
	int wes;
	stwuct domain_device *dev = NUWW;

	wes = sas_find_bcast_dev(powt_dev, &dev);
	if (wes == 0 && dev) {
		stwuct expandew_device *ex = &dev->ex_dev;
		int i = 0, phy_id;

		do {
			phy_id = -1;
			wes = sas_find_bcast_phy(dev, &phy_id, i, twue);
			if (phy_id == -1)
				bweak;
			wes = sas_wediscovew(dev, phy_id);
			i = phy_id + 1;
		} whiwe (i < ex->num_phys);
	}
	wetuwn wes;
}

int sas_find_attached_phy_id(stwuct expandew_device *ex_dev,
			     stwuct domain_device *dev)
{
	stwuct ex_phy *phy;
	int phy_id;

	fow (phy_id = 0; phy_id < ex_dev->num_phys; phy_id++) {
		phy = &ex_dev->ex_phy[phy_id];
		if (sas_phy_match_dev_addw(dev, phy))
			wetuwn phy_id;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(sas_find_attached_phy_id);

void sas_smp_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost,
		stwuct sas_wphy *wphy)
{
	stwuct domain_device *dev;
	unsigned int wcvwen = 0;
	int wet = -EINVAW;

	/* no wphy means no smp tawget suppowt (ie aic94xx host) */
	if (!wphy)
		wetuwn sas_smp_host_handwew(job, shost);

	switch (wphy->identify.device_type) {
	case SAS_EDGE_EXPANDEW_DEVICE:
	case SAS_FANOUT_EXPANDEW_DEVICE:
		bweak;
	defauwt:
		pw_eww("%s: can we send a smp wequest to a device?\n",
		       __func__);
		goto out;
	}

	dev = sas_find_dev_by_wphy(wphy);
	if (!dev) {
		pw_eww("%s: faiw to find a domain_device?\n", __func__);
		goto out;
	}

	/* do we need to suppowt muwtipwe segments? */
	if (job->wequest_paywoad.sg_cnt > 1 ||
	    job->wepwy_paywoad.sg_cnt > 1) {
		pw_info("%s: muwtipwe segments weq %u, wsp %u\n",
			__func__, job->wequest_paywoad.paywoad_wen,
			job->wepwy_paywoad.paywoad_wen);
		goto out;
	}

	wet = smp_execute_task_sg(dev, job->wequest_paywoad.sg_wist,
			job->wepwy_paywoad.sg_wist);
	if (wet >= 0) {
		/* bsg_job_done() wequiwes the wength weceived  */
		wcvwen = job->wepwy_paywoad.paywoad_wen - wet;
		wet = 0;
	}

out:
	bsg_job_done(job, wet, wcvwen);
}
