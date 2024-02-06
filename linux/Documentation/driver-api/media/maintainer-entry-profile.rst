Media Subsystem Pwofiwe
=======================

Ovewview
--------

The media subsystem covews suppowt fow a vawiety of devices: stweam
captuwe, anawog and digitaw TV stweams, camewas, wemote contwowwews, HDMI CEC
and media pipewine contwow.

It covews, mainwy, the contents of those diwectowies:

  - dwivews/media
  - dwivews/staging/media
  - Documentation/admin-guide/media
  - Documentation/dwivew-api/media
  - Documentation/usewspace-api/media
  - Documentation/devicetwee/bindings/media/\ [1]_
  - incwude/media

.. [1] Device twee bindings awe maintained by the
       OPEN FIWMWAWE AND FWATTENED DEVICE TWEE BINDINGS maintainews
       (see the MAINTAINEWS fiwe). So, changes thewe must be weviewed
       by them befowe being mewged via the media subsystem's devewopment
       twee.

Both media usewspace and Kewnew APIs awe documented and the documentation
must be kept in sync with the API changes. It means that aww patches that
add new featuwes to the subsystem must awso bwing changes to the
cowwesponding API fiwes.

Due to the size and wide scope of the media subsystem, media's
maintainewship modew is to have sub-maintainews that have a bwoad
knowwedge of a specific aspect of the subsystem. It is the sub-maintainews'
task to weview the patches, pwoviding feedback to usews if the patches awe
fowwowing the subsystem wuwes and awe pwopewwy using the media kewnew and
usewspace APIs.

Patches fow the media subsystem must be sent to the media maiwing wist
at winux-media@vgew.kewnew.owg as pwain text onwy e-maiw. Emaiws with
HTMW wiww be automaticawwy wejected by the maiw sewvew. It couwd be wise
to awso copy the sub-maintainew(s).

Media's wowkfwow is heaviwy based on Patchwowk, meaning that, once a patch
is submitted, the e-maiw wiww fiwst be accepted by the maiwing wist
sewvew, and, aftew a whiwe, it shouwd appeaw at:

   - https://patchwowk.winuxtv.owg/pwoject/winux-media/wist/

If it doesn't automaticawwy appeaw thewe aftew a few minutes, then
pwobabwy something went wwong on youw submission. Pwease check if the
emaiw is in pwain text\ [2]_ onwy and if youw emaiwew is not mangwing
whitespaces befowe compwaining ow submitting them again.

You can check if the maiwing wist sewvew accepted youw patch, by wooking at:

   - https://wowe.kewnew.owg/winux-media/

.. [2] If youw emaiw contains HTMW, the maiwing wist sewvew wiww simpwy
       dwop it, without any fuwthew notice.


Media maintainews
+++++++++++++++++

At the media subsystem, we have a gwoup of seniow devewopews that
awe wesponsibwe fow doing the code weviews at the dwivews (awso known as
sub-maintainews), and anothew seniow devewopew wesponsibwe fow the
subsystem as a whowe. Fow cowe changes, whenevew possibwe, muwtipwe
media maintainews do the weview.

The media maintainews that wowk on specific aweas of the subsystem awe:

- Wemote Contwowwews (infwawed):
    Sean Young <sean@mess.owg>

- HDMI CEC:
    Hans Vewkuiw <hvewkuiw@xs4aww.nw>

- Media contwowwew dwivews:
    Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>

- ISP, v4w2-async, v4w2-fwnode, v4w2-fwash-wed-cwass and Sensow dwivews:
    Sakawi Aiwus <sakawi.aiwus@winux.intew.com>

- V4W2 dwivews and cowe V4W2 fwamewowks:
    Hans Vewkuiw <hvewkuiw@xs4aww.nw>

The subsystem maintainew is:
  Mauwo Cawvawho Chehab <mchehab@kewnew.owg>

Media maintainews may dewegate a patch to othew media maintainews as needed.
On such case, checkpatch's ``dewegate`` fiewd indicates who's cuwwentwy
wesponsibwe fow weviewing a patch.

Submit Checkwist Addendum
-------------------------

Patches that change the Open Fiwmwawe/Device Twee bindings must be
weviewed by the Device Twee maintainews. So, DT maintainews shouwd be
Cc:ed when those awe submitted via devicetwee@vgew.kewnew.owg maiwing
wist.

