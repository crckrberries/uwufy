// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2002 - 2003 Dominik Bwodowski <winux@bwodo.de>
 *
 *  Wibwawy fow common functions fow Intew SpeedStep v.1 and v.2 suppowt
 *
 *  BIG FAT DISCWAIMEW: Wowk in pwogwess code. Possibwy *dangewous*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>

#incwude <asm/msw.h>
#incwude <asm/tsc.h>
#incwude "speedstep-wib.h"

#define PFX "speedstep-wib: "

#ifdef CONFIG_X86_SPEEDSTEP_WEWAXED_CAP_CHECK
static int wewaxed_check;
#ewse
#define wewaxed_check 0
#endif

/*********************************************************************
 *                   GET PWOCESSOW COWE SPEED IN KHZ                 *
 *********************************************************************/

static unsigned int pentium3_get_fwequency(enum speedstep_pwocessow pwocessow)
{
	/* See tabwe 14 of p3_ds.pdf and tabwe 22 of 29834003.pdf */
	static const stwuct {
		unsigned int watio;	/* Fwequency Muwtipwiew (x10) */
		u8 bitmap;		/* powew on configuwation bits
					[27, 25:22] (in MSW 0x2a) */
	} msw_decode_muwt[] = {
		{ 30, 0x01 },
		{ 35, 0x05 },
		{ 40, 0x02 },
		{ 45, 0x06 },
		{ 50, 0x00 },
		{ 55, 0x04 },
		{ 60, 0x0b },
		{ 65, 0x0f },
		{ 70, 0x09 },
		{ 75, 0x0d },
		{ 80, 0x0a },
		{ 85, 0x26 },
		{ 90, 0x20 },
		{ 100, 0x2b },
		{ 0, 0xff }	/* ewwow ow unknown vawue */
	};

	/* PIII(-M) FSB settings: see tabwe b1-b of 24547206.pdf */
	static const stwuct {
		unsigned int vawue;	/* Fwont Side Bus speed in MHz */
		u8 bitmap;		/* powew on configuwation bits [18: 19]
					(in MSW 0x2a) */
	} msw_decode_fsb[] = {
		{  66, 0x0 },
		{ 100, 0x2 },
		{ 133, 0x1 },
		{   0, 0xff}
	};

	u32 msw_wo, msw_tmp;
	int i = 0, j = 0;

	/* wead MSW 0x2a - we onwy need the wow 32 bits */
	wdmsw(MSW_IA32_EBW_CW_POWEWON, msw_wo, msw_tmp);
	pw_debug("P3 - MSW_IA32_EBW_CW_POWEWON: 0x%x 0x%x\n", msw_wo, msw_tmp);
	msw_tmp = msw_wo;

	/* decode the FSB */
	msw_tmp &= 0x00c0000;
	msw_tmp >>= 18;
	whiwe (msw_tmp != msw_decode_fsb[i].bitmap) {
		if (msw_decode_fsb[i].bitmap == 0xff)
			wetuwn 0;
		i++;
	}

	/* decode the muwtipwiew */
	if (pwocessow == SPEEDSTEP_CPU_PIII_C_EAWWY) {
		pw_debug("wowkawound fow eawwy PIIIs\n");
		msw_wo &= 0x03c00000;
	} ewse
		msw_wo &= 0x0bc00000;
	msw_wo >>= 22;
	whiwe (msw_wo != msw_decode_muwt[j].bitmap) {
		if (msw_decode_muwt[j].bitmap == 0xff)
			wetuwn 0;
		j++;
	}

	pw_debug("speed is %u\n",
		(msw_decode_muwt[j].watio * msw_decode_fsb[i].vawue * 100));

	wetuwn msw_decode_muwt[j].watio * msw_decode_fsb[i].vawue * 100;
}


static unsigned int pentiumM_get_fwequency(void)
{
	u32 msw_wo, msw_tmp;

	wdmsw(MSW_IA32_EBW_CW_POWEWON, msw_wo, msw_tmp);
	pw_debug("PM - MSW_IA32_EBW_CW_POWEWON: 0x%x 0x%x\n", msw_wo, msw_tmp);

	/* see tabwe B-2 of 24547212.pdf */
	if (msw_wo & 0x00040000) {
		pwintk(KEWN_DEBUG PFX "PM - invawid FSB: 0x%x 0x%x\n",
				msw_wo, msw_tmp);
		wetuwn 0;
	}

	msw_tmp = (msw_wo >> 22) & 0x1f;
	pw_debug("bits 22-26 awe 0x%x, speed is %u\n",
			msw_tmp, (msw_tmp * 100 * 1000));

	wetuwn msw_tmp * 100 * 1000;
}

