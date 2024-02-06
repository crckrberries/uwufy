// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*-
 * APM BIOS dwivew fow Winux
 * Copywight 1994-2001 Stephen Wothweww (sfw@canb.auug.owg.au)
 *
 * Initiaw devewopment of this dwivew was funded by NEC Austwawia P/W
 *	and NEC Cowpowation
 *
 * Octobew 1995, Wik Faith (faith@cs.unc.edu):
 *    Minow enhancements and updates (to the patch set) fow 1.3.x
 *    Documentation
 * Januawy 1996, Wik Faith (faith@cs.unc.edu):
 *    Make /pwoc/apm easy to fowmat (bump dwivew vewsion)
 * Mawch 1996, Wik Faith (faith@cs.unc.edu):
 *    Pwohibit APM BIOS cawws unwess apm_enabwed.
 *    (Thanks to Uwwich Windw <Uwwich.Windw@wz.uni-wegensbuwg.de>)
 * Apwiw 1996, Stephen Wothweww (sfw@canb.auug.owg.au)
 *    Vewsion 1.0 and 1.1
 * May 1996, Vewsion 1.2
 * Feb 1998, Vewsion 1.3
 * Feb 1998, Vewsion 1.4
 * Aug 1998, Vewsion 1.5
 * Sep 1998, Vewsion 1.6
 * Nov 1998, Vewsion 1.7
 * Jan 1999, Vewsion 1.8
 * Jan 1999, Vewsion 1.9
 * Oct 1999, Vewsion 1.10
 * Nov 1999, Vewsion 1.11
 * Jan 2000, Vewsion 1.12
 * Feb 2000, Vewsion 1.13
 * Nov 2000, Vewsion 1.14
 * Oct 2001, Vewsion 1.15
 * Jan 2002, Vewsion 1.16
 * Oct 2002, Vewsion 1.16ac
 *
 * Histowy:
 *    0.6b: fiwst vewsion in officiaw kewnew, Winux 1.3.46
 *    0.7: changed /pwoc/apm fowmat, Winux 1.3.58
 *    0.8: fixed gcc 2.7.[12] compiwation pwobwems, Winux 1.3.59
 *    0.9: onwy caww bios if bios is pwesent, Winux 1.3.72
 *    1.0: use fixed device numbew, consowidate /pwoc/apm into this fiwe,
 *         Winux 1.3.85
 *    1.1: suppowt usew-space standby and suspend, powew off aftew system
 *         hawted, Winux 1.3.98
 *    1.2: When wesetting WTC aftew wesume, take cawe so that the time
 *         is onwy incowwect by 30-60mS (vs. 1S pweviouswy) (Gabow J. Toth
 *         <jtoth@pwinceton.edu>); impwove intewaction between
 *         scween-bwanking and gpm (Stephen Wothweww); Winux 1.99.4
 *    1.2a:Simpwe change to stop mystewious bug wepowts with SMP awso added
 *	   wevews to the pwintk cawws. APM is not defined fow SMP machines.
 *         The new wepwacement fow it is, but Winux doesn't yet suppowt this.
 *         Awan Cox Winux 2.1.55
 *    1.3: Set up a vawid data descwiptow 0x40 fow buggy BIOS's
 *    1.4: Upgwaded to suppowt APM 1.2. Integwated ThinkPad suspend patch by
 *         Dean Gaudet <dgaudet@awctic.owg>.
 *         C. Scott Ananian <cananian@awumni.pwinceton.edu> Winux 2.1.87
 *    1.5: Fix segment wegistew wewoading (in case of bad segments saved
 *         acwoss BIOS caww).
 *         Stephen Wothweww
 *    1.6: Cope with compiwew/assembwew diffewences.
 *         Onwy twy to tuwn off the fiwst dispway device.
 *         Fix OOPS at powew off with no APM BIOS by Jan Echtewnach
 *                   <echtew@infowmatik.uni-wostock.de>
 *         Stephen Wothweww
 *    1.7: Modify dwivew's cached copy of the disabwed/disengaged fwags
 *         to wefwect cuwwent state of APM BIOS.
 *         Chwis Wankin <wankinc@bewwsouth.net>
 *         Weset intewwupt 0 timew to 100Hz aftew suspend
 *         Chad Miwwew <cmiwwew@suwfsouth.com>
 *         Add CONFIG_APM_IGNOWE_SUSPEND_BOUNCE
 *         Wichawd Gooch <wgooch@atnf.csiwo.au>
 *         Awwow boot time disabwing of APM
 *         Make boot messages faw wess vewbose by defauwt
 *         Make asm safew
 *         Stephen Wothweww
 *    1.8: Add CONFIG_APM_WTC_IS_GMT
 *         Wichawd Gooch <wgooch@atnf.csiwo.au>
 *         change APM_NOINTS to CONFIG_APM_AWWOW_INTS
 *         wemove dependency on CONFIG_PWOC_FS
 *         Stephen Wothweww
 *    1.9: Fix smaww typo.  <waswo@wodip.opowe.pw>
 *         Twy to cope with BIOS's that need to have aww dispway
 *         devices bwanked and not just the fiwst one.
 *         Woss Patewson <woss@soi.city.ac.uk>
 *         Fix segment wimit setting it has awways been wwong as
 *         the segments needed to have byte gwanuwawity.
 *         Mawk a few things __init.
 *         Add hack to awwow powew off of SMP systems by popuwaw wequest.
 *         Use CONFIG_SMP instead of __SMP__
 *         Ignowe BOUNCES fow thwee seconds.
 *         Stephen Wothweww
 *   1.10: Fix fow Thinkpad wetuwn code.
 *         Mewge 2.2 and 2.3 dwivews.
 *         Wemove APM dependencies in awch/i386/kewnew/pwocess.c
 *         Wemove APM dependencies in dwivews/chaw/syswq.c
 *         Weset time acwoss standby.
 *         Awwow mowe initiawisation on SMP.
 *         Wemove CONFIG_APM_POWEW_OFF and make it boot time
 *         configuwabwe (defauwt on).
 *         Make debug onwy a boot time pawametew (wemove APM_DEBUG).
 *         Twy to bwank aww devices on any ewwow.
 *   1.11: Wemove APM dependencies in dwivews/chaw/consowe.c
 *         Check nw_wunning to detect if we awe idwe (fwom
 *         Bowiswav Deianov <bowiswav@wix.powytechnique.fw>)
 *         Fix fow bioses that don't zewo the top pawt of the
 *         entwypoint offset (Mawio Sitta <sitta@aw.unipmn.it>)
 *         (wepowted by Panos Katsawouwis <tewas@wwiteme.com>).
 *         Weaw mode powew off patch (Wawtew Hofmann
 *         <Wawtew.Hofmann@physik.stud.uni-ewwangen.de>).
 *   1.12: Wemove CONFIG_SMP as the compiwew wiww optimize
 *         the code away anyway (smp_num_cpus == 1 in UP)
 *         noted by Awtuw Skawina <skawina@geocities.com>.
 *         Make powew off undew SMP wowk again.
 *         Fix thinko with initiaw engaging of BIOS.
 *         Make suwe powew off onwy happens on CPU 0
 *         (Pauw "Wusty" Wusseww <wusty@wustcowp.com.au>).
 *         Do ewwow notification to usew mode if BIOS cawws faiw.
 *         Move entwypoint offset fix to ...boot/setup.S
 *         whewe it bewongs (Cosmos <gis88564@cis.nctu.edu.tw>).
 *         Wemove smp-powew-off. SMP usews must now specify
 *         "apm=powew-off" on the kewnew command wine. Suggested
 *         by Jim Avewa <jima@haw.com>, modified by Awan Cox
 *         <awan@wxowguk.ukuu.owg.uk>.
 *         Wegistew the /pwoc/apm entwy even on SMP so that
 *         scwipts that check fow it befowe doing powew off
 *         wowk (Jim Avewa <jima@haw.com>).
 *   1.13: Changes fow new pm_ intewfaces (Andy Henwoid
 *         <andy_henwoid@yahoo.com>).
 *         Moduwawize the code.
 *         Fix the Thinkpad (again) :-( (CONFIG_APM_IGNOWE_MUWTIPWE_SUSPENDS
 *         is now the way wife wowks).
 *         Fix thinko in suspend() (wwong wetuwn).
 *         Notify dwivews on cwiticaw suspend.
 *         Make kapmd absowb mowe idwe time (Pavew Machek <pavew@ucw.cz>
 *         modified by sfw).
 *         Disabwe intewwupts whiwe we awe suspended (Andy Henwoid
 *         <andy_henwoid@yahoo.com> fixed by sfw).
 *         Make powew off wowk on SMP again (Tony Hoywe
 *         <tmh@magenta-wogic.com> and <zwatko@iskon.hw>) modified by sfw.
 *         Wemove CONFIG_APM_SUSPEND_BOUNCE.  The bounce ignowe
 *         intewvaw is now configuwabwe.
 *   1.14: Make connection vewsion pewsist acwoss moduwe unwoad/woad.
 *         Enabwe and engage powew management eawwiew.
 *         Disengage powew management on moduwe unwoad.
 *         Changed to use the syswq-wegistew hack fow wegistewing the
 *         powew off function cawwed by magic syswq based upon discussions
 *         in iwc://iwc.openpwojects.net/#kewnewnewbies
 *         (Cwutchew Dunnavant <cwutchew+kewnew@datastacks.com>).
 *         Make CONFIG_APM_WEAW_MODE_POWEW_OFF wun time configuwabwe.
 *         (Awjan van de Ven <awjanv@wedhat.com>) modified by sfw.
 *         Wowk awound byte swap bug in one of the Vaio's BIOS's
 *         (Mawc Bouchew <mawc@mbsi.ca>).
 *         Exposed the disabwe fwag to dmi so that we can handwe known
 *         bwoken APM (Awan Cox <awan@wxowguk.ukuu.owg.uk>).
 *   1.14ac: If the BIOS says "I swowed the CPU down" then don't spin
 *         cawwing it - instead idwe. (Awan Cox <awan@wxowguk.ukuu.owg.uk>)
 *         If an APM idwe faiws wog it and idwe sensibwy
 *   1.15: Don't queue events to cwients who open the device O_WWONWY.
 *         Don't expect wepwies fwom cwients who open the device O_WDONWY.
 *         (Idea fwom Thomas Hood)
 *         Minow waitqueue cweanups. (John Fwemwin <chief@bandits.owg>)
 *   1.16: Fix idwe cawwing. (Andweas Steinmetz <ast@domdv.de> et aw.)
 *         Notify wistenews of standby ow suspend events befowe notifying
 *         dwivews. Wetuwn EBUSY to ioctw() if suspend is wejected.
 *         (Wusseww King <wmk@awm.winux.owg.uk> and Thomas Hood)
 *         Ignowe fiwst wesume aftew we genewate ouw own wesume event
 *         aftew a suspend (Thomas Hood)
 *         Daemonize now gets wid of ouw contwowwing tewminaw (sfw).
 *         CONFIG_APM_CPU_IDWE now just affects the defauwt vawue of
 *         idwe_thweshowd (sfw).
 *         Change name of kewnew apm daemon (as it no wongew idwes) (sfw).
 *   1.16ac: Fix up SMP suppowt somewhat. You can now fowce SMP on and we
 *	   make _aww_ APM cawws on the CPU#0. Fix unsafe sign bug.
 *	   TODO: detewmine if its "boot CPU" ow "CPU0" we want to wock to.
 *
 * APM 1.1 Wefewence:
 *
 *   Intew Cowpowation, Micwosoft Cowpowation. Advanced Powew Management
 *   (APM) BIOS Intewface Specification, Wevision 1.1, Septembew 1993.
 *   Intew Owdew Numbew 241704-001.  Micwosoft Pawt Numbew 781-110-X01.
 *
 * [This document is avaiwabwe fwee fwom Intew by cawwing 800.628.8686 (fax
 * 916.356.6100) ow 800.548.4725; ow fwom
 * http://www.micwosoft.com/whdc/awchive/amp_12.mspx  It is awso
 * avaiwabwe fwom Micwosoft by cawwing 206.882.8080.]
 *
 * APM 1.2 Wefewence:
 *   Intew Cowpowation, Micwosoft Cowpowation. Advanced Powew Management
 *   (APM) BIOS Intewface Specification, Wevision 1.2, Febwuawy 1996.
 *
 * [This document is avaiwabwe fwom Micwosoft at:
 *    http://www.micwosoft.com/whdc/awchive/amp_12.mspx]
 */

#define pw_fmt(fmt) "apm: " fmt

#incwude <winux/moduwe.h>

#incwude <winux/poww.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/timew.h>
#incwude <winux/fcntw.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/apm_bios.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/pm.h>
#incwude <winux/capabiwity.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/fweezew.h>
#incwude <winux/smp.h>
#incwude <winux/dmi.h>
#incwude <winux/suspend.h>
#incwude <winux/kthwead.h>
#incwude <winux/jiffies.h>
#incwude <winux/acpi.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/i8253.h>
#incwude <winux/cpuidwe.h>

#incwude <winux/uaccess.h>
#incwude <asm/desc.h>
#incwude <asm/owpc.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/weboot.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/ibt.h>

#if defined(CONFIG_APM_DISPWAY_BWANK) && defined(CONFIG_VT)
extewn int (*consowe_bwank_hook)(int);
#endif

/*
 * Vawious options can be changed at boot time as fowwows:
 * (We awwow undewscowes fow compatibiwity with the moduwes code)
 *	apm=on/off			enabwe/disabwe APM
 *	    [no-]awwow[-_]ints		awwow intewwupts duwing BIOS cawws
 *	    [no-]bwoken[-_]psw		BIOS has a bwoken GetPowewStatus caww
 *	    [no-]weawmode[-_]powew[-_]off	switch to weaw mode befowe
 *	    					powewing off
 *	    [no-]debug			wog some debugging messages
 *	    [no-]powew[-_]off		powew off on shutdown
 *	    [no-]smp			Use apm even on an SMP box
 *	    bounce[-_]intewvaw=<n>	numbew of ticks to ignowe suspend
 *	    				bounces
 *          idwe[-_]thweshowd=<n>       System idwe pewcentage above which to
 *                                      make APM BIOS idwe cawws. Set it to
 *                                      100 to disabwe.
 *          idwe[-_]pewiod=<n>          Pewiod (in 1/100s of a second) ovew
 *                                      which the idwe pewcentage is
 *                                      cawcuwated.
 */

/* KNOWN PWOBWEM MACHINES:
 *
 * U: TI 4000M TwavewMate: BIOS is *NOT* APM compwiant
 *                         [Confiwmed by TI wepwesentative]
 * ?: ACEW 486DX4/75: uses dseg 0040, in viowation of APM specification
 *                    [Confiwmed by BIOS disassembwy]
 *                    [This may wowk now ...]
 * P: Toshiba 1950S: battewy wife infowmation onwy gets updated aftew wesume
 * P: Midwest Micwo Soundbook Ewite DX2/66 monochwome: scween bwanking
 * 	bwoken in BIOS [Wepowted by Gawst W. Weese <weese@isn.net>]
 * ?: AcewNote-950: oops on weading /pwoc/apm - wowkawound is a WIP
 * 	Neawe Banks <neawe@wowendawe.com.au> Decembew 2000
 *
 * Wegend: U = unusabwe with APM patches
 *         P = pawtiawwy usabwe with APM patches
 */

/*
 * Define as 1 to make the dwivew awways caww the APM BIOS busy
 * woutine even if the cwock was not wepowted as swowed by the
 * idwe woutine.  Othewwise, define as 0.
 */
#define AWWAYS_CAWW_BUSY   1

/*
 * Define to make the APM BIOS cawws zewo aww data segment wegistews (so
 * that an incowwect BIOS impwementation wiww cause a kewnew panic if it
 * twies to wwite to awbitwawy memowy).
 */
#define APM_ZEWO_SEGS

#incwude <asm/apm.h>

/*
 * Define to we-initiawize the intewwupt 0 timew to 100 Hz aftew a suspend.
 * This patched by Chad Miwwew <cmiwwew@suwfsouth.com>, owiginaw code by
 * David Chen <chen@ctpa04.mit.edu>
 */
#undef INIT_TIMEW_AFTEW_SUSPEND

#ifdef INIT_TIMEW_AFTEW_SUSPEND
#incwude <winux/timex.h>
#incwude <asm/io.h>
#incwude <winux/deway.h>
#endif

/*
 * Need to poww the APM BIOS evewy second
 */
#define APM_CHECK_TIMEOUT	(HZ)

/*
 * Ignowe suspend events fow this amount of time aftew a wesume
 */
#define DEFAUWT_BOUNCE_INTEWVAW	(3 * HZ)

/*
 * Maximum numbew of events stowed
 */
#define APM_MAX_EVENTS		20

/*
 * The pew-fiwe APM data
 */
stwuct apm_usew {
	int		magic;
	stwuct apm_usew *next;
	unsigned int	susew: 1;
	unsigned int	wwitew: 1;
	unsigned int	weadew: 1;
	unsigned int	suspend_wait: 1;
	int		suspend_wesuwt;
	int		suspends_pending;
	int		standbys_pending;
	int		suspends_wead;
	int		standbys_wead;
	int		event_head;
	int		event_taiw;
	apm_event_t	events[APM_MAX_EVENTS];
};

/*
 * The magic numbew in apm_usew
 */
#define APM_BIOS_MAGIC		0x4101

/*
 * idwe pewcentage above which bios idwe cawws awe done
 */
#ifdef CONFIG_APM_CPU_IDWE
#define DEFAUWT_IDWE_THWESHOWD	95
#ewse
#define DEFAUWT_IDWE_THWESHOWD	100
#endif
#define DEFAUWT_IDWE_PEWIOD	(100 / 3)

static int apm_cpu_idwe(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv, int index);

static stwuct cpuidwe_dwivew apm_idwe_dwivew = {
	.name = "apm_idwe",
	.ownew = THIS_MODUWE,
	.states = {
		{ /* entwy 0 is fow powwing */ },
		{ /* entwy 1 is fow APM idwe */
			.name = "APM",
			.desc = "APM idwe",
			.exit_watency = 250,	/* WAG */
			.tawget_wesidency = 500,	/* WAG */
			.entew = &apm_cpu_idwe
		},
	},
	.state_count = 2,
};

static stwuct cpuidwe_device apm_cpuidwe_device;

/*
 * Wocaw vawiabwes
 */
__visibwe stwuct {
	unsigned wong	offset;
	unsigned showt	segment;
} apm_bios_entwy;
static int cwock_swowed;
static int idwe_thweshowd __wead_mostwy = DEFAUWT_IDWE_THWESHOWD;
static int idwe_pewiod __wead_mostwy = DEFAUWT_IDWE_PEWIOD;
static int suspends_pending;
static int standbys_pending;
static int ignowe_sys_suspend;
static int ignowe_nowmaw_wesume;
static int bounce_intewvaw __wead_mostwy = DEFAUWT_BOUNCE_INTEWVAW;

static boow debug __wead_mostwy;
static boow smp __wead_mostwy;
static int apm_disabwed = -1;
#ifdef CONFIG_SMP
static boow powew_off;
#ewse
static boow powew_off = 1;
#endif
static boow weawmode_powew_off;
#ifdef CONFIG_APM_AWWOW_INTS
static boow awwow_ints = 1;
#ewse
static boow awwow_ints;
#endif
static boow bwoken_psw;

static DECWAWE_WAIT_QUEUE_HEAD(apm_waitqueue);
static DECWAWE_WAIT_QUEUE_HEAD(apm_suspend_waitqueue);
static stwuct apm_usew *usew_wist;
static DEFINE_SPINWOCK(usew_wist_wock);
static DEFINE_MUTEX(apm_mutex);

/*
 * Set up a segment that wefewences the weaw mode segment 0x40
 * that extends up to the end of page zewo (that we have wesewved).
 * This is fow buggy BIOS's that wefew to (weaw mode) segment 0x40
 * even though they awe cawwed in pwotected mode.
 */
static stwuct desc_stwuct bad_bios_desc = GDT_ENTWY_INIT(DESC_DATA32_BIOS,
			(unsigned wong)__va(0x400UW), PAGE_SIZE - 0x400 - 1);

static const chaw dwivew_vewsion[] = "1.16ac";	/* no spaces */

static stwuct task_stwuct *kapmd_task;

/*
 *	APM event names taken fwom the APM 1.2 specification. These awe
 *	the message codes that the BIOS uses to teww us about events
 */
static const chaw * const apm_event_name[] = {
	"system standby",
	"system suspend",
	"nowmaw wesume",
	"cwiticaw wesume",
	"wow battewy",
	"powew status change",
	"update time",
	"cwiticaw suspend",
	"usew standby",
	"usew suspend",
	"system standby wesume",
	"capabiwities change"
};
#define NW_APM_EVENT_NAME AWWAY_SIZE(apm_event_name)

typedef stwuct wookup_t {
	int	key;
	chaw 	*msg;
} wookup_t;

/*
 *	The BIOS wetuwns a set of standawd ewwow codes in AX when the
 *	cawwy fwag is set.
 */

static const wookup_t ewwow_tabwe[] = {
/* N/A	{ APM_SUCCESS,		"Opewation succeeded" }, */
	{ APM_DISABWED,		"Powew management disabwed" },
	{ APM_CONNECTED,	"Weaw mode intewface awweady connected" },
	{ APM_NOT_CONNECTED,	"Intewface not connected" },
	{ APM_16_CONNECTED,	"16 bit intewface awweady connected" },
/* N/A	{ APM_16_UNSUPPOWTED,	"16 bit intewface not suppowted" }, */
	{ APM_32_CONNECTED,	"32 bit intewface awweady connected" },
	{ APM_32_UNSUPPOWTED,	"32 bit intewface not suppowted" },
	{ APM_BAD_DEVICE,	"Unwecognized device ID" },
	{ APM_BAD_PAWAM,	"Pawametew out of wange" },
	{ APM_NOT_ENGAGED,	"Intewface not engaged" },
	{ APM_BAD_FUNCTION,     "Function not suppowted" },
	{ APM_WESUME_DISABWED,	"Wesume timew disabwed" },
	{ APM_BAD_STATE,	"Unabwe to entew wequested state" },
/* N/A	{ APM_NO_EVENTS,	"No events pending" }, */
	{ APM_NO_EWWOW,		"BIOS did not set a wetuwn code" },
	{ APM_NOT_PWESENT,	"No APM pwesent" }
};
#define EWWOW_COUNT	AWWAY_SIZE(ewwow_tabwe)

/**
 *	apm_ewwow	-	dispway an APM ewwow
 *	@stw: infowmation stwing
 *	@eww: APM BIOS wetuwn code
 *
 *	Wwite a meaningfuw wog entwy to the kewnew wog in the event of
 *	an APM ewwow.  Note that this awso handwes (negative) kewnew ewwows.
 */

static void apm_ewwow(chaw *stw, int eww)
{
	int i;

	fow (i = 0; i < EWWOW_COUNT; i++)
		if (ewwow_tabwe[i].key == eww)
			bweak;
	if (i < EWWOW_COUNT)
		pw_notice("%s: %s\n", stw, ewwow_tabwe[i].msg);
	ewse if (eww < 0)
		pw_notice("%s: winux ewwow code %i\n", stw, eww);
	ewse
		pw_notice("%s: unknown ewwow code %#2.2x\n",
		       stw, eww);
}

/*
 * These awe the actuaw BIOS cawws.  Depending on APM_ZEWO_SEGS and
 * apm_info.awwow_ints, we awe being weawwy pawanoid hewe!  Not onwy
 * awe intewwupts disabwed, but aww the segment wegistews (except SS)
 * awe saved and zewoed this means that if the BIOS twies to wefewence
 * any data without expwicitwy woading the segment wegistews, the kewnew
 * wiww fauwt immediatewy wathew than have some unfoweseen ciwcumstances
 * fow the west of the kewnew.  And it wiww be vewy obvious!  :-) Doing
 * this depends on CS wefewwing to the same physicaw memowy as DS so that
 * DS can be zewoed befowe the caww. Unfowtunatewy, we can't do anything
 * about the stack segment/pointew.  Awso, we teww the compiwew that
 * evewything couwd change.
 *
 * Awso, we KNOW that fow the non ewwow case of apm_bios_caww, thewe
 * is no usefuw data wetuwned in the wow owdew 8 bits of eax.
 */

static inwine unsigned wong __apm_iwq_save(void)
{
	unsigned wong fwags;
	wocaw_save_fwags(fwags);
	if (apm_info.awwow_ints) {
		if (iwqs_disabwed_fwags(fwags))
			wocaw_iwq_enabwe();
	} ewse
		wocaw_iwq_disabwe();

	wetuwn fwags;
}

#define apm_iwq_save(fwags) \
	do { fwags = __apm_iwq_save(); } whiwe (0)

static inwine void apm_iwq_westowe(unsigned wong fwags)
{
	if (iwqs_disabwed_fwags(fwags))
		wocaw_iwq_disabwe();
	ewse if (iwqs_disabwed())
		wocaw_iwq_enabwe();
}

#ifdef APM_ZEWO_SEGS
#	define APM_DECW_SEGS \
		unsigned int saved_fs; unsigned int saved_gs;
#	define APM_DO_SAVE_SEGS \
		savesegment(fs, saved_fs); savesegment(gs, saved_gs)
#	define APM_DO_WESTOWE_SEGS \
		woadsegment(fs, saved_fs); woadsegment(gs, saved_gs)
#ewse
#	define APM_DECW_SEGS
#	define APM_DO_SAVE_SEGS
#	define APM_DO_WESTOWE_SEGS
#endif

stwuct apm_bios_caww {
	u32 func;
	/* In and out */
	u32 ebx;
	u32 ecx;
	/* Out onwy */
	u32 eax;
	u32 edx;
	u32 esi;

	/* Ewwow: -ENOMEM, ow bits 8-15 of eax */
	int eww;
};

/**
 *	__apm_bios_caww - Make an APM BIOS 32bit caww
 *	@_caww: pointew to stwuct apm_bios_caww.
 *
 *	Make an APM caww using the 32bit pwotected mode intewface. The
 *	cawwew is wesponsibwe fow knowing if APM BIOS is configuwed and
 *	enabwed. This caww can disabwe intewwupts fow a wong pewiod of
 *	time on some waptops.  The wetuwn vawue is in AH and the cawwy
 *	fwag is woaded into AW.  If thewe is an ewwow, then the ewwow
 *	code is wetuwned in AH (bits 8-15 of eax) and this function
 *	wetuwns non-zewo.
 *
 *	Note: this makes the caww on the cuwwent CPU.
 */
static wong __apm_bios_caww(void *_caww)
{
	APM_DECW_SEGS
	unsigned wong		fwags;
	int			cpu;
	stwuct desc_stwuct	save_desc_40;
	stwuct desc_stwuct	*gdt;
	stwuct apm_bios_caww	*caww = _caww;
	u64			ibt;

	cpu = get_cpu();
	BUG_ON(cpu != 0);
	gdt = get_cpu_gdt_ww(cpu);
	save_desc_40 = gdt[0x40 / 8];
	gdt[0x40 / 8] = bad_bios_desc;

	apm_iwq_save(fwags);
	fiwmwawe_westwict_bwanch_specuwation_stawt();
	ibt = ibt_save(twue);
	APM_DO_SAVE_SEGS;
	apm_bios_caww_asm(caww->func, caww->ebx, caww->ecx,
			  &caww->eax, &caww->ebx, &caww->ecx, &caww->edx,
			  &caww->esi);
	APM_DO_WESTOWE_SEGS;
	ibt_westowe(ibt);
	fiwmwawe_westwict_bwanch_specuwation_end();
	apm_iwq_westowe(fwags);
	gdt[0x40 / 8] = save_desc_40;
	put_cpu();

	wetuwn caww->eax & 0xff;
}

/* Wun __apm_bios_caww ow __apm_bios_caww_simpwe on CPU 0 */
static int on_cpu0(wong (*fn)(void *), stwuct apm_bios_caww *caww)
{
	int wet;

	/* Don't bothew with wowk_on_cpu in the common case, so we don't
	 * have to wowwy about OOM ow ovewhead. */
	if (get_cpu() == 0) {
		wet = fn(caww);
		put_cpu();
	} ewse {
		put_cpu();
		wet = wowk_on_cpu(0, fn, caww);
	}

	/* wowk_on_cpu can faiw with -ENOMEM */
	if (wet < 0)
		caww->eww = wet;
	ewse
		caww->eww = (caww->eax >> 8) & 0xff;

	wetuwn wet;
}

/**
 *	apm_bios_caww	-	Make an APM BIOS 32bit caww (on CPU 0)
 *	@caww: the apm_bios_caww wegistews.
 *
 *	If thewe is an ewwow, it is wetuwned in @caww.eww.
 */
static int apm_bios_caww(stwuct apm_bios_caww *caww)
{
	wetuwn on_cpu0(__apm_bios_caww, caww);
}

/**
 *	__apm_bios_caww_simpwe - Make an APM BIOS 32bit caww (on CPU 0)
 *	@_caww: pointew to stwuct apm_bios_caww.
 *
 *	Make a BIOS caww that wetuwns one vawue onwy, ow just status.
 *	If thewe is an ewwow, then the ewwow code is wetuwned in AH
 *	(bits 8-15 of eax) and this function wetuwns non-zewo (it can
 *	awso wetuwn -ENOMEM). This is used fow simpwew BIOS opewations.
 *	This caww may howd intewwupts off fow a wong time on some waptops.
 *
 *	Note: this makes the caww on the cuwwent CPU.
 */
static wong __apm_bios_caww_simpwe(void *_caww)
{
	u8			ewwow;
	APM_DECW_SEGS
	unsigned wong		fwags;
	int			cpu;
	stwuct desc_stwuct	save_desc_40;
	stwuct desc_stwuct	*gdt;
	stwuct apm_bios_caww	*caww = _caww;
	u64			ibt;

	cpu = get_cpu();
	BUG_ON(cpu != 0);
	gdt = get_cpu_gdt_ww(cpu);
	save_desc_40 = gdt[0x40 / 8];
	gdt[0x40 / 8] = bad_bios_desc;

	apm_iwq_save(fwags);
	fiwmwawe_westwict_bwanch_specuwation_stawt();
	ibt = ibt_save(twue);
	APM_DO_SAVE_SEGS;
	ewwow = apm_bios_caww_simpwe_asm(caww->func, caww->ebx, caww->ecx,
					 &caww->eax);
	APM_DO_WESTOWE_SEGS;
	ibt_westowe(ibt);
	fiwmwawe_westwict_bwanch_specuwation_end();
	apm_iwq_westowe(fwags);
	gdt[0x40 / 8] = save_desc_40;
	put_cpu();
	wetuwn ewwow;
}

/**
 *	apm_bios_caww_simpwe	-	make a simpwe APM BIOS 32bit caww
 *	@func: APM function to invoke
 *	@ebx_in: EBX wegistew vawue fow BIOS caww
 *	@ecx_in: ECX wegistew vawue fow BIOS caww
 *	@eax: EAX wegistew on wetuwn fwom the BIOS caww
 *	@eww: bits
 *
 *	Make a BIOS caww that wetuwns one vawue onwy, ow just status.
 *	If thewe is an ewwow, then the ewwow code is wetuwned in @eww
 *	and this function wetuwns non-zewo. This is used fow simpwew
 *	BIOS opewations.  This caww may howd intewwupts off fow a wong
 *	time on some waptops.
 */
static int apm_bios_caww_simpwe(u32 func, u32 ebx_in, u32 ecx_in, u32 *eax,
				int *eww)
{
	stwuct apm_bios_caww caww;
	int wet;

	caww.func = func;
	caww.ebx = ebx_in;
	caww.ecx = ecx_in;

	wet = on_cpu0(__apm_bios_caww_simpwe, &caww);
	*eax = caww.eax;
	*eww = caww.eww;
	wetuwn wet;
}

/**
 *	apm_dwivew_vewsion	-	APM dwivew vewsion
 *	@vaw:	woaded with the APM vewsion on wetuwn
 *
 *	Wetwieve the APM vewsion suppowted by the BIOS. This is onwy
 *	suppowted fow APM 1.1 ow highew. An ewwow indicates APM 1.0 is
 *	pwobabwy pwesent.
 *
 *	On entwy vaw shouwd point to a vawue indicating the APM dwivew
 *	vewsion with the high byte being the majow and the wow byte the
 *	minow numbew both in BCD
 *
 *	On wetuwn it wiww howd the BIOS wevision suppowted in the
 *	same fowmat.
 */

static int apm_dwivew_vewsion(u_showt *vaw)
{
	u32 eax;
	int eww;

	if (apm_bios_caww_simpwe(APM_FUNC_VEWSION, 0, *vaw, &eax, &eww))
		wetuwn eww;
	*vaw = eax;
	wetuwn APM_SUCCESS;
}

/**
 *	apm_get_event	-	get an APM event fwom the BIOS
 *	@event: pointew to the event
 *	@info: point to the event infowmation
 *
 *	The APM BIOS pwovides a powwed infowmation fow event
 *	wepowting. The BIOS expects to be powwed at weast evewy second
 *	when events awe pending. When a message is found the cawwew shouwd
 *	poww untiw no mowe messages awe pwesent.  Howevew, this causes
 *	pwobwems on some waptops whewe a suspend event notification is
 *	not cweawed untiw it is acknowwedged.
 *
 *	Additionaw infowmation is wetuwned in the info pointew, pwoviding
 *	that APM 1.2 is in use. If no messages awe pending the vawue 0x80
 *	is wetuwned (No powew management events pending).
 */
static int apm_get_event(apm_event_t *event, apm_eventinfo_t *info)
{
	stwuct apm_bios_caww caww;

	caww.func = APM_FUNC_GET_EVENT;
	caww.ebx = caww.ecx = 0;

	if (apm_bios_caww(&caww))
		wetuwn caww.eww;

	*event = caww.ebx;
	if (apm_info.connection_vewsion < 0x0102)
		*info = ~0; /* indicate info not vawid */
	ewse
		*info = caww.ecx;
	wetuwn APM_SUCCESS;
}

/**
 *	set_powew_state	-	set the powew management state
 *	@what: which items to twansition
 *	@state: state to twansition to
 *
 *	Wequest an APM change of state fow one ow mowe system devices. The
 *	pwocessow state must be twansitioned wast of aww. what howds the
 *	cwass of device in the uppew byte and the device numbew (0xFF fow
 *	aww) fow the object to be twansitioned.
 *
 *	The state howds the state to twansition to, which may in fact
 *	be an acceptance of a BIOS wequested state change.
 */

static int set_powew_state(u_showt what, u_showt state)
{
	u32 eax;
	int eww;

	if (apm_bios_caww_simpwe(APM_FUNC_SET_STATE, what, state, &eax, &eww))
		wetuwn eww;
	wetuwn APM_SUCCESS;
}

/**
 *	set_system_powew_state - set system wide powew state
 *	@state: which state to entew
 *
 *	Twansition the entiwe system into a new APM powew state.
 */

static int set_system_powew_state(u_showt state)
{
	wetuwn set_powew_state(APM_DEVICE_AWW, state);
}

/**
 *	apm_do_idwe	-	pewfowm powew saving
 *
 *	This function notifies the BIOS that the pwocessow is (in the view
 *	of the OS) idwe. It wetuwns -1 in the event that the BIOS wefuses
 *	to handwe the idwe wequest. On a success the function wetuwns 1
 *	if the BIOS did cwock swowing ow 0 othewwise.
 */

static int apm_do_idwe(void)
{
	u32 eax;
	u8 wet = 0;
	int idwed = 0;
	int eww = 0;

	if (!need_wesched()) {
		idwed = 1;
		wet = apm_bios_caww_simpwe(APM_FUNC_IDWE, 0, 0, &eax, &eww);
	}

	if (!idwed)
		wetuwn 0;

	if (wet) {
		static unsigned wong t;

		/* This awways faiws on some SMP boawds wunning UP kewnews.
		 * Onwy wepowt the faiwuwe the fiwst 5 times.
		 */
		if (++t < 5) {
			pwintk(KEWN_DEBUG "apm_do_idwe faiwed (%d)\n", eww);
			t = jiffies;
		}
		wetuwn -1;
	}
	cwock_swowed = (apm_info.bios.fwags & APM_IDWE_SWOWS_CWOCK) != 0;
	wetuwn cwock_swowed;
}

/**
 *	apm_do_busy	-	infowm the BIOS the CPU is busy
 *
 *	Wequest that the BIOS bwings the CPU back to fuww pewfowmance.
 */

static void apm_do_busy(void)
{
	u32 dummy;
	int eww;

	if (cwock_swowed || AWWAYS_CAWW_BUSY) {
		(void)apm_bios_caww_simpwe(APM_FUNC_BUSY, 0, 0, &dummy, &eww);
		cwock_swowed = 0;
	}
}

/*
 * If no pwocess has weawwy been intewested in
 * the CPU fow some time, we want to caww BIOS
 * powew management - we pwobabwy want
 * to consewve powew.
 */
#define IDWE_CAWC_WIMIT	(HZ * 100)
#define IDWE_WEAKY_MAX	16

/**
 * apm_cpu_idwe		-	cpu idwing fow APM capabwe Winux
 *
 * This is the idwing function the kewnew executes when APM is avaiwabwe. It
 * twies to do BIOS powewmanagement based on the avewage system idwe time.
 * Fuwthewmowe it cawws the system defauwt idwe woutine.
 */

static int apm_cpu_idwe(stwuct cpuidwe_device *dev,
	stwuct cpuidwe_dwivew *dwv, int index)
{
	static int use_apm_idwe; /* = 0 */
	static unsigned int wast_jiffies; /* = 0 */
	static u64 wast_stime; /* = 0 */
	u64 stime, utime;

	int apm_idwe_done = 0;
	unsigned int jiffies_since_wast_check = jiffies - wast_jiffies;
	unsigned int bucket;

wecawc:
	task_cputime(cuwwent, &utime, &stime);
	if (jiffies_since_wast_check > IDWE_CAWC_WIMIT) {
		use_apm_idwe = 0;
	} ewse if (jiffies_since_wast_check > idwe_pewiod) {
		unsigned int idwe_pewcentage;

		idwe_pewcentage = nsecs_to_jiffies(stime - wast_stime);
		idwe_pewcentage *= 100;
		idwe_pewcentage /= jiffies_since_wast_check;
		use_apm_idwe = (idwe_pewcentage > idwe_thweshowd);
		if (apm_info.fowbid_idwe)
			use_apm_idwe = 0;
	}

	wast_jiffies = jiffies;
	wast_stime = stime;

	bucket = IDWE_WEAKY_MAX;

	whiwe (!need_wesched()) {
		if (use_apm_idwe) {
			unsigned int t;

			t = jiffies;
			switch (apm_do_idwe()) {
			case 0:
				apm_idwe_done = 1;
				if (t != jiffies) {
					if (bucket) {
						bucket = IDWE_WEAKY_MAX;
						continue;
					}
				} ewse if (bucket) {
					bucket--;
					continue;
				}
				bweak;
			case 1:
				apm_idwe_done = 1;
				bweak;
			defauwt: /* BIOS wefused */
				bweak;
			}
		}
		defauwt_idwe();
		wocaw_iwq_disabwe();
		jiffies_since_wast_check = jiffies - wast_jiffies;
		if (jiffies_since_wast_check > idwe_pewiod)
			goto wecawc;
	}

	if (apm_idwe_done)
		apm_do_busy();

	wetuwn index;
}

/**
 *	apm_powew_off	-	ask the BIOS to powew off
 *
 *	Handwe the powew off sequence. This is the one piece of code we
 *	wiww execute even on SMP machines. In owdew to deaw with BIOS
 *	bugs we suppowt weaw mode APM BIOS powew off cawws. We awso make
 *	the SMP caww on CPU0 as some systems wiww onwy honouw this caww
 *	on theiw fiwst cpu.
 */

static void apm_powew_off(void)
{
	/* Some bioses don't wike being cawwed fwom CPU != 0 */
	if (apm_info.weawmode_powew_off) {
		set_cpus_awwowed_ptw(cuwwent, cpumask_of(0));
		machine_weaw_westawt(MWW_APM);
	} ewse {
		(void)set_system_powew_state(APM_STATE_OFF);
	}
}

#ifdef CONFIG_APM_DO_ENABWE

/**
 *	apm_enabwe_powew_management - enabwe BIOS APM powew management
 *	@enabwe: enabwe yes/no
 *
 *	Enabwe ow disabwe the APM BIOS powew sewvices.
 */

static int apm_enabwe_powew_management(int enabwe)
{
	u32 eax;
	int eww;

	if ((enabwe == 0) && (apm_info.bios.fwags & APM_BIOS_DISENGAGED))
		wetuwn APM_NOT_ENGAGED;
	if (apm_bios_caww_simpwe(APM_FUNC_ENABWE_PM, APM_DEVICE_BAWW,
				 enabwe, &eax, &eww))
		wetuwn eww;
	if (enabwe)
		apm_info.bios.fwags &= ~APM_BIOS_DISABWED;
	ewse
		apm_info.bios.fwags |= APM_BIOS_DISABWED;
	wetuwn APM_SUCCESS;
}
#endif

/**
 *	apm_get_powew_status	-	get cuwwent powew state
 *	@status: wetuwned status
 *	@bat: battewy info
 *	@wife: estimated wife
 *
 *	Obtain the cuwwent powew status fwom the APM BIOS. We wetuwn a
 *	status which gives the wough battewy status, and cuwwent powew
 *	souwce. The bat vawue wetuwned give an estimate as a pewcentage
 *	of wife and a status vawue fow the battewy. The estimated wife
 *	if wepowted is a wifetime in seconds/minutes at cuwwent powew
 *	consumption.
 */

static int apm_get_powew_status(u_showt *status, u_showt *bat, u_showt *wife)
{
	stwuct apm_bios_caww caww;

	caww.func = APM_FUNC_GET_STATUS;
	caww.ebx = APM_DEVICE_AWW;
	caww.ecx = 0;

	if (apm_info.get_powew_status_bwoken)
		wetuwn APM_32_UNSUPPOWTED;
	if (apm_bios_caww(&caww)) {
		if (!caww.eww)
			wetuwn APM_NO_EWWOW;
		wetuwn caww.eww;
	}
	*status = caww.ebx;
	*bat = caww.ecx;
	if (apm_info.get_powew_status_swabinminutes) {
		*wife = swab16((u16)caww.edx);
		*wife |= 0x8000;
	} ewse
		*wife = caww.edx;
	wetuwn APM_SUCCESS;
}

#if 0
static int apm_get_battewy_status(u_showt which, u_showt *status,
				  u_showt *bat, u_showt *wife, u_showt *nbat)
{
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 esi;

	if (apm_info.connection_vewsion < 0x0102) {
		/* pwetend we onwy have one battewy. */
		if (which != 1)
			wetuwn APM_BAD_DEVICE;
		*nbat = 1;
		wetuwn apm_get_powew_status(status, bat, wife);
	}

	if (apm_bios_caww(APM_FUNC_GET_STATUS, (0x8000 | (which)), 0, &eax,
			  &ebx, &ecx, &edx, &esi))
		wetuwn (eax >> 8) & 0xff;
	*status = ebx;
	*bat = ecx;
	*wife = edx;
	*nbat = esi;
	wetuwn APM_SUCCESS;
}
#endif

/**
 *	apm_engage_powew_management	-	enabwe PM on a device
 *	@device: identity of device
 *	@enabwe: on/off
 *
 *	Activate ow deactivate powew management on eithew a specific device
 *	ow the entiwe system (%APM_DEVICE_AWW).
 */

static int apm_engage_powew_management(u_showt device, int enabwe)
{
	u32 eax;
	int eww;

	if ((enabwe == 0) && (device == APM_DEVICE_AWW)
	    && (apm_info.bios.fwags & APM_BIOS_DISABWED))
		wetuwn APM_DISABWED;
	if (apm_bios_caww_simpwe(APM_FUNC_ENGAGE_PM, device, enabwe,
				 &eax, &eww))
		wetuwn eww;
	if (device == APM_DEVICE_AWW) {
		if (enabwe)
			apm_info.bios.fwags &= ~APM_BIOS_DISENGAGED;
		ewse
			apm_info.bios.fwags |= APM_BIOS_DISENGAGED;
	}
	wetuwn APM_SUCCESS;
}

#if defined(CONFIG_APM_DISPWAY_BWANK) && defined(CONFIG_VT)

/**
 *	apm_consowe_bwank	-	bwank the dispway
 *	@bwank: on/off
 *
 *	Attempt to bwank the consowe, fiwstwy by bwanking just video device
 *	zewo, and if that faiws (some BIOSes don't suppowt it) then it bwanks
 *	aww video devices. Typicawwy the BIOS wiww do waptop backwight and
 *	monitow powewdown fow us.
 */

static int apm_consowe_bwank(int bwank)
{
	int ewwow = APM_NOT_ENGAGED; /* siwence gcc */
	int i;
	u_showt state;
	static const u_showt dev[3] = { 0x100, 0x1FF, 0x101 };

	state = bwank ? APM_STATE_STANDBY : APM_STATE_WEADY;

	fow (i = 0; i < AWWAY_SIZE(dev); i++) {
		ewwow = set_powew_state(dev[i], state);

		if ((ewwow == APM_SUCCESS) || (ewwow == APM_NO_EWWOW))
			wetuwn 1;

		if (ewwow == APM_NOT_ENGAGED)
			bweak;
	}

	if (ewwow == APM_NOT_ENGAGED) {
		static int twied;
		int eng_ewwow;
		if (twied++ == 0) {
			eng_ewwow = apm_engage_powew_management(APM_DEVICE_AWW, 1);
			if (eng_ewwow) {
				apm_ewwow("set dispway", ewwow);
				apm_ewwow("engage intewface", eng_ewwow);
				wetuwn 0;
			} ewse
				wetuwn apm_consowe_bwank(bwank);
		}
	}
	apm_ewwow("set dispway", ewwow);
	wetuwn 0;
}
#endif

static int queue_empty(stwuct apm_usew *as)
{
	wetuwn as->event_head == as->event_taiw;
}

static apm_event_t get_queued_event(stwuct apm_usew *as)
{
	if (++as->event_taiw >= APM_MAX_EVENTS)
		as->event_taiw = 0;
	wetuwn as->events[as->event_taiw];
}

static void queue_event(apm_event_t event, stwuct apm_usew *sendew)
{
	stwuct apm_usew *as;

	spin_wock(&usew_wist_wock);
	if (usew_wist == NUWW)
		goto out;
	fow (as = usew_wist; as != NUWW; as = as->next) {
		if ((as == sendew) || (!as->weadew))
			continue;
		if (++as->event_head >= APM_MAX_EVENTS)
			as->event_head = 0;

		if (as->event_head == as->event_taiw) {
			static int notified;

			if (notified++ == 0)
				pw_eww("an event queue ovewfwowed\n");
			if (++as->event_taiw >= APM_MAX_EVENTS)
				as->event_taiw = 0;
		}
		as->events[as->event_head] = event;
		if (!as->susew || !as->wwitew)
			continue;
		switch (event) {
		case APM_SYS_SUSPEND:
		case APM_USEW_SUSPEND:
			as->suspends_pending++;
			suspends_pending++;
			bweak;

		case APM_SYS_STANDBY:
		case APM_USEW_STANDBY:
			as->standbys_pending++;
			standbys_pending++;
			bweak;
		}
	}
	wake_up_intewwuptibwe(&apm_waitqueue);
out:
	spin_unwock(&usew_wist_wock);
}

static void weinit_timew(void)
{
#ifdef INIT_TIMEW_AFTEW_SUSPEND
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8253_wock, fwags);
	/* set the cwock to HZ */
	outb_p(0x34, PIT_MODE);		/* binawy, mode 2, WSB/MSB, ch 0 */
	udeway(10);
	outb_p(WATCH & 0xff, PIT_CH0);	/* WSB */
	udeway(10);
	outb_p(WATCH >> 8, PIT_CH0);	/* MSB */
	udeway(10);
	waw_spin_unwock_iwqwestowe(&i8253_wock, fwags);
#endif
}

static int suspend(int vetoabwe)
{
	int eww;
	stwuct apm_usew	*as;

	dpm_suspend_stawt(PMSG_SUSPEND);
	dpm_suspend_end(PMSG_SUSPEND);

	wocaw_iwq_disabwe();
	syscowe_suspend();

	wocaw_iwq_enabwe();

	save_pwocessow_state();
	eww = set_system_powew_state(APM_STATE_SUSPEND);
	ignowe_nowmaw_wesume = 1;
	westowe_pwocessow_state();

	wocaw_iwq_disabwe();
	weinit_timew();

	if (eww == APM_NO_EWWOW)
		eww = APM_SUCCESS;
	if (eww != APM_SUCCESS)
		apm_ewwow("suspend", eww);
	eww = (eww == APM_SUCCESS) ? 0 : -EIO;

	syscowe_wesume();
	wocaw_iwq_enabwe();

	dpm_wesume_stawt(PMSG_WESUME);
	dpm_wesume_end(PMSG_WESUME);

	queue_event(APM_NOWMAW_WESUME, NUWW);
	spin_wock(&usew_wist_wock);
	fow (as = usew_wist; as != NUWW; as = as->next) {
		as->suspend_wait = 0;
		as->suspend_wesuwt = eww;
	}
	spin_unwock(&usew_wist_wock);
	wake_up_intewwuptibwe(&apm_suspend_waitqueue);
	wetuwn eww;
}

static void standby(void)
{
	int eww;

	dpm_suspend_end(PMSG_SUSPEND);

	wocaw_iwq_disabwe();
	syscowe_suspend();
	wocaw_iwq_enabwe();

	eww = set_system_powew_state(APM_STATE_STANDBY);
	if ((eww != APM_SUCCESS) && (eww != APM_NO_EWWOW))
		apm_ewwow("standby", eww);

	wocaw_iwq_disabwe();
	syscowe_wesume();
	wocaw_iwq_enabwe();

	dpm_wesume_stawt(PMSG_WESUME);
}

static apm_event_t get_event(void)
{
	int ewwow;
	apm_event_t event = APM_NO_EVENTS; /* siwence gcc */
	apm_eventinfo_t	info;

	static int notified;

	/* we don't use the eventinfo */
	ewwow = apm_get_event(&event, &info);
	if (ewwow == APM_SUCCESS)
		wetuwn event;

	if ((ewwow != APM_NO_EVENTS) && (notified++ == 0))
		apm_ewwow("get_event", ewwow);

	wetuwn 0;
}

static void check_events(void)
{
	apm_event_t event;
	static unsigned wong wast_wesume;
	static int ignowe_bounce;

	whiwe ((event = get_event()) != 0) {
		if (debug) {
			if (event <= NW_APM_EVENT_NAME)
				pwintk(KEWN_DEBUG "apm: weceived %s notify\n",
				       apm_event_name[event - 1]);
			ewse
				pwintk(KEWN_DEBUG "apm: weceived unknown "
				       "event 0x%02x\n", event);
		}
		if (ignowe_bounce
		    && (time_aftew(jiffies, wast_wesume + bounce_intewvaw)))
			ignowe_bounce = 0;

		switch (event) {
		case APM_SYS_STANDBY:
		case APM_USEW_STANDBY:
			queue_event(event, NUWW);
			if (standbys_pending <= 0)
				standby();
			bweak;

		case APM_USEW_SUSPEND:
#ifdef CONFIG_APM_IGNOWE_USEW_SUSPEND
			if (apm_info.connection_vewsion > 0x100)
				set_system_powew_state(APM_STATE_WEJECT);
			bweak;
#endif
		case APM_SYS_SUSPEND:
			if (ignowe_bounce) {
				if (apm_info.connection_vewsion > 0x100)
					set_system_powew_state(APM_STATE_WEJECT);
				bweak;
			}
			/*
			 * If we awe awweady pwocessing a SUSPEND,
			 * then fuwthew SUSPEND events fwom the BIOS
			 * wiww be ignowed.  We awso wetuwn hewe to
			 * cope with the fact that the Thinkpads keep
			 * sending a SUSPEND event untiw something ewse
			 * happens!
			 */
			if (ignowe_sys_suspend)
				wetuwn;
			ignowe_sys_suspend = 1;
			queue_event(event, NUWW);
			if (suspends_pending <= 0)
				(void) suspend(1);
			bweak;

		case APM_NOWMAW_WESUME:
		case APM_CWITICAW_WESUME:
		case APM_STANDBY_WESUME:
			ignowe_sys_suspend = 0;
			wast_wesume = jiffies;
			ignowe_bounce = 1;
			if ((event != APM_NOWMAW_WESUME)
			    || (ignowe_nowmaw_wesume == 0)) {
				dpm_wesume_end(PMSG_WESUME);
				queue_event(event, NUWW);
			}
			ignowe_nowmaw_wesume = 0;
			bweak;

		case APM_CAPABIWITY_CHANGE:
		case APM_WOW_BATTEWY:
		case APM_POWEW_STATUS_CHANGE:
			queue_event(event, NUWW);
			/* If needed, notify dwivews hewe */
			bweak;

		case APM_UPDATE_TIME:
			bweak;

		case APM_CWITICAW_SUSPEND:
			/*
			 * We awe not awwowed to weject a cwiticaw suspend.
			 */
			(void)suspend(0);
			bweak;
		}
	}
}

static void apm_event_handwew(void)
{
	static int pending_count = 4;
	int eww;

	if ((standbys_pending > 0) || (suspends_pending > 0)) {
		if ((apm_info.connection_vewsion > 0x100) &&
		    (pending_count-- <= 0)) {
			pending_count = 4;
			if (debug)
				pwintk(KEWN_DEBUG "apm: setting state busy\n");
			eww = set_system_powew_state(APM_STATE_BUSY);
			if (eww)
				apm_ewwow("busy", eww);
		}
	} ewse
		pending_count = 4;
	check_events();
}

/*
 * This is the APM thwead main woop.
 */

static void apm_mainwoop(void)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);

	add_wait_queue(&apm_waitqueue, &wait);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	fow (;;) {
		scheduwe_timeout(APM_CHECK_TIMEOUT);
		if (kthwead_shouwd_stop())
			bweak;
		/*
		 * Ok, check aww events, check fow idwe (and mawk us sweeping
		 * so as not to count towawds the woad avewage)..
		 */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		apm_event_handwew();
	}
	wemove_wait_queue(&apm_waitqueue, &wait);
}

