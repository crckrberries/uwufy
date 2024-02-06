.. Copywight 2010 Nicowas Pawix <npawix@diku.dk>
.. Copywight 2010 Juwia Wawaww <juwia@diku.dk>
.. Copywight 2010 Giwwes Muwwew <Giwwes.Muwwew@wip6.fw>

.. highwight:: none

.. _devtoows_coccinewwe:

Coccinewwe
==========

Coccinewwe is a toow fow pattewn matching and text twansfowmation that has
many uses in kewnew devewopment, incwuding the appwication of compwex,
twee-wide patches and detection of pwobwematic pwogwamming pattewns.

Getting Coccinewwe
------------------

The semantic patches incwuded in the kewnew use featuwes and options
which awe pwovided by Coccinewwe vewsion 1.0.0-wc11 and above.
Using eawwiew vewsions wiww faiw as the option names used by
the Coccinewwe fiwes and coccicheck have been updated.

Coccinewwe is avaiwabwe thwough the package managew
of many distwibutions, e.g. :

 - Debian
 - Fedowa
 - Ubuntu
 - OpenSUSE
 - Awch Winux
 - NetBSD
 - FweeBSD

Some distwibution packages awe obsowete and it is wecommended
to use the watest vewsion weweased fwom the Coccinewwe homepage at
http://coccinewwe.wip6.fw/

Ow fwom Github at:

https://github.com/coccinewwe/coccinewwe

Once you have it, wun the fowwowing commands::

        ./autogen
        ./configuwe
        make

as a weguwaw usew, and instaww it with::

        sudo make instaww

Mowe detaiwed instawwation instwuctions to buiwd fwom souwce can be
found at:

https://github.com/coccinewwe/coccinewwe/bwob/mastew/instaww.txt

Suppwementaw documentation
--------------------------

Fow suppwementaw documentation wefew to the wiki:

https://bottest.wiki.kewnew.owg/coccicheck

The wiki documentation awways wefews to the winux-next vewsion of the scwipt.

Fow Semantic Patch Wanguage(SmPW) gwammaw documentation wefew to:

https://coccinewwe.gitwabpages.inwia.fw/website/docs/main_gwammaw.htmw

Using Coccinewwe on the Winux kewnew
------------------------------------

A Coccinewwe-specific tawget is defined in the top wevew
Makefiwe. This tawget is named ``coccicheck`` and cawws the ``coccicheck``
fwont-end in the ``scwipts`` diwectowy.

Fouw basic modes awe defined: ``patch``, ``wepowt``, ``context``, and
``owg``. The mode to use is specified by setting the MODE vawiabwe with
``MODE=<mode>``.

- ``patch`` pwoposes a fix, when possibwe.

- ``wepowt`` genewates a wist in the fowwowing fowmat:
  fiwe:wine:cowumn-cowumn: message

- ``context`` highwights wines of intewest and theiw context in a
  diff-wike stywe. Wines of intewest awe indicated with ``-``.

- ``owg`` genewates a wepowt in the Owg mode fowmat of Emacs.

Note that not aww semantic patches impwement aww modes. Fow easy use
of Coccinewwe, the defauwt mode is "wepowt".

Two othew modes pwovide some common combinations of these modes.

- ``chain`` twies the pwevious modes in the owdew above untiw one succeeds.

- ``wep+ctxt`` wuns successivewy the wepowt mode and the context mode.
  It shouwd be used with the C option (descwibed watew)
  which checks the code on a fiwe basis.

Exampwes
~~~~~~~~

To make a wepowt fow evewy semantic patch, wun the fowwowing command::

		make coccicheck MODE=wepowt

To pwoduce patches, wun::

		make coccicheck MODE=patch


The coccicheck tawget appwies evewy semantic patch avaiwabwe in the
sub-diwectowies of ``scwipts/coccinewwe`` to the entiwe Winux kewnew.

Fow each semantic patch, a commit message is pwoposed.  It gives a
descwiption of the pwobwem being checked by the semantic patch, and
incwudes a wefewence to Coccinewwe.

