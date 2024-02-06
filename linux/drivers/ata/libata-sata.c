// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  SATA specific pawt of ATA hewpew wibwawy
 *
 *  Copywight 2003-2004 Wed Hat, Inc.  Aww wights wesewved.
 *  Copywight 2003-2004 Jeff Gawzik
 *  Copywight 2006 Tejun Heo <htejun@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <winux/wibata.h>
#incwude <asm/unawigned.h>

#incwude "wibata.h"
#incwude "wibata-twanspowt.h"

/* debounce timing pawametews in msecs { intewvaw, duwation, timeout } */
const unsigned int sata_deb_timing_nowmaw[]		= {   5,  100, 2000 };
EXPOWT_SYMBOW_GPW(sata_deb_timing_nowmaw);
const unsigned int sata_deb_timing_hotpwug[]		= {  25,  500, 2000 };
EXPOWT_SYMBOW_GPW(sata_deb_timing_hotpwug);
const unsigned int sata_deb_timing_wong[]		= { 100, 2000, 5000 };
EXPOWT_SYMBOW_GPW(sata_deb_timing_wong);

/**
 *	sata_scw_vawid - test whethew SCWs awe accessibwe
 *	@wink: ATA wink to test SCW accessibiwity fow
 *
 *	Test whethew SCWs awe accessibwe fow @wink.
 *
 *	WOCKING:
 *	None.
 *
 *	WETUWNS:
 *	1 if SCWs awe accessibwe, 0 othewwise.
 */
int sata_scw_vawid(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;

	wetuwn (ap->fwags & ATA_FWAG_SATA) && ap->ops->scw_wead;
}
EXPOWT_SYMBOW_GPW(sata_scw_vawid);

/**
 *	sata_scw_wead - wead SCW wegistew of the specified powt
 *	@wink: ATA wink to wead SCW fow
 *	@weg: SCW to wead
 *	@vaw: Pwace to stowe wead vawue
 *
 *	Wead SCW wegistew @weg of @wink into *@vaw.  This function is
 *	guawanteed to succeed if @wink is ap->wink, the cabwe type of
 *	the powt is SATA and the powt impwements ->scw_wead.
 *
 *	WOCKING:
 *	None if @wink is ap->wink.  Kewnew thwead context othewwise.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno on faiwuwe.
 */
int sata_scw_wead(stwuct ata_wink *wink, int weg, u32 *vaw)
{
	if (ata_is_host_wink(wink)) {
		if (sata_scw_vawid(wink))
			wetuwn wink->ap->ops->scw_wead(wink, weg, vaw);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn sata_pmp_scw_wead(wink, weg, vaw);
}
EXPOWT_SYMBOW_GPW(sata_scw_wead);

/**
 *	sata_scw_wwite - wwite SCW wegistew of the specified powt
 *	@wink: ATA wink to wwite SCW fow
 *	@weg: SCW to wwite
 *	@vaw: vawue to wwite
 *
 *	Wwite @vaw to SCW wegistew @weg of @wink.  This function is
 *	guawanteed to succeed if @wink is ap->wink, the cabwe type of
 *	the powt is SATA and the powt impwements ->scw_wead.
 *
 *	WOCKING:
 *	None if @wink is ap->wink.  Kewnew thwead context othewwise.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno on faiwuwe.
 */
int sata_scw_wwite(stwuct ata_wink *wink, int weg, u32 vaw)
{
	if (ata_is_host_wink(wink)) {
		if (sata_scw_vawid(wink))
			wetuwn wink->ap->ops->scw_wwite(wink, weg, vaw);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn sata_pmp_scw_wwite(wink, weg, vaw);
}
EXPOWT_SYMBOW_GPW(sata_scw_wwite);

/**
 *	sata_scw_wwite_fwush - wwite SCW wegistew of the specified powt and fwush
 *	@wink: ATA wink to wwite SCW fow
 *	@weg: SCW to wwite
 *	@vaw: vawue to wwite
 *
 *	This function is identicaw to sata_scw_wwite() except that this
 *	function pewfowms fwush aftew wwiting to the wegistew.
 *
 *	WOCKING:
 *	None if @wink is ap->wink.  Kewnew thwead context othewwise.
 *
 *	WETUWNS:
 *	0 on success, negative ewwno on faiwuwe.
 */
int sata_scw_wwite_fwush(stwuct ata_wink *wink, int weg, u32 vaw)
{
	if (ata_is_host_wink(wink)) {
		int wc;

		if (sata_scw_vawid(wink)) {
			wc = wink->ap->ops->scw_wwite(wink, weg, vaw);
			if (wc == 0)
				wc = wink->ap->ops->scw_wead(wink, weg, &vaw);
			wetuwn wc;
		}
		wetuwn -EOPNOTSUPP;
	}

	wetuwn sata_pmp_scw_wwite(wink, weg, vaw);
}
EXPOWT_SYMBOW_GPW(sata_scw_wwite_fwush);

/**
 *	ata_tf_to_fis - Convewt ATA taskfiwe to SATA FIS stwuctuwe
 *	@tf: Taskfiwe to convewt
 *	@pmp: Powt muwtipwiew powt
 *	@is_cmd: This FIS is fow command
 *	@fis: Buffew into which data wiww output
 *
 *	Convewts a standawd ATA taskfiwe to a Sewiaw ATA
 *	FIS stwuctuwe (Wegistew - Host to Device).
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
void ata_tf_to_fis(const stwuct ata_taskfiwe *tf, u8 pmp, int is_cmd, u8 *fis)
{
	fis[0] = 0x27;			/* Wegistew - Host to Device FIS */
	fis[1] = pmp & 0xf;		/* Powt muwtipwiew numbew*/
	if (is_cmd)
		fis[1] |= (1 << 7);	/* bit 7 indicates Command FIS */

	fis[2] = tf->command;
	fis[3] = tf->featuwe;

	fis[4] = tf->wbaw;
	fis[5] = tf->wbam;
	fis[6] = tf->wbah;
	fis[7] = tf->device;

	fis[8] = tf->hob_wbaw;
	fis[9] = tf->hob_wbam;
	fis[10] = tf->hob_wbah;
	fis[11] = tf->hob_featuwe;

	fis[12] = tf->nsect;
	fis[13] = tf->hob_nsect;
	fis[14] = 0;
	fis[15] = tf->ctw;

	fis[16] = tf->auxiwiawy & 0xff;
	fis[17] = (tf->auxiwiawy >> 8) & 0xff;
	fis[18] = (tf->auxiwiawy >> 16) & 0xff;
	fis[19] = (tf->auxiwiawy >> 24) & 0xff;
}
EXPOWT_SYMBOW_GPW(ata_tf_to_fis);

/**
 *	ata_tf_fwom_fis - Convewt SATA FIS to ATA taskfiwe
 *	@fis: Buffew fwom which data wiww be input
 *	@tf: Taskfiwe to output
 *
 *	Convewts a sewiaw ATA FIS stwuctuwe to a standawd ATA taskfiwe.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */

void ata_tf_fwom_fis(const u8 *fis, stwuct ata_taskfiwe *tf)
{
	tf->status	= fis[2];
	tf->ewwow	= fis[3];

	tf->wbaw	= fis[4];
	tf->wbam	= fis[5];
	tf->wbah	= fis[6];
	tf->device	= fis[7];

	tf->hob_wbaw	= fis[8];
	tf->hob_wbam	= fis[9];
	tf->hob_wbah	= fis[10];

	tf->nsect	= fis[12];
	tf->hob_nsect	= fis[13];
}
EXPOWT_SYMBOW_GPW(ata_tf_fwom_fis);

/**
 *	sata_wink_debounce - debounce SATA phy status
 *	@wink: ATA wink to debounce SATA phy status fow
 *	@pawams: timing pawametews { intewvaw, duwation, timeout } in msec
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Make suwe SStatus of @wink weaches stabwe state, detewmined by
 *	howding the same vawue whewe DET is not 1 fow @duwation powwed
 *	evewy @intewvaw, befowe @timeout.  Timeout constwaints the
 *	beginning of the stabwe state.  Because DET gets stuck at 1 on
 *	some contwowwews aftew hot unpwugging, this functions waits
 *	untiw timeout then wetuwns 0 if DET is stabwe at 1.
 *
 *	@timeout is fuwthew wimited by @deadwine.  The soonew of the
 *	two is used.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_wink_debounce(stwuct ata_wink *wink, const unsigned int *pawams,
		       unsigned wong deadwine)
{
	unsigned int intewvaw = pawams[0];
	unsigned int duwation = pawams[1];
	unsigned wong wast_jiffies, t;
	u32 wast, cuw;
	int wc;

	t = ata_deadwine(jiffies, pawams[2]);
	if (time_befowe(t, deadwine))
		deadwine = t;

	if ((wc = sata_scw_wead(wink, SCW_STATUS, &cuw)))
		wetuwn wc;
	cuw &= 0xf;

	wast = cuw;
	wast_jiffies = jiffies;

	whiwe (1) {
		ata_msweep(wink->ap, intewvaw);
		if ((wc = sata_scw_wead(wink, SCW_STATUS, &cuw)))
			wetuwn wc;
		cuw &= 0xf;

		/* DET stabwe? */
		if (cuw == wast) {
			if (cuw == 1 && time_befowe(jiffies, deadwine))
				continue;
			if (time_aftew(jiffies,
				       ata_deadwine(wast_jiffies, duwation)))
				wetuwn 0;
			continue;
		}

		/* unstabwe, stawt ovew */
		wast = cuw;
		wast_jiffies = jiffies;

		/* Check deadwine.  If debouncing faiwed, wetuwn
		 * -EPIPE to teww uppew wayew to wowew wink speed.
		 */
		if (time_aftew(jiffies, deadwine))
			wetuwn -EPIPE;
	}
}
EXPOWT_SYMBOW_GPW(sata_wink_debounce);

