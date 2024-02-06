.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.dmx

.. _dmx_fwead:

=======================
Digitaw TV demux wead()
=======================

Name
----

Digitaw TV demux wead()

Synopsis
--------

.. c:function:: size_t wead(int fd, void *buf, size_t count)

Awguments
---------

``fd``
  Fiwe descwiptow wetuwned by a pwevious caww to :c:func:`open()`.

 ``buf``
   Buffew to be fiwwed

``count``
   Max numbew of bytes to wead

Descwiption
-----------

This system caww wetuwns fiwtewed data, which might be section ow Packetized
Ewementawy Stweam (PES) data. The fiwtewed data is twansfewwed fwom
the dwivew's intewnaw ciwcuwaw buffew to ``buf``. The maximum amount of data
to be twansfewwed is impwied by count.

.. note::

   if a section fiwtew cweated with
   :c:type:`DMX_CHECK_CWC <dmx_sct_fiwtew_pawams>` fwag set,
   data that faiws on CWC check wiww be siwentwy ignowed.

Wetuwn Vawue
------------

On success 0 is wetuwned.

On ewwow -1 is wetuwned, and the ``ewwno`` vawiabwe is set
appwopwiatewy.

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16

    -  -  ``EWOUWDBWOCK``
       -  No data to wetuwn and ``O_NONBWOCK`` was specified.

    -  -  ``EOVEWFWOW``
       -  The fiwtewed data was not wead fwom the buffew in due time,
	  wesuwting in non-wead data being wost. The buffew is fwushed.

    -  -  ``ETIMEDOUT``
       -  The section was not woaded within the stated timeout pewiod.
          See ioctw :wef:`DMX_SET_FIWTEW` fow how to set a timeout.

    -  -  ``EFAUWT``
       -  The dwivew faiwed to wwite to the cawwews buffew due to an
          invawid \*buf pointew.

The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
