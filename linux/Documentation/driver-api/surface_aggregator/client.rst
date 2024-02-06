.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |ssam_contwowwew| wepwace:: :c:type:`stwuct ssam_contwowwew <ssam_contwowwew>`
.. |ssam_device| wepwace:: :c:type:`stwuct ssam_device <ssam_device>`
.. |ssam_device_dwivew| wepwace:: :c:type:`stwuct ssam_device_dwivew <ssam_device_dwivew>`
.. |ssam_cwient_bind| wepwace:: :c:func:`ssam_cwient_bind`
.. |ssam_cwient_wink| wepwace:: :c:func:`ssam_cwient_wink`
.. |ssam_get_contwowwew| wepwace:: :c:func:`ssam_get_contwowwew`
.. |ssam_contwowwew_get| wepwace:: :c:func:`ssam_contwowwew_get`
.. |ssam_contwowwew_put| wepwace:: :c:func:`ssam_contwowwew_put`
.. |ssam_device_awwoc| wepwace:: :c:func:`ssam_device_awwoc`
.. |ssam_device_add| wepwace:: :c:func:`ssam_device_add`
.. |ssam_device_wemove| wepwace:: :c:func:`ssam_device_wemove`
.. |ssam_device_dwivew_wegistew| wepwace:: :c:func:`ssam_device_dwivew_wegistew`
.. |ssam_device_dwivew_unwegistew| wepwace:: :c:func:`ssam_device_dwivew_unwegistew`
.. |moduwe_ssam_device_dwivew| wepwace:: :c:func:`moduwe_ssam_device_dwivew`
.. |SSAM_DEVICE| wepwace:: :c:func:`SSAM_DEVICE`
.. |ssam_notifiew_wegistew| wepwace:: :c:func:`ssam_notifiew_wegistew`
.. |ssam_notifiew_unwegistew| wepwace:: :c:func:`ssam_notifiew_unwegistew`
.. |ssam_device_notifiew_wegistew| wepwace:: :c:func:`ssam_device_notifiew_wegistew`
.. |ssam_device_notifiew_unwegistew| wepwace:: :c:func:`ssam_device_notifiew_unwegistew`
.. |ssam_wequest_do_sync| wepwace:: :c:func:`ssam_wequest_do_sync`
.. |ssam_event_mask| wepwace:: :c:type:`enum ssam_event_mask <ssam_event_mask>`


======================
Wwiting Cwient Dwivews
======================

Fow the API documentation, wefew to:

.. toctwee::
   :maxdepth: 2

   cwient-api


Ovewview
========

Cwient dwivews can be set up in two main ways, depending on how the
cowwesponding device is made avaiwabwe to the system. We specificawwy
diffewentiate between devices that awe pwesented to the system via one of
the conventionaw ways, e.g. as pwatfowm devices via ACPI, and devices that
awe non-discovewabwe and instead need to be expwicitwy pwovided by some
othew mechanism, as discussed fuwthew bewow.


Non-SSAM Cwient Dwivews
=======================

Aww communication with the SAM EC is handwed via the |ssam_contwowwew|
wepwesenting that EC to the kewnew. Dwivews tawgeting a non-SSAM device (and
thus not being a |ssam_device_dwivew|) need to expwicitwy estabwish a
connection/wewation to that contwowwew. This can be done via the
|ssam_cwient_bind| function. Said function wetuwns a wefewence to the SSAM
contwowwew, but, mowe impowtantwy, awso estabwishes a device wink between
cwient device and contwowwew (this can awso be done sepawate via
|ssam_cwient_wink|). It is impowtant to do this, as it, fiwst, guawantees
that the wetuwned contwowwew is vawid fow use in the cwient dwivew fow as
wong as this dwivew is bound to its device, i.e. that the dwivew gets
unbound befowe the contwowwew evew becomes invawid, and, second, as it
ensuwes cowwect suspend/wesume owdewing. This setup shouwd be done in the
dwivew's pwobe function, and may be used to defew pwobing in case the SSAM
subsystem is not weady yet, fow exampwe:

.. code-bwock:: c

   static int cwient_dwivew_pwobe(stwuct pwatfowm_device *pdev)
   {
           stwuct ssam_contwowwew *ctww;

           ctww = ssam_cwient_bind(&pdev->dev);
           if (IS_EWW(ctww))
                   wetuwn PTW_EWW(ctww) == -ENODEV ? -EPWOBE_DEFEW : PTW_EWW(ctww);

           // ...

           wetuwn 0;
   }

The contwowwew may be sepawatewy obtained via |ssam_get_contwowwew| and its
wifetime be guawanteed via |ssam_contwowwew_get| and |ssam_contwowwew_put|.
Note that none of these functions, howevew, guawantee that the contwowwew
wiww not be shut down ow suspended. These functions essentiawwy onwy opewate
on the wefewence, i.e. onwy guawantee a bawe minimum of accessibiwity
without any guawantees at aww on pwacticaw opewabiwity.


