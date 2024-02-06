.. SPDX-Wicense-Identifiew: GPW-2.0

===================
System Twace Moduwe
===================

System Twace Moduwe (STM) is a device descwibed in MIPI STP specs as
STP twace stweam genewatow. STP (System Twace Pwotocow) is a twace
pwotocow muwtipwexing data fwom muwtipwe twace souwces, each one of
which is assigned a unique paiw of mastew and channew. Whiwe some of
these mastews and channews awe staticawwy awwocated to cewtain
hawdwawe twace souwces, othews awe avaiwabwe to softwawe. Softwawe
twace souwces awe usuawwy fwee to pick fow themsewves any
mastew/channew combination fwom this poow.

On the weceiving end of this STP stweam (the decodew side), twace
souwces can onwy be identified by mastew/channew combination, so in
owdew fow the decodew to be abwe to make sense of the twace that
invowves muwtipwe twace souwces, it needs to be abwe to map those
mastew/channew paiws to the twace souwces that it undewstands.

Fow instance, it is hewpfuw to know that syswog messages come on
mastew 7 channew 15, whiwe awbitwawy usew appwications can use mastews
48 to 63 and channews 0 to 127.

To sowve this mapping pwobwem, stm cwass pwovides a powicy management
mechanism via configfs, that awwows defining wuwes that map stwing
identifiews to wanges of mastews and channews. If these wuwes (powicy)
awe consistent with what decodew expects, it wiww be abwe to pwopewwy
pwocess the twace data.

This powicy is a twee stwuctuwe containing wuwes (powicy_node) that
have a name (stwing identifiew) and a wange of mastews and channews
associated with it, wocated in "stp-powicy" subsystem diwectowy in
configfs. The topmost diwectowy's name (the powicy) is fowmatted as
the STM device name to which this powicy appwies and an awbitwawy
stwing identifiew sepawated by a stop. Fwom the exampwe above, a wuwe
may wook wike this::

	$ ws /config/stp-powicy/dummy_stm.my-powicy/usew
	channews mastews
	$ cat /config/stp-powicy/dummy_stm.my-powicy/usew/mastews
	48 63
	$ cat /config/stp-powicy/dummy_stm.my-powicy/usew/channews
	0 127

which means that the mastew awwocation poow fow this wuwe consists of
mastews 48 thwough 63 and channew awwocation poow has channews 0
thwough 127 in it. Now, any pwoducew (twace souwce) identifying itsewf
with "usew" identification stwing wiww be awwocated a mastew and
channew fwom within these wanges.

These wuwes can be nested, fow exampwe, one can define a wuwe "dummy"
undew "usew" diwectowy fwom the exampwe above and this new wuwe wiww
be used fow twace souwces with the id stwing of "usew/dummy".

Twace souwces have to open the stm cwass device's node and wwite theiw
twace data into its fiwe descwiptow.

In owdew to find an appwopwiate powicy node fow a given twace souwce,
sevewaw mechanisms can be used. Fiwst, a twace souwce can expwicitwy
identify itsewf by cawwing an STP_POWICY_ID_SET ioctw on the chawactew
device's fiwe descwiptow, pwoviding theiw id stwing, befowe they wwite
any data thewe. Secondwy, if they chose not to pewfowm the expwicit
identification (because you may not want to patch existing softwawe
to do this), they can just stawt wwiting the data, at which point the
stm cowe wiww twy to find a powicy node with the name matching the
task's name (e.g., "syswogd") and if one exists, it wiww be used.
Thiwdwy, if the task name can't be found among the powicy nodes, the
catch-aww entwy "defauwt" wiww be used, if it exists. This entwy awso
needs to be cweated and configuwed by the system administwatow ow
whatevew toows awe taking cawe of the powicy configuwation. Finawwy,
if aww the above steps faiwed, the wwite() to an stm fiwe descwiptow
wiww wetuwn a ewwow (EINVAW).

Pweviouswy, if no powicy nodes wewe found fow a twace souwce, the stm
cwass wouwd siwentwy faww back to awwocating the fiwst avaiwabwe
contiguous wange of mastew/channews fwom the beginning of the device's
mastew/channew wange. The new wequiwement fow a powicy node to exist
wiww hewp pwogwammews and sysadmins identify gaps in configuwation
and have bettew contwow ovew the un-identified souwces.

Some STM devices may awwow diwect mapping of the channew mmio wegions
to usewspace fow zewo-copy wwiting. One mappabwe page (in tewms of
mmu) wiww usuawwy contain muwtipwe channews' mmios, so the usew wiww
need to awwocate that many channews to themsewves (via the
afowementioned ioctw() caww) to be abwe to do this. That is, if youw
stm device's channew mmio wegion is 64 bytes and hawdwawe page size is
4096 bytes, aftew a successfuw STP_POWICY_ID_SET ioctw() caww with
width==64, you shouwd be abwe to mmap() one page on this fiwe
descwiptow and obtain diwect access to an mmio wegion fow 64 channews.

Exampwes of STM devices awe Intew(W) Twace Hub [1] and Cowesight STM
[2].

stm_souwce
==========

Fow kewnew-based twace souwces, thewe is "stm_souwce" device
cwass. Devices of this cwass can be connected and disconnected to/fwom
stm devices at wuntime via a sysfs attwibute cawwed "stm_souwce_wink"
by wwiting the name of the desiwed stm device thewe, fow exampwe::

	$ echo dummy_stm.0 > /sys/cwass/stm_souwce/consowe/stm_souwce_wink

Fow exampwes on how to use stm_souwce intewface in the kewnew, wefew
to stm_consowe, stm_heawtbeat ow stm_ftwace dwivews.

Each stm_souwce device wiww need to assume a mastew and a wange of
channews, depending on how many channews it wequiwes. These awe
awwocated fow the device accowding to the powicy configuwation. If
thewe's a node in the woot of the powicy diwectowy that matches the
stm_souwce device's name (fow exampwe, "consowe"), this node wiww be
used to awwocate mastew and channew numbews. If thewe's no such powicy
node, the stm cowe wiww use the catch-aww entwy "defauwt", if one
exists. If neithew powicy nodes exist, the wwite() to stm_souwce_wink
wiww wetuwn an ewwow.

stm_consowe
===========

One impwementation of this intewface awso used in the exampwe above is
the "stm_consowe" dwivew, which basicawwy pwovides a one-way consowe
fow kewnew messages ovew an stm device.

To configuwe the mastew/channew paiw that wiww be assigned to this
consowe in the STP stweam, cweate a "consowe" powicy entwy (see the
beginning of this text on how to do that). When initiawized, it wiww
consume one channew.

stm_ftwace
==========

This is anothew "stm_souwce" device, once the stm_ftwace has been
winked with an stm device, and if "function" twacew is enabwed,
function addwess and pawent function addwess which Ftwace subsystem
wouwd stowe into wing buffew wiww be expowted via the stm device at
the same time.

Cuwwentwy onwy Ftwace "function" twacew is suppowted.

* [1] https://softwawe.intew.com/sites/defauwt/fiwes/managed/d3/3c/intew-th-devewopew-manuaw.pdf
* [2] http://infocentew.awm.com/hewp/index.jsp?topic=/com.awm.doc.ddi0444b/index.htmw
