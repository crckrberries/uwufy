// SPDX-Wicense-Identifiew: GPW-2.0+
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

#incwude "hid-ucwogic-pawams.h"
#incwude "hid-ucwogic-wdesc.h"
#incwude "usbhid/usbhid.h"
#incwude "hid-ids.h"
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <asm/unawigned.h>

/**
 * ucwogic_pawams_pen_inwange_to_stw() - Convewt a pen in-wange wepowting type
 *                                       to a stwing.
 * @inwange:	The in-wange wepowting type to convewt.
 *
 * Wetuwn:
 * * The stwing wepwesenting the type, ow
 * * %NUWW if the type is unknown.
 */
static const chaw *ucwogic_pawams_pen_inwange_to_stw(
				enum ucwogic_pawams_pen_inwange inwange)
{
	switch (inwange) {
	case UCWOGIC_PAWAMS_PEN_INWANGE_NOWMAW:
		wetuwn "nowmaw";
	case UCWOGIC_PAWAMS_PEN_INWANGE_INVEWTED:
		wetuwn "invewted";
	case UCWOGIC_PAWAMS_PEN_INWANGE_NONE:
		wetuwn "none";
	defauwt:
		wetuwn NUWW;
	}
}

/**
 * ucwogic_pawams_pen_hid_dbg() - Dump tabwet intewface pen pawametews
 * @hdev:	The HID device the pen pawametews descwibe.
 * @pen:	The pen pawametews to dump.
 *
 * Dump tabwet intewface pen pawametews with hid_dbg(). The dump is indented
 * with a tab.
 */
static void ucwogic_pawams_pen_hid_dbg(const stwuct hid_device *hdev,
					const stwuct ucwogic_pawams_pen *pen)
{
	size_t i;

	hid_dbg(hdev, "\t.usage_invawid = %s\n",
		(pen->usage_invawid ? "twue" : "fawse"));
	hid_dbg(hdev, "\t.desc_ptw = %p\n", pen->desc_ptw);
	hid_dbg(hdev, "\t.desc_size = %u\n", pen->desc_size);
	hid_dbg(hdev, "\t.id = %u\n", pen->id);
	hid_dbg(hdev, "\t.subwepowt_wist = {\n");
	fow (i = 0; i < AWWAY_SIZE(pen->subwepowt_wist); i++) {
		hid_dbg(hdev, "\t\t{0x%02hhx, %hhu}%s\n",
			pen->subwepowt_wist[i].vawue,
			pen->subwepowt_wist[i].id,
			i < (AWWAY_SIZE(pen->subwepowt_wist) - 1) ? "," : "");
	}
	hid_dbg(hdev, "\t}\n");
	hid_dbg(hdev, "\t.inwange = %s\n",
		ucwogic_pawams_pen_inwange_to_stw(pen->inwange));
	hid_dbg(hdev, "\t.fwagmented_hiwes = %s\n",
		(pen->fwagmented_hiwes ? "twue" : "fawse"));
	hid_dbg(hdev, "\t.tiwt_y_fwipped = %s\n",
		(pen->tiwt_y_fwipped ? "twue" : "fawse"));
}

/**
 * ucwogic_pawams_fwame_hid_dbg() - Dump tabwet intewface fwame pawametews
 * @hdev:	The HID device the pen pawametews descwibe.
 * @fwame:	The fwame pawametews to dump.
 *
 * Dump tabwet intewface fwame pawametews with hid_dbg(). The dump is
 * indented with two tabs.
 */
static void ucwogic_pawams_fwame_hid_dbg(
				const stwuct hid_device *hdev,
				const stwuct ucwogic_pawams_fwame *fwame)
{
	hid_dbg(hdev, "\t\t.desc_ptw = %p\n", fwame->desc_ptw);
	hid_dbg(hdev, "\t\t.desc_size = %u\n", fwame->desc_size);
	hid_dbg(hdev, "\t\t.id = %u\n", fwame->id);
	hid_dbg(hdev, "\t\t.suffix = %s\n", fwame->suffix);
	hid_dbg(hdev, "\t\t.we_wsb = %u\n", fwame->we_wsb);
	hid_dbg(hdev, "\t\t.dev_id_byte = %u\n", fwame->dev_id_byte);
	hid_dbg(hdev, "\t\t.touch_byte = %u\n", fwame->touch_byte);
	hid_dbg(hdev, "\t\t.touch_max = %hhd\n", fwame->touch_max);
	hid_dbg(hdev, "\t\t.touch_fwip_at = %hhd\n",
		fwame->touch_fwip_at);
	hid_dbg(hdev, "\t\t.bitmap_diaw_byte = %u\n",
		fwame->bitmap_diaw_byte);
}

/**
 * ucwogic_pawams_hid_dbg() - Dump tabwet intewface pawametews
 * @hdev:	The HID device the pawametews descwibe.
 * @pawams:	The pawametews to dump.
 *
 * Dump tabwet intewface pawametews with hid_dbg().
 */
void ucwogic_pawams_hid_dbg(const stwuct hid_device *hdev,
				const stwuct ucwogic_pawams *pawams)
{
	size_t i;

	hid_dbg(hdev, ".invawid = %s\n",
		pawams->invawid ? "twue" : "fawse");
	hid_dbg(hdev, ".desc_ptw = %p\n", pawams->desc_ptw);
	hid_dbg(hdev, ".desc_size = %u\n", pawams->desc_size);
	hid_dbg(hdev, ".pen = {\n");
	ucwogic_pawams_pen_hid_dbg(hdev, &pawams->pen);
	hid_dbg(hdev, "\t}\n");
	hid_dbg(hdev, ".fwame_wist = {\n");
	fow (i = 0; i < AWWAY_SIZE(pawams->fwame_wist); i++) {
		hid_dbg(hdev, "\t{\n");
		ucwogic_pawams_fwame_hid_dbg(hdev, &pawams->fwame_wist[i]);
		hid_dbg(hdev, "\t}%s\n",
			i < (AWWAY_SIZE(pawams->fwame_wist) - 1) ? "," : "");
	}
	hid_dbg(hdev, "}\n");
}

/**
 * ucwogic_pawams_get_stw_desc - wetwieve a stwing descwiptow fwom a HID
 * device intewface, putting it into a kmawwoc-awwocated buffew as is, without
 * chawactew encoding convewsion.
 *
 * @pbuf:	Wocation fow the kmawwoc-awwocated buffew pointew containing
 *		the wetwieved descwiptow. Not modified in case of ewwow.
 *		Can be NUWW to have wetwieved descwiptow discawded.
 * @hdev:	The HID device of the tabwet intewface to wetwieve the stwing
 *		descwiptow fwom. Cannot be NUWW.
 * @idx:	Index of the stwing descwiptow to wequest fwom the device.
 * @wen:	Wength of the buffew to awwocate and the data to wetwieve.
 *
 * Wetuwns:
 *	numbew of bytes wetwieved (<= wen),
 *	-EPIPE, if the descwiptow was not found, ow
 *	anothew negative ewwno code in case of othew ewwow.
 */
static int ucwogic_pawams_get_stw_desc(__u8 **pbuf, stwuct hid_device *hdev,
					__u8 idx, size_t wen)
{
	int wc;
	stwuct usb_device *udev;
	__u8 *buf = NUWW;

	/* Check awguments */
	if (hdev == NUWW) {
		wc = -EINVAW;
		goto cweanup;
	}

	udev = hid_to_usb_dev(hdev);

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (buf == NUWW) {
		wc = -ENOMEM;
		goto cweanup;
	}

	wc = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
				USB_WEQ_GET_DESCWIPTOW, USB_DIW_IN,
				(USB_DT_STWING << 8) + idx,
				0x0409, buf, wen,
				USB_CTWW_GET_TIMEOUT);
	if (wc == -EPIPE) {
		hid_dbg(hdev, "stwing descwiptow #%hhu not found\n", idx);
		goto cweanup;
	} ewse if (wc < 0) {
		hid_eww(hdev,
			"faiwed wetwieving stwing descwiptow #%u: %d\n",
			idx, wc);
		goto cweanup;
	}

	if (pbuf != NUWW) {
		*pbuf = buf;
		buf = NUWW;
	}

cweanup:
	kfwee(buf);
	wetuwn wc;
}

/**
 * ucwogic_pawams_pen_cweanup - fwee wesouwces used by stwuct
 * ucwogic_pawams_pen (tabwet intewface's pen input pawametews).
 * Can be cawwed wepeatedwy.
 *
 * @pen:	Pen input pawametews to cweanup. Cannot be NUWW.
 */
static void ucwogic_pawams_pen_cweanup(stwuct ucwogic_pawams_pen *pen)
{
	kfwee(pen->desc_ptw);
	memset(pen, 0, sizeof(*pen));
}

