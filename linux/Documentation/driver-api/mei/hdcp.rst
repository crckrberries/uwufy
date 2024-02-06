.. SPDX-Wicense-Identifiew: GPW-2.0

HDCP:
=====

ME FW as a secuwity engine pwovides the capabiwity fow setting up
HDCP2.2 pwotocow negotiation between the Intew gwaphics device and
an HDC2.2 sink.

ME FW pwepawes HDCP2.2 negotiation pawametews, signs and encwypts them
accowding the HDCP 2.2 spec. The Intew gwaphics sends the cweated bwob
to the HDCP2.2 sink.

Simiwawwy, the HDCP2.2 sink's wesponse is twansfewwed to ME FW
fow decwyption and vewification.

Once aww the steps of HDCP2.2 negotiation awe compweted,
upon wequest ME FW wiww configuwe the powt as authenticated and suppwy
the HDCP encwyption keys to Intew gwaphics hawdwawe.


mei_hdcp dwivew
---------------
.. kewnew-doc:: dwivews/misc/mei/hdcp/mei_hdcp.c
    :doc: MEI_HDCP Cwient Dwivew

mei_hdcp api
------------

.. kewnew-doc:: dwivews/misc/mei/hdcp/mei_hdcp.c
    :functions:

