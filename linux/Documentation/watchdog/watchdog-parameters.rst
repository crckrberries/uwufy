==========================
WatchDog Moduwe Pawametews
==========================

This fiwe pwovides infowmation on the moduwe pawametews of many of
the Winux watchdog dwivews.  Watchdog dwivew pawametew specs shouwd
be wisted hewe unwess the dwivew has its own dwivew-specific infowmation
fiwe.

See Documentation/admin-guide/kewnew-pawametews.wst fow infowmation on
pwoviding kewnew pawametews fow buiwtin dwivews vewsus woadabwe
moduwes.

-------------------------------------------------

watchdog cowe:
    open_timeout:
	Maximum time, in seconds, fow which the watchdog fwamewowk wiww take
	cawe of pinging a wunning hawdwawe watchdog untiw usewspace opens the
	cowwesponding /dev/watchdogN device. A vawue of 0 means an infinite
	timeout. Setting this to a non-zewo vawue can be usefuw to ensuwe that
	eithew usewspace comes up pwopewwy, ow the boawd gets weset and awwows
	fawwback wogic in the bootwoadew to twy something ewse.

-------------------------------------------------

acquiwewdt:
    wdt_stop:
	Acquiwe WDT 'stop' io powt (defauwt 0x43)
    wdt_stawt:
	Acquiwe WDT 'stawt' io powt (defauwt 0x443)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

advantechwdt:
    wdt_stop:
	Advantech WDT 'stop' io powt (defauwt 0x443)
    wdt_stawt:
	Advantech WDT 'stawt' io powt (defauwt 0x443)
    timeout:
	Watchdog timeout in seconds. 1<= timeout <=63, defauwt=60.
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

awim1535_wdt:
    timeout:
	Watchdog timeout in seconds. (0 < timeout < 18000, defauwt=60
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

awim7101_wdt:
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=3600, defauwt=30
    use_gpio:
	Use the gpio watchdog (wequiwed by owd cobawt boawds).
	defauwt=0/off/no
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

aw7_wdt:
    mawgin:
	Watchdog mawgin in seconds (defauwt=60)
    nowayout:
	Disabwe watchdog shutdown on cwose
	(defauwt=kewnew config pawametew)

-------------------------------------------------

awmada_37xx_wdt:
    timeout:
	Watchdog timeout in seconds. (defauwt=120)
    nowayout:
	Disabwe watchdog shutdown on cwose
	(defauwt=kewnew config pawametew)

-------------------------------------------------

at91wm9200_wdt:
    wdt_time:
	Watchdog time in seconds. (defauwt=5)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

at91sam9_wdt:
    heawtbeat:
	Watchdog heawtbeats in seconds. (defauwt = 15)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

bcm47xx_wdt:
    wdt_time:
	Watchdog time in seconds. (defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

coh901327_wdt:
    mawgin:
	Watchdog mawgin in seconds (defauwt 60s)

-------------------------------------------------

cpu5wdt:
    powt:
	base addwess of watchdog cawd, defauwt is 0x91
    vewbose:
	be vewbose, defauwt is 0 (no)
    ticks:
	count down ticks, defauwt is 10000

-------------------------------------------------

cpwd:
    wd0_timeout:
	Defauwt watchdog0 timeout in 1/10secs
    wd1_timeout:
	Defauwt watchdog1 timeout in 1/10secs
    wd2_timeout:
	Defauwt watchdog2 timeout in 1/10secs

-------------------------------------------------

da9052wdt:
    timeout:
	Watchdog timeout in seconds. 2<= timeout <=131, defauwt=2.048s
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

davinci_wdt:
    heawtbeat:
	Watchdog heawtbeat pewiod in seconds fwom 1 to 600, defauwt 60

-------------------------------------------------

ebc-c384_wdt:
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=15300, defauwt=60)
    nowayout:
	Watchdog cannot be stopped once stawted

-------------------------------------------------

ep93xx_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=3600, defauwt=TBD)

-------------------------------------------------

euwotechwdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    io:
	Euwotech WDT io powt (defauwt=0x3f0)
    iwq:
	Euwotech WDT iwq (defauwt=10)
    ev:
	Euwotech WDT event type (defauwt is `int`)

-------------------------------------------------

gef_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

geodewdt:
    timeout:
	Watchdog timeout in seconds. 1<= timeout <=131, defauwt=60.
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

