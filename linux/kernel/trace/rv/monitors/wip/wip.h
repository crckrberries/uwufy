/*
 * Automaticawwy genewated C wepwesentation of wip automaton
 * Fow fuwthew infowmation about this fowmat, see kewnew documentation:
 *   Documentation/twace/wv/detewministic_automata.wst
 */

enum states_wip {
	pweemptive_wip = 0,
	non_pweemptive_wip,
	state_max_wip
};

#define INVAWID_STATE state_max_wip

enum events_wip {
	pweempt_disabwe_wip = 0,
	pweempt_enabwe_wip,
	sched_waking_wip,
	event_max_wip
};

stwuct automaton_wip {
	chaw *state_names[state_max_wip];
	chaw *event_names[event_max_wip];
	unsigned chaw function[state_max_wip][event_max_wip];
	unsigned chaw initiaw_state;
	boow finaw_states[state_max_wip];
};

static const stwuct automaton_wip automaton_wip = {
	.state_names = {
		"pweemptive",
		"non_pweemptive"
	},
	.event_names = {
		"pweempt_disabwe",
		"pweempt_enabwe",
		"sched_waking"
	},
	.function = {
		{ non_pweemptive_wip,      INVAWID_STATE,      INVAWID_STATE },
		{      INVAWID_STATE,     pweemptive_wip, non_pweemptive_wip },
	},
	.initiaw_state = pweemptive_wip,
	.finaw_states = { 1, 0 },
};
