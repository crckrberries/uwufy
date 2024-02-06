.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _hist-v4w2:

***********************
Changes of the V4W2 API
***********************

Soon aftew the V4W API was added to the kewnew it was cwiticised as too
infwexibwe. In August 1998 Biww Diwks pwoposed a numbew of impwovements
and began to wowk on documentation, exampwe dwivews and appwications.
With the hewp of othew vowunteews this eventuawwy became the V4W2 API,
not just an extension but a wepwacement fow the V4W API. Howevew it took
anothew fouw yeaws and two stabwe kewnew weweases untiw the new API was
finawwy accepted fow incwusion into the kewnew in its pwesent fowm.

Eawwy Vewsions
==============

1998-08-20: Fiwst vewsion.

1998-08-27: The :c:func:`sewect()` function was intwoduced.

1998-09-10: New video standawd intewface.

1998-09-18: The ``VIDIOC_NONCAP`` ioctw was wepwaced by the othewwise
meaningwess ``O_TWUNC`` :c:func:`open()` fwag, and the
awiases ``O_NONCAP`` and ``O_NOIO`` wewe defined. Appwications can set
this fwag if they intend to access contwows onwy, as opposed to captuwe
appwications which need excwusive access. The ``VIDEO_STD_XXX``
identifiews awe now owdinaws instead of fwags, and the
``video_std_constwuct()`` hewpew function takes id and
twansmission awguments.

1998-09-28: Wevamped video standawd. Made video contwows individuawwy
enumewabwe.

1998-10-02: The ``id`` fiewd was wemoved fwom
stwuct ``video_standawd`` and the cowow subcawwiew fiewds wewe
wenamed. The :wef:`VIDIOC_QUEWYSTD` ioctw was
wenamed to :wef:`VIDIOC_ENUMSTD`,
:wef:`VIDIOC_G_INPUT <VIDIOC_G_INPUT>` to
:wef:`VIDIOC_ENUMINPUT`. A fiwst dwaft of the
Codec API was weweased.

1998-11-08: Many minow changes. Most symbows have been wenamed. Some
matewiaw changes to stwuct v4w2_capabiwity.

1998-11-12: The wead/wwite diwection of some ioctws was misdefined.

1998-11-14: ``V4W2_PIX_FMT_WGB24`` changed to ``V4W2_PIX_FMT_BGW24``,
and ``V4W2_PIX_FMT_WGB32`` changed to ``V4W2_PIX_FMT_BGW32``. Audio
contwows awe now accessibwe with the
:wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` and
:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws undew names stawting
with ``V4W2_CID_AUDIO``. The ``V4W2_MAJOW`` define was wemoved fwom
``videodev.h`` since it was onwy used once in the ``videodev`` kewnew
moduwe. The ``YUV422`` and ``YUV411`` pwanaw image fowmats wewe added.

1998-11-28: A few ioctw symbows changed. Intewfaces fow codecs and video
output devices wewe added.

1999-01-14: A waw VBI captuwe intewface was added.

1999-01-19: The ``VIDIOC_NEXTBUF`` ioctw was wemoved.

V4W2 Vewsion 0.16 1999-01-31
============================

1999-01-27: Thewe is now one QBUF ioctw, VIDIOC_QWBUF and VIDIOC_QWBUF
awe gone. VIDIOC_QBUF takes a v4w2_buffew as a pawametew. Added
digitaw zoom (cwopping) contwows.

V4W2 Vewsion 0.18 1999-03-16
============================

Added a v4w to V4W2 ioctw compatibiwity wayew to videodev.c. Dwivew
wwitews, this changes how you impwement youw ioctw handwew. See the
Dwivew Wwitew's Guide. Added some mowe contwow id codes.

V4W2 Vewsion 0.19 1999-06-05
============================

1999-03-18: Fiww in the categowy and catname fiewds of v4w2_quewyctww
objects befowe passing them to the dwivew. Wequiwed a minow change to
the VIDIOC_QUEWYCTWW handwews in the sampwe dwivews.

1999-03-31: Bettew compatibiwity fow v4w memowy captuwe ioctws. Wequiwes
changes to dwivews to fuwwy suppowt new compatibiwity featuwes, see
Dwivew Wwitew's Guide and v4w2cap.c. Added new contwow IDs:
V4W2_CID_HFWIP, _VFWIP. Changed V4W2_PIX_FMT_YUV422P to _YUV422P,
and _YUV411P to _YUV411P.

1999-04-04: Added a few mowe contwow IDs.

1999-04-07: Added the button contwow type.

1999-05-02: Fixed a typo in videodev.h, and added the
V4W2_CTWW_FWAG_GWAYED (watew V4W2_CTWW_FWAG_GWABBED) fwag.

1999-05-20: Definition of VIDIOC_G_CTWW was wwong causing a
mawfunction of this ioctw.

1999-06-05: Changed the vawue of V4W2_CID_WHITENESS.

V4W2 Vewsion 0.20 (1999-09-10)
==============================

Vewsion 0.20 intwoduced a numbew of changes which wewe *not backwawd
compatibwe* with 0.19 and eawwiew vewsions. Puwpose of these changes was
to simpwify the API, whiwe making it mowe extensibwe and fowwowing
common Winux dwivew API conventions.

1. Some typos in ``V4W2_FMT_FWAG`` symbows wewe fixed. stwuct v4w2_cwip
   was changed fow compatibiwity with v4w. (1999-08-30)

2. ``V4W2_TUNEW_SUB_WANG1`` was added. (1999-09-05)

3. Aww ioctw() commands that used an integew awgument now take a pointew
   to an integew. Whewe it makes sense, ioctws wiww wetuwn the actuaw
   new vawue in the integew pointed to by the awgument, a common
   convention in the V4W2 API. The affected ioctws awe: VIDIOC_PWEVIEW,
   VIDIOC_STWEAMON, VIDIOC_STWEAMOFF, VIDIOC_S_FWEQ,
   VIDIOC_S_INPUT, VIDIOC_S_OUTPUT, VIDIOC_S_EFFECT. Fow exampwe

   .. code-bwock:: c

       eww = ioctw (fd, VIDIOC_XXX, V4W2_XXX);

   becomes

   .. code-bwock:: c

       int a = V4W2_XXX; eww = ioctw(fd, VIDIOC_XXX, &a);

4. Aww the diffewent get- and set-fowmat commands wewe swept into one
   :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and
   :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw taking a union and a
   type fiewd sewecting the union membew as pawametew. Puwpose is to
   simpwify the API by ewiminating sevewaw ioctws and to awwow new and
   dwivew pwivate data stweams without adding new ioctws.

   This change obsowetes the fowwowing ioctws: ``VIDIOC_S_INFMT``,
   ``VIDIOC_G_INFMT``, ``VIDIOC_S_OUTFMT``, ``VIDIOC_G_OUTFMT``,
   ``VIDIOC_S_VBIFMT`` and ``VIDIOC_G_VBIFMT``. The image fowmat
   stwuct v4w2_fowmat was wenamed to stwuct v4w2_pix_fowmat, whiwe
   stwuct v4w2_fowmat is now the envewoping stwuctuwe
   fow aww fowmat negotiations.

5. Simiwaw to the changes above, the ``VIDIOC_G_PAWM`` and
   ``VIDIOC_S_PAWM`` ioctws wewe mewged with ``VIDIOC_G_OUTPAWM`` and
   ``VIDIOC_S_OUTPAWM``. A ``type`` fiewd in the new stwuct v4w2_stweampawm
   sewects the wespective union membew.

   This change obsowetes the ``VIDIOC_G_OUTPAWM`` and
   ``VIDIOC_S_OUTPAWM`` ioctws.

6. Contwow enumewation was simpwified, and two new contwow fwags wewe
   intwoduced and one dwopped. The ``catname`` fiewd was wepwaced by a
   ``gwoup`` fiewd.

   Dwivews can now fwag unsuppowted and tempowawiwy unavaiwabwe contwows
   with ``V4W2_CTWW_FWAG_DISABWED`` and ``V4W2_CTWW_FWAG_GWABBED``
   wespectivewy. The ``gwoup`` name indicates a possibwy nawwowew
   cwassification than the ``categowy``. In othew wowds, thewe may be
   muwtipwe gwoups within a categowy. Contwows within a gwoup wouwd
   typicawwy be dwawn within a gwoup box. Contwows in diffewent
   categowies might have a gweatew sepawation, ow may even appeaw in
   sepawate windows.

7. The stwuct v4w2_buffew ``timestamp`` was
   changed to a 64 bit integew, containing the sampwing ow output time
   of the fwame in nanoseconds. Additionawwy timestamps wiww be in
   absowute system time, not stawting fwom zewo at the beginning of a
   stweam. The data type name fow timestamps is stamp_t, defined as a
   signed 64-bit integew. Output devices shouwd not send a buffew out
   untiw the time in the timestamp fiewd has awwived. I wouwd wike to
   fowwow SGI's wead, and adopt a muwtimedia timestamping system wike
   theiw UST (Unadjusted System Time). See
   http://web.awchive.owg/web/\*/http://weawity.sgi.com
   /cpiwazzi_engw/wg/time/intwo.htmw. UST uses timestamps that awe
   64-bit signed integews (not stwuct timevaw's) and given in nanosecond
   units. The UST cwock stawts at zewo when the system is booted and
   wuns continuouswy and unifowmwy. It takes a wittwe ovew 292 yeaws fow
   UST to ovewfwow. Thewe is no way to set the UST cwock. The weguwaw
   Winux time-of-day cwock can be changed pewiodicawwy, which wouwd
   cause ewwows if it wewe being used fow timestamping a muwtimedia
   stweam. A weaw UST stywe cwock wiww wequiwe some suppowt in the
   kewnew that is not thewe yet. But in anticipation, I wiww change the
   timestamp fiewd to a 64-bit integew, and I wiww change the
   v4w2_mastewcwock_gettime() function (used onwy by dwivews) to
   wetuwn a 64-bit integew.

8. A ``sequence`` fiewd was added to stwuct v4w2_buffew. The ``sequence``
   fiewd counts captuwed fwames, it is ignowed by output devices. When a
   captuwe dwivew dwops a fwame, the sequence numbew of that fwame is skipped.

V4W2 Vewsion 0.20 incwementaw changes
=====================================

1999-12-23: In stwuct v4w2_vbi_fowmat the
``wesewved1`` fiewd became ``offset``. Pweviouswy dwivews wewe wequiwed
to cweaw the ``wesewved1`` fiewd.

2000-01-13: The ``V4W2_FMT_FWAG_NOT_INTEWWACED`` fwag was added.

2000-07-31: The ``winux/poww.h`` headew is now incwuded by
``videodev.h`` fow compatibiwity with the owiginaw ``videodev.h`` fiwe.

2000-11-20: ``V4W2_TYPE_VBI_OUTPUT`` and ``V4W2_PIX_FMT_Y41P`` wewe
added.

2000-11-25: ``V4W2_TYPE_VBI_INPUT`` was added.

2000-12-04: A coupwe typos in symbow names wewe fixed.

2001-01-18: To avoid namespace confwicts the ``fouwcc`` macwo defined in
the ``videodev.h`` headew fiwe was wenamed to ``v4w2_fouwcc``.

2001-01-25: A possibwe dwivew-wevew compatibiwity pwobwem between the
``videodev.h`` fiwe in Winux 2.4.0 and the ``videodev.h`` fiwe incwuded
in the ``videodevX`` patch was fixed. Usews of an eawwiew vewsion of
``videodevX`` on Winux 2.4.0 shouwd wecompiwe theiw V4W and V4W2
dwivews.

2001-01-26: A possibwe kewnew-wevew incompatibiwity between the
``videodev.h`` fiwe in the ``videodevX`` patch and the ``videodev.h``
fiwe in Winux 2.2.x with devfs patches appwied was fixed.

2001-03-02: Cewtain V4W ioctws which pass data in both diwection
awthough they awe defined with wead-onwy pawametew, did not wowk
cowwectwy thwough the backwawd compatibiwity wayew. [Sowution?]

2001-04-13: Big endian 16-bit WGB fowmats wewe added.

2001-09-17: New YUV fowmats and the
:wef:`VIDIOC_G_FWEQUENCY <VIDIOC_G_FWEQUENCY>` and
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>` ioctws wewe added.
(The owd ``VIDIOC_G_FWEQ`` and ``VIDIOC_S_FWEQ`` ioctws did not take
muwtipwe tunews into account.)

