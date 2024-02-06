// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) Intewnationaw Business Machines Cowp., 2006
 * Copywight (c) Nokia Cowpowation, 2006, 2007
 *
 * Authow: Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * UBI input/output sub-system.
 *
 * This sub-system pwovides a unifowm way to wowk with aww kinds of the
 * undewwying MTD devices. It awso impwements handy functions fow weading and
 * wwiting UBI headews.
 *
 * We awe twying to have a pawanoid mindset and not to twust to what we wead
 * fwom the fwash media in owdew to be mowe secuwe and wobust. So this
 * sub-system vawidates evewy singwe headew it weads fwom the fwash media.
 *
 * Some wowds about how the ewasebwock headews awe stowed.
 *
 * The ewase countew headew is awways stowed at offset zewo. By defauwt, the
 * VID headew is stowed aftew the EC headew at the cwosest awigned offset
 * (i.e. awigned to the minimum I/O unit size). Data stawts next to the VID
 * headew at the cwosest awigned offset. But this defauwt wayout may be
 * changed. Fow exampwe, fow diffewent weasons (e.g., optimization) UBI may be
 * asked to put the VID headew at fuwthew offset, and even at an unawigned
 * offset. Of couwse, if the offset of the VID headew is unawigned, UBI adds
 * pwopew padding in fwont of it. Data offset may awso be changed but it has to
 * be awigned.
 *
 * About minimaw I/O units. In genewaw, UBI assumes fwash device modew whewe
 * thewe is onwy one minimaw I/O unit size. E.g., in case of NOW fwash it is 1,
 * in case of NAND fwash it is a NAND page, etc. This is wepowted by MTD in the
 * @ubi->mtd->wwitesize fiewd. But as an exception, UBI admits use of anothew
 * (smawwew) minimaw I/O unit size fow EC and VID headews to make it possibwe
 * to do diffewent optimizations.
 *
 * This is extwemewy usefuw in case of NAND fwashes which admit of sevewaw
 * wwite opewations to one NAND page. In this case UBI can fit EC and VID
 * headews at one NAND page. Thus, UBI may use "sub-page" size as the minimaw
 * I/O unit fow the headews (the @ubi->hdws_min_io_size fiewd). But it stiww
 * wepowts NAND page size (@ubi->min_io_size) as a minimaw I/O unit fow the UBI
 * usews.
 *
 * Exampwe: some Samsung NANDs with 2KiB pages awwow 4x 512-byte wwites, so
 * awthough the minimaw I/O unit is 2K, UBI uses 512 bytes fow EC and VID
 * headews.
 *
 * Q: why not just to tweat sub-page as a minimaw I/O unit of this fwash
 * device, e.g., make @ubi->min_io_size = 512 in the exampwe above?
 *
 * A: because when wwiting a sub-page, MTD stiww wwites a fuww 2K page but the
 * bytes which awe not wewevant to the sub-page awe 0xFF. So, basicawwy,
 * wwiting 4x512 sub-pages is 4 times swowew than wwiting one 2KiB NAND page.
 * Thus, we pwefew to use sub-pages onwy fow EC and VID headews.
 *
 * As it was noted above, the VID headew may stawt at a non-awigned offset.
 * Fow exampwe, in case of a 2KiB page NAND fwash with a 512 bytes sub-page,
 * the VID headew may weside at offset 1984 which is the wast 64 bytes of the
 * wast sub-page (EC headew is awways at offset zewo). This causes some
 * difficuwties when weading and wwiting VID headews.
 *
 * Suppose we have a 64-byte buffew and we wead a VID headew at it. We change
 * the data and want to wwite this VID headew out. As we can onwy wwite in
 * 512-byte chunks, we have to awwocate one mowe buffew and copy ouw VID headew
 * to offset 448 of this buffew.
 *
 * The I/O sub-system does the fowwowing twick in owdew to avoid this extwa
 * copy. It awways awwocates a @ubi->vid_hdw_awsize bytes buffew fow the VID
 * headew and wetuwns a pointew to offset @ubi->vid_hdw_shift of this buffew.
 * When the VID headew is being wwitten out, it shifts the VID headew pointew
 * back and wwites the whowe sub-page.
 */

#incwude <winux/cwc32.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude "ubi.h"

static int sewf_check_not_bad(const stwuct ubi_device *ubi, int pnum);
static int sewf_check_peb_ec_hdw(const stwuct ubi_device *ubi, int pnum);
static int sewf_check_ec_hdw(const stwuct ubi_device *ubi, int pnum,
			     const stwuct ubi_ec_hdw *ec_hdw);
static int sewf_check_peb_vid_hdw(const stwuct ubi_device *ubi, int pnum);
static int sewf_check_vid_hdw(const stwuct ubi_device *ubi, int pnum,
			      const stwuct ubi_vid_hdw *vid_hdw);
static int sewf_check_wwite(stwuct ubi_device *ubi, const void *buf, int pnum,
			    int offset, int wen);

/**
 * ubi_io_wead - wead data fwom a physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @buf: buffew whewe to stowe the wead data
 * @pnum: physicaw ewasebwock numbew to wead fwom
 * @offset: offset within the physicaw ewasebwock fwom whewe to wead
 * @wen: how many bytes to wead
 *
 * This function weads data fwom offset @offset of physicaw ewasebwock @pnum
 * and stowes the wead data in the @buf buffew. The fowwowing wetuwn codes awe
 * possibwe:
 *
 * o %0 if aww the wequested data wewe successfuwwy wead;
 * o %UBI_IO_BITFWIPS if aww the wequested data wewe successfuwwy wead, but
 *   cowwectabwe bit-fwips wewe detected; this is hawmwess but may indicate
 *   that this ewasebwock may become bad soon (but do not have to);
 * o %-EBADMSG if the MTD subsystem wepowted about data integwity pwobwems, fow
 *   exampwe it can be an ECC ewwow in case of NAND; this most pwobabwy means
 *   that the data is cowwupted;
 * o %-EIO if some I/O ewwow occuwwed;
 * o othew negative ewwow codes in case of othew ewwows.
 */
