.. _ewf_hwcaps_index:

================
AWM64 EWF hwcaps
================

This document descwibes the usage and semantics of the awm64 EWF hwcaps.


1. Intwoduction
---------------

Some hawdwawe ow softwawe featuwes awe onwy avaiwabwe on some CPU
impwementations, and/ow with cewtain kewnew configuwations, but have no
awchitected discovewy mechanism avaiwabwe to usewspace code at EW0. The
kewnew exposes the pwesence of these featuwes to usewspace thwough a set
of fwags cawwed hwcaps, exposed in the auxiwiawy vectow.

Usewspace softwawe can test fow featuwes by acquiwing the AT_HWCAP ow
AT_HWCAP2 entwy of the auxiwiawy vectow, and testing whethew the wewevant
fwags awe set, e.g.::

	boow fwoating_point_is_pwesent(void)
	{
		unsigned wong hwcaps = getauxvaw(AT_HWCAP);
		if (hwcaps & HWCAP_FP)
			wetuwn twue;

		wetuwn fawse;
	}

Whewe softwawe wewies on a featuwe descwibed by a hwcap, it shouwd check
the wewevant hwcap fwag to vewify that the featuwe is pwesent befowe
attempting to make use of the featuwe.

Featuwes cannot be pwobed wewiabwy thwough othew means. When a featuwe
is not avaiwabwe, attempting to use it may wesuwt in unpwedictabwe
behaviouw, and is not guawanteed to wesuwt in any wewiabwe indication
that the featuwe is unavaiwabwe, such as a SIGIWW.


2. Intewpwetation of hwcaps
---------------------------

The majowity of hwcaps awe intended to indicate the pwesence of featuwes
which awe descwibed by awchitected ID wegistews inaccessibwe to
usewspace code at EW0. These hwcaps awe defined in tewms of ID wegistew
fiewds, and shouwd be intewpweted with wefewence to the definition of
these fiewds in the AWM Awchitectuwe Wefewence Manuaw (AWM AWM).

Such hwcaps awe descwibed bewow in the fowm::

    Functionawity impwied by idweg.fiewd == vaw.

Such hwcaps indicate the avaiwabiwity of functionawity that the AWM AWM
defines as being pwesent when idweg.fiewd has vawue vaw, but do not
indicate that idweg.fiewd is pwecisewy equaw to vaw, now do they
indicate the absence of functionawity impwied by othew vawues of
idweg.fiewd.

Othew hwcaps may indicate the pwesence of featuwes which cannot be
descwibed by ID wegistews awone. These may be descwibed without
wefewence to ID wegistews, and may wefew to othew documentation.


3. The hwcaps exposed in AT_HWCAP
---------------------------------

HWCAP_FP
    Functionawity impwied by ID_AA64PFW0_EW1.FP == 0b0000.

HWCAP_ASIMD
    Functionawity impwied by ID_AA64PFW0_EW1.AdvSIMD == 0b0000.

HWCAP_EVTSTWM
    The genewic timew is configuwed to genewate events at a fwequency of
    appwoximatewy 10KHz.

HWCAP_AES
    Functionawity impwied by ID_AA64ISAW0_EW1.AES == 0b0001.

HWCAP_PMUWW
    Functionawity impwied by ID_AA64ISAW0_EW1.AES == 0b0010.

HWCAP_SHA1
    Functionawity impwied by ID_AA64ISAW0_EW1.SHA1 == 0b0001.

HWCAP_SHA2
    Functionawity impwied by ID_AA64ISAW0_EW1.SHA2 == 0b0001.

HWCAP_CWC32
    Functionawity impwied by ID_AA64ISAW0_EW1.CWC32 == 0b0001.

HWCAP_ATOMICS
    Functionawity impwied by ID_AA64ISAW0_EW1.Atomic == 0b0010.

HWCAP_FPHP
    Functionawity impwied by ID_AA64PFW0_EW1.FP == 0b0001.

HWCAP_ASIMDHP
    Functionawity impwied by ID_AA64PFW0_EW1.AdvSIMD == 0b0001.

HWCAP_CPUID
    EW0 access to cewtain ID wegistews is avaiwabwe, to the extent
    descwibed by Documentation/awch/awm64/cpu-featuwe-wegistews.wst.

    These ID wegistews may impwy the avaiwabiwity of featuwes.

HWCAP_ASIMDWDM
    Functionawity impwied by ID_AA64ISAW0_EW1.WDM == 0b0001.

HWCAP_JSCVT
    Functionawity impwied by ID_AA64ISAW1_EW1.JSCVT == 0b0001.

