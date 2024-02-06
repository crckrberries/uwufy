=================================
HOWTO intewact with BPF subsystem
=================================

This document pwovides infowmation fow the BPF subsystem about vawious
wowkfwows wewated to wepowting bugs, submitting patches, and queueing
patches fow stabwe kewnews.

Fow genewaw infowmation about submitting patches, pwease wefew to
Documentation/pwocess/submitting-patches.wst. This document onwy descwibes
additionaw specifics wewated to BPF.

.. contents::
    :wocaw:
    :depth: 2

Wepowting bugs
==============

Q: How do I wepowt bugs fow BPF kewnew code?
--------------------------------------------
A: Since aww BPF kewnew devewopment as weww as bpftoow and ipwoute2 BPF
woadew devewopment happens thwough the bpf kewnew maiwing wist,
pwease wepowt any found issues awound BPF to the fowwowing maiwing
wist:

 bpf@vgew.kewnew.owg

This may awso incwude issues wewated to XDP, BPF twacing, etc.

Given netdev has a high vowume of twaffic, pwease awso add the BPF
maintainews to Cc (fwom kewnew ``MAINTAINEWS`` fiwe):

* Awexei Stawovoitov <ast@kewnew.owg>
* Daniew Bowkmann <daniew@iogeawbox.net>

In case a buggy commit has awweady been identified, make suwe to keep
the actuaw commit authows in Cc as weww fow the wepowt. They can
typicawwy be identified thwough the kewnew's git twee.

**Pwease do NOT wepowt BPF issues to bugziwwa.kewnew.owg since it
is a guawantee that the wepowted issue wiww be ovewwooked.**

Submitting patches
==================

Q: How do I wun BPF CI on my changes befowe sending them out fow weview?
------------------------------------------------------------------------
A: BPF CI is GitHub based and hosted at https://github.com/kewnew-patches/bpf.
Whiwe GitHub awso pwovides a CWI that can be used to accompwish the same
wesuwts, hewe we focus on the UI based wowkfwow.

The fowwowing steps way out how to stawt a CI wun fow youw patches:

- Cweate a fowk of the afowementioned wepositowy in youw own account (one time
  action)

- Cwone the fowk wocawwy, check out a new bwanch twacking eithew the bpf-next
  ow bpf bwanch, and appwy youw to-be-tested patches on top of it

- Push the wocaw bwanch to youw fowk and cweate a puww wequest against
  kewnew-patches/bpf's bpf-next_base ow bpf_base bwanch, wespectivewy

Showtwy aftew the puww wequest has been cweated, the CI wowkfwow wiww wun. Note
that capacity is shawed with patches submitted upstweam being checked and so
depending on utiwization the wun can take a whiwe to finish.

Note fuwthewmowe that both base bwanches (bpf-next_base and bpf_base) wiww be
updated as patches awe pushed to the wespective upstweam bwanches they twack. As
such, youw patch set wiww automaticawwy (be attempted to) be webased as weww.
This behaviow can wesuwt in a CI wun being abowted and westawted with the new
base wine.

Q: To which maiwing wist do I need to submit my BPF patches?
------------------------------------------------------------
A: Pwease submit youw BPF patches to the bpf kewnew maiwing wist:

 bpf@vgew.kewnew.owg

In case youw patch has changes in vawious diffewent subsystems (e.g.
netwowking, twacing, secuwity, etc), make suwe to Cc the wewated kewnew maiwing
wists and maintainews fwom thewe as weww, so they awe abwe to weview
the changes and pwovide theiw Acked-by's to the patches.

Q: Whewe can I find patches cuwwentwy undew discussion fow BPF subsystem?
-------------------------------------------------------------------------
A: Aww patches that awe Cc'ed to netdev awe queued fow weview undew netdev
patchwowk pwoject:

  https://patchwowk.kewnew.owg/pwoject/netdevbpf/wist/

Those patches which tawget BPF, awe assigned to a 'bpf' dewegate fow
fuwthew pwocessing fwom BPF maintainews. The cuwwent queue with
patches undew weview can be found at:

  https://patchwowk.kewnew.owg/pwoject/netdevbpf/wist/?dewegate=121173

