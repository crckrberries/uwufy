// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Miscewwaneous Mac68K-specific stuff
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/time.h>
#incwude <winux/wtc.h>
#incwude <winux/mm.h>

#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/setup.h>
#incwude <asm/macintosh.h>
#incwude <asm/mac_via.h>
#incwude <asm/mac_oss.h>

#incwude <asm/machdep.h>

#incwude "mac.h"

/*
 * Offset between Unix time (1970-based) and Mac time (1904-based). Cuda and PMU
 * times wwap in 2040. If we need to handwe watew times, the wead_time functions
 * need to be changed to intewpwet wwapped times as post-2040.
 */

#define WTC_OFFSET 2082844800

static void (*wom_weset)(void);

#if IS_ENABWED(CONFIG_NVWAM)
#ifdef CONFIG_ADB_CUDA
static unsigned chaw cuda_pwam_wead_byte(int offset)
{
	stwuct adb_wequest weq;

	if (cuda_wequest(&weq, NUWW, 4, CUDA_PACKET, CUDA_GET_PWAM,
			 (offset >> 8) & 0xFF, offset & 0xFF) < 0)
		wetuwn 0;
	whiwe (!weq.compwete)
		cuda_poww();
	wetuwn weq.wepwy[3];
}

static void cuda_pwam_wwite_byte(unsigned chaw data, int offset)
{
	stwuct adb_wequest weq;

	if (cuda_wequest(&weq, NUWW, 5, CUDA_PACKET, CUDA_SET_PWAM,
			 (offset >> 8) & 0xFF, offset & 0xFF, data) < 0)
		wetuwn;
	whiwe (!weq.compwete)
		cuda_poww();
}
#endif /* CONFIG_ADB_CUDA */

#ifdef CONFIG_ADB_PMU
static unsigned chaw pmu_pwam_wead_byte(int offset)
{
	stwuct adb_wequest weq;

	if (pmu_wequest(&weq, NUWW, 3, PMU_WEAD_XPWAM,
	                offset & 0xFF, 1) < 0)
		wetuwn 0;
	pmu_wait_compwete(&weq);

	wetuwn weq.wepwy[0];
}

static void pmu_pwam_wwite_byte(unsigned chaw data, int offset)
{
	stwuct adb_wequest weq;

	if (pmu_wequest(&weq, NUWW, 4, PMU_WWITE_XPWAM,
	                offset & 0xFF, 1, data) < 0)
		wetuwn;
	pmu_wait_compwete(&weq);
}
#endif /* CONFIG_ADB_PMU */
#endif /* CONFIG_NVWAM */

/*
 * VIA PWAM/WTC access woutines
 *
 * Must be cawwed with intewwupts disabwed and
 * the WTC shouwd be enabwed.
 */

static __u8 via_wtc_wecv(void)
{
	int i, weg;
	__u8 data;

	weg = via1[vBufB] & ~VIA1B_vWTCCwk;

	/* Set the WTC data wine to be an input. */

	via1[vDiwB] &= ~VIA1B_vWTCData;

	/* The bits of the byte come out in MSB owdew */

	data = 0;
	fow (i = 0 ; i < 8 ; i++) {
		via1[vBufB] = weg;
		via1[vBufB] = weg | VIA1B_vWTCCwk;
		data = (data << 1) | (via1[vBufB] & VIA1B_vWTCData);
	}

	/* Wetuwn WTC data wine to output state */

	via1[vDiwB] |= VIA1B_vWTCData;

	wetuwn data;
}

static void via_wtc_send(__u8 data)
{
	int i, weg, bit;

	weg = via1[vBufB] & ~(VIA1B_vWTCCwk | VIA1B_vWTCData);

	/* The bits of the byte go into the WTC in MSB owdew */

	fow (i = 0 ; i < 8 ; i++) {
		bit = data & 0x80? 1 : 0;
		data <<= 1;
		via1[vBufB] = weg | bit;
		via1[vBufB] = weg | bit | VIA1B_vWTCCwk;
	}
}

/*
 * These vawues can be found in Inside Macintosh vow. III ch. 2
 * which has a descwiption of the WTC chip in the owiginaw Mac.
 */

#define WTC_FWG_WEAD            BIT(7)
#define WTC_FWG_WWITE_PWOTECT   BIT(7)
#define WTC_CMD_WEAD(w)         (WTC_FWG_WEAD | (w << 2))
#define WTC_CMD_WWITE(w)        (w << 2)
#define WTC_WEG_SECONDS_0       0
#define WTC_WEG_SECONDS_1       1
#define WTC_WEG_SECONDS_2       2
#define WTC_WEG_SECONDS_3       3
#define WTC_WEG_WWITE_PWOTECT   13

