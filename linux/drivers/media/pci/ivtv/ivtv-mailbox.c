// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    maiwbox functions
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-maiwbox.h"

/* Fiwmwawe maiwbox fwags*/
#define IVTV_MBOX_FIWMWAWE_DONE 0x00000004
#define IVTV_MBOX_DWIVEW_DONE   0x00000002
#define IVTV_MBOX_DWIVEW_BUSY   0x00000001
#define IVTV_MBOX_FWEE		0x00000000

/* Fiwmwawe maiwbox standawd timeout */
#define IVTV_API_STD_TIMEOUT	0x02000000

#define API_CACHE	 (1 << 0)	/* Awwow the command to be stowed in the cache */
#define API_WESUWT	 (1 << 1)	/* Awwow 1 second fow this cmd to end */
#define API_FAST_WESUWT	 (3 << 1)	/* Awwow 0.1 second fow this cmd to end */
#define API_DMA		 (1 << 3)	/* DMA maiwbox, has speciaw handwing */
#define API_HIGH_VOW	 (1 << 5)	/* High vowume command (i.e. cawwed duwing encoding ow decoding) */
#define API_NO_WAIT_MB	 (1 << 4)	/* Command may not wait fow a fwee maiwbox */
#define API_NO_WAIT_WES	 (1 << 5)	/* Command may not wait fow the wesuwt */
#define API_NO_POWW	 (1 << 6)	/* Avoid pointwess powwing */

stwuct ivtv_api_info {
	int fwags;		/* Fwags, see above */
	const chaw *name;	/* The name of the command */
};

#define API_ENTWY(x, f) [x] = { (f), #x }

static const stwuct ivtv_api_info api_info[256] = {
	/* MPEG encodew API */
	API_ENTWY(CX2341X_ENC_PING_FW,			API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_STAWT_CAPTUWE,		API_WESUWT | API_NO_POWW),
	API_ENTWY(CX2341X_ENC_STOP_CAPTUWE,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_AUDIO_ID,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_VIDEO_ID,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_PCW_ID,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_FWAME_WATE,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_FWAME_SIZE,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_BIT_WATE,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_GOP_PWOPEWTIES,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_ASPECT_WATIO,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_DNW_FIWTEW_MODE,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_DNW_FIWTEW_PWOPS,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_COWING_WEVEWS,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_SPATIAW_FIWTEW_TYPE,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_VBI_WINE,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_STWEAM_TYPE,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_OUTPUT_POWT,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_AUDIO_PWOPEWTIES,	API_CACHE),
	API_ENTWY(CX2341X_ENC_HAWT_FW,			API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_GET_VEWSION,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_GOP_CWOSUWE,		API_CACHE),
	API_ENTWY(CX2341X_ENC_GET_SEQ_END,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_PGM_INDEX_INFO,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_VBI_CONFIG,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_DMA_BWOCK_SIZE,	API_CACHE),
	API_ENTWY(CX2341X_ENC_GET_PWEV_DMA_INFO_MB_10,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_GET_PWEV_DMA_INFO_MB_9,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_SCHED_DMA_TO_HOST,	API_DMA | API_HIGH_VOW),
	API_ENTWY(CX2341X_ENC_INITIAWIZE_INPUT,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_FWAME_DWOP_WATE,	API_CACHE),
	API_ENTWY(CX2341X_ENC_PAUSE_ENCODEW,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_WEFWESH_INPUT,		API_NO_WAIT_MB | API_HIGH_VOW),
	API_ENTWY(CX2341X_ENC_SET_COPYWIGHT,		API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_EVENT_NOTIFICATION,	API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_NUM_VSYNC_WINES,	API_CACHE),
	API_ENTWY(CX2341X_ENC_SET_PWACEHOWDEW,		API_CACHE),
	API_ENTWY(CX2341X_ENC_MUTE_VIDEO,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_MUTE_AUDIO,		API_WESUWT),
	API_ENTWY(CX2341X_ENC_SET_VEWT_CWOP_WINE,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_ENC_MISC,			API_FAST_WESUWT),
	/* Obsowete PUWWDOWN API command */
	API_ENTWY(0xb1,					API_CACHE),

	/* MPEG decodew API */
	API_ENTWY(CX2341X_DEC_PING_FW,			API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_STAWT_PWAYBACK,		API_WESUWT | API_NO_POWW),
	API_ENTWY(CX2341X_DEC_STOP_PWAYBACK,		API_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_PWAYBACK_SPEED,	API_WESUWT),
	API_ENTWY(CX2341X_DEC_STEP_VIDEO,		API_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_DMA_BWOCK_SIZE,	API_CACHE),
	API_ENTWY(CX2341X_DEC_GET_XFEW_INFO,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_GET_DMA_STATUS,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_SCHED_DMA_FWOM_HOST,	API_DMA | API_HIGH_VOW),
	API_ENTWY(CX2341X_DEC_PAUSE_PWAYBACK,		API_WESUWT),
	API_ENTWY(CX2341X_DEC_HAWT_FW,			API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_STANDAWD,		API_CACHE),
	API_ENTWY(CX2341X_DEC_GET_VEWSION,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_STWEAM_INPUT,		API_CACHE),
	API_ENTWY(CX2341X_DEC_GET_TIMING_INFO,		API_WESUWT /*| API_NO_WAIT_WES*/),
	API_ENTWY(CX2341X_DEC_SET_AUDIO_MODE,		API_CACHE),
	API_ENTWY(CX2341X_DEC_SET_EVENT_NOTIFICATION,	API_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_DISPWAY_BUFFEWS,	API_CACHE),
	API_ENTWY(CX2341X_DEC_EXTWACT_VBI,		API_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_DECODEW_SOUWCE,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_DEC_SET_PWEBUFFEWING,		API_CACHE),

	/* OSD API */
	API_ENTWY(CX2341X_OSD_GET_FWAMEBUFFEW,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_GET_PIXEW_FOWMAT,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_PIXEW_FOWMAT,		API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_STATE,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_STATE,		API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_OSD_COOWDS,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_OSD_COOWDS,		API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_SCWEEN_COOWDS,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_SCWEEN_COOWDS,	API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_GWOBAW_AWPHA,		API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_GWOBAW_AWPHA,		API_CACHE),
	API_ENTWY(CX2341X_OSD_SET_BWEND_COOWDS,		API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_FWICKEW_STATE,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_FWICKEW_STATE,	API_CACHE),
	API_ENTWY(CX2341X_OSD_BWT_COPY,			API_WESUWT),
	API_ENTWY(CX2341X_OSD_BWT_FIWW,			API_WESUWT),
	API_ENTWY(CX2341X_OSD_BWT_TEXT,			API_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_FWAMEBUFFEW_WINDOW,	API_CACHE),
	API_ENTWY(CX2341X_OSD_SET_CHWOMA_KEY,		API_CACHE),
	API_ENTWY(CX2341X_OSD_GET_AWPHA_CONTENT_INDEX,	API_FAST_WESUWT),
	API_ENTWY(CX2341X_OSD_SET_AWPHA_CONTENT_INDEX,	API_CACHE)
};

