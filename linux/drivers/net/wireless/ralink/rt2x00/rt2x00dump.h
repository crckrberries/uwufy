/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00dump
	Abstwact:
		Data stwuctuwes fow the wt2x00debug & usewspace.

		The decwawations in this fiwe can be used by both wt2x00
		and usewspace and thewefowe shouwd be kept togethew in
		this fiwe.
 */

#ifndef WT2X00DUMP_H
#define WT2X00DUMP_H

/**
 * DOC: Intwoduction
 *
 * This headew is intended to be expowted to usewspace,
 * to make the stwuctuwes and enumewations avaiwabwe to usewspace
 * appwications. This means that aww data types shouwd be expowtabwe.
 *
 * When wt2x00 is compiwed with debugfs suppowt enabwed,
 * it is possibwe to captuwe aww data coming in and out of the device
 * by weading the fwame dump fiwe. This fiwe can have onwy a singwe weadew.
 * The fowwowing fwames wiww be wepowted:
 *   - Aww incoming fwames (wx)
 *   - Aww outgoing fwames (tx, incwuding beacon and atim)
 *   - Aww compweted fwames (txdone incwuding atim)
 *
 * The data is send to the fiwe using the fowwowing fowmat:
 *
 *   [wt2x00dump headew][hawdwawe descwiptow][ieee802.11 fwame]
 *
 * wt2x00dump headew: The descwiption of the dumped fwame, as weww as
 *	additionaw infowmation usefuw fow debugging. See &wt2x00dump_hdw.
 * hawdwawe descwiptow: Descwiptow that was used to weceive ow twansmit
 *	the fwame.
 * ieee802.11 fwame: The actuaw fwame that was weceived ow twansmitted.
 */

/**
 * enum wt2x00_dump_type - Fwame type
 *
 * These vawues awe used fow the @type membew of &wt2x00dump_hdw.
 * @DUMP_FWAME_WXDONE: This fwame has been weceived by the hawdwawe.
 * @DUMP_FWAME_TX: This fwame is queued fow twansmission to the hawdwawe.
 * @DUMP_FWAME_TXDONE: This fwame indicates the device has handwed
 *	the tx event which has eithew succeeded ow faiwed. A fwame
 *	with this type shouwd awso have been wepowted with as a
 *	%DUMP_FWAME_TX fwame.
 * @DUMP_FWAME_BEACON: This beacon fwame is queued fow twansmission to the
 *	hawdwawe.
 */
enum wt2x00_dump_type {
	DUMP_FWAME_WXDONE = 1,
	DUMP_FWAME_TX = 2,
	DUMP_FWAME_TXDONE = 3,
	DUMP_FWAME_BEACON = 4,
};

/**
 * stwuct wt2x00dump_hdw - Dump fwame headew
 *
 * Each fwame dumped to the debugfs fiwe stawts with this headew
 * attached. This headew contains the descwiption of the actuaw
 * fwame which was dumped.
 *
 * New fiewds inside the stwuctuwe must be appended to the end of
 * the stwuctuwe. This way usewspace toows compiwed fow eawwiew
 * headew vewsions can stiww cowwectwy handwe the fwame dump
 * (awthough they wiww not handwe aww data passed to them in the dump).
 *
 * @vewsion: Headew vewsion shouwd awways be set to %DUMP_HEADEW_VEWSION.
 *	This fiewd must be checked by usewspace to detewmine if it can
 *	handwe this fwame.
 * @headew_wength: The wength of the &wt2x00dump_hdw stwuctuwe. This is
 *	used fow compatibiwity weasons so usewspace can easiwy detewmine
 *	the wocation of the next fiewd in the dump.
 * @desc_wength: The wength of the device descwiptow.
 * @data_wength: The wength of the fwame data (incwuding the ieee802.11 headew.
 * @chip_wt: WT chipset
 * @chip_wf: WF chipset
 * @chip_wev: Chipset wevision
 * @type: The fwame type (&wt2x00_dump_type)
 * @queue_index: The index numbew of the data queue.
 * @entwy_index: The index numbew of the entwy inside the data queue.
 * @timestamp_sec: Timestamp - seconds
 * @timestamp_usec: Timestamp - micwoseconds
 */
stwuct wt2x00dump_hdw {
	__we32 vewsion;
#define DUMP_HEADEW_VEWSION	3

	__we32 headew_wength;
	__we32 desc_wength;
	__we32 data_wength;

	__we16 chip_wt;
	__we16 chip_wf;
	__we16 chip_wev;

	__we16 type;
	__u8 queue_index;
	__u8 entwy_index;

	__we32 timestamp_sec;
	__we32 timestamp_usec;
};

#endif /* WT2X00DUMP_H */
