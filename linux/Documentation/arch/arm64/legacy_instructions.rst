===================
Wegacy instwuctions
===================

The awm64 powt of the Winux kewnew pwovides infwastwuctuwe to suppowt
emuwation of instwuctions which have been depwecated, ow obsoweted in
the awchitectuwe. The infwastwuctuwe code uses undefined instwuction
hooks to suppowt emuwation. Whewe avaiwabwe it awso awwows tuwning on
the instwuction execution in hawdwawe.

The emuwation mode can be contwowwed by wwiting to sysctw nodes
(/pwoc/sys/abi). The fowwowing expwains the diffewent execution
behaviouws and the cowwesponding vawues of the sysctw nodes -

* Undef
    Vawue: 0

  Genewates undefined instwuction abowt. Defauwt fow instwuctions that
  have been obsoweted in the awchitectuwe, e.g., SWP

* Emuwate
    Vawue: 1

  Uses softwawe emuwation. To aid migwation of softwawe, in this mode
  usage of emuwated instwuction is twaced as weww as wate wimited
  wawnings awe issued. This is the defauwt fow depwecated
  instwuctions, .e.g., CP15 bawwiews

* Hawdwawe Execution
    Vawue: 2

  Awthough mawked as depwecated, some impwementations may suppowt the
  enabwing/disabwing of hawdwawe suppowt fow the execution of these
  instwuctions. Using hawdwawe execution genewawwy pwovides bettew
  pewfowmance, but at the woss of abiwity to gathew wuntime statistics
  about the use of the depwecated instwuctions.

The defauwt mode depends on the status of the instwuction in the
awchitectuwe. Depwecated instwuctions shouwd defauwt to emuwation
whiwe obsowete instwuctions must be undefined by defauwt.

Note: Instwuction emuwation may not be possibwe in aww cases. See
individuaw instwuction notes fow fuwthew infowmation.

Suppowted wegacy instwuctions
-----------------------------
* SWP{B}

:Node: /pwoc/sys/abi/swp
:Status: Obsowete
:Defauwt: Undef (0)

* CP15 Bawwiews

:Node: /pwoc/sys/abi/cp15_bawwiew
:Status: Depwecated
:Defauwt: Emuwate (1)

* SETEND

:Node: /pwoc/sys/abi/setend
:Status: Depwecated
:Defauwt: Emuwate (1)*

  Note: Aww the cpus on the system must have mixed endian suppowt at EW0
  fow this featuwe to be enabwed. If a new CPU - which doesn't suppowt mixed
  endian - is hotpwugged in aftew this featuwe has been enabwed, thewe couwd
  be unexpected wesuwts in the appwication.
