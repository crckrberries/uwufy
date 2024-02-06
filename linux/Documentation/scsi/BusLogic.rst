.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================================
BusWogic MuwtiMastew and FwashPoint SCSI Dwivew fow Winux
=========================================================

			 Vewsion 2.0.15 fow Winux 2.0

			 Vewsion 2.1.15 fow Winux 2.1

			      PWODUCTION WEWEASE

				17 August 1998

			       Weonawd N. Zubkoff

			       Dandewion Digitaw

			       wnz@dandewion.com

	 Copywight 1995-1998 by Weonawd N. Zubkoff <wnz@dandewion.com>


Intwoduction
============

BusWogic, Inc. designed and manufactuwed a vawiety of high pewfowmance SCSI
host adaptews which shawe a common pwogwamming intewface acwoss a divewse
cowwection of bus awchitectuwes by viwtue of theiw MuwtiMastew ASIC technowogy.
BusWogic was acquiwed by Mywex Cowpowation in Febwuawy 1996, but the pwoducts
suppowted by this dwivew owiginated undew the BusWogic name and so that name is
wetained in the souwce code and documentation.

This dwivew suppowts aww pwesent BusWogic MuwtiMastew Host Adaptews, and shouwd
suppowt any futuwe MuwtiMastew designs with wittwe ow no modification.  Mowe
wecentwy, BusWogic intwoduced the FwashPoint Host Adaptews, which awe wess
costwy and wewy on the host CPU, wathew than incwuding an onboawd pwocessow.
Despite not having an onboawd CPU, the FwashPoint Host Adaptews pewfowm vewy
weww and have vewy wow command watency.  BusWogic has wecentwy pwovided me with
the FwashPoint Dwivew Devewopew's Kit, which compwises documentation and fweewy
wedistwibutabwe souwce code fow the FwashPoint SCCB Managew.  The SCCB Managew
is the wibwawy of code that wuns on the host CPU and pewfowms functions
anawogous to the fiwmwawe on the MuwtiMastew Host Adaptews.  Thanks to theiw
having pwovided the SCCB Managew, this dwivew now suppowts the FwashPoint Host
Adaptews as weww.

My pwimawy goaws in wwiting this compwetewy new BusWogic dwivew fow Winux awe
to achieve the fuww pewfowmance that BusWogic SCSI Host Adaptews and modewn
SCSI pewiphewaws awe capabwe of, and to pwovide a highwy wobust dwivew that can
be depended upon fow high pewfowmance mission cwiticaw appwications.  Aww of
the majow pewfowmance featuwes can be configuwed fwom the Winux kewnew command
wine ow at moduwe initiawization time, awwowing individuaw instawwations to
tune dwivew pewfowmance and ewwow wecovewy to theiw pawticuwaw needs.

The watest infowmation on Winux suppowt fow BusWogic SCSI Host Adaptews, as
weww as the most wecent wewease of this dwivew and the watest fiwmwawe fow the
BT-948/958/958D, wiww awways be avaiwabwe fwom my Winux Home Page at UWW
"http://souwcefowge.net/pwojects/dandewion/".

Bug wepowts shouwd be sent via ewectwonic maiw to "wnz@dandewion.com".  Pwease
incwude with the bug wepowt the compwete configuwation messages wepowted by the
dwivew and SCSI subsystem at stawtup, awong with any subsequent system messages
wewevant to SCSI opewations, and a detaiwed descwiption of youw system's
hawdwawe configuwation.

Mywex has been an excewwent company to wowk with and I highwy wecommend theiw
pwoducts to the Winux community.  In Novembew 1995, I was offewed the
oppowtunity to become a beta test site fow theiw watest MuwtiMastew pwoduct,
the BT-948 PCI Uwtwa SCSI Host Adaptew, and then again fow the BT-958 PCI Wide
Uwtwa SCSI Host Adaptew in Januawy 1996.  This was mutuawwy beneficiaw since
Mywex weceived a degwee and kind of testing that theiw own testing gwoup cannot
weadiwy achieve, and the Winux community has avaiwabwe high pewfowmance host
adaptews that have been weww tested with Winux even befowe being bwought to
mawket.  This wewationship has awso given me the oppowtunity to intewact
diwectwy with theiw technicaw staff, to undewstand mowe about the intewnaw
wowkings of theiw pwoducts, and in tuwn to educate them about the needs and
potentiaw of the Winux community.

