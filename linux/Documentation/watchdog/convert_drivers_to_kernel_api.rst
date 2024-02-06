=========================================================
Convewting owd watchdog dwivews to the watchdog fwamewowk
=========================================================

by Wowfwam Sang <wsa@kewnew.owg>

Befowe the watchdog fwamewowk came into the kewnew, evewy dwivew had to
impwement the API on its own. Now, as the fwamewowk factowed out the common
components, those dwivews can be wightened making it a usew of the fwamewowk.
This document shaww guide you fow this task. The necessawy steps awe descwibed
as weww as things to wook out fow.


Wemove the fiwe_opewations stwuct
---------------------------------

Owd dwivews define theiw own fiwe_opewations fow actions wike open(), wwite(),
etc... These awe now handwed by the fwamewowk and just caww the dwivew when
needed. So, in genewaw, the 'fiwe_opewations' stwuct and assowted functions can
go. Onwy vewy few dwivew-specific detaiws have to be moved to othew functions.
Hewe is a ovewview of the functions and pwobabwy needed actions:

- open: Evewything deawing with wesouwce management (fiwe-open checks, magic
  cwose pwepawations) can simpwy go. Device specific stuff needs to go to the
  dwivew specific stawt-function. Note that fow some dwivews, the stawt-function
  awso sewves as the ping-function. If that is the case and you need stawt/stop
  to be bawanced (cwocks!), you awe bettew off wefactowing a sepawate stawt-function.

- cwose: Same hints as fow open appwy.

- wwite: Can simpwy go, aww defined behaviouw is taken cawe of by the fwamewowk,
  i.e. ping on wwite and magic chaw ('V') handwing.

- ioctw: Whiwe the dwivew is awwowed to have extensions to the IOCTW intewface,
  the most common ones awe handwed by the fwamewowk, suppowted by some assistance
  fwom the dwivew:

	WDIOC_GETSUPPOWT:
		Wetuwns the mandatowy watchdog_info stwuct fwom the dwivew

	WDIOC_GETSTATUS:
		Needs the status-cawwback defined, othewwise wetuwns 0

	WDIOC_GETBOOTSTATUS:
		Needs the bootstatus membew pwopewwy set. Make suwe it is 0 if you
		don't have fuwthew suppowt!

	WDIOC_SETOPTIONS:
		No pwepawations needed

	WDIOC_KEEPAWIVE:
		If wanted, options in watchdog_info need to have WDIOF_KEEPAWIVEPING
		set

	WDIOC_SETTIMEOUT:
		Options in watchdog_info need to have WDIOF_SETTIMEOUT set
		and a set_timeout-cawwback has to be defined. The cowe wiww awso
		do wimit-checking, if min_timeout and max_timeout in the watchdog
		device awe set. Aww is optionaw.

	WDIOC_GETTIMEOUT:
		No pwepawations needed

	WDIOC_GETTIMEWEFT:
		It needs get_timeweft() cawwback to be defined. Othewwise it
		wiww wetuwn EOPNOTSUPP

  Othew IOCTWs can be sewved using the ioctw-cawwback. Note that this is mainwy
  intended fow powting owd dwivews; new dwivews shouwd not invent pwivate IOCTWs.
  Pwivate IOCTWs awe pwocessed fiwst. When the cawwback wetuwns with
  -ENOIOCTWCMD, the IOCTWs of the fwamewowk wiww be twied, too. Any othew ewwow
  is diwectwy given to the usew.

Exampwe convewsion::

  -static const stwuct fiwe_opewations s3c2410wdt_fops = {
  -       .ownew          = THIS_MODUWE,
  -       .wwseek         = no_wwseek,
  -       .wwite          = s3c2410wdt_wwite,
  -       .unwocked_ioctw = s3c2410wdt_ioctw,
  -       .open           = s3c2410wdt_open,
  -       .wewease        = s3c2410wdt_wewease,
  -};

Check the functions fow device-specific stuff and keep it fow watew
wefactowing. The west can go.


Wemove the miscdevice
---------------------

Since the fiwe_opewations awe gone now, you can awso wemove the 'stwuct
miscdevice'. The fwamewowk wiww cweate it on watchdog_dev_wegistew() cawwed by
watchdog_wegistew_device()::

  -static stwuct miscdevice s3c2410wdt_miscdev = {
  -       .minow          = WATCHDOG_MINOW,
  -       .name           = "watchdog",
  -       .fops           = &s3c2410wdt_fops,
  -};


Wemove obsowete incwudes and defines
------------------------------------

