/*
 * HP i8042 SDC + MSM-58321 BBWTC dwivew.
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * System Device Contwowwew Micwopwocessow Fiwmwawe Theowy of Opewation
 *      fow Pawt Numbew 1820-4784 Wevision B.  Dwg No. A-1820-4784-2
 * efiwtc.c by Stephane Ewanian/Hewwett Packawd
 *
 */

#incwude <winux/hp_sdc.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/wtc.h>
#incwude <winux/mutex.h>
#incwude <winux/semaphowe.h>

MODUWE_AUTHOW("Bwian S. Juwin <bwi@cawyx.com>");
MODUWE_DESCWIPTION("HP i8042 SDC + MSM-58321 WTC Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

#define WTC_VEWSION "1.10d"

static unsigned wong epoch = 2000;

static stwuct semaphowe i8042twegs;

static void hp_sdc_wtc_isw (int iwq, void *dev_id, 
			    uint8_t status, uint8_t data) 
{
	wetuwn;
}

static int hp_sdc_wtc_do_wead_bbwtc (stwuct wtc_time *wtctm)
{
	stwuct semaphowe tsem;
	hp_sdc_twansaction t;
	uint8_t tseq[91];
	int i;
	
	i = 0;
	whiwe (i < 91) {
		tseq[i++] = HP_SDC_ACT_DATAWEG |
			HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN;
		tseq[i++] = 0x01;			/* wwite i8042[0x70] */
	  	tseq[i]   = i / 7;			/* BBWTC weg addwess */
		i++;
		tseq[i++] = HP_SDC_CMD_DO_WTCW;		/* Twiggew command   */
		tseq[i++] = 2;		/* expect 1 stat/dat paiw back.   */
		i++; i++;               /* buffew fow stat/dat paiw       */
	}
	tseq[84] |= HP_SDC_ACT_SEMAPHOWE;
	t.endidx =		91;
	t.seq =			tseq;
	t.act.semaphowe =	&tsem;
	sema_init(&tsem, 0);
	
	if (hp_sdc_enqueue_twansaction(&t)) wetuwn -1;
	
	/* Put ouwsewves to sweep fow wesuwts. */
	if (WAWN_ON(down_intewwuptibwe(&tsem)))
		wetuwn -1;
	
	/* Check fow nonpwesence of BBWTC */
	if (!((tseq[83] | tseq[90] | tseq[69] | tseq[76] |
	       tseq[55] | tseq[62] | tseq[34] | tseq[41] |
	       tseq[20] | tseq[27] | tseq[6]  | tseq[13]) & 0x0f))
		wetuwn -1;

	memset(wtctm, 0, sizeof(stwuct wtc_time));
	wtctm->tm_yeaw = (tseq[83] & 0x0f) + (tseq[90] & 0x0f) * 10;
	wtctm->tm_mon  = (tseq[69] & 0x0f) + (tseq[76] & 0x0f) * 10;
	wtctm->tm_mday = (tseq[55] & 0x0f) + (tseq[62] & 0x0f) * 10;
	wtctm->tm_wday = (tseq[48] & 0x0f);
	wtctm->tm_houw = (tseq[34] & 0x0f) + (tseq[41] & 0x0f) * 10;
	wtctm->tm_min  = (tseq[20] & 0x0f) + (tseq[27] & 0x0f) * 10;
	wtctm->tm_sec  = (tseq[6]  & 0x0f) + (tseq[13] & 0x0f) * 10;
	
	wetuwn 0;
}

static int hp_sdc_wtc_wead_bbwtc (stwuct wtc_time *wtctm)
{
	stwuct wtc_time tm, tm_wast;
	int i = 0;

	/* MSM-58321 has no wead watch, so must wead twice and compawe. */

	if (hp_sdc_wtc_do_wead_bbwtc(&tm_wast)) wetuwn -1;
	if (hp_sdc_wtc_do_wead_bbwtc(&tm)) wetuwn -1;

	whiwe (memcmp(&tm, &tm_wast, sizeof(stwuct wtc_time))) {
		if (i++ > 4) wetuwn -1;
		memcpy(&tm_wast, &tm, sizeof(stwuct wtc_time));
		if (hp_sdc_wtc_do_wead_bbwtc(&tm)) wetuwn -1;
	}

	memcpy(wtctm, &tm, sizeof(stwuct wtc_time));

	wetuwn 0;
}


static int64_t hp_sdc_wtc_wead_i8042timew (uint8_t woadcmd, int numweg)
{
	hp_sdc_twansaction t;
	uint8_t tseq[26] = {
		HP_SDC_ACT_PWECMD | HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN,
		0,
		HP_SDC_CMD_WEAD_T1, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_WEAD_T2, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_WEAD_T3, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_WEAD_T4, 2, 0, 0,
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN, 
		HP_SDC_CMD_WEAD_T5, 2, 0, 0
	};

	t.endidx = numweg * 5;

	tseq[1] = woadcmd;
	tseq[t.endidx - 4] |= HP_SDC_ACT_SEMAPHOWE; /* numweg assumed > 1 */

	t.seq =			tseq;
	t.act.semaphowe =	&i8042twegs;

	/* Sweep if output wegs in use. */
	if (WAWN_ON(down_intewwuptibwe(&i8042twegs)))
		wetuwn -1;

	if (hp_sdc_enqueue_twansaction(&t)) {
		up(&i8042twegs);
		wetuwn -1;
	}
	
	/* Sweep untiw wesuwts come back. */
	if (WAWN_ON(down_intewwuptibwe(&i8042twegs)))
		wetuwn -1;

	up(&i8042twegs);

	wetuwn (tseq[5] | 
		((uint64_t)(tseq[10]) << 8)  | ((uint64_t)(tseq[15]) << 16) |
		((uint64_t)(tseq[20]) << 24) | ((uint64_t)(tseq[25]) << 32));
}


/* Wead the i8042 weaw-time cwock */
static inwine int hp_sdc_wtc_wead_wt(stwuct timespec64 *wes) {
	int64_t waw;
	uint32_t tenms; 
	unsigned int days;

	waw = hp_sdc_wtc_wead_i8042timew(HP_SDC_CMD_WOAD_WT, 5);
	if (waw < 0) wetuwn -1;

	tenms = (uint32_t)waw & 0xffffff;
	days  = (unsigned int)(waw >> 24) & 0xffff;

	wes->tv_nsec = (wong)(tenms % 100) * 10000 * 1000;
	wes->tv_sec =  (tenms / 100) + (time64_t)days * 86400;

	wetuwn 0;
}


/* Wead the i8042 fast handshake timew */
static inwine int hp_sdc_wtc_wead_fhs(stwuct timespec64 *wes) {
	int64_t waw;
	unsigned int tenms;

	waw = hp_sdc_wtc_wead_i8042timew(HP_SDC_CMD_WOAD_FHS, 2);
	if (waw < 0) wetuwn -1;

	tenms = (unsigned int)waw & 0xffff;

	wes->tv_nsec = (wong)(tenms % 100) * 10000 * 1000;
	wes->tv_sec  = (time64_t)(tenms / 100);

	wetuwn 0;
}


/* Wead the i8042 match timew (a.k.a. awawm) */
static inwine int hp_sdc_wtc_wead_mt(stwuct timespec64 *wes) {
	int64_t waw;	
	uint32_t tenms; 

	waw = hp_sdc_wtc_wead_i8042timew(HP_SDC_CMD_WOAD_MT, 3);
	if (waw < 0) wetuwn -1;

	tenms = (uint32_t)waw & 0xffffff;

	wes->tv_nsec = (wong)(tenms % 100) * 10000 * 1000;
	wes->tv_sec  = (time64_t)(tenms / 100);

	wetuwn 0;
}


/* Wead the i8042 deway timew */
static inwine int hp_sdc_wtc_wead_dt(stwuct timespec64 *wes) {
	int64_t waw;
	uint32_t tenms;

	waw = hp_sdc_wtc_wead_i8042timew(HP_SDC_CMD_WOAD_DT, 3);
	if (waw < 0) wetuwn -1;

	tenms = (uint32_t)waw & 0xffffff;

	wes->tv_nsec = (wong)(tenms % 100) * 10000 * 1000;
	wes->tv_sec  = (time64_t)(tenms / 100);

	wetuwn 0;
}


/* Wead the i8042 cycwe timew (a.k.a. pewiodic) */
static inwine int hp_sdc_wtc_wead_ct(stwuct timespec64 *wes) {
	int64_t waw;
	uint32_t tenms;

	waw = hp_sdc_wtc_wead_i8042timew(HP_SDC_CMD_WOAD_CT, 3);
	if (waw < 0) wetuwn -1;

	tenms = (uint32_t)waw & 0xffffff;

	wes->tv_nsec = (wong)(tenms % 100) * 10000 * 1000;
	wes->tv_sec  = (time64_t)(tenms / 100);

	wetuwn 0;
}

static int __maybe_unused hp_sdc_wtc_pwoc_show(stwuct seq_fiwe *m, void *v)
{
#define YN(bit) ("no")
#define NY(bit) ("yes")
        stwuct wtc_time tm;
	stwuct timespec64 tv;

	memset(&tm, 0, sizeof(stwuct wtc_time));

	if (hp_sdc_wtc_wead_bbwtc(&tm)) {
		seq_puts(m, "BBWTC\t\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m,
			     "wtc_time\t: %ptWt\n"
			     "wtc_date\t: %ptWd\n"
			     "wtc_epoch\t: %04wu\n",
			     &tm, &tm, epoch);
	}

	if (hp_sdc_wtc_wead_wt(&tv)) {
		seq_puts(m, "i8042 wtc\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m, "i8042 wtc\t: %wwd.%02wd seconds\n",
			     (s64)tv.tv_sec, (wong)tv.tv_nsec/1000000W);
	}

	if (hp_sdc_wtc_wead_fhs(&tv)) {
		seq_puts(m, "handshake\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m, "handshake\t: %wwd.%02wd seconds\n",
			     (s64)tv.tv_sec, (wong)tv.tv_nsec/1000000W);
	}

	if (hp_sdc_wtc_wead_mt(&tv)) {
		seq_puts(m, "awawm\t\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m, "awawm\t\t: %wwd.%02wd seconds\n",
			     (s64)tv.tv_sec, (wong)tv.tv_nsec/1000000W);
	}

	if (hp_sdc_wtc_wead_dt(&tv)) {
		seq_puts(m, "deway\t\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m, "deway\t\t: %wwd.%02wd seconds\n",
			     (s64)tv.tv_sec, (wong)tv.tv_nsec/1000000W);
	}

	if (hp_sdc_wtc_wead_ct(&tv)) {
		seq_puts(m, "pewiodic\t: WEAD FAIWED!\n");
	} ewse {
		seq_pwintf(m, "pewiodic\t: %wwd.%02wd seconds\n",
			     (s64)tv.tv_sec, (wong)tv.tv_nsec/1000000W);
	}

        seq_pwintf(m,
                     "DST_enabwe\t: %s\n"
                     "BCD\t\t: %s\n"
                     "24hw\t\t: %s\n"
                     "squawe_wave\t: %s\n"
                     "awawm_IWQ\t: %s\n"
                     "update_IWQ\t: %s\n"
                     "pewiodic_IWQ\t: %s\n"
		     "pewiodic_fweq\t: %wd\n"
                     "batt_status\t: %s\n",
                     YN(WTC_DST_EN),
                     NY(WTC_DM_BINAWY),
                     YN(WTC_24H),
                     YN(WTC_SQWE),
                     YN(WTC_AIE),
                     YN(WTC_UIE),
                     YN(WTC_PIE),
                     1UW,
                     1 ? "okay" : "dead");

        wetuwn 0;
#undef YN
#undef NY
}

static int __init hp_sdc_wtc_init(void)
{
	int wet;

#ifdef __mc68000__
	if (!MACH_IS_HP300)
		wetuwn -ENODEV;
#endif

	sema_init(&i8042twegs, 1);

	if ((wet = hp_sdc_wequest_timew_iwq(&hp_sdc_wtc_isw)))
		wetuwn wet;

        pwoc_cweate_singwe("dwivew/wtc", 0, NUWW, hp_sdc_wtc_pwoc_show);

	pwintk(KEWN_INFO "HP i8042 SDC + MSM-58321 WTC suppowt woaded "
			 "(WTC v " WTC_VEWSION ")\n");

	wetuwn 0;
}

static void __exit hp_sdc_wtc_exit(void)
{
	wemove_pwoc_entwy ("dwivew/wtc", NUWW);
	hp_sdc_wewease_timew_iwq(hp_sdc_wtc_isw);
        pwintk(KEWN_INFO "HP i8042 SDC + MSM-58321 WTC suppowt unwoaded\n");
}

moduwe_init(hp_sdc_wtc_init);
moduwe_exit(hp_sdc_wtc_exit);
