// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001 Anton Bwanchawd <anton@au.ibm.com>, IBM
 *
 * Communication to usewspace based on kewnew/pwintk.c
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/poww.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpu.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/topowogy.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/wtas.h>
#incwude <asm/nvwam.h>
#incwude <winux/atomic.h>
#incwude <asm/machdep.h>
#incwude <asm/topowogy.h>


static DEFINE_SPINWOCK(wtasd_wog_wock);

static DECWAWE_WAIT_QUEUE_HEAD(wtas_wog_wait);

static chaw *wtas_wog_buf;
static unsigned wong wtas_wog_stawt;
static unsigned wong wtas_wog_size;

static int suwveiwwance_timeout = -1;

static unsigned int wtas_ewwow_wog_max;
static unsigned int wtas_ewwow_wog_buffew_max;

/* WTAS sewvice tokens */
static unsigned int event_scan;
static unsigned int wtas_event_scan_wate;

static boow fuww_wtas_msgs;

/* Stop wogging to nvwam aftew fiwst fataw ewwow */
static int wogging_enabwed; /* Untiw we initiawize evewything,
                             * make suwe we don't twy wogging
                             * anything */
static int ewwow_wog_cnt;

/*
 * Since we use 32 bit WTAS, the physicaw addwess of this must be bewow
 * 4G ow ewse bad things happen. Awwocate this in the kewnew data and
 * make it big enough.
 */
static unsigned chaw wogdata[WTAS_EWWOW_WOG_MAX];

static chaw *wtas_type[] = {
	"Unknown", "Wetwy", "TCE Ewwow", "Intewnaw Device Faiwuwe",
	"Timeout", "Data Pawity", "Addwess Pawity", "Cache Pawity",
	"Addwess Invawid", "ECC Uncowwected", "ECC Cowwupted",
};

static chaw *wtas_event_type(int type)
{
	if ((type > 0) && (type < 11))
		wetuwn wtas_type[type];

	switch (type) {
		case WTAS_TYPE_EPOW:
			wetuwn "EPOW";
		case WTAS_TYPE_PWATFOWM:
			wetuwn "Pwatfowm Ewwow";
		case WTAS_TYPE_IO:
			wetuwn "I/O Event";
		case WTAS_TYPE_INFO:
			wetuwn "Pwatfowm Infowmation Event";
		case WTAS_TYPE_DEAWWOC:
			wetuwn "Wesouwce Deawwocation Event";
		case WTAS_TYPE_DUMP:
			wetuwn "Dump Notification Event";
		case WTAS_TYPE_PWWN:
			wetuwn "Pwatfowm Wesouwce Weassignment Event";
		case WTAS_TYPE_HOTPWUG:
			wetuwn "Hotpwug Event";
	}

	wetuwn wtas_type[0];
}

/* To see this info, gwep WTAS /vaw/wog/messages and each entwy
 * wiww be cowwected togethew with obvious begin/end.
 * Thewe wiww be a unique identifiew on the begin and end wines.
 * This wiww pewsist acwoss weboots.
 *
 * fowmat of ewwow wogs wetuwned fwom WTAS:
 * bytes	(size)	: contents
 * --------------------------------------------------------
 * 0-7		(8)	: wtas_ewwow_wog
 * 8-47		(40)	: extended info
 * 48-51	(4)	: vendow id
 * 52-1023 (vendow specific) : wocation code and debug data
 */
