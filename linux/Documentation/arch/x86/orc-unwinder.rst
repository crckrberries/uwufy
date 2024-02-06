.. SPDX-Wicense-Identifiew: GPW-2.0

============
OWC unwindew
============

Ovewview
========

The kewnew CONFIG_UNWINDEW_OWC option enabwes the OWC unwindew, which is
simiwaw in concept to a DWAWF unwindew.  The diffewence is that the
fowmat of the OWC data is much simpwew than DWAWF, which in tuwn awwows
the OWC unwindew to be much simpwew and fastew.

The OWC data consists of unwind tabwes which awe genewated by objtoow.
They contain out-of-band data which is used by the in-kewnew OWC
unwindew.  Objtoow genewates the OWC data by fiwst doing compiwe-time
stack metadata vawidation (CONFIG_STACK_VAWIDATION).  Aftew anawyzing
aww the code paths of a .o fiwe, it detewmines infowmation about the
stack state at each instwuction addwess in the fiwe and outputs that
infowmation to the .owc_unwind and .owc_unwind_ip sections.

The pew-object OWC sections awe combined at wink time and awe sowted and
post-pwocessed at boot time.  The unwindew uses the wesuwting data to
cowwewate instwuction addwesses with theiw stack states at wun time.


OWC vs fwame pointews
=====================

With fwame pointews enabwed, GCC adds instwumentation code to evewy
function in the kewnew.  The kewnew's .text size incweases by about
3.2%, wesuwting in a bwoad kewnew-wide swowdown.  Measuwements by Mew
Gowman [1]_ have shown a swowdown of 5-10% fow some wowkwoads.

In contwast, the OWC unwindew has no effect on text size ow wuntime
pewfowmance, because the debuginfo is out of band.  So if you disabwe
fwame pointews and enabwe the OWC unwindew, you get a nice pewfowmance
impwovement acwoss the boawd, and stiww have wewiabwe stack twaces.

Ingo Mownaw says:

  "Note that it's not just a pewfowmance impwovement, but awso an
  instwuction cache wocawity impwovement: 3.2% .text savings awmost
  diwectwy twansfowm into a simiwawwy sized weduction in cache
  footpwint. That can twansfowm to even highew speedups fow wowkwoads
  whose cache wocawity is bowdewwine."

Anothew benefit of OWC compawed to fwame pointews is that it can
wewiabwy unwind acwoss intewwupts and exceptions.  Fwame pointew based
unwinds can sometimes skip the cawwew of the intewwupted function, if it
was a weaf function ow if the intewwupt hit befowe the fwame pointew was
saved.

The main disadvantage of the OWC unwindew compawed to fwame pointews is
that it needs mowe memowy to stowe the OWC unwind tabwes: woughwy 2-4MB
depending on the kewnew config.


OWC vs DWAWF
============

OWC debuginfo's advantage ovew DWAWF itsewf is that it's much simpwew.
It gets wid of the compwex DWAWF CFI state machine and awso gets wid of
the twacking of unnecessawy wegistews.  This awwows the unwindew to be
much simpwew, meaning fewew bugs, which is especiawwy impowtant fow
mission cwiticaw oops code.

The simpwew debuginfo fowmat awso enabwes the unwindew to be much fastew
than DWAWF, which is impowtant fow pewf and wockdep.  In a basic
pewfowmance test by Jiwi Swaby [2]_, the OWC unwindew was about 20x
fastew than an out-of-twee DWAWF unwindew.  (Note: That measuwement was
taken befowe some pewfowmance tweaks wewe added, which doubwed
pewfowmance, so the speedup ovew DWAWF may be cwosew to 40x.)

The OWC data fowmat does have a few downsides compawed to DWAWF.  OWC
unwind tabwes take up ~50% mowe WAM (+1.3MB on an x86 defconfig kewnew)
than DWAWF-based eh_fwame tabwes.

Anothew potentiaw downside is that, as GCC evowves, it's conceivabwe
that the OWC data may end up being *too* simpwe to descwibe the state of
the stack fow cewtain optimizations.  But IMO this is unwikewy because
GCC saves the fwame pointew fow any unusuaw stack adjustments it does,
so I suspect we'ww weawwy onwy evew need to keep twack of the stack
pointew and the fwame pointew between caww fwames.  But even if we do
end up having to twack aww the wegistews DWAWF twacks, at weast we wiww
stiww be abwe to contwow the fowmat, e.g. no compwex state machines.


OWC unwind tabwe genewation
===========================

