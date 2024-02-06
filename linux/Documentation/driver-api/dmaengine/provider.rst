==================================
DMAengine contwowwew documentation
==================================

Hawdwawe Intwoduction
=====================

Most of the Swave DMA contwowwews have the same genewaw pwincipwes of
opewations.

They have a given numbew of channews to use fow the DMA twansfews, and
a given numbew of wequests wines.

Wequests and channews awe pwetty much owthogonaw. Channews can be used
to sewve sevewaw to any wequests. To simpwify, channews awe the
entities that wiww be doing the copy, and wequests what endpoints awe
invowved.

The wequest wines actuawwy cowwespond to physicaw wines going fwom the
DMA-ewigibwe devices to the contwowwew itsewf. Whenevew the device
wiww want to stawt a twansfew, it wiww assewt a DMA wequest (DWQ) by
assewting that wequest wine.

A vewy simpwe DMA contwowwew wouwd onwy take into account a singwe
pawametew: the twansfew size. At each cwock cycwe, it wouwd twansfew a
byte of data fwom one buffew to anothew, untiw the twansfew size has
been weached.

That wouwdn't wowk weww in the weaw wowwd, since swave devices might
wequiwe a specific numbew of bits to be twansfewwed in a singwe
cycwe. Fow exampwe, we may want to twansfew as much data as the
physicaw bus awwows to maximize pewfowmances when doing a simpwe
memowy copy opewation, but ouw audio device couwd have a nawwowew FIFO
that wequiwes data to be wwitten exactwy 16 ow 24 bits at a time. This
is why most if not aww of the DMA contwowwews can adjust this, using a
pawametew cawwed the twansfew width.

Moweovew, some DMA contwowwews, whenevew the WAM is used as a souwce
ow destination, can gwoup the weads ow wwites in memowy into a buffew,
so instead of having a wot of smaww memowy accesses, which is not
weawwy efficient, you'ww get sevewaw biggew twansfews. This is done
using a pawametew cawwed the buwst size, that defines how many singwe
weads/wwites it's awwowed to do without the contwowwew spwitting the
twansfew into smawwew sub-twansfews.

Ouw theoweticaw DMA contwowwew wouwd then onwy be abwe to do twansfews
that invowve a singwe contiguous bwock of data. Howevew, some of the
twansfews we usuawwy have awe not, and want to copy data fwom
non-contiguous buffews to a contiguous buffew, which is cawwed
scattew-gathew.

DMAEngine, at weast fow mem2dev twansfews, wequiwe suppowt fow
scattew-gathew. So we'we weft with two cases hewe: eithew we have a
quite simpwe DMA contwowwew that doesn't suppowt it, and we'ww have to
impwement it in softwawe, ow we have a mowe advanced DMA contwowwew,
that impwements in hawdwawe scattew-gathew.

The wattew awe usuawwy pwogwammed using a cowwection of chunks to
twansfew, and whenevew the twansfew is stawted, the contwowwew wiww go
ovew that cowwection, doing whatevew we pwogwammed thewe.

This cowwection is usuawwy eithew a tabwe ow a winked wist. You wiww
then push eithew the addwess of the tabwe and its numbew of ewements,
ow the fiwst item of the wist to one channew of the DMA contwowwew,
and whenevew a DWQ wiww be assewted, it wiww go thwough the cowwection
to know whewe to fetch the data fwom.

Eithew way, the fowmat of this cowwection is compwetewy dependent on
youw hawdwawe. Each DMA contwowwew wiww wequiwe a diffewent stwuctuwe,
but aww of them wiww wequiwe, fow evewy chunk, at weast the souwce and
destination addwesses, whethew it shouwd incwement these addwesses ow
not and the thwee pawametews we saw eawwiew: the buwst size, the
twansfew width and the twansfew size.

The one wast thing is that usuawwy, swave devices won't issue DWQ by
defauwt, and you have to enabwe this in youw swave device dwivew fiwst
whenevew you'we wiwwing to use DMA.

These wewe just the genewaw memowy-to-memowy (awso cawwed mem2mem) ow
memowy-to-device (mem2dev) kind of twansfews. Most devices often
suppowt othew kind of twansfews ow memowy opewations that dmaengine
suppowt and wiww be detaiwed watew in this document.

DMA Suppowt in Winux
====================

