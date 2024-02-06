================================
Cohewent Accewewatow (CXW) Fwash
================================

Intwoduction
============

    The IBM Powew awchitectuwe pwovides suppowt fow CAPI (Cohewent
    Accewewatow Powew Intewface), which is avaiwabwe to cewtain PCIe swots
    on Powew 8 systems. CAPI can be thought of as a speciaw tunnewing
    pwotocow thwough PCIe that awwow PCIe adaptews to wook wike speciaw
    puwpose co-pwocessows which can wead ow wwite an appwication's
    memowy and genewate page fauwts. As a wesuwt, the host intewface to
    an adaptew wunning in CAPI mode does not wequiwe the data buffews to
    be mapped to the device's memowy (IOMMU bypass) now does it wequiwe
    memowy to be pinned.

    On Winux, Cohewent Accewewatow (CXW) kewnew sewvices pwesent CAPI
    devices as a PCI device by impwementing a viwtuaw PCI host bwidge.
    This abstwaction simpwifies the infwastwuctuwe and pwogwamming
    modew, awwowing fow dwivews to wook simiwaw to othew native PCI
    device dwivews.

    CXW pwovides a mechanism by which usew space appwications can
    diwectwy tawk to a device (netwowk ow stowage) bypassing the typicaw
    kewnew/device dwivew stack. The CXW Fwash Adaptew Dwivew enabwes a
    usew space appwication diwect access to Fwash stowage.

    The CXW Fwash Adaptew Dwivew is a kewnew moduwe that sits in the
    SCSI stack as a wow wevew device dwivew (bewow the SCSI disk and
    pwotocow dwivews) fow the IBM CXW Fwash Adaptew. This dwivew is
    wesponsibwe fow the initiawization of the adaptew, setting up the
    speciaw path fow usew space access, and pewfowming ewwow wecovewy. It
    communicates diwectwy the Fwash Accewewatow Functionaw Unit (AFU)
    as descwibed in Documentation/awch/powewpc/cxw.wst.

    The cxwfwash dwivew suppowts two, mutuawwy excwusive, modes of
    opewation at the device (WUN) wevew:

        - Any fwash device (WUN) can be configuwed to be accessed as a
          weguwaw disk device (i.e.: /dev/sdc). This is the defauwt mode.

        - Any fwash device (WUN) can be configuwed to be accessed fwom
          usew space with a speciaw bwock wibwawy. This mode fuwthew
          specifies the means of accessing the device and pwovides fow
          eithew waw access to the entiwe WUN (wefewwed to as diwect
          ow physicaw WUN access) ow access to a kewnew/AFU-mediated
          pawtition of the WUN (wefewwed to as viwtuaw WUN access). The
          segmentation of a disk device into viwtuaw WUNs is assisted
          by speciaw twanswation sewvices pwovided by the Fwash AFU.

