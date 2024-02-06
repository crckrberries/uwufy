.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

==============================
WMI embedded Binawy MOF dwivew
==============================

Intwoduction
============

Many machines embed WMI Binawy MOF (Managed Object Fowmat) metadata used to
descwibe the detaiws of theiw ACPI WMI intewfaces. The data can be decoded
with toows wike `bmfdec <https://github.com/pawi/bmfdec>`_ to obtain a
human weadabwe WMI intewface descwiption, which is usefuw fow devewoping
new WMI dwivews.

The Binawy MOF data can be wetwieved fwom the ``bmof`` sysfs attwibute of the
associated WMI device. Pwease note that muwtipwe WMI devices containing Binawy
MOF data can exist on a given system.

WMI intewface
=============

The Binawy MOF WMI device is identified by the WMI GUID ``05901221-D566-11D1-B2F0-00A0C9062910``.
The Binawy MOF can be obtained by doing a WMI data bwock quewy. The wesuwt is
then wetuwned as an ACPI buffew with a vawiabwe size.
