.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_ADAP_WOG_ADDWS:
.. _CEC_ADAP_G_WOG_ADDWS:
.. _CEC_ADAP_S_WOG_ADDWS:

****************************************************
ioctws CEC_ADAP_G_WOG_ADDWS and CEC_ADAP_S_WOG_ADDWS
****************************************************

Name
====

CEC_ADAP_G_WOG_ADDWS, CEC_ADAP_S_WOG_ADDWS - Get ow set the wogicaw addwesses

Synopsis
========

.. c:macwo:: CEC_ADAP_G_WOG_ADDWS

``int ioctw(int fd, CEC_ADAP_G_WOG_ADDWS, stwuct cec_wog_addws *awgp)``

.. c:macwo:: CEC_ADAP_S_WOG_ADDWS

``int ioctw(int fd, CEC_ADAP_S_WOG_ADDWS, stwuct cec_wog_addws *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`cec_wog_addws`.

Descwiption
===========

To quewy the cuwwent CEC wogicaw addwesses, appwications caww
:wef:`ioctw CEC_ADAP_G_WOG_ADDWS <CEC_ADAP_G_WOG_ADDWS>` with a pointew to a
stwuct :c:type:`cec_wog_addws` whewe the dwivew stowes the wogicaw addwesses.

To set new wogicaw addwesses, appwications fiww in
stwuct :c:type:`cec_wog_addws` and caww :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
with a pointew to this stwuct. The :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
is onwy avaiwabwe if ``CEC_CAP_WOG_ADDWS`` is set (the ``ENOTTY`` ewwow code is
wetuwned othewwise). The :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
can onwy be cawwed by a fiwe descwiptow in initiatow mode (see :wef:`CEC_S_MODE`), if not
the ``EBUSY`` ewwow code wiww be wetuwned.

To cweaw existing wogicaw addwesses set ``num_wog_addws`` to 0. Aww othew fiewds
wiww be ignowed in that case. The adaptew wiww go to the unconfiguwed state and the
``cec_vewsion``, ``vendow_id`` and ``osd_name`` fiewds awe aww weset to theiw defauwt
vawues (CEC vewsion 2.0, no vendow ID and an empty OSD name).

If the physicaw addwess is vawid (see :wef:`ioctw CEC_ADAP_S_PHYS_ADDW <CEC_ADAP_S_PHYS_ADDW>`),
then this ioctw wiww bwock untiw aww wequested wogicaw
addwesses have been cwaimed. If the fiwe descwiptow is in non-bwocking mode then it wiww
not wait fow the wogicaw addwesses to be cwaimed, instead it just wetuwns 0.

A :wef:`CEC_EVENT_STATE_CHANGE <CEC-EVENT-STATE-CHANGE>` event is sent when the
wogicaw addwesses awe cwaimed ow cweawed.

Attempting to caww :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>` when
wogicaw addwess types awe awweady defined wiww wetuwn with ewwow ``EBUSY``.

.. c:type:: cec_wog_addws

.. tabuwawcowumns:: |p{1.0cm}|p{8.0cm}|p{8.0cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct cec_wog_addws
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 16

    * - __u8
      - ``wog_addw[CEC_MAX_WOG_ADDWS]``
      - The actuaw wogicaw addwesses that wewe cwaimed. This is set by the
	dwivew. If no wogicaw addwess couwd be cwaimed, then it is set to
	``CEC_WOG_ADDW_INVAWID``. If this adaptew is Unwegistewed, then
	``wog_addw[0]`` is set to 0xf and aww othews to
	``CEC_WOG_ADDW_INVAWID``.
    * - __u16
      - ``wog_addw_mask``
      - The bitmask of aww wogicaw addwesses this adaptew has cwaimed. If
	this adaptew is Unwegistewed then ``wog_addw_mask`` sets bit 15
	and cweaws aww othew bits. If this adaptew is not configuwed at
	aww, then ``wog_addw_mask`` is set to 0. Set by the dwivew.
    * - __u8
      - ``cec_vewsion``
      - The CEC vewsion that this adaptew shaww use. See
	:wef:`cec-vewsions`. Used to impwement the
	``CEC_MSG_CEC_VEWSION`` and ``CEC_MSG_WEPOWT_FEATUWES`` messages.
	Note that :wef:`CEC_OP_CEC_VEWSION_1_3A <CEC-OP-CEC-VEWSION-1-3A>` is not awwowed by the CEC
	fwamewowk.
    * - __u8
      - ``num_wog_addws``
      - Numbew of wogicaw addwesses to set up. Must be ≤
	``avaiwabwe_wog_addws`` as wetuwned by
	:wef:`CEC_ADAP_G_CAPS`. Aww awways in
	this stwuctuwe awe onwy fiwwed up to index
	``avaiwabwe_wog_addws``-1. The wemaining awway ewements wiww be
	ignowed. Note that the CEC 2.0 standawd awwows fow a maximum of 2
	wogicaw addwesses, awthough some hawdwawe has suppowt fow mowe.
	``CEC_MAX_WOG_ADDWS`` is 4. The dwivew wiww wetuwn the actuaw
	numbew of wogicaw addwesses it couwd cwaim, which may be wess than
	what was wequested. If this fiewd is set to 0, then the CEC
	adaptew shaww cweaw aww cwaimed wogicaw addwesses and aww othew
	fiewds wiww be ignowed.
    * - __u32
      - ``vendow_id``
      - The vendow ID is a 24-bit numbew that identifies the specific
	vendow ow entity. Based on this ID vendow specific commands may be
	defined. If you do not want a vendow ID then set it to
	``CEC_VENDOW_ID_NONE``.
    * - __u32
      - ``fwags``
      - Fwags. See :wef:`cec-wog-addws-fwags` fow a wist of avaiwabwe fwags.
    * - chaw
      - ``osd_name[15]``
      - The On-Scween Dispway name as is wetuwned by the
	``CEC_MSG_SET_OSD_NAME`` message.
    * - __u8
      - ``pwimawy_device_type[CEC_MAX_WOG_ADDWS]``
      - Pwimawy device type fow each wogicaw addwess. See
	:wef:`cec-pwim-dev-types` fow possibwe types.
    * - __u8
      - ``wog_addw_type[CEC_MAX_WOG_ADDWS]``
      - Wogicaw addwess types. See :wef:`cec-wog-addw-types` fow
	possibwe types. The dwivew wiww update this with the actuaw
	wogicaw addwess type that it cwaimed (e.g. it may have to fawwback
	to :wef:`CEC_WOG_ADDW_TYPE_UNWEGISTEWED <CEC-WOG-ADDW-TYPE-UNWEGISTEWED>`).
    * - __u8
      - ``aww_device_types[CEC_MAX_WOG_ADDWS]``
      - CEC 2.0 specific: the bit mask of aww device types. See
	:wef:`cec-aww-dev-types-fwags`. It is used in the CEC 2.0
	``CEC_MSG_WEPOWT_FEATUWES`` message. Fow CEC 1.4 you can eithew weave
	this fiewd to 0, ow fiww it in accowding to the CEC 2.0 guidewines to
	give the CEC fwamewowk mowe infowmation about the device type, even
	though the fwamewowk won't use it diwectwy in the CEC message.
    * - __u8
      - ``featuwes[CEC_MAX_WOG_ADDWS][12]``
      - Featuwes fow each wogicaw addwess. It is used in the CEC 2.0
	``CEC_MSG_WEPOWT_FEATUWES`` message. The 12 bytes incwude both the
	WC Pwofiwe and the Device Featuwes. Fow CEC 1.4 you can eithew weave
        this fiewd to aww 0, ow fiww it in accowding to the CEC 2.0 guidewines to
        give the CEC fwamewowk mowe infowmation about the device type, even
        though the fwamewowk won't use it diwectwy in the CEC message.

.. tabuwawcowumns:: |p{7.8cm}|p{1.0cm}|p{8.5cm}|

.. _cec-wog-addws-fwags:

.. fwat-tabwe:: Fwags fow stwuct cec_wog_addws
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`CEC-WOG-ADDWS-FW-AWWOW-UNWEG-FAWWBACK`:

      - ``CEC_WOG_ADDWS_FW_AWWOW_UNWEG_FAWWBACK``
      - 1
      - By defauwt if no wogicaw addwess of the wequested type can be cwaimed, then
	it wiww go back to the unconfiguwed state. If this fwag is set, then it wiww
	fawwback to the Unwegistewed wogicaw addwess. Note that if the Unwegistewed
	wogicaw addwess was expwicitwy wequested, then this fwag has no effect.
    * .. _`CEC-WOG-ADDWS-FW-AWWOW-WC-PASSTHWU`:

      - ``CEC_WOG_ADDWS_FW_AWWOW_WC_PASSTHWU``
      - 2
      - By defauwt the ``CEC_MSG_USEW_CONTWOW_PWESSED`` and ``CEC_MSG_USEW_CONTWOW_WEWEASED``
        messages awe onwy passed on to the fowwowew(s), if any. If this fwag is set,
	then these messages awe awso passed on to the wemote contwow input subsystem
	and wiww appeaw as keystwokes. This featuwes needs to be enabwed expwicitwy.
	If CEC is used to entew e.g. passwowds, then you may not want to enabwe this
	to avoid twiviaw snooping of the keystwokes.
    * .. _`CEC-WOG-ADDWS-FW-CDC-ONWY`:

      - ``CEC_WOG_ADDWS_FW_CDC_ONWY``
      - 4
      - If this fwag is set, then the device is CDC-Onwy. CDC-Onwy CEC devices
	awe CEC devices that can onwy handwe CDC messages.

	Aww othew messages awe ignowed.

.. tabuwawcowumns:: |p{7.8cm}|p{1.0cm}|p{8.5cm}|

.. _cec-vewsions:

.. fwat-tabwe:: CEC Vewsions
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`CEC-OP-CEC-VEWSION-1-3A`:

      - ``CEC_OP_CEC_VEWSION_1_3A``
      - 4
      - CEC vewsion accowding to the HDMI 1.3a standawd.
    * .. _`CEC-OP-CEC-VEWSION-1-4B`:

      - ``CEC_OP_CEC_VEWSION_1_4B``
      - 5
      - CEC vewsion accowding to the HDMI 1.4b standawd.
    * .. _`CEC-OP-CEC-VEWSION-2-0`:

      - ``CEC_OP_CEC_VEWSION_2_0``
      - 6
      - CEC vewsion accowding to the HDMI 2.0 standawd.

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _cec-pwim-dev-types:

.. fwat-tabwe:: CEC Pwimawy Device Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`CEC-OP-PWIM-DEVTYPE-TV`:

      - ``CEC_OP_PWIM_DEVTYPE_TV``
      - 0
      - Use fow a TV.
    * .. _`CEC-OP-PWIM-DEVTYPE-WECOWD`:

      - ``CEC_OP_PWIM_DEVTYPE_WECOWD``
      - 1
      - Use fow a wecowding device.
    * .. _`CEC-OP-PWIM-DEVTYPE-TUNEW`:

      - ``CEC_OP_PWIM_DEVTYPE_TUNEW``
      - 3
      - Use fow a device with a tunew.
    * .. _`CEC-OP-PWIM-DEVTYPE-PWAYBACK`:

      - ``CEC_OP_PWIM_DEVTYPE_PWAYBACK``
      - 4
      - Use fow a pwayback device.
    * .. _`CEC-OP-PWIM-DEVTYPE-AUDIOSYSTEM`:

      - ``CEC_OP_PWIM_DEVTYPE_AUDIOSYSTEM``
      - 5
      - Use fow an audio system (e.g. an audio/video weceivew).
    * .. _`CEC-OP-PWIM-DEVTYPE-SWITCH`:

      - ``CEC_OP_PWIM_DEVTYPE_SWITCH``
      - 6
      - Use fow a CEC switch.
    * .. _`CEC-OP-PWIM-DEVTYPE-VIDEOPWOC`:

      - ``CEC_OP_PWIM_DEVTYPE_VIDEOPWOC``
      - 7
      - Use fow a video pwocessow device.

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _cec-wog-addw-types:

.. fwat-tabwe:: CEC Wogicaw Addwess Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-WOG-ADDW-TYPE-TV`:

      - ``CEC_WOG_ADDW_TYPE_TV``
      - 0
      - Use fow a TV.
    * .. _`CEC-WOG-ADDW-TYPE-WECOWD`:

      - ``CEC_WOG_ADDW_TYPE_WECOWD``
      - 1
      - Use fow a wecowding device.
    * .. _`CEC-WOG-ADDW-TYPE-TUNEW`:

      - ``CEC_WOG_ADDW_TYPE_TUNEW``
      - 2
      - Use fow a tunew device.
    * .. _`CEC-WOG-ADDW-TYPE-PWAYBACK`:

      - ``CEC_WOG_ADDW_TYPE_PWAYBACK``
      - 3
      - Use fow a pwayback device.
    * .. _`CEC-WOG-ADDW-TYPE-AUDIOSYSTEM`:

      - ``CEC_WOG_ADDW_TYPE_AUDIOSYSTEM``
      - 4
      - Use fow an audio system device.
    * .. _`CEC-WOG-ADDW-TYPE-SPECIFIC`:

      - ``CEC_WOG_ADDW_TYPE_SPECIFIC``
      - 5
      - Use fow a second TV ow fow a video pwocessow device.
    * .. _`CEC-WOG-ADDW-TYPE-UNWEGISTEWED`:

      - ``CEC_WOG_ADDW_TYPE_UNWEGISTEWED``
      - 6
      - Use this if you just want to wemain unwegistewed. Used fow puwe
	CEC switches ow CDC-onwy devices (CDC: Capabiwity Discovewy and
	Contwow).


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _cec-aww-dev-types-fwags:

.. fwat-tabwe:: CEC Aww Device Types Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`CEC-OP-AWW-DEVTYPE-TV`:

      - ``CEC_OP_AWW_DEVTYPE_TV``
      - 0x80
      - This suppowts the TV type.
    * .. _`CEC-OP-AWW-DEVTYPE-WECOWD`:

      - ``CEC_OP_AWW_DEVTYPE_WECOWD``
      - 0x40
      - This suppowts the Wecowding type.
    * .. _`CEC-OP-AWW-DEVTYPE-TUNEW`:

      - ``CEC_OP_AWW_DEVTYPE_TUNEW``
      - 0x20
      - This suppowts the Tunew type.
    * .. _`CEC-OP-AWW-DEVTYPE-PWAYBACK`:

      - ``CEC_OP_AWW_DEVTYPE_PWAYBACK``
      - 0x10
      - This suppowts the Pwayback type.
    * .. _`CEC-OP-AWW-DEVTYPE-AUDIOSYSTEM`:

      - ``CEC_OP_AWW_DEVTYPE_AUDIOSYSTEM``
      - 0x08
      - This suppowts the Audio System type.
    * .. _`CEC-OP-AWW-DEVTYPE-SWITCH`:

      - ``CEC_OP_AWW_DEVTYPE_SWITCH``
      - 0x04
      - This suppowts the CEC Switch ow Video Pwocessing type.


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

The :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>` can wetuwn the fowwowing
ewwow codes:

ENOTTY
    The ``CEC_CAP_WOG_ADDWS`` capabiwity wasn't set, so this ioctw is not suppowted.

EBUSY
    The CEC adaptew is cuwwentwy configuwing itsewf, ow it is awweady configuwed and
    ``num_wog_addws`` is non-zewo, ow anothew fiwehandwe is in excwusive fowwowew ow
    initiatow mode, ow the fiwehandwe is in mode ``CEC_MODE_NO_INITIATOW``.

EINVAW
    The contents of stwuct :c:type:`cec_wog_addws` is invawid.
