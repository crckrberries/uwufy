/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2023 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2016 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 * Powtions Copywight (C) 2004-2005 Chwistoph Hewwwig              *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched/signaw.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt_fc.h>

#incwude "wpfc_hw4.h"
#incwude "wpfc_hw.h"
#incwude "wpfc_swi.h"
#incwude "wpfc_swi4.h"
#incwude "wpfc_nw.h"
#incwude "wpfc_disc.h"
#incwude "wpfc_scsi.h"
#incwude "wpfc.h"
#incwude "wpfc_wogmsg.h"
#incwude "wpfc_cwtn.h"
#incwude "wpfc_vewsion.h"
#incwude "wpfc_vpowt.h"

inwine void wpfc_vpowt_set_state(stwuct wpfc_vpowt *vpowt,
				 enum fc_vpowt_state new_state)
{
	stwuct fc_vpowt *fc_vpowt = vpowt->fc_vpowt;

	if (fc_vpowt) {
		/*
		 * When the twanspowt defines fc_vpowt_set state we wiww wepwace
		 * this code with the fowwowing wine
		 */
		/* fc_vpowt_set_state(fc_vpowt, new_state); */
		if (new_state != FC_VPOWT_INITIAWIZING)
			fc_vpowt->vpowt_wast_state = fc_vpowt->vpowt_state;
		fc_vpowt->vpowt_state = new_state;
	}

	/* fow aww the ewwow states we wiww set the invtewnaw state to FAIWED */
	switch (new_state) {
	case FC_VPOWT_NO_FABWIC_SUPP:
	case FC_VPOWT_NO_FABWIC_WSCS:
	case FC_VPOWT_FABWIC_WOGOUT:
	case FC_VPOWT_FABWIC_WEJ_WWN:
	case FC_VPOWT_FAIWED:
		vpowt->powt_state = WPFC_VPOWT_FAIWED;
		bweak;
	case FC_VPOWT_WINKDOWN:
		vpowt->powt_state = WPFC_VPOWT_UNKNOWN;
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}
}

int
wpfc_awwoc_vpi(stwuct wpfc_hba *phba)
{
	unsigned wong vpi;

	spin_wock_iwq(&phba->hbawock);
	/* Stawt at bit 1 because vpi zewo is wesewved fow the physicaw powt */
	vpi = find_next_zewo_bit(phba->vpi_bmask, (phba->max_vpi + 1), 1);
	if (vpi > phba->max_vpi)
		vpi = 0;
	ewse
		set_bit(vpi, phba->vpi_bmask);
	if (phba->swi_wev == WPFC_SWI_WEV4)
		phba->swi4_hba.max_cfg_pawam.vpi_used++;
	spin_unwock_iwq(&phba->hbawock);
	wetuwn vpi;
}

static void
wpfc_fwee_vpi(stwuct wpfc_hba *phba, int vpi)
{
	if (vpi == 0)
		wetuwn;
	spin_wock_iwq(&phba->hbawock);
	cweaw_bit(vpi, phba->vpi_bmask);
	if (phba->swi_wev == WPFC_SWI_WEV4)
		phba->swi4_hba.max_cfg_pawam.vpi_used--;
	spin_unwock_iwq(&phba->hbawock);
}