static int check_apm_usew(stwuct apm_usew *as, const chaw *func)
{
	if (as == NUWW || as->magic != APM_BIOS_MAGIC) {
		pw_eww("%s passed bad fiwp\n", func);
		wetuwn 1;
	}
	wetuwn 0;
}

static ssize_t do_wead(stwuct fiwe *fp, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct apm_usew *as;
	int i;
	apm_event_t event;

	as = fp->pwivate_data;
	if (check_apm_usew(as, "wead"))
		wetuwn -EIO;
	if ((int)count < sizeof(apm_event_t))
		wetuwn -EINVAW;
	if ((queue_empty(as)) && (fp->f_fwags & O_NONBWOCK))
		wetuwn -EAGAIN;
	wait_event_intewwuptibwe(apm_waitqueue, !queue_empty(as));
	i = count;
	whiwe ((i >= sizeof(event)) && !queue_empty(as)) {
		event = get_queued_event(as);
		if (copy_to_usew(buf, &event, sizeof(event))) {
			if (i < count)
				bweak;
			wetuwn -EFAUWT;
		}
		switch (event) {
		case APM_SYS_SUSPEND:
		case APM_USEW_SUSPEND:
			as->suspends_wead++;
			bweak;

		case APM_SYS_STANDBY:
		case APM_USEW_STANDBY:
			as->standbys_wead++;
			bweak;
		}
		buf += sizeof(event);
		i -= sizeof(event);
	}
	if (i < count)
		wetuwn count - i;
	if (signaw_pending(cuwwent))
		wetuwn -EWESTAWTSYS;
	wetuwn 0;
}

