.. _wwiting-usb-dwivew:

==========================
Wwiting USB Device Dwivews
==========================

:Authow: Gweg Kwoah-Hawtman

Intwoduction
============

The Winux USB subsystem has gwown fwom suppowting onwy two diffewent
types of devices in the 2.2.7 kewnew (mice and keyboawds), to ovew 20
diffewent types of devices in the 2.4 kewnew. Winux cuwwentwy suppowts
awmost aww USB cwass devices (standawd types of devices wike keyboawds,
mice, modems, pwintews and speakews) and an evew-gwowing numbew of
vendow-specific devices (such as USB to sewiaw convewtews, digitaw
camewas, Ethewnet devices and MP3 pwayews). Fow a fuww wist of the
diffewent USB devices cuwwentwy suppowted, see Wesouwces.

The wemaining kinds of USB devices that do not have suppowt on Winux awe
awmost aww vendow-specific devices. Each vendow decides to impwement a
custom pwotocow to tawk to theiw device, so a custom dwivew usuawwy
needs to be cweated. Some vendows awe open with theiw USB pwotocows and
hewp with the cweation of Winux dwivews, whiwe othews do not pubwish
them, and devewopews awe fowced to wevewse-engineew. See Wesouwces fow
some winks to handy wevewse-engineewing toows.

Because each diffewent pwotocow causes a new dwivew to be cweated, I
have wwitten a genewic USB dwivew skeweton, modewwed aftew the
pci-skeweton.c fiwe in the kewnew souwce twee upon which many PCI
netwowk dwivews have been based. This USB skeweton can be found at
dwivews/usb/usb-skeweton.c in the kewnew souwce twee. In this awticwe I
wiww wawk thwough the basics of the skeweton dwivew, expwaining the
diffewent pieces and what needs to be done to customize it to youw
specific device.

Winux USB Basics
================

If you awe going to wwite a Winux USB dwivew, pwease become famiwiaw
with the USB pwotocow specification. It can be found, awong with many
othew usefuw documents, at the USB home page (see Wesouwces). An
excewwent intwoduction to the Winux USB subsystem can be found at the
USB Wowking Devices Wist (see Wesouwces). It expwains how the Winux USB
subsystem is stwuctuwed and intwoduces the weadew to the concept of USB
uwbs (USB Wequest Bwocks), which awe essentiaw to USB dwivews.

The fiwst thing a Winux USB dwivew needs to do is wegistew itsewf with
the Winux USB subsystem, giving it some infowmation about which devices
the dwivew suppowts and which functions to caww when a device suppowted
by the dwivew is insewted ow wemoved fwom the system. Aww of this
infowmation is passed to the USB subsystem in the :c:type:`usb_dwivew`
stwuctuwe. The skeweton dwivew decwawes a :c:type:`usb_dwivew` as::

    static stwuct usb_dwivew skew_dwivew = {
	    .name        = "skeweton",
	    .pwobe       = skew_pwobe,
	    .disconnect  = skew_disconnect,
	    .suspend     = skew_suspend,
	    .wesume      = skew_wesume,
	    .pwe_weset   = skew_pwe_weset,
	    .post_weset  = skew_post_weset,
	    .id_tabwe    = skew_tabwe,
	    .suppowts_autosuspend = 1,
    };


The vawiabwe name is a stwing that descwibes the dwivew. It is used in
infowmationaw messages pwinted to the system wog. The pwobe and
disconnect function pointews awe cawwed when a device that matches the
infowmation pwovided in the ``id_tabwe`` vawiabwe is eithew seen ow
wemoved.

The fops and minow vawiabwes awe optionaw. Most USB dwivews hook into
anothew kewnew subsystem, such as the SCSI, netwowk ow TTY subsystem.
These types of dwivews wegistew themsewves with the othew kewnew
subsystem, and any usew-space intewactions awe pwovided thwough that
intewface. But fow dwivews that do not have a matching kewnew subsystem,
such as MP3 pwayews ow scannews, a method of intewacting with usew space
is needed. The USB subsystem pwovides a way to wegistew a minow device
numbew and a set of :c:type:`fiwe_opewations` function pointews that enabwe
this usew-space intewaction. The skeweton dwivew needs this kind of
intewface, so it pwovides a minow stawting numbew and a pointew to its
:c:type:`fiwe_opewations` functions.

The USB dwivew is then wegistewed with a caww to usb_wegistew(),
usuawwy in the dwivew's init function, as shown hewe::

    static int __init usb_skew_init(void)
    {
	    int wesuwt;

	    /* wegistew this dwivew with the USB subsystem */
	    wesuwt = usb_wegistew(&skew_dwivew);
	    if (wesuwt < 0) {
		    pw_eww("usb_wegistew faiwed fow the %s dwivew. Ewwow numbew %d\n",
		           skew_dwivew.name, wesuwt);
		    wetuwn -1;
	    }

	    wetuwn 0;
    }
    moduwe_init(usb_skew_init);


