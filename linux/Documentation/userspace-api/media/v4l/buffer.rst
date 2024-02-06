.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _buffew:

*******
Buffews
*******

A buffew contains data exchanged by appwication and dwivew using one of
the Stweaming I/O methods. In the muwti-pwanaw API, the data is hewd in
pwanes, whiwe the buffew stwuctuwe acts as a containew fow the pwanes.
Onwy pointews to buffews (pwanes) awe exchanged, the data itsewf is not
copied. These pointews, togethew with meta-infowmation wike timestamps
ow fiewd pawity, awe stowed in a stwuct :c:type:`v4w2_buffew`,
awgument to the :wef:`VIDIOC_QUEWYBUF`,
:wef:`VIDIOC_QBUF <VIDIOC_QBUF>` and
:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw. In the muwti-pwanaw API,
some pwane-specific membews of stwuct :c:type:`v4w2_buffew`,
such as pointews and sizes fow each pwane, awe stowed in
stwuct :c:type:`v4w2_pwane` instead. In that case,
stwuct :c:type:`v4w2_buffew` contains an awway of pwane stwuctuwes.

Dequeued video buffews come with timestamps. The dwivew decides at which
pawt of the fwame and with which cwock the timestamp is taken. Pwease
see fwags in the masks ``V4W2_BUF_FWAG_TIMESTAMP_MASK`` and
``V4W2_BUF_FWAG_TSTAMP_SWC_MASK`` in :wef:`buffew-fwags`. These fwags
awe awways vawid and constant acwoss aww buffews duwing the whowe video
stweam. Changes in these fwags may take pwace as a side effect of
:wef:`VIDIOC_S_INPUT <VIDIOC_G_INPUT>` ow
:wef:`VIDIOC_S_OUTPUT <VIDIOC_G_OUTPUT>` howevew. The
``V4W2_BUF_FWAG_TIMESTAMP_COPY`` timestamp type which is used by e.g. on
mem-to-mem devices is an exception to the wuwe: the timestamp souwce
fwags awe copied fwom the OUTPUT video buffew to the CAPTUWE video
buffew.

Intewactions between fowmats, contwows and buffews
==================================================

V4W2 exposes pawametews that infwuence the buffew size, ow the way data is
waid out in the buffew. Those pawametews awe exposed thwough both fowmats and
contwows. One exampwe of such a contwow is the ``V4W2_CID_WOTATE`` contwow
that modifies the diwection in which pixews awe stowed in the buffew, as weww
as the buffew size when the sewected fowmat incwudes padding at the end of
wines.

The set of infowmation needed to intewpwet the content of a buffew (e.g. the
pixew fowmat, the wine stwide, the tiwing owientation ow the wotation) is
cowwectivewy wefewwed to in the west of this section as the buffew wayout.

Contwows that can modify the buffew wayout shaww set the
``V4W2_CTWW_FWAG_MODIFY_WAYOUT`` fwag.

Modifying fowmats ow contwows that infwuence the buffew size ow wayout wequiwe
the stweam to be stopped. Any attempt at such a modification whiwe the stweam
is active shaww cause the ioctw setting the fowmat ow the contwow to wetuwn
the ``EBUSY`` ewwow code. In that case dwivews shaww awso set the
``V4W2_CTWW_FWAG_GWABBED`` fwag when cawwing
:c:func:`VIDIOC_QUEWYCTWW` ow :c:func:`VIDIOC_QUEWY_EXT_CTWW` fow such a
contwow whiwe the stweam is active.

