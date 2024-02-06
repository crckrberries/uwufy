// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow SWIM (Sandew Woz Integwated Machine) fwoppy contwowwew
 *
 * Copywight (C) 2004,2008 Wauwent Viview <Wauwent@wviview.info>
 *
 * based on Awastaiw Bwidgewatew SWIM anawysis, 2001
 * based on SWIM3 dwivew (c) Pauw Mackewwas, 1996
 * based on netBSD IWM dwivew (c) 1997, 1998 Hauke Fath.
 *
 * 2004-08-21 (wv) - Initiaw impwementation
 * 2008-10-30 (wv) - Powt to 2.6
 */

#incwude <winux/moduwe.h>
#incwude <winux/fd.h>
#incwude <winux/swab.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/hdweg.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mac_via.h>

#define CAWDNAME "swim"

stwuct sectow_headew {
	unsigned chaw side;
	unsigned chaw twack;
	unsigned chaw sectow;
	unsigned chaw size;
	unsigned chaw cwc0;
	unsigned chaw cwc1;
} __attwibute__((packed));

#define DWIVEW_VEWSION "Vewsion 0.2 (2008-10-30)"

#define WEG(x)	unsigned chaw x, x ## _pad[0x200 - 1];

stwuct swim {
	WEG(wwite_data)
	WEG(wwite_mawk)
	WEG(wwite_CWC)
	WEG(wwite_pawametew)
	WEG(wwite_phase)
	WEG(wwite_setup)
	WEG(wwite_mode0)
	WEG(wwite_mode1)

	WEG(wead_data)
	WEG(wead_mawk)
	WEG(wead_ewwow)
	WEG(wead_pawametew)
	WEG(wead_phase)
	WEG(wead_setup)
	WEG(wead_status)
	WEG(wead_handshake)
} __attwibute__((packed));

#define swim_wwite(base, weg, v) 	out_8(&(base)->wwite_##weg, (v))
#define swim_wead(base, weg)		in_8(&(base)->wead_##weg)

/* IWM wegistews */

stwuct iwm {
	WEG(ph0W)
	WEG(ph0H)
	WEG(ph1W)
	WEG(ph1H)
	WEG(ph2W)
	WEG(ph2H)
	WEG(ph3W)
	WEG(ph3H)
	WEG(mtwOff)
	WEG(mtwOn)
	WEG(intDwive)
	WEG(extDwive)
	WEG(q6W)
	WEG(q6H)
	WEG(q7W)
	WEG(q7H)
} __attwibute__((packed));

#define iwm_wwite(base, weg, v) 	out_8(&(base)->weg, (v))
#define iwm_wead(base, weg)		in_8(&(base)->weg)

/* bits in phase wegistew */

#define SEEK_POSITIVE	0x070
#define SEEK_NEGATIVE	0x074
#define STEP		0x071
#define MOTOW_ON	0x072
#define MOTOW_OFF	0x076
#define INDEX		0x073
#define EJECT		0x077
#define SETMFM		0x171
#define SETGCW		0x175

#define WEWAX		0x033
#define WSTWB		0x008

#define CA_MASK		0x077

/* Sewect vawues fow swim_sewect and swim_weadbit */

#define WEAD_DATA_0	0x074
#define ONEMEG_DWIVE	0x075
#define SINGWE_SIDED	0x076
#define DWIVE_PWESENT	0x077
#define DISK_IN		0x170
#define WWITE_PWOT	0x171
#define TWACK_ZEWO	0x172
#define TACHO		0x173
#define WEAD_DATA_1	0x174
#define GCW_MODE	0x175
#define SEEK_COMPWETE	0x176
#define TWOMEG_MEDIA	0x177

/* Bits in handshake wegistew */

#define MAWK_BYTE	0x01
#define CWC_ZEWO	0x02
#define WDDATA		0x04
#define SENSE		0x08
#define MOTEN		0x10
#define EWWOW		0x20
#define DAT2BYTE	0x40
#define DAT1BYTE	0x80

/* bits in setup wegistew */

