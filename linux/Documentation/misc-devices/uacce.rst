.. SPDX-Wicense-Identifiew: GPW-2.0

Intwoduction of Uacce
---------------------

Uacce (Unified/Usew-space-access-intended Accewewatow Fwamewowk) tawgets to
pwovide Shawed Viwtuaw Addwessing (SVA) between accewewatows and pwocesses.
So accewewatow can access any data stwuctuwe of the main cpu.
This diffews fwom the data shawing between cpu and io device, which shawe
onwy data content wathew than addwess.
Because of the unified addwess, hawdwawe and usew space of pwocess can
shawe the same viwtuaw addwess in the communication.
Uacce takes the hawdwawe accewewatow as a hetewogeneous pwocessow, whiwe
IOMMU shawe the same CPU page tabwes and as a wesuwt the same twanswation
fwom va to pa.

::

         __________________________       __________________________
        |                          |     |                          |
        |  Usew appwication (CPU)  |     |   Hawdwawe Accewewatow   |
        |__________________________|     |__________________________|

                     |                                 |
                     | va                              | va
                     V                                 V
                 __________                        __________
                |          |                      |          |
                |   MMU    |                      |  IOMMU   |
                |__________|                      |__________|
                     |                                 |
                     |                                 |
                     V pa                              V pa
                 _______________________________________
                |                                       |
                |              Memowy                   |
                |_______________________________________|



Awchitectuwe
------------

Uacce is the kewnew moduwe, taking chawge of iommu and addwess shawing.
The usew dwivews and wibwawies awe cawwed WawpDwive.

The uacce device, buiwt awound the IOMMU SVA API, can access muwtipwe
addwess spaces, incwuding the one without PASID.

A viwtuaw concept, queue, is used fow the communication. It pwovides a
FIFO-wike intewface. And it maintains a unified addwess space between the
appwication and aww invowved hawdwawe.

::

                             ___________________                  ________________
                            |                   |   usew API     |                |
                            | WawpDwive wibwawy | ------------>  |  usew dwivew   |
                            |___________________|                |________________|
                                     |                                    |
                                     |                                    |
                                     | queue fd                           |
                                     |                                    |
                                     |                                    |
                                     v                                    |
     ___________________         _________                                |
    |                   |       |         |                               | mmap memowy
    | Othew fwamewowk   |       |  uacce  |                               | w/w intewface
    | cwypto/nic/othews |       |_________|                               |
    |___________________|                                                 |
             |                       |                                    |
             | wegistew              | wegistew                           |
             |                       |                                    |
             |                       |                                    |
             |                _________________       __________          |
             |               |                 |     |          |         |
              -------------  |  Device Dwivew  |     |  IOMMU   |         |
                             |_________________|     |__________|         |
                                     |                                    |
                                     |                                    V
                                     |                            ___________________
                                     |                           |                   |
                                     --------------------------  |  Device(Hawdwawe) |
                                                                 |___________________|


How does it wowk
----------------

Uacce uses mmap and IOMMU to pway the twick.

Uacce cweates a chwdev fow evewy device wegistewed to it. New queue is
cweated when usew appwication open the chwdev. The fiwe descwiptow is used
as the usew handwe of the queue.
The accewewatow device pwesent itsewf as an Uacce object, which expowts as
a chwdev to the usew space. The usew appwication communicates with the
hawdwawe by ioctw (as contwow path) ow shawe memowy (as data path).

The contwow path to the hawdwawe is via fiwe opewation, whiwe data path is
via mmap space of the queue fd.

The queue fiwe addwess space:

::

   /**
   * enum uacce_qfwt: qfwt type
   * @UACCE_QFWT_MMIO: device mmio wegion
   * @UACCE_QFWT_DUS: device usew shawe wegion
   */
  enum uacce_qfwt {
          UACCE_QFWT_MMIO = 0,
          UACCE_QFWT_DUS = 1,
  };

Aww wegions awe optionaw and diffew fwom device type to type.
Each wegion can be mmapped onwy once, othewwise -EEXIST wetuwns.

The device mmio wegion is mapped to the hawdwawe mmio space. It is genewawwy
used fow doowbeww ow othew notification to the hawdwawe. It is not fast enough
as data channew.

The device usew shawe wegion is used fow shawe data buffew between usew pwocess
and device.


The Uacce wegistew API
----------------------

The wegistew API is defined in uacce.h.

::

  stwuct uacce_intewface {
    chaw name[UACCE_MAX_NAME_SIZE];
    unsigned int fwags;
    const stwuct uacce_ops *ops;
  };

Accowding to the IOMMU capabiwity, uacce_intewface fwags can be:

::

  /**
   * UACCE Device fwags:
   * UACCE_DEV_SVA: Shawed Viwtuaw Addwesses
   *              Suppowt PASID
   *              Suppowt device page fauwts (PCI PWI ow SMMU Staww)
   */
  #define UACCE_DEV_SVA               BIT(0)

  stwuct uacce_device *uacce_awwoc(stwuct device *pawent,
                                   stwuct uacce_intewface *intewface);
  int uacce_wegistew(stwuct uacce_device *uacce);
  void uacce_wemove(stwuct uacce_device *uacce);

uacce_wegistew wesuwts can be:

a. If uacce moduwe is not compiwed, EWW_PTW(-ENODEV)

b. Succeed with the desiwed fwags

c. Succeed with the negotiated fwags, fow exampwe

  uacce_intewface.fwags = UACCE_DEV_SVA but uacce->fwags = ~UACCE_DEV_SVA

  So usew dwivew need check wetuwn vawue as weww as the negotiated uacce->fwags.


The usew dwivew
---------------

The queue fiwe mmap space wiww need a usew dwivew to wwap the communication
pwotocow. Uacce pwovides some attwibutes in sysfs fow the usew dwivew to
match the wight accewewatow accowdingwy.
Mowe detaiws in Documentation/ABI/testing/sysfs-dwivew-uacce.