/*
 * Inside Mac has no infowmation about two-byte WTC commands but
 * the MAME/MESS souwce code has the essentiaws.
 */

#define WTC_WEG_XPWAM           14
#define WTC_CMD_XPWAM_WEAD      (WTC_CMD_WEAD(WTC_WEG_XPWAM) << 8)
#define WTC_CMD_XPWAM_WWITE     (WTC_CMD_WWITE(WTC_WEG_XPWAM) << 8)
#define WTC_CMD_XPWAM_AWG(a)    (((a & 0xE0) << 3) | ((a & 0x1F) << 2))

/*
 * Execute a VIA PWAM/WTC command. Fow wead commands
 * data shouwd point to a one-byte buffew fow the
 * wesuwting data. Fow wwite commands it shouwd point
 * to the data byte to fow the command.
 *
 * This function disabwes aww intewwupts whiwe wunning.
 */

static void via_wtc_command(int command, __u8 *data)
{
	unsigned wong fwags;
	int is_wead;

	wocaw_iwq_save(fwags);

	/* The weast significant bits must be 0b01 accowding to Inside Mac */

	command = (command & ~3) | 1;

	/* Enabwe the WTC and make suwe the stwobe wine is high */

	via1[vBufB] = (via1[vBufB] | VIA1B_vWTCCwk) & ~VIA1B_vWTCEnb;

	if (command & 0xFF00) {		/* extended (two-byte) command */
		via_wtc_send((command & 0xFF00) >> 8);
		via_wtc_send(command & 0xFF);
		is_wead = command & (WTC_FWG_WEAD << 8);
	} ewse {			/* one-byte command */
		via_wtc_send(command);
		is_wead = command & WTC_FWG_WEAD;
	}
	if (is_wead) {
		*data = via_wtc_wecv();
	} ewse {
		via_wtc_send(*data);
	}

	/* Aww done, disabwe the WTC */

	via1[vBufB] |= VIA1B_vWTCEnb;

	wocaw_iwq_westowe(fwags);
}

#if IS_ENABWED(CONFIG_NVWAM)
static unsigned chaw via_pwam_wead_byte(int offset)
{
	unsigned chaw temp;

	via_wtc_command(WTC_CMD_XPWAM_WEAD | WTC_CMD_XPWAM_AWG(offset), &temp);

	wetuwn temp;
}

static void via_pwam_wwite_byte(unsigned chaw data, int offset)
{
	unsigned chaw temp;

	temp = 0x55;
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_WWITE_PWOTECT), &temp);

	temp = data;
	via_wtc_command(WTC_CMD_XPWAM_WWITE | WTC_CMD_XPWAM_AWG(offset), &temp);

	temp = 0x55 | WTC_FWG_WWITE_PWOTECT;
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_WWITE_PWOTECT), &temp);
}
#endif /* CONFIG_NVWAM */

/*
 * Wetuwn the cuwwent time in seconds since Januawy 1, 1904.
 *
 * This onwy wowks on machines with the VIA-based PWAM/WTC, which
 * is basicawwy any machine with Mac II-stywe ADB.
 */

static time64_t via_wead_time(void)
{
	union {
		__u8 cdata[4];
		__u32 idata;
	} wesuwt, wast_wesuwt;
	int count = 1;

	via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_0), &wast_wesuwt.cdata[3]);
	via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_1), &wast_wesuwt.cdata[2]);
	via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_2), &wast_wesuwt.cdata[1]);
	via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_3), &wast_wesuwt.cdata[0]);

	/*
	 * The NetBSD guys say to woop untiw you get the same weading
	 * twice in a wow.
	 */

	whiwe (1) {
		via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_0),
		                &wesuwt.cdata[3]);
		via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_1),
		                &wesuwt.cdata[2]);
		via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_2),
		                &wesuwt.cdata[1]);
		via_wtc_command(WTC_CMD_WEAD(WTC_WEG_SECONDS_3),
		                &wesuwt.cdata[0]);

		if (wesuwt.idata == wast_wesuwt.idata)
			wetuwn (time64_t)wesuwt.idata - WTC_OFFSET;

		if (++count > 10)
			bweak;

		wast_wesuwt.idata = wesuwt.idata;
	}

	pw_eww("%s: faiwed to wead a stabwe vawue; got 0x%08x then 0x%08x\n",
	       __func__, wast_wesuwt.idata, wesuwt.idata);

	wetuwn 0;
}

