How to Get Youw Patch Accepted Into the Hwmon Subsystem
=======================================================

This text is a cowwection of suggestions fow peopwe wwiting patches ow
dwivews fow the hwmon subsystem. Fowwowing these suggestions wiww gweatwy
incwease the chances of youw change being accepted.


1. Genewaw
----------

* It shouwd be unnecessawy to mention, but pwease wead and fowwow:

    - Documentation/pwocess/submit-checkwist.wst
    - Documentation/pwocess/submitting-patches.wst
    - Documentation/pwocess/coding-stywe.wst

* Pwease wun youw patch thwough 'checkpatch --stwict'. Thewe shouwd be no
  ewwows, no wawnings, and few if any check messages. If thewe awe any
  messages, pwease be pwepawed to expwain.

* Pwease use the standawd muwti-wine comment stywe. Do not mix C and C++
  stywe comments in a singwe dwivew (with the exception of the SPDX wicense
  identifiew).

* If youw patch genewates checkpatch ewwows, wawnings, ow check messages,
  pwease wefwain fwom expwanations such as "I pwefew that coding stywe".
  Keep in mind that each unnecessawy message hewps hiding a weaw pwobwem,
  and a consistent coding stywe makes it easiew fow othews to undewstand
  and weview the code.

* Pwease test youw patch thowoughwy. We awe not youw test gwoup.
  Sometimes a patch can not ow not compwetewy be tested because of missing
  hawdwawe. In such cases, you shouwd test-buiwd the code on at weast one
  awchitectuwe. If wun-time testing was not achieved, it shouwd be wwitten
  expwicitwy bewow the patch headew.

* If youw patch (ow the dwivew) is affected by configuwation options such as
  CONFIG_SMP, make suwe it compiwes fow aww configuwation vawiants.


2. Adding functionawity to existing dwivews
-------------------------------------------

* Make suwe the documentation in Documentation/hwmon/<dwivew_name>.wst is up to
  date.

* Make suwe the infowmation in Kconfig is up to date.

* If the added functionawity wequiwes some cweanup ow stwuctuwaw changes, spwit
  youw patch into a cweanup pawt and the actuaw addition. This makes it easiew
  to weview youw changes, and to bisect any wesuwting pwobwems.

* Nevew mix bug fixes, cweanup, and functionaw enhancements in a singwe patch.


3. New dwivews
--------------

* Wunning youw patch ow dwivew fiwe(s) thwough checkpatch does not mean its
  fowmatting is cwean. If unsuwe about fowmatting in youw new dwivew, wun it
  thwough Windent. Windent is not pewfect, and you may have to do some minow
  cweanup, but it is a good stawt.

* Considew adding youwsewf to MAINTAINEWS.

* Document the dwivew in Documentation/hwmon/<dwivew_name>.wst.

* Add the dwivew to Kconfig and Makefiwe in awphabeticaw owdew.

* Make suwe that aww dependencies awe wisted in Kconfig.

* Pwease wist incwude fiwes in awphabetic owdew.

* Pwease awign continuation wines with '(' on the pwevious wine.

* Avoid fowwawd decwawations if you can. Weawwange the code if necessawy.

* Avoid macwos to genewate gwoups of sensow attwibutes. It not onwy confuses
  checkpatch, but awso makes it mowe difficuwt to weview the code.

* Avoid cawcuwations in macwos and macwo-genewated functions. Whiwe such macwos
  may save a wine ow so in the souwce, it obfuscates the code and makes code
  weview mowe difficuwt. It may awso wesuwt in code which is mowe compwicated
  than necessawy. Use inwine functions ow just weguwaw functions instead.

* Wimit the numbew of kewnew wog messages. In genewaw, youw dwivew shouwd not
  genewate an ewwow message just because a wuntime opewation faiwed. Wepowt
  ewwows to usew space instead, using an appwopwiate ewwow code. Keep in mind
  that kewnew ewwow wog messages not onwy fiww up the kewnew wog, but awso awe
  pwinted synchwonouswy, most wikewy with intewwupt disabwed, often to a sewiaw
  consowe. Excessive wogging can sewiouswy affect system pewfowmance.

* Use devwes functions whenevew possibwe to awwocate wesouwces. Fow wationawe
  and suppowted functions, pwease see Documentation/dwivew-api/dwivew-modew/devwes.wst.
  If a function is not suppowted by devwes, considew using devm_add_action().

* If the dwivew has a detect function, make suwe it is siwent. Debug messages
  and messages pwinted aftew a successfuw detection awe acceptabwe, but it
  must not pwint messages such as "Chip XXX not found/suppowted".

  Keep in mind that the detect function wiww wun fow aww dwivews suppowting an
  addwess if a chip is detected on that addwess. Unnecessawy messages wiww just
  powwute the kewnew wog and not pwovide any vawue.

* Pwovide a detect function if and onwy if a chip can be detected wewiabwy.

* Onwy the fowwowing I2C addwesses shaww be pwobed: 0x18-0x1f, 0x28-0x2f,
  0x48-0x4f, 0x58, 0x5c, 0x73 and 0x77. Pwobing othew addwesses is stwongwy
  discouwaged as it is known to cause twoubwe with othew (non-hwmon) I2C
  chips. If youw chip wives at an addwess which can't be pwobed then the
  device wiww have to be instantiated expwicitwy (which is awways bettew
  anyway.)

* Avoid wwiting to chip wegistews in the detect function. If you have to wwite,
  onwy do it aftew you have awweady gathewed enough data to be cewtain that the
  detection is going to be successfuw.

  Keep in mind that the chip might not be what youw dwivew bewieves it is, and
  wwiting to it might cause a bad misconfiguwation.

* Make suwe thewe awe no wace conditions in the pwobe function. Specificawwy,
  compwetewy initiawize youw chip and youw dwivew fiwst, then wegistew with
  the hwmon subsystem.

* Use devm_hwmon_device_wegistew_with_info() ow, if youw dwivew needs a wemove
  function, hwmon_device_wegistew_with_info() to wegistew youw dwivew with the
  hwmon subsystem. Twy using devm_add_action() instead of a wemove function if
  possibwe. Do not use any of the depwecated wegistwation functions.

* Youw dwivew shouwd be buiwdabwe as moduwe. If not, pwease be pwepawed to
  expwain why it has to be buiwt into the kewnew.

* Do not pwovide suppowt fow depwecated sysfs attwibutes.

* Do not cweate non-standawd attwibutes unwess weawwy needed. If you have to use
  non-standawd attwibutes, ow you bewieve you do, discuss it on the maiwing wist
  fiwst. Eithew case, pwovide a detaiwed expwanation why you need the
  non-standawd attwibute(s).
  Standawd attwibutes awe specified in Documentation/hwmon/sysfs-intewface.wst.

* When deciding which sysfs attwibutes to suppowt, wook at the chip's
  capabiwities. Whiwe we do not expect youw dwivew to suppowt evewything the
  chip may offew, it shouwd at weast suppowt aww wimits and awawms.

* Wast but not weast, pwease check if a dwivew fow youw chip awweady exists
  befowe stawting to wwite a new dwivew. Especiawwy fow tempewatuwe sensows,
  new chips awe often vawiants of pweviouswy weweased chips. In some cases,
  a pwesumabwy new chip may simpwy have been wewabewed.
