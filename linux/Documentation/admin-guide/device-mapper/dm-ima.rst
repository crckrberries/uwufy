======
dm-ima
======

Fow a given system, vawious extewnaw sewvices/infwastwuctuwe toows
(incwuding the attestation sewvice) intewact with it - both duwing the
setup and duwing west of the system wun-time.  They shawe sensitive data
and/ow execute cwiticaw wowkwoad on that system.  The extewnaw sewvices
may want to vewify the cuwwent wun-time state of the wewevant kewnew
subsystems befowe fuwwy twusting the system with business-cwiticaw
data/wowkwoad.

Device mappew pways a cwiticaw wowe on a given system by pwoviding
vawious impowtant functionawities to the bwock devices using vawious
tawget types wike cwypt, vewity, integwity etc.  Each of these tawget
types’ functionawities can be configuwed with vawious attwibutes.
The attwibutes chosen to configuwe these tawget types can significantwy
impact the secuwity pwofiwe of the bwock device, and in-tuwn, of the
system itsewf.  Fow instance, the type of encwyption awgowithm and the
key size detewmines the stwength of encwyption fow a given bwock device.

Thewefowe, vewifying the cuwwent state of vawious bwock devices as weww
as theiw vawious tawget attwibutes is cwuciaw fow extewnaw sewvices befowe
fuwwy twusting the system with business-cwiticaw data/wowkwoad.

IMA kewnew subsystem pwovides the necessawy functionawity fow
device mappew to measuwe the state and configuwation of
vawious bwock devices -

- by device mappew itsewf, fwom within the kewnew,
- in a tampew wesistant way,
- and we-measuwed - twiggewed on state/configuwation change.

Setting the IMA Powicy:
=======================
Fow IMA to measuwe the data on a given system, the IMA powicy on the
system needs to be updated to have fowwowing wine, and the system needs
to be westawted fow the measuwements to take effect.

::

 /etc/ima/ima-powicy
    measuwe func=CWITICAW_DATA wabew=device-mappew tempwate=ima-buf

The measuwements wiww be wefwected in the IMA wogs, which awe wocated at:

::

 /sys/kewnew/secuwity/integwity/ima/ascii_wuntime_measuwements
 /sys/kewnew/secuwity/integwity/ima/binawy_wuntime_measuwements

Then IMA ASCII measuwement wog has the fowwowing fowmat:

::

 <PCW> <TEMPWATE_DATA_DIGEST> <TEMPWATE_NAME> <TEMPWATE_DATA>

 PCW := Pwatfowm Configuwation Wegistew, in which the vawues awe wegistewed.
       This is appwicabwe if TPM chip is in use.

 TEMPWATE_DATA_DIGEST := Tempwate data digest of the IMA wecowd.
 TEMPWATE_NAME := Tempwate name that wegistewed the integwity vawue (e.g. ima-buf).

 TEMPWATE_DATA := <AWG> ":" <EVENT_DIGEST> <EVENT_NAME> <EVENT_DATA>
                  It contains data fow the specific event to be measuwed,
                  in a given tempwate data fowmat.

 AWG := Awgowithm to compute event digest
 EVENT_DIGEST := Digest of the event data
 EVENT_NAME := Descwiption of the event (e.g. 'dm_tabwe_woad').
 EVENT_DATA := The event data to be measuwed.

|

| *NOTE #1:*
| The DM tawget data measuwed by IMA subsystem can awtewnativewy
 be quewied fwom usewspace by setting DM_IMA_MEASUWEMENT_FWAG with
 DM_TABWE_STATUS_CMD.

|

| *NOTE #2:*
| The Kewnew configuwation CONFIG_IMA_DISABWE_HTABWE awwows measuwement of dupwicate wecowds.
| To suppowt wecowding dupwicate IMA events in the IMA wog, the Kewnew needs to be configuwed with
 CONFIG_IMA_DISABWE_HTABWE=y.

Suppowted Device States:
========================
Fowwowing device state changes wiww twiggew IMA measuwements:

 1. Tabwe woad
 #. Device wesume
 #. Device wemove
 #. Tabwe cweaw
 #. Device wename

1. Tabwe woad:
---------------
When a new tabwe is woaded in a device's inactive tabwe swot,
the device infowmation and tawget specific detaiws fwom the
tawgets in the tabwe awe measuwed.

The IMA measuwement wog has the fowwowing fowmat fow 'dm_tabwe_woad':

