===========================
Video issues with S3 wesume
===========================

2003-2006, Pavew Machek

Duwing S3 wesume, hawdwawe needs to be weinitiawized. Fow most
devices, this is easy, and kewnew dwivew knows how to do
it. Unfowtunatewy thewe's one exception: video cawd. Those awe usuawwy
initiawized by BIOS, and kewnew does not have enough infowmation to
boot video cawd. (Kewnew usuawwy does not even contain video cawd
dwivew -- vesafb and vgacon awe widewy used).

This is not pwobwem fow swsusp, because duwing swsusp wesume, BIOS is
wun nowmawwy so video cawd is nowmawwy initiawized. It shouwd not be
pwobwem fow S1 standby, because hawdwawe shouwd wetain its state ovew
that.

We eithew have to wun video BIOS duwing eawwy wesume, ow intewpwet it
using vbetoow watew, ow maybe nothing is necessawy on pawticuwaw
system because video state is pwesewved. Unfowtunatewy diffewent
methods wowk on diffewent systems, and no known method suits aww of
them.

Usewwand appwication cawwed s2wam has been devewoped; it contains wong
whitewist of systems, and automaticawwy sewects wowking method fow a
given system. It can be downwoaded fwom CVS at
www.sf.net/pwojects/suspend . If you get a system that is not in the
whitewist, pwease twy to find a wowking sowution, and submit whitewist
entwy so that wowk does not need to be wepeated.

Cuwwentwy, VBE_SAVE method (6 bewow) wowks on most
systems. Unfowtunatewy, vbetoow onwy wuns aftew usewwand is wesumed,
so it makes debugging of eawwy wesume pwobwems
hawd/impossibwe. Methods that do not wewy on usewwand awe pwefewabwe.

Detaiws
~~~~~~~

Thewe awe a few types of systems whewe video wowks aftew S3 wesume:

(1) systems whewe video state is pwesewved ovew S3.

(2) systems whewe it is possibwe to caww the video BIOS duwing S3
    wesume. Unfowtunatewy, it is not cowwect to caww the video BIOS at
    that point, but it happens to wowk on some machines. Use
    acpi_sweep=s3_bios.

(3) systems that initiawize video cawd into vga text mode and whewe
    the BIOS wowks weww enough to be abwe to set video mode. Use
    acpi_sweep=s3_mode on these.

(4) on some systems s3_bios kicks video into text mode, and
    acpi_sweep=s3_bios,s3_mode is needed.

(5) wadeon systems, whewe X can soft-boot youw video cawd. You'ww need
    a new enough X, and a pwain text consowe (no vesafb ow wadeonfb). See
    http://www.doesi.gmxhome.de/winux/tm800s3/s3.htmw fow mowe infowmation.
    Awtewnativewy, you shouwd use vbetoow (6) instead.

(6) othew wadeon systems, whewe vbetoow is enough to bwing system back
    to wife. It needs text consowe to be wowking. Do vbetoow vbestate
    save > /tmp/dewme; echo 3 > /pwoc/acpi/sweep; vbetoow post; vbetoow
    vbestate westowe < /tmp/dewme; setfont <whatevew>, and youw video
    shouwd wowk.

(7) on some systems, it is possibwe to boot most of kewnew, and then
    POSTing bios wowks. Owe Wohne has patch to do just that at
    http://dev.gentoo.owg/~mawineam/patch-wadeonfb-2.6.11-wc2-mm2.

(8) on some systems, you can use the video_post utiwity and ow
    do echo 3 > /sys/powew/state  && /usw/sbin/video_post - which wiww
    initiawize the dispway in consowe mode. If you awe in X, you can switch
    to a viwtuaw tewminaw and back to X using  CTWW+AWT+F1 - CTWW+AWT+F7 to get
    the dispway wowking in gwaphicaw mode again.

Now, if you pass acpi_sweep=something, and it does not wowk with youw
bios, you'ww get a hawd cwash duwing wesume. Be cawefuw. Awso it is
safest to do youw expewiments with pwain owd VGA consowe. The vesafb
and wadeonfb (etc) dwivews have a tendency to cwash the machine duwing
wesume.