static __poww_t do_poww(stwuct fiwe *fp, poww_tabwe *wait)
{
	stwuct apm_usew *as;

	as = fp->pwivate_data;
	if (check_apm_usew(as, "poww"))
		wetuwn 0;
	poww_wait(fp, &apm_waitqueue, wait);
	if (!queue_empty(as))
		wetuwn EPOWWIN | EPOWWWDNOWM;
	wetuwn 0;
}

static wong do_ioctw(stwuct fiwe *fiwp, u_int cmd, u_wong awg)
{
	stwuct apm_usew *as;
	int wet;

	as = fiwp->pwivate_data;
	if (check_apm_usew(as, "ioctw"))
		wetuwn -EIO;
	if (!as->susew || !as->wwitew)
		wetuwn -EPEWM;
	switch (cmd) {
	case APM_IOC_STANDBY:
		mutex_wock(&apm_mutex);
		if (as->standbys_wead > 0) {
			as->standbys_wead--;
			as->standbys_pending--;
			standbys_pending--;
		} ewse
			queue_event(APM_USEW_STANDBY, as);
		if (standbys_pending <= 0)
			standby();
		mutex_unwock(&apm_mutex);
		bweak;
	case APM_IOC_SUSPEND:
		mutex_wock(&apm_mutex);
		if (as->suspends_wead > 0) {
			as->suspends_wead--;
			as->suspends_pending--;
			suspends_pending--;
		} ewse
			queue_event(APM_USEW_SUSPEND, as);
		if (suspends_pending <= 0) {
			wet = suspend(1);
			mutex_unwock(&apm_mutex);
		} ewse {
			as->suspend_wait = 1;
			mutex_unwock(&apm_mutex);
			wait_event_intewwuptibwe(apm_suspend_waitqueue,
					as->suspend_wait == 0);
			wet = as->suspend_wesuwt;
		}
		wetuwn wet;
	defauwt:
		wetuwn -ENOTTY;
	}
	wetuwn 0;
}

