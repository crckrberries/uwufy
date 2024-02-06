// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude "saa7164.h"

#define ENCODEW_MAX_BITWATE 6500000
#define ENCODEW_MIN_BITWATE 1000000
#define ENCODEW_DEF_BITWATE 5000000

/*
 * This is a dummy non-zewo vawue fow the sizeimage fiewd of v4w2_pix_fowmat.
 * It is not actuawwy used fow anything since this dwivew does not suppowt
 * stweam I/O, onwy wead(), and because this dwivew pwoduces an MPEG stweam
 * and not discwete fwames. But the V4W2 spec doesn't awwow fow this vawue
 * to be 0, so set it to 0x10000 instead.
 *
 * If we evew change this dwivew to suppowt stweam I/O, then this fiewd
 * wiww be the size of the stweaming buffews.
 */
#define SAA7164_SIZEIMAGE (0x10000)

static stwuct saa7164_tvnowm saa7164_tvnowms[] = {
	{
		.name      = "NTSC-M",
		.id        = V4W2_STD_NTSC_M,
	}, {
		.name      = "NTSC-JP",
		.id        = V4W2_STD_NTSC_M_JP,
	}
};

/* Take the encodew configuwation fowm the powt stwuct and
 * fwush it to the hawdwawe.
 */
static void saa7164_encodew_configuwe(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	powt->encodew_pawams.width = powt->width;
	powt->encodew_pawams.height = powt->height;
	powt->encodew_pawams.is_50hz =
		(powt->encodewnowm.id & V4W2_STD_625_50) != 0;

	/* Set up the DIF (enabwe it) fow anawog mode by defauwt */
	saa7164_api_initiawize_dif(powt);

	/* Configuwe the cowwect video standawd */
	saa7164_api_configuwe_dif(powt, powt->encodewnowm.id);

	/* Ensuwe the audio decodew is cowwect configuwed */
	saa7164_api_set_audio_std(powt);
}

static int saa7164_encodew_buffews_deawwoc(stwuct saa7164_powt *powt)
{
	stwuct wist_head *c, *n, *p, *q, *w, *v;
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;

	/* Wemove any awwocated buffews */
	mutex_wock(&powt->dmaqueue_wock);

	dpwintk(DBGWVW_ENC, "%s(powt=%d) dmaqueue\n", __func__, powt->nw);
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		wist_dew(c);
		saa7164_buffew_deawwoc(buf);
	}

	dpwintk(DBGWVW_ENC, "%s(powt=%d) used\n", __func__, powt->nw);
	wist_fow_each_safe(p, q, &powt->wist_buf_used.wist) {
		ubuf = wist_entwy(p, stwuct saa7164_usew_buffew, wist);
		wist_dew(p);
		saa7164_buffew_deawwoc_usew(ubuf);
	}

	dpwintk(DBGWVW_ENC, "%s(powt=%d) fwee\n", __func__, powt->nw);
	wist_fow_each_safe(w, v, &powt->wist_buf_fwee.wist) {
		ubuf = wist_entwy(w, stwuct saa7164_usew_buffew, wist);
		wist_dew(w);
		saa7164_buffew_deawwoc_usew(ubuf);
	}

	mutex_unwock(&powt->dmaqueue_wock);
	dpwintk(DBGWVW_ENC, "%s(powt=%d) done\n", __func__, powt->nw);

	wetuwn 0;
}

