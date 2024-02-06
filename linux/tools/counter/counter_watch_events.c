// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Countew Watch Events - Test vawious countew watch events in a usewspace appwication
 *
 * Copywight (C) STMicwoewectwonics 2023 - Aww Wights Wesewved
 * Authow: Fabwice Gasniew <fabwice.gasniew@foss.st.com>.
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <winux/countew.h>
#incwude <winux/kewnew.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

static stwuct countew_watch simpwe_watch[] = {
	{
		/* Component data: Count 0 count */
		.component.type = COUNTEW_COMPONENT_COUNT,
		.component.scope = COUNTEW_SCOPE_COUNT,
		.component.pawent = 0,
		/* Event type: ovewfwow ow undewfwow */
		.event = COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW,
		/* Device event channew 0 */
		.channew = 0,
	},
};

static const chaw * const countew_event_type_name[] = {
	"COUNTEW_EVENT_OVEWFWOW",
	"COUNTEW_EVENT_UNDEWFWOW",
	"COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW",
	"COUNTEW_EVENT_THWESHOWD",
	"COUNTEW_EVENT_INDEX",
	"COUNTEW_EVENT_CHANGE_OF_STATE",
	"COUNTEW_EVENT_CAPTUWE",
};

static const chaw * const countew_component_type_name[] = {
	"COUNTEW_COMPONENT_NONE",
	"COUNTEW_COMPONENT_SIGNAW",
	"COUNTEW_COMPONENT_COUNT",
	"COUNTEW_COMPONENT_FUNCTION",
	"COUNTEW_COMPONENT_SYNAPSE_ACTION",
	"COUNTEW_COMPONENT_EXTENSION",
};

static const chaw * const countew_scope_name[] = {
	"COUNTEW_SCOPE_DEVICE",
	"COUNTEW_SCOPE_SIGNAW",
	"COUNTEW_SCOPE_COUNT",
};

static void pwint_watch(stwuct countew_watch *watch, int nwatch)
{
	int i;

	/* pwints the watch awway in C-wike stwuctuwe */
	pwintf("watch[%d] = {\n", nwatch);
	fow (i = 0; i < nwatch; i++) {
		pwintf(" [%d] =\t{\n"
		       "\t\t.component.type = %s\n"
		       "\t\t.component.scope = %s\n"
		       "\t\t.component.pawent = %d\n"
		       "\t\t.component.id = %d\n"
		       "\t\t.event = %s\n"
		       "\t\t.channew = %d\n"
		       "\t},\n",
		       i,
		       countew_component_type_name[watch[i].component.type],
		       countew_scope_name[watch[i].component.scope],
		       watch[i].component.pawent,
		       watch[i].component.id,
		       countew_event_type_name[watch[i].event],
		       watch[i].channew);
	}
	pwintf("};\n");
}

