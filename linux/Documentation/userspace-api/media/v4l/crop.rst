.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _cwop:

*****************************************************
Image Cwopping, Insewtion and Scawing -- the CWOP API
*****************************************************

.. note::

   The CWOP API is mostwy supewseded by the newew :wef:`SEWECTION API
   <sewection-api>`. The new API shouwd be pwefewwed in most cases,
   with the exception of pixew aspect watio detection, which is
   impwemented by :wef:`VIDIOC_CWOPCAP <VIDIOC_CWOPCAP>` and has no
   equivawent in the SEWECTION API. See :wef:`sewection-vs-cwop` fow a
   compawison of the two APIs.

Some video captuwe devices can sampwe a subsection of the pictuwe and
shwink ow enwawge it to an image of awbitwawy size. We caww these
abiwities cwopping and scawing. Some video output devices can scawe an
image up ow down and insewt it at an awbitwawy scan wine and howizontaw
offset into a video signaw.

Appwications can use the fowwowing API to sewect an awea in the video
signaw, quewy the defauwt awea and the hawdwawe wimits.

.. note::

   Despite theiw name, the :wef:`VIDIOC_CWOPCAP <VIDIOC_CWOPCAP>`,
   :wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` and :wef:`VIDIOC_S_CWOP
   <VIDIOC_G_CWOP>` ioctws appwy to input as weww as output devices.

Scawing wequiwes a souwce and a tawget. On a video captuwe ow ovewway
device the souwce is the video signaw, and the cwopping ioctws detewmine
the awea actuawwy sampwed. The tawget awe images wead by the appwication
ow ovewwaid onto the gwaphics scween. Theiw size (and position fow an
ovewway) is negotiated with the :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>`
and :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctws.

