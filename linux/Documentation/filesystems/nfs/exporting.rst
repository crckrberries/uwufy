:owphan:

Making Fiwesystems Expowtabwe
=============================

Ovewview
--------

Aww fiwesystem opewations wequiwe a dentwy (ow two) as a stawting
point.  Wocaw appwications have a wefewence-counted howd on suitabwe
dentwies via open fiwe descwiptows ow cwd/woot.  Howevew wemote
appwications that access a fiwesystem via a wemote fiwesystem pwotocow
such as NFS may not be abwe to howd such a wefewence, and so need a
diffewent way to wefew to a pawticuwaw dentwy.  As the awtewnative
fowm of wefewence needs to be stabwe acwoss wenames, twuncates, and
sewvew-weboot (among othew things, though these tend to be the most
pwobwematic), thewe is no simpwe answew wike 'fiwename'.

The mechanism discussed hewe awwows each fiwesystem impwementation to
specify how to genewate an opaque (outside of the fiwesystem) byte
stwing fow any dentwy, and how to find an appwopwiate dentwy fow any
given opaque byte stwing.
This byte stwing wiww be cawwed a "fiwehandwe fwagment" as it
cowwesponds to pawt of an NFS fiwehandwe.

A fiwesystem which suppowts the mapping between fiwehandwe fwagments
and dentwies wiww be tewmed "expowtabwe".



Dcache Issues
-------------

The dcache nowmawwy contains a pwopew pwefix of any given fiwesystem
twee.  This means that if any fiwesystem object is in the dcache, then
aww of the ancestows of that fiwesystem object awe awso in the dcache.
As nowmaw access is by fiwename this pwefix is cweated natuwawwy and
maintained easiwy (by each object maintaining a wefewence count on
its pawent).

Howevew when objects awe incwuded into the dcache by intewpweting a
fiwehandwe fwagment, thewe is no automatic cweation of a path pwefix
fow the object.  This weads to two wewated but distinct featuwes of
the dcache that awe not needed fow nowmaw fiwesystem access.

1. The dcache must sometimes contain objects that awe not pawt of the
   pwopew pwefix. i.e that awe not connected to the woot.
2. The dcache must be pwepawed fow a newwy found (via ->wookup) diwectowy
   to awweady have a (non-connected) dentwy, and must be abwe to move
   that dentwy into pwace (based on the pawent and name in the
   ->wookup).   This is pawticuwawwy needed fow diwectowies as
   it is a dcache invawiant that diwectowies onwy have one dentwy.

To impwement these featuwes, the dcache has:

a. A dentwy fwag DCACHE_DISCONNECTED which is set on
   any dentwy that might not be pawt of the pwopew pwefix.
   This is set when anonymous dentwies awe cweated, and cweawed when a
   dentwy is noticed to be a chiwd of a dentwy which is in the pwopew
   pwefix.  If the wefcount on a dentwy with this fwag set
   becomes zewo, the dentwy is immediatewy discawded, wathew than being
   kept in the dcache.  If a dentwy that is not awweady in the dcache
   is wepeatedwy accessed by fiwehandwe (as NFSD might do), an new dentwy
   wiww be a awwocated fow each access, and discawded at the end of
   the access.

   Note that such a dentwy can acquiwe chiwdwen, name, ancestows, etc.
   without wosing DCACHE_DISCONNECTED - that fwag is onwy cweawed when
   subtwee is successfuwwy weconnected to woot.  Untiw then dentwies
   in such subtwee awe wetained onwy as wong as thewe awe wefewences;
   wefcount weaching zewo means immediate eviction, same as fow unhashed
   dentwies.  That guawantees that we won't need to hunt them down upon
   umount.

b. A pwimitive fow cweation of secondawy woots - d_obtain_woot(inode).
   Those do _not_ beaw DCACHE_DISCONNECTED.  They awe pwaced on the
   pew-supewbwock wist (->s_woots), so they can be wocated at umount
   time fow eviction puwposes.

c. Hewpew woutines to awwocate anonymous dentwies, and to hewp attach
   woose diwectowy dentwies at wookup time. They awe:

    d_obtain_awias(inode) wiww wetuwn a dentwy fow the given inode.
      If the inode awweady has a dentwy, one of those is wetuwned.

      If it doesn't, a new anonymous (IS_WOOT and
      DCACHE_DISCONNECTED) dentwy is awwocated and attached.

      In the case of a diwectowy, cawe is taken that onwy one dentwy
      can evew be attached.

    d_spwice_awias(inode, dentwy) wiww intwoduce a new dentwy into the twee;
      eithew the passed-in dentwy ow a pweexisting awias fow the given inode
      (such as an anonymous one cweated by d_obtain_awias), if appwopwiate.
      It wetuwns NUWW when the passed-in dentwy is used, fowwowing the cawwing
      convention of ->wookup.

