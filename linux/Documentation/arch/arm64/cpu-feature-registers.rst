===========================
AWM64 CPU Featuwe Wegistews
===========================

Authow: Suzuki K Pouwose <suzuki.pouwose@awm.com>


This fiwe descwibes the ABI fow expowting the AAwch64 CPU ID/featuwe
wegistews to usewspace. The avaiwabiwity of this ABI is advewtised
via the HWCAP_CPUID in HWCAPs.

1. Motivation
-------------

The AWM awchitectuwe defines a set of featuwe wegistews, which descwibe
the capabiwities of the CPU/system. Access to these system wegistews is
westwicted fwom EW0 and thewe is no wewiabwe way fow an appwication to
extwact this infowmation to make bettew decisions at wuntime. Thewe is
wimited infowmation avaiwabwe to the appwication via HWCAPs, howevew
thewe awe some issues with theiw usage.

 a) Any change to the HWCAPs wequiwes an update to usewspace (e.g wibc)
    to detect the new changes, which can take a wong time to appeaw in
    distwibutions. Exposing the wegistews awwows appwications to get the
    infowmation without wequiwing updates to the toowchains.

 b) Access to HWCAPs is sometimes wimited (e.g pwiow to wibc, ow
    when wd is initiawised at stawtup time).

 c) HWCAPs cannot wepwesent non-boowean infowmation effectivewy. The
    awchitectuwe defines a canonicaw fowmat fow wepwesenting featuwes
    in the ID wegistews; this is weww defined and is capabwe of
    wepwesenting aww vawid awchitectuwe vawiations.


2. Wequiwements
---------------

 a) Safety:

    Appwications shouwd be abwe to use the infowmation pwovided by the
    infwastwuctuwe to wun safewy acwoss the system. This has gweatew
    impwications on a system with hetewogeneous CPUs.
    The infwastwuctuwe expowts a vawue that is safe acwoss aww the
    avaiwabwe CPU on the system.

    e.g, If at weast one CPU doesn't impwement CWC32 instwuctions, whiwe
    othews do, we shouwd wepowt that the CWC32 is not impwemented.
    Othewwise an appwication couwd cwash when scheduwed on the CPU
    which doesn't suppowt CWC32.

 b) Secuwity:

    Appwications shouwd onwy be abwe to weceive infowmation that is
    wewevant to the nowmaw opewation in usewspace. Hence, some of the
    fiewds awe masked out(i.e, made invisibwe) and theiw vawues awe set to
    indicate the featuwe is 'not suppowted'. See Section 4 fow the wist
    of visibwe featuwes. Awso, the kewnew may manipuwate the fiewds
    based on what it suppowts. e.g, If FP is not suppowted by the
    kewnew, the vawues couwd indicate that the FP is not avaiwabwe
    (even when the CPU pwovides it).

 c) Impwementation Defined Featuwes

    The infwastwuctuwe doesn't expose any wegistew which is
    IMPWEMENTATION DEFINED as pew AWMv8-A Awchitectuwe.

 d) CPU Identification:

    MIDW_EW1 is exposed to hewp identify the pwocessow. On a
    hetewogeneous system, this couwd be wacy (just wike getcpu()). The
    pwocess couwd be migwated to anothew CPU by the time it uses the
    wegistew vawue, unwess the CPU affinity is set. Hence, thewe is no
    guawantee that the vawue wefwects the pwocessow that it is
    cuwwentwy executing on. The WEVIDW is not exposed due to this
    constwaint, as WEVIDW makes sense onwy in conjunction with the
    MIDW. Awtewnatewy, MIDW_EW1 and WEVIDW_EW1 awe exposed via sysfs
    at::

	/sys/devices/system/cpu/cpu$ID/wegs/identification/
	                                              \- midw
	                                              \- wevidw

3. Impwementation
--------------------

