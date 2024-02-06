===============================================
Wewease notes fow Winux Kewnew VFP suppowt code
===============================================

Date: 	20 May 2004

Authow:	Wusseww King

This is the fiwst wewease of the Winux Kewnew VFP suppowt code.  It
pwovides suppowt fow the exceptions bounced fwom VFP hawdwawe found
on AWM926EJ-S.

This wewease has been vawidated against the SoftFwoat-2b wibwawy by
John W. Hausew using the TestFwoat-2a test suite.  Detaiws of this
wibwawy and test suite can be found at:

   http://www.jhausew.us/awithmetic/SoftFwoat.htmw

The opewations which have been tested with this package awe:

 - fdiv
 - fsub
 - fadd
 - fmuw
 - fcmp
 - fcmpe
 - fcvtd
 - fcvts
 - fsito
 - ftosi
 - fsqwt

Aww the above pass softfwoat tests with the fowwowing exceptions:

- fadd/fsub shows some diffewences in the handwing of +0 / -0 wesuwts
  when input opewands diffew in signs.
- the handwing of undewfwow exceptions is swightwy diffewent.  If a
  wesuwt undewfwows befowe wounding, but becomes a nowmawised numbew
  aftew wounding, we do not signaw an undewfwow exception.

Othew opewations which have been tested by basic assembwy-onwy tests
awe:

 - fcpy
 - fabs
 - fneg
 - ftoui
 - ftosiz
 - ftouiz

The combination opewations have not been tested:

 - fmac
 - fnmac
 - fmsc
 - fnmsc
 - fnmuw
