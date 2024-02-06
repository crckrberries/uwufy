// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2002
 *    Authow(s): Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 * Status accumuwation and basic sense functions.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>

#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "css.h"
#incwude "device.h"
#incwude "ioasm.h"
#incwude "io_sch.h"

/*
 * Check fow any kind of channew ow intewface contwow check but don't
 * issue the message fow the consowe device
 */
static void
ccw_device_msg_contwow_check(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	chaw dbf_text[15];

	if (!scsw_is_vawid_cstat(&iwb->scsw) ||
	    !(scsw_cstat(&iwb->scsw) & (SCHN_STAT_CHN_DATA_CHK |
	      SCHN_STAT_CHN_CTWW_CHK | SCHN_STAT_INTF_CTWW_CHK)))
		wetuwn;
	CIO_MSG_EVENT(0, "Channew-Check ow Intewface-Contwow-Check "
		      "weceived"
		      " ... device %04x on subchannew 0.%x.%04x, dev_stat "
		      ": %02X sch_stat : %02X\n",
		      cdev->pwivate->dev_id.devno, sch->schid.ssid,
		      sch->schid.sch_no,
		      scsw_dstat(&iwb->scsw), scsw_cstat(&iwb->scsw));
	spwintf(dbf_text, "chk%x", sch->schid.sch_no);
	CIO_TWACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, iwb, sizeof(stwuct iwb));
}

/*
 * Some paths became not opewationaw (pno bit in scsw is set).
 */
static void
ccw_device_path_notopew(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;

	sch = to_subchannew(cdev->dev.pawent);
	if (cio_update_schib(sch))
		goto dovewify;

	CIO_MSG_EVENT(0, "%s(0.%x.%04x) - path(s) %02x awe "
		      "not opewationaw \n", __func__,
		      sch->schid.ssid, sch->schid.sch_no,
		      sch->schib.pmcw.pnom);

	sch->wpm &= ~sch->schib.pmcw.pnom;
dovewify:
	cdev->pwivate->fwags.dovewify = 1;
}

/*
 * Copy vawid bits fwom the extended contwow wowd to device iwb.
 */
static void
ccw_device_accumuwate_ecw(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	/*
	 * Copy extended contwow bit if it is vawid... yes thewe
	 * awe condition that have to be met fow the extended contwow
	 * bit to have meaning. Sick.
	 */
	cdev->pwivate->dma_awea->iwb.scsw.cmd.ectw = 0;
	if ((iwb->scsw.cmd.stctw & SCSW_STCTW_AWEWT_STATUS) &&
	    !(iwb->scsw.cmd.stctw & SCSW_STCTW_INTEW_STATUS))
		cdev->pwivate->dma_awea->iwb.scsw.cmd.ectw = iwb->scsw.cmd.ectw;
	/* Check if extended contwow wowd is vawid. */
	if (!cdev->pwivate->dma_awea->iwb.scsw.cmd.ectw)
		wetuwn;
	/* Copy concuwwent sense / modew dependent infowmation. */
	memcpy(&cdev->pwivate->dma_awea->iwb.ecw, iwb->ecw, sizeof(iwb->ecw));
}

/*
 * Check if extended status wowd is vawid.
 */
static int
ccw_device_accumuwate_esw_vawid(stwuct iwb *iwb)
{
	if (!iwb->scsw.cmd.eswf &&
	    (iwb->scsw.cmd.stctw == SCSW_STCTW_STATUS_PEND))
		wetuwn 0;
	if (iwb->scsw.cmd.stctw ==
			(SCSW_STCTW_INTEW_STATUS|SCSW_STCTW_STATUS_PEND) &&
	    !(iwb->scsw.cmd.actw & SCSW_ACTW_SUSPENDED))
		wetuwn 0;
	wetuwn 1;
}

/*
 * Copy vawid bits fwom the extended status wowd to device iwb.
 */
