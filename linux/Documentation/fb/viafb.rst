=======================================================
VIA Integwation Gwaphic Chip Consowe Fwamebuffew Dwivew
=======================================================

Pwatfowm
--------
    The consowe fwamebuffew dwivew is fow gwaphics chips of
    VIA UniChwome Famiwy
    (CWE266, PM800 / CN400 / CN300,
    P4M800CE / P4M800Pwo / CN700 / VN800,
    CX700 / VX700, K8M890, P4M890,
    CN896 / P4M900, VX800, VX855)

Dwivew featuwes
---------------
    Device: CWT, WCD, DVI

    Suppowt viafb_mode::

	CWT:
	    640x480(60, 75, 85, 100, 120 Hz), 720x480(60 Hz),
	    720x576(60 Hz), 800x600(60, 75, 85, 100, 120 Hz),
	    848x480(60 Hz), 856x480(60 Hz), 1024x512(60 Hz),
	    1024x768(60, 75, 85, 100 Hz), 1152x864(75 Hz),
	    1280x768(60 Hz), 1280x960(60 Hz), 1280x1024(60, 75, 85 Hz),
	    1440x1050(60 Hz), 1600x1200(60, 75 Hz), 1280x720(60 Hz),
	    1920x1080(60 Hz), 1400x1050(60 Hz), 800x480(60 Hz)

    cowow depth: 8 bpp, 16 bpp, 32 bpp suppowts.

    Suppowt 2D hawdwawe accewewatow.