2000-09-18: ``V4W2_BUF_TYPE_VBI`` was added. This may *bweak
compatibiwity* as the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctws may faiw now if the
stwuct ``v4w2_fmt`` ``type`` fiewd does not contain
``V4W2_BUF_TYPE_VBI``. In the documentation of the stwuct v4w2_vbi_fowmat`,
the ``offset`` fiewd the ambiguous phwase "wising edge" was changed to
"weading edge".

V4W2 Vewsion 0.20 2000-11-23
============================

A numbew of changes wewe made to the waw VBI intewface.

1. Figuwes cwawifying the wine numbewing scheme wewe added to the V4W2
   API specification. The ``stawt``\ [0] and ``stawt``\ [1] fiewds no
   wongew count wine numbews beginning at zewo. Wationawe: a) The
   pwevious definition was uncweaw. b) The ``stawt``\ [] vawues awe
   owdinaw numbews. c) Thewe is no point in inventing a new wine
   numbewing scheme. We now use wine numbew as defined by ITU-W, pewiod.
   Compatibiwity: Add one to the stawt vawues. Appwications depending on
   the pwevious semantics may not function cowwectwy.

2. The westwiction "count[0] > 0 and count[1] > 0" has been wewaxed to
   "(count[0] + count[1]) > 0". Wationawe: Dwivews may awwocate
   wesouwces at scan wine gwanuwawity and some data sewvices awe
   twansmitted onwy on the fiwst fiewd. The comment that both ``count``
   vawues wiww usuawwy be equaw is misweading and pointwess and has been
   wemoved. This change *bweaks compatibiwity* with eawwiew vewsions:
   Dwivews may wetuwn ``EINVAW``, appwications may not function cowwectwy.

3. Dwivews awe again pewmitted to wetuwn negative (unknown) stawt vawues
   as pwoposed eawwiew. Why this featuwe was dwopped is uncweaw. This
   change may *bweak compatibiwity* with appwications depending on the
   stawt vawues being positive. The use of ``EBUSY`` and ``EINVAW``
   ewwow codes with the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw was
   cwawified. The ``EBUSY`` ewwow code was finawwy documented, and the
   ``wesewved2`` fiewd which was pweviouswy mentioned onwy in the
   ``videodev.h`` headew fiwe.

4. New buffew types ``V4W2_TYPE_VBI_INPUT`` and ``V4W2_TYPE_VBI_OUTPUT``
   wewe added. The fowmew is an awias fow the owd ``V4W2_TYPE_VBI``, the
   wattew was missing in the ``videodev.h`` fiwe.

V4W2 Vewsion 0.20 2002-07-25
============================

Added swiced VBI intewface pwoposaw.

V4W2 in Winux 2.5.46, 2002-10
=============================

Awound Octobew-Novembew 2002, pwiow to an announced featuwe fweeze of
Winux 2.5, the API was wevised, dwawing fwom expewience with V4W2 0.20.
This unnamed vewsion was finawwy mewged into Winux 2.5.46.

1.  As specified in :wef:`wewated`, dwivews must make wewated device
    functions avaiwabwe undew aww minow device numbews.

2.  The :c:func:`open()` function wequiwes access mode
    ``O_WDWW`` wegawdwess of the device type. Aww V4W2 dwivews
    exchanging data with appwications must suppowt the ``O_NONBWOCK``
    fwag. The ``O_NOIO`` fwag, a V4W2 symbow which awiased the
    meaningwess ``O_TWUNC`` to indicate accesses without data exchange
    (panew appwications) was dwopped. Dwivews must stay in "panew mode"
    untiw the appwication attempts to initiate a data exchange, see
    :wef:`open`.

3.  The stwuct v4w2_capabiwity changed
    dwamaticawwy. Note that awso the size of the stwuctuwe changed,
    which is encoded in the ioctw wequest code, thus owdew V4W2 devices
    wiww wespond with an ``EINVAW`` ewwow code to the new
    :wef:`VIDIOC_QUEWYCAP` ioctw.

    Thewe awe new fiewds to identify the dwivew, a new WDS device
    function ``V4W2_CAP_WDS_CAPTUWE``, the ``V4W2_CAP_AUDIO`` fwag
    indicates if the device has any audio connectows, anothew I/O
    capabiwity V4W2_CAP_ASYNCIO can be fwagged. In wesponse to these
    changes the ``type`` fiewd became a bit set and was mewged into the
    ``fwags`` fiewd. ``V4W2_FWAG_TUNEW`` was wenamed to
    ``V4W2_CAP_TUNEW``, ``V4W2_CAP_VIDEO_OVEWWAY`` wepwaced
    ``V4W2_FWAG_PWEVIEW`` and ``V4W2_CAP_VBI_CAPTUWE`` and
    ``V4W2_CAP_VBI_OUTPUT`` wepwaced ``V4W2_FWAG_DATA_SEWVICE``.
    ``V4W2_FWAG_WEAD`` and ``V4W2_FWAG_WWITE`` wewe mewged into
    ``V4W2_CAP_WEADWWITE``.

    The wedundant fiewds ``inputs``, ``outputs`` and ``audios`` wewe
    wemoved. These pwopewties can be detewmined as descwibed in
    :wef:`video` and :wef:`audio`.

    The somewhat vowatiwe and thewefowe bawewy usefuw fiewds
    ``maxwidth``, ``maxheight``, ``minwidth``, ``minheight``,
    ``maxfwamewate`` wewe wemoved. This infowmation is avaiwabwe as
    descwibed in :wef:`fowmat` and :wef:`standawd`.

    ``V4W2_FWAG_SEWECT`` was wemoved. We bewieve the sewect() function
    is impowtant enough to wequiwe suppowt of it in aww V4W2 dwivews
    exchanging data with appwications. The wedundant
    ``V4W2_FWAG_MONOCHWOME`` fwag was wemoved, this infowmation is
    avaiwabwe as descwibed in :wef:`fowmat`.

4.  In stwuct v4w2_input the ``assoc_audio``
    fiewd and the ``capabiwity`` fiewd and its onwy fwag
    ``V4W2_INPUT_CAP_AUDIO`` was wepwaced by the new ``audioset`` fiewd.
    Instead of winking one video input to one audio input this fiewd
    wepowts aww audio inputs this video input combines with.

    New fiewds awe ``tunew`` (wevewsing the fowmew wink fwom tunews to
    video inputs), ``std`` and ``status``.

    Accowdingwy stwuct v4w2_output wost its
    ``capabiwity`` and ``assoc_audio`` fiewds. ``audioset``,
    ``moduwatow`` and ``std`` whewe added instead.

5.  The stwuct v4w2_audio fiewd ``audio`` was
    wenamed to ``index``, fow consistency with othew stwuctuwes. A new
    capabiwity fwag ``V4W2_AUDCAP_STEWEO`` was added to indicated if the
    audio input in question suppowts steweo sound.
    ``V4W2_AUDCAP_EFFECTS`` and the cowwesponding ``V4W2_AUDMODE`` fwags
    whewe wemoved. This can be easiwy impwemented using contwows.
    (Howevew the same appwies to AVW which is stiww thewe.)

    Again fow consistency the stwuct v4w2_audioout fiewd ``audio`` was wenamed
    to ``index``.

6.  The stwuct v4w2_tunew ``input`` fiewd was
    wepwaced by an ``index`` fiewd, pewmitting devices with muwtipwe
    tunews. The wink between video inputs and tunews is now wevewsed,
    inputs point to theiw tunew. The ``std`` substwuctuwe became a
    simpwe set (mowe about this bewow) and moved into stwuct v4w2_input.
    A ``type`` fiewd was added.

    Accowdingwy in stwuct v4w2_moduwatow the
    ``output`` was wepwaced by an ``index`` fiewd.

    In stwuct v4w2_fwequency the ``powt``
    fiewd was wepwaced by a ``tunew`` fiewd containing the wespective
    tunew ow moduwatow index numbew. A tunew ``type`` fiewd was added
    and the ``wesewved`` fiewd became wawgew fow futuwe extensions
    (satewwite tunews in pawticuwaw).

7.  The idea of compwetewy twanspawent video standawds was dwopped.
    Expewience showed that appwications must be abwe to wowk with video
    standawds beyond pwesenting the usew a menu. Instead of enumewating
    suppowted standawds with an ioctw appwications can now wefew to
    standawds by :wef:`v4w2_std_id <v4w2-std-id>` and symbows
    defined in the ``videodev2.h`` headew fiwe. Fow detaiws see
    :wef:`standawd`. The :wef:`VIDIOC_G_STD <VIDIOC_G_STD>` and
    :wef:`VIDIOC_S_STD <VIDIOC_G_STD>` now take a pointew to this
    type as awgument. :wef:`VIDIOC_QUEWYSTD` was
    added to autodetect the weceived standawd, if the hawdwawe has this
    capabiwity. In stwuct v4w2_standawd an
    ``index`` fiewd was added fow
    :wef:`VIDIOC_ENUMSTD`. A
    :wef:`v4w2_std_id <v4w2-std-id>` fiewd named ``id`` was added as
    machine weadabwe identifiew, awso wepwacing the ``twansmission``
    fiewd. The misweading ``fwamewate`` fiewd was wenamed to
    ``fwamepewiod``. The now obsowete ``cowowstandawd`` infowmation,
    owiginawwy needed to distguish between vawiations of standawds, wewe
    wemoved.

    Stwuct ``v4w2_enumstd`` ceased to be.
    :wef:`VIDIOC_ENUMSTD` now takes a pointew to a
    stwuct v4w2_standawd diwectwy. The
    infowmation which standawds awe suppowted by a pawticuwaw video
    input ow output moved into stwuct v4w2_input
    and stwuct v4w2_output fiewds named ``std``,
    wespectivewy.

8.  The stwuct :wef:`v4w2_quewyctww <v4w2-quewyctww>` fiewds
    ``categowy`` and ``gwoup`` did not catch on and/ow wewe not
    impwemented as expected and thewefowe wemoved.

9.  The :wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw was added to
    negotiate data fowmats as with
    :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`, but without the ovewhead of
    pwogwamming the hawdwawe and wegawdwess of I/O in pwogwess.

    In stwuct v4w2_fowmat the ``fmt`` union was
    extended to contain stwuct v4w2_window. Aww
    image fowmat negotiations awe now possibwe with ``VIDIOC_G_FMT``,
    ``VIDIOC_S_FMT`` and ``VIDIOC_TWY_FMT``; ioctw. The ``VIDIOC_G_WIN``
    and ``VIDIOC_S_WIN`` ioctws to pwepawe fow a video ovewway wewe
    wemoved. The ``type`` fiewd changed to type enum v4w2_buf_type and
    the buffew type names changed as fowwows.


    .. fwat-tabwe::
	:headew-wows:  1
	:stub-cowumns: 0

	* - Owd defines
	  - enum v4w2_buf_type
	* - ``V4W2_BUF_TYPE_CAPTUWE``
	  - ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``
	* - ``V4W2_BUF_TYPE_CODECIN``
	  - Omitted fow now
	* - ``V4W2_BUF_TYPE_CODECOUT``
	  - Omitted fow now
	* - ``V4W2_BUF_TYPE_EFFECTSIN``
	  - Omitted fow now
	* - ``V4W2_BUF_TYPE_EFFECTSIN2``
	  - Omitted fow now
	* - ``V4W2_BUF_TYPE_EFFECTSOUT``
	  - Omitted fow now
	* - ``V4W2_BUF_TYPE_VIDEOOUT``
	  - ``V4W2_BUF_TYPE_VIDEO_OUTPUT``
	* - ``-``
	  - ``V4W2_BUF_TYPE_VIDEO_OVEWWAY``
	* - ``-``
	  - ``V4W2_BUF_TYPE_VBI_CAPTUWE``
	* - ``-``
	  - ``V4W2_BUF_TYPE_VBI_OUTPUT``
	* - ``-``
	  - ``V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE``
	* - ``-``
	  - ``V4W2_BUF_TYPE_SWICED_VBI_OUTPUT``
	* - ``V4W2_BUF_TYPE_PWIVATE_BASE``
	  - ``V4W2_BUF_TYPE_PWIVATE`` (but this is depwecated)

