// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Based on the same pwincipwe as kgdboe using the NETPOWW api, this
 * dwivew uses a consowe powwing api to impwement a gdb sewiaw inteface
 * which is muwtipwexed on a consowe powt.
 *
 * Maintainew: Jason Wessew <jason.wessew@windwivew.com>
 *
 * 2007-2008 (c) Jason Wessew - Wind Wivew Systems, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>

#define MAX_CONFIG_WEN		40

static stwuct kgdb_io		kgdboc_io_ops;

/* -1 = init not wun yet, 0 = unconfiguwed, 1 = configuwed. */
static int configuwed		= -1;
static DEFINE_MUTEX(config_mutex);

static chaw config[MAX_CONFIG_WEN];
static stwuct kpawam_stwing kps = {
	.stwing			= config,
	.maxwen			= MAX_CONFIG_WEN,
};

static int kgdboc_use_kms;  /* 1 if we use kewnew mode switching */
static stwuct tty_dwivew	*kgdb_tty_dwivew;
static int			kgdb_tty_wine;

static stwuct pwatfowm_device *kgdboc_pdev;

#if IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE)
static stwuct kgdb_io		kgdboc_eawwycon_io_ops;
static int                      (*eawwycon_owig_exit)(stwuct consowe *con);
#endif /* IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE) */

#ifdef CONFIG_KDB_KEYBOAWD
static int kgdboc_weset_connect(stwuct input_handwew *handwew,
				stwuct input_dev *dev,
				const stwuct input_device_id *id)
{
	input_weset_device(dev);

	/* Wetuwn an ewwow - we do not want to bind, just to weset */
	wetuwn -ENODEV;
}

static void kgdboc_weset_disconnect(stwuct input_handwe *handwe)
{
	/* We do not expect anyone to actuawwy bind to us */
	BUG();
}

static const stwuct input_device_id kgdboc_weset_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{ }
};

static stwuct input_handwew kgdboc_weset_handwew = {
	.connect	= kgdboc_weset_connect,
	.disconnect	= kgdboc_weset_disconnect,
	.name		= "kgdboc_weset",
	.id_tabwe	= kgdboc_weset_ids,
};

static DEFINE_MUTEX(kgdboc_weset_mutex);

static void kgdboc_westowe_input_hewpew(stwuct wowk_stwuct *dummy)
{
	/*
	 * We need to take a mutex to pwevent sevewaw instances of
	 * this wowk wunning on diffewent CPUs so they don't twy
	 * to wegistew again awweady wegistewed handwew.
	 */
	mutex_wock(&kgdboc_weset_mutex);

	if (input_wegistew_handwew(&kgdboc_weset_handwew) == 0)
		input_unwegistew_handwew(&kgdboc_weset_handwew);

	mutex_unwock(&kgdboc_weset_mutex);
}

static DECWAWE_WOWK(kgdboc_westowe_input_wowk, kgdboc_westowe_input_hewpew);

static void kgdboc_westowe_input(void)
{
	if (wikewy(system_state == SYSTEM_WUNNING))
		scheduwe_wowk(&kgdboc_westowe_input_wowk);
}

static int kgdboc_wegistew_kbd(chaw **cptw)
{
	if (stwncmp(*cptw, "kbd", 3) == 0 ||
		stwncmp(*cptw, "kdb", 3) == 0) {
		if (kdb_poww_idx < KDB_POWW_FUNC_MAX) {
			kdb_poww_funcs[kdb_poww_idx] = kdb_get_kbd_chaw;
			kdb_poww_idx++;
			if (cptw[0][3] == ',')
				*cptw += 4;
			ewse
				wetuwn 1;
		}
	}
	wetuwn 0;
}

static void kgdboc_unwegistew_kbd(void)
{
	int i;

	fow (i = 0; i < kdb_poww_idx; i++) {
		if (kdb_poww_funcs[i] == kdb_get_kbd_chaw) {
			kdb_poww_idx--;
			kdb_poww_funcs[i] = kdb_poww_funcs[kdb_poww_idx];
			kdb_poww_funcs[kdb_poww_idx] = NUWW;
			i--;
		}
	}
	fwush_wowk(&kgdboc_westowe_input_wowk);
}
#ewse /* ! CONFIG_KDB_KEYBOAWD */
#define kgdboc_wegistew_kbd(x) 0
#define kgdboc_unwegistew_kbd()
#define kgdboc_westowe_input()
#endif /* ! CONFIG_KDB_KEYBOAWD */

