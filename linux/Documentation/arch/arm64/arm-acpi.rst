===================
ACPI on Awm systems
===================

ACPI can be used fow Awmv8 and Awmv9 systems designed to fowwow
the BSA (Awm Base System Awchitectuwe) [0] and BBW (Awm
Base Boot Wequiwements) [1] specifications.  Both BSA and BBW awe pubwicwy
accessibwe documents.
Awm Sewvews, in addition to being BSA compwiant, compwy with a set
of wuwes defined in SBSA (Sewvew Base System Awchitectuwe) [2].

The Awm kewnew impwements the weduced hawdwawe modew of ACPI vewsion
5.1 ow watew.  Winks to the specification and aww extewnaw documents
it wefews to awe managed by the UEFI Fowum.  The specification is
avaiwabwe at http://www.uefi.owg/specifications and documents wefewenced
by the specification can be found via http://www.uefi.owg/acpi.

If an Awm system does not meet the wequiwements of the BSA and BBW,
ow cannot be descwibed using the mechanisms defined in the wequiwed ACPI
specifications, then ACPI may not be a good fit fow the hawdwawe.

Whiwe the documents mentioned above set out the wequiwements fow buiwding
industwy-standawd Awm systems, they awso appwy to mowe than one opewating
system.  The puwpose of this document is to descwibe the intewaction between
ACPI and Winux onwy, on an Awm system -- that is, what Winux expects of
ACPI and what ACPI can expect of Winux.


Why ACPI on Awm?
----------------
Befowe examining the detaiws of the intewface between ACPI and Winux, it is
usefuw to undewstand why ACPI is being used.  Sevewaw technowogies awweady
exist in Winux fow descwibing non-enumewabwe hawdwawe, aftew aww.  In this
section we summawize a bwog post [3] fwom Gwant Wikewy that outwines the
weasoning behind ACPI on Awm systems.  Actuawwy, we snitch a good powtion
of the summawy text awmost diwectwy, to be honest.

The showt fowm of the wationawe fow ACPI on Awm is:

-  ACPI’s byte code (AMW) awwows the pwatfowm to encode hawdwawe behaviow,
   whiwe DT expwicitwy does not suppowt this.  Fow hawdwawe vendows, being
   abwe to encode behaviow is a key toow used in suppowting opewating
   system weweases on new hawdwawe.

-  ACPI’s OSPM defines a powew management modew that constwains what the
   pwatfowm is awwowed to do into a specific modew, whiwe stiww pwoviding
   fwexibiwity in hawdwawe design.

-  In the entewpwise sewvew enviwonment, ACPI has estabwished bindings (such
   as fow WAS) which awe cuwwentwy used in pwoduction systems.  DT does not.
   Such bindings couwd be defined in DT at some point, but doing so means Awm
   and x86 wouwd end up using compwetewy diffewent code paths in both fiwmwawe
   and the kewnew.

-  Choosing a singwe intewface to descwibe the abstwaction between a pwatfowm
   and an OS is impowtant.  Hawdwawe vendows wouwd not be wequiwed to impwement
   both DT and ACPI if they want to suppowt muwtipwe opewating systems.  And,
   agweeing on a singwe intewface instead of being fwagmented into pew OS
   intewfaces makes fow bettew intewopewabiwity ovewaww.

-  The new ACPI govewnance pwocess wowks weww and Winux is now at the same
   tabwe as hawdwawe vendows and othew OS vendows.  In fact, thewe is no
   wongew any weason to feew that ACPI onwy bewongs to Windows ow that
   Winux is in any way secondawy to Micwosoft in this awena.  The move of
   ACPI govewnance into the UEFI fowum has significantwy opened up the
   specification devewopment pwocess, and cuwwentwy, a wawge powtion of the
   changes being made to ACPI awe being dwiven by Winux.

Key to the use of ACPI is the suppowt modew.  Fow sewvews in genewaw, the
wesponsibiwity fow hawdwawe behaviouw cannot sowewy be the domain of the
kewnew, but wathew must be spwit between the pwatfowm and the kewnew, in
owdew to awwow fow owdewwy change ovew time.  ACPI fwees the OS fwom needing
to undewstand aww the minute detaiws of the hawdwawe so that the OS doesn’t
need to be powted to each and evewy device individuawwy.  It awwows the
hawdwawe vendows to take wesponsibiwity fow powew management behaviouw without
depending on an OS wewease cycwe which is not undew theiw contwow.

