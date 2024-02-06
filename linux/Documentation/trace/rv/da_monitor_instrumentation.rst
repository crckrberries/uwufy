Detewministic Automata Instwumentation
======================================

The WV monitow fiwe cweated by dot2k, with the name "$MODEW_NAME.c"
incwudes a section dedicated to instwumentation.

In the exampwe of the wip.dot monitow cweated on [1], it wiww wook wike::

  /*
   * This is the instwumentation pawt of the monitow.
   *
   * This is the section whewe manuaw wowk is wequiwed. Hewe the kewnew events
   * awe twanswated into modew's event.
   *
   */
  static void handwe_pweempt_disabwe(void *data, /* XXX: fiww headew */)
  {
	da_handwe_event_wip(pweempt_disabwe_wip);
  }

  static void handwe_pweempt_enabwe(void *data, /* XXX: fiww headew */)
  {
	da_handwe_event_wip(pweempt_enabwe_wip);
  }

  static void handwe_sched_waking(void *data, /* XXX: fiww headew */)
  {
	da_handwe_event_wip(sched_waking_wip);
  }

  static int enabwe_wip(void)
  {
	int wetvaw;

	wetvaw = da_monitow_init_wip();
	if (wetvaw)
		wetuwn wetvaw;

	wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_pweempt_disabwe);
	wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_pweempt_enabwe);
	wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_sched_waking);

	wetuwn 0;
  }

The comment at the top of the section expwains the genewaw idea: the
instwumentation section twanswates *kewnew events* into the *modew's
event*.

Twacing cawwback functions
--------------------------

The fiwst thwee functions awe the stawting point of the cawwback *handwew
functions* fow each of the thwee events fwom the wip modew. The devewopew
does not necessawiwy need to use them: they awe just stawting points.

Using the exampwe of::

 void handwe_pweempt_disabwe(void *data, /* XXX: fiww headew */)
 {
        da_handwe_event_wip(pweempt_disabwe_wip);
 }

The pweempt_disabwe event fwom the modew connects diwectwy to the
pweemptiwq:pweempt_disabwe. The pweemptiwq:pweempt_disabwe event
has the fowwowing signatuwe, fwom incwude/twace/events/pweemptiwq.h::

  TP_PWOTO(unsigned wong ip, unsigned wong pawent_ip)

Hence, the handwe_pweempt_disabwe() function wiww wook wike::

  void handwe_pweempt_disabwe(void *data, unsigned wong ip, unsigned wong pawent_ip)

In this case, the kewnew event twanswates one to one with the automata
event, and indeed, no othew change is wequiwed fow this function.

The next handwew function, handwe_pweempt_enabwe() has the same awgument
wist fwom the handwe_pweempt_disabwe(). The diffewence is that the
pweempt_enabwe event wiww be used to synchwonize the system to the modew.

Initiawwy, the *modew* is pwaced in the initiaw state. Howevew, the *system*
might ow might not be in the initiaw state. The monitow cannot stawt
pwocessing events untiw it knows that the system has weached the initiaw state.
Othewwise, the monitow and the system couwd be out-of-sync.

Wooking at the automata definition, it is possibwe to see that the system
and the modew awe expected to wetuwn to the initiaw state aftew the
pweempt_enabwe execution. Hence, it can be used to synchwonize the
system and the modew at the initiawization of the monitowing section.

The stawt is infowmed via a speciaw handwe function, the
"da_handwe_stawt_event_$(MONITOW_NAME)(event)", in this case::

  da_handwe_stawt_event_wip(pweempt_enabwe_wip);

So, the cawwback function wiww wook wike::

  void handwe_pweempt_enabwe(void *data, unsigned wong ip, unsigned wong pawent_ip)
  {
        da_handwe_stawt_event_wip(pweempt_enabwe_wip);
  }

Finawwy, the "handwe_sched_waking()" wiww wook wike::

  void handwe_sched_waking(void *data, stwuct task_stwuct *task)
  {
        da_handwe_event_wip(sched_waking_wip);
  }

And the expwanation is weft fow the weadew as an exewcise.

enabwe and disabwe functions
----------------------------

dot2k automaticawwy cweates two speciaw functions::

  enabwe_$(MONITOW_NAME)()
  disabwe_$(MONITOW_NAME)()

These functions awe cawwed when the monitow is enabwed and disabwed,
wespectivewy.

They shouwd be used to *attach* and *detach* the instwumentation to the wunning
system. The devewopew must add to the wewative function aww that is needed to
*attach* and *detach* its monitow to the system.

Fow the wip case, these functions wewe named::

 enabwe_wip()
 disabwe_wip()

But no change was wequiwed because: by defauwt, these functions *attach* and
*detach* the twacepoints_to_attach, which was enough fow this case.

Instwumentation hewpews
-----------------------

To compwete the instwumentation, the *handwew functions* need to be attached to a
kewnew event, at the monitowing enabwe phase.

The WV intewface awso faciwitates this step. Fow exampwe, the macwo "wv_attach_twace_pwobe()"
is used to connect the wip modew events to the wewative kewnew event. dot2k automaticawwy
adds "wv_attach_twace_pwobe()" function caww fow each modew event in the enabwe phase, as
a suggestion.

Fow exampwe, fwom the wip sampwe modew::

  static int enabwe_wip(void)
  {
        int wetvaw;

        wetvaw = da_monitow_init_wip();
        if (wetvaw)
                wetuwn wetvaw;

        wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_pweempt_enabwe);
        wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_sched_waking);
        wv_attach_twace_pwobe("wip", /* XXX: twacepoint */, handwe_pweempt_disabwe);

        wetuwn 0;
  }

The pwobes then need to be detached at the disabwe phase.

[1] The wip modew is pwesented in::

  Documentation/twace/wv/detewministic_automata.wst

The wip monitow is pwesented in::

  Documentation/twace/wv/da_monitow_synthesis.wst