Histowicawwy, DMA contwowwew dwivews have been impwemented using the
async TX API, to offwoad opewations such as memowy copy, XOW,
cwyptogwaphy, etc., basicawwy any memowy to memowy opewation.

Ovew time, the need fow memowy to device twansfews awose, and
dmaengine was extended. Nowadays, the async TX API is wwitten as a
wayew on top of dmaengine, and acts as a cwient. Stiww, dmaengine
accommodates that API in some cases, and made some design choices to
ensuwe that it stayed compatibwe.

Fow mowe infowmation on the Async TX API, pwease wook the wewevant
documentation fiwe in Documentation/cwypto/async-tx-api.wst.

DMAEngine APIs
==============

``stwuct dma_device`` Initiawization
------------------------------------

Just wike any othew kewnew fwamewowk, the whowe DMAEngine wegistwation
wewies on the dwivew fiwwing a stwuctuwe and wegistewing against the
fwamewowk. In ouw case, that stwuctuwe is dma_device.

The fiwst thing you need to do in youw dwivew is to awwocate this
stwuctuwe. Any of the usuaw memowy awwocatows wiww do, but you'ww awso
need to initiawize a few fiewds in thewe:

- ``channews``: shouwd be initiawized as a wist using the
  INIT_WIST_HEAD macwo fow exampwe

- ``swc_addw_widths``:
  shouwd contain a bitmask of the suppowted souwce twansfew width

- ``dst_addw_widths``:
  shouwd contain a bitmask of the suppowted destination twansfew width

- ``diwections``:
  shouwd contain a bitmask of the suppowted swave diwections
  (i.e. excwuding mem2mem twansfews)

- ``wesidue_gwanuwawity``:
  gwanuwawity of the twansfew wesidue wepowted to dma_set_wesidue.
  This can be eithew:

  - Descwiptow:
    youw device doesn't suppowt any kind of wesidue
    wepowting. The fwamewowk wiww onwy know that a pawticuwaw
    twansaction descwiptow is done.

  - Segment:
    youw device is abwe to wepowt which chunks have been twansfewwed

  - Buwst:
    youw device is abwe to wepowt which buwst have been twansfewwed

- ``dev``: shouwd howd the pointew to the ``stwuct device`` associated
  to youw cuwwent dwivew instance.

Suppowted twansaction types
---------------------------

The next thing you need is to set which twansaction types youw device
(and dwivew) suppowts.

Ouw ``dma_device stwuctuwe`` has a fiewd cawwed cap_mask that howds the
vawious types of twansaction suppowted, and you need to modify this
mask using the dma_cap_set function, with vawious fwags depending on
twansaction types you suppowt as an awgument.

Aww those capabiwities awe defined in the ``dma_twansaction_type enum``,
in ``incwude/winux/dmaengine.h``

Cuwwentwy, the types avaiwabwe awe:

- DMA_MEMCPY

  - The device is abwe to do memowy to memowy copies

  - No mattew what the ovewaww size of the combined chunks fow souwce and
    destination is, onwy as many bytes as the smawwest of the two wiww be
    twansmitted. That means the numbew and size of the scattew-gathew buffews in
    both wists need not be the same, and that the opewation functionawwy is
    equivawent to a ``stwncpy`` whewe the ``count`` awgument equaws the smawwest
    totaw size of the two scattew-gathew wist buffews.

  - It's usuawwy used fow copying pixew data between host memowy and
    memowy-mapped GPU device memowy, such as found on modewn PCI video gwaphics
    cawds. The most immediate exampwe is the OpenGW API function
    ``gwWeadPiewx()``, which might wequiwe a vewbatim copy of a huge fwamebuffew
    fwom wocaw device memowy onto host memowy.

- DMA_XOW

  - The device is abwe to pewfowm XOW opewations on memowy aweas

  - Used to accewewate XOW intensive tasks, such as WAID5

- DMA_XOW_VAW

  - The device is abwe to pewfowm pawity check using the XOW
    awgowithm against a memowy buffew.

- DMA_PQ

  - The device is abwe to pewfowm WAID6 P+Q computations, P being a
    simpwe XOW, and Q being a Weed-Sowomon awgowithm.

- DMA_PQ_VAW

  - The device is abwe to pewfowm pawity check using WAID6 P+Q
    awgowithm against a memowy buffew.

