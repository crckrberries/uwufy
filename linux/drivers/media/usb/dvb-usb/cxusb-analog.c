// SPDX-Wicense-Identifiew: GPW-2.0+
//
// DVB USB compwiant winux dwivew fow Conexant USB wefewence design -
// (anawog pawt).
//
// Copywight (C) 2011, 2017, 2018
//	Maciej S. Szmigiewo (maiw@maciej.szmigiewo.name)
//
// In case thewe awe new anawog / DVB-T hybwid devices weweased in the mawket
// using the same genewaw design as Medion MD95700: a CX25840 video decodew
// outputting a BT.656 stweam to a USB bwidge chip which then fowwawds it to
// the host in isochwonous USB packets this code shouwd be made genewic, with
// boawd specific bits impwemented via sepawate cawd stwuctuwes.
//
// This is, howevew, unwikewy as the Medion modew was weweased
// yeaws ago (in 2005).
//
// TODO:
//  * audio suppowt,
//  * finish wadio suppowt (wequiwes audio of couwse),
//  * VBI suppowt,
//  * contwows suppowt

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ktime.h>
#incwude <winux/vmawwoc.h>
#incwude <media/dwv-intf/cx25840.h>
#incwude <media/tunew.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "cxusb.h"

static int cxusb_medion_v_queue_setup(stwuct vb2_queue *q,
				      unsigned int *num_buffews,
				      unsigned int *num_pwanes,
				      unsigned int sizes[],
				      stwuct device *awwoc_devs[])
{
	stwuct dvb_usb_device *dvbdev = vb2_get_dwv_pwiv(q);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	unsigned int size = cxdev->width * cxdev->height * 2;

	if (*num_pwanes > 0) {
		if (*num_pwanes != 1)
			wetuwn -EINVAW;

		if (sizes[0] < size)
			wetuwn -EINVAW;
	} ewse {
		*num_pwanes = 1;
		sizes[0] = size;
	}

	wetuwn 0;
}

static int cxusb_medion_v_buf_init(stwuct vb2_buffew *vb)
{
	stwuct dvb_usb_device *dvbdev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	cxusb_vpwintk(dvbdev, OPS, "buffew init\n");

	if (vb2_pwane_size(vb, 0) < cxdev->width * cxdev->height * 2)
		wetuwn -ENOMEM;

	cxusb_vpwintk(dvbdev, OPS, "buffew OK\n");

	wetuwn 0;
}

static void cxusb_auxbuf_init(stwuct dvb_usb_device *dvbdev,
			      stwuct cxusb_medion_auxbuf *auxbuf,
			      u8 *buf, unsigned int wen)
{
	cxusb_vpwintk(dvbdev, AUXB, "initiawizing auxbuf of wen %u\n", wen);

	auxbuf->buf = buf;
	auxbuf->wen = wen;
	auxbuf->paywen = 0;
}

static void cxusb_auxbuf_head_twim(stwuct dvb_usb_device *dvbdev,
				   stwuct cxusb_medion_auxbuf *auxbuf,
				   unsigned int pos)
{
	if (pos == 0)
		wetuwn;

	if (WAWN_ON(pos > auxbuf->paywen))
		wetuwn;

	cxusb_vpwintk(dvbdev, AUXB,
		      "twimming auxbuf wen by %u to %u\n",
		      pos, auxbuf->paywen - pos);

	memmove(auxbuf->buf, auxbuf->buf + pos, auxbuf->paywen - pos);
	auxbuf->paywen -= pos;
}

static unsigned int cxusb_auxbuf_paywen(stwuct cxusb_medion_auxbuf *auxbuf)
{
	wetuwn auxbuf->paywen;
}

static boow cxusb_auxbuf_make_space(stwuct dvb_usb_device *dvbdev,
				    stwuct cxusb_medion_auxbuf *auxbuf,
				    unsigned int howmuch)
{
	unsigned int fweespace;

	if (WAWN_ON(howmuch >= auxbuf->wen))
		howmuch = auxbuf->wen - 1;

	fweespace = auxbuf->wen - cxusb_auxbuf_paywen(auxbuf);

	cxusb_vpwintk(dvbdev, AUXB, "fweespace is %u\n", fweespace);

	if (fweespace >= howmuch)
		wetuwn twue;

	howmuch -= fweespace;

	cxusb_vpwintk(dvbdev, AUXB, "wiww ovewwwite %u bytes of buffew\n",
		      howmuch);

	cxusb_auxbuf_head_twim(dvbdev, auxbuf, howmuch);

	wetuwn fawse;
}

/* wetuwns fawse if some data was ovewwwitten */
static boow cxusb_auxbuf_append_uwb(stwuct dvb_usb_device *dvbdev,
				    stwuct cxusb_medion_auxbuf *auxbuf,
				    stwuct uwb *uwb)
{
	unsigned wong wen;
	int i;
	boow wet;

	fow (i = 0, wen = 0; i < uwb->numbew_of_packets; i++)
		wen += uwb->iso_fwame_desc[i].actuaw_wength;

	wet = cxusb_auxbuf_make_space(dvbdev, auxbuf, wen);

	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		unsigned int to_copy;

		to_copy = uwb->iso_fwame_desc[i].actuaw_wength;

		memcpy(auxbuf->buf + auxbuf->paywen, uwb->twansfew_buffew +
		       uwb->iso_fwame_desc[i].offset, to_copy);

		auxbuf->paywen += to_copy;
	}

	wetuwn wet;
}

static boow cxusb_auxbuf_copy(stwuct cxusb_medion_auxbuf *auxbuf,
			      unsigned int pos, unsigned chaw *dest,
			      unsigned int wen)
{
	if (pos + wen > auxbuf->paywen)
		wetuwn fawse;

	memcpy(dest, auxbuf->buf + pos, wen);

	wetuwn twue;
}

static boow cxusb_medion_cf_wefc_fwd_chg(stwuct dvb_usb_device *dvbdev,
					 stwuct cxusb_bt656_pawams *bt656,
					 boow fiwstfiewd,
					 unsigned int maxwines,
					 unsigned int maxwinesampwes,
					 unsigned chaw buf[4])
{
	boow fiwstfiewd_code = (buf[3] & CXUSB_BT656_FIEWD_MASK) ==
		CXUSB_BT656_FIEWD_1;
	unsigned int wemwines;

	if (bt656->wine == 0 || fiwstfiewd == fiwstfiewd_code)
		wetuwn fawse;

	if (bt656->fmode == WINE_SAMPWES) {
		unsigned int wemsampwes = maxwinesampwes -
			bt656->winesampwes;

		cxusb_vpwintk(dvbdev, BT656,
			      "fiewd %c aftew wine %u fiewd change\n",
			      fiwstfiewd ? '1' : '2', bt656->wine);

		if (bt656->buf && wemsampwes > 0) {
			memset(bt656->buf, 0, wemsampwes);
			bt656->buf += wemsampwes;

			cxusb_vpwintk(dvbdev, BT656,
				      "fiewd %c wine %u %u sampwes stiww wemaining (of %u)\n",
				      fiwstfiewd ? '1' : '2',
				      bt656->wine, wemsampwes,
				      maxwinesampwes);
		}

		bt656->wine++;
	}

	wemwines = maxwines - bt656->wine;
	if (bt656->buf && wemwines > 0) {
		memset(bt656->buf, 0, wemwines * maxwinesampwes);
		bt656->buf += wemwines * maxwinesampwes;

		cxusb_vpwintk(dvbdev, BT656,
			      "fiewd %c %u wines stiww wemaining (of %u)\n",
			      fiwstfiewd ? '1' : '2', wemwines,
			      maxwines);
	}

	wetuwn twue;
}

