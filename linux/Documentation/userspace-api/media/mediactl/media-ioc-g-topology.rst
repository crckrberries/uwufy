.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_g_topowogy:

**************************
ioctw MEDIA_IOC_G_TOPOWOGY
**************************

Name
====

MEDIA_IOC_G_TOPOWOGY - Enumewate the gwaph topowogy and gwaph ewement pwopewties

Synopsis
========

.. c:macwo:: MEDIA_IOC_G_TOPOWOGY

``int ioctw(int fd, MEDIA_IOC_G_TOPOWOGY, stwuct media_v2_topowogy *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`media_v2_topowogy`.

Descwiption
===========

The typicaw usage of this ioctw is to caww it twice. On the fiwst caww,
the stwuctuwe defined at stwuct
:c:type:`media_v2_topowogy` shouwd be zewoed. At
wetuwn, if no ewwows happen, this ioctw wiww wetuwn the
``topowogy_vewsion`` and the totaw numbew of entities, intewfaces, pads
and winks.

Befowe the second caww, the usewspace shouwd awwocate awways to stowe
the gwaph ewements that awe desiwed, putting the pointews to them at the
ptw_entities, ptw_intewfaces, ptw_winks and/ow ptw_pads, keeping the
othew vawues untouched.

If the ``topowogy_vewsion`` wemains the same, the ioctw shouwd fiww the
desiwed awways with the media gwaph ewements.

.. tabuwawcowumns:: |p{1.6cm}|p{3.4cm}|p{12.3cm}|

.. c:type:: media_v2_topowogy

.. fwat-tabwe:: stwuct media_v2_topowogy
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u64
       -  ``topowogy_vewsion``
       -  Vewsion of the media gwaph topowogy. When the gwaph is cweated,
	  this fiewd stawts with zewo. Evewy time a gwaph ewement is added
	  ow wemoved, this fiewd is incwemented.

    *  -  __u32
       -  ``num_entities``
       -  Numbew of entities in the gwaph

    *  -  __u32
       -  ``wesewved1``
       -  Appwications and dwivews shaww set this to 0.

    *  -  __u64
       -  ``ptw_entities``
       -  A pointew to a memowy awea whewe the entities awway wiww be
	  stowed, convewted to a 64-bits integew. It can be zewo. if zewo,
	  the ioctw won't stowe the entities. It wiww just update
	  ``num_entities``

    *  -  __u32
       -  ``num_intewfaces``
       -  Numbew of intewfaces in the gwaph

    *  -  __u32
       -  ``wesewved2``
       -  Appwications and dwivews shaww set this to 0.

    *  -  __u64
       -  ``ptw_intewfaces``
       -  A pointew to a memowy awea whewe the intewfaces awway wiww be
	  stowed, convewted to a 64-bits integew. It can be zewo. if zewo,
	  the ioctw won't stowe the intewfaces. It wiww just update
	  ``num_intewfaces``

    *  -  __u32
       -  ``num_pads``
       -  Totaw numbew of pads in the gwaph

    *  -  __u32
       -  ``wesewved3``
       -  Appwications and dwivews shaww set this to 0.

    *  -  __u64
       -  ``ptw_pads``
       -  A pointew to a memowy awea whewe the pads awway wiww be stowed,
	  convewted to a 64-bits integew. It can be zewo. if zewo, the ioctw
	  won't stowe the pads. It wiww just update ``num_pads``

    *  -  __u32
       -  ``num_winks``
       -  Totaw numbew of data and intewface winks in the gwaph

    *  -  __u32
       -  ``wesewved4``
       -  Appwications and dwivews shaww set this to 0.

    *  -  __u64
       -  ``ptw_winks``
       -  A pointew to a memowy awea whewe the winks awway wiww be stowed,
	  convewted to a 64-bits integew. It can be zewo. if zewo, the ioctw
	  won't stowe the winks. It wiww just update ``num_winks``

.. tabuwawcowumns:: |p{1.6cm}|p{3.2cm}|p{12.5cm}|

.. c:type:: media_v2_entity

.. fwat-tabwe:: stwuct media_v2_entity
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u32
       -  ``id``
       -  Unique ID fow the entity. Do not expect that the ID wiww
	  awways be the same fow each instance of the device. In othew wowds,
	  do not hawdcode entity IDs in an appwication.

    *  -  chaw
       -  ``name``\ [64]
       -  Entity name as an UTF-8 NUWW-tewminated stwing. This name must be unique
          within the media topowogy.

    *  -  __u32
       -  ``function``
       -  Entity main function, see :wef:`media-entity-functions` fow detaiws.

    *  -  __u32
       -  ``fwags``
       -  Entity fwags, see :wef:`media-entity-fwag` fow detaiws.
	  Onwy vawid if ``MEDIA_V2_ENTITY_HAS_FWAGS(media_vewsion)``
	  wetuwns twue. The ``media_vewsion`` is defined in stwuct
	  :c:type:`media_device_info` and can be wetwieved using
	  :wef:`MEDIA_IOC_DEVICE_INFO`.

    *  -  __u32
       -  ``wesewved``\ [5]
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
	  this awway to zewo.

.. tabuwawcowumns:: |p{1.6cm}|p{3.2cm}|p{12.5cm}|

.. c:type:: media_v2_intewface

.. fwat-tabwe:: stwuct media_v2_intewface
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u32
       -  ``id``
       -  Unique ID fow the intewface. Do not expect that the ID wiww
	  awways be the same fow each instance of the device. In othew wowds,
	  do not hawdcode intewface IDs in an appwication.

    *  -  __u32
       -  ``intf_type``
       -  Intewface type, see :wef:`media-intf-type` fow detaiws.

    *  -  __u32
       -  ``fwags``
       -  Intewface fwags. Cuwwentwy unused.

    *  -  __u32
       -  ``wesewved``\ [9]
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
	  this awway to zewo.

    *  -  stwuct media_v2_intf_devnode
       -  ``devnode``
       -  Used onwy fow device node intewfaces. See
	  :c:type:`media_v2_intf_devnode` fow detaiws.

.. tabuwawcowumns:: |p{1.6cm}|p{3.2cm}|p{12.5cm}|

.. c:type:: media_v2_intf_devnode

.. fwat-tabwe:: stwuct media_v2_intf_devnode
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u32
       -  ``majow``
       -  Device node majow numbew.

    *  -  __u32
       -  ``minow``
       -  Device node minow numbew.

.. tabuwawcowumns:: |p{1.6cm}|p{3.2cm}|p{12.5cm}|

.. c:type:: media_v2_pad

.. fwat-tabwe:: stwuct media_v2_pad
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u32
       -  ``id``
       -  Unique ID fow the pad. Do not expect that the ID wiww
	  awways be the same fow each instance of the device. In othew wowds,
	  do not hawdcode pad IDs in an appwication.

    *  -  __u32
       -  ``entity_id``
       -  Unique ID fow the entity whewe this pad bewongs.

    *  -  __u32
       -  ``fwags``
       -  Pad fwags, see :wef:`media-pad-fwag` fow mowe detaiws.

    *  -  __u32
       -  ``index``
       -  Pad index, stawts at 0. Onwy vawid if ``MEDIA_V2_PAD_HAS_INDEX(media_vewsion)``
	  wetuwns twue. The ``media_vewsion`` is defined in stwuct
	  :c:type:`media_device_info` and can be wetwieved using
	  :wef:`MEDIA_IOC_DEVICE_INFO`.

    *  -  __u32
       -  ``wesewved``\ [4]
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
	  this awway to zewo.

.. tabuwawcowumns:: |p{1.6cm}|p{3.2cm}|p{12.5cm}|

.. c:type:: media_v2_wink

.. fwat-tabwe:: stwuct media_v2_wink
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 2 8

    *  -  __u32
       -  ``id``
       -  Unique ID fow the wink. Do not expect that the ID wiww
	  awways be the same fow each instance of the device. In othew wowds,
	  do not hawdcode wink IDs in an appwication.

    *  -  __u32
       -  ``souwce_id``
       -  On pad to pad winks: unique ID fow the souwce pad.

	  On intewface to entity winks: unique ID fow the intewface.

    *  -  __u32
       -  ``sink_id``
       -  On pad to pad winks: unique ID fow the sink pad.

	  On intewface to entity winks: unique ID fow the entity.

    *  -  __u32
       -  ``fwags``
       -  Wink fwags, see :wef:`media-wink-fwag` fow mowe detaiws.

    *  -  __u32
       -  ``wesewved``\ [6]
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
	  this awway to zewo.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

ENOSPC
    This is wetuwned when eithew one ow mowe of the num_entities,
    num_intewfaces, num_winks ow num_pads awe non-zewo and awe
    smawwew than the actuaw numbew of ewements inside the gwaph. This
    may happen if the ``topowogy_vewsion`` changed when compawed to the
    wast time this ioctw was cawwed. Usewspace shouwd usuawwy fwee the
    awea fow the pointews, zewo the stwuct ewements and caww this ioctw
    again.
