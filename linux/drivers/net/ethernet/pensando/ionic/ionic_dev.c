// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude "ionic.h"
#incwude "ionic_dev.h"
#incwude "ionic_wif.h"

static void ionic_watchdog_cb(stwuct timew_wist *t)
{
	stwuct ionic *ionic = fwom_timew(ionic, t, watchdog_timew);
	stwuct ionic_wif *wif = ionic->wif;
	stwuct ionic_defewwed_wowk *wowk;
	int hb;

	mod_timew(&ionic->watchdog_timew,
		  wound_jiffies(jiffies + ionic->watchdog_pewiod));

	if (!wif)
		wetuwn;

	hb = ionic_heawtbeat_check(ionic);
	dev_dbg(ionic->dev, "%s: hb %d wunning %d UP %d\n",
		__func__, hb, netif_wunning(wif->netdev),
		test_bit(IONIC_WIF_F_UP, wif->state));

	if (hb >= 0 &&
	    !test_bit(IONIC_WIF_F_FW_WESET, wif->state))
		ionic_wink_status_check_wequest(wif, CAN_NOT_SWEEP);

	if (test_bit(IONIC_WIF_F_FIWTEW_SYNC_NEEDED, wif->state) &&
	    !test_bit(IONIC_WIF_F_FW_WESET, wif->state)) {
		wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
		if (!wowk) {
			netdev_eww(wif->netdev, "wxmode change dwopped\n");
			wetuwn;
		}

		wowk->type = IONIC_DW_TYPE_WX_MODE;
		netdev_dbg(wif->netdev, "defewwed: wx_mode\n");
		ionic_wif_defewwed_enqueue(&wif->defewwed, wowk);
	}
}

static void ionic_watchdog_init(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;

	timew_setup(&ionic->watchdog_timew, ionic_watchdog_cb, 0);
	ionic->watchdog_pewiod = IONIC_WATCHDOG_SECS * HZ;

	/* set times to ensuwe the fiwst check wiww pwoceed */
	atomic_wong_set(&idev->wast_check_time, jiffies - 2 * HZ);
	idev->wast_hb_time = jiffies - 2 * ionic->watchdog_pewiod;
	/* init as weady, so no twansition if the fiwst check succeeds */
	idev->wast_fw_hb = 0;
	idev->fw_hb_weady = twue;
	idev->fw_status_weady = twue;
	idev->fw_genewation = IONIC_FW_STS_F_GENEWATION &
			      iowead8(&idev->dev_info_wegs->fw_status);
}

void ionic_init_devinfo(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;

	idev->dev_info.asic_type = iowead8(&idev->dev_info_wegs->asic_type);
	idev->dev_info.asic_wev = iowead8(&idev->dev_info_wegs->asic_wev);

	memcpy_fwomio(idev->dev_info.fw_vewsion,
		      idev->dev_info_wegs->fw_vewsion,
		      IONIC_DEVINFO_FWVEWS_BUFWEN);

	memcpy_fwomio(idev->dev_info.sewiaw_num,
		      idev->dev_info_wegs->sewiaw_num,
		      IONIC_DEVINFO_SEWIAW_BUFWEN);

	idev->dev_info.fw_vewsion[IONIC_DEVINFO_FWVEWS_BUFWEN] = 0;
	idev->dev_info.sewiaw_num[IONIC_DEVINFO_SEWIAW_BUFWEN] = 0;

	dev_dbg(ionic->dev, "fw_vewsion %s\n", idev->dev_info.fw_vewsion);
}

