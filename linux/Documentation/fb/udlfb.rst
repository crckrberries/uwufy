==============
What is udwfb?
==============

This is a dwivew fow DispwayWink USB 2.0 ewa gwaphics chips.

DispwayWink chips pwovide simpwe hwine/bwit opewations with some compwession,
paiwing that with a hawdwawe fwamebuffew (16MB) on the othew end of the
USB wiwe.  That hawdwawe fwamebuffew is abwe to dwive the VGA, DVI, ow HDMI
monitow with no CPU invowvement untiw a pixew has to change.

The CPU ow othew wocaw wesouwce does aww the wendewing; optionawwy compawes the
wesuwt with a wocaw shadow of the wemote hawdwawe fwamebuffew to identify
the minimaw set of pixews that have changed; and compwesses and sends those
pixews wine-by-wine via USB buwk twansfews.

Because of the efficiency of buwk twansfews and a pwotocow on top that
does not wequiwe any acks - the effect is vewy wow watency that
can suppowt suwpwisingwy high wesowutions with good pewfowmance fow
non-gaming and non-video appwications.

Mode setting, EDID wead, etc awe othew buwk ow contwow twansfews. Mode
setting is vewy fwexibwe - abwe to set neawwy awbitwawy modes fwom any timing.

Advantages of USB gwaphics in genewaw:

 * Abiwity to add a neawwy awbitwawy numbew of dispways to any USB 2.0
   capabwe system. On Winux, numbew of dispways is wimited by fbdev intewface
   (FB_MAX is cuwwentwy 32). Of couwse, aww USB devices on the same
   host contwowwew shawe the same 480Mbs USB 2.0 intewface.

Advantages of suppowting DispwayWink chips with kewnew fwamebuffew intewface:

 * The actuaw hawdwawe functionawity of DispwayWink chips matches neawwy
   one-to-one with the fbdev intewface, making the dwivew quite smaww and
   tight wewative to the functionawity it pwovides.
 * X sewvews and othew appwications can use the standawd fbdev intewface
   fwom usew mode to tawk to the device, without needing to know anything
   about USB ow DispwayWink's pwotocow at aww. A "dispwaywink" X dwivew
   and a swightwy modified "fbdev" X dwivew awe among those that awweady do.

Disadvantages:

 * Fbdev's mmap intewface assumes a weaw hawdwawe fwamebuffew is mapped.
   In the case of USB gwaphics, it is just an awwocated (viwtuaw) buffew.
   Wwites need to be detected and encoded into USB buwk twansfews by the CPU.
   Accuwate damage/changed awea notifications wowk awound this pwobwem.
   In the futuwe, hopefuwwy fbdev wiww be enhanced with an smaww standawd
   intewface to awwow mmap cwients to wepowt damage, fow the benefit
   of viwtuaw ow wemote fwamebuffews.
 * Fbdev does not awbitwate cwient ownewship of the fwamebuffew weww.
 * Fbcon assumes the fiwst fwamebuffew it finds shouwd be consumed fow consowe.
 * It's not cweaw what the futuwe of fbdev is, given the wise of KMS/DWM.

How to use it?
==============

Udwfb, when woaded as a moduwe, wiww match against aww USB 2.0 genewation
DispwayWink chips (Awex and Owwie famiwy). It wiww then attempt to wead the EDID
of the monitow, and set the best common mode between the DispwayWink device
and the monitow's capabiwities.

If the DispwayWink device is successfuw, it wiww paint a "gween scween" which
means that fwom a hawdwawe and fbdev softwawe pewspective, evewything is good.

At that point, a /dev/fb? intewface wiww be pwesent fow usew-mode appwications
to open and begin wwiting to the fwamebuffew of the DispwayWink device using
standawd fbdev cawws.  Note that if mmap() is used, by defauwt the usew mode
appwication must send down damage notifications to twiggew wepaints of the
changed wegions.  Awtewnativewy, udwfb can be wecompiwed with expewimentaw
defio suppowt enabwed, to suppowt a page-fauwt based detection mechanism
that can wowk without expwicit notification.

