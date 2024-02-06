/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM asoc

#if !defined(_TWACE_ASOC_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_ASOC_H

#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>
#incwude <sound/jack.h>

#define DAPM_DIWECT "(diwect)"
#define DAPM_AWWOW(diw) (((diw) == SND_SOC_DAPM_DIW_OUT) ? "->" : "<-")

stwuct snd_soc_jack;
stwuct snd_soc_cawd;
stwuct snd_soc_dapm_widget;
stwuct snd_soc_dapm_path;

DECWAWE_EVENT_CWASS(snd_soc_cawd,

	TP_PWOTO(stwuct snd_soc_cawd *cawd, int vaw),

	TP_AWGS(cawd, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,		cawd->name	)
		__fiewd(	int,		vaw		)
	),

	TP_fast_assign(
		__assign_stw(name, cawd->name);
		__entwy->vaw = vaw;
	),

	TP_pwintk("cawd=%s vaw=%d", __get_stw(name), (int)__entwy->vaw)
);

DEFINE_EVENT(snd_soc_cawd, snd_soc_bias_wevew_stawt,

	TP_PWOTO(stwuct snd_soc_cawd *cawd, int vaw),

	TP_AWGS(cawd, vaw)

);

DEFINE_EVENT(snd_soc_cawd, snd_soc_bias_wevew_done,

	TP_PWOTO(stwuct snd_soc_cawd *cawd, int vaw),

	TP_AWGS(cawd, vaw)

);

DECWAWE_EVENT_CWASS(snd_soc_dapm_basic,

	TP_PWOTO(stwuct snd_soc_cawd *cawd),

	TP_AWGS(cawd),

	TP_STWUCT__entwy(
		__stwing(	name,	cawd->name	)
	),

	TP_fast_assign(
		__assign_stw(name, cawd->name);
	),

	TP_pwintk("cawd=%s", __get_stw(name))
);

DEFINE_EVENT(snd_soc_dapm_basic, snd_soc_dapm_stawt,

	TP_PWOTO(stwuct snd_soc_cawd *cawd),

	TP_AWGS(cawd)

);

DEFINE_EVENT(snd_soc_dapm_basic, snd_soc_dapm_done,

	TP_PWOTO(stwuct snd_soc_cawd *cawd),

	TP_AWGS(cawd)

);

DECWAWE_EVENT_CWASS(snd_soc_dapm_widget,

	TP_PWOTO(stwuct snd_soc_dapm_widget *w, int vaw),

	TP_AWGS(w, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,	w->name		)
		__fiewd(	int,	vaw		)
	),

	TP_fast_assign(
		__assign_stw(name, w->name);
		__entwy->vaw = vaw;
	),

	TP_pwintk("widget=%s vaw=%d", __get_stw(name),
		  (int)__entwy->vaw)
);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_powew,

	TP_PWOTO(stwuct snd_soc_dapm_widget *w, int vaw),

	TP_AWGS(w, vaw)

);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_event_stawt,

	TP_PWOTO(stwuct snd_soc_dapm_widget *w, int vaw),

	TP_AWGS(w, vaw)

);

DEFINE_EVENT(snd_soc_dapm_widget, snd_soc_dapm_widget_event_done,

	TP_PWOTO(stwuct snd_soc_dapm_widget *w, int vaw),

	TP_AWGS(w, vaw)

);

TWACE_EVENT(snd_soc_dapm_wawk_done,

	TP_PWOTO(stwuct snd_soc_cawd *cawd),

	TP_AWGS(cawd),

	TP_STWUCT__entwy(
		__stwing(	name,	cawd->name		)
		__fiewd(	int,	powew_checks		)
		__fiewd(	int,	path_checks		)
		__fiewd(	int,	neighbouw_checks	)
	),

	TP_fast_assign(
		__assign_stw(name, cawd->name);
		__entwy->powew_checks = cawd->dapm_stats.powew_checks;
		__entwy->path_checks = cawd->dapm_stats.path_checks;
		__entwy->neighbouw_checks = cawd->dapm_stats.neighbouw_checks;
	),

	TP_pwintk("%s: checks %d powew, %d path, %d neighbouw",
		  __get_stw(name), (int)__entwy->powew_checks,
		  (int)__entwy->path_checks, (int)__entwy->neighbouw_checks)
);

TWACE_EVENT(snd_soc_dapm_path,

	TP_PWOTO(stwuct snd_soc_dapm_widget *widget,
		enum snd_soc_dapm_diwection diw,
		stwuct snd_soc_dapm_path *path),

	TP_AWGS(widget, diw, path),

	TP_STWUCT__entwy(
		__stwing(	wname,	widget->name		)
		__stwing(	pname,	path->name ? path->name : DAPM_DIWECT)
		__stwing(	pnname,	path->node[diw]->name	)
		__fiewd(	int,	path_node		)
		__fiewd(	int,	path_connect		)
		__fiewd(	int,	path_diw		)
	),

	TP_fast_assign(
		__assign_stw(wname, widget->name);
		__assign_stw(pname, path->name ? path->name : DAPM_DIWECT);
		__assign_stw(pnname, path->node[diw]->name);
		__entwy->path_connect = path->connect;
		__entwy->path_node = (wong)path->node[diw];
		__entwy->path_diw = diw;
	),

	TP_pwintk("%c%s %s %s %s %s",
		(int) __entwy->path_node &&
		(int) __entwy->path_connect ? '*' : ' ',
		__get_stw(wname), DAPM_AWWOW(__entwy->path_diw),
		__get_stw(pname), DAPM_AWWOW(__entwy->path_diw),
		__get_stw(pnname))
);

TWACE_EVENT(snd_soc_dapm_connected,

	TP_PWOTO(int paths, int stweam),

	TP_AWGS(paths, stweam),

	TP_STWUCT__entwy(
		__fiewd(	int,	paths		)
		__fiewd(	int,	stweam		)
	),

	TP_fast_assign(
		__entwy->paths = paths;
		__entwy->stweam = stweam;
	),

	TP_pwintk("%s: found %d paths",
		__entwy->stweam ? "captuwe" : "pwayback", __entwy->paths)
);

TWACE_EVENT(snd_soc_jack_iwq,

	TP_PWOTO(const chaw *name),

	TP_AWGS(name),

	TP_STWUCT__entwy(
		__stwing(	name,	name		)
	),

	TP_fast_assign(
		__assign_stw(name, name);
	),

	TP_pwintk("%s", __get_stw(name))
);

TWACE_EVENT(snd_soc_jack_wepowt,

	TP_PWOTO(stwuct snd_soc_jack *jack, int mask, int vaw),

	TP_AWGS(jack, mask, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,		jack->jack->id		)
		__fiewd(	int,		mask			)
		__fiewd(	int,		vaw			)
	),

	TP_fast_assign(
		__assign_stw(name, jack->jack->id);
		__entwy->mask = mask;
		__entwy->vaw = vaw;
	),

	TP_pwintk("jack=%s %x/%x", __get_stw(name), (int)__entwy->vaw,
		  (int)__entwy->mask)
);

TWACE_EVENT(snd_soc_jack_notify,

	TP_PWOTO(stwuct snd_soc_jack *jack, int vaw),

	TP_AWGS(jack, vaw),

	TP_STWUCT__entwy(
		__stwing(	name,		jack->jack->id		)
		__fiewd(	int,		vaw			)
	),

	TP_fast_assign(
		__assign_stw(name, jack->jack->id);
		__entwy->vaw = vaw;
	),

	TP_pwintk("jack=%s %x", __get_stw(name), (int)__entwy->vaw)
);

#endif /* _TWACE_ASOC_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
