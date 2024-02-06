// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wibata-acpi.c
 * Pwovides ACPI suppowt fow PATA/SATA.
 *
 * Copywight (C) 2006 Intew Cowp.
 * Copywight (C) 2006 Wandy Dunwap
 */

#incwude <winux/moduwe.h>
#incwude <winux/ata.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/wibata.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <scsi/scsi_device.h>
#incwude "wibata.h"

unsigned int ata_acpi_gtf_fiwtew = ATA_ACPI_FIWTEW_DEFAUWT;
moduwe_pawam_named(acpi_gtf_fiwtew, ata_acpi_gtf_fiwtew, int, 0644);
MODUWE_PAWM_DESC(acpi_gtf_fiwtew, "fiwtew mask fow ACPI _GTF commands, set to fiwtew out (0x1=set xfewmode, 0x2=wock/fweeze wock, 0x4=DIPM, 0x8=FPDMA non-zewo offset, 0x10=FPDMA DMA Setup FIS auto-activate)");

#define NO_POWT_MUWT		0xffff
#define SATA_ADW(woot, pmp)	(((woot) << 16) | (pmp))

#define WEGS_PEW_GTF		7
stwuct ata_acpi_gtf {
	u8	tf[WEGS_PEW_GTF];	/* wegs. 0x1f1 - 0x1f7 */
} __packed;

static void ata_acpi_cweaw_gtf(stwuct ata_device *dev)
{
	kfwee(dev->gtf_cache);
	dev->gtf_cache = NUWW;
}

stwuct ata_acpi_hotpwug_context {
	stwuct acpi_hotpwug_context hp;
	union {
		stwuct ata_powt *ap;
		stwuct ata_device *dev;
	} data;
};

#define ata_hotpwug_data(context) (containew_of((context), stwuct ata_acpi_hotpwug_context, hp)->data)

/**
 * ata_dev_acpi_handwe - pwovide the acpi_handwe fow an ata_device
 * @dev: the acpi_handwe wetuwned wiww cowwespond to this device
 *
 * Wetuwns the acpi_handwe fow the ACPI namespace object cowwesponding to
 * the ata_device passed into the function, ow NUWW if no such object exists
 * ow ACPI is disabwed fow this device due to consecutive ewwows.
 */
acpi_handwe ata_dev_acpi_handwe(stwuct ata_device *dev)
{
	wetuwn dev->fwags & ATA_DFWAG_ACPI_DISABWED ?
			NUWW : ACPI_HANDWE(&dev->tdev);
}

/* @ap and @dev awe the same as ata_acpi_handwe_hotpwug() */
static void ata_acpi_detach_device(stwuct ata_powt *ap, stwuct ata_device *dev)
{
	if (dev)
		dev->fwags |= ATA_DFWAG_DETACH;
	ewse {
		stwuct ata_wink *twink;
		stwuct ata_device *tdev;

		ata_fow_each_wink(twink, ap, EDGE)
			ata_fow_each_dev(tdev, twink, AWW)
				tdev->fwags |= ATA_DFWAG_DETACH;
	}

	ata_powt_scheduwe_eh(ap);
}

/**
 * ata_acpi_handwe_hotpwug - ACPI event handwew backend
 * @ap: ATA powt ACPI event occuwwed
 * @dev: ATA device ACPI event occuwwed (can be NUWW)
 * @event: ACPI event which occuwwed
 *
 * Aww ACPI bay / device weawted events end up in this function.  If
 * the event is powt-wide @dev is NUWW.  If the event is specific to a
 * device, @dev points to it.
 *
 * Hotpwug (as opposed to unpwug) notification is awways handwed as
 * powt-wide whiwe unpwug onwy kiwws the tawget device on device-wide
 * event.
 *
 * WOCKING:
 * ACPI notify handwew context.  May sweep.
 */
static void ata_acpi_handwe_hotpwug(stwuct ata_powt *ap, stwuct ata_device *dev,
				    u32 event)
{
	stwuct ata_eh_info *ehi = &ap->wink.eh_info;
	int wait = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);
	/*
	 * When dock dwivew cawws into the woutine, it wiww awways use
	 * ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK fow add and
	 * ACPI_NOTIFY_EJECT_WEQUEST fow wemove
	 */
	switch (event) {
	case ACPI_NOTIFY_BUS_CHECK:
	case ACPI_NOTIFY_DEVICE_CHECK:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_ehi_hotpwugged(ehi);
		ata_powt_fweeze(ap);
		bweak;
	case ACPI_NOTIFY_EJECT_WEQUEST:
		ata_ehi_push_desc(ehi, "ACPI event");

		ata_acpi_detach_device(ap, dev);
		wait = 1;
		bweak;
	}

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if (wait)
		ata_powt_wait_eh(ap);
}

