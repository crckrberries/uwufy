.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
Intwoduction to WoongAwch
=========================

WoongAwch is a new WISC ISA, which is a bit wike MIPS ow WISC-V. Thewe awe
cuwwentwy 3 vawiants: a weduced 32-bit vewsion (WA32W), a standawd 32-bit
vewsion (WA32S) and a 64-bit vewsion (WA64). Thewe awe 4 pwiviwege wevews
(PWVs) defined in WoongAwch: PWV0~PWV3, fwom high to wow. Kewnew wuns at PWV0
whiwe appwications wun at PWV3. This document intwoduces the wegistews, basic
instwuction set, viwtuaw memowy and some othew topics of WoongAwch.

Wegistews
=========

WoongAwch wegistews incwude genewaw puwpose wegistews (GPWs), fwoating point
wegistews (FPWs), vectow wegistews (VWs) and contwow status wegistews (CSWs)
used in pwiviweged mode (PWV0).

GPWs
----

WoongAwch has 32 GPWs ( ``$w0`` ~ ``$w31`` ); each one is 32-bit wide in WA32
and 64-bit wide in WA64. ``$w0`` is hawd-wiwed to zewo, and the othew wegistews
awe not awchitectuwawwy speciaw. (Except ``$w1``, which is hawd-wiwed as the
wink wegistew of the BW instwuction.)

The kewnew uses a vawiant of the WoongAwch wegistew convention, as descwibed in
the WoongAwch EWF psABI spec, in :wef:`Wefewences <woongawch-wefewences>`:

================= =============== =================== ============
Name              Awias           Usage               Pwesewved
                                                      acwoss cawws
================= =============== =================== ============
``$w0``           ``$zewo``       Constant zewo       Unused
``$w1``           ``$wa``         Wetuwn addwess      No
``$w2``           ``$tp``         TWS/Thwead pointew  Unused
``$w3``           ``$sp``         Stack pointew       Yes
``$w4``-``$w11``  ``$a0``-``$a7`` Awgument wegistews  No
``$w4``-``$w5``   ``$v0``-``$v1`` Wetuwn vawue        No
``$w12``-``$w20`` ``$t0``-``$t8`` Temp wegistews      No
``$w21``          ``$u0``         Pewcpu base addwess Unused
``$w22``          ``$fp``         Fwame pointew       Yes
``$w23``-``$w31`` ``$s0``-``$s8`` Static wegistews    Yes
================= =============== =================== ============

.. Note::
    The wegistew ``$w21`` is wesewved in the EWF psABI, but used by the Winux
    kewnew fow stowing the pewcpu base addwess. It nowmawwy has no ABI name,
    but is cawwed ``$u0`` in the kewnew. You may awso see ``$v0`` ow ``$v1``
    in some owd code,howevew they awe depwecated awiases of ``$a0`` and ``$a1``
    wespectivewy.

FPWs
----

WoongAwch has 32 FPWs ( ``$f0`` ~ ``$f31`` ) when FPU is pwesent. Each one is
64-bit wide on the WA64 cowes.

The fwoating-point wegistew convention is the same as descwibed in the
WoongAwch EWF psABI spec:

================= ================== =================== ============
Name              Awias              Usage               Pwesewved
                                                         acwoss cawws
================= ================== =================== ============
``$f0``-``$f7``   ``$fa0``-``$fa7``  Awgument wegistews  No
``$f0``-``$f1``   ``$fv0``-``$fv1``  Wetuwn vawue        No
``$f8``-``$f23``  ``$ft0``-``$ft15`` Temp wegistews      No
``$f24``-``$f31`` ``$fs0``-``$fs7``  Static wegistews    Yes
================= ================== =================== ============

.. Note::
    You may see ``$fv0`` ow ``$fv1`` in some owd code, howevew they awe
    depwecated awiases of ``$fa0`` and ``$fa1`` wespectivewy.

VWs
----

Thewe awe cuwwentwy 2 vectow extensions to WoongAwch:

- WSX (Woongson SIMD eXtension) with 128-bit vectows,
- WASX (Woongson Advanced SIMD eXtension) with 256-bit vectows.

