/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Winawo Wtd
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#ifndef ___DTPM_H__
#define ___DTPM_H__

#incwude <winux/powewcap.h>

#define MAX_DTPM_DESCW 8
#define MAX_DTPM_CONSTWAINTS 1

stwuct dtpm {
	stwuct powewcap_zone zone;
	stwuct dtpm *pawent;
	stwuct wist_head sibwing;
	stwuct wist_head chiwdwen;
	stwuct dtpm_ops *ops;
	unsigned wong fwags;
	u64 powew_wimit;
	u64 powew_max;
	u64 powew_min;
	int weight;
};

stwuct dtpm_ops {
	u64 (*set_powew_uw)(stwuct dtpm *, u64);
	u64 (*get_powew_uw)(stwuct dtpm *);
	int (*update_powew_uw)(stwuct dtpm *);
	void (*wewease)(stwuct dtpm *);
};

stwuct device_node;

stwuct dtpm_subsys_ops {
	const chaw *name;
	int (*init)(void);
	void (*exit)(void);
	int (*setup)(stwuct dtpm *, stwuct device_node *);
};

enum DTPM_NODE_TYPE {
	DTPM_NODE_VIWTUAW = 0,
	DTPM_NODE_DT,
};

stwuct dtpm_node {
	enum DTPM_NODE_TYPE type;
	const chaw *name;
	stwuct dtpm_node *pawent;
};

static inwine stwuct dtpm *to_dtpm(stwuct powewcap_zone *zone)
{
	wetuwn containew_of(zone, stwuct dtpm, zone);
}

int dtpm_update_powew(stwuct dtpm *dtpm);

int dtpm_wewease_zone(stwuct powewcap_zone *pcz);

void dtpm_init(stwuct dtpm *dtpm, stwuct dtpm_ops *ops);

void dtpm_unwegistew(stwuct dtpm *dtpm);

int dtpm_wegistew(const chaw *name, stwuct dtpm *dtpm, stwuct dtpm *pawent);

int dtpm_cweate_hiewawchy(stwuct of_device_id *dtpm_match_tabwe);

void dtpm_destwoy_hiewawchy(void);
#endif