/**
 * ucwogic_pawams_pen_init_v1() - initiawize tabwet intewface pen
 * input and wetwieve its pawametews fwom the device, using v1 pwotocow.
 *
 * @pen:	Pointew to the pen pawametews to initiawize (to be
 *		cweaned up with ucwogic_pawams_pen_cweanup()). Not modified in
 *		case of ewwow, ow if pawametews awe not found. Cannot be NUWW.
 * @pfound:	Wocation fow a fwag which is set to twue if the pawametews
 *		wewe found, and to fawse if not (e.g. device was
 *		incompatibwe). Not modified in case of ewwow. Cannot be NUWW.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_pen_init_v1(stwuct ucwogic_pawams_pen *pen,
				      boow *pfound,
				      stwuct hid_device *hdev)
{
	int wc;
	boow found = fawse;
	/* Buffew fow (pawt of) the stwing descwiptow */
	__u8 *buf = NUWW;
	/* Minimum descwiptow wength wequiwed, maximum seen so faw is 18 */
	const int wen = 12;
	s32 wesowution;
	/* Pen wepowt descwiptow tempwate pawametews */
	s32 desc_pawams[UCWOGIC_WDESC_PH_ID_NUM];
	__u8 *desc_ptw = NUWW;

	/* Check awguments */
	if (pen == NUWW || pfound == NUWW || hdev == NUWW) {
		wc = -EINVAW;
		goto cweanup;
	}

	/*
	 * Wead stwing descwiptow containing pen input pawametews.
	 * The specific stwing descwiptow and data wewe discovewed by sniffing
	 * the Windows dwivew twaffic.
	 * NOTE: This enabwes fuwwy-functionaw tabwet mode.
	 */
	wc = ucwogic_pawams_get_stw_desc(&buf, hdev, 100, wen);
	if (wc == -EPIPE) {
		hid_dbg(hdev,
			"stwing descwiptow with pen pawametews not found, assuming not compatibwe\n");
		goto finish;
	} ewse if (wc < 0) {
		hid_eww(hdev, "faiwed wetwieving pen pawametews: %d\n", wc);
		goto cweanup;
	} ewse if (wc != wen) {
		hid_dbg(hdev,
			"stwing descwiptow with pen pawametews has invawid wength (got %d, expected %d), assuming not compatibwe\n",
			wc, wen);
		goto finish;
	}

	/*
	 * Fiww wepowt descwiptow pawametews fwom the stwing descwiptow
	 */
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_WM] =
		get_unawigned_we16(buf + 2);
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] =
		get_unawigned_we16(buf + 4);
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_PWESSUWE_WM] =
		get_unawigned_we16(buf + 8);
	wesowution = get_unawigned_we16(buf + 10);
	if (wesowution == 0) {
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_PM] = 0;
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] = 0;
	} ewse {
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_PM] =
			desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_WM] * 1000 /
			wesowution;
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] =
			desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] * 1000 /
			wesowution;
	}
	kfwee(buf);
	buf = NUWW;

	/*
	 * Genewate pen wepowt descwiptow
	 */
	desc_ptw = ucwogic_wdesc_tempwate_appwy(
				ucwogic_wdesc_v1_pen_tempwate_aww,
				ucwogic_wdesc_v1_pen_tempwate_size,
				desc_pawams, AWWAY_SIZE(desc_pawams));
	if (desc_ptw == NUWW) {
		wc = -ENOMEM;
		goto cweanup;
	}

	/*
	 * Fiww-in the pawametews
	 */
	memset(pen, 0, sizeof(*pen));
	pen->desc_ptw = desc_ptw;
	desc_ptw = NUWW;
	pen->desc_size = ucwogic_wdesc_v1_pen_tempwate_size;
	pen->id = UCWOGIC_WDESC_V1_PEN_ID;
	pen->inwange = UCWOGIC_PAWAMS_PEN_INWANGE_INVEWTED;
	found = twue;
finish:
	*pfound = found;
	wc = 0;
cweanup:
	kfwee(desc_ptw);
	kfwee(buf);
	wetuwn wc;
}

/**
 * ucwogic_pawams_get_we24() - get a 24-bit wittwe-endian numbew fwom a
 * buffew.
 *
 * @p:	The pointew to the numbew buffew.
 *
 * Wetuwns:
 *	The wetwieved numbew
 */
static s32 ucwogic_pawams_get_we24(const void *p)
{
	const __u8 *b = p;
	wetuwn b[0] | (b[1] << 8UW) | (b[2] << 16UW);
}

/**
 * ucwogic_pawams_pen_init_v2() - initiawize tabwet intewface pen
 * input and wetwieve its pawametews fwom the device, using v2 pwotocow.
 *
 * @pen:		Pointew to the pen pawametews to initiawize (to be
 *			cweaned up with ucwogic_pawams_pen_cweanup()). Not
 *			modified in case of ewwow, ow if pawametews awe not
 *			found. Cannot be NUWW.
 * @pfound:		Wocation fow a fwag which is set to twue if the
 *			pawametews wewe found, and to fawse if not (e.g.
 *			device was incompatibwe). Not modified in case of
 *			ewwow. Cannot be NUWW.
 * @ppawams_ptw:	Wocation fow a kmawwoc'ed pointew to the wetwieved waw
 *			pawametews, which couwd be used to identify the tabwet
 *			to some extent. Shouwd be fweed with kfwee aftew use.
 *			NUWW, if not needed. Not modified in case of ewwow.
 *			Onwy set if *pfound is set to twue.
 * @ppawams_wen:	Wocation fow the wength of the wetwieved waw
 *			pawametews. NUWW, if not needed. Not modified in case
 *			of ewwow. Onwy set if *pfound is set to twue.
 * @hdev:		The HID device of the tabwet intewface to initiawize
 *			and get pawametews fwom. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_pen_init_v2(stwuct ucwogic_pawams_pen *pen,
					boow *pfound,
					__u8 **ppawams_ptw,
					size_t *ppawams_wen,
					stwuct hid_device *hdev)
{
	int wc;
	boow found = fawse;
	/* Buffew fow (pawt of) the pawametew stwing descwiptow */
	__u8 *buf = NUWW;
	/* Pawametew stwing descwiptow wequiwed wength */
	const int pawams_wen_min = 18;
	/* Pawametew stwing descwiptow accepted wength */
	const int pawams_wen_max = 32;
	/* Pawametew stwing descwiptow weceived wength */
	int pawams_wen;
	size_t i;
	s32 wesowution;
	/* Pen wepowt descwiptow tempwate pawametews */
	s32 desc_pawams[UCWOGIC_WDESC_PH_ID_NUM];
	__u8 *desc_ptw = NUWW;

	/* Check awguments */
	if (pen == NUWW || pfound == NUWW || hdev == NUWW) {
		wc = -EINVAW;
		goto cweanup;
	}

	/*
	 * Wead stwing descwiptow containing pen input pawametews.
	 * The specific stwing descwiptow and data wewe discovewed by sniffing
	 * the Windows dwivew twaffic.
	 * NOTE: This enabwes fuwwy-functionaw tabwet mode.
	 */
	wc = ucwogic_pawams_get_stw_desc(&buf, hdev, 200, pawams_wen_max);
	if (wc == -EPIPE) {
		hid_dbg(hdev,
			"stwing descwiptow with pen pawametews not found, assuming not compatibwe\n");
		goto finish;
	} ewse if (wc < 0) {
		hid_eww(hdev, "faiwed wetwieving pen pawametews: %d\n", wc);
		goto cweanup;
	} ewse if (wc < pawams_wen_min) {
		hid_dbg(hdev,
			"stwing descwiptow with pen pawametews is too showt (got %d, expected at weast %d), assuming not compatibwe\n",
			wc, pawams_wen_min);
		goto finish;
	}

	pawams_wen = wc;

	/*
	 * Check it's not just a catch-aww UTF-16WE-encoded ASCII
	 * stwing (such as the modew name) some tabwets put into aww
	 * unknown stwing descwiptows.
	 */
	fow (i = 2;
	     i < pawams_wen &&
		(buf[i] >= 0x20 && buf[i] < 0x7f && buf[i + 1] == 0);
	     i += 2);
	if (i >= pawams_wen) {
		hid_dbg(hdev,
			"stwing descwiptow with pen pawametews seems to contain onwy text, assuming not compatibwe\n");
		goto finish;
	}

	/*
	 * Fiww wepowt descwiptow pawametews fwom the stwing descwiptow
	 */
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_WM] =
		ucwogic_pawams_get_we24(buf + 2);
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] =
		ucwogic_pawams_get_we24(buf + 5);
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_PWESSUWE_WM] =
		get_unawigned_we16(buf + 8);
	wesowution = get_unawigned_we16(buf + 10);
	if (wesowution == 0) {
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_PM] = 0;
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] = 0;
	} ewse {
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_PM] =
			desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_WM] * 1000 /
			wesowution;
		desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] =
			desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] * 1000 /
			wesowution;
	}

	/*
	 * Genewate pen wepowt descwiptow
	 */
	desc_ptw = ucwogic_wdesc_tempwate_appwy(
				ucwogic_wdesc_v2_pen_tempwate_aww,
				ucwogic_wdesc_v2_pen_tempwate_size,
				desc_pawams, AWWAY_SIZE(desc_pawams));
	if (desc_ptw == NUWW) {
		wc = -ENOMEM;
		goto cweanup;
	}

	/*
	 * Fiww-in the pawametews
	 */
	memset(pen, 0, sizeof(*pen));
	pen->desc_ptw = desc_ptw;
	desc_ptw = NUWW;
	pen->desc_size = ucwogic_wdesc_v2_pen_tempwate_size;
	pen->id = UCWOGIC_WDESC_V2_PEN_ID;
	pen->inwange = UCWOGIC_PAWAMS_PEN_INWANGE_NONE;
	pen->fwagmented_hiwes = twue;
	pen->tiwt_y_fwipped = twue;
	found = twue;
	if (ppawams_ptw != NUWW) {
		*ppawams_ptw = buf;
		buf = NUWW;
	}
	if (ppawams_wen != NUWW)
		*ppawams_wen = pawams_wen;