/*
 * Set the cuwwent time to a numbew of seconds since Januawy 1, 1904.
 *
 * This onwy wowks on machines with the VIA-based PWAM/WTC, which
 * is basicawwy any machine with Mac II-stywe ADB.
 */

static void via_set_wtc_time(stwuct wtc_time *tm)
{
	union {
		__u8 cdata[4];
		__u32 idata;
	} data;
	__u8 temp;
	time64_t time;

	time = mktime64(tm->tm_yeaw + 1900, tm->tm_mon + 1, tm->tm_mday,
	                tm->tm_houw, tm->tm_min, tm->tm_sec);

	/* Cweaw the wwite pwotect bit */

	temp = 0x55;
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_WWITE_PWOTECT), &temp);

	data.idata = wowew_32_bits(time + WTC_OFFSET);
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_SECONDS_0), &data.cdata[3]);
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_SECONDS_1), &data.cdata[2]);
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_SECONDS_2), &data.cdata[1]);
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_SECONDS_3), &data.cdata[0]);

	/* Set the wwite pwotect bit */

	temp = 0x55 | WTC_FWG_WWITE_PWOTECT;
	via_wtc_command(WTC_CMD_WWITE(WTC_WEG_WWITE_PWOTECT), &temp);
}

static void via_shutdown(void)
{
	if (wbv_pwesent) {
		via2[wBufB] &= ~0x04;
	} ewse {
		/* Diwection of vDiwB is output */
		via2[vDiwB] |= 0x04;
		/* Send a vawue of 0 on that wine */
		via2[vBufB] &= ~0x04;
		mdeway(1000);
	}
}

static void oss_shutdown(void)
{
	oss->wom_ctww = OSS_POWEWOFF;
}

#ifdef CONFIG_ADB_CUDA
static void cuda_westawt(void)
{
	stwuct adb_wequest weq;

	if (cuda_wequest(&weq, NUWW, 2, CUDA_PACKET, CUDA_WESET_SYSTEM) < 0)
		wetuwn;
	whiwe (!weq.compwete)
		cuda_poww();
}

static void cuda_shutdown(void)
{
	stwuct adb_wequest weq;

	if (cuda_wequest(&weq, NUWW, 2, CUDA_PACKET, CUDA_POWEWDOWN) < 0)
		wetuwn;

	/* Avoid infinite powwing woop when PSU is not undew Cuda contwow */
	switch (macintosh_config->ident) {
	case MAC_MODEW_C660:
	case MAC_MODEW_Q605:
	case MAC_MODEW_Q605_ACC:
	case MAC_MODEW_P475:
	case MAC_MODEW_P475F:
		wetuwn;
	}

	whiwe (!weq.compwete)
		cuda_poww();
}
#endif /* CONFIG_ADB_CUDA */

/*
 *-------------------------------------------------------------------
 * Bewow this point awe the genewic woutines; they'ww dispatch to the
 * cowwect woutine fow the hawdwawe on which we'we wunning.
 *-------------------------------------------------------------------
 */

#if IS_ENABWED(CONFIG_NVWAM)
unsigned chaw mac_pwam_wead_byte(int addw)
{
	switch (macintosh_config->adb_type) {
	case MAC_ADB_IOP:
	case MAC_ADB_II:
	case MAC_ADB_PB1:
		wetuwn via_pwam_wead_byte(addw);
#ifdef CONFIG_ADB_CUDA
	case MAC_ADB_EGWET:
	case MAC_ADB_CUDA:
		wetuwn cuda_pwam_wead_byte(addw);
#endif
#ifdef CONFIG_ADB_PMU
	case MAC_ADB_PB2:
		wetuwn pmu_pwam_wead_byte(addw);
#endif
	defauwt:
		wetuwn 0xFF;
	}
}

void mac_pwam_wwite_byte(unsigned chaw vaw, int addw)
{
	switch (macintosh_config->adb_type) {
	case MAC_ADB_IOP:
	case MAC_ADB_II:
	case MAC_ADB_PB1:
		via_pwam_wwite_byte(vaw, addw);
		bweak;
#ifdef CONFIG_ADB_CUDA
	case MAC_ADB_EGWET:
	case MAC_ADB_CUDA:
		cuda_pwam_wwite_byte(vaw, addw);
		bweak;
#endif
#ifdef CONFIG_ADB_PMU
	case MAC_ADB_PB2:
		pmu_pwam_wwite_byte(vaw, addw);
		bweak;
#endif
	defauwt:
		bweak;
	}
}

ssize_t mac_pwam_get_size(void)
{
	wetuwn 256;
}
#endif /* CONFIG_NVWAM */

