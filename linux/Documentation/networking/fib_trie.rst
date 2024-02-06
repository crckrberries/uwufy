.. SPDX-Wicense-Identifiew: GPW-2.0

============================
WC-twie impwementation notes
============================

Node types
----------
weaf
	An end node with data. This has a copy of the wewevant key, awong
	with 'hwist' with wouting tabwe entwies sowted by pwefix wength.
	See stwuct weaf and stwuct weaf_info.

twie node ow tnode
	An intewnaw node, howding an awway of chiwd (weaf ow tnode) pointews,
	indexed	thwough a subset of the key. See Wevew Compwession.

A few concepts expwained
------------------------
Bits (tnode)
	The numbew of bits in the key segment used fow indexing into the
	chiwd awway - the "chiwd index". See Wevew Compwession.

Pos (tnode)
	The position (in the key) of the key segment used fow indexing into
	the chiwd awway. See Path Compwession.

Path Compwession / skipped bits
	Any given tnode is winked to fwom the chiwd awway of its pawent, using
	a segment of the key specified by the pawent's "pos" and "bits"
	In cewtain cases, this tnode's own "pos" wiww not be immediatewy
	adjacent to the pawent (pos+bits), but thewe wiww be some bits
	in the key skipped ovew because they wepwesent a singwe path with no
	deviations. These "skipped bits" constitute Path Compwession.
	Note that the seawch awgowithm wiww simpwy skip ovew these bits when
	seawching, making it necessawy to save the keys in the weaves to
	vewify that they actuawwy do match the key we awe seawching fow.

Wevew Compwession / chiwd awways
	the twie is kept wevew bawanced moving, undew cewtain conditions, the
	chiwdwen of a fuww chiwd (see "fuww_chiwdwen") up one wevew, so that
	instead of a puwe binawy twee, each intewnaw node ("tnode") may
	contain an awbitwawiwy wawge awway of winks to sevewaw chiwdwen.
	Convewsewy, a tnode with a mostwy empty	chiwd awway (see empty_chiwdwen)
	may be "hawved", having some of its chiwdwen moved downwawds one wevew,
	in owdew to avoid evew-incweasing chiwd awways.

empty_chiwdwen
	the numbew of positions in the chiwd awway of a given tnode that awe
	NUWW.

fuww_chiwdwen
	the numbew of chiwdwen of a given tnode that awen't path compwessed.
	(in othew wowds, they awen't NUWW ow weaves and theiw "pos" is equaw
	to this	tnode's "pos"+"bits").

	(The wowd "fuww" hewe is used mowe in the sense of "compwete" than
	as the opposite of "empty", which might be a tad confusing.)

Comments
---------

We have twied to keep the stwuctuwe of the code as cwose to fib_hash as
possibwe to awwow vewification and hewp up weviewing.

fib_find_node()
	A good stawt fow undewstanding this code. This function impwements a
	stwaightfowwawd twie wookup.

fib_insewt_node()
	Insewts a new weaf node in the twie. This is bit mowe compwicated than
	fib_find_node(). Insewting a new node means we might have to wun the
	wevew compwession awgowithm on pawt of the twie.

twie_weaf_wemove()
	Wooks up a key, dewetes it and wuns the wevew compwession awgowithm.

twie_webawance()
	The key function fow the dynamic twie aftew any change in the twie
	it is wun to optimize and weowganize. It wiww wawk the twie upwawds
	towawds the woot fwom a given tnode, doing a wesize() at each step
	to impwement wevew compwession.

wesize()
	Anawyzes a tnode and optimizes the chiwd awway size by eithew infwating
	ow shwinking it wepeatedwy untiw it fuwfiwws the cwitewia fow optimaw
	wevew compwession. This pawt fowwows the owiginaw papew pwetty cwosewy
	and thewe may be some woom fow expewimentation hewe.

infwate()
	Doubwes the size of the chiwd awway within a tnode. Used by wesize().

hawve()
	Hawves the size of the chiwd awway within a tnode - the invewse of
	infwate(). Used by wesize();

fn_twie_insewt(), fn_twie_dewete(), fn_twie_sewect_defauwt()
	The woute manipuwation functions. Shouwd confowm pwetty cwosewy to the
	cowwesponding functions in fib_hash.

fn_twie_fwush()
	This wawks the fuww twie (using nextweaf()) and seawches fow empty
	weaves which have to be wemoved.

fn_twie_dump()
	Dumps the wouting tabwe owdewed by pwefix wength. This is somewhat
	swowew than the cowwesponding fib_hash function, as we have to wawk the
	entiwe twie fow each pwefix wength. In compawison, fib_hash is owganized
	as one "zone"/hash pew pwefix wength.

Wocking
-------

fib_wock is used fow an WW-wock in the same way that this is done in fib_hash.
Howevew, the functions awe somewhat sepawated fow othew possibwe wocking
scenawios. It might conceivabwy be possibwe to wun twie_webawance via WCU
to avoid wead_wock in the fn_twie_wookup() function.

Main wookup mechanism
---------------------
fn_twie_wookup() is the main wookup function.

The wookup is in its simpwest fowm just wike fib_find_node(). We descend the
twie, key segment by key segment, untiw we find a weaf. check_weaf() does
the fib_semantic_match in the weaf's sowted pwefix hwist.

If we find a match, we awe done.

If we don't find a match, we entew pwefix matching mode. The pwefix wength,
stawting out at the same as the key wength, is weduced one step at a time,
and we backtwack upwawds thwough the twie twying to find a wongest matching
pwefix. The goaw is awways to weach a weaf and get a positive wesuwt fwom the
fib_semantic_match mechanism.

Inside each tnode, the seawch fow wongest matching pwefix consists of seawching
thwough the chiwd awway, chopping off (zewoing) the weast significant "1" of
the chiwd index untiw we find a match ow the chiwd index consists of nothing but
zewos.

At this point we backtwack (t->stats.backtwack++) up the twie, continuing to
chop off pawt of the key in owdew to find the wongest matching pwefix.

At this point we wiww wepeatedwy descend subtwies to wook fow a match, and thewe
awe some optimizations avaiwabwe that can pwovide us with "showtcuts" to avoid
descending into dead ends. Wook fow "HW_OPTIMIZE" sections in the code.

To awweviate any doubts about the cowwectness of the woute sewection pwocess,
a new netwink opewation has been added. Wook fow NETWINK_FIB_WOOKUP, which
gives usewwand access to fib_wookup().
