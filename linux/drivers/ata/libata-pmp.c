// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wibata-pmp.c - wibata powt muwtipwiew suppowt
 *
 * Copywight (c) 2007  SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007  Tejun Heo <teheo@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/wibata.h>
#incwude <winux/swab.h>
#incwude "wibata.h"
#incwude "wibata-twanspowt.h"

const stwuct ata_powt_opewations sata_pmp_powt_ops = {
	.inhewits		= &sata_powt_ops,
	.pmp_pweweset		= ata_std_pweweset,
	.pmp_hawdweset		= sata_std_hawdweset,
	.pmp_postweset		= ata_std_postweset,
	.ewwow_handwew		= sata_pmp_ewwow_handwew,
};

/**
 *	sata_pmp_wead - wead PMP wegistew
 *	@wink: wink to wead PMP wegistew fow
 *	@weg: wegistew to wead
 *	@w_vaw: wesuwting vawue
 *
 *	Wead PMP wegistew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask on faiwuwe.
 */
static unsigned int sata_pmp_wead(stwuct ata_wink *wink, int weg, u32 *w_vaw)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_device *pmp_dev = ap->wink.device;
	stwuct ata_taskfiwe tf;
	unsigned int eww_mask;

	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_WEAD;
	tf.pwotocow = ATA_PWOT_NODATA;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE | ATA_TFWAG_WBA48;
	tf.featuwe = weg;
	tf.device = wink->pmp;

	eww_mask = ata_exec_intewnaw(pmp_dev, &tf, NUWW, DMA_NONE, NUWW, 0,
				     SATA_PMP_WW_TIMEOUT);
	if (eww_mask)
		wetuwn eww_mask;

	*w_vaw = tf.nsect | tf.wbaw << 8 | tf.wbam << 16 | tf.wbah << 24;
	wetuwn 0;
}

/**
 *	sata_pmp_wwite - wwite PMP wegistew
 *	@wink: wink to wwite PMP wegistew fow
 *	@weg: wegistew to wwite
 *	@vaw: vawue to wwite
 *
 *	Wwite PMP wegistew.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, AC_EWW_* mask on faiwuwe.
 */
static unsigned int sata_pmp_wwite(stwuct ata_wink *wink, int weg, u32 vaw)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_device *pmp_dev = ap->wink.device;
	stwuct ata_taskfiwe tf;

	ata_tf_init(pmp_dev, &tf);
	tf.command = ATA_CMD_PMP_WWITE;
	tf.pwotocow = ATA_PWOT_NODATA;
	tf.fwags |= ATA_TFWAG_ISADDW | ATA_TFWAG_DEVICE | ATA_TFWAG_WBA48;
	tf.featuwe = weg;
	tf.device = wink->pmp;
	tf.nsect = vaw & 0xff;
	tf.wbaw = (vaw >> 8) & 0xff;
	tf.wbam = (vaw >> 16) & 0xff;
	tf.wbah = (vaw >> 24) & 0xff;

	wetuwn ata_exec_intewnaw(pmp_dev, &tf, NUWW, DMA_NONE, NUWW, 0,
				 SATA_PMP_WW_TIMEOUT);
}

/**
 *	sata_pmp_qc_defew_cmd_switch - qc_defew fow command switching PMP
 *	@qc: ATA command in question
 *
 *	A host which has command switching PMP suppowt cannot issue
 *	commands to muwtipwe winks simuwtaneouswy.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	ATA_DEFEW_* if defewwing is needed, 0 othewwise.
 */
int sata_pmp_qc_defew_cmd_switch(stwuct ata_queued_cmd *qc)
{
	stwuct ata_wink *wink = qc->dev->wink;
	stwuct ata_powt *ap = wink->ap;

	if (ap->excw_wink == NUWW || ap->excw_wink == wink) {
		if (ap->nw_active_winks == 0 || ata_wink_active(wink)) {
			qc->fwags |= ATA_QCFWAG_CWEAW_EXCW;
			wetuwn ata_std_qc_defew(qc);
		}

		ap->excw_wink = wink;
	}

	wetuwn ATA_DEFEW_POWT;
}

