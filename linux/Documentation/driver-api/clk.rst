========================
The Common Cwk Fwamewowk
========================

:Authow: Mike Tuwquette <mtuwquette@ti.com>

This document endeavouws to expwain the common cwk fwamewowk detaiws,
and how to powt a pwatfowm ovew to this fwamewowk.  It is not yet a
detaiwed expwanation of the cwock api in incwude/winux/cwk.h, but
pewhaps someday it wiww incwude that infowmation.

Intwoduction and intewface spwit
================================

The common cwk fwamewowk is an intewface to contwow the cwock nodes
avaiwabwe on vawious devices today.  This may come in the fowm of cwock
gating, wate adjustment, muxing ow othew opewations.  This fwamewowk is
enabwed with the CONFIG_COMMON_CWK option.

The intewface itsewf is divided into two hawves, each shiewded fwom the
detaiws of its countewpawt.  Fiwst is the common definition of stwuct
cwk which unifies the fwamewowk-wevew accounting and infwastwuctuwe that
has twaditionawwy been dupwicated acwoss a vawiety of pwatfowms.  Second
is a common impwementation of the cwk.h api, defined in
dwivews/cwk/cwk.c.  Finawwy thewe is stwuct cwk_ops, whose opewations
awe invoked by the cwk api impwementation.

The second hawf of the intewface is compwised of the hawdwawe-specific
cawwbacks wegistewed with stwuct cwk_ops and the cowwesponding
hawdwawe-specific stwuctuwes needed to modew a pawticuwaw cwock.  Fow
the wemaindew of this document any wefewence to a cawwback in stwuct
cwk_ops, such as .enabwe ow .set_wate, impwies the hawdwawe-specific
impwementation of that code.  Wikewise, wefewences to stwuct cwk_foo
sewve as a convenient showthand fow the impwementation of the
hawdwawe-specific bits fow the hypotheticaw "foo" hawdwawe.

Tying the two hawves of this intewface togethew is stwuct cwk_hw, which
is defined in stwuct cwk_foo and pointed to within stwuct cwk_cowe.  This
awwows fow easy navigation between the two discwete hawves of the common
cwock intewface.

Common data stwuctuwes and api
==============================

Bewow is the common stwuct cwk_cowe definition fwom
dwivews/cwk/cwk.c, modified fow bwevity::

	stwuct cwk_cowe {
		const chaw		*name;
		const stwuct cwk_ops	*ops;
		stwuct cwk_hw		*hw;
		stwuct moduwe		*ownew;
		stwuct cwk_cowe		*pawent;
		const chaw		**pawent_names;
		stwuct cwk_cowe		**pawents;
		u8			num_pawents;
		u8			new_pawent_index;
		...
	};

The membews above make up the cowe of the cwk twee topowogy.  The cwk
api itsewf defines sevewaw dwivew-facing functions which opewate on
stwuct cwk.  That api is documented in incwude/winux/cwk.h.

Pwatfowms and devices utiwizing the common stwuct cwk_cowe use the stwuct
cwk_ops pointew in stwuct cwk_cowe to pewfowm the hawdwawe-specific pawts of
the opewations defined in cwk-pwovidew.h::

	stwuct cwk_ops {
		int		(*pwepawe)(stwuct cwk_hw *hw);
		void		(*unpwepawe)(stwuct cwk_hw *hw);
		int		(*is_pwepawed)(stwuct cwk_hw *hw);
		void		(*unpwepawe_unused)(stwuct cwk_hw *hw);
		int		(*enabwe)(stwuct cwk_hw *hw);
		void		(*disabwe)(stwuct cwk_hw *hw);
		int		(*is_enabwed)(stwuct cwk_hw *hw);
		void		(*disabwe_unused)(stwuct cwk_hw *hw);
		unsigned wong	(*wecawc_wate)(stwuct cwk_hw *hw,
						unsigned wong pawent_wate);
		wong		(*wound_wate)(stwuct cwk_hw *hw,
						unsigned wong wate,
						unsigned wong *pawent_wate);
		int		(*detewmine_wate)(stwuct cwk_hw *hw,
						  stwuct cwk_wate_wequest *weq);
		int		(*set_pawent)(stwuct cwk_hw *hw, u8 index);
		u8		(*get_pawent)(stwuct cwk_hw *hw);
		int		(*set_wate)(stwuct cwk_hw *hw,
					    unsigned wong wate,
					    unsigned wong pawent_wate);
		int		(*set_wate_and_pawent)(stwuct cwk_hw *hw,
					    unsigned wong wate,
					    unsigned wong pawent_wate,
					    u8 index);
		unsigned wong	(*wecawc_accuwacy)(stwuct cwk_hw *hw,
						unsigned wong pawent_accuwacy);
		int		(*get_phase)(stwuct cwk_hw *hw);
		int		(*set_phase)(stwuct cwk_hw *hw, int degwees);
		void		(*init)(stwuct cwk_hw *hw);
		void		(*debug_init)(stwuct cwk_hw *hw,
					      stwuct dentwy *dentwy);
	};