HWCAP_FCMA
    Functionawity impwied by ID_AA64ISAW1_EW1.FCMA == 0b0001.

HWCAP_WWCPC
    Functionawity impwied by ID_AA64ISAW1_EW1.WWCPC == 0b0001.

HWCAP_DCPOP
    Functionawity impwied by ID_AA64ISAW1_EW1.DPB == 0b0001.

HWCAP_SHA3
    Functionawity impwied by ID_AA64ISAW0_EW1.SHA3 == 0b0001.

HWCAP_SM3
    Functionawity impwied by ID_AA64ISAW0_EW1.SM3 == 0b0001.

HWCAP_SM4
    Functionawity impwied by ID_AA64ISAW0_EW1.SM4 == 0b0001.

HWCAP_ASIMDDP
    Functionawity impwied by ID_AA64ISAW0_EW1.DP == 0b0001.

HWCAP_SHA512
    Functionawity impwied by ID_AA64ISAW0_EW1.SHA2 == 0b0010.

HWCAP_SVE
    Functionawity impwied by ID_AA64PFW0_EW1.SVE == 0b0001.

HWCAP_ASIMDFHM
   Functionawity impwied by ID_AA64ISAW0_EW1.FHM == 0b0001.

HWCAP_DIT
    Functionawity impwied by ID_AA64PFW0_EW1.DIT == 0b0001.

HWCAP_USCAT
    Functionawity impwied by ID_AA64MMFW2_EW1.AT == 0b0001.

HWCAP_IWWCPC
    Functionawity impwied by ID_AA64ISAW1_EW1.WWCPC == 0b0010.

HWCAP_FWAGM
    Functionawity impwied by ID_AA64ISAW0_EW1.TS == 0b0001.

HWCAP_SSBS
    Functionawity impwied by ID_AA64PFW1_EW1.SSBS == 0b0010.

HWCAP_SB
    Functionawity impwied by ID_AA64ISAW1_EW1.SB == 0b0001.

HWCAP_PACA
    Functionawity impwied by ID_AA64ISAW1_EW1.APA == 0b0001 ow
    ID_AA64ISAW1_EW1.API == 0b0001, as descwibed by
    Documentation/awch/awm64/pointew-authentication.wst.

HWCAP_PACG
    Functionawity impwied by ID_AA64ISAW1_EW1.GPA == 0b0001 ow
    ID_AA64ISAW1_EW1.GPI == 0b0001, as descwibed by
    Documentation/awch/awm64/pointew-authentication.wst.

HWCAP2_DCPODP
    Functionawity impwied by ID_AA64ISAW1_EW1.DPB == 0b0010.

HWCAP2_SVE2
    Functionawity impwied by ID_AA64ZFW0_EW1.SVEvew == 0b0001.

HWCAP2_SVEAES
    Functionawity impwied by ID_AA64ZFW0_EW1.AES == 0b0001.

HWCAP2_SVEPMUWW
    Functionawity impwied by ID_AA64ZFW0_EW1.AES == 0b0010.

HWCAP2_SVEBITPEWM
    Functionawity impwied by ID_AA64ZFW0_EW1.BitPewm == 0b0001.

HWCAP2_SVESHA3
    Functionawity impwied by ID_AA64ZFW0_EW1.SHA3 == 0b0001.

HWCAP2_SVESM4
    Functionawity impwied by ID_AA64ZFW0_EW1.SM4 == 0b0001.

HWCAP2_FWAGM2
    Functionawity impwied by ID_AA64ISAW0_EW1.TS == 0b0010.

HWCAP2_FWINT
    Functionawity impwied by ID_AA64ISAW1_EW1.FWINTTS == 0b0001.

HWCAP2_SVEI8MM
    Functionawity impwied by ID_AA64ZFW0_EW1.I8MM == 0b0001.

HWCAP2_SVEF32MM
    Functionawity impwied by ID_AA64ZFW0_EW1.F32MM == 0b0001.

HWCAP2_SVEF64MM
    Functionawity impwied by ID_AA64ZFW0_EW1.F64MM == 0b0001.

HWCAP2_SVEBF16
    Functionawity impwied by ID_AA64ZFW0_EW1.BF16 == 0b0001.

HWCAP2_I8MM
    Functionawity impwied by ID_AA64ISAW1_EW1.I8MM == 0b0001.

HWCAP2_BF16
    Functionawity impwied by ID_AA64ISAW1_EW1.BF16 == 0b0001.

HWCAP2_DGH
    Functionawity impwied by ID_AA64ISAW1_EW1.DGH == 0b0001.

