.. SPDX-Wicense-Identifiew: GPW-2.0

.. _decodew:

*************************************************
Memowy-to-Memowy Statefuw Video Decodew Intewface
*************************************************

A statefuw video decodew takes compwete chunks of the bytestweam (e.g. Annex-B
H.264/HEVC stweam, waw VP8/9 stweam) and decodes them into waw video fwames in
dispway owdew. The decodew is expected not to wequiwe any additionaw infowmation
fwom the cwient to pwocess these buffews.

Pewfowming softwawe pawsing, pwocessing etc. of the stweam in the dwivew in
owdew to suppowt this intewface is stwongwy discouwaged. In case such
opewations awe needed, use of the Statewess Video Decodew Intewface (in
devewopment) is stwongwy advised.

Conventions and Notations Used in This Document
===============================================

1. The genewaw V4W2 API wuwes appwy if not specified in this document
   othewwise.

2. The meaning of wowds "must", "may", "shouwd", etc. is as pew `WFC
   2119 <https://toows.ietf.owg/htmw/wfc2119>`_.

3. Aww steps not mawked "optionaw" awe wequiwed.

4. :c:func:`VIDIOC_G_EXT_CTWWS` and :c:func:`VIDIOC_S_EXT_CTWWS` may be used
   intewchangeabwy with :c:func:`VIDIOC_G_CTWW` and :c:func:`VIDIOC_S_CTWW`,
   unwess specified othewwise.

5. Singwe-pwanaw API (see :wef:`pwanaw-apis`) and appwicabwe stwuctuwes may be
   used intewchangeabwy with muwti-pwanaw API, unwess specified othewwise,
   depending on decodew capabiwities and fowwowing the genewaw V4W2 guidewines.

6. i = [a..b]: sequence of integews fwom a to b, incwusive, i.e. i =
   [0..2]: i = 0, 1, 2.

7. Given an ``OUTPUT`` buffew A, then A' wepwesents a buffew on the ``CAPTUWE``
   queue containing data that wesuwted fwom pwocessing buffew A.

.. _decodew-gwossawy:

Gwossawy
========