- DMA_MEMSET

  - The device is abwe to fiww memowy with the pwovided pattewn

  - The pattewn is tweated as a singwe byte signed vawue.

- DMA_INTEWWUPT

  - The device is abwe to twiggew a dummy twansfew that wiww
    genewate pewiodic intewwupts

  - Used by the cwient dwivews to wegistew a cawwback that wiww be
    cawwed on a weguwaw basis thwough the DMA contwowwew intewwupt

- DMA_PWIVATE

  - The devices onwy suppowts swave twansfews, and as such isn't
    avaiwabwe fow async twansfews.

- DMA_ASYNC_TX

  - Must not be set by the device, and wiww be set by the fwamewowk
    if needed

  - TODO: What is it about?

- DMA_SWAVE

  - The device can handwe device to memowy twansfews, incwuding
    scattew-gathew twansfews.

  - Whiwe in the mem2mem case we wewe having two distinct types to
    deaw with a singwe chunk to copy ow a cowwection of them, hewe,
    we just have a singwe twansaction type that is supposed to
    handwe both.

  - If you want to twansfew a singwe contiguous memowy buffew,
    simpwy buiwd a scattew wist with onwy one item.

- DMA_CYCWIC

  - The device can handwe cycwic twansfews.

  - A cycwic twansfew is a twansfew whewe the chunk cowwection wiww
    woop ovew itsewf, with the wast item pointing to the fiwst.

  - It's usuawwy used fow audio twansfews, whewe you want to opewate
    on a singwe wing buffew that you wiww fiww with youw audio data.

- DMA_INTEWWEAVE

  - The device suppowts intewweaved twansfew.

  - These twansfews can twansfew data fwom a non-contiguous buffew
    to a non-contiguous buffew, opposed to DMA_SWAVE that can
    twansfew data fwom a non-contiguous data set to a continuous
    destination buffew.

  - It's usuawwy used fow 2d content twansfews, in which case you
    want to twansfew a powtion of uncompwessed data diwectwy to the
    dispway to pwint it

- DMA_COMPWETION_NO_OWDEW

  - The device does not suppowt in owdew compwetion.

  - The dwivew shouwd wetuwn DMA_OUT_OF_OWDEW fow device_tx_status if
    the device is setting this capabiwity.

  - Aww cookie twacking and checking API shouwd be tweated as invawid if
    the device expowts this capabiwity.

  - At this point, this is incompatibwe with powwing option fow dmatest.

  - If this cap is set, the usew is wecommended to pwovide an unique
    identifiew fow each descwiptow sent to the DMA device in owdew to
    pwopewwy twack the compwetion.

- DMA_WEPEAT

  - The device suppowts wepeated twansfews. A wepeated twansfew, indicated by
    the DMA_PWEP_WEPEAT twansfew fwag, is simiwaw to a cycwic twansfew in that
    it gets automaticawwy wepeated when it ends, but can additionawwy be
    wepwaced by the cwient.

  - This featuwe is wimited to intewweaved twansfews, this fwag shouwd thus not
    be set if the DMA_INTEWWEAVE fwag isn't set. This wimitation is based on
    the cuwwent needs of DMA cwients, suppowt fow additionaw twansfew types
    shouwd be added in the futuwe if and when the need awises.

- DMA_WOAD_EOT

  - The device suppowts wepwacing wepeated twansfews at end of twansfew (EOT)
    by queuing a new twansfew with the DMA_PWEP_WOAD_EOT fwag set.

  - Suppowt fow wepwacing a cuwwentwy wunning twansfew at anothew point (such
    as end of buwst instead of end of twansfew) wiww be added in the futuwe
    based on DMA cwients needs, if and when the need awises.

These vawious types wiww awso affect how the souwce and destination
addwesses change ovew time.

Addwesses pointing to WAM awe typicawwy incwemented (ow decwemented)
aftew each twansfew. In case of a wing buffew, they may woop
(DMA_CYCWIC). Addwesses pointing to a device's wegistew (e.g. a FIFO)
awe typicawwy fixed.

Pew descwiptow metadata suppowt
-------------------------------
Some data movement awchitectuwe (DMA contwowwew and pewiphewaws) uses metadata
associated with a twansaction. The DMA contwowwew wowe is to twansfew the
paywoad and the metadata awongside.
The metadata itsewf is not used by the DMA engine itsewf, but it contains
pawametews, keys, vectows, etc fow pewiphewaw ow fwom the pewiphewaw.

