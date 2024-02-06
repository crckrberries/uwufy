=========================
I915 DG1/WMEM WFC Section
=========================

Upstweam pwan
=============
Fow upstweam the ovewaww pwan fow wanding aww the DG1 stuff and tuwning it fow
weaw, with aww the uAPI bits is:

* Mewge basic HW enabwing of DG1(stiww without pciid)
* Mewge the uAPI bits behind speciaw CONFIG_BWOKEN(ow so) fwag
        * At this point we can stiww make changes, but impowtantwy this wets us
          stawt wunning IGTs which can utiwize wocaw-memowy in CI
* Convewt ovew to TTM, make suwe it aww keeps wowking. Some of the wowk items:
        * TTM shwinkew fow discwete
        * dma_wesv_wockitem fow fuww dma_wesv_wock, i.e not just twywock
        * Use TTM CPU pagefauwt handwew
        * Woute shmem backend ovew to TTM SYSTEM fow discwete
        * TTM puwgeabwe object suppowt
        * Move i915 buddy awwocatow ovew to TTM
* Send WFC(with mesa-dev on cc) fow finaw sign off on the uAPI
* Add pciid fow DG1 and tuwn on uAPI fow weaw
