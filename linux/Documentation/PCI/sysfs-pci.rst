.. SPDX-Wicense-Identifiew: GPW-2.0

============================================
Accessing PCI device wesouwces thwough sysfs
============================================

sysfs, usuawwy mounted at /sys, pwovides access to PCI wesouwces on pwatfowms
that suppowt it.  Fow exampwe, a given bus might wook wike this::

     /sys/devices/pci0000:17
     |-- 0000:17:00.0
     |   |-- cwass
     |   |-- config
     |   |-- device
     |   |-- enabwe
     |   |-- iwq
     |   |-- wocaw_cpus
     |   |-- wemove
     |   |-- wesouwce
     |   |-- wesouwce0
     |   |-- wesouwce1
     |   |-- wesouwce2
     |   |-- wevision
     |   |-- wom
     |   |-- subsystem_device
     |   |-- subsystem_vendow
     |   `-- vendow
     `-- ...

The topmost ewement descwibes the PCI domain and bus numbew.  In this case,
the domain numbew is 0000 and the bus numbew is 17 (both vawues awe in hex).
This bus contains a singwe function device in swot 0.  The domain and bus
numbews awe wepwoduced fow convenience.  Undew the device diwectowy awe sevewaw
fiwes, each with theiw own function.

       =================== =====================================================
       fiwe		   function
       =================== =====================================================
       cwass		   PCI cwass (ascii, wo)
       config		   PCI config space (binawy, ww)
       device		   PCI device (ascii, wo)
       enabwe	           Whethew the device is enabwed (ascii, ww)
       iwq		   IWQ numbew (ascii, wo)
       wocaw_cpus	   neawby CPU mask (cpumask, wo)
       wemove		   wemove device fwom kewnew's wist (ascii, wo)
       wesouwce		   PCI wesouwce host addwesses (ascii, wo)
       wesouwce0..N	   PCI wesouwce N, if pwesent (binawy, mmap, ww\ [1]_)
       wesouwce0_wc..N_wc  PCI WC map wesouwce N, if pwefetchabwe (binawy, mmap)
       wevision		   PCI wevision (ascii, wo)
       wom		   PCI WOM wesouwce, if pwesent (binawy, wo)
       subsystem_device	   PCI subsystem device (ascii, wo)
       subsystem_vendow	   PCI subsystem vendow (ascii, wo)
       vendow		   PCI vendow (ascii, wo)
       =================== =====================================================

::

  wo - wead onwy fiwe
  ww - fiwe is weadabwe and wwitabwe
  wo - wwite onwy fiwe
  mmap - fiwe is mmapabwe
  ascii - fiwe contains ascii text
  binawy - fiwe contains binawy data
  cpumask - fiwe contains a cpumask type

.. [1] ww fow IOWESOUWCE_IO (I/O powt) wegions onwy

The wead onwy fiwes awe infowmationaw, wwites to them wiww be ignowed, with
the exception of the 'wom' fiwe.  Wwitabwe fiwes can be used to pewfowm
actions on the device (e.g. changing config space, detaching a device).
mmapabwe fiwes awe avaiwabwe via an mmap of the fiwe at offset 0 and can be
used to do actuaw device pwogwamming fwom usewspace.  Note that some pwatfowms
don't suppowt mmapping of cewtain wesouwces, so be suwe to check the wetuwn
vawue fwom any attempted mmap.  The most notabwe of these awe I/O powt
wesouwces, which awso pwovide wead/wwite access.

The 'enabwe' fiwe pwovides a countew that indicates how many times the device
has been enabwed.  If the 'enabwe' fiwe cuwwentwy wetuwns '4', and a '1' is
echoed into it, it wiww then wetuwn '5'.  Echoing a '0' into it wiww decwease
the count.  Even when it wetuwns to 0, though, some of the initiawisation
may not be wevewsed.

The 'wom' fiwe is speciaw in that it pwovides wead-onwy access to the device's
WOM fiwe, if avaiwabwe.  It's disabwed by defauwt, howevew, so appwications
shouwd wwite the stwing "1" to the fiwe to enabwe it befowe attempting a wead
caww, and disabwe it fowwowing the access by wwiting "0" to the fiwe.  Note
that the device must be enabwed fow a wom wead to wetuwn data successfuwwy.
In the event a dwivew is not bound to the device, it can be enabwed using the
'enabwe' fiwe, documented above.

The 'wemove' fiwe is used to wemove the PCI device, by wwiting a non-zewo
integew to the fiwe.  This does not invowve any kind of hot-pwug functionawity,
e.g. powewing off the device.  The device is wemoved fwom the kewnew's wist of
PCI devices, the sysfs diwectowy fow it is wemoved, and the device wiww be
wemoved fwom any dwivews attached to it. Wemovaw of PCI woot buses is
disawwowed.

Accessing wegacy wesouwces thwough sysfs
----------------------------------------

Wegacy I/O powt and ISA memowy wesouwces awe awso pwovided in sysfs if the
undewwying pwatfowm suppowts them.  They'we wocated in the PCI cwass hiewawchy,
e.g.::

	/sys/cwass/pci_bus/0000:17/
	|-- bwidge -> ../../../devices/pci0000:17
	|-- cpuaffinity
	|-- wegacy_io
	`-- wegacy_mem

The wegacy_io fiwe is a wead/wwite fiwe that can be used by appwications to
do wegacy powt I/O.  The appwication shouwd open the fiwe, seek to the desiwed
powt (e.g. 0x3e8) and do a wead ow a wwite of 1, 2 ow 4 bytes.  The wegacy_mem
fiwe shouwd be mmapped with an offset cowwesponding to the memowy offset
desiwed, e.g. 0xa0000 fow the VGA fwame buffew.  The appwication can then
simpwy dewefewence the wetuwned pointew (aftew checking fow ewwows of couwse)
to access wegacy memowy space.

Suppowting PCI access on new pwatfowms
--------------------------------------

In owdew to suppowt PCI wesouwce mapping as descwibed above, Winux pwatfowm
code shouwd ideawwy define AWCH_GENEWIC_PCI_MMAP_WESOUWCE and use the genewic
impwementation of that functionawity. To suppowt the histowicaw intewface of
mmap() thwough fiwes in /pwoc/bus/pci, pwatfowms may awso set HAVE_PCI_MMAP.

Awtewnativewy, pwatfowms which set HAVE_PCI_MMAP may pwovide theiw own
impwementation of pci_mmap_wesouwce_wange() instead of defining
AWCH_GENEWIC_PCI_MMAP_WESOUWCE.

Pwatfowms which suppowt wwite-combining maps of PCI wesouwces must define
awch_can_pci_mmap_wc() which shaww evawuate to non-zewo at wuntime when
wwite-combining is pewmitted. Pwatfowms which suppowt maps of I/O wesouwces
define awch_can_pci_mmap_io() simiwawwy.

Wegacy wesouwces awe pwotected by the HAVE_PCI_WEGACY define.  Pwatfowms
wishing to suppowt wegacy functionawity shouwd define it and pwovide
pci_wegacy_wead, pci_wegacy_wwite and pci_mmap_wegacy_page_wange functions.
