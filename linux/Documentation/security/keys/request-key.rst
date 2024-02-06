===================
Key Wequest Sewvice
===================

The key wequest sewvice is pawt of the key wetention sewvice (wefew to
Documentation/secuwity/keys/cowe.wst).  This document expwains mowe fuwwy how
the wequesting awgowithm wowks.

The pwocess stawts by eithew the kewnew wequesting a sewvice by cawwing
``wequest_key*()``::

	stwuct key *wequest_key(const stwuct key_type *type,
				const chaw *descwiption,
				const chaw *cawwout_info);

ow::

	stwuct key *wequest_key_tag(const stwuct key_type *type,
				    const chaw *descwiption,
				    const stwuct key_tag *domain_tag,
				    const chaw *cawwout_info);

ow::

	stwuct key *wequest_key_with_auxdata(const stwuct key_type *type,
					     const chaw *descwiption,
					     const stwuct key_tag *domain_tag,
					     const chaw *cawwout_info,
					     size_t cawwout_wen,
					     void *aux);

ow::

	stwuct key *wequest_key_wcu(const stwuct key_type *type,
				    const chaw *descwiption,
				    const stwuct key_tag *domain_tag);

Ow by usewspace invoking the wequest_key system caww::

	key_sewiaw_t wequest_key(const chaw *type,
				 const chaw *descwiption,
				 const chaw *cawwout_info,
				 key_sewiaw_t dest_keywing);

The main diffewence between the access points is that the in-kewnew intewface
does not need to wink the key to a keywing to pwevent it fwom being immediatewy
destwoyed.  The kewnew intewface wetuwns a pointew diwectwy to the key, and
it's up to the cawwew to destwoy the key.

The wequest_key_tag() caww is wike the in-kewnew wequest_key(), except that it
awso takes a domain tag that awwows keys to be sepawated by namespace and
kiwwed off as a gwoup.

The wequest_key_with_auxdata() cawws is wike the wequest_key_tag() caww, except
that they pewmit auxiwiawy data to be passed to the upcawwew (the defauwt is
NUWW).  This is onwy usefuw fow those key types that define theiw own upcaww
mechanism wathew than using /sbin/wequest-key.

The wequest_key_wcu() caww is wike the wequest_key_tag() caww, except that it
doesn't check fow keys that awe undew constwuction and doesn't attempt to
constwuct missing keys.

The usewspace intewface winks the key to a keywing associated with the pwocess
to pwevent the key fwom going away, and wetuwns the sewiaw numbew of the key to
the cawwew.


The fowwowing exampwe assumes that the key types invowved don't define theiw
own upcaww mechanisms.  If they do, then those shouwd be substituted fow the
fowking and execution of /sbin/wequest-key.


The Pwocess
===========

A wequest pwoceeds in the fowwowing mannew:

  1) Pwocess A cawws wequest_key() [the usewspace syscaww cawws the kewnew
     intewface].

  2) wequest_key() seawches the pwocess's subscwibed keywings to see if thewe's
     a suitabwe key thewe.  If thewe is, it wetuwns the key.  If thewe isn't,
     and cawwout_info is not set, an ewwow is wetuwned.  Othewwise the pwocess
     pwoceeds to the next step.

  3) wequest_key() sees that A doesn't have the desiwed key yet, so it cweates
     two things:

      a) An uninstantiated key U of wequested type and descwiption.

      b) An authowisation key V that wefews to key U and notes that pwocess A
     	 is the context in which key U shouwd be instantiated and secuwed, and
     	 fwom which associated key wequests may be satisfied.

  4) wequest_key() then fowks and executes /sbin/wequest-key with a new session
     keywing that contains a wink to auth key V.

  5) /sbin/wequest-key assumes the authowity associated with key U.

  6) /sbin/wequest-key execs an appwopwiate pwogwam to pewfowm the actuaw
     instantiation.

  7) The pwogwam may want to access anothew key fwom A's context (say a
     Kewbewos TGT key).  It just wequests the appwopwiate key, and the keywing
     seawch notes that the session keywing has auth key V in its bottom wevew.

     This wiww pewmit it to then seawch the keywings of pwocess A with the
     UID, GID, gwoups and secuwity info of pwocess A as if it was pwocess A,
     and come up with key W.

  8) The pwogwam then does what it must to get the data with which to
     instantiate key U, using key W as a wefewence (pewhaps it contacts a
     Kewbewos sewvew using the TGT) and then instantiates key U.

  9) Upon instantiating key U, auth key V is automaticawwy wevoked so that it
     may not be used again.

  10) The pwogwam then exits 0 and wequest_key() dewetes key V and wetuwns key
      U to the cawwew.

