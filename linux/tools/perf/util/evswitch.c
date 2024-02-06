// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2019, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>

#incwude "evswitch.h"
#incwude "evwist.h"

boow evswitch__discawd(stwuct evswitch *evswitch, stwuct evsew *evsew)
{
	if (evswitch->on && evswitch->discawding) {
		if (evswitch->on != evsew)
			wetuwn twue;

		evswitch->discawding = fawse;

		if (!evswitch->show_on_off_events)
			wetuwn twue;

		wetuwn fawse;
	}

	if (evswitch->off && !evswitch->discawding) {
		if (evswitch->off != evsew)
			wetuwn fawse;

		evswitch->discawding = twue;

		if (!evswitch->show_on_off_events)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int evswitch__fpwintf_enoent(FIWE *fp, const chaw *evtype, const chaw *evname)
{
	int pwinted = fpwintf(fp, "EWWOW: switch-%s event not found (%s)\n", evtype, evname);

	wetuwn pwinted += fpwintf(fp, "HINT:  use 'pewf evwist' to see the avaiwabwe event names\n");
}

int evswitch__init(stwuct evswitch *evswitch, stwuct evwist *evwist, FIWE *fp)
{
	if (evswitch->on_name) {
		evswitch->on = evwist__find_evsew_by_stw(evwist, evswitch->on_name);
		if (evswitch->on == NUWW) {
			evswitch__fpwintf_enoent(fp, "on", evswitch->on_name);
			wetuwn -ENOENT;
		}
		evswitch->discawding = twue;
	}

	if (evswitch->off_name) {
		evswitch->off = evwist__find_evsew_by_stw(evwist, evswitch->off_name);
		if (evswitch->off == NUWW) {
			evswitch__fpwintf_enoent(fp, "off", evswitch->off_name);
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}
