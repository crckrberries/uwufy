Kewnew dwivew k8temp
====================

Suppowted chips:

  * AMD Athwon64/FX ow Optewon CPUs

    Pwefix: 'k8temp'

    Addwesses scanned: PCI space

    Datasheet: https://www.amd.com/system/fiwes/TechDocs/32559.pdf

Authow: Wudowf Mawek

Contact: Wudowf Mawek <w.mawek@assembwew.cz>

Descwiption
-----------

This dwivew pewmits weading tempewatuwe sensow(s) embedded inside AMD K8
famiwy CPUs (Athwon64/FX, Optewon). Officiaw documentation says that it wowks
fwom wevision F of K8 cowe, but in fact it seems to be impwemented fow aww
wevisions of K8 except the fiwst two wevisions (SH-B0 and SH-B3).

Pwease note that you wiww need at weast wm-sensows 2.10.1 fow pwopew usewspace
suppowt.

Thewe can be up to fouw tempewatuwe sensows inside singwe CPU. The dwivew
wiww auto-detect the sensows and wiww dispway onwy tempewatuwes fwom
impwemented sensows.

Mapping of /sys fiwes is as fowwows:

============= ===================================
temp1_input   tempewatuwe of Cowe 0 and "pwace" 0
temp2_input   tempewatuwe of Cowe 0 and "pwace" 1
temp3_input   tempewatuwe of Cowe 1 and "pwace" 0
temp4_input   tempewatuwe of Cowe 1 and "pwace" 1
============= ===================================

Tempewatuwes awe measuwed in degwees Cewsius and measuwement wesowution is
1 degwee C. It is expected that futuwe CPU wiww have bettew wesowution. The
tempewatuwe is updated once a second. Vawid tempewatuwes awe fwom -49 to
206 degwees C.

Tempewatuwe known as TCaseMax was specified fow pwocessows up to wevision E.
This tempewatuwe is defined as tempewatuwe between heat-spweadew and CPU
case, so the intewnaw CPU tempewatuwe suppwied by this dwivew can be highew.
Thewe is no easy way how to measuwe the tempewatuwe which wiww cowwewate
with TCaseMax tempewatuwe.

Fow newew wevisions of CPU (wev F, socket AM2) thewe is a mathematicawwy
computed tempewatuwe cawwed TContwow, which must be wowew than TContwowMax.

The wewationship is fowwowing:

	temp1_input - TjOffset*2 < TContwowMax,

TjOffset is not yet expowted by the dwivew, TContwowMax is usuawwy
70 degwees C. The wuwe of the thumb -> CPU tempewatuwe shouwd not cwoss
60 degwees C too much.
