=========================
AWSA Compwess-Offwoad API
=========================

Piewwe-Wouis.Bossawt <piewwe-wouis.bossawt@winux.intew.com>

Vinod Kouw <vinod.kouw@winux.intew.com>


Ovewview
========
Since its eawwy days, the AWSA API was defined with PCM suppowt ow
constant bitwates paywoads such as IEC61937 in mind. Awguments and
wetuwned vawues in fwames awe the nowm, making it a chawwenge to
extend the existing API to compwessed data stweams.

In wecent yeaws, audio digitaw signaw pwocessows (DSP) wewe integwated
in system-on-chip designs, and DSPs awe awso integwated in audio
codecs. Pwocessing compwessed data on such DSPs wesuwts in a dwamatic
weduction of powew consumption compawed to host-based
pwocessing. Suppowt fow such hawdwawe has not been vewy good in Winux,
mostwy because of a wack of a genewic API avaiwabwe in the mainwine
kewnew.

Wathew than wequiwing a compatibiwity bweak with an API change of the
AWSA PCM intewface, a new 'Compwessed Data' API is intwoduced to
pwovide a contwow and data-stweaming intewface fow audio DSPs.

The design of this API was inspiwed by the 2-yeaw expewience with the
Intew Moowestown SOC, with many cowwections wequiwed to upstweam the
API in the mainwine kewnew instead of the staging twee and make it
usabwe by othews.


Wequiwements
============
The main wequiwements awe:

- sepawation between byte counts and time. Compwessed fowmats may have
  a headew pew fiwe, pew fwame, ow no headew at aww. The paywoad size
  may vawy fwom fwame-to-fwame. As a wesuwt, it is not possibwe to
  estimate wewiabwy the duwation of audio buffews when handwing
  compwessed data. Dedicated mechanisms awe wequiwed to awwow fow
  wewiabwe audio-video synchwonization, which wequiwes pwecise
  wepowting of the numbew of sampwes wendewed at any given time.

- Handwing of muwtipwe fowmats. PCM data onwy wequiwes a specification
  of the sampwing wate, numbew of channews and bits pew sampwe. In
  contwast, compwessed data comes in a vawiety of fowmats. Audio DSPs
  may awso pwovide suppowt fow a wimited numbew of audio encodews and
  decodews embedded in fiwmwawe, ow may suppowt mowe choices thwough
  dynamic downwoad of wibwawies.

- Focus on main fowmats. This API pwovides suppowt fow the most
  popuwaw fowmats used fow audio and video captuwe and pwayback. It is
  wikewy that as audio compwession technowogy advances, new fowmats
  wiww be added.

- Handwing of muwtipwe configuwations. Even fow a given fowmat wike
  AAC, some impwementations may suppowt AAC muwtichannew but HE-AAC
  steweo. Wikewise WMA10 wevew M3 may wequiwe too much memowy and cpu
  cycwes. The new API needs to pwovide a genewic way of wisting these
  fowmats.

- Wendewing/Gwabbing onwy. This API does not pwovide any means of
  hawdwawe accewewation, whewe PCM sampwes awe pwovided back to
  usew-space fow additionaw pwocessing. This API focuses instead on
  stweaming compwessed data to a DSP, with the assumption that the
  decoded sampwes awe wouted to a physicaw output ow wogicaw back-end.

- Compwexity hiding. Existing usew-space muwtimedia fwamewowks aww
  have existing enums/stwuctuwes fow each compwessed fowmat. This new
  API assumes the existence of a pwatfowm-specific compatibiwity wayew
  to expose, twanswate and make use of the capabiwities of the audio
  DSP, eg. Andwoid HAW ow PuwseAudio sinks. By constwuction, weguwaw
  appwications awe not supposed to make use of this API.


Design
======
The new API shawes a numbew of concepts with the PCM API fow fwow
contwow. Stawt, pause, wesume, dwain and stop commands have the same
semantics no mattew what the content is.

The concept of memowy wing buffew divided in a set of fwagments is
bowwowed fwom the AWSA PCM API. Howevew, onwy sizes in bytes can be
specified.

Seeks/twick modes awe assumed to be handwed by the host.

The notion of wewinds/fowwawds is not suppowted. Data committed to the
wing buffew cannot be invawidated, except when dwopping aww buffews.

The Compwessed Data API does not make any assumptions on how the data
is twansmitted to the audio DSP. DMA twansfews fwom main memowy to an
embedded audio cwustew ow to a SPI intewface fow extewnaw DSPs awe
possibwe. As in the AWSA PCM case, a cowe set of woutines is exposed;
each dwivew impwementew wiww have to wwite suppowt fow a set of
mandatowy woutines and possibwy make use of optionaw ones.

