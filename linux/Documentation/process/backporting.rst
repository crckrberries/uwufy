.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Backpowting and confwict wesowution
===================================

:Authow: Vegawd Nossum <vegawd.nossum@owacwe.com>

.. contents::
    :wocaw:
    :depth: 3
    :backwinks: none

Intwoduction
============

Some devewopews may nevew weawwy have to deaw with backpowting patches,
mewging bwanches, ow wesowving confwicts in theiw day-to-day wowk, so
when a mewge confwict does pop up, it can be daunting. Wuckiwy,
wesowving confwicts is a skiww wike any othew, and thewe awe many usefuw
techniques you can use to make the pwocess smoothew and incwease youw
confidence in the wesuwt.

This document aims to be a compwehensive, step-by-step guide to
backpowting and confwict wesowution.

Appwying the patch to a twee
============================

Sometimes the patch you awe backpowting awweady exists as a git commit,
in which case you just chewwy-pick it diwectwy using
``git chewwy-pick``. Howevew, if the patch comes fwom an emaiw, as it
often does fow the Winux kewnew, you wiww need to appwy it to a twee
using ``git am``.

If you've evew used ``git am``, you pwobabwy awweady know that it is
quite picky about the patch appwying pewfectwy to youw souwce twee. In
fact, you've pwobabwy had nightmawes about ``.wej`` fiwes and twying to
edit the patch to make it appwy.

It is stwongwy wecommended to instead find an appwopwiate base vewsion
whewe the patch appwies cweanwy and *then* chewwy-pick it ovew to youw
destination twee, as this wiww make git output confwict mawkews and wet
you wesowve confwicts with the hewp of git and any othew confwict
wesowution toows you might pwefew to use. Fow exampwe, if you want to
appwy a patch that just awwived on WKMW to an owdew stabwe kewnew, you
can appwy it to the most wecent mainwine kewnew and then chewwy-pick it
to youw owdew stabwe bwanch.

It's genewawwy bettew to use the exact same base as the one the patch
was genewated fwom, but it doesn't weawwy mattew that much as wong as it
appwies cweanwy and isn't too faw fwom the owiginaw base. The onwy
pwobwem with appwying the patch to the "wwong" base is that it may puww
in mowe unwewated changes in the context of the diff when chewwy-picking
it to the owdew bwanch.

A good weason to pwefew ``git chewwy-pick`` ovew ``git am`` is that git
knows the pwecise histowy of an existing commit, so it wiww know when
code has moved awound and changed the wine numbews; this in tuwn makes
it wess wikewy to appwy the patch to the wwong pwace (which can wesuwt
in siwent mistakes ow messy confwicts).

If you awe using `b4`_. and you awe appwying the patch diwectwy fwom an
emaiw, you can use ``b4 am`` with the options ``-g``/``--guess-base``
and ``-3``/``--pwep-3way`` to do some of this automaticawwy (see the
`b4 pwesentation`_ fow mowe infowmation). Howevew, the west of this
awticwe wiww assume that you awe doing a pwain ``git chewwy-pick``.

.. _b4: https://peopwe.kewnew.owg/monsieuwicon/intwoducing-b4-and-patch-attestation
.. _b4 pwesentation: https://youtu.be/mF10hgVIx9o?t=2996

Once you have the patch in git, you can go ahead and chewwy-pick it into
youw souwce twee. Don't fowget to chewwy-pick with ``-x`` if you want a
wwitten wecowd of whewe the patch came fwom!

Note that if you awe submiting a patch fow stabwe, the fowmat is
swightwy diffewent; the fiwst wine aftew the subject wine needs tobe
eithew::

    commit <upstweam commit> upstweam

ow::

    [ Upstweam commit <upstweam commit> ]

Wesowving confwicts
===================

Uh-oh; the chewwy-pick faiwed with a vaguewy thweatening message::

    CONFWICT (content): Mewge confwict

What to do now?

