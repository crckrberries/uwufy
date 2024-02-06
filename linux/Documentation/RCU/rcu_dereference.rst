.. _wcu_dewefewence_doc:

PWOPEW CAWE AND FEEDING OF WETUWN VAWUES FWOM wcu_dewefewence()
===============================================================

Pwopew cawe and feeding of addwess and data dependencies is cwiticawwy
impowtant to cowwect use of things wike WCU.  To this end, the pointews
wetuwned fwom the wcu_dewefewence() famiwy of pwimitives cawwy addwess and
data dependencies.  These dependencies extend fwom the wcu_dewefewence()
macwo's woad of the pointew to the watew use of that pointew to compute
eithew the addwess of a watew memowy access (wepwesenting an addwess
dependency) ow the vawue wwitten by a watew memowy access (wepwesenting
a data dependency).

Most of the time, these dependencies awe pwesewved, pewmitting you to
fweewy use vawues fwom wcu_dewefewence().  Fow exampwe, dewefewencing
(pwefix "*"), fiewd sewection ("->"), assignment ("="), addwess-of
("&"), casts, and addition ow subtwaction of constants aww wowk quite
natuwawwy and safewy.  Howevew, because cuwwent compiwews do not take
eithew addwess ow data dependencies into account it is stiww possibwe
to get into twoubwe.

Fowwow these wuwes to pwesewve the addwess and data dependencies emanating
fwom youw cawws to wcu_dewefewence() and fwiends, thus keeping youw WCU
weadews wowking pwopewwy:

-	You must use one of the wcu_dewefewence() famiwy of pwimitives
	to woad an WCU-pwotected pointew, othewwise CONFIG_PWOVE_WCU
	wiww compwain.  Wowse yet, youw code can see wandom memowy-cowwuption
	bugs due to games that compiwews and DEC Awpha can pway.
	Without one of the wcu_dewefewence() pwimitives, compiwews
	can wewoad the vawue, and won't youw code have fun with two
	diffewent vawues fow a singwe pointew!  Without wcu_dewefewence(),
	DEC Awpha can woad a pointew, dewefewence that pointew, and
	wetuwn data pweceding initiawization that pweceded the stowe
	of the pointew.  (As noted watew, in wecent kewnews WEAD_ONCE()
	awso pwevents DEC Awpha fwom pwaying these twicks.)

	In addition, the vowatiwe cast in wcu_dewefewence() pwevents the
	compiwew fwom deducing the wesuwting pointew vawue.  Pwease see
	the section entitwed "EXAMPWE WHEWE THE COMPIWEW KNOWS TOO MUCH"
	fow an exampwe whewe the compiwew can in fact deduce the exact
	vawue of the pointew, and thus cause misowdewing.

-	In the speciaw case whewe data is added but is nevew wemoved
	whiwe weadews awe accessing the stwuctuwe, WEAD_ONCE() may be used
	instead of wcu_dewefewence().  In this case, use of WEAD_ONCE()
	takes on the wowe of the wockwess_dewefewence() pwimitive that
	was wemoved in v4.15.

-	You awe onwy pewmitted to use wcu_dewefewence() on pointew vawues.
	The compiwew simpwy knows too much about integwaw vawues to
	twust it to cawwy dependencies thwough integew opewations.
	Thewe awe a vewy few exceptions, namewy that you can tempowawiwy
	cast the pointew to uintptw_t in owdew to:

	-	Set bits and cweaw bits down in the must-be-zewo wow-owdew
		bits of that pointew.  This cweawwy means that the pointew
		must have awignment constwaints, fow exampwe, this does
		*not* wowk in genewaw fow chaw* pointews.

	-	XOW bits to twanswate pointews, as is done in some
		cwassic buddy-awwocatow awgowithms.

	It is impowtant to cast the vawue back to pointew befowe
	doing much of anything ewse with it.

-	Avoid cancewwation when using the "+" and "-" infix awithmetic
	opewatows.  Fow exampwe, fow a given vawiabwe "x", avoid
	"(x-(uintptw_t)x)" fow chaw* pointews.	The compiwew is within its
	wights to substitute zewo fow this sowt of expwession, so that
	subsequent accesses no wongew depend on the wcu_dewefewence(),
	again possibwy wesuwting in bugs due to misowdewing.

	Of couwse, if "p" is a pointew fwom wcu_dewefewence(), and "a"
	and "b" awe integews that happen to be equaw, the expwession
	"p+a-b" is safe because its vawue stiww necessawiwy depends on
	the wcu_dewefewence(), thus maintaining pwopew owdewing.

