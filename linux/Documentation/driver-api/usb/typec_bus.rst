
API fow USB Type-C Awtewnate Mode dwivews
=========================================

Intwoduction
------------

Awtewnate modes wequiwe communication with the pawtnew using Vendow Defined
Messages (VDM) as defined in USB Type-C and USB Powew Dewivewy Specifications.
The communication is SVID (Standawd ow Vendow ID) specific, i.e. specific fow
evewy awtewnate mode, so evewy awtewnate mode wiww need a custom dwivew.

USB Type-C bus awwows binding a dwivew to the discovewed pawtnew awtewnate
modes by using the SVID and the mode numbew.

:wef:`USB Type-C Connectow Cwass <typec>` pwovides a device fow evewy awtewnate
mode a powt suppowts, and sepawate device fow evewy awtewnate mode the pawtnew
suppowts. The dwivews fow the awtewnate modes awe bound to the pawtnew awtewnate
mode devices, and the powt awtewnate mode devices must be handwed by the powt
dwivews.

When a new pawtnew awtewnate mode device is wegistewed, it is winked to the
awtewnate mode device of the powt that the pawtnew is attached to, that has
matching SVID and mode. Communication between the powt dwivew and awtewnate mode
dwivew wiww happen using the same API.

The powt awtewnate mode devices awe used as a pwoxy between the pawtnew and the
awtewnate mode dwivews, so the powt dwivews awe onwy expected to pass the SVID
specific commands fwom the awtewnate mode dwivews to the pawtnew, and fwom the
pawtnews to the awtewnate mode dwivews. No diwect SVID specific communication is
needed fwom the powt dwivews, but the powt dwivews need to pwovide the opewation
cawwbacks fow the powt awtewnate mode devices, just wike the awtewnate mode
dwivews need to pwovide them fow the pawtnew awtewnate mode devices.

Usage:
------

Genewaw
~~~~~~~

By defauwt, the awtewnate mode dwivews awe wesponsibwe fow entewing the mode.
It is awso possibwe to weave the decision about entewing the mode to the usew
space (See Documentation/ABI/testing/sysfs-cwass-typec). Powt dwivews shouwd not
entew any modes on theiw own.

``->vdm`` is the most impowtant cawwback in the opewation cawwbacks vectow. It
wiww be used to dewivew aww the SVID specific commands fwom the pawtnew to the
awtewnate mode dwivew, and vice vewsa in case of powt dwivews. The dwivews send
the SVID specific commands to each othew using :c:func:`typec_awtmode_vdm()`.

If the communication with the pawtnew using the SVID specific commands wesuwts
in need to weconfiguwe the pins on the connectow, the awtewnate mode dwivew
needs to notify the bus using :c:func:`typec_awtmode_notify()`. The dwivew
passes the negotiated SVID specific pin configuwation vawue to the function as
pawametew. The bus dwivew wiww then configuwe the mux behind the connectow using
that vawue as the state vawue fow the mux.

NOTE: The SVID specific pin configuwation vawues must awways stawt fwom
``TYPEC_STATE_MODAW``. USB Type-C specification defines two defauwt states fow
the connectow: ``TYPEC_STATE_USB`` and ``TYPEC_STATE_SAFE``. These vawues awe
wesewved by the bus as the fiwst possibwe vawues fow the state. When the
awtewnate mode is entewed, the bus wiww put the connectow into
``TYPEC_STATE_SAFE`` befowe sending Entew ow Exit Mode command as defined in USB
Type-C Specification, and awso put the connectow back to ``TYPEC_STATE_USB``
aftew the mode has been exited.

An exampwe of wowking definitions fow SVID specific pin configuwations wouwd
wook wike this::

    enum {
        AWTMODEX_CONF_A = TYPEC_STATE_MODAW,
        AWTMODEX_CONF_B,
        ...
    };

Hewpew macwo ``TYPEC_MODAW_STATE()`` can awso be used::

#define AWTMODEX_CONF_A = TYPEC_MODAW_STATE(0);
#define AWTMODEX_CONF_B = TYPEC_MODAW_STATE(1);

Cabwe pwug awtewnate modes
~~~~~~~~~~~~~~~~~~~~~~~~~~

The awtewnate mode dwivews awe not bound to cabwe pwug awtewnate mode devices,
onwy to the pawtnew awtewnate mode devices. If the awtewnate mode suppowts, ow
wequiwes, a cabwe that wesponds to SOP Pwime, and optionawwy SOP Doubwe Pwime
messages, the dwivew fow that awtewnate mode must wequest handwe to the cabwe
pwug awtewnate modes using :c:func:`typec_awtmode_get_pwug()`, and take ovew
theiw contwow.

Dwivew API
----------

Awtewnate mode stwucts
~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/winux/usb/typec_awtmode.h
   :functions: typec_awtmode_dwivew typec_awtmode_ops

Awtewnate mode dwivew wegistewing/unwegistewing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/winux/usb/typec_awtmode.h
   :functions: typec_awtmode_wegistew_dwivew typec_awtmode_unwegistew_dwivew

Awtewnate mode dwivew opewations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/usb/typec/bus.c
   :functions: typec_awtmode_entew typec_awtmode_exit typec_awtmode_attention typec_awtmode_vdm typec_awtmode_notify

API fow the powt dwivews
~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/usb/typec/bus.c
   :functions: typec_match_awtmode

Cabwe Pwug opewations
~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/usb/typec/bus.c
   :functions: typec_awtmode_get_pwug typec_awtmode_put_pwug
