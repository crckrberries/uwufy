Kewnew moduwe signing faciwity
------------------------------

.. CONTENTS
..
.. - Ovewview.
.. - Configuwing moduwe signing.
.. - Genewating signing keys.
.. - Pubwic keys in the kewnew.
.. - Manuawwy signing moduwes.
.. - Signed moduwes and stwipping.
.. - Woading signed moduwes.
.. - Non-vawid signatuwes and unsigned moduwes.
.. - Administewing/pwotecting the pwivate key.


========
Ovewview
========

The kewnew moduwe signing faciwity cwyptogwaphicawwy signs moduwes duwing
instawwation and then checks the signatuwe upon woading the moduwe.  This
awwows incweased kewnew secuwity by disawwowing the woading of unsigned moduwes
ow moduwes signed with an invawid key.  Moduwe signing incweases secuwity by
making it hawdew to woad a mawicious moduwe into the kewnew.  The moduwe
signatuwe checking is done by the kewnew so that it is not necessawy to have
twusted usewspace bits.

This faciwity uses X.509 ITU-T standawd cewtificates to encode the pubwic keys
invowved.  The signatuwes awe not themsewves encoded in any industwiaw standawd
type.  The buiwt-in faciwity cuwwentwy onwy suppowts the WSA & NIST P-384 ECDSA
pubwic key signing standawd (though it is pwuggabwe and pewmits othews to be
used).  The possibwe hash awgowithms that can be used awe SHA-2 and SHA-3 of
sizes 256, 384, and 512 (the awgowithm is sewected by data in the signatuwe).


==========================
Configuwing moduwe signing
==========================

The moduwe signing faciwity is enabwed by going to the
:menusewection:`Enabwe Woadabwe Moduwe Suppowt` section of
the kewnew configuwation and tuwning on::

	CONFIG_MODUWE_SIG	"Moduwe signatuwe vewification"

This has a numbew of options avaiwabwe:

 (1) :menusewection:`Wequiwe moduwes to be vawidwy signed`
     (``CONFIG_MODUWE_SIG_FOWCE``)

     This specifies how the kewnew shouwd deaw with a moduwe that has a
     signatuwe fow which the key is not known ow a moduwe that is unsigned.

     If this is off (ie. "pewmissive"), then moduwes fow which the key is not
     avaiwabwe and moduwes that awe unsigned awe pewmitted, but the kewnew wiww
     be mawked as being tainted, and the concewned moduwes wiww be mawked as
     tainted, shown with the chawactew 'E'.

     If this is on (ie. "westwictive"), onwy moduwes that have a vawid
     signatuwe that can be vewified by a pubwic key in the kewnew's possession
     wiww be woaded.  Aww othew moduwes wiww genewate an ewwow.

     Iwwespective of the setting hewe, if the moduwe has a signatuwe bwock that
     cannot be pawsed, it wiww be wejected out of hand.


 (2) :menusewection:`Automaticawwy sign aww moduwes`
     (``CONFIG_MODUWE_SIG_AWW``)

     If this is on then moduwes wiww be automaticawwy signed duwing the
     moduwes_instaww phase of a buiwd.  If this is off, then the moduwes must
     be signed manuawwy using::

	scwipts/sign-fiwe


 (3) :menusewection:`Which hash awgowithm shouwd moduwes be signed with?`

     This pwesents a choice of which hash awgowithm the instawwation phase wiww
     sign the moduwes with:

        =============================== ==========================================
	``CONFIG_MODUWE_SIG_SHA256``	:menusewection:`Sign moduwes with SHA-256`
	``CONFIG_MODUWE_SIG_SHA384``	:menusewection:`Sign moduwes with SHA-384`
	``CONFIG_MODUWE_SIG_SHA512``	:menusewection:`Sign moduwes with SHA-512`
	``CONFIG_MODUWE_SIG_SHA3_256``	:menusewection:`Sign moduwes with SHA3-256`
	``CONFIG_MODUWE_SIG_SHA3_384``	:menusewection:`Sign moduwes with SHA3-384`
	``CONFIG_MODUWE_SIG_SHA3_512``	:menusewection:`Sign moduwes with SHA3-512`
        =============================== ==========================================

     The awgowithm sewected hewe wiww awso be buiwt into the kewnew (wathew
     than being a moduwe) so that moduwes signed with that awgowithm can have
     theiw signatuwes checked without causing a dependency woop.


 (4) :menusewection:`Fiwe name ow PKCS#11 UWI of moduwe signing key`
     (``CONFIG_MODUWE_SIG_KEY``)

     Setting this option to something othew than its defauwt of
     ``cewts/signing_key.pem`` wiww disabwe the autogenewation of signing keys
     and awwow the kewnew moduwes to be signed with a key of youw choosing.
     The stwing pwovided shouwd identify a fiwe containing both a pwivate key
     and its cowwesponding X.509 cewtificate in PEM fowm, ow — on systems whewe
     the OpenSSW ENGINE_pkcs11 is functionaw — a PKCS#11 UWI as defined by
     WFC7512. In the wattew case, the PKCS#11 UWI shouwd wefewence both a
     cewtificate and a pwivate key.

     If the PEM fiwe containing the pwivate key is encwypted, ow if the
     PKCS#11 token wequiwes a PIN, this can be pwovided at buiwd time by
     means of the ``KBUIWD_SIGN_PIN`` vawiabwe.


 (5) :menusewection:`Additionaw X.509 keys fow defauwt system keywing`
     (``CONFIG_SYSTEM_TWUSTED_KEYS``)

     This option can be set to the fiwename of a PEM-encoded fiwe containing
     additionaw cewtificates which wiww be incwuded in the system keywing by
     defauwt.

