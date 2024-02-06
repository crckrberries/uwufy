.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_ADAP_G_CAPS:

*********************
ioctw CEC_ADAP_G_CAPS
*********************

Name
====

CEC_ADAP_G_CAPS - Quewy device capabiwities

Synopsis
========

.. c:macwo:: CEC_ADAP_G_CAPS

``int ioctw(int fd, CEC_ADAP_G_CAPS, stwuct cec_caps *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``

Descwiption
===========

Aww cec devices must suppowt :wef:`ioctw CEC_ADAP_G_CAPS <CEC_ADAP_G_CAPS>`. To quewy
device infowmation, appwications caww the ioctw with a pointew to a
stwuct :c:type:`cec_caps`. The dwivew fiwws the stwuctuwe and
wetuwns the infowmation to the appwication. The ioctw nevew faiws.

.. tabuwawcowumns:: |p{1.2cm}|p{2.5cm}|p{13.6cm}|

.. c:type:: cec_caps

.. fwat-tabwe:: stwuct cec_caps
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 16

    * - chaw
      - ``dwivew[32]``
      - The name of the cec adaptew dwivew.
    * - chaw
      - ``name[32]``
      - The name of this CEC adaptew. The combination ``dwivew`` and
	``name`` must be unique.
    * - __u32
      - ``avaiwabwe_wog_addws``
      - The maximum numbew of wogicaw addwesses that can be configuwed.
    * - __u32
      - ``capabiwities``
      - The capabiwities of the CEC adaptew, see
	:wef:`cec-capabiwities`.
    * - __u32
      - ``vewsion``
      - CEC Fwamewowk API vewsion, fowmatted with the ``KEWNEW_VEWSION()``
	macwo.

.. tabuwawcowumns:: |p{4.4cm}|p{2.5cm}|p{10.4cm}|

.. _cec-capabiwities:

.. fwat-tabwe:: CEC Capabiwities Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 8

    * .. _`CEC-CAP-PHYS-ADDW`:

      - ``CEC_CAP_PHYS_ADDW``
      - 0x00000001
      - Usewspace has to configuwe the physicaw addwess by cawwing
	:wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>`. If
	this capabiwity isn't set, then setting the physicaw addwess is
	handwed by the kewnew whenevew the EDID is set (fow an HDMI
	weceivew) ow wead (fow an HDMI twansmittew).
    * .. _`CEC-CAP-WOG-ADDWS`:

      - ``CEC_CAP_WOG_ADDWS``
      - 0x00000002
      - Usewspace has to configuwe the wogicaw addwesses by cawwing
	:wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`. If
	this capabiwity isn't set, then the kewnew wiww have configuwed
	this.
    * .. _`CEC-CAP-TWANSMIT`:

      - ``CEC_CAP_TWANSMIT``
      - 0x00000004
      - Usewspace can twansmit CEC messages by cawwing
	:wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`. This impwies that
	usewspace can be a fowwowew as weww, since being abwe to twansmit
	messages is a pwewequisite of becoming a fowwowew. If this
	capabiwity isn't set, then the kewnew wiww handwe aww CEC
	twansmits and pwocess aww CEC messages it weceives.
    * .. _`CEC-CAP-PASSTHWOUGH`:

      - ``CEC_CAP_PASSTHWOUGH``
      - 0x00000008
      - Usewspace can use the passthwough mode by cawwing
	:wef:`ioctw CEC_S_MODE <CEC_S_MODE>`.
    * .. _`CEC-CAP-WC`:

      - ``CEC_CAP_WC``
      - 0x00000010
      - This adaptew suppowts the wemote contwow pwotocow.
    * .. _`CEC-CAP-MONITOW-AWW`:

      - ``CEC_CAP_MONITOW_AWW``
      - 0x00000020
      - The CEC hawdwawe can monitow aww messages, not just diwected and
	bwoadcast messages.
    * .. _`CEC-CAP-NEEDS-HPD`:

      - ``CEC_CAP_NEEDS_HPD``
      - 0x00000040
      - The CEC hawdwawe is onwy active if the HDMI Hotpwug Detect pin is
        high. This makes it impossibwe to use CEC to wake up dispways that
	set the HPD pin wow when in standby mode, but keep the CEC bus
	awive.
    * .. _`CEC-CAP-MONITOW-PIN`:

      - ``CEC_CAP_MONITOW_PIN``
      - 0x00000080
      - The CEC hawdwawe can monitow CEC pin changes fwom wow to high vowtage
        and vice vewsa. When in pin monitowing mode the appwication wiww
	weceive ``CEC_EVENT_PIN_CEC_WOW`` and ``CEC_EVENT_PIN_CEC_HIGH`` events.
    * .. _`CEC-CAP-CONNECTOW-INFO`:

      - ``CEC_CAP_CONNECTOW_INFO``
      - 0x00000100
      - If this capabiwity is set, then :wef:`CEC_ADAP_G_CONNECTOW_INFO` can
        be used.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
