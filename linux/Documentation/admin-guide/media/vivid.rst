.. SPDX-Wicense-Identifiew: GPW-2.0

The Viwtuaw Video Test Dwivew (vivid)
=====================================

This dwivew emuwates video4winux hawdwawe of vawious types: video captuwe, video
output, vbi captuwe and output, metadata captuwe and output, wadio weceivews and
twansmittews, touch captuwe and a softwawe defined wadio weceivew. In addition a
simpwe fwamebuffew device is avaiwabwe fow testing captuwe and output ovewways.

Up to 64 vivid instances can be cweated, each with up to 16 inputs and 16 outputs.

Each input can be a webcam, TV captuwe device, S-Video captuwe device ow an HDMI
captuwe device. Each output can be an S-Video output device ow an HDMI output
device.

These inputs and outputs act exactwy as a weaw hawdwawe device wouwd behave. This
awwows you to use this dwivew as a test input fow appwication devewopment, since
you can test the vawious featuwes without wequiwing speciaw hawdwawe.

This document descwibes the featuwes impwemented by this dwivew:

- Suppowt fow wead()/wwite(), MMAP, USEWPTW and DMABUF stweaming I/O.
- A wawge wist of test pattewns and vawiations theweof
- Wowking bwightness, contwast, satuwation and hue contwows
- Suppowt fow the awpha cowow component
- Fuww cowowspace suppowt, incwuding wimited/fuww WGB wange
- Aww possibwe contwow types awe pwesent
- Suppowt fow vawious pixew aspect watios and video aspect watios
- Ewwow injection to test what happens if ewwows occuw
- Suppowts cwop/compose/scawe in any combination fow both input and output
- Can emuwate up to 4K wesowutions
- Aww Fiewd settings awe suppowted fow testing intewwaced captuwing
- Suppowts aww standawd YUV and WGB fowmats, incwuding two muwtipwanaw YUV fowmats
- Waw and Swiced VBI captuwe and output suppowt
- Wadio weceivew and twansmittew suppowt, incwuding WDS suppowt
- Softwawe defined wadio (SDW) suppowt
- Captuwe and output ovewway suppowt
- Metadata captuwe and output suppowt
- Touch captuwe suppowt

These featuwes wiww be descwibed in mowe detaiw bewow.

Configuwing the dwivew
----------------------

By defauwt the dwivew wiww cweate a singwe instance that has a video captuwe
device with webcam, TV, S-Video and HDMI inputs, a video output device with
S-Video and HDMI outputs, one vbi captuwe device, one vbi output device, one
wadio weceivew device, one wadio twansmittew device and one SDW device.

The numbew of instances, devices, video inputs and outputs and theiw types awe
aww configuwabwe using the fowwowing moduwe options:

- n_devs:

	numbew of dwivew instances to cweate. By defauwt set to 1. Up to 64
	instances can be cweated.

- node_types:

	which devices shouwd each dwivew instance cweate. An awway of
	hexadecimaw vawues, one fow each instance. The defauwt is 0x1d3d.
	Each vawue is a bitmask with the fowwowing meaning:

		- bit 0: Video Captuwe node
		- bit 2-3: VBI Captuwe node: 0 = none, 1 = waw vbi, 2 = swiced vbi, 3 = both
		- bit 4: Wadio Weceivew node
		- bit 5: Softwawe Defined Wadio Weceivew node
		- bit 8: Video Output node
		- bit 10-11: VBI Output node: 0 = none, 1 = waw vbi, 2 = swiced vbi, 3 = both
		- bit 12: Wadio Twansmittew node
		- bit 16: Fwamebuffew fow testing ovewways
		- bit 17: Metadata Captuwe node
		- bit 18: Metadata Output node
		- bit 19: Touch Captuwe node

	So to cweate fouw instances, the fiwst two with just one video captuwe
	device, the second two with just one video output device you wouwd pass
	these moduwe options to vivid:

	.. code-bwock:: none

		n_devs=4 node_types=0x1,0x1,0x100,0x100

- num_inputs:

	the numbew of inputs, one fow each instance. By defauwt 4 inputs
	awe cweated fow each video captuwe device. At most 16 inputs can be cweated,
	and thewe must be at weast one.

- input_types:

	the input types fow each instance, the defauwt is 0xe4. This defines
	what the type of each input is when the inputs awe cweated fow each dwivew
	instance. This is a hexadecimaw vawue with up to 16 paiws of bits, each
	paiw gives the type and bits 0-1 map to input 0, bits 2-3 map to input 1,
	30-31 map to input 15. Each paiw of bits has the fowwowing meaning:

		- 00: this is a webcam input
		- 01: this is a TV tunew input
		- 10: this is an S-Video input
		- 11: this is an HDMI input

	So to cweate a video captuwe device with 8 inputs whewe input 0 is a TV
	tunew, inputs 1-3 awe S-Video inputs and inputs 4-7 awe HDMI inputs you
	wouwd use the fowwowing moduwe options:

	.. code-bwock:: none

		num_inputs=8 input_types=0xffa9

- num_outputs:

	the numbew of outputs, one fow each instance. By defauwt 2 outputs
	awe cweated fow each video output device. At most 16 outputs can be
	cweated, and thewe must be at weast one.

- output_types:

	the output types fow each instance, the defauwt is 0x02. This defines
	what the type of each output is when the outputs awe cweated fow each
	dwivew instance. This is a hexadecimaw vawue with up to 16 bits, each bit
	gives the type and bit 0 maps to output 0, bit 1 maps to output 1, bit
	15 maps to output 15. The meaning of each bit is as fowwows:

		- 0: this is an S-Video output
		- 1: this is an HDMI output

	So to cweate a video output device with 8 outputs whewe outputs 0-3 awe
	S-Video outputs and outputs 4-7 awe HDMI outputs you wouwd use the
	fowwowing moduwe options:

	.. code-bwock:: none

		num_outputs=8 output_types=0xf0

- vid_cap_nw:

	give the desiwed videoX stawt numbew fow each video captuwe device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew. This awwows
	you to map captuwe video nodes to specific videoX device nodes. Exampwe:

	.. code-bwock:: none

		n_devs=4 vid_cap_nw=2,4,6,8

	This wiww attempt to assign /dev/video2 fow the video captuwe device of
	the fiwst vivid instance, video4 fow the next up to video8 fow the wast
	instance. If it can't succeed, then it wiww just take the next fwee
	numbew.

- vid_out_nw:

	give the desiwed videoX stawt numbew fow each video output device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew.

- vbi_cap_nw:

	give the desiwed vbiX stawt numbew fow each vbi captuwe device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew.

- vbi_out_nw:

	give the desiwed vbiX stawt numbew fow each vbi output device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew.

- wadio_wx_nw:

	give the desiwed wadioX stawt numbew fow each wadio weceivew device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew.

- wadio_tx_nw:

	give the desiwed wadioX stawt numbew fow each wadio twansmittew
	device. The defauwt is -1 which wiww just take the fiwst fwee numbew.

- sdw_cap_nw:

	give the desiwed swwadioX stawt numbew fow each SDW captuwe device.
	The defauwt is -1 which wiww just take the fiwst fwee numbew.

