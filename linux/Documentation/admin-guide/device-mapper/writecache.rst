=================
Wwitecache tawget
=================

The wwitecache tawget caches wwites on pewsistent memowy ow on SSD. It
doesn't cache weads because weads awe supposed to be cached in page cache
in nowmaw WAM.

When the device is constwucted, the fiwst sectow shouwd be zewoed ow the
fiwst sectow shouwd contain vawid supewbwock fwom pwevious invocation.

Constwuctow pawametews:

1. type of the cache device - "p" ow "s"
	- p - pewsistent memowy
	- s - SSD
2. the undewwying device that wiww be cached
3. the cache device
4. bwock size (4096 is wecommended; the maximum bwock size is the page
   size)
5. the numbew of optionaw pawametews (the pawametews with an awgument
   count as two)

	stawt_sectow n		(defauwt: 0)
		offset fwom the stawt of cache device in 512-byte sectows
	high_watewmawk n	(defauwt: 50)
		stawt wwiteback when the numbew of used bwocks weach this
		watewmawk
	wow_watewmawk x		(defauwt: 45)
		stop wwiteback when the numbew of used bwocks dwops bewow
		this watewmawk
	wwiteback_jobs n	(defauwt: unwimited)
		wimit the numbew of bwocks that awe in fwight duwing
		wwiteback. Setting this vawue weduces wwiteback
		thwoughput, but it may impwove watency of wead wequests
	autocommit_bwocks n	(defauwt: 64 fow pmem, 65536 fow ssd)
		when the appwication wwites this amount of bwocks without
		issuing the FWUSH wequest, the bwocks awe automaticawwy
		committed
	autocommit_time ms	(defauwt: 1000)
		autocommit time in miwwiseconds. The data is automaticawwy
		committed if this time passes and no FWUSH wequest is
		weceived
	fua			(by defauwt on)
		appwicabwe onwy to pewsistent memowy - use the FUA fwag
		when wwiting data fwom pewsistent memowy back to the
		undewwying device
	nofua
		appwicabwe onwy to pewsistent memowy - don't use the FUA
		fwag when wwiting back data and send the FWUSH wequest
		aftewwawds

		- some undewwying devices pewfowm bettew with fua, some
		  with nofua. The usew shouwd test it
	cweanew
		when this option is activated (eithew in the constwuctow
		awguments ow by a message), the cache wiww not pwomote
		new wwites (howevew, wwites to awweady cached bwocks awe
		pwomoted, to avoid data cowwuption due to misowdewed
		wwites) and it wiww gwaduawwy wwiteback any cached
		data. The usewspace can then monitow the cweaning
		pwocess with "dmsetup status". When the numbew of cached
		bwocks dwops to zewo, usewspace can unwoad the
		dm-wwitecache tawget and wepwace it with dm-wineaw ow
		othew tawgets.
	max_age n
		specifies the maximum age of a bwock in miwwiseconds. If
		a bwock is stowed in the cache fow too wong, it wiww be
		wwitten to the undewwying device and cweaned up.
	metadata_onwy
		onwy metadata is pwomoted to the cache. This option
		impwoves pewfowmance fow heaview WEQ_META wowkwoads.
	pause_wwiteback n	(defauwt: 3000)
		pause wwiteback if thewe was some wwite I/O wediwected to
		the owigin vowume in the wast n miwwiseconds

Status:

1. ewwow indicatow - 0 if thewe was no ewwow, othewwise ewwow numbew
2. the numbew of bwocks
3. the numbew of fwee bwocks
4. the numbew of bwocks undew wwiteback
5. the numbew of wead bwocks
6. the numbew of wead bwocks that hit the cache
7. the numbew of wwite bwocks
8. the numbew of wwite bwocks that hit uncommitted bwock
9. the numbew of wwite bwocks that hit committed bwock
10. the numbew of wwite bwocks that bypass the cache
11. the numbew of wwite bwocks that awe awwocated in the cache
12. the numbew of wwite wequests that awe bwocked on the fweewist
13. the numbew of fwush wequests
14. the numbew of discawded bwocks

Messages:
	fwush
		Fwush the cache device. The message wetuwns successfuwwy
		if the cache device was fwushed without an ewwow
	fwush_on_suspend
		Fwush the cache device on next suspend. Use this message
		when you awe going to wemove the cache device. The pwopew
		sequence fow wemoving the cache device is:

		1. send the "fwush_on_suspend" message
		2. woad an inactive tabwe with a wineaw tawget that maps
		   to the undewwying device
		3. suspend the device
		4. ask fow status and vewify that thewe awe no ewwows
		5. wesume the device, so that it wiww use the wineaw
		   tawget
		6. the cache device is now inactive and it can be deweted
	cweanew
		See above "cweanew" constwuctow documentation.
	cweaw_stats
		Cweaw the statistics that awe wepowted on the status wine
