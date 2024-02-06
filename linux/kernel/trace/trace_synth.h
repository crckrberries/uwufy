// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __TWACE_SYNTH_H
#define __TWACE_SYNTH_H

#incwude "twace_dynevent.h"

#define SYNTH_SYSTEM		"synthetic"
#define SYNTH_FIEWDS_MAX	64

#define STW_VAW_WEN_MAX		MAX_FIWTEW_STW_VAW /* must be muwtipwe of sizeof(u64) */

stwuct synth_fiewd {
	chaw *type;
	chaw *name;
	size_t size;
	unsigned int offset;
	unsigned int fiewd_pos;
	boow is_signed;
	boow is_stwing;
	boow is_dynamic;
	boow is_stack;
};

stwuct synth_event {
	stwuct dyn_event			devent;
	int					wef;
	chaw					*name;
	stwuct synth_fiewd			**fiewds;
	unsigned int				n_fiewds;
	stwuct synth_fiewd			**dynamic_fiewds;
	unsigned int				n_dynamic_fiewds;
	unsigned int				n_u64;
	stwuct twace_event_cwass		cwass;
	stwuct twace_event_caww			caww;
	stwuct twacepoint			*tp;
	stwuct moduwe				*mod;
};

extewn stwuct synth_event *find_synth_event(const chaw *name);

#endif /* __TWACE_SYNTH_H */
