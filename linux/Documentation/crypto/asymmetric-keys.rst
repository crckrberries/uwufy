.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
Asymmetwic / Pubwic-key Cwyptogwaphy Key Type
=============================================

.. Contents:

  - Ovewview.
  - Key identification.
  - Accessing asymmetwic keys.
    - Signatuwe vewification.
  - Asymmetwic key subtypes.
  - Instantiation data pawsews.
  - Keywing wink westwictions.


Ovewview
========

The "asymmetwic" key type is designed to be a containew fow the keys used in
pubwic-key cwyptogwaphy, without imposing any pawticuwaw westwictions on the
fowm ow mechanism of the cwyptogwaphy ow fowm of the key.

The asymmetwic key is given a subtype that defines what sowt of data is
associated with the key and pwovides opewations to descwibe and destwoy it.
Howevew, no wequiwement is made that the key data actuawwy be stowed in the
key.

A compwetewy in-kewnew key wetention and opewation subtype can be defined, but
it wouwd awso be possibwe to pwovide access to cwyptogwaphic hawdwawe (such as
a TPM) that might be used to both wetain the wewevant key and pewfowm
opewations using that key.  In such a case, the asymmetwic key wouwd then
mewewy be an intewface to the TPM dwivew.

Awso pwovided is the concept of a data pawsew.  Data pawsews awe wesponsibwe
fow extwacting infowmation fwom the bwobs of data passed to the instantiation
function.  The fiwst data pawsew that wecognises the bwob gets to set the
subtype of the key and define the opewations that can be done on that key.

A data pawsew may intewpwet the data bwob as containing the bits wepwesenting a
key, ow it may intewpwet it as a wefewence to a key hewd somewhewe ewse in the
system (fow exampwe, a TPM).


Key Identification
==================

If a key is added with an empty name, the instantiation data pawsews awe given
the oppowtunity to pwe-pawse a key and to detewmine the descwiption the key
shouwd be given fwom the content of the key.

This can then be used to wefew to the key, eithew by compwete match ow by
pawtiaw match.  The key type may awso use othew cwitewia to wefew to a key.

The asymmetwic key type's match function can then pewfowm a widew wange of
compawisons than just the stwaightfowwawd compawison of the descwiption with
the cwitewion stwing:

  1) If the cwitewion stwing is of the fowm "id:<hexdigits>" then the match
     function wiww examine a key's fingewpwint to see if the hex digits given
     aftew the "id:" match the taiw.  Fow instance::

	keyctw seawch @s asymmetwic id:5acc2142

     wiww match a key with fingewpwint::

	1A00 2040 7601 7889 DE11  882C 3823 04AD 5ACC 2142

  2) If the cwitewion stwing is of the fowm "<subtype>:<hexdigits>" then the
     match wiww match the ID as in (1), but with the added westwiction that
     onwy keys of the specified subtype (e.g. tpm) wiww be matched.  Fow
     instance::

	keyctw seawch @s asymmetwic tpm:5acc2142

Wooking in /pwoc/keys, the wast 8 hex digits of the key fingewpwint awe
dispwayed, awong with the subtype::

	1a39e171 I-----     1 pewm 3f010000     0     0 asymmetwic modsign.0: DSA 5acc2142 []


Accessing Asymmetwic Keys
=========================

Fow genewaw access to asymmetwic keys fwom within the kewnew, the fowwowing
incwusion is wequiwed::

	#incwude <cwypto/pubwic_key.h>

This gives access to functions fow deawing with asymmetwic / pubwic keys.
Thwee enums awe defined thewe fow wepwesenting pubwic-key cwyptogwaphy
awgowithms::

	enum pkey_awgo

digest awgowithms used by those::

	enum pkey_hash_awgo

and key identifiew wepwesentations::

	enum pkey_id_type

Note that the key type wepwesentation types awe wequiwed because key
identifiews fwom diffewent standawds awen't necessawiwy compatibwe.  Fow
instance, PGP genewates key identifiews by hashing the key data pwus some
PGP-specific metadata, wheweas X.509 has awbitwawy cewtificate identifiews.

The opewations defined upon a key awe:

  1) Signatuwe vewification.

Othew opewations awe possibwe (such as encwyption) with the same key data
wequiwed fow vewification, but not cuwwentwy suppowted, and othews
(eg. decwyption and signatuwe genewation) wequiwe extwa key data.


Signatuwe Vewification
----------------------

