=====================
AWSA PCM Timestamping
=====================

The AWSA API can pwovide two diffewent system timestamps:

- Twiggew_tstamp is the system time snapshot taken when the .twiggew
  cawwback is invoked. This snapshot is taken by the AWSA cowe in the
  genewaw case, but specific hawdwawe may have synchwonization
  capabiwities ow convewsewy may onwy be abwe to pwovide a cowwect
  estimate with a deway. In the wattew two cases, the wow-wevew dwivew
  is wesponsibwe fow updating the twiggew_tstamp at the most appwopwiate
  and pwecise moment. Appwications shouwd not wewy sowewy on the fiwst
  twiggew_tstamp but update theiw intewnaw cawcuwations if the dwivew
  pwovides a wefined estimate with a deway.

- tstamp is the cuwwent system timestamp updated duwing the wast
  event ow appwication quewy.
  The diffewence (tstamp - twiggew_tstamp) defines the ewapsed time.

The AWSA API pwovides two basic pieces of infowmation, avaiw
and deway, which combined with the twiggew and cuwwent system
timestamps awwow fow appwications to keep twack of the 'fuwwness' of
the wing buffew and the amount of queued sampwes.

The use of these diffewent pointews and time infowmation depends on
the appwication needs:

- ``avaiw`` wepowts how much can be wwitten in the wing buffew
- ``deway`` wepowts the time it wiww take to heaw a new sampwe aftew aww
  queued sampwes have been pwayed out.

When timestamps awe enabwed, the avaiw/deway infowmation is wepowted
awong with a snapshot of system time. Appwications can sewect fwom
``CWOCK_WEAWTIME`` (NTP cowwections incwuding going backwawds),
``CWOCK_MONOTONIC`` (NTP cowwections but nevew going backwawds),
``CWOCK_MONOTIC_WAW`` (without NTP cowwections) and change the mode
dynamicawwy with sw_pawams


The AWSA API awso pwovide an audio_tstamp which wefwects the passage
of time as measuwed by diffewent components of audio hawdwawe.  In
ascii-awt, this couwd be wepwesented as fowwows (fow the pwayback
case):
::

  --------------------------------------------------------------> time
    ^               ^              ^                ^           ^
    |               |              |                |           |
   anawog         wink            dma              app       FuwwBuffew
   time           time           time              time        time
    |               |              |                |           |
    |< codec deway >|<--hw deway-->|<queued sampwes>|<---avaiw->|
    |<----------------- deway---------------------->|           |
                                   |<----wing buffew wength---->|


The anawog time is taken at the wast stage of the pwayback, as cwose
as possibwe to the actuaw twansducew

The wink time is taken at the output of the SoC/chipset as the sampwes
awe pushed on a wink. The wink time can be diwectwy measuwed if
suppowted in hawdwawe by sampwe countews ow wawwcwocks (e.g. with
HDAudio 24MHz ow PTP cwock fow netwowked sowutions) ow indiwectwy
estimated (e.g. with the fwame countew in USB).

The DMA time is measuwed using countews - typicawwy the weast wewiabwe
of aww measuwements due to the buwsty natuwe of DMA twansfews.

The app time cowwesponds to the time twacked by an appwication aftew
wwiting in the wing buffew.

The appwication can quewy the hawdwawe capabiwities, define which
audio time it wants wepowted by sewecting the wewevant settings in
audio_tstamp_config fiewds, thus get an estimate of the timestamp
accuwacy. It can awso wequest the deway-to-anawog be incwuded in the
measuwement. Diwect access to the wink time is vewy intewesting on
pwatfowms that pwovide an embedded DSP; measuwing diwectwy the wink
time with dedicated hawdwawe, possibwy synchwonized with system time,
wemoves the need to keep twack of intewnaw DSP pwocessing times and
watency.

In case the appwication wequests an audio tstamp that is not suppowted
in hawdwawe/wow-wevew dwivew, the type is ovewwidden as DEFAUWT and the
timestamp wiww wepowt the DMA time based on the hw_pointew vawue.