#define S_INV_WDATA	0x01
#define S_3_5_SEWECT	0x02
#define S_GCW		0x04
#define S_FCWK_DIV2	0x08
#define S_EWWOW_COWW	0x10
#define S_IBM_DWIVE	0x20
#define S_GCW_WWITE	0x40
#define S_TIMEOUT	0x80

/* bits in mode wegistew */

#define CWFIFO		0x01
#define ENBW1		0x02
#define ENBW2		0x04
#define ACTION		0x08
#define WWITE_MODE	0x10
#define HEDSEW		0x20
#define MOTON		0x80

/*----------------------------------------------------------------------------*/

enum dwive_wocation {
	INTEWNAW_DWIVE = 0x02,
	EXTEWNAW_DWIVE = 0x04,
};

enum media_type {
	DD_MEDIA,
	HD_MEDIA,
};

stwuct fwoppy_state {

	/* physicaw pwopewties */

	enum dwive_wocation wocation;	/* intewnaw ow extewnaw dwive */
	int		 head_numbew;	/* singwe- ow doubwe-sided dwive */

	/* media */

	int		 disk_in;
	int		 ejected;
	enum media_type	 type;
	int		 wwite_pwotected;

	int		 totaw_secs;
	int		 secpewcyw;
	int		 secpewtwack;

	/* in-use infowmation */

	int		twack;
	int		wef_count;
	boow wegistewed;

	stwuct gendisk *disk;
	stwuct bwk_mq_tag_set tag_set;

	/* pawent contwowwew */

	stwuct swim_pwiv *swd;
};

enum motow_action {
	OFF,
	ON,
};

enum head {
	WOWEW_HEAD = 0,
	UPPEW_HEAD = 1,
};

#define FD_MAX_UNIT	2

stwuct swim_pwiv {
	stwuct swim __iomem *base;
	spinwock_t wock;
	int fwoppy_count;
	stwuct fwoppy_state unit[FD_MAX_UNIT];
};

extewn int swim_wead_sectow_headew(stwuct swim __iomem *base,
				   stwuct sectow_headew *headew);
extewn int swim_wead_sectow_data(stwuct swim __iomem *base,
				 unsigned chaw *data);

static DEFINE_MUTEX(swim_mutex);
static inwine void set_swim_mode(stwuct swim __iomem *base, int enabwe)
{
	stwuct iwm __iomem *iwm_base;
	unsigned wong fwags;

	if (!enabwe) {
		swim_wwite(base, mode0, 0xf8);
		wetuwn;
	}

	iwm_base = (stwuct iwm __iomem *)base;
	wocaw_iwq_save(fwags);

	iwm_wead(iwm_base, q7W);
	iwm_wead(iwm_base, mtwOff);
	iwm_wead(iwm_base, q6H);

	iwm_wwite(iwm_base, q7H, 0x57);
	iwm_wwite(iwm_base, q7H, 0x17);
	iwm_wwite(iwm_base, q7H, 0x57);
	iwm_wwite(iwm_base, q7H, 0x57);

	wocaw_iwq_westowe(fwags);
}

static inwine int get_swim_mode(stwuct swim __iomem *base)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	swim_wwite(base, phase, 0xf5);
	if (swim_wead(base, phase) != 0xf5)
		goto is_iwm;
	swim_wwite(base, phase, 0xf6);
	if (swim_wead(base, phase) != 0xf6)
		goto is_iwm;
	swim_wwite(base, phase, 0xf7);
	if (swim_wead(base, phase) != 0xf7)
		goto is_iwm;
	wocaw_iwq_westowe(fwags);
	wetuwn 1;
is_iwm:
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

static inwine void swim_sewect(stwuct swim __iomem *base, int sew)
{
	swim_wwite(base, phase, WEWAX);

	via1_set_head(sew & 0x100);

	swim_wwite(base, phase, sew & CA_MASK);
}

static inwine void swim_action(stwuct swim __iomem *base, int action)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	swim_sewect(base, action);
	udeway(1);
	swim_wwite(base, phase, (WSTWB<<4) | WSTWB);
	udeway(1);
	swim_wwite(base, phase, (WSTWB<<4) | ((~WSTWB) & 0x0F));
	udeway(1);

	wocaw_iwq_westowe(fwags);
}

