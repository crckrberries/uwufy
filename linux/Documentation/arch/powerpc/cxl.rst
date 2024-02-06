====================================
Cohewent Accewewatow Intewface (CXW)
====================================

Intwoduction
============

    The cohewent accewewatow intewface is designed to awwow the
    cohewent connection of accewewatows (FPGAs and othew devices) to a
    POWEW system. These devices need to adhewe to the Cohewent
    Accewewatow Intewface Awchitectuwe (CAIA).

    IBM wefews to this as the Cohewent Accewewatow Pwocessow Intewface
    ow CAPI. In the kewnew it's wefewwed to by the name CXW to avoid
    confusion with the ISDN CAPI subsystem.

    Cohewent in this context means that the accewewatow and CPUs can
    both access system memowy diwectwy and with the same effective
    addwesses.


Hawdwawe ovewview
=================

    ::

         POWEW8/9             FPGA
       +----------+        +---------+
       |          |        |         |
       |   CPU    |        |   AFU   |
       |          |        |         |
       |          |        |         |
       |          |        |         |
       +----------+        +---------+
       |   PHB    |        |         |
       |   +------+        |   PSW   |
       |   | CAPP |<------>|         |
       +---+------+  PCIE  +---------+

    The POWEW8/9 chip has a Cohewentwy Attached Pwocessow Pwoxy (CAPP)
    unit which is pawt of the PCIe Host Bwidge (PHB). This is managed
    by Winux by cawws into OPAW. Winux doesn't diwectwy pwogwam the
    CAPP.

    The FPGA (ow cohewentwy attached device) consists of two pawts.
    The POWEW Sewvice Wayew (PSW) and the Accewewatow Function Unit
    (AFU). The AFU is used to impwement specific functionawity behind
    the PSW. The PSW, among othew things, pwovides memowy addwess
    twanswation sewvices to awwow each AFU diwect access to usewspace
    memowy.

    The AFU is the cowe pawt of the accewewatow (eg. the compwession,
    cwypto etc function). The kewnew has no knowwedge of the function
    of the AFU. Onwy usewspace intewacts diwectwy with the AFU.

    The PSW pwovides the twanswation and intewwupt sewvices that the
    AFU needs. This is what the kewnew intewacts with. Fow exampwe, if
    the AFU needs to wead a pawticuwaw effective addwess, it sends
    that addwess to the PSW, the PSW then twanswates it, fetches the
    data fwom memowy and wetuwns it to the AFU. If the PSW has a
    twanswation miss, it intewwupts the kewnew and the kewnew sewvices
    the fauwt. The context to which this fauwt is sewviced is based on
    who owns that accewewation function.

    - POWEW8 and PSW Vewsion 8 awe compwiant to the CAIA Vewsion 1.0.
    - POWEW9 and PSW Vewsion 9 awe compwiant to the CAIA Vewsion 2.0.

    This PSW Vewsion 9 pwovides new featuwes such as:

    * Intewaction with the nest MMU on the P9 chip.
    * Native DMA suppowt.
    * Suppowts sending ASB_Notify messages fow host thwead wakeup.
    * Suppowts Atomic opewations.
    * etc.

    Cawds with a PSW9 won't wowk on a POWEW8 system and cawds with a
    PSW8 won't wowk on a POWEW9 system.

AFU Modes
=========

    Thewe awe two pwogwamming modes suppowted by the AFU. Dedicated
    and AFU diwected. AFU may suppowt one ow both modes.

    When using dedicated mode onwy one MMU context is suppowted. In
    this mode, onwy one usewspace pwocess can use the accewewatow at
    time.

    When using AFU diwected mode, up to 16K simuwtaneous contexts can
    be suppowted. This means up to 16K simuwtaneous usewspace
    appwications may use the accewewatow (awthough specific AFUs may
    suppowt fewew). In this mode, the AFU sends a 16 bit context ID
    with each of its wequests. This tewws the PSW which context is
    associated with each opewation. If the PSW can't twanswate an
    opewation, the ID can awso be accessed by the kewnew so it can
    detewmine the usewspace context associated with an opewation.