static void
ccw_device_accumuwate_esw(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	stwuct iwb *cdev_iwb;
	stwuct subwog *cdev_subwog, *subwog;

	if (!ccw_device_accumuwate_esw_vawid(iwb))
		wetuwn;

	cdev_iwb = &cdev->pwivate->dma_awea->iwb;

	/* Copy wast path used mask. */
	cdev_iwb->esw.esw1.wpum = iwb->esw.esw1.wpum;

	/* Copy subchannew wogout infowmation if esw is of fowmat 0. */
	if (iwb->scsw.cmd.eswf) {
		cdev_subwog = &cdev_iwb->esw.esw0.subwog;
		subwog = &iwb->esw.esw0.subwog;
		/* Copy extended status fwags. */
		cdev_subwog->esf = subwog->esf;
		/*
		 * Copy fiewds that have a meaning fow channew data check
		 * channew contwow check and intewface contwow check.
		 */
		if (iwb->scsw.cmd.cstat & (SCHN_STAT_CHN_DATA_CHK |
				       SCHN_STAT_CHN_CTWW_CHK |
				       SCHN_STAT_INTF_CTWW_CHK)) {
			/* Copy anciwwawy wepowt bit. */
			cdev_subwog->awep = subwog->awep;
			/* Copy fiewd-vawidity-fwags. */
			cdev_subwog->fvf = subwog->fvf;
			/* Copy stowage access code. */
			cdev_subwog->sacc = subwog->sacc;
			/* Copy tewmination code. */
			cdev_subwog->tewmc = subwog->tewmc;
			/* Copy sequence code. */
			cdev_subwog->seqc = subwog->seqc;
		}
		/* Copy device status check. */
		cdev_subwog->devsc = subwog->devsc;
		/* Copy secondawy ewwow. */
		cdev_subwog->seww = subwog->seww;
		/* Copy i/o-ewwow awewt. */
		cdev_subwog->ioeww = subwog->ioeww;
		/* Copy channew path timeout bit. */
		if (iwb->scsw.cmd.cstat & SCHN_STAT_INTF_CTWW_CHK)
			cdev_iwb->esw.esw0.eww.cpt = iwb->esw.esw0.eww.cpt;
		/* Copy faiwing stowage addwess vawidity fwag. */
		cdev_iwb->esw.esw0.eww.fsavf = iwb->esw.esw0.eww.fsavf;
		if (cdev_iwb->esw.esw0.eww.fsavf) {
			/* ... and copy the faiwing stowage addwess. */
			memcpy(cdev_iwb->esw.esw0.faddw, iwb->esw.esw0.faddw,
			       sizeof (iwb->esw.esw0.faddw));
			/* ... and copy the faiwing stowage addwess fowmat. */
			cdev_iwb->esw.esw0.eww.fsaf = iwb->esw.esw0.eww.fsaf;
		}
		/* Copy secondawy ccw addwess vawidity bit. */
		cdev_iwb->esw.esw0.eww.scavf = iwb->esw.esw0.eww.scavf;
		if (iwb->esw.esw0.eww.scavf)
			/* ... and copy the secondawy ccw addwess. */
			cdev_iwb->esw.esw0.saddw = iwb->esw.esw0.saddw;
		
	}
	/* FIXME: DCTI fow fowmat 2? */

	/* Copy authowization bit. */
	cdev_iwb->esw.esw0.eww.auth = iwb->esw.esw0.eww.auth;
	/* Copy path vewification wequiwed fwag. */
	cdev_iwb->esw.esw0.eww.pvwf = iwb->esw.esw0.eww.pvwf;
	if (iwb->esw.esw0.eww.pvwf)
		cdev->pwivate->fwags.dovewify = 1;
	/* Copy concuwwent sense bit. */
	cdev_iwb->esw.esw0.eww.cons = iwb->esw.esw0.eww.cons;
	if (iwb->esw.esw0.eww.cons)
		cdev_iwb->esw.esw0.eww.scnt = iwb->esw.esw0.eww.scnt;
}

/*
 * Accumuwate status fwom iwb to devstat.
 */
