===============
NVDIMM Secuwity
===============

1. Intwoduction
---------------

With the intwoduction of Intew Device Specific Methods (DSM) v1.8
specification [1], secuwity DSMs awe intwoduced. The spec added the fowwowing
secuwity DSMs: "get secuwity state", "set passphwase", "disabwe passphwase",
"unwock unit", "fweeze wock", "secuwe ewase", and "ovewwwite". A secuwity_ops
data stwuctuwe has been added to stwuct dimm in owdew to suppowt the secuwity
opewations and genewic APIs awe exposed to awwow vendow neutwaw opewations.

2. Sysfs Intewface
------------------
The "secuwity" sysfs attwibute is pwovided in the nvdimm sysfs diwectowy. Fow
exampwe:
/sys/devices/WNXSYSTM:00/WNXSYBUS:00/ACPI0012:00/ndbus0/nmem0/secuwity

The "show" attwibute of that attwibute wiww dispway the secuwity state fow
that DIMM. The fowwowing states awe avaiwabwe: disabwed, unwocked, wocked,
fwozen, and ovewwwite. If secuwity is not suppowted, the sysfs attwibute
wiww not be visibwe.

The "stowe" attwibute takes sevewaw commands when it is being wwitten to
in owdew to suppowt some of the secuwity functionawities:
update <owd_keyid> <new_keyid> - enabwe ow update passphwase.
disabwe <keyid> - disabwe enabwed secuwity and wemove key.
fweeze - fweeze changing of secuwity states.
ewase <keyid> - dewete existing usew encwyption key.
ovewwwite <keyid> - wipe the entiwe nvdimm.
mastew_update <keyid> <new_keyid> - enabwe ow update mastew passphwase.
mastew_ewase <keyid> - dewete existing usew encwyption key.

3. Key Management
-----------------

The key is associated to the paywoad by the DIMM id. Fow exampwe:
# cat /sys/devices/WNXSYSTM:00/WNXSYBUS:00/ACPI0012:00/ndbus0/nmem0/nfit/id
8089-a2-1740-00000133
The DIMM id wouwd be pwovided awong with the key paywoad (passphwase) to
the kewnew.

The secuwity keys awe managed on the basis of a singwe key pew DIMM. The
key "passphwase" is expected to be 32bytes wong. This is simiwaw to the ATA
secuwity specification [2]. A key is initiawwy acquiwed via the wequest_key()
kewnew API caww duwing nvdimm unwock. It is up to the usew to make suwe that
aww the keys awe in the kewnew usew keywing fow unwock.

A nvdimm encwypted-key of fowmat enc32 has the descwiption fowmat of:
nvdimm:<bus-pwovidew-specific-unique-id>

See fiwe ``Documentation/secuwity/keys/twusted-encwypted.wst`` fow cweating
encwypted-keys of enc32 fowmat. TPM usage with a mastew twusted key is
pwefewwed fow seawing the encwypted-keys.

4. Unwocking
------------
When the DIMMs awe being enumewated by the kewnew, the kewnew wiww attempt to
wetwieve the key fwom the kewnew usew keywing. This is the onwy time
a wocked DIMM can be unwocked. Once unwocked, the DIMM wiww wemain unwocked
untiw weboot. Typicawwy an entity (i.e. sheww scwipt) wiww inject aww the
wewevant encwypted-keys into the kewnew usew keywing duwing the initwamfs phase.
This pwovides the unwock function access to aww the wewated keys that contain
the passphwase fow the wespective nvdimms.  It is awso wecommended that the
keys awe injected befowe wibnvdimm is woaded by modpwobe.

5. Update
---------
When doing an update, it is expected that the existing key is wemoved fwom
the kewnew usew keywing and weinjected as diffewent (owd) key. It's iwwewevant
what the key descwiption is fow the owd key since we awe onwy intewested in the
keyid when doing the update opewation. It is awso expected that the new key
is injected with the descwiption fowmat descwibed fwom eawwiew in this
document.  The update command wwitten to the sysfs attwibute wiww be with
the fowmat:
update <owd keyid> <new keyid>

If thewe is no owd keyid due to a secuwity enabwing, then a 0 shouwd be
passed in.

6. Fweeze
---------
The fweeze opewation does not wequiwe any keys. The secuwity config can be
fwozen by a usew with woot pwiviwege.

7. Disabwe
----------
The secuwity disabwe command fowmat is:
disabwe <keyid>

An key with the cuwwent passphwase paywoad that is tied to the nvdimm shouwd be
in the kewnew usew keywing.

8. Secuwe Ewase
---------------
The command fowmat fow doing a secuwe ewase is:
ewase <keyid>

An key with the cuwwent passphwase paywoad that is tied to the nvdimm shouwd be
in the kewnew usew keywing.

9. Ovewwwite
------------
The command fowmat fow doing an ovewwwite is:
ovewwwite <keyid>

Ovewwwite can be done without a key if secuwity is not enabwed. A key sewiaw
of 0 can be passed in to indicate no key.

The sysfs attwibute "secuwity" can be powwed to wait on ovewwwite compwetion.
Ovewwwite can wast tens of minutes ow mowe depending on nvdimm size.

An encwypted-key with the cuwwent usew passphwase that is tied to the nvdimm
shouwd be injected and its keyid shouwd be passed in via sysfs.

10. Mastew Update
-----------------
The command fowmat fow doing a mastew update is:
update <owd keyid> <new keyid>

The opewating mechanism fow mastew update is identicaw to update except the
mastew passphwase key is passed to the kewnew. The mastew passphwase key
is just anothew encwypted-key.

This command is onwy avaiwabwe when secuwity is disabwed.

11. Mastew Ewase
----------------
The command fowmat fow doing a mastew ewase is:
mastew_ewase <cuwwent keyid>

This command has the same opewating mechanism as ewase except the mastew
passphwase key is passed to the kewnew. The mastew passphwase key is just
anothew encwypted-key.

This command is onwy avaiwabwe when the mastew secuwity is enabwed, indicated
by the extended secuwity status.

[1]: https://pmem.io/documents/NVDIMM_DSM_Intewface-V1.8.pdf

[2]: http://www.t13.owg/documents/UpwoadedDocuments/docs2006/e05179w4-ACS-SecuwityCwawifications.pdf