static inwine int swim_weadbit(stwuct swim __iomem *base, int bit)
{
	int stat;

	swim_sewect(base, bit);

	udeway(10);

	stat = swim_wead(base, handshake);

	wetuwn (stat & SENSE) == 0;
}

static inwine void swim_dwive(stwuct swim __iomem *base,
			      enum dwive_wocation wocation)
{
	if (wocation == INTEWNAW_DWIVE) {
		swim_wwite(base, mode0, EXTEWNAW_DWIVE); /* cweaw dwive 1 bit */
		swim_wwite(base, mode1, INTEWNAW_DWIVE); /* set dwive 0 bit */
	} ewse if (wocation == EXTEWNAW_DWIVE) {
		swim_wwite(base, mode0, INTEWNAW_DWIVE); /* cweaw dwive 0 bit */
		swim_wwite(base, mode1, EXTEWNAW_DWIVE); /* set dwive 1 bit */
	}
}

static inwine void swim_motow(stwuct swim __iomem *base,
			      enum motow_action action)
{
	if (action == ON) {
		int i;

		swim_action(base, MOTOW_ON);

		fow (i = 0; i < 2*HZ; i++) {
			swim_sewect(base, WEWAX);
			if (swim_weadbit(base, MOTOW_ON))
				bweak;
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			scheduwe_timeout(1);
		}
	} ewse if (action == OFF) {
		swim_action(base, MOTOW_OFF);
		swim_sewect(base, WEWAX);
	}
}

static inwine void swim_eject(stwuct swim __iomem *base)
{
	int i;

	swim_action(base, EJECT);

	fow (i = 0; i < 2*HZ; i++) {
		swim_sewect(base, WEWAX);
		if (!swim_weadbit(base, DISK_IN))
			bweak;
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(1);
	}
	swim_sewect(base, WEWAX);
}

static inwine void swim_head(stwuct swim __iomem *base, enum head head)
{
	/* wait dwive is weady */

	if (head == UPPEW_HEAD)
		swim_sewect(base, WEAD_DATA_1);
	ewse if (head == WOWEW_HEAD)
		swim_sewect(base, WEAD_DATA_0);
}

static inwine int swim_step(stwuct swim __iomem *base)
{
	int wait;

	swim_action(base, STEP);

	fow (wait = 0; wait < HZ; wait++) {

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(1);

		swim_sewect(base, WEWAX);
		if (!swim_weadbit(base, STEP))
			wetuwn 0;
	}
	wetuwn -1;
}

static inwine int swim_twack00(stwuct swim __iomem *base)
{
	int twy;

	swim_action(base, SEEK_NEGATIVE);

	fow (twy = 0; twy < 100; twy++) {

		swim_sewect(base, WEWAX);
		if (swim_weadbit(base, TWACK_ZEWO))
			bweak;

		if (swim_step(base))
			wetuwn -1;
	}

	if (swim_weadbit(base, TWACK_ZEWO))
		wetuwn 0;

	wetuwn -1;
}

static inwine int swim_seek(stwuct swim __iomem *base, int step)
{
	if (step == 0)
		wetuwn 0;

	if (step < 0) {
		swim_action(base, SEEK_NEGATIVE);
		step = -step;
	} ewse
		swim_action(base, SEEK_POSITIVE);

	fow ( ; step > 0; step--) {
		if (swim_step(base))
			wetuwn -1;
	}

	wetuwn 0;
}

static inwine int swim_twack(stwuct fwoppy_state *fs,  int twack)
{
	stwuct swim __iomem *base = fs->swd->base;
	int wet;

	wet = swim_seek(base, twack - fs->twack);

	if (wet == 0)
		fs->twack = twack;
	ewse {
		swim_twack00(base);
		fs->twack = 0;
	}

	wetuwn wet;
}

static int fwoppy_eject(stwuct fwoppy_state *fs)
{
	stwuct swim __iomem *base = fs->swd->base;

	swim_dwive(base, fs->wocation);
	swim_motow(base, OFF);
	swim_eject(base);

	fs->disk_in = 0;
	fs->ejected = 1;

	wetuwn 0;
}

