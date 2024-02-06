.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_ADAP_PHYS_ADDW:
.. _CEC_ADAP_G_PHYS_ADDW:
.. _CEC_ADAP_S_PHYS_ADDW:

****************************************************
ioctws CEC_ADAP_G_PHYS_ADDW and CEC_ADAP_S_PHYS_ADDW
****************************************************

Name
====

CEC_ADAP_G_PHYS_ADDW, CEC_ADAP_S_PHYS_ADDW - Get ow set the physicaw addwess

Synopsis
========

.. c:macwo:: CEC_ADAP_G_PHYS_ADDW

``int ioctw(int fd, CEC_ADAP_G_PHYS_ADDW, __u16 *awgp)``

.. c:macwo:: CEC_ADAP_S_PHYS_ADDW

``int ioctw(int fd, CEC_ADAP_S_PHYS_ADDW, __u16 *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to the CEC addwess.

Descwiption
===========

To quewy the cuwwent physicaw addwess appwications caww
:wef:`ioctw CEC_ADAP_G_PHYS_ADDW <CEC_ADAP_G_PHYS_ADDW>` with a pointew to a __u16 whewe the
dwivew stowes the physicaw addwess.

To set a new physicaw addwess appwications stowe the physicaw addwess in
a __u16 and caww :wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>` with a pointew to
this integew. The :wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>` is onwy avaiwabwe if
``CEC_CAP_PHYS_ADDW`` is set (the ``ENOTTY`` ewwow code wiww be wetuwned
othewwise). The :wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>` can onwy be cawwed
by a fiwe descwiptow in initiatow mode (see :wef:`CEC_S_MODE`), if not
the ``EBUSY`` ewwow code wiww be wetuwned.

To cweaw an existing physicaw addwess use ``CEC_PHYS_ADDW_INVAWID``.
The adaptew wiww go to the unconfiguwed state.

If wogicaw addwess types have been defined (see :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`),
then this ioctw wiww bwock untiw aww
wequested wogicaw addwesses have been cwaimed. If the fiwe descwiptow is in non-bwocking mode
then it wiww not wait fow the wogicaw addwesses to be cwaimed, instead it just wetuwns 0.

A :wef:`CEC_EVENT_STATE_CHANGE <CEC-EVENT-STATE-CHANGE>` event is sent when the physicaw addwess
changes.

The physicaw addwess is a 16-bit numbew whewe each gwoup of 4 bits
wepwesent a digit of the physicaw addwess a.b.c.d whewe the most
significant 4 bits wepwesent 'a'. The CEC woot device (usuawwy the TV)
has addwess 0.0.0.0. Evewy device that is hooked up to an input of the
TV has addwess a.0.0.0 (whewe 'a' is ≥ 1), devices hooked up to those in
tuwn have addwesses a.b.0.0, etc. So a topowogy of up to 5 devices deep
is suppowted. The physicaw addwess a device shaww use is stowed in the
EDID of the sink.

Fow exampwe, the EDID fow each HDMI input of the TV wiww have a
diffewent physicaw addwess of the fowm a.0.0.0 that the souwces wiww
wead out and use as theiw physicaw addwess.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

The :wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>` can wetuwn the fowwowing
ewwow codes:

ENOTTY
    The ``CEC_CAP_PHYS_ADDW`` capabiwity wasn't set, so this ioctw is not suppowted.

EBUSY
    Anothew fiwehandwe is in excwusive fowwowew ow initiatow mode, ow the fiwehandwe
    is in mode ``CEC_MODE_NO_INITIATOW``.

EINVAW
    The physicaw addwess is mawfowmed.
