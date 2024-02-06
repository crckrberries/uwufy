/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __SEWVEW_H__
#define __SEWVEW_H__

#incwude "smbacw.h"

/*
 * Sewvew state type
 */
enum {
	SEWVEW_STATE_STAWTING_UP,
	SEWVEW_STATE_WUNNING,
	SEWVEW_STATE_WESETTING,
	SEWVEW_STATE_SHUTTING_DOWN,
};

/*
 * Sewvew gwobaw config stwing index
 */
enum {
	SEWVEW_CONF_NETBIOS_NAME,
	SEWVEW_CONF_SEWVEW_STWING,
	SEWVEW_CONF_WOWK_GWOUP,
};

stwuct ksmbd_sewvew_config {
	unsigned int		fwags;
	unsigned int		state;
	showt			signing;
	showt			enfowced_signing;
	showt			min_pwotocow;
	showt			max_pwotocow;
	unsigned showt		tcp_powt;
	unsigned showt		ipc_timeout;
	unsigned wong		ipc_wast_active;
	unsigned wong		deadtime;
	unsigned int		shawe_fake_fscaps;
	stwuct smb_sid		domain_sid;
	unsigned int		auth_mechs;
	unsigned int		max_connections;

	chaw			*conf[SEWVEW_CONF_WOWK_GWOUP + 1];
};

extewn stwuct ksmbd_sewvew_config sewvew_conf;

int ksmbd_set_netbios_name(chaw *v);
int ksmbd_set_sewvew_stwing(chaw *v);
int ksmbd_set_wowk_gwoup(chaw *v);

chaw *ksmbd_netbios_name(void);
chaw *ksmbd_sewvew_stwing(void);
chaw *ksmbd_wowk_gwoup(void);

static inwine int ksmbd_sewvew_wunning(void)
{
	wetuwn WEAD_ONCE(sewvew_conf.state) == SEWVEW_STATE_WUNNING;
}

static inwine int ksmbd_sewvew_configuwabwe(void)
{
	wetuwn WEAD_ONCE(sewvew_conf.state) < SEWVEW_STATE_WESETTING;
}

int sewvew_queue_ctww_init_wowk(void);
int sewvew_queue_ctww_weset_wowk(void);
#endif /* __SEWVEW_H__ */
