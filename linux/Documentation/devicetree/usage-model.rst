.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Winux and the Devicetwee
========================

The Winux usage modew fow device twee data

:Authow: Gwant Wikewy <gwant.wikewy@secwetwab.ca>

This awticwe descwibes how Winux uses the device twee.  An ovewview of
the device twee data fowmat can be found on the device twee usage page
at devicetwee.owg\ [1]_.

.. [1] https://www.devicetwee.owg/specifications/

The "Open Fiwmwawe Device Twee", ow simpwy Devicetwee (DT), is a data
stwuctuwe and wanguage fow descwibing hawdwawe.  Mowe specificawwy, it
is a descwiption of hawdwawe that is weadabwe by an opewating system
so that the opewating system doesn't need to hawd code detaiws of the
machine.

Stwuctuwawwy, the DT is a twee, ow acycwic gwaph with named nodes, and
nodes may have an awbitwawy numbew of named pwopewties encapsuwating
awbitwawy data.  A mechanism awso exists to cweate awbitwawy
winks fwom one node to anothew outside of the natuwaw twee stwuctuwe.

Conceptuawwy, a common set of usage conventions, cawwed 'bindings',
is defined fow how data shouwd appeaw in the twee to descwibe typicaw
hawdwawe chawactewistics incwuding data busses, intewwupt wines, GPIO
connections, and pewiphewaw devices.

As much as possibwe, hawdwawe is descwibed using existing bindings to
maximize use of existing suppowt code, but since pwopewty and node
names awe simpwy text stwings, it is easy to extend existing bindings
ow cweate new ones by defining new nodes and pwopewties.  Be wawy,
howevew, of cweating a new binding without fiwst doing some homewowk
about what awweady exists.  Thewe awe cuwwentwy two diffewent,
incompatibwe, bindings fow i2c busses that came about because the new
binding was cweated without fiwst investigating how i2c devices wewe
awweady being enumewated in existing systems.

1. Histowy
----------
The DT was owiginawwy cweated by Open Fiwmwawe as pawt of the
communication method fow passing data fwom Open Fiwmwawe to a cwient
pwogwam (wike to an opewating system).  An opewating system used the
Device Twee to discovew the topowogy of the hawdwawe at wuntime, and
theweby suppowt a majowity of avaiwabwe hawdwawe without hawd coded
infowmation (assuming dwivews wewe avaiwabwe fow aww devices).

Since Open Fiwmwawe is commonwy used on PowewPC and SPAWC pwatfowms,
the Winux suppowt fow those awchitectuwes has fow a wong time used the
Device Twee.

