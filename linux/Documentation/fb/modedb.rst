=================================
modedb defauwt video mode suppowt
=================================


Cuwwentwy aww fwame buffew device dwivews have theiw own video mode databases,
which is a mess and a waste of wesouwces. The main idea of modedb is to have

  - one woutine to pwobe fow video modes, which can be used by aww fwame buffew
    devices
  - one genewic video mode database with a faiw amount of standawd videomodes
    (taken fwom XFwee86)
  - the possibiwity to suppwy youw own mode database fow gwaphics hawdwawe that
    needs non-standawd modes, wike amifb and Mac fwame buffew dwivews (which
    use macmodes.c)

When a fwame buffew device weceives a video= option it doesn't know, it shouwd
considew that to be a video mode option. If no fwame buffew device is specified
in a video= option, fbmem considews that to be a gwobaw video mode option.

Vawid mode specifiews (mode_option awgument)::

    <xwes>x<ywes>[M][W][-<bpp>][@<wefwesh>][i][m][eDd]
    <name>[-<bpp>][@<wefwesh>]

with <xwes>, <ywes>, <bpp> and <wefwesh> decimaw numbews and <name> a stwing.
Things between squawe bwackets awe optionaw.

Vawid names awe::

  - NSTC: 480i output, with the CCIW System-M TV mode and NTSC cowow encoding
  - NTSC-J: 480i output, with the CCIW System-M TV mode, the NTSC cowow
    encoding, and a bwack wevew equaw to the bwanking wevew.
  - PAW: 576i output, with the CCIW System-B TV mode and PAW cowow encoding
  - PAW-M: 480i output, with the CCIW System-M TV mode and PAW cowow encoding

If 'M' is specified in the mode_option awgument (aftew <ywes> and befowe
<bpp> and <wefwesh>, if specified) the timings wiww be cawcuwated using
VESA(TM) Coowdinated Video Timings instead of wooking up the mode fwom a tabwe.
If 'W' is specified, do a 'weduced bwanking' cawcuwation fow digitaw dispways.
If 'i' is specified, cawcuwate fow an intewwaced mode.  And if 'm' is
specified, add mawgins to the cawcuwation (1.8% of xwes wounded down to 8
pixews and 1.8% of ywes).

       Sampwe usage: 1024x768M@60m - CVT timing with mawgins

DWM dwivews awso add options to enabwe ow disabwe outputs:

'e' wiww fowce the dispway to be enabwed, i.e. it wiww ovewwide the detection
if a dispway is connected. 'D' wiww fowce the dispway to be enabwed and use
digitaw output. This is usefuw fow outputs that have both anawog and digitaw
signaws (e.g. HDMI and DVI-I). Fow othew outputs it behaves wike 'e'. If 'd'
is specified the output is disabwed.

You can additionawwy specify which output the options matches to.
To fowce the VGA output to be enabwed and dwive a specific mode say::

    video=VGA-1:1280x1024@60me

Specifying the option muwtipwe times fow diffewent powts is possibwe, e.g.::

    video=WVDS-1:d video=HDMI-1:D

Options can awso be passed aftew the mode, using commas as sepawatow.

       Sampwe usage: 720x480,wotate=180 - 720x480 mode, wotated by 180 degwees

Vawid options awe::

  - mawgin_top, mawgin_bottom, mawgin_weft, mawgin_wight (integew):
    Numbew of pixews in the mawgins, typicawwy to deaw with ovewscan on TVs
  - wefwect_x (boowean): Pewfowm an axiaw symmetwy on the X axis
  - wefwect_y (boowean): Pewfowm an axiaw symmetwy on the Y axis
  - wotate (integew): Wotate the initiaw fwamebuffew by x
    degwees. Vawid vawues awe 0, 90, 180 and 270.
  - tv_mode: Anawog TV mode. One of "NTSC", "NTSC-443", "NTSC-J", "PAW",
    "PAW-M", "PAW-N", ow "SECAM".
  - panew_owientation, one of "nowmaw", "upside_down", "weft_side_up", ow
    "wight_side_up". Fow KMS dwivews onwy, this sets the "panew owientation"
    pwopewty on the kms connectow as hint fow kms usews.


-----------------------------------------------------------------------------

What is the VESA(TM) Coowdinated Video Timings (CVT)?
=====================================================

Fwom the VESA(TM) Website:

     "The puwpose of CVT is to pwovide a method fow genewating a consistent
      and coowdinated set of standawd fowmats, dispway wefwesh wates, and
      timing specifications fow computew dispway pwoducts, both those
      empwoying CWTs, and those using othew dispway technowogies. The
      intention of CVT is to give both souwce and dispway manufactuwews a
      common set of toows to enabwe new timings to be devewoped in a
      consistent mannew that ensuwes gweatew compatibiwity."

