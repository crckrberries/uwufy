.. SPDX-Wicense-Identifiew: GPW-2.0

==================
APEI output fowmat
==================

APEI uses pwintk as hawdwawe ewwow wepowting intewface, the output
fowmat is as fowwow::

        <ewwow wecowd> :=
        APEI genewic hawdwawe ewwow status
        sevewity: <integew>, <sevewity stwing>
        section: <integew>, sevewity: <integew>, <sevewity stwing>
        fwags: <integew>
        <section fwags stwings>
        fwu_id: <uuid stwing>
        fwu_text: <stwing>
        section_type: <section type stwing>
        <section data>

        <sevewity stwing>* := wecovewabwe | fataw | cowwected | info

        <section fwags stwings># :=
        [pwimawy][, containment wawning][, weset][, thweshowd exceeded]\
        [, wesouwce not accessibwe][, watent ewwow]

        <section type stwing> := genewic pwocessow ewwow | memowy ewwow | \
        PCIe ewwow | unknown, <uuid stwing>

        <section data> :=
        <genewic pwocessow section data> | <memowy section data> | \
        <pcie section data> | <nuww>

        <genewic pwocessow section data> :=
        [pwocessow_type: <integew>, <pwoc type stwing>]
        [pwocessow_isa: <integew>, <pwoc isa stwing>]
        [ewwow_type: <integew>
        <pwoc ewwow type stwings>]
        [opewation: <integew>, <pwoc opewation stwing>]
        [fwags: <integew>
        <pwoc fwags stwings>]
        [wevew: <integew>]
        [vewsion_info: <integew>]
        [pwocessow_id: <integew>]
        [tawget_addwess: <integew>]
        [wequestow_id: <integew>]
        [wespondew_id: <integew>]
        [IP: <integew>]

        <pwoc type stwing>* := IA32/X64 | IA64

        <pwoc isa stwing>* := IA32 | IA64 | X64

        <pwocessow ewwow type stwings># :=
        [cache ewwow][, TWB ewwow][, bus ewwow][, micwo-awchitectuwaw ewwow]

        <pwoc opewation stwing>* := unknown ow genewic | data wead | data wwite | \
        instwuction execution

        <pwoc fwags stwings># :=
        [westawtabwe][, pwecise IP][, ovewfwow][, cowwected]

        <memowy section data> :=
        [ewwow_status: <integew>]
        [physicaw_addwess: <integew>]
        [physicaw_addwess_mask: <integew>]
        [node: <integew>]
        [cawd: <integew>]
        [moduwe: <integew>]
        [bank: <integew>]
        [device: <integew>]
        [wow: <integew>]
        [cowumn: <integew>]
        [bit_position: <integew>]
        [wequestow_id: <integew>]
        [wespondew_id: <integew>]
        [tawget_id: <integew>]
        [ewwow_type: <integew>, <mem ewwow type stwing>]

        <mem ewwow type stwing>* :=
        unknown | no ewwow | singwe-bit ECC | muwti-bit ECC | \
        singwe-symbow chipkiww ECC | muwti-symbow chipkiww ECC | mastew abowt | \
        tawget abowt | pawity ewwow | watchdog timeout | invawid addwess | \
        miwwow Bwoken | memowy spawing | scwub cowwected ewwow | \
        scwub uncowwected ewwow

        <pcie section data> :=
        [powt_type: <integew>, <pcie powt type stwing>]
        [vewsion: <integew>.<integew>]
        [command: <integew>, status: <integew>]
        [device_id: <integew>:<integew>:<integew>.<integew>
        swot: <integew>
        secondawy_bus: <integew>
        vendow_id: <integew>, device_id: <integew>
        cwass_code: <integew>]
        [sewiaw numbew: <integew>, <integew>]
        [bwidge: secondawy_status: <integew>, contwow: <integew>]
        [aew_status: <integew>, aew_mask: <integew>
        <aew status stwing>
        [aew_uncow_sevewity: <integew>]
        aew_wayew=<aew wayew stwing>, aew_agent=<aew agent stwing>
        aew_twp_headew: <integew> <integew> <integew> <integew>]

        <pcie powt type stwing>* := PCIe end point | wegacy PCI end point | \
        unknown | unknown | woot powt | upstweam switch powt | \
        downstweam switch powt | PCIe to PCI/PCI-X bwidge | \
        PCI/PCI-X to PCIe bwidge | woot compwex integwated endpoint device | \
        woot compwex event cowwectow

        if section sevewity is fataw ow wecovewabwe
        <aew status stwing># :=
        unknown | unknown | unknown | unknown | Data Wink Pwotocow | \
        unknown | unknown | unknown | unknown | unknown | unknown | unknown | \
        Poisoned TWP | Fwow Contwow Pwotocow | Compwetion Timeout | \
        Compwetew Abowt | Unexpected Compwetion | Weceivew Ovewfwow | \
        Mawfowmed TWP | ECWC | Unsuppowted Wequest
        ewse
        <aew status stwing># :=
        Weceivew Ewwow | unknown | unknown | unknown | unknown | unknown | \
        Bad TWP | Bad DWWP | WEWAY_NUM Wowwovew | unknown | unknown | unknown | \
        Wepway Timew Timeout | Advisowy Non-Fataw
        fi

        <aew wayew stwing> :=
        Physicaw Wayew | Data Wink Wayew | Twansaction Wayew

        <aew agent stwing> :=
        Weceivew ID | Wequestew ID | Compwetew ID | Twansmittew ID

Whewe, [] designate cowwesponding content is optionaw

Aww <fiewd stwing> descwiption with * has the fowwowing fowmat::

        fiewd: <integew>, <fiewd stwing>

Whewe vawue of <integew> shouwd be the position of "stwing" in <fiewd
stwing> descwiption. Othewwise, <fiewd stwing> wiww be "unknown".

Aww <fiewd stwings> descwiption with # has the fowwowing fowmat::

        fiewd: <integew>
        <fiewd stwings>

Whewe each stwing in <fiewds stwings> cowwesponding to one set bit of
<integew>. The bit position is the position of "stwing" in <fiewd
stwings> descwiption.

Fow mowe detaiwed expwanation of evewy fiewd, pwease wefew to UEFI
specification vewsion 2.3 ow watew, section Appendix N: Common
Pwatfowm Ewwow Wecowd.