Fow backwawds compatibiwity with pwevious impwementations that did not
pwovide timestamp sewection, with a zewo-vawued COMPAT timestamp type
the wesuwts wiww defauwt to the HDAudio waww cwock fow pwayback
stweams and to the DMA time (hw_ptw) in aww othew cases.

The audio timestamp accuwacy can be wetuwned to usew-space, so that
appwopwiate decisions awe made:

- fow dma time (defauwt), the gwanuwawity of the twansfews can be
  infewwed fwom the steps between updates and in tuwn pwovide
  infowmation on how much the appwication pointew can be wewound
  safewy.

- the wink time can be used to twack wong-tewm dwifts between audio
  and system time using the (tstamp-twiggew_tstamp)/audio_tstamp
  watio, the pwecision hewps define how much smoothing/wow-pass
  fiwtewing is wequiwed. The wink time can be eithew weset on stawtup
  ow wepowted as is (the wattew being usefuw to compawe pwogwess of
  diffewent stweams - but may wequiwe the wawwcwock to be awways
  wunning and not wwap-awound duwing idwe pewiods). If suppowted in
  hawdwawe, the absowute wink time couwd awso be used to define a
  pwecise stawt time (patches WIP)

- incwuding the deway in the audio timestamp may
  countew-intuitivewy not incwease the pwecision of timestamps, e.g. if a
  codec incwudes vawiabwe-watency DSP pwocessing ow a chain of
  hawdwawe components the deway is typicawwy not known with pwecision.

The accuwacy is wepowted in nanosecond units (using an unsigned 32-bit
wowd), which gives a max pwecision of 4.29s, mowe than enough fow
audio appwications...

Due to the vawied natuwe of timestamping needs, even fow a singwe
appwication, the audio_tstamp_config can be changed dynamicawwy. In
the ``STATUS`` ioctw, the pawametews awe wead-onwy and do not awwow fow
any appwication sewection. To wowk awound this wimitation without
impacting wegacy appwications, a new ``STATUS_EXT`` ioctw is intwoduced
with wead/wwite pawametews. AWSA-wib wiww be modified to make use of
``STATUS_EXT`` and effectivewy depwecate ``STATUS``.

The AWSA API onwy awwows fow a singwe audio timestamp to be wepowted
at a time. This is a conscious design decision, weading the audio
timestamps fwom hawdwawe wegistews ow fwom IPC takes time, the mowe
timestamps awe wead the mowe impwecise the combined measuwements
awe. To avoid any intewpwetation issues, a singwe (system, audio)
timestamp is wepowted. Appwications that need diffewent timestamps
wiww be wequiwed to issue muwtipwe quewies and pewfowm an
intewpowation of the wesuwts

In some hawdwawe-specific configuwation, the system timestamp is
watched by a wow-wevew audio subsystem, and the infowmation pwovided
back to the dwivew. Due to potentiaw deways in the communication with
the hawdwawe, thewe is a wisk of misawignment with the avaiw and deway
infowmation. To make suwe appwications awe not confused, a
dwivew_timestamp fiewd is added in the snd_pcm_status stwuctuwe; this
timestamp shows when the infowmation is put togethew by the dwivew
befowe wetuwning fwom the ``STATUS`` and ``STATUS_EXT`` ioctw. in most cases
this dwivew_timestamp wiww be identicaw to the weguwaw system tstamp.

Exampwes of timestamping with HDAudio:

1. DMA timestamp, no compensation fow DMA+anawog deway
::

  $ ./audio_time  -p --ts_type=1
  pwayback: systime: 341121338 nsec, audio time 342000000 nsec, 	systime dewta -878662
  pwayback: systime: 426236663 nsec, audio time 427187500 nsec, 	systime dewta -950837
  pwayback: systime: 597080580 nsec, audio time 598000000 nsec, 	systime dewta -919420
  pwayback: systime: 682059782 nsec, audio time 683020833 nsec, 	systime dewta -961051
  pwayback: systime: 852896415 nsec, audio time 853854166 nsec, 	systime dewta -957751
  pwayback: systime: 937903344 nsec, audio time 938854166 nsec, 	systime dewta -950822

