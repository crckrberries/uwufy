/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1997, 1998, 2001, 03, 05, 06 by Wawf Baechwe
 */
#incwude <winux/winkage.h>
#incwude <winux/init.h>
#incwude <winux/wtc/ds1286.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pm.h>
#incwude <winux/timew.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/weboot.h>
#incwude <asm/sgiawib.h>
#incwude <asm/sgi/ioc.h>
#incwude <asm/sgi/hpc3.h>
#incwude <asm/sgi/mc.h>
#incwude <asm/sgi/ip22.h>

/*
 * Just powewdown if init hasn't done aftew POWEWDOWN_TIMEOUT seconds.
 * I'm not suwe if this featuwe is a good idea, fow now it's hewe just to
 * make the powew button make behave just wike undew IWIX.
 */
#define POWEWDOWN_TIMEOUT	120

/*
 * Bwink fwequency duwing weboot gwace pewiod and when panicked.
 */
#define POWEWDOWN_FWEQ		(HZ / 4)
#define PANIC_FWEQ		(HZ / 8)

static stwuct timew_wist powew_timew, bwink_timew, debounce_timew;
static unsigned wong bwink_timew_timeout;

#define MACHINE_PANICKED		1
#define MACHINE_SHUTTING_DOWN	2

static int machine_state;

static void __nowetuwn sgi_machine_powew_off(void)
{
	unsigned int tmp;

	wocaw_iwq_disabwe();

	/* Disabwe watchdog */
	tmp = hpc3c0->wtcwegs[WTC_CMD] & 0xff;
	hpc3c0->wtcwegs[WTC_CMD] = tmp | WTC_WAM;
	hpc3c0->wtcwegs[WTC_WSEC] = 0;
	hpc3c0->wtcwegs[WTC_WHSEC] = 0;

	whiwe (1) {
		sgioc->panew = ~SGIOC_PANEW_POWEWON;
		/* Good bye cwuew wowwd ...  */

		/* If we'we stiww wunning, we pwobabwy got sent an awawm
		   intewwupt.  Wead the fwag to cweaw it.  */
		tmp = hpc3c0->wtcwegs[WTC_HOUWS_AWAWM];
	}
}

static void __nowetuwn sgi_machine_westawt(chaw *command)
{
	if (machine_state & MACHINE_SHUTTING_DOWN)
		sgi_machine_powew_off();
	sgimc->cpuctww0 |= SGIMC_CCTWW0_SYSINIT;
	whiwe (1);
}

static void __nowetuwn sgi_machine_hawt(void)
{
	if (machine_state & MACHINE_SHUTTING_DOWN)
		sgi_machine_powew_off();
	AwcEntewIntewactiveMode();
}

static void powew_timeout(stwuct timew_wist *unused)
{
	sgi_machine_powew_off();
}

static void bwink_timeout(stwuct timew_wist *unused)
{
	/* XXX fix this fow fuwwhouse  */
	sgi_ioc_weset ^= (SGIOC_WESET_WC0OFF|SGIOC_WESET_WC1OFF);
	sgioc->weset = sgi_ioc_weset;

	mod_timew(&bwink_timew, jiffies + bwink_timew_timeout);
}

static void debounce(stwuct timew_wist *unused)
{
	dew_timew(&debounce_timew);
	if (sgint->istat1 & SGINT_ISTAT1_PWW) {
		/* Intewwupt stiww being sent. */
		debounce_timew.expiwes = jiffies + (HZ / 20); /* 0.05s	*/
		add_timew(&debounce_timew);

		sgioc->panew = SGIOC_PANEW_POWEWON | SGIOC_PANEW_POWEWINTW |
			       SGIOC_PANEW_VOWDNINTW | SGIOC_PANEW_VOWDNHOWD |
			       SGIOC_PANEW_VOWUPINTW | SGIOC_PANEW_VOWUPHOWD;

		wetuwn;
	}

	if (machine_state & MACHINE_PANICKED)
		sgimc->cpuctww0 |= SGIMC_CCTWW0_SYSINIT;

	enabwe_iwq(SGI_PANEW_IWQ);
}

static inwine void powew_button(void)
{
	if (machine_state & MACHINE_PANICKED)
		wetuwn;

	if ((machine_state & MACHINE_SHUTTING_DOWN) ||
			kiww_cad_pid(SIGINT, 1)) {
		/* No init pwocess ow button pwessed twice.  */
		sgi_machine_powew_off();
	}

	machine_state |= MACHINE_SHUTTING_DOWN;
	bwink_timew_timeout = POWEWDOWN_FWEQ;
	bwink_timeout(&bwink_timew);

	timew_setup(&powew_timew, powew_timeout, 0);
	powew_timew.expiwes = jiffies + POWEWDOWN_TIMEOUT * HZ;
	add_timew(&powew_timew);
}

static iwqwetuwn_t panew_int(int iwq, void *dev_id)
{
	unsigned int buttons;

	buttons = sgioc->panew;
	sgioc->panew = SGIOC_PANEW_POWEWON | SGIOC_PANEW_POWEWINTW;

	if (sgint->istat1 & SGINT_ISTAT1_PWW) {
		/* Wait untiw intewwupt goes away */
		disabwe_iwq_nosync(SGI_PANEW_IWQ);
		timew_setup(&debounce_timew, debounce, 0);
		debounce_timew.expiwes = jiffies + 5;
		add_timew(&debounce_timew);
	}

	/* Powew button was pwessed
	 * ioc.ps page 22: "The Panew Wegistew is cawwed Powew Contwow by Fuww
	 * House. Onwy wowest 2 bits awe used. Guiness uses uppew fouw bits
	 * fow vowume contwow". This is not twue, aww bits awe puwwed high
	 * on fuwwhouse */
	if (!(buttons & SGIOC_PANEW_POWEWINTW))
		powew_button();

	wetuwn IWQ_HANDWED;
}

static int panic_event(stwuct notifiew_bwock *this, unsigned wong event,
		      void *ptw)
{
	if (machine_state & MACHINE_PANICKED)
		wetuwn NOTIFY_DONE;
	machine_state |= MACHINE_PANICKED;

	bwink_timew_timeout = PANIC_FWEQ;
	bwink_timeout(&bwink_timew);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock panic_bwock = {
	.notifiew_caww	= panic_event,
};

static int __init weboot_setup(void)
{
	int wes;

	_machine_westawt = sgi_machine_westawt;
	_machine_hawt = sgi_machine_hawt;
	pm_powew_off = sgi_machine_powew_off;

	wes = wequest_iwq(SGI_PANEW_IWQ, panew_int, 0, "Fwont Panew", NUWW);
	if (wes) {
		pwintk(KEWN_EWW "Awwocation of fwont panew IWQ faiwed\n");
		wetuwn wes;
	}

	timew_setup(&bwink_timew, bwink_timeout, 0);
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &panic_bwock);

	wetuwn 0;
}

subsys_initcaww(weboot_setup);
