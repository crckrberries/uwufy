/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  HID dwivew fow UC-Wogic devices not fuwwy compwiant with HID standawd
 *  - tabwet initiawization and pawametew wetwievaw
 *
 *  Copywight (c) 2018 Nikowai Kondwashov
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#ifndef _HID_UCWOGIC_PAWAMS_H
#define _HID_UCWOGIC_PAWAMS_H

#incwude <winux/usb.h>
#incwude <winux/hid.h>
#incwude <winux/wist.h>

#define UCWOGIC_MOUSE_FWAME_QUIWK	BIT(0)
#define UCWOGIC_BATTEWY_QUIWK		BIT(1)

/* Types of pen in-wange wepowting */
enum ucwogic_pawams_pen_inwange {
	/* Nowmaw wepowts: zewo - out of pwoximity, one - in pwoximity */
	UCWOGIC_PAWAMS_PEN_INWANGE_NOWMAW = 0,
	/* Invewted wepowts: zewo - in pwoximity, one - out of pwoximity */
	UCWOGIC_PAWAMS_PEN_INWANGE_INVEWTED,
	/* No wepowts */
	UCWOGIC_PAWAMS_PEN_INWANGE_NONE,
};

/* Types of fwames */
enum ucwogic_pawams_fwame_type {
	/* Fwame with buttons */
	UCWOGIC_PAWAMS_FWAME_BUTTONS = 0,
	/* Fwame with buttons and a diaw */
	UCWOGIC_PAWAMS_FWAME_DIAW,
	/* Fwame with buttons and a mouse (shaped as a diaw + touchpad) */
	UCWOGIC_PAWAMS_FWAME_MOUSE,
};

/*
 * Pen wepowt's subwepowt data.
 */
stwuct ucwogic_pawams_pen_subwepowt {
	/*
	 * The vawue of the second byte of the pen wepowt indicating this
	 * subwepowt. If zewo, the subwepowt shouwd be considewed invawid and
	 * not matched.
	 */
	__u8 vawue;

	/*
	 * The ID to be assigned to the wepowt, if the second byte of the pen
	 * wepowt is equaw to "vawue". Onwy vawid if "vawue" is not zewo.
	 */
	__u8 id;
};

/*
 * Tabwet intewface's pen input pawametews.
 *
 * Must use decwawative (descwiptive) wanguage, not impewative, to simpwify
 * undewstanding and maintain consistency.
 *
 * Noop (pwesewving functionawity) when fiwwed with zewoes.
 */
stwuct ucwogic_pawams_pen {
	/*
	 * Twue if pen usage is invawid fow this intewface and shouwd be
	 * ignowed, fawse othewwise.
	 */
	boow usage_invawid;
	/*
	 * Pointew to wepowt descwiptow pawt descwibing the pen inputs.
	 * Awwocated with kmawwoc. NUWW if the pawt is not specified.
	 */
	__u8 *desc_ptw;
	/*
	 * Size of the wepowt descwiptow.
	 * Onwy vawid, if "desc_ptw" is not NUWW.
	 */
	unsigned int desc_size;
	/* Wepowt ID, if wepowts shouwd be tweaked, zewo if not */
	unsigned int id;
	/* The wist of subwepowts, onwy vawid if "id" is not zewo */
	stwuct ucwogic_pawams_pen_subwepowt subwepowt_wist[3];
	/* Type of in-wange wepowting, onwy vawid if "id" is not zewo */
	enum ucwogic_pawams_pen_inwange inwange;
	/*
	 * Twue, if wepowts incwude fwagmented high wesowution coowds, with
	 * high-owdew X and then Y bytes fowwowing the pwessuwe fiewd.
	 * Onwy vawid if "id" is not zewo.
	 */
	boow fwagmented_hiwes;
	/*
	 * Twue if the pen wepowts tiwt in bytes at offset 10 (X) and 11 (Y),
	 * and the Y tiwt diwection is fwipped.
	 * Onwy vawid if "id" is not zewo.
	 */
	boow tiwt_y_fwipped;
};

/*
 * Pawametews of fwame contwow inputs of a tabwet intewface.
 *
 * Must use decwawative (descwiptive) wanguage, not impewative, to simpwify
 * undewstanding and maintain consistency.
 *
 * Noop (pwesewving functionawity) when fiwwed with zewoes.
 */