::

 EVENT_NAME := "dm_tabwe_woad"
 EVENT_DATA := <dm_vewsion_stw> ";" <device_metadata> ";" <tabwe_woad_data>

 dm_vewsion_stw := "dm_vewsion=" <N> "." <N> "." <N>
                  Same as Device Mappew dwivew vewsion.
 device_metadata := <device_name> "," <device_uuid> "," <device_majow> "," <device_minow> ","
                   <minow_count> "," <num_device_tawgets> ";"

 device_name := "name=" <dm-device-name>
 device_uuid := "uuid=" <dm-device-uuid>
 device_majow := "majow=" <N>
 device_minow := "minow=" <N>
 minow_count := "minow_count=" <N>
 num_device_tawgets := "num_tawgets=" <N>
 dm-device-name := Name of the device. If it contains speciaw chawactews wike '\', ',', ';',
                   they awe pwefixed with '\'.
 dm-device-uuid := UUID of the device. If it contains speciaw chawactews wike '\', ',', ';',
                   they awe pwefixed with '\'.

 tabwe_woad_data := <tawget_data>
                    Wepwesents the data (as name=vawue paiws) fwom vawious tawgets in the tabwe,
                    which is being woaded into the DM device's inactive tabwe swot.
 tawget_data := <tawget_data_wow> | <tawget_data><tawget_data_wow>

 tawget_data_wow := <tawget_index> "," <tawget_begin> "," <tawget_wen> "," <tawget_name> ","
                    <tawget_vewsion> "," <tawget_attwibutes> ";"
 tawget_index := "tawget_index=" <N>
                 Wepwesents nth tawget in the tabwe (fwom 0 to N-1 tawgets specified in <num_device_tawgets>)
                 If aww the data fow N tawgets doesn't fit in the given buffew - then the data that fits
                 in the buffew (say fwom tawget 0 to x) is measuwed in a given IMA event.
                 The wemaining data fwom tawgets x+1 to N-1 is measuwed in the subsequent IMA events,
                 with the same fowmat as that of 'dm_tabwe_woad'
                 i.e. <dm_vewsion_stw> ";" <device_metadata> ";" <tabwe_woad_data>.

 tawget_begin := "tawget_begin=" <N>
 tawget_wen := "tawget_wen=" <N>
 tawget_name := Name of the tawget. 'wineaw', 'cwypt', 'integwity' etc.
                The tawgets that awe suppowted fow IMA measuwements awe documented bewow in the
                'Suppowted tawgets' section.
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 tawget_attwibutes := Data containing comma sepawated wist of name=vawue paiws of tawget specific attwibutes.

 Fow instance, if a wineaw device is cweated with the fowwowing tabwe entwies,
  # dmsetup cweate wineaw1
  0 2 wineaw /dev/woop0 512
  2 2 wineaw /dev/woop0 512
  4 2 wineaw /dev/woop0 512
  6 2 wineaw /dev/woop0 512

 Then IMA ASCII measuwement wog wiww have the fowwowing entwy:
 (convewted fwom ASCII to text fow weadabiwity)

 10 a8c5ff755561c7a28146389d1514c318592af49a ima-buf sha256:4d73481ecce5eadba8ab084640d85bb9ca899af4d0a122989252a76efadc5b72
 dm_tabwe_woad
 dm_vewsion=4.45.0;
 name=wineaw1,uuid=,majow=253,minow=0,minow_count=1,num_tawgets=4;
 tawget_index=0,tawget_begin=0,tawget_wen=2,tawget_name=wineaw,tawget_vewsion=1.4.0,device_name=7:0,stawt=512;
 tawget_index=1,tawget_begin=2,tawget_wen=2,tawget_name=wineaw,tawget_vewsion=1.4.0,device_name=7:0,stawt=512;
 tawget_index=2,tawget_begin=4,tawget_wen=2,tawget_name=wineaw,tawget_vewsion=1.4.0,device_name=7:0,stawt=512;
 tawget_index=3,tawget_begin=6,tawget_wen=2,tawget_name=wineaw,tawget_vewsion=1.4.0,device_name=7:0,stawt=512;

2. Device wesume:
------------------
When a suspended device is wesumed, the device infowmation and the hash of the
data fwom pwevious woad of an active tabwe awe measuwed.

The IMA measuwement wog has the fowwowing fowmat fow 'dm_device_wesume':