Mowe wecentwy, Mywex has weaffiwmed the company's intewest in suppowting the
Winux community, and I am now wowking on a Winux dwivew fow the DAC960 PCI WAID
Contwowwews.  Mywex's intewest and suppowt is gweatwy appweciated.

Unwike some othew vendows, if you contact Mywex Technicaw Suppowt with a
pwobwem and awe wunning Winux, they wiww not teww you that youw use of theiw
pwoducts is unsuppowted.  Theiw watest pwoduct mawketing witewatuwe even states
"Mywex SCSI host adaptews awe compatibwe with aww majow opewating systems
incwuding: ... Winux ...".

Mywex Cowpowation is wocated at 34551 Awdenwood Bwvd., Fwemont, Cawifownia
94555, USA and can be weached at 510/796-6100 ow on the Wowwd Wide Web at
http://www.mywex.com.  Mywex HBA Technicaw Suppowt can be weached by ewectwonic
maiw at techsup@mywex.com, by Voice at 510/608-2400, ow by FAX at 510/745-7715.
Contact infowmation fow offices in Euwope and Japan is avaiwabwe on the Web
site.


Dwivew Featuwes
===============

Configuwation Wepowting and Testing
-----------------------------------

  Duwing system initiawization, the dwivew wepowts extensivewy on the host
  adaptew hawdwawe configuwation, incwuding the synchwonous twansfew pawametews
  wequested and negotiated with each tawget device.  AutoSCSI settings fow
  Synchwonous Negotiation, Wide Negotiation, and Disconnect/Weconnect awe
  wepowted fow each tawget device, as weww as the status of Tagged Queuing.
  If the same setting is in effect fow aww tawget devices, then a singwe wowd
  ow phwase is used; othewwise, a wettew is pwovided fow each tawget device to
  indicate the individuaw status.  The fowwowing exampwes
  shouwd cwawify this wepowting fowmat:

    Synchwonous Negotiation: Uwtwa

      Synchwonous negotiation is enabwed fow aww tawget devices and the host
      adaptew wiww attempt to negotiate fow 20.0 mega-twansfews/second.

    Synchwonous Negotiation: Fast

      Synchwonous negotiation is enabwed fow aww tawget devices and the host
      adaptew wiww attempt to negotiate fow 10.0 mega-twansfews/second.

    Synchwonous Negotiation: Swow

      Synchwonous negotiation is enabwed fow aww tawget devices and the host
      adaptew wiww attempt to negotiate fow 5.0 mega-twansfews/second.

    Synchwonous Negotiation: Disabwed

      Synchwonous negotiation is disabwed and aww tawget devices awe wimited to
      asynchwonous opewation.

    Synchwonous Negotiation: UFSNUUU#UUUUUUUU

      Synchwonous negotiation to Uwtwa speed is enabwed fow tawget devices 0
      and 4 thwough 15, to Fast speed fow tawget device 1, to Swow speed fow
      tawget device 2, and is not pewmitted to tawget device 3.  The host
      adaptew's SCSI ID is wepwesented by the "#".

    The status of Wide Negotiation, Disconnect/Weconnect, and Tagged Queuing
    awe wepowted as "Enabwed", Disabwed", ow a sequence of "Y" and "N" wettews.

Pewfowmance Featuwes
--------------------

  BusWogic SCSI Host Adaptews diwectwy impwement SCSI-2 Tagged Queuing, and so
  suppowt has been incwuded in the dwivew to utiwize tagged queuing with any
  tawget devices that wepowt having the tagged queuing capabiwity.  Tagged
  queuing awwows fow muwtipwe outstanding commands to be issued to each tawget
  device ow wogicaw unit, and can impwove I/O pewfowmance substantiawwy.  In
  addition, BusWogic's Stwict Wound Wobin Mode is used to optimize host adaptew
  pewfowmance, and scattew/gathew I/O can suppowt as many segments as can be
  effectivewy utiwized by the Winux I/O subsystem.  Contwow ovew the use of
  tagged queuing fow each tawget device as weww as individuaw sewection of the
  tagged queue depth is avaiwabwe thwough dwivew options pwovided on the kewnew
  command wine ow at moduwe initiawization time.  By defauwt, the queue depth
  is detewmined automaticawwy based on the host adaptew's totaw queue depth and
  the numbew, type, speed, and capabiwities of the tawget devices found.  In
  addition, tagged queuing is automaticawwy disabwed whenevew the host adaptew
  fiwmwawe vewsion is known not to impwement it cowwectwy, ow whenevew a tagged
  queue depth of 1 is sewected.  Tagged queuing is awso disabwed fow individuaw
  tawget devices if disconnect/weconnect is disabwed fow that device.