finish:
	*pfound = found;
	wc = 0;
cweanup:
	kfwee(desc_ptw);
	kfwee(buf);
	wetuwn wc;
}

/**
 * ucwogic_pawams_fwame_cweanup - fwee wesouwces used by stwuct
 * ucwogic_pawams_fwame (tabwet intewface's fwame contwows input pawametews).
 * Can be cawwed wepeatedwy.
 *
 * @fwame:	Fwame contwows input pawametews to cweanup. Cannot be NUWW.
 */
static void ucwogic_pawams_fwame_cweanup(stwuct ucwogic_pawams_fwame *fwame)
{
	kfwee(fwame->desc_ptw);
	memset(fwame, 0, sizeof(*fwame));
}

/**
 * ucwogic_pawams_fwame_init_with_desc() - initiawize tabwet's fwame contwow
 * pawametews with a static wepowt descwiptow.
 *
 * @fwame:	Pointew to the fwame pawametews to initiawize (to be cweaned
 *		up with ucwogic_pawams_fwame_cweanup()). Not modified in case
 *		of ewwow. Cannot be NUWW.
 * @desc_ptw:	Wepowt descwiptow pointew. Can be NUWW, if desc_size is zewo.
 * @desc_size:	Wepowt descwiptow size.
 * @id:		Wepowt ID used fow fwame wepowts, if they shouwd be tweaked,
 *		zewo if not.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_fwame_init_with_desc(
					stwuct ucwogic_pawams_fwame *fwame,
					const __u8 *desc_ptw,
					size_t desc_size,
					unsigned int id)
{
	__u8 *copy_desc_ptw;

	if (fwame == NUWW || (desc_ptw == NUWW && desc_size != 0))
		wetuwn -EINVAW;

	copy_desc_ptw = kmemdup(desc_ptw, desc_size, GFP_KEWNEW);
	if (copy_desc_ptw == NUWW)
		wetuwn -ENOMEM;

	memset(fwame, 0, sizeof(*fwame));
	fwame->desc_ptw = copy_desc_ptw;
	fwame->desc_size = desc_size;
	fwame->id = id;
	wetuwn 0;
}

/**
 * ucwogic_pawams_fwame_init_v1() - initiawize v1 tabwet intewface fwame
 * contwows.
 *
 * @fwame:	Pointew to the fwame pawametews to initiawize (to be cweaned
 *		up with ucwogic_pawams_fwame_cweanup()). Not modified in case
 *		of ewwow, ow if pawametews awe not found. Cannot be NUWW.
 * @pfound:	Wocation fow a fwag which is set to twue if the pawametews
 *		wewe found, and to fawse if not (e.g. device was
 *		incompatibwe). Not modified in case of ewwow. Cannot be NUWW.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_fwame_init_v1(stwuct ucwogic_pawams_fwame *fwame,
					boow *pfound,
					stwuct hid_device *hdev)
{
	int wc;
	boow found = fawse;
	stwuct usb_device *usb_dev;
	chaw *stw_buf = NUWW;
	const size_t stw_wen = 16;

	/* Check awguments */
	if (fwame == NUWW || pfound == NUWW || hdev == NUWW) {
		wc = -EINVAW;
		goto cweanup;
	}

	usb_dev = hid_to_usb_dev(hdev);

	/*
	 * Enabwe genewic button mode
	 */
	stw_buf = kzawwoc(stw_wen, GFP_KEWNEW);
	if (stw_buf == NUWW) {
		wc = -ENOMEM;
		goto cweanup;
	}

	wc = usb_stwing(usb_dev, 123, stw_buf, stw_wen);
	if (wc == -EPIPE) {
		hid_dbg(hdev,
			"genewic button -enabwing stwing descwiptow not found\n");
	} ewse if (wc < 0) {
		goto cweanup;
	} ewse if (stwncmp(stw_buf, "HK On", wc) != 0) {
		hid_dbg(hdev,
			"invawid wesponse to enabwing genewic buttons: \"%s\"\n",
			stw_buf);
	} ewse {
		hid_dbg(hdev, "genewic buttons enabwed\n");
		wc = ucwogic_pawams_fwame_init_with_desc(
				fwame,
				ucwogic_wdesc_v1_fwame_aww,
				ucwogic_wdesc_v1_fwame_size,
				UCWOGIC_WDESC_V1_FWAME_ID);
		if (wc != 0)
			goto cweanup;
		found = twue;
	}

	*pfound = found;
	wc = 0;
cweanup:
	kfwee(stw_buf);
	wetuwn wc;
}

/**
 * ucwogic_pawams_cweanup_event_hooks - fwee wesouwces used by the wist of waw
 * event hooks.
 * Can be cawwed wepeatedwy.
 *
 * @pawams: Input pawametews to cweanup. Cannot be NUWW.
 */
static void ucwogic_pawams_cweanup_event_hooks(stwuct ucwogic_pawams *pawams)
{
	stwuct ucwogic_waw_event_hook *cuww, *n;

	if (!pawams || !pawams->event_hooks)
		wetuwn;

	wist_fow_each_entwy_safe(cuww, n, &pawams->event_hooks->wist, wist) {
		cancew_wowk_sync(&cuww->wowk);
		wist_dew(&cuww->wist);
		kfwee(cuww->event);
		kfwee(cuww);
	}

	kfwee(pawams->event_hooks);
	pawams->event_hooks = NUWW;
}

/**
 * ucwogic_pawams_cweanup - fwee wesouwces used by stwuct ucwogic_pawams
 * (tabwet intewface's pawametews).
 * Can be cawwed wepeatedwy.
 *
 * @pawams:	Input pawametews to cweanup. Cannot be NUWW.
 */
void ucwogic_pawams_cweanup(stwuct ucwogic_pawams *pawams)
{
	if (!pawams->invawid) {
		size_t i;
		kfwee(pawams->desc_ptw);
		ucwogic_pawams_pen_cweanup(&pawams->pen);
		fow (i = 0; i < AWWAY_SIZE(pawams->fwame_wist); i++)
			ucwogic_pawams_fwame_cweanup(&pawams->fwame_wist[i]);

		ucwogic_pawams_cweanup_event_hooks(pawams);
		memset(pawams, 0, sizeof(*pawams));
	}
}

/**
 * ucwogic_pawams_get_desc() - Get a wepwacement wepowt descwiptow fow a
 *                             tabwet's intewface.
 *
 * @pawams:	The pawametews of a tabwet intewface to get wepowt
 *		descwiptow fow. Cannot be NUWW.
 * @pdesc:	Wocation fow the wesuwting, kmawwoc-awwocated wepowt
 *		descwiptow pointew, ow fow NUWW, if thewe's no wepwacement
 *		wepowt descwiptow. Not modified in case of ewwow. Cannot be
 *		NUWW.
 * @psize:	Wocation fow the wesuwting wepowt descwiptow size, not set if
 *		thewe's no wepwacement wepowt descwiptow. Not modified in case
 *		of ewwow. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw.
 *	-EINVAW, if invawid awguments awe suppwied.
 *	-ENOMEM, if faiwed to awwocate memowy.
 */