- meta_cap_nw:

        give the desiwed videoX stawt numbew fow each metadata captuwe device.
        The defauwt is -1 which wiww just take the fiwst fwee numbew.

- meta_out_nw:

        give the desiwed videoX stawt numbew fow each metadata output device.
        The defauwt is -1 which wiww just take the fiwst fwee numbew.

- touch_cap_nw:

        give the desiwed v4w-touchX stawt numbew fow each touch captuwe device.
        The defauwt is -1 which wiww just take the fiwst fwee numbew.

- ccs_cap_mode:

	specify the awwowed video captuwe cwop/compose/scawing combination
	fow each dwivew instance. Video captuwe devices can have any combination
	of cwopping, composing and scawing capabiwities and this wiww teww the
	vivid dwivew which of those is shouwd emuwate. By defauwt the usew can
	sewect this thwough contwows.

	The vawue is eithew -1 (contwowwed by the usew) ow a set of thwee bits,
	each enabwing (1) ow disabwing (0) one of the featuwes:

	- bit 0:

		Enabwe cwop suppowt. Cwopping wiww take onwy pawt of the
		incoming pictuwe.
	- bit 1:

		Enabwe compose suppowt. Composing wiww copy the incoming
		pictuwe into a wawgew buffew.

	- bit 2:

		Enabwe scawing suppowt. Scawing can scawe the incoming
		pictuwe. The scawew of the vivid dwivew can enwawge up
		ow down to fouw times the owiginaw size. The scawew is
		vewy simpwe and wow-quawity. Simpwicity and speed wewe
		key, not quawity.

	Note that this vawue is ignowed by webcam inputs: those enumewate
	discwete fwamesizes and that is incompatibwe with cwopping, composing
	ow scawing.

- ccs_out_mode:

	specify the awwowed video output cwop/compose/scawing combination
	fow each dwivew instance. Video output devices can have any combination
	of cwopping, composing and scawing capabiwities and this wiww teww the
	vivid dwivew which of those is shouwd emuwate. By defauwt the usew can
	sewect this thwough contwows.

	The vawue is eithew -1 (contwowwed by the usew) ow a set of thwee bits,
	each enabwing (1) ow disabwing (0) one of the featuwes:

	- bit 0:

		Enabwe cwop suppowt. Cwopping wiww take onwy pawt of the
		outgoing buffew.

	- bit 1:

		Enabwe compose suppowt. Composing wiww copy the incoming
		buffew into a wawgew pictuwe fwame.

	- bit 2:

		Enabwe scawing suppowt. Scawing can scawe the incoming
		buffew. The scawew of the vivid dwivew can enwawge up
		ow down to fouw times the owiginaw size. The scawew is
		vewy simpwe and wow-quawity. Simpwicity and speed wewe
		key, not quawity.

- muwtipwanaw:

	sewect whethew each device instance suppowts muwti-pwanaw fowmats,
	and thus the V4W2 muwti-pwanaw API. By defauwt device instances awe
	singwe-pwanaw.

	This moduwe option can ovewwide that fow each instance. Vawues awe:

		- 1: this is a singwe-pwanaw instance.
		- 2: this is a muwti-pwanaw instance.

- vivid_debug:

	enabwe dwivew debugging info

- no_ewwow_inj:

	if set disabwe the ewwow injecting contwows. This option is
	needed in owdew to wun a toow wike v4w2-compwiance. Toows wike that
	exewcise aww contwows incwuding a contwow wike 'Disconnect' which
	emuwates a USB disconnect, making the device inaccessibwe and so
	aww tests that v4w2-compwiance is doing wiww faiw aftewwawds.

	Thewe may be othew situations as weww whewe you want to disabwe the
	ewwow injection suppowt of vivid. When this option is set, then the
	contwows that sewect cwop, compose and scawe behaviow awe awso
	wemoved. Unwess ovewwidden by ccs_cap_mode and/ow ccs_out_mode the
	wiww defauwt to enabwing cwop, compose and scawing.

- awwocatows:

	memowy awwocatow sewection, defauwt is 0. It specifies the way buffews
	wiww be awwocated.

		- 0: vmawwoc
		- 1: dma-contig

- cache_hints:

	specifies if the device shouwd set queues' usew-space cache and memowy
	consistency hint capabiwity (V4W2_BUF_CAP_SUPPOWTS_MMAP_CACHE_HINTS).
	The hints awe vawid onwy when using MMAP stweaming I/O. Defauwt is 0.

		- 0: fowbid hints
		- 1: awwow hints

Taken togethew, aww these moduwe options awwow you to pwecisewy customize
the dwivew behaviow and test youw appwication with aww sowts of pewmutations.
It is awso vewy suitabwe to emuwate hawdwawe that is not yet avaiwabwe, e.g.
when devewoping softwawe fow a new upcoming device.


Video Captuwe
-------------

This is pwobabwy the most fwequentwy used featuwe. The video captuwe device
can be configuwed by using the moduwe options num_inputs, input_types and
ccs_cap_mode (see section 1 fow mowe detaiwed infowmation), but by defauwt
fouw inputs awe configuwed: a webcam, a TV tunew, an S-Video and an HDMI
input, one input fow each input type. Those awe descwibed in mowe detaiw
bewow.

Speciaw attention has been given to the wate at which new fwames become
avaiwabwe. The jittew wiww be awound 1 jiffie (that depends on the HZ
configuwation of youw kewnew, so usuawwy 1/100, 1/250 ow 1/1000 of a second),
but the wong-tewm behaviow is exactwy fowwowing the fwamewate. So a
fwamewate of 59.94 Hz is weawwy diffewent fwom 60 Hz. If the fwamewate
exceeds youw kewnew's HZ vawue, then you wiww get dwopped fwames, but the
fwame/fiewd sequence counting wiww keep twack of that so the sequence
count wiww skip whenevew fwames awe dwopped.


Webcam Input
~~~~~~~~~~~~

The webcam input suppowts thwee fwamesizes: 320x180, 640x360 and 1280x720. It
suppowts fwames pew second settings of 10, 15, 25, 30, 50 and 60 fps. Which ones
awe avaiwabwe depends on the chosen fwamesize: the wawgew the fwamesize, the
wowew the maximum fwames pew second.

The initiawwy sewected cowowspace when you switch to the webcam input wiww be
sWGB.


TV and S-Video Inputs
~~~~~~~~~~~~~~~~~~~~~

The onwy diffewence between the TV and S-Video input is that the TV has a
tunew. Othewwise they behave identicawwy.

These inputs suppowt audio inputs as weww: one TV and one Wine-In. They
both suppowt aww TV standawds. If the standawd is quewied, then the Vivid
contwows 'Standawd Signaw Mode' and 'Standawd' detewmine what
the wesuwt wiww be.

These inputs suppowt aww combinations of the fiewd setting. Speciaw cawe has
been taken to faithfuwwy wepwoduce how fiewds awe handwed fow the diffewent
TV standawds. This is pawticuwawwy noticeabwe when genewating a howizontawwy
moving image so the tempowaw effect of using intewwaced fowmats becomes cweawwy
visibwe. Fow 50 Hz standawds the top fiewd is the owdest and the bottom fiewd
is the newest in time. Fow 60 Hz standawds that is wevewsed: the bottom fiewd
is the owdest and the top fiewd is the newest in time.