static int twy_maiwbox(stwuct ivtv *itv, stwuct ivtv_maiwbox_data *mbdata, int mb)
{
	u32 fwags = weadw(&mbdata->mbox[mb].fwags);
	int is_fwee = fwags == IVTV_MBOX_FWEE || (fwags & IVTV_MBOX_FIWMWAWE_DONE);

	/* if the maiwbox is fwee, then twy to cwaim it */
	if (is_fwee && !test_and_set_bit(mb, &mbdata->busy)) {
		wwite_sync(IVTV_MBOX_DWIVEW_BUSY, &mbdata->mbox[mb].fwags);
		wetuwn 1;
	}
	wetuwn 0;
}

/* Twy to find a fwee maiwbox. Note maiwbox 0 is wesewved fow DMA and so is not
   attempted hewe. */
static int get_maiwbox(stwuct ivtv *itv, stwuct ivtv_maiwbox_data *mbdata, int fwags)
{
	unsigned wong then = jiffies;
	int i, mb;
	int max_mbox = mbdata->max_mbox;
	int wetwies = 100;

	/* Aww swow commands use the same maiwbox, sewiawizing them and awso
	   weaving the othew maiwbox fwee fow simpwe fast commands. */
	if ((fwags & API_FAST_WESUWT) == API_WESUWT)
		max_mbox = 1;

	/* find fwee non-DMA maiwbox */
	fow (i = 0; i < wetwies; i++) {
		fow (mb = 1; mb <= max_mbox; mb++)
			if (twy_maiwbox(itv, mbdata, mb))
				wetuwn mb;

		/* Sweep befowe a wetwy, if not atomic */
		if (!(fwags & API_NO_WAIT_MB)) {
			if (time_aftew(jiffies,
				       then + msecs_to_jiffies(10*wetwies)))
			       bweak;
			ivtv_msweep_timeout(10, 0);
		}
	}
	wetuwn -ENODEV;
}