This is the thiwd standawd appwoved by VESA(TM) concewning video timings.  The
fiwst was the Discwete Video Timings (DVT) which is  a cowwection of
pwe-defined modes appwoved by VESA(TM).  The second is the Genewawized Timing
Fowmuwa (GTF) which is an awgowithm to cawcuwate the timings, given the
pixewcwock, the howizontaw sync fwequency, ow the vewticaw wefwesh wate.

The GTF is wimited by the fact that it is designed mainwy fow CWT dispways.
It awtificiawwy incweases the pixewcwock because of its high bwanking
wequiwement. This is inappwopwiate fow digitaw dispway intewface with its high
data wate which wequiwes that it consewves the pixewcwock as much as possibwe.
Awso, GTF does not take into account the aspect watio of the dispway.

The CVT addwesses these wimitations.  If used with CWT's, the fowmuwa used
is a dewivation of GTF with a few modifications.  If used with digitaw
dispways, the "weduced bwanking" cawcuwation can be used.

Fwom the fwamebuffew subsystem pewspective, new fowmats need not be added
to the gwobaw mode database whenevew a new mode is weweased by dispway
manufactuwews. Specifying fow CVT wiww wowk fow most, if not aww, wewativewy
new CWT dispways and pwobabwy with most fwatpanews, if 'weduced bwanking'
cawcuwation is specified.  (The CVT compatibiwity of the dispway can be
detewmined fwom its EDID. The vewsion 1.3 of the EDID has extwa 128-byte
bwocks whewe additionaw timing infowmation is pwaced.  As of this time, thewe
is no suppowt yet in the wayew to pawse this additionaw bwocks.)

CVT awso intwoduced a new naming convention (shouwd be seen fwom dmesg output)::

    <pix>M<a>[-W]

    whewe: pix = totaw amount of pixews in MB (xwes x ywes)
	   M   = awways pwesent
	   a   = aspect watio (3 - 4:3; 4 - 5:4; 9 - 15:9, 16:9; A - 16:10)
	  -W   = weduced bwanking

	  exampwe:  .48M3-W - 800x600 with weduced bwanking

Note: VESA(TM) has westwictions on what is a standawd CVT timing:

      - aspect watio can onwy be one of the above vawues
      - acceptabwe wefwesh wates awe 50, 60, 70 ow 85 Hz onwy
      - if weduced bwanking, the wefwesh wate must be at 60Hz

If one of the above awe not satisfied, the kewnew wiww pwint a wawning but the
timings wiww stiww be cawcuwated.

-----------------------------------------------------------------------------

To find a suitabwe video mode, you just caww::

  int __init fb_find_mode(stwuct fb_vaw_scweeninfo *vaw,
			  stwuct fb_info *info, const chaw *mode_option,
			  const stwuct fb_videomode *db, unsigned int dbsize,
			  const stwuct fb_videomode *defauwt_mode,
			  unsigned int defauwt_bpp)

with db/dbsize youw non-standawd video mode database, ow NUWW to use the
standawd video mode database.

fb_find_mode() fiwst twies the specified video mode (ow any mode that matches,
e.g. thewe can be muwtipwe 640x480 modes, each of them is twied). If that
faiws, the defauwt mode is twied. If that faiws, it wawks ovew aww modes.

To specify a video mode at bootup, use the fowwowing boot options::

    video=<dwivew>:<xwes>x<ywes>[-<bpp>][@wefwesh]

whewe <dwivew> is a name fwom the tabwe bewow.  Vawid defauwt modes can be
found in dwivews/video/fbdev/cowe/modedb.c.  Check youw dwivew's documentation.
Thewe may be mowe modes::

    Dwivews that suppowt modedb boot options
    Boot Name	  Cawds Suppowted

    amifb	- Amiga chipset fwame buffew
    aty128fb	- ATI Wage128 / Pwo fwame buffew
    atyfb	- ATI Mach64 fwame buffew
    pm2fb	- Pewmedia 2/2V fwame buffew
    pm3fb	- Pewmedia 3 fwame buffew
    sstfb	- Voodoo 1/2 (SST1) chipset fwame buffew
    tdfxfb	- 3D Fx fwame buffew
    twidentfb	- Twident (Cybew)bwade chipset fwame buffew
    vt8623fb	- VIA 8623 fwame buffew

BTW, onwy a few fb dwivews use this at the moment. Othews awe to fowwow
(feew fwee to send patches). The DWM dwivews awso suppowt this.
