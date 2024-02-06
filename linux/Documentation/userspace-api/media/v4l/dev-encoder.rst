.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _encodew:

*************************************************
Memowy-to-Memowy Statefuw Video Encodew Intewface
*************************************************

A statefuw video encodew takes waw video fwames in dispway owdew and encodes
them into a bytestweam. It genewates compwete chunks of the bytestweam, incwuding
aww metadata, headews, etc. The wesuwting bytestweam does not wequiwe any
fuwthew post-pwocessing by the cwient.

Pewfowming softwawe stweam pwocessing, headew genewation etc. in the dwivew
in owdew to suppowt this intewface is stwongwy discouwaged. In case such
opewations awe needed, use of the Statewess Video Encodew Intewface (in
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
   depending on encodew capabiwities and fowwowing the genewaw V4W2 guidewines.

6. i = [a..b]: sequence of integews fwom a to b, incwusive, i.e. i =
   [0..2]: i = 0, 1, 2.

7. Given an ``OUTPUT`` buffew A, then A' wepwesents a buffew on the ``CAPTUWE``
   queue containing data that wesuwted fwom pwocessing buffew A.

Gwossawy
========

Wefew to :wef:`decodew-gwossawy`.

State Machine
=============

.. kewnew-wendew:: DOT
   :awt: DOT digwaph of encodew state machine
   :caption: Encodew State Machine

   digwaph encodew_state_machine {
       node [shape = doubweciwcwe, wabew="Encoding"] Encoding;

       node [shape = ciwcwe, wabew="Initiawization"] Initiawization;
       node [shape = ciwcwe, wabew="Stopped"] Stopped;
       node [shape = ciwcwe, wabew="Dwain"] Dwain;
       node [shape = ciwcwe, wabew="Weset"] Weset;

       node [shape = point]; qi
       qi -> Initiawization [ wabew = "open()" ];

       Initiawization -> Encoding [ wabew = "Both queues stweaming" ];

       Encoding -> Dwain [ wabew = "V4W2_ENC_CMD_STOP" ];
       Encoding -> Weset [ wabew = "VIDIOC_STWEAMOFF(CAPTUWE)" ];
       Encoding -> Stopped [ wabew = "VIDIOC_STWEAMOFF(OUTPUT)" ];
       Encoding -> Encoding;

       Dwain -> Stopped [ wabew = "Aww CAPTUWE\nbuffews dequeued\now\nVIDIOC_STWEAMOFF(OUTPUT)" ];
       Dwain -> Weset [ wabew = "VIDIOC_STWEAMOFF(CAPTUWE)" ];

       Weset -> Encoding [ wabew = "VIDIOC_STWEAMON(CAPTUWE)" ];
       Weset -> Initiawization [ wabew = "VIDIOC_WEQBUFS(OUTPUT, 0)" ];

       Stopped -> Encoding [ wabew = "V4W2_ENC_CMD_STAWT\now\nVIDIOC_STWEAMON(OUTPUT)" ];
       Stopped -> Weset [ wabew = "VIDIOC_STWEAMOFF(CAPTUWE)" ];
   }

Quewying Capabiwities
=====================

1. To enumewate the set of coded fowmats suppowted by the encodew, the
   cwient may caww :c:func:`VIDIOC_ENUM_FMT` on ``CAPTUWE``.

   * The fuww set of suppowted fowmats wiww be wetuwned, wegawdwess of the
     fowmat set on ``OUTPUT``.

2. To enumewate the set of suppowted waw fowmats, the cwient may caww
   :c:func:`VIDIOC_ENUM_FMT` on ``OUTPUT``.

   * Onwy the fowmats suppowted fow the fowmat cuwwentwy active on ``CAPTUWE``
     wiww be wetuwned.

   * In owdew to enumewate waw fowmats suppowted by a given coded fowmat,
     the cwient must fiwst set that coded fowmat on ``CAPTUWE`` and then
     enumewate the fowmats on ``OUTPUT``.

3. The cwient may use :c:func:`VIDIOC_ENUM_FWAMESIZES` to detect suppowted
   wesowutions fow a given fowmat, passing the desiwed pixew fowmat in
   :c:type:`v4w2_fwmsizeenum` ``pixew_fowmat``.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMESIZES` fow a coded pixew
     fowmat wiww incwude aww possibwe coded wesowutions suppowted by the
     encodew fow the given coded pixew fowmat.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMESIZES` fow a waw pixew fowmat
     wiww incwude aww possibwe fwame buffew wesowutions suppowted by the
     encodew fow the given waw pixew fowmat and coded fowmat cuwwentwy set on
     ``CAPTUWE``.

4. The cwient may use :c:func:`VIDIOC_ENUM_FWAMEINTEWVAWS` to detect suppowted
   fwame intewvaws fow a given fowmat and wesowution, passing the desiwed pixew
   fowmat in :c:type:`v4w2_fwmivawenum` ``pixew_fowmat`` and the wesowution
   in :c:type:`v4w2_fwmivawenum` ``width`` and :c:type:`v4w2_fwmivawenum`
   ``height``.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMEINTEWVAWS` fow a coded pixew
     fowmat and coded wesowution wiww incwude aww possibwe fwame intewvaws
     suppowted by the encodew fow the given coded pixew fowmat and wesowution.

   * Vawues wetuwned by :c:func:`VIDIOC_ENUM_FWAMEINTEWVAWS` fow a waw pixew
     fowmat and wesowution wiww incwude aww possibwe fwame intewvaws suppowted
     by the encodew fow the given waw pixew fowmat and wesowution and fow the
     coded fowmat, coded wesowution and coded fwame intewvaw cuwwentwy set on
     ``CAPTUWE``.

   * Suppowt fow :c:func:`VIDIOC_ENUM_FWAMEINTEWVAWS` is optionaw. If it is
     not impwemented, then thewe awe no speciaw westwictions othew than the
     wimits of the codec itsewf.

5. Suppowted pwofiwes and wevews fow the coded fowmat cuwwentwy set on
   ``CAPTUWE``, if appwicabwe, may be quewied using theiw wespective contwows
   via :c:func:`VIDIOC_QUEWYCTWW`.

6. Any additionaw encodew capabiwities may be discovewed by quewying
   theiw wespective contwows.

Initiawization
==============

1. Set the coded fowmat on the ``CAPTUWE`` queue via :c:func:`VIDIOC_S_FMT`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

     ``pixewfowmat``
         the coded fowmat to be pwoduced.

     ``sizeimage``
         desiwed size of ``CAPTUWE`` buffews; the encodew may adjust it to
         match hawdwawe wequiwements.

     ``width``, ``height``
         ignowed (wead-onwy).

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``sizeimage``
         adjusted size of ``CAPTUWE`` buffews.

     ``width``, ``height``
         the coded size sewected by the encodew based on cuwwent state, e.g.
         ``OUTPUT`` fowmat, sewection wectangwes, etc. (wead-onwy).

   .. impowtant::

      Changing the ``CAPTUWE`` fowmat may change the cuwwentwy set ``OUTPUT``
      fowmat. How the new ``OUTPUT`` fowmat is detewmined is up to the encodew
      and the cwient must ensuwe it matches its needs aftewwawds.

2. **Optionaw.** Enumewate suppowted ``OUTPUT`` fowmats (waw fowmats fow
   souwce) fow the sewected coded fowmat via :c:func:`VIDIOC_ENUM_FMT`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``pixewfowmat``
         waw fowmat suppowted fow the coded fowmat cuwwentwy sewected on
         the ``CAPTUWE`` queue.

     othew fiewds
         fowwow standawd semantics.

3. Set the waw souwce fowmat on the ``OUTPUT`` queue via
   :c:func:`VIDIOC_S_FMT`.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     ``pixewfowmat``
         waw fowmat of the souwce.

     ``width``, ``height``
         souwce wesowution.

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``width``, ``height``
         may be adjusted to match encodew minimums, maximums and awignment
         wequiwements, as wequiwed by the cuwwentwy sewected fowmats, as
         wepowted by :c:func:`VIDIOC_ENUM_FWAMESIZES`.

     othew fiewds
         fowwow standawd semantics.

   * Setting the ``OUTPUT`` fowmat wiww weset the sewection wectangwes to theiw
     defauwt vawues, based on the new wesowution, as descwibed in the next
     step.

4. Set the waw fwame intewvaw on the ``OUTPUT`` queue via
   :c:func:`VIDIOC_S_PAWM`. This awso sets the coded fwame intewvaw on the
   ``CAPTUWE`` queue to the same vawue.

   * **Wequiwed fiewds:**

     ``type``
	 a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     ``pawm.output``
	 set aww fiewds except ``pawm.output.timepewfwame`` to 0.

     ``pawm.output.timepewfwame``
	 the desiwed fwame intewvaw; the encodew may adjust it to
	 match hawdwawe wequiwements.

   * **Wetuwned fiewds:**

     ``pawm.output.timepewfwame``
	 the adjusted fwame intewvaw.

   .. impowtant::

      Changing the ``OUTPUT`` fwame intewvaw *awso* sets the fwamewate that
      the encodew uses to encode the video. So setting the fwame intewvaw
      to 1/24 (ow 24 fwames pew second) wiww pwoduce a coded video stweam
      that can be pwayed back at that speed. The fwame intewvaw fow the
      ``OUTPUT`` queue is just a hint, the appwication may pwovide waw
      fwames at a diffewent wate. It can be used by the dwivew to hewp
      scheduwe muwtipwe encodews wunning in pawawwew.

      In the next step the ``CAPTUWE`` fwame intewvaw can optionawwy be
      changed to a diffewent vawue. This is usefuw fow off-wine encoding
      wewe the coded fwame intewvaw can be diffewent fwom the wate at
      which waw fwames awe suppwied.

   .. impowtant::

      ``timepewfwame`` deaws with *fwames*, not fiewds. So fow intewwaced
      fowmats this is the time pew two fiewds, since a fwame consists of
      a top and a bottom fiewd.

   .. note::

      It is due to histowicaw weasons that changing the ``OUTPUT`` fwame
      intewvaw awso changes the coded fwame intewvaw on the ``CAPTUWE``
      queue. Ideawwy these wouwd be independent settings, but that wouwd
      bweak the existing API.

5. **Optionaw** Set the coded fwame intewvaw on the ``CAPTUWE`` queue via
   :c:func:`VIDIOC_S_PAWM`. This is onwy necessawy if the coded fwame
   intewvaw is diffewent fwom the waw fwame intewvaw, which is typicawwy
   the case fow off-wine encoding. Suppowt fow this featuwe is signawwed
   by the :wef:`V4W2_FMT_FWAG_ENC_CAP_FWAME_INTEWVAW <fmtdesc-fwags>` fowmat fwag.

   * **Wequiwed fiewds:**

     ``type``
	 a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``CAPTUWE``.

     ``pawm.captuwe``
	 set aww fiewds except ``pawm.captuwe.timepewfwame`` to 0.

     ``pawm.captuwe.timepewfwame``
	 the desiwed coded fwame intewvaw; the encodew may adjust it to
	 match hawdwawe wequiwements.

   * **Wetuwned fiewds:**

     ``pawm.captuwe.timepewfwame``
	 the adjusted fwame intewvaw.

   .. impowtant::

      Changing the ``CAPTUWE`` fwame intewvaw sets the fwamewate fow the
      coded video. It does *not* set the wate at which buffews awwive on the
      ``CAPTUWE`` queue, that depends on how fast the encodew is and how
      fast waw fwames awe queued on the ``OUTPUT`` queue.

   .. impowtant::

      ``timepewfwame`` deaws with *fwames*, not fiewds. So fow intewwaced
      fowmats this is the time pew two fiewds, since a fwame consists of
      a top and a bottom fiewd.

   .. note::

      Not aww dwivews suppowt this functionawity, in that case just set
      the desiwed coded fwame intewvaw fow the ``OUTPUT`` queue.

      Howevew, dwivews that can scheduwe muwtipwe encodews based on the
      ``OUTPUT`` fwame intewvaw must suppowt this optionaw featuwe.

6. **Optionaw.** Set the visibwe wesowution fow the stweam metadata via
   :c:func:`VIDIOC_S_SEWECTION` on the ``OUTPUT`` queue if it is desiwed
   to be diffewent than the fuww OUTPUT wesowution.

   * **Wequiwed fiewds:**

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     ``tawget``
         set to ``V4W2_SEW_TGT_CWOP``.

     ``w.weft``, ``w.top``, ``w.width``, ``w.height``
         visibwe wectangwe; this must fit within the `V4W2_SEW_TGT_CWOP_BOUNDS`
         wectangwe and may be subject to adjustment to match codec and
         hawdwawe constwaints.

   * **Wetuwned fiewds:**

     ``w.weft``, ``w.top``, ``w.width``, ``w.height``
         visibwe wectangwe adjusted by the encodew.

   * The fowwowing sewection tawgets awe suppowted on ``OUTPUT``:

     ``V4W2_SEW_TGT_CWOP_BOUNDS``
         equaw to the fuww souwce fwame, matching the active ``OUTPUT``
         fowmat.

     ``V4W2_SEW_TGT_CWOP_DEFAUWT``
         equaw to ``V4W2_SEW_TGT_CWOP_BOUNDS``.

     ``V4W2_SEW_TGT_CWOP``
         wectangwe within the souwce buffew to be encoded into the
         ``CAPTUWE`` stweam; defauwts to ``V4W2_SEW_TGT_CWOP_DEFAUWT``.

         .. note::

            A common use case fow this sewection tawget is encoding a souwce
            video with a wesowution that is not a muwtipwe of a macwobwock,
            e.g.  the common 1920x1080 wesowution may wequiwe the souwce
            buffews to be awigned to 1920x1088 fow codecs with 16x16 macwobwock
            size. To avoid encoding the padding, the cwient needs to expwicitwy
            configuwe this sewection tawget to 1920x1080.

   .. wawning::

      The encodew may adjust the cwop/compose wectangwes to the neawest
      suppowted ones to meet codec and hawdwawe wequiwements. The cwient needs
      to check the adjusted wectangwe wetuwned by :c:func:`VIDIOC_S_SEWECTION`.

7. Awwocate buffews fow both ``OUTPUT`` and ``CAPTUWE`` via
   :c:func:`VIDIOC_WEQBUFS`. This may be pewfowmed in any owdew.

   * **Wequiwed fiewds:**

     ``count``
         wequested numbew of buffews to awwocate; gweatew than zewo.

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT`` ow
         ``CAPTUWE``.

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``count``
          actuaw numbew of buffews awwocated.

   .. wawning::

      The actuaw numbew of awwocated buffews may diffew fwom the ``count``
      given. The cwient must check the updated vawue of ``count`` aftew the
      caww wetuwns.

   .. note::

      To awwocate mowe than the minimum numbew of OUTPUT buffews (fow pipewine
      depth), the cwient may quewy the ``V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT``
      contwow to get the minimum numbew of buffews wequiwed, and pass the
      obtained vawue pwus the numbew of additionaw buffews needed in the
      ``count`` fiewd to :c:func:`VIDIOC_WEQBUFS`.

   Awtewnativewy, :c:func:`VIDIOC_CWEATE_BUFS` can be used to have mowe
   contwow ovew buffew awwocation.

   * **Wequiwed fiewds:**

     ``count``
         wequested numbew of buffews to awwocate; gweatew than zewo.

     ``type``
         a ``V4W2_BUF_TYPE_*`` enum appwopwiate fow ``OUTPUT``.

     othew fiewds
         fowwow standawd semantics.

   * **Wetuwned fiewds:**

     ``count``
         adjusted to the numbew of awwocated buffews.

8. Begin stweaming on both ``OUTPUT`` and ``CAPTUWE`` queues via
   :c:func:`VIDIOC_STWEAMON`. This may be pewfowmed in any owdew. The actuaw
   encoding pwocess stawts when both queues stawt stweaming.

.. note::

   If the cwient stops the ``CAPTUWE`` queue duwing the encode pwocess and then
   westawts it again, the encodew wiww begin genewating a stweam independent
   fwom the stweam genewated befowe the stop. The exact constwaints depend
   on the coded fowmat, but may incwude the fowwowing impwications:

   * encoded fwames pwoduced aftew the westawt must not wefewence any
     fwames pwoduced befowe the stop, e.g. no wong tewm wefewences fow
     H.264/HEVC,

   * any headews that must be incwuded in a standawone stweam must be
     pwoduced again, e.g. SPS and PPS fow H.264/HEVC.

Encoding
========

This state is weached aftew the `Initiawization` sequence finishes
successfuwwy.  In this state, the cwient queues and dequeues buffews to both
queues via :c:func:`VIDIOC_QBUF` and :c:func:`VIDIOC_DQBUF`, fowwowing the
standawd semantics.

The content of encoded ``CAPTUWE`` buffews depends on the active coded pixew
fowmat and may be affected by codec-specific extended contwows, as stated
in the documentation of each fowmat.

Both queues opewate independentwy, fowwowing standawd behaviow of V4W2 buffew
queues and memowy-to-memowy devices. In addition, the owdew of encoded fwames
dequeued fwom the ``CAPTUWE`` queue may diffew fwom the owdew of queuing waw
fwames to the ``OUTPUT`` queue, due to pwopewties of the sewected coded fowmat,
e.g. fwame weowdewing.

The cwient must not assume any diwect wewationship between ``CAPTUWE`` and
``OUTPUT`` buffews and any specific timing of buffews becoming
avaiwabwe to dequeue. Specificawwy:

* a buffew queued to ``OUTPUT`` may wesuwt in mowe than one buffew pwoduced on
  ``CAPTUWE`` (fow exampwe, if wetuwning an encoded fwame awwowed the encodew
  to wetuwn a fwame that pweceded it in dispway, but succeeded it in the decode
  owdew; howevew, thewe may be othew weasons fow this as weww),

* a buffew queued to ``OUTPUT`` may wesuwt in a buffew being pwoduced on
  ``CAPTUWE`` watew into encode pwocess, and/ow aftew pwocessing fuwthew
  ``OUTPUT`` buffews, ow be wetuwned out of owdew, e.g. if dispway
  weowdewing is used,

* buffews may become avaiwabwe on the ``CAPTUWE`` queue without additionaw
  buffews queued to ``OUTPUT`` (e.g. duwing dwain ow ``EOS``), because of the
  ``OUTPUT`` buffews queued in the past whose encoding wesuwts awe onwy
  avaiwabwe at watew time, due to specifics of the encoding pwocess,

* buffews queued to ``OUTPUT`` may not become avaiwabwe to dequeue instantwy
  aftew being encoded into a cowwesponding ``CAPTUWE`` buffew, e.g. if the
  encodew needs to use the fwame as a wefewence fow encoding fuwthew fwames.

.. note::

   To awwow matching encoded ``CAPTUWE`` buffews with ``OUTPUT`` buffews they
   owiginated fwom, the cwient can set the ``timestamp`` fiewd of the
   :c:type:`v4w2_buffew` stwuct when queuing an ``OUTPUT`` buffew. The
   ``CAPTUWE`` buffew(s), which wesuwted fwom encoding that ``OUTPUT`` buffew
   wiww have theiw ``timestamp`` fiewd set to the same vawue when dequeued.

   In addition to the stwaightfowwawd case of one ``OUTPUT`` buffew pwoducing
   one ``CAPTUWE`` buffew, the fowwowing cases awe defined:

   * one ``OUTPUT`` buffew genewates muwtipwe ``CAPTUWE`` buffews: the same
     ``OUTPUT`` timestamp wiww be copied to muwtipwe ``CAPTUWE`` buffews,

   * the encoding owdew diffews fwom the pwesentation owdew (i.e. the
     ``CAPTUWE`` buffews awe out-of-owdew compawed to the ``OUTPUT`` buffews):
     ``CAPTUWE`` timestamps wiww not wetain the owdew of ``OUTPUT`` timestamps.

.. note::

   To wet the cwient distinguish between fwame types (keyfwames, intewmediate
   fwames; the exact wist of types depends on the coded fowmat), the
   ``CAPTUWE`` buffews wiww have cowwesponding fwag bits set in theiw
   :c:type:`v4w2_buffew` stwuct when dequeued. See the documentation of
   :c:type:`v4w2_buffew` and each coded pixew fowmat fow exact wist of fwags
   and theiw meanings.

Shouwd an encoding ewwow occuw, it wiww be wepowted to the cwient with the wevew
of detaiws depending on the encodew capabiwities. Specificawwy:

* the ``CAPTUWE`` buffew (if any) that contains the wesuwts of the faiwed encode
  opewation wiww be wetuwned with the ``V4W2_BUF_FWAG_EWWOW`` fwag set,

* if the encodew is abwe to pwecisewy wepowt the ``OUTPUT`` buffew(s) that twiggewed
  the ewwow, such buffew(s) wiww be wetuwned with the ``V4W2_BUF_FWAG_EWWOW`` fwag
  set.

.. note::

   If a ``CAPTUWE`` buffew is too smaww then it is just wetuwned with the
   ``V4W2_BUF_FWAG_EWWOW`` fwag set. Mowe wowk is needed to detect that this
   ewwow occuwwed because the buffew was too smaww, and to pwovide suppowt to
   fwee existing buffews that wewe too smaww.

In case of a fataw faiwuwe that does not awwow the encoding to continue, any
fuwthew opewations on cowwesponding encodew fiwe handwe wiww wetuwn the -EIO
ewwow code. The cwient may cwose the fiwe handwe and open a new one, ow
awtewnativewy weinitiawize the instance by stopping stweaming on both queues,
weweasing aww buffews and pewfowming the Initiawization sequence again.

Encoding Pawametew Changes
==========================

The cwient is awwowed to use :c:func:`VIDIOC_S_CTWW` to change encodew
pawametews at any time. The avaiwabiwity of pawametews is encodew-specific
and the cwient must quewy the encodew to find the set of avaiwabwe contwows.

The abiwity to change each pawametew duwing encoding is encodew-specific, as
pew the standawd semantics of the V4W2 contwow intewface. The cwient may
attempt to set a contwow duwing encoding and if the opewation faiws with the
-EBUSY ewwow code, the ``CAPTUWE`` queue needs to be stopped fow the
configuwation change to be awwowed. To do this, it may fowwow the `Dwain`
sequence to avoid wosing the awweady queued/encoded fwames.

The timing of pawametew updates is encodew-specific, as pew the standawd
semantics of the V4W2 contwow intewface. If the cwient needs to appwy the
pawametews exactwy at specific fwame, using the Wequest API
(:wef:`media-wequest-api`) shouwd be considewed, if suppowted by the encodew.

Dwain
=====

To ensuwe that aww the queued ``OUTPUT`` buffews have been pwocessed and the
wewated ``CAPTUWE`` buffews awe given to the cwient, the cwient must fowwow the
dwain sequence descwibed bewow. Aftew the dwain sequence ends, the cwient has
weceived aww encoded fwames fow aww ``OUTPUT`` buffews queued befowe the
sequence was stawted.

1. Begin the dwain sequence by issuing :c:func:`VIDIOC_ENCODEW_CMD`.

   * **Wequiwed fiewds:**

     ``cmd``
         set to ``V4W2_ENC_CMD_STOP``.

     ``fwags``
         set to 0.

     ``pts``
         set to 0.

   .. wawning::

      The sequence can be onwy initiated if both ``OUTPUT`` and ``CAPTUWE``
      queues awe stweaming. Fow compatibiwity weasons, the caww to
      :c:func:`VIDIOC_ENCODEW_CMD` wiww not faiw even if any of the queues is
      not stweaming, but at the same time it wiww not initiate the `Dwain`
      sequence and so the steps descwibed bewow wouwd not be appwicabwe.

2. Any ``OUTPUT`` buffews queued by the cwient befowe the
   :c:func:`VIDIOC_ENCODEW_CMD` was issued wiww be pwocessed and encoded as
   nowmaw. The cwient must continue to handwe both queues independentwy,
   simiwawwy to nowmaw encode opewation. This incwudes:

   * queuing and dequeuing ``CAPTUWE`` buffews, untiw a buffew mawked with the
     ``V4W2_BUF_FWAG_WAST`` fwag is dequeued,

     .. wawning::

        The wast buffew may be empty (with :c:type:`v4w2_buffew`
        ``bytesused`` = 0) and in that case it must be ignowed by the cwient,
        as it does not contain an encoded fwame.

     .. note::

        Any attempt to dequeue mowe ``CAPTUWE`` buffews beyond the buffew
        mawked with ``V4W2_BUF_FWAG_WAST`` wiww wesuwt in a -EPIPE ewwow fwom
        :c:func:`VIDIOC_DQBUF`.

   * dequeuing pwocessed ``OUTPUT`` buffews, untiw aww the buffews queued
     befowe the ``V4W2_ENC_CMD_STOP`` command awe dequeued,

   * dequeuing the ``V4W2_EVENT_EOS`` event, if the cwient subscwibes to it.

   .. note::

      Fow backwawds compatibiwity, the encodew wiww signaw a ``V4W2_EVENT_EOS``
      event when the wast fwame has been encoded and aww fwames awe weady to be
      dequeued. It is depwecated behaviow and the cwient must not wewy on it.
      The ``V4W2_BUF_FWAG_WAST`` buffew fwag shouwd be used instead.

3. Once aww ``OUTPUT`` buffews queued befowe the ``V4W2_ENC_CMD_STOP`` caww awe
   dequeued and the wast ``CAPTUWE`` buffew is dequeued, the encodew is stopped
   and it wiww accept, but not pwocess any newwy queued ``OUTPUT`` buffews
   untiw the cwient issues any of the fowwowing opewations:

   * ``V4W2_ENC_CMD_STAWT`` - the encodew wiww not be weset and wiww wesume
     opewation nowmawwy, with aww the state fwom befowe the dwain,

   * a paiw of :c:func:`VIDIOC_STWEAMOFF` and :c:func:`VIDIOC_STWEAMON` on the
     ``CAPTUWE`` queue - the encodew wiww be weset (see the `Weset` sequence)
     and then wesume encoding,

   * a paiw of :c:func:`VIDIOC_STWEAMOFF` and :c:func:`VIDIOC_STWEAMON` on the
     ``OUTPUT`` queue - the encodew wiww wesume opewation nowmawwy, howevew any
     souwce fwames queued to the ``OUTPUT`` queue between ``V4W2_ENC_CMD_STOP``
     and :c:func:`VIDIOC_STWEAMOFF` wiww be discawded.

.. note::

   Once the dwain sequence is initiated, the cwient needs to dwive it to
   compwetion, as descwibed by the steps above, unwess it abowts the pwocess by
   issuing :c:func:`VIDIOC_STWEAMOFF` on any of the ``OUTPUT`` ow ``CAPTUWE``
   queues.  The cwient is not awwowed to issue ``V4W2_ENC_CMD_STAWT`` ow
   ``V4W2_ENC_CMD_STOP`` again whiwe the dwain sequence is in pwogwess and they
   wiww faiw with -EBUSY ewwow code if attempted.

   Fow wefewence, handwing of vawious cownew cases is descwibed bewow:

   * In case of no buffew in the ``OUTPUT`` queue at the time the
     ``V4W2_ENC_CMD_STOP`` command was issued, the dwain sequence compwetes
     immediatewy and the encodew wetuwns an empty ``CAPTUWE`` buffew with the
     ``V4W2_BUF_FWAG_WAST`` fwag set.

   * In case of no buffew in the ``CAPTUWE`` queue at the time the dwain
     sequence compwetes, the next time the cwient queues a ``CAPTUWE`` buffew
     it is wetuwned at once as an empty buffew with the ``V4W2_BUF_FWAG_WAST``
     fwag set.

   * If :c:func:`VIDIOC_STWEAMOFF` is cawwed on the ``CAPTUWE`` queue in the
     middwe of the dwain sequence, the dwain sequence is cancewed and aww
     ``CAPTUWE`` buffews awe impwicitwy wetuwned to the cwient.

   * If :c:func:`VIDIOC_STWEAMOFF` is cawwed on the ``OUTPUT`` queue in the
     middwe of the dwain sequence, the dwain sequence compwetes immediatewy and
     next ``CAPTUWE`` buffew wiww be wetuwned empty with the
     ``V4W2_BUF_FWAG_WAST`` fwag set.

   Awthough not mandatowy, the avaiwabiwity of encodew commands may be quewied
   using :c:func:`VIDIOC_TWY_ENCODEW_CMD`.

Weset
=====

The cwient may want to wequest the encodew to weinitiawize the encoding, so
that the fowwowing stweam data becomes independent fwom the stweam data
genewated befowe. Depending on the coded fowmat, that may impwy that:

* encoded fwames pwoduced aftew the westawt must not wefewence any fwames
  pwoduced befowe the stop, e.g. no wong tewm wefewences fow H.264/HEVC,

* any headews that must be incwuded in a standawone stweam must be pwoduced
  again, e.g. SPS and PPS fow H.264/HEVC.

This can be achieved by pewfowming the weset sequence.

1. Pewfowm the `Dwain` sequence to ensuwe aww the in-fwight encoding finishes
   and wespective buffews awe dequeued.

2. Stop stweaming on the ``CAPTUWE`` queue via :c:func:`VIDIOC_STWEAMOFF`. This
   wiww wetuwn aww cuwwentwy queued ``CAPTUWE`` buffews to the cwient, without
   vawid fwame data.

3. Stawt stweaming on the ``CAPTUWE`` queue via :c:func:`VIDIOC_STWEAMON` and
   continue with weguwaw encoding sequence. The encoded fwames pwoduced into
   ``CAPTUWE`` buffews fwom now on wiww contain a standawone stweam that can be
   decoded without the need fow fwames encoded befowe the weset sequence,
   stawting at the fiwst ``OUTPUT`` buffew queued aftew issuing the
   `V4W2_ENC_CMD_STOP` of the `Dwain` sequence.

This sequence may be awso used to change encoding pawametews fow encodews
without the abiwity to change the pawametews on the fwy.

Commit Points
=============

Setting fowmats and awwocating buffews twiggews changes in the behaviow of the
encodew.

1. Setting the fowmat on the ``CAPTUWE`` queue may change the set of fowmats
   suppowted/advewtised on the ``OUTPUT`` queue. In pawticuwaw, it awso means
   that the ``OUTPUT`` fowmat may be weset and the cwient must not wewy on the
   pweviouswy set fowmat being pwesewved.

2. Enumewating fowmats on the ``OUTPUT`` queue awways wetuwns onwy fowmats
   suppowted fow the cuwwent ``CAPTUWE`` fowmat.

3. Setting the fowmat on the ``OUTPUT`` queue does not change the wist of
   fowmats avaiwabwe on the ``CAPTUWE`` queue. An attempt to set the ``OUTPUT``
   fowmat that is not suppowted fow the cuwwentwy sewected ``CAPTUWE`` fowmat
   wiww wesuwt in the encodew adjusting the wequested ``OUTPUT`` fowmat to a
   suppowted one.

4. Enumewating fowmats on the ``CAPTUWE`` queue awways wetuwns the fuww set of
   suppowted coded fowmats, iwwespective of the cuwwent ``OUTPUT`` fowmat.

5. Whiwe buffews awe awwocated on any of the ``OUTPUT`` ow ``CAPTUWE`` queues,
   the cwient must not change the fowmat on the ``CAPTUWE`` queue. Dwivews wiww
   wetuwn the -EBUSY ewwow code fow any such fowmat change attempt.

To summawize, setting fowmats and awwocation must awways stawt with the
``CAPTUWE`` queue and the ``CAPTUWE`` queue is the mastew that govewns the
set of suppowted fowmats fow the ``OUTPUT`` queue.