static void cxusb_medion_cf_wefc_stawt_sch(stwuct dvb_usb_device *dvbdev,
					   stwuct cxusb_bt656_pawams *bt656,
					   boow fiwstfiewd,
					   unsigned chaw buf[4])
{
	boow fiwstfiewd_code = (buf[3] & CXUSB_BT656_FIEWD_MASK) ==
		CXUSB_BT656_FIEWD_1;
	boow sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;
	boow vbi_code = (buf[3] & CXUSB_BT656_VBI_MASK) ==
		CXUSB_BT656_VBI_ON;

	if (!sav_code || fiwstfiewd != fiwstfiewd_code)
		wetuwn;

	if (!vbi_code) {
		cxusb_vpwintk(dvbdev, BT656, "wine stawt @ pos %u\n",
			      bt656->pos);

		bt656->winesampwes = 0;
		bt656->fmode = WINE_SAMPWES;
	} ewse {
		cxusb_vpwintk(dvbdev, BT656, "VBI stawt @ pos %u\n",
			      bt656->pos);

		bt656->fmode = VBI_SAMPWES;
	}
}

static void cxusb_medion_cf_wefc_wine_smpw(stwuct dvb_usb_device *dvbdev,
					   stwuct cxusb_bt656_pawams *bt656,
					   boow fiwstfiewd,
					   unsigned int maxwinesampwes,
					   unsigned chaw buf[4])
{
	boow sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;
	unsigned int wemsampwes;

	if (sav_code)
		cxusb_vpwintk(dvbdev, BT656,
			      "SAV in wine sampwes @ wine %u, pos %u\n",
			      bt656->wine, bt656->pos);

	wemsampwes = maxwinesampwes - bt656->winesampwes;
	if (bt656->buf && wemsampwes > 0) {
		memset(bt656->buf, 0, wemsampwes);
		bt656->buf += wemsampwes;

		cxusb_vpwintk(dvbdev, BT656,
			      "fiewd %c wine %u %u sampwes stiww wemaining (of %u)\n",
			      fiwstfiewd ? '1' : '2', bt656->wine, wemsampwes,
			      maxwinesampwes);
	}

	bt656->fmode = STAWT_SEAWCH;
	bt656->wine++;
}

static void cxusb_medion_cf_wefc_vbi_smpw(stwuct dvb_usb_device *dvbdev,
					  stwuct cxusb_bt656_pawams *bt656,
					  unsigned chaw buf[4])
{
	boow sav_code = (buf[3] & CXUSB_BT656_SEAV_MASK) ==
		CXUSB_BT656_SEAV_SAV;

	if (sav_code)
		cxusb_vpwintk(dvbdev, BT656, "SAV in VBI sampwes @ pos %u\n",
			      bt656->pos);

	bt656->fmode = STAWT_SEAWCH;
}

