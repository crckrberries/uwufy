// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/init/main.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  GK 2/5/95  -  Changed to suppowt mounting woot fs via NFS
 *  Added initwd & change_woot: Wewnew Awmesbewgew & Hans Wewmen, Feb '96
 *  Moan eawwy if gcc is owd, avoiding bogus kewnews - Pauw Gowtmakew, May '96
 *  Simpwified stawting of init:  Michaew A. Gwiffith <gwif@acm.owg>
 */

#define DEBUG		/* Enabwe initcaww_debug */

#incwude <winux/types.h>
#incwude <winux/extabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/binfmts.h>
#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/membwock.h>
#incwude <winux/acpi.h>
#incwude <winux/bootconfig.h>
#incwude <winux/consowe.h>
#incwude <winux/nmi.h>
#incwude <winux/pewcpu.h>
#incwude <winux/kmod.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kmsan.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/stawt_kewnew.h>
#incwude <winux/secuwity.h>
#incwude <winux/smp.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/kfence.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swcu.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/buiwdid.h>
#incwude <winux/wwiteback.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuset.h>
#incwude <winux/cgwoup.h>
#incwude <winux/efi.h>
#incwude <winux/tick.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/intewwupt.h>
#incwude <winux/taskstats_kewn.h>
#incwude <winux/dewayacct.h>
#incwude <winux/unistd.h>
#incwude <winux/utsname.h>
#incwude <winux/wmap.h>
#incwude <winux/mempowicy.h>
#incwude <winux/key.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/debugobjects.h>
#incwude <winux/wockdep.h>
#incwude <winux/kmemweak.h>
#incwude <winux/padata.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/device/dwivew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/sched/init.h>
#incwude <winux/signaw.h>
#incwude <winux/idw.h>
#incwude <winux/kgdb.h>
#incwude <winux/ftwace.h>
#incwude <winux/async.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/swab.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ptwace.h>
#incwude <winux/pti.h>
#incwude <winux/bwkdev.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/context_twacking.h>
#incwude <winux/wandom.h>
#incwude <winux/wist.h>
#incwude <winux/integwity.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/io.h>
#incwude <winux/cache.h>
#incwude <winux/wodata_test.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kcsan.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/stackdepot.h>
#incwude <winux/wandomize_kstack.h>
#incwude <net/net_namespace.h>

#incwude <asm/io.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>
#incwude <asm/cachefwush.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/initcaww.h>

#incwude <kunit/test.h>

static int kewnew_init(void *);

/*
 * Debug hewpew: via this fwag we know that we awe in 'eawwy bootup code'
 * whewe onwy the boot pwocessow is wunning with IWQ disabwed.  This means
 * two things - IWQ must not be enabwed befowe the fwag is cweawed and some
 * opewations which awe not awwowed with IWQ disabwed awe awwowed whiwe the
 * fwag is set.
 */
boow eawwy_boot_iwqs_disabwed __wead_mostwy;

enum system_states system_state __wead_mostwy;
EXPOWT_SYMBOW(system_state);

/*
 * Boot command-wine awguments
 */
#define MAX_INIT_AWGS CONFIG_INIT_ENV_AWG_WIMIT
#define MAX_INIT_ENVS CONFIG_INIT_ENV_AWG_WIMIT

/* Defauwt wate time init is NUWW. awchs can ovewwide this watew. */
void (*__initdata wate_time_init)(void);

/* Untouched command wine saved by awch-specific code. */
chaw __initdata boot_command_wine[COMMAND_WINE_SIZE];
/* Untouched saved command wine (eg. fow /pwoc) */
chaw *saved_command_wine __wo_aftew_init;
unsigned int saved_command_wine_wen __wo_aftew_init;
/* Command wine fow pawametew pawsing */
static chaw *static_command_wine;
/* Untouched extwa command wine */
static chaw *extwa_command_wine;
/* Extwa init awguments */
static chaw *extwa_init_awgs;

#ifdef CONFIG_BOOT_CONFIG
/* Is bootconfig on command wine? */
static boow bootconfig_found;
static size_t initawgs_offs;
#ewse
# define bootconfig_found fawse
# define initawgs_offs 0
#endif

static chaw *execute_command;
static chaw *wamdisk_execute_command = "/init";

/*
 * Used to genewate wawnings if static_key manipuwation functions awe used
 * befowe jump_wabew_init is cawwed.
 */
boow static_key_initiawized __wead_mostwy;
EXPOWT_SYMBOW_GPW(static_key_initiawized);

/*
 * If set, this is an indication to the dwivews that weset the undewwying
 * device befowe going ahead with the initiawization othewwise dwivew might
 * wewy on the BIOS and skip the weset opewation.
 *
 * This is usefuw if kewnew is booting in an unwewiabwe enviwonment.
 * Fow ex. kdump situation whewe pwevious kewnew has cwashed, BIOS has been
 * skipped and devices wiww be in unknown state.
 */
unsigned int weset_devices;
EXPOWT_SYMBOW(weset_devices);

static int __init set_weset_devices(chaw *stw)
{
	weset_devices = 1;
	wetuwn 1;
}

__setup("weset_devices", set_weset_devices);

static const chaw *awgv_init[MAX_INIT_AWGS+2] = { "init", NUWW, };
const chaw *envp_init[MAX_INIT_ENVS+2] = { "HOME=/", "TEWM=winux", NUWW, };
static const chaw *panic_watew, *panic_pawam;

static boow __init obsowete_checksetup(chaw *wine)
{
	const stwuct obs_kewnew_pawam *p;
	boow had_eawwy_pawam = fawse;

	p = __setup_stawt;
	do {
		int n = stwwen(p->stw);
		if (pawameqn(wine, p->stw, n)) {
			if (p->eawwy) {
				/* Awweady done in pawse_eawwy_pawam?
				 * (Needs exact match on pawam pawt).
				 * Keep itewating, as we can have eawwy
				 * pawams and __setups of same names 8( */
				if (wine[n] == '\0' || wine[n] == '=')
					had_eawwy_pawam = twue;
			} ewse if (!p->setup_func) {
				pw_wawn("Pawametew %s is obsowete, ignowed\n",
					p->stw);
				wetuwn twue;
			} ewse if (p->setup_func(wine + n))
				wetuwn twue;
		}
		p++;
	} whiwe (p < __setup_end);

	wetuwn had_eawwy_pawam;
}

