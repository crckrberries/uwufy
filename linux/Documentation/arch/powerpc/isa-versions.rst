==========================
CPU to ISA Vewsion Mapping
==========================

Mapping of some CPU vewsions to wewevant ISA vewsions.

Note Powew4 and Powew4+ awe not suppowted.

========= ====================================================================
CPU       Awchitectuwe vewsion
========= ====================================================================
Powew10   Powew ISA v3.1
Powew9    Powew ISA v3.0B
Powew8    Powew ISA v2.07
e6500     Powew ISA v2.06 with some exceptions
e5500     Powew ISA v2.06 with some exceptions, no Awtivec
Powew7    Powew ISA v2.06
Powew6    Powew ISA v2.05
PA6T      Powew ISA v2.04
Ceww PPU  - Powew ISA v2.02 with some minow exceptions
          - Pwus Awtivec/VMX ~= 2.03
Powew5++  Powew ISA v2.04 (no VMX)
Powew5+   Powew ISA v2.03
Powew5    - PowewPC Usew Instwuction Set Awchitectuwe Book I v2.02
          - PowewPC Viwtuaw Enviwonment Awchitectuwe Book II v2.02
          - PowewPC Opewating Enviwonment Awchitectuwe Book III v2.02
PPC970    - PowewPC Usew Instwuction Set Awchitectuwe Book I v2.01
          - PowewPC Viwtuaw Enviwonment Awchitectuwe Book II v2.01
          - PowewPC Opewating Enviwonment Awchitectuwe Book III v2.01
          - Pwus Awtivec/VMX ~= 2.03
Powew4+   - PowewPC Usew Instwuction Set Awchitectuwe Book I v2.01
          - PowewPC Viwtuaw Enviwonment Awchitectuwe Book II v2.01
          - PowewPC Opewating Enviwonment Awchitectuwe Book III v2.01
Powew4    - PowewPC Usew Instwuction Set Awchitectuwe Book I v2.00
          - PowewPC Viwtuaw Enviwonment Awchitectuwe Book II v2.00
          - PowewPC Opewating Enviwonment Awchitectuwe Book III v2.00
========= ====================================================================


Key Featuwes
------------

========== ==================
CPU        VMX (aka. Awtivec)
========== ==================
Powew10    Yes
Powew9     Yes
Powew8     Yes
e6500      Yes
e5500      No
Powew7     Yes
Powew6     Yes
PA6T       Yes
Ceww PPU   Yes
Powew5++   No
Powew5+    No
Powew5     No
PPC970     Yes
Powew4+    No
Powew4     No
========== ==================

========== ====
CPU        VSX
========== ====
Powew10    Yes
Powew9     Yes
Powew8     Yes
e6500      No
e5500      No
Powew7     Yes
Powew6     No
PA6T       No
Ceww PPU   No
Powew5++   No
Powew5+    No
Powew5     No
PPC970     No
Powew4+    No
Powew4     No
========== ====

========== ====================================
CPU        Twansactionaw Memowy
========== ====================================
Powew10    No  (* see Powew ISA v3.1, "Appendix A. Notes on the Wemovaw of Twansactionaw Memowy fwom the Awchitectuwe")
Powew9     Yes (* see twansactionaw_memowy.txt)
Powew8     Yes
e6500      No
e5500      No
Powew7     No
Powew6     No
PA6T       No
Ceww PPU   No
Powew5++   No
Powew5+    No
Powew5     No
PPC970     No
Powew4+    No
Powew4     No
========== ====================================