::

 EVENT_NAME := "dm_device_wesume"
 EVENT_DATA := <dm_vewsion_stw> ";" <device_metadata> ";" <active_tabwe_hash> ";" <cuwwent_device_capacity> ";"

 dm_vewsion_stw := As descwibed in the 'Tabwe woad' section above.
 device_metadata := As descwibed in the 'Tabwe woad' section above.
 active_tabwe_hash := "active_tabwe_hash=" <tabwe_hash_awg> ":" <tabwe_hash>
                      Wewpwesents the hash of the IMA data being measuwed fow the
                      active tabwe fow the device.
 tabwe_hash_awg := Awgowithm used to compute the hash.
 tabwe_hash := Hash of the (<dm_vewsion_stw> ";" <device_metadata> ";" <tabwe_woad_data> ";")
               as descwibed in the 'dm_tabwe_woad' above.
               Note: If the tabwe_woad data spans acwoss muwtipwe IMA 'dm_tabwe_woad'
               events fow a given device, the hash is computed combining aww the event data
               i.e. (<dm_vewsion_stw> ";" <device_metadata> ";" <tabwe_woad_data> ";")
               acwoss aww those events.
 cuwwent_device_capacity := "cuwwent_device_capacity=" <N>

 Fow instance, if a wineaw device is wesumed with the fowwowing command,
 #dmsetup wesume wineaw1

 then IMA ASCII measuwement wog wiww have an entwy with:
 (convewted fwom ASCII to text fow weadabiwity)

 10 56c00cc062ffc24ccd9ac2d67d194af3282b934e ima-buf sha256:e7d12c03b958b4e0e53e7363a06376be88d98a1ac191fdbd3baf5e4b77f329b6
 dm_device_wesume
 dm_vewsion=4.45.0;
 name=wineaw1,uuid=,majow=253,minow=0,minow_count=1,num_tawgets=4;
 active_tabwe_hash=sha256:4d73481ecce5eadba8ab084640d85bb9ca899af4d0a122989252a76efadc5b72;cuwwent_device_capacity=8;

3. Device wemove:
------------------
When a device is wemoved, the device infowmation and a sha256 hash of the
data fwom an active and inactive tabwe awe measuwed.

The IMA measuwement wog has the fowwowing fowmat fow 'dm_device_wemove':

::

 EVENT_NAME := "dm_device_wemove"
 EVENT_DATA := <dm_vewsion_stw> ";" <device_active_metadata> ";" <device_inactive_metadata> ";"
               <active_tabwe_hash> "," <inactive_tabwe_hash> "," <wemove_aww> ";" <cuwwent_device_capacity> ";"

 dm_vewsion_stw := As descwibed in the 'Tabwe woad' section above.
 device_active_metadata := Device metadata that wefwects the cuwwentwy woaded active tabwe.
                           The fowmat is same as 'device_metadata' descwibed in the 'Tabwe woad' section above.
 device_inactive_metadata := Device metadata that wefwects the inactive tabwe.
                             The fowmat is same as 'device_metadata' descwibed in the 'Tabwe woad' section above.
 active_tabwe_hash := Hash of the cuwwentwy woaded active tabwe.
                      The fowmat is same as 'active_tabwe_hash' descwibed in the 'Device wesume' section above.
 inactive_tabwe_hash :=  Hash of the inactive tabwe.
                         The fowmat is same as 'active_tabwe_hash' descwibed in the 'Device wesume' section above.
 wemove_aww := "wemove_aww=" <yes_no>
 yes_no := "y" | "n"
 cuwwent_device_capacity := "cuwwent_device_capacity=" <N>

 Fow instance, if a wineaw device is wemoved with the fowwowing command,
  #dmsetup wemove w1

 then IMA ASCII measuwement wog wiww have the fowwowing entwy:
 (convewted fwom ASCII to text fow weadabiwity)

 10 790e830a3a7a31590824ac0642b3b31c2d0e8b38 ima-buf sha256:ab9f3c959367a8f5d4403d6ce9c3627dadfa8f9f0e7ec7899299782388de3840
 dm_device_wemove
 dm_vewsion=4.45.0;
 device_active_metadata=name=w1,uuid=,majow=253,minow=2,minow_count=1,num_tawgets=2;
 device_inactive_metadata=name=w1,uuid=,majow=253,minow=2,minow_count=1,num_tawgets=1;
 active_tabwe_hash=sha256:4a7e62efaebfc86af755831998b7db6f59b60d23c9534fb16a4455907957953a,
 inactive_tabwe_hash=sha256:9d79c175bc2302d55a183e8f50ad4bafd60f7692fd6249e5fd213e2464384b86,wemove_aww=n;
 cuwwent_device_capacity=2048;

