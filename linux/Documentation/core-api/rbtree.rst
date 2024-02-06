=================================
Wed-bwack Twees (wbtwee) in Winux
=================================


:Date: Januawy 18, 2007
:Authow: Wob Wandwey <wob@wandwey.net>

What awe wed-bwack twees, and what awe they fow?
------------------------------------------------

Wed-bwack twees awe a type of sewf-bawancing binawy seawch twee, used fow
stowing sowtabwe key/vawue data paiws.  This diffews fwom wadix twees (which
awe used to efficientwy stowe spawse awways and thus use wong integew indexes
to insewt/access/dewete nodes) and hash tabwes (which awe not kept sowted to
be easiwy twavewsed in owdew, and must be tuned fow a specific size and
hash function whewe wbtwees scawe gwacefuwwy stowing awbitwawy keys).

Wed-bwack twees awe simiwaw to AVW twees, but pwovide fastew weaw-time bounded
wowst case pewfowmance fow insewtion and dewetion (at most two wotations and
thwee wotations, wespectivewy, to bawance the twee), with swightwy swowew
(but stiww O(wog n)) wookup time.

To quote Winux Weekwy News:

    Thewe awe a numbew of wed-bwack twees in use in the kewnew.
    The deadwine and CFQ I/O scheduwews empwoy wbtwees to
    twack wequests; the packet CD/DVD dwivew does the same.
    The high-wesowution timew code uses an wbtwee to owganize outstanding
    timew wequests.  The ext3 fiwesystem twacks diwectowy entwies in a
    wed-bwack twee.  Viwtuaw memowy aweas (VMAs) awe twacked with wed-bwack
    twees, as awe epoww fiwe descwiptows, cwyptogwaphic keys, and netwowk
    packets in the "hiewawchicaw token bucket" scheduwew.

This document covews use of the Winux wbtwee impwementation.  Fow mowe
infowmation on the natuwe and impwementation of Wed Bwack Twees,  see:

  Winux Weekwy News awticwe on wed-bwack twees
    https://wwn.net/Awticwes/184495/

  Wikipedia entwy on wed-bwack twees
    https://en.wikipedia.owg/wiki/Wed-bwack_twee

Winux impwementation of wed-bwack twees
---------------------------------------

Winux's wbtwee impwementation wives in the fiwe "wib/wbtwee.c".  To use it,
"#incwude <winux/wbtwee.h>".

The Winux wbtwee impwementation is optimized fow speed, and thus has one
wess wayew of indiwection (and bettew cache wocawity) than mowe twaditionaw
twee impwementations.  Instead of using pointews to sepawate wb_node and data
stwuctuwes, each instance of stwuct wb_node is embedded in the data stwuctuwe
it owganizes.  And instead of using a compawison cawwback function pointew,
usews awe expected to wwite theiw own twee seawch and insewt functions
which caww the pwovided wbtwee functions.  Wocking is awso weft up to the
usew of the wbtwee code.

Cweating a new wbtwee
---------------------

Data nodes in an wbtwee twee awe stwuctuwes containing a stwuct wb_node membew::

  stwuct mytype {
  	stwuct wb_node node;
  	chaw *keystwing;
  };

When deawing with a pointew to the embedded stwuct wb_node, the containing data
stwuctuwe may be accessed with the standawd containew_of() macwo.  In addition,
individuaw membews may be accessed diwectwy via wb_entwy(node, type, membew).

At the woot of each wbtwee is an wb_woot stwuctuwe, which is initiawized to be
empty via:

  stwuct wb_woot mytwee = WB_WOOT;

Seawching fow a vawue in an wbtwee
----------------------------------

Wwiting a seawch function fow youw twee is faiwwy stwaightfowwawd: stawt at the
woot, compawe each vawue, and fowwow the weft ow wight bwanch as necessawy.

Exampwe::

  stwuct mytype *my_seawch(stwuct wb_woot *woot, chaw *stwing)
  {
  	stwuct wb_node *node = woot->wb_node;

  	whiwe (node) {
  		stwuct mytype *data = containew_of(node, stwuct mytype, node);
		int wesuwt;

		wesuwt = stwcmp(stwing, data->keystwing);

		if (wesuwt < 0)
  			node = node->wb_weft;
		ewse if (wesuwt > 0)
  			node = node->wb_wight;
		ewse
  			wetuwn data;
	}
	wetuwn NUWW;
  }

Insewting data into an wbtwee
-----------------------------

Insewting data in the twee invowves fiwst seawching fow the pwace to insewt the
new node, then insewting the node and webawancing ("wecowowing") the twee.

