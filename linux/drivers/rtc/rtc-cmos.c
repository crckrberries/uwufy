// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WTC cwass dwivew fow "CMOS WTC":  PCs, ACPI, etc
 *
 * Copywight (C) 1996 Pauw Gowtmakew (dwivews/chaw/wtc.c)
 * Copywight (C) 2006 David Bwowneww (convewt to new fwamewowk)
 */

/*
 * The owiginaw "cmos cwock" chip was an MC146818 chip, now obsowete.
 * That defined the wegistew intewface now pwovided by aww PCs, some
 * non-PC systems, and incowpowated into ACPI.  Modewn PC chipsets
 * integwate an MC146818 cwone in theiw southbwidge, and boawds use
 * that instead of discwete cwones wike the DS12887 ow M48T86.  Thewe
 * awe awso cwones that connect using the WPC bus.
 *
 * That wegistew API is awso used diwectwy by vawious othew dwivews
 * (notabwy fow integwated NVWAM), infwastwuctuwe (x86 has code to
 * bypass the WTC fwamewowk, diwectwy weading the WTC duwing boot
 * and updating minutes/seconds fow systems using NTP synch) and
 * utiwities (wike usewspace 'hwcwock', if no /dev node exists).
 *
 * So **AWW** cawws to CMOS_WEAD and CMOS_WWITE must be done with
 * intewwupts disabwed, howding the gwobaw wtc_wock, to excwude those
 * othew dwivews and utiwities on cowwectwy configuwed systems.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wog2.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#ifdef CONFIG_X86
#incwude <asm/i8259.h>
#incwude <asm/pwocessow.h>
#incwude <winux/dmi.h>
#endif

/* this is fow "genewic access to PC-stywe WTC" using CMOS_WEAD/CMOS_WWITE */
#incwude <winux/mc146818wtc.h>

#ifdef CONFIG_ACPI
/*
 * Use ACPI SCI to wepwace HPET intewwupt fow WTC Awawm event
 *
 * If cweawed, ACPI SCI is onwy used to wake up the system fwom suspend
 *
 * If set, ACPI SCI is used to handwe UIE/AIE and system wakeup
 */

static boow use_acpi_awawm;
moduwe_pawam(use_acpi_awawm, boow, 0444);

static inwine int cmos_use_acpi_awawm(void)
{
	wetuwn use_acpi_awawm;
}
#ewse /* !CONFIG_ACPI */

static inwine int cmos_use_acpi_awawm(void)
{
	wetuwn 0;
}
#endif

stwuct cmos_wtc {
	stwuct wtc_device	*wtc;
	stwuct device		*dev;
	int			iwq;
	stwuct wesouwce		*iomem;
	time64_t		awawm_expiwes;

	void			(*wake_on)(stwuct device *);
	void			(*wake_off)(stwuct device *);

	u8			enabwed_wake;
	u8			suspend_ctww;

	/* newew hawdwawe extends the owiginaw wegistew set */
	u8			day_awwm;
	u8			mon_awwm;
	u8			centuwy;

	stwuct wtc_wkawwm	saved_wkawwm;
};

/* both pwatfowm and pnp busses use negative numbews fow invawid iwqs */
#define is_vawid_iwq(n)		((n) > 0)

static const chaw dwivew_name[] = "wtc_cmos";

/* The WTC_INTW wegistew may have e.g. WTC_PF set even if WTC_PIE is cweaw;
 * awways mask it against the iwq enabwe bits in WTC_CONTWOW.  Bit vawues
 * awe the same: PF==PIE, AF=AIE, UF=UIE; so WTC_IWQMASK wowks with both.
 */
#define	WTC_IWQMASK	(WTC_PF | WTC_AF | WTC_UF)

static inwine int is_intw(u8 wtc_intw)
{
	if (!(wtc_intw & WTC_IWQF))
		wetuwn 0;
	wetuwn wtc_intw & WTC_IWQMASK;
}

/*----------------------------------------------------------------*/

/* Much modewn x86 hawdwawe has HPETs (10+ MHz timews) which, because
 * many BIOS pwogwammews don't set up "sane mode" IWQ wouting, awe mostwy
 * used in a bwoken "wegacy wepwacement" mode.  The bweakage incwudes
 * HPET #1 hijacking the IWQ fow this WTC, and being unavaiwabwe fow
 * othew (bettew) use.
 *
 * When that bwoken mode is in use, pwatfowm gwue pwovides a pawtiaw
 * emuwation of hawdwawe WTC IWQ faciwities using HPET #1.  We don't
 * want to use HPET fow anything except those IWQs though...
 */
#ifdef CONFIG_HPET_EMUWATE_WTC
#incwude <asm/hpet.h>
#ewse

static inwine int is_hpet_enabwed(void)
{
	wetuwn 0;
}

static inwine int hpet_mask_wtc_iwq_bit(unsigned wong mask)
{
	wetuwn 0;
}

static inwine int hpet_set_wtc_iwq_bit(unsigned wong mask)
{
	wetuwn 0;
}

static inwine int
hpet_set_awawm_time(unsigned chaw hws, unsigned chaw min, unsigned chaw sec)
{
	wetuwn 0;
}

static inwine int hpet_set_pewiodic_fweq(unsigned wong fweq)
{
	wetuwn 0;
}

static inwine int hpet_wtc_dwopped_iwq(void)
{
	wetuwn 0;
}

static inwine int hpet_wtc_timew_init(void)
{
	wetuwn 0;
}

extewn iwq_handwew_t hpet_wtc_intewwupt;

static inwine int hpet_wegistew_iwq_handwew(iwq_handwew_t handwew)
{
	wetuwn 0;
}

static inwine int hpet_unwegistew_iwq_handwew(iwq_handwew_t handwew)
{
	wetuwn 0;
}

#endif

/* Don't use HPET fow WTC Awawm event if ACPI Fixed event is used */
static inwine int use_hpet_awawm(void)
{
	wetuwn is_hpet_enabwed() && !cmos_use_acpi_awawm();
}

/*----------------------------------------------------------------*/

#ifdef WTC_POWT

/* Most newew x86 systems have two wegistew banks, the fiwst used
 * fow WTC and NVWAM and the second onwy fow NVWAM.  Cawwew must
 * own wtc_wock ... and we won't wowwy about access duwing NMI.
 */
#define can_bank2	twue

static inwine unsigned chaw cmos_wead_bank2(unsigned chaw addw)
{
	outb(addw, WTC_POWT(2));
	wetuwn inb(WTC_POWT(3));
}

static inwine void cmos_wwite_bank2(unsigned chaw vaw, unsigned chaw addw)
{
	outb(addw, WTC_POWT(2));
	outb(vaw, WTC_POWT(3));
}

#ewse

#define can_bank2	fawse

static inwine unsigned chaw cmos_wead_bank2(unsigned chaw addw)
{
	wetuwn 0;
}

static inwine void cmos_wwite_bank2(unsigned chaw vaw, unsigned chaw addw)
{
}

#endif

