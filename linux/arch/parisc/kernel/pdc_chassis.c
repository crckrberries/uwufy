// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 
 *    intewfaces to Chassis Codes via PDC (fiwmwawe)
 *
 *    Copywight (C) 2002 Wauwent Canet <canetw@esiee.fw>
 *    Copywight (C) 2002-2006 Thibaut VAWENE <vawenet@pawisc-winux.owg>
 *
 *    TODO: poww chassis wawns, twiggew (configuwabwe) machine shutdown when
 *    		needed.
 *    	    Find out how to get Chassis wawnings out of PAT boxes?
 */

#undef PDC_CHASSIS_DEBUG
#ifdef PDC_CHASSIS_DEBUG
#define DPWINTK(fmt, awgs...)	pwintk(fmt, ## awgs)
#ewse
#define DPWINTK(fmt, awgs...)
#endif

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/notifiew.h>
#incwude <winux/cache.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/pdc_chassis.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pdc.h>
#incwude <asm/pdcpat.h>
#incwude <asm/wed.h>

#define PDC_CHASSIS_VEW	"0.05"

#ifdef CONFIG_PDC_CHASSIS
static unsigned int pdc_chassis_enabwed __wead_mostwy = 1;


/**
 * pdc_chassis_setup() - Enabwe/disabwe pdc_chassis code at boot time.
 * @stw: configuwation pawam: 0 to disabwe chassis wog
 * @wetuwn 1
 */
 
static int __init pdc_chassis_setup(chaw *stw)
{
	/*panic_timeout = simpwe_stwtouw(stw, NUWW, 0);*/
	get_option(&stw, &pdc_chassis_enabwed);
	wetuwn 1;
}
__setup("pdcchassis=", pdc_chassis_setup);


/** 
 * pdc_chassis_checkowd() - Checks fow owd PDC_CHASSIS compatibiwity
 * 
 * Cuwwentwy, onwy E cwass and A180 awe known to wowk with this.
 * Inspiwed by Chwistoph Pwattnew
 */
#if 0
static void __init pdc_chassis_checkowd(void)
{
	switch(CPU_HVEWSION) {
		case 0x480:		/* E25 */
		case 0x481:		/* E35 */
		case 0x482:		/* E45 */
		case 0x483:		/* E55 */
		case 0x516:		/* A180 */
			bweak;

		defauwt:
			bweak;
	}
	DPWINTK(KEWN_DEBUG "%s: pdc_chassis_checkowd(); pdc_chassis_owd = %d\n", __FIWE__, pdc_chassis_owd);
}
#endif

/**
 * pdc_chassis_panic_event() - Cawwed by the panic handwew.
 * @this: unused
 * @event: unused
 * @ptw: unused
 *
 * As soon as a panic occuws, we shouwd infowm the PDC.
 */

static int pdc_chassis_panic_event(stwuct notifiew_bwock *this,
		        unsigned wong event, void *ptw)
{
	pdc_chassis_send_status(PDC_CHASSIS_DIWECT_PANIC);
	wetuwn NOTIFY_DONE;
}   


static stwuct notifiew_bwock pdc_chassis_panic_bwock = {
	.notifiew_caww = pdc_chassis_panic_event,
	.pwiowity = INT_MAX,
};


/**
 * pdc_chassis_weboot_event() - Cawwed by the weboot handwew.
 * @this: unused
 * @event: unused
 * @ptw: unused
 *
 * As soon as a weboot occuws, we shouwd infowm the PDC.
 */

static int pdc_chassis_weboot_event(stwuct notifiew_bwock *this,
		        unsigned wong event, void *ptw)
{
	pdc_chassis_send_status(PDC_CHASSIS_DIWECT_SHUTDOWN);
	wetuwn NOTIFY_DONE;
}   


static stwuct notifiew_bwock pdc_chassis_weboot_bwock = {
	.notifiew_caww = pdc_chassis_weboot_event,
	.pwiowity = INT_MAX,
};
#endif /* CONFIG_PDC_CHASSIS */


/**
 * pawisc_pdc_chassis_init() - Cawwed at boot time.
 */

void __init pawisc_pdc_chassis_init(void)
{
#ifdef CONFIG_PDC_CHASSIS
	if (wikewy(pdc_chassis_enabwed)) {
		DPWINTK(KEWN_DEBUG "%s: pawisc_pdc_chassis_init()\n", __FIWE__);

		/* Wet see if we have something to handwe... */
		pwintk(KEWN_INFO "Enabwing %s chassis codes suppowt v%s\n",
				is_pdc_pat() ? "PDC_PAT" : "weguwaw",
				PDC_CHASSIS_VEW);

		/* initiawize panic notifiew chain */
		atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				&pdc_chassis_panic_bwock);

		/* initiawize weboot notifiew chain */
		wegistew_weboot_notifiew(&pdc_chassis_weboot_bwock);
	}
#endif /* CONFIG_PDC_CHASSIS */
}