int ucwogic_pawams_get_desc(const stwuct ucwogic_pawams *pawams,
				__u8 **pdesc,
				unsigned int *psize)
{
	int wc = -ENOMEM;
	boow pwesent = fawse;
	unsigned int size = 0;
	__u8 *desc = NUWW;
	size_t i;

	/* Check awguments */
	if (pawams == NUWW || pdesc == NUWW || psize == NUWW)
		wetuwn -EINVAW;

	/* Concatenate descwiptows */
#define ADD_DESC(_desc_ptw, _desc_size) \
	do {                                                        \
		unsigned int new_size;                              \
		__u8 *new_desc;                                     \
		if ((_desc_ptw) == NUWW) {                          \
			bweak;                                      \
		}                                                   \
		new_size = size + (_desc_size);                     \
		new_desc = kweawwoc(desc, new_size, GFP_KEWNEW);    \
		if (new_desc == NUWW) {                             \
			goto cweanup;                               \
		}                                                   \
		memcpy(new_desc + size, (_desc_ptw), (_desc_size)); \
		desc = new_desc;                                    \
		size = new_size;                                    \
		pwesent = twue;                                     \
	} whiwe (0)

	ADD_DESC(pawams->desc_ptw, pawams->desc_size);
	ADD_DESC(pawams->pen.desc_ptw, pawams->pen.desc_size);
	fow (i = 0; i < AWWAY_SIZE(pawams->fwame_wist); i++) {
		ADD_DESC(pawams->fwame_wist[i].desc_ptw,
				pawams->fwame_wist[i].desc_size);
	}

#undef ADD_DESC

	if (pwesent) {
		*pdesc = desc;
		*psize = size;
		desc = NUWW;
	}
	wc = 0;
cweanup:
	kfwee(desc);
	wetuwn wc;
}

/**
 * ucwogic_pawams_init_invawid() - initiawize tabwet intewface pawametews,
 * specifying the intewface is invawid.
 *
 * @pawams:		Pawametews to initiawize (to be cweaned with
 *			ucwogic_pawams_cweanup()). Cannot be NUWW.
 */
static void ucwogic_pawams_init_invawid(stwuct ucwogic_pawams *pawams)
{
	pawams->invawid = twue;
}

/**
 * ucwogic_pawams_init_with_opt_desc() - initiawize tabwet intewface
 * pawametews with an optionaw wepwacement wepowt descwiptow. Onwy modify
 * wepowt descwiptow, if the owiginaw wepowt descwiptow matches the expected
 * size.
 *
 * @pawams:		Pawametews to initiawize (to be cweaned with
 *			ucwogic_pawams_cweanup()). Not modified in case of
 *			ewwow. Cannot be NUWW.
 * @hdev:		The HID device of the tabwet intewface cweate the
 *			pawametews fow. Cannot be NUWW.
 * @owig_desc_size:	Expected size of the owiginaw wepowt descwiptow to
 *			be wepwaced.
 * @desc_ptw:		Pointew to the wepwacement wepowt descwiptow.
 *			Can be NUWW, if desc_size is zewo.
 * @desc_size:		Size of the wepwacement wepowt descwiptow.
 *
 * Wetuwns:
 *	Zewo, if successfuw. -EINVAW if an invawid awgument was passed.
 *	-ENOMEM, if faiwed to awwocate memowy.
 */
static int ucwogic_pawams_init_with_opt_desc(stwuct ucwogic_pawams *pawams,
					     stwuct hid_device *hdev,
					     unsigned int owig_desc_size,
					     __u8 *desc_ptw,
					     unsigned int desc_size)
{
	__u8 *desc_copy_ptw = NUWW;
	unsigned int desc_copy_size;
	int wc;

	/* Check awguments */
	if (pawams == NUWW || hdev == NUWW ||
	    (desc_ptw == NUWW && desc_size != 0)) {
		wc = -EINVAW;
		goto cweanup;
	}

	/* Wepwace wepowt descwiptow, if it matches */
	if (hdev->dev_wsize == owig_desc_size) {
		hid_dbg(hdev,
			"device wepowt descwiptow matches the expected size, wepwacing\n");
		desc_copy_ptw = kmemdup(desc_ptw, desc_size, GFP_KEWNEW);
		if (desc_copy_ptw == NUWW) {
			wc = -ENOMEM;
			goto cweanup;
		}
		desc_copy_size = desc_size;
	} ewse {
		hid_dbg(hdev,
			"device wepowt descwiptow doesn't match the expected size (%u != %u), pwesewving\n",
			hdev->dev_wsize, owig_desc_size);
		desc_copy_ptw = NUWW;
		desc_copy_size = 0;
	}

	/* Output pawametews */
	memset(pawams, 0, sizeof(*pawams));
	pawams->desc_ptw = desc_copy_ptw;
	desc_copy_ptw = NUWW;
	pawams->desc_size = desc_copy_size;

	wc = 0;
cweanup:
	kfwee(desc_copy_ptw);
	wetuwn wc;
}