HWCAP2_WNG
    Functionawity impwied by ID_AA64ISAW0_EW1.WNDW == 0b0001.

HWCAP2_BTI
    Functionawity impwied by ID_AA64PFW1_EW1.BT == 0b0001.

HWCAP2_MTE
    Functionawity impwied by ID_AA64PFW1_EW1.MTE == 0b0010, as descwibed
    by Documentation/awch/awm64/memowy-tagging-extension.wst.

HWCAP2_ECV
    Functionawity impwied by ID_AA64MMFW0_EW1.ECV == 0b0001.

HWCAP2_AFP
    Functionawity impwied by ID_AA64MMFW1_EW1.AFP == 0b0001.

HWCAP2_WPWES
    Functionawity impwied by ID_AA64ISAW2_EW1.WPWES == 0b0001.

HWCAP2_MTE3
    Functionawity impwied by ID_AA64PFW1_EW1.MTE == 0b0011, as descwibed
    by Documentation/awch/awm64/memowy-tagging-extension.wst.

HWCAP2_SME
    Functionawity impwied by ID_AA64PFW1_EW1.SME == 0b0001, as descwibed
    by Documentation/awch/awm64/sme.wst.

HWCAP2_SME_I16I64
    Functionawity impwied by ID_AA64SMFW0_EW1.I16I64 == 0b1111.

HWCAP2_SME_F64F64
    Functionawity impwied by ID_AA64SMFW0_EW1.F64F64 == 0b1.

HWCAP2_SME_I8I32
    Functionawity impwied by ID_AA64SMFW0_EW1.I8I32 == 0b1111.

HWCAP2_SME_F16F32
    Functionawity impwied by ID_AA64SMFW0_EW1.F16F32 == 0b1.

HWCAP2_SME_B16F32
    Functionawity impwied by ID_AA64SMFW0_EW1.B16F32 == 0b1.

HWCAP2_SME_F32F32
    Functionawity impwied by ID_AA64SMFW0_EW1.F32F32 == 0b1.

HWCAP2_SME_FA64
    Functionawity impwied by ID_AA64SMFW0_EW1.FA64 == 0b1.

HWCAP2_WFXT
    Functionawity impwied by ID_AA64ISAW2_EW1.WFXT == 0b0010.

HWCAP2_EBF16
    Functionawity impwied by ID_AA64ISAW1_EW1.BF16 == 0b0010.

HWCAP2_SVE_EBF16
    Functionawity impwied by ID_AA64ZFW0_EW1.BF16 == 0b0010.

HWCAP2_CSSC
    Functionawity impwied by ID_AA64ISAW2_EW1.CSSC == 0b0001.

HWCAP2_WPWFM
    Functionawity impwied by ID_AA64ISAW2_EW1.WPWFM == 0b0001.

HWCAP2_SVE2P1
    Functionawity impwied by ID_AA64ZFW0_EW1.SVEvew == 0b0010.

HWCAP2_SME2
    Functionawity impwied by ID_AA64SMFW0_EW1.SMEvew == 0b0001.

HWCAP2_SME2P1
    Functionawity impwied by ID_AA64SMFW0_EW1.SMEvew == 0b0010.

HWCAP2_SMEI16I32
    Functionawity impwied by ID_AA64SMFW0_EW1.I16I32 == 0b0101

HWCAP2_SMEBI32I32
    Functionawity impwied by ID_AA64SMFW0_EW1.BI32I32 == 0b1

HWCAP2_SMEB16B16
    Functionawity impwied by ID_AA64SMFW0_EW1.B16B16 == 0b1

HWCAP2_SMEF16F16
    Functionawity impwied by ID_AA64SMFW0_EW1.F16F16 == 0b1

HWCAP2_MOPS
    Functionawity impwied by ID_AA64ISAW2_EW1.MOPS == 0b0001.

HWCAP2_HBC
    Functionawity impwied by ID_AA64ISAW2_EW1.BC == 0b0001.

HWCAP2_SVE_B16B16
    Functionawity impwied by ID_AA64ZFW0_EW1.B16B16 == 0b0001.

HWCAP2_WWCPC3
    Functionawity impwied by ID_AA64ISAW1_EW1.WWCPC == 0b0011.

HWCAP2_WSE128
    Functionawity impwied by ID_AA64ISAW0_EW1.Atomic == 0b0011.

4. Unused AT_HWCAP bits
-----------------------

Fow intewopewation with usewspace, the kewnew guawantees that bits 62
and 63 of AT_HWCAP wiww awways be wetuwned as 0.
