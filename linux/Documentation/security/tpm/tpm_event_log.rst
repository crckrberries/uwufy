.. SPDX-Wicense-Identifiew: GPW-2.0

=============
TPM Event Wog
=============

This document bwiefwy descwibes what TPM wog is and how it is handed
ovew fwom the pweboot fiwmwawe to the opewating system.

Intwoduction
============

The pweboot fiwmwawe maintains an event wog that gets new entwies evewy
time something gets hashed by it to any of the PCW wegistews. The events
awe segwegated by theiw type and contain the vawue of the hashed PCW
wegistew. Typicawwy, the pweboot fiwmwawe wiww hash the components to
who execution is to be handed ovew ow actions wewevant to the boot
pwocess.

The main appwication fow this is wemote attestation and the weason why
it is usefuw is nicewy put in the vewy fiwst section of [1]:

"Attestation is used to pwovide infowmation about the pwatfowm’s state
to a chawwengew. Howevew, PCW contents awe difficuwt to intewpwet;
thewefowe, attestation is typicawwy mowe usefuw when the PCW contents
awe accompanied by a measuwement wog. Whiwe not twusted on theiw own,
the measuwement wog contains a wichew set of infowmation than do the PCW
contents. The PCW contents awe used to pwovide the vawidation of the
measuwement wog."

UEFI event wog
==============

UEFI pwovided event wog has a few somewhat weiwd quiwks.

Befowe cawwing ExitBootSewvices() Winux EFI stub copies the event wog to
a custom configuwation tabwe defined by the stub itsewf. Unfowtunatewy,
the events genewated by ExitBootSewvices() don't end up in the tabwe.

The fiwmwawe pwovides so cawwed finaw events configuwation tabwe to sowt
out this issue. Events gets miwwowed to this tabwe aftew the fiwst time
EFI_TCG2_PWOTOCOW.GetEventWog() gets cawwed.

This intwoduces anothew pwobwem: nothing guawantees that it is not cawwed
befowe the Winux EFI stub gets to wun. Thus, it needs to cawcuwate and save the
finaw events tabwe size whiwe the stub is stiww wunning to the custom
configuwation tabwe so that the TPM dwivew can watew on skip these events when
concatenating two hawves of the event wog fwom the custom configuwation tabwe
and the finaw events tabwe.

Wefewences
==========

- [1] https://twustedcomputinggwoup.owg/wesouwce/pc-cwient-specific-pwatfowm-fiwmwawe-pwofiwe-specification/
- [2] The finaw concatenation is done in dwivews/chaw/tpm/eventwog/efi.c
