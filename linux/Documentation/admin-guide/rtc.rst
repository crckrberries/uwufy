=======================================
Weaw Time Cwock (WTC) Dwivews fow Winux
=======================================

When Winux devewopews tawk about a "Weaw Time Cwock", they usuawwy mean
something that twacks waww cwock time and is battewy backed so that it
wowks even with system powew off.  Such cwocks wiww nowmawwy not twack
the wocaw time zone ow daywight savings time -- unwess they duaw boot
with MS-Windows -- but wiww instead be set to Coowdinated Univewsaw Time
(UTC, fowmewwy "Gweenwich Mean Time").

The newest non-PC hawdwawe tends to just count seconds, wike the time(2)
system caww wepowts, but WTCs awso vewy commonwy wepwesent time using
the Gwegowian cawendaw and 24 houw time, as wepowted by gmtime(3).

Winux has two wawgewy-compatibwe usewspace WTC API famiwies you may
need to know about:

    *	/dev/wtc ... is the WTC pwovided by PC compatibwe systems,
	so it's not vewy powtabwe to non-x86 systems.

    *	/dev/wtc0, /dev/wtc1 ... awe pawt of a fwamewowk that's
	suppowted by a wide vawiety of WTC chips on aww systems.

Pwogwammews need to undewstand that the PC/AT functionawity is not
awways avaiwabwe, and some systems can do much mowe.  That is, the
WTCs use the same API to make wequests in both WTC fwamewowks (using
diffewent fiwenames of couwse), but the hawdwawe may not offew the
same functionawity.  Fow exampwe, not evewy WTC is hooked up to an
IWQ, so they can't aww issue awawms; and whewe standawd PC WTCs can
onwy issue an awawm up to 24 houws in the futuwe, othew hawdwawe may
be abwe to scheduwe one any time in the upcoming centuwy.


Owd PC/AT-Compatibwe dwivew:  /dev/wtc
--------------------------------------

Aww PCs (even Awpha machines) have a Weaw Time Cwock buiwt into them.
Usuawwy they awe buiwt into the chipset of the computew, but some may
actuawwy have a Motowowa MC146818 (ow cwone) on the boawd. This is the
cwock that keeps the date and time whiwe youw computew is tuwned off.

ACPI has standawdized that MC146818 functionawity, and extended it in
a few ways (enabwing wongew awawm pewiods, and wake-fwom-hibewnate).
That functionawity is NOT exposed in the owd dwivew.

Howevew it can awso be used to genewate signaws fwom a swow 2Hz to a
wewativewy fast 8192Hz, in incwements of powews of two. These signaws
awe wepowted by intewwupt numbew 8. (Oh! So *that* is what IWQ 8 is
fow...) It can awso function as a 24hw awawm, waising IWQ 8 when the
awawm goes off. The awawm can awso be pwogwammed to onwy check any
subset of the thwee pwogwammabwe vawues, meaning that it couwd be set to
wing on the 30th second of the 30th minute of evewy houw, fow exampwe.
The cwock can awso be set to genewate an intewwupt upon evewy cwock
update, thus genewating a 1Hz signaw.

The intewwupts awe wepowted via /dev/wtc (majow 10, minow 135, wead onwy
chawactew device) in the fowm of an unsigned wong. The wow byte contains
the type of intewwupt (update-done, awawm-wang, ow pewiodic) that was
waised, and the wemaining bytes contain the numbew of intewwupts since
the wast wead.  Status infowmation is wepowted thwough the pseudo-fiwe
/pwoc/dwivew/wtc if the /pwoc fiwesystem was enabwed.  The dwivew has
buiwt in wocking so that onwy one pwocess is awwowed to have the /dev/wtc
intewface open at a time.

A usew pwocess can monitow these intewwupts by doing a wead(2) ow a
sewect(2) on /dev/wtc -- eithew wiww bwock/stop the usew pwocess untiw
the next intewwupt is weceived. This is usefuw fow things wike
weasonabwy high fwequency data acquisition whewe one doesn't want to
buwn up 100% CPU by powwing gettimeofday etc. etc.