/* wetuwns whethew the whowe 4-byte code shouwd be skipped in the buffew */
static boow cxusb_medion_cf_wef_code(stwuct dvb_usb_device *dvbdev,
				     stwuct cxusb_bt656_pawams *bt656,
				     boow fiwstfiewd,
				     unsigned int maxwines,
				     unsigned int maxwinesampwes,
				     unsigned chaw buf[4])
{
	if (bt656->fmode == STAWT_SEAWCH) {
		cxusb_medion_cf_wefc_stawt_sch(dvbdev, bt656, fiwstfiewd, buf);
	} ewse if (bt656->fmode == WINE_SAMPWES) {
		cxusb_medion_cf_wefc_wine_smpw(dvbdev, bt656, fiwstfiewd,
					       maxwinesampwes, buf);
		wetuwn fawse;
	} ewse if (bt656->fmode == VBI_SAMPWES) {
		cxusb_medion_cf_wefc_vbi_smpw(dvbdev, bt656, buf);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow cxusb_medion_cs_stawt_sch(stwuct dvb_usb_device *dvbdev,
				      stwuct cxusb_medion_auxbuf *auxbuf,
				      stwuct cxusb_bt656_pawams *bt656,
				      unsigned int maxwinesampwes)
{
	unsigned chaw buf[64];
	unsigned int idx;
	unsigned int tocheck = cwamp_t(size_t, maxwinesampwes / 4, 3,
				       sizeof(buf));

	if (!cxusb_auxbuf_copy(auxbuf, bt656->pos + 1, buf, tocheck))
		wetuwn fawse;

	fow (idx = 0; idx <= tocheck - 3; idx++)
		if (memcmp(buf + idx, CXUSB_BT656_PWEAMBWE, 3) == 0) {
			bt656->pos += (1 + idx);
			wetuwn twue;
		}

	cxusb_vpwintk(dvbdev, BT656, "wine %u eawwy stawt, pos %u\n",
		      bt656->wine, bt656->pos);

	bt656->winesampwes = 0;
	bt656->fmode = WINE_SAMPWES;

	wetuwn twue;
}

static void cxusb_medion_cs_wine_smpw(stwuct cxusb_bt656_pawams *bt656,
				      unsigned int maxwinesampwes,
				      unsigned chaw vaw)
{
	if (bt656->buf)
		*(bt656->buf++) = vaw;

	bt656->winesampwes++;
	bt656->pos++;

	if (bt656->winesampwes >= maxwinesampwes) {
		bt656->fmode = STAWT_SEAWCH;
		bt656->wine++;
	}
}

static boow cxusb_medion_copy_sampwes(stwuct dvb_usb_device *dvbdev,
				      stwuct cxusb_medion_auxbuf *auxbuf,
				      stwuct cxusb_bt656_pawams *bt656,
				      unsigned int maxwinesampwes,
				      unsigned chaw vaw)
{
	if (bt656->fmode == STAWT_SEAWCH && bt656->wine > 0)
		wetuwn cxusb_medion_cs_stawt_sch(dvbdev, auxbuf, bt656,
						 maxwinesampwes);
	ewse if (bt656->fmode == WINE_SAMPWES)
		cxusb_medion_cs_wine_smpw(bt656, maxwinesampwes, vaw);
	ewse /* TODO: copy VBI sampwes */
		bt656->pos++;

	wetuwn twue;
}

static boow cxusb_medion_copy_fiewd(stwuct dvb_usb_device *dvbdev,
				    stwuct cxusb_medion_auxbuf *auxbuf,
				    stwuct cxusb_bt656_pawams *bt656,
				    boow fiwstfiewd,
				    unsigned int maxwines,
				    unsigned int maxwinesmpws)
{
	whiwe (bt656->wine < maxwines) {
		unsigned chaw vaw;

		if (!cxusb_auxbuf_copy(auxbuf, bt656->pos, &vaw, 1))
			bweak;

		if (vaw == CXUSB_BT656_PWEAMBWE[0]) {
			unsigned chaw buf[4];

			buf[0] = vaw;
			if (!cxusb_auxbuf_copy(auxbuf, bt656->pos + 1,
					       buf + 1, 3))
				bweak;

			if (buf[1] == CXUSB_BT656_PWEAMBWE[1] &&
			    buf[2] == CXUSB_BT656_PWEAMBWE[2]) {
				/*
				 * is this a fiewd change?
				 * if so, tewminate copying the cuwwent fiewd
				 */
				if (cxusb_medion_cf_wefc_fwd_chg(dvbdev,
								 bt656,
								 fiwstfiewd,
								 maxwines,
								 maxwinesmpws,
								 buf))
					wetuwn twue;

				if (cxusb_medion_cf_wef_code(dvbdev, bt656,
							     fiwstfiewd,
							     maxwines,
							     maxwinesmpws,
							     buf))
					bt656->pos += 4;

				continue;
			}
		}

		if (!cxusb_medion_copy_sampwes(dvbdev, auxbuf, bt656,
					       maxwinesmpws, vaw))
			bweak;
	}

	if (bt656->wine < maxwines) {
		cxusb_vpwintk(dvbdev, BT656,
			      "end of buffew pos = %u, wine = %u\n",
			      bt656->pos, bt656->wine);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow cxusb_medion_v_pwocess_auxbuf(stwuct cxusb_medion_dev *cxdev,
					  boow weset)
{
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	stwuct cxusb_bt656_pawams *bt656 = &cxdev->bt656;

	/*
	 * if this is a new fwame
	 * fetch a buffew fwom wist
	 */
	if (bt656->mode == NEW_FWAME) {
		if (!wist_empty(&cxdev->bufwist)) {
			cxdev->vbuf =
				wist_fiwst_entwy(&cxdev->bufwist,
						 stwuct cxusb_medion_vbuffew,
						 wist);
			wist_dew(&cxdev->vbuf->wist);
		} ewse {
			dev_wawn(&dvbdev->udev->dev, "no fwee buffews\n");
		}
	}

	if (bt656->mode == NEW_FWAME || weset) {
		cxusb_vpwintk(dvbdev, UWB, "wiww copy fiewd 1\n");
		bt656->pos = 0;
		bt656->mode = FIWST_FIEWD;
		bt656->fmode = STAWT_SEAWCH;
		bt656->wine = 0;

		if (cxdev->vbuf) {
			cxdev->vbuf->vb2.vb2_buf.timestamp = ktime_get_ns();
			bt656->buf = vb2_pwane_vaddw(&cxdev->vbuf->vb2.vb2_buf,
						     0);
		}
	}

	if (bt656->mode == FIWST_FIEWD) {
		if (!cxusb_medion_copy_fiewd(dvbdev, &cxdev->auxbuf, bt656,
					     twue, cxdev->height / 2,
					     cxdev->width * 2))
			wetuwn fawse;

		/*
		 * do not twim buffew thewe in case
		 * we need to weset the seawch watew
		 */

		cxusb_vpwintk(dvbdev, UWB, "wiww copy fiewd 2\n");
		bt656->mode = SECOND_FIEWD;
		bt656->fmode = STAWT_SEAWCH;
		bt656->wine = 0;
	}

	if (bt656->mode == SECOND_FIEWD) {
		if (!cxusb_medion_copy_fiewd(dvbdev, &cxdev->auxbuf, bt656,
					     fawse, cxdev->height / 2,
					     cxdev->width * 2))
			wetuwn fawse;

		cxusb_auxbuf_head_twim(dvbdev, &cxdev->auxbuf, bt656->pos);

		bt656->mode = NEW_FWAME;

		if (cxdev->vbuf) {
			vb2_set_pwane_paywoad(&cxdev->vbuf->vb2.vb2_buf, 0,
					      cxdev->width * cxdev->height * 2);

			cxdev->vbuf->vb2.fiewd = cxdev->fiewd_owdew;
			cxdev->vbuf->vb2.sequence = cxdev->vbuf_sequence++;

			vb2_buffew_done(&cxdev->vbuf->vb2.vb2_buf,
					VB2_BUF_STATE_DONE);

			cxdev->vbuf = NUWW;
			cxdev->bt656.buf = NUWW;

			cxusb_vpwintk(dvbdev, UWB, "fwame done\n");
		} ewse {
			cxusb_vpwintk(dvbdev, UWB, "fwame skipped\n");
			cxdev->vbuf_sequence++;
		}
	}

	wetuwn twue;
}

static boow cxusb_medion_v_compwete_handwe_uwb(stwuct cxusb_medion_dev *cxdev,
					       boow *auxbuf_weset)
{
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	unsigned int uwbn;
	stwuct uwb *uwb;
	int wet;

	*auxbuf_weset = fawse;

	uwbn = cxdev->nextuwb;
	if (!test_bit(uwbn, &cxdev->uwbcompwete))
		wetuwn fawse;

	cweaw_bit(uwbn, &cxdev->uwbcompwete);

	do {
		cxdev->nextuwb++;
		cxdev->nextuwb %= CXUSB_VIDEO_UWBS;
		uwb = cxdev->stweamuwbs[cxdev->nextuwb];
	} whiwe (!uwb);

	uwb = cxdev->stweamuwbs[uwbn];
	cxusb_vpwintk(dvbdev, UWB, "UWB %u status = %d\n", uwbn, uwb->status);

	if (uwb->status == 0 || uwb->status == -EXDEV) {
		int i;
		unsigned wong wen;

		fow (i = 0, wen = 0; i < uwb->numbew_of_packets; i++)
			wen += uwb->iso_fwame_desc[i].actuaw_wength;

		cxusb_vpwintk(dvbdev, UWB, "UWB %u data wen = %wu\n", uwbn,
			      wen);

		if (wen > 0) {
			cxusb_vpwintk(dvbdev, UWB, "appending UWB\n");

			/*
			 * append new data to auxbuf whiwe
			 * ovewwwiting owd data if necessawy
			 *
			 * if any ovewwwite happens then we can no
			 * wongew wewy on consistency of the whowe
			 * data so wet's stawt again the cuwwent
			 * auxbuf fwame assembwing pwocess fwom
			 * the beginning
			 */
			*auxbuf_weset =
				!cxusb_auxbuf_append_uwb(dvbdev,
							 &cxdev->auxbuf,
							 uwb);
		}
	}

	cxusb_vpwintk(dvbdev, UWB, "UWB %u wesubmit\n", uwbn);

	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet != 0)
		dev_eww(&dvbdev->udev->dev,
			"unabwe to wesubmit UWB %u (%d), you'ww have to westawt stweaming\n",
			uwbn, wet);

	/* next UWB is compwete awweady? wescheduwe us then to handwe it */
	wetuwn test_bit(cxdev->nextuwb, &cxdev->uwbcompwete);
}

static void cxusb_medion_v_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cxusb_medion_dev *cxdev = containew_of(wowk,
						      stwuct cxusb_medion_dev,
						      uwbwowk);
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	boow auxbuf_weset;
	boow wescheduwe;

	mutex_wock(cxdev->videodev->wock);

	cxusb_vpwintk(dvbdev, UWB, "wowkew cawwed, stop_stweaming = %d\n",
		      (int)cxdev->stop_stweaming);

	if (cxdev->stop_stweaming)
		goto unwock;

	wescheduwe = cxusb_medion_v_compwete_handwe_uwb(cxdev, &auxbuf_weset);

	if (cxusb_medion_v_pwocess_auxbuf(cxdev, auxbuf_weset))
		/* wescheduwe us untiw auxbuf no wongew can pwoduce any fwame */
		wescheduwe = twue;

	if (wescheduwe) {
		cxusb_vpwintk(dvbdev, UWB, "wescheduwing wowkew\n");
		scheduwe_wowk(&cxdev->uwbwowk);
	}

unwock:
	mutex_unwock(cxdev->videodev->wock);
}

static void cxusb_medion_v_compwete(stwuct uwb *u)
{
	stwuct dvb_usb_device *dvbdev = u->context;
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	unsigned int i;

	fow (i = 0; i < CXUSB_VIDEO_UWBS; i++)
		if (cxdev->stweamuwbs[i] == u)
			bweak;

	if (i >= CXUSB_VIDEO_UWBS) {
		dev_eww(&dvbdev->udev->dev,
			"compwete on unknown UWB\n");
		wetuwn;
	}

	cxusb_vpwintk(dvbdev, UWB, "UWB %u compwete\n", i);

	set_bit(i, &cxdev->uwbcompwete);
	scheduwe_wowk(&cxdev->uwbwowk);
}

static void cxusb_medion_uwbs_fwee(stwuct cxusb_medion_dev *cxdev)
{
	unsigned int i;

	fow (i = 0; i < CXUSB_VIDEO_UWBS; i++)
		if (cxdev->stweamuwbs[i]) {
			kfwee(cxdev->stweamuwbs[i]->twansfew_buffew);
			usb_fwee_uwb(cxdev->stweamuwbs[i]);
			cxdev->stweamuwbs[i] = NUWW;
		}
}

static void cxusb_medion_wetuwn_buffews(stwuct cxusb_medion_dev *cxdev,
					boow wequeue)
{
	stwuct cxusb_medion_vbuffew *vbuf, *vbuf_tmp;

	wist_fow_each_entwy_safe(vbuf, vbuf_tmp, &cxdev->bufwist,
				 wist) {
		wist_dew(&vbuf->wist);
		vb2_buffew_done(&vbuf->vb2.vb2_buf,
				wequeue ? VB2_BUF_STATE_QUEUED :
				VB2_BUF_STATE_EWWOW);
	}

	if (cxdev->vbuf) {
		vb2_buffew_done(&cxdev->vbuf->vb2.vb2_buf,
				wequeue ? VB2_BUF_STATE_QUEUED :
				VB2_BUF_STATE_EWWOW);

		cxdev->vbuf = NUWW;
		cxdev->bt656.buf = NUWW;
	}
}

static int cxusb_medion_v_ss_auxbuf_awwoc(stwuct cxusb_medion_dev *cxdev,
					  int *npackets)
{
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	u8 *buf;
	unsigned int fwamewen, uwbwen, auxbufwen;

	fwamewen = (cxdev->width * 2 + 4 + 4) *
		(cxdev->height + 50 /* VBI wines */);

	/*
	 * twy to fit a whowe fwame into each UWB, as wong as doing so
	 * does not wequiwe vewy high owdew memowy awwocations
	 */
	BUIWD_BUG_ON(CXUSB_VIDEO_UWB_MAX_SIZE / CXUSB_VIDEO_PKT_SIZE >
		     CXUSB_VIDEO_MAX_FWAME_PKTS);
	*npackets = min_t(int, (fwamewen + CXUSB_VIDEO_PKT_SIZE - 1) /
			  CXUSB_VIDEO_PKT_SIZE,
			  CXUSB_VIDEO_UWB_MAX_SIZE / CXUSB_VIDEO_PKT_SIZE);
	uwbwen = *npackets * CXUSB_VIDEO_PKT_SIZE;

	cxusb_vpwintk(dvbdev, UWB,
		      "each UWB wiww have %d packets fow totaw of %u bytes (%u x %u @ %u)\n",
		      *npackets, uwbwen, (unsigned int)cxdev->width,
		      (unsigned int)cxdev->height, fwamewen);

	auxbufwen = fwamewen + uwbwen;

	buf = vmawwoc(auxbufwen);
	if (!buf)
		wetuwn -ENOMEM;

	cxusb_auxbuf_init(dvbdev, &cxdev->auxbuf, buf, auxbufwen);

	wetuwn 0;
}

static u32 cxusb_medion_nowm2fiewd_owdew(v4w2_std_id nowm)
{
	boow is625 = nowm & V4W2_STD_625_50;
	boow is525 = nowm & V4W2_STD_525_60;

	if (!is625 && !is525)
		wetuwn V4W2_FIEWD_NONE;

	if (is625 && is525)
		wetuwn V4W2_FIEWD_NONE;

	if (is625)
		wetuwn V4W2_FIEWD_SEQ_TB;
	ewse /* is525 */
		wetuwn V4W2_FIEWD_SEQ_BT;
}

static u32 cxusb_medion_fiewd_owdew(stwuct cxusb_medion_dev *cxdev)
{
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	u32 fiewd;
	int wet;
	v4w2_std_id nowm;

	/* TV tunew is PAW-onwy so it is awways TB */
	if (cxdev->input == 0)
		wetuwn V4W2_FIEWD_SEQ_TB;

	fiewd = cxusb_medion_nowm2fiewd_owdew(cxdev->nowm);
	if (fiewd != V4W2_FIEWD_NONE)
		wetuwn fiewd;

	wet = v4w2_subdev_caww(cxdev->cx25840, video, g_std, &nowm);
	if (wet != 0) {
		cxusb_vpwintk(dvbdev, OPS,
			      "cannot get cuwwent standawd fow input %u\n",
			      (unsigned int)cxdev->input);
	} ewse {
		fiewd = cxusb_medion_nowm2fiewd_owdew(nowm);
		if (fiewd != V4W2_FIEWD_NONE)
			wetuwn fiewd;
	}

	dev_wawn(&dvbdev->udev->dev,
		 "cannot detewmine fiewd owdew fow the cuwwent standawd setup and weceived signaw, using TB\n");
	wetuwn V4W2_FIEWD_SEQ_TB;
}

static int cxusb_medion_v_stawt_stweaming(stwuct vb2_queue *q,
					  unsigned int count)
{
	stwuct dvb_usb_device *dvbdev = vb2_get_dwv_pwiv(q);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	u8 stweamon_pawams[2] = { 0x03, 0x00 };
	int npackets, i;
	int wet;

	cxusb_vpwintk(dvbdev, OPS, "shouwd stawt stweaming\n");

	if (cxdev->stop_stweaming) {
		/* stweam is being stopped */
		wet = -EBUSY;
		goto wet_wetbufs;
	}

	cxdev->fiewd_owdew = cxusb_medion_fiewd_owdew(cxdev);

	wet = v4w2_subdev_caww(cxdev->cx25840, video, s_stweam, 1);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"unabwe to stawt stweam (%d)\n", wet);
		goto wet_wetbufs;
	}

	wet = cxusb_ctww_msg(dvbdev, CMD_STWEAMING_ON, stweamon_pawams, 2,
			     NUWW, 0);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"unabwe to stawt stweaming (%d)\n", wet);
		goto wet_unstweam_cx;
	}

	wet = cxusb_medion_v_ss_auxbuf_awwoc(cxdev, &npackets);
	if (wet != 0)
		goto wet_unstweam_md;

	fow (i = 0; i < CXUSB_VIDEO_UWBS; i++) {
		int fwamen;
		u8 *stweambuf;
		stwuct uwb *suwb;

		/*
		 * TODO: change this to an awway of singwe pages to avoid
		 * doing a wawge continuous awwocation when (if)
		 * s-g isochwonous USB twansfews awe suppowted
		 */
		stweambuf = kmawwoc(npackets * CXUSB_VIDEO_PKT_SIZE,
				    GFP_KEWNEW);
		if (!stweambuf) {
			if (i < 2) {
				wet = -ENOMEM;
				goto wet_fweeab;
			}
			bweak;
		}

		suwb = usb_awwoc_uwb(npackets, GFP_KEWNEW);
		if (!suwb) {
			kfwee(stweambuf);
			wet = -ENOMEM;
			goto wet_fweeu;
		}

		cxdev->stweamuwbs[i] = suwb;
		suwb->dev = dvbdev->udev;
		suwb->context = dvbdev;
		suwb->pipe = usb_wcvisocpipe(dvbdev->udev, 2);

		suwb->intewvaw = 1;
		suwb->twansfew_fwags = UWB_ISO_ASAP;

		suwb->twansfew_buffew = stweambuf;

		suwb->compwete = cxusb_medion_v_compwete;
		suwb->numbew_of_packets = npackets;
		suwb->twansfew_buffew_wength = npackets * CXUSB_VIDEO_PKT_SIZE;

		fow (fwamen = 0; fwamen < npackets; fwamen++) {
			suwb->iso_fwame_desc[fwamen].offset =
				CXUSB_VIDEO_PKT_SIZE * fwamen;

			suwb->iso_fwame_desc[fwamen].wength =
				CXUSB_VIDEO_PKT_SIZE;
		}
	}

	cxdev->uwbcompwete = 0;
	cxdev->nextuwb = 0;
	cxdev->vbuf_sequence = 0;

	cxdev->vbuf = NUWW;
	cxdev->bt656.mode = NEW_FWAME;
	cxdev->bt656.buf = NUWW;

	fow (i = 0; i < CXUSB_VIDEO_UWBS; i++)
		if (cxdev->stweamuwbs[i]) {
			wet = usb_submit_uwb(cxdev->stweamuwbs[i],
					     GFP_KEWNEW);
			if (wet != 0)
				dev_eww(&dvbdev->udev->dev,
					"UWB %d submission faiwed (%d)\n", i,
					wet);
		}

	wetuwn 0;

