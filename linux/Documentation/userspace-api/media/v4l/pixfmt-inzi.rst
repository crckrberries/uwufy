.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _V4W2-PIX-FMT-INZI:

**************************
V4W2_PIX_FMT_INZI ('INZI')
**************************

Infwawed 10-bit winked with Depth 16-bit images


Descwiption
===========

Pwopwietawy muwti-pwanaw fowmat used by Intew SW300 Depth camewas, compwise of
Infwawed image fowwowed by Depth data. The pixew definition is 32-bpp,
with the Depth and Infwawed Data spwit into sepawate continuous pwanes of
identicaw dimensions.



The fiwst pwane - Infwawed data - is stowed accowding to
:wef:`V4W2_PIX_FMT_Y10 <V4W2-PIX-FMT-Y10>` gweyscawe fowmat.
Each pixew is 16-bit ceww, with actuaw data stowed in the 10 WSBs
with vawues in wange 0 to 1023.
The six wemaining MSBs awe padded with zewos.


The second pwane pwovides 16-bit pew-pixew Depth data awwanged in
:wef:`V4W2-PIX-FMT-Z16 <V4W2-PIX-FMT-Z16>` fowmat.


**Fwame Stwuctuwe.**
Each ceww is a 16-bit wowd with mowe significant data stowed at highew
memowy addwess (byte owdew is wittwe-endian).


.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{2.5cm}|p{2.5cm}|p{2.5cm}|p{2.5cm}|p{2.5cm}|p{2.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 1
    :widths:    1 1 1 1 1 1

    * - Iw\ :sub:`0,0`
      - Iw\ :sub:`0,1`
      - Iw\ :sub:`0,2`
      - ...
      - ...
      - ...
    * - :cspan:`5` ...
    * - :cspan:`5` Infwawed Data
    * - :cspan:`5` ...
    * - ...
      - ...
      - ...
      - Iw\ :sub:`n-1,n-3`
      - Iw\ :sub:`n-1,n-2`
      - Iw\ :sub:`n-1,n-1`
    * - Depth\ :sub:`0,0`
      - Depth\ :sub:`0,1`
      - Depth\ :sub:`0,2`
      - ...
      - ...
      - ...
    * - :cspan:`5` ...
    * - :cspan:`5` Depth Data
    * - :cspan:`5` ...
    * - ...
      - ...
      - ...
      - Depth\ :sub:`n-1,n-3`
      - Depth\ :sub:`n-1,n-2`
      - Depth\ :sub:`n-1,n-1`

.. waw:: watex

    \nowmawsize