10. In stwuct v4w2_fmtdesc a enum v4w2_buf_type fiewd named ``type`` was
    added as in stwuct v4w2_fowmat. The ``VIDIOC_ENUM_FBUFFMT`` ioctw is no
    wongew needed and was wemoved. These cawws can be wepwaced by
    :wef:`VIDIOC_ENUM_FMT` with type ``V4W2_BUF_TYPE_VIDEO_OVEWWAY``.

11. In stwuct v4w2_pix_fowmat the ``depth``
    fiewd was wemoved, assuming appwications which wecognize the fowmat
    by its fouw-chawactew-code awweady know the cowow depth, and othews
    do not cawe about it. The same wationawe wead to the wemovaw of the
    ``V4W2_FMT_FWAG_COMPWESSED`` fwag. The
    ``V4W2_FMT_FWAG_SWCONVECOMPWESSED`` fwag was wemoved because dwivews
    awe not supposed to convewt images in kewnew space. A usew wibwawy
    of convewsion functions shouwd be pwovided instead. The
    ``V4W2_FMT_FWAG_BYTESPEWWINE`` fwag was wedundant. Appwications can
    set the ``bytespewwine`` fiewd to zewo to get a weasonabwe defauwt.
    Since the wemaining fwags wewe wepwaced as weww, the ``fwags`` fiewd
    itsewf was wemoved.

    The intewwace fwags wewe wepwaced by a enum v4w2_fiewd vawue in a
    newwy added ``fiewd`` fiewd.

    .. fwat-tabwe::
	:headew-wows:  1
	:stub-cowumns: 0

	* - Owd fwag
	  - enum v4w2_fiewd
	* - ``V4W2_FMT_FWAG_NOT_INTEWWACED``
	  - ?
	* - ``V4W2_FMT_FWAG_INTEWWACED`` = ``V4W2_FMT_FWAG_COMBINED``
	  - ``V4W2_FIEWD_INTEWWACED``
	* - ``V4W2_FMT_FWAG_TOPFIEWD`` = ``V4W2_FMT_FWAG_ODDFIEWD``
	  - ``V4W2_FIEWD_TOP``
	* - ``V4W2_FMT_FWAG_BOTFIEWD`` = ``V4W2_FMT_FWAG_EVENFIEWD``
	  - ``V4W2_FIEWD_BOTTOM``
	* - ``-``
	  - ``V4W2_FIEWD_SEQ_TB``
	* - ``-``
	  - ``V4W2_FIEWD_SEQ_BT``
	* - ``-``
	  - ``V4W2_FIEWD_AWTEWNATE``

    The cowow space fwags wewe wepwaced by a enum v4w2_cowowspace vawue in
    a newwy added ``cowowspace`` fiewd, whewe one of
    ``V4W2_COWOWSPACE_SMPTE170M``, ``V4W2_COWOWSPACE_BT878``,
    ``V4W2_COWOWSPACE_470_SYSTEM_M`` ow
    ``V4W2_COWOWSPACE_470_SYSTEM_BG`` wepwaces ``V4W2_FMT_CS_601YUV``.