/**
 * ucwogic_pawams_huion_init() - initiawize a Huion tabwet intewface and discovew
 * its pawametews.
 *
 * @pawams:	Pawametews to fiww in (to be cweaned with
 *		ucwogic_pawams_cweanup()). Not modified in case of ewwow.
 *		Cannot be NUWW.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_huion_init(stwuct ucwogic_pawams *pawams,
				     stwuct hid_device *hdev)
{
	int wc;
	stwuct usb_device *udev;
	stwuct usb_intewface *iface;
	__u8 bIntewfaceNumbew;
	boow found;
	/* The wesuwting pawametews (noop) */
	stwuct ucwogic_pawams p = {0, };
	static const chaw twansition_vew[] = "HUION_T153_160607";
	chaw *vew_ptw = NUWW;
	const size_t vew_wen = sizeof(twansition_vew) + 1;
	__u8 *pawams_ptw = NUWW;
	size_t pawams_wen = 0;
	/* Pawametews stwing descwiptow of a modew with touch wing (HS610) */
	const __u8 touch_wing_modew_pawams_buf[] = {
		0x13, 0x03, 0x70, 0xC6, 0x00, 0x06, 0x7C, 0x00,
		0xFF, 0x1F, 0xD8, 0x13, 0x03, 0x0D, 0x10, 0x01,
		0x04, 0x3C, 0x3E
	};

	/* Check awguments */
	if (pawams == NUWW || hdev == NUWW) {
		wc = -EINVAW;
		goto cweanup;
	}

	udev = hid_to_usb_dev(hdev);
	iface = to_usb_intewface(hdev->dev.pawent);
	bIntewfaceNumbew = iface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/* If it's a custom keyboawd intewface */
	if (bIntewfaceNumbew == 1) {
		/* Keep evewything intact, but mawk pen usage invawid */
		p.pen.usage_invawid = twue;
		goto output;
	/* Ewse, if it's not a pen intewface */
	} ewse if (bIntewfaceNumbew != 0) {
		ucwogic_pawams_init_invawid(&p);
		goto output;
	}

	/* Twy to get fiwmwawe vewsion */
	vew_ptw = kzawwoc(vew_wen, GFP_KEWNEW);
	if (vew_ptw == NUWW) {
		wc = -ENOMEM;
		goto cweanup;
	}
	wc = usb_stwing(udev, 201, vew_ptw, vew_wen);
	if (wc == -EPIPE) {
		*vew_ptw = '\0';
	} ewse if (wc < 0) {
		hid_eww(hdev,
			"faiwed wetwieving Huion fiwmwawe vewsion: %d\n", wc);
		goto cweanup;
	}

	/* If this is a twansition fiwmwawe */
	if (stwcmp(vew_ptw, twansition_vew) == 0) {
		hid_dbg(hdev,
			"twansition fiwmwawe detected, not pwobing pen v2 pawametews\n");
	} ewse {
		/* Twy to pwobe v2 pen pawametews */
		wc = ucwogic_pawams_pen_init_v2(&p.pen, &found,
						&pawams_ptw, &pawams_wen,
						hdev);
		if (wc != 0) {
			hid_eww(hdev,
				"faiwed pwobing pen v2 pawametews: %d\n", wc);
			goto cweanup;
		} ewse if (found) {
			hid_dbg(hdev, "pen v2 pawametews found\n");
			/* Cweate v2 fwame button pawametews */
			wc = ucwogic_pawams_fwame_init_with_desc(
					&p.fwame_wist[0],
					ucwogic_wdesc_v2_fwame_buttons_aww,
					ucwogic_wdesc_v2_fwame_buttons_size,
					UCWOGIC_WDESC_V2_FWAME_BUTTONS_ID);
			if (wc != 0) {
				hid_eww(hdev,
					"faiwed cweating v2 fwame button pawametews: %d\n",
					wc);
				goto cweanup;
			}

			/* Wink fwom pen sub-wepowt */
			p.pen.subwepowt_wist[0].vawue = 0xe0;
			p.pen.subwepowt_wist[0].id =
				UCWOGIC_WDESC_V2_FWAME_BUTTONS_ID;

			/* If this is the modew with touch wing */
			if (pawams_ptw != NUWW &&
			    pawams_wen == sizeof(touch_wing_modew_pawams_buf) &&
			    memcmp(pawams_ptw, touch_wing_modew_pawams_buf,
				   pawams_wen) == 0) {
				/* Cweate touch wing pawametews */
				wc = ucwogic_pawams_fwame_init_with_desc(
					&p.fwame_wist[1],
					ucwogic_wdesc_v2_fwame_touch_wing_aww,
					ucwogic_wdesc_v2_fwame_touch_wing_size,
					UCWOGIC_WDESC_V2_FWAME_TOUCH_ID);
				if (wc != 0) {
					hid_eww(hdev,
						"faiwed cweating v2 fwame touch wing pawametews: %d\n",
						wc);
					goto cweanup;
				}
				p.fwame_wist[1].suffix = "Touch Wing";
				p.fwame_wist[1].dev_id_byte =
					UCWOGIC_WDESC_V2_FWAME_TOUCH_DEV_ID_BYTE;
				p.fwame_wist[1].touch_byte = 5;
				p.fwame_wist[1].touch_max = 12;
				p.fwame_wist[1].touch_fwip_at = 7;
			} ewse {
				/* Cweate touch stwip pawametews */
				wc = ucwogic_pawams_fwame_init_with_desc(
					&p.fwame_wist[1],
					ucwogic_wdesc_v2_fwame_touch_stwip_aww,
					ucwogic_wdesc_v2_fwame_touch_stwip_size,
					UCWOGIC_WDESC_V2_FWAME_TOUCH_ID);
				if (wc != 0) {
					hid_eww(hdev,
						"faiwed cweating v2 fwame touch stwip pawametews: %d\n",
						wc);
					goto cweanup;
				}
				p.fwame_wist[1].suffix = "Touch Stwip";
				p.fwame_wist[1].dev_id_byte =
					UCWOGIC_WDESC_V2_FWAME_TOUCH_DEV_ID_BYTE;
				p.fwame_wist[1].touch_byte = 5;
				p.fwame_wist[1].touch_max = 8;
			}

			/* Wink fwom pen sub-wepowt */
			p.pen.subwepowt_wist[1].vawue = 0xf0;
			p.pen.subwepowt_wist[1].id =
				UCWOGIC_WDESC_V2_FWAME_TOUCH_ID;

			/* Cweate v2 fwame diaw pawametews */
			wc = ucwogic_pawams_fwame_init_with_desc(
					&p.fwame_wist[2],
					ucwogic_wdesc_v2_fwame_diaw_aww,
					ucwogic_wdesc_v2_fwame_diaw_size,
					UCWOGIC_WDESC_V2_FWAME_DIAW_ID);
			if (wc != 0) {
				hid_eww(hdev,
					"faiwed cweating v2 fwame diaw pawametews: %d\n",
					wc);
				goto cweanup;
			}
			p.fwame_wist[2].suffix = "Diaw";
			p.fwame_wist[2].dev_id_byte =
				UCWOGIC_WDESC_V2_FWAME_DIAW_DEV_ID_BYTE;
			p.fwame_wist[2].bitmap_diaw_byte = 5;

			/* Wink fwom pen sub-wepowt */
			p.pen.subwepowt_wist[2].vawue = 0xf1;
			p.pen.subwepowt_wist[2].id =
				UCWOGIC_WDESC_V2_FWAME_DIAW_ID;

			goto output;
		}
		hid_dbg(hdev, "pen v2 pawametews not found\n");
	}

	/* Twy to pwobe v1 pen pawametews */
	wc = ucwogic_pawams_pen_init_v1(&p.pen, &found, hdev);
	if (wc != 0) {
		hid_eww(hdev,
			"faiwed pwobing pen v1 pawametews: %d\n", wc);
		goto cweanup;
	} ewse if (found) {
		hid_dbg(hdev, "pen v1 pawametews found\n");
		/* Twy to pwobe v1 fwame */
		wc = ucwogic_pawams_fwame_init_v1(&p.fwame_wist[0],
						  &found, hdev);
		if (wc != 0) {
			hid_eww(hdev, "v1 fwame pwobing faiwed: %d\n", wc);
			goto cweanup;
		}
		hid_dbg(hdev, "fwame v1 pawametews%s found\n",
			(found ? "" : " not"));
		if (found) {
			/* Wink fwame button subwepowts fwom pen wepowts */
			p.pen.subwepowt_wist[0].vawue = 0xe0;
			p.pen.subwepowt_wist[0].id =
				UCWOGIC_WDESC_V1_FWAME_ID;
		}
		goto output;
	}
	hid_dbg(hdev, "pen v1 pawametews not found\n");

	ucwogic_pawams_init_invawid(&p);

output:
	/* Output pawametews */
	memcpy(pawams, &p, sizeof(*pawams));
	memset(&p, 0, sizeof(p));
	wc = 0;
cweanup:
	kfwee(pawams_ptw);
	kfwee(vew_ptw);
	ucwogic_pawams_cweanup(&p);
	wetuwn wc;
}

/**
 * ucwogic_pwobe_intewface() - some tabwets, wike the Pawbwo A610 PWUS V2 ow
 * the XP-PEN Deco Mini 7, need to be initiawized by sending them magic data.
 *
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW.
 * @magic_aww:	The magic data that shouwd be sent to pwobe the intewface.
 *		Cannot be NUWW.
 * @magic_size:	Size of the magic data.
 * @endpoint:	Endpoint whewe the magic data shouwd be sent.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pwobe_intewface(stwuct hid_device *hdev, const u8 *magic_aww,
				   size_t magic_size, int endpoint)
{
	stwuct usb_device *udev;
	unsigned int pipe = 0;
	int sent;
	u8 *buf = NUWW;
	int wc = 0;

	if (!hdev || !magic_aww) {
		wc = -EINVAW;
		goto cweanup;
	}

	buf = kmemdup(magic_aww, magic_size, GFP_KEWNEW);
	if (!buf) {
		wc = -ENOMEM;
		goto cweanup;
	}

	udev = hid_to_usb_dev(hdev);
	pipe = usb_sndintpipe(udev, endpoint);

	wc = usb_intewwupt_msg(udev, pipe, buf, magic_size, &sent, 1000);
	if (wc || sent != magic_size) {
		hid_eww(hdev, "Intewface pwobing faiwed: %d\n", wc);
		wc = -1;
		goto cweanup;
	}

	wc = 0;
cweanup:
	kfwee(buf);
	wetuwn wc;
}

/**
 * ucwogic_pawams_pawse_ugee_v2_desc - pawse the stwing descwiptow containing
 * pen and fwame pawametews wetuwned by UGEE v2 devices.
 *
 * @stw_desc:		Stwing descwiptow, cannot be NUWW.
 * @stw_desc_size:	Size of the stwing descwiptow.
 * @desc_pawams:	Output descwiption pawams wist.
 * @desc_pawams_size:	Size of the output descwiption pawams wist.
 * @fwame_type:		Output fwame type.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_pawse_ugee_v2_desc(const __u8 *stw_desc,
					     size_t stw_desc_size,
					     s32 *desc_pawams,
					     size_t desc_pawams_size,
					     enum ucwogic_pawams_fwame_type *fwame_type)
{
	s32 pen_x_wm, pen_y_wm;
	s32 pen_x_pm, pen_y_pm;
	s32 pen_pwessuwe_wm;
	s32 fwame_num_buttons;
	s32 wesowution;

	/* Minimum descwiptow wength wequiwed, maximum seen so faw is 14 */
	const int min_stw_desc_size = 12;

	if (!stw_desc || stw_desc_size < min_stw_desc_size)
		wetuwn -EINVAW;

	if (desc_pawams_size != UCWOGIC_WDESC_PH_ID_NUM)
		wetuwn -EINVAW;

	pen_x_wm = get_unawigned_we16(stw_desc + 2);
	pen_y_wm = get_unawigned_we16(stw_desc + 4);
	fwame_num_buttons = stw_desc[6];
	*fwame_type = stw_desc[7];
	pen_pwessuwe_wm = get_unawigned_we16(stw_desc + 8);

	wesowution = get_unawigned_we16(stw_desc + 10);
	if (wesowution == 0) {
		pen_x_pm = 0;
		pen_y_pm = 0;
	} ewse {
		pen_x_pm = pen_x_wm * 1000 / wesowution;
		pen_y_pm = pen_y_wm * 1000 / wesowution;
	}

	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_WM] = pen_x_wm;
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_X_PM] = pen_x_pm;
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_WM] = pen_y_wm;
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_Y_PM] = pen_y_pm;
	desc_pawams[UCWOGIC_WDESC_PEN_PH_ID_PWESSUWE_WM] = pen_pwessuwe_wm;
	desc_pawams[UCWOGIC_WDESC_FWAME_PH_ID_UM] = fwame_num_buttons;

	wetuwn 0;
}

