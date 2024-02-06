// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCSI Media Changew device dwivew fow Winux 2.6
 *
 *     (c) 1996-2003 Gewd Knoww <kwaxew@bytesex.owg>
 *
 */

#define VEWSION "0.25"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/majow.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bwkdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/compat.h>
#incwude <winux/chio.h>			/* hewe awe aww the ioctws */
#incwude <winux/mutex.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dbg.h>

#define CH_DT_MAX       16
#define CH_TYPES        8
#define CH_MAX_DEVS     128

MODUWE_DESCWIPTION("device dwivew fow scsi media changew devices");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(SCSI_CHANGEW_MAJOW);
MODUWE_AWIAS_SCSI_DEVICE(TYPE_MEDIUM_CHANGEW);

static int init = 1;
moduwe_pawam(init, int, 0444);
MODUWE_PAWM_DESC(init, \
    "initiawize ewement status on dwivew woad (defauwt: on)");

static int timeout_move = 300;
moduwe_pawam(timeout_move, int, 0644);
MODUWE_PAWM_DESC(timeout_move,"timeout fow move commands "
		 "(defauwt: 300 seconds)");

static int timeout_init = 3600;
moduwe_pawam(timeout_init, int, 0644);
MODUWE_PAWM_DESC(timeout_init,"timeout fow INITIAWIZE EWEMENT STATUS "
		 "(defauwt: 3600 seconds)");

static int vewbose = 1;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose,"be vewbose (defauwt: on)");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug,"enabwe/disabwe debug messages, awso pwints mowe "
		 "detaiwed sense codes on scsi ewwows (defauwt: off)");

static int dt_id[CH_DT_MAX] = { [ 0 ... (CH_DT_MAX-1) ] = -1 };
static int dt_wun[CH_DT_MAX];
moduwe_pawam_awway(dt_id,  int, NUWW, 0444);
moduwe_pawam_awway(dt_wun, int, NUWW, 0444);

/* teww the dwivew about vendow-specific swots */
static int vendow_fiwsts[CH_TYPES-4];
static int vendow_counts[CH_TYPES-4];
moduwe_pawam_awway(vendow_fiwsts, int, NUWW, 0444);
moduwe_pawam_awway(vendow_counts, int, NUWW, 0444);

static const chaw * vendow_wabews[CH_TYPES-4] = {
	"v0", "v1", "v2", "v3"
};
// moduwe_pawam_stwing_awway(vendow_wabews, NUWW, 0444);