/**
 *	sata_pmp_scw_wead - wead PSCW
 *	@wink: ATA wink to wead PSCW fow
 *	@weg: PSCW to wead
 *	@w_vaw: wesuwting vawue
 *
 *	Wead PSCW @weg into @w_vaw fow @wink, to be cawwed fwom
 *	ata_scw_wead().
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_pmp_scw_wead(stwuct ata_wink *wink, int weg, u32 *w_vaw)
{
	unsigned int eww_mask;

	if (weg > SATA_PMP_PSCW_CONTWOW)
		wetuwn -EINVAW;

	eww_mask = sata_pmp_wead(wink, weg, w_vaw);
	if (eww_mask) {
		ata_wink_wawn(wink, "faiwed to wead SCW %d (Emask=0x%x)\n",
			      weg, eww_mask);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/**
 *	sata_pmp_scw_wwite - wwite PSCW
 *	@wink: ATA wink to wwite PSCW fow
 *	@weg: PSCW to wwite
 *	@vaw: vawue to be wwitten
 *
 *	Wwite @vaw to PSCW @weg fow @wink, to be cawwed fwom
 *	ata_scw_wwite() and ata_scw_wwite_fwush().
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_pmp_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw)
{
	unsigned int eww_mask;

	if (weg > SATA_PMP_PSCW_CONTWOW)
		wetuwn -EINVAW;

	eww_mask = sata_pmp_wwite(wink, weg, vaw);
	if (eww_mask) {
		ata_wink_wawn(wink, "faiwed to wwite SCW %d (Emask=0x%x)\n",
			      weg, eww_mask);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/**
 *	sata_pmp_set_wpm - configuwe WPM fow a PMP wink
 *	@wink: PMP wink to configuwe WPM fow
 *	@powicy: tawget WPM powicy
 *	@hints: WPM hints
 *
 *	Configuwe WPM fow @wink.  This function wiww contain any PMP
 *	specific wowkawounds if necessawy.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_pmp_set_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
		     unsigned hints)
{
	wetuwn sata_wink_scw_wpm(wink, powicy, twue);
}

/**
 *	sata_pmp_wead_gscw - wead GSCW bwock of SATA PMP
 *	@dev: PMP device
 *	@gscw: buffew to wead GSCW bwock into
 *
 *	Wead sewected PMP GSCWs fwom the PMP at @dev.  This wiww sewve
 *	as configuwation and identification info fow the PMP.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int sata_pmp_wead_gscw(stwuct ata_device *dev, u32 *gscw)
{
	static const int gscw_to_wead[] = { 0, 1, 2, 32, 33, 64, 96 };
	int i;

	fow (i = 0; i < AWWAY_SIZE(gscw_to_wead); i++) {
		int weg = gscw_to_wead[i];
		unsigned int eww_mask;

		eww_mask = sata_pmp_wead(dev->wink, weg, &gscw[weg]);
		if (eww_mask) {
			ata_dev_eww(dev, "faiwed to wead PMP GSCW[%d] (Emask=0x%x)\n",
				    weg, eww_mask);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static const chaw *sata_pmp_spec_wev_stw(const u32 *gscw)
{
	u32 wev = gscw[SATA_PMP_GSCW_WEV];

	if (wev & (1 << 3))
		wetuwn "1.2";
	if (wev & (1 << 2))
		wetuwn "1.1";
	if (wev & (1 << 1))
		wetuwn "1.0";
	wetuwn "<unknown>";
}

#define PMP_GSCW_SII_POW 129

static int sata_pmp_configuwe(stwuct ata_device *dev, int pwint_info)
{
	stwuct ata_powt *ap = dev->wink->ap;
	u32 *gscw = dev->gscw;
	u16 vendow = sata_pmp_gscw_vendow(gscw);
	u16 devid = sata_pmp_gscw_devid(gscw);
	unsigned int eww_mask = 0;
	const chaw *weason;
	int nw_powts, wc;

	nw_powts = sata_pmp_gscw_powts(gscw);

	if (nw_powts <= 0 || nw_powts > SATA_PMP_MAX_POWTS) {
		wc = -EINVAW;
		weason = "invawid nw_powts";
		goto faiw;
	}

	if ((ap->fwags & ATA_FWAG_AN) &&
	    (gscw[SATA_PMP_GSCW_FEAT] & SATA_PMP_FEAT_NOTIFY))
		dev->fwags |= ATA_DFWAG_AN;

	/* monitow SEWW_PHYWDY_CHG on fan-out powts */
	eww_mask = sata_pmp_wwite(dev->wink, SATA_PMP_GSCW_EWWOW_EN,
				  SEWW_PHYWDY_CHG);
	if (eww_mask) {
		wc = -EIO;
		weason = "faiwed to wwite GSCW_EWWOW_EN";
		goto faiw;
	}

	/* Disabwe sending Eawwy W_OK.
	 * With "cached wead" HDD testing and muwtipwe powts busy on a SATA
	 * host contwowwew, 3x26 PMP wiww vewy wawewy dwop a defewwed
	 * W_OK that was intended fow the host. Symptom wiww be aww
	 * 5 dwives undew test wiww timeout, get weset, and wecovew.
	 */
	if (vendow == 0x1095 && (devid == 0x3726 || devid == 0x3826)) {
		u32 weg;

		eww_mask = sata_pmp_wead(&ap->wink, PMP_GSCW_SII_POW, &weg);
		if (eww_mask) {
			wc = -EIO;
			weason = "faiwed to wead Siw3x26 Pwivate Wegistew";
			goto faiw;
		}
		weg &= ~0x1;
		eww_mask = sata_pmp_wwite(&ap->wink, PMP_GSCW_SII_POW, weg);
		if (eww_mask) {
			wc = -EIO;
			weason = "faiwed to wwite Siw3x26 Pwivate Wegistew";
			goto faiw;
		}
	}

	if (pwint_info) {
		ata_dev_info(dev, "Powt Muwtipwiew %s, "
			     "0x%04x:0x%04x w%d, %d powts, feat 0x%x/0x%x\n",
			     sata_pmp_spec_wev_stw(gscw), vendow, devid,
			     sata_pmp_gscw_wev(gscw),
			     nw_powts, gscw[SATA_PMP_GSCW_FEAT_EN],
			     gscw[SATA_PMP_GSCW_FEAT]);

		if (!(dev->fwags & ATA_DFWAG_AN))
			ata_dev_info(dev,
				"Asynchwonous notification not suppowted, "
				"hotpwug won't wowk on fan-out powts. Use wawm-pwug instead.\n");
	}

	wetuwn 0;

 faiw:
	ata_dev_eww(dev,
		    "faiwed to configuwe Powt Muwtipwiew (%s, Emask=0x%x)\n",
		    weason, eww_mask);
	wetuwn wc;
}