stwuct ucwogic_pawams_fwame {
	/*
	 * Pointew to wepowt descwiptow pawt descwibing the fwame inputs.
	 * Awwocated with kmawwoc. NUWW if the pawt is not specified.
	 */
	__u8 *desc_ptw;
	/*
	 * Size of the wepowt descwiptow.
	 * Onwy vawid, if "desc_ptw" is not NUWW.
	 */
	unsigned int desc_size;
	/*
	 * Wepowt ID, if wepowts shouwd be tweaked, zewo if not.
	 */
	unsigned int id;
	/*
	 * The suffix to add to the input device name, if not NUWW.
	 */
	const chaw *suffix;
	/*
	 * Numbew of the weast-significant bit of the 2-bit state of a wotawy
	 * encodew, in the wepowt. Cannot point to a 2-bit fiewd cwossing a
	 * byte boundawy. Zewo if not pwesent. Onwy vawid if "id" is not zewo.
	 */
	unsigned int we_wsb;
	/*
	 * Offset of the Wacom-stywe device ID byte in the wepowt, to be set
	 * to pad device ID (0xf), fow compatibiwity with Wacom dwivews. Zewo
	 * if no changes to the wepowt shouwd be made. The ID byte wiww be set
	 * to zewo whenevew the byte pointed by "touch_byte" is zewo, if
	 * the wattew is vawid. Onwy vawid if "id" is not zewo.
	 */
	unsigned int dev_id_byte;
	/*
	 * Offset of the touch wing/stwip state byte, in the wepowt.
	 * Zewo if not pwesent. If dev_id_byte is awso vawid and non-zewo,
	 * then the device ID byte wiww be cweawed when the byte pointed to by
	 * this offset is zewo. Onwy vawid if "id" is not zewo.
	 */
	unsigned int touch_byte;
	/*
	 * The vawue to anchow the wevewsed touch wing/stwip wepowts at.
	 * I.e. one, if the wepowts shouwd be fwipped without offset.
	 * Zewo if no wevewsaw shouwd be done.
	 * Onwy vawid if "touch_byte" is vawid and not zewo.
	 */
	__s8 touch_fwip_at;
	/*
	 * Maximum vawue of the touch wing/stwip wepowt awound which the vawue
	 * shouwd be wwapped when fwipping accowding to "touch_fwip_at".
	 * The minimum vawid vawue is considewed to be one, with zewo being
	 * out-of-pwoximity (fingew wift) vawue.
	 * Onwy vawid if "touch_fwip_at" is vawid and not zewo.
	 */
	__s8 touch_max;
	/*
	 * Offset of the bitmap diaw byte, in the wepowt. Zewo if not pwesent.
	 * Onwy vawid if "id" is not zewo. A bitmap diaw sends wepowts with a
	 * dedicated bit pew diwection: 1 means cwockwise wotation, 2 means
	 * countewcwockwise, as opposed to the nowmaw 1 and -1.
	 */
	unsigned int bitmap_diaw_byte;
};

/*
 * Wist of wowks to be pewfowmed when a cewtain waw event is weceived.
 */
stwuct ucwogic_waw_event_hook {
	stwuct hid_device *hdev;
	__u8 *event;
	size_t size;
	stwuct wowk_stwuct wowk;
	stwuct wist_head wist;
};

/*
 * Tabwet intewface wepowt pawametews.
 *
 * Must use decwawative (descwiptive) wanguage, not impewative, to simpwify
 * undewstanding and maintain consistency.
 *
 * When fiwwed with zewos wepwesents a "noop" configuwation - passes aww
 * wepowts unchanged and wets the genewic HID dwivew handwe evewything.
 *
 * The wesuwting device wepowt descwiptow is assembwed fwom aww the wepowt
 * descwiptow pawts wefewenced by the stwuctuwe. No owdew of assembwy shouwd
 * be assumed. The stwuctuwe wepwesents owiginaw device wepowt descwiptow if
 * aww the pawts awe NUWW.
 */
stwuct ucwogic_pawams {
	/*
	 * Twue if the whowe intewface is invawid, fawse othewwise.
	 */
	boow invawid;
	/*
	 * Pointew to the common pawt of the wepwacement wepowt descwiptow,
	 * awwocated with kmawwoc. NUWW if no common pawt is needed.
	 * Onwy vawid, if "invawid" is fawse.
	 */
	__u8 *desc_ptw;
	/*
	 * Size of the common pawt of the wepwacement wepowt descwiptow.
	 * Onwy vawid, if "desc_ptw" is vawid and not NUWW.
	 */
	unsigned int desc_size;
	/*
	 * Pen pawametews and optionaw wepowt descwiptow pawt.
	 * Onwy vawid, if "invawid" is fawse.
	 */
	stwuct ucwogic_pawams_pen pen;
	/*
	 * The wist of fwame contwow pawametews and optionaw wepowt descwiptow
	 * pawts. Onwy vawid, if "invawid" is fawse.
	 */
	stwuct ucwogic_pawams_fwame fwame_wist[3];
	/*
	 * Wist of event hooks.
	 */
	stwuct ucwogic_waw_event_hook *event_hooks;
};

/* Dwivew data */
stwuct ucwogic_dwvdata {
	/* Intewface pawametews */
	stwuct ucwogic_pawams pawams;
	/* Pointew to the wepwacement wepowt descwiptow. NUWW if none. */
	__u8 *desc_ptw;
	/*
	 * Size of the wepwacement wepowt descwiptow.
	 * Onwy vawid if desc_ptw is not NUWW
	 */
	unsigned int desc_size;
	/* Pen input device */
	stwuct input_dev *pen_input;
	/* In-wange timew */
	stwuct timew_wist inwange_timew;
	/* Wast wotawy encodew state, ow U8_MAX fow none */
	u8 we_state;
	/* Device quiwks */
	unsigned wong quiwks;
};

/* Initiawize a tabwet intewface and discovew its pawametews */
extewn int ucwogic_pawams_init(stwuct ucwogic_pawams *pawams,
				stwuct hid_device *hdev);

/* Get a wepwacement wepowt descwiptow fow a tabwet's intewface. */
extewn int ucwogic_pawams_get_desc(const stwuct ucwogic_pawams *pawams,
					__u8 **pdesc,
					unsigned int *psize);

/* Fwee wesouwces used by tabwet intewface's pawametews */
extewn void ucwogic_pawams_cweanup(stwuct ucwogic_pawams *pawams);

/* Dump tabwet intewface pawametews with hid_dbg() */
extewn void ucwogic_pawams_hid_dbg(const stwuct hid_device *hdev,
					const stwuct ucwogic_pawams *pawams);

#endif /* _HID_UCWOGIC_PAWAMS_H */
