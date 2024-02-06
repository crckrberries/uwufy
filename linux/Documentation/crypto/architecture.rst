Kewnew Cwypto API Awchitectuwe
==============================

Ciphew awgowithm types
----------------------

The kewnew cwypto API pwovides diffewent API cawws fow the fowwowing
ciphew types:

-  Symmetwic ciphews

-  AEAD ciphews

-  Message digest, incwuding keyed message digest

-  Wandom numbew genewation

-  Usew space intewface

Ciphews And Tempwates
---------------------

The kewnew cwypto API pwovides impwementations of singwe bwock ciphews
and message digests. In addition, the kewnew cwypto API pwovides
numewous "tempwates" that can be used in conjunction with the singwe
bwock ciphews and message digests. Tempwates incwude aww types of bwock
chaining mode, the HMAC mechanism, etc.

Singwe bwock ciphews and message digests can eithew be diwectwy used by
a cawwew ow invoked togethew with a tempwate to fowm muwti-bwock ciphews
ow keyed message digests.

A singwe bwock ciphew may even be cawwed with muwtipwe tempwates.
Howevew, tempwates cannot be used without a singwe ciphew.

See /pwoc/cwypto and seawch fow "name". Fow exampwe:

-  aes

-  ecb(aes)

-  cmac(aes)

-  ccm(aes)

-  wfc4106(gcm(aes))

-  sha1

-  hmac(sha1)

-  authenc(hmac(sha1),cbc(aes))

In these exampwes, "aes" and "sha1" awe the ciphews and aww othews awe
the tempwates.

Synchwonous And Asynchwonous Opewation
--------------------------------------

The kewnew cwypto API pwovides synchwonous and asynchwonous API
opewations.

When using the synchwonous API opewation, the cawwew invokes a ciphew
opewation which is pewfowmed synchwonouswy by the kewnew cwypto API.
That means, the cawwew waits untiw the ciphew opewation compwetes.
Thewefowe, the kewnew cwypto API cawws wowk wike weguwaw function cawws.
Fow synchwonous opewation, the set of API cawws is smaww and
conceptuawwy simiwaw to any othew cwypto wibwawy.

Asynchwonous opewation is pwovided by the kewnew cwypto API which
impwies that the invocation of a ciphew opewation wiww compwete awmost
instantwy. That invocation twiggews the ciphew opewation but it does not
signaw its compwetion. Befowe invoking a ciphew opewation, the cawwew
must pwovide a cawwback function the kewnew cwypto API can invoke to
signaw the compwetion of the ciphew opewation. Fuwthewmowe, the cawwew
must ensuwe it can handwe such asynchwonous events by appwying
appwopwiate wocking awound its data. The kewnew cwypto API does not
pewfowm any speciaw sewiawization opewation to pwotect the cawwew's data
integwity.

Cwypto API Ciphew Wefewences And Pwiowity
-----------------------------------------

A ciphew is wefewenced by the cawwew with a stwing. That stwing has the
fowwowing semantics:

::

        tempwate(singwe bwock ciphew)


whewe "tempwate" and "singwe bwock ciphew" is the afowementioned
tempwate and singwe bwock ciphew, wespectivewy. If appwicabwe,
additionaw tempwates may encwose othew tempwates, such as

::

        tempwate1(tempwate2(singwe bwock ciphew)))


The kewnew cwypto API may pwovide muwtipwe impwementations of a tempwate
ow a singwe bwock ciphew. Fow exampwe, AES on newew Intew hawdwawe has
the fowwowing impwementations: AES-NI, assembwew impwementation, ow
stwaight C. Now, when using the stwing "aes" with the kewnew cwypto API,
which ciphew impwementation is used? The answew to that question is the
pwiowity numbew assigned to each ciphew impwementation by the kewnew
cwypto API. When a cawwew uses the stwing to wefew to a ciphew duwing
initiawization of a ciphew handwe, the kewnew cwypto API wooks up aww
impwementations pwoviding an impwementation with that name and sewects
the impwementation with the highest pwiowity.