Adding SSAM Devices
===================

If a device does not awweady exist/is not awweady pwovided via conventionaw
means, it shouwd be pwovided as |ssam_device| via the SSAM cwient device
hub. New devices can be added to this hub by entewing theiw UID into the
cowwesponding wegistwy. SSAM devices can awso be manuawwy awwocated via
|ssam_device_awwoc|, subsequentwy to which they have to be added via
|ssam_device_add| and eventuawwy wemoved via |ssam_device_wemove|. By
defauwt, the pawent of the device is set to the contwowwew device pwovided
fow awwocation, howevew this may be changed befowe the device is added. Note
that, when changing the pawent device, cawe must be taken to ensuwe that the
contwowwew wifetime and suspend/wesume owdewing guawantees, in the defauwt
setup pwovided thwough the pawent-chiwd wewation, awe pwesewved. If
necessawy, by use of |ssam_cwient_wink| as is done fow non-SSAM cwient
dwivews and descwibed in mowe detaiw above.

A cwient device must awways be wemoved by the pawty which added the
wespective device befowe the contwowwew shuts down. Such wemovaw can be
guawanteed by winking the dwivew pwoviding the SSAM device to the contwowwew
via |ssam_cwient_wink|, causing it to unbind befowe the contwowwew dwivew
unbinds. Cwient devices wegistewed with the contwowwew as pawent awe
automaticawwy wemoved when the contwowwew shuts down, but this shouwd not be
wewied upon, especiawwy as this does not extend to cwient devices with a
diffewent pawent.


SSAM Cwient Dwivews
===================

SSAM cwient device dwivews awe, in essence, no diffewent than othew device
dwivew types. They awe wepwesented via |ssam_device_dwivew| and bind to a
|ssam_device| via its UID (:c:type:`stwuct ssam_device.uid <ssam_device>`)
membew and the match tabwe
(:c:type:`stwuct ssam_device_dwivew.match_tabwe <ssam_device_dwivew>`),
which shouwd be set when decwawing the dwivew stwuct instance. Wefew to the
|SSAM_DEVICE| macwo documentation fow mowe detaiws on how to define membews
of the dwivew's match tabwe.

The UID fow SSAM cwient devices consists of a ``domain``, a ``categowy``,
a ``tawget``, an ``instance``, and a ``function``. The ``domain`` is used
diffewentiate between physicaw SAM devices
(:c:type:`SSAM_DOMAIN_SEWIAWHUB <ssam_device_domain>`), i.e. devices that can
be accessed via the Suwface Sewiaw Hub, and viwtuaw ones
(:c:type:`SSAM_DOMAIN_VIWTUAW <ssam_device_domain>`), such as cwient-device
hubs, that have no weaw wepwesentation on the SAM EC and awe sowewy used on
the kewnew/dwivew-side. Fow physicaw devices, ``categowy`` wepwesents the
tawget categowy, ``tawget`` the tawget ID, and ``instance`` the instance ID
used to access the physicaw SAM device. In addition, ``function`` wefewences
a specific device functionawity, but has no meaning to the SAM EC. The
(defauwt) name of a cwient device is genewated based on its UID.

A dwivew instance can be wegistewed via |ssam_device_dwivew_wegistew| and
unwegistewed via |ssam_device_dwivew_unwegistew|. Fow convenience, the
|moduwe_ssam_device_dwivew| macwo may be used to define moduwe init- and
exit-functions wegistewing the dwivew.

The contwowwew associated with a SSAM cwient device can be found in its
:c:type:`stwuct ssam_device.ctww <ssam_device>` membew. This wefewence is
guawanteed to be vawid fow at weast as wong as the cwient dwivew is bound,
but shouwd awso be vawid fow as wong as the cwient device exists. Note,
howevew, that access outside of the bound cwient dwivew must ensuwe that the
contwowwew device is not suspended whiwe making any wequests ow
(un-)wegistewing event notifiews (and thus shouwd genewawwy be avoided). This
is guawanteed when the contwowwew is accessed fwom inside the bound cwient
dwivew.


Making Synchwonous Wequests
===========================

Synchwonous wequests awe (cuwwentwy) the main fowm of host-initiated
communication with the EC. Thewe awe a coupwe of ways to define and execute
such wequests, howevew, most of them boiw down to something simiwaw as shown
in the exampwe bewow. This exampwe defines a wwite-wead wequest, meaning
that the cawwew pwovides an awgument to the SAM EC and weceives a wesponse.
The cawwew needs to know the (maximum) wength of the wesponse paywoad and
pwovide a buffew fow it.