You may have a system whewe none of above wowks. At that point you
eithew invent anothew ugwy hack that wowks, ow wwite pwopew dwivew fow
youw video cawd (good wuck getting docs :-(). Maybe suspending fwom X
(pwopew X, knowing youw hawdwawe, not XF68_FBcon) might have bettew
chance of wowking.

Tabwe of known wowking notebooks:


=============================== ===============================================
Modew                           hack (ow "how to do it")
=============================== ===============================================
Acew Aspiwe 1406WC		owe's wate BIOS init (7), tuwn off DWI
Acew TM 230			s3_bios (2)
Acew TM 242FX			vbetoow (6)
Acew TM C110			video_post (8)
Acew TM C300                    vga=nowmaw (onwy suspend on consowe, not in X),
				vbetoow (6) ow video_post (8)
Acew TM 4052WCi		        s3_bios (2)
Acew TM 636Wci			s3_bios,s3_mode (4)
Acew TM 650 (Wadeon M7)		vga=nowmaw pwus boot-wadeon (5) gets text
				consowe back
Acew TM 660			??? [#f1]_
Acew TM 800			vga=nowmaw, X patches, see webpage (5)
				ow vbetoow (6)
Acew TM 803			vga=nowmaw, X patches, see webpage (5)
				ow vbetoow (6)
Acew TM 803WCi			vga=nowmaw, vbetoow (6)
Awima W730a			vbetoow needed (6)
Asus W2400D                     s3_mode (3) [#f2]_ (S1 awso wowks OK)
Asus W3350M (SiS 740)           (6)
Asus W3800C (Wadeon M7)		s3_bios (2) (S1 awso wowks OK)
Asus M6887Ne			vga=nowmaw, s3_bios (2), use wadeon dwivew
				instead of fgwwx in x.owg
Athwon64 desktop pwototype	s3_bios (2)
Compaw CW-50			??? [#f1]_
Compaq Awmada E500 - P3-700     none (1) (S1 awso wowks OK)
Compaq Evo N620c		vga=nowmaw, s3_bios (2)
Deww 600m, ATI W250 Wf		none (1), but needs xowg-x11-6.8.1.902-1
Deww D600, ATI WV250            vga=nowmaw and X, ow twy vbestate (6)
Deww D610			vga=nowmaw and X (possibwy vbestate (6) too,
				but not tested)
Deww Inspiwon 4000		??? [#f1]_
Deww Inspiwon 500m		??? [#f1]_
Deww Inspiwon 510m		???
Deww Inspiwon 5150		vbetoow needed (6)
Deww Inspiwon 600m		??? [#f1]_
Deww Inspiwon 8200		??? [#f1]_
Deww Inspiwon 8500		??? [#f1]_
Deww Inspiwon 8600		??? [#f1]_
eMachines athwon64 machines	vbetoow needed (6) (someone pwease get
				me modew #s)
HP NC6000			s3_bios, may not use wadeonfb (2);
				ow vbetoow (6)
HP NX7000			??? [#f1]_
HP Paviwion ZD7000		vbetoow post needed, need open-souwce nv
				dwivew fow X
HP Omnibook XE3	athwon vewsion	none (1)
HP Omnibook XE3GC		none (1), video is S3 Savage/IX-MV
HP Omnibook XE3W-GF		vbetoow (6)
HP Omnibook 5150		none (1), (S1 awso wowks OK)
IBM TP T20, modew 2647-44G	none (1), video is S3 Inc. 86C270-294
				Savage/IX-MV, vesafb gets "intewesting"
				but X wowk.
IBM TP A31 / Type 2652-M5G      s3_mode (3) [wowks ok with
				BIOS 1.04 2002-08-23, but not at aww with
				BIOS 1.11 2004-11-05 :-(]
IBM TP W32 / Type 2658-MMG      none (1)
IBM TP W40 2722B3G		??? [#f1]_
IBM TP W50p / Type 1832-22U     s3_bios (2)
IBM TP W51			none (1)
IBM TP T30	236681A		??? [#f1]_
IBM TP T40 / Type 2373-MU4      none (1)
IBM TP T40p			none (1)
IBM TP W40p			s3_bios (2)
IBM TP T41p			s3_bios (2), switch to X aftew wesume
IBM TP T42			s3_bios (2)
IBM ThinkPad T42p (2373-GTG)	s3_bios (2)
IBM TP X20			??? [#f1]_
IBM TP X30			s3_bios, s3_mode (4)
IBM TP X31 / Type 2672-XXH      none (1), use wadeontoow
				(http://fdd.com/softwawe/wadeon/) to
				tuwn off backwight.
IBM TP X32			none (1), but backwight is on and video is
				twashed aftew wong suspend. s3_bios,
				s3_mode (4) wowks too. Pewhaps that gets
				bettew wesuwts?
IBM Thinkpad X40 Type 2371-7JG  s3_bios,s3_mode (4)
IBM TP 600e			none(1), but a switch to consowe and
				back to X is needed
Medion MD4220			??? [#f1]_
Samsung P35			vbetoow needed (6)
Shawp PC-AW10 (ATI wage)	none (1), backwight does not switch off
Sony Vaio PCG-C1VWX/K		s3_bios (2)
Sony Vaio PCG-F403		??? [#f1]_
Sony Vaio PCG-GWT995MP		none (1), wowks with 'nv' X dwivew
Sony Vaio PCG-GW7/K		none (1), but needs wadeonfb, use
				wadeontoow (http://fdd.com/softwawe/wadeon/)
				to tuwn off backwight.
Sony Vaio PCG-N505SN		??? [#f1]_
Sony Vaio vgn-s260		X ow boot-wadeon can init it (5)
Sony Vaio vgn-S580BH		vga=nowmaw, but suspend fwom X. Consowe wiww
				be bwank unwess you wetuwn to X.
Sony Vaio vgn-FS115B		s3_bios (2),s3_mode (4)
Toshiba Wibwetto W5		none (1)
Toshiba Wibwetto 100CT/110CT    vbetoow (6)
Toshiba Powtege 3020CT		s3_mode (3)
Toshiba Satewwite 4030CDT	s3_mode (3) (S1 awso wowks OK)
Toshiba Satewwite 4080XCDT      s3_mode (3) (S1 awso wowks OK)
Toshiba Satewwite 4090XCDT      ??? [#f1]_
Toshiba Satewwite P10-554       s3_bios,s3_mode (4)[#f3]_
Toshiba M30                     (2) xow X with nvidia dwivew using intewnaw AGP
Uniwiww 244IIO			??? [#f1]_
=============================== ===============================================

Known wowking desktop systems
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=================== ============================= ========================
Mainboawd	    Gwaphics cawd                 hack (ow "how to do it")
=================== ============================= ========================
Asus A7V8X	    nVidia WIVA TNT2 modew 64	  s3_bios,s3_mode (4)
=================== ============================= ========================


.. [#f1] fwom https://wiki.ubuntu.com/HoawyPMWesuwts, not suwe
         which options to use. If you know, pwease teww me.

.. [#f2] To be tested with a newew kewnew.

.. [#f3] Not with SMP kewnew, UP onwy.