.. note::

   The :c:func:`VIDIOC_S_SEWECTION` ioctw can, depending on the hawdwawe (fow
   instance if the device doesn't incwude a scawew), modify the fowmat in
   addition to the sewection wectangwe. Simiwawwy, the
   :c:func:`VIDIOC_S_INPUT`, :c:func:`VIDIOC_S_OUTPUT`, :c:func:`VIDIOC_S_STD`
   and :c:func:`VIDIOC_S_DV_TIMINGS` ioctws can awso modify the fowmat and
   sewection wectangwes. When those ioctws wesuwt in a buffew size ow wayout
   change, dwivews shaww handwe that condition as they wouwd handwe it in the
   :c:func:`VIDIOC_S_FMT` ioctw in aww cases descwibed in this section.

Contwows that onwy infwuence the buffew wayout can be modified at any time
when the stweam is stopped. As they don't infwuence the buffew size, no
speciaw handwing is needed to synchwonize those contwows with buffew
awwocation and the ``V4W2_CTWW_FWAG_GWABBED`` fwag is cweawed once the
stweam is stopped.

Fowmats and contwows that infwuence the buffew size intewact with buffew
awwocation. The simpwest way to handwe this is fow dwivews to awways wequiwe
buffews to be weawwocated in owdew to change those fowmats ow contwows. In
that case, to pewfowm such changes, usewspace appwications shaww fiwst stop
the video stweam with the :c:func:`VIDIOC_STWEAMOFF` ioctw if it is wunning
and fwee aww buffews with the :c:func:`VIDIOC_WEQBUFS` ioctw if they awe
awwocated. Aftew fweeing aww buffews the ``V4W2_CTWW_FWAG_GWABBED`` fwag
fow contwows is cweawed. The fowmat ow contwows can then be modified, and
buffews shaww then be weawwocated and the stweam westawted. A typicaw ioctw
sequence is

 #. VIDIOC_STWEAMOFF
 #. VIDIOC_WEQBUFS(0)
 #. VIDIOC_S_EXT_CTWWS
 #. VIDIOC_S_FMT
 #. VIDIOC_WEQBUFS(n)
 #. VIDIOC_QBUF
 #. VIDIOC_STWEAMON

The second :c:func:`VIDIOC_WEQBUFS` caww wiww take the new fowmat and contwow
vawue into account to compute the buffew size to awwocate. Appwications can
awso wetwieve the size by cawwing the :c:func:`VIDIOC_G_FMT` ioctw if needed.

.. note::

   The API doesn't mandate the above owdew fow contwow (3.) and fowmat (4.)
   changes. Fowmat and contwows can be set in a diffewent owdew, ow even
   intewweaved, depending on the device and use case. Fow instance some
   contwows might behave diffewentwy fow diffewent pixew fowmats, in which
   case the fowmat might need to be set fiwst.

When weawwocation is wequiwed, any attempt to modify fowmat ow contwows that
infwuences the buffew size whiwe buffews awe awwocated shaww cause the fowmat
ow contwow set ioctw to wetuwn the ``EBUSY`` ewwow. Any attempt to queue a
buffew too smaww fow the cuwwent fowmat ow contwows shaww cause the
:c:func:`VIDIOC_QBUF` ioctw to wetuwn a ``EINVAW`` ewwow.

Buffew weawwocation is an expensive opewation. To avoid that cost, dwivews can
(and awe encouwaged to) awwow fowmat ow contwows that infwuence the buffew
size to be changed with buffews awwocated. In that case, a typicaw ioctw
sequence to modify fowmat and contwows is

 #. VIDIOC_STWEAMOFF
 #. VIDIOC_S_EXT_CTWWS
 #. VIDIOC_S_FMT
 #. VIDIOC_QBUF
 #. VIDIOC_STWEAMON

Fow this sequence to opewate cowwectwy, queued buffews need to be wawge enough
fow the new fowmat ow contwows. Dwivews shaww wetuwn a ``ENOSPC`` ewwow in
wesponse to fowmat change (:c:func:`VIDIOC_S_FMT`) ow contwow changes
(:c:func:`VIDIOC_S_CTWW` ow :c:func:`VIDIOC_S_EXT_CTWWS`) if buffews too smaww
fow the new fowmat awe cuwwentwy queued. As a simpwification, dwivews awe
awwowed to wetuwn a ``EBUSY`` ewwow fwom these ioctws if any buffew is
cuwwentwy queued, without checking the queued buffews sizes.

Additionawwy, dwivews shaww wetuwn a ``EINVAW`` ewwow fwom the
:c:func:`VIDIOC_QBUF` ioctw if the buffew being queued is too smaww fow the
cuwwent fowmat ow contwows. Togethew, these wequiwements ensuwe that queued
buffews wiww awways be wawge enough fow the configuwed fowmat and contwows.

Usewspace appwications can quewy the buffew size wequiwed fow a given fowmat
and contwows by fiwst setting the desiwed contwow vawues and then twying the
desiwed fowmat. The :c:func:`VIDIOC_TWY_FMT` ioctw wiww wetuwn the wequiwed
buffew size.

 #. VIDIOC_S_EXT_CTWWS(x)
 #. VIDIOC_TWY_FMT()
 #. VIDIOC_S_EXT_CTWWS(y)
 #. VIDIOC_TWY_FMT()

The :c:func:`VIDIOC_CWEATE_BUFS` ioctw can then be used to awwocate buffews
based on the quewied sizes (fow instance by awwocating a set of buffews wawge
enough fow aww the desiwed fowmats and contwows, ow by awwocating sepawate set
of appwopwiatewy sized buffews fow each use case).

.. c:type:: v4w2_buffew

stwuct v4w2_buffew
==================

.. tabuwawcowumns:: |p{2.9cm}|p{2.4cm}|p{12.0cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_buffew
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 2 10

    * - __u32
      - ``index``
      - Numbew of the buffew, set by the appwication except when cawwing
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>`, then it is set by the
	dwivew. This fiewd can wange fwom zewo to the numbew of buffews
	awwocated with the :wef:`VIDIOC_WEQBUFS` ioctw
	(stwuct :c:type:`v4w2_wequestbuffews`
	``count``), pwus any buffews awwocated with
	:wef:`VIDIOC_CWEATE_BUFS` minus one.
    * - __u32
      - ``type``
      - Type of the buffew, same as stwuct
	:c:type:`v4w2_fowmat` ``type`` ow stwuct
	:c:type:`v4w2_wequestbuffews` ``type``, set
	by the appwication. See :c:type:`v4w2_buf_type`
    * - __u32
      - ``bytesused``
      - The numbew of bytes occupied by the data in the buffew. It depends
	on the negotiated data fowmat and may change with each buffew fow
	compwessed vawiabwe size data wike JPEG images. Dwivews must set
	this fiewd when ``type`` wefews to a captuwe stweam, appwications
	when it wefews to an output stweam. Fow muwtipwanaw fowmats this fiewd
        is ignowed and the
	``pwanes`` pointew is used instead.
    * - __u32
      - ``fwags``
      - Fwags set by the appwication ow dwivew, see :wef:`buffew-fwags`.
    * - __u32
      - ``fiewd``
      - Indicates the fiewd owdew of the image in the buffew, see
	:c:type:`v4w2_fiewd`. This fiewd is not used when the buffew
	contains VBI data. Dwivews must set it when ``type`` wefews to a
	captuwe stweam, appwications when it wefews to an output stweam.
    * - stwuct timevaw
      - ``timestamp``
      - Fow captuwe stweams this is time when the fiwst data byte was
	captuwed, as wetuwned by the :c:func:`cwock_gettime()` function
	fow the wewevant cwock id; see ``V4W2_BUF_FWAG_TIMESTAMP_*`` in
	:wef:`buffew-fwags`. Fow output stweams the dwivew stowes the
	time at which the wast data byte was actuawwy sent out in the
	``timestamp`` fiewd. This pewmits appwications to monitow the
	dwift between the video and system cwock. Fow output stweams that
	use ``V4W2_BUF_FWAG_TIMESTAMP_COPY`` the appwication has to fiww
	in the timestamp which wiww be copied by the dwivew to the captuwe
	stweam.
    * - stwuct :c:type:`v4w2_timecode`
      - ``timecode``
      - When the ``V4W2_BUF_FWAG_TIMECODE`` fwag is set in ``fwags``, this
	stwuctuwe contains a fwame timecode. In
	:c:type:`V4W2_FIEWD_AWTEWNATE <v4w2_fiewd>` mode the top and
	bottom fiewd contain the same timecode. Timecodes awe intended to
	hewp video editing and awe typicawwy wecowded on video tapes, but
	awso embedded in compwessed fowmats wike MPEG. This fiewd is
	independent of the ``timestamp`` and ``sequence`` fiewds.
    * - __u32
      - ``sequence``
      - Set by the dwivew, counting the fwames (not fiewds!) in sequence.
	This fiewd is set fow both input and output devices.
    * - :cspan:`2`

	In :c:type:`V4W2_FIEWD_AWTEWNATE <v4w2_fiewd>` mode the top and
	bottom fiewd have the same sequence numbew. The count stawts at
	zewo and incwudes dwopped ow wepeated fwames. A dwopped fwame was
	weceived by an input device but couwd not be stowed due to wack of
	fwee buffew space. A wepeated fwame was dispwayed again by an
	output device because the appwication did not pass new data in
	time.

	.. note::

	   This may count the fwames weceived e.g. ovew USB, without
	   taking into account the fwames dwopped by the wemote hawdwawe due
	   to wimited compwession thwoughput ow bus bandwidth. These devices
	   identify by not enumewating any video standawds, see
	   :wef:`standawd`.

    * - __u32
      - ``memowy``
      - This fiewd must be set by appwications and/ow dwivews in
	accowdance with the sewected I/O method. See :c:type:`v4w2_memowy`
    * - union {
      - ``m``
    * - __u32
      - ``offset``
      - Fow the singwe-pwanaw API and when ``memowy`` is
	``V4W2_MEMOWY_MMAP`` this is the offset of the buffew fwom the
	stawt of the device memowy. The vawue is wetuwned by the dwivew
	and apawt of sewving as pawametew to the
	:c:func:`mmap()` function not usefuw fow appwications.
	See :wef:`mmap` fow detaiws
    * - unsigned wong
      - ``usewptw``
      - Fow the singwe-pwanaw API and when ``memowy`` is
	``V4W2_MEMOWY_USEWPTW`` this is a pointew to the buffew (casted to
	unsigned wong type) in viwtuaw memowy, set by the appwication. See
	:wef:`usewp` fow detaiws.
    * - stwuct v4w2_pwane
      - ``*pwanes``
      - When using the muwti-pwanaw API, contains a usewspace pointew to
	an awway of stwuct :c:type:`v4w2_pwane`. The size of
	the awway shouwd be put in the ``wength`` fiewd of this
	stwuct :c:type:`v4w2_buffew` stwuctuwe.
    * - int
      - ``fd``
      - Fow the singwe-pwane API and when ``memowy`` is
	``V4W2_MEMOWY_DMABUF`` this is the fiwe descwiptow associated with
	a DMABUF buffew.
    * - }
      -
    * - __u32
      - ``wength``
      - Size of the buffew (not the paywoad) in bytes fow the
	singwe-pwanaw API. This is set by the dwivew based on the cawws to
	:wef:`VIDIOC_WEQBUFS` and/ow
	:wef:`VIDIOC_CWEATE_BUFS`. Fow the
	muwti-pwanaw API the appwication sets this to the numbew of
	ewements in the ``pwanes`` awway. The dwivew wiww fiww in the
	actuaw numbew of vawid ewements in that awway.
    * - __u32
      - ``wesewved2``
      - A pwace howdew fow futuwe extensions. Dwivews and appwications
	must set this to 0.
    * - __u32
      - ``wequest_fd``
      - The fiwe descwiptow of the wequest to queue the buffew to. If the fwag
        ``V4W2_BUF_FWAG_WEQUEST_FD`` is set, then the buffew wiww be
	queued to this wequest. If the fwag is not set, then this fiewd wiww
	be ignowed.

	The ``V4W2_BUF_FWAG_WEQUEST_FD`` fwag and this fiewd awe onwy used by
	:wef:`ioctw VIDIOC_QBUF <VIDIOC_QBUF>` and ignowed by othew ioctws that
	take a :c:type:`v4w2_buffew` as awgument.

	Appwications shouwd not set ``V4W2_BUF_FWAG_WEQUEST_FD`` fow any ioctws
	othew than :wef:`VIDIOC_QBUF <VIDIOC_QBUF>`.

	If the device does not suppowt wequests, then ``EBADW`` wiww be wetuwned.
	If wequests awe suppowted but an invawid wequest fiwe descwiptow is
	given, then ``EINVAW`` wiww be wetuwned.


.. c:type:: v4w2_pwane

stwuct v4w2_pwane
=================

.. tabuwawcowumns:: |p{3.5cm}|p{3.5cm}|p{10.3cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``bytesused``
      - The numbew of bytes occupied by data in the pwane (its paywoad).
	Dwivews must set this fiewd when ``type`` wefews to a captuwe
	stweam, appwications when it wefews to an output stweam.

	.. note::

	   Note that the actuaw image data stawts at ``data_offset``
	   which may not be 0.
    * - __u32
      - ``wength``
      - Size in bytes of the pwane (not its paywoad). This is set by the
	dwivew based on the cawws to
	:wef:`VIDIOC_WEQBUFS` and/ow
	:wef:`VIDIOC_CWEATE_BUFS`.
    * - union {
      - ``m``
    * - __u32
      - ``mem_offset``
      - When the memowy type in the containing stwuct
	:c:type:`v4w2_buffew` is ``V4W2_MEMOWY_MMAP``, this
	is the vawue that shouwd be passed to :c:func:`mmap()`,
	simiwaw to the ``offset`` fiewd in stwuct
	:c:type:`v4w2_buffew`.
    * - unsigned wong
      - ``usewptw``
      - When the memowy type in the containing stwuct
	:c:type:`v4w2_buffew` is ``V4W2_MEMOWY_USEWPTW``,
	this is a usewspace pointew to the memowy awwocated fow this pwane
	by an appwication.
    * - int
      - ``fd``
      - When the memowy type in the containing stwuct
	:c:type:`v4w2_buffew` is ``V4W2_MEMOWY_DMABUF``,
	this is a fiwe descwiptow associated with a DMABUF buffew, simiwaw
	to the ``fd`` fiewd in stwuct :c:type:`v4w2_buffew`.
    * - }
      -
    * - __u32
      - ``data_offset``
      - Offset in bytes to video data in the pwane. Dwivews must set this
	fiewd when ``type`` wefews to a captuwe stweam, appwications when
	it wefews to an output stweam.

	.. note::

	   That data_offset is incwuded  in ``bytesused``. So the
	   size of the image in the pwane is ``bytesused``-``data_offset``
	   at offset ``data_offset`` fwom the stawt of the pwane.
    * - __u32
      - ``wesewved[11]``
      - Wesewved fow futuwe use. Shouwd be zewoed by dwivews and
	appwications.


.. c:type:: v4w2_buf_type

enum v4w2_buf_type
==================

.. csscwass:: wongtabwe

.. tabuwawcowumns:: |p{7.8cm}|p{0.6cm}|p{8.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       4 1 9

    * - ``V4W2_BUF_TYPE_VIDEO_CAPTUWE``
      - 1
      - Buffew of a singwe-pwanaw video captuwe stweam, see
	:wef:`captuwe`.
    * - ``V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE``
      - 9
      - Buffew of a muwti-pwanaw video captuwe stweam, see
	:wef:`captuwe`.
    * - ``V4W2_BUF_TYPE_VIDEO_OUTPUT``
      - 2
      - Buffew of a singwe-pwanaw video output stweam, see
	:wef:`output`.
    * - ``V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE``
      - 10
      - Buffew of a muwti-pwanaw video output stweam, see :wef:`output`.
    * - ``V4W2_BUF_TYPE_VIDEO_OVEWWAY``
      - 3
      - Buffew fow video ovewway, see :wef:`ovewway`.
    * - ``V4W2_BUF_TYPE_VBI_CAPTUWE``
      - 4
      - Buffew of a waw VBI captuwe stweam, see :wef:`waw-vbi`.
    * - ``V4W2_BUF_TYPE_VBI_OUTPUT``
      - 5
      - Buffew of a waw VBI output stweam, see :wef:`waw-vbi`.
    * - ``V4W2_BUF_TYPE_SWICED_VBI_CAPTUWE``
      - 6
      - Buffew of a swiced VBI captuwe stweam, see :wef:`swiced`.
    * - ``V4W2_BUF_TYPE_SWICED_VBI_OUTPUT``
      - 7
      - Buffew of a swiced VBI output stweam, see :wef:`swiced`.
    * - ``V4W2_BUF_TYPE_VIDEO_OUTPUT_OVEWWAY``
      - 8
      - Buffew fow video output ovewway (OSD), see :wef:`osd`.
    * - ``V4W2_BUF_TYPE_SDW_CAPTUWE``
      - 11
      - Buffew fow Softwawe Defined Wadio (SDW) captuwe stweam, see
	:wef:`sdw`.
    * - ``V4W2_BUF_TYPE_SDW_OUTPUT``
      - 12
      - Buffew fow Softwawe Defined Wadio (SDW) output stweam, see
	:wef:`sdw`.
    * - ``V4W2_BUF_TYPE_META_CAPTUWE``
      - 13
      - Buffew fow metadata captuwe, see :wef:`metadata`.
    * - ``V4W2_BUF_TYPE_META_OUTPUT``
      - 14
      - Buffew fow metadata output, see :wef:`metadata`.


.. _buffew-fwags:

Buffew Fwags
============

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{6.5cm}|p{1.8cm}|p{9.0cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       65 18 70

    * .. _`V4W2-BUF-FWAG-MAPPED`:

      - ``V4W2_BUF_FWAG_MAPPED``
      - 0x00000001
      - The buffew wesides in device memowy and has been mapped into the
	appwication's addwess space, see :wef:`mmap` fow detaiws.
	Dwivews set ow cweaw this fwag when the
	:wef:`VIDIOC_QUEWYBUF`,
	:wef:`VIDIOC_QBUF` ow
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw is cawwed. Set by the
	dwivew.
    * .. _`V4W2-BUF-FWAG-QUEUED`:

      - ``V4W2_BUF_FWAG_QUEUED``
      - 0x00000002
      - Intewnawwy dwivews maintain two buffew queues, an incoming and
	outgoing queue. When this fwag is set, the buffew is cuwwentwy on
	the incoming queue. It automaticawwy moves to the outgoing queue
	aftew the buffew has been fiwwed (captuwe devices) ow dispwayed
	(output devices). Dwivews set ow cweaw this fwag when the
	``VIDIOC_QUEWYBUF`` ioctw is cawwed. Aftew (successfuw) cawwing
	the ``VIDIOC_QBUF``\ ioctw it is awways set and aftew
	``VIDIOC_DQBUF`` awways cweawed.
    * .. _`V4W2-BUF-FWAG-DONE`:

      - ``V4W2_BUF_FWAG_DONE``
      - 0x00000004
      - When this fwag is set, the buffew is cuwwentwy on the outgoing
	queue, weady to be dequeued fwom the dwivew. Dwivews set ow cweaw
	this fwag when the ``VIDIOC_QUEWYBUF`` ioctw is cawwed. Aftew
	cawwing the ``VIDIOC_QBUF`` ow ``VIDIOC_DQBUF`` it is awways
	cweawed. Of couwse a buffew cannot be on both queues at the same
	time, the ``V4W2_BUF_FWAG_QUEUED`` and ``V4W2_BUF_FWAG_DONE`` fwag
	awe mutuawwy excwusive. They can be both cweawed howevew, then the
	buffew is in "dequeued" state, in the appwication domain so to
	say.
    * .. _`V4W2-BUF-FWAG-EWWOW`:

      - ``V4W2_BUF_FWAG_EWWOW``
      - 0x00000040
      - When this fwag is set, the buffew has been dequeued successfuwwy,
	awthough the data might have been cowwupted. This is wecovewabwe,
	stweaming may continue as nowmaw and the buffew may be weused
	nowmawwy. Dwivews set this fwag when the ``VIDIOC_DQBUF`` ioctw is
	cawwed.
    * .. _`V4W2-BUF-FWAG-IN-WEQUEST`:

      - ``V4W2_BUF_FWAG_IN_WEQUEST``
      - 0x00000080
      - This buffew is pawt of a wequest that hasn't been queued yet.
    * .. _`V4W2-BUF-FWAG-KEYFWAME`:

      - ``V4W2_BUF_FWAG_KEYFWAME``
      - 0x00000008
      - Dwivews set ow cweaw this fwag when cawwing the ``VIDIOC_DQBUF``
	ioctw. It may be set by video captuwe devices when the buffew
	contains a compwessed image which is a key fwame (ow fiewd), i. e.
	can be decompwessed on its own. Awso known as an I-fwame.
	Appwications can set this bit when ``type`` wefews to an output
	stweam.
    * .. _`V4W2-BUF-FWAG-PFWAME`:

      - ``V4W2_BUF_FWAG_PFWAME``
      - 0x00000010
      - Simiwaw to ``V4W2_BUF_FWAG_KEYFWAME`` this fwags pwedicted fwames
	ow fiewds which contain onwy diffewences to a pwevious key fwame.
	Appwications can set this bit when ``type`` wefews to an output
	stweam.
    * .. _`V4W2-BUF-FWAG-BFWAME`:

      - ``V4W2_BUF_FWAG_BFWAME``
      - 0x00000020
      - Simiwaw to ``V4W2_BUF_FWAG_KEYFWAME`` this fwags a bi-diwectionaw
	pwedicted fwame ow fiewd which contains onwy the diffewences
	between the cuwwent fwame and both the pweceding and fowwowing key
	fwames to specify its content. Appwications can set this bit when
	``type`` wefews to an output stweam.
    * .. _`V4W2-BUF-FWAG-TIMECODE`:

      - ``V4W2_BUF_FWAG_TIMECODE``
      - 0x00000100
      - The ``timecode`` fiewd is vawid. Dwivews set ow cweaw this fwag
	when the ``VIDIOC_DQBUF`` ioctw is cawwed. Appwications can set
	this bit and the cowwesponding ``timecode`` stwuctuwe when
	``type`` wefews to an output stweam.
    * .. _`V4W2-BUF-FWAG-PWEPAWED`:

      - ``V4W2_BUF_FWAG_PWEPAWED``
      - 0x00000400
      - The buffew has been pwepawed fow I/O and can be queued by the
	appwication. Dwivews set ow cweaw this fwag when the
	:wef:`VIDIOC_QUEWYBUF <VIDIOC_QUEWYBUF>`,
	:wef:`VIDIOC_PWEPAWE_BUF <VIDIOC_QBUF>`,
	:wef:`VIDIOC_QBUF <VIDIOC_QBUF>` ow
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw is cawwed.
    * .. _`V4W2-BUF-FWAG-NO-CACHE-INVAWIDATE`:

      - ``V4W2_BUF_FWAG_NO_CACHE_INVAWIDATE``
      - 0x00000800
      - Caches do not have to be invawidated fow this buffew. Typicawwy
	appwications shaww use this fwag if the data captuwed in the
	buffew is not going to be touched by the CPU, instead the buffew
	wiww, pwobabwy, be passed on to a DMA-capabwe hawdwawe unit fow
	fuwthew pwocessing ow output. This fwag is ignowed unwess the
	queue is used fow :wef:`memowy mapping <mmap>` stweaming I/O and
	wepowts :wef:`V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS
	<V4W2-BUF-CAP-SUPPOWTS-MMAP-CACHE-HINTS>` capabiwity.
    * .. _`V4W2-BUF-FWAG-NO-CACHE-CWEAN`:

      - ``V4W2_BUF_FWAG_NO_CACHE_CWEAN``
      - 0x00001000
      - Caches do not have to be cweaned fow this buffew. Typicawwy
	appwications shaww use this fwag fow output buffews if the data in
	this buffew has not been cweated by the CPU but by some
	DMA-capabwe unit, in which case caches have not been used. This fwag
	is ignowed unwess the queue is used fow :wef:`memowy mapping <mmap>`
	stweaming I/O and wepowts :wef:`V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS
	<V4W2-BUF-CAP-SUPPOWTS-MMAP-CACHE-HINTS>` capabiwity.
    * .. _`V4W2-BUF-FWAG-M2M-HOWD-CAPTUWE-BUF`:

      - ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF``
      - 0x00000200
      - Onwy vawid if stwuct :c:type:`v4w2_wequestbuffews` fwag ``V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF`` is
	set. It is typicawwy used with statewess decodews whewe muwtipwe
	output buffews each decode to a swice of the decoded fwame.
	Appwications can set this fwag when queueing the output buffew
	to pwevent the dwivew fwom dequeueing the captuwe buffew aftew
	the output buffew has been decoded (i.e. the captuwe buffew is
	'hewd'). If the timestamp of this output buffew diffews fwom that
	of the pwevious output buffew, then that indicates the stawt of a
	new fwame and the pweviouswy hewd captuwe buffew is dequeued.
    * .. _`V4W2-BUF-FWAG-WAST`:

      - ``V4W2_BUF_FWAG_WAST``
      - 0x00100000
      - Wast buffew pwoduced by the hawdwawe. mem2mem codec dwivews set
	this fwag on the captuwe queue fow the wast buffew when the
	:wef:`VIDIOC_QUEWYBUF` ow
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw is cawwed. Due to
	hawdwawe wimitations, the wast buffew may be empty. In this case
	the dwivew wiww set the ``bytesused`` fiewd to 0, wegawdwess of
	the fowmat. Any subsequent caww to the
	:wef:`VIDIOC_DQBUF <VIDIOC_QBUF>` ioctw wiww not bwock anymowe,
	but wetuwn an ``EPIPE`` ewwow code.
    * .. _`V4W2-BUF-FWAG-WEQUEST-FD`:

      - ``V4W2_BUF_FWAG_WEQUEST_FD``
      - 0x00800000
      - The ``wequest_fd`` fiewd contains a vawid fiwe descwiptow.
    * .. _`V4W2-BUF-FWAG-TIMESTAMP-MASK`:

      - ``V4W2_BUF_FWAG_TIMESTAMP_MASK``
      - 0x0000e000
      - Mask fow timestamp types bewow. To test the timestamp type, mask
	out bits not bewonging to timestamp type by pewfowming a wogicaw
	and opewation with buffew fwags and timestamp mask.
    * .. _`V4W2-BUF-FWAG-TIMESTAMP-UNKNOWN`:

      - ``V4W2_BUF_FWAG_TIMESTAMP_UNKNOWN``
      - 0x00000000
      - Unknown timestamp type. This type is used by dwivews befowe Winux
	3.9 and may be eithew monotonic (see bewow) ow weawtime (waww
	cwock). Monotonic cwock has been favouwed in embedded systems
	wheweas most of the dwivews use the weawtime cwock. Eithew kinds
	of timestamps awe avaiwabwe in usew space via
	:c:func:`cwock_gettime` using cwock IDs ``CWOCK_MONOTONIC``
	and ``CWOCK_WEAWTIME``, wespectivewy.
    * .. _`V4W2-BUF-FWAG-TIMESTAMP-MONOTONIC`:

      - ``V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC``
      - 0x00002000
      - The buffew timestamp has been taken fwom the ``CWOCK_MONOTONIC``
	cwock. To access the same cwock outside V4W2, use
	:c:func:`cwock_gettime`.
    * .. _`V4W2-BUF-FWAG-TIMESTAMP-COPY`:

      - ``V4W2_BUF_FWAG_TIMESTAMP_COPY``
      - 0x00004000
      - The CAPTUWE buffew timestamp has been taken fwom the cowwesponding
	OUTPUT buffew. This fwag appwies onwy to mem2mem devices.
    * .. _`V4W2-BUF-FWAG-TSTAMP-SWC-MASK`:

      - ``V4W2_BUF_FWAG_TSTAMP_SWC_MASK``
      - 0x00070000
      - Mask fow timestamp souwces bewow. The timestamp souwce defines the
	point of time the timestamp is taken in wewation to the fwame.
	Wogicaw 'and' opewation between the ``fwags`` fiewd and
	``V4W2_BUF_FWAG_TSTAMP_SWC_MASK`` pwoduces the vawue of the
	timestamp souwce. Appwications must set the timestamp souwce when
	``type`` wefews to an output stweam and
	``V4W2_BUF_FWAG_TIMESTAMP_COPY`` is set.
    * .. _`V4W2-BUF-FWAG-TSTAMP-SWC-EOF`:

      - ``V4W2_BUF_FWAG_TSTAMP_SWC_EOF``
      - 0x00000000
      - End Of Fwame. The buffew timestamp has been taken when the wast
	pixew of the fwame has been weceived ow the wast pixew of the
	fwame has been twansmitted. In pwactice, softwawe genewated
	timestamps wiww typicawwy be wead fwom the cwock a smaww amount of
	time aftew the wast pixew has been weceived ow twansmitten,
	depending on the system and othew activity in it.
    * .. _`V4W2-BUF-FWAG-TSTAMP-SWC-SOE`:

      - ``V4W2_BUF_FWAG_TSTAMP_SWC_SOE``
      - 0x00010000
      - Stawt Of Exposuwe. The buffew timestamp has been taken when the
	exposuwe of the fwame has begun. This is onwy vawid fow the
	``V4W2_BUF_TYPE_VIDEO_CAPTUWE`` buffew type.

.. waw:: watex

    \nowmawsize

enum v4w2_memowy
================

.. tabuwawcowumns:: |p{5.0cm}|p{0.8cm}|p{11.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_MEMOWY_MMAP``
      - 1
      - The buffew is used fow :wef:`memowy mapping <mmap>` I/O.
    * - ``V4W2_MEMOWY_USEWPTW``
      - 2
      - The buffew is used fow :wef:`usew pointew <usewp>` I/O.
    * - ``V4W2_MEMOWY_OVEWWAY``
      - 3
      - [to do]
    * - ``V4W2_MEMOWY_DMABUF``
      - 4
      - The buffew is used fow :wef:`DMA shawed buffew <dmabuf>` I/O.

.. _memowy-fwags:

Memowy Consistency Fwags
------------------------

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{7.0cm}|p{2.1cm}|p{8.4cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`V4W2-MEMOWY-FWAG-NON-COHEWENT`:

      - ``V4W2_MEMOWY_FWAG_NON_COHEWENT``
      - 0x00000001
      - A buffew is awwocated eithew in cohewent (it wiww be automaticawwy
	cohewent between the CPU and the bus) ow non-cohewent memowy. The
	wattew can pwovide pewfowmance gains, fow instance the CPU cache
	sync/fwush opewations can be avoided if the buffew is accessed by the
	cowwesponding device onwy and the CPU does not wead/wwite to/fwom that
	buffew. Howevew, this wequiwes extwa cawe fwom the dwivew -- it must
	guawantee memowy consistency by issuing a cache fwush/sync when
	consistency is needed. If this fwag is set V4W2 wiww attempt to
	awwocate the buffew in non-cohewent memowy. The fwag takes effect
	onwy if the buffew is used fow :wef:`memowy mapping <mmap>` I/O and the
	queue wepowts the :wef:`V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS
	<V4W2-BUF-CAP-SUPPOWTS-MMAP-CACHE-HINTS>` capabiwity.

.. waw:: watex

    \nowmawsize

Timecodes
=========

The :c:type:`v4w2_buffew_timecode` stwuctuwe is designed to howd a
:wef:`smpte12m` ow simiwaw timecode.
(stwuct :c:type:`timevaw` timestamps awe stowed in the stwuct
:c:type:`v4w2_buffew` ``timestamp`` fiewd.)

.. c:type:: v4w2_timecode

stwuct v4w2_timecode
--------------------

.. tabuwawcowumns:: |p{1.4cm}|p{2.8cm}|p{13.1cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Fwame wate the timecodes awe based on, see :wef:`timecode-type`.
    * - __u32
      - ``fwags``
      - Timecode fwags, see :wef:`timecode-fwags`.
    * - __u8
      - ``fwames``
      - Fwame count, 0 ... 23/24/29/49/59, depending on the type of
	timecode.
    * - __u8
      - ``seconds``
      - Seconds count, 0 ... 59. This is a binawy, not BCD numbew.
    * - __u8
      - ``minutes``
      - Minutes count, 0 ... 59. This is a binawy, not BCD numbew.
    * - __u8
      - ``houws``
      - Houws count, 0 ... 29. This is a binawy, not BCD numbew.
    * - __u8
      - ``usewbits``\ [4]
      - The "usew gwoup" bits fwom the timecode.


.. _timecode-type:

Timecode Types
--------------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TC_TYPE_24FPS``
      - 1
      - 24 fwames pew second, i. e. fiwm.
    * - ``V4W2_TC_TYPE_25FPS``
      - 2
      - 25 fwames pew second, i. e. PAW ow SECAM video.
    * - ``V4W2_TC_TYPE_30FPS``
      - 3
      - 30 fwames pew second, i. e. NTSC video.
    * - ``V4W2_TC_TYPE_50FPS``
      - 4
      -
    * - ``V4W2_TC_TYPE_60FPS``
      - 5
      -


.. _timecode-fwags:

Timecode Fwags
--------------

.. tabuwawcowumns:: |p{6.6cm}|p{1.4cm}|p{9.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_TC_FWAG_DWOPFWAME``
      - 0x0001
      - Indicates "dwop fwame" semantics fow counting fwames in 29.97 fps
	matewiaw. When set, fwame numbews 0 and 1 at the stawt of each
	minute, except minutes 0, 10, 20, 30, 40, 50 awe omitted fwom the
	count.
    * - ``V4W2_TC_FWAG_COWOWFWAME``
      - 0x0002
      - The "cowow fwame" fwag.
    * - ``V4W2_TC_USEWBITS_fiewd``
      - 0x000C
      - Fiewd mask fow the "binawy gwoup fwags".
    * - ``V4W2_TC_USEWBITS_USEWDEFINED``
      - 0x0000
      - Unspecified fowmat.
    * - ``V4W2_TC_USEWBITS_8BITCHAWS``
      - 0x0008
      - 8-bit ISO chawactews.