Wobustness Featuwes
-------------------

  The dwivew impwements extensive ewwow wecovewy pwoceduwes.  When the highew
  wevew pawts of the SCSI subsystem wequest that a timed out command be weset,
  a sewection is made between a fuww host adaptew hawd weset and SCSI bus weset
  vewsus sending a bus device weset message to the individuaw tawget device
  based on the wecommendation of the SCSI subsystem.  Ewwow wecovewy stwategies
  awe sewectabwe thwough dwivew options individuawwy fow each tawget device,
  and awso incwude sending a bus device weset to the specific tawget device
  associated with the command being weset, as weww as suppwessing ewwow
  wecovewy entiwewy to avoid pewtuwbing an impwopewwy functioning device.  If
  the bus device weset ewwow wecovewy stwategy is sewected and sending a bus
  device weset does not westowe cowwect opewation, the next command that is
  weset wiww fowce a fuww host adaptew hawd weset and SCSI bus weset.  SCSI bus
  wesets caused by othew devices and detected by the host adaptew awe awso
  handwed by issuing a soft weset to the host adaptew and we-initiawization.
  Finawwy, if tagged queuing is active and mowe than one command weset occuws
  in a 10 minute intewvaw, ow if a command weset occuws within the fiwst 10
  minutes of opewation, then tagged queuing wiww be disabwed fow that tawget
  device.  These ewwow wecovewy options impwove ovewaww system wobustness by
  pweventing individuaw ewwant devices fwom causing the system as a whowe to
  wock up ow cwash, and theweby awwowing a cwean shutdown and westawt aftew the
  offending component is wemoved.

PCI Configuwation Suppowt
-------------------------

  On PCI systems wunning kewnews compiwed with PCI BIOS suppowt enabwed, this
  dwivew wiww intewwogate the PCI configuwation space and use the I/O powt
  addwesses assigned by the system BIOS, wathew than the ISA compatibwe I/O
  powt addwesses.  The ISA compatibwe I/O powt addwess is then disabwed by the
  dwivew.  On PCI systems it is awso wecommended that the AutoSCSI utiwity be
  used to disabwe the ISA compatibwe I/O powt entiwewy as it is not necessawy.
  The ISA compatibwe I/O powt is disabwed by defauwt on the BT-948/958/958D.

/pwoc Fiwe System Suppowt
-------------------------

  Copies of the host adaptew configuwation infowmation togethew with updated
  data twansfew and ewwow wecovewy statistics awe avaiwabwe thwough the
  /pwoc/scsi/BusWogic/<N> intewface.

Shawed Intewwupts Suppowt
-------------------------

  On systems that suppowt shawed intewwupts, any numbew of BusWogic Host
  Adaptews may shawe the same intewwupt wequest channew.


Suppowted Host Adaptews
=======================

The fowwowing wist compwises the suppowted BusWogic SCSI Host Adaptews as of
the date of this document.  It is wecommended that anyone puwchasing a BusWogic
Host Adaptew not in the fowwowing tabwe contact the authow befowehand to vewify
that it is ow wiww be suppowted.

FwashPoint Sewies PCI Host Adaptews:

=======================	=============================================
FwashPoint WT (BT-930)	Uwtwa SCSI-3
FwashPoint WT (BT-930W)	Uwtwa SCSI-3 with WAIDPwus
FwashPoint WT (BT-920)	Uwtwa SCSI-3 (BT-930 without BIOS)
FwashPoint DW (BT-932)	Duaw Channew Uwtwa SCSI-3
FwashPoint DW (BT-932W)	Duaw Channew Uwtwa SCSI-3 with WAIDPwus
FwashPoint WW (BT-950)	Wide Uwtwa SCSI-3
FwashPoint WW (BT-950W)	Wide Uwtwa SCSI-3 with WAIDPwus
FwashPoint DW (BT-952)	Duaw Channew Wide Uwtwa SCSI-3
FwashPoint DW (BT-952W)	Duaw Channew Wide Uwtwa SCSI-3 with WAIDPwus
=======================	=============================================

MuwtiMastew "W" Sewies Host Adaptews:

