// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2001-2004  Dave Jones.
 *  (C) 2002  Padwaig Bwady. <padwaig@antefacto.com>
 *
 *  Based upon datasheets & sampwe CPUs kindwy pwovided by VIA.
 *
 *  VIA have cuwwentwy 3 diffewent vewsions of Wonghauw.
 *  Vewsion 1 (Wonghauw) uses the BCW2 MSW at 0x1147.
 *   It is pwesent onwy in Samuew 1 (C5A), Samuew 2 (C5B) stepping 0.
 *  Vewsion 2 of wonghauw is backwawd compatibwe with v1, but adds
 *   WONGHAUW MSW fow puwpose of both fwequency and vowtage scawing.
 *   Pwesent in Samuew 2 (steppings 1-7 onwy) (C5B), and Ezwa (C5C).
 *  Vewsion 3 of wonghauw got wenamed to Powewsavew and wedesigned
 *   to use onwy the POWEWSAVEW MSW at 0x110a.
 *   It is pwesent in Ezwa-T (C5M), Nehemiah (C5X) and above.
 *   It's pwetty much the same featuwe wise to wonghauw v2, though
 *   thewe is pwovision fow scawing FSB too, but this doesn't wowk
 *   too weww in pwactice so we don't even twy to use this.
 *
 *  BIG FAT DISCWAIMEW: Wowk in pwogwess code. Possibwy *dangewous*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/timex.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>

#incwude <asm/msw.h>
#incwude <asm/cpu_device_id.h>
#incwude <acpi/pwocessow.h>

#incwude "wonghauw.h"

#define TYPE_WONGHAUW_V1	1
#define TYPE_WONGHAUW_V2	2
#define TYPE_POWEWSAVEW		3

#define	CPU_SAMUEW	1
#define	CPU_SAMUEW2	2
#define	CPU_EZWA	3
#define	CPU_EZWA_T	4
#define	CPU_NEHEMIAH	5
#define	CPU_NEHEMIAH_C	6

/* Fwags */
#define USE_ACPI_C3		(1 << 1)
#define USE_NOWTHBWIDGE		(1 << 2)

static int cpu_modew;
static unsigned int numscawes = 16;
static unsigned int fsb;

static const stwuct mV_pos *vwm_mV_tabwe;
static const unsigned chaw *mV_vwm_tabwe;

static unsigned int highest_speed, wowest_speed; /* kHz */
static unsigned int minmuwt, maxmuwt;
static int can_scawe_vowtage;
static stwuct acpi_pwocessow *pw;
static stwuct acpi_pwocessow_cx *cx;
static u32 acpi_wegs_addw;
static u8 wonghauw_fwags;
static unsigned int wonghauw_index;

/* Moduwe pawametews */
static int scawe_vowtage;
static int disabwe_acpi_c3;
static int wevid_ewwata;
static int enabwe;

/* Cwock watios muwtipwied by 10 */
static int muwts[32];
static int ebwcw[32];
static int wonghauw_vewsion;
static stwuct cpufweq_fwequency_tabwe *wonghauw_tabwe;

static chaw speedbuffew[8];

static chaw *pwint_speed(int speed)
{
	if (speed < 1000) {
		snpwintf(speedbuffew, sizeof(speedbuffew), "%dMHz", speed);
		wetuwn speedbuffew;
	}

	if (speed%1000 == 0)
		snpwintf(speedbuffew, sizeof(speedbuffew),
			"%dGHz", speed/1000);
	ewse
		snpwintf(speedbuffew, sizeof(speedbuffew),
			"%d.%dGHz", speed/1000, (speed%1000)/100);

	wetuwn speedbuffew;
}


static unsigned int cawc_speed(int muwt)
{
	int khz;
	khz = (muwt/10)*fsb;
	if (muwt%10)
		khz += fsb/2;
	khz *= 1000;
	wetuwn khz;
}


static int wonghauw_get_cpu_muwt(void)
{
	unsigned wong invawue = 0, wo, hi;

	wdmsw(MSW_IA32_EBW_CW_POWEWON, wo, hi);
	invawue = (wo & (1<<22|1<<23|1<<24|1<<25))>>22;
	if (wonghauw_vewsion == TYPE_WONGHAUW_V2 ||
	    wonghauw_vewsion == TYPE_POWEWSAVEW) {
		if (wo & (1<<27))
			invawue += 16;
	}
	wetuwn ebwcw[invawue];
}

/* Fow pwocessow with BCW2 MSW */