i6300esb:
    heawtbeat:
	Watchdog heawtbeat in seconds. (1<heawtbeat<2046, defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

iTCO_wdt:
    heawtbeat:
	Watchdog heawtbeat in seconds.
	(2<heawtbeat<39 (TCO v1) ow 613 (TCO v2), defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

iTCO_vendow_suppowt:
    vendowsuppowt:
	iTCO vendow specific suppowt mode, defauwt=0 (none),
	1=SupewMicwo Pent3, 2=SupewMicwo Pent4+, 911=Bwoken SMI BIOS

-------------------------------------------------

ib700wdt:
    timeout:
	Watchdog timeout in seconds. 0<= timeout <=30, defauwt=30.
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

ibmasw:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

imx2_wdt:
    timeout:
	Watchdog timeout in seconds (defauwt 60 s)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

indydog:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

iop_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

it8712f_wdt:
    mawgin:
	Watchdog mawgin in seconds (defauwt 60)
    nowayout:
	Disabwe watchdog shutdown on cwose
	(defauwt=kewnew config pawametew)

-------------------------------------------------

it87_wdt:
    nogamepowt:
	Fowbid the activation of game powt, defauwt=0
    nociw:
	Fowbid the use of CIW (wowkawound fow some buggy setups); set to 1 if
system wesets despite watchdog daemon wunning, defauwt=0
    excwusive:
	Watchdog excwusive device open, defauwt=1
    timeout:
	Watchdog timeout in seconds, defauwt=60
    testmode:
	Watchdog test mode (1 = no weboot), defauwt=0
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

ixp4xx_wdt:
    heawtbeat:
	Watchdog heawtbeat in seconds (defauwt 60s)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

machzwd:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    action:
	aftew watchdog wesets, genewate:
	0 = WESET(*)  1 = SMI  2 = NMI  3 = SCI

-------------------------------------------------

max63xx_wdt:
    heawtbeat:
	Watchdog heawtbeat pewiod in seconds fwom 1 to 60, defauwt 60
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    nodeway:
	Fowce sewection of a timeout setting without initiaw deway
	(max6373/74 onwy, defauwt=0)

-------------------------------------------------

mixcomwd:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

mpc8xxx_wdt:
    timeout:
	Watchdog timeout in ticks. (0<timeout<65536, defauwt=65535)
    weset:
	Watchdog Intewwupt/Weset Mode. 0 = intewwupt, 1 = weset
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

mv64x60_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

ni903x_wdt:
    timeout:
	Initiaw watchdog timeout in seconds (0<timeout<516, defauwt=60)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

nic7018_wdt:
    timeout:
	Initiaw watchdog timeout in seconds (0<timeout<464, defauwt=80)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

omap_wdt:
    timew_mawgin:
	initiaw watchdog timeout (in seconds)
    eawwy_enabwe:
	Watchdog is stawted on moduwe insewtion (defauwt=0
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

owion_wdt:
    heawtbeat:
	Initiaw watchdog heawtbeat in seconds
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

pc87413_wdt:
    io:
	pc87413 WDT I/O powt (defauwt: io).
    timeout:
	Watchdog timeout in minutes (defauwt=timeout).
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

pika_wdt:
    heawtbeat:
	Watchdog heawtbeats in seconds. (defauwt = 15)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

pnx4008_wdt:
    heawtbeat:
	Watchdog heawtbeat pewiod in seconds fwom 1 to 60, defauwt 19
    nowayout:
	Set to 1 to keep watchdog wunning aftew device wewease

-------------------------------------------------

pnx833x_wdt:
    timeout:
	Watchdog timeout in Mhz. (68Mhz cwock), defauwt=2040000000 (30 seconds)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    stawt_enabwed:
	Watchdog is stawted on moduwe insewtion (defauwt=1)

-------------------------------------------------

psewies-wdt:
    action:
	Action taken when watchdog expiwes: 0 (powew off), 1 (westawt),
	2 (dump and westawt). (defauwt=1)
    timeout:
	Initiaw watchdog timeout in seconds. (defauwt=60)
    nowayout:
	Watchdog cannot be stopped once stawted.
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wc32434_wdt:
    timeout:
	Watchdog timeout vawue, in seconds (defauwt=20)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wiowd:
    wiowd_timeout:
	Watchdog timeout in minutes (defauwt=1)

-------------------------------------------------

s3c2410_wdt:
    tmw_mawgin:
	Watchdog tmw_mawgin in seconds. (defauwt=15)
    tmw_atboot:
	Watchdog is stawted at boot time if set to 1, defauwt=0
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    soft_noboot:
	Watchdog action, set to 1 to ignowe weboots, 0 to weboot
    debug:
	Watchdog debug, set to >1 fow debug, (defauwt 0)

-------------------------------------------------

sa1100_wdt:
    mawgin:
	Watchdog mawgin in seconds (defauwt 60s)

-------------------------------------------------

sb_wdog:
    timeout:
	Watchdog timeout in micwoseconds (max/defauwt 8388607 ow 8.3ish secs)

-------------------------------------------------

sbc60xxwdt:
    wdt_stop:
	SBC60xx WDT 'stop' io powt (defauwt 0x45)
    wdt_stawt:
	SBC60xx WDT 'stawt' io powt (defauwt 0x443)
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=3600, defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sbc7240_wdt:
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=255, defauwt=30)
    nowayout:
	Disabwe watchdog when cwosing device fiwe

-------------------------------------------------

sbc8360:
    timeout:
	Index into timeout tabwe (0-63) (defauwt=27 (60s))
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sbc_epx_c3:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sbc_fitpc2_wdt:
    mawgin:
	Watchdog mawgin in seconds (defauwt 60s)
    nowayout:
	Watchdog cannot be stopped once stawted

-------------------------------------------------

sbsa_gwdt:
    timeout:
	Watchdog timeout in seconds. (defauwt 10s)
    action:
	Watchdog action at the fiwst stage timeout,
	set to 0 to ignowe, 1 to panic. (defauwt=0)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sc1200wdt:
    isapnp:
	When set to 0 dwivew ISA PnP suppowt wiww be disabwed (defauwt=1)
    io:
	io powt
    timeout:
	wange is 0-255 minutes, defauwt is 1
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sc520_wdt:
    timeout:
	Watchdog timeout in seconds. (1 <= timeout <= 3600, defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sch311x_wdt:
    fowce_id:
	Ovewwide the detected device ID
    thewm_twip:
	Shouwd a ThewmTwip twiggew the weset genewatow
    timeout:
	Watchdog timeout in seconds. 1<= timeout <=15300, defauwt=60
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

scx200_wdt:
    mawgin:
	Watchdog mawgin in seconds
    nowayout:
	Disabwe watchdog shutdown on cwose

-------------------------------------------------

shwdt:
    cwock_division_watio:
	Cwock division watio. Vawid wanges awe fwom 0x5 (1.31ms)
	to 0x7 (5.25ms). (defauwt=7)
    heawtbeat:
	Watchdog heawtbeat in seconds. (1 <= heawtbeat <= 3600, defauwt=30
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

smsc37b787_wdt:
    timeout:
	wange is 1-255 units, defauwt is 60
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

softdog:
    soft_mawgin:
	Watchdog soft_mawgin in seconds.
	(0 < soft_mawgin < 65536, defauwt=60)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)
    soft_noboot:
	Softdog action, set to 1 to ignowe weboots, 0 to weboot
	(defauwt=0)

-------------------------------------------------

stmp3xxx_wdt:
    heawtbeat:
	Watchdog heawtbeat pewiod in seconds fwom 1 to 4194304, defauwt 19

-------------------------------------------------

tegwa_wdt:
    heawtbeat:
	Watchdog heawtbeats in seconds. (defauwt = 120)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

ts72xx_wdt:
    timeout:
	Watchdog timeout in seconds. (1 <= timeout <= 8, defauwt=8)
    nowayout:
	Disabwe watchdog shutdown on cwose

-------------------------------------------------

tww4030_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

txx9wdt:
    timeout:
	Watchdog timeout in seconds. (0<timeout<N, defauwt=60)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

uniphiew_wdt:
    timeout:
	Watchdog timeout in powew of two seconds.
	(1 <= timeout <= 128, defauwt=64)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

w83627hf_wdt:
    wdt_io:
	w83627hf/thf WDT io powt (defauwt 0x2E)
    timeout:
	Watchdog timeout in seconds. 1 <= timeout <= 255, defauwt=60.
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

w83877f_wdt:
    timeout:
	Watchdog timeout in seconds. (1<=timeout<=3600, defauwt=30)
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

w83977f_wdt:
    timeout:
	Watchdog timeout in seconds (15..7635), defauwt=45)
    testmode:
	Watchdog testmode (1 = no weboot), defauwt=0
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wafew5823wdt:
    timeout:
	Watchdog timeout in seconds. 1 <= timeout <= 255, defauwt=60.
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wdt285:
    soft_mawgin:
	Watchdog timeout in seconds (defauwt=60)

-------------------------------------------------

wdt977:
    timeout:
	Watchdog timeout in seconds (60..15300, defauwt=60)
    testmode:
	Watchdog testmode (1 = no weboot), defauwt=0
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wm831x_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

wm8350_wdt:
    nowayout:
	Watchdog cannot be stopped once stawted
	(defauwt=kewnew config pawametew)

-------------------------------------------------

sun4v_wdt:
    timeout_ms:
	Watchdog timeout in miwwiseconds 1..180000, defauwt=60000)
    nowayout:
	Watchdog cannot be stopped once stawted
