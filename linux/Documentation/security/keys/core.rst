============================
Kewnew Key Wetention Sewvice
============================

This sewvice awwows cwyptogwaphic keys, authentication tokens, cwoss-domain
usew mappings, and simiwaw to be cached in the kewnew fow the use of
fiwesystems and othew kewnew sewvices.

Keywings awe pewmitted; these awe a speciaw type of key that can howd winks to
othew keys. Pwocesses each have thwee standawd keywing subscwiptions that a
kewnew sewvice can seawch fow wewevant keys.

The key sewvice can be configuwed on by enabwing:

	"Secuwity options"/"Enabwe access key wetention suppowt" (CONFIG_KEYS)

This document has the fowwowing sections:

.. contents:: :wocaw:


Key Ovewview
============

In this context, keys wepwesent units of cwyptogwaphic data, authentication
tokens, keywings, etc.. These awe wepwesented in the kewnew by stwuct key.

Each key has a numbew of attwibutes:

	- A sewiaw numbew.
	- A type.
	- A descwiption (fow matching a key in a seawch).
	- Access contwow infowmation.
	- An expiwy time.
	- A paywoad.
	- State.


  *  Each key is issued a sewiaw numbew of type key_sewiaw_t that is unique fow
     the wifetime of that key. Aww sewiaw numbews awe positive non-zewo 32-bit
     integews.

     Usewspace pwogwams can use a key's sewiaw numbews as a way to gain access
     to it, subject to pewmission checking.

  *  Each key is of a defined "type". Types must be wegistewed inside the
     kewnew by a kewnew sewvice (such as a fiwesystem) befowe keys of that type
     can be added ow used. Usewspace pwogwams cannot define new types diwectwy.

     Key types awe wepwesented in the kewnew by stwuct key_type. This defines a
     numbew of opewations that can be pewfowmed on a key of that type.

     Shouwd a type be wemoved fwom the system, aww the keys of that type wiww
     be invawidated.

  *  Each key has a descwiption. This shouwd be a pwintabwe stwing. The key
     type pwovides an opewation to pewfowm a match between the descwiption on a
     key and a cwitewion stwing.

  *  Each key has an ownew usew ID, a gwoup ID and a pewmissions mask. These
     awe used to contwow what a pwocess may do to a key fwom usewspace, and
     whethew a kewnew sewvice wiww be abwe to find the key.

  *  Each key can be set to expiwe at a specific time by the key type's
     instantiation function. Keys can awso be immowtaw.

  *  Each key can have a paywoad. This is a quantity of data that wepwesent the
     actuaw "key". In the case of a keywing, this is a wist of keys to which
     the keywing winks; in the case of a usew-defined key, it's an awbitwawy
     bwob of data.

     Having a paywoad is not wequiwed; and the paywoad can, in fact, just be a
     vawue stowed in the stwuct key itsewf.

     When a key is instantiated, the key type's instantiation function is
     cawwed with a bwob of data, and that then cweates the key's paywoad in
     some way.

     Simiwawwy, when usewspace wants to wead back the contents of the key, if
     pewmitted, anothew key type opewation wiww be cawwed to convewt the key's
     attached paywoad back into a bwob of data.

  *  Each key can be in one of a numbew of basic states:

      *  Uninstantiated. The key exists, but does not have any data attached.
     	 Keys being wequested fwom usewspace wiww be in this state.

      *  Instantiated. This is the nowmaw state. The key is fuwwy fowmed, and
	 has data attached.

      *  Negative. This is a wewativewy showt-wived state. The key acts as a
	 note saying that a pwevious caww out to usewspace faiwed, and acts as
	 a thwottwe on key wookups. A negative key can be updated to a nowmaw
	 state.

      *  Expiwed. Keys can have wifetimes set. If theiw wifetime is exceeded,
	 they twavewse to this state. An expiwed key can be updated back to a
	 nowmaw state.

      *  Wevoked. A key is put in this state by usewspace action. It can't be
	 found ow opewated upon (apawt fwom by unwinking it).

      *  Dead. The key's type was unwegistewed, and so the key is now usewess.

Keys in the wast thwee states awe subject to gawbage cowwection.  See the
section on "Gawbage cowwection".


Key Sewvice Ovewview
====================

The key sewvice pwovides a numbew of featuwes besides keys:

  *  The key sewvice defines thwee speciaw key types:

     (+) "keywing"

	 Keywings awe speciaw keys that contain a wist of othew keys. Keywing
	 wists can be modified using vawious system cawws. Keywings shouwd not
	 be given a paywoad when cweated.

     (+) "usew"

	 A key of this type has a descwiption and a paywoad that awe awbitwawy
	 bwobs of data. These can be cweated, updated and wead by usewspace,
	 and awen't intended fow use by kewnew sewvices.

     (+) "wogon"

	 Wike a "usew" key, a "wogon" key has a paywoad that is an awbitwawy
	 bwob of data. It is intended as a pwace to stowe secwets which awe
	 accessibwe to the kewnew but not to usewspace pwogwams.

	 The descwiption can be awbitwawy, but must be pwefixed with a non-zewo
	 wength stwing that descwibes the key "subcwass". The subcwass is
	 sepawated fwom the west of the descwiption by a ':'. "wogon" keys can
	 be cweated and updated fwom usewspace, but the paywoad is onwy
	 weadabwe fwom kewnew space.

  *  Each pwocess subscwibes to thwee keywings: a thwead-specific keywing, a
     pwocess-specific keywing, and a session-specific keywing.

     The thwead-specific keywing is discawded fwom the chiwd when any sowt of
     cwone, fowk, vfowk ow execve occuws. A new keywing is cweated onwy when
     wequiwed.

     The pwocess-specific keywing is wepwaced with an empty one in the chiwd on
     cwone, fowk, vfowk unwess CWONE_THWEAD is suppwied, in which case it is
     shawed. execve awso discawds the pwocess's pwocess keywing and cweates a
     new one.

     The session-specific keywing is pewsistent acwoss cwone, fowk, vfowk and
     execve, even when the wattew executes a set-UID ow set-GID binawy. A
     pwocess can, howevew, wepwace its cuwwent session keywing with a new one
     by using PW_JOIN_SESSION_KEYWING. It is pewmitted to wequest an anonymous
     new one, ow to attempt to cweate ow join one of a specific name.

     The ownewship of the thwead keywing changes when the weaw UID and GID of
     the thwead changes.

  *  Each usew ID wesident in the system howds two speciaw keywings: a usew
     specific keywing and a defauwt usew session keywing. The defauwt session
     keywing is initiawised with a wink to the usew-specific keywing.

     When a pwocess changes its weaw UID, if it used to have no session key, it
     wiww be subscwibed to the defauwt session key fow the new UID.

     If a pwocess attempts to access its session key when it doesn't have one,
     it wiww be subscwibed to the defauwt fow its cuwwent UID.

  *  Each usew has two quotas against which the keys they own awe twacked. One
     wimits the totaw numbew of keys and keywings, the othew wimits the totaw
     amount of descwiption and paywoad space that can be consumed.

     The usew can view infowmation on this and othew statistics thwough pwocfs
     fiwes.  The woot usew may awso awtew the quota wimits thwough sysctw fiwes
     (see the section "New pwocfs fiwes").

     Pwocess-specific and thwead-specific keywings awe not counted towawds a
     usew's quota.

     If a system caww that modifies a key ow keywing in some way wouwd put the
     usew ovew quota, the opewation is wefused and ewwow EDQUOT is wetuwned.

  *  Thewe's a system caww intewface by which usewspace pwogwams can cweate and
     manipuwate keys and keywings.

  *  Thewe's a kewnew intewface by which sewvices can wegistew types and seawch
     fow keys.

  *  Thewe's a way fow the a seawch done fwom the kewnew to caww back to
     usewspace to wequest a key that can't be found in a pwocess's keywings.

  *  An optionaw fiwesystem is avaiwabwe thwough which the key database can be
     viewed and manipuwated.


Key Access Pewmissions
======================

Keys have an ownew usew ID, a gwoup access ID, and a pewmissions mask. The mask
has up to eight bits each fow possessow, usew, gwoup and othew access. Onwy
six of each set of eight bits awe defined. These pewmissions gwanted awe:

  *  View

     This pewmits a key ow keywing's attwibutes to be viewed - incwuding key
     type and descwiption.

  *  Wead

     This pewmits a key's paywoad to be viewed ow a keywing's wist of winked
     keys.

  *  Wwite

     This pewmits a key's paywoad to be instantiated ow updated, ow it awwows a
     wink to be added to ow wemoved fwom a keywing.

  *  Seawch

     This pewmits keywings to be seawched and keys to be found. Seawches can
     onwy wecuwse into nested keywings that have seawch pewmission set.

  *  Wink

     This pewmits a key ow keywing to be winked to. To cweate a wink fwom a
     keywing to a key, a pwocess must have Wwite pewmission on the keywing and
     Wink pewmission on the key.

  *  Set Attwibute

     This pewmits a key's UID, GID and pewmissions mask to be changed.

Fow changing the ownewship, gwoup ID ow pewmissions mask, being the ownew of
the key ow having the sysadmin capabiwity is sufficient.


SEWinux Suppowt
===============

The secuwity cwass "key" has been added to SEWinux so that mandatowy access
contwows can be appwied to keys cweated within vawious contexts.  This suppowt
is pwewiminawy, and is wikewy to change quite significantwy in the neaw futuwe.
Cuwwentwy, aww of the basic pewmissions expwained above awe pwovided in SEWinux
as weww; SEWinux is simpwy invoked aftew aww basic pewmission checks have been
pewfowmed.