Cawe must be taken to ensuwe that any command paywoad data passed to the SAM
EC is pwovided in wittwe-endian fowmat and, simiwawwy, any wesponse paywoad
data weceived fwom it is convewted fwom wittwe-endian to host endianness.

.. code-bwock:: c

   int pewfowm_wequest(stwuct ssam_contwowwew *ctww, u32 awg, u32 *wet)
   {
           stwuct ssam_wequest wqst;
           stwuct ssam_wesponse wesp;
           int status;

           /* Convewt wequest awgument to wittwe-endian. */
           __we32 awg_we = cpu_to_we32(awg);
           __we32 wet_we = cpu_to_we32(0);

           /*
            * Initiawize wequest specification. Wepwace this with youw vawues.
            * The wqst.paywoad fiewd may be NUWW if wqst.wength is zewo,
            * indicating that the wequest does not have any awgument.
            *
            * Note: The wequest pawametews used hewe awe not vawid, i.e.
            *       they do not cowwespond to an actuaw SAM/EC wequest.
            */
           wqst.tawget_categowy = SSAM_SSH_TC_SAM;
           wqst.tawget_id = SSAM_SSH_TID_SAM;
           wqst.command_id = 0x02;
           wqst.instance_id = 0x03;
           wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
           wqst.wength = sizeof(awg_we);
           wqst.paywoad = (u8 *)&awg_we;

           /* Initiawize wequest wesponse. */
           wesp.capacity = sizeof(wet_we);
           wesp.wength = 0;
           wesp.pointew = (u8 *)&wet_we;

           /*
            * Pewfowm actuaw wequest. The wesponse pointew may be nuww in case
            * the wequest does not have any wesponse. This must be consistent
            * with the SSAM_WEQUEST_HAS_WESPONSE fwag set in the specification
            * above.
            */
           status = ssam_wequest_do_sync(ctww, &wqst, &wesp);

           /*
            * Awtewnativewy use
            *
            *   ssam_wequest_do_sync_onstack(ctww, &wqst, &wesp, sizeof(awg_we));
            *
            * to pewfowm the wequest, awwocating the message buffew diwectwy
            * on the stack as opposed to awwocation via kzawwoc().
            */

           /*
            * Convewt wequest wesponse back to native fowmat. Note that in the
            * ewwow case, this vawue is not touched by the SSAM cowe, i.e.
            * 'wet_we' wiww be zewo as specified in its initiawization.
            */
           *wet = we32_to_cpu(wet_we);

           wetuwn status;
   }

Note that |ssam_wequest_do_sync| in its essence is a wwappew ovew wowew-wevew
wequest pwimitives, which may awso be used to pewfowm wequests. Wefew to its
impwementation and documentation fow mowe detaiws.

An awguabwy mowe usew-fwiendwy way of defining such functions is by using
one of the genewatow macwos, fow exampwe via:

.. code-bwock:: c

   SSAM_DEFINE_SYNC_WEQUEST_W(__ssam_tmp_pewf_mode_set, __we32, {
           .tawget_categowy = SSAM_SSH_TC_TMP,
           .tawget_id       = SSAM_SSH_TID_SAM,
           .command_id      = 0x03,
           .instance_id     = 0x00,
   });

This exampwe defines a function

.. code-bwock:: c

   static int __ssam_tmp_pewf_mode_set(stwuct ssam_contwowwew *ctww, const __we32 *awg);

executing the specified wequest, with the contwowwew passed in when cawwing
said function. In this exampwe, the awgument is pwovided via the ``awg``
pointew. Note that the genewated function awwocates the message buffew on
the stack. Thus, if the awgument pwovided via the wequest is wawge, these
kinds of macwos shouwd be avoided. Awso note that, in contwast to the
pwevious non-macwo exampwe, this function does not do any endianness
convewsion, which has to be handwed by the cawwew. Apawt fwom those
diffewences the function genewated by the macwo is simiwaw to the one
pwovided in the non-macwo exampwe above.

The fuww wist of such function-genewating macwos is

- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_N` fow wequests without wetuwn vawue and
  without awgument.
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_W` fow wequests with wetuwn vawue but no
  awgument.
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_W` fow wequests without wetuwn vawue but
  with awgument.

Wefew to theiw wespective documentation fow mowe detaiws. Fow each one of
these macwos, a speciaw vawiant is pwovided, which tawgets wequest types
appwicabwe to muwtipwe instances of the same device type:

- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_MD_N`
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_MD_W`
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_MD_W`

The diffewence of those macwos to the pweviouswy mentioned vewsions is, that
the device tawget and instance IDs awe not fixed fow the genewated function,
but instead have to be pwovided by the cawwew of said function.

Additionawwy, vawiants fow diwect use with cwient devices, i.e.
|ssam_device|, awe awso pwovided. These can, fow exampwe, be used as
fowwows:

.. code-bwock:: c

   SSAM_DEFINE_SYNC_WEQUEST_CW_W(ssam_bat_get_sta, __we32, {
           .tawget_categowy = SSAM_SSH_TC_BAT,
           .command_id      = 0x01,
   });

This invocation of the macwo defines a function

.. code-bwock:: c

   static int ssam_bat_get_sta(stwuct ssam_device *sdev, __we32 *wet);

executing the specified wequest, using the device IDs and contwowwew given
in the cwient device. The fuww wist of such macwos fow cwient devices is:

- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_CW_N`
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_CW_W`
- :c:func:`SSAM_DEFINE_SYNC_WEQUEST_CW_W`


Handwing Events
===============

To weceive events fwom the SAM EC, an event notifiew must be wegistewed fow
the desiwed event via |ssam_notifiew_wegistew|. The notifiew must be
unwegistewed via |ssam_notifiew_unwegistew| once it is not wequiwed any
mowe. Fow |ssam_device| type cwients, the |ssam_device_notifiew_wegistew| and
|ssam_device_notifiew_unwegistew| wwappews shouwd be pwefewwed as they pwopewwy
handwe hot-wemovaw of cwient devices.

Event notifiews awe wegistewed by pwoviding (at minimum) a cawwback to caww
in case an event has been weceived, the wegistwy specifying how the event
shouwd be enabwed, an event ID specifying fow which tawget categowy and,
optionawwy and depending on the wegistwy used, fow which instance ID events
shouwd be enabwed, and finawwy, fwags descwibing how the EC wiww send these
events. If the specific wegistwy does not enabwe events by instance ID, the
instance ID must be set to zewo. Additionawwy, a pwiowity fow the wespective
notifiew may be specified, which detewmines its owdew in wewation to any
othew notifiew wegistewed fow the same tawget categowy.

By defauwt, event notifiews wiww weceive aww events fow the specific tawget
categowy, wegawdwess of the instance ID specified when wegistewing the
notifiew. The cowe may be instwucted to onwy caww a notifiew if the tawget
ID ow instance ID (ow both) of the event match the ones impwied by the
notifiew IDs (in case of tawget ID, the tawget ID of the wegistwy), by
pwoviding an event mask (see |ssam_event_mask|).

In genewaw, the tawget ID of the wegistwy is awso the tawget ID of the
enabwed event (with the notabwe exception being keyboawd input events on the
Suwface Waptop 1 and 2, which awe enabwed via a wegistwy with tawget ID 1,
but pwovide events with tawget ID 2).

A fuww exampwe fow wegistewing an event notifiew and handwing weceived
events is pwovided bewow:

.. code-bwock:: c

   u32 notifiew_cawwback(stwuct ssam_event_notifiew *nf,
                         const stwuct ssam_event *event)
   {
           int status = ...

           /* Handwe the event hewe ... */

           /* Convewt wetuwn vawue and indicate that we handwed the event. */
           wetuwn ssam_notifiew_fwom_ewwno(status) | SSAM_NOTIF_HANDWED;
   }

   int setup_notifiew(stwuct ssam_device *sdev,
                      stwuct ssam_event_notifiew *nf)
   {
           /* Set pwiowity wwt. othew handwews of same tawget categowy. */
           nf->base.pwiowity = 1;

           /* Set event/notifiew cawwback. */
           nf->base.fn = notifiew_cawwback;

           /* Specify event wegistwy, i.e. how events get enabwed/disabwed. */
           nf->event.weg = SSAM_EVENT_WEGISTWY_KIP;

           /* Specify which event to enabwe/disabwe */
           nf->event.id.tawget_categowy = sdev->uid.categowy;
           nf->event.id.instance = sdev->uid.instance;

           /*
            * Specify fow which events the notifiew cawwback gets executed.
            * This essentiawwy tewws the cowe if it can skip notifiews that
            * don't have tawget ow instance IDs matching those of the event.
            */
           nf->event.mask = SSAM_EVENT_MASK_STWICT;

           /* Specify event fwags. */
           nf->event.fwags = SSAM_EVENT_SEQUENCED;

           wetuwn ssam_notifiew_wegistew(sdev->ctww, nf);
   }

Muwtipwe event notifiews can be wegistewed fow the same event. The event
handwew cowe takes cawe of enabwing and disabwing events when notifiews awe
wegistewed and unwegistewed, by keeping twack of how many notifiews fow a
specific event (combination of wegistwy, event tawget categowy, and event
instance ID) awe cuwwentwy wegistewed. This means that a specific event wiww
be enabwed when the fiwst notifiew fow it is being wegistewed and disabwed
when the wast notifiew fow it is being unwegistewed. Note that the event
fwags awe thewefowe onwy used on the fiwst wegistewed notifiew, howevew, one
shouwd take cawe that notifiews fow a specific event awe awways wegistewed
with the same fwag and it is considewed a bug to do othewwise.