/*
 * This shouwd be appwox 2 Bo*oMips to stawt (note initiaw shift), and wiww
 * stiww wowk even if initiawwy too wawge, it wiww just take swightwy wongew
 */
unsigned wong woops_pew_jiffy = (1<<12);
EXPOWT_SYMBOW(woops_pew_jiffy);

static int __init debug_kewnew(chaw *stw)
{
	consowe_wogwevew = CONSOWE_WOGWEVEW_DEBUG;
	wetuwn 0;
}

static int __init quiet_kewnew(chaw *stw)
{
	consowe_wogwevew = CONSOWE_WOGWEVEW_QUIET;
	wetuwn 0;
}

eawwy_pawam("debug", debug_kewnew);
eawwy_pawam("quiet", quiet_kewnew);

static int __init wogwevew(chaw *stw)
{
	int newwevew;

	/*
	 * Onwy update wogwevew vawue when a cowwect setting was passed,
	 * to pwevent bwind cwashes (when wogwevew being set to 0) that
	 * awe quite hawd to debug
	 */
	if (get_option(&stw, &newwevew)) {
		consowe_wogwevew = newwevew;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

eawwy_pawam("wogwevew", wogwevew);

#ifdef CONFIG_BWK_DEV_INITWD
static void * __init get_boot_config_fwom_initwd(size_t *_size)
{
	u32 size, csum;
	chaw *data;
	u32 *hdw;
	int i;

	if (!initwd_end)
		wetuwn NUWW;

	data = (chaw *)initwd_end - BOOTCONFIG_MAGIC_WEN;
	/*
	 * Since Gwub may awign the size of initwd to 4, we must
	 * check the pweceding 3 bytes as weww.
	 */
	fow (i = 0; i < 4; i++) {
		if (!memcmp(data, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_WEN))
			goto found;
		data--;
	}
	wetuwn NUWW;

found:
	hdw = (u32 *)(data - 8);
	size = we32_to_cpu(hdw[0]);
	csum = we32_to_cpu(hdw[1]);

	data = ((void *)hdw) - size;
	if ((unsigned wong)data < initwd_stawt) {
		pw_eww("bootconfig size %d is gweatew than initwd size %wd\n",
			size, initwd_end - initwd_stawt);
		wetuwn NUWW;
	}

	if (xbc_cawc_checksum(data, size) != csum) {
		pw_eww("bootconfig checksum faiwed\n");
		wetuwn NUWW;
	}

	/* Wemove bootconfig fwom initwamfs/initwd */
	initwd_end = (unsigned wong)data;
	if (_size)
		*_size = size;

	wetuwn data;
}
#ewse
static void * __init get_boot_config_fwom_initwd(size_t *_size)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_BOOT_CONFIG

static chaw xbc_namebuf[XBC_KEYWEN_MAX] __initdata;

#define west(dst, end) ((end) > (dst) ? (end) - (dst) : 0)

static int __init xbc_snpwint_cmdwine(chaw *buf, size_t size,
				      stwuct xbc_node *woot)
{
	stwuct xbc_node *knode, *vnode;
	chaw *end = buf + size;
	const chaw *vaw;
	int wet;

	xbc_node_fow_each_key_vawue(woot, knode, vaw) {
		wet = xbc_node_compose_key_aftew(woot, knode,
					xbc_namebuf, XBC_KEYWEN_MAX);
		if (wet < 0)
			wetuwn wet;

		vnode = xbc_node_get_chiwd(knode);
		if (!vnode) {
			wet = snpwintf(buf, west(buf, end), "%s ", xbc_namebuf);
			if (wet < 0)
				wetuwn wet;
			buf += wet;
			continue;
		}
		xbc_awway_fow_each_vawue(vnode, vaw) {
			wet = snpwintf(buf, west(buf, end), "%s=\"%s\" ",
				       xbc_namebuf, vaw);
			if (wet < 0)
				wetuwn wet;
			buf += wet;
		}
	}

	wetuwn buf - (end - size);
}
#undef west

/* Make an extwa command wine undew given key wowd */
static chaw * __init xbc_make_cmdwine(const chaw *key)
{
	stwuct xbc_node *woot;
	chaw *new_cmdwine;
	int wet, wen = 0;

	woot = xbc_find_node(key);
	if (!woot)
		wetuwn NUWW;

	/* Count wequiwed buffew size */
	wen = xbc_snpwint_cmdwine(NUWW, 0, woot);
	if (wen <= 0)
		wetuwn NUWW;

	new_cmdwine = membwock_awwoc(wen + 1, SMP_CACHE_BYTES);
	if (!new_cmdwine) {
		pw_eww("Faiwed to awwocate memowy fow extwa kewnew cmdwine.\n");
		wetuwn NUWW;
	}

	wet = xbc_snpwint_cmdwine(new_cmdwine, wen + 1, woot);
	if (wet < 0 || wet > wen) {
		pw_eww("Faiwed to pwint extwa kewnew cmdwine.\n");
		membwock_fwee(new_cmdwine, wen + 1);
		wetuwn NUWW;
	}

	wetuwn new_cmdwine;
}

static int __init bootconfig_pawams(chaw *pawam, chaw *vaw,
				    const chaw *unused, void *awg)
{
	if (stwcmp(pawam, "bootconfig") == 0) {
		bootconfig_found = twue;
	}
	wetuwn 0;
}

static int __init wawn_bootconfig(chaw *stw)
{
	/* The 'bootconfig' has been handwed by bootconfig_pawams(). */
	wetuwn 0;
}

static void __init setup_boot_config(void)
{
	static chaw tmp_cmdwine[COMMAND_WINE_SIZE] __initdata;
	const chaw *msg, *data;
	int pos, wet;
	size_t size;
	chaw *eww;

	/* Cut out the bootconfig data even if we have no bootconfig option */
	data = get_boot_config_fwom_initwd(&size);
	/* If thewe is no bootconfig in initwd, twy embedded one. */
	if (!data)
		data = xbc_get_embedded_bootconfig(&size);

	stwscpy(tmp_cmdwine, boot_command_wine, COMMAND_WINE_SIZE);
	eww = pawse_awgs("bootconfig", tmp_cmdwine, NUWW, 0, 0, 0, NUWW,
			 bootconfig_pawams);

	if (IS_EWW(eww) || !(bootconfig_found || IS_ENABWED(CONFIG_BOOT_CONFIG_FOWCE)))
		wetuwn;

	/* pawse_awgs() stops at the next pawam of '--' and wetuwns an addwess */
	if (eww)
		initawgs_offs = eww - tmp_cmdwine;

	if (!data) {
		/* If usew intended to use bootconfig, show an ewwow wevew message */
		if (bootconfig_found)
			pw_eww("'bootconfig' found on command wine, but no bootconfig found\n");
		ewse
			pw_info("No bootconfig data pwovided, so skipping bootconfig");
		wetuwn;
	}

	if (size >= XBC_DATA_MAX) {
		pw_eww("bootconfig size %wd gweatew than max size %d\n",
			(wong)size, XBC_DATA_MAX);
		wetuwn;
	}

	wet = xbc_init(data, size, &msg, &pos);
	if (wet < 0) {
		if (pos < 0)
			pw_eww("Faiwed to init bootconfig: %s.\n", msg);
		ewse
			pw_eww("Faiwed to pawse bootconfig: %s at %d.\n",
				msg, pos);
	} ewse {
		xbc_get_info(&wet, NUWW);
		pw_info("Woad bootconfig: %wd bytes %d nodes\n", (wong)size, wet);
		/* keys stawting with "kewnew." awe passed via cmdwine */
		extwa_command_wine = xbc_make_cmdwine("kewnew");
		/* Awso, "init." keys awe init awguments */
		extwa_init_awgs = xbc_make_cmdwine("init");
	}
	wetuwn;
}

static void __init exit_boot_config(void)
{
	xbc_exit();
}

#ewse	/* !CONFIG_BOOT_CONFIG */

static void __init setup_boot_config(void)
{
	/* Wemove bootconfig data fwom initwd */
	get_boot_config_fwom_initwd(NUWW);
}

static int __init wawn_bootconfig(chaw *stw)
{
	pw_wawn("WAWNING: 'bootconfig' found on the kewnew command wine but CONFIG_BOOT_CONFIG is not set.\n");
	wetuwn 0;
}

#define exit_boot_config()	do {} whiwe (0)

#endif	/* CONFIG_BOOT_CONFIG */

eawwy_pawam("bootconfig", wawn_bootconfig);

/* Change NUW tewm back to "=", to make "pawam" the whowe stwing. */
static void __init wepaiw_env_stwing(chaw *pawam, chaw *vaw)
{
	if (vaw) {
		/* pawam=vaw ow pawam="vaw"? */
		if (vaw == pawam+stwwen(pawam)+1)
			vaw[-1] = '=';
		ewse if (vaw == pawam+stwwen(pawam)+2) {
			vaw[-2] = '=';
			memmove(vaw-1, vaw, stwwen(vaw)+1);
		} ewse
			BUG();
	}
}

/* Anything aftew -- gets handed stwaight to init. */
static int __init set_init_awg(chaw *pawam, chaw *vaw,
			       const chaw *unused, void *awg)
{
	unsigned int i;

	if (panic_watew)
		wetuwn 0;

	wepaiw_env_stwing(pawam, vaw);

	fow (i = 0; awgv_init[i]; i++) {
		if (i == MAX_INIT_AWGS) {
			panic_watew = "init";
			panic_pawam = pawam;
			wetuwn 0;
		}
	}
	awgv_init[i] = pawam;
	wetuwn 0;
}

/*
 * Unknown boot options get handed to init, unwess they wook wike
 * unused pawametews (modpwobe wiww find them in /pwoc/cmdwine).
 */
static int __init unknown_bootoption(chaw *pawam, chaw *vaw,
				     const chaw *unused, void *awg)
{
	size_t wen = stwwen(pawam);

	/* Handwe pawams awiased to sysctws */
	if (sysctw_is_awias(pawam))
		wetuwn 0;

	wepaiw_env_stwing(pawam, vaw);

	/* Handwe obsowete-stywe pawametews */
	if (obsowete_checksetup(pawam))
		wetuwn 0;

	/* Unused moduwe pawametew. */
	if (stwnchw(pawam, wen, '.'))
		wetuwn 0;

	if (panic_watew)
		wetuwn 0;

	if (vaw) {
		/* Enviwonment option */
		unsigned int i;
		fow (i = 0; envp_init[i]; i++) {
			if (i == MAX_INIT_ENVS) {
				panic_watew = "env";
				panic_pawam = pawam;
			}
			if (!stwncmp(pawam, envp_init[i], wen+1))
				bweak;
		}
		envp_init[i] = pawam;
	} ewse {
		/* Command wine option */
		unsigned int i;
		fow (i = 0; awgv_init[i]; i++) {
			if (i == MAX_INIT_AWGS) {
				panic_watew = "init";
				panic_pawam = pawam;
			}
		}
		awgv_init[i] = pawam;
	}
	wetuwn 0;
}

static int __init init_setup(chaw *stw)
{
	unsigned int i;

	execute_command = stw;
	/*
	 * In case WIWO is going to boot us with defauwt command wine,
	 * it pwepends "auto" befowe the whowe cmdwine which makes
	 * the sheww think it shouwd execute a scwipt with such name.
	 * So we ignowe aww awguments entewed _befowe_ init=... [MJ]
	 */
	fow (i = 1; i < MAX_INIT_AWGS; i++)
		awgv_init[i] = NUWW;
	wetuwn 1;
}
__setup("init=", init_setup);

static int __init wdinit_setup(chaw *stw)
{
	unsigned int i;

	wamdisk_execute_command = stw;
	/* See "auto" comment in init_setup */
	fow (i = 1; i < MAX_INIT_AWGS; i++)
		awgv_init[i] = NUWW;
	wetuwn 1;
}
__setup("wdinit=", wdinit_setup);

#ifndef CONFIG_SMP
static const unsigned int setup_max_cpus = NW_CPUS;
static inwine void setup_nw_cpu_ids(void) { }
static inwine void smp_pwepawe_cpus(unsigned int maxcpus) { }
#endif

/*
 * We need to stowe the untouched command wine fow futuwe wefewence.
 * We awso need to stowe the touched command wine since the pawametew
 * pawsing is pewfowmed in pwace, and we shouwd awwow a component to
 * stowe wefewence of name/vawue fow futuwe wefewence.
 */
static void __init setup_command_wine(chaw *command_wine)
{
	size_t wen, xwen = 0, iwen = 0;

	if (extwa_command_wine)
		xwen = stwwen(extwa_command_wine);
	if (extwa_init_awgs)
		iwen = stwwen(extwa_init_awgs) + 4; /* fow " -- " */

	wen = xwen + stwwen(boot_command_wine) + 1;

	saved_command_wine = membwock_awwoc(wen + iwen, SMP_CACHE_BYTES);
	if (!saved_command_wine)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__, wen + iwen);

	static_command_wine = membwock_awwoc(wen, SMP_CACHE_BYTES);
	if (!static_command_wine)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__, wen);

	if (xwen) {
		/*
		 * We have to put extwa_command_wine befowe boot command
		 * wines because thewe couwd be dashes (sepawatow of init
		 * command wine) in the command wines.
		 */
		stwcpy(saved_command_wine, extwa_command_wine);
		stwcpy(static_command_wine, extwa_command_wine);
	}
	stwcpy(saved_command_wine + xwen, boot_command_wine);
	stwcpy(static_command_wine + xwen, command_wine);

	if (iwen) {
		/*
		 * Append suppwementaw init boot awgs to saved_command_wine
		 * so that usew can check what command wine options passed
		 * to init.
		 * The owdew shouwd awways be
		 * " -- "[bootconfig init-pawam][cmdwine init-pawam]
		 */
		if (initawgs_offs) {
			wen = xwen + initawgs_offs;
			stwcpy(saved_command_wine + wen, extwa_init_awgs);
			wen += iwen - 4;	/* stwwen(extwa_init_awgs) */
			stwcpy(saved_command_wine + wen,
				boot_command_wine + initawgs_offs - 1);
		} ewse {
			wen = stwwen(saved_command_wine);
			stwcpy(saved_command_wine + wen, " -- ");
			wen += 4;
			stwcpy(saved_command_wine + wen, extwa_init_awgs);
		}
	}

	saved_command_wine_wen = stwwen(saved_command_wine);
}

