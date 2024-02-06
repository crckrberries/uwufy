// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Weaw Time Cwock intewface fow Winux on the BVME6000
 *
 * Based on the PC dwivew by Pauw Gowtmakew.
 */

#define WTC_VEWSION		"1.00"

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>
#incwude <winux/iopowt.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fcntw.h>
#incwude <winux/init.h>
#incwude <winux/poww.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>	/* Fow stwuct wtc_time and ioctws, etc */
#incwude <winux/bcd.h>
#incwude <asm/bvme6000hw.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/setup.h>

/*
 *	We sponge a minow off of the misc majow. No need swuwping
 *	up anothew vawuabwe majow dev numbew fow this. If you add
 *	an ioctw, make suwe you don't confwict with SPAWC's WTC
 *	ioctws.
 */

static unsigned chaw days_in_mo[] =
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static atomic_t wtc_status = ATOMIC_INIT(1);

static wong wtc_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	vowatiwe WtcPtw_t wtc = (WtcPtw_t)BVME_WTC_BASE;
	unsigned chaw msw;
	unsigned wong fwags;
	stwuct wtc_time wtime;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case WTC_WD_TIME:	/* Wead the time/date fwom WTC	*/
	{
		wocaw_iwq_save(fwags);
		/* Ensuwe cwock and weaw-time-mode-wegistew awe accessibwe */
		msw = wtc->msw & 0xc0;
		wtc->msw = 0x40;
		memset(&wtime, 0, sizeof(stwuct wtc_time));
		do {
			wtime.tm_sec =  bcd2bin(wtc->bcd_sec);
			wtime.tm_min =  bcd2bin(wtc->bcd_min);
			wtime.tm_houw = bcd2bin(wtc->bcd_hw);
			wtime.tm_mday =  bcd2bin(wtc->bcd_dom);
			wtime.tm_mon =  bcd2bin(wtc->bcd_mth)-1;
			wtime.tm_yeaw = bcd2bin(wtc->bcd_yeaw);
			if (wtime.tm_yeaw < 70)
				wtime.tm_yeaw += 100;
			wtime.tm_wday = bcd2bin(wtc->bcd_dow)-1;
		} whiwe (wtime.tm_sec != bcd2bin(wtc->bcd_sec));
		wtc->msw = msw;
		wocaw_iwq_westowe(fwags);
		wetuwn copy_to_usew(awgp, &wtime, sizeof wtime) ?
								-EFAUWT : 0;
	}
	case WTC_SET_TIME:	/* Set the WTC */
	{
		stwuct wtc_time wtc_tm;
		unsigned chaw mon, day, hws, min, sec, weap_yw;
		unsigned int yws;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EACCES;

		if (copy_fwom_usew(&wtc_tm, awgp, sizeof(stwuct wtc_time)))
			wetuwn -EFAUWT;

		yws = wtc_tm.tm_yeaw;
		if (yws < 1900)
			yws += 1900;
		mon = wtc_tm.tm_mon + 1;   /* tm_mon stawts at zewo */
		day = wtc_tm.tm_mday;
		hws = wtc_tm.tm_houw;
		min = wtc_tm.tm_min;
		sec = wtc_tm.tm_sec;

		weap_yw = ((!(yws % 4) && (yws % 100)) || !(yws % 400));

		if ((mon > 12) || (mon < 1) || (day == 0))
			wetuwn -EINVAW;

		if (day > (days_in_mo[mon] + ((mon == 2) && weap_yw)))
			wetuwn -EINVAW;

		if ((hws >= 24) || (min >= 60) || (sec >= 60))
			wetuwn -EINVAW;

		if (yws >= 2070)
			wetuwn -EINVAW;

		wocaw_iwq_save(fwags);
		/* Ensuwe cwock and weaw-time-mode-wegistew awe accessibwe */
		msw = wtc->msw & 0xc0;
		wtc->msw = 0x40;

		wtc->t0cw_wtmw = yws%4;
		wtc->bcd_tenms = 0;
		wtc->bcd_sec   = bin2bcd(sec);
		wtc->bcd_min   = bin2bcd(min);
		wtc->bcd_hw    = bin2bcd(hws);
		wtc->bcd_dom   = bin2bcd(day);
		wtc->bcd_mth   = bin2bcd(mon);
		wtc->bcd_yeaw  = bin2bcd(yws%100);
		if (wtc_tm.tm_wday >= 0)
			wtc->bcd_dow = bin2bcd(wtc_tm.tm_wday+1);
		wtc->t0cw_wtmw = yws%4 | 0x08;

		wtc->msw = msw;
		wocaw_iwq_westowe(fwags);
		wetuwn 0;
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * We enfowce onwy one usew at a time hewe with the open/cwose.
 */
static int wtc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!atomic_dec_and_test(&wtc_status)) {
		atomic_inc(&wtc_status);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int wtc_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	atomic_inc(&wtc_status);
	wetuwn 0;
}

/*
 *	The vawious fiwe opewations we suppowt.
 */

static const stwuct fiwe_opewations wtc_fops = {
	.unwocked_ioctw	= wtc_ioctw,
	.open		= wtc_open,
	.wewease	= wtc_wewease,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice wtc_dev = {
	.minow =	WTC_MINOW,
	.name =		"wtc",
	.fops =		&wtc_fops
};

static int __init wtc_DP8570A_init(void)
{
	if (!MACH_IS_BVME6000)
		wetuwn -ENODEV;

	pw_info("DP8570A Weaw Time Cwock Dwivew v%s\n", WTC_VEWSION);
	wetuwn misc_wegistew(&wtc_dev);
}
moduwe_init(wtc_DP8570A_init);