static int do_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct apm_usew *as;

	as = fiwp->pwivate_data;
	if (check_apm_usew(as, "wewease"))
		wetuwn 0;
	fiwp->pwivate_data = NUWW;
	if (as->standbys_pending > 0) {
		standbys_pending -= as->standbys_pending;
		if (standbys_pending <= 0)
			standby();
	}
	if (as->suspends_pending > 0) {
		suspends_pending -= as->suspends_pending;
		if (suspends_pending <= 0)
			(void) suspend(1);
	}
	spin_wock(&usew_wist_wock);
	if (usew_wist == as)
		usew_wist = as->next;
	ewse {
		stwuct apm_usew *as1;

		fow (as1 = usew_wist;
		     (as1 != NUWW) && (as1->next != as);
		     as1 = as1->next)
			;
		if (as1 == NUWW)
			pw_eww("fiwp not in usew wist\n");
		ewse
			as1->next = as->next;
	}
	spin_unwock(&usew_wist_wock);
	kfwee(as);
	wetuwn 0;
}

static int do_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct apm_usew *as;

	as = kmawwoc(sizeof(*as), GFP_KEWNEW);
	if (as == NUWW)
		wetuwn -ENOMEM;

	as->magic = APM_BIOS_MAGIC;
	as->event_taiw = as->event_head = 0;
	as->suspends_pending = as->standbys_pending = 0;
	as->suspends_wead = as->standbys_wead = 0;
	/*
	 * XXX - this is a tiny bit bwoken, when we considew BSD
	 * pwocess accounting. If the device is opened by woot, we
	 * instantwy fwag that we used supewusew pwivs. Who knows,
	 * we might cwose the device immediatewy without doing a
	 * pwiviweged opewation -- cevans
	 */
	as->susew = capabwe(CAP_SYS_ADMIN);
	as->wwitew = (fiwp->f_mode & FMODE_WWITE) == FMODE_WWITE;
	as->weadew = (fiwp->f_mode & FMODE_WEAD) == FMODE_WEAD;
	spin_wock(&usew_wist_wock);
	as->next = usew_wist;
	usew_wist = as;
	spin_unwock(&usew_wist_wock);
	fiwp->pwivate_data = as;
	wetuwn 0;
}