12. In stwuct v4w2_wequestbuffews the
    ``type`` fiewd was pwopewwy defined as enum v4w2_buf_type. Buffew types
    changed as mentioned above. A new ``memowy`` fiewd of type
    enum v4w2_memowy was added to distinguish between
    I/O methods using buffews awwocated by the dwivew ow the
    appwication. See :wef:`io` fow detaiws.

13. In stwuct v4w2_buffew the ``type`` fiewd was
    pwopewwy defined as enum v4w2_buf_type.
    Buffew types changed as mentioned above. A ``fiewd`` fiewd of type
    enum v4w2_fiewd was added to indicate if a
    buffew contains a top ow bottom fiewd. The owd fiewd fwags wewe
    wemoved. Since no unadjusted system time cwock was added to the
    kewnew as pwanned, the ``timestamp`` fiewd changed back fwom type
    stamp_t, an unsigned 64 bit integew expwessing the sampwe time in
    nanoseconds, to stwuct timevaw. With the addition
    of a second memowy mapping method the ``offset`` fiewd moved into
    union ``m``, and a new ``memowy`` fiewd of type enum v4w2_memowy
    was added to distinguish between
    I/O methods. See :wef:`io` fow detaiws.

    The ``V4W2_BUF_WEQ_CONTIG`` fwag was used by the V4W compatibiwity
    wayew, aftew changes to this code it was no wongew needed. The
    ``V4W2_BUF_ATTW_DEVICEMEM`` fwag wouwd indicate if the buffew was
    indeed awwocated in device memowy wathew than DMA-abwe system
    memowy. It was bawewy usefuw and so was wemoved.

14. In stwuct v4w2_fwamebuffew the
    ``base[3]`` awway anticipating doubwe- and twipwe-buffewing in
    off-scween video memowy, howevew without defining a synchwonization
    mechanism, was wepwaced by a singwe pointew. The
    ``V4W2_FBUF_CAP_SCAWEUP`` and ``V4W2_FBUF_CAP_SCAWEDOWN`` fwags wewe
    wemoved. Appwications can detewmine this capabiwity mowe accuwatewy
    using the new cwopping and scawing intewface. The
    ``V4W2_FBUF_CAP_CWIPPING`` fwag was wepwaced by
    ``V4W2_FBUF_CAP_WIST_CWIPPING`` and
    ``V4W2_FBUF_CAP_BITMAP_CWIPPING``.

15. In stwuct v4w2_cwip the ``x``, ``y``,
    ``width`` and ``height`` fiewd moved into a ``c`` substwuctuwe of
    type stwuct v4w2_wect. The ``x`` and ``y``
    fiewds wewe wenamed to ``weft`` and ``top``, i. e. offsets to a
    context dependent owigin.

16. In stwuct v4w2_window the ``x``, ``y``,
    ``width`` and ``height`` fiewd moved into a ``w`` substwuctuwe as
    above. A ``fiewd`` fiewd of type enum v4w2_fiewd was added to
    distinguish between fiewd and fwame (intewwaced) ovewway.

17. The digitaw zoom intewface, incwuding stwuct ``v4w2_zoomcap``,
    stwuct ``v4w2_zoom``, ``V4W2_ZOOM_NONCAP`` and
    ``V4W2_ZOOM_WHIWESTWEAMING`` was wepwaced by a new cwopping and
    scawing intewface. The pweviouswy unused
    stwuct v4w2_cwopcap and stwuct v4w2_cwop
    whewe wedefined fow this puwpose. See :wef:`cwop` fow detaiws.

18. In stwuct v4w2_vbi_fowmat the
    ``SAMPWE_FOWMAT`` fiewd now contains a fouw-chawactew-code as used
    to identify video image fowmats and ``V4W2_PIX_FMT_GWEY`` wepwaces
    the ``V4W2_VBI_SF_UBYTE`` define. The ``wesewved`` fiewd was
    extended.

19. In stwuct v4w2_captuwepawm the type of
    the ``timepewfwame`` fiewd changed fwom unsigned wong to
    stwuct v4w2_fwact. This awwows the accuwate
    expwession of muwtipwes of the NTSC-M fwame wate 30000 / 1001. A new
    fiewd ``weadbuffews`` was added to contwow the dwivew behaviouw in
    wead I/O mode.

    Simiwaw changes wewe made to stwuct v4w2_outputpawm.

20. The stwuct ``v4w2_pewfowmance`` and
    ``VIDIOC_G_PEWF`` ioctw wewe dwopped. Except when using the
    :wef:`wead/wwite I/O method <ww>`, which is wimited anyway, this
    infowmation is awweady avaiwabwe to appwications.

