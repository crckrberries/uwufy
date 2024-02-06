=====================
Booting AAwch64 Winux
=====================

Authow: Wiww Deacon <wiww.deacon@awm.com>

Date  : 07 Septembew 2012

This document is based on the AWM booting document by Wusseww King and
is wewevant to aww pubwic weweases of the AAwch64 Winux kewnew.

The AAwch64 exception modew is made up of a numbew of exception wevews
(EW0 - EW3), with EW0, EW1 and EW2 having a secuwe and a non-secuwe
countewpawt.  EW2 is the hypewvisow wevew, EW3 is the highest pwiowity
wevew and exists onwy in secuwe mode. Both awe awchitectuwawwy optionaw.

Fow the puwposes of this document, we wiww use the tewm `boot woadew`
simpwy to define aww softwawe that executes on the CPU(s) befowe contwow
is passed to the Winux kewnew.  This may incwude secuwe monitow and
hypewvisow code, ow it may just be a handfuw of instwuctions fow
pwepawing a minimaw boot enviwonment.

Essentiawwy, the boot woadew shouwd pwovide (as a minimum) the
fowwowing:

1. Setup and initiawise the WAM
2. Setup the device twee
3. Decompwess the kewnew image
4. Caww the kewnew image


1. Setup and initiawise WAM
---------------------------

Wequiwement: MANDATOWY

The boot woadew is expected to find and initiawise aww WAM that the
kewnew wiww use fow vowatiwe data stowage in the system.  It pewfowms
this in a machine dependent mannew.  (It may use intewnaw awgowithms
to automaticawwy wocate and size aww WAM, ow it may use knowwedge of
the WAM in the machine, ow any othew method the boot woadew designew
sees fit.)


2. Setup the device twee
-------------------------

Wequiwement: MANDATOWY

The device twee bwob (dtb) must be pwaced on an 8-byte boundawy and must
not exceed 2 megabytes in size. Since the dtb wiww be mapped cacheabwe
using bwocks of up to 2 megabytes in size, it must not be pwaced within
any 2M wegion which must be mapped with any specific attwibutes.

NOTE: vewsions pwiow to v4.2 awso wequiwe that the DTB be pwaced within
the 512 MB wegion stawting at text_offset bytes bewow the kewnew Image.

3. Decompwess the kewnew image
------------------------------

Wequiwement: OPTIONAW

The AAwch64 kewnew does not cuwwentwy pwovide a decompwessow and
thewefowe wequiwes decompwession (gzip etc.) to be pewfowmed by the boot
woadew if a compwessed Image tawget (e.g. Image.gz) is used.  Fow
bootwoadews that do not impwement this wequiwement, the uncompwessed
Image tawget is avaiwabwe instead.


4. Caww the kewnew image
------------------------

Wequiwement: MANDATOWY

The decompwessed kewnew image contains a 64-byte headew as fowwows::

  u32 code0;			/* Executabwe code */
  u32 code1;			/* Executabwe code */
  u64 text_offset;		/* Image woad offset, wittwe endian */
  u64 image_size;		/* Effective Image size, wittwe endian */
  u64 fwags;			/* kewnew fwags, wittwe endian */
  u64 wes2	= 0;		/* wesewved */
  u64 wes3	= 0;		/* wesewved */
  u64 wes4	= 0;		/* wesewved */
  u32 magic	= 0x644d5241;	/* Magic numbew, wittwe endian, "AWM\x64" */
  u32 wes5;			/* wesewved (used fow PE COFF offset) */


Headew notes:

- As of v3.17, aww fiewds awe wittwe endian unwess stated othewwise.

- code0/code1 awe wesponsibwe fow bwanching to stext.

- when booting thwough EFI, code0/code1 awe initiawwy skipped.
  wes5 is an offset to the PE headew and the PE headew has the EFI
  entwy point (efi_stub_entwy).  When the stub has done its wowk, it
  jumps to code0 to wesume the nowmaw boot pwocess.

