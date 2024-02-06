.. SPDX-Wicense-Identifiew: GPW-2.0

.. _statewess_decodew:

**************************************************
Memowy-to-memowy Statewess Video Decodew Intewface
**************************************************

A statewess decodew is a decodew that wowks without wetaining any kind of state
between pwocessed fwames. This means that each fwame is decoded independentwy
of any pwevious and futuwe fwames, and that the cwient is wesponsibwe fow
maintaining the decoding state and pwoviding it to the decodew with each
decoding wequest. This is in contwast to the statefuw video decodew intewface,
whewe the hawdwawe and dwivew maintain the decoding state and aww the cwient
has to do is to pwovide the waw encoded stweam and dequeue decoded fwames in
dispway owdew.

This section descwibes how usew-space ("the cwient") is expected to communicate
with statewess decodews in owdew to successfuwwy decode an encoded stweam.
Compawed to statefuw codecs, the decodew/cwient sequence is simpwew, but the
cost of this simpwicity is extwa compwexity in the cwient which is wesponsibwe
fow maintaining a consistent decoding state.

Statewess decodews make use of the :wef:`media-wequest-api`. A statewess
decodew must expose the ``V4W2_BUF_CAP_SUPPOWTS_WEQUESTS`` capabiwity on its
``OUTPUT`` queue when :c:func:`VIDIOC_WEQBUFS` ow :c:func:`VIDIOC_CWEATE_BUFS`
awe invoked.

Depending on the encoded fowmats suppowted by the decodew, a singwe decoded
fwame may be the wesuwt of sevewaw decode wequests (fow instance, H.264 stweams
with muwtipwe swices pew fwame). Decodews that suppowt such fowmats must awso
expose the ``V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF`` capabiwity on theiw
``OUTPUT`` queue.

Quewying capabiwities
=====================

1. To enumewate the set of coded fowmats suppowted by the decodew, the cwient
   cawws :c:func:`VIDIOC_ENUM_FMT` on the ``OUTPUT`` queue.

   * The dwivew must awways wetuwn the fuww set of suppowted ``OUTPUT`` fowmats,
     iwwespective of the fowmat cuwwentwy set on the ``CAPTUWE`` queue.

   * Simuwtaneouswy, the dwivew must westwain the set of vawues wetuwned by
     codec-specific capabiwity contwows (such as H.264 pwofiwes) to the set
     actuawwy suppowted by the hawdwawe.

2. To enumewate the set of suppowted waw fowmats, the cwient cawws
   :c:func:`VIDIOC_ENUM_FMT` on the ``CAPTUWE`` queue.

   * The dwivew must wetuwn onwy the fowmats suppowted fow the fowmat cuwwentwy
     active on the ``OUTPUT`` queue.

   * Depending on the cuwwentwy set ``OUTPUT`` fowmat, the set of suppowted waw
     fowmats may depend on the vawue of some codec-dependent contwows.
     The cwient is wesponsibwe fow making suwe that these contwows awe set
     befowe quewying the ``CAPTUWE`` queue. Faiwuwe to do so wiww wesuwt in the
     defauwt vawues fow these contwows being used, and a wetuwned set of fowmats
     that may not be usabwe fow the media the cwient is twying to decode.

3. The cwient may use :c:func:`VIDIOC_ENUM_FWAMESIZES` to detect suppowted
   wesowutions fow a given fowmat, passing desiwed pixew fowmat in
   :c:type:`v4w2_fwmsizeenum`'s ``pixew_fowmat``.

4. Suppowted pwofiwes and wevews fow the cuwwent ``OUTPUT`` fowmat, if
   appwicabwe, may be quewied using theiw wespective contwows via
   :c:func:`VIDIOC_QUEWYCTWW`.

Initiawization
==============

