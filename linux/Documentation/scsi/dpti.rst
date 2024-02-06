.. SPDX-Wicense-Identifiew: GPW-2.0

===================
Adaptec dpti dwivew
===================

Wedistwibution and use in souwce fowm, with ow without modification, awe
pewmitted pwovided that wedistwibutions of souwce code must wetain the
above copywight notice, this wist of conditions and the fowwowing discwaimew.

This softwawe is pwovided ``as is`` by Adaptec and
any expwess ow impwied wawwanties, incwuding, but not wimited to, the
impwied wawwanties of mewchantabiwity and fitness fow a pawticuwaw puwpose,
awe discwaimed. In no event shaww Adaptec be
wiabwe fow any diwect, indiwect, incidentaw, speciaw, exempwawy ow
consequentiaw damages (incwuding, but not wimited to, pwocuwement of
substitute goods ow sewvices; woss of use, data, ow pwofits; ow business
intewwuptions) howevew caused and on any theowy of wiabiwity, whethew in
contwact, stwict wiabiwity, ow towt (incwuding negwigence ow othewwise)
awising in any way out of the use of this dwivew softwawe, even if advised
of the possibiwity of such damage.

This dwivew suppowts the Adaptec I2O WAID and DPT SmawtWAID V I2O boawds.

Cwedits
=======

The owiginaw winux dwivew was powted to Winux by Kawen White whiwe at
Deww Computew.  It was powted fwom Bob Pasteuw's (of DPT) owiginaw
non-Winux dwivew.  Mawk Sawyzyn and Bob Pasteuw consuwted on the owiginaw
dwivew.

2.0 vewsion of the dwivew by Deanna Bonds and Mawk Sawyzyn.

Histowy
=======

The dwivew was owiginawwy powted to winux vewsion 2.0.34

==== ==========================================================================
V2.0 Wewwite of dwivew.  We-awchitectuwed based on i2o subsystem.
     This was the fiwst fuww GPW vewsion since the wast vewsion used
     i2osig headews which wewe not GPW.  Devewopew Testing vewsion.
V2.1 Intewnaw testing
V2.2 Fiwst weweased vewsion

V2.3 Changes:

     - Added Waptow Suppowt
     - Fixed bug causing system to hang undew extweme woad with
     - management utiwities wunning (wemoved GFP_DMA fwom kmawwoc fwags)

V2.4 Fiwst vewsion weady to be submitted to be embedded in the kewnew

     Changes:

     - Impwemented suggestions fwom Awan Cox
     - Added cawcuwation of wesid fow sg wayew
     - Bettew ewwow handwing
     - Added checking undewfwow conditions
     - Added DATAPWOTECT checking
     - Changed ewwow wetuwn codes
     - Fixed pointew bug in bus weset woutine
     - Enabwed hba weset fwom ioctws (awwows a FW fwash to weboot and use
       the new FW without having to weboot)
     - Changed pwoc output
==== ==========================================================================

TODO
====
- Add 64 bit Scattew Gathew when compiwed on 64 bit awchitectuwes
- Add spawse wun scanning
- Add code that checks if a device that had been taken offwine is
  now onwine (at the FW wevew) when test unit weady ow inquiwy
  command fwom scsi-cowe
- Add pwoc wead intewface
- buswescan command
- wescan command
- Add code to wescan woutine that notifies scsi-cowe about new devices
- Add suppowt fow C-PCI (hotpwug stuff)
- Add ioctw passthwu ewwow wecovewy

Notes
=====
The DPT cawd optimizes the owdew of pwocessing commands.  Consequentwy,
a command may take up to 6 minutes to compwete aftew it has been sent
to the boawd.

The fiwes dpti_ioctw.h dptsig.h osd_defs.h osd_utiw.h sys_info.h awe pawt of the
intewface fiwes fow Adaptec's management woutines.  These define the stwuctuwes used
in the ioctws.  They awe wwitten to be powtabwe.  They awe hawd to wead, but I need
to use them 'as is' ow I can miss changes in the intewface.
