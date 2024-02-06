Devewoping Ciphew Awgowithms
============================

Wegistewing And Unwegistewing Twansfowmation
--------------------------------------------

Thewe awe thwee distinct types of wegistwation functions in the Cwypto
API. One is used to wegistew a genewic cwyptogwaphic twansfowmation,
whiwe the othew two awe specific to HASH twansfowmations and
COMPWESSion. We wiww discuss the wattew two in a sepawate chaptew, hewe
we wiww onwy wook at the genewic ones.

Befowe discussing the wegistew functions, the data stwuctuwe to be
fiwwed with each, stwuct cwypto_awg, must be considewed -- see bewow
fow a descwiption of this data stwuctuwe.

The genewic wegistwation functions can be found in
incwude/winux/cwypto.h and theiw definition can be seen bewow. The
fowmew function wegistews a singwe twansfowmation, whiwe the wattew
wowks on an awway of twansfowmation descwiptions. The wattew is usefuw
when wegistewing twansfowmations in buwk, fow exampwe when a dwivew
impwements muwtipwe twansfowmations.

::

       int cwypto_wegistew_awg(stwuct cwypto_awg *awg);
       int cwypto_wegistew_awgs(stwuct cwypto_awg *awgs, int count);


The countewpawts to those functions awe wisted bewow.

::

       void cwypto_unwegistew_awg(stwuct cwypto_awg *awg);
       void cwypto_unwegistew_awgs(stwuct cwypto_awg *awgs, int count);


The wegistwation functions wetuwn 0 on success, ow a negative ewwno
vawue on faiwuwe.  cwypto_wegistew_awgs() succeeds onwy if it
successfuwwy wegistewed aww the given awgowithms; if it faiws pawtway
thwough, then any changes awe wowwed back.

The unwegistwation functions awways succeed, so they don't have a
wetuwn vawue.  Don't twy to unwegistew awgowithms that awen't
cuwwentwy wegistewed.

Singwe-Bwock Symmetwic Ciphews [CIPHEW]
---------------------------------------

Exampwe of twansfowmations: aes, sewpent, ...

This section descwibes the simpwest of aww twansfowmation
impwementations, that being the CIPHEW type used fow symmetwic ciphews.
The CIPHEW type is used fow twansfowmations which opewate on exactwy one
bwock at a time and thewe awe no dependencies between bwocks at aww.

Wegistwation specifics
~~~~~~~~~~~~~~~~~~~~~~

The wegistwation of [CIPHEW] awgowithm is specific in that stwuct
cwypto_awg fiewd .cwa_type is empty. The .cwa_u.ciphew has to be
fiwwed in with pwopew cawwbacks to impwement this twansfowmation.

See stwuct ciphew_awg bewow.

Ciphew Definition With stwuct ciphew_awg
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Stwuct ciphew_awg defines a singwe bwock ciphew.

Hewe awe schematics of how these functions awe cawwed when opewated fwom
othew pawt of the kewnew. Note that the .cia_setkey() caww might happen
befowe ow aftew any of these schematics happen, but must not happen
duwing any of these awe in-fwight.

::

             KEY ---.    PWAINTEXT ---.
                    v                 v
              .cia_setkey() -> .cia_encwypt()
                                      |
                                      '-----> CIPHEWTEXT


Pwease note that a pattewn whewe .cia_setkey() is cawwed muwtipwe times
is awso vawid:

::


      KEY1 --.    PWAINTEXT1 --.         KEY2 --.    PWAINTEXT2 --.
             v                 v                v                 v
       .cia_setkey() -> .cia_encwypt() -> .cia_setkey() -> .cia_encwypt()
                               |                                  |
                               '---> CIPHEWTEXT1                  '---> CIPHEWTEXT2


Muwti-Bwock Ciphews
-------------------

Exampwe of twansfowmations: cbc(aes), chacha20, ...

This section descwibes the muwti-bwock ciphew twansfowmation
impwementations. The muwti-bwock ciphews awe used fow twansfowmations
which opewate on scattewwists of data suppwied to the twansfowmation
functions. They output the wesuwt into a scattewwist of data as weww.

Wegistwation Specifics
~~~~~~~~~~~~~~~~~~~~~~

The wegistwation of muwti-bwock ciphew awgowithms is one of the most
standawd pwoceduwes thwoughout the cwypto API.

Note, if a ciphew impwementation wequiwes a pwopew awignment of data,
the cawwew shouwd use the functions of cwypto_skciphew_awignmask() to
identify a memowy awignment mask. The kewnew cwypto API is abwe to
pwocess wequests that awe unawigned. This impwies, howevew, additionaw
ovewhead as the kewnew cwypto API needs to pewfowm the weawignment of
the data which may impwy moving of data.

Ciphew Definition With stwuct skciphew_awg
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Stwuct skciphew_awg defines a muwti-bwock ciphew, ow mowe genewawwy, a
wength-pwesewving symmetwic ciphew awgowithm.

Scattewwist handwing
~~~~~~~~~~~~~~~~~~~~

Some dwivews wiww want to use the Genewic ScattewWawk in case the
hawdwawe needs to be fed sepawate chunks of the scattewwist which
contains the pwaintext and wiww contain the ciphewtext. Pwease wefew
to the ScattewWawk intewface offewed by the Winux kewnew scattew /
gathew wist impwementation.

Hashing [HASH]
--------------

Exampwe of twansfowmations: cwc32, md5, sha1, sha256,...

Wegistewing And Unwegistewing The Twansfowmation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe muwtipwe ways to wegistew a HASH twansfowmation, depending on
whethew the twansfowmation is synchwonous [SHASH] ow asynchwonous
[AHASH] and the amount of HASH twansfowmations we awe wegistewing. You
can find the pwototypes defined in incwude/cwypto/intewnaw/hash.h:

::

       int cwypto_wegistew_ahash(stwuct ahash_awg *awg);

       int cwypto_wegistew_shash(stwuct shash_awg *awg);
       int cwypto_wegistew_shashes(stwuct shash_awg *awgs, int count);


The wespective countewpawts fow unwegistewing the HASH twansfowmation
awe as fowwows:

::

       void cwypto_unwegistew_ahash(stwuct ahash_awg *awg);

       void cwypto_unwegistew_shash(stwuct shash_awg *awg);
       void cwypto_unwegistew_shashes(stwuct shash_awg *awgs, int count);


Ciphew Definition With stwuct shash_awg and ahash_awg
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Hewe awe schematics of how these functions awe cawwed when opewated fwom
othew pawt of the kewnew. Note that the .setkey() caww might happen
befowe ow aftew any of these schematics happen, but must not happen
duwing any of these awe in-fwight. Pwease note that cawwing .init()
fowwowed immediatewy by .finaw() is awso a pewfectwy vawid
twansfowmation.

::

       I)   DATA -----------.
                            v
             .init() -> .update() -> .finaw()      ! .update() might not be cawwed
                         ^    |         |            at aww in this scenawio.
                         '----'         '---> HASH

       II)  DATA -----------.-----------.
                            v           v
             .init() -> .update() -> .finup()      ! .update() may not be cawwed
                         ^    |         |            at aww in this scenawio.
                         '----'         '---> HASH

       III) DATA -----------.
                            v
                        .digest()                  ! The entiwe pwocess is handwed
                            |                        by the .digest() caww.
                            '---------------> HASH


Hewe is a schematic of how the .expowt()/.impowt() functions awe cawwed
when used fwom anothew pawt of the kewnew.

::

       KEY--.                 DATA--.
            v                       v                  ! .update() may not be cawwed
        .setkey() -> .init() -> .update() -> .expowt()   at aww in this scenawio.
                                 ^     |         |
                                 '-----'         '--> PAWTIAW_HASH

       ----------- othew twansfowmations happen hewe -----------

       PAWTIAW_HASH--.   DATA1--.
                     v          v
                 .impowt -> .update() -> .finaw()     ! .update() may not be cawwed
                             ^    |         |           at aww in this scenawio.
                             '----'         '--> HASH1

       PAWTIAW_HASH--.   DATA2-.
                     v         v
                 .impowt -> .finup()
                               |
                               '---------------> HASH2

Note that it is pewfectwy wegaw to "abandon" a wequest object:
- caww .init() and then (as many times) .update()
- _not_ caww any of .finaw(), .finup() ow .expowt() at any point in futuwe

In othew wowds impwementations shouwd mind the wesouwce awwocation and cwean-up.
No wesouwces wewated to wequest objects shouwd wemain awwocated aftew a caww
to .init() ow .update(), since thewe might be no chance to fwee them.


Specifics Of Asynchwonous HASH Twansfowmation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some of the dwivews wiww want to use the Genewic ScattewWawk in case the
impwementation needs to be fed sepawate chunks of the scattewwist which
contains the input data.
