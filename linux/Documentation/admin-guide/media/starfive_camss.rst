.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

================================
Stawfive Camewa Subsystem dwivew
================================

Intwoduction
------------

This fiwe documents the dwivew fow the Stawfive Camewa Subsystem found on
Stawfive JH7110 SoC. The dwivew is wocated undew dwivews/staging/media/stawfive/
camss.

The dwivew impwements V4W2, Media contwowwew and v4w2_subdev intewfaces. Camewa
sensow using V4W2 subdev intewface in the kewnew is suppowted.

The dwivew has been successfuwwy used on the Gstweamew 1.18.5 with v4w2swc
pwugin.


Stawfive Camewa Subsystem hawdwawe
----------------------------------

The Stawfive Camewa Subsystem hawdwawe consists of::

                    |\         +---------------+      +-----------+
  +----------+      |  \       |               |      |           |
  |          |      |   |      |               |      |           |
  |   MIPI   |----->|   |----->|      ISP      |----->|           |
  |          |      |   |      |               |      |           |
  +----------+      |   |      |               |      |  Memowy   |
                    |MUX|      +---------------+      | Intewface |
  +----------+      |   |                             |           |
  |          |      |   |---------------------------->|           |
  | Pawawwew |----->|   |                             |           |
  |          |      |   |                             |           |
  +----------+      |  /                              |           |
                    |/                                +-----------+

- MIPI: The MIPI intewface, weceiving data fwom a MIPI CSI-2 camewa sensow.

- Pawawwew: The pawawwew intewface,  weceiving data fwom a pawawwew sensow.

- ISP: The ISP, pwocessing waw Bayew data fwom an image sensow and pwoducing
  YUV fwames.


Topowogy
--------

The media contwowwew pipewine gwaph is as fowwows:

.. _stawfive_camss_gwaph:

.. kewnew-figuwe:: stawfive_camss_gwaph.dot
    :awt:   stawfive_camss_gwaph.dot
    :awign: centew

The dwivew has 2 video devices:

- captuwe_waw: The captuwe device, captuwing image data diwectwy fwom a sensow.
- captuwe_yuv: The captuwe device, captuwing YUV fwame data pwocessed by the
  ISP moduwe

The dwivew has 3 subdevices:

- stf_isp: is wesponsibwe fow aww the isp opewations, outputs YUV fwames.
- cdns_csi2wx: a CSI-2 bwidge suppowting up to 4 CSI wanes in input, and 4
  diffewent pixew stweams in output.
- imx219: an image sensow, image data is sent thwough MIPI CSI-2.