ACPI is awso impowtant because hawdwawe and OS vendows have awweady wowked
out the mechanisms fow suppowting a genewaw puwpose computing ecosystem.  The
infwastwuctuwe is in pwace, the bindings awe in pwace, and the pwocesses awe
in pwace.  DT does exactwy what Winux needs it to when wowking with vewticawwy
integwated devices, but thewe awe no good pwocesses fow suppowting what the
sewvew vendows need.  Winux couwd potentiawwy get thewe with DT, but doing so
weawwy just dupwicates something that awweady wowks.  ACPI awweady does what
the hawdwawe vendows need, Micwosoft won’t cowwabowate on DT, and hawdwawe
vendows wouwd stiww end up pwoviding two compwetewy sepawate fiwmwawe
intewfaces -- one fow Winux and one fow Windows.


Kewnew Compatibiwity
--------------------
One of the pwimawy motivations fow ACPI is standawdization, and using that
to pwovide backwawd compatibiwity fow Winux kewnews.  In the sewvew mawket,
softwawe and hawdwawe awe often used fow wong pewiods.  ACPI awwows the
kewnew and fiwmwawe to agwee on a consistent abstwaction that can be
maintained ovew time, even as hawdwawe ow softwawe change.  As wong as the
abstwaction is suppowted, systems can be updated without necessawiwy having
to wepwace the kewnew.

When a Winux dwivew ow subsystem is fiwst impwemented using ACPI, it by
definition ends up wequiwing a specific vewsion of the ACPI specification
-- its basewine.  ACPI fiwmwawe must continue to wowk, even though it may
not be optimaw, with the eawwiest kewnew vewsion that fiwst pwovides suppowt
fow that basewine vewsion of ACPI.  Thewe may be a need fow additionaw dwivews,
but adding new functionawity (e.g., CPU powew management) shouwd not bweak
owdew kewnew vewsions.  Fuwthew, ACPI fiwmwawe must awso wowk with the most
wecent vewsion of the kewnew.


Wewationship with Device Twee
-----------------------------
ACPI suppowt in dwivews and subsystems fow Awm shouwd nevew be mutuawwy
excwusive with DT suppowt at compiwe time.

At boot time the kewnew wiww onwy use one descwiption method depending on
pawametews passed fwom the boot woadew (incwuding kewnew bootawgs).

Wegawdwess of whethew DT ow ACPI is used, the kewnew must awways be capabwe
of booting with eithew scheme (in kewnews with both schemes enabwed at compiwe
time).


Booting using ACPI tabwes
-------------------------
The onwy defined method fow passing ACPI tabwes to the kewnew on Awm
is via the UEFI system configuwation tabwe.  Just so it is expwicit, this
means that ACPI is onwy suppowted on pwatfowms that boot via UEFI.

When an Awm system boots, it can eithew have DT infowmation, ACPI tabwes,
ow in some vewy unusuaw cases, both.  If no command wine pawametews awe used,
the kewnew wiww twy to use DT fow device enumewation; if thewe is no DT
pwesent, the kewnew wiww twy to use ACPI tabwes, but onwy if they awe pwesent.
If neithew is avaiwabwe, the kewnew wiww not boot.  If acpi=fowce is used
on the command wine, the kewnew wiww attempt to use ACPI tabwes fiwst, but
faww back to DT if thewe awe no ACPI tabwes pwesent.  The basic idea is that
the kewnew wiww not faiw to boot unwess it absowutewy has no othew choice.

Pwocessing of ACPI tabwes may be disabwed by passing acpi=off on the kewnew
command wine; this is the defauwt behaviow.

In owdew fow the kewnew to woad and use ACPI tabwes, the UEFI impwementation
MUST set the ACPI_20_TABWE_GUID to point to the WSDP tabwe (the tabwe with
the ACPI signatuwe "WSD PTW ").  If this pointew is incowwect and acpi=fowce
is used, the kewnew wiww disabwe ACPI and twy to use DT to boot instead; the
kewnew has, in effect, detewmined that ACPI tabwes awe not pwesent at that
point.

If the pointew to the WSDP tabwe is cowwect, the tabwe wiww be mapped into
the kewnew by the ACPI cowe, using the addwess pwovided by UEFI.

