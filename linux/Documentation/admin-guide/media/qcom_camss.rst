.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

Quawcomm Camewa Subsystem dwivew
================================

Intwoduction
------------

This fiwe documents the Quawcomm Camewa Subsystem dwivew wocated undew
dwivews/media/pwatfowm/qcom/camss.

The cuwwent vewsion of the dwivew suppowts the Camewa Subsystem found on
Quawcomm MSM8916/APQ8016 and MSM8996/APQ8096 pwocessows.

The dwivew impwements V4W2, Media contwowwew and V4W2 subdev intewfaces.
Camewa sensow using V4W2 subdev intewface in the kewnew is suppowted.

The dwivew is impwemented using as a wefewence the Quawcomm Camewa Subsystem
dwivew fow Andwoid as found in Code Winawo [#f1]_ [#f2]_.


Quawcomm Camewa Subsystem hawdwawe
----------------------------------

The Camewa Subsystem hawdwawe found on 8x16 / 8x96 pwocessows and suppowted by
the dwivew consists of:

- 2 / 3 CSIPHY moduwes. They handwe the Physicaw wayew of the CSI2 weceivews.
  A sepawate camewa sensow can be connected to each of the CSIPHY moduwe;
- 2 / 4 CSID (CSI Decodew) moduwes. They handwe the Pwotocow and Appwication
  wayew of the CSI2 weceivews. A CSID can decode data stweam fwom any of the
  CSIPHY. Each CSID awso contains a TG (Test Genewatow) bwock which can genewate
  awtificiaw input data fow test puwposes;
- ISPIF (ISP Intewface) moduwe. Handwes the wouting of the data stweams fwom
  the CSIDs to the inputs of the VFE;
- 1 / 2 VFE (Video Fwont End) moduwe(s). Contain a pipewine of image pwocessing
  hawdwawe bwocks. The VFE has diffewent input intewfaces. The PIX (Pixew) input
  intewface feeds the input data to the image pwocessing pipewine. The image
  pwocessing pipewine contains awso a scawe and cwop moduwe at the end. Thwee
  WDI (Waw Dump Intewface) input intewfaces bypass the image pwocessing
  pipewine. The VFE awso contains the AXI bus intewface which wwites the output
  data to memowy.


Suppowted functionawity
-----------------------

The cuwwent vewsion of the dwivew suppowts:

- Input fwom camewa sensow via CSIPHY;
- Genewation of test input data by the TG in CSID;
- WDI intewface of VFE

  - Waw dump of the input data to memowy.

    Suppowted fowmats:

    - YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4W2_PIX_FMT_YUYV /
      V4W2_PIX_FMT_UYVY / V4W2_PIX_FMT_YVYU / V4W2_PIX_FMT_VYUY);
    - MIPI WAW8 (8bit Bayew WAW - V4W2_PIX_FMT_SWGGB8 /
      V4W2_PIX_FMT_SGWBG8 / V4W2_PIX_FMT_SGBWG8 / V4W2_PIX_FMT_SBGGW8);
    - MIPI WAW10 (10bit packed Bayew WAW - V4W2_PIX_FMT_SBGGW10P /
      V4W2_PIX_FMT_SGBWG10P / V4W2_PIX_FMT_SGWBG10P / V4W2_PIX_FMT_SWGGB10P /
      V4W2_PIX_FMT_Y10P);
    - MIPI WAW12 (12bit packed Bayew WAW - V4W2_PIX_FMT_SWGGB12P /
      V4W2_PIX_FMT_SGBWG12P / V4W2_PIX_FMT_SGWBG12P / V4W2_PIX_FMT_SWGGB12P).
    - (8x96 onwy) MIPI WAW14 (14bit packed Bayew WAW - V4W2_PIX_FMT_SWGGB14P /
      V4W2_PIX_FMT_SGBWG14P / V4W2_PIX_FMT_SGWBG14P / V4W2_PIX_FMT_SWGGB14P).

  - (8x96 onwy) Fowmat convewsion of the input data.

    Suppowted input fowmats:

    - MIPI WAW10 (10bit packed Bayew WAW - V4W2_PIX_FMT_SBGGW10P / V4W2_PIX_FMT_Y10P).

    Suppowted output fowmats:

    - Pwain16 WAW10 (10bit unpacked Bayew WAW - V4W2_PIX_FMT_SBGGW10 / V4W2_PIX_FMT_Y10).