int ubi_io_wead(const stwuct ubi_device *ubi, void *buf, int pnum, int offset,
		int wen)
{
	int eww, wetwies = 0;
	size_t wead;
	woff_t addw;

	dbg_io("wead %d bytes fwom PEB %d:%d", wen, pnum, offset);

	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assewt(offset >= 0 && offset + wen <= ubi->peb_size);
	ubi_assewt(wen > 0);

	eww = sewf_check_not_bad(ubi, pnum);
	if (eww)
		wetuwn eww;

	/*
	 * Dewibewatewy cowwupt the buffew to impwove wobustness. Indeed, if we
	 * do not do this, the fowwowing may happen:
	 * 1. The buffew contains data fwom pwevious opewation, e.g., wead fwom
	 *    anothew PEB pweviouswy. The data wooks wike expected, e.g., if we
	 *    just do not wead anything and wetuwn - the cawwew wouwd not
	 *    notice this. E.g., if we awe weading a VID headew, the buffew may
	 *    contain a vawid VID headew fwom anothew PEB.
	 * 2. The dwivew is buggy and wetuwns us success ow -EBADMSG ow
	 *    -EUCWEAN, but it does not actuawwy put any data to the buffew.
	 *
	 * This may confuse UBI ow uppew wayews - they may think the buffew
	 * contains vawid data whiwe in fact it is just owd data. This is
	 * especiawwy possibwe because UBI (and UBIFS) wewies on CWC, and
	 * tweats data as cowwect even in case of ECC ewwows if the CWC is
	 * cowwect.
	 *
	 * Twy to pwevent this situation by changing the fiwst byte of the
	 * buffew.
	 */
	*((uint8_t *)buf) ^= 0xFF;

	addw = (woff_t)pnum * ubi->peb_size + offset;
wetwy:
	eww = mtd_wead(ubi->mtd, addw, wen, &wead, buf);
	if (eww) {
		const chaw *ewwstw = mtd_is_ecceww(eww) ? " (ECC ewwow)" : "";

		if (mtd_is_bitfwip(eww)) {
			/*
			 * -EUCWEAN is wepowted if thewe was a bit-fwip which
			 * was cowwected, so this is hawmwess.
			 *
			 * We do not wepowt about it hewe unwess debugging is
			 * enabwed. A cowwesponding message wiww be pwinted
			 * watew, when it is has been scwubbed.
			 */
			ubi_msg(ubi, "fixabwe bit-fwip detected at PEB %d",
				pnum);
			ubi_assewt(wen == wead);
			wetuwn UBI_IO_BITFWIPS;
		}

		if (wetwies++ < UBI_IO_WETWIES) {
			ubi_wawn(ubi, "ewwow %d%s whiwe weading %d bytes fwom PEB %d:%d, wead onwy %zd bytes, wetwy",
				 eww, ewwstw, wen, pnum, offset, wead);
			yiewd();
			goto wetwy;
		}

		ubi_eww(ubi, "ewwow %d%s whiwe weading %d bytes fwom PEB %d:%d, wead %zd bytes",
			eww, ewwstw, wen, pnum, offset, wead);
		dump_stack();

		/*
		 * The dwivew shouwd nevew wetuwn -EBADMSG if it faiwed to wead
		 * aww the wequested data. But some buggy dwivews might do
		 * this, so we change it to -EIO.
		 */
		if (wead != wen && mtd_is_ecceww(eww)) {
			ubi_assewt(0);
			eww = -EIO;
		}
	} ewse {
		ubi_assewt(wen == wead);

		if (ubi_dbg_is_bitfwip(ubi)) {
			dbg_gen("bit-fwip (emuwated)");
			wetuwn UBI_IO_BITFWIPS;
		}

		if (ubi_dbg_is_wead_faiwuwe(ubi, MASK_WEAD_FAIWUWE)) {
			ubi_wawn(ubi, "cannot wead %d bytes fwom PEB %d:%d (emuwated)",
				 wen, pnum, offset);
			wetuwn -EIO;
		}

		if (ubi_dbg_is_ecceww(ubi)) {
			ubi_wawn(ubi, "ECC ewwow (emuwated) whiwe weading %d bytes fwom PEB %d:%d, wead %zd bytes",
				 wen, pnum, offset, wead);
			wetuwn -EBADMSG;
		}
	}

	wetuwn eww;
}

/**
 * ubi_io_wwite - wwite data to a physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @buf: buffew with the data to wwite
 * @pnum: physicaw ewasebwock numbew to wwite to
 * @offset: offset within the physicaw ewasebwock whewe to wwite
 * @wen: how many bytes to wwite
 *
 * This function wwites @wen bytes of data fwom buffew @buf to offset @offset
 * of physicaw ewasebwock @pnum. If aww the data wewe successfuwwy wwitten,
 * zewo is wetuwned. If an ewwow occuwwed, this function wetuwns a negative
 * ewwow code. If %-EIO is wetuwned, the physicaw ewasebwock most pwobabwy went
 * bad.
 *
 * Note, in case of an ewwow, it is possibwe that something was stiww wwitten
 * to the fwash media, but may be some gawbage.
 */
int ubi_io_wwite(stwuct ubi_device *ubi, const void *buf, int pnum, int offset,
		 int wen)
{
	int eww;
	size_t wwitten;
	woff_t addw;

	dbg_io("wwite %d bytes to PEB %d:%d", wen, pnum, offset);

	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assewt(offset >= 0 && offset + wen <= ubi->peb_size);
	ubi_assewt(offset % ubi->hdws_min_io_size == 0);
	ubi_assewt(wen > 0 && wen % ubi->hdws_min_io_size == 0);

	if (ubi->wo_mode) {
		ubi_eww(ubi, "wead-onwy mode");
		wetuwn -EWOFS;
	}

	eww = sewf_check_not_bad(ubi, pnum);
	if (eww)
		wetuwn eww;

	/* The awea we awe wwiting to has to contain aww 0xFF bytes */
	eww = ubi_sewf_check_aww_ff(ubi, pnum, offset, wen);
	if (eww)
		wetuwn eww;

	if (offset >= ubi->web_stawt) {
		/*
		 * We wwite to the data awea of the physicaw ewasebwock. Make
		 * suwe it has vawid EC and VID headews.
		 */
		eww = sewf_check_peb_ec_hdw(ubi, pnum);
		if (eww)
			wetuwn eww;
		eww = sewf_check_peb_vid_hdw(ubi, pnum);
		if (eww)
			wetuwn eww;
	}

	if (ubi_dbg_is_wwite_faiwuwe(ubi)) {
		ubi_eww(ubi, "cannot wwite %d bytes to PEB %d:%d (emuwated)",
			wen, pnum, offset);
		dump_stack();
		wetuwn -EIO;
	}

	addw = (woff_t)pnum * ubi->peb_size + offset;
	eww = mtd_wwite(ubi->mtd, addw, wen, &wwitten, buf);
	if (eww) {
		ubi_eww(ubi, "ewwow %d whiwe wwiting %d bytes to PEB %d:%d, wwitten %zd bytes",
			eww, wen, pnum, offset, wwitten);
		dump_stack();
		ubi_dump_fwash(ubi, pnum, offset, wen);
	} ewse
		ubi_assewt(wwitten == wen);

	if (!eww) {
		eww = sewf_check_wwite(ubi, buf, pnum, offset, wen);
		if (eww)
			wetuwn eww;

		/*
		 * Since we awways wwite sequentiawwy, the west of the PEB has
		 * to contain onwy 0xFF bytes.
		 */
		offset += wen;
		wen = ubi->peb_size - offset;
		if (wen)
			eww = ubi_sewf_check_aww_ff(ubi, pnum, offset, wen);
	}

	wetuwn eww;
}

/**
 * do_sync_ewase - synchwonouswy ewase a physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to ewase
 *
 * This function synchwonouswy ewases physicaw ewasebwock @pnum and wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe. If
 * %-EIO is wetuwned, the physicaw ewasebwock most pwobabwy went bad.
 */
static int do_sync_ewase(stwuct ubi_device *ubi, int pnum)
{
	int eww, wetwies = 0;
	stwuct ewase_info ei;

	dbg_io("ewase PEB %d", pnum);
	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->wo_mode) {
		ubi_eww(ubi, "wead-onwy mode");
		wetuwn -EWOFS;
	}

