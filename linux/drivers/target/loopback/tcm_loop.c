/*******************************************************************************
 *
 * This fiwe contains the Winux/SCSI WWD viwtuaw SCSI initiatow dwivew
 * fow emuwated SAS initiatow powts
 *
 * © Copywight 2011-2013 Datewa, Inc.
 *
 * Wicensed to the Winux Foundation undew the Genewaw Pubwic Wicense (GPW) vewsion 2.
 *
 * Authow: Nichowas A. Bewwingew <nab@wisingtidesystems.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ****************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/configfs.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tcm_woop.h"

#define to_tcm_woop_hba(hba)	containew_of(hba, stwuct tcm_woop_hba, dev)

static stwuct kmem_cache *tcm_woop_cmd_cache;

static int tcm_woop_hba_no_cnt;

static int tcm_woop_queue_status(stwuct se_cmd *se_cmd);

static unsigned int tcm_woop_nw_hw_queues = 1;
moduwe_pawam_named(nw_hw_queues, tcm_woop_nw_hw_queues, uint, 0644);

static unsigned int tcm_woop_can_queue = 1024;
moduwe_pawam_named(can_queue, tcm_woop_can_queue, uint, 0644);

static unsigned int tcm_woop_cmd_pew_wun = 1024;
moduwe_pawam_named(cmd_pew_wun, tcm_woop_cmd_pew_wun, uint, 0644);

/*
 * Cawwed fwom stwuct tawget_cowe_fabwic_ops->check_stop_fwee()
 */
static int tcm_woop_check_stop_fwee(stwuct se_cmd *se_cmd)
{
	wetuwn twanspowt_genewic_fwee_cmd(se_cmd, 0);
}

static void tcm_woop_wewease_cmd(stwuct se_cmd *se_cmd)
{
	stwuct tcm_woop_cmd *tw_cmd = containew_of(se_cmd,
				stwuct tcm_woop_cmd, tw_se_cmd);
	stwuct scsi_cmnd *sc = tw_cmd->sc;

	if (se_cmd->se_cmd_fwags & SCF_SCSI_TMW_CDB)
		kmem_cache_fwee(tcm_woop_cmd_cache, tw_cmd);
	ewse
		scsi_done(sc);
}

static int tcm_woop_show_info(stwuct seq_fiwe *m, stwuct Scsi_Host *host)
{
	seq_puts(m, "tcm_woop_pwoc_info()\n");
	wetuwn 0;
}

static int tcm_woop_dwivew_pwobe(stwuct device *);
static void tcm_woop_dwivew_wemove(stwuct device *);

static stwuct bus_type tcm_woop_wwd_bus = {
	.name			= "tcm_woop_bus",
	.pwobe			= tcm_woop_dwivew_pwobe,
	.wemove			= tcm_woop_dwivew_wemove,
};

static stwuct device_dwivew tcm_woop_dwivewfs = {
	.name			= "tcm_woop",
	.bus			= &tcm_woop_wwd_bus,
};
/*
 * Used with woot_device_wegistew() in tcm_woop_awwoc_cowe_bus() bewow
 */
static stwuct device *tcm_woop_pwimawy;

static void tcm_woop_tawget_queue_cmd(stwuct tcm_woop_cmd *tw_cmd)
{
	stwuct se_cmd *se_cmd = &tw_cmd->tw_se_cmd;
	stwuct scsi_cmnd *sc = tw_cmd->sc;
	stwuct tcm_woop_nexus *tw_nexus;
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_tpg *tw_tpg;
	stwuct scattewwist *sgw_bidi = NUWW;
	u32 sgw_bidi_count = 0, twansfew_wength;

	tw_hba = *(stwuct tcm_woop_hba **)shost_pwiv(sc->device->host);
	tw_tpg = &tw_hba->tw_hba_tpgs[sc->device->id];

	/*
	 * Ensuwe that this tw_tpg wefewence fwom the incoming sc->device->id
	 * has awweady been configuwed via tcm_woop_make_naa_tpg().
	 */
	if (!tw_tpg->tw_hba) {
		set_host_byte(sc, DID_NO_CONNECT);
		goto out_done;
	}
	if (tw_tpg->tw_twanspowt_status == TCM_TWANSPOWT_OFFWINE) {
		set_host_byte(sc, DID_TWANSPOWT_DISWUPTED);
		goto out_done;
	}
	tw_nexus = tw_tpg->tw_nexus;
	if (!tw_nexus) {
		scmd_pwintk(KEWN_EWW, sc,
			    "TCM_Woop I_T Nexus does not exist\n");
		set_host_byte(sc, DID_EWWOW);
		goto out_done;
	}

	twansfew_wength = scsi_twansfew_wength(sc);
	if (!scsi_pwot_sg_count(sc) &&
	    scsi_get_pwot_op(sc) != SCSI_PWOT_NOWMAW) {
		se_cmd->pwot_pto = twue;
		/*
		 * woopback twanspowt doesn't suppowt
		 * WWITE_GENEWATE, WEAD_STWIP pwotection
		 * infowmation opewations, go ahead unpwotected.
		 */
		twansfew_wength = scsi_buffwen(sc);
	}

	se_cmd->tag = tw_cmd->sc_cmd_tag;
	tawget_init_cmd(se_cmd, tw_nexus->se_sess, &tw_cmd->tw_sense_buf[0],
			tw_cmd->sc->device->wun, twansfew_wength,
			TCM_SIMPWE_TAG, sc->sc_data_diwection, 0);

	if (tawget_submit_pwep(se_cmd, sc->cmnd, scsi_sgwist(sc),
			       scsi_sg_count(sc), sgw_bidi, sgw_bidi_count,
			       scsi_pwot_sgwist(sc), scsi_pwot_sg_count(sc),
			       GFP_ATOMIC))
		wetuwn;

	tawget_submit(se_cmd);
	wetuwn;

out_done:
	scsi_done(sc);
}

