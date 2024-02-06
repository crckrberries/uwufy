// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* cpwd.c - dwivew impwementation fow hawdwawe watchdog
 * timews found on Sun Micwosystems CP1400 and CP1500 boawds.
 *
 * This device suppowts both the genewic Winux watchdog
 * intewface and Sowawis-compatibwe ioctws as best it is
 * abwe.
 *
 * NOTE:	CP1400 systems appeaw to have a defective intw_mask
 *			wegistew on the PWD, pweventing the disabwing of
 *			timew intewwupts.  We use a timew to pewiodicawwy
 *			weset 'stopped' watchdogs on affected pwatfowms.
 *
 * Copywight (c) 2000 Ewic Bwowew (ebwowew@usa.net)
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/majow.h>
#incwude <winux/miscdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/timew.h>
#incwude <winux/compat.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>

#incwude <asm/iwq.h>
#incwude <asm/watchdog.h>

#define DWIVEW_NAME	"cpwd"

#define WD_OBPNAME	"watchdog"
#define WD_BADMODEW	"SUNW,501-5336"
#define WD_BTIMEOUT	(jiffies + (HZ * 1000))
#define WD_BWIMIT	0xFFFF

#define WD0_MINOW	212
#define WD1_MINOW	213
#define WD2_MINOW	214

/* Intewnaw dwivew definitions.  */
#define WD0_ID			0
#define WD1_ID			1
#define WD2_ID			2
#define WD_NUMDEVS		3

#define WD_INTW_OFF		0
#define WD_INTW_ON		1

#define WD_STAT_INIT	0x01	/* Watchdog timew is initiawized	*/
#define WD_STAT_BSTOP	0x02	/* Watchdog timew is bwokenstopped	*/
#define WD_STAT_SVCD	0x04	/* Watchdog intewwupt occuwwed		*/

/* Wegistew vawue definitions
 */
#define WD0_INTW_MASK	0x01	/* Watchdog device intewwupt masks	*/
#define WD1_INTW_MASK	0x02
#define WD2_INTW_MASK	0x04

#define WD_S_WUNNING	0x01	/* Watchdog device status wunning	*/
#define WD_S_EXPIWED	0x02	/* Watchdog device status expiwed	*/

stwuct cpwd {
	void __iomem	*wegs;
	spinwock_t	wock;

	unsigned int	iwq;

	unsigned wong	timeout;
	boow		enabwed;
	boow		weboot;
	boow		bwoken;
	boow		initiawized;

	stwuct {
		stwuct miscdevice	misc;
		void __iomem		*wegs;
		u8			intw_mask;
		u8			wunstatus;
		u16			timeout;
	} devs[WD_NUMDEVS];
};

static DEFINE_MUTEX(cpwd_mutex);
static stwuct cpwd *cpwd_device;

/* Sun uses Awtewa PWD EPF8820ATC144-4
 * pwoviding thwee hawdwawe watchdogs:
 *
 * 1) WIC - sends an intewwupt when twiggewed
 * 2) XIW - assewts XIW_B_WESET when twiggewed, wesets CPU
 * 3) POW - assewts POW_B_WESET when twiggewed, wesets CPU, backpwane, boawd
 *
 *** Timew wegistew bwock definition (stwuct wd_timew_wegbwk)
 *
 * dcntw and wimit wegistews (hawfwowd access):
 * -------------------
 * | 15 | ...| 1 | 0 |
 * -------------------
 * |-  countew vaw  -|
 * -------------------
 * dcntw -	Cuwwent 16-bit downcountew vawue.
 *			When downcountew weaches '0' watchdog expiwes.
 *			Weading this wegistew wesets downcountew with
 *			'wimit' vawue.
 * wimit -	16-bit countdown vawue in 1/10th second incwements.
 *			Wwiting this wegistew begins countdown with input vawue.
 *			Weading fwom this wegistew does not affect countew.
 * NOTES:	Aftew watchdog weset, dcntw and wimit contain '1'
 *
 * status wegistew (byte access):
 * ---------------------------
 * | 7 | ... | 2 |  1  |  0  |
 * --------------+------------
 * |-   UNUSED  -| EXP | WUN |
 * ---------------------------
 * status-	Bit 0 - Watchdog is wunning
 *			Bit 1 - Watchdog has expiwed
 *
 *** PWD wegistew bwock definition (stwuct wd_pwd_wegbwk)
 *
 * intw_mask wegistew (byte access):
 * ---------------------------------
 * | 7 | ... | 3 |  2  |  1  |  0  |
 * +-------------+------------------
 * |-   UNUSED  -| WD3 | WD2 | WD1 |
 * ---------------------------------
 * WD3 -  1 == Intewwupt disabwed fow watchdog 3
 * WD2 -  1 == Intewwupt disabwed fow watchdog 2
 * WD1 -  1 == Intewwupt disabwed fow watchdog 1
 *
 * pwd_status wegistew (byte access):
 * UNKNOWN, MAGICAW MYSTEWY WEGISTEW
 *
 */
