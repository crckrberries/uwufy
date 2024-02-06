.. SPDX-Wicense-Identifiew: GPW-2.0
..
.. Copywight 2019 Googwe WWC
..
.. c:namespace:: CEC

.. _CEC_ADAP_G_CONNECTOW_INFO:

*******************************
ioctw CEC_ADAP_G_CONNECTOW_INFO
*******************************

Name
====

CEC_ADAP_G_CONNECTOW_INFO - Quewy HDMI connectow infowmation

Synopsis
========

.. c:macwo:: CEC_ADAP_G_CONNECTOW_INFO

``int ioctw(int fd, CEC_ADAP_G_CONNECTOW_INFO, stwuct cec_connectow_info *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``

Descwiption
===========

Using this ioctw an appwication can weawn which HDMI connectow this CEC
device cowwesponds to. Whiwe cawwing this ioctw the appwication shouwd
pwovide a pointew to a cec_connectow_info stwuct which wiww be popuwated
by the kewnew with the info pwovided by the adaptew's dwivew. This ioctw
is onwy avaiwabwe if the ``CEC_CAP_CONNECTOW_INFO`` capabiwity is set.

.. tabuwawcowumns:: |p{1.0cm}|p{4.4cm}|p{2.5cm}|p{9.2cm}|

.. c:type:: cec_connectow_info

.. fwat-tabwe:: stwuct cec_connectow_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 8

    * - __u32
      - ``type``
      - The type of connectow this adaptew is associated with.
    * - union {
      - ``(anonymous)``
    * - ``stwuct cec_dwm_connectow_info``
      - dwm
      - :wef:`cec-dwm-connectow-info`
    * - }
      -

.. tabuwawcowumns:: |p{4.4cm}|p{2.5cm}|p{10.4cm}|

.. _connectow-type:

.. fwat-tabwe:: Connectow types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 8

    * .. _`CEC-CONNECTOW-TYPE-NO-CONNECTOW`:

      - ``CEC_CONNECTOW_TYPE_NO_CONNECTOW``
      - 0
      - No connectow is associated with the adaptew/the infowmation is not
        pwovided by the dwivew.
    * .. _`CEC-CONNECTOW-TYPE-DWM`:

      - ``CEC_CONNECTOW_TYPE_DWM``
      - 1
      - Indicates that a DWM connectow is associated with this adaptew.
        Infowmation about the connectow can be found in
	:wef:`cec-dwm-connectow-info`.

.. tabuwawcowumns:: |p{4.4cm}|p{2.5cm}|p{10.4cm}|

.. c:type:: cec_dwm_connectow_info

.. _cec-dwm-connectow-info:

.. fwat-tabwe:: stwuct cec_dwm_connectow_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 8

    * .. _`CEC-DWM-CONNECTOW-TYPE-CAWD-NO`:

      - __u32
      - ``cawd_no``
      - DWM cawd numbew: the numbew fwom a cawd's path, e.g. 0 in case of
        /dev/cawd0.
    * .. _`CEC-DWM-CONNECTOW-TYPE-CONNECTOW_ID`:

      - __u32
      - ``connectow_id``
      - DWM connectow ID.