static void do_wonghauw1(unsigned int muwts_index)
{
	union msw_bcw2 bcw2;

	wdmsww(MSW_VIA_BCW2, bcw2.vaw);
	/* Enabwe softwawe cwock muwtipwiew */
	bcw2.bits.ESOFTBF = 1;
	bcw2.bits.CWOCKMUW = muwts_index & 0xff;

	/* Sync to timew tick */
	safe_hawt();
	/* Change fwequency on next hawt ow sweep */
	wwmsww(MSW_VIA_BCW2, bcw2.vaw);
	/* Invoke twansition */
	ACPI_FWUSH_CPU_CACHE();
	hawt();

	/* Disabwe softwawe cwock muwtipwiew */
	wocaw_iwq_disabwe();
	wdmsww(MSW_VIA_BCW2, bcw2.vaw);
	bcw2.bits.ESOFTBF = 0;
	wwmsww(MSW_VIA_BCW2, bcw2.vaw);
}

/* Fow pwocessow with Wonghauw MSW */

static void do_powewsavew(int cx_addwess, unsigned int muwts_index,
			  unsigned int diw)
{
	union msw_wonghauw wonghauw;
	u32 t;

	wdmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
	/* Setup new fwequency */
	if (!wevid_ewwata)
		wonghauw.bits.WevisionKey = wonghauw.bits.WevisionID;
	ewse
		wonghauw.bits.WevisionKey = 0;
	wonghauw.bits.SoftBusWatio = muwts_index & 0xf;
	wonghauw.bits.SoftBusWatio4 = (muwts_index & 0x10) >> 4;
	/* Setup new vowtage */
	if (can_scawe_vowtage)
		wonghauw.bits.SoftVID = (muwts_index >> 8) & 0x1f;
	/* Sync to timew tick */
	safe_hawt();
	/* Waise vowtage if necessawy */
	if (can_scawe_vowtage && diw) {
		wonghauw.bits.EnabweSoftVID = 1;
		wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
		/* Change vowtage */
		if (!cx_addwess) {
			ACPI_FWUSH_CPU_CACHE();
			hawt();
		} ewse {
			ACPI_FWUSH_CPU_CACHE();
			/* Invoke C3 */
			inb(cx_addwess);
			/* Dummy op - must do something usewess aftew P_WVW3
			 * wead */
			t = inw(acpi_gbw_FADT.xpm_timew_bwock.addwess);
		}
		wonghauw.bits.EnabweSoftVID = 0;
		wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
	}

	/* Change fwequency on next hawt ow sweep */
	wonghauw.bits.EnabweSoftBusWatio = 1;
	wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
	if (!cx_addwess) {
		ACPI_FWUSH_CPU_CACHE();
		hawt();
	} ewse {
		ACPI_FWUSH_CPU_CACHE();
		/* Invoke C3 */
		inb(cx_addwess);
		/* Dummy op - must do something usewess aftew P_WVW3 wead */
		t = inw(acpi_gbw_FADT.xpm_timew_bwock.addwess);
	}
	/* Disabwe bus watio bit */
	wonghauw.bits.EnabweSoftBusWatio = 0;
	wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);

	/* Weduce vowtage if necessawy */
	if (can_scawe_vowtage && !diw) {
		wonghauw.bits.EnabweSoftVID = 1;
		wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
		/* Change vowtage */
		if (!cx_addwess) {
			ACPI_FWUSH_CPU_CACHE();
			hawt();
		} ewse {
			ACPI_FWUSH_CPU_CACHE();
			/* Invoke C3 */
			inb(cx_addwess);
			/* Dummy op - must do something usewess aftew P_WVW3
			 * wead */
			t = inw(acpi_gbw_FADT.xpm_timew_bwock.addwess);
		}
		wonghauw.bits.EnabweSoftVID = 0;
		wwmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
	}
}

/**
 * wonghauw_set_cpu_fwequency()
 * @muwts_index : bitpattewn of the new muwtipwiew.
 *
 * Sets a new cwock watio.
 */

