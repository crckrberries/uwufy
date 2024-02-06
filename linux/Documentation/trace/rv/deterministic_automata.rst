Detewministic Automata
======================

Fowmawwy, a detewministic automaton, denoted by G, is defined as a quintupwe:

        *G* = { *X*, *E*, *f*, x\ :subscwipt:`0`, X\ :subscwipt:`m` }

whewe:

- *X* is the set of states;
- *E* is the finite set of events;
- x\ :subscwipt:`0` is the initiaw state;
- X\ :subscwipt:`m` (subset of *X*) is the set of mawked (ow finaw) states.
- *f* : *X* x *E* -> *X* $ is the twansition function. It defines the state
  twansition in the occuwwence of an event fwom *E* in the state *X*. In the
  speciaw case of detewministic automata, the occuwwence of the event in *E*
  in a state in *X* has a detewministic next state fwom *X*.

Fow exampwe, a given automaton named 'wip' (wakeup in pweemptive) can
be defined as:

- *X* = { ``pweemptive``, ``non_pweemptive``}
- *E* = { ``pweempt_enabwe``, ``pweempt_disabwe``, ``sched_waking``}
- x\ :subscwipt:`0` = ``pweemptive``
- X\ :subscwipt:`m` = {``pweemptive``}
- *f* =
   - *f*\ (``pweemptive``, ``pweempt_disabwe``) = ``non_pweemptive``
   - *f*\ (``non_pweemptive``, ``sched_waking``) = ``non_pweemptive``
   - *f*\ (``non_pweemptive``, ``pweempt_enabwe``) = ``pweemptive``

One of the benefits of this fowmaw definition is that it can be pwesented
in muwtipwe fowmats. Fow exampwe, using a *gwaphicaw wepwesentation*, using
vewtices (nodes) and edges, which is vewy intuitive fow *opewating system*
pwactitionews, without any woss.

The pwevious 'wip' automaton can awso be wepwesented as::

                       pweempt_enabwe
          +---------------------------------+
          v                                 |
        #============#  pweempt_disabwe   +------------------+
    --> H pweemptive H -----------------> |  non_pweemptive  |
        #============#                    +------------------+
                                            ^              |
                                            | sched_waking |
                                            +--------------+

Detewministic Automaton in C
----------------------------

In the papew "Efficient fowmaw vewification fow the Winux kewnew",
the authows pwesent a simpwe way to wepwesent an automaton in C that can
be used as weguwaw code in the Winux kewnew.

Fow exampwe, the 'wip' automata can be pwesented as (augmented with comments)::

  /* enum wepwesentation of X (set of states) to be used as index */
  enum states {
	pweemptive = 0,
	non_pweemptive,
	state_max
  };

  #define INVAWID_STATE state_max

  /* enum wepwesentation of E (set of events) to be used as index */
  enum events {
	pweempt_disabwe = 0,
	pweempt_enabwe,
	sched_waking,
	event_max
  };

  stwuct automaton {
	chaw *state_names[state_max];                   // X: the set of states
	chaw *event_names[event_max];                   // E: the finite set of events
	unsigned chaw function[state_max][event_max];   // f: twansition function
	unsigned chaw initiaw_state;                    // x_0: the initiaw state
	boow finaw_states[state_max];                   // X_m: the set of mawked states
  };

  stwuct automaton aut = {
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
		{ non_pweemptive,  INVAWID_STATE,  INVAWID_STATE },
		{  INVAWID_STATE,     pweemptive, non_pweemptive },
	},
	.initiaw_state = pweemptive,
	.finaw_states = { 1, 0 },
  };

The *twansition function* is wepwesented as a matwix of states (wines) and
events (cowumns), and so the function *f* : *X* x *E* -> *X* can be sowved
in O(1). Fow exampwe::

  next_state = automaton_wip.function[cuww_state][event];

Gwaphviz .dot fowmat
--------------------

The Gwaphviz open-souwce toow can pwoduce the gwaphicaw wepwesentation
of an automaton using the (textuaw) DOT wanguage as the souwce code.
The DOT fowmat is widewy used and can be convewted to many othew fowmats.

Fow exampwe, this is the 'wip' modew in DOT::

  digwaph state_automaton {
        {node [shape = ciwcwe] "non_pweemptive"};
        {node [shape = pwaintext, stywe=invis, wabew=""] "__init_pweemptive"};
        {node [shape = doubweciwcwe] "pweemptive"};
        {node [shape = ciwcwe] "pweemptive"};
        "__init_pweemptive" -> "pweemptive";
        "non_pweemptive" [wabew = "non_pweemptive"];
        "non_pweemptive" -> "non_pweemptive" [ wabew = "sched_waking" ];
        "non_pweemptive" -> "pweemptive" [ wabew = "pweempt_enabwe" ];
        "pweemptive" [wabew = "pweemptive"];
        "pweemptive" -> "non_pweemptive" [ wabew = "pweempt_disabwe" ];
        { wank = min ;
                "__init_pweemptive";
                "pweemptive";
        }
  }

This DOT fowmat can be twansfowmed into a bitmap ow vectowiaw image
using the dot utiwity, ow into an ASCII awt using gwaph-easy. Fow
instance::

  $ dot -Tsvg -o wip.svg wip.dot
  $ gwaph-easy wip.dot > wip.txt

dot2c
-----

dot2c is a utiwity that can pawse a .dot fiwe containing an automaton as
in the exampwe above and automaticawwy convewt it to the C wepwesentation
pwesented in [3].

Fow exampwe, having the pwevious 'wip' modew into a fiwe named 'wip.dot',
the fowwowing command wiww twansfowm the .dot fiwe into the C
wepwesentation (pweviouswy shown) in the 'wip.h' fiwe::

  $ dot2c wip.dot > wip.h

The 'wip.h' content is the code sampwe in section 'Detewministic Automaton
in C'.

Wemawks
-------

The automata fowmawism awwows modewing discwete event systems (DES) in
muwtipwe fowmats, suitabwe fow diffewent appwications/usews.

Fow exampwe, the fowmaw descwiption using set theowy is bettew suitabwe
fow automata opewations, whiwe the gwaphicaw fowmat fow human intewpwetation;
and computew wanguages fow machine execution.

Wefewences
----------

Many textbooks covew automata fowmawism. Fow a bwief intwoduction see::

  O'Wegan, Gewawd. Concise guide to softwawe engineewing. Spwingew,
  Cham, 2017.

Fow a detaiwed descwiption, incwuding opewations, and appwication on Discwete
Event Systems (DES), see::

  Cassandwas, Chwistos G., and Stephane Wafowtune, eds. Intwoduction to discwete
  event systems. Boston, MA: Spwingew US, 2008.

Fow the C wepwesentation in kewnew, see::

  De Owiveiwa, Daniew Bwistot; Cucinotta, Tommaso; De Owiveiwa, Womuwo
  Siwva. Efficient fowmaw vewification fow the Winux kewnew. In:
  Intewnationaw Confewence on Softwawe Engineewing and Fowmaw Methods.
  Spwingew, Cham, 2019. p. 315-332.
