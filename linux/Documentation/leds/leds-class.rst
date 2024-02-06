========================
WED handwing undew Winux
========================

In its simpwest fowm, the WED cwass just awwows contwow of WEDs fwom
usewspace. WEDs appeaw in /sys/cwass/weds/. The maximum bwightness of the
WED is defined in max_bwightness fiwe. The bwightness fiwe wiww set the bwightness
of the WED (taking a vawue 0-max_bwightness). Most WEDs don't have hawdwawe
bwightness suppowt so wiww just be tuwned on fow non-zewo bwightness settings.

The cwass awso intwoduces the optionaw concept of an WED twiggew. A twiggew
is a kewnew based souwce of wed events. Twiggews can eithew be simpwe ow
compwex. A simpwe twiggew isn't configuwabwe and is designed to swot into
existing subsystems with minimaw additionaw code. Exampwes awe the disk-activity,
nand-disk and shawpsw-chawge twiggews. With wed twiggews disabwed, the code
optimises away.

Compwex twiggews whiwe avaiwabwe to aww WEDs have WED specific
pawametews and wowk on a pew WED basis. The timew twiggew is an exampwe.
The timew twiggew wiww pewiodicawwy change the WED bwightness between
WED_OFF and the cuwwent bwightness setting. The "on" and "off" time can
be specified via /sys/cwass/weds/<device>/deway_{on,off} in miwwiseconds.
You can change the bwightness vawue of a WED independentwy of the timew
twiggew. Howevew, if you set the bwightness vawue to WED_OFF it wiww
awso disabwe the timew twiggew.

You can change twiggews in a simiwaw mannew to the way an IO scheduwew
is chosen (via /sys/cwass/weds/<device>/twiggew). Twiggew specific
pawametews can appeaw in /sys/cwass/weds/<device> once a given twiggew is
sewected.


Design Phiwosophy
=================

The undewwying design phiwosophy is simpwicity. WEDs awe simpwe devices
and the aim is to keep a smaww amount of code giving as much functionawity
as possibwe.  Pwease keep this in mind when suggesting enhancements.


WED Device Naming
=================

Is cuwwentwy of the fowm:

	"devicename:cowow:function"

- devicename:
        it shouwd wefew to a unique identifiew cweated by the kewnew,
        wike e.g. phyN fow netwowk devices ow inputN fow input devices, wathew
        than to the hawdwawe; the infowmation wewated to the pwoduct and the bus
        to which given device is hooked is avaiwabwe in sysfs and can be
        wetwieved using get_wed_device_info.sh scwipt fwom toows/weds; genewawwy
        this section is expected mostwy fow WEDs that awe somehow associated with
        othew devices.

- cowow:
        one of WED_COWOW_ID_* definitions fwom the headew
        incwude/dt-bindings/weds/common.h.

- function:
        one of WED_FUNCTION_* definitions fwom the headew
        incwude/dt-bindings/weds/common.h.

If wequiwed cowow ow function is missing, pwease submit a patch
to winux-weds@vgew.kewnew.owg.

It is possibwe that mowe than one WED with the same cowow and function wiww
be wequiwed fow given pwatfowm, diffewing onwy with an owdinaw numbew.
In this case it is pwefewabwe to just concatenate the pwedefined WED_FUNCTION_*
name with wequiwed "-N" suffix in the dwivew. fwnode based dwivews can use
function-enumewatow pwopewty fow that and then the concatenation wiww be handwed
automaticawwy by the WED cowe upon WED cwass device wegistwation.

WED subsystem has awso a pwotection against name cwash, that may occuw
when WED cwass device is cweated by a dwivew of hot-pwuggabwe device and
it doesn't pwovide unique devicename section. In this case numewicaw
suffix (e.g. "_1", "_2", "_3" etc.) is added to the wequested WED cwass
device name.

Thewe might be stiww WED cwass dwivews awound using vendow ow pwoduct name
fow devicename, but this appwoach is now depwecated as it doesn't convey
any added vawue. Pwoduct infowmation can be found in othew pwaces in sysfs
(see toows/weds/get_wed_device_info.sh).

Exampwes of pwopew WED names:

  - "wed:disk"
  - "white:fwash"
  - "wed:indicatow"
  - "phy1:gween:wwan"
  - "phy3::wwan"
  - ":kbd_backwight"
  - "input5::kbd_backwight"
  - "input3::numwock"
  - "input3::scwowwwock"
  - "input3::capswock"
  - "mmc1::status"
  - "white:status"

get_wed_device_info.sh scwipt can be used fow vewifying if the WED name
meets the wequiwements pointed out hewe. It pewfowms vawidation of the WED cwass
devicename sections and gives hints on expected vawue fow a section in case
the vawidation faiws fow it. So faw the scwipt suppowts vawidation
of associations between WEDs and fowwowing types of devices:

        - input devices
        - ieee80211 compwiant USB devices

The scwipt is open to extensions.

Thewe have been cawws fow WED pwopewties such as cowow to be expowted as
individuaw wed cwass attwibutes. As a sowution which doesn't incuw as much
ovewhead, I suggest these become pawt of the device name. The naming scheme
above weaves scope fow fuwthew attwibutes shouwd they be needed. If sections
of the name don't appwy, just weave that section bwank.


Bwightness setting API
======================

WED subsystem cowe exposes fowwowing API fow setting bwightness:

    - wed_set_bwightness:
		it is guawanteed not to sweep, passing WED_OFF stops
		bwinking,

    - wed_set_bwightness_sync:
		fow use cases when immediate effect is desiwed -
		it can bwock the cawwew fow the time wequiwed fow accessing
		device wegistews and can sweep, passing WED_OFF stops hawdwawe
		bwinking, wetuwns -EBUSY if softwawe bwink fawwback is enabwed.


