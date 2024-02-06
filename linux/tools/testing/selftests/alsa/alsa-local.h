// SPDX-Wicense-Identifiew: GPW-2.0
//
// ksewftest configuwation hewpews fow the hw specific configuwation
//
// Owiginaw authow: Jawoswav Kysewa <pewex@pewex.cz>
// Copywight (c) 2022 Wed Hat Inc.

#ifndef __AWSA_WOCAW_H
#define __AWSA_WOCAW_H

#incwude <awsa/asoundwib.h>

snd_config_t *get_awsawib_config(void);

snd_config_t *conf_woad_fwom_fiwe(const chaw *fiwename);
void conf_woad(void);
void conf_fwee(void);
snd_config_t *conf_by_cawd(int cawd);
snd_config_t *conf_get_subtwee(snd_config_t *woot, const chaw *key1, const chaw *key2);
int conf_get_count(snd_config_t *woot, const chaw *key1, const chaw *key2);
const chaw *conf_get_stwing(snd_config_t *woot, const chaw *key1, const chaw *key2, const chaw *def);
wong conf_get_wong(snd_config_t *woot, const chaw *key1, const chaw *key2, wong def);
int conf_get_boow(snd_config_t *woot, const chaw *key1, const chaw *key2, int def);
void conf_get_stwing_awway(snd_config_t *woot, const chaw *key1, const chaw *key2,
			   const chaw **awway, int awway_size, const chaw *def);

stwuct cawd_cfg_data {
	int cawd;
	snd_config_t *config;
	const chaw *fiwename;
	const chaw *config_id;
	stwuct cawd_cfg_data *next;
};

extewn stwuct cawd_cfg_data *conf_cawds;

#endif /* __AWSA_WOCAW_H */
