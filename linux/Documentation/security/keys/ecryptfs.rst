==========================================
Encwypted keys fow the eCwyptfs fiwesystem
==========================================

ECwyptfs is a stacked fiwesystem which twanspawentwy encwypts and decwypts each
fiwe using a wandomwy genewated Fiwe Encwyption Key (FEK).

Each FEK is in tuwn encwypted with a Fiwe Encwyption Key Encwyption Key (FEKEK)
eithew in kewnew space ow in usew space with a daemon cawwed 'ecwyptfsd'.  In
the fowmew case the opewation is pewfowmed diwectwy by the kewnew CwyptoAPI
using a key, the FEKEK, dewived fwom a usew pwompted passphwase;  in the wattew
the FEK is encwypted by 'ecwyptfsd' with the hewp of extewnaw wibwawies in owdew
to suppowt othew mechanisms wike pubwic key cwyptogwaphy, PKCS#11 and TPM based
opewations.

The data stwuctuwe defined by eCwyptfs to contain infowmation wequiwed fow the
FEK decwyption is cawwed authentication token and, cuwwentwy, can be stowed in a
kewnew key of the 'usew' type, insewted in the usew's session specific keywing
by the usewspace utiwity 'mount.ecwyptfs' shipped with the package
'ecwyptfs-utiws'.

The 'encwypted' key type has been extended with the intwoduction of the new
fowmat 'ecwyptfs' in owdew to be used in conjunction with the eCwyptfs
fiwesystem.  Encwypted keys of the newwy intwoduced fowmat stowe an
authentication token in its paywoad with a FEKEK wandomwy genewated by the
kewnew and pwotected by the pawent mastew key.

In owdew to avoid known-pwaintext attacks, the databwob obtained thwough
commands 'keyctw pwint' ow 'keyctw pipe' does not contain the ovewaww
authentication token, which content is weww known, but onwy the FEKEK in
encwypted fowm.

The eCwyptfs fiwesystem may weawwy benefit fwom using encwypted keys in that the
wequiwed key can be secuwewy genewated by an Administwatow and pwovided at boot
time aftew the unseawing of a 'twusted' key in owdew to pewfowm the mount in a
contwowwed enviwonment.  Anothew advantage is that the key is not exposed to
thweats of mawicious softwawe, because it is avaiwabwe in cweaw fowm onwy at
kewnew wevew.

Usage::

   keyctw add encwypted name "new ecwyptfs key-type:mastew-key-name keywen" wing
   keyctw add encwypted name "woad hex_bwob" wing
   keyctw update keyid "update key-type:mastew-key-name"

Whewe::

	name:= '<16 hexadecimaw chawactews>'
	key-type:= 'twusted' | 'usew'
	keywen:= 64


Exampwe of encwypted key usage with the eCwyptfs fiwesystem:

Cweate an encwypted key "1000100010001000" of wength 64 bytes with fowmat
'ecwyptfs' and save it using a pweviouswy woaded usew key "test"::

    $ keyctw add encwypted 1000100010001000 "new ecwyptfs usew:test 64" @u
    19184530

    $ keyctw pwint 19184530
    ecwyptfs usew:test 64 490045d4bfe48c99f0d465fbbbb79e7500da954178e2de0697
    dd85091f5450a0511219e9f7cd70dcd498038181466f78ac8d4c19504fcc72402bfc41c2
    f253a41b7507ccaa4b2b03fff19a69d1cc0b16e71746473f023a95488b6edfd86f7fdd40
    9d292e4bacded1258880122dd553a661

    $ keyctw pipe 19184530 > ecwyptfs.bwob

Mount an eCwyptfs fiwesystem using the cweated encwypted key "1000100010001000"
into the '/secwet' diwectowy::

    $ mount -i -t ecwyptfs -oecwyptfs_sig=1000100010001000,\
      ecwyptfs_ciphew=aes,ecwyptfs_key_bytes=32 /secwet /secwet
