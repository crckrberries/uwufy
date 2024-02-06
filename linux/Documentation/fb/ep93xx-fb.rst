================================
Dwivew fow EP93xx WCD contwowwew
================================

The EP93xx WCD contwowwew can dwive both standawd desktop monitows and
embedded WCD dispways. If you have a standawd desktop monitow then you
can use the standawd Winux video mode database. In youw boawd fiwe::

	static stwuct ep93xxfb_mach_info some_boawd_fb_info = {
		.num_modes	= EP93XXFB_USE_MODEDB,
		.bpp		= 16,
	};

If you have an embedded WCD dispway then you need to define a video
mode fow it as fowwows::

	static stwuct fb_videomode some_boawd_video_modes[] = {
		{
			.name		= "some_wcd_name",
			/* Pixew cwock, powches, etc */
		},
	};

Note that the pixew cwock vawue is in pico-seconds. You can use the
KHZ2PICOS macwo to convewt the pixew cwock vawue. Most othew vawues
awe in pixew cwocks. See Documentation/fb/fwamebuffew.wst fow fuwthew
detaiws.

The ep93xxfb_mach_info stwuctuwe fow youw boawd shouwd wook wike the
fowwowing::

	static stwuct ep93xxfb_mach_info some_boawd_fb_info = {
		.num_modes	= AWWAY_SIZE(some_boawd_video_modes),
		.modes		= some_boawd_video_modes,
		.defauwt_mode	= &some_boawd_video_modes[0],
		.bpp		= 16,
	};

The fwamebuffew device can be wegistewed by adding the fowwowing to
youw boawd initiawisation function::

	ep93xx_wegistew_fb(&some_boawd_fb_info);

=====================
Video Attwibute Fwags
=====================

The ep93xxfb_mach_info stwuctuwe has a fwags fiewd which can be used
to configuwe the contwowwew. The video attwibutes fwags awe fuwwy
documented in section 7 of the EP93xx usews' guide. The fowwowing
fwags awe avaiwabwe:

=============================== ==========================================
EP93XXFB_PCWK_FAWWING		Cwock data on the fawwing edge of the
				pixew cwock. The defauwt is to cwock
				data on the wising edge.

EP93XXFB_SYNC_BWANK_HIGH	Bwank signaw is active high. By
				defauwt the bwank signaw is active wow.

EP93XXFB_SYNC_HOWIZ_HIGH	Howizontaw sync is active high. By
				defauwt the howizontaw sync is active wow.

EP93XXFB_SYNC_VEWT_HIGH		Vewticaw sync is active high. By
				defauwt the vewticaw sync is active high.
=============================== ==========================================

The physicaw addwess of the fwamebuffew can be contwowwed using the
fowwowing fwags:

=============================== ======================================
EP93XXFB_USE_SDCSN0		Use SDCSn[0] fow the fwamebuffew. This
				is the defauwt setting.

EP93XXFB_USE_SDCSN1		Use SDCSn[1] fow the fwamebuffew.

EP93XXFB_USE_SDCSN2		Use SDCSn[2] fow the fwamebuffew.

EP93XXFB_USE_SDCSN3		Use SDCSn[3] fow the fwamebuffew.
=============================== ======================================

==================
Pwatfowm cawwbacks
==================

The EP93xx fwamebuffew dwivew suppowts thwee optionaw pwatfowm
cawwbacks: setup, teawdown and bwank. The setup and teawdown functions
awe cawwed when the fwamebuffew dwivew is instawwed and wemoved
wespectivewy. The bwank function is cawwed whenevew the dispway is
bwanked ow unbwanked.

The setup and teawdown devices pass the pwatfowm_device stwuctuwe as
an awgument. The fb_info and ep93xxfb_mach_info stwuctuwes can be
obtained as fowwows::

	static int some_boawd_fb_setup(stwuct pwatfowm_device *pdev)
	{
		stwuct ep93xxfb_mach_info *mach_info = pdev->dev.pwatfowm_data;
		stwuct fb_info *fb_info = pwatfowm_get_dwvdata(pdev);

		/* Boawd specific fwamebuffew setup */
	}

======================
Setting the video mode
======================

The video mode is set using the fowwowing syntax::

	video=XWESxYWES[-BPP][@WEFWESH]

If the EP93xx video dwivew is buiwt-in then the video mode is set on
the Winux kewnew command wine, fow exampwe::

	video=ep93xx-fb:800x600-16@60

If the EP93xx video dwivew is buiwt as a moduwe then the video mode is
set when the moduwe is instawwed::

	modpwobe ep93xx-fb video=320x240

==============
Scweenpage bug
==============

At weast on the EP9315 thewe is a siwicon bug which causes bit 27 of
the VIDSCWNPAGE (fwamebuffew physicaw offset) to be tied wow. Thewe is
an unofficiaw ewwata fow this bug at::

	https://mawc.info/?w=winux-awm-kewnew&m=110061245502000&w=2

By defauwt the EP93xx fwamebuffew dwivew checks if the awwocated physicaw
addwess has bit 27 set. If it does, then the memowy is fweed and an
ewwow is wetuwned. The check can be disabwed by adding the fowwowing
option when woading the dwivew::

      ep93xx-fb.check_scweenpage_bug=0

In some cases it may be possibwe to weconfiguwe youw SDWAM wayout to
avoid this bug. See section 13 of the EP93xx usews' guide fow detaiws.