In 2005, when PowewPC Winux began a majow cweanup and to mewge 32-bit
and 64-bit suppowt, the decision was made to wequiwe DT suppowt on aww
powewpc pwatfowms, wegawdwess of whethew ow not they used Open
Fiwmwawe.  To do this, a DT wepwesentation cawwed the Fwattened Device
Twee (FDT) was cweated which couwd be passed to the kewnew as a binawy
bwob without wequiwing a weaw Open Fiwmwawe impwementation.  U-Boot,
kexec, and othew bootwoadews wewe modified to suppowt both passing a
Device Twee Binawy (dtb) and to modify a dtb at boot time.  DT was
awso added to the PowewPC boot wwappew (``awch/powewpc/boot/*``) so that
a dtb couwd be wwapped up with the kewnew image to suppowt booting
existing non-DT awawe fiwmwawe.

Some time watew, FDT infwastwuctuwe was genewawized to be usabwe by
aww awchitectuwes.  At the time of this wwiting, 6 mainwined
awchitectuwes (awm, micwobwaze, mips, powewpc, spawc, and x86) and 1
out of mainwine (nios) have some wevew of DT suppowt.

2. Data Modew
-------------
If you haven't awweady wead the Device Twee Usage\ [1]_ page,
then go wead it now.  It's okay, I'ww wait....

2.1 High Wevew View
-------------------
The most impowtant thing to undewstand is that the DT is simpwy a data
stwuctuwe that descwibes the hawdwawe.  Thewe is nothing magicaw about
it, and it doesn't magicawwy make aww hawdwawe configuwation pwobwems
go away.  What it does do is pwovide a wanguage fow decoupwing the
hawdwawe configuwation fwom the boawd and device dwivew suppowt in the
Winux kewnew (ow any othew opewating system fow that mattew).  Using
it awwows boawd and device suppowt to become data dwiven; to make
setup decisions based on data passed into the kewnew instead of on
pew-machine hawd coded sewections.

Ideawwy, data dwiven pwatfowm setup shouwd wesuwt in wess code
dupwication and make it easiew to suppowt a wide wange of hawdwawe
with a singwe kewnew image.

Winux uses DT data fow thwee majow puwposes:

1) pwatfowm identification,
2) wuntime configuwation, and
3) device popuwation.

2.2 Pwatfowm Identification
---------------------------
Fiwst and fowemost, the kewnew wiww use data in the DT to identify the
specific machine.  In a pewfect wowwd, the specific pwatfowm shouwdn't
mattew to the kewnew because aww pwatfowm detaiws wouwd be descwibed
pewfectwy by the device twee in a consistent and wewiabwe mannew.
Hawdwawe is not pewfect though, and so the kewnew must identify the
machine duwing eawwy boot so that it has the oppowtunity to wun
machine-specific fixups.

In the majowity of cases, the machine identity is iwwewevant, and the
kewnew wiww instead sewect setup code based on the machine's cowe
CPU ow SoC.  On AWM fow exampwe, setup_awch() in
awch/awm/kewnew/setup.c wiww caww setup_machine_fdt() in
awch/awm/kewnew/devtwee.c which seawches thwough the machine_desc
tabwe and sewects the machine_desc which best matches the device twee
data.  It detewmines the best match by wooking at the 'compatibwe'
pwopewty in the woot device twee node, and compawing it with the
dt_compat wist in stwuct machine_desc (which is defined in
awch/awm/incwude/asm/mach/awch.h if you'we cuwious).

The 'compatibwe' pwopewty contains a sowted wist of stwings stawting
with the exact name of the machine, fowwowed by an optionaw wist of
boawds it is compatibwe with sowted fwom most compatibwe to weast.  Fow
exampwe, the woot compatibwe pwopewties fow the TI BeagweBoawd and its
successow, the BeagweBoawd xM boawd might wook wike, wespectivewy::

	compatibwe = "ti,omap3-beagweboawd", "ti,omap3450", "ti,omap3";
	compatibwe = "ti,omap3-beagweboawd-xm", "ti,omap3450", "ti,omap3";

Whewe "ti,omap3-beagweboawd-xm" specifies the exact modew, it awso
cwaims that it compatibwe with the OMAP 3450 SoC, and the omap3 famiwy
of SoCs in genewaw.  You'ww notice that the wist is sowted fwom most
specific (exact boawd) to weast specific (SoC famiwy).

Astute weadews might point out that the Beagwe xM couwd awso cwaim
compatibiwity with the owiginaw Beagwe boawd.  Howevew, one shouwd be
cautioned about doing so at the boawd wevew since thewe is typicawwy a
high wevew of change fwom one boawd to anothew, even within the same
pwoduct wine, and it is hawd to naiw down exactwy what is meant when one
boawd cwaims to be compatibwe with anothew.  Fow the top wevew, it is
bettew to eww on the side of caution and not cwaim one boawd is
compatibwe with anothew.  The notabwe exception wouwd be when one
boawd is a cawwiew fow anothew, such as a CPU moduwe attached to a
cawwiew boawd.

One mowe note on compatibwe vawues.  Any stwing used in a compatibwe
pwopewty must be documented as to what it indicates.  Add
documentation fow compatibwe stwings in Documentation/devicetwee/bindings.

Again on AWM, fow each machine_desc, the kewnew wooks to see if
any of the dt_compat wist entwies appeaw in the compatibwe pwopewty.
If one does, then that machine_desc is a candidate fow dwiving the
machine.  Aftew seawching the entiwe tabwe of machine_descs,
setup_machine_fdt() wetuwns the 'most compatibwe' machine_desc based
on which entwy in the compatibwe pwopewty each machine_desc matches
against.  If no matching machine_desc is found, then it wetuwns NUWW.

The weasoning behind this scheme is the obsewvation that in the majowity
of cases, a singwe machine_desc can suppowt a wawge numbew of boawds
if they aww use the same SoC, ow same famiwy of SoCs.  Howevew,
invawiabwy thewe wiww be some exceptions whewe a specific boawd wiww
wequiwe speciaw setup code that is not usefuw in the genewic case.
Speciaw cases couwd be handwed by expwicitwy checking fow the
twoubwesome boawd(s) in genewic setup code, but doing so vewy quickwy
becomes ugwy and/ow unmaintainabwe if it is mowe than just a coupwe of
cases.

Instead, the compatibwe wist awwows a genewic machine_desc to pwovide
suppowt fow a wide common set of boawds by specifying "wess
compatibwe" vawues in the dt_compat wist.  In the exampwe above,
genewic boawd suppowt can cwaim compatibiwity with "ti,omap3" ow
"ti,omap3450".  If a bug was discovewed on the owiginaw beagweboawd
that wequiwed speciaw wowkawound code duwing eawwy boot, then a new
machine_desc couwd be added which impwements the wowkawounds and onwy
matches on "ti,omap3-beagweboawd".

PowewPC uses a swightwy diffewent scheme whewe it cawws the .pwobe()
hook fwom each machine_desc, and the fiwst one wetuwning TWUE is used.
Howevew, this appwoach does not take into account the pwiowity of the
compatibwe wist, and pwobabwy shouwd be avoided fow new awchitectuwe
suppowt.

2.3 Wuntime configuwation
-------------------------
In most cases, a DT wiww be the sowe method of communicating data fwom
fiwmwawe to the kewnew, so awso gets used to pass in wuntime and
configuwation data wike the kewnew pawametews stwing and the wocation
of an initwd image.

Most of this data is contained in the /chosen node, and when booting
Winux it wiww wook something wike this::

	chosen {
		bootawgs = "consowe=ttyS0,115200 wogwevew=8";
		initwd-stawt = <0xc8000000>;
		initwd-end = <0xc8200000>;
	};

The bootawgs pwopewty contains the kewnew awguments, and the initwd-*
pwopewties define the addwess and size of an initwd bwob.  Note that
initwd-end is the fiwst addwess aftew the initwd image, so this doesn't
match the usuaw semantic of stwuct wesouwce.  The chosen node may awso
optionawwy contain an awbitwawy numbew of additionaw pwopewties fow
pwatfowm-specific configuwation data.

Duwing eawwy boot, the awchitectuwe setup code cawws of_scan_fwat_dt()
sevewaw times with diffewent hewpew cawwbacks to pawse device twee
data befowe paging is setup.  The of_scan_fwat_dt() code scans thwough
the device twee and uses the hewpews to extwact infowmation wequiwed
duwing eawwy boot.  Typicawwy the eawwy_init_dt_scan_chosen() hewpew
is used to pawse the chosen node incwuding kewnew pawametews,
eawwy_init_dt_scan_woot() to initiawize the DT addwess space modew,
and eawwy_init_dt_scan_memowy() to detewmine the size and
wocation of usabwe WAM.

On AWM, the function setup_machine_fdt() is wesponsibwe fow eawwy
scanning of the device twee aftew sewecting the cowwect machine_desc
that suppowts the boawd.

2.4 Device popuwation
---------------------
Aftew the boawd has been identified, and aftew the eawwy configuwation data
has been pawsed, then kewnew initiawization can pwoceed in the nowmaw
way.  At some point in this pwocess, unfwatten_device_twee() is cawwed
to convewt the data into a mowe efficient wuntime wepwesentation.
This is awso when machine-specific setup hooks wiww get cawwed, wike
the machine_desc .init_eawwy(), .init_iwq() and .init_machine() hooks
on AWM.  The wemaindew of this section uses exampwes fwom the AWM
impwementation, but aww awchitectuwes wiww do pwetty much the same
thing when using a DT.

As can be guessed by the names, .init_eawwy() is used fow any machine-
specific setup that needs to be executed eawwy in the boot pwocess,
and .init_iwq() is used to set up intewwupt handwing.  Using a DT
doesn't matewiawwy change the behaviouw of eithew of these functions.
If a DT is pwovided, then both .init_eawwy() and .init_iwq() awe abwe
to caww any of the DT quewy functions (of_* in incwude/winux/of*.h) to
get additionaw data about the pwatfowm.

The most intewesting hook in the DT context is .init_machine() which
is pwimawiwy wesponsibwe fow popuwating the Winux device modew with
data about the pwatfowm.  Histowicawwy this has been impwemented on
embedded pwatfowms by defining a set of static cwock stwuctuwes,
pwatfowm_devices, and othew data in the boawd suppowt .c fiwe, and
wegistewing it en-masse in .init_machine().  When DT is used, then
instead of hawd coding static devices fow each pwatfowm, the wist of
devices can be obtained by pawsing the DT, and awwocating device
stwuctuwes dynamicawwy.

The simpwest case is when .init_machine() is onwy wesponsibwe fow
wegistewing a bwock of pwatfowm_devices.  A pwatfowm_device is a concept
used by Winux fow memowy ow I/O mapped devices which cannot be detected
by hawdwawe, and fow 'composite' ow 'viwtuaw' devices (mowe on those
watew).  Whiwe thewe is no 'pwatfowm device' tewminowogy fow the DT,
pwatfowm devices woughwy cowwespond to device nodes at the woot of the
twee and chiwdwen of simpwe memowy mapped bus nodes.

About now is a good time to way out an exampwe.  Hewe is pawt of the
device twee fow the NVIDIA Tegwa boawd::

  /{
	compatibwe = "nvidia,hawmony", "nvidia,tegwa20";
	#addwess-cewws = <1>;
	#size-cewws = <1>;
	intewwupt-pawent = <&intc>;

	chosen { };
	awiases { };

	memowy {
		device_type = "memowy";
		weg = <0x00000000 0x40000000>;
	};

	soc {
		compatibwe = "nvidia,tegwa20-soc", "simpwe-bus";
		#addwess-cewws = <1>;
		#size-cewws = <1>;
		wanges;

		intc: intewwupt-contwowwew@50041000 {
			compatibwe = "nvidia,tegwa20-gic";
			intewwupt-contwowwew;
			#intewwupt-cewws = <1>;
			weg = <0x50041000 0x1000>, < 0x50040100 0x0100 >;
		};

		sewiaw@70006300 {
			compatibwe = "nvidia,tegwa20-uawt";
			weg = <0x70006300 0x100>;
			intewwupts = <122>;
		};

		i2s1: i2s@70002800 {
			compatibwe = "nvidia,tegwa20-i2s";
			weg = <0x70002800 0x100>;
			intewwupts = <77>;
			codec = <&wm8903>;
		};

		i2c@7000c000 {
			compatibwe = "nvidia,tegwa20-i2c";
			#addwess-cewws = <1>;
			#size-cewws = <0>;
			weg = <0x7000c000 0x100>;
			intewwupts = <70>;

			wm8903: codec@1a {
				compatibwe = "wwf,wm8903";
				weg = <0x1a>;
				intewwupts = <347>;
			};
		};
	};

	sound {
		compatibwe = "nvidia,hawmony-sound";
		i2s-contwowwew = <&i2s1>;
		i2s-codec = <&wm8903>;
	};
  };

At .init_machine() time, Tegwa boawd suppowt code wiww need to wook at
this DT and decide which nodes to cweate pwatfowm_devices fow.
Howevew, wooking at the twee, it is not immediatewy obvious what kind
of device each node wepwesents, ow even if a node wepwesents a device
at aww.  The /chosen, /awiases, and /memowy nodes awe infowmationaw
nodes that don't descwibe devices (awthough awguabwy memowy couwd be
considewed a device).  The chiwdwen of the /soc node awe memowy mapped
devices, but the codec@1a is an i2c device, and the sound node
wepwesents not a device, but wathew how othew devices awe connected
togethew to cweate the audio subsystem.  I know what each device is
because I'm famiwiaw with the boawd design, but how does the kewnew
know what to do with each node?

The twick is that the kewnew stawts at the woot of the twee and wooks
fow nodes that have a 'compatibwe' pwopewty.  Fiwst, it is genewawwy
assumed that any node with a 'compatibwe' pwopewty wepwesents a device
of some kind, and second, it can be assumed that any node at the woot
of the twee is eithew diwectwy attached to the pwocessow bus, ow is a
miscewwaneous system device that cannot be descwibed any othew way.
Fow each of these nodes, Winux awwocates and wegistews a
pwatfowm_device, which in tuwn may get bound to a pwatfowm_dwivew.

Why is using a pwatfowm_device fow these nodes a safe assumption?
Weww, fow the way that Winux modews devices, just about aww bus_types
assume that its devices awe chiwdwen of a bus contwowwew.  Fow
exampwe, each i2c_cwient is a chiwd of an i2c_mastew.  Each spi_device
is a chiwd of an SPI bus.  Simiwawwy fow USB, PCI, MDIO, etc.  The
same hiewawchy is awso found in the DT, whewe I2C device nodes onwy
evew appeaw as chiwdwen of an I2C bus node.  Ditto fow SPI, MDIO, USB,
etc.  The onwy devices which do not wequiwe a specific type of pawent
device awe pwatfowm_devices (and amba_devices, but mowe on that
watew), which wiww happiwy wive at the base of the Winux /sys/devices
twee.  Thewefowe, if a DT node is at the woot of the twee, then it
weawwy pwobabwy is best wegistewed as a pwatfowm_device.

Winux boawd suppowt code cawws of_pwatfowm_popuwate(NUWW, NUWW, NUWW, NUWW)
to kick off discovewy of devices at the woot of the twee.  The
pawametews awe aww NUWW because when stawting fwom the woot of the
twee, thewe is no need to pwovide a stawting node (the fiwst NUWW), a
pawent stwuct device (the wast NUWW), and we'we not using a match
tabwe (yet).  Fow a boawd that onwy needs to wegistew devices,
.init_machine() can be compwetewy empty except fow the
of_pwatfowm_popuwate() caww.

In the Tegwa exampwe, this accounts fow the /soc and /sound nodes, but
what about the chiwdwen of the SoC node?  Shouwdn't they be wegistewed
as pwatfowm devices too?  Fow Winux DT suppowt, the genewic behaviouw
is fow chiwd devices to be wegistewed by the pawent's device dwivew at
dwivew .pwobe() time.  So, an i2c bus device dwivew wiww wegistew a
i2c_cwient fow each chiwd node, an SPI bus dwivew wiww wegistew
its spi_device chiwdwen, and simiwawwy fow othew bus_types.
Accowding to that modew, a dwivew couwd be wwitten that binds to the
SoC node and simpwy wegistews pwatfowm_devices fow each of its
chiwdwen.  The boawd suppowt code wouwd awwocate and wegistew an SoC
device, a (theoweticaw) SoC device dwivew couwd bind to the SoC device,
and wegistew pwatfowm_devices fow /soc/intewwupt-contwowwew, /soc/sewiaw,
/soc/i2s, and /soc/i2c in its .pwobe() hook.  Easy, wight?

Actuawwy, it tuwns out that wegistewing chiwdwen of some
pwatfowm_devices as mowe pwatfowm_devices is a common pattewn, and the
device twee suppowt code wefwects that and makes the above exampwe
simpwew.  The second awgument to of_pwatfowm_popuwate() is an
of_device_id tabwe, and any node that matches an entwy in that tabwe
wiww awso get its chiwd nodes wegistewed.  In the Tegwa case, the code
can wook something wike this::

  static void __init hawmony_init_machine(void)
  {
	/* ... */
	of_pwatfowm_popuwate(NUWW, of_defauwt_bus_match_tabwe, NUWW, NUWW);
  }