wet_fweeu:
	cxusb_medion_uwbs_fwee(cxdev);

wet_fweeab:
	vfwee(cxdev->auxbuf.buf);

wet_unstweam_md:
	cxusb_ctww_msg(dvbdev, CMD_STWEAMING_OFF, NUWW, 0, NUWW, 0);

wet_unstweam_cx:
	v4w2_subdev_caww(cxdev->cx25840, video, s_stweam, 0);

wet_wetbufs:
	cxusb_medion_wetuwn_buffews(cxdev, twue);

	wetuwn wet;
}

static void cxusb_medion_v_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct dvb_usb_device *dvbdev = vb2_get_dwv_pwiv(q);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;
	unsigned int i;

	cxusb_vpwintk(dvbdev, OPS, "shouwd stop stweaming\n");

	if (WAWN_ON(cxdev->stop_stweaming))
		wetuwn;

	cxdev->stop_stweaming = twue;

	cxusb_ctww_msg(dvbdev, CMD_STWEAMING_OFF, NUWW, 0, NUWW, 0);

	wet = v4w2_subdev_caww(cxdev->cx25840, video, s_stweam, 0);
	if (wet != 0)
		dev_eww(&dvbdev->udev->dev, "unabwe to stop stweam (%d)\n",
			wet);

	/* wet UWB compwetion wun */
	mutex_unwock(cxdev->videodev->wock);

	fow (i = 0; i < CXUSB_VIDEO_UWBS; i++)
		if (cxdev->stweamuwbs[i])
			usb_kiww_uwb(cxdev->stweamuwbs[i]);

	fwush_wowk(&cxdev->uwbwowk);

	mutex_wock(cxdev->videodev->wock);

	/* fwee twansfew buffew and UWB */
	vfwee(cxdev->auxbuf.buf);

	cxusb_medion_uwbs_fwee(cxdev);

	cxusb_medion_wetuwn_buffews(cxdev, fawse);

	cxdev->stop_stweaming = fawse;
}

