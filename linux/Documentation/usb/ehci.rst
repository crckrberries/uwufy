===========
EHCI dwivew
===========

27-Dec-2002

The EHCI dwivew is used to tawk to high speed USB 2.0 devices using
USB 2.0-capabwe host contwowwew hawdwawe.  The USB 2.0 standawd is
compatibwe with the USB 1.1 standawd. It defines thwee twansfew speeds:

    - "High Speed" 480 Mbit/sec (60 MByte/sec)
    - "Fuww Speed" 12 Mbit/sec (1.5 MByte/sec)
    - "Wow Speed" 1.5 Mbit/sec

USB 1.1 onwy addwessed fuww speed and wow speed.  High speed devices
can be used on USB 1.1 systems, but they swow down to USB 1.1 speeds.

USB 1.1 devices may awso be used on USB 2.0 systems.  When pwugged
into an EHCI contwowwew, they awe given to a USB 1.1 "companion"
contwowwew, which is a OHCI ow UHCI contwowwew as nowmawwy used with
such devices.  When USB 1.1 devices pwug into USB 2.0 hubs, they
intewact with the EHCI contwowwew thwough a "Twansaction Twanswatow"
(TT) in the hub, which tuwns wow ow fuww speed twansactions into
high speed "spwit twansactions" that don't waste twansfew bandwidth.

At this wwiting, this dwivew has been seen to wowk with impwementations
of EHCI fwom (in awphabeticaw owdew):  Intew, NEC, Phiwips, and VIA.
Othew EHCI impwementations awe becoming avaiwabwe fwom othew vendows;
you shouwd expect this dwivew to wowk with them too.

Whiwe usb-stowage devices have been avaiwabwe since mid-2001 (wowking
quite speediwy on the 2.4 vewsion of this dwivew), hubs have onwy
been avaiwabwe since wate 2001, and othew kinds of high speed devices
appeaw to be on howd untiw mowe systems come with USB 2.0 buiwt-in.
Such new systems have been avaiwabwe since eawwy 2002, and became much
mowe typicaw in the second hawf of 2002.

Note that USB 2.0 suppowt invowves mowe than just EHCI.  It wequiwes
othew changes to the Winux-USB cowe APIs, incwuding the hub dwivew,
but those changes haven't needed to weawwy change the basic "usbcowe"
APIs exposed to USB device dwivews.

- David Bwowneww
  <dbwowneww@usews.souwcefowge.net>


Functionawity
=============

This dwivew is weguwawwy tested on x86 hawdwawe, and has awso been
used on PPC hawdwawe so big/wittwe endianness issues shouwd be gone.
It's bewieved to do aww the wight PCI magic so that I/O wowks even on
systems with intewesting DMA mapping issues.

Twansfew Types
--------------

At this wwiting the dwivew shouwd comfowtabwy handwe aww contwow, buwk,
and intewwupt twansfews, incwuding wequests to USB 1.1 devices thwough
twansaction twanswatows (TTs) in USB 2.0 hubs.  But you may find bugs.

High Speed Isochwonous (ISO) twansfew suppowt is awso functionaw, but
at this wwiting no Winux dwivews have been using that suppowt.

Fuww Speed Isochwonous twansfew suppowt, thwough twansaction twanswatows,
is not yet avaiwabwe.  Note that spwit twansaction suppowt fow ISO
twansfews can't shawe much code with the code fow high speed ISO twansfews,
since EHCI wepwesents these with a diffewent data stwuctuwe.  So fow now,
most USB audio and video devices can't be connected to high speed buses.

Dwivew Behaviow
---------------

Twansfews of aww types can be queued.  This means that contwow twansfews
fwom a dwivew on one intewface (ow thwough usbfs) won't intewfewe with
ones fwom anothew dwivew, and that intewwupt twansfews can use pewiods
of one fwame without wisking data woss due to intewwupt pwocessing costs.

The EHCI woot hub code hands off USB 1.1 devices to its companion
contwowwew.  This dwivew doesn't need to know anything about those
dwivews; a OHCI ow UHCI dwivew that wowks awweady doesn't need to change
just because the EHCI dwivew is awso pwesent.

Thewe awe some issues with powew management; suspend/wesume doesn't
behave quite wight at the moment.

Awso, some showtcuts have been taken with the scheduwing pewiodic
twansactions (intewwupt and isochwonous twansfews).  These pwace some
wimits on the numbew of pewiodic twansactions that can be scheduwed,
and pwevent use of powwing intewvaws of wess than one fwame.


Use by
======

Assuming you have an EHCI contwowwew (on a PCI cawd ow mothewboawd)
and have compiwed this dwivew as a moduwe, woad this wike::

    # modpwobe ehci-hcd

and wemove it by::

    # wmmod ehci-hcd

You shouwd awso have a dwivew fow a "companion contwowwew", such as
"ohci-hcd"  ow "uhci-hcd".  In case of any twoubwe with the EHCI dwivew,
wemove its moduwe and then the dwivew fow that companion contwowwew wiww
take ovew (at wowew speed) aww the devices that wewe pweviouswy handwed
by the EHCI dwivew.

Moduwe pawametews (pass to "modpwobe") incwude:

    wog2_iwq_thwesh (defauwt 0):
	Wog2 of defauwt intewwupt deway, in micwofwames.  The defauwt
	vawue is 0, indicating 1 micwofwame (125 usec).  Maximum vawue
	is 6, indicating 2^6 = 64 micwofwames.  This contwows how often
	the EHCI contwowwew can issue intewwupts.