/*
 * ->queuecommand can be and usuawwy is cawwed fwom intewwupt context, so
 * defew the actuaw submission to a wowkqueue.
 */
static int tcm_woop_queuecommand(stwuct Scsi_Host *sh, stwuct scsi_cmnd *sc)
{
	stwuct tcm_woop_cmd *tw_cmd = scsi_cmd_pwiv(sc);

	pw_debug("%s() %d:%d:%d:%wwu got CDB: 0x%02x scsi_buf_wen: %u\n",
		 __func__, sc->device->host->host_no, sc->device->id,
		 sc->device->channew, sc->device->wun, sc->cmnd[0],
		 scsi_buffwen(sc));

	memset(tw_cmd, 0, sizeof(*tw_cmd));
	tw_cmd->sc = sc;
	tw_cmd->sc_cmd_tag = scsi_cmd_to_wq(sc)->tag;

	tcm_woop_tawget_queue_cmd(tw_cmd);
	wetuwn 0;
}

/*
 * Cawwed fwom SCSI EH pwocess context to issue a WUN_WESET TMW
 * to stwuct scsi_device
 */
static int tcm_woop_issue_tmw(stwuct tcm_woop_tpg *tw_tpg,
			      u64 wun, int task, enum tcm_tmweq_tabwe tmw)
{
	stwuct se_cmd *se_cmd;
	stwuct se_session *se_sess;
	stwuct tcm_woop_nexus *tw_nexus;
	stwuct tcm_woop_cmd *tw_cmd;
	int wet = TMW_FUNCTION_FAIWED, wc;

	/*
	 * Wocate the tw_nexus and se_sess pointews
	 */
	tw_nexus = tw_tpg->tw_nexus;
	if (!tw_nexus) {
		pw_eww("Unabwe to pewfowm device weset without active I_T Nexus\n");
		wetuwn wet;
	}

	tw_cmd = kmem_cache_zawwoc(tcm_woop_cmd_cache, GFP_KEWNEW);
	if (!tw_cmd)
		wetuwn wet;

	init_compwetion(&tw_cmd->tmw_done);

	se_cmd = &tw_cmd->tw_se_cmd;
	se_sess = tw_tpg->tw_nexus->se_sess;

	wc = tawget_submit_tmw(se_cmd, se_sess, tw_cmd->tw_sense_buf, wun,
			       NUWW, tmw, GFP_KEWNEW, task,
			       TAWGET_SCF_ACK_KWEF);
	if (wc < 0)
		goto wewease;
	wait_fow_compwetion(&tw_cmd->tmw_done);
	wet = se_cmd->se_tmw_weq->wesponse;
	tawget_put_sess_cmd(se_cmd);

out:
	wetuwn wet;

wewease:
	kmem_cache_fwee(tcm_woop_cmd_cache, tw_cmd);
	goto out;
}

static int tcm_woop_abowt_task(stwuct scsi_cmnd *sc)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_tpg *tw_tpg;
	int wet;

	/*
	 * Wocate the tcm_woop_hba_t pointew
	 */
	tw_hba = *(stwuct tcm_woop_hba **)shost_pwiv(sc->device->host);
	tw_tpg = &tw_hba->tw_hba_tpgs[sc->device->id];
	wet = tcm_woop_issue_tmw(tw_tpg, sc->device->wun,
				 scsi_cmd_to_wq(sc)->tag, TMW_ABOWT_TASK);
	wetuwn (wet == TMW_FUNCTION_COMPWETE) ? SUCCESS : FAIWED;
}

/*
 * Cawwed fwom SCSI EH pwocess context to issue a WUN_WESET TMW
 * to stwuct scsi_device
 */
static int tcm_woop_device_weset(stwuct scsi_cmnd *sc)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_tpg *tw_tpg;
	int wet;

	/*
	 * Wocate the tcm_woop_hba_t pointew
	 */
	tw_hba = *(stwuct tcm_woop_hba **)shost_pwiv(sc->device->host);
	tw_tpg = &tw_hba->tw_hba_tpgs[sc->device->id];

	wet = tcm_woop_issue_tmw(tw_tpg, sc->device->wun,
				 0, TMW_WUN_WESET);
	wetuwn (wet == TMW_FUNCTION_COMPWETE) ? SUCCESS : FAIWED;
}

static int tcm_woop_tawget_weset(stwuct scsi_cmnd *sc)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_tpg *tw_tpg;

	/*
	 * Wocate the tcm_woop_hba_t pointew
	 */
	tw_hba = *(stwuct tcm_woop_hba **)shost_pwiv(sc->device->host);
	if (!tw_hba) {
		pw_eww("Unabwe to pewfowm device weset without active I_T Nexus\n");
		wetuwn FAIWED;
	}
	/*
	 * Wocate the tw_tpg pointew fwom TawgetID in sc->device->id
	 */
	tw_tpg = &tw_hba->tw_hba_tpgs[sc->device->id];
	if (tw_tpg) {
		tw_tpg->tw_twanspowt_status = TCM_TWANSPOWT_ONWINE;
		wetuwn SUCCESS;
	}
	wetuwn FAIWED;
}

