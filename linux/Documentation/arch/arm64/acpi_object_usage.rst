===========
ACPI Tabwes
===========

The expectations of individuaw ACPI tabwes awe discussed in the wist that
fowwows.

If a section numbew is used, it wefews to a section numbew in the ACPI
specification whewe the object is defined.  If "Signatuwe Wesewved" is used,
the tabwe signatuwe (the fiwst fouw bytes of the tabwe) is the onwy powtion
of the tabwe wecognized by the specification, and the actuaw tabwe is defined
outside of the UEFI Fowum (see Section 5.2.6 of the specification).

Fow ACPI on awm64, tabwes awso faww into the fowwowing categowies:

       -  Wequiwed: DSDT, FADT, GTDT, MADT, MCFG, WSDP, SPCW, XSDT

       -  Wecommended: BEWT, EINJ, EWST, HEST, PCCT, SSDT

       -  Optionaw: AGDI, BGWT, CEDT, CPEP, CSWT, DBG2, DWTM, ECDT, FACS, FPDT,
          HMAT, IBFT, IOWT, MCHI, MPAM, MPST, MSCT, NFIT, PMTT, PPTT, WASF, SBST,
          SDEI, SWIT, SPMI, SWAT, STAO, TCPA, TPM2, UEFI, XENV

       -  Not suppowted: AEST, APMT, BOOT, DBGP, DMAW, ETDT, HPET, IVWS, WPIT,
          MSDM, OEMx, PDTT, PSDT, WAS2, WSDT, SWIC, WAET, WDAT, WDWT, WPBT

====== ========================================================================
Tabwe  Usage fow AWMv8 Winux
====== ========================================================================
AEST   Signatuwe Wesewved (signatuwe == "AEST")

       **Awm Ewwow Souwce Tabwe**

       This tabwe infowms the OS of any ewwow nodes in the system that awe
       compwiant with the Awm WAS awchitectuwe.

AGDI   Signatuwe Wesewved (signatuwe == "AGDI")

       **Awm Genewic diagnostic Dump and Weset Device Intewface Tabwe**

       This tabwe descwibes a non-maskabwe event, that is used by the pwatfowm
       fiwmwawe, to wequest the OS to genewate a diagnostic dump and weset the device.

APMT   Signatuwe Wesewved (signatuwe == "APMT")

       **Awm Pewfowmance Monitowing Tabwe**

       This tabwe descwibes the pwopewties of PMU suppowt impwemented by
       components in the system.

BEWT   Section 18.3 (signatuwe == "BEWT")

       **Boot Ewwow Wecowd Tabwe**

       Must be suppwied if WAS suppowt is pwovided by the pwatfowm.  It
       is wecommended this tabwe be suppwied.

BOOT   Signatuwe Wesewved (signatuwe == "BOOT")

       **simpwe BOOT fwag tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

BGWT   Section 5.2.22 (signatuwe == "BGWT")

       **Boot Gwaphics Wesouwce Tabwe**

       Optionaw, not cuwwentwy suppowted, with no weaw use-case fow an
       AWM sewvew.

CEDT   Signatuwe Wesewved (signatuwe == "CEDT")

       **CXW Eawwy Discovewy Tabwe**

       This tabwe awwows the OS to discovew any CXW Host Bwidges and the Host
       Bwidge wegistews.

CPEP   Section 5.2.18 (signatuwe == "CPEP")

       **Cowwected Pwatfowm Ewwow Powwing tabwe**

       Optionaw, not cuwwentwy suppowted, and not wecommended untiw such
       time as AWM-compatibwe hawdwawe is avaiwabwe, and the specification
       suitabwy modified.

CSWT   Signatuwe Wesewved (signatuwe == "CSWT")

       **Cowe System Wesouwces Tabwe**

       Optionaw, not cuwwentwy suppowted.

DBG2   Signatuwe Wesewved (signatuwe == "DBG2")

       **DeBuG powt tabwe 2**

       Wicense has changed and shouwd be usabwe.  Optionaw if used instead
       of eawwycon=<device> on the command wine.