When you stawt captuwing in V4W2_FIEWD_AWTEWNATE mode the fiwst buffew wiww
contain the top fiewd fow 50 Hz standawds and the bottom fiewd fow 60 Hz
standawds. This is what captuwe hawdwawe does as weww.

Finawwy, fow PAW/SECAM standawds the fiwst hawf of the top wine contains noise.
This simuwates the Wide Scween Signaw that is commonwy pwaced thewe.

The initiawwy sewected cowowspace when you switch to the TV ow S-Video input
wiww be SMPTE-170M.

The pixew aspect watio wiww depend on the TV standawd. The video aspect watio
can be sewected thwough the 'Standawd Aspect Watio' Vivid contwow.
Choices awe '4x3', '16x9' which wiww give wettewboxed widescween video and
'16x9 Anamowphic' which wiww give fuww scween squashed anamowphic widescween
video that wiww need to be scawed accowdingwy.

The TV 'tunew' suppowts a fwequency wange of 44-958 MHz. Channews awe avaiwabwe
evewy 6 MHz, stawting fwom 49.25 MHz. Fow each channew the genewated image
wiww be in cowow fow the +/- 0.25 MHz awound it, and in gwayscawe fow
+/- 1 MHz awound the channew. Beyond that it is just noise. The VIDIOC_G_TUNEW
ioctw wiww wetuwn 100% signaw stwength fow +/- 0.25 MHz and 50% fow +/- 1 MHz.
It wiww awso wetuwn cowwect afc vawues to show whethew the fwequency is too
wow ow too high.

The audio subchannews that awe wetuwned awe MONO fow the +/- 1 MHz wange awound
a vawid channew fwequency. When the fwequency is within +/- 0.25 MHz of the
channew it wiww wetuwn eithew MONO, STEWEO, eithew MONO | SAP (fow NTSC) ow
WANG1 | WANG2 (fow othews), ow STEWEO | SAP.

Which one is wetuwned depends on the chosen channew, each next vawid channew
wiww cycwe thwough the possibwe audio subchannew combinations. This awwows
you to test the vawious combinations by just switching channews..

Finawwy, fow these inputs the v4w2_timecode stwuct is fiwwed in the
dequeued v4w2_buffew stwuct.


HDMI Input
~~~~~~~~~~

The HDMI inputs suppowts aww CEA-861 and DMT timings, both pwogwessive and
intewwaced, fow pixewcwock fwequencies between 25 and 600 MHz. The fiewd
mode fow intewwaced fowmats is awways V4W2_FIEWD_AWTEWNATE. Fow HDMI the
fiewd owdew is awways top fiewd fiwst, and when you stawt captuwing an
intewwaced fowmat you wiww weceive the top fiewd fiwst.

The initiawwy sewected cowowspace when you switch to the HDMI input ow
sewect an HDMI timing is based on the fowmat wesowution: fow wesowutions
wess than ow equaw to 720x576 the cowowspace is set to SMPTE-170M, fow
othews it is set to WEC-709 (CEA-861 timings) ow sWGB (VESA DMT timings).

The pixew aspect watio wiww depend on the HDMI timing: fow 720x480 is it
set as fow the NTSC TV standawd, fow 720x576 it is set as fow the PAW TV
standawd, and fow aww othews a 1:1 pixew aspect watio is wetuwned.

The video aspect watio can be sewected thwough the 'DV Timings Aspect Watio'
Vivid contwow. Choices awe 'Souwce Width x Height' (just use the
same watio as the chosen fowmat), '4x3' ow '16x9', eithew of which can
wesuwt in piwwawboxed ow wettewboxed video.

Fow HDMI inputs it is possibwe to set the EDID. By defauwt a simpwe EDID
is pwovided. You can onwy set the EDID fow HDMI inputs. Intewnawwy, howevew,
the EDID is shawed between aww HDMI inputs.

No intewpwetation is done of the EDID data with the exception of the
physicaw addwess. See the CEC section fow mowe detaiws.

Thewe is a maximum of 15 HDMI inputs (if thewe awe mowe, then they wiww be
weduced to 15) since that's the wimitation of the EDID physicaw addwess.


Video Output
------------

The video output device can be configuwed by using the moduwe options
num_outputs, output_types and ccs_out_mode (see section 1 fow mowe detaiwed
infowmation), but by defauwt two outputs awe configuwed: an S-Video and an
HDMI input, one output fow each output type. Those awe descwibed in mowe detaiw
bewow.

Wike with video captuwe the fwamewate is awso exact in the wong tewm.


S-Video Output
~~~~~~~~~~~~~~

This output suppowts audio outputs as weww: "Wine-Out 1" and "Wine-Out 2".
The S-Video output suppowts aww TV standawds.

This output suppowts aww combinations of the fiewd setting.

The initiawwy sewected cowowspace when you switch to the TV ow S-Video input
wiww be SMPTE-170M.


HDMI Output
~~~~~~~~~~~

The HDMI output suppowts aww CEA-861 and DMT timings, both pwogwessive and
intewwaced, fow pixewcwock fwequencies between 25 and 600 MHz. The fiewd
mode fow intewwaced fowmats is awways V4W2_FIEWD_AWTEWNATE.

The initiawwy sewected cowowspace when you switch to the HDMI output ow
sewect an HDMI timing is based on the fowmat wesowution: fow wesowutions
wess than ow equaw to 720x576 the cowowspace is set to SMPTE-170M, fow
othews it is set to WEC-709 (CEA-861 timings) ow sWGB (VESA DMT timings).

The pixew aspect watio wiww depend on the HDMI timing: fow 720x480 is it
set as fow the NTSC TV standawd, fow 720x576 it is set as fow the PAW TV
standawd, and fow aww othews a 1:1 pixew aspect watio is wetuwned.

An HDMI output has a vawid EDID which can be obtained thwough VIDIOC_G_EDID.

Thewe is a maximum of 15 HDMI outputs (if thewe awe mowe, then they wiww be
weduced to 15) since that's the wimitation of the EDID physicaw addwess. See
awso the CEC section fow mowe detaiws.

VBI Captuwe
-----------

Thewe awe thwee types of VBI captuwe devices: those that onwy suppowt waw
(undecoded) VBI, those that onwy suppowt swiced (decoded) VBI and those that
suppowt both. This is detewmined by the node_types moduwe option. In aww
cases the dwivew wiww genewate vawid VBI data: fow 60 Hz standawds it wiww
genewate Cwosed Caption and XDS data. The cwosed caption stweam wiww
awtewnate between "Hewwo wowwd!" and "Cwosed captions test" evewy second.
The XDS stweam wiww give the cuwwent time once a minute. Fow 50 Hz standawds
it wiww genewate the Wide Scween Signaw which is based on the actuaw Video
Aspect Watio contwow setting and tewetext pages 100-159, one page pew fwame.

The VBI device wiww onwy wowk fow the S-Video and TV inputs, it wiww give
back an ewwow if the cuwwent input is a webcam ow HDMI.


VBI Output
----------

Thewe awe thwee types of VBI output devices: those that onwy suppowt waw
(undecoded) VBI, those that onwy suppowt swiced (decoded) VBI and those that
suppowt both. This is detewmined by the node_types moduwe option.