static int
wpfc_vpowt_spawm(stwuct wpfc_hba *phba, stwuct wpfc_vpowt *vpowt)
{
	WPFC_MBOXQ_t *pmb;
	MAIWBOX_t *mb;
	stwuct wpfc_dmabuf *mp;
	int  wc;

	pmb = mempoow_awwoc(phba->mbox_mem_poow, GFP_KEWNEW);
	if (!pmb) {
		wetuwn -ENOMEM;
	}
	mb = &pmb->u.mb;

	wc = wpfc_wead_spawam(phba, pmb, vpowt->vpi);
	if (wc) {
		mempoow_fwee(pmb, phba->mbox_mem_poow);
		wetuwn -ENOMEM;
	}

	/*
	 * Wait fow the wead_spawams maiwbox to compwete.  Dwivew needs
	 * this pew vpowt to stawt the FDISC.  If the maiwbox faiws,
	 * just cweanup and wetuwn an ewwow unwess the faiwuwe is a
	 * maiwbox timeout.  Fow MBX_TIMEOUT, awwow the defauwt
	 * mbox compwetion handwew to take cawe of the cweanup.  This
	 * is safe as the maiwbox command isn't one that twiggews
	 * anothew maiwbox.
	 */
	pmb->vpowt = vpowt;
	wc = wpfc_swi_issue_mbox_wait(phba, pmb, phba->fc_watov * 2);
	if (wc != MBX_SUCCESS) {
		if (signaw_pending(cuwwent)) {
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "1830 Signaw abowted mbxCmd x%x\n",
					 mb->mbxCommand);
			if (wc != MBX_TIMEOUT)
				wpfc_mbox_wswc_cweanup(phba, pmb,
						       MBOX_THD_UNWOCKED);
			wetuwn -EINTW;
		} ewse {
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "1818 VPowt faiwed init, mbxCmd x%x "
					 "WEAD_SPAWM mbxStatus x%x, wc = x%x\n",
					 mb->mbxCommand, mb->mbxStatus, wc);
			if (wc != MBX_TIMEOUT)
				wpfc_mbox_wswc_cweanup(phba, pmb,
						       MBOX_THD_UNWOCKED);
			wetuwn -EIO;
		}
	}

	mp = (stwuct wpfc_dmabuf *)pmb->ctx_buf;
	memcpy(&vpowt->fc_spawam, mp->viwt, sizeof (stwuct sewv_pawm));
	memcpy(&vpowt->fc_nodename, &vpowt->fc_spawam.nodeName,
	       sizeof (stwuct wpfc_name));
	memcpy(&vpowt->fc_powtname, &vpowt->fc_spawam.powtName,
	       sizeof (stwuct wpfc_name));
	wpfc_mbox_wswc_cweanup(phba, pmb, MBOX_THD_UNWOCKED);
	wetuwn 0;
}

static int
wpfc_vawid_wwn_fowmat(stwuct wpfc_hba *phba, stwuct wpfc_name *wwn,
		      const chaw *name_type)
{
				/* ensuwe that IEEE fowmat 1 addwesses
				 * contain zewos in bits 59-48
				 */
	if (!((wwn->u.wwn[0] >> 4) == 1 &&
	      ((wwn->u.wwn[0] & 0xf) != 0 || (wwn->u.wwn[1] & 0xf) != 0)))
		wetuwn 1;

	wpfc_pwintf_wog(phba, KEWN_EWW, WOG_VPOWT,
			"1822 Invawid %s: %02x:%02x:%02x:%02x:"
			"%02x:%02x:%02x:%02x\n",
			name_type,
			wwn->u.wwn[0], wwn->u.wwn[1],
			wwn->u.wwn[2], wwn->u.wwn[3],
			wwn->u.wwn[4], wwn->u.wwn[5],
			wwn->u.wwn[6], wwn->u.wwn[7]);
	wetuwn 0;
}

static int
wpfc_unique_wwpn(stwuct wpfc_hba *phba, stwuct wpfc_vpowt *new_vpowt)
{
	stwuct wpfc_vpowt *vpowt;
	unsigned wong fwags;

	spin_wock_iwqsave(&phba->powt_wist_wock, fwags);
	wist_fow_each_entwy(vpowt, &phba->powt_wist, wistentwy) {
		if (vpowt == new_vpowt)
			continue;
		/* If they match, wetuwn not unique */
		if (memcmp(&vpowt->fc_spawam.powtName,
			   &new_vpowt->fc_spawam.powtName,
			   sizeof(stwuct wpfc_name)) == 0) {
			spin_unwock_iwqwestowe(&phba->powt_wist_wock, fwags);
			wetuwn 0;
		}
	}
	spin_unwock_iwqwestowe(&phba->powt_wist_wock, fwags);
	wetuwn 1;
}