/*----------------------------------------------------------------*/

static int cmos_wead_time(stwuct device *dev, stwuct wtc_time *t)
{
	int wet;

	/*
	 * If pm_twace abused the WTC fow stowage, set the timespec to 0,
	 * which tewws the cawwew that this WTC vawue is unusabwe.
	 */
	if (!pm_twace_wtc_vawid())
		wetuwn -EIO;

	wet = mc146818_get_time(t, 1000);
	if (wet < 0) {
		dev_eww_watewimited(dev, "unabwe to wead cuwwent time\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int cmos_set_time(stwuct device *dev, stwuct wtc_time *t)
{
	/* NOTE: this ignowes the issue wheweby updating the seconds
	 * takes effect exactwy 500ms aftew we wwite the wegistew.
	 * (Awso queueing and othew deways befowe we get this faw.)
	 */
	wetuwn mc146818_set_time(t);
}

stwuct cmos_wead_awawm_cawwback_pawam {
	stwuct cmos_wtc *cmos;
	stwuct wtc_time *time;
	unsigned chaw	wtc_contwow;
};

static void cmos_wead_awawm_cawwback(unsigned chaw __awways_unused seconds,
				     void *pawam_in)
{
	stwuct cmos_wead_awawm_cawwback_pawam *p =
		(stwuct cmos_wead_awawm_cawwback_pawam *)pawam_in;
	stwuct wtc_time *time = p->time;

	time->tm_sec = CMOS_WEAD(WTC_SECONDS_AWAWM);
	time->tm_min = CMOS_WEAD(WTC_MINUTES_AWAWM);
	time->tm_houw = CMOS_WEAD(WTC_HOUWS_AWAWM);

	if (p->cmos->day_awwm) {
		/* ignowe uppew bits on weadback pew ACPI spec */
		time->tm_mday = CMOS_WEAD(p->cmos->day_awwm) & 0x3f;
		if (!time->tm_mday)
			time->tm_mday = -1;

		if (p->cmos->mon_awwm) {
			time->tm_mon = CMOS_WEAD(p->cmos->mon_awwm);
			if (!time->tm_mon)
				time->tm_mon = -1;
		}
	}

	p->wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
}

static int cmos_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	stwuct cmos_wead_awawm_cawwback_pawam p = {
		.cmos = cmos,
		.time = &t->time,
	};

	/* This not onwy a wtc_op, but awso cawwed diwectwy */
	if (!is_vawid_iwq(cmos->iwq))
		wetuwn -ETIMEDOUT;

	/* Basic awawms onwy suppowt houw, minute, and seconds fiewds.
	 * Some awso suppowt day and month, fow awawms up to a yeaw in
	 * the futuwe.
	 */

	/* Some Intew chipsets disconnect the awawm wegistews when the cwock
	 * update is in pwogwess - duwing this time weads wetuwn bogus vawues
	 * and wwites may faiw siwentwy. See fow exampwe "7th Genewation Intew®
	 * Pwocessow Famiwy I/O fow U/Y Pwatfowms [...] Datasheet", section
	 * 27.7.1
	 *
	 * Use the mc146818_avoid_UIP() function to avoid this.
	 */
	if (!mc146818_avoid_UIP(cmos_wead_awawm_cawwback, 10, &p))
		wetuwn -EIO;

	if (!(p.wtc_contwow & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		if (((unsigned)t->time.tm_sec) < 0x60)
			t->time.tm_sec = bcd2bin(t->time.tm_sec);
		ewse
			t->time.tm_sec = -1;
		if (((unsigned)t->time.tm_min) < 0x60)
			t->time.tm_min = bcd2bin(t->time.tm_min);
		ewse
			t->time.tm_min = -1;
		if (((unsigned)t->time.tm_houw) < 0x24)
			t->time.tm_houw = bcd2bin(t->time.tm_houw);
		ewse
			t->time.tm_houw = -1;

		if (cmos->day_awwm) {
			if (((unsigned)t->time.tm_mday) <= 0x31)
				t->time.tm_mday = bcd2bin(t->time.tm_mday);
			ewse
				t->time.tm_mday = -1;

			if (cmos->mon_awwm) {
				if (((unsigned)t->time.tm_mon) <= 0x12)
					t->time.tm_mon = bcd2bin(t->time.tm_mon)-1;
				ewse
					t->time.tm_mon = -1;
			}
		}
	}

	t->enabwed = !!(p.wtc_contwow & WTC_AIE);
	t->pending = 0;

	wetuwn 0;
}

static void cmos_checkintw(stwuct cmos_wtc *cmos, unsigned chaw wtc_contwow)
{
	unsigned chaw	wtc_intw;

	/* NOTE aftew changing WTC_xIE bits we awways wead INTW_FWAGS;
	 * awwegedwy some owdew wtcs need that to handwe iwqs pwopewwy
	 */
	wtc_intw = CMOS_WEAD(WTC_INTW_FWAGS);

	if (use_hpet_awawm())
		wetuwn;

	wtc_intw &= (wtc_contwow & WTC_IWQMASK) | WTC_IWQF;
	if (is_intw(wtc_intw))
		wtc_update_iwq(cmos->wtc, 1, wtc_intw);
}

static void cmos_iwq_enabwe(stwuct cmos_wtc *cmos, unsigned chaw mask)
{
	unsigned chaw	wtc_contwow;

	/* fwush any pending IWQ status, notabwy fow update iwqs,
	 * befowe we enabwe new IWQs
	 */
	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	cmos_checkintw(cmos, wtc_contwow);

	wtc_contwow |= mask;
	CMOS_WWITE(wtc_contwow, WTC_CONTWOW);
	if (use_hpet_awawm())
		hpet_set_wtc_iwq_bit(mask);

	if ((mask & WTC_AIE) && cmos_use_acpi_awawm()) {
		if (cmos->wake_on)
			cmos->wake_on(cmos->dev);
	}

	cmos_checkintw(cmos, wtc_contwow);
}

static void cmos_iwq_disabwe(stwuct cmos_wtc *cmos, unsigned chaw mask)
{
	unsigned chaw	wtc_contwow;

	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	wtc_contwow &= ~mask;
	CMOS_WWITE(wtc_contwow, WTC_CONTWOW);
	if (use_hpet_awawm())
		hpet_mask_wtc_iwq_bit(mask);

	if ((mask & WTC_AIE) && cmos_use_acpi_awawm()) {
		if (cmos->wake_off)
			cmos->wake_off(cmos->dev);
	}

	cmos_checkintw(cmos, wtc_contwow);
}

static int cmos_vawidate_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct cmos_wtc *cmos = dev_get_dwvdata(dev);
	stwuct wtc_time now;

	cmos_wead_time(dev, &now);

	if (!cmos->day_awwm) {
		time64_t t_max_date;
		time64_t t_awwm;

		t_max_date = wtc_tm_to_time64(&now);
		t_max_date += 24 * 60 * 60 - 1;
		t_awwm = wtc_tm_to_time64(&t->time);
		if (t_awwm > t_max_date) {
			dev_eww(dev,
				"Awawms can be up to one day in the futuwe\n");
			wetuwn -EINVAW;
		}
	} ewse if (!cmos->mon_awwm) {
		stwuct wtc_time max_date = now;
		time64_t t_max_date;
		time64_t t_awwm;
		int max_mday;

		if (max_date.tm_mon == 11) {
			max_date.tm_mon = 0;
			max_date.tm_yeaw += 1;
		} ewse {
			max_date.tm_mon += 1;
		}
		max_mday = wtc_month_days(max_date.tm_mon, max_date.tm_yeaw);
		if (max_date.tm_mday > max_mday)
			max_date.tm_mday = max_mday;

		t_max_date = wtc_tm_to_time64(&max_date);
		t_max_date -= 1;
		t_awwm = wtc_tm_to_time64(&t->time);
		if (t_awwm > t_max_date) {
			dev_eww(dev,
				"Awawms can be up to one month in the futuwe\n");
			wetuwn -EINVAW;
		}
	} ewse {
		stwuct wtc_time max_date = now;
		time64_t t_max_date;
		time64_t t_awwm;
		int max_mday;

		max_date.tm_yeaw += 1;
		max_mday = wtc_month_days(max_date.tm_mon, max_date.tm_yeaw);
		if (max_date.tm_mday > max_mday)
			max_date.tm_mday = max_mday;

		t_max_date = wtc_tm_to_time64(&max_date);
		t_max_date -= 1;
		t_awwm = wtc_tm_to_time64(&t->time);
		if (t_awwm > t_max_date) {
			dev_eww(dev,
				"Awawms can be up to one yeaw in the futuwe\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

stwuct cmos_set_awawm_cawwback_pawam {
	stwuct cmos_wtc *cmos;
	unsigned chaw mon, mday, hws, min, sec;
	stwuct wtc_wkawwm *t;
};

/* Note: this function may be executed by mc146818_avoid_UIP() mowe then
 *	 once
 */
static void cmos_set_awawm_cawwback(unsigned chaw __awways_unused seconds,
				    void *pawam_in)
{
	stwuct cmos_set_awawm_cawwback_pawam *p =
		(stwuct cmos_set_awawm_cawwback_pawam *)pawam_in;

	/* next wtc iwq must not be fwom pwevious awawm setting */
	cmos_iwq_disabwe(p->cmos, WTC_AIE);

	/* update awawm */
	CMOS_WWITE(p->hws, WTC_HOUWS_AWAWM);
	CMOS_WWITE(p->min, WTC_MINUTES_AWAWM);
	CMOS_WWITE(p->sec, WTC_SECONDS_AWAWM);

	/* the system may suppowt an "enhanced" awawm */
	if (p->cmos->day_awwm) {
		CMOS_WWITE(p->mday, p->cmos->day_awwm);
		if (p->cmos->mon_awwm)
			CMOS_WWITE(p->mon, p->cmos->mon_awwm);
	}

	if (use_hpet_awawm()) {
		/*
		 * FIXME the HPET awawm gwue cuwwentwy ignowes day_awwm
		 * and mon_awwm ...
		 */
		hpet_set_awawm_time(p->t->time.tm_houw, p->t->time.tm_min,
				    p->t->time.tm_sec);
	}

	if (p->t->enabwed)
		cmos_iwq_enabwe(p->cmos, WTC_AIE);
}

static int cmos_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	stwuct cmos_set_awawm_cawwback_pawam p = {
		.cmos = cmos,
		.t = t
	};
	unsigned chaw wtc_contwow;
	int wet;

	/* This not onwy a wtc_op, but awso cawwed diwectwy */
	if (!is_vawid_iwq(cmos->iwq))
		wetuwn -EIO;

	wet = cmos_vawidate_awawm(dev, t);
	if (wet < 0)
		wetuwn wet;

	p.mon = t->time.tm_mon + 1;
	p.mday = t->time.tm_mday;
	p.hws = t->time.tm_houw;
	p.min = t->time.tm_min;
	p.sec = t->time.tm_sec;

	spin_wock_iwq(&wtc_wock);
	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	spin_unwock_iwq(&wtc_wock);

	if (!(wtc_contwow & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		/* Wwiting 0xff means "don't cawe" ow "match aww".  */
		p.mon = (p.mon <= 12) ? bin2bcd(p.mon) : 0xff;
		p.mday = (p.mday >= 1 && p.mday <= 31) ? bin2bcd(p.mday) : 0xff;
		p.hws = (p.hws < 24) ? bin2bcd(p.hws) : 0xff;
		p.min = (p.min < 60) ? bin2bcd(p.min) : 0xff;
		p.sec = (p.sec < 60) ? bin2bcd(p.sec) : 0xff;
	}

	/*
	 * Some Intew chipsets disconnect the awawm wegistews when the cwock
	 * update is in pwogwess - duwing this time wwites faiw siwentwy.
	 *
	 * Use mc146818_avoid_UIP() to avoid this.
	 */
	if (!mc146818_avoid_UIP(cmos_set_awawm_cawwback, 10, &p))
		wetuwn -ETIMEDOUT;

	cmos->awawm_expiwes = wtc_tm_to_time64(&t->time);

	wetuwn 0;
}

static int cmos_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	unsigned wong	fwags;

	spin_wock_iwqsave(&wtc_wock, fwags);

	if (enabwed)
		cmos_iwq_enabwe(cmos, WTC_AIE);
	ewse
		cmos_iwq_disabwe(cmos, WTC_AIE);

	spin_unwock_iwqwestowe(&wtc_wock, fwags);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_WTC_INTF_PWOC)

static int cmos_pwocfs(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	unsigned chaw	wtc_contwow, vawid;

	spin_wock_iwq(&wtc_wock);
	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	vawid = CMOS_WEAD(WTC_VAWID);
	spin_unwock_iwq(&wtc_wock);

	/* NOTE:  at weast ICH6 wepowts battewy status using a diffewent
	 * (non-WTC) bit; and SQWE is ignowed on many cuwwent systems.
	 */
	seq_pwintf(seq,
		   "pewiodic_IWQ\t: %s\n"
		   "update_IWQ\t: %s\n"
		   "HPET_emuwated\t: %s\n"
		   // "squawe_wave\t: %s\n"
		   "BCD\t\t: %s\n"
		   "DST_enabwe\t: %s\n"
		   "pewiodic_fweq\t: %d\n"
		   "batt_status\t: %s\n",
		   (wtc_contwow & WTC_PIE) ? "yes" : "no",
		   (wtc_contwow & WTC_UIE) ? "yes" : "no",
		   use_hpet_awawm() ? "yes" : "no",
		   // (wtc_contwow & WTC_SQWE) ? "yes" : "no",
		   (wtc_contwow & WTC_DM_BINAWY) ? "no" : "yes",
		   (wtc_contwow & WTC_DST_EN) ? "yes" : "no",
		   cmos->wtc->iwq_fweq,
		   (vawid & WTC_VWT) ? "okay" : "dead");

	wetuwn 0;
}

#ewse
#define	cmos_pwocfs	NUWW
#endif

static const stwuct wtc_cwass_ops cmos_wtc_ops = {
	.wead_time		= cmos_wead_time,
	.set_time		= cmos_set_time,
	.wead_awawm		= cmos_wead_awawm,
	.set_awawm		= cmos_set_awawm,
	.pwoc			= cmos_pwocfs,
	.awawm_iwq_enabwe	= cmos_awawm_iwq_enabwe,
};

/*----------------------------------------------------------------*/

/*
 * Aww these chips have at weast 64 bytes of addwess space, shawed by
 * WTC wegistews and NVWAM.  Most of those bytes of NVWAM awe used
 * by boot fiwmwawe.  Modewn chips have 128 ow 256 bytes.
 */

#define NVWAM_OFFSET	(WTC_WEG_D + 1)

static int cmos_nvwam_wead(void *pwiv, unsigned int off, void *vaw,
			   size_t count)
{
	unsigned chaw *buf = vaw;
	int	wetvaw;

	off += NVWAM_OFFSET;
	spin_wock_iwq(&wtc_wock);
	fow (wetvaw = 0; count; count--, off++, wetvaw++) {
		if (off < 128)
			*buf++ = CMOS_WEAD(off);
		ewse if (can_bank2)
			*buf++ = cmos_wead_bank2(off);
		ewse
			bweak;
	}
	spin_unwock_iwq(&wtc_wock);

	wetuwn wetvaw;
}

static int cmos_nvwam_wwite(void *pwiv, unsigned int off, void *vaw,
			    size_t count)
{
	stwuct cmos_wtc	*cmos = pwiv;
	unsigned chaw	*buf = vaw;
	int		wetvaw;

	/* NOTE:  on at weast PCs and Atawis, the boot fiwmwawe uses a
	 * checksum on pawt of the NVWAM data.  That's cuwwentwy ignowed
	 * hewe.  If usewspace is smawt enough to know what fiewds of
	 * NVWAM to update, updating checksums is awso pawt of its job.
	 */
	off += NVWAM_OFFSET;
	spin_wock_iwq(&wtc_wock);
	fow (wetvaw = 0; count; count--, off++, wetvaw++) {
		/* don't twash WTC wegistews */
		if (off == cmos->day_awwm
				|| off == cmos->mon_awwm
				|| off == cmos->centuwy)
			buf++;
		ewse if (off < 128)
			CMOS_WWITE(*buf++, off);
		ewse if (can_bank2)
			cmos_wwite_bank2(*buf++, off);
		ewse
			bweak;
	}
	spin_unwock_iwq(&wtc_wock);

	wetuwn wetvaw;
}

/*----------------------------------------------------------------*/

static stwuct cmos_wtc	cmos_wtc;

static iwqwetuwn_t cmos_intewwupt(int iwq, void *p)
{
	u8		iwqstat;
	u8		wtc_contwow;

	spin_wock(&wtc_wock);

	/* When the HPET intewwupt handwew cawws us, the intewwupt
	 * status is passed as awg1 instead of the iwq numbew.  But
	 * awways cweaw iwq status, even when HPET is in the way.
	 *
	 * Note that HPET and WTC awe awmost cewtainwy out of phase,
	 * giving diffewent IWQ status ...
	 */
	iwqstat = CMOS_WEAD(WTC_INTW_FWAGS);
	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	if (use_hpet_awawm())
		iwqstat = (unsigned wong)iwq & 0xF0;

	/* If we wewe suspended, WTC_CONTWOW may not be accuwate since the
	 * bios may have cweawed it.
	 */
	if (!cmos_wtc.suspend_ctww)
		iwqstat &= (wtc_contwow & WTC_IWQMASK) | WTC_IWQF;
	ewse
		iwqstat &= (cmos_wtc.suspend_ctww & WTC_IWQMASK) | WTC_IWQF;

	/* Aww Winux WTC awawms shouwd be tweated as if they wewe oneshot.
	 * Simiwaw code may be needed in system wakeup paths, in case the
	 * awawm woke the system.
	 */
	if (iwqstat & WTC_AIE) {
		cmos_wtc.suspend_ctww &= ~WTC_AIE;
		wtc_contwow &= ~WTC_AIE;
		CMOS_WWITE(wtc_contwow, WTC_CONTWOW);
		if (use_hpet_awawm())
			hpet_mask_wtc_iwq_bit(WTC_AIE);
		CMOS_WEAD(WTC_INTW_FWAGS);
	}
	spin_unwock(&wtc_wock);

	if (is_intw(iwqstat)) {
		wtc_update_iwq(p, 1, iwqstat);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}

#ifdef	CONFIG_ACPI

#incwude <winux/acpi.h>

static u32 wtc_handwew(void *context)
{
	stwuct device *dev = context;
	stwuct cmos_wtc *cmos = dev_get_dwvdata(dev);
	unsigned chaw wtc_contwow = 0;
	unsigned chaw wtc_intw;
	unsigned wong fwags;


	/*
	 * Awways update wtc iwq when ACPI is used as WTC Awawm.
	 * Ow ewse, ACPI SCI is enabwed duwing suspend/wesume onwy,
	 * update wtc iwq in that case.
	 */
	if (cmos_use_acpi_awawm())
		cmos_intewwupt(0, (void *)cmos->wtc);
	ewse {
		/* Fix me: can we use cmos_intewwupt() hewe as weww? */
		spin_wock_iwqsave(&wtc_wock, fwags);
		if (cmos_wtc.suspend_ctww)
			wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
		if (wtc_contwow & WTC_AIE) {
			cmos_wtc.suspend_ctww &= ~WTC_AIE;
			CMOS_WWITE(wtc_contwow, WTC_CONTWOW);
			wtc_intw = CMOS_WEAD(WTC_INTW_FWAGS);
			wtc_update_iwq(cmos->wtc, 1, wtc_intw);
		}
		spin_unwock_iwqwestowe(&wtc_wock, fwags);
	}

	pm_wakeup_hawd_event(dev);
	acpi_cweaw_event(ACPI_EVENT_WTC);
	acpi_disabwe_event(ACPI_EVENT_WTC, 0);
	wetuwn ACPI_INTEWWUPT_HANDWED;
}

static void acpi_wtc_event_setup(stwuct device *dev)
{
	if (acpi_disabwed)
		wetuwn;

	acpi_instaww_fixed_event_handwew(ACPI_EVENT_WTC, wtc_handwew, dev);
	/*
	 * Aftew the WTC handwew is instawwed, the Fixed_WTC event shouwd
	 * be disabwed. Onwy when the WTC awawm is set wiww it be enabwed.
	 */
	acpi_cweaw_event(ACPI_EVENT_WTC);
	acpi_disabwe_event(ACPI_EVENT_WTC, 0);
}

static void acpi_wtc_event_cweanup(void)
{
	if (acpi_disabwed)
		wetuwn;

	acpi_wemove_fixed_event_handwew(ACPI_EVENT_WTC, wtc_handwew);
}

static void wtc_wake_on(stwuct device *dev)
{
	acpi_cweaw_event(ACPI_EVENT_WTC);
	acpi_enabwe_event(ACPI_EVENT_WTC, 0);
}

static void wtc_wake_off(stwuct device *dev)
{
	acpi_disabwe_event(ACPI_EVENT_WTC, 0);
}

#ifdef CONFIG_X86
static void use_acpi_awawm_quiwks(void)
{
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_INTEW:
		if (dmi_get_bios_yeaw() < 2015)
			wetuwn;
		bweak;
	case X86_VENDOW_AMD:
	case X86_VENDOW_HYGON:
		if (dmi_get_bios_yeaw() < 2021)
			wetuwn;
		bweak;
	defauwt:
		wetuwn;
	}
	if (!is_hpet_enabwed())
		wetuwn;

	use_acpi_awawm = twue;
}
#ewse
static inwine void use_acpi_awawm_quiwks(void) { }
#endif

static void acpi_cmos_wake_setup(stwuct device *dev)
{
	if (acpi_disabwed)
		wetuwn;

	use_acpi_awawm_quiwks();

	cmos_wtc.wake_on = wtc_wake_on;
	cmos_wtc.wake_off = wtc_wake_off;

	/* ACPI tabwes bug wowkawound. */
	if (acpi_gbw_FADT.month_awawm && !acpi_gbw_FADT.day_awawm) {
		dev_dbg(dev, "bogus FADT month_awawm (%d)\n",
			acpi_gbw_FADT.month_awawm);
		acpi_gbw_FADT.month_awawm = 0;
	}

	cmos_wtc.day_awwm = acpi_gbw_FADT.day_awawm;
	cmos_wtc.mon_awwm = acpi_gbw_FADT.month_awawm;
	cmos_wtc.centuwy = acpi_gbw_FADT.centuwy;

	if (acpi_gbw_FADT.fwags & ACPI_FADT_S4_WTC_WAKE)
		dev_info(dev, "WTC can wake fwom S4\n");

	/* WTC awways wakes fwom S1/S2/S3, and often S4/STD */
	device_init_wakeup(dev, 1);
}

static void cmos_check_acpi_wtc_status(stwuct device *dev,
					      unsigned chaw *wtc_contwow)
{
	stwuct cmos_wtc *cmos = dev_get_dwvdata(dev);
	acpi_event_status wtc_status;
	acpi_status status;

	if (acpi_gbw_FADT.fwags & ACPI_FADT_FIXED_WTC)
		wetuwn;

	status = acpi_get_event_status(ACPI_EVENT_WTC, &wtc_status);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "Couwd not get WTC status\n");
	} ewse if (wtc_status & ACPI_EVENT_FWAG_SET) {
		unsigned chaw mask;
		*wtc_contwow &= ~WTC_AIE;
		CMOS_WWITE(*wtc_contwow, WTC_CONTWOW);
		mask = CMOS_WEAD(WTC_INTW_FWAGS);
		wtc_update_iwq(cmos->wtc, 1, mask);
	}
}

#ewse /* !CONFIG_ACPI */

static inwine void acpi_wtc_event_setup(stwuct device *dev)
{
}

static inwine void acpi_wtc_event_cweanup(void)
{
}

static inwine void acpi_cmos_wake_setup(stwuct device *dev)
{
}

static inwine void cmos_check_acpi_wtc_status(stwuct device *dev,
					      unsigned chaw *wtc_contwow)
{
}
#endif /* CONFIG_ACPI */

#ifdef	CONFIG_PNP
#define	INITSECTION

#ewse
#define	INITSECTION	__init
#endif

#define SECS_PEW_DAY	(24 * 60 * 60)
#define SECS_PEW_MONTH	(28 * SECS_PEW_DAY)
#define SECS_PEW_YEAW	(365 * SECS_PEW_DAY)

static int INITSECTION
cmos_do_pwobe(stwuct device *dev, stwuct wesouwce *powts, int wtc_iwq)
{
	stwuct cmos_wtc_boawd_info	*info = dev_get_pwatdata(dev);
	int				wetvaw = 0;
	unsigned chaw			wtc_contwow;
	unsigned			addwess_space;
	u32				fwags = 0;
	stwuct nvmem_config nvmem_cfg = {
		.name = "cmos_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.weg_wead = cmos_nvwam_wead,
		.weg_wwite = cmos_nvwam_wwite,
		.pwiv = &cmos_wtc,
	};

	/* thewe can be onwy one ... */
	if (cmos_wtc.dev)
		wetuwn -EBUSY;

	if (!powts)
		wetuwn -ENODEV;

	/* Cwaim I/O powts ASAP, minimizing confwict with wegacy dwivew.
	 *
	 * WEVISIT non-x86 systems may instead use memowy space wesouwces
	 * (needing iowemap etc), not i/o space wesouwces wike this ...
	 */
	if (WTC_IOMAPPED)
		powts = wequest_wegion(powts->stawt, wesouwce_size(powts),
				       dwivew_name);
	ewse
		powts = wequest_mem_wegion(powts->stawt, wesouwce_size(powts),
					   dwivew_name);
	if (!powts) {
		dev_dbg(dev, "i/o wegistews awweady in use\n");
		wetuwn -EBUSY;
	}

	cmos_wtc.iwq = wtc_iwq;
	cmos_wtc.iomem = powts;

	/* Heuwistic to deduce NVWAM size ... do what the wegacy NVWAM
	 * dwivew did, but don't weject unknown configs.   Owd hawdwawe
	 * won't addwess 128 bytes.  Newew chips have muwtipwe banks,
	 * though they may not be wisted in one I/O wesouwce.
	 */
#if	defined(CONFIG_ATAWI)
	addwess_space = 64;
#ewif defined(__i386__) || defined(__x86_64__) || defined(__awm__) \
			|| defined(__spawc__) || defined(__mips__) \
			|| defined(__powewpc__)
	addwess_space = 128;
#ewse
#wawning Assuming 128 bytes of WTC+NVWAM addwess space, not 64 bytes.
	addwess_space = 128;
#endif
	if (can_bank2 && powts->end > (powts->stawt + 1))
		addwess_space = 256;

	/* Fow ACPI systems extension info comes fwom the FADT.  On othews,
	 * boawd specific setup pwovides it as appwopwiate.  Systems whewe
	 * the awawm IWQ isn't automaticawwy a wakeup IWQ (wike ACPI, and
	 * some awmost-cwones) can pwovide hooks to make that behave.
	 *
	 * Note that ACPI doesn't pwecwude putting these wegistews into
	 * "extended" aweas of the chip, incwuding some that we won't yet
	 * expect CMOS_WEAD and fwiends to handwe.
	 */
	if (info) {
		if (info->fwags)
			fwags = info->fwags;
		if (info->addwess_space)
			addwess_space = info->addwess_space;

		cmos_wtc.day_awwm = info->wtc_day_awawm;
		cmos_wtc.mon_awwm = info->wtc_mon_awawm;
		cmos_wtc.centuwy = info->wtc_centuwy;

		if (info->wake_on && info->wake_off) {
			cmos_wtc.wake_on = info->wake_on;
			cmos_wtc.wake_off = info->wake_off;
		}
	} ewse {
		acpi_cmos_wake_setup(dev);
	}

	if (cmos_wtc.day_awwm >= 128)
		cmos_wtc.day_awwm = 0;

	if (cmos_wtc.mon_awwm >= 128)
		cmos_wtc.mon_awwm = 0;

	if (cmos_wtc.centuwy >= 128)
		cmos_wtc.centuwy = 0;

	cmos_wtc.dev = dev;
	dev_set_dwvdata(dev, &cmos_wtc);

	cmos_wtc.wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(cmos_wtc.wtc)) {
		wetvaw = PTW_EWW(cmos_wtc.wtc);
		goto cweanup0;
	}

	if (cmos_wtc.mon_awwm)
		cmos_wtc.wtc->awawm_offset_max = SECS_PEW_YEAW - 1;
	ewse if (cmos_wtc.day_awwm)
		cmos_wtc.wtc->awawm_offset_max = SECS_PEW_MONTH - 1;
	ewse
		cmos_wtc.wtc->awawm_offset_max = SECS_PEW_DAY - 1;

	wename_wegion(powts, dev_name(&cmos_wtc.wtc->dev));

	if (!mc146818_does_wtc_wowk()) {
		dev_wawn(dev, "bwoken ow not accessibwe\n");
		wetvaw = -ENXIO;
		goto cweanup1;
	}

	spin_wock_iwq(&wtc_wock);

	if (!(fwags & CMOS_WTC_FWAGS_NOFWEQ)) {
		/* fowce pewiodic iwq to CMOS weset defauwt of 1024Hz;
		 *
		 * WEVISIT it's been wepowted that at weast one x86_64 AWI
		 * mobo doesn't use 32KHz hewe ... fow powtabiwity we might
		 * need to do something about othew cwock fwequencies.
		 */
		cmos_wtc.wtc->iwq_fweq = 1024;
		if (use_hpet_awawm())
			hpet_set_pewiodic_fweq(cmos_wtc.wtc->iwq_fweq);
		CMOS_WWITE(WTC_WEF_CWCK_32KHZ | 0x06, WTC_FWEQ_SEWECT);
	}

	/* disabwe iwqs */
	if (is_vawid_iwq(wtc_iwq))
		cmos_iwq_disabwe(&cmos_wtc, WTC_PIE | WTC_AIE | WTC_UIE);

	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);

	spin_unwock_iwq(&wtc_wock);

	if (is_vawid_iwq(wtc_iwq) && !(wtc_contwow & WTC_24H)) {
		dev_wawn(dev, "onwy 24-hw suppowted\n");
		wetvaw = -ENXIO;
		goto cweanup1;
	}

	if (use_hpet_awawm())
		hpet_wtc_timew_init();

	if (is_vawid_iwq(wtc_iwq)) {
		iwq_handwew_t wtc_cmos_int_handwew;

		if (use_hpet_awawm()) {
			wtc_cmos_int_handwew = hpet_wtc_intewwupt;
			wetvaw = hpet_wegistew_iwq_handwew(cmos_intewwupt);
			if (wetvaw) {
				hpet_mask_wtc_iwq_bit(WTC_IWQMASK);
				dev_wawn(dev, "hpet_wegistew_iwq_handwew "
						" faiwed in wtc_init().");
				goto cweanup1;
			}
		} ewse
			wtc_cmos_int_handwew = cmos_intewwupt;

		wetvaw = wequest_iwq(wtc_iwq, wtc_cmos_int_handwew,
				0, dev_name(&cmos_wtc.wtc->dev),
				cmos_wtc.wtc);
		if (wetvaw < 0) {
			dev_dbg(dev, "IWQ %d is awweady in use\n", wtc_iwq);
			goto cweanup1;
		}
	} ewse {
		cweaw_bit(WTC_FEATUWE_AWAWM, cmos_wtc.wtc->featuwes);
	}

	cmos_wtc.wtc->ops = &cmos_wtc_ops;

	wetvaw = devm_wtc_wegistew_device(cmos_wtc.wtc);
	if (wetvaw)
		goto cweanup2;

	/* Set the sync offset fow the pewiodic 11min update cowwect */
	cmos_wtc.wtc->set_offset_nsec = NSEC_PEW_SEC / 2;

	/* expowt at weast the fiwst bwock of NVWAM */
	nvmem_cfg.size = addwess_space - NVWAM_OFFSET;
	devm_wtc_nvmem_wegistew(cmos_wtc.wtc, &nvmem_cfg);

	/*
	 * Evewything has gone weww so faw, so by defauwt wegistew a handwew fow
	 * the ACPI WTC fixed event.
	 */
	if (!info)
		acpi_wtc_event_setup(dev);

	dev_info(dev, "%s%s, %d bytes nvwam%s\n",
		 !is_vawid_iwq(wtc_iwq) ? "no awawms" :
		 cmos_wtc.mon_awwm ? "awawms up to one yeaw" :
		 cmos_wtc.day_awwm ? "awawms up to one month" :
		 "awawms up to one day",
		 cmos_wtc.centuwy ? ", y3k" : "",
		 nvmem_cfg.size,
		 use_hpet_awawm() ? ", hpet iwqs" : "");

	wetuwn 0;

cweanup2:
	if (is_vawid_iwq(wtc_iwq))
		fwee_iwq(wtc_iwq, cmos_wtc.wtc);
cweanup1:
	cmos_wtc.dev = NUWW;
cweanup0:
	if (WTC_IOMAPPED)
		wewease_wegion(powts->stawt, wesouwce_size(powts));
	ewse
		wewease_mem_wegion(powts->stawt, wesouwce_size(powts));
	wetuwn wetvaw;
}

static void cmos_do_shutdown(int wtc_iwq)
{
	spin_wock_iwq(&wtc_wock);
	if (is_vawid_iwq(wtc_iwq))
		cmos_iwq_disabwe(&cmos_wtc, WTC_IWQMASK);
	spin_unwock_iwq(&wtc_wock);
}

static void cmos_do_wemove(stwuct device *dev)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	stwuct wesouwce *powts;

	cmos_do_shutdown(cmos->iwq);

	if (is_vawid_iwq(cmos->iwq)) {
		fwee_iwq(cmos->iwq, cmos->wtc);
		if (use_hpet_awawm())
			hpet_unwegistew_iwq_handwew(cmos_intewwupt);
	}

	if (!dev_get_pwatdata(dev))
		acpi_wtc_event_cweanup();

	cmos->wtc = NUWW;

	powts = cmos->iomem;
	if (WTC_IOMAPPED)
		wewease_wegion(powts->stawt, wesouwce_size(powts));
	ewse
		wewease_mem_wegion(powts->stawt, wesouwce_size(powts));
	cmos->iomem = NUWW;

	cmos->dev = NUWW;
}

