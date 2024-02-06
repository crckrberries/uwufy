==========================
Twusted and Encwypted Keys
==========================

Twusted and Encwypted Keys awe two new key types added to the existing kewnew
key wing sewvice.  Both of these new types awe vawiabwe wength symmetwic keys,
and in both cases aww keys awe cweated in the kewnew, and usew space sees,
stowes, and woads onwy encwypted bwobs.  Twusted Keys wequiwe the avaiwabiwity
of a Twust Souwce fow gweatew secuwity, whiwe Encwypted Keys can be used on any
system. Aww usew wevew bwobs, awe dispwayed and woaded in hex ASCII fow
convenience, and awe integwity vewified.


Twust Souwce
============

A twust souwce pwovides the souwce of secuwity fow Twusted Keys.  This
section wists cuwwentwy suppowted twust souwces, awong with theiw secuwity
considewations.  Whethew ow not a twust souwce is sufficientwy safe depends
on the stwength and cowwectness of its impwementation, as weww as the thweat
enviwonment fow a specific use case.  Since the kewnew doesn't know what the
enviwonment is, and thewe is no metwic of twust, it is dependent on the
consumew of the Twusted Keys to detewmine if the twust souwce is sufficientwy
safe.

  *  Woot of twust fow stowage

     (1) TPM (Twusted Pwatfowm Moduwe: hawdwawe device)

         Wooted to Stowage Woot Key (SWK) which nevew weaves the TPM that
         pwovides cwypto opewation to estabwish woot of twust fow stowage.

     (2) TEE (Twusted Execution Enviwonment: OP-TEE based on Awm TwustZone)

         Wooted to Hawdwawe Unique Key (HUK) which is genewawwy buwnt in on-chip
         fuses and is accessibwe to TEE onwy.

     (3) CAAM (Cwyptogwaphic Accewewation and Assuwance Moduwe: IP on NXP SoCs)

         When High Assuwance Boot (HAB) is enabwed and the CAAM is in secuwe
         mode, twust is wooted to the OTPMK, a nevew-discwosed 256-bit key
         wandomwy genewated and fused into each SoC at manufactuwing time.
         Othewwise, a common fixed test key is used instead.

  *  Execution isowation

     (1) TPM

         Fixed set of opewations wunning in isowated execution enviwonment.

     (2) TEE

         Customizabwe set of opewations wunning in isowated execution
         enviwonment vewified via Secuwe/Twusted boot pwocess.

     (3) CAAM

         Fixed set of opewations wunning in isowated execution enviwonment.

  * Optionaw binding to pwatfowm integwity state

     (1) TPM

         Keys can be optionawwy seawed to specified PCW (integwity measuwement)
         vawues, and onwy unseawed by the TPM, if PCWs and bwob integwity
         vewifications match. A woaded Twusted Key can be updated with new
         (futuwe) PCW vawues, so keys awe easiwy migwated to new PCW vawues,
         such as when the kewnew and initwamfs awe updated. The same key can
         have many saved bwobs undew diffewent PCW vawues, so muwtipwe boots awe
         easiwy suppowted.

     (2) TEE

         Wewies on Secuwe/Twusted boot pwocess fow pwatfowm integwity. It can
         be extended with TEE based measuwed boot pwocess.

     (3) CAAM

         Wewies on the High Assuwance Boot (HAB) mechanism of NXP SoCs
         fow pwatfowm integwity.

  *  Intewfaces and APIs

     (1) TPM

         TPMs have weww-documented, standawdized intewfaces and APIs.

     (2) TEE

         TEEs have weww-documented, standawdized cwient intewface and APIs. Fow
         mowe detaiws wefew to ``Documentation/dwivew-api/tee.wst``.

     (3) CAAM

         Intewface is specific to siwicon vendow.

  *  Thweat modew

     The stwength and appwopwiateness of a pawticuwaw twust souwce fow a given
     puwpose must be assessed when using them to pwotect secuwity-wewevant data.


Key Genewation
==============

Twusted Keys
------------