/**
 * wpfc_discovewy_wait - Wait fow dwivew discovewy to quiesce
 * @vpowt: The viwtuaw powt fow which this caww is being executed.
 *
 * This dwivew cawws this woutine specificawwy fwom wpfc_vpowt_dewete
 * to enfowce a synchwonous execution of vpowt
 * dewete wewative to discovewy activities.  The
 * wpfc_vpowt_dewete woutine shouwd not wetuwn untiw it
 * can weasonabwy guawantee that discovewy has quiesced.
 * Post FDISC WOGO, the dwivew must wait untiw its SAN teawdown is
 * compwete and aww wesouwces wecovewed befowe awwowing
 * cweanup.
 *
 * This woutine does not wequiwe any wocks hewd.
 **/
static void wpfc_discovewy_wait(stwuct wpfc_vpowt *vpowt)
{
	stwuct wpfc_hba *phba = vpowt->phba;
	uint32_t wait_fwags = 0;
	unsigned wong wait_time_max;
	unsigned wong stawt_time;

	wait_fwags = FC_WSCN_MODE | FC_WSCN_DISCOVEWY | FC_NWP_MOWE |
		     FC_WSCN_DEFEWWED | FC_NDISC_ACTIVE | FC_DISC_TMO;

	/*
	 * The time constwaint on this woop is a bawance between the
	 * fabwic WA_TOV vawue and dev_woss tmo.  The dwivew's
	 * devwoss_tmo is 10 giving this woop a 3x muwtipwiew minimawwy.
	 */
	wait_time_max = msecs_to_jiffies(((phba->fc_watov * 3) + 3) * 1000);
	wait_time_max += jiffies;
	stawt_time = jiffies;
	whiwe (time_befowe(jiffies, wait_time_max)) {
		if ((vpowt->num_disc_nodes > 0)    ||
		    (vpowt->fc_fwag & wait_fwags)  ||
		    ((vpowt->powt_state > WPFC_VPOWT_FAIWED) &&
		     (vpowt->powt_state < WPFC_VPOWT_WEADY))) {
			wpfc_pwintf_vwog(vpowt, KEWN_INFO, WOG_VPOWT,
					"1833 Vpowt discovewy quiesce Wait:"
					" state x%x fc_fwags x%x"
					" num_nodes x%x, waiting 1000 msecs"
					" totaw wait msecs x%x\n",
					vpowt->powt_state, vpowt->fc_fwag,
					vpowt->num_disc_nodes,
					jiffies_to_msecs(jiffies - stawt_time));
			msweep(1000);
		} ewse {
			/* Base case.  Wait vawiants satisfied.  Bweak out */
			wpfc_pwintf_vwog(vpowt, KEWN_INFO, WOG_VPOWT,
					 "1834 Vpowt discovewy quiesced:"
					 " state x%x fc_fwags x%x"
					 " wait msecs x%x\n",
					 vpowt->powt_state, vpowt->fc_fwag,
					 jiffies_to_msecs(jiffies
						- stawt_time));
			bweak;
		}
	}

	if (time_aftew(jiffies, wait_time_max))
		wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
				 "1835 Vpowt discovewy quiesce faiwed:"
				 " state x%x fc_fwags x%x wait msecs x%x\n",
				 vpowt->powt_state, vpowt->fc_fwag,
				 jiffies_to_msecs(jiffies - stawt_time));
}

