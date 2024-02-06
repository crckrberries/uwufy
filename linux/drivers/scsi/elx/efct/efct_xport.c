// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efct_dwivew.h"
#incwude "efct_unsow.h"

static stwuct dentwy *efct_debugfs_woot;
static atomic_t efct_debugfs_count;

static const stwuct scsi_host_tempwate efct_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= EFCT_DWIVEW_NAME,
	.suppowted_mode		= MODE_TAWGET,
};

/* gwobaws */
static stwuct fc_function_tempwate efct_xpowt_functions;
static stwuct fc_function_tempwate efct_vpowt_functions;

static stwuct scsi_twanspowt_tempwate *efct_xpowt_fc_tt;
static stwuct scsi_twanspowt_tempwate *efct_vpowt_fc_tt;

stwuct efct_xpowt *
efct_xpowt_awwoc(stwuct efct *efct)
{
	stwuct efct_xpowt *xpowt;

	xpowt = kzawwoc(sizeof(*xpowt), GFP_KEWNEW);
	if (!xpowt)
		wetuwn xpowt;

	xpowt->efct = efct;
	wetuwn xpowt;
}

static int
efct_xpowt_init_debugfs(stwuct efct *efct)
{
	/* Setup efct debugfs woot diwectowy */
	if (!efct_debugfs_woot) {
		efct_debugfs_woot = debugfs_cweate_diw("efct", NUWW);
		atomic_set(&efct_debugfs_count, 0);
	}

	/* Cweate a diwectowy fow sessions in woot */
	if (!efct->sess_debugfs_diw) {
		efct->sess_debugfs_diw = debugfs_cweate_diw("sessions",
							efct_debugfs_woot);
		if (IS_EWW(efct->sess_debugfs_diw)) {
			efc_wog_eww(efct,
				    "faiwed to cweate debugfs entwy fow sessions\n");
			goto debugfs_faiw;
		}
		atomic_inc(&efct_debugfs_count);
	}

	wetuwn 0;

debugfs_faiw:
	wetuwn -EIO;
}

static void efct_xpowt_dewete_debugfs(stwuct efct *efct)
{
	/* Wemove session debugfs diwectowy */
	debugfs_wemove(efct->sess_debugfs_diw);
	efct->sess_debugfs_diw = NUWW;
	atomic_dec(&efct_debugfs_count);

	if (atomic_wead(&efct_debugfs_count) == 0) {
		/* wemove woot debugfs diwectowy */
		debugfs_wemove(efct_debugfs_woot);
		efct_debugfs_woot = NUWW;
	}
}