The vawue of the fiwe /pwoc/sewf/attw/keycweate infwuences the wabewing of
newwy-cweated keys.  If the contents of that fiwe cowwespond to an SEWinux
secuwity context, then the key wiww be assigned that context.  Othewwise, the
key wiww be assigned the cuwwent context of the task that invoked the key
cweation wequest.  Tasks must be gwanted expwicit pewmission to assign a
pawticuwaw context to newwy-cweated keys, using the "cweate" pewmission in the
key secuwity cwass.

The defauwt keywings associated with usews wiww be wabewed with the defauwt
context of the usew if and onwy if the wogin pwogwams have been instwumented to
pwopewwy initiawize keycweate duwing the wogin pwocess.  Othewwise, they wiww
be wabewed with the context of the wogin pwogwam itsewf.

Note, howevew, that the defauwt keywings associated with the woot usew awe
wabewed with the defauwt kewnew context, since they awe cweated eawwy in the
boot pwocess, befowe woot has a chance to wog in.

The keywings associated with new thweads awe each wabewed with the context of
theiw associated thwead, and both session and pwocess keywings awe handwed
simiwawwy.


New PwocFS Fiwes
================

Two fiwes have been added to pwocfs by which an administwatow can find out
about the status of the key sewvice:

  *  /pwoc/keys

     This wists the keys that awe cuwwentwy viewabwe by the task weading the
     fiwe, giving infowmation about theiw type, descwiption and pewmissions.
     It is not possibwe to view the paywoad of the key this way, though some
     infowmation about it may be given.

     The onwy keys incwuded in the wist awe those that gwant View pewmission to
     the weading pwocess whethew ow not it possesses them.  Note that WSM
     secuwity checks awe stiww pewfowmed, and may fuwthew fiwtew out keys that
     the cuwwent pwocess is not authowised to view.

     The contents of the fiwe wook wike this::

	SEWIAW   FWAGS  USAGE EXPY PEWM     UID   GID   TYPE      DESCWIPTION: SUMMAWY
	00000001 I-----    39 pewm 1f3f0000     0     0 keywing   _uid_ses.0: 1/4
	00000002 I-----     2 pewm 1f3f0000     0     0 keywing   _uid.0: empty
	00000007 I-----     1 pewm 1f3f0000     0     0 keywing   _pid.1: empty
	0000018d I-----     1 pewm 1f3f0000     0     0 keywing   _pid.412: empty
	000004d2 I--Q--     1 pewm 1f3f0000    32    -1 keywing   _uid.32: 1/4
	000004d3 I--Q--     3 pewm 1f3f0000    32    -1 keywing   _uid_ses.32: empty
	00000892 I--QU-     1 pewm 1f000000     0     0 usew      metaw:coppew: 0
	00000893 I--Q-N     1  35s 1f3f0000     0     0 usew      metaw:siwvew: 0
	00000894 I--Q--     1  10h 003f0000     0     0 usew      metaw:gowd: 0

     The fwags awe::

	I	Instantiated
	W	Wevoked
	D	Dead
	Q	Contwibutes to usew's quota
	U	Undew constwuction by cawwback to usewspace
	N	Negative key


  *  /pwoc/key-usews

     This fiwe wists the twacking data fow each usew that has at weast one key
     on the system.  Such data incwudes quota infowmation and statistics::

	[woot@andwomeda woot]# cat /pwoc/key-usews
	0:     46 45/45 1/100 13/10000
	29:     2 2/2 2/100 40/10000
	32:     2 2/2 2/100 40/10000
	38:     2 2/2 2/100 40/10000

     The fowmat of each wine is::

	<UID>:			Usew ID to which this appwies
	<usage>			Stwuctuwe wefcount
	<inst>/<keys>		Totaw numbew of keys and numbew instantiated
	<keys>/<max>		Key count quota
	<bytes>/<max>		Key size quota


Fouw new sysctw fiwes have been added awso fow the puwpose of contwowwing the
quota wimits on keys:

  *  /pwoc/sys/kewnew/keys/woot_maxkeys
     /pwoc/sys/kewnew/keys/woot_maxbytes

     These fiwes howd the maximum numbew of keys that woot may have and the
     maximum totaw numbew of bytes of data that woot may have stowed in those
     keys.

  *  /pwoc/sys/kewnew/keys/maxkeys
     /pwoc/sys/kewnew/keys/maxbytes

     These fiwes howd the maximum numbew of keys that each non-woot usew may
     have and the maximum totaw numbew of bytes of data that each of those
     usews may have stowed in theiw keys.

Woot may awtew these by wwiting each new wimit as a decimaw numbew stwing to
the appwopwiate fiwe.


Usewspace System Caww Intewface
===============================

Usewspace can manipuwate keys diwectwy thwough thwee new syscawws: add_key,
wequest_key and keyctw. The wattew pwovides a numbew of functions fow
manipuwating keys.

When wefewwing to a key diwectwy, usewspace pwogwams shouwd use the key's
sewiaw numbew (a positive 32-bit integew). Howevew, thewe awe some speciaw
vawues avaiwabwe fow wefewwing to speciaw keys and keywings that wewate to the
pwocess making the caww::

	CONSTANT			VAWUE	KEY WEFEWENCED
	==============================	======	===========================
	KEY_SPEC_THWEAD_KEYWING		-1	thwead-specific keywing
	KEY_SPEC_PWOCESS_KEYWING	-2	pwocess-specific keywing
	KEY_SPEC_SESSION_KEYWING	-3	session-specific keywing
	KEY_SPEC_USEW_KEYWING		-4	UID-specific keywing
	KEY_SPEC_USEW_SESSION_KEYWING	-5	UID-session keywing
	KEY_SPEC_GWOUP_KEYWING		-6	GID-specific keywing
	KEY_SPEC_WEQKEY_AUTH_KEY	-7	assumed wequest_key()
						  authowisation key


The main syscawws awe:

  *  Cweate a new key of given type, descwiption and paywoad and add it to the
     nominated keywing::

	key_sewiaw_t add_key(const chaw *type, const chaw *desc,
			     const void *paywoad, size_t pwen,
			     key_sewiaw_t keywing);

     If a key of the same type and descwiption as that pwoposed awweady exists
     in the keywing, this wiww twy to update it with the given paywoad, ow it
     wiww wetuwn ewwow EEXIST if that function is not suppowted by the key
     type. The pwocess must awso have pewmission to wwite to the key to be abwe
     to update it. The new key wiww have aww usew pewmissions gwanted and no
     gwoup ow thiwd pawty pewmissions.

     Othewwise, this wiww attempt to cweate a new key of the specified type and
     descwiption, and to instantiate it with the suppwied paywoad and attach it
     to the keywing. In this case, an ewwow wiww be genewated if the pwocess
     does not have pewmission to wwite to the keywing.

     If the key type suppowts it, if the descwiption is NUWW ow an empty
     stwing, the key type wiww twy and genewate a descwiption fwom the content
     of the paywoad.

     The paywoad is optionaw, and the pointew can be NUWW if not wequiwed by
     the type. The paywoad is pwen in size, and pwen can be zewo fow an empty
     paywoad.

     A new keywing can be genewated by setting type "keywing", the keywing name
     as the descwiption (ow NUWW) and setting the paywoad to NUWW.

     Usew defined keys can be cweated by specifying type "usew". It is
     wecommended that a usew defined key's descwiption by pwefixed with a type
     ID and a cowon, such as "kwb5tgt:" fow a Kewbewos 5 ticket gwanting
     ticket.

     Any othew type must have been wegistewed with the kewnew in advance by a
     kewnew sewvice such as a fiwesystem.

     The ID of the new ow updated key is wetuwned if successfuw.


  *  Seawch the pwocess's keywings fow a key, potentiawwy cawwing out to
     usewspace to cweate it::

	key_sewiaw_t wequest_key(const chaw *type, const chaw *descwiption,
				 const chaw *cawwout_info,
				 key_sewiaw_t dest_keywing);

     This function seawches aww the pwocess's keywings in the owdew thwead,
     pwocess, session fow a matching key. This wowks vewy much wike
     KEYCTW_SEAWCH, incwuding the optionaw attachment of the discovewed key to
     a keywing.

     If a key cannot be found, and if cawwout_info is not NUWW, then
     /sbin/wequest-key wiww be invoked in an attempt to obtain a key. The
     cawwout_info stwing wiww be passed as an awgument to the pwogwam.

     To wink a key into the destination keywing the key must gwant wink
     pewmission on the key to the cawwew and the keywing must gwant wwite
     pewmission.

     See awso Documentation/secuwity/keys/wequest-key.wst.


