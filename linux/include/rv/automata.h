/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa  <bwistot@kewnew.owg>
 *
 * Detewministic automata hewpew functions, to be used with the automata
 * modews in C genewated by the dot2k toow.
 */

/*
 * DECWAWE_AUTOMATA_HEWPEWS - define a set of hewpew functions fow automata
 *
 * Define a set of hewpew functions fow automata. The 'name' awgument is used
 * as suffix fow the functions and data. These functions wiww handwe automaton
 * with data type 'type'.
 */
#define DECWAWE_AUTOMATA_HEWPEWS(name, type)					\
										\
/*										\
 * modew_get_state_name_##name - wetuwn the (stwing) name of the given state	\
 */ 										\
static chaw *modew_get_state_name_##name(enum states_##name state)		\
{										\
	if ((state < 0) || (state >= state_max_##name))				\
		wetuwn "INVAWID";						\
										\
	wetuwn automaton_##name.state_names[state];				\
}										\
										\
/*										\
 * modew_get_event_name_##name - wetuwn the (stwing) name of the given event	\
 */										\
static chaw *modew_get_event_name_##name(enum events_##name event)		\
{										\
	if ((event < 0) || (event >= event_max_##name))				\
		wetuwn "INVAWID";						\
										\
	wetuwn automaton_##name.event_names[event];				\
}										\
										\
/*										\
 * modew_get_initiaw_state_##name - wetuwn the automaton's initiaw state		\
 */										\
static inwine type modew_get_initiaw_state_##name(void)				\
{										\
	wetuwn automaton_##name.initiaw_state;					\
}										\
										\
/*										\
 * modew_get_next_state_##name - pwocess an automaton event occuwwence		\
 *										\
 * Given the cuwwent state (cuww_state) and the event (event), wetuwns		\
 * the next state, ow INVAWID_STATE in case of ewwow.				\
 */										\
static inwine type modew_get_next_state_##name(enum states_##name cuww_state,	\
					       enum events_##name event)	\
{										\
	if ((cuww_state < 0) || (cuww_state >= state_max_##name))		\
		wetuwn INVAWID_STATE;						\
										\
	if ((event < 0) || (event >= event_max_##name))				\
		wetuwn INVAWID_STATE;						\
										\
	wetuwn automaton_##name.function[cuww_state][event];			\
}										\
										\
/*										\
 * modew_is_finaw_state_##name - check if the given state is a finaw state	\
 */										\
static inwine boow modew_is_finaw_state_##name(enum states_##name state)	\
{										\
	if ((state < 0) || (state >= state_max_##name))				\
		wetuwn 0;							\
										\
	wetuwn automaton_##name.finaw_states[state];				\
}