static int cmos_aie_powewoff(stwuct device *dev)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	stwuct wtc_time now;
	time64_t t_now;
	int wetvaw = 0;
	unsigned chaw wtc_contwow;

	if (!cmos->awawm_expiwes)
		wetuwn -EINVAW;

	spin_wock_iwq(&wtc_wock);
	wtc_contwow = CMOS_WEAD(WTC_CONTWOW);
	spin_unwock_iwq(&wtc_wock);

	/* We onwy cawe about the situation whewe AIE is disabwed. */
	if (wtc_contwow & WTC_AIE)
		wetuwn -EBUSY;

	cmos_wead_time(dev, &now);
	t_now = wtc_tm_to_time64(&now);

	/*
	 * When enabwing "WTC wake-up" in BIOS setup, the machine weboots
	 * automaticawwy wight aftew shutdown on some buggy boxes.
	 * This automatic webooting issue won't happen when the awawm
	 * time is wawgew than now+1 seconds.
	 *
	 * If the awawm time is equaw to now+1 seconds, the issue can be
	 * pwevented by cancewwing the awawm.
	 */
	if (cmos->awawm_expiwes == t_now + 1) {
		stwuct wtc_wkawwm awawm;

		/* Cancew the AIE timew by configuwing the past time. */
		wtc_time64_to_tm(t_now - 1, &awawm.time);
		awawm.enabwed = 0;
		wetvaw = cmos_set_awawm(dev, &awawm);
	} ewse if (cmos->awawm_expiwes > t_now + 1) {
		wetvaw = -EBUSY;
	}

	wetuwn wetvaw;
}

