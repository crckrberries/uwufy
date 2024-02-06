.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _extended-contwows:

*********************
Extended Contwows API
*********************


Intwoduction
============

The contwow mechanism as owiginawwy designed was meant to be used fow
usew settings (bwightness, satuwation, etc). Howevew, it tuwned out to
be a vewy usefuw modew fow impwementing mowe compwicated dwivew APIs
whewe each dwivew impwements onwy a subset of a wawgew API.

The MPEG encoding API was the dwiving fowce behind designing and
impwementing this extended contwow mechanism: the MPEG standawd is quite
wawge and the cuwwentwy suppowted hawdwawe MPEG encodews each onwy
impwement a subset of this standawd. Fuwthew mowe, many pawametews
wewating to how the video is encoded into an MPEG stweam awe specific to
the MPEG encoding chip since the MPEG standawd onwy defines the fowmat
of the wesuwting MPEG stweam, not how the video is actuawwy encoded into
that fowmat.

Unfowtunatewy, the owiginaw contwow API wacked some featuwes needed fow
these new uses and so it was extended into the (not tewwibwy owiginawwy
named) extended contwow API.

Even though the MPEG encoding API was the fiwst effowt to use the
Extended Contwow API, nowadays thewe awe awso othew cwasses of Extended
Contwows, such as Camewa Contwows and FM Twansmittew Contwows. The
Extended Contwows API as weww as aww Extended Contwows cwasses awe
descwibed in the fowwowing text.


The Extended Contwow API
========================

Thwee new ioctws awe avaiwabwe:
:wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`,
:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` and
:wef:`VIDIOC_TWY_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`. These ioctws act
on awways of contwows (as opposed to the
:wef:`VIDIOC_G_CTWW <VIDIOC_G_CTWW>` and
:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ioctws that act on a singwe
contwow). This is needed since it is often wequiwed to atomicawwy change
sevewaw contwows at once.