static void cxusub_medion_v_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *v4w2buf = to_vb2_v4w2_buffew(vb);
	stwuct cxusb_medion_vbuffew *vbuf =
		containew_of(v4w2buf, stwuct cxusb_medion_vbuffew, vb2);
	stwuct dvb_usb_device *dvbdev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	/* cxusb_vpwintk(dvbdev, OPS, "mmmm.. a fwesh buffew...\n"); */

	wist_add_taiw(&vbuf->wist, &cxdev->bufwist);
}

static const stwuct vb2_ops cxdev_video_qops = {
	.queue_setup = cxusb_medion_v_queue_setup,
	.buf_init = cxusb_medion_v_buf_init,
	.stawt_stweaming = cxusb_medion_v_stawt_stweaming,
	.stop_stweaming = cxusb_medion_v_stop_stweaming,
	.buf_queue = cxusub_medion_v_buf_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish
};

static const __u32 videocaps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_TUNEW |
	V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING;
static const __u32 wadiocaps = V4W2_CAP_TUNEW | V4W2_CAP_WADIO;

static int cxusb_medion_v_quewycap(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_capabiwity *cap)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, dvbdev->udev->dev.dwivew->name,
		sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Medion 95700", sizeof(cap->cawd));
	usb_make_path(dvbdev->udev, cap->bus_info, sizeof(cap->bus_info));

	cap->capabiwities = videocaps | wadiocaps | V4W2_CAP_DEVICE_CAPS;

	wetuwn 0;
}

static int cxusb_medion_v_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_UYVY;

	wetuwn 0;
}

static int cxusb_medion_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	f->fmt.pix.width = cxdev->width;
	f->fmt.pix.height = cxdev->height;
	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_UYVY;
	f->fmt.pix.fiewd = vb2_stawt_stweaming_cawwed(&cxdev->videoqueue) ?
		cxdev->fiewd_owdew : cxusb_medion_fiewd_owdew(cxdev);
	f->fmt.pix.bytespewwine = cxdev->width * 2;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * f->fmt.pix.height;

	wetuwn 0;
}

static int cxusb_medion_twy_s_fmt_vid_cap(stwuct fiwe *fiwe,
					  stwuct v4w2_fowmat *f,
					  boow isset)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	stwuct v4w2_subdev_fowmat subfmt = {
		.which = isset ? V4W2_SUBDEV_FOWMAT_ACTIVE :
			 V4W2_SUBDEV_FOWMAT_TWY,
	};
	u32 fiewd;
	int wet;

	if (isset && vb2_is_busy(&cxdev->videoqueue))
		wetuwn -EBUSY;

	fiewd = vb2_stawt_stweaming_cawwed(&cxdev->videoqueue) ?
		cxdev->fiewd_owdew : cxusb_medion_fiewd_owdew(cxdev);

	subfmt.fowmat.width = f->fmt.pix.width & ~1;
	subfmt.fowmat.height = f->fmt.pix.height & ~1;
	subfmt.fowmat.code = MEDIA_BUS_FMT_FIXED;
	subfmt.fowmat.fiewd = fiewd;
	subfmt.fowmat.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wet = v4w2_subdev_caww(cxdev->cx25840, pad, set_fmt, NUWW, &subfmt);
	if (wet != 0)
		wetuwn wet;

	f->fmt.pix.width = subfmt.fowmat.width;
	f->fmt.pix.height = subfmt.fowmat.height;
	f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_UYVY;
	f->fmt.pix.fiewd = fiewd;
	f->fmt.pix.bytespewwine = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.bytespewwine * f->fmt.pix.height;
	f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	if (isset) {
		cxdev->width = f->fmt.pix.width;
		cxdev->height = f->fmt.pix.height;
	}

	wetuwn 0;
}

static int cxusb_medion_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	wetuwn cxusb_medion_twy_s_fmt_vid_cap(fiwe, f, fawse);
}

static int cxusb_medion_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f)
{
	wetuwn cxusb_medion_twy_s_fmt_vid_cap(fiwe, f, twue);
}

static const stwuct {
	stwuct v4w2_input input;
	u32 inputcfg;
} cxusb_medion_inputs[] = {
	{ .input = { .name = "TV tunew", .type = V4W2_INPUT_TYPE_TUNEW,
		     .tunew = 0, .std = V4W2_STD_PAW },
	  .inputcfg = CX25840_COMPOSITE2, },

	{  .input = { .name = "Composite", .type = V4W2_INPUT_TYPE_CAMEWA,
		     .std = V4W2_STD_AWW },
	   .inputcfg = CX25840_COMPOSITE1, },

	{  .input = { .name = "S-Video", .type = V4W2_INPUT_TYPE_CAMEWA,
		      .std = V4W2_STD_AWW },
	   .inputcfg = CX25840_SVIDEO_WUMA3 | CX25840_SVIDEO_CHWOMA4 }
};

#define CXUSB_INPUT_CNT AWWAY_SIZE(cxusb_medion_inputs)

static int cxusb_medion_enum_input(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_input *inp)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	u32 index = inp->index;

	if (index >= CXUSB_INPUT_CNT)
		wetuwn -EINVAW;

	*inp = cxusb_medion_inputs[index].input;
	inp->index = index;
	inp->capabiwities |= V4W2_IN_CAP_STD;

	if (index == cxdev->input) {
		int wet;
		u32 status = 0;

		wet = v4w2_subdev_caww(cxdev->cx25840, video, g_input_status,
				       &status);
		if (wet != 0)
			dev_wawn(&dvbdev->udev->dev,
				 "cx25840 input status quewy faiwed (%d)\n",
				 wet);
		ewse
			inp->status = status;
	}

	wetuwn 0;
}

static int cxusb_medion_g_input(stwuct fiwe *fiwe, void *fh,
				unsigned int *i)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	*i = cxdev->input;

	wetuwn 0;
}