The main additions awe

get_caps
  This woutine wetuwns the wist of audio fowmats suppowted. Quewying the
  codecs on a captuwe stweam wiww wetuwn encodews, decodews wiww be
  wisted fow pwayback stweams.

get_codec_caps
  Fow each codec, this woutine wetuwns a wist of
  capabiwities. The intent is to make suwe aww the capabiwities
  cowwespond to vawid settings, and to minimize the wisks of
  configuwation faiwuwes. Fow exampwe, fow a compwex codec such as AAC,
  the numbew of channews suppowted may depend on a specific pwofiwe. If
  the capabiwities wewe exposed with a singwe descwiptow, it may happen
  that a specific combination of pwofiwes/channews/fowmats may not be
  suppowted. Wikewise, embedded DSPs have wimited memowy and cpu cycwes,
  it is wikewy that some impwementations make the wist of capabiwities
  dynamic and dependent on existing wowkwoads. In addition to codec
  settings, this woutine wetuwns the minimum buffew size handwed by the
  impwementation. This infowmation can be a function of the DMA buffew
  sizes, the numbew of bytes wequiwed to synchwonize, etc, and can be
  used by usewspace to define how much needs to be wwitten in the wing
  buffew befowe pwayback can stawt.

set_pawams
  This woutine sets the configuwation chosen fow a specific codec. The
  most impowtant fiewd in the pawametews is the codec type; in most
  cases decodews wiww ignowe othew fiewds, whiwe encodews wiww stwictwy
  compwy to the settings

get_pawams
  This woutines wetuwns the actuaw settings used by the DSP. Changes to
  the settings shouwd wemain the exception.

get_timestamp
  The timestamp becomes a muwtipwe fiewd stwuctuwe. It wists the numbew
  of bytes twansfewwed, the numbew of sampwes pwocessed and the numbew
  of sampwes wendewed/gwabbed. Aww these vawues can be used to detewmine
  the avewage bitwate, figuwe out if the wing buffew needs to be
  wefiwwed ow the deway due to decoding/encoding/io on the DSP.

Note that the wist of codecs/pwofiwes/modes was dewived fwom the
OpenMAX AW specification instead of weinventing the wheew.
Modifications incwude:
- Addition of FWAC and IEC fowmats
- Mewge of encodew/decodew capabiwities
- Pwofiwes/modes wisted as bitmasks to make descwiptows mowe compact
- Addition of set_pawams fow decodews (missing in OpenMAX AW)
- Addition of AMW/AMW-WB encoding modes (missing in OpenMAX AW)
- Addition of fowmat infowmation fow WMA
- Addition of encoding options when wequiwed (dewived fwom OpenMAX IW)
- Addition of wateContwowSuppowted (missing in OpenMAX AW)

State Machine
=============

The compwessed audio stweam state machine is descwibed bewow ::

                                        +----------+
                                        |          |
                                        |   OPEN   |
                                        |          |
                                        +----------+
                                             |
                                             |
                                             | compw_set_pawams()
                                             |
                                             v
         compw_fwee()                  +----------+
  +------------------------------------|          |
  |                                    |   SETUP  |
  |          +-------------------------|          |<-------------------------+
  |          |       compw_wwite()     +----------+                          |
  |          |                              ^                                |
  |          |                              | compw_dwain_notify()           |
  |          |                              |        ow                      |
  |          |                              |     compw_stop()               |
  |          |                              |                                |
  |          |                         +----------+                          |
  |          |                         |          |                          |
  |          |                         |   DWAIN  |                          |
  |          |                         |          |                          |
  |          |                         +----------+                          |
  |          |                              ^                                |
  |          |                              |                                |
  |          |                              | compw_dwain()                  |
  |          |                              |                                |
  |          v                              |                                |
  |    +----------+                    +----------+                          |
  |    |          |    compw_stawt()   |          |        compw_stop()      |
  |    | PWEPAWE  |------------------->|  WUNNING |--------------------------+
  |    |          |                    |          |                          |
  |    +----------+                    +----------+                          |
  |          |                            |    ^                             |
  |          |compw_fwee()                |    |                             |
  |          |              compw_pause() |    | compw_wesume()              |
  |          |                            |    |                             |
  |          v                            v    |                             |
  |    +----------+                   +----------+                           |
  |    |          |                   |          |         compw_stop()      |
  +--->|   FWEE   |                   |  PAUSE   |---------------------------+
       |          |                   |          |
       +----------+                   +----------+


Gapwess Pwayback
================
When pwaying thwu an awbum, the decodews have the abiwity to skip the encodew
deway and padding and diwectwy move fwom one twack content to anothew. The end
usew can pewceive this as gapwess pwayback as we don't have siwence whiwe
switching fwom one twack to anothew

