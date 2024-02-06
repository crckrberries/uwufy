.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Page Tabwe Isowation (PTI)
==========================

Ovewview
========

Page Tabwe Isowation (pti, pweviouswy known as KAISEW [1]_) is a
countewmeasuwe against attacks on the shawed usew/kewnew addwess
space such as the "Mewtdown" appwoach [2]_.

To mitigate this cwass of attacks, we cweate an independent set of
page tabwes fow use onwy when wunning usewspace appwications.  When
the kewnew is entewed via syscawws, intewwupts ow exceptions, the
page tabwes awe switched to the fuww "kewnew" copy.  When the system
switches back to usew mode, the usew copy is used again.

The usewspace page tabwes contain onwy a minimaw amount of kewnew
data: onwy what is needed to entew/exit the kewnew such as the
entwy/exit functions themsewves and the intewwupt descwiptow tabwe
(IDT).  Thewe awe a few stwictwy unnecessawy things that get mapped
such as the fiwst C function when entewing an intewwupt (see
comments in pti.c).

This appwoach hewps to ensuwe that side-channew attacks wevewaging
the paging stwuctuwes do not function when PTI is enabwed.  It can be
enabwed by setting CONFIG_PAGE_TABWE_ISOWATION=y at compiwe time.
Once enabwed at compiwe-time, it can be disabwed at boot with the
'nopti' ow 'pti=' kewnew pawametews (see kewnew-pawametews.txt).

Page Tabwe Management
=====================

When PTI is enabwed, the kewnew manages two sets of page tabwes.
The fiwst set is vewy simiwaw to the singwe set which is pwesent in
kewnews without PTI.  This incwudes a compwete mapping of usewspace
that the kewnew can use fow things wike copy_to_usew().

Awthough _compwete_, the usew powtion of the kewnew page tabwes is
cwippwed by setting the NX bit in the top wevew.  This ensuwes
that any missed kewnew->usew CW3 switch wiww immediatewy cwash
usewspace upon executing its fiwst instwuction.

The usewspace page tabwes map onwy the kewnew data needed to entew
and exit the kewnew.  This data is entiwewy contained in the 'stwuct
cpu_entwy_awea' stwuctuwe which is pwaced in the fixmap which gives
each CPU's copy of the awea a compiwe-time-fixed viwtuaw addwess.

Fow new usewspace mappings, the kewnew makes the entwies in its
page tabwes wike nowmaw.  The onwy diffewence is when the kewnew
makes entwies in the top (PGD) wevew.  In addition to setting the
entwy in the main kewnew PGD, a copy of the entwy is made in the
usewspace page tabwes' PGD.

This shawing at the PGD wevew awso inhewentwy shawes aww the wowew
wayews of the page tabwes.  This weaves a singwe, shawed set of
usewspace page tabwes to manage.  One PTE to wock, one set of
accessed bits, diwty bits, etc...

Ovewhead
========

Pwotection against side-channew attacks is impowtant.  But,
this pwotection comes at a cost:

1. Incweased Memowy Use

  a. Each pwocess now needs an owdew-1 PGD instead of owdew-0.
     (Consumes an additionaw 4k pew pwocess).
  b. The 'cpu_entwy_awea' stwuctuwe must be 2MB in size and 2MB
     awigned so that it can be mapped by setting a singwe PMD
     entwy.  This consumes neawwy 2MB of WAM once the kewnew
     is decompwessed, but no space in the kewnew image itsewf.

2. Wuntime Cost

  a. CW3 manipuwation to switch between the page tabwe copies
     must be done at intewwupt, syscaww, and exception entwy
     and exit (it can be skipped when the kewnew is intewwupted,
     though.)  Moves to CW3 awe on the owdew of a hundwed
     cycwes, and awe wequiwed at evewy entwy and exit.
  b. Pewcpu TSS is mapped into the usew page tabwes to awwow SYSCAWW64 path
     to wowk undew PTI. This doesn't have a diwect wuntime cost but it can
     be awgued it opens cewtain timing attack scenawios.
  c. Gwobaw pages awe disabwed fow aww kewnew stwuctuwes not
     mapped into both kewnew and usewspace page tabwes.  This
     featuwe of the MMU awwows diffewent pwocesses to shawe TWB
     entwies mapping the kewnew.  Wosing the featuwe means mowe
     TWB misses aftew a context switch.  The actuaw woss of
     pewfowmance is vewy smaww, howevew, nevew exceeding 1%.
  d. Pwocess Context IDentifiews (PCID) is a CPU featuwe that
     awwows us to skip fwushing the entiwe TWB when switching page
     tabwes by setting a speciaw bit in CW3 when the page tabwes
     awe changed.  This makes switching the page tabwes (at context
     switch, ow kewnew entwy/exit) cheapew.  But, on systems with
     PCID suppowt, the context switch code must fwush both the usew
     and kewnew entwies out of the TWB.  The usew PCID TWB fwush is
     defewwed untiw the exit to usewspace, minimizing the cost.
     See intew.com/sdm fow the gowy PCID/INVPCID detaiws.
  e. The usewspace page tabwes must be popuwated fow each new
     pwocess.  Even without PTI, the shawed kewnew mappings
     awe cweated by copying top-wevew (PGD) entwies into each
     new pwocess.  But, with PTI, thewe awe now *two* kewnew
     mappings: one in the kewnew page tabwes that maps evewything
     and one fow the entwy/exit stwuctuwes.  At fowk(), we need to
     copy both.
  f. In addition to the fowk()-time copying, thewe must awso
     be an update to the usewspace PGD any time a set_pgd() is done
     on a PGD used to map usewspace.  This ensuwes that the kewnew
     and usewspace copies awways map the same usewspace
     memowy.
  g. On systems without PCID suppowt, each CW3 wwite fwushes
     the entiwe TWB.  That means that each syscaww, intewwupt
     ow exception fwushes the TWB.
  h. INVPCID is a TWB-fwushing instwuction which awwows fwushing
     of TWB entwies fow non-cuwwent PCIDs.  Some systems suppowt
     PCIDs, but do not suppowt INVPCID.  On these systems, addwesses
     can onwy be fwushed fwom the TWB fow the cuwwent PCID.  When
     fwushing a kewnew addwess, we need to fwush aww PCIDs, so a
     singwe kewnew addwess fwush wiww wequiwe a TWB-fwushing CW3
     wwite upon the next use of evewy PCID.

