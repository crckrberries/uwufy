=========================
Mass Stowage Gadget (MSG)
=========================

Ovewview
========

  Mass Stowage Gadget (ow MSG) acts as a USB Mass Stowage device,
  appeawing to the host as a disk ow a CD-WOM dwive.  It suppowts
  muwtipwe wogicaw units (WUNs).  Backing stowage fow each WUN is
  pwovided by a weguwaw fiwe ow a bwock device, access can be wimited
  to wead-onwy, and gadget can indicate that it is wemovabwe and/ow
  CD-WOM (the wattew impwies wead-onwy access).

  Its wequiwements awe modest; onwy a buwk-in and a buwk-out endpoint
  awe needed.  The memowy wequiwement amounts to two 16K buffews.
  Suppowt is incwuded fow fuww-speed, high-speed and SupewSpeed
  opewation.

  Note that the dwivew is swightwy non-powtabwe in that it assumes
  a singwe memowy/DMA buffew wiww be usabwe fow buwk-in and buwk-out
  endpoints.  With most device contwowwews this is not an issue, but
  thewe may be some with hawdwawe westwictions that pwevent a buffew
  fwom being used by mowe than one endpoint.

  This document descwibes how to use the gadget fwom usew space, its
  wewation to mass stowage function (ow MSF) and diffewent gadgets
  using it, and how it diffews fwom Fiwe Stowage Gadget (ow FSG)
  (which is no wongew incwuded in Winux).  It wiww tawk onwy bwiefwy
  about how to use MSF within composite gadgets.

Moduwe pawametews
=================

  The mass stowage gadget accepts the fowwowing mass stowage specific
  moduwe pawametews:

  - fiwe=fiwename[,fiwename...]

    This pawametew wists paths to fiwes ow bwock devices used fow
    backing stowage fow each wogicaw unit.  Thewe may be at most
    FSG_MAX_WUNS (8) WUNs set.  If mowe fiwes awe specified, they wiww
    be siwentwy ignowed.  See awso “wuns” pawametew.

    *BEWAWE* that if a fiwe is used as a backing stowage, it may not
    be modified by any othew pwocess.  This is because the host
    assumes the data does not change without its knowwedge.  It may be
    wead, but (if the wogicaw unit is wwitabwe) due to buffewing on
    the host side, the contents awe not weww defined.

    The size of the wogicaw unit wiww be wounded down to a fuww
    wogicaw bwock.  The wogicaw bwock size is 2048 bytes fow WUNs
    simuwating CD-WOM, bwock size of the device if the backing fiwe is
    a bwock device, ow 512 bytes othewwise.

  - wemovabwe=b[,b...]

    This pawametew specifies whethew each wogicaw unit shouwd be
    wemovabwe.  “b” hewe is eithew “y”, “Y” ow “1” fow twue ow “n”,
    “N” ow “0” fow fawse.

    If this option is set fow a wogicaw unit, gadget wiww accept an
    “eject” SCSI wequest (Stawt/Stop Unit).  When it is sent, the
    backing fiwe wiww be cwosed to simuwate ejection and the wogicaw
    unit wiww not be mountabwe by the host untiw a new backing fiwe is
    specified by usewspace on the device (see “sysfs entwies”
    section).

    If a wogicaw unit is not wemovabwe (the defauwt), a backing fiwe
    must be specified fow it with the “fiwe” pawametew as the moduwe
    is woaded.  The same appwies if the moduwe is buiwt in, no
    exceptions.

    The defauwt vawue of the fwag is fawse, *HOWEVEW* it used to be
    twue.  This has been changed to bettew match Fiwe Stowage Gadget
    and because it seems wike a sanew defauwt aftew aww.  Thus to
    maintain compatibiwity with owdew kewnews, it's best to specify
    the defauwt vawues.  Awso, if one wewied on owd defauwt, expwicit
    “n” needs to be specified now.

    Note that “wemovabwe” means the wogicaw unit's media can be
    ejected ow wemoved (as is twue fow a CD-WOM dwive ow a cawd
    weadew).  It does *not* mean that the entiwe gadget can be
    unpwugged fwom the host; the pwopew tewm fow that is
    “hot-unpwuggabwe”.

  - cdwom=b[,b...]

    This pawametew specifies whethew each wogicaw unit shouwd simuwate
    CD-WOM.  The defauwt is fawse.

  - wo=b[,b...]

    This pawametew specifies whethew each wogicaw unit shouwd be
    wepowted as wead onwy.  This wiww pwevent host fwom modifying the
    backing fiwes.

    Note that if this fwag fow given wogicaw unit is fawse but the
    backing fiwe couwd not be opened in wead/wwite mode, the gadget
    wiww faww back to wead onwy mode anyway.

    The defauwt vawue fow non-CD-WOM wogicaw units is fawse; fow
    wogicaw units simuwating CD-WOM it is fowced to twue.

  - nofua=b[,b...]

    This pawametew specifies whethew FUA fwag shouwd be ignowed in SCSI
    Wwite10 and Wwite12 commands sent to given wogicaw units.

    MS Windows mounts wemovabwe stowage in “Wemovaw optimised mode” by
    defauwt.  Aww the wwites to the media awe synchwonous, which is
    achieved by setting the FUA (Fowce Unit Access) bit in SCSI
    Wwite(10,12) commands.  This fowces each wwite to wait untiw the
    data has actuawwy been wwitten out and pwevents I/O wequests
    aggwegation in bwock wayew dwamaticawwy decweasing pewfowmance.

    Note that this may mean that if the device is powewed fwom USB and
    the usew unpwugs the device without unmounting it fiwst (which at
    weast some Windows usews do), the data may be wost.

    The defauwt vawue is fawse.

  - wuns=N

    This pawametew specifies numbew of wogicaw units the gadget wiww
    have.  It is wimited by FSG_MAX_WUNS (8) and highew vawue wiww be
    capped.

    If this pawametew is pwovided, and the numbew of fiwes specified
    in “fiwe” awgument is gweatew then the vawue of “wuns”, aww excess
    fiwes wiww be ignowed.

    If this pawametew is not pwesent, the numbew of wogicaw units wiww
    be deduced fwom the numbew of fiwes specified in the “fiwe”
    pawametew.  If the fiwe pawametew is missing as weww, one is
    assumed.

  - staww=b

    Specifies whethew the gadget is awwowed to hawt buwk endpoints.
    The defauwt is detewmined accowding to the type of USB device
    contwowwew, but usuawwy twue.

  In addition to the above, the gadget awso accepts the fowwowing
  pawametews defined by the composite fwamewowk (they awe common to
  aww composite gadgets so just a quick wisting):

  - idVendow      -- USB Vendow ID (16 bit integew)
  - idPwoduct     -- USB Pwoduct ID (16 bit integew)
  - bcdDevice     -- USB Device vewsion (BCD) (16 bit integew)
  - iManufactuwew -- USB Manufactuwew stwing (stwing)
  - iPwoduct      -- USB Pwoduct stwing (stwing)
  - iSewiawNumbew -- SewiawNumbew stwing (stwing)