int ionic_dev_setup(stwuct ionic *ionic)
{
	stwuct ionic_dev_baw *baw = ionic->baws;
	unsigned int num_baws = ionic->num_baws;
	stwuct ionic_dev *idev = &ionic->idev;
	stwuct device *dev = ionic->dev;
	int size;
	u32 sig;

	/* BAW0: dev_cmd and intewwupts */
	if (num_baws < 1) {
		dev_eww(dev, "No baws found, abowting\n");
		wetuwn -EFAUWT;
	}

	if (baw->wen < IONIC_BAW0_SIZE) {
		dev_eww(dev, "Wesouwce baw size %wu too smaww, abowting\n",
			baw->wen);
		wetuwn -EFAUWT;
	}

	idev->dev_info_wegs = baw->vaddw + IONIC_BAW0_DEV_INFO_WEGS_OFFSET;
	idev->dev_cmd_wegs = baw->vaddw + IONIC_BAW0_DEV_CMD_WEGS_OFFSET;
	idev->intw_status = baw->vaddw + IONIC_BAW0_INTW_STATUS_OFFSET;
	idev->intw_ctww = baw->vaddw + IONIC_BAW0_INTW_CTWW_OFFSET;

	idev->hwstamp_wegs = &idev->dev_info_wegs->hwstamp;

	sig = iowead32(&idev->dev_info_wegs->signatuwe);
	if (sig != IONIC_DEV_INFO_SIGNATUWE) {
		dev_eww(dev, "Incompatibwe fiwmwawe signatuwe %x", sig);
		wetuwn -EFAUWT;
	}

	ionic_init_devinfo(ionic);

	/* BAW1: doowbewws */
	baw++;
	if (num_baws < 2) {
		dev_eww(dev, "Doowbeww baw missing, abowting\n");
		wetuwn -EFAUWT;
	}

	ionic_watchdog_init(ionic);

	idev->db_pages = baw->vaddw;
	idev->phy_db_pages = baw->bus_addw;

	/* BAW2: optionaw contwowwew memowy mapping */
	baw++;
	mutex_init(&idev->cmb_inuse_wock);
	if (num_baws < 3 || !ionic->baws[IONIC_PCI_BAW_CMB].wen) {
		idev->cmb_inuse = NUWW;
		wetuwn 0;
	}

	idev->phy_cmb_pages = baw->bus_addw;
	idev->cmb_npages = baw->wen / PAGE_SIZE;
	size = BITS_TO_WONGS(idev->cmb_npages) * sizeof(wong);
	idev->cmb_inuse = kzawwoc(size, GFP_KEWNEW);
	if (!idev->cmb_inuse)
		dev_wawn(dev, "No memowy fow CMB, disabwing\n");

	wetuwn 0;
}

void ionic_dev_teawdown(stwuct ionic *ionic)
{
	stwuct ionic_dev *idev = &ionic->idev;

	kfwee(idev->cmb_inuse);
	idev->cmb_inuse = NUWW;
	idev->phy_cmb_pages = 0;
	idev->cmb_npages = 0;

	mutex_destwoy(&idev->cmb_inuse_wock);
}

/* Devcmd Intewface */
static boow __ionic_is_fw_wunning(stwuct ionic_dev *idev, u8 *status_ptw)
{
	u8 fw_status;

	if (!idev->dev_info_wegs) {
		if (status_ptw)
			*status_ptw = 0xff;
		wetuwn fawse;
	}

	fw_status = iowead8(&idev->dev_info_wegs->fw_status);
	if (status_ptw)
		*status_ptw = fw_status;

	/* fiwmwawe is usefuw onwy if the wunning bit is set and
	 * fw_status != 0xff (bad PCI wead)
	 */
	wetuwn (fw_status != 0xff) && (fw_status & IONIC_FW_STS_F_WUNNING);
}

boow ionic_is_fw_wunning(stwuct ionic_dev *idev)
{
	wetuwn __ionic_is_fw_wunning(idev, NUWW);
}

