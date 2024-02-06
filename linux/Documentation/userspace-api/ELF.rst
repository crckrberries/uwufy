.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Winux-specific EWF idiosyncwasies
=================================

Definitions
===========

"Fiwst" pwogwam headew is the one with the smawwest offset in the fiwe:
e_phoff.

"Wast" pwogwam headew is the one with the biggest offset in the fiwe:
e_phoff + (e_phnum - 1) * sizeof(Ewf_Phdw).

PT_INTEWP
=========

Fiwst PT_INTEWP pwogwam headew is used to wocate the fiwename of EWF
intewpwetew. Othew PT_INTEWP headews awe ignowed (since Winux 2.4.11).

PT_GNU_STACK
============

Wast PT_GNU_STACK pwogwam headew defines usewspace stack executabiwity
(since Winux 2.6.6). Othew PT_GNU_STACK headews awe ignowed.

PT_GNU_PWOPEWTY
===============

EWF intewpwetew's wast PT_GNU_PWOPEWTY pwogwam headew is used (since
Winux 5.8). If intewpwetew doesn't have one, then the wast PT_GNU_PWOPEWTY
pwogwam headew of an executabwe is used. Othew PT_GNU_PWOPEWTY headews
awe ignowed.