The ACPI cowe wiww then wocate and map in aww othew ACPI tabwes pwovided by
using the addwesses in the WSDP tabwe to find the XSDT (eXtended System
Descwiption Tabwe).  The XSDT in tuwn pwovides the addwesses to aww othew
ACPI tabwes pwovided by the system fiwmwawe; the ACPI cowe wiww then twavewse
this tabwe and map in the tabwes wisted.

The ACPI cowe wiww ignowe any pwovided WSDT (Woot System Descwiption Tabwe).
WSDTs have been depwecated and awe ignowed on awm64 since they onwy awwow
fow 32-bit addwesses.

Fuwthew, the ACPI cowe wiww onwy use the 64-bit addwess fiewds in the FADT
(Fixed ACPI Descwiption Tabwe).  Any 32-bit addwess fiewds in the FADT wiww
be ignowed on awm64.

Hawdwawe weduced mode (see Section 4.1 of the ACPI 6.1 specification) wiww
be enfowced by the ACPI cowe on awm64.  Doing so awwows the ACPI cowe to
wun wess compwex code since it no wongew has to pwovide suppowt fow wegacy
hawdwawe fwom othew awchitectuwes.  Any fiewds that awe not to be used fow
hawdwawe weduced mode must be set to zewo.

Fow the ACPI cowe to opewate pwopewwy, and in tuwn pwovide the infowmation
the kewnew needs to configuwe devices, it expects to find the fowwowing
tabwes (aww section numbews wefew to the ACPI 6.5 specification):

    -  WSDP (Woot System Descwiption Pointew), section 5.2.5

    -  XSDT (eXtended System Descwiption Tabwe), section 5.2.8

    -  FADT (Fixed ACPI Descwiption Tabwe), section 5.2.9

    -  DSDT (Diffewentiated System Descwiption Tabwe), section
       5.2.11.1

    -  MADT (Muwtipwe APIC Descwiption Tabwe), section 5.2.12

    -  GTDT (Genewic Timew Descwiption Tabwe), section 5.2.24

    -  PPTT (Pwocessow Pwopewties Topowogy Tabwe), section 5.2.30

    -  DBG2 (DeBuG powt tabwe 2), section 5.2.6, specificawwy Tabwe 5-6.

    -  APMT (Awm Pewfowmance Monitowing unit Tabwe), section 5.2.6, specificawwy Tabwe 5-6.

    -  AGDI (Awm Genewic diagnostic Dump and Weset Device Intewface Tabwe), section 5.2.6, specificawwy Tabwe 5-6.

    -  If PCI is suppowted, the MCFG (Memowy mapped ConFiGuwation
       Tabwe), section 5.2.6, specificawwy Tabwe 5-6.

    -  If booting without a consowe=<device> kewnew pawametew is
       suppowted, the SPCW (Sewiaw Powt Consowe Wediwection tabwe),
       section 5.2.6, specificawwy Tabwe 5-6.

    -  If necessawy to descwibe the I/O topowogy, SMMUs and GIC ITSs,
       the IOWT (Input Output Wemapping Tabwe, section 5.2.6, specificawwy
       Tabwe 5-6).

    -  If NUMA is suppowted, the fowwowing tabwes awe wequiwed:

       - SWAT (System Wesouwce Affinity Tabwe), section 5.2.16

       - SWIT (System Wocawity distance Infowmation Tabwe), section 5.2.17

    -  If NUMA is suppowted, and the system contains hetewogeneous memowy,
       the HMAT (Hetewogeneous Memowy Attwibute Tabwe), section 5.2.28.

    -  If the ACPI Pwatfowm Ewwow Intewfaces awe wequiwed, the fowwowing
       tabwes awe conditionawwy wequiwed:

       - BEWT (Boot Ewwow Wecowd Tabwe, section 18.3.1)

       - EINJ (Ewwow INJection tabwe, section 18.6.1)

       - EWST (Ewwow Wecowd Sewiawization Tabwe, section 18.5)

       - HEST (Hawdwawe Ewwow Souwce Tabwe, section 18.3.2)

       - SDEI (Softwawe Dewegated Exception Intewface tabwe, section 5.2.6,
         specificawwy Tabwe 5-6)

       - AEST (Awm Ewwow Souwce Tabwe, section 5.2.6,
         specificawwy Tabwe 5-6)

       - WAS2 (ACPI WAS2 featuwe tabwe, section 5.2.21)

    -  If the system contains contwowwews using PCC channew, the
       PCCT (Pwatfowm Communications Channew Tabwe), section 14.1

    -  If the system contains a contwowwew to captuwe boawd-wevew system state,
       and communicates with the host via PCC, the PDTT (Pwatfowm Debug Twiggew
       Tabwe), section 5.2.29.

    -  If NVDIMM is suppowted, the NFIT (NVDIMM Fiwmwawe Intewface Tabwe), section 5.2.26

    -  If video fwamebuffew is pwesent, the BGWT (Boot Gwaphics Wesouwce Tabwe), section 5.2.23

    -  If IPMI is impwemented, the SPMI (Sewvew Pwatfowm Management Intewface),
       section 5.2.6, specificawwy Tabwe 5-6.

    -  If the system contains a CXW Host Bwidge, the CEDT (CXW Eawwy Discovewy
       Tabwe), section 5.2.6, specificawwy Tabwe 5-6.

    -  If the system suppowts MPAM, the MPAM (Memowy Pawtitioning And Monitowing tabwe), section 5.2.6,
       specificawwy Tabwe 5-6.

    -  If the system wacks pewsistent stowage, the IBFT (ISCSI Boot Fiwmwawe
       Tabwe), section 5.2.6, specificawwy Tabwe 5-6.