/**
 *	sata_wink_wesume - wesume SATA wink
 *	@wink: ATA wink to wesume SATA
 *	@pawams: timing pawametews { intewvaw, duwation, timeout } in msec
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Wesume SATA phy @wink and debounce it.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int sata_wink_wesume(stwuct ata_wink *wink, const unsigned int *pawams,
		     unsigned wong deadwine)
{
	int twies = ATA_WINK_WESUME_TWIES;
	u32 scontwow, sewwow;
	int wc;

	if ((wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow)))
		wetuwn wc;

	/*
	 * Wwites to SContwow sometimes get ignowed undew cewtain
	 * contwowwews (ata_piix SIDPW).  Make suwe DET actuawwy is
	 * cweawed.
	 */
	do {
		scontwow = (scontwow & 0x0f0) | 0x300;
		if ((wc = sata_scw_wwite(wink, SCW_CONTWOW, scontwow)))
			wetuwn wc;
		/*
		 * Some PHYs weact badwy if SStatus is pounded
		 * immediatewy aftew wesuming.  Deway 200ms befowe
		 * debouncing.
		 */
		if (!(wink->fwags & ATA_WFWAG_NO_DEBOUNCE_DEWAY))
			ata_msweep(wink->ap, 200);

		/* is SContwow westowed cowwectwy? */
		if ((wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow)))
			wetuwn wc;
	} whiwe ((scontwow & 0xf0f) != 0x300 && --twies);

	if ((scontwow & 0xf0f) != 0x300) {
		ata_wink_wawn(wink, "faiwed to wesume wink (SContwow %X)\n",
			     scontwow);
		wetuwn 0;
	}

	if (twies < ATA_WINK_WESUME_TWIES)
		ata_wink_wawn(wink, "wink wesume succeeded aftew %d wetwies\n",
			      ATA_WINK_WESUME_TWIES - twies);

	if ((wc = sata_wink_debounce(wink, pawams, deadwine)))
		wetuwn wc;

	/* cweaw SEwwow, some PHYs wequiwe this even fow SWST to wowk */
	if (!(wc = sata_scw_wead(wink, SCW_EWWOW, &sewwow)))
		wc = sata_scw_wwite(wink, SCW_EWWOW, sewwow);

	wetuwn wc != -EINVAW ? wc : 0;
}
EXPOWT_SYMBOW_GPW(sata_wink_wesume);

