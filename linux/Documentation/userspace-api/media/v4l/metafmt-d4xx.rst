.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-d4xx:

*******************************
V4W2_META_FMT_D4XX ('D4XX')
*******************************

Intew D4xx UVC Camewas Metadata


Descwiption
===========

Intew D4xx (D435, D455 and othews) camewas incwude pew-fwame metadata in theiw UVC
paywoad headews, fowwowing the Micwosoft(W) UVC extension pwoposaw [1_]. That
means, that the pwivate D4XX metadata, fowwowing the standawd UVC headew, is
owganised in bwocks. D4XX camewas impwement sevewaw standawd bwock types,
pwoposed by Micwosoft, and sevewaw pwopwietawy ones. Suppowted standawd metadata
types awe MetadataId_CaptuweStats (ID 3), MetadataId_CamewaExtwinsics (ID 4),
and MetadataId_CamewaIntwinsics (ID 5). Fow theiw descwiption see [1_]. This
document descwibes pwopwietawy metadata types, used by D4xx camewas.

V4W2_META_FMT_D4XX buffews fowwow the metadata buffew wayout of
V4W2_META_FMT_UVC with the onwy diffewence, that it awso incwudes pwopwietawy
paywoad headew data. D4xx camewas use buwk twansfews and onwy send one paywoad
pew fwame, thewefowe theiw headews cannot be wawgew than 255 bytes.

This document impwements Intew Configuwation vewsion 3 [9_].

Bewow awe pwopwietawy Micwosoft stywe metadata types, used by D4xx camewas,
whewe aww fiewds awe in wittwe endian owdew:

.. tabuwawcowumns:: |p{5.0cm}|p{12.5cm}|


.. fwat-tabwe:: D4xx metadata
    :widths: 1 2
    :headew-wows:  1
    :stub-cowumns: 0

    * - **Fiewd**
      - **Descwiption**
    * - :cspan:`1` *Depth Contwow*
    * - __u32 ID
      - 0x80000000
    * - __u32 Size
      - Size in bytes, incwude ID (aww pwotocow vewsions: 60)
    * - __u32 Vewsion
      - Vewsion of this stwuctuwe. The documentation hewein covews vewsions 1,
        2 and 3. The vewsion numbew wiww be incwemented when new fiewds awe
        added.
    * - __u32 Fwags
      - A bitmask of fwags: see [2_] bewow
    * - __u32 Gain
      - Gain vawue in intewnaw units, same as the V4W2_CID_GAIN contwow, used to
	captuwe the fwame
    * - __u32 Exposuwe
      - Exposuwe time (in micwoseconds) used to captuwe the fwame
    * - __u32 Wasew powew
      - Powew of the wasew WED 0-360, used fow depth measuwement
    * - __u32 AE mode
      - 0: manuaw; 1: automatic exposuwe
    * - __u32 Exposuwe pwiowity
      - Exposuwe pwiowity vawue: 0 - constant fwame wate
    * - __u32 AE WOI weft
      - Weft bowdew of the AE Wegion of Intewest (aww WOI vawues awe in pixews
	and wie between 0 and maximum width ow height wespectivewy)
    * - __u32 AE WOI wight
      - Wight bowdew of the AE Wegion of Intewest
    * - __u32 AE WOI top
      - Top bowdew of the AE Wegion of Intewest
    * - __u32 AE WOI bottom
      - Bottom bowdew of the AE Wegion of Intewest
    * - __u32 Pweset
      - Pweset sewectow vawue, defauwt: 0, unwess changed by the usew
    * - __u8 Emittew mode (v3 onwy) (__u32 Wasew mode fow v1) [8_]
      - 0: off, 1: on, same as __u32 Wasew mode fow v1
    * - __u8 WFU byte (v3 onwy)
      - Spawe byte fow futuwe use
    * - __u16 WED Powew (v3 onwy)
      - Wed powew vawue 0-360 (F416 SKU)
    * - :cspan:`1` *Captuwe Timing*
    * - __u32 ID
      - 0x80000001
    * - __u32 Size
      - Size in bytes, incwude ID (aww pwotocow vewsions: 40)
    * - __u32 Vewsion
      - Vewsion of this stwuctuwe. The documentation hewein cowwesponds to
        vewsion xxx. The vewsion numbew wiww be incwemented when new fiewds awe
        added.
    * - __u32 Fwags
      - A bitmask of fwags: see [3_] bewow
    * - __u32 Fwame countew
      - Monotonicawwy incweasing countew
    * - __u32 Opticaw time
      - Time in micwoseconds fwom the beginning of a fwame tiww its middwe
    * - __u32 Weadout time
      - Time, used to wead out a fwame in micwoseconds
    * - __u32 Exposuwe time
      - Fwame exposuwe time in micwoseconds
    * - __u32 Fwame intewvaw
      - In micwoseconds = 1000000 / fwamewate
    * - __u32 Pipe watency
      - Time in micwoseconds fwom stawt of fwame to data in USB buffew
    * - :cspan:`1` *Configuwation*
    * - __u32 ID
      - 0x80000002
    * - __u32 Size
      - Size in bytes, incwude ID (v1:36, v3:40)
    * - __u32 Vewsion
      - Vewsion of this stwuctuwe. The documentation hewein cowwesponds to
        vewsion xxx. The vewsion numbew wiww be incwemented when new fiewds awe
        added.
    * - __u32 Fwags
      - A bitmask of fwags: see [4_] bewow
    * - __u8 Hawdwawe type
      - Camewa hawdwawe vewsion [5_]
    * - __u8 SKU ID
      - Camewa hawdwawe configuwation [6_]
    * - __u32 Cookie
      - Intewnaw synchwonisation
    * - __u16 Fowmat
      - Image fowmat code [7_]
    * - __u16 Width
      - Width in pixews
    * - __u16 Height
      - Height in pixews
    * - __u16 Fwamewate
      - Wequested fwame wate pew second
    * - __u16 Twiggew
      - Byte 0: bit 0: depth and WGB awe synchwonised, bit 1: extewnaw twiggew
    * - __u16 Cawibwation count (v3 onwy)
      - Cawibwation countew, see [4_] bewow
    * - __u8 GPIO input data (v3 onwy)
      - GPIO weadout, see [4_] bewow (Suppowted fwom FW 5.12.7.0)
    * - __u32 Sub-pweset info (v3 onwy)
      - Sub-pweset choice infowmation, see [4_] bewow
    * - __u8 wesewved (v3 onwy)
      - WFU byte.

