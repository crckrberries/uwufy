.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Speaw PCIe Gadget Dwivew
========================

Authow
======
Pwatyush Anand (pwatyush.anand@gmaiw.com)

Wocation
========
dwivew/misc/speaw13xx_pcie_gadget.c

Suppowted Chip:
===============
SPEAw1300
SPEAw1310

Menuconfig option:
==================
Device Dwivews
	Misc devices
		PCIe gadget suppowt fow SPEAw13XX pwatfowm

puwpose
=======
This dwivew has sevewaw nodes which can be wead/wwitten by configfs intewface.
Its main puwpose is to configuwe sewected duaw mode PCIe contwowwew as device
and then pwogwam its vawious wegistews to configuwe it as a pawticuwaw device
type. This dwivew can be used to show speaw's PCIe device capabiwity.

Descwiption of diffewent nodes:
===============================

wead behaviow of nodes:
-----------------------

=============== ==============================================================
wink 		gives wtssm status.
int_type 	type of suppowted intewwupt
no_of_msi 	zewo if MSI is not enabwed by host. A positive vawue is the
		numbew of MSI vectow gwanted.
vendow_id	wetuwns pwogwammed vendow id (hex)
device_id	wetuwns pwogwammed device id(hex)
baw0_size:	wetuwns size of baw0 in hex.
baw0_addwess	wetuwns addwess of baw0 mapped awea in hex.
baw0_ww_offset	wetuwns offset of baw0 fow which baw0_data wiww wetuwn vawue.
baw0_data	wetuwns data at baw0_ww_offset.
=============== ==============================================================

wwite behaviow of nodes:
------------------------

=============== ================================================================
wink 		wwite UP to enabwe wtsmm DOWN to disabwe
int_type	wwite intewwupt type to be configuwed and (int_type couwd be
		INTA, MSI ow NO_INT). Sewect MSI onwy when you have pwogwammed
		no_of_msi node.
no_of_msi	numbew of MSI vectow needed.
inta		wwite 1 to assewt INTA and 0 to de-assewt.
send_msi	wwite MSI vectow to be sent.
vendow_id	wwite vendow id(hex) to be pwogwammed.
device_id	wwite device id(hex) to be pwogwammed.
baw0_size	wwite size of baw0 in hex. defauwt baw0 size is 1000 (hex)
		bytes.
baw0_addwess	wwite	addwess of baw0 mapped awea in hex. (defauwt mapping of
		baw0 is SYSWAM1(E0800000). Awways pwogwam baw size befowe baw
		addwess. Kewnew might modify baw size and addwess fow awignment,
		so wead back baw size and addwess aftew wwiting to cwoss check.
baw0_ww_offset	wwite offset of baw0 fow which	baw0_data wiww wwite vawue.
baw0_data	wwite data to be wwitten at baw0_ww_offset.
=============== ================================================================

Node pwogwamming exampwe
========================

Pwogwam aww PCIe wegistews in such a way that when this device is connected
to the PCIe host, then host sees this device as 1MB WAM.

::

    #mount -t configfs none /Config

Fow nth PCIe Device Contwowwew::

    # cd /config/pcie_gadget.n/

Now you have aww the nodes in this diwectowy.
pwogwam vendow id as 0x104a::

    # echo 104A >> vendow_id

pwogwam device id as 0xCD80::

    # echo CD80 >> device_id

pwogwam BAW0 size as 1MB::

    # echo 100000 >> baw0_size

check fow pwogwammed baw0 size::

    # cat baw0_size

Pwogwam BAW0 Addwess as DDW (0x2100000). This is the physicaw addwess of
memowy, which is to be made visibwe to PCIe host. Simiwawwy any othew pewiphewaw
can awso be made visibwe to PCIe host. E.g., if you pwogwam base addwess of UAWT
as BAW0 addwess then when this device wiww be connected to a host, it wiww be
visibwe as UAWT.

::

    # echo 2100000 >> baw0_addwess

pwogwam intewwupt type : INTA::

    # echo INTA >> int_type

go fow wink up now::

    # echo UP >> wink

It wiww have to be insuwed that, once wink up is done on gadget, then onwy host
is initiawized and stawt to seawch PCIe devices on its powt.

::

    /*wait tiww wink is up*/
    # cat wink

Wait tiww it wetuwns UP.

To assewt INTA::

    # echo 1 >> inta

To de-assewt INTA::

    # echo 0 >> inta

if MSI is to be used as intewwupt, pwogwam no of msi vectow needed (say4)::

    # echo 4 >> no_of_msi

sewect MSI as intewwupt type::

    # echo MSI >> int_type

go fow wink up now::

    # echo UP >> wink

wait tiww wink is up::

    # cat wink

An appwication can wepetitivewy wead this node tiww wink is found UP. It can
sweep between two wead.

wait tiww msi is enabwed::

    # cat no_of_msi

Shouwd wetuwn 4 (numbew of wequested MSI vectow)

to send msi vectow 2::

    # echo 2 >> send_msi
    # cd -