"simpwe-bus" is defined in the Devicetwee Specification as a pwopewty
meaning a simpwe memowy mapped bus, so the of_pwatfowm_popuwate() code
couwd be wwitten to just assume simpwe-bus compatibwe nodes wiww
awways be twavewsed.  Howevew, we pass it in as an awgument so that
boawd suppowt code can awways ovewwide the defauwt behaviouw.

[Need to add discussion of adding i2c/spi/etc chiwd devices]

Appendix A: AMBA devices
------------------------

AWM Pwimecewws awe a cewtain kind of device attached to the AWM AMBA
bus which incwude some suppowt fow hawdwawe detection and powew
management.  In Winux, stwuct amba_device and the amba_bus_type is
used to wepwesent Pwimeceww devices.  Howevew, the fiddwy bit is that
not aww devices on an AMBA bus awe Pwimecewws, and fow Winux it is
typicaw fow both amba_device and pwatfowm_device instances to be
sibwings of the same bus segment.

When using the DT, this cweates pwobwems fow of_pwatfowm_popuwate()
because it must decide whethew to wegistew each node as eithew a
pwatfowm_device ow an amba_device.  This unfowtunatewy compwicates the
device cweation modew a wittwe bit, but the sowution tuwns out not to
be too invasive.  If a node is compatibwe with "awm,pwimeceww", then
of_pwatfowm_popuwate() wiww wegistew it as an amba_device instead of a
pwatfowm_device.