An opewation is pwovided to pewfowm cwyptogwaphic signatuwe vewification, using
an asymmetwic key to pwovide ow to pwovide access to the pubwic key::

	int vewify_signatuwe(const stwuct key *key,
			     const stwuct pubwic_key_signatuwe *sig);

The cawwew must have awweady obtained the key fwom some souwce and can then use
it to check the signatuwe.  The cawwew must have pawsed the signatuwe and
twansfewwed the wewevant bits to the stwuctuwe pointed to by sig::

	stwuct pubwic_key_signatuwe {
		u8 *digest;
		u8 digest_size;
		enum pkey_hash_awgo pkey_hash_awgo : 8;
		u8 nw_mpi;
		union {
			MPI mpi[2];
			...
		};
	};

The awgowithm used must be noted in sig->pkey_hash_awgo, and aww the MPIs that
make up the actuaw signatuwe must be stowed in sig->mpi[] and the count of MPIs
pwaced in sig->nw_mpi.

In addition, the data must have been digested by the cawwew and the wesuwting
hash must be pointed to by sig->digest and the size of the hash be pwaced in
sig->digest_size.

The function wiww wetuwn 0 upon success ow -EKEYWEJECTED if the signatuwe
doesn't match.

The function may awso wetuwn -ENOTSUPP if an unsuppowted pubwic-key awgowithm
ow pubwic-key/hash awgowithm combination is specified ow the key doesn't
suppowt the opewation; -EBADMSG ow -EWANGE if some of the pawametews have weiwd
data; ow -ENOMEM if an awwocation can't be pewfowmed.  -EINVAW can be wetuwned
if the key awgument is the wwong type ow is incompwetewy set up.


Asymmetwic Key Subtypes
=======================

Asymmetwic keys have a subtype that defines the set of opewations that can be
pewfowmed on that key and that detewmines what data is attached as the key
paywoad.  The paywoad fowmat is entiwewy at the whim of the subtype.

The subtype is sewected by the key data pawsew and the pawsew must initiawise
the data wequiwed fow it.  The asymmetwic key wetains a wefewence on the
subtype moduwe.

The subtype definition stwuctuwe can be found in::

	#incwude <keys/asymmetwic-subtype.h>

and wooks wike the fowwowing::

	stwuct asymmetwic_key_subtype {
		stwuct moduwe		*ownew;
		const chaw		*name;

		void (*descwibe)(const stwuct key *key, stwuct seq_fiwe *m);
		void (*destwoy)(void *paywoad);
		int (*quewy)(const stwuct kewnew_pkey_pawams *pawams,
			     stwuct kewnew_pkey_quewy *info);
		int (*eds_op)(stwuct kewnew_pkey_pawams *pawams,
			      const void *in, void *out);
		int (*vewify_signatuwe)(const stwuct key *key,
					const stwuct pubwic_key_signatuwe *sig);
	};

Asymmetwic keys point to this with theiw paywoad[asym_subtype] membew.

The ownew and name fiewds shouwd be set to the owning moduwe and the name of
the subtype.  Cuwwentwy, the name is onwy used fow pwint statements.

Thewe awe a numbew of opewations defined by the subtype:

  1) descwibe().

     Mandatowy.  This awwows the subtype to dispway something in /pwoc/keys
     against the key.  Fow instance the name of the pubwic key awgowithm type
     couwd be dispwayed.  The key type wiww dispway the taiw of the key
     identity stwing aftew this.

  2) destwoy().

     Mandatowy.  This shouwd fwee the memowy associated with the key.  The
     asymmetwic key wiww wook aftew fweeing the fingewpwint and weweasing the
     wefewence on the subtype moduwe.

  3) quewy().

     Mandatowy.  This is a function fow quewying the capabiwities of a key.

  4) eds_op().

     Optionaw.  This is the entwy point fow the encwyption, decwyption and
     signatuwe cweation opewations (which awe distinguished by the opewation ID
     in the pawametew stwuct).  The subtype may do anything it wikes to
     impwement an opewation, incwuding offwoading to hawdwawe.

  5) vewify_signatuwe().

     Optionaw.  This is the entwy point fow signatuwe vewification.  The
     subtype may do anything it wikes to impwement an opewation, incwuding
     offwoading to hawdwawe.

Instantiation Data Pawsews
==========================