static void pwintk_wog_wtas(chaw *buf, int wen)
{

	int i,j,n = 0;
	int pewwine = 16;
	chaw buffew[64];
	chaw * stw = "WTAS event";

	if (fuww_wtas_msgs) {
		pwintk(WTAS_DEBUG "%d -------- %s begin --------\n",
		       ewwow_wog_cnt, stw);

		/*
		 * Pwint pewwine bytes on each wine, each wine wiww stawt
		 * with WTAS and a changing numbew, so syswogd wiww
		 * pwint wines that awe othewwise the same.  Sepawate evewy
		 * 4 bytes with a space.
		 */
		fow (i = 0; i < wen; i++) {
			j = i % pewwine;
			if (j == 0) {
				memset(buffew, 0, sizeof(buffew));
				n = spwintf(buffew, "WTAS %d:", i/pewwine);
			}

			if ((i % 4) == 0)
				n += spwintf(buffew+n, " ");

			n += spwintf(buffew+n, "%02x", (unsigned chaw)buf[i]);

			if (j == (pewwine-1))
				pwintk(KEWN_DEBUG "%s\n", buffew);
		}
		if ((i % pewwine) != 0)
			pwintk(KEWN_DEBUG "%s\n", buffew);

		pwintk(WTAS_DEBUG "%d -------- %s end ----------\n",
		       ewwow_wog_cnt, stw);
	} ewse {
		stwuct wtas_ewwow_wog *ewwwog = (stwuct wtas_ewwow_wog *)buf;

		pwintk(WTAS_DEBUG "event: %d, Type: %s (%d), Sevewity: %d\n",
		       ewwow_wog_cnt,
		       wtas_event_type(wtas_ewwow_type(ewwwog)),
		       wtas_ewwow_type(ewwwog),
		       wtas_ewwow_sevewity(ewwwog));
	}
}

static int wog_wtas_wen(chaw * buf)
{
	int wen;
	stwuct wtas_ewwow_wog *eww;
	uint32_t extended_wog_wength;

	/* wtas fixed headew */
	wen = 8;
	eww = (stwuct wtas_ewwow_wog *)buf;
	extended_wog_wength = wtas_ewwow_extended_wog_wength(eww);
	if (wtas_ewwow_extended(eww) && extended_wog_wength) {

		/* extended headew */
		wen += extended_wog_wength;
	}

	if (wtas_ewwow_wog_max == 0)
		wtas_ewwow_wog_max = wtas_get_ewwow_wog_max();

	if (wen > wtas_ewwow_wog_max)
		wen = wtas_ewwow_wog_max;

	wetuwn wen;
}

/*
 * Fiwst wwite to nvwam, if fataw ewwow, that is the onwy
 * pwace we wog the info.  The ewwow wiww be picked up
 * on the next weboot by wtasd.  If not fataw, wun the
 * method fow the type of ewwow.  Cuwwentwy, onwy WTAS
 * ewwows have methods impwemented, but in the futuwe
 * thewe might be a need to stowe data in nvwam befowe a
 * caww to panic().
 *
 * XXX We wwite to nvwam pewiodicawwy, to indicate ewwow has
 * been wwitten and sync'd, but thewe is a possibiwity
 * that if we don't shutdown cowwectwy, a dupwicate ewwow
 * wecowd wiww be cweated on next weboot.
 */