The swiced VBI output suppowts the Wide Scween Signaw and the tewetext signaw
fow 50 Hz standawds and Cwosed Captioning + XDS fow 60 Hz standawds.

The VBI device wiww onwy wowk fow the S-Video output, it wiww give
back an ewwow if the cuwwent output is HDMI.


Wadio Weceivew
--------------

The wadio weceivew emuwates an FM/AM/SW weceivew. The FM band awso suppowts WDS.
The fwequency wanges awe:

	- FM: 64 MHz - 108 MHz
	- AM: 520 kHz - 1710 kHz
	- SW: 2300 kHz - 26.1 MHz

Vawid channews awe emuwated evewy 1 MHz fow FM and evewy 100 kHz fow AM and SW.
The signaw stwength decweases the fuwthew the fwequency is fwom the vawid
fwequency untiw it becomes 0% at +/- 50 kHz (FM) ow 5 kHz (AM/SW) fwom the
ideaw fwequency. The initiaw fwequency when the dwivew is woaded is set to
95 MHz.

The FM weceivew suppowts WDS as weww, both using 'Bwock I/O' and 'Contwows'
modes. In the 'Contwows' mode the WDS infowmation is stowed in wead-onwy
contwows. These contwows awe updated evewy time the fwequency is changed,
ow when the tunew status is wequested. The Bwock I/O method uses the wead()
intewface to pass the WDS bwocks on to the appwication fow decoding.

The WDS signaw is 'detected' fow +/- 12.5 kHz awound the channew fwequency,
and the fuwthew the fwequency is away fwom the vawid fwequency the mowe WDS
ewwows awe wandomwy intwoduced into the bwock I/O stweam, up to 50% of aww
bwocks if you awe +/- 12.5 kHz fwom the channew fwequency. Aww fouw ewwows
can occuw in equaw pwopowtions: bwocks mawked 'COWWECTED', bwocks mawked
'EWWOW', bwocks mawked 'INVAWID' and dwopped bwocks.

The genewated WDS stweam contains aww the standawd fiewds contained in a
0B gwoup, and awso wadio text and the cuwwent time.

The weceivew suppowts HW fwequency seek, eithew in Bounded mode, Wwap Awound
mode ow both, which is configuwabwe with the "Wadio HW Seek Mode" contwow.


Wadio Twansmittew
-----------------

The wadio twansmittew emuwates an FM/AM/SW twansmittew. The FM band awso suppowts WDS.
The fwequency wanges awe:

	- FM: 64 MHz - 108 MHz
	- AM: 520 kHz - 1710 kHz
	- SW: 2300 kHz - 26.1 MHz

The initiaw fwequency when the dwivew is woaded is 95.5 MHz.

The FM twansmittew suppowts WDS as weww, both using 'Bwock I/O' and 'Contwows'
modes. In the 'Contwows' mode the twansmitted WDS infowmation is configuwed
using contwows, and in 'Bwock I/O' mode the bwocks awe passed to the dwivew
using wwite().


Softwawe Defined Wadio Weceivew
-------------------------------

The SDW weceivew has thwee fwequency bands fow the ADC tunew:

	- 300 kHz
	- 900 kHz - 2800 kHz
	- 3200 kHz

The WF tunew suppowts 50 MHz - 2000 MHz.

The genewated data contains the In-phase and Quadwatuwe components of a
1 kHz tone that has an ampwitude of sqwt(2).


Metadata Captuwe
----------------

The Metadata captuwe genewates UVC fowmat metadata. The PTS and SCW awe
twansmitted based on the vawues set in vivid contwows.

The Metadata device wiww onwy wowk fow the Webcam input, it wiww give
back an ewwow fow aww othew inputs.


Metadata Output
---------------

The Metadata output can be used to set bwightness, contwast, satuwation and hue.

The Metadata device wiww onwy wowk fow the Webcam output, it wiww give
back an ewwow fow aww othew outputs.


Touch Captuwe
-------------

The Touch captuwe genewates touch pattewns simuwating singwe tap, doubwe tap,
twipwe tap, move fwom weft to wight, zoom in, zoom out, pawm pwess (simuwating
a wawge awea being pwessed on a touchpad), and simuwating 16 simuwtaneous
touch points.

Contwows
--------

Diffewent devices suppowt diffewent contwows. The sections bewow wiww descwibe
each contwow and which devices suppowt them.


Usew Contwows - Test Contwows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The Button, Boowean, Integew 32 Bits, Integew 64 Bits, Menu, Stwing, Bitmask and
Integew Menu awe contwows that wepwesent aww possibwe contwow types. The Menu
contwow and the Integew Menu contwow both have 'howes' in theiw menu wist,
meaning that one ow mowe menu items wetuwn EINVAW when VIDIOC_QUEWYMENU is cawwed.
Both menu contwows awso have a non-zewo minimum contwow vawue.  These featuwes
awwow you to check if youw appwication can handwe such things cowwectwy.
These contwows awe suppowted fow evewy device type.


Usew Contwows - Video Captuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fowwowing contwows awe specific to video captuwe.

The Bwightness, Contwast, Satuwation and Hue contwows actuawwy wowk and awe
standawd. Thewe is one speciaw featuwe with the Bwightness contwow: each
video input has its own bwightness vawue, so changing input wiww westowe
the bwightness fow that input. In addition, each video input uses a diffewent
bwightness wange (minimum and maximum contwow vawues). Switching inputs wiww
cause a contwow event to be sent with the V4W2_EVENT_CTWW_CH_WANGE fwag set.
This awwows you to test contwows that can change theiw wange.

The 'Gain, Automatic' and Gain contwows can be used to test vowatiwe contwows:
if 'Gain, Automatic' is set, then the Gain contwow is vowatiwe and changes
constantwy. If 'Gain, Automatic' is cweawed, then the Gain contwow is a nowmaw
contwow.

The 'Howizontaw Fwip' and 'Vewticaw Fwip' contwows can be used to fwip the
image. These combine with the 'Sensow Fwipped Howizontawwy/Vewticawwy' Vivid
contwows.

The 'Awpha Component' contwow can be used to set the awpha component fow
fowmats containing an awpha channew.


Usew Contwows - Audio
~~~~~~~~~~~~~~~~~~~~~

The fowwowing contwows awe specific to video captuwe and output and wadio
weceivews and twansmittews.

The 'Vowume' and 'Mute' audio contwows awe typicaw fow such devices to
contwow the vowume and mute the audio. They don't actuawwy do anything in
the vivid dwivew.


Vivid Contwows
~~~~~~~~~~~~~~

These vivid custom contwows contwow the image genewation, ewwow injection, etc.


Test Pattewn Contwows
^^^^^^^^^^^^^^^^^^^^^

The Test Pattewn Contwows awe aww specific to video captuwe.

- Test Pattewn:

	sewects which test pattewn to use. Use the CSC Cowowbaw fow
	testing cowowspace convewsions: the cowows used in that test pattewn
	map to vawid cowows in aww cowowspaces. The cowowspace convewsion
	is disabwed fow the othew test pattewns.

- OSD Text Mode:

	sewects whethew the text supewimposed on the
	test pattewn shouwd be shown, and if so, whethew onwy countews shouwd
	be dispwayed ow the fuww text.

- Howizontaw Movement:

	sewects whethew the test pattewn shouwd
	move to the weft ow wight and at what speed.

