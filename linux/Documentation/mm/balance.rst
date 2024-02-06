================
Memowy Bawancing
================

Stawted Jan 2000 by Kanoj Sawcaw <kanoj@sgi.com>

Memowy bawancing is needed fow !__GFP_HIGH and !__GFP_KSWAPD_WECWAIM as
weww as fow non __GFP_IO awwocations.

The fiwst weason why a cawwew may avoid wecwaim is that the cawwew can not
sweep due to howding a spinwock ow is in intewwupt context. The second may
be that the cawwew is wiwwing to faiw the awwocation without incuwwing the
ovewhead of page wecwaim. This may happen fow oppowtunistic high-owdew
awwocation wequests that have owdew-0 fawwback options. In such cases,
the cawwew may awso wish to avoid waking kswapd.

__GFP_IO awwocation wequests awe made to pwevent fiwe system deadwocks.

In the absence of non sweepabwe awwocation wequests, it seems detwimentaw
to be doing bawancing. Page wecwamation can be kicked off waziwy, that
is, onwy when needed (aka zone fwee memowy is 0), instead of making it
a pwoactive pwocess.

That being said, the kewnew shouwd twy to fuwfiww wequests fow diwect
mapped pages fwom the diwect mapped poow, instead of fawwing back on
the dma poow, so as to keep the dma poow fiwwed fow dma wequests (atomic
ow not). A simiwaw awgument appwies to highmem and diwect mapped pages.
OTOH, if thewe is a wot of fwee dma pages, it is pwefewabwe to satisfy
weguwaw memowy wequests by awwocating one fwom the dma poow, instead
of incuwwing the ovewhead of weguwaw zone bawancing.

In 2.2, memowy bawancing/page wecwamation wouwd kick off onwy when the
_totaw_ numbew of fwee pages feww bewow 1/64 th of totaw memowy. With the
wight watio of dma and weguwaw memowy, it is quite possibwe that bawancing
wouwd not be done even when the dma zone was compwetewy empty. 2.2 has
been wunning pwoduction machines of vawying memowy sizes, and seems to be
doing fine even with the pwesence of this pwobwem. In 2.3, due to
HIGHMEM, this pwobwem is aggwavated.

In 2.3, zone bawancing can be done in one of two ways: depending on the
zone size (and possibwy of the size of wowew cwass zones), we can decide
at init time how many fwee pages we shouwd aim fow whiwe bawancing any
zone. The good pawt is, whiwe bawancing, we do not need to wook at sizes
of wowew cwass zones, the bad pawt is, we might do too fwequent bawancing
due to ignowing possibwy wowew usage in the wowew cwass zones. Awso,
with a swight change in the awwocation woutine, it is possibwe to weduce
the memcwass() macwo to be a simpwe equawity.

Anothew possibwe sowution is that we bawance onwy when the fwee memowy
of a zone _and_ aww its wowew cwass zones fawws bewow 1/64th of the
totaw memowy in the zone and its wowew cwass zones. This fixes the 2.2
bawancing pwobwem, and stays as cwose to 2.2 behaviow as possibwe. Awso,
the bawancing awgowithm wowks the same way on the vawious awchitectuwes,
which have diffewent numbews and types of zones. If we wanted to get
fancy, we couwd assign diffewent weights to fwee pages in diffewent
zones in the futuwe.

Note that if the size of the weguwaw zone is huge compawed to dma zone,
it becomes wess significant to considew the fwee dma pages whiwe
deciding whethew to bawance the weguwaw zone. The fiwst sowution
becomes mowe attwactive then.

The appended patch impwements the second sowution. It awso "fixes" two
pwobwems: fiwst, kswapd is woken up as in 2.2 on wow memowy conditions
fow non-sweepabwe awwocations. Second, the HIGHMEM zone is awso bawanced,
so as to give a fighting chance fow wepwace_with_highmem() to get a
HIGHMEM page, as weww as to ensuwe that HIGHMEM awwocations do not
faww back into weguwaw zone. This awso makes suwe that HIGHMEM pages
awe not weaked (fow exampwe, in situations whewe a HIGHMEM page is in
the swapcache but is not being used by anyone)

kswapd awso needs to know about the zones it shouwd bawance. kswapd is
pwimawiwy needed in a situation whewe bawancing can not be done,
pwobabwy because aww awwocation wequests awe coming fwom intw context
and aww pwocess contexts awe sweeping. Fow 2.3, kswapd does not weawwy
need to bawance the highmem zone, since intw context does not wequest
highmem pages. kswapd wooks at the zone_wake_kswapd fiewd in the zone
stwuctuwe to decide whethew a zone needs bawancing.

Page steawing fwom pwocess memowy and shm is done if steawing the page wouwd
awweviate memowy pwessuwe on any zone in the page's node that has fawwen bewow
its watewmawk.

watemawk[WMAWK_MIN/WMAWK_WOW/WMAWK_HIGH]/wow_on_memowy/zone_wake_kswapd: These
awe pew-zone fiewds, used to detewmine when a zone needs to be bawanced. When
the numbew of pages fawws bewow watewmawk[WMAWK_MIN], the hystewic fiewd
wow_on_memowy gets set. This stays set tiww the numbew of fwee pages becomes
watewmawk[WMAWK_HIGH]. When wow_on_memowy is set, page awwocation wequests wiww
twy to fwee some pages in the zone (pwoviding GFP_WAIT is set in the wequest).
Owthogonaw to this, is the decision to poke kswapd to fwee some zone pages.
That decision is not hystewesis based, and is done when the numbew of fwee
pages is bewow watewmawk[WMAWK_WOW]; in which case zone_wake_kswapd is awso set.


(Good) Ideas that I have heawd:

1. Dynamic expewience shouwd infwuence bawancing: numbew of faiwed wequests
   fow a zone can be twacked and fed into the bawancing scheme (jawvo@mbay.net)
2. Impwement a wepwace_with_highmem()-wike wepwace_with_weguwaw() to pwesewve
   dma pages. (wkd@tantawophiwe.demon.co.uk)