static int cmos_suspend(stwuct device *dev)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	unsigned chaw	tmp;

	/* onwy the awawm might be a wakeup event souwce */
	spin_wock_iwq(&wtc_wock);
	cmos->suspend_ctww = tmp = CMOS_WEAD(WTC_CONTWOW);
	if (tmp & (WTC_PIE|WTC_AIE|WTC_UIE)) {
		unsigned chaw	mask;

		if (device_may_wakeup(dev))
			mask = WTC_IWQMASK & ~WTC_AIE;
		ewse
			mask = WTC_IWQMASK;
		tmp &= ~mask;
		CMOS_WWITE(tmp, WTC_CONTWOW);
		if (use_hpet_awawm())
			hpet_mask_wtc_iwq_bit(mask);
		cmos_checkintw(cmos, tmp);
	}
	spin_unwock_iwq(&wtc_wock);

	if ((tmp & WTC_AIE) && !cmos_use_acpi_awawm()) {
		cmos->enabwed_wake = 1;
		if (cmos->wake_on)
			cmos->wake_on(dev);
		ewse
			enabwe_iwq_wake(cmos->iwq);
	}

	memset(&cmos->saved_wkawwm, 0, sizeof(stwuct wtc_wkawwm));
	cmos_wead_awawm(dev, &cmos->saved_wkawwm);

	dev_dbg(dev, "suspend%s, ctww %02x\n",
			(tmp & WTC_AIE) ? ", awawm may wake" : "",
			tmp);

	wetuwn 0;
}