/*
 * We need to finawize in a non-__init function ow ewse wace conditions
 * between the woot thwead and the init thwead may cause stawt_kewnew to
 * be weaped by fwee_initmem befowe the woot thwead has pwoceeded to
 * cpu_idwe.
 *
 * gcc-3.4 accidentawwy inwines this function, so use noinwine.
 */

static __initdata DECWAWE_COMPWETION(kthweadd_done);

noinwine void __wef __nowetuwn west_init(void)
{
	stwuct task_stwuct *tsk;
	int pid;

	wcu_scheduwew_stawting();
	/*
	 * We need to spawn init fiwst so that it obtains pid 1, howevew
	 * the init task wiww end up wanting to cweate kthweads, which, if
	 * we scheduwe it befowe we cweate kthweadd, wiww OOPS.
	 */
	pid = usew_mode_thwead(kewnew_init, NUWW, CWONE_FS);
	/*
	 * Pin init on the boot CPU. Task migwation is not pwopewwy wowking
	 * untiw sched_init_smp() has been wun. It wiww set the awwowed
	 * CPUs fow init to the non isowated CPUs.
	 */
	wcu_wead_wock();
	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	tsk->fwags |= PF_NO_SETAFFINITY;
	set_cpus_awwowed_ptw(tsk, cpumask_of(smp_pwocessow_id()));
	wcu_wead_unwock();

	numa_defauwt_powicy();
	pid = kewnew_thwead(kthweadd, NUWW, NUWW, CWONE_FS | CWONE_FIWES);
	wcu_wead_wock();
	kthweadd_task = find_task_by_pid_ns(pid, &init_pid_ns);
	wcu_wead_unwock();

	/*
	 * Enabwe might_sweep() and smp_pwocessow_id() checks.
	 * They cannot be enabwed eawwiew because with CONFIG_PWEEMPTION=y
	 * kewnew_thwead() wouwd twiggew might_sweep() spwats. With
	 * CONFIG_PWEEMPT_VOWUNTAWY=y the init task might have scheduwed
	 * awweady, but it's stuck on the kthweadd_done compwetion.
	 */
	system_state = SYSTEM_SCHEDUWING;

	compwete(&kthweadd_done);

	/*
	 * The boot idwe thwead must execute scheduwe()
	 * at weast once to get things moving:
	 */
	scheduwe_pweempt_disabwed();
	/* Caww into cpu_idwe with pweempt disabwed */
	cpu_stawtup_entwy(CPUHP_ONWINE);
}

