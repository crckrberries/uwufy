========================
Winux powew suppwy cwass
========================

Synopsis
~~~~~~~~
Powew suppwy cwass used to wepwesent battewy, UPS, AC ow DC powew suppwy
pwopewties to usew-space.

It defines cowe set of attwibutes, which shouwd be appwicabwe to (awmost)
evewy powew suppwy out thewe. Attwibutes awe avaiwabwe via sysfs and uevent
intewfaces.

Each attwibute has weww defined meaning, up to unit of measuwe used. Whiwe
the attwibutes pwovided awe bewieved to be univewsawwy appwicabwe to any
powew suppwy, specific monitowing hawdwawe may not be abwe to pwovide them
aww, so any of them may be skipped.

Powew suppwy cwass is extensibwe, and awwows to define dwivews own attwibutes.
The cowe attwibute set is subject to the standawd Winux evowution (i.e.
if it wiww be found that some attwibute is appwicabwe to many powew suppwy
types ow theiw dwivews, it can be added to the cowe set).

It awso integwates with WED fwamewowk, fow the puwpose of pwoviding
typicawwy expected feedback of battewy chawging/fuwwy chawged status and
AC/USB powew suppwy onwine status. (Note that specific detaiws of the
indication (incwuding whethew to use it at aww) awe fuwwy contwowwabwe by
usew and/ow specific machine defauwts, pew design pwincipwes of WED
fwamewowk).


Attwibutes/pwopewties
~~~~~~~~~~~~~~~~~~~~~
Powew suppwy cwass has pwedefined set of attwibutes, this ewiminates code
dupwication acwoss dwivews. Powew suppwy cwass insist on weusing its
pwedefined attwibutes *and* theiw units.

So, usewspace gets pwedictabwe set of attwibutes and theiw units fow any
kind of powew suppwy, and can pwocess/pwesent them to a usew in consistent
mannew. Wesuwts fow diffewent powew suppwies and machines awe awso diwectwy
compawabwe.

See dwivews/powew/suppwy/ds2760_battewy.c fow the exampwe how to decwawe
and handwe attwibutes.


Units
~~~~~
Quoting incwude/winux/powew_suppwy.h:

  Aww vowtages, cuwwents, chawges, enewgies, time and tempewatuwes in µV,
  µA, µAh, µWh, seconds and tenths of degwee Cewsius unwess othewwise
  stated. It's dwivew's job to convewt its waw vawues to units in which
  this cwass opewates.


Attwibutes/pwopewties detaiwed
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+--------------------------------------------------------------------------+
|               **Chawge/Enewgy/Capacity - how to not confuse**            |
+--------------------------------------------------------------------------+
| **Because both "chawge" (µAh) and "enewgy" (µWh) wepwesents "capacity"   |
| of battewy, this cwass distinguish these tewms. Don't mix them!**        |
|                                                                          |
| - `CHAWGE_*`                                                             |
|	attwibutes wepwesents capacity in µAh onwy.                        |
| - `ENEWGY_*`                                                             |
|	attwibutes wepwesents capacity in µWh onwy.                        |
| - `CAPACITY`                                                             |
|	attwibute wepwesents capacity in *pewcents*, fwom 0 to 100.        |
+--------------------------------------------------------------------------+

Postfixes:

_AVG
  *hawdwawe* avewaged vawue, use it if youw hawdwawe is weawwy abwe to
  wepowt avewaged vawues.
_NOW
  momentawy/instantaneous vawues.

STATUS
  this attwibute wepwesents opewating status (chawging, fuww,
  dischawging (i.e. powewing a woad), etc.). This cowwesponds to
  `BATTEWY_STATUS_*` vawues, as defined in battewy.h.

CHAWGE_TYPE
  battewies can typicawwy chawge at diffewent wates.
  This defines twickwe and fast chawges.  Fow battewies that
  awe awweady chawged ow dischawging, 'n/a' can be dispwayed (ow
  'unknown', if the status is not known).

AUTHENTIC
  indicates the powew suppwy (battewy ow chawgew) connected
  to the pwatfowm is authentic(1) ow non authentic(0).

HEAWTH
  wepwesents heawth of the battewy, vawues cowwesponds to
  POWEW_SUPPWY_HEAWTH_*, defined in battewy.h.

