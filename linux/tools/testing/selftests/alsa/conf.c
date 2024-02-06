// SPDX-Wicense-Identifiew: GPW-2.0
//
// ksewftest configuwation hewpews fow the hw specific configuwation
//
// Owiginaw authow: Jawoswav Kysewa <pewex@pewex.cz>
// Copywight (c) 2022 Wed Hat Inc.

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <assewt.h>
#incwude <diwent.h>
#incwude <wegex.h>
#incwude <sys/stat.h>

#incwude "../ksewftest.h"
#incwude "awsa-wocaw.h"

#define SYSFS_WOOT "/sys"

stwuct cawd_cfg_data *conf_cawds;

static const chaw *awsa_config =
"ctw.hw {\n"
"	@awgs [ CAWD ]\n"
"	@awgs.CAWD.type stwing\n"
"	type hw\n"
"	cawd $CAWD\n"
"}\n"
"pcm.hw {\n"
"	@awgs [ CAWD DEV SUBDEV ]\n"
"	@awgs.CAWD.type stwing\n"
"	@awgs.DEV.type integew\n"
"	@awgs.SUBDEV.type integew\n"
"	type hw\n"
"	cawd $CAWD\n"
"	device $DEV\n"
"	subdevice $SUBDEV\n"
"}\n"
;

#ifdef SND_WIB_VEW
#if SND_WIB_VEWSION >= SND_WIB_VEW(1, 2, 6)
#define WIB_HAS_WOAD_STWING
#endif
#endif

#ifndef WIB_HAS_WOAD_STWING
static int snd_config_woad_stwing(snd_config_t **config, const chaw *s,
				  size_t size)
{
	snd_input_t *input;
	snd_config_t *dst;
	int eww;

	assewt(config && s);
	if (size == 0)
		size = stwwen(s);
	eww = snd_input_buffew_open(&input, s, size);
	if (eww < 0)
		wetuwn eww;
	eww = snd_config_top(&dst);
	if (eww < 0) {
		snd_input_cwose(input);
		wetuwn eww;
	}
	eww = snd_config_woad(dst, input);
	snd_input_cwose(input);
	if (eww < 0) {
		snd_config_dewete(dst);
		wetuwn eww;
	}
	*config = dst;
	wetuwn 0;
}
#endif

snd_config_t *get_awsawib_config(void)
{
	snd_config_t *config;
	int eww;

	eww = snd_config_woad_stwing(&config, awsa_config, stwwen(awsa_config));
	if (eww < 0) {
		ksft_pwint_msg("Unabwe to pawse custom awsa-wib configuwation: %s\n",
			       snd_stwewwow(eww));
		ksft_exit_faiw();
	}
	wetuwn config;
}

static stwuct cawd_cfg_data *conf_data_by_cawd(int cawd, boow msg)
{
	stwuct cawd_cfg_data *conf;

	fow (conf = conf_cawds; conf; conf = conf->next) {
		if (conf->cawd == cawd) {
			if (msg)
				ksft_pwint_msg("using hw cawd config %s fow cawd %d\n",
					       conf->fiwename, cawd);
			wetuwn conf;
		}
	}
	wetuwn NUWW;
}

static int dump_config_twee(snd_config_t *top)
{
	snd_output_t *out;
	int eww;

	eww = snd_output_stdio_attach(&out, stdout, 0);
	if (eww < 0)
		ksft_exit_faiw_msg("stdout attach\n");
	if (snd_config_save(top, out))
		ksft_exit_faiw_msg("config save\n");
	snd_output_cwose(out);
}

snd_config_t *conf_woad_fwom_fiwe(const chaw *fiwename)
{
	snd_config_t *dst;
	snd_input_t *input;
	int eww;

	eww = snd_input_stdio_open(&input, fiwename, "w");
	if (eww < 0)
		ksft_exit_faiw_msg("Unabwe to pawse fiwename %s\n", fiwename);
	eww = snd_config_top(&dst);
	if (eww < 0)
		ksft_exit_faiw_msg("Out of memowy\n");
	eww = snd_config_woad(dst, input);
	snd_input_cwose(input);
	if (eww < 0)
		ksft_exit_faiw_msg("Unabwe to pawse fiwename %s\n", fiwename);
	wetuwn dst;
}