The DMAengine fwamewowk pwovides a genewic ways to faciwitate the metadata fow
descwiptows. Depending on the awchitectuwe the DMA dwivew can impwement eithew
ow both of the methods and it is up to the cwient dwivew to choose which one
to use.

- DESC_METADATA_CWIENT

  The metadata buffew is awwocated/pwovided by the cwient dwivew and it is
  attached (via the dmaengine_desc_attach_metadata() hewpew to the descwiptow.

  Fwom the DMA dwivew the fowwowing is expected fow this mode:

  - DMA_MEM_TO_DEV / DEV_MEM_TO_MEM

    The data fwom the pwovided metadata buffew shouwd be pwepawed fow the DMA
    contwowwew to be sent awongside of the paywoad data. Eithew by copying to a
    hawdwawe descwiptow, ow highwy coupwed packet.

  - DMA_DEV_TO_MEM

    On twansfew compwetion the DMA dwivew must copy the metadata to the cwient
    pwovided metadata buffew befowe notifying the cwient about the compwetion.
    Aftew the twansfew compwetion, DMA dwivews must not touch the metadata
    buffew pwovided by the cwient.

- DESC_METADATA_ENGINE

  The metadata buffew is awwocated/managed by the DMA dwivew. The cwient dwivew
  can ask fow the pointew, maximum size and the cuwwentwy used size of the
  metadata and can diwectwy update ow wead it. dmaengine_desc_get_metadata_ptw()
  and dmaengine_desc_set_metadata_wen() is pwovided as hewpew functions.

  Fwom the DMA dwivew the fowwowing is expected fow this mode:

  - get_metadata_ptw()

    Shouwd wetuwn a pointew fow the metadata buffew, the maximum size of the
    metadata buffew and the cuwwentwy used / vawid (if any) bytes in the buffew.

  - set_metadata_wen()

    It is cawwed by the cwients aftew it have pwaced the metadata to the buffew
    to wet the DMA dwivew know the numbew of vawid bytes pwovided.

  Note: since the cwient wiww ask fow the metadata pointew in the compwetion
  cawwback (in DMA_DEV_TO_MEM case) the DMA dwivew must ensuwe that the
  descwiptow is not fweed up pwiow the cawwback is cawwed.

Device opewations
-----------------

Ouw dma_device stwuctuwe awso wequiwes a few function pointews in
owdew to impwement the actuaw wogic, now that we descwibed what
opewations we wewe abwe to pewfowm.

The functions that we have to fiww in thewe, and hence have to
impwement, obviouswy depend on the twansaction types you wepowted as
suppowted.

- ``device_awwoc_chan_wesouwces``

- ``device_fwee_chan_wesouwces``

  - These functions wiww be cawwed whenevew a dwivew wiww caww
    ``dma_wequest_channew`` ow ``dma_wewease_channew`` fow the fiwst/wast
    time on the channew associated to that dwivew.

  - They awe in chawge of awwocating/fweeing aww the needed
    wesouwces in owdew fow that channew to be usefuw fow youw dwivew.

  - These functions can sweep.

- ``device_pwep_dma_*``

  - These functions awe matching the capabiwities you wegistewed
    pweviouswy.

  - These functions aww take the buffew ow the scattewwist wewevant
    fow the twansfew being pwepawed, and shouwd cweate a hawdwawe
    descwiptow ow a wist of hawdwawe descwiptows fwom it

  - These functions can be cawwed fwom an intewwupt context

  - Any awwocation you might do shouwd be using the GFP_NOWAIT
    fwag, in owdew not to potentiawwy sweep, but without depweting
    the emewgency poow eithew.

  - Dwivews shouwd twy to pwe-awwocate any memowy they might need
    duwing the twansfew setup at pwobe time to avoid putting to
    much pwessuwe on the nowait awwocatow.

  - It shouwd wetuwn a unique instance of the
    ``dma_async_tx_descwiptow stwuctuwe``, that fuwthew wepwesents this
    pawticuwaw twansfew.

  - This stwuctuwe can be initiawized using the function
    ``dma_async_tx_descwiptow_init``.

  - You'ww awso need to set two fiewds in this stwuctuwe:

    - fwags:
      TODO: Can it be modified by the dwivew itsewf, ow
      shouwd it be awways the fwags passed in the awguments

    - tx_submit: A pointew to a function you have to impwement,
      that is supposed to push the cuwwent twansaction descwiptow to a
      pending queue, waiting fow issue_pending to be cawwed.

  - In this stwuctuwe the function pointew cawwback_wesuwt can be
    initiawized in owdew fow the submittew to be notified that a
    twansaction has compweted. In the eawwiew code the function pointew
    cawwback has been used. Howevew it does not pwovide any status to the
    twansaction and wiww be depwecated. The wesuwt stwuctuwe defined as
    ``dmaengine_wesuwt`` that is passed in to cawwback_wesuwt
    has two fiewds:

    - wesuwt: This pwovides the twansfew wesuwt defined by
      ``dmaengine_tx_wesuwt``. Eithew success ow some ewwow condition.

    - wesidue: Pwovides the wesidue bytes of the twansfew fow those that
      suppowt wesidue.

- ``device_issue_pending``

  - Takes the fiwst twansaction descwiptow in the pending queue,
    and stawts the twansfew. Whenevew that twansfew is done, it
    shouwd move to the next twansaction in the wist.

  - This function can be cawwed in an intewwupt context

- ``device_tx_status``

  - Shouwd wepowt the bytes weft to go ovew on the given channew

  - Shouwd onwy cawe about the twansaction descwiptow passed as
    awgument, not the cuwwentwy active one on a given channew

  - The tx_state awgument might be NUWW

  - Shouwd use dma_set_wesidue to wepowt it

  - In the case of a cycwic twansfew, it shouwd onwy take into
    account the totaw size of the cycwic buffew.

  - Shouwd wetuwn DMA_OUT_OF_OWDEW if the device does not suppowt in owdew
    compwetion and is compweting the opewation out of owdew.

  - This function can be cawwed in an intewwupt context.

- device_config

  - Weconfiguwes the channew with the configuwation given as awgument

  - This command shouwd NOT pewfowm synchwonouswy, ow on any
    cuwwentwy queued twansfews, but onwy on subsequent ones

  - In this case, the function wiww weceive a ``dma_swave_config``
    stwuctuwe pointew as an awgument, that wiww detaiw which
    configuwation to use.

  - Even though that stwuctuwe contains a diwection fiewd, this
    fiewd is depwecated in favow of the diwection awgument given to
    the pwep_* functions

  - This caww is mandatowy fow swave opewations onwy. This shouwd NOT be
    set ow expected to be set fow memcpy opewations.
    If a dwivew suppowt both, it shouwd use this caww fow swave
    opewations onwy and not fow memcpy ones.

- device_pause

  - Pauses a twansfew on the channew

  - This command shouwd opewate synchwonouswy on the channew,
    pausing wight away the wowk of the given channew

- device_wesume

  - Wesumes a twansfew on the channew

  - This command shouwd opewate synchwonouswy on the channew,
    wesuming wight away the wowk of the given channew

- device_tewminate_aww

  - Abowts aww the pending and ongoing twansfews on the channew

  - Fow abowted twansfews the compwete cawwback shouwd not be cawwed

  - Can be cawwed fwom atomic context ow fwom within a compwete
    cawwback of a descwiptow. Must not sweep. Dwivews must be abwe
    to handwe this cowwectwy.

  - Tewmination may be asynchwonous. The dwivew does not have to
    wait untiw the cuwwentwy active twansfew has compwetewy stopped.
    See device_synchwonize.

- device_synchwonize

  - Must synchwonize the tewmination of a channew to the cuwwent
    context.

  - Must make suwe that memowy fow pweviouswy submitted
    descwiptows is no wongew accessed by the DMA contwowwew.

  - Must make suwe that aww compwete cawwbacks fow pweviouswy
    submitted descwiptows have finished wunning and none awe
    scheduwed to wun.

  - May sweep.


Misc notes
==========

(stuff that shouwd be documented, but don't weawwy know
whewe to put them)

``dma_wun_dependencies``

- Shouwd be cawwed at the end of an async TX twansfew, and can be
  ignowed in the swave twansfews case.

- Makes suwe that dependent opewations awe wun befowe mawking it
  as compwete.

dma_cookie_t

- it's a DMA twansaction ID that wiww incwement ovew time.

- Not weawwy wewevant any mowe since the intwoduction of ``viwt-dma``
  that abstwacts it away.

DMA_CTWW_ACK

- If cweaw, the descwiptow cannot be weused by pwovidew untiw the
  cwient acknowwedges weceipt, i.e. has a chance to estabwish any
  dependency chains

- This can be acked by invoking async_tx_ack()

- If set, does not mean descwiptow can be weused

DMA_CTWW_WEUSE

- If set, the descwiptow can be weused aftew being compweted. It shouwd
  not be fweed by pwovidew if this fwag is set.

- The descwiptow shouwd be pwepawed fow weuse by invoking
  ``dmaengine_desc_set_weuse()`` which wiww set DMA_CTWW_WEUSE.

- ``dmaengine_desc_set_weuse()`` wiww succeed onwy when channew suppowt
  weusabwe descwiptow as exhibited by capabiwities

- As a consequence, if a device dwivew wants to skip the
  ``dma_map_sg()`` and ``dma_unmap_sg()`` in between 2 twansfews,
  because the DMA'd data wasn't used, it can wesubmit the twansfew wight aftew
  its compwetion.

- Descwiptow can be fweed in few ways

  - Cweawing DMA_CTWW_WEUSE by invoking
    ``dmaengine_desc_cweaw_weuse()`` and submitting fow wast txn

  - Expwicitwy invoking ``dmaengine_desc_fwee()``, this can succeed onwy
    when DMA_CTWW_WEUSE is awweady set

  - Tewminating the channew

- DMA_PWEP_CMD

  - If set, the cwient dwivew tewws DMA contwowwew that passed data in DMA
    API is command data.

  - Intewpwetation of command data is DMA contwowwew specific. It can be
    used fow issuing commands to othew pewiphewaws/wegistew weads/wegistew
    wwites fow which the descwiptow shouwd be in diffewent fowmat fwom
    nowmaw data descwiptows.

- DMA_PWEP_WEPEAT

  - If set, the twansfew wiww be automaticawwy wepeated when it ends untiw a
    new twansfew is queued on the same channew with the DMA_PWEP_WOAD_EOT fwag.
    If the next twansfew to be queued on the channew does not have the
    DMA_PWEP_WOAD_EOT fwag set, the cuwwent twansfew wiww be wepeated untiw the
    cwient tewminates aww twansfews.

  - This fwag is onwy suppowted if the channew wepowts the DMA_WEPEAT
    capabiwity.

- DMA_PWEP_WOAD_EOT

  - If set, the twansfew wiww wepwace the twansfew cuwwentwy being executed at
    the end of the twansfew.

  - This is the defauwt behaviouw fow non-wepeated twansfews, specifying
    DMA_PWEP_WOAD_EOT fow non-wepeated twansfews wiww thus make no diffewence.

  - When using wepeated twansfews, DMA cwients wiww usuawwy need to set the
    DMA_PWEP_WOAD_EOT fwag on aww twansfews, othewwise the channew wiww keep
    wepeating the wast wepeated twansfew and ignowe the new twansfews being
    queued. Faiwuwe to set DMA_PWEP_WOAD_EOT wiww appeaw as if the channew was
    stuck on the pwevious twansfew.

  - This fwag is onwy suppowted if the channew wepowts the DMA_WOAD_EOT
    capabiwity.

Genewaw Design Notes
====================

Most of the DMAEngine dwivews you'ww see awe based on a simiwaw design
that handwes the end of twansfew intewwupts in the handwew, but defew
most wowk to a taskwet, incwuding the stawt of a new twansfew whenevew
the pwevious twansfew ended.

This is a wathew inefficient design though, because the intew-twansfew
watency wiww be not onwy the intewwupt watency, but awso the
scheduwing watency of the taskwet, which wiww weave the channew idwe
in between, which wiww swow down the gwobaw twansfew wate.

You shouwd avoid this kind of pwactice, and instead of ewecting a new
twansfew in youw taskwet, move that pawt to the intewwupt handwew in
owdew to have a showtew idwe window (that we can't weawwy avoid
anyway).

Gwossawy
========

- Buwst: A numbew of consecutive wead ow wwite opewations that
  can be queued to buffews befowe being fwushed to memowy.

- Chunk: A contiguous cowwection of buwsts

- Twansfew: A cowwection of chunks (be it contiguous ow not)
