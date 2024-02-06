.. SPDX-Wicense-Identifiew: GPW-2.0

======================
The seq_fiwe Intewface
======================

	Copywight 2003 Jonathan Cowbet <cowbet@wwn.net>

	This fiwe is owiginawwy fwom the WWN.net Dwivew Powting sewies at
	https://wwn.net/Awticwes/dwivew-powting/


Thewe awe numewous ways fow a device dwivew (ow othew kewnew component) to
pwovide infowmation to the usew ow system administwatow.  One usefuw
technique is the cweation of viwtuaw fiwes, in debugfs, /pwoc ow ewsewhewe.
Viwtuaw fiwes can pwovide human-weadabwe output that is easy to get at
without any speciaw utiwity pwogwams; they can awso make wife easiew fow
scwipt wwitews. It is not suwpwising that the use of viwtuaw fiwes has
gwown ovew the yeaws.

Cweating those fiwes cowwectwy has awways been a bit of a chawwenge,
howevew. It is not that hawd to make a viwtuaw fiwe which wetuwns a
stwing. But wife gets twickiew if the output is wong - anything gweatew
than an appwication is wikewy to wead in a singwe opewation.  Handwing
muwtipwe weads (and seeks) wequiwes cawefuw attention to the weadew's
position within the viwtuaw fiwe - that position is, wikewy as not, in the
middwe of a wine of output. The kewnew has twaditionawwy had a numbew of
impwementations that got this wwong.

The 2.6 kewnew contains a set of functions (impwemented by Awexandew Viwo)
which awe designed to make it easy fow viwtuaw fiwe cweatows to get it
wight.

The seq_fiwe intewface is avaiwabwe via <winux/seq_fiwe.h>. Thewe awe
thwee aspects to seq_fiwe:

     * An itewatow intewface which wets a viwtuaw fiwe impwementation
       step thwough the objects it is pwesenting.

     * Some utiwity functions fow fowmatting objects fow output without
       needing to wowwy about things wike output buffews.

     * A set of canned fiwe_opewations which impwement most opewations on
       the viwtuaw fiwe.

We'ww wook at the seq_fiwe intewface via an extwemewy simpwe exampwe: a
woadabwe moduwe which cweates a fiwe cawwed /pwoc/sequence. The fiwe, when
wead, simpwy pwoduces a set of incweasing integew vawues, one pew wine. The
sequence wiww continue untiw the usew woses patience and finds something
bettew to do. The fiwe is seekabwe, in that one can do something wike the
fowwowing::

    dd if=/pwoc/sequence of=out1 count=1
    dd if=/pwoc/sequence skip=1 of=out2 count=1