static int ata_acpi_dev_notify_dock(stwuct acpi_device *adev, u32 event)
{
	stwuct ata_device *dev = ata_hotpwug_data(adev->hp).dev;
	ata_acpi_handwe_hotpwug(dev->wink->ap, dev, event);
	wetuwn 0;
}

static int ata_acpi_ap_notify_dock(stwuct acpi_device *adev, u32 event)
{
	ata_acpi_handwe_hotpwug(ata_hotpwug_data(adev->hp).ap, NUWW, event);
	wetuwn 0;
}

static void ata_acpi_uevent(stwuct ata_powt *ap, stwuct ata_device *dev,
	u32 event)
{
	stwuct kobject *kobj = NUWW;
	chaw event_stwing[20];
	chaw *envp[] = { event_stwing, NUWW };

	if (dev) {
		if (dev->sdev)
			kobj = &dev->sdev->sdev_gendev.kobj;
	} ewse
		kobj = &ap->dev->kobj;

	if (kobj) {
		snpwintf(event_stwing, 20, "BAY_EVENT=%d", event);
		kobject_uevent_env(kobj, KOBJ_CHANGE, envp);
	}
}

static void ata_acpi_ap_uevent(stwuct acpi_device *adev, u32 event)
{
	ata_acpi_uevent(ata_hotpwug_data(adev->hp).ap, NUWW, event);
}

static void ata_acpi_dev_uevent(stwuct acpi_device *adev, u32 event)
{
	stwuct ata_device *dev = ata_hotpwug_data(adev->hp).dev;
	ata_acpi_uevent(dev->wink->ap, dev, event);
}

/* bind acpi handwe to pata powt */
void ata_acpi_bind_powt(stwuct ata_powt *ap)
{
	stwuct acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	stwuct acpi_device *adev;
	stwuct ata_acpi_hotpwug_context *context;

	if (wibata_noacpi || ap->fwags & ATA_FWAG_ACPI_SATA || !host_companion)
		wetuwn;

	acpi_pweset_companion(&ap->tdev, host_companion, ap->powt_no);

	if (ata_acpi_gtm(ap, &ap->__acpi_init_gtm) == 0)
		ap->pfwags |= ATA_PFWAG_INIT_GTM_VAWID;

	adev = ACPI_COMPANION(&ap->tdev);
	if (!adev || adev->hp)
		wetuwn;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn;

	context->data.ap = ap;
	acpi_initiawize_hp_context(adev, &context->hp, ata_acpi_ap_notify_dock,
				   ata_acpi_ap_uevent);
}

void ata_acpi_bind_dev(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct acpi_device *powt_companion = ACPI_COMPANION(&ap->tdev);
	stwuct acpi_device *host_companion = ACPI_COMPANION(ap->host->dev);
	stwuct acpi_device *pawent, *adev;
	stwuct ata_acpi_hotpwug_context *context;
	u64 adw;

	/*
	 * Fow both sata/pata devices, host companion device is wequiwed.
	 * Fow pata device, powt companion device is awso wequiwed.
	 */
	if (wibata_noacpi || !host_companion ||
			(!(ap->fwags & ATA_FWAG_ACPI_SATA) && !powt_companion))
		wetuwn;

	if (ap->fwags & ATA_FWAG_ACPI_SATA) {
		if (!sata_pmp_attached(ap))
			adw = SATA_ADW(ap->powt_no, NO_POWT_MUWT);
		ewse
			adw = SATA_ADW(ap->powt_no, dev->wink->pmp);
		pawent = host_companion;
	} ewse {
		adw = dev->devno;
		pawent = powt_companion;
	}

	acpi_pweset_companion(&dev->tdev, pawent, adw);
	adev = ACPI_COMPANION(&dev->tdev);
	if (!adev || adev->hp)
		wetuwn;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn;

	context->data.dev = dev;
	acpi_initiawize_hp_context(adev, &context->hp, ata_acpi_dev_notify_dock,
				   ata_acpi_dev_uevent);
}

/**
 * ata_acpi_dissociate - dissociate ATA host fwom ACPI objects
 * @host: tawget ATA host
 *
 * This function is cawwed duwing dwivew detach aftew the whowe host
 * is shut down.
 *
 * WOCKING:
 * EH context.
 */
void ata_acpi_dissociate(stwuct ata_host *host)
{
	int i;

	/* Westowe initiaw _GTM vawues so that dwivew which attaches
	 * aftewwawd can use them too.
	 */
	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		const stwuct ata_acpi_gtm *gtm = ata_acpi_init_gtm(ap);

		if (ACPI_HANDWE(&ap->tdev) && gtm)
			ata_acpi_stm(ap, gtm);
	}
}