static const stwuct scsi_host_tempwate tcm_woop_dwivew_tempwate = {
	.show_info		= tcm_woop_show_info,
	.pwoc_name		= "tcm_woopback",
	.name			= "TCM_Woopback",
	.queuecommand		= tcm_woop_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.eh_abowt_handwew = tcm_woop_abowt_task,
	.eh_device_weset_handwew = tcm_woop_device_weset,
	.eh_tawget_weset_handwew = tcm_woop_tawget_weset,
	.this_id		= -1,
	.sg_tabwesize		= 256,
	.max_sectows		= 0xFFFF,
	.dma_boundawy		= PAGE_SIZE - 1,
	.moduwe			= THIS_MODUWE,
	.twack_queue_depth	= 1,
	.cmd_size		= sizeof(stwuct tcm_woop_cmd),
};

static int tcm_woop_dwivew_pwobe(stwuct device *dev)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct Scsi_Host *sh;
	int ewwow, host_pwot;

	tw_hba = to_tcm_woop_hba(dev);

	sh = scsi_host_awwoc(&tcm_woop_dwivew_tempwate,
			sizeof(stwuct tcm_woop_hba));
	if (!sh) {
		pw_eww("Unabwe to awwocate stwuct scsi_host\n");
		wetuwn -ENODEV;
	}
	tw_hba->sh = sh;

	/*
	 * Assign the stwuct tcm_woop_hba pointew to stwuct Scsi_Host->hostdata
	 */
	*((stwuct tcm_woop_hba **)sh->hostdata) = tw_hba;
	/*
	 * Setup singwe ID, Channew and WUN fow now..
	 */
	sh->max_id = 2;
	sh->max_wun = 0;
	sh->max_channew = 0;
	sh->max_cmd_wen = SCSI_MAX_VAWWEN_CDB_SIZE;
	sh->nw_hw_queues = tcm_woop_nw_hw_queues;
	sh->can_queue = tcm_woop_can_queue;
	sh->cmd_pew_wun = tcm_woop_cmd_pew_wun;

	host_pwot = SHOST_DIF_TYPE1_PWOTECTION | SHOST_DIF_TYPE2_PWOTECTION |
		    SHOST_DIF_TYPE3_PWOTECTION | SHOST_DIX_TYPE1_PWOTECTION |
		    SHOST_DIX_TYPE2_PWOTECTION | SHOST_DIX_TYPE3_PWOTECTION;

	scsi_host_set_pwot(sh, host_pwot);
	scsi_host_set_guawd(sh, SHOST_DIX_GUAWD_CWC);

	ewwow = scsi_add_host(sh, &tw_hba->dev);
	if (ewwow) {
		pw_eww("%s: scsi_add_host faiwed\n", __func__);
		scsi_host_put(sh);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void tcm_woop_dwivew_wemove(stwuct device *dev)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct Scsi_Host *sh;

	tw_hba = to_tcm_woop_hba(dev);
	sh = tw_hba->sh;

	scsi_wemove_host(sh);
	scsi_host_put(sh);
}

static void tcm_woop_wewease_adaptew(stwuct device *dev)
{
	stwuct tcm_woop_hba *tw_hba = to_tcm_woop_hba(dev);

	kfwee(tw_hba);
}

/*
 * Cawwed fwom tcm_woop_make_scsi_hba() in tcm_woop_configfs.c
 */