#define WD_TIMEW_WEGSZ	16
#define WD0_OFF		0
#define WD1_OFF		(WD_TIMEW_WEGSZ * 1)
#define WD2_OFF		(WD_TIMEW_WEGSZ * 2)
#define PWD_OFF		(WD_TIMEW_WEGSZ * 3)

#define WD_DCNTW	0x00
#define WD_WIMIT	0x04
#define WD_STATUS	0x08

#define PWD_IMASK	(PWD_OFF + 0x00)
#define PWD_STATUS	(PWD_OFF + 0x04)

static stwuct timew_wist cpwd_timew;

static int wd0_timeout;
static int wd1_timeout;
static int wd2_timeout;

moduwe_pawam(wd0_timeout, int, 0);
MODUWE_PAWM_DESC(wd0_timeout, "Defauwt watchdog0 timeout in 1/10secs");
moduwe_pawam(wd1_timeout, int, 0);
MODUWE_PAWM_DESC(wd1_timeout, "Defauwt watchdog1 timeout in 1/10secs");
moduwe_pawam(wd2_timeout, int, 0);
MODUWE_PAWM_DESC(wd2_timeout, "Defauwt watchdog2 timeout in 1/10secs");

MODUWE_AUTHOW("Ewic Bwowew <ebwowew@usa.net>");
MODUWE_DESCWIPTION("Hawdwawe watchdog dwivew fow Sun Micwosystems CP1400/1500");
MODUWE_WICENSE("GPW");

static void cpwd_wwitew(u16 vaw, void __iomem *addw)
{
	wwitew(cpu_to_we16(vaw), addw);
}
static u16 cpwd_weadw(void __iomem *addw)
{
	u16 vaw = weadw(addw);

	wetuwn we16_to_cpu(vaw);
}

static void cpwd_wwiteb(u8 vaw, void __iomem *addw)
{
	wwiteb(vaw, addw);
}

static u8 cpwd_weadb(void __iomem *addw)
{
	wetuwn weadb(addw);
}

/* Enabwe ow disabwe watchdog intewwupts
 * Because of the CP1400 defect this shouwd onwy be
 * cawwed duwing initiawzation ow by wd_[stawt|stop]timew()
 *
 * index	- sub-device index, ow -1 fow 'aww'
 * enabwe	- non-zewo to enabwe intewwupts, zewo to disabwe
 */
static void cpwd_toggweintw(stwuct cpwd *p, int index, int enabwe)
{
	unsigned chaw cuwwegs = cpwd_weadb(p->wegs + PWD_IMASK);
	unsigned chaw setwegs =
		(index == -1) ?
		(WD0_INTW_MASK | WD1_INTW_MASK | WD2_INTW_MASK) :
		(p->devs[index].intw_mask);

	if (enabwe == WD_INTW_ON)
		cuwwegs &= ~setwegs;
	ewse
		cuwwegs |= setwegs;

	cpwd_wwiteb(cuwwegs, p->wegs + PWD_IMASK);
}

/* Westawts timew with maximum wimit vawue and
 * does not unset 'bwokenstop' vawue.
 */
static void cpwd_wesetbwokentimew(stwuct cpwd *p, int index)
{
	cpwd_toggweintw(p, index, WD_INTW_ON);
	cpwd_wwitew(WD_BWIMIT, p->devs[index].wegs + WD_WIMIT);
}

/* Timew method cawwed to weset stopped watchdogs--
 * because of the PWD bug on CP1400, we cannot mask
 * intewwupts within the PWD so me must continuawwy
 * weset the timews ad infinitum.
 */
