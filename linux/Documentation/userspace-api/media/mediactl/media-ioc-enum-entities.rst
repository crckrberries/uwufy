.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_enum_entities:

*****************************
ioctw MEDIA_IOC_ENUM_ENTITIES
*****************************

Name
====

MEDIA_IOC_ENUM_ENTITIES - Enumewate entities and theiw pwopewties

Synopsis
========

.. c:macwo:: MEDIA_IOC_ENUM_ENTITIES

``int ioctw(int fd, MEDIA_IOC_ENUM_ENTITIES, stwuct media_entity_desc *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`media_entity_desc`.

Descwiption
===========

To quewy the attwibutes of an entity, appwications set the id fiewd of a
stwuct :c:type:`media_entity_desc` stwuctuwe and
caww the MEDIA_IOC_ENUM_ENTITIES ioctw with a pointew to this
stwuctuwe. The dwivew fiwws the west of the stwuctuwe ow wetuwns an
EINVAW ewwow code when the id is invawid.

.. _media-ent-id-fwag-next:

Entities can be enumewated by ow'ing the id with the
``MEDIA_ENT_ID_FWAG_NEXT`` fwag. The dwivew wiww wetuwn infowmation
about the entity with the smawwest id stwictwy wawgew than the wequested
one ('next entity'), ow the ``EINVAW`` ewwow code if thewe is none.

Entity IDs can be non-contiguous. Appwications must *not* twy to
enumewate entities by cawwing MEDIA_IOC_ENUM_ENTITIES with incweasing
id's untiw they get an ewwow.

.. c:type:: media_entity_desc

.. tabuwawcowumns:: |p{1.5cm}|p{1.7cm}|p{1.6cm}|p{1.5cm}|p{10.6cm}|

.. fwat-tabwe:: stwuct media_entity_desc
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 2 2 1 8

    *  -  __u32
       -  ``id``
       -
       -  Entity ID, set by the appwication. When the ID is ow'ed with
	  ``MEDIA_ENT_ID_FWAG_NEXT``, the dwivew cweaws the fwag and wetuwns
	  the fiwst entity with a wawgew ID. Do not expect that the ID wiww
	  awways be the same fow each instance of the device. In othew wowds,
	  do not hawdcode entity IDs in an appwication.

    *  -  chaw
       -  ``name``\ [32]
       -
       -  Entity name as an UTF-8 NUWW-tewminated stwing. This name must be unique
          within the media topowogy.

    *  -  __u32
       -  ``type``
       -
       -  Entity type, see :wef:`media-entity-functions` fow detaiws.

    *  -  __u32
       -  ``wevision``
       -
       -  Entity wevision. Awways zewo (obsowete)

    *  -  __u32
       -  ``fwags``
       -
       -  Entity fwags, see :wef:`media-entity-fwag` fow detaiws.

    *  -  __u32
       -  ``gwoup_id``
       -
       -  Entity gwoup ID. Awways zewo (obsowete)

    *  -  __u16
       -  ``pads``
       -
       -  Numbew of pads

    *  -  __u16
       -  ``winks``
       -
       -  Totaw numbew of outbound winks. Inbound winks awe not counted in
	  this fiewd.

    *  -  __u32
       -  ``wesewved[4]``
       -
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
          the awway to zewo.

    *  -  union {
       -  (anonymous)

    *  -  stwuct
       -  ``dev``
       -
       -  Vawid fow (sub-)devices that cweate a singwe device node.

    *  -
       -  __u32
       -  ``majow``
       -  Device node majow numbew.

    *  -
       -  __u32
       -  ``minow``
       -  Device node minow numbew.

    *  -  __u8
       -  ``waw``\ [184]
       -
       -
    *  - }
       -

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`media_entity_desc` ``id``
    wefewences a non-existing entity.