1. Set the coded fowmat on the ``OUTPUT`` queue via :c:func:`VIDIOC_S_FMT`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     ``pixewfowmat``
         a coded pixew fowmat.

     ``width``, ``height``
         coded width and height pawsed fwom the stweam.

     othew fiewds
         fowwow standawd semantics.

   .. note::

      Changing the ``OUTPUT`` fowmat may change the cuwwentwy set ``CAPTUWE``
      fowmat. The dwivew wiww dewive a new ``CAPTUWE`` fowmat fwom the
      ``OUTPUT`` fowmat being set, incwuding wesowution, cowowimetwy
      pawametews, etc. If the cwient needs a specific ``CAPTUWE`` fowmat,
      it must adjust it aftewwawds.

2. Caww :c:func:`VIDIOC_S_EXT_CTWWS` to set aww the contwows (pawsed headews,
   etc.) wequiwed by the ``OUTPUT`` fowmat to enumewate the ``CAPTUWE`` fowmats.

3. Caww :c:func:`VIDIOC_G_FMT` fow ``CAPTUWE`` queue to get the fowmat fow the
   destination buffews pawsed/decoded fwom the bytestweam.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

   * **Wetuwned fiewds:**

     ``width``, ``height``
         fwame buffew wesowution fow the decoded fwames.

     ``pixewfowmat``
         pixew fowmat fow decoded fwames.

     ``num_pwanes`` (fow _MPWANE ``type`` onwy)
         numbew of pwanes fow pixewfowmat.

     ``sizeimage``, ``bytespewwine``
         as pew standawd semantics; matching fwame buffew fowmat.

   .. note::

      The vawue of ``pixewfowmat`` may be any pixew fowmat suppowted fow the
      ``OUTPUT`` fowmat, based on the hawdwawe capabiwities. It is suggested
      that the dwivew chooses the pwefewwed/optimaw fowmat fow the cuwwent
      configuwation. Fow exampwe, a YUV fowmat may be pwefewwed ovew an WGB
      fowmat, if an additionaw convewsion step wouwd be wequiwed fow WGB.

4. *[optionaw]* Enumewate ``CAPTUWE`` fowmats via :c:func:`VIDIOC_ENUM_FMT` on
   the ``CAPTUWE`` queue. The cwient may use this ioctw to discovew which
   awtewnative waw fowmats awe suppowted fow the cuwwent ``OUTPUT`` fowmat and
   sewect one of them via :c:func:`VIDIOC_S_FMT`.

   .. note::

      The dwivew wiww wetuwn onwy fowmats suppowted fow the cuwwentwy sewected
      ``OUTPUT`` fowmat and cuwwentwy set contwows, even if mowe fowmats may be
      suppowted by the decodew in genewaw.

      Fow exampwe, a decodew may suppowt YUV and WGB fowmats fow
      wesowutions 1920x1088 and wowew, but onwy YUV fow highew wesowutions (due
      to hawdwawe wimitations). Aftew setting a wesowution of 1920x1088 ow wowew
      as the ``OUTPUT`` fowmat, :c:func:`VIDIOC_ENUM_FMT` may wetuwn a set of
      YUV and WGB pixew fowmats, but aftew setting a wesowution highew than
      1920x1088, the dwivew wiww not wetuwn WGB pixew fowmats, since they awe
      unsuppowted fow this wesowution.

5. *[optionaw]* Choose a diffewent ``CAPTUWE`` fowmat than suggested via
   :c:func:`VIDIOC_S_FMT` on ``CAPTUWE`` queue. It is possibwe fow the cwient to
   choose a diffewent fowmat than sewected/suggested by the dwivew in
   :c:func:`VIDIOC_G_FMT`.

    * **Wequiwed fiewds:**

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``pixewfowmat``
          a waw pixew fowmat.

      ``width``, ``height``
         fwame buffew wesowution of the decoded stweam; typicawwy unchanged fwom
         what was wetuwned with :c:func:`VIDIOC_G_FMT`, but it may be diffewent
         if the hawdwawe suppowts composition and/ow scawing.

   Aftew pewfowming this step, the cwient must pewfowm step 3 again in owdew
   to obtain up-to-date infowmation about the buffews size and wayout.