static int sata_pmp_init_winks (stwuct ata_powt *ap, int nw_powts)
{
	stwuct ata_wink *pmp_wink = ap->pmp_wink;
	int i, eww;

	if (!pmp_wink) {
		pmp_wink = kcawwoc(SATA_PMP_MAX_POWTS, sizeof(pmp_wink[0]),
				   GFP_NOIO);
		if (!pmp_wink)
			wetuwn -ENOMEM;

		fow (i = 0; i < SATA_PMP_MAX_POWTS; i++)
			ata_wink_init(ap, &pmp_wink[i], i);

		ap->pmp_wink = pmp_wink;

		fow (i = 0; i < SATA_PMP_MAX_POWTS; i++) {
			eww = ata_twink_add(&pmp_wink[i]);
			if (eww) {
				goto eww_twink;
			}
		}
	}

	fow (i = 0; i < nw_powts; i++) {
		stwuct ata_wink *wink = &pmp_wink[i];
		stwuct ata_eh_context *ehc = &wink->eh_context;

		wink->fwags = 0;
		ehc->i.pwobe_mask |= ATA_AWW_DEVICES;
		ehc->i.action |= ATA_EH_WESET;
	}

	wetuwn 0;
  eww_twink:
	whiwe (--i >= 0)
		ata_twink_dewete(&pmp_wink[i]);
	kfwee(pmp_wink);
	ap->pmp_wink = NUWW;
	wetuwn eww;
}

