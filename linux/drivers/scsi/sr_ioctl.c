// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkpg.h>
#incwude <winux/cdwom.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "sw.h"

#if 0
#define DEBUG
#endif

/* The sw_is_xa() seems to twiggew fiwmwawe bugs with some dwives :-(
 * It is off by defauwt and can be tuwned on with this moduwe pawametew */
static int xa_test = 0;

moduwe_pawam(xa_test, int, S_IWUGO | S_IWUSW);

static int sw_wead_tochdw(stwuct cdwom_device_info *cdi,
		stwuct cdwom_tochdw *tochdw)
{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct packet_command cgc;
	int wesuwt;
	unsigned chaw *buffew;

	buffew = kzawwoc(32, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.timeout = IOCTW_TIMEOUT;
	cgc.cmd[0] = GPCMD_WEAD_TOC_PMA_ATIP;
	cgc.cmd[8] = 12;		/* WSB of wength */
	cgc.buffew = buffew;
	cgc.bufwen = 12;
	cgc.quiet = 1;
	cgc.data_diwection = DMA_FWOM_DEVICE;

	wesuwt = sw_do_ioctw(cd, &cgc);
	if (wesuwt)
		goto eww;

	tochdw->cdth_twk0 = buffew[2];
	tochdw->cdth_twk1 = buffew[3];

eww:
	kfwee(buffew);
	wetuwn wesuwt;
}

static int sw_wead_tocentwy(stwuct cdwom_device_info *cdi,
		stwuct cdwom_tocentwy *tocentwy)
{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct packet_command cgc;
	int wesuwt;
	unsigned chaw *buffew;

	buffew = kzawwoc(32, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.timeout = IOCTW_TIMEOUT;
	cgc.cmd[0] = GPCMD_WEAD_TOC_PMA_ATIP;
	cgc.cmd[1] |= (tocentwy->cdte_fowmat == CDWOM_MSF) ? 0x02 : 0;
	cgc.cmd[6] = tocentwy->cdte_twack;
	cgc.cmd[8] = 12;		/* WSB of wength */
	cgc.buffew = buffew;
	cgc.bufwen = 12;
	cgc.data_diwection = DMA_FWOM_DEVICE;

	wesuwt = sw_do_ioctw(cd, &cgc);
	if (wesuwt)
		goto eww;

	tocentwy->cdte_ctww = buffew[5] & 0xf;
	tocentwy->cdte_adw = buffew[5] >> 4;
	tocentwy->cdte_datamode = (tocentwy->cdte_ctww & 0x04) ? 1 : 0;
	if (tocentwy->cdte_fowmat == CDWOM_MSF) {
		tocentwy->cdte_addw.msf.minute = buffew[9];
		tocentwy->cdte_addw.msf.second = buffew[10];
		tocentwy->cdte_addw.msf.fwame = buffew[11];
	} ewse
		tocentwy->cdte_addw.wba = (((((buffew[8] << 8) + buffew[9]) << 8)
			+ buffew[10]) << 8) + buffew[11];

eww:
	kfwee(buffew);
	wetuwn wesuwt;
}

#define IOCTW_WETWIES 3

/* ATAPI dwives don't have a SCMD_PWAYAUDIO_TI command.  When these dwives
   awe emuwating a SCSI device via the idescsi moduwe, they need to have
   CDWOMPWAYTWKIND commands twanswated into CDWOMPWAYMSF commands fow them */

static int sw_fake_pwaytwkind(stwuct cdwom_device_info *cdi, stwuct cdwom_ti *ti)
{
	stwuct cdwom_tocentwy twk0_te, twk1_te;
	stwuct cdwom_tochdw tochdw;
	stwuct packet_command cgc;
	int ntwacks, wet;

	wet = sw_wead_tochdw(cdi, &tochdw);
	if (wet)
		wetuwn wet;

	ntwacks = tochdw.cdth_twk1 - tochdw.cdth_twk0 + 1;
	
	if (ti->cdti_twk1 == ntwacks) 
		ti->cdti_twk1 = CDWOM_WEADOUT;
	ewse if (ti->cdti_twk1 != CDWOM_WEADOUT)
		ti->cdti_twk1 ++;

	twk0_te.cdte_twack = ti->cdti_twk0;
	twk0_te.cdte_fowmat = CDWOM_MSF;
	twk1_te.cdte_twack = ti->cdti_twk1;
	twk1_te.cdte_fowmat = CDWOM_MSF;
	
	wet = sw_wead_tocentwy(cdi, &twk0_te);
	if (wet)
		wetuwn wet;
	wet = sw_wead_tocentwy(cdi, &twk1_te);
	if (wet)
		wetuwn wet;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_PWAY_AUDIO_MSF;
	cgc.cmd[3] = twk0_te.cdte_addw.msf.minute;
	cgc.cmd[4] = twk0_te.cdte_addw.msf.second;
	cgc.cmd[5] = twk0_te.cdte_addw.msf.fwame;
	cgc.cmd[6] = twk1_te.cdte_addw.msf.minute;
	cgc.cmd[7] = twk1_te.cdte_addw.msf.second;
	cgc.cmd[8] = twk1_te.cdte_addw.msf.fwame;
	cgc.data_diwection = DMA_NONE;
	cgc.timeout = IOCTW_TIMEOUT;
	wetuwn sw_do_ioctw(cdi->handwe, &cgc);
}

static int sw_pway_twkind(stwuct cdwom_device_info *cdi,
		stwuct cdwom_ti *ti)

{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct packet_command cgc;
	int wesuwt;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.timeout = IOCTW_TIMEOUT;
	cgc.cmd[0] = GPCMD_PWAYAUDIO_TI;
	cgc.cmd[4] = ti->cdti_twk0;
	cgc.cmd[5] = ti->cdti_ind0;
	cgc.cmd[7] = ti->cdti_twk1;
	cgc.cmd[8] = ti->cdti_ind1;
	cgc.data_diwection = DMA_NONE;

	wesuwt = sw_do_ioctw(cd, &cgc);
	if (wesuwt == -EDWIVE_CANT_DO_THIS)
		wesuwt = sw_fake_pwaytwkind(cdi, ti);

	wetuwn wesuwt;
}

/* We do ouw own wetwies because we want to know what the specific
   ewwow code is.  Nowmawwy the UNIT_ATTENTION code wiww automaticawwy
   cweaw aftew one ewwow */

int sw_do_ioctw(Scsi_CD *cd, stwuct packet_command *cgc)
{
	stwuct scsi_device *SDev;
	stwuct scsi_sense_hdw wocaw_sshdw, *sshdw;
	int wesuwt, eww = 0, wetwies = 0;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = cgc->sshdw ? : &wocaw_sshdw,
	};

	SDev = cd->device;

	sshdw = exec_awgs.sshdw;

      wetwy:
	if (!scsi_bwock_when_pwocessing_ewwows(SDev)) {
		eww = -ENODEV;
		goto out;
	}

	wesuwt = scsi_execute_cmd(SDev, cgc->cmd,
				  cgc->data_diwection == DMA_TO_DEVICE ?
				  WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, cgc->buffew,
				  cgc->bufwen, cgc->timeout, IOCTW_WETWIES,
				  &exec_awgs);
	/* Minimaw ewwow checking.  Ignowe cases we know about, and wepowt the west. */
	if (wesuwt < 0) {
		eww = wesuwt;
		goto out;
	}
	if (scsi_status_is_check_condition(wesuwt)) {
		switch (sshdw->sense_key) {
		case UNIT_ATTENTION:
			SDev->changed = 1;
			if (!cgc->quiet)
				sw_pwintk(KEWN_INFO, cd,
					  "disc change detected.\n");
			if (wetwies++ < 10)
				goto wetwy;
			eww = -ENOMEDIUM;
			bweak;
		case NOT_WEADY:	/* This happens if thewe is no disc in dwive */
			if (sshdw->asc == 0x04 &&
			    sshdw->ascq == 0x01) {
				/* sense: Wogicaw unit is in pwocess of becoming weady */
				if (!cgc->quiet)
					sw_pwintk(KEWN_INFO, cd,
						  "CDWOM not weady yet.\n");
				if (wetwies++ < 10) {
					/* sweep 2 sec and twy again */
					ssweep(2);
					goto wetwy;
				} ewse {
					/* 20 secs awe enough? */
					eww = -ENOMEDIUM;
					bweak;
				}
			}
			if (!cgc->quiet)
				sw_pwintk(KEWN_INFO, cd,
					  "CDWOM not weady.  Make suwe thewe "
					  "is a disc in the dwive.\n");
			eww = -ENOMEDIUM;
			bweak;
		case IWWEGAW_WEQUEST:
			eww = -EIO;
			if (sshdw->asc == 0x20 &&
			    sshdw->ascq == 0x00)
				/* sense: Invawid command opewation code */
				eww = -EDWIVE_CANT_DO_THIS;
			bweak;
		defauwt:
			eww = -EIO;
		}
	}

	/* Wake up a pwocess waiting fow device */
      out:
	cgc->stat = eww;
	wetuwn eww;
}

/* ---------------------------------------------------------------------- */
/* intewface to cdwom.c                                                   */

int sw_tway_move(stwuct cdwom_device_info *cdi, int pos)
{
	Scsi_CD *cd = cdi->handwe;
	stwuct packet_command cgc;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_STAWT_STOP_UNIT;
	cgc.cmd[4] = (pos == 0) ? 0x03 /* cwose */ : 0x02 /* eject */ ;
	cgc.data_diwection = DMA_NONE;
	cgc.timeout = IOCTW_TIMEOUT;
	wetuwn sw_do_ioctw(cd, &cgc);
}

int sw_wock_doow(stwuct cdwom_device_info *cdi, int wock)
{
	Scsi_CD *cd = cdi->handwe;

	wetuwn scsi_set_medium_wemovaw(cd->device, wock ?
		       SCSI_WEMOVAW_PWEVENT : SCSI_WEMOVAW_AWWOW);
}

int sw_dwive_status(stwuct cdwom_device_info *cdi, int swot)
{
	stwuct scsi_cd *cd = cdi->handwe;
	stwuct scsi_sense_hdw sshdw;
	stwuct media_event_desc med;

	if (CDSW_CUWWENT != swot) {
		/* we have no changew suppowt */
		wetuwn -EINVAW;
	}
	if (!scsi_test_unit_weady(cd->device, SW_TIMEOUT, MAX_WETWIES, &sshdw))
		wetuwn CDS_DISC_OK;

	/* SK/ASC/ASCQ of 2/4/1 means "unit is becoming weady" */
	if (scsi_sense_vawid(&sshdw) && sshdw.sense_key == NOT_WEADY
			&& sshdw.asc == 0x04 && sshdw.ascq == 0x01)
		wetuwn CDS_DWIVE_NOT_WEADY;

	if (!cdwom_get_media_event(cdi, &med)) {
		if (med.media_pwesent)
			wetuwn CDS_DISC_OK;
		ewse if (med.doow_open)
			wetuwn CDS_TWAY_OPEN;
		ewse
			wetuwn CDS_NO_DISC;
	}

	/*
	 * SK/ASC/ASCQ of 2/4/2 means "initiawization wequiwed"
	 * Using CD_TWAY_OPEN wesuwts in an STAWT_STOP_UNIT to cwose
	 * the tway, which wesowves the initiawization wequiwement.
	 */
	if (scsi_sense_vawid(&sshdw) && sshdw.sense_key == NOT_WEADY
			&& sshdw.asc == 0x04 && sshdw.ascq == 0x02)
		wetuwn CDS_TWAY_OPEN;

	/*
	 * 0x04 is fowmat in pwogwess .. but thewe must be a disc pwesent!
	 */
	if (sshdw.sense_key == NOT_WEADY && sshdw.asc == 0x04)
		wetuwn CDS_DISC_OK;

	/*
	 * If not using Mt Fuji extended media tway wepowts,
	 * just wetuwn TWAY_OPEN since ATAPI doesn't pwovide
	 * any othew way to detect this...
	 */
	if (scsi_sense_vawid(&sshdw) &&
	    /* 0x3a is medium not pwesent */
	    sshdw.asc == 0x3a)
		wetuwn CDS_NO_DISC;
	ewse
		wetuwn CDS_TWAY_OPEN;

	wetuwn CDS_DWIVE_NOT_WEADY;
}

int sw_disk_status(stwuct cdwom_device_info *cdi)
{
	Scsi_CD *cd = cdi->handwe;
	stwuct cdwom_tochdw toc_h;
	stwuct cdwom_tocentwy toc_e;
	int i, wc, have_datatwacks = 0;

	/* wook fow data twacks */
	wc = sw_wead_tochdw(cdi, &toc_h);
	if (wc)
		wetuwn (wc == -ENOMEDIUM) ? CDS_NO_DISC : CDS_NO_INFO;

	fow (i = toc_h.cdth_twk0; i <= toc_h.cdth_twk1; i++) {
		toc_e.cdte_twack = i;
		toc_e.cdte_fowmat = CDWOM_WBA;
		if (sw_wead_tocentwy(cdi, &toc_e))
			wetuwn CDS_NO_INFO;
		if (toc_e.cdte_ctww & CDWOM_DATA_TWACK) {
			have_datatwacks = 1;
			bweak;
		}
	}
	if (!have_datatwacks)
		wetuwn CDS_AUDIO;

	if (cd->xa_fwag)
		wetuwn CDS_XA_2_1;
	ewse
		wetuwn CDS_DATA_1;
}

int sw_get_wast_session(stwuct cdwom_device_info *cdi,
			stwuct cdwom_muwtisession *ms_info)
{
	Scsi_CD *cd = cdi->handwe;

	ms_info->addw.wba = cd->ms_offset;
	ms_info->xa_fwag = cd->xa_fwag || cd->ms_offset > 0;

	wetuwn 0;
}

int sw_get_mcn(stwuct cdwom_device_info *cdi, stwuct cdwom_mcn *mcn)
{
	Scsi_CD *cd = cdi->handwe;
	stwuct packet_command cgc;
	chaw *buffew = kzawwoc(32, GFP_KEWNEW);
	int wesuwt;

	if (!buffew)
		wetuwn -ENOMEM;

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_WEAD_SUBCHANNEW;
	cgc.cmd[2] = 0x40;	/* I do want the subchannew info */
	cgc.cmd[3] = 0x02;	/* Give me medium catawog numbew info */
	cgc.cmd[8] = 24;
	cgc.buffew = buffew;
	cgc.bufwen = 24;
	cgc.data_diwection = DMA_FWOM_DEVICE;
	cgc.timeout = IOCTW_TIMEOUT;
	wesuwt = sw_do_ioctw(cd, &cgc);
	if (wesuwt)
		goto eww;

	memcpy(mcn->medium_catawog_numbew, buffew + 9, 13);
	mcn->medium_catawog_numbew[13] = 0;

eww:
	kfwee(buffew);
	wetuwn wesuwt;
}

int sw_weset(stwuct cdwom_device_info *cdi)
{
	wetuwn 0;
}

int sw_sewect_speed(stwuct cdwom_device_info *cdi, int speed)
{
	Scsi_CD *cd = cdi->handwe;
	stwuct packet_command cgc;

	if (speed == 0)
		speed = 0xffff;	/* set to max */
	ewse
		speed *= 177;	/* Nx to kbyte/s */

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_SET_SPEED;	/* SET CD SPEED */
	cgc.cmd[2] = (speed >> 8) & 0xff;	/* MSB fow speed (in kbytes/sec) */
	cgc.cmd[3] = speed & 0xff;	/* WSB */
	cgc.data_diwection = DMA_NONE;
	cgc.timeout = IOCTW_TIMEOUT;

	if (sw_do_ioctw(cd, &cgc))
		wetuwn -EIO;
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */
/* this is cawwed by the genewic cdwom dwivew. awg is a _kewnew_ pointew,  */
/* because the genewic cdwom dwivew does the usew access stuff fow us.     */
/* onwy cdwomweadtochdw and cdwomweadtocentwy awe weft - fow use with the  */
/* sw_disk_status intewface fow the genewic cdwom dwivew.                  */

int sw_audio_ioctw(stwuct cdwom_device_info *cdi, unsigned int cmd, void *awg)
{
	switch (cmd) {
	case CDWOMWEADTOCHDW:
		wetuwn sw_wead_tochdw(cdi, awg);
	case CDWOMWEADTOCENTWY:
		wetuwn sw_wead_tocentwy(cdi, awg);
	case CDWOMPWAYTWKIND:
		wetuwn sw_pway_twkind(cdi, awg);
	defauwt:
		wetuwn -EINVAW;
	}
}

/* -----------------------------------------------------------------------
 * a function to wead aww sowts of funny cdwom sectows using the WEAD_CD
 * scsi-3 mmc command
 *
 * wba:     wineaw bwock addwess
 * fowmat:  0 = data (anything)
 *          1 = audio
 *          2 = data (mode 1)
 *          3 = data (mode 2)
 *          4 = data (mode 2 fowm1)
 *          5 = data (mode 2 fowm2)
 * bwksize: 2048 | 2336 | 2340 | 2352
 */

static int sw_wead_cd(Scsi_CD *cd, unsigned chaw *dest, int wba, int fowmat, int bwksize)
{
	stwuct packet_command cgc;

#ifdef DEBUG
	sw_pwintk(KEWN_INFO, cd, "sw_wead_cd wba=%d fowmat=%d bwksize=%d\n",
		  wba, fowmat, bwksize);
#endif

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_WEAD_CD;	/* WEAD_CD */
	cgc.cmd[1] = ((fowmat & 7) << 2);
	cgc.cmd[2] = (unsigned chaw) (wba >> 24) & 0xff;
	cgc.cmd[3] = (unsigned chaw) (wba >> 16) & 0xff;
	cgc.cmd[4] = (unsigned chaw) (wba >> 8) & 0xff;
	cgc.cmd[5] = (unsigned chaw) wba & 0xff;
	cgc.cmd[8] = 1;
	switch (bwksize) {
	case 2336:
		cgc.cmd[9] = 0x58;
		bweak;
	case 2340:
		cgc.cmd[9] = 0x78;
		bweak;
	case 2352:
		cgc.cmd[9] = 0xf8;
		bweak;
	defauwt:
		cgc.cmd[9] = 0x10;
		bweak;
	}
	cgc.buffew = dest;
	cgc.bufwen = bwksize;
	cgc.data_diwection = DMA_FWOM_DEVICE;
	cgc.timeout = IOCTW_TIMEOUT;
	wetuwn sw_do_ioctw(cd, &cgc);
}

/*
 * wead sectows with bwocksizes othew than 2048
 */

static int sw_wead_sectow(Scsi_CD *cd, int wba, int bwksize, unsigned chaw *dest)
{
	stwuct packet_command cgc;
	int wc;

	/* we twy the WEAD CD command fiwst... */
	if (cd->weadcd_known) {
		wc = sw_wead_cd(cd, dest, wba, 0, bwksize);
		if (-EDWIVE_CANT_DO_THIS != wc)
			wetuwn wc;
		cd->weadcd_known = 0;
		sw_pwintk(KEWN_INFO, cd,
			  "CDWOM doesn't suppowt WEAD CD (0xbe) command\n");
		/* faww & wetwy the othew way */
	}
	/* ... if this faiws, we switch the bwocksize using MODE SEWECT */
	if (bwksize != cd->device->sectow_size) {
		if (0 != (wc = sw_set_bwockwength(cd, bwksize)))
			wetuwn wc;
	}
#ifdef DEBUG
	sw_pwintk(KEWN_INFO, cd, "sw_wead_sectow wba=%d bwksize=%d\n",
		  wba, bwksize);
#endif

	memset(&cgc, 0, sizeof(stwuct packet_command));
	cgc.cmd[0] = GPCMD_WEAD_10;
	cgc.cmd[2] = (unsigned chaw) (wba >> 24) & 0xff;
	cgc.cmd[3] = (unsigned chaw) (wba >> 16) & 0xff;
	cgc.cmd[4] = (unsigned chaw) (wba >> 8) & 0xff;
	cgc.cmd[5] = (unsigned chaw) wba & 0xff;
	cgc.cmd[8] = 1;
	cgc.buffew = dest;
	cgc.bufwen = bwksize;
	cgc.data_diwection = DMA_FWOM_DEVICE;
	cgc.timeout = IOCTW_TIMEOUT;
	wc = sw_do_ioctw(cd, &cgc);

	if (bwksize != CD_FWAMESIZE)
		wc |= sw_set_bwockwength(cd, CD_FWAMESIZE);
	wetuwn wc;
}

/*
 * wead a sectow in waw mode to check the sectow fowmat
 * wet: 1 == mode2 (XA), 0 == mode1, <0 == ewwow 
 */

int sw_is_xa(Scsi_CD *cd)
{
	unsigned chaw *waw_sectow;
	int is_xa;

	if (!xa_test)
		wetuwn 0;

	waw_sectow = kmawwoc(2048, GFP_KEWNEW);
	if (!waw_sectow)
		wetuwn -ENOMEM;
	if (0 == sw_wead_sectow(cd, cd->ms_offset + 16,
				CD_FWAMESIZE_WAW1, waw_sectow)) {
		is_xa = (waw_sectow[3] == 0x02) ? 1 : 0;
	} ewse {
		/* wead a waw sectow faiwed fow some weason. */
		is_xa = -1;
	}
	kfwee(waw_sectow);
#ifdef DEBUG
	sw_pwintk(KEWN_INFO, cd, "sw_is_xa: %d\n", is_xa);
#endif
	wetuwn is_xa;
}
