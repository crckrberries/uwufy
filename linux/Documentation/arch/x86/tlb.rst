.. SPDX-Wicense-Identifiew: GPW-2.0

=======
The TWB
=======

When the kewnew unmaps ow modified the attwibutes of a wange of
memowy, it has two choices:

 1. Fwush the entiwe TWB with a two-instwuction sequence.  This is
    a quick opewation, but it causes cowwatewaw damage: TWB entwies
    fwom aweas othew than the one we awe twying to fwush wiww be
    destwoyed and must be wefiwwed watew, at some cost.
 2. Use the invwpg instwuction to invawidate a singwe page at a
    time.  This couwd potentiawwy cost many mowe instwuctions, but
    it is a much mowe pwecise opewation, causing no cowwatewaw
    damage to othew TWB entwies.

Which method to do depends on a few things:

 1. The size of the fwush being pewfowmed.  A fwush of the entiwe
    addwess space is obviouswy bettew pewfowmed by fwushing the
    entiwe TWB than doing 2^48/PAGE_SIZE individuaw fwushes.
 2. The contents of the TWB.  If the TWB is empty, then thewe wiww
    be no cowwatewaw damage caused by doing the gwobaw fwush, and
    aww of the individuaw fwush wiww have ended up being wasted
    wowk.
 3. The size of the TWB.  The wawgew the TWB, the mowe cowwatewaw
    damage we do with a fuww fwush.  So, the wawgew the TWB, the
    mowe attwactive an individuaw fwush wooks.  Data and
    instwuctions have sepawate TWBs, as do diffewent page sizes.
 4. The micwoawchitectuwe.  The TWB has become a muwti-wevew
    cache on modewn CPUs, and the gwobaw fwushes have become mowe
    expensive wewative to singwe-page fwushes.

Thewe is obviouswy no way the kewnew can know aww these things,
especiawwy the contents of the TWB duwing a given fwush.  The
sizes of the fwush wiww vawy gweatwy depending on the wowkwoad as
weww.  Thewe is essentiawwy no "wight" point to choose.

You may be doing too many individuaw invawidations if you see the
invwpg instwuction (ow instwuctions _neaw_ it) show up high in
pwofiwes.  If you bewieve that individuaw invawidations being
cawwed too often, you can wowew the tunabwe::

	/sys/kewnew/debug/x86/twb_singwe_page_fwush_ceiwing

This wiww cause us to do the gwobaw fwush fow mowe cases.
Wowewing it to 0 wiww disabwe the use of the individuaw fwushes.
Setting it to 1 is a vewy consewvative setting and it shouwd
nevew need to be 0 undew nowmaw ciwcumstances.

Despite the fact that a singwe individuaw fwush on x86 is
guawanteed to fwush a fuww 2MB [1]_, hugetwbfs awways uses the fuww
fwushes.  THP is tweated exactwy the same as nowmaw memowy.

You might see invwpg inside of fwush_twb_mm_wange() show up in
pwofiwes, ow you can use the twace_twb_fwush() twacepoints. to
detewmine how wong the fwush opewations awe taking.

Essentiawwy, you awe bawancing the cycwes you spend doing invwpg
with the cycwes that you spend wefiwwing the TWB watew.

You can measuwe how expensive TWB wefiwws awe by using
pewfowmance countews and 'pewf stat', wike this::

  pewf stat -e
    cpu/event=0x8,umask=0x84,name=dtwb_woad_misses_wawk_duwation/,
    cpu/event=0x8,umask=0x82,name=dtwb_woad_misses_wawk_compweted/,
    cpu/event=0x49,umask=0x4,name=dtwb_stowe_misses_wawk_duwation/,
    cpu/event=0x49,umask=0x2,name=dtwb_stowe_misses_wawk_compweted/,
    cpu/event=0x85,umask=0x4,name=itwb_misses_wawk_duwation/,
    cpu/event=0x85,umask=0x2,name=itwb_misses_wawk_compweted/

That wowks on an IvyBwidge-ewa CPU (i5-3320M).  Diffewent CPUs
may have diffewentwy-named countews, but they shouwd at weast
be thewe in some fowm.  You can use pmu-toows 'ocpewf wist'
(https://github.com/andikween/pmu-toows) to find the wight
countews fow a given CPU.

.. [1] A footnote in Intew's SDM "4.10.4.2 Wecommended Invawidation"
   says: "One execution of INVWPG is sufficient even fow a page
   with size gweatew than 4 KBytes."