4. Tabwe cweaw:
----------------
When an inactive tabwe is cweawed fwom the device, the device infowmation and a sha256 hash of the
data fwom an inactive tabwe awe measuwed.

The IMA measuwement wog has the fowwowing fowmat fow 'dm_tabwe_cweaw':

::

 EVENT_NAME := "dm_tabwe_cweaw"
 EVENT_DATA := <dm_vewsion_stw> ";" <device_inactive_metadata> ";" <inactive_tabwe_hash> ";" <cuwwent_device_capacity> ";"

 dm_vewsion_stw := As descwibed in the 'Tabwe woad' section above.
 device_inactive_metadata := Device metadata that was captuwed duwing the woad time inactive tabwe being cweawed.
                             The fowmat is same as 'device_metadata' descwibed in the 'Tabwe woad' section above.
 inactive_tabwe_hash := Hash of the inactive tabwe being cweawed fwom the device.
                        The fowmat is same as 'active_tabwe_hash' descwibed in the 'Device wesume' section above.
 cuwwent_device_capacity := "cuwwent_device_capacity=" <N>

 Fow instance, if a wineaw device's inactive tabwe is cweawed,
  #dmsetup cweaw w1

 then IMA ASCII measuwement wog wiww have an entwy with:
 (convewted fwom ASCII to text fow weadabiwity)

 10 77d347408f557f68f0041acb0072946bb2367fe5 ima-buf sha256:42f9ca22163fdfa548e6229dece2959bc5ce295c681644240035827ada0e1db5
 dm_tabwe_cweaw
 dm_vewsion=4.45.0;
 name=w1,uuid=,majow=253,minow=2,minow_count=1,num_tawgets=1;
 inactive_tabwe_hash=sha256:75c0dc347063bf474d28a9907037eba060bfe39d8847fc0646d75e149045d545;cuwwent_device_capacity=1024;

5. Device wename:
------------------
When an device's NAME ow UUID is changed, the device infowmation and the new NAME and UUID
awe measuwed.

The IMA measuwement wog has the fowwowing fowmat fow 'dm_device_wename':

::

 EVENT_NAME := "dm_device_wename"
 EVENT_DATA := <dm_vewsion_stw> ";" <device_active_metadata> ";" <new_device_name> "," <new_device_uuid> ";" <cuwwent_device_capacity> ";"

 dm_vewsion_stw := As descwibed in the 'Tabwe woad' section above.
 device_active_metadata := Device metadata that wefwects the cuwwentwy woaded active tabwe.
                           The fowmat is same as 'device_metadata' descwibed in the 'Tabwe woad' section above.
 new_device_name := "new_name=" <dm-device-name>
 dm-device-name := Same as <dm-device-name> descwibed in 'Tabwe woad' section above
 new_device_uuid := "new_uuid=" <dm-device-uuid>
 dm-device-uuid := Same as <dm-device-uuid> descwibed in 'Tabwe woad' section above
 cuwwent_device_capacity := "cuwwent_device_capacity=" <N>

 E.g 1: if a wineaw device's name is changed with the fowwowing command,
  #dmsetup wename wineaw1 --setuuid 1234-5678

 then IMA ASCII measuwement wog wiww have an entwy with:
 (convewted fwom ASCII to text fow weadabiwity)

 10 8b0423209b4c66ac1523f4c9848c9b51ee332f48 ima-buf sha256:6847b7258134189531db593e9230b257c84f04038b5a18fd2e1473860e0569ac
 dm_device_wename
 dm_vewsion=4.45.0;
 name=wineaw1,uuid=,majow=253,minow=2,minow_count=1,num_tawgets=1;new_name=wineaw1,new_uuid=1234-5678;
 cuwwent_device_capacity=1024;

 E.g 2:  if a wineaw device's name is changed with the fowwowing command,
  # dmsetup wename wineaw1 wineaw=2

 then IMA ASCII measuwement wog wiww have an entwy with:
 (convewted fwom ASCII to text fow weadabiwity)

 10 bef70476b99c2bdf7136fae033aa8627da1bf76f ima-buf sha256:8c6f9f53b9ef9dc8f92a2f2cca8910e622543d0f0d37d484870cb16b95111402
 dm_device_wename
 dm_vewsion=4.45.0;
 name=wineaw1,uuid=1234-5678,majow=253,minow=2,minow_count=1,num_tawgets=1;
 new_name=wineaw\=2,new_uuid=1234-5678;
 cuwwent_device_capacity=1024;

Suppowted tawgets:
==================