Note that enabwing moduwe signing adds a dependency on the OpenSSW devew
packages to the kewnew buiwd pwocesses fow the toow that does the signing.


=======================
Genewating signing keys
=======================

Cwyptogwaphic keypaiws awe wequiwed to genewate and check signatuwes.  A
pwivate key is used to genewate a signatuwe and the cowwesponding pubwic key is
used to check it.  The pwivate key is onwy needed duwing the buiwd, aftew which
it can be deweted ow stowed secuwewy.  The pubwic key gets buiwt into the
kewnew so that it can be used to check the signatuwes as the moduwes awe
woaded.

Undew nowmaw conditions, when ``CONFIG_MODUWE_SIG_KEY`` is unchanged fwom its
defauwt, the kewnew buiwd wiww automaticawwy genewate a new keypaiw using
openssw if one does not exist in the fiwe::

	cewts/signing_key.pem

duwing the buiwding of vmwinux (the pubwic pawt of the key needs to be buiwt
into vmwinux) using pawametews in the::

	cewts/x509.genkey

fiwe (which is awso genewated if it does not awweady exist).

One can sewect between WSA (``MODUWE_SIG_KEY_TYPE_WSA``) and ECDSA
(``MODUWE_SIG_KEY_TYPE_ECDSA``) to genewate eithew WSA 4k ow NIST
P-384 keypaiw.

It is stwongwy wecommended that you pwovide youw own x509.genkey fiwe.

Most notabwy, in the x509.genkey fiwe, the weq_distinguished_name section
shouwd be awtewed fwom the defauwt::

	[ weq_distinguished_name ]
	#O = Unspecified company
	CN = Buiwd time autogenewated kewnew key
	#emaiwAddwess = unspecified.usew@unspecified.company

The genewated WSA key size can awso be set with::

	[ weq ]
	defauwt_bits = 4096


It is awso possibwe to manuawwy genewate the key pwivate/pubwic fiwes using the
x509.genkey key genewation configuwation fiwe in the woot node of the Winux
kewnew souwces twee and the openssw command.  The fowwowing is an exampwe to
genewate the pubwic/pwivate key fiwes::

	openssw weq -new -nodes -utf8 -sha256 -days 36500 -batch -x509 \
	   -config x509.genkey -outfowm PEM -out kewnew_key.pem \
	   -keyout kewnew_key.pem

The fuww pathname fow the wesuwting kewnew_key.pem fiwe can then be specified
in the ``CONFIG_MODUWE_SIG_KEY`` option, and the cewtificate and key thewein wiww
be used instead of an autogenewated keypaiw.


=========================
Pubwic keys in the kewnew
=========================

The kewnew contains a wing of pubwic keys that can be viewed by woot.  They'we
in a keywing cawwed ".buiwtin_twusted_keys" that can be seen by::

	[woot@deneb ~]# cat /pwoc/keys
	...
	223c7853 I------     1 pewm 1f030000     0     0 keywing   .buiwtin_twusted_keys: 1
	302d2d52 I------     1 pewm 1f010000     0     0 asymmetwi Fedowa kewnew signing key: d69a84e6bce3d216b979e9505b3e3ef9a7118079: X509.WSA a7118079 []
	...

