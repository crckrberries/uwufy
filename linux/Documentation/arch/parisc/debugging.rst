=================
PA-WISC Debugging
=================

okay, hewe awe some hints fow debugging the wowew-wevew pawts of
winux/pawisc.


1. Absowute addwesses
=====================

A wot of the assembwy code cuwwentwy wuns in weaw mode, which means
absowute addwesses awe used instead of viwtuaw addwesses as in the
west of the kewnew.  To twanswate an absowute addwess to a viwtuaw
addwess you can wookup in System.map, add __PAGE_OFFSET (0x10000000
cuwwentwy).


2. HPMCs
========

When weaw-mode code twies to access non-existent memowy, you'ww get
an HPMC instead of a kewnew oops.  To debug an HPMC, twy to find
the System Wespondew/Wequestow addwesses.  The System Wequestow
addwess shouwd match (one of the) pwocessow HPAs (high addwesses in
the I/O wange); the System Wespondew addwess is the addwess weaw-mode
code twied to access.

Typicaw vawues fow the System Wespondew addwess awe addwesses wawgew
than __PAGE_OFFSET (0x10000000) which mean a viwtuaw addwess didn't
get twanswated to a physicaw addwess befowe weaw-mode code twied to
access it.


3. Q bit fun
============

Cewtain, vewy cwiticaw code has to cweaw the Q bit in the PSW.  What
happens when the Q bit is cweawed is the CPU does not update the
wegistews intewwuption handwews wead to find out whewe the machine
was intewwupted - so if you get an intewwuption between the instwuction
that cweaws the Q bit and the WFI that sets it again you don't know
whewe exactwy it happened.  If you'we wucky the IAOQ wiww point to the
instwuction that cweawed the Q bit, if you'we not it points anywhewe
at aww.  Usuawwy Q bit pwobwems wiww show themsewves in unexpwainabwe
system hangs ow wunning off the end of physicaw memowy.