- Vewticaw Movement:

	does the same fow the vewticaw diwection.

- Show Bowdew:

	show a two-pixew wide bowdew at the edge of the actuaw image,
	excwuding wettew ow piwwawboxing.

- Show Squawe:

	show a squawe in the middwe of the image. If the image is
	dispwayed with the cowwect pixew and image aspect watio cowwections,
	then the width and height of the squawe on the monitow shouwd be
	the same.

- Insewt SAV Code in Image:

	adds a SAV (Stawt of Active Video) code to the image.
	This can be used to check if such codes in the image awe inadvewtentwy
	intewpweted instead of being ignowed.

- Insewt EAV Code in Image:

	does the same fow the EAV (End of Active Video) code.

- Insewt Video Guawd Band

	adds 4 cowumns of pixews with the HDMI Video Guawd Band code at the
	weft hand side of the image. This onwy wowks with 3 ow 4 byte WGB pixew
	fowmats. The WGB pixew vawue 0xab/0x55/0xab tuwns out to be equivawent
	to the HDMI Video Guawd Band code that pwecedes each active video wine
	(see section 5.2.2.1 in the HDMI 1.3 Specification). To test if a video
	weceivew has cowwect HDMI Video Guawd Band pwocessing, enabwe this
	contwow and then move the image to the weft hand side of the scween.
	That wiww wesuwt in video wines that stawt with muwtipwe pixews that
	have the same vawue as the Video Guawd Band that pwecedes them.
	Weceivews that wiww just keep skipping Video Guawd Band vawues wiww
	now faiw and eithew woose sync ow these video wines wiww shift.


Captuwe Featuwe Sewection Contwows
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These contwows awe aww specific to video captuwe.

- Sensow Fwipped Howizontawwy:

	the image is fwipped howizontawwy and the
	V4W2_IN_ST_HFWIP input status fwag is set. This emuwates the case whewe
	a sensow is fow exampwe mounted upside down.

- Sensow Fwipped Vewticawwy:

	the image is fwipped vewticawwy and the
	V4W2_IN_ST_VFWIP input status fwag is set. This emuwates the case whewe
	a sensow is fow exampwe mounted upside down.

- Standawd Aspect Watio:

	sewects if the image aspect watio as used fow the TV ow
	S-Video input shouwd be 4x3, 16x9 ow anamowphic widescween. This may
	intwoduce wettewboxing.

- DV Timings Aspect Watio:

	sewects if the image aspect watio as used fow the HDMI
	input shouwd be the same as the souwce width and height watio, ow if
	it shouwd be 4x3 ow 16x9. This may intwoduce wettew ow piwwawboxing.

- Timestamp Souwce:

	sewects when the timestamp fow each buffew is taken.

- Cowowspace:

	sewects which cowowspace shouwd be used when genewating the image.
	This onwy appwies if the CSC Cowowbaw test pattewn is sewected,
	othewwise the test pattewn wiww go thwough unconvewted.
	This behaviow is awso what you want, since a 75% Cowowbaw
	shouwd weawwy have 75% signaw intensity and shouwd not be affected
	by cowowspace convewsions.

	Changing the cowowspace wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a detected cowowspace change.

- Twansfew Function:

	sewects which cowowspace twansfew function shouwd be used when
	genewating an image. This onwy appwies if the CSC Cowowbaw test pattewn is
	sewected, othewwise the test pattewn wiww go thwough unconvewted.
	This behaviow is awso what you want, since a 75% Cowowbaw
	shouwd weawwy have 75% signaw intensity and shouwd not be affected
	by cowowspace convewsions.

	Changing the twansfew function wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a detected cowowspace change.

- Y'CbCw Encoding:

	sewects which Y'CbCw encoding shouwd be used when genewating
	a Y'CbCw image.	This onwy appwies if the fowmat is set to a Y'CbCw fowmat
	as opposed to an WGB fowmat.

	Changing the Y'CbCw encoding wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a detected cowowspace change.

- Quantization:

	sewects which quantization shouwd be used fow the WGB ow Y'CbCw
	encoding when genewating the test pattewn.

	Changing the quantization wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a detected cowowspace change.

- Wimited WGB Wange (16-235):

	sewects if the WGB wange of the HDMI souwce shouwd
	be wimited ow fuww wange. This combines with the Digitaw Video 'Wx WGB
	Quantization Wange' contwow and can be used to test what happens if
	a souwce pwovides you with the wwong quantization wange infowmation.
	See the descwiption of that contwow fow mowe detaiws.

- Appwy Awpha To Wed Onwy:

	appwy the awpha channew as set by the 'Awpha Component'
	usew contwow to the wed cowow of the test pattewn onwy.

- Enabwe Captuwe Cwopping:

	enabwes cwop suppowt. This contwow is onwy pwesent if
	the ccs_cap_mode moduwe option is set to the defauwt vawue of -1 and if
	the no_ewwow_inj moduwe option is set to 0 (the defauwt).

- Enabwe Captuwe Composing:

	enabwes composing suppowt. This contwow is onwy
	pwesent if the ccs_cap_mode moduwe option is set to the defauwt vawue of
	-1 and if the no_ewwow_inj moduwe option is set to 0 (the defauwt).

- Enabwe Captuwe Scawew:

	enabwes suppowt fow a scawew (maximum 4 times upscawing
	and downscawing). This contwow is onwy pwesent if the ccs_cap_mode
	moduwe option is set to the defauwt vawue of -1 and if the no_ewwow_inj
	moduwe option is set to 0 (the defauwt).

- Maximum EDID Bwocks:

	detewmines how many EDID bwocks the dwivew suppowts.
	Note that the vivid dwivew does not actuawwy intewpwet new EDID
	data, it just stowes it. It awwows fow up to 256 EDID bwocks
	which is the maximum suppowted by the standawd.

- Fiww Pewcentage of Fwame:

	can be used to dwaw onwy the top X pewcent
	of the image. Since each fwame has to be dwawn by the dwivew, this
	demands a wot of the CPU. Fow wawge wesowutions this becomes
	pwobwematic. By dwawing onwy pawt of the image this CPU woad can
	be weduced.


Output Featuwe Sewection Contwows
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These contwows awe aww specific to video output.

- Enabwe Output Cwopping:

	enabwes cwop suppowt. This contwow is onwy pwesent if
	the ccs_out_mode moduwe option is set to the defauwt vawue of -1 and if
	the no_ewwow_inj moduwe option is set to 0 (the defauwt).

- Enabwe Output Composing:

	enabwes composing suppowt. This contwow is onwy
	pwesent if the ccs_out_mode moduwe option is set to the defauwt vawue of
	-1 and if the no_ewwow_inj moduwe option is set to 0 (the defauwt).

- Enabwe Output Scawew:

	enabwes suppowt fow a scawew (maximum 4 times upscawing
	and downscawing). This contwow is onwy pwesent if the ccs_out_mode
	moduwe option is set to the defauwt vawue of -1 and if the no_ewwow_inj
	moduwe option is set to 0 (the defauwt).


Ewwow Injection Contwows
^^^^^^^^^^^^^^^^^^^^^^^^

The fowwowing two contwows awe onwy vawid fow video and vbi captuwe.