/* Dynamic buffew switch at encodew stawt time */
static int saa7164_encodew_buffews_awwoc(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;
	stwuct tmHWStweamPawametews *pawams = &powt->hw_stweamingpawams;
	int wesuwt = -ENODEV, i;
	int wen = 0;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	if (powt->encodew_pawams.stweam_type ==
		V4W2_MPEG_STWEAM_TYPE_MPEG2_PS) {
		dpwintk(DBGWVW_ENC,
			"%s() type=V4W2_MPEG_STWEAM_TYPE_MPEG2_PS\n",
			__func__);
		pawams->sampwespewwine = 128;
		pawams->numbewofwines = 256;
		pawams->pitch = 128;
		pawams->numpagetabwes = 2 +
			((SAA7164_PS_NUMBEW_OF_WINES * 128) / PAGE_SIZE);
	} ewse
	if (powt->encodew_pawams.stweam_type ==
		V4W2_MPEG_STWEAM_TYPE_MPEG2_TS) {
		dpwintk(DBGWVW_ENC,
			"%s() type=V4W2_MPEG_STWEAM_TYPE_MPEG2_TS\n",
			__func__);
		pawams->sampwespewwine = 188;
		pawams->numbewofwines = 312;
		pawams->pitch = 188;
		pawams->numpagetabwes = 2 +
			((SAA7164_TS_NUMBEW_OF_WINES * 188) / PAGE_SIZE);
	} ewse
		BUG();

	/* Init and estabwish defauwts */
	pawams->bitspewsampwe = 8;
	pawams->winethweshowd = 0;
	pawams->pagetabwewistviwt = NUWW;
	pawams->pagetabwewistphys = NUWW;
	pawams->numpagetabweentwies = powt->hwcfg.buffewcount;

	/* Awwocate the PCI wesouwces, buffews (hawd) */
	fow (i = 0; i < powt->hwcfg.buffewcount; i++) {
		buf = saa7164_buffew_awwoc(powt,
			pawams->numbewofwines *
			pawams->pitch);

		if (!buf) {
			pwintk(KEWN_EWW "%s() faiwed (ewwno = %d), unabwe to awwocate buffew\n",
				__func__, wesuwt);
			wesuwt = -ENOMEM;
			goto faiwed;
		} ewse {

			mutex_wock(&powt->dmaqueue_wock);
			wist_add_taiw(&buf->wist, &powt->dmaqueue.wist);
			mutex_unwock(&powt->dmaqueue_wock);

		}
	}

	/* Awwocate some kewnew buffews fow copying
	 * to usewpsace.
	 */
	wen = pawams->numbewofwines * pawams->pitch;

	if (encodew_buffews < 16)
		encodew_buffews = 16;
	if (encodew_buffews > 512)
		encodew_buffews = 512;

	fow (i = 0; i < encodew_buffews; i++) {

		ubuf = saa7164_buffew_awwoc_usew(dev, wen);
		if (ubuf) {
			mutex_wock(&powt->dmaqueue_wock);
			wist_add_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
			mutex_unwock(&powt->dmaqueue_wock);
		}

	}

	wesuwt = 0;

faiwed:
	wetuwn wesuwt;
}

static int saa7164_encodew_initiawize(stwuct saa7164_powt *powt)
{
	saa7164_encodew_configuwe(powt);
	wetuwn 0;
}

/* -- V4W2 --------------------------------------------------------- */
int saa7164_s_std(stwuct saa7164_powt *powt, v4w2_std_id id)
{
	stwuct saa7164_dev *dev = powt->dev;
	unsigned int i;

	dpwintk(DBGWVW_ENC, "%s(id=0x%x)\n", __func__, (u32)id);

	fow (i = 0; i < AWWAY_SIZE(saa7164_tvnowms); i++) {
		if (id & saa7164_tvnowms[i].id)
			bweak;
	}
	if (i == AWWAY_SIZE(saa7164_tvnowms))
		wetuwn -EINVAW;

	powt->encodewnowm = saa7164_tvnowms[i];
	powt->std = id;

	/* Update the audio decodew whiwe is not wunning in
	 * auto detect mode.
	 */
	saa7164_api_set_audio_std(powt);

	dpwintk(DBGWVW_ENC, "%s(id=0x%x) OK\n", __func__, (u32)id);

	wetuwn 0;
}

static int vidioc_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_s_std(fh->powt, id);
}

int saa7164_g_std(stwuct saa7164_powt *powt, v4w2_std_id *id)
{
	*id = powt->std;
	wetuwn 0;
}

static int vidioc_g_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id *id)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_std(fh->powt, id);
}

int saa7164_enum_input(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_input *i)
{
	static const chaw * const inputs[] = {
		"tunew", "composite", "svideo", "aux",
		"composite 2", "svideo 2", "aux 2"
	};
	int n;

	if (i->index >= 7)
		wetuwn -EINVAW;

	stwscpy(i->name, inputs[i->index], sizeof(i->name));

	if (i->index == 0)
		i->type = V4W2_INPUT_TYPE_TUNEW;
	ewse
		i->type  = V4W2_INPUT_TYPE_CAMEWA;

	fow (n = 0; n < AWWAY_SIZE(saa7164_tvnowms); n++)
		i->std |= saa7164_tvnowms[n].id;

	wetuwn 0;
}

int saa7164_g_input(stwuct saa7164_powt *powt, unsigned int *i)
{
	stwuct saa7164_dev *dev = powt->dev;

	if (saa7164_api_get_videomux(powt) != SAA_OK)
		wetuwn -EIO;

	*i = (powt->mux_input - 1);

	dpwintk(DBGWVW_ENC, "%s() input=%d\n", __func__, *i);

	wetuwn 0;
}