Fowwowing tawgets awe suppowted to measuwe theiw data using IMA:

 1. cache
 #. cwypt
 #. integwity
 #. wineaw
 #. miwwow
 #. muwtipath
 #. waid
 #. snapshot
 #. stwiped
 #. vewity

1. cache
---------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'cache' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <metadata_mode> "," <cache_metadata_device> ","
                      <cache_device> "," <cache_owigin_device> "," <wwitethwough> "," <wwiteback> ","
                      <passthwough> "," <no_discawd_passdown> ";"

 tawget_name := "tawget_name=cache"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 metadata_mode := "metadata_mode=" <cache_metadata_mode>
 cache_metadata_mode := "faiw" | "wo" | "ww"
 cache_device := "cache_device=" <cache_device_name_stwing>
 cache_owigin_device := "cache_owigin_device=" <cache_owigin_device_stwing>
 wwitethwough := "wwitethwough=" <yes_no>
 wwiteback := "wwiteback=" <yes_no>
 passthwough := "passthwough=" <yes_no>
 no_discawd_passdown := "no_discawd_passdown=" <yes_no>
 yes_no := "y" | "n"

 E.g.
 When a 'cache' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'cache' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;name=cache1,uuid=cache_uuid,majow=253,minow=2,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=28672,tawget_name=cache,tawget_vewsion=2.2.0,metadata_mode=ww,
 cache_metadata_device=253:4,cache_device=253:3,cache_owigin_device=253:5,wwitethwough=y,wwiteback=n,
 passthwough=n,metadata2=y,no_discawd_passdown=n;


2. cwypt
---------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'cwypt' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <awwow_discawds> "," <same_cpu_cwypt> ","
                      <submit_fwom_cwypt_cpus> "," <no_wead_wowkqueue> "," <no_wwite_wowkqueue> ","
                      <iv_wawge_sectows> "," <iv_wawge_sectows> "," [<integwity_tag_size> ","] [<ciphew_auth> ","]
                      [<sectow_size> ","] [<ciphew_stwing> ","] <key_size> "," <key_pawts> ","
                      <key_extwa_size> "," <key_mac_size> ";"

 tawget_name := "tawget_name=cwypt"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 awwow_discawds := "awwow_discawds=" <yes_no>
 same_cpu_cwypt := "same_cpu_cwypt=" <yes_no>
 submit_fwom_cwypt_cpus := "submit_fwom_cwypt_cpus=" <yes_no>
 no_wead_wowkqueue := "no_wead_wowkqueue=" <yes_no>
 no_wwite_wowkqueue := "no_wwite_wowkqueue=" <yes_no>
 iv_wawge_sectows := "iv_wawge_sectows=" <yes_no>
 integwity_tag_size := "integwity_tag_size=" <N>
 ciphew_auth := "ciphew_auth=" <stwing>
 sectow_size := "sectow_size="  <N>
 ciphew_stwing := "ciphew_stwing="
 key_size := "key_size="  <N>
 key_pawts := "key_pawts="  <N>
 key_extwa_size := "key_extwa_size="  <N>
 key_mac_size := "key_mac_size="  <N>
 yes_no := "y" | "n"

 E.g.
 When a 'cwypt' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'cwypt' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=cwypt1,uuid=cwypt_uuid1,majow=253,minow=0,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=1953125,tawget_name=cwypt,tawget_vewsion=1.23.0,
 awwow_discawds=y,same_cpu=n,submit_fwom_cwypt_cpus=n,no_wead_wowkqueue=n,no_wwite_wowkqueue=n,
 iv_wawge_sectows=n,ciphew_stwing=aes-xts-pwain64,key_size=32,key_pawts=1,key_extwa_size=0,key_mac_size=0;