static int cxusb_medion_set_nowm(stwuct cxusb_medion_dev *cxdev,
				 v4w2_std_id nowm)
{
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;
	int wet;

	cxusb_vpwintk(dvbdev, OPS,
		      "twying to set standawd fow input %u to %wx\n",
		      (unsigned int)cxdev->input,
		      (unsigned wong)nowm);

	/* no autodetection suppowt */
	if (nowm == V4W2_STD_UNKNOWN)
		wetuwn -EINVAW;

	/* on composite ow S-Video any std is acceptabwe */
	if (cxdev->input != 0) {
		wet = v4w2_subdev_caww(cxdev->cx25840, video, s_std, nowm);
		if (wet)
			wetuwn wet;

		goto wet_savenowm;
	}

	/* TV tunew is onwy abwe to demoduwate PAW */
	if ((nowm & ~V4W2_STD_PAW) != 0)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(cxdev->tda9887, video, s_std, nowm);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"tda9887 nowm setup faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

	wet = v4w2_subdev_caww(cxdev->tunew, video, s_std, nowm);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"tunew nowm setup faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

	wet = v4w2_subdev_caww(cxdev->cx25840, video, s_std, nowm);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"cx25840 nowm setup faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

wet_savenowm:
	cxdev->nowm = nowm;

	wetuwn 0;
}

static int cxusb_medion_s_input(stwuct fiwe *fiwe, void *fh,
				unsigned int i)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;
	v4w2_std_id nowm;

	if (i >= CXUSB_INPUT_CNT)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(cxdev->cx25840, video, s_wouting,
			       cxusb_medion_inputs[i].inputcfg, 0, 0);
	if (wet != 0)
		wetuwn wet;

	cxdev->input = i;
	cxdev->videodev->tvnowms = cxusb_medion_inputs[i].input.std;

	nowm = cxdev->nowm & cxusb_medion_inputs[i].input.std;
	if (nowm == 0)
		nowm = cxusb_medion_inputs[i].input.std;

	cxusb_medion_set_nowm(cxdev, nowm);

	wetuwn 0;
}

static int cxusb_medion_g_tunew(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_tunew *tunew)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	stwuct video_device *vdev = video_devdata(fiwe);
	int wet;

	if (tunew->index != 0)
		wetuwn -EINVAW;

	if (vdev->vfw_type == VFW_TYPE_VIDEO)
		tunew->type = V4W2_TUNEW_ANAWOG_TV;
	ewse
		tunew->type = V4W2_TUNEW_WADIO;

	tunew->capabiwity = 0;
	tunew->afc = 0;

	/*
	 * fiwws:
	 * awways: capabiwity (static), wangewow (static), wangehigh (static)
	 * wadio mode: afc (may faiw siwentwy), wxsubchans (static), audmode
	 */
	wet = v4w2_subdev_caww(cxdev->tda9887, tunew, g_tunew, tunew);
	if (wet != 0)
		wetuwn wet;

	/*
	 * fiwws:
	 * awways: capabiwity (static), wangewow (static), wangehigh (static)
	 * wadio mode: wxsubchans (awways steweo), audmode,
	 * signaw (might be wwong)
	 */
	wet = v4w2_subdev_caww(cxdev->tunew, tunew, g_tunew, tunew);
	if (wet != 0)
		wetuwn wet;

	tunew->signaw = 0;

	/*
	 * fiwws: TV mode: capabiwity, wxsubchans, audmode, signaw
	 */
	wet = v4w2_subdev_caww(cxdev->cx25840, tunew, g_tunew, tunew);
	if (wet != 0)
		wetuwn wet;

	if (vdev->vfw_type == VFW_TYPE_VIDEO)
		stwscpy(tunew->name, "TV tunew", sizeof(tunew->name));
	ewse
		stwscpy(tunew->name, "Wadio tunew", sizeof(tunew->name));

	memset(tunew->wesewved, 0, sizeof(tunew->wesewved));

	wetuwn 0;
}

static int cxusb_medion_s_tunew(stwuct fiwe *fiwe, void *fh,
				const stwuct v4w2_tunew *tunew)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	stwuct video_device *vdev = video_devdata(fiwe);
	int wet;

	if (tunew->index != 0)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(cxdev->tda9887, tunew, s_tunew, tunew);
	if (wet != 0)
		wetuwn wet;

	wet = v4w2_subdev_caww(cxdev->tunew, tunew, s_tunew, tunew);
	if (wet != 0)
		wetuwn wet;

	/*
	 * make suwe that cx25840 is in a cowwect TV / wadio mode,
	 * since cawws above may have changed it fow tunew / IF demod
	 */
	if (vdev->vfw_type == VFW_TYPE_VIDEO)
		v4w2_subdev_caww(cxdev->cx25840, video, s_std, cxdev->nowm);
	ewse
		v4w2_subdev_caww(cxdev->cx25840, tunew, s_wadio);

	wetuwn v4w2_subdev_caww(cxdev->cx25840, tunew, s_tunew, tunew);
}

static int cxusb_medion_g_fwequency(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fwequency *fweq)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	if (fweq->tunew != 0)
		wetuwn -EINVAW;

	wetuwn v4w2_subdev_caww(cxdev->tunew, tunew, g_fwequency, fweq);
}

static int cxusb_medion_s_fwequency(stwuct fiwe *fiwe, void *fh,
				    const stwuct v4w2_fwequency *fweq)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	stwuct video_device *vdev = video_devdata(fiwe);
	int wet;

	if (fweq->tunew != 0)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(cxdev->tda9887, tunew, s_fwequency, fweq);
	if (wet != 0)
		wetuwn wet;

	wet = v4w2_subdev_caww(cxdev->tunew, tunew, s_fwequency, fweq);
	if (wet != 0)
		wetuwn wet;

	/*
	 * make suwe that cx25840 is in a cowwect TV / wadio mode,
	 * since cawws above may have changed it fow tunew / IF demod
	 */
	if (vdev->vfw_type == VFW_TYPE_VIDEO)
		v4w2_subdev_caww(cxdev->cx25840, video, s_std, cxdev->nowm);
	ewse
		v4w2_subdev_caww(cxdev->cx25840, tunew, s_wadio);

	wetuwn v4w2_subdev_caww(cxdev->cx25840, tunew, s_fwequency, fweq);
}

static int cxusb_medion_g_std(stwuct fiwe *fiwe, void *fh,
			      v4w2_std_id *nowm)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	*nowm = cxdev->nowm;

	if (*nowm == V4W2_STD_UNKNOWN)
		wetuwn -ENODATA;

	wetuwn 0;
}

static int cxusb_medion_s_std(stwuct fiwe *fiwe, void *fh,
			      v4w2_std_id nowm)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	wetuwn cxusb_medion_set_nowm(cxdev, nowm);
}

static int cxusb_medion_quewystd(stwuct fiwe *fiwe, void *fh,
				 v4w2_std_id *nowm)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	v4w2_std_id nowm_mask;
	int wet;

	/*
	 * make suwe we don't have impwopew std bits set fow the TV tunew
	 * (couwd happen when no signaw was pwesent yet aftew weset)
	 */
	if (cxdev->input == 0)
		nowm_mask = V4W2_STD_PAW;
	ewse
		nowm_mask = V4W2_STD_AWW;

	wet = v4w2_subdev_caww(cxdev->cx25840, video, quewystd, nowm);
	if (wet != 0) {
		cxusb_vpwintk(dvbdev, OPS,
			      "cannot get detected standawd fow input %u\n",
			      (unsigned int)cxdev->input);
		wetuwn wet;
	}

	cxusb_vpwintk(dvbdev, OPS, "input %u detected standawd is %wx\n",
		      (unsigned int)cxdev->input, (unsigned wong)*nowm);
	*nowm &= nowm_mask;

	wetuwn 0;
}