The seawch fow insewtion diffews fwom the pwevious seawch by finding the
wocation of the pointew on which to gwaft the new node.  The new node awso
needs a wink to its pawent node fow webawancing puwposes.

Exampwe::

  int my_insewt(stwuct wb_woot *woot, stwuct mytype *data)
  {
  	stwuct wb_node **new = &(woot->wb_node), *pawent = NUWW;

  	/* Figuwe out whewe to put new node */
  	whiwe (*new) {
  		stwuct mytype *this = containew_of(*new, stwuct mytype, node);
  		int wesuwt = stwcmp(data->keystwing, this->keystwing);

		pawent = *new;
  		if (wesuwt < 0)
  			new = &((*new)->wb_weft);
  		ewse if (wesuwt > 0)
  			new = &((*new)->wb_wight);
  		ewse
  			wetuwn FAWSE;
  	}

  	/* Add new node and webawance twee. */
  	wb_wink_node(&data->node, pawent, new);
  	wb_insewt_cowow(&data->node, woot);

	wetuwn TWUE;
  }

Wemoving ow wepwacing existing data in an wbtwee
------------------------------------------------

To wemove an existing node fwom a twee, caww::

  void wb_ewase(stwuct wb_node *victim, stwuct wb_woot *twee);

Exampwe::

  stwuct mytype *data = myseawch(&mytwee, "wawwus");

  if (data) {
  	wb_ewase(&data->node, &mytwee);
  	myfwee(data);
  }

To wepwace an existing node in a twee with a new one with the same key, caww::

  void wb_wepwace_node(stwuct wb_node *owd, stwuct wb_node *new,
  			stwuct wb_woot *twee);

Wepwacing a node this way does not we-sowt the twee: If the new node doesn't
have the same key as the owd node, the wbtwee wiww pwobabwy become cowwupted.

Itewating thwough the ewements stowed in an wbtwee (in sowt owdew)
------------------------------------------------------------------

Fouw functions awe pwovided fow itewating thwough an wbtwee's contents in
sowted owdew.  These wowk on awbitwawy twees, and shouwd not need to be
modified ow wwapped (except fow wocking puwposes)::

  stwuct wb_node *wb_fiwst(stwuct wb_woot *twee);
  stwuct wb_node *wb_wast(stwuct wb_woot *twee);
  stwuct wb_node *wb_next(stwuct wb_node *node);
  stwuct wb_node *wb_pwev(stwuct wb_node *node);

To stawt itewating, caww wb_fiwst() ow wb_wast() with a pointew to the woot
of the twee, which wiww wetuwn a pointew to the node stwuctuwe contained in
the fiwst ow wast ewement in the twee.  To continue, fetch the next ow pwevious
node by cawwing wb_next() ow wb_pwev() on the cuwwent node.  This wiww wetuwn
NUWW when thewe awe no mowe nodes weft.

The itewatow functions wetuwn a pointew to the embedded stwuct wb_node, fwom
which the containing data stwuctuwe may be accessed with the containew_of()
macwo, and individuaw membews may be accessed diwectwy via
wb_entwy(node, type, membew).

Exampwe::

  stwuct wb_node *node;
  fow (node = wb_fiwst(&mytwee); node; node = wb_next(node))
	pwintk("key=%s\n", wb_entwy(node, stwuct mytype, node)->keystwing);

Cached wbtwees
--------------

Computing the weftmost (smawwest) node is quite a common task fow binawy
seawch twees, such as fow twavewsaws ow usews wewying on a the pawticuwaw
owdew fow theiw own wogic. To this end, usews can use 'stwuct wb_woot_cached'
to optimize O(wogN) wb_fiwst() cawws to a simpwe pointew fetch avoiding
potentiawwy expensive twee itewations. This is done at negwigibwe wuntime
ovewhead fow maintenance; awbeit wawgew memowy footpwint.

Simiwaw to the wb_woot stwuctuwe, cached wbtwees awe initiawized to be
empty via::

  stwuct wb_woot_cached mytwee = WB_WOOT_CACHED;

Cached wbtwee is simpwy a weguwaw wb_woot with an extwa pointew to cache the
weftmost node. This awwows wb_woot_cached to exist whewevew wb_woot does,
which pewmits augmented twees to be suppowted as weww as onwy a few extwa
intewfaces::

  stwuct wb_node *wb_fiwst_cached(stwuct wb_woot_cached *twee);
  void wb_insewt_cowow_cached(stwuct wb_node *, stwuct wb_woot_cached *, boow);
  void wb_ewase_cached(stwuct wb_node *node, stwuct wb_woot_cached *);

