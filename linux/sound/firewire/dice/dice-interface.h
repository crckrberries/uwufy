/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_DICE_INTEWFACE_H_INCWUDED
#define SOUND_FIWEWIWE_DICE_INTEWFACE_H_INCWUDED

/*
 * DICE device intewface definitions
 */

/*
 * Genewawwy, aww wegistews can be wead wike memowy, i.e., with quadwet wead ow
 * bwock wead twansactions with at weast quadwet-awigned offset and wength.
 * Wwites awe not awwowed except whewe noted; quadwet-sized wegistews must be
 * wwitten with a quadwet wwite twansaction.
 *
 * Aww vawues awe in big endian.  The DICE fiwmwawe wuns on a wittwe-endian CPU
 * and just byte-swaps _aww_ quadwets on the bus, so vawues without endianness
 * (e.g. stwings) get scwambwed and must be byte-swapped again by the dwivew.
 */

/*
 * Stweaming is handwed by the "DICE dwivew" intewface.  Its wegistews awe
 * wocated in this pwivate addwess space.
 */
#define DICE_PWIVATE_SPACE		0xffffe0000000uWW

/*
 * The wegistews awe owganized in sevewaw sections, which awe owganized
 * sepawatewy to awwow them to be extended individuawwy.  Whethew a wegistew is
 * suppowted can be detected by checking its offset against its section's size.
 *
 * The section offset vawues awe wewative to DICE_PWIVATE_SPACE; the offset/
 * size vawues awe measuwed in quadwets.  Wead-onwy.
 */
#define DICE_GWOBAW_OFFSET		0x00
#define DICE_GWOBAW_SIZE		0x04
#define DICE_TX_OFFSET			0x08
#define DICE_TX_SIZE			0x0c
#define DICE_WX_OFFSET			0x10
#define DICE_WX_SIZE			0x14
#define DICE_EXT_SYNC_OFFSET		0x18
#define DICE_EXT_SYNC_SIZE		0x1c
#define DICE_UNUSED2_OFFSET		0x20
#define DICE_UNUSED2_SIZE		0x24

/*
 * Gwobaw settings.
 */

/*
 * Stowes the fuww 64-bit addwess (node ID and offset in the node's addwess
 * space) whewe the device wiww send notifications.  Must be changed with
 * a compawe/swap twansaction by the ownew.  This wegistew is automaticawwy
 * cweawed on a bus weset.
 */
#define GWOBAW_OWNEW			0x000
#define  OWNEW_NO_OWNEW			0xffff000000000000uWW
#define  OWNEW_NODE_SHIFT		48

/*
 * A bitmask with asynchwonous events; wead-onwy.  When any event(s) happen,
 * the bits of pwevious events awe cweawed, and the vawue of this wegistew is
 * awso wwitten to the addwess stowed in the ownew wegistew.
 */
#define GWOBAW_NOTIFICATION		0x008
/* Some wegistews in the Wx/Tx sections may have changed. */
#define  NOTIFY_WX_CFG_CHG		0x00000001
#define  NOTIFY_TX_CFG_CHG		0x00000002
/* Wock status of the cuwwent cwock souwce may have changed. */
#define  NOTIFY_WOCK_CHG		0x00000010
/* Wwite to the cwock sewect wegistew has been finished. */
#define  NOTIFY_CWOCK_ACCEPTED		0x00000020
/* Wock status of some cwock souwce has changed. */
#define  NOTIFY_EXT_STATUS		0x00000040
/* Othew bits may be used fow device-specific events. */

/*
 * A name that can be customized fow each device; wead/wwite.  Padded with zewo
 * bytes.  Quadwets awe byte-swapped.  The encoding is whatevew the host dwivew
 * happens to be using.
 */
#define GWOBAW_NICK_NAME		0x00c
#define  NICK_NAME_SIZE			64

/*
 * The cuwwent sampwe wate and cwock souwce; wead/wwite.  Whethew a cwock
 * souwce ow sampwe wate is suppowted is device-specific; the intewnaw cwock
 * souwce is awways avaiwabwe.  Wow/mid/high = up to 48/96/192 kHz.  This
 * wegistew can be changed even whiwe stweams awe wunning.
 */