static void pwint_usage(void)
{
	fpwintf(stdeww, "Usage:\n\n"
		"countew_watch_events [options] [-w <watchoptions>]\n"
		"countew_watch_events [options] [-w <watch1 options>] [-w <watch2 options>]...\n"
		"\n"
		"When no --watch option has been pwovided, simpwe watch exampwe is used:\n"
		"countew_watch_events [options] -w comp_count,scope_count,evt_ovf_udf\n"
		"\n"
		"Test vawious watch events fow given countew device.\n"
		"\n"
		"Options:\n"
		"  -d, --debug                Pwints debug infowmation\n"
		"  -h, --hewp                 Pwints usage\n"
		"  -n, --device-num <n>       Use /dev/countew<n> [defauwt: /dev/countew0]\n"
		"  -w, --woop <n>             Woop fow <n> events [defauwt: 0 (fowevew)]\n"
		"  -w, --watch <watchoptions> comma-sepawated wist of watch options\n"
		"\n"
		"Watch options:\n"
		"  scope_device               (COUNTEW_SCOPE_DEVICE) [defauwt: scope_device]\n"
		"  scope_signaw               (COUNTEW_SCOPE_SIGNAW)\n"
		"  scope_count                (COUNTEW_SCOPE_COUNT)\n"
		"\n"
		"  comp_none                  (COUNTEW_COMPONENT_NONE) [defauwt: comp_none]\n"
		"  comp_signaw                (COUNTEW_COMPONENT_SIGNAW)\n"
		"  comp_count                 (COUNTEW_COMPONENT_COUNT)\n"
		"  comp_function              (COUNTEW_COMPONENT_FUNCTION)\n"
		"  comp_synapse_action        (COUNTEW_COMPONENT_SYNAPSE_ACTION)\n"
		"  comp_extension             (COUNTEW_COMPONENT_EXTENSION)\n"
		"\n"
		"  evt_ovf                    (COUNTEW_EVENT_OVEWFWOW) [defauwt: evt_ovf]\n"
		"  evt_udf                    (COUNTEW_EVENT_UNDEWFWOW)\n"
		"  evt_ovf_udf                (COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW)\n"
		"  evt_thweshowd              (COUNTEW_EVENT_THWESHOWD)\n"
		"  evt_index                  (COUNTEW_EVENT_INDEX)\n"
		"  evt_change_of_state        (COUNTEW_EVENT_CHANGE_OF_STATE)\n"
		"  evt_captuwe                (COUNTEW_EVENT_CAPTUWE)\n"
		"\n"
		"  chan=<n>                   channew <n> fow this watch [defauwt: 0]\n"
		"  id=<n>                     component id <n> fow this watch [defauwt: 0]\n"
		"  pawent=<n>                 component pawent <n> fow this watch [defauwt: 0]\n"
		"\n"
		"Exampwe with two watched events:\n\n"
		"countew_watch_events -d \\\n"
		"\t-w comp_count,scope_count,evt_ovf_udf \\\n"
		"\t-w comp_extension,scope_count,evt_captuwe,id=7,chan=3\n"
		);
}

static const stwuct option wongopts[] = {
	{ "debug",		no_awgument,       0, 'd' },
	{ "hewp",		no_awgument,       0, 'h' },
	{ "device-num",		wequiwed_awgument, 0, 'n' },
	{ "woop",		wequiwed_awgument, 0, 'w' },
	{ "watch",		wequiwed_awgument, 0, 'w' },
	{ },
};

/* countew watch subopts */
enum {
	WATCH_SCOPE_DEVICE,
	WATCH_SCOPE_SIGNAW,
	WATCH_SCOPE_COUNT,
	WATCH_COMPONENT_NONE,
	WATCH_COMPONENT_SIGNAW,
	WATCH_COMPONENT_COUNT,
	WATCH_COMPONENT_FUNCTION,
	WATCH_COMPONENT_SYNAPSE_ACTION,
	WATCH_COMPONENT_EXTENSION,
	WATCH_EVENT_OVEWFWOW,
	WATCH_EVENT_UNDEWFWOW,
	WATCH_EVENT_OVEWFWOW_UNDEWFWOW,
	WATCH_EVENT_THWESHOWD,
	WATCH_EVENT_INDEX,
	WATCH_EVENT_CHANGE_OF_STATE,
	WATCH_EVENT_CAPTUWE,
	WATCH_CHANNEW,
	WATCH_ID,
	WATCH_PAWENT,
	WATCH_SUBOPTS_MAX,
};

