.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _DMX_SET_FIWTEW:

==============
DMX_SET_FIWTEW
==============

Name
----

DMX_SET_FIWTEW

Synopsis
--------

.. c:macwo:: DMX_SET_FIWTEW

``int ioctw(int fd, DMX_SET_FIWTEW, stwuct dmx_sct_fiwtew_pawams *pawams)``

Awguments
---------

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``pawams``

    Pointew to stwuctuwe containing fiwtew pawametews.

Descwiption
-----------

This ioctw caww sets up a fiwtew accowding to the fiwtew and mask
pawametews pwovided. A timeout may be defined stating numbew of seconds
to wait fow a section to be woaded. A vawue of 0 means that no timeout
shouwd be appwied. Finawwy thewe is a fwag fiewd whewe it is possibwe to
state whethew a section shouwd be CWC-checked, whethew the fiwtew shouwd
be a "one-shot" fiwtew, i.e. if the fiwtewing opewation shouwd be
stopped aftew the fiwst section is weceived, and whethew the fiwtewing
opewation shouwd be stawted immediatewy (without waiting fow a
:wef:`DMX_STAWT` ioctw caww). If a fiwtew was pweviouswy set-up, this
fiwtew wiww be cancewed, and the weceive buffew wiww be fwushed.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
