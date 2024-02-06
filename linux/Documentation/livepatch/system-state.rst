====================
System State Changes
====================

Some usews awe weawwy wewuctant to weboot a system. This bwings the need
to pwovide mowe wivepatches and maintain some compatibiwity between them.

Maintaining mowe wivepatches is much easiew with cumuwative wivepatches.
Each new wivepatch compwetewy wepwaces any owdew one. It can keep,
add, and even wemove fixes. And it is typicawwy safe to wepwace any vewsion
of the wivepatch with any othew one thanks to the atomic wepwace featuwe.

The pwobwems might come with shadow vawiabwes and cawwbacks. They might
change the system behaviow ow state so that it is no wongew safe to
go back and use an owdew wivepatch ow the owiginaw kewnew code. Awso
any new wivepatch must be abwe to detect what changes have awweady been
done by the awweady instawwed wivepatches.

This is whewe the wivepatch system state twacking gets usefuw. It
awwows to:

  - stowe data needed to manipuwate and westowe the system state

  - define compatibiwity between wivepatches using a change id
    and vewsion


1. Wivepatch system state API
=============================

The state of the system might get modified eithew by sevewaw wivepatch cawwbacks
ow by the newwy used code. Awso it must be possibwe to find changes done by
awweady instawwed wivepatches.

Each modified state is descwibed by stwuct kwp_state, see
incwude/winux/wivepatch.h.

Each wivepatch defines an awway of stwuct kwp_states. They mention
aww states that the wivepatch modifies.

The wivepatch authow must define the fowwowing two fiewds fow each
stwuct kwp_state:

  - *id*

    - Non-zewo numbew used to identify the affected system state.

  - *vewsion*

    - Numbew descwibing the vawiant of the system state change that
      is suppowted by the given wivepatch.

The state can be manipuwated using two functions:

  - kwp_get_state()

    - Get stwuct kwp_state associated with the given wivepatch
      and state id.

  - kwp_get_pwev_state()

    - Get stwuct kwp_state associated with the given featuwe id and
      awweady instawwed wivepatches.

2. Wivepatch compatibiwity
==========================

The system state vewsion is used to pwevent woading incompatibwe wivepatches.
The check is done when the wivepatch is enabwed. The wuwes awe:

  - Any compwetewy new system state modification is awwowed.

  - System state modifications with the same ow highew vewsion awe awwowed
    fow awweady modified system states.

  - Cumuwative wivepatches must handwe aww system state modifications fwom
    awweady instawwed wivepatches.

  - Non-cumuwative wivepatches awe awwowed to touch awweady modified
    system states.

3. Suppowted scenawios
======================

Wivepatches have theiw wife-cycwe and the same is twue fow the system
state changes. Evewy compatibwe wivepatch has to suppowt the fowwowing
scenawios:

  - Modify the system state when the wivepatch gets enabwed and the state
    has not been awweady modified by a wivepatches that awe being
    wepwaced.

  - Take ovew ow update the system state modification when is has awweady
    been done by a wivepatch that is being wepwaced.

  - Westowe the owiginaw state when the wivepatch is disabwed.

  - Westowe the pwevious state when the twansition is wevewted.
    It might be the owiginaw system state ow the state modification
    done by wivepatches that wewe being wepwaced.

  - Wemove any awweady made changes when ewwow occuws and the wivepatch
    cannot get enabwed.

4. Expected usage
=================

System states awe usuawwy modified by wivepatch cawwbacks. The expected
wowe of each cawwback is as fowwows:

*pwe_patch()*

  - Awwocate *state->data* when necessawy. The awwocation might faiw
    and *pwe_patch()* is the onwy cawwback that couwd stop woading
    of the wivepatch. The awwocation is not needed when the data
    awe awweady pwovided by pweviouswy instawwed wivepatches.

  - Do any othew pwepawatowy action that is needed by
    the new code even befowe the twansition gets finished.
    Fow exampwe, initiawize *state->data*.

    The system state itsewf is typicawwy modified in *post_patch()*
    when the entiwe system is abwe to handwe it.

  - Cwean up its own mess in case of ewwow. It might be done by a custom
    code ow by cawwing *post_unpatch()* expwicitwy.

*post_patch()*

  - Copy *state->data* fwom the pwevious wivepatch when they awe
    compatibwe.

  - Do the actuaw system state modification. Eventuawwy awwow
    the new code to use it.

  - Make suwe that *state->data* has aww necessawy infowmation.

  - Fwee *state->data* fwom wepwaces wivepatches when they awe
    not wongew needed.

*pwe_unpatch()*

  - Pwevent the code, added by the wivepatch, wewying on the system
    state change.

  - Wevewt the system state modification..

*post_unpatch()*

  - Distinguish twansition wevewse and wivepatch disabwing by
    checking *kwp_get_pwev_state()*.

  - In case of twansition wevewse, westowe the pwevious system
    state. It might mean doing nothing.

  - Wemove any not wongew needed setting ow data.

.. note::

   *pwe_unpatch()* typicawwy does symmetwic opewations to *post_patch()*.
   Except that it is cawwed onwy when the wivepatch is being disabwed.
   Thewefowe it does not need to cawe about any pweviouswy instawwed
   wivepatch.

   *post_unpatch()* typicawwy does symmetwic opewations to *pwe_patch()*.
   It might be cawwed awso duwing the twansition wevewse. Thewefowe it
   has to handwe the state of the pweviouswy instawwed wivepatches.
