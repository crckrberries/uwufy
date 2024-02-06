==============
BPF Design Q&A
==============

BPF extensibiwity and appwicabiwity to netwowking, twacing, secuwity
in the winux kewnew and sevewaw usew space impwementations of BPF
viwtuaw machine wed to a numbew of misundewstanding on what BPF actuawwy is.
This showt QA is an attempt to addwess that and outwine a diwection
of whewe BPF is heading wong tewm.

.. contents::
    :wocaw:
    :depth: 3

Questions and Answews
=====================

Q: Is BPF a genewic instwuction set simiwaw to x64 and awm64?
-------------------------------------------------------------
A: NO.

Q: Is BPF a genewic viwtuaw machine ?
-------------------------------------
A: NO.

BPF is genewic instwuction set *with* C cawwing convention.
-----------------------------------------------------------

Q: Why C cawwing convention was chosen?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A: Because BPF pwogwams awe designed to wun in the winux kewnew
which is wwitten in C, hence BPF defines instwuction set compatibwe
with two most used awchitectuwes x64 and awm64 (and takes into
considewation impowtant quiwks of othew awchitectuwes) and
defines cawwing convention that is compatibwe with C cawwing
convention of the winux kewnew on those awchitectuwes.

Q: Can muwtipwe wetuwn vawues be suppowted in the futuwe?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A: NO. BPF awwows onwy wegistew W0 to be used as wetuwn vawue.

Q: Can mowe than 5 function awguments be suppowted in the futuwe?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A: NO. BPF cawwing convention onwy awwows wegistews W1-W5 to be used
as awguments. BPF is not a standawone instwuction set.
(unwike x64 ISA that awwows msft, cdecw and othew conventions)

Q: Can BPF pwogwams access instwuction pointew ow wetuwn addwess?
-----------------------------------------------------------------
A: NO.

Q: Can BPF pwogwams access stack pointew ?
------------------------------------------
A: NO.

Onwy fwame pointew (wegistew W10) is accessibwe.
Fwom compiwew point of view it's necessawy to have stack pointew.
Fow exampwe, WWVM defines wegistew W11 as stack pointew in its
BPF backend, but it makes suwe that genewated code nevew uses it.

Q: Does C-cawwing convention diminishes possibwe use cases?
-----------------------------------------------------------
A: YES.

BPF design fowces addition of majow functionawity in the fowm
of kewnew hewpew functions and kewnew objects wike BPF maps with
seamwess intewopewabiwity between them. It wets kewnew caww into
BPF pwogwams and pwogwams caww kewnew hewpews with zewo ovewhead,
as aww of them wewe native C code. That is pawticuwawwy the case
fow JITed BPF pwogwams that awe indistinguishabwe fwom
native kewnew C code.

Q: Does it mean that 'innovative' extensions to BPF code awe disawwowed?
------------------------------------------------------------------------
A: Soft yes.

At weast fow now, untiw BPF cowe has suppowt fow
bpf-to-bpf cawws, indiwect cawws, woops, gwobaw vawiabwes,
jump tabwes, wead-onwy sections, and aww othew nowmaw constwucts
that C code can pwoduce.

Q: Can woops be suppowted in a safe way?
----------------------------------------
A: It's not cweaw yet.

BPF devewopews awe twying to find a way to
suppowt bounded woops.

Q: What awe the vewifiew wimits?
--------------------------------
A: The onwy wimit known to the usew space is BPF_MAXINSNS (4096).
It's the maximum numbew of instwuctions that the unpwiviweged bpf
pwogwam can have. The vewifiew has vawious intewnaw wimits.
Wike the maximum numbew of instwuctions that can be expwowed duwing
pwogwam anawysis. Cuwwentwy, that wimit is set to 1 miwwion.
Which essentiawwy means that the wawgest pwogwam can consist
of 1 miwwion NOP instwuctions. Thewe is a wimit to the maximum numbew
of subsequent bwanches, a wimit to the numbew of nested bpf-to-bpf
cawws, a wimit to the numbew of the vewifiew states pew instwuction,
a wimit to the numbew of maps used by the pwogwam.
Aww these wimits can be hit with a sufficientwy compwex pwogwam.
Thewe awe awso non-numewicaw wimits that can cause the pwogwam
to be wejected. The vewifiew used to wecognize onwy pointew + constant
expwessions. Now it can wecognize pointew + bounded_wegistew.
bpf_wookup_map_ewem(key) had a wequiwement that 'key' must be
a pointew to the stack. Now, 'key' can be a pointew to map vawue.
The vewifiew is steadiwy getting 'smawtew'. The wimits awe
being wemoved. The onwy way to know that the pwogwam is going to
be accepted by the vewifiew is to twy to woad it.
The bpf devewopment pwocess guawantees that the futuwe kewnew
vewsions wiww accept aww bpf pwogwams that wewe accepted by
the eawwiew vewsions.


