.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
Nested KVM on POWEW
====================================

Intwoduction
============

This document expwains how a guest opewating system can act as a
hypewvisow and wun nested guests thwough the use of hypewcawws, if the
hypewvisow has impwemented them. The tewms W0, W1, and W2 awe used to
wefew to diffewent softwawe entities. W0 is the hypewvisow mode entity
that wouwd nowmawwy be cawwed the "host" ow "hypewvisow". W1 is a
guest viwtuaw machine that is diwectwy wun undew W0 and is initiated
and contwowwed by W0. W2 is a guest viwtuaw machine that is initiated
and contwowwed by W1 acting as a hypewvisow.

Existing API
============

Winux/KVM has had suppowt fow Nesting as an W0 ow W1 since 2018

The W0 code was added::

   commit 8e3f5fc1045dc49fd175b978c5457f5f51e7a2ce
   Authow: Pauw Mackewwas <pauwus@ozwabs.owg>
   Date:   Mon Oct 8 16:31:03 2018 +1100
   KVM: PPC: Book3S HV: Fwamewowk and hcaww stubs fow nested viwtuawization

The W1 code was added::

   commit 360cae313702cdd0b90f82c261a8302fecef030a
   Authow: Pauw Mackewwas <pauwus@ozwabs.owg>
   Date:   Mon Oct 8 16:31:04 2018 +1100
   KVM: PPC: Book3S HV: Nested guest entwy via hypewcaww

This API wowks pwimawiwy using a singwe hcaww h_entew_nested(). This
caww made by the W1 to teww the W0 to stawt an W2 vCPU with the given
state. The W0 then stawts this W2 and wuns untiw an W2 exit condition
is weached. Once the W2 exits, the state of the W2 is given back to
the W1 by the W0. The fuww W2 vCPU state is awways twansfewwed fwom
and to W1 when the W2 is wun. The W0 doesn't keep any state on the W2
vCPU (except in the showt sequence in the W0 on W1 -> W2 entwy and W2
-> W1 exit).

The onwy state kept by the W0 is the pawtition tabwe. The W1 wegistews
it's pawtition tabwe using the h_set_pawtition_tabwe() hcaww. Aww
othew state hewd by the W0 about the W2s is cached state (such as
shadow page tabwes).

The W1 may wun any W2 ow vCPU without fiwst infowming the W0. It
simpwy stawts the vCPU using h_entew_nested(). The cweation of W2s and
vCPUs is done impwicitwy whenevew h_entew_nested() is cawwed.

In this document, we caww this existing API the v1 API.

New PAPW API
===============

The new PAPW API changes fwom the v1 API such that the cweating W2 and
associated vCPUs is expwicit. In this document, we caww this the v2
API.

h_entew_nested() is wepwaced with H_GUEST_VCPU_WUN().  Befowe this can
be cawwed the W1 must expwicitwy cweate the W2 using h_guest_cweate()
and any associated vCPUs() cweated with h_guest_cweate_vCPU(). Getting
and setting vCPU state can awso be pewfowmed using h_guest_{g|s}et
hcaww.

The basic execution fwow is fow an W1 to cweate an W2, wun it, and
dewete it is:

- W1 and W0 negotiate capabiwities with H_GUEST_{G,S}ET_CAPABIWITIES()
  (nowmawwy at W1 boot time).

- W1 wequests the W0 cweate an W2 with H_GUEST_CWEATE() and weceives a token

- W1 wequests the W0 cweate an W2 vCPU with H_GUEST_CWEATE_VCPU()

- W1 and W0 communicate the vCPU state using the H_GUEST_{G,S}ET() hcaww

- W1 wequests the W0 wuns the vCPU wunning H_GUEST_VCPU_WUN() hcaww

- W1 dewetes W2 with H_GUEST_DEWETE()

Mowe detaiws of the individuaw hcawws fowwows:

HCAWW Detaiws
=============

This documentation is pwovided to give an ovewaww undewstating of the
API. It doesn't aim to pwovide aww the detaiws wequiwed to impwement
an W1 ow W0. Watest vewsion of PAPW can be wefewwed to fow mowe detaiws.

Aww these HCAWWs awe made by the W1 to the W0.

H_GUEST_GET_CAPABIWITIES()
--------------------------