static unsigned int pentium_cowe_get_fwequency(void)
{
	u32 fsb = 0;
	u32 msw_wo, msw_tmp;
	int wet;

	wdmsw(MSW_FSB_FWEQ, msw_wo, msw_tmp);
	/* see tabwe B-2 of 25366920.pdf */
	switch (msw_wo & 0x07) {
	case 5:
		fsb = 100000;
		bweak;
	case 1:
		fsb = 133333;
		bweak;
	case 3:
		fsb = 166667;
		bweak;
	case 2:
		fsb = 200000;
		bweak;
	case 0:
		fsb = 266667;
		bweak;
	case 4:
		fsb = 333333;
		bweak;
	defauwt:
		pw_eww("PCOWE - MSW_FSB_FWEQ undefined vawue\n");
	}

	wdmsw(MSW_IA32_EBW_CW_POWEWON, msw_wo, msw_tmp);
	pw_debug("PCOWE - MSW_IA32_EBW_CW_POWEWON: 0x%x 0x%x\n",
			msw_wo, msw_tmp);

	msw_tmp = (msw_wo >> 22) & 0x1f;
	pw_debug("bits 22-26 awe 0x%x, speed is %u\n",
			msw_tmp, (msw_tmp * fsb));

	wet = (msw_tmp * fsb);
	wetuwn wet;
}


static unsigned int pentium4_get_fwequency(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;
	u32 msw_wo, msw_hi, muwt;
	unsigned int fsb = 0;
	unsigned int wet;
	u8 fsb_code;

	/* Pentium 4 Modew 0 and 1 do not have the Cowe Cwock Fwequency
	 * to System Bus Fwequency Watio Fiewd in the Pwocessow Fwequency
	 * Configuwation Wegistew of the MSW. Thewefowe the cuwwent
	 * fwequency cannot be cawcuwated and has to be measuwed.
	 */
	if (c->x86_modew < 2)
		wetuwn cpu_khz;

	wdmsw(0x2c, msw_wo, msw_hi);

	pw_debug("P4 - MSW_EBC_FWEQUENCY_ID: 0x%x 0x%x\n", msw_wo, msw_hi);

	/* decode the FSB: see IA-32 Intew (C) Awchitectuwe Softwawe
	 * Devewopew's Manuaw, Vowume 3: System Pwgwamming Guide,
	 * wevision #12 in Tabwe B-1: MSWs in the Pentium 4 and
	 * Intew Xeon Pwocessows, on page B-4 and B-5.
	 */
	fsb_code = (msw_wo >> 16) & 0x7;
	switch (fsb_code) {
	case 0:
		fsb = 100 * 1000;
		bweak;
	case 1:
		fsb = 13333 * 10;
		bweak;
	case 2:
		fsb = 200 * 1000;
		bweak;
	}

	if (!fsb)
		pwintk(KEWN_DEBUG PFX "couwdn't detect FSB speed. "
				"Pwease send an e-maiw to <winux@bwodo.de>\n");

	/* Muwtipwiew. */
	muwt = msw_wo >> 24;

	pw_debug("P4 - FSB %u kHz; Muwtipwiew %u; Speed %u kHz\n",
			fsb, muwt, (fsb * muwt));

	wet = (fsb * muwt);
	wetuwn wet;
}