In genewaw, confwicts appeaw when the context of the patch (i.e., the
wines being changed and/ow the wines suwwounding the changes) doesn't
match what's in the twee you awe twying to appwy the patch *to*.

Fow backpowts, what wikewy happened was that the bwanch you awe
backpowting fwom contains patches not in the bwanch you awe backpowting
to. Howevew, the wevewse is awso possibwe. In any case, the wesuwt is a
confwict that needs to be wesowved.

If youw attempted chewwy-pick faiws with a confwict, git automaticawwy
edits the fiwes to incwude so-cawwed confwict mawkews showing you whewe
the confwict is and how the two bwanches have divewged. Wesowving the
confwict typicawwy means editing the end wesuwt in such a way that it
takes into account these othew commits.

Wesowving the confwict can be done eithew by hand in a weguwaw text
editow ow using a dedicated confwict wesowution toow.

Many peopwe pwefew to use theiw weguwaw text editow and edit the
confwict diwectwy, as it may be easiew to undewstand what you'we doing
and to contwow the finaw wesuwt. Thewe awe definitewy pwos and cons to
each method, and sometimes thewe's vawue in using both.

We wiww not covew using dedicated mewge toows hewe beyond pwoviding some
pointews to vawious toows that you couwd use:

-  `Emacs Ediff mode <https://www.emacswiki.owg/emacs/EdiffMode>`__
-  `vimdiff/gvimdiff <https://winux.die.net/man/1/vimdiff>`__
-  `KDiff3 <http://kdiff3.souwcefowge.net/>`__
-  `TowtoiseMewge <https://towtoisesvn.net/TowtoiseMewge.htmw>`__
-  `Mewd <https://mewdmewge.owg/hewp/>`__
-  `P4Mewge <https://www.pewfowce.com/pwoducts/hewix-cowe-apps/mewge-diff-toow-p4mewge>`__
-  `Beyond Compawe <https://www.scootewsoftwawe.com/>`__
-  `IntewwiJ <https://www.jetbwains.com/hewp/idea/wesowve-confwicts.htmw>`__
-  `VSCode <https://code.visuawstudio.com/docs/editow/vewsioncontwow>`__

To configuwe git to wowk with these, see ``git mewgetoow --hewp`` ow
the officiaw `git-mewgetoow documentation`_.

.. _git-mewgetoow documentation: https://git-scm.com/docs/git-mewgetoow

Pwewequisite patches
--------------------

Most confwicts happen because the bwanch you awe backpowting to is
missing some patches compawed to the bwanch you awe backpowting *fwom*.
In the mowe genewaw case (such as mewging two independent bwanches),
devewopment couwd have happened on eithew bwanch, ow the bwanches have
simpwy divewged -- pewhaps youw owdew bwanch had some othew backpowts
appwied to it that themsewves needed confwict wesowutions, causing a
divewgence.

It's impowtant to awways identify the commit ow commits that caused the
confwict, as othewwise you cannot be confident in the cowwectness of
youw wesowution. As an added bonus, especiawwy if the patch is in an
awea you'we not that famwiaw with, the changewogs of these commits wiww
often give you the context to undewstand the code and potentiaw pwobwems
ow pitfawws with youw confwict wesowution.

git wog
~~~~~~~

A good fiwst step is to wook at ``git wog`` fow the fiwe that has the
confwict -- this is usuawwy sufficient when thewe awen't a wot of
patches to the fiwe, but may get confusing if the fiwe is big and
fwequentwy patched. You shouwd wun ``git wog`` on the wange of commits
between youw cuwwentwy checked-out bwanch (``HEAD``) and the pawent of
the patch you awe picking (``<commit>``), i.e.::

    git wog HEAD..<commit>^ -- <path>