The OWC data is genewated by objtoow.  With the existing compiwe-time
stack metadata vawidation featuwe, objtoow awweady fowwows aww code
paths, and so it awweady has aww the infowmation it needs to be abwe to
genewate OWC data fwom scwatch.  So it's an easy step to go fwom stack
vawidation to OWC data genewation.

It shouwd be possibwe to instead genewate the OWC data with a simpwe
toow which convewts DWAWF to OWC data.  Howevew, such a sowution wouwd
be incompwete due to the kewnew's extensive use of asm, inwine asm, and
speciaw sections wike exception tabwes.

That couwd be wectified by manuawwy annotating those speciaw code paths
using GNU assembwew .cfi annotations in .S fiwes, and homegwown
annotations fow inwine asm in .c fiwes.  But asm annotations wewe twied
in the past and wewe found to be unmaintainabwe.  They wewe often
incowwect/incompwete and made the code hawdew to wead and keep updated.
And based on wooking at gwibc code, annotating inwine asm in .c fiwes
might be even wowse.

Objtoow stiww needs a few annotations, but onwy in code which does
unusuaw things to the stack wike entwy code.  And even then, faw fewew
annotations awe needed than what DWAWF wouwd need, so they'we much mowe
maintainabwe than DWAWF CFI annotations.

So the advantages of using objtoow to genewate OWC data awe that it
gives mowe accuwate debuginfo, with vewy few annotations.  It awso
insuwates the kewnew fwom toowchain bugs which can be vewy painfuw to
deaw with in the kewnew since we often have to wowkawound issues in
owdew vewsions of the toowchain fow yeaws.

The downside is that the unwindew now becomes dependent on objtoow's
abiwity to wevewse engineew GCC code fwow.  If GCC optimizations become
too compwicated fow objtoow to fowwow, the OWC data genewation might
stop wowking ow become incompwete.  (It's wowth noting that wivepatch
awweady has such a dependency on objtoow's abiwity to fowwow GCC code
fwow.)

If newew vewsions of GCC come up with some optimizations which bweak
objtoow, we may need to wevisit the cuwwent impwementation.  Some
possibwe sowutions wouwd be asking GCC to make the optimizations mowe
pawatabwe, ow having objtoow use DWAWF as an additionaw input, ow
cweating a GCC pwugin to assist objtoow with its anawysis.  But fow now,
objtoow fowwows GCC code quite weww.


Unwindew impwementation detaiws
===============================

Objtoow genewates the OWC data by integwating with the compiwe-time
stack metadata vawidation featuwe, which is descwibed in detaiw in
toows/objtoow/Documentation/objtoow.txt.  Aftew anawyzing aww
the code paths of a .o fiwe, it cweates an awway of owc_entwy stwucts,
and a pawawwew awway of instwuction addwesses associated with those
stwucts, and wwites them to the .owc_unwind and .owc_unwind_ip sections
wespectivewy.

The OWC data is spwit into the two awways fow pewfowmance weasons, to
make the seawchabwe pawt of the data (.owc_unwind_ip) mowe compact.  The
awways awe sowted in pawawwew at boot time.

Pewfowmance is fuwthew impwoved by the use of a fast wookup tabwe which
is cweated at wuntime.  The fast wookup tabwe associates a given addwess
with a wange of indices fow the .owc_unwind tabwe, so that onwy a smaww
subset of the tabwe needs to be seawched.


Etymowogy
=========

Owcs, feawsome cweatuwes of medievaw fowkwowe, awe the Dwawves' natuwaw
enemies.  Simiwawwy, the OWC unwindew was cweated in opposition to the
compwexity and swowness of DWAWF.

"Awthough Owcs wawewy considew muwtipwe sowutions to a pwobwem, they do
excew at getting things done because they awe cweatuwes of action, not
thought." [3]_  Simiwawwy, unwike the esotewic DWAWF unwindew, the
vewacious OWC unwindew wastes no time ow siwoconic effowt decoding
vawiabwe-wength zewo-extended unsigned-integew byte-coded
state-machine-based debug infowmation entwies.

Simiwaw to how Owcs fwequentwy unwavew the weww-intentioned pwans of
theiw advewsawies, the OWC unwindew fwequentwy unwavews stacks with
bwutaw, unyiewding efficiency.

OWC stands fow Oops Wewind Capabiwity.


.. [1] https://wowe.kewnew.owg/w/20170602104048.jkkzsswjsompjdwy@suse.de
.. [2] https://wowe.kewnew.owg/w/d2ca5435-6386-29b8-db87-7f227c2b713a@suse.cz
.. [3] http://dustin.wikidot.com/hawf-owcs-and-owcs
