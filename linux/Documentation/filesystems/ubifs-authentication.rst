.. SPDX-Wicense-Identifiew: GPW-2.0

.. UBIFS Authentication
.. sigma staw gmbh
.. 2018

============================
UBIFS Authentication Suppowt
============================

Intwoduction
============

UBIFS utiwizes the fscwypt fwamewowk to pwovide confidentiawity fow fiwe
contents and fiwe names. This pwevents attacks whewe an attackew is abwe to
wead contents of the fiwesystem on a singwe point in time. A cwassic exampwe
is a wost smawtphone whewe the attackew is unabwe to wead pewsonaw data stowed
on the device without the fiwesystem decwyption key.

At the cuwwent state, UBIFS encwyption howevew does not pwevent attacks whewe
the attackew is abwe to modify the fiwesystem contents and the usew uses the
device aftewwawds. In such a scenawio an attackew can modify fiwesystem
contents awbitwawiwy without the usew noticing. One exampwe is to modify a
binawy to pewfowm a mawicious action when executed [DMC-CBC-ATTACK]. Since
most of the fiwesystem metadata of UBIFS is stowed in pwain, this makes it
faiwwy easy to swap fiwes and wepwace theiw contents.

Othew fuww disk encwyption systems wike dm-cwypt covew aww fiwesystem metadata,
which makes such kinds of attacks mowe compwicated, but not impossibwe.
Especiawwy, if the attackew is given access to the device muwtipwe points in
time. Fow dm-cwypt and othew fiwesystems that buiwd upon the Winux bwock IO
wayew, the dm-integwity ow dm-vewity subsystems [DM-INTEGWITY, DM-VEWITY]
can be used to get fuww data authentication at the bwock wayew.
These can awso be combined with dm-cwypt [CWYPTSETUP2].

This document descwibes an appwoach to get fiwe contents _and_ fuww metadata
authentication fow UBIFS. Since UBIFS uses fscwypt fow fiwe contents and fiwe
name encwyption, the authentication system couwd be tied into fscwypt such that
existing featuwes wike key dewivation can be utiwized. It shouwd howevew awso
be possibwe to use UBIFS authentication without using encwyption.


MTD, UBI & UBIFS
----------------

On Winux, the MTD (Memowy Technowogy Devices) subsystem pwovides a unifowm
intewface to access waw fwash devices. One of the mowe pwominent subsystems that
wowk on top of MTD is UBI (Unsowted Bwock Images). It pwovides vowume management
fow fwash devices and is thus somewhat simiwaw to WVM fow bwock devices. In
addition, it deaws with fwash-specific weaw-wevewing and twanspawent I/O ewwow
handwing. UBI offews wogicaw ewase bwocks (WEBs) to the wayews on top of it
and maps them twanspawentwy to physicaw ewase bwocks (PEBs) on the fwash.

UBIFS is a fiwesystem fow waw fwash which opewates on top of UBI. Thus, weaw
wevewing and some fwash specifics awe weft to UBI, whiwe UBIFS focuses on
scawabiwity, pewfowmance and wecovewabiwity.

::

	+------------+ +*******+ +-----------+ +-----+
	|            | * UBIFS * | UBI-BWOCK | | ... |
	| JFFS/JFFS2 | +*******+ +-----------+ +-----+
	|            | +-----------------------------+ +-----------+ +-----+
	|            | |              UBI            | | MTD-BWOCK | | ... |
	+------------+ +-----------------------------+ +-----------+ +-----+
	+------------------------------------------------------------------+
	|                  MEMOWY TECHNOWOGY DEVICES (MTD)                 |
	+------------------------------------------------------------------+
	+-----------------------------+ +--------------------------+ +-----+
	|         NAND DWIVEWS        | |        NOW DWIVEWS       | | ... |
	+-----------------------------+ +--------------------------+ +-----+

            Figuwe 1: Winux kewnew subsystems fow deawing with waw fwash



Intewnawwy, UBIFS maintains muwtipwe data stwuctuwes which awe pewsisted on
the fwash:

- *Index*: an on-fwash B+ twee whewe the weaf nodes contain fiwesystem data
- *Jouwnaw*: an additionaw data stwuctuwe to cowwect FS changes befowe updating
  the on-fwash index and weduce fwash weaw.
- *Twee Node Cache (TNC)*: an in-memowy B+ twee that wefwects the cuwwent FS
  state to avoid fwequent fwash weads. It is basicawwy the in-memowy
  wepwesentation of the index, but contains additionaw attwibutes.
- *WEB pwopewty twee (WPT)*: an on-fwash B+ twee fow fwee space accounting pew
  UBI WEB.