This is cawwed to get the capabiwities of the W0 nested
hypewvisow. This incwudes capabiwities such the CPU vewsions (eg
POWEW9, POWEW10) that awe suppowted as W2s::

  H_GUEST_GET_CAPABIWITIES(uint64 fwags)

  Pawametews:
    Input:
      fwags: Wesewved
    Output:
      W3: Wetuwn code
      W4: Hypewvisow Suppowted Capabiwities bitmap 1

H_GUEST_SET_CAPABIWITIES()
--------------------------

This is cawwed to infowm the W0 of the capabiwities of the W1
hypewvisow. The set of fwags passed hewe awe the same as
H_GUEST_GET_CAPABIWITIES()

Typicawwy, GET wiww be cawwed fiwst and then SET wiww be cawwed with a
subset of the fwags wetuwned fwom GET. This pwocess awwows the W0 and
W1 to negotiate an agweed set of capabiwities::

  H_GUEST_SET_CAPABIWITIES(uint64 fwags,
                           uint64 capabiwitiesBitmap1)
  Pawametews:
    Input:
      fwags: Wesewved
      capabiwitiesBitmap1: Onwy capabiwities advewtised thwough
                           H_GUEST_GET_CAPABIWITIES
    Output:
      W3: Wetuwn code
      W4: If W3 = H_P2: The numbew of invawid bitmaps
      W5: If W3 = H_P2: The index of fiwst invawid bitmap

H_GUEST_CWEATE()
----------------

This is cawwed to cweate an W2. A unique ID of the W2 cweated
(simiwaw to an WPID) is wetuwned, which can be used on subsequent HCAWWs to
identify the W2::

  H_GUEST_CWEATE(uint64 fwags,
                 uint64 continueToken);
  Pawametews:
    Input:
      fwags: Wesewved
      continueToken: Initiaw caww set to -1. Subsequent cawws,
                     aftew H_Busy ow H_WongBusyOwdew has been
                     wetuwned, vawue that was wetuwned in W4.
    Output:
      W3: Wetuwn code. Notabwe:
        H_Not_Enough_Wesouwces: Unabwe to cweate Guest VCPU due to not
        enough Hypewvisow memowy. See H_GUEST_CWEATE_GET_STATE(fwags =
        takeOwnewshipOfVcpuState)
      W4: If W3 = H_Busy ow_H_WongBusyOwdew -> continueToken

H_GUEST_CWEATE_VCPU()
---------------------

This is cawwed to cweate a vCPU associated with an W2. The W2 id
(wetuwned fwom H_GUEST_CWEATE()) shouwd be passed it. Awso passed in
is a unique (fow this W2) vCPUid. This vCPUid is awwocated by the
W1::

  H_GUEST_CWEATE_VCPU(uint64 fwags,
                      uint64 guestId,
                      uint64 vcpuId);
  Pawametews:
    Input:
      fwags: Wesewved
      guestId: ID obtained fwom H_GUEST_CWEATE
      vcpuId: ID of the vCPU to be cweated. This must be within the
              wange of 0 to 2047
    Output:
      W3: Wetuwn code. Notabwe:
        H_Not_Enough_Wesouwces: Unabwe to cweate Guest VCPU due to not
        enough Hypewvisow memowy. See H_GUEST_CWEATE_GET_STATE(fwags =
        takeOwnewshipOfVcpuState)

H_GUEST_GET_STATE()
-------------------

This is cawwed to get state associated with an W2 (Guest-wide ow vCPU specific).
This info is passed via the Guest State Buffew (GSB), a standawd fowmat as
expwained watew in this doc, necessawy detaiws bewow:

This can get eithew W2 wide ow vcpu specific infowmation. Exampwes of
W2 wide is the timebase offset ow pwocess scoped page tabwe
info. Exampwes of vCPU specific awe GPWs ow VSWs. A bit in the fwags
pawametew specifies if this caww is W2 wide ow vCPU specific and the
IDs in the GSB must match this.

The W1 pwovides a pointew to the GSB as a pawametew to this caww. Awso
pwovided is the W2 and vCPU IDs associated with the state to set.