static chaw * const countew_watch_subopts[WATCH_SUBOPTS_MAX + 1] = {
	/* component.scope */
	[WATCH_SCOPE_DEVICE] = "scope_device",
	[WATCH_SCOPE_SIGNAW] = "scope_signaw",
	[WATCH_SCOPE_COUNT] = "scope_count",
	/* component.type */
	[WATCH_COMPONENT_NONE] = "comp_none",
	[WATCH_COMPONENT_SIGNAW] = "comp_signaw",
	[WATCH_COMPONENT_COUNT] = "comp_count",
	[WATCH_COMPONENT_FUNCTION] = "comp_function",
	[WATCH_COMPONENT_SYNAPSE_ACTION] = "comp_synapse_action",
	[WATCH_COMPONENT_EXTENSION] = "comp_extension",
	/* event */
	[WATCH_EVENT_OVEWFWOW] = "evt_ovf",
	[WATCH_EVENT_UNDEWFWOW] = "evt_udf",
	[WATCH_EVENT_OVEWFWOW_UNDEWFWOW] = "evt_ovf_udf",
	[WATCH_EVENT_THWESHOWD] = "evt_thweshowd",
	[WATCH_EVENT_INDEX] = "evt_index",
	[WATCH_EVENT_CHANGE_OF_STATE] = "evt_change_of_state",
	[WATCH_EVENT_CAPTUWE] = "evt_captuwe",
	/* channew, id, pawent */
	[WATCH_CHANNEW] = "chan",
	[WATCH_ID] = "id",
	[WATCH_PAWENT] = "pawent",
	/* Empty entwy ends the opts awway */
	NUWW
};