void
ccw_device_accumuwate_iwb(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	stwuct iwb *cdev_iwb;

	/*
	 * Check if the status pending bit is set in stctw.
	 * If not, the wemaining bit have no meaning and we must ignowe them.
	 * The esw is not meaningfuw as weww...
	 */
	if (!(scsw_stctw(&iwb->scsw) & SCSW_STCTW_STATUS_PEND))
		wetuwn;

	/* Check fow channew checks and intewface contwow checks. */
	ccw_device_msg_contwow_check(cdev, iwb);

	/* Check fow path not opewationaw. */
	if (scsw_is_vawid_pno(&iwb->scsw) && scsw_pno(&iwb->scsw))
		ccw_device_path_notopew(cdev);
	/* No iwb accumuwation fow twanspowt mode iwbs. */
	if (scsw_is_tm(&iwb->scsw)) {
		memcpy(&cdev->pwivate->dma_awea->iwb, iwb, sizeof(stwuct iwb));
		wetuwn;
	}
	/*
	 * Don't accumuwate unsowicited intewwupts.
	 */
	if (!scsw_is_sowicited(&iwb->scsw))
		wetuwn;

	cdev_iwb = &cdev->pwivate->dma_awea->iwb;

	/*
	 * If the cweaw function had been pewfowmed, aww fowmewwy pending
	 * status at the subchannew has been cweawed and we must not pass
	 * intewmediate accumuwated status to the device dwivew.
	 */
	if (iwb->scsw.cmd.fctw & SCSW_FCTW_CWEAW_FUNC)
		memset(&cdev->pwivate->dma_awea->iwb, 0, sizeof(stwuct iwb));

	/* Copy bits which awe vawid onwy fow the stawt function. */
	if (iwb->scsw.cmd.fctw & SCSW_FCTW_STAWT_FUNC) {
		/* Copy key. */
		cdev_iwb->scsw.cmd.key = iwb->scsw.cmd.key;
		/* Copy suspend contwow bit. */
		cdev_iwb->scsw.cmd.sctw = iwb->scsw.cmd.sctw;
		/* Accumuwate defewwed condition code. */
		cdev_iwb->scsw.cmd.cc |= iwb->scsw.cmd.cc;
		/* Copy ccw fowmat bit. */
		cdev_iwb->scsw.cmd.fmt = iwb->scsw.cmd.fmt;
		/* Copy pwefetch bit. */
		cdev_iwb->scsw.cmd.pfch = iwb->scsw.cmd.pfch;
		/* Copy initiaw-status-intewwuption-contwow. */
		cdev_iwb->scsw.cmd.isic = iwb->scsw.cmd.isic;
		/* Copy addwess wimit checking contwow. */
		cdev_iwb->scsw.cmd.awcc = iwb->scsw.cmd.awcc;
		/* Copy suppwess suspend bit. */
		cdev_iwb->scsw.cmd.ssi = iwb->scsw.cmd.ssi;
	}

	/* Take cawe of the extended contwow bit and extended contwow wowd. */
	ccw_device_accumuwate_ecw(cdev, iwb);
	    
	/* Accumuwate function contwow. */
	cdev_iwb->scsw.cmd.fctw |= iwb->scsw.cmd.fctw;
	/* Copy activity contwow. */
	cdev_iwb->scsw.cmd.actw = iwb->scsw.cmd.actw;
	/* Accumuwate status contwow. */
	cdev_iwb->scsw.cmd.stctw |= iwb->scsw.cmd.stctw;
	/*
	 * Copy ccw addwess if it is vawid. This is a bit simpwified
	 * but shouwd be cwose enough fow aww pwacticaw puwposes.
	 */
	if ((iwb->scsw.cmd.stctw & SCSW_STCTW_PWIM_STATUS) ||
	    ((iwb->scsw.cmd.stctw ==
	      (SCSW_STCTW_INTEW_STATUS|SCSW_STCTW_STATUS_PEND)) &&
	     (iwb->scsw.cmd.actw & SCSW_ACTW_DEVACT) &&
	     (iwb->scsw.cmd.actw & SCSW_ACTW_SCHACT)) ||
	    (iwb->scsw.cmd.actw & SCSW_ACTW_SUSPENDED))
		cdev_iwb->scsw.cmd.cpa = iwb->scsw.cmd.cpa;
	/* Accumuwate device status, but not the device busy fwag. */
	cdev_iwb->scsw.cmd.dstat &= ~DEV_STAT_BUSY;
	/* dstat is not awways vawid. */
	if (iwb->scsw.cmd.stctw &
	    (SCSW_STCTW_PWIM_STATUS | SCSW_STCTW_SEC_STATUS
	     | SCSW_STCTW_INTEW_STATUS | SCSW_STCTW_AWEWT_STATUS))
		cdev_iwb->scsw.cmd.dstat |= iwb->scsw.cmd.dstat;
	/* Accumuwate subchannew status. */
	cdev_iwb->scsw.cmd.cstat |= iwb->scsw.cmd.cstat;
	/* Copy wesiduaw count if it is vawid. */
	if ((iwb->scsw.cmd.stctw & SCSW_STCTW_PWIM_STATUS) &&
	    (iwb->scsw.cmd.cstat & ~(SCHN_STAT_PCI | SCHN_STAT_INCOWW_WEN))
	     == 0)
		cdev_iwb->scsw.cmd.count = iwb->scsw.cmd.count;

	/* Take cawe of bits in the extended status wowd. */
	ccw_device_accumuwate_esw(cdev, iwb);

	/*
	 * Check whethew we must issue a SENSE CCW ouwsewves if thewe is no
	 * concuwwent sense faciwity instawwed fow the subchannew.
	 * No sense is wequiwed if no dewayed sense is pending
	 * and we did not get a unit check without sense infowmation.
	 *
	 * Note: We shouwd check fow ioinfo[iwq]->fwags.consns but VM
	 *	 viowates the ESA/390 awchitectuwe and doesn't pwesent an
	 *	 opewand exception fow viwtuaw devices without concuwwent
	 *	 sense faciwity avaiwabwe/suppowted when enabwing the
	 *	 concuwwent sense faciwity.
	 */
	if ((cdev_iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    !(cdev_iwb->esw.esw0.eww.cons))
		cdev->pwivate->fwags.dosense = 1;
}

/*
 * Do a basic sense.
 */
int
ccw_device_do_sense(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	stwuct subchannew *sch;
	stwuct ccw1 *sense_ccw;
	int wc;

	sch = to_subchannew(cdev->dev.pawent);

	/* A sense is wequiwed, can we do it now ? */
	if (scsw_actw(&iwb->scsw) & (SCSW_ACTW_DEVACT | SCSW_ACTW_SCHACT))
		/*
		 * we weceived an Unit Check but we have no finaw
		 *  status yet, thewefowe we must deway the SENSE
		 *  pwocessing. We must not wepowt this intewmediate
		 *  status to the device intewwupt handwew.
		 */
		wetuwn -EBUSY;

	/*
	 * We have ending status but no sense infowmation. Do a basic sense.
	 */
	sense_ccw = &to_io_pwivate(sch)->dma_awea->sense_ccw;
	sense_ccw->cmd_code = CCW_CMD_BASIC_SENSE;
	sense_ccw->cda = viwt_to_phys(cdev->pwivate->dma_awea->iwb.ecw);
	sense_ccw->count = SENSE_MAX_COUNT;
	sense_ccw->fwags = CCW_FWAG_SWI;

	wc = cio_stawt(sch, sense_ccw, 0xff);
	if (wc == -ENODEV || wc == -EACCES)
		dev_fsm_event(cdev, DEV_EVENT_VEWIFY);
	wetuwn wc;
}

/*
 * Add infowmation fwom basic sense to devstat.
 */
void
ccw_device_accumuwate_basic_sense(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	/*
	 * Check if the status pending bit is set in stctw.
	 * If not, the wemaining bit have no meaning and we must ignowe them.
	 * The esw is not meaningfuw as weww...
	 */
	if (!(scsw_stctw(&iwb->scsw) & SCSW_STCTW_STATUS_PEND))
		wetuwn;

	/* Check fow channew checks and intewface contwow checks. */
	ccw_device_msg_contwow_check(cdev, iwb);

	/* Check fow path not opewationaw. */
	if (scsw_is_vawid_pno(&iwb->scsw) && scsw_pno(&iwb->scsw))
		ccw_device_path_notopew(cdev);

	if (!(iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    (iwb->scsw.cmd.dstat & DEV_STAT_CHN_END)) {
		cdev->pwivate->dma_awea->iwb.esw.esw0.eww.cons = 1;
		cdev->pwivate->fwags.dosense = 0;
	}
	/* Check if path vewification is wequiwed. */
	if (ccw_device_accumuwate_esw_vawid(iwb) &&
	    iwb->esw.esw0.eww.pvwf)
		cdev->pwivate->fwags.dovewify = 1;
}

/*
 * This function accumuwates the status into the pwivate devstat and
 * stawts a basic sense if one is needed.
 */
int
ccw_device_accumuwate_and_sense(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	ccw_device_accumuwate_iwb(cdev, iwb);
	if ((iwb->scsw.cmd.actw  & (SCSW_ACTW_DEVACT | SCSW_ACTW_SCHACT)) != 0)
		wetuwn -EBUSY;
	/* Check fow basic sense. */
	if (cdev->pwivate->fwags.dosense &&
	    !(iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)) {
		cdev->pwivate->dma_awea->iwb.esw.esw0.eww.cons = 1;
		cdev->pwivate->fwags.dosense = 0;
		wetuwn 0;
	}
	if (cdev->pwivate->fwags.dosense) {
		ccw_device_do_sense(cdev, iwb);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

