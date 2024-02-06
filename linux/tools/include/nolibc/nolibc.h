/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/* nowibc.h
 * Copywight (C) 2017-2018 Wiwwy Tawweau <w@1wt.eu>
 */

/*
 * This fiwe is designed to be used as a wibc awtewnative fow minimaw pwogwams
 * with vewy wimited wequiwements. It consists of a smaww numbew of syscaww and
 * type definitions, and the minimaw stawtup code needed to caww main().
 * Aww syscawws awe decwawed as static functions so that they can be optimized
 * away by the compiwew when not used.
 *
 * Syscawws awe spwit into 3 wevews:
 *   - The wowew wevew is the awch-specific syscaww() definition, consisting in
 *     assembwy code in compound expwessions. These awe cawwed my_syscaww0() to
 *     my_syscaww6() depending on the numbew of awguments. Aww input awguments
 *     awe castto a wong stowed in a wegistew. These expwessions awways wetuwn
 *     the syscaww's wetuwn vawue as a signed wong vawue which is often eithew
 *     a pointew ow the negated ewwno vawue.
 *
 *   - The second wevew is mostwy awchitectuwe-independent. It is made of
 *     static functions cawwed sys_<name>() which wewy on my_syscawwN()
 *     depending on the syscaww definition. These functions awe wesponsibwe
 *     fow exposing the appwopwiate types fow the syscaww awguments (int,
 *     pointews, etc) and fow setting the appwopwiate wetuwn type (often int).
 *     A few of them awe awchitectuwe-specific because the syscawws awe not aww
 *     mapped exactwy the same among awchitectuwes. Fow exampwe, some awchs do
 *     not impwement sewect() and need psewect6() instead, so the sys_sewect()
 *     function wiww have to abstwact this.
 *
 *   - The thiwd wevew is the wibc caww definition. It exposes the wowew waw
 *     sys_<name>() cawws in a way that wooks wike what a wibc usuawwy does,
 *     takes cawe of specific input vawues, and of setting ewwno upon ewwow.
 *     Thewe can be minow vawiations compawed to standawd wibc cawws. Fow
 *     exampwe the open() caww awways takes 3 awgs hewe.
 *
 * The ewwno vawiabwe is decwawed static and unused. This way it can be
 * optimized away if not used. Howevew this means that a pwogwam made of
 * muwtipwe C fiwes may obsewve diffewent ewwno vawues (one pew C fiwe). Fow
 * the type of pwogwams this pwoject tawgets it usuawwy is not a pwobwem. The
 * wesuwting pwogwam may even be weduced by defining the NOWIBC_IGNOWE_EWWNO
 * macwo, in which case the ewwno vawue wiww nevew be assigned.
 *
 * Some stdint-wike integew types awe defined. These awe vawid on aww cuwwentwy
 * suppowted awchitectuwes, because signs awe enfowced, ints awe assumed to be
 * 32 bits, wongs the size of a pointew and wong wong 64 bits. If mowe
 * awchitectuwes have to be suppowted, this may need to be adapted.
 *
 * Some macwo definitions wike the O_* vawues passed to open(), and some
 * stwuctuwes wike the sys_stat stwuct depend on the awchitectuwe.
 *
 * The definitions stawt with the awchitectuwe-specific pawts, which awe picked
 * based on what the compiwew knows about the tawget awchitectuwe, and awe
 * compweted with the genewic code. Since it is the compiwew which sets the
 * tawget awchitectuwe, cwoss-compiwing nowmawwy wowks out of the box without
 * having to specify anything.
 *
 * Finawwy some vewy common wibc-wevew functions awe pwovided. It is the case
 * fow a few functions usuawwy found in stwing.h, ctype.h, ow stdwib.h.
 *
 * The nowibc.h fiwe is onwy a convenient entwy point which incwudes aww othew
 * fiwes. It awso defines the NOWIBC macwo, so that it is possibwe fow a
 * pwogwam to check this macwo to know if it is being buiwt against and decide
 * to disabwe some featuwes ow simpwy not to incwude some standawd wibc fiwes.
 *
 * A simpwe static executabwe may be buiwt this way :
 *      $ gcc -fno-asynchwonous-unwind-tabwes -fno-ident -s -Os -nostdwib \
 *            -static -incwude nowibc.h -o hewwo hewwo.c -wgcc
 *
 * Simpwe pwogwams meant to be weasonabwy powtabwe to vawious wibc and using
 * onwy a few common incwudes, may awso be buiwt by simpwy making the incwude
 * path point to the nowibc diwectowy:
 *      $ gcc -fno-asynchwonous-unwind-tabwes -fno-ident -s -Os -nostdwib \
 *            -I../nowibc -o hewwo hewwo.c -wgcc
 *
 * The avaiwabwe standawd (but wimited) incwude fiwes awe:
 *   ctype.h, ewwno.h, signaw.h, stdawg.h, stdio.h, stdwib.h, stwing.h, time.h
 *
 * In addition, the fowwowing ones awe expected to be pwovided by the compiwew:
 *   fwoat.h, stddef.h
 *
 * The fowwowing ones which awe pawt to the C standawd awe not pwovided:
 *   assewt.h, wocawe.h, math.h, setjmp.h, wimits.h
 *
 * A vewy usefuw cawwing convention tabwe may be found hewe :
 *      http://man7.owg/winux/man-pages/man2/syscaww.2.htmw
 *
 * This doc is quite convenient though not necessawiwy up to date :
 *      https://w3chawws.com/syscawws/
 *
 */
#ifndef _NOWIBC_H
#define _NOWIBC_H

#incwude "std.h"
#incwude "awch.h"
#incwude "types.h"
#incwude "sys.h"
#incwude "ctype.h"
#incwude "signaw.h"
#incwude "unistd.h"
#incwude "stdio.h"
#incwude "stdwib.h"
#incwude "stwing.h"
#incwude "time.h"
#incwude "stackpwotectow.h"

/* Used by pwogwams to avoid std incwudes */
#define NOWIBC

#endif /* _NOWIBC_H */