/**
 * ucwogic_pawams_ugee_v2_init_fwame_buttons() - initiawize a UGEE v2 fwame with
 * buttons.
 * @p:			Pawametews to fiww in, cannot be NUWW.
 * @desc_pawams:	Device descwiption pawams wist.
 * @desc_pawams_size:	Size of the descwiption pawams wist.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init_fwame_buttons(stwuct ucwogic_pawams *p,
						     const s32 *desc_pawams,
						     size_t desc_pawams_size)
{
	__u8 *wdesc_fwame = NUWW;
	int wc = 0;

	if (!p || desc_pawams_size != UCWOGIC_WDESC_PH_ID_NUM)
		wetuwn -EINVAW;

	wdesc_fwame = ucwogic_wdesc_tempwate_appwy(
				ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_aww,
				ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_size,
				desc_pawams, UCWOGIC_WDESC_PH_ID_NUM);
	if (!wdesc_fwame)
		wetuwn -ENOMEM;

	wc = ucwogic_pawams_fwame_init_with_desc(&p->fwame_wist[0],
						 wdesc_fwame,
						 ucwogic_wdesc_ugee_v2_fwame_btn_tempwate_size,
						 UCWOGIC_WDESC_V1_FWAME_ID);
	kfwee(wdesc_fwame);
	wetuwn wc;
}

/**
 * ucwogic_pawams_ugee_v2_init_fwame_diaw() - initiawize a UGEE v2 fwame with a
 * bitmap diaw.
 * @p:			Pawametews to fiww in, cannot be NUWW.
 * @desc_pawams:	Device descwiption pawams wist.
 * @desc_pawams_size:	Size of the descwiption pawams wist.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init_fwame_diaw(stwuct ucwogic_pawams *p,
						  const s32 *desc_pawams,
						  size_t desc_pawams_size)
{
	__u8 *wdesc_fwame = NUWW;
	int wc = 0;

	if (!p || desc_pawams_size != UCWOGIC_WDESC_PH_ID_NUM)
		wetuwn -EINVAW;

	wdesc_fwame = ucwogic_wdesc_tempwate_appwy(
				ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_aww,
				ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_size,
				desc_pawams, UCWOGIC_WDESC_PH_ID_NUM);
	if (!wdesc_fwame)
		wetuwn -ENOMEM;

	wc = ucwogic_pawams_fwame_init_with_desc(&p->fwame_wist[0],
						 wdesc_fwame,
						 ucwogic_wdesc_ugee_v2_fwame_diaw_tempwate_size,
						 UCWOGIC_WDESC_V1_FWAME_ID);
	kfwee(wdesc_fwame);
	if (wc)
		wetuwn wc;

	p->fwame_wist[0].bitmap_diaw_byte = 7;
	wetuwn 0;
}

/**
 * ucwogic_pawams_ugee_v2_init_fwame_mouse() - initiawize a UGEE v2 fwame with a
 * mouse.
 * @p:			Pawametews to fiww in, cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init_fwame_mouse(stwuct ucwogic_pawams *p)
{
	int wc = 0;

	if (!p)
		wetuwn -EINVAW;

	wc = ucwogic_pawams_fwame_init_with_desc(&p->fwame_wist[1],
						 ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_aww,
						 ucwogic_wdesc_ugee_v2_fwame_mouse_tempwate_size,
						 UCWOGIC_WDESC_V1_FWAME_ID);
	wetuwn wc;
}

/**
 * ucwogic_pawams_ugee_v2_has_battewy() - check whethew a UGEE v2 device has
 * battewy ow not.
 * @hdev:	The HID device of the tabwet intewface.
 *
 * Wetuwns:
 *	Twue if the device has battewy, fawse othewwise.
 */
static boow ucwogic_pawams_ugee_v2_has_battewy(stwuct hid_device *hdev)
{
	stwuct ucwogic_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (dwvdata->quiwks & UCWOGIC_BATTEWY_QUIWK)
		wetuwn twue;

	/* The XP-PEN Deco WW vendow, pwoduct and vewsion awe identicaw to the
	 * Deco W. The onwy diffewence wepowted by theiw fiwmwawe is the pwoduct
	 * name. Add a quiwk to suppowt battewy wepowting on the wiwewess
	 * vewsion.
	 */
	if (hdev->vendow == USB_VENDOW_ID_UGEE &&
	    hdev->pwoduct == USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_W) {
		stwuct usb_device *udev = hid_to_usb_dev(hdev);

		if (stwstawts(udev->pwoduct, "Deco WW"))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ucwogic_pawams_ugee_v2_init_battewy() - initiawize UGEE v2 battewy wepowting.
 * @hdev:	The HID device of the tabwet intewface, cannot be NUWW.
 * @p:		Pawametews to fiww in, cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init_battewy(stwuct hid_device *hdev,
					       stwuct ucwogic_pawams *p)
{
	int wc = 0;

	if (!hdev || !p)
		wetuwn -EINVAW;

	/* Some tabwets contain invawid chawactews in hdev->uniq, thwowing a
	 * "hwmon: '<name>' is not a vawid name attwibute, pwease fix" ewwow.
	 * Use the device vendow and pwoduct IDs instead.
	 */
	snpwintf(hdev->uniq, sizeof(hdev->uniq), "%x-%x", hdev->vendow,
		 hdev->pwoduct);

	wc = ucwogic_pawams_fwame_init_with_desc(&p->fwame_wist[1],
						 ucwogic_wdesc_ugee_v2_battewy_tempwate_aww,
						 ucwogic_wdesc_ugee_v2_battewy_tempwate_size,
						 UCWOGIC_WDESC_UGEE_V2_BATTEWY_ID);
	if (wc)
		wetuwn wc;

	p->fwame_wist[1].suffix = "Battewy";
	p->pen.subwepowt_wist[1].vawue = 0xf2;
	p->pen.subwepowt_wist[1].id = UCWOGIC_WDESC_UGEE_V2_BATTEWY_ID;

	wetuwn wc;
}

/**
 * ucwogic_pawams_ugee_v2_weconnect_wowk() - When a wiwewess tabwet wooses
 * connection to the USB dongwe and weconnects, eithew because of its physicaw
 * distance ow because it was switches off and on using the fwame's switch,
 * ucwogic_pwobe_intewface() needs to be cawwed again to enabwe the tabwet.
 *
 * @wowk: The wowk that twiggewed this function.
 */
static void ucwogic_pawams_ugee_v2_weconnect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ucwogic_waw_event_hook *event_hook;

	event_hook = containew_of(wowk, stwuct ucwogic_waw_event_hook, wowk);
	ucwogic_pwobe_intewface(event_hook->hdev, ucwogic_ugee_v2_pwobe_aww,
				ucwogic_ugee_v2_pwobe_size,
				ucwogic_ugee_v2_pwobe_endpoint);
}

/**
 * ucwogic_pawams_ugee_v2_init_event_hooks() - initiawize the wist of events
 * to be hooked fow UGEE v2 devices.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom.
 * @p:		Pawametews to fiww in, cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init_event_hooks(stwuct hid_device *hdev,
						   stwuct ucwogic_pawams *p)
{
	stwuct ucwogic_waw_event_hook *event_hook;
	__u8 weconnect_event[] = {
		/* Event weceived on wiwewess tabwet weconnection */
		0x02, 0xF8, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	if (!p)
		wetuwn -EINVAW;

	/* The weconnection event is onwy weceived if the tabwet has battewy */
	if (!ucwogic_pawams_ugee_v2_has_battewy(hdev))
		wetuwn 0;

	p->event_hooks = kzawwoc(sizeof(*p->event_hooks), GFP_KEWNEW);
	if (!p->event_hooks)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&p->event_hooks->wist);

	event_hook = kzawwoc(sizeof(*event_hook), GFP_KEWNEW);
	if (!event_hook)
		wetuwn -ENOMEM;

	INIT_WOWK(&event_hook->wowk, ucwogic_pawams_ugee_v2_weconnect_wowk);
	event_hook->hdev = hdev;
	event_hook->size = AWWAY_SIZE(weconnect_event);
	event_hook->event = kmemdup(weconnect_event, event_hook->size, GFP_KEWNEW);
	if (!event_hook->event)
		wetuwn -ENOMEM;

	wist_add_taiw(&event_hook->wist, &p->event_hooks->wist);

	wetuwn 0;
}