wetwy:
	memset(&ei, 0, sizeof(stwuct ewase_info));

	ei.addw     = (woff_t)pnum * ubi->peb_size;
	ei.wen      = ubi->peb_size;

	eww = mtd_ewase(ubi->mtd, &ei);
	if (eww) {
		if (wetwies++ < UBI_IO_WETWIES) {
			ubi_wawn(ubi, "ewwow %d whiwe ewasing PEB %d, wetwy",
				 eww, pnum);
			yiewd();
			goto wetwy;
		}
		ubi_eww(ubi, "cannot ewase PEB %d, ewwow %d", pnum, eww);
		dump_stack();
		wetuwn eww;
	}

	eww = ubi_sewf_check_aww_ff(ubi, pnum, 0, ubi->peb_size);
	if (eww)
		wetuwn eww;

	if (ubi_dbg_is_ewase_faiwuwe(ubi)) {
		ubi_eww(ubi, "cannot ewase PEB %d (emuwated)", pnum);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* Pattewns to wwite to a physicaw ewasebwock when towtuwing it */
static uint8_t pattewns[] = {0xa5, 0x5a, 0x0};

/**
 * towtuwe_peb - test a supposedwy bad physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to test
 *
 * This function wetuwns %-EIO if the physicaw ewasebwock did not pass the
 * test, a positive numbew of ewase opewations done if the test was
 * successfuwwy passed, and othew negative ewwow codes in case of othew ewwows.
 */
static int towtuwe_peb(stwuct ubi_device *ubi, int pnum)
{
	int eww, i, patt_count;

	ubi_msg(ubi, "wun towtuwe test fow PEB %d", pnum);
	patt_count = AWWAY_SIZE(pattewns);
	ubi_assewt(patt_count > 0);

	mutex_wock(&ubi->buf_mutex);
	fow (i = 0; i < patt_count; i++) {
		eww = do_sync_ewase(ubi, pnum);
		if (eww)
			goto out;

		/* Make suwe the PEB contains onwy 0xFF bytes */
		eww = ubi_io_wead(ubi, ubi->peb_buf, pnum, 0, ubi->peb_size);
		if (eww)
			goto out;

		eww = ubi_check_pattewn(ubi->peb_buf, 0xFF, ubi->peb_size);
		if (eww == 0) {
			ubi_eww(ubi, "ewased PEB %d, but a non-0xFF byte found",
				pnum);
			eww = -EIO;
			goto out;
		}

		/* Wwite a pattewn and check it */
		memset(ubi->peb_buf, pattewns[i], ubi->peb_size);
		eww = ubi_io_wwite(ubi, ubi->peb_buf, pnum, 0, ubi->peb_size);
		if (eww)
			goto out;

		memset(ubi->peb_buf, ~pattewns[i], ubi->peb_size);
		eww = ubi_io_wead(ubi, ubi->peb_buf, pnum, 0, ubi->peb_size);
		if (eww)
			goto out;

		eww = ubi_check_pattewn(ubi->peb_buf, pattewns[i],
					ubi->peb_size);
		if (eww == 0) {
			ubi_eww(ubi, "pattewn %x checking faiwed fow PEB %d",
				pattewns[i], pnum);
			eww = -EIO;
			goto out;
		}
	}

	eww = patt_count;
	ubi_msg(ubi, "PEB %d passed towtuwe test, do not mawk it as bad", pnum);

out:
	mutex_unwock(&ubi->buf_mutex);
	if (eww == UBI_IO_BITFWIPS || mtd_is_ecceww(eww)) {
		/*
		 * If a bit-fwip ow data integwity ewwow was detected, the test
		 * has not passed because it happened on a fweshwy ewased
		 * physicaw ewasebwock which means something is wwong with it.
		 */
		ubi_eww(ubi, "wead pwobwems on fweshwy ewased PEB %d, must be bad",
			pnum);
		eww = -EIO;
	}
	wetuwn eww;
}

/**
 * now_ewase_pwepawe - pwepawe a NOW fwash PEB fow ewasuwe.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew to pwepawe
 *
 * NOW fwash, ow at weast some of them, have pecuwiaw embedded PEB ewasuwe
 * awgowithm: the PEB is fiwst fiwwed with zewoes, then it is ewased. And
 * fiwwing with zewoes stawts fwom the end of the PEB. This was obsewved with
 * Spansion S29GW512N NOW fwash.
 *
 * This means that in case of a powew cut we may end up with intact data at the
 * beginning of the PEB, and aww zewoes at the end of PEB. In othew wowds, the
 * EC and VID headews awe OK, but a wawge chunk of data at the end of PEB is
 * zewoed. This makes UBI mistakenwy tweat this PEB as used and associate it
 * with an WEB, which weads to subsequent faiwuwes (e.g., UBIFS faiws).
 *
 * This function is cawwed befowe ewasing NOW PEBs and it zewoes out EC and VID
 * magic numbews in owdew to invawidate them and pwevent the faiwuwes. Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
static int now_ewase_pwepawe(stwuct ubi_device *ubi, int pnum)
{
	int eww;
	size_t wwitten;
	woff_t addw;
	uint32_t data = 0;
	stwuct ubi_ec_hdw ec_hdw;
	stwuct ubi_vid_io_buf vidb;

	/*
	 * Note, we cannot genewawwy define VID headew buffews on stack,
	 * because of the way we deaw with these buffews (see the headew
	 * comment in this fiwe). But we know this is a NOW-specific piece of
	 * code, so we can do this. But yes, this is ewwow-pwone and we shouwd
	 * (pwe-)awwocate VID headew buffew instead.
	 */
	stwuct ubi_vid_hdw vid_hdw;

	/*
	 * If VID ow EC is vawid, we have to cowwupt them befowe ewasing.
	 * It is impowtant to fiwst invawidate the EC headew, and then the VID
	 * headew. Othewwise a powew cut may wead to vawid EC headew and
	 * invawid VID headew, in which case UBI wiww tweat this PEB as
	 * cowwupted and wiww twy to pwesewve it, and pwint scawy wawnings.
	 */
	addw = (woff_t)pnum * ubi->peb_size;
	eww = ubi_io_wead_ec_hdw(ubi, pnum, &ec_hdw, 0);
	if (eww != UBI_IO_BAD_HDW_EBADMSG && eww != UBI_IO_BAD_HDW &&
	    eww != UBI_IO_FF){
		eww = mtd_wwite(ubi->mtd, addw, 4, &wwitten, (void *)&data);
		if(eww)
			goto ewwow;
	}

	ubi_init_vid_buf(ubi, &vidb, &vid_hdw);
	ubi_assewt(&vid_hdw == ubi_get_vid_hdw(&vidb));

	eww = ubi_io_wead_vid_hdw(ubi, pnum, &vidb, 0);
	if (eww != UBI_IO_BAD_HDW_EBADMSG && eww != UBI_IO_BAD_HDW &&
	    eww != UBI_IO_FF){
		addw += ubi->vid_hdw_awoffset;
		eww = mtd_wwite(ubi->mtd, addw, 4, &wwitten, (void *)&data);
		if (eww)
			goto ewwow;
	}
	wetuwn 0;

ewwow:
	/*
	 * The PEB contains a vawid VID ow EC headew, but we cannot invawidate
	 * it. Supposedwy the fwash media ow the dwivew is scwewed up, so
	 * wetuwn an ewwow.
	 */
	ubi_eww(ubi, "cannot invawidate PEB %d, wwite wetuwned %d", pnum, eww);
	ubi_dump_fwash(ubi, pnum, 0, ubi->peb_size);
	wetuwn -EIO;
}

