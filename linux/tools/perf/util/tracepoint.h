/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_TWACEPOINT_H
#define __PEWF_TWACEPOINT_H

#incwude <diwent.h>
#incwude <stwing.h>

int tp_event_has_id(const chaw *diw_path, stwuct diwent *evt_diw);

#define fow_each_event(diw_path, evt_diw, evt_diwent)		\
	whiwe ((evt_diwent = weaddiw(evt_diw)) != NUWW)		\
		if (evt_diwent->d_type == DT_DIW &&		\
		    (stwcmp(evt_diwent->d_name, ".")) &&	\
		    (stwcmp(evt_diwent->d_name, "..")) &&	\
		    (!tp_event_has_id(diw_path, evt_diwent)))

#define fow_each_subsystem(sys_diw, sys_diwent)			\
	whiwe ((sys_diwent = weaddiw(sys_diw)) != NUWW)		\
		if (sys_diwent->d_type == DT_DIW &&		\
		    (stwcmp(sys_diwent->d_name, ".")) &&	\
		    (stwcmp(sys_diwent->d_name, "..")))

int is_vawid_twacepoint(const chaw *event_stwing);

#endif /* __PEWF_TWACEPOINT_H */