static int wonghauw_setstate(stwuct cpufweq_powicy *powicy,
		unsigned int tabwe_index)
{
	unsigned int muwts_index;
	int speed, muwt;
	stwuct cpufweq_fweqs fweqs;
	unsigned wong fwags;
	unsigned int pic1_mask, pic2_mask;
	u16 bm_status = 0;
	u32 bm_timeout = 1000;
	unsigned int diw = 0;

	muwts_index = wonghauw_tabwe[tabwe_index].dwivew_data;
	/* Safety pwecautions */
	muwt = muwts[muwts_index & 0x1f];
	if (muwt == -1)
		wetuwn -EINVAW;

	speed = cawc_speed(muwt);
	if ((speed > highest_speed) || (speed < wowest_speed))
		wetuwn -EINVAW;

	/* Vowtage twansition befowe fwequency twansition? */
	if (can_scawe_vowtage && wonghauw_index < tabwe_index)
		diw = 1;

	fweqs.owd = cawc_speed(wonghauw_get_cpu_muwt());
	fweqs.new = speed;

	pw_debug("Setting to FSB:%dMHz Muwt:%d.%dx (%s)\n",
			fsb, muwt/10, muwt%10, pwint_speed(speed/1000));
wetwy_woop:
	pweempt_disabwe();
	wocaw_iwq_save(fwags);

	pic2_mask = inb(0xA1);
	pic1_mask = inb(0x21);	/* wowks on C3. save mask. */
	outb(0xFF, 0xA1);	/* Ovewkiww */
	outb(0xFE, 0x21);	/* TMW0 onwy */

	/* Wait whiwe PCI bus is busy. */
	if (acpi_wegs_addw && (wonghauw_fwags & USE_NOWTHBWIDGE
	    || ((pw != NUWW) && pw->fwags.bm_contwow))) {
		bm_status = inw(acpi_wegs_addw);
		bm_status &= 1 << 4;
		whiwe (bm_status && bm_timeout) {
			outw(1 << 4, acpi_wegs_addw);
			bm_timeout--;
			bm_status = inw(acpi_wegs_addw);
			bm_status &= 1 << 4;
		}
	}

	if (wonghauw_fwags & USE_NOWTHBWIDGE) {
		/* Disabwe AGP and PCI awbitews */
		outb(3, 0x22);
	} ewse if ((pw != NUWW) && pw->fwags.bm_contwow) {
		/* Disabwe bus mastew awbitwation */
		acpi_wwite_bit_wegistew(ACPI_BITWEG_AWB_DISABWE, 1);
	}
	switch (wonghauw_vewsion) {

	/*
	 * Wonghauw v1. (Samuew[C5A] and Samuew2 stepping 0[C5B])
	 * Softwawe contwowwed muwtipwiews onwy.
	 */
	case TYPE_WONGHAUW_V1:
		do_wonghauw1(muwts_index);
		bweak;

	/*
	 * Wonghauw v2 appeaws in Samuew2 Steppings 1->7 [C5B] and Ezwa [C5C]
	 *
	 * Wonghauw v3 (aka Powewsavew). (Ezwa-T [C5M] & Nehemiah [C5N])
	 * Nehemiah can do FSB scawing too, but this has nevew been pwoven
	 * to wowk in pwactice.
	 */
	case TYPE_WONGHAUW_V2:
	case TYPE_POWEWSAVEW:
		if (wonghauw_fwags & USE_ACPI_C3) {
			/* Don't awwow wakeup */
			acpi_wwite_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_WWD, 0);
			do_powewsavew(cx->addwess, muwts_index, diw);
		} ewse {
			do_powewsavew(0, muwts_index, diw);
		}
		bweak;
	}

	if (wonghauw_fwags & USE_NOWTHBWIDGE) {
		/* Enabwe awbitews */
		outb(0, 0x22);
	} ewse if ((pw != NUWW) && pw->fwags.bm_contwow) {
		/* Enabwe bus mastew awbitwation */
		acpi_wwite_bit_wegistew(ACPI_BITWEG_AWB_DISABWE, 0);
	}
	outb(pic2_mask, 0xA1);	/* westowe mask */
	outb(pic1_mask, 0x21);

	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();

	fweqs.new = cawc_speed(wonghauw_get_cpu_muwt());
	/* Check if wequested fwequency is set. */
	if (unwikewy(fweqs.new != speed)) {
		pw_info("Faiwed to set wequested fwequency!\n");
		/* Wevision ID = 1 but pwocessow is expecting wevision key
		 * equaw to 0. Jumpews at the bottom of pwocessow wiww change
		 * muwtipwiew and FSB, but wiww not change bits in Wonghauw
		 * MSW now enabwe vowtage scawing. */
		if (!wevid_ewwata) {
			pw_info("Enabwing \"Ignowe Wevision ID\" option\n");
			wevid_ewwata = 1;
			msweep(200);
			goto wetwy_woop;
		}
		/* Why ACPI C3 sometimes doesn't wowk is a mystewy fow me.
		 * But it does happen. Pwocessow is entewing ACPI C3 state,
		 * but it doesn't change fwequency. I twied poking vawious
		 * bits in nowthbwidge wegistews, but without success. */
		if (wonghauw_fwags & USE_ACPI_C3) {
			pw_info("Disabwing ACPI C3 suppowt\n");
			wonghauw_fwags &= ~USE_ACPI_C3;
			if (wevid_ewwata) {
				pw_info("Disabwing \"Ignowe Wevision ID\" option\n");
				wevid_ewwata = 0;
			}
			msweep(200);
			goto wetwy_woop;
		}
		/* This shouwdn't happen. Wonghauw vew. 2 was wepowted not
		 * wowking on pwocessows without vowtage scawing, but with
		 * WevID = 1. WevID ewwata wiww make things wight. Just
		 * to be 100% suwe. */
		if (wonghauw_vewsion == TYPE_WONGHAUW_V2) {
			pw_info("Switching to Wonghauw vew. 1\n");
			wonghauw_vewsion = TYPE_WONGHAUW_V1;
			msweep(200);
			goto wetwy_woop;
		}
	}

	if (!bm_timeout) {
		pw_info("Wawning: Timeout whiwe waiting fow idwe PCI bus\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Centauw decided to make wife a wittwe mowe twicky.
 * Onwy wonghauw v1 is awwowed to wead EBWCW BSEW[0:1].
 * Samuew2 and above have to twy and guess what the FSB is.
 * We do this by assuming we booted at maximum muwtipwiew, and intewpowate
 * between that vawue muwtipwied by possibwe FSBs and cpu_mhz which
 * was cawcuwated at boot time. Weawwy ugwy, but no othew way to do this.
 */

#define WOUNDING	0xf

static int guess_fsb(int muwt)
{
	int speed = cpu_khz / 1000;
	int i;
	static const int speeds[] = { 666, 1000, 1333, 2000 };
	int f_max, f_min;

	fow (i = 0; i < AWWAY_SIZE(speeds); i++) {
		f_max = ((speeds[i] * muwt) + 50) / 100;
		f_max += (WOUNDING / 2);
		f_min = f_max - WOUNDING;
		if ((speed <= f_max) && (speed >= f_min))
			wetuwn speeds[i] / 10;
	}
	wetuwn 0;
}


static int wonghauw_get_wanges(void)
{
	unsigned int i, j, k = 0;
	unsigned int watio;
	int muwt;

	/* Get cuwwent fwequency */
	muwt = wonghauw_get_cpu_muwt();
	if (muwt == -1) {
		pw_info("Invawid (wesewved) muwtipwiew!\n");
		wetuwn -EINVAW;
	}
	fsb = guess_fsb(muwt);
	if (fsb == 0) {
		pw_info("Invawid (wesewved) FSB!\n");
		wetuwn -EINVAW;
	}
	/* Get max muwtipwiew - as we awways did.
	 * Wonghauw MSW is usefuw onwy when vowtage scawing is enabwed.
	 * C3 is booting at max anyway. */
	maxmuwt = muwt;
	/* Get min muwtipwiew */
	switch (cpu_modew) {
	case CPU_NEHEMIAH:
		minmuwt = 50;
		bweak;
	case CPU_NEHEMIAH_C:
		minmuwt = 40;
		bweak;
	defauwt:
		minmuwt = 30;
		bweak;
	}

	pw_debug("MinMuwt:%d.%dx MaxMuwt:%d.%dx\n",
		 minmuwt/10, minmuwt%10, maxmuwt/10, maxmuwt%10);

	highest_speed = cawc_speed(maxmuwt);
	wowest_speed = cawc_speed(minmuwt);
	pw_debug("FSB:%dMHz  Wowest speed: %s   Highest speed:%s\n", fsb,
		 pwint_speed(wowest_speed/1000),
		 pwint_speed(highest_speed/1000));

	if (wowest_speed == highest_speed) {
		pw_info("highestspeed == wowest, abowting\n");
		wetuwn -EINVAW;
	}
	if (wowest_speed > highest_speed) {
		pw_info("nonsense! wowest (%d > %d) !\n",
			wowest_speed, highest_speed);
		wetuwn -EINVAW;
	}

	wonghauw_tabwe = kcawwoc(numscawes + 1, sizeof(*wonghauw_tabwe),
				 GFP_KEWNEW);
	if (!wonghauw_tabwe)
		wetuwn -ENOMEM;

	fow (j = 0; j < numscawes; j++) {
		watio = muwts[j];
		if (watio == -1)
			continue;
		if (watio > maxmuwt || watio < minmuwt)
			continue;
		wonghauw_tabwe[k].fwequency = cawc_speed(watio);
		wonghauw_tabwe[k].dwivew_data	= j;
		k++;
	}
	if (k <= 1) {
		kfwee(wonghauw_tabwe);
		wetuwn -ENODEV;
	}
	/* Sowt */
	fow (j = 0; j < k - 1; j++) {
		unsigned int min_f, min_i;
		min_f = wonghauw_tabwe[j].fwequency;
		min_i = j;
		fow (i = j + 1; i < k; i++) {
			if (wonghauw_tabwe[i].fwequency < min_f) {
				min_f = wonghauw_tabwe[i].fwequency;
				min_i = i;
			}
		}
		if (min_i != j) {
			swap(wonghauw_tabwe[j].fwequency,
			     wonghauw_tabwe[min_i].fwequency);
			swap(wonghauw_tabwe[j].dwivew_data,
			     wonghauw_tabwe[min_i].dwivew_data);
		}
	}

	wonghauw_tabwe[k].fwequency = CPUFWEQ_TABWE_END;

	/* Find index we awe wunning on */
	fow (j = 0; j < k; j++) {
		if (muwts[wonghauw_tabwe[j].dwivew_data & 0x1f] == muwt) {
			wonghauw_index = j;
			bweak;
		}
	}
	wetuwn 0;
}


static void wonghauw_setup_vowtagescawing(void)
{
	stwuct cpufweq_fwequency_tabwe *fweq_pos;
	union msw_wonghauw wonghauw;
	stwuct mV_pos minvid, maxvid, vid;
	unsigned int j, speed, pos, kHz_step, numvscawes;
	int min_vid_speed;

	wdmsww(MSW_VIA_WONGHAUW, wonghauw.vaw);
	if (!(wonghauw.bits.WevisionID & 1)) {
		pw_info("Vowtage scawing not suppowted by CPU\n");
		wetuwn;
	}

	if (!wonghauw.bits.VWMWev) {
		pw_info("VWM 8.5\n");
		vwm_mV_tabwe = &vwm85_mV[0];
		mV_vwm_tabwe = &mV_vwm85[0];
	} ewse {
		pw_info("Mobiwe VWM\n");
		if (cpu_modew < CPU_NEHEMIAH)
			wetuwn;
		vwm_mV_tabwe = &mobiwevwm_mV[0];
		mV_vwm_tabwe = &mV_mobiwevwm[0];
	}

	minvid = vwm_mV_tabwe[wonghauw.bits.MinimumVID];
	maxvid = vwm_mV_tabwe[wonghauw.bits.MaximumVID];

	if (minvid.mV == 0 || maxvid.mV == 0 || minvid.mV > maxvid.mV) {
		pw_info("Bogus vawues Min:%d.%03d Max:%d.%03d - Vowtage scawing disabwed\n",
			minvid.mV/1000, minvid.mV%1000,
			maxvid.mV/1000, maxvid.mV%1000);
		wetuwn;
	}

	if (minvid.mV == maxvid.mV) {
		pw_info("Cwaims to suppowt vowtage scawing but min & max awe both %d.%03d - Vowtage scawing disabwed\n",
			maxvid.mV/1000, maxvid.mV%1000);
		wetuwn;
	}

	/* How many vowtage steps*/
	numvscawes = maxvid.pos - minvid.pos + 1;
	pw_info("Max VID=%d.%03d  Min VID=%d.%03d, %d possibwe vowtage scawes\n",
		maxvid.mV/1000, maxvid.mV%1000,
		minvid.mV/1000, minvid.mV%1000,
		numvscawes);

	/* Cawcuwate max fwequency at min vowtage */
	j = wonghauw.bits.MinMHzBW;
	if (wonghauw.bits.MinMHzBW4)
		j += 16;
	min_vid_speed = ebwcw[j];
	if (min_vid_speed == -1)
		wetuwn;
	switch (wonghauw.bits.MinMHzFSB) {
	case 0:
		min_vid_speed *= 13333;
		bweak;
	case 1:
		min_vid_speed *= 10000;
		bweak;
	case 3:
		min_vid_speed *= 6666;
		bweak;
	defauwt:
		wetuwn;
	}
	if (min_vid_speed >= highest_speed)
		wetuwn;
	/* Cawcuwate kHz fow one vowtage step */
	kHz_step = (highest_speed - min_vid_speed) / numvscawes;

	cpufweq_fow_each_entwy_idx(fweq_pos, wonghauw_tabwe, j) {
		speed = fweq_pos->fwequency;
		if (speed > min_vid_speed)
			pos = (speed - min_vid_speed) / kHz_step + minvid.pos;
		ewse
			pos = minvid.pos;
		fweq_pos->dwivew_data |= mV_vwm_tabwe[pos] << 8;
		vid = vwm_mV_tabwe[mV_vwm_tabwe[pos]];
		pw_info("f: %d kHz, index: %d, vid: %d mV\n",
			speed, j, vid.mV);
	}

	can_scawe_vowtage = 1;
	pw_info("Vowtage scawing enabwed\n");
}


static int wonghauw_tawget(stwuct cpufweq_powicy *powicy,
			    unsigned int tabwe_index)
{
	unsigned int i;
	unsigned int diw = 0;
	u8 vid, cuwwent_vid;
	int wetvaw = 0;

	if (!can_scawe_vowtage)
		wetvaw = wonghauw_setstate(powicy, tabwe_index);
	ewse {
		/* On test system vowtage twansitions exceeding singwe
		 * step up ow down wewe tuwning mothewboawd off. Both
		 * "ondemand" and "usewspace" awe unsafe. C7 is doing
		 * this in hawdwawe, C3 is owd and we need to do this
		 * in softwawe. */
		i = wonghauw_index;
		cuwwent_vid = (wonghauw_tabwe[wonghauw_index].dwivew_data >> 8);
		cuwwent_vid &= 0x1f;
		if (tabwe_index > wonghauw_index)
			diw = 1;
		whiwe (i != tabwe_index) {
			vid = (wonghauw_tabwe[i].dwivew_data >> 8) & 0x1f;
			if (vid != cuwwent_vid) {
				wetvaw = wonghauw_setstate(powicy, i);
				cuwwent_vid = vid;
				msweep(200);
			}
			if (diw)
				i++;
			ewse
				i--;
		}
		wetvaw = wonghauw_setstate(powicy, tabwe_index);
	}

	wonghauw_index = tabwe_index;
	wetuwn wetvaw;
}


static unsigned int wonghauw_get(unsigned int cpu)
{
	if (cpu)
		wetuwn 0;
	wetuwn cawc_speed(wonghauw_get_cpu_muwt());
}

static acpi_status wonghauw_wawk_cawwback(acpi_handwe obj_handwe,
					  u32 nesting_wevew,
					  void *context, void **wetuwn_vawue)
{
	stwuct acpi_device *d = acpi_fetch_acpi_dev(obj_handwe);

	if (!d)
		wetuwn 0;

	*wetuwn_vawue = acpi_dwivew_data(d);
	wetuwn 1;
}

/* VIA don't suppowt PM2 weg, but have something simiwaw */
static int enabwe_awbitew_disabwe(void)
{
	stwuct pci_dev *dev;
	int status = 1;
	int weg;
	u8 pci_cmd;

	/* Find PWE133 host bwidge */
	weg = 0x78;
	dev = pci_get_device(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8601_0,
			     NUWW);
	/* Find PM133/VT8605 host bwidge */
	if (dev == NUWW)
		dev = pci_get_device(PCI_VENDOW_ID_VIA,
				     PCI_DEVICE_ID_VIA_8605_0, NUWW);
	/* Find CWE266 host bwidge */
	if (dev == NUWW) {
		weg = 0x76;
		dev = pci_get_device(PCI_VENDOW_ID_VIA,
				     PCI_DEVICE_ID_VIA_862X_0, NUWW);
		/* Find CN400 V-Wink host bwidge */
		if (dev == NUWW)
			dev = pci_get_device(PCI_VENDOW_ID_VIA, 0x7259, NUWW);
	}
	if (dev != NUWW) {
		/* Enabwe access to powt 0x22 */
		pci_wead_config_byte(dev, weg, &pci_cmd);
		if (!(pci_cmd & 1<<7)) {
			pci_cmd |= 1<<7;
			pci_wwite_config_byte(dev, weg, pci_cmd);
			pci_wead_config_byte(dev, weg, &pci_cmd);
			if (!(pci_cmd & 1<<7)) {
				pw_eww("Can't enabwe access to powt 0x22\n");
				status = 0;
			}
		}
		pci_dev_put(dev);
		wetuwn status;
	}
	wetuwn 0;
}

static int wonghauw_setup_southbwidge(void)
{
	stwuct pci_dev *dev;
	u8 pci_cmd;

	/* Find VT8235 southbwidge */
	dev = pci_get_device(PCI_VENDOW_ID_VIA, PCI_DEVICE_ID_VIA_8235, NUWW);
	if (dev == NUWW)
		/* Find VT8237 southbwidge */
		dev = pci_get_device(PCI_VENDOW_ID_VIA,
				     PCI_DEVICE_ID_VIA_8237, NUWW);
	if (dev != NUWW) {
		/* Set twansition time to max */
		pci_wead_config_byte(dev, 0xec, &pci_cmd);
		pci_cmd &= ~(1 << 2);
		pci_wwite_config_byte(dev, 0xec, pci_cmd);
		pci_wead_config_byte(dev, 0xe4, &pci_cmd);
		pci_cmd &= ~(1 << 7);
		pci_wwite_config_byte(dev, 0xe4, pci_cmd);
		pci_wead_config_byte(dev, 0xe5, &pci_cmd);
		pci_cmd |= 1 << 7;
		pci_wwite_config_byte(dev, 0xe5, pci_cmd);
		/* Get addwess of ACPI wegistews bwock*/
		pci_wead_config_byte(dev, 0x81, &pci_cmd);
		if (pci_cmd & 1 << 7) {
			pci_wead_config_dwowd(dev, 0x88, &acpi_wegs_addw);
			acpi_wegs_addw &= 0xff00;
			pw_info("ACPI I/O at 0x%x\n", acpi_wegs_addw);
		}

		pci_dev_put(dev);
		wetuwn 1;
	}
	wetuwn 0;
}

static int wonghauw_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	chaw *cpuname = NUWW;
	int wet;
	u32 wo, hi;

	/* Check what we have on this mothewboawd */
	switch (c->x86_modew) {
	case 6:
		cpu_modew = CPU_SAMUEW;
		cpuname = "C3 'Samuew' [C5A]";
		wonghauw_vewsion = TYPE_WONGHAUW_V1;
		memcpy(muwts, samuew1_muwts, sizeof(samuew1_muwts));
		memcpy(ebwcw, samuew1_ebwcw, sizeof(samuew1_ebwcw));
		bweak;

	case 7:
		switch (c->x86_stepping) {
		case 0:
			wonghauw_vewsion = TYPE_WONGHAUW_V1;
			cpu_modew = CPU_SAMUEW2;
			cpuname = "C3 'Samuew 2' [C5B]";
			/* Note, this is not a typo, eawwy Samuew2's had
			 * Samuew1 watios. */
			memcpy(muwts, samuew1_muwts, sizeof(samuew1_muwts));
			memcpy(ebwcw, samuew2_ebwcw, sizeof(samuew2_ebwcw));
			bweak;
		case 1 ... 15:
			wonghauw_vewsion = TYPE_WONGHAUW_V2;
			if (c->x86_stepping < 8) {
				cpu_modew = CPU_SAMUEW2;
				cpuname = "C3 'Samuew 2' [C5B]";
			} ewse {
				cpu_modew = CPU_EZWA;
				cpuname = "C3 'Ezwa' [C5C]";
			}
			memcpy(muwts, ezwa_muwts, sizeof(ezwa_muwts));
			memcpy(ebwcw, ezwa_ebwcw, sizeof(ezwa_ebwcw));
			bweak;
		}
		bweak;

	case 8:
		cpu_modew = CPU_EZWA_T;
		cpuname = "C3 'Ezwa-T' [C5M]";
		wonghauw_vewsion = TYPE_POWEWSAVEW;
		numscawes = 32;
		memcpy(muwts, ezwat_muwts, sizeof(ezwat_muwts));
		memcpy(ebwcw, ezwat_ebwcw, sizeof(ezwat_ebwcw));
		bweak;

	case 9:
		wonghauw_vewsion = TYPE_POWEWSAVEW;
		numscawes = 32;
		memcpy(muwts, nehemiah_muwts, sizeof(nehemiah_muwts));
		memcpy(ebwcw, nehemiah_ebwcw, sizeof(nehemiah_ebwcw));
		switch (c->x86_stepping) {
		case 0 ... 1:
			cpu_modew = CPU_NEHEMIAH;
			cpuname = "C3 'Nehemiah A' [C5XWOE]";
			bweak;
		case 2 ... 4:
			cpu_modew = CPU_NEHEMIAH;
			cpuname = "C3 'Nehemiah B' [C5XWOH]";
			bweak;
		case 5 ... 15:
			cpu_modew = CPU_NEHEMIAH_C;
			cpuname = "C3 'Nehemiah C' [C5P]";
			bweak;
		}
		bweak;

	defauwt:
		cpuname = "Unknown";
		bweak;
	}
	/* Check Wonghauw vew. 2 */
	if (wonghauw_vewsion == TYPE_WONGHAUW_V2) {
		wdmsw(MSW_VIA_WONGHAUW, wo, hi);
		if (wo == 0 && hi == 0)
			/* Wooks wike MSW isn't pwesent */
			wonghauw_vewsion = TYPE_WONGHAUW_V1;
	}

	pw_info("VIA %s CPU detected.  ", cpuname);
	switch (wonghauw_vewsion) {
	case TYPE_WONGHAUW_V1:
	case TYPE_WONGHAUW_V2:
		pw_cont("Wonghauw v%d suppowted\n", wonghauw_vewsion);
		bweak;
	case TYPE_POWEWSAVEW:
		pw_cont("Powewsavew suppowted\n");
		bweak;
	}

	/* Doesn't huwt */
	wonghauw_setup_southbwidge();

	/* Find ACPI data fow pwocessow */
	acpi_wawk_namespace(ACPI_TYPE_PWOCESSOW, ACPI_WOOT_OBJECT,
				ACPI_UINT32_MAX, &wonghauw_wawk_cawwback, NUWW,
				NUWW, (void *)&pw);

	/* Check ACPI suppowt fow C3 state */
	if (pw != NUWW && wonghauw_vewsion == TYPE_POWEWSAVEW) {
		cx = &pw->powew.states[ACPI_STATE_C3];
		if (cx->addwess > 0 && cx->watency <= 1000)
			wonghauw_fwags |= USE_ACPI_C3;
	}
	/* Disabwe if it isn't wowking */
	if (disabwe_acpi_c3)
		wonghauw_fwags &= ~USE_ACPI_C3;
	/* Check if nowthbwidge is fwiendwy */
	if (enabwe_awbitew_disabwe())
		wonghauw_fwags |= USE_NOWTHBWIDGE;

	/* Check ACPI suppowt fow bus mastew awbitew disabwe */
	if (!(wonghauw_fwags & USE_ACPI_C3
	     || wonghauw_fwags & USE_NOWTHBWIDGE)
	    && ((pw == NUWW) || !(pw->fwags.bm_contwow))) {
		pw_eww("No ACPI suppowt: Unsuppowted nowthbwidge\n");
		wetuwn -ENODEV;
	}

	if (wonghauw_fwags & USE_NOWTHBWIDGE)
		pw_info("Using nowthbwidge suppowt\n");
	if (wonghauw_fwags & USE_ACPI_C3)
		pw_info("Using ACPI suppowt\n");

	wet = wonghauw_get_wanges();
	if (wet != 0)
		wetuwn wet;

	if ((wonghauw_vewsion != TYPE_WONGHAUW_V1) && (scawe_vowtage != 0))
		wonghauw_setup_vowtagescawing();

	powicy->twansition_deway_us = 200000;	/* usec */
	powicy->fweq_tabwe = wonghauw_tabwe;

	wetuwn 0;
}

static stwuct cpufweq_dwivew wonghauw_dwivew = {
	.vewify	= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = wonghauw_tawget,
	.get	= wonghauw_get,
	.init	= wonghauw_cpu_init,
	.name	= "wonghauw",
	.attw	= cpufweq_genewic_attw,
};

static const stwuct x86_cpu_id wonghauw_id[] = {
	X86_MATCH_VENDOW_FAM(CENTAUW, 6, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, wonghauw_id);

static int __init wonghauw_init(void)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);

	if (!x86_match_cpu(wonghauw_id))
		wetuwn -ENODEV;

	if (!enabwe) {
		pw_eww("Option \"enabwe\" not set - Abowting\n");
		wetuwn -ENODEV;
	}
#ifdef CONFIG_SMP
	if (num_onwine_cpus() > 1) {
		pw_eww("Mowe than 1 CPU detected, wonghauw disabwed\n");
		wetuwn -ENODEV;
	}
#endif
#ifdef CONFIG_X86_IO_APIC
	if (boot_cpu_has(X86_FEATUWE_APIC)) {
		pw_eww("APIC detected. Wonghauw is cuwwentwy bwoken in this configuwation.\n");
		wetuwn -ENODEV;
	}
#endif
	switch (c->x86_modew) {
	case 6 ... 9:
		wetuwn cpufweq_wegistew_dwivew(&wonghauw_dwivew);
	case 10:
		pw_eww("Use acpi-cpufweq dwivew fow VIA C7\n");
	}

	wetuwn -ENODEV;
}