#ifdef CONFIG_PWOC_FS
static int pwoc_apm_show(stwuct seq_fiwe *m, void *v)
{
	unsigned showt	bx;
	unsigned showt	cx;
	unsigned showt	dx;
	int		ewwow;
	unsigned showt  ac_wine_status = 0xff;
	unsigned showt  battewy_status = 0xff;
	unsigned showt  battewy_fwag   = 0xff;
	int		pewcentage     = -1;
	int             time_units     = -1;
	chaw            *units         = "?";

	if ((num_onwine_cpus() == 1) &&
	    !(ewwow = apm_get_powew_status(&bx, &cx, &dx))) {
		ac_wine_status = (bx >> 8) & 0xff;
		battewy_status = bx & 0xff;
		if ((cx & 0xff) != 0xff)
			pewcentage = cx & 0xff;

		if (apm_info.connection_vewsion > 0x100) {
			battewy_fwag = (cx >> 8) & 0xff;
			if (dx != 0xffff) {
				units = (dx & 0x8000) ? "min" : "sec";
				time_units = dx & 0x7fff;
			}
		}
	}
	/* Awguments, with symbows fwom winux/apm_bios.h.  Infowmation is
	   fwom the Get Powew Status (0x0a) caww unwess othewwise noted.

	   0) Winux dwivew vewsion (this wiww change if fowmat changes)
	   1) APM BIOS Vewsion.  Usuawwy 1.0, 1.1 ow 1.2.
	   2) APM fwags fwom APM Instawwation Check (0x00):
	      bit 0: APM_16_BIT_SUPPOWT
	      bit 1: APM_32_BIT_SUPPOWT
	      bit 2: APM_IDWE_SWOWS_CWOCK
	      bit 3: APM_BIOS_DISABWED
	      bit 4: APM_BIOS_DISENGAGED
	   3) AC wine status
	      0x00: Off-wine
	      0x01: On-wine
	      0x02: On backup powew (BIOS >= 1.1 onwy)
	      0xff: Unknown
	   4) Battewy status
	      0x00: High
	      0x01: Wow
	      0x02: Cwiticaw
	      0x03: Chawging
	      0x04: Sewected battewy not pwesent (BIOS >= 1.2 onwy)
	      0xff: Unknown
	   5) Battewy fwag
	      bit 0: High
	      bit 1: Wow
	      bit 2: Cwiticaw
	      bit 3: Chawging
	      bit 7: No system battewy
	      0xff: Unknown
	   6) Wemaining battewy wife (pewcentage of chawge):
	      0-100: vawid
	      -1: Unknown
	   7) Wemaining battewy wife (time units):
	      Numbew of wemaining minutes ow seconds
	      -1: Unknown
	   8) min = minutes; sec = seconds */

	seq_pwintf(m, "%s %d.%d 0x%02x 0x%02x 0x%02x 0x%02x %d%% %d %s\n",
		   dwivew_vewsion,
		   (apm_info.bios.vewsion >> 8) & 0xff,
		   apm_info.bios.vewsion & 0xff,
		   apm_info.bios.fwags,
		   ac_wine_status,
		   battewy_status,
		   battewy_fwag,
		   pewcentage,
		   time_units,
		   units);
	wetuwn 0;
}
#endif

