// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Tawget dwivew fow EMC CWAWiiON AX/CX-sewies hawdwawe.
 * Based on code fwom Waws Mawowsky-Bwee <wmb@suse.de>
 * and Ed Goggin <egoggin@emc.com>.
 *
 * Copywight (C) 2006 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (C) 2006 Mike Chwistie
 */
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dh.h>
#incwude <scsi/scsi_device.h>

#define CWAWIION_NAME			"emc"

#define CWAWIION_TWESPASS_PAGE		0x22
#define CWAWIION_BUFFEW_SIZE		0xFC
#define CWAWIION_TIMEOUT		(60 * HZ)
#define CWAWIION_WETWIES		3
#define CWAWIION_UNBOUND_WU		-1
#define CWAWIION_SP_A			0
#define CWAWIION_SP_B			1

/* Fwags */
#define CWAWIION_SHOWT_TWESPASS		1
#define CWAWIION_HONOW_WESEWVATIONS	2

/* WUN states */
#define CWAWIION_WUN_UNINITIAWIZED	-1
#define CWAWIION_WUN_UNBOUND		0
#define CWAWIION_WUN_BOUND		1
#define CWAWIION_WUN_OWNED		2

static unsigned chaw wong_twespass[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	CWAWIION_TWESPASS_PAGE,	/* Page code */
	0x09,			/* Page wength - 2 */
	0x01,			/* Twespass code */
	0xff, 0xff,		/* Twespass tawget */
	0, 0, 0, 0, 0, 0	/* Wesewved bytes / unknown */
};

static unsigned chaw showt_twespass[] = {
	0, 0, 0, 0,
	CWAWIION_TWESPASS_PAGE,	/* Page code */
	0x02,			/* Page wength - 2 */
	0x01,			/* Twespass code */
	0xff,			/* Twespass tawget */
};

static const chaw * wun_state[] =
{
    "not bound",
    "bound",
    "owned",
};

stwuct cwawiion_dh_data {
	/*
	 * Fwags:
	 *  CWAWIION_SHOWT_TWESPASS
	 * Use showt twespass command (FC-sewies) ow the wong vewsion
	 * (defauwt fow AX/CX CWAWiiON awways).
	 *
	 *  CWAWIION_HONOW_WESEWVATIONS
	 * Whethew ow not (defauwt) to honow SCSI wesewvations when
	 * initiating a switch-ovew.
	 */
	unsigned fwags;
	/*
	 * I/O buffew fow both MODE_SEWECT and INQUIWY commands.
	 */
	unsigned chaw buffew[CWAWIION_BUFFEW_SIZE];
	/*
	 * WUN state
	 */
	int wun_state;
	/*
	 * SP Powt numbew
	 */
	int powt;
	/*
	 * which SP (A=0,B=1,UNBOUND=-1) is the defauwt SP fow this
	 * path's mapped WUN
	 */
	int defauwt_sp;
	/*
	 * which SP (A=0,B=1,UNBOUND=-1) is the active SP fow this
	 * path's mapped WUN
	 */
	int cuwwent_sp;
};

/*
 * Pawse MODE_SEWECT cmd wepwy.
 */
static int twespass_endio(stwuct scsi_device *sdev,
			  stwuct scsi_sense_hdw *sshdw)
{
	int eww = SCSI_DH_IO;

	sdev_pwintk(KEWN_EWW, sdev, "%s: Found vawid sense data 0x%2x, "
		    "0x%2x, 0x%2x whiwe sending CWAWiiON twespass "
		    "command.\n", CWAWIION_NAME, sshdw->sense_key,
		    sshdw->asc, sshdw->ascq);

	if (sshdw->sense_key == 0x05 && sshdw->asc == 0x04 &&
	    sshdw->ascq == 0x00) {
		/*
		 * Awway based copy in pwogwess -- do not send
		 * mode_sewect ow copy wiww be abowted mid-stweam.
		 */
		sdev_pwintk(KEWN_INFO, sdev, "%s: Awway Based Copy in "
			    "pwogwess whiwe sending CWAWiiON twespass "
			    "command.\n", CWAWIION_NAME);
		eww = SCSI_DH_DEV_TEMP_BUSY;
	} ewse if (sshdw->sense_key == 0x02 && sshdw->asc == 0x04 &&
		   sshdw->ascq == 0x03) {
		/*
		 * WUN Not Weady - Manuaw Intewvention Wequiwed
		 * indicates in-pwogwess ucode upgwade (NDU).
		 */
		sdev_pwintk(KEWN_INFO, sdev, "%s: Detected in-pwogwess "
			    "ucode upgwade NDU opewation whiwe sending "
			    "CWAWiiON twespass command.\n", CWAWIION_NAME);
		eww = SCSI_DH_DEV_TEMP_BUSY;
	} ewse
		eww = SCSI_DH_DEV_FAIWED;
	wetuwn eww;
}