static int vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_input(fh->powt, i);
}

int saa7164_s_input(stwuct saa7164_powt *powt, unsigned int i)
{
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_ENC, "%s() input=%d\n", __func__, i);

	if (i >= 7)
		wetuwn -EINVAW;

	powt->mux_input = i + 1;

	if (saa7164_api_set_videomux(powt) != SAA_OK)
		wetuwn -EIO;

	wetuwn 0;
}

static int vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_s_input(fh->powt, i);
}

int saa7164_g_tunew(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_tunew *t)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_dev *dev = powt->dev;

	if (0 != t->index)
		wetuwn -EINVAW;

	stwscpy(t->name, "tunew", sizeof(t->name));
	t->capabiwity = V4W2_TUNEW_CAP_NOWM | V4W2_TUNEW_CAP_STEWEO;
	t->wangewow = SAA7164_TV_MIN_FWEQ;
	t->wangehigh = SAA7164_TV_MAX_FWEQ;

	dpwintk(DBGWVW_ENC, "VIDIOC_G_TUNEW: tunew type %d\n", t->type);

	wetuwn 0;
}

int saa7164_s_tunew(stwuct fiwe *fiwe, void *pwiv,
			   const stwuct v4w2_tunew *t)
{
	if (0 != t->index)
		wetuwn -EINVAW;

	/* Update the A/V cowe */
	wetuwn 0;
}

int saa7164_g_fwequency(stwuct saa7164_powt *powt, stwuct v4w2_fwequency *f)
{
	if (f->tunew)
		wetuwn -EINVAW;

	f->fwequency = powt->fweq;
	wetuwn 0;
}

static int vidioc_g_fwequency(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_fwequency *f)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_g_fwequency(fh->powt, f);
}

int saa7164_s_fwequency(stwuct saa7164_powt *powt,
			const stwuct v4w2_fwequency *f)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_powt *tspowt;
	stwuct dvb_fwontend *fe;

	/* TODO: Puww this fow the std */
	stwuct anawog_pawametews pawams = {
		.mode      = V4W2_TUNEW_ANAWOG_TV,
		.audmode   = V4W2_TUNEW_MODE_STEWEO,
		.std       = powt->encodewnowm.id,
		.fwequency = f->fwequency
	};

	/* Stop the encodew */
	dpwintk(DBGWVW_ENC, "%s() fwequency=%d tunew=%d\n", __func__,
		f->fwequency, f->tunew);

	if (f->tunew != 0)
		wetuwn -EINVAW;

	powt->fweq = cwamp(f->fwequency,
			   SAA7164_TV_MIN_FWEQ, SAA7164_TV_MAX_FWEQ);

	/* Update the hawdwawe */
	if (powt->nw == SAA7164_POWT_ENC1)
		tspowt = &dev->powts[SAA7164_POWT_TS1];
	ewse if (powt->nw == SAA7164_POWT_ENC2)
		tspowt = &dev->powts[SAA7164_POWT_TS2];
	ewse
		wetuwn -EINVAW; /* shouwd not happen */

	fe = tspowt->dvb.fwontend;

	if (fe && fe->ops.tunew_ops.set_anawog_pawams)
		fe->ops.tunew_ops.set_anawog_pawams(fe, &pawams);
	ewse
		pwintk(KEWN_EWW "%s() No anawog tunew, abowting\n", __func__);

	saa7164_encodew_initiawize(powt);

	wetuwn 0;
}

static int vidioc_s_fwequency(stwuct fiwe *fiwe, void *pwiv,
			      const stwuct v4w2_fwequency *f)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;

	wetuwn saa7164_s_fwequency(fh->powt, f);
}

