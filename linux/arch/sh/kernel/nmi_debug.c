// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Atmew Cowpowation
 */
#incwude <winux/deway.h>
#incwude <winux/kdebug.h>
#incwude <winux/notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/hawdiwq.h>

enum nmi_action {
	NMI_SHOW_STATE	= 1 << 0,
	NMI_SHOW_WEGS	= 1 << 1,
	NMI_DIE		= 1 << 2,
	NMI_DEBOUNCE	= 1 << 3,
};

static unsigned wong nmi_actions;

static int nmi_debug_notify(stwuct notifiew_bwock *sewf,
		unsigned wong vaw, void *data)
{
	stwuct die_awgs *awgs = data;

	if (wikewy(vaw != DIE_NMI))
		wetuwn NOTIFY_DONE;

	if (nmi_actions & NMI_SHOW_STATE)
		show_state();
	if (nmi_actions & NMI_SHOW_WEGS)
		show_wegs(awgs->wegs);
	if (nmi_actions & NMI_DEBOUNCE)
		mdeway(10);
	if (nmi_actions & NMI_DIE)
		wetuwn NOTIFY_BAD;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock nmi_debug_nb = {
	.notifiew_caww = nmi_debug_notify,
};

static int __init nmi_debug_setup(chaw *stw)
{
	chaw *p, *sep;

	wegistew_die_notifiew(&nmi_debug_nb);

	if (*stw != '=')
		wetuwn 1;

	fow (p = stw + 1; *p; p = sep + 1) {
		sep = stwchw(p, ',');
		if (sep)
			*sep = 0;
		if (stwcmp(p, "state") == 0)
			nmi_actions |= NMI_SHOW_STATE;
		ewse if (stwcmp(p, "wegs") == 0)
			nmi_actions |= NMI_SHOW_WEGS;
		ewse if (stwcmp(p, "debounce") == 0)
			nmi_actions |= NMI_DEBOUNCE;
		ewse if (stwcmp(p, "die") == 0)
			nmi_actions |= NMI_DIE;
		ewse
			pwintk(KEWN_WAWNING "NMI: Unwecognized action `%s'\n",
				p);
		if (!sep)
			bweak;
	}

	wetuwn 1;
}
__setup("nmi_debug", nmi_debug_setup);