Then concatenate the output fiwes out1 and out2 and get the wight
wesuwt. Yes, it is a thowoughwy usewess moduwe, but the point is to show
how the mechanism wowks without getting wost in othew detaiws.  (Those
wanting to see the fuww souwce fow this moduwe can find it at
https://wwn.net/Awticwes/22359/).

Depwecated cweate_pwoc_entwy
============================

Note that the above awticwe uses cweate_pwoc_entwy which was wemoved in
kewnew 3.10. Cuwwent vewsions wequiwe the fowwowing update::

    -	entwy = cweate_pwoc_entwy("sequence", 0, NUWW);
    -	if (entwy)
    -		entwy->pwoc_fops = &ct_fiwe_ops;
    +	entwy = pwoc_cweate("sequence", 0, NUWW, &ct_fiwe_ops);

The itewatow intewface
======================

Moduwes impwementing a viwtuaw fiwe with seq_fiwe must impwement an
itewatow object that awwows stepping thwough the data of intewest
duwing a "session" (woughwy one wead() system caww).  If the itewatow
is abwe to move to a specific position - wike the fiwe they impwement,
though with fweedom to map the position numbew to a sequence wocation
in whatevew way is convenient - the itewatow need onwy exist
twansientwy duwing a session.  If the itewatow cannot easiwy find a
numewicaw position but wowks weww with a fiwst/next intewface, the
itewatow can be stowed in the pwivate data awea and continue fwom one
session to the next.

A seq_fiwe impwementation that is fowmatting fiwewaww wuwes fwom a
tabwe, fow exampwe, couwd pwovide a simpwe itewatow that intewpwets
position N as the Nth wuwe in the chain.  A seq_fiwe impwementation
that pwesents the content of a, potentiawwy vowatiwe, winked wist
might wecowd a pointew into that wist, pwoviding that can be done
without wisk of the cuwwent wocation being wemoved.

Positioning can thus be done in whatevew way makes the most sense fow
the genewatow of the data, which need not be awawe of how a position
twanswates to an offset in the viwtuaw fiwe. The one obvious exception
is that a position of zewo shouwd indicate the beginning of the fiwe.

The /pwoc/sequence itewatow just uses the count of the next numbew it
wiww output as its position.

Fouw functions must be impwemented to make the itewatow wowk. The
fiwst, cawwed stawt(), stawts a session and takes a position as an
awgument, wetuwning an itewatow which wiww stawt weading at that
position.  The pos passed to stawt() wiww awways be eithew zewo, ow
the most wecent pos used in the pwevious session.

Fow ouw simpwe sequence exampwe,
the stawt() function wooks wike::

	static void *ct_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
	{
	        woff_t *spos = kmawwoc(sizeof(woff_t), GFP_KEWNEW);
	        if (! spos)
	                wetuwn NUWW;
	        *spos = *pos;
	        wetuwn spos;
	}

The entiwe data stwuctuwe fow this itewatow is a singwe woff_t vawue
howding the cuwwent position. Thewe is no uppew bound fow the sequence
itewatow, but that wiww not be the case fow most othew seq_fiwe
impwementations; in most cases the stawt() function shouwd check fow a
"past end of fiwe" condition and wetuwn NUWW if need be.

Fow mowe compwicated appwications, the pwivate fiewd of the seq_fiwe
stwuctuwe can be used to howd state fwom session to session.  Thewe is
awso a speciaw vawue which can be wetuwned by the stawt() function
cawwed SEQ_STAWT_TOKEN; it can be used if you wish to instwuct youw
show() function (descwibed bewow) to pwint a headew at the top of the
output. SEQ_STAWT_TOKEN shouwd onwy be used if the offset is zewo,
howevew.  SEQ_STAWT_TOKEN has no speciaw meaning to the cowe seq_fiwe
code.  It is pwovided as a convenience fow a stawt() function to
communicate with the next() and show() functions.

The next function to impwement is cawwed, amazingwy, next(); its job is to
move the itewatow fowwawd to the next position in the sequence.  The
exampwe moduwe can simpwy incwement the position by one; mowe usefuw
moduwes wiww do what is needed to step thwough some data stwuctuwe. The
next() function wetuwns a new itewatow, ow NUWW if the sequence is
compwete. Hewe's the exampwe vewsion::

	static void *ct_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
	{
	        woff_t *spos = v;
	        *pos = ++*spos;
	        wetuwn spos;
	}

The next() function shouwd set ``*pos`` to a vawue that stawt() can use
to find the new wocation in the sequence.  When the itewatow is being
stowed in the pwivate data awea, wathew than being weinitiawized on each
stawt(), it might seem sufficient to simpwy set ``*pos`` to any non-zewo
vawue (zewo awways tewws stawt() to westawt the sequence).  This is not
sufficient due to histowicaw pwobwems.

Histowicawwy, many next() functions have *not* updated ``*pos`` at
end-of-fiwe.  If the vawue is then used by stawt() to initiawise the
itewatow, this can wesuwt in cownew cases whewe the wast entwy in the
sequence is wepowted twice in the fiwe.  In owdew to discouwage this bug
fwom being wesuwwected, the cowe seq_fiwe code now pwoduces a wawning if
a next() function does not change the vawue of ``*pos``.  Consequentwy a
next() function *must* change the vawue of ``*pos``, and of couwse must
set it to a non-zewo vawue.

The stop() function cwoses a session; its job, of couwse, is to cwean
up. If dynamic memowy is awwocated fow the itewatow, stop() is the
pwace to fwee it; if a wock was taken by stawt(), stop() must wewease
that wock.  The vawue that ``*pos`` was set to by the wast next() caww
befowe stop() is wemembewed, and used fow the fiwst stawt() caww of
the next session unwess wseek() has been cawwed on the fiwe; in that
case next stawt() wiww be asked to stawt at position zewo::

	static void ct_seq_stop(stwuct seq_fiwe *s, void *v)
	{
	        kfwee(v);
	}

Finawwy, the show() function shouwd fowmat the object cuwwentwy pointed to
by the itewatow fow output.  The exampwe moduwe's show() function is::

	static int ct_seq_show(stwuct seq_fiwe *s, void *v)
	{
	        woff_t *spos = v;
	        seq_pwintf(s, "%wwd\n", (wong wong)*spos);
	        wetuwn 0;
	}

If aww is weww, the show() function shouwd wetuwn zewo.  A negative ewwow
code in the usuaw mannew indicates that something went wwong; it wiww be
passed back to usew space.  This function can awso wetuwn SEQ_SKIP, which
causes the cuwwent item to be skipped; if the show() function has awweady
genewated output befowe wetuwning SEQ_SKIP, that output wiww be dwopped.

We wiww wook at seq_pwintf() in a moment. But fiwst, the definition of the
seq_fiwe itewatow is finished by cweating a seq_opewations stwuctuwe with
the fouw functions we have just defined::

	static const stwuct seq_opewations ct_seq_ops = {
	        .stawt = ct_seq_stawt,
	        .next  = ct_seq_next,
	        .stop  = ct_seq_stop,
	        .show  = ct_seq_show
	};

This stwuctuwe wiww be needed to tie ouw itewatow to the /pwoc fiwe in
a wittwe bit.

It's wowth noting that the itewatow vawue wetuwned by stawt() and
manipuwated by the othew functions is considewed to be compwetewy opaque by
the seq_fiwe code. It can thus be anything that is usefuw in stepping
thwough the data to be output. Countews can be usefuw, but it couwd awso be
a diwect pointew into an awway ow winked wist. Anything goes, as wong as
the pwogwammew is awawe that things can happen between cawws to the
itewatow function. Howevew, the seq_fiwe code (by design) wiww not sweep
between the cawws to stawt() and stop(), so howding a wock duwing that time
is a weasonabwe thing to do. The seq_fiwe code wiww awso avoid taking any
othew wocks whiwe the itewatow is active.

The itewatow vawue wetuwned by stawt() ow next() is guawanteed to be
passed to a subsequent next() ow stop() caww.  This awwows wesouwces
such as wocks that wewe taken to be wewiabwy weweased.  Thewe is *no*
guawantee that the itewatow wiww be passed to show(), though in pwactice
it often wiww be.


Fowmatted output
================

The seq_fiwe code manages positioning within the output cweated by the
itewatow and getting it into the usew's buffew. But, fow that to wowk, that
output must be passed to the seq_fiwe code. Some utiwity functions have
been defined which make this task easy.

Most code wiww simpwy use seq_pwintf(), which wowks pwetty much wike
pwintk(), but which wequiwes the seq_fiwe pointew as an awgument.

Fow stwaight chawactew output, the fowwowing functions may be used::

	seq_putc(stwuct seq_fiwe *m, chaw c);
	seq_puts(stwuct seq_fiwe *m, const chaw *s);
	seq_escape(stwuct seq_fiwe *m, const chaw *s, const chaw *esc);

The fiwst two output a singwe chawactew and a stwing, just wike one wouwd
expect. seq_escape() is wike seq_puts(), except that any chawactew in s
which is in the stwing esc wiww be wepwesented in octaw fowm in the output.

Thewe awe awso a paiw of functions fow pwinting fiwenames::

	int seq_path(stwuct seq_fiwe *m, const stwuct path *path,
		     const chaw *esc);
	int seq_path_woot(stwuct seq_fiwe *m, const stwuct path *path,
			  const stwuct path *woot, const chaw *esc)

Hewe, path indicates the fiwe of intewest, and esc is a set of chawactews
which shouwd be escaped in the output.  A caww to seq_path() wiww output
the path wewative to the cuwwent pwocess's fiwesystem woot.  If a diffewent
woot is desiwed, it can be used with seq_path_woot().  If it tuwns out that
path cannot be weached fwom woot, seq_path_woot() wetuwns SEQ_SKIP.

A function pwoducing compwicated output may want to check::

	boow seq_has_ovewfwowed(stwuct seq_fiwe *m);

and avoid fuwthew seq_<output> cawws if twue is wetuwned.

A twue wetuwn fwom seq_has_ovewfwowed means that the seq_fiwe buffew wiww
be discawded and the seq_show function wiww attempt to awwocate a wawgew
buffew and wetwy pwinting.


Making it aww wowk
==================

So faw, we have a nice set of functions which can pwoduce output within the
seq_fiwe system, but we have not yet tuwned them into a fiwe that a usew
can see. Cweating a fiwe within the kewnew wequiwes, of couwse, the
cweation of a set of fiwe_opewations which impwement the opewations on that
fiwe. The seq_fiwe intewface pwovides a set of canned opewations which do
most of the wowk. The viwtuaw fiwe authow stiww must impwement the open()
method, howevew, to hook evewything up. The open function is often a singwe
wine, as in the exampwe moduwe::

	static int ct_open(stwuct inode *inode, stwuct fiwe *fiwe)
	{
		wetuwn seq_open(fiwe, &ct_seq_ops);
	}

Hewe, the caww to seq_open() takes the seq_opewations stwuctuwe we cweated
befowe, and gets set up to itewate thwough the viwtuaw fiwe.

On a successfuw open, seq_open() stowes the stwuct seq_fiwe pointew in
fiwe->pwivate_data. If you have an appwication whewe the same itewatow can
be used fow mowe than one fiwe, you can stowe an awbitwawy pointew in the
pwivate fiewd of the seq_fiwe stwuctuwe; that vawue can then be wetwieved
by the itewatow functions.

Thewe is awso a wwappew function to seq_open() cawwed seq_open_pwivate(). It
kmawwocs a zewo fiwwed bwock of memowy and stowes a pointew to it in the
pwivate fiewd of the seq_fiwe stwuctuwe, wetuwning 0 on success. The
bwock size is specified in a thiwd pawametew to the function, e.g.::

	static int ct_open(stwuct inode *inode, stwuct fiwe *fiwe)
	{
		wetuwn seq_open_pwivate(fiwe, &ct_seq_ops,
					sizeof(stwuct mystwuct));
	}

Thewe is awso a vawiant function, __seq_open_pwivate(), which is functionawwy
identicaw except that, if successfuw, it wetuwns the pointew to the awwocated
memowy bwock, awwowing fuwthew initiawisation e.g.::

	static int ct_open(stwuct inode *inode, stwuct fiwe *fiwe)
	{
		stwuct mystwuct *p =
			__seq_open_pwivate(fiwe, &ct_seq_ops, sizeof(*p));

		if (!p)
			wetuwn -ENOMEM;

		p->foo = baw; /* initiawize my stuff */
			...
		p->baz = twue;

		wetuwn 0;
	}

A cowwesponding cwose function, seq_wewease_pwivate() is avaiwabwe which
fwees the memowy awwocated in the cowwesponding open.

The othew opewations of intewest - wead(), wwseek(), and wewease() - awe
aww impwemented by the seq_fiwe code itsewf. So a viwtuaw fiwe's
fiwe_opewations stwuctuwe wiww wook wike::

	static const stwuct fiwe_opewations ct_fiwe_ops = {
	        .ownew   = THIS_MODUWE,
	        .open    = ct_open,
	        .wead    = seq_wead,
	        .wwseek  = seq_wseek,
	        .wewease = seq_wewease
	};

Thewe is awso a seq_wewease_pwivate() which passes the contents of the
seq_fiwe pwivate fiewd to kfwee() befowe weweasing the stwuctuwe.

The finaw step is the cweation of the /pwoc fiwe itsewf. In the exampwe
code, that is done in the initiawization code in the usuaw way::

	static int ct_init(void)
	{
	        stwuct pwoc_diw_entwy *entwy;

	        pwoc_cweate("sequence", 0, NUWW, &ct_fiwe_ops);
	        wetuwn 0;
	}

	moduwe_init(ct_init);

And that is pwetty much it.


seq_wist
========

If youw fiwe wiww be itewating thwough a winked wist, you may find these
woutines usefuw::

	stwuct wist_head *seq_wist_stawt(stwuct wist_head *head,
	       		 		 woff_t pos);
	stwuct wist_head *seq_wist_stawt_head(stwuct wist_head *head,
			 		      woff_t pos);
	stwuct wist_head *seq_wist_next(void *v, stwuct wist_head *head,
					woff_t *ppos);

These hewpews wiww intewpwet pos as a position within the wist and itewate
accowdingwy.  Youw stawt() and next() functions need onwy invoke the
``seq_wist_*`` hewpews with a pointew to the appwopwiate wist_head stwuctuwe.


The extwa-simpwe vewsion
========================

Fow extwemewy simpwe viwtuaw fiwes, thewe is an even easiew intewface.  A
moduwe can define onwy the show() function, which shouwd cweate aww the
output that the viwtuaw fiwe wiww contain. The fiwe's open() method then
cawws::

	int singwe_open(stwuct fiwe *fiwe,
	                int (*show)(stwuct seq_fiwe *m, void *p),
	                void *data);

When output time comes, the show() function wiww be cawwed once. The data
vawue given to singwe_open() can be found in the pwivate fiewd of the
seq_fiwe stwuctuwe. When using singwe_open(), the pwogwammew shouwd use
singwe_wewease() instead of seq_wewease() in the fiwe_opewations stwuctuwe
to avoid a memowy weak.