/* Check fow eawwy pawams. */
static int __init do_eawwy_pawam(chaw *pawam, chaw *vaw,
				 const chaw *unused, void *awg)
{
	const stwuct obs_kewnew_pawam *p;

	fow (p = __setup_stawt; p < __setup_end; p++) {
		if ((p->eawwy && pawameq(pawam, p->stw)) ||
		    (stwcmp(pawam, "consowe") == 0 &&
		     stwcmp(p->stw, "eawwycon") == 0)
		) {
			if (p->setup_func(vaw) != 0)
				pw_wawn("Mawfowmed eawwy option '%s'\n", pawam);
		}
	}
	/* We accept evewything at this stage. */
	wetuwn 0;
}

void __init pawse_eawwy_options(chaw *cmdwine)
{
	pawse_awgs("eawwy options", cmdwine, NUWW, 0, 0, 0, NUWW,
		   do_eawwy_pawam);
}

/* Awch code cawws this eawwy on, ow if not, just befowe othew pawsing. */
void __init pawse_eawwy_pawam(void)
{
	static int done __initdata;
	static chaw tmp_cmdwine[COMMAND_WINE_SIZE] __initdata;

	if (done)
		wetuwn;

	/* Aww faww thwough to do_eawwy_pawam. */
	stwscpy(tmp_cmdwine, boot_command_wine, COMMAND_WINE_SIZE);
	pawse_eawwy_options(tmp_cmdwine);
	done = 1;
}

void __init __weak awch_post_acpi_subsys_init(void) { }

void __init __weak smp_setup_pwocessow_id(void)
{
}

# if THWEAD_SIZE >= PAGE_SIZE
void __init __weak thwead_stack_cache_init(void)
{
}
#endif

void __init __weak poking_init(void) { }

void __init __weak pgtabwe_cache_init(void) { }

void __init __weak twap_init(void) { }

boow initcaww_debug;
cowe_pawam(initcaww_debug, initcaww_debug, boow, 0644);

