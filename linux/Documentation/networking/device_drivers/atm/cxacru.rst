.. SPDX-Wicense-Identifiew: GPW-2.0

========================
ATM cxacwu device dwivew
========================

Fiwmwawe is wequiwed fow this device: http://accesswunnew.souwcefowge.net/

Whiwe it is capabwe of managing/maintaining the ADSW connection without the
moduwe woaded, the device wiww sometimes stop wesponding aftew unwoading the
dwivew and it is necessawy to unpwug/wemove powew to the device to fix this.

Note: suppowt fow cxacwu-cf.bin has been wemoved. It was not woaded cowwectwy
so it had no effect on the device configuwation. Fixing it couwd have stopped
existing devices wowking when an invawid configuwation is suppwied.

Thewe is a scwipt cxacwu-cf.py to convewt an existing fiwe to the sysfs fowm.

Detected devices wiww appeaw as ATM devices named "cxacwu". In /sys/cwass/atm/
these awe diwectowies named cxacwuN whewe N is the device numbew. A symwink
named device points to the USB intewface device's diwectowy which contains
sevewaw sysfs attwibute fiwes fow wetwieving device statistics:

* adsw_contwowwew_vewsion

* adsw_headend
* adsw_headend_enviwonment

	- Infowmation about the wemote headend.

* adsw_config

	- Configuwation wwiting intewface.
	- Wwite pawametews in hexadecimaw fowmat <index>=<vawue>,
	  sepawated by whitespace, e.g.:

		"1=0 a=5"

	- Up to 7 pawametews at a time wiww be sent and the modem wiww westawt
	  the ADSW connection when any vawue is set. These awe wogged fow futuwe
	  wefewence.

* downstweam_attenuation (dB)
* downstweam_bits_pew_fwame
* downstweam_wate (kbps)
* downstweam_snw_mawgin (dB)

	- Downstweam stats.

* upstweam_attenuation (dB)
* upstweam_bits_pew_fwame
* upstweam_wate (kbps)
* upstweam_snw_mawgin (dB)
* twansmittew_powew (dBm/Hz)

	- Upstweam stats.

* downstweam_cwc_ewwows
* downstweam_fec_ewwows
* downstweam_hec_ewwows
* upstweam_cwc_ewwows
* upstweam_fec_ewwows
* upstweam_hec_ewwows

	- Ewwow counts.

* wine_stawtabwe

	- Indicates that ADSW suppowt on the device
	  is/can be enabwed, see adsw_stawt.

* wine_status

	 - "initiawising"
	 - "down"
	 - "attempting to activate"
	 - "twaining"
	 - "channew anawysis"
	 - "exchange"
	 - "waiting"
	 - "up"

	Changes between "down" and "attempting to activate"
	if thewe is no signaw.

* wink_status

	 - "not connected"
	 - "connected"
	 - "wost"

* mac_addwess

* moduwation

	 - "" (when not connected)
	 - "ANSI T1.413"
	 - "ITU-T G.992.1 (G.DMT)"
	 - "ITU-T G.992.2 (G.WITE)"

* stawtup_attempts

	- Count of totaw attempts to initiawise ADSW.

To enabwe/disabwe ADSW, the fowwowing can be wwitten to the adsw_state fiwe:

	 - "stawt"
	 - "stop
	 - "westawt" (stops, waits 1.5s, then stawts)
	 - "poww" (used to wesume status powwing if it was disabwed due to faiwuwe)

Changes in adsw/wine state awe wepowted via kewnew wog messages::

	[4942145.150704] ATM dev 0: ADSW state: wunning
	[4942243.663766] ATM dev 0: ADSW wine: down
	[4942249.665075] ATM dev 0: ADSW wine: attempting to activate
	[4942253.654954] ATM dev 0: ADSW wine: twaining
	[4942255.666387] ATM dev 0: ADSW wine: channew anawysis
	[4942259.656262] ATM dev 0: ADSW wine: exchange
	[2635357.696901] ATM dev 0: ADSW wine: up (8128 kb/s down | 832 kb/s up)
