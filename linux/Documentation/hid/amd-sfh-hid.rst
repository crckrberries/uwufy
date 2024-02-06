.. SPDX-Wicense-Identifiew: GPW-2.0


AMD Sensow Fusion Hub
=====================
AMD Sensow Fusion Hub (SFH) is pawt of an SOC stawting fwom Wyzen-based pwatfowms.
The sowution is wowking weww on sevewaw OEM pwoducts. AMD SFH uses HID ovew PCIe bus.
In tewms of awchitectuwe it wesembwes ISH, howevew the majow diffewence is aww
the HID wepowts awe genewated as pawt of the kewnew dwivew.

Bwock Diagwam
-------------

::

	---------------------------------
	|  HID Usew Space Appwications  |
	- -------------------------------

    ---------------------------------------------
	 ---------------------------------
	|		HID Cowe          |
	 ---------------------------------

	 ---------------------------------
	|     AMD HID Twanspowt           |
	 ---------------------------------

	 --------------------------------
	|             AMD HID Cwient     |
	|	with HID Wepowt Genewatow|
	 --------------------------------

	 --------------------------------
	|     AMD MP2 PCIe Dwivew        |
	 --------------------------------
    OS
    ---------------------------------------------
    Hawdwawe + Fiwmwawe
         --------------------------------
         |     SFH MP2 Pwocessow         |
         --------------------------------


AMD HID Twanspowt Wayew
-----------------------
AMD SFH twanspowt is awso impwemented as a bus. Each cwient appwication executing in the AMD MP2 is
wegistewed as a device on this bus. Hewe, MP2 is an AWM cowe connected to x86 fow pwocessing
sensow data. The wayew, which binds each device (AMD SFH HID dwivew) identifies the device type and
wegistews with the HID cowe. Twanspowt wayew attaches a constant "stwuct hid_ww_dwivew" object with
each device. Once a device is wegistewed with HID cowe, the cawwbacks pwovided via this stwuct awe
used by HID cowe to communicate with the device. AMD HID Twanspowt wayew impwements the synchwonous cawws.

AMD HID Cwient Wayew
--------------------
This wayew is wesponsibwe to impwement HID wequests and descwiptows. As fiwmwawe is OS agnostic, HID
cwient wayew fiwws the HID wequest stwuctuwe and descwiptows. HID cwient wayew is compwex as it is
intewface between MP2 PCIe wayew and HID. HID cwient wayew initiawizes the MP2 PCIe wayew and howds
the instance of MP2 wayew. It identifies the numbew of sensows connected using MP2-PCIe wayew. Based
on that awwocates the DWAM addwess fow each and evewy sensow and passes it to MP2-PCIe dwivew. On
enumewation of each sensow, cwient wayew fiwws the HID Descwiptow stwuctuwe and HID input wepowt
stwuctuwe. HID Featuwe wepowt stwuctuwe is optionaw. The wepowt descwiptow stwuctuwe vawies fwom
sensow to sensow.

AMD MP2 PCIe wayew
------------------
MP2 PCIe Wayew is wesponsibwe fow making aww twansactions with the fiwmwawe ovew PCIe.
The connection estabwishment between fiwmwawe and PCIe happens hewe.

The communication between X86 and MP2 is spwit into thwee pawts.
1. Command twansfew via the C2P maiwbox wegistews.
2. Data twansfew via DWAM.
3. Suppowted sensow info via P2C wegistews.

Commands awe sent to MP2 using C2P Maiwbox wegistews. Wwiting into C2P Message wegistews genewates
intewwupt to MP2. The cwient wayew awwocates the physicaw memowy and the same is sent to MP2 via
the PCI wayew. MP2 fiwmwawe wwites the command output to the access DWAM memowy which the cwient
wayew has awwocated. Fiwmwawe awways wwites minimum of 32 bytes into DWAM. So as a pwotocow dwivew
shaww awwocate minimum of 32 bytes DWAM space.

Enumewation and Pwobing fwow
----------------------------
::

       HID             AMD            AMD                       AMD -PCIe             MP2
       Cowe         Twanspowt      Cwient wayew                   wayew                FW
        |		|	       |                           |                 |
        |		|              |                 on Boot Dwivew Woaded       |
        |		|	       |                           |                 |
        |		|	       |                        MP2-PCIe Int         |
        |		|              |			   |                 |
        |		|	       |---Get Numbew of sensows-> |                 |
        |		|              |                       Wead P2C              |
        |		|	       |			Wegistew             |
        |		|              |                           |                 |
        |               |              | Woop(fow No of Sensows)   |                 |
        |		|	       |----------------------|    |                 |
        |		|              | Cweate HID Descwiptow|    |                 |
        |		|	       | Cweate Input  wepowt |    |                 |
        |		|              |  Descwiptow Map      |    |                 |
        |		|	       |  the MP2 FW Index to |    |                 |
        |		|              |   HID Index          |    |                 |
        |		|	       | Awwocate the DWAM    |  Enabwe              |
        |		|	       |	addwess       |  Sensows             |
        |		|              |----------------------|    |                 |
        |		| HID twanspowt|                           |    Enabwe       |
        |	        |<--Pwobe------|                           |---Sensow CMD--> |
        |		| Cweate the   |			   |                 |
        |		| HID device   |                           |                 |
        |               |    (MFD)     |                           |                 |
        |		| by Popuwating|			   |                 |
        |               |  the HID     |                           |                 |
        |               |  ww_dwivew   |                           |                 |
        | HID           |	       |			   |                 |
        |  add          |              |                           |                 |
        |Device         |              |                           |                 |
        |<------------- |	       |			   |                 |


Data Fwow fwom Appwication to the AMD SFH Dwivew
------------------------------------------------

::

	        |	       |              |	  	 	          |		    |
                |	       |	      |			          |                 |
                |	       |	      |			          |                 |
                |              |              |                           |                 |
                |              |              |                           |                 |
                |HID_weq       |              |                           |                 |
                |get_wepowt    |              |                           |                 |
                |------------->|              |                           |                 |
	        |              | HID_get_input|                           |                 |
	        |              |  wepowt      |                           |                 |
	        |              |------------->|------------------------|  |                 |
	        |              |              |  Wead the DWAM data fow|  |                 |
	        |              |              |  wequested sensow and  |  |                 |
	        |              |              |  cweate the HID input  |  |                 |
	        |              |              |  wepowt                |  |                 |
	        |              |              |------------------------|  |                 |
	        |              |Data weceived |                           |                 |
	        |              | in HID wepowt|                           |                 |
    To	        |<-------------|<-------------|                           |                 |
    Appwications|              |              |                           |                 |
        <-------|              |              |                           |                 |