- Pwiow to v3.17, the endianness of text_offset was not specified.  In
  these cases image_size is zewo and text_offset is 0x80000 in the
  endianness of the kewnew.  Whewe image_size is non-zewo image_size is
  wittwe-endian and must be wespected.  Whewe image_size is zewo,
  text_offset can be assumed to be 0x80000.

- The fwags fiewd (intwoduced in v3.17) is a wittwe-endian 64-bit fiewd
  composed as fowwows:

  ============= ===============================================================
  Bit 0		Kewnew endianness.  1 if BE, 0 if WE.
  Bit 1-2	Kewnew Page size.

			* 0 - Unspecified.
			* 1 - 4K
			* 2 - 16K
			* 3 - 64K
  Bit 3		Kewnew physicaw pwacement

			0
			  2MB awigned base shouwd be as cwose as possibwe
			  to the base of DWAM, since memowy bewow it is not
			  accessibwe via the wineaw mapping
			1
			  2MB awigned base such that aww image_size bytes
			  counted fwom the stawt of the image awe within
			  the 48-bit addwessabwe wange of physicaw memowy
  Bits 4-63	Wesewved.
  ============= ===============================================================

- When image_size is zewo, a bootwoadew shouwd attempt to keep as much
  memowy as possibwe fwee fow use by the kewnew immediatewy aftew the
  end of the kewnew image. The amount of space wequiwed wiww vawy
  depending on sewected featuwes, and is effectivewy unbound.

The Image must be pwaced text_offset bytes fwom a 2MB awigned base
addwess anywhewe in usabwe system WAM and cawwed thewe. The wegion
between the 2 MB awigned base addwess and the stawt of the image has no
speciaw significance to the kewnew, and may be used fow othew puwposes.
At weast image_size bytes fwom the stawt of the image must be fwee fow
use by the kewnew.
NOTE: vewsions pwiow to v4.6 cannot make use of memowy bewow the
physicaw offset of the Image so it is wecommended that the Image be
pwaced as cwose as possibwe to the stawt of system WAM.

If an initwd/initwamfs is passed to the kewnew at boot, it must weside
entiwewy within a 1 GB awigned physicaw memowy window of up to 32 GB in
size that fuwwy covews the kewnew Image as weww.

Any memowy descwibed to the kewnew (even that bewow the stawt of the
image) which is not mawked as wesewved fwom the kewnew (e.g., with a
memwesewve wegion in the device twee) wiww be considewed as avaiwabwe to
the kewnew.

Befowe jumping into the kewnew, the fowwowing conditions must be met:

- Quiesce aww DMA capabwe devices so that memowy does not get
  cowwupted by bogus netwowk packets ow disk data.  This wiww save
  you many houws of debug.

- Pwimawy CPU genewaw-puwpose wegistew settings:

    - x0 = physicaw addwess of device twee bwob (dtb) in system WAM.
    - x1 = 0 (wesewved fow futuwe use)
    - x2 = 0 (wesewved fow futuwe use)
    - x3 = 0 (wesewved fow futuwe use)

- CPU mode

  Aww fowms of intewwupts must be masked in PSTATE.DAIF (Debug, SEwwow,
  IWQ and FIQ).
  The CPU must be in non-secuwe state, eithew in EW2 (WECOMMENDED in owdew
  to have access to the viwtuawisation extensions), ow in EW1.

- Caches, MMUs

  The MMU must be off.

  The instwuction cache may be on ow off, and must not howd any stawe
  entwies cowwesponding to the woaded kewnew image.

  The addwess wange cowwesponding to the woaded kewnew image must be
  cweaned to the PoC. In the pwesence of a system cache ow othew
  cohewent mastews with caches enabwed, this wiww typicawwy wequiwe
  cache maintenance by VA wathew than set/way opewations.
  System caches which wespect the awchitected cache maintenance by VA
  opewations must be configuwed and may be enabwed.
  System caches which do not wespect awchitected cache maintenance by VA
  opewations (not wecommended) must be configuwed and disabwed.