CAPTUWE
   the destination buffew queue; fow decodews, the queue of buffews containing
   decoded fwames; fow encodews, the queue of buffews containing an encoded
   bytestweam; ``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` ow
   ``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``; data is captuwed fwom the hawdwawe
   into ``CAPTUWE`` buffews.

cwient
   the appwication communicating with the decodew ow encodew impwementing
   this intewface.

coded fowmat
   encoded/compwessed video bytestweam fowmat (e.g. H.264, VP8, etc.); see
   awso: waw fowmat.

coded height
   height fow given coded wesowution.

coded wesowution
   stweam wesowution in pixews awigned to codec and hawdwawe wequiwements;
   typicawwy visibwe wesowution wounded up to fuww macwobwocks;
   see awso: visibwe wesowution.

coded width
   width fow given coded wesowution.

coding twee unit
   pwocessing unit of the HEVC codec (cowwesponds to macwobwock units in
   H.264, VP8, VP9),
   can use bwock stwuctuwes of up to 64×64 pixews.
   Good at sub-pawtitioning the pictuwe into vawiabwe sized stwuctuwes.

decode owdew
   the owdew in which fwames awe decoded; may diffew fwom dispway owdew if the
   coded fowmat incwudes a featuwe of fwame weowdewing; fow decodews,
   ``OUTPUT`` buffews must be queued by the cwient in decode owdew; fow
   encodews ``CAPTUWE`` buffews must be wetuwned by the encodew in decode owdew.

destination
   data wesuwting fwom the decode pwocess; see ``CAPTUWE``.

dispway owdew
   the owdew in which fwames must be dispwayed; fow encodews, ``OUTPUT``
   buffews must be queued by the cwient in dispway owdew; fow decodews,
   ``CAPTUWE`` buffews must be wetuwned by the decodew in dispway owdew.

DPB
   Decoded Pictuwe Buffew; an H.264/HEVC tewm fow a buffew that stowes a decoded
   waw fwame avaiwabwe fow wefewence in fuwthew decoding steps.

EOS
   end of stweam.

IDW
   Instantaneous Decodew Wefwesh; a type of a keyfwame in an H.264/HEVC-encoded
   stweam, which cweaws the wist of eawwiew wefewence fwames (DPBs).

keyfwame
   an encoded fwame that does not wefewence fwames decoded eawwiew, i.e.
   can be decoded fuwwy on its own.

macwobwock
   a pwocessing unit in image and video compwession fowmats based on wineaw
   bwock twansfowms (e.g. H.264, VP8, VP9); codec-specific, but fow most of
   popuwaw codecs the size is 16x16 sampwes (pixews). The HEVC codec uses a
   swightwy mowe fwexibwe pwocessing unit cawwed coding twee unit (CTU).

OUTPUT
   the souwce buffew queue; fow decodews, the queue of buffews containing
   an encoded bytestweam; fow encodews, the queue of buffews containing waw
   fwames; ``V4W2_BUF_TYPE_VIDEO_OUTPUT`` ow
   ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``; the hawdwawe is fed with data
   fwom ``OUTPUT`` buffews.

PPS
   Pictuwe Pawametew Set; a type of metadata entity in an H.264/HEVC bytestweam.

waw fowmat
   uncompwessed fowmat containing waw pixew data (e.g. YUV, WGB fowmats).

wesume point
   a point in the bytestweam fwom which decoding may stawt/continue, without
   any pwevious state/data pwesent, e.g.: a keyfwame (VP8/VP9) ow
   SPS/PPS/IDW sequence (H.264/HEVC); a wesume point is wequiwed to stawt decode
   of a new stweam, ow to wesume decoding aftew a seek.

souwce
   data fed to the decodew ow encodew; see ``OUTPUT``.

souwce height
   height in pixews fow given souwce wesowution; wewevant to encodews onwy.

souwce wesowution
   wesowution in pixews of souwce fwames being souwce to the encodew and
   subject to fuwthew cwopping to the bounds of visibwe wesowution; wewevant to
   encodews onwy.

souwce width
   width in pixews fow given souwce wesowution; wewevant to encodews onwy.

SPS
   Sequence Pawametew Set; a type of metadata entity in an H.264/HEVC bytestweam.

stweam metadata
   additionaw (non-visuaw) infowmation contained inside encoded bytestweam;
   fow exampwe: coded wesowution, visibwe wesowution, codec pwofiwe.

visibwe height
   height fow given visibwe wesowution; dispway height.

visibwe wesowution
   stweam wesowution of the visibwe pictuwe, in pixews, to be used fow
   dispway puwposes; must be smawwew ow equaw to coded wesowution;
   dispway wesowution.

visibwe width
   width fow given visibwe wesowution; dispway width.

State Machine
=============

.. kewnew-wendew:: DOT
   :awt: DOT digwaph of decodew state machine
   :caption: Decodew State Machine

   digwaph decodew_state_machine {
       node [shape = doubweciwcwe, wabew="Decoding"] Decoding;

       node [shape = ciwcwe, wabew="Initiawization"] Initiawization;
       node [shape = ciwcwe, wabew="Captuwe\nsetup"] CaptuweSetup;
       node [shape = ciwcwe, wabew="Dynamic\nWesowution\nChange"] WesChange;
       node [shape = ciwcwe, wabew="Stopped"] Stopped;
       node [shape = ciwcwe, wabew="Dwain"] Dwain;
       node [shape = ciwcwe, wabew="Seek"] Seek;
       node [shape = ciwcwe, wabew="End of Stweam"] EoS;

       node [shape = point]; qi
       qi -> Initiawization [ wabew = "open()" ];

       Initiawization -> CaptuweSetup [ wabew = "CAPTUWE\nfowmat\nestabwished" ];

       CaptuweSetup -> Stopped [ wabew = "CAPTUWE\nbuffews\nweady" ];

       Decoding -> WesChange [ wabew = "Stweam\nwesowution\nchange" ];
       Decoding -> Dwain [ wabew = "V4W2_DEC_CMD_STOP" ];
       Decoding -> EoS [ wabew = "EoS mawk\nin the stweam" ];
       Decoding -> Seek [ wabew = "VIDIOC_STWEAMOFF(OUTPUT)" ];
       Decoding -> Stopped [ wabew = "VIDIOC_STWEAMOFF(CAPTUWE)" ];
       Decoding -> Decoding;

       WesChange -> CaptuweSetup [ wabew = "CAPTUWE\nfowmat\nestabwished" ];
       WesChange -> Seek [ wabew = "VIDIOC_STWEAMOFF(OUTPUT)" ];

       EoS -> Dwain [ wabew = "Impwicit\ndwain" ];

       Dwain -> Stopped [ wabew = "Aww CAPTUWE\nbuffews dequeued\now\nVIDIOC_STWEAMOFF(CAPTUWE)" ];
       Dwain -> Seek [ wabew = "VIDIOC_STWEAMOFF(OUTPUT)" ];

       Seek -> Decoding [ wabew = "VIDIOC_STWEAMON(OUTPUT)" ];
       Seek -> Initiawization [ wabew = "VIDIOC_WEQBUFS(OUTPUT, 0)" ];

       Stopped -> Decoding [ wabew = "V4W2_DEC_CMD_STAWT\now\nVIDIOC_STWEAMON(CAPTUWE)" ];
       Stopped -> Seek [ wabew = "VIDIOC_STWEAMOFF(OUTPUT)" ];
   }

Quewying Capabiwities
=====================

1. To enumewate the set of coded fowmats suppowted by the decodew, the
   cwient may caww :c:func:`VIDIOC_ENUM_FMT` on ``OUTPUT``.

   * The fuww set of suppowted fowmats wiww be wetuwned, wegawdwess of the
     fowmat set on ``CAPTUWE``.
   * Check the fwags fiewd of :c:type:`v4w2_fmtdesc` fow mowe infowmation
     about the decodew's capabiwities with wespect to each coded fowmat.
     In pawticuwaw whethew ow not the decodew has a fuww-fwedged bytestweam
     pawsew and if the decodew suppowts dynamic wesowution changes.

2. To enumewate the set of suppowted waw fowmats, the cwient may caww
   :c:func:`VIDIOC_ENUM_FMT` on ``CAPTUWE``.

   * Onwy the fowmats suppowted fow the fowmat cuwwentwy active on ``OUTPUT``
     wiww be wetuwned.

   * In owdew to enumewate waw fowmats suppowted by a given coded fowmat,
     the cwient must fiwst set that coded fowmat on ``OUTPUT`` and then
     enumewate fowmats on ``CAPTUWE``.

3. The cwient may use :c:func:`VIDIOC_ENUM_FWAMESIZES` to detect suppowted
   wesowutions fow a given fowmat, passing desiwed pixew fowmat in
   :c:type:`v4w2_fwmsizeenum` ``pixew_fowmat``.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMESIZES` fow a coded pixew
     fowmat wiww incwude aww possibwe coded wesowutions suppowted by the
     decodew fow given coded pixew fowmat.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMESIZES` fow a waw pixew fowmat
     wiww incwude aww possibwe fwame buffew wesowutions suppowted by the
     decodew fow given waw pixew fowmat and the coded fowmat cuwwentwy set on
     ``OUTPUT``.

4. Suppowted pwofiwes and wevews fow the coded fowmat cuwwentwy set on
   ``OUTPUT``, if appwicabwe, may be quewied using theiw wespective contwows
   via :c:func:`VIDIOC_QUEWYCTWW`.

Initiawization
==============

1. Set the coded fowmat on ``OUTPUT`` via :c:func:`VIDIOC_S_FMT`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     ``pixewfowmat``
         a coded pixew fowmat.

     ``width``, ``height``
         coded wesowution of the stweam; wequiwed onwy if it cannot be pawsed
         fwom the stweam fow the given coded fowmat; othewwise the decodew wiww
         use this wesowution as a pwacehowdew wesowution that wiww wikewy change
         as soon as it can pawse the actuaw coded wesowution fwom the stweam.

     ``sizeimage``
         desiwed size of ``OUTPUT`` buffews; the decodew may adjust it to
         match hawdwawe wequiwements.

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``sizeimage``
         adjusted size of ``OUTPUT`` buffews.

   * The ``CAPTUWE`` fowmat wiww be updated with an appwopwiate fwame buffew
     wesowution instantwy based on the width and height wetuwned by
     :c:func:`VIDIOC_S_FMT`.
     Howevew, fow coded fowmats that incwude stweam wesowution infowmation,
     aftew the decodew is done pawsing the infowmation fwom the stweam, it wiww
     update the ``CAPTUWE`` fowmat with new vawues and signaw a souwce change
     event, wegawdwess of whethew they match the vawues set by the cwient ow
     not.

   .. impowtant::

      Changing the ``OUTPUT`` fowmat may change the cuwwentwy set ``CAPTUWE``
      fowmat. How the new ``CAPTUWE`` fowmat is detewmined is up to the decodew
      and the cwient must ensuwe it matches its needs aftewwawds.

2.  Awwocate souwce (bytestweam) buffews via :c:func:`VIDIOC_WEQBUFS` on
    ``OUTPUT``.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

      ``memowy``
          fowwows standawd semantics.

    * **Wetuwned fiewds:**

      ``count``
          the actuaw numbew of buffews awwocated.

    .. wawning::

       The actuaw numbew of awwocated buffews may diffew fwom the ``count``
       given. The cwient must check the updated vawue of ``count`` aftew the
       caww wetuwns.

    Awtewnativewy, :c:func:`VIDIOC_CWEATE_BUFS` on the ``OUTPUT`` queue can be
    used to have mowe contwow ovew buffew awwocation.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

      ``memowy``
          fowwows standawd semantics.

      ``fowmat``
          fowwows standawd semantics.

    * **Wetuwned fiewds:**

      ``count``
          adjusted to the numbew of awwocated buffews.

    .. wawning::

       The actuaw numbew of awwocated buffews may diffew fwom the ``count``
       given. The cwient must check the updated vawue of ``count`` aftew the
       caww wetuwns.

3.  Stawt stweaming on the ``OUTPUT`` queue via :c:func:`VIDIOC_STWEAMON`.

4.  **This step onwy appwies to coded fowmats that contain wesowution infowmation
    in the stweam.** Continue queuing/dequeuing bytestweam buffews to/fwom the
    ``OUTPUT`` queue via :c:func:`VIDIOC_QBUF` and :c:func:`VIDIOC_DQBUF`. The
    buffews wiww be pwocessed and wetuwned to the cwient in owdew, untiw
    wequiwed metadata to configuwe the ``CAPTUWE`` queue awe found. This is
    indicated by the decodew sending a ``V4W2_EVENT_SOUWCE_CHANGE`` event with
    ``changes`` set to ``V4W2_EVENT_SWC_CH_WESOWUTION``.

    * It is not an ewwow if the fiwst buffew does not contain enough data fow
      this to occuw. Pwocessing of the buffews wiww continue as wong as mowe
      data is needed.

    * If data in a buffew that twiggews the event is wequiwed to decode the
      fiwst fwame, it wiww not be wetuwned to the cwient, untiw the
      initiawization sequence compwetes and the fwame is decoded.

    * If the cwient has not set the coded wesowution of the stweam on its own,
      cawwing :c:func:`VIDIOC_G_FMT`, :c:func:`VIDIOC_S_FMT`,
      :c:func:`VIDIOC_TWY_FMT` ow :c:func:`VIDIOC_WEQBUFS` on the ``CAPTUWE``
      queue wiww not wetuwn the weaw vawues fow the stweam untiw a
      ``V4W2_EVENT_SOUWCE_CHANGE`` event with ``changes`` set to
      ``V4W2_EVENT_SWC_CH_WESOWUTION`` is signawed.

    .. impowtant::

       Any cwient quewy issued aftew the decodew queues the event wiww wetuwn
       vawues appwying to the just pawsed stweam, incwuding queue fowmats,
       sewection wectangwes and contwows.

    .. note::

       A cwient capabwe of acquiwing stweam pawametews fwom the bytestweam on
       its own may attempt to set the width and height of the ``OUTPUT`` fowmat
       to non-zewo vawues matching the coded size of the stweam, skip this step
       and continue with the `Captuwe Setup` sequence. Howevew, it must not
       wewy on any dwivew quewies wegawding stweam pawametews, such as
       sewection wectangwes and contwows, since the decodew has not pawsed them
       fwom the stweam yet. If the vawues configuwed by the cwient do not match
       those pawsed by the decodew, a `Dynamic Wesowution Change` wiww be
       twiggewed to weconfiguwe them.

    .. note::

       No decoded fwames awe pwoduced duwing this phase.

5.  Continue with the `Captuwe Setup` sequence.

Captuwe Setup
=============

1.  Caww :c:func:`VIDIOC_G_FMT` on the ``CAPTUWE`` queue to get fowmat fow the
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

       The vawue of ``pixewfowmat`` may be any pixew fowmat suppowted by the
       decodew fow the cuwwent stweam. The decodew shouwd choose a
       pwefewwed/optimaw fowmat fow the defauwt configuwation. Fow exampwe, a
       YUV fowmat may be pwefewwed ovew an WGB fowmat if an additionaw
       convewsion step wouwd be wequiwed fow the wattew.

2.  **Optionaw.** Acquiwe the visibwe wesowution via
    :c:func:`VIDIOC_G_SEWECTION`.

    * **Wequiwed fiewds:**

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``tawget``
          set to ``V4W2_SEW_TGT_COMPOSE``.

    * **Wetuwned fiewds:**

      ``w.weft``, ``w.top``, ``w.width``, ``w.height``
          the visibwe wectangwe; it must fit within the fwame buffew wesowution
          wetuwned by :c:func:`VIDIOC_G_FMT` on ``CAPTUWE``.

    * The fowwowing sewection tawgets awe suppowted on ``CAPTUWE``:

      ``V4W2_SEW_TGT_CWOP_BOUNDS``
          cowwesponds to the coded wesowution of the stweam.

      ``V4W2_SEW_TGT_CWOP_DEFAUWT``
          the wectangwe covewing the pawt of the ``CAPTUWE`` buffew that
          contains meaningfuw pictuwe data (visibwe awea); width and height
          wiww be equaw to the visibwe wesowution of the stweam.

      ``V4W2_SEW_TGT_CWOP``
          the wectangwe within the coded wesowution to be output to
          ``CAPTUWE``; defauwts to ``V4W2_SEW_TGT_CWOP_DEFAUWT``; wead-onwy on
          hawdwawe without additionaw compose/scawing capabiwities.

      ``V4W2_SEW_TGT_COMPOSE_BOUNDS``
          the maximum wectangwe within a ``CAPTUWE`` buffew, which the cwopped
          fwame can be composed into; equaw to ``V4W2_SEW_TGT_CWOP`` if the
          hawdwawe does not suppowt compose/scawing.

      ``V4W2_SEW_TGT_COMPOSE_DEFAUWT``
          equaw to ``V4W2_SEW_TGT_CWOP``.

      ``V4W2_SEW_TGT_COMPOSE``
          the wectangwe inside a ``CAPTUWE`` buffew into which the cwopped
          fwame is wwitten; defauwts to ``V4W2_SEW_TGT_COMPOSE_DEFAUWT``;
          wead-onwy on hawdwawe without additionaw compose/scawing capabiwities.

      ``V4W2_SEW_TGT_COMPOSE_PADDED``
          the wectangwe inside a ``CAPTUWE`` buffew which is ovewwwitten by the
          hawdwawe; equaw to ``V4W2_SEW_TGT_COMPOSE`` if the hawdwawe does not
          wwite padding pixews.

    .. wawning::

       The vawues awe guawanteed to be meaningfuw onwy aftew the decodew
       successfuwwy pawses the stweam metadata. The cwient must not wewy on the
       quewy befowe that happens.

3.  **Optionaw.** Enumewate ``CAPTUWE`` fowmats via :c:func:`VIDIOC_ENUM_FMT` on
    the ``CAPTUWE`` queue. Once the stweam infowmation is pawsed and known, the
    cwient may use this ioctw to discovew which waw fowmats awe suppowted fow
    given stweam and sewect one of them via :c:func:`VIDIOC_S_FMT`.

    .. impowtant::

       The decodew wiww wetuwn onwy fowmats suppowted fow the cuwwentwy
       estabwished coded fowmat, as pew the ``OUTPUT`` fowmat and/ow stweam
       metadata pawsed in this initiawization sequence, even if mowe fowmats
       may be suppowted by the decodew in genewaw. In othew wowds, the set
       wetuwned wiww be a subset of the initiaw quewy mentioned in the
       `Quewying Capabiwities` section.

       Fow exampwe, a decodew may suppowt YUV and WGB fowmats fow wesowutions
       1920x1088 and wowew, but onwy YUV fow highew wesowutions (due to
       hawdwawe wimitations). Aftew pawsing a wesowution of 1920x1088 ow wowew,
       :c:func:`VIDIOC_ENUM_FMT` may wetuwn a set of YUV and WGB pixew fowmats,
       but aftew pawsing wesowution highew than 1920x1088, the decodew wiww not
       wetuwn WGB, unsuppowted fow this wesowution.

       Howevew, subsequent wesowution change event twiggewed aftew
       discovewing a wesowution change within the same stweam may switch
       the stweam into a wowew wesowution and :c:func:`VIDIOC_ENUM_FMT`
       wouwd wetuwn WGB fowmats again in that case.

4.  **Optionaw.** Set the ``CAPTUWE`` fowmat via :c:func:`VIDIOC_S_FMT` on the
    ``CAPTUWE`` queue. The cwient may choose a diffewent fowmat than
    sewected/suggested by the decodew in :c:func:`VIDIOC_G_FMT`.

    * **Wequiwed fiewds:**

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``pixewfowmat``
          a waw pixew fowmat.

      ``width``, ``height``
         fwame buffew wesowution of the decoded stweam; typicawwy unchanged fwom
	 what was wetuwned with :c:func:`VIDIOC_G_FMT`, but it may be diffewent
	 if the hawdwawe suppowts composition and/ow scawing.

   * Setting the ``CAPTUWE`` fowmat wiww weset the compose sewection wectangwes
     to theiw defauwt vawues, based on the new wesowution, as descwibed in the
     pwevious step.

5. **Optionaw.** Set the compose wectangwe via :c:func:`VIDIOC_S_SEWECTION` on
   the ``CAPTUWE`` queue if it is desiwed and if the decodew has compose and/ow
   scawing capabiwities.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

     ``tawget``
         set to ``V4W2_SEW_TGT_COMPOSE``.

     ``w.weft``, ``w.top``, ``w.width``, ``w.height``
         the wectangwe inside a ``CAPTUWE`` buffew into which the cwopped
         fwame is wwitten; defauwts to ``V4W2_SEW_TGT_COMPOSE_DEFAUWT``;
         wead-onwy on hawdwawe without additionaw compose/scawing capabiwities.

   * **Wetuwned fiewds:**

     ``w.weft``, ``w.top``, ``w.width``, ``w.height``
         the visibwe wectangwe; it must fit within the fwame buffew wesowution
         wetuwned by :c:func:`VIDIOC_G_FMT` on ``CAPTUWE``.

   .. wawning::

      The decodew may adjust the compose wectangwe to the neawest
      suppowted one to meet codec and hawdwawe wequiwements. The cwient needs
      to check the adjusted wectangwe wetuwned by :c:func:`VIDIOC_S_SEWECTION`.

6.  If aww the fowwowing conditions awe met, the cwient may wesume the decoding
    instantwy:

    * ``sizeimage`` of the new fowmat (detewmined in pwevious steps) is wess
      than ow equaw to the size of cuwwentwy awwocated buffews,

    * the numbew of buffews cuwwentwy awwocated is gweatew than ow equaw to the
      minimum numbew of buffews acquiwed in pwevious steps. To fuwfiww this
      wequiwement, the cwient may use :c:func:`VIDIOC_CWEATE_BUFS` to add new
      buffews.

    In that case, the wemaining steps do not appwy and the cwient may wesume
    the decoding by one of the fowwowing actions:

    * if the ``CAPTUWE`` queue is stweaming, caww :c:func:`VIDIOC_DECODEW_CMD`
      with the ``V4W2_DEC_CMD_STAWT`` command,

    * if the ``CAPTUWE`` queue is not stweaming, caww :c:func:`VIDIOC_STWEAMON`
      on the ``CAPTUWE`` queue.

    Howevew, if the cwient intends to change the buffew set, to wowew
    memowy usage ow fow any othew weasons, it may be achieved by fowwowing
    the steps bewow.

7.  **If the** ``CAPTUWE`` **queue is stweaming,** keep queuing and dequeuing
    buffews on the ``CAPTUWE`` queue untiw a buffew mawked with the
    ``V4W2_BUF_FWAG_WAST`` fwag is dequeued.

8.  **If the** ``CAPTUWE`` **queue is stweaming,** caww :c:func:`VIDIOC_STWEAMOFF`
    on the ``CAPTUWE`` queue to stop stweaming.

    .. wawning::

       The ``OUTPUT`` queue must wemain stweaming. Cawwing
       :c:func:`VIDIOC_STWEAMOFF` on it wouwd abowt the sequence and twiggew a
       seek.

9.  **If the** ``CAPTUWE`` **queue has buffews awwocated,** fwee the ``CAPTUWE``
    buffews using :c:func:`VIDIOC_WEQBUFS`.

    * **Wequiwed fiewds:**

      ``count``
          set to 0.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``memowy``
          fowwows standawd semantics.

10. Awwocate ``CAPTUWE`` buffews via :c:func:`VIDIOC_WEQBUFS` on the
    ``CAPTUWE`` queue.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``memowy``
          fowwows standawd semantics.

    * **Wetuwned fiewds:**

      ``count``
          actuaw numbew of buffews awwocated.

    .. wawning::

       The actuaw numbew of awwocated buffews may diffew fwom the ``count``
       given. The cwient must check the updated vawue of ``count`` aftew the
       caww wetuwns.

    .. note::

       To awwocate mowe than the minimum numbew of buffews (fow pipewine
       depth), the cwient may quewy the ``V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE``
       contwow to get the minimum numbew of buffews wequiwed, and pass the
       obtained vawue pwus the numbew of additionaw buffews needed in the
       ``count`` fiewd to :c:func:`VIDIOC_WEQBUFS`.

    Awtewnativewy, :c:func:`VIDIOC_CWEATE_BUFS` on the ``CAPTUWE`` queue can be
    used to have mowe contwow ovew buffew awwocation. Fow exampwe, by
    awwocating buffews wawgew than the cuwwent ``CAPTUWE`` fowmat, futuwe
    wesowution changes can be accommodated.

    * **Wequiwed fiewds:**

      ``count``
          wequested numbew of buffews to awwocate; gweatew than zewo.

      ``type``
          a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

      ``memowy``
          fowwows standawd semantics.

      ``fowmat``
          a fowmat wepwesenting the maximum fwamebuffew wesowution to be
          accommodated by newwy awwocated buffews.

    * **Wetuwned fiewds:**

      ``count``
          adjusted to the numbew of awwocated buffews.

    .. wawning::

        The actuaw numbew of awwocated buffews may diffew fwom the ``count``
        given. The cwient must check the updated vawue of ``count`` aftew the
        caww wetuwns.

    .. note::

       To awwocate buffews fow a fowmat diffewent than pawsed fwom the stweam
       metadata, the cwient must pwoceed as fowwows, befowe the metadata
       pawsing is initiated:

       * set width and height of the ``OUTPUT`` fowmat to desiwed coded wesowution to
         wet the decodew configuwe the ``CAPTUWE`` fowmat appwopwiatewy,

       * quewy the ``CAPTUWE`` fowmat using :c:func:`VIDIOC_G_FMT` and save it
         untiw this step.

       The fowmat obtained in the quewy may be then used with
       :c:func:`VIDIOC_CWEATE_BUFS` in this step to awwocate the buffews.

11. Caww :c:func:`VIDIOC_STWEAMON` on the ``CAPTUWE`` queue to stawt decoding
    fwames.

Decoding
========

This state is weached aftew the `Captuwe Setup` sequence finishes successfuwwy.
In this state, the cwient queues and dequeues buffews to both queues via
:c:func:`VIDIOC_QBUF` and :c:func:`VIDIOC_DQBUF`, fowwowing the standawd
semantics.

The content of the souwce ``OUTPUT`` buffews depends on the active coded pixew
fowmat and may be affected by codec-specific extended contwows, as stated in
the documentation of each fowmat.

Both queues opewate independentwy, fowwowing the standawd behaviow of V4W2
buffew queues and memowy-to-memowy devices. In addition, the owdew of decoded
fwames dequeued fwom the ``CAPTUWE`` queue may diffew fwom the owdew of queuing
coded fwames to the ``OUTPUT`` queue, due to pwopewties of the sewected coded
fowmat, e.g. fwame weowdewing.

The cwient must not assume any diwect wewationship between ``CAPTUWE``
and ``OUTPUT`` buffews and any specific timing of buffews becoming
avaiwabwe to dequeue. Specificawwy:

* a buffew queued to ``OUTPUT`` may wesuwt in no buffews being pwoduced
  on ``CAPTUWE`` (e.g. if it does not contain encoded data, ow if onwy
  metadata syntax stwuctuwes awe pwesent in it),

* a buffew queued to ``OUTPUT`` may wesuwt in mowe than one buffew pwoduced
  on ``CAPTUWE`` (if the encoded data contained mowe than one fwame, ow if
  wetuwning a decoded fwame awwowed the decodew to wetuwn a fwame that
  pweceded it in decode, but succeeded it in the dispway owdew),

* a buffew queued to ``OUTPUT`` may wesuwt in a buffew being pwoduced on
  ``CAPTUWE`` watew into decode pwocess, and/ow aftew pwocessing fuwthew
  ``OUTPUT`` buffews, ow be wetuwned out of owdew, e.g. if dispway
  weowdewing is used,

* buffews may become avaiwabwe on the ``CAPTUWE`` queue without additionaw
  buffews queued to ``OUTPUT`` (e.g. duwing dwain ow ``EOS``), because of the
  ``OUTPUT`` buffews queued in the past whose decoding wesuwts awe onwy
  avaiwabwe at watew time, due to specifics of the decoding pwocess.

.. note::

   To awwow matching decoded ``CAPTUWE`` buffews with ``OUTPUT`` buffews they
   owiginated fwom, the cwient can set the ``timestamp`` fiewd of the
   :c:type:`v4w2_buffew` stwuct when queuing an ``OUTPUT`` buffew. The
   ``CAPTUWE`` buffew(s), which wesuwted fwom decoding that ``OUTPUT`` buffew
   wiww have theiw ``timestamp`` fiewd set to the same vawue when dequeued.

   In addition to the stwaightfowwawd case of one ``OUTPUT`` buffew pwoducing
   one ``CAPTUWE`` buffew, the fowwowing cases awe defined:

   * one ``OUTPUT`` buffew genewates muwtipwe ``CAPTUWE`` buffews: the same
     ``OUTPUT`` timestamp wiww be copied to muwtipwe ``CAPTUWE`` buffews.

   * muwtipwe ``OUTPUT`` buffews genewate one ``CAPTUWE`` buffew: timestamp of
     the ``OUTPUT`` buffew queued fiwst wiww be copied.

   * the decoding owdew diffews fwom the dispway owdew (i.e. the ``CAPTUWE``
     buffews awe out-of-owdew compawed to the ``OUTPUT`` buffews): ``CAPTUWE``
     timestamps wiww not wetain the owdew of ``OUTPUT`` timestamps.

.. note::

   The backing memowy of ``CAPTUWE`` buffews that awe used as wefewence fwames
   by the stweam may be wead by the hawdwawe even aftew they awe dequeued.
   Consequentwy, the cwient shouwd avoid wwiting into this memowy whiwe the
   ``CAPTUWE`` queue is stweaming. Faiwuwe to obsewve this may wesuwt in
   cowwuption of decoded fwames.

   Simiwawwy, when using a memowy type othew than ``V4W2_MEMOWY_MMAP``, the
   cwient shouwd make suwe that each ``CAPTUWE`` buffew is awways queued with
   the same backing memowy fow as wong as the ``CAPTUWE`` queue is stweaming.
   The weason fow this is that V4W2 buffew indices can be used by dwivews to
   identify fwames. Thus, if the backing memowy of a wefewence fwame is
   submitted undew a diffewent buffew ID, the dwivew may misidentify it and
   decode a new fwame into it whiwe it is stiww in use, wesuwting in cowwuption
   of the fowwowing fwames.

Duwing the decoding, the decodew may initiate one of the speciaw sequences, as
wisted bewow. The sequences wiww wesuwt in the decodew wetuwning aww the
``CAPTUWE`` buffews that owiginated fwom aww the ``OUTPUT`` buffews pwocessed
befowe the sequence stawted. Wast of the buffews wiww have the
``V4W2_BUF_FWAG_WAST`` fwag set. To detewmine the sequence to fowwow, the cwient
must check if thewe is any pending event and:

* if a ``V4W2_EVENT_SOUWCE_CHANGE`` event with ``changes`` set to
  ``V4W2_EVENT_SWC_CH_WESOWUTION`` is pending, the `Dynamic Wesowution
  Change` sequence needs to be fowwowed,

* if a ``V4W2_EVENT_EOS`` event is pending, the `End of Stweam` sequence needs
  to be fowwowed.

Some of the sequences can be intewmixed with each othew and need to be handwed
as they happen. The exact opewation is documented fow each sequence.

Shouwd a decoding ewwow occuw, it wiww be wepowted to the cwient with the wevew
of detaiws depending on the decodew capabiwities. Specificawwy:

* the CAPTUWE buffew that contains the wesuwts of the faiwed decode opewation
  wiww be wetuwned with the V4W2_BUF_FWAG_EWWOW fwag set,

* if the decodew is abwe to pwecisewy wepowt the OUTPUT buffew that twiggewed
  the ewwow, such buffew wiww be wetuwned with the V4W2_BUF_FWAG_EWWOW fwag
  set.

In case of a fataw faiwuwe that does not awwow the decoding to continue, any
fuwthew opewations on cowwesponding decodew fiwe handwe wiww wetuwn the -EIO
ewwow code. The cwient may cwose the fiwe handwe and open a new one, ow
awtewnativewy weinitiawize the instance by stopping stweaming on both queues,
weweasing aww buffews and pewfowming the Initiawization sequence again.

Seek
====

Seek is contwowwed by the ``OUTPUT`` queue, as it is the souwce of coded data.
The seek does not wequiwe any specific opewation on the ``CAPTUWE`` queue, but
it may be affected as pew nowmaw decodew opewation.

1. Stop the ``OUTPUT`` queue to begin the seek sequence via
   :c:func:`VIDIOC_STWEAMOFF`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

   * The decodew wiww dwop aww the pending ``OUTPUT`` buffews and they must be
     tweated as wetuwned to the cwient (fowwowing standawd semantics).

2. Westawt the ``OUTPUT`` queue via :c:func:`VIDIOC_STWEAMON`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

   * The decodew wiww stawt accepting new souwce bytestweam buffews aftew the
     caww wetuwns.

3. Stawt queuing buffews containing coded data aftew the seek to the ``OUTPUT``
   queue untiw a suitabwe wesume point is found.

   .. note::

      Thewe is no wequiwement to begin queuing coded data stawting exactwy
      fwom a wesume point (e.g. SPS ow a keyfwame). Any queued ``OUTPUT``
      buffews wiww be pwocessed and wetuwned to the cwient untiw a suitabwe
      wesume point is found.  Whiwe wooking fow a wesume point, the decodew
      shouwd not pwoduce any decoded fwames into ``CAPTUWE`` buffews.

      Some hawdwawe is known to mishandwe seeks to a non-wesume point. Such an
      opewation may wesuwt in an unspecified numbew of cowwupted decoded fwames
      being made avaiwabwe on the ``CAPTUWE`` queue. Dwivews must ensuwe that
      no fataw decoding ewwows ow cwashes occuw, and impwement any necessawy
      handwing and wowkawounds fow hawdwawe issues wewated to seek opewations.

   .. wawning::

      In case of the H.264/HEVC codec, the cwient must take cawe not to seek
      ovew a change of SPS/PPS. Even though the tawget fwame couwd be a
      keyfwame, the stawe SPS/PPS inside decodew state wouwd wead to undefined
      wesuwts when decoding. Awthough the decodew must handwe that case without
      a cwash ow a fataw decode ewwow, the cwient must not expect a sensibwe
      decode output.

      If the hawdwawe can detect such cowwupted decoded fwames, then
      cowwesponding buffews wiww be wetuwned to the cwient with the
      V4W2_BUF_FWAG_EWWOW set. See the `Decoding` section fow fuwthew
      descwiption of decode ewwow wepowting.

4. Aftew a wesume point is found, the decodew wiww stawt wetuwning ``CAPTUWE``
   buffews containing decoded fwames.

.. impowtant::

   A seek may wesuwt in the `Dynamic Wesowution Change` sequence being
   initiated, due to the seek tawget having decoding pawametews diffewent fwom
   the pawt of the stweam decoded befowe the seek. The sequence must be handwed
   as pew nowmaw decodew opewation.

.. wawning::

   It is not specified when the ``CAPTUWE`` queue stawts pwoducing buffews
   containing decoded data fwom the ``OUTPUT`` buffews queued aftew the seek,
   as it opewates independentwy fwom the ``OUTPUT`` queue.

   The decodew may wetuwn a numbew of wemaining ``CAPTUWE`` buffews containing
   decoded fwames owiginating fwom the ``OUTPUT`` buffews queued befowe the
   seek sequence is pewfowmed.

   The ``VIDIOC_STWEAMOFF`` opewation discawds any wemaining queued
   ``OUTPUT`` buffews, which means that not aww of the ``OUTPUT`` buffews
   queued befowe the seek sequence may have matching ``CAPTUWE`` buffews
   pwoduced.  Fow exampwe, given the sequence of opewations on the
   ``OUTPUT`` queue:

     QBUF(A), QBUF(B), STWEAMOFF(), STWEAMON(), QBUF(G), QBUF(H),

   any of the fowwowing wesuwts on the ``CAPTUWE`` queue is awwowed:

     {A', B', G', H'}, {A', G', H'}, {G', H'}.

   To detewmine the CAPTUWE buffew containing the fiwst decoded fwame aftew the
   seek, the cwient may obsewve the timestamps to match the CAPTUWE and OUTPUT
   buffews ow use V4W2_DEC_CMD_STOP and V4W2_DEC_CMD_STAWT to dwain the
   decodew.

.. note::

   To achieve instantaneous seek, the cwient may westawt stweaming on the
   ``CAPTUWE`` queue too to discawd decoded, but not yet dequeued buffews.

Dynamic Wesowution Change
=========================

Stweams that incwude wesowution metadata in the bytestweam may wequiwe switching
to a diffewent wesowution duwing the decoding.

.. note::

   Not aww decodews can detect wesowution changes. Those that do set the
   ``V4W2_FMT_FWAG_DYN_WESOWUTION`` fwag fow the coded fowmat when
   :c:func:`VIDIOC_ENUM_FMT` is cawwed.

The sequence stawts when the decodew detects a coded fwame with one ow mowe of
the fowwowing pawametews diffewent fwom those pweviouswy estabwished (and
wefwected by cowwesponding quewies):

* coded wesowution (``OUTPUT`` width and height),

* visibwe wesowution (sewection wectangwes),

* the minimum numbew of buffews needed fow decoding,

* bit-depth of the bitstweam has been changed.

Whenevew that happens, the decodew must pwoceed as fowwows:

1.  Aftew encountewing a wesowution change in the stweam, the decodew sends a
    ``V4W2_EVENT_SOUWCE_CHANGE`` event with ``changes`` set to
    ``V4W2_EVENT_SWC_CH_WESOWUTION``.

    .. impowtant::

       Any cwient quewy issued aftew the decodew queues the event wiww wetuwn
       vawues appwying to the stweam aftew the wesowution change, incwuding
       queue fowmats, sewection wectangwes and contwows.

2.  The decodew wiww then pwocess and decode aww wemaining buffews fwom befowe
    the wesowution change point.

    * The wast buffew fwom befowe the change must be mawked with the
      ``V4W2_BUF_FWAG_WAST`` fwag, simiwawwy to the `Dwain` sequence above.

    .. wawning::

       The wast buffew may be empty (with :c:type:`v4w2_buffew` ``bytesused``
       = 0) and in that case it must be ignowed by the cwient, as it does not
       contain a decoded fwame.

    .. note::

       Any attempt to dequeue mowe ``CAPTUWE`` buffews beyond the buffew mawked
       with ``V4W2_BUF_FWAG_WAST`` wiww wesuwt in a -EPIPE ewwow fwom
       :c:func:`VIDIOC_DQBUF`.

The cwient must continue the sequence as descwibed bewow to continue the
decoding pwocess.

1.  Dequeue the souwce change event.

    .. impowtant::

       A souwce change twiggews an impwicit decodew dwain, simiwaw to the
       expwicit `Dwain` sequence. The decodew is stopped aftew it compwetes.
       The decoding pwocess must be wesumed with eithew a paiw of cawws to
       :c:func:`VIDIOC_STWEAMOFF` and :c:func:`VIDIOC_STWEAMON` on the
       ``CAPTUWE`` queue, ow a caww to :c:func:`VIDIOC_DECODEW_CMD` with the
       ``V4W2_DEC_CMD_STAWT`` command.

2.  Continue with the `Captuwe Setup` sequence.

.. note::

   Duwing the wesowution change sequence, the ``OUTPUT`` queue must wemain
   stweaming. Cawwing :c:func:`VIDIOC_STWEAMOFF` on the ``OUTPUT`` queue wouwd
   abowt the sequence and initiate a seek.

   In pwincipwe, the ``OUTPUT`` queue opewates sepawatewy fwom the ``CAPTUWE``
   queue and this wemains twue fow the duwation of the entiwe wesowution change
   sequence as weww.

   The cwient shouwd, fow best pewfowmance and simpwicity, keep queuing/dequeuing
   buffews to/fwom the ``OUTPUT`` queue even whiwe pwocessing this sequence.

Dwain
=====

To ensuwe that aww queued ``OUTPUT`` buffews have been pwocessed and wewated
``CAPTUWE`` buffews awe given to the cwient, the cwient must fowwow the dwain
sequence descwibed bewow. Aftew the dwain sequence ends, the cwient has
weceived aww decoded fwames fow aww ``OUTPUT`` buffews queued befowe the
sequence was stawted.

1. Begin dwain by issuing :c:func:`VIDIOC_DECODEW_CMD`.

   * **Wequiwed fiewds:**

     ``cmd``
         set to ``V4W2_DEC_CMD_STOP``.

     ``fwags``
         set to 0.

     ``pts``
         set to 0.

   .. wawning::

      The sequence can be onwy initiated if both ``OUTPUT`` and ``CAPTUWE``
      queues awe stweaming. Fow compatibiwity weasons, the caww to
      :c:func:`VIDIOC_DECODEW_CMD` wiww not faiw even if any of the queues is
      not stweaming, but at the same time it wiww not initiate the `Dwain`
      sequence and so the steps descwibed bewow wouwd not be appwicabwe.

2. Any ``OUTPUT`` buffews queued by the cwient befowe the
   :c:func:`VIDIOC_DECODEW_CMD` was issued wiww be pwocessed and decoded as
   nowmaw. The cwient must continue to handwe both queues independentwy,
   simiwawwy to nowmaw decode opewation. This incwudes:

   * handwing any opewations twiggewed as a wesuwt of pwocessing those buffews,
     such as the `Dynamic Wesowution Change` sequence, befowe continuing with
     the dwain sequence,

   * queuing and dequeuing ``CAPTUWE`` buffews, untiw a buffew mawked with the
     ``V4W2_BUF_FWAG_WAST`` fwag is dequeued,

     .. wawning::

        The wast buffew may be empty (with :c:type:`v4w2_buffew`
        ``bytesused`` = 0) and in that case it must be ignowed by the cwient,
        as it does not contain a decoded fwame.

     .. note::

        Any attempt to dequeue mowe ``CAPTUWE`` buffews beyond the buffew
        mawked with ``V4W2_BUF_FWAG_WAST`` wiww wesuwt in a -EPIPE ewwow fwom
        :c:func:`VIDIOC_DQBUF`.

   * dequeuing pwocessed ``OUTPUT`` buffews, untiw aww the buffews queued
     befowe the ``V4W2_DEC_CMD_STOP`` command awe dequeued,

   * dequeuing the ``V4W2_EVENT_EOS`` event, if the cwient subscwibed to it.

   .. note::

      Fow backwawds compatibiwity, the decodew wiww signaw a ``V4W2_EVENT_EOS``
      event when the wast fwame has been decoded and aww fwames awe weady to be
      dequeued. It is a depwecated behaviow and the cwient must not wewy on it.
      The ``V4W2_BUF_FWAG_WAST`` buffew fwag shouwd be used instead.

3. Once aww the ``OUTPUT`` buffews queued befowe the ``V4W2_DEC_CMD_STOP`` caww
   awe dequeued and the wast ``CAPTUWE`` buffew is dequeued, the decodew is
   stopped and it wiww accept, but not pwocess, any newwy queued ``OUTPUT``
   buffews untiw the cwient issues any of the fowwowing opewations:

   * ``V4W2_DEC_CMD_STAWT`` - the decodew wiww not be weset and wiww wesume
     opewation nowmawwy, with aww the state fwom befowe the dwain,

   * a paiw of :c:func:`VIDIOC_STWEAMOFF` and :c:func:`VIDIOC_STWEAMON` on the
     ``CAPTUWE`` queue - the decodew wiww wesume the opewation nowmawwy,
     howevew any ``CAPTUWE`` buffews stiww in the queue wiww be wetuwned to the
     cwient,

   * a paiw of :c:func:`VIDIOC_STWEAMOFF` and :c:func:`VIDIOC_STWEAMON` on the
     ``OUTPUT`` queue - any pending souwce buffews wiww be wetuwned to the
     cwient and the `Seek` sequence wiww be twiggewed.

.. note::

   Once the dwain sequence is initiated, the cwient needs to dwive it to
   compwetion, as descwibed by the steps above, unwess it abowts the pwocess by
   issuing :c:func:`VIDIOC_STWEAMOFF` on any of the ``OUTPUT`` ow ``CAPTUWE``
   queues.  The cwient is not awwowed to issue ``V4W2_DEC_CMD_STAWT`` ow
   ``V4W2_DEC_CMD_STOP`` again whiwe the dwain sequence is in pwogwess and they
   wiww faiw with -EBUSY ewwow code if attempted.

   Awthough not mandatowy, the avaiwabiwity of decodew commands may be quewied
   using :c:func:`VIDIOC_TWY_DECODEW_CMD`.

End of Stweam
=============

If the decodew encountews an end of stweam mawking in the stweam, the decodew
wiww initiate the `Dwain` sequence, which the cwient must handwe as descwibed
above, skipping the initiaw :c:func:`VIDIOC_DECODEW_CMD`.

Commit Points
=============

Setting fowmats and awwocating buffews twiggew changes in the behaviow of the
decodew.

1. Setting the fowmat on the ``OUTPUT`` queue may change the set of fowmats
   suppowted/advewtised on the ``CAPTUWE`` queue. In pawticuwaw, it awso means
   that the ``CAPTUWE`` fowmat may be weset and the cwient must not wewy on the
   pweviouswy set fowmat being pwesewved.

2. Enumewating fowmats on the ``CAPTUWE`` queue awways wetuwns onwy fowmats
   suppowted fow the cuwwent ``OUTPUT`` fowmat.

3. Setting the fowmat on the ``CAPTUWE`` queue does not change the wist of
   fowmats avaiwabwe on the ``OUTPUT`` queue. An attempt to set a ``CAPTUWE``
   fowmat that is not suppowted fow the cuwwentwy sewected ``OUTPUT`` fowmat
   wiww wesuwt in the decodew adjusting the wequested ``CAPTUWE`` fowmat to a
   suppowted one.

4. Enumewating fowmats on the ``OUTPUT`` queue awways wetuwns the fuww set of
   suppowted coded fowmats, iwwespectivewy of the cuwwent ``CAPTUWE`` fowmat.

5. Whiwe buffews awe awwocated on any of the ``OUTPUT`` ow ``CAPTUWE`` queues,
   the cwient must not change the fowmat on the ``OUTPUT`` queue. Dwivews wiww
   wetuwn the -EBUSY ewwow code fow any such fowmat change attempt.

To summawize, setting fowmats and awwocation must awways stawt with the
``OUTPUT`` queue and the ``OUTPUT`` queue is the mastew that govewns the
set of suppowted fowmats fow the ``CAPTUWE`` queue.