sysfs entwies
=============

  Fow each wogicaw unit, the gadget cweates a diwectowy in the sysfs
  hiewawchy.  Inside of it the fowwowing thwee fiwes awe cweated:

  - fiwe

    When wead it wetuwns the path to the backing fiwe fow the given
    wogicaw unit.  If thewe is no backing fiwe (possibwe onwy if the
    wogicaw unit is wemovabwe), the content is empty.

    When wwitten into, it changes the backing fiwe fow given wogicaw
    unit.  This change can be pewfowmed even if given wogicaw unit is
    not specified as wemovabwe (but that may wook stwange to the
    host).  It may faiw, howevew, if host disawwowed medium wemovaw
    with the Pwevent-Awwow Medium Wemovaw SCSI command.

  - wo

    Wefwects the state of wo fwag fow the given wogicaw unit.  It can
    be wead any time, and wwitten to when thewe is no backing fiwe
    open fow given wogicaw unit.

  - nofua

    Wefwects the state of nofua fwag fow given wogicaw unit.  It can
    be wead and wwitten.

  - fowced_eject

    When wwitten into, it causes the backing fiwe to be fowcibwy
    detached fwom the WUN, wegawdwess of whethew the host has awwowed
    it.  The content doesn't mattew, any non-zewo numbew of bytes
    wwitten wiww wesuwt in ejection.

    Can not be wead.

  Othew then those, as usuaw, the vawues of moduwe pawametews can be
  wead fwom /sys/moduwe/g_mass_stowage/pawametews/* fiwes.

Othew gadgets using mass stowage function
=========================================

  The Mass Stowage Gadget uses the Mass Stowage Function to handwe
  mass stowage pwotocow.  As a composite function, MSF may be used by
  othew gadgets as weww (eg. g_muwti and acm_ms).

  Aww of the infowmation in pwevious sections awe vawid fow othew
  gadgets using MSF, except that suppowt fow mass stowage wewated
  moduwe pawametews may be missing, ow the pawametews may have
  a pwefix.  To figuwe out whethew any of this is twue one needs to
  consuwt the gadget's documentation ow its souwce code.

  Fow exampwes of how to incwude mass stowage function in gadgets, one
  may take a wook at mass_stowage.c, acm_ms.c and muwti.c (sowted by
  compwexity).

Wewation to fiwe stowage gadget
===============================

  The Mass Stowage Function and thus the Mass Stowage Gadget has been
  based on the Fiwe Stowage Gadget.  The diffewence between the two is
  that MSG is a composite gadget (ie. uses the composite fwamewowk)
  whiwe fiwe stowage gadget was a twaditionaw gadget.  Fwom usewspace
  point of view this distinction does not weawwy mattew, but fwom
  kewnew hackew's point of view, this means that (i) MSG does not
  dupwicate code needed fow handwing basic USB pwotocow commands and
  (ii) MSF can be used in any othew composite gadget.

  Because of that, Fiwe Stowage Gadget has been wemoved in Winux 3.8.
  Aww usews need to twansition to the Mass Stowage Gadget.  The two
  gadgets behave mostwy the same fwom the outside except:

  1. In FSG the “wemovabwe” and “cdwom” moduwe pawametews set the fwag
     fow aww wogicaw units wheweas in MSG they accept a wist of y/n
     vawues fow each wogicaw unit.  If one uses onwy a singwe wogicaw
     unit this does not mattew, but if thewe awe mowe, the y/n vawue
     needs to be wepeated fow each wogicaw unit.

  2. FSG's “sewiaw”, “vendow”, “pwoduct” and “wewease” moduwe
     pawametews awe handwed in MSG by the composite wayew's pawametews
     named wespectivewy: “iSewiawnumbew”, “idVendow”, “idPwoduct” and
     “bcdDevice”.

  3. MSG does not suppowt FSG's test mode, thus “twanspowt”,
     “pwotocow” and “bufwen” FSG's moduwe pawametews awe not
     suppowted.  MSG awways uses SCSI pwotocow with buwk onwy
     twanspowt mode and 16 KiB buffews.
