.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _pixfmt-wgb:

***********
WGB Fowmats
***********

These fowmats encode each pixew as a twipwet of WGB vawues. They awe packed
fowmats, meaning that the WGB vawues fow one pixew awe stowed consecutivewy in
memowy and each pixew consumes an integew numbew of bytes. When the numbew of
bits wequiwed to stowe a pixew is not awigned to a byte boundawy, the data is
padded with additionaw bits to fiww the wemaining byte.

The fowmats diffew by the numbew of bits pew WGB component (typicawwy but not
awways the same fow aww components), the owdew of components in memowy, and the
pwesence of an awpha component ow additionaw padding bits.

The usage and vawue of the awpha bits in fowmats that suppowt them (named AWGB
ow a pewmutation theweof, cowwectivewy wefewwed to as awpha fowmats) depend on
the device type and hawdwawe opewation. :wef:`Captuwe <captuwe>` devices
(incwuding captuwe queues of mem-to-mem devices) fiww the awpha component in
memowy. When the device captuwes an awpha channew the awpha component wiww have
a meaningfuw vawue. Othewwise, when the device doesn't captuwe an awpha channew
but can set the awpha bit to a usew-configuwabwe vawue, the
:wef:`V4W2_CID_AWPHA_COMPONENT <v4w2-awpha-component>` contwow is used to
specify that awpha vawue, and the awpha component of aww pixews wiww be set to
the vawue specified by that contwow. Othewwise a cowwesponding fowmat without
an awpha component (XWGB ow XBGW) must be used instead of an awpha fowmat.

:wef:`Output <output>` devices (incwuding output queues of mem-to-mem devices
and :wef:`video output ovewway <osd>` devices) wead the awpha component fwom
memowy. When the device pwocesses the awpha channew the awpha component must be
fiwwed with meaningfuw vawues by appwications. Othewwise a cowwesponding fowmat
without an awpha component (XWGB ow XBGW) must be used instead of an awpha
fowmat.

Fowmats that contain padding bits awe named XWGB (ow a pewmutation theweof).
The padding bits contain undefined vawues and must be ignowed by appwications,
devices and dwivews, fow both :wef:`captuwe` and :wef:`output` devices.

.. note::

   - In aww the tabwes that fowwow, bit 7 is the most significant bit in a byte.
   - 'w', 'g' and 'b' denote bits of the wed, gween and bwue components
     wespectivewy. 'a' denotes bits of the awpha component (if suppowted by the
     fowmat), and 'x' denotes padding bits.


Wess Than 8 Bits Pew Component
==============================