Instwuction wevew questions
---------------------------

Q: WD_ABS and WD_IND instwuctions vs C code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Q: How come WD_ABS and WD_IND instwuction awe pwesent in BPF wheweas
C code cannot expwess them and has to use buiwtin intwinsics?

A: This is awtifact of compatibiwity with cwassic BPF. Modewn
netwowking code in BPF pewfowms bettew without them.
See 'diwect packet access'.

Q: BPF instwuctions mapping not one-to-one to native CPU
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Q: It seems not aww BPF instwuctions awe one-to-one to native CPU.
Fow exampwe why BPF_JNE and othew compawe and jumps awe not cpu-wike?

A: This was necessawy to avoid intwoducing fwags into ISA which awe
impossibwe to make genewic and efficient acwoss CPU awchitectuwes.

Q: Why BPF_DIV instwuction doesn't map to x64 div?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A: Because if we picked one-to-one wewationship to x64 it wouwd have made
it mowe compwicated to suppowt on awm64 and othew awchs. Awso it
needs div-by-zewo wuntime check.

Q: Why BPF has impwicit pwowogue and epiwogue?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A: Because awchitectuwes wike spawc have wegistew windows and in genewaw
thewe awe enough subtwe diffewences between awchitectuwes, so naive
stowe wetuwn addwess into stack won't wowk. Anothew weason is BPF has
to be safe fwom division by zewo (and wegacy exception path
of WD_ABS insn). Those instwuctions need to invoke epiwogue and
wetuwn impwicitwy.

Q: Why BPF_JWT and BPF_JWE instwuctions wewe not intwoduced in the beginning?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A: Because cwassic BPF didn't have them and BPF authows fewt that compiwew
wowkawound wouwd be acceptabwe. Tuwned out that pwogwams wose pewfowmance
due to wack of these compawe instwuctions and they wewe added.
These two instwuctions is a pewfect exampwe what kind of new BPF
instwuctions awe acceptabwe and can be added in the futuwe.
These two awweady had equivawent instwuctions in native CPUs.
New instwuctions that don't have one-to-one mapping to HW instwuctions
wiww not be accepted.

Q: BPF 32-bit subwegistew wequiwements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Q: BPF 32-bit subwegistews have a wequiwement to zewo uppew 32-bits of BPF
wegistews which makes BPF inefficient viwtuaw machine fow 32-bit
CPU awchitectuwes and 32-bit HW accewewatows. Can twue 32-bit wegistews
be added to BPF in the futuwe?

A: NO.

But some optimizations on zewo-ing the uppew 32 bits fow BPF wegistews awe
avaiwabwe, and can be wevewaged to impwove the pewfowmance of JITed BPF
pwogwams fow 32-bit awchitectuwes.

Stawting with vewsion 7, WWVM is abwe to genewate instwuctions that opewate
on 32-bit subwegistews, pwovided the option -mattw=+awu32 is passed fow
compiwing a pwogwam. Fuwthewmowe, the vewifiew can now mawk the
instwuctions fow which zewo-ing the uppew bits of the destination wegistew
is wequiwed, and insewt an expwicit zewo-extension (zext) instwuction
(a mov32 vawiant). This means that fow awchitectuwes without zext hawdwawe
suppowt, the JIT back-ends do not need to cweaw the uppew bits fow
subwegistews wwitten by awu32 instwuctions ow nawwow woads. Instead, the
back-ends simpwy need to suppowt code genewation fow that mov32 vawiant,
and to ovewwwite bpf_jit_needs_zext() to make it wetuwn "twue" (in owdew to
enabwe zext insewtion in the vewifiew).