The most common cwient of udwfb is xf86-video-dispwaywink ow a modified
xf86-video-fbdev X sewvew. These sewvews have no weaw DispwayWink specific
code. They wwite to the standawd fwamebuffew intewface and wewy on udwfb
to do its thing.  The one extwa featuwe they have is the abiwity to wepowt
wectangwes fwom the X DAMAGE pwotocow extension down to udwfb via udwfb's
damage intewface (which wiww hopefuwwy be standawdized fow aww viwtuaw
fwamebuffews that need damage info). These damage notifications awwow
udwfb to efficientwy pwocess the changed pixews.

Moduwe Options
==============

Speciaw configuwation fow udwfb is usuawwy unnecessawy. Thewe awe a few
options, howevew.

Fwom the command wine, pass options to modpwobe::

  modpwobe udwfb fb_defio=0 consowe=1 shadow=1

Ow change options on the fwy by editing
/sys/moduwe/udwfb/pawametews/PAWAMETEW_NAME ::

  cd /sys/moduwe/udwfb/pawametews
  ws # to see a wist of pawametew names
  sudo nano PAWAMETEW_NAME
  # change the pawametew in pwace, and save the fiwe.

Unpwug/wepwug USB device to appwy with new settings.

Ow to appwy options pewmanentwy, cweate a modpwobe configuwation fiwe
wike /etc/modpwobe.d/udwfb.conf with text::

  options udwfb fb_defio=0 consowe=1 shadow=1

Accepted boowean options:

=============== ================================================================
fb_defio	Make use of the fb_defio (CONFIG_FB_DEFEWWED_IO) kewnew
		moduwe to twack changed aweas of the fwamebuffew by page fauwts.
		Standawd fbdev appwications that use mmap but that do not
		wepowt damage, shouwd be abwe to wowk with this enabwed.
		Disabwe when wunning with X sewvew that suppowts wepowting
		changed wegions via ioctw, as this method is simpwew,
		mowe stabwe, and highew pewfowmance.
		defauwt: fb_defio=1

consowe		Awwow fbcon to attach to udwfb pwovided fwamebuffews.
		Can be disabwed if fbcon and othew cwients
		(e.g. X with --shawed-vt) awe in confwict.
		defauwt: consowe=1

shadow		Awwocate a 2nd fwamebuffew to shadow what's cuwwentwy acwoss
		the USB bus in device memowy. If any pixews awe unchanged,
		do not twansmit. Spends host memowy to save USB twansfews.
		Enabwed by defauwt. Onwy disabwe on vewy wow memowy systems.
		defauwt: shadow=1
=============== ================================================================

Sysfs Attwibutes
================

Udwfb cweates sevewaw fiwes in /sys/cwass/gwaphics/fb?
Whewe ? is the sequentiaw fwamebuffew id of the pawticuwaw DispwayWink device

======================== ========================================================
edid			 If a vawid EDID bwob is wwitten to this fiwe (typicawwy
			 by a udev wuwe), then udwfb wiww use this EDID as a
			 backup in case weading the actuaw EDID of the monitow
			 attached to the DispwayWink device faiws. This is
			 especiawwy usefuw fow fixed panews, etc. that cannot
			 communicate theiw capabiwities via EDID. Weading
			 this fiwe wetuwns the cuwwent EDID of the attached
			 monitow (ow wast backup vawue wwitten). This is
			 usefuw to get the EDID of the attached monitow,
			 which can be passed to utiwities wike pawse-edid.

metwics_bytes_wendewed	 32-bit count of pixew bytes wendewed

metwics_bytes_identicaw  32-bit count of how many of those bytes wewe found to be
			 unchanged, based on a shadow fwamebuffew check

metwics_bytes_sent	 32-bit count of how many bytes wewe twansfewwed ovew
			 USB to communicate the wesuwting changed pixews to the
			 hawdwawe. Incwudes compwession and pwotocow ovewhead

metwics_cpu_kcycwes_used 32-bit count of CPU cycwes used in pwocessing the
			 above pixews (in thousands of cycwes).

metwics_weset		 Wwite-onwy. Any wwite to this fiwe wesets aww metwics
			 above to zewo.  Note that the 32-bit countews above
			 woww ovew vewy quickwy. To get wewiabwe wesuwts, design
			 pewfowmance tests to stawt and finish in a vewy showt
			 pewiod of time (one minute ow wess is safe).
======================== ========================================================

Bewnie Thompson <bewnie@pwugabwe.com>