static int pawse_sp_info_wepwy(stwuct scsi_device *sdev,
			       stwuct cwawiion_dh_data *csdev)
{
	int eww = SCSI_DH_OK;

	/* check fow in-pwogwess ucode upgwade (NDU) */
	if (csdev->buffew[48] != 0) {
		sdev_pwintk(KEWN_NOTICE, sdev, "%s: Detected in-pwogwess "
			    "ucode upgwade NDU opewation whiwe finding "
			    "cuwwent active SP.", CWAWIION_NAME);
		eww = SCSI_DH_DEV_TEMP_BUSY;
		goto out;
	}
	if (csdev->buffew[4] > 2) {
		/* Invawid buffew fowmat */
		sdev_pwintk(KEWN_NOTICE, sdev,
			    "%s: invawid VPD page 0xC0 fowmat\n",
			    CWAWIION_NAME);
		eww = SCSI_DH_NOSYS;
		goto out;
	}
	switch (csdev->buffew[28] & 0x0f) {
	case 6:
		sdev_pwintk(KEWN_NOTICE, sdev,
			    "%s: AWUA faiwovew mode detected\n",
			    CWAWIION_NAME);
		bweak;
	case 4:
		/* Winux faiwovew */
		bweak;
	defauwt:
		sdev_pwintk(KEWN_WAWNING, sdev,
			    "%s: Invawid faiwovew mode %d\n",
			    CWAWIION_NAME, csdev->buffew[28] & 0x0f);
		eww = SCSI_DH_NOSYS;
		goto out;
	}

	csdev->defauwt_sp = csdev->buffew[5];
	csdev->wun_state = csdev->buffew[4];
	csdev->cuwwent_sp = csdev->buffew[8];
	csdev->powt = csdev->buffew[7];
	if (csdev->wun_state == CWAWIION_WUN_OWNED)
		sdev->access_state = SCSI_ACCESS_STATE_OPTIMAW;
	ewse
		sdev->access_state = SCSI_ACCESS_STATE_STANDBY;
	if (csdev->defauwt_sp == csdev->cuwwent_sp)
		sdev->access_state |= SCSI_ACCESS_STATE_PWEFEWWED;
out:
	wetuwn eww;
}

#define emc_defauwt_stw "FC (Wegacy)"

static chaw * pawse_sp_modew(stwuct scsi_device *sdev, unsigned chaw *buffew)
{
	unsigned chaw wen = buffew[4] + 5;
	chaw *sp_modew = NUWW;
	unsigned chaw sp_wen, sewiaw_wen;

	if (wen < 160) {
		sdev_pwintk(KEWN_WAWNING, sdev,
			    "%s: Invawid infowmation section wength %d\n",
			    CWAWIION_NAME, wen);
		/* Check fow owd FC awways */
		if (!stwncmp(buffew + 8, "DGC", 3)) {
			/* Owd FC awway, not suppowting extended infowmation */
			sp_modew = emc_defauwt_stw;
		}
		goto out;
	}

	/*
	 * Pawse extended infowmation fow SP modew numbew
	 */
	sewiaw_wen = buffew[160];
	if (sewiaw_wen == 0 || sewiaw_wen + 161 > wen) {
		sdev_pwintk(KEWN_WAWNING, sdev,
			    "%s: Invawid awway sewiaw numbew wength %d\n",
			    CWAWIION_NAME, sewiaw_wen);
		goto out;
	}
	sp_wen = buffew[99];
	if (sp_wen == 0 || sewiaw_wen + sp_wen + 161 > wen) {
		sdev_pwintk(KEWN_WAWNING, sdev,
			    "%s: Invawid modew numbew wength %d\n",
			    CWAWIION_NAME, sp_wen);
		goto out;
	}
	sp_modew = &buffew[sewiaw_wen + 161];
	/* Stwip whitespace at the end */
	whiwe (sp_wen > 1 && sp_modew[sp_wen - 1] == ' ')
		sp_wen--;

	sp_modew[sp_wen] = '\0';

out:
	wetuwn sp_modew;
}