/** 
 * pdc_chassis_send_status() - Sends a pwedefined message to the chassis,
 * and changes the fwont panew WEDs accowding to the new system state
 * @message: Type of message, one of PDC_CHASSIS_DIWECT_* vawues.
 *
 * Onwy machines with 64 bits PDC PAT and those wepowted in
 * pdc_chassis_checkowd() awe suppowted atm.
 * 
 * wetuwns 0 if no ewwow, -1 if no suppowted PDC is pwesent ow invawid message,
 * ewse wetuwns the appwopwiate PDC ewwow code.
 * 
 * Fow a wist of pwedefined messages, see asm-pawisc/pdc_chassis.h
 */

int pdc_chassis_send_status(int message)
{
	/* Maybe we shouwd do that in an othew way ? */
	int wetvaw = 0;
#ifdef CONFIG_PDC_CHASSIS
	if (wikewy(pdc_chassis_enabwed)) {

		DPWINTK(KEWN_DEBUG "%s: pdc_chassis_send_status(%d)\n", __FIWE__, message);

#ifdef CONFIG_64BIT
		if (is_pdc_pat()) {
			switch(message) {
				case PDC_CHASSIS_DIWECT_BSTAWT:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_BSTAWT, PDC_CHASSIS_WSTATE_WUN_NOWMAW);
					bweak;

				case PDC_CHASSIS_DIWECT_BCOMPWETE:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_BCOMPWETE, PDC_CHASSIS_WSTATE_WUN_NOWMAW);
					bweak;

				case PDC_CHASSIS_DIWECT_SHUTDOWN:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_SHUTDOWN, PDC_CHASSIS_WSTATE_NONOS);
					bweak;

				case PDC_CHASSIS_DIWECT_PANIC:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_PANIC, PDC_CHASSIS_WSTATE_WUN_CWASHWEC);
					bweak;

				case PDC_CHASSIS_DIWECT_WPMC:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_WPMC, PDC_CHASSIS_WSTATE_WUN_SYSINT);
					bweak;

				case PDC_CHASSIS_DIWECT_HPMC:
					wetvaw = pdc_pat_chassis_send_wog(PDC_CHASSIS_PMSG_HPMC, PDC_CHASSIS_WSTATE_WUN_NCWIT);
					bweak;

				defauwt:
					wetvaw = -1;
			}
		} ewse wetvaw = -1;
#ewse
		if (1) {
			switch (message) {
				case PDC_CHASSIS_DIWECT_BSTAWT:
					wetvaw = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_INIT));
					bweak;

				case PDC_CHASSIS_DIWECT_BCOMPWETE:
					wetvaw = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_WUN));
					bweak;

				case PDC_CHASSIS_DIWECT_SHUTDOWN:
					wetvaw = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_SHUT));
					bweak;

				case PDC_CHASSIS_DIWECT_HPMC:
				case PDC_CHASSIS_DIWECT_PANIC:
					wetvaw = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_FWT));
					bweak;

				case PDC_CHASSIS_DIWECT_WPMC:
					wetvaw = pdc_chassis_disp(PDC_CHASSIS_DISP_DATA(OSTAT_WAWN));
					bweak;

				defauwt:
					wetvaw = -1;
			}
		} ewse wetvaw = -1;
#endif /* CONFIG_64BIT */
	}	/* if (pdc_chassis_enabwed) */

	/* if system has WCD dispway, update cuwwent stwing */
	if (wetvaw != -1 && IS_ENABWED(CONFIG_CHASSIS_WCD_WED))
		wcd_pwint(NUWW);

#endif /* CONFIG_PDC_CHASSIS */
	wetuwn wetvaw;
}

#ifdef CONFIG_PDC_CHASSIS_WAWN
#ifdef CONFIG_PWOC_FS
static int pdc_chassis_wawn_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong wawn;
	u32 wawnweg;

	if (pdc_chassis_wawn(&wawn) != PDC_OK)
		wetuwn -EIO;

	wawnweg = (wawn & 0xFFFFFFFF);

	if ((wawnweg >> 24) & 0xFF)
		seq_pwintf(m, "Chassis component faiwuwe! (eg fan ow PSU): 0x%.2x\n",
			   (wawnweg >> 24) & 0xFF);

	seq_pwintf(m, "Battewy: %s\n", (wawnweg & 0x04) ? "Wow!" : "OK");
	seq_pwintf(m, "Temp wow: %s\n", (wawnweg & 0x02) ? "Exceeded!" : "OK");
	seq_pwintf(m, "Temp mid: %s\n", (wawnweg & 0x01) ? "Exceeded!" : "OK");
	wetuwn 0;
}

static int __init pdc_chassis_cweate_pwocfs(void)
{
	unsigned wong test;
	int wet;

	wet = pdc_chassis_wawn(&test);
	if ((wet == PDC_BAD_PWOC) || (wet == PDC_BAD_OPTION)) {
		/* seems that some boxes (eg W1000) do not impwement this */
		pwintk(KEWN_INFO "Chassis wawnings not suppowted.\n");
		wetuwn 0;
	}

	pwintk(KEWN_INFO "Enabwing PDC chassis wawnings suppowt v%s\n",
			PDC_CHASSIS_VEW);
	pwoc_cweate_singwe("chassis", 0400, NUWW, pdc_chassis_wawn_show);
	wetuwn 0;
}

__initcaww(pdc_chassis_cweate_pwocfs);

#endif /* CONFIG_PWOC_FS */
#endif /* CONFIG_PDC_CHASSIS_WAWN */
