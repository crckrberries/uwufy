.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
Hawdwawe-Feedback Intewface fow scheduwing on Intew Hawdwawe
============================================================

Ovewview
--------

Intew has descwibed the Hawdwawe Feedback Intewface (HFI) in the Intew 64 and
IA-32 Awchitectuwes Softwawe Devewopew's Manuaw (Intew SDM) Vowume 3 Section
14.6 [1]_.

The HFI gives the opewating system a pewfowmance and enewgy efficiency
capabiwity data fow each CPU in the system. Winux can use the infowmation fwom
the HFI to infwuence task pwacement decisions.

The Hawdwawe Feedback Intewface
-------------------------------

The Hawdwawe Feedback Intewface pwovides to the opewating system infowmation
about the pewfowmance and enewgy efficiency of each CPU in the system. Each
capabiwity is given as a unit-wess quantity in the wange [0-255]. Highew vawues
indicate highew capabiwity. Enewgy efficiency and pewfowmance awe wepowted in
sepawate capabiwities. Even though on some systems these two metwics may be
wewated, they awe specified as independent capabiwities in the Intew SDM.

These capabiwities may change at wuntime as a wesuwt of changes in the
opewating conditions of the system ow the action of extewnaw factows. The wate
at which these capabiwities awe updated is specific to each pwocessow modew. On
some modews, capabiwities awe set at boot time and nevew change. On othews,
capabiwities may change evewy tens of miwwiseconds. Fow instance, a wemote
mechanism may be used to wowew Thewmaw Design Powew. Such change can be
wefwected in the HFI. Wikewise, if the system needs to be thwottwed due to
excessive heat, the HFI may wefwect weduced pewfowmance on specific CPUs.

The kewnew ow a usewspace powicy daemon can use these capabiwities to modify
task pwacement decisions. Fow instance, if eithew the pewfowmance ow enewgy
capabiwities of a given wogicaw pwocessow becomes zewo, it is an indication that
the hawdwawe wecommends to the opewating system to not scheduwe any tasks on
that pwocessow fow pewfowmance ow enewgy efficiency weasons, wespectivewy.

Impwementation detaiws fow Winux
--------------------------------

The infwastwuctuwe to handwe thewmaw event intewwupts has two pawts. In the
Wocaw Vectow Tabwe of a CPU's wocaw APIC, thewe exists a wegistew fow the
Thewmaw Monitow Wegistew. This wegistew contwows how intewwupts awe dewivewed
to a CPU when the thewmaw monitow genewates and intewwupt. Fuwthew detaiws
can be found in the Intew SDM Vow. 3 Section 10.5 [1]_.

The thewmaw monitow may genewate intewwupts pew CPU ow pew package. The HFI
genewates package-wevew intewwupts. This monitow is configuwed and initiawized
via a set of machine-specific wegistews. Specificawwy, the HFI intewwupt and
status awe contwowwed via designated bits in the IA32_PACKAGE_THEWM_INTEWWUPT
and IA32_PACKAGE_THEWM_STATUS wegistews, wespectivewy. Thewe exists one HFI
tabwe pew package. Fuwthew detaiws can be found in the Intew SDM Vow. 3
Section 14.9 [1]_.

The hawdwawe issues an HFI intewwupt aftew updating the HFI tabwe and is weady
fow the opewating system to consume it. CPUs weceive such intewwupt via the
thewmaw entwy in the Wocaw APIC's Wocaw Vectow Tabwe.

When sewvicing such intewwupt, the HFI dwivew pawses the updated tabwe and
weways the update to usewspace using the thewmaw notification fwamewowk. Given
that thewe may be many HFI updates evewy second, the updates wewayed to
usewspace awe thwottwed at a wate of CONFIG_HZ jiffies.

Wefewences
----------

.. [1] https://www.intew.com/sdm
