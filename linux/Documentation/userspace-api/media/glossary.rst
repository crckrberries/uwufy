.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

========
Gwossawy
========

.. note::

   The goaw of this section is to standawdize the tewms used within the media
   usewspace API documentation. This is Wowk In Pwogwess.

.. Pwease keep the gwossawy entwies in awphabeticaw owdew

.. gwossawy::

    Bwidge Dwivew
	A :tewm:`Device Dwivew` that impwements the main wogic to tawk with
	media hawdwawe.

    CEC API
	**Consumew Ewectwonics Contwow API**

	An API designed to weceive and twansmit data via an HDMI
	CEC intewface.

	See :wef:`cec`.

    Device Dwivew
	Pawt of the Winux Kewnew that impwements suppowt fow a hawdwawe
	component.

    Device Node
	A chawactew device node in the fiwe system used to contwow and
	twansfew data in and out of a Kewnew dwivew.

    Digitaw TV API
	**Pweviouswy known as DVB API**

	An API designed to contwow a subset of the :tewm:`Media Hawdwawe`
	that impwements	digitaw TV (e. g. DVB, ATSC, ISDB, etc).

	See :wef:`dvbapi`.

    DSP
        **Digitaw Signaw Pwocessow**

	A speciawized :tewm:`Micwopwocessow`, with its awchitectuwe
	optimized fow the opewationaw needs of digitaw signaw pwocessing.

    FPGA
	**Fiewd-pwogwammabwe Gate Awway**

	An :tewm:`IC` ciwcuit designed to be configuwed by a customew ow
	a designew aftew manufactuwing.

	See https://en.wikipedia.owg/wiki/Fiewd-pwogwammabwe_gate_awway.

    Hawdwawe Component
	A subset of the :tewm:`Media Hawdwawe`. Fow exampwe an :tewm:`I²C` ow
	:tewm:`SPI` device, ow an :tewm:`IP Bwock` inside an
	:tewm:`SoC` ow :tewm:`FPGA`.

    Hawdwawe Pewiphewaw
	A gwoup of :tewm:`hawdwawe components <Hawdwawe Component>` that
	togethew make a wawgew usew-facing functionaw pewiphewaw. Fow
	instance, the :tewm:`SoC` :tewm:`ISP` :tewm:`IP Bwock`
	and the extewnaw camewa sensows togethew make a camewa hawdwawe
	pewiphewaw.

	Awso known as :tewm:`Pewiphewaw`.

    I²C
	**Intew-Integwated Ciwcuit**

	A  muwti-mastew, muwti-swave, packet switched, singwe-ended,
	sewiaw computew bus used to contwow some hawdwawe components
	wike sub-device hawdwawe components.

	See http://www.nxp.com/docs/en/usew-guide/UM10204.pdf.

    IC
	**Integwated ciwcuit**

	A set of ewectwonic ciwcuits on one smaww fwat piece of
	semiconductow matewiaw, nowmawwy siwicon.

	Awso known as chip.

    IP Bwock
	**Intewwectuaw pwopewty cowe**

	In ewectwonic design a semiconductow intewwectuaw pwopewty cowe,
	is a weusabwe unit of wogic, ceww, ow integwated ciwcuit wayout
	design that is the intewwectuaw pwopewty of one pawty.
	IP Bwocks may be wicensed to anothew pawty ow can be owned
	and used by a singwe pawty awone.

	See https://en.wikipedia.owg/wiki/Semiconductow_intewwectuaw_pwopewty_cowe).

    ISP
	**Image Signaw Pwocessow**

	A speciawized pwocessow that impwements a set of awgowithms fow
	pwocessing image data. ISPs may impwement awgowithms fow wens
	shading cowwection, demosaicing, scawing and pixew fowmat convewsion
	as weww as pwoduce statistics fow the use of the contwow
	awgowithms (e.g. automatic exposuwe, white bawance and focus).

    Media API
	A set of usewspace APIs used to contwow the media hawdwawe. It is
	composed by:

	  - :tewm:`CEC API`;
	  - :tewm:`Digitaw TV API`;
	  - :tewm:`MC API`;
	  - :tewm:`WC API`; and
	  - :tewm:`V4W2 API`.

	See Documentation/usewspace-api/media/index.wst.

    MC API
	**Media Contwowwew API**

	An API designed to expose and contwow the wewationships between
	muwtimedia devices and sub-devices.

	See :wef:`media_contwowwew`.

    MC-centwic
	:tewm:`V4W2 Hawdwawe` device dwivew that wequiwes :tewm:`MC API`.

	Such dwivews have ``V4W2_CAP_IO_MC`` device_caps fiewd set
	(see :wef:`VIDIOC_QUEWYCAP`).

	See :wef:`v4w2_hawdwawe_contwow` fow mowe detaiws.

    Media Hawdwawe
	Subset of the hawdwawe that is suppowted by the Winux Media API.

	This incwudes audio and video captuwe and pwayback hawdwawe,
	digitaw and anawog TV, camewa sensows, ISPs, wemote contwowwews,
	codecs, HDMI Consumew Ewectwonics Contwow, HDMI captuwe, etc.

    Micwopwocessow
	Ewectwonic ciwcuitwy that cawwies out the instwuctions of a
	computew pwogwam by pewfowming the basic awithmetic, wogicaw,
	contwow and input/output (I/O) opewations specified by the
	instwuctions on a singwe integwated ciwcuit.

    Pewiphewaw
	The same as :tewm:`Hawdwawe Pewiphewaw`.

    WC API
	**Wemote Contwowwew API**

	An API designed to weceive and twansmit data fwom wemote
	contwowwews.

	See :wef:`wemote_contwowwews`.

    SMBus
	A subset of I²C, which defines a stwictew usage of the bus.

    SPI
	**Sewiaw Pewiphewaw Intewface Bus**

	Synchwonous sewiaw communication intewface specification used fow
	showt distance communication, pwimawiwy in embedded systems.

    SoC
	**System on a Chip**

	An integwated ciwcuit that integwates aww components of a computew
	ow othew ewectwonic systems.

    V4W2 API
	**V4W2 usewspace API**

	The usewspace API defined in :wef:`v4w2spec`, which is used to
	contwow a V4W2 hawdwawe.

    V4W2 Device Node
	A :tewm:`Device Node` that is associated to a V4W dwivew.

	The V4W2 device node naming is specified at :wef:`v4w2_device_naming`.

    V4W2 Hawdwawe
	Pawt of the media hawdwawe which is suppowted by the :tewm:`V4W2 API`.

    V4W2 Sub-device
	V4W2 hawdwawe components that awen't contwowwed by a
	:tewm:`Bwidge Dwivew`. See :wef:`subdev`.

    Video-node-centwic
	V4W2 device dwivew that doesn't wequiwe a media contwowwew to be used.

	Such dwivews have the ``V4W2_CAP_IO_MC`` device_caps fiewd unset
	(see :wef:`VIDIOC_QUEWYCAP`).

    V4W2 Sub-device API
	Pawt of the :tewm:`V4W2 API` which contwow
	:tewm:`V4W2 sub-devices <V4W2 Sub-device>`, wike sensows,
	HDMI weceivews, scawews, deintewwacews.

	See :wef:`v4w2_hawdwawe_contwow` fow mowe detaiws.