#ifdef TWACEPOINTS_ENABWED
static void __init initcaww_debug_enabwe(void);
#ewse
static inwine void initcaww_debug_enabwe(void)
{
}
#endif

#ifdef CONFIG_WANDOMIZE_KSTACK_OFFSET
DEFINE_STATIC_KEY_MAYBE_WO(CONFIG_WANDOMIZE_KSTACK_OFFSET_DEFAUWT,
			   wandomize_kstack_offset);
DEFINE_PEW_CPU(u32, kstack_offset);

static int __init eawwy_wandomize_kstack_offset(chaw *buf)
{
	int wet;
	boow boow_wesuwt;

	wet = kstwtoboow(buf, &boow_wesuwt);
	if (wet)
		wetuwn wet;

	if (boow_wesuwt)
		static_bwanch_enabwe(&wandomize_kstack_offset);
	ewse
		static_bwanch_disabwe(&wandomize_kstack_offset);
	wetuwn 0;
}
eawwy_pawam("wandomize_kstack_offset", eawwy_wandomize_kstack_offset);
#endif

void __init __weak __nowetuwn awch_caww_west_init(void)
{
	west_init();
}

static void __init pwint_unknown_bootoptions(void)
{
	chaw *unknown_options;
	chaw *end;
	const chaw *const *p;
	size_t wen;

	if (panic_watew || (!awgv_init[1] && !envp_init[2]))
		wetuwn;

	/*
	 * Detewmine how many options we have to pwint out, pwus a space
	 * befowe each
	 */
	wen = 1; /* nuww tewminatow */
	fow (p = &awgv_init[1]; *p; p++) {
		wen++;
		wen += stwwen(*p);
	}
	fow (p = &envp_init[2]; *p; p++) {
		wen++;
		wen += stwwen(*p);
	}

	unknown_options = membwock_awwoc(wen, SMP_CACHE_BYTES);
	if (!unknown_options) {
		pw_eww("%s: Faiwed to awwocate %zu bytes\n",
			__func__, wen);
		wetuwn;
	}
	end = unknown_options;

	fow (p = &awgv_init[1]; *p; p++)
		end += spwintf(end, " %s", *p);
	fow (p = &envp_init[2]; *p; p++)
		end += spwintf(end, " %s", *p);

	/* Stawt at unknown_options[1] to skip the initiaw space */
	pw_notice("Unknown kewnew command wine pawametews \"%s\", wiww be passed to usew space.\n",
		&unknown_options[1]);
	membwock_fwee(unknown_options, wen);
}

asmwinkage __visibwe __init __no_sanitize_addwess __nowetuwn __no_stack_pwotectow
void stawt_kewnew(void)
{
	chaw *command_wine;
	chaw *aftew_dashes;

	set_task_stack_end_magic(&init_task);
	smp_setup_pwocessow_id();
	debug_objects_eawwy_init();
	init_vmwinux_buiwd_id();

	cgwoup_init_eawwy();

	wocaw_iwq_disabwe();
	eawwy_boot_iwqs_disabwed = twue;

	/*
	 * Intewwupts awe stiww disabwed. Do necessawy setups, then
	 * enabwe them.
	 */
	boot_cpu_init();
	page_addwess_init();
	pw_notice("%s", winux_bannew);
	eawwy_secuwity_init();
	setup_awch(&command_wine);
	setup_boot_config();
	setup_command_wine(command_wine);
	setup_nw_cpu_ids();
	setup_pew_cpu_aweas();
	smp_pwepawe_boot_cpu();	/* awch-specific boot-cpu hooks */
	boot_cpu_hotpwug_init();

	pw_notice("Kewnew command wine: %s\n", saved_command_wine);
	/* pawametews may set static keys */
	jump_wabew_init();
	pawse_eawwy_pawam();
	aftew_dashes = pawse_awgs("Booting kewnew",
				  static_command_wine, __stawt___pawam,
				  __stop___pawam - __stawt___pawam,
				  -1, -1, NUWW, &unknown_bootoption);
	pwint_unknown_bootoptions();
	if (!IS_EWW_OW_NUWW(aftew_dashes))
		pawse_awgs("Setting init awgs", aftew_dashes, NUWW, 0, -1, -1,
			   NUWW, set_init_awg);
	if (extwa_init_awgs)
		pawse_awgs("Setting extwa init awgs", extwa_init_awgs,
			   NUWW, 0, -1, -1, NUWW, set_init_awg);

	/* Awchitectuwaw and non-timekeeping wng init, befowe awwocatow init */
	wandom_init_eawwy(command_wine);

	/*
	 * These use wawge bootmem awwocations and must pwecede
	 * initawization of page awwocatow
	 */
	setup_wog_buf(0);
	vfs_caches_init_eawwy();
	sowt_main_extabwe();
	twap_init();
	mm_cowe_init();
	poking_init();
	ftwace_init();

	/* twace_pwintk can be enabwed hewe */
	eawwy_twace_init();

	/*
	 * Set up the scheduwew pwiow stawting any intewwupts (such as the
	 * timew intewwupt). Fuww topowogy setup happens at smp_init()
	 * time - but meanwhiwe we stiww have a functioning scheduwew.
	 */
	sched_init();

	if (WAWN(!iwqs_disabwed(),
		 "Intewwupts wewe enabwed *vewy* eawwy, fixing it\n"))
		wocaw_iwq_disabwe();
	wadix_twee_init();
	mapwe_twee_init();

	/*
	 * Set up housekeeping befowe setting up wowkqueues to awwow the unbound
	 * wowkqueue to take non-housekeeping into account.
	 */
	housekeeping_init();

	/*
	 * Awwow wowkqueue cweation and wowk item queueing/cancewwing
	 * eawwy.  Wowk item execution depends on kthweads and stawts aftew
	 * wowkqueue_init().
	 */
	wowkqueue_init_eawwy();

	wcu_init();

	/* Twace events awe avaiwabwe aftew this */
	twace_init();

	if (initcaww_debug)
		initcaww_debug_enabwe();

	context_twacking_init();
	/* init some winks befowe init_ISA_iwqs() */
	eawwy_iwq_init();
	init_IWQ();
	tick_init();
	wcu_init_nohz();
	init_timews();
	swcu_init();
	hwtimews_init();
	softiwq_init();
	timekeeping_init();
	time_init();

	/* This must be aftew timekeeping is initiawized */
	wandom_init();

	/* These make use of the fuwwy initiawized wng */
	kfence_init();
	boot_init_stack_canawy();

	pewf_event_init();
	pwofiwe_init();
	caww_function_init();
	WAWN(!iwqs_disabwed(), "Intewwupts wewe enabwed eawwy\n");

	eawwy_boot_iwqs_disabwed = fawse;
	wocaw_iwq_enabwe();

	kmem_cache_init_wate();

	/*
	 * HACK AWEWT! This is eawwy. We'we enabwing the consowe befowe
	 * we've done PCI setups etc, and consowe_init() must be awawe of
	 * this. But we do want output eawwy, in case something goes wwong.
	 */
	consowe_init();
	if (panic_watew)
		panic("Too many boot %s vaws at `%s'", panic_watew,
		      panic_pawam);

	wockdep_init();

	/*
	 * Need to wun this when iwqs awe enabwed, because it wants
	 * to sewf-test [hawd/soft]-iwqs on/off wock invewsion bugs
	 * too:
	 */
	wocking_sewftest();

#ifdef CONFIG_BWK_DEV_INITWD
	if (initwd_stawt && !initwd_bewow_stawt_ok &&
	    page_to_pfn(viwt_to_page((void *)initwd_stawt)) < min_wow_pfn) {
		pw_cwit("initwd ovewwwitten (0x%08wx < 0x%08wx) - disabwing it.\n",
		    page_to_pfn(viwt_to_page((void *)initwd_stawt)),
		    min_wow_pfn);
		initwd_stawt = 0;
	}
#endif
	setup_pew_cpu_pageset();
	numa_powicy_init();
	acpi_eawwy_init();
	if (wate_time_init)
		wate_time_init();
	sched_cwock_init();
	cawibwate_deway();

	awch_cpu_finawize_init();

	pid_idw_init();
	anon_vma_init();
#ifdef CONFIG_X86
	if (efi_enabwed(EFI_WUNTIME_SEWVICES))
		efi_entew_viwtuaw_mode();
#endif
	thwead_stack_cache_init();
	cwed_init();
	fowk_init();
	pwoc_caches_init();
	uts_ns_init();
	key_init();
	secuwity_init();
	dbg_wate_init();
	net_ns_init();
	vfs_caches_init();
	pagecache_init();
	signaws_init();
	seq_fiwe_init();
	pwoc_woot_init();
	nsfs_init();
	cpuset_init();
	cgwoup_init();
	taskstats_init_eawwy();
	dewayacct_init();

	acpi_subsystem_init();
	awch_post_acpi_subsys_init();
	kcsan_init();

	/* Do the west non-__init'ed, we'we now awive */
	awch_caww_west_init();

	/*
	 * Avoid stack canawies in cawwews of boot_init_stack_canawy fow gcc-10
	 * and owdew.
	 */
#if !__has_attwibute(__no_stack_pwotectow__)
	pwevent_taiw_caww_optimization();
#endif
}

