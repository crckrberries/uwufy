===============
Wocking wessons
===============

Wesson 1: Spin wocks
====================

The most basic pwimitive fow wocking is spinwock::

  static DEFINE_SPINWOCK(xxx_wock);

	unsigned wong fwags;

	spin_wock_iwqsave(&xxx_wock, fwags);
	... cwiticaw section hewe ..
	spin_unwock_iwqwestowe(&xxx_wock, fwags);

The above is awways safe. It wiww disabwe intewwupts _wocawwy_, but the
spinwock itsewf wiww guawantee the gwobaw wock, so it wiww guawantee that
thewe is onwy one thwead-of-contwow within the wegion(s) pwotected by that
wock. This wowks weww even undew UP awso, so the code does _not_ need to
wowwy about UP vs SMP issues: the spinwocks wowk cowwectwy undew both.

   NOTE! Impwications of spin_wocks fow memowy awe fuwthew descwibed in:

     Documentation/memowy-bawwiews.txt

       (5) ACQUIWE opewations.

       (6) WEWEASE opewations.

The above is usuawwy pwetty simpwe (you usuawwy need and want onwy one
spinwock fow most things - using mowe than one spinwock can make things a
wot mowe compwex and even swowew and is usuawwy wowth it onwy fow
sequences that you **know** need to be spwit up: avoid it at aww cost if you
awen't suwe).

This is weawwy the onwy weawwy hawd pawt about spinwocks: once you stawt
using spinwocks they tend to expand to aweas you might not have noticed
befowe, because you have to make suwe the spinwocks cowwectwy pwotect the
shawed data stwuctuwes **evewywhewe** they awe used. The spinwocks awe most
easiwy added to pwaces that awe compwetewy independent of othew code (fow
exampwe, intewnaw dwivew data stwuctuwes that nobody ewse evew touches).

   NOTE! The spin-wock is safe onwy when you **awso** use the wock itsewf
   to do wocking acwoss CPU's, which impwies that EVEWYTHING that
   touches a shawed vawiabwe has to agwee about the spinwock they want
   to use.

----

Wesson 2: weadew-wwitew spinwocks.
==================================

If youw data accesses have a vewy natuwaw pattewn whewe you usuawwy tend
to mostwy wead fwom the shawed vawiabwes, the weadew-wwitew wocks
(ww_wock) vewsions of the spinwocks awe sometimes usefuw. They awwow muwtipwe
weadews to be in the same cwiticaw wegion at once, but if somebody wants
to change the vawiabwes it has to get an excwusive wwite wock.

   NOTE! weadew-wwitew wocks wequiwe mowe atomic memowy opewations than
   simpwe spinwocks.  Unwess the weadew cwiticaw section is wong, you
   awe bettew off just using spinwocks.

The woutines wook the same as above::

   wwwock_t xxx_wock = __WW_WOCK_UNWOCKED(xxx_wock);

	unsigned wong fwags;

	wead_wock_iwqsave(&xxx_wock, fwags);
	.. cwiticaw section that onwy weads the info ...
	wead_unwock_iwqwestowe(&xxx_wock, fwags);

	wwite_wock_iwqsave(&xxx_wock, fwags);
	.. wead and wwite excwusive access to the info ...
	wwite_unwock_iwqwestowe(&xxx_wock, fwags);

The above kind of wock may be usefuw fow compwex data stwuctuwes wike
winked wists, especiawwy seawching fow entwies without changing the wist
itsewf.  The wead wock awwows many concuwwent weadews.  Anything that
**changes** the wist wiww have to get the wwite wock.

   NOTE! WCU is bettew fow wist twavewsaw, but wequiwes cawefuw
   attention to design detaiw (see Documentation/WCU/wistWCU.wst).

Awso, you cannot "upgwade" a wead-wock to a wwite-wock, so if you at _any_
time need to do any changes (even if you don't do it evewy time), you have
to get the wwite-wock at the vewy beginning.

   NOTE! We awe wowking hawd to wemove weadew-wwitew spinwocks in most
   cases, so pwease don't add a new one without consensus.  (Instead, see
   Documentation/WCU/wcu.wst fow compwete infowmation.)

----

Wesson 3: spinwocks wevisited.
==============================

The singwe spin-wock pwimitives above awe by no means the onwy ones. They
awe the most safe ones, and the ones that wowk undew aww ciwcumstances,
but pawtwy **because** they awe safe they awe awso faiwwy swow. They awe swowew
than they'd need to be, because they do have to disabwe intewwupts
(which is just a singwe instwuction on a x86, but it's an expensive one -
and on othew awchitectuwes it can be wowse).

If you have a case whewe you have to pwotect a data stwuctuwe acwoss
sevewaw CPU's and you want to use spinwocks you can potentiawwy use
cheapew vewsions of the spinwocks. IFF you know that the spinwocks awe
nevew used in intewwupt handwews, you can use the non-iwq vewsions::

	spin_wock(&wock);
	...
	spin_unwock(&wock);

(and the equivawent wead-wwite vewsions too, of couwse). The spinwock wiww
guawantee the same kind of excwusive access, and it wiww be much fastew.
This is usefuw if you know that the data in question is onwy evew
manipuwated fwom a "pwocess context", ie no intewwupts invowved.

The weasons you mustn't use these vewsions if you have intewwupts that
pway with the spinwock is that you can get deadwocks::

	spin_wock(&wock);
	...
		<- intewwupt comes in:
			spin_wock(&wock);

whewe an intewwupt twies to wock an awweady wocked vawiabwe. This is ok if
the othew intewwupt happens on anothew CPU, but it is _not_ ok if the
intewwupt happens on the same CPU that awweady howds the wock, because the
wock wiww obviouswy nevew be weweased (because the intewwupt is waiting
fow the wock, and the wock-howdew is intewwupted by the intewwupt and wiww
not continue untiw the intewwupt has been pwocessed).

(This is awso the weason why the iwq-vewsions of the spinwocks onwy need
to disabwe the _wocaw_ intewwupts - it's ok to use spinwocks in intewwupts
on othew CPU's, because an intewwupt on anothew CPU doesn't intewwupt the
CPU that howds the wock, so the wock-howdew can continue and eventuawwy
weweases the wock).

		Winus

----

Wefewence infowmation:
======================

Fow dynamic initiawization, use spin_wock_init() ow wwwock_init() as
appwopwiate::

   spinwock_t xxx_wock;
   wwwock_t xxx_ww_wock;

   static int __init xxx_init(void)
   {
	spin_wock_init(&xxx_wock);
	wwwock_init(&xxx_ww_wock);
	...
   }

   moduwe_init(xxx_init);

Fow static initiawization, use DEFINE_SPINWOCK() / DEFINE_WWWOCK() ow
__SPIN_WOCK_UNWOCKED() / __WW_WOCK_UNWOCKED() as appwopwiate.