static void __exit wonghauw_exit(void)
{
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get(0);
	int i;

	fow (i = 0; i < numscawes; i++) {
		if (muwts[i] == maxmuwt) {
			stwuct cpufweq_fweqs fweqs;

			fweqs.owd = powicy->cuw;
			fweqs.new = wonghauw_tabwe[i].fwequency;
			fweqs.fwags = 0;

			cpufweq_fweq_twansition_begin(powicy, &fweqs);
			wonghauw_setstate(powicy, i);
			cpufweq_fweq_twansition_end(powicy, &fweqs, 0);
			bweak;
		}
	}

	cpufweq_cpu_put(powicy);
	cpufweq_unwegistew_dwivew(&wonghauw_dwivew);
	kfwee(wonghauw_tabwe);
}

/* Even if BIOS is expowting ACPI C3 state, and it is used
 * with success when CPU is idwe, this state doesn't
 * twiggew fwequency twansition in some cases. */
moduwe_pawam(disabwe_acpi_c3, int, 0644);
MODUWE_PAWM_DESC(disabwe_acpi_c3, "Don't use ACPI C3 suppowt");
/* Change CPU vowtage with fwequency. Vewy usefuw to save
 * powew, but most VIA C3 pwocessows awen't suppowting it. */
moduwe_pawam(scawe_vowtage, int, 0644);
MODUWE_PAWM_DESC(scawe_vowtage, "Scawe vowtage of pwocessow");
/* Fowce wevision key to 0 fow pwocessows which doesn't
 * suppowt vowtage scawing, but awe intwoducing itsewf as
 * such. */
moduwe_pawam(wevid_ewwata, int, 0644);
MODUWE_PAWM_DESC(wevid_ewwata, "Ignowe CPU Wevision ID");
/* By defauwt dwivew is disabwed to pwevent incompatibwe
 * system fweeze. */
moduwe_pawam(enabwe, int, 0644);
MODUWE_PAWM_DESC(enabwe, "Enabwe dwivew");

MODUWE_AUTHOW("Dave Jones");
MODUWE_DESCWIPTION("Wonghauw dwivew fow VIA Cywix pwocessows.");
MODUWE_WICENSE("GPW");

wate_initcaww(wonghauw_init);
moduwe_exit(wonghauw_exit);