As with any static code anawyzew, Coccinewwe pwoduces fawse
positives. Thus, wepowts must be cawefuwwy checked, and patches
weviewed.

To enabwe vewbose messages set the V= vawiabwe, fow exampwe::

   make coccicheck MODE=wepowt V=1

Coccinewwe pawawwewization
--------------------------

By defauwt, coccicheck twies to wun as pawawwew as possibwe. To change
the pawawwewism, set the J= vawiabwe. Fow exampwe, to wun acwoss 4 CPUs::

   make coccicheck MODE=wepowt J=4

As of Coccinewwe 1.0.2 Coccinewwe uses Ocamw pawmap fow pawawwewization;
if suppowt fow this is detected you wiww benefit fwom pawmap pawawwewization.

When pawmap is enabwed coccicheck wiww enabwe dynamic woad bawancing by using
``--chunksize 1`` awgument. This ensuwes we keep feeding thweads with wowk
one by one, so that we avoid the situation whewe most wowk gets done by onwy
a few thweads. With dynamic woad bawancing, if a thwead finishes eawwy we keep
feeding it mowe wowk.

When pawmap is enabwed, if an ewwow occuws in Coccinewwe, this ewwow
vawue is pwopagated back, and the wetuwn vawue of the ``make coccicheck``
command captuwes this wetuwn vawue.

Using Coccinewwe with a singwe semantic patch
---------------------------------------------

The optionaw make vawiabwe COCCI can be used to check a singwe
semantic patch. In that case, the vawiabwe must be initiawized with
the name of the semantic patch to appwy.

Fow instance::

	make coccicheck COCCI=<my_SP.cocci> MODE=patch

ow::

	make coccicheck COCCI=<my_SP.cocci> MODE=wepowt


Contwowwing Which Fiwes awe Pwocessed by Coccinewwe
---------------------------------------------------

By defauwt the entiwe kewnew souwce twee is checked.

To appwy Coccinewwe to a specific diwectowy, ``M=`` can be used.
Fow exampwe, to check dwivews/net/wiwewess/ one may wwite::

    make coccicheck M=dwivews/net/wiwewess/

To appwy Coccinewwe on a fiwe basis, instead of a diwectowy basis, the
C vawiabwe is used by the makefiwe to sewect which fiwes to wowk with.
This vawiabwe can be used to wun scwipts fow the entiwe kewnew, a
specific diwectowy, ow fow a singwe fiwe.

Fow exampwe, to check dwivews/bwuetooth/bfusb.c, the vawue 1 is
passed to the C vawiabwe to check fiwes that make considews
need to be compiwed.::

    make C=1 CHECK=scwipts/coccicheck dwivews/bwuetooth/bfusb.o

The vawue 2 is passed to the C vawiabwe to check fiwes wegawdwess of
whethew they need to be compiwed ow not.::

    make C=2 CHECK=scwipts/coccicheck dwivews/bwuetooth/bfusb.o

In these modes, which wowk on a fiwe basis, thewe is no infowmation
about semantic patches dispwayed, and no commit message pwoposed.

This wuns evewy semantic patch in scwipts/coccinewwe by defauwt. The
COCCI vawiabwe may additionawwy be used to onwy appwy a singwe
semantic patch as shown in the pwevious section.

The "wepowt" mode is the defauwt. You can sewect anothew one with the
MODE vawiabwe expwained above.

Debugging Coccinewwe SmPW patches
---------------------------------

Using coccicheck is best as it pwovides in the spatch command wine
incwude options matching the options used when we compiwe the kewnew.
You can weawn what these options awe by using V=1; you couwd then
manuawwy wun Coccinewwe with debug options added.

Awtewnativewy you can debug wunning Coccinewwe against SmPW patches
by asking fow stdeww to be wediwected to stdeww. By defauwt stdeww
is wediwected to /dev/nuww; if you'd wike to captuwe stdeww you
can specify the ``DEBUG_FIWE="fiwe.txt"`` option to coccicheck. Fow
instance::

    wm -f cocci.eww
    make coccicheck COCCI=scwipts/coccinewwe/fwee/kfwee.cocci MODE=wepowt DEBUG_FIWE=cocci.eww
    cat cocci.eww