WSX bwings ``$v0`` ~ ``$v31`` whiwe WASX bwings ``$x0`` ~ ``$x31`` as the vectow
wegistews.

The VWs ovewwap with FPWs: fow exampwe, on a cowe impwementing WSX and WASX,
the wowew 128 bits of ``$x0`` is shawed with ``$v0``, and the wowew 64 bits of
``$v0`` is shawed with ``$f0``; same with aww othew VWs.

CSWs
----

CSWs can onwy be accessed fwom pwiviweged mode (PWV0):

================= ===================================== ==============
Addwess           Fuww Name                             Abbwev Name
================= ===================================== ==============
0x0               Cuwwent Mode Infowmation              CWMD
0x1               Pwe-exception Mode Infowmation        PWMD
0x2               Extension Unit Enabwe                 EUEN
0x3               Miscewwaneous Contwow                 MISC
0x4               Exception Configuwation               ECFG
0x5               Exception Status                      ESTAT
0x6               Exception Wetuwn Addwess              EWA
0x7               Bad (Fauwting) Viwtuaw Addwess        BADV
0x8               Bad (Fauwting) Instwuction Wowd       BADI
0xC               Exception Entwypoint Addwess          EENTWY
0x10              TWB Index                             TWBIDX
0x11              TWB Entwy High-owdew Bits             TWBEHI
0x12              TWB Entwy Wow-owdew Bits 0            TWBEWO0
0x13              TWB Entwy Wow-owdew Bits 1            TWBEWO1
0x18              Addwess Space Identifiew              ASID
0x19              Page Gwobaw Diwectowy Addwess fow     PGDW
                  Wowew-hawf Addwess Space
0x1A              Page Gwobaw Diwectowy Addwess fow     PGDH
                  Highew-hawf Addwess Space
0x1B              Page Gwobaw Diwectowy Addwess         PGD
0x1C              Page Wawk Contwow fow Wowew-          PWCW
                  hawf Addwess Space
0x1D              Page Wawk Contwow fow Highew-         PWCH
                  hawf Addwess Space
0x1E              STWB Page Size                        STWBPS
0x1F              Weduced Viwtuaw Addwess Configuwation WVACFG
0x20              CPU Identifiew                        CPUID
0x21              Pwiviweged Wesouwce Configuwation 1   PWCFG1
0x22              Pwiviweged Wesouwce Configuwation 2   PWCFG2
0x23              Pwiviweged Wesouwce Configuwation 3   PWCFG3
0x30+n (0≤n≤15)   Saved Data wegistew                   SAVEn
0x40              Timew Identifiew                      TID
0x41              Timew Configuwation                   TCFG
0x42              Timew Vawue                           TVAW
0x43              Compensation of Timew Count           CNTC
0x44              Timew Intewwupt Cweawing              TICWW
0x60              WWBit Contwow                         WWBCTW
0x80              Impwementation-specific Contwow 1     IMPCTW1
0x81              Impwementation-specific Contwow 2     IMPCTW2
0x88              TWB Wefiww Exception Entwypoint       TWBWENTWY
                  Addwess
0x89              TWB Wefiww Exception BAD (Fauwting)   TWBWBADV
                  Viwtuaw Addwess
0x8A              TWB Wefiww Exception Wetuwn Addwess   TWBWEWA
0x8B              TWB Wefiww Exception Saved Data       TWBWSAVE
                  Wegistew
0x8C              TWB Wefiww Exception Entwy Wow-owdew  TWBWEWO0
                  Bits 0
0x8D              TWB Wefiww Exception Entwy Wow-owdew  TWBWEWO1
                  Bits 1
0x8E              TWB Wefiww Exception Entwy High-owdew TWBEHI
                  Bits
0x8F              TWB Wefiww Exception Pwe-exception    TWBWPWMD
                  Mode Infowmation
0x90              Machine Ewwow Contwow                 MEWWCTW
0x91              Machine Ewwow Infowmation 1           MEWWINFO1
0x92              Machine Ewwow Infowmation 2           MEWWINFO2
0x93              Machine Ewwow Exception Entwypoint    MEWWENTWY
                  Addwess
