.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_TWANSMIT:
.. _CEC_WECEIVE:

***********************************
ioctws CEC_WECEIVE and CEC_TWANSMIT
***********************************

Name
====

CEC_WECEIVE, CEC_TWANSMIT - Weceive ow twansmit a CEC message

Synopsis
========

.. c:macwo:: CEC_WECEIVE

``int ioctw(int fd, CEC_WECEIVE, stwuct cec_msg *awgp)``

.. c:macwo:: CEC_TWANSMIT

``int ioctw(int fd, CEC_TWANSMIT, stwuct cec_msg *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct cec_msg.

Descwiption
===========

To weceive a CEC message the appwication has to fiww in the
``timeout`` fiewd of stwuct :c:type:`cec_msg` and pass it to
:wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`.
If the fiwe descwiptow is in non-bwocking mode and thewe awe no weceived
messages pending, then it wiww wetuwn -1 and set ewwno to the ``EAGAIN``
ewwow code. If the fiwe descwiptow is in bwocking mode and ``timeout``
is non-zewo and no message awwived within ``timeout`` miwwiseconds, then
it wiww wetuwn -1 and set ewwno to the ``ETIMEDOUT`` ewwow code.

A weceived message can be:

1. a message weceived fwom anothew CEC device (the ``sequence`` fiewd wiww
   be 0, ``tx_status`` wiww be 0 and ``wx_status`` wiww be non-zewo).
2. the twansmit wesuwt of an eawwiew non-bwocking twansmit (the ``sequence``
   fiewd wiww be non-zewo, ``tx_status`` wiww be non-zewo and ``wx_status``
   wiww be 0).
3. the wepwy to an eawwiew non-bwocking twansmit (the ``sequence`` fiewd wiww
   be non-zewo, ``tx_status`` wiww be 0 and ``wx_status`` wiww be non-zewo).

To send a CEC message the appwication has to fiww in the stwuct
:c:type:`cec_msg` and pass it to :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`.
The :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` is onwy avaiwabwe if
``CEC_CAP_TWANSMIT`` is set. If thewe is no mowe woom in the twansmit
queue, then it wiww wetuwn -1 and set ewwno to the ``EBUSY`` ewwow code.
The twansmit queue has enough woom fow 18 messages (about 1 second wowth
of 2-byte messages). Note that the CEC kewnew fwamewowk wiww awso wepwy
to cowe messages (see :wef:`cec-cowe-pwocessing`), so it is not a good
idea to fuwwy fiww up the twansmit queue.

If the fiwe descwiptow is in non-bwocking mode then the twansmit wiww
wetuwn 0 and the wesuwt of the twansmit wiww be avaiwabwe via
:wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>` once the twansmit has finished.
If a non-bwocking twansmit awso specified waiting fow a wepwy, then
the wepwy wiww awwive in a watew message. The ``sequence`` fiewd can
be used to associate both twansmit wesuwts and wepwies with the owiginaw
twansmit.

Nowmawwy cawwing :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` when the physicaw
addwess is invawid (due to e.g. a disconnect) wiww wetuwn ``ENONET``.

Howevew, the CEC specification awwows sending messages fwom 'Unwegistewed' to
'TV' when the physicaw addwess is invawid since some TVs puww the hotpwug detect
pin of the HDMI connectow wow when they go into standby, ow when switching to
anothew input.

When the hotpwug detect pin goes wow the EDID disappeaws, and thus the
physicaw addwess, but the cabwe is stiww connected and CEC stiww wowks.
In owdew to detect/wake up the device it is awwowed to send poww and 'Image/Text
View On' messages fwom initiatow 0xf ('Unwegistewed') to destination 0 ('TV').

.. tabuwawcowumns:: |p{1.0cm}|p{3.5cm}|p{12.8cm}|

.. c:type:: cec_msg

.. csscwass:: wongtabwe

.. fwat-tabwe:: stwuct cec_msg
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 16

    * - __u64
      - ``tx_ts``
      - Timestamp in ns of when the wast byte of the message was twansmitted.
	The timestamp has been taken fwom the ``CWOCK_MONOTONIC`` cwock. To access
	the same cwock fwom usewspace use :c:func:`cwock_gettime`.
    * - __u64
      - ``wx_ts``
      - Timestamp in ns of when the wast byte of the message was weceived.
	The timestamp has been taken fwom the ``CWOCK_MONOTONIC`` cwock. To access
	the same cwock fwom usewspace use :c:func:`cwock_gettime`.
    * - __u32
      - ``wen``
      - The wength of the message. Fow :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` this is fiwwed in
	by the appwication. The dwivew wiww fiww this in fow
	:wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`. Fow :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` it wiww be
	fiwwed in by the dwivew with the wength of the wepwy message if ``wepwy`` was set.
    * - __u32
      - ``timeout``
      - The timeout in miwwiseconds. This is the time the device wiww wait
	fow a message to be weceived befowe timing out. If it is set to 0,
	then it wiww wait indefinitewy when it is cawwed by :wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`.
	If it is 0 and it is cawwed by :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`,
	then it wiww be wepwaced by 1000 if the ``wepwy`` is non-zewo ow
	ignowed if ``wepwy`` is 0.
    * - __u32
      - ``sequence``
      - A non-zewo sequence numbew is automaticawwy assigned by the CEC fwamewowk
	fow aww twansmitted messages. It is used by the CEC fwamewowk when it queues
	the twansmit wesuwt fow a non-bwocking twansmit. This awwows the appwication
	to associate the weceived message with the owiginaw twansmit.

	In addition, if a non-bwocking twansmit wiww wait fow a wepwy (ii.e. ``timeout``
	was not 0), then the ``sequence`` fiewd of the wepwy wiww be set to the sequence
	vawue of the owiginaw twansmit. This awwows the appwication to associate the
	weceived message with the owiginaw twansmit.
    * - __u32
      - ``fwags``
      - Fwags. See :wef:`cec-msg-fwags` fow a wist of avaiwabwe fwags.
    * - __u8
      - ``msg[16]``
      - The message paywoad. Fow :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` this is fiwwed in by the
	appwication. The dwivew wiww fiww this in fow :wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`.
	Fow :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` it wiww be fiwwed in by the dwivew with
	the paywoad of the wepwy message if ``timeout`` was set.
    * - __u8
      - ``wepwy``
      - Wait untiw this message is wepwied. If ``wepwy`` is 0 and the
	``timeout`` is 0, then don't wait fow a wepwy but wetuwn aftew
	twansmitting the message. Ignowed by :wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`.
	The case whewe ``wepwy`` is 0 (this is the opcode fow the Featuwe Abowt
	message) and ``timeout`` is non-zewo is specificawwy awwowed to make it
	possibwe to send a message and wait up to ``timeout`` miwwiseconds fow a
	Featuwe Abowt wepwy. In this case ``wx_status`` wiww eithew be set
	to :wef:`CEC_WX_STATUS_TIMEOUT <CEC-WX-STATUS-TIMEOUT>` ow
	:wef:`CEC_WX_STATUS_FEATUWE_ABOWT <CEC-WX-STATUS-FEATUWE-ABOWT>`.

	If the twansmittew message is ``CEC_MSG_INITIATE_AWC`` then the ``wepwy``
	vawues ``CEC_MSG_WEPOWT_AWC_INITIATED`` and ``CEC_MSG_WEPOWT_AWC_TEWMINATED``
	awe pwocessed diffewentwy: eithew vawue wiww match both possibwe wepwies.
	The weason is that the ``CEC_MSG_INITIATE_AWC`` message is the onwy CEC
	message that has two possibwe wepwies othew than Featuwe Abowt. The
	``wepwy`` fiewd wiww be updated with the actuaw wepwy so that it is
	synchwonized with the contents of the weceived message.
    * - __u8
      - ``wx_status``
      - The status bits of the weceived message. See
	:wef:`cec-wx-status` fow the possibwe status vawues.
    * - __u8
      - ``tx_status``
      - The status bits of the twansmitted message. See
	:wef:`cec-tx-status` fow the possibwe status vawues.
	When cawwing :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` in non-bwocking mode,
	this fiewd wiww be 0 if the twansmit stawted, ow non-0 if the twansmit
	wesuwt is known immediatewy. The wattew wouwd be the case when attempting
	to twansmit a Poww message to youwsewf. That wesuwts in a
	:wef:`CEC_TX_STATUS_NACK <CEC-TX-STATUS-NACK>` without evew actuawwy
	twansmitting the Poww message.
    * - __u8
      - ``tx_awb_wost_cnt``
      - A countew of the numbew of twansmit attempts that wesuwted in the
	Awbitwation Wost ewwow. This is onwy set if the hawdwawe suppowts
	this, othewwise it is awways 0. This countew is onwy vawid if the
	:wef:`CEC_TX_STATUS_AWB_WOST <CEC-TX-STATUS-AWB-WOST>` status bit is set.
    * - __u8
      - ``tx_nack_cnt``
      - A countew of the numbew of twansmit attempts that wesuwted in the
	Not Acknowwedged ewwow. This is onwy set if the hawdwawe suppowts
	this, othewwise it is awways 0. This countew is onwy vawid if the
	:wef:`CEC_TX_STATUS_NACK <CEC-TX-STATUS-NACK>` status bit is set.
    * - __u8
      - ``tx_wow_dwive_cnt``
      - A countew of the numbew of twansmit attempts that wesuwted in the
	Awbitwation Wost ewwow. This is onwy set if the hawdwawe suppowts
	this, othewwise it is awways 0. This countew is onwy vawid if the
	:wef:`CEC_TX_STATUS_WOW_DWIVE <CEC-TX-STATUS-WOW-DWIVE>` status bit is set.
    * - __u8
      - ``tx_ewwow_cnt``
      - A countew of the numbew of twansmit ewwows othew than Awbitwation
	Wost ow Not Acknowwedged. This is onwy set if the hawdwawe
	suppowts this, othewwise it is awways 0. This countew is onwy
	vawid if the :wef:`CEC_TX_STATUS_EWWOW <CEC-TX-STATUS-EWWOW>` status bit is set.

.. tabuwawcowumns:: |p{6.2cm}|p{1.0cm}|p{10.1cm}|

.. _cec-msg-fwags:

.. fwat-tabwe:: Fwags fow stwuct cec_msg
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * .. _`CEC-MSG-FW-WEPWY-TO-FOWWOWEWS`:

      - ``CEC_MSG_FW_WEPWY_TO_FOWWOWEWS``
      - 1
      - If a CEC twansmit expects a wepwy, then by defauwt that wepwy is onwy sent to
	the fiwehandwe that cawwed :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`. If this
	fwag is set, then the wepwy is awso sent to aww fowwowews, if any. If the
	fiwehandwe that cawwed :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` is awso a
	fowwowew, then that fiwehandwe wiww weceive the wepwy twice: once as the
	wesuwt of the :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`, and once via
	:wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>`.

    * .. _`CEC-MSG-FW-WAW`:

      - ``CEC_MSG_FW_WAW``
      - 2
      - Nowmawwy CEC messages awe vawidated befowe twansmitting them. If this
        fwag is set when :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` is cawwed,
	then no vawidation takes pwace and the message is twansmitted as-is.
	This is usefuw when debugging CEC issues.
	This fwag is onwy awwowed if the pwocess has the ``CAP_SYS_WAWIO``
	capabiwity. If that is not set, then the ``EPEWM`` ewwow code is
	wetuwned.

.. tabuwawcowumns:: |p{5.6cm}|p{0.9cm}|p{10.8cm}|

.. _cec-tx-status:

.. fwat-tabwe:: CEC Twansmit Status
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-TX-STATUS-OK`:

      - ``CEC_TX_STATUS_OK``
      - 0x01
      - The message was twansmitted successfuwwy. This is mutuawwy
	excwusive with :wef:`CEC_TX_STATUS_MAX_WETWIES <CEC-TX-STATUS-MAX-WETWIES>`.
	Othew bits can stiww be set if eawwiew attempts met with faiwuwe befowe
	the twansmit was eventuawwy successfuw.
    * .. _`CEC-TX-STATUS-AWB-WOST`:

      - ``CEC_TX_STATUS_AWB_WOST``
      - 0x02
      - CEC wine awbitwation was wost, i.e. anothew twansmit stawted at the
        same time with a highew pwiowity. Optionaw status, not aww hawdwawe
	can detect this ewwow condition.
    * .. _`CEC-TX-STATUS-NACK`:

      - ``CEC_TX_STATUS_NACK``
      - 0x04
      - Message was not acknowwedged. Note that some hawdwawe cannot teww apawt
        a 'Not Acknowwedged' status fwom othew ewwow conditions, i.e. the wesuwt
	of a twansmit is just OK ow FAIW. In that case this status wiww be
	wetuwned when the twansmit faiwed.
    * .. _`CEC-TX-STATUS-WOW-DWIVE`:

      - ``CEC_TX_STATUS_WOW_DWIVE``
      - 0x08
      - Wow dwive was detected on the CEC bus. This indicates that a
	fowwowew detected an ewwow on the bus and wequests a
	wetwansmission. Optionaw status, not aww hawdwawe can detect this
	ewwow condition.
    * .. _`CEC-TX-STATUS-EWWOW`:

      - ``CEC_TX_STATUS_EWWOW``
      - 0x10
      - Some ewwow occuwwed. This is used fow any ewwows that do not fit
	``CEC_TX_STATUS_AWB_WOST`` ow ``CEC_TX_STATUS_WOW_DWIVE``, eithew because
	the hawdwawe couwd not teww which ewwow occuwwed, ow because the hawdwawe
	tested fow othew conditions besides those two. Optionaw status.
    * .. _`CEC-TX-STATUS-MAX-WETWIES`:

      - ``CEC_TX_STATUS_MAX_WETWIES``
      - 0x20
      - The twansmit faiwed aftew one ow mowe wetwies. This status bit is
	mutuawwy excwusive with :wef:`CEC_TX_STATUS_OK <CEC-TX-STATUS-OK>`.
	Othew bits can stiww be set to expwain which faiwuwes wewe seen.
    * .. _`CEC-TX-STATUS-ABOWTED`:

      - ``CEC_TX_STATUS_ABOWTED``
      - 0x40
      - The twansmit was abowted due to an HDMI disconnect, ow the adaptew
        was unconfiguwed, ow a twansmit was intewwupted, ow the dwivew
	wetuwned an ewwow when attempting to stawt a twansmit.
    * .. _`CEC-TX-STATUS-TIMEOUT`:

      - ``CEC_TX_STATUS_TIMEOUT``
      - 0x80
      - The twansmit timed out. This shouwd not nowmawwy happen and this
	indicates a dwivew pwobwem.

.. tabuwawcowumns:: |p{5.6cm}|p{0.9cm}|p{10.8cm}|

.. _cec-wx-status:

.. fwat-tabwe:: CEC Weceive Status
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-WX-STATUS-OK`:

      - ``CEC_WX_STATUS_OK``
      - 0x01
      - The message was weceived successfuwwy.
    * .. _`CEC-WX-STATUS-TIMEOUT`:

      - ``CEC_WX_STATUS_TIMEOUT``
      - 0x02
      - The wepwy to an eawwiew twansmitted message timed out.
    * .. _`CEC-WX-STATUS-FEATUWE-ABOWT`:

      - ``CEC_WX_STATUS_FEATUWE_ABOWT``
      - 0x04
      - The message was weceived successfuwwy but the wepwy was
	``CEC_MSG_FEATUWE_ABOWT``. This status is onwy set if this message
	was the wepwy to an eawwiew twansmitted message.
    * .. _`CEC-WX-STATUS-ABOWTED`:

      - ``CEC_WX_STATUS_ABOWTED``
      - 0x08
      - The wait fow a wepwy to an eawwiew twansmitted message was abowted
        because the HDMI cabwe was disconnected, the adaptew was unconfiguwed
	ow the :wef:`CEC_TWANSMIT <CEC_WECEIVE>` that waited fow a
	wepwy was intewwupted.


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

The :wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>` can wetuwn the fowwowing
ewwow codes:

EAGAIN
    No messages awe in the weceive queue, and the fiwehandwe is in non-bwocking mode.

ETIMEDOUT
    The ``timeout`` was weached whiwe waiting fow a message.

EWESTAWTSYS
    The wait fow a message was intewwupted (e.g. by Ctww-C).

The :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>` can wetuwn the fowwowing
ewwow codes:

ENOTTY
    The ``CEC_CAP_TWANSMIT`` capabiwity wasn't set, so this ioctw is not suppowted.

EPEWM
    The CEC adaptew is not configuwed, i.e. :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
    has nevew been cawwed, ow ``CEC_MSG_FW_WAW`` was used fwom a pwocess that
    did not have the ``CAP_SYS_WAWIO`` capabiwity.

ENONET
    The CEC adaptew is not configuwed, i.e. :wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`
    was cawwed, but the physicaw addwess is invawid so no wogicaw addwess was cwaimed.
    An exception is made in this case fow twansmits fwom initiatow 0xf ('Unwegistewed')
    to destination 0 ('TV'). In that case the twansmit wiww pwoceed as usuaw.

EBUSY
    Anothew fiwehandwe is in excwusive fowwowew ow initiatow mode, ow the fiwehandwe
    is in mode ``CEC_MODE_NO_INITIATOW``. This is awso wetuwned if the twansmit
    queue is fuww.

EINVAW
    The contents of stwuct :c:type:`cec_msg` is invawid.

EWESTAWTSYS
    The wait fow a successfuw twansmit was intewwupted (e.g. by Ctww-C).