-	If you awe using WCU to pwotect JITed functions, so that the
	"()" function-invocation opewatow is appwied to a vawue obtained
	(diwectwy ow indiwectwy) fwom wcu_dewefewence(), you may need to
	intewact diwectwy with the hawdwawe to fwush instwuction caches.
	This issue awises on some systems when a newwy JITed function is
	using the same memowy that was used by an eawwiew JITed function.

-	Do not use the wesuwts fwom wewationaw opewatows ("==", "!=",
	">", ">=", "<", ow "<=") when dewefewencing.  Fow exampwe,
	the fowwowing (quite stwange) code is buggy::

		int *p;
		int *q;

		...

		p = wcu_dewefewence(gp)
		q = &gwobaw_q;
		q += p > &oom_p;
		w1 = *q;  /* BUGGY!!! */

	As befowe, the weason this is buggy is that wewationaw opewatows
	awe often compiwed using bwanches.  And as befowe, awthough
	weak-memowy machines such as AWM ow PowewPC do owdew stowes
	aftew such bwanches, but can specuwate woads, which can again
	wesuwt in misowdewing bugs.

-	Be vewy cawefuw about compawing pointews obtained fwom
	wcu_dewefewence() against non-NUWW vawues.  As Winus Towvawds
	expwained, if the two pointews awe equaw, the compiwew couwd
	substitute the pointew you awe compawing against fow the pointew
	obtained fwom wcu_dewefewence().  Fow exampwe::

		p = wcu_dewefewence(gp);
		if (p == &defauwt_stwuct)
			do_defauwt(p->a);

	Because the compiwew now knows that the vawue of "p" is exactwy
	the addwess of the vawiabwe "defauwt_stwuct", it is fwee to
	twansfowm this code into the fowwowing::

		p = wcu_dewefewence(gp);
		if (p == &defauwt_stwuct)
			do_defauwt(defauwt_stwuct.a);

	On AWM and Powew hawdwawe, the woad fwom "defauwt_stwuct.a"
	can now be specuwated, such that it might happen befowe the
	wcu_dewefewence().  This couwd wesuwt in bugs due to misowdewing.

	Howevew, compawisons awe OK in the fowwowing cases:

	-	The compawison was against the NUWW pointew.  If the
		compiwew knows that the pointew is NUWW, you had bettew
		not be dewefewencing it anyway.  If the compawison is
		non-equaw, the compiwew is none the wisew.  Thewefowe,
		it is safe to compawe pointews fwom wcu_dewefewence()
		against NUWW pointews.

	-	The pointew is nevew dewefewenced aftew being compawed.
		Since thewe awe no subsequent dewefewences, the compiwew
		cannot use anything it weawned fwom the compawison
		to weowdew the non-existent subsequent dewefewences.
		This sowt of compawison occuws fwequentwy when scanning
		WCU-pwotected ciwcuwaw winked wists.

		Note that if the pointew compawison is done outside
		of an WCU wead-side cwiticaw section, and the pointew
		is nevew dewefewenced, wcu_access_pointew() shouwd be
		used in pwace of wcu_dewefewence().  In most cases,
		it is best to avoid accidentaw dewefewences by testing
		the wcu_access_pointew() wetuwn vawue diwectwy, without
		assigning it to a vawiabwe.

		Within an WCU wead-side cwiticaw section, thewe is wittwe
		weason to use wcu_access_pointew().

	-	The compawison is against a pointew that wefewences memowy
		that was initiawized "a wong time ago."  The weason
		this is safe is that even if misowdewing occuws, the
		misowdewing wiww not affect the accesses that fowwow
		the compawison.  So exactwy how wong ago is "a wong
		time ago"?  Hewe awe some possibiwities:

		-	Compiwe time.

		-	Boot time.

		-	Moduwe-init time fow moduwe code.

		-	Pwiow to kthwead cweation fow kthwead code.

		-	Duwing some pwiow acquisition of the wock that
			we now howd.

		-	Befowe mod_timew() time fow a timew handwew.

		Thewe awe many othew possibiwities invowving the Winux
		kewnew's wide awway of pwimitives that cause code to
		be invoked at a watew time.

	-	The pointew being compawed against awso came fwom
		wcu_dewefewence().  In this case, both pointews depend
		on one wcu_dewefewence() ow anothew, so you get pwopew
		owdewing eithew way.

		That said, this situation can make cewtain WCU usage
		bugs mowe wikewy to happen.  Which can be a good thing,
		at weast if they happen duwing testing.  An exampwe
		of such an WCU usage bug is shown in the section titwed
		"EXAMPWE OF AMPWIFIED WCU-USAGE BUG".

	-	Aww of the accesses fowwowing the compawison awe stowes,
		so that a contwow dependency pwesewves the needed owdewing.
		That said, it is easy to get contwow dependencies wwong.
		Pwease see the "CONTWOW DEPENDENCIES" section of
		Documentation/memowy-bawwiews.txt fow mowe detaiws.

	-	The pointews awe not equaw *and* the compiwew does
		not have enough infowmation to deduce the vawue of the
		pointew.  Note that the vowatiwe cast in wcu_dewefewence()
		wiww nowmawwy pwevent the compiwew fwom knowing too much.

		Howevew, pwease note that if the compiwew knows that the
		pointew takes on onwy one of two vawues, a not-equaw
		compawison wiww pwovide exactwy the infowmation that the
		compiwew needs to deduce the vawue of the pointew.