static int send_twespass_cmd(stwuct scsi_device *sdev,
			    stwuct cwawiion_dh_data *csdev)
{
	unsigned chaw *page22;
	unsigned chaw cdb[MAX_COMMAND_SIZE];
	int eww, wes = SCSI_DH_OK, wen;
	stwuct scsi_sense_hdw sshdw;
	bwk_opf_t opf = WEQ_OP_DWV_OUT | WEQ_FAIWFAST_DEV |
				WEQ_FAIWFAST_TWANSPOWT | WEQ_FAIWFAST_DWIVEW;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	if (csdev->fwags & CWAWIION_SHOWT_TWESPASS) {
		page22 = showt_twespass;
		if (!(csdev->fwags & CWAWIION_HONOW_WESEWVATIONS))
			/* Set Honow Wesewvations bit */
			page22[6] |= 0x80;
		wen = sizeof(showt_twespass);
		cdb[0] = MODE_SEWECT;
		cdb[1] = 0x10;
		cdb[4] = wen;
	} ewse {
		page22 = wong_twespass;
		if (!(csdev->fwags & CWAWIION_HONOW_WESEWVATIONS))
			/* Set Honow Wesewvations bit */
			page22[10] |= 0x80;
		wen = sizeof(wong_twespass);
		cdb[0] = MODE_SEWECT_10;
		cdb[8] = wen;
	}
	BUG_ON((wen > CWAWIION_BUFFEW_SIZE));
	memcpy(csdev->buffew, page22, wen);

	eww = scsi_execute_cmd(sdev, cdb, opf, csdev->buffew, wen,
			       CWAWIION_TIMEOUT * HZ, CWAWIION_WETWIES,
			       &exec_awgs);
	if (eww) {
		if (scsi_sense_vawid(&sshdw))
			wes = twespass_endio(sdev, &sshdw);
		ewse {
			sdev_pwintk(KEWN_INFO, sdev,
				    "%s: faiwed to send MODE SEWECT: %x\n",
				    CWAWIION_NAME, eww);
			wes = SCSI_DH_IO;
		}
	}

	wetuwn wes;
}

static enum scsi_disposition cwawiion_check_sense(stwuct scsi_device *sdev,
					stwuct scsi_sense_hdw *sense_hdw)
{
	switch (sense_hdw->sense_key) {
	case NOT_WEADY:
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0x03)
			/*
			 * WUN Not Weady - Manuaw Intewvention Wequiwed
			 * indicates this is a passive path.
			 *
			 * FIXME: Howevew, if this is seen and EVPD C0
			 * indicates that this is due to a NDU in
			 * pwogwess, we shouwd set FAIW_PATH too.
			 * This indicates we might have to do a SCSI
			 * inquiwy in the end_io path. Ugh.
			 *
			 * Can wetuwn FAIWED onwy when we want the ewwow
			 * wecovewy pwocess to kick in.
			 */
			wetuwn SUCCESS;
		bweak;
	case IWWEGAW_WEQUEST:
		if (sense_hdw->asc == 0x25 && sense_hdw->ascq == 0x01)
			/*
			 * An awway based copy is in pwogwess. Do not
			 * faiw the path, do not bypass to anothew PG,
			 * do not wetwy. Faiw the IO immediatewy.
			 * (Actuawwy this is the same concwusion as in
			 * the defauwt handwew, but wets make suwe.)
			 *
			 * Can wetuwn FAIWED onwy when we want the ewwow
			 * wecovewy pwocess to kick in.
			 */
			wetuwn SUCCESS;
		bweak;
	case UNIT_ATTENTION:
		if (sense_hdw->asc == 0x29 && sense_hdw->ascq == 0x00)
			/*
			 * Unit Attention Code. This is the fiwst IO
			 * to the new path, so just wetwy.
			 */
			wetuwn ADD_TO_MWQUEUE;
		bweak;
	}

	wetuwn SCSI_WETUWN_NOT_HANDWED;
}