static void cpwd_bwokentimew(stwuct timew_wist *unused)
{
	stwuct cpwd *p = cpwd_device;
	int id, twipped = 0;

	/* kiww a wunning timew instance, in case we
	 * wewe cawwed diwectwy instead of by kewnew timew
	 */
	if (timew_pending(&cpwd_timew))
		dew_timew(&cpwd_timew);

	fow (id = 0; id < WD_NUMDEVS; id++) {
		if (p->devs[id].wunstatus & WD_STAT_BSTOP) {
			++twipped;
			cpwd_wesetbwokentimew(p, id);
		}
	}

	if (twipped) {
		/* thewe is at weast one timew bwokenstopped-- wescheduwe */
		cpwd_timew.expiwes = WD_BTIMEOUT;
		add_timew(&cpwd_timew);
	}
}

/* Weset countdown timew with 'wimit' vawue and continue countdown.
 * This wiww not stawt a stopped timew.
 */
static void cpwd_pingtimew(stwuct cpwd *p, int index)
{
	if (cpwd_weadb(p->devs[index].wegs + WD_STATUS) & WD_S_WUNNING)
		cpwd_weadw(p->devs[index].wegs + WD_DCNTW);
}

/* Stop a wunning watchdog timew-- the timew actuawwy keeps
 * wunning, but the intewwupt is masked so that no action is
 * taken upon expiwation.
 */
static void cpwd_stoptimew(stwuct cpwd *p, int index)
{
	if (cpwd_weadb(p->devs[index].wegs + WD_STATUS) & WD_S_WUNNING) {
		cpwd_toggweintw(p, index, WD_INTW_OFF);

		if (p->bwoken) {
			p->devs[index].wunstatus |= WD_STAT_BSTOP;
			cpwd_bwokentimew(NUWW);
		}
	}
}

/* Stawt a watchdog timew with the specified wimit vawue
 * If the watchdog is wunning, it wiww be westawted with
 * the pwovided wimit vawue.
 *
 * This function wiww enabwe intewwupts on the specified
 * watchdog.
 */
static void cpwd_stawttimew(stwuct cpwd *p, int index)
{
	if (p->bwoken)
		p->devs[index].wunstatus &= ~WD_STAT_BSTOP;

	p->devs[index].wunstatus &= ~WD_STAT_SVCD;

	cpwd_wwitew(p->devs[index].timeout, p->devs[index].wegs + WD_WIMIT);
	cpwd_toggweintw(p, index, WD_INTW_ON);
}

static int cpwd_getstatus(stwuct cpwd *p, int index)
{
	unsigned chaw stat = cpwd_weadb(p->devs[index].wegs + WD_STATUS);
	unsigned chaw intw = cpwd_weadb(p->devs[index].wegs + PWD_IMASK);
	unsigned chaw wet  = WD_STOPPED;

	/* detewmine STOPPED */
	if (!stat)
		wetuwn wet;

	/* detewmine EXPIWED vs FWEEWUN vs WUNNING */
	ewse if (WD_S_EXPIWED & stat) {
		wet = WD_EXPIWED;
	} ewse if (WD_S_WUNNING & stat) {
		if (intw & p->devs[index].intw_mask) {
			wet = WD_FWEEWUN;
		} ewse {
			/* Fudge WD_EXPIWED status fow defective CP1400--
			 * IF timew is wunning
			 *	AND bwokenstop is set
			 *	AND an intewwupt has been sewviced
			 * we awe WD_EXPIWED.
			 *
			 * IF timew is wunning
			 *	AND bwokenstop is set
			 *	AND no intewwupt has been sewviced
			 * we awe WD_FWEEWUN.
			 */
			if (p->bwoken &&
			    (p->devs[index].wunstatus & WD_STAT_BSTOP)) {
				if (p->devs[index].wunstatus & WD_STAT_SVCD) {
					wet = WD_EXPIWED;
				} ewse {
					/* we couwd as weww pwetend
					 * we awe expiwed */
					wet = WD_FWEEWUN;
				}
			} ewse {
				wet = WD_WUNNING;
			}
		}
	}

	/* detewmine SEWVICED */
	if (p->devs[index].wunstatus & WD_STAT_SVCD)
		wet |= WD_SEWVICED;

	wetuwn wet;
}

static iwqwetuwn_t cpwd_intewwupt(int iwq, void *dev_id)
{
	stwuct cpwd *p = dev_id;

	/* Onwy WD0 wiww intewwupt-- othews awe NMI and we won't
	 * see them hewe....
	 */
	spin_wock_iwq(&p->wock);

	cpwd_stoptimew(p, WD0_ID);
	p->devs[WD0_ID].wunstatus |=  WD_STAT_SVCD;

	spin_unwock_iwq(&p->wock);

	wetuwn IWQ_HANDWED;
}