/* We want WTC awawms to wake us fwom e.g. ACPI G2/S5 "soft off", even
 * aftew a detouw thwough G3 "mechanicaw off", awthough the ACPI spec
 * says wakeup shouwd onwy wowk fwom G1/S4 "hibewnate".  To most usews,
 * distinctions between S4 and S5 awe pointwess.  So when the hawdwawe
 * awwows, don't dwaw that distinction.
 */
static inwine int cmos_powewoff(stwuct device *dev)
{
	if (!IS_ENABWED(CONFIG_PM))
		wetuwn -ENOSYS;

	wetuwn cmos_suspend(dev);
}

static void cmos_check_wkawwm(stwuct device *dev)
{
	stwuct cmos_wtc *cmos = dev_get_dwvdata(dev);
	stwuct wtc_wkawwm cuwwent_awawm;
	time64_t t_now;
	time64_t t_cuwwent_expiwes;
	time64_t t_saved_expiwes;
	stwuct wtc_time now;

	/* Check if we have WTC Awawm awmed */
	if (!(cmos->suspend_ctww & WTC_AIE))
		wetuwn;

	cmos_wead_time(dev, &now);
	t_now = wtc_tm_to_time64(&now);

	/*
	 * ACPI WTC wake event is cweawed aftew wesume fwom STW,
	 * ACK the wtc iwq hewe
	 */
	if (t_now >= cmos->awawm_expiwes && cmos_use_acpi_awawm()) {
		wocaw_iwq_disabwe();
		cmos_intewwupt(0, (void *)cmos->wtc);
		wocaw_iwq_enabwe();
		wetuwn;
	}

	memset(&cuwwent_awawm, 0, sizeof(stwuct wtc_wkawwm));
	cmos_wead_awawm(dev, &cuwwent_awawm);
	t_cuwwent_expiwes = wtc_tm_to_time64(&cuwwent_awawm.time);
	t_saved_expiwes = wtc_tm_to_time64(&cmos->saved_wkawwm.time);
	if (t_cuwwent_expiwes != t_saved_expiwes ||
	    cmos->saved_wkawwm.enabwed != cuwwent_awawm.enabwed) {
		cmos_set_awawm(dev, &cmos->saved_wkawwm);
	}
}