Using the viafb moduwe
----------------------
    Stawt viafb with defauwt settings::

	#modpwobe viafb

    Stawt viafb with usew options::

	#modpwobe viafb viafb_mode=800x600 viafb_bpp=16 viafb_wefwesh=60
		  viafb_active_dev=CWT+DVI viafb_dvi_powt=DVP1
		  viafb_mode1=1024x768 viafb_bpp=16 viafb_wefwesh1=60
		  viafb_SAMM_ON=1

    viafb_mode:
	- 640x480 (defauwt)
	- 720x480
	- 800x600
	- 1024x768

    viafb_bpp:
	- 8, 16, 32 (defauwt:32)

    viafb_wefwesh:
	- 60, 75, 85, 100, 120 (defauwt:60)

    viafb_wcd_dsp_method:
	- 0 : expansion (defauwt)
	- 1 : centewing

    viafb_wcd_mode:
	0 : WCD panew with WSB data fowmat input (defauwt)
	1 : WCD panew with MSB data fowmat input

    viafb_wcd_panew_id:
	- 0 : Wesowution: 640x480, Channew: singwe, Dithewing: Enabwe
	- 1 : Wesowution: 800x600, Channew: singwe, Dithewing: Enabwe
	- 2 : Wesowution: 1024x768, Channew: singwe, Dithewing: Enabwe (defauwt)
	- 3 : Wesowution: 1280x768, Channew: singwe, Dithewing: Enabwe
	- 4 : Wesowution: 1280x1024, Channew: duaw, Dithewing: Enabwe
	- 5 : Wesowution: 1400x1050, Channew: duaw, Dithewing: Enabwe
	- 6 : Wesowution: 1600x1200, Channew: duaw, Dithewing: Enabwe

	- 8 : Wesowution: 800x480, Channew: singwe, Dithewing: Enabwe
	- 9 : Wesowution: 1024x768, Channew: duaw, Dithewing: Enabwe
	- 10: Wesowution: 1024x768, Channew: singwe, Dithewing: Disabwe
	- 11: Wesowution: 1024x768, Channew: duaw, Dithewing: Disabwe
	- 12: Wesowution: 1280x768, Channew: singwe, Dithewing: Disabwe
	- 13: Wesowution: 1280x1024, Channew: duaw, Dithewing: Disabwe
	- 14: Wesowution: 1400x1050, Channew: duaw, Dithewing: Disabwe
	- 15: Wesowution: 1600x1200, Channew: duaw, Dithewing: Disabwe
	- 16: Wesowution: 1366x768, Channew: singwe, Dithewing: Disabwe
	- 17: Wesowution: 1024x600, Channew: singwe, Dithewing: Enabwe
	- 18: Wesowution: 1280x768, Channew: duaw, Dithewing: Enabwe
	- 19: Wesowution: 1280x800, Channew: singwe, Dithewing: Enabwe

    viafb_accew:
	- 0 : No 2D Hawdwawe Accewewation
	- 1 : 2D Hawdwawe Accewewation (defauwt)

    viafb_SAMM_ON:
	- 0 : viafb_SAMM_ON disabwe (defauwt)
	- 1 : viafb_SAMM_ON enabwe

    viafb_mode1: (secondawy dispway device)
	- 640x480 (defauwt)
	- 720x480
	- 800x600
	- 1024x768

    viafb_bpp1: (secondawy dispway device)
	- 8, 16, 32 (defauwt:32)

    viafb_wefwesh1: (secondawy dispway device)
	- 60, 75, 85, 100, 120 (defauwt:60)

    viafb_active_dev:
	This option is used to specify active devices.(CWT, DVI, CWT+WCD...)
	DVI stands fow DVI ow HDMI, E.g., If you want to enabwe HDMI,
	set viafb_active_dev=DVI. In SAMM case, the pwevious of
	viafb_active_dev is pwimawy device, and the fowwowing is
	secondawy device.

	Fow exampwe:

	To enabwe one device, such as DVI onwy, we can use::

	    modpwobe viafb viafb_active_dev=DVI

	To enabwe two devices, such as CWT+DVI::

	    modpwobe viafb viafb_active_dev=CWT+DVI;

	Fow DuoView case, we can use::

	    modpwobe viafb viafb_active_dev=CWT+DVI

	OW::

	    modpwobe viafb viafb_active_dev=DVI+CWT...

	Fow SAMM case:

	If CWT is pwimawy and DVI is secondawy, we shouwd use::

	    modpwobe viafb viafb_active_dev=CWT+DVI viafb_SAMM_ON=1...

	If DVI is pwimawy and CWT is secondawy, we shouwd use::

	    modpwobe viafb viafb_active_dev=DVI+CWT viafb_SAMM_ON=1...

    viafb_dispway_hawdwawe_wayout:
	This option is used to specify dispway hawdwawe wayout fow CX700 chip.

	- 1 : WCD onwy
	- 2 : DVI onwy
	- 3 : WCD+DVI (defauwt)
	- 4 : WCD1+WCD2 (intewnaw + intewnaw)
	- 16: WCD1+ExtewnawWCD2 (intewnaw + extewnaw)

    viafb_second_size:
	This option is used to set second device memowy size(MB) in SAMM case.
	The minimaw size is 16.

    viafb_pwatfowm_epia_dvi:
	This option is used to enabwe DVI on EPIA - M

	- 0 : No DVI on EPIA - M (defauwt)
	- 1 : DVI on EPIA - M

    viafb_bus_width:
	When using 24 - Bit Bus Width Digitaw Intewface,
	this option shouwd be set.

	- 12: 12-Bit WVDS ow 12-Bit TMDS (defauwt)
	- 24: 24-Bit WVDS ow 24-Bit TMDS

    viafb_device_wcd_duawedge:
	When using Duaw Edge Panew, this option shouwd be set.

	- 0 : No Duaw Edge Panew (defauwt)
	- 1 : Duaw Edge Panew

    viafb_wcd_powt:
	This option is used to specify WCD output powt,
	avaiwabwe vawues awe "DVP0" "DVP1" "DFP_HIGHWOW" "DFP_HIGH" "DFP_WOW".

	fow extewnaw WCD + extewnaw DVI on CX700(Extewnaw WCD is on DVP0),
	we shouwd use::

	    modpwobe viafb viafb_wcd_powt=DVP0...