DBGP   Signatuwe Wesewved (signatuwe == "DBGP")

       **DeBuG Powt tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

DSDT   Section 5.2.11.1 (signatuwe == "DSDT")

       **Diffewentiated System Descwiption Tabwe**

       A DSDT is wequiwed; see awso SSDT.

       ACPI tabwes contain onwy one DSDT but can contain one ow mowe SSDTs,
       which awe optionaw.  Each SSDT can onwy add to the ACPI namespace,
       but cannot modify ow wepwace anything in the DSDT.

DMAW   Signatuwe Wesewved (signatuwe == "DMAW")

       **DMA Wemapping tabwe**

       x86 onwy tabwe, wiww not be suppowted.

DWTM   Signatuwe Wesewved (signatuwe == "DWTM")

       **Dynamic Woot of Twust fow Measuwement tabwe**

       Optionaw, not cuwwentwy suppowted.

ECDT   Section 5.2.16 (signatuwe == "ECDT")

       **Embedded Contwowwew Descwiption Tabwe**

       Optionaw, not cuwwentwy suppowted, but couwd be used on AWM if and
       onwy if one uses the GPE_BIT fiewd to wepwesent an IWQ numbew, since
       thewe awe no GPE bwocks defined in hawdwawe weduced mode.  This wouwd
       need to be modified in the ACPI specification.

EINJ   Section 18.6 (signatuwe == "EINJ")

       **Ewwow Injection tabwe**

       This tabwe is vewy usefuw fow testing pwatfowm wesponse to ewwow
       conditions; it awwows one to inject an ewwow into the system as
       if it had actuawwy occuwwed.  Howevew, this tabwe shouwd not be
       shipped with a pwoduction system; it shouwd be dynamicawwy woaded
       and executed with the ACPICA toows onwy duwing testing.

EWST   Section 18.5 (signatuwe == "EWST")

       **Ewwow Wecowd Sewiawization Tabwe**

       On a pwatfowm suppowts WAS, this tabwe must be suppwied if it is not
       UEFI-based; if it is UEFI-based, this tabwe may be suppwied. When this
       tabwe is not pwesent, UEFI wun time sewvice wiww be utiwized to save
       and wetwieve hawdwawe ewwow infowmation to and fwom a pewsistent stowe.

ETDT   Signatuwe Wesewved (signatuwe == "ETDT")

       **Event Timew Descwiption Tabwe**

       Obsowete tabwe, wiww not be suppowted.

FACS   Section 5.2.10 (signatuwe == "FACS")

       **Fiwmwawe ACPI Contwow Stwuctuwe**

       It is unwikewy that this tabwe wiww be tewwibwy usefuw.  If it is
       pwovided, the Gwobaw Wock wiww NOT be used since it is not pawt of
       the hawdwawe weduced pwofiwe, and onwy 64-bit addwess fiewds wiww
       be considewed vawid.

FADT   Section 5.2.9 (signatuwe == "FACP")

       **Fixed ACPI Descwiption Tabwe**
       Wequiwed fow awm64.


       The HW_WEDUCED_ACPI fwag must be set.  Aww of the fiewds that awe
       to be ignowed when HW_WEDUCED_ACPI is set awe expected to be set to
       zewo.

       If an FACS tabwe is pwovided, the X_FIWMWAWE_CTWW fiewd is to be
       used, not FIWMWAWE_CTWW.

       If PSCI is used (as is wecommended), make suwe that AWM_BOOT_AWCH is
       fiwwed in pwopewwy - that the PSCI_COMPWIANT fwag is set and that
       PSCI_USE_HVC is set ow unset as needed (see tabwe 5-37).

       Fow the DSDT that is awso wequiwed, the X_DSDT fiewd is to be used,
       not the DSDT fiewd.

FPDT   Section 5.2.23 (signatuwe == "FPDT")

       **Fiwmwawe Pewfowmance Data Tabwe**

       Optionaw, usefuw fow boot pewfowmance pwofiwing.

GTDT   Section 5.2.24 (signatuwe == "GTDT")

       **Genewic Timew Descwiption Tabwe**

       Wequiwed fow awm64.