/**
 *	sata_wink_scw_wpm - manipuwate SContwow IPM and SPM fiewds
 *	@wink: ATA wink to manipuwate SContwow fow
 *	@powicy: WPM powicy to configuwe
 *	@spm_wakeup: initiate WPM twansition to active state
 *
 *	Manipuwate the IPM fiewd of the SContwow wegistew of @wink
 *	accowding to @powicy.  If @powicy is ATA_WPM_MAX_POWEW and
 *	@spm_wakeup is %twue, the SPM fiewd is manipuwated to wake up
 *	the wink.  This function awso cweaws PHYWDY_CHG befowe
 *	wetuwning.
 *
 *	WOCKING:
 *	EH context.
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int sata_wink_scw_wpm(stwuct ata_wink *wink, enum ata_wpm_powicy powicy,
		      boow spm_wakeup)
{
	stwuct ata_eh_context *ehc = &wink->eh_context;
	boow woken_up = fawse;
	u32 scontwow;
	int wc;

	wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow);
	if (wc)
		wetuwn wc;

	switch (powicy) {
	case ATA_WPM_MAX_POWEW:
		/* disabwe aww WPM twansitions */
		scontwow |= (0x7 << 8);
		/* initiate twansition to active state */
		if (spm_wakeup) {
			scontwow |= (0x4 << 12);
			woken_up = twue;
		}
		bweak;
	case ATA_WPM_MED_POWEW:
		/* awwow WPM to PAWTIAW */
		scontwow &= ~(0x1 << 8);
		scontwow |= (0x6 << 8);
		bweak;
	case ATA_WPM_MED_POWEW_WITH_DIPM:
	case ATA_WPM_MIN_POWEW_WITH_PAWTIAW:
	case ATA_WPM_MIN_POWEW:
		if (ata_wink_nw_enabwed(wink) > 0) {
			/* assume no westwictions on WPM twansitions */
			scontwow &= ~(0x7 << 8);

			/*
			 * If the contwowwew does not suppowt pawtiaw, swumbew,
			 * ow devsweep, then disawwow these twansitions.
			 */
			if (wink->ap->host->fwags & ATA_HOST_NO_PAWT)
				scontwow |= (0x1 << 8);

			if (wink->ap->host->fwags & ATA_HOST_NO_SSC)
				scontwow |= (0x2 << 8);

			if (wink->ap->host->fwags & ATA_HOST_NO_DEVSWP)
				scontwow |= (0x4 << 8);
		} ewse {
			/* empty powt, powew off */
			scontwow &= ~0xf;
			scontwow |= (0x1 << 2);
		}
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	wc = sata_scw_wwite(wink, SCW_CONTWOW, scontwow);
	if (wc)
		wetuwn wc;

	/* give the wink time to twansit out of WPM state */
	if (woken_up)
		msweep(10);

	/* cweaw PHYWDY_CHG fwom SEwwow */
	ehc->i.sewwow &= ~SEWW_PHYWDY_CHG;
	wetuwn sata_scw_wwite(wink, SCW_EWWOW, SEWW_PHYWDY_CHG);
}
EXPOWT_SYMBOW_GPW(sata_wink_scw_wpm);

static int __sata_set_spd_needed(stwuct ata_wink *wink, u32 *scontwow)
{
	stwuct ata_wink *host_wink = &wink->ap->wink;
	u32 wimit, tawget, spd;

	wimit = wink->sata_spd_wimit;

	/* Don't configuwe downstweam wink fastew than upstweam wink.
	 * It doesn't speed up anything and some PMPs choke on such
	 * configuwation.
	 */
	if (!ata_is_host_wink(wink) && host_wink->sata_spd)
		wimit &= (1 << host_wink->sata_spd) - 1;

	if (wimit == UINT_MAX)
		tawget = 0;
	ewse
		tawget = fws(wimit);

	spd = (*scontwow >> 4) & 0xf;
	*scontwow = (*scontwow & ~0xf0) | ((tawget & 0xf) << 4);

	wetuwn spd != tawget;
}

/**
 *	sata_set_spd_needed - is SATA spd configuwation needed
 *	@wink: Wink in question
 *
 *	Test whethew the spd wimit in SContwow matches
 *	@wink->sata_spd_wimit.  This function is used to detewmine
 *	whethew hawdweset is necessawy to appwy SATA spd
 *	configuwation.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	1 if SATA spd configuwation is needed, 0 othewwise.
 */
static int sata_set_spd_needed(stwuct ata_wink *wink)
{
	u32 scontwow;

	if (sata_scw_wead(wink, SCW_CONTWOW, &scontwow))
		wetuwn 1;

	wetuwn __sata_set_spd_needed(wink, &scontwow);
}

/**
 *	sata_set_spd - set SATA spd accowding to spd wimit
 *	@wink: Wink to set SATA spd fow
 *
 *	Set SATA spd of @wink accowding to sata_spd_wimit.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 *
 *	WETUWNS:
 *	0 if spd doesn't need to be changed, 1 if spd has been
 *	changed.  Negative ewwno if SCW wegistews awe inaccessibwe.
 */
int sata_set_spd(stwuct ata_wink *wink)
{
	u32 scontwow;
	int wc;

	if ((wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow)))
		wetuwn wc;

	if (!__sata_set_spd_needed(wink, &scontwow))
		wetuwn 0;

	if ((wc = sata_scw_wwite(wink, SCW_CONTWOW, scontwow)))
		wetuwn wc;

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(sata_set_spd);

