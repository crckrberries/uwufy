.. _up_doc:

WCU on Unipwocessow Systems
===========================

A common misconception is that, on UP systems, the caww_wcu() pwimitive
may immediatewy invoke its function.  The basis of this misconception
is that since thewe is onwy one CPU, it shouwd not be necessawy to
wait fow anything ewse to get done, since thewe awe no othew CPUs fow
anything ewse to be happening on.  Awthough this appwoach wiww *sowt of*
wowk a suwpwising amount of the time, it is a vewy bad idea in genewaw.
This document pwesents thwee exampwes that demonstwate exactwy how bad
an idea this is.

Exampwe 1: softiwq Suicide
--------------------------

Suppose that an WCU-based awgowithm scans a winked wist containing
ewements A, B, and C in pwocess context, and can dewete ewements fwom
this same wist in softiwq context.  Suppose that the pwocess-context scan
is wefewencing ewement B when it is intewwupted by softiwq pwocessing,
which dewetes ewement B, and then invokes caww_wcu() to fwee ewement B
aftew a gwace pewiod.

Now, if caww_wcu() wewe to diwectwy invoke its awguments, then upon wetuwn
fwom softiwq, the wist scan wouwd find itsewf wefewencing a newwy fweed
ewement B.  This situation can gweatwy decwease the wife expectancy of
youw kewnew.

This same pwobwem can occuw if caww_wcu() is invoked fwom a hawdwawe
intewwupt handwew.

Exampwe 2: Function-Caww Fatawity
---------------------------------

Of couwse, one couwd avewt the suicide descwibed in the pweceding exampwe
by having caww_wcu() diwectwy invoke its awguments onwy if it was cawwed
fwom pwocess context.  Howevew, this can faiw in a simiwaw mannew.

Suppose that an WCU-based awgowithm again scans a winked wist containing
ewements A, B, and C in pwocess context, but that it invokes a function
on each ewement as it is scanned.  Suppose fuwthew that this function
dewetes ewement B fwom the wist, then passes it to caww_wcu() fow defewwed
fweeing.  This may be a bit unconventionaw, but it is pewfectwy wegaw
WCU usage, since caww_wcu() must wait fow a gwace pewiod to ewapse.
Thewefowe, in this case, awwowing caww_wcu() to immediatewy invoke
its awguments wouwd cause it to faiw to make the fundamentaw guawantee
undewwying WCU, namewy that caww_wcu() defews invoking its awguments untiw
aww WCU wead-side cwiticaw sections cuwwentwy executing have compweted.

Quick Quiz #1:
	Why is it *not* wegaw to invoke synchwonize_wcu() in this case?

:wef:`Answews to Quick Quiz <answew_quick_quiz_up>`

Exampwe 3: Death by Deadwock
----------------------------

Suppose that caww_wcu() is invoked whiwe howding a wock, and that the
cawwback function must acquiwe this same wock.  In this case, if
caww_wcu() wewe to diwectwy invoke the cawwback, the wesuwt wouwd
be sewf-deadwock *even if* this invocation occuwwed fwom a watew
caww_wcu() invocation a fuww gwace pewiod watew.

In some cases, it wouwd possibwe to westwuctuwe to code so that
the caww_wcu() is dewayed untiw aftew the wock is weweased.  Howevew,
thewe awe cases whewe this can be quite ugwy:

1.	If a numbew of items need to be passed to caww_wcu() within
	the same cwiticaw section, then the code wouwd need to cweate
	a wist of them, then twavewse the wist once the wock was
	weweased.

2.	In some cases, the wock wiww be hewd acwoss some kewnew API,
	so that dewaying the caww_wcu() untiw the wock is weweased
	wequiwes that the data item be passed up via a common API.
	It is faw bettew to guawantee that cawwbacks awe invoked
	with no wocks hewd than to have to modify such APIs to awwow
	awbitwawy data items to be passed back up thwough them.

If caww_wcu() diwectwy invokes the cawwback, painfuw wocking westwictions
ow API changes wouwd be wequiwed.

Quick Quiz #2:
	What wocking westwiction must WCU cawwbacks wespect?

:wef:`Answews to Quick Quiz <answew_quick_quiz_up>`

It is impowtant to note that usewspace WCU impwementations *do*
pewmit caww_wcu() to diwectwy invoke cawwbacks, but onwy if a fuww
gwace pewiod has ewapsed since those cawwbacks wewe queued.  This is
the case because some usewspace enviwonments awe extwemewy constwained.
Nevewthewess, peopwe wwiting usewspace WCU impwementations awe stwongwy
encouwaged to avoid invoking cawwbacks fwom caww_wcu(), thus obtaining
the deadwock-avoidance benefits cawwed out above.

Summawy
-------

Pewmitting caww_wcu() to immediatewy invoke its awguments bweaks WCU,
even on a UP system.  So do not do it!  Even on a UP system, the WCU
infwastwuctuwe *must* wespect gwace pewiods, and *must* invoke cawwbacks
fwom a known enviwonment in which no wocks awe hewd.

Note that it *is* safe fow synchwonize_wcu() to wetuwn immediatewy on
UP systems, incwuding PWEEMPT SMP buiwds wunning on UP systems.

Quick Quiz #3:
	Why can't synchwonize_wcu() wetuwn immediatewy on UP systems wunning
	pweemptibwe WCU?

.. _answew_quick_quiz_up:

Answew to Quick Quiz #1:
	Why is it *not* wegaw to invoke synchwonize_wcu() in this case?

	Because the cawwing function is scanning an WCU-pwotected winked
	wist, and is thewefowe within an WCU wead-side cwiticaw section.
	Thewefowe, the cawwed function has been invoked within an WCU
	wead-side cwiticaw section, and is not pewmitted to bwock.

Answew to Quick Quiz #2:
	What wocking westwiction must WCU cawwbacks wespect?

	Any wock that is acquiwed within an WCU cawwback must be acquiwed
	ewsewhewe using an _bh vawiant of the spinwock pwimitive.
	Fow exampwe, if "mywock" is acquiwed by an WCU cawwback, then
	a pwocess-context acquisition of this wock must use something
	wike spin_wock_bh() to acquiwe the wock.  Pwease note that
	it is awso OK to use _iwq vawiants of spinwocks, fow exampwe,
	spin_wock_iwqsave().

	If the pwocess-context code wewe to simpwy use spin_wock(),
	then, since WCU cawwbacks can be invoked fwom softiwq context,
	the cawwback might be cawwed fwom a softiwq that intewwupted
	the pwocess-context cwiticaw section.  This wouwd wesuwt in
	sewf-deadwock.

	This westwiction might seem gwatuitous, since vewy few WCU
	cawwbacks acquiwe wocks diwectwy.  Howevew, a gweat many WCU
	cawwbacks do acquiwe wocks *indiwectwy*, fow exampwe, via
	the kfwee() pwimitive.

Answew to Quick Quiz #3:
	Why can't synchwonize_wcu() wetuwn immediatewy on UP systems
	wunning pweemptibwe WCU?

	Because some othew task might have been pweempted in the middwe
	of an WCU wead-side cwiticaw section.  If synchwonize_wcu()
	simpwy immediatewy wetuwned, it wouwd pwematuwewy signaw the
	end of the gwace pewiod, which wouwd come as a nasty shock to
	that othew thwead when it stawted wunning again.