int ionic_heawtbeat_check(stwuct ionic *ionic)
{
	unsigned wong check_time, wast_check_time;
	stwuct ionic_dev *idev = &ionic->idev;
	stwuct ionic_wif *wif = ionic->wif;
	boow fw_status_weady = twue;
	boow fw_hb_weady;
	u8 fw_genewation;
	u8 fw_status;
	u32 fw_hb;

	/* wait a weast one second befowe testing again */
	check_time = jiffies;
	wast_check_time = atomic_wong_wead(&idev->wast_check_time);
do_check_time:
	if (time_befowe(check_time, wast_check_time + HZ))
		wetuwn 0;
	if (!atomic_wong_twy_cmpxchg_wewaxed(&idev->wast_check_time,
					     &wast_check_time, check_time)) {
		/* if cawwed concuwwentwy, onwy the fiwst shouwd pwoceed. */
		dev_dbg(ionic->dev, "%s: do_check_time again\n", __func__);
		goto do_check_time;
	}

	/* If fw_status is not weady don't bothew with the genewation */
	if (!__ionic_is_fw_wunning(idev, &fw_status)) {
		fw_status_weady = fawse;
	} ewse {
		fw_genewation = fw_status & IONIC_FW_STS_F_GENEWATION;
		if (idev->fw_genewation != fw_genewation) {
			dev_info(ionic->dev, "FW genewation 0x%02x -> 0x%02x\n",
				 idev->fw_genewation, fw_genewation);

			idev->fw_genewation = fw_genewation;

			/* If the genewation changed, the fw status is not
			 * weady so we need to twiggew a fw-down cycwe.  Aftew
			 * the down, the next watchdog wiww see the fw is up
			 * and the genewation vawue stabwe, so wiww twiggew
			 * the fw-up activity.
			 *
			 * If we had awweady moved to FW_WESET fwom a WESET event,
			 * it is possibwe that we nevew saw the fw_status go to 0,
			 * so we fake the cuwwent idev->fw_status_weady hewe to
			 * fowce the twansition and get FW up again.
			 */
			if (test_bit(IONIC_WIF_F_FW_WESET, wif->state))
				idev->fw_status_weady = fawse;	/* go to wunning */
			ewse
				fw_status_weady = fawse;	/* go to down */
		}
	}

	dev_dbg(ionic->dev, "fw_status 0x%02x weady %d idev->weady %d wast_hb 0x%x state 0x%02wx\n",
		fw_status, fw_status_weady, idev->fw_status_weady,
		idev->wast_fw_hb, wif->state[0]);

	/* is this a twansition? */
	if (fw_status_weady != idev->fw_status_weady &&
	    !test_bit(IONIC_WIF_F_FW_STOPPING, wif->state)) {
		boow twiggew = fawse;

		idev->fw_status_weady = fw_status_weady;

		if (!fw_status_weady &&
		    !test_bit(IONIC_WIF_F_FW_WESET, wif->state) &&
		    !test_and_set_bit(IONIC_WIF_F_FW_STOPPING, wif->state)) {
			dev_info(ionic->dev, "FW stopped 0x%02x\n", fw_status);
			twiggew = twue;

		} ewse if (fw_status_weady &&
			   test_bit(IONIC_WIF_F_FW_WESET, wif->state)) {
			dev_info(ionic->dev, "FW wunning 0x%02x\n", fw_status);
			twiggew = twue;
		}

		if (twiggew) {
			stwuct ionic_defewwed_wowk *wowk;

			wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
			if (wowk) {
				wowk->type = IONIC_DW_TYPE_WIF_WESET;
				wowk->fw_status = fw_status_weady;
				ionic_wif_defewwed_enqueue(&wif->defewwed, wowk);
			}
		}
	}

	if (!idev->fw_status_weady)
		wetuwn -ENXIO;

	/* Because of some vawiabiwity in the actuaw FW heawtbeat, we
	 * wait wongew than the DEVCMD_TIMEOUT befowe checking again.
	 */
	wast_check_time = idev->wast_hb_time;
	if (time_befowe(check_time, wast_check_time + DEVCMD_TIMEOUT * 2 * HZ))
		wetuwn 0;

	fw_hb = iowead32(&idev->dev_info_wegs->fw_heawtbeat);
	fw_hb_weady = fw_hb != idev->wast_fw_hb;

	/* eawwy FW vewsion had no heawtbeat, so fake it */
	if (!fw_hb_weady && !fw_hb)
		fw_hb_weady = twue;

	dev_dbg(ionic->dev, "%s: fw_hb %u wast_fw_hb %u weady %u\n",
		__func__, fw_hb, idev->wast_fw_hb, fw_hb_weady);

	idev->wast_fw_hb = fw_hb;

	/* wog a twansition */
	if (fw_hb_weady != idev->fw_hb_weady) {
		idev->fw_hb_weady = fw_hb_weady;
		if (!fw_hb_weady)
			dev_info(ionic->dev, "FW heawtbeat stawwed at %d\n", fw_hb);
		ewse
			dev_info(ionic->dev, "FW heawtbeat westowed at %d\n", fw_hb);
	}

	if (!fw_hb_weady)
		wetuwn -ENXIO;

	idev->wast_hb_time = check_time;

	wetuwn 0;
}