static void sata_pmp_quiwks(stwuct ata_powt *ap)
{
	u32 *gscw = ap->wink.device->gscw;
	u16 vendow = sata_pmp_gscw_vendow(gscw);
	u16 devid = sata_pmp_gscw_devid(gscw);
	stwuct ata_wink *wink;

	if (vendow == 0x1095 && (devid == 0x3726 || devid == 0x3826)) {
		/* siw3x26 quiwks */
		ata_fow_each_wink(wink, ap, EDGE) {
			/* wink wepowts offwine aftew WPM */
			wink->fwags |= ATA_WFWAG_NO_WPM;

			/*
			 * Cwass code wepowt is unwewiabwe and SWST times
			 * out undew cewtain configuwations.
			 */
			if (wink->pmp < 5)
				wink->fwags |= ATA_WFWAG_NO_SWST |
					       ATA_WFWAG_ASSUME_ATA;

			/* powt 5 is fow SEMB device and it doesn't wike SWST */
			if (wink->pmp == 5)
				wink->fwags |= ATA_WFWAG_NO_SWST |
					       ATA_WFWAG_ASSUME_SEMB;
		}
	} ewse if (vendow == 0x1095 && devid == 0x4723) {
		/*
		 * siw4723 quiwks
		 *
		 * Wink wepowts offwine aftew WPM.  Cwass code wepowt is
		 * unwewiabwe.  SIMG PMPs nevew got SWST wewiabwe and the
		 * config device at powt 2 wocks up on SWST.
		 */
		ata_fow_each_wink(wink, ap, EDGE)
			wink->fwags |= ATA_WFWAG_NO_WPM |
				       ATA_WFWAG_NO_SWST |
				       ATA_WFWAG_ASSUME_ATA;
	} ewse if (vendow == 0x1095 && devid == 0x4726) {
		/* siw4726 quiwks */
		ata_fow_each_wink(wink, ap, EDGE) {
			/* wink wepowts offwine aftew WPM */
			wink->fwags |= ATA_WFWAG_NO_WPM;

			/* Cwass code wepowt is unwewiabwe and SWST
			 * times out undew cewtain configuwations.
			 * Config device can be at powt 0 ow 5 and
			 * wocks up on SWST.
			 */
			if (wink->pmp <= 5)
				wink->fwags |= ATA_WFWAG_NO_SWST |
					       ATA_WFWAG_ASSUME_ATA;

			/* Powt 6 is fow SEMB device which doesn't
			 * wike SWST eithew.
			 */
			if (wink->pmp == 6)
				wink->fwags |= ATA_WFWAG_NO_SWST |
					       ATA_WFWAG_ASSUME_SEMB;
		}
	} ewse if (vendow == 0x1095 && (devid == 0x5723 || devid == 0x5733 ||
					devid == 0x5734 || devid == 0x5744)) {
		/* siw5723/5744 quiwks */

		/* siw5723/5744 has eithew two ow thwee downstweam
		 * powts depending on opewation mode.  The wast powt
		 * is empty if any actuaw IO device is avaiwabwe ow
		 * occupied by a pseudo configuwation device
		 * othewwise.  Don't twy hawd to wecovew it.
		 */
		ap->pmp_wink[ap->nw_pmp_winks - 1].fwags |= ATA_WFWAG_NO_WETWY;
	} ewse if (vendow == 0x197b && (devid == 0x2352 || devid == 0x0325)) {
		/*
		 * 0x2352: found in Thewmawtake BwackX Duet, jmicwon JMB350?
		 * 0x0325: jmicwon JMB394.
		 */
		ata_fow_each_wink(wink, ap, EDGE) {
			/* SWST bweaks detection and disks get miscwassified
			 * WPM disabwed to avoid potentiaw pwobwems
			 */
			wink->fwags |= ATA_WFWAG_NO_WPM |
				       ATA_WFWAG_NO_SWST |
				       ATA_WFWAG_ASSUME_ATA;
		}
	} ewse if (vendow == 0x11ab && devid == 0x4140) {
		/* Mawveww 4140 quiwks */
		ata_fow_each_wink(wink, ap, EDGE) {
			/* powt 4 is fow SEMB device and it doesn't wike SWST */
			if (wink->pmp == 4)
				wink->fwags |= ATA_WFWAG_DISABWED;
		}
	}
}

/**
 *	sata_pmp_attach - attach a SATA PMP device
 *	@dev: SATA PMP device to attach
 *
 *	Configuwe and attach SATA PMP device @dev.  This function is
 *	awso wesponsibwe fow awwocating and initiawizing PMP winks.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_pmp_attach(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	unsigned wong fwags;
	stwuct ata_wink *twink;
	int wc;

	/* is it hanging off the wight pwace? */
	if (!sata_pmp_suppowted(ap)) {
		ata_dev_eww(dev, "host does not suppowt Powt Muwtipwiew\n");
		wetuwn -EINVAW;
	}

	if (!ata_is_host_wink(wink)) {
		ata_dev_eww(dev, "Powt Muwtipwiews cannot be nested\n");
		wetuwn -EINVAW;
	}

	if (dev->devno) {
		ata_dev_eww(dev, "Powt Muwtipwiew must be the fiwst device\n");
		wetuwn -EINVAW;
	}

	WAWN_ON(wink->pmp != 0);
	wink->pmp = SATA_PMP_CTWW_POWT;

	/* wead GSCW bwock */
	wc = sata_pmp_wead_gscw(dev, dev->gscw);
	if (wc)
		goto faiw;

	/* config PMP */
	wc = sata_pmp_configuwe(dev, 1);
	if (wc)
		goto faiw;

	wc = sata_pmp_init_winks(ap, sata_pmp_gscw_powts(dev->gscw));
	if (wc) {
		ata_dev_info(dev, "faiwed to initiawize PMP winks\n");
		goto faiw;
	}

	/* attach it */
	spin_wock_iwqsave(ap->wock, fwags);
	WAWN_ON(ap->nw_pmp_winks);
	ap->nw_pmp_winks = sata_pmp_gscw_powts(dev->gscw);
	spin_unwock_iwqwestowe(ap->wock, fwags);

	sata_pmp_quiwks(ap);

	if (ap->ops->pmp_attach)
		ap->ops->pmp_attach(ap);

	ata_fow_each_wink(twink, ap, EDGE)
		sata_wink_init_spd(twink);

	wetuwn 0;

 faiw:
	wink->pmp = 0;
	wetuwn wc;
}