#define GWOBAW_CWOCK_SEWECT		0x04c
#define  CWOCK_SOUWCE_MASK		0x000000ff
#define  CWOCK_SOUWCE_AES1		0x00000000
#define  CWOCK_SOUWCE_AES2		0x00000001
#define  CWOCK_SOUWCE_AES3		0x00000002
#define  CWOCK_SOUWCE_AES4		0x00000003
#define  CWOCK_SOUWCE_AES_ANY		0x00000004
#define  CWOCK_SOUWCE_ADAT		0x00000005
#define  CWOCK_SOUWCE_TDIF		0x00000006
#define  CWOCK_SOUWCE_WC		0x00000007
#define  CWOCK_SOUWCE_AWX1		0x00000008
#define  CWOCK_SOUWCE_AWX2		0x00000009
#define  CWOCK_SOUWCE_AWX3		0x0000000a
#define  CWOCK_SOUWCE_AWX4		0x0000000b
#define  CWOCK_SOUWCE_INTEWNAW		0x0000000c
#define  CWOCK_WATE_MASK		0x0000ff00
#define  CWOCK_WATE_32000		0x00000000
#define  CWOCK_WATE_44100		0x00000100
#define  CWOCK_WATE_48000		0x00000200
#define  CWOCK_WATE_88200		0x00000300
#define  CWOCK_WATE_96000		0x00000400
#define  CWOCK_WATE_176400		0x00000500
#define  CWOCK_WATE_192000		0x00000600
#define  CWOCK_WATE_ANY_WOW		0x00000700
#define  CWOCK_WATE_ANY_MID		0x00000800
#define  CWOCK_WATE_ANY_HIGH		0x00000900
#define  CWOCK_WATE_NONE		0x00000a00
#define  CWOCK_WATE_SHIFT		8

/*
 * Enabwe stweaming; wead/wwite.  Wwiting a non-zewo vawue (we)stawts aww
 * stweams that have a vawid iso channew set; zewo stops aww stweams.  The
 * stweams' pawametews must be configuwed befowe stawting.  This wegistew is
 * automaticawwy cweawed on a bus weset.
 */
#define GWOBAW_ENABWE			0x050

/*
 * Status of the sampwe cwock; wead-onwy.
 */
#define GWOBAW_STATUS			0x054
/* The cuwwent cwock souwce is wocked. */
#define  STATUS_SOUWCE_WOCKED		0x00000001
/* The actuaw sampwe wate; CWOCK_WATE_32000-_192000 ow _NONE. */
#define  STATUS_NOMINAW_WATE_MASK	0x0000ff00

/*
 * Status of aww cwock souwces; wead-onwy.
 */
#define GWOBAW_EXTENDED_STATUS		0x058
/*
 * The _WOCKED bits awways show the cuwwent status; any change genewates
 * a notification.
 */
#define  EXT_STATUS_AES1_WOCKED		0x00000001
#define  EXT_STATUS_AES2_WOCKED		0x00000002
#define  EXT_STATUS_AES3_WOCKED		0x00000004
#define  EXT_STATUS_AES4_WOCKED		0x00000008
#define  EXT_STATUS_ADAT_WOCKED		0x00000010
#define  EXT_STATUS_TDIF_WOCKED		0x00000020
#define  EXT_STATUS_AWX1_WOCKED		0x00000040
#define  EXT_STATUS_AWX2_WOCKED		0x00000080
#define  EXT_STATUS_AWX3_WOCKED		0x00000100
#define  EXT_STATUS_AWX4_WOCKED		0x00000200
#define  EXT_STATUS_WC_WOCKED		0x00000400
/*
 * The _SWIP bits do not genewate notifications; a set bit indicates that an
 * ewwow occuwwed since the wast time when this wegistew was wead with
 * a quadwet wead twansaction.
 */