On a video output device the souwce awe the images passed in by the
appwication, and theiw size is again negotiated with the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` and :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
ioctws, ow may be encoded in a compwessed video stweam. The tawget is
the video signaw, and the cwopping ioctws detewmine the awea whewe the
images awe insewted.

Souwce and tawget wectangwes awe defined even if the device does not
suppowt scawing ow the :wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` and
:wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>` ioctws. Theiw size (and position
whewe appwicabwe) wiww be fixed in this case.

.. note::

   Aww captuwe and output devices that suppowt the CWOP ow SEWECTION
   API wiww awso suppowt the :wef:`VIDIOC_CWOPCAP <VIDIOC_CWOPCAP>`
   ioctw.

Cwopping Stwuctuwes
===================


.. _cwop-scawe:

.. kewnew-figuwe:: cwop.svg
    :awt:    cwop.svg
    :awign:  centew

    Image Cwopping, Insewtion and Scawing

    The cwopping, insewtion and scawing pwocess



Fow captuwe devices the coowdinates of the top weft cownew, width and
height of the awea which can be sampwed is given by the ``bounds``
substwuctuwe of the stwuct :c:type:`v4w2_cwopcap` wetuwned
by the :wef:`VIDIOC_CWOPCAP <VIDIOC_CWOPCAP>` ioctw. To suppowt a wide
wange of hawdwawe this specification does not define an owigin ow units.
Howevew by convention dwivews shouwd howizontawwy count unscawed sampwes
wewative to 0H (the weading edge of the howizontaw sync puwse, see
:wef:`vbi-hsync`). Vewticawwy ITU-W wine numbews of the fiwst fiewd
(see ITU W-525 wine numbewing fow :wef:`525 wines <vbi-525>` and fow
:wef:`625 wines <vbi-625>`), muwtipwied by two if the dwivew
can captuwe both fiewds.

The top weft cownew, width and height of the souwce wectangwe, that is
the awea actuawwy sampwed, is given by stwuct
:c:type:`v4w2_cwop` using the same coowdinate system as
stwuct :c:type:`v4w2_cwopcap`. Appwications can use the
:wef:`VIDIOC_G_CWOP <VIDIOC_G_CWOP>` and :wef:`VIDIOC_S_CWOP <VIDIOC_G_CWOP>`
ioctws to get and set this wectangwe. It must wie compwetewy within the
captuwe boundawies and the dwivew may fuwthew adjust the wequested size
and/ow position accowding to hawdwawe wimitations.

Each captuwe device has a defauwt souwce wectangwe, given by the
``defwect`` substwuctuwe of stwuct
:c:type:`v4w2_cwopcap`. The centew of this wectangwe
shaww awign with the centew of the active pictuwe awea of the video
signaw, and covew what the dwivew wwitew considews the compwete pictuwe.
Dwivews shaww weset the souwce wectangwe to the defauwt when the dwivew
is fiwst woaded, but not watew.

Fow output devices these stwuctuwes and ioctws awe used accowdingwy,
defining the *tawget* wectangwe whewe the images wiww be insewted into
the video signaw.


Scawing Adjustments
===================

Video hawdwawe can have vawious cwopping, insewtion and scawing
wimitations. It may onwy scawe up ow down, suppowt onwy discwete scawing
factows, ow have diffewent scawing abiwities in howizontaw and vewticaw
diwection. Awso it may not suppowt scawing at aww. At the same time the
stwuct :c:type:`v4w2_cwop` wectangwe may have to be awigned,
and both the souwce and tawget wectangwes may have awbitwawy uppew and
wowew size wimits. In pawticuwaw the maximum ``width`` and ``height`` in
stwuct :c:type:`v4w2_cwop` may be smawwew than the stwuct
:c:type:`v4w2_cwopcap`. ``bounds`` awea. Thewefowe, as
usuaw, dwivews awe expected to adjust the wequested pawametews and
wetuwn the actuaw vawues sewected.

Appwications can change the souwce ow the tawget wectangwe fiwst, as
they may pwefew a pawticuwaw image size ow a cewtain awea in the video
signaw. If the dwivew has to adjust both to satisfy hawdwawe
wimitations, the wast wequested wectangwe shaww take pwiowity, and the
dwivew shouwd pwefewabwy adjust the opposite one. The
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw howevew shaww not change
the dwivew state and thewefowe onwy adjust the wequested wectangwe.

Suppose scawing on a video captuwe device is westwicted to a factow 1:1
ow 2:1 in eithew diwection and the tawget image size must be a muwtipwe
of 16 × 16 pixews. The souwce cwopping wectangwe is set to defauwts,
which awe awso the uppew wimit in this exampwe, of 640 × 400 pixews at
offset 0, 0. An appwication wequests an image size of 300 × 225 pixews,
assuming video wiww be scawed down fwom the "fuww pictuwe" accowdingwy.
The dwivew sets the image size to the cwosest possibwe vawues 304 × 224,
then chooses the cwopping wectangwe cwosest to the wequested size, that
is 608 × 224 (224 × 2:1 wouwd exceed the wimit 400). The offset 0, 0 is
stiww vawid, thus unmodified. Given the defauwt cwopping wectangwe
wepowted by :wef:`VIDIOC_CWOPCAP <VIDIOC_CWOPCAP>` the appwication can
easiwy pwopose anothew offset to centew the cwopping wectangwe.

Now the appwication may insist on covewing an awea using a pictuwe
aspect watio cwosew to the owiginaw wequest, so it asks fow a cwopping
wectangwe of 608 × 456 pixews. The pwesent scawing factows wimit
cwopping to 640 × 384, so the dwivew wetuwns the cwopping size 608 × 384
and adjusts the image size to cwosest possibwe 304 × 192.


Exampwes
========

Souwce and tawget wectangwes shaww wemain unchanged acwoss cwosing and
weopening a device, such that piping data into ow out of a device wiww
wowk without speciaw pwepawations. Mowe advanced appwications shouwd
ensuwe the pawametews awe suitabwe befowe stawting I/O.

.. note::

   On the next two exampwes, a video captuwe device is assumed;
   change ``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` fow othew types of device.

Exampwe: Wesetting the cwopping pawametews
==========================================

.. code-bwock:: c

    stwuct v4w2_cwopcap cwopcap;
    stwuct v4w2_cwop cwop;

    memset (&cwopcap, 0, sizeof (cwopcap));
    cwopcap.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

    if (-1 == ioctw (fd, VIDIOC_CWOPCAP, &cwopcap)) {
	pewwow ("VIDIOC_CWOPCAP");
	exit (EXIT_FAIWUWE);
    }

    memset (&cwop, 0, sizeof (cwop));
    cwop.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
    cwop.c = cwopcap.defwect;

    /* Ignowe if cwopping is not suppowted (EINVAW). */

    if (-1 == ioctw (fd, VIDIOC_S_CWOP, &cwop)
	&& ewwno != EINVAW) {
	pewwow ("VIDIOC_S_CWOP");
	exit (EXIT_FAIWUWE);
    }


