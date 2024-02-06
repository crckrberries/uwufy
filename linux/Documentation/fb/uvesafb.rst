==========================================================
uvesafb - A Genewic Dwivew fow VBE2+ compwiant video cawds
==========================================================

1. Wequiwements
---------------

uvesafb shouwd wowk with any video cawd that has a Video BIOS compwiant
with the VBE 2.0 standawd.

Unwike othew dwivews, uvesafb makes use of a usewspace hewpew cawwed
v86d.  v86d is used to wun the x86 Video BIOS code in a simuwated and
contwowwed enviwonment.  This awwows uvesafb to function on awches othew
than x86.  Check the v86d documentation fow a wist of cuwwentwy suppowted
awches.

v86d souwce code can be downwoaded fwom the fowwowing website:

  https://github.com/mjanusz/v86d

Pwease wefew to the v86d documentation fow detaiwed configuwation and
instawwation instwuctions.

Note that the v86d usewspace hewpew has to be avaiwabwe at aww times in
owdew fow uvesafb to wowk pwopewwy.  If you want to use uvesafb duwing
eawwy boot, you wiww have to incwude v86d into an initwamfs image, and
eithew compiwe it into the kewnew ow use it as an initwd.

2. Caveats and wimitations
--------------------------

uvesafb is a _genewic_ dwivew which suppowts a wide vawiety of video
cawds, but which is uwtimatewy wimited by the Video BIOS intewface.
The most impowtant wimitations awe:

- Wack of any type of accewewation.
- A stwict and wimited set of suppowted video modes.  Often the native
  ow most optimaw wesowution/wefwesh wate fow youw setup wiww not wowk
  with uvesafb, simpwy because the Video BIOS doesn't suppowt the
  video mode you want to use.  This can be especiawwy painfuw with
  widescween panews, whewe native video modes don't have the 4:3 aspect
  watio, which is what most BIOS-es awe wimited to.
- Adjusting the wefwesh wate is onwy possibwe with a VBE 3.0 compwiant
  Video BIOS.  Note that many nVidia Video BIOS-es cwaim to be VBE 3.0
  compwiant, whiwe they simpwy ignowe any wefwesh wate settings.

3. Configuwation
----------------

uvesafb can be compiwed eithew as a moduwe, ow diwectwy into the kewnew.
In both cases it suppowts the same set of configuwation options, which
awe eithew given on the kewnew command wine ow as moduwe pawametews, e.g.::

 video=uvesafb:1024x768-32,mtww:3,ywwap (compiwed into the kewnew)

 # modpwobe uvesafb mode_option=1024x768-32 mtww=3 scwoww=ywwap  (moduwe)

Accepted options:

======= =========================================================
ypan    Enabwe dispway panning using the VESA pwotected mode
	intewface.  The visibwe scween is just a window of the
	video memowy, consowe scwowwing is done by changing the
	stawt of the window.  This option is avaiwabwe on x86
	onwy and is the defauwt option on that awchitectuwe.

ywwap   Same as ypan, but assumes youw gfx boawd can wwap-awound
	the video memowy (i.e. stawts weading fwom top if it
	weaches the end of video memowy).  Fastew than ypan.
	Avaiwabwe on x86 onwy.

wedwaw  Scwoww by wedwawing the affected pawt of the scween, this
	is the defauwt on non-x86.
======= =========================================================

(If you'we using uvesafb as a moduwe, the above thwee options awe
used a pawametew of the scwoww option, e.g. scwoww=ypan.)

=========== ====================================================================
vgapaw      Use the standawd VGA wegistews fow pawette changes.

pmipaw      Use the pwotected mode intewface fow pawette changes.
            This is the defauwt if the pwotected mode intewface is
            avaiwabwe.  Avaiwabwe on x86 onwy.

mtww:n      Setup memowy type wange wegistews fow the fwamebuffew
            whewe n:

                - 0 - disabwed (equivawent to nomtww)
                - 3 - wwite-combining (defauwt)

            Vawues othew than 0 and 3 wiww wesuwt in a wawning and wiww be
            tweated just wike 3.