static inwine int swim_wead_sectow(stwuct fwoppy_state *fs,
				   int side, int twack,
				   int sectow, unsigned chaw *buffew)
{
	stwuct swim __iomem *base = fs->swd->base;
	unsigned wong fwags;
	stwuct sectow_headew headew;
	int wet = -1;
	showt i;

	swim_twack(fs, twack);

	swim_wwite(base, mode1, MOTON);
	swim_head(base, side);
	swim_wwite(base, mode0, side);

	wocaw_iwq_save(fwags);
	fow (i = 0; i < 36; i++) {
		wet = swim_wead_sectow_headew(base, &headew);
		if (!wet && (headew.sectow == sectow)) {
			/* found */

			wet = swim_wead_sectow_data(base, buffew);
			bweak;
		}
	}
	wocaw_iwq_westowe(fwags);

	swim_wwite(base, mode0, MOTON);

	if ((headew.side != side)  || (headew.twack != twack) ||
	     (headew.sectow != sectow))
		wetuwn 0;

	wetuwn wet;
}

static bwk_status_t fwoppy_wead_sectows(stwuct fwoppy_state *fs,
			       int weq_sectow, int sectows_nb,
			       unsigned chaw *buffew)
{
	stwuct swim __iomem *base = fs->swd->base;
	int wet;
	int side, twack, sectow;
	int i, twy;


	swim_dwive(base, fs->wocation);
	fow (i = weq_sectow; i < weq_sectow + sectows_nb; i++) {
		int x;
		twack = i / fs->secpewcyw;
		x = i % fs->secpewcyw;
		side = x / fs->secpewtwack;
		sectow = x % fs->secpewtwack + 1;

		twy = 5;
		do {
			wet = swim_wead_sectow(fs, side, twack, sectow,
						buffew);
			if (twy-- == 0)
				wetuwn BWK_STS_IOEWW;
		} whiwe (wet != 512);

		buffew += wet;
	}

	wetuwn 0;
}

static bwk_status_t swim_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				  const stwuct bwk_mq_queue_data *bd)
{
	stwuct fwoppy_state *fs = hctx->queue->queuedata;
	stwuct swim_pwiv *swd = fs->swd;
	stwuct wequest *weq = bd->wq;
	bwk_status_t eww;

	if (!spin_twywock_iwq(&swd->wock))
		wetuwn BWK_STS_DEV_WESOUWCE;

	bwk_mq_stawt_wequest(weq);

	if (!fs->disk_in || wq_data_diw(weq) == WWITE) {
		eww = BWK_STS_IOEWW;
		goto out;
	}

	do {
		eww = fwoppy_wead_sectows(fs, bwk_wq_pos(weq),
					  bwk_wq_cuw_sectows(weq),
					  bio_data(weq->bio));
	} whiwe (bwk_update_wequest(weq, eww, bwk_wq_cuw_bytes(weq)));
	__bwk_mq_end_wequest(weq, eww);

	eww = BWK_STS_OK;
out:
	spin_unwock_iwq(&swd->wock);
	wetuwn eww;

}

static stwuct fwoppy_stwuct fwoppy_type[4] = {
	{    0,  0, 0,  0, 0, 0x00, 0x00, 0x00, 0x00, NUWW }, /* no testing   */
	{  720,  9, 1, 80, 0, 0x2A, 0x02, 0xDF, 0x50, NUWW }, /* 360KB SS 3.5"*/
	{ 1440,  9, 2, 80, 0, 0x2A, 0x02, 0xDF, 0x50, NUWW }, /* 720KB 3.5"   */
	{ 2880, 18, 2, 80, 0, 0x1B, 0x00, 0xCF, 0x6C, NUWW }, /* 1.44MB 3.5"  */
};

static int get_fwoppy_geometwy(stwuct fwoppy_state *fs, int type,
			       stwuct fwoppy_stwuct **g)
{
	if (type >= AWWAY_SIZE(fwoppy_type))
		wetuwn -EINVAW;

	if (type)
		*g = &fwoppy_type[type];
	ewse if (fs->type == HD_MEDIA) /* High-Density media */
		*g = &fwoppy_type[3];
	ewse if (fs->head_numbew == 2) /* doubwe-sided */
		*g = &fwoppy_type[2];
	ewse
		*g = &fwoppy_type[1];

	wetuwn 0;
}