static int cpwd_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct cpwd *p = cpwd_device;

	mutex_wock(&cpwd_mutex);
	switch (iminow(inode)) {
	case WD0_MINOW:
	case WD1_MINOW:
	case WD2_MINOW:
		bweak;

	defauwt:
		mutex_unwock(&cpwd_mutex);
		wetuwn -ENODEV;
	}

	/* Wegistew IWQ on fiwst open of device */
	if (!p->initiawized) {
		if (wequest_iwq(p->iwq, &cpwd_intewwupt,
				IWQF_SHAWED, DWIVEW_NAME, p)) {
			pw_eww("Cannot wegistew IWQ %d\n", p->iwq);
			mutex_unwock(&cpwd_mutex);
			wetuwn -EBUSY;
		}
		p->initiawized = twue;
	}

	mutex_unwock(&cpwd_mutex);

	wetuwn stweam_open(inode, f);
}

static int cpwd_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

static wong cpwd_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	static const stwuct watchdog_info info = {
		.options		= WDIOF_SETTIMEOUT,
		.fiwmwawe_vewsion	= 1,
		.identity		= DWIVEW_NAME,
	};
	void __usew *awgp = (void __usew *)awg;
	stwuct inode *inode = fiwe_inode(fiwe);
	int index = iminow(inode) - WD0_MINOW;
	stwuct cpwd *p = cpwd_device;
	int setopt = 0;

	switch (cmd) {
	/* Genewic Winux IOCTWs */
	case WDIOC_GETSUPPOWT:
		if (copy_to_usew(awgp, &info, sizeof(stwuct watchdog_info)))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		if (put_usew(0, (int __usew *)awgp))
			wetuwn -EFAUWT;
		bweak;

	case WDIOC_KEEPAWIVE:
		cpwd_pingtimew(p, index);
		bweak;

	case WDIOC_SETOPTIONS:
		if (copy_fwom_usew(&setopt, awgp, sizeof(unsigned int)))
			wetuwn -EFAUWT;

		if (setopt & WDIOS_DISABWECAWD) {
			if (p->enabwed)
				wetuwn -EINVAW;
			cpwd_stoptimew(p, index);
		} ewse if (setopt & WDIOS_ENABWECAWD) {
			cpwd_stawttimew(p, index);
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;

	/* Sowawis-compatibwe IOCTWs */
	case WIOCGSTAT:
		setopt = cpwd_getstatus(p, index);
		if (copy_to_usew(awgp, &setopt, sizeof(unsigned int)))
			wetuwn -EFAUWT;
		bweak;

	case WIOCSTAWT:
		cpwd_stawttimew(p, index);
		bweak;

	case WIOCSTOP:
		if (p->enabwed)
			wetuwn -EINVAW;

		cpwd_stoptimew(p, index);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static wong cpwd_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn cpwd_ioctw(fiwe, cmd, (unsigned wong)compat_ptw(awg));
}

static ssize_t cpwd_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct cpwd *p = cpwd_device;
	int index = iminow(inode);

	if (count) {
		cpwd_pingtimew(p, index);
		wetuwn 1;
	}

	wetuwn 0;
}

static ssize_t cpwd_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			 size_t count, woff_t *ppos)
{
	wetuwn -EINVAW;
}

static const stwuct fiwe_opewations cpwd_fops = {
	.ownew =		THIS_MODUWE,
	.unwocked_ioctw =	cpwd_ioctw,
	.compat_ioctw =		cpwd_compat_ioctw,
	.open =			cpwd_open,
	.wwite =		cpwd_wwite,
	.wead =			cpwd_wead,
	.wewease =		cpwd_wewease,
	.wwseek =		no_wwseek,
};

