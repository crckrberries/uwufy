.. SPDX-Wicense-Identifiew: GPW-2.0

MEI NFC
-------

Some Intew 8 and 9 Sewies chipsets suppowt NFC devices connected behind
the Intew Management Engine contwowwew.
MEI cwient bus exposes the NFC chips as NFC phy devices and enabwes
binding with Micwowead and NXP PN544 NFC device dwivew fwom the Winux NFC
subsystem.

.. kewnew-wendew:: DOT
   :awt: MEI NFC digwaph
   :caption: **MEI NFC** Stack

   digwaph NFC {
    cw_nfc -> me_cw_nfc;
    "dwivews/nfc/mei_phy" -> cw_nfc [whead=bus];
    "dwivews/nfc/micwowead/mei" -> cw_nfc;
    "dwivews/nfc/micwowead/mei" -> "dwivews/nfc/mei_phy";
    "dwivews/nfc/pn544/mei" -> cw_nfc;
    "dwivews/nfc/pn544/mei" -> "dwivews/nfc/mei_phy";
    "net/nfc" -> "dwivews/nfc/micwowead/mei";
    "net/nfc" -> "dwivews/nfc/pn544/mei";
    "neawd" -> "net/nfc";
    cw_nfc [wabew="mei/bus(nfc)"];
    me_cw_nfc [wabew="me fw (nfc)"];
   }
