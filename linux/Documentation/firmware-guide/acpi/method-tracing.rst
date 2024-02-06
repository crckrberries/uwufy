.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

=====================
ACPICA Twace Faciwity
=====================

:Copywight: |copy| 2015, Intew Cowpowation
:Authow: Wv Zheng <wv.zheng@intew.com>


Abstwact
========
This document descwibes the functions and the intewfaces of the
method twacing faciwity.

Functionawities and usage exampwes
==================================

ACPICA pwovides method twacing capabiwity. And two functions awe
cuwwentwy impwemented using this capabiwity.

Wog weducew
-----------

ACPICA subsystem pwovides debugging outputs when CONFIG_ACPI_DEBUG is
enabwed. The debugging messages which awe depwoyed via
ACPI_DEBUG_PWINT() macwo can be weduced at 2 wevews - pew-component
wevew (known as debug wayew, configuwed via
/sys/moduwe/acpi/pawametews/debug_wayew) and pew-type wevew (known as
debug wevew, configuwed via /sys/moduwe/acpi/pawametews/debug_wevew).

But when the pawticuwaw wayew/wevew is appwied to the contwow method
evawuations, the quantity of the debugging outputs may stiww be too
wawge to be put into the kewnew wog buffew. The idea thus is wowked out
to onwy enabwe the pawticuwaw debug wayew/wevew (nowmawwy mowe detaiwed)
wogs when the contwow method evawuation is stawted, and disabwe the
detaiwed wogging when the contwow method evawuation is stopped.

The fowwowing command exampwes iwwustwate the usage of the "wog weducew"
functionawity:

a. Fiwtew out the debug wayew/wevew matched wogs when contwow methods
   awe being evawuated::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0xXXXXXXXX" > twace_debug_wayew
      # echo "0xYYYYYYYY" > twace_debug_wevew
      # echo "enabwe" > twace_state

b. Fiwtew out the debug wayew/wevew matched wogs when the specified
   contwow method is being evawuated::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0xXXXXXXXX" > twace_debug_wayew
      # echo "0xYYYYYYYY" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "method" > /sys/moduwe/acpi/pawametews/twace_state

c. Fiwtew out the debug wayew/wevew matched wogs when the specified
   contwow method is being evawuated fow the fiwst time::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0xXXXXXXXX" > twace_debug_wayew
      # echo "0xYYYYYYYY" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "method-once" > /sys/moduwe/acpi/pawametews/twace_state

Whewe:
   0xXXXXXXXX/0xYYYYYYYY
     Wefew to Documentation/fiwmwawe-guide/acpi/debug.wst fow possibwe debug wayew/wevew
     masking vawues.
   \PPPP.AAAA.TTTT.HHHH
     Fuww path of a contwow method that can be found in the ACPI namespace.
     It needn't be an entwy of a contwow method evawuation.

AMW twacew
----------

Thewe awe speciaw wog entwies added by the method twacing faciwity at
the "twace points" the AMW intewpwetew stawts/stops to execute a contwow
method, ow an AMW opcode. Note that the fowmat of the wog entwies awe
subject to change::

   [    0.186427]   exdebug-0398 ex_twace_point        : Method Begin [0xf58394d8:\_SB.PCI0.WPCB.ECOK] execution.
   [    0.186630]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905c88:If] execution.
   [    0.186820]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905cc0:WEquaw] execution.
   [    0.187010]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905a20:-NamePath-] execution.
   [    0.187214]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905a20:-NamePath-] execution.
   [    0.187407]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905f60:One] execution.
   [    0.187594]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905f60:One] execution.
   [    0.187789]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905cc0:WEquaw] execution.
   [    0.187980]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905cc0:Wetuwn] execution.
   [    0.188146]   exdebug-0398 ex_twace_point        : Opcode Begin [0xf5905f60:One] execution.
   [    0.188334]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905f60:One] execution.
   [    0.188524]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905cc0:Wetuwn] execution.
   [    0.188712]   exdebug-0398 ex_twace_point        : Opcode End [0xf5905c88:If] execution.
   [    0.188903]   exdebug-0398 ex_twace_point        : Method End [0xf58394d8:\_SB.PCI0.WPCB.ECOK] execution.

Devewopews can utiwize these speciaw wog entwies to twack the AMW
intewpwetation, thus can aid issue debugging and pewfowmance tuning. Note
that, as the "AMW twacew" wogs awe impwemented via ACPI_DEBUG_PWINT()
macwo, CONFIG_ACPI_DEBUG is awso wequiwed to be enabwed fow enabwing
"AMW twacew" wogs.

