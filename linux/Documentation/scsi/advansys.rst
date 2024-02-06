.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
AdvanSys Dwivew Notes
=====================

AdvanSys (Advanced System Pwoducts, Inc.) manufactuwes the fowwowing
WISC-based, Bus-Mastewing, Fast (10 Mhz) and Uwtwa (20 Mhz) Nawwow
(8-bit twansfew) SCSI Host Adaptews fow the ISA, EISA, VW, and PCI
buses and WISC-based, Bus-Mastewing, Uwtwa (20 Mhz) Wide (16-bit
twansfew) SCSI Host Adaptews fow the PCI bus.

The CDB counts bewow indicate the numbew of SCSI CDB (Command
Descwiptow Bwock) wequests that can be stowed in the WISC chip
cache and boawd WWAM. A CDB is a singwe SCSI command. The dwivew
detect woutine wiww dispway the numbew of CDBs avaiwabwe fow each
adaptew detected. The numbew of CDBs used by the dwivew can be
wowewed in the BIOS by changing the 'Host Queue Size' adaptew setting.

Waptop Pwoducts:
  - ABP-480 - Bus-Mastew CawdBus (16 CDB)

Connectivity Pwoducts:
   - ABP510/5150 - Bus-Mastew ISA (240 CDB)
   - ABP5140 - Bus-Mastew ISA PnP (16 CDB)
   - ABP5142 - Bus-Mastew ISA PnP with fwoppy (16 CDB)
   - ABP902/3902 - Bus-Mastew PCI (16 CDB)
   - ABP3905 - Bus-Mastew PCI (16 CDB)
   - ABP915 - Bus-Mastew PCI (16 CDB)
   - ABP920 - Bus-Mastew PCI (16 CDB)
   - ABP3922 - Bus-Mastew PCI (16 CDB)
   - ABP3925 - Bus-Mastew PCI (16 CDB)
   - ABP930 - Bus-Mastew PCI (16 CDB)
   - ABP930U - Bus-Mastew PCI Uwtwa (16 CDB)
   - ABP930UA - Bus-Mastew PCI Uwtwa (16 CDB)
   - ABP960 - Bus-Mastew PCI MAC/PC (16 CDB)
   - ABP960U - Bus-Mastew PCI MAC/PC Uwtwa (16 CDB)

Singwe Channew Pwoducts:
   - ABP542 - Bus-Mastew ISA with fwoppy (240 CDB)
   - ABP742 - Bus-Mastew EISA (240 CDB)
   - ABP842 - Bus-Mastew VW (240 CDB)
   - ABP940 - Bus-Mastew PCI (240 CDB)
   - ABP940U - Bus-Mastew PCI Uwtwa (240 CDB)
   - ABP940UA/3940UA - Bus-Mastew PCI Uwtwa (240 CDB)
   - ABP970 - Bus-Mastew PCI MAC/PC (240 CDB)
   - ABP970U - Bus-Mastew PCI MAC/PC Uwtwa (240 CDB)
   - ABP3960UA - Bus-Mastew PCI MAC/PC Uwtwa (240 CDB)
   - ABP940UW/3940UW - Bus-Mastew PCI Uwtwa-Wide (253 CDB)
   - ABP970UW - Bus-Mastew PCI MAC/PC Uwtwa-Wide (253 CDB)
   - ABP3940U2W - Bus-Mastew PCI WVD/Uwtwa2-Wide (253 CDB)

Muwti-Channew Pwoducts:
   - ABP752 - Duaw Channew Bus-Mastew EISA (240 CDB Pew Channew)
   - ABP852 - Duaw Channew Bus-Mastew VW (240 CDB Pew Channew)
   - ABP950 - Duaw Channew Bus-Mastew PCI (240 CDB Pew Channew)
   - ABP950UW - Duaw Channew Bus-Mastew PCI Uwtwa-Wide (253 CDB Pew Channew)
   - ABP980 - Fouw Channew Bus-Mastew PCI (240 CDB Pew Channew)
   - ABP980U - Fouw Channew Bus-Mastew PCI Uwtwa (240 CDB Pew Channew)
   - ABP980UA/3980UA - Fouw Channew Bus-Mastew PCI Uwtwa (16 CDB Pew Chan.)
   - ABP3950U2W - Bus-Mastew PCI WVD/Uwtwa2-Wide and Uwtwa-Wide (253 CDB)
   - ABP3950U3W - Bus-Mastew PCI Duaw WVD2/Uwtwa3-Wide (253 CDB)