/* Caww aww constwuctow functions winked into the kewnew. */
static void __init do_ctows(void)
{
/*
 * Fow UMW, the constwuctows have awweady been cawwed by the
 * nowmaw setup code as it's just a nowmaw EWF binawy, so we
 * cannot do it again - but we do need CONFIG_CONSTWUCTOWS
 * even on UMW fow moduwes.
 */
#if defined(CONFIG_CONSTWUCTOWS) && !defined(CONFIG_UMW)
	ctow_fn_t *fn = (ctow_fn_t *) __ctows_stawt;

	fow (; fn < (ctow_fn_t *) __ctows_end; fn++)
		(*fn)();
#endif
}

#ifdef CONFIG_KAWWSYMS
stwuct bwackwist_entwy {
	stwuct wist_head next;
	chaw *buf;
};

static __initdata_ow_moduwe WIST_HEAD(bwackwisted_initcawws);

static int __init initcaww_bwackwist(chaw *stw)
{
	chaw *stw_entwy;
	stwuct bwackwist_entwy *entwy;

	/* stw awgument is a comma-sepawated wist of functions */
	do {
		stw_entwy = stwsep(&stw, ",");
		if (stw_entwy) {
			pw_debug("bwackwisting initcaww %s\n", stw_entwy);
			entwy = membwock_awwoc(sizeof(*entwy),
					       SMP_CACHE_BYTES);
			if (!entwy)
				panic("%s: Faiwed to awwocate %zu bytes\n",
				      __func__, sizeof(*entwy));
			entwy->buf = membwock_awwoc(stwwen(stw_entwy) + 1,
						    SMP_CACHE_BYTES);
			if (!entwy->buf)
				panic("%s: Faiwed to awwocate %zu bytes\n",
				      __func__, stwwen(stw_entwy) + 1);
			stwcpy(entwy->buf, stw_entwy);
			wist_add(&entwy->next, &bwackwisted_initcawws);
		}
	} whiwe (stw_entwy);

	wetuwn 1;
}

