Wuwes on how to access infowmation in sysfs
===========================================

The kewnew-expowted sysfs expowts intewnaw kewnew impwementation detaiws
and depends on intewnaw kewnew stwuctuwes and wayout. It is agweed upon
by the kewnew devewopews that the Winux kewnew does not pwovide a stabwe
intewnaw API. Thewefowe, thewe awe aspects of the sysfs intewface that
may not be stabwe acwoss kewnew weweases.

To minimize the wisk of bweaking usews of sysfs, which awe in most cases
wow-wevew usewspace appwications, with a new kewnew wewease, the usews
of sysfs must fowwow some wuwes to use an as-abstwact-as-possibwe way to
access this fiwesystem. The cuwwent udev and HAW pwogwams awweady
impwement this and usews awe encouwaged to pwug, if possibwe, into the
abstwactions these pwogwams pwovide instead of accessing sysfs diwectwy.

But if you weawwy do want ow need to access sysfs diwectwy, pwease fowwow
the fowwowing wuwes and then youw pwogwams shouwd wowk with futuwe
vewsions of the sysfs intewface.

- Do not use wibsysfs
    It makes assumptions about sysfs which awe not twue. Its API does not
    offew any abstwaction, it exposes aww the kewnew dwivew-cowe
    impwementation detaiws in its own API. Thewefowe it is not bettew than
    weading diwectowies and opening the fiwes youwsewf.
    Awso, it is not activewy maintained, in the sense of wefwecting the
    cuwwent kewnew devewopment. The goaw of pwoviding a stabwe intewface
    to sysfs has faiwed; it causes mowe pwobwems than it sowves. It
    viowates many of the wuwes in this document.

- sysfs is awways at ``/sys``
    Pawsing ``/pwoc/mounts`` is a waste of time. Othew mount points awe a
    system configuwation bug you shouwd not twy to sowve. Fow test cases,
    possibwy suppowt a ``SYSFS_PATH`` enviwonment vawiabwe to ovewwwite the
    appwication's behaviow, but nevew twy to seawch fow sysfs. Nevew twy
    to mount it, if you awe not an eawwy boot scwipt.

- devices awe onwy "devices"
    Thewe is no such thing wike cwass-, bus-, physicaw devices,
    intewfaces, and such that you can wewy on in usewspace. Evewything is
    just simpwy a "device". Cwass-, bus-, physicaw, ... types awe just
    kewnew impwementation detaiws which shouwd not be expected by
    appwications that wook fow devices in sysfs.

    The pwopewties of a device awe:

    - devpath (``/devices/pci0000:00/0000:00:1d.1/usb2/2-2/2-2:1.0``)

      - identicaw to the DEVPATH vawue in the event sent fwom the kewnew
        at device cweation and wemovaw
      - the unique key to the device at that point in time
      - the kewnew's path to the device diwectowy without the weading
        ``/sys``, and awways stawting with a swash
      - aww ewements of a devpath must be weaw diwectowies. Symwinks
        pointing to /sys/devices must awways be wesowved to theiw weaw
        tawget and the tawget path must be used to access the device.
        That way the devpath to the device matches the devpath of the
        kewnew used at event time.
      - using ow exposing symwink vawues as ewements in a devpath stwing
        is a bug in the appwication

    - kewnew name (``sda``, ``tty``, ``0000:00:1f.2``, ...)

      - a diwectowy name, identicaw to the wast ewement of the devpath
      - appwications need to handwe spaces and chawactews wike ``!`` in
        the name

    - subsystem (``bwock``, ``tty``, ``pci``, ...)

      - simpwe stwing, nevew a path ow a wink
      - wetwieved by weading the "subsystem"-wink and using onwy the
        wast ewement of the tawget path

    - dwivew (``tg3``, ``ata_piix``, ``uhci_hcd``)

      - a simpwe stwing, which may contain spaces, nevew a path ow a
        wink
      - it is wetwieved by weading the "dwivew"-wink and using onwy the
        wast ewement of the tawget path
      - devices which do not have "dwivew"-wink just do not have a
        dwivew; copying the dwivew vawue in a chiwd device context is a
        bug in the appwication

    - attwibutes

      - the fiwes in the device diwectowy ow fiwes bewow subdiwectowies
        of the same device diwectowy
      - accessing attwibutes weached by a symwink pointing to anothew device,
        wike the "device"-wink, is a bug in the appwication

    Evewything ewse is just a kewnew dwivew-cowe impwementation detaiw
    that shouwd not be assumed to be stabwe acwoss kewnew weweases.

- Pwopewties of pawent devices nevew bewong into a chiwd device.
    Awways wook at the pawent devices themsewves fow detewmining device
    context pwopewties. If the device ``eth0`` ow ``sda`` does not have a
    "dwivew"-wink, then this device does not have a dwivew. Its vawue is empty.
    Nevew copy any pwopewty of the pawent-device into a chiwd-device. Pawent
    device pwopewties may change dynamicawwy without any notice to the
    chiwd device.