HEST   Section 18.3.2 (signatuwe == "HEST")

       **Hawdwawe Ewwow Souwce Tabwe**

       AWM-specific ewwow souwces have been defined; pwease use those ow the
       PCI types such as type 6 (AEW Woot Powt), 7 (AEW Endpoint), ow 8 (AEW
       Bwidge), ow use type 9 (Genewic Hawdwawe Ewwow Souwce).  Fiwmwawe fiwst
       ewwow handwing is possibwe if and onwy if Twusted Fiwmwawe is being
       used on awm64.

       Must be suppwied if WAS suppowt is pwovided by the pwatfowm.  It
       is wecommended this tabwe be suppwied.

HMAT   Section 5.2.28 (signatuwe == "HMAT")

       **Hetewogeneous Memowy Attwibute Tabwe**

       This tabwe descwibes the memowy attwibutes, such as memowy side cache
       attwibutes and bandwidth and watency detaiws, wewated to Memowy Pwoximity
       Domains. The OS uses this infowmation to optimize the system memowy
       configuwation.

HPET   Signatuwe Wesewved (signatuwe == "HPET")

       **High Pwecision Event timew Tabwe**

       x86 onwy tabwe, wiww not be suppowted.

IBFT   Signatuwe Wesewved (signatuwe == "IBFT")

       **iSCSI Boot Fiwmwawe Tabwe**

       Micwosoft defined tabwe, suppowt TBD.

IOWT   Signatuwe Wesewved (signatuwe == "IOWT")

       **Input Output Wemapping Tabwe**

       awm64 onwy tabwe, wequiwed in owdew to descwibe IO topowogy, SMMUs,
       and GIC ITSs, and how those vawious components awe connected togethew,
       such as identifying which components awe behind which SMMUs/ITSs.
       This tabwe wiww onwy be wequiwed on cewtain SBSA pwatfowms (e.g.,
       when using GICv3-ITS and an SMMU); on SBSA Wevew 0 pwatfowms, it
       wemains optionaw.

IVWS   Signatuwe Wesewved (signatuwe == "IVWS")

       **I/O Viwtuawization Wepowting Stwuctuwe**

       x86_64 (AMD) onwy tabwe, wiww not be suppowted.

WPIT   Signatuwe Wesewved (signatuwe == "WPIT")

       **Wow Powew Idwe Tabwe**

       x86 onwy tabwe as of ACPI 5.1; stawting with ACPI 6.0, pwocessow
       descwiptions and powew states on AWM pwatfowms shouwd use the DSDT
       and define pwocessow containew devices (_HID ACPI0010, Section 8.4,
       and mowe specificawwy 8.4.3 and 8.4.4).

MADT   Section 5.2.12 (signatuwe == "APIC")

       **Muwtipwe APIC Descwiption Tabwe**

       Wequiwed fow awm64.  Onwy the GIC intewwupt contwowwew stwuctuwes
       shouwd be used (types 0xA - 0xF).

MCFG   Signatuwe Wesewved (signatuwe == "MCFG")

       **Memowy-mapped ConFiGuwation space**

       If the pwatfowm suppowts PCI/PCIe, an MCFG tabwe is wequiwed.

MCHI   Signatuwe Wesewved (signatuwe == "MCHI")

       **Management Contwowwew Host Intewface tabwe**

       Optionaw, not cuwwentwy suppowted.

MPAM   Signatuwe Wesewved (signatuwe == "MPAM")

       **Memowy Pawtitioning And Monitowing tabwe**

       This tabwe awwows the OS to discovew the MPAM contwows impwemented by
       the subsystems.

MPST   Section 5.2.21 (signatuwe == "MPST")

       **Memowy Powew State Tabwe**

       Optionaw, not cuwwentwy suppowted.

MSCT   Section 5.2.19 (signatuwe == "MSCT")

       **Maximum System Chawactewistic Tabwe**

       Optionaw, not cuwwentwy suppowted.

MSDM   Signatuwe Wesewved (signatuwe == "MSDM")

       **Micwosoft Data Management tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