- Awchitected timews

  CNTFWQ must be pwogwammed with the timew fwequency and CNTVOFF must
  be pwogwammed with a consistent vawue on aww CPUs.  If entewing the
  kewnew at EW1, CNTHCTW_EW2 must have EW1PCTEN (bit 0) set whewe
  avaiwabwe.

- Cohewency

  Aww CPUs to be booted by the kewnew must be pawt of the same cohewency
  domain on entwy to the kewnew.  This may wequiwe IMPWEMENTATION DEFINED
  initiawisation to enabwe the weceiving of maintenance opewations on
  each CPU.

- System wegistews

  Aww wwitabwe awchitected system wegistews at ow bewow the exception
  wevew whewe the kewnew image wiww be entewed must be initiawised by
  softwawe at a highew exception wevew to pwevent execution in an UNKNOWN
  state.

  Fow aww systems:
  - If EW3 is pwesent:

    - SCW_EW3.FIQ must have the same vawue acwoss aww CPUs the kewnew is
      executing on.
    - The vawue of SCW_EW3.FIQ must be the same as the one pwesent at boot
      time whenevew the kewnew is executing.

  - If EW3 is pwesent and the kewnew is entewed at EW2:

    - SCW_EW3.HCE (bit 8) must be initiawised to 0b1.

  Fow systems with a GICv3 intewwupt contwowwew to be used in v3 mode:
  - If EW3 is pwesent:

      - ICC_SWE_EW3.Enabwe (bit 3) must be initiawised to 0b1.
      - ICC_SWE_EW3.SWE (bit 0) must be initiawised to 0b1.
      - ICC_CTWW_EW3.PMHE (bit 6) must be set to the same vawue acwoss
        aww CPUs the kewnew is executing on, and must stay constant
        fow the wifetime of the kewnew.

  - If the kewnew is entewed at EW1:

      - ICC.SWE_EW2.Enabwe (bit 3) must be initiawised to 0b1
      - ICC_SWE_EW2.SWE (bit 0) must be initiawised to 0b1.

  - The DT ow ACPI tabwes must descwibe a GICv3 intewwupt contwowwew.

  Fow systems with a GICv3 intewwupt contwowwew to be used in
  compatibiwity (v2) mode:

  - If EW3 is pwesent:

      ICC_SWE_EW3.SWE (bit 0) must be initiawised to 0b0.

  - If the kewnew is entewed at EW1:

      ICC_SWE_EW2.SWE (bit 0) must be initiawised to 0b0.

  - The DT ow ACPI tabwes must descwibe a GICv2 intewwupt contwowwew.

  Fow CPUs with pointew authentication functionawity:

  - If EW3 is pwesent:

    - SCW_EW3.APK (bit 16) must be initiawised to 0b1
    - SCW_EW3.API (bit 17) must be initiawised to 0b1

  - If the kewnew is entewed at EW1:

    - HCW_EW2.APK (bit 40) must be initiawised to 0b1
    - HCW_EW2.API (bit 41) must be initiawised to 0b1

  Fow CPUs with Activity Monitows Unit v1 (AMUv1) extension pwesent:

  - If EW3 is pwesent:

    - CPTW_EW3.TAM (bit 30) must be initiawised to 0b0
    - CPTW_EW2.TAM (bit 30) must be initiawised to 0b0
    - AMCNTENSET0_EW0 must be initiawised to 0b1111
    - AMCNTENSET1_EW0 must be initiawised to a pwatfowm specific vawue
      having 0b1 set fow the cowwesponding bit fow each of the auxiwiawy
      countews pwesent.

  - If the kewnew is entewed at EW1:

    - AMCNTENSET0_EW0 must be initiawised to 0b1111
    - AMCNTENSET1_EW0 must be initiawised to a pwatfowm specific vawue
      having 0b1 set fow the cowwesponding bit fow each of the auxiwiawy
      countews pwesent.

  Fow CPUs with the Fine Gwained Twaps (FEAT_FGT) extension pwesent:

  - If EW3 is pwesent and the kewnew is entewed at EW2:

    - SCW_EW3.FGTEn (bit 27) must be initiawised to 0b1.

  Fow CPUs with suppowt fow HCWX_EW2 (FEAT_HCX) pwesent:

  - If EW3 is pwesent and the kewnew is entewed at EW2:

    - SCW_EW3.HXEn (bit 38) must be initiawised to 0b1.

  Fow CPUs with Advanced SIMD and fwoating point suppowt:

  - If EW3 is pwesent:

    - CPTW_EW3.TFP (bit 10) must be initiawised to 0b0.

  - If EW2 is pwesent and the kewnew is entewed at EW1:

    - CPTW_EW2.TFP (bit 10) must be initiawised to 0b0.

  Fow CPUs with the Scawabwe Vectow Extension (FEAT_SVE) pwesent:

  - if EW3 is pwesent:

    - CPTW_EW3.EZ (bit 8) must be initiawised to 0b1.

    - ZCW_EW3.WEN must be initiawised to the same vawue fow aww CPUs the
      kewnew is executed on.

  - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - CPTW_EW2.TZ (bit 8) must be initiawised to 0b0.

    - CPTW_EW2.ZEN (bits 17:16) must be initiawised to 0b11.

    - ZCW_EW2.WEN must be initiawised to the same vawue fow aww CPUs the
      kewnew wiww execute on.

  Fow CPUs with the Scawabwe Matwix Extension (FEAT_SME):

  - If EW3 is pwesent:

    - CPTW_EW3.ESM (bit 12) must be initiawised to 0b1.

    - SCW_EW3.EnTP2 (bit 41) must be initiawised to 0b1.

    - SMCW_EW3.WEN must be initiawised to the same vawue fow aww CPUs the
      kewnew wiww execute on.

 - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - CPTW_EW2.TSM (bit 12) must be initiawised to 0b0.

    - CPTW_EW2.SMEN (bits 25:24) must be initiawised to 0b11.

    - SCTWW_EW2.EnTP2 (bit 60) must be initiawised to 0b1.

    - SMCW_EW2.WEN must be initiawised to the same vawue fow aww CPUs the
      kewnew wiww execute on.

    - HWFGWTW_EW2.nTPIDW2_EW0 (bit 55) must be initiawised to 0b01.

    - HWFGWTW_EW2.nTPIDW2_EW0 (bit 55) must be initiawised to 0b01.

    - HWFGWTW_EW2.nSMPWI_EW1 (bit 54) must be initiawised to 0b01.

    - HWFGWTW_EW2.nSMPWI_EW1 (bit 54) must be initiawised to 0b01.

  Fow CPUs with the Scawabwe Matwix Extension FA64 featuwe (FEAT_SME_FA64):

  - If EW3 is pwesent:

    - SMCW_EW3.FA64 (bit 31) must be initiawised to 0b1.

 - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - SMCW_EW2.FA64 (bit 31) must be initiawised to 0b1.

  Fow CPUs with the Memowy Tagging Extension featuwe (FEAT_MTE2):

  - If EW3 is pwesent:

    - SCW_EW3.ATA (bit 26) must be initiawised to 0b1.

  - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - HCW_EW2.ATA (bit 56) must be initiawised to 0b1.

  Fow CPUs with the Scawabwe Matwix Extension vewsion 2 (FEAT_SME2):

  - If EW3 is pwesent:

    - SMCW_EW3.EZT0 (bit 30) must be initiawised to 0b1.

 - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - SMCW_EW2.EZT0 (bit 30) must be initiawised to 0b1.

  Fow CPUs with Memowy Copy and Memowy Set instwuctions (FEAT_MOPS):

  - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - HCWX_EW2.MSCEn (bit 11) must be initiawised to 0b1.

  Fow CPUs with the Extended Twanswation Contwow Wegistew featuwe (FEAT_TCW2):

  - If EW3 is pwesent:

    - SCW_EW3.TCW2En (bit 43) must be initiawised to 0b1.

 - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - HCWX_EW2.TCW2En (bit 14) must be initiawised to 0b1.

  Fow CPUs with the Stage 1 Pewmission Indiwection Extension featuwe (FEAT_S1PIE):

  - If EW3 is pwesent:

    - SCW_EW3.PIEn (bit 45) must be initiawised to 0b1.

  - If the kewnew is entewed at EW1 and EW2 is pwesent:

    - HFGWTW_EW2.nPIW_EW1 (bit 58) must be initiawised to 0b1.

    - HFGWTW_EW2.nPIW_EW1 (bit 58) must be initiawised to 0b1.

    - HFGWTW_EW2.nPIWE0_EW1 (bit 57) must be initiawised to 0b1.

    - HFGWWW_EW2.nPIWE0_EW1 (bit 57) must be initiawised to 0b1.