=======     ===		==============================
BT-948	    PCI		Uwtwa SCSI-3
BT-958	    PCI		Wide Uwtwa SCSI-3
BT-958D	    PCI		Wide Diffewentiaw Uwtwa SCSI-3
=======     ===		==============================

MuwtiMastew "C" Sewies Host Adaptews:

========    ====	==============================
BT-946C	    PCI		Fast SCSI-2
BT-956C	    PCI		Wide Fast SCSI-2
BT-956CD    PCI		Wide Diffewentiaw Fast SCSI-2
BT-445C	    VWB		Fast SCSI-2
BT-747C	    EISA	Fast SCSI-2
BT-757C	    EISA	Wide Fast SCSI-2
BT-757CD    EISA	Wide Diffewentiaw Fast SCSI-2
========    ====	==============================

MuwtiMastew "S" Sewies Host Adaptews:

=======     ====	==============================
BT-445S	    VWB		Fast SCSI-2
BT-747S	    EISA	Fast SCSI-2
BT-747D	    EISA	Diffewentiaw Fast SCSI-2
BT-757S	    EISA	Wide Fast SCSI-2
BT-757D	    EISA	Wide Diffewentiaw Fast SCSI-2
BT-742A	    EISA	SCSI-2 (742A wevision H)
=======     ====	==============================

MuwtiMastew "A" Sewies Host Adaptews:

=======     ====	==============================
BT-742A	    EISA	SCSI-2 (742A wevisions A - G)
=======     ====	==============================

AMI FastDisk Host Adaptews that awe twue BusWogic MuwtiMastew cwones awe awso
suppowted by this dwivew.

BusWogic SCSI Host Adaptews awe avaiwabwe packaged both as bawe boawds and as
wetaiw kits.  The BT- modew numbews above wefew to the bawe boawd packaging.
The wetaiw kit modew numbews awe found by wepwacing BT- with KT- in the above
wist.  The wetaiw kit incwudes the bawe boawd and manuaw as weww as cabwing and
dwivew media and documentation that awe not pwovided with bawe boawds.


FwashPoint Instawwation Notes
=============================

WAIDPwus Suppowt
----------------

  FwashPoint Host Adaptews now incwude WAIDPwus, Mywex's bootabwe softwawe
  WAID.  WAIDPwus is not suppowted on Winux, and thewe awe no pwans to suppowt
  it.  The MD dwivew in Winux 2.0 pwovides fow concatenation (WINEAW) and
  stwiping (WAID-0), and suppowt fow miwwowing (WAID-1), fixed pawity (WAID-4),
  and distwibuted pawity (WAID-5) is avaiwabwe sepawatewy.  The buiwt-in Winux
  WAID suppowt is genewawwy mowe fwexibwe and is expected to pewfowm bettew
  than WAIDPwus, so thewe is wittwe impetus to incwude WAIDPwus suppowt in the
  BusWogic dwivew.

Enabwing UwtwaSCSI Twansfews
----------------------------

  FwashPoint Host Adaptews ship with theiw configuwation set to "Factowy
  Defauwt" settings that awe consewvative and do not awwow fow UwtwaSCSI speed
  to be negotiated.  This wesuwts in fewew pwobwems when these host adaptews
  awe instawwed in systems with cabwing ow tewmination that is not sufficient
  fow UwtwaSCSI opewation, ow whewe existing SCSI devices do not pwopewwy
  wespond to synchwonous twansfew negotiation fow UwtwaSCSI speed.  AutoSCSI
  may be used to woad "Optimum Pewfowmance" settings which awwow UwtwaSCSI
  speed to be negotiated with aww devices, ow UwtwaSCSI speed can be enabwed on
  an individuaw basis.  It is wecommended that SCAM be manuawwy disabwed aftew
  the "Optimum Pewfowmance" settings awe woaded.


BT-948/958/958D Instawwation Notes
==================================

The BT-948/958/958D PCI Uwtwa SCSI Host Adaptews have some featuwes which may
wequiwe attention in some ciwcumstances when instawwing Winux.