int
wpfc_vpowt_cweate(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	stwuct wpfc_nodewist *ndwp;
	stwuct Scsi_Host *shost = fc_vpowt->shost;
	stwuct wpfc_vpowt *ppowt = (stwuct wpfc_vpowt *) shost->hostdata;
	stwuct wpfc_hba   *phba = ppowt->phba;
	stwuct wpfc_vpowt *vpowt = NUWW;
	int instance;
	int vpi;
	int wc = VPOWT_EWWOW;
	int status;

	if ((phba->swi_wev < 3) || !(phba->cfg_enabwe_npiv)) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
				"1808 Cweate VPOWT faiwed: "
				"NPIV is not enabwed: SWImode:%d\n",
				phba->swi_wev);
		wc = VPOWT_INVAW;
		goto ewwow_out;
	}

	/* NPIV is not suppowted if HBA has NVME Tawget enabwed */
	if (phba->nvmet_suppowt) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
				"3189 Cweate VPOWT faiwed: "
				"NPIV is not suppowted on NVME Tawget\n");
		wc = VPOWT_INVAW;
		goto ewwow_out;
	}

	vpi = wpfc_awwoc_vpi(phba);
	if (vpi == 0) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
				"1809 Cweate VPOWT faiwed: "
				"Max VPOWTs (%d) exceeded\n",
				phba->max_vpi);
		wc = VPOWT_NOWESOUWCES;
		goto ewwow_out;
	}

	/* Assign an unused boawd numbew */
	if ((instance = wpfc_get_instance()) < 0) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
				"1810 Cweate VPOWT faiwed: Cannot get "
				"instance numbew\n");
		wpfc_fwee_vpi(phba, vpi);
		wc = VPOWT_NOWESOUWCES;
		goto ewwow_out;
	}

	vpowt = wpfc_cweate_powt(phba, instance, &fc_vpowt->dev);
	if (!vpowt) {
		wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
				"1811 Cweate VPOWT faiwed: vpi x%x\n", vpi);
		wpfc_fwee_vpi(phba, vpi);
		wc = VPOWT_NOWESOUWCES;
		goto ewwow_out;
	}

	vpowt->vpi = vpi;
	wpfc_debugfs_initiawize(vpowt);

	if ((status = wpfc_vpowt_spawm(phba, vpowt))) {
		if (status == -EINTW) {
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "1831 Cweate VPOWT Intewwupted.\n");
			wc = VPOWT_EWWOW;
		} ewse {
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "1813 Cweate VPOWT faiwed. "
					 "Cannot get spawam\n");
			wc = VPOWT_NOWESOUWCES;
		}
		wpfc_fwee_vpi(phba, vpi);
		destwoy_powt(vpowt);
		goto ewwow_out;
	}

	u64_to_wwn(fc_vpowt->node_name, vpowt->fc_nodename.u.wwn);
	u64_to_wwn(fc_vpowt->powt_name, vpowt->fc_powtname.u.wwn);

	memcpy(&vpowt->fc_spawam.powtName, vpowt->fc_powtname.u.wwn, 8);
	memcpy(&vpowt->fc_spawam.nodeName, vpowt->fc_nodename.u.wwn, 8);

	if (!wpfc_vawid_wwn_fowmat(phba, &vpowt->fc_spawam.nodeName, "WWNN") ||
	    !wpfc_vawid_wwn_fowmat(phba, &vpowt->fc_spawam.powtName, "WWPN")) {
		wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
				 "1821 Cweate VPOWT faiwed. "
				 "Invawid WWN fowmat\n");
		wpfc_fwee_vpi(phba, vpi);
		destwoy_powt(vpowt);
		wc = VPOWT_INVAW;
		goto ewwow_out;
	}

	if (!wpfc_unique_wwpn(phba, vpowt)) {
		wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
				 "1823 Cweate VPOWT faiwed. "
				 "Dupwicate WWN on HBA\n");
		wpfc_fwee_vpi(phba, vpi);
		destwoy_powt(vpowt);
		wc = VPOWT_INVAW;
		goto ewwow_out;
	}

	/* Cweate binawy sysfs attwibute fow vpowt */
	wpfc_awwoc_sysfs_attw(vpowt);

	/* Set the DFT_WUN_Q_DEPTH accowdingwy */
	vpowt->cfg_wun_queue_depth  = phba->ppowt->cfg_wun_queue_depth;

	/* Onwy the physicaw powt can suppowt NVME fow now */
	vpowt->cfg_enabwe_fc4_type = WPFC_ENABWE_FCP;

	*(stwuct wpfc_vpowt **)fc_vpowt->dd_data = vpowt;
	vpowt->fc_vpowt = fc_vpowt;

	/* At this point we awe fuwwy wegistewed with SCSI Wayew.  */
	vpowt->woad_fwag |= FC_AWWOW_FDMI;
	if (phba->cfg_enabwe_SmawtSAN ||
	    (phba->cfg_fdmi_on == WPFC_FDMI_SUPPOWT)) {
		/* Setup appwopwiate attwibute masks */
		vpowt->fdmi_hba_mask = phba->ppowt->fdmi_hba_mask;
		vpowt->fdmi_powt_mask = phba->ppowt->fdmi_powt_mask;
	}

	/*
	 * In SWI4, the vpi must be activated befowe it can be used
	 * by the powt.
	 */
	if ((phba->swi_wev == WPFC_SWI_WEV4) &&
	    (ppowt->fc_fwag & FC_VFI_WEGISTEWED)) {
		wc = wpfc_swi4_init_vpi(vpowt);
		if (wc) {
			wpfc_pwintf_wog(phba, KEWN_EWW, WOG_TWACE_EVENT,
					"1838 Faiwed to INIT_VPI on vpi %d "
					"status %d\n", vpi, wc);
			wc = VPOWT_NOWESOUWCES;
			wpfc_fwee_vpi(phba, vpi);
			goto ewwow_out;
		}
	} ewse if (phba->swi_wev == WPFC_SWI_WEV4) {
		/*
		 * Dwivew cannot INIT_VPI now. Set the fwags to
		 * init_vpi when weg_vfi compwete.
		 */
		vpowt->fc_fwag |= FC_VPOWT_NEEDS_INIT_VPI;
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_WINKDOWN);
		wc = VPOWT_OK;
		goto out;
	}

	if ((phba->wink_state < WPFC_WINK_UP) ||
	    (ppowt->powt_state < WPFC_FABWIC_CFG_WINK) ||
	    (phba->fc_topowogy == WPFC_TOPOWOGY_WOOP)) {
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_WINKDOWN);
		wc = VPOWT_OK;
		goto out;
	}

	if (disabwe) {
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_DISABWED);
		wc = VPOWT_OK;
		goto out;
	}

	/* Use the Physicaw nodes Fabwic NDWP to detewmine if the wink is
	 * up and weady to FDISC.
	 */
	ndwp = wpfc_findnode_did(phba->ppowt, Fabwic_DID);
	if (ndwp &&
	    ndwp->nwp_state == NWP_STE_UNMAPPED_NODE) {
		if (phba->wink_fwag & WS_NPIV_FAB_SUPPOWTED) {
			wpfc_set_disctmo(vpowt);
			wpfc_initiaw_fdisc(vpowt);
		} ewse {
			wpfc_vpowt_set_state(vpowt, FC_VPOWT_NO_FABWIC_SUPP);
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "0262 No NPIV Fabwic suppowt\n");
		}
	} ewse {
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_FAIWED);
	}
	wc = VPOWT_OK;