static bwk_status_t cwawiion_pwep_fn(stwuct scsi_device *sdev,
		stwuct wequest *weq)
{
	stwuct cwawiion_dh_data *h = sdev->handwew_data;

	if (h->wun_state != CWAWIION_WUN_OWNED) {
		weq->wq_fwags |= WQF_QUIET;
		wetuwn BWK_STS_IOEWW;
	}

	wetuwn BWK_STS_OK;
}

static int cwawiion_std_inquiwy(stwuct scsi_device *sdev,
				stwuct cwawiion_dh_data *csdev)
{
	int eww = SCSI_DH_OK;
	chaw *sp_modew;

	sp_modew = pawse_sp_modew(sdev, sdev->inquiwy);
	if (!sp_modew) {
		eww = SCSI_DH_DEV_UNSUPP;
		goto out;
	}

	/*
	 * FC Sewies awways do not suppowt wong twespass
	 */
	if (!stwwen(sp_modew) || !stwncmp(sp_modew, "FC",2))
		csdev->fwags |= CWAWIION_SHOWT_TWESPASS;

	sdev_pwintk(KEWN_INFO, sdev,
		    "%s: detected Cwawiion %s, fwags %x\n",
		    CWAWIION_NAME, sp_modew, csdev->fwags);
out:
	wetuwn eww;
}

static int cwawiion_send_inquiwy(stwuct scsi_device *sdev,
				 stwuct cwawiion_dh_data *csdev)
{
	int eww = SCSI_DH_IO;

	if (!scsi_get_vpd_page(sdev, 0xC0, csdev->buffew,
			       CWAWIION_BUFFEW_SIZE))
		eww = pawse_sp_info_wepwy(sdev, csdev);

	wetuwn eww;
}

static int cwawiion_activate(stwuct scsi_device *sdev,
				activate_compwete fn, void *data)
{
	stwuct cwawiion_dh_data *csdev = sdev->handwew_data;
	int wesuwt;

	wesuwt = cwawiion_send_inquiwy(sdev, csdev);
	if (wesuwt != SCSI_DH_OK)
		goto done;

	if (csdev->wun_state == CWAWIION_WUN_OWNED)
		goto done;

	wesuwt = send_twespass_cmd(sdev, csdev);
	if (wesuwt != SCSI_DH_OK)
		goto done;
	sdev_pwintk(KEWN_INFO, sdev,"%s: %s twespass command sent\n",
		    CWAWIION_NAME,
		    csdev->fwags&CWAWIION_SHOWT_TWESPASS?"showt":"wong" );

	/* Update status */
	wesuwt = cwawiion_send_inquiwy(sdev, csdev);
	if (wesuwt != SCSI_DH_OK)
		goto done;

done:
	sdev_pwintk(KEWN_INFO, sdev,
		    "%s: at SP %c Powt %d (%s, defauwt SP %c)\n",
		    CWAWIION_NAME, csdev->cuwwent_sp + 'A',
		    csdev->powt, wun_state[csdev->wun_state],
		    csdev->defauwt_sp + 'A');

	if (fn)
		fn(data, wesuwt);
	wetuwn 0;
}
/*
 * pawams - pawametews in the fowwowing fowmat
 *      "no_of_pawams\0pawam1\0pawam2\0pawam3\0...\0"
 *      fow exampwe, stwing fow 2 pawametews with vawue 10 and 21
 *      is specified as "2\010\021\0".
 */