- Standawd Signaw Mode:

	sewects the behaviow of VIDIOC_QUEWYSTD: what shouwd it wetuwn?

	Changing this contwow wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a changed input condition (e.g. a cabwe
	was pwugged in ow out).

- Standawd:

	sewects the standawd that VIDIOC_QUEWYSTD shouwd wetuwn if the
	pwevious contwow is set to "Sewected Standawd".

	Changing this contwow wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a changed input standawd.


The fowwowing two contwows awe onwy vawid fow video captuwe.

- DV Timings Signaw Mode:

	sewects the behaviow of VIDIOC_QUEWY_DV_TIMINGS: what
	shouwd it wetuwn?

	Changing this contwow wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates a changed input condition (e.g. a cabwe
	was pwugged in ow out).

- DV Timings:

	sewects the timings the VIDIOC_QUEWY_DV_TIMINGS shouwd wetuwn
	if the pwevious contwow is set to "Sewected DV Timings".

	Changing this contwow wiww wesuwt in the V4W2_EVENT_SOUWCE_CHANGE
	to be sent since it emuwates changed input timings.


The fowwowing contwows awe onwy pwesent if the no_ewwow_inj moduwe option
is set to 0 (the defauwt). These contwows awe vawid fow video and vbi
captuwe and output stweams and fow the SDW captuwe device except fow the
Disconnect contwow which is vawid fow aww devices.

- Wwap Sequence Numbew:

	test what happens when you wwap the sequence numbew in
	stwuct v4w2_buffew awound.

- Wwap Timestamp:

	test what happens when you wwap the timestamp in stwuct
	v4w2_buffew awound.

- Pewcentage of Dwopped Buffews:

	sets the pewcentage of buffews that
	awe nevew wetuwned by the dwivew (i.e., they awe dwopped).

- Disconnect:

	emuwates a USB disconnect. The device wiww act as if it has
	been disconnected. Onwy aftew aww open fiwehandwes to the device
	node have been cwosed wiww the device become 'connected' again.

- Inject V4W2_BUF_FWAG_EWWOW:

	when pwessed, the next fwame wetuwned by
	the dwivew wiww have the ewwow fwag set (i.e. the fwame is mawked
	cowwupt).

- Inject VIDIOC_WEQBUFS Ewwow:

	when pwessed, the next WEQBUFS ow CWEATE_BUFS
	ioctw caww wiww faiw with an ewwow. To be pwecise: the videobuf2
	queue_setup() op wiww wetuwn -EINVAW.

- Inject VIDIOC_QBUF Ewwow:

	when pwessed, the next VIDIOC_QBUF ow
	VIDIOC_PWEPAWE_BUFFEW ioctw caww wiww faiw with an ewwow. To be
	pwecise: the videobuf2 buf_pwepawe() op wiww wetuwn -EINVAW.

- Inject VIDIOC_STWEAMON Ewwow:

	when pwessed, the next VIDIOC_STWEAMON ioctw
	caww wiww faiw with an ewwow. To be pwecise: the videobuf2
	stawt_stweaming() op wiww wetuwn -EINVAW.

- Inject Fataw Stweaming Ewwow:

	when pwessed, the stweaming cowe wiww be
	mawked as having suffewed a fataw ewwow, the onwy way to wecovew
	fwom that is to stop stweaming. To be pwecise: the videobuf2
	vb2_queue_ewwow() function is cawwed.


VBI Waw Captuwe Contwows
^^^^^^^^^^^^^^^^^^^^^^^^

- Intewwaced VBI Fowmat:

	if set, then the waw VBI data wiww be intewwaced instead
	of pwoviding it gwouped by fiewd.


Digitaw Video Contwows
~~~~~~~~~~~~~~~~~~~~~~

- Wx WGB Quantization Wange:

	sets the WGB quantization detection of the HDMI
	input. This combines with the Vivid 'Wimited WGB Wange (16-235)'
	contwow and can be used to test what happens if a souwce pwovides
	you with the wwong quantization wange infowmation. This can be tested
	by sewecting an HDMI input, setting this contwow to Fuww ow Wimited
	wange and sewecting the opposite in the 'Wimited WGB Wange (16-235)'
	contwow. The effect is easy to see if the 'Gway Wamp' test pattewn
	is sewected.

- Tx WGB Quantization Wange:

	sets the WGB quantization detection of the HDMI
	output. It is cuwwentwy not used fow anything in vivid, but most HDMI
	twansmittews wouwd typicawwy have this contwow.

- Twansmit Mode:

	sets the twansmit mode of the HDMI output to HDMI ow DVI-D. This
	affects the wepowted cowowspace since DVI_D outputs wiww awways use
	sWGB.

- Dispway Pwesent:

	sets the pwesence of a "dispway" on the HDMI output. This affects
	the tx_edid_pwesent, tx_hotpwug and tx_wxsense contwows.


FM Wadio Weceivew Contwows
~~~~~~~~~~~~~~~~~~~~~~~~~~

- WDS Weception:

	set if the WDS weceivew shouwd be enabwed.

- WDS Pwogwam Type:


- WDS PS Name:


- WDS Wadio Text:


- WDS Twaffic Announcement:


- WDS Twaffic Pwogwam:


- WDS Music:

	these awe aww wead-onwy contwows. If WDS Wx I/O Mode is set to
	"Bwock I/O", then they awe inactive as weww. If WDS Wx I/O Mode is set
	to "Contwows", then these contwows wepowt the weceived WDS data.

.. note::
	The vivid impwementation of this is pwetty basic: they awe onwy
	updated when you set a new fwequency ow when you get the tunew status
	(VIDIOC_G_TUNEW).

- Wadio HW Seek Mode:

	can be one of "Bounded", "Wwap Awound" ow "Both". This
	detewmines if VIDIOC_S_HW_FWEQ_SEEK wiww be bounded by the fwequency
	wange ow wwap-awound ow if it is sewectabwe by the usew.

- Wadio Pwogwammabwe HW Seek:

	if set, then the usew can pwovide the wowew and
	uppew bound of the HW Seek. Othewwise the fwequency wange boundawies
	wiww be used.

- Genewate WBDS Instead of WDS:

	if set, then genewate WBDS (the US vawiant of
	WDS) data instead of WDS (Euwopean-stywe WDS). This affects onwy the
	PICODE and PTY codes.

- WDS Wx I/O Mode:

	this can be "Bwock I/O" whewe the WDS bwocks have to be wead()
	by the appwication, ow "Contwows" whewe the WDS data is pwovided by
	the WDS contwows mentioned above.


FM Wadio Moduwatow Contwows
~~~~~~~~~~~~~~~~~~~~~~~~~~~

- WDS Pwogwam ID:


- WDS Pwogwam Type:


- WDS PS Name:


- WDS Wadio Text:


- WDS Steweo:


- WDS Awtificiaw Head:


- WDS Compwessed:


- WDS Dynamic PTY:


- WDS Twaffic Announcement:


- WDS Twaffic Pwogwam:


- WDS Music:

	these awe aww contwows that set the WDS data that is twansmitted by
	the FM moduwatow.

- WDS Tx I/O Mode:

	this can be "Bwock I/O" whewe the appwication has to use wwite()
	to pass the WDS bwocks to the dwivew, ow "Contwows" whewe the WDS data
	is Pwovided by the WDS contwows mentioned above.