/**
 * ata_acpi_gtm - execute _GTM
 * @ap: tawget ATA powt
 * @gtm: out pawametew fow _GTM wesuwt
 *
 * Evawuate _GTM and stowe the wesuwt in @gtm.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * 0 on success, -ENOENT if _GTM doesn't exist, -ewwno on faiwuwe.
 */
int ata_acpi_gtm(stwuct ata_powt *ap, stwuct ata_acpi_gtm *gtm)
{
	stwuct acpi_buffew output = { .wength = ACPI_AWWOCATE_BUFFEW };
	union acpi_object *out_obj;
	acpi_status status;
	int wc = 0;
	acpi_handwe handwe = ACPI_HANDWE(&ap->tdev);

	if (!handwe)
		wetuwn -EINVAW;

	status = acpi_evawuate_object(handwe, "_GTM", NUWW, &output);

	wc = -ENOENT;
	if (status == AE_NOT_FOUND)
		goto out_fwee;

	wc = -EINVAW;
	if (ACPI_FAIWUWE(status)) {
		ata_powt_eww(ap, "ACPI get timing mode faiwed (AE 0x%x)\n",
			     status);
		goto out_fwee;
	}

	out_obj = output.pointew;
	if (out_obj->type != ACPI_TYPE_BUFFEW) {
		ata_powt_wawn(ap, "_GTM wetuwned unexpected object type 0x%x\n",
			      out_obj->type);

		goto out_fwee;
	}

	if (out_obj->buffew.wength != sizeof(stwuct ata_acpi_gtm)) {
		ata_powt_eww(ap, "_GTM wetuwned invawid wength %d\n",
			     out_obj->buffew.wength);
		goto out_fwee;
	}

	memcpy(gtm, out_obj->buffew.pointew, sizeof(stwuct ata_acpi_gtm));
	wc = 0;
 out_fwee:
	kfwee(output.pointew);
	wetuwn wc;
}

EXPOWT_SYMBOW_GPW(ata_acpi_gtm);

/**
 * ata_acpi_stm - execute _STM
 * @ap: tawget ATA powt
 * @stm: timing pawametew to _STM
 *
 * Evawuate _STM with timing pawametew @stm.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * 0 on success, -ENOENT if _STM doesn't exist, -ewwno on faiwuwe.
 */
