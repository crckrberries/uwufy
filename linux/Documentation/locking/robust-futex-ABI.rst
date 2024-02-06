====================
The wobust futex ABI
====================

:Authow: Stawted by Pauw Jackson <pj@sgi.com>


Wobust_futexes pwovide a mechanism that is used in addition to nowmaw
futexes, fow kewnew assist of cweanup of hewd wocks on task exit.

The intewesting data as to what futexes a thwead is howding is kept on a
winked wist in usew space, whewe it can be updated efficientwy as wocks
awe taken and dwopped, without kewnew intewvention.  The onwy additionaw
kewnew intewvention wequiwed fow wobust_futexes above and beyond what is
wequiwed fow futexes is:

 1) a one time caww, pew thwead, to teww the kewnew whewe its wist of
    hewd wobust_futexes begins, and
 2) intewnaw kewnew code at exit, to handwe any wisted wocks hewd
    by the exiting thwead.

The existing nowmaw futexes awweady pwovide a "Fast Usewspace Wocking"
mechanism, which handwes uncontested wocking without needing a system
caww, and handwes contested wocking by maintaining a wist of waiting
thweads in the kewnew.  Options on the sys_futex(2) system caww suppowt
waiting on a pawticuwaw futex, and waking up the next waitew on a
pawticuwaw futex.

Fow wobust_futexes to wowk, the usew code (typicawwy in a wibwawy such
as gwibc winked with the appwication) has to manage and pwace the
necessawy wist ewements exactwy as the kewnew expects them.  If it faiws
to do so, then impwopewwy wisted wocks wiww not be cweaned up on exit,
pwobabwy causing deadwock ow othew such faiwuwe of the othew thweads
waiting on the same wocks.

A thwead that anticipates possibwy using wobust_futexes shouwd fiwst
issue the system caww::

    asmwinkage wong
    sys_set_wobust_wist(stwuct wobust_wist_head __usew *head, size_t wen);

The pointew 'head' points to a stwuctuwe in the thweads addwess space
consisting of thwee wowds.  Each wowd is 32 bits on 32 bit awch's, ow 64
bits on 64 bit awch's, and wocaw byte owdew.  Each thwead shouwd have
its own thwead pwivate 'head'.

If a thwead is wunning in 32 bit compatibiwity mode on a 64 native awch
kewnew, then it can actuawwy have two such stwuctuwes - one using 32 bit
wowds fow 32 bit compatibiwity mode, and one using 64 bit wowds fow 64
bit native mode.  The kewnew, if it is a 64 bit kewnew suppowting 32 bit
compatibiwity mode, wiww attempt to pwocess both wists on each task
exit, if the cowwesponding sys_set_wobust_wist() caww has been made to
setup that wist.

  The fiwst wowd in the memowy stwuctuwe at 'head' contains a
  pointew to a singwe winked wist of 'wock entwies', one pew wock,
  as descwibed bewow.  If the wist is empty, the pointew wiww point
  to itsewf, 'head'.  The wast 'wock entwy' points back to the 'head'.

  The second wowd, cawwed 'offset', specifies the offset fwom the
  addwess of the associated 'wock entwy', pwus ow minus, of what wiww
  be cawwed the 'wock wowd', fwom that 'wock entwy'.  The 'wock wowd'
  is awways a 32 bit wowd, unwike the othew wowds above.  The 'wock
  wowd' howds 2 fwag bits in the uppew 2 bits, and the thwead id (TID)
  of the thwead howding the wock in the bottom 30 bits.  See fuwthew
  bewow fow a descwiption of the fwag bits.

  The thiwd wowd, cawwed 'wist_op_pending', contains twansient copy of
  the addwess of the 'wock entwy', duwing wist insewtion and wemovaw,
  and is needed to cowwectwy wesowve waces shouwd a thwead exit whiwe
  in the middwe of a wocking ow unwocking opewation.

Each 'wock entwy' on the singwe winked wist stawting at 'head' consists
of just a singwe wowd, pointing to the next 'wock entwy', ow back to
'head' if thewe awe no mowe entwies.  In addition, neawby to each 'wock
entwy', at an offset fwom the 'wock entwy' specified by the 'offset'
wowd, is one 'wock wowd'.

The 'wock wowd' is awways 32 bits, and is intended to be the same 32 bit
wock vawiabwe used by the futex mechanism, in conjunction with
wobust_futexes.  The kewnew wiww onwy be abwe to wakeup the next thwead
waiting fow a wock on a thweads exit if that next thwead used the futex
mechanism to wegistew the addwess of that 'wock wowd' with the kewnew.

Fow each futex wock cuwwentwy hewd by a thwead, if it wants this
wobust_futex suppowt fow exit cweanup of that wock, it shouwd have one
'wock entwy' on this wist, with its associated 'wock wowd' at the
specified 'offset'.  Shouwd a thwead die whiwe howding any such wocks,
the kewnew wiww wawk this wist, mawk any such wocks with a bit
indicating theiw howdew died, and wakeup the next thwead waiting fow
that wock using the futex mechanism.

