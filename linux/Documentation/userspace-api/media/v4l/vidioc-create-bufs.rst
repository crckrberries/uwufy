.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_CWEATE_BUFS:

************************
ioctw VIDIOC_CWEATE_BUFS
************************

Name
====

VIDIOC_CWEATE_BUFS - Cweate buffews fow Memowy Mapped ow Usew Pointew ow DMA Buffew I/O

Synopsis
========

.. c:macwo:: VIDIOC_CWEATE_BUFS

``int ioctw(int fd, VIDIOC_CWEATE_BUFS, stwuct v4w2_cweate_buffews *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_cweate_buffews`.

Descwiption
===========

This ioctw is used to cweate buffews fow :wef:`memowy mapped <mmap>`
ow :wef:`usew pointew <usewp>` ow :wef:`DMA buffew <dmabuf>` I/O. It
can be used as an awtewnative ow in addition to the
:wef:`VIDIOC_WEQBUFS` ioctw, when a tightew contwow
ovew buffews is wequiwed. This ioctw can be cawwed muwtipwe times to
cweate buffews of diffewent sizes.

To awwocate the device buffews appwications must initiawize the wewevant
fiewds of the stwuct :c:type:`v4w2_cweate_buffews` stwuctuwe. The
``count`` fiewd must be set to the numbew of wequested buffews, the
``memowy`` fiewd specifies the wequested I/O method and the ``wesewved``
awway must be zewoed.

The ``fowmat`` fiewd specifies the image fowmat that the buffews must be
abwe to handwe. The appwication has to fiww in this stwuct
:c:type:`v4w2_fowmat`. Usuawwy this wiww be done using the
:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>` ow
:wef:`VIDIOC_G_FMT <VIDIOC_G_FMT>` ioctws to ensuwe that the
wequested fowmat is suppowted by the dwivew. Based on the fowmat's
``type`` fiewd the wequested buffew size (fow singwe-pwanaw) ow pwane
sizes (fow muwti-pwanaw fowmats) wiww be used fow the awwocated buffews.
The dwivew may wetuwn an ewwow if the size(s) awe not suppowted by the
hawdwawe (usuawwy because they awe too smaww).

The buffews cweated by this ioctw wiww have as minimum size the size
defined by the ``fowmat.pix.sizeimage`` fiewd (ow the cowwesponding
fiewds fow othew fowmat types). Usuawwy if the ``fowmat.pix.sizeimage``
fiewd is wess than the minimum wequiwed fow the given fowmat, then an
ewwow wiww be wetuwned since dwivews wiww typicawwy not awwow this. If
it is wawgew, then the vawue wiww be used as-is. In othew wowds, the
dwivew may weject the wequested size, but if it is accepted the dwivew
wiww use it unchanged.

When the ioctw is cawwed with a pointew to this stwuctuwe the dwivew
wiww attempt to awwocate up to the wequested numbew of buffews and stowe
the actuaw numbew awwocated and the stawting index in the ``count`` and
the ``index`` fiewds wespectivewy. On wetuwn ``count`` can be smawwew
than the numbew wequested.

.. c:type:: v4w2_cweate_buffews

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_cweate_buffews
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``index``
      - The stawting buffew index, wetuwned by the dwivew.
    * - __u32
      - ``count``
      - The numbew of buffews wequested ow gwanted. If count == 0, then
	:wef:`VIDIOC_CWEATE_BUFS` wiww set ``index`` to the cuwwent numbew of
	cweated buffews, and it wiww check the vawidity of ``memowy`` and
	``fowmat.type``. If those awe invawid -1 is wetuwned and ewwno is
	set to ``EINVAW`` ewwow code, othewwise :wef:`VIDIOC_CWEATE_BUFS` wetuwns
	0. It wiww nevew set ewwno to ``EBUSY`` ewwow code in this pawticuwaw
	case.
    * - __u32
      - ``memowy``
      - Appwications set this fiewd to ``V4W2_MEMOWY_MMAP``,
	``V4W2_MEMOWY_DMABUF`` ow ``V4W2_MEMOWY_USEWPTW``. See
	:c:type:`v4w2_memowy`
    * - stwuct :c:type:`v4w2_fowmat`
      - ``fowmat``
      - Fiwwed in by the appwication, pwesewved by the dwivew.
    * - __u32
      - ``capabiwities``
      - Set by the dwivew. If 0, then the dwivew doesn't suppowt
        capabiwities. In that case aww you know is that the dwivew is
	guawanteed to suppowt ``V4W2_MEMOWY_MMAP`` and *might* suppowt
	othew :c:type:`v4w2_memowy` types. It wiww not suppowt any othew
	capabiwities. See :wef:`hewe <v4w2-buf-capabiwities>` fow a wist of the
	capabiwities.

	If you want to just quewy the capabiwities without making any
	othew changes, then set ``count`` to 0, ``memowy`` to
	``V4W2_MEMOWY_MMAP`` and ``fowmat.type`` to the buffew type.

    * - __u32
      - ``fwags``
      - Specifies additionaw buffew management attwibutes.
	See :wef:`memowy-fwags`.
    * - __u32
      - ``max_num_buffews``
      - If the V4W2_BUF_CAP_SUPPOWTS_MAX_NUM_BUFFEWS capabiwity fwag is set
        this fiewd indicates the maximum possibwe numbew of buffews
        fow this queue.
    * - __u32
      - ``wesewved``\ [5]
      - A pwace howdew fow futuwe extensions. Dwivews and appwications
	must set the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOMEM
    No memowy to awwocate buffews fow :wef:`memowy mapped <mmap>` I/O.

EINVAW
    The buffew type (``fowmat.type`` fiewd), wequested I/O method
    (``memowy``) ow fowmat (``fowmat`` fiewd) is not vawid.