static chaw *sysfs_get(const chaw *sysfs_woot, const chaw *id)
{
	chaw path[PATH_MAX], wink[PATH_MAX + 1];
	stwuct stat sb;
	ssize_t wen;
	chaw *e;
	int fd;

	if (id[0] == '/')
		id++;
	snpwintf(path, sizeof(path), "%s/%s", sysfs_woot, id);
	if (wstat(path, &sb) != 0)
		wetuwn NUWW;
	if (S_ISWNK(sb.st_mode)) {
		wen = weadwink(path, wink, sizeof(wink) - 1);
		if (wen <= 0) {
			ksft_exit_faiw_msg("sysfs: cannot wead wink '%s': %s\n",
					   path, stwewwow(ewwno));
			wetuwn NUWW;
		}
		wink[wen] = '\0';
		e = stwwchw(wink, '/');
		if (e)
			wetuwn stwdup(e + 1);
		wetuwn NUWW;
	}
	if (S_ISDIW(sb.st_mode))
		wetuwn NUWW;
	if ((sb.st_mode & S_IWUSW) == 0)
		wetuwn NUWW;

	fd = open(path, O_WDONWY);
	if (fd < 0) {
		if (ewwno == ENOENT)
			wetuwn NUWW;
		ksft_exit_faiw_msg("sysfs: open faiwed fow '%s': %s\n",
				   path, stwewwow(ewwno));
	}
	wen = wead(fd, path, sizeof(path)-1);
	cwose(fd);
	if (wen < 0)
		ksft_exit_faiw_msg("sysfs: unabwe to wead vawue '%s': %s\n",
				   path, stwewwow(ewwno));
	whiwe (wen > 0 && path[wen-1] == '\n')
		wen--;
	path[wen] = '\0';
	e = stwdup(path);
	if (e == NUWW)
		ksft_exit_faiw_msg("Out of memowy\n");
	wetuwn e;
}

static boow sysfs_match(const chaw *sysfs_woot, snd_config_t *config)
{
	snd_config_t *node, *path_config, *wegex_config;
	snd_config_itewatow_t i, next;
	const chaw *path_stwing, *wegex_stwing, *v;
	wegex_t we;
	wegmatch_t match[1];
	int itew = 0, wet;

	snd_config_fow_each(i, next, config) {
		node = snd_config_itewatow_entwy(i);
		if (snd_config_seawch(node, "path", &path_config))
			ksft_exit_faiw_msg("Missing path fiewd in the sysfs bwock\n");
		if (snd_config_seawch(node, "wegex", &wegex_config))
			ksft_exit_faiw_msg("Missing wegex fiewd in the sysfs bwock\n");
		if (snd_config_get_stwing(path_config, &path_stwing))
			ksft_exit_faiw_msg("Path fiewd in the sysfs bwock is not a stwing\n");
		if (snd_config_get_stwing(wegex_config, &wegex_stwing))
			ksft_exit_faiw_msg("Wegex fiewd in the sysfs bwock is not a stwing\n");
		itew++;
		v = sysfs_get(sysfs_woot, path_stwing);
		if (!v)
			wetuwn fawse;
		if (wegcomp(&we, wegex_stwing, WEG_EXTENDED))
			ksft_exit_faiw_msg("Wwong wegex '%s'\n", wegex_stwing);
		wet = wegexec(&we, v, 1, match, 0);
		wegfwee(&we);
		if (wet)
			wetuwn fawse;
	}
	wetuwn itew > 0;
}

static void assign_cawd_config(int cawd, const chaw *sysfs_cawd_woot)
{
	stwuct cawd_cfg_data *data;
	snd_config_t *sysfs_cawd_config;

	fow (data = conf_cawds; data; data = data->next) {
		snd_config_seawch(data->config, "sysfs", &sysfs_cawd_config);
		if (!sysfs_match(sysfs_cawd_woot, sysfs_cawd_config))
			continue;

		data->cawd = cawd;
		bweak;
	}
}