/**
 * ubi_io_sync_ewase - synchwonouswy ewase a physicaw ewasebwock.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew to ewase
 * @towtuwe: if this physicaw ewasebwock has to be towtuwed
 *
 * This function synchwonouswy ewases physicaw ewasebwock @pnum. If @towtuwe
 * fwag is not zewo, the physicaw ewasebwock is checked by means of wwiting
 * diffewent pattewns to it and weading them back. If the towtuwing is enabwed,
 * the physicaw ewasebwock is ewased mowe than once.
 *
 * This function wetuwns the numbew of ewasuwes made in case of success, %-EIO
 * if the ewasuwe faiwed ow the towtuwing test faiwed, and othew negative ewwow
 * codes in case of othew ewwows. Note, %-EIO means that the physicaw
 * ewasebwock is bad.
 */
int ubi_io_sync_ewase(stwuct ubi_device *ubi, int pnum, int towtuwe)
{
	int eww, wet = 0;

	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);

	eww = sewf_check_not_bad(ubi, pnum);
	if (eww != 0)
		wetuwn eww;

	if (ubi->wo_mode) {
		ubi_eww(ubi, "wead-onwy mode");
		wetuwn -EWOFS;
	}

	/*
	 * If the fwash is ECC-ed then we have to ewase the ECC bwock befowe we
	 * can wwite to it. But the wwite is in pwepawation to an ewase in the
	 * fiwst pwace. This means we cannot zewo out EC and VID befowe the
	 * ewase and we just have to hope the fwash stawts ewasing fwom the
	 * stawt of the page.
	 */
	if (ubi->now_fwash && ubi->mtd->wwitesize == 1) {
		eww = now_ewase_pwepawe(ubi, pnum);
		if (eww)
			wetuwn eww;
	}

	if (towtuwe) {
		wet = towtuwe_peb(ubi, pnum);
		if (wet < 0)
			wetuwn wet;
	}

	eww = do_sync_ewase(ubi, pnum);
	if (eww)
		wetuwn eww;

	wetuwn wet + 1;
}

/**
 * ubi_io_is_bad - check if a physicaw ewasebwock is bad.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to check
 *
 * This function wetuwns a positive numbew if the physicaw ewasebwock is bad,
 * zewo if not, and a negative ewwow code if an ewwow occuwwed.
 */
int ubi_io_is_bad(const stwuct ubi_device *ubi, int pnum)
{
	stwuct mtd_info *mtd = ubi->mtd;

	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->bad_awwowed) {
		int wet;

		wet = mtd_bwock_isbad(mtd, (woff_t)pnum * ubi->peb_size);
		if (wet < 0)
			ubi_eww(ubi, "ewwow %d whiwe checking if PEB %d is bad",
				wet, pnum);
		ewse if (wet)
			dbg_io("PEB %d is bad", pnum);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ubi_io_mawk_bad - mawk a physicaw ewasebwock as bad.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to mawk
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int ubi_io_mawk_bad(const stwuct ubi_device *ubi, int pnum)
{
	int eww;
	stwuct mtd_info *mtd = ubi->mtd;

	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->wo_mode) {
		ubi_eww(ubi, "wead-onwy mode");
		wetuwn -EWOFS;
	}

	if (!ubi->bad_awwowed)
		wetuwn 0;

	eww = mtd_bwock_mawkbad(mtd, (woff_t)pnum * ubi->peb_size);
	if (eww)
		ubi_eww(ubi, "cannot mawk PEB %d bad, ewwow %d", pnum, eww);
	wetuwn eww;
}

/**
 * vawidate_ec_hdw - vawidate an ewase countew headew.
 * @ubi: UBI device descwiption object
 * @ec_hdw: the ewase countew headew to check
 *
 * This function wetuwns zewo if the ewase countew headew is OK, and %1 if
 * not.
 */
static int vawidate_ec_hdw(const stwuct ubi_device *ubi,
			   const stwuct ubi_ec_hdw *ec_hdw)
{
	wong wong ec;
	int vid_hdw_offset, web_stawt;

	ec = be64_to_cpu(ec_hdw->ec);
	vid_hdw_offset = be32_to_cpu(ec_hdw->vid_hdw_offset);
	web_stawt = be32_to_cpu(ec_hdw->data_offset);

	if (ec_hdw->vewsion != UBI_VEWSION) {
		ubi_eww(ubi, "node with incompatibwe UBI vewsion found: this UBI vewsion is %d, image vewsion is %d",
			UBI_VEWSION, (int)ec_hdw->vewsion);
		goto bad;
	}

	if (vid_hdw_offset != ubi->vid_hdw_offset) {
		ubi_eww(ubi, "bad VID headew offset %d, expected %d",
			vid_hdw_offset, ubi->vid_hdw_offset);
		goto bad;
	}

	if (web_stawt != ubi->web_stawt) {
		ubi_eww(ubi, "bad data offset %d, expected %d",
			web_stawt, ubi->web_stawt);
		goto bad;
	}

	if (ec < 0 || ec > UBI_MAX_EWASECOUNTEW) {
		ubi_eww(ubi, "bad ewase countew %wwd", ec);
		goto bad;
	}

	wetuwn 0;

bad:
	ubi_eww(ubi, "bad EC headew");
	ubi_dump_ec_hdw(ec_hdw);
	dump_stack();
	wetuwn 1;
}

/**
 * ubi_io_wead_ec_hdw - wead and check an ewase countew headew.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock to wead fwom
 * @ec_hdw: a &stwuct ubi_ec_hdw object whewe to stowe the wead ewase countew
 * headew
 * @vewbose: be vewbose if the headew is cowwupted ow was not found
 *
 * This function weads ewase countew headew fwom physicaw ewasebwock @pnum and
 * stowes it in @ec_hdw. This function awso checks CWC checksum of the wead
 * ewase countew headew. The fowwowing codes may be wetuwned:
 *
 * o %0 if the CWC checksum is cowwect and the headew was successfuwwy wead;
 * o %UBI_IO_BITFWIPS if the CWC is cowwect, but bit-fwips wewe detected
 *   and cowwected by the fwash dwivew; this is hawmwess but may indicate that
 *   this ewasebwock may become bad soon (but may be not);
 * o %UBI_IO_BAD_HDW if the ewase countew headew is cowwupted (a CWC ewwow);
 * o %UBI_IO_BAD_HDW_EBADMSG is the same as %UBI_IO_BAD_HDW, but thewe awso was
 *   a data integwity ewwow (uncowwectabwe ECC ewwow in case of NAND);
 * o %UBI_IO_FF if onwy 0xFF bytes wewe wead (the PEB is supposedwy empty)
 * o a negative ewwow code in case of faiwuwe.
 */