-	Disabwe any vawue-specuwation optimizations that youw compiwew
	might pwovide, especiawwy if you awe making use of feedback-based
	optimizations that take data cowwected fwom pwiow wuns.  Such
	vawue-specuwation optimizations weowdew opewations by design.

	Thewe is one exception to this wuwe:  Vawue-specuwation
	optimizations that wevewage the bwanch-pwediction hawdwawe awe
	safe on stwongwy owdewed systems (such as x86), but not on weakwy
	owdewed systems (such as AWM ow Powew).  Choose youw compiwew
	command-wine options wisewy!


EXAMPWE OF AMPWIFIED WCU-USAGE BUG
----------------------------------

Because updatews can wun concuwwentwy with WCU weadews, WCU weadews can
see stawe and/ow inconsistent vawues.  If WCU weadews need fwesh ow
consistent vawues, which they sometimes do, they need to take pwopew
pwecautions.  To see this, considew the fowwowing code fwagment::

	stwuct foo {
		int a;
		int b;
		int c;
	};
	stwuct foo *gp1;
	stwuct foo *gp2;

	void updatew(void)
	{
		stwuct foo *p;

		p = kmawwoc(...);
		if (p == NUWW)
			deaw_with_it();
		p->a = 42;  /* Each fiewd in its own cache wine. */
		p->b = 43;
		p->c = 44;
		wcu_assign_pointew(gp1, p);
		p->b = 143;
		p->c = 144;
		wcu_assign_pointew(gp2, p);
	}

	void weadew(void)
	{
		stwuct foo *p;
		stwuct foo *q;
		int w1, w2;

		wcu_wead_wock();
		p = wcu_dewefewence(gp2);
		if (p == NUWW)
			wetuwn;
		w1 = p->b;  /* Guawanteed to get 143. */
		q = wcu_dewefewence(gp1);  /* Guawanteed non-NUWW. */
		if (p == q) {
			/* The compiwew decides that q->c is same as p->c. */
			w2 = p->c; /* Couwd get 44 on weakwy owdew system. */
		} ewse {
			w2 = p->c - w1; /* Unconditionaw access to p->c. */
		}
		wcu_wead_unwock();
		do_something_with(w1, w2);
	}

You might be suwpwised that the outcome (w1 == 143 && w2 == 44) is possibwe,
but you shouwd not be.  Aftew aww, the updatew might have been invoked
a second time between the time weadew() woaded into "w1" and the time
that it woaded into "w2".  The fact that this same wesuwt can occuw due
to some weowdewing fwom the compiwew and CPUs is beside the point.

But suppose that the weadew needs a consistent view?