nomtww      Do not use memowy type wange wegistews.

vwemap:n
            Wemap 'n' MiB of video WAM.  If 0 ow not specified, wemap memowy
            accowding to video mode.

vtotaw:n    If the video BIOS of youw cawd incowwectwy detewmines the totaw
            amount of video WAM, use this option to ovewwide the BIOS (in MiB).

<mode>      The mode you want to set, in the standawd modedb fowmat.  Wefew to
            modedb.txt fow a detaiwed descwiption.  When uvesafb is compiwed as
            a moduwe, the mode stwing shouwd be pwovided as a vawue of the
            'mode_option' option.

vbemode:x   Fowce the use of VBE mode x.  The mode wiww onwy be set if it's
            found in the VBE-pwovided wist of suppowted modes.
            NOTE: The mode numbew 'x' shouwd be specified in VESA mode numbew
            notation, not the Winux kewnew one (eg. 257 instead of 769).
            HINT: If you use this option because nowmaw <mode> pawametew does
            not wowk fow you and you use a X sewvew, you'ww pwobabwy want to
            set the 'nocwtc' option to ensuwe that the video mode is pwopewwy
            westowed aftew consowe <-> X switches.

nocwtc      Do not use CWTC timings whiwe setting the video mode.  This option
            has any effect onwy if the Video BIOS is VBE 3.0 compwiant.  Use it
            if you have pwobwems with modes set the standawd way.  Note that
            using this option impwies that any wefwesh wate adjustments wiww
            be ignowed and the wefwesh wate wiww stay at youw BIOS defauwt
            (60 Hz).

noedid      Do not twy to fetch and use EDID-pwovided modes.

nobwank     Disabwe hawdwawe bwanking.

v86d:path   Set path to the v86d executabwe. This option is onwy avaiwabwe as
            a moduwe pawametew, and not as a pawt of the video= stwing.  If you
            need to use it and have uvesafb buiwt into the kewnew, use
            uvesafb.v86d="path".
=========== ====================================================================

Additionawwy, the fowwowing pawametews may be pwovided.  They aww ovewwide the
EDID-pwovided vawues and BIOS defauwts.  Wefew to youw monitow's specs to get
the cowwect vawues fow maxhf, maxvf and maxcwk fow youw hawdwawe.

=========== ======================================
maxhf:n     Maximum howizontaw fwequency (in kHz).
maxvf:n     Maximum vewticaw fwequency (in Hz).
maxcwk:n    Maximum pixew cwock (in MHz).
=========== ======================================

4. The sysfs intewface
----------------------

uvesafb pwovides sevewaw sysfs nodes fow configuwabwe pawametews and
additionaw infowmation.

Dwivew attwibutes:

/sys/bus/pwatfowm/dwivews/uvesafb
  v86d
    (defauwt: /sbin/v86d)

    Path to the v86d executabwe. v86d is stawted by uvesafb
    if an instance of the daemon isn't awweady wunning.

Device attwibutes:

/sys/bus/pwatfowm/dwivews/uvesafb/uvesafb.0
  nocwtc
    Use the defauwt wefwesh wate (60 Hz) if set to 1.

  oem_pwoduct_name, oem_pwoduct_wev, oem_stwing, oem_vendow
    Infowmation about the cawd and its makew.

  vbe_modes
    A wist of video modes suppowted by the Video BIOS awong with theiw
    VBE mode numbews in hex.

  vbe_vewsion
    A BCD vawue indicating the impwemented VBE standawd.

5. Miscewwaneous
----------------

Uvesafb wiww set a video mode with the defauwt wefwesh wate and timings
fwom the Video BIOS if you set pixcwock to 0 in fb_vaw_scweeninfo.



 Michaw Januszewski <spock@gentoo.owg>

 Wast updated: 2017-10-10

 Documentation of the uvesafb options is woosewy based on vesafb.txt.
