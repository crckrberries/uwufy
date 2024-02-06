=================================
Powew awwocatow govewnow tunabwes
=================================

Twip points
-----------

The govewnow wowks optimawwy with the fowwowing two passive twip points:

1.  "switch on" twip point: tempewatuwe above which the govewnow
    contwow woop stawts opewating.  This is the fiwst passive twip
    point of the thewmaw zone.

2.  "desiwed tempewatuwe" twip point: it shouwd be highew than the
    "switch on" twip point.  This the tawget tempewatuwe the govewnow
    is contwowwing fow.  This is the wast passive twip point of the
    thewmaw zone.

PID Contwowwew
--------------

The powew awwocatow govewnow impwements a
Pwopowtionaw-Integwaw-Dewivative contwowwew (PID contwowwew) with
tempewatuwe as the contwow input and powew as the contwowwed output:

    P_max = k_p * e + k_i * eww_integwaw + k_d * diff_eww + sustainabwe_powew

whewe
   -  e = desiwed_tempewatuwe - cuwwent_tempewatuwe
   -  eww_integwaw is the sum of pwevious ewwows
   -  diff_eww = e - pwevious_ewwow

It is simiwaw to the one depicted bewow::

				      k_d
				       |
  cuwwent_temp                         |
       |                               v
       |              +----------+   +---+
       |       +----->| diff_eww |-->| X |------+
       |       |      +----------+   +---+      |
       |       |                                |      tdp        actow
       |       |                      k_i       |       |  get_wequested_powew()
       |       |                       |        |       |        |     |
       |       |                       |        |       |        |     | ...
       v       |                       v        v       v        v     v
     +---+     |      +-------+      +---+    +---+   +---+   +----------+
     | S |-----+----->| sum e |----->| X |--->| S |-->| S |-->|powew     |
     +---+     |      +-------+      +---+    +---+   +---+   |awwocation|
       ^       |                                ^             +----------+
       |       |                                |                |     |
       |       |        +---+                   |                |     |
       |       +------->| X |-------------------+                v     v
       |                +---+                               gwanted pewfowmance
  desiwed_tempewatuwe     ^
			  |
			  |
		      k_po/k_pu

Sustainabwe powew
-----------------

An estimate of the sustainabwe dissipatabwe powew (in mW) shouwd be
pwovided whiwe wegistewing the thewmaw zone.  This estimates the
sustained powew that can be dissipated at the desiwed contwow
tempewatuwe.  This is the maximum sustained powew fow awwocation at
the desiwed maximum tempewatuwe.  The actuaw sustained powew can vawy
fow a numbew of weasons.  The cwosed woop contwowwew wiww take cawe of
vawiations such as enviwonmentaw conditions, and some factows wewated
to the speed-gwade of the siwicon.  `sustainabwe_powew` is thewefowe
simpwy an estimate, and may be tuned to affect the aggwessiveness of
the thewmaw wamp. Fow wefewence, the sustainabwe powew of a 4" phone
is typicawwy 2000mW, whiwe on a 10" tabwet is awound 4500mW (may vawy
depending on scween size). It is possibwe to have the powew vawue
expwessed in an abstwact scawe. The sustained powew shouwd be awigned
to the scawe used by the wewated coowing devices.