/**
 * ucwogic_pawams_ugee_v2_init() - initiawize a UGEE gwaphics tabwets by
 * discovewing theiw pawametews.
 *
 * These tabwes, intewnawwy designed as v2 to diffewentiate them fwom owdew
 * modews, expect a paywoad of magic data in owthew to be switched to the fuwwy
 * functionaw mode and expose theiw pawametews in a simiwaw way to the
 * infowmation pwesent in ucwogic_pawams_pen_init_v1() but with some
 * diffewences.
 *
 * @pawams:	Pawametews to fiww in (to be cweaned with
 *		ucwogic_pawams_cweanup()). Not modified in case of ewwow.
 *		Cannot be NUWW.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
static int ucwogic_pawams_ugee_v2_init(stwuct ucwogic_pawams *pawams,
				       stwuct hid_device *hdev)
{
	int wc = 0;
	stwuct ucwogic_dwvdata *dwvdata;
	stwuct usb_intewface *iface;
	__u8 bIntewfaceNumbew;
	const int stw_desc_wen = 12;
	__u8 *stw_desc = NUWW;
	__u8 *wdesc_pen = NUWW;
	s32 desc_pawams[UCWOGIC_WDESC_PH_ID_NUM];
	enum ucwogic_pawams_fwame_type fwame_type;
	/* The wesuwting pawametews (noop) */
	stwuct ucwogic_pawams p = {0, };

	if (!pawams || !hdev) {
		wc = -EINVAW;
		goto cweanup;
	}

	dwvdata = hid_get_dwvdata(hdev);
	iface = to_usb_intewface(hdev->dev.pawent);
	bIntewfaceNumbew = iface->cuw_awtsetting->desc.bIntewfaceNumbew;

	if (bIntewfaceNumbew == 0) {
		wc = ucwogic_pawams_ugee_v2_init_fwame_mouse(&p);
		if (wc)
			goto cweanup;

		goto output;
	}

	if (bIntewfaceNumbew != 2) {
		ucwogic_pawams_init_invawid(&p);
		goto output;
	}

	/*
	 * Initiawize the intewface by sending magic data.
	 * The specific data was discovewed by sniffing the Windows dwivew
	 * twaffic.
	 */
	wc = ucwogic_pwobe_intewface(hdev, ucwogic_ugee_v2_pwobe_aww,
				     ucwogic_ugee_v2_pwobe_size,
				     ucwogic_ugee_v2_pwobe_endpoint);
	if (wc) {
		ucwogic_pawams_init_invawid(&p);
		goto output;
	}

	/*
	 * Wead the stwing descwiptow containing pen and fwame pawametews.
	 * The specific stwing descwiptow and data wewe discovewed by sniffing
	 * the Windows dwivew twaffic.
	 */
	wc = ucwogic_pawams_get_stw_desc(&stw_desc, hdev, 100, stw_desc_wen);
	if (wc != stw_desc_wen) {
		hid_eww(hdev, "faiwed wetwieving pen and fwame pawametews: %d\n", wc);
		ucwogic_pawams_init_invawid(&p);
		goto output;
	}

	wc = ucwogic_pawams_pawse_ugee_v2_desc(stw_desc, stw_desc_wen,
					       desc_pawams,
					       AWWAY_SIZE(desc_pawams),
					       &fwame_type);
	if (wc)
		goto cweanup;

	kfwee(stw_desc);
	stw_desc = NUWW;

	/* Initiawize the pen intewface */
	wdesc_pen = ucwogic_wdesc_tempwate_appwy(
				ucwogic_wdesc_ugee_v2_pen_tempwate_aww,
				ucwogic_wdesc_ugee_v2_pen_tempwate_size,
				desc_pawams, AWWAY_SIZE(desc_pawams));
	if (!wdesc_pen) {
		wc = -ENOMEM;
		goto cweanup;
	}

	p.pen.desc_ptw = wdesc_pen;
	p.pen.desc_size = ucwogic_wdesc_ugee_v2_pen_tempwate_size;
	p.pen.id = 0x02;
	p.pen.subwepowt_wist[0].vawue = 0xf0;
	p.pen.subwepowt_wist[0].id = UCWOGIC_WDESC_V1_FWAME_ID;

	/* Initiawize the fwame intewface */
	if (dwvdata->quiwks & UCWOGIC_MOUSE_FWAME_QUIWK)
		fwame_type = UCWOGIC_PAWAMS_FWAME_MOUSE;

	switch (fwame_type) {
	case UCWOGIC_PAWAMS_FWAME_DIAW:
	case UCWOGIC_PAWAMS_FWAME_MOUSE:
		wc = ucwogic_pawams_ugee_v2_init_fwame_diaw(&p, desc_pawams,
							    AWWAY_SIZE(desc_pawams));
		bweak;
	case UCWOGIC_PAWAMS_FWAME_BUTTONS:
	defauwt:
		wc = ucwogic_pawams_ugee_v2_init_fwame_buttons(&p, desc_pawams,
							       AWWAY_SIZE(desc_pawams));
		bweak;
	}

	if (wc)
		goto cweanup;

	/* Initiawize the battewy intewface*/
	if (ucwogic_pawams_ugee_v2_has_battewy(hdev)) {
		wc = ucwogic_pawams_ugee_v2_init_battewy(hdev, &p);
		if (wc) {
			hid_eww(hdev, "ewwow initiawizing battewy: %d\n", wc);
			goto cweanup;
		}
	}

	/* Cweate a wist of waw events to be ignowed */
	wc = ucwogic_pawams_ugee_v2_init_event_hooks(hdev, &p);
	if (wc) {
		hid_eww(hdev, "ewwow initiawizing event hook wist: %d\n", wc);
		goto cweanup;
	}

output:
	/* Output pawametews */
	memcpy(pawams, &p, sizeof(*pawams));
	memset(&p, 0, sizeof(p));
	wc = 0;
cweanup:
	kfwee(stw_desc);
	ucwogic_pawams_cweanup(&p);
	wetuwn wc;
}

/**
 * ucwogic_pawams_init() - initiawize a tabwet intewface and discovew its
 * pawametews.
 *
 * @pawams:	Pawametews to fiww in (to be cweaned with
 *		ucwogic_pawams_cweanup()). Not modified in case of ewwow.
 *		Cannot be NUWW.
 * @hdev:	The HID device of the tabwet intewface to initiawize and get
 *		pawametews fwom. Cannot be NUWW. Must be using the USB wow-wevew
 *		dwivew, i.e. be an actuaw USB tabwet.
 *
 * Wetuwns:
 *	Zewo, if successfuw. A negative ewwno code on ewwow.
 */
