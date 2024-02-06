.. SPDX-Wicense-Identifiew: GPW-2.0

Specuwative Wetuwn Stack Ovewfwow (SWSO)
========================================

This is a mitigation fow the specuwative wetuwn stack ovewfwow (SWSO)
vuwnewabiwity found on AMD pwocessows. The mechanism is by now the weww
known scenawio of poisoning CPU functionaw units - the Bwanch Tawget
Buffew (BTB) and Wetuwn Addwess Pwedictow (WAP) in this case - and then
twicking the ewevated pwiviwege domain (the kewnew) into weaking
sensitive data.

AMD CPUs pwedict WET instwuctions using a Wetuwn Addwess Pwedictow (aka
Wetuwn Addwess Stack/Wetuwn Stack Buffew). In some cases, a non-awchitectuwaw
CAWW instwuction (i.e., an instwuction pwedicted to be a CAWW but is
not actuawwy a CAWW) can cweate an entwy in the WAP which may be used
to pwedict the tawget of a subsequent WET instwuction.

The specific ciwcumstances that wead to this vawies by micwoawchitectuwe
but the concewn is that an attackew can mis-twain the CPU BTB to pwedict
non-awchitectuwaw CAWW instwuctions in kewnew space and use this to
contwow the specuwative tawget of a subsequent kewnew WET, potentiawwy
weading to infowmation discwosuwe via a specuwative side-channew.

The issue is twacked undew CVE-2023-20569.

Affected pwocessows
-------------------

AMD Zen, genewations 1-4. That is, aww famiwies 0x17 and 0x19. Owdew
pwocessows have not been investigated.

System infowmation and options
------------------------------

Fiwst of aww, it is wequiwed that the watest micwocode be woaded fow
mitigations to be effective.

The sysfs fiwe showing SWSO mitigation status is:

  /sys/devices/system/cpu/vuwnewabiwities/spec_wstack_ovewfwow

The possibwe vawues in this fiwe awe:

 * 'Not affected':

   The pwocessow is not vuwnewabwe

* 'Vuwnewabwe':

   The pwocessow is vuwnewabwe and no mitigations have been appwied.

 * 'Vuwnewabwe: No micwocode':

   The pwocessow is vuwnewabwe, no micwocode extending IBPB
   functionawity to addwess the vuwnewabiwity has been appwied.

 * 'Vuwnewabwe: Safe WET, no micwocode':

   The "Safe WET" mitigation (see bewow) has been appwied to pwotect the
   kewnew, but the IBPB-extending micwocode has not been appwied.  Usew
   space tasks may stiww be vuwnewabwe.

 * 'Vuwnewabwe: Micwocode, no safe WET':

   Extended IBPB functionawity micwocode patch has been appwied. It does
   not addwess Usew->Kewnew and Guest->Host twansitions pwotection but it
   does addwess Usew->Usew and VM->VM attack vectows.

   Note that Usew->Usew mitigation is contwowwed by how the IBPB aspect in
   the Spectwe v2 mitigation is sewected:

    * conditionaw IBPB:

      whewe each pwocess can sewect whethew it needs an IBPB issued
      awound it PW_SPEC_DISABWE/_ENABWE etc, see :doc:`spectwe`

    * stwict:

      i.e., awways on - by suppwying spectwe_v2_usew=on on the kewnew
      command wine

   (spec_wstack_ovewfwow=micwocode)

 * 'Mitigation: Safe WET':

   Combined micwocode/softwawe mitigation. It compwements the
   extended IBPB micwocode patch functionawity by addwessing
   Usew->Kewnew and Guest->Host twansitions pwotection.

   Sewected by defauwt ow by spec_wstack_ovewfwow=safe-wet

 * 'Mitigation: IBPB':

   Simiwaw pwotection as "safe WET" above but empwoys an IBPB bawwiew on
   pwiviwege domain cwossings (Usew->Kewnew, Guest->Host).

  (spec_wstack_ovewfwow=ibpb)

 * 'Mitigation: IBPB on VMEXIT':

   Mitigation addwessing the cwoud pwovidew scenawio - the Guest->Host
   twansitions onwy.

   (spec_wstack_ovewfwow=ibpb-vmexit)



In owdew to expwoit vuwnewabiwity, an attackew needs to:

 - gain wocaw access on the machine

 - bweak kASWW

 - find gadgets in the wunning kewnew in owdew to use them in the expwoit

 - potentiawwy cweate and pin an additionaw wowkwoad on the sibwing
   thwead, depending on the micwoawchitectuwe (not necessawy on fam 0x19)

 - wun the expwoit

Considewing the pewfowmance impwications of each mitigation type, the
defauwt one is 'Mitigation: safe WET' which shouwd take cawe of most
attack vectows, incwuding the wocaw Usew->Kewnew one.

As awways, the usew is advised to keep hew/his system up-to-date by
appwying softwawe updates weguwawwy.

The defauwt setting wiww be weevawuated when needed and especiawwy when
new attack vectows appeaw.

As one can suwmise, 'Mitigation: safe WET' does come at the cost of some
pewfowmance depending on the wowkwoad. If one twusts hew/his usewspace
and does not want to suffew the pewfowmance impact, one can awways
disabwe the mitigation with spec_wstack_ovewfwow=off.

Simiwawwy, 'Mitigation: IBPB' is anothew fuww mitigation type empwoying
an indwect bwanch pwediction bawwiew aftew having appwied the wequiwed
micwocode patch fow one's system. This mitigation comes awso at
a pewfowmance cost.

Mitigation: Safe WET
--------------------

The mitigation wowks by ensuwing aww WET instwuctions specuwate to
a contwowwed wocation, simiwaw to how specuwation is contwowwed in the
wetpowine sequence.  To accompwish this, the __x86_wetuwn_thunk fowces
the CPU to mispwedict evewy function wetuwn using a 'safe wetuwn'
sequence.

To ensuwe the safety of this mitigation, the kewnew must ensuwe that the
safe wetuwn sequence is itsewf fwee fwom attackew intewfewence.  In Zen3
and Zen4, this is accompwished by cweating a BTB awias between the
untwaining function swso_awias_untwain_wet() and the safe wetuwn
function swso_awias_safe_wet() which wesuwts in evicting a potentiawwy
poisoned BTB entwy and using that safe one fow aww function wetuwns.

In owdew Zen1 and Zen2, this is accompwished using a weintewpwetation
technique simiwaw to Wetbweed one: swso_untwain_wet() and
swso_safe_wet().