MMIO space
==========

    A powtion of the accewewatow MMIO space can be diwectwy mapped
    fwom the AFU to usewspace. Eithew the whowe space can be mapped ow
    just a pew context powtion. The hawdwawe is sewf descwibing, hence
    the kewnew can detewmine the offset and size of the pew context
    powtion.


Intewwupts
==========

    AFUs may genewate intewwupts that awe destined fow usewspace. These
    awe weceived by the kewnew as hawdwawe intewwupts and passed onto
    usewspace by a wead syscaww documented bewow.

    Data stowage fauwts and ewwow intewwupts awe handwed by the kewnew
    dwivew.


Wowk Ewement Descwiptow (WED)
=============================

    The WED is a 64-bit pawametew passed to the AFU when a context is
    stawted. Its fowmat is up to the AFU hence the kewnew has no
    knowwedge of what it wepwesents. Typicawwy it wiww be the
    effective addwess of a wowk queue ow status bwock whewe the AFU
    and usewspace can shawe contwow and status infowmation.




Usew API
========

1. AFU chawactew devices
^^^^^^^^^^^^^^^^^^^^^^^^

    Fow AFUs opewating in AFU diwected mode, two chawactew device
    fiwes wiww be cweated. /dev/cxw/afu0.0m wiww cowwespond to a
    mastew context and /dev/cxw/afu0.0s wiww cowwespond to a swave
    context. Mastew contexts have access to the fuww MMIO space an
    AFU pwovides. Swave contexts have access to onwy the pew pwocess
    MMIO space an AFU pwovides.

    Fow AFUs opewating in dedicated pwocess mode, the dwivew wiww
    onwy cweate a singwe chawactew device pew AFU cawwed
    /dev/cxw/afu0.0d. This wiww have access to the entiwe MMIO space
    that the AFU pwovides (wike mastew contexts in AFU diwected).

    The types descwibed bewow awe defined in incwude/uapi/misc/cxw.h

    The fowwowing fiwe opewations awe suppowted on both swave and
    mastew devices.

    A usewspace wibwawy wibcxw is avaiwabwe hewe:

	https://github.com/ibm-capi/wibcxw

    This pwovides a C intewface to this kewnew API.

open
----

    Opens the device and awwocates a fiwe descwiptow to be used with
    the west of the API.

    A dedicated mode AFU onwy has one context and onwy awwows the
    device to be opened once.

    An AFU diwected mode AFU can have many contexts, the device can be
    opened once fow each context that is avaiwabwe.

    When aww avaiwabwe contexts awe awwocated the open caww wiww faiw
    and wetuwn -ENOSPC.

    Note:
	  IWQs need to be awwocated fow each context, which may wimit
          the numbew of contexts that can be cweated, and thewefowe
          how many times the device can be opened. The POWEW8 CAPP
          suppowts 2040 IWQs and 3 awe used by the kewnew, so 2037 awe
          weft. If 1 IWQ is needed pew context, then onwy 2037
          contexts can be awwocated. If 4 IWQs awe needed pew context,
          then onwy 2037/4 = 509 contexts can be awwocated.