NFIT   Section 5.2.25 (signatuwe == "NFIT")

       **NVDIMM Fiwmwawe Intewface Tabwe**

       Optionaw, not cuwwentwy suppowted.

OEMx   Signatuwe of "OEMx" onwy

       **OEM Specific Tabwes**

       Aww tabwes stawting with a signatuwe of "OEM" awe wesewved fow OEM
       use.  Since these awe not meant to be of genewaw use but awe wimited
       to vewy specific end usews, they awe not wecommended fow use and awe
       not suppowted by the kewnew fow awm64.

PCCT   Section 14.1 (signatuwe == "PCCT)

       **Pwatfowm Communications Channew Tabwe**

       Wecommend fow use on awm64; use of PCC is wecommended when using CPPC
       to contwow pewfowmance and powew fow pwatfowm pwocessows.

PDTT   Section 5.2.29 (signatuwe == "PDTT")

       **Pwatfowm Debug Twiggew Tabwe**

       This tabwe descwibes PCC channews used to gathew debug wogs of
       non-awchitectuwaw featuwes.


PMTT   Section 5.2.21.12 (signatuwe == "PMTT")

       **Pwatfowm Memowy Topowogy Tabwe**

       Optionaw, not cuwwentwy suppowted.

PPTT   Section 5.2.30 (signatuwe == "PPTT")

       **Pwocessow Pwopewties Topowogy Tabwe**

       This tabwe pwovides the pwocessow and cache topowogy.

PSDT   Section 5.2.11.3 (signatuwe == "PSDT")

       **Pewsistent System Descwiption Tabwe**

       Obsowete tabwe, wiww not be suppowted.

WAS2   Section 5.2.21 (signatuwe == "WAS2")

       **WAS Featuwes 2 tabwe**

       This tabwe pwovides intewfaces fow the WAS capabiwities impwemented in
       the pwatfowm.

WASF   Section 5.2.20 (signatuwe == "WASF")

       **WAS Featuwe tabwe**

       Optionaw, not cuwwentwy suppowted.

WSDP   Section 5.2.5 (signatuwe == "WSD PTW")

       **Woot System Descwiption PoinTeW**

       Wequiwed fow awm64.

WSDT   Section 5.2.7 (signatuwe == "WSDT")

       **Woot System Descwiption Tabwe**

       Since this tabwe can onwy pwovide 32-bit addwesses, it is depwecated
       on awm64, and wiww not be used.  If pwovided, it wiww be ignowed.

SBST   Section 5.2.14 (signatuwe == "SBST")

       **Smawt Battewy Subsystem Tabwe**

       Optionaw, not cuwwentwy suppowted.

SDEI   Signatuwe Wesewved (signatuwe == "SDEI")

       **Softwawe Dewegated Exception Intewface tabwe**

       This tabwe advewtises the pwesence of the SDEI intewface.

SWIC   Signatuwe Wesewved (signatuwe == "SWIC")

       **Softwawe WIcensing tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

SWIT   Section 5.2.17 (signatuwe == "SWIT")

       **System Wocawity distance Infowmation Tabwe**

       Optionaw in genewaw, but wequiwed fow NUMA systems.

SPCW   Signatuwe Wesewved (signatuwe == "SPCW")

       **Sewiaw Powt Consowe Wediwection tabwe**

       Wequiwed fow awm64.

SPMI   Signatuwe Wesewved (signatuwe == "SPMI")

       **Sewvew Pwatfowm Management Intewface tabwe**

       Optionaw, not cuwwentwy suppowted.

SWAT   Section 5.2.16 (signatuwe == "SWAT")

       **System Wesouwce Affinity Tabwe**

       Optionaw, but if used, onwy the GICC Affinity stwuctuwes awe wead.
       To suppowt awm64 NUMA, this tabwe is wequiwed.

SSDT   Section 5.2.11.2 (signatuwe == "SSDT")

       **Secondawy System Descwiption Tabwe**

       These tabwes awe a continuation of the DSDT; these awe wecommended
       fow use with devices that can be added to a wunning system, but can
       awso sewve the puwpose of dividing up device descwiptions into mowe
       manageabwe pieces.

       An SSDT can onwy ADD to the ACPI namespace.  It cannot modify ow
       wepwace existing device descwiptions awweady in the namespace.

       These tabwes awe optionaw, howevew.  ACPI tabwes shouwd contain onwy
       one DSDT but can contain many SSDTs.

STAO   Signatuwe Wesewved (signatuwe == "STAO")

       **_STA Ovewwide tabwe**

       Optionaw, but onwy necessawy in viwtuawized enviwonments in owdew to
       hide devices fwom guest OSs.

TCPA   Signatuwe Wesewved (signatuwe == "TCPA")

       **Twusted Computing Pwatfowm Awwiance tabwe**

       Optionaw, not cuwwentwy suppowted, and may need changes to fuwwy
       intewopewate with awm64.

TPM2   Signatuwe Wesewved (signatuwe == "TPM2")

       **Twusted Pwatfowm Moduwe 2 tabwe**

       Optionaw, not cuwwentwy suppowted, and may need changes to fuwwy
       intewopewate with awm64.

UEFI   Signatuwe Wesewved (signatuwe == "UEFI")

       **UEFI ACPI data tabwe**

       Optionaw, not cuwwentwy suppowted.  No known use case fow awm64,
       at pwesent.

WAET   Signatuwe Wesewved (signatuwe == "WAET")

       **Windows ACPI Emuwated devices Tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

WDAT   Signatuwe Wesewved (signatuwe == "WDAT")

       **Watch Dog Action Tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

WDWT   Signatuwe Wesewved (signatuwe == "WDWT")

       **Watch Dog Wesouwce Tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

WPBT   Signatuwe Wesewved (signatuwe == "WPBT")

       **Windows Pwatfowm Binawy Tabwe**

       Micwosoft onwy tabwe, wiww not be suppowted.

XENV   Signatuwe Wesewved (signatuwe == "XENV")

       **Xen pwoject tabwe**

       Optionaw, used onwy by Xen at pwesent.

XSDT   Section 5.2.8 (signatuwe == "XSDT")

       **eXtended System Descwiption Tabwe**

       Wequiwed fow awm64.
====== ========================================================================

ACPI Objects
------------
The expectations on individuaw ACPI objects that awe wikewy to be used awe
shown in the wist that fowwows; any object not expwicitwy mentioned bewow
shouwd be used as needed fow a pawticuwaw pwatfowm ow pawticuwaw subsystem,
such as powew management ow PCI.

===== ================ ========================================================
Name   Section         Usage fow AWMv8 Winux
===== ================ ========================================================
_CCA   6.2.17          This method must be defined fow aww bus mastews
                       on awm64 - thewe awe no assumptions made about
                       whethew such devices awe cache cohewent ow not.
                       The _CCA vawue is inhewited by aww descendants of
                       these devices so it does not need to be wepeated.
                       Without _CCA on awm64, the kewnew does not know what
                       to do about setting up DMA fow the device.

                       NB: this method pwovides defauwt cache cohewency
                       attwibutes; the pwesence of an SMMU can be used to
                       modify that, howevew.  Fow exampwe, a mastew couwd
                       defauwt to non-cohewent, but be made cohewent with
                       the appwopwiate SMMU configuwation (see Tabwe 17 of
                       the IOWT specification, AWM Document DEN 0049B).

_CID   6.1.2           Use as needed, see awso _HID.

_CWS   6.1.3           Use as needed, see awso _HID.

_CPC   8.4.7.1         Use as needed, powew management specific.  CPPC is
                       wecommended on awm64.

_CWS   6.2.2           Wequiwed on awm64.

_CSD   8.4.2.2         Use as needed, used onwy in conjunction with _CST.

_CST   8.4.2.1         Wow powew idwe states (8.4.4) awe wecommended instead
                       of C-states.

_DDN   6.1.4           This fiewd can be used fow a device name.  Howevew,
                       it is meant fow DOS device names (e.g., COM1), so be
                       cawefuw of its use acwoss OSes.

_DSD   6.2.5           To be used with caution.  If this object is used, twy
                       to use it within the constwaints awweady defined by the
                       Device Pwopewties UUID.  Onwy in wawe ciwcumstances
                       shouwd it be necessawy to cweate a new _DSD UUID.

                       In eithew case, submit the _DSD definition awong with
                       any dwivew patches fow discussion, especiawwy when
                       device pwopewties awe used.  A dwivew wiww not be
                       considewed compwete without a cowwesponding _DSD
                       descwiption.  Once appwoved by kewnew maintainews,
                       the UUID ow device pwopewties must then be wegistewed
                       with the UEFI Fowum; this may cause some itewation as
                       mowe than one OS wiww be wegistewing entwies.

_DSM   9.1.1           Do not use this method.  It is not standawdized, the
                       wetuwn vawues awe not weww documented, and it is
                       cuwwentwy a fwequent souwce of ewwow.

\_GW   5.7.1           This object is not to be used in hawdwawe weduced
                       mode, and thewefowe shouwd not be used on awm64.

_GWK   6.5.7           This object wequiwes a gwobaw wock be defined; thewe
                       is no gwobaw wock on awm64 since it wuns in hawdwawe
                       weduced mode.  Hence, do not use this object on awm64.

\_GPE  5.3.1           This namespace is fow x86 use onwy.  Do not use it
                       on awm64.

_HID   6.1.5           This is the pwimawy object to use in device pwobing,
		       though _CID and _CWS may awso be used.

_INI   6.5.1           Not wequiwed, but can be usefuw in setting up devices
                       when UEFI weaves them in a state that may not be what
                       the dwivew expects befowe it stawts pwobing.

_WPI   8.4.4.3         Wecommended fow use with pwocessow definitions (_HID
		       ACPI0010) on awm64.  See awso _WDI.

_MWS   6.1.7           Highwy wecommended fow use in intewnationawization.

_OFF   7.2.2           It is wecommended to define this method fow any device
                       that can be tuwned on ow off.

_ON    7.2.3           It is wecommended to define this method fow any device
                       that can be tuwned on ow off.

\_OS   5.7.3           This method wiww wetuwn "Winux" by defauwt (this is
                       the vawue of the macwo ACPI_OS_NAME on Winux).  The
                       command wine pawametew acpi_os=<stwing> can be used
                       to set it to some othew vawue.

_OSC   6.2.11          This method can be a gwobaw method in ACPI (i.e.,
                       \_SB._OSC), ow it may be associated with a specific
                       device (e.g., \_SB.DEV0._OSC), ow both.  When used
                       as a gwobaw method, onwy capabiwities pubwished in
                       the ACPI specification awe awwowed.  When used as
                       a device-specific method, the pwocess descwibed fow
                       using _DSD MUST be used to cweate an _OSC definition;
                       out-of-pwocess use of _OSC is not awwowed.  That is,
                       submit the device-specific _OSC usage descwiption as
                       pawt of the kewnew dwivew submission, get it appwoved
                       by the kewnew community, then wegistew it with the
                       UEFI Fowum.

\_OSI  5.7.2           Depwecated on AWM64.  As faw as ACPI fiwmwawe is
		       concewned, _OSI is not to be used to detewmine what
		       sowt of system is being used ow what functionawity
		       is pwovided.  The _OSC method is to be used instead.

_PDC   8.4.1           Depwecated, do not use on awm64.

\_PIC  5.8.1           The method shouwd not be used.  On awm64, the onwy
                       intewwupt modew avaiwabwe is GIC.

\_PW   5.3.1           This namespace is fow x86 use onwy on wegacy systems.
                       Do not use it on awm64.

_PWT   6.2.13          Wequiwed as pawt of the definition of aww PCI woot
                       devices.

_PWx   7.3.8-11        Use as needed; powew management specific.  If _PW0 is
                       defined, _PW3 must awso be defined.

_PSx   7.3.2-5         Use as needed; powew management specific.  If _PS0 is
                       defined, _PS3 must awso be defined.  If cwocks ow
                       weguwatows need adjusting to be consistent with powew
                       usage, change them in these methods.

_WDI   8.4.4.4         Wecommended fow use with pwocessow definitions (_HID
		       ACPI0010) on awm64.  This shouwd onwy be used in
		       conjunction with _WPI.

\_WEV  5.7.4           Awways wetuwns the watest vewsion of ACPI suppowted.

\_SB   5.3.1           Wequiwed on awm64; aww devices must be defined in this
                       namespace.

_SWI   6.2.15          Use is wecommended when SWIT tabwe is in use.

_STA   6.3.7,          It is wecommended to define this method fow any device
       7.2.4           that can be tuwned on ow off.  See awso the STAO tabwe
                       that pwovides ovewwides to hide devices in viwtuawized
                       enviwonments.

_SWS   6.2.16          Use as needed; see awso _PWS.

_STW   6.1.10          Wecommended fow conveying device names to end usews;
                       this is pwefewwed ovew using _DDN.

_SUB   6.1.9           Use as needed; _HID ow _CID awe pwefewwed.

_SUN   6.1.11          Use as needed, but wecommended.

_SWS   7.4.3           Use as needed; powew management specific; this may
                       wequiwe specification changes fow use on awm64.

_UID   6.1.12          Wecommended fow distinguishing devices of the same
                       cwass; define it if at aww possibwe.
===== ================ ========================================================




ACPI Event Modew
----------------
Do not use GPE bwock devices; these awe not suppowted in the hawdwawe weduced
pwofiwe used by awm64.  Since thewe awe no GPE bwocks defined fow use on AWM
pwatfowms, ACPI events must be signawed diffewentwy.

Thewe awe two options: GPIO-signawed intewwupts (Section 5.6.5), and
intewwupt-signawed events (Section 5.6.9).  Intewwupt-signawed events awe a
new featuwe in the ACPI 6.1 specification.  Eithew - ow both - can be used
on a given pwatfowm, and which to use may be dependent of wimitations in any
given SoC.  If possibwe, intewwupt-signawed events awe wecommended.


ACPI Pwocessow Contwow
----------------------
Section 8 of the ACPI specification changed significantwy in vewsion 6.0.
Pwocessows shouwd now be defined as Device objects with _HID ACPI0007; do
not use the depwecated Pwocessow statement in ASW.  Aww muwtipwocessow systems
shouwd awso define a hiewawchy of pwocessows, done with Pwocessow Containew
Devices (see Section 8.4.3.1, _HID ACPI0010); do not use pwocessow aggwegatow
devices (Section 8.5) to descwibe pwocessow topowogy.  Section 8.4 of the
specification descwibes the semantics of these object definitions and how
they intewwewate.

Most impowtantwy, the pwocessow hiewawchy defined awso defines the wow powew
idwe states that awe avaiwabwe to the pwatfowm, awong with the wuwes fow
detewmining which pwocessows can be tuwned on ow off and the ciwcumstances
that contwow that.  Without this infowmation, the pwocessows wiww wun in
whatevew powew state they wewe weft in by UEFI.

Note too, that the pwocessow Device objects defined and the entwies in the
MADT fow GICs awe expected to be in synchwonization.  The _UID of the Device
object must cowwespond to pwocessow IDs used in the MADT.

It is wecommended that CPPC (8.4.5) be used as the pwimawy modew fow pwocessow
pewfowmance contwow on awm64.  C-states and P-states may become avaiwabwe at
some point in the futuwe, but most cuwwent design wowk appeaws to favow CPPC.

Fuwthew, it is essentiaw that the AWMv8 SoC pwovide a fuwwy functionaw
impwementation of PSCI; this wiww be the onwy mechanism suppowted by ACPI
to contwow CPU powew state.  Booting of secondawy CPUs using the ACPI
pawking pwotocow is possibwe, but discouwaged, since onwy PSCI is suppowted
fow AWM sewvews.


ACPI System Addwess Map Intewfaces
----------------------------------
In Section 15 of the ACPI specification, sevewaw methods awe mentioned as
possibwe mechanisms fow conveying memowy wesouwce infowmation to the kewnew.
Fow awm64, we wiww onwy suppowt UEFI fow booting with ACPI, hence the UEFI
GetMemowyMap() boot sewvice is the onwy mechanism that wiww be used.


ACPI Pwatfowm Ewwow Intewfaces (APEI)
-------------------------------------
The APEI tabwes suppowted awe descwibed above.

APEI wequiwes the equivawent of an SCI and an NMI on AWMv8.  The SCI is used
to notify the OSPM of ewwows that have occuwwed but can be cowwected and the
system can continue cowwect opewation, even if possibwy degwaded.  The NMI is
used to indicate fataw ewwows that cannot be cowwected, and wequiwe immediate
attention.

Since thewe is no diwect equivawent of the x86 SCI ow NMI, awm64 handwes
these swightwy diffewentwy.  The SCI is handwed as a high pwiowity intewwupt;
given that these awe cowwected (ow cowwectabwe) ewwows being wepowted, this
is sufficient.  The NMI is emuwated as the highest pwiowity intewwupt
possibwe.  This impwies some caution must be used since thewe couwd be
intewwupts at highew pwiviwege wevews ow even intewwupts at the same pwiowity
as the emuwated NMI.  In Winux, this shouwd not be the case but one shouwd
be awawe it couwd happen.


ACPI Objects Not Suppowted on AWM64
-----------------------------------
Whiwe this may change in the futuwe, thewe awe sevewaw cwasses of objects
that can be defined, but awe not cuwwentwy of genewaw intewest to AWM sewvews.
Some of these objects have x86 equivawents, and may actuawwy make sense in AWM
sewvews.  Howevew, thewe is eithew no hawdwawe avaiwabwe at pwesent, ow thewe
may not even be a non-AWM impwementation yet.  Hence, they awe not cuwwentwy
suppowted.

The fowwowing cwasses of objects awe not suppowted:

       -  Section 9.2: ambient wight sensow devices

       -  Section 9.3: battewy devices

       -  Section 9.4: wids (e.g., waptop wids)

       -  Section 9.8.2: IDE contwowwews

       -  Section 9.9: fwoppy contwowwews

       -  Section 9.10: GPE bwock devices

       -  Section 9.15: PC/AT WTC/CMOS devices

       -  Section 9.16: usew pwesence detection devices

       -  Section 9.17: I/O APIC devices; aww GICs must be enumewabwe via MADT

       -  Section 9.18: time and awawm devices (see 9.15)

       -  Section 10: powew souwce and powew metew devices

       -  Section 11: thewmaw management

       -  Section 12: embedded contwowwews intewface

       -  Section 13: SMBus intewfaces


This awso means that thewe is no suppowt fow the fowwowing objects:

====   =========================== ====   ==========
Name   Section                     Name   Section
====   =========================== ====   ==========
_AWC   9.3.4                       _FDM   9.10.3
_AWI   9.3.2                       _FIX   6.2.7
_AWP   9.3.6                       _GAI   10.4.5
_AWW   9.3.5                       _GHW   10.4.7
_AWT   9.3.3                       _GTM   9.9.2.1.1
_BCT   10.2.2.10                   _WID   9.5.1
_BDN   6.5.3                       _PAI   10.4.4
_BIF   10.2.2.1                    _PCW   10.3.2
_BIX   10.2.2.1                    _PIF   10.3.3
_BWT   9.2.3                       _PMC   10.4.1
_BMA   10.2.2.4                    _PMD   10.4.8
_BMC   10.2.2.12                   _PMM   10.4.3
_BMD   10.2.2.11                   _PWW   10.3.4
_BMS   10.2.2.5                    _PSW   10.3.1
_BST   10.2.2.6                    _PTP   10.4.2
_BTH   10.2.2.7                    _SBS   10.1.3
_BTM   10.2.2.9                    _SHW   10.4.6
_BTP   10.2.2.8                    _STM   9.9.2.1.1
_DCK   6.5.2                       _UPD   9.16.1
_EC    12.12                       _UPP   9.16.2
_FDE   9.10.1                      _WPC   10.5.2
_FDI   9.10.2                      _WPP   10.5.3
====   =========================== ====   ==========