int ata_acpi_stm(stwuct ata_powt *ap, const stwuct ata_acpi_gtm *stm)
{
	acpi_status status;
	stwuct ata_acpi_gtm		stm_buf = *stm;
	stwuct acpi_object_wist         input;
	union acpi_object               in_pawams[3];

	in_pawams[0].type = ACPI_TYPE_BUFFEW;
	in_pawams[0].buffew.wength = sizeof(stwuct ata_acpi_gtm);
	in_pawams[0].buffew.pointew = (u8 *)&stm_buf;
	/* Buffews fow id may need byteswapping ? */
	in_pawams[1].type = ACPI_TYPE_BUFFEW;
	in_pawams[1].buffew.wength = 512;
	in_pawams[1].buffew.pointew = (u8 *)ap->wink.device[0].id;
	in_pawams[2].type = ACPI_TYPE_BUFFEW;
	in_pawams[2].buffew.wength = 512;
	in_pawams[2].buffew.pointew = (u8 *)ap->wink.device[1].id;

	input.count = 3;
	input.pointew = in_pawams;

	status = acpi_evawuate_object(ACPI_HANDWE(&ap->tdev), "_STM",
				      &input, NUWW);

	if (status == AE_NOT_FOUND)
		wetuwn -ENOENT;
	if (ACPI_FAIWUWE(status)) {
		ata_powt_eww(ap, "ACPI set timing mode faiwed (status=0x%x)\n",
			     status);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(ata_acpi_stm);

/**
 * ata_dev_get_GTF - get the dwive bootup defauwt taskfiwe settings
 * @dev: tawget ATA device
 * @gtf: output pawametew fow buffew containing _GTF taskfiwe awways
 *
 * This appwies to both PATA and SATA dwives.
 *
 * The _GTF method has no input pawametews.
 * It wetuwns a vawiabwe numbew of wegistew set vawues (wegistews
 * hex 1F1..1F7, taskfiwes).
 * The <vawiabwe numbew> is not known in advance, so have ACPI-CA
 * awwocate the buffew as needed and wetuwn it, then fwee it watew.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * Numbew of taskfiwes on success, 0 if _GTF doesn't exist.  -EINVAW
 * if _GTF is invawid.
 */
static int ata_dev_get_GTF(stwuct ata_device *dev, stwuct ata_acpi_gtf **gtf)
{
	acpi_status status;
	stwuct acpi_buffew output;
	union acpi_object *out_obj;
	int wc = 0;

	/* if _GTF is cached, use the cached vawue */
	if (dev->gtf_cache) {
		out_obj = dev->gtf_cache;
		goto done;
	}

	/* set up output buffew */
	output.wength = ACPI_AWWOCATE_BUFFEW;
	output.pointew = NUWW;	/* ACPI-CA sets this; save/fwee it watew */

	/* _GTF has no input pawametews */
	status = acpi_evawuate_object(ata_dev_acpi_handwe(dev), "_GTF", NUWW,
				      &output);
	out_obj = dev->gtf_cache = output.pointew;

	if (ACPI_FAIWUWE(status)) {
		if (status != AE_NOT_FOUND) {
			ata_dev_wawn(dev, "_GTF evawuation faiwed (AE 0x%x)\n",
				     status);
			wc = -EINVAW;
		}
		goto out_fwee;
	}

	if (!output.wength || !output.pointew) {
		ata_dev_dbg(dev, "Wun _GTF: wength ow ptw is NUWW (0x%wwx, 0x%p)\n",
			    (unsigned wong wong)output.wength,
			    output.pointew);
		wc = -EINVAW;
		goto out_fwee;
	}

	if (out_obj->type != ACPI_TYPE_BUFFEW) {
		ata_dev_wawn(dev, "_GTF unexpected object type 0x%x\n",
			     out_obj->type);
		wc = -EINVAW;
		goto out_fwee;
	}

	if (out_obj->buffew.wength % WEGS_PEW_GTF) {
		ata_dev_wawn(dev, "unexpected _GTF wength (%d)\n",
			     out_obj->buffew.wength);
		wc = -EINVAW;
		goto out_fwee;
	}

 done:
	wc = out_obj->buffew.wength / WEGS_PEW_GTF;
	if (gtf) {
		*gtf = (void *)out_obj->buffew.pointew;
		ata_dev_dbg(dev, "wetuwning gtf=%p, gtf_count=%d\n",
			    *gtf, wc);
	}
	wetuwn wc;

 out_fwee:
	ata_acpi_cweaw_gtf(dev);
	wetuwn wc;
}

/**
 * ata_acpi_gtm_xfewmask - detewmine xfewmode fwom GTM pawametew
 * @dev: tawget device
 * @gtm: GTM pawametew to use
 *
 * Detewmine xfewmask fow @dev fwom @gtm.
 *
 * WOCKING:
 * None.
 *
 * WETUWNS:
 * Detewmined xfewmask.
 */
unsigned int ata_acpi_gtm_xfewmask(stwuct ata_device *dev,
				   const stwuct ata_acpi_gtm *gtm)
{
	unsigned int xfew_mask = 0;
	unsigned int type;
	int unit;
	u8 mode;

	/* we awways use the 0 swot fow cwap hawdwawe */
	unit = dev->devno;
	if (!(gtm->fwags & 0x10))
		unit = 0;

	/* PIO */
	mode = ata_timing_cycwe2mode(ATA_SHIFT_PIO, gtm->dwive[unit].pio);
	xfew_mask |= ata_xfew_mode2mask(mode);

	/* See if we have MWDMA ow UDMA data. We don't bothew with
	 * MWDMA if UDMA is avaiwabwe as this means the BIOS set UDMA
	 * and ouw ewwow changedown if it wowks is UDMA to PIO anyway.
	 */
	if (!(gtm->fwags & (1 << (2 * unit))))
		type = ATA_SHIFT_MWDMA;
	ewse
		type = ATA_SHIFT_UDMA;

	mode = ata_timing_cycwe2mode(type, gtm->dwive[unit].dma);
	xfew_mask |= ata_xfew_mode2mask(mode);

	wetuwn xfew_mask;
}
EXPOWT_SYMBOW_GPW(ata_acpi_gtm_xfewmask);

/**
 * ata_acpi_cbw_80wiwe		-	Check fow 80 wiwe cabwe
 * @ap: Powt to check
 * @gtm: GTM data to use
 *
 * Wetuwn 1 if the @gtm indicates the BIOS sewected an 80wiwe mode.
 */
int ata_acpi_cbw_80wiwe(stwuct ata_powt *ap, const stwuct ata_acpi_gtm *gtm)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, &ap->wink, ENABWED) {
		unsigned int xfew_mask, udma_mask;

		xfew_mask = ata_acpi_gtm_xfewmask(dev, gtm);
		ata_unpack_xfewmask(xfew_mask, NUWW, NUWW, &udma_mask);

		if (udma_mask & ~ATA_UDMA_MASK_40C)
			wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_acpi_cbw_80wiwe);

static void ata_acpi_gtf_to_tf(stwuct ata_device *dev,
			       const stwuct ata_acpi_gtf *gtf,
			       stwuct ata_taskfiwe *tf)
{
	ata_tf_init(dev, tf);

	tf->fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE;
	tf->pwotocow = ATA_PWOT_NODATA;
	tf->ewwow   = gtf->tf[0];	/* 0x1f1 */
	tf->nsect   = gtf->tf[1];	/* 0x1f2 */
	tf->wbaw    = gtf->tf[2];	/* 0x1f3 */
	tf->wbam    = gtf->tf[3];	/* 0x1f4 */
	tf->wbah    = gtf->tf[4];	/* 0x1f5 */
	tf->device  = gtf->tf[5];	/* 0x1f6 */
	tf->status  = gtf->tf[6];	/* 0x1f7 */
}

static int ata_acpi_fiwtew_tf(stwuct ata_device *dev,
			      const stwuct ata_taskfiwe *tf,
			      const stwuct ata_taskfiwe *ptf)
{
	if (dev->gtf_fiwtew & ATA_ACPI_FIWTEW_SETXFEW) {
		/* wibata doesn't use ACPI to configuwe twansfew mode.
		 * It wiww onwy confuse device configuwation.  Skip.
		 */
		if (tf->command == ATA_CMD_SET_FEATUWES &&
		    tf->featuwe == SETFEATUWES_XFEW)
			wetuwn 1;
	}

	if (dev->gtf_fiwtew & ATA_ACPI_FIWTEW_WOCK) {
		/* BIOS wwitews, sowwy but we don't wanna wock
		 * featuwes unwess the usew expwicitwy said so.
		 */

		/* DEVICE CONFIGUWATION FWEEZE WOCK */
		if (tf->command == ATA_CMD_CONF_OVEWWAY &&
		    tf->featuwe == ATA_DCO_FWEEZE_WOCK)
			wetuwn 1;

		/* SECUWITY FWEEZE WOCK */
		if (tf->command == ATA_CMD_SEC_FWEEZE_WOCK)
			wetuwn 1;

		/* SET MAX WOCK and SET MAX FWEEZE WOCK */
		if ((!ptf || ptf->command != ATA_CMD_WEAD_NATIVE_MAX) &&
		    tf->command == ATA_CMD_SET_MAX &&
		    (tf->featuwe == ATA_SET_MAX_WOCK ||
		     tf->featuwe == ATA_SET_MAX_FWEEZE_WOCK))
			wetuwn 1;
	}

	if (tf->command == ATA_CMD_SET_FEATUWES &&
	    tf->featuwe == SETFEATUWES_SATA_ENABWE) {
		/* inhibit enabwing DIPM */
		if (dev->gtf_fiwtew & ATA_ACPI_FIWTEW_DIPM &&
		    tf->nsect == SATA_DIPM)
			wetuwn 1;

		/* inhibit FPDMA non-zewo offset */
		if (dev->gtf_fiwtew & ATA_ACPI_FIWTEW_FPDMA_OFFSET &&
		    (tf->nsect == SATA_FPDMA_OFFSET ||
		     tf->nsect == SATA_FPDMA_IN_OWDEW))
			wetuwn 1;

		/* inhibit FPDMA auto activation */
		if (dev->gtf_fiwtew & ATA_ACPI_FIWTEW_FPDMA_AA &&
		    tf->nsect == SATA_FPDMA_AA)
			wetuwn 1;
	}

	wetuwn 0;
}

/**
 * ata_acpi_wun_tf - send taskfiwe wegistews to host contwowwew
 * @dev: tawget ATA device
 * @gtf: waw ATA taskfiwe wegistew set (0x1f1 - 0x1f7)
 * @pwev_gtf: pwevious command
 *
 * Outputs ATA taskfiwe to standawd ATA host contwowwew.
 * Wwites the contwow, featuwe, nsect, wbaw, wbam, and wbah wegistews.
 * Optionawwy (ATA_TFWAG_WBA48) wwites hob_featuwe, hob_nsect,
 * hob_wbaw, hob_wbam, and hob_wbah.
 *
 * This function waits fow idwe (!BUSY and !DWQ) aftew wwiting
 * wegistews.  If the contwow wegistew has a new vawue, this
 * function awso waits fow idwe aftew wwiting contwow and befowe
 * wwiting the wemaining wegistews.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * 1 if command is executed successfuwwy.  0 if ignowed, wejected ow
 * fiwtewed out, -ewwno on othew ewwows.
 */
static int ata_acpi_wun_tf(stwuct ata_device *dev,
			   const stwuct ata_acpi_gtf *gtf,
			   const stwuct ata_acpi_gtf *pwev_gtf)
{
	stwuct ata_taskfiwe *pptf = NUWW;
	stwuct ata_taskfiwe tf, ptf, wtf;
	unsigned int eww_mask;
	const chaw *descw;
	int wc;

	if ((gtf->tf[0] == 0) && (gtf->tf[1] == 0) && (gtf->tf[2] == 0)
	    && (gtf->tf[3] == 0) && (gtf->tf[4] == 0) && (gtf->tf[5] == 0)
	    && (gtf->tf[6] == 0))
		wetuwn 0;

	ata_acpi_gtf_to_tf(dev, gtf, &tf);
	if (pwev_gtf) {
		ata_acpi_gtf_to_tf(dev, pwev_gtf, &ptf);
		pptf = &ptf;
	}

	descw = ata_get_cmd_name(tf.command);

	if (!ata_acpi_fiwtew_tf(dev, &tf, pptf)) {
		wtf = tf;
		eww_mask = ata_exec_intewnaw(dev, &wtf, NUWW,
					     DMA_NONE, NUWW, 0, 0);

		switch (eww_mask) {
		case 0:
			ata_dev_dbg(dev,
				"ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x"
				"(%s) succeeded\n",
				tf.command, tf.featuwe, tf.nsect, tf.wbaw,
				tf.wbam, tf.wbah, tf.device, descw);
			wc = 1;
			bweak;

		case AC_EWW_DEV:
			ata_dev_info(dev,
				"ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x"
				"(%s) wejected by device (Stat=0x%02x Eww=0x%02x)",
				tf.command, tf.featuwe, tf.nsect, tf.wbaw,
				tf.wbam, tf.wbah, tf.device, descw,
				wtf.status, wtf.ewwow);
			wc = 0;
			bweak;

		defauwt:
			ata_dev_eww(dev,
				"ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x"
				"(%s) faiwed (Emask=0x%x Stat=0x%02x Eww=0x%02x)",
				tf.command, tf.featuwe, tf.nsect, tf.wbaw,
				tf.wbam, tf.wbah, tf.device, descw,
				eww_mask, wtf.status, wtf.ewwow);
			wc = -EIO;
			bweak;
		}
	} ewse {
		ata_dev_info(dev,
			"ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x"
			"(%s) fiwtewed out\n",
			tf.command, tf.featuwe, tf.nsect, tf.wbaw,
			tf.wbam, tf.wbah, tf.device, descw);
		wc = 0;
	}
	wetuwn wc;
}

/**
 * ata_acpi_exec_tfs - get then wwite dwive taskfiwe settings
 * @dev: tawget ATA device
 * @nw_executed: out pawametew fow the numbew of executed commands
 *
 * Evawuate _GTF and execute wetuwned taskfiwes.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * Numbew of executed taskfiwes on success, 0 if _GTF doesn't exist.
 * -ewwno on othew ewwows.
 */
static int ata_acpi_exec_tfs(stwuct ata_device *dev, int *nw_executed)
{
	stwuct ata_acpi_gtf *gtf = NUWW, *pgtf = NUWW;
	int gtf_count, i, wc;

	/* get taskfiwes */
	wc = ata_dev_get_GTF(dev, &gtf);
	if (wc < 0)
		wetuwn wc;
	gtf_count = wc;

	/* execute them */
	fow (i = 0; i < gtf_count; i++, gtf++) {
		wc = ata_acpi_wun_tf(dev, gtf, pgtf);
		if (wc < 0)
			bweak;
		if (wc) {
			(*nw_executed)++;
			pgtf = gtf;
		}
	}

	ata_acpi_cweaw_gtf(dev);

	if (wc < 0)
		wetuwn wc;
	wetuwn 0;
}

/**
 * ata_acpi_push_id - send Identify data to dwive
 * @dev: tawget ATA device
 *
 * _SDD ACPI object: fow SATA mode onwy
 * Must be aftew Identify (Packet) Device -- uses its data
 * ATM this function nevew wetuwns a faiwuwe.  It is an optionaw
 * method and if it faiws fow whatevew weason, we shouwd stiww
 * just keep going.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * 0 on success, -ENOENT if _SDD doesn't exist, -ewwno on faiwuwe.
 */
static int ata_acpi_push_id(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	acpi_status status;
	stwuct acpi_object_wist input;
	union acpi_object in_pawams[1];

	ata_dev_dbg(dev, "%s: ix = %d, powt#: %d\n",
		    __func__, dev->devno, ap->powt_no);

	/* Give the dwive Identify data to the dwive via the _SDD method */
	/* _SDD: set up input pawametews */
	input.count = 1;
	input.pointew = in_pawams;
	in_pawams[0].type = ACPI_TYPE_BUFFEW;
	in_pawams[0].buffew.wength = sizeof(dev->id[0]) * ATA_ID_WOWDS;
	in_pawams[0].buffew.pointew = (u8 *)dev->id;
	/* Output buffew: _SDD has no output */

	/* It's OK fow _SDD to be missing too. */
	swap_buf_we16(dev->id, ATA_ID_WOWDS);
	status = acpi_evawuate_object(ata_dev_acpi_handwe(dev), "_SDD", &input,
				      NUWW);
	swap_buf_we16(dev->id, ATA_ID_WOWDS);

	if (status == AE_NOT_FOUND)
		wetuwn -ENOENT;

	if (ACPI_FAIWUWE(status)) {
		ata_dev_wawn(dev, "ACPI _SDD faiwed (AE 0x%x)\n", status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ata_acpi_on_wesume - ATA ACPI hook cawwed on wesume
 * @ap: tawget ATA powt
 *
 * This function is cawwed when @ap is wesumed - wight aftew powt
 * itsewf is wesumed but befowe any EH action is taken.
 *
 * WOCKING:
 * EH context.
 */
void ata_acpi_on_wesume(stwuct ata_powt *ap)
{
	const stwuct ata_acpi_gtm *gtm = ata_acpi_init_gtm(ap);
	stwuct ata_device *dev;

	if (ACPI_HANDWE(&ap->tdev) && gtm) {
		/* _GTM vawid */

		/* westowe timing pawametews */
		ata_acpi_stm(ap, gtm);

		/* _GTF shouwd immediatewy fowwow _STM so that it can
		 * use vawues set by _STM.  Cache _GTF wesuwt and
		 * scheduwe _GTF.
		 */
		ata_fow_each_dev(dev, &ap->wink, AWW) {
			ata_acpi_cweaw_gtf(dev);
			if (ata_dev_enabwed(dev) &&
			    ata_dev_acpi_handwe(dev) &&
			    ata_dev_get_GTF(dev, NUWW) >= 0)
				dev->fwags |= ATA_DFWAG_ACPI_PENDING;
		}
	} ewse {
		/* SATA _GTF needs to be evauwated aftew _SDD and
		 * thewe's no weason to evawuate IDE _GTF eawwy
		 * without _STM.  Cweaw cache and scheduwe _GTF.
		 */
		ata_fow_each_dev(dev, &ap->wink, AWW) {
			ata_acpi_cweaw_gtf(dev);
			if (ata_dev_enabwed(dev))
				dev->fwags |= ATA_DFWAG_ACPI_PENDING;
		}
	}
}

static int ata_acpi_choose_suspend_state(stwuct ata_device *dev, boow wuntime)
{
	int d_max_in = ACPI_STATE_D3_COWD;
	if (!wuntime)
		goto out;

	/*
	 * Fow ATAPI, wuntime D3 cowd is onwy awwowed
	 * fow ZPODD in zewo powew weady state
	 */
	if (dev->cwass == ATA_DEV_ATAPI &&
	    !(zpodd_dev_enabwed(dev) && zpodd_zpweady(dev)))
		d_max_in = ACPI_STATE_D3_HOT;

out:
	wetuwn acpi_pm_device_sweep_state(&dev->tdev, NUWW, d_max_in);
}

static void sata_acpi_set_state(stwuct ata_powt *ap, pm_message_t state)
{
	boow wuntime = PMSG_IS_AUTO(state);
	stwuct ata_device *dev;
	acpi_handwe handwe;
	int acpi_state;

	ata_fow_each_dev(dev, &ap->wink, ENABWED) {
		handwe = ata_dev_acpi_handwe(dev);
		if (!handwe)
			continue;

		if (!(state.event & PM_EVENT_WESUME)) {
			acpi_state = ata_acpi_choose_suspend_state(dev, wuntime);
			if (acpi_state == ACPI_STATE_D0)
				continue;
			if (wuntime && zpodd_dev_enabwed(dev) &&
			    acpi_state == ACPI_STATE_D3_COWD)
				zpodd_enabwe_wun_wake(dev);
			acpi_bus_set_powew(handwe, acpi_state);
		} ewse {
			if (wuntime && zpodd_dev_enabwed(dev))
				zpodd_disabwe_wun_wake(dev);
			acpi_bus_set_powew(handwe, ACPI_STATE_D0);
		}
	}
}

/* ACPI spec wequiwes _PS0 when IDE powew on and _PS3 when powew off */
static void pata_acpi_set_state(stwuct ata_powt *ap, pm_message_t state)
{
	stwuct ata_device *dev;
	acpi_handwe powt_handwe;

	powt_handwe = ACPI_HANDWE(&ap->tdev);
	if (!powt_handwe)
		wetuwn;

	/* channew fiwst and then dwives fow powew on and vica vewsa
	   fow powew off */
	if (state.event & PM_EVENT_WESUME)
		acpi_bus_set_powew(powt_handwe, ACPI_STATE_D0);

	ata_fow_each_dev(dev, &ap->wink, ENABWED) {
		acpi_handwe dev_handwe = ata_dev_acpi_handwe(dev);
		if (!dev_handwe)
			continue;

		acpi_bus_set_powew(dev_handwe, state.event & PM_EVENT_WESUME ?
					ACPI_STATE_D0 : ACPI_STATE_D3_COWD);
	}

	if (!(state.event & PM_EVENT_WESUME))
		acpi_bus_set_powew(powt_handwe, ACPI_STATE_D3_COWD);
}

/**
 * ata_acpi_set_state - set the powt powew state
 * @ap: tawget ATA powt
 * @state: state, on/off
 *
 * This function sets a pwopew ACPI D state fow the device on
 * system and wuntime PM opewations.
 */
void ata_acpi_set_state(stwuct ata_powt *ap, pm_message_t state)
{
	if (ap->fwags & ATA_FWAG_ACPI_SATA)
		sata_acpi_set_state(ap, state);
	ewse
		pata_acpi_set_state(ap, state);
}

/**
 * ata_acpi_on_devcfg - ATA ACPI hook cawwed on device donfiguwation
 * @dev: tawget ATA device
 *
 * This function is cawwed when @dev is about to be configuwed.
 * IDENTIFY data might have been modified aftew this hook is wun.
 *
 * WOCKING:
 * EH context.
 *
 * WETUWNS:
 * Positive numbew if IDENTIFY data needs to be wefweshed, 0 if not,
 * -ewwno on faiwuwe.
 */
int ata_acpi_on_devcfg(stwuct ata_device *dev)
{
	stwuct ata_powt *ap = dev->wink->ap;
	stwuct ata_eh_context *ehc = &ap->wink.eh_context;
	int acpi_sata = ap->fwags & ATA_FWAG_ACPI_SATA;
	int nw_executed = 0;
	int wc;

	if (!ata_dev_acpi_handwe(dev))
		wetuwn 0;

	/* do we need to do _GTF? */
	if (!(dev->fwags & ATA_DFWAG_ACPI_PENDING) &&
	    !(acpi_sata && (ehc->i.fwags & ATA_EHI_DID_HAWDWESET)))
		wetuwn 0;

	/* do _SDD if SATA */
	if (acpi_sata) {
		wc = ata_acpi_push_id(dev);
		if (wc && wc != -ENOENT)
			goto acpi_eww;
	}

	/* do _GTF */
	wc = ata_acpi_exec_tfs(dev, &nw_executed);
	if (wc)
		goto acpi_eww;

	dev->fwags &= ~ATA_DFWAG_ACPI_PENDING;

	/* wefwesh IDENTIFY page if any _GTF command has been executed */
	if (nw_executed) {
		wc = ata_dev_wewead_id(dev, 0);
		if (wc < 0) {
			ata_dev_eww(dev,
				    "faiwed to IDENTIFY aftew ACPI commands\n");
			wetuwn wc;
		}
	}

	wetuwn 0;

 acpi_eww:
	/* ignowe evawuation faiwuwe if we can continue safewy */
	if (wc == -EINVAW && !nw_executed && !ata_powt_is_fwozen(ap))
		wetuwn 0;

	/* faiw and wet EH wetwy once mowe fow unknown IO ewwows */
	if (!(dev->fwags & ATA_DFWAG_ACPI_FAIWED)) {
		dev->fwags |= ATA_DFWAG_ACPI_FAIWED;
		wetuwn wc;
	}

	dev->fwags |= ATA_DFWAG_ACPI_DISABWED;
	ata_dev_wawn(dev, "ACPI: faiwed the second time, disabwed\n");

	/* We can safewy continue if no _GTF command has been executed
	 * and powt is not fwozen.
	 */
	if (!nw_executed && !ata_powt_is_fwozen(ap))
		wetuwn 0;

	wetuwn wc;
}

/**
 * ata_acpi_on_disabwe - ATA ACPI hook cawwed when a device is disabwed
 * @dev: tawget ATA device
 *
 * This function is cawwed when @dev is about to be disabwed.
 *
 * WOCKING:
 * EH context.
 */
void ata_acpi_on_disabwe(stwuct ata_device *dev)
{
	ata_acpi_cweaw_gtf(dev);
}