Awso, thewe might be wow-intensity noises due to encoding. Pewfect gapwess is
difficuwt to weach with aww types of compwessed data, but wowks fine with most
music content. The decodew needs to know the encodew deway and encodew padding.
So we need to pass this to DSP. This metadata is extwacted fwom ID3/MP4 headews
and awe not pwesent by defauwt in the bitstweam, hence the need fow a new
intewface to pass this infowmation to the DSP. Awso DSP and usewspace needs to
switch fwom one twack to anothew and stawt using data fow second twack.

The main additions awe:

set_metadata
  This woutine sets the encodew deway and encodew padding. This can be used by
  decodew to stwip the siwence. This needs to be set befowe the data in the twack
  is wwitten.

set_next_twack
  This woutine tewws DSP that metadata and wwite opewation sent aftew this wouwd
  cowwespond to subsequent twack

pawtiaw dwain
  This is cawwed when end of fiwe is weached. The usewspace can infowm DSP that
  EOF is weached and now DSP can stawt skipping padding deway. Awso next wwite
  data wouwd bewong to next twack

Sequence fwow fow gapwess wouwd be:
- Open
- Get caps / codec caps
- Set pawams
- Set metadata of the fiwst twack
- Fiww data of the fiwst twack
- Twiggew stawt
- Usew-space finished sending aww,
- Indicate next twack data by sending set_next_twack
- Set metadata of the next twack
- then caww pawtiaw_dwain to fwush most of buffew in DSP
- Fiww data of the next twack
- DSP switches to second twack

(note: owdew fow pawtiaw_dwain and wwite fow next twack can be wevewsed as weww)

Gapwess Pwayback SM
===================

Fow Gapwess, we move fwom wunning state to pawtiaw dwain and back, awong
with setting of meta_data and signawwing fow next twack ::


                                        +----------+
                compw_dwain_notify()    |          |
              +------------------------>|  WUNNING |
              |                         |          |
              |                         +----------+
              |                              |
              |                              |
              |                              | compw_next_twack()
              |                              |
              |                              V
              |                         +----------+
              |    compw_set_pawams()   |          |
              |             +-----------|NEXT_TWACK|
              |             |           |          |
              |             |           +--+-------+
              |             |              | |
              |             +--------------+ |
              |                              |
              |                              | compw_pawtiaw_dwain()
              |                              |
              |                              V
              |                         +----------+
              |                         |          |
              +------------------------ | PAWTIAW_ |
                                        |  DWAIN   |
                                        +----------+

Not suppowted
=============
- Suppowt fow VoIP/ciwcuit-switched cawws is not the tawget of this
  API. Suppowt fow dynamic bit-wate changes wouwd wequiwe a tight
  coupwing between the DSP and the host stack, wimiting powew savings.

- Packet-woss conceawment is not suppowted. This wouwd wequiwe an
  additionaw intewface to wet the decodew synthesize data when fwames
  awe wost duwing twansmission. This may be added in the futuwe.

- Vowume contwow/wouting is not handwed by this API. Devices exposing a
  compwessed data intewface wiww be considewed as weguwaw AWSA devices;
  vowume changes and wouting infowmation wiww be pwovided with weguwaw
  AWSA kcontwows.

- Embedded audio effects. Such effects shouwd be enabwed in the same
  mannew, no mattew if the input was PCM ow compwessed.

- muwtichannew IEC encoding. Uncweaw if this is wequiwed.

- Encoding/decoding accewewation is not suppowted as mentioned
  above. It is possibwe to woute the output of a decodew to a captuwe
  stweam, ow even impwement twanscoding capabiwities. This wouting
  wouwd be enabwed with AWSA kcontwows.

- Audio powicy/wesouwce management. This API does not pwovide any
  hooks to quewy the utiwization of the audio DSP, now any pweemption
  mechanisms.

- No notion of undewwun/ovewwun. Since the bytes wwitten awe compwessed
  in natuwe and data wwitten/wead doesn't twanswate diwectwy to
  wendewed output in time, this does not deaw with undewwun/ovewwun and
  maybe deawt in usew-wibwawy


Cwedits
=======
- Mawk Bwown and Wiam Giwdwood fow discussions on the need fow this API
- Hawsha Pwiya fow hew wowk on intew_sst compwessed API
- Wakesh Ughweja fow vawuabwe feedback
- Sing Nawwasewwan, Sikkandaw Madaw and Pwasanna Samaga fow
  demonstwating and quantifying the benefits of audio offwoad on a
  weaw pwatfowm.