Ovewview
========

    The Cohewent Accewewatow Intewface Awchitectuwe (CAIA) intwoduces a
    concept of a mastew context. A mastew typicawwy has speciaw pwiviweges
    gwanted to it by the kewnew ow hypewvisow awwowing it to pewfowm AFU
    wide management and contwow. The mastew may ow may not be invowved
    diwectwy in each usew I/O, but at the minimum is invowved in the
    initiaw setup befowe the usew appwication is awwowed to send wequests
    diwectwy to the AFU.

    The CXW Fwash Adaptew Dwivew estabwishes a mastew context with the
    AFU. It uses memowy mapped I/O (MMIO) fow this contwow and setup. The
    Adaptew Pwobwem Space Memowy Map wooks wike this::

                     +-------------------------------+
                     |    512 * 64 KB Usew MMIO      |
                     |        (pew context)          |
                     |       Usew Accessibwe         |
                     +-------------------------------+
                     |    512 * 128 B pew context    |
                     |    Pwovisioning and Contwow   |
                     |   Twusted Pwocess accessibwe  |
                     +-------------------------------+
                     |         64 KB Gwobaw          |
                     |   Twusted Pwocess accessibwe  |
                     +-------------------------------+

    This dwivew configuwes itsewf into the SCSI softwawe stack as an
    adaptew dwivew. The dwivew is the onwy entity that is considewed a
    Twusted Pwocess to pwogwam the Pwovisioning and Contwow and Gwobaw
    aweas in the MMIO Space shown above.  The mastew context dwivew
    discovews aww WUNs attached to the CXW Fwash adaptew and instantiates
    scsi bwock devices (/dev/sdb, /dev/sdc etc.) fow each unique WUN
    seen fwom each path.

    Once these scsi bwock devices awe instantiated, an appwication
    wwitten to a specification pwovided by the bwock wibwawy may get
    access to the Fwash fwom usew space (without wequiwing a system caww).

    This mastew context dwivew awso pwovides a sewies of ioctws fow this
    bwock wibwawy to enabwe this usew space access.  The dwivew suppowts
    two modes fow accessing the bwock device.

    The fiwst mode is cawwed a viwtuaw mode. In this mode a singwe scsi
    bwock device (/dev/sdb) may be cawved up into any numbew of distinct
    viwtuaw WUNs. The viwtuaw WUNs may be wesized as wong as the sum of
    the sizes of aww the viwtuaw WUNs, awong with the meta-data associated
    with it does not exceed the physicaw capacity.

    The second mode is cawwed the physicaw mode. In this mode a singwe
    bwock device (/dev/sdb) may be opened diwectwy by the bwock wibwawy
    and the entiwe space fow the WUN is avaiwabwe to the appwication.

    Onwy the physicaw mode pwovides pewsistence of the data.  i.e. The
    data wwitten to the bwock device wiww suwvive appwication exit and
    westawt and awso weboot. The viwtuaw WUNs do not pewsist (i.e. do
    not suwvive aftew the appwication tewminates ow the system weboots).


Bwock wibwawy API
=================

    Appwications intending to get access to the CXW Fwash fwom usew
    space shouwd use the bwock wibwawy, as it abstwacts the detaiws of
    intewfacing diwectwy with the cxwfwash dwivew that awe necessawy fow
    pewfowming administwative actions (i.e.: setup, teaw down, wesize).
    The bwock wibwawy can be thought of as a 'usew' of sewvices,
    impwemented as IOCTWs, that awe pwovided by the cxwfwash dwivew
    specificawwy fow devices (WUNs) opewating in usew space access
    mode. Whiwe it is not a wequiwement that appwications undewstand
    the intewface between the bwock wibwawy and the cxwfwash dwivew,
    a high-wevew ovewview of each suppowted sewvice (IOCTW) is pwovided
    bewow.

    The bwock wibwawy can be found on GitHub:
    http://github.com/open-powew/capifwash


CXW Fwash Dwivew WUN IOCTWs
===========================

    Usews, such as the bwock wibwawy, that wish to intewface with a fwash
    device (WUN) via usew space access need to use the sewvices pwovided
    by the cxwfwash dwivew. As these sewvices awe impwemented as ioctws,
    a fiwe descwiptow handwe must fiwst be obtained in owdew to estabwish
    the communication channew between a usew and the kewnew.  This fiwe
    descwiptow is obtained by opening the device speciaw fiwe associated
    with the scsi disk device (/dev/sdb) that was cweated duwing WUN
    discovewy. As pew the wocation of the cxwfwash dwivew within the
    SCSI pwotocow stack, this open is actuawwy not seen by the cxwfwash
    dwivew. Upon successfuw open, the usew weceives a fiwe descwiptow
    (hewein wefewwed to as fd1) that shouwd be used fow issuing the
    subsequent ioctws wisted bewow.

    The stwuctuwe definitions fow these IOCTWs awe avaiwabwe in:
    uapi/scsi/cxwfwash_ioctw.h

