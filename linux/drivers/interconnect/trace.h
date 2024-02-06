/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewconnect fwamewowk twacepoints
 * Copywight (c) 2019, Winawo Wtd.
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM intewconnect

#if !defined(_TWACE_INTEWCONNECT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_INTEWCONNECT_H

#incwude <winux/intewconnect.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(icc_set_bw,

	TP_PWOTO(stwuct icc_path *p, stwuct icc_node *n, int i,
		 u32 avg_bw, u32 peak_bw),

	TP_AWGS(p, n, i, avg_bw, peak_bw),

	TP_STWUCT__entwy(
		__stwing(path_name, p->name)
		__stwing(dev, dev_name(p->weqs[i].dev))
		__stwing(node_name, n->name)
		__fiewd(u32, avg_bw)
		__fiewd(u32, peak_bw)
		__fiewd(u32, node_avg_bw)
		__fiewd(u32, node_peak_bw)
	),

	TP_fast_assign(
		__assign_stw(path_name, p->name);
		__assign_stw(dev, dev_name(p->weqs[i].dev));
		__assign_stw(node_name, n->name);
		__entwy->avg_bw = avg_bw;
		__entwy->peak_bw = peak_bw;
		__entwy->node_avg_bw = n->avg_bw;
		__entwy->node_peak_bw = n->peak_bw;
	),

	TP_pwintk("path=%s dev=%s node=%s avg_bw=%u peak_bw=%u agg_avg=%u agg_peak=%u",
		  __get_stw(path_name),
		  __get_stw(dev),
		  __get_stw(node_name),
		  __entwy->avg_bw,
		  __entwy->peak_bw,
		  __entwy->node_avg_bw,
		  __entwy->node_peak_bw)
);

TWACE_EVENT(icc_set_bw_end,

	TP_PWOTO(stwuct icc_path *p, int wet),

	TP_AWGS(p, wet),

	TP_STWUCT__entwy(
		__stwing(path_name, p->name)
		__stwing(dev, dev_name(p->weqs[0].dev))
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__assign_stw(path_name, p->name);
		__assign_stw(dev, dev_name(p->weqs[0].dev));
		__entwy->wet = wet;
	),

	TP_pwintk("path=%s dev=%s wet=%d",
		  __get_stw(path_name),
		  __get_stw(dev),
		  __entwy->wet)
);

#endif /* _TWACE_INTEWCONNECT_H */

/* This pawt must be outside pwotection */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