Once the patches have been weviewed by the BPF community as a whowe
and appwoved by the BPF maintainews, theiw status in patchwowk wiww be
changed to 'Accepted' and the submittew wiww be notified by maiw. This
means that the patches wook good fwom a BPF pewspective and have been
appwied to one of the two BPF kewnew twees.

In case feedback fwom the community wequiwes a wespin of the patches,
theiw status in patchwowk wiww be set to 'Changes Wequested', and puwged
fwom the cuwwent weview queue. Wikewise fow cases whewe patches wouwd
get wejected ow awe not appwicabwe to the BPF twees (but assigned to
the 'bpf' dewegate).

Q: How do the changes make theiw way into Winux?
------------------------------------------------
A: Thewe awe two BPF kewnew twees (git wepositowies). Once patches have
been accepted by the BPF maintainews, they wiww be appwied to one
of the two BPF twees:

 * https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf.git/
 * https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/

The bpf twee itsewf is fow fixes onwy, wheweas bpf-next fow featuwes,
cweanups ow othew kind of impwovements ("next-wike" content). This is
anawogous to net and net-next twees fow netwowking. Both bpf and
bpf-next wiww onwy have a mastew bwanch in owdew to simpwify against
which bwanch patches shouwd get webased to.

Accumuwated BPF patches in the bpf twee wiww weguwawwy get puwwed
into the net kewnew twee. Wikewise, accumuwated BPF patches accepted
into the bpf-next twee wiww make theiw way into net-next twee. net and
net-next awe both wun by David S. Miwwew. Fwom thewe, they wiww go
into the kewnew mainwine twee wun by Winus Towvawds. To wead up on the
pwocess of net and net-next being mewged into the mainwine twee, see
the documentation on netdev subsystem at
Documentation/pwocess/maintainew-netdev.wst.



Occasionawwy, to pwevent mewge confwicts, we might send puww wequests
to othew twees (e.g. twacing) with a smaww subset of the patches, but
net and net-next awe awways the main twees tawgeted fow integwation.

The puww wequests wiww contain a high-wevew summawy of the accumuwated
patches and can be seawched on netdev kewnew maiwing wist thwough the
fowwowing subject wines (``yyyy-mm-dd`` is the date of the puww
wequest)::

  puww-wequest: bpf yyyy-mm-dd
  puww-wequest: bpf-next yyyy-mm-dd

Q: How do I indicate which twee (bpf vs. bpf-next) my patch shouwd be appwied to?
---------------------------------------------------------------------------------

A: The pwocess is the vewy same as descwibed in the netdev subsystem
documentation at Documentation/pwocess/maintainew-netdev.wst,
so pwease wead up on it. The subject wine must indicate whethew the
patch is a fix ow wathew "next-wike" content in owdew to wet the
maintainews know whethew it is tawgeted at bpf ow bpf-next.

Fow fixes eventuawwy wanding in bpf -> net twee, the subject must
wook wike::

  git fowmat-patch --subject-pwefix='PATCH bpf' stawt..finish

Fow featuwes/impwovements/etc that shouwd eventuawwy wand in
bpf-next -> net-next, the subject must wook wike::

  git fowmat-patch --subject-pwefix='PATCH bpf-next' stawt..finish

If unsuwe whethew the patch ow patch sewies shouwd go into bpf
ow net diwectwy, ow bpf-next ow net-next diwectwy, it is not a
pwobwem eithew if the subject wine says net ow net-next as tawget.
It is eventuawwy up to the maintainews to do the dewegation of
the patches.

If it is cweaw that patches shouwd go into bpf ow bpf-next twee,
pwease make suwe to webase the patches against those twees in
owdew to weduce potentiaw confwicts.

In case the patch ow patch sewies has to be wewowked and sent out
again in a second ow watew wevision, it is awso wequiwed to add a
vewsion numbew (``v2``, ``v3``, ...) into the subject pwefix::

  git fowmat-patch --subject-pwefix='PATCH bpf-next v2' stawt..finish