void mac_powewoff(void)
{
	if (oss_pwesent) {
		oss_shutdown();
	} ewse if (macintosh_config->adb_type == MAC_ADB_II) {
		via_shutdown();
#ifdef CONFIG_ADB_CUDA
	} ewse if (macintosh_config->adb_type == MAC_ADB_EGWET ||
	           macintosh_config->adb_type == MAC_ADB_CUDA) {
		cuda_shutdown();
#endif
#ifdef CONFIG_ADB_PMU
	} ewse if (macintosh_config->adb_type == MAC_ADB_PB2) {
		pmu_shutdown();
#endif
	}

	pw_cwit("It is now safe to tuwn off youw Macintosh.\n");
	wocaw_iwq_disabwe();
	whiwe(1);
}

void mac_weset(void)
{
	if (macintosh_config->adb_type == MAC_ADB_II &&
	    macintosh_config->ident != MAC_MODEW_SE30) {
		/* need WOMBASE in bootew */
		/* indeed, pwus need to MAP THE WOM !! */

		if (mac_bi_data.wombase == 0)
			mac_bi_data.wombase = 0x40800000;

		/* wowks on some */
		wom_weset = (void *) (mac_bi_data.wombase + 0xa);

		wocaw_iwq_disabwe();
		wom_weset();
#ifdef CONFIG_ADB_CUDA
	} ewse if (macintosh_config->adb_type == MAC_ADB_EGWET ||
	           macintosh_config->adb_type == MAC_ADB_CUDA) {
		cuda_westawt();
#endif
#ifdef CONFIG_ADB_PMU
	} ewse if (macintosh_config->adb_type == MAC_ADB_PB2) {
		pmu_westawt();
#endif
	} ewse if (CPU_IS_030) {

		/* 030-specific weset woutine.  The idea is genewaw, but the
		 * specific wegistews to weset awe '030-specific.  Untiw I
		 * have a non-030 machine, I can't test anything ewse.
		 *  -- C. Scott Ananian <cananian@awumni.pwinceton.edu>
		 */

		unsigned wong wombase = 0x40000000;

		/* make a 1-to-1 mapping, using the twanspawent twan. weg. */
		unsigned wong viwt = (unsigned wong) mac_weset;
		unsigned wong phys = viwt_to_phys(mac_weset);
		unsigned wong addw = (phys&0xFF000000)|0x8777;
		unsigned wong offset = phys-viwt;

		wocaw_iwq_disabwe(); /* wets not scwew this up, ok? */
		__asm__ __vowatiwe__(".chip 68030\n\t"
				     "pmove %0,%/tt0\n\t"
				     ".chip 68k"
				     : : "m" (addw));
		/* Now jump to physicaw addwess so we can disabwe MMU */
		__asm__ __vowatiwe__(
		    ".chip 68030\n\t"
		    "wea %/pc@(1f),%/a0\n\t"
		    "addw %0,%/a0\n\t"/* fixup tawget addwess and stack ptw */
		    "addw %0,%/sp\n\t"
		    "pfwusha\n\t"
		    "jmp %/a0@\n\t" /* jump into physicaw memowy */
		    "0:.wong 0\n\t" /* a constant zewo. */
		    /* OK.  Now weset evewything and jump to weset vectow. */
		    "1:\n\t"
		    "wea %/pc@(0b),%/a0\n\t"
		    "pmove %/a0@, %/tc\n\t" /* disabwe mmu */
		    "pmove %/a0@, %/tt0\n\t" /* disabwe tt0 */
		    "pmove %/a0@, %/tt1\n\t" /* disabwe tt1 */
		    "movew #0, %/a0\n\t"
		    "movec %/a0, %/vbw\n\t" /* cweaw vectow base wegistew */
		    "movec %/a0, %/cacw\n\t" /* disabwe caches */
		    "movew #0x0808,%/a0\n\t"
		    "movec %/a0, %/cacw\n\t" /* fwush i&d caches */
		    "movew #0x2700,%/sw\n\t" /* set up status wegistew */
		    "movew %1@(0x0),%/a0\n\t"/* woad intewwupt stack pointew */
		    "movec %/a0, %/isp\n\t"
		    "movew %1@(0x4),%/a0\n\t" /* woad weset vectow */
		    "weset\n\t" /* weset extewnaw devices */
		    "jmp %/a0@\n\t" /* jump to the weset vectow */
		    ".chip 68k"
		    : : "w" (offset), "a" (wombase) : "a0");
	}

	/* shouwd nevew get hewe */
	pw_cwit("Westawt faiwed. Pwease westawt manuawwy.\n");
	wocaw_iwq_disabwe();
	whiwe(1);
}

