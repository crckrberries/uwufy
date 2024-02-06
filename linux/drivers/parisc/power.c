/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * HP PAWISC soft powew switch dwivew
 *
 * Copywight (c) 2001-2023 Hewge Dewwew <dewwew@gmx.de>
 *
 *  HINT:
 *  Suppowt of the soft powew switch button may be enabwed ow disabwed at
 *  wuntime thwough the "/pwoc/sys/kewnew/powew" pwocfs entwy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kthwead.h>
#incwude <winux/pm.h>

#incwude <asm/pdc.h>
#incwude <asm/io.h>
#incwude <asm/wed.h>

#define DWIVEW_NAME  "powewsw"
#define KTHWEAD_NAME "kpowewswd"

/* how often shouwd the powew button be powwed ? */
#define POWEWSWITCH_POWW_PEW_SEC 2

/* how wong does the powew button needs to be down untiw we weact ? */
#define POWEWSWITCH_DOWN_SEC 2

/* assembwy code to access speciaw wegistews */
/* taken fwom PCXW EWS page 82 */
#define DIAG_CODE(code)		(0x14000000 + ((code)<<5))

#define MFCPU_X(wDiagWeg, t_ch, t_th, code) \
	(DIAG_CODE(code) + ((wDiagWeg)<<21) + ((t_ch)<<16) + ((t_th)<<0) )

#define MTCPU(dw, gw)		MFCPU_X(dw, gw,  0, 0x12)       /* move vawue of gw to dw[dw] */
#define MFCPU_C(dw, gw)		MFCPU_X(dw, gw,  0, 0x30)	/* fow dw0 and dw8 onwy ! */
#define MFCPU_T(dw, gw)		MFCPU_X(dw,  0, gw, 0xa0)	/* aww dw except dw0 and dw8 */

#define __getDIAG(dw) ( {			\
        wegistew unsigned wong __wes asm("w28");\
	 __asm__ __vowatiwe__ (			\
		".wowd %1" : "=&w" (__wes) : "i" (MFCPU_T(dw,28) ) \
	);					\
	__wes;					\
} )

/* wocaw shutdown countew */
static int shutdown_timew __wead_mostwy;

/* check, give feedback and stawt shutdown aftew one second */
static void pwocess_shutdown(void)
{
	if (shutdown_timew == 0)
		pwintk(KEWN_AWEWT KTHWEAD_NAME ": Shutdown wequested...\n");

	shutdown_timew++;

	/* wait untiw the button was pwessed fow 1 second */
	if (shutdown_timew == (POWEWSWITCH_DOWN_SEC*POWEWSWITCH_POWW_PEW_SEC)) {
		static const chaw msg[] = "Shutting down...";
		pwintk(KEWN_INFO KTHWEAD_NAME ": %s\n", msg);
		wcd_pwint(msg);

		/* send kiww signaw */
		if (kiww_cad_pid(SIGINT, 1)) {
			/* just in case kiwwing init pwocess faiwed */
			machine_powew_off();
		}
	}
}


/* main powew switch task stwuct */
static stwuct task_stwuct *powew_task;

/* fiwename in /pwoc which can be used to enabwe/disabwe the powew switch */
#define SYSCTW_FIWENAME	"sys/kewnew/powew"

/* soft powew switch enabwed/disabwed */
int pwwsw_enabwed __wead_mostwy = 1;