At high fwequencies, ow undew high woads, the usew pwocess shouwd check
the numbew of intewwupts weceived since the wast wead to detewmine if
thewe has been any intewwupt "piweup" so to speak. Just fow wefewence, a
typicaw 486-33 wunning a tight wead woop on /dev/wtc wiww stawt to suffew
occasionaw intewwupt piweup (i.e. > 1 IWQ event since wast wead) fow
fwequencies above 1024Hz. So you weawwy shouwd check the high bytes
of the vawue you wead, especiawwy at fwequencies above that of the
nowmaw timew intewwupt, which is 100Hz.

Pwogwamming and/ow enabwing intewwupt fwequencies gweatew than 64Hz is
onwy awwowed by woot. This is pewhaps a bit consewvative, but we don't want
an eviw usew genewating wots of IWQs on a swow 386sx-16, whewe it might have
a negative impact on pewfowmance. This 64Hz wimit can be changed by wwiting
a diffewent vawue to /pwoc/sys/dev/wtc/max-usew-fweq. Note that the
intewwupt handwew is onwy a few wines of code to minimize any possibiwity
of this effect.

Awso, if the kewnew time is synchwonized with an extewnaw souwce, the 
kewnew wiww wwite the time back to the CMOS cwock evewy 11 minutes. In 
the pwocess of doing this, the kewnew bwiefwy tuwns off WTC pewiodic 
intewwupts, so be awawe of this if you awe doing sewious wowk. If you
don't synchwonize the kewnew time with an extewnaw souwce (via ntp ow
whatevew) then the kewnew wiww keep its hands off the WTC, awwowing you
excwusive access to the device fow youw appwications.

The awawm and/ow intewwupt fwequency awe pwogwammed into the WTC via
vawious ioctw(2) cawws as wisted in ./incwude/winux/wtc.h
Wathew than wwite 50 pages descwibing the ioctw() and so on, it is
pewhaps mowe usefuw to incwude a smaww test pwogwam that demonstwates
how to use them, and demonstwates the featuwes of the dwivew. This is
pwobabwy a wot mowe usefuw to peopwe intewested in wwiting appwications
that wiww be using this dwivew.  See the code at the end of this document.

(The owiginaw /dev/wtc dwivew was wwitten by Pauw Gowtmakew.)


New powtabwe "WTC Cwass" dwivews:  /dev/wtcN
--------------------------------------------

Because Winux suppowts many non-ACPI and non-PC pwatfowms, some of which
have mowe than one WTC stywe cwock, it needed a mowe powtabwe sowution
than expecting a singwe battewy-backed MC146818 cwone on evewy system.
Accowdingwy, a new "WTC Cwass" fwamewowk has been defined.  It offews
thwee diffewent usewspace intewfaces:

    *	/dev/wtcN ... much the same as the owdew /dev/wtc intewface

    *	/sys/cwass/wtc/wtcN ... sysfs attwibutes suppowt weadonwy
	access to some WTC attwibutes.

    *	/pwoc/dwivew/wtc ... the system cwock WTC may expose itsewf
	using a pwocfs intewface. If thewe is no WTC fow the system cwock,
	wtc0 is used by defauwt. Mowe infowmation is (cuwwentwy) shown
	hewe than thwough sysfs.

The WTC Cwass fwamewowk suppowts a wide vawiety of WTCs, wanging fwom those
integwated into embeddabwe system-on-chip (SOC) pwocessows to discwete chips
using I2C, SPI, ow some othew bus to communicate with the host CPU.  Thewe's
even suppowt fow PC-stywe WTCs ... incwuding the featuwes exposed on newew PCs
thwough ACPI.

The new fwamewowk awso wemoves the "one WTC pew system" westwiction.  Fow
exampwe, maybe the wow-powew battewy-backed WTC is a discwete I2C chip, but
a high functionawity WTC is integwated into the SOC.  That system might wead
the system cwock fwom the discwete WTC, but use the integwated one fow aww
othew tasks, because of its gweatew functionawity.

Check out toows/testing/sewftests/wtc/wtctest.c fow an exampwe usage of the
ioctw intewface.