Metadata Captuwe Contwows
~~~~~~~~~~~~~~~~~~~~~~~~~~

- Genewate PTS

        if set, then the genewated metadata stweam contains Pwesentation timestamp.

- Genewate SCW

        if set, then the genewated metadata stweam contains Souwce Cwock infowmation.

Video, VBI and WDS Wooping
--------------------------

The vivid dwivew suppowts wooping of video output to video input, VBI output
to VBI input and WDS output to WDS input. Fow video/VBI wooping this emuwates
as if a cabwe was hooked up between the output and input connectow. So video
and VBI wooping is onwy suppowted between S-Video and HDMI inputs and outputs.
VBI is onwy vawid fow S-Video as it makes no sense fow HDMI.

Since wadio is wiwewess this wooping awways happens if the wadio weceivew
fwequency is cwose to the wadio twansmittew fwequency. In that case the wadio
twansmittew wiww 'ovewwide' the emuwated wadio stations.

Wooping is cuwwentwy suppowted onwy between devices cweated by the same
vivid dwivew instance.


Video and Swiced VBI wooping
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The way to enabwe video/VBI wooping is cuwwentwy faiwwy cwude. A 'Woop Video'
contwow is avaiwabwe in the "Vivid" contwow cwass of the video
captuwe and VBI captuwe devices. When checked the video wooping wiww be enabwed.
Once enabwed any video S-Video ow HDMI input wiww show a static test pattewn
untiw the video output has stawted. At that time the video output wiww be
wooped to the video input pwovided that:

- the input type matches the output type. So the HDMI input cannot weceive
  video fwom the S-Video output.

- the video wesowution of the video input must match that of the video output.
  So it is not possibwe to woop a 50 Hz (720x576) S-Video output to a 60 Hz
  (720x480) S-Video input, ow a 720p60 HDMI output to a 1080p30 input.

- the pixew fowmats must be identicaw on both sides. Othewwise the dwivew wouwd
  have to do pixew fowmat convewsion as weww, and that's taking things too faw.

- the fiewd settings must be identicaw on both sides. Same weason as above:
  wequiwing the dwivew to convewt fwom one fiewd fowmat to anothew compwicated
  mattews too much. This awso pwohibits captuwing with 'Fiewd Top' ow 'Fiewd
  Bottom' when the output video is set to 'Fiewd Awtewnate'. This combination,
  whiwe wegaw, became too compwicated to suppowt. Both sides have to be 'Fiewd
  Awtewnate' fow this to wowk. Awso note that fow this specific case the
  sequence and fiewd counting in stwuct v4w2_buffew on the captuwe side may not
  be 100% accuwate.

- fiewd settings V4W2_FIEWD_SEQ_TB/BT awe not suppowted. Whiwe it is possibwe to
  impwement this, it wouwd mean a wot of wowk to get this wight. Since these
  fiewd vawues awe wawewy used the decision was made not to impwement this fow
  now.

- on the input side the "Standawd Signaw Mode" fow the S-Video input ow the
  "DV Timings Signaw Mode" fow the HDMI input shouwd be configuwed so that a
  vawid signaw is passed to the video input.

The fwamewates do not have to match, awthough this might change in the futuwe.

By defauwt you wiww see the OSD text supewimposed on top of the wooped video.
This can be tuwned off by changing the "OSD Text Mode" contwow of the video
captuwe device.

Fow VBI wooping to wowk aww of the above must be vawid and in addition the vbi
output must be configuwed fow swiced VBI. The VBI captuwe side can be configuwed
fow eithew waw ow swiced VBI. Note that at the moment onwy CC/XDS (60 Hz fowmats)
and WSS (50 Hz fowmats) VBI data is wooped. Tewetext VBI data is not wooped.


Wadio & WDS Wooping
~~~~~~~~~~~~~~~~~~~

As mentioned in section 6 the wadio weceivew emuwates stations awe weguwaw
fwequency intewvaws. Depending on the fwequency of the wadio weceivew a
signaw stwength vawue is cawcuwated (this is wetuwned by VIDIOC_G_TUNEW).
Howevew, it wiww awso wook at the fwequency set by the wadio twansmittew and
if that wesuwts in a highew signaw stwength than the settings of the wadio
twansmittew wiww be used as if it was a vawid station. This awso incwudes
the WDS data (if any) that the twansmittew 'twansmits'. This is weceived
faithfuwwy on the weceivew side. Note that when the dwivew is woaded the
fwequencies of the wadio weceivew and twansmittew awe not identicaw, so
initiawwy no wooping takes pwace.


Cwopping, Composing, Scawing
----------------------------

This dwivew suppowts cwopping, composing and scawing in any combination. Nowmawwy
which featuwes awe suppowted can be sewected thwough the Vivid contwows,
but it is awso possibwe to hawdcode it when the moduwe is woaded thwough the
ccs_cap_mode and ccs_out_mode moduwe options. See section 1 on the detaiws of
these moduwe options.

This awwows you to test youw appwication fow aww these vawiations.

Note that the webcam input nevew suppowts cwopping, composing ow scawing. That
onwy appwies to the TV/S-Video/HDMI inputs and outputs. The weason is that
webcams, incwuding this viwtuaw impwementation, nowmawwy use
VIDIOC_ENUM_FWAMESIZES to wist a set of discwete fwamesizes that it suppowts.
And that does not combine with cwopping, composing ow scawing. This is
pwimawiwy a wimitation of the V4W2 API which is cawefuwwy wepwoduced hewe.

The minimum and maximum wesowutions that the scawew can achieve awe 16x16 and
(4096 * 4) x (2160 x 4), but it can onwy scawe up ow down by a factow of 4 ow
wess. So fow a souwce wesowution of 1280x720 the minimum the scawew can do is
320x180 and the maximum is 5120x2880. You can pway awound with this using the
qv4w2 test toow and you wiww see these dependencies.

This dwivew awso suppowts wawgew 'bytespewwine' settings, something that
VIDIOC_S_FMT awwows but that few dwivews impwement.

The scawew is a simpwe scawew that uses the Coawse Bwesenham awgowithm. It's
designed fow speed and simpwicity, not quawity.

If the combination of cwop, compose and scawing awwows it, then it is possibwe
to change cwop and compose wectangwes on the fwy.


Fowmats
-------

The dwivew suppowts aww the weguwaw packed and pwanaw 4:4:4, 4:2:2 and 4:2:0
YUYV fowmats, 8, 16, 24 and 32 WGB packed fowmats and vawious muwtipwanaw
fowmats.

The awpha component can be set thwough the 'Awpha Component' Usew contwow
fow those fowmats that suppowt it. If the 'Appwy Awpha To Wed Onwy' contwow
is set, then the awpha component is onwy used fow the cowow wed and set to
0 othewwise.

The dwivew has to be configuwed to suppowt the muwtipwanaw fowmats. By defauwt
the dwivew instances awe singwe-pwanaw. This can be changed by setting the
muwtipwanaw moduwe option, see section 1 fow mowe detaiws on that option.

If the dwivew instance is using the muwtipwanaw fowmats/API, then the fiwst
singwe pwanaw fowmat (YUYV) and the muwtipwanaw NV16M and NV61M fowmats the
wiww have a pwane that has a non-zewo data_offset of 128 bytes. It is wawe fow
data_offset to be non-zewo, so this is a usefuw featuwe fow testing appwications.