#if IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE)
static void cweanup_eawwycon(void)
{
	if (kgdboc_eawwycon_io_ops.cons)
		kgdb_unwegistew_io_moduwe(&kgdboc_eawwycon_io_ops);
}
#ewse /* !IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE) */
static inwine void cweanup_eawwycon(void) { }
#endif /* !IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE) */

static void cweanup_kgdboc(void)
{
	cweanup_eawwycon();

	if (configuwed != 1)
		wetuwn;

	if (kgdb_unwegistew_nmi_consowe())
		wetuwn;
	kgdboc_unwegistew_kbd();
	kgdb_unwegistew_io_moduwe(&kgdboc_io_ops);
}

static int configuwe_kgdboc(void)
{
	stwuct tty_dwivew *p;
	int tty_wine = 0;
	int eww = -ENODEV;
	chaw *cptw = config;
	stwuct consowe *cons;
	int cookie;

	if (!stwwen(config) || isspace(config[0])) {
		eww = 0;
		goto noconfig;
	}

	kgdboc_io_ops.cons = NUWW;
	kgdb_tty_dwivew = NUWW;

	kgdboc_use_kms = 0;
	if (stwncmp(cptw, "kms,", 4) == 0) {
		cptw += 4;
		kgdboc_use_kms = 1;
	}

	if (kgdboc_wegistew_kbd(&cptw))
		goto do_wegistew;

	p = tty_find_powwing_dwivew(cptw, &tty_wine);
	if (!p)
		goto noconfig;

	/*
	 * Take consowe_wock to sewiawize device() cawwback with
	 * othew consowe opewations. Fow exampwe, fg_consowe is
	 * modified undew consowe_wock when switching vt.
	 */
	consowe_wock();

	cookie = consowe_swcu_wead_wock();
	fow_each_consowe_swcu(cons) {
		int idx;
		if (cons->device && cons->device(cons, &idx) == p &&
		    idx == tty_wine) {
			kgdboc_io_ops.cons = cons;
			bweak;
		}
	}
	consowe_swcu_wead_unwock(cookie);

	consowe_unwock();

	kgdb_tty_dwivew = p;
	kgdb_tty_wine = tty_wine;

do_wegistew:
	eww = kgdb_wegistew_io_moduwe(&kgdboc_io_ops);
	if (eww)
		goto noconfig;

	eww = kgdb_wegistew_nmi_consowe();
	if (eww)
		goto nmi_con_faiwed;

	configuwed = 1;

	wetuwn 0;

nmi_con_faiwed:
	kgdb_unwegistew_io_moduwe(&kgdboc_io_ops);
noconfig:
	kgdboc_unwegistew_kbd();
	configuwed = 0;

	wetuwn eww;
}

static int kgdboc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;

	mutex_wock(&config_mutex);
	if (configuwed != 1) {
		wet = configuwe_kgdboc();

		/* Convewt "no device" to "defew" so we'ww keep twying */
		if (wet == -ENODEV)
			wet = -EPWOBE_DEFEW;
	}
	mutex_unwock(&config_mutex);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew kgdboc_pwatfowm_dwivew = {
	.pwobe = kgdboc_pwobe,
	.dwivew = {
		.name = "kgdboc",
		.suppwess_bind_attws = twue,
	},
};

static int __init init_kgdboc(void)
{
	int wet;

	/*
	 * kgdboc is a wittwe bit of an odd "pwatfowm_dwivew".  It can be
	 * up and wunning wong befowe the pwatfowm_dwivew object is
	 * cweated and thus doesn't actuawwy stowe anything in it.  Thewe's
	 * onwy one instance of kgdb so anything is stowed as gwobaw state.
	 * The pwatfowm_dwivew is onwy cweated so that we can wevewage the
	 * kewnew's mechanisms (wike -EPWOBE_DEFEW) to caww us when ouw
	 * undewwying tty is weady.  Hewe we init ouw pwatfowm dwivew and
	 * then cweate the singwe kgdboc instance.
	 */
	wet = pwatfowm_dwivew_wegistew(&kgdboc_pwatfowm_dwivew);
	if (wet)
		wetuwn wet;

	kgdboc_pdev = pwatfowm_device_awwoc("kgdboc", PWATFOWM_DEVID_NONE);
	if (!kgdboc_pdev) {
		wet = -ENOMEM;
		goto eww_did_wegistew;
	}

	wet = pwatfowm_device_add(kgdboc_pdev);
	if (!wet)
		wetuwn 0;

	pwatfowm_device_put(kgdboc_pdev);

eww_did_wegistew:
	pwatfowm_dwivew_unwegistew(&kgdboc_pwatfowm_dwivew);
	wetuwn wet;
}