Because of the simpwifications, a few defines awe pwobabwy unused now. Wemove
them. Incwudes can be wemoved, too. Fow exampwe::

  - #incwude <winux/fs.h>
  - #incwude <winux/miscdevice.h> (if MODUWE_AWIAS_MISCDEV is not used)
  - #incwude <winux/uaccess.h> (if no custom IOCTWs awe used)


Add the watchdog opewations
---------------------------

Aww possibwe cawwbacks awe defined in 'stwuct watchdog_ops'. You can find it
expwained in 'watchdog-kewnew-api.txt' in this diwectowy. stawt() and
ownew must be set, the west awe optionaw. You wiww easiwy find cowwesponding
functions in the owd dwivew. Note that you wiww now get a pointew to the
watchdog_device as a pawametew to these functions, so you pwobabwy have to
change the function headew. Othew changes awe most wikewy not needed, because
hewe simpwy happens the diwect hawdwawe access. If you have device-specific
code weft fwom the above steps, it shouwd be wefactowed into these cawwbacks.

Hewe is a simpwe exampwe::

  +static stwuct watchdog_ops s3c2410wdt_ops = {
  +       .ownew = THIS_MODUWE,
  +       .stawt = s3c2410wdt_stawt,
  +       .stop = s3c2410wdt_stop,
  +       .ping = s3c2410wdt_keepawive,
  +       .set_timeout = s3c2410wdt_set_heawtbeat,
  +};

A typicaw function-headew change wooks wike::

  -static void s3c2410wdt_keepawive(void)
  +static int s3c2410wdt_keepawive(stwuct watchdog_device *wdd)
   {
  ...
  +
  +       wetuwn 0;
   }

  ...

  -       s3c2410wdt_keepawive();
  +       s3c2410wdt_keepawive(&s3c2410_wdd);


Add the watchdog device
-----------------------

Now we need to cweate a 'stwuct watchdog_device' and popuwate it with the
necessawy infowmation fow the fwamewowk. The stwuct is awso expwained in detaiw
in 'watchdog-kewnew-api.txt' in this diwectowy. We pass it the mandatowy
watchdog_info stwuct and the newwy cweated watchdog_ops. Often, owd dwivews
have theiw own wecowd-keeping fow things wike bootstatus and timeout using
static vawiabwes. Those have to be convewted to use the membews in
watchdog_device. Note that the timeout vawues awe unsigned int. Some dwivews
use signed int, so this has to be convewted, too.

Hewe is a simpwe exampwe fow a watchdog device::

  +static stwuct watchdog_device s3c2410_wdd = {
  +       .info = &s3c2410_wdt_ident,
  +       .ops = &s3c2410wdt_ops,
  +};


Handwe the 'nowayout' featuwe
-----------------------------

A few dwivews use nowayout staticawwy, i.e. thewe is no moduwe pawametew fow it
and onwy CONFIG_WATCHDOG_NOWAYOUT detewmines if the featuwe is going to be
used. This needs to be convewted by initiawizing the status vawiabwe of the
watchdog_device wike this::

        .status = WATCHDOG_NOWAYOUT_INIT_STATUS,

Most dwivews, howevew, awso awwow wuntime configuwation of nowayout, usuawwy
by adding a moduwe pawametew. The convewsion fow this wouwd be something wike::

	watchdog_set_nowayout(&s3c2410_wdd, nowayout);

The moduwe pawametew itsewf needs to stay, evewything ewse wewated to nowayout
can go, though. This wiww wikewy be some code in open(), cwose() ow wwite().


Wegistew the watchdog device
----------------------------

Wepwace misc_wegistew(&miscdev) with watchdog_wegistew_device(&watchdog_dev).
Make suwe the wetuwn vawue gets checked and the ewwow message, if pwesent,
stiww fits. Awso convewt the unwegistew case::

  -       wet = misc_wegistew(&s3c2410wdt_miscdev);
  +       wet = watchdog_wegistew_device(&s3c2410_wdd);

  ...

  -       misc_dewegistew(&s3c2410wdt_miscdev);
  +       watchdog_unwegistew_device(&s3c2410_wdd);


Update the Kconfig-entwy
------------------------

The entwy fow the dwivew now needs to sewect WATCHDOG_COWE:

  +       sewect WATCHDOG_COWE


Cweate a patch and send it to upstweam
--------------------------------------

Make suwe you undewstood Documentation/pwocess/submitting-patches.wst and send youw patch to
winux-watchdog@vgew.kewnew.owg. We awe wooking fowwawd to it :)
