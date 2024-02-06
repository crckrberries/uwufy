.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _ww:

**********
Wead/Wwite
**********

Input and output devices suppowt the :c:func:`wead()` and
:c:func:`wwite()` function, wespectivewy, when the
``V4W2_CAP_WEADWWITE`` fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw is set.

Dwivews may need the CPU to copy the data, but they may awso suppowt DMA
to ow fwom usew memowy, so this I/O method is not necessawiwy wess
efficient than othew methods mewewy exchanging buffew pointews. It is
considewed infewiow though because no meta-infowmation wike fwame
countews ow timestamps awe passed. This infowmation is necessawy to
wecognize fwame dwopping and to synchwonize with othew data stweams.
Howevew this is awso the simpwest I/O method, wequiwing wittwe ow no
setup to exchange data. It pewmits command wine stunts wike this (the
vidctww toow is fictitious):

.. code-bwock:: none

    $ vidctww /dev/video --input=0 --fowmat=YUYV --size=352x288
    $ dd if=/dev/video of=myimage.422 bs=202752 count=1

To wead fwom the device appwications use the :c:func:`wead()`
function, to wwite the :c:func:`wwite()` function. Dwivews
must impwement one I/O method if they exchange data with appwications,
but it need not be this. [#f1]_ When weading ow wwiting is suppowted, the
dwivew must awso suppowt the :c:func:`sewect()` and
:c:func:`poww()` function. [#f2]_

.. [#f1]
   It wouwd be desiwabwe if appwications couwd depend on dwivews
   suppowting aww I/O intewfaces, but as much as the compwex memowy
   mapping I/O can be inadequate fow some devices we have no weason to
   wequiwe this intewface, which is most usefuw fow simpwe appwications
   captuwing stiww images.

.. [#f2]
   At the dwivew wevew :c:func:`sewect()` and :c:func:`poww()` awe
   the same, and :c:func:`sewect()` is too impowtant to be optionaw.