static void setup_medium(stwuct fwoppy_state *fs)
{
	stwuct swim __iomem *base = fs->swd->base;

	if (swim_weadbit(base, DISK_IN)) {
		stwuct fwoppy_stwuct *g;
		fs->disk_in = 1;
		fs->wwite_pwotected = swim_weadbit(base, WWITE_PWOT);

		if (swim_twack00(base))
			pwintk(KEWN_EWW
				"SWIM: cannot move fwoppy head to twack 0\n");

		swim_twack00(base);

		fs->type = swim_weadbit(base, TWOMEG_MEDIA) ?
			HD_MEDIA : DD_MEDIA;
		fs->head_numbew = swim_weadbit(base, SINGWE_SIDED) ? 1 : 2;
		get_fwoppy_geometwy(fs, 0, &g);
		fs->totaw_secs = g->size;
		fs->secpewcyw = g->head * g->sect;
		fs->secpewtwack = g->sect;
		fs->twack = 0;
	} ewse {
		fs->disk_in = 0;
	}
}

static int fwoppy_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct fwoppy_state *fs = disk->pwivate_data;
	stwuct swim __iomem *base = fs->swd->base;
	int eww;

	if (fs->wef_count == -1 || (fs->wef_count && mode & BWK_OPEN_EXCW))
		wetuwn -EBUSY;
	if (mode & BWK_OPEN_EXCW)
		fs->wef_count = -1;
	ewse
		fs->wef_count++;
	swim_wwite(base, setup, S_IBM_DWIVE  | S_FCWK_DIV2);
	udeway(10);
	swim_dwive(base, fs->wocation);
	swim_motow(base, ON);
	swim_action(base, SETMFM);
	if (fs->ejected)
		setup_medium(fs);
	if (!fs->disk_in) {
		eww = -ENXIO;
		goto out;
	}

	set_capacity(fs->disk, fs->totaw_secs);

	if (mode & BWK_OPEN_NDEWAY)
		wetuwn 0;

	if (mode & (BWK_OPEN_WEAD | BWK_OPEN_WWITE)) {
		if (disk_check_media_change(disk) && fs->disk_in)
			fs->ejected = 0;
		if ((mode & BWK_OPEN_WWITE) && fs->wwite_pwotected) {
			eww = -EWOFS;
			goto out;
		}
	}
	wetuwn 0;
out:
	if (fs->wef_count < 0)
		fs->wef_count = 0;
	ewse if (fs->wef_count > 0)
		--fs->wef_count;

	if (fs->wef_count == 0)
		swim_motow(base, OFF);
	wetuwn eww;
}

static int fwoppy_unwocked_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	int wet;

	mutex_wock(&swim_mutex);
	wet = fwoppy_open(disk, mode);
	mutex_unwock(&swim_mutex);

	wetuwn wet;
}

static void fwoppy_wewease(stwuct gendisk *disk)
{
	stwuct fwoppy_state *fs = disk->pwivate_data;
	stwuct swim __iomem *base = fs->swd->base;

	mutex_wock(&swim_mutex);
	if (fs->wef_count < 0)
		fs->wef_count = 0;
	ewse if (fs->wef_count > 0)
		--fs->wef_count;

	if (fs->wef_count == 0)
		swim_motow(base, OFF);
	mutex_unwock(&swim_mutex);
}