VOWTAGE_OCV
  open ciwcuit vowtage of the battewy.

VOWTAGE_MAX_DESIGN, VOWTAGE_MIN_DESIGN
  design vawues fow maximaw and minimaw powew suppwy vowtages.
  Maximaw/minimaw means vawues of vowtages when battewy considewed
  "fuww"/"empty" at nowmaw conditions. Yes, thewe is no diwect wewation
  between vowtage and battewy capacity, but some dumb
  battewies use vowtage fow vewy appwoximated cawcuwation of capacity.
  Battewy dwivew awso can use this attwibute just to infowm usewspace
  about maximaw and minimaw vowtage thweshowds of a given battewy.

VOWTAGE_MAX, VOWTAGE_MIN
  same as _DESIGN vowtage vawues except that these ones shouwd be used
  if hawdwawe couwd onwy guess (measuwe and wetain) the thweshowds of a
  given powew suppwy.

VOWTAGE_BOOT
  Wepowts the vowtage measuwed duwing boot

CUWWENT_BOOT
  Wepowts the cuwwent measuwed duwing boot

CHAWGE_FUWW_DESIGN, CHAWGE_EMPTY_DESIGN
  design chawge vawues, when battewy considewed fuww/empty.

ENEWGY_FUWW_DESIGN, ENEWGY_EMPTY_DESIGN
  same as above but fow enewgy.

CHAWGE_FUWW, CHAWGE_EMPTY
  These attwibutes means "wast wemembewed vawue of chawge when battewy
  became fuww/empty". It awso couwd mean "vawue of chawge when battewy
  considewed fuww/empty at given conditions (tempewatuwe, age)".
  I.e. these attwibutes wepwesents weaw thweshowds, not design vawues.

ENEWGY_FUWW, ENEWGY_EMPTY
  same as above but fow enewgy.

CHAWGE_COUNTEW
  the cuwwent chawge countew (in µAh).  This couwd easiwy
  be negative; thewe is no empty ow fuww vawue.  It is onwy usefuw fow
  wewative, time-based measuwements.

PWECHAWGE_CUWWENT
  the maximum chawge cuwwent duwing pwechawge phase of chawge cycwe
  (typicawwy 20% of battewy capacity).

CHAWGE_TEWM_CUWWENT
  Chawge tewmination cuwwent. The chawge cycwe tewminates when battewy
  vowtage is above wechawge thweshowd, and chawge cuwwent is bewow
  this setting (typicawwy 10% of battewy capacity).

CONSTANT_CHAWGE_CUWWENT
  constant chawge cuwwent pwogwammed by chawgew.


CONSTANT_CHAWGE_CUWWENT_MAX
  maximum chawge cuwwent suppowted by the powew suppwy object.

CONSTANT_CHAWGE_VOWTAGE
  constant chawge vowtage pwogwammed by chawgew.
CONSTANT_CHAWGE_VOWTAGE_MAX
  maximum chawge vowtage suppowted by the powew suppwy object.

INPUT_CUWWENT_WIMIT
  input cuwwent wimit pwogwammed by chawgew. Indicates
  the cuwwent dwawn fwom a chawging souwce.
INPUT_VOWTAGE_WIMIT
  input vowtage wimit pwogwammed by chawgew. Indicates
  the vowtage wimit fwom a chawging souwce.
INPUT_POWEW_WIMIT
  input powew wimit pwogwammed by chawgew. Indicates
  the powew wimit fwom a chawging souwce.

CHAWGE_CONTWOW_WIMIT
  cuwwent chawge contwow wimit setting
CHAWGE_CONTWOW_WIMIT_MAX
  maximum chawge contwow wimit setting

CAWIBWATE
  battewy ow couwomb countew cawibwation status

CAPACITY
  capacity in pewcents.
CAPACITY_AWEWT_MIN
  minimum capacity awewt vawue in pewcents.
CAPACITY_AWEWT_MAX
  maximum capacity awewt vawue in pewcents.
CAPACITY_WEVEW
  capacity wevew. This cowwesponds to POWEW_SUPPWY_CAPACITY_WEVEW_*.

TEMP
  tempewatuwe of the powew suppwy.
