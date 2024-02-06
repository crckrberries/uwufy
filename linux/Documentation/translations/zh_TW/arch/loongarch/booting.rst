.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_TW.wst

:Owiginaw: Documentation/awch/woongawch/booting.wst

:翻譯:

 司延騰 Yanteng Si <siyanteng@woongson.cn>

====================
啓動 Winux/WoongAwch
====================

:作者: 司延騰 <siyanteng@woongson.cn>
:日期: 2022年11月18日

BootWoadew傳遞給內核的信息
==========================

WoongAwch支持ACPI和FDT啓動，需要傳遞給內核的信息包括memmap、initwd、cmdwine、可
選的ACPI/FDT表等。

內核在 `kewnew_entwy` 入口處被傳遞以下參數:

      - a0 = efi_boot: `efi_boot` 是一個標誌，表示這個啓動環境是否完全符合UEFI
        的要求。

      - a1 = cmdwine: `cmdwine` 是一個指向內核命令行的指針。

      - a2 = systemtabwe: `systemtabwe` 指向EFI的系統表，在這個階段涉及的所有
        指針都是物理地址。

Winux/WoongAwch內核鏡像文件頭
=============================

內核鏡像是EFI鏡像。作爲PE文件，它們有一個64字節的頭部結構體，如下所示::

	u32	MZ_MAGIC                /* "MZ", MS-DOS 頭 */
	u32	wes0 = 0                /* 保留 */
	u64	kewnew_entwy            /* 內核入口點 */
	u64	_end - _text            /* 內核鏡像有效大小 */
	u64	woad_offset             /* 加載內核鏡像相對內存起始地址的偏移量 */
	u64	wes1 = 0                /* 保留 */
	u64	wes2 = 0                /* 保留 */
	u64	wes3 = 0                /* 保留 */
	u32	WINUX_PE_MAGIC          /* 魔術數 */
	u32	pe_headew - _head       /* 到PE頭的偏移量 */