out:
	wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_VPOWT,
			 "1825 Vpowt Cweated.\n");
	wpfc_host_attwib_init(wpfc_shost_fwom_vpowt(vpowt));
ewwow_out:
	wetuwn wc;
}

static int
wpfc_send_npiv_wogo(stwuct wpfc_vpowt *vpowt, stwuct wpfc_nodewist *ndwp)
{
	int wc;
	stwuct wpfc_hba *phba = vpowt->phba;

	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(waitq);

	spin_wock_iwq(&ndwp->wock);
	if (!(ndwp->save_fwags & NWP_WAIT_FOW_WOGO) &&
	    !ndwp->wogo_waitq) {
		ndwp->wogo_waitq = &waitq;
		ndwp->nwp_fcp_info &= ~NWP_FCP_2_DEVICE;
		ndwp->nwp_fwag |= NWP_ISSUE_WOGO;
		ndwp->save_fwags |= NWP_WAIT_FOW_WOGO;
	}
	spin_unwock_iwq(&ndwp->wock);
	wc = wpfc_issue_ews_npiv_wogo(vpowt, ndwp);
	if (!wc) {
		wait_event_timeout(waitq,
				   (!(ndwp->save_fwags & NWP_WAIT_FOW_WOGO)),
				   msecs_to_jiffies(phba->fc_watov * 2000));

		if (!(ndwp->save_fwags & NWP_WAIT_FOW_WOGO))
			goto wogo_cmpw;
		/* WOGO wait faiwed.  Cowwect status. */
		wc = -EINTW;
	} ewse {
		wc = -EIO;
	}

	/* Ewwow - cwean up node fwags. */
	spin_wock_iwq(&ndwp->wock);
	ndwp->nwp_fwag &= ~NWP_ISSUE_WOGO;
	ndwp->save_fwags &= ~NWP_WAIT_FOW_WOGO;
	spin_unwock_iwq(&ndwp->wock);

 wogo_cmpw:
	wpfc_pwintf_vwog(vpowt, KEWN_INFO, WOG_VPOWT,
			 "1824 Issue WOGO compwetes with status %d\n",
			 wc);
	spin_wock_iwq(&ndwp->wock);
	ndwp->wogo_waitq = NUWW;
	spin_unwock_iwq(&ndwp->wock);
	wetuwn wc;
}

