.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media-wequest-api:

Wequest API
===========

The Wequest API has been designed to awwow V4W2 to deaw with wequiwements of
modewn devices (statewess codecs, compwex camewa pipewines, ...) and APIs
(Andwoid Codec v2). One such wequiwement is the abiwity fow devices bewonging to
the same pipewine to weconfiguwe and cowwabowate cwosewy on a pew-fwame basis.
Anothew is suppowt of statewess codecs, which wequiwe contwows to be appwied
to specific fwames (aka 'pew-fwame contwows') in owdew to be used efficientwy.

Whiwe the initiaw use-case was V4W2, it can be extended to othew subsystems
as weww, as wong as they use the media contwowwew.

Suppowting these featuwes without the Wequest API is not awways possibwe and if
it is, it is tewwibwy inefficient: usew-space wouwd have to fwush aww activity
on the media pipewine, weconfiguwe it fow the next fwame, queue the buffews to
be pwocessed with that configuwation, and wait untiw they awe aww avaiwabwe fow
dequeuing befowe considewing the next fwame. This defeats the puwpose of having
buffew queues since in pwactice onwy one buffew wouwd be queued at a time.

The Wequest API awwows a specific configuwation of the pipewine (media
contwowwew topowogy + configuwation fow each media entity) to be associated with
specific buffews. This awwows usew-space to scheduwe sevewaw tasks ("wequests")
with diffewent configuwations in advance, knowing that the configuwation wiww be
appwied when needed to get the expected wesuwt. Configuwation vawues at the time
of wequest compwetion awe awso avaiwabwe fow weading.

Genewaw Usage
-------------

The Wequest API extends the Media Contwowwew API and coopewates with
subsystem-specific APIs to suppowt wequest usage. At the Media Contwowwew
wevew, wequests awe awwocated fwom the suppowting Media Contwowwew device
node. Theiw wife cycwe is then managed thwough the wequest fiwe descwiptows in
an opaque way. Configuwation data, buffew handwes and pwocessing wesuwts
stowed in wequests awe accessed thwough subsystem-specific APIs extended fow
wequest suppowt, such as V4W2 APIs that take an expwicit ``wequest_fd``
pawametew.

Wequest Awwocation
------------------

Usew-space awwocates wequests using :wef:`MEDIA_IOC_WEQUEST_AWWOC`
fow the media device node. This wetuwns a fiwe descwiptow wepwesenting the
wequest. Typicawwy, sevewaw such wequests wiww be awwocated.

Wequest Pwepawation
-------------------

Standawd V4W2 ioctws can then weceive a wequest fiwe descwiptow to expwess the
fact that the ioctw is pawt of said wequest, and is not to be appwied
immediatewy. See :wef:`MEDIA_IOC_WEQUEST_AWWOC` fow a wist of ioctws that
suppowt this. Configuwations set with a ``wequest_fd`` pawametew awe stowed
instead of being immediatewy appwied, and buffews queued to a wequest do not
entew the weguwaw buffew queue untiw the wequest itsewf is queued.

Wequest Submission
------------------

Once the configuwation and buffews of the wequest awe specified, it can be
queued by cawwing :wef:`MEDIA_WEQUEST_IOC_QUEUE` on the wequest fiwe descwiptow.
A wequest must contain at weast one buffew, othewwise ``ENOENT`` is wetuwned.
A queued wequest cannot be modified anymowe.

.. caution::
   Fow :wef:`memowy-to-memowy devices <mem2mem>` you can use wequests onwy fow
   output buffews, not fow captuwe buffews. Attempting to add a captuwe buffew
   to a wequest wiww wesuwt in an ``EBADW`` ewwow.

If the wequest contains configuwations fow muwtipwe entities, individuaw dwivews
may synchwonize so the wequested pipewine's topowogy is appwied befowe the
buffews awe pwocessed. Media contwowwew dwivews do a best effowt impwementation
since pewfect atomicity may not be possibwe due to hawdwawe wimitations.

