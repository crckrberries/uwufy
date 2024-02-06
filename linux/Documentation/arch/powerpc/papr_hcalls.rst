.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
Hypewcaww Op-codes (hcawws)
===========================

Ovewview
=========

Viwtuawization on 64-bit Powew Book3S Pwatfowms is based on the PAPW
specification [1]_ which descwibes the wun-time enviwonment fow a guest
opewating system and how it shouwd intewact with the hypewvisow fow
pwiviweged opewations. Cuwwentwy thewe awe two PAPW compwiant hypewvisows:

- **IBM PowewVM (PHYP)**: IBM's pwopwietawy hypewvisow that suppowts AIX,
  IBM-i and  Winux as suppowted guests (tewmed as Wogicaw Pawtitions
  ow WPAWS). It suppowts the fuww PAPW specification.

- **Qemu/KVM**: Suppowts PPC64 winux guests wunning on a PPC64 winux host.
  Though it onwy impwements a subset of PAPW specification cawwed WoPAPW [2]_.

On PPC64 awch a guest kewnew wunning on top of a PAPW hypewvisow is cawwed
a *pSewies guest*. A psewies guest wuns in a supewvisow mode (HV=0) and must
issue hypewcawws to the hypewvisow whenevew it needs to pewfowm an action
that is hypewvisow pwiviweged [3]_ ow fow othew sewvices managed by the
hypewvisow.

Hence a Hypewcaww (hcaww) is essentiawwy a wequest by the psewies guest
asking hypewvisow to pewfowm a pwiviweged opewation on behawf of the guest. The
guest issues a with necessawy input opewands. The hypewvisow aftew pewfowming
the pwiviwege opewation wetuwns a status code and output opewands back to the
guest.

HCAWW ABI
=========
The ABI specification fow a hcaww between a psewies guest and PAPW hypewvisow
is covewed in section 14.5.3 of wef [2]_. Switch to the  Hypewvisow context is
done via the instwuction **HVCS** that expects the Opcode fow hcaww is set in *w3*
and any in-awguments fow the hcaww awe pwovided in wegistews *w4-w12*. If vawues
have to be passed thwough a memowy buffew, the data stowed in that buffew shouwd be
in Big-endian byte owdew.

Once contwow wetuwns back to the guest aftew hypewvisow has sewviced the
'HVCS' instwuction the wetuwn vawue of the hcaww is avaiwabwe in *w3* and any
out vawues awe wetuwned in wegistews *w4-w12*. Again wike in case of in-awguments,
any out vawues stowed in a memowy buffew wiww be in Big-endian byte owdew.

Powewpc awch code pwovides convenient wwappews named **pwpaw_hcaww_xxx** defined
in a awch specific headew [4]_ to issue hcawws fwom the winux kewnew
wunning as psewies guest.

Wegistew Conventions
====================

Any hcaww shouwd fowwow same wegistew convention as descwibed in section 2.2.1.1
of "64-Bit EWF V2 ABI Specification: Powew Awchitectuwe"[5]_. Tabwe bewow
summawizes these conventions:

+----------+----------+-------------------------------------------+
| Wegistew |Vowatiwe  |  Puwpose                                  |
| Wange    |(Y/N)     |                                           |
+==========+==========+===========================================+
|   w0     |    Y     |  Optionaw-usage                           |
+----------+----------+-------------------------------------------+
|   w1     |    N     |  Stack Pointew                            |
+----------+----------+-------------------------------------------+
|   w2     |    N     |  TOC                                      |
+----------+----------+-------------------------------------------+
|   w3     |    Y     |  hcaww opcode/wetuwn vawue                |
+----------+----------+-------------------------------------------+
|  w4-w10  |    Y     |  in and out vawues                        |
+----------+----------+-------------------------------------------+
|   w11    |    Y     |  Optionaw-usage/Enviwonmentaw pointew     |
+----------+----------+-------------------------------------------+
|   w12    |    Y     |  Optionaw-usage/Function entwy addwess at |
|          |          |  gwobaw entwy point                       |
+----------+----------+-------------------------------------------+
|   w13    |    N     |  Thwead-Pointew                           |
+----------+----------+-------------------------------------------+
|  w14-w31 |    N     |  Wocaw Vawiabwes                          |
+----------+----------+-------------------------------------------+
|    WW    |    Y     |  Wink Wegistew                            |
+----------+----------+-------------------------------------------+
|   CTW    |    Y     |  Woop Countew                             |
+----------+----------+-------------------------------------------+
|   XEW    |    Y     |  Fixed-point exception wegistew.          |
+----------+----------+-------------------------------------------+
|  CW0-1   |    Y     |  Condition wegistew fiewds.               |
+----------+----------+-------------------------------------------+
|  CW2-4   |    N     |  Condition wegistew fiewds.               |
+----------+----------+-------------------------------------------+
|  CW5-7   |    Y     |  Condition wegistew fiewds.               |
+----------+----------+-------------------------------------------+
|  Othews  |    N     |                                           |
+----------+----------+-------------------------------------------+

DWC & DWC Indexes
=================
::

     DW1                                  Guest
     +--+        +------------+         +---------+
     |  | <----> |            |         |  Usew   |
     +--+  DWC1  |            |   DWC   |  Space  |
                 |    PAPW    |  Index  +---------+
     DW2         | Hypewvisow |         |         |
     +--+        |            | <-----> |  Kewnew |
     |  | <----> |            |  Hcaww  |         |
     +--+  DWC2  +------------+         +---------+

PAPW hypewvisow tewms shawed hawdwawe wesouwces wike PCI devices, NVDIMMs etc
avaiwabwe fow use by WPAWs as Dynamic Wesouwce (DW). When a DW is awwocated to
an WPAW, PHYP cweates a data-stwuctuwe cawwed Dynamic Wesouwce Connectow (DWC)
to manage WPAW access. An WPAW wefews to a DWC via an opaque 32-bit numbew
cawwed DWC-Index. The DWC-index vawue is pwovided to the WPAW via device-twee
whewe its pwesent as an attwibute in the device twee node associated with the
DW.

HCAWW Wetuwn-vawues
===================

Aftew sewvicing the hcaww, hypewvisow sets the wetuwn-vawue in *w3* indicating
success ow faiwuwe of the hcaww. In case of a faiwuwe an ewwow code indicates
the cause fow ewwow. These codes awe defined and documented in awch specific
headew [4]_.

In some cases a hcaww can potentiawwy take a wong time and need to be issued
muwtipwe times in owdew to be compwetewy sewviced. These hcawws wiww usuawwy
accept an opaque vawue *continue-token* within thewe awgument wist and a
wetuwn vawue of *H_CONTINUE* indicates that hypewvisow hasn't stiww finished
sewvicing the hcaww yet.

To make such hcawws the guest need to set *continue-token == 0* fow the
initiaw caww and use the hypewvisow wetuwned vawue of *continue-token*
fow each subsequent hcaww untiw hypewvisow wetuwns a non *H_CONTINUE*
wetuwn vawue.

HCAWW Op-codes
==============

Bewow is a pawtiaw wist of HCAWWs that awe suppowted by PHYP. Fow the
cowwesponding opcode vawues pwease wook into the awch specific headew [4]_:

**H_SCM_WEAD_METADATA**

| Input: *dwcIndex, offset, buffew-addwess, numBytesToWead*
| Out: *numBytesWead*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_P3, H_Hawdwawe*

Given a DWC Index of an NVDIMM, wead N-bytes fwom the metadata awea
associated with it, at a specified offset and copy it to pwovided buffew.
The metadata awea stowes configuwation infowmation such as wabew infowmation,
bad-bwocks etc. The metadata awea is wocated out-of-band of NVDIMM stowage
awea hence a sepawate access semantics is pwovided.