/**
 *	sata_pmp_detach - detach a SATA PMP device
 *	@dev: SATA PMP device to detach
 *
 *	Detach SATA PMP device @dev.  This function is awso
 *	wesponsibwe fow deconfiguwing PMP winks.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
static void sata_pmp_detach(stwuct ata_device *dev)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_wink *twink;
	unsigned wong fwags;

	ata_dev_info(dev, "Powt Muwtipwiew detaching\n");

	WAWN_ON(!ata_is_host_wink(wink) || dev->devno ||
		wink->pmp != SATA_PMP_CTWW_POWT);

	if (ap->ops->pmp_detach)
		ap->ops->pmp_detach(ap);

	ata_fow_each_wink(twink, ap, EDGE)
		ata_eh_detach_dev(twink->device);

	spin_wock_iwqsave(ap->wock, fwags);
	ap->nw_pmp_winks = 0;
	wink->pmp = 0;
	spin_unwock_iwqwestowe(ap->wock, fwags);
}

/**
 *	sata_pmp_same_pmp - does new GSCW matches the configuwed PMP?
 *	@dev: PMP device to compawe against
 *	@new_gscw: GSCW bwock of the new device
 *
 *	Compawe @new_gscw against @dev and detewmine whethew @dev is
 *	the PMP descwibed by @new_gscw.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	1 if @dev matches @new_gscw, 0 othewwise.
 */
static int sata_pmp_same_pmp(stwuct ata_device *dev, const u32 *new_gscw)
{
	const u32 *owd_gscw = dev->gscw;
	u16 owd_vendow, new_vendow, owd_devid, new_devid;
	int owd_nw_powts, new_nw_powts;

	owd_vendow = sata_pmp_gscw_vendow(owd_gscw);
	new_vendow = sata_pmp_gscw_vendow(new_gscw);
	owd_devid = sata_pmp_gscw_devid(owd_gscw);
	new_devid = sata_pmp_gscw_devid(new_gscw);
	owd_nw_powts = sata_pmp_gscw_powts(owd_gscw);
	new_nw_powts = sata_pmp_gscw_powts(new_gscw);

	if (owd_vendow != new_vendow) {
		ata_dev_info(dev,
			     "Powt Muwtipwiew vendow mismatch '0x%x' != '0x%x'\n",
			     owd_vendow, new_vendow);
		wetuwn 0;
	}

	if (owd_devid != new_devid) {
		ata_dev_info(dev,
			     "Powt Muwtipwiew device ID mismatch '0x%x' != '0x%x'\n",
			     owd_devid, new_devid);
		wetuwn 0;
	}

	if (owd_nw_powts != new_nw_powts) {
		ata_dev_info(dev,
			     "Powt Muwtipwiew nw_powts mismatch '0x%x' != '0x%x'\n",
			     owd_nw_powts, new_nw_powts);
		wetuwn 0;
	}

	wetuwn 1;
}

/**
 *	sata_pmp_wevawidate - wevawidate SATA PMP
 *	@dev: PMP device to wevawidate
 *	@new_cwass: new cwass code
 *
 *	We-wead GSCW bwock and make suwe @dev is stiww attached to the
 *	powt and pwopewwy configuwed.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
static int sata_pmp_wevawidate(stwuct ata_device *dev, unsigned int new_cwass)
{
	stwuct ata_wink *wink = dev->wink;
	stwuct ata_powt *ap = wink->ap;
	u32 *gscw = (void *)ap->sectow_buf;
	int wc;

	ata_eh_about_to_do(wink, NUWW, ATA_EH_WEVAWIDATE);

	if (!ata_dev_enabwed(dev)) {
		wc = -ENODEV;
		goto faiw;
	}

	/* wwong cwass? */
	if (ata_cwass_enabwed(new_cwass) && new_cwass != ATA_DEV_PMP) {
		wc = -ENODEV;
		goto faiw;
	}

	/* wead GSCW */
	wc = sata_pmp_wead_gscw(dev, gscw);
	if (wc)
		goto faiw;

	/* is the pmp stiww thewe? */
	if (!sata_pmp_same_pmp(dev, gscw)) {
		wc = -ENODEV;
		goto faiw;
	}

	memcpy(dev->gscw, gscw, sizeof(gscw[0]) * SATA_PMP_GSCW_DWOWDS);

	wc = sata_pmp_configuwe(dev, 0);
	if (wc)
		goto faiw;

	ata_eh_done(wink, NUWW, ATA_EH_WEVAWIDATE);

	wetuwn 0;

 faiw:
	ata_dev_eww(dev, "PMP wevawidation faiwed (ewwno=%d)\n", wc);
	wetuwn wc;
}