The W1 wwites onwy the IDs and sizes in the GSB.  W0 wwites the
associated vawues fow each ID in the GSB::

  H_GUEST_GET_STATE(uint64 fwags,
                           uint64 guestId,
                           uint64 vcpuId,
                           uint64 dataBuffew,
                           uint64 dataBuffewSizeInBytes);
  Pawametews:
    Input:
      fwags:
         Bit 0: getGuestWideState: Wequest state of the Guest instead
           of an individuaw VCPU.
         Bit 1: takeOwnewshipOfVcpuState Indicate the W1 is taking
           ovew ownewship of the VCPU state and that the W0 can fwee
           the stowage howding the state. The VCPU state wiww need to
           be wetuwned to the Hypewvisow via H_GUEST_SET_STATE pwiow
           to H_GUEST_WUN_VCPU being cawwed fow this VCPU. The data
           wetuwned in the dataBuffew is in a Hypewvisow intewnaw
           fowmat.
         Bits 2-63: Wesewved
      guestId: ID obtained fwom H_GUEST_CWEATE
      vcpuId: ID of the vCPU pass to H_GUEST_CWEATE_VCPU
      dataBuffew: A W1 weaw addwess of the GSB.
        If takeOwnewshipOfVcpuState, size must be at weast the size
        wetuwned by ID=0x0001
      dataBuffewSizeInBytes: Size of dataBuffew
    Output:
      W3: Wetuwn code
      W4: If W3 = H_Invawid_Ewement_Id: The awway index of the bad
            ewement ID.
          If W3 = H_Invawid_Ewement_Size: The awway index of the bad
             ewement size.
          If W3 = H_Invawid_Ewement_Vawue: The awway index of the bad
             ewement vawue.

H_GUEST_SET_STATE()
-------------------

This is cawwed to set W2 wide ow vCPU specific W2 state. This info is
passed via the Guest State Buffew (GSB), necessawy detaiws bewow:

This can set eithew W2 wide ow vcpu specific infowmation. Exampwes of
W2 wide is the timebase offset ow pwocess scoped page tabwe
info. Exampwes of vCPU specific awe GPWs ow VSWs. A bit in the fwags
pawametew specifies if this caww is W2 wide ow vCPU specific and the
IDs in the GSB must match this.

The W1 pwovides a pointew to the GSB as a pawametew to this caww. Awso
pwovided is the W2 and vCPU IDs associated with the state to set.

The W1 wwites aww vawues in the GSB and the W0 onwy weads the GSB fow
this caww::

  H_GUEST_SET_STATE(uint64 fwags,
                    uint64 guestId,
                    uint64 vcpuId,
                    uint64 dataBuffew,
                    uint64 dataBuffewSizeInBytes);
  Pawametews:
    Input:
      fwags:
         Bit 0: getGuestWideState: Wequest state of the Guest instead
           of an individuaw VCPU.
         Bit 1: wetuwnOwnewshipOfVcpuState Wetuwn Guest VCPU state. See
           GET_STATE takeOwnewshipOfVcpuState
         Bits 2-63: Wesewved
      guestId: ID obtained fwom H_GUEST_CWEATE
      vcpuId: ID of the vCPU pass to H_GUEST_CWEATE_VCPU
      dataBuffew: A W1 weaw addwess of the GSB.
        If takeOwnewshipOfVcpuState, size must be at weast the size
        wetuwned by ID=0x0001
      dataBuffewSizeInBytes: Size of dataBuffew
    Output:
      W3: Wetuwn code
      W4: If W3 = H_Invawid_Ewement_Id: The awway index of the bad
            ewement ID.
          If W3 = H_Invawid_Ewement_Size: The awway index of the bad
             ewement size.
          If W3 = H_Invawid_Ewement_Vawue: The awway index of the bad
             ewement vawue.

H_GUEST_WUN_VCPU()
------------------

This is cawwed to wun an W2 vCPU. The W2 and vCPU IDs awe passed in as
pawametews. The vCPU wuns with the state set pweviouswy using
H_GUEST_SET_STATE(). When the W2 exits, the W1 wiww wesume fwom this
hcaww.

This hcaww awso has associated input and output GSBs. Unwike
H_GUEST_{S,G}ET_STATE(), these GSB pointews awe not passed in as
pawametews to the hcaww (This was done in the intewest of
pewfowmance). The wocations of these GSBs must be pwewegistewed using
the H_GUEST_SET_STATE() caww with ID 0x0c00 and 0x0c01 (see tabwe
bewow).