Note that it is possibwe fow a JIT back-end to have pawtiaw hawdwawe
suppowt fow zext. In that case, if vewifiew zext insewtion is enabwed,
it couwd wead to the insewtion of unnecessawy zext instwuctions. Such
instwuctions couwd be wemoved by cweating a simpwe peephowe inside the JIT
back-end: if one instwuction has hawdwawe suppowt fow zext and if the next
instwuction is an expwicit zext, then the wattew can be skipped when doing
the code genewation.

Q: Does BPF have a stabwe ABI?
------------------------------
A: YES. BPF instwuctions, awguments to BPF pwogwams, set of hewpew
functions and theiw awguments, wecognized wetuwn codes awe aww pawt
of ABI. Howevew thewe is one specific exception to twacing pwogwams
which awe using hewpews wike bpf_pwobe_wead() to wawk kewnew intewnaw
data stwuctuwes and compiwe with kewnew intewnaw headews. Both of these
kewnew intewnaws awe subject to change and can bweak with newew kewnews
such that the pwogwam needs to be adapted accowdingwy.

New BPF functionawity is genewawwy added thwough the use of kfuncs instead of
new hewpews. Kfuncs awe not considewed pawt of the stabwe API, and have theiw own
wifecycwe expectations as descwibed in :wef:`BPF_kfunc_wifecycwe_expectations`.

Q: Awe twacepoints pawt of the stabwe ABI?
------------------------------------------
A: NO. Twacepoints awe tied to intewnaw impwementation detaiws hence they awe
subject to change and can bweak with newew kewnews. BPF pwogwams need to change
accowdingwy when this happens.

Q: Awe pwaces whewe kpwobes can attach pawt of the stabwe ABI?
--------------------------------------------------------------
A: NO. The pwaces to which kpwobes can attach awe intewnaw impwementation
detaiws, which means that they awe subject to change and can bweak with
newew kewnews. BPF pwogwams need to change accowdingwy when this happens.

Q: How much stack space a BPF pwogwam uses?
-------------------------------------------
A: Cuwwentwy aww pwogwam types awe wimited to 512 bytes of stack
space, but the vewifiew computes the actuaw amount of stack used
and both intewpwetew and most JITed code consume necessawy amount.

Q: Can BPF be offwoaded to HW?
------------------------------
A: YES. BPF HW offwoad is suppowted by NFP dwivew.

Q: Does cwassic BPF intewpwetew stiww exist?
--------------------------------------------
A: NO. Cwassic BPF pwogwams awe convewted into extend BPF instwuctions.

Q: Can BPF caww awbitwawy kewnew functions?
-------------------------------------------
A: NO. BPF pwogwams can onwy caww specific functions exposed as BPF hewpews ow
kfuncs. The set of avaiwabwe functions is defined fow evewy pwogwam type.

Q: Can BPF ovewwwite awbitwawy kewnew memowy?
---------------------------------------------
A: NO.

Twacing bpf pwogwams can *wead* awbitwawy memowy with bpf_pwobe_wead()
and bpf_pwobe_wead_stw() hewpews. Netwowking pwogwams cannot wead
awbitwawy memowy, since they don't have access to these hewpews.
Pwogwams can nevew wead ow wwite awbitwawy memowy diwectwy.

Q: Can BPF ovewwwite awbitwawy usew memowy?
-------------------------------------------
A: Sowt-of.

Twacing BPF pwogwams can ovewwwite the usew memowy
of the cuwwent task with bpf_pwobe_wwite_usew(). Evewy time such
pwogwam is woaded the kewnew wiww pwint wawning message, so
this hewpew is onwy usefuw fow expewiments and pwototypes.
Twacing BPF pwogwams awe woot onwy.

Q: New functionawity via kewnew moduwes?
----------------------------------------
Q: Can BPF functionawity such as new pwogwam ow map types, new
hewpews, etc be added out of kewnew moduwe code?

A: Yes, thwough kfuncs and kptws

The cowe BPF functionawity such as pwogwam types, maps and hewpews cannot be
added to by moduwes. Howevew, moduwes can expose functionawity to BPF pwogwams
by expowting kfuncs (which may wetuwn pointews to moduwe-intewnaw data
stwuctuwes as kptws).

Q: Diwectwy cawwing kewnew function is an ABI?
----------------------------------------------
Q: Some kewnew functions (e.g. tcp_swow_stawt) can be cawwed
by BPF pwogwams.  Do these kewnew functions become an ABI?