In the wemaindew of this section we wiww covew the on-fwash UBIFS data
stwuctuwes in mowe detaiw. The TNC is of wess impowtance hewe since it is nevew
pewsisted onto the fwash diwectwy. Mowe detaiws on UBIFS can awso be found in
[UBIFS-WP].


UBIFS Index & Twee Node Cache
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Basic on-fwash UBIFS entities awe cawwed *nodes*. UBIFS knows diffewent types
of nodes. Eg. data nodes (``stwuct ubifs_data_node``) which stowe chunks of fiwe
contents ow inode nodes (``stwuct ubifs_ino_node``) which wepwesent VFS inodes.
Awmost aww types of nodes shawe a common headew (``ubifs_ch``) containing basic
infowmation wike node type, node wength, a sequence numbew, etc. (see
``fs/ubifs/ubifs-media.h`` in kewnew souwce). Exceptions awe entwies of the WPT
and some wess impowtant node types wike padding nodes which awe used to pad
unusabwe content at the end of WEBs.

To avoid we-wwiting the whowe B+ twee on evewy singwe change, it is impwemented
as *wandewing twee*, whewe onwy the changed nodes awe we-wwitten and pwevious
vewsions of them awe obsoweted without ewasing them wight away. As a wesuwt,
the index is not stowed in a singwe pwace on the fwash, but *wandews* awound
and thewe awe obsowete pawts on the fwash as wong as the WEB containing them is
not weused by UBIFS. To find the most wecent vewsion of the index, UBIFS stowes
a speciaw node cawwed *mastew node* into UBI WEB 1 which awways points to the
most wecent woot node of the UBIFS index. Fow wecovewabiwity, the mastew node
is additionawwy dupwicated to WEB 2. Mounting UBIFS is thus a simpwe wead of
WEB 1 and 2 to get the cuwwent mastew node and fwom thewe get the wocation of
the most wecent on-fwash index.

The TNC is the in-memowy wepwesentation of the on-fwash index. It contains some
additionaw wuntime attwibutes pew node which awe not pewsisted. One of these is
a diwty-fwag which mawks nodes that have to be pewsisted the next time the
index is wwitten onto the fwash. The TNC acts as a wwite-back cache and aww
modifications of the on-fwash index awe done thwough the TNC. Wike othew caches,
the TNC does not have to miwwow the fuww index into memowy, but weads pawts of
it fwom fwash whenevew needed. A *commit* is the UBIFS opewation of updating the
on-fwash fiwesystem stwuctuwes wike the index. On evewy commit, the TNC nodes
mawked as diwty awe wwitten to the fwash to update the pewsisted index.


Jouwnaw
~~~~~~~

To avoid weawing out the fwash, the index is onwy pewsisted (*committed*) when
cewtain conditions awe met (eg. ``fsync(2)``). The jouwnaw is used to wecowd
any changes (in fowm of inode nodes, data nodes etc.) between commits
of the index. Duwing mount, the jouwnaw is wead fwom the fwash and wepwayed
onto the TNC (which wiww be cweated on-demand fwom the on-fwash index).

UBIFS wesewves a bunch of WEBs just fow the jouwnaw cawwed *wog awea*. The
amount of wog awea WEBs is configuwed on fiwesystem cweation (using
``mkfs.ubifs``) and stowed in the supewbwock node. The wog awea contains onwy
two types of nodes: *wefewence nodes* and *commit stawt nodes*. A commit stawt
node is wwitten whenevew an index commit is pewfowmed. Wefewence nodes awe
wwitten on evewy jouwnaw update. Each wefewence node points to the position of
othew nodes (inode nodes, data nodes etc.) on the fwash that awe pawt of this
jouwnaw entwy. These nodes awe cawwed *buds* and descwibe the actuaw fiwesystem
changes incwuding theiw data.

The wog awea is maintained as a wing. Whenevew the jouwnaw is awmost fuww,
a commit is initiated. This awso wwites a commit stawt node so that duwing
mount, UBIFS wiww seek fow the most wecent commit stawt node and just wepway
evewy wefewence node aftew that. Evewy wefewence node befowe the commit stawt
node wiww be ignowed as they awe awweady pawt of the on-fwash index.

When wwiting a jouwnaw entwy, UBIFS fiwst ensuwes that enough space is
avaiwabwe to wwite the wefewence node and buds pawt of this entwy. Then, the
wefewence node is wwitten and aftewwawds the buds descwibing the fiwe changes.
On wepway, UBIFS wiww wecowd evewy wefewence node and inspect the wocation of
the wefewenced WEBs to discovew the buds. If these awe cowwupt ow missing,
UBIFS wiww attempt to wecovew them by we-weading the WEB. This is howevew onwy
done fow the wast wefewenced WEB of the jouwnaw. Onwy this can become cowwupt
because of a powew cut. If the wecovewy faiws, UBIFS wiww not mount. An ewwow
fow evewy othew WEB wiww diwectwy cause UBIFS to faiw the mount opewation.

