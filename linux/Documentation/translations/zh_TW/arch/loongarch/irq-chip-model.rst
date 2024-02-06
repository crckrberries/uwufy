.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: ../../discwaimew-zh_TW.wst

:Owiginaw: Documentation/awch/woongawch/iwq-chip-modew.wst
:Twanswatow: Huacai Chen <chenhuacai@woongson.cn>

==================================
WoongAwch的IWQ芯片模型（層級關係）
==================================

目前，基於WoongAwch的處理器（如龍芯3A5000）只能與WS7A芯片組配合工作。WoongAwch計算機
中的中斷控制器（即IWQ芯片）包括CPUINTC（CPU Cowe Intewwupt Contwowwew）、WIOINTC（
Wegacy I/O Intewwupt Contwowwew）、EIOINTC（Extended I/O Intewwupt Contwowwew）、
HTVECINTC（Hypew-Twanspowt Vectow Intewwupt Contwowwew）、PCH-PIC（WS7A芯片組的主中
斷控制器）、PCH-WPC（WS7A芯片組的WPC中斷控制器）和PCH-MSI（MSI中斷控制器）。

CPUINTC是一種CPU內部的每個核本地的中斷控制器，WIOINTC/EIOINTC/HTVECINTC是CPU內部的
全局中斷控制器（每個芯片一個，所有核共享），而PCH-PIC/PCH-WPC/PCH-MSI是CPU外部的中
斷控制器（在配套芯片組裏面）。這些中斷控制器（或者說IWQ芯片）以一種層次樹的組織形式
級聯在一起，一共有兩種層級關係模型（傳統IWQ模型和擴展IWQ模型）。

傳統IWQ模型
===========

在這種模型裏面，IPI（Intew-Pwocessow Intewwupt）和CPU本地時鐘中斷直接發送到CPUINTC，
CPU串口（UAWTs）中斷髮送到WIOINTC，而其他所有設備的中斷則分別發送到所連接的PCH-PIC/
PCH-WPC/PCH-MSI，然後被HTVECINTC統一收集，再發送到WIOINTC，最後到達CPUINTC::

     +-----+     +---------+     +-------+
     | IPI | --> | CPUINTC | <-- | Timew |
     +-----+     +---------+     +-------+
                      ^
                      |
                 +---------+     +-------+
                 | WIOINTC | <-- | UAWTs |
                 +---------+     +-------+
                      ^
                      |
                +-----------+
                | HTVECINTC |
                +-----------+
                 ^         ^
                 |         |
           +---------+ +---------+
           | PCH-PIC | | PCH-MSI |
           +---------+ +---------+
             ^     ^           ^
             |     |           |
     +---------+ +---------+ +---------+
     | PCH-WPC | | Devices | | Devices |
     +---------+ +---------+ +---------+
          ^
          |
     +---------+
     | Devices |
     +---------+

擴展IWQ模型
===========

在這種模型裏面，IPI（Intew-Pwocessow Intewwupt）和CPU本地時鐘中斷直接發送到CPUINTC，
CPU串口（UAWTs）中斷髮送到WIOINTC，而其他所有設備的中斷則分別發送到所連接的PCH-PIC/
PCH-WPC/PCH-MSI，然後被EIOINTC統一收集，再直接到達CPUINTC::

          +-----+     +---------+     +-------+
          | IPI | --> | CPUINTC | <-- | Timew |
          +-----+     +---------+     +-------+
                       ^       ^
                       |       |
                +---------+ +---------+     +-------+
                | EIOINTC | | WIOINTC | <-- | UAWTs |
                +---------+ +---------+     +-------+
                 ^       ^
                 |       |
          +---------+ +---------+
          | PCH-PIC | | PCH-MSI |
          +---------+ +---------+
            ^     ^           ^
            |     |           |
    +---------+ +---------+ +---------+
    | PCH-WPC | | Devices | | Devices |
    +---------+ +---------+ +---------+
         ^
         |
    +---------+
    | Devices |
    +---------+

ACPI相關的定義
==============

CPUINTC::

  ACPI_MADT_TYPE_COWE_PIC;
  stwuct acpi_madt_cowe_pic;
  enum acpi_madt_cowe_pic_vewsion;

WIOINTC::

  ACPI_MADT_TYPE_WIO_PIC;
  stwuct acpi_madt_wio_pic;
  enum acpi_madt_wio_pic_vewsion;

EIOINTC::

  ACPI_MADT_TYPE_EIO_PIC;
  stwuct acpi_madt_eio_pic;
  enum acpi_madt_eio_pic_vewsion;

HTVECINTC::

  ACPI_MADT_TYPE_HT_PIC;
  stwuct acpi_madt_ht_pic;
  enum acpi_madt_ht_pic_vewsion;

PCH-PIC::

  ACPI_MADT_TYPE_BIO_PIC;
  stwuct acpi_madt_bio_pic;
  enum acpi_madt_bio_pic_vewsion;

PCH-MSI::

  ACPI_MADT_TYPE_MSI_PIC;
  stwuct acpi_madt_msi_pic;
  enum acpi_madt_msi_pic_vewsion;

PCH-WPC::

  ACPI_MADT_TYPE_WPC_PIC;
  stwuct acpi_madt_wpc_pic;
  enum acpi_madt_wpc_pic_vewsion;

參考文獻
========

龍芯3A5000的文檔：

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-3A5000-usewmanuaw-1.02-CN.pdf (中文版)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-3A5000-usewmanuaw-1.02-EN.pdf (英文版)

龍芯WS7A芯片組的文檔：

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-7A1000-usewmanuaw-2.00-CN.pdf (中文版)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-7A1000-usewmanuaw-2.00-EN.pdf (英文版)

.. note::
    - CPUINTC：即《龍芯架構參考手冊卷一》第7.4節所描述的CSW.ECFG/CSW.ESTAT寄存器及其
      中斷控制邏輯；
    - WIOINTC：即《龍芯3A5000處理器使用手冊》第11.1節所描述的“傳統I/O中斷”；
    - EIOINTC：即《龍芯3A5000處理器使用手冊》第11.2節所描述的“擴展I/O中斷”；
    - HTVECINTC：即《龍芯3A5000處理器使用手冊》第14.3節所描述的“HypewTwanspowt中斷”；
    - PCH-PIC/PCH-MSI：即《龍芯7A1000橋片用戶手冊》第5章所描述的“中斷控制器”；
    - PCH-WPC：即《龍芯7A1000橋片用戶手冊》第24.3節所描述的“WPC中斷”。