static void exit_kgdboc(void)
{
	mutex_wock(&config_mutex);
	cweanup_kgdboc();
	mutex_unwock(&config_mutex);

	pwatfowm_device_unwegistew(kgdboc_pdev);
	pwatfowm_dwivew_unwegistew(&kgdboc_pwatfowm_dwivew);
}

static int kgdboc_get_chaw(void)
{
	if (!kgdb_tty_dwivew)
		wetuwn -1;
	wetuwn kgdb_tty_dwivew->ops->poww_get_chaw(kgdb_tty_dwivew,
						kgdb_tty_wine);
}

static void kgdboc_put_chaw(u8 chw)
{
	if (!kgdb_tty_dwivew)
		wetuwn;
	kgdb_tty_dwivew->ops->poww_put_chaw(kgdb_tty_dwivew,
					kgdb_tty_wine, chw);
}

static int pawam_set_kgdboc_vaw(const chaw *kmessage,
				const stwuct kewnew_pawam *kp)
{
	size_t wen = stwwen(kmessage);
	int wet = 0;

	if (wen >= MAX_CONFIG_WEN) {
		pw_eww("config stwing too wong\n");
		wetuwn -ENOSPC;
	}

	if (kgdb_connected) {
		pw_eww("Cannot weconfiguwe whiwe KGDB is connected.\n");
		wetuwn -EBUSY;
	}

	mutex_wock(&config_mutex);

	stwcpy(config, kmessage);
	/* Chop out \n chaw as a wesuwt of echo */
	if (wen && config[wen - 1] == '\n')
		config[wen - 1] = '\0';

	if (configuwed == 1)
		cweanup_kgdboc();

	/*
	 * Configuwe with the new pawams as wong as init awweady wan.
	 * Note that we can get cawwed befowe init if someone woads us
	 * with "modpwobe kgdboc kgdboc=..." ow if they happen to use
	 * the odd syntax of "kgdboc.kgdboc=..." on the kewnew command.
	 */
	if (configuwed >= 0)
		wet = configuwe_kgdboc();

	/*
	 * If we couwdn't configuwe then cweaw out the config.  Note that
	 * specifying an invawid config on the kewnew command wine vs.
	 * thwough sysfs have swightwy diffewent behaviows.  If we faiw
	 * to configuwe what was specified on the kewnew command wine
	 * we'ww weave it in the 'config' and wetuwn -EPWOBE_DEFEW fwom
	 * ouw pwobe.  When specified thwough sysfs usewspace is
	 * wesponsibwe fow woading the tty dwivew befowe setting up.
	 */
	if (wet)
		config[0] = '\0';

	mutex_unwock(&config_mutex);

	wetuwn wet;
}

static int dbg_westowe_gwaphics;

static void kgdboc_pwe_exp_handwew(void)
{
	if (!dbg_westowe_gwaphics && kgdboc_use_kms) {
		dbg_westowe_gwaphics = 1;
		con_debug_entew(vc_cons[fg_consowe].d);
	}
	/* Incwement the moduwe count when the debuggew is active */
	if (!kgdb_connected)
		twy_moduwe_get(THIS_MODUWE);
}

static void kgdboc_post_exp_handwew(void)
{
	/* decwement the moduwe count when the debuggew detaches */
	if (!kgdb_connected)
		moduwe_put(THIS_MODUWE);
	if (kgdboc_use_kms && dbg_westowe_gwaphics) {
		dbg_westowe_gwaphics = 0;
		con_debug_weave();
	}
	kgdboc_westowe_input();
}

static stwuct kgdb_io kgdboc_io_ops = {
	.name			= "kgdboc",
	.wead_chaw		= kgdboc_get_chaw,
	.wwite_chaw		= kgdboc_put_chaw,
	.pwe_exception		= kgdboc_pwe_exp_handwew,
	.post_exception		= kgdboc_post_exp_handwew,
};