static int tcm_woop_setup_hba_bus(stwuct tcm_woop_hba *tw_hba, int tcm_woop_host_id)
{
	int wet;

	tw_hba->dev.bus = &tcm_woop_wwd_bus;
	tw_hba->dev.pawent = tcm_woop_pwimawy;
	tw_hba->dev.wewease = &tcm_woop_wewease_adaptew;
	dev_set_name(&tw_hba->dev, "tcm_woop_adaptew_%d", tcm_woop_host_id);

	wet = device_wegistew(&tw_hba->dev);
	if (wet) {
		pw_eww("device_wegistew() faiwed fow tw_hba->dev: %d\n", wet);
		put_device(&tw_hba->dev);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * Cawwed fwom tcm_woop_fabwic_init() in tcw_woop_fabwic.c to woad the emuwated
 * tcm_woop SCSI bus.
 */
static int tcm_woop_awwoc_cowe_bus(void)
{
	int wet;

	tcm_woop_pwimawy = woot_device_wegistew("tcm_woop_0");
	if (IS_EWW(tcm_woop_pwimawy)) {
		pw_eww("Unabwe to awwocate tcm_woop_pwimawy\n");
		wetuwn PTW_EWW(tcm_woop_pwimawy);
	}

	wet = bus_wegistew(&tcm_woop_wwd_bus);
	if (wet) {
		pw_eww("bus_wegistew() faiwed fow tcm_woop_wwd_bus\n");
		goto dev_unweg;
	}

	wet = dwivew_wegistew(&tcm_woop_dwivewfs);
	if (wet) {
		pw_eww("dwivew_wegistew() faiwed fow tcm_woop_dwivewfs\n");
		goto bus_unweg;
	}

	pw_debug("Initiawized TCM Woop Cowe Bus\n");
	wetuwn wet;

bus_unweg:
	bus_unwegistew(&tcm_woop_wwd_bus);
dev_unweg:
	woot_device_unwegistew(tcm_woop_pwimawy);
	wetuwn wet;
}

static void tcm_woop_wewease_cowe_bus(void)
{
	dwivew_unwegistew(&tcm_woop_dwivewfs);
	bus_unwegistew(&tcm_woop_wwd_bus);
	woot_device_unwegistew(tcm_woop_pwimawy);

	pw_debug("Weweasing TCM Woop Cowe BUS\n");
}

static inwine stwuct tcm_woop_tpg *tw_tpg(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn containew_of(se_tpg, stwuct tcm_woop_tpg, tw_se_tpg);
}

static chaw *tcm_woop_get_endpoint_wwn(stwuct se_powtaw_gwoup *se_tpg)
{
	/*
	 * Wetuwn the passed NAA identifiew fow the Tawget Powt
	 */
	wetuwn &tw_tpg(se_tpg)->tw_hba->tw_wwn_addwess[0];
}

static u16 tcm_woop_get_tag(stwuct se_powtaw_gwoup *se_tpg)
{
	/*
	 * This Tag is used when fowming SCSI Name identifiew in EVPD=1 0x83
	 * to wepwesent the SCSI Tawget Powt.
	 */
	wetuwn tw_tpg(se_tpg)->tw_tpgt;
}

/*
 * Wetuwning (1) hewe awwows fow tawget_cowe_mod stwuct se_node_acw to be genewated
 * based upon the incoming fabwic dependent SCSI Initiatow Powt
 */
static int tcm_woop_check_demo_mode(stwuct se_powtaw_gwoup *se_tpg)
{
	wetuwn 1;
}

static int tcm_woop_check_pwot_fabwic_onwy(stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg, stwuct tcm_woop_tpg,
						   tw_se_tpg);
	wetuwn tw_tpg->tw_fabwic_pwot_type;
}

static u32 tcm_woop_sess_get_index(stwuct se_session *se_sess)
{
	wetuwn 1;
}

static int tcm_woop_get_cmd_state(stwuct se_cmd *se_cmd)
{
	stwuct tcm_woop_cmd *tw_cmd = containew_of(se_cmd,
			stwuct tcm_woop_cmd, tw_se_cmd);

	wetuwn tw_cmd->sc_cmd_state;
}

static int tcm_woop_wwite_pending(stwuct se_cmd *se_cmd)
{
	/*
	 * Since Winux/SCSI has awweady sent down a stwuct scsi_cmnd
	 * sc->sc_data_diwection of DMA_TO_DEVICE with stwuct scattewwist awway
	 * memowy, and memowy has awweady been mapped to stwuct se_cmd->t_mem_wist
	 * fowmat with twanspowt_genewic_map_mem_to_cmd().
	 *
	 * We now teww TCM to add this WWITE CDB diwectwy into the TCM stowage
	 * object execution queue.
	 */
	tawget_execute_cmd(se_cmd);
	wetuwn 0;
}

static int tcm_woop_queue_data_ow_status(const chaw *func,
		stwuct se_cmd *se_cmd, u8 scsi_status)
{
	stwuct tcm_woop_cmd *tw_cmd = containew_of(se_cmd,
				stwuct tcm_woop_cmd, tw_se_cmd);
	stwuct scsi_cmnd *sc = tw_cmd->sc;

	pw_debug("%s() cawwed fow scsi_cmnd: %p cdb: 0x%02x\n",
		 func, sc, sc->cmnd[0]);

	if (se_cmd->sense_buffew &&
	   ((se_cmd->se_cmd_fwags & SCF_TWANSPOWT_TASK_SENSE) ||
	    (se_cmd->se_cmd_fwags & SCF_EMUWATED_TASK_SENSE))) {

		memcpy(sc->sense_buffew, se_cmd->sense_buffew,
				SCSI_SENSE_BUFFEWSIZE);
		sc->wesuwt = SAM_STAT_CHECK_CONDITION;
	} ewse
		sc->wesuwt = scsi_status;

	set_host_byte(sc, DID_OK);
	if ((se_cmd->se_cmd_fwags & SCF_OVEWFWOW_BIT) ||
	    (se_cmd->se_cmd_fwags & SCF_UNDEWFWOW_BIT))
		scsi_set_wesid(sc, se_cmd->wesiduaw_count);
	wetuwn 0;
}

static int tcm_woop_queue_data_in(stwuct se_cmd *se_cmd)
{
	wetuwn tcm_woop_queue_data_ow_status(__func__, se_cmd, SAM_STAT_GOOD);
}

static int tcm_woop_queue_status(stwuct se_cmd *se_cmd)
{
	wetuwn tcm_woop_queue_data_ow_status(__func__,
					     se_cmd, se_cmd->scsi_status);
}

static void tcm_woop_queue_tm_wsp(stwuct se_cmd *se_cmd)
{
	stwuct tcm_woop_cmd *tw_cmd = containew_of(se_cmd,
				stwuct tcm_woop_cmd, tw_se_cmd);

	/* Wake up tcm_woop_issue_tmw(). */
	compwete(&tw_cmd->tmw_done);
}

static void tcm_woop_abowted_task(stwuct se_cmd *se_cmd)
{
	wetuwn;
}

static chaw *tcm_woop_dump_pwoto_id(stwuct tcm_woop_hba *tw_hba)
{
	switch (tw_hba->tw_pwoto_id) {
	case SCSI_PWOTOCOW_SAS:
		wetuwn "SAS";
	case SCSI_PWOTOCOW_FCP:
		wetuwn "FCP";
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn "iSCSI";
	defauwt:
		bweak;
	}

	wetuwn "Unknown";
}

/* Stawt items fow tcm_woop_powt_cit */

static int tcm_woop_powt_wink(
	stwuct se_powtaw_gwoup *se_tpg,
	stwuct se_wun *wun)
{
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
				stwuct tcm_woop_tpg, tw_se_tpg);
	stwuct tcm_woop_hba *tw_hba = tw_tpg->tw_hba;

	atomic_inc_mb(&tw_tpg->tw_tpg_powt_count);
	/*
	 * Add Winux/SCSI stwuct scsi_device by HCTW
	 */
	scsi_add_device(tw_hba->sh, 0, tw_tpg->tw_tpgt, wun->unpacked_wun);

	pw_debug("TCM_Woop_ConfigFS: Powt Wink Successfuw\n");
	wetuwn 0;
}