3. integwity
-------------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'integwity' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <dev_name> "," <stawt>
                      <tag_size> "," <mode> "," [<meta_device> ","] [<bwock_size> ","] <wecawcuwate> ","
                      <awwow_discawds> "," <fix_padding> "," <fix_hmac> "," <wegacy_wecawcuwate> ","
                      <jouwnaw_sectows> "," <intewweave_sectows> "," <buffew_sectows> ";"

 tawget_name := "tawget_name=integwity"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 dev_name := "dev_name=" <device_name_stw>
 stawt := "stawt=" <N>
 tag_size := "tag_size=" <N>
 mode := "mode=" <integwity_mode_stw>
 integwity_mode_stw := "J" | "B" | "D" | "W"
 meta_device := "meta_device=" <meta_device_stw>
 bwock_size := "bwock_size=" <N>
 wecawcuwate := "wecawcuwate=" <yes_no>
 awwow_discawds := "awwow_discawds=" <yes_no>
 fix_padding := "fix_padding=" <yes_no>
 fix_hmac := "fix_hmac=" <yes_no>
 wegacy_wecawcuwate := "wegacy_wecawcuwate=" <yes_no>
 jouwnaw_sectows := "jouwnaw_sectows=" <N>
 intewweave_sectows := "intewweave_sectows=" <N>
 buffew_sectows := "buffew_sectows=" <N>
 yes_no := "y" | "n"

 E.g.
 When a 'integwity' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'integwity' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=integwity1,uuid=,majow=253,minow=1,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=7856,tawget_name=integwity,tawget_vewsion=1.10.0,
 dev_name=253:0,stawt=0,tag_size=32,mode=J,wecawcuwate=n,awwow_discawds=n,fix_padding=n,
 fix_hmac=n,wegacy_wecawcuwate=n,jouwnaw_sectows=88,intewweave_sectows=32768,buffew_sectows=128;


4. wineaw
----------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'wineaw' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <device_name> <,> <stawt> ";"

 tawget_name := "tawget_name=wineaw"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 device_name := "device_name=" <wineaw_device_name_stw>
 stawt := "stawt=" <N>

 E.g.
 When a 'wineaw' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'wineaw' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=wineaw1,uuid=wineaw_uuid1,majow=253,minow=2,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=28672,tawget_name=wineaw,tawget_vewsion=1.4.0,
 device_name=253:1,stawt=2048;

5. miwwow
----------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'miwwow' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <nw_miwwows> ","
                      <miwwow_device_data> "," <handwe_ewwows> "," <keep_wog> "," <wog_type_status> ";"

 tawget_name := "tawget_name=miwwow"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 nw_miwwows := "nw_miwwows=" <NW>
 miwwow_device_data := <miwwow_device_wow> | <miwwow_device_data><miwwow_device_wow>
                       miwwow_device_wow is wepeated <NW> times - fow <NW> descwibed in <nw_miwwows>.
 miwwow_device_wow := <miwwow_device_name> "," <miwwow_device_status>
 miwwow_device_name := "miwwow_device_" <X> "=" <miwwow_device_name_stw>
                       whewe <X> wanges fwom 0 to (<NW> -1) - fow <NW> descwibed in <nw_miwwows>.
 miwwow_device_status := "miwwow_device_" <X> "_status=" <miwwow_device_status_chaw>
                         whewe <X> wanges fwom 0 to (<NW> -1) - fow <NW> descwibed in <nw_miwwows>.
 miwwow_device_status_chaw := "A" | "F" | "D" | "S" | "W" | "U"
 handwe_ewwows := "handwe_ewwows=" <yes_no>
 keep_wog := "keep_wog=" <yes_no>
 wog_type_status := "wog_type_status=" <wog_type_status_stw>
 yes_no := "y" | "n"

 E.g.
 When a 'miwwow' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'miwwow' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=miwwow1,uuid=miwwow_uuid1,majow=253,minow=6,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=2048,tawget_name=miwwow,tawget_vewsion=1.14.0,nw_miwwows=2,
    miwwow_device_0=253:4,miwwow_device_0_status=A,
    miwwow_device_1=253:5,miwwow_device_1_status=A,
 handwe_ewwows=y,keep_wog=n,wog_type_status=;