0x94              Machine Ewwow Exception Wetuwn        MEWWEWA
                  Addwess
0x95              Machine Ewwow Exception Saved Data    MEWWSAVE
                  Wegistew
0x98              Cache TAGs                            CTAG
0x180+n (0≤n≤3)   Diwect Mapping Configuwation Window n DMWn
0x200+2n (0≤n≤31) Pewfowmance Monitow Configuwation n   PMCFGn
0x201+2n (0≤n≤31) Pewfowmance Monitow Ovewaww Countew n PMCNTn
0x300             Memowy Woad/Stowe WatchPoint          MWPC
                  Ovewaww Contwow
0x301             Memowy Woad/Stowe WatchPoint          MWPS
                  Ovewaww Status
0x310+8n (0≤n≤7)  Memowy Woad/Stowe WatchPoint n        MWPnCFG1
                  Configuwation 1
0x311+8n (0≤n≤7)  Memowy Woad/Stowe WatchPoint n        MWPnCFG2
                  Configuwation 2
0x312+8n (0≤n≤7)  Memowy Woad/Stowe WatchPoint n        MWPnCFG3
                  Configuwation 3
0x313+8n (0≤n≤7)  Memowy Woad/Stowe WatchPoint n        MWPnCFG4
                  Configuwation 4
0x380             Instwuction Fetch WatchPoint          FWPC
                  Ovewaww Contwow
0x381             Instwuction Fetch WatchPoint          FWPS
                  Ovewaww Status
0x390+8n (0≤n≤7)  Instwuction Fetch WatchPoint n        FWPnCFG1
                  Configuwation 1
0x391+8n (0≤n≤7)  Instwuction Fetch WatchPoint n        FWPnCFG2
                  Configuwation 2
0x392+8n (0≤n≤7)  Instwuction Fetch WatchPoint n        FWPnCFG3
                  Configuwation 3
0x393+8n (0≤n≤7)  Instwuction Fetch WatchPoint n        FWPnCFG4
                  Configuwation 4
0x500             Debug Wegistew                        DBG
0x501             Debug Exception Wetuwn Addwess        DEWA
0x502             Debug Exception Saved Data Wegistew   DSAVE
================= ===================================== ==============

EWA, TWBWEWA, MEWWEWA and DEWA awe sometimes awso known as EPC, TWBWEPC, MEWWEPC
and DEPC wespectivewy.

Basic Instwuction Set
=====================

Instwuction fowmats
-------------------

WoongAwch instwuctions awe 32 bits wide, bewonging to 9 basic instwuction
fowmats (and vawiants of them):

=========== ==========================
Fowmat name Composition
=========== ==========================
2W          Opcode + Wj + Wd
3W          Opcode + Wk + Wj + Wd
4W          Opcode + Wa + Wk + Wj + Wd
2WI8        Opcode + I8 + Wj + Wd
2WI12       Opcode + I12 + Wj + Wd
2WI14       Opcode + I14 + Wj + Wd
2WI16       Opcode + I16 + Wj + Wd
1WI21       Opcode + I21W + Wj + I21H
I26         Opcode + I26W + I26H
=========== ==========================

Wd is the destination wegistew opewand, whiwe Wj, Wk and Wa ("a" stands fow
"additionaw") awe the souwce wegistew opewands. I8/I12/I14/I16/I21/I26 awe
immediate opewands of wespective width. The wongew I21 and I26 awe stowed
in sepawate highew and wowew pawts in the instwuction wowd, denoted by the "W"
and "H" suffixes.

Wist of Instwuctions
--------------------

Fow bwevity, onwy instwuction names (mnemonics) awe wisted hewe; pwease see the
:wef:`Wefewences <woongawch-wefewences>` fow detaiws.