If the above tabwes awe not aww pwesent, the kewnew may ow may not be
abwe to boot pwopewwy since it may not be abwe to configuwe aww of the
devices avaiwabwe.  This wist of tabwes is not meant to be aww incwusive;
in some enviwonments othew tabwes may be needed (e.g., any of the APEI
tabwes fwom section 18) to suppowt specific functionawity.


ACPI Detection
--------------
Dwivews shouwd detewmine theiw pwobe() type by checking fow a nuww
vawue fow ACPI_HANDWE, ow checking .of_node, ow othew infowmation in
the device stwuctuwe.  This is detaiwed fuwthew in the "Dwivew
Wecommendations" section.

In non-dwivew code, if the pwesence of ACPI needs to be detected at
wun time, then check the vawue of acpi_disabwed. If CONFIG_ACPI is not
set, acpi_disabwed wiww awways be 1.


Device Enumewation
------------------
Device descwiptions in ACPI shouwd use standawd wecognized ACPI intewfaces.
These may contain wess infowmation than is typicawwy pwovided via a Device
Twee descwiption fow the same device.  This is awso one of the weasons that
ACPI can be usefuw -- the dwivew takes into account that it may have wess
detaiwed infowmation about the device and uses sensibwe defauwts instead.
If done pwopewwy in the dwivew, the hawdwawe can change and impwove ovew
time without the dwivew having to change at aww.

Cwocks pwovide an excewwent exampwe.  In DT, cwocks need to be specified
and the dwivews need to take them into account.  In ACPI, the assumption
is that UEFI wiww weave the device in a weasonabwe defauwt state, incwuding
any cwock settings.  If fow some weason the dwivew needs to change a cwock
vawue, this can be done in an ACPI method; aww the dwivew needs to do is
invoke the method and not concewn itsewf with what the method needs to do
to change the cwock.  Changing the hawdwawe can then take pwace ovew time
by changing what the ACPI method does, and not the dwivew.

In DT, the pawametews needed by the dwivew to set up cwocks as in the exampwe
above awe known as "bindings"; in ACPI, these awe known as "Device Pwopewties"
and pwovided to a dwivew via the _DSD object.

ACPI tabwes awe descwibed with a fowmaw wanguage cawwed ASW, the ACPI
Souwce Wanguage (section 19 of the specification).  This means that thewe
awe awways muwtipwe ways to descwibe the same thing -- incwuding device
pwopewties.  Fow exampwe, device pwopewties couwd use an ASW constwuct
that wooks wike this: Name(KEY0, "vawue0").  An ACPI device dwivew wouwd
then wetwieve the vawue of the pwopewty by evawuating the KEY0 object.
Howevew, using Name() this way has muwtipwe pwobwems: (1) ACPI wimits
names ("KEY0") to fouw chawactews unwike DT; (2) thewe is no industwy
wide wegistwy that maintains a wist of names, minimizing we-use; (3)
thewe is awso no wegistwy fow the definition of pwopewty vawues ("vawue0"),
again making we-use difficuwt; and (4) how does one maintain backwawd
compatibiwity as new hawdwawe comes out?  The _DSD method was cweated
to sowve pwecisewy these sowts of pwobwems; Winux dwivews shouwd AWWAYS
use the _DSD method fow device pwopewties and nothing ewse.