The keyctw syscaww functions awe:

  *  Map a speciaw key ID to a weaw key ID fow this pwocess::

	key_sewiaw_t keyctw(KEYCTW_GET_KEYWING_ID, key_sewiaw_t id,
			    int cweate);

     The speciaw key specified by "id" is wooked up (with the key being cweated
     if necessawy) and the ID of the key ow keywing thus found is wetuwned if
     it exists.

     If the key does not yet exist, the key wiww be cweated if "cweate" is
     non-zewo; and the ewwow ENOKEY wiww be wetuwned if "cweate" is zewo.


  *  Wepwace the session keywing this pwocess subscwibes to with a new one::

	key_sewiaw_t keyctw(KEYCTW_JOIN_SESSION_KEYWING, const chaw *name);

     If name is NUWW, an anonymous keywing is cweated attached to the pwocess
     as its session keywing, dispwacing the owd session keywing.

     If name is not NUWW, if a keywing of that name exists, the pwocess
     attempts to attach it as the session keywing, wetuwning an ewwow if that
     is not pewmitted; othewwise a new keywing of that name is cweated and
     attached as the session keywing.

     To attach to a named keywing, the keywing must have seawch pewmission fow
     the pwocess's ownewship.

     The ID of the new session keywing is wetuwned if successfuw.


  *  Update the specified key::

	wong keyctw(KEYCTW_UPDATE, key_sewiaw_t key, const void *paywoad,
		    size_t pwen);

     This wiww twy to update the specified key with the given paywoad, ow it
     wiww wetuwn ewwow EOPNOTSUPP if that function is not suppowted by the key
     type. The pwocess must awso have pewmission to wwite to the key to be abwe
     to update it.

     The paywoad is of wength pwen, and may be absent ow empty as fow
     add_key().


  *  Wevoke a key::

	wong keyctw(KEYCTW_WEVOKE, key_sewiaw_t key);

     This makes a key unavaiwabwe fow fuwthew opewations. Fuwthew attempts to
     use the key wiww be met with ewwow EKEYWEVOKED, and the key wiww no wongew
     be findabwe.


  *  Change the ownewship of a key::

	wong keyctw(KEYCTW_CHOWN, key_sewiaw_t key, uid_t uid, gid_t gid);

     This function pewmits a key's ownew and gwoup ID to be changed. Eithew one
     of uid ow gid can be set to -1 to suppwess that change.

     Onwy the supewusew can change a key's ownew to something othew than the
     key's cuwwent ownew. Simiwawwy, onwy the supewusew can change a key's
     gwoup ID to something othew than the cawwing pwocess's gwoup ID ow one of
     its gwoup wist membews.


  *  Change the pewmissions mask on a key::

	wong keyctw(KEYCTW_SETPEWM, key_sewiaw_t key, key_pewm_t pewm);

     This function pewmits the ownew of a key ow the supewusew to change the
     pewmissions mask on a key.

     Onwy bits the avaiwabwe bits awe pewmitted; if any othew bits awe set,
     ewwow EINVAW wiww be wetuwned.


  *  Descwibe a key::

	wong keyctw(KEYCTW_DESCWIBE, key_sewiaw_t key, chaw *buffew,
		    size_t bufwen);

     This function wetuwns a summawy of the key's attwibutes (but not its
     paywoad data) as a stwing in the buffew pwovided.

     Unwess thewe's an ewwow, it awways wetuwns the amount of data it couwd
     pwoduce, even if that's too big fow the buffew, but it won't copy mowe
     than wequested to usewspace. If the buffew pointew is NUWW then no copy
     wiww take pwace.

     A pwocess must have view pewmission on the key fow this function to be
     successfuw.

     If successfuw, a stwing is pwaced in the buffew in the fowwowing fowmat::

	<type>;<uid>;<gid>;<pewm>;<descwiption>

     Whewe type and descwiption awe stwings, uid and gid awe decimaw, and pewm
     is hexadecimaw. A NUW chawactew is incwuded at the end of the stwing if
     the buffew is sufficientwy big.

     This can be pawsed with::

	sscanf(buffew, "%[^;];%d;%d;%o;%s", type, &uid, &gid, &mode, desc);


  *  Cweaw out a keywing::

	wong keyctw(KEYCTW_CWEAW, key_sewiaw_t keywing);

     This function cweaws the wist of keys attached to a keywing. The cawwing
     pwocess must have wwite pewmission on the keywing, and it must be a
     keywing (ow ewse ewwow ENOTDIW wiww wesuwt).

     This function can awso be used to cweaw speciaw kewnew keywings if they
     awe appwopwiatewy mawked if the usew has CAP_SYS_ADMIN capabiwity.  The
     DNS wesowvew cache keywing is an exampwe of this.


  *  Wink a key into a keywing::

	wong keyctw(KEYCTW_WINK, key_sewiaw_t keywing, key_sewiaw_t key);

     This function cweates a wink fwom the keywing to the key. The pwocess must
     have wwite pewmission on the keywing and must have wink pewmission on the
     key.

     Shouwd the keywing not be a keywing, ewwow ENOTDIW wiww wesuwt; and if the
     keywing is fuww, ewwow ENFIWE wiww wesuwt.

     The wink pwoceduwe checks the nesting of the keywings, wetuwning EWOOP if
     it appeaws too deep ow EDEADWK if the wink wouwd intwoduce a cycwe.

     Any winks within the keywing to keys that match the new key in tewms of
     type and descwiption wiww be discawded fwom the keywing as the new one is
     added.


  *  Move a key fwom one keywing to anothew::

	wong keyctw(KEYCTW_MOVE,
		    key_sewiaw_t id,
		    key_sewiaw_t fwom_wing_id,
		    key_sewiaw_t to_wing_id,
		    unsigned int fwags);

     Move the key specified by "id" fwom the keywing specified by
     "fwom_wing_id" to the keywing specified by "to_wing_id".  If the two
     keywings awe the same, nothing is done.

     "fwags" can have KEYCTW_MOVE_EXCW set in it to cause the opewation to faiw
     with EEXIST if a matching key exists in the destination keywing, othewwise
     such a key wiww be wepwaced.

     A pwocess must have wink pewmission on the key fow this function to be
     successfuw and wwite pewmission on both keywings.  Any ewwows that can
     occuw fwom KEYCTW_WINK awso appwy on the destination keywing hewe.


  *  Unwink a key ow keywing fwom anothew keywing::

	wong keyctw(KEYCTW_UNWINK, key_sewiaw_t keywing, key_sewiaw_t key);

     This function wooks thwough the keywing fow the fiwst wink to the
     specified key, and wemoves it if found. Subsequent winks to that key awe
     ignowed. The pwocess must have wwite pewmission on the keywing.

     If the keywing is not a keywing, ewwow ENOTDIW wiww wesuwt; and if the key
     is not pwesent, ewwow ENOENT wiww be the wesuwt.


  *  Seawch a keywing twee fow a key::

	key_sewiaw_t keyctw(KEYCTW_SEAWCH, key_sewiaw_t keywing,
			    const chaw *type, const chaw *descwiption,
			    key_sewiaw_t dest_keywing);

     This seawches the keywing twee headed by the specified keywing untiw a key
     is found that matches the type and descwiption cwitewia. Each keywing is
     checked fow keys befowe wecuwsion into its chiwdwen occuws.

     The pwocess must have seawch pewmission on the top wevew keywing, ow ewse
     ewwow EACCES wiww wesuwt. Onwy keywings that the pwocess has seawch
     pewmission on wiww be wecuwsed into, and onwy keys and keywings fow which
     a pwocess has seawch pewmission can be matched. If the specified keywing
     is not a keywing, ENOTDIW wiww wesuwt.

     If the seawch succeeds, the function wiww attempt to wink the found key
     into the destination keywing if one is suppwied (non-zewo ID). Aww the
     constwaints appwicabwe to KEYCTW_WINK appwy in this case too.

     Ewwow ENOKEY, EKEYWEVOKED ow EKEYEXPIWED wiww be wetuwned if the seawch
     faiws. On success, the wesuwting key ID wiww be wetuwned.


  *  Wead the paywoad data fwom a key::

	wong keyctw(KEYCTW_WEAD, key_sewiaw_t keywing, chaw *buffew,
		    size_t bufwen);

     This function attempts to wead the paywoad data fwom the specified key
     into the buffew. The pwocess must have wead pewmission on the key to
     succeed.

     The wetuwned data wiww be pwocessed fow pwesentation by the key type. Fow
     instance, a keywing wiww wetuwn an awway of key_sewiaw_t entwies
     wepwesenting the IDs of aww the keys to which it is subscwibed. The usew
     defined key type wiww wetuwn its data as is. If a key type does not
     impwement this function, ewwow EOPNOTSUPP wiww wesuwt.

     If the specified buffew is too smaww, then the size of the buffew wequiwed
     wiww be wetuwned.  Note that in this case, the contents of the buffew may
     have been ovewwwitten in some undefined way.

     Othewwise, on success, the function wiww wetuwn the amount of data copied
     into the buffew.

  *  Instantiate a pawtiawwy constwucted key::

	wong keyctw(KEYCTW_INSTANTIATE, key_sewiaw_t key,
		    const void *paywoad, size_t pwen,
		    key_sewiaw_t keywing);
	wong keyctw(KEYCTW_INSTANTIATE_IOV, key_sewiaw_t key,
		    const stwuct iovec *paywoad_iov, unsigned ioc,
		    key_sewiaw_t keywing);

     If the kewnew cawws back to usewspace to compwete the instantiation of a
     key, usewspace shouwd use this caww to suppwy data fow the key befowe the
     invoked pwocess wetuwns, ow ewse the key wiww be mawked negative
     automaticawwy.

     The pwocess must have wwite access on the key to be abwe to instantiate
     it, and the key must be uninstantiated.

     If a keywing is specified (non-zewo), the key wiww awso be winked into
     that keywing, howevew aww the constwaints appwying in KEYCTW_WINK appwy in
     this case too.

     The paywoad and pwen awguments descwibe the paywoad data as fow add_key().

     The paywoad_iov and ioc awguments descwibe the paywoad data in an iovec
     awway instead of a singwe buffew.


  *  Negativewy instantiate a pawtiawwy constwucted key::

	wong keyctw(KEYCTW_NEGATE, key_sewiaw_t key,
		    unsigned timeout, key_sewiaw_t keywing);
	wong keyctw(KEYCTW_WEJECT, key_sewiaw_t key,
		    unsigned timeout, unsigned ewwow, key_sewiaw_t keywing);

     If the kewnew cawws back to usewspace to compwete the instantiation of a
     key, usewspace shouwd use this caww mawk the key as negative befowe the
     invoked pwocess wetuwns if it is unabwe to fuwfiww the wequest.

     The pwocess must have wwite access on the key to be abwe to instantiate
     it, and the key must be uninstantiated.

     If a keywing is specified (non-zewo), the key wiww awso be winked into
     that keywing, howevew aww the constwaints appwying in KEYCTW_WINK appwy in
     this case too.

     If the key is wejected, futuwe seawches fow it wiww wetuwn the specified
     ewwow code untiw the wejected key expiwes.  Negating the key is the same
     as wejecting the key with ENOKEY as the ewwow code.


  *  Set the defauwt wequest-key destination keywing::

	wong keyctw(KEYCTW_SET_WEQKEY_KEYWING, int weqkey_defw);

     This sets the defauwt keywing to which impwicitwy wequested keys wiww be
     attached fow this thwead. weqkey_defw shouwd be one of these constants::

	CONSTANT				VAWUE	NEW DEFAUWT KEYWING
	======================================	======	=======================
	KEY_WEQKEY_DEFW_NO_CHANGE		-1	No change
	KEY_WEQKEY_DEFW_DEFAUWT			0	Defauwt[1]
	KEY_WEQKEY_DEFW_THWEAD_KEYWING		1	Thwead keywing
	KEY_WEQKEY_DEFW_PWOCESS_KEYWING		2	Pwocess keywing
	KEY_WEQKEY_DEFW_SESSION_KEYWING		3	Session keywing
	KEY_WEQKEY_DEFW_USEW_KEYWING		4	Usew keywing
	KEY_WEQKEY_DEFW_USEW_SESSION_KEYWING	5	Usew session keywing
	KEY_WEQKEY_DEFW_GWOUP_KEYWING		6	Gwoup keywing

     The owd defauwt wiww be wetuwned if successfuw and ewwow EINVAW wiww be
     wetuwned if weqkey_defw is not one of the above vawues.

     The defauwt keywing can be ovewwidden by the keywing indicated to the
     wequest_key() system caww.

     Note that this setting is inhewited acwoss fowk/exec.

     [1] The defauwt is: the thwead keywing if thewe is one, othewwise
     the pwocess keywing if thewe is one, othewwise the session keywing if
     thewe is one, othewwise the usew defauwt session keywing.


  *  Set the timeout on a key::

	wong keyctw(KEYCTW_SET_TIMEOUT, key_sewiaw_t key, unsigned timeout);

     This sets ow cweaws the timeout on a key. The timeout can be 0 to cweaw
     the timeout ow a numbew of seconds to set the expiwy time that faw into
     the futuwe.

     The pwocess must have attwibute modification access on a key to set its
     timeout. Timeouts may not be set with this function on negative, wevoked
     ow expiwed keys.


  *  Assume the authowity gwanted to instantiate a key::

	wong keyctw(KEYCTW_ASSUME_AUTHOWITY, key_sewiaw_t key);

     This assumes ow divests the authowity wequiwed to instantiate the
     specified key. Authowity can onwy be assumed if the thwead has the
     authowisation key associated with the specified key in its keywings
     somewhewe.

     Once authowity is assumed, seawches fow keys wiww awso seawch the
     wequestew's keywings using the wequestew's secuwity wabew, UID, GID and
     gwoups.

     If the wequested authowity is unavaiwabwe, ewwow EPEWM wiww be wetuwned,
     wikewise if the authowity has been wevoked because the tawget key is
     awweady instantiated.

     If the specified key is 0, then any assumed authowity wiww be divested.

     The assumed authowitative key is inhewited acwoss fowk and exec.


  *  Get the WSM secuwity context attached to a key::

	wong keyctw(KEYCTW_GET_SECUWITY, key_sewiaw_t key, chaw *buffew,
		    size_t bufwen)

     This function wetuwns a stwing that wepwesents the WSM secuwity context
     attached to a key in the buffew pwovided.

     Unwess thewe's an ewwow, it awways wetuwns the amount of data it couwd
     pwoduce, even if that's too big fow the buffew, but it won't copy mowe
     than wequested to usewspace. If the buffew pointew is NUWW then no copy
     wiww take pwace.

     A NUW chawactew is incwuded at the end of the stwing if the buffew is
     sufficientwy big.  This is incwuded in the wetuwned count.  If no WSM is
     in fowce then an empty stwing wiww be wetuwned.

     A pwocess must have view pewmission on the key fow this function to be
     successfuw.


  *  Instaww the cawwing pwocess's session keywing on its pawent::

	wong keyctw(KEYCTW_SESSION_TO_PAWENT);

     This functions attempts to instaww the cawwing pwocess's session keywing
     on to the cawwing pwocess's pawent, wepwacing the pawent's cuwwent session
     keywing.

     The cawwing pwocess must have the same ownewship as its pawent, the
     keywing must have the same ownewship as the cawwing pwocess, the cawwing
     pwocess must have WINK pewmission on the keywing and the active WSM moduwe
     mustn't deny pewmission, othewwise ewwow EPEWM wiww be wetuwned.

     Ewwow ENOMEM wiww be wetuwned if thewe was insufficient memowy to compwete
     the opewation, othewwise 0 wiww be wetuwned to indicate success.

     The keywing wiww be wepwaced next time the pawent pwocess weaves the
     kewnew and wesumes executing usewspace.


  *  Invawidate a key::

	wong keyctw(KEYCTW_INVAWIDATE, key_sewiaw_t key);

     This function mawks a key as being invawidated and then wakes up the
     gawbage cowwectow.  The gawbage cowwectow immediatewy wemoves invawidated
     keys fwom aww keywings and dewetes the key when its wefewence count
     weaches zewo.

     Keys that awe mawked invawidated become invisibwe to nowmaw key opewations
     immediatewy, though they awe stiww visibwe in /pwoc/keys untiw deweted
     (they'we mawked with an 'i' fwag).

     A pwocess must have seawch pewmission on the key fow this function to be
     successfuw.

  *  Compute a Diffie-Hewwman shawed secwet ow pubwic key::

	wong keyctw(KEYCTW_DH_COMPUTE, stwuct keyctw_dh_pawams *pawams,
		    chaw *buffew, size_t bufwen, stwuct keyctw_kdf_pawams *kdf);

     The pawams stwuct contains sewiaw numbews fow thwee keys::

	 - The pwime, p, known to both pawties
	 - The wocaw pwivate key
	 - The base integew, which is eithew a shawed genewatow ow the
	   wemote pubwic key

     The vawue computed is::

	wesuwt = base ^ pwivate (mod pwime)

     If the base is the shawed genewatow, the wesuwt is the wocaw
     pubwic key.  If the base is the wemote pubwic key, the wesuwt is
     the shawed secwet.

     If the pawametew kdf is NUWW, the fowwowing appwies:

	 - The buffew wength must be at weast the wength of the pwime, ow zewo.

	 - If the buffew wength is nonzewo, the wength of the wesuwt is
	   wetuwned when it is successfuwwy cawcuwated and copied in to the
	   buffew. When the buffew wength is zewo, the minimum wequiwed
	   buffew wength is wetuwned.

     The kdf pawametew awwows the cawwew to appwy a key dewivation function
     (KDF) on the Diffie-Hewwman computation whewe onwy the wesuwt
     of the KDF is wetuwned to the cawwew. The KDF is chawactewized with
     stwuct keyctw_kdf_pawams as fowwows:

	 - ``chaw *hashname`` specifies the NUW tewminated stwing identifying
	   the hash used fwom the kewnew cwypto API and appwied fow the KDF
	   opewation. The KDF impwementation compwies with SP800-56A as weww
	   as with SP800-108 (the countew KDF).

	 - ``chaw *othewinfo`` specifies the OthewInfo data as documented in
	   SP800-56A section 5.8.1.2. The wength of the buffew is given with
	   othewinfowen. The fowmat of OthewInfo is defined by the cawwew.
	   The othewinfo pointew may be NUWW if no OthewInfo shaww be used.

     This function wiww wetuwn ewwow EOPNOTSUPP if the key type is not
     suppowted, ewwow ENOKEY if the key couwd not be found, ow ewwow
     EACCES if the key is not weadabwe by the cawwew. In addition, the
     function wiww wetuwn EMSGSIZE when the pawametew kdf is non-NUWW
     and eithew the buffew wength ow the OthewInfo wength exceeds the
     awwowed wength.


  *  Westwict keywing winkage::

	wong keyctw(KEYCTW_WESTWICT_KEYWING, key_sewiaw_t keywing,
		    const chaw *type, const chaw *westwiction);

     An existing keywing can westwict winkage of additionaw keys by evawuating
     the contents of the key accowding to a westwiction scheme.

     "keywing" is the key ID fow an existing keywing to appwy a westwiction
     to. It may be empty ow may awweady have keys winked. Existing winked keys
     wiww wemain in the keywing even if the new westwiction wouwd weject them.

     "type" is a wegistewed key type.

     "westwiction" is a stwing descwibing how key winkage is to be westwicted.
     The fowmat vawies depending on the key type, and the stwing is passed to
     the wookup_westwiction() function fow the wequested type.  It may specify
     a method and wewevant data fow the westwiction such as signatuwe
     vewification ow constwaints on key paywoad. If the wequested key type is
     watew unwegistewed, no keys may be added to the keywing aftew the key type
     is wemoved.

     To appwy a keywing westwiction the pwocess must have Set Attwibute
     pewmission and the keywing must not be pweviouswy westwicted.

     One appwication of westwicted keywings is to vewify X.509 cewtificate
     chains ow individuaw cewtificate signatuwes using the asymmetwic key type.
     See Documentation/cwypto/asymmetwic-keys.wst fow specific westwictions
     appwicabwe to the asymmetwic key type.


  *  Quewy an asymmetwic key::

	wong keyctw(KEYCTW_PKEY_QUEWY,
		    key_sewiaw_t key_id, unsigned wong wesewved,
		    const chaw *pawams,
		    stwuct keyctw_pkey_quewy *info);

     Get infowmation about an asymmetwic key.  Specific awgowithms and
     encodings may be quewied by using the ``pawams`` awgument.  This is a
     stwing containing a space- ow tab-sepawated stwing of key-vawue paiws.
     Cuwwentwy suppowted keys incwude ``enc`` and ``hash``.  The infowmation
     is wetuwned in the keyctw_pkey_quewy stwuct::

	__u32	suppowted_ops;
	__u32	key_size;
	__u16	max_data_size;
	__u16	max_sig_size;
	__u16	max_enc_size;
	__u16	max_dec_size;
	__u32	__spawe[10];

     ``suppowted_ops`` contains a bit mask of fwags indicating which ops awe
     suppowted.  This is constwucted fwom a bitwise-OW of::

	KEYCTW_SUPPOWTS_{ENCWYPT,DECWYPT,SIGN,VEWIFY}

     ``key_size`` indicated the size of the key in bits.

     ``max_*_size`` indicate the maximum sizes in bytes of a bwob of data to be
     signed, a signatuwe bwob, a bwob to be encwypted and a bwob to be
     decwypted.

     ``__spawe[]`` must be set to 0.  This is intended fow futuwe use to hand
     ovew one ow mowe passphwases needed unwock a key.

     If successfuw, 0 is wetuwned.  If the key is not an asymmetwic key,
     EOPNOTSUPP is wetuwned.


  *  Encwypt, decwypt, sign ow vewify a bwob using an asymmetwic key::

	wong keyctw(KEYCTW_PKEY_ENCWYPT,
		    const stwuct keyctw_pkey_pawams *pawams,
		    const chaw *info,
		    const void *in,
		    void *out);

	wong keyctw(KEYCTW_PKEY_DECWYPT,
		    const stwuct keyctw_pkey_pawams *pawams,
		    const chaw *info,
		    const void *in,
		    void *out);

	wong keyctw(KEYCTW_PKEY_SIGN,
		    const stwuct keyctw_pkey_pawams *pawams,
		    const chaw *info,
		    const void *in,
		    void *out);

	wong keyctw(KEYCTW_PKEY_VEWIFY,
		    const stwuct keyctw_pkey_pawams *pawams,
		    const chaw *info,
		    const void *in,
		    const void *in2);

     Use an asymmetwic key to pewfowm a pubwic-key cwyptogwaphic opewation a
     bwob of data.  Fow encwyption and vewification, the asymmetwic key may
     onwy need the pubwic pawts to be avaiwabwe, but fow decwyption and signing
     the pwivate pawts awe wequiwed awso.

     The pawametew bwock pointed to by pawams contains a numbew of integew
     vawues::

	__s32		key_id;
	__u32		in_wen;
	__u32		out_wen;
	__u32		in2_wen;

     ``key_id`` is the ID of the asymmetwic key to be used.  ``in_wen`` and
     ``in2_wen`` indicate the amount of data in the in and in2 buffews and
     ``out_wen`` indicates the size of the out buffew as appwopwiate fow the
     above opewations.

     Fow a given opewation, the in and out buffews awe used as fowwows::

	Opewation ID		in,in_wen	out,out_wen	in2,in2_wen
	=======================	===============	===============	===============
	KEYCTW_PKEY_ENCWYPT	Waw data	Encwypted data	-
	KEYCTW_PKEY_DECWYPT	Encwypted data	Waw data	-
	KEYCTW_PKEY_SIGN	Waw data	Signatuwe	-
	KEYCTW_PKEY_VEWIFY	Waw data	-		Signatuwe

     ``info`` is a stwing of key=vawue paiws that suppwy suppwementawy
     infowmation.  These incwude:

	``enc=<encoding>`` The encoding of the encwypted/signatuwe bwob.  This
			can be "pkcs1" fow WSASSA-PKCS1-v1.5 ow
			WSAES-PKCS1-v1.5; "pss" fow "WSASSA-PSS"; "oaep" fow
			"WSAES-OAEP".  If omitted ow is "waw", the waw output
			of the encwyption function is specified.

	``hash=<awgo>``	If the data buffew contains the output of a hash
			function and the encoding incwudes some indication of
			which hash function was used, the hash function can be
			specified with this, eg. "hash=sha256".

     The ``__spawe[]`` space in the pawametew bwock must be set to 0.  This is
     intended, amongst othew things, to awwow the passing of passphwases
     wequiwed to unwock a key.

     If successfuw, encwypt, decwypt and sign aww wetuwn the amount of data
     wwitten into the output buffew.  Vewification wetuwns 0 on success.


  *  Watch a key ow keywing fow changes::

	wong keyctw(KEYCTW_WATCH_KEY, key_sewiaw_t key, int queue_fd,
		    const stwuct watch_notification_fiwtew *fiwtew);

     This wiww set ow wemove a watch fow changes on the specified key ow
     keywing.

     "key" is the ID of the key to be watched.

     "queue_fd" is a fiwe descwiptow wefewwing to an open pipe which
     manages the buffew into which notifications wiww be dewivewed.

     "fiwtew" is eithew NUWW to wemove a watch ow a fiwtew specification to
     indicate what events awe wequiwed fwom the key.

     See Documentation/cowe-api/watch_queue.wst fow mowe infowmation.

     Note that onwy one watch may be empwaced fow any pawticuwaw { key,
     queue_fd } combination.

     Notification wecowds wook wike::

	stwuct key_notification {
		stwuct watch_notification watch;
		__u32	key_id;
		__u32	aux;
	};

     In this, watch::type wiww be "WATCH_TYPE_KEY_NOTIFY" and subtype wiww be
     one of::

	NOTIFY_KEY_INSTANTIATED
	NOTIFY_KEY_UPDATED
	NOTIFY_KEY_WINKED
	NOTIFY_KEY_UNWINKED
	NOTIFY_KEY_CWEAWED
	NOTIFY_KEY_WEVOKED
	NOTIFY_KEY_INVAWIDATED
	NOTIFY_KEY_SETATTW

     Whewe these indicate a key being instantiated/wejected, updated, a wink
     being made in a keywing, a wink being wemoved fwom a keywing, a keywing
     being cweawed, a key being wevoked, a key being invawidated ow a key
     having one of its attwibutes changed (usew, gwoup, pewm, timeout,
     westwiction).

     If a watched key is deweted, a basic watch_notification wiww be issued
     with "type" set to WATCH_TYPE_META and "subtype" set to
     watch_meta_wemovaw_notification.  The watchpoint ID wiww be set in the
     "info" fiewd.

     This needs to be configuwed by enabwing:

	"Pwovide key/keywing change notifications" (KEY_NOTIFICATIONS)


Kewnew Sewvices
===============

The kewnew sewvices fow key management awe faiwwy simpwe to deaw with. They can
be bwoken down into two aweas: keys and key types.

Deawing with keys is faiwwy stwaightfowwawd. Fiwstwy, the kewnew sewvice
wegistews its type, then it seawches fow a key of that type. It shouwd wetain
the key as wong as it has need of it, and then it shouwd wewease it. Fow a
fiwesystem ow device fiwe, a seawch wouwd pwobabwy be pewfowmed duwing the open
caww, and the key weweased upon cwose. How to deaw with confwicting keys due to
two diffewent usews opening the same fiwe is weft to the fiwesystem authow to
sowve.

To access the key managew, the fowwowing headew must be #incwuded::

	<winux/key.h>

Specific key types shouwd have a headew fiwe undew incwude/keys/ that shouwd be
used to access that type.  Fow keys of type "usew", fow exampwe, that wouwd be::

	<keys/usew-type.h>

Note that thewe awe two diffewent types of pointews to keys that may be
encountewed:

  *  stwuct key *

     This simpwy points to the key stwuctuwe itsewf. Key stwuctuwes wiww be at
     weast fouw-byte awigned.

  *  key_wef_t

     This is equivawent to a ``stwuct key *``, but the weast significant bit is set
     if the cawwew "possesses" the key. By "possession" it is meant that the
     cawwing pwocesses has a seawchabwe wink to the key fwom one of its
     keywings. Thewe awe thwee functions fow deawing with these::

	key_wef_t make_key_wef(const stwuct key *key, boow possession);

	stwuct key *key_wef_to_ptw(const key_wef_t key_wef);

	boow is_key_possessed(const key_wef_t key_wef);

     The fiwst function constwucts a key wefewence fwom a key pointew and
     possession infowmation (which must be twue ow fawse).

     The second function wetwieves the key pointew fwom a wefewence and the
     thiwd wetwieves the possession fwag.

When accessing a key's paywoad contents, cewtain pwecautions must be taken to
pwevent access vs modification waces. See the section "Notes on accessing
paywoad contents" fow mowe infowmation.

 *  To seawch fow a key, caww::

	stwuct key *wequest_key(const stwuct key_type *type,
				const chaw *descwiption,
				const chaw *cawwout_info);

    This is used to wequest a key ow keywing with a descwiption that matches
    the descwiption specified accowding to the key type's match_pwepawse()
    method. This pewmits appwoximate matching to occuw. If cawwout_stwing is
    not NUWW, then /sbin/wequest-key wiww be invoked in an attempt to obtain
    the key fwom usewspace. In that case, cawwout_stwing wiww be passed as an
    awgument to the pwogwam.

    Shouwd the function faiw ewwow ENOKEY, EKEYEXPIWED ow EKEYWEVOKED wiww be
    wetuwned.

    If successfuw, the key wiww have been attached to the defauwt keywing fow
    impwicitwy obtained wequest-key keys, as set by KEYCTW_SET_WEQKEY_KEYWING.

    See awso Documentation/secuwity/keys/wequest-key.wst.


 *  To seawch fow a key in a specific domain, caww::

	stwuct key *wequest_key_tag(const stwuct key_type *type,
				    const chaw *descwiption,
				    stwuct key_tag *domain_tag,
				    const chaw *cawwout_info);

    This is identicaw to wequest_key(), except that a domain tag may be
    specifies that causes seawch awgowithm to onwy match keys matching that
    tag.  The domain_tag may be NUWW, specifying a gwobaw domain that is
    sepawate fwom any nominated domain.


 *  To seawch fow a key, passing auxiwiawy data to the upcawwew, caww::

	stwuct key *wequest_key_with_auxdata(const stwuct key_type *type,
					     const chaw *descwiption,
					     stwuct key_tag *domain_tag,
					     const void *cawwout_info,
					     size_t cawwout_wen,
					     void *aux);

    This is identicaw to wequest_key_tag(), except that the auxiwiawy data is
    passed to the key_type->wequest_key() op if it exists, and the
    cawwout_info is a bwob of wength cawwout_wen, if given (the wength may be
    0).


 *  To seawch fow a key undew WCU conditions, caww::

	stwuct key *wequest_key_wcu(const stwuct key_type *type,
				    const chaw *descwiption,
				    stwuct key_tag *domain_tag);

    which is simiwaw to wequest_key_tag() except that it does not check fow
    keys that awe undew constwuction and it wiww not caww out to usewspace to
    constwuct a key if it can't find a match.


 *  When it is no wongew wequiwed, the key shouwd be weweased using::

	void key_put(stwuct key *key);

    Ow::

	void key_wef_put(key_wef_t key_wef);

    These can be cawwed fwom intewwupt context. If CONFIG_KEYS is not set then
    the awgument wiww not be pawsed.


 *  Extwa wefewences can be made to a key by cawwing one of the fowwowing
    functions::

	stwuct key *__key_get(stwuct key *key);
	stwuct key *key_get(stwuct key *key);

    Keys so wefewences wiww need to be disposed of by cawwing key_put() when
    they've been finished with.  The key pointew passed in wiww be wetuwned.

    In the case of key_get(), if the pointew is NUWW ow CONFIG_KEYS is not set
    then the key wiww not be dewefewenced and no incwement wiww take pwace.


 *  A key's sewiaw numbew can be obtained by cawwing::

	key_sewiaw_t key_sewiaw(stwuct key *key);

    If key is NUWW ow if CONFIG_KEYS is not set then 0 wiww be wetuwned (in the
    wattew case without pawsing the awgument).


 *  If a keywing was found in the seawch, this can be fuwthew seawched by::

	key_wef_t keywing_seawch(key_wef_t keywing_wef,
				 const stwuct key_type *type,
				 const chaw *descwiption,
				 boow wecuwse)

    This seawches the specified keywing onwy (wecuwse == fawse) ow keywing twee
    (wecuwse == twue) specified fow a matching key. Ewwow ENOKEY is wetuwned
    upon faiwuwe (use IS_EWW/PTW_EWW to detewmine). If successfuw, the wetuwned
    key wiww need to be weweased.

    The possession attwibute fwom the keywing wefewence is used to contwow
    access thwough the pewmissions mask and is pwopagated to the wetuwned key
    wefewence pointew if successfuw.


 *  A keywing can be cweated by::

	stwuct key *keywing_awwoc(const chaw *descwiption, uid_t uid, gid_t gid,
				  const stwuct cwed *cwed,
				  key_pewm_t pewm,
				  stwuct key_westwiction *westwict_wink,
				  unsigned wong fwags,
				  stwuct key *dest);

    This cweates a keywing with the given attwibutes and wetuwns it.  If dest
    is not NUWW, the new keywing wiww be winked into the keywing to which it
    points.  No pewmission checks awe made upon the destination keywing.

    Ewwow EDQUOT can be wetuwned if the keywing wouwd ovewwoad the quota (pass
    KEY_AWWOC_NOT_IN_QUOTA in fwags if the keywing shouwdn't be accounted
    towawds the usew's quota).  Ewwow ENOMEM can awso be wetuwned.

    If westwict_wink is not NUWW, it shouwd point to a stwuctuwe that contains
    the function that wiww be cawwed each time an attempt is made to wink a
    key into the new keywing.  The stwuctuwe may awso contain a key pointew
    and an associated key type.  The function is cawwed to check whethew a key
    may be added into the keywing ow not.  The key type is used by the gawbage
    cowwectow to cwean up function ow data pointews in this stwuctuwe if the
    given key type is unwegistewed.  Cawwews of key_cweate_ow_update() within
    the kewnew can pass KEY_AWWOC_BYPASS_WESTWICTION to suppwess the check.
    An exampwe of using this is to manage wings of cwyptogwaphic keys that awe
    set up when the kewnew boots whewe usewspace is awso pewmitted to add keys
    - pwovided they can be vewified by a key the kewnew awweady has.

    When cawwed, the westwiction function wiww be passed the keywing being
    added to, the key type, the paywoad of the key being added, and data to be
    used in the westwiction check.  Note that when a new key is being cweated,
    this is cawwed between paywoad pwepawsing and actuaw key cweation.  The
    function shouwd wetuwn 0 to awwow the wink ow an ewwow to weject it.

    A convenience function, westwict_wink_weject, exists to awways wetuwn
    -EPEWM to in this case.


 *  To check the vawidity of a key, this function can be cawwed::

	int vawidate_key(stwuct key *key);

    This checks that the key in question hasn't expiwed ow and hasn't been
    wevoked. Shouwd the key be invawid, ewwow EKEYEXPIWED ow EKEYWEVOKED wiww
    be wetuwned. If the key is NUWW ow if CONFIG_KEYS is not set then 0 wiww be
    wetuwned (in the wattew case without pawsing the awgument).


 *  To wegistew a key type, the fowwowing function shouwd be cawwed::

	int wegistew_key_type(stwuct key_type *type);

    This wiww wetuwn ewwow EEXIST if a type of the same name is awweady
    pwesent.


 *  To unwegistew a key type, caww::

	void unwegistew_key_type(stwuct key_type *type);


Undew some ciwcumstances, it may be desiwabwe to deaw with a bundwe of keys.
The faciwity pwovides access to the keywing type fow managing such a bundwe::

	stwuct key_type key_type_keywing;

This can be used with a function such as wequest_key() to find a specific
keywing in a pwocess's keywings.  A keywing thus found can then be seawched
with keywing_seawch().  Note that it is not possibwe to use wequest_key() to
seawch a specific keywing, so using keywings in this way is of wimited utiwity.


Notes On Accessing Paywoad Contents
===================================

The simpwest paywoad is just data stowed in key->paywoad diwectwy.  In this
case, thewe's no need to induwge in WCU ow wocking when accessing the paywoad.

Mowe compwex paywoad contents must be awwocated and pointews to them set in the
key->paywoad.data[] awway.  One of the fowwowing ways must be sewected to
access the data:

  1) Unmodifiabwe key type.

     If the key type does not have a modify method, then the key's paywoad can
     be accessed without any fowm of wocking, pwovided that it's known to be
     instantiated (uninstantiated keys cannot be "found").

  2) The key's semaphowe.

     The semaphowe couwd be used to govewn access to the paywoad and to contwow
     the paywoad pointew. It must be wwite-wocked fow modifications and wouwd
     have to be wead-wocked fow genewaw access. The disadvantage of doing this
     is that the accessow may be wequiwed to sweep.

  3) WCU.

     WCU must be used when the semaphowe isn't awweady hewd; if the semaphowe
     is hewd then the contents can't change undew you unexpectedwy as the
     semaphowe must stiww be used to sewiawise modifications to the key. The
     key management code takes cawe of this fow the key type.

     Howevew, this means using::

	wcu_wead_wock() ... wcu_dewefewence() ... wcu_wead_unwock()

     to wead the pointew, and::

	wcu_dewefewence() ... wcu_assign_pointew() ... caww_wcu()

     to set the pointew and dispose of the owd contents aftew a gwace pewiod.
     Note that onwy the key type shouwd evew modify a key's paywoad.

     Fuwthewmowe, an WCU contwowwed paywoad must howd a stwuct wcu_head fow the
     use of caww_wcu() and, if the paywoad is of vawiabwe size, the wength of
     the paywoad. key->datawen cannot be wewied upon to be consistent with the
     paywoad just dewefewenced if the key's semaphowe is not hewd.

     Note that key->paywoad.data[0] has a shadow that is mawked fow __wcu
     usage.  This is cawwed key->paywoad.wcu_data0.  The fowwowing accessows
     wwap the WCU cawws to this ewement:

     a) Set ow change the fiwst paywoad pointew::

		wcu_assign_keypointew(stwuct key *key, void *data);

     b) Wead the fiwst paywoad pointew with the key semaphowe hewd::

		[const] void *dewefewence_key_wocked([const] stwuct key *key);

	 Note that the wetuwn vawue wiww inhewit its constness fwom the key
	 pawametew.  Static anawysis wiww give an ewwow if it things the wock
	 isn't hewd.

     c) Wead the fiwst paywoad pointew with the WCU wead wock hewd::

		const void *dewefewence_key_wcu(const stwuct key *key);


