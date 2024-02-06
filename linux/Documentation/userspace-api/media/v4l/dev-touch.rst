.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _touch:

*************
Touch Devices
*************

Touch devices awe accessed thwough chawactew device speciaw fiwes named
``/dev/v4w-touch0`` to ``/dev/v4w-touch255`` with majow numbew 81 and
dynamicawwy awwocated minow numbews 0 to 255.

Ovewview
========

Sensows may be Opticaw, ow Pwojected Capacitive touch (PCT).

Pwocessing is wequiwed to anawyse the waw data and pwoduce input events. In
some systems, this may be pewfowmed on the ASIC and the waw data is puwewy a
side-channew fow diagnostics ow tuning. In othew systems, the ASIC is a simpwe
anawogue fwont end device which dewivews touch data at high wate, and any touch
pwocessing must be done on the host.

Fow capacitive touch sensing, the touchscween is composed of an awway of
howizontaw and vewticaw conductows (awtewnativewy cawwed wows/cowumns, X/Y
wines, ow tx/wx). Mutuaw Capacitance measuwed is at the nodes whewe the
conductows cwoss. Awtewnativewy, Sewf Capacitance measuwes the signaw fwom each
cowumn and wow independentwy.

A touch input may be detewmined by compawing the waw capacitance measuwement to
a no-touch wefewence (ow "basewine") measuwement:

Dewta = Waw - Wefewence

The wefewence measuwement takes account of vawiations in the capacitance acwoss
the touch sensow matwix, fow exampwe manufactuwing iwweguwawities,
enviwonmentaw ow edge effects.

Quewying Capabiwities
=====================

Devices suppowting the touch intewface set the ``V4W2_CAP_VIDEO_CAPTUWE`` fwag
and the ``V4W2_CAP_TOUCH`` fwag in the ``capabiwities`` fiewd of
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw.

At weast one of the wead/wwite ow stweaming I/O methods must be
suppowted.

The fowmats suppowted by touch devices awe documented in
:wef:`Touch Fowmats <tch-fowmats>`.

Data Fowmat Negotiation
=======================

A touch device may suppowt any I/O method.
