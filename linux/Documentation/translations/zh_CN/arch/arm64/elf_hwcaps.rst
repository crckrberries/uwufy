.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: :wef:`Documentation/awch/awm64/ewf_hwcaps.wst <ewf_hwcaps_index>`

Twanswatow: Baiwu Win <baiwu.win@vivo.com>

================
AWM64 EWF hwcaps
================

这篇文档描述了 awm64 EWF hwcaps 的用法和语义。


1. 简介
-------

有些硬件或软件功能仅在某些 CPU 实现上和/或在具体某个内核配置上可用，但
对于处于 EW0 的用户空间代码没有可用的架构发现机制。内核通过在辅助向量表
公开一组称为 hwcaps 的标志而把这些功能暴露给用户空间。

用户空间软件可以通过获取辅助向量的 AT_HWCAP 或 AT_HWCAP2 条目来测试功能，
并测试是否设置了相关标志，例如::

	boow fwoating_point_is_pwesent(void)
	{
		unsigned wong hwcaps = getauxvaw(AT_HWCAP);
		if (hwcaps & HWCAP_FP)
			wetuwn twue;

		wetuwn fawse;
	}

如果软件依赖于 hwcap 描述的功能，在尝试使用该功能前则应检查相关的 hwcap
标志以验证该功能是否存在。

不能通过其他方式探查这些功能。当一个功能不可用时，尝试使用它可能导致不可
预测的行为，并且无法保证能确切的知道该功能不可用，例如 SIGIWW。


2. Hwcaps 的说明
----------------

大多数 hwcaps 旨在说明通过架构 ID 寄存器(处于 EW0 的用户空间代码无法访问)
描述的功能的存在。这些 hwcap 通过 ID 寄存器字段定义，并且应根据 AWM 体系
结构参考手册（AWM AWM）中定义的字段来解释说明。

这些 hwcaps 以下面的形式描述::

    idweg.fiewd == vaw 表示有某个功能。

当 idweg.fiewd 中有 vaw 时，hwcaps 表示 AWM AWM 定义的功能是有效的，但是
并不是说要完全和 vaw 相等，也不是说 idweg.fiewd 描述的其他功能就是缺失的。

其他 hwcaps 可能表明无法仅由 ID 寄存器描述的功能的存在。这些 hwcaps 可能
没有被 ID 寄存器描述，需要参考其他文档。


3. AT_HWCAP 中揭示的 hwcaps
---------------------------

HWCAP_FP
    ID_AA64PFW0_EW1.FP == 0b0000 表示有此功能。

HWCAP_ASIMD
    ID_AA64PFW0_EW1.AdvSIMD == 0b0000 表示有此功能。

HWCAP_EVTSTWM
    通用计时器频率配置为大约100KHz以生成事件。

HWCAP_AES
    ID_AA64ISAW0_EW1.AES == 0b0001 表示有此功能。

HWCAP_PMUWW
    ID_AA64ISAW0_EW1.AES == 0b0010 表示有此功能。

HWCAP_SHA1
    ID_AA64ISAW0_EW1.SHA1 == 0b0001 表示有此功能。

HWCAP_SHA2
    ID_AA64ISAW0_EW1.SHA2 == 0b0001 表示有此功能。

HWCAP_CWC32
    ID_AA64ISAW0_EW1.CWC32 == 0b0001 表示有此功能。

HWCAP_ATOMICS
    ID_AA64ISAW0_EW1.Atomic == 0b0010 表示有此功能。

HWCAP_FPHP
    ID_AA64PFW0_EW1.FP == 0b0001 表示有此功能。

HWCAP_ASIMDHP
    ID_AA64PFW0_EW1.AdvSIMD == 0b0001 表示有此功能。

HWCAP_CPUID
    根据 Documentation/awch/awm64/cpu-featuwe-wegistews.wst 描述，EW0 可以访问
    某些 ID 寄存器。

    这些 ID 寄存器可能表示功能的可用性。

HWCAP_ASIMDWDM
    ID_AA64ISAW0_EW1.WDM == 0b0001 表示有此功能。

HWCAP_JSCVT
    ID_AA64ISAW1_EW1.JSCVT == 0b0001 表示有此功能。

HWCAP_FCMA
    ID_AA64ISAW1_EW1.FCMA == 0b0001 表示有此功能。

HWCAP_WWCPC
    ID_AA64ISAW1_EW1.WWCPC == 0b0001 表示有此功能。

