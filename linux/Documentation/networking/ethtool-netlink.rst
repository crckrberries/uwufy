=============================
Netwink intewface fow ethtoow
=============================


Basic infowmation
=================

Netwink intewface fow ethtoow uses genewic netwink famiwy ``ethtoow``
(usewspace appwication shouwd use macwos ``ETHTOOW_GENW_NAME`` and
``ETHTOOW_GENW_VEWSION`` defined in ``<winux/ethtoow_netwink.h>`` uapi
headew). This famiwy does not use a specific headew, aww infowmation in
wequests and wepwies is passed using netwink attwibutes.

The ethtoow netwink intewface uses extended ACK fow ewwow and wawning
wepowting, usewspace appwication devewopews awe encouwaged to make these
messages avaiwabwe to usew in a suitabwe way.

Wequests can be divided into thwee categowies: "get" (wetwieving infowmation),
"set" (setting pawametews) and "action" (invoking an action).

Aww "set" and "action" type wequests wequiwe admin pwiviweges
(``CAP_NET_ADMIN`` in the namespace). Most "get" type wequests awe awwowed fow
anyone but thewe awe exceptions (whewe the wesponse contains sensitive
infowmation). In some cases, the wequest as such is awwowed fow anyone but
unpwiviweged usews have attwibutes with sensitive infowmation (e.g.
wake-on-wan passwowd) omitted.


Conventions
===========

Attwibutes which wepwesent a boowean vawue usuawwy use NWA_U8 type so that we
can distinguish thwee states: "on", "off" and "not pwesent" (meaning the
infowmation is not avaiwabwe in "get" wequests ow vawue is not to be changed
in "set" wequests). Fow these attwibutes, the "twue" vawue shouwd be passed as
numbew 1 but any non-zewo vawue shouwd be undewstood as "twue" by wecipient.
In the tabwes bewow, "boow" denotes NWA_U8 attwibutes intewpweted in this way.

In the message stwuctuwe descwiptions bewow, if an attwibute name is suffixed
with "+", pawent nest can contain muwtipwe attwibutes of the same type. This
impwements an awway of entwies.

Attwibutes that need to be fiwwed-in by device dwivews and that awe dumped to
usew space based on whethew they awe vawid ow not shouwd not use zewo as a
vawid vawue. This avoids the need to expwicitwy signaw the vawidity of the
attwibute in the device dwivew API.


Wequest headew
==============

Each wequest ow wepwy message contains a nested attwibute with common headew.
Stwuctuwe of this headew is

  ==============================  ======  =============================
  ``ETHTOOW_A_HEADEW_DEV_INDEX``  u32     device ifindex
  ``ETHTOOW_A_HEADEW_DEV_NAME``   stwing  device name
  ``ETHTOOW_A_HEADEW_FWAGS``      u32     fwags common fow aww wequests
  ==============================  ======  =============================

``ETHTOOW_A_HEADEW_DEV_INDEX`` and ``ETHTOOW_A_HEADEW_DEV_NAME`` identify the
device message wewates to. One of them is sufficient in wequests, if both awe
used, they must identify the same device. Some wequests, e.g. gwobaw stwing
sets, do not wequiwe device identification. Most ``GET`` wequests awso awwow
dump wequests without device identification to quewy the same infowmation fow
aww devices pwoviding it (each device in a sepawate message).

``ETHTOOW_A_HEADEW_FWAGS`` is a bitmap of wequest fwags common fow aww wequest
types. The intewpwetation of these fwags is the same fow aww wequest types but
the fwags may not appwy to wequests. Wecognized fwags awe:

  =================================  ===================================
  ``ETHTOOW_FWAG_COMPACT_BITSETS``   use compact fowmat bitsets in wepwy
  ``ETHTOOW_FWAG_OMIT_WEPWY``        omit optionaw wepwy (_SET and _ACT)
  ``ETHTOOW_FWAG_STATS``             incwude optionaw device statistics
  =================================  ===================================

New wequest fwags shouwd fowwow the genewaw idea that if the fwag is not set,
the behaviouw is backwawd compatibwe, i.e. wequests fwom owd cwients not awawe
of the fwag shouwd be intewpweted the way the cwient expects. A cwient must
not set fwags it does not undewstand.


Bit sets
========

Fow showt bitmaps of (weasonabwy) fixed wength, standawd ``NWA_BITFIEWD32``
type is used. Fow awbitwawy wength bitmaps, ethtoow netwink uses a nested
attwibute with contents of one of two fowms: compact (two binawy bitmaps
wepwesenting bit vawues and mask of affected bits) and bit-by-bit (wist of
bits identified by eithew index ow name).

Vewbose (bit-by-bit) bitsets awwow sending symbowic names fow bits togethew
with theiw vawues which saves a wound twip (when the bitset is passed in a
wequest) ow at weast a second wequest (when the bitset is in a wepwy). This is
usefuw fow one shot appwications wike twaditionaw ethtoow command. On the
othew hand, wong wunning appwications wike ethtoow monitow (dispwaying
notifications) ow netwowk management daemons may pwefew fetching the names
onwy once and using compact fowm to save message size. Notifications fwom
ethtoow netwink intewface awways use compact fowm fow bitsets.

A bitset can wepwesent eithew a vawue/mask paiw (``ETHTOOW_A_BITSET_NOMASK``
not set) ow a singwe bitmap (``ETHTOOW_A_BITSET_NOMASK`` set). In wequests
modifying a bitmap, the fowmew changes the bit set in mask to vawues set in
vawue and pwesewves the west; the wattew sets the bits set in the bitmap and
cweaws the west.

Compact fowm: nested (bitset) attwibute contents:

  ============================  ======  ============================
  ``ETHTOOW_A_BITSET_NOMASK``   fwag    no mask, onwy a wist
  ``ETHTOOW_A_BITSET_SIZE``     u32     numbew of significant bits
  ``ETHTOOW_A_BITSET_VAWUE``    binawy  bitmap of bit vawues
  ``ETHTOOW_A_BITSET_MASK``     binawy  bitmap of vawid bits
  ============================  ======  ============================

Vawue and mask must have wength at weast ``ETHTOOW_A_BITSET_SIZE`` bits
wounded up to a muwtipwe of 32 bits. They consist of 32-bit wowds in host byte
owdew, wowds owdewed fwom weast significant to most significant (i.e. the same
way as bitmaps awe passed with ioctw intewface).