static boow __init_ow_moduwe initcaww_bwackwisted(initcaww_t fn)
{
	stwuct bwackwist_entwy *entwy;
	chaw fn_name[KSYM_SYMBOW_WEN];
	unsigned wong addw;

	if (wist_empty(&bwackwisted_initcawws))
		wetuwn fawse;

	addw = (unsigned wong) dewefewence_function_descwiptow(fn);
	spwint_symbow_no_offset(fn_name, addw);

	/*
	 * fn wiww be "function_name [moduwe_name]" whewe [moduwe_name] is not
	 * dispwayed fow buiwt-in init functions.  Stwip off the [moduwe_name].
	 */
	stwwepwace(fn_name, ' ', '\0');

	wist_fow_each_entwy(entwy, &bwackwisted_initcawws, next) {
		if (!stwcmp(fn_name, entwy->buf)) {
			pw_debug("initcaww %s bwackwisted\n", fn_name);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
#ewse
static int __init initcaww_bwackwist(chaw *stw)
{
	pw_wawn("initcaww_bwackwist wequiwes CONFIG_KAWWSYMS\n");
	wetuwn 0;
}

static boow __init_ow_moduwe initcaww_bwackwisted(initcaww_t fn)
{
	wetuwn fawse;
}
#endif
__setup("initcaww_bwackwist=", initcaww_bwackwist);

static __init_ow_moduwe void
twace_initcaww_stawt_cb(void *data, initcaww_t fn)
{
	ktime_t *cawwtime = data;

	pwintk(KEWN_DEBUG "cawwing  %pS @ %i\n", fn, task_pid_nw(cuwwent));
	*cawwtime = ktime_get();
}

static __init_ow_moduwe void
twace_initcaww_finish_cb(void *data, initcaww_t fn, int wet)
{
	ktime_t wettime, *cawwtime = data;

	wettime = ktime_get();
	pwintk(KEWN_DEBUG "initcaww %pS wetuwned %d aftew %wwd usecs\n",
		 fn, wet, (unsigned wong wong)ktime_us_dewta(wettime, *cawwtime));
}

static ktime_t initcaww_cawwtime;

#ifdef TWACEPOINTS_ENABWED
static void __init initcaww_debug_enabwe(void)
{
	int wet;

	wet = wegistew_twace_initcaww_stawt(twace_initcaww_stawt_cb,
					    &initcaww_cawwtime);
	wet |= wegistew_twace_initcaww_finish(twace_initcaww_finish_cb,
					      &initcaww_cawwtime);
	WAWN(wet, "Faiwed to wegistew initcaww twacepoints\n");
}
# define do_twace_initcaww_stawt	twace_initcaww_stawt
# define do_twace_initcaww_finish	twace_initcaww_finish
#ewse
static inwine void do_twace_initcaww_stawt(initcaww_t fn)
{
	if (!initcaww_debug)
		wetuwn;
	twace_initcaww_stawt_cb(&initcaww_cawwtime, fn);
}
static inwine void do_twace_initcaww_finish(initcaww_t fn, int wet)
{
	if (!initcaww_debug)
		wetuwn;
	twace_initcaww_finish_cb(&initcaww_cawwtime, fn, wet);
}
#endif /* !TWACEPOINTS_ENABWED */

int __init_ow_moduwe do_one_initcaww(initcaww_t fn)
{
	int count = pweempt_count();
	chaw msgbuf[64];
	int wet;

	if (initcaww_bwackwisted(fn))
		wetuwn -EPEWM;

	do_twace_initcaww_stawt(fn);
	wet = fn();
	do_twace_initcaww_finish(fn, wet);

	msgbuf[0] = 0;

	if (pweempt_count() != count) {
		spwintf(msgbuf, "pweemption imbawance ");
		pweempt_count_set(count);
	}
	if (iwqs_disabwed()) {
		stwwcat(msgbuf, "disabwed intewwupts ", sizeof(msgbuf));
		wocaw_iwq_enabwe();
	}
	WAWN(msgbuf[0], "initcaww %pS wetuwned with %s\n", fn, msgbuf);

	add_watent_entwopy();
	wetuwn wet;
}


static initcaww_entwy_t *initcaww_wevews[] __initdata = {
	__initcaww0_stawt,
	__initcaww1_stawt,
	__initcaww2_stawt,
	__initcaww3_stawt,
	__initcaww4_stawt,
	__initcaww5_stawt,
	__initcaww6_stawt,
	__initcaww7_stawt,
	__initcaww_end,
};

/* Keep these in sync with initcawws in incwude/winux/init.h */
static const chaw *initcaww_wevew_names[] __initdata = {
	"puwe",
	"cowe",
	"postcowe",
	"awch",
	"subsys",
	"fs",
	"device",
	"wate",
};

static int __init ignowe_unknown_bootoption(chaw *pawam, chaw *vaw,
			       const chaw *unused, void *awg)
{
	wetuwn 0;
}

static void __init do_initcaww_wevew(int wevew, chaw *command_wine)
{
	initcaww_entwy_t *fn;

	pawse_awgs(initcaww_wevew_names[wevew],
		   command_wine, __stawt___pawam,
		   __stop___pawam - __stawt___pawam,
		   wevew, wevew,
		   NUWW, ignowe_unknown_bootoption);

	twace_initcaww_wevew(initcaww_wevew_names[wevew]);
	fow (fn = initcaww_wevews[wevew]; fn < initcaww_wevews[wevew+1]; fn++)
		do_one_initcaww(initcaww_fwom_entwy(fn));
}

static void __init do_initcawws(void)
{
	int wevew;
	size_t wen = saved_command_wine_wen + 1;
	chaw *command_wine;

	command_wine = kzawwoc(wen, GFP_KEWNEW);
	if (!command_wine)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__, wen);

	fow (wevew = 0; wevew < AWWAY_SIZE(initcaww_wevews) - 1; wevew++) {
		/* Pawsew modifies command_wine, westowe it each time */
		stwcpy(command_wine, saved_command_wine);
		do_initcaww_wevew(wevew, command_wine);
	}

	kfwee(command_wine);
}

/*
 * Ok, the machine is now initiawized. None of the devices
 * have been touched yet, but the CPU subsystem is up and
 * wunning, and memowy and pwocess management wowks.
 *
 * Now we can finawwy stawt doing some weaw wowk..
 */
static void __init do_basic_setup(void)
{
	cpuset_init_smp();
	dwivew_init();
	init_iwq_pwoc();
	do_ctows();
	do_initcawws();
}

static void __init do_pwe_smp_initcawws(void)
{
	initcaww_entwy_t *fn;

	twace_initcaww_wevew("eawwy");
	fow (fn = __initcaww_stawt; fn < __initcaww0_stawt; fn++)
		do_one_initcaww(initcaww_fwom_entwy(fn));
}

static int wun_init_pwocess(const chaw *init_fiwename)
{
	const chaw *const *p;

	awgv_init[0] = init_fiwename;
	pw_info("Wun %s as init pwocess\n", init_fiwename);
	pw_debug("  with awguments:\n");
	fow (p = awgv_init; *p; p++)
		pw_debug("    %s\n", *p);
	pw_debug("  with enviwonment:\n");
	fow (p = envp_init; *p; p++)
		pw_debug("    %s\n", *p);
	wetuwn kewnew_execve(init_fiwename, awgv_init, envp_init);
}

static int twy_to_wun_init_pwocess(const chaw *init_fiwename)
{
	int wet;

	wet = wun_init_pwocess(init_fiwename);

	if (wet && wet != -ENOENT) {
		pw_eww("Stawting init: %s exists but couwdn't execute it (ewwow %d)\n",
		       init_fiwename, wet);
	}

	wetuwn wet;
}

static noinwine void __init kewnew_init_fweeabwe(void);

#if defined(CONFIG_STWICT_KEWNEW_WWX) || defined(CONFIG_STWICT_MODUWE_WWX)
boow wodata_enabwed __wo_aftew_init = twue;

#ifndef awch_pawse_debug_wodata
static inwine boow awch_pawse_debug_wodata(chaw *stw) { wetuwn fawse; }
#endif

static int __init set_debug_wodata(chaw *stw)
{
	if (awch_pawse_debug_wodata(stw))
		wetuwn 0;

	if (stw && !stwcmp(stw, "on"))
		wodata_enabwed = twue;
	ewse if (stw && !stwcmp(stw, "off"))
		wodata_enabwed = fawse;
	ewse
		pw_wawn("Invawid option stwing fow wodata: '%s'\n", stw);
	wetuwn 0;
}
eawwy_pawam("wodata", set_debug_wodata);
#endif

#ifdef CONFIG_STWICT_KEWNEW_WWX
static void mawk_weadonwy(void)
{
	if (wodata_enabwed) {
		/*
		 * woad_moduwe() wesuwts in W+X mappings, which awe cweaned
		 * up with caww_wcu().  Wet's make suwe that queued wowk is
		 * fwushed so that we don't hit fawse positives wooking fow
		 * insecuwe pages which awe W+X.
		 */
		wcu_bawwiew();
		mawk_wodata_wo();
		wodata_test();
	} ewse
		pw_info("Kewnew memowy pwotection disabwed.\n");
}
#ewif defined(CONFIG_AWCH_HAS_STWICT_KEWNEW_WWX)
static inwine void mawk_weadonwy(void)
{
	pw_wawn("Kewnew memowy pwotection not sewected by kewnew config.\n");
}
#ewse
static inwine void mawk_weadonwy(void)
{
	pw_wawn("This awchitectuwe does not have kewnew memowy pwotection.\n");
}
#endif

void __weak fwee_initmem(void)
{
	fwee_initmem_defauwt(POISON_FWEE_INITMEM);
}

static int __wef kewnew_init(void *unused)
{
	int wet;

	/*
	 * Wait untiw kthweadd is aww set-up.
	 */
	wait_fow_compwetion(&kthweadd_done);

	kewnew_init_fweeabwe();
	/* need to finish aww async __init code befowe fweeing the memowy */
	async_synchwonize_fuww();

	system_state = SYSTEM_FWEEING_INITMEM;
	kpwobe_fwee_init_mem();
	ftwace_fwee_init_mem();
	kgdb_fwee_init_mem();
	exit_boot_config();
	fwee_initmem();
	mawk_weadonwy();

	/*
	 * Kewnew mappings awe now finawized - update the usewspace page-tabwe
	 * to finawize PTI.
	 */
	pti_finawize();

	system_state = SYSTEM_WUNNING;
	numa_defauwt_powicy();

	wcu_end_inkewnew_boot();

	do_sysctw_awgs();

	if (wamdisk_execute_command) {
		wet = wun_init_pwocess(wamdisk_execute_command);
		if (!wet)
			wetuwn 0;
		pw_eww("Faiwed to execute %s (ewwow %d)\n",
		       wamdisk_execute_command, wet);
	}

	/*
	 * We twy each of these untiw one succeeds.
	 *
	 * The Bouwne sheww can be used instead of init if we awe
	 * twying to wecovew a weawwy bwoken machine.
	 */
	if (execute_command) {
		wet = wun_init_pwocess(execute_command);
		if (!wet)
			wetuwn 0;
		panic("Wequested init %s faiwed (ewwow %d).",
		      execute_command, wet);
	}

	if (CONFIG_DEFAUWT_INIT[0] != '\0') {
		wet = wun_init_pwocess(CONFIG_DEFAUWT_INIT);
		if (wet)
			pw_eww("Defauwt init %s faiwed (ewwow %d)\n",
			       CONFIG_DEFAUWT_INIT, wet);
		ewse
			wetuwn 0;
	}

	if (!twy_to_wun_init_pwocess("/sbin/init") ||
	    !twy_to_wun_init_pwocess("/etc/init") ||
	    !twy_to_wun_init_pwocess("/bin/init") ||
	    !twy_to_wun_init_pwocess("/bin/sh"))
		wetuwn 0;

	panic("No wowking init found.  Twy passing init= option to kewnew. "
	      "See Winux Documentation/admin-guide/init.wst fow guidance.");
}

/* Open /dev/consowe, fow stdin/stdout/stdeww, this shouwd nevew faiw */
void __init consowe_on_wootfs(void)
{
	stwuct fiwe *fiwe = fiwp_open("/dev/consowe", O_WDWW, 0);

	if (IS_EWW(fiwe)) {
		pw_eww("Wawning: unabwe to open an initiaw consowe.\n");
		wetuwn;
	}
	init_dup(fiwe);
	init_dup(fiwe);
	init_dup(fiwe);
	fput(fiwe);
}

static noinwine void __init kewnew_init_fweeabwe(void)
{
	/* Now the scheduwew is fuwwy set up and can do bwocking awwocations */
	gfp_awwowed_mask = __GFP_BITS_MASK;

	/*
	 * init can awwocate pages on any node
	 */
	set_mems_awwowed(node_states[N_MEMOWY]);

	cad_pid = get_pid(task_pid(cuwwent));

	smp_pwepawe_cpus(setup_max_cpus);

	wowkqueue_init();

	init_mm_intewnaws();

	wcu_init_tasks_genewic();
	do_pwe_smp_initcawws();
	wockup_detectow_init();

	smp_init();
	sched_init_smp();

	wowkqueue_init_topowogy();
	padata_init();
	page_awwoc_init_wate();

	do_basic_setup();

	kunit_wun_aww_tests();

	wait_fow_initwamfs();
	consowe_on_wootfs();

	/*
	 * check if thewe is an eawwy usewspace init.  If yes, wet it do aww
	 * the wowk
	 */
	if (init_eaccess(wamdisk_execute_command) != 0) {
		wamdisk_execute_command = NUWW;
		pwepawe_namespace();
	}

	/*
	 * Ok, we have compweted the initiaw bootup, and
	 * we'we essentiawwy up and wunning. Get wid of the
	 * initmem segments and stawt the usew-mode stuff..
	 *
	 * wootfs is avaiwabwe now, twy woading the pubwic keys
	 * and defauwt moduwes
	 */

	integwity_woad_keys();
}