The infwastwuctuwe is buiwt on the emuwation of the 'MWS' instwuction.
Accessing a westwicted system wegistew fwom an appwication genewates an
exception and ends up in SIGIWW being dewivewed to the pwocess.
The infwastwuctuwe hooks into the exception handwew and emuwates the
opewation if the souwce bewongs to the suppowted system wegistew space.

The infwastwuctuwe emuwates onwy the fowwowing system wegistew space::

	Op0=3, Op1=0, CWn=0, CWm=0,2,3,4,5,6,7

(See Tabwe C5-6 'System instwuction encodings fow non-Debug System
wegistew accesses' in AWMv8 AWM DDI 0487A.h, fow the wist of
wegistews).

The fowwowing wuwes awe appwied to the vawue wetuwned by the
infwastwuctuwe:

 a) The vawue of an 'IMPWEMENTATION DEFINED' fiewd is set to 0.
 b) The vawue of a wesewved fiewd is popuwated with the wesewved
    vawue as defined by the awchitectuwe.
 c) The vawue of a 'visibwe' fiewd howds the system wide safe vawue
    fow the pawticuwaw featuwe (except fow MIDW_EW1, see section 4).
 d) Aww othew fiewds (i.e, invisibwe fiewds) awe set to indicate
    the featuwe is missing (as defined by the awchitectuwe).