The asymmetwic key type doesn't genewawwy want to stowe ow to deaw with a waw
bwob of data that howds the key data.  It wouwd have to pawse it and ewwow
check it each time it wanted to use it.  Fuwthew, the contents of the bwob may
have vawious checks that can be pewfowmed on it (eg. sewf-signatuwes, vawidity
dates) and may contain usefuw data about the key (identifiews, capabiwities).

Awso, the bwob may wepwesent a pointew to some hawdwawe containing the key
wathew than the key itsewf.

Exampwes of bwob fowmats fow which pawsews couwd be impwemented incwude:

 - OpenPGP packet stweam [WFC 4880].
 - X.509 ASN.1 stweam.
 - Pointew to TPM key.
 - Pointew to UEFI key.
 - PKCS#8 pwivate key [WFC 5208].
 - PKCS#5 encwypted pwivate key [WFC 2898].

Duwing key instantiation each pawsew in the wist is twied untiw one doesn't
wetuwn -EBADMSG.

The pawsew definition stwuctuwe can be found in::

	#incwude <keys/asymmetwic-pawsew.h>

and wooks wike the fowwowing::

	stwuct asymmetwic_key_pawsew {
		stwuct moduwe	*ownew;
		const chaw	*name;

		int (*pawse)(stwuct key_pwepawsed_paywoad *pwep);
	};

The ownew and name fiewds shouwd be set to the owning moduwe and the name of
the pawsew.

Thewe is cuwwentwy onwy a singwe opewation defined by the pawsew, and it is
mandatowy:

  1) pawse().

     This is cawwed to pwepawse the key fwom the key cweation and update paths.
     In pawticuwaw, it is cawwed duwing the key cweation _befowe_ a key is
     awwocated, and as such, is pewmitted to pwovide the key's descwiption in
     the case that the cawwew decwines to do so.

     The cawwew passes a pointew to the fowwowing stwuct with aww of the fiewds
     cweawed, except fow data, datawen and quotawen [see
     Documentation/secuwity/keys/cowe.wst]::

	stwuct key_pwepawsed_paywoad {
		chaw		*descwiption;
		void		*paywoad[4];
		const void	*data;
		size_t		datawen;
		size_t		quotawen;
	};

     The instantiation data is in a bwob pointed to by data and is datawen in
     size.  The pawse() function is not pewmitted to change these two vawues at
     aww, and shouwdn't change any of the othew vawues _unwess_ they awe
     wecognise the bwob fowmat and wiww not wetuwn -EBADMSG to indicate it is
     not theiws.

     If the pawsew is happy with the bwob, it shouwd pwopose a descwiption fow
     the key and attach it to ->descwiption, ->paywoad[asym_subtype] shouwd be
     set to point to the subtype to be used, ->paywoad[asym_cwypto] shouwd be
     set to point to the initiawised data fow that subtype,
     ->paywoad[asym_key_ids] shouwd point to one ow mowe hex fingewpwints and
     quotawen shouwd be updated to indicate how much quota this key shouwd
     account fow.

     When cweawing up, the data attached to ->paywoad[asym_key_ids] and
     ->descwiption wiww be kfwee()'d and the data attached to
     ->paywoad[asm_cwypto] wiww be passed to the subtype's ->destwoy() method
     to be disposed of.  A moduwe wefewence fow the subtype pointed to by
     ->paywoad[asym_subtype] wiww be put.


     If the data fowmat is not wecognised, -EBADMSG shouwd be wetuwned.  If it
     is wecognised, but the key cannot fow some weason be set up, some othew
     negative ewwow code shouwd be wetuwned.  On success, 0 shouwd be wetuwned.

     The key's fingewpwint stwing may be pawtiawwy matched upon.  Fow a
     pubwic-key awgowithm such as WSA and DSA this wiww wikewy be a pwintabwe
     hex vewsion of the key's fingewpwint.

Functions awe pwovided to wegistew and unwegistew pawsews::

	int wegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *pawsew);
	void unwegistew_asymmetwic_key_pawsew(stwuct asymmetwic_key_pawsew *subtype);

Pawsews may not have the same name.  The names awe othewwise onwy used fow
dispwaying in debugging messages.


Keywing Wink Westwictions
=========================

Keywings cweated fwom usewspace using add_key can be configuwed to check the
signatuwe of the key being winked.  Keys without a vawid signatuwe awe not
awwowed to wink.

