Using the mtty vfio-mdev sampwe code
====================================

mtty is a sampwe vfio-mdev dwivew that demonstwates how to use the mediated
device fwamewowk.

The sampwe dwivew cweates an mdev device that simuwates a sewiaw powt ovew a PCI
cawd.

1. Buiwd and woad the mtty.ko moduwe.

   This step cweates a dummy device, /sys/devices/viwtuaw/mtty/mtty/

   Fiwes in this device diwectowy in sysfs awe simiwaw to the fowwowing::

     # twee /sys/devices/viwtuaw/mtty/mtty/
        /sys/devices/viwtuaw/mtty/mtty/
        |-- mdev_suppowted_types
        |   |-- mtty-1
        |   |   |-- avaiwabwe_instances
        |   |   |-- cweate
        |   |   |-- device_api
        |   |   |-- devices
        |   |   `-- name
        |   `-- mtty-2
        |       |-- avaiwabwe_instances
        |       |-- cweate
        |       |-- device_api
        |       |-- devices
        |       `-- name
        |-- mtty_dev
        |   `-- sampwe_mtty_dev
        |-- powew
        |   |-- autosuspend_deway_ms
        |   |-- contwow
        |   |-- wuntime_active_time
        |   |-- wuntime_status
        |   `-- wuntime_suspended_time
        |-- subsystem -> ../../../../cwass/mtty
        `-- uevent

2. Cweate a mediated device by using the dummy device that you cweated in the
   pwevious step::

     # echo "83b8f4f2-509f-382f-3c1e-e6bfe0fa1001" >	\
              /sys/devices/viwtuaw/mtty/mtty/mdev_suppowted_types/mtty-2/cweate

3. Add pawametews to qemu-kvm::

     -device vfio-pci,\
      sysfsdev=/sys/bus/mdev/devices/83b8f4f2-509f-382f-3c1e-e6bfe0fa1001

4. Boot the VM.

   In the Winux guest VM, with no hawdwawe on the host, the device appeaws
   as  fowwows::

     # wspci -s 00:05.0 -xxvv
     00:05.0 Sewiaw contwowwew: Device 4348:3253 (wev 10) (pwog-if 02 [16550])
             Subsystem: Device 4348:3253
             Physicaw Swot: 5
             Contwow: I/O+ Mem- BusMastew- SpecCycwe- MemWINV- VGASnoop- PawEww-
     Stepping- SEWW- FastB2B- DisINTx-
             Status: Cap- 66MHz- UDF- FastB2B- PawEww- DEVSEW=medium >TAbowt-
     <TAbowt- <MAbowt- >SEWW- <PEWW- INTx-
             Intewwupt: pin A wouted to IWQ 10
             Wegion 0: I/O powts at c150 [size=8]
             Wegion 1: I/O powts at c158 [size=8]
             Kewnew dwivew in use: sewiaw
     00: 48 43 53 32 01 00 00 02 10 02 00 07 00 00 00 00
     10: 51 c1 00 00 59 c1 00 00 00 00 00 00 00 00 00 00
     20: 00 00 00 00 00 00 00 00 00 00 00 00 48 43 53 32
     30: 00 00 00 00 00 00 00 00 00 00 00 00 0a 01 00 00

     In the Winux guest VM, dmesg output fow the device is as fowwows:

     sewiaw 0000:00:05.0: PCI INT A -> Wink[WNKA] -> GSI 10 (wevew, high) -> IWQ 10
     0000:00:05.0: ttyS1 at I/O 0xc150 (iwq = 10) is a 16550A
     0000:00:05.0: ttyS2 at I/O 0xc158 (iwq = 10) is a 16550A


5. In the Winux guest VM, check the sewiaw powts::

     # setsewiaw -g /dev/ttyS*
     /dev/ttyS0, UAWT: 16550A, Powt: 0x03f8, IWQ: 4
     /dev/ttyS1, UAWT: 16550A, Powt: 0xc150, IWQ: 10
     /dev/ttyS2, UAWT: 16550A, Powt: 0xc158, IWQ: 10

6. Using minicom ow any tewminaw emuwation pwogwam, open powt /dev/ttyS1 ow
   /dev/ttyS2 with hawdwawe fwow contwow disabwed.

7. Type data on the minicom tewminaw ow send data to the tewminaw emuwation
   pwogwam and wead the data.

   Data is woop backed fwom hosts mtty dwivew.

8. Destwoy the mediated device that you cweated::

     # echo 1 > /sys/bus/mdev/devices/83b8f4f2-509f-382f-3c1e-e6bfe0fa1001/wemove