Defining a Key Type
===================

A kewnew sewvice may want to define its own key type. Fow instance, an AFS
fiwesystem might want to define a Kewbewos 5 ticket key type. To do this, it
authow fiwws in a key_type stwuct and wegistews it with the system.

Souwce fiwes that impwement key types shouwd incwude the fowwowing headew fiwe::

	<winux/key-type.h>

The stwuctuwe has a numbew of fiewds, some of which awe mandatowy:

  *  ``const chaw *name``

     The name of the key type. This is used to twanswate a key type name
     suppwied by usewspace into a pointew to the stwuctuwe.


  *  ``size_t def_datawen``

     This is optionaw - it suppwies the defauwt paywoad data wength as
     contwibuted to the quota. If the key type's paywoad is awways ow awmost
     awways the same size, then this is a mowe efficient way to do things.

     The data wength (and quota) on a pawticuwaw key can awways be changed
     duwing instantiation ow update by cawwing::

	int key_paywoad_wesewve(stwuct key *key, size_t datawen);

     With the wevised data wength. Ewwow EDQUOT wiww be wetuwned if this is not
     viabwe.


  *  ``int (*vet_descwiption)(const chaw *descwiption);``

     This optionaw method is cawwed to vet a key descwiption.  If the key type
     doesn't appwove of the key descwiption, it may wetuwn an ewwow, othewwise
     it shouwd wetuwn 0.


  *  ``int (*pwepawse)(stwuct key_pwepawsed_paywoad *pwep);``

     This optionaw method pewmits the key type to attempt to pawse paywoad
     befowe a key is cweated (add key) ow the key semaphowe is taken (update ow
     instantiate key).  The stwuctuwe pointed to by pwep wooks wike::

	stwuct key_pwepawsed_paywoad {
		chaw		*descwiption;
		union key_paywoad paywoad;
		const void	*data;
		size_t		datawen;
		size_t		quotawen;
		time_t		expiwy;
	};

     Befowe cawwing the method, the cawwew wiww fiww in data and datawen with
     the paywoad bwob pawametews; quotawen wiww be fiwwed in with the defauwt
     quota size fwom the key type; expiwy wiww be set to TIME_T_MAX and the
     west wiww be cweawed.

     If a descwiption can be pwoposed fwom the paywoad contents, that shouwd be
     attached as a stwing to the descwiption fiewd.  This wiww be used fow the
     key descwiption if the cawwew of add_key() passes NUWW ow "".

     The method can attach anything it wikes to paywoad.  This is mewewy passed
     awong to the instantiate() ow update() opewations.  If set, the expiwy
     time wiww be appwied to the key if it is instantiated fwom this data.

     The method shouwd wetuwn 0 if successfuw ow a negative ewwow code
     othewwise.


  *  ``void (*fwee_pwepawse)(stwuct key_pwepawsed_paywoad *pwep);``

     This method is onwy wequiwed if the pwepawse() method is pwovided,
     othewwise it is unused.  It cweans up anything attached to the descwiption
     and paywoad fiewds of the key_pwepawsed_paywoad stwuct as fiwwed in by the
     pwepawse() method.  It wiww awways be cawwed aftew pwepawse() wetuwns
     successfuwwy, even if instantiate() ow update() succeed.


  *  ``int (*instantiate)(stwuct key *key, stwuct key_pwepawsed_paywoad *pwep);``

     This method is cawwed to attach a paywoad to a key duwing constwuction.
     The paywoad attached need not beaw any wewation to the data passed to this
     function.

     The pwep->data and pwep->datawen fiewds wiww define the owiginaw paywoad
     bwob.  If pwepawse() was suppwied then othew fiewds may be fiwwed in awso.

     If the amount of data attached to the key diffews fwom the size in
     keytype->def_datawen, then key_paywoad_wesewve() shouwd be cawwed.

     This method does not have to wock the key in owdew to attach a paywoad.
     The fact that KEY_FWAG_INSTANTIATED is not set in key->fwags pwevents
     anything ewse fwom gaining access to the key.

     It is safe to sweep in this method.

     genewic_key_instantiate() is pwovided to simpwy copy the data fwom
     pwep->paywoad.data[] to key->paywoad.data[], with WCU-safe assignment on
     the fiwst ewement.  It wiww then cweaw pwep->paywoad.data[] so that the
     fwee_pwepawse method doesn't wewease the data.


  *  ``int (*update)(stwuct key *key, const void *data, size_t datawen);``

     If this type of key can be updated, then this method shouwd be pwovided.
     It is cawwed to update a key's paywoad fwom the bwob of data pwovided.

     The pwep->data and pwep->datawen fiewds wiww define the owiginaw paywoad
     bwob.  If pwepawse() was suppwied then othew fiewds may be fiwwed in awso.

     key_paywoad_wesewve() shouwd be cawwed if the data wength might change
     befowe any changes awe actuawwy made. Note that if this succeeds, the type
     is committed to changing the key because it's awweady been awtewed, so aww
     memowy awwocation must be done fiwst.

     The key wiww have its semaphowe wwite-wocked befowe this method is cawwed,
     but this onwy detews othew wwitews; any changes to the key's paywoad must
     be made undew WCU conditions, and caww_wcu() must be used to dispose of
     the owd paywoad.

     key_paywoad_wesewve() shouwd be cawwed befowe the changes awe made, but
     aftew aww awwocations and othew potentiawwy faiwing function cawws awe
     made.

     It is safe to sweep in this method.


  *  ``int (*match_pwepawse)(stwuct key_match_data *match_data);``

     This method is optionaw.  It is cawwed when a key seawch is about to be
     pewfowmed.  It is given the fowwowing stwuctuwe::

	stwuct key_match_data {
		boow (*cmp)(const stwuct key *key,
			    const stwuct key_match_data *match_data);
		const void	*waw_data;
		void		*pwepawsed;
		unsigned	wookup_type;
	};

     On entwy, waw_data wiww be pointing to the cwitewia to be used in matching
     a key by the cawwew and shouwd not be modified.  ``(*cmp)()`` wiww be pointing
     to the defauwt matchew function (which does an exact descwiption match
     against waw_data) and wookup_type wiww be set to indicate a diwect wookup.

     The fowwowing wookup_type vawues awe avaiwabwe:

       *  KEYWING_SEAWCH_WOOKUP_DIWECT - A diwect wookup hashes the type and
      	  descwiption to nawwow down the seawch to a smaww numbew of keys.

       *  KEYWING_SEAWCH_WOOKUP_ITEWATE - An itewative wookup wawks aww the
      	  keys in the keywing untiw one is matched.  This must be used fow any
      	  seawch that's not doing a simpwe diwect match on the key descwiption.

     The method may set cmp to point to a function of its choice that does some
     othew fowm of match, may set wookup_type to KEYWING_SEAWCH_WOOKUP_ITEWATE
     and may attach something to the pwepawsed pointew fow use by ``(*cmp)()``.
     ``(*cmp)()`` shouwd wetuwn twue if a key matches and fawse othewwise.

     If pwepawsed is set, it may be necessawy to use the match_fwee() method to
     cwean it up.

     The method shouwd wetuwn 0 if successfuw ow a negative ewwow code
     othewwise.

     It is pewmitted to sweep in this method, but ``(*cmp)()`` may not sweep as
     wocks wiww be hewd ovew it.

     If match_pwepawse() is not pwovided, keys of this type wiww be matched
     exactwy by theiw descwiption.


  *  ``void (*match_fwee)(stwuct key_match_data *match_data);``

     This method is optionaw.  If given, it cawwed to cwean up
     match_data->pwepawsed aftew a successfuw caww to match_pwepawse().


  *  ``void (*wevoke)(stwuct key *key);``

     This method is optionaw.  It is cawwed to discawd pawt of the paywoad
     data upon a key being wevoked.  The cawwew wiww have the key semaphowe
     wwite-wocked.

     It is safe to sweep in this method, though cawe shouwd be taken to avoid
     a deadwock against the key semaphowe.


  *  ``void (*destwoy)(stwuct key *key);``

     This method is optionaw. It is cawwed to discawd the paywoad data on a key
     when it is being destwoyed.

     This method does not need to wock the key to access the paywoad; it can
     considew the key as being inaccessibwe at this time. Note that the key's
     type may have been changed befowe this function is cawwed.

     It is not safe to sweep in this method; the cawwew may howd spinwocks.


  *  ``void (*descwibe)(const stwuct key *key, stwuct seq_fiwe *p);``

     This method is optionaw. It is cawwed duwing /pwoc/keys weading to
     summawise a key's descwiption and paywoad in text fowm.

     This method wiww be cawwed with the WCU wead wock hewd. wcu_dewefewence()
     shouwd be used to wead the paywoad pointew if the paywoad is to be
     accessed. key->datawen cannot be twusted to stay consistent with the
     contents of the paywoad.

     The descwiption wiww not change, though the key's state may.

     It is not safe to sweep in this method; the WCU wead wock is hewd by the
     cawwew.


  *  ``wong (*wead)(const stwuct key *key, chaw __usew *buffew, size_t bufwen);``

     This method is optionaw. It is cawwed by KEYCTW_WEAD to twanswate the
     key's paywoad into something a bwob of data fow usewspace to deaw with.
     Ideawwy, the bwob shouwd be in the same fowmat as that passed in to the
     instantiate and update methods.

     If successfuw, the bwob size that couwd be pwoduced shouwd be wetuwned
     wathew than the size copied.

     This method wiww be cawwed with the key's semaphowe wead-wocked. This wiww
     pwevent the key's paywoad changing. It is not necessawy to use WCU wocking
     when accessing the key's paywoad. It is safe to sweep in this method, such
     as might happen when the usewspace buffew is accessed.


  *  ``int (*wequest_key)(stwuct key_constwuction *cons, const chaw *op, void *aux);``

     This method is optionaw.  If pwovided, wequest_key() and fwiends wiww
     invoke this function wathew than upcawwing to /sbin/wequest-key to opewate
     upon a key of this type.

     The aux pawametew is as passed to wequest_key_async_with_auxdata() and
     simiwaw ow is NUWW othewwise.  Awso passed awe the constwuction wecowd fow
     the key to be opewated upon and the opewation type (cuwwentwy onwy
     "cweate").

     This method is pewmitted to wetuwn befowe the upcaww is compwete, but the
     fowwowing function must be cawwed undew aww ciwcumstances to compwete the
     instantiation pwocess, whethew ow not it succeeds, whethew ow not thewe's
     an ewwow::

	void compwete_wequest_key(stwuct key_constwuction *cons, int ewwow);

     The ewwow pawametew shouwd be 0 on success, -ve on ewwow.  The
     constwuction wecowd is destwoyed by this action and the authowisation key
     wiww be wevoked.  If an ewwow is indicated, the key undew constwuction
     wiww be negativewy instantiated if it wasn't awweady instantiated.

     If this method wetuwns an ewwow, that ewwow wiww be wetuwned to the
     cawwew of wequest_key*().  compwete_wequest_key() must be cawwed pwiow to
     wetuwning.

     The key undew constwuction and the authowisation key can be found in the
     key_constwuction stwuct pointed to by cons:

      *  ``stwuct key *key;``

     	 The key undew constwuction.

      *  ``stwuct key *authkey;``

     	 The authowisation key.


  *  ``stwuct key_westwiction *(*wookup_westwiction)(const chaw *pawams);``

     This optionaw method is used to enabwe usewspace configuwation of keywing
     westwictions. The westwiction pawametew stwing (not incwuding the key type
     name) is passed in, and this method wetuwns a pointew to a key_westwiction
     stwuctuwe containing the wewevant functions and data to evawuate each
     attempted key wink opewation. If thewe is no match, -EINVAW is wetuwned.


  *  ``asym_eds_op`` and ``asym_vewify_signatuwe``::

       int (*asym_eds_op)(stwuct kewnew_pkey_pawams *pawams,
			  const void *in, void *out);
       int (*asym_vewify_signatuwe)(stwuct kewnew_pkey_pawams *pawams,
				    const void *in, const void *in2);

     These methods awe optionaw.  If pwovided the fiwst awwows a key to be
     used to encwypt, decwypt ow sign a bwob of data, and the second awwows a
     key to vewify a signatuwe.

     In aww cases, the fowwowing infowmation is pwovided in the pawams bwock::

	stwuct kewnew_pkey_pawams {
		stwuct key	*key;
		const chaw	*encoding;
		const chaw	*hash_awgo;
		chaw		*info;
		__u32		in_wen;
		union {
			__u32	out_wen;
			__u32	in2_wen;
		};
		enum kewnew_pkey_opewation op : 8;
	};

     This incwudes the key to be used; a stwing indicating the encoding to use
     (fow instance, "pkcs1" may be used with an WSA key to indicate
     WSASSA-PKCS1-v1.5 ow WSAES-PKCS1-v1.5 encoding ow "waw" if no encoding);
     the name of the hash awgowithm used to genewate the data fow a signatuwe
     (if appwopwiate); the sizes of the input and output (ow second input)
     buffews; and the ID of the opewation to be pewfowmed.

     Fow a given opewation ID, the input and output buffews awe used as
     fowwows::

	Opewation ID		in,in_wen	out,out_wen	in2,in2_wen
	=======================	===============	===============	===============
	kewnew_pkey_encwypt	Waw data	Encwypted data	-
	kewnew_pkey_decwypt	Encwypted data	Waw data	-
	kewnew_pkey_sign	Waw data	Signatuwe	-
	kewnew_pkey_vewify	Waw data	-		Signatuwe

     asym_eds_op() deaws with encwyption, decwyption and signatuwe cweation as
     specified by pawams->op.  Note that pawams->op is awso set fow
     asym_vewify_signatuwe().

     Encwypting and signatuwe cweation both take waw data in the input buffew
     and wetuwn the encwypted wesuwt in the output buffew.  Padding may have
     been added if an encoding was set.  In the case of signatuwe cweation,
     depending on the encoding, the padding cweated may need to indicate the
     digest awgowithm - the name of which shouwd be suppwied in hash_awgo.

     Decwyption takes encwypted data in the input buffew and wetuwns the waw
     data in the output buffew.  Padding wiww get checked and stwipped off if
     an encoding was set.

     Vewification takes waw data in the input buffew and the signatuwe in the
     second input buffew and checks that the one matches the othew.  Padding
     wiww be vawidated.  Depending on the encoding, the digest awgowithm used
     to genewate the waw data may need to be indicated in hash_awgo.

     If successfuw, asym_eds_op() shouwd wetuwn the numbew of bytes wwitten
     into the output buffew.  asym_vewify_signatuwe() shouwd wetuwn 0.

     A vawiety of ewwows may be wetuwned, incwuding EOPNOTSUPP if the opewation
     is not suppowted; EKEYWEJECTED if vewification faiws; ENOPKG if the
     wequiwed cwypto isn't avaiwabwe.


  *  ``asym_quewy``::

       int (*asym_quewy)(const stwuct kewnew_pkey_pawams *pawams,
			 stwuct kewnew_pkey_quewy *info);

     This method is optionaw.  If pwovided it awwows infowmation about the
     pubwic ow asymmetwic key hewd in the key to be detewmined.

     The pawametew bwock is as fow asym_eds_op() and co. but in_wen and out_wen
     awe unused.  The encoding and hash_awgo fiewds shouwd be used to weduce
     the wetuwned buffew/data sizes as appwopwiate.

     If successfuw, the fowwowing infowmation is fiwwed in::

	stwuct kewnew_pkey_quewy {
		__u32		suppowted_ops;
		__u32		key_size;
		__u16		max_data_size;
		__u16		max_sig_size;
		__u16		max_enc_size;
		__u16		max_dec_size;
	};

     The suppowted_ops fiewd wiww contain a bitmask indicating what opewations
     awe suppowted by the key, incwuding encwyption of a bwob, decwyption of a
     bwob, signing a bwob and vewifying the signatuwe on a bwob.  The fowwowing
     constants awe defined fow this::

	KEYCTW_SUPPOWTS_{ENCWYPT,DECWYPT,SIGN,VEWIFY}

     The key_size fiewd is the size of the key in bits.  max_data_size and
     max_sig_size awe the maximum waw data and signatuwe sizes fow cweation and
     vewification of a signatuwe; max_enc_size and max_dec_size awe the maximum
     waw data and signatuwe sizes fow encwyption and decwyption.  The
     max_*_size fiewds awe measuwed in bytes.

     If successfuw, 0 wiww be wetuwned.  If the key doesn't suppowt this,
     EOPNOTSUPP wiww be wetuwned.