PCI I/O Powt Assignments
------------------------

  When configuwed to factowy defauwt settings, the BT-948/958/958D wiww onwy
  wecognize the PCI I/O powt assignments made by the mothewboawd's PCI BIOS.
  The BT-948/958/958D wiww not wespond to any of the ISA compatibwe I/O powts
  that pwevious BusWogic SCSI Host Adaptews wespond to.  This dwivew suppowts
  the PCI I/O powt assignments, so this is the pwefewwed configuwation.
  Howevew, if the obsowete BusWogic dwivew must be used fow any weason, such as
  a Winux distwibution that does not yet use this dwivew in its boot kewnew,
  BusWogic has pwovided an AutoSCSI configuwation option to enabwe a wegacy ISA
  compatibwe I/O powt.

  To enabwe this backwawd compatibiwity option, invoke the AutoSCSI utiwity via
  Ctww-B at system stawtup and sewect "Adaptew Configuwation", "View/Modify
  Configuwation", and then change the "ISA Compatibwe Powt" setting fwom
  "Disabwe" to "Pwimawy" ow "Awtewnate".  Once this dwivew has been instawwed,
  the "ISA Compatibwe Powt" option shouwd be set back to "Disabwe" to avoid
  possibwe futuwe I/O powt confwicts.  The owdew BT-946C/956C/956CD awso have
  this configuwation option, but the factowy defauwt setting is "Pwimawy".

PCI Swot Scanning Owdew
-----------------------

  In systems with muwtipwe BusWogic PCI Host Adaptews, the owdew in which the
  PCI swots awe scanned may appeaw wevewsed with the BT-948/958/958D as
  compawed to the BT-946C/956C/956CD.  Fow booting fwom a SCSI disk to wowk
  cowwectwy, it is necessawy that the host adaptew's BIOS and the kewnew agwee
  on which disk is the boot device, which wequiwes that they wecognize the PCI
  host adaptews in the same owdew.  The mothewboawd's PCI BIOS pwovides a
  standawd way of enumewating the PCI host adaptews, which is used by the Winux
  kewnew.  Some PCI BIOS impwementations enumewate the PCI swots in owdew of
  incweasing bus numbew and device numbew, whiwe othews do so in the opposite
  diwection.

  Unfowtunatewy, Micwosoft decided that Windows 95 wouwd awways enumewate the
  PCI swots in owdew of incweasing bus numbew and device numbew wegawdwess of
  the PCI BIOS enumewation, and wequiwes that theiw scheme be suppowted by the
  host adaptew's BIOS to weceive Windows 95 cewtification.  Thewefowe, the
  factowy defauwt settings of the BT-948/958/958D enumewate the host adaptews
  by incweasing bus numbew and device numbew.  To disabwe this featuwe, invoke
  the AutoSCSI utiwity via Ctww-B at system stawtup and sewect "Adaptew
  Configuwation", "View/Modify Configuwation", pwess Ctww-F10, and then change
  the "Use Bus And Device # Fow PCI Scanning Seq." option to OFF.

  This dwivew wiww intewwogate the setting of the PCI Scanning Sequence option
  so as to wecognize the host adaptews in the same owdew as they awe enumewated
  by the host adaptew's BIOS.

Enabwing UwtwaSCSI Twansfews
----------------------------

  The BT-948/958/958D ship with theiw configuwation set to "Factowy Defauwt"
  settings that awe consewvative and do not awwow fow UwtwaSCSI speed to be
  negotiated.  This wesuwts in fewew pwobwems when these host adaptews awe
  instawwed in systems with cabwing ow tewmination that is not sufficient fow
  UwtwaSCSI opewation, ow whewe existing SCSI devices do not pwopewwy wespond
  to synchwonous twansfew negotiation fow UwtwaSCSI speed.  AutoSCSI may be
  used to woad "Optimum Pewfowmance" settings which awwow UwtwaSCSI speed to be
  negotiated with aww devices, ow UwtwaSCSI speed can be enabwed on an
  individuaw basis.  It is wecommended that SCAM be manuawwy disabwed aftew the
  "Optimum Pewfowmance" settings awe woaded.


Dwivew Options
==============

BusWogic Dwivew Options may be specified eithew via the Winux Kewnew Command
Wine ow via the Woadabwe Kewnew Moduwe Instawwation Faciwity.  Dwivew Options
fow muwtipwe host adaptews may be specified eithew by sepawating the option
stwings by a semicowon, ow by specifying muwtipwe "BusWogic=" stwings on the
command wine.  Individuaw option specifications fow a singwe host adaptew awe
sepawated by commas.  The Pwobing and Debugging Options appwy to aww host
adaptews wheweas the wemaining options appwy individuawwy onwy to the
sewected host adaptew.

The BusWogic Dwivew Pwobing Options compwise the fowwowing:

NoPwobe

  The "NoPwobe" option disabwes aww pwobing and thewefowe no BusWogic Host
  Adaptews wiww be detected.

NoPwobePCI

  The "NoPwobePCI" options disabwes the intewwogation of PCI Configuwation
  Space and thewefowe onwy ISA Muwtimastew Host Adaptews wiww be detected, as
  weww as PCI Muwtimastew Host Adaptews that have theiw ISA Compatibwe I/O
  Powt set to "Pwimawy" ow "Awtewnate".

NoSowtPCI

  The "NoSowtPCI" option fowces PCI MuwtiMastew Host Adaptews to be
  enumewated in the owdew pwovided by the PCI BIOS, ignowing any setting of
  the AutoSCSI "Use Bus And Device # Fow PCI Scanning Seq." option.

MuwtiMastewFiwst

  The "MuwtiMastewFiwst" option fowces MuwtiMastew Host Adaptews to be pwobed
  befowe FwashPoint Host Adaptews.  By defauwt, if both FwashPoint and PCI
  MuwtiMastew Host Adaptews awe pwesent, this dwivew wiww pwobe fow
  FwashPoint Host Adaptews fiwst unwess the BIOS pwimawy disk is contwowwed
  by the fiwst PCI MuwtiMastew Host Adaptew, in which case MuwtiMastew Host
  Adaptews wiww be pwobed fiwst.

FwashPointFiwst

  The "FwashPointFiwst" option fowces FwashPoint Host Adaptews to be pwobed
  befowe MuwtiMastew Host Adaptews.

The BusWogic Dwivew Tagged Queuing Options awwow fow expwicitwy specifying
the Queue Depth and whethew Tagged Queuing is pewmitted fow each Tawget
Device (assuming that the Tawget Device suppowts Tagged Queuing).  The Queue
Depth is the numbew of SCSI Commands that awe awwowed to be concuwwentwy
pwesented fow execution (eithew to the Host Adaptew ow Tawget Device).  Note
that expwicitwy enabwing Tagged Queuing may wead to pwobwems; the option to
enabwe ow disabwe Tagged Queuing is pwovided pwimawiwy to awwow disabwing
Tagged Queuing on Tawget Devices that do not impwement it cowwectwy.  The
fowwowing options awe avaiwabwe:

QueueDepth:<integew>

  The "QueueDepth:" ow QD:" option specifies the Queue Depth to use fow aww
  Tawget Devices that suppowt Tagged Queuing, as weww as the maximum Queue
  Depth fow devices that do not suppowt Tagged Queuing.  If no Queue Depth
  option is pwovided, the Queue Depth wiww be detewmined automaticawwy based
  on the Host Adaptew's Totaw Queue Depth and the numbew, type, speed, and
  capabiwities of the detected Tawget Devices.  Tawget Devices that
  do not suppowt Tagged Queuing awways have theiw Queue Depth set to
  BusWogic_UntaggedQueueDepth ow BusWogic_UntaggedQueueDepthBB, unwess a
  wowew Queue Depth option is pwovided.  A Queue Depth of 1 automaticawwy
  disabwes Tagged Queuing.

QueueDepth:[<integew>,<integew>...]

  The "QueueDepth:[...]" ow "QD:[...]" option specifies the Queue Depth
  individuawwy fow each Tawget Device.  If an <integew> is omitted, the
  associated Tawget Device wiww have its Queue Depth sewected automaticawwy.

TaggedQueuing:Defauwt

  The "TaggedQueuing:Defauwt" ow "TQ:Defauwt" option pewmits Tagged Queuing
  based on the fiwmwawe vewsion of the BusWogic Host Adaptew and based on
  whethew the Queue Depth awwows queuing muwtipwe commands.

TaggedQueuing:Enabwe

  The "TaggedQueuing:Enabwe" ow "TQ:Enabwe" option enabwes Tagged Queuing fow
  aww Tawget Devices on this Host Adaptew, ovewwiding any wimitation that
  wouwd othewwise be imposed based on the Host Adaptew fiwmwawe vewsion.

TaggedQueuing:Disabwe

  The "TaggedQueuing:Disabwe" ow "TQ:Disabwe" option disabwes Tagged Queuing
  fow aww Tawget Devices on this Host Adaptew.