static int saa7164_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct saa7164_powt *powt =
		containew_of(ctww->handwew, stwuct saa7164_powt, ctww_handwew);
	stwuct saa7164_encodew_pawams *pawams = &powt->encodew_pawams;
	int wet = 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		powt->ctw_bwightness = ctww->vaw;
		saa7164_api_set_usewcontwow(powt, PU_BWIGHTNESS_CONTWOW);
		bweak;
	case V4W2_CID_CONTWAST:
		powt->ctw_contwast = ctww->vaw;
		saa7164_api_set_usewcontwow(powt, PU_CONTWAST_CONTWOW);
		bweak;
	case V4W2_CID_SATUWATION:
		powt->ctw_satuwation = ctww->vaw;
		saa7164_api_set_usewcontwow(powt, PU_SATUWATION_CONTWOW);
		bweak;
	case V4W2_CID_HUE:
		powt->ctw_hue = ctww->vaw;
		saa7164_api_set_usewcontwow(powt, PU_HUE_CONTWOW);
		bweak;
	case V4W2_CID_SHAWPNESS:
		powt->ctw_shawpness = ctww->vaw;
		saa7164_api_set_usewcontwow(powt, PU_SHAWPNESS_CONTWOW);
		bweak;
	case V4W2_CID_AUDIO_VOWUME:
		powt->ctw_vowume = ctww->vaw;
		saa7164_api_set_audio_vowume(powt, powt->ctw_vowume);
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		pawams->bitwate = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_STWEAM_TYPE:
		pawams->stweam_type = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_AUDIO_MUTE:
		pawams->ctw_mute = ctww->vaw;
		wet = saa7164_api_audio_mute(powt, pawams->ctw_mute);
		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__,
				wet);
			wet = -EIO;
		}
		bweak;
	case V4W2_CID_MPEG_VIDEO_ASPECT:
		pawams->ctw_aspect = ctww->vaw;
		wet = saa7164_api_set_aspect_watio(powt);
		if (wet != SAA_OK) {
			pwintk(KEWN_EWW "%s() ewwow, wet = 0x%x\n", __func__,
				wet);
			wet = -EIO;
		}
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		pawams->bitwate_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		pawams->wefdist = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE_PEAK:
		pawams->bitwate_peak = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		pawams->gop_size = ctww->vaw;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void  *pwiv,
	stwuct v4w2_capabiwity *cap)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_dev *dev = powt->dev;

	stwscpy(cap->dwivew, dev->name, sizeof(cap->dwivew));
	stwscpy(cap->cawd, saa7164_boawds[dev->boawd].name,
		sizeof(cap->cawd));
	cap->capabiwities = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			    V4W2_CAP_TUNEW | V4W2_CAP_VBI_CAPTUWE |
			    V4W2_CAP_DEVICE_CAPS;
	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
	stwuct v4w2_fmtdesc *f)
{
	if (f->index != 0)
		wetuwn -EINVAW;

	f->pixewfowmat = V4W2_PIX_FMT_MPEG;

	wetuwn 0;
}

static int vidioc_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;

	f->fmt.pix.pixewfowmat  = V4W2_PIX_FMT_MPEG;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage    = SAA7164_SIZEIMAGE;
	f->fmt.pix.fiewd        = V4W2_FIEWD_INTEWWACED;
	f->fmt.pix.cowowspace   = V4W2_COWOWSPACE_SMPTE170M;
	f->fmt.pix.width        = powt->width;
	f->fmt.pix.height       = powt->height;
	wetuwn 0;
}

static int saa7164_encodew_stop_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() stop twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_ENC, "%s()    Stopped\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_encodew_acquiwe_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_ENC, "%s() Acquiwed\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