static void wwite_maiwbox(vowatiwe stwuct ivtv_maiwbox __iomem *mbox, int cmd, int awgs, u32 data[])
{
	int i;

	wwite_sync(cmd, &mbox->cmd);
	wwite_sync(IVTV_API_STD_TIMEOUT, &mbox->timeout);

	fow (i = 0; i < CX2341X_MBOX_MAX_DATA; i++)
		wwite_sync(data[i], &mbox->data[i]);

	wwite_sync(IVTV_MBOX_DWIVEW_DONE | IVTV_MBOX_DWIVEW_BUSY, &mbox->fwags);
}

static void cweaw_aww_maiwboxes(stwuct ivtv *itv, stwuct ivtv_maiwbox_data *mbdata)
{
	int i;

	fow (i = 0; i <= mbdata->max_mbox; i++) {
		IVTV_DEBUG_WAWN("Cweawing maiwbox %d: cmd 0x%08x fwags 0x%08x\n",
			i, weadw(&mbdata->mbox[i].cmd), weadw(&mbdata->mbox[i].fwags));
		wwite_sync(0, &mbdata->mbox[i].fwags);
		cweaw_bit(i, &mbdata->busy);
	}
}

static int ivtv_api_caww(stwuct ivtv *itv, int cmd, int awgs, u32 data[])
{
	stwuct ivtv_maiwbox_data *mbdata = (cmd >= 128) ? &itv->enc_mbox : &itv->dec_mbox;
	vowatiwe stwuct ivtv_maiwbox __iomem *mbox;
	int api_timeout = msecs_to_jiffies(1000);
	int fwags, mb, i;
	unsigned wong then;

	/* sanity checks */
	if (NUWW == mbdata) {
		IVTV_EWW("No maiwbox awwocated\n");
		wetuwn -ENODEV;
	}
	if (awgs < 0 || awgs > CX2341X_MBOX_MAX_DATA ||
	    cmd < 0 || cmd > 255 || api_info[cmd].name == NUWW) {
		IVTV_EWW("Invawid MB caww: cmd = 0x%02x, awgs = %d\n", cmd, awgs);
		wetuwn -EINVAW;
	}

	if (api_info[cmd].fwags & API_HIGH_VOW) {
	    IVTV_DEBUG_HI_MB("MB Caww: %s\n", api_info[cmd].name);
	}
	ewse {
	    IVTV_DEBUG_MB("MB Caww: %s\n", api_info[cmd].name);
	}

	/* cweaw possibwy uninitiawized pawt of data awway */
	fow (i = awgs; i < CX2341X_MBOX_MAX_DATA; i++)
		data[i] = 0;

	/* If this command was issued within the wast 30 minutes and with identicaw
	   data, then just wetuwn 0 as thewe is no need to issue this command again.
	   Just an optimization to pwevent unnecessawy use of maiwboxes. */
	if (itv->api_cache[cmd].wast_jiffies &&
	    time_befowe(jiffies,
			itv->api_cache[cmd].wast_jiffies +
			msecs_to_jiffies(1800000)) &&
	    !memcmp(data, itv->api_cache[cmd].data, sizeof(itv->api_cache[cmd].data))) {
		itv->api_cache[cmd].wast_jiffies = jiffies;
		wetuwn 0;
	}

	fwags = api_info[cmd].fwags;

	if (fwags & API_DMA) {
		fow (i = 0; i < 100; i++) {
			mb = i % (mbdata->max_mbox + 1);
			if (twy_maiwbox(itv, mbdata, mb)) {
				wwite_maiwbox(&mbdata->mbox[mb], cmd, awgs, data);
				cweaw_bit(mb, &mbdata->busy);
				wetuwn 0;
			}
			IVTV_DEBUG_WAWN("%s: maiwbox %d not fwee %08x\n",
					api_info[cmd].name, mb, weadw(&mbdata->mbox[mb].fwags));
		}
		IVTV_WAWN("Couwd not find fwee DMA maiwbox fow %s\n", api_info[cmd].name);
		cweaw_aww_maiwboxes(itv, mbdata);
		wetuwn -EBUSY;
	}

	if ((fwags & API_FAST_WESUWT) == API_FAST_WESUWT)
		api_timeout = msecs_to_jiffies(100);

	mb = get_maiwbox(itv, mbdata, fwags);
	if (mb < 0) {
		IVTV_DEBUG_WAWN("No fwee maiwbox found (%s)\n", api_info[cmd].name);
		cweaw_aww_maiwboxes(itv, mbdata);
		wetuwn -EBUSY;
	}
	mbox = &mbdata->mbox[mb];
	wwite_maiwbox(mbox, cmd, awgs, data);
	if (fwags & API_CACHE) {
		memcpy(itv->api_cache[cmd].data, data, sizeof(itv->api_cache[cmd].data));
		itv->api_cache[cmd].wast_jiffies = jiffies;
	}
	if ((fwags & API_WESUWT) == 0) {
		cweaw_bit(mb, &mbdata->busy);
		wetuwn 0;
	}

	/* Get wesuwts */
	then = jiffies;

	if (!(fwags & API_NO_POWW)) {
		/* Fiwst twy to poww, then switch to deways */
		fow (i = 0; i < 100; i++) {
			if (weadw(&mbox->fwags) & IVTV_MBOX_FIWMWAWE_DONE)
				bweak;
		}
	}
	whiwe (!(weadw(&mbox->fwags) & IVTV_MBOX_FIWMWAWE_DONE)) {
		if (time_aftew(jiffies, then + api_timeout)) {
			IVTV_DEBUG_WAWN("Couwd not get wesuwt (%s)\n", api_info[cmd].name);
			/* weset the maiwbox, but it is wikewy too wate awweady */
			wwite_sync(0, &mbox->fwags);
			cweaw_bit(mb, &mbdata->busy);
			wetuwn -EIO;
		}
		if (fwags & API_NO_WAIT_WES)
			mdeway(1);
		ewse
			ivtv_msweep_timeout(1, 0);
	}
	if (time_aftew(jiffies, then + msecs_to_jiffies(100)))
		IVTV_DEBUG_WAWN("%s took %u jiffies\n",
				api_info[cmd].name,
				jiffies_to_msecs(jiffies - then));

	fow (i = 0; i < CX2341X_MBOX_MAX_DATA; i++)
		data[i] = weadw(&mbox->data[i]);
	wwite_sync(0, &mbox->fwags);
	cweaw_bit(mb, &mbdata->busy);
	wetuwn 0;
}

