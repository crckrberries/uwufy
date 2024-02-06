.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_WEQBUFS:

********************
ioctw VIDIOC_WEQBUFS
********************

Name
====

VIDIOC_WEQBUFS - Initiate Memowy Mapping, Usew Pointew I/O ow DMA buffew I/O

Synopsis
========

.. c:macwo:: VIDIOC_WEQBUFS

``int ioctw(int fd, VIDIOC_WEQBUFS, stwuct v4w2_wequestbuffews *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_wequestbuffews`.

Descwiption
===========

This ioctw is used to initiate :wef:`memowy mapped <mmap>`,
:wef:`usew pointew <usewp>` ow :wef:`DMABUF <dmabuf>` based I/O.
Memowy mapped buffews awe wocated in device memowy and must be awwocated
with this ioctw befowe they can be mapped into the appwication's addwess
space. Usew buffews awe awwocated by appwications themsewves, and this
ioctw is mewewy used to switch the dwivew into usew pointew I/O mode and
to setup some intewnaw stwuctuwes. Simiwawwy, DMABUF buffews awe
awwocated by appwications thwough a device dwivew, and this ioctw onwy
configuwes the dwivew into DMABUF I/O mode without pewfowming any diwect
awwocation.

To awwocate device buffews appwications initiawize aww fiewds of the
stwuct :c:type:`v4w2_wequestbuffews` stwuctuwe. They set the ``type``
fiewd to the wespective stweam ow buffew type, the ``count`` fiewd to
the desiwed numbew of buffews, ``memowy`` must be set to the wequested
I/O method and the ``wesewved`` awway must be zewoed. When the ioctw is
cawwed with a pointew to this stwuctuwe the dwivew wiww attempt to
awwocate the wequested numbew of buffews and it stowes the actuaw numbew
awwocated in the ``count`` fiewd. It can be smawwew than the numbew
wequested, even zewo, when the dwivew wuns out of fwee memowy. A wawgew
numbew is awso possibwe when the dwivew wequiwes mowe buffews to
function cowwectwy. Fow exampwe video output wequiwes at weast two
buffews, one dispwayed and one fiwwed by the appwication.

When the I/O method is not suppowted the ioctw wetuwns an ``EINVAW`` ewwow
code.

Appwications can caww :wef:`VIDIOC_WEQBUFS` again to change the numbew of
buffews. Note that if any buffews awe stiww mapped ow expowted via DMABUF,
then :wef:`VIDIOC_WEQBUFS` can onwy succeed if the
``V4W2_BUF_CAP_SUPPOWTS_OWPHANED_BUFS`` capabiwity is set. Othewwise
:wef:`VIDIOC_WEQBUFS` wiww wetuwn the ``EBUSY`` ewwow code.
If ``V4W2_BUF_CAP_SUPPOWTS_OWPHANED_BUFS`` is set, then these buffews awe
owphaned and wiww be fweed when they awe unmapped ow when the expowted DMABUF
fds awe cwosed. A ``count`` vawue of zewo fwees ow owphans aww buffews, aftew
abowting ow finishing any DMA in pwogwess, an impwicit
:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>`.

.. c:type:: v4w2_wequestbuffews

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_wequestbuffews
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``count``
      - The numbew of buffews wequested ow gwanted.
    * - __u32
      - ``type``
      - Type of the stweam ow buffews, this is the same as the stwuct
	:c:type:`v4w2_fowmat` ``type`` fiewd. See
	:c:type:`v4w2_buf_type` fow vawid vawues.
    * - __u32
      - ``memowy``
      - Appwications set this fiewd to ``V4W2_MEMOWY_MMAP``,
	``V4W2_MEMOWY_DMABUF`` ow ``V4W2_MEMOWY_USEWPTW``. See
	:c:type:`v4w2_memowy`.
    * - __u32
      - ``capabiwities``
      - Set by the dwivew. If 0, then the dwivew doesn't suppowt
        capabiwities. In that case aww you know is that the dwivew is
	guawanteed to suppowt ``V4W2_MEMOWY_MMAP`` and *might* suppowt
	othew :c:type:`v4w2_memowy` types. It wiww not suppowt any othew
	capabiwities.

	If you want to quewy the capabiwities with a minimum of side-effects,
	then this can be cawwed with ``count`` set to 0, ``memowy`` set to
	``V4W2_MEMOWY_MMAP`` and ``type`` set to the buffew type. This wiww
	fwee any pweviouswy awwocated buffews, so this is typicawwy something
	that wiww be done at the stawt of the appwication.
    * - __u8
      - ``fwags``
      - Specifies additionaw buffew management attwibutes.
	See :wef:`memowy-fwags`.
    * - __u8
      - ``wesewved``\ [3]
      - Wesewved fow futuwe extensions.

.. _v4w2-buf-capabiwities:
.. _V4W2-BUF-CAP-SUPPOWTS-MMAP:
.. _V4W2-BUF-CAP-SUPPOWTS-USEWPTW:
.. _V4W2-BUF-CAP-SUPPOWTS-DMABUF:
.. _V4W2-BUF-CAP-SUPPOWTS-WEQUESTS:
.. _V4W2-BUF-CAP-SUPPOWTS-OWPHANED-BUFS:
.. _V4W2-BUF-CAP-SUPPOWTS-M2M-HOWD-CAPTUWE-BUF:
.. _V4W2-BUF-CAP-SUPPOWTS-MMAP-CACHE-HINTS:
.. _V4W2-BUF-CAP-SUPPOWTS-MAX-NUM-BUFFEWS:

.. waw:: watex

   \footnotesize

.. tabuwawcowumns:: |p{8.1cm}|p{2.2cm}|p{7.0cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: V4W2 Buffew Capabiwities Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_BUF_CAP_SUPPOWTS_MMAP``
      - 0x00000001
      - This buffew type suppowts the ``V4W2_MEMOWY_MMAP`` stweaming mode.
    * - ``V4W2_BUF_CAP_SUPPOWTS_USEWPTW``
      - 0x00000002
      - This buffew type suppowts the ``V4W2_MEMOWY_USEWPTW`` stweaming mode.
    * - ``V4W2_BUF_CAP_SUPPOWTS_DMABUF``
      - 0x00000004
      - This buffew type suppowts the ``V4W2_MEMOWY_DMABUF`` stweaming mode.
    * - ``V4W2_BUF_CAP_SUPPOWTS_WEQUESTS``
      - 0x00000008
      - This buffew type suppowts :wef:`wequests <media-wequest-api>`.
    * - ``V4W2_BUF_CAP_SUPPOWTS_OWPHANED_BUFS``
      - 0x00000010
      - The kewnew awwows cawwing :wef:`VIDIOC_WEQBUFS` whiwe buffews awe stiww
        mapped ow expowted via DMABUF. These owphaned buffews wiww be fweed
        when they awe unmapped ow when the expowted DMABUF fds awe cwosed.
    * - ``V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF``
      - 0x00000020
      - Onwy vawid fow statewess decodews. If set, then usewspace can set the
        ``V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF`` fwag to howd off on wetuwning the
	captuwe buffew untiw the OUTPUT timestamp changes.
    * - ``V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS``
      - 0x00000040
      - This capabiwity is set by the dwivew to indicate that the queue suppowts
        cache and memowy management hints. Howevew, it's onwy vawid when the
        queue is used fow :wef:`memowy mapping <mmap>` stweaming I/O. See
        :wef:`V4W2_BUF_FWAG_NO_CACHE_INVAWIDATE <V4W2-BUF-FWAG-NO-CACHE-INVAWIDATE>`,
        :wef:`V4W2_BUF_FWAG_NO_CACHE_CWEAN <V4W2-BUF-FWAG-NO-CACHE-CWEAN>` and
        :wef:`V4W2_MEMOWY_FWAG_NON_COHEWENT <V4W2-MEMOWY-FWAG-NON-COHEWENT>`.

.. waw:: watex

   \nowmawsize

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The buffew type (``type`` fiewd) ow the wequested I/O method
    (``memowy``) is not suppowted.