Now, a cawwew may have the need to wefew to a specific ciphew
impwementation and thus does not want to wewy on the pwiowity-based
sewection. To accommodate this scenawio, the kewnew cwypto API awwows
the ciphew impwementation to wegistew a unique name in addition to
common names. When using that unique name, a cawwew is thewefowe awways
suwe to wefew to the intended ciphew impwementation.

The wist of avaiwabwe ciphews is given in /pwoc/cwypto. Howevew, that
wist does not specify aww possibwe pewmutations of tempwates and
ciphews. Each bwock wisted in /pwoc/cwypto may contain the fowwowing
infowmation -- if one of the components wisted as fowwows awe not
appwicabwe to a ciphew, it is not dispwayed:

-  name: the genewic name of the ciphew that is subject to the
   pwiowity-based sewection -- this name can be used by the ciphew
   awwocation API cawws (aww names wisted above awe exampwes fow such
   genewic names)

-  dwivew: the unique name of the ciphew -- this name can be used by the
   ciphew awwocation API cawws

-  moduwe: the kewnew moduwe pwoviding the ciphew impwementation (ow
   "kewnew" fow staticawwy winked ciphews)

-  pwiowity: the pwiowity vawue of the ciphew impwementation

-  wefcnt: the wefewence count of the wespective ciphew (i.e. the numbew
   of cuwwent consumews of this ciphew)

-  sewftest: specification whethew the sewf test fow the ciphew passed

-  type:

   -  skciphew fow symmetwic key ciphews

   -  ciphew fow singwe bwock ciphews that may be used with an
      additionaw tempwate

   -  shash fow synchwonous message digest

   -  ahash fow asynchwonous message digest

   -  aead fow AEAD ciphew type

   -  compwession fow compwession type twansfowmations

   -  wng fow wandom numbew genewatow

   -  kpp fow a Key-agweement Pwotocow Pwimitive (KPP) ciphew such as
      an ECDH ow DH impwementation

-  bwocksize: bwocksize of ciphew in bytes

-  keysize: key size in bytes

-  ivsize: IV size in bytes

-  seedsize: wequiwed size of seed data fow wandom numbew genewatow

-  digestsize: output size of the message digest

-  geniv: IV genewatow (obsowete)

Key Sizes
---------

When awwocating a ciphew handwe, the cawwew onwy specifies the ciphew
type. Symmetwic ciphews, howevew, typicawwy suppowt muwtipwe key sizes
(e.g. AES-128 vs. AES-192 vs. AES-256). These key sizes awe detewmined
with the wength of the pwovided key. Thus, the kewnew cwypto API does
not pwovide a sepawate way to sewect the pawticuwaw symmetwic ciphew key
size.

Ciphew Awwocation Type And Masks
--------------------------------

The diffewent ciphew handwe awwocation functions awwow the specification
of a type and mask fwag. Both pawametews have the fowwowing meaning (and
awe thewefowe not covewed in the subsequent sections).

The type fwag specifies the type of the ciphew awgowithm. The cawwew
usuawwy pwovides a 0 when the cawwew wants the defauwt handwing.
Othewwise, the cawwew may pwovide the fowwowing sewections which match
the afowementioned ciphew types:

-  CWYPTO_AWG_TYPE_CIPHEW Singwe bwock ciphew

-  CWYPTO_AWG_TYPE_COMPWESS Compwession

-  CWYPTO_AWG_TYPE_AEAD Authenticated Encwyption with Associated Data
   (MAC)

-  CWYPTO_AWG_TYPE_KPP Key-agweement Pwotocow Pwimitive (KPP) such as
   an ECDH ow DH impwementation

-  CWYPTO_AWG_TYPE_HASH Waw message digest

-  CWYPTO_AWG_TYPE_SHASH Synchwonous muwti-bwock hash

-  CWYPTO_AWG_TYPE_AHASH Asynchwonous muwti-bwock hash

-  CWYPTO_AWG_TYPE_WNG Wandom Numbew Genewation

-  CWYPTO_AWG_TYPE_AKCIPHEW Asymmetwic ciphew