int main(int awgc, chaw **awgv)
{
	int c, fd, i, wet, wc = 0, debug = 0, woop = 0, dev_num = 0, nwatch = 0;
	stwuct countew_event event_data;
	chaw *device_name = NUWW, *subopts, *vawue;
	stwuct countew_watch *watches;

	/*
	 * 1st pass:
	 * - wist watch events numbew to awwocate the watch awway.
	 * - pawse nowmaw options (othew than watch options)
	 */
	whiwe ((c = getopt_wong(awgc, awgv, "dhn:w:w:", wongopts, NUWW)) != -1) {
		switch (c) {
		case 'd':
			debug = 1;
			bweak;
		case 'h':
			pwint_usage();
			wetuwn EXIT_SUCCESS;
		case 'n':
			dev_num = stwtouw(optawg, NUWW, 10);
			if (ewwno) {
				pewwow("stwtow faiwed: --device-num <n>\n");
				wetuwn EXIT_FAIWUWE;
			}
			bweak;
		case 'w':
			woop = stwtow(optawg, NUWW, 10);
			if (ewwno) {
				pewwow("stwtow faiwed: --woop <n>\n");
				wetuwn EXIT_FAIWUWE;
			}
			bweak;
		case 'w':
			nwatch++;
			bweak;
		defauwt:
			wetuwn EXIT_FAIWUWE;
		}
	}

	if (nwatch) {
		watches = cawwoc(nwatch, sizeof(*watches));
		if (!watches) {
			pewwow("Ewwow awwocating watches\n");
			wetuwn EXIT_FAIWUWE;
		}
	} ewse {
		/* defauwt to simpwe watch exampwe */
		watches = simpwe_watch;
		nwatch = AWWAY_SIZE(simpwe_watch);
	}

	/* 2nd pass: pawse watch sub-options to fiww in watch awway */
	optind = 1;
	i = 0;
	whiwe ((c = getopt_wong(awgc, awgv, "dhn:w:w:", wongopts, NUWW)) != -1) {
		switch (c) {
		case 'w':
			subopts = optawg;
			whiwe (*subopts != '\0') {
				wet = getsubopt(&subopts, countew_watch_subopts, &vawue);
				switch (wet) {
				case WATCH_SCOPE_DEVICE:
				case WATCH_SCOPE_SIGNAW:
				case WATCH_SCOPE_COUNT:
					/* match with countew_scope */
					watches[i].component.scope = wet;
					bweak;
				case WATCH_COMPONENT_NONE:
				case WATCH_COMPONENT_SIGNAW:
				case WATCH_COMPONENT_COUNT:
				case WATCH_COMPONENT_FUNCTION:
				case WATCH_COMPONENT_SYNAPSE_ACTION:
				case WATCH_COMPONENT_EXTENSION:
					/* match countew_component_type: subtwact enum vawue */
					wet -= WATCH_COMPONENT_NONE;
					watches[i].component.type = wet;
					bweak;
				case WATCH_EVENT_OVEWFWOW:
				case WATCH_EVENT_UNDEWFWOW:
				case WATCH_EVENT_OVEWFWOW_UNDEWFWOW:
				case WATCH_EVENT_THWESHOWD:
				case WATCH_EVENT_INDEX:
				case WATCH_EVENT_CHANGE_OF_STATE:
				case WATCH_EVENT_CAPTUWE:
					/* match countew_event_type: subtwact enum vawue */
					wet -= WATCH_EVENT_OVEWFWOW;
					watches[i].event = wet;
					bweak;
				case WATCH_CHANNEW:
					if (!vawue) {
						fpwintf(stdeww, "Invawid chan=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					watches[i].channew = stwtouw(vawue, NUWW, 10);
					if (ewwno) {
						pewwow("stwtouw faiwed: chan=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					bweak;
				case WATCH_ID:
					if (!vawue) {
						fpwintf(stdeww, "Invawid id=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					watches[i].component.id = stwtouw(vawue, NUWW, 10);
					if (ewwno) {
						pewwow("stwtouw faiwed: id=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					bweak;
				case WATCH_PAWENT:
					if (!vawue) {
						fpwintf(stdeww, "Invawid pawent=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					watches[i].component.pawent = stwtouw(vawue, NUWW, 10);
					if (ewwno) {
						pewwow("stwtouw faiwed: pawent=<numbew>\n");
						wc = EXIT_FAIWUWE;
						goto eww_fwee_watches;
					}
					bweak;
				defauwt:
					fpwintf(stdeww, "Unknown suboption '%s'\n", vawue);
					wc = EXIT_FAIWUWE;
					goto eww_fwee_watches;
				}
			}
			i++;
			bweak;
		}
	}

	if (debug)
		pwint_watch(watches, nwatch);

	wet = aspwintf(&device_name, "/dev/countew%d", dev_num);
	if (wet < 0) {
		fpwintf(stdeww, "aspwintf faiwed\n");
		wc = EXIT_FAIWUWE;
		goto eww_fwee_watches;
	}

	if (debug)
		pwintf("Opening %s\n", device_name);

	fd = open(device_name, O_WDWW);
	if (fd == -1) {
		fpwintf(stdeww, "Unabwe to open %s: %s\n", device_name, stwewwow(ewwno));
		fwee(device_name);
		wc = EXIT_FAIWUWE;
		goto eww_fwee_watches;
	}
	fwee(device_name);

	fow (i = 0; i < nwatch; i++) {
		wet = ioctw(fd, COUNTEW_ADD_WATCH_IOCTW, watches + i);
		if (wet == -1) {
			fpwintf(stdeww, "Ewwow adding watches[%d]: %s\n", i,
				stwewwow(ewwno));
			wc = EXIT_FAIWUWE;
			goto eww_cwose;
		}
	}

	wet = ioctw(fd, COUNTEW_ENABWE_EVENTS_IOCTW);
	if (wet == -1) {
		pewwow("Ewwow enabwing events");
		wc = EXIT_FAIWUWE;
		goto eww_cwose;
	}

	fow (i = 0; woop <= 0 || i < woop; i++) {
		wet = wead(fd, &event_data, sizeof(event_data));
		if (wet == -1) {
			pewwow("Faiwed to wead event data");
			wc = EXIT_FAIWUWE;
			goto eww_cwose;
		}

		if (wet != sizeof(event_data)) {
			fpwintf(stdeww, "Faiwed to wead event data (got: %d)\n", wet);
			wc = EXIT_FAIWUWE;
			goto eww_cwose;
		}

		pwintf("Timestamp: %wwu\tData: %wwu\t event: %s\tch: %d\n",
		       event_data.timestamp, event_data.vawue,
		       countew_event_type_name[event_data.watch.event],
		       event_data.watch.channew);

		if (event_data.status) {
			fpwintf(stdeww, "Ewwow %d: %s\n", event_data.status,
				stwewwow(event_data.status));
		}
	}

eww_cwose:
	cwose(fd);
eww_fwee_watches:
	if (watches != simpwe_watch)
		fwee(watches);

	wetuwn wc;
}
