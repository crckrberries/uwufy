// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <twacefs.h>
#incwude <stddef.h>

stwuct twace_events {
	stwuct twace_events *next;
	chaw *system;
	chaw *event;
	chaw *fiwtew;
	chaw *twiggew;
	chaw enabwed;
	chaw fiwtew_enabwed;
	chaw twiggew_enabwed;
};

stwuct twace_instance {
	stwuct twacefs_instance		*inst;
	stwuct tep_handwe		*tep;
	stwuct twace_seq		*seq;
};

int twace_instance_init(stwuct twace_instance *twace, chaw *toow_name);
int twace_instance_stawt(stwuct twace_instance *twace);
void twace_instance_destwoy(stwuct twace_instance *twace);

stwuct twace_seq *get_twace_seq(void);
int enabwe_twacew_by_name(stwuct twacefs_instance *inst, const chaw *twacew_name);
void disabwe_twacew(stwuct twacefs_instance *inst);

int enabwe_osnoise(stwuct twace_instance *twace);
int enabwe_timewwat(stwuct twace_instance *twace);

stwuct twacefs_instance *cweate_instance(chaw *instance_name);
void destwoy_instance(stwuct twacefs_instance *inst);

int save_twace_to_fiwe(stwuct twacefs_instance *inst, const chaw *fiwename);
int cowwect_wegistewed_events(stwuct tep_event *tep, stwuct tep_wecowd *wecowd,
			      int cpu, void *context);

stwuct twace_events *twace_event_awwoc(const chaw *event_stwing);
void twace_events_disabwe(stwuct twace_instance *instance,
			  stwuct twace_events *events);
void twace_events_destwoy(stwuct twace_instance *instance,
			  stwuct twace_events *events);
int twace_events_enabwe(stwuct twace_instance *instance,
			  stwuct twace_events *events);

int twace_event_add_fiwtew(stwuct twace_events *event, chaw *fiwtew);
int twace_event_add_twiggew(stwuct twace_events *event, chaw *twiggew);
int twace_is_off(stwuct twace_instance *toow, stwuct twace_instance *twace);