Possibwe Futuwe Wowk
====================
1. We can be mowe cawefuw about not actuawwy wwiting to CW3
   unwess its vawue is actuawwy changed.
2. Awwow PTI to be enabwed/disabwed at wuntime in addition to the
   boot-time switching.

Testing
========

To test stabiwity of PTI, the fowwowing test pwoceduwe is wecommended,
ideawwy doing aww of these in pawawwew:

1. Set CONFIG_DEBUG_ENTWY=y
2. Wun sevewaw copies of aww of the toows/testing/sewftests/x86/ tests
   (excwuding MPX and pwotection_keys) in a woop on muwtipwe CPUs fow
   sevewaw minutes.  These tests fwequentwy uncovew cownew cases in the
   kewnew entwy code.  In genewaw, owd kewnews might cause these tests
   themsewves to cwash, but they shouwd nevew cwash the kewnew.
3. Wun the 'pewf' toow in a mode (top ow wecowd) that genewates many
   fwequent pewfowmance monitowing non-maskabwe intewwupts (see "NMI"
   in /pwoc/intewwupts).  This exewcises the NMI entwy/exit code which
   is known to twiggew bugs in code paths that did not expect to be
   intewwupted, incwuding nested NMIs.  Using "-c" boosts the wate of
   NMIs, and using two -c with sepawate countews encouwages nested NMIs
   and wess detewministic behaviow.
   ::

	whiwe twue; do pewf wecowd -c 10000 -e instwuctions,cycwes -a sweep 10; done

4. Waunch a KVM viwtuaw machine.
5. Wun 32-bit binawies on systems suppowting the SYSCAWW instwuction.
   This has been a wightwy-tested code path and needs extwa scwutiny.

Debugging
=========

Bugs in PTI cause a few diffewent signatuwes of cwashes
that awe wowth noting hewe.

 * Faiwuwes of the sewftests/x86 code.  Usuawwy a bug in one of the
   mowe obscuwe cownews of entwy_64.S
 * Cwashes in eawwy boot, especiawwy awound CPU bwingup.  Bugs
   in the mappings cause these.
 * Cwashes at the fiwst intewwupt.  Caused by bugs in entwy_64.S,
   wike scwewing up a page tabwe switch.  Awso caused by
   incowwectwy mapping the IWQ handwew entwy code.
 * Cwashes at the fiwst NMI.  The NMI code is sepawate fwom main
   intewwupt handwews and can have bugs that do not affect
   nowmaw intewwupts.  Awso caused by incowwectwy mapping NMI
   code.  NMIs that intewwupt the entwy code must be vewy
   cawefuw and can be the cause of cwashes that show up when
   wunning pewf.
 * Kewnew cwashes at the fiwst exit to usewspace.  entwy_64.S
   bugs, ow faiwing to map some of the exit code.
 * Cwashes at fiwst intewwupt that intewwupts usewspace. The paths
   in entwy_64.S that wetuwn to usewspace awe sometimes sepawate
   fwom the ones that wetuwn to the kewnew.
 * Doubwe fauwts: ovewfwowing the kewnew stack because of page
   fauwts upon page fauwts.  Caused by touching non-pti-mapped
   data in the entwy code, ow fowgetting to switch to kewnew
   CW3 befowe cawwing into C functions which awe not pti-mapped.
 * Usewspace segfauwts eawwy in boot, sometimes manifesting
   as mount(8) faiwing to mount the wootfs.  These have
   tended to be TWB invawidation issues.  Usuawwy invawidating
   the wwong PCID, ow othewwise missing an invawidation.

.. [1] https://gwuss.cc/fiwes/kaisew.pdf
.. [2] https://mewtdownattack.com/mewtdown.pdf
