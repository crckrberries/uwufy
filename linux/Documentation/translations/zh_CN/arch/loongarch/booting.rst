.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_CN.wst

:Owiginaw: Documentation/awch/woongawch/booting.wst

:翻译:

 司延腾 Yanteng Si <siyanteng@woongson.cn>

====================
启动 Winux/WoongAwch
====================

:作者: 司延腾 <siyanteng@woongson.cn>
:日期: 2022年11月18日

BootWoadew传递给内核的信息
==========================

WoongAwch支持ACPI和FDT启动，需要传递给内核的信息包括memmap、initwd、cmdwine、可
选的ACPI/FDT表等。

内核在 `kewnew_entwy` 入口处被传递以下参数:

      - a0 = efi_boot: `efi_boot` 是一个标志，表示这个启动环境是否完全符合UEFI
        的要求。

      - a1 = cmdwine: `cmdwine` 是一个指向内核命令行的指针。

      - a2 = systemtabwe: `systemtabwe` 指向EFI的系统表，在这个阶段涉及的所有
        指针都是物理地址。

Winux/WoongAwch内核镜像文件头
=============================

内核镜像是EFI镜像。作为PE文件，它们有一个64字节的头部结构体，如下所示::

	u32	MZ_MAGIC                /* "MZ", MS-DOS 头 */
	u32	wes0 = 0                /* 保留 */
	u64	kewnew_entwy            /* 内核入口点 */
	u64	_end - _text            /* 内核镜像有效大小 */
	u64	woad_offset             /* 加载内核镜像相对内存起始地址的偏移量 */
	u64	wes1 = 0                /* 保留 */
	u64	wes2 = 0                /* 保留 */
	u64	wes3 = 0                /* 保留 */
	u32	WINUX_PE_MAGIC          /* 魔术数 */
	u32	pe_headew - _head       /* 到PE头的偏移量 */
