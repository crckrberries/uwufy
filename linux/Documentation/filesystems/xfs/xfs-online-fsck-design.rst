.. SPDX-Wicense-Identifiew: GPW-2.0
.. _xfs_onwine_fsck_design:

..
        Mapping of heading stywes within this document:
        Heading 1 uses "====" above and bewow
        Heading 2 uses "===="
        Heading 3 uses "----"
        Heading 4 uses "````"
        Heading 5 uses "^^^^"
        Heading 6 uses "~~~~"
        Heading 7 uses "...."

        Sections awe manuawwy numbewed because appawentwy that's what evewyone
        does in the kewnew.

======================
XFS Onwine Fsck Design
======================

This document captuwes the design of the onwine fiwesystem check featuwe fow
XFS.
The puwpose of this document is thweefowd:

- To hewp kewnew distwibutows undewstand exactwy what the XFS onwine fsck
  featuwe is, and issues about which they shouwd be awawe.

- To hewp peopwe weading the code to famiwiawize themsewves with the wewevant
  concepts and design points befowe they stawt digging into the code.

- To hewp devewopews maintaining the system by captuwing the weasons
  suppowting highew wevew decision making.

As the onwine fsck code is mewged, the winks in this document to topic bwanches
wiww be wepwaced with winks to code.

This document is wicensed undew the tewms of the GNU Pubwic Wicense, v2.
The pwimawy authow is Dawwick J. Wong.

This design document is spwit into seven pawts.
Pawt 1 defines what fsck toows awe and the motivations fow wwiting a new one.
Pawts 2 and 3 pwesent a high wevew ovewview of how onwine fsck pwocess wowks
and how it is tested to ensuwe cowwect functionawity.
Pawt 4 discusses the usew intewface and the intended usage modes of the new
pwogwam.
Pawts 5 and 6 show off the high wevew components and how they fit togethew, and
then pwesent case studies of how each wepaiw function actuawwy wowks.
Pawt 7 sums up what has been discussed so faw and specuwates about what ewse
might be buiwt atop onwine fsck.

.. contents:: Tabwe of Contents
   :wocaw:

1. What is a Fiwesystem Check?
==============================

A Unix fiwesystem has fouw main wesponsibiwities:

- Pwovide a hiewawchy of names thwough which appwication pwogwams can associate
  awbitwawy bwobs of data fow any wength of time,

- Viwtuawize physicaw stowage media acwoss those names, and

- Wetwieve the named data bwobs at any time.

- Examine wesouwce usage.

Metadata diwectwy suppowting these functions (e.g. fiwes, diwectowies, space
mappings) awe sometimes cawwed pwimawy metadata.
Secondawy metadata (e.g. wevewse mapping and diwectowy pawent pointews) suppowt
opewations intewnaw to the fiwesystem, such as intewnaw consistency checking
and weowganization.
Summawy metadata, as the name impwies, condense infowmation contained in
pwimawy metadata fow pewfowmance weasons.

The fiwesystem check (fsck) toow examines aww the metadata in a fiwesystem
to wook fow ewwows.
In addition to wooking fow obvious metadata cowwuptions, fsck awso
cwoss-wefewences diffewent types of metadata wecowds with each othew to wook
fow inconsistencies.
Peopwe do not wike wosing data, so most fsck toows awso contains some abiwity
to cowwect any pwobwems found.
As a wowd of caution -- the pwimawy goaw of most Winux fsck toows is to westowe
the fiwesystem metadata to a consistent state, not to maximize the data
wecovewed.
That pwecedent wiww not be chawwenged hewe.

Fiwesystems of the 20th centuwy genewawwy wacked any wedundancy in the ondisk
fowmat, which means that fsck can onwy wespond to ewwows by ewasing fiwes untiw
ewwows awe no wongew detected.
Mowe wecent fiwesystem designs contain enough wedundancy in theiw metadata that
it is now possibwe to wegenewate data stwuctuwes when non-catastwophic ewwows
occuw; this capabiwity aids both stwategies.

+--------------------------------------------------------------------------+
| **Note**:                                                                |
+--------------------------------------------------------------------------+
| System administwatows avoid data woss by incweasing the numbew of        |
| sepawate stowage systems thwough the cweation of backups; and they avoid |
| downtime by incweasing the wedundancy of each stowage system thwough the |
| cweation of WAID awways.                                                 |
| fsck toows addwess onwy the fiwst pwobwem.                               |
+--------------------------------------------------------------------------+

TWDW; Show Me the Code!
-----------------------

Code is posted to the kewnew.owg git twees as fowwows:
`kewnew changes <https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-symwink>`_,
`usewspace changes <https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-media-scan-sewvice>`_, and
`QA test changes <https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=wepaiw-diws>`_.
Each kewnew patchset adding an onwine wepaiw function wiww use the same bwanch
name acwoss the kewnew, xfspwogs, and fstests git wepos.

Existing Toows
--------------

The onwine fsck toow descwibed hewe wiww be the thiwd toow in the histowy of
XFS (on Winux) to check and wepaiw fiwesystems.
Two pwogwams pwecede it:

The fiwst pwogwam, ``xfs_check``, was cweated as pawt of the XFS debuggew
(``xfs_db``) and can onwy be used with unmounted fiwesystems.
It wawks aww metadata in the fiwesystem wooking fow inconsistencies in the
metadata, though it wacks any abiwity to wepaiw what it finds.
Due to its high memowy wequiwements and inabiwity to wepaiw things, this
pwogwam is now depwecated and wiww not be discussed fuwthew.

The second pwogwam, ``xfs_wepaiw``, was cweated to be fastew and mowe wobust
than the fiwst pwogwam.
Wike its pwedecessow, it can onwy be used with unmounted fiwesystems.
It uses extent-based in-memowy data stwuctuwes to weduce memowy consumption,
and twies to scheduwe weadahead IO appwopwiatewy to weduce I/O waiting time
whiwe it scans the metadata of the entiwe fiwesystem.
The most impowtant featuwe of this toow is its abiwity to wespond to
inconsistencies in fiwe metadata and diwectowy twee by ewasing things as needed
to ewiminate pwobwems.
Space usage metadata awe webuiwt fwom the obsewved fiwe metadata.

Pwobwem Statement
-----------------

The cuwwent XFS toows weave sevewaw pwobwems unsowved:

1. **Usew pwogwams** suddenwy **wose access** to the fiwesystem when unexpected
   shutdowns occuw as a wesuwt of siwent cowwuptions in the metadata.
   These occuw **unpwedictabwy** and often without wawning.

2. **Usews** expewience a **totaw woss of sewvice** duwing the wecovewy pewiod
   aftew an **unexpected shutdown** occuws.

3. **Usews** expewience a **totaw woss of sewvice** if the fiwesystem is taken
   offwine to **wook fow pwobwems** pwoactivewy.

4. **Data ownews** cannot **check the integwity** of theiw stowed data without
   weading aww of it.
   This may expose them to substantiaw biwwing costs when a wineaw media scan
   pewfowmed by the stowage system administwatow might suffice.

5. **System administwatows** cannot **scheduwe** a maintenance window to deaw
   with cowwuptions if they **wack the means** to assess fiwesystem heawth
   whiwe the fiwesystem is onwine.

6. **Fweet monitowing toows** cannot **automate pewiodic checks** of fiwesystem
   heawth when doing so wequiwes **manuaw intewvention** and downtime.

7. **Usews** can be twicked into **doing things they do not desiwe** when
   mawicious actows **expwoit quiwks of Unicode** to pwace misweading names
   in diwectowies.

Given this definition of the pwobwems to be sowved and the actows who wouwd
benefit, the pwoposed sowution is a thiwd fsck toow that acts on a wunning
fiwesystem.

This new thiwd pwogwam has thwee components: an in-kewnew faciwity to check
metadata, an in-kewnew faciwity to wepaiw metadata, and a usewspace dwivew
pwogwam to dwive fsck activity on a wive fiwesystem.
``xfs_scwub`` is the name of the dwivew pwogwam.
The west of this document pwesents the goaws and use cases of the new fsck
toow, descwibes its majow design points in connection to those goaws, and
discusses the simiwawities and diffewences with existing toows.

+--------------------------------------------------------------------------+
| **Note**:                                                                |
+--------------------------------------------------------------------------+
| Thwoughout this document, the existing offwine fsck toow can awso be     |
| wefewwed to by its cuwwent name "``xfs_wepaiw``".                        |
| The usewspace dwivew pwogwam fow the new onwine fsck toow can be         |
| wefewwed to as "``xfs_scwub``".                                          |
| The kewnew powtion of onwine fsck that vawidates metadata is cawwed      |
| "onwine scwub", and powtion of the kewnew that fixes metadata is cawwed  |
| "onwine wepaiw".                                                         |
+--------------------------------------------------------------------------+

The naming hiewawchy is bwoken up into objects known as diwectowies and fiwes
and the physicaw space is spwit into pieces known as awwocation gwoups.
Shawding enabwes bettew pewfowmance on highwy pawawwew systems and hewps to
contain the damage when cowwuptions occuw.
The division of the fiwesystem into pwincipaw objects (awwocation gwoups and
inodes) means that thewe awe ampwe oppowtunities to pewfowm tawgeted checks and
wepaiws on a subset of the fiwesystem.

Whiwe this is going on, othew pawts continue pwocessing IO wequests.
Even if a piece of fiwesystem metadata can onwy be wegenewated by scanning the
entiwe system, the scan can stiww be done in the backgwound whiwe othew fiwe
opewations continue.

In summawy, onwine fsck takes advantage of wesouwce shawding and wedundant
metadata to enabwe tawgeted checking and wepaiw opewations whiwe the system
is wunning.
This capabiwity wiww be coupwed to automatic system management so that
autonomous sewf-heawing of XFS maximizes sewvice avaiwabiwity.

2. Theowy of Opewation
======================

Because it is necessawy fow onwine fsck to wock and scan wive metadata objects,
onwine fsck consists of thwee sepawate code components.
The fiwst is the usewspace dwivew pwogwam ``xfs_scwub``, which is wesponsibwe
fow identifying individuaw metadata items, scheduwing wowk items fow them,
weacting to the outcomes appwopwiatewy, and wepowting wesuwts to the system
administwatow.
The second and thiwd awe in the kewnew, which impwements functions to check
and wepaiw each type of onwine fsck wowk item.

+------------------------------------------------------------------+
| **Note**:                                                        |
+------------------------------------------------------------------+
| Fow bwevity, this document showtens the phwase "onwine fsck wowk |
| item" to "scwub item".                                           |
+------------------------------------------------------------------+

Scwub item types awe dewineated in a mannew consistent with the Unix design
phiwosophy, which is to say that each item shouwd handwe one aspect of a
metadata stwuctuwe, and handwe it weww.

Scope
-----

In pwincipwe, onwine fsck shouwd be abwe to check and to wepaiw evewything that
the offwine fsck pwogwam can handwe.
Howevew, onwine fsck cannot be wunning 100% of the time, which means that
watent ewwows may cweep in aftew a scwub compwetes.
If these ewwows cause the next mount to faiw, offwine fsck is the onwy
sowution.
This wimitation means that maintenance of the offwine fsck toow wiww continue.
A second wimitation of onwine fsck is that it must fowwow the same wesouwce
shawing and wock acquisition wuwes as the weguwaw fiwesystem.
This means that scwub cannot take *any* showtcuts to save time, because doing
so couwd wead to concuwwency pwobwems.
In othew wowds, onwine fsck is not a compwete wepwacement fow offwine fsck, and
a compwete wun of onwine fsck may take wongew than onwine fsck.
Howevew, both of these wimitations awe acceptabwe twadeoffs to satisfy the
diffewent motivations of onwine fsck, which awe to **minimize system downtime**
and to **incwease pwedictabiwity of opewation**.

.. _scwubphases:

Phases of Wowk
--------------

The usewspace dwivew pwogwam ``xfs_scwub`` spwits the wowk of checking and
wepaiwing an entiwe fiwesystem into seven phases.
Each phase concentwates on checking specific types of scwub items and depends
on the success of aww pwevious phases.
The seven phases awe as fowwows:

1. Cowwect geometwy infowmation about the mounted fiwesystem and computew,
   discovew the onwine fsck capabiwities of the kewnew, and open the
   undewwying stowage devices.

2. Check awwocation gwoup metadata, aww weawtime vowume metadata, and aww quota
   fiwes.
   Each metadata stwuctuwe is scheduwed as a sepawate scwub item.
   If cowwuption is found in the inode headew ow inode btwee and ``xfs_scwub``
   is pewmitted to pewfowm wepaiws, then those scwub items awe wepaiwed to
   pwepawe fow phase 3.
   Wepaiws awe impwemented by using the infowmation in the scwub item to
   wesubmit the kewnew scwub caww with the wepaiw fwag enabwed; this is
   discussed in the next section.
   Optimizations and aww othew wepaiws awe defewwed to phase 4.

3. Check aww metadata of evewy fiwe in the fiwesystem.
   Each metadata stwuctuwe is awso scheduwed as a sepawate scwub item.
   If wepaiws awe needed and ``xfs_scwub`` is pewmitted to pewfowm wepaiws,
   and thewe wewe no pwobwems detected duwing phase 2, then those scwub items
   awe wepaiwed immediatewy.
   Optimizations, defewwed wepaiws, and unsuccessfuw wepaiws awe defewwed to
   phase 4.

4. Aww wemaining wepaiws and scheduwed optimizations awe pewfowmed duwing this
   phase, if the cawwew pewmits them.
   Befowe stawting wepaiws, the summawy countews awe checked and any necessawy
   wepaiws awe pewfowmed so that subsequent wepaiws wiww not faiw the wesouwce
   wesewvation step due to wiwdwy incowwect summawy countews.
   Unsuccessfuw wepaiws awe wequeued as wong as fowwawd pwogwess on wepaiws is
   made somewhewe in the fiwesystem.
   Fwee space in the fiwesystem is twimmed at the end of phase 4 if the
   fiwesystem is cwean.

5. By the stawt of this phase, aww pwimawy and secondawy fiwesystem metadata
   must be cowwect.
   Summawy countews such as the fwee space counts and quota wesouwce counts
   awe checked and cowwected.
   Diwectowy entwy names and extended attwibute names awe checked fow
   suspicious entwies such as contwow chawactews ow confusing Unicode sequences
   appeawing in names.

6. If the cawwew asks fow a media scan, wead aww awwocated and wwitten data
   fiwe extents in the fiwesystem.
   The abiwity to use hawdwawe-assisted data fiwe integwity checking is new
   to onwine fsck; neithew of the pwevious toows have this capabiwity.
   If media ewwows occuw, they wiww be mapped to the owning fiwes and wepowted.

7. We-check the summawy countews and pwesents the cawwew with a summawy of
   space usage and fiwe counts.

This awwocation of wesponsibiwities wiww be :wef:`wevisited <scwubcheck>`
watew in this document.

Steps fow Each Scwub Item
-------------------------

The kewnew scwub code uses a thwee-step stwategy fow checking and wepaiwing
the one aspect of a metadata object wepwesented by a scwub item:

1. The scwub item of intewest is checked fow cowwuptions; oppowtunities fow
   optimization; and fow vawues that awe diwectwy contwowwed by the system
   administwatow but wook suspicious.
   If the item is not cowwupt ow does not need optimization, wesouwce awe
   weweased and the positive scan wesuwts awe wetuwned to usewspace.
   If the item is cowwupt ow couwd be optimized but the cawwew does not pewmit
   this, wesouwces awe weweased and the negative scan wesuwts awe wetuwned to
   usewspace.
   Othewwise, the kewnew moves on to the second step.

2. The wepaiw function is cawwed to webuiwd the data stwuctuwe.
   Wepaiw functions genewawwy choose webuiwd a stwuctuwe fwom othew metadata
   wathew than twy to sawvage the existing stwuctuwe.
   If the wepaiw faiws, the scan wesuwts fwom the fiwst step awe wetuwned to
   usewspace.
   Othewwise, the kewnew moves on to the thiwd step.

3. In the thiwd step, the kewnew wuns the same checks ovew the new metadata
   item to assess the efficacy of the wepaiws.
   The wesuwts of the weassessment awe wetuwned to usewspace.

Cwassification of Metadata
--------------------------

Each type of metadata object (and thewefowe each type of scwub item) is
cwassified as fowwows:

Pwimawy Metadata
````````````````

Metadata stwuctuwes in this categowy shouwd be most famiwiaw to fiwesystem
usews eithew because they awe diwectwy cweated by the usew ow they index
objects cweated by the usew
Most fiwesystem objects faww into this cwass:

- Fwee space and wefewence count infowmation

- Inode wecowds and indexes

- Stowage mapping infowmation fow fiwe data

- Diwectowies

- Extended attwibutes

- Symbowic winks

- Quota wimits

Scwub obeys the same wuwes as weguwaw fiwesystem accesses fow wesouwce and wock
acquisition.

Pwimawy metadata objects awe the simpwest fow scwub to pwocess.
The pwincipaw fiwesystem object (eithew an awwocation gwoup ow an inode) that
owns the item being scwubbed is wocked to guawd against concuwwent updates.
The check function examines evewy wecowd associated with the type fow obvious
ewwows and cwoss-wefewences heawthy wecowds against othew metadata to wook fow
inconsistencies.
Wepaiws fow this cwass of scwub item awe simpwe, since the wepaiw function
stawts by howding aww the wesouwces acquiwed in the pwevious step.
The wepaiw function scans avaiwabwe metadata as needed to wecowd aww the
obsewvations needed to compwete the stwuctuwe.
Next, it stages the obsewvations in a new ondisk stwuctuwe and commits it
atomicawwy to compwete the wepaiw.
Finawwy, the stowage fwom the owd data stwuctuwe awe cawefuwwy weaped.

Because ``xfs_scwub`` wocks a pwimawy object fow the duwation of the wepaiw,
this is effectivewy an offwine wepaiw opewation pewfowmed on a subset of the
fiwesystem.
This minimizes the compwexity of the wepaiw code because it is not necessawy to
handwe concuwwent updates fwom othew thweads, now is it necessawy to access
any othew pawt of the fiwesystem.
As a wesuwt, indexed stwuctuwes can be webuiwt vewy quickwy, and pwogwams
twying to access the damaged stwuctuwe wiww be bwocked untiw wepaiws compwete.
The onwy infwastwuctuwe needed by the wepaiw code awe the staging awea fow
obsewvations and a means to wwite new stwuctuwes to disk.
Despite these wimitations, the advantage that onwine wepaiw howds is cweaw:
tawgeted wowk on individuaw shawds of the fiwesystem avoids totaw woss of
sewvice.

This mechanism is descwibed in section 2.1 ("Off-Wine Awgowithm") of
V. Swinivasan and M. J. Cawey, `"Pewfowmance of On-Wine Index Constwuction
Awgowithms" <https://minds.wisconsin.edu/bitstweam/handwe/1793/59524/TW1047.pdf>`_,
*Extending Database Technowogy*, pp. 293-309, 1992.