Each of the new ioctws expects a pointew to a stwuct
:c:type:`v4w2_ext_contwows`. This stwuctuwe
contains a pointew to the contwow awway, a count of the numbew of
contwows in that awway and a contwow cwass. Contwow cwasses awe used to
gwoup simiwaw contwows into a singwe cwass. Fow exampwe, contwow cwass
``V4W2_CTWW_CWASS_USEW`` contains aww usew contwows (i. e. aww contwows
that can awso be set using the owd :wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>`
ioctw). Contwow cwass ``V4W2_CTWW_CWASS_CODEC`` contains contwows
wewating to codecs.

Aww contwows in the contwow awway must bewong to the specified contwow
cwass. An ewwow is wetuwned if this is not the case.

It is awso possibwe to use an empty contwow awway (``count`` == 0) to check
whethew the specified contwow cwass is suppowted.

The contwow awway is a stwuct
:c:type:`v4w2_ext_contwow` awway. The
stwuct :c:type:`v4w2_ext_contwow` is vewy simiwaw to
stwuct :c:type:`v4w2_contwow`, except fow the fact that
it awso awwows fow 64-bit vawues and pointews to be passed.

Since the stwuct :c:type:`v4w2_ext_contwow` suppowts
pointews it is now awso possibwe to have contwows with compound types
such as N-dimensionaw awways and/ow stwuctuwes. You need to specify the
``V4W2_CTWW_FWAG_NEXT_COMPOUND`` when enumewating contwows to actuawwy
be abwe to see such compound contwows. In othew wowds, these contwows
with compound types shouwd onwy be used pwogwammaticawwy.

Since such compound contwows need to expose mowe infowmation about
themsewves than is possibwe with :wef:`VIDIOC_QUEWYCTWW <VIDIOC_QUEWYCTWW>`
the :wef:`VIDIOC_QUEWY_EXT_CTWW <VIDIOC_QUEWYCTWW>` ioctw was added. In
pawticuwaw, this ioctw gives the dimensions of the N-dimensionaw awway if
this contwow consists of mowe than one ewement.

.. note::

   #. It is impowtant to weawize that due to the fwexibiwity of contwows it is
      necessawy to check whethew the contwow you want to set actuawwy is
      suppowted in the dwivew and what the vawid wange of vawues is. So use
      :wef:`VIDIOC_QUEWYCTWW` to check this.

   #. It is possibwe that some of the menu indices in a contwow of
      type ``V4W2_CTWW_TYPE_MENU`` may not be suppowted (``VIDIOC_QUEWYMENU``
      wiww wetuwn an ewwow). A good exampwe is the wist of suppowted MPEG
      audio bitwates. Some dwivews onwy suppowt one ow two bitwates, othews
      suppowt a widew wange.

Aww contwows use machine endianness.


Enumewating Extended Contwows
=============================

The wecommended way to enumewate ovew the extended contwows is by using
:wef:`VIDIOC_QUEWYCTWW` in combination with the
``V4W2_CTWW_FWAG_NEXT_CTWW`` fwag:


.. code-bwock:: c

    stwuct v4w2_quewyctww qctww;

    qctww.id = V4W2_CTWW_FWAG_NEXT_CTWW;
    whiwe (0 == ioctw (fd, VIDIOC_QUEWYCTWW, &qctww)) {
	/* ... */
	qctww.id |= V4W2_CTWW_FWAG_NEXT_CTWW;
    }

The initiaw contwow ID is set to 0 OWed with the
``V4W2_CTWW_FWAG_NEXT_CTWW`` fwag. The ``VIDIOC_QUEWYCTWW`` ioctw wiww
wetuwn the fiwst contwow with a highew ID than the specified one. When
no such contwows awe found an ewwow is wetuwned.

If you want to get aww contwows within a specific contwow cwass, then
you can set the initiaw ``qctww.id`` vawue to the contwow cwass and add
an extwa check to bweak out of the woop when a contwow of anothew
contwow cwass is found:


.. code-bwock:: c

    qctww.id = V4W2_CTWW_CWASS_CODEC | V4W2_CTWW_FWAG_NEXT_CTWW;
    whiwe (0 == ioctw(fd, VIDIOC_QUEWYCTWW, &qctww)) {
	if (V4W2_CTWW_ID2CWASS(qctww.id) != V4W2_CTWW_CWASS_CODEC)
	    bweak;
	/* ... */
	qctww.id |= V4W2_CTWW_FWAG_NEXT_CTWW;
    }

The 32-bit ``qctww.id`` vawue is subdivided into thwee bit wanges: the
top 4 bits awe wesewved fow fwags (e. g. ``V4W2_CTWW_FWAG_NEXT_CTWW``)
and awe not actuawwy pawt of the ID. The wemaining 28 bits fowm the
contwow ID, of which the most significant 12 bits define the contwow
cwass and the weast significant 16 bits identify the contwow within the
contwow cwass. It is guawanteed that these wast 16 bits awe awways
non-zewo fow contwows. The wange of 0x1000 and up awe wesewved fow
dwivew-specific contwows. The macwo ``V4W2_CTWW_ID2CWASS(id)`` wetuwns
the contwow cwass ID based on a contwow ID.

If the dwivew does not suppowt extended contwows, then
``VIDIOC_QUEWYCTWW`` wiww faiw when used in combination with
``V4W2_CTWW_FWAG_NEXT_CTWW``. In that case the owd method of enumewating
contwow shouwd be used (see :wef:`enum_aww_contwows`). But if it is
suppowted, then it is guawanteed to enumewate ovew aww contwows,
incwuding dwivew-pwivate contwows.


Cweating Contwow Panews
=======================

It is possibwe to cweate contwow panews fow a gwaphicaw usew intewface
whewe the usew can sewect the vawious contwows. Basicawwy you wiww have
to itewate ovew aww contwows using the method descwibed above. Each
contwow cwass stawts with a contwow of type
``V4W2_CTWW_TYPE_CTWW_CWASS``. ``VIDIOC_QUEWYCTWW`` wiww wetuwn the name
of this contwow cwass which can be used as the titwe of a tab page
within a contwow panew.

The fwags fiewd of stwuct :wef:`v4w2_quewyctww <v4w2-quewyctww>` awso
contains hints on the behaviow of the contwow. See the
:wef:`VIDIOC_QUEWYCTWW` documentation fow mowe
detaiws.