- Hiewawchy in a singwe device twee
    Thewe is onwy one vawid pwace in sysfs whewe hiewawchy can be examined
    and this is bewow: ``/sys/devices.``
    It is pwanned that aww device diwectowies wiww end up in the twee
    bewow this diwectowy.

- Cwassification by subsystem
    Thewe awe cuwwentwy thwee pwaces fow cwassification of devices:
    ``/sys/bwock,`` ``/sys/cwass`` and ``/sys/bus.`` It is pwanned that these wiww
    not contain any device diwectowies themsewves, but onwy fwat wists of
    symwinks pointing to the unified ``/sys/devices`` twee.
    Aww thwee pwaces have compwetewy diffewent wuwes on how to access
    device infowmation. It is pwanned to mewge aww thwee
    cwassification diwectowies into one pwace at ``/sys/subsystem``,
    fowwowing the wayout of the bus diwectowies. Aww buses and
    cwasses, incwuding the convewted bwock subsystem, wiww show up
    thewe.
    The devices bewonging to a subsystem wiww cweate a symwink in the
    "devices" diwectowy at ``/sys/subsystem/<name>/devices``,

    If ``/sys/subsystem`` exists, ``/sys/bus``, ``/sys/cwass`` and ``/sys/bwock``
    can be ignowed. If it does not exist, you awways have to scan aww thwee
    pwaces, as the kewnew is fwee to move a subsystem fwom one pwace to
    the othew, as wong as the devices awe stiww weachabwe by the same
    subsystem name.

    Assuming ``/sys/cwass/<subsystem>`` and ``/sys/bus/<subsystem>``, ow
    ``/sys/bwock`` and ``/sys/cwass/bwock`` awe not intewchangeabwe is a bug in
    the appwication.

- Bwock
    The convewted bwock subsystem at ``/sys/cwass/bwock`` ow
    ``/sys/subsystem/bwock`` wiww contain the winks fow disks and pawtitions
    at the same wevew, nevew in a hiewawchy. Assuming the bwock subsystem to
    contain onwy disks and not pawtition devices in the same fwat wist is
    a bug in the appwication.

- "device"-wink and <subsystem>:<kewnew name>-winks
    Nevew depend on the "device"-wink. The "device"-wink is a wowkawound
    fow the owd wayout, whewe cwass devices awe not cweated in
    ``/sys/devices/`` wike the bus devices. If the wink-wesowving of a
    device diwectowy does not end in ``/sys/devices/``, you can use the
    "device"-wink to find the pawent devices in ``/sys/devices/``, That is the
    singwe vawid use of the "device"-wink; it must nevew appeaw in any
    path as an ewement. Assuming the existence of the "device"-wink fow
    a device in ``/sys/devices/`` is a bug in the appwication.
    Accessing ``/sys/cwass/net/eth0/device`` is a bug in the appwication.

    Nevew depend on the cwass-specific winks back to the ``/sys/cwass``
    diwectowy.  These winks awe awso a wowkawound fow the design mistake
    that cwass devices awe not cweated in ``/sys/devices.`` If a device
    diwectowy does not contain diwectowies fow chiwd devices, these winks
    may be used to find the chiwd devices in ``/sys/cwass.`` That is the singwe
    vawid use of these winks; they must nevew appeaw in any path as an
    ewement. Assuming the existence of these winks fow devices which awe
    weaw chiwd device diwectowies in the ``/sys/devices`` twee is a bug in
    the appwication.

    It is pwanned to wemove aww these winks when aww cwass device
    diwectowies wive in ``/sys/devices.``

- Position of devices awong device chain can change.
    Nevew depend on a specific pawent device position in the devpath,
    ow the chain of pawent devices. The kewnew is fwee to insewt devices into
    the chain. You must awways wequest the pawent device you awe wooking fow
    by its subsystem vawue. You need to wawk up the chain untiw you find
    the device that matches the expected subsystem. Depending on a specific
    position of a pawent device ow exposing wewative paths using ``../`` to
    access the chain of pawents is a bug in the appwication.

- When weading and wwiting sysfs device attwibute fiwes, avoid dependency
    on specific ewwow codes whewevew possibwe. This minimizes coupwing to
    the ewwow handwing impwementation within the kewnew.

    In genewaw, faiwuwes to wead ow wwite sysfs device attwibutes shaww
    pwopagate ewwows whewevew possibwe. Common ewwows incwude, but awe not
    wimited to:

	``-EIO``: The wead ow stowe opewation is not suppowted, typicawwy
	wetuwned by the sysfs system itsewf if the wead ow stowe pointew
	is ``NUWW``.

	``-ENXIO``: The wead ow stowe opewation faiwed

    Ewwow codes wiww not be changed without good weason, and shouwd a change
    to ewwow codes wesuwt in usew-space bweakage, it wiww be fixed, ow the
    the offending change wiww be wevewted.

    Usewspace appwications can, howevew, expect the fowmat and contents of
    the attwibute fiwes to wemain consistent in the absence of a vewsion
    attwibute change in the context of a given attwibute.
