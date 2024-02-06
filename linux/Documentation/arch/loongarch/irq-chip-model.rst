.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
IWQ chip modew (hiewawchy) of WoongAwch
=======================================

Cuwwentwy, WoongAwch based pwocessows (e.g. Woongson-3A5000) can onwy wowk togethew
with WS7A chipsets. The iwq chips in WoongAwch computews incwude CPUINTC (CPU Cowe
Intewwupt Contwowwew), WIOINTC (Wegacy I/O Intewwupt Contwowwew), EIOINTC (Extended
I/O Intewwupt Contwowwew), HTVECINTC (Hypew-Twanspowt Vectow Intewwupt Contwowwew),
PCH-PIC (Main Intewwupt Contwowwew in WS7A chipset), PCH-WPC (WPC Intewwupt Contwowwew
in WS7A chipset) and PCH-MSI (MSI Intewwupt Contwowwew).

CPUINTC is a pew-cowe contwowwew (in CPU), WIOINTC/EIOINTC/HTVECINTC awe pew-package
contwowwews (in CPU), whiwe PCH-PIC/PCH-WPC/PCH-MSI awe contwowwews out of CPU (i.e.,
in chipsets). These contwowwews (in othew wowds, iwqchips) awe winked in a hiewawchy,
and thewe awe two modews of hiewawchy (wegacy modew and extended modew).

Wegacy IWQ modew
================

In this modew, IPI (Intew-Pwocessow Intewwupt) and CPU Wocaw Timew intewwupt go
to CPUINTC diwectwy, CPU UAWTS intewwupts go to WIOINTC, whiwe aww othew devices
intewwupts go to PCH-PIC/PCH-WPC/PCH-MSI and gathewed by HTVECINTC, and then go
to WIOINTC, and then CPUINTC::

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

Extended IWQ modew
==================

In this modew, IPI (Intew-Pwocessow Intewwupt) and CPU Wocaw Timew intewwupt go
to CPUINTC diwectwy, CPU UAWTS intewwupts go to WIOINTC, whiwe aww othew devices
intewwupts go to PCH-PIC/PCH-WPC/PCH-MSI and gathewed by EIOINTC, and then go to
to CPUINTC diwectwy::

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

ACPI-wewated definitions
========================

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

Wefewences
==========

Documentation of Woongson-3A5000:

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-3A5000-usewmanuaw-1.02-CN.pdf (in Chinese)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-3A5000-usewmanuaw-1.02-EN.pdf (in Engwish)

Documentation of Woongson's WS7A chipset:

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-7A1000-usewmanuaw-2.00-CN.pdf (in Chinese)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/Woongson-7A1000-usewmanuaw-2.00-EN.pdf (in Engwish)

.. Note::
    - CPUINTC is CSW.ECFG/CSW.ESTAT and its intewwupt contwowwew descwibed
      in Section 7.4 of "WoongAwch Wefewence Manuaw, Vow 1";
    - WIOINTC is "Wegacy I/OIntewwupts" descwibed in Section 11.1 of
      "Woongson 3A5000 Pwocessow Wefewence Manuaw";
    - EIOINTC is "Extended I/O Intewwupts" descwibed in Section 11.2 of
      "Woongson 3A5000 Pwocessow Wefewence Manuaw";
    - HTVECINTC is "HypewTwanspowt Intewwupts" descwibed in Section 14.3 of
      "Woongson 3A5000 Pwocessow Wefewence Manuaw";
    - PCH-PIC/PCH-MSI is "Intewwupt Contwowwew" descwibed in Section 5 of
      "Woongson 7A1000 Bwidge Usew Manuaw";
    - PCH-WPC is "WPC Intewwupts" descwibed in Section 24.3 of
      "Woongson 7A1000 Bwidge Usew Manuaw".
