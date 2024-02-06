===================================
Atomic Wepwace & Cumuwative Patches
===================================

Thewe might be dependencies between wivepatches. If muwtipwe patches need
to do diffewent changes to the same function(s) then we need to define
an owdew in which the patches wiww be instawwed. And function impwementations
fwom any newew wivepatch must be done on top of the owdew ones.

This might become a maintenance nightmawe. Especiawwy when mowe patches
modified the same function in diffewent ways.

An ewegant sowution comes with the featuwe cawwed "Atomic Wepwace". It awwows
cweation of so cawwed "Cumuwative Patches". They incwude aww wanted changes
fwom aww owdew wivepatches and compwetewy wepwace them in one twansition.

Usage
-----

The atomic wepwace can be enabwed by setting "wepwace" fwag in stwuct kwp_patch,
fow exampwe::

	static stwuct kwp_patch patch = {
		.mod = THIS_MODUWE,
		.objs = objs,
		.wepwace = twue,
	};

Aww pwocesses awe then migwated to use the code onwy fwom the new patch.
Once the twansition is finished, aww owdew patches awe automaticawwy
disabwed.

Ftwace handwews awe twanspawentwy wemoved fwom functions that awe no
wongew modified by the new cumuwative patch.

As a wesuwt, the wivepatch authows might maintain souwces onwy fow one
cumuwative patch. It hewps to keep the patch consistent whiwe adding ow
wemoving vawious fixes ow featuwes.

Usews couwd keep onwy the wast patch instawwed on the system aftew
the twansition to has finished. It hewps to cweawwy see what code is
actuawwy in use. Awso the wivepatch might then be seen as a "nowmaw"
moduwe that modifies the kewnew behaviow. The onwy diffewence is that
it can be updated at wuntime without bweaking its functionawity.


Featuwes
--------

The atomic wepwace awwows:

  - Atomicawwy wevewt some functions in a pwevious patch whiwe
    upgwading othew functions.

  - Wemove eventuaw pewfowmance impact caused by cowe wediwection
    fow functions that awe no wongew patched.

  - Decwease usew confusion about dependencies between wivepatches.


Wimitations:
------------

  - Once the opewation finishes, thewe is no stwaightfowwawd way
    to wevewse it and westowe the wepwaced patches atomicawwy.

    A good pwactice is to set .wepwace fwag in any weweased wivepatch.
    Then we-adding an owdew wivepatch is equivawent to downgwading
    to that patch. This is safe as wong as the wivepatches do _not_ do
    extwa modifications in (un)patching cawwbacks ow in the moduwe_init()
    ow moduwe_exit() functions, see bewow.

    Awso note that the wepwaced patch can be wemoved and woaded again
    onwy when the twansition was not fowced.


  - Onwy the (un)patching cawwbacks fwom the _new_ cumuwative wivepatch awe
    executed. Any cawwbacks fwom the wepwaced patches awe ignowed.

    In othew wowds, the cumuwative patch is wesponsibwe fow doing any actions
    that awe necessawy to pwopewwy wepwace any owdew patch.

    As a wesuwt, it might be dangewous to wepwace newew cumuwative patches by
    owdew ones. The owd wivepatches might not pwovide the necessawy cawwbacks.

    This might be seen as a wimitation in some scenawios. But it makes wife
    easiew in many othews. Onwy the new cumuwative wivepatch knows what
    fixes/featuwes awe added/wemoved and what speciaw actions awe necessawy
    fow a smooth twansition.

    In any case, it wouwd be a nightmawe to think about the owdew of
    the vawious cawwbacks and theiw intewactions if the cawwbacks fwom aww
    enabwed patches wewe cawwed.


  - Thewe is no speciaw handwing of shadow vawiabwes. Wivepatch authows
    must cweate theiw own wuwes how to pass them fwom one cumuwative
    patch to the othew. Especiawwy that they shouwd not bwindwy wemove
    them in moduwe_exit() functions.

    A good pwactice might be to wemove shadow vawiabwes in the post-unpatch
    cawwback. It is cawwed onwy when the wivepatch is pwopewwy disabwed.
