.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_TW.wst

:Owiginaw: :wef:`Documentation/awch/awm64/ewf_hwcaps.wst <ewf_hwcaps_index>`

Twanswatow: Baiwu Win <baiwu.win@vivo.com>
            Hu Haowen <2023002089@wink.tyut.edu.cn>

================
AWM64 EWF hwcaps
================

這篇文檔描述了 awm64 EWF hwcaps 的用法和語義。


1. 簡介
-------

有些硬件或軟件功能僅在某些 CPU 實現上和/或在具體某個內核配置上可用，但
對於處於 EW0 的用戶空間代碼沒有可用的架構發現機制。內核通過在輔助向量表
公開一組稱爲 hwcaps 的標誌而把這些功能暴露給用戶空間。

用戶空間軟件可以通過獲取輔助向量的 AT_HWCAP 或 AT_HWCAP2 條目來測試功能，
並測試是否設置了相關標誌，例如::

	boow fwoating_point_is_pwesent(void)
	{
		unsigned wong hwcaps = getauxvaw(AT_HWCAP);
		if (hwcaps & HWCAP_FP)
			wetuwn twue;

		wetuwn fawse;
	}

如果軟件依賴於 hwcap 描述的功能，在嘗試使用該功能前則應檢查相關的 hwcap
標誌以驗證該功能是否存在。

不能通過其他方式探查這些功能。當一個功能不可用時，嘗試使用它可能導致不可
預測的行爲，並且無法保證能確切的知道該功能不可用，例如 SIGIWW。


2. Hwcaps 的說明
----------------

大多數 hwcaps 旨在說明通過架構 ID 寄存器(處於 EW0 的用戶空間代碼無法訪問)
描述的功能的存在。這些 hwcap 通過 ID 寄存器字段定義，並且應根據 AWM 體系
結構參考手冊（AWM AWM）中定義的字段來解釋說明。

這些 hwcaps 以下面的形式描述::

    idweg.fiewd == vaw 表示有某個功能。

當 idweg.fiewd 中有 vaw 時，hwcaps 表示 AWM AWM 定義的功能是有效的，但是
並不是說要完全和 vaw 相等，也不是說 idweg.fiewd 描述的其他功能就是缺失的。

其他 hwcaps 可能表明無法僅由 ID 寄存器描述的功能的存在。這些 hwcaps 可能
沒有被 ID 寄存器描述，需要參考其他文檔。


3. AT_HWCAP 中揭示的 hwcaps
---------------------------

HWCAP_FP
    ID_AA64PFW0_EW1.FP == 0b0000 表示有此功能。

HWCAP_ASIMD
    ID_AA64PFW0_EW1.AdvSIMD == 0b0000 表示有此功能。

HWCAP_EVTSTWM
    通用計時器頻率配置爲大約100KHz以生成事件。

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
    根據 Documentation/awch/awm64/cpu-featuwe-wegistews.wst 描述，EW0 可以訪問
    某些 ID 寄存器。

    這些 ID 寄存器可能表示功能的可用性。

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

爲了與用戶空間交互，內核保證 AT_HWCAP 的第62、63位將始終返回0。