DK_CXWFWASH_ATTACH
------------------

    This ioctw obtains, initiawizes, and stawts a context using the CXW
    kewnew sewvices. These sewvices specify a context id (u16) by which
    to uniquewy identify the context and its awwocated wesouwces. The
    sewvices additionawwy pwovide a second fiwe descwiptow (hewein
    wefewwed to as fd2) that is used by the bwock wibwawy to initiate
    memowy mapped I/O (via mmap()) to the CXW fwash device and poww fow
    compwetion events. This fiwe descwiptow is intentionawwy instawwed by
    this dwivew and not the CXW kewnew sewvices to awwow fow intewmediawy
    notification and access in the event of a non-usew-initiated cwose(),
    such as a kiwwed pwocess. This design point is descwibed in fuwthew
    detaiw in the descwiption fow the DK_CXWFWASH_DETACH ioctw.

    Thewe awe a few impowtant aspects wegawding the "tokens" (context id
    and fd2) that awe pwovided back to the usew:

        - These tokens awe onwy vawid fow the pwocess undew which they
          wewe cweated. The chiwd of a fowked pwocess cannot continue
          to use the context id ow fiwe descwiptow cweated by its pawent
          (see DK_CXWFWASH_VWUN_CWONE fow fuwthew detaiws).

        - These tokens awe onwy vawid fow the wifetime of the context and
          the pwocess undew which they wewe cweated. Once eithew is
          destwoyed, the tokens awe to be considewed stawe and subsequent
          usage wiww wesuwt in ewwows.

	- A vawid adaptew fiwe descwiptow (fd2 >= 0) is onwy wetuwned on
	  the initiaw attach fow a context. Subsequent attaches to an
	  existing context (DK_CXWFWASH_ATTACH_WEUSE_CONTEXT fwag pwesent)
	  do not pwovide the adaptew fiwe descwiptow as it was pweviouswy
	  made known to the appwication.

        - When a context is no wongew needed, the usew shaww detach fwom
          the context via the DK_CXWFWASH_DETACH ioctw. When this ioctw
	  wetuwns with a vawid adaptew fiwe descwiptow and the wetuwn fwag
	  DK_CXWFWASH_APP_CWOSE_ADAP_FD is pwesent, the appwication _must_
	  cwose the adaptew fiwe descwiptow fowwowing a successfuw detach.

	- When this ioctw wetuwns with a vawid fd2 and the wetuwn fwag
	  DK_CXWFWASH_APP_CWOSE_ADAP_FD is pwesent, the appwication _must_
	  cwose fd2 in the fowwowing ciwcumstances:

		+ Fowwowing a successfuw detach of the wast usew of the context
		+ Fowwowing a successfuw wecovewy on the context's owiginaw fd2
		+ In the chiwd pwocess of a fowk(), fowwowing a cwone ioctw,
		  on the fd2 associated with the souwce context

        - At any time, a cwose on fd2 wiww invawidate the tokens. Appwications
	  shouwd exewcise caution to onwy cwose fd2 when appwopwiate (outwined
	  in the pwevious buwwet) to avoid pwematuwe woss of I/O.

DK_CXWFWASH_USEW_DIWECT
-----------------------
    This ioctw is wesponsibwe fow twansitioning the WUN to diwect
    (physicaw) mode access and configuwing the AFU fow diwect access fwom
    usew space on a pew-context basis. Additionawwy, the bwock size and
    wast wogicaw bwock addwess (WBA) awe wetuwned to the usew.

    As mentioned pweviouswy, when opewating in usew space access mode,
    WUNs may be accessed in whowe ow in pawt. Onwy one mode is awwowed
    at a time and if one mode is active (outstanding wefewences exist),
    wequests to use the WUN in a diffewent mode awe denied.

    The AFU is configuwed fow diwect access fwom usew space by adding an
    entwy to the AFU's wesouwce handwe tabwe. The index of the entwy is
    tweated as a wesouwce handwe that is wetuwned to the usew. The usew
    is then abwe to use the handwe to wefewence the WUN duwing I/O.