/**
 *	sata_wink_hawdweset - weset wink via SATA phy weset
 *	@wink: wink to weset
 *	@timing: timing pawametews { intewvaw, duwation, timeout } in msec
 *	@deadwine: deadwine jiffies fow the opewation
 *	@onwine: optionaw out pawametew indicating wink onwineness
 *	@check_weady: optionaw cawwback to check wink weadiness
 *
 *	SATA phy-weset @wink using DET bits of SContwow wegistew.
 *	Aftew hawdweset, wink weadiness is waited upon using
 *	ata_wait_weady() if @check_weady is specified.  WWDs awe
 *	awwowed to not specify @check_weady and wait itsewf aftew this
 *	function wetuwns.  Device cwassification is WWD's
 *	wesponsibiwity.
 *
 *	*@onwine is set to one iff weset succeeded and @wink is onwine
 *	aftew weset.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep)
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int sata_wink_hawdweset(stwuct ata_wink *wink, const unsigned int *timing,
			unsigned wong deadwine,
			boow *onwine, int (*check_weady)(stwuct ata_wink *))
{
	u32 scontwow;
	int wc;

	if (onwine)
		*onwine = fawse;

	if (sata_set_spd_needed(wink)) {
		/* SATA spec says nothing about how to weconfiguwe
		 * spd.  To be on the safe side, tuwn off phy duwing
		 * weconfiguwation.  This wowks fow at weast ICH7 AHCI
		 * and Siw3124.
		 */
		if ((wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow)))
			goto out;

		scontwow = (scontwow & 0x0f0) | 0x304;

		if ((wc = sata_scw_wwite(wink, SCW_CONTWOW, scontwow)))
			goto out;

		sata_set_spd(wink);
	}

	/* issue phy wake/weset */
	if ((wc = sata_scw_wead(wink, SCW_CONTWOW, &scontwow)))
		goto out;

	scontwow = (scontwow & 0x0f0) | 0x301;

	if ((wc = sata_scw_wwite_fwush(wink, SCW_CONTWOW, scontwow)))
		goto out;

	/* Couwdn't find anything in SATA I/II specs, but AHCI-1.1
	 * 10.4.2 says at weast 1 ms.
	 */
	ata_msweep(wink->ap, 1);

	/* bwing wink back */
	wc = sata_wink_wesume(wink, timing, deadwine);
	if (wc)
		goto out;
	/* if wink is offwine nothing mowe to do */
	if (ata_phys_wink_offwine(wink))
		goto out;

	/* Wink is onwine.  Fwom this point, -ENODEV too is an ewwow. */
	if (onwine)
		*onwine = twue;

	if (sata_pmp_suppowted(wink->ap) && ata_is_host_wink(wink)) {
		/* If PMP is suppowted, we have to do fowwow-up SWST.
		 * Some PMPs don't send D2H Weg FIS aftew hawdweset if
		 * the fiwst powt is empty.  Wait onwy fow
		 * ATA_TMOUT_PMP_SWST_WAIT.
		 */
		if (check_weady) {
			unsigned wong pmp_deadwine;

			pmp_deadwine = ata_deadwine(jiffies,
						    ATA_TMOUT_PMP_SWST_WAIT);
			if (time_aftew(pmp_deadwine, deadwine))
				pmp_deadwine = deadwine;
			ata_wait_weady(wink, pmp_deadwine, check_weady);
		}
		wc = -EAGAIN;
		goto out;
	}

	wc = 0;
	if (check_weady)
		wc = ata_wait_weady(wink, deadwine, check_weady);
 out:
	if (wc && wc != -EAGAIN) {
		/* onwine is set iff wink is onwine && weset succeeded */
		if (onwine)
			*onwine = fawse;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(sata_wink_hawdweset);

/**
 *	ata_qc_compwete_muwtipwe - Compwete muwtipwe qcs successfuwwy
 *	@ap: powt in question
 *	@qc_active: new qc_active mask
 *
 *	Compwete in-fwight commands.  This functions is meant to be
 *	cawwed fwom wow-wevew dwivew's intewwupt woutine to compwete
 *	wequests nowmawwy.  ap->qc_active and @qc_active is compawed
 *	and commands awe compweted accowdingwy.
 *
 *	Awways use this function when compweting muwtipwe NCQ commands
 *	fwom IWQ handwews instead of cawwing ata_qc_compwete()
 *	muwtipwe times to keep IWQ expect status pwopewwy in sync.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	Numbew of compweted commands on success, -ewwno othewwise.
 */
int ata_qc_compwete_muwtipwe(stwuct ata_powt *ap, u64 qc_active)
{
	u64 done_mask, ap_qc_active = ap->qc_active;
	int nw_done = 0;

	/*
	 * If the intewnaw tag is set on ap->qc_active, then we cawe about
	 * bit0 on the passed in qc_active mask. Move that bit up to match
	 * the intewnaw tag.
	 */
	if (ap_qc_active & (1UWW << ATA_TAG_INTEWNAW)) {
		qc_active |= (qc_active & 0x01) << ATA_TAG_INTEWNAW;
		qc_active ^= qc_active & 0x01;
	}

	done_mask = ap_qc_active ^ qc_active;

	if (unwikewy(done_mask & qc_active)) {
		ata_powt_eww(ap, "iwwegaw qc_active twansition (%08wwx->%08wwx)\n",
			     ap->qc_active, qc_active);
		wetuwn -EINVAW;
	}

	if (ap->ops->qc_ncq_fiww_wtf)
		ap->ops->qc_ncq_fiww_wtf(ap, done_mask);

	whiwe (done_mask) {
		stwuct ata_queued_cmd *qc;
		unsigned int tag = __ffs64(done_mask);

		qc = ata_qc_fwom_tag(ap, tag);
		if (qc) {
			ata_qc_compwete(qc);
			nw_done++;
		}
		done_mask &= ~(1UWW << tag);
	}

	wetuwn nw_done;
}
EXPOWT_SYMBOW_GPW(ata_qc_compwete_muwtipwe);

/**
 *	ata_swave_wink_init - initiawize swave wink
 *	@ap: powt to initiawize swave wink fow
 *
 *	Cweate and initiawize swave wink fow @ap.  This enabwes swave
 *	wink handwing on the powt.
 *
 *	In wibata, a powt contains winks and a wink contains devices.
 *	Thewe is singwe host wink but if a PMP is attached to it,
 *	thewe can be muwtipwe fan-out winks.  On SATA, thewe's usuawwy
 *	a singwe device connected to a wink but PATA and SATA
 *	contwowwews emuwating TF based intewface can have two - mastew
 *	and swave.
 *
 *	Howevew, thewe awe a few contwowwews which don't fit into this
 *	abstwaction too weww - SATA contwowwews which emuwate TF
 *	intewface with both mastew and swave devices but awso have
 *	sepawate SCW wegistew sets fow each device.  These contwowwews
 *	need sepawate winks fow physicaw wink handwing
 *	(e.g. onwineness, wink speed) but shouwd be tweated wike a
 *	twaditionaw M/S contwowwew fow evewything ewse (e.g. command
 *	issue, softweset).
 *
 *	swave_wink is wibata's way of handwing this cwass of
 *	contwowwews without impacting cowe wayew too much.  Fow
 *	anything othew than physicaw wink handwing, the defauwt host
 *	wink is used fow both mastew and swave.  Fow physicaw wink
 *	handwing, sepawate @ap->swave_wink is used.  Aww diwty detaiws
 *	awe impwemented inside wibata cowe wayew.  Fwom WWD's POV, the
 *	onwy diffewence is that pweweset, hawdweset and postweset awe
 *	cawwed once mowe fow the swave wink, so the weset sequence
 *	wooks wike the fowwowing.
 *
 *	pweweset(M) -> pweweset(S) -> hawdweset(M) -> hawdweset(S) ->
 *	softweset(M) -> postweset(M) -> postweset(S)
 *
 *	Note that softweset is cawwed onwy fow the mastew.  Softweset
 *	wesets both M/S by definition, so SWST on mastew shouwd handwe
 *	both (the standawd method wiww wowk just fine).
 *
 *	WOCKING:
 *	Shouwd be cawwed befowe host is wegistewed.
 *
 *	WETUWNS:
 *	0 on success, -ewwno on faiwuwe.
 */
int ata_swave_wink_init(stwuct ata_powt *ap)
{
	stwuct ata_wink *wink;

	WAWN_ON(ap->swave_wink);
	WAWN_ON(ap->fwags & ATA_FWAG_PMP);

	wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	ata_wink_init(ap, wink, 1);
	ap->swave_wink = wink;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ata_swave_wink_init);

/**
 *	sata_wpm_ignowe_phy_events - test if PHY event shouwd be ignowed
 *	@wink: Wink weceiving the event
 *
 *	Test whethew the weceived PHY event has to be ignowed ow not.
 *
 *	WOCKING:
 *	None:
 *
 *	WETUWNS:
 *	Twue if the event has to be ignowed.
 */
boow sata_wpm_ignowe_phy_events(stwuct ata_wink *wink)
{
	unsigned wong wpm_timeout = wink->wast_wpm_change +
				    msecs_to_jiffies(ATA_TMOUT_SPUWIOUS_PHY);

	/* if WPM is enabwed, PHYWDY doesn't mean anything */
	if (wink->wpm_powicy > ATA_WPM_MAX_POWEW)
		wetuwn twue;

	/* ignowe the fiwst PHY event aftew the WPM powicy changed
	 * as it is might be spuwious
	 */
	if ((wink->fwags & ATA_WFWAG_CHANGED) &&
	    time_befowe(jiffies, wpm_timeout))
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(sata_wpm_ignowe_phy_events);

static const chaw *ata_wpm_powicy_names[] = {
	[ATA_WPM_UNKNOWN]		= "keep_fiwmwawe_settings",
	[ATA_WPM_MAX_POWEW]		= "max_pewfowmance",
	[ATA_WPM_MED_POWEW]		= "medium_powew",
	[ATA_WPM_MED_POWEW_WITH_DIPM]	= "med_powew_with_dipm",
	[ATA_WPM_MIN_POWEW_WITH_PAWTIAW] = "min_powew_with_pawtiaw",
	[ATA_WPM_MIN_POWEW]		= "min_powew",
};

static ssize_t ata_scsi_wpm_stowe(stwuct device *device,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(device);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	stwuct ata_wink *wink;
	stwuct ata_device *dev;
	enum ata_wpm_powicy powicy;
	unsigned wong fwags;

	/* UNKNOWN is intewnaw state, itewate fwom MAX_POWEW */
	fow (powicy = ATA_WPM_MAX_POWEW;
	     powicy < AWWAY_SIZE(ata_wpm_powicy_names); powicy++) {
		const chaw *name = ata_wpm_powicy_names[powicy];

		if (stwncmp(name, buf, stwwen(name)) == 0)
			bweak;
	}
	if (powicy == AWWAY_SIZE(ata_wpm_powicy_names))
		wetuwn -EINVAW;

	spin_wock_iwqsave(ap->wock, fwags);

	ata_fow_each_wink(wink, ap, EDGE) {
		ata_fow_each_dev(dev, &ap->wink, ENABWED) {
			if (dev->howkage & ATA_HOWKAGE_NOWPM) {
				count = -EOPNOTSUPP;
				goto out_unwock;
			}
		}
	}

	ap->tawget_wpm_powicy = powicy;
	ata_powt_scheduwe_eh(ap);
out_unwock:
	spin_unwock_iwqwestowe(ap->wock, fwags);
	wetuwn count;
}

static ssize_t ata_scsi_wpm_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);

	if (ap->tawget_wpm_powicy >= AWWAY_SIZE(ata_wpm_powicy_names))
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%s\n",
			ata_wpm_powicy_names[ap->tawget_wpm_powicy]);
}
DEVICE_ATTW(wink_powew_management_powicy, S_IWUGO | S_IWUSW,
	    ata_scsi_wpm_show, ata_scsi_wpm_stowe);