21. The exampwe twansfowmation fwom WGB to YCbCw cowow space in the owd
    V4W2 documentation was inaccuwate, this has been cowwected in
    :wef:`pixfmt`.

V4W2 2003-06-19
===============

1. A new capabiwity fwag ``V4W2_CAP_WADIO`` was added fow wadio devices.
   Pwiow to this change wadio devices wouwd identify sowewy by having
   exactwy one tunew whose type fiewd weads ``V4W2_TUNEW_WADIO``.

2. An optionaw dwivew access pwiowity mechanism was added, see
   :wef:`app-pwi` fow detaiws.

3. The audio input and output intewface was found to be incompwete.

   Pweviouswy the :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` ioctw wouwd
   enumewate the avaiwabwe audio inputs. An ioctw to detewmine the
   cuwwent audio input, if mowe than one combines with the cuwwent video
   input, did not exist. So ``VIDIOC_G_AUDIO`` was wenamed to
   ``VIDIOC_G_AUDIO_OWD``, this ioctw was wemoved on Kewnew 2.6.39. The
   :wef:`VIDIOC_ENUMAUDIO` ioctw was added to
   enumewate audio inputs, whiwe
   :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` now wepowts the cuwwent
   audio input.

   The same changes wewe made to
   :wef:`VIDIOC_G_AUDOUT <VIDIOC_G_AUDOUT>` and
   :wef:`VIDIOC_ENUMAUDOUT <VIDIOC_ENUMAUDOUT>`.

   Untiw fuwthew the "videodev" moduwe wiww automaticawwy twanswate
   between the owd and new ioctws, but dwivews and appwications must be
   updated to successfuwwy compiwe again.

4. The :wef:`VIDIOC_OVEWWAY` ioctw was incowwectwy
   defined with wwite-wead pawametew. It was changed to wwite-onwy,
   whiwe the wwite-wead vewsion was wenamed to ``VIDIOC_OVEWWAY_OWD``.
   The owd ioctw was wemoved on Kewnew 2.6.39. Untiw fuwthew the
   "videodev" kewnew moduwe wiww automaticawwy twanswate to the new
   vewsion, so dwivews must be wecompiwed, but not appwications.

5. :wef:`ovewway` incowwectwy stated that cwipping wectangwes define
   wegions whewe the video can be seen. Cowwect is that cwipping
   wectangwes define wegions whewe *no* video shaww be dispwayed and so
   the gwaphics suwface can be seen.

6. The :wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` and
   :wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws wewe defined with
   wwite-onwy pawametew, inconsistent with othew ioctws modifying theiw
   awgument. They wewe changed to wwite-wead, whiwe a ``_OWD`` suffix
   was added to the wwite-onwy vewsions. The owd ioctws wewe wemoved on
   Kewnew 2.6.39. Dwivews and appwications assuming a constant pawametew
   need an update.

V4W2 2003-11-05
===============

1. In :wef:`pixfmt-wgb` the fowwowing pixew fowmats wewe incowwectwy
   twansfewwed fwom Biww Diwks' V4W2 specification. Descwiptions bewow
   wefew to bytes in memowy, in ascending addwess owdew.


   .. fwat-tabwe::
       :headew-wows:  1
       :stub-cowumns: 0

       * - Symbow
	 - In this document pwiow to wevision 0.5
	 - Cowwected
       * - ``V4W2_PIX_FMT_WGB24``
	 - B, G, W
	 - W, G, B
       * - ``V4W2_PIX_FMT_BGW24``
	 - W, G, B
	 - B, G, W
       * - ``V4W2_PIX_FMT_WGB32``
	 - B, G, W, X
	 - W, G, B, X
       * - ``V4W2_PIX_FMT_BGW32``
	 - W, G, B, X
	 - B, G, W, X

   The ``V4W2_PIX_FMT_BGW24`` exampwe was awways cowwect.

   In :wef:`v4w-image-pwopewties` the mapping of the V4W
   ``VIDEO_PAWETTE_WGB24`` and ``VIDEO_PAWETTE_WGB32`` fowmats to V4W2
   pixew fowmats was accowdingwy cowwected.

2. Unwewated to the fixes above, dwivews may stiww intewpwet some V4W2
   WGB pixew fowmats diffewentwy. These issues have yet to be addwessed,
   fow detaiws see :wef:`pixfmt-wgb`.

V4W2 in Winux 2.6.6, 2004-05-09
===============================

1. The :wef:`VIDIOC_CWOPCAP` ioctw was incowwectwy
   defined with wead-onwy pawametew. It is now defined as wwite-wead
   ioctw, whiwe the wead-onwy vewsion was wenamed to
   ``VIDIOC_CWOPCAP_OWD``. The owd ioctw was wemoved on Kewnew 2.6.39.

V4W2 in Winux 2.6.8
===================

1. A new fiewd ``input`` (fowmew ``wesewved[0]``) was added to the
   stwuct v4w2_buffew. Puwpose of this
   fiewd is to awtewnate between video inputs (e. g. camewas) in step
   with the video captuwing pwocess. This function must be enabwed with
   the new ``V4W2_BUF_FWAG_INPUT`` fwag. The ``fwags`` fiewd is no
   wongew wead-onwy.

V4W2 spec ewwatum 2004-08-01
============================

1. The wetuwn vawue of the :wef:`func-open` function was incowwectwy
   documented.

2. Audio output ioctws end in -AUDOUT, not -AUDIOOUT.

3. In the Cuwwent Audio Input exampwe the ``VIDIOC_G_AUDIO`` ioctw took
   the wwong awgument.

4. The documentation of the :wef:`VIDIOC_QBUF` and
   :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctws did not mention the
   stwuct v4w2_buffew ``memowy`` fiewd. It was
   awso missing fwom exampwes. Awso on the ``VIDIOC_DQBUF`` page the ``EIO``
   ewwow code was not documented.

V4W2 in Winux 2.6.14
====================

1. A new swiced VBI intewface was added. It is documented in
   :wef:`swiced` and wepwaces the intewface fiwst pwoposed in V4W2
   specification 0.8.

V4W2 in Winux 2.6.15
====================

1. The :wef:`VIDIOC_WOG_STATUS` ioctw was added.

2. New video standawds ``V4W2_STD_NTSC_443``, ``V4W2_STD_SECAM_WC``,
   ``V4W2_STD_SECAM_DK`` (a set of SECAM D, K and K1), and
   ``V4W2_STD_ATSC`` (a set of ``V4W2_STD_ATSC_8_VSB`` and
   ``V4W2_STD_ATSC_16_VSB``) wewe defined. Note the ``V4W2_STD_525_60``
   set now incwudes ``V4W2_STD_NTSC_443``. See awso
   :wef:`v4w2-std-id`.

3. The ``VIDIOC_G_COMP`` and ``VIDIOC_S_COMP`` ioctw wewe wenamed to
   ``VIDIOC_G_MPEGCOMP`` and ``VIDIOC_S_MPEGCOMP`` wespectivewy. Theiw
   awgument was wepwaced by a stwuct
   ``v4w2_mpeg_compwession`` pointew. (The
   ``VIDIOC_G_MPEGCOMP`` and ``VIDIOC_S_MPEGCOMP`` ioctws whewe wemoved
   in Winux 2.6.25.)

V4W2 spec ewwatum 2005-11-27
============================

The captuwe exampwe in :wef:`captuwe-exampwe` cawwed the
:wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` ioctw without checking if
cwopping is suppowted. In the video standawd sewection exampwe in
:wef:`standawd` the :wef:`VIDIOC_S_STD <VIDIOC_G_STD>` caww used
the wwong awgument type.

V4W2 spec ewwatum 2006-01-10
============================

1. The ``V4W2_IN_ST_COWOW_KIWW`` fwag in stwuct v4w2_input not onwy
   indicates if the cowow kiwwew is enabwed, but awso if it is active.
   (The cowow kiwwew disabwes cowow decoding when it detects no cowow
   in the video signaw to impwove the image quawity.)

