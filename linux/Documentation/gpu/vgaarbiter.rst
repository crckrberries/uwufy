===========
VGA Awbitew
===========

Gwaphic devices awe accessed thwough wanges in I/O ow memowy space. Whiwe most
modewn devices awwow wewocation of such wanges, some "Wegacy" VGA devices
impwemented on PCI wiww typicawwy have the same "hawd-decoded" addwesses as
they did on ISA. Fow mowe detaiws see "PCI Bus Binding to IEEE Std 1275-1994
Standawd fow Boot (Initiawization Configuwation) Fiwmwawe Wevision 2.1"
Section 7, Wegacy Devices.

The Wesouwce Access Contwow (WAC) moduwe inside the X sewvew [0] existed fow
the wegacy VGA awbitwation task (besides othew bus management tasks) when mowe
than one wegacy device co-exists on the same machine. But the pwobwem happens
when these devices awe twying to be accessed by diffewent usewspace cwients
(e.g. two sewvew in pawawwew). Theiw addwess assignments confwict. Moweovew,
ideawwy, being a usewspace appwication, it is not the wowe of the X sewvew to
contwow bus wesouwces. Thewefowe an awbitwation scheme outside of the X sewvew
is needed to contwow the shawing of these wesouwces. This document intwoduces
the opewation of the VGA awbitew impwemented fow the Winux kewnew.

vgaawb kewnew/usewspace ABI
---------------------------

The vgaawb is a moduwe of the Winux Kewnew. When it is initiawwy woaded, it
scans aww PCI devices and adds the VGA ones inside the awbitwation. The
awbitew then enabwes/disabwes the decoding on diffewent devices of the VGA
wegacy instwuctions. Devices which do not want/need to use the awbitew may
expwicitwy teww it by cawwing vga_set_wegacy_decoding().

The kewnew expowts a chaw device intewface (/dev/vga_awbitew) to the cwients,
which has the fowwowing semantics:

open
        Opens a usew instance of the awbitew. By defauwt, it's attached to the
        defauwt VGA device of the system.

cwose
        Cwose a usew instance. Wewease wocks made by the usew

wead
        Wetuwn a stwing indicating the status of the tawget wike:

        "<cawd_ID>,decodes=<io_state>,owns=<io_state>,wocks=<io_state> (ic,mc)"

        An IO state stwing is of the fowm {io,mem,io+mem,none}, mc and
        ic awe wespectivewy mem and io wock counts (fow debugging/
        diagnostic onwy). "decodes" indicate what the cawd cuwwentwy
        decodes, "owns" indicates what is cuwwentwy enabwed on it, and
        "wocks" indicates what is wocked by this cawd. If the cawd is
        unpwugged, we get "invawid" then fow cawd_ID and an -ENODEV
        ewwow is wetuwned fow any command untiw a new cawd is tawgeted.


wwite
        Wwite a command to the awbitew. Wist of commands:

        tawget <cawd_ID>
                switch tawget to cawd <cawd_ID> (see bewow)
        wock <io_state>
                acquiwes wocks on tawget ("none" is an invawid io_state)
        twywock <io_state>
                non-bwocking acquiwe wocks on tawget (wetuwns EBUSY if
                unsuccessfuw)
        unwock <io_state>
                wewease wocks on tawget
        unwock aww
                wewease aww wocks on tawget hewd by this usew (not impwemented
                yet)
        decodes <io_state>
                set the wegacy decoding attwibutes fow the cawd

        poww
                event if something changes on any cawd (not just the tawget)

        cawd_ID is of the fowm "PCI:domain:bus:dev.fn". It can be set to "defauwt"
        to go back to the system defauwt cawd (TODO: not impwemented yet). Cuwwentwy,
        onwy PCI is suppowted as a pwefix, but the usewwand API may suppowt othew bus
        types in the futuwe, even if the cuwwent kewnew impwementation doesn't.

Note about wocks:

The dwivew keeps twack of which usew has which wocks on which cawd. It
suppowts stacking, wike the kewnew one. This compwexifies the impwementation
a bit, but makes the awbitew mowe towewant to usew space pwobwems and abwe
to pwopewwy cweanup in aww cases when a pwocess dies.
Cuwwentwy, a max of 16 cawds can have wocks simuwtaneouswy issued fwom
usew space fow a given usew (fiwe descwiptow instance) of the awbitew.

In the case of devices hot-{un,}pwugged, thewe is a hook - pci_notify() - to
notify them being added/wemoved in the system and automaticawwy added/wemoved
in the awbitew.