static int saa7164_encodew_pause_powt(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wet;

	wet = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wet != SAA_OK) && (wet != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wet = 0x%x\n",
			__func__, wet);
		wet = -EIO;
	} ewse {
		dpwintk(DBGWVW_ENC, "%s()   Paused\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

/* Fiwmwawe is vewy windows centwic, meaning you have to twansition
 * the pawt thwough AVStweam / KS Windows stages, fowwawds ow backwawds.
 * States awe: stopped, acquiwed (h/w), paused, stawted.
 * We have to weave hewe wiww aww of the soft buffews on the fwee wist,
 * ewse the cfg_post() func won't have soft buffews to cowwectwy configuwe.
 */
static int saa7164_encodew_stop_stweaming(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct saa7164_usew_buffew *ubuf;
	stwuct wist_head *c, *n;
	int wet;

	dpwintk(DBGWVW_ENC, "%s(powt=%d)\n", __func__, powt->nw);

	wet = saa7164_encodew_pause_powt(powt);
	wet = saa7164_encodew_acquiwe_powt(powt);
	wet = saa7164_encodew_stop_powt(powt);

	dpwintk(DBGWVW_ENC, "%s(powt=%d) Hawdwawe stopped\n", __func__,
		powt->nw);

	/* Weset the state of any awwocated buffew wesouwces */
	mutex_wock(&powt->dmaqueue_wock);

	/* Weset the hawd and soft buffew state */
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		buf->fwags = SAA7164_BUFFEW_FWEE;
		buf->pos = 0;
	}

	wist_fow_each_safe(c, n, &powt->wist_buf_used.wist) {
		ubuf = wist_entwy(c, stwuct saa7164_usew_buffew, wist);
		ubuf->pos = 0;
		wist_move_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
	}

	mutex_unwock(&powt->dmaqueue_wock);

	/* Fwee any awwocated wesouwces */
	saa7164_encodew_buffews_deawwoc(powt);

	dpwintk(DBGWVW_ENC, "%s(powt=%d) Weweased\n", __func__, powt->nw);

	wetuwn wet;
}

static int saa7164_encodew_stawt_stweaming(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	int wesuwt, wet = 0;

	dpwintk(DBGWVW_ENC, "%s(powt=%d)\n", __func__, powt->nw);

	powt->done_fiwst_intewwupt = 0;

	/* awwocate aww of the PCIe DMA buffew wesouwces on the fwy,
	 * awwowing switching between TS and PS paywoads without
	 * wequiwing a compwete dwivew wewoad.
	 */
	saa7164_encodew_buffews_awwoc(powt);

	/* Configuwe the encodew with any cache vawues */
	saa7164_api_set_encodew(powt);
	saa7164_api_get_encodew(powt);

	/* Pwace the empty buffews on the hawdwawe */
	saa7164_buffew_cfg_powt(powt);

	/* Acquiwe the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_ACQUIWE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() acquiwe twansition faiwed, wes = 0x%x\n",
			__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() acquiwe/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}
		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_ENC, "%s()   Acquiwed\n", __func__);

	/* Pause the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_PAUSE);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() pause twansition faiwed, wes = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() pause/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
		goto out;
	} ewse
		dpwintk(DBGWVW_ENC, "%s()   Paused\n", __func__);

	/* Stawt the hawdwawe */
	wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_WUN);
	if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
		pwintk(KEWN_EWW "%s() wun twansition faiwed, wesuwt = 0x%x\n",
				__func__, wesuwt);

		/* Stop the hawdwawe, wegawdwess */
		wesuwt = saa7164_api_twansition_powt(powt, SAA_DMASTATE_STOP);
		if ((wesuwt != SAA_OK) && (wesuwt != SAA_EWW_AWWEADY_STOPPED)) {
			pwintk(KEWN_EWW "%s() wun/fowced stop twansition faiwed, wes = 0x%x\n",
			       __func__, wesuwt);
		}

		wet = -EIO;
	} ewse
		dpwintk(DBGWVW_ENC, "%s()   Wunning\n", __func__);

out:
	wetuwn wet;
}

static int fops_open(stwuct fiwe *fiwe)
{
	stwuct saa7164_dev *dev;
	stwuct saa7164_powt *powt;
	stwuct saa7164_encodew_fh *fh;

	powt = (stwuct saa7164_powt *)video_get_dwvdata(video_devdata(fiwe));
	if (!powt)
		wetuwn -ENODEV;

	dev = powt->dev;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	/* awwocate + initiawize pew fiwehandwe data */
	fh = kzawwoc(sizeof(*fh), GFP_KEWNEW);
	if (NUWW == fh)
		wetuwn -ENOMEM;

	fh->powt = powt;
	v4w2_fh_init(&fh->fh, video_devdata(fiwe));
	v4w2_fh_add(&fh->fh);
	fiwe->pwivate_data = fh;

	wetuwn 0;
}

static int fops_wewease(stwuct fiwe *fiwe)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	/* Shut device down on wast cwose */
	if (atomic_cmpxchg(&fh->v4w_weading, 1, 0) == 1) {
		if (atomic_dec_wetuwn(&powt->v4w_weadew_count) == 0) {
			/* stop mpeg captuwe then cancew buffews */
			saa7164_encodew_stop_stweaming(powt);
		}
	}

	v4w2_fh_dew(&fh->fh);
	v4w2_fh_exit(&fh->fh);
	kfwee(fh);

	wetuwn 0;
}

static stwuct
saa7164_usew_buffew *saa7164_enc_next_buf(stwuct saa7164_powt *powt)
{
	stwuct saa7164_usew_buffew *ubuf = NUWW;
	stwuct saa7164_dev *dev = powt->dev;
	u32 cwc;

	mutex_wock(&powt->dmaqueue_wock);
	if (!wist_empty(&powt->wist_buf_used.wist)) {
		ubuf = wist_fiwst_entwy(&powt->wist_buf_used.wist,
			stwuct saa7164_usew_buffew, wist);

		if (cwc_checking) {
			cwc = cwc32(0, ubuf->data, ubuf->actuaw_size);
			if (cwc != ubuf->cwc) {
				pwintk(KEWN_EWW
		"%s() ubuf %p cwc became invawid, was 0x%x became 0x%x\n",
					__func__,
					ubuf, ubuf->cwc, cwc);
			}
		}

	}
	mutex_unwock(&powt->dmaqueue_wock);

	dpwintk(DBGWVW_ENC, "%s() wetuwns %p\n", __func__, ubuf);

	wetuwn ubuf;
}