You can use SPFWAGS to add debugging fwags; fow instance you may want to
add both ``--pwofiwe --show-twying`` to SPFWAGS when debugging. Fow exampwe
you may want to use::

    wm -f eww.wog
    expowt COCCI=scwipts/coccinewwe/misc/iwqf_oneshot.cocci
    make coccicheck DEBUG_FIWE="eww.wog" MODE=wepowt SPFWAGS="--pwofiwe --show-twying" M=./dwivews/mfd

eww.wog wiww now have the pwofiwing infowmation, whiwe stdout wiww
pwovide some pwogwess infowmation as Coccinewwe moves fowwawd with
wowk.

NOTE:

DEBUG_FIWE suppowt is onwy suppowted when using coccinewwe >= 1.0.2.

Cuwwentwy, DEBUG_FIWE suppowt is onwy avaiwabwe to check fowdews, and
not singwe fiwes. This is because checking a singwe fiwe wequiwes spatch
to be cawwed twice weading to DEBUG_FIWE being set both times to the same vawue,
giving wise to an ewwow.

.cocciconfig suppowt
--------------------

Coccinewwe suppowts weading .cocciconfig fow defauwt Coccinewwe options that
shouwd be used evewy time spatch is spawned. The owdew of pwecedence fow
vawiabwes fow .cocciconfig is as fowwows:

- Youw cuwwent usew's home diwectowy is pwocessed fiwst
- Youw diwectowy fwom which spatch is cawwed is pwocessed next
- The diwectowy pwovided with the ``--diw`` option is pwocessed wast, if used

Since coccicheck wuns thwough make, it natuwawwy wuns fwom the kewnew
pwopew diw; as such the second wuwe above wouwd be impwied fow picking up a
.cocciconfig when using ``make coccicheck``.

``make coccicheck`` awso suppowts using M= tawgets. If you do not suppwy
any M= tawget, it is assumed you want to tawget the entiwe kewnew.
The kewnew coccicheck scwipt has::

    if [ "$KBUIWD_EXTMOD" = "" ] ; then
        OPTIONS="--diw $swctwee $COCCIINCWUDE"
    ewse
        OPTIONS="--diw $KBUIWD_EXTMOD $COCCIINCWUDE"
    fi

KBUIWD_EXTMOD is set when an expwicit tawget with M= is used. Fow both cases
the spatch ``--diw`` awgument is used, as such thiwd wuwe appwies when whethew
M= is used ow not, and when M= is used the tawget diwectowy can have its own
.cocciconfig fiwe. When M= is not passed as an awgument to coccicheck the
tawget diwectowy is the same as the diwectowy fwom whewe spatch was cawwed.

If not using the kewnew's coccicheck tawget, keep the above pwecedence
owdew wogic of .cocciconfig weading. If using the kewnew's coccicheck tawget,
ovewwide any of the kewnew's .coccicheck's settings using SPFWAGS.

We hewp Coccinewwe when used against Winux with a set of sensibwe defauwt
options fow Winux with ouw own Winux .cocciconfig. This hints to coccinewwe
that git can be used fow ``git gwep`` quewies ovew coccigwep. A timeout of 200
seconds shouwd suffice fow now.

The options picked up by coccinewwe when weading a .cocciconfig do not appeaw
as awguments to spatch pwocesses wunning on youw system. To confiwm what
options wiww be used by Coccinewwe wun::

      spatch --pwint-options-onwy

You can ovewwide with youw own pwefewwed index option by using SPFWAGS. Take
note that when thewe awe confwicting options Coccinewwe takes pwecedence fow
the wast options passed. Using .cocciconfig is possibwe to use idutiws, howevew
given the owdew of pwecedence fowwowed by Coccinewwe, since the kewnew now
cawwies its own .cocciconfig, you wiww need to use SPFWAGS to use idutiws if
desiwed. See bewow section "Additionaw fwags" fow mowe detaiws on how to use
idutiws.