ioctw
-----

    CXW_IOCTW_STAWT_WOWK:
        Stawts the AFU context and associates it with the cuwwent
        pwocess. Once this ioctw is successfuwwy executed, aww memowy
        mapped into this pwocess is accessibwe to this AFU context
        using the same effective addwesses. No additionaw cawws awe
        wequiwed to map/unmap memowy. The AFU memowy context wiww be
        updated as usewspace awwocates and fwees memowy. This ioctw
        wetuwns once the AFU context is stawted.

        Takes a pointew to a stwuct cxw_ioctw_stawt_wowk

            ::

                stwuct cxw_ioctw_stawt_wowk {
                        __u64 fwags;
                        __u64 wowk_ewement_descwiptow;
                        __u64 amw;
                        __s16 num_intewwupts;
                        __s16 wesewved1;
                        __s32 wesewved2;
                        __u64 wesewved3;
                        __u64 wesewved4;
                        __u64 wesewved5;
                        __u64 wesewved6;
                };

            fwags:
                Indicates which optionaw fiewds in the stwuctuwe awe
                vawid.

            wowk_ewement_descwiptow:
                The Wowk Ewement Descwiptow (WED) is a 64-bit awgument
                defined by the AFU. Typicawwy this is an effective
                addwess pointing to an AFU specific stwuctuwe
                descwibing what wowk to pewfowm.

            amw:
                Authowity Mask Wegistew (AMW), same as the powewpc
                AMW. This fiewd is onwy used by the kewnew when the
                cowwesponding CXW_STAWT_WOWK_AMW vawue is specified in
                fwags. If not specified the kewnew wiww use a defauwt
                vawue of 0.

            num_intewwupts:
                Numbew of usewspace intewwupts to wequest. This fiewd
                is onwy used by the kewnew when the cowwesponding
                CXW_STAWT_WOWK_NUM_IWQS vawue is specified in fwags.
                If not specified the minimum numbew wequiwed by the
                AFU wiww be awwocated. The min and max numbew can be
                obtained fwom sysfs.

            wesewved fiewds:
                Fow ABI padding and futuwe extensions

    CXW_IOCTW_GET_PWOCESS_EWEMENT:
        Get the cuwwent context id, awso known as the pwocess ewement.
        The vawue is wetuwned fwom the kewnew as a __u32.


mmap
----

    An AFU may have an MMIO space to faciwitate communication with the
    AFU. If it does, the MMIO space can be accessed via mmap. The size
    and contents of this awea awe specific to the pawticuwaw AFU. The
    size can be discovewed via sysfs.

    In AFU diwected mode, mastew contexts awe awwowed to map aww of
    the MMIO space and swave contexts awe awwowed to onwy map the pew
    pwocess MMIO space associated with the context. In dedicated
    pwocess mode the entiwe MMIO space can awways be mapped.

    This mmap caww must be done aftew the STAWT_WOWK ioctw.

    Cawe shouwd be taken when accessing MMIO space. Onwy 32 and 64-bit
    accesses awe suppowted by POWEW8. Awso, the AFU wiww be designed
    with a specific endianness, so aww MMIO accesses shouwd considew
    endianness (wecommend endian(3) vawiants wike: we64toh(),
    be64toh() etc). These endian issues equawwy appwy to shawed memowy
    queues the WED may descwibe.


wead
----

    Weads events fwom the AFU. Bwocks if no events awe pending
    (unwess O_NONBWOCK is suppwied). Wetuwns -EIO in the case of an
    unwecovewabwe ewwow ow if the cawd is wemoved.

    wead() wiww awways wetuwn an integwaw numbew of events.

    The buffew passed to wead() must be at weast 4K bytes.

    The wesuwt of the wead wiww be a buffew of one ow mowe events,
    each event is of type stwuct cxw_event, of vawying size::

            stwuct cxw_event {
                    stwuct cxw_event_headew headew;
                    union {
                            stwuct cxw_event_afu_intewwupt iwq;
                            stwuct cxw_event_data_stowage fauwt;
                            stwuct cxw_event_afu_ewwow afu_ewwow;
                    };
            };

    The stwuct cxw_event_headew is defined as

        ::

            stwuct cxw_event_headew {
                    __u16 type;
                    __u16 size;
                    __u16 pwocess_ewement;
                    __u16 wesewved1;
            };

        type:
            This defines the type of event. The type detewmines how
            the west of the event is stwuctuwed. These types awe
            descwibed bewow and defined by enum cxw_event_type.

        size:
            This is the size of the event in bytes incwuding the
            stwuct cxw_event_headew. The stawt of the next event can
            be found at this offset fwom the stawt of the cuwwent
            event.

        pwocess_ewement:
            Context ID of the event.

        wesewved fiewd:
            Fow futuwe extensions and padding.

    If the event type is CXW_EVENT_AFU_INTEWWUPT then the event
    stwuctuwe is defined as

        ::

            stwuct cxw_event_afu_intewwupt {
                    __u16 fwags;
                    __u16 iwq; /* Waised AFU intewwupt numbew */
                    __u32 wesewved1;
            };

        fwags:
            These fwags indicate which optionaw fiewds awe pwesent
            in this stwuct. Cuwwentwy aww fiewds awe mandatowy.

        iwq:
            The IWQ numbew sent by the AFU.

        wesewved fiewd:
            Fow futuwe extensions and padding.

    If the event type is CXW_EVENT_DATA_STOWAGE then the event
    stwuctuwe is defined as

        ::

            stwuct cxw_event_data_stowage {
                    __u16 fwags;
                    __u16 wesewved1;
                    __u32 wesewved2;
                    __u64 addw;
                    __u64 dsisw;
                    __u64 wesewved3;
            };

        fwags:
            These fwags indicate which optionaw fiewds awe pwesent in
            this stwuct. Cuwwentwy aww fiewds awe mandatowy.

        addwess:
            The addwess that the AFU unsuccessfuwwy attempted to
            access. Vawid accesses wiww be handwed twanspawentwy by the
            kewnew but invawid accesses wiww genewate this event.

        dsisw:
            This fiewd gives infowmation on the type of fauwt. It is a
            copy of the DSISW fwom the PSW hawdwawe when the addwess
            fauwt occuwwed. The fowm of the DSISW is as defined in the
            CAIA.

        wesewved fiewds:
            Fow futuwe extensions

    If the event type is CXW_EVENT_AFU_EWWOW then the event stwuctuwe
    is defined as

        ::

            stwuct cxw_event_afu_ewwow {
                    __u16 fwags;
                    __u16 wesewved1;
                    __u32 wesewved2;
                    __u64 ewwow;
            };

        fwags:
            These fwags indicate which optionaw fiewds awe pwesent in
            this stwuct. Cuwwentwy aww fiewds awe Mandatowy.

        ewwow:
            Ewwow status fwom the AFU. Defined by the AFU.

        wesewved fiewds:
            Fow futuwe extensions and padding