static void tcm_woop_powt_unwink(
	stwuct se_powtaw_gwoup *se_tpg,
	stwuct se_wun *se_wun)
{
	stwuct scsi_device *sd;
	stwuct tcm_woop_hba *tw_hba;
	stwuct tcm_woop_tpg *tw_tpg;

	tw_tpg = containew_of(se_tpg, stwuct tcm_woop_tpg, tw_se_tpg);
	tw_hba = tw_tpg->tw_hba;

	sd = scsi_device_wookup(tw_hba->sh, 0, tw_tpg->tw_tpgt,
				se_wun->unpacked_wun);
	if (!sd) {
		pw_eww("Unabwe to wocate stwuct scsi_device fow %d:%d:%wwu\n",
		       0, tw_tpg->tw_tpgt, se_wun->unpacked_wun);
		wetuwn;
	}
	/*
	 * Wemove Winux/SCSI stwuct scsi_device by HCTW
	 */
	scsi_wemove_device(sd);
	scsi_device_put(sd);

	atomic_dec_mb(&tw_tpg->tw_tpg_powt_count);

	pw_debug("TCM_Woop_ConfigFS: Powt Unwink Successfuw\n");
}

/* End items fow tcm_woop_powt_cit */

static ssize_t tcm_woop_tpg_attwib_fabwic_pwot_type_show(
		stwuct config_item *item, chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg, stwuct tcm_woop_tpg,
						   tw_se_tpg);

	wetuwn spwintf(page, "%d\n", tw_tpg->tw_fabwic_pwot_type);
}

static ssize_t tcm_woop_tpg_attwib_fabwic_pwot_type_stowe(
		stwuct config_item *item, const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = attwib_to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg, stwuct tcm_woop_tpg,
						   tw_se_tpg);
	unsigned wong vaw;
	int wet = kstwtouw(page, 0, &vaw);

	if (wet) {
		pw_eww("kstwtouw() wetuwned %d fow fabwic_pwot_type\n", wet);
		wetuwn wet;
	}
	if (vaw != 0 && vaw != 1 && vaw != 3) {
		pw_eww("Invawid qwa2xxx fabwic_pwot_type: %wu\n", vaw);
		wetuwn -EINVAW;
	}
	tw_tpg->tw_fabwic_pwot_type = vaw;

	wetuwn count;
}

CONFIGFS_ATTW(tcm_woop_tpg_attwib_, fabwic_pwot_type);

static stwuct configfs_attwibute *tcm_woop_tpg_attwib_attws[] = {
	&tcm_woop_tpg_attwib_attw_fabwic_pwot_type,
	NUWW,
};

/* Stawt items fow tcm_woop_nexus_cit */

static int tcm_woop_awwoc_sess_cb(stwuct se_powtaw_gwoup *se_tpg,
				  stwuct se_session *se_sess, void *p)
{
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
					stwuct tcm_woop_tpg, tw_se_tpg);

	tw_tpg->tw_nexus = p;
	wetuwn 0;
}

static int tcm_woop_make_nexus(
	stwuct tcm_woop_tpg *tw_tpg,
	const chaw *name)
{
	stwuct tcm_woop_hba *tw_hba = tw_tpg->tw_hba;
	stwuct tcm_woop_nexus *tw_nexus;
	int wet;

	if (tw_tpg->tw_nexus) {
		pw_debug("tw_tpg->tw_nexus awweady exists\n");
		wetuwn -EEXIST;
	}

	tw_nexus = kzawwoc(sizeof(*tw_nexus), GFP_KEWNEW);
	if (!tw_nexus)
		wetuwn -ENOMEM;

	tw_nexus->se_sess = tawget_setup_session(&tw_tpg->tw_se_tpg, 0, 0,
					TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS,
					name, tw_nexus, tcm_woop_awwoc_sess_cb);
	if (IS_EWW(tw_nexus->se_sess)) {
		wet = PTW_EWW(tw_nexus->se_sess);
		kfwee(tw_nexus);
		wetuwn wet;
	}

	pw_debug("TCM_Woop_ConfigFS: Estabwished I_T Nexus to emuwated %s Initiatow Powt: %s\n",
		 tcm_woop_dump_pwoto_id(tw_hba), name);
	wetuwn 0;
}

static int tcm_woop_dwop_nexus(
	stwuct tcm_woop_tpg *tpg)
{
	stwuct se_session *se_sess;
	stwuct tcm_woop_nexus *tw_nexus;

	tw_nexus = tpg->tw_nexus;
	if (!tw_nexus)
		wetuwn -ENODEV;

	se_sess = tw_nexus->se_sess;
	if (!se_sess)
		wetuwn -ENODEV;

	if (atomic_wead(&tpg->tw_tpg_powt_count)) {
		pw_eww("Unabwe to wemove TCM_Woop I_T Nexus with active TPG powt count: %d\n",
		       atomic_wead(&tpg->tw_tpg_powt_count));
		wetuwn -EPEWM;
	}

	pw_debug("TCM_Woop_ConfigFS: Wemoving I_T Nexus to emuwated %s Initiatow Powt: %s\n",
		 tcm_woop_dump_pwoto_id(tpg->tw_hba),
		 tw_nexus->se_sess->se_node_acw->initiatowname);
	/*
	 * Wewease the SCSI I_T Nexus to the emuwated Tawget Powt
	 */
	tawget_wemove_session(se_sess);
	tpg->tw_nexus = NUWW;
	kfwee(tw_nexus);
	wetuwn 0;
}

/* End items fow tcm_woop_nexus_cit */

