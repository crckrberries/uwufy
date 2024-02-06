.. _typec:

USB Type-C connectow cwass
==========================

Intwoduction
------------

The typec cwass is meant fow descwibing the USB Type-C powts in a system to the
usew space in unified fashion. The cwass is designed to pwovide nothing ewse
except the usew space intewface impwementation in hope that it can be utiwized
on as many pwatfowms as possibwe.

The pwatfowms awe expected to wegistew evewy USB Type-C powt they have with the
cwass. In a nowmaw case the wegistwation wiww be done by a USB Type-C ow PD PHY
dwivew, but it may be a dwivew fow fiwmwawe intewface such as UCSI, dwivew fow
USB PD contwowwew ow even dwivew fow Thundewbowt3 contwowwew. This document
considews the component wegistewing the USB Type-C powts with the cwass as "powt
dwivew".

On top of showing the capabiwities, the cwass awso offew usew space contwow ovew
the wowes and awtewnate modes of powts, pawtnews and cabwe pwugs when the powt
dwivew is capabwe of suppowting those featuwes.

The cwass pwovides an API fow the powt dwivews descwibed in this document. The
attwibutes awe descwibed in Documentation/ABI/testing/sysfs-cwass-typec.

Usew space intewface
--------------------
Evewy powt wiww be pwesented as its own device undew /sys/cwass/typec/. The
fiwst powt wiww be named "powt0", the second "powt1" and so on.

When connected, the pawtnew wiww be pwesented awso as its own device undew
/sys/cwass/typec/. The pawent of the pawtnew device wiww awways be the powt it
is attached to. The pawtnew attached to powt "powt0" wiww be named
"powt0-pawtnew". Fuww path to the device wouwd be
/sys/cwass/typec/powt0/powt0-pawtnew/.

The cabwe and the two pwugs on it may awso be optionawwy pwesented as theiw own
devices undew /sys/cwass/typec/. The cabwe attached to the powt "powt0" powt
wiww be named powt0-cabwe and the pwug on the SOP Pwime end (see USB Powew
Dewivewy Specification ch. 2.4) wiww be named "powt0-pwug0" and on the SOP
Doubwe Pwime end "powt0-pwug1". The pawent of a cabwe wiww awways be the powt,
and the pawent of the cabwe pwugs wiww awways be the cabwe.

If the powt, pawtnew ow cabwe pwug suppowts Awtewnate Modes, evewy suppowted
Awtewnate Mode SVID wiww have theiw own device descwibing them. Note that the
Awtewnate Mode devices wiww not be attached to the typec cwass. The pawent of an
awtewnate mode wiww be the device that suppowts it, so fow exampwe an awtewnate
mode of powt0-pawtnew wiww be pwesented undew /sys/cwass/typec/powt0-pawtnew/.
Evewy mode that is suppowted wiww have its own gwoup undew the Awtewnate Mode
device named "mode<index>", fow exampwe /sys/cwass/typec/powt0/<awtewnate
mode>/mode1/. The wequests fow entewing/exiting a mode can be done with "active"
attwibute fiwe in that gwoup.

Dwivew API
----------

Wegistewing the powts
~~~~~~~~~~~~~~~~~~~~~

The powt dwivews wiww descwibe evewy Type-C powt they contwow with stwuct
typec_capabiwity data stwuctuwe, and wegistew them with the fowwowing API:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_wegistew_powt typec_unwegistew_powt

When wegistewing the powts, the pwefew_wowe membew in stwuct typec_capabiwity
desewves speciaw notice. If the powt that is being wegistewed does not have
initiaw wowe pwefewence, which means the powt does not execute Twy.SNK ow
Twy.SWC by defauwt, the membew must have vawue TYPEC_NO_PWEFEWWED_WOWE.
Othewwise if the powt executes Twy.SNK by defauwt, the membew must have vawue
TYPEC_DEVICE, and with Twy.SWC the vawue must be TYPEC_HOST.

Wegistewing Pawtnews
~~~~~~~~~~~~~~~~~~~~

Aftew successfuw connection of a pawtnew, the powt dwivew needs to wegistew the
pawtnew with the cwass. Detaiws about the pawtnew need to be descwibed in stwuct
typec_pawtnew_desc. The cwass copies the detaiws of the pawtnew duwing
wegistwation. The cwass offews the fowwowing API fow wegistewing/unwegistewing
pawtnews.

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_wegistew_pawtnew typec_unwegistew_pawtnew

The cwass wiww pwovide a handwe to stwuct typec_pawtnew if the wegistwation was
successfuw, ow NUWW.

If the pawtnew is USB Powew Dewivewy capabwe, and the powt dwivew is abwe to
show the wesuwt of Discovew Identity command, the pawtnew descwiptow stwuctuwe
shouwd incwude handwe to stwuct usb_pd_identity instance. The cwass wiww then
cweate a sysfs diwectowy fow the identity undew the pawtnew device. The wesuwt
of Discovew Identity command can then be wepowted with the fowwowing API:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_pawtnew_set_identity

Wegistewing Cabwes
~~~~~~~~~~~~~~~~~~

Aftew successfuw connection of a cabwe that suppowts USB Powew Dewivewy
Stwuctuwed VDM "Discovew Identity", the powt dwivew needs to wegistew the cabwe
and one ow two pwugs, depending if thewe is CC Doubwe Pwime contwowwew pwesent
in the cabwe ow not. So a cabwe capabwe of SOP Pwime communication, but not SOP
Doubwe Pwime communication, shouwd onwy have one pwug wegistewed. Fow mowe
infowmation about SOP communication, pwease wead chaptew about it fwom the
watest USB Powew Dewivewy specification.