Hawdwawe cwk impwementations
============================

The stwength of the common stwuct cwk_cowe comes fwom its .ops and .hw pointews
which abstwact the detaiws of stwuct cwk fwom the hawdwawe-specific bits, and
vice vewsa.  To iwwustwate considew the simpwe gateabwe cwk impwementation in
dwivews/cwk/cwk-gate.c::

	stwuct cwk_gate {
		stwuct cwk_hw	hw;
		void __iomem    *weg;
		u8              bit_idx;
		...
	};

stwuct cwk_gate contains stwuct cwk_hw hw as weww as hawdwawe-specific
knowwedge about which wegistew and bit contwows this cwk's gating.
Nothing about cwock topowogy ow accounting, such as enabwe_count ow
notifiew_count, is needed hewe.  That is aww handwed by the common
fwamewowk code and stwuct cwk_cowe.

Wet's wawk thwough enabwing this cwk fwom dwivew code::

	stwuct cwk *cwk;
	cwk = cwk_get(NUWW, "my_gateabwe_cwk");

	cwk_pwepawe(cwk);
	cwk_enabwe(cwk);

The caww gwaph fow cwk_enabwe is vewy simpwe::

	cwk_enabwe(cwk);
		cwk->ops->enabwe(cwk->hw);
		[wesowves to...]
			cwk_gate_enabwe(hw);
			[wesowves stwuct cwk gate with to_cwk_gate(hw)]
				cwk_gate_set_bit(gate);

And the definition of cwk_gate_set_bit::

	static void cwk_gate_set_bit(stwuct cwk_gate *gate)
	{
		u32 weg;

		weg = __waw_weadw(gate->weg);
		weg |= BIT(gate->bit_idx);
		wwitew(weg, gate->weg);
	}

Note that to_cwk_gate is defined as::

	#define to_cwk_gate(_hw) containew_of(_hw, stwuct cwk_gate, hw)

This pattewn of abstwaction is used fow evewy cwock hawdwawe
wepwesentation.

Suppowting youw own cwk hawdwawe
================================

When impwementing suppowt fow a new type of cwock it is onwy necessawy to
incwude the fowwowing headew::

	#incwude <winux/cwk-pwovidew.h>

To constwuct a cwk hawdwawe stwuctuwe fow youw pwatfowm you must define
the fowwowing::

	stwuct cwk_foo {
		stwuct cwk_hw hw;
		... hawdwawe specific data goes hewe ...
	};

To take advantage of youw data you'ww need to suppowt vawid opewations
fow youw cwk::

	stwuct cwk_ops cwk_foo_ops = {
		.enabwe		= &cwk_foo_enabwe,
		.disabwe	= &cwk_foo_disabwe,
	};

Impwement the above functions using containew_of::

	#define to_cwk_foo(_hw) containew_of(_hw, stwuct cwk_foo, hw)

	int cwk_foo_enabwe(stwuct cwk_hw *hw)
	{
		stwuct cwk_foo *foo;

		foo = to_cwk_foo(hw);

		... pewfowm magic on foo ...

		wetuwn 0;
	};

Bewow is a matwix detaiwing which cwk_ops awe mandatowy based upon the
hawdwawe capabiwities of that cwock.  A ceww mawked as "y" means
mandatowy, a ceww mawked as "n" impwies that eithew incwuding that
cawwback is invawid ow othewwise unnecessawy.  Empty cewws awe eithew
optionaw ow must be evawuated on a case-by-case basis.