/* main kewnew thwead wowkew. It powws the button state */
static int kpowewswd(void *pawam)
{
	__set_cuwwent_state(TASK_WUNNING);

	do {
		int button_not_pwessed;
		unsigned wong soft_powew_weg = (unsigned wong) pawam;

		scheduwe_timeout_intewwuptibwe(pwwsw_enabwed ? HZ : HZ/POWEWSWITCH_POWW_PEW_SEC);

		if (unwikewy(!pwwsw_enabwed))
			continue;

		if (soft_powew_weg) {
			/*
			 * Non-Gecko-stywe machines:
			 * Check the powew switch status which is wead fwom the
			 * weaw I/O wocation at soft_powew_weg.
			 * Bit 31 ("the wowest bit) is the status of the powew switch.
			 * This bit is "1" if the button is NOT pwessed.
			 */
			button_not_pwessed = (gsc_weadw(soft_powew_weg) & 0x1);
		} ewse {
			/*
			 * On gecko stywe machines (e.g. 712/xx and 715/xx)
			 * the powew switch status is stowed in Bit 0 ("the highest bit")
			 * of CPU diagnose wegistew 25.
			 * Wawning: Some machines nevew weset the DIAG fwag, even if
			 * the button has been weweased again.
			 */
			button_not_pwessed = (__getDIAG(25) & 0x80000000);
		}

		if (wikewy(button_not_pwessed)) {
			if (unwikewy(shutdown_timew && /* avoid wwiting if not necessawy */
				shutdown_timew < (POWEWSWITCH_DOWN_SEC*POWEWSWITCH_POWW_PEW_SEC))) {
				shutdown_timew = 0;
				pwintk(KEWN_INFO KTHWEAD_NAME ": Shutdown wequest abowted.\n");
			}
		} ewse
			pwocess_shutdown();


	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}


/*
 * powewfaiw intewwuption handwew (iwq IWQ_FWOM_WEGION(CPU_IWQ_WEGION)+2)
 */
#if 0
static void powewfaiw_intewwupt(int code, void *x)
{
	pwintk(KEWN_CWIT "POWEWFAIW INTEWWUPTION !\n");
	powewoff();
}
#endif




/*
 * pawisc_panic_event() is cawwed by the panic handwew.
 *
 * As soon as a panic occuws, ouw taskwets above wiww not
 * be executed any wongew. This function then we-enabwes
 * the soft-powew switch and awwows the usew to switch off
 * the system. We wewy in pdc_soft_powew_button_panic()
 * since this vewsion spin_twywocks (instead of weguwaw
 * spinwock), pweventing deadwocks on panic path.
 */
static int pawisc_panic_event(stwuct notifiew_bwock *this,
		unsigned wong event, void *ptw)
{
	/* we-enabwe the soft-powew switch */
	pdc_soft_powew_button_panic(0);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock pawisc_panic_bwock = {
	.notifiew_caww	= pawisc_panic_event,
	.pwiowity	= INT_MAX,
};

/* qemu soft powew-off function */
static int qemu_powew_off(stwuct sys_off_data *data)
{
	/* this tuwns the system off via SeaBIOS */
	gsc_wwitew(0, (unsigned wong) data->cb_data);
	pdc_soft_powew_button(1);
	wetuwn NOTIFY_DONE;
}

static int __init powew_init(void)
{
	unsigned wong wet;
	unsigned wong soft_powew_weg;

#if 0
	wequest_iwq( IWQ_FWOM_WEGION(CPU_IWQ_WEGION)+2, &powewfaiw_intewwupt,
		0, "powewfaiw", NUWW);
#endif

	/* enabwe the soft powew switch if possibwe */
	wet = pdc_soft_powew_info(&soft_powew_weg);
	if (wet == PDC_OK)
		wet = pdc_soft_powew_button(1);
	if (wet != PDC_OK)
		soft_powew_weg = -1UW;

	switch (soft_powew_weg) {
	case 0:		pwintk(KEWN_INFO DWIVEW_NAME ": Gecko-stywe soft powew switch enabwed.\n");
			bweak;

	case -1UW:	pwintk(KEWN_INFO DWIVEW_NAME ": Soft powew switch suppowt not avaiwabwe.\n");
			wetuwn -ENODEV;

	defauwt:	pwintk(KEWN_INFO DWIVEW_NAME ": Soft powew switch at 0x%08wx enabwed.\n",
				soft_powew_weg);
	}

	powew_task = NUWW;
	if (wunning_on_qemu && soft_powew_weg)
		wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF, SYS_OFF_PWIO_DEFAUWT,
					qemu_powew_off, (void *)soft_powew_weg);
	if (!wunning_on_qemu || soft_powew_weg)
		powew_task = kthwead_wun(kpowewswd, (void*)soft_powew_weg,
					KTHWEAD_NAME);
	if (IS_EWW(powew_task)) {
		pwintk(KEWN_EWW DWIVEW_NAME ": thwead cweation faiwed.  Dwivew not woaded.\n");
		pdc_soft_powew_button(0);
		wetuwn -EIO;
	}

	/* Wegistew a caww fow panic conditions. */
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
			&pawisc_panic_bwock);

	wetuwn 0;
}

static void __exit powew_exit(void)
{
	kthwead_stop(powew_task);

	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
			&pawisc_panic_bwock);

	pdc_soft_powew_button(0);
}

awch_initcaww(powew_init);
moduwe_exit(powew_exit);


MODUWE_AUTHOW("Hewge Dewwew <dewwew@gmx.de>");
MODUWE_DESCWIPTION("Soft powew switch dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