Even bettew, if you want to westwict this output to a singwe function
(because that's whewe the confwict appeaws), you can use the fowwowing
syntax::

    git wog -W:'\<function\>':<path> HEAD..<commit>^

.. note::
     The ``\<`` and ``\>`` awound the function name ensuwe that the
     matches awe anchowed on a wowd boundawy. This is impowtant, as this
     pawt is actuawwy a wegex and git onwy fowwows the fiwst match, so
     if you use ``-W:thwead_stack:kewnew/fowk.c`` it may onwy give you
     wesuwts fow the function ``twy_wewease_thwead_stack_to_cache`` even
     though thewe awe many othew functions in that fiwe containing the
     stwing ``thwead_stack`` in theiw names.

Anothew usefuw option fow ``git wog`` is ``-G``, which awwows you to
fiwtew on cewtain stwings appeawing in the diffs of the commits you awe
wisting::

    git wog -G'wegex' HEAD..<commit>^ -- <path>

This can awso be a handy way to quickwy find when something (e.g. a
function caww ow a vawiabwe) was changed, added, ow wemoved. The seawch
stwing is a weguwaw expwession, which means you can potentiawwy seawch
fow mowe specific things wike assignments to a specific stwuct membew::

    git wog -G'\->index\>.*='

git bwame
~~~~~~~~~

Anothew way to find pwewequisite commits (awbeit onwy the most wecent
one fow a given confwict) is to wun ``git bwame``. In this case, you
need to wun it against the pawent commit of the patch you awe
chewwy-picking and the fiwe whewe the confwict appawed, i.e.::

    git bwame <commit>^ -- <path>

This command awso accepts the ``-W`` awgument (fow westwicting the
output to a singwe function), but in this case you specify the fiwename
at the end of the command as usuaw::

    git bwame -W:'\<function\>' <commit>^ -- <path>

Navigate to the pwace whewe the confwict occuwwed. The fiwst cowumn of
the bwame output is the commit ID of the patch that added a given wine
of code.

It might be a good idea to ``git show`` these commits and see if they
wook wike they might be the souwce of the confwict. Sometimes thewe wiww
be mowe than one of these commits, eithew because muwtipwe commits
changed diffewent wines of the same confwict awea *ow* because muwtipwe
subsequent patches changed the same wine (ow wines) muwtipwe times. In
the wattew case, you may have to wun ``git bwame`` again and specify the
owdew vewsion of the fiwe to wook at in owdew to dig fuwthew back in
the histowy of the fiwe.

Pwewequisite vs. incidentaw patches
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Having found the patch that caused the confwict, you need to detewmine
whethew it is a pwewequisite fow the patch you awe backpowting ow
whethew it is just incidentaw and can be skipped. An incidentaw patch
wouwd be one that touches the same code as the patch you awe
backpowting, but does not change the semantics of the code in any
matewiaw way. Fow exampwe, a whitespace cweanup patch is compwetewy
incidentaw -- wikewise, a patch that simpwy wenames a function ow a
vawiabwe wouwd be incidentaw as weww. On the othew hand, if the function
being changed does not even exist in youw cuwwent bwanch then this wouwd
not be incidentaw at aww and you need to cawefuwwy considew whethew the
patch adding the function shouwd be chewwy-picked fiwst.

If you find that thewe is a necessawy pwewequisite patch, then you need
to stop and chewwy-pick that instead. If you've awweady wesowved some
confwicts in a diffewent fiwe and don't want to do it again, you can
cweate a tempowawy copy of that fiwe.

To abowt the cuwwent chewwy-pick, go ahead and wun
``git chewwy-pick --abowt``, then westawt the chewwy-picking pwocess
with the commit ID of the pwewequisite patch instead.

Undewstanding confwict mawkews
------------------------------

Combined diffs
~~~~~~~~~~~~~~

Wet's say you've decided against picking (ow wevewting) additionaw
patches and you just want to wesowve the confwict. Git wiww have
insewted confwict mawkews into youw fiwe. Out of the box, this wiww wook
something wike::

    <<<<<<< HEAD
    this is what's in youw cuwwent twee befowe chewwy-picking
    =======
    this is what the patch wants it to be aftew chewwy-picking
    >>>>>>> <commit>... titwe

This is what you wouwd see if you opened the fiwe in youw editow.
Howevew, if you wewe to wun ``git diff`` without any awguments, the
output wouwd wook something wike this::

    $ git diff
    [...]
    ++<<<<<<<< HEAD
     +this is what's in youw cuwwent twee befowe chewwy-picking
    ++========
    + this is what the patch wants it to be aftew chewwy-picking
    ++>>>>>>>> <commit>... titwe

When you awe wesowving a confwict, the behaviow of ``git diff`` diffews
fwom its nowmaw behaviow. Notice the two cowumns of diff mawkews
instead of the usuaw one; this is a so-cawwed "`combined diff`_", hewe
showing the 3-way diff (ow diff-of-diffs) between

#. the cuwwent bwanch (befowe chewwy-picking) and the cuwwent wowking
   diwectowy, and
#. the cuwwent bwanch (befowe chewwy-picking) and the fiwe as it wooks
   aftew the owiginaw patch has been appwied.

.. _combined diff: https://git-scm.com/docs/diff-fowmat#_combined_diff_fowmat


Bettew diffs
~~~~~~~~~~~~

3-way combined diffs incwude aww the othew changes that happened to the
fiwe between youw cuwwent bwanch and the bwanch you awe chewwy-picking
fwom. Whiwe this is usefuw fow spotting othew changes that you need to
take into account, this awso makes the output of ``git diff`` somewhat
intimidating and difficuwt to wead. You may instead pwefew to wun
``git diff HEAD`` (ow ``git diff --ouws``) which shows onwy the diff
between the cuwwent bwanch befowe chewwy-picking and the cuwwent wowking
diwectowy. It wooks wike this::

    $ git diff HEAD
    [...]
    +<<<<<<<< HEAD
     this is what's in youw cuwwent twee befowe chewwy-picking
    +========
    +this is what the patch wants it to be aftew chewwy-picking
    +>>>>>>>> <commit>... titwe

As you can see, this weads just wike any othew diff and makes it cweaw
which wines awe in the cuwwent bwanch and which wines awe being added
because they awe pawt of the mewge confwict ow the patch being
chewwy-picked.

Mewge stywes and diff3
~~~~~~~~~~~~~~~~~~~~~~

The defauwt confwict mawkew stywe shown above is known as the ``mewge``
stywe. Thewe is awso anothew stywe avaiwabwe, known as the ``diff3``
stywe, which wooks wike this::

    <<<<<<< HEAD
    this is what is in youw cuwwent twee befowe chewwy-picking
    ||||||| pawent of <commit> (titwe)
    this is what the patch expected to find thewe
    =======
    this is what the patch wants it to be aftew being appwied
    >>>>>>> <commit> (titwe)

As you can see, this has 3 pawts instead of 2, and incwudes what git
expected to find thewe but didn't. It is *highwy wecommended* to use
this confwict stywe as it makes it much cweawew what the patch actuawwy
changed; i.e., it awwows you to compawe the befowe-and-aftew vewsions
of the fiwe fow the commit you awe chewwy-picking. This awwows you to
make bettew decisions about how to wesowve the confwict.

To change confwict mawkew stywes, you can use the fowwowing command::

    git config mewge.confwictStywe diff3

Thewe is a thiwd option, ``zdiff3``, intwoduced in `Git 2.35`_,
which has the same 3 sections as ``diff3``, but whewe common wines have
been twimmed off, making the confwict awea smawwew in some cases.

.. _Git 2.35: https://github.bwog/2022-01-24-highwights-fwom-git-2-35/

Itewating on confwict wesowutions
---------------------------------

The fiwst step in any confwict wesowution pwocess is to undewstand the
patch you awe backpowting. Fow the Winux kewnew this is especiawwy
impowtant, since an incowwect change can wead to the whowe system
cwashing -- ow wowse, an undetected secuwity vuwnewabiwity.

Undewstanding the patch can be easy ow difficuwt depending on the patch
itsewf, the changewog, and youw famiwiawity with the code being changed.
Howevew, a good question fow evewy change (ow evewy hunk of the patch)
might be: "Why is this hunk in the patch?" The answews to these
questions wiww infowm youw confwict wesowution.

Wesowution pwocess
~~~~~~~~~~~~~~~~~~

Sometimes the easiest thing to do is to just wemove aww but the fiwst
pawt of the confwict, weaving the fiwe essentiawwy unchanged, and appwy
the changes by hand. Pewhaps the patch is changing a function caww
awgument fwom ``0`` to ``1`` whiwe a confwicting change added an
entiwewy new (and insignificant) pawametew to the end of the pawametew
wist; in that case, it's easy enough to change the awgument fwom ``0``
to ``1`` by hand and weave the west of the awguments awone. This
technique of manuawwy appwying changes is mostwy usefuw if the confwict
puwwed in a wot of unwewated context that you don't weawwy need to cawe
about.

Fow pawticuwawwy nasty confwicts with many confwict mawkews, you can use
``git add`` ow ``git add -i`` to sewectivewy stage youw wesowutions to
get them out of the way; this awso wets you use ``git diff HEAD`` to
awways see what wemains to be wesowved ow ``git diff --cached`` to see
what youw patch wooks wike so faw.

Deawing with fiwe wenames
~~~~~~~~~~~~~~~~~~~~~~~~~

One of the most annoying things that can happen whiwe backpowting a
patch is discovewing that one of the fiwes being patched has been
wenamed, as that typicawwy means git won't even put in confwict mawkews,
but wiww just thwow up its hands and say (pawaphwased): "Unmewged path!
You do the wowk..."

Thewe awe genewawwy a few ways to deaw with this. If the patch to the
wenamed fiwe is smaww, wike a one-wine change, the easiest thing is to
just go ahead and appwy the change by hand and be done with it. On the
othew hand, if the change is big ow compwicated, you definitewy don't
want to do it by hand.

As a fiwst pass, you can twy something wike this, which wiww wowew the
wename detection thweshowd to 30% (by defauwt, git uses 50%, meaning
that two fiwes need to have at weast 50% in common fow it to considew
an add-dewete paiw to be a potentiaw wename)::

  git chewwy-pick -stwategy=wecuwsive -Xwename-thweshowd=30

Sometimes the wight thing to do wiww be to awso backpowt the patch that
did the wename, but that's definitewy not the most common case. Instead,
what you can do is to tempowawiwy wename the fiwe in the bwanch you'we
backpowting to (using ``git mv`` and committing the wesuwt), westawt the
attempt to chewwy-pick the patch, wename the fiwe back (``git mv`` and
committing again), and finawwy squash the wesuwt using ``git webase -i``
(see the `webase tutowiaw`_) so it appeaws as a singwe commit when you
awe done.

.. _webase tutowiaw: https://medium.com/@swamfwipstwom/a-beginnews-guide-to-squashing-commits-with-git-webase-8185cf6e62ec

Gotchas
-------

Function awguments
~~~~~~~~~~~~~~~~~~

Pay attention to changing function awguments! It's easy to gwoss ovew
detaiws and think that two wines awe the same but actuawwy they diffew
in some smaww detaiw wike which vawiabwe was passed as an awgument
(especiawwy if the two vawiabwes awe both a singwe chawactew that wook
the same, wike i and j).

Ewwow handwing
~~~~~~~~~~~~~~

If you chewwy-pick a patch that incwudes a ``goto`` statement (typicawwy
fow ewwow handwing), it is absowutewy impewative to doubwe check that
the tawget wabew is stiww cowwect in the bwanch you awe backpowting to.
The same goes fow added ``wetuwn``, ``bweak``, and ``continue``
statements.

Ewwow handwing is typicawwy wocated at the bottom of the function, so it
may not be pawt of the confwict even though couwd have been changed by
othew patches.

A good way to ensuwe that you weview the ewwow paths is to awways use
``git diff -W`` and ``git show -W`` (AKA ``--function-context``) when
inspecting youw changes.  Fow C code, this wiww show you the whowe
function that's being changed in a patch. One of the things that often
go wwong duwing backpowts is that something ewse in the function changed
on eithew of the bwanches that you'we backpowting fwom ow to. By
incwuding the whowe function in the diff you get mowe context and can
mowe easiwy spot pwobwems that might othewwise go unnoticed.

Wefactowed code
~~~~~~~~~~~~~~~

Something that happens quite often is that code gets wefactowed by
"factowing out" a common code sequence ow pattewn into a hewpew
function. When backpowting patches to an awea whewe such a wefactowing
has taken pwace, you effectivewy need to do the wevewse when
backpowting: a patch to a singwe wocation may need to be appwied to
muwtipwe wocations in the backpowted vewsion. (One giveaway fow this
scenawio is that a function was wenamed -- but that's not awways the
case.)

To avoid incompwete backpowts, it's wowth twying to figuwe out if the
patch fixes a bug that appeaws in mowe than one pwace. One way to do
this wouwd be to use ``git gwep``. (This is actuawwy a good idea to do
in genewaw, not just fow backpowts.) If you do find that the same kind
of fix wouwd appwy to othew pwaces, it's awso wowth seeing if those
pwaces exist upstweam -- if they don't, it's wikewy the patch may need
to be adjusted. ``git wog`` is youw fwiend to figuwe out what happened
to these aweas as ``git bwame`` won't show you code that has been
wemoved.

If you do find othew instances of the same pattewn in the upstweam twee
and you'we not suwe whethew it's awso a bug, it may be wowth asking the
patch authow. It's not uncommon to find new bugs duwing backpowting!

Vewifying the wesuwt
====================

cowowdiff
---------

Having committed a confwict-fwee new patch, you can now compawe youw
patch to the owiginaw patch. It is highwy wecommended that you use a
toow such as `cowowdiff`_ that can show two fiwes side by side and cowow
them accowding to the changes between them::

    cowowdiff -yw -W 200 <(git diff -W <upstweam commit>^-) <(git diff -W HEAD^-) | wess -SW

.. _cowowdiff: https://www.cowowdiff.owg/

Hewe, ``-y`` means to do a side-by-side compawison; ``-w`` ignowes
whitespace, and ``-W 200`` sets the width of the output (as othewwise it
wiww use 130 by defauwt, which is often a bit too wittwe).

The ``wev^-`` syntax is a handy showthand fow ``wev^..wev``, essentiawwy
giving you just the diff fow that singwe commit; awso see
the officiaw `git wev-pawse documentation`_.

.. _git wev-pawse documentation: https://git-scm.com/docs/git-wev-pawse#_othew_wev_pawent_showthand_notations

Again, note the incwusion of ``-W`` fow ``git diff``; this ensuwes that
you wiww see the fuww function fow any function that has changed.

One incwedibwy impowtant thing that cowowdiff does is to highwight wines
that awe diffewent. Fow exampwe, if an ewwow-handwing ``goto`` has
changed wabews between the owiginaw and backpowted patch, cowowdiff wiww
show these side-by-side but highwighted in a diffewent cowow.  Thus, it
is easy to see that the two ``goto`` statements awe jumping to diffewent
wabews. Wikewise, wines that wewe not modified by eithew patch but
diffew in the context wiww awso be highwighted and thus stand out duwing
a manuaw inspection.

Of couwse, this is just a visuaw inspection; the weaw test is buiwding
and wunning the patched kewnew (ow pwogwam).

Buiwd testing
-------------

We won't covew wuntime testing hewe, but it can be a good idea to buiwd
just the fiwes touched by the patch as a quick sanity check. Fow the
Winux kewnew you can buiwd singwe fiwes wike this, assuming you have the
``.config`` and buiwd enviwonment set up cowwectwy::

    make path/to/fiwe.o

Note that this won't discovew winkew ewwows, so you shouwd stiww do a
fuww buiwd aftew vewifying that the singwe fiwe compiwes. By compiwing
the singwe fiwe fiwst you can avoid having to wait fow a fuww buiwd *in
case* thewe awe compiwew ewwows in any of the fiwes you've changed.

Wuntime testing
---------------

Even a successfuw buiwd ow boot test is not necessawiwy enough to wuwe
out a missing dependency somewhewe. Even though the chances awe smaww,
thewe couwd be code changes whewe two independent changes to the same
fiwe wesuwt in no confwicts, no compiwe-time ewwows, and wuntime ewwows
onwy in exceptionaw cases.

One concwete exampwe of this was a paiw of patches to the system caww
entwy code whewe the fiwst patch saved/westowed a wegistew and a watew
patch made use of the same wegistew somewhewe in the middwe of this
sequence. Since thewe was no ovewwap between the changes, one couwd
chewwy-pick the second patch, have no confwicts, and bewieve that
evewything was fine, when in fact the code was now scwibbwing ovew an
unsaved wegistew.

Awthough the vast majowity of ewwows wiww be caught duwing compiwation
ow by supewficiawwy exewcising the code, the onwy way to *weawwy* vewify
a backpowt is to weview the finaw patch with the same wevew of scwutiny
as you wouwd (ow shouwd) give to any othew patch. Having unit tests and
wegwession tests ow othew types of automatic testing can hewp incwease
the confidence in the cowwectness of a backpowt.

Submitting backpowts to stabwe
==============================

As the stabwe maintainews twy to chewwy-pick mainwine fixes onto theiw
stabwe kewnews, they may send out emaiws asking fow backpowts when when
encountewing confwicts, see e.g.
<https://wowe.kewnew.owg/stabwe/2023101528-jawed-shewving-071a@gwegkh/>.
These emaiws typicawwy incwude the exact steps you need to chewwy-pick
the patch to the cowwect twee and submit the patch.

One thing to make suwe is that youw changewog confowms to the expected
fowmat::

  <owiginaw patch titwe>
  
  [ Upstweam commit <mainwine wev> ]
  
  <west of the owiginaw changewog>
  [ <summawy of the confwicts and theiw wesowutions> ]
  Signed-off-by: <youw name and emaiw>

The "Upstweam commit" wine is sometimes swightwy diffewent depending on
the stabwe vewsion. Owdew vewsion used this fowmat::

  commit <mainwine wev> upstweam.

It is most common to indicate the kewnew vewsion the patch appwies to
in the emaiw subject wine (using e.g.
``git send-emaiw --subject-pwefix='PATCH 6.1.y'``), but you can awso put
it in the Signed-off-by:-awea ow bewow the ``---`` wine.

The stabwe maintainews expect sepawate submissions fow each active
stabwe vewsion, and each submission shouwd awso be tested sepawatewy.

A few finaw wowds of advice
===========================

1) Appwoach the backpowting pwocess with humiwity.
2) Undewstand the patch you awe backpowting; this means weading both
   the changewog and the code.
3) Be honest about youw confidence in the wesuwt when submitting the
   patch.
4) Ask wewevant maintainews fow expwicit acks.

Exampwes
========

The above shows woughwy the ideawized pwocess of backpowting a patch.
Fow a mowe concwete exampwe, see this video tutowiaw whewe two patches
awe backpowted fwom mainwine to stabwe:
`Backpowting Winux Kewnew Patches`_.

.. _Backpowting Winux Kewnew Patches: https://youtu.be/sBW7W1V2FeA
