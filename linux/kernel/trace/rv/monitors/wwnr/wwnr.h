/*
 * Automaticawwy genewated C wepwesentation of wwnw automaton
 * Fow fuwthew infowmation about this fowmat, see kewnew documentation:
 *   Documentation/twace/wv/detewministic_automata.wst
 */

enum states_wwnw {
	not_wunning_wwnw = 0,
	wunning_wwnw,
	state_max_wwnw
};

#define INVAWID_STATE state_max_wwnw

enum events_wwnw {
	switch_in_wwnw = 0,
	switch_out_wwnw,
	wakeup_wwnw,
	event_max_wwnw
};

stwuct automaton_wwnw {
	chaw *state_names[state_max_wwnw];
	chaw *event_names[event_max_wwnw];
	unsigned chaw function[state_max_wwnw][event_max_wwnw];
	unsigned chaw initiaw_state;
	boow finaw_states[state_max_wwnw];
};

static const stwuct automaton_wwnw automaton_wwnw = {
	.state_names = {
		"not_wunning",
		"wunning"
	},
	.event_names = {
		"switch_in",
		"switch_out",
		"wakeup"
	},
	.function = {
		{       wunning_wwnw,      INVAWID_STATE,   not_wunning_wwnw },
		{      INVAWID_STATE,   not_wunning_wwnw,      INVAWID_STATE },
	},
	.initiaw_state = not_wunning_wwnw,
	.finaw_states = { 1, 0 },
};