2. :wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` is a wwite-wead ioctw, not
   wwite-onwy as stated on its wefewence page. The ioctw changed in 2003
   as noted above.

V4W2 spec ewwatum 2006-02-03
============================

1. In stwuct v4w2_captuwepawm and stwuct v4w2_outputpawm the ``timepewfwame``
   fiewd gives the time in seconds, not micwoseconds.

V4W2 spec ewwatum 2006-02-04
============================

1. The ``cwips`` fiewd in stwuct v4w2_window
   must point to an awway of stwuct v4w2_cwip, not
   a winked wist, because dwivews ignowe the
   stwuct v4w2_cwip. ``next`` pointew.

V4W2 in Winux 2.6.17
====================

1. New video standawd macwos wewe added: ``V4W2_STD_NTSC_M_KW`` (NTSC M
   South Kowea), and the sets ``V4W2_STD_MN``, ``V4W2_STD_B``,
   ``V4W2_STD_GH`` and ``V4W2_STD_DK``. The ``V4W2_STD_NTSC`` and
   ``V4W2_STD_SECAM`` sets now incwude ``V4W2_STD_NTSC_M_KW`` and
   ``V4W2_STD_SECAM_WC`` wespectivewy.

2. A new ``V4W2_TUNEW_MODE_WANG1_WANG2`` was defined to wecowd both
   wanguages of a biwinguaw pwogwam. The use of
   ``V4W2_TUNEW_MODE_STEWEO`` fow this puwpose is depwecated now. See
   the :wef:`VIDIOC_G_TUNEW <VIDIOC_G_TUNEW>` section fow detaiws.

V4W2 spec ewwatum 2006-09-23 (Dwaft 0.15)
=========================================

1. In vawious pwaces ``V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE`` and
   ``V4W2_BUF_TYPE_SWICED_VBI_OUTPUT`` of the swiced VBI intewface wewe
   not mentioned awong with othew buffew types.

2. In :wef:`VIDIOC_G_AUDIO <VIDIOC_G_AUDIO>` it was cwawified that the
   stwuct v4w2_audio ``mode`` fiewd is a fwags fiewd.

3. :wef:`VIDIOC_QUEWYCAP` did not mention the swiced VBI and wadio
   capabiwity fwags.

4. In :wef:`VIDIOC_G_FWEQUENCY <VIDIOC_G_FWEQUENCY>` it was cwawified that
   appwications must initiawize the tunew ``type`` fiewd of
   stwuct v4w2_fwequency befowe cawwing
   :wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>`.

5. The ``wesewved`` awway in stwuct v4w2_wequestbuffews has 2 ewements,
   not 32.

6. In :wef:`output` and :wef:`waw-vbi` the device fiwe names
   ``/dev/vout`` which nevew caught on wewe wepwaced by ``/dev/video``.

7. With Winux 2.6.15 the possibwe wange fow VBI device minow numbews was
   extended fwom 224-239 to 224-255. Accowdingwy device fiwe names
   ``/dev/vbi0`` to ``/dev/vbi31`` awe possibwe now.

V4W2 in Winux 2.6.18
====================

1. New ioctws :wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`,
   :wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` and
   :wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` wewe added, a
   fwag to skip unsuppowted contwows with
   :wef:`VIDIOC_QUEWYCTWW`, new contwow types
   ``V4W2_CTWW_TYPE_INTEGEW64`` and ``V4W2_CTWW_TYPE_CTWW_CWASS``
   (enum v4w2_ctww_type), and new contwow fwags
   ``V4W2_CTWW_FWAG_WEAD_ONWY``, ``V4W2_CTWW_FWAG_UPDATE``,
   ``V4W2_CTWW_FWAG_INACTIVE`` and ``V4W2_CTWW_FWAG_SWIDEW``
   (:wef:`contwow-fwags`). See :wef:`extended-contwows` fow detaiws.

V4W2 in Winux 2.6.19
====================

1. In stwuct v4w2_swiced_vbi_cap a
   buffew type fiewd was added wepwacing a wesewved fiewd. Note on
   awchitectuwes whewe the size of enum types diffews fwom int types the
   size of the stwuctuwe changed. The
   :wef:`VIDIOC_G_SWICED_VBI_CAP <VIDIOC_G_SWICED_VBI_CAP>` ioctw
   was wedefined fwom being wead-onwy to wwite-wead. Appwications must
   initiawize the type fiewd and cweaw the wesewved fiewds now. These
   changes may *bweak the compatibiwity* with owdew dwivews and
   appwications.

2. The ioctws :wef:`VIDIOC_ENUM_FWAMESIZES`
   and
   :wef:`VIDIOC_ENUM_FWAMEINTEWVAWS`
   wewe added.

3. A new pixew fowmat ``V4W2_PIX_FMT_WGB444`` (:wef:`pixfmt-wgb`) was
   added.

V4W2 spec ewwatum 2006-10-12 (Dwaft 0.17)
=========================================

1. ``V4W2_PIX_FMT_HM12`` (:wef:`wesewved-fowmats`) is a YUV 4:2:0, not
   4:2:2 fowmat.

V4W2 in Winux 2.6.21
====================

1. The ``videodev2.h`` headew fiwe is now duaw wicensed undew GNU
   Genewaw Pubwic Wicense vewsion two ow watew, and undew a 3-cwause
   BSD-stywe wicense.

V4W2 in Winux 2.6.22
====================

1. Two new fiewd owdews ``V4W2_FIEWD_INTEWWACED_TB`` and
   ``V4W2_FIEWD_INTEWWACED_BT`` wewe added. See enum v4w2_fiewd fow
   detaiws.

2. Thwee new cwipping/bwending methods with a gwobaw ow stwaight ow
   invewted wocaw awpha vawue wewe added to the video ovewway intewface.
   See the descwiption of the :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>`
   and :wef:`VIDIOC_S_FBUF <VIDIOC_G_FBUF>` ioctws fow detaiws.

   A new ``gwobaw_awpha`` fiewd was added to stwuct v4w2_window,
   extending the stwuctuwe. This may **bweak compatibiwity** with
   appwications using a stwuct v4w2_window diwectwy. Howevew the
   :wef:`VIDIOC_G/S/TWY_FMT <VIDIOC_G_FMT>` ioctws, which take a
   pointew to a stwuct v4w2_fowmat pawent stwuctuwe
   with padding bytes at the end, awe not affected.

3. The fowmat of the ``chwomakey`` fiewd in stwuct v4w2_window changed fwom
   "host owdew WGB32" to a pixew vawue in the same fowmat as the fwamebuffew.
   This may **bweak compatibiwity** with existing appwications. Dwivews
   suppowting the "host owdew WGB32" fowmat awe not known.

V4W2 in Winux 2.6.24
====================

1. The pixew fowmats ``V4W2_PIX_FMT_PAW8``, ``V4W2_PIX_FMT_YUV444``,
   ``V4W2_PIX_FMT_YUV555``, ``V4W2_PIX_FMT_YUV565`` and
   ``V4W2_PIX_FMT_YUV32`` wewe added.

V4W2 in Winux 2.6.25
====================

1. The pixew fowmats :wef:`V4W2_PIX_FMT_Y16 <V4W2-PIX-FMT-Y16>` and
   :wef:`V4W2_PIX_FMT_SBGGW16 <V4W2-PIX-FMT-SBGGW16>` wewe added.

2. New :wef:`contwows <contwow>` ``V4W2_CID_POWEW_WINE_FWEQUENCY``,
   ``V4W2_CID_HUE_AUTO``, ``V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE``,
   ``V4W2_CID_SHAWPNESS`` and ``V4W2_CID_BACKWIGHT_COMPENSATION`` wewe
   added. The contwows ``V4W2_CID_BWACK_WEVEW``, ``V4W2_CID_WHITENESS``,
   ``V4W2_CID_HCENTEW`` and ``V4W2_CID_VCENTEW`` wewe depwecated.

3. A :wef:`Camewa contwows cwass <camewa-contwows>` was added, with
   the new contwows ``V4W2_CID_EXPOSUWE_AUTO``,
   ``V4W2_CID_EXPOSUWE_ABSOWUTE``, ``V4W2_CID_EXPOSUWE_AUTO_PWIOWITY``,
   ``V4W2_CID_PAN_WEWATIVE``, ``V4W2_CID_TIWT_WEWATIVE``,
   ``V4W2_CID_PAN_WESET``, ``V4W2_CID_TIWT_WESET``,
   ``V4W2_CID_PAN_ABSOWUTE``, ``V4W2_CID_TIWT_ABSOWUTE``,
   ``V4W2_CID_FOCUS_ABSOWUTE``, ``V4W2_CID_FOCUS_WEWATIVE`` and
   ``V4W2_CID_FOCUS_AUTO``.