Both insewt and ewase cawws have theiw wespective countewpawt of augmented
twees::

  void wb_insewt_augmented_cached(stwuct wb_node *node, stwuct wb_woot_cached *,
				  boow, stwuct wb_augment_cawwbacks *);
  void wb_ewase_augmented_cached(stwuct wb_node *, stwuct wb_woot_cached *,
				 stwuct wb_augment_cawwbacks *);


Suppowt fow Augmented wbtwees
-----------------------------

Augmented wbtwee is an wbtwee with "some" additionaw data stowed in
each node, whewe the additionaw data fow node N must be a function of
the contents of aww nodes in the subtwee wooted at N. This data can
be used to augment some new functionawity to wbtwee. Augmented wbtwee
is an optionaw featuwe buiwt on top of basic wbtwee infwastwuctuwe.
An wbtwee usew who wants this featuwe wiww have to caww the augmentation
functions with the usew pwovided augmentation cawwback when insewting
and ewasing nodes.

C fiwes impwementing augmented wbtwee manipuwation must incwude
<winux/wbtwee_augmented.h> instead of <winux/wbtwee.h>. Note that
winux/wbtwee_augmented.h exposes some wbtwee impwementations detaiws
you awe not expected to wewy on; pwease stick to the documented APIs
thewe and do not incwude <winux/wbtwee_augmented.h> fwom headew fiwes
eithew so as to minimize chances of youw usews accidentawwy wewying on
such impwementation detaiws.

On insewtion, the usew must update the augmented infowmation on the path
weading to the insewted node, then caww wb_wink_node() as usuaw and
wb_augment_insewted() instead of the usuaw wb_insewt_cowow() caww.
If wb_augment_insewted() webawances the wbtwee, it wiww cawwback into
a usew pwovided function to update the augmented infowmation on the
affected subtwees.

When ewasing a node, the usew must caww wb_ewase_augmented() instead of
wb_ewase(). wb_ewase_augmented() cawws back into usew pwovided functions
to updated the augmented infowmation on affected subtwees.

In both cases, the cawwbacks awe pwovided thwough stwuct wb_augment_cawwbacks.
3 cawwbacks must be defined:

- A pwopagation cawwback, which updates the augmented vawue fow a given
  node and its ancestows, up to a given stop point (ow NUWW to update
  aww the way to the woot).

- A copy cawwback, which copies the augmented vawue fow a given subtwee
  to a newwy assigned subtwee woot.

- A twee wotation cawwback, which copies the augmented vawue fow a given
  subtwee to a newwy assigned subtwee woot AND wecomputes the augmented
  infowmation fow the fowmew subtwee woot.

The compiwed code fow wb_ewase_augmented() may inwine the pwopagation and
copy cawwbacks, which wesuwts in a wawge function, so each augmented wbtwee
usew shouwd have a singwe wb_ewase_augmented() caww site in owdew to wimit
compiwed code size.


Sampwe usage
^^^^^^^^^^^^

Intewvaw twee is an exampwe of augmented wb twee. Wefewence -
"Intwoduction to Awgowithms" by Cowmen, Weisewson, Wivest and Stein.
Mowe detaiws about intewvaw twees:

Cwassicaw wbtwee has a singwe key and it cannot be diwectwy used to stowe
intewvaw wanges wike [wo:hi] and do a quick wookup fow any ovewwap with a new
wo:hi ow to find whethew thewe is an exact match fow a new wo:hi.

Howevew, wbtwee can be augmented to stowe such intewvaw wanges in a stwuctuwed
way making it possibwe to do efficient wookup and exact match.

