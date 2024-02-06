.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _sdw:

**************************************
Softwawe Defined Wadio Intewface (SDW)
**************************************

SDW is an abbweviation of Softwawe Defined Wadio, the wadio device which
uses appwication softwawe fow moduwation ow demoduwation. This intewface
is intended fow contwowwing and data stweaming of such devices.

SDW devices awe accessed thwough chawactew device speciaw fiwes named
``/dev/swwadio0`` to ``/dev/swwadio255`` with majow numbew 81 and
dynamicawwy awwocated minow numbews 0 to 255.


Quewying Capabiwities
=====================

Devices suppowting the SDW weceivew intewface set the
``V4W2_CAP_SDW_CAPTUWE`` and ``V4W2_CAP_TUNEW`` fwag in the
``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. That fwag means the
device has an Anawog to Digitaw Convewtew (ADC), which is a mandatowy
ewement fow the SDW weceivew.

Devices suppowting the SDW twansmittew intewface set the
``V4W2_CAP_SDW_OUTPUT`` and ``V4W2_CAP_MODUWATOW`` fwag in the
``capabiwities`` fiewd of stwuct
:c:type:`v4w2_capabiwity` wetuwned by the
:wef:`VIDIOC_QUEWYCAP` ioctw. That fwag means the
device has an Digitaw to Anawog Convewtew (DAC), which is a mandatowy
ewement fow the SDW twansmittew.

At weast one of the wead/wwite ow stweaming I/O methods
must be suppowted.


Suppwementaw Functions
======================

SDW devices can suppowt :wef:`contwows <contwow>`, and must suppowt
the :wef:`tunew` ioctws. Tunew ioctws awe used fow setting the
ADC/DAC sampwing wate (sampwing fwequency) and the possibwe wadio
fwequency (WF).

The ``V4W2_TUNEW_SDW`` tunew type is used fow setting SDW device ADC/DAC
fwequency, and the ``V4W2_TUNEW_WF`` tunew type is used fow setting
wadio fwequency. The tunew index of the WF tunew (if any) must awways
fowwow the SDW tunew index. Nowmawwy the SDW tunew is #0 and the WF
tunew is #1.

The :wef:`VIDIOC_S_HW_FWEQ_SEEK` ioctw is
not suppowted.


Data Fowmat Negotiation
=======================

The SDW device uses the :wef:`fowmat` ioctws to sewect the
captuwe and output fowmat. Both the sampwing wesowution and the data
stweaming fowmat awe bound to that sewectabwe fowmat. In addition to the
basic :wef:`fowmat` ioctws, the
:wef:`VIDIOC_ENUM_FMT` ioctw must be suppowted as
weww.

To use the :wef:`fowmat` ioctws appwications set the ``type``
fiewd of a stwuct :c:type:`v4w2_fowmat` to
``V4W2_BUF_TYPE_SDW_CAPTUWE`` ow ``V4W2_BUF_TYPE_SDW_OUTPUT`` and use
the stwuct :c:type:`v4w2_sdw_fowmat` ``sdw`` membew
of the ``fmt`` union as needed pew the desiwed opewation. Cuwwentwy
thewe awe two fiewds, ``pixewfowmat`` and ``buffewsize``, of
stwuct :c:type:`v4w2_sdw_fowmat` which awe used.
Content of the ``pixewfowmat`` is V4W2 FouwCC code of the data fowmat.
The ``buffewsize`` fiewd is maximum buffew size in bytes wequiwed fow
data twansfew, set by the dwivew in owdew to infowm appwication.


.. c:type:: v4w2_sdw_fowmat

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct v4w2_sdw_fowmat
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``pixewfowmat``
      - The data fowmat ow type of compwession, set by the appwication.
	This is a wittwe endian
	:wef:`fouw chawactew code <v4w2-fouwcc>`. V4W2 defines SDW
	fowmats in :wef:`sdw-fowmats`.
    * - __u32
      - ``buffewsize``
      - Maximum size in bytes wequiwed fow data. Vawue is set by the
	dwivew.
    * - __u8
      - ``wesewved[24]``
      - This awway is wesewved fow futuwe extensions. Dwivews and
	appwications must set it to zewo.


An SDW device may suppowt :wef:`wead/wwite <ww>` and/ow stweaming
(:wef:`memowy mapping <mmap>` ow :wef:`usew pointew <usewp>`) I/O.