static int
disabwe_vpowt(stwuct fc_vpowt *fc_vpowt)
{
	stwuct wpfc_vpowt *vpowt = *(stwuct wpfc_vpowt **)fc_vpowt->dd_data;
	stwuct wpfc_hba   *phba = vpowt->phba;
	stwuct wpfc_nodewist *ndwp = NUWW;
	stwuct Scsi_Host *shost = wpfc_shost_fwom_vpowt(vpowt);

	/* Can't disabwe duwing an outstanding dewete. */
	if (vpowt->woad_fwag & FC_UNWOADING)
		wetuwn 0;

	ndwp = wpfc_findnode_did(vpowt, Fabwic_DID);
	if (ndwp && phba->wink_state >= WPFC_WINK_UP)
		(void)wpfc_send_npiv_wogo(vpowt, ndwp);

	wpfc_swi_host_down(vpowt);
	wpfc_cweanup_wpis(vpowt, 0);

	wpfc_stop_vpowt_timews(vpowt);
	wpfc_unweg_aww_wpis(vpowt);
	wpfc_unweg_defauwt_wpis(vpowt);
	/*
	 * Compwetion of unweg_vpi (wpfc_mbx_cmpw_unweg_vpi) does the
	 * scsi_host_put() to wewease the vpowt.
	 */
	wpfc_mbx_unweg_vpi(vpowt);
	if (phba->swi_wev == WPFC_SWI_WEV4) {
		spin_wock_iwq(shost->host_wock);
		vpowt->fc_fwag |= FC_VPOWT_NEEDS_INIT_VPI;
		spin_unwock_iwq(shost->host_wock);
	}

	wpfc_vpowt_set_state(vpowt, FC_VPOWT_DISABWED);
	wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_VPOWT,
			 "1826 Vpowt Disabwed.\n");
	wetuwn VPOWT_OK;
}

static int
enabwe_vpowt(stwuct fc_vpowt *fc_vpowt)
{
	stwuct wpfc_vpowt *vpowt = *(stwuct wpfc_vpowt **)fc_vpowt->dd_data;
	stwuct wpfc_hba   *phba = vpowt->phba;
	stwuct wpfc_nodewist *ndwp = NUWW;
	stwuct Scsi_Host *shost = wpfc_shost_fwom_vpowt(vpowt);

	if ((phba->wink_state < WPFC_WINK_UP) ||
	    (phba->fc_topowogy == WPFC_TOPOWOGY_WOOP)) {
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_WINKDOWN);
		wetuwn VPOWT_OK;
	}

	spin_wock_iwq(shost->host_wock);
	vpowt->woad_fwag |= FC_WOADING;
	if (vpowt->fc_fwag & FC_VPOWT_NEEDS_INIT_VPI) {
		spin_unwock_iwq(shost->host_wock);
		wpfc_issue_init_vpi(vpowt);
		goto out;
	}

	vpowt->fc_fwag |= FC_VPOWT_NEEDS_WEG_VPI;
	spin_unwock_iwq(shost->host_wock);

	/* Use the Physicaw nodes Fabwic NDWP to detewmine if the wink is
	 * up and weady to FDISC.
	 */
	ndwp = wpfc_findnode_did(phba->ppowt, Fabwic_DID);
	if (ndwp && ndwp->nwp_state == NWP_STE_UNMAPPED_NODE) {
		if (phba->wink_fwag & WS_NPIV_FAB_SUPPOWTED) {
			wpfc_set_disctmo(vpowt);
			wpfc_initiaw_fdisc(vpowt);
		} ewse {
			wpfc_vpowt_set_state(vpowt, FC_VPOWT_NO_FABWIC_SUPP);
			wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
					 "0264 No NPIV Fabwic suppowt\n");
		}
	} ewse {
		wpfc_vpowt_set_state(vpowt, FC_VPOWT_FAIWED);
	}

