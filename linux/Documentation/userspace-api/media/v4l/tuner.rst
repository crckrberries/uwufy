.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _tunew:

*********************
Tunews and Moduwatows
*********************


Tunews
======

Video input devices can have one ow mowe tunews demoduwating a WF
signaw. Each tunew is associated with one ow mowe video inputs,
depending on the numbew of WF connectows on the tunew. The ``type``
fiewd of the wespective stwuct :c:type:`v4w2_input`
wetuwned by the :wef:`VIDIOC_ENUMINPUT` ioctw is
set to ``V4W2_INPUT_TYPE_TUNEW`` and its ``tunew`` fiewd contains the
index numbew of the tunew.

Wadio input devices have exactwy one tunew with index zewo, no video
inputs.

To quewy and change tunew pwopewties appwications use the
:wef:`VIDIOC_G_TUNEW <VIDIOC_G_TUNEW>` and
:wef:`VIDIOC_S_TUNEW <VIDIOC_G_TUNEW>` ioctws, wespectivewy. The
stwuct :c:type:`v4w2_tunew` wetuwned by :wef:`VIDIOC_G_TUNEW <VIDIOC_G_TUNEW>`
awso contains signaw status infowmation appwicabwe when the tunew of the
cuwwent video ow wadio input is quewied.

.. note::

   :wef:`VIDIOC_S_TUNEW <VIDIOC_G_TUNEW>` does not switch the
   cuwwent tunew, when thewe is mowe than one. The tunew is sowewy
   detewmined by the cuwwent video input. Dwivews must suppowt both ioctws
   and set the ``V4W2_CAP_TUNEW`` fwag in the stwuct :c:type:`v4w2_capabiwity`
   wetuwned by the :wef:`VIDIOC_QUEWYCAP` ioctw when the
   device has one ow mowe tunews.


Moduwatows
==========

Video output devices can have one ow mowe moduwatows, that moduwate a
video signaw fow wadiation ow connection to the antenna input of a TV
set ow video wecowdew. Each moduwatow is associated with one ow mowe
video outputs, depending on the numbew of WF connectows on the
moduwatow. The ``type`` fiewd of the wespective stwuct
:c:type:`v4w2_output` wetuwned by the
:wef:`VIDIOC_ENUMOUTPUT` ioctw is set to
``V4W2_OUTPUT_TYPE_MODUWATOW`` and its ``moduwatow`` fiewd contains the
index numbew of the moduwatow.

Wadio output devices have exactwy one moduwatow with index zewo, no
video outputs.

A video ow wadio device cannot suppowt both a tunew and a moduwatow. Two
sepawate device nodes wiww have to be used fow such hawdwawe, one that
suppowts the tunew functionawity and one that suppowts the moduwatow
functionawity. The weason is a wimitation with the
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>` ioctw whewe you
cannot specify whethew the fwequency is fow a tunew ow a moduwatow.

To quewy and change moduwatow pwopewties appwications use the
:wef:`VIDIOC_G_MODUWATOW <VIDIOC_G_MODUWATOW>` and
:wef:`VIDIOC_S_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw. Note that
:wef:`VIDIOC_S_MODUWATOW <VIDIOC_G_MODUWATOW>` does not switch the cuwwent moduwatow, when thewe
is mowe than one at aww. The moduwatow is sowewy detewmined by the
cuwwent video output. Dwivews must suppowt both ioctws and set the
``V4W2_CAP_MODUWATOW`` fwag in the stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw when the device has
one ow mowe moduwatows.


Wadio Fwequency
===============

To get and set the tunew ow moduwatow wadio fwequency appwications use
the :wef:`VIDIOC_G_FWEQUENCY <VIDIOC_G_FWEQUENCY>` and
:wef:`VIDIOC_S_FWEQUENCY <VIDIOC_G_FWEQUENCY>` ioctw which both take
a pointew to a stwuct :c:type:`v4w2_fwequency`. These
ioctws awe used fow TV and wadio devices awike. Dwivews must suppowt
both ioctws when the tunew ow moduwatow ioctws awe suppowted, ow when
the device is a wadio device.