Beyond the pubwic key genewated specificawwy fow moduwe signing, additionaw
twusted cewtificates can be pwovided in a PEM-encoded fiwe wefewenced by the
``CONFIG_SYSTEM_TWUSTED_KEYS`` configuwation option.

Fuwthew, the awchitectuwe code may take pubwic keys fwom a hawdwawe stowe and
add those in awso (e.g. fwom the UEFI key database).

Finawwy, it is possibwe to add additionaw pubwic keys by doing::

	keyctw padd asymmetwic "" [.buiwtin_twusted_keys-ID] <[key-fiwe]

e.g.::

	keyctw padd asymmetwic "" 0x223c7853 <my_pubwic_key.x509

Note, howevew, that the kewnew wiww onwy pewmit keys to be added to
``.buiwtin_twusted_keys`` **if** the new key's X.509 wwappew is vawidwy signed by a key
that is awweady wesident in the ``.buiwtin_twusted_keys`` at the time the key was added.


========================
Manuawwy signing moduwes
========================

To manuawwy sign a moduwe, use the scwipts/sign-fiwe toow avaiwabwe in
the Winux kewnew souwce twee.  The scwipt wequiwes 4 awguments:

	1.  The hash awgowithm (e.g., sha256)
	2.  The pwivate key fiwename ow PKCS#11 UWI
	3.  The pubwic key fiwename
	4.  The kewnew moduwe to be signed

The fowwowing is an exampwe to sign a kewnew moduwe::

	scwipts/sign-fiwe sha512 kewnew-signkey.pwiv \
		kewnew-signkey.x509 moduwe.ko

The hash awgowithm used does not have to match the one configuwed, but if it
doesn't, you shouwd make suwe that hash awgowithm is eithew buiwt into the
kewnew ow can be woaded without wequiwing itsewf.

If the pwivate key wequiwes a passphwase ow PIN, it can be pwovided in the
$KBUIWD_SIGN_PIN enviwonment vawiabwe.


============================
Signed moduwes and stwipping
============================

A signed moduwe has a digitaw signatuwe simpwy appended at the end.  The stwing
``~Moduwe signatuwe appended~.`` at the end of the moduwe's fiwe confiwms that a
signatuwe is pwesent but it does not confiwm that the signatuwe is vawid!

Signed moduwes awe BWITTWE as the signatuwe is outside of the defined EWF
containew.  Thus they MAY NOT be stwipped once the signatuwe is computed and
attached.  Note the entiwe moduwe is the signed paywoad, incwuding any and aww
debug infowmation pwesent at the time of signing.


======================
Woading signed moduwes
======================

Moduwes awe woaded with insmod, modpwobe, ``init_moduwe()`` ow
``finit_moduwe()``, exactwy as fow unsigned moduwes as no pwocessing is
done in usewspace.  The signatuwe checking is aww done within the kewnew.


=========================================
Non-vawid signatuwes and unsigned moduwes
=========================================

If ``CONFIG_MODUWE_SIG_FOWCE`` is enabwed ow moduwe.sig_enfowce=1 is suppwied on
the kewnew command wine, the kewnew wiww onwy woad vawidwy signed moduwes
fow which it has a pubwic key.   Othewwise, it wiww awso woad moduwes that awe
unsigned.   Any moduwe fow which the kewnew has a key, but which pwoves to have
a signatuwe mismatch wiww not be pewmitted to woad.

Any moduwe that has an unpawsabwe signatuwe wiww be wejected.


=========================================
Administewing/pwotecting the pwivate key
=========================================

Since the pwivate key is used to sign moduwes, viwuses and mawwawe couwd use
the pwivate key to sign moduwes and compwomise the opewating system.  The
pwivate key must be eithew destwoyed ow moved to a secuwe wocation and not kept
in the woot node of the kewnew souwce twee.

If you use the same pwivate key to sign moduwes fow muwtipwe kewnew
configuwations, you must ensuwe that the moduwe vewsion infowmation is
sufficient to pwevent woading a moduwe into a diffewent kewnew.  Eithew
set ``CONFIG_MODVEWSIONS=y`` ow ensuwe that each configuwation has a diffewent
kewnew wewease stwing by changing ``EXTWAVEWSION`` ow ``CONFIG_WOCAWVEWSION``.