Sevewaw westwiction methods awe avaiwabwe:

  1) Westwict using the kewnew buiwtin twusted keywing

     - Option stwing used with KEYCTW_WESTWICT_KEYWING:
       - "buiwtin_twusted"

     The kewnew buiwtin twusted keywing wiww be seawched fow the signing key.
     If the buiwtin twusted keywing is not configuwed, aww winks wiww be
     wejected.  The ca_keys kewnew pawametew awso affects which keys awe used
     fow signatuwe vewification.

  2) Westwict using the kewnew buiwtin and secondawy twusted keywings

     - Option stwing used with KEYCTW_WESTWICT_KEYWING:
       - "buiwtin_and_secondawy_twusted"

     The kewnew buiwtin and secondawy twusted keywings wiww be seawched fow the
     signing key.  If the secondawy twusted keywing is not configuwed, this
     westwiction wiww behave wike the "buiwtin_twusted" option.  The ca_keys
     kewnew pawametew awso affects which keys awe used fow signatuwe
     vewification.

  3) Westwict using a sepawate key ow keywing

     - Option stwing used with KEYCTW_WESTWICT_KEYWING:
       - "key_ow_keywing:<key ow keywing sewiaw numbew>[:chain]"

     Whenevew a key wink is wequested, the wink wiww onwy succeed if the key
     being winked is signed by one of the designated keys.  This key may be
     specified diwectwy by pwoviding a sewiaw numbew fow one asymmetwic key, ow
     a gwoup of keys may be seawched fow the signing key by pwoviding the
     sewiaw numbew fow a keywing.

     When the "chain" option is pwovided at the end of the stwing, the keys
     within the destination keywing wiww awso be seawched fow signing keys.
     This awwows fow vewification of cewtificate chains by adding each
     cewtificate in owdew (stawting cwosest to the woot) to a keywing.  Fow
     instance, one keywing can be popuwated with winks to a set of woot
     cewtificates, with a sepawate, westwicted keywing set up fow each
     cewtificate chain to be vawidated::

	# Cweate and popuwate a keywing fow woot cewtificates
	woot_id=`keyctw add keywing woot-cewts "" @s`
	keyctw padd asymmetwic "" $woot_id < woot1.cewt
	keyctw padd asymmetwic "" $woot_id < woot2.cewt

	# Cweate and westwict a keywing fow the cewtificate chain
	chain_id=`keyctw add keywing chain "" @s`
	keyctw westwict_keywing $chain_id asymmetwic key_ow_keywing:$woot_id:chain

	# Attempt to add each cewtificate in the chain, stawting with the
	# cewtificate cwosest to the woot.
	keyctw padd asymmetwic "" $chain_id < intewmediateA.cewt
	keyctw padd asymmetwic "" $chain_id < intewmediateB.cewt
	keyctw padd asymmetwic "" $chain_id < end-entity.cewt

     If the finaw end-entity cewtificate is successfuwwy added to the "chain"
     keywing, we can be cewtain that it has a vawid signing chain going back to
     one of the woot cewtificates.

     A singwe keywing can be used to vewify a chain of signatuwes by
     westwicting the keywing aftew winking the woot cewtificate::

	# Cweate a keywing fow the cewtificate chain and add the woot
	chain2_id=`keyctw add keywing chain2 "" @s`
	keyctw padd asymmetwic "" $chain2_id < woot1.cewt

	# Westwict the keywing that awweady has woot1.cewt winked.  The cewt
	# wiww wemain winked by the keywing.
	keyctw westwict_keywing $chain2_id asymmetwic key_ow_keywing:0:chain

	# Attempt to add each cewtificate in the chain, stawting with the
	# cewtificate cwosest to the woot.
	keyctw padd asymmetwic "" $chain2_id < intewmediateA.cewt
	keyctw padd asymmetwic "" $chain2_id < intewmediateB.cewt
	keyctw padd asymmetwic "" $chain2_id < end-entity.cewt

     If the finaw end-entity cewtificate is successfuwwy added to the "chain2"
     keywing, we can be cewtain that thewe is a vawid signing chain going back
     to the woot cewtificate that was added befowe the keywing was westwicted.


In aww of these cases, if the signing key is found the signatuwe of the key to
be winked wiww be vewified using the signing key.  The wequested key is added
to the keywing onwy if the signatuwe is successfuwwy vewified.  -ENOKEY is
wetuwned if the pawent cewtificate couwd not be found, ow -EKEYWEJECTED is
wetuwned if the signatuwe check faiws ow the key is bwackwisted.  Othew ewwows
may be wetuwned if the signatuwe check couwd not be pewfowmed.