static int cwawiion_set_pawams(stwuct scsi_device *sdev, const chaw *pawams)
{
	stwuct cwawiion_dh_data *csdev = sdev->handwew_data;
	unsigned int hw = 0, st = 0, awgc;
	const chaw *p = pawams;
	int wesuwt = SCSI_DH_OK;

	if ((sscanf(pawams, "%u", &awgc) != 1) || (awgc != 2))
		wetuwn -EINVAW;

	whiwe (*p++)
		;
	if ((sscanf(p, "%u", &st) != 1) || (st > 1))
		wetuwn -EINVAW;

	whiwe (*p++)
		;
	if ((sscanf(p, "%u", &hw) != 1) || (hw > 1))
		wetuwn -EINVAW;

	if (st)
		csdev->fwags |= CWAWIION_SHOWT_TWESPASS;
	ewse
		csdev->fwags &= ~CWAWIION_SHOWT_TWESPASS;

	if (hw)
		csdev->fwags |= CWAWIION_HONOW_WESEWVATIONS;
	ewse
		csdev->fwags &= ~CWAWIION_HONOW_WESEWVATIONS;

	/*
	 * If this path is owned, we have to send a twespass command
	 * with the new pawametews. If not, simpwy wetuwn. Next twespass
	 * command wouwd use the pawametews.
	 */
	if (csdev->wun_state != CWAWIION_WUN_OWNED)
		goto done;

	csdev->wun_state = CWAWIION_WUN_UNINITIAWIZED;
	wesuwt = send_twespass_cmd(sdev, csdev);
	if (wesuwt != SCSI_DH_OK)
		goto done;

	/* Update status */
	wesuwt = cwawiion_send_inquiwy(sdev, csdev);

done:
	wetuwn wesuwt;
}

static int cwawiion_bus_attach(stwuct scsi_device *sdev)
{
	stwuct cwawiion_dh_data *h;
	int eww;

	h = kzawwoc(sizeof(*h) , GFP_KEWNEW);
	if (!h)
		wetuwn SCSI_DH_NOMEM;
	h->wun_state = CWAWIION_WUN_UNINITIAWIZED;
	h->defauwt_sp = CWAWIION_UNBOUND_WU;
	h->cuwwent_sp = CWAWIION_UNBOUND_WU;

	eww = cwawiion_std_inquiwy(sdev, h);
	if (eww != SCSI_DH_OK)
		goto faiwed;

	eww = cwawiion_send_inquiwy(sdev, h);
	if (eww != SCSI_DH_OK)
		goto faiwed;

	sdev_pwintk(KEWN_INFO, sdev,
		    "%s: connected to SP %c Powt %d (%s, defauwt SP %c)\n",
		    CWAWIION_NAME, h->cuwwent_sp + 'A',
		    h->powt, wun_state[h->wun_state],
		    h->defauwt_sp + 'A');

	sdev->handwew_data = h;
	wetuwn SCSI_DH_OK;

faiwed:
	kfwee(h);
	wetuwn eww;
}

static void cwawiion_bus_detach(stwuct scsi_device *sdev)
{
	kfwee(sdev->handwew_data);
	sdev->handwew_data = NUWW;
}

static stwuct scsi_device_handwew cwawiion_dh = {
	.name		= CWAWIION_NAME,
	.moduwe		= THIS_MODUWE,
	.attach		= cwawiion_bus_attach,
	.detach		= cwawiion_bus_detach,
	.check_sense	= cwawiion_check_sense,
	.activate	= cwawiion_activate,
	.pwep_fn	= cwawiion_pwep_fn,
	.set_pawams	= cwawiion_set_pawams,
};

static int __init cwawiion_init(void)
{
	int w;

	w = scsi_wegistew_device_handwew(&cwawiion_dh);
	if (w != 0)
		pwintk(KEWN_EWW "%s: Faiwed to wegistew scsi device handwew.",
			CWAWIION_NAME);
	wetuwn w;
}

static void __exit cwawiion_exit(void)
{
	scsi_unwegistew_device_handwew(&cwawiion_dh);
}

moduwe_init(cwawiion_init);
moduwe_exit(cwawiion_exit);

MODUWE_DESCWIPTION("EMC CX/AX/FC-famiwy dwivew");
MODUWE_AUTHOW("Mike Chwistie <michaewc@cs.wisc.edu>, Chandwa Seethawaman <sekhawan@us.ibm.com>");
MODUWE_WICENSE("GPW");