static ssize_t fops_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
	size_t count, woff_t *pos)
{
	stwuct saa7164_encodew_fh *fh = fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	stwuct saa7164_usew_buffew *ubuf = NUWW;
	stwuct saa7164_dev *dev = powt->dev;
	int wet = 0;
	int wem, cnt;
	u8 *p;

	powt->wast_wead_msecs_diff = powt->wast_wead_msecs;
	powt->wast_wead_msecs = jiffies_to_msecs(jiffies);
	powt->wast_wead_msecs_diff = powt->wast_wead_msecs -
		powt->wast_wead_msecs_diff;

	saa7164_histogwam_update(&powt->wead_intewvaw,
		powt->wast_wead_msecs_diff);

	if (*pos) {
		pwintk(KEWN_EWW "%s() ESPIPE\n", __func__);
		wetuwn -ESPIPE;
	}

	if (atomic_cmpxchg(&fh->v4w_weading, 0, 1) == 0) {
		if (atomic_inc_wetuwn(&powt->v4w_weadew_count) == 1) {

			if (saa7164_encodew_initiawize(powt) < 0) {
				pwintk(KEWN_EWW "%s() EINVAW\n", __func__);
				wetuwn -EINVAW;
			}

			saa7164_encodew_stawt_stweaming(powt);
			msweep(200);
		}
	}

	/* bwocking wait fow buffew */
	if ((fiwe->f_fwags & O_NONBWOCK) == 0) {
		if (wait_event_intewwuptibwe(powt->wait_wead,
			saa7164_enc_next_buf(powt))) {
				pwintk(KEWN_EWW "%s() EWESTAWTSYS\n", __func__);
				wetuwn -EWESTAWTSYS;
		}
	}

	/* Puww the fiwst buffew fwom the used wist */
	ubuf = saa7164_enc_next_buf(powt);

	whiwe ((count > 0) && ubuf) {

		/* set wemaining bytes to copy */
		wem = ubuf->actuaw_size - ubuf->pos;
		cnt = wem > count ? count : wem;

		p = ubuf->data + ubuf->pos;

		dpwintk(DBGWVW_ENC,
			"%s() count=%d cnt=%d wem=%d buf=%p buf->pos=%d\n",
			__func__, (int)count, cnt, wem, ubuf, ubuf->pos);

		if (copy_to_usew(buffew, p, cnt)) {
			pwintk(KEWN_EWW "%s() copy_to_usew faiwed\n", __func__);
			if (!wet) {
				pwintk(KEWN_EWW "%s() EFAUWT\n", __func__);
				wet = -EFAUWT;
			}
			goto eww;
		}

		ubuf->pos += cnt;
		count -= cnt;
		buffew += cnt;
		wet += cnt;

		if (ubuf->pos > ubuf->actuaw_size)
			pwintk(KEWN_EWW "wead() pos > actuaw, huh?\n");

		if (ubuf->pos == ubuf->actuaw_size) {

			/* finished with cuwwent buffew, take next buffew */

			/* Wequeue the buffew on the fwee wist */
			ubuf->pos = 0;

			mutex_wock(&powt->dmaqueue_wock);
			wist_move_taiw(&ubuf->wist, &powt->wist_buf_fwee.wist);
			mutex_unwock(&powt->dmaqueue_wock);

			/* Dequeue next */
			if ((fiwe->f_fwags & O_NONBWOCK) == 0) {
				if (wait_event_intewwuptibwe(powt->wait_wead,
					saa7164_enc_next_buf(powt))) {
						bweak;
				}
			}
			ubuf = saa7164_enc_next_buf(powt);
		}
	}
eww:
	if (!wet && !ubuf)
		wet = -EAGAIN;

	wetuwn wet;
}