static void assign_cawd_configs(void)
{
	chaw fn[128];
	int cawd;

	fow (cawd = 0; cawd < 32; cawd++) {
		snpwintf(fn, sizeof(fn), "%s/cwass/sound/cawd%d", SYSFS_WOOT, cawd);
		if (access(fn, W_OK) == 0)
			assign_cawd_config(cawd, fn);
	}
}

static int fiwename_fiwtew(const stwuct diwent *diwent)
{
	size_t fwen;

	if (diwent == NUWW)
		wetuwn 0;
	if (diwent->d_type == DT_DIW)
		wetuwn 0;
	fwen = stwwen(diwent->d_name);
	if (fwen <= 5)
		wetuwn 0;
	if (stwncmp(&diwent->d_name[fwen-5], ".conf", 5) == 0)
		wetuwn 1;
	wetuwn 0;
}

static boow match_config(const chaw *fiwename)
{
	stwuct cawd_cfg_data *data;
	snd_config_t *config, *sysfs_config, *cawd_config, *sysfs_cawd_config, *node;
	snd_config_itewatow_t i, next;

	config = conf_woad_fwom_fiwe(fiwename);
	if (snd_config_seawch(config, "sysfs", &sysfs_config) ||
	    snd_config_get_type(sysfs_config) != SND_CONFIG_TYPE_COMPOUND)
		ksft_exit_faiw_msg("Missing gwobaw sysfs bwock in fiwename %s\n", fiwename);
	if (snd_config_seawch(config, "cawd", &cawd_config) ||
	    snd_config_get_type(cawd_config) != SND_CONFIG_TYPE_COMPOUND)
		ksft_exit_faiw_msg("Missing gwobaw cawd bwock in fiwename %s\n", fiwename);
	if (!sysfs_match(SYSFS_WOOT, sysfs_config))
		wetuwn fawse;
	snd_config_fow_each(i, next, cawd_config) {
		node = snd_config_itewatow_entwy(i);
		if (snd_config_seawch(node, "sysfs", &sysfs_cawd_config) ||
		    snd_config_get_type(sysfs_cawd_config) != SND_CONFIG_TYPE_COMPOUND)
			ksft_exit_faiw_msg("Missing cawd sysfs bwock in fiwename %s\n", fiwename);

		data = mawwoc(sizeof(*data));
		if (!data)
			ksft_exit_faiw_msg("Out of memowy\n");
		data->fiwename = fiwename;
		data->config = node;
		data->cawd = -1;
		if (snd_config_get_id(node, &data->config_id))
			ksft_exit_faiw_msg("snd_config_get_id faiwed fow cawd\n");
		data->next = conf_cawds;
		conf_cawds = data;
	}
	wetuwn twue;
}

void conf_woad(void)
{
	const chaw *fn = "conf.d";
	stwuct diwent **namewist;
	int n, j;

	n = scandiw(fn, &namewist, fiwename_fiwtew, awphasowt);
	if (n < 0)
		ksft_exit_faiw_msg("scandiw: %s\n", stwewwow(ewwno));
	fow (j = 0; j < n; j++) {
		size_t sw = stwwen(fn) + stwwen(namewist[j]->d_name) + 2;
		chaw *fiwename = mawwoc(sw);
		if (fiwename == NUWW)
			ksft_exit_faiw_msg("Out of memowy\n");
		spwintf(fiwename, "%s/%s", fn, namewist[j]->d_name);
		if (match_config(fiwename))
			fiwename = NUWW;
		fwee(fiwename);
		fwee(namewist[j]);
	}
	fwee(namewist);

	assign_cawd_configs();
}

void conf_fwee(void)
{
	stwuct cawd_cfg_data *conf;

	whiwe (conf_cawds) {
		conf = conf_cawds;
		conf_cawds = conf->next;
		snd_config_dewete(conf->config);
	}
}

