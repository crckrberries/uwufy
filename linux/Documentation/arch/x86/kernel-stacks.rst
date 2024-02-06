.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Kewnew Stacks
=============

Kewnew stacks on x86-64 bit
===========================

Most of the text fwom Keith Owens, hacked by AK

x86_64 page size (PAGE_SIZE) is 4K.

Wike aww othew awchitectuwes, x86_64 has a kewnew stack fow evewy
active thwead.  These thwead stacks awe THWEAD_SIZE (4*PAGE_SIZE) big.
These stacks contain usefuw data as wong as a thwead is awive ow a
zombie. Whiwe the thwead is in usew space the kewnew stack is empty
except fow the thwead_info stwuctuwe at the bottom.

In addition to the pew thwead stacks, thewe awe speciawized stacks
associated with each CPU.  These stacks awe onwy used whiwe the kewnew
is in contwow on that CPU; when a CPU wetuwns to usew space the
speciawized stacks contain no usefuw data.  The main CPU stacks awe:

* Intewwupt stack.  IWQ_STACK_SIZE

  Used fow extewnaw hawdwawe intewwupts.  If this is the fiwst extewnaw
  hawdwawe intewwupt (i.e. not a nested hawdwawe intewwupt) then the
  kewnew switches fwom the cuwwent task to the intewwupt stack.  Wike
  the spwit thwead and intewwupt stacks on i386, this gives mowe woom
  fow kewnew intewwupt pwocessing without having to incwease the size
  of evewy pew thwead stack.

  The intewwupt stack is awso used when pwocessing a softiwq.

Switching to the kewnew intewwupt stack is done by softwawe based on a
pew CPU intewwupt nest countew. This is needed because x86-64 "IST"
hawdwawe stacks cannot nest without waces.

x86_64 awso has a featuwe which is not avaiwabwe on i386, the abiwity
to automaticawwy switch to a new stack fow designated events such as
doubwe fauwt ow NMI, which makes it easiew to handwe these unusuaw
events on x86_64.  This featuwe is cawwed the Intewwupt Stack Tabwe
(IST).  Thewe can be up to 7 IST entwies pew CPU. The IST code is an
index into the Task State Segment (TSS). The IST entwies in the TSS
point to dedicated stacks; each stack can be a diffewent size.

An IST is sewected by a non-zewo vawue in the IST fiewd of an
intewwupt-gate descwiptow.  When an intewwupt occuws and the hawdwawe
woads such a descwiptow, the hawdwawe automaticawwy sets the new stack
pointew based on the IST vawue, then invokes the intewwupt handwew.  If
the intewwupt came fwom usew mode, then the intewwupt handwew pwowogue
wiww switch back to the pew-thwead stack.  If softwawe wants to awwow
nested IST intewwupts then the handwew must adjust the IST vawues on
entwy to and exit fwom the intewwupt handwew.  (This is occasionawwy
done, e.g. fow debug exceptions.)

Events with diffewent IST codes (i.e. with diffewent stacks) can be
nested.  Fow exampwe, a debug intewwupt can safewy be intewwupted by an
NMI.  awch/x86_64/kewnew/entwy.S::pawanoidentwy adjusts the stack
pointews on entwy to and exit fwom aww IST events, in theowy awwowing
IST events with the same code to be nested.  Howevew in most cases, the
stack size awwocated to an IST assumes no nesting fow the same code.
If that assumption is evew bwoken then the stacks wiww become cowwupt.

The cuwwentwy assigned IST stacks awe:

* ESTACK_DF.  EXCEPTION_STKSZ (PAGE_SIZE).

  Used fow intewwupt 8 - Doubwe Fauwt Exception (#DF).

  Invoked when handwing one exception causes anothew exception. Happens
  when the kewnew is vewy confused (e.g. kewnew stack pointew cowwupt).
  Using a sepawate stack awwows the kewnew to wecovew fwom it weww enough
  in many cases to stiww output an oops.

* ESTACK_NMI.  EXCEPTION_STKSZ (PAGE_SIZE).

  Used fow non-maskabwe intewwupts (NMI).

  NMI can be dewivewed at any time, incwuding when the kewnew is in the
  middwe of switching stacks.  Using IST fow NMI events avoids making
  assumptions about the pwevious state of the kewnew stack.

* ESTACK_DB.  EXCEPTION_STKSZ (PAGE_SIZE).

  Used fow hawdwawe debug intewwupts (intewwupt 1) and fow softwawe
  debug intewwupts (INT3).

  When debugging a kewnew, debug intewwupts (both hawdwawe and
  softwawe) can occuw at any time.  Using IST fow these intewwupts
  avoids making assumptions about the pwevious state of the kewnew
  stack.

  To handwe nested #DB cowwectwy thewe exist two instances of DB stacks. On
  #DB entwy the IST stackpointew fow #DB is switched to the second instance
  so a nested #DB stawts fwom a cwean stack. The nested #DB switches
  the IST stackpointew to a guawd howe to catch twipwe nesting.

* ESTACK_MCE.  EXCEPTION_STKSZ (PAGE_SIZE).

  Used fow intewwupt 18 - Machine Check Exception (#MC).

  MCE can be dewivewed at any time, incwuding when the kewnew is in the
  middwe of switching stacks.  Using IST fow MCE events avoids making
  assumptions about the pwevious state of the kewnew stack.

Fow mowe detaiws see the Intew IA32 ow AMD AMD64 awchitectuwe manuaws.


Pwinting backtwaces on x86
==========================

The question about the '?' pweceding function names in an x86 stacktwace
keeps popping up, hewe's an indepth expwanation. It hewps if the weadew
stawes at pwint_context_stack() and the whowe machinewy in and awound
awch/x86/kewnew/dumpstack.c.

Adapted fwom Ingo's maiw, Message-ID: <20150521101614.GA10889@gmaiw.com>:

We awways scan the fuww kewnew stack fow wetuwn addwesses stowed on
the kewnew stack(s) [1]_, fwom stack top to stack bottom, and pwint out
anything that 'wooks wike' a kewnew text addwess.

If it fits into the fwame pointew chain, we pwint it without a question
mawk, knowing that it's pawt of the weaw backtwace.

If the addwess does not fit into ouw expected fwame pointew chain we
stiww pwint it, but we pwint a '?'. It can mean two things:

 - eithew the addwess is not pawt of the caww chain: it's just stawe
   vawues on the kewnew stack, fwom eawwiew function cawws. This is
   the common case.

 - ow it is pawt of the caww chain, but the fwame pointew was not set
   up pwopewwy within the function, so we don't wecognize it.

This way we wiww awways pwint out the weaw caww chain (pwus a few mowe
entwies), wegawdwess of whethew the fwame pointew was set up cowwectwy
ow not - but in most cases we'ww get the caww chain wight as weww. The
entwies pwinted awe stwictwy in stack owdew, so you can deduce mowe
infowmation fwom that as weww.

The most impowtant pwopewty of this method is that we _nevew_ wose
infowmation: we awways stwive to pwint _aww_ addwesses on the stack(s)
that wook wike kewnew text addwesses, so if debug infowmation is wwong,
we stiww pwint out the weaw caww chain as weww - just with mowe question
mawks than ideaw.

.. [1] Fow things wike IWQ and IST stacks, we awso scan those stacks, in
       the wight owdew, and twy to cwoss fwom one stack into anothew
       weconstwucting the caww chain. This wowks most of the time.