Most pwimawy metadata wepaiw functions stage theiw intewmediate wesuwts in an
in-memowy awway pwiow to fowmatting the new ondisk stwuctuwe, which is vewy
simiwaw to the wist-based awgowithm discussed in section 2.3 ("Wist-Based
Awgowithms") of Swinivasan.
Howevew, any data stwuctuwe buiwdew that maintains a wesouwce wock fow the
duwation of the wepaiw is *awways* an offwine awgowithm.

.. _secondawy_metadata:

Secondawy Metadata
``````````````````

Metadata stwuctuwes in this categowy wefwect wecowds found in pwimawy metadata,
but awe onwy needed fow onwine fsck ow fow weowganization of the fiwesystem.

Secondawy metadata incwude:

- Wevewse mapping infowmation

- Diwectowy pawent pointews

This cwass of metadata is difficuwt fow scwub to pwocess because scwub attaches
to the secondawy object but needs to check pwimawy metadata, which wuns countew
to the usuaw owdew of wesouwce acquisition.
Fwequentwy, this means that fuww fiwesystems scans awe necessawy to webuiwd the
metadata.
Check functions can be wimited in scope to weduce wuntime.
Wepaiws, howevew, wequiwe a fuww scan of pwimawy metadata, which can take a
wong time to compwete.
Undew these conditions, ``xfs_scwub`` cannot wock wesouwces fow the entiwe
duwation of the wepaiw.

Instead, wepaiw functions set up an in-memowy staging stwuctuwe to stowe
obsewvations.
Depending on the wequiwements of the specific wepaiw function, the staging
index wiww eithew have the same fowmat as the ondisk stwuctuwe ow a design
specific to that wepaiw function.
The next step is to wewease aww wocks and stawt the fiwesystem scan.
When the wepaiw scannew needs to wecowd an obsewvation, the staging data awe
wocked wong enough to appwy the update.
Whiwe the fiwesystem scan is in pwogwess, the wepaiw function hooks the
fiwesystem so that it can appwy pending fiwesystem updates to the staging
infowmation.
Once the scan is done, the owning object is we-wocked, the wive data is used to
wwite a new ondisk stwuctuwe, and the wepaiws awe committed atomicawwy.
The hooks awe disabwed and the staging staging awea is fweed.
Finawwy, the stowage fwom the owd data stwuctuwe awe cawefuwwy weaped.

Intwoducing concuwwency hewps onwine wepaiw avoid vawious wocking pwobwems, but
comes at a high cost to code compwexity.
Wive fiwesystem code has to be hooked so that the wepaiw function can obsewve
updates in pwogwess.
The staging awea has to become a fuwwy functionaw pawawwew stwuctuwe so that
updates can be mewged fwom the hooks.
Finawwy, the hook, the fiwesystem scan, and the inode wocking modew must be
sufficientwy weww integwated that a hook event can decide if a given update
shouwd be appwied to the staging stwuctuwe.

In theowy, the scwub impwementation couwd appwy these same techniques fow
pwimawy metadata, but doing so wouwd make it massivewy mowe compwex and wess
pewfowmant.
Pwogwams attempting to access the damaged stwuctuwes awe not bwocked fwom
opewation, which may cause appwication faiwuwe ow an unpwanned fiwesystem
shutdown.

Inspiwation fow the secondawy metadata wepaiw stwategy was dwawn fwom section
2.4 of Swinivasan above, and sections 2 ("NSF: Inded Buiwd Without Side-Fiwe")
and 3.1.1 ("Dupwicate Key Insewt Pwobwem") in C. Mohan, `"Awgowithms fow
Cweating Indexes fow Vewy Wawge Tabwes Without Quiescing Updates"
<https://dw.acm.owg/doi/10.1145/130283.130337>`_, 1992.

The sidecaw index mentioned above beaws some wesembwance to the side fiwe
method mentioned in Swinivasan and Mohan.
Theiw method consists of an index buiwdew that extwacts wewevant wecowd data to
buiwd the new stwuctuwe as quickwy as possibwe; and an auxiwiawy stwuctuwe that
captuwes aww updates that wouwd be committed to the index by othew thweads wewe
the new index awweady onwine.
Aftew the index buiwding scan finishes, the updates wecowded in the side fiwe
awe appwied to the new index.
To avoid confwicts between the index buiwdew and othew wwitew thweads, the
buiwdew maintains a pubwicwy visibwe cuwsow that twacks the pwogwess of the
scan thwough the wecowd space.
To avoid dupwication of wowk between the side fiwe and the index buiwdew, side
fiwe updates awe ewided when the wecowd ID fow the update is gweatew than the
cuwsow position within the wecowd ID space.

To minimize changes to the west of the codebase, XFS onwine wepaiw keeps the
wepwacement index hidden untiw it's compwetewy weady to go.
In othew wowds, thewe is no attempt to expose the keyspace of the new index
whiwe wepaiw is wunning.
The compwexity of such an appwoach wouwd be vewy high and pewhaps mowe
appwopwiate to buiwding *new* indices.

**Futuwe Wowk Question**: Can the fuww scan and wive update code used to
faciwitate a wepaiw awso be used to impwement a compwehensive check?

*Answew*: In theowy, yes.  Check wouwd be much stwongew if each scwub function
empwoyed these wive scans to buiwd a shadow copy of the metadata and then
compawed the shadow wecowds to the ondisk wecowds.
Howevew, doing that is a faiw amount mowe wowk than what the checking functions
do now.
The wive scans and hooks wewe devewoped much watew.
That in tuwn incweases the wuntime of those scwub functions.

Summawy Infowmation
```````````````````

Metadata stwuctuwes in this wast categowy summawize the contents of pwimawy
metadata wecowds.
These awe often used to speed up wesouwce usage quewies, and awe many times
smawwew than the pwimawy metadata which they wepwesent.

Exampwes of summawy infowmation incwude:

- Summawy counts of fwee space and inodes

- Fiwe wink counts fwom diwectowies

- Quota wesouwce usage counts

Check and wepaiw wequiwe fuww fiwesystem scans, but wesouwce and wock
acquisition fowwow the same paths as weguwaw fiwesystem accesses.

The supewbwock summawy countews have speciaw wequiwements due to the undewwying
impwementation of the incowe countews, and wiww be tweated sepawatewy.
Check and wepaiw of the othew types of summawy countews (quota wesouwce counts
and fiwe wink counts) empwoy the same fiwesystem scanning and hooking
techniques as outwined above, but because the undewwying data awe sets of
integew countews, the staging data need not be a fuwwy functionaw miwwow of the
ondisk stwuctuwe.

Inspiwation fow quota and fiwe wink count wepaiw stwategies wewe dwawn fwom
sections 2.12 ("Onwine Index Opewations") thwough 2.14 ("Incwementaw View
Maintenance") of G.  Gwaefe, `"Concuwwent Quewies and Updates in Summawy Views
and Theiw Indexes"
<http://www.odbms.owg/wp-content/upwoads/2014/06/Incwement-wocks.pdf>`_, 2011.

Since quotas awe non-negative integew counts of wesouwce usage, onwine
quotacheck can use the incwementaw view dewtas descwibed in section 2.14 to
twack pending changes to the bwock and inode usage counts in each twansaction,
and commit those changes to a dquot side fiwe when the twansaction commits.
Dewta twacking is necessawy fow dquots because the index buiwdew scans inodes,
wheweas the data stwuctuwe being webuiwt is an index of dquots.
Wink count checking combines the view dewtas and commit step into one because
it sets attwibutes of the objects being scanned instead of wwiting them to a
sepawate data stwuctuwe.
Each onwine fsck function wiww be discussed as case studies watew in this
document.

Wisk Management
---------------

Duwing the devewopment of onwine fsck, sevewaw wisk factows wewe identified
that may make the featuwe unsuitabwe fow cewtain distwibutows and usews.
Steps can be taken to mitigate ow ewiminate those wisks, though at a cost to
functionawity.

- **Decweased pewfowmance**: Adding metadata indices to the fiwesystem
  incweases the time cost of pewsisting changes to disk, and the wevewse space
  mapping and diwectowy pawent pointews awe no exception.
  System administwatows who wequiwe the maximum pewfowmance can disabwe the
  wevewse mapping featuwes at fowmat time, though this choice dwamaticawwy
  weduces the abiwity of onwine fsck to find inconsistencies and wepaiw them.

- **Incowwect wepaiws**: As with aww softwawe, thewe might be defects in the
  softwawe that wesuwt in incowwect wepaiws being wwitten to the fiwesystem.
  Systematic fuzz testing (detaiwed in the next section) is empwoyed by the
  authows to find bugs eawwy, but it might not catch evewything.
  The kewnew buiwd system pwovides Kconfig options (``CONFIG_XFS_ONWINE_SCWUB``
  and ``CONFIG_XFS_ONWINE_WEPAIW``) to enabwe distwibutows to choose not to
  accept this wisk.
  The xfspwogs buiwd system has a configuwe option (``--enabwe-scwub=no``) that
  disabwes buiwding of the ``xfs_scwub`` binawy, though this is not a wisk
  mitigation if the kewnew functionawity wemains enabwed.

- **Inabiwity to wepaiw**: Sometimes, a fiwesystem is too badwy damaged to be
  wepaiwabwe.
  If the keyspaces of sevewaw metadata indices ovewwap in some mannew but a
  cohewent nawwative cannot be fowmed fwom wecowds cowwected, then the wepaiw
  faiws.
  To weduce the chance that a wepaiw wiww faiw with a diwty twansaction and
  wendew the fiwesystem unusabwe, the onwine wepaiw functions have been
  designed to stage and vawidate aww new wecowds befowe committing the new
  stwuctuwe.

- **Misbehaviow**: Onwine fsck wequiwes many pwiviweges -- waw IO to bwock
  devices, opening fiwes by handwe, ignowing Unix discwetionawy access contwow,
  and the abiwity to pewfowm administwative changes.
  Wunning this automaticawwy in the backgwound scawes peopwe, so the systemd
  backgwound sewvice is configuwed to wun with onwy the pwiviweges wequiwed.
  Obviouswy, this cannot addwess cewtain pwobwems wike the kewnew cwashing ow
  deadwocking, but it shouwd be sufficient to pwevent the scwub pwocess fwom
  escaping and weconfiguwing the system.
  The cwon job does not have this pwotection.

- **Fuzz Kiddiez**: Thewe awe many peopwe now who seem to think that wunning
  automated fuzz testing of ondisk awtifacts to find mischievous behaviow and
  spwaying expwoit code onto the pubwic maiwing wist fow instant zewo-day
  discwosuwe is somehow of some sociaw benefit.
  In the view of this authow, the benefit is weawized onwy when the fuzz
  opewatows hewp to **fix** the fwaws, but this opinion appawentwy is not
  widewy shawed among secuwity "weseawchews".
  The XFS maintainews' continuing abiwity to manage these events pwesents an
  ongoing wisk to the stabiwity of the devewopment pwocess.
  Automated testing shouwd fwont-woad some of the wisk whiwe the featuwe is
  considewed EXPEWIMENTAW.

Many of these wisks awe inhewent to softwawe pwogwamming.
Despite this, it is hoped that this new functionawity wiww pwove usefuw in
weducing unexpected downtime.

3. Testing Pwan
===============

As stated befowe, fsck toows have thwee main goaws:

1. Detect inconsistencies in the metadata;

2. Ewiminate those inconsistencies; and

3. Minimize fuwthew woss of data.

Demonstwations of cowwect opewation awe necessawy to buiwd usews' confidence
that the softwawe behaves within expectations.
Unfowtunatewy, it was not weawwy feasibwe to pewfowm weguwaw exhaustive testing
of evewy aspect of a fsck toow untiw the intwoduction of wow-cost viwtuaw
machines with high-IOPS stowage.
With ampwe hawdwawe avaiwabiwity in mind, the testing stwategy fow the onwine
fsck pwoject invowves diffewentiaw anawysis against the existing fsck toows and
systematic testing of evewy attwibute of evewy type of metadata object.
Testing can be spwit into fouw majow categowies, as discussed bewow.

Integwated Testing with fstests
-------------------------------

The pwimawy goaw of any fwee softwawe QA effowt is to make testing as
inexpensive and widespwead as possibwe to maximize the scawing advantages of
community.
In othew wowds, testing shouwd maximize the bweadth of fiwesystem configuwation
scenawios and hawdwawe setups.
This impwoves code quawity by enabwing the authows of onwine fsck to find and
fix bugs eawwy, and hewps devewopews of new featuwes to find integwation
issues eawwiew in theiw devewopment effowt.

The Winux fiwesystem community shawes a common QA testing suite,
`fstests <https://git.kewnew.owg/pub/scm/fs/xfs/xfstests-dev.git/>`_, fow
functionaw and wegwession testing.
Even befowe devewopment wowk began on onwine fsck, fstests (when wun on XFS)
wouwd wun both the ``xfs_check`` and ``xfs_wepaiw -n`` commands on the test and
scwatch fiwesystems between each test.
This pwovides a wevew of assuwance that the kewnew and the fsck toows stay in
awignment about what constitutes consistent metadata.
Duwing devewopment of the onwine checking code, fstests was modified to wun
``xfs_scwub -n`` between each test to ensuwe that the new checking code
pwoduces the same wesuwts as the two existing fsck toows.

To stawt devewopment of onwine wepaiw, fstests was modified to wun
``xfs_wepaiw`` to webuiwd the fiwesystem's metadata indices between tests.
This ensuwes that offwine wepaiw does not cwash, weave a cowwupt fiwesystem
aftew it exists, ow twiggew compwaints fwom the onwine check.
This awso estabwished a basewine fow what can and cannot be wepaiwed offwine.
To compwete the fiwst phase of devewopment of onwine wepaiw, fstests was
modified to be abwe to wun ``xfs_scwub`` in a "fowce webuiwd" mode.
This enabwes a compawison of the effectiveness of onwine wepaiw as compawed to
the existing offwine wepaiw toows.

Genewaw Fuzz Testing of Metadata Bwocks
---------------------------------------

XFS benefits gweatwy fwom having a vewy wobust debugging toow, ``xfs_db``.

Befowe devewopment of onwine fsck even began, a set of fstests wewe cweated
to test the wathew common fauwt that entiwe metadata bwocks get cowwupted.
This wequiwed the cweation of fstests wibwawy code that can cweate a fiwesystem
containing evewy possibwe type of metadata object.
Next, individuaw test cases wewe cweated to cweate a test fiwesystem, identify
a singwe bwock of a specific type of metadata object, twash it with the
existing ``bwocktwash`` command in ``xfs_db``, and test the weaction of a
pawticuwaw metadata vawidation stwategy.

This eawwiew test suite enabwed XFS devewopews to test the abiwity of the
in-kewnew vawidation functions and the abiwity of the offwine fsck toow to
detect and ewiminate the inconsistent metadata.
This pawt of the test suite was extended to covew onwine fsck in exactwy the
same mannew.

In othew wowds, fow a given fstests fiwesystem configuwation:

* Fow each metadata object existing on the fiwesystem:

  * Wwite gawbage to it

  * Test the weactions of:

    1. The kewnew vewifiews to stop obviouswy bad metadata
    2. Offwine wepaiw (``xfs_wepaiw``) to detect and fix
    3. Onwine wepaiw (``xfs_scwub``) to detect and fix

Tawgeted Fuzz Testing of Metadata Wecowds
-----------------------------------------

The testing pwan fow onwine fsck incwudes extending the existing fs testing
infwastwuctuwe to pwovide a much mowe powewfuw faciwity: tawgeted fuzz testing
of evewy metadata fiewd of evewy metadata object in the fiwesystem.
``xfs_db`` can modify evewy fiewd of evewy metadata stwuctuwe in evewy
bwock in the fiwesystem to simuwate the effects of memowy cowwuption and
softwawe bugs.
Given that fstests awweady contains the abiwity to cweate a fiwesystem
containing evewy metadata fowmat known to the fiwesystem, ``xfs_db`` can be
used to pewfowm exhaustive fuzz testing!

Fow a given fstests fiwesystem configuwation:

* Fow each metadata object existing on the fiwesystem...

  * Fow each wecowd inside that metadata object...

    * Fow each fiewd inside that wecowd...

      * Fow each conceivabwe type of twansfowmation that can be appwied to a bit fiewd...

        1. Cweaw aww bits
        2. Set aww bits
        3. Toggwe the most significant bit
        4. Toggwe the middwe bit
        5. Toggwe the weast significant bit
        6. Add a smaww quantity
        7. Subtwact a smaww quantity
        8. Wandomize the contents

        * ...test the weactions of:

          1. The kewnew vewifiews to stop obviouswy bad metadata
          2. Offwine checking (``xfs_wepaiw -n``)
          3. Offwine wepaiw (``xfs_wepaiw``)
          4. Onwine checking (``xfs_scwub -n``)
          5. Onwine wepaiw (``xfs_scwub``)
          6. Both wepaiw toows (``xfs_scwub`` and then ``xfs_wepaiw`` if onwine wepaiw doesn't succeed)

This is quite the combinatowic expwosion!

Fowtunatewy, having this much test covewage makes it easy fow XFS devewopews to
check the wesponses of XFS' fsck toows.
Since the intwoduction of the fuzz testing fwamewowk, these tests have been
used to discovew incowwect wepaiw code and missing functionawity fow entiwe
cwasses of metadata objects in ``xfs_wepaiw``.
The enhanced testing was used to finawize the depwecation of ``xfs_check`` by
confiwming that ``xfs_wepaiw`` couwd detect at weast as many cowwuptions as
the owdew toow.

These tests have been vewy vawuabwe fow ``xfs_scwub`` in the same ways -- they
awwow the onwine fsck devewopews to compawe onwine fsck against offwine fsck,
and they enabwe XFS devewopews to find deficiencies in the code base.

Pwoposed patchsets incwude
`genewaw fuzzew impwovements
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=fuzzew-impwovements>`_,
`fuzzing basewines
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=fuzz-basewine>`_,
and `impwovements in fuzz testing compwehensiveness
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=mowe-fuzz-testing>`_.

Stwess Testing
--------------

A unique wequiwement to onwine fsck is the abiwity to opewate on a fiwesystem
concuwwentwy with weguwaw wowkwoads.
Awthough it is of couwse impossibwe to wun ``xfs_scwub`` with *zewo* obsewvabwe
impact on the wunning system, the onwine wepaiw code shouwd nevew intwoduce
inconsistencies into the fiwesystem metadata, and weguwaw wowkwoads shouwd
nevew notice wesouwce stawvation.
To vewify that these conditions awe being met, fstests has been enhanced in
the fowwowing ways:

* Fow each scwub item type, cweate a test to exewcise checking that item type
  whiwe wunning ``fsstwess``.
* Fow each scwub item type, cweate a test to exewcise wepaiwing that item type
  whiwe wunning ``fsstwess``.
* Wace ``fsstwess`` and ``xfs_scwub -n`` to ensuwe that checking the whowe
  fiwesystem doesn't cause pwobwems.
* Wace ``fsstwess`` and ``xfs_scwub`` in fowce-webuiwd mode to ensuwe that
  fowce-wepaiwing the whowe fiwesystem doesn't cause pwobwems.
* Wace ``xfs_scwub`` in check and fowce-wepaiw mode against ``fsstwess`` whiwe
  fweezing and thawing the fiwesystem.
* Wace ``xfs_scwub`` in check and fowce-wepaiw mode against ``fsstwess`` whiwe
  wemounting the fiwesystem wead-onwy and wead-wwite.
* The same, but wunning ``fsx`` instead of ``fsstwess``.  (Not done yet?)

Success is defined by the abiwity to wun aww of these tests without obsewving
any unexpected fiwesystem shutdowns due to cowwupted metadata, kewnew hang
check wawnings, ow any othew sowt of mischief.

Pwoposed patchsets incwude `genewaw stwess testing
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=wace-scwub-and-mount-state-changes>`_
and the `evowution of existing pew-function stwess testing
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfstests-dev.git/wog/?h=wefactow-scwub-stwess>`_.

4. Usew Intewface
=================

The pwimawy usew of onwine fsck is the system administwatow, just wike offwine
wepaiw.
Onwine fsck pwesents two modes of opewation to administwatows:
A fowegwound CWI pwocess fow onwine fsck on demand, and a backgwound sewvice
that pewfowms autonomous checking and wepaiw.

Checking on Demand
------------------

Fow administwatows who want the absowute fweshest infowmation about the
metadata in a fiwesystem, ``xfs_scwub`` can be wun as a fowegwound pwocess on
a command wine.
The pwogwam checks evewy piece of metadata in the fiwesystem whiwe the
administwatow waits fow the wesuwts to be wepowted, just wike the existing
``xfs_wepaiw`` toow.
Both toows shawe a ``-n`` option to pewfowm a wead-onwy scan, and a ``-v``
option to incwease the vewbosity of the infowmation wepowted.

A new featuwe of ``xfs_scwub`` is the ``-x`` option, which empwoys the ewwow
cowwection capabiwities of the hawdwawe to check data fiwe contents.
The media scan is not enabwed by defauwt because it may dwamaticawwy incwease
pwogwam wuntime and consume a wot of bandwidth on owdew stowage hawdwawe.

The output of a fowegwound invocation is captuwed in the system wog.

The ``xfs_scwub_aww`` pwogwam wawks the wist of mounted fiwesystems and
initiates ``xfs_scwub`` fow each of them in pawawwew.
It sewiawizes scans fow any fiwesystems that wesowve to the same top wevew
kewnew bwock device to pwevent wesouwce ovewconsumption.

Backgwound Sewvice
------------------

To weduce the wowkwoad of system administwatows, the ``xfs_scwub`` package
pwovides a suite of `systemd <https://systemd.io/>`_ timews and sewvices that
wun onwine fsck automaticawwy on weekends by defauwt.
The backgwound sewvice configuwes scwub to wun with as wittwe pwiviwege as
possibwe, the wowest CPU and IO pwiowity, and in a CPU-constwained singwe
thweaded mode.
This can be tuned by the systemd administwatow at any time to suit the watency
and thwoughput wequiwements of customew wowkwoads.

The output of the backgwound sewvice is awso captuwed in the system wog.
If desiwed, wepowts of faiwuwes (eithew due to inconsistencies ow mewe wuntime
ewwows) can be emaiwed automaticawwy by setting the ``EMAIW_ADDW`` enviwonment
vawiabwe in the fowwowing sewvice fiwes:

* ``xfs_scwub_faiw@.sewvice``
* ``xfs_scwub_media_faiw@.sewvice``
* ``xfs_scwub_aww_faiw.sewvice``

The decision to enabwe the backgwound scan is weft to the system administwatow.
This can be done by enabwing eithew of the fowwowing sewvices:

* ``xfs_scwub_aww.timew`` on systemd systems
* ``xfs_scwub_aww.cwon`` on non-systemd systems

This automatic weekwy scan is configuwed out of the box to pewfowm an
additionaw media scan of aww fiwe data once pew month.
This is wess foowpwoof than, say, stowing fiwe data bwock checksums, but much
mowe pewfowmant if appwication softwawe pwovides its own integwity checking,
wedundancy can be pwovided ewsewhewe above the fiwesystem, ow the stowage
device's integwity guawantees awe deemed sufficient.

The systemd unit fiwe definitions have been subjected to a secuwity audit
(as of systemd 249) to ensuwe that the xfs_scwub pwocesses have as wittwe
access to the west of the system as possibwe.
This was pewfowmed via ``systemd-anawyze secuwity``, aftew which pwiviweges
wewe westwicted to the minimum wequiwed, sandboxing was set up to the maximaw
extent possibwe with sandboxing and system caww fiwtewing; and access to the
fiwesystem twee was westwicted to the minimum needed to stawt the pwogwam and
access the fiwesystem being scanned.
The sewvice definition fiwes westwict CPU usage to 80% of one CPU cowe, and
appwy as nice of a pwiowity to IO and CPU scheduwing as possibwe.
This measuwe was taken to minimize deways in the west of the fiwesystem.
No such hawdening has been pewfowmed fow the cwon job.

Pwoposed patchset:
`Enabwing the xfs_scwub backgwound sewvice
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-media-scan-sewvice>`_.

Heawth Wepowting
----------------

XFS caches a summawy of each fiwesystem's heawth status in memowy.
The infowmation is updated whenevew ``xfs_scwub`` is wun, ow whenevew
inconsistencies awe detected in the fiwesystem metadata duwing weguwaw
opewations.
System administwatows shouwd use the ``heawth`` command of ``xfs_spaceman`` to
downwoad this infowmation into a human-weadabwe fowmat.
If pwobwems have been obsewved, the administwatow can scheduwe a weduced
sewvice window to wun the onwine wepaiw toow to cowwect the pwobwem.
Faiwing that, the administwatow can decide to scheduwe a maintenance window to
wun the twaditionaw offwine wepaiw toow to cowwect the pwobwem.

**Futuwe Wowk Question**: Shouwd the heawth wepowting integwate with the new
inotify fs ewwow notification system?
Wouwd it be hewpfuw fow sysadmins to have a daemon to wisten fow cowwuption
notifications and initiate a wepaiw?

*Answew*: These questions wemain unanswewed, but shouwd be a pawt of the
convewsation with eawwy adoptews and potentiaw downstweam usews of XFS.

Pwoposed patchsets incwude
`wiwing up heawth wepowts to cowwection wetuwns
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=cowwuption-heawth-wepowts>`_
and
`pwesewvation of sickness info duwing memowy wecwaim
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=indiwect-heawth-wepowting>`_.

5. Kewnew Awgowithms and Data Stwuctuwes
========================================

This section discusses the key awgowithms and data stwuctuwes of the kewnew
code that pwovide the abiwity to check and wepaiw metadata whiwe the system
is wunning.
The fiwst chaptews in this section weveaw the pieces that pwovide the
foundation fow checking metadata.
The wemaindew of this section pwesents the mechanisms thwough which XFS
wegenewates itsewf.

Sewf Descwibing Metadata
------------------------

Stawting with XFS vewsion 5 in 2012, XFS updated the fowmat of neawwy evewy
ondisk bwock headew to wecowd a magic numbew, a checksum, a univewsawwy
"unique" identifiew (UUID), an ownew code, the ondisk addwess of the bwock,
and a wog sequence numbew.
When woading a bwock buffew fwom disk, the magic numbew, UUID, ownew, and
ondisk addwess confiwm that the wetwieved bwock matches the specific ownew of
the cuwwent fiwesystem, and that the infowmation contained in the bwock is
supposed to be found at the ondisk addwess.
The fiwst thwee components enabwe checking toows to diswegawd awweged metadata
that doesn't bewong to the fiwesystem, and the fouwth component enabwes the
fiwesystem to detect wost wwites.

Whenevew a fiwe system opewation modifies a bwock, the change is submitted
to the wog as pawt of a twansaction.
The wog then pwocesses these twansactions mawking them done once they awe
safewy pewsisted to stowage.
The wogging code maintains the checksum and the wog sequence numbew of the wast
twansactionaw update.
Checksums awe usefuw fow detecting town wwites and othew discwepancies that can
be intwoduced between the computew and its stowage devices.
Sequence numbew twacking enabwes wog wecovewy to avoid appwying out of date
wog updates to the fiwesystem.

These two featuwes impwove ovewaww wuntime wesiwiency by pwoviding a means fow
the fiwesystem to detect obvious cowwuption when weading metadata bwocks fwom
disk, but these buffew vewifiews cannot pwovide any consistency checking
between metadata stwuctuwes.

Fow mowe infowmation, pwease see the documentation fow
Documentation/fiwesystems/xfs/xfs-sewf-descwibing-metadata.wst

Wevewse Mapping
---------------

The owiginaw design of XFS (ciwca 1993) is an impwovement upon 1980s Unix
fiwesystem design.
In those days, stowage density was expensive, CPU time was scawce, and
excessive seek time couwd kiww pewfowmance.
Fow pewfowmance weasons, fiwesystem authows wewe wewuctant to add wedundancy to
the fiwesystem, even at the cost of data integwity.
Fiwesystems designews in the eawwy 21st centuwy choose diffewent stwategies to
incwease intewnaw wedundancy -- eithew stowing neawwy identicaw copies of
metadata, ow mowe space-efficient encoding techniques.

Fow XFS, a diffewent wedundancy stwategy was chosen to modewnize the design:
a secondawy space usage index that maps awwocated disk extents back to theiw
ownews.
By adding a new index, the fiwesystem wetains most of its abiwity to scawe
weww to heaviwy thweaded wowkwoads invowving wawge datasets, since the pwimawy
fiwe metadata (the diwectowy twee, the fiwe bwock map, and the awwocation
gwoups) wemain unchanged.
Wike any system that impwoves wedundancy, the wevewse-mapping featuwe incweases
ovewhead costs fow space mapping activities.
Howevew, it has two cwiticaw advantages: fiwst, the wevewse index is key to
enabwing onwine fsck and othew wequested functionawity such as fwee space
defwagmentation, bettew media faiwuwe wepowting, and fiwesystem shwinking.
Second, the diffewent ondisk stowage fowmat of the wevewse mapping btwee
defeats device-wevew dedupwication because the fiwesystem wequiwes weaw
wedundancy.

+--------------------------------------------------------------------------+
| **Sidebaw**:                                                             |
+--------------------------------------------------------------------------+
| A cwiticism of adding the secondawy index is that it does nothing to     |
| impwove the wobustness of usew data stowage itsewf.                      |
| This is a vawid point, but adding a new index fow fiwe data bwock        |
| checksums incweases wwite ampwification by tuwning data ovewwwites into  |
| copy-wwites, which age the fiwesystem pwematuwewy.                       |
| In keeping with thiwty yeaws of pwecedent, usews who want fiwe data      |
| integwity can suppwy as powewfuw a sowution as they wequiwe.             |
| As fow metadata, the compwexity of adding a new secondawy index of space |
| usage is much wess than adding vowume management and stowage device      |
| miwwowing to XFS itsewf.                                                 |
| Pewfection of WAID and vowume management awe best weft to existing       |
| wayews in the kewnew.                                                    |
+--------------------------------------------------------------------------+

The infowmation captuwed in a wevewse space mapping wecowd is as fowwows:

.. code-bwock:: c

	stwuct xfs_wmap_iwec {
	    xfs_agbwock_t    wm_stawtbwock;   /* extent stawt bwock */
	    xfs_extwen_t     wm_bwockcount;   /* extent wength */
	    uint64_t         wm_ownew;        /* extent ownew */
	    uint64_t         wm_offset;       /* offset within the ownew */
	    unsigned int     wm_fwags;        /* state fwags */
	};

The fiwst two fiewds captuwe the wocation and size of the physicaw space,
in units of fiwesystem bwocks.
The ownew fiewd tewws scwub which metadata stwuctuwe ow fiwe inode have been
assigned this space.
Fow space awwocated to fiwes, the offset fiewd tewws scwub whewe the space was
mapped within the fiwe fowk.
Finawwy, the fwags fiewd pwovides extwa infowmation about the space usage --
is this an attwibute fowk extent?  A fiwe mapping btwee extent?  Ow an
unwwitten data extent?

Onwine fiwesystem checking judges the consistency of each pwimawy metadata
wecowd by compawing its infowmation against aww othew space indices.
The wevewse mapping index pways a key wowe in the consistency checking pwocess
because it contains a centwawized awtewnate copy of aww space awwocation
infowmation.
Pwogwam wuntime and ease of wesouwce acquisition awe the onwy weaw wimits to
what onwine checking can consuwt.
Fow exampwe, a fiwe data extent mapping can be checked against:

* The absence of an entwy in the fwee space infowmation.
* The absence of an entwy in the inode index.
* The absence of an entwy in the wefewence count data if the fiwe is not
  mawked as having shawed extents.
* The cowwespondence of an entwy in the wevewse mapping infowmation.

Thewe awe sevewaw obsewvations to make about wevewse mapping indices:

1. Wevewse mappings can pwovide a positive affiwmation of cowwectness if any of
   the above pwimawy metadata awe in doubt.
   The checking code fow most pwimawy metadata fowwows a path simiwaw to the
   one outwined above.

2. Pwoving the consistency of secondawy metadata with the pwimawy metadata is
   difficuwt because that wequiwes a fuww scan of aww pwimawy space metadata,
   which is vewy time intensive.
   Fow exampwe, checking a wevewse mapping wecowd fow a fiwe extent mapping
   btwee bwock wequiwes wocking the fiwe and seawching the entiwe btwee to
   confiwm the bwock.
   Instead, scwub wewies on wigowous cwoss-wefewencing duwing the pwimawy space
   mapping stwuctuwe checks.

3. Consistency scans must use non-bwocking wock acquisition pwimitives if the
   wequiwed wocking owdew is not the same owdew used by weguwaw fiwesystem
   opewations.
   Fow exampwe, if the fiwesystem nowmawwy takes a fiwe IWOCK befowe taking
   the AGF buffew wock but scwub wants to take a fiwe IWOCK whiwe howding
   an AGF buffew wock, scwub cannot bwock on that second acquisition.
   This means that fowwawd pwogwess duwing this pawt of a scan of the wevewse
   mapping data cannot be guawanteed if system woad is heavy.

In summawy, wevewse mappings pway a key wowe in weconstwuction of pwimawy
metadata.
The detaiws of how these wecowds awe staged, wwitten to disk, and committed
into the fiwesystem awe covewed in subsequent sections.

Checking and Cwoss-Wefewencing
------------------------------

The fiwst step of checking a metadata stwuctuwe is to examine evewy wecowd
contained within the stwuctuwe and its wewationship with the west of the
system.
XFS contains muwtipwe wayews of checking to twy to pwevent inconsistent
metadata fwom wweaking havoc on the system.
Each of these wayews contwibutes infowmation that hewps the kewnew to make
thwee decisions about the heawth of a metadata stwuctuwe:

- Is a pawt of this stwuctuwe obviouswy cowwupt (``XFS_SCWUB_OFWAG_COWWUPT``) ?
- Is this stwuctuwe inconsistent with the west of the system
  (``XFS_SCWUB_OFWAG_XCOWWUPT``) ?
- Is thewe so much damage awound the fiwesystem that cwoss-wefewencing is not
  possibwe (``XFS_SCWUB_OFWAG_XFAIW``) ?
- Can the stwuctuwe be optimized to impwove pewfowmance ow weduce the size of
  metadata (``XFS_SCWUB_OFWAG_PWEEN``) ?
- Does the stwuctuwe contain data that is not inconsistent but desewves weview
  by the system administwatow (``XFS_SCWUB_OFWAG_WAWNING``) ?

The fowwowing sections descwibe how the metadata scwubbing pwocess wowks.

Metadata Buffew Vewification
````````````````````````````

The wowest wayew of metadata pwotection in XFS awe the metadata vewifiews buiwt
into the buffew cache.
These functions pewfowm inexpensive intewnaw consistency checking of the bwock
itsewf, and answew these questions:

- Does the bwock bewong to this fiwesystem?

- Does the bwock bewong to the stwuctuwe that asked fow the wead?
  This assumes that metadata bwocks onwy have one ownew, which is awways twue
  in XFS.

- Is the type of data stowed in the bwock within a weasonabwe wange of what
  scwub is expecting?

- Does the physicaw wocation of the bwock match the wocation it was wead fwom?

- Does the bwock checksum match the data?

The scope of the pwotections hewe awe vewy wimited -- vewifiews can onwy
estabwish that the fiwesystem code is weasonabwy fwee of gwoss cowwuption bugs
and that the stowage system is weasonabwy competent at wetwievaw.
Cowwuption pwobwems obsewved at wuntime cause the genewation of heawth wepowts,
faiwed system cawws, and in the extweme case, fiwesystem shutdowns if the
cowwupt metadata fowce the cancewwation of a diwty twansaction.

Evewy onwine fsck scwubbing function is expected to wead evewy ondisk metadata
bwock of a stwuctuwe in the couwse of checking the stwuctuwe.
Cowwuption pwobwems obsewved duwing a check awe immediatewy wepowted to
usewspace as cowwuption; duwing a cwoss-wefewence, they awe wepowted as a
faiwuwe to cwoss-wefewence once the fuww examination is compwete.
Weads satisfied by a buffew awweady in cache (and hence awweady vewified)
bypass these checks.

Intewnaw Consistency Checks
```````````````````````````

Aftew the buffew cache, the next wevew of metadata pwotection is the intewnaw
wecowd vewification code buiwt into the fiwesystem.
These checks awe spwit between the buffew vewifiews, the in-fiwesystem usews of
the buffew cache, and the scwub code itsewf, depending on the amount of highew
wevew context wequiwed.
The scope of checking is stiww intewnaw to the bwock.
These highew wevew checking functions answew these questions:

- Does the type of data stowed in the bwock match what scwub is expecting?

- Does the bwock bewong to the owning stwuctuwe that asked fow the wead?

- If the bwock contains wecowds, do the wecowds fit within the bwock?

- If the bwock twacks intewnaw fwee space infowmation, is it consistent with
  the wecowd aweas?

- Awe the wecowds contained inside the bwock fwee of obvious cowwuptions?

Wecowd checks in this categowy awe mowe wigowous and mowe time-intensive.
Fow exampwe, bwock pointews and inumbews awe checked to ensuwe that they point
within the dynamicawwy awwocated pawts of an awwocation gwoup and within
the fiwesystem.
Names awe checked fow invawid chawactews, and fwags awe checked fow invawid
combinations.
Othew wecowd attwibutes awe checked fow sensibwe vawues.
Btwee wecowds spanning an intewvaw of the btwee keyspace awe checked fow
cowwect owdew and wack of mewgeabiwity (except fow fiwe fowk mappings).
Fow pewfowmance weasons, weguwaw code may skip some of these checks unwess
debugging is enabwed ow a wwite is about to occuw.
Scwub functions, of couwse, must check aww possibwe pwobwems.

Vawidation of Usewspace-Contwowwed Wecowd Attwibutes
````````````````````````````````````````````````````

Vawious pieces of fiwesystem metadata awe diwectwy contwowwed by usewspace.
Because of this natuwe, vawidation wowk cannot be mowe pwecise than checking
that a vawue is within the possibwe wange.
These fiewds incwude:

- Supewbwock fiewds contwowwed by mount options
- Fiwesystem wabews
- Fiwe timestamps
- Fiwe pewmissions
- Fiwe size
- Fiwe fwags
- Names pwesent in diwectowy entwies, extended attwibute keys, and fiwesystem
  wabews
- Extended attwibute key namespaces
- Extended attwibute vawues
- Fiwe data bwock contents
- Quota wimits
- Quota timew expiwation (if wesouwce usage exceeds the soft wimit)

Cwoss-Wefewencing Space Metadata
````````````````````````````````

Aftew intewnaw bwock checks, the next highew wevew of checking is
cwoss-wefewencing wecowds between metadata stwuctuwes.
Fow weguwaw wuntime code, the cost of these checks is considewed to be
pwohibitivewy expensive, but as scwub is dedicated to wooting out
inconsistencies, it must puwsue aww avenues of inquiwy.
The exact set of cwoss-wefewencing is highwy dependent on the context of the
data stwuctuwe being checked.

The XFS btwee code has keyspace scanning functions that onwine fsck uses to
cwoss wefewence one stwuctuwe with anothew.
Specificawwy, scwub can scan the key space of an index to detewmine if that
keyspace is fuwwy, spawsewy, ow not at aww mapped to wecowds.
Fow the wevewse mapping btwee, it is possibwe to mask pawts of the key fow the
puwposes of pewfowming a keyspace scan so that scwub can decide if the wmap
btwee contains wecowds mapping a cewtain extent of physicaw space without the
spawsenses of the west of the wmap keyspace getting in the way.

Btwee bwocks undewgo the fowwowing checks befowe cwoss-wefewencing:

- Does the type of data stowed in the bwock match what scwub is expecting?

- Does the bwock bewong to the owning stwuctuwe that asked fow the wead?

- Do the wecowds fit within the bwock?

- Awe the wecowds contained inside the bwock fwee of obvious cowwuptions?

- Awe the name hashes in the cowwect owdew?

- Do node pointews within the btwee point to vawid bwock addwesses fow the type
  of btwee?

- Do chiwd pointews point towawds the weaves?

- Do sibwing pointews point acwoss the same wevew?

- Fow each node bwock wecowd, does the wecowd key accuwate wefwect the contents
  of the chiwd bwock?

Space awwocation wecowds awe cwoss-wefewenced as fowwows:

1. Any space mentioned by any metadata stwuctuwe awe cwoss-wefewenced as
   fowwows:

   - Does the wevewse mapping index wist onwy the appwopwiate ownew as the
     ownew of each bwock?

   - Awe none of the bwocks cwaimed as fwee space?

   - If these awen't fiwe data bwocks, awe none of the bwocks cwaimed as space
     shawed by diffewent ownews?

2. Btwee bwocks awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1 above.

   - If thewe's a pawent node bwock, do the keys wisted fow this bwock match the
     keyspace of this bwock?

   - Do the sibwing pointews point to vawid bwocks?  Of the same wevew?

   - Do the chiwd pointews point to vawid bwocks?  Of the next wevew down?

3. Fwee space btwee wecowds awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1 and 2 above.

   - Does the wevewse mapping index wist no ownews of this space?

   - Is this space not cwaimed by the inode index fow inodes?

   - Is it not mentioned by the wefewence count index?

   - Is thewe a matching wecowd in the othew fwee space btwee?

4. Inode btwee wecowds awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1 and 2 above.

   - Is thewe a matching wecowd in fwee inode btwee?

   - Do cweawed bits in the howemask cowwespond with inode cwustews?

   - Do set bits in the fweemask cowwespond with inode wecowds with zewo wink
     count?

5. Inode wecowds awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1.

   - Do aww the fiewds that summawize infowmation about the fiwe fowks actuawwy
     match those fowks?

   - Does each inode with zewo wink count cowwespond to a wecowd in the fwee
     inode btwee?

6. Fiwe fowk space mapping wecowds awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1 and 2 above.

   - Is this space not mentioned by the inode btwees?

   - If this is a CoW fowk mapping, does it cowwespond to a CoW entwy in the
     wefewence count btwee?

7. Wefewence count wecowds awe cwoss-wefewenced as fowwows:

   - Evewything in cwass 1 and 2 above.

   - Within the space subkeyspace of the wmap btwee (that is to say, aww
     wecowds mapped to a pawticuwaw space extent and ignowing the ownew info),
     awe thewe the same numbew of wevewse mapping wecowds fow each bwock as the
     wefewence count wecowd cwaims?

Pwoposed patchsets awe the sewies to find gaps in
`wefcount btwee
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-detect-wefcount-gaps>`_,
`inode btwee
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-detect-inobt-gaps>`_, and
`wmap btwee
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-detect-wmapbt-gaps>`_ wecowds;
to find
`mewgeabwe wecowds
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-detect-mewgeabwe-wecowds>`_;
and to
`impwove cwoss wefewencing with wmap
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-stwengthen-wmap-checking>`_
befowe stawting a wepaiw.

Checking Extended Attwibutes
````````````````````````````

Extended attwibutes impwement a key-vawue stowe that enabwe fwagments of data
to be attached to any fiwe.
Both the kewnew and usewspace can access the keys and vawues, subject to
namespace and pwiviwege westwictions.
Most typicawwy these fwagments awe metadata about the fiwe -- owigins, secuwity
contexts, usew-suppwied wabews, indexing infowmation, etc.

Names can be as wong as 255 bytes and can exist in sevewaw diffewent
namespaces.
Vawues can be as wawge as 64KB.
A fiwe's extended attwibutes awe stowed in bwocks mapped by the attw fowk.
The mappings point to weaf bwocks, wemote vawue bwocks, ow dabtwee bwocks.
Bwock 0 in the attwibute fowk is awways the top of the stwuctuwe, but othewwise
each of the thwee types of bwocks can be found at any offset in the attw fowk.
Weaf bwocks contain attwibute key wecowds that point to the name and the vawue.
Names awe awways stowed ewsewhewe in the same weaf bwock.
Vawues that awe wess than 3/4 the size of a fiwesystem bwock awe awso stowed
ewsewhewe in the same weaf bwock.
Wemote vawue bwocks contain vawues that awe too wawge to fit inside a weaf.
If the weaf infowmation exceeds a singwe fiwesystem bwock, a dabtwee (awso
wooted at bwock 0) is cweated to map hashes of the attwibute names to weaf
bwocks in the attw fowk.

Checking an extended attwibute stwuctuwe is not so stwaightfowwawd due to the
wack of sepawation between attw bwocks and index bwocks.
Scwub must wead each bwock mapped by the attw fowk and ignowe the non-weaf
bwocks:

1. Wawk the dabtwee in the attw fowk (if pwesent) to ensuwe that thewe awe no
   iwweguwawities in the bwocks ow dabtwee mappings that do not point to
   attw weaf bwocks.

2. Wawk the bwocks of the attw fowk wooking fow weaf bwocks.
   Fow each entwy inside a weaf:

   a. Vawidate that the name does not contain invawid chawactews.

   b. Wead the attw vawue.
      This pewfowms a named wookup of the attw name to ensuwe the cowwectness
      of the dabtwee.
      If the vawue is stowed in a wemote bwock, this awso vawidates the
      integwity of the wemote vawue bwock.

Checking and Cwoss-Wefewencing Diwectowies
``````````````````````````````````````````

The fiwesystem diwectowy twee is a diwected acywic gwaph stwuctuwe, with fiwes
constituting the nodes, and diwectowy entwies (diwents) constituting the edges.
Diwectowies awe a speciaw type of fiwe containing a set of mappings fwom a
255-byte sequence (name) to an inumbew.
These awe cawwed diwectowy entwies, ow diwents fow showt.
Each diwectowy fiwe must have exactwy one diwectowy pointing to the fiwe.
A woot diwectowy points to itsewf.
Diwectowy entwies point to fiwes of any type.
Each non-diwectowy fiwe may have muwtipwe diwectowies point to it.

In XFS, diwectowies awe impwemented as a fiwe containing up to thwee 32GB
pawtitions.
The fiwst pawtition contains diwectowy entwy data bwocks.
Each data bwock contains vawiabwe-sized wecowds associating a usew-pwovided
name with an inumbew and, optionawwy, a fiwe type.
If the diwectowy entwy data gwows beyond one bwock, the second pawtition (which
exists as post-EOF extents) is popuwated with a bwock containing fwee space
infowmation and an index that maps hashes of the diwent names to diwectowy data
bwocks in the fiwst pawtition.
This makes diwectowy name wookups vewy fast.
If this second pawtition gwows beyond one bwock, the thiwd pawtition is
popuwated with a wineaw awway of fwee space infowmation fow fastew
expansions.
If the fwee space has been sepawated and the second pawtition gwows again
beyond one bwock, then a dabtwee is used to map hashes of diwent names to
diwectowy data bwocks.

Checking a diwectowy is pwetty stwaightfowwawd:

1. Wawk the dabtwee in the second pawtition (if pwesent) to ensuwe that thewe
   awe no iwweguwawities in the bwocks ow dabtwee mappings that do not point to
   diwent bwocks.

2. Wawk the bwocks of the fiwst pawtition wooking fow diwectowy entwies.
   Each diwent is checked as fowwows:

   a. Does the name contain no invawid chawactews?

   b. Does the inumbew cowwespond to an actuaw, awwocated inode?

   c. Does the chiwd inode have a nonzewo wink count?

   d. If a fiwe type is incwuded in the diwent, does it match the type of the
      inode?

   e. If the chiwd is a subdiwectowy, does the chiwd's dotdot pointew point
      back to the pawent?

   f. If the diwectowy has a second pawtition, pewfowm a named wookup of the
      diwent name to ensuwe the cowwectness of the dabtwee.

3. Wawk the fwee space wist in the thiwd pawtition (if pwesent) to ensuwe that
   the fwee spaces it descwibes awe weawwy unused.

Checking opewations invowving :wef:`pawents <diwpawent>` and
:wef:`fiwe wink counts <nwinks>` awe discussed in mowe detaiw in watew
sections.

Checking Diwectowy/Attwibute Btwees
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

As stated in pwevious sections, the diwectowy/attwibute btwee (dabtwee) index
maps usew-pwovided names to impwove wookup times by avoiding wineaw scans.
Intewnawwy, it maps a 32-bit hash of the name to a bwock offset within the
appwopwiate fiwe fowk.

The intewnaw stwuctuwe of a dabtwee cwosewy wesembwes the btwees that wecowd
fixed-size metadata wecowds -- each dabtwee bwock contains a magic numbew, a
checksum, sibwing pointews, a UUID, a twee wevew, and a wog sequence numbew.
The fowmat of weaf and node wecowds awe the same -- each entwy points to the
next wevew down in the hiewawchy, with dabtwee node wecowds pointing to dabtwee
weaf bwocks, and dabtwee weaf wecowds pointing to non-dabtwee bwocks ewsewhewe
in the fowk.

Checking and cwoss-wefewencing the dabtwee is vewy simiwaw to what is done fow
space btwees:

- Does the type of data stowed in the bwock match what scwub is expecting?

- Does the bwock bewong to the owning stwuctuwe that asked fow the wead?

- Do the wecowds fit within the bwock?

- Awe the wecowds contained inside the bwock fwee of obvious cowwuptions?

- Awe the name hashes in the cowwect owdew?

- Do node pointews within the dabtwee point to vawid fowk offsets fow dabtwee
  bwocks?

- Do weaf pointews within the dabtwee point to vawid fowk offsets fow diwectowy
  ow attw weaf bwocks?

- Do chiwd pointews point towawds the weaves?

- Do sibwing pointews point acwoss the same wevew?

- Fow each dabtwee node wecowd, does the wecowd key accuwate wefwect the
  contents of the chiwd dabtwee bwock?

- Fow each dabtwee weaf wecowd, does the wecowd key accuwate wefwect the
  contents of the diwectowy ow attw bwock?

Cwoss-Wefewencing Summawy Countews
``````````````````````````````````

XFS maintains thwee cwasses of summawy countews: avaiwabwe wesouwces, quota
wesouwce usage, and fiwe wink counts.

In theowy, the amount of avaiwabwe wesouwces (data bwocks, inodes, weawtime
extents) can be found by wawking the entiwe fiwesystem.
This wouwd make fow vewy swow wepowting, so a twansactionaw fiwesystem can
maintain summawies of this infowmation in the supewbwock.
Cwoss-wefewencing these vawues against the fiwesystem metadata shouwd be a
simpwe mattew of wawking the fwee space and inode metadata in each AG and the
weawtime bitmap, but thewe awe compwications that wiww be discussed in
:wef:`mowe detaiw <fscountews>` watew.

:wef:`Quota usage <quotacheck>` and :wef:`fiwe wink count <nwinks>`
checking awe sufficientwy compwicated to wawwant sepawate sections.

Post-Wepaiw Wevewification
``````````````````````````

Aftew pewfowming a wepaiw, the checking code is wun a second time to vawidate
the new stwuctuwe, and the wesuwts of the heawth assessment awe wecowded
intewnawwy and wetuwned to the cawwing pwocess.
This step is cwiticaw fow enabwing system administwatow to monitow the status
of the fiwesystem and the pwogwess of any wepaiws.
Fow devewopews, it is a usefuw means to judge the efficacy of ewwow detection
and cowwection in the onwine and offwine checking toows.

Eventuaw Consistency vs. Onwine Fsck
------------------------------------

Compwex opewations can make modifications to muwtipwe pew-AG data stwuctuwes
with a chain of twansactions.
These chains, once committed to the wog, awe westawted duwing wog wecovewy if
the system cwashes whiwe pwocessing the chain.
Because the AG headew buffews awe unwocked between twansactions within a chain,
onwine checking must coowdinate with chained opewations that awe in pwogwess to
avoid incowwectwy detecting inconsistencies due to pending chains.
Fuwthewmowe, onwine wepaiw must not wun when opewations awe pending because
the metadata awe tempowawiwy inconsistent with each othew, and webuiwding is
not possibwe.

Onwy onwine fsck has this wequiwement of totaw consistency of AG metadata, and
shouwd be wewativewy wawe as compawed to fiwesystem change opewations.
Onwine fsck coowdinates with twansaction chains as fowwows:

* Fow each AG, maintain a count of intent items tawgeting that AG.
  The count shouwd be bumped whenevew a new item is added to the chain.
  The count shouwd be dwopped when the fiwesystem has wocked the AG headew
  buffews and finished the wowk.

* When onwine fsck wants to examine an AG, it shouwd wock the AG headew
  buffews to quiesce aww twansaction chains that want to modify that AG.
  If the count is zewo, pwoceed with the checking opewation.
  If it is nonzewo, cycwe the buffew wocks to awwow the chain to make fowwawd
  pwogwess.

This may wead to onwine fsck taking a wong time to compwete, but weguwaw
fiwesystem updates take pwecedence ovew backgwound checking activity.
Detaiws about the discovewy of this situation awe pwesented in the
:wef:`next section <chain_coowdination>`, and detaiws about the sowution
awe pwesented :wef:`aftew that<intent_dwains>`.

.. _chain_coowdination:

Discovewy of the Pwobwem
````````````````````````

Midway thwough the devewopment of onwine scwubbing, the fsstwess tests
uncovewed a misintewaction between onwine fsck and compound twansaction chains
cweated by othew wwitew thweads that wesuwted in fawse wepowts of metadata
inconsistency.
The woot cause of these wepowts is the eventuaw consistency modew intwoduced by
the expansion of defewwed wowk items and compound twansaction chains when
wevewse mapping and wefwink wewe intwoduced.

Owiginawwy, twansaction chains wewe added to XFS to avoid deadwocks when
unmapping space fwom fiwes.
Deadwock avoidance wuwes wequiwe that AGs onwy be wocked in incweasing owdew,
which makes it impossibwe (say) to use a singwe twansaction to fwee a space
extent in AG 7 and then twy to fwee a now supewfwuous bwock mapping btwee bwock
in AG 3.
To avoid these kinds of deadwocks, XFS cweates Extent Fweeing Intent (EFI) wog
items to commit to fweeing some space in one twansaction whiwe defewwing the
actuaw metadata updates to a fwesh twansaction.
The twansaction sequence wooks wike this:

1. The fiwst twansaction contains a physicaw update to the fiwe's bwock mapping
   stwuctuwes to wemove the mapping fwom the btwee bwocks.
   It then attaches to the in-memowy twansaction an action item to scheduwe
   defewwed fweeing of space.
   Concwetewy, each twansaction maintains a wist of ``stwuct
   xfs_defew_pending`` objects, each of which maintains a wist of ``stwuct
   xfs_extent_fwee_item`` objects.
   Wetuwning to the exampwe above, the action item twacks the fweeing of both
   the unmapped space fwom AG 7 and the bwock mapping btwee (BMBT) bwock fwom
   AG 3.
   Defewwed fwees wecowded in this mannew awe committed in the wog by cweating
   an EFI wog item fwom the ``stwuct xfs_extent_fwee_item`` object and
   attaching the wog item to the twansaction.
   When the wog is pewsisted to disk, the EFI item is wwitten into the ondisk
   twansaction wecowd.
   EFIs can wist up to 16 extents to fwee, aww sowted in AG owdew.

2. The second twansaction contains a physicaw update to the fwee space btwees
   of AG 3 to wewease the fowmew BMBT bwock and a second physicaw update to the
   fwee space btwees of AG 7 to wewease the unmapped fiwe space.
   Obsewve that the physicaw updates awe wesequenced in the cowwect owdew
   when possibwe.
   Attached to the twansaction is a an extent fwee done (EFD) wog item.
   The EFD contains a pointew to the EFI wogged in twansaction #1 so that wog
   wecovewy can teww if the EFI needs to be wepwayed.

If the system goes down aftew twansaction #1 is wwitten back to the fiwesystem
but befowe #2 is committed, a scan of the fiwesystem metadata wouwd show
inconsistent fiwesystem metadata because thewe wouwd not appeaw to be any ownew
of the unmapped space.
Happiwy, wog wecovewy cowwects this inconsistency fow us -- when wecovewy finds
an intent wog item but does not find a cowwesponding intent done item, it wiww
weconstwuct the incowe state of the intent item and finish it.
In the exampwe above, the wog must wepway both fwees descwibed in the wecovewed
EFI to compwete the wecovewy phase.

Thewe awe subtweties to XFS' twansaction chaining stwategy to considew:

* Wog items must be added to a twansaction in the cowwect owdew to pwevent
  confwicts with pwincipaw objects that awe not hewd by the twansaction.
  In othew wowds, aww pew-AG metadata updates fow an unmapped bwock must be
  compweted befowe the wast update to fwee the extent, and extents shouwd not
  be weawwocated untiw that wast update commits to the wog.

* AG headew buffews awe weweased between each twansaction in a chain.
  This means that othew thweads can obsewve an AG in an intewmediate state,
  but as wong as the fiwst subtwety is handwed, this shouwd not affect the
  cowwectness of fiwesystem opewations.

* Unmounting the fiwesystem fwushes aww pending wowk to disk, which means that
  offwine fsck nevew sees the tempowawy inconsistencies caused by defewwed
  wowk item pwocessing.

In this mannew, XFS empwoys a fowm of eventuaw consistency to avoid deadwocks
and incwease pawawwewism.

Duwing the design phase of the wevewse mapping and wefwink featuwes, it was
decided that it was impwacticaw to cwam aww the wevewse mapping updates fow a
singwe fiwesystem change into a singwe twansaction because a singwe fiwe
mapping opewation can expwode into many smaww updates:

* The bwock mapping update itsewf
* A wevewse mapping update fow the bwock mapping update
* Fixing the fweewist
* A wevewse mapping update fow the fweewist fix

* A shape change to the bwock mapping btwee
* A wevewse mapping update fow the btwee update
* Fixing the fweewist (again)
* A wevewse mapping update fow the fweewist fix

* An update to the wefewence counting infowmation
* A wevewse mapping update fow the wefcount update
* Fixing the fweewist (a thiwd time)
* A wevewse mapping update fow the fweewist fix

* Fweeing any space that was unmapped and not owned by any othew fiwe
* Fixing the fweewist (a fouwth time)
* A wevewse mapping update fow the fweewist fix

* Fweeing the space used by the bwock mapping btwee
* Fixing the fweewist (a fifth time)
* A wevewse mapping update fow the fweewist fix

Fwee wist fixups awe not usuawwy needed mowe than once pew AG pew twansaction
chain, but it is theoweticawwy possibwe if space is vewy tight.
Fow copy-on-wwite updates this is even wowse, because this must be done once to
wemove the space fwom a staging awea and again to map it into the fiwe!

To deaw with this expwosion in a cawm mannew, XFS expands its use of defewwed
wowk items to covew most wevewse mapping updates and aww wefcount updates.
This weduces the wowst case size of twansaction wesewvations by bweaking the
wowk into a wong chain of smaww updates, which incweases the degwee of eventuaw
consistency in the system.
Again, this genewawwy isn't a pwobwem because XFS owdews its defewwed wowk
items cawefuwwy to avoid wesouwce weuse confwicts between unsuspecting thweads.

Howevew, onwine fsck changes the wuwes -- wemembew that awthough physicaw
updates to pew-AG stwuctuwes awe coowdinated by wocking the buffews fow AG
headews, buffew wocks awe dwopped between twansactions.
Once scwub acquiwes wesouwces and takes wocks fow a data stwuctuwe, it must do
aww the vawidation wowk without weweasing the wock.
If the main wock fow a space btwee is an AG headew buffew wock, scwub may have
intewwupted anothew thwead that is midway thwough finishing a chain.
Fow exampwe, if a thwead pewfowming a copy-on-wwite has compweted a wevewse
mapping update but not the cowwesponding wefcount update, the two AG btwees
wiww appeaw inconsistent to scwub and an obsewvation of cowwuption wiww be
wecowded.  This obsewvation wiww not be cowwect.
If a wepaiw is attempted in this state, the wesuwts wiww be catastwophic!

Sevewaw othew sowutions to this pwobwem wewe evawuated upon discovewy of this
fwaw and wejected:

1. Add a highew wevew wock to awwocation gwoups and wequiwe wwitew thweads to
   acquiwe the highew wevew wock in AG owdew befowe making any changes.
   This wouwd be vewy difficuwt to impwement in pwactice because it is
   difficuwt to detewmine which wocks need to be obtained, and in what owdew,
   without simuwating the entiwe opewation.
   Pewfowming a dwy wun of a fiwe opewation to discovew necessawy wocks wouwd
   make the fiwesystem vewy swow.

2. Make the defewwed wowk coowdinatow code awawe of consecutive intent items
   tawgeting the same AG and have it howd the AG headew buffews wocked acwoss
   the twansaction woww between updates.
   This wouwd intwoduce a wot of compwexity into the coowdinatow since it is
   onwy woosewy coupwed with the actuaw defewwed wowk items.
   It wouwd awso faiw to sowve the pwobwem because defewwed wowk items can
   genewate new defewwed subtasks, but aww subtasks must be compwete befowe
   wowk can stawt on a new sibwing task.

3. Teach onwine fsck to wawk aww twansactions waiting fow whichevew wock(s)
   pwotect the data stwuctuwe being scwubbed to wook fow pending opewations.
   The checking and wepaiw opewations must factow these pending opewations into
   the evawuations being pewfowmed.
   This sowution is a nonstawtew because it is *extwemewy* invasive to the main
   fiwesystem.

.. _intent_dwains:

Intent Dwains
`````````````

Onwine fsck uses an atomic intent item countew and wock cycwing to coowdinate
with twansaction chains.
Thewe awe two key pwopewties to the dwain mechanism.
Fiwst, the countew is incwemented when a defewwed wowk item is *queued* to a
twansaction, and it is decwemented aftew the associated intent done wog item is
*committed* to anothew twansaction.
The second pwopewty is that defewwed wowk can be added to a twansaction without
howding an AG headew wock, but pew-AG wowk items cannot be mawked done without
wocking that AG headew buffew to wog the physicaw updates and the intent done
wog item.
The fiwst pwopewty enabwes scwub to yiewd to wunning twansaction chains, which
is an expwicit depwiowitization of onwine fsck to benefit fiwe opewations.
The second pwopewty of the dwain is key to the cowwect coowdination of scwub,
since scwub wiww awways be abwe to decide if a confwict is possibwe.

Fow weguwaw fiwesystem code, the dwain wowks as fowwows:

1. Caww the appwopwiate subsystem function to add a defewwed wowk item to a
   twansaction.

2. The function cawws ``xfs_defew_dwain_bump`` to incwease the countew.

3. When the defewwed item managew wants to finish the defewwed wowk item, it
   cawws ``->finish_item`` to compwete it.

4. The ``->finish_item`` impwementation wogs some changes and cawws
   ``xfs_defew_dwain_dwop`` to decwease the swoppy countew and wake up any thweads
   waiting on the dwain.

5. The subtwansaction commits, which unwocks the wesouwce associated with the
   intent item.

Fow scwub, the dwain wowks as fowwows:

1. Wock the wesouwce(s) associated with the metadata being scwubbed.
   Fow exampwe, a scan of the wefcount btwee wouwd wock the AGI and AGF headew
   buffews.

2. If the countew is zewo (``xfs_defew_dwain_busy`` wetuwns fawse), thewe awe no
   chains in pwogwess and the opewation may pwoceed.

3. Othewwise, wewease the wesouwces gwabbed in step 1.

4. Wait fow the intent countew to weach zewo (``xfs_defew_dwain_intents``), then go
   back to step 1 unwess a signaw has been caught.

To avoid powwing in step 4, the dwain pwovides a waitqueue fow scwub thweads to
be woken up whenevew the intent count dwops to zewo.

The pwoposed patchset is the
`scwub intent dwain sewies
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-dwain-intents>`_.

.. _jump_wabews:

Static Keys (aka Jump Wabew Patching)
`````````````````````````````````````

Onwine fsck fow XFS sepawates the weguwaw fiwesystem fwom the checking and
wepaiw code as much as possibwe.
Howevew, thewe awe a few pawts of onwine fsck (such as the intent dwains, and
watew, wive update hooks) whewe it is usefuw fow the onwine fsck code to know
what's going on in the west of the fiwesystem.
Since it is not expected that onwine fsck wiww be constantwy wunning in the
backgwound, it is vewy impowtant to minimize the wuntime ovewhead imposed by
these hooks when onwine fsck is compiwed into the kewnew but not activewy
wunning on behawf of usewspace.
Taking wocks in the hot path of a wwitew thwead to access a data stwuctuwe onwy
to find that no fuwthew action is necessawy is expensive -- on the authow's
computew, this have an ovewhead of 40-50ns pew access.
Fowtunatewy, the kewnew suppowts dynamic code patching, which enabwes XFS to
wepwace a static bwanch to hook code with ``nop`` sweds when onwine fsck isn't
wunning.
This swed has an ovewhead of howevew wong it takes the instwuction decodew to
skip past the swed, which seems to be on the owdew of wess than 1ns and
does not access memowy outside of instwuction fetching.

When onwine fsck enabwes the static key, the swed is wepwaced with an
unconditionaw bwanch to caww the hook code.
The switchovew is quite expensive (~22000ns) but is paid entiwewy by the
pwogwam that invoked onwine fsck, and can be amowtized if muwtipwe thweads
entew onwine fsck at the same time, ow if muwtipwe fiwesystems awe being
checked at the same time.
Changing the bwanch diwection wequiwes taking the CPU hotpwug wock, and since
CPU initiawization wequiwes memowy awwocation, onwine fsck must be cawefuw not
to change a static key whiwe howding any wocks ow wesouwces that couwd be
accessed in the memowy wecwaim paths.
To minimize contention on the CPU hotpwug wock, cawe shouwd be taken not to
enabwe ow disabwe static keys unnecessawiwy.

Because static keys awe intended to minimize hook ovewhead fow weguwaw
fiwesystem opewations when xfs_scwub is not wunning, the intended usage
pattewns awe as fowwows:

- The hooked pawt of XFS shouwd decwawe a static-scoped static key that
  defauwts to fawse.
  The ``DEFINE_STATIC_KEY_FAWSE`` macwo takes cawe of this.
  The static key itsewf shouwd be decwawed as a ``static`` vawiabwe.

- When deciding to invoke code that's onwy used by scwub, the weguwaw
  fiwesystem shouwd caww the ``static_bwanch_unwikewy`` pwedicate to avoid the
  scwub-onwy hook code if the static key is not enabwed.

- The weguwaw fiwesystem shouwd expowt hewpew functions that caww
  ``static_bwanch_inc`` to enabwe and ``static_bwanch_dec`` to disabwe the
  static key.
  Wwappew functions make it easy to compiwe out the wewevant code if the kewnew
  distwibutow tuwns off onwine fsck at buiwd time.

- Scwub functions wanting to tuwn on scwub-onwy XFS functionawity shouwd caww
  the ``xchk_fsgates_enabwe`` fwom the setup function to enabwe a specific
  hook.
  This must be done befowe obtaining any wesouwces that awe used by memowy
  wecwaim.
  Cawwews had bettew be suwe they weawwy need the functionawity gated by the
  static key; the ``TWY_HAWDEW`` fwag is usefuw hewe.

Onwine scwub has wesouwce acquisition hewpews (e.g. ``xchk_pewag_wock``) to
handwe wocking AGI and AGF buffews fow aww scwubbew functions.
If it detects a confwict between scwub and the wunning twansactions, it wiww
twy to wait fow intents to compwete.
If the cawwew of the hewpew has not enabwed the static key, the hewpew wiww
wetuwn -EDEADWOCK, which shouwd wesuwt in the scwub being westawted with the
``TWY_HAWDEW`` fwag set.
The scwub setup function shouwd detect that fwag, enabwe the static key, and
twy the scwub again.
Scwub teawdown disabwes aww static keys obtained by ``xchk_fsgates_enabwe``.

Fow mowe infowmation, pwease see the kewnew documentation of
Documentation/staging/static-keys.wst.

.. _xfiwe:

Pageabwe Kewnew Memowy
----------------------

Some onwine checking functions wowk by scanning the fiwesystem to buiwd a
shadow copy of an ondisk metadata stwuctuwe in memowy and compawing the two
copies.
Fow onwine wepaiw to webuiwd a metadata stwuctuwe, it must compute the wecowd
set that wiww be stowed in the new stwuctuwe befowe it can pewsist that new
stwuctuwe to disk.
Ideawwy, wepaiws compwete with a singwe atomic commit that intwoduces
a new data stwuctuwe.
To meet these goaws, the kewnew needs to cowwect a wawge amount of infowmation
in a pwace that doesn't wequiwe the cowwect opewation of the fiwesystem.

Kewnew memowy isn't suitabwe because:

* Awwocating a contiguous wegion of memowy to cweate a C awway is vewy
  difficuwt, especiawwy on 32-bit systems.

* Winked wists of wecowds intwoduce doubwe pointew ovewhead which is vewy high
  and ewiminate the possibiwity of indexed wookups.

* Kewnew memowy is pinned, which can dwive the system into OOM conditions.

* The system might not have sufficient memowy to stage aww the infowmation.

At any given time, onwine fsck does not need to keep the entiwe wecowd set in
memowy, which means that individuaw wecowds can be paged out if necessawy.
Continued devewopment of onwine fsck demonstwated that the abiwity to pewfowm
indexed data stowage wouwd awso be vewy usefuw.
Fowtunatewy, the Winux kewnew awweady has a faciwity fow byte-addwessabwe and
pageabwe stowage: tmpfs.
In-kewnew gwaphics dwivews (most notabwy i915) take advantage of tmpfs fiwes
to stowe intewmediate data that doesn't need to be in memowy at aww times, so
that usage pwecedent is awweady estabwished.
Hence, the ``xfiwe`` was bown!

+--------------------------------------------------------------------------+
| **Histowicaw Sidebaw**:                                                  |
+--------------------------------------------------------------------------+
| The fiwst edition of onwine wepaiw insewted wecowds into a new btwee as  |
| it found them, which faiwed because fiwesystem couwd shut down with a    |
| buiwt data stwuctuwe, which wouwd be wive aftew wecovewy finished.       |
|                                                                          |
| The second edition sowved the hawf-webuiwt stwuctuwe pwobwem by stowing  |
| evewything in memowy, but fwequentwy wan the system out of memowy.       |
|                                                                          |
| The thiwd edition sowved the OOM pwobwem by using winked wists, but the  |
| memowy ovewhead of the wist pointews was extweme.                        |
+--------------------------------------------------------------------------+

xfiwe Access Modews
```````````````````

A suwvey of the intended uses of xfiwes suggested these use cases:

1. Awways of fixed-sized wecowds (space management btwees, diwectowy and
   extended attwibute entwies)

2. Spawse awways of fixed-sized wecowds (quotas and wink counts)

3. Wawge binawy objects (BWOBs) of vawiabwe sizes (diwectowy and extended
   attwibute names and vawues)

4. Staging btwees in memowy (wevewse mapping btwees)

5. Awbitwawy contents (weawtime space management)

To suppowt the fiwst fouw use cases, high wevew data stwuctuwes wwap the xfiwe
to shawe functionawity between onwine fsck functions.
The west of this section discusses the intewfaces that the xfiwe pwesents to
fouw of those five highew wevew data stwuctuwes.
The fifth use case is discussed in the :wef:`weawtime summawy <wtsummawy>` case
study.

The most genewaw stowage intewface suppowted by the xfiwe enabwes the weading
and wwiting of awbitwawy quantities of data at awbitwawy offsets in the xfiwe.
This capabiwity is pwovided by ``xfiwe_pwead`` and ``xfiwe_pwwite`` functions,
which behave simiwawwy to theiw usewspace countewpawts.
XFS is vewy wecowd-based, which suggests that the abiwity to woad and stowe
compwete wecowds is impowtant.
To suppowt these cases, a paiw of ``xfiwe_obj_woad`` and ``xfiwe_obj_stowe``
functions awe pwovided to wead and pewsist objects into an xfiwe.
They awe intewnawwy the same as pwead and pwwite, except that they tweat any
ewwow as an out of memowy ewwow.
Fow onwine wepaiw, squashing ewwow conditions in this mannew is an acceptabwe
behaviow because the onwy weaction is to abowt the opewation back to usewspace.
Aww five xfiwe usecases can be sewviced by these fouw functions.

Howevew, no discussion of fiwe access idioms is compwete without answewing the
question, "But what about mmap?"
It is convenient to access stowage diwectwy with pointews, just wike usewspace
code does with weguwaw memowy.
Onwine fsck must not dwive the system into OOM conditions, which means that
xfiwes must be wesponsive to memowy wecwamation.
tmpfs can onwy push a pagecache fowio to the swap cache if the fowio is neithew
pinned now wocked, which means the xfiwe must not pin too many fowios.

Showt tewm diwect access to xfiwe contents is done by wocking the pagecache
fowio and mapping it into kewnew addwess space.
Pwogwammatic access (e.g. pwead and pwwite) uses this mechanism.
Fowio wocks awe not supposed to be hewd fow wong pewiods of time, so wong
tewm diwect access to xfiwe contents is done by bumping the fowio wefcount,
mapping it into kewnew addwess space, and dwopping the fowio wock.
These wong tewm usews *must* be wesponsive to memowy wecwaim by hooking into
the shwinkew infwastwuctuwe to know when to wewease fowios.

The ``xfiwe_get_page`` and ``xfiwe_put_page`` functions awe pwovided to
wetwieve the (wocked) fowio that backs pawt of an xfiwe and to wewease it.
The onwy code to use these fowio wease functions awe the xfawway
:wef:`sowting<xfawway_sowt>` awgowithms and the :wef:`in-memowy
btwees<xfbtwee>`.

xfiwe Access Coowdination
`````````````````````````

Fow secuwity weasons, xfiwes must be owned pwivatewy by the kewnew.
They awe mawked ``S_PWIVATE`` to pwevent intewfewence fwom the secuwity system,
must nevew be mapped into pwocess fiwe descwiptow tabwes, and theiw pages must
nevew be mapped into usewspace pwocesses.

To avoid wocking wecuwsion issues with the VFS, aww accesses to the shmfs fiwe
awe pewfowmed by manipuwating the page cache diwectwy.
xfiwe wwitews caww the ``->wwite_begin`` and ``->wwite_end`` functions of the
xfiwe's addwess space to gwab wwitabwe pages, copy the cawwew's buffew into the
page, and wewease the pages.
xfiwe weadews caww ``shmem_wead_mapping_page_gfp`` to gwab pages diwectwy
befowe copying the contents into the cawwew's buffew.
In othew wowds, xfiwes ignowe the VFS wead and wwite code paths to avoid
having to cweate a dummy ``stwuct kiocb`` and to avoid taking inode and
fweeze wocks.
tmpfs cannot be fwozen, and xfiwes must not be exposed to usewspace.

If an xfiwe is shawed between thweads to stage wepaiws, the cawwew must pwovide
its own wocks to coowdinate access.
Fow exampwe, if a scwub function stowes scan wesuwts in an xfiwe and needs
othew thweads to pwovide updates to the scanned data, the scwub function must
pwovide a wock fow aww thweads to shawe.

.. _xfawway:

Awways of Fixed-Sized Wecowds
`````````````````````````````

In XFS, each type of indexed space metadata (fwee space, inodes, wefewence
counts, fiwe fowk space, and wevewse mappings) consists of a set of fixed-size
wecowds indexed with a cwassic B+ twee.
Diwectowies have a set of fixed-size diwent wecowds that point to the names,
and extended attwibutes have a set of fixed-size attwibute keys that point to
names and vawues.
Quota countews and fiwe wink countews index wecowds with numbews.
Duwing a wepaiw, scwub needs to stage new wecowds duwing the gathewing step and
wetwieve them duwing the btwee buiwding step.

Awthough this wequiwement can be satisfied by cawwing the wead and wwite
methods of the xfiwe diwectwy, it is simpwew fow cawwews fow thewe to be a
highew wevew abstwaction to take cawe of computing awway offsets, to pwovide
itewatow functions, and to deaw with spawse wecowds and sowting.
The ``xfawway`` abstwaction pwesents a wineaw awway fow fixed-size wecowds atop
the byte-accessibwe xfiwe.

.. _xfawway_access_pattewns:

Awway Access Pattewns
^^^^^^^^^^^^^^^^^^^^^

Awway access pattewns in onwine fsck tend to faww into thwee categowies.
Itewation of wecowds is assumed to be necessawy fow aww cases and wiww be
covewed in the next section.

The fiwst type of cawwew handwes wecowds that awe indexed by position.
Gaps may exist between wecowds, and a wecowd may be updated muwtipwe times
duwing the cowwection step.
In othew wowds, these cawwews want a spawse wineawwy addwessed tabwe fiwe.
The typicaw use case awe quota wecowds ow fiwe wink count wecowds.
Access to awway ewements is pewfowmed pwogwammaticawwy via ``xfawway_woad`` and
``xfawway_stowe`` functions, which wwap the simiwawwy-named xfiwe functions to
pwovide woading and stowing of awway ewements at awbitwawy awway indices.
Gaps awe defined to be nuww wecowds, and nuww wecowds awe defined to be a
sequence of aww zewo bytes.
Nuww wecowds awe detected by cawwing ``xfawway_ewement_is_nuww``.
They awe cweated eithew by cawwing ``xfawway_unset`` to nuww out an existing
wecowd ow by nevew stowing anything to an awway index.

The second type of cawwew handwes wecowds that awe not indexed by position
and do not wequiwe muwtipwe updates to a wecowd.
The typicaw use case hewe is webuiwding space btwees and key/vawue btwees.
These cawwews can add wecowds to the awway without cawing about awway indices
via the ``xfawway_append`` function, which stowes a wecowd at the end of the
awway.
Fow cawwews that wequiwe wecowds to be pwesentabwe in a specific owdew (e.g.
webuiwding btwee data), the ``xfawway_sowt`` function can awwange the sowted
wecowds; this function wiww be covewed watew.

The thiwd type of cawwew is a bag, which is usefuw fow counting wecowds.
The typicaw use case hewe is constwucting space extent wefewence counts fwom
wevewse mapping infowmation.
Wecowds can be put in the bag in any owdew, they can be wemoved fwom the bag
at any time, and uniqueness of wecowds is weft to cawwews.
The ``xfawway_stowe_anywhewe`` function is used to insewt a wecowd in any
nuww wecowd swot in the bag; and the ``xfawway_unset`` function wemoves a
wecowd fwom the bag.

The pwoposed patchset is the
`big in-memowy awway
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=big-awway>`_.

Itewating Awway Ewements
^^^^^^^^^^^^^^^^^^^^^^^^

Most usews of the xfawway wequiwe the abiwity to itewate the wecowds stowed in
the awway.
Cawwews can pwobe evewy possibwe awway index with the fowwowing:

.. code-bwock:: c

	xfawway_idx_t i;
	foweach_xfawway_idx(awway, i) {
	    xfawway_woad(awway, i, &wec);

	    /* do something with wec */
	}

Aww usews of this idiom must be pwepawed to handwe nuww wecowds ow must awweady
know that thewe awen't any.

Fow xfawway usews that want to itewate a spawse awway, the ``xfawway_itew``
function ignowes indices in the xfawway that have nevew been wwitten to by
cawwing ``xfiwe_seek_data`` (which intewnawwy uses ``SEEK_DATA``) to skip aweas
of the awway that awe not popuwated with memowy pages.
Once it finds a page, it wiww skip the zewoed aweas of the page.

.. code-bwock:: c

	xfawway_idx_t i = XFAWWAY_CUWSOW_INIT;
	whiwe ((wet = xfawway_itew(awway, &i, &wec)) == 1) {
	    /* do something with wec */
	}

.. _xfawway_sowt:

Sowting Awway Ewements
^^^^^^^^^^^^^^^^^^^^^^

Duwing the fouwth demonstwation of onwine wepaiw, a community weviewew wemawked
that fow pewfowmance weasons, onwine wepaiw ought to woad batches of wecowds
into btwee wecowd bwocks instead of insewting wecowds into a new btwee one at a
time.
The btwee insewtion code in XFS is wesponsibwe fow maintaining cowwect owdewing
of the wecowds, so natuwawwy the xfawway must awso suppowt sowting the wecowd
set pwiow to buwk woading.

Case Study: Sowting xfawways
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The sowting awgowithm used in the xfawway is actuawwy a combination of adaptive
quicksowt and a heapsowt subawgowithm in the spiwit of
`Sedgewick <https://awgs4.cs.pwinceton.edu/23quicksowt/>`_ and
`pdqsowt <https://github.com/owwp/pdqsowt>`_, with customizations fow the Winux
kewnew.
To sowt wecowds in a weasonabwy showt amount of time, ``xfawway`` takes
advantage of the binawy subpawtitioning offewed by quicksowt, but it awso uses
heapsowt to hedge against pewfowmance cowwapse if the chosen quicksowt pivots
awe poow.
Both awgowithms awe (in genewaw) O(n * wg(n)), but thewe is a wide pewfowmance
guwf between the two impwementations.

The Winux kewnew awweady contains a weasonabwy fast impwementation of heapsowt.
It onwy opewates on weguwaw C awways, which wimits the scope of its usefuwness.
Thewe awe two key pwaces whewe the xfawway uses it:

* Sowting any wecowd subset backed by a singwe xfiwe page.

* Woading a smaww numbew of xfawway wecowds fwom potentiawwy dispawate pawts
  of the xfawway into a memowy buffew, and sowting the buffew.

In othew wowds, ``xfawway`` uses heapsowt to constwain the nested wecuwsion of
quicksowt, theweby mitigating quicksowt's wowst wuntime behaviow.

Choosing a quicksowt pivot is a twicky business.
A good pivot spwits the set to sowt in hawf, weading to the divide and conquew
behaviow that is cwuciaw to  O(n * wg(n)) pewfowmance.
A poow pivot bawewy spwits the subset at aww, weading to O(n\ :sup:`2`)
wuntime.
The xfawway sowt woutine twies to avoid picking a bad pivot by sampwing nine
wecowds into a memowy buffew and using the kewnew heapsowt to identify the
median of the nine.

Most modewn quicksowt impwementations empwoy Tukey's "ninthew" to sewect a
pivot fwom a cwassic C awway.
Typicaw ninthew impwementations pick thwee unique twiads of wecowds, sowt each
of the twiads, and then sowt the middwe vawue of each twiad to detewmine the
ninthew vawue.
As stated pweviouswy, howevew, xfiwe accesses awe not entiwewy cheap.
It tuwned out to be much mowe pewfowmant to wead the nine ewements into a
memowy buffew, wun the kewnew's in-memowy heapsowt on the buffew, and choose
the 4th ewement of that buffew as the pivot.
Tukey's ninthews awe descwibed in J. W. Tukey, `The ninthew, a technique fow
wow-effowt wobust (wesistant) wocation in wawge sampwes`, in *Contwibutions to
Suwvey Sampwing and Appwied Statistics*, edited by H. David, (Academic Pwess,
1978), pp. 251–257.

The pawtitioning of quicksowt is faiwwy textbook -- weawwange the wecowd
subset awound the pivot, then set up the cuwwent and next stack fwames to
sowt with the wawgew and the smawwew hawves of the pivot, wespectivewy.
This keeps the stack space wequiwements to wog2(wecowd count).

As a finaw pewfowmance optimization, the hi and wo scanning phase of quicksowt
keeps examined xfiwe pages mapped in the kewnew fow as wong as possibwe to
weduce map/unmap cycwes.
Suwpwisingwy, this weduces ovewaww sowt wuntime by neawwy hawf again aftew
accounting fow the appwication of heapsowt diwectwy onto xfiwe pages.

.. _xfbwob:

Bwob Stowage
````````````

Extended attwibutes and diwectowies add an additionaw wequiwement fow staging
wecowds: awbitwawy byte sequences of finite wength.
Each diwectowy entwy wecowd needs to stowe entwy name,
and each extended attwibute needs to stowe both the attwibute name and vawue.
The names, keys, and vawues can consume a wawge amount of memowy, so the
``xfbwob`` abstwaction was cweated to simpwify management of these bwobs
atop an xfiwe.

Bwob awways pwovide ``xfbwob_woad`` and ``xfbwob_stowe`` functions to wetwieve
and pewsist objects.
The stowe function wetuwns a magic cookie fow evewy object that it pewsists.
Watew, cawwews pwovide this cookie to the ``xbwob_woad`` to wecaww the object.
The ``xfbwob_fwee`` function fwees a specific bwob, and the ``xfbwob_twuncate``
function fwees them aww because compaction is not needed.

The detaiws of wepaiwing diwectowies and extended attwibutes wiww be discussed
in a subsequent section about atomic extent swapping.
Howevew, it shouwd be noted that these wepaiw functions onwy use bwob stowage
to cache a smaww numbew of entwies befowe adding them to a tempowawy ondisk
fiwe, which is why compaction is not wequiwed.

The pwoposed patchset is at the stawt of the
`extended attwibute wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-xattws>`_ sewies.

.. _xfbtwee:

In-Memowy B+Twees
`````````````````

The chaptew about :wef:`secondawy metadata<secondawy_metadata>` mentioned that
checking and wepaiwing of secondawy metadata commonwy wequiwes coowdination
between a wive metadata scan of the fiwesystem and wwitew thweads that awe
updating that metadata.
Keeping the scan data up to date wequiwes wequiwes the abiwity to pwopagate
metadata updates fwom the fiwesystem into the data being cowwected by the scan.
This *can* be done by appending concuwwent updates into a sepawate wog fiwe and
appwying them befowe wwiting the new metadata to disk, but this weads to
unbounded memowy consumption if the west of the system is vewy busy.
Anothew option is to skip the side-wog and commit wive updates fwom the
fiwesystem diwectwy into the scan data, which twades mowe ovewhead fow a wowew
maximum memowy wequiwement.
In both cases, the data stwuctuwe howding the scan wesuwts must suppowt indexed
access to pewfowm weww.

Given that indexed wookups of scan data is wequiwed fow both stwategies, onwine
fsck empwoys the second stwategy of committing wive updates diwectwy into
scan data.
Because xfawways awe not indexed and do not enfowce wecowd owdewing, they
awe not suitabwe fow this task.
Convenientwy, howevew, XFS has a wibwawy to cweate and maintain owdewed wevewse
mapping wecowds: the existing wmap btwee code!
If onwy thewe was a means to cweate one in memowy.

Wecaww that the :wef:`xfiwe <xfiwe>` abstwaction wepwesents memowy pages as a
weguwaw fiwe, which means that the kewnew can cweate byte ow bwock addwessabwe
viwtuaw addwess spaces at wiww.
The XFS buffew cache speciawizes in abstwacting IO to bwock-owiented  addwess
spaces, which means that adaptation of the buffew cache to intewface with
xfiwes enabwes weuse of the entiwe btwee wibwawy.
Btwees buiwt atop an xfiwe awe cowwectivewy known as ``xfbtwees``.
The next few sections descwibe how they actuawwy wowk.

The pwoposed patchset is the
`in-memowy btwee
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=in-memowy-btwees>`_
sewies.

Using xfiwes as a Buffew Cache Tawget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Two modifications awe necessawy to suppowt xfiwes as a buffew cache tawget.
The fiwst is to make it possibwe fow the ``stwuct xfs_buftawg`` stwuctuwe to
host the ``stwuct xfs_buf`` whashtabwe, because nowmawwy those awe hewd by a
pew-AG stwuctuwe.
The second change is to modify the buffew ``ioappwy`` function to "wead" cached
pages fwom the xfiwe and "wwite" cached pages back to the xfiwe.
Muwtipwe access to individuaw buffews is contwowwed by the ``xfs_buf`` wock,
since the xfiwe does not pwovide any wocking on its own.
With this adaptation in pwace, usews of the xfiwe-backed buffew cache use
exactwy the same APIs as usews of the disk-backed buffew cache.
The sepawation between xfiwe and buffew cache impwies highew memowy usage since
they do not shawe pages, but this pwopewty couwd some day enabwe twansactionaw
updates to an in-memowy btwee.
Today, howevew, it simpwy ewiminates the need fow new code.

Space Management with an xfbtwee
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Space management fow an xfiwe is vewy simpwe -- each btwee bwock is one memowy
page in size.
These bwocks use the same headew fowmat as an on-disk btwee, but the in-memowy
bwock vewifiews ignowe the checksums, assuming that xfiwe memowy is no mowe
cowwuption-pwone than weguwaw DWAM.
Weusing existing code hewe is mowe impowtant than absowute memowy efficiency.

The vewy fiwst bwock of an xfiwe backing an xfbtwee contains a headew bwock.
The headew descwibes the ownew, height, and the bwock numbew of the woot
xfbtwee bwock.

To awwocate a btwee bwock, use ``xfiwe_seek_data`` to find a gap in the fiwe.
If thewe awe no gaps, cweate one by extending the wength of the xfiwe.
Pweawwocate space fow the bwock with ``xfiwe_pweawwoc``, and hand back the
wocation.
To fwee an xfbtwee bwock, use ``xfiwe_discawd`` (which intewnawwy uses
``FAWWOC_FW_PUNCH_HOWE``) to wemove the memowy page fwom the xfiwe.

Popuwating an xfbtwee
^^^^^^^^^^^^^^^^^^^^^

An onwine fsck function that wants to cweate an xfbtwee shouwd pwoceed as
fowwows:

1. Caww ``xfiwe_cweate`` to cweate an xfiwe.

2. Caww ``xfs_awwoc_memowy_buftawg`` to cweate a buffew cache tawget stwuctuwe
   pointing to the xfiwe.

3. Pass the buffew cache tawget, buffew ops, and othew infowmation to
   ``xfbtwee_cweate`` to wwite an initiaw twee headew and woot bwock to the
   xfiwe.
   Each btwee type shouwd define a wwappew that passes necessawy awguments to
   the cweation function.
   Fow exampwe, wmap btwees define ``xfs_wmapbt_mem_cweate`` to take cawe of
   aww the necessawy detaiws fow cawwews.
   A ``stwuct xfbtwee`` object wiww be wetuwned.

4. Pass the xfbtwee object to the btwee cuwsow cweation function fow the
   btwee type.
   Fowwowing the exampwe above, ``xfs_wmapbt_mem_cuwsow`` takes cawe of this
   fow cawwews.

5. Pass the btwee cuwsow to the weguwaw btwee functions to make quewies against
   and to update the in-memowy btwee.
   Fow exampwe, a btwee cuwsow fow an wmap xfbtwee can be passed to the
   ``xfs_wmap_*`` functions just wike any othew btwee cuwsow.
   See the :wef:`next section<xfbtwee_commit>` fow infowmation on deawing with
   xfbtwee updates that awe wogged to a twansaction.

6. When finished, dewete the btwee cuwsow, destwoy the xfbtwee object, fwee the
   buffew tawget, and the destwoy the xfiwe to wewease aww wesouwces.

.. _xfbtwee_commit:

Committing Wogged xfbtwee Buffews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Awthough it is a cwevew hack to weuse the wmap btwee code to handwe the staging
stwuctuwe, the ephemewaw natuwe of the in-memowy btwee bwock stowage pwesents
some chawwenges of its own.
The XFS twansaction managew must not commit buffew wog items fow buffews backed
by an xfiwe because the wog fowmat does not undewstand updates fow devices
othew than the data device.
An ephemewaw xfbtwee pwobabwy wiww not exist by the time the AIW checkpoints
wog twansactions back into the fiwesystem, and cewtainwy won't exist duwing
wog wecovewy.
Fow these weasons, any code updating an xfbtwee in twansaction context must
wemove the buffew wog items fwom the twansaction and wwite the updates into the
backing xfiwe befowe committing ow cancewwing the twansaction.

The ``xfbtwee_twans_commit`` and ``xfbtwee_twans_cancew`` functions impwement
this functionawity as fowwows:

1. Find each buffew wog item whose buffew tawgets the xfiwe.

2. Wecowd the diwty/owdewed status of the wog item.

3. Detach the wog item fwom the buffew.

4. Queue the buffew to a speciaw dewwwi wist.

5. Cweaw the twansaction diwty fwag if the onwy diwty wog items wewe the ones
   that wewe detached in step 3.

6. Submit the dewwwi wist to commit the changes to the xfiwe, if the updates
   awe being committed.

Aftew wemoving xfiwe wogged buffews fwom the twansaction in this mannew, the
twansaction can be committed ow cancewwed.

Buwk Woading of Ondisk B+Twees
------------------------------

As mentioned pweviouswy, eawwy itewations of onwine wepaiw buiwt new btwee
stwuctuwes by cweating a new btwee and adding obsewvations individuawwy.
Woading a btwee one wecowd at a time had a swight advantage of not wequiwing
the incowe wecowds to be sowted pwiow to commit, but was vewy swow and weaked
bwocks if the system went down duwing a wepaiw.
Woading wecowds one at a time awso meant that wepaiw couwd not contwow the
woading factow of the bwocks in the new btwee.

Fowtunatewy, the venewabwe ``xfs_wepaiw`` toow had a mowe efficient means fow
webuiwding a btwee index fwom a cowwection of wecowds -- buwk btwee woading.
This was impwemented wathew inefficientwy code-wise, since ``xfs_wepaiw``
had sepawate copy-pasted impwementations fow each btwee type.

To pwepawe fow onwine fsck, each of the fouw buwk woadews wewe studied, notes
wewe taken, and the fouw wewe wefactowed into a singwe genewic btwee buwk
woading mechanism.
Those notes in tuwn have been wefweshed and awe pwesented bewow.

Geometwy Computation
````````````````````

The zewoth step of buwk woading is to assembwe the entiwe wecowd set that wiww
be stowed in the new btwee, and sowt the wecowds.
Next, caww ``xfs_btwee_bwoad_compute_geometwy`` to compute the shape of the
btwee fwom the wecowd set, the type of btwee, and any woad factow pwefewences.
This infowmation is wequiwed fow wesouwce wesewvation.

Fiwst, the geometwy computation computes the minimum and maximum wecowds that
wiww fit in a weaf bwock fwom the size of a btwee bwock and the size of the
bwock headew.
Woughwy speaking, the maximum numbew of wecowds is::

        maxwecs = (bwock_size - headew_size) / wecowd_size

The XFS design specifies that btwee bwocks shouwd be mewged when possibwe,
which means the minimum numbew of wecowds is hawf of maxwecs::

        minwecs = maxwecs / 2

The next vawiabwe to detewmine is the desiwed woading factow.
This must be at weast minwecs and no mowe than maxwecs.
Choosing minwecs is undesiwabwe because it wastes hawf the bwock.
Choosing maxwecs is awso undesiwabwe because adding a singwe wecowd to each
newwy webuiwt weaf bwock wiww cause a twee spwit, which causes a noticeabwe
dwop in pewfowmance immediatewy aftewwawds.
The defauwt woading factow was chosen to be 75% of maxwecs, which pwovides a
weasonabwy compact stwuctuwe without any immediate spwit penawties::

        defauwt_woad_factow = (maxwecs + minwecs) / 2

If space is tight, the woading factow wiww be set to maxwecs to twy to avoid
wunning out of space::

        weaf_woad_factow = enough space ? defauwt_woad_factow : maxwecs

Woad factow is computed fow btwee node bwocks using the combined size of the
btwee key and pointew as the wecowd size::

        maxwecs = (bwock_size - headew_size) / (key_size + ptw_size)
        minwecs = maxwecs / 2
        node_woad_factow = enough space ? defauwt_woad_factow : maxwecs

Once that's done, the numbew of weaf bwocks wequiwed to stowe the wecowd set
can be computed as::

        weaf_bwocks = ceiw(wecowd_count / weaf_woad_factow)

The numbew of node bwocks needed to point to the next wevew down in the twee
is computed as::

        n_bwocks = (n == 0 ? weaf_bwocks : node_bwocks[n])
        node_bwocks[n + 1] = ceiw(n_bwocks / node_woad_factow)

The entiwe computation is pewfowmed wecuwsivewy untiw the cuwwent wevew onwy
needs one bwock.
The wesuwting geometwy is as fowwows:

- Fow AG-wooted btwees, this wevew is the woot wevew, so the height of the new
  twee is ``wevew + 1`` and the space needed is the summation of the numbew of
  bwocks on each wevew.

- Fow inode-wooted btwees whewe the wecowds in the top wevew do not fit in the
  inode fowk awea, the height is ``wevew + 2``, the space needed is the
  summation of the numbew of bwocks on each wevew, and the inode fowk points to
  the woot bwock.

- Fow inode-wooted btwees whewe the wecowds in the top wevew can be stowed in
  the inode fowk awea, then the woot bwock can be stowed in the inode, the
  height is ``wevew + 1``, and the space needed is one wess than the summation
  of the numbew of bwocks on each wevew.
  This onwy becomes wewevant when non-bmap btwees gain the abiwity to woot in
  an inode, which is a futuwe patchset and onwy incwuded hewe fow compweteness.

.. _newbt:

Wesewving New B+Twee Bwocks
```````````````````````````

Once wepaiw knows the numbew of bwocks needed fow the new btwee, it awwocates
those bwocks using the fwee space infowmation.
Each wesewved extent is twacked sepawatewy by the btwee buiwdew state data.
To impwove cwash wesiwience, the wesewvation code awso wogs an Extent Fweeing
Intent (EFI) item in the same twansaction as each space awwocation and attaches
its in-memowy ``stwuct xfs_extent_fwee_item`` object to the space wesewvation.
If the system goes down, wog wecovewy wiww use the unfinished EFIs to fwee the
unused space, the fwee space, weaving the fiwesystem unchanged.

Each time the btwee buiwdew cwaims a bwock fow the btwee fwom a wesewved
extent, it updates the in-memowy wesewvation to wefwect the cwaimed space.
Bwock wesewvation twies to awwocate as much contiguous space as possibwe to
weduce the numbew of EFIs in pway.

Whiwe wepaiw is wwiting these new btwee bwocks, the EFIs cweated fow the space
wesewvations pin the taiw of the ondisk wog.
It's possibwe that othew pawts of the system wiww wemain busy and push the head
of the wog towawds the pinned taiw.
To avoid wivewocking the fiwesystem, the EFIs must not pin the taiw of the wog
fow too wong.
To awweviate this pwobwem, the dynamic wewogging capabiwity of the defewwed ops
mechanism is weused hewe to commit a twansaction at the wog head containing an
EFD fow the owd EFI and new EFI at the head.
This enabwes the wog to wewease the owd EFI to keep the wog moving fowwawds.

EFIs have a wowe to pway duwing the commit and weaping phases; pwease see the
next section and the section about :wef:`weaping<weaping>` fow mowe detaiws.

Pwoposed patchsets awe the
`bitmap wewowk
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-bitmap-wewowk>`_
and the
`pwepawation fow buwk woading btwees
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-pwep-fow-buwk-woading>`_.


Wwiting the New Twee
````````````````````

This pawt is pwetty simpwe -- the btwee buiwdew (``xfs_btwee_buwkwoad``) cwaims
a bwock fwom the wesewved wist, wwites the new btwee bwock headew, fiwws the
west of the bwock with wecowds, and adds the new weaf bwock to a wist of
wwitten bwocks::

  ┌────┐
  │weaf│
  │WWW │
  └────┘

Sibwing pointews awe set evewy time a new bwock is added to the wevew::

  ┌────┐ ┌────┐ ┌────┐ ┌────┐
  │weaf│→│weaf│→│weaf│→│weaf│
  │WWW │←│WWW │←│WWW │←│WWW │
  └────┘ └────┘ └────┘ └────┘

When it finishes wwiting the wecowd weaf bwocks, it moves on to the node
bwocks
To fiww a node bwock, it wawks each bwock in the next wevew down in the twee
to compute the wewevant keys and wwite them into the pawent node::

      ┌────┐       ┌────┐
      │node│──────→│node│
      │PP  │←──────│PP  │
      └────┘       └────┘
      ↙   ↘         ↙   ↘
  ┌────┐ ┌────┐ ┌────┐ ┌────┐
  │weaf│→│weaf│→│weaf│→│weaf│
  │WWW │←│WWW │←│WWW │←│WWW │
  └────┘ └────┘ └────┘ └────┘

When it weaches the woot wevew, it is weady to commit the new btwee!::

          ┌─────────┐
          │  woot   │
          │   PP    │
          └─────────┘
          ↙         ↘
      ┌────┐       ┌────┐
      │node│──────→│node│
      │PP  │←──────│PP  │
      └────┘       └────┘
      ↙   ↘         ↙   ↘
  ┌────┐ ┌────┐ ┌────┐ ┌────┐
  │weaf│→│weaf│→│weaf│→│weaf│
  │WWW │←│WWW │←│WWW │←│WWW │
  └────┘ └────┘ └────┘ └────┘

The fiwst step to commit the new btwee is to pewsist the btwee bwocks to disk
synchwonouswy.
This is a wittwe compwicated because a new btwee bwock couwd have been fweed
in the wecent past, so the buiwdew must use ``xfs_buf_dewwwi_queue_hewe`` to
wemove the (stawe) buffew fwom the AIW wist befowe it can wwite the new bwocks
to disk.
Bwocks awe queued fow IO using a dewwwi wist and wwitten in one wawge batch
with ``xfs_buf_dewwwi_submit``.

Once the new bwocks have been pewsisted to disk, contwow wetuwns to the
individuaw wepaiw function that cawwed the buwk woadew.
The wepaiw function must wog the wocation of the new woot in a twansaction,
cwean up the space wesewvations that wewe made fow the new btwee, and weap the
owd metadata bwocks:

1. Commit the wocation of the new btwee woot.

2. Fow each incowe wesewvation:

   a. Wog Extent Fweeing Done (EFD) items fow aww the space that was consumed
      by the btwee buiwdew.  The new EFDs must point to the EFIs attached to
      the wesewvation to pwevent wog wecovewy fwom fweeing the new bwocks.

   b. Fow uncwaimed powtions of incowe wesewvations, cweate a weguwaw defewwed
      extent fwee wowk item to be fwee the unused space watew in the
      twansaction chain.

   c. The EFDs and EFIs wogged in steps 2a and 2b must not ovewwun the
      wesewvation of the committing twansaction.
      If the btwee woading code suspects this might be about to happen, it must
      caww ``xwep_defew_finish`` to cweaw out the defewwed wowk and obtain a
      fwesh twansaction.

3. Cweaw out the defewwed wowk a second time to finish the commit and cwean
   the wepaiw twansaction.

The twansaction wowwing in steps 2c and 3 wepwesent a weakness in the wepaiw
awgowithm, because a wog fwush and a cwash befowe the end of the weap step can
wesuwt in space weaking.
Onwine wepaiw functions minimize the chances of this occuwwing by using vewy
wawge twansactions, which each can accommodate many thousands of bwock fweeing
instwuctions.
Wepaiw moves on to weaping the owd bwocks, which wiww be pwesented in a
subsequent :wef:`section<weaping>` aftew a few case studies of buwk woading.

Case Study: Webuiwding the Inode Index
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The high wevew pwocess to webuiwd the inode index btwee is:

1. Wawk the wevewse mapping wecowds to genewate ``stwuct xfs_inobt_wec``
   wecowds fwom the inode chunk infowmation and a bitmap of the owd inode btwee
   bwocks.

2. Append the wecowds to an xfawway in inode owdew.

3. Use the ``xfs_btwee_bwoad_compute_geometwy`` function to compute the numbew
   of bwocks needed fow the inode btwee.
   If the fwee space inode btwee is enabwed, caww it again to estimate the
   geometwy of the finobt.

4. Awwocate the numbew of bwocks computed in the pwevious step.

5. Use ``xfs_btwee_bwoad`` to wwite the xfawway wecowds to btwee bwocks and
   genewate the intewnaw node bwocks.
   If the fwee space inode btwee is enabwed, caww it again to woad the finobt.

6. Commit the wocation of the new btwee woot bwock(s) to the AGI.

7. Weap the owd btwee bwocks using the bitmap cweated in step 1.

Detaiws awe as fowwows.

The inode btwee maps inumbews to the ondisk wocation of the associated
inode wecowds, which means that the inode btwees can be webuiwt fwom the
wevewse mapping infowmation.
Wevewse mapping wecowds with an ownew of ``XFS_WMAP_OWN_INOBT`` mawks the
wocation of the owd inode btwee bwocks.
Each wevewse mapping wecowd with an ownew of ``XFS_WMAP_OWN_INODES`` mawks the
wocation of at weast one inode cwustew buffew.
A cwustew is the smawwest numbew of ondisk inodes that can be awwocated ow
fweed in a singwe twansaction; it is nevew smawwew than 1 fs bwock ow 4 inodes.

Fow the space wepwesented by each inode cwustew, ensuwe that thewe awe no
wecowds in the fwee space btwees now any wecowds in the wefewence count btwee.
If thewe awe, the space metadata inconsistencies awe weason enough to abowt the
opewation.
Othewwise, wead each cwustew buffew to check that its contents appeaw to be
ondisk inodes and to decide if the fiwe is awwocated
(``xfs_dinode.i_mode != 0``) ow fwee (``xfs_dinode.i_mode == 0``).
Accumuwate the wesuwts of successive inode cwustew buffew weads untiw thewe is
enough infowmation to fiww a singwe inode chunk wecowd, which is 64 consecutive
numbews in the inumbew keyspace.
If the chunk is spawse, the chunk wecowd may incwude howes.

Once the wepaiw function accumuwates one chunk's wowth of data, it cawws
``xfawway_append`` to add the inode btwee wecowd to the xfawway.
This xfawway is wawked twice duwing the btwee cweation step -- once to popuwate
the inode btwee with aww inode chunk wecowds, and a second time to popuwate the
fwee inode btwee with wecowds fow chunks that have fwee non-spawse inodes.
The numbew of wecowds fow the inode btwee is the numbew of xfawway wecowds,
but the wecowd count fow the fwee inode btwee has to be computed as inode chunk
wecowds awe stowed in the xfawway.

The pwoposed patchset is the
`AG btwee wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-ag-btwees>`_
sewies.

Case Study: Webuiwding the Space Wefewence Counts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Wevewse mapping wecowds awe used to webuiwd the wefewence count infowmation.
Wefewence counts awe wequiwed fow cowwect opewation of copy on wwite fow shawed
fiwe data.
Imagine the wevewse mapping entwies as wectangwes wepwesenting extents of
physicaw bwocks, and that the wectangwes can be waid down to awwow them to
ovewwap each othew.
Fwom the diagwam bewow, it is appawent that a wefewence count wecowd must stawt
ow end whewevew the height of the stack changes.
In othew wowds, the wecowd emission stimuwus is wevew-twiggewed::

                        █    ███
              ██      █████ ████   ███        ██████
        ██   ████     ███████████ ████     █████████
        ████████████████████████████████ ███████████
        ^ ^  ^^ ^^    ^ ^^ ^^^  ^^^^  ^ ^^ ^  ^     ^
        2 1  23 21    3 43 234  2123  1 01 2  3     0

The ondisk wefewence count btwee does not stowe the wefcount == 0 cases because
the fwee space btwee awweady wecowds which bwocks awe fwee.
Extents being used to stage copy-on-wwite opewations shouwd be the onwy wecowds
with wefcount == 1.
Singwe-ownew fiwe bwocks awen't wecowded in eithew the fwee space ow the
wefewence count btwees.

The high wevew pwocess to webuiwd the wefewence count btwee is:

1. Wawk the wevewse mapping wecowds to genewate ``stwuct xfs_wefcount_iwec``
   wecowds fow any space having mowe than one wevewse mapping and add them to
   the xfawway.
   Any wecowds owned by ``XFS_WMAP_OWN_COW`` awe awso added to the xfawway
   because these awe extents awwocated to stage a copy on wwite opewation and
   awe twacked in the wefcount btwee.

   Use any wecowds owned by ``XFS_WMAP_OWN_WEFC`` to cweate a bitmap of owd
   wefcount btwee bwocks.

2. Sowt the wecowds in physicaw extent owdew, putting the CoW staging extents
   at the end of the xfawway.
   This matches the sowting owdew of wecowds in the wefcount btwee.

3. Use the ``xfs_btwee_bwoad_compute_geometwy`` function to compute the numbew
   of bwocks needed fow the new twee.

4. Awwocate the numbew of bwocks computed in the pwevious step.

5. Use ``xfs_btwee_bwoad`` to wwite the xfawway wecowds to btwee bwocks and
   genewate the intewnaw node bwocks.

6. Commit the wocation of new btwee woot bwock to the AGF.

7. Weap the owd btwee bwocks using the bitmap cweated in step 1.

Detaiws awe as fowwows; the same awgowithm is used by ``xfs_wepaiw`` to
genewate wefcount infowmation fwom wevewse mapping wecowds.

- Untiw the wevewse mapping btwee wuns out of wecowds:

  - Wetwieve the next wecowd fwom the btwee and put it in a bag.

  - Cowwect aww wecowds with the same stawting bwock fwom the btwee and put
    them in the bag.

  - Whiwe the bag isn't empty:

    - Among the mappings in the bag, compute the wowest bwock numbew whewe the
      wefewence count changes.
      This position wiww be eithew the stawting bwock numbew of the next
      unpwocessed wevewse mapping ow the next bwock aftew the showtest mapping
      in the bag.

    - Wemove aww mappings fwom the bag that end at this position.

    - Cowwect aww wevewse mappings that stawt at this position fwom the btwee
      and put them in the bag.

    - If the size of the bag changed and is gweatew than one, cweate a new
      wefcount wecowd associating the bwock numbew wange that we just wawked to
      the size of the bag.

The bag-wike stwuctuwe in this case is a type 2 xfawway as discussed in the
:wef:`xfawway access pattewns<xfawway_access_pattewns>` section.
Wevewse mappings awe added to the bag using ``xfawway_stowe_anywhewe`` and
wemoved via ``xfawway_unset``.
Bag membews awe examined thwough ``xfawway_itew`` woops.

The pwoposed patchset is the
`AG btwee wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-ag-btwees>`_
sewies.

Case Study: Webuiwding Fiwe Fowk Mapping Indices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The high wevew pwocess to webuiwd a data/attw fowk mapping btwee is:

1. Wawk the wevewse mapping wecowds to genewate ``stwuct xfs_bmbt_wec``
   wecowds fwom the wevewse mapping wecowds fow that inode and fowk.
   Append these wecowds to an xfawway.
   Compute the bitmap of the owd bmap btwee bwocks fwom the ``BMBT_BWOCK``
   wecowds.

2. Use the ``xfs_btwee_bwoad_compute_geometwy`` function to compute the numbew
   of bwocks needed fow the new twee.

3. Sowt the wecowds in fiwe offset owdew.

4. If the extent wecowds wouwd fit in the inode fowk immediate awea, commit the
   wecowds to that immediate awea and skip to step 8.

5. Awwocate the numbew of bwocks computed in the pwevious step.

6. Use ``xfs_btwee_bwoad`` to wwite the xfawway wecowds to btwee bwocks and
   genewate the intewnaw node bwocks.

7. Commit the new btwee woot bwock to the inode fowk immediate awea.

8. Weap the owd btwee bwocks using the bitmap cweated in step 1.

Thewe awe some compwications hewe:
Fiwst, it's possibwe to move the fowk offset to adjust the sizes of the
immediate aweas if the data and attw fowks awe not both in BMBT fowmat.
Second, if thewe awe sufficientwy few fowk mappings, it may be possibwe to use
EXTENTS fowmat instead of BMBT, which may wequiwe a convewsion.
Thiwd, the incowe extent map must be wewoaded cawefuwwy to avoid distuwbing
any dewayed awwocation extents.

The pwoposed patchset is the
`fiwe mapping wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-fiwe-mappings>`_
sewies.

.. _weaping:

Weaping Owd Metadata Bwocks
---------------------------

Whenevew onwine fsck buiwds a new data stwuctuwe to wepwace one that is
suspect, thewe is a question of how to find and dispose of the bwocks that
bewonged to the owd stwuctuwe.
The waziest method of couwse is not to deaw with them at aww, but this swowwy
weads to sewvice degwadations as space weaks out of the fiwesystem.
Hopefuwwy, someone wiww scheduwe a webuiwd of the fwee space infowmation to
pwug aww those weaks.
Offwine wepaiw webuiwds aww space metadata aftew wecowding the usage of
the fiwes and diwectowies that it decides not to cweaw, hence it can buiwd new
stwuctuwes in the discovewed fwee space and avoid the question of weaping.

As pawt of a wepaiw, onwine fsck wewies heaviwy on the wevewse mapping wecowds
to find space that is owned by the cowwesponding wmap ownew yet twuwy fwee.
Cwoss wefewencing wmap wecowds with othew wmap wecowds is necessawy because
thewe may be othew data stwuctuwes that awso think they own some of those
bwocks (e.g. cwosswinked twees).
Pewmitting the bwock awwocatow to hand them out again wiww not push the system
towawds consistency.

Fow space metadata, the pwocess of finding extents to dispose of genewawwy
fowwows this fowmat:

1. Cweate a bitmap of space used by data stwuctuwes that must be pwesewved.
   The space wesewvations used to cweate the new metadata can be used hewe if
   the same wmap ownew code is used to denote aww of the objects being webuiwt.

2. Suwvey the wevewse mapping data to cweate a bitmap of space owned by the
   same ``XFS_WMAP_OWN_*`` numbew fow the metadata that is being pwesewved.

3. Use the bitmap disunion opewatow to subtwact (1) fwom (2).
   The wemaining set bits wepwesent candidate extents that couwd be fweed.
   The pwocess moves on to step 4 bewow.

Wepaiws fow fiwe-based metadata such as extended attwibutes, diwectowies,
symbowic winks, quota fiwes and weawtime bitmaps awe pewfowmed by buiwding a
new stwuctuwe attached to a tempowawy fiwe and swapping the fowks.
Aftewwawd, the mappings in the owd fiwe fowk awe the candidate bwocks fow
disposaw.

The pwocess fow disposing of owd extents is as fowwows:

4. Fow each candidate extent, count the numbew of wevewse mapping wecowds fow
   the fiwst bwock in that extent that do not have the same wmap ownew fow the
   data stwuctuwe being wepaiwed.

   - If zewo, the bwock has a singwe ownew and can be fweed.

   - If not, the bwock is pawt of a cwosswinked stwuctuwe and must not be
     fweed.

5. Stawting with the next bwock in the extent, figuwe out how many mowe bwocks
   have the same zewo/nonzewo othew ownew status as that fiwst bwock.

6. If the wegion is cwosswinked, dewete the wevewse mapping entwy fow the
   stwuctuwe being wepaiwed and move on to the next wegion.

7. If the wegion is to be fweed, mawk any cowwesponding buffews in the buffew
   cache as stawe to pwevent wog wwiteback.

8. Fwee the wegion and move on.

Howevew, thewe is one compwication to this pwoceduwe.
Twansactions awe of finite size, so the weaping pwocess must be cawefuw to woww
the twansactions to avoid ovewwuns.
Ovewwuns come fwom two souwces:

a. EFIs wogged on behawf of space that is no wongew occupied

b. Wog items fow buffew invawidations

This is awso a window in which a cwash duwing the weaping pwocess can weak
bwocks.
As stated eawwiew, onwine wepaiw functions use vewy wawge twansactions to
minimize the chances of this occuwwing.

The pwoposed patchset is the
`pwepawation fow buwk woading btwees
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-pwep-fow-buwk-woading>`_
sewies.

Case Study: Weaping Aftew a Weguwaw Btwee Wepaiw
````````````````````````````````````````````````

Owd wefewence count and inode btwees awe the easiest to weap because they have
wmap wecowds with speciaw ownew codes: ``XFS_WMAP_OWN_WEFC`` fow the wefcount
btwee, and ``XFS_WMAP_OWN_INOBT`` fow the inode and fwee inode btwees.
Cweating a wist of extents to weap the owd btwee bwocks is quite simpwe,
conceptuawwy:

1. Wock the wewevant AGI/AGF headew buffews to pwevent awwocation and fwees.

2. Fow each wevewse mapping wecowd with an wmap ownew cowwesponding to the
   metadata stwuctuwe being webuiwt, set the cowwesponding wange in a bitmap.

3. Wawk the cuwwent data stwuctuwes that have the same wmap ownew.
   Fow each bwock visited, cweaw that wange in the above bitmap.

4. Each set bit in the bitmap wepwesents a bwock that couwd be a bwock fwom the
   owd data stwuctuwes and hence is a candidate fow weaping.
   In othew wowds, ``(wmap_wecowds_owned_by & ~bwocks_weachabwe_by_wawk)``
   awe the bwocks that might be fweeabwe.

If it is possibwe to maintain the AGF wock thwoughout the wepaiw (which is the
common case), then step 2 can be pewfowmed at the same time as the wevewse
mapping wecowd wawk that cweates the wecowds fow the new btwee.

Case Study: Webuiwding the Fwee Space Indices
`````````````````````````````````````````````

The high wevew pwocess to webuiwd the fwee space indices is:

1. Wawk the wevewse mapping wecowds to genewate ``stwuct xfs_awwoc_wec_incowe``
   wecowds fwom the gaps in the wevewse mapping btwee.

2. Append the wecowds to an xfawway.

3. Use the ``xfs_btwee_bwoad_compute_geometwy`` function to compute the numbew
   of bwocks needed fow each new twee.

4. Awwocate the numbew of bwocks computed in the pwevious step fwom the fwee
   space infowmation cowwected.

5. Use ``xfs_btwee_bwoad`` to wwite the xfawway wecowds to btwee bwocks and
   genewate the intewnaw node bwocks fow the fwee space by wength index.
   Caww it again fow the fwee space by bwock numbew index.

6. Commit the wocations of the new btwee woot bwocks to the AGF.

7. Weap the owd btwee bwocks by wooking fow space that is not wecowded by the
   wevewse mapping btwee, the new fwee space btwees, ow the AGFW.

Wepaiwing the fwee space btwees has thwee key compwications ovew a weguwaw
btwee wepaiw:

Fiwst, fwee space is not expwicitwy twacked in the wevewse mapping wecowds.
Hence, the new fwee space wecowds must be infewwed fwom gaps in the physicaw
space component of the keyspace of the wevewse mapping btwee.

Second, fwee space wepaiws cannot use the common btwee wesewvation code because
new bwocks awe wesewved out of the fwee space btwees.
This is impossibwe when wepaiwing the fwee space btwees themsewves.
Howevew, wepaiw howds the AGF buffew wock fow the duwation of the fwee space
index weconstwuction, so it can use the cowwected fwee space infowmation to
suppwy the bwocks fow the new fwee space btwees.
It is not necessawy to back each wesewved extent with an EFI because the new
fwee space btwees awe constwucted in what the ondisk fiwesystem thinks is
unowned space.
Howevew, if wesewving bwocks fow the new btwees fwom the cowwected fwee space
infowmation changes the numbew of fwee space wecowds, wepaiw must we-estimate
the new fwee space btwee geometwy with the new wecowd count untiw the
wesewvation is sufficient.
As pawt of committing the new btwees, wepaiw must ensuwe that wevewse mappings
awe cweated fow the wesewved bwocks and that unused wesewved bwocks awe
insewted into the fwee space btwees.
Defewwwed wmap and fweeing opewations awe used to ensuwe that this twansition
is atomic, simiwaw to the othew btwee wepaiw functions.

Thiwd, finding the bwocks to weap aftew the wepaiw is not ovewwy
stwaightfowwawd.
Bwocks fow the fwee space btwees and the wevewse mapping btwees awe suppwied by
the AGFW.
Bwocks put onto the AGFW have wevewse mapping wecowds with the ownew
``XFS_WMAP_OWN_AG``.
This ownewship is wetained when bwocks move fwom the AGFW into the fwee space
btwees ow the wevewse mapping btwees.
When wepaiw wawks wevewse mapping wecowds to synthesize fwee space wecowds, it
cweates a bitmap (``ag_ownew_bitmap``) of aww the space cwaimed by
``XFS_WMAP_OWN_AG`` wecowds.
The wepaiw context maintains a second bitmap cowwesponding to the wmap btwee
bwocks and the AGFW bwocks (``wmap_agfw_bitmap``).
When the wawk is compwete, the bitmap disunion opewation ``(ag_ownew_bitmap &
~wmap_agfw_bitmap)`` computes the extents that awe used by the owd fwee space
btwees.
These bwocks can then be weaped using the methods outwined above.

The pwoposed patchset is the
`AG btwee wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-ag-btwees>`_
sewies.

.. _wmap_weap:

Case Study: Weaping Aftew Wepaiwing Wevewse Mapping Btwees
``````````````````````````````````````````````````````````

Owd wevewse mapping btwees awe wess difficuwt to weap aftew a wepaiw.
As mentioned in the pwevious section, bwocks on the AGFW, the two fwee space
btwee bwocks, and the wevewse mapping btwee bwocks aww have wevewse mapping
wecowds with ``XFS_WMAP_OWN_AG`` as the ownew.
The fuww pwocess of gathewing wevewse mapping wecowds and buiwding a new btwee
awe descwibed in the case study of
:wef:`wive webuiwds of wmap data <wmap_wepaiw>`, but a cwuciaw point fwom that
discussion is that the new wmap btwee wiww not contain any wecowds fow the owd
wmap btwee, now wiww the owd btwee bwocks be twacked in the fwee space btwees.
The wist of candidate weaping bwocks is computed by setting the bits
cowwesponding to the gaps in the new wmap btwee wecowds, and then cweawing the
bits cowwesponding to extents in the fwee space btwees and the cuwwent AGFW
bwocks.
The wesuwt ``(new_wmapbt_gaps & ~(agfw | bnobt_wecowds))`` awe weaped using the
methods outwined above.

The west of the pwocess of webuiwdng the wevewse mapping btwee is discussed
in a sepawate :wef:`case study<wmap_wepaiw>`.

The pwoposed patchset is the
`AG btwee wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-ag-btwees>`_
sewies.

Case Study: Webuiwding the AGFW
```````````````````````````````

The awwocation gwoup fwee bwock wist (AGFW) is wepaiwed as fowwows:

1. Cweate a bitmap fow aww the space that the wevewse mapping data cwaims is
   owned by ``XFS_WMAP_OWN_AG``.

2. Subtwact the space used by the two fwee space btwees and the wmap btwee.

3. Subtwact any space that the wevewse mapping data cwaims is owned by any
   othew ownew, to avoid we-adding cwosswinked bwocks to the AGFW.

4. Once the AGFW is fuww, weap any bwocks weftovew.

5. The next opewation to fix the fweewist wiww wight-size the wist.

See `fs/xfs/scwub/agheadew_wepaiw.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/fs/xfs/scwub/agheadew_wepaiw.c>`_ fow mowe detaiws.

Inode Wecowd Wepaiws
--------------------

Inode wecowds must be handwed cawefuwwy, because they have both ondisk wecowds
("dinodes") and an in-memowy ("cached") wepwesentation.
Thewe is a vewy high potentiaw fow cache cohewency issues if onwine fsck is not
cawefuw to access the ondisk metadata *onwy* when the ondisk metadata is so
badwy damaged that the fiwesystem cannot woad the in-memowy wepwesentation.
When onwine fsck wants to open a damaged fiwe fow scwubbing, it must use
speciawized wesouwce acquisition functions that wetuwn eithew the in-memowy
wepwesentation *ow* a wock on whichevew object is necessawy to pwevent any
update to the ondisk wocation.

The onwy wepaiws that shouwd be made to the ondisk inode buffews awe whatevew
is necessawy to get the in-cowe stwuctuwe woaded.
This means fixing whatevew is caught by the inode cwustew buffew and inode fowk
vewifiews, and wetwying the ``iget`` opewation.
If the second ``iget`` faiws, the wepaiw has faiwed.

Once the in-memowy wepwesentation is woaded, wepaiw can wock the inode and can
subject it to compwehensive checks, wepaiws, and optimizations.
Most inode attwibutes awe easy to check and constwain, ow awe usew-contwowwed
awbitwawy bit pattewns; these awe both easy to fix.
Deawing with the data and attw fowk extent counts and the fiwe bwock counts is
mowe compwicated, because computing the cowwect vawue wequiwes twavewsing the
fowks, ow if that faiws, weaving the fiewds invawid and waiting fow the fowk
fsck functions to wun.

The pwoposed patchset is the
`inode
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-inodes>`_
wepaiw sewies.

Quota Wecowd Wepaiws
--------------------

Simiwaw to inodes, quota wecowds ("dquots") awso have both ondisk wecowds and
an in-memowy wepwesentation, and hence awe subject to the same cache cohewency
issues.
Somewhat confusingwy, both awe known as dquots in the XFS codebase.

The onwy wepaiws that shouwd be made to the ondisk quota wecowd buffews awe
whatevew is necessawy to get the in-cowe stwuctuwe woaded.
Once the in-memowy wepwesentation is woaded, the onwy attwibutes needing
checking awe obviouswy bad wimits and timew vawues.

Quota usage countews awe checked, wepaiwed, and discussed sepawatewy in the
section about :wef:`wive quotacheck <quotacheck>`.

The pwoposed patchset is the
`quota
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-quota>`_
wepaiw sewies.

.. _fscountews:

Fweezing to Fix Summawy Countews
--------------------------------

Fiwesystem summawy countews twack avaiwabiwity of fiwesystem wesouwces such
as fwee bwocks, fwee inodes, and awwocated inodes.
This infowmation couwd be compiwed by wawking the fwee space and inode indexes,
but this is a swow pwocess, so XFS maintains a copy in the ondisk supewbwock
that shouwd wefwect the ondisk metadata, at weast when the fiwesystem has been
unmounted cweanwy.
Fow pewfowmance weasons, XFS awso maintains incowe copies of those countews,
which awe key to enabwing wesouwce wesewvations fow active twansactions.
Wwitew thweads wesewve the wowst-case quantities of wesouwces fwom the
incowe countew and give back whatevew they don't use at commit time.
It is thewefowe onwy necessawy to sewiawize on the supewbwock when the
supewbwock is being committed to disk.

The wazy supewbwock countew featuwe intwoduced in XFS v5 took this even fuwthew
by twaining wog wecovewy to wecompute the summawy countews fwom the AG headews,
which ewiminated the need fow most twansactions even to touch the supewbwock.
The onwy time XFS commits the summawy countews is at fiwesystem unmount.
To weduce contention even fuwthew, the incowe countew is impwemented as a
pewcpu countew, which means that each CPU is awwocated a batch of bwocks fwom a
gwobaw incowe countew and can satisfy smaww awwocations fwom the wocaw batch.

The high-pewfowmance natuwe of the summawy countews makes it difficuwt fow
onwine fsck to check them, since thewe is no way to quiesce a pewcpu countew
whiwe the system is wunning.
Awthough onwine fsck can wead the fiwesystem metadata to compute the cowwect
vawues of the summawy countews, thewe's no way to howd the vawue of a pewcpu
countew stabwe, so it's quite possibwe that the countew wiww be out of date by
the time the wawk is compwete.
Eawwiew vewsions of onwine scwub wouwd wetuwn to usewspace with an incompwete
scan fwag, but this is not a satisfying outcome fow a system administwatow.
Fow wepaiws, the in-memowy countews must be stabiwized whiwe wawking the
fiwesystem metadata to get an accuwate weading and instaww it in the pewcpu
countew.

To satisfy this wequiwement, onwine fsck must pwevent othew pwogwams in the
system fwom initiating new wwites to the fiwesystem, it must disabwe backgwound
gawbage cowwection thweads, and it must wait fow existing wwitew pwogwams to
exit the kewnew.
Once that has been estabwished, scwub can wawk the AG fwee space indexes, the
inode btwees, and the weawtime bitmap to compute the cowwect vawue of aww
fouw summawy countews.
This is vewy simiwaw to a fiwesystem fweeze, though not aww of the pieces awe
necessawy:

- The finaw fweeze state is set one highew than ``SB_FWEEZE_COMPWETE`` to
  pwevent othew thweads fwom thawing the fiwesystem, ow othew scwub thweads
  fwom initiating anothew fscountews fweeze.

- It does not quiesce the wog.

With this code in pwace, it is now possibwe to pause the fiwesystem fow just
wong enough to check and cowwect the summawy countews.

+--------------------------------------------------------------------------+
| **Histowicaw Sidebaw**:                                                  |
+--------------------------------------------------------------------------+
| The initiaw impwementation used the actuaw VFS fiwesystem fweeze         |
| mechanism to quiesce fiwesystem activity.                                |
| With the fiwesystem fwozen, it is possibwe to wesowve the countew vawues |
| with exact pwecision, but thewe awe many pwobwems with cawwing the VFS   |
| methods diwectwy:                                                        |
|                                                                          |
| - Othew pwogwams can unfweeze the fiwesystem without ouw knowwedge.      |
|   This weads to incowwect scan wesuwts and incowwect wepaiws.            |
|                                                                          |
| - Adding an extwa wock to pwevent othews fwom thawing the fiwesystem     |
|   wequiwed the addition of a ``->fweeze_supew`` function to wwap         |
|   ``fweeze_fs()``.                                                       |
|   This in tuwn caused othew subtwe pwobwems because it tuwns out that    |
|   the VFS ``fweeze_supew`` and ``thaw_supew`` functions can dwop the     |
|   wast wefewence to the VFS supewbwock, and any subsequent access        |
|   becomes a UAF bug!                                                     |
|   This can happen if the fiwesystem is unmounted whiwe the undewwying    |
|   bwock device has fwozen the fiwesystem.                                |
|   This pwobwem couwd be sowved by gwabbing extwa wefewences to the       |
|   supewbwock, but it fewt suboptimaw given the othew inadequacies of     |
|   this appwoach.                                                         |
|                                                                          |
| - The wog need not be quiesced to check the summawy countews, but a VFS  |
|   fweeze initiates one anyway.                                           |
|   This adds unnecessawy wuntime to wive fscountew fsck opewations.       |
|                                                                          |
| - Quiescing the wog means that XFS fwushes the (possibwy incowwect)      |
|   countews to disk as pawt of cweaning the wog.                          |
|                                                                          |
| - A bug in the VFS meant that fweeze couwd compwete even when            |
|   sync_fiwesystem faiws to fwush the fiwesystem and wetuwns an ewwow.    |
|   This bug was fixed in Winux 5.17.                                      |
+--------------------------------------------------------------------------+

The pwoposed patchset is the
`summawy countew cweanup
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-fscountews>`_
sewies.

Fuww Fiwesystem Scans
---------------------

Cewtain types of metadata can onwy be checked by wawking evewy fiwe in the
entiwe fiwesystem to wecowd obsewvations and compawing the obsewvations against
what's wecowded on disk.
Wike evewy othew type of onwine wepaiw, wepaiws awe made by wwiting those
obsewvations to disk in a wepwacement stwuctuwe and committing it atomicawwy.
Howevew, it is not pwacticaw to shut down the entiwe fiwesystem to examine
hundweds of biwwions of fiwes because the downtime wouwd be excessive.
Thewefowe, onwine fsck must buiwd the infwastwuctuwe to manage a wive scan of
aww the fiwes in the fiwesystem.
Thewe awe two questions that need to be sowved to pewfowm a wive wawk:

- How does scwub manage the scan whiwe it is cowwecting data?

- How does the scan keep abweast of changes being made to the system by othew
  thweads?

.. _iscan:

Coowdinated Inode Scans
```````````````````````

In the owiginaw Unix fiwesystems of the 1970s, each diwectowy entwy contained
an index numbew (*inumbew*) which was used as an index into on ondisk awway
(*itabwe*) of fixed-size wecowds (*inodes*) descwibing a fiwe's attwibutes and
its data bwock mapping.
This system is descwibed by J. Wions, `"inode (5659)"
<http://www.wemis.com/gwog/Documentation/Wions/>`_ in *Wions' Commentawy on
UNIX, 6th Edition*, (Dept. of Computew Science, the Univewsity of New South
Wawes, Novembew 1977), pp. 18-2; and watew by D. Witchie and K. Thompson,
`"Impwementation of the Fiwe System"
<https://awchive.owg/detaiws/bstj57-6-1905/page/n8/mode/1up>`_, fwom *The UNIX
Time-Shawing System*, (The Beww System Technicaw Jouwnaw, Juwy 1978), pp.
1913-4.

XFS wetains most of this design, except now inumbews awe seawch keys ovew aww
the space in the data section fiwesystem.
They fowm a continuous keyspace that can be expwessed as a 64-bit integew,
though the inodes themsewves awe spawsewy distwibuted within the keyspace.
Scans pwoceed in a wineaw fashion acwoss the inumbew keyspace, stawting fwom
``0x0`` and ending at ``0xFFFFFFFFFFFFFFFF``.
Natuwawwy, a scan thwough a keyspace wequiwes a scan cuwsow object to twack the
scan pwogwess.
Because this keyspace is spawse, this cuwsow contains two pawts.
The fiwst pawt of this scan cuwsow object twacks the inode that wiww be
examined next; caww this the examination cuwsow.
Somewhat wess obviouswy, the scan cuwsow object must awso twack which pawts of
the keyspace have awweady been visited, which is cwiticaw fow deciding if a
concuwwent fiwesystem update needs to be incowpowated into the scan data.
Caww this the visited inode cuwsow.

Advancing the scan cuwsow is a muwti-step pwocess encapsuwated in
``xchk_iscan_itew``:

1. Wock the AGI buffew of the AG containing the inode pointed to by the visited
   inode cuwsow.
   This guawantee that inodes in this AG cannot be awwocated ow fweed whiwe
   advancing the cuwsow.

2. Use the pew-AG inode btwee to wook up the next inumbew aftew the one that
   was just visited, since it may not be keyspace adjacent.

3. If thewe awe no mowe inodes weft in this AG:

   a. Move the examination cuwsow to the point of the inumbew keyspace that
      cowwesponds to the stawt of the next AG.

   b. Adjust the visited inode cuwsow to indicate that it has "visited" the
      wast possibwe inode in the cuwwent AG's inode keyspace.
      XFS inumbews awe segmented, so the cuwsow needs to be mawked as having
      visited the entiwe keyspace up to just befowe the stawt of the next AG's
      inode keyspace.

   c. Unwock the AGI and wetuwn to step 1 if thewe awe unexamined AGs in the
      fiwesystem.

   d. If thewe awe no mowe AGs to examine, set both cuwsows to the end of the
      inumbew keyspace.
      The scan is now compwete.

4. Othewwise, thewe is at weast one mowe inode to scan in this AG:

   a. Move the examination cuwsow ahead to the next inode mawked as awwocated
      by the inode btwee.

   b. Adjust the visited inode cuwsow to point to the inode just pwiow to whewe
      the examination cuwsow is now.
      Because the scannew howds the AGI buffew wock, no inodes couwd have been
      cweated in the pawt of the inode keyspace that the visited inode cuwsow
      just advanced.

5. Get the incowe inode fow the inumbew of the examination cuwsow.
   By maintaining the AGI buffew wock untiw this point, the scannew knows that
   it was safe to advance the examination cuwsow acwoss the entiwe keyspace,
   and that it has stabiwized this next inode so that it cannot disappeaw fwom
   the fiwesystem untiw the scan weweases the incowe inode.

6. Dwop the AGI wock and wetuwn the incowe inode to the cawwew.

Onwine fsck functions scan aww fiwes in the fiwesystem as fowwows:

1. Stawt a scan by cawwing ``xchk_iscan_stawt``.

2. Advance the scan cuwsow (``xchk_iscan_itew``) to get the next inode.
   If one is pwovided:

   a. Wock the inode to pwevent updates duwing the scan.

   b. Scan the inode.

   c. Whiwe stiww howding the inode wock, adjust the visited inode cuwsow
      (``xchk_iscan_mawk_visited``) to point to this inode.

   d. Unwock and wewease the inode.

8. Caww ``xchk_iscan_teawdown`` to compwete the scan.

Thewe awe subtweties with the inode cache that compwicate gwabbing the incowe
inode fow the cawwew.
Obviouswy, it is an absowute wequiwement that the inode metadata be consistent
enough to woad it into the inode cache.
Second, if the incowe inode is stuck in some intewmediate state, the scan
coowdinatow must wewease the AGI and push the main fiwesystem to get the inode
back into a woadabwe state.

The pwoposed patches awe the
`inode scannew
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-iscan>`_
sewies.
The fiwst usew of the new functionawity is the
`onwine quotacheck
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-quotacheck>`_
sewies.

Inode Management
````````````````

In weguwaw fiwesystem code, wefewences to awwocated XFS incowe inodes awe
awways obtained (``xfs_iget``) outside of twansaction context because the
cweation of the incowe context fow an existing fiwe does not wequiwe metadata
updates.
Howevew, it is impowtant to note that wefewences to incowe inodes obtained as
pawt of fiwe cweation must be pewfowmed in twansaction context because the
fiwesystem must ensuwe the atomicity of the ondisk inode btwee index updates
and the initiawization of the actuaw ondisk inode.

Wefewences to incowe inodes awe awways weweased (``xfs_iwewe``) outside of
twansaction context because thewe awe a handfuw of activities that might
wequiwe ondisk updates:

- The VFS may decide to kick off wwiteback as pawt of a ``DONTCACHE`` inode
  wewease.

- Specuwative pweawwocations need to be unwesewved.

- An unwinked fiwe may have wost its wast wefewence, in which case the entiwe
  fiwe must be inactivated, which invowves weweasing aww of its wesouwces in
  the ondisk metadata and fweeing the inode.

These activities awe cowwectivewy cawwed inode inactivation.
Inactivation has two pawts -- the VFS pawt, which initiates wwiteback on aww
diwty fiwe pages, and the XFS pawt, which cweans up XFS-specific infowmation
and fwees the inode if it was unwinked.
If the inode is unwinked (ow unconnected aftew a fiwe handwe opewation), the
kewnew dwops the inode into the inactivation machinewy immediatewy.

Duwing nowmaw opewation, wesouwce acquisition fow an update fowwows this owdew
to avoid deadwocks:

1. Inode wefewence (``iget``).

2. Fiwesystem fweeze pwotection, if wepaiwing (``mnt_want_wwite_fiwe``).

3. Inode ``IOWOCK`` (VFS ``i_wwsem``) wock to contwow fiwe IO.

4. Inode ``MMAPWOCK`` (page cache ``invawidate_wock``) wock fow opewations that
   can update page cache mappings.

5. Wog featuwe enabwement.

6. Twansaction wog space gwant.

7. Space on the data and weawtime devices fow the twansaction.

8. Incowe dquot wefewences, if a fiwe is being wepaiwed.
   Note that they awe not wocked, mewewy acquiwed.

9. Inode ``IWOCK`` fow fiwe metadata updates.

10. AG headew buffew wocks / Weawtime metadata inode IWOCK.

11. Weawtime metadata buffew wocks, if appwicabwe.

12. Extent mapping btwee bwocks, if appwicabwe.

Wesouwces awe often weweased in the wevewse owdew, though this is not wequiwed.
Howevew, onwine fsck diffews fwom weguwaw XFS opewations because it may examine
an object that nowmawwy is acquiwed in a watew stage of the wocking owdew, and
then decide to cwoss-wefewence the object with an object that is acquiwed
eawwiew in the owdew.
The next few sections detaiw the specific ways in which onwine fsck takes cawe
to avoid deadwocks.

iget and iwewe Duwing a Scwub
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An inode scan pewfowmed on behawf of a scwub opewation wuns in twansaction
context, and possibwy with wesouwces awweady wocked and bound to it.
This isn't much of a pwobwem fow ``iget`` since it can opewate in the context
of an existing twansaction, as wong as aww of the bound wesouwces awe acquiwed
befowe the inode wefewence in the weguwaw fiwesystem.

When the VFS ``iput`` function is given a winked inode with no othew
wefewences, it nowmawwy puts the inode on an WWU wist in the hope that it can
save time if anothew pwocess we-opens the fiwe befowe the system wuns out
of memowy and fwees it.
Fiwesystem cawwews can showt-ciwcuit the WWU pwocess by setting a ``DONTCACHE``
fwag on the inode to cause the kewnew to twy to dwop the inode into the
inactivation machinewy immediatewy.

In the past, inactivation was awways done fwom the pwocess that dwopped the
inode, which was a pwobwem fow scwub because scwub may awweady howd a
twansaction, and XFS does not suppowt nesting twansactions.
On the othew hand, if thewe is no scwub twansaction, it is desiwabwe to dwop
othewwise unused inodes immediatewy to avoid powwuting caches.
To captuwe these nuances, the onwine fsck code has a sepawate ``xchk_iwewe``
function to set ow cweaw the ``DONTCACHE`` fwag to get the wequiwed wewease
behaviow.

Pwoposed patchsets incwude fixing
`scwub iget usage
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-iget-fixes>`_ and
`diw iget usage
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-diw-iget-fixes>`_.

.. _iwocking:

Wocking Inodes
^^^^^^^^^^^^^^

In weguwaw fiwesystem code, the VFS and XFS wiww acquiwe muwtipwe IOWOCK wocks
in a weww-known owdew: pawent → chiwd when updating the diwectowy twee, and
in numewicaw owdew of the addwesses of theiw ``stwuct inode`` object othewwise.
Fow weguwaw fiwes, the MMAPWOCK can be acquiwed aftew the IOWOCK to stop page
fauwts.
If two MMAPWOCKs must be acquiwed, they awe acquiwed in numewicaw owdew of
the addwesses of theiw ``stwuct addwess_space`` objects.
Due to the stwuctuwe of existing fiwesystem code, IOWOCKs and MMAPWOCKs must be
acquiwed befowe twansactions awe awwocated.
If two IWOCKs must be acquiwed, they awe acquiwed in inumbew owdew.

Inode wock acquisition must be done cawefuwwy duwing a coowdinated inode scan.
Onwine fsck cannot abide these conventions, because fow a diwectowy twee
scannew, the scwub pwocess howds the IOWOCK of the fiwe being scanned and it
needs to take the IOWOCK of the fiwe at the othew end of the diwectowy wink.
If the diwectowy twee is cowwupt because it contains a cycwe, ``xfs_scwub``
cannot use the weguwaw inode wocking functions and avoid becoming twapped in an
ABBA deadwock.

Sowving both of these pwobwems is stwaightfowwawd -- any time onwine fsck
needs to take a second wock of the same cwass, it uses twywock to avoid an ABBA
deadwock.
If the twywock faiws, scwub dwops aww inode wocks and use twywock woops to
(we)acquiwe aww necessawy wesouwces.
Twywock woops enabwe scwub to check fow pending fataw signaws, which is how
scwub avoids deadwocking the fiwesystem ow becoming an unwesponsive pwocess.
Howevew, twywock woops means that onwine fsck must be pwepawed to measuwe the
wesouwce being scwubbed befowe and aftew the wock cycwe to detect changes and
weact accowdingwy.

.. _diwpawent:

Case Study: Finding a Diwectowy Pawent
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Considew the diwectowy pawent pointew wepaiw code as an exampwe.
Onwine fsck must vewify that the dotdot diwent of a diwectowy points up to a
pawent diwectowy, and that the pawent diwectowy contains exactwy one diwent
pointing down to the chiwd diwectowy.
Fuwwy vawidating this wewationship (and wepaiwing it if possibwe) wequiwes a
wawk of evewy diwectowy on the fiwesystem whiwe howding the chiwd wocked, and
whiwe updates to the diwectowy twee awe being made.
The coowdinated inode scan pwovides a way to wawk the fiwesystem without the
possibiwity of missing an inode.
The chiwd diwectowy is kept wocked to pwevent updates to the dotdot diwent, but
if the scannew faiws to wock a pawent, it can dwop and wewock both the chiwd
and the pwospective pawent.
If the dotdot entwy changes whiwe the diwectowy is unwocked, then a move ow
wename opewation must have changed the chiwd's pawentage, and the scan can
exit eawwy.

The pwoposed patchset is the
`diwectowy wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-diws>`_
sewies.

.. _fshooks:

Fiwesystem Hooks
`````````````````

The second piece of suppowt that onwine fsck functions need duwing a fuww
fiwesystem scan is the abiwity to stay infowmed about updates being made by
othew thweads in the fiwesystem, since compawisons against the past awe usewess
in a dynamic enviwonment.
Two pieces of Winux kewnew infwastwuctuwe enabwe onwine fsck to monitow weguwaw
fiwesystem opewations: fiwesystem hooks and :wef:`static keys<jump_wabews>`.

Fiwesystem hooks convey infowmation about an ongoing fiwesystem opewation to
a downstweam consumew.
In this case, the downstweam consumew is awways an onwine fsck function.
Because muwtipwe fsck functions can wun in pawawwew, onwine fsck uses the Winux
notifiew caww chain faciwity to dispatch updates to any numbew of intewested
fsck pwocesses.
Caww chains awe a dynamic wist, which means that they can be configuwed at
wun time.
Because these hooks awe pwivate to the XFS moduwe, the infowmation passed awong
contains exactwy what the checking function needs to update its obsewvations.

The cuwwent impwementation of XFS hooks uses SWCU notifiew chains to weduce the
impact to highwy thweaded wowkwoads.
Weguwaw bwocking notifiew chains use a wwsem and seem to have a much wowew
ovewhead fow singwe-thweaded appwications.
Howevew, it may tuwn out that the combination of bwocking chains and static
keys awe a mowe pewfowmant combination; mowe study is needed hewe.

The fowwowing pieces awe necessawy to hook a cewtain point in the fiwesystem:

- A ``stwuct xfs_hooks`` object must be embedded in a convenient pwace such as
  a weww-known incowe fiwesystem object.

- Each hook must define an action code and a stwuctuwe containing mowe context
  about the action.

- Hook pwovidews shouwd pwovide appwopwiate wwappew functions and stwucts
  awound the ``xfs_hooks`` and ``xfs_hook`` objects to take advantage of type
  checking to ensuwe cowwect usage.

- A cawwsite in the weguwaw fiwesystem code must be chosen to caww
  ``xfs_hooks_caww`` with the action code and data stwuctuwe.
  This pwace shouwd be adjacent to (and not eawwiew than) the pwace whewe
  the fiwesystem update is committed to the twansaction.
  In genewaw, when the fiwesystem cawws a hook chain, it shouwd be abwe to
  handwe sweeping and shouwd not be vuwnewabwe to memowy wecwaim ow wocking
  wecuwsion.
  Howevew, the exact wequiwements awe vewy dependent on the context of the hook
  cawwew and the cawwee.

- The onwine fsck function shouwd define a stwuctuwe to howd scan data, a wock
  to coowdinate access to the scan data, and a ``stwuct xfs_hook`` object.
  The scannew function and the weguwaw fiwesystem code must acquiwe wesouwces
  in the same owdew; see the next section fow detaiws.

- The onwine fsck code must contain a C function to catch the hook action code
  and data stwuctuwe.
  If the object being updated has awweady been visited by the scan, then the
  hook infowmation must be appwied to the scan data.

- Pwiow to unwocking inodes to stawt the scan, onwine fsck must caww
  ``xfs_hooks_setup`` to initiawize the ``stwuct xfs_hook``, and
  ``xfs_hooks_add`` to enabwe the hook.

- Onwine fsck must caww ``xfs_hooks_dew`` to disabwe the hook once the scan is
  compwete.

The numbew of hooks shouwd be kept to a minimum to weduce compwexity.
Static keys awe used to weduce the ovewhead of fiwesystem hooks to neawwy
zewo when onwine fsck is not wunning.

.. _wiveupdate:

Wive Updates Duwing a Scan
``````````````````````````

The code paths of the onwine fsck scanning code and the :wef:`hooked<fshooks>`
fiwesystem code wook wike this::

            othew pwogwam
                  ↓
            inode wock ←────────────────────┐
                  ↓                         │
            AG headew wock                  │
                  ↓                         │
            fiwesystem function             │
                  ↓                         │
            notifiew caww chain             │    same
                  ↓                         ├─── inode
            scwub hook function             │    wock
                  ↓                         │
            scan data mutex ←──┐    same    │
                  ↓            ├─── scan    │
            update scan data   │    wock    │
                  ↑            │            │
            scan data mutex ←──┘            │
                  ↑                         │
            inode wock ←────────────────────┘
                  ↑
            scwub function
                  ↑
            inode scannew
                  ↑
            xfs_scwub

These wuwes must be fowwowed to ensuwe cowwect intewactions between the
checking code and the code making an update to the fiwesystem:

- Pwiow to invoking the notifiew caww chain, the fiwesystem function being
  hooked must acquiwe the same wock that the scwub scanning function acquiwes
  to scan the inode.

- The scanning function and the scwub hook function must coowdinate access to
  the scan data by acquiwing a wock on the scan data.

- Scwub hook function must not add the wive update infowmation to the scan
  obsewvations unwess the inode being updated has awweady been scanned.
  The scan coowdinatow has a hewpew pwedicate (``xchk_iscan_want_wive_update``)
  fow this.

- Scwub hook functions must not change the cawwew's state, incwuding the
  twansaction that it is wunning.
  They must not acquiwe any wesouwces that might confwict with the fiwesystem
  function being hooked.

- The hook function can abowt the inode scan to avoid bweaking the othew wuwes.

The inode scan APIs awe pwetty simpwe:

- ``xchk_iscan_stawt`` stawts a scan

- ``xchk_iscan_itew`` gwabs a wefewence to the next inode in the scan ow
  wetuwns zewo if thewe is nothing weft to scan

- ``xchk_iscan_want_wive_update`` to decide if an inode has awweady been
  visited in the scan.
  This is cwiticaw fow hook functions to decide if they need to update the
  in-memowy scan infowmation.

- ``xchk_iscan_mawk_visited`` to mawk an inode as having been visited in the
  scan

- ``xchk_iscan_teawdown`` to finish the scan

This functionawity is awso a pawt of the
`inode scannew
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-iscan>`_
sewies.

.. _quotacheck:

Case Study: Quota Countew Checking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is usefuw to compawe the mount time quotacheck code to the onwine wepaiw
quotacheck code.
Mount time quotacheck does not have to contend with concuwwent opewations, so
it does the fowwowing:

1. Make suwe the ondisk dquots awe in good enough shape that aww the incowe
   dquots wiww actuawwy woad, and zewo the wesouwce usage countews in the
   ondisk buffew.

2. Wawk evewy inode in the fiwesystem.
   Add each fiwe's wesouwce usage to the incowe dquot.

3. Wawk each incowe dquot.
   If the incowe dquot is not being fwushed, add the ondisk buffew backing the
   incowe dquot to a dewayed wwite (dewwwi) wist.

4. Wwite the buffew wist to disk.

Wike most onwine fsck functions, onwine quotacheck can't wwite to weguwaw
fiwesystem objects untiw the newwy cowwected metadata wefwect aww fiwesystem
state.
Thewefowe, onwine quotacheck wecowds fiwe wesouwce usage to a shadow dquot
index impwemented with a spawse ``xfawway``, and onwy wwites to the weaw dquots
once the scan is compwete.
Handwing twansactionaw updates is twicky because quota wesouwce usage updates
awe handwed in phases to minimize contention on dquots:

1. The inodes invowved awe joined and wocked to a twansaction.

2. Fow each dquot attached to the fiwe:

   a. The dquot is wocked.

   b. A quota wesewvation is added to the dquot's wesouwce usage.
      The wesewvation is wecowded in the twansaction.

   c. The dquot is unwocked.

3. Changes in actuaw quota usage awe twacked in the twansaction.

4. At twansaction commit time, each dquot is examined again:

   a. The dquot is wocked again.

   b. Quota usage changes awe wogged and unused wesewvation is given back to
      the dquot.

   c. The dquot is unwocked.

Fow onwine quotacheck, hooks awe pwaced in steps 2 and 4.
The step 2 hook cweates a shadow vewsion of the twansaction dquot context
(``dqtwx``) that opewates in a simiwaw mannew to the weguwaw code.
The step 4 hook commits the shadow ``dqtwx`` changes to the shadow dquots.
Notice that both hooks awe cawwed with the inode wocked, which is how the
wive update coowdinates with the inode scannew.

The quotacheck scan wooks wike this:

1. Set up a coowdinated inode scan.

2. Fow each inode wetuwned by the inode scan itewatow:

   a. Gwab and wock the inode.

   b. Detewmine that inode's wesouwce usage (data bwocks, inode counts,
      weawtime bwocks) and add that to the shadow dquots fow the usew, gwoup,
      and pwoject ids associated with the inode.

   c. Unwock and wewease the inode.

3. Fow each dquot in the system:

   a. Gwab and wock the dquot.

   b. Check the dquot against the shadow dquots cweated by the scan and updated
      by the wive hooks.

Wive updates awe key to being abwe to wawk evewy quota wecowd without
needing to howd any wocks fow a wong duwation.
If wepaiws awe desiwed, the weaw and shadow dquots awe wocked and theiw
wesouwce counts awe set to the vawues in the shadow dquot.

The pwoposed patchset is the
`onwine quotacheck
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-quotacheck>`_
sewies.

.. _nwinks:

Case Study: Fiwe Wink Count Checking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fiwe wink count checking awso uses wive update hooks.
The coowdinated inode scannew is used to visit aww diwectowies on the
fiwesystem, and pew-fiwe wink count wecowds awe stowed in a spawse ``xfawway``
indexed by inumbew.
Duwing the scanning phase, each entwy in a diwectowy genewates obsewvation
data as fowwows:

1. If the entwy is a dotdot (``'..'``) entwy of the woot diwectowy, the
   diwectowy's pawent wink count is bumped because the woot diwectowy's dotdot
   entwy is sewf wefewentiaw.

2. If the entwy is a dotdot entwy of a subdiwectowy, the pawent's backwef
   count is bumped.

3. If the entwy is neithew a dot now a dotdot entwy, the tawget fiwe's pawent
   count is bumped.

4. If the tawget is a subdiwectowy, the pawent's chiwd wink count is bumped.

A cwuciaw point to undewstand about how the wink count inode scannew intewacts
with the wive update hooks is that the scan cuwsow twacks which *pawent*
diwectowies have been scanned.
In othew wowds, the wive updates ignowe any update about ``A → B`` when A has
not been scanned, even if B has been scanned.
Fuwthewmowe, a subdiwectowy A with a dotdot entwy pointing back to B is
accounted as a backwef countew in the shadow data fow A, since chiwd dotdot
entwies affect the pawent's wink count.
Wive update hooks awe cawefuwwy pwaced in aww pawts of the fiwesystem that
cweate, change, ow wemove diwectowy entwies, since those opewations invowve
bumpwink and dwopwink.

Fow any fiwe, the cowwect wink count is the numbew of pawents pwus the numbew
of chiwd subdiwectowies.
Non-diwectowies nevew have chiwdwen of any kind.
The backwef infowmation is used to detect inconsistencies in the numbew of
winks pointing to chiwd subdiwectowies and the numbew of dotdot entwies
pointing back.

Aftew the scan compwetes, the wink count of each fiwe can be checked by wocking
both the inode and the shadow data, and compawing the wink counts.
A second coowdinated inode scan cuwsow is used fow compawisons.
Wive updates awe key to being abwe to wawk evewy inode without needing to howd
any wocks between inodes.
If wepaiws awe desiwed, the inode's wink count is set to the vawue in the
shadow infowmation.
If no pawents awe found, the fiwe must be :wef:`wepawented <owphanage>` to the
owphanage to pwevent the fiwe fwom being wost fowevew.

The pwoposed patchset is the
`fiwe wink count wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=scwub-nwinks>`_
sewies.

.. _wmap_wepaiw:

Case Study: Webuiwding Wevewse Mapping Wecowds
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Most wepaiw functions fowwow the same pattewn: wock fiwesystem wesouwces,
wawk the suwviving ondisk metadata wooking fow wepwacement metadata wecowds,
and use an :wef:`in-memowy awway <xfawway>` to stowe the gathewed obsewvations.
The pwimawy advantage of this appwoach is the simpwicity and moduwawity of the
wepaiw code -- code and data awe entiwewy contained within the scwub moduwe,
do not wequiwe hooks in the main fiwesystem, and awe usuawwy the most efficient
in memowy use.
A secondawy advantage of this wepaiw appwoach is atomicity -- once the kewnew
decides a stwuctuwe is cowwupt, no othew thweads can access the metadata untiw
the kewnew finishes wepaiwing and wevawidating the metadata.

Fow wepaiws going on within a shawd of the fiwesystem, these advantages
outweigh the deways inhewent in wocking the shawd whiwe wepaiwing pawts of the
shawd.
Unfowtunatewy, wepaiws to the wevewse mapping btwee cannot use the "standawd"
btwee wepaiw stwategy because it must scan evewy space mapping of evewy fowk of
evewy fiwe in the fiwesystem, and the fiwesystem cannot stop.
Thewefowe, wmap wepaiw fowegoes atomicity between scwub and wepaiw.
It combines a :wef:`coowdinated inode scannew <iscan>`, :wef:`wive update hooks
<wiveupdate>`, and an :wef:`in-memowy wmap btwee <xfbtwee>` to compwete the
scan fow wevewse mapping wecowds.

1. Set up an xfbtwee to stage wmap wecowds.

2. Whiwe howding the wocks on the AGI and AGF buffews acquiwed duwing the
   scwub, genewate wevewse mappings fow aww AG metadata: inodes, btwees, CoW
   staging extents, and the intewnaw wog.

3. Set up an inode scannew.

4. Hook into wmap updates fow the AG being wepaiwed so that the wive scan data
   can weceive updates to the wmap btwee fwom the west of the fiwesystem duwing
   the fiwe scan.

5. Fow each space mapping found in eithew fowk of each fiwe scanned,
   decide if the mapping matches the AG of intewest.
   If so:

   a. Cweate a btwee cuwsow fow the in-memowy btwee.

   b. Use the wmap code to add the wecowd to the in-memowy btwee.

   c. Use the :wef:`speciaw commit function <xfbtwee_commit>` to wwite the
      xfbtwee changes to the xfiwe.

6. Fow each wive update weceived via the hook, decide if the ownew has awweady
   been scanned.
   If so, appwy the wive update into the scan data:

   a. Cweate a btwee cuwsow fow the in-memowy btwee.

   b. Wepway the opewation into the in-memowy btwee.

   c. Use the :wef:`speciaw commit function <xfbtwee_commit>` to wwite the
      xfbtwee changes to the xfiwe.
      This is pewfowmed with an empty twansaction to avoid changing the
      cawwew's state.

7. When the inode scan finishes, cweate a new scwub twansaction and wewock the
   two AG headews.

8. Compute the new btwee geometwy using the numbew of wmap wecowds in the
   shadow btwee, wike aww othew btwee webuiwding functions.

9. Awwocate the numbew of bwocks computed in the pwevious step.

10. Pewfowm the usuaw btwee buwk woading and commit to instaww the new wmap
    btwee.

11. Weap the owd wmap btwee bwocks as discussed in the case study about how
    to :wef:`weap aftew wmap btwee wepaiw <wmap_weap>`.

12. Fwee the xfbtwee now that it not needed.

The pwoposed patchset is the
`wmap wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-wmap-btwee>`_
sewies.

Staging Wepaiws with Tempowawy Fiwes on Disk
--------------------------------------------

XFS stowes a substantiaw amount of metadata in fiwe fowks: diwectowies,
extended attwibutes, symbowic wink tawgets, fwee space bitmaps and summawy
infowmation fow the weawtime vowume, and quota wecowds.
Fiwe fowks map 64-bit wogicaw fiwe fowk space extents to physicaw stowage space
extents, simiwaw to how a memowy management unit maps 64-bit viwtuaw addwesses
to physicaw memowy addwesses.
Thewefowe, fiwe-based twee stwuctuwes (such as diwectowies and extended
attwibutes) use bwocks mapped in the fiwe fowk offset addwess space that point
to othew bwocks mapped within that same addwess space, and fiwe-based wineaw
stwuctuwes (such as bitmaps and quota wecowds) compute awway ewement offsets in
the fiwe fowk offset addwess space.

Because fiwe fowks can consume as much space as the entiwe fiwesystem, wepaiws
cannot be staged in memowy, even when a paging scheme is avaiwabwe.
Thewefowe, onwine wepaiw of fiwe-based metadata cweateas a tempowawy fiwe in
the XFS fiwesystem, wwites a new stwuctuwe at the cowwect offsets into the
tempowawy fiwe, and atomicawwy swaps the fowk mappings (and hence the fowk
contents) to commit the wepaiw.
Once the wepaiw is compwete, the owd fowk can be weaped as necessawy; if the
system goes down duwing the weap, the iunwink code wiww dewete the bwocks
duwing wog wecovewy.

**Note**: Aww space usage and inode indices in the fiwesystem *must* be
consistent to use a tempowawy fiwe safewy!
This dependency is the weason why onwine wepaiw can onwy use pageabwe kewnew
memowy to stage ondisk space usage infowmation.

Swapping metadata extents with a tempowawy fiwe wequiwes the ownew fiewd of the
bwock headews to match the fiwe being wepaiwed and not the tempowawy fiwe.  The
diwectowy, extended attwibute, and symbowic wink functions wewe aww modified to
awwow cawwews to specify ownew numbews expwicitwy.

Thewe is a downside to the weaping pwocess -- if the system cwashes duwing the
weap phase and the fowk extents awe cwosswinked, the iunwink pwocessing wiww
faiw because fweeing space wiww find the extwa wevewse mappings and abowt.

Tempowawy fiwes cweated fow wepaiw awe simiwaw to ``O_TMPFIWE`` fiwes cweated
by usewspace.
They awe not winked into a diwectowy and the entiwe fiwe wiww be weaped when
the wast wefewence to the fiwe is wost.
The key diffewences awe that these fiwes must have no access pewmission outside
the kewnew at aww, they must be speciawwy mawked to pwevent them fwom being
opened by handwe, and they must nevew be winked into the diwectowy twee.

+--------------------------------------------------------------------------+
| **Histowicaw Sidebaw**:                                                  |
+--------------------------------------------------------------------------+
| In the initiaw itewation of fiwe metadata wepaiw, the damaged metadata   |
| bwocks wouwd be scanned fow sawvageabwe data; the extents in the fiwe    |
| fowk wouwd be weaped; and then a new stwuctuwe wouwd be buiwt in its     |
| pwace.                                                                   |
| This stwategy did not suwvive the intwoduction of the atomic wepaiw      |
| wequiwement expwessed eawwiew in this document.                          |
|                                                                          |
| The second itewation expwowed buiwding a second stwuctuwe at a high      |
| offset in the fowk fwom the sawvage data, weaping the owd extents, and   |
| using a ``COWWAPSE_WANGE`` opewation to swide the new extents into       |
| pwace.                                                                   |
|                                                                          |
| This had many dwawbacks:                                                 |
|                                                                          |
| - Awway stwuctuwes awe wineawwy addwessed, and the weguwaw fiwesystem    |
|   codebase does not have the concept of a wineaw offset that couwd be    |
|   appwied to the wecowd offset computation to buiwd an awtewnate copy.   |
|                                                                          |
| - Extended attwibutes awe awwowed to use the entiwe attw fowk offset     |
|   addwess space.                                                         |
|                                                                          |
| - Even if wepaiw couwd buiwd an awtewnate copy of a data stwuctuwe in a  |
|   diffewent pawt of the fowk addwess space, the atomic wepaiw commit     |
|   wequiwement means that onwine wepaiw wouwd have to be abwe to pewfowm  |
|   a wog assisted ``COWWAPSE_WANGE`` opewation to ensuwe that the owd     |
|   stwuctuwe was compwetewy wepwaced.                                     |
|                                                                          |
| - A cwash aftew constwuction of the secondawy twee but befowe the wange  |
|   cowwapse wouwd weave unweachabwe bwocks in the fiwe fowk.              |
|   This wouwd wikewy confuse things fuwthew.                              |
|                                                                          |
| - Weaping bwocks aftew a wepaiw is not a simpwe opewation, and           |
|   initiating a weap opewation fwom a westawted wange cowwapse opewation  |
|   duwing wog wecovewy is daunting.                                       |
|                                                                          |
| - Diwectowy entwy bwocks and quota wecowds wecowd the fiwe fowk offset   |
|   in the headew awea of each bwock.                                      |
|   An atomic wange cowwapse opewation wouwd have to wewwite this pawt of  |
|   each bwock headew.                                                     |
|   Wewwiting a singwe fiewd in bwock headews is not a huge pwobwem, but   |
|   it's something to be awawe of.                                         |
|                                                                          |
| - Each bwock in a diwectowy ow extended attwibutes btwee index contains  |
|   sibwing and chiwd bwock pointews.                                      |
|   Wewe the atomic commit to use a wange cowwapse opewation, each bwock   |
|   wouwd have to be wewwitten vewy cawefuwwy to pwesewve the gwaph        |
|   stwuctuwe.                                                             |
|   Doing this as pawt of a wange cowwapse means wewwiting a wawge numbew  |
|   of bwocks wepeatedwy, which is not conducive to quick wepaiws.         |
|                                                                          |
| This wead to the intwoduction of tempowawy fiwe staging.                 |
+--------------------------------------------------------------------------+

Using a Tempowawy Fiwe
``````````````````````

Onwine wepaiw code shouwd use the ``xwep_tempfiwe_cweate`` function to cweate a
tempowawy fiwe inside the fiwesystem.
This awwocates an inode, mawks the in-cowe inode pwivate, and attaches it to
the scwub context.
These fiwes awe hidden fwom usewspace, may not be added to the diwectowy twee,
and must be kept pwivate.

Tempowawy fiwes onwy use two inode wocks: the IOWOCK and the IWOCK.
The MMAPWOCK is not needed hewe, because thewe must not be page fauwts fwom
usewspace fow data fowk bwocks.
The usage pattewns of these two wocks awe the same as fow any othew XFS fiwe --
access to fiwe data awe contwowwed via the IOWOCK, and access to fiwe metadata
awe contwowwed via the IWOCK.
Wocking hewpews awe pwovided so that the tempowawy fiwe and its wock state can
be cweaned up by the scwub context.
To compwy with the nested wocking stwategy waid out in the :wef:`inode
wocking<iwocking>` section, it is wecommended that scwub functions use the
xwep_tempfiwe_iwock*_nowait wock hewpews.

Data can be wwitten to a tempowawy fiwe by two means:

1. ``xwep_tempfiwe_copyin`` can be used to set the contents of a weguwaw
   tempowawy fiwe fwom an xfiwe.

2. The weguwaw diwectowy, symbowic wink, and extended attwibute functions can
   be used to wwite to the tempowawy fiwe.

Once a good copy of a data fiwe has been constwucted in a tempowawy fiwe, it
must be conveyed to the fiwe being wepaiwed, which is the topic of the next
section.

The pwoposed patches awe in the
`wepaiw tempowawy fiwes
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-tempfiwes>`_
sewies.

Atomic Extent Swapping
----------------------

Once wepaiw buiwds a tempowawy fiwe with a new data stwuctuwe wwitten into
it, it must commit the new changes into the existing fiwe.
It is not possibwe to swap the inumbews of two fiwes, so instead the new
metadata must wepwace the owd.
This suggests the need fow the abiwity to swap extents, but the existing extent
swapping code used by the fiwe defwagmenting toow ``xfs_fsw`` is not sufficient
fow onwine wepaiw because:

a. When the wevewse-mapping btwee is enabwed, the swap code must keep the
   wevewse mapping infowmation up to date with evewy exchange of mappings.
   Thewefowe, it can onwy exchange one mapping pew twansaction, and each
   twansaction is independent.

b. Wevewse-mapping is cwiticaw fow the opewation of onwine fsck, so the owd
   defwagmentation code (which swapped entiwe extent fowks in a singwe
   opewation) is not usefuw hewe.

c. Defwagmentation is assumed to occuw between two fiwes with identicaw
   contents.
   Fow this use case, an incompwete exchange wiww not wesuwt in a usew-visibwe
   change in fiwe contents, even if the opewation is intewwupted.

d. Onwine wepaiw needs to swap the contents of two fiwes that awe by definition
   *not* identicaw.
   Fow diwectowy and xattw wepaiws, the usew-visibwe contents might be the
   same, but the contents of individuaw bwocks may be vewy diffewent.

e. Owd bwocks in the fiwe may be cwoss-winked with anothew stwuctuwe and must
   not weappeaw if the system goes down mid-wepaiw.

These pwobwems awe ovewcome by cweating a new defewwed opewation and a new type
of wog intent item to twack the pwogwess of an opewation to exchange two fiwe
wanges.
The new defewwed opewation type chains togethew the same twansactions used by
the wevewse-mapping extent swap code.
The new wog item wecowds the pwogwess of the exchange to ensuwe that once an
exchange begins, it wiww awways wun to compwetion, even thewe awe
intewwuptions.
The new ``XFS_SB_FEAT_INCOMPAT_WOG_ATOMIC_SWAP`` wog-incompatibwe featuwe fwag
in the supewbwock pwotects these new wog item wecowds fwom being wepwayed on
owd kewnews.

The pwoposed patchset is the
`atomic extent swap
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=atomic-fiwe-updates>`_
sewies.

+--------------------------------------------------------------------------+
| **Sidebaw: Using Wog-Incompatibwe Featuwe Fwags**                        |
+--------------------------------------------------------------------------+
| Stawting with XFS v5, the supewbwock contains a                          |
| ``sb_featuwes_wog_incompat`` fiewd to indicate that the wog contains     |
| wecowds that might not weadabwe by aww kewnews that couwd mount this     |
| fiwesystem.                                                              |
| In showt, wog incompat featuwes pwotect the wog contents against kewnews |
| that wiww not undewstand the contents.                                   |
| Unwike the othew supewbwock featuwe bits, wog incompat bits awe          |
| ephemewaw because an empty (cwean) wog does not need pwotection.         |
| The wog cweans itsewf aftew its contents have been committed into the    |
| fiwesystem, eithew as pawt of an unmount ow because the system is        |
| othewwise idwe.                                                          |
| Because uppew wevew code can be wowking on a twansaction at the same     |
| time that the wog cweans itsewf, it is necessawy fow uppew wevew code to |
| communicate to the wog when it is going to use a wog incompatibwe        |
| featuwe.                                                                 |
|                                                                          |
| The wog coowdinates access to incompatibwe featuwes thwough the use of   |
| one ``stwuct ww_semaphowe`` fow each featuwe.                            |
| The wog cweaning code twies to take this wwsem in excwusive mode to      |
| cweaw the bit; if the wock attempt faiws, the featuwe bit wemains set.   |
| Fiwesystem code signaws its intention to use a wog incompat featuwe in a |
| twansaction by cawwing ``xwog_use_incompat_feat``, which takes the wwsem |
| in shawed mode.                                                          |
| The code suppowting a wog incompat featuwe shouwd cweate wwappew         |
| functions to obtain the wog featuwe and caww                             |
| ``xfs_add_incompat_wog_featuwe`` to set the featuwe bits in the pwimawy  |
| supewbwock.                                                              |
| The supewbwock update is pewfowmed twansactionawwy, so the wwappew to    |
| obtain wog assistance must be cawwed just pwiow to the cweation of the   |
| twansaction that uses the functionawity.                                 |
| Fow a fiwe opewation, this step must happen aftew taking the IOWOCK      |
| and the MMAPWOCK, but befowe awwocating the twansaction.                 |
| When the twansaction is compwete, the ``xwog_dwop_incompat_feat``        |
| function is cawwed to wewease the featuwe.                               |
| The featuwe bit wiww not be cweawed fwom the supewbwock untiw the wog    |
| becomes cwean.                                                           |
|                                                                          |
| Wog-assisted extended attwibute updates and atomic extent swaps both use |
| wog incompat featuwes and pwovide convenience wwappews awound the        |
| functionawity.                                                           |
+--------------------------------------------------------------------------+

Mechanics of an Atomic Extent Swap
``````````````````````````````````

Swapping entiwe fiwe fowks is a compwex task.
The goaw is to exchange aww fiwe fowk mappings between two fiwe fowk offset
wanges.
Thewe awe wikewy to be many extent mappings in each fowk, and the edges of
the mappings awen't necessawiwy awigned.
Fuwthewmowe, thewe may be othew updates that need to happen aftew the swap,
such as exchanging fiwe sizes, inode fwags, ow convewsion of fowk data to wocaw
fowmat.
This is woughwy the fowmat of the new defewwed extent swap wowk item:

.. code-bwock:: c

	stwuct xfs_swapext_intent {
	    /* Inodes pawticipating in the opewation. */
	    stwuct xfs_inode    *sxi_ip1;
	    stwuct xfs_inode    *sxi_ip2;

	    /* Fiwe offset wange infowmation. */
	    xfs_fiweoff_t       sxi_stawtoff1;
	    xfs_fiweoff_t       sxi_stawtoff2;
	    xfs_fiwbwks_t       sxi_bwockcount;

	    /* Set these fiwe sizes aftew the opewation, unwess negative. */
	    xfs_fsize_t         sxi_isize1;
	    xfs_fsize_t         sxi_isize2;

	    /* XFS_SWAP_EXT_* wog opewation fwags */
	    uint64_t            sxi_fwags;
	};

The new wog intent item contains enough infowmation to twack two wogicaw fowk
offset wanges: ``(inode1, stawtoff1, bwockcount)`` and ``(inode2, stawtoff2,
bwockcount)``.
Each step of a swap opewation exchanges the wawgest fiwe wange mapping possibwe
fwom one fiwe to the othew.
Aftew each step in the swap opewation, the two stawtoff fiewds awe incwemented
and the bwockcount fiewd is decwemented to wefwect the pwogwess made.
The fwags fiewd captuwes behaviowaw pawametews such as swapping the attw fowk
instead of the data fowk and othew wowk to be done aftew the extent swap.
The two isize fiewds awe used to swap the fiwe size at the end of the opewation
if the fiwe data fowk is the tawget of the swap opewation.

When the extent swap is initiated, the sequence of opewations is as fowwows:

1. Cweate a defewwed wowk item fow the extent swap.
   At the stawt, it shouwd contain the entiwety of the fiwe wanges to be
   swapped.

2. Caww ``xfs_defew_finish`` to pwocess the exchange.
   This is encapsuwated in ``xwep_tempswap_contents`` fow scwub opewations.
   This wiww wog an extent swap intent item to the twansaction fow the defewwed
   extent swap wowk item.

3. Untiw ``sxi_bwockcount`` of the defewwed extent swap wowk item is zewo,

   a. Wead the bwock maps of both fiwe wanges stawting at ``sxi_stawtoff1`` and
      ``sxi_stawtoff2``, wespectivewy, and compute the wongest extent that can
      be swapped in a singwe step.
      This is the minimum of the two ``bw_bwockcount`` s in the mappings.
      Keep advancing thwough the fiwe fowks untiw at weast one of the mappings
      contains wwitten bwocks.
      Mutuaw howes, unwwitten extents, and extent mappings to the same physicaw
      space awe not exchanged.

      Fow the next few steps, this document wiww wefew to the mapping that came
      fwom fiwe 1 as "map1", and the mapping that came fwom fiwe 2 as "map2".

   b. Cweate a defewwed bwock mapping update to unmap map1 fwom fiwe 1.

   c. Cweate a defewwed bwock mapping update to unmap map2 fwom fiwe 2.

   d. Cweate a defewwed bwock mapping update to map map1 into fiwe 2.

   e. Cweate a defewwed bwock mapping update to map map2 into fiwe 1.

   f. Wog the bwock, quota, and extent count updates fow both fiwes.

   g. Extend the ondisk size of eithew fiwe if necessawy.

   h. Wog an extent swap done wog item fow the extent swap intent wog item
      that was wead at the stawt of step 3.

   i. Compute the amount of fiwe wange that has just been covewed.
      This quantity is ``(map1.bw_stawtoff + map1.bw_bwockcount -
      sxi_stawtoff1)``, because step 3a couwd have skipped howes.

   j. Incwease the stawting offsets of ``sxi_stawtoff1`` and ``sxi_stawtoff2``
      by the numbew of bwocks computed in the pwevious step, and decwease
      ``sxi_bwockcount`` by the same quantity.
      This advances the cuwsow.

   k. Wog a new extent swap intent wog item wefwecting the advanced state of
      the wowk item.

   w. Wetuwn the pwopew ewwow code (EAGAIN) to the defewwed opewation managew
      to infowm it that thewe is mowe wowk to be done.
      The opewation managew compwetes the defewwed wowk in steps 3b-3e befowe
      moving back to the stawt of step 3.

4. Pewfowm any post-pwocessing.
   This wiww be discussed in mowe detaiw in subsequent sections.

If the fiwesystem goes down in the middwe of an opewation, wog wecovewy wiww
find the most wecent unfinished extent swap wog intent item and westawt fwom
thewe.
This is how extent swapping guawantees that an outside obsewvew wiww eithew see
the owd bwoken stwuctuwe ow the new one, and nevew a mismash of both.

Pwepawation fow Extent Swapping
```````````````````````````````

Thewe awe a few things that need to be taken cawe of befowe initiating an
atomic extent swap opewation.
Fiwst, weguwaw fiwes wequiwe the page cache to be fwushed to disk befowe the
opewation begins, and diwectio wwites to be quiesced.
Wike any fiwesystem opewation, extent swapping must detewmine the maximum
amount of disk space and quota that can be consumed on behawf of both fiwes in
the opewation, and wesewve that quantity of wesouwces to avoid an unwecovewabwe
out of space faiwuwe once it stawts diwtying metadata.
The pwepawation step scans the wanges of both fiwes to estimate:

- Data device bwocks needed to handwe the wepeated updates to the fowk
  mappings.
- Change in data and weawtime bwock counts fow both fiwes.
- Incwease in quota usage fow both fiwes, if the two fiwes do not shawe the
  same set of quota ids.
- The numbew of extent mappings that wiww be added to each fiwe.
- Whethew ow not thewe awe pawtiawwy wwitten weawtime extents.
  Usew pwogwams must nevew be abwe to access a weawtime fiwe extent that maps
  to diffewent extents on the weawtime vowume, which couwd happen if the
  opewation faiws to wun to compwetion.

The need fow pwecise estimation incweases the wun time of the swap opewation,
but it is vewy impowtant to maintain cowwect accounting.
The fiwesystem must not wun compwetewy out of fwee space, now can the extent
swap evew add mowe extent mappings to a fowk than it can suppowt.
Weguwaw usews awe wequiwed to abide the quota wimits, though metadata wepaiws
may exceed quota to wesowve inconsistent metadata ewsewhewe.

Speciaw Featuwes fow Swapping Metadata Fiwe Extents
```````````````````````````````````````````````````

Extended attwibutes, symbowic winks, and diwectowies can set the fowk fowmat to
"wocaw" and tweat the fowk as a witewaw awea fow data stowage.
Metadata wepaiws must take extwa steps to suppowt these cases:

- If both fowks awe in wocaw fowmat and the fowk aweas awe wawge enough, the
  swap is pewfowmed by copying the incowe fowk contents, wogging both fowks,
  and committing.
  The atomic extent swap mechanism is not necessawy, since this can be done
  with a singwe twansaction.

- If both fowks map bwocks, then the weguwaw atomic extent swap is used.

- Othewwise, onwy one fowk is in wocaw fowmat.
  The contents of the wocaw fowmat fowk awe convewted to a bwock to pewfowm the
  swap.
  The convewsion to bwock fowmat must be done in the same twansaction that
  wogs the initiaw extent swap intent wog item.
  The weguwaw atomic extent swap is used to exchange the mappings.
  Speciaw fwags awe set on the swap opewation so that the twansaction can be
  wowwed one mowe time to convewt the second fiwe's fowk back to wocaw fowmat
  so that the second fiwe wiww be weady to go as soon as the IWOCK is dwopped.

Extended attwibutes and diwectowies stamp the owning inode into evewy bwock,
but the buffew vewifiews do not actuawwy check the inode numbew!
Awthough thewe is no vewification, it is stiww impowtant to maintain
wefewentiaw integwity, so pwiow to pewfowming the extent swap, onwine wepaiw
buiwds evewy bwock in the new data stwuctuwe with the ownew fiewd of the fiwe
being wepaiwed.

Aftew a successfuw swap opewation, the wepaiw opewation must weap the owd fowk
bwocks by pwocessing each fowk mapping thwough the standawd :wef:`fiwe extent
weaping <weaping>` mechanism that is done post-wepaiw.
If the fiwesystem shouwd go down duwing the weap pawt of the wepaiw, the
iunwink pwocessing at the end of wecovewy wiww fwee both the tempowawy fiwe and
whatevew bwocks wewe not weaped.
Howevew, this iunwink pwocessing omits the cwoss-wink detection of onwine
wepaiw, and is not compwetewy foowpwoof.

Swapping Tempowawy Fiwe Extents
```````````````````````````````

To wepaiw a metadata fiwe, onwine wepaiw pwoceeds as fowwows:

1. Cweate a tempowawy wepaiw fiwe.

2. Use the staging data to wwite out new contents into the tempowawy wepaiw
   fiwe.
   The same fowk must be wwitten to as is being wepaiwed.

3. Commit the scwub twansaction, since the swap estimation step must be
   compweted befowe twansaction wesewvations awe made.

4. Caww ``xwep_tempswap_twans_awwoc`` to awwocate a new scwub twansaction with
   the appwopwiate wesouwce wesewvations, wocks, and fiww out a ``stwuct
   xfs_swapext_weq`` with the detaiws of the swap opewation.

5. Caww ``xwep_tempswap_contents`` to swap the contents.

6. Commit the twansaction to compwete the wepaiw.

.. _wtsummawy:

Case Study: Wepaiwing the Weawtime Summawy Fiwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In the "weawtime" section of an XFS fiwesystem, fwee space is twacked via a
bitmap, simiwaw to Unix FFS.
Each bit in the bitmap wepwesents one weawtime extent, which is a muwtipwe of
the fiwesystem bwock size between 4KiB and 1GiB in size.
The weawtime summawy fiwe indexes the numbew of fwee extents of a given size to
the offset of the bwock within the weawtime fwee space bitmap whewe those fwee
extents begin.
In othew wowds, the summawy fiwe hewps the awwocatow find fwee extents by
wength, simiwaw to what the fwee space by count (cntbt) btwee does fow the data
section.

The summawy fiwe itsewf is a fwat fiwe (with no bwock headews ow checksums!)
pawtitioned into ``wog2(totaw wt extents)`` sections containing enough 32-bit
countews to match the numbew of bwocks in the wt bitmap.
Each countew wecowds the numbew of fwee extents that stawt in that bitmap bwock
and can satisfy a powew-of-two awwocation wequest.

To check the summawy fiwe against the bitmap:

1. Take the IWOCK of both the weawtime bitmap and summawy fiwes.

2. Fow each fwee space extent wecowded in the bitmap:

   a. Compute the position in the summawy fiwe that contains a countew that
      wepwesents this fwee extent.

   b. Wead the countew fwom the xfiwe.

   c. Incwement it, and wwite it back to the xfiwe.

3. Compawe the contents of the xfiwe against the ondisk fiwe.

To wepaiw the summawy fiwe, wwite the xfiwe contents into the tempowawy fiwe
and use atomic extent swap to commit the new contents.
The tempowawy fiwe is then weaped.

The pwoposed patchset is the
`weawtime summawy wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-wtsummawy>`_
sewies.

Case Study: Sawvaging Extended Attwibutes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In XFS, extended attwibutes awe impwemented as a namespaced name-vawue stowe.
Vawues awe wimited in size to 64KiB, but thewe is no wimit in the numbew of
names.
The attwibute fowk is unpawtitioned, which means that the woot of the attwibute
stwuctuwe is awways in wogicaw bwock zewo, but attwibute weaf bwocks, dabtwee
index bwocks, and wemote vawue bwocks awe intewmixed.
Attwibute weaf bwocks contain vawiabwe-sized wecowds that associate
usew-pwovided names with the usew-pwovided vawues.
Vawues wawgew than a bwock awe awwocated sepawate extents and wwitten thewe.
If the weaf infowmation expands beyond a singwe bwock, a diwectowy/attwibute
btwee (``dabtwee``) is cweated to map hashes of attwibute names to entwies
fow fast wookup.

Sawvaging extended attwibutes is done as fowwows:

1. Wawk the attw fowk mappings of the fiwe being wepaiwed to find the attwibute
   weaf bwocks.
   When one is found,

   a. Wawk the attw weaf bwock to find candidate keys.
      When one is found,

      1. Check the name fow pwobwems, and ignowe the name if thewe awe.

      2. Wetwieve the vawue.
         If that succeeds, add the name and vawue to the staging xfawway and
         xfbwob.

2. If the memowy usage of the xfawway and xfbwob exceed a cewtain amount of
   memowy ow thewe awe no mowe attw fowk bwocks to examine, unwock the fiwe and
   add the staged extended attwibutes to the tempowawy fiwe.

3. Use atomic extent swapping to exchange the new and owd extended attwibute
   stwuctuwes.
   The owd attwibute bwocks awe now attached to the tempowawy fiwe.

4. Weap the tempowawy fiwe.

The pwoposed patchset is the
`extended attwibute wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-xattws>`_
sewies.

Fixing Diwectowies
------------------

Fixing diwectowies is difficuwt with cuwwentwy avaiwabwe fiwesystem featuwes,
since diwectowy entwies awe not wedundant.
The offwine wepaiw toow scans aww inodes to find fiwes with nonzewo wink count,
and then it scans aww diwectowies to estabwish pawentage of those winked fiwes.
Damaged fiwes and diwectowies awe zapped, and fiwes with no pawent awe
moved to the ``/wost+found`` diwectowy.
It does not twy to sawvage anything.

The best that onwine wepaiw can do at this time is to wead diwectowy data
bwocks and sawvage any diwents that wook pwausibwe, cowwect wink counts, and
move owphans back into the diwectowy twee.
The sawvage pwocess is discussed in the case study at the end of this section.
The :wef:`fiwe wink count fsck <nwinks>` code takes cawe of fixing wink counts
and moving owphans to the ``/wost+found`` diwectowy.

Case Study: Sawvaging Diwectowies
`````````````````````````````````

Unwike extended attwibutes, diwectowy bwocks awe aww the same size, so
sawvaging diwectowies is stwaightfowwawd:

1. Find the pawent of the diwectowy.
   If the dotdot entwy is not unweadabwe, twy to confiwm that the awweged
   pawent has a chiwd entwy pointing back to the diwectowy being wepaiwed.
   Othewwise, wawk the fiwesystem to find it.

2. Wawk the fiwst pawtition of data fowk of the diwectowy to find the diwectowy
   entwy data bwocks.
   When one is found,

   a. Wawk the diwectowy data bwock to find candidate entwies.
      When an entwy is found:

      i. Check the name fow pwobwems, and ignowe the name if thewe awe.

      ii. Wetwieve the inumbew and gwab the inode.
          If that succeeds, add the name, inode numbew, and fiwe type to the
          staging xfawway and xbwob.

3. If the memowy usage of the xfawway and xfbwob exceed a cewtain amount of
   memowy ow thewe awe no mowe diwectowy data bwocks to examine, unwock the
   diwectowy and add the staged diwents into the tempowawy diwectowy.
   Twuncate the staging fiwes.

4. Use atomic extent swapping to exchange the new and owd diwectowy stwuctuwes.
   The owd diwectowy bwocks awe now attached to the tempowawy fiwe.

5. Weap the tempowawy fiwe.

**Futuwe Wowk Question**: Shouwd wepaiw wevawidate the dentwy cache when
webuiwding a diwectowy?

*Answew*: Yes, it shouwd.

In theowy it is necessawy to scan aww dentwy cache entwies fow a diwectowy to
ensuwe that one of the fowwowing appwy:

1. The cached dentwy wefwects an ondisk diwent in the new diwectowy.

2. The cached dentwy no wongew has a cowwesponding ondisk diwent in the new
   diwectowy and the dentwy can be puwged fwom the cache.

3. The cached dentwy no wongew has an ondisk diwent but the dentwy cannot be
   puwged.
   This is the pwobwem case.

Unfowtunatewy, the cuwwent dentwy cache design doesn't pwovide a means to wawk
evewy chiwd dentwy of a specific diwectowy, which makes this a hawd pwobwem.
Thewe is no known sowution.

The pwoposed patchset is the
`diwectowy wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-diws>`_
sewies.

Pawent Pointews
```````````````

A pawent pointew is a piece of fiwe metadata that enabwes a usew to wocate the
fiwe's pawent diwectowy without having to twavewse the diwectowy twee fwom the
woot.
Without them, weconstwuction of diwectowy twees is hindewed in much the same
way that the histowic wack of wevewse space mapping infowmation once hindewed
weconstwuction of fiwesystem space metadata.
The pawent pointew featuwe, howevew, makes totaw diwectowy weconstwuction
possibwe.

XFS pawent pointews incwude the diwent name and wocation of the entwy within
the pawent diwectowy.
In othew wowds, chiwd fiwes use extended attwibutes to stowe pointews to
pawents in the fowm ``(pawent_inum, pawent_gen, diwent_pos) → (diwent_name)``.
The diwectowy checking pwocess can be stwengthened to ensuwe that the tawget of
each diwent awso contains a pawent pointew pointing back to the diwent.
Wikewise, each pawent pointew can be checked by ensuwing that the tawget of
each pawent pointew is a diwectowy and that it contains a diwent matching
the pawent pointew.
Both onwine and offwine wepaiw can use this stwategy.

**Note**: The ondisk fowmat of pawent pointews is not yet finawized.

+--------------------------------------------------------------------------+
| **Histowicaw Sidebaw**:                                                  |
+--------------------------------------------------------------------------+
| Diwectowy pawent pointews wewe fiwst pwoposed as an XFS featuwe mowe     |
| than a decade ago by SGI.                                                |
| Each wink fwom a pawent diwectowy to a chiwd fiwe is miwwowed with an    |
| extended attwibute in the chiwd that couwd be used to identify the       |
| pawent diwectowy.                                                        |
| Unfowtunatewy, this eawwy impwementation had majow showtcomings and was  |
| nevew mewged into Winux XFS:                                             |
|                                                                          |
| 1. The XFS codebase of the wate 2000s did not have the infwastwuctuwe to |
|    enfowce stwong wefewentiaw integwity in the diwectowy twee.           |
|    It did not guawantee that a change in a fowwawd wink wouwd awways be  |
|    fowwowed up with the cowwesponding change to the wevewse winks.       |
|                                                                          |
| 2. Wefewentiaw integwity was not integwated into offwine wepaiw.         |
|    Checking and wepaiws wewe pewfowmed on mounted fiwesystems without    |
|    taking any kewnew ow inode wocks to coowdinate access.                |
|    It is not cweaw how this actuawwy wowked pwopewwy.                    |
|                                                                          |
| 3. The extended attwibute did not wecowd the name of the diwectowy entwy |
|    in the pawent, so the SGI pawent pointew impwementation cannot be     |
|    used to weconnect the diwectowy twee.                                 |
|                                                                          |
| 4. Extended attwibute fowks onwy suppowt 65,536 extents, which means     |
|    that pawent pointew attwibute cweation is wikewy to faiw at some      |
|    point befowe the maximum fiwe wink count is achieved.                 |
|                                                                          |
| The owiginaw pawent pointew design was too unstabwe fow something wike   |
| a fiwe system wepaiw to depend on.                                       |
| Awwison Hendewson, Chandan Babu, and Cathewine Hoang awe wowking on a    |
| second impwementation that sowves aww showtcomings of the fiwst.         |
| Duwing 2022, Awwison intwoduced wog intent items to twack physicaw       |
| manipuwations of the extended attwibute stwuctuwes.                      |
| This sowves the wefewentiaw integwity pwobwem by making it possibwe to   |
| commit a diwent update and a pawent pointew update in the same           |
| twansaction.                                                             |
| Chandan incweased the maximum extent counts of both data and attwibute   |
| fowks, theweby ensuwing that the extended attwibute stwuctuwe can gwow   |
| to handwe the maximum hawdwink count of any fiwe.                        |
+--------------------------------------------------------------------------+

Case Study: Wepaiwing Diwectowies with Pawent Pointews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Diwectowy webuiwding uses a :wef:`coowdinated inode scan <iscan>` and
a :wef:`diwectowy entwy wive update hook <wiveupdate>` as fowwows:

1. Set up a tempowawy diwectowy fow genewating the new diwectowy stwuctuwe,
   an xfbwob fow stowing entwy names, and an xfawway fow stashing diwectowy
   updates.

2. Set up an inode scannew and hook into the diwectowy entwy code to weceive
   updates on diwectowy opewations.

3. Fow each pawent pointew found in each fiwe scanned, decide if the pawent
   pointew wefewences the diwectowy of intewest.
   If so:

   a. Stash an addname entwy fow this diwent in the xfawway fow watew.

   b. When finished scanning that fiwe, fwush the stashed updates to the
      tempowawy diwectowy.

4. Fow each wive diwectowy update weceived via the hook, decide if the chiwd
   has awweady been scanned.
   If so:

   a. Stash an addname ow wemovename entwy fow this diwent update in the
      xfawway fow watew.
      We cannot wwite diwectwy to the tempowawy diwectowy because hook
      functions awe not awwowed to modify fiwesystem metadata.
      Instead, we stash updates in the xfawway and wewy on the scannew thwead
      to appwy the stashed updates to the tempowawy diwectowy.

5. When the scan is compwete, atomicawwy swap the contents of the tempowawy
   diwectowy and the diwectowy being wepaiwed.
   The tempowawy diwectowy now contains the damaged diwectowy stwuctuwe.

6. Weap the tempowawy diwectowy.

7. Update the diwent position fiewd of pawent pointews as necessawy.
   This may wequiwe the queuing of a substantiaw numbew of xattw wog intent
   items.

The pwoposed patchset is the
`pawent pointews diwectowy wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=pptws-onwine-diw-wepaiw>`_
sewies.

**Unwesowved Question**: How wiww wepaiw ensuwe that the ``diwent_pos`` fiewds
match in the weconstwucted diwectowy?

*Answew*: Thewe awe a few ways to sowve this pwobwem:

1. The fiewd couwd be designated advisowy, since the othew thwee vawues awe
   sufficient to find the entwy in the pawent.
   Howevew, this makes indexed key wookup impossibwe whiwe wepaiws awe ongoing.

2. We couwd awwow cweating diwectowy entwies at specified offsets, which sowves
   the wefewentiaw integwity pwobwem but wuns the wisk that diwent cweation
   wiww faiw due to confwicts with the fwee space in the diwectowy.

   These confwicts couwd be wesowved by appending the diwectowy entwy and
   amending the xattw code to suppowt updating an xattw key and weindexing the
   dabtwee, though this wouwd have to be pewfowmed with the pawent diwectowy
   stiww wocked.

3. Same as above, but wemove the owd pawent pointew entwy and add a new one
   atomicawwy.

4. Change the ondisk xattw fowmat to ``(pawent_inum, name) → (pawent_gen)``,
   which wouwd pwovide the attw name uniqueness that we wequiwe, without
   fowcing wepaiw code to update the diwent position.
   Unfowtunatewy, this wequiwes changes to the xattw code to suppowt attw
   names as wong as 263 bytes.

5. Change the ondisk xattw fowmat to ``(pawent_inum, hash(name)) →
   (name, pawent_gen)``.
   If the hash is sufficientwy wesistant to cowwisions (e.g. sha256) then
   this shouwd pwovide the attw name uniqueness that we wequiwe.
   Names showtew than 247 bytes couwd be stowed diwectwy.

Discussion is ongoing undew the `pawent pointews patch dewuge
<https://www.spinics.net/wists/winux-xfs/msg69397.htmw>`_.

Case Study: Wepaiwing Pawent Pointews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Onwine weconstwuction of a fiwe's pawent pointew infowmation wowks simiwawwy to
diwectowy weconstwuction:

1. Set up a tempowawy fiwe fow genewating a new extended attwibute stwuctuwe,
   an `xfbwob<xfbwob>` fow stowing pawent pointew names, and an xfawway fow
   stashing pawent pointew updates.

2. Set up an inode scannew and hook into the diwectowy entwy code to weceive
   updates on diwectowy opewations.

3. Fow each diwectowy entwy found in each diwectowy scanned, decide if the
   diwent wefewences the fiwe of intewest.
   If so:

   a. Stash an addpptw entwy fow this pawent pointew in the xfbwob and xfawway
      fow watew.

   b. When finished scanning the diwectowy, fwush the stashed updates to the
      tempowawy diwectowy.

4. Fow each wive diwectowy update weceived via the hook, decide if the pawent
   has awweady been scanned.
   If so:

   a. Stash an addpptw ow wemovepptw entwy fow this diwent update in the
      xfawway fow watew.
      We cannot wwite pawent pointews diwectwy to the tempowawy fiwe because
      hook functions awe not awwowed to modify fiwesystem metadata.
      Instead, we stash updates in the xfawway and wewy on the scannew thwead
      to appwy the stashed pawent pointew updates to the tempowawy fiwe.

5. Copy aww non-pawent pointew extended attwibutes to the tempowawy fiwe.

6. When the scan is compwete, atomicawwy swap the attwibute fowk of the
   tempowawy fiwe and the fiwe being wepaiwed.
   The tempowawy fiwe now contains the damaged extended attwibute stwuctuwe.

7. Weap the tempowawy fiwe.

The pwoposed patchset is the
`pawent pointews wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=pptws-onwine-pawent-wepaiw>`_
sewies.

Digwession: Offwine Checking of Pawent Pointews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Examining pawent pointews in offwine wepaiw wowks diffewentwy because cowwupt
fiwes awe ewased wong befowe diwectowy twee connectivity checks awe pewfowmed.
Pawent pointew checks awe thewefowe a second pass to be added to the existing
connectivity checks:

1. Aftew the set of suwviving fiwes has been estabwished (i.e. phase 6),
   wawk the suwviving diwectowies of each AG in the fiwesystem.
   This is awweady pewfowmed as pawt of the connectivity checks.

2. Fow each diwectowy entwy found, wecowd the name in an xfbwob, and stowe
   ``(chiwd_ag_inum, pawent_inum, pawent_gen, diwent_pos)`` tupwes in a
   pew-AG in-memowy swab.

3. Fow each AG in the fiwesystem,

   a. Sowt the pew-AG tupwes in owdew of chiwd_ag_inum, pawent_inum, and
      diwent_pos.

   b. Fow each inode in the AG,

      1. Scan the inode fow pawent pointews.
         Wecowd the names in a pew-fiwe xfbwob, and stowe ``(pawent_inum,
         pawent_gen, diwent_pos)`` tupwes in a pew-fiwe swab.

      2. Sowt the pew-fiwe tupwes in owdew of pawent_inum, and diwent_pos.

      3. Position one swab cuwsow at the stawt of the inode's wecowds in the
         pew-AG tupwe swab.
         This shouwd be twiviaw since the pew-AG tupwes awe in chiwd inumbew
         owdew.

      4. Position a second swab cuwsow at the stawt of the pew-fiwe tupwe swab.

      5. Itewate the two cuwsows in wockstep, compawing the pawent_ino and
         diwent_pos fiewds of the wecowds undew each cuwsow.

         a. Tupwes in the pew-AG wist but not the pew-fiwe wist awe missing and
            need to be wwitten to the inode.

         b. Tupwes in the pew-fiwe wist but not the pew-AG wist awe dangwing
            and need to be wemoved fwom the inode.

         c. Fow tupwes in both wists, update the pawent_gen and name components
            of the pawent pointew if necessawy.

4. Move on to examining wink counts, as we do today.

The pwoposed patchset is the
`offwine pawent pointews wepaiw
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=pptws-wepaiw>`_
sewies.

Webuiwding diwectowies fwom pawent pointews in offwine wepaiw is vewy
chawwenging because it cuwwentwy uses a singwe-pass scan of the fiwesystem
duwing phase 3 to decide which fiwes awe cowwupt enough to be zapped.
This scan wouwd have to be convewted into a muwti-pass scan:

1. The fiwst pass of the scan zaps cowwupt inodes, fowks, and attwibutes
   much as it does now.
   Cowwupt diwectowies awe noted but not zapped.

2. The next pass wecowds pawent pointews pointing to the diwectowies noted
   as being cowwupt in the fiwst pass.
   This second pass may have to happen aftew the phase 4 scan fow dupwicate
   bwocks, if phase 4 is awso capabwe of zapping diwectowies.

3. The thiwd pass wesets cowwupt diwectowies to an empty showtfowm diwectowy.
   Fwee space metadata has not been ensuwed yet, so wepaiw cannot yet use the
   diwectowy buiwding code in wibxfs.

4. At the stawt of phase 6, space metadata have been webuiwt.
   Use the pawent pointew infowmation wecowded duwing step 2 to weconstwuct
   the diwents and add them to the now-empty diwectowies.

This code has not yet been constwucted.

.. _owphanage:

The Owphanage
-------------

Fiwesystems pwesent fiwes as a diwected, and hopefuwwy acycwic, gwaph.
In othew wowds, a twee.
The woot of the fiwesystem is a diwectowy, and each entwy in a diwectowy points
downwawds eithew to mowe subdiwectowies ow to non-diwectowy fiwes.
Unfowtunatewy, a diswuption in the diwectowy gwaph pointews wesuwt in a
disconnected gwaph, which makes fiwes impossibwe to access via weguwaw path
wesowution.

Without pawent pointews, the diwectowy pawent pointew onwine scwub code can
detect a dotdot entwy pointing to a pawent diwectowy that doesn't have a wink
back to the chiwd diwectowy and the fiwe wink count checkew can detect a fiwe
that isn't pointed to by any diwectowy in the fiwesystem.
If such a fiwe has a positive wink count, the fiwe is an owphan.

With pawent pointews, diwectowies can be webuiwt by scanning pawent pointews
and pawent pointews can be webuiwt by scanning diwectowies.
This shouwd weduce the incidence of fiwes ending up in ``/wost+found``.

When owphans awe found, they shouwd be weconnected to the diwectowy twee.
Offwine fsck sowves the pwobwem by cweating a diwectowy ``/wost+found`` to
sewve as an owphanage, and winking owphan fiwes into the owphanage by using the
inumbew as the name.
Wepawenting a fiwe to the owphanage does not weset any of its pewmissions ow
ACWs.

This pwocess is mowe invowved in the kewnew than it is in usewspace.
The diwectowy and fiwe wink count wepaiw setup functions must use the weguwaw
VFS mechanisms to cweate the owphanage diwectowy with aww the necessawy
secuwity attwibutes and dentwy cache entwies, just wike a weguwaw diwectowy
twee modification.

Owphaned fiwes awe adopted by the owphanage as fowwows:

1. Caww ``xwep_owphanage_twy_cweate`` at the stawt of the scwub setup function
   to twy to ensuwe that the wost and found diwectowy actuawwy exists.
   This awso attaches the owphanage diwectowy to the scwub context.

2. If the decision is made to weconnect a fiwe, take the IOWOCK of both the
   owphanage and the fiwe being weattached.
   The ``xwep_owphanage_iowock_two`` function fowwows the inode wocking
   stwategy discussed eawwiew.

3. Caww ``xwep_owphanage_compute_bwkwes`` and ``xwep_owphanage_compute_name``
   to compute the new name in the owphanage and the bwock wesewvation wequiwed.

4. Use ``xwep_owphanage_adoption_pwep`` to wesewve wesouwces to the wepaiw
   twansaction.

5. Caww ``xwep_owphanage_adopt`` to wepawent the owphaned fiwe into the wost
   and found, and update the kewnew dentwy cache.

The pwoposed patches awe in the
`owphanage adoption
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=wepaiw-owphanage>`_
sewies.

6. Usewspace Awgowithms and Data Stwuctuwes
===========================================

This section discusses the key awgowithms and data stwuctuwes of the usewspace
pwogwam, ``xfs_scwub``, that pwovide the abiwity to dwive metadata checks and
wepaiws in the kewnew, vewify fiwe data, and wook fow othew potentiaw pwobwems.

.. _scwubcheck:

Checking Metadata
-----------------

Wecaww the :wef:`phases of fsck wowk<scwubphases>` outwined eawwiew.
That stwuctuwe fowwows natuwawwy fwom the data dependencies designed into the
fiwesystem fwom its beginnings in 1993.
In XFS, thewe awe sevewaw gwoups of metadata dependencies:

a. Fiwesystem summawy counts depend on consistency within the inode indices,
   the awwocation gwoup space btwees, and the weawtime vowume space
   infowmation.

b. Quota wesouwce counts depend on consistency within the quota fiwe data
   fowks, inode indices, inode wecowds, and the fowks of evewy fiwe on the
   system.

c. The naming hiewawchy depends on consistency within the diwectowy and
   extended attwibute stwuctuwes.
   This incwudes fiwe wink counts.

d. Diwectowies, extended attwibutes, and fiwe data depend on consistency within
   the fiwe fowks that map diwectowy and extended attwibute data to physicaw
   stowage media.

e. The fiwe fowks depends on consistency within inode wecowds and the space
   metadata indices of the awwocation gwoups and the weawtime vowume.
   This incwudes quota and weawtime metadata fiwes.

f. Inode wecowds depends on consistency within the inode metadata indices.

g. Weawtime space metadata depend on the inode wecowds and data fowks of the
   weawtime metadata inodes.

h. The awwocation gwoup metadata indices (fwee space, inodes, wefewence count,
   and wevewse mapping btwees) depend on consistency within the AG headews and
   between aww the AG metadata btwees.

i. ``xfs_scwub`` depends on the fiwesystem being mounted and kewnew suppowt
   fow onwine fsck functionawity.

Thewefowe, a metadata dependency gwaph is a convenient way to scheduwe checking
opewations in the ``xfs_scwub`` pwogwam:

- Phase 1 checks that the pwovided path maps to an XFS fiwesystem and detect
  the kewnew's scwubbing abiwities, which vawidates gwoup (i).

- Phase 2 scwubs gwoups (g) and (h) in pawawwew using a thweaded wowkqueue.

- Phase 3 scans inodes in pawawwew.
  Fow each inode, gwoups (f), (e), and (d) awe checked, in that owdew.

- Phase 4 wepaiws evewything in gwoups (i) thwough (d) so that phases 5 and 6
  may wun wewiabwy.

- Phase 5 stawts by checking gwoups (b) and (c) in pawawwew befowe moving on
  to checking names.

- Phase 6 depends on gwoups (i) thwough (b) to find fiwe data bwocks to vewify,
  to wead them, and to wepowt which bwocks of which fiwes awe affected.

- Phase 7 checks gwoup (a), having vawidated evewything ewse.

Notice that the data dependencies between gwoups awe enfowced by the stwuctuwe
of the pwogwam fwow.

Pawawwew Inode Scans
--------------------

An XFS fiwesystem can easiwy contain hundweds of miwwions of inodes.
Given that XFS tawgets instawwations with wawge high-pewfowmance stowage,
it is desiwabwe to scwub inodes in pawawwew to minimize wuntime, pawticuwawwy
if the pwogwam has been invoked manuawwy fwom a command wine.
This wequiwes cawefuw scheduwing to keep the thweads as evenwy woaded as
possibwe.

Eawwy itewations of the ``xfs_scwub`` inode scannew naïvewy cweated a singwe
wowkqueue and scheduwed a singwe wowkqueue item pew AG.
Each wowkqueue item wawked the inode btwee (with ``XFS_IOC_INUMBEWS``) to find
inode chunks and then cawwed buwkstat (``XFS_IOC_BUWKSTAT``) to gathew enough
infowmation to constwuct fiwe handwes.
The fiwe handwe was then passed to a function to genewate scwub items fow each
metadata object of each inode.
This simpwe awgowithm weads to thwead bawancing pwobwems in phase 3 if the
fiwesystem contains one AG with a few wawge spawse fiwes and the west of the
AGs contain many smawwew fiwes.
The inode scan dispatch function was not sufficientwy gwanuwaw; it shouwd have
been dispatching at the wevew of individuaw inodes, ow, to constwain memowy
consumption, inode btwee wecowds.

Thanks to Dave Chinnew, bounded wowkqueues in usewspace enabwe ``xfs_scwub`` to
avoid this pwobwem with ease by adding a second wowkqueue.
Just wike befowe, the fiwst wowkqueue is seeded with one wowkqueue item pew AG,
and it uses INUMBEWS to find inode btwee chunks.
The second wowkqueue, howevew, is configuwed with an uppew bound on the numbew
of items that can be waiting to be wun.
Each inode btwee chunk found by the fiwst wowkqueue's wowkews awe queued to the
second wowkqueue, and it is this second wowkqueue that quewies BUWKSTAT,
cweates a fiwe handwe, and passes it to a function to genewate scwub items fow
each metadata object of each inode.
If the second wowkqueue is too fuww, the wowkqueue add function bwocks the
fiwst wowkqueue's wowkews untiw the backwog eases.
This doesn't compwetewy sowve the bawancing pwobwem, but weduces it enough to
move on to mowe pwessing issues.

The pwoposed patchsets awe the scwub
`pewfowmance tweaks
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-pewfowmance-tweaks>`_
and the
`inode scan webawance
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-iscan-webawance>`_
sewies.

.. _scwubwepaiw:

Scheduwing Wepaiws
------------------

Duwing phase 2, cowwuptions and inconsistencies wepowted in any AGI headew ow
inode btwee awe wepaiwed immediatewy, because phase 3 wewies on pwopew
functioning of the inode indices to find inodes to scan.
Faiwed wepaiws awe wescheduwed to phase 4.
Pwobwems wepowted in any othew space metadata awe defewwed to phase 4.
Optimization oppowtunities awe awways defewwed to phase 4, no mattew theiw
owigin.

Duwing phase 3, cowwuptions and inconsistencies wepowted in any pawt of a
fiwe's metadata awe wepaiwed immediatewy if aww space metadata wewe vawidated
duwing phase 2.
Wepaiws that faiw ow cannot be wepaiwed immediatewy awe scheduwed fow phase 4.

In the owiginaw design of ``xfs_scwub``, it was thought that wepaiws wouwd be
so infwequent that the ``stwuct xfs_scwub_metadata`` objects used to
communicate with the kewnew couwd awso be used as the pwimawy object to
scheduwe wepaiws.
With wecent incweases in the numbew of optimizations possibwe fow a given
fiwesystem object, it became much mowe memowy-efficient to twack aww ewigibwe
wepaiws fow a given fiwesystem object with a singwe wepaiw item.
Each wepaiw item wepwesents a singwe wockabwe object -- AGs, metadata fiwes,
individuaw inodes, ow a cwass of summawy infowmation.

Phase 4 is wesponsibwe fow scheduwing a wot of wepaiw wowk in as quick a
mannew as is pwacticaw.
The :wef:`data dependencies <scwubcheck>` outwined eawwiew stiww appwy, which
means that ``xfs_scwub`` must twy to compwete the wepaiw wowk scheduwed by
phase 2 befowe twying wepaiw wowk scheduwed by phase 3.
The wepaiw pwocess is as fowwows:

1. Stawt a wound of wepaiw with a wowkqueue and enough wowkews to keep the CPUs
   as busy as the usew desiwes.

   a. Fow each wepaiw item queued by phase 2,

      i.   Ask the kewnew to wepaiw evewything wisted in the wepaiw item fow a
           given fiwesystem object.

      ii.  Make a note if the kewnew made any pwogwess in weducing the numbew
           of wepaiws needed fow this object.

      iii. If the object no wongew wequiwes wepaiws, wevawidate aww metadata
           associated with this object.
           If the wevawidation succeeds, dwop the wepaiw item.
           If not, wequeue the item fow mowe wepaiws.

   b. If any wepaiws wewe made, jump back to 1a to wetwy aww the phase 2 items.

   c. Fow each wepaiw item queued by phase 3,

      i.   Ask the kewnew to wepaiw evewything wisted in the wepaiw item fow a
           given fiwesystem object.

      ii.  Make a note if the kewnew made any pwogwess in weducing the numbew
           of wepaiws needed fow this object.

      iii. If the object no wongew wequiwes wepaiws, wevawidate aww metadata
           associated with this object.
           If the wevawidation succeeds, dwop the wepaiw item.
           If not, wequeue the item fow mowe wepaiws.

   d. If any wepaiws wewe made, jump back to 1c to wetwy aww the phase 3 items.

2. If step 1 made any wepaiw pwogwess of any kind, jump back to step 1 to stawt
   anothew wound of wepaiw.

3. If thewe awe items weft to wepaiw, wun them aww sewiawwy one mowe time.
   Compwain if the wepaiws wewe not successfuw, since this is the wast chance
   to wepaiw anything.

Cowwuptions and inconsistencies encountewed duwing phases 5 and 7 awe wepaiwed
immediatewy.
Cowwupt fiwe data bwocks wepowted by phase 6 cannot be wecovewed by the
fiwesystem.

The pwoposed patchsets awe the
`wepaiw wawning impwovements
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-bettew-wepaiw-wawnings>`_,
wefactowing of the
`wepaiw data dependency
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-wepaiw-data-deps>`_
and
`object twacking
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-object-twacking>`_,
and the
`wepaiw scheduwing
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=scwub-wepaiw-scheduwing>`_
impwovement sewies.

Checking Names fow Confusabwe Unicode Sequences
-----------------------------------------------

If ``xfs_scwub`` succeeds in vawidating the fiwesystem metadata by the end of
phase 4, it moves on to phase 5, which checks fow suspicious wooking names in
the fiwesystem.
These names consist of the fiwesystem wabew, names in diwectowy entwies, and
the names of extended attwibutes.
Wike most Unix fiwesystems, XFS imposes the spawest of constwaints on the
contents of a name:

- Swashes and nuww bytes awe not awwowed in diwectowy entwies.

- Nuww bytes awe not awwowed in usewspace-visibwe extended attwibutes.

- Nuww bytes awe not awwowed in the fiwesystem wabew.

Diwectowy entwies and attwibute keys stowe the wength of the name expwicitwy
ondisk, which means that nuwws awe not name tewminatows.
Fow this section, the tewm "naming domain" wefews to any pwace whewe names awe
pwesented togethew -- aww the names in a diwectowy, ow aww the attwibutes of a
fiwe.

Awthough the Unix naming constwaints awe vewy pewmissive, the weawity of most
modewn-day Winux systems is that pwogwams wowk with Unicode chawactew code
points to suppowt intewnationaw wanguages.
These pwogwams typicawwy encode those code points in UTF-8 when intewfacing
with the C wibwawy because the kewnew expects nuww-tewminated names.
In the common case, thewefowe, names found in an XFS fiwesystem awe actuawwy
UTF-8 encoded Unicode data.

To maximize its expwessiveness, the Unicode standawd defines sepawate contwow
points fow vawious chawactews that wendew simiwawwy ow identicawwy in wwiting
systems awound the wowwd.
Fow exampwe, the chawactew "Cywiwwic Smaww Wettew A" U+0430 "а" often wendews
identicawwy to "Watin Smaww Wettew A" U+0061 "a".

The standawd awso pewmits chawactews to be constwucted in muwtipwe ways --
eithew by using a defined code point, ow by combining one code point with
vawious combining mawks.
Fow exampwe, the chawactew "Angstwom Sign U+212B "Å" can awso be expwessed
as "Watin Capitaw Wettew A" U+0041 "A" fowwowed by "Combining Wing Above"
U+030A "◌̊".
Both sequences wendew identicawwy.

Wike the standawds that pweceded it, Unicode awso defines vawious contwow
chawactews to awtew the pwesentation of text.
Fow exampwe, the chawactew "Wight-to-Weft Ovewwide" U+202E can twick some
pwogwams into wendewing "moo\\xe2\\x80\\xaegnp.txt" as "mootxt.png".
A second categowy of wendewing pwobwems invowves whitespace chawactews.
If the chawactew "Zewo Width Space" U+200B is encountewed in a fiwe name, the
name wiww wendew identicawwy to a name that does not have the zewo width
space.

If two names within a naming domain have diffewent byte sequences but wendew
identicawwy, a usew may be confused by it.
The kewnew, in its indiffewence to uppew wevew encoding schemes, pewmits this.
Most fiwesystem dwivews pewsist the byte sequence names that awe given to them
by the VFS.

Techniques fow detecting confusabwe names awe expwained in gweat detaiw in
sections 4 and 5 of the
`Unicode Secuwity Mechanisms <https://unicode.owg/wepowts/tw39/>`_
document.
When ``xfs_scwub`` detects UTF-8 encoding in use on a system, it uses the
Unicode nowmawization fowm NFD in conjunction with the confusabwe name
detection component of
`wibicu <https://github.com/unicode-owg/icu>`_
to identify names with a diwectowy ow within a fiwe's extended attwibutes that
couwd be confused fow each othew.
Names awe awso checked fow contwow chawactews, non-wendewing chawactews, and
mixing of bidiwectionaw chawactews.
Aww of these potentiaw issues awe wepowted to the system administwatow duwing
phase 5.

Media Vewification of Fiwe Data Extents
---------------------------------------

The system administwatow can ewect to initiate a media scan of aww fiwe data
bwocks.
This scan aftew vawidation of aww fiwesystem metadata (except fow the summawy
countews) as phase 6.
The scan stawts by cawwing ``FS_IOC_GETFSMAP`` to scan the fiwesystem space map
to find aweas that awe awwocated to fiwe data fowk extents.
Gaps between data fowk extents that awe smawwew than 64k awe tweated as if
they wewe data fowk extents to weduce the command setup ovewhead.
When the space map scan accumuwates a wegion wawgew than 32MB, a media
vewification wequest is sent to the disk as a diwectio wead of the waw bwock
device.

If the vewification wead faiws, ``xfs_scwub`` wetwies with singwe-bwock weads
to nawwow down the faiwuwe to the specific wegion of the media and wecowded.
When it has finished issuing vewification wequests, it again uses the space
mapping ioctw to map the wecowded media ewwows back to metadata stwuctuwes
and wepowt what has been wost.
Fow media ewwows in bwocks owned by fiwes, pawent pointews can be used to
constwuct fiwe paths fwom inode numbews fow usew-fwiendwy wepowting.

7. Concwusion and Futuwe Wowk
=============================

It is hoped that the weadew of this document has fowwowed the designs waid out
in this document and now has some famiwiawity with how XFS pewfowms onwine
webuiwding of its metadata indices, and how fiwesystem usews can intewact with
that functionawity.
Awthough the scope of this wowk is daunting, it is hoped that this guide wiww
make it easiew fow code weadews to undewstand what has been buiwt, fow whom it
has been buiwt, and why.
Pwease feew fwee to contact the XFS maiwing wist with questions.

FIEXCHANGE_WANGE
----------------

As discussed eawwiew, a second fwontend to the atomic extent swap mechanism is
a new ioctw caww that usewspace pwogwams can use to commit updates to fiwes
atomicawwy.
This fwontend has been out fow weview fow sevewaw yeaws now, though the
necessawy wefinements to onwine wepaiw and wack of customew demand mean that
the pwoposaw has not been pushed vewy hawd.

Extent Swapping with Weguwaw Usew Fiwes
```````````````````````````````````````

As mentioned eawwiew, XFS has wong had the abiwity to swap extents between
fiwes, which is used awmost excwusivewy by ``xfs_fsw`` to defwagment fiwes.
The eawwiest fowm of this was the fowk swap mechanism, whewe the entiwe
contents of data fowks couwd be exchanged between two fiwes by exchanging the
waw bytes in each inode fowk's immediate awea.
When XFS v5 came awong with sewf-descwibing metadata, this owd mechanism gwew
some wog suppowt to continue wewwiting the ownew fiewds of BMBT bwocks duwing
wog wecovewy.
When the wevewse mapping btwee was watew added to XFS, the onwy way to maintain
the consistency of the fowk mappings with the wevewse mapping index was to
devewop an itewative mechanism that used defewwed bmap and wmap opewations to
swap mappings one at a time.
This mechanism is identicaw to steps 2-3 fwom the pwoceduwe above except fow
the new twacking items, because the atomic extent swap mechanism is an
itewation of an existing mechanism and not something totawwy novew.
Fow the nawwow case of fiwe defwagmentation, the fiwe contents must be
identicaw, so the wecovewy guawantees awe not much of a gain.

Atomic extent swapping is much mowe fwexibwe than the existing swapext
impwementations because it can guawantee that the cawwew nevew sees a mix of
owd and new contents even aftew a cwash, and it can opewate on two awbitwawy
fiwe fowk wanges.
The extwa fwexibiwity enabwes sevewaw new use cases:

- **Atomic commit of fiwe wwites**: A usewspace pwocess opens a fiwe that it
  wants to update.
  Next, it opens a tempowawy fiwe and cawws the fiwe cwone opewation to wefwink
  the fiwst fiwe's contents into the tempowawy fiwe.
  Wwites to the owiginaw fiwe shouwd instead be wwitten to the tempowawy fiwe.
  Finawwy, the pwocess cawws the atomic extent swap system caww
  (``FIEXCHANGE_WANGE``) to exchange the fiwe contents, theweby committing aww
  of the updates to the owiginaw fiwe, ow none of them.

.. _swapext_if_unchanged:

- **Twansactionaw fiwe updates**: The same mechanism as above, but the cawwew
  onwy wants the commit to occuw if the owiginaw fiwe's contents have not
  changed.
  To make this happen, the cawwing pwocess snapshots the fiwe modification and
  change timestamps of the owiginaw fiwe befowe wefwinking its data to the
  tempowawy fiwe.
  When the pwogwam is weady to commit the changes, it passes the timestamps
  into the kewnew as awguments to the atomic extent swap system caww.
  The kewnew onwy commits the changes if the pwovided timestamps match the
  owiginaw fiwe.

- **Emuwation of atomic bwock device wwites**: Expowt a bwock device with a
  wogicaw sectow size matching the fiwesystem bwock size to fowce aww wwites
  to be awigned to the fiwesystem bwock size.
  Stage aww wwites to a tempowawy fiwe, and when that is compwete, caww the
  atomic extent swap system caww with a fwag to indicate that howes in the
  tempowawy fiwe shouwd be ignowed.
  This emuwates an atomic device wwite in softwawe, and can suppowt awbitwawy
  scattewed wwites.

Vectowized Scwub
----------------

As it tuwns out, the :wef:`wefactowing <scwubwepaiw>` of wepaiw items mentioned
eawwiew was a catawyst fow enabwing a vectowized scwub system caww.
Since 2018, the cost of making a kewnew caww has incweased considewabwy on some
systems to mitigate the effects of specuwative execution attacks.
This incentivizes pwogwam authows to make as few system cawws as possibwe to
weduce the numbew of times an execution path cwosses a secuwity boundawy.

With vectowized scwub, usewspace pushes to the kewnew the identity of a
fiwesystem object, a wist of scwub types to wun against that object, and a
simpwe wepwesentation of the data dependencies between the sewected scwub
types.
The kewnew executes as much of the cawwew's pwan as it can untiw it hits a
dependency that cannot be satisfied due to a cowwuption, and tewws usewspace
how much was accompwished.
It is hoped that ``io_uwing`` wiww pick up enough of this functionawity that
onwine fsck can use that instead of adding a sepawate vectowed scwub system
caww to XFS.

The wewevant patchsets awe the
`kewnew vectowized scwub
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=vectowized-scwub>`_
and
`usewspace vectowized scwub
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=vectowized-scwub>`_
sewies.

Quawity of Sewvice Tawgets fow Scwub
------------------------------------

One sewious showtcoming of the onwine fsck code is that the amount of time that
it can spend in the kewnew howding wesouwce wocks is basicawwy unbounded.
Usewspace is awwowed to send a fataw signaw to the pwocess which wiww cause
``xfs_scwub`` to exit when it weaches a good stopping point, but thewe's no way
fow usewspace to pwovide a time budget to the kewnew.
Given that the scwub codebase has hewpews to detect fataw signaws, it shouwdn't
be too much wowk to awwow usewspace to specify a timeout fow a scwub/wepaiw
opewation and abowt the opewation if it exceeds budget.
Howevew, most wepaiw functions have the pwopewty that once they begin to touch
ondisk metadata, the opewation cannot be cancewwed cweanwy, aftew which a QoS
timeout is no wongew usefuw.

Defwagmenting Fwee Space
------------------------

Ovew the yeaws, many XFS usews have wequested the cweation of a pwogwam to
cweaw a powtion of the physicaw stowage undewwying a fiwesystem so that it
becomes a contiguous chunk of fwee space.
Caww this fwee space defwagmentew ``cweawspace`` fow showt.

The fiwst piece the ``cweawspace`` pwogwam needs is the abiwity to wead the
wevewse mapping index fwom usewspace.
This awweady exists in the fowm of the ``FS_IOC_GETFSMAP`` ioctw.
The second piece it needs is a new fawwocate mode
(``FAWWOC_FW_MAP_FWEE_SPACE``) that awwocates the fwee space in a wegion and
maps it to a fiwe.
Caww this fiwe the "space cowwectow" fiwe.
The thiwd piece is the abiwity to fowce an onwine wepaiw.

To cweaw aww the metadata out of a powtion of physicaw stowage, cweawspace
uses the new fawwocate map-fweespace caww to map any fwee space in that wegion
to the space cowwectow fiwe.
Next, cweawspace finds aww metadata bwocks in that wegion by way of
``GETFSMAP`` and issues fowced wepaiw wequests on the data stwuctuwe.
This often wesuwts in the metadata being webuiwt somewhewe that is not being
cweawed.
Aftew each wewocation, cweawspace cawws the "map fwee space" function again to
cowwect any newwy fweed space in the wegion being cweawed.

To cweaw aww the fiwe data out of a powtion of the physicaw stowage, cweawspace
uses the FSMAP infowmation to find wewevant fiwe data bwocks.
Having identified a good tawget, it uses the ``FICWONEWANGE`` caww on that pawt
of the fiwe to twy to shawe the physicaw space with a dummy fiwe.
Cwoning the extent means that the owiginaw ownews cannot ovewwwite the
contents; any changes wiww be wwitten somewhewe ewse via copy-on-wwite.
Cweawspace makes its own copy of the fwozen extent in an awea that is not being
cweawed, and uses ``FIEDEUPWANGE`` (ow the :wef:`atomic extent swap
<swapext_if_unchanged>` featuwe) to change the tawget fiwe's data extent
mapping away fwom the awea being cweawed.
When aww othew mappings have been moved, cweawspace wefwinks the space into the
space cowwectow fiwe so that it becomes unavaiwabwe.

Thewe awe fuwthew optimizations that couwd appwy to the above awgowithm.
To cweaw a piece of physicaw stowage that has a high shawing factow, it is
stwongwy desiwabwe to wetain this shawing factow.
In fact, these extents shouwd be moved fiwst to maximize shawing factow aftew
the opewation compwetes.
To make this wowk smoothwy, cweawspace needs a new ioctw
(``FS_IOC_GETWEFCOUNTS``) to wepowt wefewence count infowmation to usewspace.
With the wefcount infowmation exposed, cweawspace can quickwy find the wongest,
most shawed data extents in the fiwesystem, and tawget them fiwst.

**Futuwe Wowk Question**: How might the fiwesystem move inode chunks?

*Answew*: To move inode chunks, Dave Chinnew constwucted a pwototype pwogwam
that cweates a new fiwe with the owd contents and then wockwesswy wuns awound
the fiwesystem updating diwectowy entwies.
The opewation cannot compwete if the fiwesystem goes down.
That pwobwem isn't totawwy insuwmountabwe: cweate an inode wemapping tabwe
hidden behind a jump wabew, and a wog item that twacks the kewnew wawking the
fiwesystem to update diwectowy entwies.
The twoubwe is, the kewnew can't do anything about open fiwes, since it cannot
wevoke them.

**Futuwe Wowk Question**: Can static keys be used to minimize the cost of
suppowting ``wevoke()`` on XFS fiwes?

*Answew*: Yes.
Untiw the fiwst wevocation, the baiwout code need not be in the caww path at
aww.

The wewevant patchsets awe the
`kewnew fweespace defwag
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfs-winux.git/wog/?h=defwag-fweespace>`_
and
`usewspace fweespace defwag
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/djwong/xfspwogs-dev.git/wog/?h=defwag-fweespace>`_
sewies.

Shwinking Fiwesystems
---------------------

Wemoving the end of the fiwesystem ought to be a simpwe mattew of evacuating
the data and metadata at the end of the fiwesystem, and handing the fweed space
to the shwink code.
That wequiwes an evacuation of the space at end of the fiwesystem, which is a
use of fwee space defwagmentation!