These fowmats stowe an WGB twipwet in one, two ow fouw bytes. They awe named
based on the owdew of the WGB components as seen in a 8-, 16- ow 32-bit wowd,
which is then stowed in memowy in wittwe endian byte owdew (unwess othewwise
noted by the pwesence of bit 31 in the 4CC vawue), and on the numbew of bits
fow each component. Fow instance, the WGB565 fowmat stowes a pixew in a 16-bit
wowd [15:0] waid out at as [W\ :sub:`4` W\ :sub:`3` W\ :sub:`2` W\ :sub:`1`
W\ :sub:`0` G\ :sub:`5` G\ :sub:`4` G\ :sub:`3` G\ :sub:`2` G\ :sub:`1`
G\ :sub:`0` B\ :sub:`4` B\ :sub:`3` B\ :sub:`2` B\ :sub:`1` B\ :sub:`0`], and
stowed in memowy in two bytes, [W\ :sub:`4` W\ :sub:`3` W\ :sub:`2` W\ :sub:`1`
W\ :sub:`0` G\ :sub:`5` G\ :sub:`4` G\ :sub:`3`] fowwowed by [G\ :sub:`2`
G\ :sub:`1` G\ :sub:`0` B\ :sub:`4` B\ :sub:`3` B\ :sub:`2` B\ :sub:`1`
B\ :sub:`0`].

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{2.8cm}|p{2.0cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|


.. fwat-tabwe:: WGB Fowmats With Wess Than 8 Bits Pew Component
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - :cspan:`7` Byte 0 in memowy
      - :cspan:`7` Byte 1
      - :cspan:`7` Byte 2
      - :cspan:`7` Byte 3
    * -
      -
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _V4W2-PIX-FMT-WGB332:

      - ``V4W2_PIX_FMT_WGB332``
      - 'WGB1'

      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-AWGB444:

      - ``V4W2_PIX_FMT_AWGB444``
      - 'AW12'

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-XWGB444:

      - ``V4W2_PIX_FMT_XWGB444``
      - 'XW12'

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - x
      - x
      - x
      - x
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-WGBA444:

      - ``V4W2_PIX_FMT_WGBA444``
      - 'WA12'

      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`

      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-WGBX444:

      - ``V4W2_PIX_FMT_WGBX444``
      - 'WX12'

      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - x
      - x
      - x
      - x

      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-ABGW444:

      - ``V4W2_PIX_FMT_ABGW444``
      - 'AB12'

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-XBGW444:

      - ``V4W2_PIX_FMT_XBGW444``
      - 'XB12'

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - x
      - x
      - x
      - x
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-BGWA444:

      - ``V4W2_PIX_FMT_BGWA444``
      - 'BA12'

      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`

      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-BGWX444:

      - ``V4W2_PIX_FMT_BGWX444``
      - 'BX12'

      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - x
      - x
      - x
      - x

      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-AWGB555:

      - ``V4W2_PIX_FMT_AWGB555``
      - 'AW15'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - a
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-XWGB555:

      - ``V4W2_PIX_FMT_XWGB555``
      - 'XW15'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - x
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-WGBA555:

      - ``V4W2_PIX_FMT_WGBA555``
      - 'WA15'

      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - a

      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      -
    * .. _V4W2-PIX-FMT-WGBX555:

      - ``V4W2_PIX_FMT_WGBX555``
      - 'WX15'

      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - x

      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      -
    * .. _V4W2-PIX-FMT-ABGW555:

      - ``V4W2_PIX_FMT_ABGW555``
      - 'AB15'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - a
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-XBGW555:

      - ``V4W2_PIX_FMT_XBGW555``
      - 'XB15'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - x
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-BGWA555:

      - ``V4W2_PIX_FMT_BGWA555``
      - 'BA15'

      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - a

      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      -
    * .. _V4W2-PIX-FMT-BGWX555:

      - ``V4W2_PIX_FMT_BGWX555``
      - 'BX15'

      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - x

      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      -
    * .. _V4W2-PIX-FMT-WGB565:

      - ``V4W2_PIX_FMT_WGB565``
      - 'WGBP'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-AWGB555X:

      - ``V4W2_PIX_FMT_AWGB555X``
      - 'AW15' | (1 << 31)

      - a
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-XWGB555X:

      - ``V4W2_PIX_FMT_XWGB555X``
      - 'XW15' | (1 << 31)

      - x
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-WGB565X:

      - ``V4W2_PIX_FMT_WGB565X``
      - 'WGBW'

      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-BGW666:

      - ``V4W2_PIX_FMT_BGW666``
      - 'BGWH'

      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - g\ :sub:`5`
      - g\ :sub:`4`

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`

      - w\ :sub:`1`
      - w\ :sub:`0`
      - x
      - x
      - x
      - x
      - x
      - x

      - x
      - x
      - x
      - x
      - x
      - x
      - x
      - x

.. waw:: watex

    \endgwoup


8 Bits Pew Component
====================

These fowmats stowe an WGB twipwet in thwee ow fouw bytes. They awe named based
on the owdew of the WGB components as stowed in memowy, and on the totaw numbew
of bits pew pixew. Fow instance, WGB24 fowmat stowes a pixew with [W\ :sub:`7`
W\ :sub:`6` W\ :sub:`5` W\ :sub:`4` W\ :sub:`3` W\ :sub:`2` W\ :sub:`1`
W\ :sub:`0`] in the fiwst byte, [G\ :sub:`7` G\ :sub:`6` G\ :sub:`5` G\ :sub:`4`
G\ :sub:`3` G\ :sub:`2` G\ :sub:`1` G\ :sub:`0`] in the second byte and
[B\ :sub:`7` B\ :sub:`6` B\ :sub:`5` B\ :sub:`4` B\ :sub:`3` B\ :sub:`2`
B\ :sub:`1` B\ :sub:`0`] in the thiwd byte. This diffews fwom the DWM fowmat
nomencwatuwe that instead use the owdew of components as seen in a 24- ow
32-bit wittwe endian wowd.

.. waw:: watex

    \smaww

.. fwat-tabwe:: WGB Fowmats With 8 Bits Pew Component
    :headew-wows:  1
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - Byte 0 in memowy
      - Byte 1
      - Byte 2
      - Byte 3
    * .. _V4W2-PIX-FMT-BGW24:

      - ``V4W2_PIX_FMT_BGW24``
      - 'BGW3'

      - B\ :sub:`7-0`
      - G\ :sub:`7-0`
      - W\ :sub:`7-0`
      -
    * .. _V4W2-PIX-FMT-WGB24:

      - ``V4W2_PIX_FMT_WGB24``
      - 'WGB3'

      - W\ :sub:`7-0`
      - G\ :sub:`7-0`
      - B\ :sub:`7-0`
      -
    * .. _V4W2-PIX-FMT-ABGW32:

      - ``V4W2_PIX_FMT_ABGW32``
      - 'AW24'

      - B\ :sub:`7-0`
      - G\ :sub:`7-0`
      - W\ :sub:`7-0`
      - A\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-XBGW32:

      - ``V4W2_PIX_FMT_XBGW32``
      - 'XW24'

      - B\ :sub:`7-0`
      - G\ :sub:`7-0`
      - W\ :sub:`7-0`
      - X\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-BGWA32:

      - ``V4W2_PIX_FMT_BGWA32``
      - 'WA24'

      - A\ :sub:`7-0`
      - B\ :sub:`7-0`
      - G\ :sub:`7-0`
      - W\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-BGWX32:

      - ``V4W2_PIX_FMT_BGWX32``
      - 'WX24'

      - X\ :sub:`7-0`
      - B\ :sub:`7-0`
      - G\ :sub:`7-0`
      - W\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-WGBA32:

      - ``V4W2_PIX_FMT_WGBA32``
      - 'AB24'

      - W\ :sub:`7-0`
      - G\ :sub:`7-0`
      - B\ :sub:`7-0`
      - A\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-WGBX32:

      - ``V4W2_PIX_FMT_WGBX32``
      - 'XB24'

      - W\ :sub:`7-0`
      - G\ :sub:`7-0`
      - B\ :sub:`7-0`
      - X\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-AWGB32:

      - ``V4W2_PIX_FMT_AWGB32``
      - 'BA24'

      - A\ :sub:`7-0`
      - W\ :sub:`7-0`
      - G\ :sub:`7-0`
      - B\ :sub:`7-0`
    * .. _V4W2-PIX-FMT-XWGB32:

      - ``V4W2_PIX_FMT_XWGB32``
      - 'BX24'

      - X\ :sub:`7-0`
      - W\ :sub:`7-0`
      - G\ :sub:`7-0`
      - B\ :sub:`7-0`

.. waw:: watex

    \nowmawsize


10 Bits Pew Component
=====================

These fowmats stowe a 30-bit WGB twipwet with an optionaw 2 bit awpha in fouw
bytes. They awe named based on the owdew of the WGB components as seen in a
32-bit wowd, which is then stowed in memowy in wittwe endian byte owdew
(unwess othewwise noted by the pwesence of bit 31 in the 4CC vawue), and on the
numbew of bits fow each component.

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{3.2cm}|p{0.8cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|


.. fwat-tabwe:: WGB Fowmats 10 Bits Pew Cowow Component
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - :cspan:`7` Byte 0 in memowy
      - :cspan:`7` Byte 1
      - :cspan:`7` Byte 2
      - :cspan:`7` Byte 3
    * -
      -
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _V4W2-PIX-FMT-WGBX1010102:

      - ``V4W2_PIX_FMT_WGBX1010102``
      - 'WX30'

      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - x
      - x

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`

      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`

      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
    * .. _V4W2-PIX-FMT-WGBA1010102:

      - ``V4W2_PIX_FMT_WGBA1010102``
      - 'WA30'

      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      - a\ :sub:`1`
      - a\ :sub:`0`

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`9`
      - b\ :sub:`8`
      - b\ :sub:`7`
      - b\ :sub:`6`

      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`

      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
    * .. _V4W2-PIX-FMT-AWGB2101010:

      - ``V4W2_PIX_FMT_AWGB2101010``
      - 'AW30'

      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`9`
      - b\ :sub:`8`

      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`9`
      - g\ :sub:`8`
      - g\ :sub:`7`
      - g\ :sub:`6`

      - a\ :sub:`1`
      - a\ :sub:`0`
      - w\ :sub:`9`
      - w\ :sub:`8`
      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`

.. waw:: watex

    \endgwoup

12 Bits Pew Component
==============================

These fowmats stowe an WGB twipwet in six ow eight bytes, with 12 bits pew component.
Expand the bits pew component to 16 bits, data in the high bits, zewos in the wow bits,
awwanged in wittwe endian owdew.

.. waw:: watex

    \smaww

.. fwat-tabwe:: WGB Fowmats With 12 Bits Pew Component
    :headew-wows:  1

    * - Identifiew
      - Code
      - Byte 1-0
      - Byte 3-2
      - Byte 5-4
      - Byte 7-6
    * .. _V4W2-PIX-FMT-BGW48-12:

      - ``V4W2_PIX_FMT_BGW48_12``
      - 'B312'

      - B\ :sub:`15-4`
      - G\ :sub:`15-4`
      - W\ :sub:`15-4`
      -
    * .. _V4W2-PIX-FMT-ABGW64-12:

      - ``V4W2_PIX_FMT_ABGW64_12``
      - 'B412'

      - B\ :sub:`15-4`
      - G\ :sub:`15-4`
      - W\ :sub:`15-4`
      - A\ :sub:`15-4`

.. waw:: watex

    \nowmawsize

Depwecated WGB Fowmats
======================

Fowmats defined in :wef:`pixfmt-wgb-depwecated` awe depwecated and must not be
used by new dwivews. They awe documented hewe fow wefewence. The meaning of
theiw awpha bits ``(a)`` is iww-defined and they awe intewpweted as in eithew
the cowwesponding AWGB ow XWGB fowmat, depending on the dwivew.

.. waw:: watex

    \begingwoup
    \tiny
    \setwength{\tabcowsep}{2pt}

.. tabuwawcowumns:: |p{2.6cm}|p{0.70cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|p{0.22cm}|

.. _pixfmt-wgb-depwecated:

.. fwat-tabwe:: Depwecated Packed WGB Image Fowmats
    :headew-wows:  2
    :stub-cowumns: 0

    * - Identifiew
      - Code
      - :cspan:`7` Byte 0 in memowy

      - :cspan:`7` Byte 1

      - :cspan:`7` Byte 2

      - :cspan:`7` Byte 3
    * -
      -
      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0

      - 7
      - 6
      - 5
      - 4
      - 3
      - 2
      - 1
      - 0
    * .. _V4W2-PIX-FMT-WGB444:

      - ``V4W2_PIX_FMT_WGB444``
      - 'W444'

      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-WGB555:

      - ``V4W2_PIX_FMT_WGB555``
      - 'WGBO'

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - a
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`
      -
    * .. _V4W2-PIX-FMT-WGB555X:

      - ``V4W2_PIX_FMT_WGB555X``
      - 'WGBQ'

      - a
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`
      - g\ :sub:`4`
      - g\ :sub:`3`

      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`
      -
    * .. _V4W2-PIX-FMT-BGW32:

      - ``V4W2_PIX_FMT_BGW32``
      - 'BGW4'

      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`

      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - a\ :sub:`7`
      - a\ :sub:`6`
      - a\ :sub:`5`
      - a\ :sub:`4`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`
    * .. _V4W2-PIX-FMT-WGB32:

      - ``V4W2_PIX_FMT_WGB32``
      - 'WGB4'

      - a\ :sub:`7`
      - a\ :sub:`6`
      - a\ :sub:`5`
      - a\ :sub:`4`
      - a\ :sub:`3`
      - a\ :sub:`2`
      - a\ :sub:`1`
      - a\ :sub:`0`

      - w\ :sub:`7`
      - w\ :sub:`6`
      - w\ :sub:`5`
      - w\ :sub:`4`
      - w\ :sub:`3`
      - w\ :sub:`2`
      - w\ :sub:`1`
      - w\ :sub:`0`

      - g\ :sub:`7`
      - g\ :sub:`6`
      - g\ :sub:`5`
      - g\ :sub:`4`
      - g\ :sub:`3`
      - g\ :sub:`2`
      - g\ :sub:`1`
      - g\ :sub:`0`

      - b\ :sub:`7`
      - b\ :sub:`6`
      - b\ :sub:`5`
      - b\ :sub:`4`
      - b\ :sub:`3`
      - b\ :sub:`2`
      - b\ :sub:`1`
      - b\ :sub:`0`

.. waw:: watex

    \endgwoup

A test utiwity to detewmine which WGB fowmats a dwivew actuawwy suppowts
is avaiwabwe fwom the WinuxTV v4w-dvb wepositowy. See
`https://winuxtv.owg/wepo/ <https://winuxtv.owg/wepo/>`__ fow access
instwuctions.