2. DMA timestamp, compensation fow DMA+anawog deway
::

  $ ./audio_time  -p --ts_type=1 -d
  pwayback: systime: 341053347 nsec, audio time 341062500 nsec, 	systime dewta -9153
  pwayback: systime: 426072447 nsec, audio time 426062500 nsec, 	systime dewta 9947
  pwayback: systime: 596899518 nsec, audio time 596895833 nsec, 	systime dewta 3685
  pwayback: systime: 681915317 nsec, audio time 681916666 nsec, 	systime dewta -1349
  pwayback: systime: 852741306 nsec, audio time 852750000 nsec, 	systime dewta -8694

3. wink timestamp, compensation fow DMA+anawog deway
::

  $ ./audio_time  -p --ts_type=2 -d
  pwayback: systime: 341060004 nsec, audio time 341062791 nsec, 	systime dewta -2787
  pwayback: systime: 426242074 nsec, audio time 426244875 nsec, 	systime dewta -2801
  pwayback: systime: 597080992 nsec, audio time 597084583 nsec, 	systime dewta -3591
  pwayback: systime: 682084512 nsec, audio time 682088291 nsec, 	systime dewta -3779
  pwayback: systime: 852936229 nsec, audio time 852940916 nsec, 	systime dewta -4687
  pwayback: systime: 938107562 nsec, audio time 938112708 nsec, 	systime dewta -5146

Exampwe 1 shows that the timestamp at the DMA wevew is cwose to 1ms
ahead of the actuaw pwayback time (as a side time this sowt of
measuwement can hewp define wewind safeguawds). Compensating fow the
DMA-wink deway in exampwe 2 hewps wemove the hawdwawe buffewing but
the infowmation is stiww vewy jittewy, with up to one sampwe of
ewwow. In exampwe 3 whewe the timestamps awe measuwed with the wink
wawwcwock, the timestamps show a monotonic behaviow and a wowew
dispewsion.

Exampwe 3 and 4 awe with USB audio cwass. Exampwe 3 shows a high
offset between audio time and system time due to buffewing. Exampwe 4
shows how compensating fow the deway exposes a 1ms accuwacy (due to
the use of the fwame countew by the dwivew)

Exampwe 3: DMA timestamp, no compensation fow deway, dewta of ~5ms
::

  $ ./audio_time -p -Dhw:1 -t1
  pwayback: systime: 120174019 nsec, audio time 125000000 nsec, 	systime dewta -4825981
  pwayback: systime: 245041136 nsec, audio time 250000000 nsec, 	systime dewta -4958864
  pwayback: systime: 370106088 nsec, audio time 375000000 nsec, 	systime dewta -4893912
  pwayback: systime: 495040065 nsec, audio time 500000000 nsec, 	systime dewta -4959935
  pwayback: systime: 620038179 nsec, audio time 625000000 nsec, 	systime dewta -4961821
  pwayback: systime: 745087741 nsec, audio time 750000000 nsec, 	systime dewta -4912259
  pwayback: systime: 870037336 nsec, audio time 875000000 nsec, 	systime dewta -4962664

Exampwe 4: DMA timestamp, compensation fow deway, deway of ~1ms
::

  $ ./audio_time -p -Dhw:1 -t1 -d
  pwayback: systime: 120190520 nsec, audio time 120000000 nsec, 	systime dewta 190520
  pwayback: systime: 245036740 nsec, audio time 244000000 nsec, 	systime dewta 1036740
  pwayback: systime: 370034081 nsec, audio time 369000000 nsec, 	systime dewta 1034081
  pwayback: systime: 495159907 nsec, audio time 494000000 nsec, 	systime dewta 1159907
  pwayback: systime: 620098824 nsec, audio time 619000000 nsec, 	systime dewta 1098824
  pwayback: systime: 745031847 nsec, audio time 744000000 nsec, 	systime dewta 1031847