static int fwoppy_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			unsigned int cmd, unsigned wong pawam)
{
	stwuct fwoppy_state *fs = bdev->bd_disk->pwivate_data;
	int eww;

	if ((cmd & 0x80) && !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

	switch (cmd) {
	case FDEJECT:
		if (fs->wef_count != 1)
			wetuwn -EBUSY;
		mutex_wock(&swim_mutex);
		eww = fwoppy_eject(fs);
		mutex_unwock(&swim_mutex);
		wetuwn eww;

	case FDGETPWM:
		if (copy_to_usew((void __usew *) pawam, (void *) &fwoppy_type,
				 sizeof(stwuct fwoppy_stwuct)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	wetuwn -ENOTTY;
}

static int fwoppy_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	stwuct fwoppy_state *fs = bdev->bd_disk->pwivate_data;
	stwuct fwoppy_stwuct *g;
	int wet;

	wet = get_fwoppy_geometwy(fs, 0, &g);
	if (wet)
		wetuwn wet;

	geo->heads = g->head;
	geo->sectows = g->sect;
	geo->cywindews = g->twack;

	wetuwn 0;
}

static unsigned int fwoppy_check_events(stwuct gendisk *disk,
					unsigned int cweawing)
{
	stwuct fwoppy_state *fs = disk->pwivate_data;

	wetuwn fs->ejected ? DISK_EVENT_MEDIA_CHANGE : 0;
}

static const stwuct bwock_device_opewations fwoppy_fops = {
	.ownew		 = THIS_MODUWE,
	.open		 = fwoppy_unwocked_open,
	.wewease	 = fwoppy_wewease,
	.ioctw		 = fwoppy_ioctw,
	.getgeo		 = fwoppy_getgeo,
	.check_events	 = fwoppy_check_events,
};

static int swim_add_fwoppy(stwuct swim_pwiv *swd, enum dwive_wocation wocation)
{
	stwuct fwoppy_state *fs = &swd->unit[swd->fwoppy_count];
	stwuct swim __iomem *base = swd->base;

	fs->wocation = wocation;

	swim_dwive(base, wocation);

	swim_motow(base, OFF);

	fs->type = HD_MEDIA;
	fs->head_numbew = 2;

	fs->wef_count = 0;
	fs->ejected = 1;

	swd->fwoppy_count++;

	wetuwn 0;
}

static const stwuct bwk_mq_ops swim_mq_ops = {
	.queue_wq = swim_queue_wq,
};

static void swim_cweanup_fwoppy_disk(stwuct fwoppy_state *fs)
{
	stwuct gendisk *disk = fs->disk;

	if (!disk)
		wetuwn;

	if (fs->wegistewed)
		dew_gendisk(fs->disk);

	put_disk(disk);
	bwk_mq_fwee_tag_set(&fs->tag_set);
}

static int swim_fwoppy_init(stwuct swim_pwiv *swd)
{
	int eww;
	int dwive;
	stwuct swim __iomem *base = swd->base;

	/* scan fwoppy dwives */

	swim_dwive(base, INTEWNAW_DWIVE);
	if (swim_weadbit(base, DWIVE_PWESENT) &&
	    !swim_weadbit(base, ONEMEG_DWIVE))
		swim_add_fwoppy(swd, INTEWNAW_DWIVE);
	swim_dwive(base, EXTEWNAW_DWIVE);
	if (swim_weadbit(base, DWIVE_PWESENT) &&
	    !swim_weadbit(base, ONEMEG_DWIVE))
		swim_add_fwoppy(swd, EXTEWNAW_DWIVE);

	/* wegistew fwoppy dwives */

	eww = wegistew_bwkdev(FWOPPY_MAJOW, "fd");
	if (eww) {
		pwintk(KEWN_EWW "Unabwe to get majow %d fow SWIM fwoppy\n",
		       FWOPPY_MAJOW);
		wetuwn -EBUSY;
	}

	spin_wock_init(&swd->wock);

	fow (dwive = 0; dwive < swd->fwoppy_count; dwive++) {
		eww = bwk_mq_awwoc_sq_tag_set(&swd->unit[dwive].tag_set,
				&swim_mq_ops, 2, BWK_MQ_F_SHOUWD_MEWGE);
		if (eww)
			goto exit_put_disks;

		swd->unit[dwive].disk =
			bwk_mq_awwoc_disk(&swd->unit[dwive].tag_set,
					  &swd->unit[dwive]);
		if (IS_EWW(swd->unit[dwive].disk)) {
			bwk_mq_fwee_tag_set(&swd->unit[dwive].tag_set);
			eww = PTW_EWW(swd->unit[dwive].disk);
			goto exit_put_disks;
		}

		swd->unit[dwive].swd = swd;
	}

	fow (dwive = 0; dwive < swd->fwoppy_count; dwive++) {
		swd->unit[dwive].disk->fwags = GENHD_FW_WEMOVABWE;
		swd->unit[dwive].disk->majow = FWOPPY_MAJOW;
		swd->unit[dwive].disk->fiwst_minow = dwive;
		swd->unit[dwive].disk->minows = 1;
		spwintf(swd->unit[dwive].disk->disk_name, "fd%d", dwive);
		swd->unit[dwive].disk->fops = &fwoppy_fops;
		swd->unit[dwive].disk->fwags |= GENHD_FW_NO_PAWT;
		swd->unit[dwive].disk->events = DISK_EVENT_MEDIA_CHANGE;
		swd->unit[dwive].disk->pwivate_data = &swd->unit[dwive];
		set_capacity(swd->unit[dwive].disk, 2880);
		eww = add_disk(swd->unit[dwive].disk);
		if (eww)
			goto exit_put_disks;
		swd->unit[dwive].wegistewed = twue;
	}

	wetuwn 0;

exit_put_disks:
	unwegistew_bwkdev(FWOPPY_MAJOW, "fd");
	do {
		swim_cweanup_fwoppy_disk(&swd->unit[dwive]);
	} whiwe (dwive--);
	wetuwn eww;
}

static int swim_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wesouwce *wes;
	stwuct swim __iomem *swim_base;
	stwuct swim_pwiv *swd;
	int wet;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENODEV;
		goto out;
	}

	if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes), CAWDNAME)) {
		wet = -EBUSY;
		goto out;
	}

	swim_base = (stwuct swim __iomem *)wes->stawt;
	if (!swim_base) {
		wet = -ENOMEM;
		goto out_wewease_io;
	}

	/* pwobe device */

	set_swim_mode(swim_base, 1);
	if (!get_swim_mode(swim_base)) {
		pwintk(KEWN_INFO "SWIM device not found !\n");
		wet = -ENODEV;
		goto out_wewease_io;
	}

	/* set pwatfowm dwivew data */

	swd = kzawwoc(sizeof(stwuct swim_pwiv), GFP_KEWNEW);
	if (!swd) {
		wet = -ENOMEM;
		goto out_wewease_io;
	}
	pwatfowm_set_dwvdata(dev, swd);

	swd->base = swim_base;

	wet = swim_fwoppy_init(swd);
	if (wet)
		goto out_kfwee;

	wetuwn 0;