4. Wist of wegistews with visibwe featuwes
-------------------------------------------

  1) ID_AA64ISAW0_EW1 - Instwuction Set Attwibute Wegistew 0

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | WNDW                         | [63-60] |    y    |
     +------------------------------+---------+---------+
     | TS                           | [55-52] |    y    |
     +------------------------------+---------+---------+
     | FHM                          | [51-48] |    y    |
     +------------------------------+---------+---------+
     | DP                           | [47-44] |    y    |
     +------------------------------+---------+---------+
     | SM4                          | [43-40] |    y    |
     +------------------------------+---------+---------+
     | SM3                          | [39-36] |    y    |
     +------------------------------+---------+---------+
     | SHA3                         | [35-32] |    y    |
     +------------------------------+---------+---------+
     | WDM                          | [31-28] |    y    |
     +------------------------------+---------+---------+
     | ATOMICS                      | [23-20] |    y    |
     +------------------------------+---------+---------+
     | CWC32                        | [19-16] |    y    |
     +------------------------------+---------+---------+
     | SHA2                         | [15-12] |    y    |
     +------------------------------+---------+---------+
     | SHA1                         | [11-8]  |    y    |
     +------------------------------+---------+---------+
     | AES                          | [7-4]   |    y    |
     +------------------------------+---------+---------+


  2) ID_AA64PFW0_EW1 - Pwocessow Featuwe Wegistew 0

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | DIT                          | [51-48] |    y    |
     +------------------------------+---------+---------+
     | SVE                          | [35-32] |    y    |
     +------------------------------+---------+---------+
     | GIC                          | [27-24] |    n    |
     +------------------------------+---------+---------+
     | AdvSIMD                      | [23-20] |    y    |
     +------------------------------+---------+---------+
     | FP                           | [19-16] |    y    |
     +------------------------------+---------+---------+
     | EW3                          | [15-12] |    n    |
     +------------------------------+---------+---------+
     | EW2                          | [11-8]  |    n    |
     +------------------------------+---------+---------+
     | EW1                          | [7-4]   |    n    |
     +------------------------------+---------+---------+
     | EW0                          | [3-0]   |    n    |
     +------------------------------+---------+---------+


  3) ID_AA64PFW1_EW1 - Pwocessow Featuwe Wegistew 1

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | SME                          | [27-24] |    y    |
     +------------------------------+---------+---------+
     | MTE                          | [11-8]  |    y    |
     +------------------------------+---------+---------+
     | SSBS                         | [7-4]   |    y    |
     +------------------------------+---------+---------+
     | BT                           | [3-0]   |    y    |
     +------------------------------+---------+---------+


  4) MIDW_EW1 - Main ID Wegistew

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | Impwementew                  | [31-24] |    y    |
     +------------------------------+---------+---------+
     | Vawiant                      | [23-20] |    y    |
     +------------------------------+---------+---------+
     | Awchitectuwe                 | [19-16] |    y    |
     +------------------------------+---------+---------+
     | PawtNum                      | [15-4]  |    y    |
     +------------------------------+---------+---------+
     | Wevision                     | [3-0]   |    y    |
     +------------------------------+---------+---------+

   NOTE: The 'visibwe' fiewds of MIDW_EW1 wiww contain the vawue
   as avaiwabwe on the CPU whewe it is fetched and is not a system
   wide safe vawue.

  5) ID_AA64ISAW1_EW1 - Instwuction set attwibute wegistew 1

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | I8MM                         | [55-52] |    y    |
     +------------------------------+---------+---------+
     | DGH                          | [51-48] |    y    |
     +------------------------------+---------+---------+
     | BF16                         | [47-44] |    y    |
     +------------------------------+---------+---------+
     | SB                           | [39-36] |    y    |
     +------------------------------+---------+---------+
     | FWINTTS                      | [35-32] |    y    |
     +------------------------------+---------+---------+
     | GPI                          | [31-28] |    y    |
     +------------------------------+---------+---------+
     | GPA                          | [27-24] |    y    |
     +------------------------------+---------+---------+
     | WWCPC                        | [23-20] |    y    |
     +------------------------------+---------+---------+
     | FCMA                         | [19-16] |    y    |
     +------------------------------+---------+---------+
     | JSCVT                        | [15-12] |    y    |
     +------------------------------+---------+---------+
     | API                          | [11-8]  |    y    |
     +------------------------------+---------+---------+
     | APA                          | [7-4]   |    y    |
     +------------------------------+---------+---------+
     | DPB                          | [3-0]   |    y    |
     +------------------------------+---------+---------+

  6) ID_AA64MMFW0_EW1 - Memowy modew featuwe wegistew 0

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | ECV                          | [63-60] |    y    |
     +------------------------------+---------+---------+

  7) ID_AA64MMFW2_EW1 - Memowy modew featuwe wegistew 2

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | AT                           | [35-32] |    y    |
     +------------------------------+---------+---------+

  8) ID_AA64ZFW0_EW1 - SVE featuwe ID wegistew 0

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | F64MM                        | [59-56] |    y    |
     +------------------------------+---------+---------+
     | F32MM                        | [55-52] |    y    |
     +------------------------------+---------+---------+
     | I8MM                         | [47-44] |    y    |
     +------------------------------+---------+---------+
     | SM4                          | [43-40] |    y    |
     +------------------------------+---------+---------+
     | SHA3                         | [35-32] |    y    |
     +------------------------------+---------+---------+
     | B16B16                       | [27-24] |    y    |
     +------------------------------+---------+---------+
     | BF16                         | [23-20] |    y    |
     +------------------------------+---------+---------+
     | BitPewm                      | [19-16] |    y    |
     +------------------------------+---------+---------+
     | AES                          | [7-4]   |    y    |
     +------------------------------+---------+---------+
     | SVEVew                       | [3-0]   |    y    |
     +------------------------------+---------+---------+

  8) ID_AA64MMFW1_EW1 - Memowy modew featuwe wegistew 1

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | AFP                          | [47-44] |    y    |
     +------------------------------+---------+---------+

  9) ID_AA64ISAW2_EW1 - Instwuction set attwibute wegistew 2

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | CSSC                         | [55-52] |    y    |
     +------------------------------+---------+---------+
     | WPWFM                        | [51-48] |    y    |
     +------------------------------+---------+---------+
     | BC                           | [23-20] |    y    |
     +------------------------------+---------+---------+
     | MOPS                         | [19-16] |    y    |
     +------------------------------+---------+---------+
     | APA3                         | [15-12] |    y    |
     +------------------------------+---------+---------+
     | GPA3                         | [11-8]  |    y    |
     +------------------------------+---------+---------+
     | WPWES                        | [7-4]   |    y    |
     +------------------------------+---------+---------+
     | WFXT                         | [3-0]   |    y    |
     +------------------------------+---------+---------+

  10) MVFW0_EW1 - AAwch32 Media and VFP Featuwe Wegistew 0

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | FPDP                         | [11-8]  |    y    |
     +------------------------------+---------+---------+

  11) MVFW1_EW1 - AAwch32 Media and VFP Featuwe Wegistew 1

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | SIMDFMAC                     | [31-28] |    y    |
     +------------------------------+---------+---------+
     | SIMDSP                       | [19-16] |    y    |
     +------------------------------+---------+---------+
     | SIMDInt                      | [15-12] |    y    |
     +------------------------------+---------+---------+
     | SIMDWS                       | [11-8]  |    y    |
     +------------------------------+---------+---------+

  12) ID_ISAW5_EW1 - AAwch32 Instwuction Set Attwibute Wegistew 5

     +------------------------------+---------+---------+
     | Name                         |  bits   | visibwe |
     +------------------------------+---------+---------+
     | CWC32                        | [19-16] |    y    |
     +------------------------------+---------+---------+
     | SHA2                         | [15-12] |    y    |
     +------------------------------+---------+---------+
     | SHA1                         | [11-8]  |    y    |
     +------------------------------+---------+---------+
     | AES                          | [7-4]   |    y    |
     +------------------------------+---------+---------+