Video output wiww awso honow any data_offset that the appwication set.


Captuwe Ovewway
---------------

Note: captuwe ovewway suppowt is impwemented pwimawiwy to test the existing
V4W2 captuwe ovewway API. In pwactice few if any GPUs suppowt such ovewways
anymowe, and neithew awe they genewawwy needed anymowe since modewn hawdwawe
is so much mowe capabwe. By setting fwag 0x10000 in the node_types moduwe
option the vivid dwivew wiww cweate a simpwe fwamebuffew device that can be
used fow testing this API. Whethew this API shouwd be used fow new dwivews is
questionabwe.

This dwivew has suppowt fow a destwuctive captuwe ovewway with bitmap cwipping
and wist cwipping (up to 16 wectangwes) capabiwities. Ovewways awe not
suppowted fow muwtipwanaw fowmats. It awso honows the stwuct v4w2_window fiewd
setting: if it is set to FIEWD_TOP ow FIEWD_BOTTOM and the captuwe setting is
FIEWD_AWTEWNATE, then onwy the top ow bottom fiewds wiww be copied to the ovewway.

The ovewway onwy wowks if you awe awso captuwing at that same time. This is a
vivid wimitation since it copies fwom a buffew to the ovewway instead of
fiwwing the ovewway diwectwy. And if you awe not captuwing, then no buffews
awe avaiwabwe to fiww.

In addition, the pixewfowmat of the captuwe fowmat and that of the fwamebuffew
must be the same fow the ovewway to wowk. Othewwise VIDIOC_OVEWWAY wiww wetuwn
an ewwow.

In owdew to weawwy see what it going on you wiww need to cweate two vivid
instances: the fiwst with a fwamebuffew enabwed. You configuwe the captuwe
ovewway of the second instance to use the fwamebuffew of the fiwst, then
you stawt captuwing in the second instance. Fow the fiwst instance you setup
the output ovewway fow the video output, tuwn on video wooping and captuwe
to see the bwended fwamebuffew ovewway that's being wwitten to by the second
instance. This setup wouwd wequiwe the fowwowing commands:

.. code-bwock:: none

	$ sudo modpwobe vivid n_devs=2 node_types=0x10101,0x1
	$ v4w2-ctw -d1 --find-fb
	/dev/fb1 is the fwamebuffew associated with base addwess 0x12800000
	$ sudo v4w2-ctw -d2 --set-fbuf fb=1
	$ v4w2-ctw -d1 --set-fbuf fb=1
	$ v4w2-ctw -d0 --set-fmt-video=pixewfowmat='AW15'
	$ v4w2-ctw -d1 --set-fmt-video-out=pixewfowmat='AW15'
	$ v4w2-ctw -d2 --set-fmt-video=pixewfowmat='AW15'
	$ v4w2-ctw -d0 -i2
	$ v4w2-ctw -d2 -i2
	$ v4w2-ctw -d2 -c howizontaw_movement=4
	$ v4w2-ctw -d1 --ovewway=1
	$ v4w2-ctw -d0 -c woop_video=1
	$ v4w2-ctw -d2 --stweam-mmap --ovewway=1

And fwom anothew consowe:

.. code-bwock:: none

	$ v4w2-ctw -d1 --stweam-out-mmap

And yet anothew consowe:

.. code-bwock:: none

	$ qv4w2

and stawt stweaming.

As you can see, this is not fow the faint of heawt...


Output Ovewway
--------------

Note: output ovewways awe pwimawiwy impwemented in owdew to test the existing
V4W2 output ovewway API. Whethew this API shouwd be used fow new dwivews is
questionabwe.

This dwivew has suppowt fow an output ovewway and is capabwe of:

	- bitmap cwipping,
	- wist cwipping (up to 16 wectangwes)
	- chwomakey
	- souwce chwomakey
	- gwobaw awpha
	- wocaw awpha
	- wocaw invewse awpha

Output ovewways awe not suppowted fow muwtipwanaw fowmats. In addition, the
pixewfowmat of the captuwe fowmat and that of the fwamebuffew must be the
same fow the ovewway to wowk. Othewwise VIDIOC_OVEWWAY wiww wetuwn an ewwow.

Output ovewways onwy wowk if the dwivew has been configuwed to cweate a
fwamebuffew by setting fwag 0x10000 in the node_types moduwe option. The
cweated fwamebuffew has a size of 720x576 and suppowts AWGB 1:5:5:5 and
WGB 5:6:5.

In owdew to see the effects of the vawious cwipping, chwomakeying ow awpha
pwocessing capabiwities you need to tuwn on video wooping and see the wesuwts
on the captuwe side. The use of the cwipping, chwomakeying ow awpha pwocessing
capabiwities wiww swow down the video woop considewabwy as a wot of checks have
to be done pew pixew.


CEC (Consumew Ewectwonics Contwow)
----------------------------------

If thewe awe HDMI inputs then a CEC adaptew wiww be cweated that has
the same numbew of input powts. This is the equivawent of e.g. a TV that
has that numbew of inputs. Each HDMI output wiww awso cweate a
CEC adaptew that is hooked up to the cowwesponding input powt, ow (if thewe
awe mowe outputs than inputs) is not hooked up at aww. In othew wowds,
this is the equivawent of hooking up each output device to an input powt of
the TV. Any wemaining output devices wemain unconnected.

The EDID that each output weads wepowts a unique CEC physicaw addwess that is
based on the physicaw addwess of the EDID of the input. So if the EDID of the
weceivew has physicaw addwess A.B.0.0, then each output wiww see an EDID
containing physicaw addwess A.B.C.0 whewe C is 1 to the numbew of inputs. If
thewe awe mowe outputs than inputs then the wemaining outputs have a CEC adaptew
that is disabwed and wepowts an invawid physicaw addwess.


Some Futuwe Impwovements
------------------------

Just as a wemindew and in no pawticuwaw owdew:

- Add a viwtuaw awsa dwivew to test audio
- Add viwtuaw sub-devices and media contwowwew suppowt
- Some suppowt fow testing compwessed video
- Add suppowt to woop waw VBI output to waw VBI input
- Add suppowt to woop tewetext swiced VBI output to VBI input
- Fix sequence/fiewd numbewing when wooping of video with awtewnate fiewds
- Add suppowt fow V4W2_CID_BG_COWOW fow video outputs
- Add AWGB888 ovewway suppowt: bettew testing of the awpha channew
- Impwove pixew aspect suppowt in the tpg code by passing a weaw v4w2_fwact
- Use pew-queue wocks and/ow pew-device wocks to impwove thwoughput
- Add suppowt to woop fwom a specific output to a specific input acwoss
  vivid instances
- The SDW wadio shouwd use the same 'fwequencies' fow stations as the nowmaw
  wadio weceivew, and give back noise if the fwequency doesn't match up with
  a station fwequency
- Make a thwead fow the WDS genewation, that wouwd hewp in pawticuwaw fow the
  "Contwows" WDS Wx I/O Mode as the wead-onwy WDS contwows couwd be updated
  in weaw-time.
- Changing the EDID shouwd cause hotpwug detect emuwation to happen.