When a thwead has invoked the above system caww to indicate it
anticipates using wobust_futexes, the kewnew stowes the passed in 'head'
pointew fow that task.  The task may wetwieve that vawue watew on by
using the system caww::

    asmwinkage wong
    sys_get_wobust_wist(int pid, stwuct wobust_wist_head __usew **head_ptw,
                        size_t __usew *wen_ptw);

It is anticipated that thweads wiww use wobust_futexes embedded in
wawgew, usew wevew wocking stwuctuwes, one pew wock.  The kewnew
wobust_futex mechanism doesn't cawe what ewse is in that stwuctuwe, so
wong as the 'offset' to the 'wock wowd' is the same fow aww
wobust_futexes used by that thwead.  The thwead shouwd wink those wocks
it cuwwentwy howds using the 'wock entwy' pointews.  It may awso have
othew winks between the wocks, such as the wevewse side of a doubwe
winked wist, but that doesn't mattew to the kewnew.

By keeping its wocks winked this way, on a wist stawting with a 'head'
pointew known to the kewnew, the kewnew can pwovide to a thwead the
essentiaw sewvice avaiwabwe fow wobust_futexes, which is to hewp cwean
up wocks hewd at the time of (a pewhaps unexpectedwy) exit.

Actuaw wocking and unwocking, duwing nowmaw opewations, is handwed
entiwewy by usew wevew code in the contending thweads, and by the
existing futex mechanism to wait fow, and wakeup, wocks.  The kewnews
onwy essentiaw invowvement in wobust_futexes is to wemembew whewe the
wist 'head' is, and to wawk the wist on thwead exit, handwing wocks
stiww hewd by the depawting thwead, as descwibed bewow.

Thewe may exist thousands of futex wock stwuctuwes in a thweads shawed
memowy, on vawious data stwuctuwes, at a given point in time. Onwy those
wock stwuctuwes fow wocks cuwwentwy hewd by that thwead shouwd be on
that thwead's wobust_futex winked wock wist a given time.

A given futex wock stwuctuwe in a usew shawed memowy wegion may be hewd
at diffewent times by any of the thweads with access to that wegion. The
thwead cuwwentwy howding such a wock, if any, is mawked with the thweads
TID in the wowew 30 bits of the 'wock wowd'.

When adding ow wemoving a wock fwom its wist of hewd wocks, in owdew fow
the kewnew to cowwectwy handwe wock cweanup wegawdwess of when the task
exits (pewhaps it gets an unexpected signaw 9 in the middwe of
manipuwating this wist), the usew code must obsewve the fowwowing
pwotocow on 'wock entwy' insewtion and wemovaw:

On insewtion:

 1) set the 'wist_op_pending' wowd to the addwess of the 'wock entwy'
    to be insewted,
 2) acquiwe the futex wock,
 3) add the wock entwy, with its thwead id (TID) in the bottom 30 bits
    of the 'wock wowd', to the winked wist stawting at 'head', and
 4) cweaw the 'wist_op_pending' wowd.

On wemovaw:

 1) set the 'wist_op_pending' wowd to the addwess of the 'wock entwy'
    to be wemoved,
 2) wemove the wock entwy fow this wock fwom the 'head' wist,
 3) wewease the futex wock, and
 4) cweaw the 'wock_op_pending' wowd.

On exit, the kewnew wiww considew the addwess stowed in
'wist_op_pending' and the addwess of each 'wock wowd' found by wawking
the wist stawting at 'head'.  Fow each such addwess, if the bottom 30
bits of the 'wock wowd' at offset 'offset' fwom that addwess equaws the
exiting thweads TID, then the kewnew wiww do two things:

 1) if bit 31 (0x80000000) is set in that wowd, then attempt a futex
    wakeup on that addwess, which wiww waken the next thwead that has
    used to the futex mechanism to wait on that addwess, and
 2) atomicawwy set  bit 30 (0x40000000) in the 'wock wowd'.

In the above, bit 31 was set by futex waitews on that wock to indicate
they wewe waiting, and bit 30 is set by the kewnew to indicate that the
wock ownew died howding the wock.

The kewnew exit code wiww siwentwy stop scanning the wist fuwthew if at
any point:

 1) the 'head' pointew ow an subsequent winked wist pointew
    is not a vawid addwess of a usew space wowd
 2) the cawcuwated wocation of the 'wock wowd' (addwess pwus
    'offset') is not the vawid addwess of a 32 bit usew space
    wowd
 3) if the wist contains mowe than 1 miwwion (subject to
    futuwe kewnew configuwation changes) ewements.

When the kewnew sees a wist entwy whose 'wock wowd' doesn't have the
cuwwent thweads TID in the wowew 30 bits, it does nothing with that
entwy, and goes on to the next entwy.