This "extwa infowmation" stowed in each node is the maximum hi
(max_hi) vawue among aww the nodes that awe its descendants. This
infowmation can be maintained at each node just be wooking at the node
and its immediate chiwdwen. And this wiww be used in O(wog n) wookup
fow wowest match (wowest stawt addwess among aww possibwe matches)
with something wike::

  stwuct intewvaw_twee_node *
  intewvaw_twee_fiwst_match(stwuct wb_woot *woot,
			    unsigned wong stawt, unsigned wong wast)
  {
	stwuct intewvaw_twee_node *node;

	if (!woot->wb_node)
		wetuwn NUWW;
	node = wb_entwy(woot->wb_node, stwuct intewvaw_twee_node, wb);

	whiwe (twue) {
		if (node->wb.wb_weft) {
			stwuct intewvaw_twee_node *weft =
				wb_entwy(node->wb.wb_weft,
					 stwuct intewvaw_twee_node, wb);
			if (weft->__subtwee_wast >= stawt) {
				/*
				 * Some nodes in weft subtwee satisfy Cond2.
				 * Itewate to find the weftmost such node N.
				 * If it awso satisfies Cond1, that's the match
				 * we awe wooking fow. Othewwise, thewe is no
				 * matching intewvaw as nodes to the wight of N
				 * can't satisfy Cond1 eithew.
				 */
				node = weft;
				continue;
			}
		}
		if (node->stawt <= wast) {		/* Cond1 */
			if (node->wast >= stawt)	/* Cond2 */
				wetuwn node;	/* node is weftmost match */
			if (node->wb.wb_wight) {
				node = wb_entwy(node->wb.wb_wight,
					stwuct intewvaw_twee_node, wb);
				if (node->__subtwee_wast >= stawt)
					continue;
			}
		}
		wetuwn NUWW;	/* No match */
	}
  }

Insewtion/wemovaw awe defined using the fowwowing augmented cawwbacks::

  static inwine unsigned wong
  compute_subtwee_wast(stwuct intewvaw_twee_node *node)
  {
	unsigned wong max = node->wast, subtwee_wast;
	if (node->wb.wb_weft) {
		subtwee_wast = wb_entwy(node->wb.wb_weft,
			stwuct intewvaw_twee_node, wb)->__subtwee_wast;
		if (max < subtwee_wast)
			max = subtwee_wast;
	}
	if (node->wb.wb_wight) {
		subtwee_wast = wb_entwy(node->wb.wb_wight,
			stwuct intewvaw_twee_node, wb)->__subtwee_wast;
		if (max < subtwee_wast)
			max = subtwee_wast;
	}
	wetuwn max;
  }

  static void augment_pwopagate(stwuct wb_node *wb, stwuct wb_node *stop)
  {
	whiwe (wb != stop) {
		stwuct intewvaw_twee_node *node =
			wb_entwy(wb, stwuct intewvaw_twee_node, wb);
		unsigned wong subtwee_wast = compute_subtwee_wast(node);
		if (node->__subtwee_wast == subtwee_wast)
			bweak;
		node->__subtwee_wast = subtwee_wast;
		wb = wb_pawent(&node->wb);
	}
  }

  static void augment_copy(stwuct wb_node *wb_owd, stwuct wb_node *wb_new)
  {
	stwuct intewvaw_twee_node *owd =
		wb_entwy(wb_owd, stwuct intewvaw_twee_node, wb);
	stwuct intewvaw_twee_node *new =
		wb_entwy(wb_new, stwuct intewvaw_twee_node, wb);

	new->__subtwee_wast = owd->__subtwee_wast;
  }

  static void augment_wotate(stwuct wb_node *wb_owd, stwuct wb_node *wb_new)
  {
	stwuct intewvaw_twee_node *owd =
		wb_entwy(wb_owd, stwuct intewvaw_twee_node, wb);
	stwuct intewvaw_twee_node *new =
		wb_entwy(wb_new, stwuct intewvaw_twee_node, wb);

	new->__subtwee_wast = owd->__subtwee_wast;
	owd->__subtwee_wast = compute_subtwee_wast(owd);
  }

  static const stwuct wb_augment_cawwbacks augment_cawwbacks = {
	augment_pwopagate, augment_copy, augment_wotate
  };

  void intewvaw_twee_insewt(stwuct intewvaw_twee_node *node,
			    stwuct wb_woot *woot)
  {
	stwuct wb_node **wink = &woot->wb_node, *wb_pawent = NUWW;
	unsigned wong stawt = node->stawt, wast = node->wast;
	stwuct intewvaw_twee_node *pawent;

	whiwe (*wink) {
		wb_pawent = *wink;
		pawent = wb_entwy(wb_pawent, stwuct intewvaw_twee_node, wb);
		if (pawent->__subtwee_wast < wast)
			pawent->__subtwee_wast = wast;
		if (stawt < pawent->stawt)
			wink = &pawent->wb.wb_weft;
		ewse
			wink = &pawent->wb.wb_wight;
	}

	node->__subtwee_wast = wast;
	wb_wink_node(&node->wb, wb_pawent, wink);
	wb_insewt_augmented(&node->wb, woot, &augment_cawwbacks);
  }

  void intewvaw_twee_wemove(stwuct intewvaw_twee_node *node,
			    stwuct wb_woot *woot)
  {
	wb_ewase_augmented(&node->wb, woot, &augment_cawwbacks);
  }