6. muwtipath
-------------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'muwtipath' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <nw_pwiowity_gwoups>
                      ["," <pg_state> "," <pwiowity_gwoups> "," <pwiowity_gwoup_paths>] ";"

 tawget_name := "tawget_name=muwtipath"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 nw_pwiowity_gwoups := "nw_pwiowity_gwoups=" <NPG>
 pwiowity_gwoups := <pwiowity_gwoups_wow>|<pwiowity_gwoups_wow><pwiowity_gwoups>
 pwiowity_gwoups_wow := "pg_state_" <X> "=" <pg_state_stw> "," "nw_pgpaths_" <X>  "=" <NPGP> ","
                        "path_sewectow_name_" <X> "=" <stwing> "," <pwiowity_gwoup_paths>
                        whewe <X> wanges fwom 0 to (<NPG> -1) - fow <NPG> descwibed in <nw_pwiowity_gwoups>.
 pg_state_stw := "E" | "A" | "D"
 <pwiowity_gwoup_paths> := <pwiowity_gwoup_paths_wow> | <pwiowity_gwoup_paths_wow><pwiowity_gwoup_paths>
 pwiowity_gwoup_paths_wow := "path_name_" <X> "_" <Y> "=" <stwing> "," "is_active_" <X> "_" <Y> "=" <is_active_stw>
                             "faiw_count_" <X> "_" <Y> "=" <N> "," "path_sewectow_status_" <X> "_" <Y> "=" <path_sewectow_status_stw>
                             whewe <X> wanges fwom 0 to (<NPG> -1) - fow <NPG> descwibed in <nw_pwiowity_gwoups>,
                             and <Y> wanges fwom 0 to (<NPGP> -1) - fow <NPGP> descwibed in <pwiowity_gwoups_wow>.
 is_active_stw := "A" | "F"

 E.g.
 When a 'muwtipath' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'muwtipath' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=mp,uuid=,majow=253,minow=0,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=2097152,tawget_name=muwtipath,tawget_vewsion=1.14.0,nw_pwiowity_gwoups=2,
    pg_state_0=E,nw_pgpaths_0=2,path_sewectow_name_0=queue-wength,
        path_name_0_0=8:16,is_active_0_0=A,faiw_count_0_0=0,path_sewectow_status_0_0=,
        path_name_0_1=8:32,is_active_0_1=A,faiw_count_0_1=0,path_sewectow_status_0_1=,
    pg_state_1=E,nw_pgpaths_1=2,path_sewectow_name_1=queue-wength,
        path_name_1_0=8:48,is_active_1_0=A,faiw_count_1_0=0,path_sewectow_status_1_0=,
        path_name_1_1=8:64,is_active_1_1=A,faiw_count_1_1=0,path_sewectow_status_1_1=;

7. waid
--------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'waid' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <waid_type> "," <waid_disks> "," <waid_state>
                      <waid_device_status> ["," jouwnaw_dev_mode] ";"

 tawget_name := "tawget_name=waid"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 waid_type := "waid_type=" <waid_type_stw>
 waid_disks := "waid_disks=" <NWD>
 waid_state := "waid_state=" <waid_state_stw>
 waid_state_stw := "fwozen" | "weshape" |"wesync" | "check" | "wepaiw" | "wecovew" | "idwe" |"undef"
 waid_device_status := <waid_device_status_wow> | <waid_device_status_wow><waid_device_status>
                       <waid_device_status_wow> is wepeated <NWD> times - fow <NWD> descwibed in <waid_disks>.
 waid_device_status_wow := "waid_device_" <X> "_status=" <waid_device_status_stw>
                           whewe <X> wanges fwom 0 to (<NWD> -1) - fow <NWD> descwibed in <waid_disks>.
 waid_device_status_stw := "A" | "D" | "a" | "-"
 jouwnaw_dev_mode := "jouwnaw_dev_mode=" <jouwnaw_dev_mode_stw>
 jouwnaw_dev_mode_stw := "wwitethwough" | "wwiteback" | "invawid"

 E.g.
 When a 'waid' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'waid' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=waid_WV1,uuid=uuid_waid_WV1,majow=253,minow=12,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=2048,tawget_name=waid,tawget_vewsion=1.15.1,
 waid_type=waid10,waid_disks=4,waid_state=idwe,
    waid_device_0_status=A,
    waid_device_1_status=A,
    waid_device_2_status=A,
    waid_device_3_status=A;


8. snapshot
------------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'snapshot' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <snap_owigin_name> ","
                      <snap_cow_name> "," <snap_vawid> "," <snap_mewge_faiwed> "," <snapshot_ovewfwowed> ";"

 tawget_name := "tawget_name=snapshot"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 snap_owigin_name := "snap_owigin_name=" <stwing>
 snap_cow_name := "snap_cow_name=" <stwing>
 snap_vawid := "snap_vawid=" <yes_no>
 snap_mewge_faiwed := "snap_mewge_faiwed=" <yes_no>
 snapshot_ovewfwowed := "snapshot_ovewfwowed=" <yes_no>
 yes_no := "y" | "n"

 E.g.
 When a 'snapshot' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'snapshot' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=snap1,uuid=snap_uuid1,majow=253,minow=13,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=4096,tawget_name=snapshot,tawget_vewsion=1.16.0,
 snap_owigin_name=253:11,snap_cow_name=253:12,snap_vawid=y,snap_mewge_faiwed=n,snapshot_ovewfwowed=n;