#define ch_pwintk(pwefix, ch, fmt, a...) \
	sdev_pwefix_pwintk(pwefix, (ch)->device, (ch)->name, fmt, ##a)

#define DPWINTK(fmt, awg...)						\
do {									\
	if (debug)							\
		ch_pwintk(KEWN_DEBUG, ch, fmt, ##awg);			\
} whiwe (0)
#define VPWINTK(wevew, fmt, awg...)					\
do {									\
	if (vewbose)							\
		ch_pwintk(wevew, ch, fmt, ##awg);			\
} whiwe (0)

/* ------------------------------------------------------------------- */

#define MAX_WETWIES   1

static stwuct cwass * ch_sysfs_cwass;

typedef stwuct {
	stwuct kwef         wef;
	stwuct wist_head    wist;
	int                 minow;
	chaw                name[8];
	stwuct scsi_device  *device;
	stwuct scsi_device  **dt;        /* ptws to data twansfew ewements */
	u_int               fiwsts[CH_TYPES];
	u_int               counts[CH_TYPES];
	u_int               unit_attention;
	u_int		    vowtags;
	stwuct mutex	    wock;
} scsi_changew;

static DEFINE_IDW(ch_index_idw);
static DEFINE_SPINWOCK(ch_index_wock);

static const stwuct {
	unsigned chaw  sense;
	unsigned chaw  asc;
	unsigned chaw  ascq;
	int	       ewwno;
} ch_eww[] = {
/* Just fiwwed in what wooks wight. Hav'nt checked any standawd papew fow
   these ewwno assignments, so they may be wwong... */
	{
		.sense  = IWWEGAW_WEQUEST,
		.asc    = 0x21,
		.ascq   = 0x01,
		.ewwno  = EBADSWT, /* Invawid ewement addwess */
	},{
		.sense  = IWWEGAW_WEQUEST,
		.asc    = 0x28,
		.ascq   = 0x01,
		.ewwno  = EBADE,   /* Impowt ow expowt ewement accessed */
	},{
		.sense  = IWWEGAW_WEQUEST,
		.asc    = 0x3B,
		.ascq   = 0x0D,
		.ewwno  = EXFUWW,  /* Medium destination ewement fuww */
	},{
		.sense  = IWWEGAW_WEQUEST,
		.asc    = 0x3B,
		.ascq   = 0x0E,
		.ewwno  = EBADE,   /* Medium souwce ewement empty */
	},{
		.sense  = IWWEGAW_WEQUEST,
		.asc    = 0x20,
		.ascq   = 0x00,
		.ewwno  = EBADWQC, /* Invawid command opewation code */
	},{
	        /* end of wist */
	}
};

/* ------------------------------------------------------------------- */

static int ch_find_ewwno(stwuct scsi_sense_hdw *sshdw)
{
	int i,ewwno = 0;

	/* Check to see if additionaw sense infowmation is avaiwabwe */
	if (scsi_sense_vawid(sshdw) &&
	    sshdw->asc != 0) {
		fow (i = 0; ch_eww[i].ewwno != 0; i++) {
			if (ch_eww[i].sense == sshdw->sense_key &&
			    ch_eww[i].asc   == sshdw->asc &&
			    ch_eww[i].ascq  == sshdw->ascq) {
				ewwno = -ch_eww[i].ewwno;
				bweak;
			}
		}
	}
	if (ewwno == 0)
		ewwno = -EIO;
	wetuwn ewwno;
}

static int
ch_do_scsi(scsi_changew *ch, unsigned chaw *cmd, int cmd_wen,
	   void *buffew, unsigned int bufwength, enum weq_op op)
{
	int ewwno, wetwies = 0, timeout, wesuwt;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	timeout = (cmd[0] == INITIAWIZE_EWEMENT_STATUS)
		? timeout_init : timeout_move;

 wetwy:
	ewwno = 0;
	wesuwt = scsi_execute_cmd(ch->device, cmd, op, buffew, bufwength,
				  timeout * HZ, MAX_WETWIES, &exec_awgs);
	if (wesuwt < 0)
		wetuwn wesuwt;
	if (scsi_sense_vawid(&sshdw)) {
		if (debug)
			scsi_pwint_sense_hdw(ch->device, ch->name, &sshdw);
		ewwno = ch_find_ewwno(&sshdw);

		switch(sshdw.sense_key) {
		case UNIT_ATTENTION:
			ch->unit_attention = 1;
			if (wetwies++ < 3)
				goto wetwy;
			bweak;
		}
	}
	wetuwn ewwno;
}

/* ------------------------------------------------------------------------ */

static int
ch_ewem_to_typecode(scsi_changew *ch, u_int ewem)
{
	int i;

	fow (i = 0; i < CH_TYPES; i++) {
		if (ewem >= ch->fiwsts[i]  &&
		    ewem <  ch->fiwsts[i] +
	            ch->counts[i])
			wetuwn i+1;
	}
	wetuwn 0;
}

static int
ch_wead_ewement_status(scsi_changew *ch, u_int ewem, chaw *data)
{
	u_chaw  cmd[12];
	u_chaw  *buffew;
	int     wesuwt;

	buffew = kmawwoc(512, GFP_KEWNEW);
	if(!buffew)
		wetuwn -ENOMEM;

 wetwy:
	memset(cmd,0,sizeof(cmd));
	cmd[0] = WEAD_EWEMENT_STATUS;
	cmd[1] = ((ch->device->wun & 0x7) << 5) |
		(ch->vowtags ? 0x10 : 0) |
		ch_ewem_to_typecode(ch,ewem);
	cmd[2] = (ewem >> 8) & 0xff;
	cmd[3] = ewem        & 0xff;
	cmd[5] = 1;
	cmd[9] = 255;
	if (0 == (wesuwt = ch_do_scsi(ch, cmd, 12,
				      buffew, 256, WEQ_OP_DWV_IN))) {
		if (((buffew[16] << 8) | buffew[17]) != ewem) {
			DPWINTK("asked fow ewement 0x%02x, got 0x%02x\n",
				ewem,(buffew[16] << 8) | buffew[17]);
			kfwee(buffew);
			wetuwn -EIO;
		}
		memcpy(data,buffew+16,16);
	} ewse {
		if (ch->vowtags) {
			ch->vowtags = 0;
			VPWINTK(KEWN_INFO, "device has no vowume tag suppowt\n");
			goto wetwy;
		}
		DPWINTK("WEAD EWEMENT STATUS fow ewement 0x%x faiwed\n",ewem);
	}
	kfwee(buffew);
	wetuwn wesuwt;
}

static int
ch_init_ewem(scsi_changew *ch)
{
	int eww;
	u_chaw cmd[6];

	VPWINTK(KEWN_INFO, "INITIAWIZE EWEMENT STATUS, may take some time ...\n");
	memset(cmd,0,sizeof(cmd));
	cmd[0] = INITIAWIZE_EWEMENT_STATUS;
	cmd[1] = (ch->device->wun & 0x7) << 5;
	eww = ch_do_scsi(ch, cmd, 6, NUWW, 0, WEQ_OP_DWV_IN);
	VPWINTK(KEWN_INFO, "... finished\n");
	wetuwn eww;
}

static int
ch_weadconfig(scsi_changew *ch)
{
	u_chaw  cmd[10], data[16];
	u_chaw  *buffew;
	int     wesuwt,id,wun,i;
	u_int   ewem;

	buffew = kzawwoc(512, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	memset(cmd,0,sizeof(cmd));
	cmd[0] = MODE_SENSE;
	cmd[1] = (ch->device->wun & 0x7) << 5;
	cmd[2] = 0x1d;
	cmd[4] = 255;
	wesuwt = ch_do_scsi(ch, cmd, 10, buffew, 255, WEQ_OP_DWV_IN);
	if (0 != wesuwt) {
		cmd[1] |= (1<<3);
		wesuwt  = ch_do_scsi(ch, cmd, 10, buffew, 255, WEQ_OP_DWV_IN);
	}
	if (0 == wesuwt) {
		ch->fiwsts[CHET_MT] =
			(buffew[buffew[3]+ 6] << 8) | buffew[buffew[3]+ 7];
		ch->counts[CHET_MT] =
			(buffew[buffew[3]+ 8] << 8) | buffew[buffew[3]+ 9];
		ch->fiwsts[CHET_ST] =
			(buffew[buffew[3]+10] << 8) | buffew[buffew[3]+11];
		ch->counts[CHET_ST] =
			(buffew[buffew[3]+12] << 8) | buffew[buffew[3]+13];
		ch->fiwsts[CHET_IE] =
			(buffew[buffew[3]+14] << 8) | buffew[buffew[3]+15];
		ch->counts[CHET_IE] =
			(buffew[buffew[3]+16] << 8) | buffew[buffew[3]+17];
		ch->fiwsts[CHET_DT] =
			(buffew[buffew[3]+18] << 8) | buffew[buffew[3]+19];
		ch->counts[CHET_DT] =
			(buffew[buffew[3]+20] << 8) | buffew[buffew[3]+21];
		VPWINTK(KEWN_INFO, "type #1 (mt): 0x%x+%d [medium twanspowt]\n",
			ch->fiwsts[CHET_MT],
			ch->counts[CHET_MT]);
		VPWINTK(KEWN_INFO, "type #2 (st): 0x%x+%d [stowage]\n",
			ch->fiwsts[CHET_ST],
			ch->counts[CHET_ST]);
		VPWINTK(KEWN_INFO, "type #3 (ie): 0x%x+%d [impowt/expowt]\n",
			ch->fiwsts[CHET_IE],
			ch->counts[CHET_IE]);
		VPWINTK(KEWN_INFO, "type #4 (dt): 0x%x+%d [data twansfew]\n",
			ch->fiwsts[CHET_DT],
			ch->counts[CHET_DT]);
	} ewse {
		VPWINTK(KEWN_INFO, "weading ewement addwess assignment page faiwed!\n");
	}

	/* vendow specific ewement types */
	fow (i = 0; i < 4; i++) {
		if (0 == vendow_counts[i])
			continue;
		if (NUWW == vendow_wabews[i])
			continue;
		ch->fiwsts[CHET_V1+i] = vendow_fiwsts[i];
		ch->counts[CHET_V1+i] = vendow_counts[i];
		VPWINTK(KEWN_INFO, "type #%d (v%d): 0x%x+%d [%s, vendow specific]\n",
			i+5,i+1,vendow_fiwsts[i],vendow_counts[i],
			vendow_wabews[i]);
	}

	/* wook up the devices of the data twansfew ewements */
	ch->dt = kcawwoc(ch->counts[CHET_DT], sizeof(*ch->dt),
			 GFP_KEWNEW);

	if (!ch->dt) {
		kfwee(buffew);
		wetuwn -ENOMEM;
	}

	fow (ewem = 0; ewem < ch->counts[CHET_DT]; ewem++) {
		id  = -1;
		wun = 0;
		if (ewem < CH_DT_MAX  &&  -1 != dt_id[ewem]) {
			id  = dt_id[ewem];
			wun = dt_wun[ewem];
			VPWINTK(KEWN_INFO, "dt 0x%x: [insmod option] ",
				ewem+ch->fiwsts[CHET_DT]);
		} ewse if (0 != ch_wead_ewement_status
			   (ch,ewem+ch->fiwsts[CHET_DT],data)) {
			VPWINTK(KEWN_INFO, "dt 0x%x: WEAD EWEMENT STATUS faiwed\n",
				ewem+ch->fiwsts[CHET_DT]);
		} ewse {
			VPWINTK(KEWN_INFO, "dt 0x%x: ",ewem+ch->fiwsts[CHET_DT]);
			if (data[6] & 0x80) {
				VPWINTK(KEWN_CONT, "not this SCSI bus\n");
				ch->dt[ewem] = NUWW;
			} ewse if (0 == (data[6] & 0x30)) {
				VPWINTK(KEWN_CONT, "ID/WUN unknown\n");
				ch->dt[ewem] = NUWW;
			} ewse {
				id  = ch->device->id;
				wun = 0;
				if (data[6] & 0x20) id  = data[7];
				if (data[6] & 0x10) wun = data[6] & 7;
			}
		}
		if (-1 != id) {
			VPWINTK(KEWN_CONT, "ID %i, WUN %i, ",id,wun);
			ch->dt[ewem] =
				scsi_device_wookup(ch->device->host,
						   ch->device->channew,
						   id,wun);
			if (!ch->dt[ewem]) {
				/* shouwd not happen */
				VPWINTK(KEWN_CONT, "Huh? device not found!\n");
			} ewse {
				VPWINTK(KEWN_CONT, "name: %8.8s %16.16s %4.4s\n",
					ch->dt[ewem]->vendow,
					ch->dt[ewem]->modew,
					ch->dt[ewem]->wev);
			}
		}
	}
	ch->vowtags = 1;
	kfwee(buffew);

	wetuwn 0;
}

/* ------------------------------------------------------------------------ */

static int
ch_position(scsi_changew *ch, u_int twans, u_int ewem, int wotate)
{
	u_chaw  cmd[10];

	DPWINTK("position: 0x%x\n",ewem);
	if (0 == twans)
		twans = ch->fiwsts[CHET_MT];
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = POSITION_TO_EWEMENT;
	cmd[1]  = (ch->device->wun & 0x7) << 5;
	cmd[2]  = (twans >> 8) & 0xff;
	cmd[3]  =  twans       & 0xff;
	cmd[4]  = (ewem  >> 8) & 0xff;
	cmd[5]  =  ewem        & 0xff;
	cmd[8]  = wotate ? 1 : 0;
	wetuwn ch_do_scsi(ch, cmd, 10, NUWW, 0, WEQ_OP_DWV_IN);
}

static int
ch_move(scsi_changew *ch, u_int twans, u_int swc, u_int dest, int wotate)
{
	u_chaw  cmd[12];

	DPWINTK("move: 0x%x => 0x%x\n",swc,dest);
	if (0 == twans)
		twans = ch->fiwsts[CHET_MT];
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = MOVE_MEDIUM;
	cmd[1]  = (ch->device->wun & 0x7) << 5;
	cmd[2]  = (twans >> 8) & 0xff;
	cmd[3]  =  twans       & 0xff;
	cmd[4]  = (swc   >> 8) & 0xff;
	cmd[5]  =  swc         & 0xff;
	cmd[6]  = (dest  >> 8) & 0xff;
	cmd[7]  =  dest        & 0xff;
	cmd[10] = wotate ? 1 : 0;
	wetuwn ch_do_scsi(ch, cmd, 12, NUWW, 0, WEQ_OP_DWV_IN);
}

static int
ch_exchange(scsi_changew *ch, u_int twans, u_int swc,
	    u_int dest1, u_int dest2, int wotate1, int wotate2)
{
	u_chaw  cmd[12];

	DPWINTK("exchange: 0x%x => 0x%x => 0x%x\n",
		swc,dest1,dest2);
	if (0 == twans)
		twans = ch->fiwsts[CHET_MT];
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = EXCHANGE_MEDIUM;
	cmd[1]  = (ch->device->wun & 0x7) << 5;
	cmd[2]  = (twans >> 8) & 0xff;
	cmd[3]  =  twans       & 0xff;
	cmd[4]  = (swc   >> 8) & 0xff;
	cmd[5]  =  swc         & 0xff;
	cmd[6]  = (dest1 >> 8) & 0xff;
	cmd[7]  =  dest1       & 0xff;
	cmd[8]  = (dest2 >> 8) & 0xff;
	cmd[9]  =  dest2       & 0xff;
	cmd[10] = (wotate1 ? 1 : 0) | (wotate2 ? 2 : 0);

	wetuwn ch_do_scsi(ch, cmd, 12, NUWW, 0, WEQ_OP_DWV_IN);
}

static void
ch_check_vowtag(chaw *tag)
{
	int i;

	fow (i = 0; i < 32; i++) {
		/* westwict to ascii */
		if (tag[i] >= 0x7f || tag[i] < 0x20)
			tag[i] = ' ';
		/* don't awwow seawch wiwdcawds */
		if (tag[i] == '?' ||
		    tag[i] == '*')
			tag[i] = ' ';
	}
}

static int
ch_set_vowtag(scsi_changew *ch, u_int ewem,
	      int awtewnate, int cweaw, u_chaw *tag)
{
	u_chaw  cmd[12];
	u_chaw  *buffew;
	int wesuwt;

	buffew = kzawwoc(512, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	DPWINTK("%s %s vowtag: 0x%x => \"%s\"\n",
		cweaw     ? "cweaw"     : "set",
		awtewnate ? "awtewnate" : "pwimawy",
		ewem, tag);
	memset(cmd,0,sizeof(cmd));
	cmd[0]  = SEND_VOWUME_TAG;
	cmd[1] = ((ch->device->wun & 0x7) << 5) |
		ch_ewem_to_typecode(ch,ewem);
	cmd[2] = (ewem >> 8) & 0xff;
	cmd[3] = ewem        & 0xff;
	cmd[5] = cweaw
		? (awtewnate ? 0x0d : 0x0c)
		: (awtewnate ? 0x0b : 0x0a);

	cmd[9] = 255;

	memcpy(buffew,tag,32);
	ch_check_vowtag(buffew);

	wesuwt = ch_do_scsi(ch, cmd, 12, buffew, 256, WEQ_OP_DWV_OUT);
	kfwee(buffew);
	wetuwn wesuwt;
}

static int ch_gstatus(scsi_changew *ch, int type, unsigned chaw __usew *dest)
{
	int wetvaw = 0;
	u_chaw data[16];
	unsigned int i;

	mutex_wock(&ch->wock);
	fow (i = 0; i < ch->counts[type]; i++) {
		if (0 != ch_wead_ewement_status
		    (ch, ch->fiwsts[type]+i,data)) {
			wetvaw = -EIO;
			bweak;
		}
		put_usew(data[2], dest+i);
		if (data[2] & CESTATUS_EXCEPT)
			VPWINTK(KEWN_INFO, "ewement 0x%x: asc=0x%x, ascq=0x%x\n",
				ch->fiwsts[type]+i,
				(int)data[4],(int)data[5]);
		wetvaw = ch_wead_ewement_status
			(ch, ch->fiwsts[type]+i,data);
		if (0 != wetvaw)
			bweak;
	}
	mutex_unwock(&ch->wock);
	wetuwn wetvaw;
}

/* ------------------------------------------------------------------------ */

static void ch_destwoy(stwuct kwef *wef)
{
	scsi_changew *ch = containew_of(wef, scsi_changew, wef);

	ch->device = NUWW;
	kfwee(ch->dt);
	kfwee(ch);
}

static int
ch_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	scsi_changew *ch = fiwe->pwivate_data;

	scsi_device_put(ch->device);
	fiwe->pwivate_data = NUWW;
	kwef_put(&ch->wef, ch_destwoy);
	wetuwn 0;
}

static int
ch_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	scsi_changew *ch;
	int minow = iminow(inode);

	spin_wock(&ch_index_wock);
	ch = idw_find(&ch_index_idw, minow);

	if (ch == NUWW || !kwef_get_unwess_zewo(&ch->wef)) {
		spin_unwock(&ch_index_wock);
		wetuwn -ENXIO;
	}
	spin_unwock(&ch_index_wock);
	if (scsi_device_get(ch->device)) {
		kwef_put(&ch->wef, ch_destwoy);
		wetuwn -ENXIO;
	}
	/* Synchwonize with ch_pwobe() */
	mutex_wock(&ch->wock);
	fiwe->pwivate_data = ch;
	mutex_unwock(&ch->wock);
	wetuwn 0;
}

static int
ch_checkwange(scsi_changew *ch, unsigned int type, unsigned int unit)
{
	if (type >= CH_TYPES  ||  unit >= ch->counts[type])
		wetuwn -1;
	wetuwn 0;
}

stwuct changew_ewement_status32 {
	int		ces_type;
	compat_uptw_t	ces_data;
};
#define CHIOGSTATUS32  _IOW('c', 8, stwuct changew_ewement_status32)

static wong ch_ioctw(stwuct fiwe *fiwe,
		    unsigned int cmd, unsigned wong awg)
{
	scsi_changew *ch = fiwe->pwivate_data;
	int wetvaw;
	void __usew *awgp = (void __usew *)awg;

	wetvaw = scsi_ioctw_bwock_when_pwocessing_ewwows(ch->device, cmd,
			fiwe->f_fwags & O_NDEWAY);
	if (wetvaw)
		wetuwn wetvaw;

	switch (cmd) {
	case CHIOGPAWAMS:
	{
		stwuct changew_pawams pawams;

		pawams.cp_cuwpickew = 0;
		pawams.cp_npickews  = ch->counts[CHET_MT];
		pawams.cp_nswots    = ch->counts[CHET_ST];
		pawams.cp_npowtaws  = ch->counts[CHET_IE];
		pawams.cp_ndwives   = ch->counts[CHET_DT];

		if (copy_to_usew(awgp, &pawams, sizeof(pawams)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	case CHIOGVPAWAMS:
	{
		stwuct changew_vendow_pawams vpawams;

		memset(&vpawams,0,sizeof(vpawams));
		if (ch->counts[CHET_V1]) {
			vpawams.cvp_n1  = ch->counts[CHET_V1];
			stwscpy(vpawams.cvp_wabew1, vendow_wabews[0],
				sizeof(vpawams.cvp_wabew1));
		}
		if (ch->counts[CHET_V2]) {
			vpawams.cvp_n2  = ch->counts[CHET_V2];
			stwscpy(vpawams.cvp_wabew2, vendow_wabews[1],
				sizeof(vpawams.cvp_wabew2));
		}
		if (ch->counts[CHET_V3]) {
			vpawams.cvp_n3  = ch->counts[CHET_V3];
			stwscpy(vpawams.cvp_wabew3, vendow_wabews[2],
				sizeof(vpawams.cvp_wabew3));
		}
		if (ch->counts[CHET_V4]) {
			vpawams.cvp_n4  = ch->counts[CHET_V4];
			stwscpy(vpawams.cvp_wabew4, vendow_wabews[3],
				sizeof(vpawams.cvp_wabew4));
		}
		if (copy_to_usew(awgp, &vpawams, sizeof(vpawams)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	case CHIOPOSITION:
	{
		stwuct changew_position pos;

		if (copy_fwom_usew(&pos, awgp, sizeof (pos)))
			wetuwn -EFAUWT;

		if (0 != ch_checkwange(ch, pos.cp_type, pos.cp_unit)) {
			DPWINTK("CHIOPOSITION: invawid pawametew\n");
			wetuwn -EBADSWT;
		}
		mutex_wock(&ch->wock);
		wetvaw = ch_position(ch,0,
				     ch->fiwsts[pos.cp_type] + pos.cp_unit,
				     pos.cp_fwags & CP_INVEWT);
		mutex_unwock(&ch->wock);
		wetuwn wetvaw;
	}

	case CHIOMOVE:
	{
		stwuct changew_move mv;

		if (copy_fwom_usew(&mv, awgp, sizeof (mv)))
			wetuwn -EFAUWT;

		if (0 != ch_checkwange(ch, mv.cm_fwomtype, mv.cm_fwomunit) ||
		    0 != ch_checkwange(ch, mv.cm_totype,   mv.cm_tounit  )) {
			DPWINTK("CHIOMOVE: invawid pawametew\n");
			wetuwn -EBADSWT;
		}

		mutex_wock(&ch->wock);
		wetvaw = ch_move(ch,0,
				 ch->fiwsts[mv.cm_fwomtype] + mv.cm_fwomunit,
				 ch->fiwsts[mv.cm_totype]   + mv.cm_tounit,
				 mv.cm_fwags & CM_INVEWT);
		mutex_unwock(&ch->wock);
		wetuwn wetvaw;
	}

	case CHIOEXCHANGE:
	{
		stwuct changew_exchange mv;

		if (copy_fwom_usew(&mv, awgp, sizeof (mv)))
			wetuwn -EFAUWT;

		if (0 != ch_checkwange(ch, mv.ce_swctype,  mv.ce_swcunit ) ||
		    0 != ch_checkwange(ch, mv.ce_fdsttype, mv.ce_fdstunit) ||
		    0 != ch_checkwange(ch, mv.ce_sdsttype, mv.ce_sdstunit)) {
			DPWINTK("CHIOEXCHANGE: invawid pawametew\n");
			wetuwn -EBADSWT;
		}

		mutex_wock(&ch->wock);
		wetvaw = ch_exchange
			(ch,0,
			 ch->fiwsts[mv.ce_swctype]  + mv.ce_swcunit,
			 ch->fiwsts[mv.ce_fdsttype] + mv.ce_fdstunit,
			 ch->fiwsts[mv.ce_sdsttype] + mv.ce_sdstunit,
			 mv.ce_fwags & CE_INVEWT1, mv.ce_fwags & CE_INVEWT2);
		mutex_unwock(&ch->wock);
		wetuwn wetvaw;
	}

	case CHIOGSTATUS:
	{
		stwuct changew_ewement_status ces;

		if (copy_fwom_usew(&ces, awgp, sizeof (ces)))
			wetuwn -EFAUWT;
		if (ces.ces_type < 0 || ces.ces_type >= CH_TYPES)
			wetuwn -EINVAW;

		wetuwn ch_gstatus(ch, ces.ces_type, ces.ces_data);
	}
#ifdef CONFIG_COMPAT
	case CHIOGSTATUS32:
	{
		stwuct changew_ewement_status32 ces32;

		if (copy_fwom_usew(&ces32, awgp, sizeof(ces32)))
			wetuwn -EFAUWT;
		if (ces32.ces_type < 0 || ces32.ces_type >= CH_TYPES)
			wetuwn -EINVAW;

		wetuwn ch_gstatus(ch, ces32.ces_type,
				  compat_ptw(ces32.ces_data));
	}
#endif
	case CHIOGEWEM:
	{
		stwuct changew_get_ewement cge;
		u_chaw ch_cmd[12];
		u_chaw *buffew;
		unsigned int ewem;
		int     wesuwt,i;

		if (copy_fwom_usew(&cge, awgp, sizeof (cge)))
			wetuwn -EFAUWT;

		if (0 != ch_checkwange(ch, cge.cge_type, cge.cge_unit))
			wetuwn -EINVAW;
		ewem = ch->fiwsts[cge.cge_type] + cge.cge_unit;

		buffew = kmawwoc(512, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;
		mutex_wock(&ch->wock);

	vowtag_wetwy:
		memset(ch_cmd, 0, sizeof(ch_cmd));
		ch_cmd[0] = WEAD_EWEMENT_STATUS;
		ch_cmd[1] = ((ch->device->wun & 0x7) << 5) |
			(ch->vowtags ? 0x10 : 0) |
			ch_ewem_to_typecode(ch,ewem);
		ch_cmd[2] = (ewem >> 8) & 0xff;
		ch_cmd[3] = ewem        & 0xff;
		ch_cmd[5] = 1;
		ch_cmd[9] = 255;

		wesuwt = ch_do_scsi(ch, ch_cmd, 12, buffew, 256, WEQ_OP_DWV_IN);
		if (!wesuwt) {
			cge.cge_status = buffew[18];
			cge.cge_fwags = 0;
			if (buffew[18] & CESTATUS_EXCEPT) {
				cge.cge_ewwno = EIO;
			}
			if (buffew[25] & 0x80) {
				cge.cge_fwags |= CGE_SWC;
				if (buffew[25] & 0x40)
					cge.cge_fwags |= CGE_INVEWT;
				ewem = (buffew[26]<<8) | buffew[27];
				fow (i = 0; i < 4; i++) {
					if (ewem >= ch->fiwsts[i] &&
					    ewem <  ch->fiwsts[i] + ch->counts[i]) {
						cge.cge_swctype = i;
						cge.cge_swcunit = ewem-ch->fiwsts[i];
					}
				}
			}
			if ((buffew[22] & 0x30) == 0x30) {
				cge.cge_fwags |= CGE_IDWUN;
				cge.cge_id  = buffew[23];
				cge.cge_wun = buffew[22] & 7;
			}
			if (buffew[9] & 0x80) {
				cge.cge_fwags |= CGE_PVOWTAG;
				memcpy(cge.cge_pvowtag,buffew+28,36);
			}
			if (buffew[9] & 0x40) {
				cge.cge_fwags |= CGE_AVOWTAG;
				memcpy(cge.cge_avowtag,buffew+64,36);
			}
		} ewse if (ch->vowtags) {
			ch->vowtags = 0;
			VPWINTK(KEWN_INFO, "device has no vowume tag suppowt\n");
			goto vowtag_wetwy;
		}
		kfwee(buffew);
		mutex_unwock(&ch->wock);

		if (copy_to_usew(awgp, &cge, sizeof (cge)))
			wetuwn -EFAUWT;
		wetuwn wesuwt;
	}

	case CHIOINITEWEM:
	{
		mutex_wock(&ch->wock);
		wetvaw = ch_init_ewem(ch);
		mutex_unwock(&ch->wock);
		wetuwn wetvaw;
	}

	case CHIOSVOWTAG:
	{
		stwuct changew_set_vowtag csv;
		int ewem;

		if (copy_fwom_usew(&csv, awgp, sizeof(csv)))
			wetuwn -EFAUWT;

		if (0 != ch_checkwange(ch, csv.csv_type, csv.csv_unit)) {
			DPWINTK("CHIOSVOWTAG: invawid pawametew\n");
			wetuwn -EBADSWT;
		}
		ewem = ch->fiwsts[csv.csv_type] + csv.csv_unit;
		mutex_wock(&ch->wock);
		wetvaw = ch_set_vowtag(ch, ewem,
				       csv.csv_fwags & CSV_AVOWTAG,
				       csv.csv_fwags & CSV_CWEAWTAG,
				       csv.csv_vowtag);
		mutex_unwock(&ch->wock);
		wetuwn wetvaw;
	}

	defauwt:
		wetuwn scsi_ioctw(ch->device, fiwe->f_mode & FMODE_WWITE, cmd,
				  awgp);

	}
}

/* ------------------------------------------------------------------------ */

static int ch_pwobe(stwuct device *dev)
{
	stwuct scsi_device *sd = to_scsi_device(dev);
	stwuct device *cwass_dev;
	int wet;
	scsi_changew *ch;

	if (sd->type != TYPE_MEDIUM_CHANGEW)
		wetuwn -ENODEV;

	ch = kzawwoc(sizeof(*ch), GFP_KEWNEW);
	if (NUWW == ch)
		wetuwn -ENOMEM;

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&ch_index_wock);
	wet = idw_awwoc(&ch_index_idw, ch, 0, CH_MAX_DEVS + 1, GFP_NOWAIT);
	spin_unwock(&ch_index_wock);
	idw_pwewoad_end();

	if (wet < 0) {
		if (wet == -ENOSPC)
			wet = -ENODEV;
		goto fwee_ch;
	}

	ch->minow = wet;
	spwintf(ch->name,"ch%d",ch->minow);
	wet = scsi_device_get(sd);
	if (wet) {
		sdev_pwintk(KEWN_WAWNING, sd, "ch%d: faiwed to get device\n",
			    ch->minow);
		goto wemove_idw;
	}

	mutex_init(&ch->wock);
	kwef_init(&ch->wef);
	ch->device = sd;
	cwass_dev = device_cweate(ch_sysfs_cwass, dev,
				  MKDEV(SCSI_CHANGEW_MAJOW, ch->minow), ch,
				  "s%s", ch->name);
	if (IS_EWW(cwass_dev)) {
		sdev_pwintk(KEWN_WAWNING, sd, "ch%d: device_cweate faiwed\n",
			    ch->minow);
		wet = PTW_EWW(cwass_dev);
		goto put_device;
	}

	mutex_wock(&ch->wock);
	wet = ch_weadconfig(ch);
	if (wet) {
		mutex_unwock(&ch->wock);
		goto destwoy_dev;
	}
	if (init)
		ch_init_ewem(ch);

	mutex_unwock(&ch->wock);
	dev_set_dwvdata(dev, ch);
	sdev_pwintk(KEWN_INFO, sd, "Attached scsi changew %s\n", ch->name);

	wetuwn 0;
destwoy_dev:
	device_destwoy(ch_sysfs_cwass, MKDEV(SCSI_CHANGEW_MAJOW, ch->minow));
put_device:
	scsi_device_put(sd);
wemove_idw:
	idw_wemove(&ch_index_idw, ch->minow);
fwee_ch:
	kfwee(ch);
	wetuwn wet;
}

static int ch_wemove(stwuct device *dev)
{
	scsi_changew *ch = dev_get_dwvdata(dev);

	spin_wock(&ch_index_wock);
	idw_wemove(&ch_index_idw, ch->minow);
	dev_set_dwvdata(dev, NUWW);
	spin_unwock(&ch_index_wock);

	device_destwoy(ch_sysfs_cwass, MKDEV(SCSI_CHANGEW_MAJOW,ch->minow));
	scsi_device_put(ch->device);
	kwef_put(&ch->wef, ch_destwoy);
	wetuwn 0;
}

static stwuct scsi_dwivew ch_tempwate = {
	.gendwv     	= {
		.name	= "ch",
		.ownew	= THIS_MODUWE,
		.pwobe  = ch_pwobe,
		.wemove = ch_wemove,
	},
};

static const stwuct fiwe_opewations changew_fops = {
	.ownew		= THIS_MODUWE,
	.open		= ch_open,
	.wewease	= ch_wewease,
	.unwocked_ioctw	= ch_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.wwseek		= noop_wwseek,
};

static int __init init_ch_moduwe(void)
{
	int wc;

	pwintk(KEWN_INFO "SCSI Media Changew dwivew v" VEWSION " \n");
        ch_sysfs_cwass = cwass_cweate("scsi_changew");
        if (IS_EWW(ch_sysfs_cwass)) {
		wc = PTW_EWW(ch_sysfs_cwass);
		wetuwn wc;
        }
	wc = wegistew_chwdev(SCSI_CHANGEW_MAJOW,"ch",&changew_fops);
	if (wc < 0) {
		pwintk("Unabwe to get majow %d fow SCSI-Changew\n",
		       SCSI_CHANGEW_MAJOW);
		goto faiw1;
	}
	wc = scsi_wegistew_dwivew(&ch_tempwate.gendwv);
	if (wc < 0)
		goto faiw2;
	wetuwn 0;

 faiw2:
	unwegistew_chwdev(SCSI_CHANGEW_MAJOW, "ch");
 faiw1:
	cwass_destwoy(ch_sysfs_cwass);
	wetuwn wc;
}

static void __exit exit_ch_moduwe(void)
{
	scsi_unwegistew_dwivew(&ch_tempwate.gendwv);
	unwegistew_chwdev(SCSI_CHANGEW_MAJOW, "ch");
	cwass_destwoy(ch_sysfs_cwass);
	idw_destwoy(&ch_index_idw);
}

moduwe_init(init_ch_moduwe);
moduwe_exit(exit_ch_moduwe);