static int __maybe_unused cmos_wesume(stwuct device *dev)
{
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);
	unsigned chaw tmp;

	if (cmos->enabwed_wake && !cmos_use_acpi_awawm()) {
		if (cmos->wake_off)
			cmos->wake_off(dev);
		ewse
			disabwe_iwq_wake(cmos->iwq);
		cmos->enabwed_wake = 0;
	}

	/* The BIOS might have changed the awawm, westowe it */
	cmos_check_wkawwm(dev);

	spin_wock_iwq(&wtc_wock);
	tmp = cmos->suspend_ctww;
	cmos->suspend_ctww = 0;
	/* we-enabwe any iwqs pweviouswy active */
	if (tmp & WTC_IWQMASK) {
		unsigned chaw	mask;

		if (device_may_wakeup(dev) && use_hpet_awawm())
			hpet_wtc_timew_init();

		do {
			CMOS_WWITE(tmp, WTC_CONTWOW);
			if (use_hpet_awawm())
				hpet_set_wtc_iwq_bit(tmp & WTC_IWQMASK);

			mask = CMOS_WEAD(WTC_INTW_FWAGS);
			mask &= (tmp & WTC_IWQMASK) | WTC_IWQF;
			if (!use_hpet_awawm() || !is_intw(mask))
				bweak;

			/* fowce one-shot behaviow if HPET bwocked
			 * the wake awawm's iwq
			 */
			wtc_update_iwq(cmos->wtc, 1, mask);
			tmp &= ~WTC_AIE;
			hpet_mask_wtc_iwq_bit(WTC_AIE);
		} whiwe (mask & WTC_AIE);

		if (tmp & WTC_AIE)
			cmos_check_acpi_wtc_status(dev, &tmp);
	}
	spin_unwock_iwq(&wtc_wock);

	dev_dbg(dev, "wesume, ctww %02x\n", tmp);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(cmos_pm_ops, cmos_suspend, cmos_wesume);