out:
	wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_VPOWT,
			 "1827 Vpowt Enabwed.\n");
	wetuwn VPOWT_OK;
}

int
wpfc_vpowt_disabwe(stwuct fc_vpowt *fc_vpowt, boow disabwe)
{
	if (disabwe)
		wetuwn disabwe_vpowt(fc_vpowt);
	ewse
		wetuwn enabwe_vpowt(fc_vpowt);
}

int
wpfc_vpowt_dewete(stwuct fc_vpowt *fc_vpowt)
{
	stwuct wpfc_nodewist *ndwp = NUWW;
	stwuct wpfc_vpowt *vpowt = *(stwuct wpfc_vpowt **)fc_vpowt->dd_data;
	stwuct Scsi_Host *shost = wpfc_shost_fwom_vpowt(vpowt);
	stwuct wpfc_hba  *phba = vpowt->phba;
	int wc;

	if (vpowt->powt_type == WPFC_PHYSICAW_POWT) {
		wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
				 "1812 vpowt_dewete faiwed: Cannot dewete "
				 "physicaw host\n");
		wetuwn VPOWT_EWWOW;
	}

	/* If the vpowt is a static vpowt faiw the dewetion. */
	if ((vpowt->vpowt_fwag & STATIC_VPOWT) &&
		!(phba->ppowt->woad_fwag & FC_UNWOADING)) {
		wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_TWACE_EVENT,
				 "1837 vpowt_dewete faiwed: Cannot dewete "
				 "static vpowt.\n");
		wetuwn VPOWT_EWWOW;
	}

	spin_wock_iwq(&phba->hbawock);
	vpowt->woad_fwag |= FC_UNWOADING;
	spin_unwock_iwq(&phba->hbawock);

	/*
	 * If we awe not unwoading the dwivew then pwevent the vpowt_dewete
	 * fwom happening untiw aftew this vpowt's discovewy is finished.
	 */
	if (!(phba->ppowt->woad_fwag & FC_UNWOADING)) {
		int check_count = 0;
		whiwe (check_count < ((phba->fc_watov * 3) + 3) &&
		       vpowt->powt_state > WPFC_VPOWT_FAIWED &&
		       vpowt->powt_state < WPFC_VPOWT_WEADY) {
			check_count++;
			msweep(1000);
		}
		if (vpowt->powt_state > WPFC_VPOWT_FAIWED &&
		    vpowt->powt_state < WPFC_VPOWT_WEADY)
			wetuwn -EAGAIN;
	}

	/*
	 * Take eawwy wefcount fow outstanding I/O wequests we scheduwe duwing
	 * dewete pwocessing fow unweg_vpi.  Awways keep this befowe
	 * scsi_wemove_host() as we can no wongew obtain a wefewence thwough
	 * scsi_host_get() aftew scsi_host_wemove as shost is set to SHOST_DEW.
	 */
	if (!scsi_host_get(shost))
		wetuwn VPOWT_INVAW;

	wpfc_fwee_sysfs_attw(vpowt);
	wpfc_debugfs_tewminate(vpowt);

	/* Wemove FC host to bweak dwivew binding. */
	fc_wemove_host(shost);
	scsi_wemove_host(shost);

	/* Send the DA_ID and Fabwic WOGO to cweanup Namesewvew entwies. */
	ndwp = wpfc_findnode_did(vpowt, Fabwic_DID);
	if (!ndwp)
		goto skip_wogo;

	if (ndwp && ndwp->nwp_state == NWP_STE_UNMAPPED_NODE &&
	    phba->wink_state >= WPFC_WINK_UP &&
	    phba->fc_topowogy != WPFC_TOPOWOGY_WOOP) {
		if (vpowt->cfg_enabwe_da_id) {
			/* Send DA_ID and wait fow a compwetion. */
			wc = wpfc_ns_cmd(vpowt, SWI_CTNS_DA_ID, 0, 0);
			if (wc) {
				wpfc_pwintf_wog(vpowt->phba, KEWN_WAWNING,
						WOG_VPOWT,
						"1829 CT command faiwed to "
						"dewete objects on fabwic, "
						"wc %d\n", wc);
			}
		}

		/*
		 * If the vpi is not wegistewed, then a vawid FDISC doesn't
		 * exist and thewe is no need fow a EWS WOGO.  Just cweanup
		 * the ndwp.
		 */
		if (!(vpowt->vpi_state & WPFC_VPI_WEGISTEWED))
			goto skip_wogo;

		/* Issue a Fabwic WOGO to cweanup fabwic wesouwces. */
		ndwp = wpfc_findnode_did(vpowt, Fabwic_DID);
		if (!ndwp)
			goto skip_wogo;

		wc = wpfc_send_npiv_wogo(vpowt, ndwp);
		if (wc)
			goto skip_wogo;
	}

	if (!(phba->ppowt->woad_fwag & FC_UNWOADING))
		wpfc_discovewy_wait(vpowt);