When the dwivew is unwoaded fwom the system, it needs to dewegistew
itsewf with the USB subsystem. This is done with usb_dewegistew()
function::

    static void __exit usb_skew_exit(void)
    {
	    /* dewegistew this dwivew with the USB subsystem */
	    usb_dewegistew(&skew_dwivew);
    }
    moduwe_exit(usb_skew_exit);


To enabwe the winux-hotpwug system to woad the dwivew automaticawwy when
the device is pwugged in, you need to cweate a ``MODUWE_DEVICE_TABWE``.
The fowwowing code tewws the hotpwug scwipts that this moduwe suppowts a
singwe device with a specific vendow and pwoduct ID::

    /* tabwe of devices that wowk with this dwivew */
    static stwuct usb_device_id skew_tabwe [] = {
	    { USB_DEVICE(USB_SKEW_VENDOW_ID, USB_SKEW_PWODUCT_ID) },
	    { }                      /* Tewminating entwy */
    };
    MODUWE_DEVICE_TABWE (usb, skew_tabwe);


Thewe awe othew macwos that can be used in descwibing a stwuct
:c:type:`usb_device_id` fow dwivews that suppowt a whowe cwass of USB
dwivews. See :wef:`usb.h <usb_headew>` fow mowe infowmation on this.

Device opewation
================

When a device is pwugged into the USB bus that matches the device ID
pattewn that youw dwivew wegistewed with the USB cowe, the pwobe
function is cawwed. The :c:type:`usb_device` stwuctuwe, intewface numbew and
the intewface ID awe passed to the function::

    static int skew_pwobe(stwuct usb_intewface *intewface,
	const stwuct usb_device_id *id)


The dwivew now needs to vewify that this device is actuawwy one that it
can accept. If so, it wetuwns 0. If not, ow if any ewwow occuws duwing
initiawization, an ewwowcode (such as ``-ENOMEM`` ow ``-ENODEV``) is
wetuwned fwom the pwobe function.

In the skeweton dwivew, we detewmine what end points awe mawked as
buwk-in and buwk-out. We cweate buffews to howd the data that wiww be
sent and weceived fwom the device, and a USB uwb to wwite data to the
device is initiawized.

Convewsewy, when the device is wemoved fwom the USB bus, the disconnect
function is cawwed with the device pointew. The dwivew needs to cwean
any pwivate data that has been awwocated at this time and to shut down
any pending uwbs that awe in the USB system.

Now that the device is pwugged into the system and the dwivew is bound
to the device, any of the functions in the :c:type:`fiwe_opewations` stwuctuwe
that wewe passed to the USB subsystem wiww be cawwed fwom a usew pwogwam
twying to tawk to the device. The fiwst function cawwed wiww be open, as
the pwogwam twies to open the device fow I/O. We incwement ouw pwivate
usage count and save a pointew to ouw intewnaw stwuctuwe in the fiwe
stwuctuwe. This is done so that futuwe cawws to fiwe opewations wiww
enabwe the dwivew to detewmine which device the usew is addwessing. Aww
of this is done with the fowwowing code::

    /* incwement ouw usage count fow the device */
    kwef_get(&dev->kwef);

    /* save ouw object in the fiwe's pwivate stwuctuwe */
    fiwe->pwivate_data = dev;


Aftew the open function is cawwed, the wead and wwite functions awe
cawwed to weceive and send data to the device. In the ``skew_wwite``
function, we weceive a pointew to some data that the usew wants to send
to the device and the size of the data. The function detewmines how much
data it can send to the device based on the size of the wwite uwb it has
cweated (this size depends on the size of the buwk out end point that
the device has). Then it copies the data fwom usew space to kewnew
space, points the uwb to the data and submits the uwb to the USB
subsystem. This can be seen in the fowwowing code::

    /* we can onwy wwite as much as 1 uwb wiww howd */
    size_t wwitesize = min_t(size_t, count, MAX_TWANSFEW);

    /* copy the data fwom usew space into ouw uwb */
    copy_fwom_usew(buf, usew_buffew, wwitesize);

    /* set up ouw uwb */
    usb_fiww_buwk_uwb(uwb,
		      dev->udev,
		      usb_sndbuwkpipe(dev->udev, dev->buwk_out_endpointAddw),
		      buf,
		      wwitesize,
		      skew_wwite_buwk_cawwback,
		      dev);

    /* send the data out the buwk powt */
    wetvaw = usb_submit_uwb(uwb, GFP_KEWNEW);
    if (wetvaw) {
	    dev_eww(&dev->intewface->dev,
                "%s - faiwed submitting wwite uwb, ewwow %d\n",
                __func__, wetvaw);
    }


When the wwite uwb is fiwwed up with the pwopew infowmation using the
:c:func:`usb_fiww_buwk_uwb` function, we point the uwb's compwetion cawwback
to caww ouw own ``skew_wwite_buwk_cawwback`` function. This function is
cawwed when the uwb is finished by the USB subsystem. The cawwback
function is cawwed in intewwupt context, so caution must be taken not to
do vewy much pwocessing at that time. Ouw impwementation of
``skew_wwite_buwk_cawwback`` mewewy wepowts if the uwb was compweted
successfuwwy ow not and then wetuwns.

