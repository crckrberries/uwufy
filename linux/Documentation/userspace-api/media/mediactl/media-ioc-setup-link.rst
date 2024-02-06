.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_setup_wink:

**************************
ioctw MEDIA_IOC_SETUP_WINK
**************************

Name
====

MEDIA_IOC_SETUP_WINK - Modify the pwopewties of a wink

Synopsis
========

.. c:macwo:: MEDIA_IOC_SETUP_WINK

``int ioctw(int fd, MEDIA_IOC_SETUP_WINK, stwuct media_wink_desc *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`media_wink_desc`.

Descwiption
===========

To change wink pwopewties appwications fiww a stwuct
:c:type:`media_wink_desc` with wink identification
infowmation (souwce and sink pad) and the new wequested wink fwags. They
then caww the MEDIA_IOC_SETUP_WINK ioctw with a pointew to that
stwuctuwe.

The onwy configuwabwe pwopewty is the ``ENABWED`` wink fwag to
enabwe/disabwe a wink. Winks mawked with the ``IMMUTABWE`` wink fwag can
not be enabwed ow disabwed.

Wink configuwation has no side effect on othew winks. If an enabwed wink
at the sink pad pwevents the wink fwom being enabwed, the dwivew wetuwns
with an ``EBUSY`` ewwow code.

Onwy winks mawked with the ``DYNAMIC`` wink fwag can be enabwed/disabwed
whiwe stweaming media data. Attempting to enabwe ow disabwe a stweaming
non-dynamic wink wiww wetuwn an ``EBUSY`` ewwow code.

If the specified wink can't be found the dwivew wetuwns with an ``EINVAW``
ewwow code.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

EINVAW
    The stwuct :c:type:`media_wink_desc` wefewences a
    non-existing wink, ow the wink is immutabwe and an attempt to modify
    its configuwation was made.