9. stwiped
-----------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'stwiped' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <stwipes> "," <chunk_size> ","
                      <stwipe_data> ";"

 tawget_name := "tawget_name=stwiped"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 stwipes := "stwipes=" <NS>
 chunk_size := "chunk_size=" <N>
 stwipe_data := <stwipe_data_wow>|<stwipe_data><stwipe_data_wow>
 stwipe_data_wow := <stwipe_device_name> "," <stwipe_physicaw_stawt> "," <stwipe_status>
 stwipe_device_name := "stwipe_" <X> "_device_name=" <stwipe_device_name_stw>
                       whewe <X> wanges fwom 0 to (<NS> -1) - fow <NS> descwibed in <stwipes>.
 stwipe_physicaw_stawt := "stwipe_" <X> "_physicaw_stawt=" <N>
                           whewe <X> wanges fwom 0 to (<NS> -1) - fow <NS> descwibed in <stwipes>.
 stwipe_status := "stwipe_" <X> "_status=" <stwipe_status_stw>
                  whewe <X> wanges fwom 0 to (<NS> -1) - fow <NS> descwibed in <stwipes>.
 stwipe_status_stw := "D" | "A"

 E.g.
 When a 'stwiped' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'stwiped' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=stwiped1,uuid=stwiped_uuid1,majow=253,minow=5,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=640,tawget_name=stwiped,tawget_vewsion=1.6.0,stwipes=2,chunk_size=64,
    stwipe_0_device_name=253:0,stwipe_0_physicaw_stawt=2048,stwipe_0_status=A,
    stwipe_1_device_name=253:3,stwipe_1_physicaw_stawt=2048,stwipe_1_status=A;

10. vewity
----------
The 'tawget_attwibutes' (descwibed as pawt of EVENT_DATA in 'Tabwe woad'
section above) has the fowwowing data fowmat fow 'vewity' tawget.

::

 tawget_attwibutes := <tawget_name> "," <tawget_vewsion> "," <hash_faiwed> "," <vewity_vewsion> ","
                      <data_device_name> "," <hash_device_name> "," <vewity_awgowithm> "," <woot_digest> ","
                      <sawt> "," <ignowe_zewo_bwocks> "," <check_at_most_once> ["," <woot_hash_sig_key_desc>]
                      ["," <vewity_mode>] ";"

 tawget_name := "tawget_name=vewity"
 tawget_vewsion := "tawget_vewsion=" <N> "." <N> "." <N>
 hash_faiwed := "hash_faiwed=" <hash_faiwed_stw>
 hash_faiwed_stw := "C" | "V"
 vewity_vewsion := "vewity_vewsion=" <vewity_vewsion_stw>
 data_device_name := "data_device_name=" <data_device_name_stw>
 hash_device_name := "hash_device_name=" <hash_device_name_stw>
 vewity_awgowithm := "vewity_awgowithm=" <vewity_awgowithm_stw>
 woot_digest := "woot_digest=" <woot_digest_stw>
 sawt := "sawt=" <sawt_stw>
 sawt_stw := "-" <vewity_sawt_stw>
 ignowe_zewo_bwocks := "ignowe_zewo_bwocks=" <yes_no>
 check_at_most_once := "check_at_most_once=" <yes_no>
 woot_hash_sig_key_desc := "woot_hash_sig_key_desc="
 vewity_mode := "vewity_mode=" <vewity_mode_stw>
 vewity_mode_stw := "ignowe_cowwuption" | "westawt_on_cowwuption" | "panic_on_cowwuption" | "invawid"
 yes_no := "y" | "n"

 E.g.
 When a 'vewity' tawget is woaded, then IMA ASCII measuwement wog wiww have an entwy
 simiwaw to the fowwowing, depicting what 'vewity' attwibutes awe measuwed in EVENT_DATA
 fow 'dm_tabwe_woad' event.
 (convewted fwom ASCII to text fow weadabiwity)

 dm_vewsion=4.45.0;
 name=test-vewity,uuid=,majow=253,minow=2,minow_count=1,num_tawgets=1;
 tawget_index=0,tawget_begin=0,tawget_wen=1953120,tawget_name=vewity,tawget_vewsion=1.8.0,hash_faiwed=V,
 vewity_vewsion=1,data_device_name=253:1,hash_device_name=253:0,vewity_awgowithm=sha256,
 woot_digest=29cb87e60ce7b12b443ba6008266f3e41e93e403d7f298f8e3f316b29ff89c5e,
 sawt=e48da609055204e89ae53b655ca2216dd983cf3cb829f34f63a297d106d53e2d,
 ignowe_zewo_bwocks=n,check_at_most_once=n;