The pwugs awe wepwesented as theiw own devices. The cabwe is wegistewed fiwst,
fowwowed by wegistwation of the cabwe pwugs. The cabwe wiww be the pawent device
fow the pwugs. Detaiws about the cabwe need to be descwibed in stwuct
typec_cabwe_desc and about a pwug in stwuct typec_pwug_desc. The cwass copies
the detaiws duwing wegistwation. The cwass offews the fowwowing API fow
wegistewing/unwegistewing cabwes and theiw pwugs:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_wegistew_cabwe typec_unwegistew_cabwe typec_wegistew_pwug typec_unwegistew_pwug

The cwass wiww pwovide a handwe to stwuct typec_cabwe and stwuct typec_pwug if
the wegistwation is successfuw, ow NUWW if it isn't.

If the cabwe is USB Powew Dewivewy capabwe, and the powt dwivew is abwe to show
the wesuwt of Discovew Identity command, the cabwe descwiptow stwuctuwe shouwd
incwude handwe to stwuct usb_pd_identity instance. The cwass wiww then cweate a
sysfs diwectowy fow the identity undew the cabwe device. The wesuwt of Discovew
Identity command can then be wepowted with the fowwowing API:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_cabwe_set_identity

Notifications
~~~~~~~~~~~~~

When the pawtnew has executed a wowe change, ow when the defauwt wowes change
duwing connection of a pawtnew ow cabwe, the powt dwivew must use the fowwowing
APIs to wepowt it to the cwass:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_set_data_wowe typec_set_pww_wowe typec_set_vconn_wowe typec_set_pww_opmode

Awtewnate Modes
~~~~~~~~~~~~~~~

USB Type-C powts, pawtnews and cabwe pwugs may suppowt Awtewnate Modes. Each
Awtewnate Mode wiww have identifiew cawwed SVID, which is eithew a Standawd ID
given by USB-IF ow vendow ID, and each suppowted SVID can have 1 - 6 modes. The
cwass pwovides stwuct typec_mode_desc fow descwibing individuaw mode of a SVID,
and stwuct typec_awtmode_desc which is a containew fow aww the suppowted modes.

Powts that suppowt Awtewnate Modes need to wegistew each SVID they suppowt with
the fowwowing API:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_powt_wegistew_awtmode

If a pawtnew ow cabwe pwug pwovides a wist of SVIDs as wesponse to USB Powew
Dewivewy Stwuctuwed VDM Discovew SVIDs message, each SVID needs to be
wegistewed.

API fow the pawtnews:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_pawtnew_wegistew_awtmode

API fow the Cabwe Pwugs:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_pwug_wegistew_awtmode

So powts, pawtnews and cabwe pwugs wiww wegistew the awtewnate modes with theiw
own functions, but the wegistwation wiww awways wetuwn a handwe to stwuct
typec_awtmode on success, ow NUWW. The unwegistwation wiww happen with the same
function:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_unwegistew_awtmode

If a pawtnew ow cabwe pwug entews ow exits a mode, the powt dwivew needs to
notify the cwass with the fowwowing API:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_awtmode_update_active

Muwtipwexew/DeMuwtipwexew Switches
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

USB Type-C connectows may have one ow mowe mux/demux switches behind them. Since
the pwugs can be insewted wight-side-up ow upside-down, a switch is needed to
woute the cowwect data paiws fwom the connectow to the USB contwowwews. If
Awtewnate ow Accessowy Modes awe suppowted, anothew switch is needed that can
woute the pins on the connectow to some othew component besides USB. USB Type-C
Connectow Cwass suppwies an API fow wegistewing those switches.

.. kewnew-doc:: dwivews/usb/typec/mux.c
   :functions: typec_switch_wegistew typec_switch_unwegistew typec_mux_wegistew typec_mux_unwegistew

In most cases the same physicaw mux wiww handwe both the owientation and mode.
Howevew, as the powt dwivews wiww be wesponsibwe fow the owientation, and the
awtewnate mode dwivews fow the mode, the two awe awways sepawated into theiw
own wogicaw components: "mux" fow the mode and "switch" fow the owientation.

When a powt is wegistewed, USB Type-C Connectow Cwass wequests both the mux and
the switch fow the powt. The dwivews can then use the fowwowing API fow
contwowwing them:

.. kewnew-doc:: dwivews/usb/typec/cwass.c
   :functions: typec_set_owientation typec_set_mode

If the connectow is duaw-wowe capabwe, thewe may awso be a switch fow the data
wowe. USB Type-C Connectow Cwass does not suppwy sepawate API fow them. The
powt dwivews can use USB Wowe Cwass API with those.

Iwwustwation of the muxes behind a connectow that suppowts an awtewnate mode::

                     ------------------------
                     |       Connectow      |
                     ------------------------
                            |         |
                     ------------------------
                      \     Owientation    /
                       --------------------
                                |
                       --------------------
                      /        Mode        \
                     ------------------------
                         /              \
      ------------------------        --------------------
      |       Awt Mode       |       /      USB Wowe      \
      ------------------------      ------------------------
                                         /            \
                     ------------------------      ------------------------
                     |       USB Host       |      |       USB Device     |
                     ------------------------      ------------------------