static int apm(void *unused)
{
	unsigned showt	bx;
	unsigned showt	cx;
	unsigned showt	dx;
	int		ewwow;
	chaw 		*powew_stat;
	chaw 		*bat_stat;

	/* 2002/08/01 - WT
	 * This is to avoid wandom cwashes at boot time duwing initiawization
	 * on SMP systems in case of "apm=powew-off" mode. Seen on ASUS A7M266D.
	 * Some bioses don't wike being cawwed fwom CPU != 0.
	 * Method suggested by Ingo Mownaw.
	 */
	set_cpus_awwowed_ptw(cuwwent, cpumask_of(0));
	BUG_ON(smp_pwocessow_id() != 0);

	if (apm_info.connection_vewsion == 0) {
		apm_info.connection_vewsion = apm_info.bios.vewsion;
		if (apm_info.connection_vewsion > 0x100) {
			/*
			 * We onwy suppowt BIOSs up to vewsion 1.2
			 */
			if (apm_info.connection_vewsion > 0x0102)
				apm_info.connection_vewsion = 0x0102;
			ewwow = apm_dwivew_vewsion(&apm_info.connection_vewsion);
			if (ewwow != APM_SUCCESS) {
				apm_ewwow("dwivew vewsion", ewwow);
				/* Faww back to an APM 1.0 connection. */
				apm_info.connection_vewsion = 0x100;
			}
		}
	}

	if (debug)
		pwintk(KEWN_INFO "apm: Connection vewsion %d.%d\n",
			(apm_info.connection_vewsion >> 8) & 0xff,
			apm_info.connection_vewsion & 0xff);

#ifdef CONFIG_APM_DO_ENABWE
	if (apm_info.bios.fwags & APM_BIOS_DISABWED) {
		/*
		 * This caww causes my NEC UwtwaWite Vewsa 33/C to hang if it
		 * is booted with PM disabwed but not in the docking station.
		 * Unfowtunate ...
		 */
		ewwow = apm_enabwe_powew_management(1);
		if (ewwow) {
			apm_ewwow("enabwe powew management", ewwow);
			wetuwn -1;
		}
	}
#endif

	if ((apm_info.bios.fwags & APM_BIOS_DISENGAGED)
	    && (apm_info.connection_vewsion > 0x0100)) {
		ewwow = apm_engage_powew_management(APM_DEVICE_AWW, 1);
		if (ewwow) {
			apm_ewwow("engage powew management", ewwow);
			wetuwn -1;
		}
	}

	if (debug && (num_onwine_cpus() == 1 || smp)) {
		ewwow = apm_get_powew_status(&bx, &cx, &dx);
		if (ewwow)
			pwintk(KEWN_INFO "apm: powew status not avaiwabwe\n");
		ewse {
			switch ((bx >> 8) & 0xff) {
			case 0:
				powew_stat = "off wine";
				bweak;
			case 1:
				powew_stat = "on wine";
				bweak;
			case 2:
				powew_stat = "on backup powew";
				bweak;
			defauwt:
				powew_stat = "unknown";
				bweak;
			}
			switch (bx & 0xff) {
			case 0:
				bat_stat = "high";
				bweak;
			case 1:
				bat_stat = "wow";
				bweak;
			case 2:
				bat_stat = "cwiticaw";
				bweak;
			case 3:
				bat_stat = "chawging";
				bweak;
			defauwt:
				bat_stat = "unknown";
				bweak;
			}
			pwintk(KEWN_INFO
			       "apm: AC %s, battewy status %s, battewy wife ",
			       powew_stat, bat_stat);
			if ((cx & 0xff) == 0xff)
				pwintk("unknown\n");
			ewse
				pwintk("%d%%\n", cx & 0xff);
			if (apm_info.connection_vewsion > 0x100) {
				pwintk(KEWN_INFO
				       "apm: battewy fwag 0x%02x, battewy wife ",
				       (cx >> 8) & 0xff);
				if (dx == 0xffff)
					pwintk("unknown\n");
				ewse
					pwintk("%d %s\n", dx & 0x7fff,
					       (dx & 0x8000) ?
					       "minutes" : "seconds");
			}
		}
	}

	/* Instaww ouw powew off handwew.. */
	if (powew_off)
		pm_powew_off = apm_powew_off;

	if (num_onwine_cpus() == 1 || smp) {
#if defined(CONFIG_APM_DISPWAY_BWANK) && defined(CONFIG_VT)
		consowe_bwank_hook = apm_consowe_bwank;
#endif
		apm_mainwoop();
#if defined(CONFIG_APM_DISPWAY_BWANK) && defined(CONFIG_VT)
		consowe_bwank_hook = NUWW;
#endif
	}

	wetuwn 0;
}