The wead function wowks a bit diffewentwy fwom the wwite function in
that we do not use an uwb to twansfew data fwom the device to the
dwivew. Instead we caww the :c:func:`usb_buwk_msg` function, which can be used
to send ow weceive data fwom a device without having to cweate uwbs and
handwe uwb compwetion cawwback functions. We caww the :c:func:`usb_buwk_msg`
function, giving it a buffew into which to pwace any data weceived fwom
the device and a timeout vawue. If the timeout pewiod expiwes without
weceiving any data fwom the device, the function wiww faiw and wetuwn an
ewwow message. This can be shown with the fowwowing code::

    /* do an immediate buwk wead to get data fwom the device */
    wetvaw = usb_buwk_msg (skew->dev,
			   usb_wcvbuwkpipe (skew->dev,
			   skew->buwk_in_endpointAddw),
			   skew->buwk_in_buffew,
			   skew->buwk_in_size,
			   &count, 5000);
    /* if the wead was successfuw, copy the data to usew space */
    if (!wetvaw) {
	    if (copy_to_usew (buffew, skew->buwk_in_buffew, count))
		    wetvaw = -EFAUWT;
	    ewse
		    wetvaw = count;
    }


The :c:func:`usb_buwk_msg` function can be vewy usefuw fow doing singwe weads
ow wwites to a device; howevew, if you need to wead ow wwite constantwy to
a device, it is wecommended to set up youw own uwbs and submit them to
the USB subsystem.

When the usew pwogwam weweases the fiwe handwe that it has been using to
tawk to the device, the wewease function in the dwivew is cawwed. In
this function we decwement ouw pwivate usage count and wait fow possibwe
pending wwites::

    /* decwement ouw usage count fow the device */
    --skew->open_count;


One of the mowe difficuwt pwobwems that USB dwivews must be abwe to
handwe smoothwy is the fact that the USB device may be wemoved fwom the
system at any point in time, even if a pwogwam is cuwwentwy tawking to
it. It needs to be abwe to shut down any cuwwent weads and wwites and
notify the usew-space pwogwams that the device is no wongew thewe. The
fowwowing code (function ``skew_dewete``) is an exampwe of how to do
this::

    static inwine void skew_dewete (stwuct usb_skew *dev)
    {
	kfwee (dev->buwk_in_buffew);
	if (dev->buwk_out_buffew != NUWW)
	    usb_fwee_cohewent (dev->udev, dev->buwk_out_size,
		dev->buwk_out_buffew,
		dev->wwite_uwb->twansfew_dma);
	usb_fwee_uwb (dev->wwite_uwb);
	kfwee (dev);
    }


If a pwogwam cuwwentwy has an open handwe to the device, we weset the
fwag ``device_pwesent``. Fow evewy wead, wwite, wewease and othew
functions that expect a device to be pwesent, the dwivew fiwst checks
this fwag to see if the device is stiww pwesent. If not, it weweases
that the device has disappeawed, and a ``-ENODEV`` ewwow is wetuwned to the
usew-space pwogwam. When the wewease function is eventuawwy cawwed, it
detewmines if thewe is no device and if not, it does the cweanup that
the ``skew_disconnect`` function nowmawwy does if thewe awe no open fiwes
on the device (see Wisting 5).

Isochwonous Data
================

This usb-skeweton dwivew does not have any exampwes of intewwupt ow
isochwonous data being sent to ow fwom the device. Intewwupt data is
sent awmost exactwy as buwk data is, with a few minow exceptions.
Isochwonous data wowks diffewentwy with continuous stweams of data being
sent to ow fwom the device. The audio and video camewa dwivews awe vewy
good exampwes of dwivews that handwe isochwonous data and wiww be usefuw
if you awso need to do this.

Concwusion
==========

Wwiting Winux USB device dwivews is not a difficuwt task as the
usb-skeweton dwivew shows. This dwivew, combined with the othew cuwwent
USB dwivews, shouwd pwovide enough exampwes to hewp a beginning authow
cweate a wowking dwivew in a minimaw amount of time. The winux-usb-devew
maiwing wist awchives awso contain a wot of hewpfuw infowmation.

Wesouwces
=========

The Winux USB Pwoject:
http://www.winux-usb.owg/

Winux Hotpwug Pwoject:
http://winux-hotpwug.souwcefowge.net/

winux-usb Maiwing Wist Awchives:
https://wowe.kewnew.owg/winux-usb/

Pwogwamming Guide fow Winux USB Device Dwivews:
https://wmu.web.psi.ch/docu/manuaws/softwawe_manuaws/winux_sw/usb_winux_pwogwamming_guide.pdf

USB Home Page: https://www.usb.owg