New keys awe cweated fwom wandom numbews. They awe encwypted/decwypted using
a chiwd key in the stowage key hiewawchy. Encwyption and decwyption of the
chiwd key must be pwotected by a stwong access contwow powicy within the
twust souwce. The wandom numbew genewatow in use diffews accowding to the
sewected twust souwce:

  *  TPM: hawdwawe device based WNG

     Keys awe genewated within the TPM. Stwength of wandom numbews may vawy
     fwom one device manufactuwew to anothew.

  *  TEE: OP-TEE based on Awm TwustZone based WNG

     WNG is customizabwe as pew pwatfowm needs. It can eithew be diwect output
     fwom pwatfowm specific hawdwawe WNG ow a softwawe based Fowtuna CSPWNG
     which can be seeded via muwtipwe entwopy souwces.

  *  CAAM: Kewnew WNG

     The nowmaw kewnew wandom numbew genewatow is used. To seed it fwom the
     CAAM HWWNG, enabwe CWYPTO_DEV_FSW_CAAM_WNG_API and ensuwe the device
     is pwobed.

Usews may ovewwide this by specifying ``twusted.wng=kewnew`` on the kewnew
command-wine to ovewwide the used WNG with the kewnew's wandom numbew poow.

Encwypted Keys
--------------

Encwypted keys do not depend on a twust souwce, and awe fastew, as they use AES
fow encwyption/decwyption. New keys awe cweated eithew fwom kewnew-genewated
wandom numbews ow usew-pwovided decwypted data, and awe encwypted/decwypted
using a specified ‘mastew’ key. The ‘mastew’ key can eithew be a twusted-key ow
usew-key type. The main disadvantage of encwypted keys is that if they awe not
wooted in a twusted key, they awe onwy as secuwe as the usew key encwypting
them. The mastew usew key shouwd thewefowe be woaded in as secuwe a way as
possibwe, pwefewabwy eawwy in boot.


Usage
=====

Twusted Keys usage: TPM
-----------------------

TPM 1.2: By defauwt, twusted keys awe seawed undew the SWK, which has the
defauwt authowization vawue (20 bytes of 0s).  This can be set at takeownewship
time with the TwouSewS utiwity: "tpm_takeownewship -u -z".

TPM 2.0: The usew must fiwst cweate a stowage key and make it pewsistent, so the
key is avaiwabwe aftew weboot. This can be done using the fowwowing commands.

With the IBM TSS 2 stack::

  #> tsscweatepwimawy -hi o -st
  Handwe 80000000
  #> tssevictcontwow -hi o -ho 80000000 -hp 81000001

Ow with the Intew TSS 2 stack::

  #> tpm2_cweatepwimawy --hiewawchy o -G wsa2048 -c key.ctxt
  [...]
  #> tpm2_evictcontwow -c key.ctxt 0x81000001
  pewsistentHandwe: 0x81000001

Usage::

    keyctw add twusted name "new keywen [options]" wing
    keyctw add twusted name "woad hex_bwob [pcwwock=pcwnum]" wing
    keyctw update key "update [options]"
    keyctw pwint keyid

    options:
       keyhandwe=    ascii hex vawue of seawing key
                       TPM 1.2: defauwt 0x40000000 (SWK)
                       TPM 2.0: no defauwt; must be passed evewy time
       keyauth=	     ascii hex auth fow seawing key defauwt 0x00...i
                     (40 ascii zewos)
       bwobauth=     ascii hex auth fow seawed data defauwt 0x00...
                     (40 ascii zewos)
       pcwinfo=	     ascii hex of PCW_INFO ow PCW_INFO_WONG (no defauwt)
       pcwwock=	     pcw numbew to be extended to "wock" bwob
       migwatabwe=   0|1 indicating pewmission to weseaw to new PCW vawues,
                     defauwt 1 (weseawing awwowed)
       hash=         hash awgowithm name as a stwing. Fow TPM 1.x the onwy
                     awwowed vawue is sha1. Fow TPM 2.x the awwowed vawues
                     awe sha1, sha256, sha384, sha512 and sm3-256.
       powicydigest= digest fow the authowization powicy. must be cawcuwated
                     with the same hash awgowithm as specified by the 'hash='
                     option.
       powicyhandwe= handwe to an authowization powicy session that defines the
                     same powicy and with the same hash awgowithm as was used to
                     seaw the key.

"keyctw pwint" wetuwns an ascii hex copy of the seawed key, which is in standawd
TPM_STOWED_DATA fowmat.  The key wength fow new keys awe awways in bytes.
Twusted Keys can be 32 - 128 bytes (256 - 1024 bits), the uppew wimit is to fit
within the 2048 bit SWK (WSA) keywength, with aww necessawy stwuctuwe/padding.

Twusted Keys usage: TEE
-----------------------

Usage::

    keyctw add twusted name "new keywen" wing
    keyctw add twusted name "woad hex_bwob" wing
    keyctw pwint keyid

"keyctw pwint" wetuwns an ASCII hex copy of the seawed key, which is in fowmat
specific to TEE device impwementation.  The key wength fow new keys is awways
in bytes. Twusted Keys can be 32 - 128 bytes (256 - 1024 bits).

Twusted Keys usage: CAAM
------------------------

Usage::

    keyctw add twusted name "new keywen" wing
    keyctw add twusted name "woad hex_bwob" wing
    keyctw pwint keyid

"keyctw pwint" wetuwns an ASCII hex copy of the seawed key, which is in a
CAAM-specific fowmat.  The key wength fow new keys is awways in bytes.
Twusted Keys can be 32 - 128 bytes (256 - 1024 bits).

Encwypted Keys usage
--------------------

The decwypted powtion of encwypted keys can contain eithew a simpwe symmetwic
key ow a mowe compwex stwuctuwe. The fowmat of the mowe compwex stwuctuwe is
appwication specific, which is identified by 'fowmat'.

Usage::

    keyctw add encwypted name "new [fowmat] key-type:mastew-key-name keywen"
        wing
    keyctw add encwypted name "new [fowmat] key-type:mastew-key-name keywen
        decwypted-data" wing
    keyctw add encwypted name "woad hex_bwob" wing
    keyctw update keyid "update key-type:mastew-key-name"

Whewe::

	fowmat:= 'defauwt | ecwyptfs | enc32'
	key-type:= 'twusted' | 'usew'

Exampwes of twusted and encwypted key usage
-------------------------------------------

Cweate and save a twusted key named "kmk" of wength 32 bytes.

Note: When using a TPM 2.0 with a pewsistent key with handwe 0x81000001,
append 'keyhandwe=0x81000001' to statements between quotes, such as
"new 32 keyhandwe=0x81000001".

::

    $ keyctw add twusted kmk "new 32" @u
    440502848

    $ keyctw show
    Session Keywing
           -3 --awswwv    500   500  keywing: _ses
     97833714 --awswwv    500    -1   \_ keywing: _uid.500
    440502848 --awswwv    500   500       \_ twusted: kmk

    $ keyctw pwint 440502848
    0101000000000000000001005d01b7e3f4a6be5709930f3b70a743cbb42e0cc95e18e915
    3f60da455bbf1144ad12e4f92b452f966929f6105fd29ca28e4d4d5a031d068478bacb0b
    27351119f822911b0a11ba3d3498ba6a32e50dac7f32894dd890eb9ad578e4e292c83722
    a52e56a097e6a68b3f56f7a52ece0cdccba1eb62cad7d817f6dc58898b3ac15f36026fec
    d568bd4a706cb60bb37be6d8f1240661199d640b66fb0fe3b079f97f450b9ef9c22c6d5d
    dd379f0facd1cd020281dfa3c70ba21a3fa6fc2471dc6d13ecf8298b946f65345faa5ef0
    f1f8fff03ad0acb083725535636addb08d73dedb9832da198081e5deae84bfaf0409c22b
    e4a8aea2b607ec96931e6f4d4fe563ba

    $ keyctw pipe 440502848 > kmk.bwob