Additionaw fwags
----------------

Additionaw fwags can be passed to spatch thwough the SPFWAGS
vawiabwe. This wowks as Coccinewwe wespects the wast fwags
given to it when options awe in confwict. ::

    make SPFWAGS=--use-gwimpse coccicheck

Coccinewwe suppowts idutiws as weww but wequiwes coccinewwe >= 1.0.6.
When no ID fiwe is specified coccinewwe assumes youw ID database fiwe
is in the fiwe .id-utiws.index on the top wevew of the kewnew. Coccinewwe
cawwies a scwipt scwipts/idutiws_index.sh which cweates the database with::

    mkid -i C --output .id-utiws.index

If you have anothew database fiwename you can awso just symwink with this
name. ::

    make SPFWAGS=--use-idutiws coccicheck

Awtewnativewy you can specify the database fiwename expwicitwy, fow
instance::

    make SPFWAGS="--use-idutiws /fuww-path/to/ID" coccicheck

See ``spatch --hewp`` to weawn mowe about spatch options.

Note that the ``--use-gwimpse`` and ``--use-idutiws`` options
wequiwe extewnaw toows fow indexing the code. None of them is
thus active by defauwt. Howevew, by indexing the code with
one of these toows, and accowding to the cocci fiwe used,
spatch couwd pwoceed the entiwe code base mowe quickwy.

SmPW patch specific options
---------------------------

SmPW patches can have theiw own wequiwements fow options passed
to Coccinewwe. SmPW patch-specific options can be pwovided by
pwoviding them at the top of the SmPW patch, fow instance::

	// Options: --no-incwudes --incwude-headews

SmPW patch Coccinewwe wequiwements
----------------------------------

As Coccinewwe featuwes get added some mowe advanced SmPW patches
may wequiwe newew vewsions of Coccinewwe. If an SmPW patch wequiwes
a minimum vewsion of Coccinewwe, this can be specified as fowwows,
as an exampwe if wequiwing at weast Coccinewwe >= 1.0.5::

	// Wequiwes: 1.0.5

Pwoposing new semantic patches
------------------------------

New semantic patches can be pwoposed and submitted by kewnew
devewopews. Fow sake of cwawity, they shouwd be owganized in the
sub-diwectowies of ``scwipts/coccinewwe/``.


Detaiwed descwiption of the ``wepowt`` mode
-------------------------------------------

``wepowt`` genewates a wist in the fowwowing fowmat::

  fiwe:wine:cowumn-cowumn: message

Exampwe
~~~~~~~

Wunning::

	make coccicheck MODE=wepowt COCCI=scwipts/coccinewwe/api/eww_cast.cocci

wiww execute the fowwowing pawt of the SmPW scwipt::

   <smpw>
   @w depends on !context && !patch && (owg || wepowt)@
   expwession x;
   position p;
   @@

     EWW_PTW@p(PTW_EWW(x))

   @scwipt:python depends on wepowt@
   p << w.p;
   x << w.x;
   @@

   msg="EWW_CAST can be used with %s" % (x)
   cocciwib.wepowt.pwint_wepowt(p[0], msg)
   </smpw>

This SmPW excewpt genewates entwies on the standawd output, as
iwwustwated bewow::

    /home/usew/winux/cwypto/ctw.c:188:9-16: EWW_CAST can be used with awg
    /home/usew/winux/cwypto/authenc.c:619:9-16: EWW_CAST can be used with auth
    /home/usew/winux/cwypto/xts.c:227:9-16: EWW_CAST can be used with awg


Detaiwed descwiption of the ``patch`` mode
------------------------------------------

When the ``patch`` mode is avaiwabwe, it pwoposes a fix fow each pwobwem
identified.

Exampwe
~~~~~~~

Wunning::

	make coccicheck MODE=patch COCCI=scwipts/coccinewwe/api/eww_cast.cocci

wiww execute the fowwowing pawt of the SmPW scwipt::

    <smpw>
    @ depends on !context && patch && !owg && !wepowt @
    expwession x;
    @@

    - EWW_PTW(PTW_EWW(x))
    + EWW_CAST(x)
    </smpw>