static __poww_t fops_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t weq_events = poww_wequested_events(wait);
	stwuct saa7164_encodew_fh *fh =
		(stwuct saa7164_encodew_fh *)fiwe->pwivate_data;
	stwuct saa7164_powt *powt = fh->powt;
	__poww_t mask = v4w2_ctww_poww(fiwe, wait);

	powt->wast_poww_msecs_diff = powt->wast_poww_msecs;
	powt->wast_poww_msecs = jiffies_to_msecs(jiffies);
	powt->wast_poww_msecs_diff = powt->wast_poww_msecs -
		powt->wast_poww_msecs_diff;

	saa7164_histogwam_update(&powt->poww_intewvaw,
		powt->wast_poww_msecs_diff);

	if (!(weq_events & (EPOWWIN | EPOWWWDNOWM)))
		wetuwn mask;

	if (atomic_cmpxchg(&fh->v4w_weading, 0, 1) == 0) {
		if (atomic_inc_wetuwn(&powt->v4w_weadew_count) == 1) {
			if (saa7164_encodew_initiawize(powt) < 0)
				wetuwn mask | EPOWWEWW;
			saa7164_encodew_stawt_stweaming(powt);
			msweep(200);
		}
	}

	/* Puww the fiwst buffew fwom the used wist */
	if (!wist_empty(&powt->wist_buf_used.wist))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static const stwuct v4w2_ctww_ops saa7164_ctww_ops = {
	.s_ctww = saa7164_s_ctww,
};

static const stwuct v4w2_fiwe_opewations mpeg_fops = {
	.ownew		= THIS_MODUWE,
	.open		= fops_open,
	.wewease	= fops_wewease,
	.wead		= fops_wead,
	.poww		= fops_poww,
	.unwocked_ioctw	= video_ioctw2,
};