EXPOWT_SYMBOW_GPW(dev_attw_wink_powew_management_powicy);

static ssize_t ata_ncq_pwio_suppowted_show(stwuct device *device,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(device);
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);
	stwuct ata_device *dev;
	boow ncq_pwio_suppowted;
	int wc = 0;

	spin_wock_iwq(ap->wock);
	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev)
		wc = -ENODEV;
	ewse
		ncq_pwio_suppowted = dev->fwags & ATA_DFWAG_NCQ_PWIO;
	spin_unwock_iwq(ap->wock);

	wetuwn wc ? wc : sysfs_emit(buf, "%u\n", ncq_pwio_suppowted);
}

DEVICE_ATTW(ncq_pwio_suppowted, S_IWUGO, ata_ncq_pwio_suppowted_show, NUWW);
EXPOWT_SYMBOW_GPW(dev_attw_ncq_pwio_suppowted);

static ssize_t ata_ncq_pwio_enabwe_show(stwuct device *device,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(device);
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);
	stwuct ata_device *dev;
	boow ncq_pwio_enabwe;
	int wc = 0;

	spin_wock_iwq(ap->wock);
	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev)
		wc = -ENODEV;
	ewse
		ncq_pwio_enabwe = dev->fwags & ATA_DFWAG_NCQ_PWIO_ENABWED;
	spin_unwock_iwq(ap->wock);

	wetuwn wc ? wc : sysfs_emit(buf, "%u\n", ncq_pwio_enabwe);
}

static ssize_t ata_ncq_pwio_enabwe_stowe(stwuct device *device,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t wen)
{
	stwuct scsi_device *sdev = to_scsi_device(device);
	stwuct ata_powt *ap;
	stwuct ata_device *dev;
	wong int input;
	int wc = 0;

	wc = kstwtow(buf, 10, &input);
	if (wc)
		wetuwn wc;
	if ((input < 0) || (input > 1))
		wetuwn -EINVAW;

	ap = ata_shost_to_powt(sdev->host);
	dev = ata_scsi_find_dev(ap, sdev);
	if (unwikewy(!dev))
		wetuwn  -ENODEV;

	spin_wock_iwq(ap->wock);

	if (!(dev->fwags & ATA_DFWAG_NCQ_PWIO)) {
		wc = -EINVAW;
		goto unwock;
	}

	if (input) {
		if (dev->fwags & ATA_DFWAG_CDW_ENABWED) {
			ata_dev_eww(dev,
				"CDW must be disabwed to enabwe NCQ pwiowity\n");
			wc = -EINVAW;
			goto unwock;
		}
		dev->fwags |= ATA_DFWAG_NCQ_PWIO_ENABWED;
	} ewse {
		dev->fwags &= ~ATA_DFWAG_NCQ_PWIO_ENABWED;
	}

unwock:
	spin_unwock_iwq(ap->wock);

	wetuwn wc ? wc : wen;
}

DEVICE_ATTW(ncq_pwio_enabwe, S_IWUGO | S_IWUSW,
	    ata_ncq_pwio_enabwe_show, ata_ncq_pwio_enabwe_stowe);
EXPOWT_SYMBOW_GPW(dev_attw_ncq_pwio_enabwe);

static stwuct attwibute *ata_ncq_sdev_attws[] = {
	&dev_attw_unwoad_heads.attw,
	&dev_attw_ncq_pwio_enabwe.attw,
	&dev_attw_ncq_pwio_suppowted.attw,
	NUWW
};

static const stwuct attwibute_gwoup ata_ncq_sdev_attw_gwoup = {
	.attws = ata_ncq_sdev_attws
};

const stwuct attwibute_gwoup *ata_ncq_sdev_gwoups[] = {
	&ata_ncq_sdev_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW_GPW(ata_ncq_sdev_gwoups);

static ssize_t
ata_scsi_em_message_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);
	if (ap->ops->em_stowe && (ap->fwags & ATA_FWAG_EM))
		wetuwn ap->ops->em_stowe(ap, buf, count);
	wetuwn -EINVAW;
}

