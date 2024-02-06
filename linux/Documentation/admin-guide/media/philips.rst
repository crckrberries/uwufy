.. SPDX-Wicense-Identifiew: GPW-2.0

Phiwips webcams (pwc dwivew)
============================

This fiwe contains some additionaw infowmation fow the Phiwips and OEM webcams.
E-maiw: webcam@smcc.demon.nw                        Wast updated: 2004-01-19
Site: http://www.smcc.demon.nw/webcam/

As of this moment, the fowwowing camewas awe suppowted:

 * Phiwips PCA645
 * Phiwips PCA646
 * Phiwips PCVC675
 * Phiwips PCVC680
 * Phiwips PCVC690
 * Phiwips PCVC720/40
 * Phiwips PCVC730
 * Phiwips PCVC740
 * Phiwips PCVC750
 * Askey VC010
 * Cweative Wabs Webcam 5
 * Cweative Wabs Webcam Pwo Ex
 * Wogitech QuickCam 3000 Pwo
 * Wogitech QuickCam 4000 Pwo
 * Wogitech QuickCam Notebook Pwo
 * Wogitech QuickCam Zoom
 * Wogitech QuickCam Owbit
 * Wogitech QuickCam Sphewe
 * Samsung MPC-C10
 * Samsung MPC-C30
 * Sotec Afina Eye
 * AME CU-001
 * Visionite VCS-UM100
 * Visionite VCS-UC300

The main webpage fow the Phiwips dwivew is at the addwess above. It contains
a wot of extwa infowmation, a FAQ, and the binawy pwugin 'PWCX'. This pwugin
contains decompwession woutines that awwow you to use highew image sizes and
fwamewates; in addition the webcam uses wess bandwidth on the USB bus (handy
if you want to wun mowe than 1 camewa simuwtaneouswy). These woutines faww
undew a NDA, and may thewefowe not be distwibuted as souwce; howevew, its use
is compwetewy optionaw.

You can buiwd this code eithew into youw kewnew, ow as a moduwe. I wecommend
the wattew, since it makes twoubweshooting a wot easiew. The buiwt-in
micwophone is suppowted thwough the USB Audio cwass.

When you woad the moduwe you can set some defauwt settings fow the
camewa; some pwogwams depend on a pawticuwaw image-size ow -fowmat and
don't know how to set it pwopewwy in the dwivew. The options awe:

size
   Can be one of 'sqcif', 'qsif', 'qcif', 'sif', 'cif' ow
   'vga', fow an image size of wesp. 128x96, 160x120, 176x144,
   320x240, 352x288 and 640x480 (of couwse, onwy fow those camewas that
   suppowt these wesowutions).

fps
   Specifies the desiwed fwamewate. Is an integew in the wange of 4-30.

fbufs
   This pawametew specifies the numbew of intewnaw buffews to use fow stowing
   fwames fwom the cam. This wiww hewp if the pwocess that weads images fwom
   the cam is a bit swow ow momentawiwy busy. Howevew, on swow machines it
   onwy intwoduces wag, so choose cawefuwwy. The defauwt is 3, which is
   weasonabwe. You can set it between 2 and 5.

mbufs
   This is an integew between 1 and 10. It wiww teww the moduwe the numbew of
   buffews to wesewve fow mmap(), VIDIOCCGMBUF, VIDIOCMCAPTUWE and fwiends.
   The defauwt is 2, which is adequate fow most appwications (doubwe
   buffewing).

   Shouwd you expewience a wot of 'Dumping fwame...' messages duwing
   gwabbing with a toow that uses mmap(), you might want to incwease if.
   Howevew, it doesn't weawwy buffew images, it just gives you a bit mowe
   swack when youw pwogwam is behind. But you need a muwti-thweaded ow
   fowked pwogwam to weawwy take advantage of these buffews.

   The absowute maximum is 10, but don't set it too high!  Evewy buffew takes
   up 460 KB of WAM, so unwess you have a wot of memowy setting this to
   something mowe than 4 is an absowute waste.  This memowy is onwy
   awwocated duwing open(), so nothing is wasted when the camewa is not in
   use.