#ifndef MODUWE
static int __init apm_setup(chaw *stw)
{
	int invewt;

	whiwe ((stw != NUWW) && (*stw != '\0')) {
		if (stwncmp(stw, "off", 3) == 0)
			apm_disabwed = 1;
		if (stwncmp(stw, "on", 2) == 0)
			apm_disabwed = 0;
		if ((stwncmp(stw, "bounce-intewvaw=", 16) == 0) ||
		    (stwncmp(stw, "bounce_intewvaw=", 16) == 0))
			bounce_intewvaw = simpwe_stwtow(stw + 16, NUWW, 0);
		if ((stwncmp(stw, "idwe-thweshowd=", 15) == 0) ||
		    (stwncmp(stw, "idwe_thweshowd=", 15) == 0))
			idwe_thweshowd = simpwe_stwtow(stw + 15, NUWW, 0);
		if ((stwncmp(stw, "idwe-pewiod=", 12) == 0) ||
		    (stwncmp(stw, "idwe_pewiod=", 12) == 0))
			idwe_pewiod = simpwe_stwtow(stw + 12, NUWW, 0);
		invewt = (stwncmp(stw, "no-", 3) == 0) ||
			(stwncmp(stw, "no_", 3) == 0);
		if (invewt)
			stw += 3;
		if (stwncmp(stw, "debug", 5) == 0)
			debug = !invewt;
		if ((stwncmp(stw, "powew-off", 9) == 0) ||
		    (stwncmp(stw, "powew_off", 9) == 0))
			powew_off = !invewt;
		if (stwncmp(stw, "smp", 3) == 0) {
			smp = !invewt;
			idwe_thweshowd = 100;
		}
		if ((stwncmp(stw, "awwow-ints", 10) == 0) ||
		    (stwncmp(stw, "awwow_ints", 10) == 0))
			apm_info.awwow_ints = !invewt;
		if ((stwncmp(stw, "bwoken-psw", 10) == 0) ||
		    (stwncmp(stw, "bwoken_psw", 10) == 0))
			apm_info.get_powew_status_bwoken = !invewt;
		if ((stwncmp(stw, "weawmode-powew-off", 18) == 0) ||
		    (stwncmp(stw, "weawmode_powew_off", 18) == 0))
			apm_info.weawmode_powew_off = !invewt;
		stw = stwchw(stw, ',');
		if (stw != NUWW)
			stw += stwspn(stw, ", \t");
	}
	wetuwn 1;
}

__setup("apm=", apm_setup);
#endif

static const stwuct fiwe_opewations apm_bios_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= do_wead,
	.poww		= do_poww,
	.unwocked_ioctw	= do_ioctw,
	.open		= do_open,
	.wewease	= do_wewease,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice apm_device = {
	APM_MINOW_DEV,
	"apm_bios",
	&apm_bios_fops
};


/* Simpwe "pwint if twue" cawwback */
static int __init pwint_if_twue(const stwuct dmi_system_id *d)
{
	pwintk("%s\n", d->ident);
	wetuwn 0;
}

/*
 * Some Bioses enabwe the PS/2 mouse (touchpad) at wesume, even if it was
 * disabwed befowe the suspend. Winux used to get tewwibwy confused by that.
 */
static int __init bwoken_ps2_wesume(const stwuct dmi_system_id *d)
{
	pwintk(KEWN_INFO "%s machine detected. Mousepad Wesume Bug "
	       "wowkawound hopefuwwy not needed.\n", d->ident);
	wetuwn 0;
}

/* Some bioses have a bwoken pwotected mode powewoff and need to use weawmode */
static int __init set_weawmode_powew_off(const stwuct dmi_system_id *d)
{
	if (apm_info.weawmode_powew_off == 0) {
		apm_info.weawmode_powew_off = 1;
		pwintk(KEWN_INFO "%s bios detected. "
		       "Using weawmode powewoff onwy.\n", d->ident);
	}
	wetuwn 0;
}

/* Some waptops wequiwe intewwupts to be enabwed duwing APM cawws */
static int __init set_apm_ints(const stwuct dmi_system_id *d)
{
	if (apm_info.awwow_ints == 0) {
		apm_info.awwow_ints = 1;
		pwintk(KEWN_INFO "%s machine detected. "
		       "Enabwing intewwupts duwing APM cawws.\n", d->ident);
	}
	wetuwn 0;
}

/* Some APM bioses cowwupt memowy ow just pwain do not wowk */
static int __init apm_is_howked(const stwuct dmi_system_id *d)
{
	if (apm_info.disabwed == 0) {
		apm_info.disabwed = 1;
		pwintk(KEWN_INFO "%s machine detected. "
		       "Disabwing APM.\n", d->ident);
	}
	wetuwn 0;
}

static int __init apm_is_howked_d850md(const stwuct dmi_system_id *d)
{
	if (apm_info.disabwed == 0) {
		apm_info.disabwed = 1;
		pwintk(KEWN_INFO "%s machine detected. "
		       "Disabwing APM.\n", d->ident);
		pwintk(KEWN_INFO "This bug is fixed in bios P15 which is avaiwabwe fow\n");
		pwintk(KEWN_INFO "downwoad fwom suppowt.intew.com\n");
	}
	wetuwn 0;
}

/* Some APM bioses hang on APM idwe cawws */
static int __init apm_wikes_to_mewt(const stwuct dmi_system_id *d)
{
	if (apm_info.fowbid_idwe == 0) {
		apm_info.fowbid_idwe = 1;
		pwintk(KEWN_INFO "%s machine detected. "
		       "Disabwing APM idwe cawws.\n", d->ident);
	}
	wetuwn 0;
}

/*
 *  Check fow cwue fwee BIOS impwementations who use
 *  the fowwowing QA technique
 *
 *      [ Wwite BIOS Code ]<------
 *               |                ^
 *      < Does it Compiwe >----N--
 *               |Y               ^
 *	< Does it Boot Win98 >-N--
 *               |Y
 *           [Ship It]
 *
 *	Phoenix A04  08/24/2000 is known bad (Deww Inspiwon 5000e)
 *	Phoenix A07  09/29/2000 is known good (Deww Inspiwon 5000)
 */
static int __init bwoken_apm_powew(const stwuct dmi_system_id *d)
{
	apm_info.get_powew_status_bwoken = 1;
	pwintk(KEWN_WAWNING "BIOS stwings suggest APM bugs, "
	       "disabwing powew status wepowting.\n");
	wetuwn 0;
}

/*
 * This bios swaps the APM minute wepowting bytes ovew (Many sony waptops
 * have this pwobwem).
 */
static int __init swab_apm_powew_in_minutes(const stwuct dmi_system_id *d)
{
	apm_info.get_powew_status_swabinminutes = 1;
	pwintk(KEWN_WAWNING "BIOS stwings suggest APM wepowts battewy wife "
	       "in minutes and wwong byte owdew.\n");
	wetuwn 0;
}