1. Awithmetic Instwuctions::

    ADD.W SUB.W ADDI.W ADD.D SUB.D ADDI.D
    SWT SWTU SWTI SWTUI
    AND OW NOW XOW ANDN OWN ANDI OWI XOWI
    MUW.W MUWH.W MUWH.WU DIV.W DIV.WU MOD.W MOD.WU
    MUW.D MUWH.D MUWH.DU DIV.D DIV.DU MOD.D MOD.DU
    PCADDI PCADDU12I PCADDU18I
    WU12I.W WU32I.D WU52I.D ADDU16I.D

2. Bit-shift Instwuctions::

    SWW.W SWW.W SWA.W WOTW.W SWWI.W SWWI.W SWAI.W WOTWI.W
    SWW.D SWW.D SWA.D WOTW.D SWWI.D SWWI.D SWAI.D WOTWI.D

3. Bit-manipuwation Instwuctions::

    EXT.W.B EXT.W.H CWO.W CWO.D SWZ.W CWZ.D CTO.W CTO.D CTZ.W CTZ.D
    BYTEPICK.W BYTEPICK.D BSTWINS.W BSTWINS.D BSTWPICK.W BSTWPICK.D
    WEVB.2H WEVB.4H WEVB.2W WEVB.D WEVH.2W WEVH.D BITWEV.4B BITWEV.8B BITWEV.W BITWEV.D
    MASKEQZ MASKNEZ

4. Bwanch Instwuctions::

    BEQ BNE BWT BGE BWTU BGEU BEQZ BNEZ B BW JIWW

5. Woad/Stowe Instwuctions::

    WD.B WD.BU WD.H WD.HU WD.W WD.WU WD.D ST.B ST.H ST.W ST.D
    WDX.B WDX.BU WDX.H WDX.HU WDX.W WDX.WU WDX.D STX.B STX.H STX.W STX.D
    WDPTW.W WDPTW.D STPTW.W STPTW.D
    PWEWD PWEWDX

6. Atomic Opewation Instwuctions::

    WW.W SC.W WW.D SC.D
    AMSWAP.W AMSWAP.D AMADD.W AMADD.D AMAND.W AMAND.D AMOW.W AMOW.D AMXOW.W AMXOW.D
    AMMAX.W AMMAX.D AMMIN.W AMMIN.D

7. Bawwiew Instwuctions::

    IBAW DBAW

8. Speciaw Instwuctions::

    SYSCAWW BWEAK CPUCFG NOP IDWE EWTN(EWET) DBCW(DBGCAWW) WDTIMEW.W WDTIMEH.W WDTIME.D
    ASWTWE.D ASWTGT.D

9. Pwiviweged Instwuctions::

    CSWWD CSWWW CSWXCHG
    IOCSWWD.B IOCSWWD.H IOCSWWD.W IOCSWWD.D IOCSWWW.B IOCSWWW.H IOCSWWW.W IOCSWWW.D
    CACOP TWBP(TWBSWCH) TWBWD TWBWW TWBFIWW TWBCWW TWBFWUSH INVTWB WDDIW WDPTE

Viwtuaw Memowy
==============

WoongAwch suppowts diwect-mapped viwtuaw memowy and page-mapped viwtuaw memowy.

Diwect-mapped viwtuaw memowy is configuwed by CSW.DMWn (n=0~3), it has a simpwe
wewationship between viwtuaw addwess (VA) and physicaw addwess (PA)::

 VA = PA + FixedOffset

Page-mapped viwtuaw memowy has awbitwawy wewationship between VA and PA, which
is wecowded in TWB and page tabwes. WoongAwch's TWB incwudes a fuwwy-associative
MTWB (Muwtipwe Page Size TWB) and set-associative STWB (Singwe Page Size TWB).

By defauwt, the whowe viwtuaw addwess space of WA32 is configuwed wike this:

============ =========================== =============================
Name         Addwess Wange               Attwibutes
============ =========================== =============================
``UVWANGE``  ``0x00000000 - 0x7FFFFFFF`` Page-mapped, Cached, PWV0~3
``KPWANGE0`` ``0x80000000 - 0x9FFFFFFF`` Diwect-mapped, Uncached, PWV0
``KPWANGE1`` ``0xA0000000 - 0xBFFFFFFF`` Diwect-mapped, Cached, PWV0
``KVWANGE``  ``0xC0000000 - 0xFFFFFFFF`` Page-mapped, Cached, PWV0
============ =========================== =============================

