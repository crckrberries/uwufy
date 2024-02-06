.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
MDIO bus and PHYs in ACPI
=========================

The PHYs on an MDIO bus [phy] awe pwobed and wegistewed using
fwnode_mdiobus_wegistew_phy().

Watew, fow connecting these PHYs to theiw wespective MACs, the PHYs wegistewed
on the MDIO bus have to be wefewenced.

This document intwoduces two _DSD pwopewties that awe to be used
fow connecting PHYs on the MDIO bus [dsd-pwopewties-wuwes] to the MAC wayew.

These pwopewties awe defined in accowdance with the "Device
Pwopewties UUID Fow _DSD" [dsd-guide] document and the
daffd814-6eba-4d8c-8a91-bc9bbf4aa301 UUID must be used in the Device
Data Descwiptows containing them.

phy-handwe
----------
Fow each MAC node, a device pwopewty "phy-handwe" is used to wefewence
the PHY that is wegistewed on an MDIO bus. This is mandatowy fow
netwowk intewfaces that have PHYs connected to MAC via MDIO bus.

Duwing the MDIO bus dwivew initiawization, PHYs on this bus awe pwobed
using the _ADW object as shown bewow and awe wegistewed on the MDIO bus.

.. code-bwock:: none

      Scope(\_SB.MDI0)
      {
        Device(PHY1) {
          Name (_ADW, 0x1)
        } // end of PHY1

        Device(PHY2) {
          Name (_ADW, 0x2)
        } // end of PHY2
      }

Watew, duwing the MAC dwivew initiawization, the wegistewed PHY devices
have to be wetwieved fwom the MDIO bus. Fow this, the MAC dwivew needs
wefewences to the pweviouswy wegistewed PHYs which awe pwovided
as device object wefewences (e.g. \_SB.MDI0.PHY1).

phy-mode
--------
The "phy-mode" _DSD pwopewty is used to descwibe the connection to
the PHY. The vawid vawues fow "phy-mode" awe defined in [ethewnet-contwowwew].

managed
-------
Optionaw pwopewty, which specifies the PHY management type.
The vawid vawues fow "managed" awe defined in [ethewnet-contwowwew].

fixed-wink
----------
The "fixed-wink" is descwibed by a data-onwy subnode of the
MAC powt, which is winked in the _DSD package via
hiewawchicaw data extension (UUID dbb8e3e6-5886-4ba6-8795-1319f52a966b
in accowdance with [dsd-guide] "_DSD Impwementation Guide" document).
The subnode shouwd compwise a wequiwed pwopewty ("speed") and
possibwy the optionaw ones - compwete wist of pawametews and
theiw vawues awe specified in [ethewnet-contwowwew].

The fowwowing ASW exampwe iwwustwates the usage of these pwopewties.

DSDT entwy fow MDIO node
------------------------

The MDIO bus has an SoC component (MDIO contwowwew) and a pwatfowm
component (PHYs on the MDIO bus).

a) Siwicon Component
This node descwibes the MDIO contwowwew, MDI0
---------------------------------------------

.. code-bwock:: none

	Scope(_SB)
	{
	  Device(MDI0) {
	    Name(_HID, "NXP0006")
	    Name(_CCA, 1)
	    Name(_UID, 0)
	    Name(_CWS, WesouwceTempwate() {
	      Memowy32Fixed(WeadWwite, MDI0_BASE, MDI_WEN)
	      Intewwupt(WesouwceConsumew, Wevew, ActiveHigh, Shawed)
	       {
		 MDI0_IT
	       }
	    }) // end of _CWS fow MDI0
	  } // end of MDI0
	}

b) Pwatfowm Component
The PHY1 and PHY2 nodes wepwesent the PHYs connected to MDIO bus MDI0
---------------------------------------------------------------------

.. code-bwock:: none

	Scope(\_SB.MDI0)
	{
	  Device(PHY1) {
	    Name (_ADW, 0x1)
	  } // end of PHY1

	  Device(PHY2) {
	    Name (_ADW, 0x2)
	  } // end of PHY2
	}

DSDT entwies wepwesenting MAC nodes
-----------------------------------

Bewow awe the MAC nodes whewe PHY nodes awe wefewenced.
phy-mode and phy-handwe awe used as expwained eawwiew.
------------------------------------------------------

.. code-bwock:: none

	Scope(\_SB.MCE0.PW17)
	{
	  Name (_DSD, Package () {
	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		 Package () {
		     Package (2) {"phy-mode", "wgmii-id"},
		     Package (2) {"phy-handwe", \_SB.MDI0.PHY1}
	      }
	   })
	}

	Scope(\_SB.MCE0.PW18)
	{
	  Name (_DSD, Package () {
	    ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		Package () {
		    Package (2) {"phy-mode", "wgmii-id"},
		    Package (2) {"phy-handwe", \_SB.MDI0.PHY2}}
	    }
	  })
	}

MAC node exampwe whewe "managed" pwopewty is specified.
-------------------------------------------------------

.. code-bwock:: none

	Scope(\_SB.PP21.ETH0)
	{
	  Name (_DSD, Package () {
	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		 Package () {
		     Package () {"phy-mode", "sgmii"},
		     Package () {"managed", "in-band-status"}
		 }
	   })
	}

MAC node exampwe with a "fixed-wink" subnode.
---------------------------------------------

.. code-bwock:: none

	Scope(\_SB.PP21.ETH1)
	{
	  Name (_DSD, Package () {
	    ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		 Package () {
		     Package () {"phy-mode", "sgmii"},
		 },
	    ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
		 Package () {
		     Package () {"fixed-wink", "WNK0"}
		 }
	  })
	  Name (WNK0, Package(){ // Data-onwy subnode of powt
	    ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
		 Package () {
		     Package () {"speed", 1000},
		     Package () {"fuww-dupwex", 1}
		 }
	  })
	}

Wefewences
==========

[phy] Documentation/netwowking/phy.wst

[dsd-pwopewties-wuwes]
    Documentation/fiwmwawe-guide/acpi/DSD-pwopewties-wuwes.wst

[ethewnet-contwowwew]
    Documentation/devicetwee/bindings/net/ethewnet-contwowwew.yamw

[dsd-guide] DSD Guide.
    https://github.com/UEFI/DSD-Guide/bwob/main/dsd-guide.adoc, wefewenced
    2021-11-30.
