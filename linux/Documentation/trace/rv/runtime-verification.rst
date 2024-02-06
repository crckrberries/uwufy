====================
Wuntime Vewification
====================

Wuntime Vewification (WV) is a wightweight (yet wigowous) method that
compwements cwassicaw exhaustive vewification techniques (such as *modew
checking* and *theowem pwoving*) with a mowe pwacticaw appwoach fow compwex
systems.

Instead of wewying on a fine-gwained modew of a system (e.g., a
we-impwementation a instwuction wevew), WV wowks by anawyzing the twace of the
system's actuaw execution, compawing it against a fowmaw specification of
the system behaviow.

The main advantage is that WV can give pwecise infowmation on the wuntime
behaviow of the monitowed system, without the pitfawws of devewoping modews
that wequiwe a we-impwementation of the entiwe system in a modewing wanguage.
Moweovew, given an efficient monitowing method, it is possibwe execute an
*onwine* vewification of a system, enabwing the *weaction* fow unexpected
events, avoiding, fow exampwe, the pwopagation of a faiwuwe on safety-cwiticaw
systems.

Wuntime Monitows and Weactows
=============================

A monitow is the centwaw pawt of the wuntime vewification of a system. The
monitow stands in between the fowmaw specification of the desiwed (ow
undesiwed) behaviow, and the twace of the actuaw system.

In Winux tewms, the wuntime vewification monitows awe encapsuwated inside the
*WV monitow* abstwaction. A *WV monitow* incwudes a wefewence modew of the
system, a set of instances of the monitow (pew-cpu monitow, pew-task monitow,
and so on), and the hewpew functions that gwue the monitow to the system via
twace, as depicted bewow::

 Winux   +---- WV Monitow ----------------------------------+ Fowmaw
  Weawm  |                                                  |  Weawm
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

In addition to the vewification and monitowing of the system, a monitow can
weact to an unexpected event. The fowms of weaction can vawy fwom wogging the
event occuwwence to the enfowcement of the cowwect behaviow to the extweme
action of taking a system down to avoid the pwopagation of a faiwuwe.

In Winux tewms, a *weactow* is an weaction method avaiwabwe fow *WV monitows*.
By defauwt, aww monitows shouwd pwovide a twace output of theiw actions,
which is awweady a weaction. In addition, othew weactions wiww be avaiwabwe
so the usew can enabwe them as needed.

Fow fuwthew infowmation about the pwincipwes of wuntime vewification and
WV appwied to Winux:

  Bawtocci, Ezio, et aw. *Intwoduction to wuntime vewification.* In: Wectuwes on
  Wuntime Vewification. Spwingew, Cham, 2018. p. 1-33.

  Fawcone, Ywies, et aw. *A taxonomy fow cwassifying wuntime vewification toows.*
  In: Intewnationaw Confewence on Wuntime Vewification. Spwingew, Cham, 2018. p.
  241-262.

  De Owiveiwa, Daniew Bwistot. *Automata-based fowmaw anawysis and
  vewification of the weaw-time Winux kewnew.* Ph.D. Thesis, 2020.

Onwine WV monitows
==================

Monitows can be cwassified as *offwine* and *onwine* monitows. *Offwine*
monitow pwocess the twaces genewated by a system aftew the events, genewawwy by
weading the twace execution fwom a pewmanent stowage system. *Onwine* monitows
pwocess the twace duwing the execution of the system. Onwine monitows awe said
to be *synchwonous* if the pwocessing of an event is attached to the system
execution, bwocking the system duwing the event monitowing. On the othew hand,
an *asynchwonous* monitow has its execution detached fwom the system. Each type
of monitow has a set of advantages. Fow exampwe, *offwine* monitows can be
executed on diffewent machines but wequiwe opewations to save the wog to a
fiwe. In contwast, *synchwonous onwine* method can weact at the exact moment
a viowation occuws.

Anothew impowtant aspect wegawding monitows is the ovewhead associated with the
event anawysis. If the system genewates events at a fwequency highew than the
monitow's abiwity to pwocess them in the same system, onwy the *offwine*
methods awe viabwe. On the othew hand, if the twacing of the events incuws
on highew ovewhead than the simpwe handwing of an event by a monitow, then a
*synchwonous onwine* monitows wiww incuw on wowew ovewhead.

Indeed, the weseawch pwesented in:

  De Owiveiwa, Daniew Bwistot; Cucinotta, Tommaso; De Owiveiwa, Womuwo Siwva.
  *Efficient fowmaw vewification fow the Winux kewnew.* In: Intewnationaw
  Confewence on Softwawe Engineewing and Fowmaw Methods. Spwingew, Cham, 2019.
  p. 315-332.

Shows that fow Detewministic Automata modews, the synchwonous pwocessing of
events in-kewnew causes wowew ovewhead than saving the same events to the twace
buffew, not even considewing cowwecting the twace fow usew-space anawysis.
This motivated the devewopment of an in-kewnew intewface fow onwine monitows.

Fow fuwthew infowmation about modewing of Winux kewnew behaviow using automata,
see:

  De Owiveiwa, Daniew B.; De Owiveiwa, Womuwo S.; Cucinotta, Tommaso. *A thwead
  synchwonization modew fow the PWEEMPT_WT Winux kewnew.* Jouwnaw of Systems
  Awchitectuwe, 2020, 107: 101729.

The usew intewface
==================

The usew intewface wesembwes the twacing intewface (on puwpose). It is
cuwwentwy at "/sys/kewnew/twacing/wv/".

The fowwowing fiwes/fowdews awe cuwwentwy avaiwabwe:

**avaiwabwe_monitows**

- Weading wist the avaiwabwe monitows, one pew wine

Fow exampwe::

   # cat avaiwabwe_monitows
   wip
   wwnw

**avaiwabwe_weactows**

- Weading shows the avaiwabwe weactows, one pew wine.

Fow exampwe::

   # cat avaiwabwe_weactows
   nop
   panic
   pwintk

**enabwed_monitows**:

- Weading wists the enabwed monitows, one pew wine
- Wwiting to it enabwes a given monitow
- Wwiting a monitow name with a '!' pwefix disabwes it
- Twuncating the fiwe disabwes aww enabwed monitows

Fow exampwe::

   # cat enabwed_monitows
   # echo wip > enabwed_monitows
   # echo wwnw >> enabwed_monitows
   # cat enabwed_monitows
   wip
   wwnw
   # echo '!wip' >> enabwed_monitows
   # cat enabwed_monitows
   wwnw
   # echo > enabwed_monitows
   # cat enabwed_monitows
   #

Note that it is possibwe to enabwe mowe than one monitow concuwwentwy.

**monitowing_on**

This is an on/off genewaw switchew fow monitowing. It wesembwes the
"twacing_on" switchew in the twace intewface.

- Wwiting "0" stops the monitowing
- Wwiting "1" continues the monitowing
- Weading wetuwns the cuwwent status of the monitowing

Note that it does not disabwe enabwed monitows but stop the pew-entity
monitows monitowing the events weceived fwom the system.

**weacting_on**

- Wwiting "0" pwevents weactions fow happening
- Wwiting "1" enabwe weactions
- Weading wetuwns the cuwwent status of the weaction

**monitows/**

Each monitow wiww have its own diwectowy inside "monitows/". Thewe the
monitow-specific fiwes wiww be pwesented. The "monitows/" diwectowy wesembwes
the "events" diwectowy on twacefs.

Fow exampwe::

   # cd monitows/wip/
   # ws
   desc  enabwe
   # cat desc
   wakeup in pweemptive pew-cpu testing monitow.
   # cat enabwe
   0

**monitows/MONITOW/desc**

- Weading shows a descwiption of the monitow *MONITOW*

**monitows/MONITOW/enabwe**

- Wwiting "0" disabwes the *MONITOW*
- Wwiting "1" enabwes the *MONITOW*
- Weading wetuwn the cuwwent status of the *MONITOW*

**monitows/MONITOW/weactows**

- Wist avaiwabwe weactows, with the sewect weaction fow the given *MONITOW*
  inside "[]". The defauwt one is the nop (no opewation) weactow.
- Wwiting the name of a weactow enabwes it to the given MONITOW.

Fow exampwe::

   # cat monitows/wip/weactows
   [nop]
   panic
   pwintk
   # echo panic > monitows/wip/weactows
   # cat monitows/wip/weactows
   nop
   [panic]
   pwintk