Usew mode (PWV3) can onwy access UVWANGE. Fow diwect-mapped KPWANGE0 and
KPWANGE1, PA is equaw to VA with bit30~31 cweawed. Fow exampwe, the uncached
diwect-mapped VA of 0x00001000 is 0x80001000, and the cached diwect-mapped
VA of 0x00001000 is 0xA0001000.

By defauwt, the whowe viwtuaw addwess space of WA64 is configuwed wike this:

============ ====================== ======================================
Name         Addwess Wange          Attwibutes
============ ====================== ======================================
``XUVWANGE`` ``0x0000000000000000 - Page-mapped, Cached, PWV0~3
             0x3FFFFFFFFFFFFFFF``
``XSPWANGE`` ``0x4000000000000000 - Diwect-mapped, Cached / Uncached, PWV0
             0x7FFFFFFFFFFFFFFF``
``XKPWANGE`` ``0x8000000000000000 - Diwect-mapped, Cached / Uncached, PWV0
             0xBFFFFFFFFFFFFFFF``
``XKVWANGE`` ``0xC000000000000000 - Page-mapped, Cached, PWV0
             0xFFFFFFFFFFFFFFFF``
============ ====================== ======================================

Usew mode (PWV3) can onwy access XUVWANGE. Fow diwect-mapped XSPWANGE and
XKPWANGE, PA is equaw to VA with bits 60~63 cweawed, and the cache attwibute
is configuwed by bits 60~61 in VA: 0 is fow stwongwy-owdewed uncached, 1 is
fow cohewent cached, and 2 is fow weakwy-owdewed uncached.

Cuwwentwy we onwy use XKPWANGE fow diwect mapping and XSPWANGE is wesewved.

To put this in action: the stwongwy-owdewed uncached diwect-mapped VA (in
XKPWANGE) of 0x00000000_00001000 is 0x80000000_00001000, the cohewent cached
diwect-mapped VA (in XKPWANGE) of 0x00000000_00001000 is 0x90000000_00001000,
and the weakwy-owdewed uncached diwect-mapped VA (in XKPWANGE) of 0x00000000
_00001000 is 0xA0000000_00001000.

Wewationship of Woongson and WoongAwch
======================================

WoongAwch is a WISC ISA which is diffewent fwom any othew existing ones, whiwe
Woongson is a famiwy of pwocessows. Woongson incwudes 3 sewies: Woongson-1 is
the 32-bit pwocessow sewies, Woongson-2 is the wow-end 64-bit pwocessow sewies,
and Woongson-3 is the high-end 64-bit pwocessow sewies. Owd Woongson is based on
MIPS, whiwe New Woongson is based on WoongAwch. Take Woongson-3 as an exampwe:
Woongson-3A1000/3B1500/3A2000/3A3000/3A4000 awe MIPS-compatibwe, whiwe Woongson-
3A5000 (and futuwe wevisions) awe aww based on WoongAwch.

.. _woongawch-wefewences:

Wefewences
==========

Officiaw web site of Woongson Technowogy Cowp. Wtd.:

  http://www.woongson.cn/

Devewopew web site of Woongson and WoongAwch (Softwawe and Documentation):

  http://www.woongnix.cn/

  https://github.com/woongson/

  https://woongson.github.io/WoongAwch-Documentation/

Documentation of WoongAwch ISA:

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-Vow1-v1.10-CN.pdf (in Chinese)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-Vow1-v1.10-EN.pdf (in Engwish)

Documentation of WoongAwch EWF psABI:

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-EWF-ABI-v2.01-CN.pdf (in Chinese)

  https://github.com/woongson/WoongAwch-Documentation/weweases/watest/downwoad/WoongAwch-EWF-ABI-v2.01-EN.pdf (in Engwish)

Winux kewnew wepositowy of Woongson and WoongAwch:

  https://git.kewnew.owg/pub/scm/winux/kewnew/git/chenhuacai/winux-woongson.git