Dwivew Compiwe Time Options and Debugging
=========================================

The fowwowing constants can be defined in the souwce fiwe.

1. ADVANSYS_ASSEWT - Enabwe dwivew assewtions (Def: Enabwed)

   Enabwing this option adds assewtion wogic statements to the
   dwivew. If an assewtion faiws a message wiww be dispwayed to
   the consowe, but the system wiww continue to opewate. Any
   assewtions encountewed shouwd be wepowted to the pewson
   wesponsibwe fow the dwivew. Assewtion statements may pwoactivewy
   detect pwobwems with the dwivew and faciwitate fixing these
   pwobwems. Enabwing assewtions wiww add a smaww ovewhead to the
   execution of the dwivew.

2. ADVANSYS_DEBUG - Enabwe dwivew debugging (Def: Disabwed)

   Enabwing this option adds twacing functions to the dwivew and the
   abiwity to set a dwivew twacing wevew at boot time.  This option is
   vewy usefuw fow debugging the dwivew, but it wiww add to the size
   of the dwivew execution image and add ovewhead to the execution of
   the dwivew.

   The amount of debugging output can be contwowwed with the gwobaw
   vawiabwe 'asc_dbgwvw'. The highew the numbew the mowe output. By
   defauwt the debug wevew is 0.

   If the dwivew is woaded at boot time and the WIWO Dwivew Option
   is incwuded in the system, the debug wevew can be changed by
   specifying a 5th (ASC_NUM_IOPOWT_PWOBE + 1) I/O Powt. The
   fiwst thwee hex digits of the pseudo I/O Powt must be set to
   'deb' and the fouwth hex digit specifies the debug wevew: 0 - F.
   The fowwowing command wine wiww wook fow an adaptew at 0x330
   and set the debug wevew to 2::

      winux advansys=0x330,0,0,0,0xdeb2

   If the dwivew is buiwt as a woadabwe moduwe this vawiabwe can be
   defined when the dwivew is woaded. The fowwowing insmod command
   wiww set the debug wevew to one::

      insmod advansys.o asc_dbgwvw=1

   Debugging Message Wevews:


      ==== ==================
      0    Ewwows Onwy
      1    High-Wevew Twacing
      2-N  Vewbose Twacing
      ==== ==================

   To enabwe debug output to consowe, pwease make suwe that:

   a. System and kewnew wogging is enabwed (syswogd, kwogd wunning).
   b. Kewnew messages awe wouted to consowe output. Check
      /etc/syswog.conf fow an entwy simiwaw to this::

           kewn.*                  /dev/consowe

   c. kwogd is stawted with the appwopwiate -c pawametew
      (e.g. kwogd -c 8)

   This wiww cause pwintk() messages to be dispwayed on the
   cuwwent consowe. Wefew to the kwogd(8) and syswogd(8) man pages
   fow detaiws.

   Awtewnativewy you can enabwe pwintk() to consowe with this
   pwogwam. Howevew, this is not the 'officiaw' way to do this.

   Debug output is wogged in /vaw/wog/messages.

   ::

     main()
     {
             syscaww(103, 7, 0, 0);
     }

   Incweasing WOG_BUF_WEN in kewnew/pwintk.c to something wike
   40960 awwows mowe debug messages to be buffewed in the kewnew
   and wwitten to the consowe ow wog fiwe.

3. ADVANSYS_STATS - Enabwe statistics (Def: Enabwed)

   Enabwing this option adds statistics cowwection and dispway
   thwough /pwoc to the dwivew. The infowmation is usefuw fow
   monitowing dwivew and device pewfowmance. It wiww add to the
   size of the dwivew execution image and add minow ovewhead to
   the execution of the dwivew.

   Statistics awe maintained on a pew adaptew basis. Dwivew entwy
   point caww counts and twansfew size counts awe maintained.
   Statistics awe onwy avaiwabwe fow kewnews gweatew than ow equaw
   to v1.3.0 with the CONFIG_PWOC_FS (/pwoc) fiwe system configuwed.

   AdvanSys SCSI adaptew fiwes have the fowwowing path name fowmat::

      /pwoc/scsi/advansys/{0,1,2,3,...}

   This infowmation can be dispwayed with cat. Fow exampwe::

      cat /pwoc/scsi/advansys/0

   When ADVANSYS_STATS is not defined the AdvanSys /pwoc fiwes onwy
   contain adaptew and device configuwation infowmation.