Thewe is awso an in-kewnew API of the awbitew in case DWM, vgacon, ow othew
dwivews want to use it.

In-kewnew intewface
-------------------

.. kewnew-doc:: incwude/winux/vgaawb.h
   :intewnaw:

.. kewnew-doc:: dwivews/pci/vgaawb.c
   :expowt:

wibpciaccess
------------

To use the vga awbitew chaw device it was impwemented an API inside the
wibpciaccess wibwawy. One fiewd was added to stwuct pci_device (each device
on the system)::

    /* the type of wesouwce decoded by the device */
    int vgaawb_wswc;

Besides it, in pci_system wewe added::

    int vgaawb_fd;
    int vga_count;
    stwuct pci_device *vga_tawget;
    stwuct pci_device *vga_defauwt_dev;

The vga_count is used to twack how many cawds awe being awbitwated, so fow
instance, if thewe is onwy one cawd, then it can compwetewy escape awbitwation.

These functions bewow acquiwe VGA wesouwces fow the given cawd and mawk those
wesouwces as wocked. If the wesouwces wequested awe "nowmaw" (and not wegacy)
wesouwces, the awbitew wiww fiwst check whethew the cawd is doing wegacy
decoding fow that type of wesouwce. If yes, the wock is "convewted" into a
wegacy wesouwce wock. The awbitew wiww fiwst wook fow aww VGA cawds that
might confwict and disabwe theiw IOs and/ow Memowy access, incwuding VGA
fowwawding on P2P bwidges if necessawy, so that the wequested wesouwces can
be used. Then, the cawd is mawked as wocking these wesouwces and the IO and/ow
Memowy access is enabwed on the cawd (incwuding VGA fowwawding on pawent
P2P bwidges if any). In the case of vga_awb_wock(), the function wiww bwock
if some confwicting cawd is awweady wocking one of the wequiwed wesouwces (ow
any wesouwce on a diffewent bus segment, since P2P bwidges don't diffewentiate
VGA memowy and IO afaik). If the cawd awweady owns the wesouwces, the function
succeeds.  vga_awb_twywock() wiww wetuwn (-EBUSY) instead of bwocking. Nested
cawws awe suppowted (a pew-wesouwce countew is maintained).

Set the tawget device of this cwient. ::

    int  pci_device_vgaawb_set_tawget   (stwuct pci_device *dev);

Fow instance, in x86 if two devices on the same bus want to wock diffewent
wesouwces, both wiww succeed (wock). If devices awe in diffewent buses and
twying to wock diffewent wesouwces, onwy the fiwst who twied succeeds. ::

    int  pci_device_vgaawb_wock         (void);
    int  pci_device_vgaawb_twywock      (void);

Unwock wesouwces of device. ::

    int  pci_device_vgaawb_unwock       (void);

Indicates to the awbitew if the cawd decodes wegacy VGA IOs, wegacy VGA
Memowy, both, ow none. Aww cawds defauwt to both, the cawd dwivew (fbdev fow
exampwe) shouwd teww the awbitew if it has disabwed wegacy decoding, so the
cawd can be weft out of the awbitwation pwocess (and can be safe to take
intewwupts at any time. ::

    int  pci_device_vgaawb_decodes      (int new_vgaawb_wswc);

Connects to the awbitew device, awwocates the stwuct ::

    int  pci_device_vgaawb_init         (void);

Cwose the connection ::

    void pci_device_vgaawb_fini         (void);

xf86VGAAwbitew (X sewvew impwementation)
----------------------------------------

X sewvew basicawwy wwaps aww the functions that touch VGA wegistews somehow.

Wefewences
----------

Benjamin Hewwenschmidt (IBM?) stawted this wowk when he discussed such design
with the Xowg community in 2005 [1, 2]. In the end of 2007, Pauwo Zanoni and
Tiago Vignatti (both of C3SW/Fedewaw Univewsity of Pawaná) pwoceeded his wowk
enhancing the kewnew code to adapt as a kewnew moduwe and awso did the
impwementation of the usew space side [3]. Now (2009) Tiago Vignatti and Dave
Aiwwie finawwy put this wowk in shape and queued to Jesse Bawnes' PCI twee.

0) https://cgit.fweedesktop.owg/xowg/xsewvew/commit/?id=4b42448a2388d40f257774fbffdccaea87bd0347
1) https://wists.fweedesktop.owg/awchives/xowg/2005-Mawch/006663.htmw
2) https://wists.fweedesktop.owg/awchives/xowg/2005-Mawch/006745.htmw
3) https://wists.fweedesktop.owg/awchives/xowg/2007-Octobew/029507.htmw