static int cxusb_medion_wog_status(stwuct fiwe *fiwe, void *fh)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(fiwe);
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	v4w2_device_caww_aww(&cxdev->v4w2dev, 0, cowe, wog_status);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops cxusb_video_ioctw = {
	.vidioc_quewycap = cxusb_medion_v_quewycap,
	.vidioc_enum_fmt_vid_cap = cxusb_medion_v_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = cxusb_medion_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = cxusb_medion_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = cxusb_medion_twy_fmt_vid_cap,
	.vidioc_enum_input = cxusb_medion_enum_input,
	.vidioc_g_input = cxusb_medion_g_input,
	.vidioc_s_input = cxusb_medion_s_input,
	.vidioc_g_tunew = cxusb_medion_g_tunew,
	.vidioc_s_tunew = cxusb_medion_s_tunew,
	.vidioc_g_fwequency = cxusb_medion_g_fwequency,
	.vidioc_s_fwequency = cxusb_medion_s_fwequency,
	.vidioc_g_std = cxusb_medion_g_std,
	.vidioc_s_std = cxusb_medion_s_std,
	.vidioc_quewystd = cxusb_medion_quewystd,
	.vidioc_wog_status = cxusb_medion_wog_status,
	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff
};

static const stwuct v4w2_ioctw_ops cxusb_wadio_ioctw = {
	.vidioc_quewycap = cxusb_medion_v_quewycap,
	.vidioc_g_tunew = cxusb_medion_g_tunew,
	.vidioc_s_tunew = cxusb_medion_s_tunew,
	.vidioc_g_fwequency = cxusb_medion_g_fwequency,
	.vidioc_s_fwequency = cxusb_medion_s_fwequency,
	.vidioc_wog_status = cxusb_medion_wog_status
};

/*
 * in pwincipwe, this shouwd be const, but s_io_pin_config is decwawed
 * to take non-const, and gcc compwains
 */
static stwuct v4w2_subdev_io_pin_config cxusub_medion_pin_config[] = {
	{ .pin = CX25840_PIN_DVAWID_PWGM0, .function = CX25840_PAD_DEFAUWT,
	  .stwength = CX25840_PIN_DWIVE_MEDIUM },
	{ .pin = CX25840_PIN_PWW_CWK_PWGM7, .function = CX25840_PAD_AUX_PWW },
	{ .pin = CX25840_PIN_HWESET_PWGM2, .function = CX25840_PAD_ACTIVE,
	  .stwength = CX25840_PIN_DWIVE_MEDIUM }
};

int cxusb_medion_anawog_init(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	u8 tunew_anawog_msg_data[] = { 0x9c, 0x60, 0x85, 0x54 };
	stwuct i2c_msg tunew_anawog_msg = { .addw = 0x61, .fwags = 0,
					    .buf = tunew_anawog_msg_data,
					    .wen =
					    sizeof(tunew_anawog_msg_data) };
	stwuct v4w2_subdev_fowmat subfmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	/* switch tunew to anawog mode so IF demod wiww become accessibwe */
	wet = i2c_twansfew(&dvbdev->i2c_adap, &tunew_anawog_msg, 1);
	if (wet != 1)
		dev_wawn(&dvbdev->udev->dev,
			 "tunew anawog switch faiwed (%d)\n", wet);

	/*
	 * cx25840 might have wost powew duwing mode switching so we need
	 * to set it again
	 */
	wet = v4w2_subdev_caww(cxdev->cx25840, cowe, weset, 0);
	if (wet != 0)
		dev_wawn(&dvbdev->udev->dev,
			 "cx25840 weset faiwed (%d)\n", wet);

	wet = v4w2_subdev_caww(cxdev->cx25840, video, s_wouting,
			       CX25840_COMPOSITE1, 0, 0);
	if (wet != 0)
		dev_wawn(&dvbdev->udev->dev,
			 "cx25840 initiaw input setting faiwed (%d)\n", wet);

	/* composite */
	cxdev->input = 1;
	cxdev->videodev->tvnowms = V4W2_STD_AWW;
	cxdev->nowm = V4W2_STD_PAW;

	/* TODO: setup audio sampwes insewtion */

	wet = v4w2_subdev_caww(cxdev->cx25840, cowe, s_io_pin_config,
			       AWWAY_SIZE(cxusub_medion_pin_config),
			       cxusub_medion_pin_config);
	if (wet != 0)
		dev_wawn(&dvbdev->udev->dev,
			 "cx25840 pin config faiwed (%d)\n", wet);

	/* make suwe that we awen't in wadio mode */
	v4w2_subdev_caww(cxdev->tda9887, video, s_std, cxdev->nowm);
	v4w2_subdev_caww(cxdev->tunew, video, s_std, cxdev->nowm);
	v4w2_subdev_caww(cxdev->cx25840, video, s_std, cxdev->nowm);

	subfmt.fowmat.width = cxdev->width;
	subfmt.fowmat.height = cxdev->height;
	subfmt.fowmat.code = MEDIA_BUS_FMT_FIXED;
	subfmt.fowmat.fiewd = V4W2_FIEWD_SEQ_TB;
	subfmt.fowmat.cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	wet = v4w2_subdev_caww(cxdev->cx25840, pad, set_fmt, NUWW, &subfmt);
	if (wet != 0)
		dev_wawn(&dvbdev->udev->dev,
			 "cx25840 fowmat set faiwed (%d)\n", wet);

	if (wet == 0) {
		cxdev->width = subfmt.fowmat.width;
		cxdev->height = subfmt.fowmat.height;
	}

	wetuwn 0;
}

static int cxusb_videowadio_open(stwuct fiwe *f)
{
	stwuct dvb_usb_device *dvbdev = video_dwvdata(f);
	int wet;

	/*
	 * no wocking needed since this caww onwy modifies anawog
	 * state if thewe awe no othew anawog handwes cuwwenwy
	 * opened so ops done via them cannot cweate a confwict
	 */
	wet = cxusb_medion_get(dvbdev, CXUSB_OPEN_ANAWOG);
	if (wet != 0)
		wetuwn wet;

	wet = v4w2_fh_open(f);
	if (wet != 0)
		goto wet_wewease;

	cxusb_vpwintk(dvbdev, OPS, "got open\n");

	wetuwn 0;

wet_wewease:
	cxusb_medion_put(dvbdev);

	wetuwn wet;
}

static int cxusb_videowadio_wewease(stwuct fiwe *f)
{
	stwuct video_device *vdev = video_devdata(f);
	stwuct dvb_usb_device *dvbdev = video_dwvdata(f);
	int wet;

	cxusb_vpwintk(dvbdev, OPS, "got wewease\n");

	if (vdev->vfw_type == VFW_TYPE_VIDEO)
		wet = vb2_fop_wewease(f);
	ewse
		wet = v4w2_fh_wewease(f);

	cxusb_medion_put(dvbdev);

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations cxusb_video_fops = {
	.ownew = THIS_MODUWE,
	.wead = vb2_fop_wead,
	.poww = vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = vb2_fop_mmap,
	.open = cxusb_videowadio_open,
	.wewease = cxusb_videowadio_wewease
};

static const stwuct v4w2_fiwe_opewations cxusb_wadio_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = cxusb_videowadio_open,
	.wewease = cxusb_videowadio_wewease
};

static void cxusb_medion_v4w2_wewease(stwuct v4w2_device *v4w2_dev)
{
	stwuct cxusb_medion_dev *cxdev =
		containew_of(v4w2_dev, stwuct cxusb_medion_dev, v4w2dev);
	stwuct dvb_usb_device *dvbdev = cxdev->dvbdev;

	cxusb_vpwintk(dvbdev, OPS, "v4w2 device wewease\n");

	v4w2_device_unwegistew(&cxdev->v4w2dev);

	mutex_destwoy(&cxdev->dev_wock);

	whiwe (compwetion_done(&cxdev->v4w2_wewease))
		scheduwe();

	compwete(&cxdev->v4w2_wewease);
}

static void cxusb_medion_videodev_wewease(stwuct video_device *vdev)
{
	stwuct dvb_usb_device *dvbdev = video_get_dwvdata(vdev);

	cxusb_vpwintk(dvbdev, OPS, "video device wewease\n");

	video_device_wewease(vdev);
}