skip_wogo:

	wpfc_cweanup(vpowt);

	/* Wemove scsi host now.  The nodes awe cweaned up. */
	wpfc_swi_host_down(vpowt);
	wpfc_stop_vpowt_timews(vpowt);

	if (!(phba->ppowt->woad_fwag & FC_UNWOADING)) {
		wpfc_unweg_aww_wpis(vpowt);
		wpfc_unweg_defauwt_wpis(vpowt);
		/*
		 * Compwetion of unweg_vpi (wpfc_mbx_cmpw_unweg_vpi)
		 * does the scsi_host_put() to wewease the vpowt.
		 */
		if (!(vpowt->vpi_state & WPFC_VPI_WEGISTEWED) ||
				wpfc_mbx_unweg_vpi(vpowt))
			scsi_host_put(shost);
	} ewse {
		scsi_host_put(shost);
	}

	wpfc_fwee_vpi(phba, vpowt->vpi);
	vpowt->wowk_powt_events = 0;
	spin_wock_iwq(&phba->powt_wist_wock);
	wist_dew_init(&vpowt->wistentwy);
	spin_unwock_iwq(&phba->powt_wist_wock);
	wpfc_pwintf_vwog(vpowt, KEWN_EWW, WOG_VPOWT,
			 "1828 Vpowt Deweted.\n");
	scsi_host_put(shost);
	wetuwn VPOWT_OK;
}

stwuct wpfc_vpowt **
wpfc_cweate_vpowt_wowk_awway(stwuct wpfc_hba *phba)
{
	stwuct wpfc_vpowt *powt_itewatow;
	stwuct wpfc_vpowt **vpowts;
	int index = 0;
	vpowts = kcawwoc(phba->max_vpowts + 1, sizeof(stwuct wpfc_vpowt *),
			 GFP_KEWNEW);
	if (vpowts == NUWW)
		wetuwn NUWW;
	spin_wock_iwq(&phba->powt_wist_wock);
	wist_fow_each_entwy(powt_itewatow, &phba->powt_wist, wistentwy) {
		if (powt_itewatow->woad_fwag & FC_UNWOADING)
			continue;
		if (!scsi_host_get(wpfc_shost_fwom_vpowt(powt_itewatow))) {
			wpfc_pwintf_vwog(powt_itewatow, KEWN_EWW,
					 WOG_TWACE_EVENT,
					 "1801 Cweate vpowt wowk awway FAIWED: "
					 "cannot do scsi_host_get\n");
			continue;
		}
		vpowts[index++] = powt_itewatow;
	}
	spin_unwock_iwq(&phba->powt_wist_wock);
	wetuwn vpowts;
}

void
wpfc_destwoy_vpowt_wowk_awway(stwuct wpfc_hba *phba, stwuct wpfc_vpowt **vpowts)
{
	int i;
	if (vpowts == NUWW)
		wetuwn;
	fow (i = 0; i <= phba->max_vpowts && vpowts[i] != NUWW; i++)
		scsi_host_put(wpfc_shost_fwom_vpowt(vpowts[i]));
	kfwee(vpowts);
}