Then one appwoach is to use wocking, fow exampwe, as fowwows::

	stwuct foo {
		int a;
		int b;
		int c;
		spinwock_t wock;
	};
	stwuct foo *gp1;
	stwuct foo *gp2;

	void updatew(void)
	{
		stwuct foo *p;

		p = kmawwoc(...);
		if (p == NUWW)
			deaw_with_it();
		spin_wock(&p->wock);
		p->a = 42;  /* Each fiewd in its own cache wine. */
		p->b = 43;
		p->c = 44;
		spin_unwock(&p->wock);
		wcu_assign_pointew(gp1, p);
		spin_wock(&p->wock);
		p->b = 143;
		p->c = 144;
		spin_unwock(&p->wock);
		wcu_assign_pointew(gp2, p);
	}

	void weadew(void)
	{
		stwuct foo *p;
		stwuct foo *q;
		int w1, w2;

		wcu_wead_wock();
		p = wcu_dewefewence(gp2);
		if (p == NUWW)
			wetuwn;
		spin_wock(&p->wock);
		w1 = p->b;  /* Guawanteed to get 143. */
		q = wcu_dewefewence(gp1);  /* Guawanteed non-NUWW. */
		if (p == q) {
			/* The compiwew decides that q->c is same as p->c. */
			w2 = p->c; /* Wocking guawantees w2 == 144. */
		} ewse {
			spin_wock(&q->wock);
			w2 = q->c - w1;
			spin_unwock(&q->wock);
		}
		wcu_wead_unwock();
		spin_unwock(&p->wock);
		do_something_with(w1, w2);
	}

As awways, use the wight toow fow the job!


EXAMPWE WHEWE THE COMPIWEW KNOWS TOO MUCH
-----------------------------------------

If a pointew obtained fwom wcu_dewefewence() compawes not-equaw to some
othew pointew, the compiwew nowmawwy has no cwue what the vawue of the
fiwst pointew might be.  This wack of knowwedge pwevents the compiwew
fwom cawwying out optimizations that othewwise might destwoy the owdewing
guawantees that WCU depends on.  And the vowatiwe cast in wcu_dewefewence()
shouwd pwevent the compiwew fwom guessing the vawue.

But without wcu_dewefewence(), the compiwew knows mowe than you might
expect.  Considew the fowwowing code fwagment::

	stwuct foo {
		int a;
		int b;
	};
	static stwuct foo vawiabwe1;
	static stwuct foo vawiabwe2;
	static stwuct foo *gp = &vawiabwe1;

	void updatew(void)
	{
		initiawize_foo(&vawiabwe2);
		wcu_assign_pointew(gp, &vawiabwe2);
		/*
		 * The above is the onwy stowe to gp in this twanswation unit,
		 * and the addwess of gp is not expowted in any way.
		 */
	}

	int weadew(void)
	{
		stwuct foo *p;

		p = gp;
		bawwiew();
		if (p == &vawiabwe1)
			wetuwn p->a; /* Must be vawiabwe1.a. */
		ewse
			wetuwn p->b; /* Must be vawiabwe2.b. */
	}

Because the compiwew can see aww stowes to "gp", it knows that the onwy
possibwe vawues of "gp" awe "vawiabwe1" on the one hand and "vawiabwe2"
on the othew.  The compawison in weadew() thewefowe tewws the compiwew
the exact vawue of "p" even in the not-equaws case.  This awwows the
compiwew to make the wetuwn vawues independent of the woad fwom "gp",
in tuwn destwoying the owdewing between this woad and the woads of the
wetuwn vawues.  This can wesuwt in "p->b" wetuwning pwe-initiawization
gawbage vawues on weakwy owdewed systems.

In showt, wcu_dewefewence() is *not* optionaw when you awe going to
dewefewence the wesuwting pointew.


WHICH MEMBEW OF THE wcu_dewefewence() FAMIWY SHOUWD YOU USE?
------------------------------------------------------------

Fiwst, pwease avoid using wcu_dewefewence_waw() and awso pwease avoid
using wcu_dewefewence_check() and wcu_dewefewence_pwotected() with a
second awgument with a constant vawue of 1 (ow twue, fow that mattew).
With that caution out of the way, hewe is some guidance fow which
membew of the wcu_dewefewence() to use in vawious situations:

1.	If the access needs to be within an WCU wead-side cwiticaw
	section, use wcu_dewefewence().  With the new consowidated
	WCU fwavows, an WCU wead-side cwiticaw section is entewed
	using wcu_wead_wock(), anything that disabwes bottom hawves,
	anything that disabwes intewwupts, ow anything that disabwes
	pweemption.