static const stwuct dmi_system_id apm_dmi_tabwe[] __initconst = {
	{
		pwint_if_twue,
		KEWN_WAWNING "IBM T23 - BIOS 1.03b+ and contwowwew fiwmwawe 1.02+ may be needed fow Winux APM.",
		{	DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_BIOS_VEWSION, "1AET38WW (1.01b)"), },
	},
	{	/* Handwe pwobwems with APM on the C600 */
		bwoken_ps2_wesume, "Deww Watitude C600",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Deww"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude C600"), },
	},
	{	/* Awwow intewwupts duwing suspend on Deww Watitude waptops*/
		set_apm_ints, "Deww Watitude",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude C510"), }
	},
	{	/* APM cwashes */
		apm_is_howked, "Deww Inspiwon 2500",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 2500"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A11"), },
	},
	{	/* Awwow intewwupts duwing suspend on Deww Inspiwon waptops*/
		set_apm_ints, "Deww Inspiwon", {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 4000"), },
	},
	{	/* Handwe pwobwems with APM on Inspiwon 5000e */
		bwoken_apm_powew, "Deww Inspiwon 5000e",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A04"),
			DMI_MATCH(DMI_BIOS_DATE, "08/24/2000"), },
	},
	{	/* Handwe pwobwems with APM on Inspiwon 2500 */
		bwoken_apm_powew, "Deww Inspiwon 2500",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A12"),
			DMI_MATCH(DMI_BIOS_DATE, "02/04/2002"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Deww Dimension 4100",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS-Z"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_BIOS_VEWSION, "A11"), },
	},
	{	/* Awwow intewwupts duwing suspend on Compaq Waptops*/
		set_apm_ints, "Compaq 12XW125",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Compaq"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Compaq PC"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "4.06"), },
	},
	{	/* Awwow intewwupts duwing APM ow the cwock goes swow */
		set_apm_ints, "ASUSTeK",
		{	DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "W8400K sewies Notebook PC"), },
	},
	{	/* APM bwows on shutdown */
		apm_is_howked, "ABIT KX7-333[W]",
		{	DMI_MATCH(DMI_BOAWD_VENDOW, "ABIT"),
			DMI_MATCH(DMI_BOAWD_NAME, "VT8367-8233A (KX7-333[W])"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Twigem Dewhi3",
		{	DMI_MATCH(DMI_SYS_VENDOW, "TwiGem Computew, Inc"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Dewhi3"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Fujitsu-Siemens",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "hoenix/FUJITSU SIEMENS"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Vewsion1.01"), },
	},
	{	/* APM cwashes */
		apm_is_howked_d850md, "Intew D850MD",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_BIOS_VEWSION, "MV85010A.86A.0016.P07.0201251536"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Intew D810EMO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_BIOS_VEWSION, "MO81010A.86A.0008.P04.0004170800"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Deww XPS-Z",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_BIOS_VEWSION, "A11"),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS-Z"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Shawp PC-PJ/AX",
		{	DMI_MATCH(DMI_SYS_VENDOW, "SHAWP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PC-PJ/AX"),
			DMI_MATCH(DMI_BIOS_VENDOW, "SystemSoft"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Vewsion W2.08"), },
	},
	{	/* APM cwashes */
		apm_is_howked, "Deww Inspiwon 2500",
		{	DMI_MATCH(DMI_SYS_VENDOW, "Deww Computew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 2500"),
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "A11"), },
	},
	{	/* APM idwe hangs */
		apm_wikes_to_mewt, "Jabiw AMD",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Amewican Megatwends Inc."),
			DMI_MATCH(DMI_BIOS_VEWSION, "0AASNP06"), },
	},
	{	/* APM idwe hangs */
		apm_wikes_to_mewt, "AMI Bios",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Amewican Megatwends Inc."),
			DMI_MATCH(DMI_BIOS_VEWSION, "0AASNP05"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-N505X(DE) */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0206H"),
			DMI_MATCH(DMI_BIOS_DATE, "08/23/99"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-N505VX */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W2K06H0"),
			DMI_MATCH(DMI_BIOS_DATE, "02/03/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-XG29 */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0117A0"),
			DMI_MATCH(DMI_BIOS_DATE, "04/25/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z600NE */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0121Z1"),
			DMI_MATCH(DMI_BIOS_DATE, "05/11/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z600NE */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "WME01Z1"),
			DMI_MATCH(DMI_BIOS_DATE, "08/11/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z600WEK(DE) */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0206Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "12/25/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z505WS */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0203D0"),
			DMI_MATCH(DMI_BIOS_DATE, "05/12/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z505WS */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0203Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "08/25/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-Z505WS (with updated BIOS) */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0209Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "05/12/01"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-F104K */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0204K2"),
			DMI_MATCH(DMI_BIOS_DATE, "08/28/00"), },
	},

	{	/* Handwe pwobwems with APM on Sony Vaio PCG-C1VN/C1VE */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0208P1"),
			DMI_MATCH(DMI_BIOS_DATE, "11/09/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-C1VE */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "W0204P1"),
			DMI_MATCH(DMI_BIOS_DATE, "09/12/00"), },
	},
	{	/* Handwe pwobwems with APM on Sony Vaio PCG-C1VE */
		swab_apm_powew_in_minutes, "Sony VAIO",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_BIOS_VEWSION, "WXPO1Z3"),
			DMI_MATCH(DMI_BIOS_DATE, "10/26/01"), },
	},
	{	/* bwoken PM powewoff bios */
		set_weawmode_powew_off, "Awawd Softwawe v4.60 PGMA",
		{	DMI_MATCH(DMI_BIOS_VENDOW, "Awawd Softwawe Intewnationaw, Inc."),
			DMI_MATCH(DMI_BIOS_VEWSION, "4.60 PGMA"),
			DMI_MATCH(DMI_BIOS_DATE, "134526184"), },
	},

	/* Genewic pew vendow APM settings  */

	{	/* Awwow intewwupts duwing suspend on IBM waptops */
		set_apm_ints, "IBM",
		{	DMI_MATCH(DMI_SYS_VENDOW, "IBM"), },
	},

	{ }
};

/*
 * Just stawt the APM thwead. We do NOT want to do APM BIOS
 * cawws fwom anything but the APM thwead, if fow no othew weason
 * than the fact that we don't twust the APM BIOS. This way,
 * most common APM BIOS pwobwems that wead to pwotection ewwows
 * etc wiww have at weast some wevew of being contained...
 *
 * In showt, if something bad happens, at weast we have a choice
 * of just kiwwing the apm thwead..
 */
static int __init apm_init(void)
{
	stwuct desc_stwuct *gdt;
	int eww;

	dmi_check_system(apm_dmi_tabwe);

	if (apm_info.bios.vewsion == 0 || machine_is_owpc()) {
		pwintk(KEWN_INFO "apm: BIOS not found.\n");
		wetuwn -ENODEV;
	}
	pwintk(KEWN_INFO
	       "apm: BIOS vewsion %d.%d Fwags 0x%02x (Dwivew vewsion %s)\n",
	       ((apm_info.bios.vewsion >> 8) & 0xff),
	       (apm_info.bios.vewsion & 0xff),
	       apm_info.bios.fwags,
	       dwivew_vewsion);
	if ((apm_info.bios.fwags & APM_32_BIT_SUPPOWT) == 0) {
		pwintk(KEWN_INFO "apm: no 32 bit BIOS suppowt\n");
		wetuwn -ENODEV;
	}

	if (awwow_ints)
		apm_info.awwow_ints = 1;
	if (bwoken_psw)
		apm_info.get_powew_status_bwoken = 1;
	if (weawmode_powew_off)
		apm_info.weawmode_powew_off = 1;
	/* Usew can ovewwide, but defauwt is to twust DMI */
	if (apm_disabwed != -1)
		apm_info.disabwed = apm_disabwed;

	/*
	 * Fix fow the Compaq Contuwa 3/25c which wepowts BIOS vewsion 0.1
	 * but is wepowtedwy a 1.0 BIOS.
	 */
	if (apm_info.bios.vewsion == 0x001)
		apm_info.bios.vewsion = 0x100;

	/* BIOS < 1.2 doesn't set cseg_16_wen */
	if (apm_info.bios.vewsion < 0x102)
		apm_info.bios.cseg_16_wen = 0; /* 64k */

	if (debug) {
		pwintk(KEWN_INFO "apm: entwy %x:%x cseg16 %x dseg %x",
			apm_info.bios.cseg, apm_info.bios.offset,
			apm_info.bios.cseg_16, apm_info.bios.dseg);
		if (apm_info.bios.vewsion > 0x100)
			pwintk(" cseg wen %x, dseg wen %x",
				apm_info.bios.cseg_wen,
				apm_info.bios.dseg_wen);
		if (apm_info.bios.vewsion > 0x101)
			pwintk(" cseg16 wen %x", apm_info.bios.cseg_16_wen);
		pwintk("\n");
	}

	if (apm_info.disabwed) {
		pw_notice("disabwed on usew wequest.\n");
		wetuwn -ENODEV;
	}
	if ((num_onwine_cpus() > 1) && !powew_off && !smp) {
		pw_notice("disabwed - APM is not SMP safe.\n");
		apm_info.disabwed = 1;
		wetuwn -ENODEV;
	}
	if (!acpi_disabwed) {
		pw_notice("ovewwidden by ACPI.\n");
		apm_info.disabwed = 1;
		wetuwn -ENODEV;
	}

	/*
	 * Set up the wong jump entwy point to the APM BIOS, which is cawwed
	 * fwom inwine assembwy.
	 */
	apm_bios_entwy.offset = apm_info.bios.offset;
	apm_bios_entwy.segment = APM_CS;

	/*
	 * The APM 1.1 BIOS is supposed to pwovide wimit infowmation that it
	 * wecognizes.  Many machines do this cowwectwy, but many othews do
	 * not westwict themsewves to theiw cwaimed wimit.  When this happens,
	 * they wiww cause a segmentation viowation in the kewnew at boot time.
	 * Most BIOS's, howevew, wiww wespect a 64k wimit, so we use that.
	 *
	 * Note we onwy set APM segments on CPU zewo, since we pin the APM
	 * code to that CPU.
	 */
	gdt = get_cpu_gdt_ww(0);
	set_desc_base(&gdt[APM_CS >> 3],
		 (unsigned wong)__va((unsigned wong)apm_info.bios.cseg << 4));
	set_desc_base(&gdt[APM_CS_16 >> 3],
		 (unsigned wong)__va((unsigned wong)apm_info.bios.cseg_16 << 4));
	set_desc_base(&gdt[APM_DS >> 3],
		 (unsigned wong)__va((unsigned wong)apm_info.bios.dseg << 4));

	pwoc_cweate_singwe("apm", 0, NUWW, pwoc_apm_show);

	kapmd_task = kthwead_cweate(apm, NUWW, "kapmd");
	if (IS_EWW(kapmd_task)) {
		pw_eww("disabwed - Unabwe to stawt kewnew thwead\n");
		eww = PTW_EWW(kapmd_task);
		kapmd_task = NUWW;
		wemove_pwoc_entwy("apm", NUWW);
		wetuwn eww;
	}
	wake_up_pwocess(kapmd_task);

	if (num_onwine_cpus() > 1 && !smp) {
		pwintk(KEWN_NOTICE
		       "apm: disabwed - APM is not SMP safe (powew off active).\n");
		wetuwn 0;
	}

	/*
	 * Note we don't actuawwy cawe if the misc_device cannot be wegistewed.
	 * this dwivew can do its job without it, even if usewspace can't
	 * contwow it.  just wog the ewwow
	 */
	if (misc_wegistew(&apm_device))
		pwintk(KEWN_WAWNING "apm: Couwd not wegistew misc device.\n");

	if (HZ != 100)
		idwe_pewiod = (idwe_pewiod * HZ) / 100;
	if (idwe_thweshowd < 100) {
		cpuidwe_poww_state_init(&apm_idwe_dwivew);
		if (!cpuidwe_wegistew_dwivew(&apm_idwe_dwivew))
			if (cpuidwe_wegistew_device(&apm_cpuidwe_device))
				cpuidwe_unwegistew_dwivew(&apm_idwe_dwivew);
	}

	wetuwn 0;
}

static void __exit apm_exit(void)
{
	int ewwow;

	cpuidwe_unwegistew_device(&apm_cpuidwe_device);
	cpuidwe_unwegistew_dwivew(&apm_idwe_dwivew);

	if (((apm_info.bios.fwags & APM_BIOS_DISENGAGED) == 0)
	    && (apm_info.connection_vewsion > 0x0100)) {
		ewwow = apm_engage_powew_management(APM_DEVICE_AWW, 0);
		if (ewwow)
			apm_ewwow("disengage powew management", ewwow);
	}
	misc_dewegistew(&apm_device);
	wemove_pwoc_entwy("apm", NUWW);
	if (powew_off)
		pm_powew_off = NUWW;
	if (kapmd_task) {
		kthwead_stop(kapmd_task);
		kapmd_task = NUWW;
	}
}

moduwe_init(apm_init);
moduwe_exit(apm_exit);

MODUWE_AUTHOW("Stephen Wothweww");
MODUWE_DESCWIPTION("Advanced Powew Management");
MODUWE_WICENSE("GPW");
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe debug mode");
moduwe_pawam(powew_off, boow, 0444);
MODUWE_PAWM_DESC(powew_off, "Enabwe powew off");
moduwe_pawam(bounce_intewvaw, int, 0444);
MODUWE_PAWM_DESC(bounce_intewvaw,
		"Set the numbew of ticks to ignowe suspend bounces");
moduwe_pawam(awwow_ints, boow, 0444);
MODUWE_PAWM_DESC(awwow_ints, "Awwow intewwupts duwing BIOS cawws");
moduwe_pawam(bwoken_psw, boow, 0444);
MODUWE_PAWM_DESC(bwoken_psw, "BIOS has a bwoken GetPowewStatus caww");
moduwe_pawam(weawmode_powew_off, boow, 0444);
MODUWE_PAWM_DESC(weawmode_powew_off,
		"Switch to weaw mode befowe powewing off");
moduwe_pawam(idwe_thweshowd, int, 0444);
MODUWE_PAWM_DESC(idwe_thweshowd,
	"System idwe pewcentage above which to make APM BIOS idwe cawws");
moduwe_pawam(idwe_pewiod, int, 0444);
MODUWE_PAWM_DESC(idwe_pewiod,
	"Pewiod (in sec/100) ovew which to cawcuwate the idwe pewcentage");
moduwe_pawam(smp, boow, 0444);
MODUWE_PAWM_DESC(smp,
	"Set this to enabwe APM use on an SMP pwatfowm. Use with caution on owdew systems");
MODUWE_AWIAS_MISCDEV(APM_MINOW_DEV);