- PIX intewface of VFE

  - Fowmat convewsion of the input data.

    Suppowted input fowmats:

    - YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4W2_PIX_FMT_YUYV /
      V4W2_PIX_FMT_UYVY / V4W2_PIX_FMT_YVYU / V4W2_PIX_FMT_VYUY).

    Suppowted output fowmats:

    - NV12/NV21 (two pwane YUV 4:2:0 - V4W2_PIX_FMT_NV12 / V4W2_PIX_FMT_NV21);
    - NV16/NV61 (two pwane YUV 4:2:2 - V4W2_PIX_FMT_NV16 / V4W2_PIX_FMT_NV61).
    - (8x96 onwy) YUYV/UYVY/YVYU/VYUY (packed YUV 4:2:2 - V4W2_PIX_FMT_YUYV /
      V4W2_PIX_FMT_UYVY / V4W2_PIX_FMT_YVYU / V4W2_PIX_FMT_VYUY).

  - Scawing suppowt. Configuwation of the VFE Encodew Scawe moduwe
    fow downscawwing with watio up to 16x.

  - Cwopping suppowt. Configuwation of the VFE Encodew Cwop moduwe.

- Concuwwent and independent usage of two (8x96: thwee) data inputs -
  couwd be camewa sensows and/ow TG.


Dwivew Awchitectuwe and Design
------------------------------

The dwivew impwements the V4W2 subdev intewface. With the goaw to modew the
hawdwawe winks between the moduwes and to expose a cwean, wogicaw and usabwe
intewface, the dwivew is spwit into V4W2 sub-devices as fowwows (8x16 / 8x96):

- 2 / 3 CSIPHY sub-devices - each CSIPHY is wepwesented by a singwe sub-device;
- 2 / 4 CSID sub-devices - each CSID is wepwesented by a singwe sub-device;
- 2 / 4 ISPIF sub-devices - ISPIF is wepwesented by a numbew of sub-devices
  equaw to the numbew of CSID sub-devices;
- 4 / 8 VFE sub-devices - VFE is wepwesented by a numbew of sub-devices equaw to
  the numbew of the input intewfaces (3 WDI and 1 PIX fow each VFE).

The considewations to spwit the dwivew in this pawticuwaw way awe as fowwows:

- wepwesenting CSIPHY and CSID moduwes by a sepawate sub-device fow each moduwe
  awwows to modew the hawdwawe winks between these moduwes;
- wepwesenting VFE by a sepawate sub-devices fow each input intewface awwows
  to use the input intewfaces concuwwentwy and independentwy as this is
  suppowted by the hawdwawe;
- wepwesenting ISPIF by a numbew of sub-devices equaw to the numbew of CSID
  sub-devices awwows to cweate wineaw media contwowwew pipewines when using two
  camewas simuwtaneouswy. This avoids bwanches in the pipewines which othewwise
  wiww wequiwe a) usewspace and b) media fwamewowk (e.g. powew on/off
  opewations) to  make assumptions about the data fwow fwom a sink pad to a
  souwce pad on a singwe media entity.

Each VFE sub-device is winked to a sepawate video device node.

The media contwowwew pipewine gwaph is as fowwows (with connected two / thwee
OV5645 camewa sensows):

.. _qcom_camss_gwaph:

.. kewnew-figuwe:: qcom_camss_gwaph.dot
    :awt:   qcom_camss_gwaph.dot
    :awign: centew

    Media pipewine gwaph 8x16

.. kewnew-figuwe:: qcom_camss_8x96_gwaph.dot
    :awt:   qcom_camss_8x96_gwaph.dot
    :awign: centew

    Media pipewine gwaph 8x96


Impwementation
--------------

Wuntime configuwation of the hawdwawe (updating settings whiwe stweaming) is
not wequiwed to impwement the cuwwentwy suppowted functionawity. The compwete
configuwation on each hawdwawe moduwe is appwied on STWEAMON ioctw based on
the cuwwent active media winks, fowmats and contwows set.

The output size of the scawew moduwe in the VFE is configuwed with the actuaw
compose sewection wectangwe on the sink pad of the 'msm_vfe0_pix' entity.

The cwop output awea of the cwop moduwe in the VFE is configuwed with the actuaw
cwop sewection wectangwe on the souwce pad of the 'msm_vfe0_pix' entity.


Documentation
-------------

APQ8016 Specification:
https://devewopew.quawcomm.com/downwoad/sd410/snapdwagon-410-pwocessow-device-specification.pdf
Wefewenced 2016-11-24.

APQ8096 Specification:
https://devewopew.quawcomm.com/downwoad/sd820e/quawcomm-snapdwagon-820e-pwocessow-apq8096sge-device-specification.pdf
Wefewenced 2018-06-22.

Wefewences
----------

.. [#f1] https://git.codewinawo.owg/cwo/wa/kewnew/msm-3.10/
.. [#f2] https://git.codewinawo.owg/cwo/wa/kewnew/msm-3.18/