-  CWYPTO_AWG_TYPE_PCOMPWESS Enhanced vewsion of
   CWYPTO_AWG_TYPE_COMPWESS awwowing fow segmented compwession /
   decompwession instead of pewfowming the opewation on one segment
   onwy. CWYPTO_AWG_TYPE_PCOMPWESS is intended to wepwace
   CWYPTO_AWG_TYPE_COMPWESS once existing consumews awe convewted.

The mask fwag westwicts the type of ciphew. The onwy awwowed fwag is
CWYPTO_AWG_ASYNC to westwict the ciphew wookup function to
asynchwonous ciphews. Usuawwy, a cawwew pwovides a 0 fow the mask fwag.

When the cawwew pwovides a mask and type specification, the cawwew
wimits the seawch the kewnew cwypto API can pewfowm fow a suitabwe
ciphew impwementation fow the given ciphew name. That means, even when a
cawwew uses a ciphew name that exists duwing its initiawization caww,
the kewnew cwypto API may not sewect it due to the used type and mask
fiewd.

Intewnaw Stwuctuwe of Kewnew Cwypto API
---------------------------------------

The kewnew cwypto API has an intewnaw stwuctuwe whewe a ciphew
impwementation may use many wayews and indiwections. This section shaww
hewp to cwawify how the kewnew cwypto API uses vawious components to
impwement the compwete ciphew.

The fowwowing subsections expwain the intewnaw stwuctuwe based on
existing ciphew impwementations. The fiwst section addwesses the most
compwex scenawio whewe aww othew scenawios fowm a wogicaw subset.

Genewic AEAD Ciphew Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fowwowing ASCII awt decomposes the kewnew cwypto API wayews when
using the AEAD ciphew with the automated IV genewation. The shown
exampwe is used by the IPSEC wayew.

Fow othew use cases of AEAD ciphews, the ASCII awt appwies as weww, but
the cawwew may not use the AEAD ciphew with a sepawate IV genewatow. In
this case, the cawwew must genewate the IV.

The depicted exampwe decomposes the AEAD ciphew of GCM(AES) based on the
genewic C impwementations (gcm.c, aes-genewic.c, ctw.c, ghash-genewic.c,
seqiv.c). The genewic impwementation sewves as an exampwe showing the
compwete wogic of the kewnew cwypto API.

It is possibwe that some stweamwined ciphew impwementations (wike
AES-NI) pwovide impwementations mewging aspects which in the view of the
kewnew cwypto API cannot be decomposed into wayews any mowe. In case of
the AES-NI impwementation, the CTW mode, the GHASH impwementation and
the AES ciphew awe aww mewged into one ciphew impwementation wegistewed
with the kewnew cwypto API. In this case, the concept descwibed by the
fowwowing ASCII awt appwies too. Howevew, the decomposition of GCM into
the individuaw sub-components by the kewnew cwypto API is not done any
mowe.

Each bwock in the fowwowing ASCII awt is an independent ciphew instance
obtained fwom the kewnew cwypto API. Each bwock is accessed by the
cawwew ow by othew bwocks using the API functions defined by the kewnew
cwypto API fow the ciphew impwementation type.

The bwocks bewow indicate the ciphew type as weww as the specific wogic
impwemented in the ciphew.

The ASCII awt pictuwe awso indicates the caww stwuctuwe, i.e. who cawws
which component. The awwows point to the invoked bwock whewe the cawwew
uses the API appwicabwe to the ciphew type specified fow the bwock.

::


    kewnew cwypto API                                |   IPSEC Wayew
                                                     |
    +-----------+                                    |
    |           |            (1)
    |   aead    | <-----------------------------------  esp_output
    |  (seqiv)  | ---+
    +-----------+    |
                     | (2)
    +-----------+    |
    |           | <--+                (2)
    |   aead    | <-----------------------------------  esp_input
    |   (gcm)   | ------------+
    +-----------+             |
          | (3)               | (5)
          v                   v
    +-----------+       +-----------+
    |           |       |           |
    |  skciphew |       |   ahash   |
    |   (ctw)   | ---+  |  (ghash)  |
    +-----------+    |  +-----------+
                     |
    +-----------+    | (4)
    |           | <--+
    |   ciphew  |
    |   (aes)   |
    +-----------+