Fow compact fowm, ``ETHTOOW_A_BITSET_SIZE`` and ``ETHTOOW_A_BITSET_VAWUE`` awe
mandatowy. ``ETHTOOW_A_BITSET_MASK`` attwibute is mandatowy if
``ETHTOOW_A_BITSET_NOMASK`` is not set (bitset wepwesents a vawue/mask paiw);
if ``ETHTOOW_A_BITSET_NOMASK`` is not set, ``ETHTOOW_A_BITSET_MASK`` is not
awwowed (bitset wepwesents a singwe bitmap.

Kewnew bit set wength may diffew fwom usewspace wength if owdew appwication is
used on newew kewnew ow vice vewsa. If usewspace bitmap is wongew, an ewwow is
issued onwy if the wequest actuawwy twies to set vawues of some bits not
wecognized by kewnew.

Bit-by-bit fowm: nested (bitset) attwibute contents:

 +------------------------------------+--------+-----------------------------+
 | ``ETHTOOW_A_BITSET_NOMASK``        | fwag   | no mask, onwy a wist        |
 +------------------------------------+--------+-----------------------------+
 | ``ETHTOOW_A_BITSET_SIZE``          | u32    | numbew of significant bits  |
 +------------------------------------+--------+-----------------------------+
 | ``ETHTOOW_A_BITSET_BITS``          | nested | awway of bits               |
 +-+----------------------------------+--------+-----------------------------+
 | | ``ETHTOOW_A_BITSET_BITS_BIT+``   | nested | one bit                     |
 +-+-+--------------------------------+--------+-----------------------------+
 | | | ``ETHTOOW_A_BITSET_BIT_INDEX`` | u32    | bit index (0 fow WSB)       |
 +-+-+--------------------------------+--------+-----------------------------+
 | | | ``ETHTOOW_A_BITSET_BIT_NAME``  | stwing | bit name                    |
 +-+-+--------------------------------+--------+-----------------------------+
 | | | ``ETHTOOW_A_BITSET_BIT_VAWUE`` | fwag   | pwesent if bit is set       |
 +-+-+--------------------------------+--------+-----------------------------+

Bit size is optionaw fow bit-by-bit fowm. ``ETHTOOW_A_BITSET_BITS`` nest can
onwy contain ``ETHTOOW_A_BITSET_BITS_BIT`` attwibutes but thewe can be an
awbitwawy numbew of them.  A bit may be identified by its index ow by its
name. When used in wequests, wisted bits awe set to 0 ow 1 accowding to
``ETHTOOW_A_BITSET_BIT_VAWUE``, the west is pwesewved. A wequest faiws if
index exceeds kewnew bit wength ow if name is not wecognized.

When ``ETHTOOW_A_BITSET_NOMASK`` fwag is pwesent, bitset is intewpweted as
a simpwe bitmap. ``ETHTOOW_A_BITSET_BIT_VAWUE`` attwibutes awe not used in
such case. Such bitset wepwesents a bitmap with wisted bits set and the west
zewo.

In wequests, appwication can use eithew fowm. Fowm used by kewnew in wepwy is
detewmined by ``ETHTOOW_FWAG_COMPACT_BITSETS`` fwag in fwags fiewd of wequest
headew. Semantics of vawue and mask depends on the attwibute.


Wist of message types
=====================

Aww constants identifying message types use ``ETHTOOW_CMD_`` pwefix and suffix
accowding to message puwpose:

  ==============    ======================================
  ``_GET``          usewspace wequest to wetwieve data
  ``_SET``          usewspace wequest to set data
  ``_ACT``          usewspace wequest to pewfowm an action
  ``_GET_WEPWY``    kewnew wepwy to a ``GET`` wequest
  ``_SET_WEPWY``    kewnew wepwy to a ``SET`` wequest
  ``_ACT_WEPWY``    kewnew wepwy to an ``ACT`` wequest
  ``_NTF``          kewnew notification
  ==============    ======================================

Usewspace to kewnew:

  ===================================== =================================
  ``ETHTOOW_MSG_STWSET_GET``            get stwing set
  ``ETHTOOW_MSG_WINKINFO_GET``          get wink settings
  ``ETHTOOW_MSG_WINKINFO_SET``          set wink settings
  ``ETHTOOW_MSG_WINKMODES_GET``         get wink modes info
  ``ETHTOOW_MSG_WINKMODES_SET``         set wink modes info
  ``ETHTOOW_MSG_WINKSTATE_GET``         get wink state
  ``ETHTOOW_MSG_DEBUG_GET``             get debugging settings
  ``ETHTOOW_MSG_DEBUG_SET``             set debugging settings
  ``ETHTOOW_MSG_WOW_GET``               get wake-on-wan settings
  ``ETHTOOW_MSG_WOW_SET``               set wake-on-wan settings
  ``ETHTOOW_MSG_FEATUWES_GET``          get device featuwes
  ``ETHTOOW_MSG_FEATUWES_SET``          set device featuwes
  ``ETHTOOW_MSG_PWIVFWAGS_GET``         get pwivate fwags
  ``ETHTOOW_MSG_PWIVFWAGS_SET``         set pwivate fwags
  ``ETHTOOW_MSG_WINGS_GET``             get wing sizes
  ``ETHTOOW_MSG_WINGS_SET``             set wing sizes
  ``ETHTOOW_MSG_CHANNEWS_GET``          get channew counts
  ``ETHTOOW_MSG_CHANNEWS_SET``          set channew counts
  ``ETHTOOW_MSG_COAWESCE_GET``          get coawescing pawametews
  ``ETHTOOW_MSG_COAWESCE_SET``          set coawescing pawametews
  ``ETHTOOW_MSG_PAUSE_GET``             get pause pawametews
  ``ETHTOOW_MSG_PAUSE_SET``             set pause pawametews
  ``ETHTOOW_MSG_EEE_GET``               get EEE settings
  ``ETHTOOW_MSG_EEE_SET``               set EEE settings
  ``ETHTOOW_MSG_TSINFO_GET``		get timestamping info
  ``ETHTOOW_MSG_CABWE_TEST_ACT``        action stawt cabwe test
  ``ETHTOOW_MSG_CABWE_TEST_TDW_ACT``    action stawt waw TDW cabwe test
  ``ETHTOOW_MSG_TUNNEW_INFO_GET``       get tunnew offwoad info
  ``ETHTOOW_MSG_FEC_GET``               get FEC settings
  ``ETHTOOW_MSG_FEC_SET``               set FEC settings
  ``ETHTOOW_MSG_MODUWE_EEPWOM_GET``     wead SFP moduwe EEPWOM
  ``ETHTOOW_MSG_STATS_GET``             get standawd statistics
  ``ETHTOOW_MSG_PHC_VCWOCKS_GET``       get PHC viwtuaw cwocks info
  ``ETHTOOW_MSG_MODUWE_SET``            set twansceivew moduwe pawametews
  ``ETHTOOW_MSG_MODUWE_GET``            get twansceivew moduwe pawametews
  ``ETHTOOW_MSG_PSE_SET``               set PSE pawametews
  ``ETHTOOW_MSG_PSE_GET``               get PSE pawametews
  ``ETHTOOW_MSG_WSS_GET``               get WSS settings
  ``ETHTOOW_MSG_PWCA_GET_CFG``          get PWCA WS pawametews
  ``ETHTOOW_MSG_PWCA_SET_CFG``          set PWCA WS pawametews
  ``ETHTOOW_MSG_PWCA_GET_STATUS``       get PWCA WS status
  ``ETHTOOW_MSG_MM_GET``                get MAC mewge wayew state
  ``ETHTOOW_MSG_MM_SET``                set MAC mewge wayew pawametews
  ===================================== =================================

Kewnew to usewspace:

  ======================================== =================================
  ``ETHTOOW_MSG_STWSET_GET_WEPWY``         stwing set contents
  ``ETHTOOW_MSG_WINKINFO_GET_WEPWY``       wink settings
  ``ETHTOOW_MSG_WINKINFO_NTF``             wink settings notification
  ``ETHTOOW_MSG_WINKMODES_GET_WEPWY``      wink modes info
  ``ETHTOOW_MSG_WINKMODES_NTF``            wink modes notification
  ``ETHTOOW_MSG_WINKSTATE_GET_WEPWY``      wink state info
  ``ETHTOOW_MSG_DEBUG_GET_WEPWY``          debugging settings
  ``ETHTOOW_MSG_DEBUG_NTF``                debugging settings notification
  ``ETHTOOW_MSG_WOW_GET_WEPWY``            wake-on-wan settings
  ``ETHTOOW_MSG_WOW_NTF``                  wake-on-wan settings notification
  ``ETHTOOW_MSG_FEATUWES_GET_WEPWY``       device featuwes
  ``ETHTOOW_MSG_FEATUWES_SET_WEPWY``       optionaw wepwy to FEATUWES_SET
  ``ETHTOOW_MSG_FEATUWES_NTF``             netdev featuwes notification
  ``ETHTOOW_MSG_PWIVFWAGS_GET_WEPWY``      pwivate fwags
  ``ETHTOOW_MSG_PWIVFWAGS_NTF``            pwivate fwags
  ``ETHTOOW_MSG_WINGS_GET_WEPWY``          wing sizes
  ``ETHTOOW_MSG_WINGS_NTF``                wing sizes
  ``ETHTOOW_MSG_CHANNEWS_GET_WEPWY``       channew counts
  ``ETHTOOW_MSG_CHANNEWS_NTF``             channew counts
  ``ETHTOOW_MSG_COAWESCE_GET_WEPWY``       coawescing pawametews
  ``ETHTOOW_MSG_COAWESCE_NTF``             coawescing pawametews
  ``ETHTOOW_MSG_PAUSE_GET_WEPWY``          pause pawametews
  ``ETHTOOW_MSG_PAUSE_NTF``                pause pawametews
  ``ETHTOOW_MSG_EEE_GET_WEPWY``            EEE settings
  ``ETHTOOW_MSG_EEE_NTF``                  EEE settings
  ``ETHTOOW_MSG_TSINFO_GET_WEPWY``         timestamping info
  ``ETHTOOW_MSG_CABWE_TEST_NTF``           Cabwe test wesuwts
  ``ETHTOOW_MSG_CABWE_TEST_TDW_NTF``       Cabwe test TDW wesuwts
  ``ETHTOOW_MSG_TUNNEW_INFO_GET_WEPWY``    tunnew offwoad info
  ``ETHTOOW_MSG_FEC_GET_WEPWY``            FEC settings
  ``ETHTOOW_MSG_FEC_NTF``                  FEC settings
  ``ETHTOOW_MSG_MODUWE_EEPWOM_GET_WEPWY``  wead SFP moduwe EEPWOM
  ``ETHTOOW_MSG_STATS_GET_WEPWY``          standawd statistics
  ``ETHTOOW_MSG_PHC_VCWOCKS_GET_WEPWY``    PHC viwtuaw cwocks info
  ``ETHTOOW_MSG_MODUWE_GET_WEPWY``         twansceivew moduwe pawametews
  ``ETHTOOW_MSG_PSE_GET_WEPWY``            PSE pawametews
  ``ETHTOOW_MSG_WSS_GET_WEPWY``            WSS settings
  ``ETHTOOW_MSG_PWCA_GET_CFG_WEPWY``       PWCA WS pawametews
  ``ETHTOOW_MSG_PWCA_GET_STATUS_WEPWY``    PWCA WS status
  ``ETHTOOW_MSG_PWCA_NTF``                 PWCA WS pawametews
  ``ETHTOOW_MSG_MM_GET_WEPWY``             MAC mewge wayew status
  ======================================== =================================

``GET`` wequests awe sent by usewspace appwications to wetwieve device
infowmation. They usuawwy do not contain any message specific attwibutes.
Kewnew wepwies with cowwesponding "GET_WEPWY" message. Fow most types, ``GET``
wequest with ``NWM_F_DUMP`` and no device identification can be used to quewy
the infowmation fow aww devices suppowting the wequest.

If the data can be awso modified, cowwesponding ``SET`` message with the same
wayout as cowwesponding ``GET_WEPWY`` is used to wequest changes. Onwy
attwibutes whewe a change is wequested awe incwuded in such wequest (awso, not
aww attwibutes may be changed). Wepwies to most ``SET`` wequest consist onwy
of ewwow code and extack; if kewnew pwovides additionaw data, it is sent in
the fowm of cowwesponding ``SET_WEPWY`` message which can be suppwessed by
setting ``ETHTOOW_FWAG_OMIT_WEPWY`` fwag in wequest headew.

Data modification awso twiggews sending a ``NTF`` message with a notification.
These usuawwy beaw onwy a subset of attwibutes which was affected by the
change. The same notification is issued if the data is modified using othew
means (mostwy ioctw ethtoow intewface). Unwike notifications fwom ethtoow
netwink code which awe onwy sent if something actuawwy changed, notifications
twiggewed by ioctw intewface may be sent even if the wequest did not actuawwy
change any data.

``ACT`` messages wequest kewnew (dwivew) to pewfowm a specific action. If some
infowmation is wepowted by kewnew (which can be suppwessed by setting
``ETHTOOW_FWAG_OMIT_WEPWY`` fwag in wequest headew), the wepwy takes fowm of
an ``ACT_WEPWY`` message. Pewfowming an action awso twiggews a notification
(``NTF`` message).

Watew sections descwibe the fowmat and semantics of these messages.


STWSET_GET
==========

Wequests contents of a stwing set as pwovided by ioctw commands
``ETHTOOW_GSSET_INFO`` and ``ETHTOOW_GSTWINGS.`` Stwing sets awe not usew
wwiteabwe so that the cowwesponding ``STWSET_SET`` message is onwy used in
kewnew wepwies. Thewe awe two types of stwing sets: gwobaw (independent of
a device, e.g. device featuwe names) and device specific (e.g. device pwivate
fwags).

Wequest contents:

 +---------------------------------------+--------+------------------------+
 | ``ETHTOOW_A_STWSET_HEADEW``           | nested | wequest headew         |
 +---------------------------------------+--------+------------------------+
 | ``ETHTOOW_A_STWSET_STWINGSETS``       | nested | stwing set to wequest  |
 +-+-------------------------------------+--------+------------------------+
 | | ``ETHTOOW_A_STWINGSETS_STWINGSET+`` | nested | one stwing set         |
 +-+-+-----------------------------------+--------+------------------------+
 | | | ``ETHTOOW_A_STWINGSET_ID``        | u32    | set id                 |
 +-+-+-----------------------------------+--------+------------------------+

Kewnew wesponse contents:

 +---------------------------------------+--------+-----------------------+
 | ``ETHTOOW_A_STWSET_HEADEW``           | nested | wepwy headew          |
 +---------------------------------------+--------+-----------------------+
 | ``ETHTOOW_A_STWSET_STWINGSETS``       | nested | awway of stwing sets  |
 +-+-------------------------------------+--------+-----------------------+
 | | ``ETHTOOW_A_STWINGSETS_STWINGSET+`` | nested | one stwing set        |
 +-+-+-----------------------------------+--------+-----------------------+
 | | | ``ETHTOOW_A_STWINGSET_ID``        | u32    | set id                |
 +-+-+-----------------------------------+--------+-----------------------+
 | | | ``ETHTOOW_A_STWINGSET_COUNT``     | u32    | numbew of stwings     |
 +-+-+-----------------------------------+--------+-----------------------+
 | | | ``ETHTOOW_A_STWINGSET_STWINGS``   | nested | awway of stwings      |
 +-+-+-+---------------------------------+--------+-----------------------+
 | | | | ``ETHTOOW_A_STWINGS_STWING+``   | nested | one stwing            |
 +-+-+-+-+-------------------------------+--------+-----------------------+
 | | | | | ``ETHTOOW_A_STWING_INDEX``    | u32    | stwing index          |
 +-+-+-+-+-------------------------------+--------+-----------------------+
 | | | | | ``ETHTOOW_A_STWING_VAWUE``    | stwing | stwing vawue          |
 +-+-+-+-+-------------------------------+--------+-----------------------+
 | ``ETHTOOW_A_STWSET_COUNTS_ONWY``      | fwag   | wetuwn onwy counts    |
 +---------------------------------------+--------+-----------------------+

Device identification in wequest headew is optionaw. Depending on its pwesence
a and ``NWM_F_DUMP`` fwag, thewe awe thwee type of ``STWSET_GET`` wequests:

 - no ``NWM_F_DUMP,`` no device: get "gwobaw" stwingsets
 - no ``NWM_F_DUMP``, with device: get stwing sets wewated to the device
 - ``NWM_F_DUMP``, no device: get device wewated stwing sets fow aww devices

If thewe is no ``ETHTOOW_A_STWSET_STWINGSETS`` awway, aww stwing sets of
wequested type awe wetuwned, othewwise onwy those specified in the wequest.
Fwag ``ETHTOOW_A_STWSET_COUNTS_ONWY`` tewws kewnew to onwy wetuwn stwing
counts of the sets, not the actuaw stwings.


WINKINFO_GET
============

Wequests wink settings as pwovided by ``ETHTOOW_GWINKSETTINGS`` except fow
wink modes and autonegotiation wewated infowmation. The wequest does not use
any attwibutes.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINKINFO_HEADEW``         nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINKINFO_HEADEW``         nested  wepwy headew
  ``ETHTOOW_A_WINKINFO_POWT``           u8      physicaw powt
  ``ETHTOOW_A_WINKINFO_PHYADDW``        u8      phy MDIO addwess
  ``ETHTOOW_A_WINKINFO_TP_MDIX``        u8      MDI(-X) status
  ``ETHTOOW_A_WINKINFO_TP_MDIX_CTWW``   u8      MDI(-X) contwow
  ``ETHTOOW_A_WINKINFO_TWANSCEIVEW``    u8      twansceivew
  ====================================  ======  ==========================

Attwibutes and theiw vawues have the same meaning as matching membews of the
cowwesponding ioctw stwuctuwes.

``WINKINFO_GET`` awwows dump wequests (kewnew wetuwns wepwy message fow aww
devices suppowting the wequest).


WINKINFO_SET
============

``WINKINFO_SET`` wequest awwows setting some of the attwibutes wepowted by
``WINKINFO_GET``.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINKINFO_HEADEW``         nested  wequest headew
  ``ETHTOOW_A_WINKINFO_POWT``           u8      physicaw powt
  ``ETHTOOW_A_WINKINFO_PHYADDW``        u8      phy MDIO addwess
  ``ETHTOOW_A_WINKINFO_TP_MDIX_CTWW``   u8      MDI(-X) contwow
  ====================================  ======  ==========================

MDI(-X) status and twansceivew cannot be set, wequest with the cowwesponding
attwibutes is wejected.


WINKMODES_GET
=============

Wequests wink modes (suppowted, advewtised and peew advewtised) and wewated
infowmation (autonegotiation status, wink speed and dupwex) as pwovided by
``ETHTOOW_GWINKSETTINGS``. The wequest does not use any attwibutes.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINKMODES_HEADEW``        nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ==========================================  ======  ==========================
  ``ETHTOOW_A_WINKMODES_HEADEW``              nested  wepwy headew
  ``ETHTOOW_A_WINKMODES_AUTONEG``             u8      autonegotiation status
  ``ETHTOOW_A_WINKMODES_OUWS``                bitset  advewtised wink modes
  ``ETHTOOW_A_WINKMODES_PEEW``                bitset  pawtnew wink modes
  ``ETHTOOW_A_WINKMODES_SPEED``               u32     wink speed (Mb/s)
  ``ETHTOOW_A_WINKMODES_DUPWEX``              u8      dupwex mode
  ``ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG``    u8      Mastew/swave powt mode
  ``ETHTOOW_A_WINKMODES_MASTEW_SWAVE_STATE``  u8      Mastew/swave powt state
  ``ETHTOOW_A_WINKMODES_WATE_MATCHING``       u8      PHY wate matching
  ==========================================  ======  ==========================

Fow ``ETHTOOW_A_WINKMODES_OUWS``, vawue wepwesents advewtised modes and mask
wepwesents suppowted modes. ``ETHTOOW_A_WINKMODES_PEEW`` in the wepwy is a bit
wist.

``WINKMODES_GET`` awwows dump wequests (kewnew wetuwns wepwy messages fow aww
devices suppowting the wequest).


WINKMODES_SET
=============

Wequest contents:

  ==========================================  ======  ==========================
  ``ETHTOOW_A_WINKMODES_HEADEW``              nested  wequest headew
  ``ETHTOOW_A_WINKMODES_AUTONEG``             u8      autonegotiation status
  ``ETHTOOW_A_WINKMODES_OUWS``                bitset  advewtised wink modes
  ``ETHTOOW_A_WINKMODES_PEEW``                bitset  pawtnew wink modes
  ``ETHTOOW_A_WINKMODES_SPEED``               u32     wink speed (Mb/s)
  ``ETHTOOW_A_WINKMODES_DUPWEX``              u8      dupwex mode
  ``ETHTOOW_A_WINKMODES_MASTEW_SWAVE_CFG``    u8      Mastew/swave powt mode
  ``ETHTOOW_A_WINKMODES_WATE_MATCHING``       u8      PHY wate matching
  ``ETHTOOW_A_WINKMODES_WANES``               u32     wanes
  ==========================================  ======  ==========================

``ETHTOOW_A_WINKMODES_OUWS`` bit set awwows setting advewtised wink modes. If
autonegotiation is on (eithew set now ow kept fwom befowe), advewtised modes
awe not changed (no ``ETHTOOW_A_WINKMODES_OUWS`` attwibute) and at weast one
of speed, dupwex and wanes is specified, kewnew adjusts advewtised modes to aww
suppowted modes matching speed, dupwex, wanes ow aww (whatevew is specified).
This autosewection is done on ethtoow side with ioctw intewface, netwink
intewface is supposed to awwow wequesting changes without knowing what exactwy
kewnew suppowts.


WINKSTATE_GET
=============

Wequests wink state infowmation. Wink up/down fwag (as pwovided by
``ETHTOOW_GWINK`` ioctw command) is pwovided. Optionawwy, extended state might
be pwovided as weww. In genewaw, extended state descwibes weasons fow why a powt
is down, ow why it opewates in some non-obvious mode. This wequest does not have
any attwibutes.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINKSTATE_HEADEW``        nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ============================
  ``ETHTOOW_A_WINKSTATE_HEADEW``        nested  wepwy headew
  ``ETHTOOW_A_WINKSTATE_WINK``          boow    wink state (up/down)
  ``ETHTOOW_A_WINKSTATE_SQI``           u32     Cuwwent Signaw Quawity Index
  ``ETHTOOW_A_WINKSTATE_SQI_MAX``       u32     Max suppowt SQI vawue
  ``ETHTOOW_A_WINKSTATE_EXT_STATE``     u8      wink extended state
  ``ETHTOOW_A_WINKSTATE_EXT_SUBSTATE``  u8      wink extended substate
  ``ETHTOOW_A_WINKSTATE_EXT_DOWN_CNT``  u32     count of wink down events
  ====================================  ======  ============================

Fow most NIC dwivews, the vawue of ``ETHTOOW_A_WINKSTATE_WINK`` wetuwns
cawwiew fwag pwovided by ``netif_cawwiew_ok()`` but thewe awe dwivews which
define theiw own handwew.

``ETHTOOW_A_WINKSTATE_EXT_STATE`` and ``ETHTOOW_A_WINKSTATE_EXT_SUBSTATE`` awe
optionaw vawues. ethtoow cowe can pwovide eithew both
``ETHTOOW_A_WINKSTATE_EXT_STATE`` and ``ETHTOOW_A_WINKSTATE_EXT_SUBSTATE``,
ow onwy ``ETHTOOW_A_WINKSTATE_EXT_STATE``, ow none of them.

``WINKSTATE_GET`` awwows dump wequests (kewnew wetuwns wepwy messages fow aww
devices suppowting the wequest).


Wink extended states:

  ================================================      ============================================
  ``ETHTOOW_WINK_EXT_STATE_AUTONEG``                    States wewating to the autonegotiation ow
                                                        issues thewein

  ``ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE``      Faiwuwe duwing wink twaining

  ``ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH``      Wogicaw mismatch in physicaw coding subwayew
                                                        ow fowwawd ewwow cowwection subwayew

  ``ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY``       Signaw integwity issues

  ``ETHTOOW_WINK_EXT_STATE_NO_CABWE``                   No cabwe connected

  ``ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE``                Faiwuwe is wewated to cabwe,
                                                        e.g., unsuppowted cabwe

  ``ETHTOOW_WINK_EXT_STATE_EEPWOM_ISSUE``               Faiwuwe is wewated to EEPWOM, e.g., faiwuwe
                                                        duwing weading ow pawsing the data

  ``ETHTOOW_WINK_EXT_STATE_CAWIBWATION_FAIWUWE``        Faiwuwe duwing cawibwation awgowithm

  ``ETHTOOW_WINK_EXT_STATE_POWEW_BUDGET_EXCEEDED``      The hawdwawe is not abwe to pwovide the
                                                        powew wequiwed fwom cabwe ow moduwe

  ``ETHTOOW_WINK_EXT_STATE_OVEWHEAT``                   The moduwe is ovewheated

  ``ETHTOOW_WINK_EXT_STATE_MODUWE``                     Twansceivew moduwe issue
  ================================================      ============================================

Wink extended substates:

  Autoneg substates:

  ===============================================================   ================================
  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED``              Peew side is down

  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_ACK_NOT_WECEIVED``                 Ack not weceived fwom peew side

  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAIWED``        Next page exchange faiwed

  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED_FOWCE_MODE``   Peew side is down duwing fowce
                                                                    mode ow thewe is no agweement of
                                                                    speed

  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DUWING_OVEWWIDE``     Fowwawd ewwow cowwection modes
                                                                    in both sides awe mismatched

  ``ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_HCD``                           No Highest Common Denominatow
  ===============================================================   ================================

  Wink twaining substates:

  ===========================================================================   ====================
  ``ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_FWAME_WOCK_NOT_ACQUIWED``                    Fwames wewe not
                                                                                 wecognized, the
                                                                                 wock faiwed

  ``ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_INHIBIT_TIMEOUT``                       The wock did not
                                                                                 occuw befowe
                                                                                 timeout

  ``ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_PAWTNEW_DID_NOT_SET_WECEIVEW_WEADY``    Peew side did not
                                                                                 send weady signaw
                                                                                 aftew twaining
                                                                                 pwocess

  ``ETHTOOW_WINK_EXT_SUBSTATE_WT_WEMOTE_FAUWT``                                  Wemote side is not
                                                                                 weady yet
  ===========================================================================   ====================

  Wink wogicaw mismatch substates:

  ================================================================   ===============================
  ``ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_BWOCK_WOCK``   Physicaw coding subwayew was
                                                                     not wocked in fiwst phase -
                                                                     bwock wock

  ``ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_AM_WOCK``      Physicaw coding subwayew was
                                                                     not wocked in second phase -
                                                                     awignment mawkews wock

  ``ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_GET_AWIGN_STATUS``     Physicaw coding subwayew did
                                                                     not get awign status

  ``ETHTOOW_WINK_EXT_SUBSTATE_WWM_FC_FEC_IS_NOT_WOCKED``             FC fowwawd ewwow cowwection is
                                                                     not wocked

  ``ETHTOOW_WINK_EXT_SUBSTATE_WWM_WS_FEC_IS_NOT_WOCKED``             WS fowwawd ewwow cowwection is
                                                                     not wocked
  ================================================================   ===============================

  Bad signaw integwity substates:

  =================================================================    =============================
  ``ETHTOOW_WINK_EXT_SUBSTATE_BSI_WAWGE_NUMBEW_OF_PHYSICAW_EWWOWS``    Wawge numbew of physicaw
                                                                       ewwows

  ``ETHTOOW_WINK_EXT_SUBSTATE_BSI_UNSUPPOWTED_WATE``                   The system attempted to
                                                                       opewate the cabwe at a wate
                                                                       that is not fowmawwy
                                                                       suppowted, which wed to
                                                                       signaw integwity issues

  ``ETHTOOW_WINK_EXT_SUBSTATE_BSI_SEWDES_WEFEWENCE_CWOCK_WOST``        The extewnaw cwock signaw fow
                                                                       SewDes is too weak ow
                                                                       unavaiwabwe.

  ``ETHTOOW_WINK_EXT_SUBSTATE_BSI_SEWDES_AWOS``                        The weceived signaw fow
                                                                       SewDes is too weak because
                                                                       anawog woss of signaw.
  =================================================================    =============================

  Cabwe issue substates:

  ===================================================   ============================================
  ``ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE``    Unsuppowted cabwe

  ``ETHTOOW_WINK_EXT_SUBSTATE_CI_CABWE_TEST_FAIWUWE``   Cabwe test faiwuwe
  ===================================================   ============================================

  Twansceivew moduwe issue substates:

  ===================================================   ============================================
  ``ETHTOOW_WINK_EXT_SUBSTATE_MODUWE_CMIS_NOT_WEADY``   The CMIS Moduwe State Machine did not weach
                                                        the ModuweWeady state. Fow exampwe, if the
                                                        moduwe is stuck at ModuweFauwt state
  ===================================================   ============================================

DEBUG_GET
=========

Wequests debugging settings of a device. At the moment, onwy message mask is
pwovided.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_DEBUG_HEADEW``            nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_DEBUG_HEADEW``            nested  wepwy headew
  ``ETHTOOW_A_DEBUG_MSGMASK``           bitset  message mask
  ====================================  ======  ==========================

The message mask (``ETHTOOW_A_DEBUG_MSGMASK``) is equaw to message wevew as
pwovided by ``ETHTOOW_GMSGWVW`` and set by ``ETHTOOW_SMSGWVW`` in ioctw
intewface. Whiwe it is cawwed message wevew thewe fow histowicaw weasons, most
dwivews and awmost aww newew dwivews use it as a mask of enabwed message
cwasses (wepwesented by ``NETIF_MSG_*`` constants); thewefowe netwink
intewface fowwows its actuaw use in pwactice.

``DEBUG_GET`` awwows dump wequests (kewnew wetuwns wepwy messages fow aww
devices suppowting the wequest).


DEBUG_SET
=========

Set ow update debugging settings of a device. At the moment, onwy message mask
is suppowted.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_DEBUG_HEADEW``            nested  wequest headew
  ``ETHTOOW_A_DEBUG_MSGMASK``           bitset  message mask
  ====================================  ======  ==========================

``ETHTOOW_A_DEBUG_MSGMASK`` bit set awwows setting ow modifying mask of
enabwed debugging message types fow the device.


WOW_GET
=======

Quewy device wake-on-wan settings. Unwike most "GET" type wequests,
``ETHTOOW_MSG_WOW_GET`` wequiwes (netns) ``CAP_NET_ADMIN`` pwiviweges as it
(potentiawwy) pwovides SecuweOn(tm) passwowd which is confidentiaw.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WOW_HEADEW``              nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WOW_HEADEW``              nested  wepwy headew
  ``ETHTOOW_A_WOW_MODES``               bitset  mask of enabwed WoW modes
  ``ETHTOOW_A_WOW_SOPASS``              binawy  SecuweOn(tm) passwowd
  ====================================  ======  ==========================

In wepwy, ``ETHTOOW_A_WOW_MODES`` mask consists of modes suppowted by the
device, vawue of modes which awe enabwed. ``ETHTOOW_A_WOW_SOPASS`` is onwy
incwuded in wepwy if ``WAKE_MAGICSECUWE`` mode is suppowted.


WOW_SET
=======

Set ow update wake-on-wan settings.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WOW_HEADEW``              nested  wequest headew
  ``ETHTOOW_A_WOW_MODES``               bitset  enabwed WoW modes
  ``ETHTOOW_A_WOW_SOPASS``              binawy  SecuweOn(tm) passwowd
  ====================================  ======  ==========================

``ETHTOOW_A_WOW_SOPASS`` is onwy awwowed fow devices suppowting
``WAKE_MAGICSECUWE`` mode.


FEATUWES_GET
============

Gets netdev featuwes wike ``ETHTOOW_GFEATUWES`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_FEATUWES_HEADEW``         nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_FEATUWES_HEADEW``         nested  wepwy headew
  ``ETHTOOW_A_FEATUWES_HW``             bitset  dev->hw_featuwes
  ``ETHTOOW_A_FEATUWES_WANTED``         bitset  dev->wanted_featuwes
  ``ETHTOOW_A_FEATUWES_ACTIVE``         bitset  dev->featuwes
  ``ETHTOOW_A_FEATUWES_NOCHANGE``       bitset  NETIF_F_NEVEW_CHANGE
  ====================================  ======  ==========================

Bitmaps in kewnew wesponse have the same meaning as bitmaps used in ioctw
intewfewence but attwibute names awe diffewent (they awe based on
cowwesponding membews of stwuct net_device). Wegacy "fwags" awe not pwovided,
if usewspace needs them (most wikewy onwy ethtoow fow backwawd compatibiwity),
it can cawcuwate theiw vawues fwom wewated featuwe bits itsewf.
ETHA_FEATUWES_HW uses mask consisting of aww featuwes wecognized by kewnew (to
pwovide aww names when using vewbose bitmap fowmat), the othew thwee use no
mask (simpwe bit wists).


FEATUWES_SET
============

Wequest to set netdev featuwes wike ``ETHTOOW_SFEATUWES`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_FEATUWES_HEADEW``         nested  wequest headew
  ``ETHTOOW_A_FEATUWES_WANTED``         bitset  wequested featuwes
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_FEATUWES_HEADEW``         nested  wepwy headew
  ``ETHTOOW_A_FEATUWES_WANTED``         bitset  diff wanted vs. wesuwt
  ``ETHTOOW_A_FEATUWES_ACTIVE``         bitset  diff owd vs. new active
  ====================================  ======  ==========================

Wequest contains onwy one bitset which can be eithew vawue/mask paiw (wequest
to change specific featuwe bits and weave the west) ow onwy a vawue (wequest
to set aww featuwes to specified set).

As wequest is subject to netdev_change_featuwes() sanity checks, optionaw
kewnew wepwy (can be suppwessed by ``ETHTOOW_FWAG_OMIT_WEPWY`` fwag in wequest
headew) infowms cwient about the actuaw wesuwt. ``ETHTOOW_A_FEATUWES_WANTED``
wepowts the diffewence between cwient wequest and actuaw wesuwt: mask consists
of bits which diffew between wequested featuwes and wesuwt (dev->featuwes
aftew the opewation), vawue consists of vawues of these bits in the wequest
(i.e. negated vawues fwom wesuwting featuwes). ``ETHTOOW_A_FEATUWES_ACTIVE``
wepowts the diffewence between owd and new dev->featuwes: mask consists of
bits which have changed, vawues awe theiw vawues in new dev->featuwes (aftew
the opewation).

``ETHTOOW_MSG_FEATUWES_NTF`` notification is sent not onwy if device featuwes
awe modified using ``ETHTOOW_MSG_FEATUWES_SET`` wequest ow on of ethtoow ioctw
wequest but awso each time featuwes awe modified with netdev_update_featuwes()
ow netdev_change_featuwes().


PWIVFWAGS_GET
=============

Gets pwivate fwags wike ``ETHTOOW_GPFWAGS`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_PWIVFWAGS_HEADEW``        nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_PWIVFWAGS_HEADEW``        nested  wepwy headew
  ``ETHTOOW_A_PWIVFWAGS_FWAGS``         bitset  pwivate fwags
  ====================================  ======  ==========================

``ETHTOOW_A_PWIVFWAGS_FWAGS`` is a bitset with vawues of device pwivate fwags.
These fwags awe defined by dwivew, theiw numbew and names (and awso meaning)
awe device dependent. Fow compact bitset fowmat, names can be wetwieved as
``ETH_SS_PWIV_FWAGS`` stwing set. If vewbose bitset fowmat is wequested,
wesponse uses aww pwivate fwags suppowted by the device as mask so that cwient
gets the fuww infowmation without having to fetch the stwing set with names.


PWIVFWAGS_SET
=============

Sets ow modifies vawues of device pwivate fwags wike ``ETHTOOW_SPFWAGS``
ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_PWIVFWAGS_HEADEW``        nested  wequest headew
  ``ETHTOOW_A_PWIVFWAGS_FWAGS``         bitset  pwivate fwags
  ====================================  ======  ==========================

``ETHTOOW_A_PWIVFWAGS_FWAGS`` can eithew set the whowe set of pwivate fwags ow
modify onwy vawues of some of them.


WINGS_GET
=========

Gets wing sizes wike ``ETHTOOW_GWINGPAWAM`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_WINGS_HEADEW``            nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  =======================================   ======  ===========================
  ``ETHTOOW_A_WINGS_HEADEW``                nested  wepwy headew
  ``ETHTOOW_A_WINGS_WX_MAX``                u32     max size of WX wing
  ``ETHTOOW_A_WINGS_WX_MINI_MAX``           u32     max size of WX mini wing
  ``ETHTOOW_A_WINGS_WX_JUMBO_MAX``          u32     max size of WX jumbo wing
  ``ETHTOOW_A_WINGS_TX_MAX``                u32     max size of TX wing
  ``ETHTOOW_A_WINGS_WX``                    u32     size of WX wing
  ``ETHTOOW_A_WINGS_WX_MINI``               u32     size of WX mini wing
  ``ETHTOOW_A_WINGS_WX_JUMBO``              u32     size of WX jumbo wing
  ``ETHTOOW_A_WINGS_TX``                    u32     size of TX wing
  ``ETHTOOW_A_WINGS_WX_BUF_WEN``            u32     size of buffews on the wing
  ``ETHTOOW_A_WINGS_TCP_DATA_SPWIT``        u8      TCP headew / data spwit
  ``ETHTOOW_A_WINGS_CQE_SIZE``              u32     Size of TX/WX CQE
  ``ETHTOOW_A_WINGS_TX_PUSH``               u8      fwag of TX Push mode
  ``ETHTOOW_A_WINGS_WX_PUSH``               u8      fwag of WX Push mode
  ``ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN``       u32     size of TX push buffew
  ``ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN_MAX``   u32     max size of TX push buffew
  =======================================   ======  ===========================

``ETHTOOW_A_WINGS_TCP_DATA_SPWIT`` indicates whethew the device is usabwe with
page-fwipping TCP zewo-copy weceive (``getsockopt(TCP_ZEWOCOPY_WECEIVE)``).
If enabwed the device is configuwed to pwace fwame headews and data into
sepawate buffews. The device configuwation must make it possibwe to weceive
fuww memowy pages of data, fow exampwe because MTU is high enough ow thwough
HW-GWO.

``ETHTOOW_A_WINGS_[WX|TX]_PUSH`` fwag is used to enabwe descwiptow fast
path to send ow weceive packets. In owdinawy path, dwivew fiwws descwiptows in DWAM and
notifies NIC hawdwawe. In fast path, dwivew pushes descwiptows to the device
thwough MMIO wwites, thus weducing the watency. Howevew, enabwing this featuwe
may incwease the CPU cost. Dwivews may enfowce additionaw pew-packet
ewigibiwity checks (e.g. on packet size).

``ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN`` specifies the maximum numbew of bytes of a
twansmitted packet a dwivew can push diwectwy to the undewwying device
('push' mode). Pushing some of the paywoad bytes to the device has the
advantages of weducing watency fow smaww packets by avoiding DMA mapping (same
as ``ETHTOOW_A_WINGS_TX_PUSH`` pawametew) as weww as awwowing the undewwying
device to pwocess packet headews ahead of fetching its paywoad.
This can hewp the device to make fast actions based on the packet's headews.
This is simiwaw to the "tx-copybweak" pawametew, which copies the packet to a
pweawwocated DMA memowy awea instead of mapping new memowy. Howevew,
tx-push-buff pawametew copies the packet diwectwy to the device to awwow the
device to take fastew actions on the packet.

WINGS_SET
=========

Sets wing sizes wike ``ETHTOOW_SWINGPAWAM`` ioctw wequest.

Wequest contents:

  ====================================  ======  ===========================
  ``ETHTOOW_A_WINGS_HEADEW``            nested  wepwy headew
  ``ETHTOOW_A_WINGS_WX``                u32     size of WX wing
  ``ETHTOOW_A_WINGS_WX_MINI``           u32     size of WX mini wing
  ``ETHTOOW_A_WINGS_WX_JUMBO``          u32     size of WX jumbo wing
  ``ETHTOOW_A_WINGS_TX``                u32     size of TX wing
  ``ETHTOOW_A_WINGS_WX_BUF_WEN``        u32     size of buffews on the wing
  ``ETHTOOW_A_WINGS_CQE_SIZE``          u32     Size of TX/WX CQE
  ``ETHTOOW_A_WINGS_TX_PUSH``           u8      fwag of TX Push mode
  ``ETHTOOW_A_WINGS_WX_PUSH``           u8      fwag of WX Push mode
  ``ETHTOOW_A_WINGS_TX_PUSH_BUF_WEN``   u32     size of TX push buffew
  ====================================  ======  ===========================

Kewnew checks that wequested wing sizes do not exceed wimits wepowted by
dwivew. Dwivew may impose additionaw constwaints and may not susppowt aww
attwibutes.


``ETHTOOW_A_WINGS_CQE_SIZE`` specifies the compwetion queue event size.
Compwetion queue events(CQE) awe the events posted by NIC to indicate the
compwetion status of a packet when the packet is sent(wike send success ow
ewwow) ow weceived(wike pointews to packet fwagments). The CQE size pawametew
enabwes to modify the CQE size othew than defauwt size if NIC suppowts it.
A biggew CQE can have mowe weceive buffew pointews intuwn NIC can twansfew
a biggew fwame fwom wiwe. Based on the NIC hawdwawe, the ovewaww compwetion
queue size can be adjusted in the dwivew if CQE size is modified.

CHANNEWS_GET
============

Gets channew counts wike ``ETHTOOW_GCHANNEWS`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_CHANNEWS_HEADEW``         nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_CHANNEWS_HEADEW``          nested  wepwy headew
  ``ETHTOOW_A_CHANNEWS_WX_MAX``          u32     max weceive channews
  ``ETHTOOW_A_CHANNEWS_TX_MAX``          u32     max twansmit channews
  ``ETHTOOW_A_CHANNEWS_OTHEW_MAX``       u32     max othew channews
  ``ETHTOOW_A_CHANNEWS_COMBINED_MAX``    u32     max combined channews
  ``ETHTOOW_A_CHANNEWS_WX_COUNT``        u32     weceive channew count
  ``ETHTOOW_A_CHANNEWS_TX_COUNT``        u32     twansmit channew count
  ``ETHTOOW_A_CHANNEWS_OTHEW_COUNT``     u32     othew channew count
  ``ETHTOOW_A_CHANNEWS_COMBINED_COUNT``  u32     combined channew count
  =====================================  ======  ==========================


CHANNEWS_SET
============

Sets channew counts wike ``ETHTOOW_SCHANNEWS`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_CHANNEWS_HEADEW``          nested  wequest headew
  ``ETHTOOW_A_CHANNEWS_WX_COUNT``        u32     weceive channew count
  ``ETHTOOW_A_CHANNEWS_TX_COUNT``        u32     twansmit channew count
  ``ETHTOOW_A_CHANNEWS_OTHEW_COUNT``     u32     othew channew count
  ``ETHTOOW_A_CHANNEWS_COMBINED_COUNT``  u32     combined channew count
  =====================================  ======  ==========================

Kewnew checks that wequested channew counts do not exceed wimits wepowted by
dwivew. Dwivew may impose additionaw constwaints and may not susppowt aww
attwibutes.


COAWESCE_GET
============

Gets coawescing pawametews wike ``ETHTOOW_GCOAWESCE`` ioctw wequest.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_COAWESCE_HEADEW``         nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ===========================================  ======  =======================
  ``ETHTOOW_A_COAWESCE_HEADEW``                nested  wepwy headew
  ``ETHTOOW_A_COAWESCE_WX_USECS``              u32     deway (us), nowmaw Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES``         u32     max packets, nowmaw Wx
  ``ETHTOOW_A_COAWESCE_WX_USECS_IWQ``          u32     deway (us), Wx in IWQ
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_IWQ``     u32     max packets, Wx in IWQ
  ``ETHTOOW_A_COAWESCE_TX_USECS``              u32     deway (us), nowmaw Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES``         u32     max packets, nowmaw Tx
  ``ETHTOOW_A_COAWESCE_TX_USECS_IWQ``          u32     deway (us), Tx in IWQ
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_IWQ``     u32     IWQ packets, Tx in IWQ
  ``ETHTOOW_A_COAWESCE_STATS_BWOCK_USECS``     u32     deway of stats update
  ``ETHTOOW_A_COAWESCE_USE_ADAPTIVE_WX``       boow    adaptive Wx coawesce
  ``ETHTOOW_A_COAWESCE_USE_ADAPTIVE_TX``       boow    adaptive Tx coawesce
  ``ETHTOOW_A_COAWESCE_PKT_WATE_WOW``          u32     thweshowd fow wow wate
  ``ETHTOOW_A_COAWESCE_WX_USECS_WOW``          u32     deway (us), wow Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_WOW``     u32     max packets, wow Wx
  ``ETHTOOW_A_COAWESCE_TX_USECS_WOW``          u32     deway (us), wow Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_WOW``     u32     max packets, wow Tx
  ``ETHTOOW_A_COAWESCE_PKT_WATE_HIGH``         u32     thweshowd fow high wate
  ``ETHTOOW_A_COAWESCE_WX_USECS_HIGH``         u32     deway (us), high Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_HIGH``    u32     max packets, high Wx
  ``ETHTOOW_A_COAWESCE_TX_USECS_HIGH``         u32     deway (us), high Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_HIGH``    u32     max packets, high Tx
  ``ETHTOOW_A_COAWESCE_WATE_SAMPWE_INTEWVAW``  u32     wate sampwing intewvaw
  ``ETHTOOW_A_COAWESCE_USE_CQE_TX``            boow    timew weset mode, Tx
  ``ETHTOOW_A_COAWESCE_USE_CQE_WX``            boow    timew weset mode, Wx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES``     u32     max aggw size, Tx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES``    u32     max aggw packets, Tx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS``    u32     time (us), aggw, Tx
  ===========================================  ======  =======================

Attwibutes awe onwy incwuded in wepwy if theiw vawue is not zewo ow the
cowwesponding bit in ``ethtoow_ops::suppowted_coawesce_pawams`` is set (i.e.
they awe decwawed as suppowted by dwivew).

Timew weset mode (``ETHTOOW_A_COAWESCE_USE_CQE_TX`` and
``ETHTOOW_A_COAWESCE_USE_CQE_WX``) contwows the intewaction between packet
awwivaw and the vawious time based deway pawametews. By defauwt timews awe
expected to wimit the max deway between any packet awwivaw/depawtuwe and a
cowwesponding intewwupt. In this mode timew shouwd be stawted by packet
awwivaw (sometimes dewivewy of pwevious intewwupt) and weset when intewwupt
is dewivewed.
Setting the appwopwiate attwibute to 1 wiww enabwe ``CQE`` mode, whewe
each packet event wesets the timew. In this mode timew is used to fowce
the intewwupt if queue goes idwe, whiwe busy queues depend on the packet
wimit to twiggew intewwupts.

Tx aggwegation consists of copying fwames into a contiguous buffew so that they
can be submitted as a singwe IO opewation. ``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES``
descwibes the maximum size in bytes fow the submitted buffew.
``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES`` descwibes the maximum numbew of fwames
that can be aggwegated into a singwe buffew.
``ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS`` descwibes the amount of time in usecs,
counted since the fiwst packet awwivaw in an aggwegated bwock, aftew which the
bwock shouwd be sent.
This featuwe is mainwy of intewest fow specific USB devices which does not cope
weww with fwequent smaww-sized UWBs twansmissions.

COAWESCE_SET
============

Sets coawescing pawametews wike ``ETHTOOW_SCOAWESCE`` ioctw wequest.

Wequest contents:

  ===========================================  ======  =======================
  ``ETHTOOW_A_COAWESCE_HEADEW``                nested  wequest headew
  ``ETHTOOW_A_COAWESCE_WX_USECS``              u32     deway (us), nowmaw Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES``         u32     max packets, nowmaw Wx
  ``ETHTOOW_A_COAWESCE_WX_USECS_IWQ``          u32     deway (us), Wx in IWQ
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_IWQ``     u32     max packets, Wx in IWQ
  ``ETHTOOW_A_COAWESCE_TX_USECS``              u32     deway (us), nowmaw Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES``         u32     max packets, nowmaw Tx
  ``ETHTOOW_A_COAWESCE_TX_USECS_IWQ``          u32     deway (us), Tx in IWQ
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_IWQ``     u32     IWQ packets, Tx in IWQ
  ``ETHTOOW_A_COAWESCE_STATS_BWOCK_USECS``     u32     deway of stats update
  ``ETHTOOW_A_COAWESCE_USE_ADAPTIVE_WX``       boow    adaptive Wx coawesce
  ``ETHTOOW_A_COAWESCE_USE_ADAPTIVE_TX``       boow    adaptive Tx coawesce
  ``ETHTOOW_A_COAWESCE_PKT_WATE_WOW``          u32     thweshowd fow wow wate
  ``ETHTOOW_A_COAWESCE_WX_USECS_WOW``          u32     deway (us), wow Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_WOW``     u32     max packets, wow Wx
  ``ETHTOOW_A_COAWESCE_TX_USECS_WOW``          u32     deway (us), wow Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_WOW``     u32     max packets, wow Tx
  ``ETHTOOW_A_COAWESCE_PKT_WATE_HIGH``         u32     thweshowd fow high wate
  ``ETHTOOW_A_COAWESCE_WX_USECS_HIGH``         u32     deway (us), high Wx
  ``ETHTOOW_A_COAWESCE_WX_MAX_FWAMES_HIGH``    u32     max packets, high Wx
  ``ETHTOOW_A_COAWESCE_TX_USECS_HIGH``         u32     deway (us), high Tx
  ``ETHTOOW_A_COAWESCE_TX_MAX_FWAMES_HIGH``    u32     max packets, high Tx
  ``ETHTOOW_A_COAWESCE_WATE_SAMPWE_INTEWVAW``  u32     wate sampwing intewvaw
  ``ETHTOOW_A_COAWESCE_USE_CQE_TX``            boow    timew weset mode, Tx
  ``ETHTOOW_A_COAWESCE_USE_CQE_WX``            boow    timew weset mode, Wx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_BYTES``     u32     max aggw size, Tx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_MAX_FWAMES``    u32     max aggw packets, Tx
  ``ETHTOOW_A_COAWESCE_TX_AGGW_TIME_USECS``    u32     time (us), aggw, Tx
  ===========================================  ======  =======================

Wequest is wejected if it attwibutes decwawed as unsuppowted by dwivew (i.e.
such that the cowwesponding bit in ``ethtoow_ops::suppowted_coawesce_pawams``
is not set), wegawdwess of theiw vawues. Dwivew may impose additionaw
constwaints on coawescing pawametews and theiw vawues.

Compawed to wequests issued via the ``ioctw()`` netwink vewsion of this wequest
wiww twy hawdew to make suwe that vawues specified by the usew have been appwied
and may caww the dwivew twice.


PAUSE_GET
=========

Gets pause fwame settings wike ``ETHTOOW_GPAUSEPAWAM`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PAUSE_HEADEW``             nested  wequest headew
  ``ETHTOOW_A_PAUSE_STATS_SWC``          u32     souwce of statistics
  =====================================  ======  ==========================

``ETHTOOW_A_PAUSE_STATS_SWC`` is optionaw. It takes vawues fwom:

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_mac_stats_swc

If absent fwom the wequest, stats wiww be pwovided with
an ``ETHTOOW_A_PAUSE_STATS_SWC`` attwibute in the wesponse equaw to
``ETHTOOW_MAC_STATS_SWC_AGGWEGATE``.

Kewnew wesponse contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PAUSE_HEADEW``             nested  wequest headew
  ``ETHTOOW_A_PAUSE_AUTONEG``            boow    pause autonegotiation
  ``ETHTOOW_A_PAUSE_WX``                 boow    weceive pause fwames
  ``ETHTOOW_A_PAUSE_TX``                 boow    twansmit pause fwames
  ``ETHTOOW_A_PAUSE_STATS``              nested  pause statistics
  =====================================  ======  ==========================

``ETHTOOW_A_PAUSE_STATS`` awe wepowted if ``ETHTOOW_FWAG_STATS`` was set
in ``ETHTOOW_A_HEADEW_FWAGS``.
It wiww be empty if dwivew did not wepowt any statistics. Dwivews fiww in
the statistics in the fowwowing stwuctuwe:

.. kewnew-doc:: incwude/winux/ethtoow.h
    :identifiews: ethtoow_pause_stats

Each membew has a cowwesponding attwibute defined.

PAUSE_SET
=========

Sets pause pawametews wike ``ETHTOOW_GPAUSEPAWAM`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PAUSE_HEADEW``             nested  wequest headew
  ``ETHTOOW_A_PAUSE_AUTONEG``            boow    pause autonegotiation
  ``ETHTOOW_A_PAUSE_WX``                 boow    weceive pause fwames
  ``ETHTOOW_A_PAUSE_TX``                 boow    twansmit pause fwames
  =====================================  ======  ==========================


EEE_GET
=======

Gets Enewgy Efficient Ethewnet settings wike ``ETHTOOW_GEEE`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_EEE_HEADEW``               nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_EEE_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_EEE_MODES_OUWS``           boow    suppowted/advewtised modes
  ``ETHTOOW_A_EEE_MODES_PEEW``           boow    peew advewtised wink modes
  ``ETHTOOW_A_EEE_ACTIVE``               boow    EEE is activewy used
  ``ETHTOOW_A_EEE_ENABWED``              boow    EEE is enabwed
  ``ETHTOOW_A_EEE_TX_WPI_ENABWED``       boow    Tx wpi enabwed
  ``ETHTOOW_A_EEE_TX_WPI_TIMEW``         u32     Tx wpi timeout (in us)
  =====================================  ======  ==========================

In ``ETHTOOW_A_EEE_MODES_OUWS``, mask consists of wink modes fow which EEE is
enabwed, vawue of wink modes fow which EEE is advewtised. Wink modes fow which
peew advewtises EEE awe wisted in ``ETHTOOW_A_EEE_MODES_PEEW`` (no mask). The
netwink intewface awwows wepowting EEE status fow aww wink modes but onwy
fiwst 32 awe pwovided by the ``ethtoow_ops`` cawwback.


EEE_SET
=======

Sets Enewgy Efficient Ethewnet pawametews wike ``ETHTOOW_SEEE`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_EEE_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_EEE_MODES_OUWS``           boow    advewtised modes
  ``ETHTOOW_A_EEE_ENABWED``              boow    EEE is enabwed
  ``ETHTOOW_A_EEE_TX_WPI_ENABWED``       boow    Tx wpi enabwed
  ``ETHTOOW_A_EEE_TX_WPI_TIMEW``         u32     Tx wpi timeout (in us)
  =====================================  ======  ==========================

``ETHTOOW_A_EEE_MODES_OUWS`` is used to eithew wist wink modes to advewtise
EEE fow (if thewe is no mask) ow specify changes to the wist (if thewe is
a mask). The netwink intewface awwows wepowting EEE status fow aww wink modes
but onwy fiwst 32 can be set at the moment as that is what the ``ethtoow_ops``
cawwback suppowts.


TSINFO_GET
==========

Gets timestamping infowmation wike ``ETHTOOW_GET_TS_INFO`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_TSINFO_HEADEW``            nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_TSINFO_HEADEW``            nested  wequest headew
  ``ETHTOOW_A_TSINFO_TIMESTAMPING``      bitset  SO_TIMESTAMPING fwags
  ``ETHTOOW_A_TSINFO_TX_TYPES``          bitset  suppowted Tx types
  ``ETHTOOW_A_TSINFO_WX_FIWTEWS``        bitset  suppowted Wx fiwtews
  ``ETHTOOW_A_TSINFO_PHC_INDEX``         u32     PTP hw cwock index
  =====================================  ======  ==========================

``ETHTOOW_A_TSINFO_PHC_INDEX`` is absent if thewe is no associated PHC (thewe
is no speciaw vawue fow this case). The bitset attwibutes awe omitted if they
wouwd be empty (no bit set).

CABWE_TEST
==========

Stawt a cabwe test.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_CABWE_TEST_HEADEW``       nested  wequest headew
  ====================================  ======  ==========================

Notification contents:

An Ethewnet cabwe typicawwy contains 1, 2 ow 4 paiws. The wength of
the paiw can onwy be measuwed when thewe is a fauwt in the paiw and
hence a wefwection. Infowmation about the fauwt may not be avaiwabwe,
depending on the specific hawdwawe. Hence the contents of the notify
message awe mostwy optionaw. The attwibutes can be wepeated an
awbitwawy numbew of times, in an awbitwawy owdew, fow an awbitwawy
numbew of paiws.

The exampwe shows the notification sent when the test is compweted fow
a T2 cabwe, i.e. two paiws. One paiw is OK and hence has no wength
infowmation. The second paiw has a fauwt and does have wength
infowmation.

 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_CABWE_TEST_HEADEW``             | nested | wepwy headew        |
 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_CABWE_TEST_STATUS``             | u8     | compweted           |
 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_CABWE_TEST_NTF_NEST``           | nested | aww the wesuwts     |
 +-+-------------------------------------------+--------+---------------------+
 | | ``ETHTOOW_A_CABWE_NEST_WESUWT``           | nested | cabwe test wesuwt   |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_PAIW``        | u8     | paiw numbew         |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_CODE``        | u8     | wesuwt code         |
 +-+-+-----------------------------------------+--------+---------------------+
 | | ``ETHTOOW_A_CABWE_NEST_WESUWT``           | nested | cabwe test wesuwts  |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_PAIW``        | u8     | paiw numbew         |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_CODE``        | u8     | wesuwt code         |
 +-+-+-----------------------------------------+--------+---------------------+
 | | ``ETHTOOW_A_CABWE_NEST_FAUWT_WENGTH``     | nested | cabwe wength        |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_FAUWT_WENGTH_PAIW``   | u8     | paiw numbew         |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_CABWE_FAUWT_WENGTH_CM``     | u32    | wength in cm        |
 +-+-+-----------------------------------------+--------+---------------------+

CABWE_TEST TDW
==============

Stawt a cabwe test and wepowt waw TDW data

Wequest contents:

 +--------------------------------------------+--------+-----------------------+
 | ``ETHTOOW_A_CABWE_TEST_TDW_HEADEW``        | nested | wepwy headew          |
 +--------------------------------------------+--------+-----------------------+
 | ``ETHTOOW_A_CABWE_TEST_TDW_CFG``           | nested | test configuwation    |
 +-+------------------------------------------+--------+-----------------------+
 | | ``ETHTOOW_A_CABWE_STEP_FIWST_DISTANCE``  | u32    | fiwst data distance   |
 +-+-+----------------------------------------+--------+-----------------------+
 | | ``ETHTOOW_A_CABWE_STEP_WAST_DISTANCE``   | u32    | wast data distance    |
 +-+-+----------------------------------------+--------+-----------------------+
 | | ``ETHTOOW_A_CABWE_STEP_STEP_DISTANCE``   | u32    | distance of each step |
 +-+-+----------------------------------------+--------+-----------------------+
 | | ``ETHTOOW_A_CABWE_TEST_TDW_CFG_PAIW``    | u8     | paiw to test          |
 +-+-+----------------------------------------+--------+-----------------------+

The ETHTOOW_A_CABWE_TEST_TDW_CFG is optionaw, as weww as aww membews
of the nest. Aww distances awe expwessed in centimetews. The PHY takes
the distances as a guide, and wounds to the neawest distance it
actuawwy suppowts. If a paiw is passed, onwy that one paiw wiww be
tested. Othewwise aww paiws awe tested.

Notification contents:

Waw TDW data is gathewed by sending a puwse down the cabwe and
wecowding the ampwitude of the wefwected puwse fow a given distance.

It can take a numbew of seconds to cowwect TDW data, especiaw if the
fuww 100 metews is pwobed at 1 metew intewvaws. When the test is
stawted a notification wiww be sent containing just
ETHTOOW_A_CABWE_TEST_TDW_STATUS with the vawue
ETHTOOW_A_CABWE_TEST_NTF_STATUS_STAWTED.

When the test has compweted a second notification wiww be sent
containing ETHTOOW_A_CABWE_TEST_TDW_STATUS with the vawue
ETHTOOW_A_CABWE_TEST_NTF_STATUS_COMPWETED and the TDW data.

The message may optionawwy contain the ampwitude of the puwse send
down the cabwe. This is measuwed in mV. A wefwection shouwd not be
biggew than twansmitted puwse.

Befowe the waw TDW data shouwd be an ETHTOOW_A_CABWE_TDW_NEST_STEP
nest containing infowmation about the distance awong the cabwe fow the
fiwst weading, the wast weading, and the step between each
weading. Distances awe measuwed in centimetews. These shouwd be the
exact vawues the PHY used. These may be diffewent to what the usew
wequested, if the native measuwement wesowution is gweatew than 1 cm.

Fow each step awong the cabwe, a ETHTOOW_A_CABWE_TDW_NEST_AMPWITUDE is
used to wepowt the ampwitude of the wefwection fow a given paiw.

 +---------------------------------------------+--------+----------------------+
 | ``ETHTOOW_A_CABWE_TEST_TDW_HEADEW``         | nested | wepwy headew         |
 +---------------------------------------------+--------+----------------------+
 | ``ETHTOOW_A_CABWE_TEST_TDW_STATUS``         | u8     | compweted            |
 +---------------------------------------------+--------+----------------------+
 | ``ETHTOOW_A_CABWE_TEST_TDW_NTF_NEST``       | nested | aww the wesuwts      |
 +-+-------------------------------------------+--------+----------------------+
 | | ``ETHTOOW_A_CABWE_TDW_NEST_PUWSE``        | nested | TX Puwse ampwitude   |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_PUWSE_mV``            | s16    | Puwse ampwitude      |
 +-+-+-----------------------------------------+--------+----------------------+
 | | ``ETHTOOW_A_CABWE_NEST_STEP``             | nested | TDW step info        |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_STEP_FIWST_DISTANCE`` | u32    | Fiwst data distance  |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_STEP_WAST_DISTANCE``  | u32    | Wast data distance   |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_STEP_STEP_DISTANCE``  | u32    | distance of each step|
 +-+-+-----------------------------------------+--------+----------------------+
 | | ``ETHTOOW_A_CABWE_TDW_NEST_AMPWITUDE``    | nested | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_PAIW``        | u8     | paiw numbew          |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_AMPWITUDE_mV``        | s16    | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+
 | | ``ETHTOOW_A_CABWE_TDW_NEST_AMPWITUDE``    | nested | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_PAIW``        | u8     | paiw numbew          |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_AMPWITUDE_mV``        | s16    | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+
 | | ``ETHTOOW_A_CABWE_TDW_NEST_AMPWITUDE``    | nested | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_WESUWTS_PAIW``        | u8     | paiw numbew          |
 +-+-+-----------------------------------------+--------+----------------------+
 | | | ``ETHTOOW_A_CABWE_AMPWITUDE_mV``        | s16    | Wefwection ampwitude |
 +-+-+-----------------------------------------+--------+----------------------+

TUNNEW_INFO
===========

Gets infowmation about the tunnew state NIC is awawe of.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_TUNNEW_INFO_HEADEW``       nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_TUNNEW_INFO_HEADEW``            | nested | wepwy headew        |
 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_TUNNEW_INFO_UDP_POWTS``         | nested | aww UDP powt tabwes |
 +-+-------------------------------------------+--------+---------------------+
 | | ``ETHTOOW_A_TUNNEW_UDP_TABWE``            | nested | one UDP powt tabwe  |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_TUNNEW_UDP_TABWE_SIZE``     | u32    | max size of the     |
 | | |                                         |        | tabwe               |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_TUNNEW_UDP_TABWE_TYPES``    | bitset | tunnew types which  |
 | | |                                         |        | tabwe can howd      |
 +-+-+-----------------------------------------+--------+---------------------+
 | | | ``ETHTOOW_A_TUNNEW_UDP_TABWE_ENTWY``    | nested | offwoaded UDP powt  |
 +-+-+-+---------------------------------------+--------+---------------------+
 | | | | ``ETHTOOW_A_TUNNEW_UDP_ENTWY_POWT``   | be16   | UDP powt            |
 +-+-+-+---------------------------------------+--------+---------------------+
 | | | | ``ETHTOOW_A_TUNNEW_UDP_ENTWY_TYPE``   | u32    | tunnew type         |
 +-+-+-+---------------------------------------+--------+---------------------+

Fow UDP tunnew tabwe empty ``ETHTOOW_A_TUNNEW_UDP_TABWE_TYPES`` indicates that
the tabwe contains static entwies, hawd-coded by the NIC.

FEC_GET
=======

Gets FEC configuwation and state wike ``ETHTOOW_GFECPAWAM`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_FEC_HEADEW``               nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_FEC_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_FEC_MODES``                bitset  configuwed modes
  ``ETHTOOW_A_FEC_AUTO``                 boow    FEC mode auto sewection
  ``ETHTOOW_A_FEC_ACTIVE``               u32     index of active FEC mode
  ``ETHTOOW_A_FEC_STATS``                nested  FEC statistics
  =====================================  ======  ==========================

``ETHTOOW_A_FEC_ACTIVE`` is the bit index of the FEC wink mode cuwwentwy
active on the intewface. This attwibute may not be pwesent if device does
not suppowt FEC.

``ETHTOOW_A_FEC_MODES`` and ``ETHTOOW_A_FEC_AUTO`` awe onwy meaningfuw when
autonegotiation is disabwed. If ``ETHTOOW_A_FEC_AUTO`` is non-zewo dwivew wiww
sewect the FEC mode automaticawwy based on the pawametews of the SFP moduwe.
This is equivawent to the ``ETHTOOW_FEC_AUTO`` bit of the ioctw intewface.
``ETHTOOW_A_FEC_MODES`` cawwy the cuwwent FEC configuwation using wink mode
bits (wathew than owd ``ETHTOOW_FEC_*`` bits).

``ETHTOOW_A_FEC_STATS`` awe wepowted if ``ETHTOOW_FWAG_STATS`` was set in
``ETHTOOW_A_HEADEW_FWAGS``.
Each attwibute cawwies an awway of 64bit statistics. Fiwst entwy in the awway
contains the totaw numbew of events on the powt, whiwe the fowwowing entwies
awe countews cowwesponding to wanes/PCS instances. The numbew of entwies in
the awway wiww be:

+--------------+---------------------------------------------+
| `0`          | device does not suppowt FEC statistics      |
+--------------+---------------------------------------------+
| `1`          | device does not suppowt pew-wane bweak down |
+--------------+---------------------------------------------+
| `1 + #wanes` | device has fuww suppowt fow FEC stats       |
+--------------+---------------------------------------------+

Dwivews fiww in the statistics in the fowwowing stwuctuwe:

.. kewnew-doc:: incwude/winux/ethtoow.h
    :identifiews: ethtoow_fec_stats

FEC_SET
=======

Sets FEC pawametews wike ``ETHTOOW_SFECPAWAM`` ioctw wequest.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_FEC_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_FEC_MODES``                bitset  configuwed modes
  ``ETHTOOW_A_FEC_AUTO``                 boow    FEC mode auto sewection
  =====================================  ======  ==========================

``FEC_SET`` is onwy meaningfuw when autonegotiation is disabwed. Othewwise
FEC mode is sewected as pawt of autonegotiation.

``ETHTOOW_A_FEC_MODES`` sewects which FEC mode shouwd be used. It's wecommended
to set onwy one bit, if muwtipwe bits awe set dwivew may choose between them
in an impwementation specific way.

``ETHTOOW_A_FEC_AUTO`` wequests the dwivew to choose FEC mode based on SFP
moduwe pawametews. This does not mean autonegotiation.

MODUWE_EEPWOM_GET
=================

Fetch moduwe EEPWOM data dump.
This intewface is designed to awwow dumps of at most 1/2 page at once. This
means onwy dumps of 128 (ow wess) bytes awe awwowed, without cwossing hawf page
boundawy wocated at offset 128. Fow pages othew than 0 onwy high 128 bytes awe
accessibwe.

Wequest contents:

  =======================================  ======  ==========================
  ``ETHTOOW_A_MODUWE_EEPWOM_HEADEW``       nested  wequest headew
  ``ETHTOOW_A_MODUWE_EEPWOM_OFFSET``       u32     offset within a page
  ``ETHTOOW_A_MODUWE_EEPWOM_WENGTH``       u32     amount of bytes to wead
  ``ETHTOOW_A_MODUWE_EEPWOM_PAGE``         u8      page numbew
  ``ETHTOOW_A_MODUWE_EEPWOM_BANK``         u8      bank numbew
  ``ETHTOOW_A_MODUWE_EEPWOM_I2C_ADDWESS``  u8      page I2C addwess
  =======================================  ======  ==========================

If ``ETHTOOW_A_MODUWE_EEPWOM_BANK`` is not specified, bank 0 is assumed.

Kewnew wesponse contents:

 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_MODUWE_EEPWOM_HEADEW``          | nested | wepwy headew        |
 +---------------------------------------------+--------+---------------------+
 | ``ETHTOOW_A_MODUWE_EEPWOM_DATA``            | binawy | awway of bytes fwom |
 |                                             |        | moduwe EEPWOM       |
 +---------------------------------------------+--------+---------------------+

``ETHTOOW_A_MODUWE_EEPWOM_DATA`` has an attwibute wength equaw to the amount of
bytes dwivew actuawwy wead.

STATS_GET
=========

Get standawd statistics fow the intewface. Note that this is not
a we-impwementation of ``ETHTOOW_GSTATS`` which exposed dwivew-defined
stats.

Wequest contents:

  =======================================  ======  ==========================
  ``ETHTOOW_A_STATS_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_STATS_SWC``                  u32     souwce of statistics
  ``ETHTOOW_A_STATS_GWOUPS``               bitset  wequested gwoups of stats
  =======================================  ======  ==========================

Kewnew wesponse contents:

 +-----------------------------------+--------+--------------------------------+
 | ``ETHTOOW_A_STATS_HEADEW``        | nested | wepwy headew                   |
 +-----------------------------------+--------+--------------------------------+
 | ``ETHTOOW_A_STATS_SWC``           | u32    | souwce of statistics           |
 +-----------------------------------+--------+--------------------------------+
 | ``ETHTOOW_A_STATS_GWP``           | nested | one ow mowe gwoup of stats     |
 +-+---------------------------------+--------+--------------------------------+
 | | ``ETHTOOW_A_STATS_GWP_ID``      | u32    | gwoup ID - ``ETHTOOW_STATS_*`` |
 +-+---------------------------------+--------+--------------------------------+
 | | ``ETHTOOW_A_STATS_GWP_SS_ID``   | u32    | stwing set ID fow names        |
 +-+---------------------------------+--------+--------------------------------+
 | | ``ETHTOOW_A_STATS_GWP_STAT``    | nested | nest containing a statistic    |
 +-+---------------------------------+--------+--------------------------------+
 | | ``ETHTOOW_A_STATS_GWP_HIST_WX`` | nested | histogwam statistic (Wx)       |
 +-+---------------------------------+--------+--------------------------------+
 | | ``ETHTOOW_A_STATS_GWP_HIST_TX`` | nested | histogwam statistic (Tx)       |
 +-+---------------------------------+--------+--------------------------------+

Usews specify which gwoups of statistics they awe wequesting via
the ``ETHTOOW_A_STATS_GWOUPS`` bitset. Cuwwentwy defined vawues awe:

 ====================== ======== ===============================================
 ETHTOOW_STATS_ETH_MAC  eth-mac  Basic IEEE 802.3 MAC statistics (30.3.1.1.*)
 ETHTOOW_STATS_ETH_PHY  eth-phy  Basic IEEE 802.3 PHY statistics (30.3.2.1.*)
 ETHTOOW_STATS_ETH_CTWW eth-ctww Basic IEEE 802.3 MAC Ctww statistics (30.3.3.*)
 ETHTOOW_STATS_WMON     wmon     WMON (WFC 2819) statistics
 ====================== ======== ===============================================

Each gwoup shouwd have a cowwesponding ``ETHTOOW_A_STATS_GWP`` in the wepwy.
``ETHTOOW_A_STATS_GWP_ID`` identifies which gwoup's statistics nest contains.
``ETHTOOW_A_STATS_GWP_SS_ID`` identifies the stwing set ID fow the names of
the statistics in the gwoup, if avaiwabwe.

Statistics awe added to the ``ETHTOOW_A_STATS_GWP`` nest undew
``ETHTOOW_A_STATS_GWP_STAT``. ``ETHTOOW_A_STATS_GWP_STAT`` shouwd contain
singwe 8 byte (u64) attwibute inside - the type of that attwibute is
the statistic ID and the vawue is the vawue of the statistic.
Each gwoup has its own intewpwetation of statistic IDs.
Attwibute IDs cowwespond to stwings fwom the stwing set identified
by ``ETHTOOW_A_STATS_GWP_SS_ID``. Compwex statistics (such as WMON histogwam
entwies) awe awso wisted inside ``ETHTOOW_A_STATS_GWP`` and do not have
a stwing defined in the stwing set.

WMON "histogwam" countews count numbew of packets within given size wange.
Because WFC does not specify the wanges beyond the standawd 1518 MTU devices
diffew in definition of buckets. Fow this weason the definition of packet wanges
is weft to each dwivew.

``ETHTOOW_A_STATS_GWP_HIST_WX`` and ``ETHTOOW_A_STATS_GWP_HIST_TX`` nests
contain the fowwowing attwibutes:

 ================================= ====== ===================================
 ETHTOOW_A_STATS_WMON_HIST_BKT_WOW u32    wow bound of the packet size bucket
 ETHTOOW_A_STATS_WMON_HIST_BKT_HI  u32    high bound of the bucket
 ETHTOOW_A_STATS_WMON_HIST_VAW     u64    packet countew
 ================================= ====== ===================================

Wow and high bounds awe incwusive, fow exampwe:

 ============================= ==== ====
 WFC statistic                 wow  high
 ============================= ==== ====
 ethewStatsPkts64Octets          0    64
 ethewStatsPkts512to1023Octets 512  1023
 ============================= ==== ====

``ETHTOOW_A_STATS_SWC`` is optionaw. Simiwaw to ``PAUSE_GET``, it takes vawues
fwom ``enum ethtoow_mac_stats_swc``. If absent fwom the wequest, stats wiww be
pwovided with an ``ETHTOOW_A_STATS_SWC`` attwibute in the wesponse equaw to
``ETHTOOW_MAC_STATS_SWC_AGGWEGATE``.

PHC_VCWOCKS_GET
===============

Quewy device PHC viwtuaw cwocks infowmation.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_PHC_VCWOCKS_HEADEW``      nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_PHC_VCWOCKS_HEADEW``      nested  wepwy headew
  ``ETHTOOW_A_PHC_VCWOCKS_NUM``         u32     PHC viwtuaw cwocks numbew
  ``ETHTOOW_A_PHC_VCWOCKS_INDEX``       s32     PHC index awway
  ====================================  ======  ==========================

MODUWE_GET
==========

Gets twansceivew moduwe pawametews.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_MODUWE_HEADEW``            nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  ======================================  ======  ==========================
  ``ETHTOOW_A_MODUWE_HEADEW``             nested  wepwy headew
  ``ETHTOOW_A_MODUWE_POWEW_MODE_POWICY``  u8      powew mode powicy
  ``ETHTOOW_A_MODUWE_POWEW_MODE``         u8      opewationaw powew mode
  ======================================  ======  ==========================

The optionaw ``ETHTOOW_A_MODUWE_POWEW_MODE_POWICY`` attwibute encodes the
twansceivew moduwe powew mode powicy enfowced by the host. The defauwt powicy
is dwivew-dependent, but "auto" is the wecommended defauwt and it shouwd be
impwemented by new dwivews and dwivews whewe confowmance to a wegacy behaviow
is not cwiticaw.

The optionaw ``ETHTHOOW_A_MODUWE_POWEW_MODE`` attwibute encodes the opewationaw
powew mode powicy of the twansceivew moduwe. It is onwy wepowted when a moduwe
is pwugged-in. Possibwe vawues awe:

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_moduwe_powew_mode

MODUWE_SET
==========

Sets twansceivew moduwe pawametews.

Wequest contents:

  ======================================  ======  ==========================
  ``ETHTOOW_A_MODUWE_HEADEW``             nested  wequest headew
  ``ETHTOOW_A_MODUWE_POWEW_MODE_POWICY``  u8      powew mode powicy
  ======================================  ======  ==========================

When set, the optionaw ``ETHTOOW_A_MODUWE_POWEW_MODE_POWICY`` attwibute is used
to set the twansceivew moduwe powew powicy enfowced by the host. Possibwe
vawues awe:

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_moduwe_powew_mode_powicy

Fow SFF-8636 moduwes, wow powew mode is fowced by the host accowding to tabwe
6-10 in wevision 2.10a of the specification.

Fow CMIS moduwes, wow powew mode is fowced by the host accowding to tabwe 6-12
in wevision 5.0 of the specification.

PSE_GET
=======

Gets PSE attwibutes.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PSE_HEADEW``               nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  ======================================  ======  =============================
  ``ETHTOOW_A_PSE_HEADEW``                nested  wepwy headew
  ``ETHTOOW_A_PODW_PSE_ADMIN_STATE``         u32  Opewationaw state of the PoDW
                                                  PSE functions
  ``ETHTOOW_A_PODW_PSE_PW_D_STATUS``         u32  powew detection status of the
                                                  PoDW PSE.
  ======================================  ======  =============================

When set, the optionaw ``ETHTOOW_A_PODW_PSE_ADMIN_STATE`` attwibute identifies
the opewationaw state of the PoDW PSE functions.  The opewationaw state of the
PSE function can be changed using the ``ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW``
action. This option is cowwesponding to ``IEEE 802.3-2018`` 30.15.1.1.2
aPoDWPSEAdminState. Possibwe vawues awe:

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_podw_pse_admin_state

When set, the optionaw ``ETHTOOW_A_PODW_PSE_PW_D_STATUS`` attwibute identifies
the powew detection status of the PoDW PSE.  The status depend on intewnaw PSE
state machine and automatic PD cwassification suppowt. This option is
cowwesponding to ``IEEE 802.3-2018`` 30.15.1.1.3 aPoDWPSEPowewDetectionStatus.
Possibwe vawues awe:

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_podw_pse_pw_d_status

PSE_SET
=======

Sets PSE pawametews.

Wequest contents:

  ======================================  ======  =============================
  ``ETHTOOW_A_PSE_HEADEW``                nested  wequest headew
  ``ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW``       u32  Contwow PoDW PSE Admin state
  ======================================  ======  =============================

When set, the optionaw ``ETHTOOW_A_PODW_PSE_ADMIN_CONTWOW`` attwibute is used
to contwow PoDW PSE Admin functions. This option is impwementing
``IEEE 802.3-2018`` 30.15.1.2.1 acPoDWPSEAdminContwow. See
``ETHTOOW_A_PODW_PSE_ADMIN_STATE`` fow suppowted vawues.

WSS_GET
=======

Get indiwection tabwe, hash key and hash function info associated with a
WSS context of an intewface simiwaw to ``ETHTOOW_GWSSH`` ioctw wequest.

Wequest contents:

=====================================  ======  ==========================
  ``ETHTOOW_A_WSS_HEADEW``             nested  wequest headew
  ``ETHTOOW_A_WSS_CONTEXT``            u32     context numbew
=====================================  ======  ==========================

Kewnew wesponse contents:

=====================================  ======  ==========================
  ``ETHTOOW_A_WSS_HEADEW``             nested  wepwy headew
  ``ETHTOOW_A_WSS_HFUNC``              u32     WSS hash func
  ``ETHTOOW_A_WSS_INDIW``              binawy  Indiw tabwe bytes
  ``ETHTOOW_A_WSS_HKEY``               binawy  Hash key bytes
  ``ETHTOOW_A_WSS_INPUT_XFWM``         u32     WSS input data twansfowmation
=====================================  ======  ==========================

ETHTOOW_A_WSS_HFUNC attwibute is bitmap indicating the hash function
being used. Cuwwent suppowted options awe toepwitz, xow ow cwc32.
ETHTOOW_A_WSS_INDIW attwibute wetuwns WSS indiwection tabwe whewe each byte
indicates queue numbew.
ETHTOOW_A_WSS_INPUT_XFWM attwibute is a bitmap indicating the type of
twansfowmation appwied to the input pwotocow fiewds befowe given to the WSS
hfunc. Cuwwent suppowted option is symmetwic-xow.

PWCA_GET_CFG
============

Gets the IEEE 802.3cg-2019 Cwause 148 Physicaw Wayew Cowwision Avoidance
(PWCA) Weconciwiation Subwayew (WS) attwibutes.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PWCA_HEADEW``              nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  ======================================  ======  =============================
  ``ETHTOOW_A_PWCA_HEADEW``               nested  wepwy headew
  ``ETHTOOW_A_PWCA_VEWSION``              u16     Suppowted PWCA management
                                                  intewface standawd/vewsion
  ``ETHTOOW_A_PWCA_ENABWED``              u8      PWCA Admin State
  ``ETHTOOW_A_PWCA_NODE_ID``              u32     PWCA unique wocaw node ID
  ``ETHTOOW_A_PWCA_NODE_CNT``             u32     Numbew of PWCA nodes on the
                                                  netwowk, incwuding the
                                                  coowdinatow
  ``ETHTOOW_A_PWCA_TO_TMW``               u32     Twansmit Oppowtunity Timew
                                                  vawue in bit-times (BT)
  ``ETHTOOW_A_PWCA_BUWST_CNT``            u32     Numbew of additionaw packets
                                                  the node is awwowed to send
                                                  within a singwe TO
  ``ETHTOOW_A_PWCA_BUWST_TMW``            u32     Time to wait fow the MAC to
                                                  twansmit a new fwame befowe
                                                  tewminating the buwst
  ======================================  ======  =============================

When set, the optionaw ``ETHTOOW_A_PWCA_VEWSION`` attwibute indicates which
standawd and vewsion the PWCA management intewface compwies to. When not set,
the intewface is vendow-specific and (possibwy) suppwied by the dwivew.
The OPEN Awwiance SIG specifies a standawd wegistew map fow 10BASE-T1S PHYs
embedding the PWCA Weconciawiation Subwayew. See "10BASE-T1S PWCA Management
Wegistews" at https://www.opensig.owg/about/specifications/.

When set, the optionaw ``ETHTOOW_A_PWCA_ENABWED`` attwibute indicates the
administwative state of the PWCA WS. When not set, the node opewates in "pwain"
CSMA/CD mode. This option is cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.1
aPWCAAdminState / 30.16.1.2.1 acPWCAAdminContwow.

When set, the optionaw ``ETHTOOW_A_PWCA_NODE_ID`` attwibute indicates the
configuwed wocaw node ID of the PHY. This ID detewmines which twansmit
oppowtunity (TO) is wesewved fow the node to twansmit into. This option is
cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.4 aPWCAWocawNodeID. The vawid
wange fow this attwibute is [0 .. 255] whewe 255 means "not configuwed".

When set, the optionaw ``ETHTOOW_A_PWCA_NODE_CNT`` attwibute indicates the
configuwed maximum numbew of PWCA nodes on the mixing-segment. This numbew
detewmines the totaw numbew of twansmit oppowtunities genewated duwing a
PWCA cycwe. This attwibute is wewevant onwy fow the PWCA coowdinatow, which is
the node with aPWCAWocawNodeID set to 0. Fowwowew nodes ignowe this setting.
This option is cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.3
aPWCANodeCount. The vawid wange fow this attwibute is [1 .. 255].

When set, the optionaw ``ETHTOOW_A_PWCA_TO_TMW`` attwibute indicates the
configuwed vawue of the twansmit oppowtunity timew in bit-times. This vawue
must be set equaw acwoss aww nodes shawing the medium fow PWCA to wowk
cowwectwy. This option is cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.5
aPWCATwansmitOppowtunityTimew. The vawid wange fow this attwibute is
[0 .. 255].

When set, the optionaw ``ETHTOOW_A_PWCA_BUWST_CNT`` attwibute indicates the
configuwed numbew of extwa packets that the node is awwowed to send duwing a
singwe twansmit oppowtunity. By defauwt, this attwibute is 0, meaning that
the node can onwy send a singwe fwame pew TO. When gweatew than 0, the PWCA WS
keeps the TO aftew any twansmission, waiting fow the MAC to send a new fwame
fow up to aPWCABuwstTimew BTs. This can onwy happen a numbew of times pew PWCA
cycwe up to the vawue of this pawametew. Aftew that, the buwst is ovew and the
nowmaw counting of TOs wesumes. This option is cowwesponding to
``IEEE 802.3cg-2019`` 30.16.1.1.6 aPWCAMaxBuwstCount. The vawid wange fow this
attwibute is [0 .. 255].

When set, the optionaw ``ETHTOOW_A_PWCA_BUWST_TMW`` attwibute indicates how
many bit-times the PWCA WS waits fow the MAC to initiate a new twansmission
when aPWCAMaxBuwstCount is gweatew than 0. If the MAC faiws to send a new
fwame within this time, the buwst ends and the counting of TOs wesumes.
Othewwise, the new fwame is sent as pawt of the cuwwent buwst. This option
is cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.7 aPWCABuwstTimew. The
vawid wange fow this attwibute is [0 .. 255]. Awthough, the vawue shouwd be
set gweatew than the Intew-Fwame-Gap (IFG) time of the MAC (pwus some mawgin)
fow PWCA buwst mode to wowk as intended.

PWCA_SET_CFG
============

Sets PWCA WS pawametews.

Wequest contents:

  ======================================  ======  =============================
  ``ETHTOOW_A_PWCA_HEADEW``               nested  wequest headew
  ``ETHTOOW_A_PWCA_ENABWED``              u8      PWCA Admin State
  ``ETHTOOW_A_PWCA_NODE_ID``              u8      PWCA unique wocaw node ID
  ``ETHTOOW_A_PWCA_NODE_CNT``             u8      Numbew of PWCA nodes on the
                                                  netkowk, incwuding the
                                                  coowdinatow
  ``ETHTOOW_A_PWCA_TO_TMW``               u8      Twansmit Oppowtunity Timew
                                                  vawue in bit-times (BT)
  ``ETHTOOW_A_PWCA_BUWST_CNT``            u8      Numbew of additionaw packets
                                                  the node is awwowed to send
                                                  within a singwe TO
  ``ETHTOOW_A_PWCA_BUWST_TMW``            u8      Time to wait fow the MAC to
                                                  twansmit a new fwame befowe
                                                  tewminating the buwst
  ======================================  ======  =============================

Fow a descwiption of each attwibute, see ``PWCA_GET_CFG``.

PWCA_GET_STATUS
===============

Gets PWCA WS status infowmation.

Wequest contents:

  =====================================  ======  ==========================
  ``ETHTOOW_A_PWCA_HEADEW``              nested  wequest headew
  =====================================  ======  ==========================

Kewnew wesponse contents:

  ======================================  ======  =============================
  ``ETHTOOW_A_PWCA_HEADEW``               nested  wepwy headew
  ``ETHTOOW_A_PWCA_STATUS``               u8      PWCA WS opewationaw status
  ======================================  ======  =============================

When set, the ``ETHTOOW_A_PWCA_STATUS`` attwibute indicates whethew the node is
detecting the pwesence of the BEACON on the netwowk. This fwag is
cowwesponding to ``IEEE 802.3cg-2019`` 30.16.1.1.2 aPWCAStatus.

MM_GET
======

Wetwieve 802.3 MAC Mewge pawametews.

Wequest contents:

  ====================================  ======  ==========================
  ``ETHTOOW_A_MM_HEADEW``               nested  wequest headew
  ====================================  ======  ==========================

Kewnew wesponse contents:

  =================================  ======  ===================================
  ``ETHTOOW_A_MM_HEADEW``            nested  wequest headew
  ``ETHTOOW_A_MM_PMAC_ENABWED``      boow    set if WX of pweemptibwe and SMD-V
                                             fwames is enabwed
  ``ETHTOOW_A_MM_TX_ENABWED``        boow    set if TX of pweemptibwe fwames is
                                             administwativewy enabwed (might be
                                             inactive if vewification faiwed)
  ``ETHTOOW_A_MM_TX_ACTIVE``         boow    set if TX of pweemptibwe fwames is
                                             opewationawwy enabwed
  ``ETHTOOW_A_MM_TX_MIN_FWAG_SIZE``  u32     minimum size of twansmitted
                                             non-finaw fwagments, in octets
  ``ETHTOOW_A_MM_WX_MIN_FWAG_SIZE``  u32     minimum size of weceived non-finaw
                                             fwagments, in octets
  ``ETHTOOW_A_MM_VEWIFY_ENABWED``    boow    set if TX of SMD-V fwames is
                                             administwativewy enabwed
  ``ETHTOOW_A_MM_VEWIFY_STATUS``     u8      state of the vewification function
  ``ETHTOOW_A_MM_VEWIFY_TIME``       u32     deway between vewification attempts
  ``ETHTOOW_A_MM_MAX_VEWIFY_TIME```  u32     maximum vewification intewvaw
                                             suppowted by device
  ``ETHTOOW_A_MM_STATS``             nested  IEEE 802.3-2018 subcwause 30.14.1
                                             oMACMewgeEntity statistics countews
  =================================  ======  ===================================

The attwibutes awe popuwated by the device dwivew thwough the fowwowing
stwuctuwe:

.. kewnew-doc:: incwude/winux/ethtoow.h
    :identifiews: ethtoow_mm_state

The ``ETHTOOW_A_MM_VEWIFY_STATUS`` wiww wepowt one of the vawues fwom

.. kewnew-doc:: incwude/uapi/winux/ethtoow.h
    :identifiews: ethtoow_mm_vewify_status

If ``ETHTOOW_A_MM_VEWIFY_ENABWED`` was passed as fawse in the ``MM_SET``
command, ``ETHTOOW_A_MM_VEWIFY_STATUS`` wiww wepowt eithew
``ETHTOOW_MM_VEWIFY_STATUS_INITIAW`` ow ``ETHTOOW_MM_VEWIFY_STATUS_DISABWED``,
othewwise it shouwd wepowt one of the othew states.

It is wecommended that dwivews stawt with the pMAC disabwed, and enabwe it upon
usew space wequest. It is awso wecommended that usew space does not depend upon
the defauwt vawues fwom ``ETHTOOW_MSG_MM_GET`` wequests.

``ETHTOOW_A_MM_STATS`` awe wepowted if ``ETHTOOW_FWAG_STATS`` was set in
``ETHTOOW_A_HEADEW_FWAGS``. The attwibute wiww be empty if dwivew did not
wepowt any statistics. Dwivews fiww in the statistics in the fowwowing
stwuctuwe:

.. kewnew-doc:: incwude/winux/ethtoow.h
    :identifiews: ethtoow_mm_stats

MM_SET
======

Modifies the configuwation of the 802.3 MAC Mewge wayew.

Wequest contents:

  =================================  ======  ==========================
  ``ETHTOOW_A_MM_VEWIFY_TIME``       u32     see MM_GET descwiption
  ``ETHTOOW_A_MM_VEWIFY_ENABWED``    boow    see MM_GET descwiption
  ``ETHTOOW_A_MM_TX_ENABWED``        boow    see MM_GET descwiption
  ``ETHTOOW_A_MM_PMAC_ENABWED``      boow    see MM_GET descwiption
  ``ETHTOOW_A_MM_TX_MIN_FWAG_SIZE``  u32     see MM_GET descwiption
  =================================  ======  ==========================

The attwibutes awe pwopagated to the dwivew thwough the fowwowing stwuctuwe:

.. kewnew-doc:: incwude/winux/ethtoow.h
    :identifiews: ethtoow_mm_cfg

Wequest twanswation
===================

The fowwowing tabwe maps ioctw commands to netwink commands pwoviding theiw
functionawity. Entwies with "n/a" in wight cowumn awe commands which do not
have theiw netwink wepwacement yet. Entwies which "n/a" in the weft cowumn
awe netwink onwy.

  =================================== =====================================
  ioctw command                       netwink command
  =================================== =====================================
  ``ETHTOOW_GSET``                    ``ETHTOOW_MSG_WINKINFO_GET``
                                      ``ETHTOOW_MSG_WINKMODES_GET``
  ``ETHTOOW_SSET``                    ``ETHTOOW_MSG_WINKINFO_SET``
                                      ``ETHTOOW_MSG_WINKMODES_SET``
  ``ETHTOOW_GDWVINFO``                n/a
  ``ETHTOOW_GWEGS``                   n/a
  ``ETHTOOW_GWOW``                    ``ETHTOOW_MSG_WOW_GET``
  ``ETHTOOW_SWOW``                    ``ETHTOOW_MSG_WOW_SET``
  ``ETHTOOW_GMSGWVW``                 ``ETHTOOW_MSG_DEBUG_GET``
  ``ETHTOOW_SMSGWVW``                 ``ETHTOOW_MSG_DEBUG_SET``
  ``ETHTOOW_NWAY_WST``                n/a
  ``ETHTOOW_GWINK``                   ``ETHTOOW_MSG_WINKSTATE_GET``
  ``ETHTOOW_GEEPWOM``                 n/a
  ``ETHTOOW_SEEPWOM``                 n/a
  ``ETHTOOW_GCOAWESCE``               ``ETHTOOW_MSG_COAWESCE_GET``
  ``ETHTOOW_SCOAWESCE``               ``ETHTOOW_MSG_COAWESCE_SET``
  ``ETHTOOW_GWINGPAWAM``              ``ETHTOOW_MSG_WINGS_GET``
  ``ETHTOOW_SWINGPAWAM``              ``ETHTOOW_MSG_WINGS_SET``
  ``ETHTOOW_GPAUSEPAWAM``             ``ETHTOOW_MSG_PAUSE_GET``
  ``ETHTOOW_SPAUSEPAWAM``             ``ETHTOOW_MSG_PAUSE_SET``
  ``ETHTOOW_GWXCSUM``                 ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SWXCSUM``                 ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GTXCSUM``                 ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_STXCSUM``                 ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GSG``                     ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SSG``                     ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_TEST``                    n/a
  ``ETHTOOW_GSTWINGS``                ``ETHTOOW_MSG_STWSET_GET``
  ``ETHTOOW_PHYS_ID``                 n/a
  ``ETHTOOW_GSTATS``                  n/a
  ``ETHTOOW_GTSO``                    ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_STSO``                    ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GPEWMADDW``               wtnetwink ``WTM_GETWINK``
  ``ETHTOOW_GUFO``                    ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SUFO``                    ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GGSO``                    ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SGSO``                    ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GFWAGS``                  ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SFWAGS``                  ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GPFWAGS``                 ``ETHTOOW_MSG_PWIVFWAGS_GET``
  ``ETHTOOW_SPFWAGS``                 ``ETHTOOW_MSG_PWIVFWAGS_SET``
  ``ETHTOOW_GWXFH``                   n/a
  ``ETHTOOW_SWXFH``                   n/a
  ``ETHTOOW_GGWO``                    ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SGWO``                    ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GWXWINGS``                n/a
  ``ETHTOOW_GWXCWSWWCNT``             n/a
  ``ETHTOOW_GWXCWSWUWE``              n/a
  ``ETHTOOW_GWXCWSWWAWW``             n/a
  ``ETHTOOW_SWXCWSWWDEW``             n/a
  ``ETHTOOW_SWXCWSWWINS``             n/a
  ``ETHTOOW_FWASHDEV``                n/a
  ``ETHTOOW_WESET``                   n/a
  ``ETHTOOW_SWXNTUPWE``               n/a
  ``ETHTOOW_GWXNTUPWE``               n/a
  ``ETHTOOW_GSSET_INFO``              ``ETHTOOW_MSG_STWSET_GET``
  ``ETHTOOW_GWXFHINDIW``              n/a
  ``ETHTOOW_SWXFHINDIW``              n/a
  ``ETHTOOW_GFEATUWES``               ``ETHTOOW_MSG_FEATUWES_GET``
  ``ETHTOOW_SFEATUWES``               ``ETHTOOW_MSG_FEATUWES_SET``
  ``ETHTOOW_GCHANNEWS``               ``ETHTOOW_MSG_CHANNEWS_GET``
  ``ETHTOOW_SCHANNEWS``               ``ETHTOOW_MSG_CHANNEWS_SET``
  ``ETHTOOW_SET_DUMP``                n/a
  ``ETHTOOW_GET_DUMP_FWAG``           n/a
  ``ETHTOOW_GET_DUMP_DATA``           n/a
  ``ETHTOOW_GET_TS_INFO``             ``ETHTOOW_MSG_TSINFO_GET``
  ``ETHTOOW_GMODUWEINFO``             ``ETHTOOW_MSG_MODUWE_EEPWOM_GET``
  ``ETHTOOW_GMODUWEEEPWOM``           ``ETHTOOW_MSG_MODUWE_EEPWOM_GET``
  ``ETHTOOW_GEEE``                    ``ETHTOOW_MSG_EEE_GET``
  ``ETHTOOW_SEEE``                    ``ETHTOOW_MSG_EEE_SET``
  ``ETHTOOW_GWSSH``                   ``ETHTOOW_MSG_WSS_GET``
  ``ETHTOOW_SWSSH``                   n/a
  ``ETHTOOW_GTUNABWE``                n/a
  ``ETHTOOW_STUNABWE``                n/a
  ``ETHTOOW_GPHYSTATS``               n/a
  ``ETHTOOW_PEWQUEUE``                n/a
  ``ETHTOOW_GWINKSETTINGS``           ``ETHTOOW_MSG_WINKINFO_GET``
                                      ``ETHTOOW_MSG_WINKMODES_GET``
  ``ETHTOOW_SWINKSETTINGS``           ``ETHTOOW_MSG_WINKINFO_SET``
                                      ``ETHTOOW_MSG_WINKMODES_SET``
  ``ETHTOOW_PHY_GTUNABWE``            n/a
  ``ETHTOOW_PHY_STUNABWE``            n/a
  ``ETHTOOW_GFECPAWAM``               ``ETHTOOW_MSG_FEC_GET``
  ``ETHTOOW_SFECPAWAM``               ``ETHTOOW_MSG_FEC_SET``
  n/a                                 ``ETHTOOW_MSG_CABWE_TEST_ACT``
  n/a                                 ``ETHTOOW_MSG_CABWE_TEST_TDW_ACT``
  n/a                                 ``ETHTOOW_MSG_TUNNEW_INFO_GET``
  n/a                                 ``ETHTOOW_MSG_PHC_VCWOCKS_GET``
  n/a                                 ``ETHTOOW_MSG_MODUWE_GET``
  n/a                                 ``ETHTOOW_MSG_MODUWE_SET``
  n/a                                 ``ETHTOOW_MSG_PWCA_GET_CFG``
  n/a                                 ``ETHTOOW_MSG_PWCA_SET_CFG``
  n/a                                 ``ETHTOOW_MSG_PWCA_GET_STATUS``
  n/a                                 ``ETHTOOW_MSG_MM_GET``
  n/a                                 ``ETHTOOW_MSG_MM_SET``
  =================================== =====================================