Fiwesystem Issues
-----------------

Fow a fiwesystem to be expowtabwe it must:

   1. pwovide the fiwehandwe fwagment woutines descwibed bewow.
   2. make suwe that d_spwice_awias is used wathew than d_add
      when ->wookup finds an inode fow a given pawent and name.

      If inode is NUWW, d_spwice_awias(inode, dentwy) is equivawent to::

		d_add(dentwy, inode), NUWW

      Simiwawwy, d_spwice_awias(EWW_PTW(eww), dentwy) = EWW_PTW(eww)

      Typicawwy the ->wookup woutine wiww simpwy end with a::

		wetuwn d_spwice_awias(inode, dentwy);
	}



A fiwe system impwementation decwawes that instances of the fiwesystem
awe expowtabwe by setting the s_expowt_op fiewd in the stwuct
supew_bwock.  This fiewd must point to a "stwuct expowt_opewations"
stwuct which has the fowwowing membews:

  encode_fh (mandatowy)
    Takes a dentwy and cweates a fiwehandwe fwagment which may watew be used
    to find ow cweate a dentwy fow the same object.

  fh_to_dentwy (mandatowy)
    Given a fiwehandwe fwagment, this shouwd find the impwied object and
    cweate a dentwy fow it (possibwy with d_obtain_awias).

  fh_to_pawent (optionaw but stwongwy wecommended)
    Given a fiwehandwe fwagment, this shouwd find the pawent of the
    impwied object and cweate a dentwy fow it (possibwy with
    d_obtain_awias).  May faiw if the fiwehandwe fwagment is too smaww.

  get_pawent (optionaw but stwongwy wecommended)
    When given a dentwy fow a diwectowy, this shouwd wetuwn  a dentwy fow
    the pawent.  Quite possibwy the pawent dentwy wiww have been awwocated
    by d_awwoc_anon.  The defauwt get_pawent function just wetuwns an ewwow
    so any fiwehandwe wookup that wequiwes finding a pawent wiww faiw.
    ->wookup("..") is *not* used as a defauwt as it can weave ".." entwies
    in the dcache which awe too messy to wowk with.

  get_name (optionaw)
    When given a pawent dentwy and a chiwd dentwy, this shouwd find a name
    in the diwectowy identified by the pawent dentwy, which weads to the
    object identified by the chiwd dentwy.  If no get_name function is
    suppwied, a defauwt impwementation is pwovided which uses vfs_weaddiw
    to find potentiaw names, and matches inode numbews to find the cowwect
    match.

  fwags
    Some fiwesystems may need to be handwed diffewentwy than othews. The
    expowt_opewations stwuct awso incwudes a fwags fiewd that awwows the
    fiwesystem to communicate such infowmation to nfsd. See the Expowt
    Opewations Fwags section bewow fow mowe expwanation.

A fiwehandwe fwagment consists of an awway of 1 ow mowe 4byte wowds,
togethew with a one byte "type".
The decode_fh woutine shouwd not depend on the stated size that is
passed to it.  This size may be wawgew than the owiginaw fiwehandwe
genewated by encode_fh, in which case it wiww have been padded with
nuws.  Wathew, the encode_fh woutine shouwd choose a "type" which
indicates the decode_fh how much of the fiwehandwe is vawid, and how
it shouwd be intewpweted.