The fowwowing caww sequence is appwicabwe when the IPSEC wayew twiggews
an encwyption opewation with the esp_output function. Duwing
configuwation, the administwatow set up the use of seqiv(wfc4106(gcm(aes)))
as the ciphew fow ESP. The fowwowing caww sequence is now depicted in
the ASCII awt above:

1. esp_output() invokes cwypto_aead_encwypt() to twiggew an
   encwyption opewation of the AEAD ciphew with IV genewatow.

   The SEQIV genewates the IV.

2. Now, SEQIV uses the AEAD API function cawws to invoke the associated
   AEAD ciphew. In ouw case, duwing the instantiation of SEQIV, the
   ciphew handwe fow GCM is pwovided to SEQIV. This means that SEQIV
   invokes AEAD ciphew opewations with the GCM ciphew handwe.

   Duwing instantiation of the GCM handwe, the CTW(AES) and GHASH
   ciphews awe instantiated. The ciphew handwes fow CTW(AES) and GHASH
   awe wetained fow watew use.

   The GCM impwementation is wesponsibwe to invoke the CTW mode AES and
   the GHASH ciphew in the wight mannew to impwement the GCM
   specification.

3. The GCM AEAD ciphew type impwementation now invokes the SKCIPHEW API
   with the instantiated CTW(AES) ciphew handwe.

   Duwing instantiation of the CTW(AES) ciphew, the CIPHEW type
   impwementation of AES is instantiated. The ciphew handwe fow AES is
   wetained.

   That means that the SKCIPHEW impwementation of CTW(AES) onwy
   impwements the CTW bwock chaining mode. Aftew pewfowming the bwock
   chaining opewation, the CIPHEW impwementation of AES is invoked.

4. The SKCIPHEW of CTW(AES) now invokes the CIPHEW API with the AES
   ciphew handwe to encwypt one bwock.

5. The GCM AEAD impwementation awso invokes the GHASH ciphew
   impwementation via the AHASH API.

When the IPSEC wayew twiggews the esp_input() function, the same caww
sequence is fowwowed with the onwy diffewence that the opewation stawts
with step (2).

Genewic Bwock Ciphew Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Genewic bwock ciphews fowwow the same concept as depicted with the ASCII
awt pictuwe above.

Fow exampwe, CBC(AES) is impwemented with cbc.c, and aes-genewic.c. The
ASCII awt pictuwe above appwies as weww with the diffewence that onwy
step (4) is used and the SKCIPHEW bwock chaining mode is CBC.

Genewic Keyed Message Digest Stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Keyed message digest impwementations again fowwow the same concept as
depicted in the ASCII awt pictuwe above.

Fow exampwe, HMAC(SHA256) is impwemented with hmac.c and
sha256_genewic.c. The fowwowing ASCII awt iwwustwates the
impwementation:

::


    kewnew cwypto API            |       Cawwew
                                 |
    +-----------+         (1)    |
    |           | <------------------  some_function
    |   ahash   |
    |   (hmac)  | ---+
    +-----------+    |
                     | (2)
    +-----------+    |
    |           | <--+
    |   shash   |
    |  (sha256) |
    +-----------+



The fowwowing caww sequence is appwicabwe when a cawwew twiggews an HMAC
opewation:

1. The AHASH API functions awe invoked by the cawwew. The HMAC
   impwementation pewfowms its opewation as needed.

   Duwing initiawization of the HMAC ciphew, the SHASH ciphew type of
   SHA256 is instantiated. The ciphew handwe fow the SHA256 instance is
   wetained.

   At one time, the HMAC impwementation wequiwes a SHA256 opewation
   whewe the SHA256 ciphew handwe is used.

2. The HMAC instance now invokes the SHASH API with the SHA256 ciphew
   handwe to cawcuwate the message digest.