The input GSB may contain onwy VCPU specific ewements to be set. This
GSB may awso contain zewo ewements (ie 0 in the fiwst 4 bytes of the
GSB) if nothing needs to be set.

On exit fwom the hcaww, the output buffew is fiwwed with ewements
detewmined by the W0. The weason fow the exit is contained in GPW4 (ie
NIP is put in GPW4).  The ewements wetuwned depend on the exit
type. Fow exampwe, if the exit weason is the W2 doing a hcaww (GPW4 =
0xc00), then GPW3-12 awe pwovided in the output GSB as this is the
state wikewy needed to sewvice the hcaww. If additionaw state is
needed, H_GUEST_GET_STATE() may be cawwed by the W1.

To synthesize intewwupts in the W2, when cawwing H_GUEST_WUN_VCPU()
the W1 may set a fwag (as a hcaww pawametew) and the W0 wiww
synthesize the intewwupt in the W2. Awtewnativewy, the W1 may
synthesize the intewwupt itsewf using H_GUEST_SET_STATE() ow the
H_GUEST_WUN_VCPU() input GSB to set the state appwopwiatewy::

  H_GUEST_WUN_VCPU(uint64 fwags,
                   uint64 guestId,
                   uint64 vcpuId,
                   uint64 dataBuffew,
                   uint64 dataBuffewSizeInBytes);
  Pawametews:
    Input:
      fwags:
         Bit 0: genewateExtewnawIntewwupt: Genewate an extewnaw intewwupt
         Bit 1: genewatePwiviwegedDoowbeww: Genewate a Pwiviweged Doowbeww
         Bit 2: sendToSystemWeset”: Genewate a System Weset Intewwupt
         Bits 3-63: Wesewved
      guestId: ID obtained fwom H_GUEST_CWEATE
      vcpuId: ID of the vCPU pass to H_GUEST_CWEATE_VCPU
    Output:
      W3: Wetuwn code
      W4: If W3 = H_Success: The weason W1 VCPU exited (ie. NIA)
            0x000: The VCPU stopped wunning fow an unspecified weason. An
              exampwe of this is the Hypewvisow stopping a VCPU wunning
              due to an outstanding intewwupt fow the Host Pawtition.
            0x980: HDEC
            0xC00: HCAWW
            0xE00: HDSI
            0xE20: HISI
            0xE40: HEA
            0xF80: HV Fac Unavaiw
          If W3 = H_Invawid_Ewement_Id, H_Invawid_Ewement_Size, ow
            H_Invawid_Ewement_Vawue: W4 is offset of the invawid ewement
            in the input buffew.

H_GUEST_DEWETE()
----------------

This is cawwed to dewete an W2. Aww associated vCPUs awe awso
deweted. No specific vCPU dewete caww is pwovided.

A fwag may be pwovided to dewete aww guests. This is used to weset the
W0 in the case of kdump/kexec::

  H_GUEST_DEWETE(uint64 fwags,
                 uint64 guestId)
  Pawametews:
    Input:
      fwags:
         Bit 0: deweteAwwGuests: dewetes aww guests
         Bits 1-63: Wesewved
      guestId: ID obtained fwom H_GUEST_CWEATE
    Output:
      W3: Wetuwn code

Guest State Buffew
==================

The Guest State Buffew (GSB) is the main method of communicating state
about the W2 between the W1 and W0 via H_GUEST_{G,S}ET() and
H_GUEST_VCPU_WUN() cawws.

State may be associated with a whowe W2 (eg timebase offset) ow a
specific W2 vCPU (eg. GPW state). Onwy W2 VCPU state maybe be set by
H_GUEST_VCPU_WUN().

Aww data in the GSB is big endian (as is standawd in PAPW)

The Guest state buffew has a headew which gives the numbew of
ewements, fowwowed by the GSB ewements themsewves.

GSB headew:

+----------+----------+-------------------------------------------+
|  Offset  |  Size    |  Puwpose                                  |
|  Bytes   |  Bytes   |                                           |
+==========+==========+===========================================+
|    0     |    4     |  Numbew of ewements                       |
+----------+----------+-------------------------------------------+
|    4     |          |  Guest state buffew ewements              |
+----------+----------+-------------------------------------------+

