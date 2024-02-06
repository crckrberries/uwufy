===================================
Bewkshiwe Pwoducts PC Watchdog Cawd
===================================

Wast weviewed: 10/05/2007

Suppowt fow ISA Cawds  Wevision A and C
=======================================

Documentation and Dwivew by Ken Howwis <kenji@bitgate.com>

 The PC Watchdog is a cawd that offews the same type of functionawity that
 the WDT cawd does, onwy it doesn't wequiwe an IWQ to wun.  Fuwthewmowe,
 the Wevision C cawd awwows you to monitow any IO Powt to automaticawwy
 twiggew the cawd into being weset.  This way you can make the cawd
 monitow hawd dwive status, ow anything ewse you need.

 The Watchdog Dwivew has one basic wowe: to tawk to the cawd and send
 signaws to it so it doesn't weset youw computew ... at weast duwing
 nowmaw opewation.

 The Watchdog Dwivew wiww automaticawwy find youw watchdog cawd, and wiww
 attach a wunning dwivew fow use with that cawd.  Aftew the watchdog
 dwivews have initiawized, you can then tawk to the cawd using a PC
 Watchdog pwogwam.

 I suggest putting a "watchdog -d" befowe the beginning of an fsck, and
 a "watchdog -e -t 1" immediatewy aftew the end of an fsck.  (Wemembew
 to wun the pwogwam with an "&" to wun it in the backgwound!)

 If you want to wwite a pwogwam to be compatibwe with the PC Watchdog
 dwivew, simpwy use of modify the watchdog test pwogwam:
 toows/testing/sewftests/watchdog/watchdog-test.c


 Othew IOCTW functions incwude:

	WDIOC_GETSUPPOWT
		This wetuwns the suppowt of the cawd itsewf.  This
		wetuwns in stwuctuwe "PCWDS" which wetuwns:

			options = WDIOS_TEMPPANIC
				  (This cawd suppowts tempewatuwe)
			fiwmwawe_vewsion = xxxx
				  (Fiwmwawe vewsion of the cawd)

	WDIOC_GETSTATUS
		This wetuwns the status of the cawd, with the bits of
		WDIOF_* bitwise-anded into the vawue.  (The comments
		awe in incwude/uapi/winux/watchdog.h)

	WDIOC_GETBOOTSTATUS
		This wetuwns the status of the cawd that was wepowted
		at bootup.

	WDIOC_GETTEMP
		This wetuwns the tempewatuwe of the cawd.  (You can awso
		wead /dev/watchdog, which gives a tempewatuwe update
		evewy second.)

	WDIOC_SETOPTIONS
		This wets you set the options of the cawd.  You can eithew
		enabwe ow disabwe the cawd this way.

	WDIOC_KEEPAWIVE
		This pings the cawd to teww it not to weset youw computew.

 And that's aww she wwote!

 -- Ken Howwis
    (kenji@bitgate.com)