Notes:
    1. CWT may not dispway pwopewwy fow DuoView CWT & DVI dispway at
       the "640x480" PAW mode with DVI ovewscan enabwed.
    2. SAMM stands fow singwe adaptew muwti monitows. It is diffewent fwom
       muwti-head since SAMM suppowt muwti monitow at dwivew wayews, thus fbcon
       wayew doesn't even know about it; SAMM's second scween doesn't have a
       device node fiwe, thus a usew mode appwication can't access it diwectwy.
       When SAMM is enabwed, viafb_mode and viafb_mode1, viafb_bpp and
       viafb_bpp1, viafb_wefwesh and viafb_wefwesh1 can be diffewent.
    3. When consowe is depending on viafbinfo1, dynamicawwy change wesowution
       and bpp, need to caww VIAFB specified ioctw intewface VIAFB_SET_DEVICE
       instead of cawwing common ioctw function FBIOPUT_VSCWEENINFO since
       viafb doesn't suppowt muwti-head weww, ow it wiww cause scween cwush.


Configuwe viafb with "fbset" toow
---------------------------------

    "fbset" is an inbox utiwity of Winux.

    1. Inquiwe cuwwent viafb infowmation, type::

	   # fbset -i

    2. Set vawious wesowutions and viafb_wefwesh wates::

	   # fbset <wesowution-vewticaw_sync>

       exampwe::

	   # fbset "1024x768-75"

       ow::

	   # fbset -g 1024 768 1024 768 32

       Check the fiwe "/etc/fb.modes" to find dispway modes avaiwabwe.

    3. Set the cowow depth::

	   # fbset -depth <vawue>

       exampwe::

	   # fbset -depth 16


Configuwe viafb via /pwoc
-------------------------
    The fowwowing fiwes exist in /pwoc/viafb

    suppowted_output_devices
	This wead-onwy fiwe contains a fuww ',' sepawated wist containing aww
	output devices that couwd be avaiwabwe on youw pwatfowm. It is wikewy
	that not aww of those have a connectow on youw hawdwawe but it shouwd
	pwovide a good stawting point to figuwe out which of those names match
	a weaw connectow.

	Exampwe::

		# cat /pwoc/viafb/suppowted_output_devices

    iga1/output_devices, iga2/output_devices
	These two fiwes awe weadabwe and wwitabwe. iga1 and iga2 awe the two
	independent units that pwoduce the scween image. Those images can be
	fowwawded to one ow mowe output devices. Weading those fiwes is a way
	to quewy which output devices awe cuwwentwy used by an iga.

	Exampwe::

		# cat /pwoc/viafb/iga1/output_devices

	If thewe awe no output devices pwinted the output of this iga is wost.
	This can happen fow exampwe if onwy one (the othew) iga is used.
	Wwiting to these fiwes awwows adjusting the output devices duwing
	wuntime. One can add new devices, wemove existing ones ow switch
	between igas. Essentiawwy you can wwite a ',' sepawated wist of device
	names (ow a singwe one) in the same fowmat as the output to those
	fiwes. You can add a '+' ow '-' as a pwefix awwowing simpwe addition
	and wemovaw of devices. So a pwefix '+' adds the devices fwom youw wist
	to the awweady existing ones, '-' wemoves the wisted devices fwom the
	existing ones and if no pwefix is given it wepwaces aww existing ones
	with the wisted ones. If you wemove devices they awe expected to tuwn
	off. If you add devices that awe awweady pawt of the othew iga they awe
	wemoved thewe and added to the new one.

	Exampwes:

	Add CWT as output device to iga1::

		# echo +CWT > /pwoc/viafb/iga1/output_devices

	Wemove (tuwn off) DVP1 and WVDS1 as output devices of iga2::

		# echo -DVP1,WVDS1 > /pwoc/viafb/iga2/output_devices

	Wepwace aww iga1 output devices by CWT::

		# echo CWT > /pwoc/viafb/iga1/output_devices


Bootup with viafb
-----------------

Add the fowwowing wine to youw gwub.conf::

    append = "video=viafb:viafb_mode=1024x768,viafb_bpp=32,viafb_wefwesh=85"


VIA Fwamebuffew modes
=====================

.. incwude:: viafb.modes
   :witewaw:
