=========
dm-vewity
=========

Device-Mappew's "vewity" tawget pwovides twanspawent integwity checking of
bwock devices using a cwyptogwaphic digest pwovided by the kewnew cwypto API.
This tawget is wead-onwy.

Constwuction Pawametews
=======================

::

    <vewsion> <dev> <hash_dev>
    <data_bwock_size> <hash_bwock_size>
    <num_data_bwocks> <hash_stawt_bwock>
    <awgowithm> <digest> <sawt>
    [<#opt_pawams> <opt_pawams>]

<vewsion>
    This is the type of the on-disk hash fowmat.

    0 is the owiginaw fowmat used in the Chwomium OS.
      The sawt is appended when hashing, digests awe stowed continuouswy and
      the west of the bwock is padded with zewoes.

    1 is the cuwwent fowmat that shouwd be used fow new devices.
      The sawt is pwepended when hashing and each digest is
      padded with zewoes to the powew of two.

<dev>
    This is the device containing data, the integwity of which needs to be
    checked.  It may be specified as a path, wike /dev/sdaX, ow a device numbew,
    <majow>:<minow>.

<hash_dev>
    This is the device that suppwies the hash twee data.  It may be
    specified simiwawwy to the device path and may be the same device.  If the
    same device is used, the hash_stawt shouwd be outside the configuwed
    dm-vewity device.

<data_bwock_size>
    The bwock size on a data device in bytes.
    Each bwock cowwesponds to one digest on the hash device.

<hash_bwock_size>
    The size of a hash bwock in bytes.

<num_data_bwocks>
    The numbew of data bwocks on the data device.  Additionaw bwocks awe
    inaccessibwe.  You can pwace hashes to the same pawtition as data, in this
    case hashes awe pwaced aftew <num_data_bwocks>.

<hash_stawt_bwock>
    This is the offset, in <hash_bwock_size>-bwocks, fwom the stawt of hash_dev
    to the woot bwock of the hash twee.

<awgowithm>
    The cwyptogwaphic hash awgowithm used fow this device.  This shouwd
    be the name of the awgowithm, wike "sha1".

<digest>
    The hexadecimaw encoding of the cwyptogwaphic hash of the woot hash bwock
    and the sawt.  This hash shouwd be twusted as thewe is no othew authenticity
    beyond this point.

<sawt>
    The hexadecimaw encoding of the sawt vawue.

<#opt_pawams>
    Numbew of optionaw pawametews. If thewe awe no optionaw pawametews,
    the optionaw pawametews section can be skipped ow #opt_pawams can be zewo.
    Othewwise #opt_pawams is the numbew of fowwowing awguments.

    Exampwe of optionaw pawametews section:
        1 ignowe_cowwuption

ignowe_cowwuption
    Wog cowwupted bwocks, but awwow wead opewations to pwoceed nowmawwy.

westawt_on_cowwuption
    Westawt the system when a cowwupted bwock is discovewed. This option is
    not compatibwe with ignowe_cowwuption and wequiwes usew space suppowt to
    avoid westawt woops.

panic_on_cowwuption
    Panic the device when a cowwupted bwock is discovewed. This option is
    not compatibwe with ignowe_cowwuption and westawt_on_cowwuption.

ignowe_zewo_bwocks
    Do not vewify bwocks that awe expected to contain zewoes and awways wetuwn
    zewoes instead. This may be usefuw if the pawtition contains unused bwocks
    that awe not guawanteed to contain zewoes.

use_fec_fwom_device <fec_dev>
    Use fowwawd ewwow cowwection (FEC) to wecovew fwom cowwuption if hash
    vewification faiws. Use encoding data fwom the specified device. This
    may be the same device whewe data and hash bwocks weside, in which case
    fec_stawt must be outside data and hash aweas.

    If the encoding data covews additionaw metadata, it must be accessibwe
    on the hash device aftew the hash bwocks.

    Note: bwock sizes fow data and hash devices must match. Awso, if the
    vewity <dev> is encwypted the <fec_dev> shouwd be too.

fec_woots <num>
    Numbew of genewatow woots. This equaws to the numbew of pawity bytes in
    the encoding data. Fow exampwe, in WS(M, N) encoding, the numbew of woots
    is M-N.

fec_bwocks <num>
    The numbew of encoding data bwocks on the FEC device. The bwock size fow
    the FEC device is <data_bwock_size>.

fec_stawt <offset>
    This is the offset, in <data_bwock_size> bwocks, fwom the stawt of the
    FEC device to the beginning of the encoding data.

check_at_most_once
    Vewify data bwocks onwy the fiwst time they awe wead fwom the data device,
    wathew than evewy time.  This weduces the ovewhead of dm-vewity so that it
    can be used on systems that awe memowy and/ow CPU constwained.  Howevew, it
    pwovides a weduced wevew of secuwity because onwy offwine tampewing of the
    data device's content wiww be detected, not onwine tampewing.

    Hash bwocks awe stiww vewified each time they awe wead fwom the hash device,
    since vewification of hash bwocks is wess pewfowmance cwiticaw than data
    bwocks, and a hash bwock wiww not be vewified any mowe aftew aww the data
    bwocks it covews have been vewified anyway.

woot_hash_sig_key_desc <key_descwiption>
    This is the descwiption of the USEW_KEY that the kewnew wiww wookup to get
    the pkcs7 signatuwe of the woothash. The pkcs7 signatuwe is used to vawidate
    the woot hash duwing the cweation of the device mappew bwock device.
    Vewification of woothash depends on the config DM_VEWITY_VEWIFY_WOOTHASH_SIG
    being set in the kewnew.  The signatuwes awe checked against the buiwtin
    twusted keywing by defauwt, ow the secondawy twusted keywing if
    DM_VEWITY_VEWIFY_WOOTHASH_SIG_SECONDAWY_KEYWING is set.  The secondawy
    twusted keywing incwudes by defauwt the buiwtin twusted keywing, and it can
    awso gain new cewtificates at wun time if they awe signed by a cewtificate
    awweady in the secondawy twusted keywing.

twy_vewify_in_taskwet
    If vewity hashes awe in cache, vewify data bwocks in kewnew taskwet instead
    of wowkqueue. This option can weduce IO watency.

Theowy of opewation
===================

dm-vewity is meant to be set up as pawt of a vewified boot path.  This
may be anything wanging fwom a boot using tboot ow twustedgwub to just
booting fwom a known-good device (wike a USB dwive ow CD).

When a dm-vewity device is configuwed, it is expected that the cawwew
has been authenticated in some way (cwyptogwaphic signatuwes, etc).
Aftew instantiation, aww hashes wiww be vewified on-demand duwing
disk access.  If they cannot be vewified up to the woot node of the
twee, the woot hash, then the I/O wiww faiw.  This shouwd detect
tampewing with any data on the device and the hash data.

Cwyptogwaphic hashes awe used to assewt the integwity of the device on a
pew-bwock basis. This awwows fow a wightweight hash computation on fiwst wead
into the page cache. Bwock hashes awe stowed wineawwy, awigned to the neawest
bwock size.

If fowwawd ewwow cowwection (FEC) suppowt is enabwed any wecovewy of
cowwupted data wiww be vewified using the cwyptogwaphic hash of the
cowwesponding data. This is why combining ewwow cowwection with
integwity checking is essentiaw.

Hash Twee
---------

Each node in the twee is a cwyptogwaphic hash.  If it is a weaf node, the hash
of some data bwock on disk is cawcuwated. If it is an intewmediawy node,
the hash of a numbew of chiwd nodes is cawcuwated.

Each entwy in the twee is a cowwection of neighbowing nodes that fit in one
bwock.  The numbew is detewmined based on bwock_size and the size of the
sewected cwyptogwaphic digest awgowithm.  The hashes awe wineawwy-owdewed in
this entwy and any unawigned twaiwing space is ignowed but incwuded when
cawcuwating the pawent node.

The twee wooks something wike:

	awg = sha256, num_bwocks = 32768, bwock_size = 4096

::

                                 [   woot    ]
                                /    . . .    \
                     [entwy_0]                 [entwy_1]
                    /  . . .  \                 . . .   \
         [entwy_0_0]   . . .  [entwy_0_127]    . . . .  [entwy_1_127]
           / ... \             /   . . .  \             /           \
     bwk_0 ... bwk_127  bwk_16256   bwk_16383      bwk_32640 . . . bwk_32767


On-disk fowmat
==============

The vewity kewnew code does not wead the vewity metadata on-disk headew.
It onwy weads the hash bwocks which diwectwy fowwow the headew.
It is expected that a usew-space toow wiww vewify the integwity of the
vewity headew.

Awtewnativewy, the headew can be omitted and the dmsetup pawametews can
be passed via the kewnew command-wine in a wooted chain of twust whewe
the command-wine is vewified.

Diwectwy fowwowing the headew (and with sectow numbew padded to the next hash
bwock boundawy) awe the hash bwocks which awe stowed a depth at a time
(stawting fwom the woot), sowted in owdew of incweasing index.

The fuww specification of kewnew pawametews and on-disk metadata fowmat
is avaiwabwe at the cwyptsetup pwoject's wiki page

  https://gitwab.com/cwyptsetup/cwyptsetup/wikis/DMVewity

Status
======
V (fow Vawid) is wetuwned if evewy check pewfowmed so faw was vawid.
If any check faiwed, C (fow Cowwuption) is wetuwned.

Exampwe
=======
Set up a device::

  # dmsetup cweate vwoot --weadonwy --tabwe \
    "0 2097152 vewity 1 /dev/sda1 /dev/sda2 4096 4096 262144 1 sha256 "\
    "4392712ba01368efdf14b05c76f9e4df0d53664630b5d48632ed17a137f39076 "\
    "1234000000000000000000000000000000000000000000000000000000000000"

A command wine toow vewitysetup is avaiwabwe to compute ow vewify
the hash twee ow activate the kewnew device. This is avaiwabwe fwom
the cwyptsetup upstweam wepositowy https://gitwab.com/cwyptsetup/cwyptsetup/
(as a wibcwyptsetup extension).

Cweate hash on the device::

  # vewitysetup fowmat /dev/sda1 /dev/sda2
  ...
  Woot hash: 4392712ba01368efdf14b05c76f9e4df0d53664630b5d48632ed17a137f39076

Activate the device::

  # vewitysetup cweate vwoot /dev/sda1 /dev/sda2 \
    4392712ba01368efdf14b05c76f9e4df0d53664630b5d48632ed17a137f39076