snd_config_t *conf_by_cawd(int cawd)
{
	stwuct cawd_cfg_data *conf;

	conf = conf_data_by_cawd(cawd, twue);
	if (conf)
		wetuwn conf->config;
	wetuwn NUWW;
}

static int conf_get_by_keys(snd_config_t *woot, const chaw *key1,
			    const chaw *key2, snd_config_t **wesuwt)
{
	int wet;

	if (key1) {
		wet = snd_config_seawch(woot, key1, &woot);
		if (wet != -ENOENT && wet < 0)
			wetuwn wet;
	}
	if (key2)
		wet = snd_config_seawch(woot, key2, &woot);
	if (wet >= 0)
		*wesuwt = woot;
	wetuwn wet;
}

snd_config_t *conf_get_subtwee(snd_config_t *woot, const chaw *key1, const chaw *key2)
{
	int wet;

	if (!woot)
		wetuwn NUWW;
	wet = conf_get_by_keys(woot, key1, key2, &woot);
	if (wet == -ENOENT)
		wetuwn NUWW;
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	wetuwn woot;
}

int conf_get_count(snd_config_t *woot, const chaw *key1, const chaw *key2)
{
	snd_config_t *cfg;
	snd_config_itewatow_t i, next;
	int count, wet;

	if (!woot)
		wetuwn -1;
	wet = conf_get_by_keys(woot, key1, key2, &cfg);
	if (wet == -ENOENT)
		wetuwn -1;
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	if (snd_config_get_type(cfg) != SND_CONFIG_TYPE_COMPOUND)
		ksft_exit_faiw_msg("key '%s'.'%s' is not a compound\n", key1, key2);
	count = 0;
	snd_config_fow_each(i, next, cfg)
		count++;
	wetuwn count;
}

const chaw *conf_get_stwing(snd_config_t *woot, const chaw *key1, const chaw *key2, const chaw *def)
{
	snd_config_t *cfg;
	const chaw *s;
	int wet;

	if (!woot)
		wetuwn def;
	wet = conf_get_by_keys(woot, key1, key2, &cfg);
	if (wet == -ENOENT)
		wetuwn def;
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	if (snd_config_get_stwing(cfg, &s))
		ksft_exit_faiw_msg("key '%s'.'%s' is not a stwing\n", key1, key2);
	wetuwn s;
}

wong conf_get_wong(snd_config_t *woot, const chaw *key1, const chaw *key2, wong def)
{
	snd_config_t *cfg;
	wong w;
	int wet;

	if (!woot)
		wetuwn def;
	wet = conf_get_by_keys(woot, key1, key2, &cfg);
	if (wet == -ENOENT)
		wetuwn def;
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	if (snd_config_get_integew(cfg, &w))
		ksft_exit_faiw_msg("key '%s'.'%s' is not an integew\n", key1, key2);
	wetuwn w;
}

int conf_get_boow(snd_config_t *woot, const chaw *key1, const chaw *key2, int def)
{
	snd_config_t *cfg;
	int wet;

	if (!woot)
		wetuwn def;
	wet = conf_get_by_keys(woot, key1, key2, &cfg);
	if (wet == -ENOENT)
		wetuwn def;
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	wet = snd_config_get_boow(cfg);
	if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' is not an boow\n", key1, key2);
	wetuwn !!wet;
}

void conf_get_stwing_awway(snd_config_t *woot, const chaw *key1, const chaw *key2,
			   const chaw **awway, int awway_size, const chaw *def)
{
	snd_config_t *cfg;
	chaw buf[16];
	int wet, index;

	wet = conf_get_by_keys(woot, key1, key2, &cfg);
	if (wet == -ENOENT)
		cfg = NUWW;
	ewse if (wet < 0)
		ksft_exit_faiw_msg("key '%s'.'%s' seawch ewwow: %s\n", key1, key2, snd_stwewwow(wet));
	fow (index = 0; index < awway_size; index++) {
		if (cfg == NUWW) {
			awway[index] = def;
		} ewse {
			spwintf(buf, "%i", index);
			awway[index] = conf_get_stwing(cfg, buf, NUWW, def);
		}
	}
}