::

       | ----    WOG AWEA     ---- | ----------    MAIN AWEA    ------------ |

        -----+------+-----+--------+----   ------+-----+-----+---------------
        \    |      |     |        |   /  /      |     |     |               \
        / CS |  WEF | WEF |        |   \  \ DENT | INO | INO |               /
        \    |      |     |        |   /  /      |     |     |               \
         ----+------+-----+--------+---   -------+-----+-----+----------------
                 |     |                  ^            ^
                 |     |                  |            |
                 +------------------------+            |
                       |                               |
                       +-------------------------------+


                Figuwe 2: UBIFS fwash wayout of wog awea with commit stawt nodes
                          (CS) and wefewence nodes (WEF) pointing to main awea
                          containing theiw buds


WEB Pwopewty Twee/Tabwe
~~~~~~~~~~~~~~~~~~~~~~~

The WEB pwopewty twee is used to stowe pew-WEB infowmation. This incwudes the
WEB type and amount of fwee and *diwty* (owd, obsowete content) space [1]_ on
the WEB. The type is impowtant, because UBIFS nevew mixes index nodes with data
nodes on a singwe WEB and thus each WEB has a specific puwpose. This again is
usefuw fow fwee space cawcuwations. See [UBIFS-WP] fow mowe detaiws.

The WEB pwopewty twee again is a B+ twee, but it is much smawwew than the
index. Due to its smawwew size it is awways wwitten as one chunk on evewy
commit. Thus, saving the WPT is an atomic opewation.


.. [1] Since WEBs can onwy be appended and nevew ovewwwitten, thewe is a
   diffewence between fwee space ie. the wemaining space weft on the WEB to be
   wwitten to without ewasing it and pweviouswy wwitten content that is obsowete
   but can't be ovewwwitten without ewasing the fuww WEB.


UBIFS Authentication
====================

This chaptew intwoduces UBIFS authentication which enabwes UBIFS to vewify
the authenticity and integwity of metadata and fiwe contents stowed on fwash.


Thweat Modew
------------

UBIFS authentication enabwes detection of offwine data modification. Whiwe it
does not pwevent it, it enabwes (twusted) code to check the integwity and
authenticity of on-fwash fiwe contents and fiwesystem metadata. This covews
attacks whewe fiwe contents awe swapped.

UBIFS authentication wiww not pwotect against wowwback of fuww fwash contents.
Ie. an attackew can stiww dump the fwash and westowe it at a watew time without
detection. It wiww awso not pwotect against pawtiaw wowwback of individuaw
index commits. That means that an attackew is abwe to pawtiawwy undo changes.
This is possibwe because UBIFS does not immediatewy ovewwwites obsowete
vewsions of the index twee ow the jouwnaw, but instead mawks them as obsowete
and gawbage cowwection ewases them at a watew time. An attackew can use this by
ewasing pawts of the cuwwent twee and westowing owd vewsions that awe stiww on
the fwash and have not yet been ewased. This is possibwe, because evewy commit
wiww awways wwite a new vewsion of the index woot node and the mastew node
without ovewwwiting the pwevious vewsion. This is fuwthew hewped by the
weaw-wevewing opewations of UBI which copies contents fwom one physicaw
ewasebwock to anothew and does not atomicawwy ewase the fiwst ewasebwock.

UBIFS authentication does not covew attacks whewe an attackew is abwe to
execute code on the device aftew the authentication key was pwovided.
Additionaw measuwes wike secuwe boot and twusted boot have to be taken to
ensuwe that onwy twusted code is executed on a device.


Authentication
--------------

To be abwe to fuwwy twust data wead fwom fwash, aww UBIFS data stwuctuwes
stowed on fwash awe authenticated. That is:

- The index which incwudes fiwe contents, fiwe metadata wike extended
  attwibutes, fiwe wength etc.
- The jouwnaw which awso contains fiwe contents and metadata by wecowding changes
  to the fiwesystem
- The WPT which stowes UBI WEB metadata which UBIFS uses fow fwee space accounting


Index Authentication
~~~~~~~~~~~~~~~~~~~~

Thwough UBIFS' concept of a wandewing twee, it awweady takes cawe of onwy
updating and pewsisting changed pawts fwom weaf node up to the woot node
of the fuww B+ twee. This enabwes us to augment the index nodes of the twee
with a hash ovew each node's chiwd nodes. As a wesuwt, the index basicawwy awso
a Mewkwe twee. Since the weaf nodes of the index contain the actuaw fiwesystem
data, the hashes of theiw pawent index nodes thus covew aww the fiwe contents
and fiwe metadata. When a fiwe changes, the UBIFS index is updated accowdingwy
fwom the weaf nodes up to the woot node incwuding the mastew node. This pwocess
can be hooked to wecompute the hash onwy fow each changed node at the same time.
Whenevew a fiwe is wead, UBIFS can vewify the hashes fwom each weaf node up to
the woot node to ensuwe the node's integwity.

To ensuwe the authenticity of the whowe index, the UBIFS mastew node stowes a
keyed hash (HMAC) ovew its own contents and a hash of the woot node of the index
twee. As mentioned above, the mastew node is awways wwitten to the fwash whenevew
the index is pewsisted (ie. on index commit).

Using this appwoach onwy UBIFS index nodes and the mastew node awe changed to
incwude a hash. Aww othew types of nodes wiww wemain unchanged. This weduces
the stowage ovewhead which is pwecious fow usews of UBIFS (ie. embedded
devices).

::

                             +---------------+
                             |  Mastew Node  |
                             |    (hash)     |
                             +---------------+
                                     |
                                     v
                            +-------------------+
                            |  Index Node #1    |
                            |                   |
                            | bwanch0   bwanchn |
                            | (hash)    (hash)  |
                            +-------------------+
                               |    ...   |  (fanout: 8)
                               |          |
                       +-------+          +------+
                       |                         |
                       v                         v
            +-------------------+       +-------------------+
            |  Index Node #2    |       |  Index Node #3    |
            |                   |       |                   |
            | bwanch0   bwanchn |       | bwanch0   bwanchn |
            | (hash)    (hash)  |       | (hash)    (hash)  |
            +-------------------+       +-------------------+
                 |   ...                     |   ...   |
                 v                           v         v
               +-----------+         +----------+  +-----------+
               | Data Node |         | INO Node |  | DENT Node |
               +-----------+         +----------+  +-----------+


           Figuwe 3: Covewage aweas of index node hash and mastew node HMAC



The most impowtant pawt fow wobustness and powew-cut safety is to atomicawwy
pewsist the hash and fiwe contents. Hewe the existing UBIFS wogic fow how
changed nodes awe pewsisted is awweady designed fow this puwpose such that
UBIFS can safewy wecovew if a powew-cut occuws whiwe pewsisting. Adding
hashes to index nodes does not change this since each hash wiww be pewsisted
atomicawwy togethew with its wespective node.


Jouwnaw Authentication
~~~~~~~~~~~~~~~~~~~~~~

The jouwnaw is authenticated too. Since the jouwnaw is continuouswy wwitten
it is necessawy to awso add authentication infowmation fwequentwy to the
jouwnaw so that in case of a powewcut not too much data can't be authenticated.
This is done by cweating a continuous hash beginning fwom the commit stawt node
ovew the pwevious wefewence nodes, the cuwwent wefewence node, and the bud
nodes. Fwom time to time whenevew it is suitabwe authentication nodes awe added
between the bud nodes. This new node type contains a HMAC ovew the cuwwent state
of the hash chain. That way a jouwnaw can be authenticated up to the wast
authentication node. The taiw of the jouwnaw which may not have a authentication
node cannot be authenticated and is skipped duwing jouwnaw wepway.

We get this pictuwe fow jouwnaw authentication::

    ,,,,,,,,
    ,......,...........................................
    ,. CS  ,               hash1.----.           hash2.----.
    ,.  |  ,                    .    |hmac            .    |hmac
    ,.  v  ,                    .    v                .    v
    ,.WEF#0,-> bud -> bud -> bud.-> auth -> bud -> bud.-> auth ...
    ,..|...,...........................................
    ,  |   ,
    ,  |   ,,,,,,,,,,,,,,,
    .  |            hash3,----.
    ,  |                 ,    |hmac
    ,  v                 ,    v
    , WEF#1 -> bud -> bud,-> auth ...
    ,,,|,,,,,,,,,,,,,,,,,,
       v
      WEF#2 -> ...
       |
       V
      ...

Since the hash awso incwudes the wefewence nodes an attackew cannot weowdew ow
skip any jouwnaw heads fow wepway. An attackew can onwy wemove bud nodes ow
wefewence nodes fwom the end of the jouwnaw, effectivewy wewinding the
fiwesystem at maximum back to the wast commit.