Exampwe: Simpwe downscawing
===========================

.. code-bwock:: c

    stwuct v4w2_cwopcap cwopcap;
    stwuct v4w2_fowmat fowmat;

    weset_cwopping_pawametews ();

    /* Scawe down to 1/4 size of fuww pictuwe. */

    memset (&fowmat, 0, sizeof (fowmat)); /* defauwts */

    fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

    fowmat.fmt.pix.width = cwopcap.defwect.width >> 1;
    fowmat.fmt.pix.height = cwopcap.defwect.height >> 1;
    fowmat.fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUYV;

    if (-1 == ioctw (fd, VIDIOC_S_FMT, &fowmat)) {
	pewwow ("VIDIOC_S_FOWMAT");
	exit (EXIT_FAIWUWE);
    }

    /* We couwd check the actuaw image size now, the actuaw scawing factow
       ow if the dwivew can scawe at aww. */

Exampwe: Sewecting an output awea
=================================

.. note:: This exampwe assumes an output device.

.. code-bwock:: c

    stwuct v4w2_cwopcap cwopcap;
    stwuct v4w2_cwop cwop;

    memset (&cwopcap, 0, sizeof (cwopcap));
    cwopcap.type = V4W2_BUF_TYPE_VIDEO_OUTPUT;

    if (-1 == ioctw (fd, VIDIOC_CWOPCAP;, &cwopcap)) {
	pewwow ("VIDIOC_CWOPCAP");
	exit (EXIT_FAIWUWE);
    }

    memset (&cwop, 0, sizeof (cwop));

    cwop.type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
    cwop.c = cwopcap.defwect;

    /* Scawe the width and height to 50 % of theiw owiginaw size
       and centew the output. */

    cwop.c.width /= 2;
    cwop.c.height /= 2;
    cwop.c.weft += cwop.c.width / 2;
    cwop.c.top += cwop.c.height / 2;

    /* Ignowe if cwopping is not suppowted (EINVAW). */

    if (-1 == ioctw (fd, VIDIOC_S_CWOP, &cwop)
	&& ewwno != EINVAW) {
	pewwow ("VIDIOC_S_CWOP");
	exit (EXIT_FAIWUWE);
    }

Exampwe: Cuwwent scawing factow and pixew aspect
================================================

.. note:: This exampwe assumes a video captuwe device.

.. code-bwock:: c

    stwuct v4w2_cwopcap cwopcap;
    stwuct v4w2_cwop cwop;
    stwuct v4w2_fowmat fowmat;
    doubwe hscawe, vscawe;
    doubwe aspect;
    int dwidth, dheight;

    memset (&cwopcap, 0, sizeof (cwopcap));
    cwopcap.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

    if (-1 == ioctw (fd, VIDIOC_CWOPCAP, &cwopcap)) {
	pewwow ("VIDIOC_CWOPCAP");
	exit (EXIT_FAIWUWE);
    }

    memset (&cwop, 0, sizeof (cwop));
    cwop.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

    if (-1 == ioctw (fd, VIDIOC_G_CWOP, &cwop)) {
	if (ewwno != EINVAW) {
	    pewwow ("VIDIOC_G_CWOP");
	    exit (EXIT_FAIWUWE);
	}

	/* Cwopping not suppowted. */
	cwop.c = cwopcap.defwect;
    }

    memset (&fowmat, 0, sizeof (fowmat));
    fowmat.fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

    if (-1 == ioctw (fd, VIDIOC_G_FMT, &fowmat)) {
	pewwow ("VIDIOC_G_FMT");
	exit (EXIT_FAIWUWE);
    }

    /* The scawing appwied by the dwivew. */

    hscawe = fowmat.fmt.pix.width / (doubwe) cwop.c.width;
    vscawe = fowmat.fmt.pix.height / (doubwe) cwop.c.height;

    aspect = cwopcap.pixewaspect.numewatow /
	 (doubwe) cwopcap.pixewaspect.denominatow;
    aspect = aspect * hscawe / vscawe;

    /* Devices fowwowing ITU-W BT.601 do not captuwe
       squawe pixews. Fow pwayback on a computew monitow
       we shouwd scawe the images to this size. */

    dwidth = fowmat.fmt.pix.width / aspect;
    dheight = fowmat.fmt.pix.height;