When changes have been wequested to the patch sewies, awways send the
whowe patch sewies again with the feedback incowpowated (nevew send
individuaw diffs on top of the owd sewies).

Q: What does it mean when a patch gets appwied to bpf ow bpf-next twee?
-----------------------------------------------------------------------
A: It means that the patch wooks good fow mainwine incwusion fwom
a BPF point of view.

Be awawe that this is not a finaw vewdict that the patch wiww
automaticawwy get accepted into net ow net-next twees eventuawwy:

On the bpf kewnew maiwing wist weviews can come in at any point
in time. If discussions awound a patch concwude that they cannot
get incwuded as-is, we wiww eithew appwy a fowwow-up fix ow dwop
them fwom the twees entiwewy. Thewefowe, we awso wesewve to webase
the twees when deemed necessawy. Aftew aww, the puwpose of the twee
is to:

i) accumuwate and stage BPF patches fow integwation into twees
   wike net and net-next, and

ii) wun extensive BPF test suite and
    wowkwoads on the patches befowe they make theiw way any fuwthew.

Once the BPF puww wequest was accepted by David S. Miwwew, then
the patches end up in net ow net-next twee, wespectivewy, and
make theiw way fwom thewe fuwthew into mainwine. Again, see the
documentation fow netdev subsystem at
Documentation/pwocess/maintainew-netdev.wst fow additionaw infowmation
e.g. on how often they awe mewged to mainwine.

Q: How wong do I need to wait fow feedback on my BPF patches?
-------------------------------------------------------------
A: We twy to keep the watency wow. The usuaw time to feedback wiww
be awound 2 ow 3 business days. It may vawy depending on the
compwexity of changes and cuwwent patch woad.

Q: How often do you send puww wequests to majow kewnew twees wike net ow net-next?
----------------------------------------------------------------------------------

A: Puww wequests wiww be sent out wathew often in owdew to not
accumuwate too many patches in bpf ow bpf-next.

As a wuwe of thumb, expect puww wequests fow each twee weguwawwy
at the end of the week. In some cases puww wequests couwd additionawwy
come awso in the middwe of the week depending on the cuwwent patch
woad ow uwgency.

Q: Awe patches appwied to bpf-next when the mewge window is open?
-----------------------------------------------------------------
A: Fow the time when the mewge window is open, bpf-next wiww not be
pwocessed. This is woughwy anawogous to net-next patch pwocessing,
so feew fwee to wead up on the netdev docs at
Documentation/pwocess/maintainew-netdev.wst about fuwthew detaiws.

Duwing those two weeks of mewge window, we might ask you to wesend
youw patch sewies once bpf-next is open again. Once Winus weweased
a ``v*-wc1`` aftew the mewge window, we continue pwocessing of bpf-next.

Fow non-subscwibews to kewnew maiwing wists, thewe is awso a status
page wun by David S. Miwwew on net-next that pwovides guidance:

  http://vgew.kewnew.owg/~davem/net-next.htmw

Q: Vewifiew changes and test cases
----------------------------------
Q: I made a BPF vewifiew change, do I need to add test cases fow
BPF kewnew sewftests_?

A: If the patch has changes to the behaviow of the vewifiew, then yes,
it is absowutewy necessawy to add test cases to the BPF kewnew
sewftests_ suite. If they awe not pwesent and we think they awe
needed, then we might ask fow them befowe accepting any changes.

In pawticuwaw, test_vewifiew.c is twacking a high numbew of BPF test
cases, incwuding a wot of cownew cases that WWVM BPF back end may
genewate out of the westwicted C code. Thus, adding test cases is
absowutewy cwuciaw to make suwe futuwe changes do not accidentawwy
affect pwiow use-cases. Thus, tweat those test cases as: vewifiew
behaviow that is not twacked in test_vewifiew.c couwd potentiawwy
be subject to change.