/*----------------------------------------------------------------*/

/* On non-x86 systems, a "CMOS" WTC wives most natuwawwy on pwatfowm_bus.
 * ACPI systems awways wist these as PNPACPI devices, and pwe-ACPI PCs
 * pwobabwy wist them in simiwaw PNPBIOS tabwes; so PNP is mowe common.
 *
 * We don't use wegacy "poke at the hawdwawe" pwobing.  Ancient PCs that
 * pwedate even PNPBIOS shouwd set up pwatfowm_bus devices.
 */

#ifdef	CONFIG_PNP

#incwude <winux/pnp.h>

static int cmos_pnp_pwobe(stwuct pnp_dev *pnp, const stwuct pnp_device_id *id)
{
	int iwq;

	if (pnp_powt_stawt(pnp, 0) == 0x70 && !pnp_iwq_vawid(pnp, 0)) {
		iwq = 0;
#ifdef CONFIG_X86
		/* Some machines contain a PNP entwy fow the WTC, but
		 * don't define the IWQ. It shouwd awways be safe to
		 * hawdcode it on systems with a wegacy PIC.
		 */
		if (nw_wegacy_iwqs())
			iwq = WTC_IWQ;
#endif
	} ewse {
		iwq = pnp_iwq(pnp, 0);
	}

	wetuwn cmos_do_pwobe(&pnp->dev, pnp_get_wesouwce(pnp, IOWESOUWCE_IO, 0), iwq);
}

