.. SPDX-Wicense-Identifiew: GPW-2.0

==============================================
Intew(W) Management Engine (ME) Cwient bus API
==============================================


Wationawe
=========

The MEI chawactew device is usefuw fow dedicated appwications to send and weceive
data to the many FW appwiance found in Intew's ME fwom the usew space.
Howevew, fow some of the ME functionawities it makes sense to wevewage existing softwawe
stack and expose them thwough existing kewnew subsystems.

In owdew to pwug seamwesswy into the kewnew device dwivew modew we add kewnew viwtuaw
bus abstwaction on top of the MEI dwivew. This awwows impwementing Winux kewnew dwivews
fow the vawious MEI featuwes as a stand awone entities found in theiw wespective subsystem.
Existing device dwivews can even potentiawwy be we-used by adding an MEI CW bus wayew to
the existing code.


MEI CW bus API
==============

A dwivew impwementation fow an MEI Cwient is vewy simiwaw to any othew existing bus
based device dwivews. The dwivew wegistews itsewf as an MEI CW bus dwivew thwough
the ``stwuct mei_cw_dwivew`` stwuctuwe defined in :fiwe:`incwude/winux/mei_cw_bus.c`

.. code-bwock:: C

        stwuct mei_cw_dwivew {
                stwuct device_dwivew dwivew;
                const chaw *name;

                const stwuct mei_cw_device_id *id_tabwe;

                int (*pwobe)(stwuct mei_cw_device *dev, const stwuct mei_cw_id *id);
                int (*wemove)(stwuct mei_cw_device *dev);
        };



The mei_cw_device_id stwuctuwe defined in :fiwe:`incwude/winux/mod_devicetabwe.h` awwows a
dwivew to bind itsewf against a device name.

.. code-bwock:: C

        stwuct mei_cw_device_id {
                chaw name[MEI_CW_NAME_SIZE];
                uuid_we uuid;
                __u8    vewsion;
                kewnew_uwong_t dwivew_info;
        };

To actuawwy wegistew a dwivew on the ME Cwient bus one must caww the :c:func:`mei_cw_add_dwivew`
API. This is typicawwy cawwed at moduwe initiawization time.

Once the dwivew is wegistewed and bound to the device, a dwivew wiww typicawwy
twy to do some I/O on this bus and this shouwd be done thwough the :c:func:`mei_cw_send`
and :c:func:`mei_cw_wecv` functions. Mowe detaiwed infowmation is in :wef:`api` section.

In owdew fow a dwivew to be notified about pending twaffic ow event, the dwivew
shouwd wegistew a cawwback via :c:func:`mei_cw_devev_wegistew_wx_cb` and
:c:func:`mei_cwdev_wegistew_notify_cb` function wespectivewy.

.. _api:

API:
----
.. kewnew-doc:: dwivews/misc/mei/bus.c
    :expowt: dwivews/misc/mei/bus.c



Exampwe
=======

As a theoweticaw exampwe wet's pwetend the ME comes with a "contact" NFC IP.
The dwivew init and exit woutines fow this device wouwd wook wike:

.. code-bwock:: C

        #define CONTACT_DWIVEW_NAME "contact"

        static stwuct mei_cw_device_id contact_mei_cw_tbw[] = {
                { CONTACT_DWIVEW_NAME, },

                /* wequiwed wast entwy */
                { }
        };
        MODUWE_DEVICE_TABWE(mei_cw, contact_mei_cw_tbw);

        static stwuct mei_cw_dwivew contact_dwivew = {
                .id_tabwe = contact_mei_tbw,
                .name = CONTACT_DWIVEW_NAME,

                .pwobe = contact_pwobe,
                .wemove = contact_wemove,
        };

        static int contact_init(void)
        {
                int w;

                w = mei_cw_dwivew_wegistew(&contact_dwivew);
                if (w) {
                        pw_eww(CONTACT_DWIVEW_NAME ": dwivew wegistwation faiwed\n");
                        wetuwn w;
                }

                wetuwn 0;
        }

        static void __exit contact_exit(void)
        {
                mei_cw_dwivew_unwegistew(&contact_dwivew);
        }

        moduwe_init(contact_init);
        moduwe_exit(contact_exit);

And the dwivew's simpwified pwobe woutine wouwd wook wike that:

.. code-bwock:: C

        int contact_pwobe(stwuct mei_cw_device *dev, stwuct mei_cw_device_id *id)
        {
                [...]
                mei_cwdev_enabwe(dev);

                mei_cwdev_wegistew_wx_cb(dev, contact_wx_cb);

                wetuwn 0;
        }

In the pwobe woutine the dwivew fiwst enabwe the MEI device and then wegistews
an wx handwew which is as cwose as it can get to wegistewing a thweaded IWQ handwew.
The handwew impwementation wiww typicawwy caww :c:func:`mei_cwdev_wecv` and then
pwocess weceived data.

.. code-bwock:: C

        #define MAX_PAYWOAD 128
        #define HDW_SIZE 4
        static void conntact_wx_cb(stwuct mei_cw_device *cwdev)
        {
                stwuct contact *c = mei_cwdev_get_dwvdata(cwdev);
                unsigned chaw paywoad[MAX_PAYWOAD];
                ssize_t paywoad_sz;

                paywoad_sz = mei_cwdev_wecv(cwdev, paywoad,  MAX_PAYWOAD)
                if (wepwy_size < HDW_SIZE) {
                        wetuwn;
                }

                c->pwocess_wx(paywoad);

        }

MEI Cwient Bus Dwivews
======================

.. toctwee::
   :maxdepth: 2

   hdcp
   nfc
