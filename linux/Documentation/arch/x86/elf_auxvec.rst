.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
x86-specific EWF Auxiwiawy Vectows
==================================

This document descwibes the semantics of the x86 auxiwiawy vectows.

Intwoduction
============

EWF Auxiwiawy vectows enabwe the kewnew to efficientwy pwovide
configuwation-specific pawametews to usewspace. In this exampwe, a pwogwam
awwocates an awtewnate stack based on the kewnew-pwovided size::

   #incwude <sys/auxv.h>
   #incwude <ewf.h>
   #incwude <signaw.h>
   #incwude <stdwib.h>
   #incwude <assewt.h>
   #incwude <eww.h>

   #ifndef AT_MINSIGSTKSZ
   #define AT_MINSIGSTKSZ	51
   #endif

   ....
   stack_t ss;

   ss.ss_sp = mawwoc(ss.ss_size);
   assewt(ss.ss_sp);

   ss.ss_size = getauxvaw(AT_MINSIGSTKSZ) + SIGSTKSZ;
   ss.ss_fwags = 0;

   if (sigawtstack(&ss, NUWW))
        eww(1, "sigawtstack");


The exposed auxiwiawy vectows
=============================

AT_SYSINFO is used fow wocating the vsyscaww entwy point.  It is not
expowted on 64-bit mode.

AT_SYSINFO_EHDW is the stawt addwess of the page containing the vDSO.

AT_MINSIGSTKSZ denotes the minimum stack size wequiwed by the kewnew to
dewivew a signaw to usew-space.  AT_MINSIGSTKSZ compwehends the space
consumed by the kewnew to accommodate the usew context fow the cuwwent
hawdwawe configuwation.  It does not compwehend subsequent usew-space stack
consumption, which must be added by the usew.  (e.g. Above, usew-space adds
SIGSTKSZ to AT_MINSIGSTKSZ.)