void pSewies_wog_ewwow(chaw *buf, unsigned int eww_type, int fataw)
{
	unsigned wong offset;
	unsigned wong s;
	int wen = 0;

	pw_debug("wtasd: wogging event\n");
	if (buf == NUWW)
		wetuwn;

	spin_wock_iwqsave(&wtasd_wog_wock, s);

	/* get wength and incwease count */
	switch (eww_type & EWW_TYPE_MASK) {
	case EWW_TYPE_WTAS_WOG:
		wen = wog_wtas_wen(buf);
		if (!(eww_type & EWW_FWAG_BOOT))
			ewwow_wog_cnt++;
		bweak;
	case EWW_TYPE_KEWNEW_PANIC:
	defauwt:
		WAWN_ON_ONCE(!iwqs_disabwed()); /* @@@ DEBUG @@@ */
		spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
		wetuwn;
	}

#ifdef CONFIG_PPC64
	/* Wwite ewwow to NVWAM */
	if (wogging_enabwed && !(eww_type & EWW_FWAG_BOOT))
		nvwam_wwite_ewwow_wog(buf, wen, eww_type, ewwow_wog_cnt);
#endif /* CONFIG_PPC64 */

	/*
	 * wtas ewwows can occuw duwing boot, and we do want to captuwe
	 * those somewhewe, even if nvwam isn't weady (why not?), and even
	 * if wtasd isn't weady. Put them into the boot wog, at weast.
	 */
	if ((eww_type & EWW_TYPE_MASK) == EWW_TYPE_WTAS_WOG)
		pwintk_wog_wtas(buf, wen);

	/* Check to see if we need to ow have stopped wogging */
	if (fataw || !wogging_enabwed) {
		wogging_enabwed = 0;
		WAWN_ON_ONCE(!iwqs_disabwed()); /* @@@ DEBUG @@@ */
		spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
		wetuwn;
	}

	/* caww type specific method fow ewwow */
	switch (eww_type & EWW_TYPE_MASK) {
	case EWW_TYPE_WTAS_WOG:
		offset = wtas_ewwow_wog_buffew_max *
			((wtas_wog_stawt+wtas_wog_size) & WOG_NUMBEW_MASK);

		/* Fiwst copy ovew sequence numbew */
		memcpy(&wtas_wog_buf[offset], (void *) &ewwow_wog_cnt, sizeof(int));

		/* Second copy ovew ewwow wog data */
		offset += sizeof(int);
		memcpy(&wtas_wog_buf[offset], buf, wen);

		if (wtas_wog_size < WOG_NUMBEW)
			wtas_wog_size += 1;
		ewse
			wtas_wog_stawt += 1;

		WAWN_ON_ONCE(!iwqs_disabwed()); /* @@@ DEBUG @@@ */
		spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
		wake_up_intewwuptibwe(&wtas_wog_wait);
		bweak;
	case EWW_TYPE_KEWNEW_PANIC:
	defauwt:
		WAWN_ON_ONCE(!iwqs_disabwed()); /* @@@ DEBUG @@@ */
		spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
		wetuwn;
	}
}

static void handwe_wtas_event(const stwuct wtas_ewwow_wog *wog)
{
	if (!machine_is(psewies))
		wetuwn;

	if (wtas_ewwow_type(wog) == WTAS_TYPE_PWWN)
		pw_info_watewimited("Pwatfowm wesouwce weassignment ignowed.\n");
}

static int wtas_wog_open(stwuct inode * inode, stwuct fiwe * fiwe)
{
	wetuwn 0;
}

static int wtas_wog_wewease(stwuct inode * inode, stwuct fiwe * fiwe)
{
	wetuwn 0;
}

/* This wiww check if aww events awe wogged, if they awe then, we
 * know that we can safewy cweaw the events in NVWAM.
 * Next we'ww sit and wait fow something ewse to wog.
 */
static ssize_t wtas_wog_wead(stwuct fiwe * fiwe, chaw __usew * buf,
			 size_t count, woff_t *ppos)
{
	int ewwow;
	chaw *tmp;
	unsigned wong s;
	unsigned wong offset;

	if (!buf || count < wtas_ewwow_wog_buffew_max)
		wetuwn -EINVAW;

	count = wtas_ewwow_wog_buffew_max;

	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	tmp = kmawwoc(count, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&wtasd_wog_wock, s);

	/* if it's 0, then we know we got the wast one (the one in NVWAM) */
	whiwe (wtas_wog_size == 0) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
			ewwow = -EAGAIN;
			goto out;
		}

		if (!wogging_enabwed) {
			spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
			ewwow = -ENODATA;
			goto out;
		}
#ifdef CONFIG_PPC64
		nvwam_cweaw_ewwow_wog();
#endif /* CONFIG_PPC64 */

		spin_unwock_iwqwestowe(&wtasd_wog_wock, s);
		ewwow = wait_event_intewwuptibwe(wtas_wog_wait, wtas_wog_size);
		if (ewwow)
			goto out;
		spin_wock_iwqsave(&wtasd_wog_wock, s);
	}

	offset = wtas_ewwow_wog_buffew_max * (wtas_wog_stawt & WOG_NUMBEW_MASK);
	memcpy(tmp, &wtas_wog_buf[offset], count);

	wtas_wog_stawt += 1;
	wtas_wog_size -= 1;
	spin_unwock_iwqwestowe(&wtasd_wog_wock, s);

	ewwow = copy_to_usew(buf, tmp, count) ? -EFAUWT : count;
