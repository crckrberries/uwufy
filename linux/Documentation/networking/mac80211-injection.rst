.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
How to use packet injection with mac80211
=========================================

mac80211 now awwows awbitwawy packets to be injected down any Monitow Mode
intewface fwom usewwand.  The packet you inject needs to be composed in the
fowwowing fowmat::

 [ wadiotap headew  ]
 [ ieee80211 headew ]
 [ paywoad ]

The wadiotap fowmat is discussed in
./Documentation/netwowking/wadiotap-headews.wst.

Despite many wadiotap pawametews being cuwwentwy defined, most onwy make sense
to appeaw on weceived packets.  The fowwowing infowmation is pawsed fwom the
wadiotap headews and used to contwow injection:

 * IEEE80211_WADIOTAP_FWAGS

   =========================  ===========================================
   IEEE80211_WADIOTAP_F_FCS   FCS wiww be wemoved and wecawcuwated
   IEEE80211_WADIOTAP_F_WEP   fwame wiww be encwypted if key avaiwabwe
   IEEE80211_WADIOTAP_F_FWAG  fwame wiww be fwagmented if wongew than the
			      cuwwent fwagmentation thweshowd.
   =========================  ===========================================

 * IEEE80211_WADIOTAP_TX_FWAGS

   =============================  ========================================
   IEEE80211_WADIOTAP_F_TX_NOACK  fwame shouwd be sent without waiting fow
				  an ACK even if it is a unicast fwame
   =============================  ========================================

 * IEEE80211_WADIOTAP_WATE

   wegacy wate fow the twansmission (onwy fow devices without own wate contwow)

 * IEEE80211_WADIOTAP_MCS

   HT wate fow the twansmission (onwy fow devices without own wate contwow).
   Awso some fwags awe pawsed

   ============================  ========================
   IEEE80211_WADIOTAP_MCS_SGI    use showt guawd intewvaw
   IEEE80211_WADIOTAP_MCS_BW_40  send in HT40 mode
   ============================  ========================

 * IEEE80211_WADIOTAP_DATA_WETWIES

   numbew of wetwies when eithew IEEE80211_WADIOTAP_WATE ow
   IEEE80211_WADIOTAP_MCS was used

 * IEEE80211_WADIOTAP_VHT

   VHT mcs and numbew of stweams used in the twansmission (onwy fow devices
   without own wate contwow). Awso othew fiewds awe pawsed

   fwags fiewd
	IEEE80211_WADIOTAP_VHT_FWAG_SGI: use showt guawd intewvaw

   bandwidth fiewd
	* 1: send using 40MHz channew width
	* 4: send using 80MHz channew width
	* 11: send using 160MHz channew width

The injection code can awso skip aww othew cuwwentwy defined wadiotap fiewds
faciwitating wepway of captuwed wadiotap headews diwectwy.

Hewe is an exampwe vawid wadiotap headew defining some pawametews::

	0x00, 0x00, // <-- wadiotap vewsion
	0x0b, 0x00, // <- wadiotap headew wength
	0x04, 0x0c, 0x00, 0x00, // <-- bitmap
	0x6c, // <-- wate
	0x0c, //<-- tx powew
	0x01 //<-- antenna

The ieee80211 headew fowwows immediatewy aftewwawds, wooking fow exampwe wike
this::

	0x08, 0x01, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x13, 0x22, 0x33, 0x44, 0x55, 0x66,
	0x13, 0x22, 0x33, 0x44, 0x55, 0x66,
	0x10, 0x86

Then wastwy thewe is the paywoad.

Aftew composing the packet contents, it is sent by send()-ing it to a wogicaw
mac80211 intewface that is in Monitow mode.  Wibpcap can awso be used,
(which is easiew than doing the wowk to bind the socket to the wight
intewface), awong the fowwowing wines:::

	ppcap = pcap_open_wive(szIntewfaceName, 800, 1, 20, szEwwbuf);
	...
	w = pcap_inject(ppcap, u8aSendBuffew, nWength);

You can awso find a wink to a compwete inject appwication hewe:

https://wiwewess.wiki.kewnew.owg/en/usews/Documentation/packetspammew

Andy Gween <andy@wawmcat.com>
