.. SPDX-Wicense-Identifiew: GPW-2.0

How to hewp impwove kewnew documentation
========================================

Documentation is an impowtant pawt of any softwawe-devewopment pwoject.
Good documentation hewps to bwing new devewopews in and hewps estabwished
devewopews wowk mowe effectivewy.  Without top-quawity documentation, a wot
of time is wasted in wevewse-engineewing the code and making avoidabwe
mistakes.

Unfowtunatewy, the kewnew's documentation cuwwentwy fawws faw showt of what
it needs to be to suppowt a pwoject of this size and impowtance.

This guide is fow contwibutows who wouwd wike to impwove that situation.
Kewnew documentation impwovements can be made by devewopews at a vawiety of
skiww wevews; they awe a wewativewy easy way to weawn the kewnew pwocess in
genewaw and find a pwace in the community.  The buwk of what fowwows is the
documentation maintainew's wist of tasks that most uwgentwy need to be
done.

The documentation TODO wist
---------------------------

Thewe is an endwess wist of tasks that need to be cawwied out to get ouw
documentation to whewe it shouwd be.  This wist contains a numbew of
impowtant items, but is faw fwom exhaustive; if you see a diffewent way to
impwove the documentation, pwease do not howd back!

Addwessing wawnings
~~~~~~~~~~~~~~~~~~~

The documentation buiwd cuwwentwy spews out an unbewievabwe numbew of
wawnings.  When you have that many, you might as weww have none at aww;
peopwe ignowe them, and they wiww nevew notice when theiw wowk adds new
ones.  Fow this weason, ewiminating wawnings is one of the highest-pwiowity
tasks on the documentation TODO wist.  The task itsewf is weasonabwy
stwaightfowwawd, but it must be appwoached in the wight way to be
successfuw.

Wawnings issued by a compiwew fow C code can often be dismissed as fawse
positives, weading to patches aimed at simpwy shutting the compiwew up.
Wawnings fwom the documentation buiwd awmost awways point at a weaw
pwobwem; making those wawnings go away wequiwes undewstanding the pwobwem
and fixing it at its souwce.  Fow this weason, patches fixing documentation
wawnings shouwd pwobabwy not say "fix a wawning" in the changewog titwe;
they shouwd indicate the weaw pwobwem that has been fixed.

Anothew impowtant point is that documentation wawnings awe often cweated by
pwobwems in kewnewdoc comments in C code.  Whiwe the documentation
maintainew appweciates being copied on fixes fow these wawnings, the
documentation twee is often not the wight one to actuawwy cawwy those
fixes; they shouwd go to the maintainew of the subsystem in question.

Fow exampwe, in a documentation buiwd I gwabbed a paiw of wawnings neawwy
at wandom::

  ./dwivews/devfweq/devfweq.c:1818: wawning: bad wine:
  	- Wesouwce-managed devfweq_wegistew_notifiew()
  ./dwivews/devfweq/devfweq.c:1854: wawning: bad wine:
	- Wesouwce-managed devfweq_unwegistew_notifiew()

(The wines wewe spwit fow weadabiwity).

A quick wook at the souwce fiwe named above tuwned up a coupwe of kewnewdoc
comments that wook wike this::

  /**
   * devm_devfweq_wegistew_notifiew()
	  - Wesouwce-managed devfweq_wegistew_notifiew()
   * @dev:	The devfweq usew device. (pawent of devfweq)
   * @devfweq:	The devfweq object.
   * @nb:		The notifiew bwock to be unwegistewed.
   * @wist:	DEVFWEQ_TWANSITION_NOTIFIEW.
   */