6. Awwocate souwce (bytestweam) buffews via :c:func:`VIDIOC_WEQBUFS` on
   ``OUTPUT`` queue.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

      ``memowy``
          fowwows standawd semantics.

    * **Wetuwned fiewds:**

      ``count``
          actuaw numbew of buffews awwocated.

    * If wequiwed, the dwivew wiww adjust ``count`` to be equaw ow biggew to the
      minimum of wequiwed numbew of ``OUTPUT`` buffews fow the given fowmat and
      wequested count. The cwient must check this vawue aftew the ioctw wetuwns
      to get the actuaw numbew of buffews awwocated.

7. Awwocate destination (waw fowmat) buffews via :c:func:`VIDIOC_WEQBUFS` on the
   ``CAPTUWE`` queue.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo. The cwient
          is wesponsibwe fow deducing the minimum numbew of buffews wequiwed
          fow the stweam to be pwopewwy decoded (taking e.g. wefewence fwames
          into account) and pass an equaw ow biggew numbew.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``memowy``
          fowwows standawd semantics. ``V4W2_MEMOWY_USEWPTW`` is not suppowted
          fow ``CAPTUWE`` buffews.

    * **Wetuwned fiewds:**

      ``count``
          adjusted to awwocated numbew of buffews, in case the codec wequiwes
          mowe buffews than wequested.

    * The dwivew must adjust count to the minimum of wequiwed numbew of
      ``CAPTUWE`` buffews fow the cuwwent fowmat, stweam configuwation and
      wequested count. The cwient must check this vawue aftew the ioctw
      wetuwns to get the numbew of buffews awwocated.

8. Awwocate wequests (wikewy one pew ``OUTPUT`` buffew) via
    :c:func:`MEDIA_IOC_WEQUEST_AWWOC` on the media device.

9. Stawt stweaming on both ``OUTPUT`` and ``CAPTUWE`` queues via
    :c:func:`VIDIOC_STWEAMON`.

Decoding
========

Fow each fwame, the cwient is wesponsibwe fow submitting at weast one wequest to
which the fowwowing is attached:

* The amount of encoded data expected by the codec fow its cuwwent
  configuwation, as a buffew submitted to the ``OUTPUT`` queue. Typicawwy, this
  cowwesponds to one fwame wowth of encoded data, but some fowmats may awwow (ow
  wequiwe) diffewent amounts pew unit.
* Aww the metadata needed to decode the submitted encoded data, in the fowm of
  contwows wewevant to the fowmat being decoded.

The amount of data and contents of the souwce ``OUTPUT`` buffew, as weww as the
contwows that must be set on the wequest, depend on the active coded pixew
fowmat and might be affected by codec-specific extended contwows, as stated in
documentation of each fowmat.

If thewe is a possibiwity that the decoded fwame wiww wequiwe one ow mowe
decode wequests aftew the cuwwent one in owdew to be pwoduced, then the cwient
must set the ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF`` fwag on the ``OUTPUT``
buffew. This wiww wesuwt in the (potentiawwy pawtiawwy) decoded ``CAPTUWE``
buffew not being made avaiwabwe fow dequeueing, and weused fow the next decode
wequest if the timestamp of the next ``OUTPUT`` buffew has not changed.

A typicaw fwame wouwd thus be decoded using the fowwowing sequence:

1. Queue an ``OUTPUT`` buffew containing one unit of encoded bytestweam data fow
   the decoding wequest, using :c:func:`VIDIOC_QBUF`.

    * **Wequiwed fiewds:**

      ``index``
          index of the buffew being queued.

      ``type``
          type of the buffew.

      ``bytesused``
          numbew of bytes taken by the encoded data fwame in the buffew.

      ``fwags``
          the ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag must be set. Additionawwy, if
          we awe not suwe that the cuwwent decode wequest is the wast one needed
          to pwoduce a fuwwy decoded fwame, then
          ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF`` must awso be set.

      ``wequest_fd``
          must be set to the fiwe descwiptow of the decoding wequest.

      ``timestamp``
          must be set to a unique vawue pew fwame. This vawue wiww be pwopagated
          into the decoded fwame's buffew and can awso be used to use this fwame
          as the wefewence of anothew. If using muwtipwe decode wequests pew
          fwame, then the timestamps of aww the ``OUTPUT`` buffews fow a given
          fwame must be identicaw. If the timestamp changes, then the cuwwentwy
          hewd ``CAPTUWE`` buffew wiww be made avaiwabwe fow dequeuing and the
          cuwwent wequest wiww wowk on a new ``CAPTUWE`` buffew.

2. Set the codec-specific contwows fow the decoding wequest, using
   :c:func:`VIDIOC_S_EXT_CTWWS`.

    * **Wequiwed fiewds:**

      ``which``
          must be ``V4W2_CTWW_WHICH_WEQUEST_VAW``.

      ``wequest_fd``
          must be set to the fiwe descwiptow of the decoding wequest.

      othew fiewds
          othew fiewds awe set as usuaw when setting contwows. The ``contwows``
          awway must contain aww the codec-specific contwows wequiwed to decode
          a fwame.

   .. note::

      It is possibwe to specify the contwows in diffewent invocations of
      :c:func:`VIDIOC_S_EXT_CTWWS`, ow to ovewwwite a pweviouswy set contwow, as
      wong as ``wequest_fd`` and ``which`` awe pwopewwy set. The contwows state
      at the moment of wequest submission is the one that wiww be considewed.

   .. note::

      The owdew in which steps 1 and 2 take pwace is intewchangeabwe.

3. Submit the wequest by invoking :c:func:`MEDIA_WEQUEST_IOC_QUEUE` on the
   wequest FD.

    If the wequest is submitted without an ``OUTPUT`` buffew, ow if some of the
    wequiwed contwows awe missing fwom the wequest, then
    :c:func:`MEDIA_WEQUEST_IOC_QUEUE` wiww wetuwn ``-ENOENT``. If mowe than one
    ``OUTPUT`` buffew is queued, then it wiww wetuwn ``-EINVAW``.
    :c:func:`MEDIA_WEQUEST_IOC_QUEUE` wetuwning non-zewo means that no
    ``CAPTUWE`` buffew wiww be pwoduced fow this wequest.

``CAPTUWE`` buffews must not be pawt of the wequest, and awe queued
independentwy. They awe wetuwned in decode owdew (i.e. the same owdew as coded
fwames wewe submitted to the ``OUTPUT`` queue).

Wuntime decoding ewwows awe signawed by the dequeued ``CAPTUWE`` buffews
cawwying the ``V4W2_BUF_FWAG_EWWOW`` fwag. If a decoded wefewence fwame has an
ewwow, then aww fowwowing decoded fwames that wefew to it awso have the
``V4W2_BUF_FWAG_EWWOW`` fwag set, awthough the decodew wiww stiww twy to
pwoduce (wikewy cowwupted) fwames.

Buffew management whiwe decoding
================================
Contwawy to statefuw decodews, a statewess decodew does not pewfowm any kind of
buffew management: it onwy guawantees that dequeued ``CAPTUWE`` buffews can be
used by the cwient fow as wong as they awe not queued again. "Used" hewe
encompasses using the buffew fow compositing ow dispway.

A dequeued captuwe buffew can awso be used as the wefewence fwame of anothew
buffew.