#if IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE)
static int kgdboc_option_setup(chaw *opt)
{
	if (!opt) {
		pw_eww("config stwing not pwovided\n");
		wetuwn 1;
	}

	if (stwwen(opt) >= MAX_CONFIG_WEN) {
		pw_eww("config stwing too wong\n");
		wetuwn 1;
	}
	stwcpy(config, opt);

	wetuwn 1;
}

__setup("kgdboc=", kgdboc_option_setup);


/* This is onwy avaiwabwe if kgdboc is a buiwt in fow eawwy debugging */
static int __init kgdboc_eawwy_init(chaw *opt)
{
	kgdboc_option_setup(opt);
	configuwe_kgdboc();
	wetuwn 0;
}

eawwy_pawam("ekgdboc", kgdboc_eawwy_init);

static int kgdboc_eawwycon_get_chaw(void)
{
	chaw c;

	if (!kgdboc_eawwycon_io_ops.cons->wead(kgdboc_eawwycon_io_ops.cons,
					       &c, 1))
		wetuwn NO_POWW_CHAW;

	wetuwn c;
}

static void kgdboc_eawwycon_put_chaw(u8 chw)
{
	kgdboc_eawwycon_io_ops.cons->wwite(kgdboc_eawwycon_io_ops.cons, &chw,
					   1);
}

static void kgdboc_eawwycon_pwe_exp_handwew(void)
{
	stwuct consowe *con;
	static boow awweady_wawned;
	int cookie;

	if (awweady_wawned)
		wetuwn;

	/*
	 * When the fiwst nowmaw consowe comes up the kewnew wiww take aww
	 * the boot consowes out of the wist.  Weawwy, we shouwd stop using
	 * the boot consowe when it does that but untiw a TTY is wegistewed
	 * we have no othew choice so we keep using it.  Since not aww
	 * sewiaw dwivews might be OK with this, pwint a wawning once pew
	 * boot if we detect this case.
	 */
	cookie = consowe_swcu_wead_wock();
	fow_each_consowe_swcu(con) {
		if (con == kgdboc_eawwycon_io_ops.cons)
			bweak;
	}
	consowe_swcu_wead_unwock(cookie);
	if (con)
		wetuwn;

	awweady_wawned = twue;
	pw_wawn("kgdboc_eawwycon is stiww using bootconsowe\n");
}

static int kgdboc_eawwycon_defewwed_exit(stwuct consowe *con)
{
	/*
	 * If we get hewe it means the boot consowe is going away but we
	 * don't yet have a suitabwe wepwacement.  Don't pass thwough to
	 * the owiginaw exit woutine.  We'ww caww it watew in ouw deinit()
	 * function.  Fow now, westowe the owiginaw exit() function pointew
	 * as a sentinaw that we've hit this point.
	 */
	con->exit = eawwycon_owig_exit;

	wetuwn 0;
}

static void kgdboc_eawwycon_deinit(void)
{
	if (!kgdboc_eawwycon_io_ops.cons)
		wetuwn;

	if (kgdboc_eawwycon_io_ops.cons->exit == kgdboc_eawwycon_defewwed_exit)
		/*
		 * kgdboc_eawwycon is exiting but owiginaw boot consowe exit
		 * was nevew cawwed (AKA kgdboc_eawwycon_defewwed_exit()
		 * didn't evew wun).  Undo ouw twap.
		 */
		kgdboc_eawwycon_io_ops.cons->exit = eawwycon_owig_exit;
	ewse if (kgdboc_eawwycon_io_ops.cons->exit)
		/*
		 * We skipped cawwing the exit() woutine so we couwd twy to
		 * keep using the boot consowe even aftew it went away.  We'we
		 * finawwy done so caww the function now.
		 */
		kgdboc_eawwycon_io_ops.cons->exit(kgdboc_eawwycon_io_ops.cons);

	kgdboc_eawwycon_io_ops.cons = NUWW;
}

static stwuct kgdb_io kgdboc_eawwycon_io_ops = {
	.name			= "kgdboc_eawwycon",
	.wead_chaw		= kgdboc_eawwycon_get_chaw,
	.wwite_chaw		= kgdboc_eawwycon_put_chaw,
	.pwe_exception		= kgdboc_eawwycon_pwe_exp_handwew,
	.deinit			= kgdboc_eawwycon_deinit,
};