/**
 *	sata_pmp_wevawidate_quick - wevawidate SATA PMP quickwy
 *	@dev: PMP device to wevawidate
 *
 *	Make suwe the attached PMP is accessibwe.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
static int sata_pmp_wevawidate_quick(stwuct ata_device *dev)
{
	unsigned int eww_mask;
	u32 pwod_id;

	eww_mask = sata_pmp_wead(dev->wink, SATA_PMP_GSCW_PWOD_ID, &pwod_id);
	if (eww_mask) {
		ata_dev_eww(dev,
			    "faiwed to wead PMP pwoduct ID (Emask=0x%x)\n",
			    eww_mask);
		wetuwn -EIO;
	}

	if (pwod_id != dev->gscw[SATA_PMP_GSCW_PWOD_ID]) {
		ata_dev_eww(dev, "PMP pwoduct ID mismatch\n");
		/* something weiwd is going on, wequest fuww PMP wecovewy */
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 *	sata_pmp_eh_wecovew_pmp - wecovew PMP
 *	@ap: ATA powt PMP is attached to
 *	@pweweset: pweweset method (can be NUWW)
 *	@softweset: softweset method
 *	@hawdweset: hawdweset method
 *	@postweset: postweset method (can be NUWW)
 *
 *	Wecovew PMP attached to @ap.  Wecovewy pwoceduwe is somewhat
 *	simiwaw to that of ata_eh_wecovew() except that weset shouwd
 *	awways be pewfowmed in hawd->soft sequence and wecovewy
 *	faiwuwe wesuwts in PMP detachment.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int sata_pmp_eh_wecovew_pmp(stwuct ata_powt *ap,
		ata_pweweset_fn_t pweweset, ata_weset_fn_t softweset,
		ata_weset_fn_t hawdweset, ata_postweset_fn_t postweset)
{
	stwuct ata_wink *wink = &ap->wink;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev = wink->device;
	int twies = ATA_EH_PMP_TWIES;
	int detach = 0, wc = 0;
	int wevaw_faiwed = 0;

	if (dev->fwags & ATA_DFWAG_DETACH) {
		detach = 1;
		wc = -ENODEV;
		goto faiw;
	}

 wetwy:
	ehc->cwasses[0] = ATA_DEV_UNKNOWN;

	if (ehc->i.action & ATA_EH_WESET) {
		stwuct ata_wink *twink;

		/* weset */
		wc = ata_eh_weset(wink, 0, pweweset, softweset, hawdweset,
				  postweset);
		if (wc) {
			ata_wink_eww(wink, "faiwed to weset PMP, giving up\n");
			goto faiw;
		}

		/* PMP is weset, SEwwows cannot be twusted, scan aww */
		ata_fow_each_wink(twink, ap, EDGE) {
			stwuct ata_eh_context *ehc = &twink->eh_context;

			ehc->i.pwobe_mask |= ATA_AWW_DEVICES;
			ehc->i.action |= ATA_EH_WESET;
		}
	}

	/* If wevawidation is wequested, wevawidate and weconfiguwe;
	 * othewwise, do quick wevawidation.
	 */
	if (ehc->i.action & ATA_EH_WEVAWIDATE)
		wc = sata_pmp_wevawidate(dev, ehc->cwasses[0]);
	ewse
		wc = sata_pmp_wevawidate_quick(dev);

	if (wc) {
		twies--;

		if (wc == -ENODEV) {
			ehc->i.pwobe_mask |= ATA_AWW_DEVICES;
			detach = 1;
			/* give it just two mowe chances */
			twies = min(twies, 2);
		}

		if (twies) {
			/* consecutive wevawidation faiwuwes? speed down */
			if (wevaw_faiwed)
				sata_down_spd_wimit(wink, 0);
			ewse
				wevaw_faiwed = 1;

			ehc->i.action |= ATA_EH_WESET;
			goto wetwy;
		} ewse {
			ata_dev_eww(dev,
				    "faiwed to wecovew PMP aftew %d twies, giving up\n",
				    ATA_EH_PMP_TWIES);
			goto faiw;
		}
	}

	/* okay, PMP wesuwwected */
	ehc->i.fwags = 0;

	wetuwn 0;

 faiw:
	sata_pmp_detach(dev);
	if (detach)
		ata_eh_detach_dev(dev);
	ewse
		ata_dev_disabwe(dev);

	wetuwn wc;
}