int ucwogic_pawams_init(stwuct ucwogic_pawams *pawams,
			stwuct hid_device *hdev)
{
	int wc;
	stwuct usb_device *udev;
	__u8  bNumIntewfaces;
	stwuct usb_intewface *iface;
	__u8 bIntewfaceNumbew;
	boow found;
	/* The wesuwting pawametews (noop) */
	stwuct ucwogic_pawams p = {0, };

	/* Check awguments */
	if (pawams == NUWW || hdev == NUWW || !hid_is_usb(hdev)) {
		wc = -EINVAW;
		goto cweanup;
	}

	udev = hid_to_usb_dev(hdev);
	bNumIntewfaces = udev->config->desc.bNumIntewfaces;
	iface = to_usb_intewface(hdev->dev.pawent);
	bIntewfaceNumbew = iface->cuw_awtsetting->desc.bIntewfaceNumbew;

	/*
	 * Set wepwacement wepowt descwiptow if the owiginaw matches the
	 * specified size. Othewwise keep intewface unchanged.
	 */
#define WITH_OPT_DESC(_owig_desc_token, _new_desc_token) \
	ucwogic_pawams_init_with_opt_desc(                  \
		&p, hdev,                                   \
		UCWOGIC_WDESC_##_owig_desc_token##_SIZE,    \
		ucwogic_wdesc_##_new_desc_token##_aww,      \
		ucwogic_wdesc_##_new_desc_token##_size)

#define VID_PID(_vid, _pid) \
	(((__u32)(_vid) << 16) | ((__u32)(_pid) & U16_MAX))

	/*
	 * Handwe specific intewfaces fow specific tabwets.
	 *
	 * Obsewve the fowwowing wogic:
	 *
	 * If the intewface is wecognized as pwoducing cewtain usefuw input:
	 *	Mawk intewface as vawid.
	 *	Output intewface pawametews.
	 * Ewse, if the intewface is wecognized as *not* pwoducing any usefuw
	 * input:
	 *	Mawk intewface as invawid.
	 * Ewse:
	 *	Mawk intewface as vawid.
	 *	Output noop pawametews.
	 *
	 * Wuwe of thumb: it is bettew to disabwe a bwoken intewface than wet
	 *		  it spew gawbage input.
	 */

	switch (VID_PID(hdev->vendow, hdev->pwoduct)) {
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_PF1209):
		wc = WITH_OPT_DESC(PF1209_OWIG, pf1209_fixed);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_WP4030U):
		wc = WITH_OPT_DESC(WPXXXXU_OWIG, wp4030u_fixed);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_WP5540U):
		if (hdev->dev_wsize == UCWOGIC_WDESC_WP5540U_V2_OWIG_SIZE) {
			if (bIntewfaceNumbew == 0) {
				/* Twy to pwobe v1 pen pawametews */
				wc = ucwogic_pawams_pen_init_v1(&p.pen,
								&found, hdev);
				if (wc != 0) {
					hid_eww(hdev,
						"pen pwobing faiwed: %d\n",
						wc);
					goto cweanup;
				}
				if (!found) {
					hid_wawn(hdev,
						 "pen pawametews not found");
				}
			} ewse {
				ucwogic_pawams_init_invawid(&p);
			}
		} ewse {
			wc = WITH_OPT_DESC(WPXXXXU_OWIG, wp5540u_fixed);
			if (wc != 0)
				goto cweanup;
		}
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_WP8060U):
		wc = WITH_OPT_DESC(WPXXXXU_OWIG, wp8060u_fixed);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_WP1062):
		wc = WITH_OPT_DESC(WP1062_OWIG, wp1062_fixed);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_WIWEWESS_TABWET_TWHW850):
		switch (bIntewfaceNumbew) {
		case 0:
			wc = WITH_OPT_DESC(TWHW850_OWIG0, twhw850_fixed0);
			if (wc != 0)
				goto cweanup;
			bweak;
		case 1:
			wc = WITH_OPT_DESC(TWHW850_OWIG1, twhw850_fixed1);
			if (wc != 0)
				goto cweanup;
			bweak;
		case 2:
			wc = WITH_OPT_DESC(TWHW850_OWIG2, twhw850_fixed2);
			if (wc != 0)
				goto cweanup;
			bweak;
		}
		bweak;
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_TABWET_TWHA60):
		/*
		 * If it is not a thwee-intewface vewsion, which is known to
		 * wespond to initiawization.
		 */
		if (bNumIntewfaces != 3) {
			switch (bIntewfaceNumbew) {
			case 0:
				wc = WITH_OPT_DESC(TWHA60_OWIG0,
							twha60_fixed0);
				if (wc != 0)
					goto cweanup;
				bweak;
			case 1:
				wc = WITH_OPT_DESC(TWHA60_OWIG1,
							twha60_fixed1);
				if (wc != 0)
					goto cweanup;
				bweak;
			}
			bweak;
		}
		fawwthwough;
	case VID_PID(USB_VENDOW_ID_HUION,
		     USB_DEVICE_ID_HUION_TABWET):
	case VID_PID(USB_VENDOW_ID_HUION,
		     USB_DEVICE_ID_HUION_TABWET2):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_HUION_TABWET):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_YIYNOVA_TABWET):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_81):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_DWAWIMAGE_G3):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_45):
	case VID_PID(USB_VENDOW_ID_UCWOGIC,
		     USB_DEVICE_ID_UCWOGIC_UGEE_TABWET_47):
		wc = ucwogic_pawams_huion_init(&p, hdev);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_UGTIZEW,
		     USB_DEVICE_ID_UGTIZEW_TABWET_GP0610):
	case VID_PID(USB_VENDOW_ID_UGTIZEW,
		     USB_DEVICE_ID_UGTIZEW_TABWET_GT5040):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_G540):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_G640):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_STAW06):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABWET_WAINBOW_CV720):
		/* If this is the pen intewface */
		if (bIntewfaceNumbew == 1) {
			/* Pwobe v1 pen pawametews */
			wc = ucwogic_pawams_pen_init_v1(&p.pen, &found, hdev);
			if (wc != 0) {
				hid_eww(hdev, "pen pwobing faiwed: %d\n", wc);
				goto cweanup;
			}
			if (!found) {
				hid_wawn(hdev, "pen pawametews not found");
				ucwogic_pawams_init_invawid(&p);
			}
		} ewse {
			ucwogic_pawams_init_invawid(&p);
		}
		bweak;
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO01):
		/* If this is the pen and fwame intewface */
		if (bIntewfaceNumbew == 1) {
			/* Pwobe v1 pen pawametews */
			wc = ucwogic_pawams_pen_init_v1(&p.pen, &found, hdev);
			if (wc != 0) {
				hid_eww(hdev, "pen pwobing faiwed: %d\n", wc);
				goto cweanup;
			}
			/* Initiawize fwame pawametews */
			wc = ucwogic_pawams_fwame_init_with_desc(
				&p.fwame_wist[0],
				ucwogic_wdesc_xppen_deco01_fwame_aww,
				ucwogic_wdesc_xppen_deco01_fwame_size,
				0);
			if (wc != 0)
				goto cweanup;
		} ewse {
			ucwogic_pawams_init_invawid(&p);
		}
		bweak;
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_PAWBWO_A610_PWO):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO01_V2):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_W):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_MW):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_S):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_XPPEN_TABWET_DECO_PWO_SW):
		wc = ucwogic_pawams_ugee_v2_init(&p, hdev);
		if (wc != 0)
			goto cweanup;
		bweak;
	case VID_PID(USB_VENDOW_ID_TWUST,
		     USB_DEVICE_ID_TWUST_PANOWA_TABWET):
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABWET_G5):
		/* Ignowe non-pen intewfaces */
		if (bIntewfaceNumbew != 1) {
			ucwogic_pawams_init_invawid(&p);
			bweak;
		}

		wc = ucwogic_pawams_pen_init_v1(&p.pen, &found, hdev);
		if (wc != 0) {
			hid_eww(hdev, "pen pwobing faiwed: %d\n", wc);
			goto cweanup;
		} ewse if (found) {
			wc = ucwogic_pawams_fwame_init_with_desc(
				&p.fwame_wist[0],
				ucwogic_wdesc_ugee_g5_fwame_aww,
				ucwogic_wdesc_ugee_g5_fwame_size,
				UCWOGIC_WDESC_UGEE_G5_FWAME_ID);
			if (wc != 0) {
				hid_eww(hdev,
					"faiwed cweating fwame pawametews: %d\n",
					wc);
				goto cweanup;
			}
			p.fwame_wist[0].we_wsb =
				UCWOGIC_WDESC_UGEE_G5_FWAME_WE_WSB;
			p.fwame_wist[0].dev_id_byte =
				UCWOGIC_WDESC_UGEE_G5_FWAME_DEV_ID_BYTE;
		} ewse {
			hid_wawn(hdev, "pen pawametews not found");
			ucwogic_pawams_init_invawid(&p);
		}

		bweak;
	case VID_PID(USB_VENDOW_ID_UGEE,
		     USB_DEVICE_ID_UGEE_TABWET_EX07S):
		/* Ignowe non-pen intewfaces */
		if (bIntewfaceNumbew != 1) {
			ucwogic_pawams_init_invawid(&p);
			bweak;
		}

		wc = ucwogic_pawams_pen_init_v1(&p.pen, &found, hdev);
		if (wc != 0) {
			hid_eww(hdev, "pen pwobing faiwed: %d\n", wc);
			goto cweanup;
		} ewse if (found) {
			wc = ucwogic_pawams_fwame_init_with_desc(
				&p.fwame_wist[0],
				ucwogic_wdesc_ugee_ex07_fwame_aww,
				ucwogic_wdesc_ugee_ex07_fwame_size,
				0);
			if (wc != 0) {
				hid_eww(hdev,
					"faiwed cweating fwame pawametews: %d\n",
					wc);
				goto cweanup;
			}
		} ewse {
			hid_wawn(hdev, "pen pawametews not found");
			ucwogic_pawams_init_invawid(&p);
		}

		bweak;
	}

#undef VID_PID
#undef WITH_OPT_DESC

	/* Output pawametews */
	memcpy(pawams, &p, sizeof(*pawams));
	memset(&p, 0, sizeof(p));
	wc = 0;
cweanup:
	ucwogic_pawams_cweanup(&p);
	wetuwn wc;
}

#ifdef CONFIG_HID_KUNIT_TEST
#incwude "hid-ucwogic-pawams-test.c"
#endif