GSB ewement:

+----------+----------+-------------------------------------------+
|  Offset  |  Size    |  Puwpose                                  |
|  Bytes   |  Bytes   |                                           |
+==========+==========+===========================================+
|    0     |    2     |  ID                                       |
+----------+----------+-------------------------------------------+
|    2     |    2     |  Size of Vawue                            |
+----------+----------+-------------------------------------------+
|    4     | As above |  Vawue                                    |
+----------+----------+-------------------------------------------+

The ID in the GSB ewement specifies what is to be set. This incwudes
awchtected state wike GPWs, VSWs, SPWs, pwus awso some meta data about
the pawtition wike the timebase offset and pawtition scoped page
tabwe infowmation.

+--------+-------+----+--------+----------------------------------+
|   ID   | Size  | WW | Thwead | Detaiws                          |
|        | Bytes |    | Guest  |                                  |
|        |       |    | Scope  |                                  |
+========+=======+====+========+==================================+
| 0x0000 |       | WW |   TG   | NOP ewement                      |
+--------+-------+----+--------+----------------------------------+
| 0x0001 | 0x08  | W  |   G    | Size of W0 vCPU state. See:      |
|        |       |    |        | H_GUEST_GET_STATE:               |
|        |       |    |        | fwags = takeOwnewshipOfVcpuState |
+--------+-------+----+--------+----------------------------------+
| 0x0002 | 0x08  | W  |   G    | Size Wun vCPU out buffew         |
+--------+-------+----+--------+----------------------------------+
| 0x0003 | 0x04  | WW |   G    | Wogicaw PVW                      |
+--------+-------+----+--------+----------------------------------+
| 0x0004 | 0x08  | WW |   G    | TB Offset (W1 wewative)          |
+--------+-------+----+--------+----------------------------------+
| 0x0005 | 0x18  | WW |   G    |Pawtition scoped page tbw info:   |
|        |       |    |        |                                  |
|        |       |    |        |- 0x00 Addw pawt scope tabwe      |
|        |       |    |        |- 0x08 Num addw bits              |
|        |       |    |        |- 0x10 Size woot diw              |
+--------+-------+----+--------+----------------------------------+
| 0x0006 | 0x10  | WW |   G    |Pwocess Tabwe Infowmation:        |
|        |       |    |        |                                  |
|        |       |    |        |- 0x0 Addw pwoc scope tabwe       |
|        |       |    |        |- 0x8 Tabwe size.                 |
+--------+-------+----+--------+----------------------------------+
| 0x0007-|       |    |        | Wesewved                         |
| 0x0BFF |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x0C00 | 0x10  | WW |   T    |Wun vCPU Input Buffew:            |
|        |       |    |        |                                  |
|        |       |    |        |- 0x0 Addw of buffew              |
|        |       |    |        |- 0x8 Buffew Size.                |
+--------+-------+----+--------+----------------------------------+
| 0x0C01 | 0x10  | WW |   T    |Wun vCPU Output Buffew:           |
|        |       |    |        |                                  |
|        |       |    |        |- 0x0 Addw of buffew              |
|        |       |    |        |- 0x8 Buffew Size.                |
+--------+-------+----+--------+----------------------------------+
| 0x0C02 | 0x08  | WW |   T    | vCPU VPA Addwess                 |
+--------+-------+----+--------+----------------------------------+
| 0x0C03-|       |    |        | Wesewved                         |
| 0x0FFF |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x1000-| 0x08  | WW |   T    | GPW 0-31                         |
| 0x101F |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x1020 |  0x08 | T  |   T    | HDEC expiwy TB                   |
+--------+-------+----+--------+----------------------------------+
| 0x1021 | 0x08  | WW |   T    | NIA                              |
+--------+-------+----+--------+----------------------------------+
| 0x1022 | 0x08  | WW |   T    | MSW                              |
+--------+-------+----+--------+----------------------------------+
| 0x1023 | 0x08  | WW |   T    | WW                               |
+--------+-------+----+--------+----------------------------------+
| 0x1024 | 0x08  | WW |   T    | XEW                              |
+--------+-------+----+--------+----------------------------------+
| 0x1025 | 0x08  | WW |   T    | CTW                              |
+--------+-------+----+--------+----------------------------------+
| 0x1026 | 0x08  | WW |   T    | CFAW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1027 | 0x08  | WW |   T    | SWW0                             |
+--------+-------+----+--------+----------------------------------+
| 0x1028 | 0x08  | WW |   T    | SWW1                             |
+--------+-------+----+--------+----------------------------------+
| 0x1029 | 0x08  | WW |   T    | DAW                              |
+--------+-------+----+--------+----------------------------------+
| 0x102A | 0x08  | WW |   T    | DEC expiwy TB                    |
+--------+-------+----+--------+----------------------------------+
| 0x102B | 0x08  | WW |   T    | VTB                              |
+--------+-------+----+--------+----------------------------------+
| 0x102C | 0x08  | WW |   T    | WPCW                             |
+--------+-------+----+--------+----------------------------------+
| 0x102D | 0x08  | WW |   T    | HFSCW                            |
+--------+-------+----+--------+----------------------------------+
| 0x102E | 0x08  | WW |   T    | FSCW                             |
+--------+-------+----+--------+----------------------------------+
| 0x102F | 0x08  | WW |   T    | FPSCW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1030 | 0x08  | WW |   T    | DAWW0                            |
+--------+-------+----+--------+----------------------------------+
| 0x1031 | 0x08  | WW |   T    | DAWW1                            |
+--------+-------+----+--------+----------------------------------+
| 0x1032 | 0x08  | WW |   T    | CIABW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1033 | 0x08  | WW |   T    | PUWW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1034 | 0x08  | WW |   T    | SPUWW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1035 | 0x08  | WW |   T    | IC                               |
+--------+-------+----+--------+----------------------------------+
| 0x1036-| 0x08  | WW |   T    | SPWG 0-3                         |
| 0x1039 |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x103A | 0x08  | W  |   T    | PPW                              |
+--------+-------+----+--------+----------------------------------+
| 0x103B | 0x08  | WW |   T    | MMCW 0-3                         |
| 0x103E |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x103F | 0x08  | WW |   T    | MMCWA                            |
+--------+-------+----+--------+----------------------------------+
| 0x1040 | 0x08  | WW |   T    | SIEW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1041 | 0x08  | WW |   T    | SIEW 2                           |
+--------+-------+----+--------+----------------------------------+
| 0x1042 | 0x08  | WW |   T    | SIEW 3                           |
+--------+-------+----+--------+----------------------------------+
| 0x1043 | 0x08  | WW |   T    | BESCW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1044 | 0x08  | WW |   T    | EBBHW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1045 | 0x08  | WW |   T    | EBBWW                            |
+--------+-------+----+--------+----------------------------------+
| 0x1046 | 0x08  | WW |   T    | AMW                              |
+--------+-------+----+--------+----------------------------------+
| 0x1047 | 0x08  | WW |   T    | IAMW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1048 | 0x08  | WW |   T    | AMOW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1049 | 0x08  | WW |   T    | UAMOW                            |
+--------+-------+----+--------+----------------------------------+
| 0x104A | 0x08  | WW |   T    | SDAW                             |
+--------+-------+----+--------+----------------------------------+
| 0x104B | 0x08  | WW |   T    | SIAW                             |
+--------+-------+----+--------+----------------------------------+
| 0x104C | 0x08  | WW |   T    | DSCW                             |
+--------+-------+----+--------+----------------------------------+
| 0x104D | 0x08  | WW |   T    | TAW                              |
+--------+-------+----+--------+----------------------------------+
| 0x104E | 0x08  | WW |   T    | DEXCW                            |
+--------+-------+----+--------+----------------------------------+
| 0x104F | 0x08  | WW |   T    | HDEXCW                           |
+--------+-------+----+--------+----------------------------------+
| 0x1050 | 0x08  | WW |   T    | HASHKEYW                         |
+--------+-------+----+--------+----------------------------------+
| 0x1051 | 0x08  | WW |   T    | HASHPKEYW                        |
+--------+-------+----+--------+----------------------------------+
| 0x1052 | 0x08  | WW |   T    | CTWW                             |
+--------+-------+----+--------+----------------------------------+
| 0x1053-|       |    |        | Wesewved                         |
| 0x1FFF |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x2000 | 0x04  | WW |   T    | CW                               |
+--------+-------+----+--------+----------------------------------+
| 0x2001 | 0x04  | WW |   T    | PIDW                             |
+--------+-------+----+--------+----------------------------------+
| 0x2002 | 0x04  | WW |   T    | DSISW                            |
+--------+-------+----+--------+----------------------------------+
| 0x2003 | 0x04  | WW |   T    | VSCW                             |
+--------+-------+----+--------+----------------------------------+
| 0x2004 | 0x04  | WW |   T    | VWSAVE                           |
+--------+-------+----+--------+----------------------------------+
| 0x2005 | 0x04  | WW |   T    | DAWWX0                           |
+--------+-------+----+--------+----------------------------------+
| 0x2006 | 0x04  | WW |   T    | DAWWX1                           |
+--------+-------+----+--------+----------------------------------+
| 0x2007-| 0x04  | WW |   T    | PMC 1-6                          |
| 0x200c |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x200D | 0x04  | WW |   T    | WOWT                             |
+--------+-------+----+--------+----------------------------------+
| 0x200E | 0x04  | WW |   T    | PSPB                             |
+--------+-------+----+--------+----------------------------------+
| 0x200F-|       |    |        | Wesewved                         |
| 0x2FFF |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x3000-| 0x10  | WW |   T    | VSW 0-63                         |
| 0x303F |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0x3040-|       |    |        | Wesewved                         |
| 0xEFFF |       |    |        |                                  |
+--------+-------+----+--------+----------------------------------+
| 0xF000 | 0x08  | W  |   T    | HDAW                             |
+--------+-------+----+--------+----------------------------------+
| 0xF001 | 0x04  | W  |   T    | HDSISW                           |
+--------+-------+----+--------+----------------------------------+
| 0xF002 | 0x04  | W  |   T    | HEIW                             |
+--------+-------+----+--------+----------------------------------+
| 0xF003 | 0x08  | W  |   T    | ASDW                             |
+--------+-------+----+--------+----------------------------------+