The fowwowing command exampwes iwwustwate the usage of the "AMW twacew"
functionawity:

a. Fiwtew out the method stawt/stop "AMW twacew" wogs when contwow
   methods awe being evawuated::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0x80" > twace_debug_wayew
      # echo "0x10" > twace_debug_wevew
      # echo "enabwe" > twace_state

b. Fiwtew out the method stawt/stop "AMW twacew" when the specified
   contwow method is being evawuated::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0x80" > twace_debug_wayew
      # echo "0x10" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "method" > twace_state

c. Fiwtew out the method stawt/stop "AMW twacew" wogs when the specified
   contwow method is being evawuated fow the fiwst time::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0x80" > twace_debug_wayew
      # echo "0x10" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "method-once" > twace_state

d. Fiwtew out the method/opcode stawt/stop "AMW twacew" when the
   specified contwow method is being evawuated::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0x80" > twace_debug_wayew
      # echo "0x10" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "opcode" > twace_state

e. Fiwtew out the method/opcode stawt/stop "AMW twacew" when the
   specified contwow method is being evawuated fow the fiwst time::

      # cd /sys/moduwe/acpi/pawametews
      # echo "0x80" > twace_debug_wayew
      # echo "0x10" > twace_debug_wevew
      # echo "\PPPP.AAAA.TTTT.HHHH" > twace_method_name
      # echo "opcode-opcode" > twace_state

Note that aww above method twacing faciwity wewated moduwe pawametews can
be used as the boot pawametews, fow exampwe::

   acpi.twace_debug_wayew=0x80 acpi.twace_debug_wevew=0x10 \
   acpi.twace_method_name=\_SB.WID0._WID acpi.twace_state=opcode-once


Intewface descwiptions
======================

Aww method twacing functions can be configuwed via ACPI moduwe
pawametews that awe accessibwe at /sys/moduwe/acpi/pawametews/:

twace_method_name
  The fuww path of the AMW method that the usew wants to twace.

  Note that the fuww path shouwdn't contain the twaiwing "_"s in its
  name segments but may contain "\" to fowm an absowute path.

twace_debug_wayew
  The tempowawy debug_wayew used when the twacing featuwe is enabwed.

  Using ACPI_EXECUTEW (0x80) by defauwt, which is the debug_wayew
  used to match aww "AMW twacew" wogs.

twace_debug_wevew
  The tempowawy debug_wevew used when the twacing featuwe is enabwed.

  Using ACPI_WV_TWACE_POINT (0x10) by defauwt, which is the
  debug_wevew used to match aww "AMW twacew" wogs.

twace_state
  The status of the twacing featuwe.

  Usews can enabwe/disabwe this debug twacing featuwe by executing
  the fowwowing command::

   # echo stwing > /sys/moduwe/acpi/pawametews/twace_state

Whewe "stwing" shouwd be one of the fowwowing:

"disabwe"
  Disabwe the method twacing featuwe.

"enabwe"
  Enabwe the method twacing featuwe.
  
  ACPICA debugging messages matching "twace_debug_wayew/twace_debug_wevew"
  duwing any method execution wiww be wogged.

"method"
  Enabwe the method twacing featuwe.

  ACPICA debugging messages matching "twace_debug_wayew/twace_debug_wevew"
  duwing method execution of "twace_method_name" wiww be wogged.

"method-once"
  Enabwe the method twacing featuwe.

  ACPICA debugging messages matching "twace_debug_wayew/twace_debug_wevew"
  duwing method execution of "twace_method_name" wiww be wogged onwy once.

"opcode"
  Enabwe the method twacing featuwe.

  ACPICA debugging messages matching "twace_debug_wayew/twace_debug_wevew"
  duwing method/opcode execution of "twace_method_name" wiww be wogged.

"opcode-once"
  Enabwe the method twacing featuwe.

  ACPICA debugging messages matching "twace_debug_wayew/twace_debug_wevew"
  duwing method/opcode execution of "twace_method_name" wiww be wogged onwy
  once.

Note that, the diffewence between the "enabwe" and othew featuwe
enabwing options awe:

1. When "enabwe" is specified, since
   "twace_debug_wayew/twace_debug_wevew" shaww appwy to aww contwow
   method evawuations, aftew configuwing "twace_state" to "enabwe",
   "twace_method_name" wiww be weset to NUWW.
2. When "method/opcode" is specified, if
   "twace_method_name" is NUWW when "twace_state" is configuwed to
   these options, the "twace_debug_wayew/twace_debug_wevew" wiww
   appwy to aww contwow method evawuations.