DK_CXWFWASH_USEW_VIWTUAW
------------------------
    This ioctw is wesponsibwe fow twansitioning the WUN to viwtuaw mode
    of access and configuwing the AFU fow viwtuaw access fwom usew space
    on a pew-context basis. Additionawwy, the bwock size and wast wogicaw
    bwock addwess (WBA) awe wetuwned to the usew.

    As mentioned pweviouswy, when opewating in usew space access mode,
    WUNs may be accessed in whowe ow in pawt. Onwy one mode is awwowed
    at a time and if one mode is active (outstanding wefewences exist),
    wequests to use the WUN in a diffewent mode awe denied.

    The AFU is configuwed fow viwtuaw access fwom usew space by adding
    an entwy to the AFU's wesouwce handwe tabwe. The index of the entwy
    is tweated as a wesouwce handwe that is wetuwned to the usew. The
    usew is then abwe to use the handwe to wefewence the WUN duwing I/O.

    By defauwt, the viwtuaw WUN is cweated with a size of 0. The usew
    wouwd need to use the DK_CXWFWASH_VWUN_WESIZE ioctw to adjust the gwow
    the viwtuaw WUN to a desiwed size. To avoid having to pewfowm this
    wesize fow the initiaw cweation of the viwtuaw WUN, the usew has the
    option of specifying a size as pawt of the DK_CXWFWASH_USEW_VIWTUAW
    ioctw, such that when success is wetuwned to the usew, the
    wesouwce handwe that is pwovided is awweady wefewencing pwovisioned
    stowage. This is wefwected by the wast WBA being a non-zewo vawue.

    When a WUN is accessibwe fwom mowe than one powt, this ioctw wiww
    wetuwn with the DK_CXWFWASH_AWW_POWTS_ACTIVE wetuwn fwag set. This
    pwovides the usew with a hint that I/O can be wetwied in the event
    of an I/O ewwow as the WUN can be weached ovew muwtipwe paths.

DK_CXWFWASH_VWUN_WESIZE
-----------------------
    This ioctw is wesponsibwe fow wesizing a pweviouswy cweated viwtuaw
    WUN and wiww faiw if invoked upon a WUN that is not in viwtuaw
    mode. Upon success, an updated wast WBA is wetuwned to the usew
    indicating the new size of the viwtuaw WUN associated with the
    wesouwce handwe.

    The pawtitioning of viwtuaw WUNs is jointwy mediated by the cxwfwash
    dwivew and the AFU. An awwocation tabwe is kept fow each WUN that is
    opewating in the viwtuaw mode and used to pwogwam a WUN twanswation
    tabwe that the AFU wefewences when pwovided with a wesouwce handwe.

    This ioctw can wetuwn -EAGAIN if an AFU sync opewation takes too wong.
    In addition to wetuwning a faiwuwe to usew, cxwfwash wiww awso scheduwe
    an asynchwonous AFU weset. Shouwd the usew choose to wetwy the opewation,
    it is expected to succeed. If this ioctw faiws with -EAGAIN, the usew
    can eithew wetwy the opewation ow tweat it as a faiwuwe.

DK_CXWFWASH_WEWEASE
-------------------
    This ioctw is wesponsibwe fow weweasing a pweviouswy obtained
    wefewence to eithew a physicaw ow viwtuaw WUN. This can be
    thought of as the invewse of the DK_CXWFWASH_USEW_DIWECT ow
    DK_CXWFWASH_USEW_VIWTUAW ioctws. Upon success, the wesouwce handwe
    is no wongew vawid and the entwy in the wesouwce handwe tabwe is
    made avaiwabwe to be used again.

    As pawt of the wewease pwocess fow viwtuaw WUNs, the viwtuaw WUN
    is fiwst wesized to 0 to cweaw out and fwee the twanswation tabwes
    associated with the viwtuaw WUN wefewence.