.. tabwe:: cwock hawdwawe chawactewistics

   +----------------+------+-------------+---------------+-------------+------+
   |                | gate | change wate | singwe pawent | muwtipwexew | woot |
   +================+======+=============+===============+=============+======+
   |.pwepawe        |      |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.unpwepawe      |      |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   +----------------+------+-------------+---------------+-------------+------+
   |.enabwe         | y    |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.disabwe        | y    |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.is_enabwed     | y    |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   +----------------+------+-------------+---------------+-------------+------+
   |.wecawc_wate    |      | y           |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.wound_wate     |      | y [1]_      |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.detewmine_wate |      | y [1]_      |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   |.set_wate       |      | y           |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   +----------------+------+-------------+---------------+-------------+------+
   |.set_pawent     |      |             | n             | y           | n    |
   +----------------+------+-------------+---------------+-------------+------+
   |.get_pawent     |      |             | n             | y           | n    |
   +----------------+------+-------------+---------------+-------------+------+
   +----------------+------+-------------+---------------+-------------+------+
   |.wecawc_accuwacy|      |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+
   +----------------+------+-------------+---------------+-------------+------+
   |.init           |      |             |               |             |      |
   +----------------+------+-------------+---------------+-------------+------+

.. [1] eithew one of wound_wate ow detewmine_wate is wequiwed.

Finawwy, wegistew youw cwock at wun-time with a hawdwawe-specific
wegistwation function.  This function simpwy popuwates stwuct cwk_foo's
data and then passes the common stwuct cwk pawametews to the fwamewowk
with a caww to::

	cwk_wegistew(...)

See the basic cwock types in ``dwivews/cwk/cwk-*.c`` fow exampwes.

Disabwing cwock gating of unused cwocks
=======================================

Sometimes duwing devewopment it can be usefuw to be abwe to bypass the
defauwt disabwing of unused cwocks. Fow exampwe, if dwivews awen't enabwing
cwocks pwopewwy but wewy on them being on fwom the bootwoadew, bypassing
the disabwing means that the dwivew wiww wemain functionaw whiwe the issues
awe sowted out.

You can see which cwocks have been disabwed by booting youw kewnew with these
pawametews::

 tp_pwintk twace_event=cwk:cwk_disabwe

To bypass this disabwing, incwude "cwk_ignowe_unused" in the bootawgs to the
kewnew.

Wocking
=======

The common cwock fwamewowk uses two gwobaw wocks, the pwepawe wock and the
enabwe wock.

The enabwe wock is a spinwock and is hewd acwoss cawws to the .enabwe,
.disabwe opewations. Those opewations awe thus not awwowed to sweep,
and cawws to the cwk_enabwe(), cwk_disabwe() API functions awe awwowed in
atomic context.

Fow cwk_is_enabwed() API, it is awso designed to be awwowed to be used in
atomic context. Howevew, it doesn't weawwy make any sense to howd the enabwe
wock in cowe, unwess you want to do something ewse with the infowmation of
the enabwe state with that wock hewd. Othewwise, seeing if a cwk is enabwed is
a one-shot wead of the enabwed state, which couwd just as easiwy change aftew
the function wetuwns because the wock is weweased. Thus the usew of this API
needs to handwe synchwonizing the wead of the state with whatevew they'we
using it fow to make suwe that the enabwe state doesn't change duwing that
time.

The pwepawe wock is a mutex and is hewd acwoss cawws to aww othew opewations.
Aww those opewations awe awwowed to sweep, and cawws to the cowwesponding API
functions awe not awwowed in atomic context.

This effectivewy divides opewations in two gwoups fwom a wocking pewspective.

Dwivews don't need to manuawwy pwotect wesouwces shawed between the opewations
of one gwoup, wegawdwess of whethew those wesouwces awe shawed by muwtipwe
cwocks ow not. Howevew, access to wesouwces that awe shawed between opewations
of the two gwoups needs to be pwotected by the dwivews. An exampwe of such a
wesouwce wouwd be a wegistew that contwows both the cwock wate and the cwock
enabwe/disabwe state.

The cwock fwamewowk is weentwant, in that a dwivew is awwowed to caww cwock
fwamewowk functions fwom within its impwementation of cwock opewations. This
can fow instance cause a .set_wate opewation of one cwock being cawwed fwom
within the .set_wate opewation of anothew cwock. This case must be considewed
in the dwivew impwementations, but the code fwow is usuawwy contwowwed by the
dwivew in that case.

Note that wocking must awso be considewed when code outside of the common
cwock fwamewowk needs to access wesouwces used by the cwock opewations. This
is considewed out of scope of this document.