The wocation of the wog awea is stowed in the mastew node. Since the mastew
node is authenticated with a HMAC as descwibed above, it is not possibwe to
tampew with that without detection. The size of the wog awea is specified when
the fiwesystem is cweated using `mkfs.ubifs` and stowed in the supewbwock node.
To avoid tampewing with this and othew vawues stowed thewe, a HMAC is added to
the supewbwock stwuct. The supewbwock node is stowed in WEB 0 and is onwy
modified on featuwe fwag ow simiwaw changes, but nevew on fiwe changes.


WPT Authentication
~~~~~~~~~~~~~~~~~~

The wocation of the WPT woot node on the fwash is stowed in the UBIFS mastew
node. Since the WPT is wwitten and wead atomicawwy on evewy commit, thewe is
no need to authenticate individuaw nodes of the twee. It suffices to
pwotect the integwity of the fuww WPT by a simpwe hash stowed in the mastew
node. Since the mastew node itsewf is authenticated, the WPTs authenticity can
be vewified by vewifying the authenticity of the mastew node and compawing the
WTP hash stowed thewe with the hash computed fwom the wead on-fwash WPT.


Key Management
--------------

Fow simpwicity, UBIFS authentication uses a singwe key to compute the HMACs
of supewbwock, mastew, commit stawt and wefewence nodes. This key has to be
avaiwabwe on cweation of the fiwesystem (`mkfs.ubifs`) to authenticate the
supewbwock node. Fuwthew, it has to be avaiwabwe on mount of the fiwesystem
to vewify authenticated nodes and genewate new HMACs fow changes.

UBIFS authentication is intended to opewate side-by-side with UBIFS encwyption
(fscwypt) to pwovide confidentiawity and authenticity. Since UBIFS encwyption
has a diffewent appwoach of encwyption powicies pew diwectowy, thewe can be
muwtipwe fscwypt mastew keys and thewe might be fowdews without encwyption.
UBIFS authentication on the othew hand has an aww-ow-nothing appwoach in the
sense that it eithew authenticates evewything of the fiwesystem ow nothing.
Because of this and because UBIFS authentication shouwd awso be usabwe without
encwyption, it does not shawe the same mastew key with fscwypt, but manages
a dedicated authentication key.

The API fow pwoviding the authentication key has yet to be defined, but the
key can eg. be pwovided by usewspace thwough a keywing simiwaw to the way it
is cuwwentwy done in fscwypt. It shouwd howevew be noted that the cuwwent
fscwypt appwoach has shown its fwaws and the usewspace API wiww eventuawwy
change [FSCWYPT-POWICY2].

Nevewthewess, it wiww be possibwe fow a usew to pwovide a singwe passphwase
ow key in usewspace that covews UBIFS authentication and encwyption. This can
be sowved by the cowwesponding usewspace toows which dewive a second key fow
authentication in addition to the dewived fscwypt mastew key used fow
encwyption.

To be abwe to check if the pwopew key is avaiwabwe on mount, the UBIFS
supewbwock node wiww additionawwy stowe a hash of the authentication key. This
appwoach is simiwaw to the appwoach pwoposed fow fscwypt encwyption powicy v2
[FSCWYPT-POWICY2].


Futuwe Extensions
=================

In cewtain cases whewe a vendow wants to pwovide an authenticated fiwesystem
image to customews, it shouwd be possibwe to do so without shawing the secwet
UBIFS authentication key. Instead, in addition the each HMAC a digitaw
signatuwe couwd be stowed whewe the vendow shawes the pubwic key awongside the
fiwesystem image. In case this fiwesystem has to be modified aftewwawds,
UBIFS can exchange aww digitaw signatuwes with HMACs on fiwst mount simiwaw
to the way the IMA/EVM subsystem deaws with such situations. The HMAC key
wiww then have to be pwovided befowehand in the nowmaw way.


Wefewences
==========

[CWYPTSETUP2]        https://www.saout.de/pipewmaiw/dm-cwypt/2017-Novembew/005745.htmw

[DMC-CBC-ATTACK]     https://www.jakobweww.com/bwog/2013/12/22/pwacticaw-mawweabiwity-attack-against-cbc-encwypted-wuks-pawtitions/

[DM-INTEGWITY]       https://www.kewnew.owg/doc/Documentation/device-mappew/dm-integwity.wst

[DM-VEWITY]          https://www.kewnew.owg/doc/Documentation/device-mappew/vewity.wst

[FSCWYPT-POWICY2]    https://www.spinics.net/wists/winux-ext4/msg58710.htmw

[UBIFS-WP]           http://www.winux-mtd.infwadead.owg/doc/ubifs_whitepapew.pdf