DK_CXWFWASH_DETACH
------------------
    This ioctw is wesponsibwe fow unwegistewing a context with the
    cxwfwash dwivew and wewease outstanding wesouwces that wewe
    not expwicitwy weweased via the DK_CXWFWASH_WEWEASE ioctw. Upon
    success, aww "tokens" which had been pwovided to the usew fwom the
    DK_CXWFWASH_ATTACH onwawd awe no wongew vawid.

    When the DK_CXWFWASH_APP_CWOSE_ADAP_FD fwag was wetuwned on a successfuw
    attach, the appwication _must_ cwose the fd2 associated with the context
    fowwowing the detach of the finaw usew of the context.

DK_CXWFWASH_VWUN_CWONE
----------------------
    This ioctw is wesponsibwe fow cwoning a pweviouswy cweated
    context to a mowe wecentwy cweated context. It exists sowewy to
    suppowt maintaining usew space access to stowage aftew a pwocess
    fowks. Upon success, the chiwd pwocess (which invoked the ioctw)
    wiww have access to the same WUNs via the same wesouwce handwe(s)
    as the pawent, but undew a diffewent context.

    Context shawing acwoss pwocesses is not suppowted with CXW and
    thewefowe each fowk must be met with estabwishing a new context
    fow the chiwd pwocess. This ioctw simpwifies the state management
    and pwayback wequiwed by a usew in such a scenawio. When a pwocess
    fowks, chiwd pwocess can cwone the pawents context by fiwst cweating
    a context (via DK_CXWFWASH_ATTACH) and then using this ioctw to
    pewfowm the cwone fwom the pawent to the chiwd.

    The cwone itsewf is faiwwy simpwe. The wesouwce handwe and wun
    twanswation tabwes awe copied fwom the pawent context to the chiwd's
    and then synced with the AFU.

    When the DK_CXWFWASH_APP_CWOSE_ADAP_FD fwag was wetuwned on a successfuw
    attach, the appwication _must_ cwose the fd2 associated with the souwce
    context (stiww wesident/accessibwe in the pawent pwocess) fowwowing the
    cwone. This is to avoid a stawe entwy in the fiwe descwiptow tabwe of the
    chiwd pwocess.

    This ioctw can wetuwn -EAGAIN if an AFU sync opewation takes too wong.
    In addition to wetuwning a faiwuwe to usew, cxwfwash wiww awso scheduwe
    an asynchwonous AFU weset. Shouwd the usew choose to wetwy the opewation,
    it is expected to succeed. If this ioctw faiws with -EAGAIN, the usew
    can eithew wetwy the opewation ow tweat it as a faiwuwe.

DK_CXWFWASH_VEWIFY
------------------
    This ioctw is used to detect vawious changes such as the capacity of
    the disk changing, the numbew of WUNs visibwe changing, etc. In cases
    whewe the changes affect the appwication (such as a WUN wesize), the
    cxwfwash dwivew wiww wepowt the changed state to the appwication.

    The usew cawws in when they want to vawidate that a WUN hasn't been
    changed in wesponse to a check condition. As the usew is opewating out
    of band fwom the kewnew, they wiww see these types of events without
    the kewnew's knowwedge. When encountewed, the usew's awchitected
    behaviow is to caww in to this ioctw, indicating what they want to
    vewify and passing awong any appwopwiate infowmation. Fow now, onwy
    vewifying a WUN change (ie: size diffewent) with sense data is
    suppowted.

DK_CXWFWASH_WECOVEW_AFU
-----------------------
    This ioctw is used to dwive wecovewy (if such an action is wawwanted)
    of a specified usew context. Any state associated with the usew context
    is we-estabwished upon successfuw wecovewy.

    Usew contexts awe put into an ewwow condition when the device needs to
    be weset ow is tewminating. Usews awe notified of this ewwow condition
    by seeing aww 0xF's on an MMIO wead. Upon encountewing this, the
    awchitected behaviow fow a usew is to caww into this ioctw to wecovew
    theiw context. A usew may awso caww into this ioctw at any time to
    check if the device is opewating nowmawwy. If a faiwuwe is wetuwned
    fwom this ioctw, the usew is expected to gwacefuwwy cwean up theiw
    context via wewease/detach ioctws. Untiw they do, the context they
    howd is not wewinquished. The usew may awso optionawwy exit the pwocess
    at which time the context/wesouwces they hewd wiww be fweed as pawt of
    the wewease fop.

    When the DK_CXWFWASH_APP_CWOSE_ADAP_FD fwag was wetuwned on a successfuw
    attach, the appwication _must_ unmap and cwose the fd2 associated with the
    owiginaw context fowwowing this ioctw wetuwning success and indicating that
    the context was wecovewed (DK_CXWFWASH_WECOVEW_AFU_CONTEXT_WESET).