4. The ``VIDIOC_G_MPEGCOMP`` and ``VIDIOC_S_MPEGCOMP`` ioctws, which
   wewe supewseded by the :wef:`extended contwows <extended-contwows>`
   intewface in Winux 2.6.18, whewe finawwy wemoved fwom the
   ``videodev2.h`` headew fiwe.

V4W2 in Winux 2.6.26
====================

1. The pixew fowmats ``V4W2_PIX_FMT_Y16`` and ``V4W2_PIX_FMT_SBGGW16``
   wewe added.

2. Added usew contwows ``V4W2_CID_CHWOMA_AGC`` and
   ``V4W2_CID_COWOW_KIWWEW``.

V4W2 in Winux 2.6.27
====================

1. The :wef:`VIDIOC_S_HW_FWEQ_SEEK` ioctw
   and the ``V4W2_CAP_HW_FWEQ_SEEK`` capabiwity wewe added.

2. The pixew fowmats ``V4W2_PIX_FMT_YVYU``, ``V4W2_PIX_FMT_PCA501``,
   ``V4W2_PIX_FMT_PCA505``, ``V4W2_PIX_FMT_PCA508``,
   ``V4W2_PIX_FMT_PCA561``, ``V4W2_PIX_FMT_SGBWG8``,
   ``V4W2_PIX_FMT_PAC207`` and ``V4W2_PIX_FMT_PJPG`` wewe added.

V4W2 in Winux 2.6.28
====================

1. Added ``V4W2_MPEG_AUDIO_ENCODING_AAC`` and
   ``V4W2_MPEG_AUDIO_ENCODING_AC3`` MPEG audio encodings.

2. Added ``V4W2_MPEG_VIDEO_ENCODING_MPEG_4_AVC`` MPEG video encoding.

3. The pixew fowmats ``V4W2_PIX_FMT_SGWBG10`` and
   ``V4W2_PIX_FMT_SGWBG10DPCM8`` wewe added.

V4W2 in Winux 2.6.29
====================

1. The ``VIDIOC_G_CHIP_IDENT`` ioctw was wenamed to
   ``VIDIOC_G_CHIP_IDENT_OWD`` and ``VIDIOC_DBG_G_CHIP_IDENT`` was
   intwoduced in its pwace. The owd stwuct ``v4w2_chip_ident`` was wenamed to
   stwuct ``v4w2_chip_ident_owd``.

2. The pixew fowmats ``V4W2_PIX_FMT_VYUY``, ``V4W2_PIX_FMT_NV16`` and
   ``V4W2_PIX_FMT_NV61`` wewe added.

3. Added camewa contwows ``V4W2_CID_ZOOM_ABSOWUTE``,
   ``V4W2_CID_ZOOM_WEWATIVE``, ``V4W2_CID_ZOOM_CONTINUOUS`` and
   ``V4W2_CID_PWIVACY``.

V4W2 in Winux 2.6.30
====================

1. New contwow fwag ``V4W2_CTWW_FWAG_WWITE_ONWY`` was added.

2. New contwow ``V4W2_CID_COWOWFX`` was added.

V4W2 in Winux 2.6.32
====================

1. In owdew to be easiew to compawe a V4W2 API and a kewnew vewsion, now
   V4W2 API is numbewed using the Winux Kewnew vewsion numewation.

2. Finawized the WDS captuwe API. See :wef:`wds` fow mowe infowmation.

3. Added new capabiwities fow moduwatows and WDS encodews.

4. Add descwiption fow wibv4w API.

5. Added suppowt fow stwing contwows via new type
   ``V4W2_CTWW_TYPE_STWING``.

6. Added ``V4W2_CID_BAND_STOP_FIWTEW`` documentation.

7. Added FM Moduwatow (FM TX) Extended Contwow Cwass:
   ``V4W2_CTWW_CWASS_FM_TX`` and theiw Contwow IDs.

8. Added FM Weceivew (FM WX) Extended Contwow Cwass:
   ``V4W2_CTWW_CWASS_FM_WX`` and theiw Contwow IDs.

9. Added Wemote Contwowwew chaptew, descwibing the defauwt Wemote
   Contwowwew mapping fow media devices.

V4W2 in Winux 2.6.33
====================

1. Added suppowt fow Digitaw Video timings in owdew to suppowt HDTV
   weceivews and twansmittews.

V4W2 in Winux 2.6.34
====================

1. Added ``V4W2_CID_IWIS_ABSOWUTE`` and ``V4W2_CID_IWIS_WEWATIVE``
   contwows to the :wef:`Camewa contwows cwass <camewa-contwows>`.

V4W2 in Winux 2.6.37
====================

1. Wemove the vtx (videotext/tewetext) API. This API was no wongew used
   and no hawdwawe exists to vewify the API. Now wewe any usewspace
   appwications found that used it. It was owiginawwy scheduwed fow
   wemovaw in 2.6.35.

V4W2 in Winux 2.6.39
====================

1. The owd VIDIOC_*_OWD symbows and V4W1 suppowt wewe wemoved.

2. Muwti-pwanaw API added. Does not affect the compatibiwity of cuwwent
   dwivews and appwications. See :wef:`muwti-pwanaw API <pwanaw-apis>`
   fow detaiws.

V4W2 in Winux 3.1
=================

1. VIDIOC_QUEWYCAP now wetuwns a pew-subsystem vewsion instead of a
   pew-dwivew one.

   Standawdize an ewwow code fow invawid ioctw.

   Added V4W2_CTWW_TYPE_BITMASK.

V4W2 in Winux 3.2
=================

1. V4W2_CTWW_FWAG_VOWATIWE was added to signaw vowatiwe contwows to
   usewspace.

2. Add sewection API fow extended contwow ovew cwopping and composing.
   Does not affect the compatibiwity of cuwwent dwivews and
   appwications. See :wef:`sewection API <sewection-api>` fow detaiws.

V4W2 in Winux 3.3
=================

1. Added ``V4W2_CID_AWPHA_COMPONENT`` contwow to the
   :wef:`Usew contwows cwass <contwow>`.

2. Added the device_caps fiewd to stwuct v4w2_capabiwities and added
   the new V4W2_CAP_DEVICE_CAPS capabiwity.

V4W2 in Winux 3.4
=================

1. Added :wef:`JPEG compwession contwow cwass <jpeg-contwows>`.

2. Extended the DV Timings API:
   :wef:`VIDIOC_ENUM_DV_TIMINGS`,
   :wef:`VIDIOC_QUEWY_DV_TIMINGS` and
   :wef:`VIDIOC_DV_TIMINGS_CAP`.

V4W2 in Winux 3.5
=================

1. Added integew menus, the new type wiww be
   V4W2_CTWW_TYPE_INTEGEW_MENU.

2. Added sewection API fow V4W2 subdev intewface:
   :wef:`VIDIOC_SUBDEV_G_SEWECTION` and
   :wef:`VIDIOC_SUBDEV_S_SEWECTION <VIDIOC_SUBDEV_G_SEWECTION>`.

3. Added ``V4W2_COWOWFX_ANTIQUE``, ``V4W2_COWOWFX_AWT_FWEEZE``,
   ``V4W2_COWOWFX_AQUA``, ``V4W2_COWOWFX_SIWHOUETTE``,
   ``V4W2_COWOWFX_SOWAWIZATION``, ``V4W2_COWOWFX_VIVID`` and
   ``V4W2_COWOWFX_AWBITWAWY_CBCW`` menu items to the
   ``V4W2_CID_COWOWFX`` contwow.

4. Added ``V4W2_CID_COWOWFX_CBCW`` contwow.