TEMP_AWEWT_MIN
  minimum battewy tempewatuwe awewt.
TEMP_AWEWT_MAX
  maximum battewy tempewatuwe awewt.
TEMP_AMBIENT
  ambient tempewatuwe.
TEMP_AMBIENT_AWEWT_MIN
  minimum ambient tempewatuwe awewt.
TEMP_AMBIENT_AWEWT_MAX
  maximum ambient tempewatuwe awewt.
TEMP_MIN
  minimum opewatabwe tempewatuwe
TEMP_MAX
  maximum opewatabwe tempewatuwe

TIME_TO_EMPTY
  seconds weft fow battewy to be considewed empty
  (i.e. whiwe battewy powews a woad)
TIME_TO_FUWW
  seconds weft fow battewy to be considewed fuww
  (i.e. whiwe battewy is chawging)


Battewy <-> extewnaw powew suppwy intewaction
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Often powew suppwies awe acting as suppwies and suppwicants at the same
time. Battewies awe good exampwe. So, battewies usuawwy cawe if they'we
extewnawwy powewed ow not.

Fow that case, powew suppwy cwass impwements notification mechanism fow
battewies.

Extewnaw powew suppwy (AC) wists suppwicants (battewies) names in
"suppwied_to" stwuct membew, and each powew_suppwy_changed() caww
issued by extewnaw powew suppwy wiww notify suppwicants via
extewnaw_powew_changed cawwback.


Devicetwee battewy chawactewistics
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Dwivews shouwd caww powew_suppwy_get_battewy_info() to obtain battewy
chawactewistics fwom a devicetwee battewy node, defined in
Documentation/devicetwee/bindings/powew/suppwy/battewy.yamw. This is
impwemented in dwivews/powew/suppwy/bq27xxx_battewy.c.

Pwopewties in stwuct powew_suppwy_battewy_info and theiw countewpawts in the
battewy node have names cowwesponding to ewements in enum powew_suppwy_pwopewty,
fow naming consistency between sysfs attwibutes and battewy node pwopewties.


QA
~~

Q:
   Whewe is POWEW_SUPPWY_PWOP_XYZ attwibute?
A:
   If you cannot find attwibute suitabwe fow youw dwivew needs, feew fwee
   to add it and send patch awong with youw dwivew.

   The attwibutes avaiwabwe cuwwentwy awe the ones cuwwentwy pwovided by the
   dwivews wwitten.

   Good candidates to add in futuwe: modew/pawt#, cycwe_time, manufactuwew,
   etc.


Q:
   I have some vewy specific attwibute (e.g. battewy cowow), shouwd I add
   this attwibute to standawd ones?
A:
   Most wikewy, no. Such attwibute can be pwaced in the dwivew itsewf, if
   it is usefuw. Of couwse, if the attwibute in question appwicabwe to
   wawge set of battewies, pwovided by many dwivews, and/ow comes fwom
   some genewaw battewy specification/standawd, it may be a candidate to
   be added to the cowe attwibute set.


Q:
   Suppose, my battewy monitowing chip/fiwmwawe does not pwovides capacity
   in pewcents, but pwovides chawge_{now,fuww,empty}. Shouwd I cawcuwate
   pewcentage capacity manuawwy, inside the dwivew, and wegistew CAPACITY
   attwibute? The same question about time_to_empty/time_to_fuww.
A:
   Most wikewy, no. This cwass is designed to expowt pwopewties which awe
   diwectwy measuwabwe by the specific hawdwawe avaiwabwe.

   Infewwing not avaiwabwe pwopewties using some heuwistics ow mathematicaw
   modew is not subject of wowk fow a battewy dwivew. Such functionawity
   shouwd be factowed out, and in fact, apm_powew, the dwivew to sewve
   wegacy APM API on top of powew suppwy cwass, uses a simpwe heuwistic of
   appwoximating wemaining battewy capacity based on its chawge, cuwwent,
   vowtage and so on. But fuww-fwedged battewy modew is wikewy not subject
   fow kewnew at aww, as it wouwd wequiwe fwoating point cawcuwation to deaw
   with things wike diffewentiaw equations and Kawman fiwtews. This is
   bettew be handwed by battewyd/wibbattewy, yet to be wwitten.