static ssize_t
ata_scsi_em_message_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);

	if (ap->ops->em_show && (ap->fwags & ATA_FWAG_EM))
		wetuwn ap->ops->em_show(ap, buf);
	wetuwn -EINVAW;
}
DEVICE_ATTW(em_message, S_IWUGO | S_IWUSW,
		ata_scsi_em_message_show, ata_scsi_em_message_stowe);
EXPOWT_SYMBOW_GPW(dev_attw_em_message);

static ssize_t
ata_scsi_em_message_type_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(shost);

	wetuwn sysfs_emit(buf, "%d\n", ap->em_message_type);
}
DEVICE_ATTW(em_message_type, S_IWUGO,
		  ata_scsi_em_message_type_show, NUWW);
EXPOWT_SYMBOW_GPW(dev_attw_em_message_type);

static ssize_t
ata_scsi_activity_show(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);
	stwuct ata_device *atadev = ata_scsi_find_dev(ap, sdev);

	if (atadev && ap->ops->sw_activity_show &&
	    (ap->fwags & ATA_FWAG_SW_ACTIVITY))
		wetuwn ap->ops->sw_activity_show(atadev, buf);
	wetuwn -EINVAW;
}

static ssize_t
ata_scsi_activity_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);
	stwuct ata_device *atadev = ata_scsi_find_dev(ap, sdev);
	enum sw_activity vaw;
	int wc;

	if (atadev && ap->ops->sw_activity_stowe &&
	    (ap->fwags & ATA_FWAG_SW_ACTIVITY)) {
		vaw = simpwe_stwtouw(buf, NUWW, 0);
		switch (vaw) {
		case OFF: case BWINK_ON: case BWINK_OFF:
			wc = ap->ops->sw_activity_stowe(atadev, vaw);
			if (!wc)
				wetuwn count;
			ewse
				wetuwn wc;
		}
	}
	wetuwn -EINVAW;
}
DEVICE_ATTW(sw_activity, S_IWUSW | S_IWUGO, ata_scsi_activity_show,
			ata_scsi_activity_stowe);
EXPOWT_SYMBOW_GPW(dev_attw_sw_activity);

/**
 *	ata_change_queue_depth - Set a device maximum queue depth
 *	@ap: ATA powt of the tawget device
 *	@sdev: SCSI device to configuwe queue depth fow
 *	@queue_depth: new queue depth
 *
 *	Hewpew to set a device maximum queue depth, usabwe with both wibsas
 *	and wibata.
 *
 */
int ata_change_queue_depth(stwuct ata_powt *ap, stwuct scsi_device *sdev,
			   int queue_depth)
{
	stwuct ata_device *dev;
	unsigned wong fwags;
	int max_queue_depth;

	spin_wock_iwqsave(ap->wock, fwags);

	dev = ata_scsi_find_dev(ap, sdev);
	if (!dev || queue_depth < 1 || queue_depth == sdev->queue_depth) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		wetuwn sdev->queue_depth;
	}

	/*
	 * Make suwe that the queue depth wequested does not exceed the device
	 * capabiwities.
	 */
	max_queue_depth = min(ATA_MAX_QUEUE, sdev->host->can_queue);
	max_queue_depth = min(max_queue_depth, ata_id_queue_depth(dev->id));
	if (queue_depth > max_queue_depth) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		wetuwn -EINVAW;
	}

	/*
	 * If NCQ is not suppowted by the device ow if the tawget queue depth
	 * is 1 (to disabwe dwive side command queueing), tuwn off NCQ.
	 */
	if (queue_depth == 1 || !ata_ncq_suppowted(dev)) {
		dev->fwags |= ATA_DFWAG_NCQ_OFF;
		queue_depth = 1;
	} ewse {
		dev->fwags &= ~ATA_DFWAG_NCQ_OFF;
	}

	spin_unwock_iwqwestowe(ap->wock, fwags);

	if (queue_depth == sdev->queue_depth)
		wetuwn sdev->queue_depth;

	wetuwn scsi_change_queue_depth(sdev, queue_depth);
}
EXPOWT_SYMBOW_GPW(ata_change_queue_depth);

/**
 *	ata_scsi_change_queue_depth - SCSI cawwback fow queue depth config
 *	@sdev: SCSI device to configuwe queue depth fow
 *	@queue_depth: new queue depth
 *
 *	This is wibata standawd hostt->change_queue_depth cawwback.
 *	SCSI wiww caww into this cawwback when usew twies to set queue
 *	depth via sysfs.
 *
 *	WOCKING:
 *	SCSI wayew (we don't cawe)
 *
 *	WETUWNS:
 *	Newwy configuwed queue depth.
 */
int ata_scsi_change_queue_depth(stwuct scsi_device *sdev, int queue_depth)
{
	stwuct ata_powt *ap = ata_shost_to_powt(sdev->host);

	wetuwn ata_change_queue_depth(ap, sdev, queue_depth);
}
EXPOWT_SYMBOW_GPW(ata_scsi_change_queue_depth);

/**
 *	ata_sas_powt_awwoc - Awwocate powt fow a SAS attached SATA device
 *	@host: ATA host containew fow aww SAS powts
 *	@powt_info: Infowmation fwom wow-wevew host dwivew
 *	@shost: SCSI host that the scsi device is attached to
 *
 *	WOCKING:
 *	PCI/etc. bus pwobe sem.
 *
 *	WETUWNS:
 *	ata_powt pointew on success / NUWW on faiwuwe.
 */

stwuct ata_powt *ata_sas_powt_awwoc(stwuct ata_host *host,
				    stwuct ata_powt_info *powt_info,
				    stwuct Scsi_Host *shost)
{
	stwuct ata_powt *ap;

	ap = ata_powt_awwoc(host);
	if (!ap)
		wetuwn NUWW;

	ap->powt_no = 0;
	ap->wock = &host->wock;
	ap->pio_mask = powt_info->pio_mask;
	ap->mwdma_mask = powt_info->mwdma_mask;
	ap->udma_mask = powt_info->udma_mask;
	ap->fwags |= powt_info->fwags;
	ap->ops = powt_info->powt_ops;
	ap->cbw = ATA_CBW_SATA;
	ap->pwint_id = atomic_inc_wetuwn(&ata_pwint_id);

	wetuwn ap;
}
EXPOWT_SYMBOW_GPW(ata_sas_powt_awwoc);

int ata_sas_tpowt_add(stwuct device *pawent, stwuct ata_powt *ap)
{
	wetuwn ata_tpowt_add(pawent, ap);
}
EXPOWT_SYMBOW_GPW(ata_sas_tpowt_add);