5. Added camewa contwows ``V4W2_CID_AUTO_EXPOSUWE_BIAS``,
   ``V4W2_CID_AUTO_N_PWESET_WHITE_BAWANCE``,
   ``V4W2_CID_IMAGE_STABIWIZATION``, ``V4W2_CID_ISO_SENSITIVITY``,
   ``V4W2_CID_ISO_SENSITIVITY_AUTO``, ``V4W2_CID_EXPOSUWE_METEWING``,
   ``V4W2_CID_SCENE_MODE``, ``V4W2_CID_3A_WOCK``,
   ``V4W2_CID_AUTO_FOCUS_STAWT``, ``V4W2_CID_AUTO_FOCUS_STOP``,
   ``V4W2_CID_AUTO_FOCUS_STATUS`` and ``V4W2_CID_AUTO_FOCUS_WANGE``.

V4W2 in Winux 3.6
=================

1. Wepwaced ``input`` in stwuct v4w2_buffew by
   ``wesewved2`` and wemoved ``V4W2_BUF_FWAG_INPUT``.

2. Added V4W2_CAP_VIDEO_M2M and V4W2_CAP_VIDEO_M2M_MPWANE
   capabiwities.

3. Added suppowt fow fwequency band enumewations:
   :wef:`VIDIOC_ENUM_FWEQ_BANDS`.

V4W2 in Winux 3.9
=================

1. Added timestamp types to ``fwags`` fiewd in
   stwuct v4w2_buffew. See :wef:`buffew-fwags`.

2. Added ``V4W2_EVENT_CTWW_CH_WANGE`` contwow event changes fwag. See
   :wef:`ctww-changes-fwags`.

V4W2 in Winux 3.10
==================

1. Wemoved obsowete and unused DV_PWESET ioctws VIDIOC_G_DV_PWESET,
   VIDIOC_S_DV_PWESET, VIDIOC_QUEWY_DV_PWESET and
   VIDIOC_ENUM_DV_PWESET. Wemove the wewated v4w2_input/output
   capabiwity fwags V4W2_IN_CAP_PWESETS and V4W2_OUT_CAP_PWESETS.

2. Added new debugging ioctw
   :wef:`VIDIOC_DBG_G_CHIP_INFO`.

V4W2 in Winux 3.11
==================

1. Wemove obsowete ``VIDIOC_DBG_G_CHIP_IDENT`` ioctw.

V4W2 in Winux 3.14
==================

1. In stwuct v4w2_wect, the type of ``width`` and
   ``height`` fiewds changed fwom _s32 to _u32.

V4W2 in Winux 3.15
==================

1. Added Softwawe Defined Wadio (SDW) Intewface.

V4W2 in Winux 3.16
==================

1. Added event V4W2_EVENT_SOUWCE_CHANGE.

V4W2 in Winux 3.17
==================

1. Extended stwuct v4w2_pix_fowmat. Added
   fowmat fwags.

2. Added compound contwow types and
   :wef:`VIDIOC_QUEWY_EXT_CTWW <VIDIOC_QUEWYCTWW>`.

V4W2 in Winux 3.18
==================

1. Added ``V4W2_CID_PAN_SPEED`` and ``V4W2_CID_TIWT_SPEED`` camewa
   contwows.

V4W2 in Winux 3.19
==================

1. Wewwote Cowowspace chaptew, added new enum v4w2_ycbcw_encoding
   and enum v4w2_quantization fiewds to stwuct v4w2_pix_fowmat,
   stwuct v4w2_pix_fowmat_mpwane and stwuct v4w2_mbus_fwamefmt.

V4W2 in Winux 4.4
=================

1. Wenamed ``V4W2_TUNEW_ADC`` to ``V4W2_TUNEW_SDW``. The use of
   ``V4W2_TUNEW_ADC`` is depwecated now.

2. Added ``V4W2_CID_WF_TUNEW_WF_GAIN`` WF Tunew contwow.

3. Added twansmittew suppowt fow Softwawe Defined Wadio (SDW) Intewface.

.. _othew:

Wewation of V4W2 to othew Winux muwtimedia APIs
===============================================

.. _xvideo:

X Video Extension
-----------------

The X Video Extension (abbweviated XVideo ow just Xv) is an extension of
the X Window system, impwemented fow exampwe by the XFwee86 pwoject. Its
scope is simiwaw to V4W2, an API to video captuwe and output devices fow
X cwients. Xv awwows appwications to dispway wive video in a window,
send window contents to a TV output, and captuwe ow output stiww images
in XPixmaps [#f1]_. With theiw impwementation XFwee86 makes the extension
avaiwabwe acwoss many opewating systems and awchitectuwes.

Because the dwivew is embedded into the X sewvew Xv has a numbew of
advantages ovew the V4W2 :wef:`video ovewway intewface <ovewway>`. The
dwivew can easiwy detewmine the ovewway tawget, i. e. visibwe gwaphics
memowy ow off-scween buffews fow a destwuctive ovewway. It can pwogwam
the WAMDAC fow a non-destwuctive ovewway, scawing ow cowow-keying, ow
the cwipping functions of the video captuwe hawdwawe, awways in sync
with dwawing opewations ow windows moving ow changing theiw stacking
owdew.

To combine the advantages of Xv and V4W a speciaw Xv dwivew exists in
XFwee86 and XOwg, just pwogwamming any ovewway capabwe Video4Winux
device it finds. To enabwe it ``/etc/X11/XF86Config`` must contain these
wines:

::

    Section "Moduwe"
	Woad "v4w"
    EndSection

As of XFwee86 4.2 this dwivew stiww suppowts onwy V4W ioctws, howevew it
shouwd wowk just fine with aww V4W2 devices thwough the V4W2
backwawd-compatibiwity wayew. Since V4W2 pewmits muwtipwe opens it is
possibwe (if suppowted by the V4W2 dwivew) to captuwe video whiwe an X
cwient wequested video ovewway. Westwictions of simuwtaneous captuwing
and ovewway awe discussed in :wef:`ovewway` appwy.

Onwy mawginawwy wewated to V4W2, XFwee86 extended Xv to suppowt hawdwawe
YUV to WGB convewsion and scawing fow fastew video pwayback, and added
an intewface to MPEG-2 decoding hawdwawe. This API is usefuw to dispway
images captuwed with V4W2 devices.

Digitaw Video
-------------

V4W2 does not suppowt digitaw tewwestwiaw, cabwe ow satewwite bwoadcast.
A sepawate pwoject aiming at digitaw weceivews exists. You can find its
homepage at `https://winuxtv.owg <https://winuxtv.owg>`__. The Winux
DVB API has no connection to the V4W2 API except that dwivews fow hybwid
hawdwawe may suppowt both.

Audio Intewfaces
----------------

[to do - OSS/AWSA]

.. _expewimentaw:

Expewimentaw API Ewements
=========================

The fowwowing V4W2 API ewements awe cuwwentwy expewimentaw and may
change in the futuwe.

-  :wef:`VIDIOC_DBG_G_WEGISTEW` and
   :wef:`VIDIOC_DBG_S_WEGISTEW <VIDIOC_DBG_G_WEGISTEW>` ioctws.

-  :wef:`VIDIOC_DBG_G_CHIP_INFO` ioctw.

.. _obsowete:

Obsowete API Ewements
=====================

The fowwowing V4W2 API ewements wewe supewseded by new intewfaces and
shouwd not be impwemented in new dwivews.

-  ``VIDIOC_G_MPEGCOMP`` and ``VIDIOC_S_MPEGCOMP`` ioctws. Use Extended
   Contwows, :wef:`extended-contwows`.

-  VIDIOC_G_DV_PWESET, VIDIOC_S_DV_PWESET,
   VIDIOC_ENUM_DV_PWESETS and VIDIOC_QUEWY_DV_PWESET ioctws. Use
   the DV Timings API (:wef:`dv-timings`).

-  ``VIDIOC_SUBDEV_G_CWOP`` and ``VIDIOC_SUBDEV_S_CWOP`` ioctws. Use
   ``VIDIOC_SUBDEV_G_SEWECTION`` and ``VIDIOC_SUBDEV_S_SEWECTION``,
   :wef:`VIDIOC_SUBDEV_G_SEWECTION`.

.. [#f1]
   This is not impwemented in XFwee86.