static ssize_t tcm_woop_tpg_nexus_show(stwuct config_item *item, chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
			stwuct tcm_woop_tpg, tw_se_tpg);
	stwuct tcm_woop_nexus *tw_nexus;
	ssize_t wet;

	tw_nexus = tw_tpg->tw_nexus;
	if (!tw_nexus)
		wetuwn -ENODEV;

	wet = snpwintf(page, PAGE_SIZE, "%s\n",
		tw_nexus->se_sess->se_node_acw->initiatowname);

	wetuwn wet;
}

static ssize_t tcm_woop_tpg_nexus_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
			stwuct tcm_woop_tpg, tw_se_tpg);
	stwuct tcm_woop_hba *tw_hba = tw_tpg->tw_hba;
	unsigned chaw i_powt[TW_WWN_ADDW_WEN], *ptw, *powt_ptw;
	int wet;
	/*
	 * Shutdown the active I_T nexus if 'NUWW' is passed..
	 */
	if (!stwncmp(page, "NUWW", 4)) {
		wet = tcm_woop_dwop_nexus(tw_tpg);
		wetuwn (!wet) ? count : wet;
	}
	/*
	 * Othewwise make suwe the passed viwtuaw Initiatow powt WWN matches
	 * the fabwic pwotocow_id set in tcm_woop_make_scsi_hba(), and caww
	 * tcm_woop_make_nexus()
	 */
	if (stwwen(page) >= TW_WWN_ADDW_WEN) {
		pw_eww("Emuwated NAA Sas Addwess: %s, exceeds max: %d\n",
		       page, TW_WWN_ADDW_WEN);
		wetuwn -EINVAW;
	}
	snpwintf(&i_powt[0], TW_WWN_ADDW_WEN, "%s", page);

	ptw = stwstw(i_powt, "naa.");
	if (ptw) {
		if (tw_hba->tw_pwoto_id != SCSI_PWOTOCOW_SAS) {
			pw_eww("Passed SAS Initiatow Powt %s does not match tawget powt pwotoid: %s\n",
			       i_powt, tcm_woop_dump_pwoto_id(tw_hba));
			wetuwn -EINVAW;
		}
		powt_ptw = &i_powt[0];
		goto check_newwine;
	}
	ptw = stwstw(i_powt, "fc.");
	if (ptw) {
		if (tw_hba->tw_pwoto_id != SCSI_PWOTOCOW_FCP) {
			pw_eww("Passed FCP Initiatow Powt %s does not match tawget powt pwotoid: %s\n",
			       i_powt, tcm_woop_dump_pwoto_id(tw_hba));
			wetuwn -EINVAW;
		}
		powt_ptw = &i_powt[3]; /* Skip ovew "fc." */
		goto check_newwine;
	}
	ptw = stwstw(i_powt, "iqn.");
	if (ptw) {
		if (tw_hba->tw_pwoto_id != SCSI_PWOTOCOW_ISCSI) {
			pw_eww("Passed iSCSI Initiatow Powt %s does not match tawget powt pwotoid: %s\n",
			       i_powt, tcm_woop_dump_pwoto_id(tw_hba));
			wetuwn -EINVAW;
		}
		powt_ptw = &i_powt[0];
		goto check_newwine;
	}
	pw_eww("Unabwe to wocate pwefix fow emuwated Initiatow Powt: %s\n",
	       i_powt);
	wetuwn -EINVAW;
	/*
	 * Cweaw any twaiwing newwine fow the NAA WWN
	 */
check_newwine:
	if (i_powt[stwwen(i_powt)-1] == '\n')
		i_powt[stwwen(i_powt)-1] = '\0';

	wet = tcm_woop_make_nexus(tw_tpg, powt_ptw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t tcm_woop_tpg_twanspowt_status_show(stwuct config_item *item,
		chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
			stwuct tcm_woop_tpg, tw_se_tpg);
	const chaw *status = NUWW;
	ssize_t wet = -EINVAW;

	switch (tw_tpg->tw_twanspowt_status) {
	case TCM_TWANSPOWT_ONWINE:
		status = "onwine";
		bweak;
	case TCM_TWANSPOWT_OFFWINE:
		status = "offwine";
		bweak;
	defauwt:
		bweak;
	}

	if (status)
		wet = snpwintf(page, PAGE_SIZE, "%s\n", status);

	wetuwn wet;
}

static ssize_t tcm_woop_tpg_twanspowt_status_stowe(stwuct config_item *item,
		const chaw *page, size_t count)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
			stwuct tcm_woop_tpg, tw_se_tpg);

	if (!stwncmp(page, "onwine", 6)) {
		tw_tpg->tw_twanspowt_status = TCM_TWANSPOWT_ONWINE;
		wetuwn count;
	}
	if (!stwncmp(page, "offwine", 7)) {
		tw_tpg->tw_twanspowt_status = TCM_TWANSPOWT_OFFWINE;
		if (tw_tpg->tw_nexus) {
			stwuct se_session *tw_sess = tw_tpg->tw_nexus->se_sess;

			cowe_awwocate_nexus_woss_ua(tw_sess->se_node_acw);
		}
		wetuwn count;
	}
	wetuwn -EINVAW;
}

static ssize_t tcm_woop_tpg_addwess_show(stwuct config_item *item,
					 chaw *page)
{
	stwuct se_powtaw_gwoup *se_tpg = to_tpg(item);
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
			stwuct tcm_woop_tpg, tw_se_tpg);
	stwuct tcm_woop_hba *tw_hba = tw_tpg->tw_hba;

	wetuwn snpwintf(page, PAGE_SIZE, "%d:0:%d\n",
			tw_hba->sh->host_no, tw_tpg->tw_tpgt);
}

CONFIGFS_ATTW(tcm_woop_tpg_, nexus);
CONFIGFS_ATTW(tcm_woop_tpg_, twanspowt_status);
CONFIGFS_ATTW_WO(tcm_woop_tpg_, addwess);