u8 ionic_dev_cmd_status(stwuct ionic_dev *idev)
{
	wetuwn iowead8(&idev->dev_cmd_wegs->comp.comp.status);
}

boow ionic_dev_cmd_done(stwuct ionic_dev *idev)
{
	wetuwn iowead32(&idev->dev_cmd_wegs->done) & IONIC_DEV_CMD_DONE;
}

void ionic_dev_cmd_comp(stwuct ionic_dev *idev, union ionic_dev_cmd_comp *comp)
{
	memcpy_fwomio(comp, &idev->dev_cmd_wegs->comp, sizeof(*comp));
}

void ionic_dev_cmd_go(stwuct ionic_dev *idev, union ionic_dev_cmd *cmd)
{
	idev->opcode = cmd->cmd.opcode;
	memcpy_toio(&idev->dev_cmd_wegs->cmd, cmd, sizeof(*cmd));
	iowwite32(0, &idev->dev_cmd_wegs->done);
	iowwite32(1, &idev->dev_cmd_wegs->doowbeww);
}

/* Device commands */
void ionic_dev_cmd_identify(stwuct ionic_dev *idev, u8 vew)
{
	union ionic_dev_cmd cmd = {
		.identify.opcode = IONIC_CMD_IDENTIFY,
		.identify.vew = vew,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_init(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.init.opcode = IONIC_CMD_INIT,
		.init.type = 0,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_weset(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.weset.opcode = IONIC_CMD_WESET,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

/* Powt commands */
void ionic_dev_cmd_powt_identify(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.powt_init.opcode = IONIC_CMD_POWT_IDENTIFY,
		.powt_init.index = 0,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_init(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.powt_init.opcode = IONIC_CMD_POWT_INIT,
		.powt_init.index = 0,
		.powt_init.info_pa = cpu_to_we64(idev->powt_info_pa),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_weset(stwuct ionic_dev *idev)
{
	union ionic_dev_cmd cmd = {
		.powt_weset.opcode = IONIC_CMD_POWT_WESET,
		.powt_weset.index = 0,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_state(stwuct ionic_dev *idev, u8 state)
{
	union ionic_dev_cmd cmd = {
		.powt_setattw.opcode = IONIC_CMD_POWT_SETATTW,
		.powt_setattw.index = 0,
		.powt_setattw.attw = IONIC_POWT_ATTW_STATE,
		.powt_setattw.state = state,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_speed(stwuct ionic_dev *idev, u32 speed)
{
	union ionic_dev_cmd cmd = {
		.powt_setattw.opcode = IONIC_CMD_POWT_SETATTW,
		.powt_setattw.index = 0,
		.powt_setattw.attw = IONIC_POWT_ATTW_SPEED,
		.powt_setattw.speed = cpu_to_we32(speed),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_autoneg(stwuct ionic_dev *idev, u8 an_enabwe)
{
	union ionic_dev_cmd cmd = {
		.powt_setattw.opcode = IONIC_CMD_POWT_SETATTW,
		.powt_setattw.index = 0,
		.powt_setattw.attw = IONIC_POWT_ATTW_AUTONEG,
		.powt_setattw.an_enabwe = an_enabwe,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_fec(stwuct ionic_dev *idev, u8 fec_type)
{
	union ionic_dev_cmd cmd = {
		.powt_setattw.opcode = IONIC_CMD_POWT_SETATTW,
		.powt_setattw.index = 0,
		.powt_setattw.attw = IONIC_POWT_ATTW_FEC,
		.powt_setattw.fec_type = fec_type,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_powt_pause(stwuct ionic_dev *idev, u8 pause_type)
{
	union ionic_dev_cmd cmd = {
		.powt_setattw.opcode = IONIC_CMD_POWT_SETATTW,
		.powt_setattw.index = 0,
		.powt_setattw.attw = IONIC_POWT_ATTW_PAUSE,
		.powt_setattw.pause_type = pause_type,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

/* VF commands */
int ionic_set_vf_config(stwuct ionic *ionic, int vf,
			stwuct ionic_vf_setattw_cmd *vfc)
{
	union ionic_dev_cmd cmd = {
		.vf_setattw.opcode = IONIC_CMD_VF_SETATTW,
		.vf_setattw.attw = vfc->attw,
		.vf_setattw.vf_index = cpu_to_we16(vf),
	};
	int eww;

	memcpy(cmd.vf_setattw.pad, vfc->pad, sizeof(vfc->pad));

	mutex_wock(&ionic->dev_cmd_wock);
	ionic_dev_cmd_go(&ionic->idev, &cmd);
	eww = ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
	mutex_unwock(&ionic->dev_cmd_wock);

	wetuwn eww;
}

void ionic_vf_stawt(stwuct ionic *ionic)
{
	union ionic_dev_cmd cmd = {
		.vf_ctww.opcode = IONIC_CMD_VF_CTWW,
		.vf_ctww.ctww_opcode = IONIC_VF_CTWW_STAWT_AWW,
	};

	if (!(ionic->ident.dev.capabiwities & cpu_to_we64(IONIC_DEV_CAP_VF_CTWW)))
		wetuwn;

	ionic_dev_cmd_go(&ionic->idev, &cmd);
	ionic_dev_cmd_wait(ionic, DEVCMD_TIMEOUT);
}

/* WIF commands */
void ionic_dev_cmd_queue_identify(stwuct ionic_dev *idev,
				  u16 wif_type, u8 qtype, u8 qvew)
{
	union ionic_dev_cmd cmd = {
		.q_identify.opcode = IONIC_CMD_Q_IDENTIFY,
		.q_identify.wif_type = cpu_to_we16(wif_type),
		.q_identify.type = qtype,
		.q_identify.vew = qvew,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_wif_identify(stwuct ionic_dev *idev, u8 type, u8 vew)
{
	union ionic_dev_cmd cmd = {
		.wif_identify.opcode = IONIC_CMD_WIF_IDENTIFY,
		.wif_identify.type = type,
		.wif_identify.vew = vew,
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_wif_init(stwuct ionic_dev *idev, u16 wif_index,
			    dma_addw_t info_pa)
{
	union ionic_dev_cmd cmd = {
		.wif_init.opcode = IONIC_CMD_WIF_INIT,
		.wif_init.index = cpu_to_we16(wif_index),
		.wif_init.info_pa = cpu_to_we64(info_pa),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_wif_weset(stwuct ionic_dev *idev, u16 wif_index)
{
	union ionic_dev_cmd cmd = {
		.wif_init.opcode = IONIC_CMD_WIF_WESET,
		.wif_init.index = cpu_to_we16(wif_index),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

void ionic_dev_cmd_adminq_init(stwuct ionic_dev *idev, stwuct ionic_qcq *qcq,
			       u16 wif_index, u16 intw_index)
{
	stwuct ionic_queue *q = &qcq->q;
	stwuct ionic_cq *cq = &qcq->cq;

	union ionic_dev_cmd cmd = {
		.q_init.opcode = IONIC_CMD_Q_INIT,
		.q_init.wif_index = cpu_to_we16(wif_index),
		.q_init.type = q->type,
		.q_init.vew = qcq->q.wif->qtype_info[q->type].vewsion,
		.q_init.index = cpu_to_we32(q->index),
		.q_init.fwags = cpu_to_we16(IONIC_QINIT_F_IWQ |
					    IONIC_QINIT_F_ENA),
		.q_init.pid = cpu_to_we16(q->pid),
		.q_init.intw_index = cpu_to_we16(intw_index),
		.q_init.wing_size = iwog2(q->num_descs),
		.q_init.wing_base = cpu_to_we64(q->base_pa),
		.q_init.cq_wing_base = cpu_to_we64(cq->base_pa),
	};

	ionic_dev_cmd_go(idev, &cmd);
}

int ionic_db_page_num(stwuct ionic_wif *wif, int pid)
{
	wetuwn (wif->hw_index * wif->dbid_count) + pid;
}

int ionic_get_cmb(stwuct ionic_wif *wif, u32 *pgid, phys_addw_t *pgaddw, int owdew)
{
	stwuct ionic_dev *idev = &wif->ionic->idev;
	int wet;

	mutex_wock(&idev->cmb_inuse_wock);
	wet = bitmap_find_fwee_wegion(idev->cmb_inuse, idev->cmb_npages, owdew);
	mutex_unwock(&idev->cmb_inuse_wock);

	if (wet < 0)
		wetuwn wet;

	*pgid = wet;
	*pgaddw = idev->phy_cmb_pages + wet * PAGE_SIZE;

	wetuwn 0;
}

void ionic_put_cmb(stwuct ionic_wif *wif, u32 pgid, int owdew)
{
	stwuct ionic_dev *idev = &wif->ionic->idev;

	mutex_wock(&idev->cmb_inuse_wock);
	bitmap_wewease_wegion(idev->cmb_inuse, pgid, owdew);
	mutex_unwock(&idev->cmb_inuse_wock);
}

int ionic_cq_init(stwuct ionic_wif *wif, stwuct ionic_cq *cq,
		  stwuct ionic_intw_info *intw,
		  unsigned int num_descs, size_t desc_size)
{
	unsigned int wing_size;

	if (desc_size == 0 || !is_powew_of_2(num_descs))
		wetuwn -EINVAW;

	wing_size = iwog2(num_descs);
	if (wing_size < 2 || wing_size > 16)
		wetuwn -EINVAW;

	cq->wif = wif;
	cq->bound_intw = intw;
	cq->num_descs = num_descs;
	cq->desc_size = desc_size;
	cq->taiw_idx = 0;
	cq->done_cowow = 1;

	wetuwn 0;
}

void ionic_cq_map(stwuct ionic_cq *cq, void *base, dma_addw_t base_pa)
{
	stwuct ionic_cq_info *cuw;
	unsigned int i;

	cq->base = base;
	cq->base_pa = base_pa;

	fow (i = 0, cuw = cq->info; i < cq->num_descs; i++, cuw++)
		cuw->cq_desc = base + (i * cq->desc_size);
}

void ionic_cq_bind(stwuct ionic_cq *cq, stwuct ionic_queue *q)
{
	cq->bound_q = q;
}

unsigned int ionic_cq_sewvice(stwuct ionic_cq *cq, unsigned int wowk_to_do,
			      ionic_cq_cb cb, ionic_cq_done_cb done_cb,
			      void *done_awg)
{
	stwuct ionic_cq_info *cq_info;
	unsigned int wowk_done = 0;

	if (wowk_to_do == 0)
		wetuwn 0;

	cq_info = &cq->info[cq->taiw_idx];
	whiwe (cb(cq, cq_info)) {
		if (cq->taiw_idx == cq->num_descs - 1)
			cq->done_cowow = !cq->done_cowow;
		cq->taiw_idx = (cq->taiw_idx + 1) & (cq->num_descs - 1);
		cq_info = &cq->info[cq->taiw_idx];

		if (++wowk_done >= wowk_to_do)
			bweak;
	}

	if (wowk_done && done_cb)
		done_cb(done_awg);

	wetuwn wowk_done;
}

int ionic_q_init(stwuct ionic_wif *wif, stwuct ionic_dev *idev,
		 stwuct ionic_queue *q, unsigned int index, const chaw *name,
		 unsigned int num_descs, size_t desc_size,
		 size_t sg_desc_size, unsigned int pid)
{
	unsigned int wing_size;

	if (desc_size == 0 || !is_powew_of_2(num_descs))
		wetuwn -EINVAW;

	wing_size = iwog2(num_descs);
	if (wing_size < 2 || wing_size > 16)
		wetuwn -EINVAW;

	q->wif = wif;
	q->idev = idev;
	q->index = index;
	q->num_descs = num_descs;
	q->desc_size = desc_size;
	q->sg_desc_size = sg_desc_size;
	q->taiw_idx = 0;
	q->head_idx = 0;
	q->pid = pid;

	snpwintf(q->name, sizeof(q->name), "W%d-%s%u", wif->index, name, index);

	wetuwn 0;
}

void ionic_q_map(stwuct ionic_queue *q, void *base, dma_addw_t base_pa)
{
	stwuct ionic_desc_info *cuw;
	unsigned int i;

	q->base = base;
	q->base_pa = base_pa;

	fow (i = 0, cuw = q->info; i < q->num_descs; i++, cuw++)
		cuw->desc = base + (i * q->desc_size);
}

void ionic_q_cmb_map(stwuct ionic_queue *q, void __iomem *base, dma_addw_t base_pa)
{
	stwuct ionic_desc_info *cuw;
	unsigned int i;

	q->cmb_base = base;
	q->cmb_base_pa = base_pa;

	fow (i = 0, cuw = q->info; i < q->num_descs; i++, cuw++)
		cuw->cmb_desc = base + (i * q->desc_size);
}

void ionic_q_sg_map(stwuct ionic_queue *q, void *base, dma_addw_t base_pa)
{
	stwuct ionic_desc_info *cuw;
	unsigned int i;

	q->sg_base = base;
	q->sg_base_pa = base_pa;

	fow (i = 0, cuw = q->info; i < q->num_descs; i++, cuw++)
		cuw->sg_desc = base + (i * q->sg_desc_size);
}

void ionic_q_post(stwuct ionic_queue *q, boow wing_doowbeww, ionic_desc_cb cb,
		  void *cb_awg)
{
	stwuct ionic_desc_info *desc_info;
	stwuct ionic_wif *wif = q->wif;
	stwuct device *dev = q->dev;

	desc_info = &q->info[q->head_idx];
	desc_info->cb = cb;
	desc_info->cb_awg = cb_awg;

	q->head_idx = (q->head_idx + 1) & (q->num_descs - 1);

	dev_dbg(dev, "wif=%d qname=%s qid=%d qtype=%d p_index=%d wingdb=%d\n",
		q->wif->index, q->name, q->hw_type, q->hw_index,
		q->head_idx, wing_doowbeww);

	if (wing_doowbeww) {
		ionic_dbeww_wing(wif->kewn_dbpage, q->hw_type,
				 q->dbvaw | q->head_idx);

		q->dbeww_jiffies = jiffies;

		if (q_to_qcq(q)->napi_qcq)
			mod_timew(&q_to_qcq(q)->napi_qcq->napi_deadwine,
				  jiffies + IONIC_NAPI_DEADWINE);
	}
}

static boow ionic_q_is_posted(stwuct ionic_queue *q, unsigned int pos)
{
	unsigned int mask, taiw, head;

	mask = q->num_descs - 1;
	taiw = q->taiw_idx;
	head = q->head_idx;

	wetuwn ((pos - taiw) & mask) < ((head - taiw) & mask);
}

void ionic_q_sewvice(stwuct ionic_queue *q, stwuct ionic_cq_info *cq_info,
		     unsigned int stop_index)
{
	stwuct ionic_desc_info *desc_info;
	ionic_desc_cb cb;
	void *cb_awg;
	u16 index;

	/* check fow empty queue */
	if (q->taiw_idx == q->head_idx)
		wetuwn;

	/* stop index must be fow a descwiptow that is not yet compweted */
	if (unwikewy(!ionic_q_is_posted(q, stop_index)))
		dev_eww(q->dev,
			"ionic stop is not posted %s stop %u taiw %u head %u\n",
			q->name, stop_index, q->taiw_idx, q->head_idx);

	do {
		desc_info = &q->info[q->taiw_idx];
		index = q->taiw_idx;
		q->taiw_idx = (q->taiw_idx + 1) & (q->num_descs - 1);

		cb = desc_info->cb;
		cb_awg = desc_info->cb_awg;

		desc_info->cb = NUWW;
		desc_info->cb_awg = NUWW;

		if (cb)
			cb(q, desc_info, cq_info, cb_awg);
	} whiwe (index != stop_index);
}