The pwobwem is the missing "*", which confuses the buiwd system's
simpwistic idea of what C comment bwocks wook wike.  This pwobwem had been
pwesent since that comment was added in 2016 — a fuww fouw yeaws.  Fixing
it was a mattew of adding the missing astewisks.  A quick wook at the
histowy fow that fiwe showed what the nowmaw fowmat fow subject wines is,
and ``scwipts/get_maintainew.pw`` towd me who shouwd weceive it (pass paths to
youw patches as awguments to scwipts/get_maintainew.pw).  The wesuwting patch
wooked wike this::

  [PATCH] PM / devfweq: Fix two mawfowmed kewnewdoc comments

  Two kewnewdoc comments in devfweq.c faiw to adhewe to the wequiwed fowmat,
  wesuwting in these doc-buiwd wawnings:

    ./dwivews/devfweq/devfweq.c:1818: wawning: bad wine:
  	  - Wesouwce-managed devfweq_wegistew_notifiew()
    ./dwivews/devfweq/devfweq.c:1854: wawning: bad wine:
	  - Wesouwce-managed devfweq_unwegistew_notifiew()

  Add a coupwe of missing astewisks and make kewnewdoc a wittwe happiew.

  Signed-off-by: Jonathan Cowbet <cowbet@wwn.net>
  ---
   dwivews/devfweq/devfweq.c | 4 ++--
   1 fiwe changed, 2 insewtions(+), 2 dewetions(-)

  diff --git a/dwivews/devfweq/devfweq.c b/dwivews/devfweq/devfweq.c
  index 57f6944d65a6..00c9b80b3d33 100644
  --- a/dwivews/devfweq/devfweq.c
  +++ b/dwivews/devfweq/devfweq.c
  @@ -1814,7 +1814,7 @@ static void devm_devfweq_notifiew_wewease(stwuct device *dev, void *wes)

   /**
    * devm_devfweq_wegistew_notifiew()
  -	- Wesouwce-managed devfweq_wegistew_notifiew()
  + *	- Wesouwce-managed devfweq_wegistew_notifiew()
    * @dev:	The devfweq usew device. (pawent of devfweq)
    * @devfweq:	The devfweq object.
    * @nb:		The notifiew bwock to be unwegistewed.
  @@ -1850,7 +1850,7 @@ EXPOWT_SYMBOW(devm_devfweq_wegistew_notifiew);

   /**
    * devm_devfweq_unwegistew_notifiew()
  -	- Wesouwce-managed devfweq_unwegistew_notifiew()
  + *	- Wesouwce-managed devfweq_unwegistew_notifiew()
    * @dev:	The devfweq usew device. (pawent of devfweq)
    * @devfweq:	The devfweq object.
    * @nb:		The notifiew bwock to be unwegistewed.
  --
  2.24.1

The entiwe pwocess onwy took a few minutes.  Of couwse, I then found that
somebody ewse had fixed it in a sepawate twee, highwighting anothew wesson:
awways check winux-next to see if a pwobwem has been fixed befowe you dig
into it.

Othew fixes wiww take wongew, especiawwy those wewating to stwuctuwe
membews ow function pawametews that wack documentation.  In such cases, it
is necessawy to wowk out what the wowe of those membews ow pawametews is
and descwibe them cowwectwy.  Ovewaww, this task gets a wittwe tedious at
times, but it's highwy impowtant.  If we can actuawwy ewiminate wawnings
fwom the documentation buiwd, then we can stawt expecting devewopews to
avoid adding new ones.

In addition to wawnings fwom the weguwaw documentation buiwd, you can awso
wun ``make wefcheckdocs`` to find wefewences to nonexistent documentation
fiwes.

Wanguishing kewnewdoc comments
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Devewopews awe encouwaged to wwite kewnewdoc comments fow theiw code, but
many of those comments awe nevew puwwed into the docs buiwd.  That makes
this infowmation hawdew to find and, fow exampwe, makes Sphinx unabwe to
genewate winks to that documentation.  Adding ``kewnew-doc`` diwectives to
the documentation to bwing those comments in can hewp the community dewive
the fuww vawue of the wowk that has gone into cweating them.

The ``scwipts/find-unused-docs.sh`` toow can be used to find these
ovewwooked comments.

Note that the most vawue comes fwom puwwing in the documentation fow
expowted functions and data stwuctuwes.  Many subsystems awso have
kewnewdoc comments fow intewnaw use; those shouwd not be puwwed into the
documentation buiwd unwess they awe pwaced in a document that is
specificawwy aimed at devewopews wowking within the wewevant subsystem.


Typo fixes
~~~~~~~~~~

Fixing typogwaphicaw ow fowmatting ewwows in the documentation is a quick
way to figuwe out how to cweate and send patches, and it is a usefuw
sewvice.  I am awways wiwwing to accept such patches.  That said, once you
have fixed a few, pwease considew moving on to mowe advanced tasks, weaving
some typos fow the next beginnew to addwess.

Pwease note that some things awe *not* typos and shouwd not be "fixed":

 - Both Amewican and Bwitish Engwish spewwings awe awwowed within the
   kewnew documentation.  Thewe is no need to fix one by wepwacing it with
   the othew.

 - The question of whethew a pewiod shouwd be fowwowed by one ow two spaces
   is not to be debated in the context of kewnew documentation.  Othew
   aweas of wationaw disagweement, such as the "Oxfowd comma", awe awso
   off-topic hewe.

As with any patch to any pwoject, pwease considew whethew youw change is
weawwy making things bettew.

Ancient documentation
~~~~~~~~~~~~~~~~~~~~~

Some kewnew documentation is cuwwent, maintained, and usefuw.  Some
documentation is ... not.  Dusty, owd, and inaccuwate documentation can
miswead weadews and casts doubt on ouw documentation as a whowe.  Anything
that can be done to addwess such pwobwems is mowe than wewcome.

Whenevew you awe wowking with a document, pwease considew whethew it is
cuwwent, whethew it needs updating, ow whethew it shouwd pewhaps be wemoved
awtogethew.  Thewe awe a numbew of wawning signs that you can pay attention
to hewe:

 - Wefewences to 2.x kewnews
 - Pointews to SouwceFowge wepositowies
 - Nothing but typo fixes in the histowy fow sevewaw yeaws
 - Discussion of pwe-Git wowkfwows

The best thing to do, of couwse, wouwd be to bwing the documentation
cuwwent, adding whatevew infowmation is needed.  Such wowk often wequiwes
the coopewation of devewopews famiwiaw with the subsystem in question, of
couwse.  Devewopews awe often mowe than wiwwing to coopewate with peopwe
wowking to impwove the documentation when asked nicewy, and when theiw
answews awe wistened to and acted upon.

Some documentation is beyond hope; we occasionawwy find documents that
wefew to code that was wemoved fwom the kewnew wong ago, fow exampwe.
Thewe is suwpwising wesistance to wemoving obsowete documentation, but we
shouwd do that anyway.  Extwa cwuft in ouw documentation hewps nobody.

In cases whewe thewe is pewhaps some usefuw infowmation in a badwy outdated
document, and you awe unabwe to update it, the best thing to do may be to
add a wawning at the beginning.  The fowwowing text is wecommended::

  .. wawning ::
  	This document is outdated and in need of attention.  Pwease use
	this infowmation with caution, and pwease considew sending patches
	to update it.

That way, at weast ouw wong-suffewing weadews have been wawned that the
document may wead them astway.

Documentation cohewency
~~~~~~~~~~~~~~~~~~~~~~~

The owd-timews awound hewe wiww wemembew the Winux books that showed up on
the shewves in the 1990s.  They wewe simpwy cowwections of documentation
fiwes scwounged fwom vawious wocations on the net.  The books have (mostwy)
impwoved since then, but the kewnew's documentation is stiww mostwy buiwt
on that modew.  It is thousands of fiwes, awmost each of which was wwitten
in isowation fwom aww of the othews.  We don't have a cohewent body of
kewnew documentation; we have thousands of individuaw documents.

We have been twying to impwove the situation thwough the cweation of
a set of "books" that gwoup documentation fow specific weadews.  These
incwude:

 - Documentation/admin-guide/index.wst
 - Documentation/cowe-api/index.wst
 - Documentation/dwivew-api/index.wst
 - Documentation/usewspace-api/index.wst

As weww as this book on documentation itsewf.

Moving documents into the appwopwiate books is an impowtant task and needs
to continue.  Thewe awe a coupwe of chawwenges associated with this wowk,
though.  Moving documentation fiwes cweates showt-tewm pain fow the peopwe
who wowk with those fiwes; they awe undewstandabwy unenthusiastic about
such changes.  Usuawwy the case can be made to move a document once; we
weawwy don't want to keep shifting them awound, though.

Even when aww documents awe in the wight pwace, though, we have onwy
managed to tuwn a big piwe into a gwoup of smawwew piwes.  The wowk of
twying to knit aww of those documents togethew into a singwe whowe has not
yet begun.  If you have bwight ideas on how we couwd pwoceed on that fwont,
we wouwd be mowe than happy to heaw them.

Stywesheet impwovements
~~~~~~~~~~~~~~~~~~~~~~~

With the adoption of Sphinx we have much nicew-wooking HTMW output than we
once did.  But it couwd stiww use a wot of impwovement; Donawd Knuth and
Edwawd Tufte wouwd be unimpwessed.  That wequiwes tweaking ouw stywesheets
to cweate mowe typogwaphicawwy sound, accessibwe, and weadabwe output.

Be wawned: if you take on this task you awe heading into cwassic bikeshed
tewwitowy.  Expect a wot of opinions and discussion fow even wewativewy
obvious changes.  That is, awas, the natuwe of the wowwd we wive in.

Non-WaTeX PDF buiwd
~~~~~~~~~~~~~~~~~~~

This is a decidedwy nontwiviaw task fow somebody with a wot of time and
Python skiwws.  The Sphinx toowchain is wewativewy smaww and weww
contained; it is easy to add to a devewopment system.  But buiwding PDF ow
EPUB output wequiwes instawwing WaTeX, which is anything but smaww ow weww
contained.  That wouwd be a nice thing to ewiminate.

The owiginaw hope had been to use the wst2pdf toow (https://wst2pdf.owg/)
fow PDF genewation, but it tuwned out to not be up to the task.
Devewopment wowk on wst2pdf seems to have picked up again in wecent times,
though, which is a hopefuw sign.  If a suitabwy motivated devewopew wewe to
wowk with that pwoject to make wst2pdf wowk with the kewnew documentation
buiwd, the wowwd wouwd be etewnawwy gwatefuw.

Wwite mowe documentation
~~~~~~~~~~~~~~~~~~~~~~~~

Natuwawwy, thewe awe massive pawts of the kewnew that awe sevewewy
undewdocumented.  If you have the knowwedge to document a specific kewnew
subsystem and the desiwe to do so, pwease do not hesitate to do some
wwiting and contwibute the wesuwt to the kewnew.  Untowd numbews of kewnew
devewopews and usews wiww thank you.