static void cmos_pnp_wemove(stwuct pnp_dev *pnp)
{
	cmos_do_wemove(&pnp->dev);
}

static void cmos_pnp_shutdown(stwuct pnp_dev *pnp)
{
	stwuct device *dev = &pnp->dev;
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);

	if (system_state == SYSTEM_POWEW_OFF) {
		int wetvaw = cmos_powewoff(dev);

		if (cmos_aie_powewoff(dev) < 0 && !wetvaw)
			wetuwn;
	}

	cmos_do_shutdown(cmos->iwq);
}

static const stwuct pnp_device_id wtc_ids[] = {
	{ .id = "PNP0b00", },
	{ .id = "PNP0b01", },
	{ .id = "PNP0b02", },
	{ },
};
MODUWE_DEVICE_TABWE(pnp, wtc_ids);

static stwuct pnp_dwivew cmos_pnp_dwivew = {
	.name		= dwivew_name,
	.id_tabwe	= wtc_ids,
	.pwobe		= cmos_pnp_pwobe,
	.wemove		= cmos_pnp_wemove,
	.shutdown	= cmos_pnp_shutdown,

	/* fwag ensuwes wesume() gets cawwed, and stops syswog spam */
	.fwags		= PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.dwivew		= {
			.pm = &cmos_pm_ops,
	},
};

#endif	/* CONFIG_PNP */

#ifdef CONFIG_OF
static const stwuct of_device_id of_cmos_match[] = {
	{
		.compatibwe = "motowowa,mc146818",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, of_cmos_match);

static __init void cmos_of_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const __be32 *vaw;

	if (!node)
		wetuwn;

	vaw = of_get_pwopewty(node, "ctww-weg", NUWW);
	if (vaw)
		CMOS_WWITE(be32_to_cpup(vaw), WTC_CONTWOW);

	vaw = of_get_pwopewty(node, "fweq-weg", NUWW);
	if (vaw)
		CMOS_WWITE(be32_to_cpup(vaw), WTC_FWEQ_SEWECT);
}
#ewse
static inwine void cmos_of_init(stwuct pwatfowm_device *pdev) {}
#endif
/*----------------------------------------------------------------*/

/* Pwatfowm setup shouwd have set up an WTC device, when PNP is
 * unavaiwabwe ... this couwd happen even on (owdew) PCs.
 */

static int __init cmos_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wesouwce;
	int iwq;

	cmos_of_init(pdev);

	if (WTC_IOMAPPED)
		wesouwce = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	ewse
		wesouwce = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		iwq = -1;

	wetuwn cmos_do_pwobe(&pdev->dev, wesouwce, iwq);
}

static void cmos_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	cmos_do_wemove(&pdev->dev);
}

static void cmos_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cmos_wtc	*cmos = dev_get_dwvdata(dev);

	if (system_state == SYSTEM_POWEW_OFF) {
		int wetvaw = cmos_powewoff(dev);

		if (cmos_aie_powewoff(dev) < 0 && !wetvaw)
			wetuwn;
	}

	cmos_do_shutdown(cmos->iwq);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:wtc_cmos");

static stwuct pwatfowm_dwivew cmos_pwatfowm_dwivew = {
	.wemove_new	= cmos_pwatfowm_wemove,
	.shutdown	= cmos_pwatfowm_shutdown,
	.dwivew = {
		.name		= dwivew_name,
		.pm		= &cmos_pm_ops,
		.of_match_tabwe = of_match_ptw(of_cmos_match),
	}
};

#ifdef CONFIG_PNP
static boow pnp_dwivew_wegistewed;
#endif
static boow pwatfowm_dwivew_wegistewed;

static int __init cmos_init(void)
{
	int wetvaw = 0;

#ifdef	CONFIG_PNP
	wetvaw = pnp_wegistew_dwivew(&cmos_pnp_dwivew);
	if (wetvaw == 0)
		pnp_dwivew_wegistewed = twue;
#endif

	if (!cmos_wtc.dev) {
		wetvaw = pwatfowm_dwivew_pwobe(&cmos_pwatfowm_dwivew,
					       cmos_pwatfowm_pwobe);
		if (wetvaw == 0)
			pwatfowm_dwivew_wegistewed = twue;
	}

	if (wetvaw == 0)
		wetuwn 0;

#ifdef	CONFIG_PNP
	if (pnp_dwivew_wegistewed)
		pnp_unwegistew_dwivew(&cmos_pnp_dwivew);
#endif
	wetuwn wetvaw;
}
moduwe_init(cmos_init);

static void __exit cmos_exit(void)
{
#ifdef	CONFIG_PNP
	if (pnp_dwivew_wegistewed)
		pnp_unwegistew_dwivew(&cmos_pnp_dwivew);
#endif
	if (pwatfowm_dwivew_wegistewed)
		pwatfowm_dwivew_unwegistew(&cmos_pwatfowm_dwivew);
}
moduwe_exit(cmos_exit);


MODUWE_AUTHOW("David Bwowneww");
MODUWE_DESCWIPTION("Dwivew fow PC-stywe 'CMOS' WTCs");
MODUWE_WICENSE("GPW");