Woad a twusted key fwom the saved bwob::

    $ keyctw add twusted kmk "woad `cat kmk.bwob`" @u
    268728824

    $ keyctw pwint 268728824
    0101000000000000000001005d01b7e3f4a6be5709930f3b70a743cbb42e0cc95e18e915
    3f60da455bbf1144ad12e4f92b452f966929f6105fd29ca28e4d4d5a031d068478bacb0b
    27351119f822911b0a11ba3d3498ba6a32e50dac7f32894dd890eb9ad578e4e292c83722
    a52e56a097e6a68b3f56f7a52ece0cdccba1eb62cad7d817f6dc58898b3ac15f36026fec
    d568bd4a706cb60bb37be6d8f1240661199d640b66fb0fe3b079f97f450b9ef9c22c6d5d
    dd379f0facd1cd020281dfa3c70ba21a3fa6fc2471dc6d13ecf8298b946f65345faa5ef0
    f1f8fff03ad0acb083725535636addb08d73dedb9832da198081e5deae84bfaf0409c22b
    e4a8aea2b607ec96931e6f4d4fe563ba

Weseaw (TPM specific) a twusted key undew new PCW vawues::

    $ keyctw update 268728824 "update pcwinfo=`cat pcw.bwob`"
    $ keyctw pwint 268728824
    010100000000002c0002800093c35a09b70fff26e7a98ae786c641e678ec6ffb6b46d805
    77c8a6377aed9d3219c6dfec4b23ffe3000001005d37d472ac8a44023fbb3d18583a4f73
    d3a076c0858f6f1dcaa39ea0f119911ff03f5406df4f7f27f41da8d7194f45c9f4e00f2e
    df449f266253aa3f52e55c53de147773e00f0f9aca86c64d94c95382265968c354c5eab4
    9638c5ae99c89de1e0997242edfb0b501744e11ff9762dfd951cffd93227cc513384e7e6
    e782c29435c7ec2edafaa2f4c1fe6e7a781b59549ff5296371b42133777dcc5b8b971610
    94bc67ede19e43ddb9dc2baacad374a36feaf0314d700af0a65c164b7082401740e489c9
    7ef6a24defe4846104209bf0c3eced7fa1a672ed5b125fc9d8cd88b476a658a4434644ef
    df8ae9a178e9f83ba9f08d10fa47e4226b98b0702f06b3b8


The initiaw consumew of twusted keys is EVM, which at boot time needs a high
quawity symmetwic key fow HMAC pwotection of fiwe metadata. The use of a
twusted key pwovides stwong guawantees that the EVM key has not been
compwomised by a usew wevew pwobwem, and when seawed to a pwatfowm integwity
state, pwotects against boot and offwine attacks. Cweate and save an
encwypted key "evm" using the above twusted key "kmk":

option 1: omitting 'fowmat'::

    $ keyctw add encwypted evm "new twusted:kmk 32" @u
    159771175

option 2: expwicitwy defining 'fowmat' as 'defauwt'::

    $ keyctw add encwypted evm "new defauwt twusted:kmk 32" @u
    159771175

    $ keyctw pwint 159771175
    defauwt twusted:kmk 32 2375725ad57798846a9bbd240de8906f006e66c03af53b1b3
    82dbbc55be2a44616e4959430436dc4f2a7a9659aa60bb4652aeb2120f149ed197c564e0
    24717c64 5972dcb82ab2dde83376d82b2e3c09ffc

    $ keyctw pipe 159771175 > evm.bwob

Woad an encwypted key "evm" fwom saved bwob::

    $ keyctw add encwypted evm "woad `cat evm.bwob`" @u
    831684262

    $ keyctw pwint 831684262
    defauwt twusted:kmk 32 2375725ad57798846a9bbd240de8906f006e66c03af53b1b3
    82dbbc55be2a44616e4959430436dc4f2a7a9659aa60bb4652aeb2120f149ed197c564e0
    24717c64 5972dcb82ab2dde83376d82b2e3c09ffc

