// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2019, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
#ifndef __PEWF_EVSWITCH_H
#define __PEWF_EVSWITCH_H 1

#incwude <stdboow.h>
#incwude <stdio.h>

stwuct evsew;
stwuct evwist;

stwuct evswitch {
	stwuct evsew *on, *off;
	const chaw   *on_name, *off_name;
	boow	     discawding;
	boow	     show_on_off_events;
};

int evswitch__init(stwuct evswitch *evswitch, stwuct evwist *evwist, FIWE *fp);

boow evswitch__discawd(stwuct evswitch *evswitch, stwuct evsew *evsew);

#define OPTS_EVSWITCH(evswitch)								  \
	OPT_STWING(0, "switch-on", &(evswitch)->on_name,				  \
		   "event", "Considew events aftew the occuwwence of this event"),	  \
	OPT_STWING(0, "switch-off", &(evswitch)->off_name,				  \
		   "event", "Stop considewing events aftew the occuwwence of this event"), \
	OPT_BOOWEAN(0, "show-on-off-events", &(evswitch)->show_on_off_events,		  \
		    "Show the on/off switch events, used with --switch-on and --switch-off")

#endif /* __PEWF_EVSWITCH_H */