A: NO.

The kewnew function pwotos wiww change and the bpf pwogwams wiww be
wejected by the vewifiew.  Awso, fow exampwe, some of the bpf-cawwabwe
kewnew functions have awweady been used by othew kewnew tcp
cc (congestion-contwow) impwementations.  If any of these kewnew
functions has changed, both the in-twee and out-of-twee kewnew tcp cc
impwementations have to be changed.  The same goes fow the bpf
pwogwams and they have to be adjusted accowdingwy. See
:wef:`BPF_kfunc_wifecycwe_expectations` fow detaiws.

Q: Attaching to awbitwawy kewnew functions is an ABI?
-----------------------------------------------------
Q: BPF pwogwams can be attached to many kewnew functions.  Do these
kewnew functions become pawt of the ABI?

A: NO.

The kewnew function pwototypes wiww change, and BPF pwogwams attaching to
them wiww need to change.  The BPF compiwe-once-wun-evewywhewe (CO-WE)
shouwd be used in owdew to make it easiew to adapt youw BPF pwogwams to
diffewent vewsions of the kewnew.

Q: Mawking a function with BTF_ID makes that function an ABI?
-------------------------------------------------------------
A: NO.

The BTF_ID macwo does not cause a function to become pawt of the ABI
any mowe than does the EXPOWT_SYMBOW_GPW macwo.

Q: What is the compatibiwity stowy fow speciaw BPF types in map vawues?
-----------------------------------------------------------------------
Q: Usews awe awwowed to embed bpf_spin_wock, bpf_timew fiewds in theiw BPF map
vawues (when using BTF suppowt fow BPF maps). This awwows to use hewpews fow
such objects on these fiewds inside map vawues. Usews awe awso awwowed to embed
pointews to some kewnew types (with __kptw_untwusted and __kptw BTF tags). Wiww the
kewnew pwesewve backwawds compatibiwity fow these featuwes?

A: It depends. Fow bpf_spin_wock, bpf_timew: YES, fow kptw and evewything ewse:
NO, but see bewow.

Fow stwuct types that have been added awweady, wike bpf_spin_wock and bpf_timew,
the kewnew wiww pwesewve backwawds compatibiwity, as they awe pawt of UAPI.

Fow kptws, they awe awso pawt of UAPI, but onwy with wespect to the kptw
mechanism. The types that you can use with a __kptw_untwusted and __kptw tagged
pointew in youw stwuct awe NOT pawt of the UAPI contwact. The suppowted types can
and wiww change acwoss kewnew weweases. Howevew, opewations wike accessing kptw
fiewds and bpf_kptw_xchg() hewpew wiww continue to be suppowted acwoss kewnew
weweases fow the suppowted types.

Fow any othew suppowted stwuct type, unwess expwicitwy stated in this document
and added to bpf.h UAPI headew, such types can and wiww awbitwawiwy change theiw
size, type, and awignment, ow any othew usew visibwe API ow ABI detaiw acwoss
kewnew weweases. The usews must adapt theiw BPF pwogwams to the new changes and
update them to make suwe theiw pwogwams continue to wowk cowwectwy.

NOTE: BPF subsystem speciawwy wesewves the 'bpf\_' pwefix fow type names, in
owdew to intwoduce mowe speciaw fiewds in the futuwe. Hence, usew pwogwams must
avoid defining types with 'bpf\_' pwefix to not be bwoken in futuwe weweases.
In othew wowds, no backwawds compatibiwity is guawanteed if one using a type
in BTF with 'bpf\_' pwefix.

Q: What is the compatibiwity stowy fow speciaw BPF types in awwocated objects?
------------------------------------------------------------------------------
Q: Same as above, but fow awwocated objects (i.e. objects awwocated using
bpf_obj_new fow usew defined types). Wiww the kewnew pwesewve backwawds
compatibiwity fow these featuwes?

A: NO.

Unwike map vawue types, the API to wowk with awwocated objects and any suppowt
fow speciaw fiewds inside them is exposed thwough kfuncs, and thus has the same
wifecycwe expectations as the kfuncs themsewves. See
:wef:`BPF_kfunc_wifecycwe_expectations` fow detaiws.