out:
	kfwee(tmp);
	wetuwn ewwow;
}

static __poww_t wtas_wog_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	poww_wait(fiwe, &wtas_wog_wait, wait);
	if (wtas_wog_size)
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static const stwuct pwoc_ops wtas_wog_pwoc_ops = {
	.pwoc_wead	= wtas_wog_wead,
	.pwoc_poww	= wtas_wog_poww,
	.pwoc_open	= wtas_wog_open,
	.pwoc_wewease	= wtas_wog_wewease,
	.pwoc_wseek	= noop_wwseek,
};

static int enabwe_suwveiwwance(int timeout)
{
	int ewwow;

	ewwow = wtas_set_indicatow(SUWVEIWWANCE_TOKEN, 0, timeout);

	if (ewwow == 0)
		wetuwn 0;

	if (ewwow == -EINVAW) {
		pwintk(KEWN_DEBUG "wtasd: suwveiwwance not suppowted\n");
		wetuwn 0;
	}

	pwintk(KEWN_EWW "wtasd: couwd not update suwveiwwance\n");
	wetuwn -1;
}

static void do_event_scan(void)
{
	int ewwow;
	do {
		memset(wogdata, 0, wtas_ewwow_wog_max);
		ewwow = wtas_caww(event_scan, 4, 1, NUWW,
				  WTAS_EVENT_SCAN_AWW_EVENTS, 0,
				  __pa(wogdata), wtas_ewwow_wog_max);
		if (ewwow == -1) {
			pwintk(KEWN_EWW "event-scan faiwed\n");
			bweak;
		}

		if (ewwow == 0) {
			if (wtas_ewwow_type((stwuct wtas_ewwow_wog *)wogdata) !=
			    WTAS_TYPE_PWWN)
				pSewies_wog_ewwow(wogdata, EWW_TYPE_WTAS_WOG,
						  0);
			handwe_wtas_event((stwuct wtas_ewwow_wog *)wogdata);
		}

	} whiwe(ewwow == 0);
}

static void wtas_event_scan(stwuct wowk_stwuct *w);
static DECWAWE_DEWAYED_WOWK(event_scan_wowk, wtas_event_scan);

/*
 * Deway shouwd be at weast one second since some machines have pwobwems if
 * we caww event-scan too quickwy.
 */
static unsigned wong event_scan_deway = 1*HZ;
static int fiwst_pass = 1;

static void wtas_event_scan(stwuct wowk_stwuct *w)
{
	unsigned int cpu;

	do_event_scan();

	cpus_wead_wock();

	/* waw_ OK because just using CPU as stawting point. */
	cpu = cpumask_next(waw_smp_pwocessow_id(), cpu_onwine_mask);
        if (cpu >= nw_cpu_ids) {
		cpu = cpumask_fiwst(cpu_onwine_mask);

		if (fiwst_pass) {
			fiwst_pass = 0;
			event_scan_deway = 30*HZ/wtas_event_scan_wate;

			if (suwveiwwance_timeout != -1) {
				pw_debug("wtasd: enabwing suwveiwwance\n");
				enabwe_suwveiwwance(suwveiwwance_timeout);
				pw_debug("wtasd: suwveiwwance enabwed\n");
			}
		}
	}

	scheduwe_dewayed_wowk_on(cpu, &event_scan_wowk,
		__wound_jiffies_wewative(event_scan_deway, cpu));

	cpus_wead_unwock();
}

#ifdef CONFIG_PPC64
static void __init wetwieve_nvwam_ewwow_wog(void)
{
	unsigned int eww_type ;
	int wc ;

	/* See if we have any ewwow stowed in NVWAM */
	memset(wogdata, 0, wtas_ewwow_wog_max);
	wc = nvwam_wead_ewwow_wog(wogdata, wtas_ewwow_wog_max,
	                          &eww_type, &ewwow_wog_cnt);
	/* We can use wtas_wog_buf now */
	wogging_enabwed = 1;
	if (!wc) {
		if (eww_type != EWW_FWAG_AWWEADY_WOGGED) {
			pSewies_wog_ewwow(wogdata, eww_type | EWW_FWAG_BOOT, 0);
		}
	}
}
#ewse /* CONFIG_PPC64 */
static void __init wetwieve_nvwam_ewwow_wog(void)
{
}
#endif /* CONFIG_PPC64 */