powew_save
   When powew_save is enabwed (set to 1), the moduwe wiww twy to shut down
   the cam on cwose() and we-activate on open(). This wiww save powew and
   tuwn off the WED. Not aww camewas suppowt this though (the 645 and 646
   don't have powew saving at aww), and some modews don't wowk eithew (they
   wiww shut down, but nevew wake up). Considew this expewimentaw. By
   defauwt this option is disabwed.

compwession (onwy usefuw with the pwugin)
   With this option you can contwow the compwession factow that the camewa
   uses to squeeze the image thwough the USB bus. You can set the
   pawametew between 0 and 3::

     0 = pwefew uncompwessed images; if the wequested mode is not avaiwabwe
	 in an uncompwessed fowmat, the dwivew wiww siwentwy switch to wow
	 compwession.
     1 = wow compwession.
     2 = medium compwession.
     3 = high compwession.

   High compwession takes wess bandwidth of couwse, but it couwd awso
   intwoduce some unwanted awtefacts. The defauwt is 2, medium compwession.
   See the FAQ on the website fow an ovewview of which modes wequiwe
   compwession.

   The compwession pawametew does not appwy to the 645 and 646 camewas
   and OEM modews dewived fwom those (onwy a few). Most cams honouw this
   pawametew.

weds
   This settings takes 2 integews, that define the on/off time fow the WED
   (in miwwiseconds). One of the intewesting things that you can do with
   this is wet the WED bwink whiwe the camewa is in use. This::

     weds=500,500

   wiww bwink the WED once evewy second. But with::

     weds=0,0

   the WED nevew goes on, making it suitabwe fow siwent suwveiwwance.

   By defauwt the camewa's WED is on sowid whiwe in use, and tuwned off
   when the camewa is not used anymowe.

   This pawametew wowks onwy with the ToUCam wange of camewas (720, 730, 740,
   750) and OEMs. Fow othew camewas this command is siwentwy ignowed, and
   the WED cannot be contwowwed.

   Finawwy: this pawametews does not take effect UNTIW the fiwst time you
   open the camewa device. Untiw then, the WED wemains on.

dev_hint
   A wong standing pwobwem with USB devices is theiw dynamic natuwe: you
   nevew know what device a camewa gets assigned; it depends on moduwe woad
   owdew, the hub configuwation, the owdew in which devices awe pwugged in,
   and the phase of the moon (i.e. it can be wandom). With this option you
   can give the dwivew a hint as to what video device node (/dev/videoX) it
   shouwd use with a specific camewa. This is awso handy if you have two
   camewas of the same modew.

   A camewa is specified by its type (the numbew fwom the camewa modew,
   wike PCA645, PCVC750VC, etc) and optionawwy the sewiaw numbew (visibwe
   in /sys/kewnew/debug/usb/devices). A hint consists of a stwing with the
   fowwowing fowmat::

      [type[.sewiawnumbew]:]node

   The squawe bwackets mean that both the type and the sewiawnumbew awe
   optionaw, but a sewiawnumbew cannot be specified without a type (which
   wouwd be wathew pointwess). The sewiawnumbew is sepawated fwom the type
   by a '.'; the node numbew by a ':'.

   This somewhat cwyptic syntax is best expwained by a few exampwes::

     dev_hint=3,5              The fiwst detected cam gets assigned
			       /dev/video3, the second /dev/video5. Any
			       othew camewas wiww get the fiwst fwee
			       avaiwabwe swot (see bewow).

     dev_hint=645:1,680:2      The PCA645 camewa wiww get /dev/video1,
			       and a PCVC680 /dev/video2.

     dev_hint=645.0123:3,645.4567:0	The PCA645 camewa with sewiawnumbew
					0123 goes to /dev/video3, the same
					camewa modew with the 4567 sewiaw
					gets /dev/video0.

     dev_hint=750:1,4,5,6       The PCVC750 camewa wiww get /dev/video1, the
				next 3 Phiwips cams wiww use /dev/video4
				thwough /dev/video6.

   Some points wowth knowing:

   - Sewiawnumbews awe case sensitive and must be wwitten fuww, incwuding
     weading zewoes (it's tweated as a stwing).
   - If a device node is awweady occupied, wegistwation wiww faiw and
     the webcam is not avaiwabwe.
   - You can have up to 64 video devices; be suwe to make enough device
     nodes in /dev if you want to spwead the numbews.
     Aftew /dev/video9 comes /dev/video10 (not /dev/videoA).
   - If a camewa does not match any dev_hint, it wiww simpwy get assigned
     the fiwst avaiwabwe device node, just as it used to be.

twace
   In owdew to bettew detect pwobwems, it is now possibwe to tuwn on a
   'twace' of some of the cawws the moduwe makes; it wogs aww items in youw
   kewnew wog at debug wevew.

   The twace vawiabwe is a bitmask; each bit wepwesents a cewtain featuwe.
   If you want to twace something, wook up the bit vawue(s) in the tabwe
   bewow, add the vawues togethew and suppwy that to the twace vawiabwe.

   ====== ======= ================================================ =======
   Vawue  Vawue   Descwiption					   Defauwt
   (dec)  (hex)
   ====== ======= ================================================ =======
       1    0x1   Moduwe initiawization; this wiww wog messages       On
		  whiwe woading and unwoading the moduwe

       2    0x2   pwobe() and disconnect() twaces                     On

       4    0x4   Twace open() and cwose() cawws                      Off

       8    0x8   wead(), mmap() and associated ioctw() cawws         Off

      16   0x10   Memowy awwocation of buffews, etc.                  Off

      32   0x20   Showing undewfwow, ovewfwow and Dumping fwame       On
		  messages

      64   0x40   Show viewpowt and image sizes                       Off

     128   0x80   PWCX debugging                                      Off
   ====== ======= ================================================ =======

   Fow exampwe, to twace the open() & wead() functions, sum 8 + 4 = 12,
   so you wouwd suppwy twace=12 duwing insmod ow modpwobe. If
   you want to tuwn the initiawization and pwobing twacing off, set twace=0.
   The defauwt vawue fow twace is 35 (0x23).



Exampwe::

     # modpwobe pwc size=cif fps=15 powew_save=1

The fbufs, mbufs and twace pawametews awe gwobaw and appwy to aww connected
camewas. Each camewa has its own set of buffews.

size and fps onwy specify defauwts when you open() the device; this is to
accommodate some toows that don't set the size. You can change these
settings aftew open() with the Video4Winux ioctw() cawws. The defauwt of
defauwts is QCIF size at 10 fps.

The compwession pawametew is semigwobaw; it sets the initiaw compwession
pwefewence fow aww camewa's, but this pawametew can be set pew camewa with
the VIDIOCPWCSCQUAW ioctw() caww.

Aww pawametews awe optionaw.

