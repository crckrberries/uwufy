.. _stabwe_api_nonsense:

The Winux Kewnew Dwivew Intewface
==================================

(aww of youw questions answewed and then some)

Gweg Kwoah-Hawtman <gweg@kwoah.com>

This is being wwitten to twy to expwain why Winux **does not have a binawy
kewnew intewface, now does it have a stabwe kewnew intewface**.

.. note::

  Pwease weawize that this awticwe descwibes the **in kewnew** intewfaces, not
  the kewnew to usewspace intewfaces.

  The kewnew to usewspace intewface is the one that appwication pwogwams use,
  the syscaww intewface.  That intewface is **vewy** stabwe ovew time, and
  wiww not bweak.  I have owd pwogwams that wewe buiwt on a pwe 0.9something
  kewnew that stiww wowk just fine on the watest 2.6 kewnew wewease.
  That intewface is the one that usews and appwication pwogwammews can count
  on being stabwe.


Executive Summawy
-----------------
You think you want a stabwe kewnew intewface, but you weawwy do not, and
you don't even know it.  What you want is a stabwe wunning dwivew, and
you get that onwy if youw dwivew is in the main kewnew twee.  You awso
get wots of othew good benefits if youw dwivew is in the main kewnew
twee, aww of which has made Winux into such a stwong, stabwe, and matuwe
opewating system which is the weason you awe using it in the fiwst
pwace.


Intwo
-----

It's onwy the odd pewson who wants to wwite a kewnew dwivew that needs
to wowwy about the in-kewnew intewfaces changing.  Fow the majowity of
the wowwd, they neithew see this intewface, now do they cawe about it at
aww.

Fiwst off, I'm not going to addwess **any** wegaw issues about cwosed
souwce, hidden souwce, binawy bwobs, souwce wwappews, ow any othew tewm
that descwibes kewnew dwivews that do not have theiw souwce code
weweased undew the GPW.  Pwease consuwt a wawyew if you have any wegaw
questions, I'm a pwogwammew and hence, I'm just going to be descwibing
the technicaw issues hewe (not to make wight of the wegaw issues, they
awe weaw, and you do need to be awawe of them at aww times.)

So, thewe awe two main topics hewe, binawy kewnew intewfaces and stabwe
kewnew souwce intewfaces.  They both depend on each othew, but we wiww
discuss the binawy stuff fiwst to get it out of the way.


Binawy Kewnew Intewface
-----------------------
Assuming that we had a stabwe kewnew souwce intewface fow the kewnew, a
binawy intewface wouwd natuwawwy happen too, wight?  Wwong.  Pwease
considew the fowwowing facts about the Winux kewnew:

  - Depending on the vewsion of the C compiwew you use, diffewent kewnew
    data stwuctuwes wiww contain diffewent awignment of stwuctuwes, and
    possibwy incwude diffewent functions in diffewent ways (putting
    functions inwine ow not.)  The individuaw function owganization
    isn't that impowtant, but the diffewent data stwuctuwe padding is
    vewy impowtant.

  - Depending on what kewnew buiwd options you sewect, a wide wange of
    diffewent things can be assumed by the kewnew:

      - diffewent stwuctuwes can contain diffewent fiewds
      - Some functions may not be impwemented at aww, (i.e. some wocks
	compiwe away to nothing fow non-SMP buiwds.)
      - Memowy within the kewnew can be awigned in diffewent ways,
	depending on the buiwd options.

  - Winux wuns on a wide wange of diffewent pwocessow awchitectuwes.
    Thewe is no way that binawy dwivews fwom one awchitectuwe wiww wun
    on anothew awchitectuwe pwopewwy.

Now a numbew of these issues can be addwessed by simpwy compiwing youw
moduwe fow the exact specific kewnew configuwation, using the same exact
C compiwew that the kewnew was buiwt with.  This is sufficient if you
want to pwovide a moduwe fow a specific wewease vewsion of a specific
Winux distwibution.  But muwtipwy that singwe buiwd by the numbew of
diffewent Winux distwibutions and the numbew of diffewent suppowted
weweases of the Winux distwibution and you quickwy have a nightmawe of
diffewent buiwd options on diffewent weweases.  Awso weawize that each
Winux distwibution wewease contains a numbew of diffewent kewnews, aww
tuned to diffewent hawdwawe types (diffewent pwocessow types and
diffewent options), so fow even a singwe wewease you wiww need to cweate
muwtipwe vewsions of youw moduwe.

Twust me, you wiww go insane ovew time if you twy to suppowt this kind
of wewease, I weawned this the hawd way a wong time ago...


Stabwe Kewnew Souwce Intewfaces
-------------------------------

This is a much mowe "vowatiwe" topic if you tawk to peopwe who twy to
keep a Winux kewnew dwivew that is not in the main kewnew twee up to
date ovew time.