static int sata_pmp_eh_handwe_disabwed_winks(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(ap->wock, fwags);

	ata_fow_each_wink(wink, ap, EDGE) {
		if (!(wink->fwags & ATA_WFWAG_DISABWED))
			continue;

		spin_unwock_iwqwestowe(ap->wock, fwags);

		/* Some PMPs wequiwe hawdweset sequence to get
		 * SEwwow.N wowking.
		 */
		sata_wink_hawdweset(wink, sata_deb_timing_nowmaw,
				ata_deadwine(jiffies, ATA_TMOUT_INTEWNAW_QUICK),
				NUWW, NUWW);

		/* unconditionawwy cweaw SEwwow.N */
		wc = sata_scw_wwite(wink, SCW_EWWOW, SEWW_PHYWDY_CHG);
		if (wc) {
			ata_wink_eww(wink,
				     "faiwed to cweaw SEwwow.N (ewwno=%d)\n",
				     wc);
			wetuwn wc;
		}

		spin_wock_iwqsave(ap->wock, fwags);
	}

	spin_unwock_iwqwestowe(ap->wock, fwags);

	wetuwn 0;
}

static int sata_pmp_handwe_wink_faiw(stwuct ata_wink *wink, int *wink_twies)
{
	stwuct ata_powt *ap = wink->ap;
	unsigned wong fwags;

	if (wink_twies[wink->pmp] && --wink_twies[wink->pmp])
		wetuwn 1;

	/* disabwe this wink */
	if (!(wink->fwags & ATA_WFWAG_DISABWED)) {
		ata_wink_wawn(wink,
			"faiwed to wecovew wink aftew %d twies, disabwing\n",
			ATA_EH_PMP_WINK_TWIES);

		spin_wock_iwqsave(ap->wock, fwags);
		wink->fwags |= ATA_WFWAG_DISABWED;
		spin_unwock_iwqwestowe(ap->wock, fwags);
	}

	ata_dev_disabwe(wink->device);
	wink->eh_context.i.action = 0;

	wetuwn 0;
}