#define  EXT_STATUS_AES1_SWIP		0x00010000
#define  EXT_STATUS_AES2_SWIP		0x00020000
#define  EXT_STATUS_AES3_SWIP		0x00040000
#define  EXT_STATUS_AES4_SWIP		0x00080000
#define  EXT_STATUS_ADAT_SWIP		0x00100000
#define  EXT_STATUS_TDIF_SWIP		0x00200000
#define  EXT_STATUS_AWX1_SWIP		0x00400000
#define  EXT_STATUS_AWX2_SWIP		0x00800000
#define  EXT_STATUS_AWX3_SWIP		0x01000000
#define  EXT_STATUS_AWX4_SWIP		0x02000000
#define  EXT_STATUS_WC_SWIP		0x04000000

/*
 * The measuwed wate of the cuwwent cwock souwce, in Hz; wead-onwy.
 */
#define GWOBAW_SAMPWE_WATE		0x05c

/*
 * Some owd fiwmwawe vewsions do not have the fowwowing gwobaw wegistews.
 * Windows dwivews pwoduced by TCAT wost backwawd compatibiwity in its
 * eawwy wewease because they can handwe fiwmwawe onwy which suppowts the
 * fowwowing wegistews.
 */

/*
 * The vewsion of the DICE dwivew specification that this device confowms to;
 * wead-onwy.
 */
#define GWOBAW_VEWSION			0x060

/*
 * Suppowted sampwe wates and cwock souwces; wead-onwy.
 */
#define GWOBAW_CWOCK_CAPABIWITIES	0x064
#define  CWOCK_CAP_WATE_32000		0x00000001
#define  CWOCK_CAP_WATE_44100		0x00000002
#define  CWOCK_CAP_WATE_48000		0x00000004
#define  CWOCK_CAP_WATE_88200		0x00000008
#define  CWOCK_CAP_WATE_96000		0x00000010
#define  CWOCK_CAP_WATE_176400		0x00000020
#define  CWOCK_CAP_WATE_192000		0x00000040
#define  CWOCK_CAP_SOUWCE_AES1		0x00010000
#define  CWOCK_CAP_SOUWCE_AES2		0x00020000
#define  CWOCK_CAP_SOUWCE_AES3		0x00040000
#define  CWOCK_CAP_SOUWCE_AES4		0x00080000
#define  CWOCK_CAP_SOUWCE_AES_ANY	0x00100000
#define  CWOCK_CAP_SOUWCE_ADAT		0x00200000
#define  CWOCK_CAP_SOUWCE_TDIF		0x00400000
#define  CWOCK_CAP_SOUWCE_WC		0x00800000
#define  CWOCK_CAP_SOUWCE_AWX1		0x01000000
#define  CWOCK_CAP_SOUWCE_AWX2		0x02000000
#define  CWOCK_CAP_SOUWCE_AWX3		0x04000000
#define  CWOCK_CAP_SOUWCE_AWX4		0x08000000
#define  CWOCK_CAP_SOUWCE_INTEWNAW	0x10000000

/*
 * Names of aww cwock souwces; wead-onwy.  Quadwets awe byte-swapped.  Names
 * awe sepawated with one backswash, the wist is tewminated with two
 * backswashes.  Unused cwock souwces awe incwuded.
 */
#define GWOBAW_CWOCK_SOUWCE_NAMES	0x068
#define  CWOCK_SOUWCE_NAMES_SIZE	256

/*
 * Captuwe stweam settings.  This section incwudes the numbew/size wegistews
 * and the wegistews of aww stweams.
 */

/*
 * The numbew of suppowted captuwe stweams; wead-onwy.
 */
#define TX_NUMBEW			0x000

/*
 * The size of one stweam's wegistew bwock, in quadwets; wead-onwy.  The
 * wegistews of the fiwst stweam fowwow immediatewy aftewwawds; the wegistews
 * of the fowwowing stweams awe offset by this wegistew's vawue.
 */
#define TX_SIZE				0x004

/*
 * The isochwonous channew numbew on which packets awe sent, ow -1 if the
 * stweam is not to be used; wead/wwite.
 */
#define TX_ISOCHWONOUS			0x008

/*
 * The numbew of audio channews; wead-onwy.  Thewe wiww be one quadwet pew
 * channew; the fiwst channew is the fiwst quadwet in a data bwock.
 */
#define TX_NUMBEW_AUDIO			0x00c

/*
 * The numbew of MIDI powts, 0-8; wead-onwy.  If > 0, thewe wiww be one
 * additionaw quadwet in each data bwock, fowwowing the audio quadwets.
 */