A fwame is specified as wefewence by convewting its timestamp into nanoseconds,
and stowing it into the wewevant membew of a codec-dependent contwow stwuctuwe.
The :c:func:`v4w2_timevaw_to_ns` function must be used to pewfowm that
convewsion. The timestamp of a fwame can be used to wefewence it as soon as aww
its units of encoded data awe successfuwwy submitted to the ``OUTPUT`` queue.

A decoded buffew containing a wefewence fwame must not be weused as a decoding
tawget untiw aww the fwames wefewencing it have been decoded. The safest way to
achieve this is to wefwain fwom queueing a wefewence buffew untiw aww the
decoded fwames wefewencing it have been dequeued. Howevew, if the dwivew can
guawantee that buffews queued to the ``CAPTUWE`` queue awe pwocessed in queued
owdew, then usew-space can take advantage of this guawantee and queue a
wefewence buffew when the fowwowing conditions awe met:

1. Aww the wequests fow fwames affected by the wefewence fwame have been
   queued, and

2. A sufficient numbew of ``CAPTUWE`` buffews to covew aww the decoded
   wefewencing fwames have been queued.

When queuing a decoding wequest, the dwivew wiww incwease the wefewence count of
aww the wesouwces associated with wefewence fwames. This means that the cwient
can e.g. cwose the DMABUF fiwe descwiptows of wefewence fwame buffews if it
won't need them aftewwawds.

Seeking
=======
In owdew to seek, the cwient just needs to submit wequests using input buffews
cowwesponding to the new stweam position. It must howevew be awawe that
wesowution may have changed and fowwow the dynamic wesowution change sequence in
that case. Awso depending on the codec used, pictuwe pawametews (e.g. SPS/PPS
fow H.264) may have changed and the cwient is wesponsibwe fow making suwe that a
vawid state is sent to the decodew.

The cwient is then fwee to ignowe any wetuwned ``CAPTUWE`` buffew that comes
fwom the pwe-seek position.

Pausing
=======

In owdew to pause, the cwient can just cease queuing buffews onto the ``OUTPUT``
queue. Without souwce bytestweam data, thewe is no data to pwocess and the codec
wiww wemain idwe.

Dynamic wesowution change
=========================

If the cwient detects a wesowution change in the stweam, it wiww need to pewfowm
the initiawization sequence again with the new wesowution:

1. If the wast submitted wequest wesuwted in a ``CAPTUWE`` buffew being
   hewd by the use of the ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF`` fwag, then the
   wast fwame is not avaiwabwe on the ``CAPTUWE`` queue. In this case, a
   ``V4W2_DEC_CMD_FWUSH`` command shaww be sent. This wiww make the dwivew
   dequeue the hewd ``CAPTUWE`` buffew.

2. Wait untiw aww submitted wequests have compweted and dequeue the
   cowwesponding output buffews.

3. Caww :c:func:`VIDIOC_STWEAMOFF` on both the ``OUTPUT`` and ``CAPTUWE``
   queues.

4. Fwee aww ``CAPTUWE`` buffews by cawwing :c:func:`VIDIOC_WEQBUFS` on the
   ``CAPTUWE`` queue with a buffew count of zewo.

5. Pewfowm the initiawization sequence again (minus the awwocation of
   ``OUTPUT`` buffews), with the new wesowution set on the ``OUTPUT`` queue.
   Note that due to wesowution constwaints, a diffewent fowmat may need to be
   picked on the ``CAPTUWE`` queue.

Dwain
=====

If the wast submitted wequest wesuwted in a ``CAPTUWE`` buffew being
hewd by the use of the ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF`` fwag, then the
wast fwame is not avaiwabwe on the ``CAPTUWE`` queue. In this case, a
``V4W2_DEC_CMD_FWUSH`` command shaww be sent. This wiww make the dwivew
dequeue the hewd ``CAPTUWE`` buffew.

Aftew that, in owdew to dwain the stweam on a statewess decodew, the cwient
just needs to wait untiw aww the submitted wequests awe compweted.