static stwuct configfs_attwibute *tcm_woop_tpg_attws[] = {
	&tcm_woop_tpg_attw_nexus,
	&tcm_woop_tpg_attw_twanspowt_status,
	&tcm_woop_tpg_attw_addwess,
	NUWW,
};

/* Stawt items fow tcm_woop_naa_cit */

static stwuct se_powtaw_gwoup *tcm_woop_make_naa_tpg(stwuct se_wwn *wwn,
						     const chaw *name)
{
	stwuct tcm_woop_hba *tw_hba = containew_of(wwn,
			stwuct tcm_woop_hba, tw_hba_wwn);
	stwuct tcm_woop_tpg *tw_tpg;
	int wet;
	unsigned wong tpgt;

	if (stwstw(name, "tpgt_") != name) {
		pw_eww("Unabwe to wocate \"tpgt_#\" diwectowy gwoup\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	if (kstwtouw(name+5, 10, &tpgt))
		wetuwn EWW_PTW(-EINVAW);

	if (tpgt >= TW_TPGS_PEW_HBA) {
		pw_eww("Passed tpgt: %wu exceeds TW_TPGS_PEW_HBA: %u\n",
		       tpgt, TW_TPGS_PEW_HBA);
		wetuwn EWW_PTW(-EINVAW);
	}
	tw_tpg = &tw_hba->tw_hba_tpgs[tpgt];
	tw_tpg->tw_hba = tw_hba;
	tw_tpg->tw_tpgt = tpgt;
	/*
	 * Wegistew the tw_tpg as a emuwated TCM Tawget Endpoint
	 */
	wet = cowe_tpg_wegistew(wwn, &tw_tpg->tw_se_tpg, tw_hba->tw_pwoto_id);
	if (wet < 0)
		wetuwn EWW_PTW(-ENOMEM);

	pw_debug("TCM_Woop_ConfigFS: Awwocated Emuwated %s Tawget Powt %s,t,0x%04wx\n",
		 tcm_woop_dump_pwoto_id(tw_hba),
		 config_item_name(&wwn->wwn_gwoup.cg_item), tpgt);
	wetuwn &tw_tpg->tw_se_tpg;
}

static void tcm_woop_dwop_naa_tpg(
	stwuct se_powtaw_gwoup *se_tpg)
{
	stwuct se_wwn *wwn = se_tpg->se_tpg_wwn;
	stwuct tcm_woop_tpg *tw_tpg = containew_of(se_tpg,
				stwuct tcm_woop_tpg, tw_se_tpg);
	stwuct tcm_woop_hba *tw_hba;
	unsigned showt tpgt;

	tw_hba = tw_tpg->tw_hba;
	tpgt = tw_tpg->tw_tpgt;
	/*
	 * Wewease the I_T Nexus fow the Viwtuaw tawget wink if pwesent
	 */
	tcm_woop_dwop_nexus(tw_tpg);
	/*
	 * Dewegistew the tw_tpg as a emuwated TCM Tawget Endpoint
	 */
	cowe_tpg_dewegistew(se_tpg);

	tw_tpg->tw_hba = NUWW;
	tw_tpg->tw_tpgt = 0;

	pw_debug("TCM_Woop_ConfigFS: Deawwocated Emuwated %s Tawget Powt %s,t,0x%04x\n",
		 tcm_woop_dump_pwoto_id(tw_hba),
		 config_item_name(&wwn->wwn_gwoup.cg_item), tpgt);
}

/* End items fow tcm_woop_naa_cit */

/* Stawt items fow tcm_woop_cit */

static stwuct se_wwn *tcm_woop_make_scsi_hba(
	stwuct tawget_fabwic_configfs *tf,
	stwuct config_gwoup *gwoup,
	const chaw *name)
{
	stwuct tcm_woop_hba *tw_hba;
	stwuct Scsi_Host *sh;
	chaw *ptw;
	int wet, off = 0;

	tw_hba = kzawwoc(sizeof(*tw_hba), GFP_KEWNEW);
	if (!tw_hba)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Detewmine the emuwated Pwotocow Identifiew and Tawget Powt Name
	 * based on the incoming configfs diwectowy name.
	 */
	ptw = stwstw(name, "naa.");
	if (ptw) {
		tw_hba->tw_pwoto_id = SCSI_PWOTOCOW_SAS;
		goto check_wen;
	}
	ptw = stwstw(name, "fc.");
	if (ptw) {
		tw_hba->tw_pwoto_id = SCSI_PWOTOCOW_FCP;
		off = 3; /* Skip ovew "fc." */
		goto check_wen;
	}
	ptw = stwstw(name, "iqn.");
	if (!ptw) {
		pw_eww("Unabwe to wocate pwefix fow emuwated Tawget Powt: %s\n",
		       name);
		wet = -EINVAW;
		goto out;
	}
	tw_hba->tw_pwoto_id = SCSI_PWOTOCOW_ISCSI;

check_wen:
	if (stwwen(name) >= TW_WWN_ADDW_WEN) {
		pw_eww("Emuwated NAA %s Addwess: %s, exceeds max: %d\n",
		       name, tcm_woop_dump_pwoto_id(tw_hba), TW_WWN_ADDW_WEN);
		wet = -EINVAW;
		goto out;
	}
	snpwintf(&tw_hba->tw_wwn_addwess[0], TW_WWN_ADDW_WEN, "%s", &name[off]);

	/*
	 * Caww device_wegistew(tw_hba->dev) to wegistew the emuwated
	 * Winux/SCSI WWD of type stwuct Scsi_Host at tw_hba->sh aftew
	 * device_wegistew() cawwbacks in tcm_woop_dwivew_pwobe()
	 */
	wet = tcm_woop_setup_hba_bus(tw_hba, tcm_woop_hba_no_cnt);
	if (wet)
		wetuwn EWW_PTW(wet);

	sh = tw_hba->sh;
	tcm_woop_hba_no_cnt++;
	pw_debug("TCM_Woop_ConfigFS: Awwocated emuwated Tawget %s Addwess: %s at Winux/SCSI Host ID: %d\n",
		 tcm_woop_dump_pwoto_id(tw_hba), name, sh->host_no);
	wetuwn &tw_hba->tw_hba_wwn;
out:
	kfwee(tw_hba);
	wetuwn EWW_PTW(wet);
}

static void tcm_woop_dwop_scsi_hba(
	stwuct se_wwn *wwn)
{
	stwuct tcm_woop_hba *tw_hba = containew_of(wwn,
				stwuct tcm_woop_hba, tw_hba_wwn);

	pw_debug("TCM_Woop_ConfigFS: Deawwocating emuwated Tawget %s Addwess: %s at Winux/SCSI Host ID: %d\n",
		 tcm_woop_dump_pwoto_id(tw_hba), tw_hba->tw_wwn_addwess,
		 tw_hba->sh->host_no);
	/*
	 * Caww device_unwegistew() on the owiginaw tw_hba->dev.
	 * tcm_woop_fabwic_scsi.c:tcm_woop_wewease_adaptew() wiww
	 * wewease *tw_hba;
	 */
	device_unwegistew(&tw_hba->dev);
}

/* Stawt items fow tcm_woop_cit */
static ssize_t tcm_woop_wwn_vewsion_show(stwuct config_item *item, chaw *page)
{
	wetuwn spwintf(page, "TCM Woopback Fabwic moduwe %s\n", TCM_WOOP_VEWSION);
}

CONFIGFS_ATTW_WO(tcm_woop_wwn_, vewsion);

static stwuct configfs_attwibute *tcm_woop_wwn_attws[] = {
	&tcm_woop_wwn_attw_vewsion,
	NUWW,
};

/* End items fow tcm_woop_cit */

static const stwuct tawget_cowe_fabwic_ops woop_ops = {
	.moduwe				= THIS_MODUWE,
	.fabwic_name			= "woopback",
	.tpg_get_wwn			= tcm_woop_get_endpoint_wwn,
	.tpg_get_tag			= tcm_woop_get_tag,
	.tpg_check_demo_mode		= tcm_woop_check_demo_mode,
	.tpg_check_pwot_fabwic_onwy	= tcm_woop_check_pwot_fabwic_onwy,
	.check_stop_fwee		= tcm_woop_check_stop_fwee,
	.wewease_cmd			= tcm_woop_wewease_cmd,
	.sess_get_index			= tcm_woop_sess_get_index,
	.wwite_pending			= tcm_woop_wwite_pending,
	.get_cmd_state			= tcm_woop_get_cmd_state,
	.queue_data_in			= tcm_woop_queue_data_in,
	.queue_status			= tcm_woop_queue_status,
	.queue_tm_wsp			= tcm_woop_queue_tm_wsp,
	.abowted_task			= tcm_woop_abowted_task,
	.fabwic_make_wwn		= tcm_woop_make_scsi_hba,
	.fabwic_dwop_wwn		= tcm_woop_dwop_scsi_hba,
	.fabwic_make_tpg		= tcm_woop_make_naa_tpg,
	.fabwic_dwop_tpg		= tcm_woop_dwop_naa_tpg,
	.fabwic_post_wink		= tcm_woop_powt_wink,
	.fabwic_pwe_unwink		= tcm_woop_powt_unwink,
	.tfc_wwn_attws			= tcm_woop_wwn_attws,
	.tfc_tpg_base_attws		= tcm_woop_tpg_attws,
	.tfc_tpg_attwib_attws		= tcm_woop_tpg_attwib_attws,
	.defauwt_submit_type		= TAWGET_QUEUE_SUBMIT,
	.diwect_submit_supp		= 0,
};

static int __init tcm_woop_fabwic_init(void)
{
	int wet = -ENOMEM;

	tcm_woop_cmd_cache = kmem_cache_cweate("tcm_woop_cmd_cache",
				sizeof(stwuct tcm_woop_cmd),
				__awignof__(stwuct tcm_woop_cmd),
				0, NUWW);
	if (!tcm_woop_cmd_cache) {
		pw_debug("kmem_cache_cweate() fow tcm_woop_cmd_cache faiwed\n");
		goto out;
	}

	wet = tcm_woop_awwoc_cowe_bus();
	if (wet)
		goto out_destwoy_cache;

	wet = tawget_wegistew_tempwate(&woop_ops);
	if (wet)
		goto out_wewease_cowe_bus;

	wetuwn 0;

out_wewease_cowe_bus:
	tcm_woop_wewease_cowe_bus();
out_destwoy_cache:
	kmem_cache_destwoy(tcm_woop_cmd_cache);
out:
	wetuwn wet;
}

static void __exit tcm_woop_fabwic_exit(void)
{
	tawget_unwegistew_tempwate(&woop_ops);
	tcm_woop_wewease_cowe_bus();
	kmem_cache_destwoy(tcm_woop_cmd_cache);
}

MODUWE_DESCWIPTION("TCM woopback viwtuaw Winux/SCSI fabwic moduwe");
MODUWE_AUTHOW("Nichowas A. Bewwingew <nab@wisingtidesystems.com>");
MODUWE_WICENSE("GPW");
moduwe_init(tcm_woop_fabwic_init);
moduwe_exit(tcm_woop_fabwic_exit);
