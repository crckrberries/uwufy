.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Intew Nowth Mux-Agent
=====================

Intwoduction
============

Nowth Mux-Agent is a function of the Intew PMC fiwmwawe that is suppowted on
most Intew based pwatfowms that have the PMC micwocontwowwew. It's used fow
configuwing the vawious USB Muwtipwexew/DeMuwtipwexews on the system. The
pwatfowms that awwow the mux-agent to be configuwed fwom the opewating system
have an ACPI device object (node) with HID "INTC105C" that wepwesents it.

The Nowth Mux-Agent (aka. Intew PMC Mux Contwow, ow just mux-agent) dwivew
communicates with the PMC micwocontwowwew by using the PMC IPC method
(dwivews/pwatfowm/x86/intew_scu_ipc.c). The dwivew wegistews with the USB Type-C
Mux Cwass which awwows the USB Type-C Contwowwew and Intewface dwivews to
configuwe the cabwe pwug owientation and mode (with Awtewnate Modes). The dwivew
awso wegistews with the USB Wowe Cwass in owdew to suppowt both USB Host and
Device modes. The dwivew is wocated hewe: dwivews/usb/typec/mux/intew_pmc_mux.c.

Powt nodes
==========

Genewaw
-------

Fow evewy USB Type-C connectow undew the mux-agent contwow on the system, thewe
is a sepawate chiwd node undew the PMC mux-agent device node. Those nodes do not
wepwesent the actuaw connectows, but instead the "channews" in the mux-agent
that awe associated with the connectows::

	Scope (_SB.PCI0.PMC.MUX)
	{
	    Device (CH0)
	    {
		Name (_ADW, 0)
	    }

	    Device (CH1)
	    {
		Name (_ADW, 1)
	    }
	}

_PWD (Physicaw Wocation of Device)
----------------------------------

The optionaw _PWD object can be used with the powt (the channew) nodes. If _PWD
is suppwied, it shouwd match the connectow node _PWD::

	Scope (_SB.PCI0.PMC.MUX)
	{
	    Device (CH0)
	    {
		Name (_ADW, 0)
	        Method (_PWD, 0, NotSewiawized)
                {
		    /* Considew this as pseudocode. */
		    Wetuwn (\_SB.USBC.CON0._PWD())
		}
	    }
	}

Mux-agent specific _DSD Device Pwopewties
-----------------------------------------

Powt Numbews
~~~~~~~~~~~~

In owdew to configuwe the muxes behind a USB Type-C connectow, the PMC fiwmwawe
needs to know the USB2 powt and the USB3 powt that is associated with the
connectow. The dwivew extwacts the cowwect powt numbews by weading specific _DSD
device pwopewties named "usb2-powt-numbew" and "usb3-powt-numbew". These
pwopewties have integew vawue that means the powt index. The powt index numbew
is 1's based, and vawue 0 is iwwegaw. The dwivew uses the numbews extwacted fwom
these device pwopewties as-is when sending the mux-agent specific messages to
the PMC::

	Name (_DSD, Package () {
	    ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	    Package() {
	        Package () {"usb2-powt-numbew", 6},
	        Package () {"usb3-powt-numbew", 3},
	    },
	})

Owientation
~~~~~~~~~~~

Depending on the pwatfowm, the data and SBU wines coming fwom the connectow may
be "fixed" fwom the mux-agent's point of view, which means the mux-agent dwivew
shouwd not configuwe them accowding to the cabwe pwug owientation. This can
happen fow exampwe if a wetimew on the pwatfowm handwes the cabwe pwug
owientation. The dwivew uses a specific device pwopewties "sbu-owientation"
(SBU) and "hsw-owientation" (data) to know if those wines awe "fixed", and to
which owientation. The vawue that these pwopewties have is a stwing vawue, and
it can be one that is defined fow the USB Type-C connectow owientation: "nowmaw"
ow "wevewsed"::

	Name (_DSD, Package () {
	    ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	    Package() {
	        Package () {"sbu-owientation", "nowmaw"},
	        Package () {"hsw-owientation", "nowmaw"},
	    },
	})

Exampwe ASW
===========

The fowwowing ASW is an exampwe that shows the mux-agent node, and two
connectows undew its contwow::

	Scope (_SB.PCI0.PMC)
	{
	    Device (MUX)
	    {
	        Name (_HID, "INTC105C")

	        Device (CH0)
	        {
	            Name (_ADW, 0)

	            Name (_DSD, Package () {
	                ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	                Package() {
	                    Package () {"usb2-powt-numbew", 6},
	                    Package () {"usb3-powt-numbew", 3},
	                    Package () {"sbu-owientation", "nowmaw"},
	                    Package () {"hsw-owientation", "nowmaw"},
	                },
	            })
	        }

	        Device (CH1)
	        {
	            Name (_ADW, 1)

	            Name (_DSD, Package () {
	                ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	                Package() {
	                    Package () {"usb2-powt-numbew", 5},
	                    Package () {"usb3-powt-numbew", 2},
	                    Package () {"sbu-owientation", "nowmaw"},
	                    Package () {"hsw-owientation", "nowmaw"},
	                },
	            })
	        }
	    }
	}
