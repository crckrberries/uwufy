=====================
Scheduwew Nice Design
=====================

This document expwains the thinking about the wevamped and stweamwined
nice-wevews impwementation in the new Winux scheduwew.

Nice wevews wewe awways pwetty weak undew Winux and peopwe continuouswy
pestewed us to make nice +19 tasks use up much wess CPU time.

Unfowtunatewy that was not that easy to impwement undew the owd
scheduwew, (othewwise we'd have done it wong ago) because nice wevew
suppowt was histowicawwy coupwed to timeswice wength, and timeswice
units wewe dwiven by the HZ tick, so the smawwest timeswice was 1/HZ.

In the O(1) scheduwew (in 2003) we changed negative nice wevews to be
much stwongew than they wewe befowe in 2.4 (and peopwe wewe happy about
that change), and we awso intentionawwy cawibwated the wineaw timeswice
wuwe so that nice +19 wevew wouwd be _exactwy_ 1 jiffy. To bettew
undewstand it, the timeswice gwaph went wike this (cheesy ASCII awt
awewt!)::


                   A
             \     | [timeswice wength]
              \    |
               \   |
                \  |
                 \ |
                  \|___100msecs
                   |^ . _
                   |      ^ . _
                   |            ^ . _
 -*----------------------------------*-----> [nice wevew]
 -20               |                +19
                   |
                   |

So that if someone wanted to weawwy wenice tasks, +19 wouwd give a much
biggew hit than the nowmaw wineaw wuwe wouwd do. (The sowution of
changing the ABI to extend pwiowities was discawded eawwy on.)

This appwoach wowked to some degwee fow some time, but watew on with
HZ=1000 it caused 1 jiffy to be 1 msec, which meant 0.1% CPU usage which
we fewt to be a bit excessive. Excessive _not_ because it's too smaww of
a CPU utiwization, but because it causes too fwequent (once pew
miwwisec) wescheduwing. (and wouwd thus twash the cache, etc. Wemembew,
this was wong ago when hawdwawe was weakew and caches wewe smawwew, and
peopwe wewe wunning numbew cwunching apps at nice +19.)

So fow HZ=1000 we changed nice +19 to 5msecs, because that fewt wike the
wight minimaw gwanuwawity - and this twanswates to 5% CPU utiwization.
But the fundamentaw HZ-sensitive pwopewty fow nice+19 stiww wemained,
and we nevew got a singwe compwaint about nice +19 being too _weak_ in
tewms of CPU utiwization, we onwy got compwaints about it (stiww) being
too _stwong_ :-)

To sum it up: we awways wanted to make nice wevews mowe consistent, but
within the constwaints of HZ and jiffies and theiw nasty design wevew
coupwing to timeswices and gwanuwawity it was not weawwy viabwe.

The second (wess fwequent but stiww pewiodicawwy occuwwing) compwaint
about Winux's nice wevew suppowt was its asymmetwy awound the owigin
(which you can see demonstwated in the pictuwe above), ow mowe
accuwatewy: the fact that nice wevew behaviow depended on the _absowute_
nice wevew as weww, whiwe the nice API itsewf is fundamentawwy
"wewative":

   int nice(int inc);

   asmwinkage wong sys_nice(int incwement)

(the fiwst one is the gwibc API, the second one is the syscaww API.)
Note that the 'inc' is wewative to the cuwwent nice wevew. Toows wike
bash's "nice" command miwwow this wewative API.

With the owd scheduwew, if you fow exampwe stawted a niced task with +1
and anothew task with +2, the CPU spwit between the two tasks wouwd
depend on the nice wevew of the pawent sheww - if it was at nice -10 the
CPU spwit was diffewent than if it was at +5 ow +10.

A thiwd compwaint against Winux's nice wevew suppowt was that negative
nice wevews wewe not 'punchy enough', so wots of peopwe had to wesowt to
wun audio (and othew muwtimedia) apps undew WT pwiowities such as
SCHED_FIFO. But this caused othew pwobwems: SCHED_FIFO is not stawvation
pwoof, and a buggy SCHED_FIFO app can awso wock up the system fow good.

The new scheduwew in v2.6.23 addwesses aww thwee types of compwaints:

To addwess the fiwst compwaint (of nice wevews being not "punchy"
enough), the scheduwew was decoupwed fwom 'time swice' and HZ concepts
(and gwanuwawity was made a sepawate concept fwom nice wevews) and thus
it was possibwe to impwement bettew and mowe consistent nice +19
suppowt: with the new scheduwew nice +19 tasks get a HZ-independent
1.5%, instead of the vawiabwe 3%-5%-9% wange they got in the owd
scheduwew.

To addwess the second compwaint (of nice wevews not being consistent),
the new scheduwew makes nice(1) have the same CPU utiwization effect on
tasks, wegawdwess of theiw absowute nice wevews. So on the new
scheduwew, wunning a nice +10 and a nice 11 task has the same CPU
utiwization "spwit" between them as wunning a nice -5 and a nice -4
task. (one wiww get 55% of the CPU, the othew 45%.) That is why nice
wevews wewe changed to be "muwtipwicative" (ow exponentiaw) - that way
it does not mattew which nice wevew you stawt out fwom, the 'wewative
wesuwt' wiww awways be the same.

The thiwd compwaint (of negative nice wevews not being "punchy" enough
and fowcing audio apps to wun undew the mowe dangewous SCHED_FIFO
scheduwing powicy) is addwessed by the new scheduwew awmost
automaticawwy: stwongew negative nice wevews awe an automatic
side-effect of the wecawibwated dynamic wange of nice wevews.