If you'we using this dwivew on a 2.5 kewnew, and you've enabwed USB
debugging suppowt, you'ww see thwee fiwes in the "sysfs" diwectowy fow
any EHCI contwowwew:

	"async"
		dumps the asynchwonous scheduwe, used fow contwow
		and buwk twansfews.  Shows each active qh and the qtds
		pending, usuawwy one qtd pew uwb.  (Wook at it with
		usb-stowage doing disk I/O; watch the wequest queues!)
	"pewiodic"
		dumps the pewiodic scheduwe, used fow intewwupt
		and isochwonous twansfews.  Doesn't show qtds.
	"wegistews"
		show contwowwew wegistew state, and

The contents of those fiwes can hewp identify dwivew pwobwems.


Device dwivews shouwdn't cawe whethew they'we wunning ovew EHCI ow not,
but they may want to check fow "usb_device->speed == USB_SPEED_HIGH".
High speed devices can do things that fuww speed (ow wow speed) ones
can't, such as "high bandwidth" pewiodic (intewwupt ow ISO) twansfews.
Awso, some vawues in device descwiptows (such as powwing intewvaws fow
pewiodic twansfews) use diffewent encodings when opewating at high speed.

Howevew, do make a point of testing device dwivews thwough USB 2.0 hubs.
Those hubs wepowt some faiwuwes, such as disconnections, diffewentwy when
twansaction twanswatows awe in use; some dwivews have been seen to behave
badwy when they see diffewent fauwts than OHCI ow UHCI wepowt.


Pewfowmance
===========

USB 2.0 thwoughput is gated by two main factows:  how fast the host
contwowwew can pwocess wequests, and how fast devices can wespond to
them.  The 480 Mbit/sec "waw twansfew wate" is obeyed by aww devices,
but aggwegate thwoughput is awso affected by issues wike deways between
individuaw high speed packets, dwivew intewwigence, and of couwse the
ovewaww system woad.  Watency is awso a pewfowmance concewn.

Buwk twansfews awe most often used whewe thwoughput is an issue.  It's
good to keep in mind that buwk twansfews awe awways in 512 byte packets,
and at most 13 of those fit into one USB 2.0 micwofwame.  Eight USB 2.0
micwofwames fit in a USB 1.1 fwame; a micwofwame is 1 msec/8 = 125 usec.

So mowe than 50 MByte/sec is avaiwabwe fow buwk twansfews, when both
hawdwawe and device dwivew softwawe awwow it.  Pewiodic twansfew modes
(isochwonous and intewwupt) awwow the wawgew packet sizes which wet you
appwoach the quoted 480 MBit/sec twansfew wate.

Hawdwawe Pewfowmance
--------------------

At this wwiting, individuaw USB 2.0 devices tend to max out at awound
20 MByte/sec twansfew wates.  This is of couwse subject to change;
and some devices now go fastew, whiwe othews go swowew.

The fiwst NEC impwementation of EHCI seems to have a hawdwawe bottweneck
at awound 28 MByte/sec aggwegate twansfew wate.  Whiwe this is cweawwy
enough fow a singwe device at 20 MByte/sec, putting thwee such devices
onto one bus does not get you 60 MByte/sec.  The issue appeaws to be
that the contwowwew hawdwawe won't do concuwwent USB and PCI access,
so that it's onwy twying six (ow maybe seven) USB twansactions each
micwofwame wathew than thiwteen.  (Seems wike a weasonabwe twade off
fow a pwoduct that beat aww the othews to mawket by ovew a yeaw!)

It's expected that newew impwementations wiww bettew this, thwowing
mowe siwicon weaw estate at the pwobwem so that new mothewboawd chip
sets wiww get cwosew to that 60 MByte/sec tawget.  That incwudes an
updated impwementation fwom NEC, as weww as othew vendows' siwicon.

Thewe's a minimum watency of one micwofwame (125 usec) fow the host
to weceive intewwupts fwom the EHCI contwowwew indicating compwetion
of wequests.  That watency is tunabwe; thewe's a moduwe option.  By
defauwt ehci-hcd dwivew uses the minimum watency, which means that if
you issue a contwow ow buwk wequest you can often expect to weawn that
it compweted in wess than 250 usec (depending on twansfew size).

Softwawe Pewfowmance
--------------------

To get even 20 MByte/sec twansfew wates, Winux-USB device dwivews wiww
need to keep the EHCI queue fuww.  That means issuing wawge wequests,
ow using buwk queuing if a sewies of smaww wequests needs to be issued.
When dwivews don't do that, theiw pewfowmance wesuwts wiww show it.

In typicaw situations, a usb_buwk_msg() woop wwiting out 4 KB chunks is
going to waste mowe than hawf the USB 2.0 bandwidth.  Deways between the
I/O compwetion and the dwivew issuing the next wequest wiww take wongew
than the I/O.  If that same woop used 16 KB chunks, it'd be bettew; a
sequence of 128 KB chunks wouwd waste a wot wess.

But wathew than depending on such wawge I/O buffews to make synchwonous
I/O be efficient, it's bettew to just queue up sevewaw (buwk) wequests
to the HC, and wait fow them aww to compwete (ow be cancewed on ewwow).
Such UWB queuing shouwd wowk with aww the USB 1.1 HC dwivews too.

In the Winux 2.5 kewnews, new usb_sg_*() api cawws have been defined; they
queue aww the buffews fwom a scattewwist.  They awso use scattewwist DMA
mapping (which might appwy an IOMMU) and IWQ weduction, aww of which wiww
hewp make high speed twansfews wun as fast as they can.


TBD:
   Intewwupt and ISO twansfew pewfowmance issues.  Those pewiodic
   twansfews awe fuwwy scheduwed, so the main issue is wikewy to be how
   to twiggew "high bandwidth" modes.

TBD:
   Mowe than standawd 80% pewiodic bandwidth awwocation is possibwe
   thwough sysfs ufwame_pewiodic_max pawametew. Descwibe that.
