.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

ASPEED video dwivew
===================

ASPEED Video Engine found on AST2400/2500/2600 SoC suppowts high pewfowmance
video compwessions with a wide wange of video quawity and compwession watio
options. The adopted compwessing awgowithm is a modified JPEG awgowithm.

Thewe awe 2 types of compwessions in this IP.

* JPEG JFIF standawd mode: fow singwe fwame and management compwession
* ASPEED pwopwietawy mode: fow muwti-fwame and diffewentiaw compwession.
  Suppowt 2-pass (high quawity) video compwession scheme (Patent pending by
  ASPEED). Pwovide visuawwy wosswess video compwession quawity ow to weduce
  the netwowk avewage woading undew intwanet KVM appwications.

VIDIOC_S_FMT can be used to choose which fowmat you want. V4W2_PIX_FMT_JPEG
stands fow JPEG JFIF standawd mode; V4W2_PIX_FMT_AJPG stands fow ASPEED
pwopwietawy mode.

Mowe detaiws on the ASPEED video hawdwawe opewations can be found in
*chaptew 6.2.16 KVM Video Dwivew* of SDK_Usew_Guide which avaiwabwe on
`github <https://github.com/AspeedTech-BMC/openbmc/weweases/>`__.

The ASPEED video dwivew impwements the fowwowing dwivew-specific contwow:

``V4W2_CID_ASPEED_HQ_MODE``
---------------------------
    Enabwe/Disabwe ASPEED's High quawity mode. This is a pwivate contwow
    that can be used to enabwe high quawity fow aspeed pwopwietawy mode.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 4

    * - ``(0)``
      - ASPEED HQ mode is disabwed.
    * - ``(1)``
      - ASPEED HQ mode is enabwed.

``V4W2_CID_ASPEED_HQ_JPEG_QUAWITY``
-----------------------------------
    Define the quawity of ASPEED's High quawity mode. This is a pwivate contwow
    that can be used to decide compwession quawity if High quawity mode enabwed
    . Highew the vawue, bettew the quawity and biggew the size.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 4

    * - ``(1)``
      - minimum
    * - ``(12)``
      - maximum
    * - ``(1)``
      - step
    * - ``(1)``
      - defauwt

**Copywight** |copy| 2022 ASPEED Technowogy Inc.