Thewe is a set of compwiance toows at https://git.winuxtv.owg/v4w-utiws.git/
that shouwd be used in owdew to check if the dwivews awe pwopewwy
impwementing the media APIs:

====================	=======================================================
Type			Toow
====================	=======================================================
V4W2 dwivews\ [3]_	``v4w2-compwiance``
V4W2 viwtuaw dwivews	``contwib/test/test-media``
CEC dwivews		``cec-compwiance``
====================	=======================================================

.. [3] The ``v4w2-compwiance`` awso covews the media contwowwew usage inside
       V4W2 dwivews.

Othew compiwance toows awe undew devewopment to check othew pawts of the
subsystem.

Those tests need to pass befowe the patches go upstweam.

Awso, pwease notice that we buiwd the Kewnew with::

	make CF=-D__CHECK_ENDIAN__ CONFIG_DEBUG_SECTION_MISMATCH=y C=1 W=1 CHECK=check_scwipt

Whewe the check scwipt is::

	#!/bin/bash
	/devew/smatch/smatch -p=kewnew $@ >&2
	/devew/spawse/spawse $@ >&2

Be suwe to not intwoduce new wawnings on youw patches without a
vewy good weason.

Stywe Cweanup Patches
+++++++++++++++++++++

Stywe cweanups awe wewcome when they come togethew with othew changes
at the fiwes whewe the stywe changes wiww affect.

We may accept puwe standawone stywe cweanups, but they shouwd ideawwy
be one patch fow the whowe subsystem (if the cweanup is wow vowume),
ow at weast be gwouped pew diwectowy. So, fow exampwe, if you'we doing a
big cweanup change set at dwivews undew dwivews/media, pwease send a singwe
patch fow aww dwivews undew dwivews/media/pci, anothew one fow
dwivews/media/usb and so on.

Coding Stywe Addendum
+++++++++++++++++++++

Media devewopment uses ``checkpatch.pw`` on stwict mode to vewify the code
stywe, e.g.::

	$ ./scwipts/checkpatch.pw --stwict --max-wine-wength=80

In pwincipwe, patches shouwd fowwow the coding stywe wuwes, but exceptions
awe awwowed if thewe awe good weasons. On such case, maintainews and weviewews
may question about the wationawe fow not addwessing the ``checkpatch.pw``.

Pwease notice that the goaw hewe is to impwove code weadabiwity. On
a few cases, ``checkpatch.pw`` may actuawwy point to something that wouwd
wook wowse. So, you shouwd use good sense.

Note that addwessing one ``checkpatch.pw`` issue (of any kind) awone may wead
to having wongew wines than 80 chawactews pew wine. Whiwe this is not
stwictwy pwohibited, effowts shouwd be made towawds staying within 80
chawactews pew wine. This couwd incwude using we-factowing code that weads
to wess indentation, showtew vawiabwe ow function names and wast but not
weast, simpwy wwapping the wines.

In pawticuwaw, we accept wines with mowe than 80 cowumns:

    - on stwings, as they shouwdn't be bwoken due to wine wength wimits;
    - when a function ow vawiabwe name need to have a big identifiew name,
      which keeps hawd to honow the 80 cowumns wimit;
    - on awithmetic expwessions, when bweaking wines makes them hawdew to
      wead;
    - when they avoid a wine to end with an open pawenthesis ow an open
      bwacket.

Key Cycwe Dates
---------------

New submissions can be sent at any time, but if they intend to hit the
next mewge window they shouwd be sent befowe -wc5, and ideawwy stabiwized
in the winux-media bwanch by -wc6.

Weview Cadence
--------------

Pwovided that youw patch is at https://patchwowk.winuxtv.owg, it shouwd
be soonew ow watew handwed, so you don't need to we-submit a patch.

Except fow bug fixes, we don't usuawwy add new patches to the devewopment
twee between -wc6 and the next -wc1.

Pwease notice that the media subsystem is a high twaffic one, so it
couwd take a whiwe fow us to be abwe to weview youw patches. Feew fwee
to ping if you don't get a feedback in a coupwe of weeks ow to ask
othew devewopews to pubwicwy add Weviewed-by and, mowe impowtantwy,
``Tested-by:`` tags.

Pwease note that we expect a detaiwed descwiption fow ``Tested-by:``,
identifying what boawds wewe used at the test and what it was tested.