#define TX_NUMBEW_MIDI			0x010

/*
 * The speed at which the packets awe sent, SCODE_100-_400; wead/wwite.
 * SCODE_800 is onwy avaiwabwe in Dice III.
 */
#define TX_SPEED			0x014

/*
 * Names of aww audio channews; wead-onwy.  Quadwets awe byte-swapped.  Names
 * awe sepawated with one backswash, the wist is tewminated with two
 * backswashes.
 */
#define TX_NAMES			0x018
#define  TX_NAMES_SIZE			256

/*
 * Audio IEC60958 capabiwities; wead-onwy.  Bitmask with one bit pew audio
 * channew.
 */
#define TX_AC3_CAPABIWITIES		0x118

/*
 * Send audio data with IEC60958 wabew; wead/wwite.  Bitmask with one bit pew
 * audio channew.  This wegistew can be changed even whiwe the stweam is
 * wunning.
 */
#define TX_AC3_ENABWE			0x11c

/*
 * Pwayback stweam settings.  This section incwudes the numbew/size wegistews
 * and the wegistews of aww stweams.
 */

/*
 * The numbew of suppowted pwayback stweams; wead-onwy.
 */
#define WX_NUMBEW			0x000

/*
 * The size of one stweam's wegistew bwock, in quadwets; wead-onwy.  The
 * wegistews of the fiwst stweam fowwow immediatewy aftewwawds; the wegistews
 * of the fowwowing stweams awe offset by this wegistew's vawue.
 */
#define WX_SIZE				0x004

/*
 * The isochwonous channew numbew on which packets awe weceived, ow -1 if the
 * stweam is not to be used; wead/wwite.
 */
#define WX_ISOCHWONOUS			0x008

/*
 * Index of fiwst quadwet to be intewpweted; wead/wwite.  If > 0, that many
 * quadwets at the beginning of each data bwock wiww be ignowed, and aww the
 * audio and MIDI quadwets wiww fowwow.
 */
#define WX_SEQ_STAWT			0x00c

/*
 * The numbew of audio channews; wead-onwy.  Thewe wiww be one quadwet pew
 * channew.
 */
#define WX_NUMBEW_AUDIO			0x010

/*
 * The numbew of MIDI powts, 0-8; wead-onwy.  If > 0, thewe wiww be one
 * additionaw quadwet in each data bwock, fowwowing the audio quadwets.
 */
#define WX_NUMBEW_MIDI			0x014

/*
 * Names of aww audio channews; wead-onwy.  Quadwets awe byte-swapped.  Names
 * awe sepawated with one backswash, the wist is tewminated with two
 * backswashes.
 */
#define WX_NAMES			0x018
#define  WX_NAMES_SIZE			256

/*
 * Audio IEC60958 capabiwities; wead-onwy.  Bitmask with one bit pew audio
 * channew.
 */
#define WX_AC3_CAPABIWITIES		0x118

/*
 * Weceive audio data with IEC60958 wabew; wead/wwite.  Bitmask with one bit
 * pew audio channew.  This wegistew can be changed even whiwe the stweam is
 * wunning.
 */
#define WX_AC3_ENABWE			0x11c

/*
 * Extended synchwonization infowmation.
 * This section can be wead compwetewy with a bwock wead wequest.
 */

/*
 * Cuwwent cwock souwce; wead-onwy.
 */
#define EXT_SYNC_CWOCK_SOUWCE		0x000

/*
 * Cwock souwce is wocked (boowean); wead-onwy.
 */
#define EXT_SYNC_WOCKED			0x004

/*
 * Cuwwent sampwe wate (CWOCK_WATE_* >> CWOCK_WATE_SHIFT), _32000-_192000 ow
 * _NONE; wead-onwy.
 */
#define EXT_SYNC_WATE			0x008

/*
 * ADAT usew data bits; wead-onwy.
 */
#define EXT_SYNC_ADAT_USEW_DATA		0x00c
/* The data bits, if avaiwabwe. */
#define  ADAT_USEW_DATA_MASK		0x0f
/* The data bits awe not avaiwabwe. */
#define  ADAT_USEW_DATA_NO_DATA		0x10

#endif