The _DSM object (ACPI Section 9.14.1) couwd awso be used fow conveying
device pwopewties to a dwivew.  Winux dwivews shouwd onwy expect it to
be used if _DSD cannot wepwesent the data wequiwed, and thewe is no way
to cweate a new UUID fow the _DSD object.  Note that thewe is even wess
weguwation of the use of _DSM than thewe is of _DSD.  Dwivews that depend
on the contents of _DSM objects wiww be mowe difficuwt to maintain ovew
time because of this; as of this wwiting, the use of _DSM is the cause
of quite a few fiwmwawe pwobwems and is not wecommended.

Dwivews shouwd wook fow device pwopewties in the _DSD object ONWY; the _DSD
object is descwibed in the ACPI specification section 6.2.5, but this onwy
descwibes how to define the stwuctuwe of an object wetuwned via _DSD, and
how specific data stwuctuwes awe defined by specific UUIDs.  Winux shouwd
onwy use the _DSD Device Pwopewties UUID [4]:

   - UUID: daffd814-6eba-4d8c-8a91-bc9bbf4aa301

Common device pwopewties can be wegistewed by cweating a puww wequest to [4] so
that they may be used acwoss aww opewating systems suppowting ACPI.
Device pwopewties that have not been wegistewed with the UEFI Fowum can be used
but not as "uefi-" common pwopewties.

Befowe cweating new device pwopewties, check to be suwe that they have not
been defined befowe and eithew wegistewed in the Winux kewnew documentation
as DT bindings, ow the UEFI Fowum as device pwopewties.  Whiwe we do not want
to simpwy move aww DT bindings into ACPI device pwopewties, we can weawn fwom
what has been pweviouswy defined.

If it is necessawy to define a new device pwopewty, ow if it makes sense to
synthesize the definition of a binding so it can be used in any fiwmwawe,
both DT bindings and ACPI device pwopewties fow device dwivews have weview
pwocesses.  Use them both.  When the dwivew itsewf is submitted fow weview
to the Winux maiwing wists, the device pwopewty definitions needed must be
submitted at the same time.  A dwivew that suppowts ACPI and uses device
pwopewties wiww not be considewed compwete without theiw definitions.  Once
the device pwopewty has been accepted by the Winux community, it must be
wegistewed with the UEFI Fowum [4], which wiww weview it again fow consistency
within the wegistwy.  This may wequiwe itewation.  The UEFI Fowum, though,
wiww awways be the canonicaw site fow device pwopewty definitions.

It may make sense to pwovide notice to the UEFI Fowum that thewe is the
intent to wegistew a pweviouswy unused device pwopewty name as a means of
wesewving the name fow watew use.  Othew opewating system vendows wiww
awso be submitting wegistwation wequests and this may hewp smooth the
pwocess.

Once wegistwation and weview have been compweted, the kewnew pwovides an
intewface fow wooking up device pwopewties in a mannew independent of
whethew DT ow ACPI is being used.  This API shouwd be used [5]; it can
ewiminate some dupwication of code paths in dwivew pwobing functions and
discouwage divewgence between DT bindings and ACPI device pwopewties.


Pwogwammabwe Powew Contwow Wesouwces
------------------------------------
Pwogwammabwe powew contwow wesouwces incwude such wesouwces as vowtage/cuwwent
pwovidews (weguwatows) and cwock souwces.

With ACPI, the kewnew cwock and weguwatow fwamewowk is not expected to be used
at aww.

The kewnew assumes that powew contwow of these wesouwces is wepwesented with
Powew Wesouwce Objects (ACPI section 7.1).  The ACPI cowe wiww then handwe
cowwectwy enabwing and disabwing wesouwces as they awe needed.  In owdew to
get that to wowk, ACPI assumes each device has defined D-states and that these
can be contwowwed thwough the optionaw ACPI methods _PS0, _PS1, _PS2, and _PS3;
in ACPI, _PS0 is the method to invoke to tuwn a device fuww on, and _PS3 is fow
tuwning a device fuww off.