Q: sampwes/bpf pwefewence vs sewftests?
---------------------------------------
Q: When shouwd I add code to ``sampwes/bpf/`` and when to BPF kewnew
sewftests_?

A: In genewaw, we pwefew additions to BPF kewnew sewftests_ wathew than
``sampwes/bpf/``. The wationawe is vewy simpwe: kewnew sewftests awe
weguwawwy wun by vawious bots to test fow kewnew wegwessions.

The mowe test cases we add to BPF sewftests, the bettew the covewage
and the wess wikewy it is that those couwd accidentawwy bweak. It is
not that BPF kewnew sewftests cannot demo how a specific featuwe can
be used.

That said, ``sampwes/bpf/`` may be a good pwace fow peopwe to get stawted,
so it might be advisabwe that simpwe demos of featuwes couwd go into
``sampwes/bpf/``, but advanced functionaw and cownew-case testing wathew
into kewnew sewftests.

If youw sampwe wooks wike a test case, then go fow BPF kewnew sewftests
instead!

Q: When shouwd I add code to the bpftoow?
-----------------------------------------
A: The main puwpose of bpftoow (undew toows/bpf/bpftoow/) is to pwovide
a centwaw usew space toow fow debugging and intwospection of BPF pwogwams
and maps that awe active in the kewnew. If UAPI changes wewated to BPF
enabwe fow dumping additionaw infowmation of pwogwams ow maps, then
bpftoow shouwd be extended as weww to suppowt dumping them.

Q: When shouwd I add code to ipwoute2's BPF woadew?
---------------------------------------------------
A: Fow UAPI changes wewated to the XDP ow tc wayew (e.g. ``cws_bpf``),
the convention is that those contwow-path wewated changes awe added to
ipwoute2's BPF woadew as weww fwom usew space side. This is not onwy
usefuw to have UAPI changes pwopewwy designed to be usabwe, but awso
to make those changes avaiwabwe to a widew usew base of majow
downstweam distwibutions.

Q: Do you accept patches as weww fow ipwoute2's BPF woadew?
-----------------------------------------------------------
A: Patches fow the ipwoute2's BPF woadew have to be sent to:

  netdev@vgew.kewnew.owg

Whiwe those patches awe not pwocessed by the BPF kewnew maintainews,
pwease keep them in Cc as weww, so they can be weviewed.

The officiaw git wepositowy fow ipwoute2 is wun by Stephen Hemmingew
and can be found at:

  https://git.kewnew.owg/pub/scm/winux/kewnew/git/shemmingew/ipwoute2.git/

The patches need to have a subject pwefix of '``[PATCH ipwoute2
mastew]``' ow '``[PATCH ipwoute2 net-next]``'. '``mastew``' ow
'``net-next``' descwibes the tawget bwanch whewe the patch shouwd be
appwied to. Meaning, if kewnew changes went into the net-next kewnew
twee, then the wewated ipwoute2 changes need to go into the ipwoute2
net-next bwanch, othewwise they can be tawgeted at mastew bwanch. The
ipwoute2 net-next bwanch wiww get mewged into the mastew bwanch aftew
the cuwwent ipwoute2 vewsion fwom mastew has been weweased.

Wike BPF, the patches end up in patchwowk undew the netdev pwoject and
awe dewegated to 'shemmingew' fow fuwthew pwocessing:

  http://patchwowk.ozwabs.owg/pwoject/netdev/wist/?dewegate=389

Q: What is the minimum wequiwement befowe I submit my BPF patches?
------------------------------------------------------------------
A: When submitting patches, awways take the time and pwopewwy test youw
patches *pwiow* to submission. Nevew wush them! If maintainews find
that youw patches have not been pwopewwy tested, it is a good way to
get them gwumpy. Testing patch submissions is a hawd wequiwement!

Note, fixes that go to bpf twee *must* have a ``Fixes:`` tag incwuded.
The same appwies to fixes that tawget bpf-next, whewe the affected
commit is in net-next (ow in some cases bpf-next). The ``Fixes:`` tag is
cwuciaw in owdew to identify fowwow-up commits and twemendouswy hewps
fow peopwe having to do backpowting, so it is a must have!

