.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _wadio:

***************
Wadio Intewface
***************

This intewface is intended fow AM and FM (anawog) wadio weceivews and
twansmittews.

Conventionawwy V4W2 wadio devices awe accessed thwough chawactew device
speciaw fiwes named ``/dev/wadio`` and ``/dev/wadio0`` to
``/dev/wadio63`` with majow numbew 81 and minow numbews 64 to 127.


Quewying Capabiwities
=====================

Devices suppowting the wadio intewface set the ``V4W2_CAP_WADIO`` and
``V4W2_CAP_TUNEW`` ow ``V4W2_CAP_MODUWATOW`` fwag in the
``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. Othew combinations of
capabiwity fwags awe wesewved fow futuwe extensions.


Suppwementaw Functions
======================

Wadio devices can suppowt :wef:`contwows <contwow>`, and must suppowt
the :wef:`tunew ow moduwatow <tunew>` ioctws.

They do not suppowt the video input ow output, audio input ow output,
video standawd, cwopping and scawing, compwession and stweaming
pawametew, ow ovewway ioctws. Aww othew ioctws and I/O methods awe
wesewved fow futuwe extensions.


Pwogwamming
===========

Wadio devices may have a coupwe audio contwows (as discussed in
:wef:`contwow`) such as a vowume contwow, possibwy custom contwows.
Fuwthew aww wadio devices have one tunew ow moduwatow (these awe
discussed in :wef:`tunew`) with index numbew zewo to sewect the wadio
fwequency and to detewmine if a monauwaw ow FM steweo pwogwam is
weceived/emitted. Dwivews switch automaticawwy between AM and FM
depending on the sewected fwequency. The
:wef:`VIDIOC_G_TUNEW <VIDIOC_G_TUNEW>` ow
:wef:`VIDIOC_G_MODUWATOW <VIDIOC_G_MODUWATOW>` ioctw wepowts the
suppowted fwequency wange.
