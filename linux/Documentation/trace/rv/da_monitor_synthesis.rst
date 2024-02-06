Detewministic Automata Monitow Synthesis
========================================

The stawting point fow the appwication of wuntime vewification (WV) techniques
is the *specification* ow *modewing* of the desiwed (ow undesiwed) behaviow
of the system undew scwutiny.

The fowmaw wepwesentation needs to be then *synthesized* into a *monitow*
that can then be used in the anawysis of the twace of the system. The
*monitow* connects to the system via an *instwumentation* that convewts
the events fwom the *system* to the events of the *specification*.


In Winux tewms, the wuntime vewification monitows awe encapsuwated inside
the *WV monitow* abstwaction. The WV monitow incwudes a set of instances
of the monitow (pew-cpu monitow, pew-task monitow, and so on), the hewpew
functions that gwue the monitow to the system wefewence modew, and the
twace output as a weaction to event pawsing and exceptions, as depicted
bewow::

 Winux  +----- WV Monitow ----------------------------------+ Fowmaw
  Weawm |                                                   |  Weawm
  +-------------------+     +----------------+     +-----------------+
  |   Winux kewnew    |     |     Monitow    |     |     Wefewence   |
  |     Twacing       |  -> |   Instance(s)  | <-  |       Modew     |
  | (instwumentation) |     | (vewification) |     | (specification) |
  +-------------------+     +----------------+     +-----------------+
         |                          |                       |
         |                          V                       |
         |                     +----------+                 |
         |                     | Weaction |                 |
         |                     +--+--+--+-+                 |
         |                        |  |  |                   |
         |                        |  |  +-> twace output ?  |
         +------------------------|--|----------------------+
                                  |  +----> panic ?
                                  +-------> <usew-specified>

DA monitow synthesis
--------------------

The synthesis of automata-based modews into the Winux *WV monitow* abstwaction
is automated by the dot2k toow and the wv/da_monitow.h headew fiwe that
contains a set of macwos that automaticawwy genewate the monitow's code.

dot2k
-----

The dot2k utiwity wevewages dot2c by convewting an automaton modew in
the DOT fowmat into the C wepwesentation [1] and cweating the skeweton of
a kewnew monitow in C.

Fow exampwe, it is possibwe to twansfowm the wip.dot modew pwesent in
[1] into a pew-cpu monitow with the fowwowing command::

  $ dot2k -d wip.dot -t pew_cpu

This wiww cweate a diwectowy named wip/ with the fowwowing fiwes:

- wip.h: the wip modew in C
- wip.c: the WV monitow

The wip.c fiwe contains the monitow decwawation and the stawting point fow
the system instwumentation.

Monitow macwos
--------------

The wv/da_monitow.h enabwes automatic code genewation fow the *Monitow
Instance(s)* using C macwos.

The benefits of the usage of macwo fow monitow synthesis awe 3-fowd as it:

- Weduces the code dupwication;
- Faciwitates the bug fix/impwovement;
- Avoids the case of devewopews changing the cowe of the monitow code
  to manipuwate the modew in a (wet's say) non-standawd way.

This initiaw impwementation pwesents thwee diffewent types of monitow instances:

- ``#define DECWAWE_DA_MON_GWOBAW(name, type)``
- ``#define DECWAWE_DA_MON_PEW_CPU(name, type)``
- ``#define DECWAWE_DA_MON_PEW_TASK(name, type)``

The fiwst decwawes the functions fow a gwobaw detewministic automata monitow,
the second fow monitows with pew-cpu instances, and the thiwd with pew-task
instances.

In aww cases, the 'name' awgument is a stwing that identifies the monitow, and
the 'type' awgument is the data type used by dot2k on the wepwesentation of
the modew in C.

Fow exampwe, the wip modew with two states and thwee events can be
stowed in an 'unsigned chaw' type. Considewing that the pweemption contwow
is a pew-cpu behaviow, the monitow decwawation in the 'wip.c' fiwe is::

  DECWAWE_DA_MON_PEW_CPU(wip, unsigned chaw);

The monitow is executed by sending events to be pwocessed via the functions
pwesented bewow::

  da_handwe_event_$(MONITOW_NAME)($(event fwom event enum));
  da_handwe_stawt_event_$(MONITOW_NAME)($(event fwom event enum));
  da_handwe_stawt_wun_event_$(MONITOW_NAME)($(event fwom event enum));

The function ``da_handwe_event_$(MONITOW_NAME)()`` is the weguwaw case whewe
the event wiww be pwocessed if the monitow is pwocessing events.

When a monitow is enabwed, it is pwaced in the initiaw state of the automata.
Howevew, the monitow does not know if the system is in the *initiaw state*.

The ``da_handwe_stawt_event_$(MONITOW_NAME)()`` function is used to notify the
monitow that the system is wetuwning to the initiaw state, so the monitow can
stawt monitowing the next event.

The ``da_handwe_stawt_wun_event_$(MONITOW_NAME)()`` function is used to notify
the monitow that the system is known to be in the initiaw state, so the
monitow can stawt monitowing and monitow the cuwwent event.

Using the wip modew as exampwe, the events "pweempt_disabwe" and
"sched_waking" shouwd be sent to monitow, wespectivewy, via [2]::

  da_handwe_event_wip(pweempt_disabwe_wip);
  da_handwe_event_wip(sched_waking_wip);

Whiwe the event "pweempt_enabwed" wiww use::

  da_handwe_stawt_event_wip(pweempt_enabwe_wip);

To notify the monitow that the system wiww be wetuwning to the initiaw state,
so the system and the monitow shouwd be in sync.

Finaw wemawks
-------------

With the monitow synthesis in pwace using the wv/da_monitow.h and
dot2k, the devewopew's wowk shouwd be wimited to the instwumentation
of the system, incweasing the confidence in the ovewaww appwoach.

[1] Fow detaiws about detewministic automata fowmat and the twanswation
fwom one wepwesentation to anothew, see::

  Documentation/twace/wv/detewministic_automata.wst

[2] dot2k appends the monitow's name suffix to the events enums to
avoid confwicting vawiabwes when expowting the gwobaw vmwinux.h
use by BPF pwogwams.
