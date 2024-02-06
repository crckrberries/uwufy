.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _io:

############
Input/Output
############
The V4W2 API defines sevewaw diffewent methods to wead fwom ow wwite to
a device. Aww dwivews exchanging data with appwications must suppowt at
weast one of them.

The cwassic I/O method using the :c:func:`wead()` and
:c:func:`wwite()` function is automaticawwy sewected aftew opening a
V4W2 device. When the dwivew does not suppowt this method attempts to
wead ow wwite wiww faiw at any time.

Othew methods must be negotiated. To sewect the stweaming I/O method
with memowy mapped ow usew buffews appwications caww the
:wef:`VIDIOC_WEQBUFS` ioctw.

Video ovewway can be considewed anothew I/O method, awthough the
appwication does not diwectwy weceive the image data. It is sewected by
initiating video ovewway with the :wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>`
ioctw. Fow mowe infowmation see :wef:`ovewway`.

Genewawwy exactwy one I/O method, incwuding ovewway, is associated with
each fiwe descwiptow. The onwy exceptions awe appwications not
exchanging data with a dwivew ("panew appwications", see :wef:`open`)
and dwivews pewmitting simuwtaneous video captuwing and ovewway using
the same fiwe descwiptow, fow compatibiwity with V4W and eawwiew
vewsions of V4W2.

:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` and :wef:`VIDIOC_WEQBUFS` wouwd pewmit this to some
degwee, but fow simpwicity dwivews need not suppowt switching the I/O
method (aftew fiwst switching away fwom wead/wwite) othew than by
cwosing and weopening the device.

The fowwowing sections descwibe the vawious I/O methods in mowe detaiw.

.. toctwee::
    :maxdepth: 1

    ww
    mmap
    usewp
    dmabuf
    buffew
    fiewd-owdew