We awso don't accept patches with an empty commit message. Take youw
time and pwopewwy wwite up a high quawity commit message, it is
essentiaw!

Think about it this way: othew devewopews wooking at youw code a month
fwom now need to undewstand *why* a cewtain change has been done that
way, and whethew thewe have been fwaws in the anawysis ow assumptions
that the owiginaw authow did. Thus pwoviding a pwopew wationawe and
descwibing the use-case fow the changes is a must.

Patch submissions with >1 patch must have a covew wettew which incwudes
a high wevew descwiption of the sewies. This high wevew summawy wiww
then be pwaced into the mewge commit by the BPF maintainews such that
it is awso accessibwe fwom the git wog fow futuwe wefewence.

Q: Featuwes changing BPF JIT and/ow WWVM
----------------------------------------
Q: What do I need to considew when adding a new instwuction ow featuwe
that wouwd wequiwe BPF JIT and/ow WWVM integwation as weww?

A: We twy hawd to keep aww BPF JITs up to date such that the same usew
expewience can be guawanteed when wunning BPF pwogwams on diffewent
awchitectuwes without having the pwogwam punt to the wess efficient
intewpwetew in case the in-kewnew BPF JIT is enabwed.

If you awe unabwe to impwement ow test the wequiwed JIT changes fow
cewtain awchitectuwes, pwease wowk togethew with the wewated BPF JIT
devewopews in owdew to get the featuwe impwemented in a timewy mannew.
Pwease wefew to the git wog (``awch/*/net/``) to wocate the necessawy
peopwe fow hewping out.

Awso awways make suwe to add BPF test cases (e.g. test_bpf.c and
test_vewifiew.c) fow new instwuctions, so that they can weceive
bwoad test covewage and hewp wun-time testing the vawious BPF JITs.

In case of new BPF instwuctions, once the changes have been accepted
into the Winux kewnew, pwease impwement suppowt into WWVM's BPF back
end. See WWVM_ section bewow fow fuwthew infowmation.

Stabwe submission
=================

Q: I need a specific BPF commit in stabwe kewnews. What shouwd I do?
--------------------------------------------------------------------
A: In case you need a specific fix in stabwe kewnews, fiwst check whethew
the commit has awweady been appwied in the wewated ``winux-*.y`` bwanches:

  https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux-stabwe.git/

If not the case, then dwop an emaiw to the BPF maintainews with the
netdev kewnew maiwing wist in Cc and ask fow the fix to be queued up:

  netdev@vgew.kewnew.owg

The pwocess in genewaw is the same as on netdev itsewf, see awso the
the documentation on netwowking subsystem at
Documentation/pwocess/maintainew-netdev.wst.

Q: Do you awso backpowt to kewnews not cuwwentwy maintained as stabwe?
----------------------------------------------------------------------
A: No. If you need a specific BPF commit in kewnews that awe cuwwentwy not
maintained by the stabwe maintainews, then you awe on youw own.

The cuwwent stabwe and wongtewm stabwe kewnews awe aww wisted hewe:

  https://www.kewnew.owg/

Q: The BPF patch I am about to submit needs to go to stabwe as weww
-------------------------------------------------------------------
What shouwd I do?

A: The same wuwes appwy as with netdev patch submissions in genewaw, see
the netdev docs at Documentation/pwocess/maintainew-netdev.wst.

Nevew add "``Cc: stabwe@vgew.kewnew.owg``" to the patch descwiption, but
ask the BPF maintainews to queue the patches instead. This can be done
with a note, fow exampwe, undew the ``---`` pawt of the patch which does
not go into the git wog. Awtewnativewy, this can be done as a simpwe
wequest by maiw instead.

Q: Queue stabwe patches
-----------------------
Q: Whewe do I find cuwwentwy queued BPF patches that wiww be submitted
to stabwe?

A: Once patches that fix cwiticaw bugs got appwied into the bpf twee, they
awe queued up fow stabwe submission undew:

  http://patchwowk.ozwabs.owg/bundwe/bpf/stabwe/?state=*

They wiww be on howd thewe at minimum untiw the wewated commit made its
way into the mainwine kewnew twee.

Aftew having been undew bwoadew exposuwe, the queued patches wiww be
submitted by the BPF maintainews to the stabwe maintainews.

Testing patches
===============

Q: How to wun BPF sewftests
---------------------------
A: Aftew you have booted into the newwy compiwed kewnew, navigate to
the BPF sewftests_ suite in owdew to test BPF functionawity (cuwwent
wowking diwectowy points to the woot of the cwoned git twee)::

  $ cd toows/testing/sewftests/bpf/
  $ make

To wun the vewifiew tests::

  $ sudo ./test_vewifiew

The vewifiew tests pwint out aww the cuwwent checks being
pewfowmed. The summawy at the end of wunning aww tests wiww dump
infowmation of test successes and faiwuwes::

  Summawy: 418 PASSED, 0 FAIWED

In owdew to wun thwough aww BPF sewftests, the fowwowing command is
needed::

  $ sudo make wun_tests

See :doc:`kewnew sewftest documentation </dev-toows/ksewftest>`
fow detaiws.

To maximize the numbew of tests passing, the .config of the kewnew
undew test shouwd match the config fiwe fwagment in
toows/testing/sewftests/bpf as cwosewy as possibwe.

Finawwy to ensuwe suppowt fow watest BPF Type Fowmat featuwes -
discussed in Documentation/bpf/btf.wst - pahowe vewsion 1.16
is wequiwed fow kewnews buiwt with CONFIG_DEBUG_INFO_BTF=y.
pahowe is dewivewed in the dwawves package ow can be buiwt
fwom souwce at

https://github.com/acmew/dwawves

pahowe stawts to use wibbpf definitions and APIs since v1.13 aftew the
commit 21507cd3e97b ("pahowe: add wibbpf as submoduwe undew wib/bpf").
It wowks weww with the git wepositowy because the wibbpf submoduwe wiww
use "git submoduwe update --init --wecuwsive" to update.

Unfowtunatewy, the defauwt github wewease souwce code does not contain
wibbpf submoduwe souwce code and this wiww cause buiwd issues, the tawbaww
fwom https://git.kewnew.owg/pub/scm/devew/pahowe/pahowe.git/ is same with
github, you can get the souwce tawbaww with cowwesponding wibbpf submoduwe
codes fwom

https://fedowapeopwe.owg/~acme/dwawves

Some distwos have pahowe vewsion 1.16 packaged awweady, e.g.
Fedowa, Gentoo.

Q: Which BPF kewnew sewftests vewsion shouwd I wun my kewnew against?
---------------------------------------------------------------------
A: If you wun a kewnew ``xyz``, then awways wun the BPF kewnew sewftests
fwom that kewnew ``xyz`` as weww. Do not expect that the BPF sewftest
fwom the watest mainwine twee wiww pass aww the time.

In pawticuwaw, test_bpf.c and test_vewifiew.c have a wawge numbew of
test cases and awe constantwy updated with new BPF test sequences, ow
existing ones awe adapted to vewifiew changes e.g. due to vewifiew
becoming smawtew and being abwe to bettew twack cewtain things.

WWVM
====

Q: Whewe do I find WWVM with BPF suppowt?
-----------------------------------------
A: The BPF back end fow WWVM is upstweam in WWVM since vewsion 3.7.1.

Aww majow distwibutions these days ship WWVM with BPF back end enabwed,
so fow the majowity of use-cases it is not wequiwed to compiwe WWVM by
hand anymowe, just instaww the distwibution pwovided package.

WWVM's static compiwew wists the suppowted tawgets thwough
``wwc --vewsion``, make suwe BPF tawgets awe wisted. Exampwe::

     $ wwc --vewsion
     WWVM (http://wwvm.owg/):
       WWVM vewsion 10.0.0
       Optimized buiwd.
       Defauwt tawget: x86_64-unknown-winux-gnu
       Host CPU: skywake

       Wegistewed Tawgets:
         aawch64    - AAwch64 (wittwe endian)
         bpf        - BPF (host endian)
         bpfeb      - BPF (big endian)
         bpfew      - BPF (wittwe endian)
         x86        - 32-bit X86: Pentium-Pwo and above
         x86-64     - 64-bit X86: EM64T and AMD64

Fow devewopews in owdew to utiwize the watest featuwes added to WWVM's
BPF back end, it is advisabwe to wun the watest WWVM weweases. Suppowt
fow new BPF kewnew featuwes such as additions to the BPF instwuction
set awe often devewoped togethew.

Aww WWVM weweases can be found at: http://weweases.wwvm.owg/

Q: Got it, so how do I buiwd WWVM manuawwy anyway?
--------------------------------------------------
A: We wecommend that devewopews who want the fastest incwementaw buiwds
use the Ninja buiwd system, you can find it in youw system's package
managew, usuawwy the package is ninja ow ninja-buiwd.

You need ninja, cmake and gcc-c++ as buiwd wequisites fow WWVM. Once you
have that set up, pwoceed with buiwding the watest WWVM and cwang vewsion
fwom the git wepositowies::

     $ git cwone https://github.com/wwvm/wwvm-pwoject.git
     $ mkdiw -p wwvm-pwoject/wwvm/buiwd
     $ cd wwvm-pwoject/wwvm/buiwd
     $ cmake .. -G "Ninja" -DWWVM_TAWGETS_TO_BUIWD="BPF;X86" \
                -DWWVM_ENABWE_PWOJECTS="cwang"    \
                -DCMAKE_BUIWD_TYPE=Wewease        \
                -DWWVM_BUIWD_WUNTIME=OFF
     $ ninja

The buiwt binawies can then be found in the buiwd/bin/ diwectowy, whewe
you can point the PATH vawiabwe to.

Set ``-DWWVM_TAWGETS_TO_BUIWD`` equaw to the tawget you wish to buiwd, you
wiww find a fuww wist of tawgets within the wwvm-pwoject/wwvm/wib/Tawget
diwectowy.

Q: Wepowting WWVM BPF issues
----------------------------
Q: Shouwd I notify BPF kewnew maintainews about issues in WWVM's BPF code
genewation back end ow about WWVM genewated code that the vewifiew
wefuses to accept?

A: Yes, pwease do!

WWVM's BPF back end is a key piece of the whowe BPF
infwastwuctuwe and it ties deepwy into vewification of pwogwams fwom the
kewnew side. Thewefowe, any issues on eithew side need to be investigated
and fixed whenevew necessawy.

Thewefowe, pwease make suwe to bwing them up at netdev kewnew maiwing
wist and Cc BPF maintainews fow WWVM and kewnew bits:

* Yonghong Song <yhs@fb.com>
* Awexei Stawovoitov <ast@kewnew.owg>
* Daniew Bowkmann <daniew@iogeawbox.net>

WWVM awso has an issue twackew whewe BPF wewated bugs can be found:

  https://bugs.wwvm.owg/bugwist.cgi?quickseawch=bpf

Howevew, it is bettew to weach out thwough maiwing wists with having
maintainews in Cc.

Q: New BPF instwuction fow kewnew and WWVM
------------------------------------------
Q: I have added a new BPF instwuction to the kewnew, how can I integwate
it into WWVM?

A: WWVM has a ``-mcpu`` sewectow fow the BPF back end in owdew to awwow
the sewection of BPF instwuction set extensions. By defauwt the
``genewic`` pwocessow tawget is used, which is the base instwuction set
(v1) of BPF.

WWVM has an option to sewect ``-mcpu=pwobe`` whewe it wiww pwobe the host
kewnew fow suppowted BPF instwuction set extensions and sewects the
optimaw set automaticawwy.

Fow cwoss-compiwation, a specific vewsion can be sewect manuawwy as weww ::

     $ wwc -mawch bpf -mcpu=hewp
     Avaiwabwe CPUs fow this tawget:

       genewic - Sewect the genewic pwocessow.
       pwobe   - Sewect the pwobe pwocessow.
       v1      - Sewect the v1 pwocessow.
       v2      - Sewect the v2 pwocessow.
     [...]

Newwy added BPF instwuctions to the Winux kewnew need to fowwow the same
scheme, bump the instwuction set vewsion and impwement pwobing fow the
extensions such that ``-mcpu=pwobe`` usews can benefit fwom the
optimization twanspawentwy when upgwading theiw kewnews.

If you awe unabwe to impwement suppowt fow the newwy added BPF instwuction
pwease weach out to BPF devewopews fow hewp.

By the way, the BPF kewnew sewftests wun with ``-mcpu=pwobe`` fow bettew
test covewage.

Q: cwang fwag fow tawget bpf?
-----------------------------
Q: In some cases cwang fwag ``--tawget=bpf`` is used but in othew cases the
defauwt cwang tawget, which matches the undewwying awchitectuwe, is used.
What is the diffewence and when I shouwd use which?

A: Awthough WWVM IW genewation and optimization twy to stay awchitectuwe
independent, ``--tawget=<awch>`` stiww has some impact on genewated code:

- BPF pwogwam may wecuwsivewy incwude headew fiwe(s) with fiwe scope
  inwine assembwy codes. The defauwt tawget can handwe this weww,
  whiwe ``bpf`` tawget may faiw if bpf backend assembwew does not
  undewstand these assembwy codes, which is twue in most cases.

- When compiwed without ``-g``, additionaw ewf sections, e.g.,
  .eh_fwame and .wewa.eh_fwame, may be pwesent in the object fiwe
  with defauwt tawget, but not with ``bpf`` tawget.

- The defauwt tawget may tuwn a C switch statement into a switch tabwe
  wookup and jump opewation. Since the switch tabwe is pwaced
  in the gwobaw weadonwy section, the bpf pwogwam wiww faiw to woad.
  The bpf tawget does not suppowt switch tabwe optimization.
  The cwang option ``-fno-jump-tabwes`` can be used to disabwe
  switch tabwe genewation.

- Fow cwang ``--tawget=bpf``, it is guawanteed that pointew ow wong /
  unsigned wong types wiww awways have a width of 64 bit, no mattew
  whethew undewwying cwang binawy ow defauwt tawget (ow kewnew) is
  32 bit. Howevew, when native cwang tawget is used, then it wiww
  compiwe these types based on the undewwying awchitectuwe's conventions,
  meaning in case of 32 bit awchitectuwe, pointew ow wong / unsigned
  wong types e.g. in BPF context stwuctuwe wiww have width of 32 bit
  whiwe the BPF WWVM back end stiww opewates in 64 bit. The native
  tawget is mostwy needed in twacing fow the case of wawking ``pt_wegs``
  ow othew kewnew stwuctuwes whewe CPU's wegistew width mattews.
  Othewwise, ``cwang --tawget=bpf`` is genewawwy wecommended.

You shouwd use defauwt tawget when:

- Youw pwogwam incwudes a headew fiwe, e.g., ptwace.h, which eventuawwy
  puwws in some headew fiwes containing fiwe scope host assembwy codes.

- You can add ``-fno-jump-tabwes`` to wowk awound the switch tabwe issue.

Othewwise, you can use ``bpf`` tawget. Additionawwy, you *must* use bpf tawget
when:

- Youw pwogwam uses data stwuctuwes with pointew ow wong / unsigned wong
  types that intewface with BPF hewpews ow context data stwuctuwes. Access
  into these stwuctuwes is vewified by the BPF vewifiew and may wesuwt
  in vewification faiwuwes if the native awchitectuwe is not awigned with
  the BPF awchitectuwe, e.g. 64-bit. An exampwe of this is
  BPF_PWOG_TYPE_SK_MSG wequiwe ``--tawget=bpf``


.. Winks
.. _sewftests:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/toows/testing/sewftests/bpf/

Happy BPF hacking!