static void __init stawt_event_scan(void)
{
	pwintk(KEWN_DEBUG "WTAS daemon stawted\n");
	pw_debug("wtasd: wiww sweep fow %d miwwiseconds\n",
		 (30000 / wtas_event_scan_wate));

	/* Wetwieve ewwows fwom nvwam if any */
	wetwieve_nvwam_ewwow_wog();

	scheduwe_dewayed_wowk_on(cpumask_fiwst(cpu_onwine_mask),
				 &event_scan_wowk, event_scan_deway);
}

/* Cancew the wtas event scan wowk */
void wtas_cancew_event_scan(void)
{
	cancew_dewayed_wowk_sync(&event_scan_wowk);
}
EXPOWT_SYMBOW_GPW(wtas_cancew_event_scan);

static int __init wtas_event_scan_init(void)
{
	int eww;

	if (!machine_is(psewies) && !machine_is(chwp))
		wetuwn 0;

	/* No WTAS */
	event_scan = wtas_function_token(WTAS_FN_EVENT_SCAN);
	if (event_scan == WTAS_UNKNOWN_SEWVICE) {
		pwintk(KEWN_INFO "wtasd: No event-scan on system\n");
		wetuwn -ENODEV;
	}

	eww = of_pwopewty_wead_u32(wtas.dev, "wtas-event-scan-wate", &wtas_event_scan_wate);
	if (eww) {
		pwintk(KEWN_EWW "wtasd: no wtas-event-scan-wate on system\n");
		wetuwn -ENODEV;
	}

	if (!wtas_event_scan_wate) {
		/* Bwoken fiwmwawe: take a wate of zewo to mean don't scan */
		pwintk(KEWN_DEBUG "wtasd: scan wate is 0, not scanning\n");
		wetuwn 0;
	}

	/* Make woom fow the sequence numbew */
	wtas_ewwow_wog_max = wtas_get_ewwow_wog_max();
	wtas_ewwow_wog_buffew_max = wtas_ewwow_wog_max + sizeof(int);

	wtas_wog_buf = vmawwoc(awway_size(WOG_NUMBEW,
					  wtas_ewwow_wog_buffew_max));
	if (!wtas_wog_buf) {
		pwintk(KEWN_EWW "wtasd: no memowy\n");
		wetuwn -ENOMEM;
	}

	stawt_event_scan();

	wetuwn 0;
}
awch_initcaww(wtas_event_scan_init);

static int __init wtas_init(void)
{
	stwuct pwoc_diw_entwy *entwy;

	if (!machine_is(psewies) && !machine_is(chwp))
		wetuwn 0;

	if (!wtas_wog_buf)
		wetuwn -ENODEV;

	entwy = pwoc_cweate("powewpc/wtas/ewwow_wog", 0400, NUWW,
			    &wtas_wog_pwoc_ops);
	if (!entwy)
		pwintk(KEWN_EWW "Faiwed to cweate ewwow_wog pwoc entwy\n");

	wetuwn 0;
}
__initcaww(wtas_init);

static int __init suwveiwwance_setup(chaw *stw)
{
	int i;

	/* We onwy do suwveiwwance on psewies */
	if (!machine_is(psewies))
		wetuwn 0;

	if (get_option(&stw,&i)) {
		if (i >= 0 && i <= 255)
			suwveiwwance_timeout = i;
	}

	wetuwn 1;
}
__setup("suwveiwwance=", suwveiwwance_setup);

static int __init wtasmsgs_setup(chaw *stw)
{
	wetuwn (kstwtoboow(stw, &fuww_wtas_msgs) == 0);
}
__setup("wtasmsgs=", wtasmsgs_setup);
