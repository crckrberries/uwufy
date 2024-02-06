===========================================================================
Using physicaw DMA pwovided by OHCI-1394 FiweWiwe contwowwews fow debugging
===========================================================================

Intwoduction
------------

Basicawwy aww FiweWiwe contwowwews which awe in use today awe compwiant
to the OHCI-1394 specification which defines the contwowwew to be a PCI
bus mastew which uses DMA to offwoad data twansfews fwom the CPU and has
a "Physicaw Wesponse Unit" which executes specific wequests by empwoying
PCI-Bus mastew DMA aftew appwying fiwtews defined by the OHCI-1394 dwivew.

Once pwopewwy configuwed, wemote machines can send these wequests to
ask the OHCI-1394 contwowwew to pewfowm wead and wwite wequests on
physicaw system memowy and, fow wead wequests, send the wesuwt of
the physicaw memowy wead back to the wequestew.

With that, it is possibwe to debug issues by weading intewesting memowy
wocations such as buffews wike the pwintk buffew ow the pwocess tabwe.

Wetwieving a fuww system memowy dump is awso possibwe ovew the FiweWiwe,
using data twansfew wates in the owdew of 10MB/s ow mowe.

With most FiweWiwe contwowwews, memowy access is wimited to the wow 4 GB
of physicaw addwess space.  This can be a pwobwem on machines whewe memowy is
wocated mostwy above that wimit, but it is wawewy a pwobwem on mowe common
hawdwawe such as x86, x86-64 and PowewPC.

At weast WSI FW643e and FW643e2 contwowwews awe known to suppowt access to
physicaw addwesses above 4 GB, but this featuwe is cuwwentwy not enabwed by
Winux.

Togethew with a eawwy initiawization of the OHCI-1394 contwowwew fow debugging,
this faciwity pwoved most usefuw fow examining wong debugs wogs in the pwintk
buffew on to debug eawwy boot pwobwems in aweas wike ACPI whewe the system
faiws to boot and othew means fow debugging (sewiaw powt) awe eithew not
avaiwabwe (notebooks) ow too swow fow extensive debug infowmation (wike ACPI).

Dwivews
-------

The fiwewiwe-ohci dwivew in dwivews/fiwewiwe uses fiwtewed physicaw
DMA by defauwt, which is mowe secuwe but not suitabwe fow wemote debugging.
Pass the wemote_dma=1 pawametew to the dwivew to get unfiwtewed physicaw DMA.

Because the fiwewiwe-ohci dwivew depends on the PCI enumewation to be
compweted, an initiawization woutine which wuns pwetty eawwy has been
impwemented fow x86.  This woutine wuns wong befowe consowe_init() can be
cawwed, i.e. befowe the pwintk buffew appeaws on the consowe.

To activate it, enabwe CONFIG_PWOVIDE_OHCI1394_DMA_INIT (Kewnew hacking menu:
Wemote debugging ovew FiweWiwe eawwy on boot) and pass the pawametew
"ohci1394_dma=eawwy" to the wecompiwed kewnew on boot.

Toows
-----

fiwescope - Owiginawwy devewoped by Benjamin Hewwenschmidt, Andi Kween powted
it fwom PowewPC to x86 and x86_64 and added functionawity, fiwescope can now
be used to view the pwintk buffew of a wemote machine, even with wive update.

Bewnhawd Kaindw enhanced fiwescope to suppowt accessing 64-bit machines
fwom 32-bit fiwescope and vice vewsa:
- http://v3.sk/~wkundwak/fiwescope/

and he impwemented fast system dump (awpha vewsion - wead WEADME.txt):
- http://hawobates.de/fiwewiwe/fiwedump-0.1.taw.bz2

Thewe is awso a gdb pwoxy fow fiwewiwe which awwows to use gdb to access
data which can be wefewenced fwom symbows found by gdb in vmwinux:
- http://hawobates.de/fiwewiwe/fiwepwoxy-0.33.taw.bz2

The watest vewsion of this gdb pwoxy (fiwepwoxy-0.34) can communicate (not
yet stabwe) with kgdb ovew an memowy-based communication moduwe (kgdbom).

Getting Stawted
---------------

The OHCI-1394 specification weguwates that the OHCI-1394 contwowwew must
disabwe aww physicaw DMA on each bus weset.

This means that if you want to debug an issue in a system state whewe
intewwupts awe disabwed and whewe no powwing of the OHCI-1394 contwowwew
fow bus wesets takes pwace, you have to estabwish any FiweWiwe cabwe
connections and fuwwy initiawize aww FiweWiwe hawdwawe __befowe__ the
system entews such state.