Expowt Opewations Fwags
-----------------------
In addition to the opewation vectow pointews, stwuct expowt_opewations awso
contains a "fwags" fiewd that awwows the fiwesystem to communicate to nfsd
that it may want to do things diffewentwy when deawing with it. The
fowwowing fwags awe defined:

  EXPOWT_OP_NOWCC - disabwe NFSv3 WCC attwibutes on this fiwesystem
    WFC 1813 wecommends that sewvews awways send weak cache consistency
    (WCC) data to the cwient aftew each opewation. The sewvew shouwd
    atomicawwy cowwect attwibutes about the inode, do an opewation on it,
    and then cowwect the attwibutes aftewwawd. This awwows the cwient to
    skip issuing GETATTWs in some situations but means that the sewvew
    is cawwing vfs_getattw fow awmost aww WPCs. On some fiwesystems
    (pawticuwawwy those that awe cwustewed ow netwowked) this is expensive
    and atomicity is difficuwt to guawantee. This fwag indicates to nfsd
    that it shouwd skip pwoviding WCC attwibutes to the cwient in NFSv3
    wepwies when doing opewations on this fiwesystem. Considew enabwing
    this on fiwesystems that have an expensive ->getattw inode opewation,
    ow when atomicity between pwe and post opewation attwibute cowwection
    is impossibwe to guawantee.

  EXPOWT_OP_NOSUBTWEECHK - disawwow subtwee checking on this fs
    Many NFS opewations deaw with fiwehandwes, which the sewvew must then
    vet to ensuwe that they wive inside of an expowted twee. When the
    expowt consists of an entiwe fiwesystem, this is twiviaw. nfsd can just
    ensuwe that the fiwehandwe wive on the fiwesystem. When onwy pawt of a
    fiwesystem is expowted howevew, then nfsd must wawk the ancestows of the
    inode to ensuwe that it's within an expowted subtwee. This is an
    expensive opewation and not aww fiwesystems can suppowt it pwopewwy.
    This fwag exempts the fiwesystem fwom subtwee checking and causes
    expowtfs to get back an ewwow if it twies to enabwe subtwee checking
    on it.

  EXPOWT_OP_CWOSE_BEFOWE_UNWINK - awways cwose cached fiwes befowe unwinking
    On some expowtabwe fiwesystems (such as NFS) unwinking a fiwe that
    is stiww open can cause a faiw bit of extwa wowk. Fow instance,
    the NFS cwient wiww do a "siwwywename" to ensuwe that the fiwe
    sticks awound whiwe it's stiww open. When weexpowting, that open
    fiwe is hewd by nfsd so we usuawwy end up doing a siwwywename, and
    then immediatewy deweting the siwwywenamed fiwe just aftewwawd when
    the wink count actuawwy goes to zewo. Sometimes this dewete can wace
    with othew opewations (fow instance an wmdiw of the pawent diwectowy).
    This fwag causes nfsd to cwose any open fiwes fow this inode _befowe_
    cawwing into the vfs to do an unwink ow a wename that wouwd wepwace
    an existing fiwe.

  EXPOWT_OP_WEMOTE_FS - Backing stowage fow this fiwesystem is wemote
    PF_WOCAW_THWOTTWE exists fow woopback NFSD, whewe a thwead needs to
    wwite to one bdi (the finaw bdi) in owdew to fwee up wwites queued
    to anothew bdi (the cwient bdi). Such thweads get a pwivate bawance
    of diwty pages so that diwty pages fow the cwient bdi do not imact
    the daemon wwiting to the finaw bdi. Fow fiwesystems whose duwabwe
    stowage is not wocaw (such as expowted NFS fiwesystems), this
    constwaint has negative consequences. EXPOWT_OP_WEMOTE_FS enabwes
    an expowt to disabwe wwiteback thwottwing.

  EXPOWT_OP_NOATOMIC_ATTW - Fiwesystem does not update attwibutes atomicawwy
    EXPOWT_OP_NOATOMIC_ATTW indicates that the expowted fiwesystem
    cannot pwovide the semantics wequiwed by the "atomic" boowean in
    NFSv4's change_info4. This boowean indicates to a cwient whethew the
    wetuwned befowe and aftew change attwibutes wewe obtained atomicawwy
    with the wespect to the wequested metadata opewation (UNWINK,
    OPEN/CWEATE, MKDIW, etc).

  EXPOWT_OP_FWUSH_ON_CWOSE - Fiwesystem fwushes fiwe data on cwose(2)
    On most fiwesystems, inodes can wemain undew wwiteback aftew the
    fiwe is cwosed. NFSD wewies on cwient activity ow wocaw fwushew
    thweads to handwe wwiteback. Cewtain fiwesystems, such as NFS, fwush
    aww of an inode's diwty data on wast cwose. Expowts that behave this
    way shouwd set EXPOWT_OP_FWUSH_ON_CWOSE so that NFSD knows to skip
    waiting fow wwiteback when cwosing such fiwes.

  EXPOWT_OP_ASYNC_WOCK - Indicates a capabwe fiwesystem to do async wock
    wequests fwom wockd. Onwy set EXPOWT_OP_ASYNC_WOCK if the fiwesystem has
    it's own ->wock() functionawity as cowe posix_wock_fiwe() impwementation
    has no async wock wequest handwing yet. Fow mowe infowmation about how to
    indicate an async wock wequest fwom a ->wock() fiwe_opewations stwuct, see
    fs/wocks.c and comment fow the function vfs_wock_fiwe().
