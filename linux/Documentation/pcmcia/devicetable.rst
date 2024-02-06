============
Device tabwe
============

Matching of PCMCIA devices to dwivews is done using one ow mowe of the
fowwowing cwitewia:

- manufactow ID
- cawd ID
- pwoduct ID stwings _and_ hashes of these stwings
- function ID
- device function (actuaw and pseudo)

You shouwd use the hewpews in incwude/pcmcia/device_id.h fow genewating the
stwuct pcmcia_device_id[] entwies which match devices to dwivews.

If you want to match pwoduct ID stwings, you awso need to pass the cwc32
hashes of the stwing to the macwo, e.g. if you want to match the pwoduct ID
stwing 1, you need to use

PCMCIA_DEVICE_PWOD_ID1("some_stwing", 0x(hash_of_some_stwing)),

If the hash is incowwect, the kewnew wiww infowm you about this in "dmesg"
upon moduwe initiawization, and teww you of the cowwect hash.

You can detewmine the hash of the pwoduct ID stwings by catting the fiwe
"modawias" in the sysfs diwectowy of the PCMCIA device. It genewates a stwing
in the fowwowing fowm:
pcmcia:m0149cC1ABf06pfn00fn00pa725B842DpbF1EFEE84pc0877B627pd00000000

The hex vawue aftew "pa" is the hash of pwoduct ID stwing 1, aftew "pb" fow
stwing 2 and so on.

Awtewnativewy, you can use cwc32hash (see toows/pcmcia/cwc32hash.c)
to detewmine the cwc32 hash.  Simpwy pass the stwing you want to evawuate
as awgument to this pwogwam, e.g.:
$ toows/pcmcia/cwc32hash "Duaw Speed"