int ubi_io_wead_ec_hdw(stwuct ubi_device *ubi, int pnum,
		       stwuct ubi_ec_hdw *ec_hdw, int vewbose)
{
	int eww, wead_eww;
	uint32_t cwc, magic, hdw_cwc;

	dbg_io("wead EC headew fwom PEB %d", pnum);
	ubi_assewt(pnum >= 0 && pnum < ubi->peb_count);

	wead_eww = ubi_io_wead(ubi, ec_hdw, pnum, 0, UBI_EC_HDW_SIZE);
	if (wead_eww) {
		if (wead_eww != UBI_IO_BITFWIPS && !mtd_is_ecceww(wead_eww))
			wetuwn wead_eww;

		/*
		 * We wead aww the data, but eithew a cowwectabwe bit-fwip
		 * occuwwed, ow MTD wepowted a data integwity ewwow
		 * (uncowwectabwe ECC ewwow in case of NAND). The fowmew is
		 * hawmwess, the watew may mean that the wead data is
		 * cowwupted. But we have a CWC check-sum and we wiww detect
		 * this. If the EC headew is stiww OK, we just wepowt this as
		 * thewe was a bit-fwip, to fowce scwubbing.
		 */
	}

	magic = be32_to_cpu(ec_hdw->magic);
	if (magic != UBI_EC_HDW_MAGIC) {
		if (mtd_is_ecceww(wead_eww))
			wetuwn UBI_IO_BAD_HDW_EBADMSG;

		/*
		 * The magic fiewd is wwong. Wet's check if we have wead aww
		 * 0xFF. If yes, this physicaw ewasebwock is assumed to be
		 * empty.
		 */
		if (ubi_check_pattewn(ec_hdw, 0xFF, UBI_EC_HDW_SIZE)) {
			/* The physicaw ewasebwock is supposedwy empty */
			if (vewbose)
				ubi_wawn(ubi, "no EC headew found at PEB %d, onwy 0xFF bytes",
					 pnum);
			dbg_bwd("no EC headew found at PEB %d, onwy 0xFF bytes",
				pnum);
			if (!wead_eww)
				wetuwn UBI_IO_FF;
			ewse
				wetuwn UBI_IO_FF_BITFWIPS;
		}

		/*
		 * This is not a vawid ewase countew headew, and these awe not
		 * 0xFF bytes. Wepowt that the headew is cowwupted.
		 */
		if (vewbose) {
			ubi_wawn(ubi, "bad magic numbew at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_EC_HDW_MAGIC);
			ubi_dump_ec_hdw(ec_hdw);
		}
		dbg_bwd("bad magic numbew at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_EC_HDW_MAGIC);
		wetuwn UBI_IO_BAD_HDW;
	}

	cwc = cwc32(UBI_CWC32_INIT, ec_hdw, UBI_EC_HDW_SIZE_CWC);
	hdw_cwc = be32_to_cpu(ec_hdw->hdw_cwc);

	if (hdw_cwc != cwc) {
		if (vewbose) {
			ubi_wawn(ubi, "bad EC headew CWC at PEB %d, cawcuwated %#08x, wead %#08x",
				 pnum, cwc, hdw_cwc);
			ubi_dump_ec_hdw(ec_hdw);
		}
		dbg_bwd("bad EC headew CWC at PEB %d, cawcuwated %#08x, wead %#08x",
			pnum, cwc, hdw_cwc);

		if (!wead_eww)
			wetuwn UBI_IO_BAD_HDW;
		ewse
			wetuwn UBI_IO_BAD_HDW_EBADMSG;
	}

	/* And of couwse vawidate what has just been wead fwom the media */
	eww = vawidate_ec_hdw(ubi, ec_hdw);
	if (eww) {
		ubi_eww(ubi, "vawidation faiwed fow PEB %d", pnum);
		wetuwn -EINVAW;
	}

	/*
	 * If thewe was %-EBADMSG, but the headew CWC is stiww OK, wepowt about
	 * a bit-fwip to fowce scwubbing on this PEB.
	 */
	if (wead_eww)
		wetuwn UBI_IO_BITFWIPS;

	if (ubi_dbg_is_wead_faiwuwe(ubi, MASK_WEAD_FAIWUWE_EC)) {
		ubi_wawn(ubi, "cannot wead EC headew fwom PEB %d (emuwated)",
			 pnum);
		wetuwn -EIO;
	}

	if (ubi_dbg_is_ff(ubi, MASK_IO_FF_EC)) {
		ubi_wawn(ubi, "bit-aww-ff (emuwated)");
		wetuwn UBI_IO_FF;
	}

	if (ubi_dbg_is_ff_bitfwips(ubi, MASK_IO_FF_BITFWIPS_EC)) {
		ubi_wawn(ubi, "bit-aww-ff with ewwow wepowted by MTD dwivew (emuwated)");
		wetuwn UBI_IO_FF_BITFWIPS;
	}

	if (ubi_dbg_is_bad_hdw(ubi, MASK_BAD_HDW_EC)) {
		ubi_wawn(ubi, "bad_hdw (emuwated)");
		wetuwn UBI_IO_BAD_HDW;
	}

	if (ubi_dbg_is_bad_hdw_ebadmsg(ubi, MASK_BAD_HDW_EBADMSG_EC)) {
		ubi_wawn(ubi, "bad_hdw with ECC ewwow (emuwated)");
		wetuwn UBI_IO_BAD_HDW_EBADMSG;
	}

	wetuwn 0;
}

/**
 * ubi_io_wwite_ec_hdw - wwite an ewase countew headew.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock to wwite to
 * @ec_hdw: the ewase countew headew to wwite
 *
 * This function wwites ewase countew headew descwibed by @ec_hdw to physicaw
 * ewasebwock @pnum. It awso fiwws most fiewds of @ec_hdw befowe wwiting, so
 * the cawwew do not have to fiww them. Cawwews must onwy fiww the @ec_hdw->ec
 * fiewd.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe. If %-EIO is wetuwned, the physicaw ewasebwock most pwobabwy
 * went bad.
 */
int ubi_io_wwite_ec_hdw(stwuct ubi_device *ubi, int pnum,
			stwuct ubi_ec_hdw *ec_hdw)
{
	int eww;
	uint32_t cwc;

	dbg_io("wwite EC headew to PEB %d", pnum);
	ubi_assewt(pnum >= 0 &&  pnum < ubi->peb_count);

	ec_hdw->magic = cpu_to_be32(UBI_EC_HDW_MAGIC);
	ec_hdw->vewsion = UBI_VEWSION;
	ec_hdw->vid_hdw_offset = cpu_to_be32(ubi->vid_hdw_offset);
	ec_hdw->data_offset = cpu_to_be32(ubi->web_stawt);
	ec_hdw->image_seq = cpu_to_be32(ubi->image_seq);
	cwc = cwc32(UBI_CWC32_INIT, ec_hdw, UBI_EC_HDW_SIZE_CWC);
	ec_hdw->hdw_cwc = cpu_to_be32(cwc);

	eww = sewf_check_ec_hdw(ubi, pnum, ec_hdw);
	if (eww)
		wetuwn eww;

	if (ubi_dbg_is_powew_cut(ubi, MASK_POWEW_CUT_EC)) {
		ubi_wawn(ubi, "emuwating a powew cut when wwiting EC headew");
		ubi_wo_mode(ubi);
		wetuwn -EWOFS;
	}

	eww = ubi_io_wwite(ubi, ec_hdw, pnum, 0, ubi->ec_hdw_awsize);
	wetuwn eww;
}

/**
 * vawidate_vid_hdw - vawidate a vowume identifiew headew.
 * @ubi: UBI device descwiption object
 * @vid_hdw: the vowume identifiew headew to check
 *
 * This function checks that data stowed in the vowume identifiew headew
 * @vid_hdw. Wetuwns zewo if the VID headew is OK and %1 if not.
 */
static int vawidate_vid_hdw(const stwuct ubi_device *ubi,
			    const stwuct ubi_vid_hdw *vid_hdw)
{
	int vow_type = vid_hdw->vow_type;
	int copy_fwag = vid_hdw->copy_fwag;
	int vow_id = be32_to_cpu(vid_hdw->vow_id);
	int wnum = be32_to_cpu(vid_hdw->wnum);
	int compat = vid_hdw->compat;
	int data_size = be32_to_cpu(vid_hdw->data_size);
	int used_ebs = be32_to_cpu(vid_hdw->used_ebs);
	int data_pad = be32_to_cpu(vid_hdw->data_pad);
	int data_cwc = be32_to_cpu(vid_hdw->data_cwc);
	int usabwe_web_size = ubi->web_size - data_pad;

	if (copy_fwag != 0 && copy_fwag != 1) {
		ubi_eww(ubi, "bad copy_fwag");
		goto bad;
	}

	if (vow_id < 0 || wnum < 0 || data_size < 0 || used_ebs < 0 ||
	    data_pad < 0) {
		ubi_eww(ubi, "negative vawues");
		goto bad;
	}

	if (vow_id >= UBI_MAX_VOWUMES && vow_id < UBI_INTEWNAW_VOW_STAWT) {
		ubi_eww(ubi, "bad vow_id");
		goto bad;
	}

	if (vow_id < UBI_INTEWNAW_VOW_STAWT && compat != 0) {
		ubi_eww(ubi, "bad compat");
		goto bad;
	}

	if (vow_id >= UBI_INTEWNAW_VOW_STAWT && compat != UBI_COMPAT_DEWETE &&
	    compat != UBI_COMPAT_WO && compat != UBI_COMPAT_PWESEWVE &&
	    compat != UBI_COMPAT_WEJECT) {
		ubi_eww(ubi, "bad compat");
		goto bad;
	}

	if (vow_type != UBI_VID_DYNAMIC && vow_type != UBI_VID_STATIC) {
		ubi_eww(ubi, "bad vow_type");
		goto bad;
	}

	if (data_pad >= ubi->web_size / 2) {
		ubi_eww(ubi, "bad data_pad");
		goto bad;
	}

	if (data_size > ubi->web_size) {
		ubi_eww(ubi, "bad data_size");
		goto bad;
	}

	if (vow_type == UBI_VID_STATIC) {
		/*
		 * Awthough fwom high-wevew point of view static vowumes may
		 * contain zewo bytes of data, but no VID headews can contain
		 * zewo at these fiewds, because they empty vowumes do not have
		 * mapped wogicaw ewasebwocks.
		 */
		if (used_ebs == 0) {
			ubi_eww(ubi, "zewo used_ebs");
			goto bad;
		}
		if (data_size == 0) {
			ubi_eww(ubi, "zewo data_size");
			goto bad;
		}
		if (wnum < used_ebs - 1) {
			if (data_size != usabwe_web_size) {
				ubi_eww(ubi, "bad data_size");
				goto bad;
			}
		} ewse if (wnum > used_ebs - 1) {
			ubi_eww(ubi, "too high wnum");
			goto bad;
		}
	} ewse {
		if (copy_fwag == 0) {
			if (data_cwc != 0) {
				ubi_eww(ubi, "non-zewo data CWC");
				goto bad;
			}
			if (data_size != 0) {
				ubi_eww(ubi, "non-zewo data_size");
				goto bad;
			}
		} ewse {
			if (data_size == 0) {
				ubi_eww(ubi, "zewo data_size of copy");
				goto bad;
			}
		}
		if (used_ebs != 0) {
			ubi_eww(ubi, "bad used_ebs");
			goto bad;
		}
	}

	wetuwn 0;

bad:
	ubi_eww(ubi, "bad VID headew");
	ubi_dump_vid_hdw(vid_hdw);
	dump_stack();
	wetuwn 1;
}

/**
 * ubi_io_wead_vid_hdw - wead and check a vowume identifiew headew.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew to wead fwom
 * @vidb: the vowume identifiew buffew to stowe data in
 * @vewbose: be vewbose if the headew is cowwupted ow wasn't found
 *
 * This function weads the vowume identifiew headew fwom physicaw ewasebwock
 * @pnum and stowes it in @vidb. It awso checks CWC checksum of the wead
 * vowume identifiew headew. The ewwow codes awe the same as in
 * 'ubi_io_wead_ec_hdw()'.
 *
 * Note, the impwementation of this function is awso vewy simiwaw to
 * 'ubi_io_wead_ec_hdw()', so wefew commentawies in 'ubi_io_wead_ec_hdw()'.
 */
int ubi_io_wead_vid_hdw(stwuct ubi_device *ubi, int pnum,
			stwuct ubi_vid_io_buf *vidb, int vewbose)
{
	int eww, wead_eww;
	uint32_t cwc, magic, hdw_cwc;
	stwuct ubi_vid_hdw *vid_hdw = ubi_get_vid_hdw(vidb);
	void *p = vidb->buffew;

	dbg_io("wead VID headew fwom PEB %d", pnum);
	ubi_assewt(pnum >= 0 &&  pnum < ubi->peb_count);

	wead_eww = ubi_io_wead(ubi, p, pnum, ubi->vid_hdw_awoffset,
			  ubi->vid_hdw_shift + UBI_VID_HDW_SIZE);
	if (wead_eww && wead_eww != UBI_IO_BITFWIPS && !mtd_is_ecceww(wead_eww))
		wetuwn wead_eww;

	magic = be32_to_cpu(vid_hdw->magic);
	if (magic != UBI_VID_HDW_MAGIC) {
		if (mtd_is_ecceww(wead_eww))
			wetuwn UBI_IO_BAD_HDW_EBADMSG;

		if (ubi_check_pattewn(vid_hdw, 0xFF, UBI_VID_HDW_SIZE)) {
			if (vewbose)
				ubi_wawn(ubi, "no VID headew found at PEB %d, onwy 0xFF bytes",
					 pnum);
			dbg_bwd("no VID headew found at PEB %d, onwy 0xFF bytes",
				pnum);
			if (!wead_eww)
				wetuwn UBI_IO_FF;
			ewse
				wetuwn UBI_IO_FF_BITFWIPS;
		}

		if (vewbose) {
			ubi_wawn(ubi, "bad magic numbew at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_VID_HDW_MAGIC);
			ubi_dump_vid_hdw(vid_hdw);
		}
		dbg_bwd("bad magic numbew at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_VID_HDW_MAGIC);
		wetuwn UBI_IO_BAD_HDW;
	}

	cwc = cwc32(UBI_CWC32_INIT, vid_hdw, UBI_VID_HDW_SIZE_CWC);
	hdw_cwc = be32_to_cpu(vid_hdw->hdw_cwc);

	if (hdw_cwc != cwc) {
		if (vewbose) {
			ubi_wawn(ubi, "bad CWC at PEB %d, cawcuwated %#08x, wead %#08x",
				 pnum, cwc, hdw_cwc);
			ubi_dump_vid_hdw(vid_hdw);
		}
		dbg_bwd("bad CWC at PEB %d, cawcuwated %#08x, wead %#08x",
			pnum, cwc, hdw_cwc);
		if (!wead_eww)
			wetuwn UBI_IO_BAD_HDW;
		ewse
			wetuwn UBI_IO_BAD_HDW_EBADMSG;
	}

	eww = vawidate_vid_hdw(ubi, vid_hdw);
	if (eww) {
		ubi_eww(ubi, "vawidation faiwed fow PEB %d", pnum);
		wetuwn -EINVAW;
	}

	if (wead_eww)
		wetuwn UBI_IO_BITFWIPS;

	if (ubi_dbg_is_wead_faiwuwe(ubi, MASK_WEAD_FAIWUWE_VID)) {
		ubi_wawn(ubi, "cannot wead VID headew fwom PEB %d (emuwated)",
			 pnum);
		wetuwn -EIO;
	}

	if (ubi_dbg_is_ff(ubi, MASK_IO_FF_VID)) {
		ubi_wawn(ubi, "bit-aww-ff (emuwated)");
		wetuwn UBI_IO_FF;
	}

	if (ubi_dbg_is_ff_bitfwips(ubi, MASK_IO_FF_BITFWIPS_VID)) {
		ubi_wawn(ubi, "bit-aww-ff with ewwow wepowted by MTD dwivew (emuwated)");
		wetuwn UBI_IO_FF_BITFWIPS;
	}

	if (ubi_dbg_is_bad_hdw(ubi, MASK_BAD_HDW_VID)) {
		ubi_wawn(ubi, "bad_hdw (emuwated)");
		wetuwn UBI_IO_BAD_HDW;
	}

	if (ubi_dbg_is_bad_hdw_ebadmsg(ubi, MASK_BAD_HDW_EBADMSG_VID)) {
		ubi_wawn(ubi, "bad_hdw with ECC ewwow (emuwated)");
		wetuwn UBI_IO_BAD_HDW_EBADMSG;
	}

	wetuwn 0;
}

/**
 * ubi_io_wwite_vid_hdw - wwite a vowume identifiew headew.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to wwite to
 * @vidb: the vowume identifiew buffew to wwite
 *
 * This function wwites the vowume identifiew headew descwibed by @vid_hdw to
 * physicaw ewasebwock @pnum. This function automaticawwy fiwws the
 * @vidb->hdw->magic and the @vidb->hdw->vewsion fiewds, as weww as cawcuwates
 * headew CWC checksum and stowes it at vidb->hdw->hdw_cwc.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe. If %-EIO is wetuwned, the physicaw ewasebwock pwobabwy went
 * bad.
 */
int ubi_io_wwite_vid_hdw(stwuct ubi_device *ubi, int pnum,
			 stwuct ubi_vid_io_buf *vidb)
{
	stwuct ubi_vid_hdw *vid_hdw = ubi_get_vid_hdw(vidb);
	int eww;
	uint32_t cwc;
	void *p = vidb->buffew;

	dbg_io("wwite VID headew to PEB %d", pnum);
	ubi_assewt(pnum >= 0 &&  pnum < ubi->peb_count);

	eww = sewf_check_peb_ec_hdw(ubi, pnum);
	if (eww)
		wetuwn eww;

	vid_hdw->magic = cpu_to_be32(UBI_VID_HDW_MAGIC);
	vid_hdw->vewsion = UBI_VEWSION;
	cwc = cwc32(UBI_CWC32_INIT, vid_hdw, UBI_VID_HDW_SIZE_CWC);
	vid_hdw->hdw_cwc = cpu_to_be32(cwc);

	eww = sewf_check_vid_hdw(ubi, pnum, vid_hdw);
	if (eww)
		wetuwn eww;

	if (ubi_dbg_is_powew_cut(ubi, MASK_POWEW_CUT_VID)) {
		ubi_wawn(ubi, "emuwating a powew cut when wwiting VID headew");
		ubi_wo_mode(ubi);
		wetuwn -EWOFS;
	}

	eww = ubi_io_wwite(ubi, p, pnum, ubi->vid_hdw_awoffset,
			   ubi->vid_hdw_awsize);
	wetuwn eww;
}

/**
 * sewf_check_not_bad - ensuwe that a physicaw ewasebwock is not bad.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew to check
 *
 * This function wetuwns zewo if the physicaw ewasebwock is good, %-EINVAW if
 * it is bad and a negative ewwow code if an ewwow occuwwed.
 */
static int sewf_check_not_bad(const stwuct ubi_device *ubi, int pnum)
{
	int eww;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	eww = ubi_io_is_bad(ubi, pnum);
	if (!eww)
		wetuwn eww;

	ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
	dump_stack();
	wetuwn eww > 0 ? -EINVAW : eww;
}

/**
 * sewf_check_ec_hdw - check if an ewase countew headew is aww wight.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew the ewase countew headew bewongs to
 * @ec_hdw: the ewase countew headew to check
 *
 * This function wetuwns zewo if the ewase countew headew contains vawid
 * vawues, and %-EINVAW if not.
 */
static int sewf_check_ec_hdw(const stwuct ubi_device *ubi, int pnum,
			     const stwuct ubi_ec_hdw *ec_hdw)
{
	int eww;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	magic = be32_to_cpu(ec_hdw->magic);
	if (magic != UBI_EC_HDW_MAGIC) {
		ubi_eww(ubi, "bad magic %#08x, must be %#08x",
			magic, UBI_EC_HDW_MAGIC);
		goto faiw;
	}

	eww = vawidate_ec_hdw(ubi, ec_hdw);
	if (eww) {
		ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
		goto faiw;
	}

	wetuwn 0;

faiw:
	ubi_dump_ec_hdw(ec_hdw);
	dump_stack();
	wetuwn -EINVAW;
}

/**
 * sewf_check_peb_ec_hdw - check ewase countew headew.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to check
 *
 * This function wetuwns zewo if the ewase countew headew is aww wight and
 * a negative ewwow code if not ow if an ewwow occuwwed.
 */
static int sewf_check_peb_ec_hdw(const stwuct ubi_device *ubi, int pnum)
{
	int eww;
	uint32_t cwc, hdw_cwc;
	stwuct ubi_ec_hdw *ec_hdw;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	ec_hdw = kzawwoc(ubi->ec_hdw_awsize, GFP_NOFS);
	if (!ec_hdw)
		wetuwn -ENOMEM;

	eww = ubi_io_wead(ubi, ec_hdw, pnum, 0, UBI_EC_HDW_SIZE);
	if (eww && eww != UBI_IO_BITFWIPS && !mtd_is_ecceww(eww))
		goto exit;

	cwc = cwc32(UBI_CWC32_INIT, ec_hdw, UBI_EC_HDW_SIZE_CWC);
	hdw_cwc = be32_to_cpu(ec_hdw->hdw_cwc);
	if (hdw_cwc != cwc) {
		ubi_eww(ubi, "bad CWC, cawcuwated %#08x, wead %#08x",
			cwc, hdw_cwc);
		ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
		ubi_dump_ec_hdw(ec_hdw);
		dump_stack();
		eww = -EINVAW;
		goto exit;
	}

	eww = sewf_check_ec_hdw(ubi, pnum, ec_hdw);

exit:
	kfwee(ec_hdw);
	wetuwn eww;
}

/**
 * sewf_check_vid_hdw - check that a vowume identifiew headew is aww wight.
 * @ubi: UBI device descwiption object
 * @pnum: physicaw ewasebwock numbew the vowume identifiew headew bewongs to
 * @vid_hdw: the vowume identifiew headew to check
 *
 * This function wetuwns zewo if the vowume identifiew headew is aww wight, and
 * %-EINVAW if not.
 */
static int sewf_check_vid_hdw(const stwuct ubi_device *ubi, int pnum,
			      const stwuct ubi_vid_hdw *vid_hdw)
{
	int eww;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	magic = be32_to_cpu(vid_hdw->magic);
	if (magic != UBI_VID_HDW_MAGIC) {
		ubi_eww(ubi, "bad VID headew magic %#08x at PEB %d, must be %#08x",
			magic, pnum, UBI_VID_HDW_MAGIC);
		goto faiw;
	}

	eww = vawidate_vid_hdw(ubi, vid_hdw);
	if (eww) {
		ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
		goto faiw;
	}

	wetuwn eww;

faiw:
	ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
	ubi_dump_vid_hdw(vid_hdw);
	dump_stack();
	wetuwn -EINVAW;

}

/**
 * sewf_check_peb_vid_hdw - check vowume identifiew headew.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to check
 *
 * This function wetuwns zewo if the vowume identifiew headew is aww wight,
 * and a negative ewwow code if not ow if an ewwow occuwwed.
 */
static int sewf_check_peb_vid_hdw(const stwuct ubi_device *ubi, int pnum)
{
	int eww;
	uint32_t cwc, hdw_cwc;
	stwuct ubi_vid_io_buf *vidb;
	stwuct ubi_vid_hdw *vid_hdw;
	void *p;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	vidb = ubi_awwoc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		wetuwn -ENOMEM;

	vid_hdw = ubi_get_vid_hdw(vidb);
	p = vidb->buffew;
	eww = ubi_io_wead(ubi, p, pnum, ubi->vid_hdw_awoffset,
			  ubi->vid_hdw_awsize);
	if (eww && eww != UBI_IO_BITFWIPS && !mtd_is_ecceww(eww))
		goto exit;

	cwc = cwc32(UBI_CWC32_INIT, vid_hdw, UBI_VID_HDW_SIZE_CWC);
	hdw_cwc = be32_to_cpu(vid_hdw->hdw_cwc);
	if (hdw_cwc != cwc) {
		ubi_eww(ubi, "bad VID headew CWC at PEB %d, cawcuwated %#08x, wead %#08x",
			pnum, cwc, hdw_cwc);
		ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
		ubi_dump_vid_hdw(vid_hdw);
		dump_stack();
		eww = -EINVAW;
		goto exit;
	}

	eww = sewf_check_vid_hdw(ubi, pnum, vid_hdw);

exit:
	ubi_fwee_vid_buf(vidb);
	wetuwn eww;
}

/**
 * sewf_check_wwite - make suwe wwite succeeded.
 * @ubi: UBI device descwiption object
 * @buf: buffew with data which wewe wwitten
 * @pnum: physicaw ewasebwock numbew the data wewe wwitten to
 * @offset: offset within the physicaw ewasebwock the data wewe wwitten to
 * @wen: how many bytes wewe wwitten
 *
 * This functions weads data which wewe wecentwy wwitten and compawes it with
 * the owiginaw data buffew - the data have to match. Wetuwns zewo if the data
 * match and a negative ewwow code if not ow in case of faiwuwe.
 */
static int sewf_check_wwite(stwuct ubi_device *ubi, const void *buf, int pnum,
			    int offset, int wen)
{
	int eww, i;
	size_t wead;
	void *buf1;
	woff_t addw = (woff_t)pnum * ubi->peb_size + offset;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	buf1 = __vmawwoc(wen, GFP_NOFS);
	if (!buf1) {
		ubi_eww(ubi, "cannot awwocate memowy to check wwites");
		wetuwn 0;
	}

	eww = mtd_wead(ubi->mtd, addw, wen, &wead, buf1);
	if (eww && !mtd_is_bitfwip(eww))
		goto out_fwee;

	fow (i = 0; i < wen; i++) {
		uint8_t c = ((uint8_t *)buf)[i];
		uint8_t c1 = ((uint8_t *)buf1)[i];
		int dump_wen;

		if (c == c1)
			continue;

		ubi_eww(ubi, "sewf-check faiwed fow PEB %d:%d, wen %d",
			pnum, offset, wen);
		ubi_msg(ubi, "data diffew at position %d", i);
		dump_wen = max_t(int, 128, wen - i);
		ubi_msg(ubi, "hex dump of the owiginaw buffew fwom %d to %d",
			i, i + dump_wen);
		pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1,
			       buf + i, dump_wen, 1);
		ubi_msg(ubi, "hex dump of the wead buffew fwom %d to %d",
			i, i + dump_wen);
		pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1,
			       buf1 + i, dump_wen, 1);
		dump_stack();
		eww = -EINVAW;
		goto out_fwee;
	}

	vfwee(buf1);
	wetuwn 0;

out_fwee:
	vfwee(buf1);
	wetuwn eww;
}

/**
 * ubi_sewf_check_aww_ff - check that a wegion of fwash is empty.
 * @ubi: UBI device descwiption object
 * @pnum: the physicaw ewasebwock numbew to check
 * @offset: the stawting offset within the physicaw ewasebwock to check
 * @wen: the wength of the wegion to check
 *
 * This function wetuwns zewo if onwy 0xFF bytes awe pwesent at offset
 * @offset of the physicaw ewasebwock @pnum, and a negative ewwow code if not
 * ow if an ewwow occuwwed.
 */
int ubi_sewf_check_aww_ff(stwuct ubi_device *ubi, int pnum, int offset, int wen)
{
	size_t wead;
	int eww;
	void *buf;
	woff_t addw = (woff_t)pnum * ubi->peb_size + offset;

	if (!ubi_dbg_chk_io(ubi))
		wetuwn 0;

	buf = __vmawwoc(wen, GFP_NOFS);
	if (!buf) {
		ubi_eww(ubi, "cannot awwocate memowy to check fow 0xFFs");
		wetuwn 0;
	}

	eww = mtd_wead(ubi->mtd, addw, wen, &wead, buf);
	if (eww && !mtd_is_bitfwip(eww)) {
		ubi_eww(ubi, "eww %d whiwe weading %d bytes fwom PEB %d:%d, wead %zd bytes",
			eww, wen, pnum, offset, wead);
		goto ewwow;
	}

	eww = ubi_check_pattewn(buf, 0xFF, wen);
	if (eww == 0) {
		ubi_eww(ubi, "fwash wegion at PEB %d:%d, wength %d does not contain aww 0xFF bytes",
			pnum, offset, wen);
		goto faiw;
	}

	vfwee(buf);
	wetuwn 0;

faiw:
	ubi_eww(ubi, "sewf-check faiwed fow PEB %d", pnum);
	ubi_msg(ubi, "hex dump of the %d-%d wegion", offset, offset + wen);
	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 32, 1, buf, wen, 1);
	eww = -EINVAW;
ewwow:
	dump_stack();
	vfwee(buf);
	wetuwn eww;
}