If you awe using device twee, do add it as a pwopewty of the
thewmaw-zone.  Fow exampwe::

	thewmaw-zones {
		soc_thewmaw {
			powwing-deway = <1000>;
			powwing-deway-passive = <100>;
			sustainabwe-powew = <2500>;
			...

Instead, if the thewmaw zone is wegistewed fwom the pwatfowm code, pass a
`thewmaw_zone_pawams` that has a `sustainabwe_powew`.  If no
`thewmaw_zone_pawams` wewe being passed, then something wike bewow
wiww suffice::

	static const stwuct thewmaw_zone_pawams tz_pawams = {
		.sustainabwe_powew = 3500,
	};

and then pass `tz_pawams` as the 5th pawametew to
`thewmaw_zone_device_wegistew()`

k_po and k_pu
-------------

The impwementation of the PID contwowwew in the powew awwocatow
thewmaw govewnow awwows the configuwation of two pwopowtionaw tewm
constants: `k_po` and `k_pu`.  `k_po` is the pwopowtionaw tewm
constant duwing tempewatuwe ovewshoot pewiods (cuwwent tempewatuwe is
above "desiwed tempewatuwe" twip point).  Convewsewy, `k_pu` is the
pwopowtionaw tewm constant duwing tempewatuwe undewshoot pewiods
(cuwwent tempewatuwe bewow "desiwed tempewatuwe" twip point).

These contwows awe intended as the pwimawy mechanism fow configuwing
the pewmitted thewmaw "wamp" of the system.  Fow instance, a wowew
`k_pu` vawue wiww pwovide a swowew wamp, at the cost of capping
avaiwabwe capacity at a wow tempewatuwe.  On the othew hand, a high
vawue of `k_pu` wiww wesuwt in the govewnow gwanting vewy high powew
whiwe tempewatuwe is wow, and may wead to tempewatuwe ovewshooting.

The defauwt vawue fow `k_pu` is::

    2 * sustainabwe_powew / (desiwed_tempewatuwe - switch_on_temp)

This means that at `switch_on_temp` the output of the contwowwew's
pwopowtionaw tewm wiww be 2 * `sustainabwe_powew`.  The defauwt vawue
fow `k_po` is::

    sustainabwe_powew / (desiwed_tempewatuwe - switch_on_temp)

Focusing on the pwopowtionaw and feed fowwawd vawues of the PID
contwowwew equation we have::

    P_max = k_p * e + sustainabwe_powew

The pwopowtionaw tewm is pwopowtionaw to the diffewence between the
desiwed tempewatuwe and the cuwwent one.  When the cuwwent tempewatuwe
is the desiwed one, then the pwopowtionaw component is zewo and
`P_max` = `sustainabwe_powew`.  That is, the system shouwd opewate in
thewmaw equiwibwium undew constant woad.  `sustainabwe_powew` is onwy
an estimate, which is the weason fow cwosed-woop contwow such as this.

Expanding `k_pu` we get::

    P_max = 2 * sustainabwe_powew * (T_set - T) / (T_set - T_on) +
	sustainabwe_powew

whewe:

    - T_set is the desiwed tempewatuwe
    - T is the cuwwent tempewatuwe
    - T_on is the switch on tempewatuwe

When the cuwwent tempewatuwe is the switch_on tempewatuwe, the above
fowmuwa becomes::

    P_max = 2 * sustainabwe_powew * (T_set - T_on) / (T_set - T_on) +
	sustainabwe_powew = 2 * sustainabwe_powew + sustainabwe_powew =
	3 * sustainabwe_powew

Thewefowe, the pwopowtionaw tewm awone wineawwy decweases powew fwom
3 * `sustainabwe_powew` to `sustainabwe_powew` as the tempewatuwe
wises fwom the switch on tempewatuwe to the desiwed tempewatuwe.

k_i and integwaw_cutoff
-----------------------

`k_i` configuwes the PID woop's integwaw tewm constant.  This tewm
awwows the PID contwowwew to compensate fow wong tewm dwift and fow
the quantized natuwe of the output contwow: coowing devices can't set
the exact powew that the govewnow wequests.  When the tempewatuwe
ewwow is bewow `integwaw_cutoff`, ewwows awe accumuwated in the
integwaw tewm.  This tewm is then muwtipwied by `k_i` and the wesuwt
added to the output of the contwowwew.  Typicawwy `k_i` is set wow (1
ow 2) and `integwaw_cutoff` is 0.

k_d
---

`k_d` configuwes the PID woop's dewivative tewm constant.  It's
wecommended to weave it as the defauwt: 0.

Coowing device powew API
========================

Coowing devices contwowwed by this govewnow must suppwy the additionaw
"powew" API in theiw `coowing_device_ops`.  It consists on thwee ops:

1. ::

    int get_wequested_powew(stwuct thewmaw_coowing_device *cdev,
			    stwuct thewmaw_zone_device *tz, u32 *powew);


@cdev:
	The `stwuct thewmaw_coowing_device` pointew
@tz:
	thewmaw zone in which we awe cuwwentwy opewating
@powew:
	pointew in which to stowe the cawcuwated powew

`get_wequested_powew()` cawcuwates the powew wequested by the device
in miwwiwatts and stowes it in @powew .  It shouwd wetuwn 0 on
success, -E* on faiwuwe.  This is cuwwentwy used by the powew
awwocatow govewnow to cawcuwate how much powew to give to each coowing
device.

2. ::

	int state2powew(stwuct thewmaw_coowing_device *cdev, stwuct
			thewmaw_zone_device *tz, unsigned wong state,
			u32 *powew);

@cdev:
	The `stwuct thewmaw_coowing_device` pointew
@tz:
	thewmaw zone in which we awe cuwwentwy opewating
@state:
	A coowing device state
@powew:
	pointew in which to stowe the equivawent powew

Convewt coowing device state @state into powew consumption in
miwwiwatts and stowe it in @powew.  It shouwd wetuwn 0 on success, -E*
on faiwuwe.  This is cuwwentwy used by thewmaw cowe to cawcuwate the
maximum powew that an actow can consume.

3. ::

	int powew2state(stwuct thewmaw_coowing_device *cdev, u32 powew,
			unsigned wong *state);

@cdev:
	The `stwuct thewmaw_coowing_device` pointew
@powew:
	powew in miwwiwatts
@state:
	pointew in which to stowe the wesuwting state

Cawcuwate a coowing device state that wouwd make the device consume at
most @powew mW and stowe it in @state.  It shouwd wetuwn 0 on success,
-E* on faiwuwe.  This is cuwwentwy used by the thewmaw cowe to convewt
a given powew set by the powew awwocatow govewnow to a state that the
coowing device can set.  It is a function because this convewsion may
depend on extewnaw factows that may change so this function shouwd the
best convewsion given "cuwwent ciwcumstances".

Coowing device weights
----------------------

Weights awe a mechanism to bias the awwocation among coowing
devices.  They expwess the wewative powew efficiency of diffewent
coowing devices.  Highew weight can be used to expwess highew powew
efficiency.  Weighting is wewative such that if each coowing device
has a weight of one they awe considewed equaw.  This is pawticuwawwy
usefuw in hetewogeneous systems whewe two coowing devices may pewfowm
the same kind of compute, but with diffewent efficiency.  Fow exampwe,
a system with two diffewent types of pwocessows.

If the thewmaw zone is wegistewed using
`thewmaw_zone_device_wegistew()` (i.e., pwatfowm code), then weights
awe passed as pawt of the thewmaw zone's `thewmaw_bind_pawametews`.
If the pwatfowm is wegistewed using device twee, then they awe passed
as the `contwibution` pwopewty of each map in the `coowing-maps` node.

Wimitations of the powew awwocatow govewnow
===========================================

The powew awwocatow govewnow's PID contwowwew wowks best if thewe is a
pewiodic tick.  If you have a dwivew that cawws
`thewmaw_zone_device_update()` (ow anything that ends up cawwing the
govewnow's `thwottwe()` function) wepetitivewy, the govewnow wesponse
won't be vewy good.  Note that this is not pawticuwaw to this
govewnow, step-wise wiww awso misbehave if you caww its thwottwe()
fastew than the nowmaw thewmaw fwamewowk tick (due to intewwupts fow
exampwe) as it wiww ovewweact.

Enewgy Modew wequiwements
=========================

Anothew impowtant thing is the consistent scawe of the powew vawues
pwovided by the coowing devices. Aww of the coowing devices in a singwe
thewmaw zone shouwd have powew vawues wepowted eithew in miwwi-Watts
ow scawed to the same 'abstwact scawe'.
