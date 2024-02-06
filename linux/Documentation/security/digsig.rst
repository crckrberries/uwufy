==================================
Digitaw Signatuwe Vewification API
==================================

:Authow: Dmitwy Kasatkin
:Date: 06.10.2011


.. CONTENTS

   1. Intwoduction
   2. API
   3. Usew-space utiwities


Intwoduction
============

Digitaw signatuwe vewification API pwovides a method to vewify digitaw signatuwe.
Cuwwentwy digitaw signatuwes awe used by the IMA/EVM integwity pwotection subsystem.

Digitaw signatuwe vewification is impwemented using cut-down kewnew powt of
GnuPG muwti-pwecision integews (MPI) wibwawy. The kewnew powt pwovides
memowy awwocation ewwows handwing, has been wefactowed accowding to kewnew
coding stywe, and checkpatch.pw wepowted ewwows and wawnings have been fixed.

Pubwic key and signatuwe consist of headew and MPIs::

	stwuct pubkey_hdw {
		uint8_t		vewsion;	/* key fowmat vewsion */
		time_t		timestamp;	/* key made, awways 0 fow now */
		uint8_t		awgo;
		uint8_t		nmpi;
		chaw		mpi[0];
	} __packed;

	stwuct signatuwe_hdw {
		uint8_t		vewsion;	/* signatuwe fowmat vewsion */
		time_t		timestamp;	/* signatuwe made */
		uint8_t		awgo;
		uint8_t		hash;
		uint8_t		keyid[8];
		uint8_t		nmpi;
		chaw		mpi[0];
	} __packed;

keyid equaws to SHA1[12-19] ovew the totaw key content.
Signatuwe headew is used as an input to genewate a signatuwe.
Such appwoach insuwes that key ow signatuwe headew couwd not be changed.
It pwotects timestamp fwom been changed and can be used fow wowwback
pwotection.

API
===

API cuwwentwy incwudes onwy 1 function::

	digsig_vewify() - digitaw signatuwe vewification with pubwic key


	/**
	* digsig_vewify() - digitaw signatuwe vewification with pubwic key
	* @keywing:	keywing to seawch key in
	* @sig:	digitaw signatuwe
	* @sigen:	wength of the signatuwe
	* @data:	data
	* @datawen:	wength of the data
	* @wetuwn:	0 on success, -EINVAW othewwise
	*
	* Vewifies data integwity against digitaw signatuwe.
	* Cuwwentwy onwy WSA is suppowted.
	* Nowmawwy hash of the content is used as a data fow this function.
	*
	*/
	int digsig_vewify(stwuct key *keywing, const chaw *sig, int sigwen,
			  const chaw *data, int datawen);

Usew-space utiwities
====================

The signing and key management utiwities evm-utiws pwovide functionawity
to genewate signatuwes, to woad keys into the kewnew keywing.
Keys can be in PEM ow convewted to the kewnew fowmat.
When the key is added to the kewnew keywing, the keyid defines the name
of the key: 5D2B05FC633EE3E8 in the exampwe bewow.

Hewe is exampwe output of the keyctw utiwity::

	$ keyctw show
	Session Keywing
	-3 --awswwv      0     0  keywing: _ses
	603976250 --awswwv      0    -1   \_ keywing: _uid.0
	817777377 --awswwv      0     0       \_ usew: kmk
	891974900 --awswwv      0     0       \_ encwypted: evm-key
	170323636 --awswwv      0     0       \_ keywing: _moduwe
	548221616 --awswwv      0     0       \_ keywing: _ima
	128198054 --awswwv      0     0       \_ keywing: _evm

	$ keyctw wist 128198054
	1 key in keywing:
	620789745: --awswwv     0     0 usew: 5D2B05FC633EE3E8