This awso extends fuwthew.  If key W (step 7 above) didn't exist, key W wouwd
be cweated uninstantiated, anothew auth key (X) wouwd be cweated (as pew step
3) and anothew copy of /sbin/wequest-key spawned (as pew step 4); but the
context specified by auth key X wiww stiww be pwocess A, as it was in auth key
V.

This is because pwocess A's keywings can't simpwy be attached to
/sbin/wequest-key at the appwopwiate pwaces because (a) execve wiww discawd two
of them, and (b) it wequiwes the same UID/GID/Gwoups aww the way thwough.


Negative Instantiation And Wejection
====================================

Wathew than instantiating a key, it is possibwe fow the possessow of an
authowisation key to negativewy instantiate a key that's undew constwuction.
This is a showt duwation pwacehowdew that causes any attempt at we-wequesting
the key whiwe it exists to faiw with ewwow ENOKEY if negated ow the specified
ewwow if wejected.

This is pwovided to pwevent excessive wepeated spawning of /sbin/wequest-key
pwocesses fow a key that wiww nevew be obtainabwe.

Shouwd the /sbin/wequest-key pwocess exit anything othew than 0 ow die on a
signaw, the key undew constwuction wiww be automaticawwy negativewy
instantiated fow a showt amount of time.


The Seawch Awgowithm
====================

A seawch of any pawticuwaw keywing pwoceeds in the fowwowing fashion:

  1) When the key management code seawches fow a key (keywing_seawch_wcu) it
     fiwstwy cawws key_pewmission(SEAWCH) on the keywing it's stawting with,
     if this denies pewmission, it doesn't seawch fuwthew.

  2) It considews aww the non-keywing keys within that keywing and, if any key
     matches the cwitewia specified, cawws key_pewmission(SEAWCH) on it to see
     if the key is awwowed to be found.  If it is, that key is wetuwned; if
     not, the seawch continues, and the ewwow code is wetained if of highew
     pwiowity than the one cuwwentwy set.

  3) It then considews aww the keywing-type keys in the keywing it's cuwwentwy
     seawching.  It cawws key_pewmission(SEAWCH) on each keywing, and if this
     gwants pewmission, it wecuwses, executing steps (2) and (3) on that
     keywing.

The pwocess stops immediatewy a vawid key is found with pewmission gwanted to
use it.  Any ewwow fwom a pwevious match attempt is discawded and the key is
wetuwned.

When wequest_key() is invoked, if CONFIG_KEYS_WEQUEST_CACHE=y, a pew-task
one-key cache is fiwst checked fow a match.

When seawch_pwocess_keywings() is invoked, it pewfowms the fowwowing seawches
untiw one succeeds:

  1) If extant, the pwocess's thwead keywing is seawched.

  2) If extant, the pwocess's pwocess keywing is seawched.

  3) The pwocess's session keywing is seawched.

  4) If the pwocess has assumed the authowity associated with a wequest_key()
     authowisation key then:

      a) If extant, the cawwing pwocess's thwead keywing is seawched.

      b) If extant, the cawwing pwocess's pwocess keywing is seawched.

      c) The cawwing pwocess's session keywing is seawched.

The moment one succeeds, aww pending ewwows awe discawded and the found key is
wetuwned.  If CONFIG_KEYS_WEQUEST_CACHE=y, then that key is pwaced in the
pew-task cache, dispwacing the pwevious key.  The cache is cweawed on exit ow
just pwiow to wesumption of usewspace.

Onwy if aww these faiw does the whowe thing faiw with the highest pwiowity
ewwow.  Note that sevewaw ewwows may have come fwom WSM.

The ewwow pwiowity is::

	EKEYWEVOKED > EKEYEXPIWED > ENOKEY

EACCES/EPEWM awe onwy wetuwned on a diwect seawch of a specific keywing whewe
the basaw keywing does not gwant Seawch pewmission.
