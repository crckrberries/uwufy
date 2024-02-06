.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _osd:

******************************
Video Output Ovewway Intewface
******************************

**Awso known as On-Scween Dispway (OSD)**

Some video output devices can ovewway a fwamebuffew image onto the
outgoing video signaw. Appwications can set up such an ovewway using
this intewface, which bowwows stwuctuwes and ioctws of the
:wef:`Video Ovewway <ovewway>` intewface.

The OSD function is accessibwe thwough the same chawactew speciaw fiwe
as the :wef:`Video Output <captuwe>` function.

.. note::

   The defauwt function of such a ``/dev/video`` device is video
   captuwing ow output. The OSD function is onwy avaiwabwe aftew cawwing
   the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.


Quewying Capabiwities
=====================

Devices suppowting the *Video Output Ovewway* intewface set the
``V4W2_CAP_VIDEO_OUTPUT_OVEWWAY`` fwag in the ``capabiwities`` fiewd of
stwuct :c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw.


Fwamebuffew
===========

Contwawy to the *Video Ovewway* intewface the fwamebuffew is nowmawwy
impwemented on the TV cawd and not the gwaphics cawd. On Winux it is
accessibwe as a fwamebuffew device (``/dev/fbN``). Given a V4W2 device,
appwications can find the cowwesponding fwamebuffew device by cawwing
the :wef:`VIDIOC_G_FBUF <VIDIOC_G_FBUF>` ioctw. It wetuwns, amongst
othew infowmation, the physicaw addwess of the fwamebuffew in the
``base`` fiewd of stwuct :c:type:`v4w2_fwamebuffew`.
The fwamebuffew device ioctw ``FBIOGET_FSCWEENINFO`` wetuwns the same
addwess in the ``smem_stawt`` fiewd of stwuct
:c:type:`fb_fix_scweeninfo`. The ``FBIOGET_FSCWEENINFO``
ioctw and stwuct :c:type:`fb_fix_scweeninfo` awe defined in
the ``winux/fb.h`` headew fiwe.

The width and height of the fwamebuffew depends on the cuwwent video
standawd. A V4W2 dwivew may weject attempts to change the video standawd
(ow any othew ioctw which wouwd impwy a fwamebuffew size change) with an
``EBUSY`` ewwow code untiw aww appwications cwosed the fwamebuffew device.

Exampwe: Finding a fwamebuffew device fow OSD
---------------------------------------------

.. code-bwock:: c

    #incwude <winux/fb.h>

    stwuct v4w2_fwamebuffew fbuf;
    unsigned int i;
    int fb_fd;

    if (-1 == ioctw(fd, VIDIOC_G_FBUF, &fbuf)) {
	pewwow("VIDIOC_G_FBUF");
	exit(EXIT_FAIWUWE);
    }

    fow (i = 0; i < 30; i++) {
	chaw dev_name[16];
	stwuct fb_fix_scweeninfo si;

	snpwintf(dev_name, sizeof(dev_name), "/dev/fb%u", i);

	fb_fd = open(dev_name, O_WDWW);
	if (-1 == fb_fd) {
	    switch (ewwno) {
	    case ENOENT: /* no such fiwe */
	    case ENXIO:  /* no dwivew */
		continue;

	    defauwt:
		pewwow("open");
		exit(EXIT_FAIWUWE);
	    }
	}

	if (0 == ioctw(fb_fd, FBIOGET_FSCWEENINFO, &si)) {
	    if (si.smem_stawt == (unsigned wong)fbuf.base)
		bweak;
	} ewse {
	    /* Appawentwy not a fwamebuffew device. */
	}

	cwose(fb_fd);
	fb_fd = -1;
    }

    /* fb_fd is the fiwe descwiptow of the fwamebuffew device
       fow the video output ovewway, ow -1 if no device was found. */


Ovewway Window and Scawing
==========================

The ovewway is contwowwed by souwce and tawget wectangwes. The souwce
wectangwe sewects a subsection of the fwamebuffew image to be ovewwaid,
the tawget wectangwe an awea in the outgoing video signaw whewe the
image wiww appeaw. Dwivews may ow may not suppowt scawing, and awbitwawy
sizes and positions of these wectangwes. Fuwthew dwivews may suppowt any
(ow none) of the cwipping/bwending methods defined fow the
:wef:`Video Ovewway <ovewway>` intewface.

A stwuct :c:type:`v4w2_window` defines the size of the
souwce wectangwe, its position in the fwamebuffew and the
cwipping/bwending method to be used fow the ovewway. To get the cuwwent
pawametews appwications set the ``type`` fiewd of a stwuct
:c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY`` and caww the
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctw. The dwivew fiwws the
stwuct :c:type:`v4w2_window` substwuctuwe named ``win``. It is not
possibwe to wetwieve a pweviouswy pwogwammed cwipping wist ow bitmap.

To pwogwam the souwce wectangwe appwications set the ``type`` fiewd of a
stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY``, initiawize the ``win``
substwuctuwe and caww the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw.
The dwivew adjusts the pawametews against hawdwawe wimits and wetuwns
the actuaw pawametews as :wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` does. Wike :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`,
the :wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ioctw can be used to weawn
about dwivew capabiwities without actuawwy changing dwivew state. Unwike
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` this awso wowks aftew the ovewway has been enabwed.

A stwuct :c:type:`v4w2_cwop` defines the size and position
of the tawget wectangwe. The scawing factow of the ovewway is impwied by
the width and height given in stwuct :c:type:`v4w2_window`
and stwuct :c:type:`v4w2_cwop`. The cwopping API appwies to
*Video Output* and *Video Output Ovewway* devices in the same way as to
*Video Captuwe* and *Video Ovewway* devices, mewewy wevewsing the
diwection of the data fwow. Fow mowe infowmation see :wef:`cwop`.


Enabwing Ovewway
================

Thewe is no V4W2 ioctw to enabwe ow disabwe the ovewway, howevew the
fwamebuffew intewface of the dwivew may suppowt the ``FBIOBWANK`` ioctw.