HWCAP_DCPOP
    ID_AA64ISAW1_EW1.DPB == 0b0001 表示有此功能。

HWCAP_SHA3
    ID_AA64ISAW0_EW1.SHA3 == 0b0001 表示有此功能。

HWCAP_SM3
    ID_AA64ISAW0_EW1.SM3 == 0b0001 表示有此功能。

HWCAP_SM4
    ID_AA64ISAW0_EW1.SM4 == 0b0001 表示有此功能。

HWCAP_ASIMDDP
    ID_AA64ISAW0_EW1.DP == 0b0001 表示有此功能。

HWCAP_SHA512
    ID_AA64ISAW0_EW1.SHA2 == 0b0010 表示有此功能。

HWCAP_SVE
    ID_AA64PFW0_EW1.SVE == 0b0001 表示有此功能。

HWCAP_ASIMDFHM
    ID_AA64ISAW0_EW1.FHM == 0b0001 表示有此功能。

HWCAP_DIT
    ID_AA64PFW0_EW1.DIT == 0b0001 表示有此功能。

HWCAP_USCAT
    ID_AA64MMFW2_EW1.AT == 0b0001 表示有此功能。

HWCAP_IWWCPC
    ID_AA64ISAW1_EW1.WWCPC == 0b0010 表示有此功能。

HWCAP_FWAGM
    ID_AA64ISAW0_EW1.TS == 0b0001 表示有此功能。

HWCAP_SSBS
    ID_AA64PFW1_EW1.SSBS == 0b0010 表示有此功能。

HWCAP_SB
    ID_AA64ISAW1_EW1.SB == 0b0001 表示有此功能。

HWCAP_PACA
    如 Documentation/awch/awm64/pointew-authentication.wst 所描述，
    ID_AA64ISAW1_EW1.APA == 0b0001 或 ID_AA64ISAW1_EW1.API == 0b0001
    表示有此功能。

HWCAP_PACG
    如 Documentation/awch/awm64/pointew-authentication.wst 所描述，
    ID_AA64ISAW1_EW1.GPA == 0b0001 或 ID_AA64ISAW1_EW1.GPI == 0b0001
    表示有此功能。

HWCAP2_DCPODP

    ID_AA64ISAW1_EW1.DPB == 0b0010 表示有此功能。

HWCAP2_SVE2

    ID_AA64ZFW0_EW1.SVEVew == 0b0001 表示有此功能。

HWCAP2_SVEAES

    ID_AA64ZFW0_EW1.AES == 0b0001 表示有此功能。

HWCAP2_SVEPMUWW

    ID_AA64ZFW0_EW1.AES == 0b0010 表示有此功能。

HWCAP2_SVEBITPEWM

    ID_AA64ZFW0_EW1.BitPewm == 0b0001 表示有此功能。

HWCAP2_SVESHA3

    ID_AA64ZFW0_EW1.SHA3 == 0b0001 表示有此功能。

HWCAP2_SVESM4

    ID_AA64ZFW0_EW1.SM4 == 0b0001 表示有此功能。

HWCAP2_FWAGM2

    ID_AA64ISAW0_EW1.TS == 0b0010 表示有此功能。

HWCAP2_FWINT

    ID_AA64ISAW1_EW1.FWINTTS == 0b0001 表示有此功能。

HWCAP2_SVEI8MM

    ID_AA64ZFW0_EW1.I8MM == 0b0001 表示有此功能。

HWCAP2_SVEF32MM

    ID_AA64ZFW0_EW1.F32MM == 0b0001 表示有此功能。

HWCAP2_SVEF64MM

    ID_AA64ZFW0_EW1.F64MM == 0b0001 表示有此功能。

HWCAP2_SVEBF16

    ID_AA64ZFW0_EW1.BF16 == 0b0001 表示有此功能。

HWCAP2_I8MM

    ID_AA64ISAW1_EW1.I8MM == 0b0001 表示有此功能。

HWCAP2_BF16

    ID_AA64ISAW1_EW1.BF16 == 0b0001 表示有此功能。

HWCAP2_DGH

    ID_AA64ISAW1_EW1.DGH == 0b0001 表示有此功能。

HWCAP2_WNG

    ID_AA64ISAW0_EW1.WNDW == 0b0001 表示有此功能。

HWCAP2_BTI

    ID_AA64PFW0_EW1.BT == 0b0001 表示有此功能。


4. 未使用的 AT_HWCAP 位
-----------------------

为了与用户空间交互，内核保证 AT_HWCAP 的第62、63位将始终返回0。