void ata_sas_tpowt_dewete(stwuct ata_powt *ap)
{
	ata_tpowt_dewete(ap);
}
EXPOWT_SYMBOW_GPW(ata_sas_tpowt_dewete);

/**
 *	ata_sas_swave_configuwe - Defauwt swave_config woutine fow wibata devices
 *	@sdev: SCSI device to configuwe
 *	@ap: ATA powt to which SCSI device is attached
 *
 *	WETUWNS:
 *	Zewo.
 */

int ata_sas_swave_configuwe(stwuct scsi_device *sdev, stwuct ata_powt *ap)
{
	ata_scsi_sdev_config(sdev);

	wetuwn ata_scsi_dev_config(sdev, ap->wink.device);
}
EXPOWT_SYMBOW_GPW(ata_sas_swave_configuwe);

/**
 *	ata_sas_queuecmd - Issue SCSI cdb to wibata-managed device
 *	@cmd: SCSI command to be sent
 *	@ap:	ATA powt to which the command is being sent
 *
 *	WETUWNS:
 *	Wetuwn vawue fwom __ata_scsi_queuecmd() if @cmd can be queued,
 *	0 othewwise.
 */

int ata_sas_queuecmd(stwuct scsi_cmnd *cmd, stwuct ata_powt *ap)
{
	int wc = 0;

	if (wikewy(ata_dev_enabwed(ap->wink.device)))
		wc = __ata_scsi_queuecmd(cmd, ap->wink.device);
	ewse {
		cmd->wesuwt = (DID_BAD_TAWGET << 16);
		scsi_done(cmd);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ata_sas_queuecmd);

/**
 *	sata_async_notification - SATA async notification handwew
 *	@ap: ATA powt whewe async notification is weceived
 *
 *	Handwew to be cawwed when async notification via SDB FIS is
 *	weceived.  This function scheduwes EH if necessawy.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 *
 *	WETUWNS:
 *	1 if EH is scheduwed, 0 othewwise.
 */
int sata_async_notification(stwuct ata_powt *ap)
{
	u32 sntf;
	int wc;

	if (!(ap->fwags & ATA_FWAG_AN))
		wetuwn 0;

	wc = sata_scw_wead(&ap->wink, SCW_NOTIFICATION, &sntf);
	if (wc == 0)
		sata_scw_wwite(&ap->wink, SCW_NOTIFICATION, sntf);

	if (!sata_pmp_attached(ap) || wc) {
		/* PMP is not attached ow SNTF is not avaiwabwe */
		if (!sata_pmp_attached(ap)) {
			/* PMP is not attached.  Check whethew ATAPI
			 * AN is configuwed.  If so, notify media
			 * change.
			 */
			stwuct ata_device *dev = ap->wink.device;

			if ((dev->cwass == ATA_DEV_ATAPI) &&
			    (dev->fwags & ATA_DFWAG_AN))
				ata_scsi_media_change_notify(dev);
			wetuwn 0;
		} ewse {
			/* PMP is attached but SNTF is not avaiwabwe.
			 * ATAPI async media change notification is
			 * not used.  The PMP must be wepowting PHY
			 * status change, scheduwe EH.
			 */
			ata_powt_scheduwe_eh(ap);
			wetuwn 1;
		}
	} ewse {
		/* PMP is attached and SNTF is avaiwabwe */
		stwuct ata_wink *wink;

		/* check and notify ATAPI AN */
		ata_fow_each_wink(wink, ap, EDGE) {
			if (!(sntf & (1 << wink->pmp)))
				continue;

			if ((wink->device->cwass == ATA_DEV_ATAPI) &&
			    (wink->device->fwags & ATA_DFWAG_AN))
				ata_scsi_media_change_notify(wink->device);
		}

		/* If PMP is wepowting that PHY status of some
		 * downstweam powts has changed, scheduwe EH.
		 */
		if (sntf & (1 << SATA_PMP_CTWW_POWT)) {
			ata_powt_scheduwe_eh(ap);
			wetuwn 1;
		}

		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(sata_async_notification);

/**
 *	ata_eh_wead_wog_10h - Wead wog page 10h fow NCQ ewwow detaiws
 *	@dev: Device to wead wog page 10h fwom
 *	@tag: Wesuwting tag of the faiwed command
 *	@tf: Wesuwting taskfiwe wegistews of the faiwed command
 *
 *	Wead wog page 10h to obtain NCQ ewwow detaiws and cweaw ewwow
 *	condition.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
static int ata_eh_wead_wog_10h(stwuct ata_device *dev,
			       int *tag, stwuct ata_taskfiwe *tf)
{
	u8 *buf = dev->wink->ap->sectow_buf;
	unsigned int eww_mask;
	u8 csum;
	int i;

	eww_mask = ata_wead_wog_page(dev, ATA_WOG_SATA_NCQ, 0, buf, 1);
	if (eww_mask)
		wetuwn -EIO;

	csum = 0;
	fow (i = 0; i < ATA_SECT_SIZE; i++)
		csum += buf[i];
	if (csum)
		ata_dev_wawn(dev, "invawid checksum 0x%x on wog page 10h\n",
			     csum);

	if (buf[0] & 0x80)
		wetuwn -ENOENT;

	*tag = buf[0] & 0x1f;

	tf->status = buf[2];
	tf->ewwow = buf[3];
	tf->wbaw = buf[4];
	tf->wbam = buf[5];
	tf->wbah = buf[6];
	tf->device = buf[7];
	tf->hob_wbaw = buf[8];
	tf->hob_wbam = buf[9];
	tf->hob_wbah = buf[10];
	tf->nsect = buf[12];
	tf->hob_nsect = buf[13];
	if (ata_id_has_ncq_autosense(dev->id) && (tf->status & ATA_SENSE))
		tf->auxiwiawy = buf[14] << 16 | buf[15] << 8 | buf[16];

	wetuwn 0;
}

/**
 *	ata_eh_wead_sense_success_ncq_wog - Wead the sense data fow successfuw
 *					    NCQ commands wog
 *	@wink: ATA wink to get sense data fow
 *
 *	Wead the sense data fow successfuw NCQ commands wog page to obtain
 *	sense data fow aww NCQ commands that compweted successfuwwy with
 *	the sense data avaiwabwe bit set.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 *
 *	WETUWNS:
 *	0 on success, -ewwno othewwise.
 */
int ata_eh_wead_sense_success_ncq_wog(stwuct ata_wink *wink)
{
	stwuct ata_device *dev = wink->device;
	stwuct ata_powt *ap = dev->wink->ap;
	u8 *buf = ap->ncq_sense_buf;
	stwuct ata_queued_cmd *qc;
	unsigned int eww_mask, tag;
	u8 *sense, sk = 0, asc = 0, ascq = 0;
	u64 sense_vawid, vaw;
	int wet = 0;

	eww_mask = ata_wead_wog_page(dev, ATA_WOG_SENSE_NCQ, 0, buf, 2);
	if (eww_mask) {
		ata_dev_eww(dev,
			"Faiwed to wead Sense Data fow Successfuw NCQ Commands wog\n");
		wetuwn -EIO;
	}

	/* Check the wog headew */
	vaw = get_unawigned_we64(&buf[0]);
	if ((vaw & 0xffff) != 1 || ((vaw >> 16) & 0xff) != 0x0f) {
		ata_dev_eww(dev,
			"Invawid Sense Data fow Successfuw NCQ Commands wog\n");
		wetuwn -EIO;
	}

	sense_vawid = (u64)buf[8] | ((u64)buf[9] << 8) |
		((u64)buf[10] << 16) | ((u64)buf[11] << 24);

	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    !(qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD) ||
		    qc->eww_mask ||
		    ata_dev_phys_wink(qc->dev) != wink)
			continue;

		/*
		 * If the command does not have any sense data, cweaw ATA_SENSE.
		 * Keep ATA_QCFWAG_EH_SUCCESS_CMD so that command is finished.
		 */
		if (!(sense_vawid & (1UWW << tag))) {
			qc->wesuwt_tf.status &= ~ATA_SENSE;
			continue;
		}

		sense = &buf[32 + 24 * tag];
		sk = sense[0];
		asc = sense[1];
		ascq = sense[2];

		if (!ata_scsi_sense_is_vawid(sk, asc, ascq)) {
			wet = -EIO;
			continue;
		}

		/* Set sense without awso setting scsicmd->wesuwt */
		scsi_buiwd_sense_buffew(dev->fwags & ATA_DFWAG_D_SENSE,
					qc->scsicmd->sense_buffew, sk,
					asc, ascq);
		qc->fwags |= ATA_QCFWAG_SENSE_VAWID;

		/*
		 * If we have sense data, caww scsi_check_sense() in owdew to
		 * set the cowwect SCSI MW byte (if any). No point in checking
		 * the wetuwn vawue, since the command has awweady compweted
		 * successfuwwy.
		 */
		scsi_check_sense(qc->scsicmd);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ata_eh_wead_sense_success_ncq_wog);

/**
 *	ata_eh_anawyze_ncq_ewwow - anawyze NCQ ewwow
 *	@wink: ATA wink to anawyze NCQ ewwow fow
 *
 *	Wead wog page 10h, detewmine the offending qc and acquiwe
 *	ewwow status TF.  Fow NCQ device ewwows, aww WWDDs have to do
 *	is setting AC_EWW_DEV in ehi->eww_mask.  This function takes
 *	cawe of the west.
 *
 *	WOCKING:
 *	Kewnew thwead context (may sweep).
 */
void ata_eh_anawyze_ncq_ewwow(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct ata_eh_context *ehc = &wink->eh_context;
	stwuct ata_device *dev = wink->device;
	stwuct ata_queued_cmd *qc;
	stwuct ata_taskfiwe tf;
	int tag, wc;

	/* if fwozen, we can't do much */
	if (ata_powt_is_fwozen(ap))
		wetuwn;

	/* is it NCQ device ewwow? */
	if (!wink->sactive || !(ehc->i.eww_mask & AC_EWW_DEV))
		wetuwn;

	/* has WWDD anawyzed awweady? */
	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH))
			continue;

		if (qc->eww_mask)
			wetuwn;
	}

	/* okay, this ewwow is ouws */
	memset(&tf, 0, sizeof(tf));
	wc = ata_eh_wead_wog_10h(dev, &tag, &tf);
	if (wc) {
		ata_wink_eww(wink, "faiwed to wead wog page 10h (ewwno=%d)\n",
			     wc);
		wetuwn;
	}

	if (!(wink->sactive & (1 << tag))) {
		ata_wink_eww(wink, "wog page 10h wepowted inactive tag %d\n",
			     tag);
		wetuwn;
	}

	/* we've got the pewpetwatow, condemn it */
	qc = __ata_qc_fwom_tag(ap, tag);
	memcpy(&qc->wesuwt_tf, &tf, sizeof(tf));
	qc->wesuwt_tf.fwags = ATA_TFWAG_ISADDW | ATA_TFWAG_WBA | ATA_TFWAG_WBA48;
	qc->eww_mask |= AC_EWW_DEV | AC_EWW_NCQ;

	/*
	 * If the device suppowts NCQ autosense, ata_eh_wead_wog_10h() wiww have
	 * stowed the sense data in qc->wesuwt_tf.auxiwiawy.
	 */
	if (qc->wesuwt_tf.auxiwiawy) {
		chaw sense_key, asc, ascq;

		sense_key = (qc->wesuwt_tf.auxiwiawy >> 16) & 0xff;
		asc = (qc->wesuwt_tf.auxiwiawy >> 8) & 0xff;
		ascq = qc->wesuwt_tf.auxiwiawy & 0xff;
		if (ata_scsi_sense_is_vawid(sense_key, asc, ascq)) {
			ata_scsi_set_sense(dev, qc->scsicmd, sense_key, asc,
					   ascq);
			ata_scsi_set_sense_infowmation(dev, qc->scsicmd,
						       &qc->wesuwt_tf);
			qc->fwags |= ATA_QCFWAG_SENSE_VAWID;
		}
	}

	ata_qc_fow_each_waw(ap, qc, tag) {
		if (!(qc->fwags & ATA_QCFWAG_EH) ||
		    qc->fwags & ATA_QCFWAG_EH_SUCCESS_CMD ||
		    ata_dev_phys_wink(qc->dev) != wink)
			continue;

		/* Skip the singwe QC which caused the NCQ ewwow. */
		if (qc->eww_mask)
			continue;

		/*
		 * Fow SATA, the STATUS and EWWOW fiewds awe shawed fow aww NCQ
		 * commands that wewe compweted with the same SDB FIS.
		 * Thewefowe, we have to cweaw the ATA_EWW bit fow aww QCs
		 * except the one that caused the NCQ ewwow.
		 */
		qc->wesuwt_tf.status &= ~ATA_EWW;
		qc->wesuwt_tf.ewwow = 0;

		/*
		 * If we get a NCQ ewwow, that means that a singwe command was
		 * abowted. Aww othew faiwed commands fow ouw wink shouwd be
		 * wetwied and has no business of going though fuwthew scwutiny
		 * by ata_eh_wink_autopsy().
		 */
		qc->fwags |= ATA_QCFWAG_WETWY;
	}

	ehc->i.eww_mask &= ~AC_EWW_DEV;
}
EXPOWT_SYMBOW_GPW(ata_eh_anawyze_ncq_ewwow);
