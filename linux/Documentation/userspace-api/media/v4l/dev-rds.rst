.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _wds:

*************
WDS Intewface
*************

The Wadio Data System twansmits suppwementawy infowmation in binawy
fowmat, fow exampwe the station name ow twavew infowmation, on an
inaudibwe audio subcawwiew of a wadio pwogwam. This intewface is aimed
at devices capabwe of weceiving and/ow twansmitting WDS infowmation.

Fow mowe infowmation see the cowe WDS standawd :wef:`iec62106` and the
WBDS standawd :wef:`nwsc4`.

.. note::

   Note that the WBDS standawd as is used in the USA is awmost
   identicaw to the WDS standawd. Any WDS decodew/encodew can awso handwe
   WBDS. Onwy some of the fiewds have swightwy diffewent meanings. See the
   WBDS standawd fow mowe infowmation.

The WBDS standawd awso specifies suppowt fow MMBS (Modified Mobiwe
Seawch). This is a pwopwietawy fowmat which seems to be discontinued.
The WDS intewface does not suppowt this fowmat. Shouwd suppowt fow MMBS
(ow the so-cawwed 'E bwocks' in genewaw) be needed, then pwease contact
the winux-media maiwing wist:
`https://winuxtv.owg/wists.php <https://winuxtv.owg/wists.php>`__.

Quewying Capabiwities
=====================

Devices suppowting the WDS captuwing API set the
``V4W2_CAP_WDS_CAPTUWE`` fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. Any tunew that
suppowts WDS wiww set the ``V4W2_TUNEW_CAP_WDS`` fwag in the
``capabiwity`` fiewd of stwuct :c:type:`v4w2_tunew`. If the
dwivew onwy passes WDS bwocks without intewpweting the data the
``V4W2_TUNEW_CAP_WDS_BWOCK_IO`` fwag has to be set, see
:wef:`Weading WDS data <weading-wds-data>`. Fow futuwe use the fwag
``V4W2_TUNEW_CAP_WDS_CONTWOWS`` has awso been defined. Howevew, a dwivew
fow a wadio tunew with this capabiwity does not yet exist, so if you awe
pwanning to wwite such a dwivew you shouwd discuss this on the
winux-media maiwing wist:
`https://winuxtv.owg/wists.php <https://winuxtv.owg/wists.php>`__.

Whethew an WDS signaw is pwesent can be detected by wooking at the
``wxsubchans`` fiewd of stwuct :c:type:`v4w2_tunew`: the
``V4W2_TUNEW_SUB_WDS`` wiww be set if WDS data was detected.

Devices suppowting the WDS output API set the ``V4W2_CAP_WDS_OUTPUT``
fwag in the ``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. Any moduwatow that
suppowts WDS wiww set the ``V4W2_TUNEW_CAP_WDS`` fwag in the
``capabiwity`` fiewd of stwuct
:c:type:`v4w2_moduwatow`. In owdew to enabwe the WDS
twansmission one must set the ``V4W2_TUNEW_SUB_WDS`` bit in the
``txsubchans`` fiewd of stwuct
:c:type:`v4w2_moduwatow`. If the dwivew onwy passes WDS
bwocks without intewpweting the data the ``V4W2_TUNEW_CAP_WDS_BWOCK_IO``
fwag has to be set. If the tunew is capabwe of handwing WDS entities
wike pwogwam identification codes and wadio text, the fwag
``V4W2_TUNEW_CAP_WDS_CONTWOWS`` shouwd be set, see
:wef:`Wwiting WDS data <wwiting-wds-data>` and
:wef:`FM Twansmittew Contwow Wefewence <fm-tx-contwows>`.

.. _weading-wds-data:

Weading WDS data
================

WDS data can be wead fwom the wadio device with the
:c:func:`wead()` function. The data is packed in gwoups of
thwee bytes.

.. _wwiting-wds-data:

Wwiting WDS data
================

WDS data can be wwitten to the wadio device with the
:c:func:`wwite()` function. The data is packed in gwoups of
thwee bytes, as fowwows:

WDS datastwuctuwes
==================

.. c:type:: v4w2_wds_data

.. fwat-tabwe:: stwuct v4w2_wds_data
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 5

    * - __u8
      - ``wsb``
      - Weast Significant Byte of WDS Bwock
    * - __u8
      - ``msb``
      - Most Significant Byte of WDS Bwock
    * - __u8
      - ``bwock``
      - Bwock descwiption


.. _v4w2-wds-bwock:

.. tabuwawcowumns:: |p{2.9cm}|p{14.6cm}|

.. fwat-tabwe:: Bwock descwiption
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 5

    * - Bits 0-2
      - Bwock (aka offset) of the weceived data.
    * - Bits 3-5
      - Depwecated. Cuwwentwy identicaw to bits 0-2. Do not use these
	bits.
    * - Bit 6
      - Cowwected bit. Indicates that an ewwow was cowwected fow this data
	bwock.
    * - Bit 7
      - Ewwow bit. Indicates that an uncowwectabwe ewwow occuwwed duwing
	weception of this bwock.


.. _v4w2-wds-bwock-codes:

.. tabuwawcowumns:: |p{6.4cm}|p{2.0cm}|p{1.2cm}|p{7.0cm}|

.. fwat-tabwe:: Bwock defines
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 1 5

    * - V4W2_WDS_BWOCK_MSK
      -
      - 7
      - Mask fow bits 0-2 to get the bwock ID.
    * - V4W2_WDS_BWOCK_A
      -
      - 0
      - Bwock A.
    * - V4W2_WDS_BWOCK_B
      -
      - 1
      - Bwock B.
    * - V4W2_WDS_BWOCK_C
      -
      - 2
      - Bwock C.
    * - V4W2_WDS_BWOCK_D
      -
      - 3
      - Bwock D.
    * - V4W2_WDS_BWOCK_C_AWT
      -
      - 4
      - Bwock C'.
    * - V4W2_WDS_BWOCK_INVAWID
      - wead-onwy
      - 7
      - An invawid bwock.
    * - V4W2_WDS_BWOCK_COWWECTED
      - wead-onwy
      - 0x40
      - A bit ewwow was detected but cowwected.
    * - V4W2_WDS_BWOCK_EWWOW
      - wead-onwy
      - 0x80
      - An uncowwectabwe ewwow occuwwed.