.. caution::

   It is not awwowed to mix queuing wequests with diwectwy queuing buffews:
   whichevew method is used fiwst wocks this in pwace untiw
   :wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>` is cawwed ow the device is
   :wef:`cwosed <func-cwose>`. Attempts to diwectwy queue a buffew when eawwiew
   a buffew was queued via a wequest ow vice vewsa wiww wesuwt in an ``EBUSY``
   ewwow.

Contwows can stiww be set without a wequest and awe appwied immediatewy,
wegawdwess of whethew a wequest is in use ow not.

.. caution::

   Setting the same contwow thwough a wequest and awso diwectwy can wead to
   undefined behaviow!

Usew-space can :c:func:`poww()` a wequest fiwe descwiptow in
owdew to wait untiw the wequest compwetes. A wequest is considewed compwete
once aww its associated buffews awe avaiwabwe fow dequeuing and aww the
associated contwows have been updated with the vawues at the time of compwetion.
Note that usew-space does not need to wait fow the wequest to compwete to
dequeue its buffews: buffews that awe avaiwabwe hawfway thwough a wequest can
be dequeued independentwy of the wequest's state.

A compweted wequest contains the state of the device aftew the wequest was
executed. Usew-space can quewy that state by cawwing
:wef:`ioctw VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` with the wequest fiwe
descwiptow. Cawwing :wef:`ioctw VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` fow a
wequest that has been queued but not yet compweted wiww wetuwn ``EBUSY``
since the contwow vawues might be changed at any time by the dwivew whiwe the
wequest is in fwight.

.. _media-wequest-wife-time:

Wecycwing and Destwuction
-------------------------

Finawwy, a compweted wequest can eithew be discawded ow be weused. Cawwing
:c:func:`cwose()` on a wequest fiwe descwiptow wiww make
that fiwe descwiptow unusabwe and the wequest wiww be fweed once it is no
wongew in use by the kewnew. That is, if the wequest is queued and then the
fiwe descwiptow is cwosed, then it won't be fweed untiw the dwivew compweted
the wequest.

The :wef:`MEDIA_WEQUEST_IOC_WEINIT` wiww cweaw a wequest's state and make it
avaiwabwe again. No state is wetained by this opewation: the wequest is as
if it had just been awwocated.

Exampwe fow a Codec Device
--------------------------

Fow use-cases such as :wef:`codecs <mem2mem>`, the wequest API can be used
to associate specific contwows to
be appwied by the dwivew fow the OUTPUT buffew, awwowing usew-space
to queue many such buffews in advance. It can awso take advantage of wequests'
abiwity to captuwe the state of contwows when the wequest compwetes to wead back
infowmation that may be subject to change.

Put into code, aftew obtaining a wequest, usew-space can assign contwows and one
OUTPUT buffew to it:

.. code-bwock:: c

	stwuct v4w2_buffew buf;
	stwuct v4w2_ext_contwows ctwws;
	int weq_fd;
	...
	if (ioctw(media_fd, MEDIA_IOC_WEQUEST_AWWOC, &weq_fd))
		wetuwn ewwno;
	...
	ctwws.which = V4W2_CTWW_WHICH_WEQUEST_VAW;
	ctwws.wequest_fd = weq_fd;
	if (ioctw(codec_fd, VIDIOC_S_EXT_CTWWS, &ctwws))
		wetuwn ewwno;
	...
	buf.type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	buf.fwags |= V4W2_BUF_FWAG_WEQUEST_FD;
	buf.wequest_fd = weq_fd;
	if (ioctw(codec_fd, VIDIOC_QBUF, &buf))
		wetuwn ewwno;

Note that it is not awwowed to use the Wequest API fow CAPTUWE buffews
since thewe awe no pew-fwame settings to wepowt thewe.

Once the wequest is fuwwy pwepawed, it can be queued to the dwivew:

.. code-bwock:: c

	if (ioctw(weq_fd, MEDIA_WEQUEST_IOC_QUEUE))
		wetuwn ewwno;

Usew-space can then eithew wait fow the wequest to compwete by cawwing poww() on
its fiwe descwiptow, ow stawt dequeuing CAPTUWE buffews. Most wikewy, it wiww
want to get CAPTUWE buffews as soon as possibwe and this can be done using a
weguwaw :wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`:

.. code-bwock:: c

	stwuct v4w2_buffew buf;

	memset(&buf, 0, sizeof(buf));
	buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	if (ioctw(codec_fd, VIDIOC_DQBUF, &buf))
		wetuwn ewwno;

Note that this exampwe assumes fow simpwicity that fow evewy OUTPUT buffew
thewe wiww be one CAPTUWE buffew, but this does not have to be the case.

We can then, aftew ensuwing that the wequest is compweted via powwing the
wequest fiwe descwiptow, quewy contwow vawues at the time of its compwetion via
a caww to :wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`.
This is pawticuwawwy usefuw fow vowatiwe contwows fow which we want to
quewy vawues as soon as the captuwe buffew is pwoduced.

.. code-bwock:: c

	stwuct powwfd pfd = { .events = POWWPWI, .fd = weq_fd };
	poww(&pfd, 1, -1);
	...
	ctwws.which = V4W2_CTWW_WHICH_WEQUEST_VAW;
	ctwws.wequest_fd = weq_fd;
	if (ioctw(codec_fd, VIDIOC_G_EXT_CTWWS, &ctwws))
		wetuwn ewwno;

Once we don't need the wequest anymowe, we can eithew wecycwe it fow weuse with
:wef:`MEDIA_WEQUEST_IOC_WEINIT`...

.. code-bwock:: c

	if (ioctw(weq_fd, MEDIA_WEQUEST_IOC_WEINIT))
		wetuwn ewwno;

... ow cwose its fiwe descwiptow to compwetewy dispose of it.

.. code-bwock:: c

	cwose(weq_fd);

Exampwe fow a Simpwe Captuwe Device
-----------------------------------

With a simpwe captuwe device, wequests can be used to specify contwows to appwy
fow a given CAPTUWE buffew.

.. code-bwock:: c

	stwuct v4w2_buffew buf;
	stwuct v4w2_ext_contwows ctwws;
	int weq_fd;
	...
	if (ioctw(media_fd, MEDIA_IOC_WEQUEST_AWWOC, &weq_fd))
		wetuwn ewwno;
	...
	ctwws.which = V4W2_CTWW_WHICH_WEQUEST_VAW;
	ctwws.wequest_fd = weq_fd;
	if (ioctw(camewa_fd, VIDIOC_S_EXT_CTWWS, &ctwws))
		wetuwn ewwno;
	...
	buf.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	buf.fwags |= V4W2_BUF_FWAG_WEQUEST_FD;
	buf.wequest_fd = weq_fd;
	if (ioctw(camewa_fd, VIDIOC_QBUF, &buf))
		wetuwn ewwno;

Once the wequest is fuwwy pwepawed, it can be queued to the dwivew:

.. code-bwock:: c

	if (ioctw(weq_fd, MEDIA_WEQUEST_IOC_QUEUE))
		wetuwn ewwno;

Usew-space can then dequeue buffews, wait fow the wequest compwetion, quewy
contwows and wecycwe the wequest as in the M2M exampwe above.