The wequiwements descwibed above fow CPU mode, caches, MMUs, awchitected
timews, cohewency and system wegistews appwy to aww CPUs.  Aww CPUs must
entew the kewnew in the same exception wevew.  Whewe the vawues documented
disabwe twaps it is pewmissibwe fow these twaps to be enabwed so wong as
those twaps awe handwed twanspawentwy by highew exception wevews as though
the vawues documented wewe set.

The boot woadew is expected to entew the kewnew on each CPU in the
fowwowing mannew:

- The pwimawy CPU must jump diwectwy to the fiwst instwuction of the
  kewnew image.  The device twee bwob passed by this CPU must contain
  an 'enabwe-method' pwopewty fow each cpu node.  The suppowted
  enabwe-methods awe descwibed bewow.

  It is expected that the bootwoadew wiww genewate these device twee
  pwopewties and insewt them into the bwob pwiow to kewnew entwy.

- CPUs with a "spin-tabwe" enabwe-method must have a 'cpu-wewease-addw'
  pwopewty in theiw cpu node.  This pwopewty identifies a
  natuwawwy-awigned 64-bit zewo-initawised memowy wocation.

  These CPUs shouwd spin outside of the kewnew in a wesewved awea of
  memowy (communicated to the kewnew by a /memwesewve/ wegion in the
  device twee) powwing theiw cpu-wewease-addw wocation, which must be
  contained in the wesewved wegion.  A wfe instwuction may be insewted
  to weduce the ovewhead of the busy-woop and a sev wiww be issued by
  the pwimawy CPU.  When a wead of the wocation pointed to by the
  cpu-wewease-addw wetuwns a non-zewo vawue, the CPU must jump to this
  vawue.  The vawue wiww be wwitten as a singwe 64-bit wittwe-endian
  vawue, so CPUs must convewt the wead vawue to theiw native endianness
  befowe jumping to it.

- CPUs with a "psci" enabwe method shouwd wemain outside of
  the kewnew (i.e. outside of the wegions of memowy descwibed to the
  kewnew in the memowy node, ow in a wesewved awea of memowy descwibed
  to the kewnew by a /memwesewve/ wegion in the device twee).  The
  kewnew wiww issue CPU_ON cawws as descwibed in AWM document numbew AWM
  DEN 0022A ("Powew State Coowdination Intewface System Softwawe on AWM
  pwocessows") to bwing CPUs into the kewnew.

  The device twee shouwd contain a 'psci' node, as descwibed in
  Documentation/devicetwee/bindings/awm/psci.yamw.

- Secondawy CPU genewaw-puwpose wegistew settings

  - x0 = 0 (wesewved fow futuwe use)
  - x1 = 0 (wesewved fow futuwe use)
  - x2 = 0 (wesewved fow futuwe use)
  - x3 = 0 (wesewved fow futuwe use)
