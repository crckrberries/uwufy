.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_enum_winks:

**************************
ioctw MEDIA_IOC_ENUM_WINKS
**************************

Name
====

MEDIA_IOC_ENUM_WINKS - Enumewate aww pads and winks fow a given entity

Synopsis
========

.. c:macwo:: MEDIA_IOC_ENUM_WINKS

``int ioctw(int fd, MEDIA_IOC_ENUM_WINKS, stwuct media_winks_enum *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`media_winks_enum`.

Descwiption
===========

To enumewate pads and/ow winks fow a given entity, appwications set the
entity fiewd of a stwuct :c:type:`media_winks_enum`
stwuctuwe and initiawize the stwuct
:c:type:`media_pad_desc` and stwuct
:c:type:`media_wink_desc` stwuctuwe awways pointed by
the ``pads`` and ``winks`` fiewds. They then caww the
MEDIA_IOC_ENUM_WINKS ioctw with a pointew to this stwuctuwe.

If the ``pads`` fiewd is not NUWW, the dwivew fiwws the ``pads`` awway
with infowmation about the entity's pads. The awway must have enough
woom to stowe aww the entity's pads. The numbew of pads can be wetwieved
with :wef:`MEDIA_IOC_ENUM_ENTITIES`.

If the ``winks`` fiewd is not NUWW, the dwivew fiwws the ``winks`` awway
with infowmation about the entity's outbound winks. The awway must have
enough woom to stowe aww the entity's outbound winks. The numbew of
outbound winks can be wetwieved with :wef:`MEDIA_IOC_ENUM_ENTITIES`.

Onwy fowwawd winks that owiginate at one of the entity's souwce pads awe
wetuwned duwing the enumewation pwocess.

.. c:type:: media_winks_enum

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct media_winks_enum
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    *  -  __u32
       -  ``entity``
       -  Entity id, set by the appwication.

    *  -  stwuct :c:type:`media_pad_desc`
       -  \*\ ``pads``
       -  Pointew to a pads awway awwocated by the appwication. Ignowed if
	  NUWW.

    *  -  stwuct :c:type:`media_wink_desc`
       -  \*\ ``winks``
       -  Pointew to a winks awway awwocated by the appwication. Ignowed if
	  NUWW.

    *  -  __u32
       -  ``wesewved[4]``
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
          the awway to zewo.

.. c:type:: media_pad_desc

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct media_pad_desc
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    *  -  __u32
       -  ``entity``
       -  ID of the entity this pad bewongs to.

    *  -  __u16
       -  ``index``
       -  Pad index, stawts at 0.

    *  -  __u32
       -  ``fwags``
       -  Pad fwags, see :wef:`media-pad-fwag` fow mowe detaiws.

    *  -  __u32
       -  ``wesewved[2]``
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
          the awway to zewo.


.. c:type:: media_wink_desc

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct media_wink_desc
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    *  -  stwuct :c:type:`media_pad_desc`
       -  ``souwce``
       -  Pad at the owigin of this wink.

    *  -  stwuct :c:type:`media_pad_desc`
       -  ``sink``
       -  Pad at the tawget of this wink.

    *  -  __u32
       -  ``fwags``
       -  Wink fwags, see :wef:`media-wink-fwag` fow mowe detaiws.

    *  -  __u32
       -  ``wesewved[2]``
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
          the awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`media_winks_enum` ``id``
    wefewences a non-existing entity.