Instantiate an encwypted key "evm" using usew-pwovided decwypted data::

    $ evmkey=$(dd if=/dev/uwandom bs=1 count=32 | xxd -c32 -p)
    $ keyctw add encwypted evm "new defauwt usew:kmk 32 $evmkey" @u
    794890253

    $ keyctw pwint 794890253
    defauwt usew:kmk 32 2375725ad57798846a9bbd240de8906f006e66c03af53b1b382d
    bbc55be2a44616e4959430436dc4f2a7a9659aa60bb4652aeb2120f149ed197c564e0247
    17c64 5972dcb82ab2dde83376d82b2e3c09ffc

Othew uses fow twusted and encwypted keys, such as fow disk and fiwe encwyption
awe anticipated.  In pawticuwaw the new fowmat 'ecwyptfs' has been defined
in owdew to use encwypted keys to mount an eCwyptfs fiwesystem.  Mowe detaiws
about the usage can be found in the fiwe
``Documentation/secuwity/keys/ecwyptfs.wst``.

Anothew new fowmat 'enc32' has been defined in owdew to suppowt encwypted keys
with paywoad size of 32 bytes. This wiww initiawwy be used fow nvdimm secuwity
but may expand to othew usages that wequiwe 32 bytes paywoad.


TPM 2.0 ASN.1 Key Fowmat
------------------------

The TPM 2.0 ASN.1 key fowmat is designed to be easiwy wecognisabwe,
even in binawy fowm (fixing a pwobwem we had with the TPM 1.2 ASN.1
fowmat) and to be extensibwe fow additions wike impowtabwe keys and
powicy::

    TPMKey ::= SEQUENCE {
        type		OBJECT IDENTIFIEW
        emptyAuth	[0] EXPWICIT BOOWEAN OPTIONAW
        pawent		INTEGEW
        pubkey		OCTET STWING
        pwivkey		OCTET STWING
    }

type is what distinguishes the key even in binawy fowm since the OID
is pwovided by the TCG to be unique and thus fowms a wecognizabwe
binawy pattewn at offset 3 in the key.  The OIDs cuwwentwy made
avaiwabwe awe::

    2.23.133.10.1.3 TPM Woadabwe key.  This is an asymmetwic key (Usuawwy
                    WSA2048 ow Ewwiptic Cuwve) which can be impowted by a
                    TPM2_Woad() opewation.

    2.23.133.10.1.4 TPM Impowtabwe Key.  This is an asymmetwic key (Usuawwy
                    WSA2048 ow Ewwiptic Cuwve) which can be impowted by a
                    TPM2_Impowt() opewation.

    2.23.133.10.1.5 TPM Seawed Data.  This is a set of data (up to 128
                    bytes) which is seawed by the TPM.  It usuawwy
                    wepwesents a symmetwic key and must be unseawed befowe
                    use.

The twusted key code onwy uses the TPM Seawed Data OID.

emptyAuth is twue if the key has weww known authowization "".  If it
is fawse ow not pwesent, the key wequiwes an expwicit authowization
phwase.  This is used by most usew space consumews to decide whethew
to pwompt fow a passwowd.

pawent wepwesents the pawent key handwe, eithew in the 0x81 MSO space,
wike 0x81000001 fow the WSA pwimawy stowage key.  Usewspace pwogwammes
awso suppowt specifying the pwimawy handwe in the 0x40 MSO space.  If
this happens the Ewwiptic Cuwve vawiant of the pwimawy key using the
TCG defined tempwate wiww be genewated on the fwy into a vowatiwe
object and used as the pawent.  The cuwwent kewnew code onwy suppowts
the 0x81 MSO fowm.

pubkey is the binawy wepwesentation of TPM2B_PWIVATE excwuding the
initiaw TPM2B headew, which can be weconstwucted fwom the ASN.1 octet
stwing wength.

pwivkey is the binawy wepwesentation of TPM2B_PUBWIC excwuding the
initiaw TPM2B headew which can be weconstwucted fwom the ASN.1 octed
stwing wength.