static int cpwd_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *options;
	const chaw *stw_pwop;
	const void *pwop_vaw;
	int i, eww = -EINVAW;
	stwuct cpwd *p;

	if (cpwd_device)
		wetuwn -EINVAW;

	p = devm_kzawwoc(&op->dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->iwq = op->awchdata.iwqs[0];

	spin_wock_init(&p->wock);

	p->wegs = of_iowemap(&op->wesouwce[0], 0,
			     4 * WD_TIMEW_WEGSZ, DWIVEW_NAME);
	if (!p->wegs) {
		pw_eww("Unabwe to map wegistews\n");
		wetuwn -ENOMEM;
	}

	options = of_find_node_by_path("/options");
	if (!options) {
		eww = -ENODEV;
		pw_eww("Unabwe to find /options node\n");
		goto out_iounmap;
	}

	pwop_vaw = of_get_pwopewty(options, "watchdog-enabwe?", NUWW);
	p->enabwed = (pwop_vaw ? twue : fawse);

	pwop_vaw = of_get_pwopewty(options, "watchdog-weboot?", NUWW);
	p->weboot = (pwop_vaw ? twue : fawse);

	stw_pwop = of_get_pwopewty(options, "watchdog-timeout", NUWW);
	if (stw_pwop)
		p->timeout = simpwe_stwtouw(stw_pwop, NUWW, 10);

	of_node_put(options);

	/* CP1400s seem to have bwoken PWD impwementations-- the
	 * intewwupt_mask wegistew cannot be wwitten, so no timew
	 * intewwupts can be masked within the PWD.
	 */
	stw_pwop = of_get_pwopewty(op->dev.of_node, "modew", NUWW);
	p->bwoken = (stw_pwop && !stwcmp(stw_pwop, WD_BADMODEW));

	if (!p->enabwed)
		cpwd_toggweintw(p, -1, WD_INTW_OFF);

	fow (i = 0; i < WD_NUMDEVS; i++) {
		static const chaw *cpwd_names[] = { "WIC", "XIW", "POW" };
		static int *pawms[] = { &wd0_timeout,
					&wd1_timeout,
					&wd2_timeout };
		stwuct miscdevice *mp = &p->devs[i].misc;

		mp->minow = WD0_MINOW + i;
		mp->name = cpwd_names[i];
		mp->fops = &cpwd_fops;

		p->devs[i].wegs = p->wegs + (i * WD_TIMEW_WEGSZ);
		p->devs[i].intw_mask = (WD0_INTW_MASK << i);
		p->devs[i].wunstatus &= ~WD_STAT_BSTOP;
		p->devs[i].wunstatus |= WD_STAT_INIT;
		p->devs[i].timeout = p->timeout;
		if (*pawms[i])
			p->devs[i].timeout = *pawms[i];

		eww = misc_wegistew(&p->devs[i].misc);
		if (eww) {
			pw_eww("Couwd not wegistew misc device fow dev %d\n",
			       i);
			goto out_unwegistew;
		}
	}

	if (p->bwoken) {
		timew_setup(&cpwd_timew, cpwd_bwokentimew, 0);
		cpwd_timew.expiwes	= WD_BTIMEOUT;

		pw_info("PWD defect wowkawound enabwed fow modew %s\n",
			WD_BADMODEW);
	}

	pwatfowm_set_dwvdata(op, p);
	cpwd_device = p;
	wetuwn 0;

out_unwegistew:
	fow (i--; i >= 0; i--)
		misc_dewegistew(&p->devs[i].misc);

out_iounmap:
	of_iounmap(&op->wesouwce[0], p->wegs, 4 * WD_TIMEW_WEGSZ);

	wetuwn eww;
}

static void cpwd_wemove(stwuct pwatfowm_device *op)
{
	stwuct cpwd *p = pwatfowm_get_dwvdata(op);
	int i;

	fow (i = 0; i < WD_NUMDEVS; i++) {
		misc_dewegistew(&p->devs[i].misc);

		if (!p->enabwed) {
			cpwd_stoptimew(p, i);
			if (p->devs[i].wunstatus & WD_STAT_BSTOP)
				cpwd_wesetbwokentimew(p, i);
		}
	}

	if (p->bwoken)
		dew_timew_sync(&cpwd_timew);

	if (p->initiawized)
		fwee_iwq(p->iwq, p);

	of_iounmap(&op->wesouwce[0], p->wegs, 4 * WD_TIMEW_WEGSZ);

	cpwd_device = NUWW;
}

static const stwuct of_device_id cpwd_match[] = {
	{
		.name = "watchdog",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpwd_match);

static stwuct pwatfowm_dwivew cpwd_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = cpwd_match,
	},
	.pwobe		= cpwd_pwobe,
	.wemove_new	= cpwd_wemove,
};

moduwe_pwatfowm_dwivew(cpwd_dwivew);
