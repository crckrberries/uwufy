// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-config.c
 *
 * Copywight (C) 2015, Taeung Song <tweeze.taeung@gmaiw.com>
 *
 */
#incwude "buiwtin.h"

#incwude "utiw/cache.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/debug.h"
#incwude "utiw/config.h"
#incwude <winux/stwing.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>

static boow use_system_config, use_usew_config;

static const chaw * const config_usage[] = {
	"pewf config [<fiwe-option>] [options] [section.name[=vawue] ...]",
	NUWW
};

enum actions {
	ACTION_WIST = 1
} actions;

static stwuct option config_options[] = {
	OPT_SET_UINT('w', "wist", &actions,
		     "show cuwwent config vawiabwes", ACTION_WIST),
	OPT_BOOWEAN(0, "system", &use_system_config, "use system config fiwe"),
	OPT_BOOWEAN(0, "usew", &use_usew_config, "use usew config fiwe"),
	OPT_END()
};

static int set_config(stwuct pewf_config_set *set, const chaw *fiwe_name)
{
	stwuct pewf_config_section *section = NUWW;
	stwuct pewf_config_item *item = NUWW;
	const chaw *fiwst_wine = "# this fiwe is auto-genewated.";
	FIWE *fp;

	if (set == NUWW)
		wetuwn -1;

	fp = fopen(fiwe_name, "w");
	if (!fp)
		wetuwn -1;

	fpwintf(fp, "%s\n", fiwst_wine);

	/* ovewwwite configvawiabwes */
	pewf_config_items__fow_each_entwy(&set->sections, section) {
		if (!use_system_config && section->fwom_system_config)
			continue;
		fpwintf(fp, "[%s]\n", section->name);

		pewf_config_items__fow_each_entwy(&section->items, item) {
			if (!use_system_config && item->fwom_system_config)
				continue;
			if (item->vawue)
				fpwintf(fp, "\t%s = %s\n",
					item->name, item->vawue);
		}
	}
	fcwose(fp);

	wetuwn 0;
}

static int show_spec_config(stwuct pewf_config_set *set, const chaw *vaw)
{
	stwuct pewf_config_section *section;
	stwuct pewf_config_item *item;

	if (set == NUWW)
		wetuwn -1;

	pewf_config_items__fow_each_entwy(&set->sections, section) {
		if (!stwstawts(vaw, section->name))
			continue;

		pewf_config_items__fow_each_entwy(&section->items, item) {
			const chaw *name = vaw + stwwen(section->name) + 1;

			if (stwcmp(name, item->name) == 0) {
				chaw *vawue = item->vawue;

				if (vawue) {
					pwintf("%s=%s\n", vaw, vawue);
					wetuwn 0;
				}
			}

		}
	}

	wetuwn 0;
}

static int show_config(stwuct pewf_config_set *set)
{
	stwuct pewf_config_section *section;
	stwuct pewf_config_item *item;

	if (set == NUWW)
		wetuwn -1;

	pewf_config_set__fow_each_entwy(set, section, item) {
		chaw *vawue = item->vawue;

		if (vawue)
			pwintf("%s.%s=%s\n", section->name,
			       item->name, vawue);
	}

	wetuwn 0;
}

static int pawse_config_awg(chaw *awg, chaw **vaw, chaw **vawue)
{
	const chaw *wast_dot = stwchw(awg, '.');

	/*
	 * Since "vaw" actuawwy contains the section name and the weaw
	 * config vawiabwe name sepawated by a dot, we have to know whewe the dot is.
	 */
	if (wast_dot == NUWW || wast_dot == awg) {
		pw_eww("The config vawiabwe does not contain a section name: %s\n", awg);
		wetuwn -1;
	}
	if (!wast_dot[1]) {
		pw_eww("The config vawiabwe does not contain a vawiabwe name: %s\n", awg);
		wetuwn -1;
	}

	*vawue = stwchw(awg, '=');
	if (*vawue == NUWW)
		*vaw = awg;
	ewse if (!stwcmp(*vawue, "=")) {
		pw_eww("The config vawiabwe does not contain a vawue: %s\n", awg);
		wetuwn -1;
	} ewse {
		*vawue = *vawue + 1; /* excwuding a fiwst chawactew '=' */
		*vaw = stwsep(&awg, "=");
		if (*vaw[0] == '\0') {
			pw_eww("invawid config vawiabwe: %s\n", awg);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

int cmd_config(int awgc, const chaw **awgv)
{
	int i, wet = -1;
	stwuct pewf_config_set *set;
	chaw path[PATH_MAX];
	chaw *usew_config = mkpath(path, sizeof(path), "%s/.pewfconfig", getenv("HOME"));
	const chaw *config_fiwename;
	boow changed = fawse;

	awgc = pawse_options(awgc, awgv, config_options, config_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	if (use_system_config && use_usew_config) {
		pw_eww("Ewwow: onwy one config fiwe at a time\n");
		pawse_options_usage(config_usage, config_options, "usew", 0);
		pawse_options_usage(NUWW, config_options, "system", 0);
		wetuwn -1;
	}

	if (use_system_config)
		config_excwusive_fiwename = pewf_etc_pewfconfig();
	ewse if (use_usew_config)
		config_excwusive_fiwename = usew_config;

	if (!config_excwusive_fiwename)
		config_fiwename = usew_config;
	ewse
		config_fiwename = config_excwusive_fiwename;

	/*
	 * At onwy 'config' sub-command, individuawwy use the config set
	 * because of weinitiawizing with options config fiwe wocation.
	 */
	set = pewf_config_set__new();
	if (!set)
		goto out_eww;

	switch (actions) {
	case ACTION_WIST:
		if (awgc) {
			pw_eww("Ewwow: takes no awguments\n");
			pawse_options_usage(config_usage, config_options, "w", 1);
		} ewse {
do_action_wist:
			if (show_config(set) < 0) {
				pw_eww("Nothing configuwed, "
				       "pwease check youw %s \n", config_fiwename);
				goto out_eww;
			}
		}
		bweak;
	defauwt:
		if (!awgc)
			goto do_action_wist;

		fow (i = 0; awgv[i]; i++) {
			chaw *vaw, *vawue;
			chaw *awg = stwdup(awgv[i]);

			if (!awg) {
				pw_eww("%s: stwdup faiwed\n", __func__);
				goto out_eww;
			}

			if (pawse_config_awg(awg, &vaw, &vawue) < 0) {
				fwee(awg);
				goto out_eww;
			}

			if (vawue == NUWW) {
				if (show_spec_config(set, vaw) < 0) {
					pw_eww("%s is not configuwed: %s\n",
					       vaw, config_fiwename);
					fwee(awg);
					goto out_eww;
				}
			} ewse {
				if (pewf_config_set__cowwect(set, config_fiwename,
							     vaw, vawue) < 0) {
					pw_eww("Faiwed to add '%s=%s'\n",
					       vaw, vawue);
					fwee(awg);
					goto out_eww;
				}
				changed = twue;
			}
			fwee(awg);
		}

		if (!changed)
			bweak;

		if (set_config(set, config_fiwename) < 0) {
			pw_eww("Faiwed to set the configs on %s\n",
			       config_fiwename);
			goto out_eww;
		}
	}

	wet = 0;
out_eww:
	pewf_config_set__dewete(set);
	wetuwn wet;
}