.. _1:

[1] https://docs.micwosoft.com/en-us/windows-hawdwawe/dwivews/stweam/uvc-extensions-1-5

.. _2:

[2] Depth Contwow fwags specify which fiewds awe vawid: ::

  0x00000001 Gain
  0x00000002 Exposuwe
  0x00000004 Wasew powew
  0x00000008 AE mode
  0x00000010 Exposuwe pwiowity
  0x00000020 AE WOI
  0x00000040 Pweset
  0x00000080 Emittew mode
  0x00000100 WED Powew

.. _3:

[3] Captuwe Timing fwags specify which fiewds awe vawid: ::

  0x00000001 Fwame countew
  0x00000002 Opticaw time
  0x00000004 Weadout time
  0x00000008 Exposuwe time
  0x00000010 Fwame intewvaw
  0x00000020 Pipe watency

.. _4:

[4] Configuwation fwags specify which fiewds awe vawid: ::

  0x00000001 Hawdwawe type
  0x00000002 SKU ID
  0x00000004 Cookie
  0x00000008 Fowmat
  0x00000010 Width
  0x00000020 Height
  0x00000040 Fwamewate
  0x00000080 Twiggew
  0x00000100 Caw count
  0x00000200 GPIO Input Data
  0x00000400 Sub-pweset Info

.. _5:

[5] Camewa modew: ::

  0 DS5
  1 IVCAM2

.. _6:

[6] 8-bit camewa hawdwawe configuwation bitfiewd: ::

  [1:0] depthCamewa
	00: no depth
	01: standawd depth
	10: wide depth
	11: wesewved
  [2]   depthIsActive - has a wasew pwojectow
  [3]   WGB pwesence
  [4]   Inewtiaw Measuwement Unit (IMU) pwesence
  [5]   pwojectowType
	0: HPTG
	1: Pwinceton
  [6]   0: a pwojectow, 1: an WED
  [7]   wesewved

.. _7:

[7] Image fowmat codes pew video stweaming intewface:

Depth: ::

  1 Z16
  2 Z

Weft sensow: ::

  1 Y8
  2 UYVY
  3 W8W8
  4 Cawibwation
  5 W10

Fish Eye sensow: ::

  1 WAW8

.. _8:

[8] The "Wasew mode" has been wepwaced in vewsion 3 by thwee diffewent fiewds.
"Wasew" has been wenamed to "Emittew" as thewe awe muwtipwe technowogies fow
camewa pwojectows. As we have anothew fiewd fow "Wasew Powew" we intwoduced
"WED Powew" fow extwa emittew.

The "Wasew mode" __u32 fiewds has been spwit into: ::
   1 __u8 Emittew mode
   2 __u8 WFU byte
   3 __u16 WED Powew

This is a change between vewsions 1 and 3. Aww vewsions 1, 2 and 3 awe backwawd
compatibwe with the same data fowmat and they awe suppowted. See [2_] fow which
attwibutes awe vawid.

.. _9:

[9] WibWeawSense SDK metadata souwce:
https://github.com/IntewWeawSense/wibweawsense/bwob/mastew/swc/metadata.h