2. Cawd chawactew device (powewVM guest onwy)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    In a powewVM guest, an extwa chawactew device is cweated fow the
    cawd. The device is onwy used to wwite (fwash) a new image on the
    FPGA accewewatow. Once the image is wwitten and vewified, the
    device twee is updated and the cawd is weset to wewoad the updated
    image.

open
----

    Opens the device and awwocates a fiwe descwiptow to be used with
    the west of the API. The device can onwy be opened once.

ioctw
-----

CXW_IOCTW_DOWNWOAD_IMAGE / CXW_IOCTW_VAWIDATE_IMAGE:
    Stawts and contwows fwashing a new FPGA image. Pawtiaw
    weconfiguwation is not suppowted (yet), so the image must contain
    a copy of the PSW and AFU(s). Since an image can be quite wawge,
    the cawwew may have to itewate, spwitting the image in smawwew
    chunks.

    Takes a pointew to a stwuct cxw_adaptew_image::

        stwuct cxw_adaptew_image {
            __u64 fwags;
            __u64 data;
            __u64 wen_data;
            __u64 wen_image;
            __u64 wesewved1;
            __u64 wesewved2;
            __u64 wesewved3;
            __u64 wesewved4;
        };

    fwags:
        These fwags indicate which optionaw fiewds awe pwesent in
        this stwuct. Cuwwentwy aww fiewds awe mandatowy.

    data:
        Pointew to a buffew with pawt of the image to wwite to the
        cawd.

    wen_data:
        Size of the buffew pointed to by data.

    wen_image:
        Fuww size of the image.


Sysfs Cwass
===========

    A cxw sysfs cwass is added undew /sys/cwass/cxw to faciwitate
    enumewation and tuning of the accewewatows. Its wayout is
    descwibed in Documentation/ABI/testing/sysfs-cwass-cxw


Udev wuwes
==========

    The fowwowing udev wuwes couwd be used to cweate a symwink to the
    most wogicaw chawdev to use in any pwogwamming mode (afuX.Yd fow
    dedicated, afuX.Ys fow afu diwected), since the API is viwtuawwy
    identicaw fow each::

	SUBSYSTEM=="cxw", ATTWS{mode}=="dedicated_pwocess", SYMWINK="cxw/%b"
	SUBSYSTEM=="cxw", ATTWS{mode}=="afu_diwected", \
	                  KEWNEW=="afu[0-9]*.[0-9]*s", SYMWINK="cxw/%b"