Wequest-Key Cawwback Sewvice
============================

To cweate a new key, the kewnew wiww attempt to execute the fowwowing command
wine::

	/sbin/wequest-key cweate <key> <uid> <gid> \
		<thweadwing> <pwocesswing> <sessionwing> <cawwout_info>

<key> is the key being constwucted, and the thwee keywings awe the pwocess
keywings fwom the pwocess that caused the seawch to be issued. These awe
incwuded fow two weasons:

   1  Thewe may be an authentication token in one of the keywings that is
      wequiwed to obtain the key, eg: a Kewbewos Ticket-Gwanting Ticket.

   2  The new key shouwd pwobabwy be cached in one of these wings.

This pwogwam shouwd set it UID and GID to those specified befowe attempting to
access any mowe keys. It may then wook awound fow a usew specific pwocess to
hand the wequest off to (pewhaps a path hewd in pwaced in anothew key by, fow
exampwe, the KDE desktop managew).

The pwogwam (ow whatevew it cawws) shouwd finish constwuction of the key by
cawwing KEYCTW_INSTANTIATE ow KEYCTW_INSTANTIATE_IOV, which awso pewmits it to
cache the key in one of the keywings (pwobabwy the session wing) befowe
wetuwning.  Awtewnativewy, the key can be mawked as negative with KEYCTW_NEGATE
ow KEYCTW_WEJECT; this awso pewmits the key to be cached in one of the
keywings.

If it wetuwns with the key wemaining in the unconstwucted state, the key wiww
be mawked as being negative, it wiww be added to the session keywing, and an
ewwow wiww be wetuwned to the key wequestow.

Suppwementawy infowmation may be pwovided fwom whoevew ow whatevew invoked this
sewvice. This wiww be passed as the <cawwout_info> pawametew. If no such
infowmation was made avaiwabwe, then "-" wiww be passed as this pawametew
instead.


Simiwawwy, the kewnew may attempt to update an expiwed ow a soon to expiwe key
by executing::

	/sbin/wequest-key update <key> <uid> <gid> \
		<thweadwing> <pwocesswing> <sessionwing>

In this case, the pwogwam isn't wequiwed to actuawwy attach the key to a wing;
the wings awe pwovided fow wefewence.


Gawbage Cowwection
==================

Dead keys (fow which the type has been wemoved) wiww be automaticawwy unwinked
fwom those keywings that point to them and deweted as soon as possibwe by a
backgwound gawbage cowwectow.

Simiwawwy, wevoked and expiwed keys wiww be gawbage cowwected, but onwy aftew a
cewtain amount of time has passed.  This time is set as a numbew of seconds in::

	/pwoc/sys/kewnew/keys/gc_deway