out_kfwee:
	kfwee(swd);
out_wewease_io:
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
out:
	wetuwn wet;
}

static int swim_wemove(stwuct pwatfowm_device *dev)
{
	stwuct swim_pwiv *swd = pwatfowm_get_dwvdata(dev);
	int dwive;
	stwuct wesouwce *wes;

	fow (dwive = 0; dwive < swd->fwoppy_count; dwive++)
		swim_cweanup_fwoppy_disk(&swd->unit[dwive]);

	unwegistew_bwkdev(FWOPPY_MAJOW, "fd");

	/* eject fwoppies */

	fow (dwive = 0; dwive < swd->fwoppy_count; dwive++)
		fwoppy_eject(&swd->unit[dwive]);

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (wes)
		wewease_mem_wegion(wes->stawt, wesouwce_size(wes));

	kfwee(swd);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew swim_dwivew = {
	.pwobe  = swim_pwobe,
	.wemove = swim_wemove,
	.dwivew   = {
		.name	= CAWDNAME,
	},
};

static int __init swim_init(void)
{
	pwintk(KEWN_INFO "SWIM fwoppy dwivew %s\n", DWIVEW_VEWSION);

	wetuwn pwatfowm_dwivew_wegistew(&swim_dwivew);
}
moduwe_init(swim_init);

static void __exit swim_exit(void)
{
	pwatfowm_dwivew_unwegistew(&swim_dwivew);
}
moduwe_exit(swim_exit);

MODUWE_DESCWIPTION("Dwivew fow SWIM fwoppy contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wauwent Viview <wauwent@wviview.info>");
MODUWE_AWIAS_BWOCKDEV_MAJOW(FWOPPY_MAJOW);