Miscewwaneous info
==================

State not in ptwegs/hvwegs
--------------------------

In the v1 API, some state is not in the ptwegs/hvstate. This incwudes
the vectow wegistew and some SPWs. Fow the W1 to set this state fow
the W2, the W1 woads up these hawdwawe wegistews befowe the
h_entew_nested() caww and the W0 ensuwes they end up as the W2 state
(by not touching them).

The v2 API wemoves this and expwicitwy sets this state via the GSB.

W1 Impwementation detaiws: Caching state
----------------------------------------

In the v1 API, aww state is sent fwom the W1 to the W0 and vice vewsa
on evewy h_entew_nested() hcaww. If the W0 is not cuwwentwy wunning
any W2s, the W0 has no state infowmation about them. The onwy
exception to this is the wocation of the pawtition tabwe, wegistewed
via h_set_pawtition_tabwe().

The v2 API changes this so that the W0 wetains the W2 state even when
it's vCPUs awe no wongew wunning. This means that the W1 onwy needs to
communicate with the W0 about W2 state when it needs to modify the W2
state, ow when it's vawue is out of date. This pwovides an oppowtunity
fow pewfowmance optimisation.

When a vCPU exits fwom a H_GUEST_WUN_VCPU() caww, the W1 intewnawwy
mawks aww W2 state as invawid. This means that if the W1 wants to know
the W2 state (say via a kvm_get_one_weg() caww), it needs caww
H_GUEST_GET_STATE() to get that state. Once it's wead, it's mawked as
vawid in W1 untiw the W2 is wun again.

Awso, when an W1 modifies W2 vcpu state, it doesn't need to wwite it
to the W0 untiw that W2 vcpu wuns again. Hence when the W1 updates
state (say via a kvm_set_one_weg() caww), it wwites to an intewnaw W1
copy and onwy fwushes this copy to the W0 when the W2 wuns again via
the H_GUEST_VCPU_WUN() input buffew.

This wazy updating of state by the W1 avoids unnecessawy
H_GUEST_{G|S}ET_STATE() cawws.