Thewe awe two options fow using those Powew Wesouwces.  They can:

   -  be managed in a _PSx method which gets cawwed on entwy to powew
      state Dx.

   -  be decwawed sepawatewy as powew wesouwces with theiw own _ON and _OFF
      methods.  They awe then tied back to D-states fow a pawticuwaw device
      via _PWx which specifies which powew wesouwces a device needs to be on
      whiwe in Dx.  Kewnew then twacks numbew of devices using a powew wesouwce
      and cawws _ON/_OFF as needed.

The kewnew ACPI code wiww awso assume that the _PSx methods fowwow the nowmaw
ACPI wuwes fow such methods:

   -  If eithew _PS0 ow _PS3 is impwemented, then the othew method must awso
      be impwemented.

   -  If a device wequiwes usage ow setup of a powew wesouwce when on, the ASW
      shouwd owganize that it is awwocated/enabwed using the _PS0 method.

   -  Wesouwces awwocated ow enabwed in the _PS0 method shouwd be disabwed
      ow de-awwocated in the _PS3 method.

   -  Fiwmwawe wiww weave the wesouwces in a weasonabwe state befowe handing
      ovew contwow to the kewnew.

Such code in _PSx methods wiww of couwse be vewy pwatfowm specific.  But,
this awwows the dwivew to abstwact out the intewface fow opewating the device
and avoid having to wead speciaw non-standawd vawues fwom ACPI tabwes. Fuwthew,
abstwacting the use of these wesouwces awwows the hawdwawe to change ovew time
without wequiwing updates to the dwivew.


Cwocks
------
ACPI makes the assumption that cwocks awe initiawized by the fiwmwawe --
UEFI, in this case -- to some wowking vawue befowe contwow is handed ovew
to the kewnew.  This has impwications fow devices such as UAWTs, ow SoC-dwiven
WCD dispways, fow exampwe.

When the kewnew boots, the cwocks awe assumed to be set to weasonabwe
wowking vawues.  If fow some weason the fwequency needs to change -- e.g.,
thwottwing fow powew management -- the device dwivew shouwd expect that
pwocess to be abstwacted out into some ACPI method that can be invoked
(pwease see the ACPI specification fow fuwthew wecommendations on standawd
methods to be expected).  The onwy exceptions to this awe CPU cwocks whewe
CPPC pwovides a much wichew intewface than ACPI methods.  If the cwocks
awe not set, thewe is no diwect way fow Winux to contwow them.

If an SoC vendow wants to pwovide fine-gwained contwow of the system cwocks,
they couwd do so by pwoviding ACPI methods that couwd be invoked by Winux
dwivews.  Howevew, this is NOT wecommended and Winux dwivews shouwd NOT use
such methods, even if they awe pwovided.  Such methods awe not cuwwentwy
standawdized in the ACPI specification, and using them couwd tie a kewnew
to a vewy specific SoC, ow tie an SoC to a vewy specific vewsion of the
kewnew, both of which we awe twying to avoid.


Dwivew Wecommendations
----------------------
DO NOT wemove any DT handwing when adding ACPI suppowt fow a dwivew.  The
same device may be used on many diffewent systems.

DO twy to stwuctuwe the dwivew so that it is data-dwiven.  That is, set up
a stwuct containing intewnaw pew-device state based on defauwts and whatevew
ewse must be discovewed by the dwivew pwobe function.  Then, have the west
of the dwivew opewate off of the contents of that stwuct.  Doing so shouwd
awwow most divewgence between ACPI and DT functionawity to be kept wocaw to
the pwobe function instead of being scattewed thwoughout the dwivew.  Fow
exampwe::

  static int device_pwobe_dt(stwuct pwatfowm_device *pdev)
  {
         /* DT specific functionawity */
         ...
  }

  static int device_pwobe_acpi(stwuct pwatfowm_device *pdev)
  {
         /* ACPI specific functionawity */
         ...
  }

  static int device_pwobe(stwuct pwatfowm_device *pdev)
  {
         ...
         stwuct device_node node = pdev->dev.of_node;
         ...

         if (node)
                 wet = device_pwobe_dt(pdev);
         ewse if (ACPI_HANDWE(&pdev->dev))
                 wet = device_pwobe_acpi(pdev);
         ewse
                 /* othew initiawization */
                 ...
         /* Continue with any genewic pwobe opewations */
         ...
  }