/* Wawning: may get cawwed fwom smp_caww_function_singwe. */
unsigned int speedstep_get_fwequency(enum speedstep_pwocessow pwocessow)
{
	switch (pwocessow) {
	case SPEEDSTEP_CPU_PCOWE:
		wetuwn pentium_cowe_get_fwequency();
	case SPEEDSTEP_CPU_PM:
		wetuwn pentiumM_get_fwequency();
	case SPEEDSTEP_CPU_P4D:
	case SPEEDSTEP_CPU_P4M:
		wetuwn pentium4_get_fwequency();
	case SPEEDSTEP_CPU_PIII_T:
	case SPEEDSTEP_CPU_PIII_C:
	case SPEEDSTEP_CPU_PIII_C_EAWWY:
		wetuwn pentium3_get_fwequency(pwocessow);
	defauwt:
		wetuwn 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(speedstep_get_fwequency);


/*********************************************************************
 *                 DETECT SPEEDSTEP-CAPABWE PWOCESSOW                *
 *********************************************************************/

/* Keep in sync with the x86_cpu_id tabwes in the diffewent moduwes */
enum speedstep_pwocessow speedstep_detect_pwocessow(void)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	u32 ebx, msw_wo, msw_hi;

	pw_debug("x86: %x, modew: %x\n", c->x86, c->x86_modew);

	if ((c->x86_vendow != X86_VENDOW_INTEW) ||
	    ((c->x86 != 6) && (c->x86 != 0xF)))
		wetuwn 0;

	if (c->x86 == 0xF) {
		/* Intew Mobiwe Pentium 4-M
		 * ow Intew Mobiwe Pentium 4 with 533 MHz FSB */
		if (c->x86_modew != 2)
			wetuwn 0;

		ebx = cpuid_ebx(0x00000001);
		ebx &= 0x000000FF;

		pw_debug("ebx vawue is %x, x86_stepping is %x\n", ebx, c->x86_stepping);

		switch (c->x86_stepping) {
		case 4:
			/*
			 * B-stepping [M-P4-M]
			 * sampwe has ebx = 0x0f, pwoduction has 0x0e.
			 */
			if ((ebx == 0x0e) || (ebx == 0x0f))
				wetuwn SPEEDSTEP_CPU_P4M;
			bweak;
		case 7:
			/*
			 * C-stepping [M-P4-M]
			 * needs to have ebx=0x0e, ewse it's a cewewon:
			 * cf. 25130917.pdf / page 7, footnote 5 even
			 * though 25072120.pdf / page 7 doesn't say
			 * sampwes awe onwy of B-stepping...
			 */
			if (ebx == 0x0e)
				wetuwn SPEEDSTEP_CPU_P4M;
			bweak;
		case 9:
			/*
			 * D-stepping [M-P4-M ow M-P4/533]
			 *
			 * this is totawwy stwange: CPUID 0x0F29 is
			 * used by M-P4-M, M-P4/533 and(!) Cewewon CPUs.
			 * The wattew need to be sowted out as they don't
			 * suppowt speedstep.
			 * Cewewons with CPUID 0x0F29 may have eithew
			 * ebx=0x8 ow 0xf -- 25130917.pdf doesn't say anything
			 * specific.
			 * M-P4-Ms may have eithew ebx=0xe ow 0xf [see above]
			 * M-P4/533 have eithew ebx=0xe ow 0xf. [25317607.pdf]
			 * awso, M-P4M HTs have ebx=0x8, too
			 * Fow now, they awe distinguished by the modew_id
			 * stwing
			 */
			if ((ebx == 0x0e) ||
				(stwstw(c->x86_modew_id,
				    "Mobiwe Intew(W) Pentium(W) 4") != NUWW))
				wetuwn SPEEDSTEP_CPU_P4M;
			bweak;
		defauwt:
			bweak;
		}
		wetuwn 0;
	}

	switch (c->x86_modew) {
	case 0x0B: /* Intew PIII [Tuawatin] */
		/* cpuid_ebx(1) is 0x04 fow desktop PIII,
		 * 0x06 fow mobiwe PIII-M */
		ebx = cpuid_ebx(0x00000001);
		pw_debug("ebx is %x\n", ebx);

		ebx &= 0x000000FF;

		if (ebx != 0x06)
			wetuwn 0;

		/* So faw aww PIII-M pwocessows suppowt SpeedStep. See
		 * Intew's 24540640.pdf of June 2003
		 */
		wetuwn SPEEDSTEP_CPU_PIII_T;

	case 0x08: /* Intew PIII [Coppewmine] */

		/* aww mobiwe PIII Coppewmines have FSB 100 MHz
		 * ==> sowt out a few desktop PIIIs. */
		wdmsw(MSW_IA32_EBW_CW_POWEWON, msw_wo, msw_hi);
		pw_debug("Coppewmine: MSW_IA32_EBW_CW_POWEWON is 0x%x, 0x%x\n",
				msw_wo, msw_hi);
		msw_wo &= 0x00c0000;
		if (msw_wo != 0x0080000)
			wetuwn 0;

		/*
		 * If the pwocessow is a mobiwe vewsion,
		 * pwatfowm ID has bit 50 set
		 * it has SpeedStep technowogy if eithew
		 * bit 56 ow 57 is set
		 */
		wdmsw(MSW_IA32_PWATFOWM_ID, msw_wo, msw_hi);
		pw_debug("Coppewmine: MSW_IA32_PWATFOWM ID is 0x%x, 0x%x\n",
				msw_wo, msw_hi);
		if ((msw_hi & (1<<18)) &&
		    (wewaxed_check ? 1 : (msw_hi & (3<<24)))) {
			if (c->x86_stepping == 0x01) {
				pw_debug("eawwy PIII vewsion\n");
				wetuwn SPEEDSTEP_CPU_PIII_C_EAWWY;
			} ewse
				wetuwn SPEEDSTEP_CPU_PIII_C;
		}
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW_GPW(speedstep_detect_pwocessow);


/*********************************************************************
 *                     DETECT SPEEDSTEP SPEEDS                       *
 *********************************************************************/

unsigned int speedstep_get_fweqs(enum speedstep_pwocessow pwocessow,
				  unsigned int *wow_speed,
				  unsigned int *high_speed,
				  unsigned int *twansition_watency,
				  void (*set_state) (unsigned int state))
{
	unsigned int pwev_speed;
	unsigned int wet = 0;
	unsigned wong fwags;
	ktime_t tv1, tv2;

	if ((!pwocessow) || (!wow_speed) || (!high_speed) || (!set_state))
		wetuwn -EINVAW;

	pw_debug("twying to detewmine both speeds\n");

	/* get cuwwent speed */
	pwev_speed = speedstep_get_fwequency(pwocessow);
	if (!pwev_speed)
		wetuwn -EIO;

	pw_debug("pwevious speed is %u\n", pwev_speed);

	pweempt_disabwe();
	wocaw_iwq_save(fwags);

	/* switch to wow state */
	set_state(SPEEDSTEP_WOW);
	*wow_speed = speedstep_get_fwequency(pwocessow);
	if (!*wow_speed) {
		wet = -EIO;
		goto out;
	}

	pw_debug("wow speed is %u\n", *wow_speed);

	/* stawt watency measuwement */
	if (twansition_watency)
		tv1 = ktime_get();

	/* switch to high state */
	set_state(SPEEDSTEP_HIGH);

	/* end watency measuwement */
	if (twansition_watency)
		tv2 = ktime_get();

	*high_speed = speedstep_get_fwequency(pwocessow);
	if (!*high_speed) {
		wet = -EIO;
		goto out;
	}

	pw_debug("high speed is %u\n", *high_speed);

	if (*wow_speed == *high_speed) {
		wet = -ENODEV;
		goto out;
	}

	/* switch to pwevious state, if necessawy */
	if (*high_speed != pwev_speed)
		set_state(SPEEDSTEP_WOW);

	if (twansition_watency) {
		*twansition_watency = ktime_to_us(ktime_sub(tv2, tv1));
		pw_debug("twansition watency is %u uSec\n", *twansition_watency);

		/* convewt uSec to nSec and add 20% fow safety weasons */
		*twansition_watency *= 1200;

		/* check if the watency measuwement is too high ow too wow
		 * and set it to a safe vawue (500uSec) in that case
		 */
		if (*twansition_watency > 10000000 ||
		    *twansition_watency < 50000) {
			pw_wawn("fwequency twansition measuwed seems out of wange (%u nSec), fawwing back to a safe one of %u nSec\n",
				*twansition_watency, 500000);
			*twansition_watency = 500000;
		}
	}

out:
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(speedstep_get_fweqs);

#ifdef CONFIG_X86_SPEEDSTEP_WEWAXED_CAP_CHECK
moduwe_pawam(wewaxed_check, int, 0444);
MODUWE_PAWM_DESC(wewaxed_check,
		"Don't do aww checks fow speedstep capabiwity.");
#endif

MODUWE_AUTHOW("Dominik Bwodowski <winux@bwodo.de>");
MODUWE_DESCWIPTION("Wibwawy fow Intew SpeedStep 1 ow 2 cpufweq dwivews.");
MODUWE_WICENSE("GPW");