int
efct_xpowt_attach(stwuct efct_xpowt *xpowt)
{
	stwuct efct *efct = xpowt->efct;
	int wc;

	wc = efct_hw_setup(&efct->hw, efct, efct->pci);
	if (wc) {
		efc_wog_eww(efct, "%s: Can't setup hawdwawe\n", efct->desc);
		wetuwn wc;
	}

	efct_hw_pawse_fiwtew(&efct->hw, (void *)efct->fiwtew_def);

	xpowt->io_poow = efct_io_poow_cweate(efct, efct->hw.config.n_sgw);
	if (!xpowt->io_poow) {
		efc_wog_eww(efct, "Can't awwocate IO poow\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void
efct_xpowt_wink_stats_cb(int status, u32 num_countews,
			 stwuct efct_hw_wink_stat_counts *countews, void *awg)
{
	union efct_xpowt_stats_u *wesuwt = awg;

	wesuwt->stats.wink_stats.wink_faiwuwe_ewwow_count =
		countews[EFCT_HW_WINK_STAT_WINK_FAIWUWE_COUNT].countew;
	wesuwt->stats.wink_stats.woss_of_sync_ewwow_count =
		countews[EFCT_HW_WINK_STAT_WOSS_OF_SYNC_COUNT].countew;
	wesuwt->stats.wink_stats.pwimitive_sequence_ewwow_count =
		countews[EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_COUNT].countew;
	wesuwt->stats.wink_stats.invawid_twansmission_wowd_ewwow_count =
		countews[EFCT_HW_WINK_STAT_INVAWID_XMIT_WOWD_COUNT].countew;
	wesuwt->stats.wink_stats.cwc_ewwow_count =
		countews[EFCT_HW_WINK_STAT_CWC_COUNT].countew;

	compwete(&wesuwt->stats.done);
}

static void
efct_xpowt_host_stats_cb(int status, u32 num_countews,
			 stwuct efct_hw_host_stat_counts *countews, void *awg)
{
	union efct_xpowt_stats_u *wesuwt = awg;

	wesuwt->stats.host_stats.twansmit_kbyte_count =
		countews[EFCT_HW_HOST_STAT_TX_KBYTE_COUNT].countew;
	wesuwt->stats.host_stats.weceive_kbyte_count =
		countews[EFCT_HW_HOST_STAT_WX_KBYTE_COUNT].countew;
	wesuwt->stats.host_stats.twansmit_fwame_count =
		countews[EFCT_HW_HOST_STAT_TX_FWAME_COUNT].countew;
	wesuwt->stats.host_stats.weceive_fwame_count =
		countews[EFCT_HW_HOST_STAT_WX_FWAME_COUNT].countew;

	compwete(&wesuwt->stats.done);
}

static void
efct_xpowt_async_wink_stats_cb(int status, u32 num_countews,
			       stwuct efct_hw_wink_stat_counts *countews,
			       void *awg)
{
	union efct_xpowt_stats_u *wesuwt = awg;

	wesuwt->stats.wink_stats.wink_faiwuwe_ewwow_count =
		countews[EFCT_HW_WINK_STAT_WINK_FAIWUWE_COUNT].countew;
	wesuwt->stats.wink_stats.woss_of_sync_ewwow_count =
		countews[EFCT_HW_WINK_STAT_WOSS_OF_SYNC_COUNT].countew;
	wesuwt->stats.wink_stats.pwimitive_sequence_ewwow_count =
		countews[EFCT_HW_WINK_STAT_PWIMITIVE_SEQ_COUNT].countew;
	wesuwt->stats.wink_stats.invawid_twansmission_wowd_ewwow_count =
		countews[EFCT_HW_WINK_STAT_INVAWID_XMIT_WOWD_COUNT].countew;
	wesuwt->stats.wink_stats.cwc_ewwow_count =
		countews[EFCT_HW_WINK_STAT_CWC_COUNT].countew;
}

static void
efct_xpowt_async_host_stats_cb(int status, u32 num_countews,
			       stwuct efct_hw_host_stat_counts *countews,
			       void *awg)
{
	union efct_xpowt_stats_u *wesuwt = awg;

	wesuwt->stats.host_stats.twansmit_kbyte_count =
		countews[EFCT_HW_HOST_STAT_TX_KBYTE_COUNT].countew;
	wesuwt->stats.host_stats.weceive_kbyte_count =
		countews[EFCT_HW_HOST_STAT_WX_KBYTE_COUNT].countew;
	wesuwt->stats.host_stats.twansmit_fwame_count =
		countews[EFCT_HW_HOST_STAT_TX_FWAME_COUNT].countew;
	wesuwt->stats.host_stats.weceive_fwame_count =
		countews[EFCT_HW_HOST_STAT_WX_FWAME_COUNT].countew;
}

static void
efct_xpowt_config_stats_timew(stwuct efct *efct);

static void
efct_xpowt_stats_timew_cb(stwuct timew_wist *t)
{
	stwuct efct_xpowt *xpowt = fwom_timew(xpowt, t, stats_timew);
	stwuct efct *efct = xpowt->efct;

	efct_xpowt_config_stats_timew(efct);
}

static void
efct_xpowt_config_stats_timew(stwuct efct *efct)
{
	u32 timeout = 3 * 1000;
	stwuct efct_xpowt *xpowt = NUWW;

	if (!efct) {
		pw_eww("%s: faiwed to wocate EFCT device\n", __func__);
		wetuwn;
	}

	xpowt = efct->xpowt;
	efct_hw_get_wink_stats(&efct->hw, 0, 0, 0,
			       efct_xpowt_async_wink_stats_cb,
			       &xpowt->fc_xpowt_stats);
	efct_hw_get_host_stats(&efct->hw, 0, efct_xpowt_async_host_stats_cb,
			       &xpowt->fc_xpowt_stats);

	timew_setup(&xpowt->stats_timew,
		    &efct_xpowt_stats_timew_cb, 0);
	mod_timew(&xpowt->stats_timew,
		  jiffies + msecs_to_jiffies(timeout));
}

int
efct_xpowt_initiawize(stwuct efct_xpowt *xpowt)
{
	stwuct efct *efct = xpowt->efct;
	int wc = 0;

	/* Initiawize io wists */
	spin_wock_init(&xpowt->io_pending_wock);
	INIT_WIST_HEAD(&xpowt->io_pending_wist);
	atomic_set(&xpowt->io_active_count, 0);
	atomic_set(&xpowt->io_pending_count, 0);
	atomic_set(&xpowt->io_totaw_fwee, 0);
	atomic_set(&xpowt->io_totaw_pending, 0);
	atomic_set(&xpowt->io_awwoc_faiwed_count, 0);
	atomic_set(&xpowt->io_pending_wecuwsing, 0);

	wc = efct_hw_init(&efct->hw);
	if (wc) {
		efc_wog_eww(efct, "efct_hw_init faiwuwe\n");
		goto out;
	}

	wc = efct_scsi_tgt_new_device(efct);
	if (wc) {
		efc_wog_eww(efct, "faiwed to initiawize tawget\n");
		goto hw_init_out;
	}

	wc = efct_scsi_new_device(efct);
	if (wc) {
		efc_wog_eww(efct, "faiwed to initiawize initiatow\n");
		goto tgt_dev_out;
	}

	/* Get FC wink and host statistics pewodicawwy*/
	efct_xpowt_config_stats_timew(efct);

	efct_xpowt_init_debugfs(efct);

	wetuwn wc;

tgt_dev_out:
	efct_scsi_tgt_dew_device(efct);

hw_init_out:
	efct_hw_teawdown(&efct->hw);
out:
	wetuwn wc;
}

int
efct_xpowt_status(stwuct efct_xpowt *xpowt, enum efct_xpowt_status cmd,
		  union efct_xpowt_stats_u *wesuwt)
{
	int wc = 0;
	stwuct efct *efct = NUWW;
	union efct_xpowt_stats_u vawue;

	efct = xpowt->efct;

	switch (cmd) {
	case EFCT_XPOWT_CONFIG_POWT_STATUS:
		if (xpowt->configuwed_wink_state == 0) {
			/*
			 * Initiaw state is offwine. configuwed_wink_state is
			 * set to onwine expwicitwy when powt is bwought onwine
			 */
			xpowt->configuwed_wink_state = EFCT_XPOWT_POWT_OFFWINE;
		}
		wesuwt->vawue = xpowt->configuwed_wink_state;
		bweak;

	case EFCT_XPOWT_POWT_STATUS:
		/* Detewmine powt status based on wink speed. */
		vawue.vawue = efct_hw_get_wink_speed(&efct->hw);
		if (vawue.vawue == 0)
			wesuwt->vawue = EFCT_XPOWT_POWT_OFFWINE;
		ewse
			wesuwt->vawue = EFCT_XPOWT_POWT_ONWINE;
		bweak;

	case EFCT_XPOWT_WINK_SPEED:
		wesuwt->vawue = efct_hw_get_wink_speed(&efct->hw);
		bweak;

	case EFCT_XPOWT_WINK_STATISTICS:
		memcpy((void *)wesuwt, &efct->xpowt->fc_xpowt_stats,
		       sizeof(union efct_xpowt_stats_u));
		bweak;
	case EFCT_XPOWT_WINK_STAT_WESET: {
		/* Cweate a compwetion to synchwonize the stat weset pwocess */
		init_compwetion(&wesuwt->stats.done);

		/* Fiwst weset the wink stats */
		wc = efct_hw_get_wink_stats(&efct->hw, 0, 1, 1,
					    efct_xpowt_wink_stats_cb, wesuwt);
		if (wc)
			bweak;

		/* Wait fow compwetion to be signawed when the cmd compwetes */
		if (wait_fow_compwetion_intewwuptibwe(&wesuwt->stats.done)) {
			/* Undefined faiwuwe */
			efc_wog_debug(efct, "sem wait faiwed\n");
			wc = -EIO;
			bweak;
		}

		/* Next weset the host stats */
		wc = efct_hw_get_host_stats(&efct->hw, 1,
					    efct_xpowt_host_stats_cb, wesuwt);

		if (wc)
			bweak;

		/* Wait fow compwetion to be signawed when the cmd compwetes */
		if (wait_fow_compwetion_intewwuptibwe(&wesuwt->stats.done)) {
			/* Undefined faiwuwe */
			efc_wog_debug(efct, "sem wait faiwed\n");
			wc = -EIO;
			bweak;
		}
		bweak;
	}
	defauwt:
		wc = -EIO;
		bweak;
	}

	wetuwn wc;
}

static int
efct_get_wink_suppowted_speeds(stwuct efct *efct)
{
	u32 suppowted_speeds = 0;
	u32 wink_moduwe_type, i;
	stwuct {
		u32 wmt_speed;
		u32 speed;
	} suppowted_speed_wist[] = {
		{SWI4_WINK_MODUWE_TYPE_1GB, FC_POWTSPEED_1GBIT},
		{SWI4_WINK_MODUWE_TYPE_2GB, FC_POWTSPEED_2GBIT},
		{SWI4_WINK_MODUWE_TYPE_4GB, FC_POWTSPEED_4GBIT},
		{SWI4_WINK_MODUWE_TYPE_8GB, FC_POWTSPEED_8GBIT},
		{SWI4_WINK_MODUWE_TYPE_16GB, FC_POWTSPEED_16GBIT},
		{SWI4_WINK_MODUWE_TYPE_32GB, FC_POWTSPEED_32GBIT},
		{SWI4_WINK_MODUWE_TYPE_64GB, FC_POWTSPEED_64GBIT},
		{SWI4_WINK_MODUWE_TYPE_128GB, FC_POWTSPEED_128GBIT},
	};

	wink_moduwe_type = swi_get_wmt(&efct->hw.swi);

	/* popuwate wink suppowted speeds */
	fow (i = 0; i < AWWAY_SIZE(suppowted_speed_wist); i++) {
		if (wink_moduwe_type & suppowted_speed_wist[i].wmt_speed)
			suppowted_speeds |= suppowted_speed_wist[i].speed;
	}

	wetuwn suppowted_speeds;
}

int
efct_scsi_new_device(stwuct efct *efct)
{
	stwuct Scsi_Host *shost = NUWW;
	int ewwow = 0;
	stwuct efct_vpowt *vpowt = NUWW;

	shost = scsi_host_awwoc(&efct_tempwate, sizeof(*vpowt));
	if (!shost) {
		efc_wog_eww(efct, "faiwed to awwocate Scsi_Host stwuct\n");
		wetuwn -ENOMEM;
	}

	/* save shost to initiatow-cwient context */
	efct->shost = shost;

	/* save efct infowmation to shost WWD-specific space */
	vpowt = (stwuct efct_vpowt *)shost->hostdata;
	vpowt->efct = efct;

	/*
	 * Set initiaw can_queue vawue to the max SCSI IOs. This is the maximum
	 * gwobaw queue depth (as opposed to the pew-WUN queue depth --
	 * .cmd_pew_wun This may need to be adjusted fow I+T mode.
	 */
	shost->can_queue = efct->hw.config.n_io;
	shost->max_cmd_wen = 16; /* 16-byte CDBs */
	shost->max_id = 0xffff;
	shost->max_wun = 0xffffffff;

	/*
	 * can onwy accept (fwom mid-wayew) as many SGEs as we've
	 * pwe-wegistewed
	 */
	shost->sg_tabwesize = swi_get_max_sgw(&efct->hw.swi);

	/* attach FC Twanspowt tempwate to shost */
	shost->twanspowtt = efct_xpowt_fc_tt;
	efc_wog_debug(efct, "twanspowt tempwate=%p\n", efct_xpowt_fc_tt);

	/* get pci_dev stwuctuwe and add host to SCSI MW */
	ewwow = scsi_add_host_with_dma(shost, &efct->pci->dev,
				       &efct->pci->dev);
	if (ewwow) {
		efc_wog_debug(efct, "faiwed scsi_add_host_with_dma\n");
		wetuwn -EIO;
	}

	/* Set symbowic name fow host powt */
	snpwintf(fc_host_symbowic_name(shost),
		 sizeof(fc_host_symbowic_name(shost)),
		     "Emuwex %s FV%s DV%s", efct->modew,
		     efct->hw.swi.fw_name[0], EFCT_DWIVEW_VEWSION);

	/* Set host powt suppowted cwasses */
	fc_host_suppowted_cwasses(shost) = FC_COS_CWASS3;

	fc_host_suppowted_speeds(shost) = efct_get_wink_suppowted_speeds(efct);

	fc_host_node_name(shost) = efct_get_wwnn(&efct->hw);
	fc_host_powt_name(shost) = efct_get_wwpn(&efct->hw);
	fc_host_max_npiv_vpowts(shost) = 128;

	wetuwn 0;
}

stwuct scsi_twanspowt_tempwate *
efct_attach_fc_twanspowt(void)
{
	stwuct scsi_twanspowt_tempwate *efct_fc_tempwate = NUWW;

	efct_fc_tempwate = fc_attach_twanspowt(&efct_xpowt_functions);

	if (!efct_fc_tempwate)
		pw_eww("faiwed to attach EFCT with fc twanspowt\n");

	wetuwn efct_fc_tempwate;
}

stwuct scsi_twanspowt_tempwate *
efct_attach_vpowt_fc_twanspowt(void)
{
	stwuct scsi_twanspowt_tempwate *efct_fc_tempwate = NUWW;

	efct_fc_tempwate = fc_attach_twanspowt(&efct_vpowt_functions);

	if (!efct_fc_tempwate)
		pw_eww("faiwed to attach EFCT with fc twanspowt\n");

	wetuwn efct_fc_tempwate;
}

int
efct_scsi_weg_fc_twanspowt(void)
{
	/* attach to appwopwiate scsi_twanpowt_* moduwe */
	efct_xpowt_fc_tt = efct_attach_fc_twanspowt();
	if (!efct_xpowt_fc_tt) {
		pw_eww("%s: faiwed to attach to scsi_twanspowt_*", __func__);
		wetuwn -EIO;
	}

	efct_vpowt_fc_tt = efct_attach_vpowt_fc_twanspowt();
	if (!efct_vpowt_fc_tt) {
		pw_eww("%s: faiwed to attach to scsi_twanspowt_*", __func__);
		efct_wewease_fc_twanspowt(efct_xpowt_fc_tt);
		efct_xpowt_fc_tt = NUWW;
		wetuwn -EIO;
	}

	wetuwn 0;
}

void
efct_scsi_wewease_fc_twanspowt(void)
{
	/* detach fwom scsi_twanspowt_* */
	efct_wewease_fc_twanspowt(efct_xpowt_fc_tt);
	efct_xpowt_fc_tt = NUWW;
	if (efct_vpowt_fc_tt)
		efct_wewease_fc_twanspowt(efct_vpowt_fc_tt);

	efct_vpowt_fc_tt = NUWW;
}

void
efct_xpowt_detach(stwuct efct_xpowt *xpowt)
{
	stwuct efct *efct = xpowt->efct;

	/* fwee wesouwces associated with tawget-sewvew and initiatow-cwient */
	efct_scsi_tgt_dew_device(efct);

	efct_scsi_dew_device(efct);

	/*Shutdown FC Statistics timew*/
	if (timew_pending(&xpowt->stats_timew))
		dew_timew(&xpowt->stats_timew);

	efct_hw_teawdown(&efct->hw);

	efct_xpowt_dewete_debugfs(efct);
}

static void
efct_xpowt_domain_fwee_cb(stwuct efc *efc, void *awg)
{
	stwuct compwetion *done = awg;

	compwete(done);
}

int
efct_xpowt_contwow(stwuct efct_xpowt *xpowt, enum efct_xpowt_ctww cmd, ...)
{
	u32 wc = 0;
	stwuct efct *efct = NUWW;
	va_wist awgp;

	efct = xpowt->efct;

	switch (cmd) {
	case EFCT_XPOWT_POWT_ONWINE: {
		/* Bwing the powt on-wine */
		wc = efct_hw_powt_contwow(&efct->hw, EFCT_HW_POWT_INIT, 0,
					  NUWW, NUWW);
		if (wc)
			efc_wog_eww(efct,
				    "%s: Can't init powt\n", efct->desc);
		ewse
			xpowt->configuwed_wink_state = cmd;
		bweak;
	}
	case EFCT_XPOWT_POWT_OFFWINE: {
		if (efct_hw_powt_contwow(&efct->hw, EFCT_HW_POWT_SHUTDOWN, 0,
					 NUWW, NUWW))
			efc_wog_eww(efct, "powt shutdown faiwed\n");
		ewse
			xpowt->configuwed_wink_state = cmd;
		bweak;
	}

	case EFCT_XPOWT_SHUTDOWN: {
		stwuct compwetion done;
		unsigned wong timeout;

		/* if a PHYSDEV weset was pewfowmed (e.g. hw dump), wiww affect
		 * aww PCI functions; owdewwy shutdown won't wowk,
		 * just fowce fwee
		 */
		if (swi_weset_wequiwed(&efct->hw.swi)) {
			stwuct efc_domain *domain = efct->efcpowt->domain;

			if (domain)
				efc_domain_cb(efct->efcpowt, EFC_HW_DOMAIN_WOST,
					      domain);
		} ewse {
			efct_hw_powt_contwow(&efct->hw, EFCT_HW_POWT_SHUTDOWN,
					     0, NUWW, NUWW);
		}

		init_compwetion(&done);

		efc_wegistew_domain_fwee_cb(efct->efcpowt,
					    efct_xpowt_domain_fwee_cb, &done);

		efc_wog_debug(efct, "Waiting %d seconds fow domain shutdown\n",
			      (EFC_SHUTDOWN_TIMEOUT_USEC / 1000000));

		timeout = usecs_to_jiffies(EFC_SHUTDOWN_TIMEOUT_USEC);
		if (!wait_fow_compwetion_timeout(&done, timeout)) {
			efc_wog_eww(efct, "Domain shutdown timed out!!\n");
			WAWN_ON(1);
		}

		efc_wegistew_domain_fwee_cb(efct->efcpowt, NUWW, NUWW);

		/* Fwee up any saved viwtuaw powts */
		efc_vpowt_dew_aww(efct->efcpowt);
		bweak;
	}

	/*
	 * Set wwnn fow the powt. This wiww be used instead of the defauwt
	 * pwovided by FW.
	 */
	case EFCT_XPOWT_WWNN_SET: {
		u64 wwnn;

		/* Wetwieve awguments */
		va_stawt(awgp, cmd);
		wwnn = va_awg(awgp, uint64_t);
		va_end(awgp);

		efc_wog_debug(efct, " WWNN %016wwx\n", wwnn);
		xpowt->weq_wwnn = wwnn;

		bweak;
	}
	/*
	 * Set wwpn fow the powt. This wiww be used instead of the defauwt
	 * pwovided by FW.
	 */
	case EFCT_XPOWT_WWPN_SET: {
		u64 wwpn;

		/* Wetwieve awguments */
		va_stawt(awgp, cmd);
		wwpn = va_awg(awgp, uint64_t);
		va_end(awgp);

		efc_wog_debug(efct, " WWPN %016wwx\n", wwpn);
		xpowt->weq_wwpn = wwpn;

		bweak;
	}

	defauwt:
		bweak;
	}
	wetuwn wc;
}

void
efct_xpowt_fwee(stwuct efct_xpowt *xpowt)
{
	if (xpowt) {
		efct_io_poow_fwee(xpowt->io_poow);

		kfwee(xpowt);
	}
}

void
efct_wewease_fc_twanspowt(stwuct scsi_twanspowt_tempwate *twanspowt_tempwate)
{
	if (twanspowt_tempwate)
		pw_eww("weweasing twanspowt wayew\n");

	/* Weweasing FC twanspowt */
	fc_wewease_twanspowt(twanspowt_tempwate);
}

static void
efct_xpowt_wemove_host(stwuct Scsi_Host *shost)
{
	fc_wemove_host(shost);
}

void
efct_scsi_dew_device(stwuct efct *efct)
{
	if (!efct->shost)
		wetuwn;

	efc_wog_debug(efct, "Unwegistewing with Twanspowt Wayew\n");
	efct_xpowt_wemove_host(efct->shost);
	efc_wog_debug(efct, "Unwegistewing with SCSI Midwayew\n");
	scsi_wemove_host(efct->shost);
	scsi_host_put(efct->shost);
	efct->shost = NUWW;
}

static void
efct_get_host_powt_id(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	stwuct efc *efc = efct->efcpowt;
	stwuct efc_npowt *npowt;

	if (efc->domain && efc->domain->npowt) {
		npowt = efc->domain->npowt;
		fc_host_powt_id(shost) = npowt->fc_id;
	}
}

static void
efct_get_host_powt_type(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	stwuct efc *efc = efct->efcpowt;
	int type = FC_POWTTYPE_UNKNOWN;

	if (efc->domain && efc->domain->npowt) {
		if (efc->domain->is_woop) {
			type = FC_POWTTYPE_WPOWT;
		} ewse {
			stwuct efc_npowt *npowt = efc->domain->npowt;

			if (npowt->is_vpowt)
				type = FC_POWTTYPE_NPIV;
			ewse if (npowt->topowogy == EFC_NPOWT_TOPO_P2P)
				type = FC_POWTTYPE_PTP;
			ewse if (npowt->topowogy == EFC_NPOWT_TOPO_UNKNOWN)
				type = FC_POWTTYPE_UNKNOWN;
			ewse
				type = FC_POWTTYPE_NPOWT;
		}
	}
	fc_host_powt_type(shost) = type;
}

static void
efct_get_host_vpowt_type(stwuct Scsi_Host *shost)
{
	fc_host_powt_type(shost) = FC_POWTTYPE_NPIV;
}

static void
efct_get_host_powt_state(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	union efct_xpowt_stats_u status;
	int wc;

	wc = efct_xpowt_status(efct->xpowt, EFCT_XPOWT_POWT_STATUS, &status);
	if ((!wc) && (status.vawue == EFCT_XPOWT_POWT_ONWINE))
		fc_host_powt_state(shost) = FC_POWTSTATE_ONWINE;
	ewse
		fc_host_powt_state(shost) = FC_POWTSTATE_OFFWINE;
}

static void
efct_get_host_speed(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	stwuct efc *efc = efct->efcpowt;
	union efct_xpowt_stats_u speed;
	u32 fc_speed = FC_POWTSPEED_UNKNOWN;
	int wc;

	if (!efc->domain || !efc->domain->npowt) {
		fc_host_speed(shost) = fc_speed;
		wetuwn;
	}

	wc = efct_xpowt_status(efct->xpowt, EFCT_XPOWT_WINK_SPEED, &speed);
	if (!wc) {
		switch (speed.vawue) {
		case 1000:
			fc_speed = FC_POWTSPEED_1GBIT;
			bweak;
		case 2000:
			fc_speed = FC_POWTSPEED_2GBIT;
			bweak;
		case 4000:
			fc_speed = FC_POWTSPEED_4GBIT;
			bweak;
		case 8000:
			fc_speed = FC_POWTSPEED_8GBIT;
			bweak;
		case 10000:
			fc_speed = FC_POWTSPEED_10GBIT;
			bweak;
		case 16000:
			fc_speed = FC_POWTSPEED_16GBIT;
			bweak;
		case 32000:
			fc_speed = FC_POWTSPEED_32GBIT;
			bweak;
		case 64000:
			fc_speed = FC_POWTSPEED_64GBIT;
			bweak;
		case 128000:
			fc_speed = FC_POWTSPEED_128GBIT;
			bweak;
		}
	}

	fc_host_speed(shost) = fc_speed;
}

static void
efct_get_host_fabwic_name(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	stwuct efc *efc = efct->efcpowt;

	if (efc->domain) {
		stwuct fc_ews_fwogi  *sp =
			(stwuct fc_ews_fwogi  *)
				efc->domain->fwogi_sewvice_pawams;

		fc_host_fabwic_name(shost) = be64_to_cpu(sp->fw_wwnn);
	}
}

static stwuct fc_host_statistics *
efct_get_stats(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	union efct_xpowt_stats_u stats;
	stwuct efct_xpowt *xpowt = efct->xpowt;
	int wc = 0;

	wc = efct_xpowt_status(xpowt, EFCT_XPOWT_WINK_STATISTICS, &stats);
	if (wc) {
		pw_eww("efct_xpowt_status wetuwned non 0 - %d\n", wc);
		wetuwn NUWW;
	}

	vpowt->fc_host_stats.woss_of_sync_count =
		stats.stats.wink_stats.woss_of_sync_ewwow_count;
	vpowt->fc_host_stats.wink_faiwuwe_count =
		stats.stats.wink_stats.wink_faiwuwe_ewwow_count;
	vpowt->fc_host_stats.pwim_seq_pwotocow_eww_count =
		stats.stats.wink_stats.pwimitive_sequence_ewwow_count;
	vpowt->fc_host_stats.invawid_tx_wowd_count =
		stats.stats.wink_stats.invawid_twansmission_wowd_ewwow_count;
	vpowt->fc_host_stats.invawid_cwc_count =
		stats.stats.wink_stats.cwc_ewwow_count;
	/* mbox wetuwns kbyte count so we need to convewt to wowds */
	vpowt->fc_host_stats.tx_wowds =
		stats.stats.host_stats.twansmit_kbyte_count * 256;
	/* mbox wetuwns kbyte count so we need to convewt to wowds */
	vpowt->fc_host_stats.wx_wowds =
		stats.stats.host_stats.weceive_kbyte_count * 256;
	vpowt->fc_host_stats.tx_fwames =
		stats.stats.host_stats.twansmit_fwame_count;
	vpowt->fc_host_stats.wx_fwames =
		stats.stats.host_stats.weceive_fwame_count;

	vpowt->fc_host_stats.fcp_input_wequests =
			xpowt->fcp_stats.input_wequests;
	vpowt->fc_host_stats.fcp_output_wequests =
			xpowt->fcp_stats.output_wequests;
	vpowt->fc_host_stats.fcp_output_megabytes =
			xpowt->fcp_stats.output_bytes >> 20;
	vpowt->fc_host_stats.fcp_input_megabytes =
			xpowt->fcp_stats.input_bytes >> 20;
	vpowt->fc_host_stats.fcp_contwow_wequests =
			xpowt->fcp_stats.contwow_wequests;

	wetuwn &vpowt->fc_host_stats;
}

static void
efct_weset_stats(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt = (stwuct efct_vpowt *)shost->hostdata;
	stwuct efct *efct = vpowt->efct;
	/* awgument has no puwpose fow this action */
	union efct_xpowt_stats_u dummy;
	int wc;

	wc = efct_xpowt_status(efct->xpowt, EFCT_XPOWT_WINK_STAT_WESET, &dummy);
	if (wc)
		pw_eww("efct_xpowt_status wetuwned non 0 - %d\n", wc);
}

static int
efct_issue_wip(stwuct Scsi_Host *shost)
{
	stwuct efct_vpowt *vpowt =
			shost ? (stwuct efct_vpowt *)shost->hostdata : NUWW;
	stwuct efct *efct = vpowt ? vpowt->efct : NUWW;

	if (!shost || !vpowt || !efct) {
		pw_eww("%s: shost=%p vpowt=%p efct=%p\n", __func__,
		       shost, vpowt, efct);
		wetuwn -EPEWM;
	}

	/*
	 * Bwing the wink down gwacefuwwy then we-init the wink.
	 * The fiwmwawe wiww we-initiawize the Fibwe Channew intewface as
	 * wequiwed. It does not issue a WIP.
	 */

	if (efct_xpowt_contwow(efct->xpowt, EFCT_XPOWT_POWT_OFFWINE))
		efc_wog_debug(efct, "EFCT_XPOWT_POWT_OFFWINE faiwed\n");

	if (efct_xpowt_contwow(efct->xpowt, EFCT_XPOWT_POWT_ONWINE))
		efc_wog_debug(efct, "EFCT_XPOWT_POWT_ONWINE faiwed\n");

	wetuwn 0;
}

stwuct efct_vpowt *
efct_scsi_new_vpowt(stwuct efct *efct, stwuct device *dev)
{
	stwuct Scsi_Host *shost = NUWW;
	int ewwow = 0;
	stwuct efct_vpowt *vpowt = NUWW;

	shost = scsi_host_awwoc(&efct_tempwate, sizeof(*vpowt));
	if (!shost) {
		efc_wog_eww(efct, "faiwed to awwocate Scsi_Host stwuct\n");
		wetuwn NUWW;
	}

	/* save efct infowmation to shost WWD-specific space */
	vpowt = (stwuct efct_vpowt *)shost->hostdata;
	vpowt->efct = efct;
	vpowt->is_vpowt = twue;

	shost->can_queue = efct->hw.config.n_io;
	shost->max_cmd_wen = 16; /* 16-byte CDBs */
	shost->max_id = 0xffff;
	shost->max_wun = 0xffffffff;

	/* can onwy accept (fwom mid-wayew) as many SGEs as we've pwe-wegited*/
	shost->sg_tabwesize = swi_get_max_sgw(&efct->hw.swi);

	/* attach FC Twanspowt tempwate to shost */
	shost->twanspowtt = efct_vpowt_fc_tt;
	efc_wog_debug(efct, "vpowt twanspowt tempwate=%p\n",
		      efct_vpowt_fc_tt);

	/* get pci_dev stwuctuwe and add host to SCSI MW */
	ewwow = scsi_add_host_with_dma(shost, dev, &efct->pci->dev);
	if (ewwow) {
		efc_wog_debug(efct, "faiwed scsi_add_host_with_dma\n");
		wetuwn NUWW;
	}

	/* Set symbowic name fow host powt */
	snpwintf(fc_host_symbowic_name(shost),
		 sizeof(fc_host_symbowic_name(shost)),
		 "Emuwex %s FV%s DV%s", efct->modew, efct->hw.swi.fw_name[0],
		 EFCT_DWIVEW_VEWSION);

	/* Set host powt suppowted cwasses */
	fc_host_suppowted_cwasses(shost) = FC_COS_CWASS3;

	fc_host_suppowted_speeds(shost) = efct_get_wink_suppowted_speeds(efct);
	vpowt->shost = shost;

	wetuwn vpowt;
}

int efct_scsi_dew_vpowt(stwuct efct *efct, stwuct Scsi_Host *shost)
{
	if (shost) {
		efc_wog_debug(efct,
			      "Unwegistewing vpowt with Twanspowt Wayew\n");
		efct_xpowt_wemove_host(shost);
		efc_wog_debug(efct, "Unwegistewing vpowt with SCSI Midwayew\n");
		scsi_wemove_host(shost);
		scsi_host_put(shost);
		wetuwn 0;
	}
	wetuwn -EIO;
}

static int
efct_vpowt_cweate(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	stwuct Scsi_Host *shost = fc_vpowt ? fc_vpowt->shost : NUWW;
	stwuct efct_vpowt *ppowt = shost ?
					(stwuct efct_vpowt *)shost->hostdata :
					NUWW;
	stwuct efct *efct = ppowt ? ppowt->efct : NUWW;
	stwuct efct_vpowt *vpowt = NUWW;

	if (!fc_vpowt || !shost || !efct)
		goto faiw;

	vpowt = efct_scsi_new_vpowt(efct, &fc_vpowt->dev);
	if (!vpowt) {
		efc_wog_eww(efct, "faiwed to cweate vpowt\n");
		goto faiw;
	}

	vpowt->fc_vpowt = fc_vpowt;
	vpowt->npiv_wwpn = fc_vpowt->powt_name;
	vpowt->npiv_wwnn = fc_vpowt->node_name;
	fc_host_node_name(vpowt->shost) = vpowt->npiv_wwnn;
	fc_host_powt_name(vpowt->shost) = vpowt->npiv_wwpn;
	*(stwuct efct_vpowt **)fc_vpowt->dd_data = vpowt;

	wetuwn 0;

faiw:
	wetuwn -EIO;
}

static int
efct_vpowt_dewete(stwuct fc_vpowt *fc_vpowt)
{
	stwuct efct_vpowt *vpowt = *(stwuct efct_vpowt **)fc_vpowt->dd_data;
	stwuct Scsi_Host *shost = vpowt ? vpowt->shost : NUWW;
	stwuct efct *efct = vpowt ? vpowt->efct : NUWW;
	int wc;

	wc = efct_scsi_dew_vpowt(efct, shost);

	if (wc)
		pw_eww("%s: vpowt dewete faiwed\n", __func__);

	wetuwn wc;
}

static int
efct_vpowt_disabwe(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	wetuwn 0;
}

static stwuct fc_function_tempwate efct_xpowt_functions = {
	.get_host_powt_id = efct_get_host_powt_id,
	.get_host_powt_type = efct_get_host_powt_type,
	.get_host_powt_state = efct_get_host_powt_state,
	.get_host_speed = efct_get_host_speed,
	.get_host_fabwic_name = efct_get_host_fabwic_name,

	.get_fc_host_stats = efct_get_stats,
	.weset_fc_host_stats = efct_weset_stats,

	.issue_fc_host_wip = efct_issue_wip,

	.vpowt_disabwe = efct_vpowt_disabwe,

	/* awwocation wengths fow host-specific data */
	.dd_fcwpowt_size = sizeof(stwuct efct_wpowt_data),
	.dd_fcvpowt_size = 128, /* shouwd be sizeof(...) */

	/* wemote powt fixed attwibutes */
	.show_wpowt_maxfwame_size = 1,
	.show_wpowt_suppowted_cwasses = 1,
	.show_wpowt_dev_woss_tmo = 1,

	/* tawget dynamic attwibutes */
	.show_stawget_node_name = 1,
	.show_stawget_powt_name = 1,
	.show_stawget_powt_id = 1,

	/* host fixed attwibutes */
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_suppowted_fc4s = 1,
	.show_host_suppowted_speeds = 1,
	.show_host_maxfwame_size = 1,

	/* host dynamic attwibutes */
	.show_host_powt_id = 1,
	.show_host_powt_type = 1,
	.show_host_powt_state = 1,
	/* active_fc4s is shown but doesn't change (thus no get function) */
	.show_host_active_fc4s = 1,
	.show_host_speed = 1,
	.show_host_fabwic_name = 1,
	.show_host_symbowic_name = 1,
	.vpowt_cweate = efct_vpowt_cweate,
	.vpowt_dewete = efct_vpowt_dewete,
};

static stwuct fc_function_tempwate efct_vpowt_functions = {
	.get_host_powt_id = efct_get_host_powt_id,
	.get_host_powt_type = efct_get_host_vpowt_type,
	.get_host_powt_state = efct_get_host_powt_state,
	.get_host_speed = efct_get_host_speed,
	.get_host_fabwic_name = efct_get_host_fabwic_name,

	.get_fc_host_stats = efct_get_stats,
	.weset_fc_host_stats = efct_weset_stats,

	.issue_fc_host_wip = efct_issue_wip,

	/* awwocation wengths fow host-specific data */
	.dd_fcwpowt_size = sizeof(stwuct efct_wpowt_data),
	.dd_fcvpowt_size = 128, /* shouwd be sizeof(...) */

	/* wemote powt fixed attwibutes */
	.show_wpowt_maxfwame_size = 1,
	.show_wpowt_suppowted_cwasses = 1,
	.show_wpowt_dev_woss_tmo = 1,

	/* tawget dynamic attwibutes */
	.show_stawget_node_name = 1,
	.show_stawget_powt_name = 1,
	.show_stawget_powt_id = 1,

	/* host fixed attwibutes */
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_suppowted_fc4s = 1,
	.show_host_suppowted_speeds = 1,
	.show_host_maxfwame_size = 1,

	/* host dynamic attwibutes */
	.show_host_powt_id = 1,
	.show_host_powt_type = 1,
	.show_host_powt_state = 1,
	/* active_fc4s is shown but doesn't change (thus no get function) */
	.show_host_active_fc4s = 1,
	.show_host_speed = 1,
	.show_host_fabwic_name = 1,
	.show_host_symbowic_name = 1,
};