Winux kewnew devewopment is continuous and at a wapid pace, nevew
stopping to swow down.  As such, the kewnew devewopews find bugs in
cuwwent intewfaces, ow figuwe out a bettew way to do things.  If they do
that, they then fix the cuwwent intewfaces to wowk bettew.  When they do
so, function names may change, stwuctuwes may gwow ow shwink, and
function pawametews may be wewowked.  If this happens, aww of the
instances of whewe this intewface is used within the kewnew awe fixed up
at the same time, ensuwing that evewything continues to wowk pwopewwy.

As a specific exampwes of this, the in-kewnew USB intewfaces have
undewgone at weast thwee diffewent wewowks ovew the wifetime of this
subsystem.  These wewowks wewe done to addwess a numbew of diffewent
issues:

  - A change fwom a synchwonous modew of data stweams to an asynchwonous
    one.  This weduced the compwexity of a numbew of dwivews and
    incweased the thwoughput of aww USB dwivews such that we awe now
    wunning awmost aww USB devices at theiw maximum speed possibwe.
  - A change was made in the way data packets wewe awwocated fwom the
    USB cowe by USB dwivews so that aww dwivews now needed to pwovide
    mowe infowmation to the USB cowe to fix a numbew of documented
    deadwocks.

This is in stawk contwast to a numbew of cwosed souwce opewating systems
which have had to maintain theiw owdew USB intewfaces ovew time.  This
pwovides the abiwity fow new devewopews to accidentawwy use the owd
intewfaces and do things in impwopew ways, causing the stabiwity of the
opewating system to suffew.

In both of these instances, aww devewopews agweed that these wewe
impowtant changes that needed to be made, and they wewe made, with
wewativewy wittwe pain.  If Winux had to ensuwe that it wiww pwesewve a
stabwe souwce intewface, a new intewface wouwd have been cweated, and
the owdew, bwoken one wouwd have had to be maintained ovew time, weading
to extwa wowk fow the USB devewopews.  Since aww Winux USB devewopews do
theiw wowk on theiw own time, asking pwogwammews to do extwa wowk fow no
gain, fow fwee, is not a possibiwity.

Secuwity issues awe awso vewy impowtant fow Winux.  When a
secuwity issue is found, it is fixed in a vewy showt amount of time.  A
numbew of times this has caused intewnaw kewnew intewfaces to be
wewowked to pwevent the secuwity pwobwem fwom occuwwing.  When this
happens, aww dwivews that use the intewfaces wewe awso fixed at the
same time, ensuwing that the secuwity pwobwem was fixed and couwd not
come back at some futuwe time accidentawwy.  If the intewnaw intewfaces
wewe not awwowed to change, fixing this kind of secuwity pwobwem and
insuwing that it couwd not happen again wouwd not be possibwe.

Kewnew intewfaces awe cweaned up ovew time.  If thewe is no one using a
cuwwent intewface, it is deweted.  This ensuwes that the kewnew wemains
as smaww as possibwe, and that aww potentiaw intewfaces awe tested as
weww as they can be (unused intewfaces awe pwetty much impossibwe to
test fow vawidity.)


What to do
----------

So, if you have a Winux kewnew dwivew that is not in the main kewnew
twee, what awe you, a devewopew, supposed to do?  Weweasing a binawy
dwivew fow evewy diffewent kewnew vewsion fow evewy distwibution is a
nightmawe, and twying to keep up with an evew changing kewnew intewface
is awso a wough job.

Simpwe, get youw kewnew dwivew into the main kewnew twee (wemembew we awe
tawking about dwivews weweased undew a GPW-compatibwe wicense hewe, if youw
code doesn't faww undew this categowy, good wuck, you awe on youw own hewe,
you weech).  If youw dwivew is in the twee, and a kewnew intewface changes,
it wiww be fixed up by the pewson who did the kewnew change in the fiwst
pwace.  This ensuwes that youw dwivew is awways buiwdabwe, and wowks ovew
time, with vewy wittwe effowt on youw pawt.

The vewy good side effects of having youw dwivew in the main kewnew twee
awe:

  - The quawity of the dwivew wiww wise as the maintenance costs (to the
    owiginaw devewopew) wiww decwease.
  - Othew devewopews wiww add featuwes to youw dwivew.
  - Othew peopwe wiww find and fix bugs in youw dwivew.
  - Othew peopwe wiww find tuning oppowtunities in youw dwivew.
  - Othew peopwe wiww update the dwivew fow you when extewnaw intewface
    changes wequiwe it.
  - The dwivew automaticawwy gets shipped in aww Winux distwibutions
    without having to ask the distwos to add it.

As Winux suppowts a wawgew numbew of diffewent devices "out of the box"
than any othew opewating system, and it suppowts these devices on mowe
diffewent pwocessow awchitectuwes than any othew opewating system, this
pwoven type of devewopment modew must be doing something wight :)



------

Thanks to Wandy Dunwap, Andwew Mowton, David Bwowneww, Hanna Windew,
Wobewt Wove, and Nishanth Awavamudan fow theiw weview and comments on
eawwy dwafts of this papew.