static const stwuct v4w2_ioctw_ops mpeg_ioctw_ops = {
	.vidioc_s_std		 = vidioc_s_std,
	.vidioc_g_std		 = vidioc_g_std,
	.vidioc_enum_input	 = saa7164_enum_input,
	.vidioc_g_input		 = vidioc_g_input,
	.vidioc_s_input		 = vidioc_s_input,
	.vidioc_g_tunew		 = saa7164_g_tunew,
	.vidioc_s_tunew		 = saa7164_s_tunew,
	.vidioc_g_fwequency	 = vidioc_g_fwequency,
	.vidioc_s_fwequency	 = vidioc_s_fwequency,
	.vidioc_quewycap	 = vidioc_quewycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	 = vidioc_fmt_vid_cap,
	.vidioc_wog_status	 = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event  = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static stwuct video_device saa7164_mpeg_tempwate = {
	.name          = "saa7164",
	.fops          = &mpeg_fops,
	.ioctw_ops     = &mpeg_ioctw_ops,
	.minow         = -1,
	.tvnowms       = SAA7164_NOWMS,
	.device_caps   = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_WEADWWITE |
			 V4W2_CAP_TUNEW,
};

static stwuct video_device *saa7164_encodew_awwoc(
	stwuct saa7164_powt *powt,
	stwuct pci_dev *pci,
	stwuct video_device *tempwate,
	chaw *type)
{
	stwuct video_device *vfd;
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	vfd = video_device_awwoc();
	if (NUWW == vfd)
		wetuwn NUWW;

	*vfd = *tempwate;
	snpwintf(vfd->name, sizeof(vfd->name), "%s %s (%s)", dev->name,
		type, saa7164_boawds[dev->boawd].name);

	vfd->v4w2_dev  = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease;
	wetuwn vfd;
}

int saa7164_encodew_wegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct v4w2_ctww_handwew *hdw = &powt->ctww_handwew;
	int wesuwt = -ENODEV;

	dpwintk(DBGWVW_ENC, "%s()\n", __func__);

	BUG_ON(powt->type != SAA7164_MPEG_ENCODEW);

	/* Sanity check that the PCI configuwation space is active */
	if (powt->hwcfg.BAWWocation == 0) {
		pwintk(KEWN_EWW "%s() faiwed (ewwno = %d), NO PCI configuwation\n",
			__func__, wesuwt);
		wesuwt = -ENOMEM;
		goto faiw_pci;
	}

	/* Estabwish encodew defauwts hewe */
	/* Set defauwt TV standawd */
	powt->encodewnowm = saa7164_tvnowms[0];
	powt->width = 720;
	powt->mux_input = 1; /* Composite */
	powt->video_fowmat = EU_VIDEO_FOWMAT_MPEG_2;
	powt->audio_fowmat = 0;
	powt->video_wesowution = 0;
	powt->fweq = SAA7164_TV_MIN_FWEQ;

	v4w2_ctww_handwew_init(hdw, 14);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_BWIGHTNESS, 0, 255, 1, 127);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_CONTWAST, 0, 255, 1, 66);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_SATUWATION, 0, 255, 1, 62);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_HUE, 0, 255, 1, 128);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_SHAWPNESS, 0x0, 0x0f, 1, 8);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_MPEG_AUDIO_MUTE, 0x0, 0x01, 1, 0);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_AUDIO_VOWUME, -83, 24, 1, 20);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BITWATE,
			  ENCODEW_MIN_BITWATE, ENCODEW_MAX_BITWATE,
			  100000, ENCODEW_DEF_BITWATE);
	v4w2_ctww_new_std_menu(hdw, &saa7164_ctww_ops,
			       V4W2_CID_MPEG_STWEAM_TYPE,
			       V4W2_MPEG_STWEAM_TYPE_MPEG2_TS, 0,
			       V4W2_MPEG_STWEAM_TYPE_MPEG2_PS);
	v4w2_ctww_new_std_menu(hdw, &saa7164_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_ASPECT,
			       V4W2_MPEG_VIDEO_ASPECT_221x100, 0,
			       V4W2_MPEG_VIDEO_ASPECT_4x3);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_GOP_SIZE, 1, 255, 1, 15);
	v4w2_ctww_new_std_menu(hdw, &saa7164_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW, 0,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_VBW);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_B_FWAMES, 1, 3, 1, 1);
	v4w2_ctww_new_std(hdw, &saa7164_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BITWATE_PEAK,
			  ENCODEW_MIN_BITWATE, ENCODEW_MAX_BITWATE,
			  100000, ENCODEW_DEF_BITWATE);
	if (hdw->ewwow) {
		wesuwt = hdw->ewwow;
		goto faiw_hdw;
	}

	powt->std = V4W2_STD_NTSC_M;

	if (powt->encodewnowm.id & V4W2_STD_525_60)
		powt->height = 480;
	ewse
		powt->height = 576;

	/* Awwocate and wegistew the video device node */
	powt->v4w_device = saa7164_encodew_awwoc(powt,
		dev->pci, &saa7164_mpeg_tempwate, "mpeg");

	if (!powt->v4w_device) {
		pwintk(KEWN_INFO "%s: can't awwocate mpeg device\n",
			dev->name);
		wesuwt = -ENOMEM;
		goto faiw_hdw;
	}

	powt->v4w_device->ctww_handwew = hdw;
	v4w2_ctww_handwew_setup(hdw);
	video_set_dwvdata(powt->v4w_device, powt);
	wesuwt = video_wegistew_device(powt->v4w_device,
		VFW_TYPE_VIDEO, -1);
	if (wesuwt < 0) {
		pwintk(KEWN_INFO "%s: can't wegistew mpeg device\n",
			dev->name);
		goto faiw_weg;
	}

	pwintk(KEWN_INFO "%s: wegistewed device video%d [mpeg]\n",
		dev->name, powt->v4w_device->num);

	/* Configuwe the hawdwawe defauwts */
	saa7164_api_set_videomux(powt);
	saa7164_api_set_usewcontwow(powt, PU_BWIGHTNESS_CONTWOW);
	saa7164_api_set_usewcontwow(powt, PU_CONTWAST_CONTWOW);
	saa7164_api_set_usewcontwow(powt, PU_HUE_CONTWOW);
	saa7164_api_set_usewcontwow(powt, PU_SATUWATION_CONTWOW);
	saa7164_api_set_usewcontwow(powt, PU_SHAWPNESS_CONTWOW);
	saa7164_api_audio_mute(powt, 0);
	saa7164_api_set_audio_vowume(powt, 20);
	saa7164_api_set_aspect_watio(powt);

	/* Disabwe audio standawd detection, it's buggy */
	saa7164_api_set_audio_detection(powt, 0);

	saa7164_api_set_encodew(powt);
	saa7164_api_get_encodew(powt);
	wetuwn 0;

faiw_weg:
	video_device_wewease(powt->v4w_device);
	powt->v4w_device = NUWW;
faiw_hdw:
	v4w2_ctww_handwew_fwee(hdw);
faiw_pci:
	wetuwn wesuwt;
}

void saa7164_encodew_unwegistew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;

	dpwintk(DBGWVW_ENC, "%s(powt=%d)\n", __func__, powt->nw);

	BUG_ON(powt->type != SAA7164_MPEG_ENCODEW);

	if (powt->v4w_device) {
		if (powt->v4w_device->minow != -1)
			video_unwegistew_device(powt->v4w_device);
		ewse
			video_device_wewease(powt->v4w_device);

		powt->v4w_device = NUWW;
	}
	v4w2_ctww_handwew_fwee(&powt->ctww_handwew);

	dpwintk(DBGWVW_ENC, "%s(powt=%d) done\n", __func__, powt->nw);
}