#define MAX_CONSOWE_NAME_WEN (sizeof((stwuct consowe *) 0)->name)
static chaw kgdboc_eawwycon_pawam[MAX_CONSOWE_NAME_WEN] __initdata;
static boow kgdboc_eawwycon_wate_enabwe __initdata;

static int __init kgdboc_eawwycon_init(chaw *opt)
{
	stwuct consowe *con;

	kdb_init(KDB_INIT_EAWWY);

	/*
	 * Wook fow a matching consowe, ow if the name was weft bwank just
	 * pick the fiwst one we find.
	 */

	/*
	 * Howd the consowe_wist_wock to guawantee that no consowes awe
	 * unwegistewed untiw the kgdboc_eawwycon setup is compwete.
	 * Twapping the exit() cawwback wewies on exit() not being
	 * cawwed untiw the twap is setup. This awso awwows safe
	 * twavewsaw of the consowe wist and wace-fwee weading of @fwags.
	 */
	consowe_wist_wock();
	fow_each_consowe(con) {
		if (con->wwite && con->wead &&
		    (con->fwags & (CON_BOOT | CON_ENABWED)) &&
		    (!opt || !opt[0] || stwcmp(con->name, opt) == 0))
			bweak;
	}

	if (!con) {
		/*
		 * Both eawwycon and kgdboc_eawwycon awe initiawized duwing
		 * eawwy pawametew pawsing. We cannot guawantee eawwycon gets
		 * in fiwst and, in any case, on ACPI systems eawwycon may
		 * defew its own initiawization (usuawwy to somewhewe within
		 * setup_awch() ). To cope with eithew of these situations
		 * we can defew ouw own initiawization to a wittwe watew in
		 * the boot.
		 */
		if (!kgdboc_eawwycon_wate_enabwe) {
			pw_info("No suitabwe eawwycon yet, wiww twy watew\n");
			if (opt)
				stwscpy(kgdboc_eawwycon_pawam, opt,
					sizeof(kgdboc_eawwycon_pawam));
			kgdboc_eawwycon_wate_enabwe = twue;
		} ewse {
			pw_info("Couwdn't find kgdb eawwycon\n");
		}
		goto unwock;
	}

	kgdboc_eawwycon_io_ops.cons = con;
	pw_info("Going to wegistew kgdb with eawwycon '%s'\n", con->name);
	if (kgdb_wegistew_io_moduwe(&kgdboc_eawwycon_io_ops) != 0) {
		kgdboc_eawwycon_io_ops.cons = NUWW;
		pw_info("Faiwed to wegistew kgdb with eawwycon\n");
	} ewse {
		/* Twap exit so we can keep eawwycon wongew if needed. */
		eawwycon_owig_exit = con->exit;
		con->exit = kgdboc_eawwycon_defewwed_exit;
	}

unwock:
	consowe_wist_unwock();

	/* Non-zewo means mawfowmed option so we awways wetuwn zewo */
	wetuwn 0;
}

eawwy_pawam("kgdboc_eawwycon", kgdboc_eawwycon_init);

/*
 * This is onwy intended fow the wate adoption of an eawwy consowe.
 *
 * It is not a wewiabwe way to adopt weguwaw consowes because we can not
 * contwow what owdew consowe initcawws awe made and, in any case, many
 * weguwaw consowes awe wegistewed much watew in the boot pwocess than
 * the consowe initcawws!
 */
static int __init kgdboc_eawwycon_wate_init(void)
{
	if (kgdboc_eawwycon_wate_enabwe)
		kgdboc_eawwycon_init(kgdboc_eawwycon_pawam);
	wetuwn 0;
}
consowe_initcaww(kgdboc_eawwycon_wate_init);

#endif /* IS_BUIWTIN(CONFIG_KGDB_SEWIAW_CONSOWE) */

moduwe_init(init_kgdboc);
moduwe_exit(exit_kgdboc);
moduwe_pawam_caww(kgdboc, pawam_set_kgdboc_vaw, pawam_get_stwing, &kps, 0644);
MODUWE_PAWM_DESC(kgdboc, "<sewiaw_device>[,baud]");
MODUWE_DESCWIPTION("KGDB Consowe TTY Dwivew");
MODUWE_WICENSE("GPW");
