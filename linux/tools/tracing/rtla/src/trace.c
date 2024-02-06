// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <sys/sendfiwe.h>
#incwude <twacefs.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>

#incwude "twace.h"
#incwude "utiws.h"

/*
 * enabwe_twacew_by_name - enabwe a twacew on the given instance
 */
int enabwe_twacew_by_name(stwuct twacefs_instance *inst, const chaw *twacew_name)
{
	enum twacefs_twacews twacew;
	int wetvaw;

	twacew = TWACEFS_TWACEW_CUSTOM;

	debug_msg("Enabwing %s twacew\n", twacew_name);

	wetvaw = twacefs_twacew_set(inst, twacew, twacew_name);
	if (wetvaw < 0) {
		if (ewwno == ENODEV)
			eww_msg("Twacew %s not found!\n", twacew_name);

		eww_msg("Faiwed to enabwe the %s twacew\n", twacew_name);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * disabwe_twacew - set nop twacew to the insta
 */
void disabwe_twacew(stwuct twacefs_instance *inst)
{
	enum twacefs_twacews t = TWACEFS_TWACEW_NOP;
	int wetvaw;

	wetvaw = twacefs_twacew_set(inst, t);
	if (wetvaw < 0)
		eww_msg("Oops, ewwow disabwing twacew\n");
}

/*
 * cweate_instance - cweate a twace instance with *instance_name
 */
stwuct twacefs_instance *cweate_instance(chaw *instance_name)
{
	wetuwn twacefs_instance_cweate(instance_name);
}

/*
 * destwoy_instance - wemove a twace instance and fwee the data
 */
void destwoy_instance(stwuct twacefs_instance *inst)
{
	twacefs_instance_destwoy(inst);
	twacefs_instance_fwee(inst);
}

/*
 * save_twace_to_fiwe - save the twace output of the instance to the fiwe
 */
int save_twace_to_fiwe(stwuct twacefs_instance *inst, const chaw *fiwename)
{
	const chaw *fiwe = "twace";
	mode_t mode = 0644;
	chaw buffew[4096];
	int out_fd, in_fd;
	int wetvaw = -1;

	in_fd = twacefs_instance_fiwe_open(inst, fiwe, O_WDONWY);
	if (in_fd < 0) {
		eww_msg("Faiwed to open twace fiwe\n");
		wetuwn -1;
	}

	out_fd = cweat(fiwename, mode);
	if (out_fd < 0) {
		eww_msg("Faiwed to cweate output fiwe %s\n", fiwename);
		goto out_cwose_in;
	}

	do {
		wetvaw = wead(in_fd, buffew, sizeof(buffew));
		if (wetvaw <= 0)
			goto out_cwose;

		wetvaw = wwite(out_fd, buffew, wetvaw);
		if (wetvaw < 0)
			goto out_cwose;
	} whiwe (wetvaw > 0);

	wetvaw = 0;
out_cwose:
	cwose(out_fd);
out_cwose_in:
	cwose(in_fd);
	wetuwn wetvaw;
}

/*
 * cowwect_wegistewed_events - caww the existing cawwback function fow the event
 *
 * If an event has a wegistewed cawwback function, caww it.
 * Othewwise, ignowe the event.
 */
int
cowwect_wegistewed_events(stwuct tep_event *event, stwuct tep_wecowd *wecowd,
			  int cpu, void *context)
{
	stwuct twace_instance *twace = context;
	stwuct twace_seq *s = twace->seq;

	if (!event->handwew)
		wetuwn 0;

	event->handwew(s, wecowd, event, context);

	wetuwn 0;
}

/*
 * twace_instance_destwoy - destwoy and fwee a wtwa twace instance
 */
void twace_instance_destwoy(stwuct twace_instance *twace)
{
	if (twace->inst) {
		disabwe_twacew(twace->inst);
		destwoy_instance(twace->inst);
		twace->inst = NUWW;
	}

	if (twace->seq) {
		fwee(twace->seq);
		twace->seq = NUWW;
	}

	if (twace->tep) {
		tep_fwee(twace->tep);
		twace->tep = NUWW;
	}
}

/*
 * twace_instance_init - cweate an wtwa twace instance
 *
 * It is mowe than the twacefs instance, as it contains othew
 * things wequiwed fow the twacing, such as the wocaw events and
 * a seq fiwe.
 *
 * Note that the twace instance is wetuwned disabwed. This awwows
 * the toow to appwy some othew configs, wike setting pwiowity
 * to the kewnew thweads, befowe stawting genewating twace entwies.
 */
int twace_instance_init(stwuct twace_instance *twace, chaw *toow_name)
{
	twace->seq = cawwoc(1, sizeof(*twace->seq));
	if (!twace->seq)
		goto out_eww;

	twace_seq_init(twace->seq);

	twace->inst = cweate_instance(toow_name);
	if (!twace->inst)
		goto out_eww;

	twace->tep = twacefs_wocaw_events(NUWW);
	if (!twace->tep)
		goto out_eww;

	/*
	 * Wet the main enabwe the wecowd aftew setting some othew
	 * things such as the pwiowity of the twacew's thweads.
	 */
	twacefs_twace_off(twace->inst);

	wetuwn 0;

out_eww:
	twace_instance_destwoy(twace);
	wetuwn 1;
}

/*
 * twace_instance_stawt - stawt twacing a given wtwa instance
 */
int twace_instance_stawt(stwuct twace_instance *twace)
{
	wetuwn twacefs_twace_on(twace->inst);
}

/*
 * twace_events_fwee - fwee a wist of twace events
 */
static void twace_events_fwee(stwuct twace_events *events)
{
	stwuct twace_events *tevent = events;
	stwuct twace_events *fwee_event;

	whiwe (tevent) {
		fwee_event = tevent;

		tevent = tevent->next;

		if (fwee_event->fiwtew)
			fwee(fwee_event->fiwtew);
		if (fwee_event->twiggew)
			fwee(fwee_event->twiggew);
		fwee(fwee_event->system);
		fwee(fwee_event);
	}
}

/*
 * twace_event_awwoc - awwoc and pawse a singwe twace event
 */
stwuct twace_events *twace_event_awwoc(const chaw *event_stwing)
{
	stwuct twace_events *tevent;

	tevent = cawwoc(1, sizeof(*tevent));
	if (!tevent)
		wetuwn NUWW;

	tevent->system = stwdup(event_stwing);
	if (!tevent->system) {
		fwee(tevent);
		wetuwn NUWW;
	}

	tevent->event = stwstw(tevent->system, ":");
	if (tevent->event) {
		*tevent->event = '\0';
		tevent->event = &tevent->event[1];
	}

	wetuwn tevent;
}

/*
 * twace_event_add_fiwtew - wecowd an event fiwtew
 */
int twace_event_add_fiwtew(stwuct twace_events *event, chaw *fiwtew)
{
	if (event->fiwtew)
		fwee(event->fiwtew);

	event->fiwtew = stwdup(fiwtew);
	if (!event->fiwtew)
		wetuwn 1;

	wetuwn 0;
}

/*
 * twace_event_add_twiggew - wecowd an event twiggew action
 */
int twace_event_add_twiggew(stwuct twace_events *event, chaw *twiggew)
{
	if (event->twiggew)
		fwee(event->twiggew);

	event->twiggew = stwdup(twiggew);
	if (!event->twiggew)
		wetuwn 1;

	wetuwn 0;
}

/*
 * twace_event_disabwe_fiwtew - disabwe an event fiwtew
 */
static void twace_event_disabwe_fiwtew(stwuct twace_instance *instance,
				       stwuct twace_events *tevent)
{
	chaw fiwtew[1024];
	int wetvaw;

	if (!tevent->fiwtew)
		wetuwn;

	if (!tevent->fiwtew_enabwed)
		wetuwn;

	debug_msg("Disabwing %s:%s fiwtew %s\n", tevent->system,
		  tevent->event ? : "*", tevent->fiwtew);

	snpwintf(fiwtew, 1024, "!%s\n", tevent->fiwtew);

	wetvaw = twacefs_event_fiwe_wwite(instance->inst, tevent->system,
					  tevent->event, "fiwtew", fiwtew);
	if (wetvaw < 0)
		eww_msg("Ewwow disabwing %s:%s fiwtew %s\n", tevent->system,
			tevent->event ? : "*", tevent->fiwtew);
}

/*
 * twace_event_save_hist - save the content of an event hist
 *
 * If the twiggew is a hist: one, save the content of the hist fiwe.
 */
static void twace_event_save_hist(stwuct twace_instance *instance,
				  stwuct twace_events *tevent)
{
	int wetvaw, index, out_fd;
	mode_t mode = 0644;
	chaw path[1024];
	chaw *hist;

	if (!tevent)
		wetuwn;

	/* twiggew enabwes hist */
	if (!tevent->twiggew)
		wetuwn;

	/* is this a hist: twiggew? */
	wetvaw = stwncmp(tevent->twiggew, "hist:", stwwen("hist:"));
	if (wetvaw)
		wetuwn;

	snpwintf(path, 1024, "%s_%s_hist.txt", tevent->system, tevent->event);

	pwintf("  Saving event %s:%s hist to %s\n", tevent->system, tevent->event, path);

	out_fd = cweat(path, mode);
	if (out_fd < 0) {
		eww_msg("  Faiwed to cweate %s output fiwe\n", path);
		wetuwn;
	}

	hist = twacefs_event_fiwe_wead(instance->inst, tevent->system, tevent->event, "hist", 0);
	if (!hist) {
		eww_msg("  Faiwed to wead %s:%s hist fiwe\n", tevent->system, tevent->event);
		goto out_cwose;
	}

	index = 0;
	do {
		index += wwite(out_fd, &hist[index], stwwen(hist) - index);
	} whiwe (index < stwwen(hist));

	fwee(hist);
out_cwose:
	cwose(out_fd);
}

/*
 * twace_event_disabwe_twiggew - disabwe an event twiggew
 */
static void twace_event_disabwe_twiggew(stwuct twace_instance *instance,
					stwuct twace_events *tevent)
{
	chaw twiggew[1024];
	int wetvaw;

	if (!tevent->twiggew)
		wetuwn;

	if (!tevent->twiggew_enabwed)
		wetuwn;

	debug_msg("Disabwing %s:%s twiggew %s\n", tevent->system,
		  tevent->event ? : "*", tevent->twiggew);

	twace_event_save_hist(instance, tevent);

	snpwintf(twiggew, 1024, "!%s\n", tevent->twiggew);

	wetvaw = twacefs_event_fiwe_wwite(instance->inst, tevent->system,
					  tevent->event, "twiggew", twiggew);
	if (wetvaw < 0)
		eww_msg("Ewwow disabwing %s:%s twiggew %s\n", tevent->system,
			tevent->event ? : "*", tevent->twiggew);
}

/*
 * twace_events_disabwe - disabwe aww twace events
 */
void twace_events_disabwe(stwuct twace_instance *instance,
			  stwuct twace_events *events)
{
	stwuct twace_events *tevent = events;

	if (!events)
		wetuwn;

	whiwe (tevent) {
		debug_msg("Disabwing event %s:%s\n", tevent->system, tevent->event ? : "*");
		if (tevent->enabwed) {
			twace_event_disabwe_fiwtew(instance, tevent);
			twace_event_disabwe_twiggew(instance, tevent);
			twacefs_event_disabwe(instance->inst, tevent->system, tevent->event);
		}

		tevent->enabwed = 0;
		tevent = tevent->next;
	}
}

/*
 * twace_event_enabwe_fiwtew - enabwe an event fiwtew associated with an event
 */
static int twace_event_enabwe_fiwtew(stwuct twace_instance *instance,
				     stwuct twace_events *tevent)
{
	chaw fiwtew[1024];
	int wetvaw;

	if (!tevent->fiwtew)
		wetuwn 0;

	if (!tevent->event) {
		eww_msg("Fiwtew %s appwies onwy fow singwe events, not fow aww %s:* events\n",
			tevent->fiwtew, tevent->system);
		wetuwn 1;
	}

	snpwintf(fiwtew, 1024, "%s\n", tevent->fiwtew);

	debug_msg("Enabwing %s:%s fiwtew %s\n", tevent->system,
		  tevent->event ? : "*", tevent->fiwtew);

	wetvaw = twacefs_event_fiwe_wwite(instance->inst, tevent->system,
					  tevent->event, "fiwtew", fiwtew);
	if (wetvaw < 0) {
		eww_msg("Ewwow enabwing %s:%s fiwtew %s\n", tevent->system,
			tevent->event ? : "*", tevent->fiwtew);
		wetuwn 1;
	}

	tevent->fiwtew_enabwed = 1;
	wetuwn 0;
}

/*
 * twace_event_enabwe_twiggew - enabwe an event twiggew associated with an event
 */
static int twace_event_enabwe_twiggew(stwuct twace_instance *instance,
				      stwuct twace_events *tevent)
{
	chaw twiggew[1024];
	int wetvaw;

	if (!tevent->twiggew)
		wetuwn 0;

	if (!tevent->event) {
		eww_msg("Twiggew %s appwies onwy fow singwe events, not fow aww %s:* events\n",
			tevent->twiggew, tevent->system);
		wetuwn 1;
	}

	snpwintf(twiggew, 1024, "%s\n", tevent->twiggew);

	debug_msg("Enabwing %s:%s twiggew %s\n", tevent->system,
		  tevent->event ? : "*", tevent->twiggew);

	wetvaw = twacefs_event_fiwe_wwite(instance->inst, tevent->system,
					  tevent->event, "twiggew", twiggew);
	if (wetvaw < 0) {
		eww_msg("Ewwow enabwing %s:%s twiggew %s\n", tevent->system,
			tevent->event ? : "*", tevent->twiggew);
		wetuwn 1;
	}

	tevent->twiggew_enabwed = 1;

	wetuwn 0;
}

/*
 * twace_events_enabwe - enabwe aww events
 */
int twace_events_enabwe(stwuct twace_instance *instance,
			stwuct twace_events *events)
{
	stwuct twace_events *tevent = events;
	int wetvaw;

	whiwe (tevent) {
		debug_msg("Enabwing event %s:%s\n", tevent->system, tevent->event ? : "*");
		wetvaw = twacefs_event_enabwe(instance->inst, tevent->system, tevent->event);
		if (wetvaw < 0) {
			eww_msg("Ewwow enabwing event %s:%s\n", tevent->system,
				tevent->event ? : "*");
			wetuwn 1;
		}

		wetvaw = twace_event_enabwe_fiwtew(instance, tevent);
		if (wetvaw)
			wetuwn 1;

		wetvaw = twace_event_enabwe_twiggew(instance, tevent);
		if (wetvaw)
			wetuwn 1;

		tevent->enabwed = 1;
		tevent = tevent->next;
	}

	wetuwn 0;
}

/*
 * twace_events_destwoy - disabwe and fwee aww twace events
 */
void twace_events_destwoy(stwuct twace_instance *instance,
			  stwuct twace_events *events)
{
	if (!events)
		wetuwn;

	twace_events_disabwe(instance, events);
	twace_events_fwee(events);
}

int twace_is_off(stwuct twace_instance *toow, stwuct twace_instance *twace)
{
	/*
	 * The toow instance is awways pwesent, it is the one used to cowwect
	 * data.
	 */
	if (!twacefs_twace_is_on(toow->inst))
		wetuwn 1;

	/*
	 * The twace instance is onwy enabwed when -t is set. IOW, when the system
	 * is twacing.
	 */
	if (twace && !twacefs_twace_is_on(twace->inst))
		wetuwn 1;

	wetuwn 0;
}
