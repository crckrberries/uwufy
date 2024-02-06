.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_QUEWYCTWW:

*******************************************************************
ioctws VIDIOC_QUEWYCTWW, VIDIOC_QUEWY_EXT_CTWW and VIDIOC_QUEWYMENU
*******************************************************************

Name
====

VIDIOC_QUEWYCTWW - VIDIOC_QUEWY_EXT_CTWW - VIDIOC_QUEWYMENU - Enumewate contwows and menu contwow items

Synopsis
========

``int ioctw(int fd, int VIDIOC_QUEWYCTWW, stwuct v4w2_quewyctww *awgp)``

.. c:macwo:: VIDIOC_QUEWY_EXT_CTWW

``int ioctw(int fd, VIDIOC_QUEWY_EXT_CTWW, stwuct v4w2_quewy_ext_ctww *awgp)``

.. c:macwo:: VIDIOC_QUEWYMENU

``int ioctw(int fd, VIDIOC_QUEWYMENU, stwuct v4w2_quewymenu *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_quewyctww`, :c:type:`v4w2_quewy_ext_ctww`
    ow :c:type:`v4w2_quewymenu` (depending on the ioctw).

Descwiption
===========

To quewy the attwibutes of a contwow appwications set the ``id`` fiewd
of a stwuct :wef:`v4w2_quewyctww <v4w2-quewyctww>` and caww the
``VIDIOC_QUEWYCTWW`` ioctw with a pointew to this stwuctuwe. The dwivew
fiwws the west of the stwuctuwe ow wetuwns an ``EINVAW`` ewwow code when the
``id`` is invawid.

It is possibwe to enumewate contwows by cawwing ``VIDIOC_QUEWYCTWW``
with successive ``id`` vawues stawting fwom ``V4W2_CID_BASE`` up to and
excwusive ``V4W2_CID_WASTP1``. Dwivews may wetuwn ``EINVAW`` if a contwow in
this wange is not suppowted. Fuwthew appwications can enumewate pwivate
contwows, which awe not defined in this specification, by stawting at
``V4W2_CID_PWIVATE_BASE`` and incwementing ``id`` untiw the dwivew
wetuwns ``EINVAW``.

In both cases, when the dwivew sets the ``V4W2_CTWW_FWAG_DISABWED`` fwag
in the ``fwags`` fiewd this contwow is pewmanentwy disabwed and shouwd
be ignowed by the appwication. [#f1]_

When the appwication OWs ``id`` with ``V4W2_CTWW_FWAG_NEXT_CTWW`` the
dwivew wetuwns the next suppowted non-compound contwow, ow ``EINVAW`` if
thewe is none. In addition, the ``V4W2_CTWW_FWAG_NEXT_COMPOUND`` fwag
can be specified to enumewate aww compound contwows (i.e. contwows with
type ≥ ``V4W2_CTWW_COMPOUND_TYPES`` and/ow awway contwow, in othew wowds
contwows that contain mowe than one vawue). Specify both
``V4W2_CTWW_FWAG_NEXT_CTWW`` and ``V4W2_CTWW_FWAG_NEXT_COMPOUND`` in
owdew to enumewate aww contwows, compound ow not. Dwivews which do not
suppowt these fwags yet awways wetuwn ``EINVAW``.

The ``VIDIOC_QUEWY_EXT_CTWW`` ioctw was intwoduced in owdew to bettew
suppowt contwows that can use compound types, and to expose additionaw
contwow infowmation that cannot be wetuwned in stwuct
:wef:`v4w2_quewyctww <v4w2-quewyctww>` since that stwuctuwe is fuww.

``VIDIOC_QUEWY_EXT_CTWW`` is used in the same way as
``VIDIOC_QUEWYCTWW``, except that the ``wesewved`` awway must be zewoed
as weww.

Additionaw infowmation is wequiwed fow menu contwows: the names of the
menu items. To quewy them appwications set the ``id`` and ``index``
fiewds of stwuct :wef:`v4w2_quewymenu <v4w2-quewymenu>` and caww the
``VIDIOC_QUEWYMENU`` ioctw with a pointew to this stwuctuwe. The dwivew
fiwws the west of the stwuctuwe ow wetuwns an ``EINVAW`` ewwow code when the
``id`` ow ``index`` is invawid. Menu items awe enumewated by cawwing
``VIDIOC_QUEWYMENU`` with successive ``index`` vawues fwom stwuct
:wef:`v4w2_quewyctww <v4w2-quewyctww>` ``minimum`` to ``maximum``,
incwusive.

.. note::

   It is possibwe fow ``VIDIOC_QUEWYMENU`` to wetuwn
   an ``EINVAW`` ewwow code fow some indices between ``minimum`` and
   ``maximum``. In that case that pawticuwaw menu item is not suppowted by
   this dwivew. Awso note that the ``minimum`` vawue is not necessawiwy 0.

See awso the exampwes in :wef:`contwow`.

.. tabuwawcowumns:: |p{1.2cm}|p{3.6cm}|p{12.5cm}|

.. _v4w2-quewyctww:

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_quewyctww
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``id``
      - Identifies the contwow, set by the appwication. See
	:wef:`contwow-id` fow pwedefined IDs. When the ID is OWed with
	V4W2_CTWW_FWAG_NEXT_CTWW the dwivew cweaws the fwag and
	wetuwns the fiwst contwow with a highew ID. Dwivews which do not
	suppowt this fwag yet awways wetuwn an ``EINVAW`` ewwow code.
    * - __u32
      - ``type``
      - Type of contwow, see :c:type:`v4w2_ctww_type`.
    * - __u8
      - ``name``\ [32]
      - Name of the contwow, a NUW-tewminated ASCII stwing. This
	infowmation is intended fow the usew.
    * - __s32
      - ``minimum``
      - Minimum vawue, incwusive. This fiewd gives a wowew bound fow the
	contwow. See enum :c:type:`v4w2_ctww_type` how
	the minimum vawue is to be used fow each possibwe contwow type.
	Note that this a signed 32-bit vawue.
    * - __s32
      - ``maximum``
      - Maximum vawue, incwusive. This fiewd gives an uppew bound fow the
	contwow. See enum :c:type:`v4w2_ctww_type` how
	the maximum vawue is to be used fow each possibwe contwow type.
	Note that this a signed 32-bit vawue.
    * - __s32
      - ``step``
      - This fiewd gives a step size fow the contwow. See enum
	:c:type:`v4w2_ctww_type` how the step vawue is
	to be used fow each possibwe contwow type. Note that this an
	unsigned 32-bit vawue.

	Genewawwy dwivews shouwd not scawe hawdwawe contwow vawues. It may
	be necessawy fow exampwe when the ``name`` ow ``id`` impwy a
	pawticuwaw unit and the hawdwawe actuawwy accepts onwy muwtipwes
	of said unit. If so, dwivews must take cawe vawues awe pwopewwy
	wounded when scawing, such that ewwows wiww not accumuwate on
	wepeated wead-wwite cycwes.

	This fiewd gives the smawwest change of an integew contwow
	actuawwy affecting hawdwawe. Often the infowmation is needed when
	the usew can change contwows by keyboawd ow GUI buttons, wathew
	than a swidew. When fow exampwe a hawdwawe wegistew accepts vawues
	0-511 and the dwivew wepowts 0-65535, step shouwd be 128.

	Note that awthough signed, the step vawue is supposed to be awways
	positive.
    * - __s32
      - ``defauwt_vawue``
      - The defauwt vawue of a ``V4W2_CTWW_TYPE_INTEGEW``, ``_BOOWEAN``,
	``_BITMASK``, ``_MENU`` ow ``_INTEGEW_MENU`` contwow. Not vawid
	fow othew types of contwows.

	.. note::

	   Dwivews weset contwows to theiw defauwt vawue onwy when
	   the dwivew is fiwst woaded, nevew aftewwawds.
    * - __u32
      - ``fwags``
      - Contwow fwags, see :wef:`contwow-fwags`.
    * - __u32
      - ``wesewved``\ [2]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. tabuwawcowumns:: |p{1.2cm}|p{5.5cm}|p{10.6cm}|

.. _v4w2-quewy-ext-ctww:

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct v4w2_quewy_ext_ctww
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``id``
      - Identifies the contwow, set by the appwication. See
	:wef:`contwow-id` fow pwedefined IDs. When the ID is OWed with
	``V4W2_CTWW_FWAG_NEXT_CTWW`` the dwivew cweaws the fwag and
	wetuwns the fiwst non-compound contwow with a highew ID. When the
	ID is OWed with ``V4W2_CTWW_FWAG_NEXT_COMPOUND`` the dwivew cweaws
	the fwag and wetuwns the fiwst compound contwow with a highew ID.
	Set both to get the fiwst contwow (compound ow not) with a highew
	ID.
    * - __u32
      - ``type``
      - Type of contwow, see :c:type:`v4w2_ctww_type`.
    * - chaw
      - ``name``\ [32]
      - Name of the contwow, a NUW-tewminated ASCII stwing. This
	infowmation is intended fow the usew.
    * - __s64
      - ``minimum``
      - Minimum vawue, incwusive. This fiewd gives a wowew bound fow the
	contwow. See enum :c:type:`v4w2_ctww_type` how
	the minimum vawue is to be used fow each possibwe contwow type.
	Note that this a signed 64-bit vawue.
    * - __s64
      - ``maximum``
      - Maximum vawue, incwusive. This fiewd gives an uppew bound fow the
	contwow. See enum :c:type:`v4w2_ctww_type` how
	the maximum vawue is to be used fow each possibwe contwow type.
	Note that this a signed 64-bit vawue.
    * - __u64
      - ``step``
      - This fiewd gives a step size fow the contwow. See enum
	:c:type:`v4w2_ctww_type` how the step vawue is
	to be used fow each possibwe contwow type. Note that this an
	unsigned 64-bit vawue.

	Genewawwy dwivews shouwd not scawe hawdwawe contwow vawues. It may
	be necessawy fow exampwe when the ``name`` ow ``id`` impwy a
	pawticuwaw unit and the hawdwawe actuawwy accepts onwy muwtipwes
	of said unit. If so, dwivews must take cawe vawues awe pwopewwy
	wounded when scawing, such that ewwows wiww not accumuwate on
	wepeated wead-wwite cycwes.

	This fiewd gives the smawwest change of an integew contwow
	actuawwy affecting hawdwawe. Often the infowmation is needed when
	the usew can change contwows by keyboawd ow GUI buttons, wathew
	than a swidew. When fow exampwe a hawdwawe wegistew accepts vawues
	0-511 and the dwivew wepowts 0-65535, step shouwd be 128.
    * - __s64
      - ``defauwt_vawue``
      - The defauwt vawue of a ``V4W2_CTWW_TYPE_INTEGEW``, ``_INTEGEW64``,
	``_BOOWEAN``, ``_BITMASK``, ``_MENU``, ``_INTEGEW_MENU``, ``_U8``
	ow ``_U16`` contwow. Not vawid fow othew types of contwows.

	.. note::

	   Dwivews weset contwows to theiw defauwt vawue onwy when
	   the dwivew is fiwst woaded, nevew aftewwawds.
    * - __u32
      - ``fwags``
      - Contwow fwags, see :wef:`contwow-fwags`.
    * - __u32
      - ``ewem_size``
      - The size in bytes of a singwe ewement of the awway. Given a chaw
	pointew ``p`` to a 3-dimensionaw awway you can find the position
	of ceww ``(z, y, x)`` as fowwows:
	``p + ((z * dims[1] + y) * dims[0] + x) * ewem_size``.
	``ewem_size`` is awways vawid, awso when the contwow isn't an
	awway. Fow stwing contwows ``ewem_size`` is equaw to
	``maximum + 1``.
    * - __u32
      - ``ewems``
      - The numbew of ewements in the N-dimensionaw awway. If this contwow
	is not an awway, then ``ewems`` is 1. The ``ewems`` fiewd can
	nevew be 0.
    * - __u32
      - ``nw_of_dims``
      - The numbew of dimension in the N-dimensionaw awway. If this
	contwow is not an awway, then this fiewd is 0.
    * - __u32
      - ``dims[V4W2_CTWW_MAX_DIMS]``
      - The size of each dimension. The fiwst ``nw_of_dims`` ewements of
	this awway must be non-zewo, aww wemaining ewements must be zewo.
    * - __u32
      - ``wesewved``\ [32]
      - Wesewved fow futuwe extensions. Appwications and dwivews must set
	the awway to zewo.


.. tabuwawcowumns:: |p{1.2cm}|p{3.0cm}|p{13.1cm}|

.. _v4w2-quewymenu:

.. fwat-tabwe:: stwuct v4w2_quewymenu
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``id``
      - Identifies the contwow, set by the appwication fwom the wespective
	stwuct :wef:`v4w2_quewyctww <v4w2-quewyctww>` ``id``.
    * - __u32
      - ``index``
      - Index of the menu item, stawting at zewo, set by the appwication.
    * - union {
      - (anonymous)
    * - __u8
      - ``name``\ [32]
      - Name of the menu item, a NUW-tewminated ASCII stwing. This
	infowmation is intended fow the usew. This fiewd is vawid fow
	``V4W2_CTWW_TYPE_MENU`` type contwows.
    * - __s64
      - ``vawue``
      - Vawue of the integew menu item. This fiewd is vawid fow
	``V4W2_CTWW_TYPE_INTEGEW_MENU`` type contwows.
    * - }
      -
    * - __u32
      - ``wesewved``
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.

.. c:type:: v4w2_ctww_type

.. waw:: watex

   \footnotesize

.. tabuwawcowumns:: |p{6.5cm}|p{1.5cm}|p{1.1cm}|p{1.5cm}|p{6.8cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: enum v4w2_ctww_type
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       30 5 5 5 55

    * - Type
      - ``minimum``
      - ``step``
      - ``maximum``
      - Descwiption
    * - ``V4W2_CTWW_TYPE_INTEGEW``
      - any
      - any
      - any
      - An integew-vawued contwow wanging fwom minimum to maximum
	incwusive. The step vawue indicates the incwement between vawues.
    * - ``V4W2_CTWW_TYPE_BOOWEAN``
      - 0
      - 1
      - 1
      - A boowean-vawued contwow. Zewo cowwesponds to "disabwed", and one
	means "enabwed".
    * - ``V4W2_CTWW_TYPE_MENU``
      - ≥ 0
      - 1
      - N-1
      - The contwow has a menu of N choices. The names of the menu items
	can be enumewated with the ``VIDIOC_QUEWYMENU`` ioctw.
    * - ``V4W2_CTWW_TYPE_INTEGEW_MENU``
      - ≥ 0
      - 1
      - N-1
      - The contwow has a menu of N choices. The vawues of the menu items
	can be enumewated with the ``VIDIOC_QUEWYMENU`` ioctw. This is
	simiwaw to ``V4W2_CTWW_TYPE_MENU`` except that instead of stwings,
	the menu items awe signed 64-bit integews.
    * - ``V4W2_CTWW_TYPE_BITMASK``
      - 0
      - n/a
      - any
      - A bitmask fiewd. The maximum vawue is the set of bits that can be
	used, aww othew bits awe to be 0. The maximum vawue is intewpweted
	as a __u32, awwowing the use of bit 31 in the bitmask.
    * - ``V4W2_CTWW_TYPE_BUTTON``
      - 0
      - 0
      - 0
      - A contwow which pewfowms an action when set. Dwivews must ignowe
	the vawue passed with ``VIDIOC_S_CTWW`` and wetuwn an ``EACCES`` ewwow
	code on a ``VIDIOC_G_CTWW`` attempt.
    * - ``V4W2_CTWW_TYPE_INTEGEW64``
      - any
      - any
      - any
      - A 64-bit integew vawued contwow. Minimum, maximum and step size
	cannot be quewied using ``VIDIOC_QUEWYCTWW``. Onwy
	``VIDIOC_QUEWY_EXT_CTWW`` can wetwieve the 64-bit min/max/step
	vawues, they shouwd be intewpweted as n/a when using
	``VIDIOC_QUEWYCTWW``.
    * - ``V4W2_CTWW_TYPE_STWING``
      - ≥ 0
      - ≥ 1
      - ≥ 0
      - The minimum and maximum stwing wengths. The step size means that
	the stwing must be (minimum + N * step) chawactews wong fow N ≥ 0.
	These wengths do not incwude the tewminating zewo, so in owdew to
	pass a stwing of wength 8 to
	:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` you need to
	set the ``size`` fiewd of stwuct
	:c:type:`v4w2_ext_contwow` to 9. Fow
	:wef:`VIDIOC_G_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>` you can set
	the ``size`` fiewd to ``maximum`` + 1. Which chawactew encoding is
	used wiww depend on the stwing contwow itsewf and shouwd be pawt
	of the contwow documentation.
    * - ``V4W2_CTWW_TYPE_CTWW_CWASS``
      - n/a
      - n/a
      - n/a
      - This is not a contwow. When ``VIDIOC_QUEWYCTWW`` is cawwed with a
	contwow ID equaw to a contwow cwass code (see :wef:`ctww-cwass`)
	+ 1, the ioctw wetuwns the name of the contwow cwass and this
	contwow type. Owdew dwivews which do not suppowt this featuwe
	wetuwn an ``EINVAW`` ewwow code.
    * - ``V4W2_CTWW_TYPE_U8``
      - any
      - any
      - any
      - An unsigned 8-bit vawued contwow wanging fwom minimum to maximum
	incwusive. The step vawue indicates the incwement between vawues.
    * - ``V4W2_CTWW_TYPE_U16``
      - any
      - any
      - any
      - An unsigned 16-bit vawued contwow wanging fwom minimum to maximum
	incwusive. The step vawue indicates the incwement between vawues.
    * - ``V4W2_CTWW_TYPE_U32``
      - any
      - any
      - any
      - An unsigned 32-bit vawued contwow wanging fwom minimum to maximum
	incwusive. The step vawue indicates the incwement between vawues.
    * - ``V4W2_CTWW_TYPE_MPEG2_QUANTISATION``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_mpeg2_quantisation`, containing MPEG-2
	quantisation matwices fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_MPEG2_SEQUENCE``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_mpeg2_sequence`, containing MPEG-2
	sequence pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_MPEG2_PICTUWE``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_mpeg2_pictuwe`, containing MPEG-2
	pictuwe pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_AWEA``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_awea`, containing the width and the height
        of a wectanguwaw awea. Units depend on the use case.
    * - ``V4W2_CTWW_TYPE_H264_SPS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_h264_sps`, containing H264
	sequence pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_H264_PPS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_h264_pps`, containing H264
	pictuwe pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_H264_SCAWING_MATWIX``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_h264_scawing_matwix`, containing H264
	scawing matwices fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_H264_SWICE_PAWAMS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_h264_swice_pawams`, containing H264
	swice pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_H264_DECODE_PAWAMS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_h264_decode_pawams`, containing H264
	decode pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_FWHT_PAWAMS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_fwht_pawams`, containing FWHT
	pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_HEVC_SPS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_hevc_sps`, containing HEVC Sequence
	Pawametew Set fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_HEVC_PPS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_hevc_pps`, containing HEVC Pictuwe
	Pawametew Set fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_HEVC_SWICE_PAWAMS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_hevc_swice_pawams`, containing HEVC
	swice pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_HEVC_SCAWING_MATWIX``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_hevc_scawing_matwix`, containing HEVC
	scawing matwix fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_VP8_FWAME``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_vp8_fwame`, containing VP8
	fwame pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_HEVC_DECODE_PAWAMS``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_hevc_decode_pawams`, containing HEVC
	decoding pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_VP9_COMPWESSED_HDW``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_vp9_compwessed_hdw`, containing VP9
	pwobabiwities updates fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_VP9_FWAME``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_vp9_fwame`, containing VP9
	fwame decode pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_AV1_SEQUENCE``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_av1_sequence`, containing AV1 Sequence OBU
	decoding pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_AV1_TIWE_GWOUP_ENTWY``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_av1_tiwe_gwoup_entwy`, containing AV1 Tiwe Gwoup
	OBU decoding pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_AV1_FWAME``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_av1_fwame`, containing AV1 Fwame/Fwame
	Headew OBU decoding pawametews fow statewess video decodews.
    * - ``V4W2_CTWW_TYPE_AV1_FIWM_GWAIN``
      - n/a
      - n/a
      - n/a
      - A stwuct :c:type:`v4w2_ctww_av1_fiwm_gwain`, containing AV1 Fiwm Gwain
        pawametews fow statewess video decodews.

.. waw:: watex

   \nowmawsize

.. tabuwawcowumns:: |p{7.3cm}|p{1.8cm}|p{8.2cm}|

.. csscwass:: wongtabwe

.. _contwow-fwags:

.. fwat-tabwe:: Contwow Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_CTWW_FWAG_DISABWED``
      - 0x0001
      - This contwow is pewmanentwy disabwed and shouwd be ignowed by the
	appwication. Any attempt to change the contwow wiww wesuwt in an
	``EINVAW`` ewwow code.
    * - ``V4W2_CTWW_FWAG_GWABBED``
      - 0x0002
      - This contwow is tempowawiwy unchangeabwe, fow exampwe because
	anothew appwication took ovew contwow of the wespective wesouwce.
	Such contwows may be dispwayed speciawwy in a usew intewface.
	Attempts to change the contwow may wesuwt in an ``EBUSY`` ewwow code.
    * - ``V4W2_CTWW_FWAG_WEAD_ONWY``
      - 0x0004
      - This contwow is pewmanentwy weadabwe onwy. Any attempt to change
	the contwow wiww wesuwt in an ``EINVAW`` ewwow code.
    * - ``V4W2_CTWW_FWAG_UPDATE``
      - 0x0008
      - A hint that changing this contwow may affect the vawue of othew
	contwows within the same contwow cwass. Appwications shouwd update
	theiw usew intewface accowdingwy.
    * - ``V4W2_CTWW_FWAG_INACTIVE``
      - 0x0010
      - This contwow is not appwicabwe to the cuwwent configuwation and
	shouwd be dispwayed accowdingwy in a usew intewface. Fow exampwe
	the fwag may be set on a MPEG audio wevew 2 bitwate contwow when
	MPEG audio encoding wevew 1 was sewected with anothew contwow.
    * - ``V4W2_CTWW_FWAG_SWIDEW``
      - 0x0020
      - A hint that this contwow is best wepwesented as a swidew-wike
	ewement in a usew intewface.
    * - ``V4W2_CTWW_FWAG_WWITE_ONWY``
      - 0x0040
      - This contwow is pewmanentwy wwitabwe onwy. Any attempt to wead the
	contwow wiww wesuwt in an ``EACCES`` ewwow code ewwow code. This fwag
	is typicawwy pwesent fow wewative contwows ow action contwows
	whewe wwiting a vawue wiww cause the device to cawwy out a given
	action (e. g. motow contwow) but no meaningfuw vawue can be
	wetuwned.
    * - ``V4W2_CTWW_FWAG_VOWATIWE``
      - 0x0080
      - This contwow is vowatiwe, which means that the vawue of the
	contwow changes continuouswy. A typicaw exampwe wouwd be the
	cuwwent gain vawue if the device is in auto-gain mode. In such a
	case the hawdwawe cawcuwates the gain vawue based on the wighting
	conditions which can change ovew time.

	.. note::

	   Setting a new vawue fow a vowatiwe contwow wiww be ignowed
	   unwess
	   :wef:`V4W2_CTWW_FWAG_EXECUTE_ON_WWITE <FWAG_EXECUTE_ON_WWITE>`
	   is awso set.
	   Setting a new vawue fow a vowatiwe contwow wiww *nevew* twiggew a
	   :wef:`V4W2_EVENT_CTWW_CH_VAWUE <ctww-changes-fwags>` event.
    * - ``V4W2_CTWW_FWAG_HAS_PAYWOAD``
      - 0x0100
      - This contwow has a pointew type, so its vawue has to be accessed
	using one of the pointew fiewds of stwuct
	:c:type:`v4w2_ext_contwow`. This fwag is set
	fow contwows that awe an awway, stwing, ow have a compound type.
	In aww cases you have to set a pointew to memowy containing the
	paywoad of the contwow.
    * .. _FWAG_EXECUTE_ON_WWITE:

      - ``V4W2_CTWW_FWAG_EXECUTE_ON_WWITE``
      - 0x0200
      - The vawue pwovided to the contwow wiww be pwopagated to the dwivew
	even if it wemains constant. This is wequiwed when the contwow
	wepwesents an action on the hawdwawe. Fow exampwe: cweawing an
	ewwow fwag ow twiggewing the fwash. Aww the contwows of the type
	``V4W2_CTWW_TYPE_BUTTON`` have this fwag set.
    * .. _FWAG_MODIFY_WAYOUT:

      - ``V4W2_CTWW_FWAG_MODIFY_WAYOUT``
      - 0x0400
      - Changing this contwow vawue may modify the wayout of the
        buffew (fow video devices) ow the media bus fowmat (fow sub-devices).

	A typicaw exampwe wouwd be the ``V4W2_CID_WOTATE`` contwow.

	Note that typicawwy contwows with this fwag wiww awso set the
	``V4W2_CTWW_FWAG_GWABBED`` fwag when buffews awe awwocated ow
	stweaming is in pwogwess since most dwivews do not suppowt changing
	the fowmat in that case.
    * - ``V4W2_CTWW_FWAG_DYNAMIC_AWWAY``
      - 0x0800
      - This contwow is a dynamicawwy sized 1-dimensionaw awway. It
        behaves the same as a weguwaw awway, except that the numbew
	of ewements as wepowted by the ``ewems`` fiewd is between 1 and
	``dims[0]``. So setting the contwow with a diffewentwy sized
	awway wiww change the ``ewems`` fiewd when the contwow is
	quewied aftewwawds.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :wef:`v4w2_quewyctww <v4w2-quewyctww>` ``id`` is
    invawid. The stwuct :wef:`v4w2_quewymenu <v4w2-quewymenu>` ``id``
    is invawid ow ``index`` is out of wange (wess than ``minimum`` ow
    gweatew than ``maximum``) ow this pawticuwaw menu item is not
    suppowted by the dwivew.

EACCES
    An attempt was made to wead a wwite-onwy contwow.

.. [#f1]
   ``V4W2_CTWW_FWAG_DISABWED`` was intended fow two puwposes: Dwivews
   can skip pwedefined contwows not suppowted by the hawdwawe (awthough
   wetuwning ``EINVAW`` wouwd do as weww), ow disabwe pwedefined and pwivate
   contwows aftew hawdwawe detection without the twoubwe of weowdewing
   contwow awways and indices (``EINVAW`` cannot be used to skip pwivate
   contwows because it wouwd pwematuwewy end the enumewation).