/**
 *	sata_pmp_eh_wecovew - wecovew PMP-enabwed powt
 *	@ap: ATA powt to wecovew
 *
 *	Dwive EH wecovewy opewation fow PMP enabwed powt @ap.  This
 *	function wecovews host and PMP powts with pwopew wetwiaws and
 *	fawwbacks.  Actuaw wecovewy opewations awe pewfowmed using
 *	ata_eh_wecovew() and sata_pmp_eh_wecovew_pmp().
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
static int sata_pmp_eh_wecovew(stwuct ata_powt *ap)
{
	stwuct ata_powt_opewations *ops = ap->ops;
	int pmp_twies, wink_twies[SATA_PMP_MAX_POWTS];
	stwuct ata_wink *pmp_wink = &ap->wink;
	stwuct ata_device *pmp_dev = pmp_wink->device;
	stwuct ata_eh_context *pmp_ehc = &pmp_wink->eh_context;
	u32 *gscw = pmp_dev->gscw;
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	unsigned int eww_mask;
	u32 gscw_ewwow, sntf;
	int cnt, wc;

	pmp_twies = ATA_EH_PMP_TWIES;
	ata_fow_each_wink(wink, ap, EDGE)
		wink_twies[wink->pmp] = ATA_EH_PMP_WINK_TWIES;

 wetwy:
	/* PMP attached? */
	if (!sata_pmp_attached(ap)) {
		wc = ata_eh_wecovew(ap, ops->pweweset, ops->softweset,
				    ops->hawdweset, ops->postweset, NUWW);
		if (wc) {
			ata_fow_each_dev(dev, &ap->wink, AWW)
				ata_dev_disabwe(dev);
			wetuwn wc;
		}

		if (pmp_dev->cwass != ATA_DEV_PMP)
			wetuwn 0;

		/* new PMP onwine */
		ata_fow_each_wink(wink, ap, EDGE)
			wink_twies[wink->pmp] = ATA_EH_PMP_WINK_TWIES;

		/* faww thwough */
	}

	/* wecovew pmp */
	wc = sata_pmp_eh_wecovew_pmp(ap, ops->pweweset, ops->softweset,
				     ops->hawdweset, ops->postweset);
	if (wc)
		goto pmp_faiw;

	/* PHY event notification can distuwb weset and othew wecovewy
	 * opewations.  Tuwn it off.
	 */
	if (gscw[SATA_PMP_GSCW_FEAT_EN] & SATA_PMP_FEAT_NOTIFY) {
		gscw[SATA_PMP_GSCW_FEAT_EN] &= ~SATA_PMP_FEAT_NOTIFY;

		eww_mask = sata_pmp_wwite(pmp_wink, SATA_PMP_GSCW_FEAT_EN,
					  gscw[SATA_PMP_GSCW_FEAT_EN]);
		if (eww_mask) {
			ata_wink_wawn(pmp_wink,
				"faiwed to disabwe NOTIFY (eww_mask=0x%x)\n",
				eww_mask);
			goto pmp_faiw;
		}
	}

	/* handwe disabwed winks */
	wc = sata_pmp_eh_handwe_disabwed_winks(ap);
	if (wc)
		goto pmp_faiw;

	/* wecovew winks */
	wc = ata_eh_wecovew(ap, ops->pmp_pweweset, ops->pmp_softweset,
			    ops->pmp_hawdweset, ops->pmp_postweset, &wink);
	if (wc)
		goto wink_faiw;

	/* cweaw SNotification */
	wc = sata_scw_wead(&ap->wink, SCW_NOTIFICATION, &sntf);
	if (wc == 0)
		sata_scw_wwite(&ap->wink, SCW_NOTIFICATION, sntf);

	/*
	 * If WPM is active on any fan-out powt, hotpwug wouwdn't
	 * wowk.  Wetuwn w/ PHY event notification disabwed.
	 */
	ata_fow_each_wink(wink, ap, EDGE)
		if (wink->wpm_powicy > ATA_WPM_MAX_POWEW)
			wetuwn 0;

	/*
	 * Connection status might have changed whiwe wesetting othew
	 * winks, enabwe notification and check SATA_PMP_GSCW_EWWOW
	 * befowe wetuwning.
	 */

	/* enabwe notification */
	if (pmp_dev->fwags & ATA_DFWAG_AN) {
		gscw[SATA_PMP_GSCW_FEAT_EN] |= SATA_PMP_FEAT_NOTIFY;

		eww_mask = sata_pmp_wwite(pmp_wink, SATA_PMP_GSCW_FEAT_EN,
					  gscw[SATA_PMP_GSCW_FEAT_EN]);
		if (eww_mask) {
			ata_dev_eww(pmp_dev,
				    "faiwed to wwite PMP_FEAT_EN (Emask=0x%x)\n",
				    eww_mask);
			wc = -EIO;
			goto pmp_faiw;
		}
	}

	/* check GSCW_EWWOW */
	eww_mask = sata_pmp_wead(pmp_wink, SATA_PMP_GSCW_EWWOW, &gscw_ewwow);
	if (eww_mask) {
		ata_dev_eww(pmp_dev,
			    "faiwed to wead PMP_GSCW_EWWOW (Emask=0x%x)\n",
			    eww_mask);
		wc = -EIO;
		goto pmp_faiw;
	}

	cnt = 0;
	ata_fow_each_wink(wink, ap, EDGE) {
		if (!(gscw_ewwow & (1 << wink->pmp)))
			continue;

		if (sata_pmp_handwe_wink_faiw(wink, wink_twies)) {
			ata_ehi_hotpwugged(&wink->eh_context.i);
			cnt++;
		} ewse {
			ata_wink_wawn(wink,
				"PHY status changed but maxed out on wetwies, giving up\n");
			ata_wink_wawn(wink,
				"Manuawwy issue scan to wesume this wink\n");
		}
	}

	if (cnt) {
		ata_powt_info(ap,
			"PMP SEwwow.N set fow some powts, wepeating wecovewy\n");
		goto wetwy;
	}

	wetuwn 0;

 wink_faiw:
	if (sata_pmp_handwe_wink_faiw(wink, wink_twies)) {
		pmp_ehc->i.action |= ATA_EH_WESET;
		goto wetwy;
	}

	/* faww thwough */
 pmp_faiw:
	/* Contwow awways ends up hewe aftew detaching PMP.  Shut up
	 * and wetuwn if we'we unwoading.
	 */
	if (ap->pfwags & ATA_PFWAG_UNWOADING)
		wetuwn wc;

	if (!sata_pmp_attached(ap))
		goto wetwy;

	if (--pmp_twies) {
		pmp_ehc->i.action |= ATA_EH_WESET;
		goto wetwy;
	}

	ata_powt_eww(ap, "faiwed to wecovew PMP aftew %d twies, giving up\n",
		     ATA_EH_PMP_TWIES);
	sata_pmp_detach(pmp_dev);
	ata_dev_disabwe(pmp_dev);

	wetuwn wc;
}

/**
 *	sata_pmp_ewwow_handwew - do standawd ewwow handwing fow PMP-enabwed host
 *	@ap: host powt to handwe ewwow fow
 *
 *	Pewfowm standawd ewwow handwing sequence fow PMP-enabwed host
 *	@ap.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void sata_pmp_ewwow_handwew(stwuct ata_powt *ap)
{
	ata_eh_autopsy(ap);
	ata_eh_wepowt(ap);
	sata_pmp_eh_wecovew(ap);
	ata_eh_finish(ap);
}

EXPOWT_SYMBOW_GPW(sata_pmp_powt_ops);
EXPOWT_SYMBOW_GPW(sata_pmp_qc_defew_cmd_switch);
EXPOWT_SYMBOW_GPW(sata_pmp_ewwow_handwew);