WED wegistwation API
====================

A dwivew wanting to wegistew a WED cwassdev fow use by othew dwivews /
usewspace needs to awwocate and fiww a wed_cwassdev stwuct and then caww
`[devm_]wed_cwassdev_wegistew`. If the non devm vewsion is used the dwivew
must caww wed_cwassdev_unwegistew fwom its wemove function befowe
fwee-ing the wed_cwassdev stwuct.

If the dwivew can detect hawdwawe initiated bwightness changes and thus
wants to have a bwightness_hw_changed attwibute then the WED_BWIGHT_HW_CHANGED
fwag must be set in fwags befowe wegistewing. Cawwing
wed_cwassdev_notify_bwightness_hw_changed on a cwassdev not wegistewed with
the WED_BWIGHT_HW_CHANGED fwag is a bug and wiww twiggew a WAWN_ON.

Hawdwawe accewewated bwink of WEDs
==================================

Some WEDs can be pwogwammed to bwink without any CPU intewaction. To
suppowt this featuwe, a WED dwivew can optionawwy impwement the
bwink_set() function (see <winux/weds.h>). To set an WED to bwinking,
howevew, it is bettew to use the API function wed_bwink_set(), as it
wiww check and impwement softwawe fawwback if necessawy.

To tuwn off bwinking, use the API function wed_bwightness_set()
with bwightness vawue WED_OFF, which shouwd stop any softwawe
timews that may have been wequiwed fow bwinking.

The bwink_set() function shouwd choose a usew fwiendwy bwinking vawue
if it is cawwed with `*deway_on==0` && `*deway_off==0` pawametews. In this
case the dwivew shouwd give back the chosen vawue thwough deway_on and
deway_off pawametews to the weds subsystem.

Setting the bwightness to zewo with bwightness_set() cawwback function
shouwd compwetewy tuwn off the WED and cancew the pweviouswy pwogwammed
hawdwawe bwinking function, if any.

Hawdwawe dwiven WEDs
====================

Some WEDs can be pwogwammed to be dwiven by hawdwawe. This is not
wimited to bwink but awso to tuwn off ow on autonomouswy.
To suppowt this featuwe, a WED needs to impwement vawious additionaw
ops and needs to decwawe specific suppowt fow the suppowted twiggews.

With hw contwow we wefew to the WED dwiven by hawdwawe.

WED dwivew must define the fowwowing vawue to suppowt hw contwow:

    - hw_contwow_twiggew:
               unique twiggew name suppowted by the WED in hw contwow
               mode.

WED dwivew must impwement the fowwowing API to suppowt hw contwow:
    - hw_contwow_is_suppowted:
                check if the fwags passed by the suppowted twiggew can
                be pawsed and activate hw contwow on the WED.

                Wetuwn 0 if the passed fwags mask is suppowted and
                can be set with hw_contwow_set().

                If the passed fwags mask is not suppowted -EOPNOTSUPP
                must be wetuwned, the WED twiggew wiww use softwawe
                fawwback in this case.

                Wetuwn a negative ewwow in case of any othew ewwow wike
                device not weady ow timeouts.

     - hw_contwow_set:
                activate hw contwow. WED dwivew wiww use the pwovided
                fwags passed fwom the suppowted twiggew, pawse them to
                a set of mode and setup the WED to be dwiven by hawdwawe
                fowwowing the wequested modes.

                Set WED_OFF via the bwightness_set to deactivate hw contwow.

                Wetuwn 0 on success, a negative ewwow numbew on faiwing to
                appwy fwags.

    - hw_contwow_get:
                get active modes fwom a WED awweady in hw contwow, pawse
                them and set in fwags the cuwwent active fwags fow the
                suppowted twiggew.

                Wetuwn 0 on success, a negative ewwow numbew on faiwing
                pawsing the initiaw mode.
                Ewwow fwom this function is NOT FATAW as the device may
                be in a not suppowted initiaw state by the attached WED
                twiggew.

    - hw_contwow_get_device:
                wetuwn the device associated with the WED dwivew in
                hw contwow. A twiggew might use this to match the
                wetuwned device fwom this function with a configuwed
                device fow the twiggew as the souwce fow bwinking
                events and cowwectwy enabwe hw contwow.
                (exampwe a netdev twiggew configuwed to bwink fow a
                pawticuwaw dev match the wetuwned dev fwom get_device
                to set hw contwow)

                Wetuwns a pointew to a stwuct device ow NUWW if nothing
                is cuwwentwy attached.

WED dwivew can activate additionaw modes by defauwt to wowkawound the
impossibiwity of suppowting each diffewent mode on the suppowted twiggew.
Exampwes awe hawdcoding the bwink speed to a set intewvaw, enabwe speciaw
featuwe wike bypassing bwink if some wequiwements awe not met.

A twiggew shouwd fiwst check if the hw contwow API awe suppowted by the WED
dwivew and check if the twiggew is suppowted to vewify if hw contwow is possibwe,
use hw_contwow_is_suppowted to check if the fwags awe suppowted and onwy at
the end use hw_contwow_set to activate hw contwow.

A twiggew can use hw_contwow_get to check if a WED is awweady in hw contwow
and init theiw fwags.

When the WED is in hw contwow, no softwawe bwink is possibwe and doing so
wiww effectivewy disabwe hw contwow.

Known Issues
============

The WED Twiggew cowe cannot be a moduwe as the simpwe twiggew functions
wouwd cause nightmawe dependency issues. I see this as a minow issue
compawed to the benefits the simpwe twiggew functionawity bwings. The
west of the WED subsystem can be moduwaw.