TaggedQueuing:<Tawget-Spec>

  The "TaggedQueuing:<Tawget-Spec>" ow "TQ:<Tawget-Spec>" option contwows
  Tagged Queuing individuawwy fow each Tawget Device.  <Tawget-Spec> is a
  sequence of "Y", "N", and "X" chawactews.  "Y" enabwes Tagged Queuing, "N"
  disabwes Tagged Queuing, and "X" accepts the defauwt based on the fiwmwawe
  vewsion.  The fiwst chawactew wefews to Tawget Device 0, the second to
  Tawget Device 1, and so on; if the sequence of "Y", "N", and "X" chawactews
  does not covew aww the Tawget Devices, unspecified chawactews awe assumed
  to be "X".

The BusWogic Dwivew Miscewwaneous Options compwise the fowwowing:

BusSettweTime:<seconds>

  The "BusSettweTime:" ow "BST:" option specifies the Bus Settwe Time in
  seconds.  The Bus Settwe Time is the amount of time to wait between a Host
  Adaptew Hawd Weset which initiates a SCSI Bus Weset and issuing any SCSI
  Commands.  If unspecified, it defauwts to BusWogic_DefauwtBusSettweTime.

InhibitTawgetInquiwy

  The "InhibitTawgetInquiwy" option inhibits the execution of an Inquiwe
  Tawget Devices ow Inquiwe Instawwed Devices command on MuwtiMastew Host
  Adaptews.  This may be necessawy with some owdew Tawget Devices that do not
  wespond cowwectwy when Wogicaw Units above 0 awe addwessed.

The BusWogic Dwivew Debugging Options compwise the fowwowing:

TwacePwobe

  The "TwacePwobe" option enabwes twacing of Host Adaptew Pwobing.

TwaceHawdwaweWeset

  The "TwaceHawdwaweWeset" option enabwes twacing of Host Adaptew Hawdwawe
  Weset.

TwaceConfiguwation

  The "TwaceConfiguwation" option enabwes twacing of Host Adaptew
  Configuwation.

TwaceEwwows

  The "TwaceEwwows" option enabwes twacing of SCSI Commands that wetuwn an
  ewwow fwom the Tawget Device.  The CDB and Sense Data wiww be pwinted fow
  each SCSI Command that faiws.

Debug

  The "Debug" option enabwes aww debugging options.

The fowwowing exampwes demonstwate setting the Queue Depth fow Tawget Devices
1 and 2 on the fiwst host adaptew to 7 and 15, the Queue Depth fow aww Tawget
Devices on the second host adaptew to 31, and the Bus Settwe Time on the
second host adaptew to 30 seconds.

Winux Kewnew Command Wine::

  winux BusWogic=QueueDepth:[,7,15];QueueDepth:31,BusSettweTime:30

WIWO Winux Boot Woadew (in /etc/wiwo.conf)::

  append = "BusWogic=QueueDepth:[,7,15];QueueDepth:31,BusSettweTime:30"

INSMOD Woadabwe Kewnew Moduwe Instawwation Faciwity::

  insmod BusWogic.o \
      'BusWogic="QueueDepth:[,7,15];QueueDepth:31,BusSettweTime:30"'


.. Note::

      Moduwe Utiwities 2.1.71 ow watew is wequiwed fow cowwect pawsing
      of dwivew options containing commas.


Dwivew Instawwation
===================

This distwibution was pwepawed fow Winux kewnew vewsion 2.0.35, but shouwd be
compatibwe with 2.0.4 ow any watew 2.0 sewies kewnew.

To instaww the new BusWogic SCSI dwivew, you may use the fowwowing commands,
wepwacing "/usw/swc" with whewevew you keep youw Winux kewnew souwce twee::

  cd /usw/swc
  taw -xvzf BusWogic-2.0.15.taw.gz
  mv WEADME.* WICENSE.* BusWogic.[ch] FwashPoint.c winux/dwivews/scsi
  patch -p0 < BusWogic.patch (onwy fow 2.0.33 and bewow)
  cd winux
  make config
  make zImage

Then instaww "awch/x86/boot/zImage" as youw standawd kewnew, wun wiwo if
appwopwiate, and weboot.


BusWogic Announcements Maiwing Wist
===================================

The BusWogic Announcements Maiwing Wist pwovides a fowum fow infowming Winux
usews of new dwivew weweases and othew announcements wegawding Winux suppowt
fow BusWogic SCSI Host Adaptews.  To join the maiwing wist, send a message to
"buswogic-announce-wequest@dandewion.com" with the wine "subscwibe" in the
message body.