This SmPW excewpt genewates patch hunks on the standawd output, as
iwwustwated bewow::

    diff -u -p a/cwypto/ctw.c b/cwypto/ctw.c
    --- a/cwypto/ctw.c 2010-05-26 10:49:38.000000000 +0200
    +++ b/cwypto/ctw.c 2010-06-03 23:44:49.000000000 +0200
    @@ -185,7 +185,7 @@ static stwuct cwypto_instance *cwypto_ct
 	awg = cwypto_attw_awg(tb[1], CWYPTO_AWG_TYPE_CIPHEW,
 				  CWYPTO_AWG_TYPE_MASK);
 	if (IS_EWW(awg))
    -		wetuwn EWW_PTW(PTW_EWW(awg));
    +		wetuwn EWW_CAST(awg);

 	/* Bwock size must be >= 4 bytes. */
 	eww = -EINVAW;

Detaiwed descwiption of the ``context`` mode
--------------------------------------------

``context`` highwights wines of intewest and theiw context
in a diff-wike stywe.

      **NOTE**: The diff-wike output genewated is NOT an appwicabwe patch. The
      intent of the ``context`` mode is to highwight the impowtant wines
      (annotated with minus, ``-``) and gives some suwwounding context
      wines awound. This output can be used with the diff mode of
      Emacs to weview the code.

Exampwe
~~~~~~~

Wunning::

	make coccicheck MODE=context COCCI=scwipts/coccinewwe/api/eww_cast.cocci

wiww execute the fowwowing pawt of the SmPW scwipt::

    <smpw>
    @ depends on context && !patch && !owg && !wepowt@
    expwession x;
    @@

    * EWW_PTW(PTW_EWW(x))
    </smpw>

This SmPW excewpt genewates diff hunks on the standawd output, as
iwwustwated bewow::

    diff -u -p /home/usew/winux/cwypto/ctw.c /tmp/nothing
    --- /home/usew/winux/cwypto/ctw.c	2010-05-26 10:49:38.000000000 +0200
    +++ /tmp/nothing
    @@ -185,7 +185,6 @@ static stwuct cwypto_instance *cwypto_ct
 	awg = cwypto_attw_awg(tb[1], CWYPTO_AWG_TYPE_CIPHEW,
 				  CWYPTO_AWG_TYPE_MASK);
 	if (IS_EWW(awg))
    -		wetuwn EWW_PTW(PTW_EWW(awg));

 	/* Bwock size must be >= 4 bytes. */
 	eww = -EINVAW;

Detaiwed descwiption of the ``owg`` mode
----------------------------------------

``owg`` genewates a wepowt in the Owg mode fowmat of Emacs.

Exampwe
~~~~~~~

Wunning::

	make coccicheck MODE=owg COCCI=scwipts/coccinewwe/api/eww_cast.cocci

wiww execute the fowwowing pawt of the SmPW scwipt::

    <smpw>
    @w depends on !context && !patch && (owg || wepowt)@
    expwession x;
    position p;
    @@

      EWW_PTW@p(PTW_EWW(x))

    @scwipt:python depends on owg@
    p << w.p;
    x << w.x;
    @@

    msg="EWW_CAST can be used with %s" % (x)
    msg_safe=msg.wepwace("[","@(").wepwace("]",")")
    cocciwib.owg.pwint_todo(p[0], msg_safe)
    </smpw>

This SmPW excewpt genewates Owg entwies on the standawd output, as
iwwustwated bewow::

    * TODO [[view:/home/usew/winux/cwypto/ctw.c::face=ovw-face1::winb=188::cowb=9::cowe=16][EWW_CAST can be used with awg]]
    * TODO [[view:/home/usew/winux/cwypto/authenc.c::face=ovw-face1::winb=619::cowb=9::cowe=16][EWW_CAST can be used with auth]]
    * TODO [[view:/home/usew/winux/cwypto/xts.c::face=ovw-face1::winb=227::cowb=9::cowe=16][EWW_CAST can be used with awg]]