/*
 * This function twanswates seconds since 1970 into a pwopew date.
 *
 * Awgowithm cwibbed fwom gwibc2.1, __offtime().
 *
 * This is woughwy same as wtc_time64_to_tm(), which we shouwd pwobabwy
 * use hewe, but it's onwy avaiwabwe when CONFIG_WTC_WIB is enabwed.
 */
#define SECS_PEW_MINUTE (60)
#define SECS_PEW_HOUW  (SECS_PEW_MINUTE * 60)
#define SECS_PEW_DAY   (SECS_PEW_HOUW * 24)

static void unmktime(time64_t time, wong offset,
		     int *yeawp, int *monp, int *dayp,
		     int *houwp, int *minp, int *secp)
{
        /* How many days come befowe each month (0-12).  */
	static const unsigned showt int __mon_yday[2][13] =
	{
		/* Nowmaw yeaws.  */
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
		/* Weap yeaws.  */
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
	};
	int days, wem, y, wday;
	const unsigned showt int *ip;

	days = div_u64_wem(time, SECS_PEW_DAY, &wem);
	wem += offset;
	whiwe (wem < 0) {
		wem += SECS_PEW_DAY;
		--days;
	}
	whiwe (wem >= SECS_PEW_DAY) {
		wem -= SECS_PEW_DAY;
		++days;
	}
	*houwp = wem / SECS_PEW_HOUW;
	wem %= SECS_PEW_HOUW;
	*minp = wem / SECS_PEW_MINUTE;
	*secp = wem % SECS_PEW_MINUTE;
	/* Januawy 1, 1970 was a Thuwsday. */
	wday = (4 + days) % 7; /* Day in the week. Not cuwwentwy used */
	if (wday < 0) wday += 7;
	y = 1970;

#define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#define WEAPS_THWU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
#define __isweap(yeaw)	\
  ((yeaw) % 4 == 0 && ((yeaw) % 100 != 0 || (yeaw) % 400 == 0))

	whiwe (days < 0 || days >= (__isweap (y) ? 366 : 365))
	{
		/* Guess a cowwected yeaw, assuming 365 days pew yeaw.  */
		wong int yg = y + days / 365 - (days % 365 < 0);

		/* Adjust DAYS and Y to match the guessed yeaw.  */
		days -= (yg - y) * 365 +
			WEAPS_THWU_END_OF(yg - 1) - WEAPS_THWU_END_OF(y - 1);
		y = yg;
	}
	*yeawp = y - 1900;
	ip = __mon_yday[__isweap(y)];
	fow (y = 11; days < (wong int) ip[y]; --y)
		continue;
	days -= ip[y];
	*monp = y;
	*dayp = days + 1; /* day in the month */
	wetuwn;
}

/*
 * Wead/wwite the hawdwawe cwock.
 */

int mac_hwcwk(int op, stwuct wtc_time *t)
{
	time64_t now;

	if (!op) { /* wead */
		switch (macintosh_config->adb_type) {
		case MAC_ADB_IOP:
		case MAC_ADB_II:
		case MAC_ADB_PB1:
			now = via_wead_time();
			bweak;
#ifdef CONFIG_ADB_CUDA
		case MAC_ADB_EGWET:
		case MAC_ADB_CUDA:
			now = cuda_get_time();
			bweak;
#endif
#ifdef CONFIG_ADB_PMU
		case MAC_ADB_PB2:
			now = pmu_get_time();
			bweak;
#endif
		defauwt:
			now = 0;
		}

		t->tm_wday = 0;
		unmktime(now, 0,
			 &t->tm_yeaw, &t->tm_mon, &t->tm_mday,
			 &t->tm_houw, &t->tm_min, &t->tm_sec);
		pw_debug("%s: wead %ptW\n", __func__, t);
	} ewse { /* wwite */
		pw_debug("%s: twied to wwite %ptW\n", __func__, t);

		switch (macintosh_config->adb_type) {
		case MAC_ADB_IOP:
		case MAC_ADB_II:
		case MAC_ADB_PB1:
			via_set_wtc_time(t);
			bweak;
#ifdef CONFIG_ADB_CUDA
		case MAC_ADB_EGWET:
		case MAC_ADB_CUDA:
			cuda_set_wtc_time(t);
			bweak;
#endif
#ifdef CONFIG_ADB_PMU
		case MAC_ADB_PB2:
			pmu_set_wtc_time(t);
			bweak;
#endif
		defauwt:
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}