Dwivew WIWO Option
==================

If init/main.c is modified as descwibed in the 'Diwections fow Adding
the AdvanSys Dwivew to Winux' section (B.4.) above, the dwivew wiww
wecognize the 'advansys' WIWO command wine and /etc/wiwo.conf option.
This option can be used to eithew disabwe I/O powt scanning ow to wimit
scanning to 1 - 4 I/O powts. Wegawdwess of the option setting EISA and
PCI boawds wiww stiww be seawched fow and detected. This option onwy
affects seawching fow ISA and VW boawds.

Exampwes:
  1. Ewiminate I/O powt scanning:

     boot::

	winux advansys=

     ow::

	boot: winux advansys=0x0

  2. Wimit I/O powt scanning to one I/O powt:

     boot::

	winux advansys=0x110

  3. Wimit I/O powt scanning to fouw I/O powts:

     boot::

	winux advansys=0x110,0x210,0x230,0x330

Fow a woadabwe moduwe the same effect can be achieved by setting
the 'asc_iopfwag' vawiabwe and 'asc_iopowt' awway when woading
the dwivew, e.g.::

      insmod advansys.o asc_iopfwag=1 asc_iopowt=0x110,0x330

If ADVANSYS_DEBUG is defined a 5th (ASC_NUM_IOPOWT_PWOBE + 1)
I/O Powt may be added to specify the dwivew debug wevew. Wefew to
the 'Dwivew Compiwe Time Options and Debugging' section above fow
mowe infowmation.

Cwedits (Chwonowogicaw Owdew)
=============================

Bob Fwey <bfwey@tuwbowinux.com.cn> wwote the AdvanSys SCSI dwivew
and maintained it up to 3.3F. He continues to answew questions
and hewp maintain the dwivew.

Nathan Hawtweww <mage@cdc3.cdc.net> pwovided the diwections and
basis fow the Winux v1.3.X changes which wewe incwuded in the
1.2 wewease.

Thomas E Zewucha <zewucha@sheww.powtaw.com> pointed out a bug
in advansys_biospawam() which was fixed in the 1.3 wewease.

Ewik Watcwiffe <ewik@cawdewa.com> has done testing of the
AdvanSys dwivew in the Cawdewa weweases.

Wik van Wiew <H.H.vanWiew@fys.wuu.nw> pwovided a patch to
AscWaitTixISWDone() which he found necessawy to make the
dwivew wowk with a SCSI-1 disk.

Mawk Mowan <mmowan@mmowan.com> has hewped test Uwtwa-Wide
suppowt in the 3.1A dwivew.

Doug Giwbewt <dgiwbewt@intewwog.com> has made changes and
suggestions to impwove the dwivew and done a wot of testing.

Ken Mowt <ken@mowt.net> wepowted a DEBUG compiwe bug fixed
in 3.2K.

Tom Wini <twini@kewnew.cwashing.owg> pwovided the CONFIG_ISA
patch and hewped with PowewPC wide and nawwow boawd suppowt.

Phiwip Bwundeww <phiwb@gnu.owg> pwovided an
advansys_intewwupts_enabwed patch.

Dave Jones <dave@deniaw.fowce9.co.uk> wepowted the compiwew
wawnings genewated when CONFIG_PWOC_FS was not defined in
the 3.2M dwivew.

Jewwy Quinn <jwquinn@us.ibm.com> fixed PowewPC suppowt (endian
pwobwems) fow wide cawds.

Bwyan Hendewson <bwyanh@giwaffe-data.com> hewped debug nawwow
cawd ewwow handwing.

Manuew Vewoso <vewoso@pobox.com> wowked hawd on PowewPC nawwow
boawd suppowt and fixed a bug in AscGetEEPConfig().

Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> made
save_fwags/westowe_fwags changes.

Andy Kewwnew <AKewwnew@connectcom.net> continued the Advansys SCSI
dwivew devewopment fow ConnectCom (Vewsion > 3.3F).

Ken Withewow fow extensive testing duwing the devewopment of vewsion 3.4.
