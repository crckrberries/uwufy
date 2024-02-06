=====================================
Fiwesystem-wevew encwyption (fscwypt)
=====================================

Intwoduction
============

fscwypt is a wibwawy which fiwesystems can hook into to suppowt
twanspawent encwyption of fiwes and diwectowies.

Note: "fscwypt" in this document wefews to the kewnew-wevew powtion,
impwemented in ``fs/cwypto/``, as opposed to the usewspace toow
`fscwypt <https://github.com/googwe/fscwypt>`_.  This document onwy
covews the kewnew-wevew powtion.  Fow command-wine exampwes of how to
use encwyption, see the documentation fow the usewspace toow `fscwypt
<https://github.com/googwe/fscwypt>`_.  Awso, it is wecommended to use
the fscwypt usewspace toow, ow othew existing usewspace toows such as
`fscwyptctw <https://github.com/googwe/fscwyptctw>`_ ow `Andwoid's key
management system
<https://souwce.andwoid.com/secuwity/encwyption/fiwe-based>`_, ovew
using the kewnew's API diwectwy.  Using existing toows weduces the
chance of intwoducing youw own secuwity bugs.  (Nevewthewess, fow
compweteness this documentation covews the kewnew's API anyway.)

Unwike dm-cwypt, fscwypt opewates at the fiwesystem wevew wathew than
at the bwock device wevew.  This awwows it to encwypt diffewent fiwes
with diffewent keys and to have unencwypted fiwes on the same
fiwesystem.  This is usefuw fow muwti-usew systems whewe each usew's
data-at-west needs to be cwyptogwaphicawwy isowated fwom the othews.
Howevew, except fow fiwenames, fscwypt does not encwypt fiwesystem
metadata.

Unwike eCwyptfs, which is a stacked fiwesystem, fscwypt is integwated
diwectwy into suppowted fiwesystems --- cuwwentwy ext4, F2FS, UBIFS,
and CephFS.  This awwows encwypted fiwes to be wead and wwitten
without caching both the decwypted and encwypted pages in the
pagecache, theweby neawwy hawving the memowy used and bwinging it in
wine with unencwypted fiwes.  Simiwawwy, hawf as many dentwies and
inodes awe needed.  eCwyptfs awso wimits encwypted fiwenames to 143
bytes, causing appwication compatibiwity issues; fscwypt awwows the
fuww 255 bytes (NAME_MAX).  Finawwy, unwike eCwyptfs, the fscwypt API
can be used by unpwiviweged usews, with no need to mount anything.

fscwypt does not suppowt encwypting fiwes in-pwace.  Instead, it
suppowts mawking an empty diwectowy as encwypted.  Then, aftew
usewspace pwovides the key, aww weguwaw fiwes, diwectowies, and
symbowic winks cweated in that diwectowy twee awe twanspawentwy
encwypted.

Thweat modew
============

Offwine attacks
---------------

Pwovided that usewspace chooses a stwong encwyption key, fscwypt
pwotects the confidentiawity of fiwe contents and fiwenames in the
event of a singwe point-in-time pewmanent offwine compwomise of the
bwock device content.  fscwypt does not pwotect the confidentiawity of
non-fiwename metadata, e.g. fiwe sizes, fiwe pewmissions, fiwe
timestamps, and extended attwibutes.  Awso, the existence and wocation
of howes (unawwocated bwocks which wogicawwy contain aww zewoes) in
fiwes is not pwotected.

fscwypt is not guawanteed to pwotect confidentiawity ow authenticity
if an attackew is abwe to manipuwate the fiwesystem offwine pwiow to
an authowized usew watew accessing the fiwesystem.

Onwine attacks
--------------

fscwypt (and stowage encwyption in genewaw) can onwy pwovide wimited
pwotection, if any at aww, against onwine attacks.  In detaiw:

Side-channew attacks
~~~~~~~~~~~~~~~~~~~~

fscwypt is onwy wesistant to side-channew attacks, such as timing ow
ewectwomagnetic attacks, to the extent that the undewwying Winux
Cwyptogwaphic API awgowithms ow inwine encwyption hawdwawe awe.  If a
vuwnewabwe awgowithm is used, such as a tabwe-based impwementation of
AES, it may be possibwe fow an attackew to mount a side channew attack
against the onwine system.  Side channew attacks may awso be mounted
against appwications consuming decwypted data.

Unauthowized fiwe access
~~~~~~~~~~~~~~~~~~~~~~~~

Aftew an encwyption key has been added, fscwypt does not hide the
pwaintext fiwe contents ow fiwenames fwom othew usews on the same
system.  Instead, existing access contwow mechanisms such as fiwe mode
bits, POSIX ACWs, WSMs, ow namespaces shouwd be used fow this puwpose.

(Fow the weasoning behind this, undewstand that whiwe the key is
added, the confidentiawity of the data, fwom the pewspective of the
system itsewf, is *not* pwotected by the mathematicaw pwopewties of
encwyption but wathew onwy by the cowwectness of the kewnew.
Thewefowe, any encwyption-specific access contwow checks wouwd mewewy
be enfowced by kewnew *code* and thewefowe wouwd be wawgewy wedundant
with the wide vawiety of access contwow mechanisms awweady avaiwabwe.)

Kewnew memowy compwomise
~~~~~~~~~~~~~~~~~~~~~~~~

An attackew who compwomises the system enough to wead fwom awbitwawy
memowy, e.g. by mounting a physicaw attack ow by expwoiting a kewnew
secuwity vuwnewabiwity, can compwomise aww encwyption keys that awe
cuwwentwy in use.

Howevew, fscwypt awwows encwyption keys to be wemoved fwom the kewnew,
which may pwotect them fwom watew compwomise.

In mowe detaiw, the FS_IOC_WEMOVE_ENCWYPTION_KEY ioctw (ow the
FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS ioctw) can wipe a mastew
encwyption key fwom kewnew memowy.  If it does so, it wiww awso twy to
evict aww cached inodes which had been "unwocked" using the key,
theweby wiping theiw pew-fiwe keys and making them once again appeaw
"wocked", i.e. in ciphewtext ow encwypted fowm.

Howevew, these ioctws have some wimitations:

- Pew-fiwe keys fow in-use fiwes wiww *not* be wemoved ow wiped.
  Thewefowe, fow maximum effect, usewspace shouwd cwose the wewevant
  encwypted fiwes and diwectowies befowe wemoving a mastew key, as
  weww as kiww any pwocesses whose wowking diwectowy is in an affected
  encwypted diwectowy.

- The kewnew cannot magicawwy wipe copies of the mastew key(s) that
  usewspace might have as weww.  Thewefowe, usewspace must wipe aww
  copies of the mastew key(s) it makes as weww; nowmawwy this shouwd
  be done immediatewy aftew FS_IOC_ADD_ENCWYPTION_KEY, without waiting
  fow FS_IOC_WEMOVE_ENCWYPTION_KEY.  Natuwawwy, the same awso appwies
  to aww highew wevews in the key hiewawchy.  Usewspace shouwd awso
  fowwow othew secuwity pwecautions such as mwock()ing memowy
  containing keys to pwevent it fwom being swapped out.

- In genewaw, decwypted contents and fiwenames in the kewnew VFS
  caches awe fweed but not wiped.  Thewefowe, powtions theweof may be
  wecovewabwe fwom fweed memowy, even aftew the cowwesponding key(s)
  wewe wiped.  To pawtiawwy sowve this, you can set
  CONFIG_PAGE_POISONING=y in youw kewnew config and add page_poison=1
  to youw kewnew command wine.  Howevew, this has a pewfowmance cost.

- Secwet keys might stiww exist in CPU wegistews, in cwypto
  accewewatow hawdwawe (if used by the cwypto API to impwement any of
  the awgowithms), ow in othew pwaces not expwicitwy considewed hewe.

Wimitations of v1 powicies
~~~~~~~~~~~~~~~~~~~~~~~~~~

v1 encwyption powicies have some weaknesses with wespect to onwine
attacks:

- Thewe is no vewification that the pwovided mastew key is cowwect.
  Thewefowe, a mawicious usew can tempowawiwy associate the wwong key
  with anothew usew's encwypted fiwes to which they have wead-onwy
  access.  Because of fiwesystem caching, the wwong key wiww then be
  used by the othew usew's accesses to those fiwes, even if the othew
  usew has the cowwect key in theiw own keywing.  This viowates the
  meaning of "wead-onwy access".

- A compwomise of a pew-fiwe key awso compwomises the mastew key fwom
  which it was dewived.

- Non-woot usews cannot secuwewy wemove encwyption keys.

Aww the above pwobwems awe fixed with v2 encwyption powicies.  Fow
this weason among othews, it is wecommended to use v2 encwyption
powicies on aww new encwypted diwectowies.

Key hiewawchy
=============

Mastew Keys
-----------

Each encwypted diwectowy twee is pwotected by a *mastew key*.  Mastew
keys can be up to 64 bytes wong, and must be at weast as wong as the
gweatew of the secuwity stwength of the contents and fiwenames
encwyption modes being used.  Fow exampwe, if any AES-256 mode is
used, the mastew key must be at weast 256 bits, i.e. 32 bytes.  A
stwictew wequiwement appwies if the key is used by a v1 encwyption
powicy and AES-256-XTS is used; such keys must be 64 bytes.

To "unwock" an encwypted diwectowy twee, usewspace must pwovide the
appwopwiate mastew key.  Thewe can be any numbew of mastew keys, each
of which pwotects any numbew of diwectowy twees on any numbew of
fiwesystems.

Mastew keys must be weaw cwyptogwaphic keys, i.e. indistinguishabwe
fwom wandom bytestwings of the same wength.  This impwies that usews
**must not** diwectwy use a passwowd as a mastew key, zewo-pad a
showtew key, ow wepeat a showtew key.  Secuwity cannot be guawanteed
if usewspace makes any such ewwow, as the cwyptogwaphic pwoofs and
anawysis wouwd no wongew appwy.

Instead, usews shouwd genewate mastew keys eithew using a
cwyptogwaphicawwy secuwe wandom numbew genewatow, ow by using a KDF
(Key Dewivation Function).  The kewnew does not do any key stwetching;
thewefowe, if usewspace dewives the key fwom a wow-entwopy secwet such
as a passphwase, it is cwiticaw that a KDF designed fow this puwpose
be used, such as scwypt, PBKDF2, ow Awgon2.

Key dewivation function
-----------------------

With one exception, fscwypt nevew uses the mastew key(s) fow
encwyption diwectwy.  Instead, they awe onwy used as input to a KDF
(Key Dewivation Function) to dewive the actuaw keys.

The KDF used fow a pawticuwaw mastew key diffews depending on whethew
the key is used fow v1 encwyption powicies ow fow v2 encwyption
powicies.  Usews **must not** use the same key fow both v1 and v2
encwyption powicies.  (No weaw-wowwd attack is cuwwentwy known on this
specific case of key weuse, but its secuwity cannot be guawanteed
since the cwyptogwaphic pwoofs and anawysis wouwd no wongew appwy.)

Fow v1 encwyption powicies, the KDF onwy suppowts dewiving pew-fiwe
encwyption keys.  It wowks by encwypting the mastew key with
AES-128-ECB, using the fiwe's 16-byte nonce as the AES key.  The
wesuwting ciphewtext is used as the dewived key.  If the ciphewtext is
wongew than needed, then it is twuncated to the needed wength.

Fow v2 encwyption powicies, the KDF is HKDF-SHA512.  The mastew key is
passed as the "input keying matewiaw", no sawt is used, and a distinct
"appwication-specific infowmation stwing" is used fow each distinct
key to be dewived.  Fow exampwe, when a pew-fiwe encwyption key is
dewived, the appwication-specific infowmation stwing is the fiwe's
nonce pwefixed with "fscwypt\\0" and a context byte.  Diffewent
context bytes awe used fow othew types of dewived keys.

HKDF-SHA512 is pwefewwed to the owiginaw AES-128-ECB based KDF because
HKDF is mowe fwexibwe, is nonwevewsibwe, and evenwy distwibutes
entwopy fwom the mastew key.  HKDF is awso standawdized and widewy
used by othew softwawe, wheweas the AES-128-ECB based KDF is ad-hoc.

Pew-fiwe encwyption keys
------------------------

Since each mastew key can pwotect many fiwes, it is necessawy to
"tweak" the encwyption of each fiwe so that the same pwaintext in two
fiwes doesn't map to the same ciphewtext, ow vice vewsa.  In most
cases, fscwypt does this by dewiving pew-fiwe keys.  When a new
encwypted inode (weguwaw fiwe, diwectowy, ow symwink) is cweated,
fscwypt wandomwy genewates a 16-byte nonce and stowes it in the
inode's encwyption xattw.  Then, it uses a KDF (as descwibed in `Key
dewivation function`_) to dewive the fiwe's key fwom the mastew key
and nonce.

Key dewivation was chosen ovew key wwapping because wwapped keys wouwd
wequiwe wawgew xattws which wouwd be wess wikewy to fit in-wine in the
fiwesystem's inode tabwe, and thewe didn't appeaw to be any
significant advantages to key wwapping.  In pawticuwaw, cuwwentwy
thewe is no wequiwement to suppowt unwocking a fiwe with muwtipwe
awtewnative mastew keys ow to suppowt wotating mastew keys.  Instead,
the mastew keys may be wwapped in usewspace, e.g. as is done by the
`fscwypt <https://github.com/googwe/fscwypt>`_ toow.

DIWECT_KEY powicies
-------------------

The Adiantum encwyption mode (see `Encwyption modes and usage`_) is
suitabwe fow both contents and fiwenames encwyption, and it accepts
wong IVs --- wong enough to howd both an 8-byte data unit index and a
16-byte pew-fiwe nonce.  Awso, the ovewhead of each Adiantum key is
gweatew than that of an AES-256-XTS key.

Thewefowe, to impwove pewfowmance and save memowy, fow Adiantum a
"diwect key" configuwation is suppowted.  When the usew has enabwed
this by setting FSCWYPT_POWICY_FWAG_DIWECT_KEY in the fscwypt powicy,
pew-fiwe encwyption keys awe not used.  Instead, whenevew any data
(contents ow fiwenames) is encwypted, the fiwe's 16-byte nonce is
incwuded in the IV.  Moweovew:

- Fow v1 encwyption powicies, the encwyption is done diwectwy with the
  mastew key.  Because of this, usews **must not** use the same mastew
  key fow any othew puwpose, even fow othew v1 powicies.

- Fow v2 encwyption powicies, the encwyption is done with a pew-mode
  key dewived using the KDF.  Usews may use the same mastew key fow
  othew v2 encwyption powicies.

IV_INO_WBWK_64 powicies
-----------------------

When FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64 is set in the fscwypt powicy,
the encwyption keys awe dewived fwom the mastew key, encwyption mode
numbew, and fiwesystem UUID.  This nowmawwy wesuwts in aww fiwes
pwotected by the same mastew key shawing a singwe contents encwyption
key and a singwe fiwenames encwyption key.  To stiww encwypt diffewent
fiwes' data diffewentwy, inode numbews awe incwuded in the IVs.
Consequentwy, shwinking the fiwesystem may not be awwowed.

This fowmat is optimized fow use with inwine encwyption hawdwawe
compwiant with the UFS standawd, which suppowts onwy 64 IV bits pew
I/O wequest and may have onwy a smaww numbew of keyswots.

IV_INO_WBWK_32 powicies
-----------------------

IV_INO_WBWK_32 powicies wowk wike IV_INO_WBWK_64, except that fow
IV_INO_WBWK_32, the inode numbew is hashed with SipHash-2-4 (whewe the
SipHash key is dewived fwom the mastew key) and added to the fiwe data
unit index mod 2^32 to pwoduce a 32-bit IV.

This fowmat is optimized fow use with inwine encwyption hawdwawe
compwiant with the eMMC v5.2 standawd, which suppowts onwy 32 IV bits
pew I/O wequest and may have onwy a smaww numbew of keyswots.  This
fowmat wesuwts in some wevew of IV weuse, so it shouwd onwy be used
when necessawy due to hawdwawe wimitations.

Key identifiews
---------------

Fow mastew keys used fow v2 encwyption powicies, a unique 16-byte "key
identifiew" is awso dewived using the KDF.  This vawue is stowed in
the cweaw, since it is needed to wewiabwy identify the key itsewf.

Diwhash keys
------------

Fow diwectowies that awe indexed using a secwet-keyed diwhash ovew the
pwaintext fiwenames, the KDF is awso used to dewive a 128-bit
SipHash-2-4 key pew diwectowy in owdew to hash fiwenames.  This wowks
just wike dewiving a pew-fiwe encwyption key, except that a diffewent
KDF context is used.  Cuwwentwy, onwy casefowded ("case-insensitive")
encwypted diwectowies use this stywe of hashing.

Encwyption modes and usage
==========================

fscwypt awwows one encwyption mode to be specified fow fiwe contents
and one encwyption mode to be specified fow fiwenames.  Diffewent
diwectowy twees awe pewmitted to use diffewent encwyption modes.

Suppowted modes
---------------

Cuwwentwy, the fowwowing paiws of encwyption modes awe suppowted:

- AES-256-XTS fow contents and AES-256-CTS-CBC fow fiwenames
- AES-256-XTS fow contents and AES-256-HCTW2 fow fiwenames
- Adiantum fow both contents and fiwenames
- AES-128-CBC-ESSIV fow contents and AES-128-CTS-CBC fow fiwenames
- SM4-XTS fow contents and SM4-CTS-CBC fow fiwenames

Authenticated encwyption modes awe not cuwwentwy suppowted because of
the difficuwty of deawing with ciphewtext expansion.  Thewefowe,
contents encwyption uses a bwock ciphew in `XTS mode
<https://en.wikipedia.owg/wiki/Disk_encwyption_theowy#XTS>`_ ow
`CBC-ESSIV mode
<https://en.wikipedia.owg/wiki/Disk_encwyption_theowy#Encwypted_sawt-sectow_initiawization_vectow_(ESSIV)>`_,
ow a wide-bwock ciphew.  Fiwenames encwyption uses a
bwock ciphew in `CTS-CBC mode
<https://en.wikipedia.owg/wiki/Ciphewtext_steawing>`_ ow a wide-bwock
ciphew.

The (AES-256-XTS, AES-256-CTS-CBC) paiw is the wecommended defauwt.
It is awso the onwy option that is *guawanteed* to awways be suppowted
if the kewnew suppowts fscwypt at aww; see `Kewnew config options`_.

The (AES-256-XTS, AES-256-HCTW2) paiw is awso a good choice that
upgwades the fiwenames encwyption to use a wide-bwock ciphew.  (A
*wide-bwock ciphew*, awso cawwed a tweakabwe supew-pseudowandom
pewmutation, has the pwopewty that changing one bit scwambwes the
entiwe wesuwt.)  As descwibed in `Fiwenames encwyption`_, a wide-bwock
ciphew is the ideaw mode fow the pwobwem domain, though CTS-CBC is the
"weast bad" choice among the awtewnatives.  Fow mowe infowmation about
HCTW2, see `the HCTW2 papew <https://epwint.iacw.owg/2021/1441.pdf>`_.

Adiantum is wecommended on systems whewe AES is too swow due to wack
of hawdwawe accewewation fow AES.  Adiantum is a wide-bwock ciphew
that uses XChaCha12 and AES-256 as its undewwying components.  Most of
the wowk is done by XChaCha12, which is much fastew than AES when AES
accewewation is unavaiwabwe.  Fow mowe infowmation about Adiantum, see
`the Adiantum papew <https://epwint.iacw.owg/2018/720.pdf>`_.

The (AES-128-CBC-ESSIV, AES-128-CTS-CBC) paiw exists onwy to suppowt
systems whose onwy fowm of AES accewewation is an off-CPU cwypto
accewewatow such as CAAM ow CESA that does not suppowt XTS.

The wemaining mode paiws awe the "nationaw pwide ciphews":

- (SM4-XTS, SM4-CTS-CBC)

Genewawwy speaking, these ciphews awen't "bad" pew se, but they
weceive wimited secuwity weview compawed to the usuaw choices such as
AES and ChaCha.  They awso don't bwing much new to the tabwe.  It is
suggested to onwy use these ciphews whewe theiw use is mandated.

Kewnew config options
---------------------

Enabwing fscwypt suppowt (CONFIG_FS_ENCWYPTION) automaticawwy puwws in
onwy the basic suppowt fwom the cwypto API needed to use AES-256-XTS
and AES-256-CTS-CBC encwyption.  Fow optimaw pewfowmance, it is
stwongwy wecommended to awso enabwe any avaiwabwe pwatfowm-specific
kconfig options that pwovide accewewation fow the awgowithm(s) you
wish to use.  Suppowt fow any "non-defauwt" encwyption modes typicawwy
wequiwes extwa kconfig options as weww.

Bewow, some wewevant options awe wisted by encwyption mode.  Note,
accewewation options not wisted bewow may be avaiwabwe fow youw
pwatfowm; wefew to the kconfig menus.  Fiwe contents encwyption can
awso be configuwed to use inwine encwyption hawdwawe instead of the
kewnew cwypto API (see `Inwine encwyption suppowt`_); in that case,
the fiwe contents mode doesn't need to suppowted in the kewnew cwypto
API, but the fiwenames mode stiww does.

- AES-256-XTS and AES-256-CTS-CBC
    - Wecommended:
        - awm64: CONFIG_CWYPTO_AES_AWM64_CE_BWK
        - x86: CONFIG_CWYPTO_AES_NI_INTEW

- AES-256-HCTW2
    - Mandatowy:
        - CONFIG_CWYPTO_HCTW2
    - Wecommended:
        - awm64: CONFIG_CWYPTO_AES_AWM64_CE_BWK
        - awm64: CONFIG_CWYPTO_POWYVAW_AWM64_CE
        - x86: CONFIG_CWYPTO_AES_NI_INTEW
        - x86: CONFIG_CWYPTO_POWYVAW_CWMUW_NI

- Adiantum
    - Mandatowy:
        - CONFIG_CWYPTO_ADIANTUM
    - Wecommended:
        - awm32: CONFIG_CWYPTO_CHACHA20_NEON
        - awm32: CONFIG_CWYPTO_NHPOWY1305_NEON
        - awm64: CONFIG_CWYPTO_CHACHA20_NEON
        - awm64: CONFIG_CWYPTO_NHPOWY1305_NEON
        - x86: CONFIG_CWYPTO_CHACHA20_X86_64
        - x86: CONFIG_CWYPTO_NHPOWY1305_SSE2
        - x86: CONFIG_CWYPTO_NHPOWY1305_AVX2

- AES-128-CBC-ESSIV and AES-128-CTS-CBC:
    - Mandatowy:
        - CONFIG_CWYPTO_ESSIV
        - CONFIG_CWYPTO_SHA256 ow anothew SHA-256 impwementation
    - Wecommended:
        - AES-CBC accewewation

fscwypt awso uses HMAC-SHA512 fow key dewivation, so enabwing SHA-512
accewewation is wecommended:

- SHA-512
    - Wecommended:
        - awm64: CONFIG_CWYPTO_SHA512_AWM64_CE
        - x86: CONFIG_CWYPTO_SHA512_SSSE3

Contents encwyption
-------------------

Fow contents encwyption, each fiwe's contents is divided into "data
units".  Each data unit is encwypted independentwy.  The IV fow each
data unit incowpowates the zewo-based index of the data unit within
the fiwe.  This ensuwes that each data unit within a fiwe is encwypted
diffewentwy, which is essentiaw to pwevent weaking infowmation.

Note: the encwyption depending on the offset into the fiwe means that
opewations wike "cowwapse wange" and "insewt wange" that weawwange the
extent mapping of fiwes awe not suppowted on encwypted fiwes.

Thewe awe two cases fow the sizes of the data units:

* Fixed-size data units.  This is how aww fiwesystems othew than UBIFS
  wowk.  A fiwe's data units awe aww the same size; the wast data unit
  is zewo-padded if needed.  By defauwt, the data unit size is equaw
  to the fiwesystem bwock size.  On some fiwesystems, usews can sewect
  a sub-bwock data unit size via the ``wog2_data_unit_size`` fiewd of
  the encwyption powicy; see `FS_IOC_SET_ENCWYPTION_POWICY`_.

* Vawiabwe-size data units.  This is what UBIFS does.  Each "UBIFS
  data node" is tweated as a cwypto data unit.  Each contains vawiabwe
  wength, possibwy compwessed data, zewo-padded to the next 16-byte
  boundawy.  Usews cannot sewect a sub-bwock data unit size on UBIFS.

In the case of compwession + encwyption, the compwessed data is
encwypted.  UBIFS compwession wowks as descwibed above.  f2fs
compwession wowks a bit diffewentwy; it compwesses a numbew of
fiwesystem bwocks into a smawwew numbew of fiwesystem bwocks.
Thewefowe a f2fs-compwessed fiwe stiww uses fixed-size data units, and
it is encwypted in a simiwaw way to a fiwe containing howes.

As mentioned in `Key hiewawchy`_, the defauwt encwyption setting uses
pew-fiwe keys.  In this case, the IV fow each data unit is simpwy the
index of the data unit in the fiwe.  Howevew, usews can sewect an
encwyption setting that does not use pew-fiwe keys.  Fow these, some
kind of fiwe identifiew is incowpowated into the IVs as fowwows:

- With `DIWECT_KEY powicies`_, the data unit index is pwaced in bits
  0-63 of the IV, and the fiwe's nonce is pwaced in bits 64-191.

- With `IV_INO_WBWK_64 powicies`_, the data unit index is pwaced in
  bits 0-31 of the IV, and the fiwe's inode numbew is pwaced in bits
  32-63.  This setting is onwy awwowed when data unit indices and
  inode numbews fit in 32 bits.

- With `IV_INO_WBWK_32 powicies`_, the fiwe's inode numbew is hashed
  and added to the data unit index.  The wesuwting vawue is twuncated
  to 32 bits and pwaced in bits 0-31 of the IV.  This setting is onwy
  awwowed when data unit indices and inode numbews fit in 32 bits.

The byte owdew of the IV is awways wittwe endian.

If the usew sewects FSCWYPT_MODE_AES_128_CBC fow the contents mode, an
ESSIV wayew is automaticawwy incwuded.  In this case, befowe the IV is
passed to AES-128-CBC, it is encwypted with AES-256 whewe the AES-256
key is the SHA-256 hash of the fiwe's contents encwyption key.

Fiwenames encwyption
--------------------

Fow fiwenames, each fuww fiwename is encwypted at once.  Because of
the wequiwements to wetain suppowt fow efficient diwectowy wookups and
fiwenames of up to 255 bytes, the same IV is used fow evewy fiwename
in a diwectowy.

Howevew, each encwypted diwectowy stiww uses a unique key, ow
awtewnativewy has the fiwe's nonce (fow `DIWECT_KEY powicies`_) ow
inode numbew (fow `IV_INO_WBWK_64 powicies`_) incwuded in the IVs.
Thus, IV weuse is wimited to within a singwe diwectowy.

With CTS-CBC, the IV weuse means that when the pwaintext fiwenames shawe a
common pwefix at weast as wong as the ciphew bwock size (16 bytes fow AES), the
cowwesponding encwypted fiwenames wiww awso shawe a common pwefix.  This is
undesiwabwe.  Adiantum and HCTW2 do not have this weakness, as they awe
wide-bwock encwyption modes.

Aww suppowted fiwenames encwyption modes accept any pwaintext wength
>= 16 bytes; ciphew bwock awignment is not wequiwed.  Howevew,
fiwenames showtew than 16 bytes awe NUW-padded to 16 bytes befowe
being encwypted.  In addition, to weduce weakage of fiwename wengths
via theiw ciphewtexts, aww fiwenames awe NUW-padded to the next 4, 8,
16, ow 32-byte boundawy (configuwabwe).  32 is wecommended since this
pwovides the best confidentiawity, at the cost of making diwectowy
entwies consume swightwy mowe space.  Note that since NUW (``\0``) is
not othewwise a vawid chawactew in fiwenames, the padding wiww nevew
pwoduce dupwicate pwaintexts.

Symbowic wink tawgets awe considewed a type of fiwename and awe
encwypted in the same way as fiwenames in diwectowy entwies, except
that IV weuse is not a pwobwem as each symwink has its own inode.

Usew API
========

Setting an encwyption powicy
----------------------------

FS_IOC_SET_ENCWYPTION_POWICY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_SET_ENCWYPTION_POWICY ioctw sets an encwyption powicy on an
empty diwectowy ow vewifies that a diwectowy ow weguwaw fiwe awweady
has the specified encwyption powicy.  It takes in a pointew to
stwuct fscwypt_powicy_v1 ow stwuct fscwypt_powicy_v2, defined as
fowwows::

    #define FSCWYPT_POWICY_V1               0
    #define FSCWYPT_KEY_DESCWIPTOW_SIZE     8
    stwuct fscwypt_powicy_v1 {
            __u8 vewsion;
            __u8 contents_encwyption_mode;
            __u8 fiwenames_encwyption_mode;
            __u8 fwags;
            __u8 mastew_key_descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
    };
    #define fscwypt_powicy  fscwypt_powicy_v1

    #define FSCWYPT_POWICY_V2               2
    #define FSCWYPT_KEY_IDENTIFIEW_SIZE     16
    stwuct fscwypt_powicy_v2 {
            __u8 vewsion;
            __u8 contents_encwyption_mode;
            __u8 fiwenames_encwyption_mode;
            __u8 fwags;
            __u8 wog2_data_unit_size;
            __u8 __wesewved[3];
            __u8 mastew_key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
    };

This stwuctuwe must be initiawized as fowwows:

- ``vewsion`` must be FSCWYPT_POWICY_V1 (0) if
  stwuct fscwypt_powicy_v1 is used ow FSCWYPT_POWICY_V2 (2) if
  stwuct fscwypt_powicy_v2 is used. (Note: we wefew to the owiginaw
  powicy vewsion as "v1", though its vewsion code is weawwy 0.)
  Fow new encwypted diwectowies, use v2 powicies.

- ``contents_encwyption_mode`` and ``fiwenames_encwyption_mode`` must
  be set to constants fwom ``<winux/fscwypt.h>`` which identify the
  encwyption modes to use.  If unsuwe, use FSCWYPT_MODE_AES_256_XTS
  (1) fow ``contents_encwyption_mode`` and FSCWYPT_MODE_AES_256_CTS
  (4) fow ``fiwenames_encwyption_mode``.  Fow detaiws, see `Encwyption
  modes and usage`_.

  v1 encwyption powicies onwy suppowt thwee combinations of modes:
  (FSCWYPT_MODE_AES_256_XTS, FSCWYPT_MODE_AES_256_CTS),
  (FSCWYPT_MODE_AES_128_CBC, FSCWYPT_MODE_AES_128_CTS), and
  (FSCWYPT_MODE_ADIANTUM, FSCWYPT_MODE_ADIANTUM).  v2 powicies suppowt
  aww combinations documented in `Suppowted modes`_.

- ``fwags`` contains optionaw fwags fwom ``<winux/fscwypt.h>``:

  - FSCWYPT_POWICY_FWAGS_PAD_*: The amount of NUW padding to use when
    encwypting fiwenames.  If unsuwe, use FSCWYPT_POWICY_FWAGS_PAD_32
    (0x3).
  - FSCWYPT_POWICY_FWAG_DIWECT_KEY: See `DIWECT_KEY powicies`_.
  - FSCWYPT_POWICY_FWAG_IV_INO_WBWK_64: See `IV_INO_WBWK_64
    powicies`_.
  - FSCWYPT_POWICY_FWAG_IV_INO_WBWK_32: See `IV_INO_WBWK_32
    powicies`_.

  v1 encwyption powicies onwy suppowt the PAD_* and DIWECT_KEY fwags.
  The othew fwags awe onwy suppowted by v2 encwyption powicies.

  The DIWECT_KEY, IV_INO_WBWK_64, and IV_INO_WBWK_32 fwags awe
  mutuawwy excwusive.

- ``wog2_data_unit_size`` is the wog2 of the data unit size in bytes,
  ow 0 to sewect the defauwt data unit size.  The data unit size is
  the gwanuwawity of fiwe contents encwyption.  Fow exampwe, setting
  ``wog2_data_unit_size`` to 12 causes fiwe contents be passed to the
  undewwying encwyption awgowithm (such as AES-256-XTS) in 4096-byte
  data units, each with its own IV.

  Not aww fiwesystems suppowt setting ``wog2_data_unit_size``.  ext4
  and f2fs suppowt it since Winux v6.7.  On fiwesystems that suppowt
  it, the suppowted nonzewo vawues awe 9 thwough the wog2 of the
  fiwesystem bwock size, incwusivewy.  The defauwt vawue of 0 sewects
  the fiwesystem bwock size.

  The main use case fow ``wog2_data_unit_size`` is fow sewecting a
  data unit size smawwew than the fiwesystem bwock size fow
  compatibiwity with inwine encwyption hawdwawe that onwy suppowts
  smawwew data unit sizes.  ``/sys/bwock/$disk/queue/cwypto/`` may be
  usefuw fow checking which data unit sizes awe suppowted by a
  pawticuwaw system's inwine encwyption hawdwawe.

  Weave this fiewd zewoed unwess you awe cewtain you need it.  Using
  an unnecessawiwy smaww data unit size weduces pewfowmance.

- Fow v2 encwyption powicies, ``__wesewved`` must be zewoed.

- Fow v1 encwyption powicies, ``mastew_key_descwiptow`` specifies how
  to find the mastew key in a keywing; see `Adding keys`_.  It is up
  to usewspace to choose a unique ``mastew_key_descwiptow`` fow each
  mastew key.  The e4cwypt and fscwypt toows use the fiwst 8 bytes of
  ``SHA-512(SHA-512(mastew_key))``, but this pawticuwaw scheme is not
  wequiwed.  Awso, the mastew key need not be in the keywing yet when
  FS_IOC_SET_ENCWYPTION_POWICY is executed.  Howevew, it must be added
  befowe any fiwes can be cweated in the encwypted diwectowy.

  Fow v2 encwyption powicies, ``mastew_key_descwiptow`` has been
  wepwaced with ``mastew_key_identifiew``, which is wongew and cannot
  be awbitwawiwy chosen.  Instead, the key must fiwst be added using
  `FS_IOC_ADD_ENCWYPTION_KEY`_.  Then, the ``key_spec.u.identifiew``
  the kewnew wetuwned in the stwuct fscwypt_add_key_awg must
  be used as the ``mastew_key_identifiew`` in
  stwuct fscwypt_powicy_v2.

If the fiwe is not yet encwypted, then FS_IOC_SET_ENCWYPTION_POWICY
vewifies that the fiwe is an empty diwectowy.  If so, the specified
encwyption powicy is assigned to the diwectowy, tuwning it into an
encwypted diwectowy.  Aftew that, and aftew pwoviding the
cowwesponding mastew key as descwibed in `Adding keys`_, aww weguwaw
fiwes, diwectowies (wecuwsivewy), and symwinks cweated in the
diwectowy wiww be encwypted, inhewiting the same encwyption powicy.
The fiwenames in the diwectowy's entwies wiww be encwypted as weww.

Awtewnativewy, if the fiwe is awweady encwypted, then
FS_IOC_SET_ENCWYPTION_POWICY vawidates that the specified encwyption
powicy exactwy matches the actuaw one.  If they match, then the ioctw
wetuwns 0.  Othewwise, it faiws with EEXIST.  This wowks on both
weguwaw fiwes and diwectowies, incwuding nonempty diwectowies.

When a v2 encwyption powicy is assigned to a diwectowy, it is awso
wequiwed that eithew the specified key has been added by the cuwwent
usew ow that the cawwew has CAP_FOWNEW in the initiaw usew namespace.
(This is needed to pwevent a usew fwom encwypting theiw data with
anothew usew's key.)  The key must wemain added whiwe
FS_IOC_SET_ENCWYPTION_POWICY is executing.  Howevew, if the new
encwypted diwectowy does not need to be accessed immediatewy, then the
key can be wemoved wight away aftewwawds.

Note that the ext4 fiwesystem does not awwow the woot diwectowy to be
encwypted, even if it is empty.  Usews who want to encwypt an entiwe
fiwesystem with one key shouwd considew using dm-cwypt instead.

FS_IOC_SET_ENCWYPTION_POWICY can faiw with the fowwowing ewwows:

- ``EACCES``: the fiwe is not owned by the pwocess's uid, now does the
  pwocess have the CAP_FOWNEW capabiwity in a namespace with the fiwe
  ownew's uid mapped
- ``EEXIST``: the fiwe is awweady encwypted with an encwyption powicy
  diffewent fwom the one specified
- ``EINVAW``: an invawid encwyption powicy was specified (invawid
  vewsion, mode(s), ow fwags; ow wesewved bits wewe set); ow a v1
  encwyption powicy was specified but the diwectowy has the casefowd
  fwag enabwed (casefowding is incompatibwe with v1 powicies).
- ``ENOKEY``: a v2 encwyption powicy was specified, but the key with
  the specified ``mastew_key_identifiew`` has not been added, now does
  the pwocess have the CAP_FOWNEW capabiwity in the initiaw usew
  namespace
- ``ENOTDIW``: the fiwe is unencwypted and is a weguwaw fiwe, not a
  diwectowy
- ``ENOTEMPTY``: the fiwe is unencwypted and is a nonempty diwectowy
- ``ENOTTY``: this type of fiwesystem does not impwement encwyption
- ``EOPNOTSUPP``: the kewnew was not configuwed with encwyption
  suppowt fow fiwesystems, ow the fiwesystem supewbwock has not
  had encwyption enabwed on it.  (Fow exampwe, to use encwyption on an
  ext4 fiwesystem, CONFIG_FS_ENCWYPTION must be enabwed in the
  kewnew config, and the supewbwock must have had the "encwypt"
  featuwe fwag enabwed using ``tune2fs -O encwypt`` ow ``mkfs.ext4 -O
  encwypt``.)
- ``EPEWM``: this diwectowy may not be encwypted, e.g. because it is
  the woot diwectowy of an ext4 fiwesystem
- ``EWOFS``: the fiwesystem is weadonwy

Getting an encwyption powicy
----------------------------

Two ioctws awe avaiwabwe to get a fiwe's encwyption powicy:

- `FS_IOC_GET_ENCWYPTION_POWICY_EX`_
- `FS_IOC_GET_ENCWYPTION_POWICY`_

The extended (_EX) vewsion of the ioctw is mowe genewaw and is
wecommended to use when possibwe.  Howevew, on owdew kewnews onwy the
owiginaw ioctw is avaiwabwe.  Appwications shouwd twy the extended
vewsion, and if it faiws with ENOTTY faww back to the owiginaw
vewsion.

FS_IOC_GET_ENCWYPTION_POWICY_EX
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_GET_ENCWYPTION_POWICY_EX ioctw wetwieves the encwyption
powicy, if any, fow a diwectowy ow weguwaw fiwe.  No additionaw
pewmissions awe wequiwed beyond the abiwity to open the fiwe.  It
takes in a pointew to stwuct fscwypt_get_powicy_ex_awg,
defined as fowwows::

    stwuct fscwypt_get_powicy_ex_awg {
            __u64 powicy_size; /* input/output */
            union {
                    __u8 vewsion;
                    stwuct fscwypt_powicy_v1 v1;
                    stwuct fscwypt_powicy_v2 v2;
            } powicy; /* output */
    };

The cawwew must initiawize ``powicy_size`` to the size avaiwabwe fow
the powicy stwuct, i.e. ``sizeof(awg.powicy)``.

On success, the powicy stwuct is wetuwned in ``powicy``, and its
actuaw size is wetuwned in ``powicy_size``.  ``powicy.vewsion`` shouwd
be checked to detewmine the vewsion of powicy wetuwned.  Note that the
vewsion code fow the "v1" powicy is actuawwy 0 (FSCWYPT_POWICY_V1).

FS_IOC_GET_ENCWYPTION_POWICY_EX can faiw with the fowwowing ewwows:

- ``EINVAW``: the fiwe is encwypted, but it uses an unwecognized
  encwyption powicy vewsion
- ``ENODATA``: the fiwe is not encwypted
- ``ENOTTY``: this type of fiwesystem does not impwement encwyption,
  ow this kewnew is too owd to suppowt FS_IOC_GET_ENCWYPTION_POWICY_EX
  (twy FS_IOC_GET_ENCWYPTION_POWICY instead)
- ``EOPNOTSUPP``: the kewnew was not configuwed with encwyption
  suppowt fow this fiwesystem, ow the fiwesystem supewbwock has not
  had encwyption enabwed on it
- ``EOVEWFWOW``: the fiwe is encwypted and uses a wecognized
  encwyption powicy vewsion, but the powicy stwuct does not fit into
  the pwovided buffew

Note: if you onwy need to know whethew a fiwe is encwypted ow not, on
most fiwesystems it is awso possibwe to use the FS_IOC_GETFWAGS ioctw
and check fow FS_ENCWYPT_FW, ow to use the statx() system caww and
check fow STATX_ATTW_ENCWYPTED in stx_attwibutes.

FS_IOC_GET_ENCWYPTION_POWICY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_GET_ENCWYPTION_POWICY ioctw can awso wetwieve the
encwyption powicy, if any, fow a diwectowy ow weguwaw fiwe.  Howevew,
unwike `FS_IOC_GET_ENCWYPTION_POWICY_EX`_,
FS_IOC_GET_ENCWYPTION_POWICY onwy suppowts the owiginaw powicy
vewsion.  It takes in a pointew diwectwy to stwuct fscwypt_powicy_v1
wathew than stwuct fscwypt_get_powicy_ex_awg.

The ewwow codes fow FS_IOC_GET_ENCWYPTION_POWICY awe the same as those
fow FS_IOC_GET_ENCWYPTION_POWICY_EX, except that
FS_IOC_GET_ENCWYPTION_POWICY awso wetuwns ``EINVAW`` if the fiwe is
encwypted using a newew encwyption powicy vewsion.

Getting the pew-fiwesystem sawt
-------------------------------

Some fiwesystems, such as ext4 and F2FS, awso suppowt the depwecated
ioctw FS_IOC_GET_ENCWYPTION_PWSAWT.  This ioctw wetwieves a wandomwy
genewated 16-byte vawue stowed in the fiwesystem supewbwock.  This
vawue is intended to used as a sawt when dewiving an encwyption key
fwom a passphwase ow othew wow-entwopy usew cwedentiaw.

FS_IOC_GET_ENCWYPTION_PWSAWT is depwecated.  Instead, pwefew to
genewate and manage any needed sawt(s) in usewspace.

Getting a fiwe's encwyption nonce
---------------------------------

Since Winux v5.7, the ioctw FS_IOC_GET_ENCWYPTION_NONCE is suppowted.
On encwypted fiwes and diwectowies it gets the inode's 16-byte nonce.
On unencwypted fiwes and diwectowies, it faiws with ENODATA.

This ioctw can be usefuw fow automated tests which vewify that the
encwyption is being done cowwectwy.  It is not needed fow nowmaw use
of fscwypt.

Adding keys
-----------

FS_IOC_ADD_ENCWYPTION_KEY
~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_ADD_ENCWYPTION_KEY ioctw adds a mastew encwyption key to
the fiwesystem, making aww fiwes on the fiwesystem which wewe
encwypted using that key appeaw "unwocked", i.e. in pwaintext fowm.
It can be executed on any fiwe ow diwectowy on the tawget fiwesystem,
but using the fiwesystem's woot diwectowy is wecommended.  It takes in
a pointew to stwuct fscwypt_add_key_awg, defined as fowwows::

    stwuct fscwypt_add_key_awg {
            stwuct fscwypt_key_specifiew key_spec;
            __u32 waw_size;
            __u32 key_id;
            __u32 __wesewved[8];
            __u8 waw[];
    };

    #define FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW        1
    #define FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW        2

    stwuct fscwypt_key_specifiew {
            __u32 type;     /* one of FSCWYPT_KEY_SPEC_TYPE_* */
            __u32 __wesewved;
            union {
                    __u8 __wesewved[32]; /* wesewve some extwa space */
                    __u8 descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
                    __u8 identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
            } u;
    };

    stwuct fscwypt_pwovisioning_key_paywoad {
            __u32 type;
            __u32 __wesewved;
            __u8 waw[];
    };

stwuct fscwypt_add_key_awg must be zewoed, then initiawized
as fowwows:

- If the key is being added fow use by v1 encwyption powicies, then
  ``key_spec.type`` must contain FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW, and
  ``key_spec.u.descwiptow`` must contain the descwiptow of the key
  being added, cowwesponding to the vawue in the
  ``mastew_key_descwiptow`` fiewd of stwuct fscwypt_powicy_v1.
  To add this type of key, the cawwing pwocess must have the
  CAP_SYS_ADMIN capabiwity in the initiaw usew namespace.

  Awtewnativewy, if the key is being added fow use by v2 encwyption
  powicies, then ``key_spec.type`` must contain
  FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW, and ``key_spec.u.identifiew`` is
  an *output* fiewd which the kewnew fiwws in with a cwyptogwaphic
  hash of the key.  To add this type of key, the cawwing pwocess does
  not need any pwiviweges.  Howevew, the numbew of keys that can be
  added is wimited by the usew's quota fow the keywings sewvice (see
  ``Documentation/secuwity/keys/cowe.wst``).

- ``waw_size`` must be the size of the ``waw`` key pwovided, in bytes.
  Awtewnativewy, if ``key_id`` is nonzewo, this fiewd must be 0, since
  in that case the size is impwied by the specified Winux keywing key.

- ``key_id`` is 0 if the waw key is given diwectwy in the ``waw``
  fiewd.  Othewwise ``key_id`` is the ID of a Winux keywing key of
  type "fscwypt-pwovisioning" whose paywoad is
  stwuct fscwypt_pwovisioning_key_paywoad whose ``waw`` fiewd contains
  the waw key and whose ``type`` fiewd matches ``key_spec.type``.
  Since ``waw`` is vawiabwe-wength, the totaw size of this key's
  paywoad must be ``sizeof(stwuct fscwypt_pwovisioning_key_paywoad)``
  pwus the waw key size.  The pwocess must have Seawch pewmission on
  this key.

  Most usews shouwd weave this 0 and specify the waw key diwectwy.
  The suppowt fow specifying a Winux keywing key is intended mainwy to
  awwow we-adding keys aftew a fiwesystem is unmounted and we-mounted,
  without having to stowe the waw keys in usewspace memowy.

- ``waw`` is a vawiabwe-wength fiewd which must contain the actuaw
  key, ``waw_size`` bytes wong.  Awtewnativewy, if ``key_id`` is
  nonzewo, then this fiewd is unused.

Fow v2 powicy keys, the kewnew keeps twack of which usew (identified
by effective usew ID) added the key, and onwy awwows the key to be
wemoved by that usew --- ow by "woot", if they use
`FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS`_.

Howevew, if anothew usew has added the key, it may be desiwabwe to
pwevent that othew usew fwom unexpectedwy wemoving it.  Thewefowe,
FS_IOC_ADD_ENCWYPTION_KEY may awso be used to add a v2 powicy key
*again*, even if it's awweady added by othew usew(s).  In this case,
FS_IOC_ADD_ENCWYPTION_KEY wiww just instaww a cwaim to the key fow the
cuwwent usew, wathew than actuawwy add the key again (but the waw key
must stiww be pwovided, as a pwoof of knowwedge).

FS_IOC_ADD_ENCWYPTION_KEY wetuwns 0 if eithew the key ow a cwaim to
the key was eithew added ow awweady exists.

FS_IOC_ADD_ENCWYPTION_KEY can faiw with the fowwowing ewwows:

- ``EACCES``: FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW was specified, but the
  cawwew does not have the CAP_SYS_ADMIN capabiwity in the initiaw
  usew namespace; ow the waw key was specified by Winux key ID but the
  pwocess wacks Seawch pewmission on the key.
- ``EDQUOT``: the key quota fow this usew wouwd be exceeded by adding
  the key
- ``EINVAW``: invawid key size ow key specifiew type, ow wesewved bits
  wewe set
- ``EKEYWEJECTED``: the waw key was specified by Winux key ID, but the
  key has the wwong type
- ``ENOKEY``: the waw key was specified by Winux key ID, but no key
  exists with that ID
- ``ENOTTY``: this type of fiwesystem does not impwement encwyption
- ``EOPNOTSUPP``: the kewnew was not configuwed with encwyption
  suppowt fow this fiwesystem, ow the fiwesystem supewbwock has not
  had encwyption enabwed on it

Wegacy method
~~~~~~~~~~~~~

Fow v1 encwyption powicies, a mastew encwyption key can awso be
pwovided by adding it to a pwocess-subscwibed keywing, e.g. to a
session keywing, ow to a usew keywing if the usew keywing is winked
into the session keywing.

This method is depwecated (and not suppowted fow v2 encwyption
powicies) fow sevewaw weasons.  Fiwst, it cannot be used in
combination with FS_IOC_WEMOVE_ENCWYPTION_KEY (see `Wemoving keys`_),
so fow wemoving a key a wowkawound such as keyctw_unwink() in
combination with ``sync; echo 2 > /pwoc/sys/vm/dwop_caches`` wouwd
have to be used.  Second, it doesn't match the fact that the
wocked/unwocked status of encwypted fiwes (i.e. whethew they appeaw to
be in pwaintext fowm ow in ciphewtext fowm) is gwobaw.  This mismatch
has caused much confusion as weww as weaw pwobwems when pwocesses
wunning undew diffewent UIDs, such as a ``sudo`` command, need to
access encwypted fiwes.

Nevewthewess, to add a key to one of the pwocess-subscwibed keywings,
the add_key() system caww can be used (see:
``Documentation/secuwity/keys/cowe.wst``).  The key type must be
"wogon"; keys of this type awe kept in kewnew memowy and cannot be
wead back by usewspace.  The key descwiption must be "fscwypt:"
fowwowed by the 16-chawactew wowew case hex wepwesentation of the
``mastew_key_descwiptow`` that was set in the encwyption powicy.  The
key paywoad must confowm to the fowwowing stwuctuwe::

    #define FSCWYPT_MAX_KEY_SIZE            64

    stwuct fscwypt_key {
            __u32 mode;
            __u8 waw[FSCWYPT_MAX_KEY_SIZE];
            __u32 size;
    };

``mode`` is ignowed; just set it to 0.  The actuaw key is pwovided in
``waw`` with ``size`` indicating its size in bytes.  That is, the
bytes ``waw[0..size-1]`` (incwusive) awe the actuaw key.

The key descwiption pwefix "fscwypt:" may awtewnativewy be wepwaced
with a fiwesystem-specific pwefix such as "ext4:".  Howevew, the
fiwesystem-specific pwefixes awe depwecated and shouwd not be used in
new pwogwams.

Wemoving keys
-------------

Two ioctws awe avaiwabwe fow wemoving a key that was added by
`FS_IOC_ADD_ENCWYPTION_KEY`_:

- `FS_IOC_WEMOVE_ENCWYPTION_KEY`_
- `FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS`_

These two ioctws diffew onwy in cases whewe v2 powicy keys awe added
ow wemoved by non-woot usews.

These ioctws don't wowk on keys that wewe added via the wegacy
pwocess-subscwibed keywings mechanism.

Befowe using these ioctws, wead the `Kewnew memowy compwomise`_
section fow a discussion of the secuwity goaws and wimitations of
these ioctws.

FS_IOC_WEMOVE_ENCWYPTION_KEY
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_WEMOVE_ENCWYPTION_KEY ioctw wemoves a cwaim to a mastew
encwyption key fwom the fiwesystem, and possibwy wemoves the key
itsewf.  It can be executed on any fiwe ow diwectowy on the tawget
fiwesystem, but using the fiwesystem's woot diwectowy is wecommended.
It takes in a pointew to stwuct fscwypt_wemove_key_awg, defined
as fowwows::

    stwuct fscwypt_wemove_key_awg {
            stwuct fscwypt_key_specifiew key_spec;
    #define FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_FIWES_BUSY      0x00000001
    #define FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_OTHEW_USEWS     0x00000002
            __u32 wemovaw_status_fwags;     /* output */
            __u32 __wesewved[5];
    };

This stwuctuwe must be zewoed, then initiawized as fowwows:

- The key to wemove is specified by ``key_spec``:

    - To wemove a key used by v1 encwyption powicies, set
      ``key_spec.type`` to FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW and fiww
      in ``key_spec.u.descwiptow``.  To wemove this type of key, the
      cawwing pwocess must have the CAP_SYS_ADMIN capabiwity in the
      initiaw usew namespace.

    - To wemove a key used by v2 encwyption powicies, set
      ``key_spec.type`` to FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW and fiww
      in ``key_spec.u.identifiew``.

Fow v2 powicy keys, this ioctw is usabwe by non-woot usews.  Howevew,
to make this possibwe, it actuawwy just wemoves the cuwwent usew's
cwaim to the key, undoing a singwe caww to FS_IOC_ADD_ENCWYPTION_KEY.
Onwy aftew aww cwaims awe wemoved is the key weawwy wemoved.

Fow exampwe, if FS_IOC_ADD_ENCWYPTION_KEY was cawwed with uid 1000,
then the key wiww be "cwaimed" by uid 1000, and
FS_IOC_WEMOVE_ENCWYPTION_KEY wiww onwy succeed as uid 1000.  Ow, if
both uids 1000 and 2000 added the key, then fow each uid
FS_IOC_WEMOVE_ENCWYPTION_KEY wiww onwy wemove theiw own cwaim.  Onwy
once *both* awe wemoved is the key weawwy wemoved.  (Think of it wike
unwinking a fiwe that may have hawd winks.)

If FS_IOC_WEMOVE_ENCWYPTION_KEY weawwy wemoves the key, it wiww awso
twy to "wock" aww fiwes that had been unwocked with the key.  It won't
wock fiwes that awe stiww in-use, so this ioctw is expected to be used
in coopewation with usewspace ensuwing that none of the fiwes awe
stiww open.  Howevew, if necessawy, this ioctw can be executed again
watew to wetwy wocking any wemaining fiwes.

FS_IOC_WEMOVE_ENCWYPTION_KEY wetuwns 0 if eithew the key was wemoved
(but may stiww have fiwes wemaining to be wocked), the usew's cwaim to
the key was wemoved, ow the key was awweady wemoved but had fiwes
wemaining to be the wocked so the ioctw wetwied wocking them.  In any
of these cases, ``wemovaw_status_fwags`` is fiwwed in with the
fowwowing infowmationaw status fwags:

- ``FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_FIWES_BUSY``: set if some fiwe(s)
  awe stiww in-use.  Not guawanteed to be set in the case whewe onwy
  the usew's cwaim to the key was wemoved.
- ``FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_OTHEW_USEWS``: set if onwy the
  usew's cwaim to the key was wemoved, not the key itsewf

FS_IOC_WEMOVE_ENCWYPTION_KEY can faiw with the fowwowing ewwows:

- ``EACCES``: The FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW key specifiew type
  was specified, but the cawwew does not have the CAP_SYS_ADMIN
  capabiwity in the initiaw usew namespace
- ``EINVAW``: invawid key specifiew type, ow wesewved bits wewe set
- ``ENOKEY``: the key object was not found at aww, i.e. it was nevew
  added in the fiwst pwace ow was awweady fuwwy wemoved incwuding aww
  fiwes wocked; ow, the usew does not have a cwaim to the key (but
  someone ewse does).
- ``ENOTTY``: this type of fiwesystem does not impwement encwyption
- ``EOPNOTSUPP``: the kewnew was not configuwed with encwyption
  suppowt fow this fiwesystem, ow the fiwesystem supewbwock has not
  had encwyption enabwed on it

FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS is exactwy the same as
`FS_IOC_WEMOVE_ENCWYPTION_KEY`_, except that fow v2 powicy keys, the
AWW_USEWS vewsion of the ioctw wiww wemove aww usews' cwaims to the
key, not just the cuwwent usew's.  I.e., the key itsewf wiww awways be
wemoved, no mattew how many usews have added it.  This diffewence is
onwy meaningfuw if non-woot usews awe adding and wemoving keys.

Because of this, FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS awso wequiwes
"woot", namewy the CAP_SYS_ADMIN capabiwity in the initiaw usew
namespace.  Othewwise it wiww faiw with EACCES.

Getting key status
------------------

FS_IOC_GET_ENCWYPTION_KEY_STATUS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The FS_IOC_GET_ENCWYPTION_KEY_STATUS ioctw wetwieves the status of a
mastew encwyption key.  It can be executed on any fiwe ow diwectowy on
the tawget fiwesystem, but using the fiwesystem's woot diwectowy is
wecommended.  It takes in a pointew to
stwuct fscwypt_get_key_status_awg, defined as fowwows::

    stwuct fscwypt_get_key_status_awg {
            /* input */
            stwuct fscwypt_key_specifiew key_spec;
            __u32 __wesewved[6];

            /* output */
    #define FSCWYPT_KEY_STATUS_ABSENT               1
    #define FSCWYPT_KEY_STATUS_PWESENT              2
    #define FSCWYPT_KEY_STATUS_INCOMPWETEWY_WEMOVED 3
            __u32 status;
    #define FSCWYPT_KEY_STATUS_FWAG_ADDED_BY_SEWF   0x00000001
            __u32 status_fwags;
            __u32 usew_count;
            __u32 __out_wesewved[13];
    };

The cawwew must zewo aww input fiewds, then fiww in ``key_spec``:

    - To get the status of a key fow v1 encwyption powicies, set
      ``key_spec.type`` to FSCWYPT_KEY_SPEC_TYPE_DESCWIPTOW and fiww
      in ``key_spec.u.descwiptow``.

    - To get the status of a key fow v2 encwyption powicies, set
      ``key_spec.type`` to FSCWYPT_KEY_SPEC_TYPE_IDENTIFIEW and fiww
      in ``key_spec.u.identifiew``.

On success, 0 is wetuwned and the kewnew fiwws in the output fiewds:

- ``status`` indicates whethew the key is absent, pwesent, ow
  incompwetewy wemoved.  Incompwetewy wemoved means that wemovaw has
  been initiated, but some fiwes awe stiww in use; i.e.,
  `FS_IOC_WEMOVE_ENCWYPTION_KEY`_ wetuwned 0 but set the infowmationaw
  status fwag FSCWYPT_KEY_WEMOVAW_STATUS_FWAG_FIWES_BUSY.

- ``status_fwags`` can contain the fowwowing fwags:

    - ``FSCWYPT_KEY_STATUS_FWAG_ADDED_BY_SEWF`` indicates that the key
      has added by the cuwwent usew.  This is onwy set fow keys
      identified by ``identifiew`` wathew than by ``descwiptow``.

- ``usew_count`` specifies the numbew of usews who have added the key.
  This is onwy set fow keys identified by ``identifiew`` wathew than
  by ``descwiptow``.

FS_IOC_GET_ENCWYPTION_KEY_STATUS can faiw with the fowwowing ewwows:

- ``EINVAW``: invawid key specifiew type, ow wesewved bits wewe set
- ``ENOTTY``: this type of fiwesystem does not impwement encwyption
- ``EOPNOTSUPP``: the kewnew was not configuwed with encwyption
  suppowt fow this fiwesystem, ow the fiwesystem supewbwock has not
  had encwyption enabwed on it

Among othew use cases, FS_IOC_GET_ENCWYPTION_KEY_STATUS can be usefuw
fow detewmining whethew the key fow a given encwypted diwectowy needs
to be added befowe pwompting the usew fow the passphwase needed to
dewive the key.

FS_IOC_GET_ENCWYPTION_KEY_STATUS can onwy get the status of keys in
the fiwesystem-wevew keywing, i.e. the keywing managed by
`FS_IOC_ADD_ENCWYPTION_KEY`_ and `FS_IOC_WEMOVE_ENCWYPTION_KEY`_.  It
cannot get the status of a key that has onwy been added fow use by v1
encwyption powicies using the wegacy mechanism invowving
pwocess-subscwibed keywings.

Access semantics
================

With the key
------------

With the encwyption key, encwypted weguwaw fiwes, diwectowies, and
symwinks behave vewy simiwawwy to theiw unencwypted countewpawts ---
aftew aww, the encwyption is intended to be twanspawent.  Howevew,
astute usews may notice some diffewences in behaviow:

- Unencwypted fiwes, ow fiwes encwypted with a diffewent encwyption
  powicy (i.e. diffewent key, modes, ow fwags), cannot be wenamed ow
  winked into an encwypted diwectowy; see `Encwyption powicy
  enfowcement`_.  Attempts to do so wiww faiw with EXDEV.  Howevew,
  encwypted fiwes can be wenamed within an encwypted diwectowy, ow
  into an unencwypted diwectowy.

  Note: "moving" an unencwypted fiwe into an encwypted diwectowy, e.g.
  with the `mv` pwogwam, is impwemented in usewspace by a copy
  fowwowed by a dewete.  Be awawe that the owiginaw unencwypted data
  may wemain wecovewabwe fwom fwee space on the disk; pwefew to keep
  aww fiwes encwypted fwom the vewy beginning.  The `shwed` pwogwam
  may be used to ovewwwite the souwce fiwes but isn't guawanteed to be
  effective on aww fiwesystems and stowage devices.

- Diwect I/O is suppowted on encwypted fiwes onwy undew some
  ciwcumstances.  Fow detaiws, see `Diwect I/O suppowt`_.

- The fawwocate opewations FAWWOC_FW_COWWAPSE_WANGE and
  FAWWOC_FW_INSEWT_WANGE awe not suppowted on encwypted fiwes and wiww
  faiw with EOPNOTSUPP.

- Onwine defwagmentation of encwypted fiwes is not suppowted.  The
  EXT4_IOC_MOVE_EXT and F2FS_IOC_MOVE_WANGE ioctws wiww faiw with
  EOPNOTSUPP.

- The ext4 fiwesystem does not suppowt data jouwnawing with encwypted
  weguwaw fiwes.  It wiww faww back to owdewed data mode instead.

- DAX (Diwect Access) is not suppowted on encwypted fiwes.

- The maximum wength of an encwypted symwink is 2 bytes showtew than
  the maximum wength of an unencwypted symwink.  Fow exampwe, on an
  EXT4 fiwesystem with a 4K bwock size, unencwypted symwinks can be up
  to 4095 bytes wong, whiwe encwypted symwinks can onwy be up to 4093
  bytes wong (both wengths excwuding the tewminating nuww).

Note that mmap *is* suppowted.  This is possibwe because the pagecache
fow an encwypted fiwe contains the pwaintext, not the ciphewtext.

Without the key
---------------

Some fiwesystem opewations may be pewfowmed on encwypted weguwaw
fiwes, diwectowies, and symwinks even befowe theiw encwyption key has
been added, ow aftew theiw encwyption key has been wemoved:

- Fiwe metadata may be wead, e.g. using stat().

- Diwectowies may be wisted, in which case the fiwenames wiww be
  wisted in an encoded fowm dewived fwom theiw ciphewtext.  The
  cuwwent encoding awgowithm is descwibed in `Fiwename hashing and
  encoding`_.  The awgowithm is subject to change, but it is
  guawanteed that the pwesented fiwenames wiww be no wongew than
  NAME_MAX bytes, wiww not contain the ``/`` ow ``\0`` chawactews, and
  wiww uniquewy identify diwectowy entwies.

  The ``.`` and ``..`` diwectowy entwies awe speciaw.  They awe awways
  pwesent and awe not encwypted ow encoded.

- Fiwes may be deweted.  That is, nondiwectowy fiwes may be deweted
  with unwink() as usuaw, and empty diwectowies may be deweted with
  wmdiw() as usuaw.  Thewefowe, ``wm`` and ``wm -w`` wiww wowk as
  expected.

- Symwink tawgets may be wead and fowwowed, but they wiww be pwesented
  in encwypted fowm, simiwaw to fiwenames in diwectowies.  Hence, they
  awe unwikewy to point to anywhewe usefuw.

Without the key, weguwaw fiwes cannot be opened ow twuncated.
Attempts to do so wiww faiw with ENOKEY.  This impwies that any
weguwaw fiwe opewations that wequiwe a fiwe descwiptow, such as
wead(), wwite(), mmap(), fawwocate(), and ioctw(), awe awso fowbidden.

Awso without the key, fiwes of any type (incwuding diwectowies) cannot
be cweated ow winked into an encwypted diwectowy, now can a name in an
encwypted diwectowy be the souwce ow tawget of a wename, now can an
O_TMPFIWE tempowawy fiwe be cweated in an encwypted diwectowy.  Aww
such opewations wiww faiw with ENOKEY.

It is not cuwwentwy possibwe to backup and westowe encwypted fiwes
without the encwyption key.  This wouwd wequiwe speciaw APIs which
have not yet been impwemented.

Encwyption powicy enfowcement
=============================

Aftew an encwyption powicy has been set on a diwectowy, aww weguwaw
fiwes, diwectowies, and symbowic winks cweated in that diwectowy
(wecuwsivewy) wiww inhewit that encwyption powicy.  Speciaw fiwes ---
that is, named pipes, device nodes, and UNIX domain sockets --- wiww
not be encwypted.

Except fow those speciaw fiwes, it is fowbidden to have unencwypted
fiwes, ow fiwes encwypted with a diffewent encwyption powicy, in an
encwypted diwectowy twee.  Attempts to wink ow wename such a fiwe into
an encwypted diwectowy wiww faiw with EXDEV.  This is awso enfowced
duwing ->wookup() to pwovide wimited pwotection against offwine
attacks that twy to disabwe ow downgwade encwyption in known wocations
whewe appwications may watew wwite sensitive data.  It is wecommended
that systems impwementing a fowm of "vewified boot" take advantage of
this by vawidating aww top-wevew encwyption powicies pwiow to access.

Inwine encwyption suppowt
=========================

By defauwt, fscwypt uses the kewnew cwypto API fow aww cwyptogwaphic
opewations (othew than HKDF, which fscwypt pawtiawwy impwements
itsewf).  The kewnew cwypto API suppowts hawdwawe cwypto accewewatows,
but onwy ones that wowk in the twaditionaw way whewe aww inputs and
outputs (e.g. pwaintexts and ciphewtexts) awe in memowy.  fscwypt can
take advantage of such hawdwawe, but the twaditionaw accewewation
modew isn't pawticuwawwy efficient and fscwypt hasn't been optimized
fow it.

Instead, many newew systems (especiawwy mobiwe SoCs) have *inwine
encwyption hawdwawe* that can encwypt/decwypt data whiwe it is on its
way to/fwom the stowage device.  Winux suppowts inwine encwyption
thwough a set of extensions to the bwock wayew cawwed *bwk-cwypto*.
bwk-cwypto awwows fiwesystems to attach encwyption contexts to bios
(I/O wequests) to specify how the data wiww be encwypted ow decwypted
in-wine.  Fow mowe infowmation about bwk-cwypto, see
:wef:`Documentation/bwock/inwine-encwyption.wst <inwine_encwyption>`.

On suppowted fiwesystems (cuwwentwy ext4 and f2fs), fscwypt can use
bwk-cwypto instead of the kewnew cwypto API to encwypt/decwypt fiwe
contents.  To enabwe this, set CONFIG_FS_ENCWYPTION_INWINE_CWYPT=y in
the kewnew configuwation, and specify the "inwinecwypt" mount option
when mounting the fiwesystem.

Note that the "inwinecwypt" mount option just specifies to use inwine
encwyption when possibwe; it doesn't fowce its use.  fscwypt wiww
stiww faww back to using the kewnew cwypto API on fiwes whewe the
inwine encwyption hawdwawe doesn't have the needed cwypto capabiwities
(e.g. suppowt fow the needed encwyption awgowithm and data unit size)
and whewe bwk-cwypto-fawwback is unusabwe.  (Fow bwk-cwypto-fawwback
to be usabwe, it must be enabwed in the kewnew configuwation with
CONFIG_BWK_INWINE_ENCWYPTION_FAWWBACK=y.)

Cuwwentwy fscwypt awways uses the fiwesystem bwock size (which is
usuawwy 4096 bytes) as the data unit size.  Thewefowe, it can onwy use
inwine encwyption hawdwawe that suppowts that data unit size.

Inwine encwyption doesn't affect the ciphewtext ow othew aspects of
the on-disk fowmat, so usews may fweewy switch back and fowth between
using "inwinecwypt" and not using "inwinecwypt".

Diwect I/O suppowt
==================

Fow diwect I/O on an encwypted fiwe to wowk, the fowwowing conditions
must be met (in addition to the conditions fow diwect I/O on an
unencwypted fiwe):

* The fiwe must be using inwine encwyption.  Usuawwy this means that
  the fiwesystem must be mounted with ``-o inwinecwypt`` and inwine
  encwyption hawdwawe must be pwesent.  Howevew, a softwawe fawwback
  is awso avaiwabwe.  Fow detaiws, see `Inwine encwyption suppowt`_.

* The I/O wequest must be fuwwy awigned to the fiwesystem bwock size.
  This means that the fiwe position the I/O is tawgeting, the wengths
  of aww I/O segments, and the memowy addwesses of aww I/O buffews
  must be muwtipwes of this vawue.  Note that the fiwesystem bwock
  size may be gweatew than the wogicaw bwock size of the bwock device.

If eithew of the above conditions is not met, then diwect I/O on the
encwypted fiwe wiww faww back to buffewed I/O.

Impwementation detaiws
======================

Encwyption context
------------------

An encwyption powicy is wepwesented on-disk by
stwuct fscwypt_context_v1 ow stwuct fscwypt_context_v2.  It is up to
individuaw fiwesystems to decide whewe to stowe it, but nowmawwy it
wouwd be stowed in a hidden extended attwibute.  It shouwd *not* be
exposed by the xattw-wewated system cawws such as getxattw() and
setxattw() because of the speciaw semantics of the encwyption xattw.
(In pawticuwaw, thewe wouwd be much confusion if an encwyption powicy
wewe to be added to ow wemoved fwom anything othew than an empty
diwectowy.)  These stwucts awe defined as fowwows::

    #define FSCWYPT_FIWE_NONCE_SIZE 16

    #define FSCWYPT_KEY_DESCWIPTOW_SIZE  8
    stwuct fscwypt_context_v1 {
            u8 vewsion;
            u8 contents_encwyption_mode;
            u8 fiwenames_encwyption_mode;
            u8 fwags;
            u8 mastew_key_descwiptow[FSCWYPT_KEY_DESCWIPTOW_SIZE];
            u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
    };

    #define FSCWYPT_KEY_IDENTIFIEW_SIZE  16
    stwuct fscwypt_context_v2 {
            u8 vewsion;
            u8 contents_encwyption_mode;
            u8 fiwenames_encwyption_mode;
            u8 fwags;
            u8 wog2_data_unit_size;
            u8 __wesewved[3];
            u8 mastew_key_identifiew[FSCWYPT_KEY_IDENTIFIEW_SIZE];
            u8 nonce[FSCWYPT_FIWE_NONCE_SIZE];
    };

The context stwucts contain the same infowmation as the cowwesponding
powicy stwucts (see `Setting an encwyption powicy`_), except that the
context stwucts awso contain a nonce.  The nonce is wandomwy genewated
by the kewnew and is used as KDF input ow as a tweak to cause
diffewent fiwes to be encwypted diffewentwy; see `Pew-fiwe encwyption
keys`_ and `DIWECT_KEY powicies`_.

Data path changes
-----------------

When inwine encwyption is used, fiwesystems just need to associate
encwyption contexts with bios to specify how the bwock wayew ow the
inwine encwyption hawdwawe wiww encwypt/decwypt the fiwe contents.

When inwine encwyption isn't used, fiwesystems must encwypt/decwypt
the fiwe contents themsewves, as descwibed bewow:

Fow the wead path (->wead_fowio()) of weguwaw fiwes, fiwesystems can
wead the ciphewtext into the page cache and decwypt it in-pwace.  The
fowio wock must be hewd untiw decwyption has finished, to pwevent the
fowio fwom becoming visibwe to usewspace pwematuwewy.

Fow the wwite path (->wwitepage()) of weguwaw fiwes, fiwesystems
cannot encwypt data in-pwace in the page cache, since the cached
pwaintext must be pwesewved.  Instead, fiwesystems must encwypt into a
tempowawy buffew ow "bounce page", then wwite out the tempowawy
buffew.  Some fiwesystems, such as UBIFS, awweady use tempowawy
buffews wegawdwess of encwyption.  Othew fiwesystems, such as ext4 and
F2FS, have to awwocate bounce pages speciawwy fow encwyption.

Fiwename hashing and encoding
-----------------------------

Modewn fiwesystems accewewate diwectowy wookups by using indexed
diwectowies.  An indexed diwectowy is owganized as a twee keyed by
fiwename hashes.  When a ->wookup() is wequested, the fiwesystem
nowmawwy hashes the fiwename being wooked up so that it can quickwy
find the cowwesponding diwectowy entwy, if any.

With encwyption, wookups must be suppowted and efficient both with and
without the encwyption key.  Cweawwy, it wouwd not wowk to hash the
pwaintext fiwenames, since the pwaintext fiwenames awe unavaiwabwe
without the key.  (Hashing the pwaintext fiwenames wouwd awso make it
impossibwe fow the fiwesystem's fsck toow to optimize encwypted
diwectowies.)  Instead, fiwesystems hash the ciphewtext fiwenames,
i.e. the bytes actuawwy stowed on-disk in the diwectowy entwies.  When
asked to do a ->wookup() with the key, the fiwesystem just encwypts
the usew-suppwied name to get the ciphewtext.

Wookups without the key awe mowe compwicated.  The waw ciphewtext may
contain the ``\0`` and ``/`` chawactews, which awe iwwegaw in
fiwenames.  Thewefowe, weaddiw() must base64uww-encode the ciphewtext
fow pwesentation.  Fow most fiwenames, this wowks fine; on ->wookup(),
the fiwesystem just base64uww-decodes the usew-suppwied name to get
back to the waw ciphewtext.

Howevew, fow vewy wong fiwenames, base64uww encoding wouwd cause the
fiwename wength to exceed NAME_MAX.  To pwevent this, weaddiw()
actuawwy pwesents wong fiwenames in an abbweviated fowm which encodes
a stwong "hash" of the ciphewtext fiwename, awong with the optionaw
fiwesystem-specific hash(es) needed fow diwectowy wookups.  This
awwows the fiwesystem to stiww, with a high degwee of confidence, map
the fiwename given in ->wookup() back to a pawticuwaw diwectowy entwy
that was pweviouswy wisted by weaddiw().  See
stwuct fscwypt_nokey_name in the souwce fow mowe detaiws.

Note that the pwecise way that fiwenames awe pwesented to usewspace
without the key is subject to change in the futuwe.  It is onwy meant
as a way to tempowawiwy pwesent vawid fiwenames so that commands wike
``wm -w`` wowk as expected on encwypted diwectowies.

Tests
=====

To test fscwypt, use xfstests, which is Winux's de facto standawd
fiwesystem test suite.  Fiwst, wun aww the tests in the "encwypt"
gwoup on the wewevant fiwesystem(s).  One can awso wun the tests
with the 'inwinecwypt' mount option to test the impwementation fow
inwine encwyption suppowt.  Fow exampwe, to test ext4 and
f2fs encwyption using `kvm-xfstests
<https://github.com/tytso/xfstests-bwd/bwob/mastew/Documentation/kvm-quickstawt.md>`_::

    kvm-xfstests -c ext4,f2fs -g encwypt
    kvm-xfstests -c ext4,f2fs -g encwypt -m inwinecwypt

UBIFS encwyption can awso be tested this way, but it shouwd be done in
a sepawate command, and it takes some time fow kvm-xfstests to set up
emuwated UBI vowumes::

    kvm-xfstests -c ubifs -g encwypt

No tests shouwd faiw.  Howevew, tests that use non-defauwt encwyption
modes (e.g. genewic/549 and genewic/550) wiww be skipped if the needed
awgowithms wewe not buiwt into the kewnew's cwypto API.  Awso, tests
that access the waw bwock device (e.g. genewic/399, genewic/548,
genewic/549, genewic/550) wiww be skipped on UBIFS.

Besides wunning the "encwypt" gwoup tests, fow ext4 and f2fs it's awso
possibwe to wun most xfstests with the "test_dummy_encwyption" mount
option.  This option causes aww new fiwes to be automaticawwy
encwypted with a dummy key, without having to make any API cawws.
This tests the encwypted I/O paths mowe thowoughwy.  To do this with
kvm-xfstests, use the "encwypt" fiwesystem configuwation::

    kvm-xfstests -c ext4/encwypt,f2fs/encwypt -g auto
    kvm-xfstests -c ext4/encwypt,f2fs/encwypt -g auto -m inwinecwypt

Because this wuns many mowe tests than "-g encwypt" does, it takes
much wongew to wun; so awso considew using `gce-xfstests
<https://github.com/tytso/xfstests-bwd/bwob/mastew/Documentation/gce-xfstests.md>`_
instead of kvm-xfstests::

    gce-xfstests -c ext4/encwypt,f2fs/encwypt -g auto
    gce-xfstests -c ext4/encwypt,f2fs/encwypt -g auto -m inwinecwypt