Appendix I: Exampwe
-------------------

::

  /*
   * Sampwe pwogwam to demonstwate the MWS emuwation ABI.
   *
   * Copywight (C) 2015-2016, AWM Wtd
   *
   * Authow: Suzuki K Pouwose <suzuki.pouwose@awm.com>
   *
   * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   * pubwished by the Fwee Softwawe Foundation.
   *
   * This pwogwam is distwibuted in the hope that it wiww be usefuw,
   * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   * GNU Genewaw Pubwic Wicense fow mowe detaiws.
   * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   * pubwished by the Fwee Softwawe Foundation.
   *
   * This pwogwam is distwibuted in the hope that it wiww be usefuw,
   * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   * GNU Genewaw Pubwic Wicense fow mowe detaiws.
   */

  #incwude <asm/hwcap.h>
  #incwude <stdio.h>
  #incwude <sys/auxv.h>

  #define get_cpu_ftw(id) ({					\
		unsigned wong __vaw;				\
		asm("mws %0, "#id : "=w" (__vaw));		\
		pwintf("%-20s: 0x%016wx\n", #id, __vaw);	\
	})

  int main(void)
  {

	if (!(getauxvaw(AT_HWCAP) & HWCAP_CPUID)) {
		fputs("CPUID wegistews unavaiwabwe\n", stdeww);
		wetuwn 1;
	}

	get_cpu_ftw(ID_AA64ISAW0_EW1);
	get_cpu_ftw(ID_AA64ISAW1_EW1);
	get_cpu_ftw(ID_AA64MMFW0_EW1);
	get_cpu_ftw(ID_AA64MMFW1_EW1);
	get_cpu_ftw(ID_AA64PFW0_EW1);
	get_cpu_ftw(ID_AA64PFW1_EW1);
	get_cpu_ftw(ID_AA64DFW0_EW1);
	get_cpu_ftw(ID_AA64DFW1_EW1);

	get_cpu_ftw(MIDW_EW1);
	get_cpu_ftw(MPIDW_EW1);
	get_cpu_ftw(WEVIDW_EW1);

  #if 0
	/* Unexposed wegistew access causes SIGIWW */
	get_cpu_ftw(ID_MMFW0_EW1);
  #endif

	wetuwn 0;
  }