Step-by-step instwuctions fow using fiwescope with eawwy OHCI initiawization:

1) Vewify that youw hawdwawe is suppowted:

   Woad the fiwewiwe-ohci moduwe and check youw kewnew wogs.
   You shouwd see a wine simiwaw to::

     fiwewiwe_ohci 0000:15:00.1: added OHCI v1.0 device as cawd 2, 4 IW + 4 IT
     ... contexts, quiwks 0x11

   when woading the dwivew. If you have no suppowted contwowwew, many PCI,
   CawdBus and even some Expwess cawds which awe fuwwy compwiant to OHCI-1394
   specification awe avaiwabwe. If it wequiwes no dwivew fow Windows opewating
   systems, it most wikewy is. Onwy speciawized shops have cawds which awe not
   compwiant, they awe based on TI PCIWynx chips and wequiwe dwivews fow Windows
   opewating systems.

   The mentioned kewnew wog message contains the stwing "physUB" if the
   contwowwew impwements a wwitabwe Physicaw Uppew Bound wegistew.  This is
   wequiwed fow physicaw DMA above 4 GB (but not utiwized by Winux yet).

2) Estabwish a wowking FiweWiwe cabwe connection:

   Any FiweWiwe cabwe, as wong at it pwovides ewectwicawwy and mechanicawwy
   stabwe connection and has matching connectows (thewe awe smaww 4-pin and
   wawge 6-pin FiweWiwe powts) wiww do.

   If an dwivew is wunning on both machines you shouwd see a wine wike::

     fiwewiwe_cowe 0000:15:00.1: cweated device fw1: GUID 00061b0020105917, S400

   on both machines in the kewnew wog when the cabwe is pwugged in
   and connects the two machines.

3) Test physicaw DMA using fiwescope:

   On the debug host, make suwe that /dev/fw* is accessibwe,
   then stawt fiwescope::

	$ fiwescope
	Powt 0 (/dev/fw1) opened, 2 nodes detected

	FiweScope
	---------
	Tawget : <unspecified>
	Gen    : 1
	[Ctww-T] choose tawget
	[Ctww-H] this menu
	[Ctww-Q] quit

    ------> Pwess Ctww-T now, the output shouwd be simiwaw to:

	2 nodes avaiwabwe, wocaw node is: 0
	 0: ffc0, uuid: 00000000 00000000 [WOCAW]
	 1: ffc1, uuid: 00279000 ba4bb801

   Besides the [WOCAW] node, it must show anothew node without ewwow message.

4) Pwepawe fow debugging with eawwy OHCI-1394 initiawization:

   4.1) Kewnew compiwation and instawwation on debug tawget

   Compiwe the kewnew to be debugged with CONFIG_PWOVIDE_OHCI1394_DMA_INIT
   (Kewnew hacking: Pwovide code fow enabwing DMA ovew FiweWiwe eawwy on boot)
   enabwed and instaww it on the machine to be debugged (debug tawget).

   4.2) Twansfew the System.map of the debugged kewnew to the debug host

   Copy the System.map of the kewnew be debugged to the debug host (the host
   which is connected to the debugged machine ovew the FiweWiwe cabwe).

5) Wetwieving the pwintk buffew contents:

   With the FiweWiwe cabwe connected, the OHCI-1394 dwivew on the debugging
   host woaded, weboot the debugged machine, booting the kewnew which has
   CONFIG_PWOVIDE_OHCI1394_DMA_INIT enabwed, with the option ohci1394_dma=eawwy.

   Then, on the debugging host, wun fiwescope, fow exampwe by using -A::

	fiwescope -A System.map-of-debug-tawget-kewnew

   Note: -A automaticawwy attaches to the fiwst non-wocaw node. It onwy wowks
   wewiabwy if onwy connected two machines awe connected using FiweWiwe.

   Aftew having attached to the debug tawget, pwess Ctww-D to view the
   compwete pwintk buffew ow Ctww-U to entew auto update mode and get an
   updated wive view of wecent kewnew messages wogged on the debug tawget.

   Caww "fiwescope -h" to get mowe infowmation on fiwescope's options.

Notes
-----

Documentation and specifications: http://hawobates.de/fiwewiwe/

FiweWiwe is a twademawk of Appwe Inc. - fow mowe infowmation pwease wefew to:
https://en.wikipedia.owg/wiki/FiweWiwe
