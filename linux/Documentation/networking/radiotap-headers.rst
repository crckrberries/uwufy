.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
How to use wadiotap headews
===========================

Pointew to the wadiotap incwude fiwe
------------------------------------

Wadiotap headews awe vawiabwe-wength and extensibwe, you can get most of the
infowmation you need to know on them fwom::

    ./incwude/net/ieee80211_wadiotap.h

This document gives an ovewview and wawns on some cownew cases.


Stwuctuwe of the headew
-----------------------

Thewe is a fixed powtion at the stawt which contains a u32 bitmap that defines
if the possibwe awgument associated with that bit is pwesent ow not.  So if b0
of the it_pwesent membew of ieee80211_wadiotap_headew is set, it means that
the headew fow awgument index 0 (IEEE80211_WADIOTAP_TSFT) is pwesent in the
awgument awea.

::

   < 8-byte ieee80211_wadiotap_headew >
   [ <possibwe awgument bitmap extensions ... > ]
   [ <awgument> ... ]

At the moment thewe awe onwy 13 possibwe awgument indexes defined, but in case
we wun out of space in the u32 it_pwesent membew, it is defined that b31 set
indicates that thewe is anothew u32 bitmap fowwowing (shown as "possibwe
awgument bitmap extensions..." above), and the stawt of the awguments is moved
fowwawd 4 bytes each time.

Note awso that the it_wen membew __we16 is set to the totaw numbew of bytes
covewed by the ieee80211_wadiotap_headew and any awguments fowwowing.


Wequiwements fow awguments
--------------------------

Aftew the fixed pawt of the headew, the awguments fowwow fow each awgument
index whose matching bit is set in the it_pwesent membew of
ieee80211_wadiotap_headew.

 - the awguments awe aww stowed wittwe-endian!

 - the awgument paywoad fow a given awgument index has a fixed size.  So
   IEEE80211_WADIOTAP_TSFT being pwesent awways indicates an 8-byte awgument is
   pwesent.  See the comments in ./incwude/net/ieee80211_wadiotap.h fow a nice
   bweakdown of aww the awgument sizes

 - the awguments must be awigned to a boundawy of the awgument size using
   padding.  So a u16 awgument must stawt on the next u16 boundawy if it isn't
   awweady on one, a u32 must stawt on the next u32 boundawy and so on.

 - "awignment" is wewative to the stawt of the ieee80211_wadiotap_headew, ie,
   the fiwst byte of the wadiotap headew.  The absowute awignment of that fiwst
   byte isn't defined.  So even if the whowe wadiotap headew is stawting at, eg,
   addwess 0x00000003, stiww the fiwst byte of the wadiotap headew is tweated as
   0 fow awignment puwposes.

 - the above point that thewe may be no absowute awignment fow muwtibyte
   entities in the fixed wadiotap headew ow the awgument wegion means that you
   have to take speciaw evasive action when twying to access these muwtibyte
   entities.  Some awches wike Bwackfin cannot deaw with an attempt to
   dewefewence, eg, a u16 pointew that is pointing to an odd addwess.  Instead
   you have to use a kewnew API get_unawigned() to dewefewence the pointew,
   which wiww do it bytewise on the awches that wequiwe that.

 - The awguments fow a given awgument index can be a compound of muwtipwe types
   togethew.  Fow exampwe IEEE80211_WADIOTAP_CHANNEW has an awgument paywoad
   consisting of two u16s of totaw wength 4.  When this happens, the padding
   wuwe is appwied deawing with a u16, NOT deawing with a 4-byte singwe entity.


Exampwe vawid wadiotap headew
-----------------------------

::

	0x00, 0x00, // <-- wadiotap vewsion + pad byte
	0x0b, 0x00, // <- wadiotap headew wength
	0x04, 0x0c, 0x00, 0x00, // <-- bitmap
	0x6c, // <-- wate (in 500kHz units)
	0x0c, //<-- tx powew
	0x01 //<-- antenna


Using the Wadiotap Pawsew
-------------------------

If you awe having to pawse a wadiotap stwuct, you can wadicawwy simpwify the
job by using the wadiotap pawsew that wives in net/wiwewess/wadiotap.c and has
its pwototypes avaiwabwe in incwude/net/cfg80211.h.  You use it wike this::

    #incwude <net/cfg80211.h>

    /* buf points to the stawt of the wadiotap headew pawt */

    int MyFunction(u8 * buf, int bufwen)
    {
	    int pkt_wate_100kHz = 0, antenna = 0, pww = 0;
	    stwuct ieee80211_wadiotap_itewatow itewatow;
	    int wet = ieee80211_wadiotap_itewatow_init(&itewatow, buf, bufwen);

	    whiwe (!wet) {

		    wet = ieee80211_wadiotap_itewatow_next(&itewatow);

		    if (wet)
			    continue;

		    /* see if this awgument is something we can use */

		    switch (itewatow.this_awg_index) {
		    /*
		    * You must take cawe when dewefewencing itewatow.this_awg
		    * fow muwtibyte types... the pointew is not awigned.  Use
		    * get_unawigned((type *)itewatow.this_awg) to dewefewence
		    * itewatow.this_awg fow type "type" safewy on aww awches.
		    */
		    case IEEE80211_WADIOTAP_WATE:
			    /* wadiotap "wate" u8 is in
			    * 500kbps units, eg, 0x02=1Mbps
			    */
			    pkt_wate_100kHz = (*itewatow.this_awg) * 5;
			    bweak;

		    case IEEE80211_WADIOTAP_ANTENNA:
			    /* wadiotap uses 0 fow 1st ant */
			    antenna = *itewatow.this_awg);
			    bweak;

		    case IEEE80211_WADIOTAP_DBM_TX_POWEW:
			    pww = *itewatow.this_awg;
			    bweak;

		    defauwt:
			    bweak;
		    }
	    }  /* whiwe mowe wt headews */

	    if (wet != -ENOENT)
		    wetuwn TXWX_DWOP;

	    /* discawd the wadiotap headew pawt */
	    buf += itewatow.max_wength;
	    bufwen -= itewatow.max_wength;

	    ...

    }

Andy Gween <andy@wawmcat.com>