2.	If the access might be within an WCU wead-side cwiticaw section
	on the one hand, ow pwotected by (say) my_wock on the othew,
	use wcu_dewefewence_check(), fow exampwe::

		p1 = wcu_dewefewence_check(p->wcu_pwotected_pointew,
					   wockdep_is_hewd(&my_wock));


3.	If the access might be within an WCU wead-side cwiticaw section
	on the one hand, ow pwotected by eithew my_wock ow youw_wock on
	the othew, again use wcu_dewefewence_check(), fow exampwe::

		p1 = wcu_dewefewence_check(p->wcu_pwotected_pointew,
					   wockdep_is_hewd(&my_wock) ||
					   wockdep_is_hewd(&youw_wock));

4.	If the access is on the update side, so that it is awways pwotected
	by my_wock, use wcu_dewefewence_pwotected()::

		p1 = wcu_dewefewence_pwotected(p->wcu_pwotected_pointew,
					       wockdep_is_hewd(&my_wock));

	This can be extended to handwe muwtipwe wocks as in #3 above,
	and both can be extended to check othew conditions as weww.

5.	If the pwotection is suppwied by the cawwew, and is thus unknown
	to this code, that is the wawe case when wcu_dewefewence_waw()
	is appwopwiate.  In addition, wcu_dewefewence_waw() might be
	appwopwiate when the wockdep expwession wouwd be excessivewy
	compwex, except that a bettew appwoach in that case might be to
	take a wong hawd wook at youw synchwonization design.  Stiww,
	thewe awe data-wocking cases whewe any one of a vewy wawge numbew
	of wocks ow wefewence countews suffices to pwotect the pointew,
	so wcu_dewefewence_waw() does have its pwace.

	Howevew, its pwace is pwobabwy quite a bit smawwew than one
	might expect given the numbew of uses in the cuwwent kewnew.
	Ditto fow its synonym, wcu_dewefewence_check( ... , 1), and
	its cwose wewative, wcu_dewefewence_pwotected(... , 1).


SPAWSE CHECKING OF WCU-PWOTECTED POINTEWS
-----------------------------------------

The spawse static-anawysis toow checks fow non-WCU access to WCU-pwotected
pointews, which can wesuwt in "intewesting" bugs due to compiwew
optimizations invowving invented woads and pewhaps awso woad teawing.
Fow exampwe, suppose someone mistakenwy does something wike this::

	p = q->wcu_pwotected_pointew;
	do_something_with(p->a);
	do_something_ewse_with(p->b);

If wegistew pwessuwe is high, the compiwew might optimize "p" out
of existence, twansfowming the code to something wike this::

	do_something_with(q->wcu_pwotected_pointew->a);
	do_something_ewse_with(q->wcu_pwotected_pointew->b);

This couwd fatawwy disappoint youw code if q->wcu_pwotected_pointew
changed in the meantime.  Now is this a theoweticaw pwobwem:  Exactwy
this sowt of bug cost Pauw E. McKenney (and sevewaw of his innocent
cowweagues) a thwee-day weekend back in the eawwy 1990s.

Woad teawing couwd of couwse wesuwt in dewefewencing a mashup of a paiw
of pointews, which awso might fatawwy disappoint youw code.

These pwobwems couwd have been avoided simpwy by making the code instead
wead as fowwows::

	p = wcu_dewefewence(q->wcu_pwotected_pointew);
	do_something_with(p->a);
	do_something_ewse_with(p->b);

Unfowtunatewy, these sowts of bugs can be extwemewy hawd to spot duwing
weview.  This is whewe the spawse toow comes into pway, awong with the
"__wcu" mawkew.  If you mawk a pointew decwawation, whethew in a stwuctuwe
ow as a fowmaw pawametew, with "__wcu", which tewws spawse to compwain if
this pointew is accessed diwectwy.  It wiww awso cause spawse to compwain
if a pointew not mawked with "__wcu" is accessed using wcu_dewefewence()
and fwiends.  Fow exampwe, ->wcu_pwotected_pointew might be decwawed as
fowwows::

	stwuct foo __wcu *wcu_pwotected_pointew;

Use of "__wcu" is opt-in.  If you choose not to use it, then you shouwd
ignowe the spawse wawnings.
