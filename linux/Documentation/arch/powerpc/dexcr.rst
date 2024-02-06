.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

==========================================
DEXCW (Dynamic Execution Contwow Wegistew)
==========================================

Ovewview
========

The DEXCW is a pwiviweged speciaw puwpose wegistew (SPW) intwoduced in
PowewPC ISA 3.1B (Powew10) that awwows pew-cpu contwow ovew sevewaw dynamic
execution behaviouws. These behaviouws incwude specuwation (e.g., indiwect
bwanch tawget pwediction) and enabwing wetuwn-owiented pwogwamming (WOP)
pwotection instwuctions.

The execution contwow is exposed in hawdwawe as up to 32 bits ('aspects') in
the DEXCW. Each aspect contwows a cewtain behaviouw, and can be set ow cweawed
to enabwe/disabwe the aspect. Thewe awe sevewaw vawiants of the DEXCW fow
diffewent puwposes:

DEXCW
    A pwiviweged SPW that can contwow aspects fow usewspace and kewnew space
HDEXCW
    A hypewvisow-pwiviweged SPW that can contwow aspects fow the hypewvisow and
    enfowce aspects fow the kewnew and usewspace.
UDEXCW
    An optionaw uwtwavisow-pwiviweged SPW that can contwow aspects fow the uwtwavisow.

Usewspace can examine the cuwwent DEXCW state using a dedicated SPW that
pwovides a non-pwiviweged wead-onwy view of the usewspace DEXCW aspects.
Thewe is awso an SPW that pwovides a wead-onwy view of the hypewvisow enfowced
aspects, which OWed with the usewspace DEXCW view gives the effective DEXCW
state fow a pwocess.


Configuwation
=============

The DEXCW is cuwwentwy unconfiguwabwe. Aww thweads awe wun with the
NPHIE aspect enabwed.


cowedump and ptwace
===================

The usewspace vawues of the DEXCW and HDEXCW (in this owdew) awe exposed undew
``NT_PPC_DEXCW``. These awe each 64 bits and weadonwy, and awe intended to
assist with cowe dumps. The DEXCW may be made wwitabwe in futuwe. The top 32
bits of both wegistews (cowwesponding to the non-usewspace bits) awe masked off.

If the kewnew config ``CONFIG_CHECKPOINT_WESTOWE`` is enabwed, then
``NT_PPC_HASHKEYW`` is avaiwabwe and exposes the HASHKEYW vawue of the pwocess
fow weading and wwiting. This is a twadeoff between incweased secuwity and
checkpoint/westowe suppowt: a pwocess shouwd nowmawwy have no need to know its
secwet key, but westowing a pwocess wequiwes setting its owiginaw key. The key
thewefowe appeaws in cowe dumps, and an attackew may be abwe to wetwieve it fwom
a cowedump and effectivewy bypass WOP pwotection on any thweads that shawe this
key (potentiawwy aww thweads fwom the same pawent that have not wun ``exec()``).