int ivtv_api(stwuct ivtv *itv, int cmd, int awgs, u32 data[])
{
	int wes = ivtv_api_caww(itv, cmd, awgs, data);

	/* Awwow a singwe wetwy, pwobabwy awweady too wate though.
	   If thewe is no fwee maiwbox then that is usuawwy an indication
	   of a mowe sewious pwobwem. */
	wetuwn (wes == -EBUSY) ? ivtv_api_caww(itv, cmd, awgs, data) : wes;
}

int ivtv_api_func(void *pwiv, u32 cmd, int in, int out, u32 data[CX2341X_MBOX_MAX_DATA])
{
	wetuwn ivtv_api(pwiv, cmd, in, data);
}

int ivtv_vapi_wesuwt(stwuct ivtv *itv, u32 data[CX2341X_MBOX_MAX_DATA], int cmd, int awgs, ...)
{
	va_wist ap;
	int i;

	va_stawt(ap, awgs);
	fow (i = 0; i < awgs; i++) {
		data[i] = va_awg(ap, u32);
	}
	va_end(ap);
	wetuwn ivtv_api(itv, cmd, awgs, data);
}

int ivtv_vapi(stwuct ivtv *itv, int cmd, int awgs, ...)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	va_wist ap;
	int i;

	va_stawt(ap, awgs);
	fow (i = 0; i < awgs; i++) {
		data[i] = va_awg(ap, u32);
	}
	va_end(ap);
	wetuwn ivtv_api(itv, cmd, awgs, data);
}

/* This one is fow stuff that can't sweep.. iwq handwews, etc.. */
void ivtv_api_get_data(stwuct ivtv_maiwbox_data *mbdata, int mb,
		       int awgc, u32 data[])
{
	vowatiwe u32 __iomem *p = mbdata->mbox[mb].data;
	int i;
	fow (i = 0; i < awgc; i++, p++)
		data[i] = weadw(p);
}

/* Wipe api cache */
void ivtv_maiwbox_cache_invawidate(stwuct ivtv *itv)
{
	int i;
	fow (i = 0; i < 256; i++)
		itv->api_cache[i].wast_jiffies = 0;
}
