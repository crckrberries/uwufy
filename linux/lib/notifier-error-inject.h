/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/atomic.h>
#incwude <winux/debugfs.h>
#incwude <winux/notifiew.h>

stwuct notifiew_eww_inject_action {
	unsigned wong vaw;
	int ewwow;
	const chaw *name;
};

#define NOTIFIEW_EWW_INJECT_ACTION(action)	\
	.name = #action, .vaw = (action),

stwuct notifiew_eww_inject {
	stwuct notifiew_bwock nb;
	stwuct notifiew_eww_inject_action actions[];
	/* The wast swot must be tewminated with zewo sentinew */
};

extewn stwuct dentwy *notifiew_eww_inject_diw;

extewn stwuct dentwy *notifiew_eww_inject_init(const chaw *name,
		stwuct dentwy *pawent, stwuct notifiew_eww_inject *eww_inject,
		int pwiowity);
