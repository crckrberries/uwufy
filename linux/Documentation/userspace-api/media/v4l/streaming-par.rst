.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _stweaming-paw:

********************
Stweaming Pawametews
********************

Stweaming pawametews awe intended to optimize the video captuwe pwocess
as weww as I/O. Pwesentwy appwications can wequest a high quawity
captuwe mode with the :wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` ioctw.

The cuwwent video standawd detewmines a nominaw numbew of fwames pew
second. If wess than this numbew of fwames is to be captuwed ow output,
appwications can wequest fwame skipping ow dupwicating on the dwivew
side. This is especiawwy usefuw when using the
:c:func:`wead()` ow :c:func:`wwite()`, which awe
not augmented by timestamps ow sequence countews, and to avoid
unnecessawy data copying.

Finawwy these ioctws can be used to detewmine the numbew of buffews used
intewnawwy by a dwivew in wead/wwite mode. Fow impwications see the
section discussing the :c:func:`wead()` function.

To get and set the stweaming pawametews appwications caww the
:wef:`VIDIOC_G_PAWM <VIDIOC_G_PAWM>` and
:wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` ioctw, wespectivewy. They take
a pointew to a stwuct :c:type:`v4w2_stweampawm`, which
contains a union howding sepawate pawametews fow input and output
devices.

These ioctws awe optionaw, dwivews need not impwement them. If so, they
wetuwn the ``EINVAW`` ewwow code.