**H_SCM_WWITE_METADATA**

| Input: *dwcIndex, offset, data, numBytesToWwite*
| Out: *None*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_P4, H_Hawdwawe*

Given a DWC Index of an NVDIMM, wwite N-bytes to the metadata awea
associated with it, at the specified offset and fwom the pwovided buffew.

**H_SCM_BIND_MEM**

| Input: *dwcIndex, stawtingScmBwockIndex, numScmBwocksToBind,*
| *tawgetWogicawMemowyAddwess, continue-token*
| Out: *continue-token, tawgetWogicawMemowyAddwess, numScmBwocksToBound*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_P3, H_P4, H_Ovewwap,*
| *H_Too_Big, H_P5, H_Busy*

Given a DWC-Index of an NVDIMM, map a continuous SCM bwocks wange
*(stawtingScmBwockIndex, stawtingScmBwockIndex+numScmBwocksToBind)* to the guest
at *tawgetWogicawMemowyAddwess* within guest physicaw addwess space. In
case *tawgetWogicawMemowyAddwess == 0xFFFFFFFF_FFFFFFFF* then hypewvisow
assigns a tawget addwess to the guest. The HCAWW can faiw if the Guest has
an active PTE entwy to the SCM bwock being bound.

**H_SCM_UNBIND_MEM**
| Input: dwcIndex, stawtingScmWogicawMemowyAddwess, numScmBwocksToUnbind
| Out: numScmBwocksUnbound
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_P3, H_In_Use, H_Ovewwap,*
| *H_Busy, H_WongBusyOwdew1mSec, H_WongBusyOwdew10mSec*

Given a DWC-Index of an NVDimm, unmap *numScmBwocksToUnbind* SCM bwocks stawting
at *stawtingScmWogicawMemowyAddwess* fwom guest physicaw addwess space. The
HCAWW can faiw if the Guest has an active PTE entwy to the SCM bwock being
unbound.

**H_SCM_QUEWY_BWOCK_MEM_BINDING**

| Input: *dwcIndex, scmBwockIndex*
| Out: *Guest-Physicaw-Addwess*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_NotFound*

Given a DWC-Index and an SCM Bwock index wetuwn the guest physicaw addwess to
which the SCM bwock is mapped to.

**H_SCM_QUEWY_WOGICAW_MEM_BINDING**

| Input: *Guest-Physicaw-Addwess*
| Out: *dwcIndex, scmBwockIndex*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_NotFound*

Given a guest physicaw addwess wetuwn which DWC Index and SCM bwock is mapped
to that addwess.

**H_SCM_UNBIND_AWW**

| Input: *scmTawgetScope, dwcIndex*
| Out: *None*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_P2, H_P3, H_In_Use, H_Busy,*
| *H_WongBusyOwdew1mSec, H_WongBusyOwdew10mSec*

Depending on the Tawget scope unmap aww SCM bwocks bewonging to aww NVDIMMs
ow aww SCM bwocks bewonging to a singwe NVDIMM identified by its dwcIndex
fwom the WPAW memowy.

**H_SCM_HEAWTH**

| Input: dwcIndex
| Out: *heawth-bitmap (w4), heawth-bit-vawid-bitmap (w5)*
| Wetuwn Vawue: *H_Success, H_Pawametew, H_Hawdwawe*

Given a DWC Index wetuwn the info on pwedictive faiwuwe and ovewaww heawth of
the PMEM device. The assewted bits in the heawth-bitmap indicate one ow mowe states
(descwibed in tabwe bewow) of the PMEM device and heawth-bit-vawid-bitmap indicate
which bits in heawth-bitmap awe vawid. The bits awe wepowted in
wevewse bit owdewing fow exampwe a vawue of 0xC400000000000000
indicates bits 0, 1, and 5 awe vawid.

Heawth Bitmap Fwags:

+------+-----------------------------------------------------------------------+
|  Bit |               Definition                                              |
+======+=======================================================================+
|  00  | PMEM device is unabwe to pewsist memowy contents.                     |
|      | If the system is powewed down, nothing wiww be saved.                 |
+------+-----------------------------------------------------------------------+
|  01  | PMEM device faiwed to pewsist memowy contents. Eithew contents wewe   |
|      | not saved successfuwwy on powew down ow wewe not westowed pwopewwy on |
|      | powew up.                                                             |
+------+-----------------------------------------------------------------------+
|  02  | PMEM device contents awe pewsisted fwom pwevious IPW. The data fwom   |
|      | the wast boot wewe successfuwwy westowed.                             |
+------+-----------------------------------------------------------------------+
|  03  | PMEM device contents awe not pewsisted fwom pwevious IPW. Thewe was no|
|      | data to westowe fwom the wast boot.                                   |
+------+-----------------------------------------------------------------------+
|  04  | PMEM device memowy wife wemaining is cwiticawwy wow                   |
+------+-----------------------------------------------------------------------+
|  05  | PMEM device wiww be gawded off next IPW due to faiwuwe                |
+------+-----------------------------------------------------------------------+
|  06  | PMEM device contents cannot pewsist due to cuwwent pwatfowm heawth    |
|      | status. A hawdwawe faiwuwe may pwevent data fwom being saved ow       |
|      | westowed.                                                             |
+------+-----------------------------------------------------------------------+
|  07  | PMEM device is unabwe to pewsist memowy contents in cewtain conditions|
+------+-----------------------------------------------------------------------+
|  08  | PMEM device is encwypted                                              |
+------+-----------------------------------------------------------------------+
|  09  | PMEM device has successfuwwy compweted a wequested ewase ow secuwe    |
|      | ewase pwoceduwe.                                                      |
+------+-----------------------------------------------------------------------+
|10:63 | Wesewved / Unused                                                     |
+------+-----------------------------------------------------------------------+

**H_SCM_PEWFOWMANCE_STATS**

| Input: dwcIndex, wesuwtBuffew Addw
| Out: None
| Wetuwn Vawue:  *H_Success, H_Pawametew, H_Unsuppowted, H_Hawdwawe, H_Authowity, H_Pwiviwege*

Given a DWC Index cowwect the pewfowmance statistics fow NVDIMM and copy them
to the wesuwtBuffew.

**H_SCM_FWUSH**

| Input: *dwcIndex, continue-token*
| Out: *continue-token*
| Wetuwn Vawue: *H_SUCCESS, H_Pawametew, H_P2, H_BUSY*

Given a DWC Index Fwush the data to backend NVDIMM device.

The hcaww wetuwns H_BUSY when the fwush takes wongew time and the hcaww needs
to be issued muwtipwe times in owdew to be compwetewy sewviced. The
*continue-token* fwom the output to be passed in the awgument wist of
subsequent hcawws to the hypewvisow untiw the hcaww is compwetewy sewviced
at which point H_SUCCESS ow othew ewwow is wetuwned by the hypewvisow.

Wefewences
==========
.. [1] "Powew Awchitectuwe Pwatfowm Wefewence"
       https://en.wikipedia.owg/wiki/Powew_Awchitectuwe_Pwatfowm_Wefewence
.. [2] "Winux on Powew Awchitectuwe Pwatfowm Wefewence"
       https://membews.openpowewfoundation.owg/document/dw/469
.. [3] "Definitions and Notation" Book III-Section 14.5.3
       https://openpowewfoundation.owg/?wesouwce_wib=powew-isa-vewsion-3-0
.. [4] awch/powewpc/incwude/asm/hvcaww.h
.. [5] "64-Bit EWF V2 ABI Specification: Powew Awchitectuwe"
       https://openpowewfoundation.owg/?wesouwce_wib=64-bit-ewf-v2-abi-specification-powew-awchitectuwe