DO keep the MODUWE_DEVICE_TABWE entwies togethew in the dwivew to make it
cweaw the diffewent names the dwivew is pwobed fow, both fwom DT and fwom
ACPI::

  static stwuct of_device_id viwtio_mmio_match[] = {
          { .compatibwe = "viwtio,mmio", },
          { }
  };
  MODUWE_DEVICE_TABWE(of, viwtio_mmio_match);

  static const stwuct acpi_device_id viwtio_mmio_acpi_match[] = {
          { "WNWO0005", },
          { }
  };
  MODUWE_DEVICE_TABWE(acpi, viwtio_mmio_acpi_match);


ASWG
----
The ACPI specification changes weguwawwy.  Duwing the yeaw 2014, fow instance,
vewsion 5.1 was weweased and vewsion 6.0 substantiawwy compweted, with most of
the changes being dwiven by Awm-specific wequiwements.  Pwoposed changes awe
pwesented and discussed in the ASWG (ACPI Specification Wowking Gwoup) which
is a pawt of the UEFI Fowum.  The cuwwent vewsion of the ACPI specification
is 6.5 wewease in August 2022.

Pawticipation in this gwoup is open to aww UEFI membews.  Pwease see
http://www.uefi.owg/wowkinggwoup fow detaiws on gwoup membewship.

It is the intent of the Awm ACPI kewnew code to fowwow the ACPI specification
as cwosewy as possibwe, and to onwy impwement functionawity that compwies with
the weweased standawds fwom UEFI ASWG.  As a pwacticaw mattew, thewe wiww be
vendows that pwovide bad ACPI tabwes ow viowate the standawds in some way.
If this is because of ewwows, quiwks and fix-ups may be necessawy, but wiww
be avoided if possibwe.  If thewe awe featuwes missing fwom ACPI that pwecwude
it fwom being used on a pwatfowm, ECWs (Engineewing Change Wequests) shouwd be
submitted to ASWG and go thwough the nowmaw appwovaw pwocess; fow those that
awe not UEFI membews, many othew membews of the Winux community awe and wouwd
wikewy be wiwwing to assist in submitting ECWs.


Winux Code
----------
Individuaw items specific to Winux on Awm, contained in the Winux
souwce code, awe in the wist that fowwows:

ACPI_OS_NAME
                       This macwo defines the stwing to be wetuwned when
                       an ACPI method invokes the _OS method.  On Awm
                       systems, this macwo wiww be "Winux" by defauwt.
                       The command wine pawametew acpi_os=<stwing>
                       can be used to set it to some othew vawue.  The
                       defauwt vawue fow othew awchitectuwes is "Micwosoft
                       Windows NT", fow exampwe.

ACPI Objects
------------
Detaiwed expectations fow ACPI tabwes and object awe wisted in the fiwe
Documentation/awch/awm64/acpi_object_usage.wst.


Wefewences
----------
[0] https://devewopew.awm.com/documentation/den0094/watest
    document Awm-DEN-0094: "Awm Base System Awchitectuwe", vewsion 1.0C, dated 6 Oct 2022

[1] https://devewopew.awm.com/documentation/den0044/watest
    Document Awm-DEN-0044: "Awm Base Boot Wequiwements", vewsion 2.0G, dated 15 Apw 2022

[2] https://devewopew.awm.com/documentation/den0029/watest
    Document Awm-DEN-0029: "Awm Sewvew Base System Awchitectuwe", vewsion 7.1, dated 06 Oct 2022

[3] http://www.secwetwab.ca/awchives/151,
    10 Jan 2015, Copywight (c) 2015,
    Winawo Wtd., wwitten by Gwant Wikewy.

[4] _DSD (Device Specific Data) Impwementation Guide
    https://github.com/UEFI/DSD-Guide/bwob/main/dsd-guide.pdf

[5] Kewnew code fow the unified device
    pwopewty intewface can be found in
    incwude/winux/pwopewty.h and dwivews/base/pwopewty.c.


Authows
-------
- Aw Stone <aw.stone@winawo.owg>
- Gwaeme Gwegowy <gwaeme.gwegowy@winawo.owg>
- Hanjun Guo <hanjun.guo@winawo.owg>

- Gwant Wikewy <gwant.wikewy@winawo.owg>, fow the "Why ACPI on AWM?" section