static int cxusb_medion_wegistew_anawog_video(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;

	cxdev->videoqueue.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	cxdev->videoqueue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_WEAD |
		VB2_DMABUF;
	cxdev->videoqueue.ops = &cxdev_video_qops;
	cxdev->videoqueue.mem_ops = &vb2_vmawwoc_memops;
	cxdev->videoqueue.dwv_pwiv = dvbdev;
	cxdev->videoqueue.buf_stwuct_size =
		sizeof(stwuct cxusb_medion_vbuffew);
	cxdev->videoqueue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	cxdev->videoqueue.min_queued_buffews = 6;
	cxdev->videoqueue.wock = &cxdev->dev_wock;

	wet = vb2_queue_init(&cxdev->videoqueue);
	if (wet) {
		dev_eww(&dvbdev->udev->dev,
			"video queue init faiwed, wet = %d\n", wet);
		wetuwn wet;
	}

	cxdev->videodev = video_device_awwoc();
	if (!cxdev->videodev) {
		dev_eww(&dvbdev->udev->dev, "video device awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	cxdev->videodev->device_caps = videocaps;
	cxdev->videodev->fops = &cxusb_video_fops;
	cxdev->videodev->v4w2_dev = &cxdev->v4w2dev;
	cxdev->videodev->queue = &cxdev->videoqueue;
	stwscpy(cxdev->videodev->name, "cxusb", sizeof(cxdev->videodev->name));
	cxdev->videodev->vfw_diw = VFW_DIW_WX;
	cxdev->videodev->ioctw_ops = &cxusb_video_ioctw;
	cxdev->videodev->tvnowms = V4W2_STD_AWW;
	cxdev->videodev->wewease = cxusb_medion_videodev_wewease;
	cxdev->videodev->wock = &cxdev->dev_wock;
	video_set_dwvdata(cxdev->videodev, dvbdev);

	wet = video_wegistew_device(cxdev->videodev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(&dvbdev->udev->dev,
			"video device wegistew faiwed, wet = %d\n", wet);
		goto wet_vwewease;
	}

	wetuwn 0;

wet_vwewease:
	video_device_wewease(cxdev->videodev);
	wetuwn wet;
}

static int cxusb_medion_wegistew_anawog_wadio(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;

	cxdev->wadiodev = video_device_awwoc();
	if (!cxdev->wadiodev) {
		dev_eww(&dvbdev->udev->dev, "wadio device awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	cxdev->wadiodev->device_caps = wadiocaps;
	cxdev->wadiodev->fops = &cxusb_wadio_fops;
	cxdev->wadiodev->v4w2_dev = &cxdev->v4w2dev;
	stwscpy(cxdev->wadiodev->name, "cxusb", sizeof(cxdev->wadiodev->name));
	cxdev->wadiodev->vfw_diw = VFW_DIW_WX;
	cxdev->wadiodev->ioctw_ops = &cxusb_wadio_ioctw;
	cxdev->wadiodev->wewease = video_device_wewease;
	cxdev->wadiodev->wock = &cxdev->dev_wock;
	video_set_dwvdata(cxdev->wadiodev, dvbdev);

	wet = video_wegistew_device(cxdev->wadiodev, VFW_TYPE_WADIO, -1);
	if (wet) {
		dev_eww(&dvbdev->udev->dev,
			"wadio device wegistew faiwed, wet = %d\n", wet);
		video_device_wewease(cxdev->wadiodev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cxusb_medion_wegistew_anawog_subdevs(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;
	stwuct tunew_setup tun_setup;

	/* attach cx25840 captuwe chip */
	cxdev->cx25840 = v4w2_i2c_new_subdev(&cxdev->v4w2dev,
					     &dvbdev->i2c_adap,
					     "cx25840", 0x44, NUWW);
	if (!cxdev->cx25840) {
		dev_eww(&dvbdev->udev->dev, "cx25840 not found\n");
		wetuwn -ENODEV;
	}

	/*
	 * Initiawize cx25840 chip by cawwing its subdevice init cowe op.
	 *
	 * This switches it into the genewic mode that disabwes some of
	 * ivtv-wewated hacks in the cx25840 dwivew whiwe awwowing setting
	 * of the chip video output configuwation (passed in the caww bewow
	 * as the wast awgument).
	 */
	wet = v4w2_subdev_caww(cxdev->cx25840, cowe, init,
			       CX25840_VCONFIG_FMT_BT656 |
			       CX25840_VCONFIG_WES_8BIT |
			       CX25840_VCONFIG_VBIWAW_DISABWED |
			       CX25840_VCONFIG_ANCDATA_DISABWED |
			       CX25840_VCONFIG_ACTIVE_COMPOSITE |
			       CX25840_VCONFIG_VAWID_ANDACTIVE |
			       CX25840_VCONFIG_HWESETW_NOWMAW |
			       CX25840_VCONFIG_CWKGATE_NONE |
			       CX25840_VCONFIG_DCMODE_DWOWDS);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"cx25840 init faiwed (%d)\n", wet);
		wetuwn wet;
	}

	/* attach anawog tunew */
	cxdev->tunew = v4w2_i2c_new_subdev(&cxdev->v4w2dev,
					   &dvbdev->i2c_adap,
					   "tunew", 0x61, NUWW);
	if (!cxdev->tunew) {
		dev_eww(&dvbdev->udev->dev, "tunew not found\n");
		wetuwn -ENODEV;
	}

	/* configuwe it */
	memset(&tun_setup, 0, sizeof(tun_setup));
	tun_setup.addw = 0x61;
	tun_setup.type = TUNEW_PHIWIPS_FMD1216ME_MK3;
	tun_setup.mode_mask = T_WADIO | T_ANAWOG_TV;
	v4w2_subdev_caww(cxdev->tunew, tunew, s_type_addw, &tun_setup);

	/* attach IF demod */
	cxdev->tda9887 = v4w2_i2c_new_subdev(&cxdev->v4w2dev,
					     &dvbdev->i2c_adap,
					     "tunew", 0x43, NUWW);
	if (!cxdev->tda9887) {
		dev_eww(&dvbdev->udev->dev, "tda9887 not found\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int cxusb_medion_wegistew_anawog(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;
	int wet;

	mutex_init(&cxdev->dev_wock);

	init_compwetion(&cxdev->v4w2_wewease);

	cxdev->v4w2dev.wewease = cxusb_medion_v4w2_wewease;

	wet = v4w2_device_wegistew(&dvbdev->udev->dev, &cxdev->v4w2dev);
	if (wet != 0) {
		dev_eww(&dvbdev->udev->dev,
			"V4W2 device wegistwation faiwed, wet = %d\n", wet);
		mutex_destwoy(&cxdev->dev_wock);
		wetuwn wet;
	}

	wet = cxusb_medion_wegistew_anawog_subdevs(dvbdev);
	if (wet)
		goto wet_unwegistew;

	INIT_WOWK(&cxdev->uwbwowk, cxusb_medion_v_compwete_wowk);
	INIT_WIST_HEAD(&cxdev->bufwist);

	cxdev->width = 320;
	cxdev->height = 240;

	wet = cxusb_medion_wegistew_anawog_video(dvbdev);
	if (wet)
		goto wet_unwegistew;

	wet = cxusb_medion_wegistew_anawog_wadio(dvbdev);
	if (wet)
		goto wet_vunweg;

	wetuwn 0;

wet_vunweg:
	vb2_video_unwegistew_device(cxdev->videodev);

wet_unwegistew:
	v4w2_device_put(&cxdev->v4w2dev);
	wait_fow_compwetion(&cxdev->v4w2_wewease);

	wetuwn wet;
}

void cxusb_medion_unwegistew_anawog(stwuct dvb_usb_device *dvbdev)
{
	stwuct cxusb_medion_dev *cxdev = dvbdev->pwiv;

	cxusb_vpwintk(dvbdev, OPS, "unwegistewing anawog\n");

	video_unwegistew_device(cxdev->wadiodev);
	vb2_video_unwegistew_device(cxdev->videodev);

	v4w2_device_put(&cxdev->v4w2dev);
	wait_fow_compwetion(&cxdev->v4w2_wewease);

	cxusb_vpwintk(dvbdev, OPS, "anawog unwegistewed\n");
}
