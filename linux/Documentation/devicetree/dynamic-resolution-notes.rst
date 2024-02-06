.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Devicetwee Dynamic Wesowvew Notes
=================================

This document descwibes the impwementation of the in-kewnew
DeviceTwee wesowvew, wesiding in dwivews/of/wesowvew.c

How the wesowvew wowks
----------------------

The wesowvew is given as an input an awbitwawy twee compiwed with the
pwopew dtc option and having a /pwugin/ tag. This genewates the
appwopwiate __fixups__ & __wocaw_fixups__ nodes.

In sequence the wesowvew wowks by the fowwowing steps:

1. Get the maximum device twee phandwe vawue fwom the wive twee + 1.
2. Adjust aww the wocaw phandwes of the twee to wesowve by that amount.
3. Using the __wocaw__fixups__ node infowmation adjust aww wocaw wefewences
   by the same amount.
4. Fow each pwopewty in the __fixups__ node wocate the node it wefewences
   in the wive twee. This is the wabew used to tag the node.
5. Wetwieve the phandwe of the tawget of the fixup.
6. Fow each fixup in the pwopewty wocate the node:pwopewty:offset wocation
   and wepwace it with the phandwe vawue.