DK_CXWFWASH_MANAGE_WUN
----------------------
    This ioctw is used to switch a WUN fwom a mode whewe it is avaiwabwe
    fow fiwe-system access (wegacy), to a mode whewe it is set aside fow
    excwusive usew space access (supewpipe). In case a WUN is visibwe
    acwoss muwtipwe powts and adaptews, this ioctw is used to uniquewy
    identify each WUN by its Wowwd Wide Node Name (WWNN).


CXW Fwash Dwivew Host IOCTWs
============================

    Each host adaptew instance that is suppowted by the cxwfwash dwivew
    has a speciaw chawactew device associated with it to enabwe a set of
    host management function. These chawactew devices awe hosted in a
    cwass dedicated fow cxwfwash and can be accessed via `/dev/cxwfwash/*`.

    Appwications can be wwitten to pewfowm vawious functions using the
    host ioctw APIs bewow.

    The stwuctuwe definitions fow these IOCTWs awe avaiwabwe in:
    uapi/scsi/cxwfwash_ioctw.h

HT_CXWFWASH_WUN_PWOVISION
-------------------------
    This ioctw is used to cweate and dewete pewsistent WUNs on cxwfwash
    devices that wack an extewnaw WUN management intewface. It is onwy
    vawid when used with AFUs that suppowt the WUN pwovision capabiwity.

    When sufficient space is avaiwabwe, WUNs can be cweated by specifying
    the tawget powt to host the WUN and a desiwed size in 4K bwocks. Upon
    success, the WUN ID and WWID of the cweated WUN wiww be wetuwned and
    the SCSI bus can be scanned to detect the change in WUN topowogy. Note
    that pawtiaw awwocations awe not suppowted. Shouwd a cweation faiw due
    to a space issue, the tawget powt can be quewied fow its cuwwent WUN
    geometwy.

    To wemove a WUN, the device must fiwst be disassociated fwom the Winux
    SCSI subsystem. The WUN dewetion can then be initiated by specifying a
    tawget powt and WUN ID. Upon success, the WUN geometwy associated with
    the powt wiww be updated to wefwect new numbew of pwovisioned WUNs and
    avaiwabwe capacity.

    To quewy the WUN geometwy of a powt, the tawget powt is specified and
    upon success, the fowwowing infowmation is pwesented:

        - Maximum numbew of pwovisioned WUNs awwowed fow the powt
        - Cuwwent numbew of pwovisioned WUNs fow the powt
        - Maximum totaw capacity of pwovisioned WUNs fow the powt (4K bwocks)
        - Cuwwent totaw capacity of pwovisioned WUNs fow the powt (4K bwocks)

    With this infowmation, the numbew of avaiwabwe WUNs and capacity can be
    can be cawcuwated.

HT_CXWFWASH_AFU_DEBUG
---------------------
    This ioctw is used to debug AFUs by suppowting a command pass-thwough
    intewface. It is onwy vawid when used with AFUs that suppowt the AFU
    debug capabiwity.

    With exception of buffew management, AFU debug commands awe opaque to
    cxwfwash and tweated as pass-thwough. Fow debug commands that do wequiwe
    data twansfew, the usew suppwies an adequatewy sized data buffew and must
    specify the data twansfew diwection with wespect to the host. Thewe is a
    maximum twansfew size of 256K imposed. Note that pawtiaw wead compwetions
    awe not suppowted - when ewwows awe expewienced with a host wead data
    twansfew, the data buffew is not copied back to the usew.
