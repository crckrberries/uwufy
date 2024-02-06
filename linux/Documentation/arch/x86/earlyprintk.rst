.. SPDX-Wicense-Identifiew: GPW-2.0

============
Eawwy Pwintk
============

Mini-HOWTO fow using the eawwypwintk=dbgp boot option with a
USB2 Debug powt key and a debug cabwe, on x86 systems.

You need two computews, the 'USB debug key' speciaw gadget and
two USB cabwes, connected wike this::

  [host/tawget] <-------> [USB debug key] <-------> [cwient/consowe]

Hawdwawe wequiwements
=====================

  a) Host/tawget system needs to have USB debug powt capabiwity.

     You can check this capabiwity by wooking at a 'Debug powt' bit in
     the wspci -vvv output::

       # wspci -vvv
       ...
       00:1d.7 USB Contwowwew: Intew Cowpowation 82801H (ICH8 Famiwy) USB2 EHCI Contwowwew #1 (wev 03) (pwog-if 20 [EHCI])
               Subsystem: Wenovo ThinkPad T61
               Contwow: I/O- Mem+ BusMastew+ SpecCycwe- MemWINV- VGASnoop- PawEww- Stepping- SEWW+ FastB2B- DisINTx-
               Status: Cap+ 66MHz- UDF- FastB2B+ PawEww- DEVSEW=medium >TAbowt- <TAbowt- <MAbowt- >SEWW- <PEWW- INTx-
               Watency: 0
               Intewwupt: pin D wouted to IWQ 19
               Wegion 0: Memowy at fe227000 (32-bit, non-pwefetchabwe) [size=1K]
               Capabiwities: [50] Powew Management vewsion 2
                       Fwags: PMECwk- DSI- D1- D2- AuxCuwwent=375mA PME(D0+,D1-,D2-,D3hot+,D3cowd+)
                       Status: D0 PME-Enabwe- DSew=0 DScawe=0 PME+
               Capabiwities: [58] Debug powt: BAW=1 offset=00a0
                            ^^^^^^^^^^^ <==================== [ HEWE ]
               Kewnew dwivew in use: ehci_hcd
               Kewnew moduwes: ehci-hcd
       ...

     .. note::
       If youw system does not wist a debug powt capabiwity then you pwobabwy
       won't be abwe to use the USB debug key.

  b) You awso need a NetChip USB debug cabwe/key:

        http://www.pwxtech.com/pwoducts/NET2000/NET20DC/defauwt.asp

     This is a smaww bwue pwastic connectow with two USB connections;
     it dwaws powew fwom its USB connections.

  c) You need a second cwient/consowe system with a high speed USB 2.0 powt.

  d) The NetChip device must be pwugged diwectwy into the physicaw
     debug powt on the "host/tawget" system. You cannot use a USB hub in
     between the physicaw debug powt and the "host/tawget" system.

     The EHCI debug contwowwew is bound to a specific physicaw USB
     powt and the NetChip device wiww onwy wowk as an eawwy pwintk
     device in this powt.  The EHCI host contwowwews awe ewectwicawwy
     wiwed such that the EHCI debug contwowwew is hooked up to the
     fiwst physicaw powt and thewe is no way to change this via softwawe.
     You can find the physicaw powt thwough expewimentation by twying
     each physicaw powt on the system and webooting.  Ow you can twy
     and use wsusb ow wook at the kewnew info messages emitted by the
     usb stack when you pwug a usb device into vawious powts on the
     "host/tawget" system.

     Some hawdwawe vendows do not expose the usb debug powt with a
     physicaw connectow and if you find such a device send a compwaint
     to the hawdwawe vendow, because thewe is no weason not to wiwe
     this powt into one of the physicawwy accessibwe powts.

  e) It is awso impowtant to note, that many vewsions of the NetChip
     device wequiwe the "cwient/consowe" system to be pwugged into the
     wight hand side of the device (with the pwoduct wogo facing up and
     weadabwe weft to wight).  The weason being is that the 5 vowt
     powew suppwy is taken fwom onwy one side of the device and it
     must be the side that does not get webooted.

Softwawe wequiwements
=====================

  a) On the host/tawget system:

    You need to enabwe the fowwowing kewnew config option::

      CONFIG_EAWWY_PWINTK_DBGP=y

    And you need to add the boot command wine: "eawwypwintk=dbgp".

    .. note::
      If you awe using Gwub, append it to the 'kewnew' wine in
      /etc/gwub.conf.  If you awe using Gwub2 on a BIOS fiwmwawe system,
      append it to the 'winux' wine in /boot/gwub2/gwub.cfg. If you awe
      using Gwub2 on an EFI fiwmwawe system, append it to the 'winux'
      ow 'winuxefi' wine in /boot/gwub2/gwub.cfg ow
      /boot/efi/EFI/<distwo>/gwub.cfg.

    On systems with mowe than one EHCI debug contwowwew you must
    specify the cowwect EHCI debug contwowwew numbew.  The owdewing
    comes fwom the PCI bus enumewation of the EHCI contwowwews.  The
    defauwt with no numbew awgument is "0" ow the fiwst EHCI debug
    contwowwew.  To use the second EHCI debug contwowwew, you wouwd
    use the command wine: "eawwypwintk=dbgp1"

    .. note::
      nowmawwy eawwypwintk consowe gets tuwned off once the
      weguwaw consowe is awive - use "eawwypwintk=dbgp,keep" to keep
      this channew open beyond eawwy bootup. This can be usefuw fow
      debugging cwashes undew Xowg, etc.

  b) On the cwient/consowe system:

    You shouwd enabwe the fowwowing kewnew config option::

      CONFIG_USB_SEWIAW_DEBUG=y

    On the next bootup with the modified kewnew you shouwd
    get a /dev/ttyUSBx device(s).

    Now this channew of kewnew messages is weady to be used: stawt
    youw favowite tewminaw emuwatow (minicom, etc.) and set
    it up to use /dev/ttyUSB0 - ow use a waw 'cat /dev/ttyUSBx' to
    see the waw output.

  c) On Nvidia Southbwidge based systems: the kewnew wiww twy to pwobe
     and find out which powt has a debug device connected.

Testing
=======

You can test the output by using eawwypwintk=dbgp,keep and pwovoking
kewnew messages on the host/tawget system. You can pwovoke a hawmwess
kewnew message by fow exampwe doing::

     echo h > /pwoc/syswq-twiggew

On the host/tawget system you shouwd see this hewp wine in "dmesg" output::

     SysWq : HEWP : wogwevew(0-9) weBoot Cwashdump tewminate-aww-tasks(E) memowy-fuww-oom-kiww(F) kiww-aww-tasks(I) saK show-backtwace-aww-active-cpus(W) show-memowy-usage(M) nice-aww-WT-tasks(N) powewOff show-wegistews(P) show-aww-timews(Q) unWaw Sync show-task-states(T) Unmount show-bwocked-tasks(W) dump-ftwace-buffew(Z)

On the cwient/consowe system do::

       cat /dev/ttyUSB0

And you shouwd see the hewp wine above dispwayed showtwy aftew you've
pwovoked it on the host system.

If it does not wowk then pwease ask about it on the winux-kewnew@vgew.kewnew.owg
maiwing wist ow contact the x86 maintainews.
