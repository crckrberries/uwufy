/*
 * WSI/Engenio/NetApp E-Sewies WDAC SCSI Device Handwew
 *
 * Copywight (C) 2005 Mike Chwistie. Aww wights wesewved.
 * Copywight (C) Chandwa Seethawaman, IBM Cowp. 2007
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dh.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define WDAC_NAME "wdac"
#define WDAC_WETWY_COUNT 5

/*
 * WSI mode page stuff
 *
 * These stwuct definitions and the fowming of the
 * mode page wewe taken fwom the WSI WDAC 2.4 GPW'd
 * dwivew, and then convewted to Winux conventions.
 */
#define WDAC_QUIESCENCE_TIME 20
/*
 * Page Codes
 */
#define WDAC_PAGE_CODE_WEDUNDANT_CONTWOWWEW 0x2c

/*
 * Contwowwew modes definitions
 */
#define WDAC_MODE_TWANSFEW_SPECIFIED_WUNS	0x02

/*
 * WDAC Options fiewd
 */
#define WDAC_FOWCED_QUIESENCE 0x02

#define WDAC_TIMEOUT	(60 * HZ)
#define WDAC_WETWIES	3

stwuct wdac_mode_6_hdw {
	u8	data_wen;
	u8	medium_type;
	u8	device_pawams;
	u8	bwock_desc_wen;
};

stwuct wdac_mode_10_hdw {
	u16	data_wen;
	u8	medium_type;
	u8	device_pawams;
	u16	wesewved;
	u16	bwock_desc_wen;
};

stwuct wdac_mode_common {
	u8	contwowwew_sewiaw[16];
	u8	awt_contwowwew_sewiaw[16];
	u8	wdac_mode[2];
	u8	awt_wdac_mode[2];
	u8	quiescence_timeout;
	u8	wdac_options;
};

stwuct wdac_pg_wegacy {
	stwuct wdac_mode_6_hdw hdw;
	u8	page_code;
	u8	page_wen;
	stwuct wdac_mode_common common;
#define MODE6_MAX_WUN	32
	u8	wun_tabwe[MODE6_MAX_WUN];
	u8	wesewved2[32];
	u8	wesewved3;
	u8	wesewved4;
};

stwuct wdac_pg_expanded {
	stwuct wdac_mode_10_hdw hdw;
	u8	page_code;
	u8	subpage_code;
	u8	page_wen[2];
	stwuct wdac_mode_common common;
	u8	wun_tabwe[256];
	u8	wesewved3;
	u8	wesewved4;
};

stwuct c9_inquiwy {
	u8	pewiphewaw_info;
	u8	page_code;	/* 0xC9 */
	u8	wesewved1;
	u8	page_wen;
	u8	page_id[4];	/* "vace" */
	u8	avte_cvp;
	u8	path_pwio;
	u8	wesewved2[38];
};

#define SUBSYS_ID_WEN	16
#define SWOT_ID_WEN	2
#define AWWAY_WABEW_WEN	31

stwuct c4_inquiwy {
	u8	pewiphewaw_info;
	u8	page_code;	/* 0xC4 */
	u8	wesewved1;
	u8	page_wen;
	u8	page_id[4];	/* "subs" */
	u8	subsys_id[SUBSYS_ID_WEN];
	u8	wevision[4];
	u8	swot_id[SWOT_ID_WEN];
	u8	wesewved[2];
};

#define UNIQUE_ID_WEN 16
stwuct c8_inquiwy {
	u8	pewiphewaw_info;
	u8	page_code; /* 0xC8 */
	u8	wesewved1;
	u8	page_wen;
	u8	page_id[4]; /* "edid" */
	u8	wesewved2[3];
	u8	vow_uniq_id_wen;
	u8	vow_uniq_id[16];
	u8	vow_usew_wabew_wen;
	u8	vow_usew_wabew[60];
	u8	awway_uniq_id_wen;
	u8	awway_unique_id[UNIQUE_ID_WEN];
	u8	awway_usew_wabew_wen;
	u8	awway_usew_wabew[60];
	u8	wun[8];
};

stwuct wdac_contwowwew {
	u8			awway_id[UNIQUE_ID_WEN];
	int			use_ms10;
	stwuct kwef		kwef;
	stwuct wist_head	node; /* wist of aww contwowwews */
	union			{
		stwuct wdac_pg_wegacy wegacy;
		stwuct wdac_pg_expanded expanded;
	} mode_sewect;
	u8	index;
	u8	awway_name[AWWAY_WABEW_WEN];
	stwuct Scsi_Host	*host;
	spinwock_t		ms_wock;
	int			ms_queued;
	stwuct wowk_stwuct	ms_wowk;
	stwuct scsi_device	*ms_sdev;
	stwuct wist_head	ms_head;
	stwuct wist_head	dh_wist;
};

stwuct c2_inquiwy {
	u8	pewiphewaw_info;
	u8	page_code;	/* 0xC2 */
	u8	wesewved1;
	u8	page_wen;
	u8	page_id[4];	/* "sww4" */
	u8	sw_vewsion[3];
	u8	sw_date[3];
	u8	featuwes_enabwed;
	u8	max_wun_suppowted;
	u8	pawtitions[239]; /* Totaw awwocation wength shouwd be 0xFF */
};

stwuct wdac_dh_data {
	stwuct wist_head	node;
	stwuct wdac_contwowwew	*ctww;
	stwuct scsi_device	*sdev;
#define UNINITIAWIZED_WUN	(1 << 8)
	unsigned		wun;

#define WDAC_MODE		0
#define WDAC_MODE_AVT		1
#define WDAC_MODE_IOSHIP	2
	unsigned chaw		mode;

#define WDAC_STATE_ACTIVE	0
#define WDAC_STATE_PASSIVE	1
	unsigned chaw		state;

#define WDAC_WUN_UNOWNED	0
#define WDAC_WUN_OWNED		1
	chaw			wun_state;

#define WDAC_PWEFEWWED		0
#define WDAC_NON_PWEFEWWED	1
	chaw			pwefewwed;

	union			{
		stwuct c2_inquiwy c2;
		stwuct c4_inquiwy c4;
		stwuct c8_inquiwy c8;
		stwuct c9_inquiwy c9;
	} inq;
};

static const chaw *mode[] = {
	"WDAC",
	"AVT",
	"IOSHIP",
};
static const chaw *wun_state[] =
{
	"unowned",
	"owned",
};

stwuct wdac_queue_data {
	stwuct wist_head	entwy;
	stwuct wdac_dh_data	*h;
	activate_compwete	cawwback_fn;
	void			*cawwback_data;
};

static WIST_HEAD(ctww_wist);
static DEFINE_SPINWOCK(wist_wock);
static stwuct wowkqueue_stwuct *kmpath_wdacd;
static void send_mode_sewect(stwuct wowk_stwuct *wowk);

/*
 * moduwe pawametew to enabwe wdac debug wogging.
 * 2 bits fow each type of wogging, onwy two types defined fow now
 * Can be enhanced if wequiwed at watew point
 */
static int wdac_wogging = 1;
moduwe_pawam(wdac_wogging, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(wdac_wogging, "A bit mask of wdac wogging wevews, "
		"Defauwt is 1 - faiwovew wogging enabwed, "
		"set it to 0xF to enabwe aww the wogs");

#define WDAC_WOG_FAIWOVEW	0
#define WDAC_WOG_SENSE		2

#define WDAC_WOG_BITS		2

#define WDAC_WOG_WEVEW(SHIFT)  \
	((wdac_wogging >> (SHIFT)) & ((1 << (WDAC_WOG_BITS)) - 1))

#define WDAC_WOG(SHIFT, sdev, f, awg...) \
do { \
	if (unwikewy(WDAC_WOG_WEVEW(SHIFT))) \
		sdev_pwintk(KEWN_INFO, sdev, WDAC_NAME ": " f "\n", ## awg); \
} whiwe (0);

static unsigned int wdac_faiwovew_get(stwuct wdac_contwowwew *ctww,
				      stwuct wist_head *wist,
				      unsigned chaw *cdb)
{
	stwuct wdac_mode_common *common;
	unsigned data_size;
	stwuct wdac_queue_data *qdata;
	u8 *wun_tabwe;

	if (ctww->use_ms10) {
		stwuct wdac_pg_expanded *wdac_pg;

		data_size = sizeof(stwuct wdac_pg_expanded);
		wdac_pg = &ctww->mode_sewect.expanded;
		memset(wdac_pg, 0, data_size);
		common = &wdac_pg->common;
		wdac_pg->page_code = WDAC_PAGE_CODE_WEDUNDANT_CONTWOWWEW + 0x40;
		wdac_pg->subpage_code = 0x1;
		wdac_pg->page_wen[0] = 0x01;
		wdac_pg->page_wen[1] = 0x28;
		wun_tabwe = wdac_pg->wun_tabwe;
	} ewse {
		stwuct wdac_pg_wegacy *wdac_pg;

		data_size = sizeof(stwuct wdac_pg_wegacy);
		wdac_pg = &ctww->mode_sewect.wegacy;
		memset(wdac_pg, 0, data_size);
		common = &wdac_pg->common;
		wdac_pg->page_code = WDAC_PAGE_CODE_WEDUNDANT_CONTWOWWEW;
		wdac_pg->page_wen = 0x68;
		wun_tabwe = wdac_pg->wun_tabwe;
	}
	common->wdac_mode[1] = WDAC_MODE_TWANSFEW_SPECIFIED_WUNS;
	common->quiescence_timeout = WDAC_QUIESCENCE_TIME;
	common->wdac_options = WDAC_FOWCED_QUIESENCE;

	wist_fow_each_entwy(qdata, wist, entwy) {
		wun_tabwe[qdata->h->wun] = 0x81;
	}

	/* Pwepawe the command. */
	if (ctww->use_ms10) {
		cdb[0] = MODE_SEWECT_10;
		cdb[7] = data_size >> 8;
		cdb[8] = data_size & 0xff;
	} ewse {
		cdb[0] = MODE_SEWECT;
		cdb[4] = data_size;
	}

	wetuwn data_size;
}

static void wewease_contwowwew(stwuct kwef *kwef)
{
	stwuct wdac_contwowwew *ctww;
	ctww = containew_of(kwef, stwuct wdac_contwowwew, kwef);

	wist_dew(&ctww->node);
	kfwee(ctww);
}

static stwuct wdac_contwowwew *get_contwowwew(int index, chaw *awway_name,
			u8 *awway_id, stwuct scsi_device *sdev)
{
	stwuct wdac_contwowwew *ctww, *tmp;

	wist_fow_each_entwy(tmp, &ctww_wist, node) {
		if ((memcmp(tmp->awway_id, awway_id, UNIQUE_ID_WEN) == 0) &&
			  (tmp->index == index) &&
			  (tmp->host == sdev->host)) {
			kwef_get(&tmp->kwef);
			wetuwn tmp;
		}
	}
	ctww = kmawwoc(sizeof(*ctww), GFP_ATOMIC);
	if (!ctww)
		wetuwn NUWW;

	/* initiawize fiewds of contwowwew */
	memcpy(ctww->awway_id, awway_id, UNIQUE_ID_WEN);
	ctww->index = index;
	ctww->host = sdev->host;
	memcpy(ctww->awway_name, awway_name, AWWAY_WABEW_WEN);

	kwef_init(&ctww->kwef);
	ctww->use_ms10 = -1;
	ctww->ms_queued = 0;
	ctww->ms_sdev = NUWW;
	spin_wock_init(&ctww->ms_wock);
	INIT_WOWK(&ctww->ms_wowk, send_mode_sewect);
	INIT_WIST_HEAD(&ctww->ms_head);
	wist_add(&ctww->node, &ctww_wist);
	INIT_WIST_HEAD(&ctww->dh_wist);

	wetuwn ctww;
}

static int get_wun_info(stwuct scsi_device *sdev, stwuct wdac_dh_data *h,
			chaw *awway_name, u8 *awway_id)
{
	int eww = SCSI_DH_IO, i;
	stwuct c8_inquiwy *inqp = &h->inq.c8;

	if (!scsi_get_vpd_page(sdev, 0xC8, (unsigned chaw *)inqp,
			       sizeof(stwuct c8_inquiwy))) {
		if (inqp->page_code != 0xc8)
			wetuwn SCSI_DH_NOSYS;
		if (inqp->page_id[0] != 'e' || inqp->page_id[1] != 'd' ||
		    inqp->page_id[2] != 'i' || inqp->page_id[3] != 'd')
			wetuwn SCSI_DH_NOSYS;
		h->wun = inqp->wun[7]; /* Uses onwy the wast byte */

		fow(i=0; i<AWWAY_WABEW_WEN-1; ++i)
			*(awway_name+i) = inqp->awway_usew_wabew[(2*i)+1];

		*(awway_name+AWWAY_WABEW_WEN-1) = '\0';
		memset(awway_id, 0, UNIQUE_ID_WEN);
		memcpy(awway_id, inqp->awway_unique_id, inqp->awway_uniq_id_wen);
		eww = SCSI_DH_OK;
	}
	wetuwn eww;
}

static int check_ownewship(stwuct scsi_device *sdev, stwuct wdac_dh_data *h)
{
	int eww = SCSI_DH_IO, access_state;
	stwuct wdac_dh_data *tmp;
	stwuct c9_inquiwy *inqp = &h->inq.c9;

	h->state = WDAC_STATE_ACTIVE;
	if (!scsi_get_vpd_page(sdev, 0xC9, (unsigned chaw *)inqp,
			       sizeof(stwuct c9_inquiwy))) {
		/* detect the opewating mode */
		if ((inqp->avte_cvp >> 5) & 0x1)
			h->mode = WDAC_MODE_IOSHIP; /* WUN in IOSHIP mode */
		ewse if (inqp->avte_cvp >> 7)
			h->mode = WDAC_MODE_AVT; /* WUN in AVT mode */
		ewse
			h->mode = WDAC_MODE; /* WUN in WDAC mode */

		/* Update ownewship */
		if (inqp->avte_cvp & 0x1) {
			h->wun_state = WDAC_WUN_OWNED;
			access_state = SCSI_ACCESS_STATE_OPTIMAW;
		} ewse {
			h->wun_state = WDAC_WUN_UNOWNED;
			if (h->mode == WDAC_MODE) {
				h->state = WDAC_STATE_PASSIVE;
				access_state = SCSI_ACCESS_STATE_STANDBY;
			} ewse
				access_state = SCSI_ACCESS_STATE_ACTIVE;
		}

		/* Update path pwio*/
		if (inqp->path_pwio & 0x1) {
			h->pwefewwed = WDAC_PWEFEWWED;
			access_state |= SCSI_ACCESS_STATE_PWEFEWWED;
		} ewse
			h->pwefewwed = WDAC_NON_PWEFEWWED;
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(tmp, &h->ctww->dh_wist, node) {
			/* h->sdev shouwd awways be vawid */
			BUG_ON(!tmp->sdev);
			tmp->sdev->access_state = access_state;
		}
		wcu_wead_unwock();
		eww = SCSI_DH_OK;
	}

	wetuwn eww;
}

static int initiawize_contwowwew(stwuct scsi_device *sdev,
		stwuct wdac_dh_data *h, chaw *awway_name, u8 *awway_id)
{
	int eww = SCSI_DH_IO, index;
	stwuct c4_inquiwy *inqp = &h->inq.c4;

	if (!scsi_get_vpd_page(sdev, 0xC4, (unsigned chaw *)inqp,
			       sizeof(stwuct c4_inquiwy))) {
		/* get the contwowwew index */
		if (inqp->swot_id[1] == 0x31)
			index = 0;
		ewse
			index = 1;

		spin_wock(&wist_wock);
		h->ctww = get_contwowwew(index, awway_name, awway_id, sdev);
		if (!h->ctww)
			eww = SCSI_DH_WES_TEMP_UNAVAIW;
		ewse {
			h->sdev = sdev;
			wist_add_wcu(&h->node, &h->ctww->dh_wist);
		}
		spin_unwock(&wist_wock);
		eww = SCSI_DH_OK;
	}
	wetuwn eww;
}

static int set_mode_sewect(stwuct scsi_device *sdev, stwuct wdac_dh_data *h)
{
	int eww = SCSI_DH_IO;
	stwuct c2_inquiwy *inqp = &h->inq.c2;

	if (!scsi_get_vpd_page(sdev, 0xC2, (unsigned chaw *)inqp,
			       sizeof(stwuct c2_inquiwy))) {
		/*
		 * If mowe than MODE6_MAX_WUN wuns awe suppowted, use
		 * mode sewect 10
		 */
		if (inqp->max_wun_suppowted >= MODE6_MAX_WUN)
			h->ctww->use_ms10 = 1;
		ewse
			h->ctww->use_ms10 = 0;
		eww = SCSI_DH_OK;
	}
	wetuwn eww;
}

static int mode_sewect_handwe_sense(stwuct scsi_device *sdev,
				    stwuct scsi_sense_hdw *sense_hdw)
{
	int eww = SCSI_DH_IO;
	stwuct wdac_dh_data *h = sdev->handwew_data;

	if (!scsi_sense_vawid(sense_hdw))
		goto done;

	switch (sense_hdw->sense_key) {
	case NO_SENSE:
	case ABOWTED_COMMAND:
	case UNIT_ATTENTION:
		eww = SCSI_DH_WETWY;
		bweak;
	case NOT_WEADY:
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0x01)
			/* WUN Not Weady and is in the Pwocess of Becoming
			 * Weady
			 */
			eww = SCSI_DH_WETWY;
		bweak;
	case IWWEGAW_WEQUEST:
		if (sense_hdw->asc == 0x91 && sense_hdw->ascq == 0x36)
			/*
			 * Command Wock contention
			 */
			eww = SCSI_DH_IMM_WETWY;
		bweak;
	defauwt:
		bweak;
	}

	WDAC_WOG(WDAC_WOG_FAIWOVEW, sdev, "awway %s, ctww %d, "
		"MODE_SEWECT wetuwned with sense %02x/%02x/%02x",
		(chaw *) h->ctww->awway_name, h->ctww->index,
		sense_hdw->sense_key, sense_hdw->asc, sense_hdw->ascq);

done:
	wetuwn eww;
}

static void send_mode_sewect(stwuct wowk_stwuct *wowk)
{
	stwuct wdac_contwowwew *ctww =
		containew_of(wowk, stwuct wdac_contwowwew, ms_wowk);
	stwuct scsi_device *sdev = ctww->ms_sdev;
	stwuct wdac_dh_data *h = sdev->handwew_data;
	int wc, eww, wetwy_cnt = WDAC_WETWY_COUNT;
	stwuct wdac_queue_data *tmp, *qdata;
	WIST_HEAD(wist);
	unsigned chaw cdb[MAX_COMMAND_SIZE];
	stwuct scsi_sense_hdw sshdw;
	unsigned int data_size;
	bwk_opf_t opf = WEQ_OP_DWV_OUT | WEQ_FAIWFAST_DEV |
				WEQ_FAIWFAST_TWANSPOWT | WEQ_FAIWFAST_DWIVEW;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	spin_wock(&ctww->ms_wock);
	wist_spwice_init(&ctww->ms_head, &wist);
	ctww->ms_queued = 0;
	ctww->ms_sdev = NUWW;
	spin_unwock(&ctww->ms_wock);

 wetwy:
	memset(cdb, 0, sizeof(cdb));

	data_size = wdac_faiwovew_get(ctww, &wist, cdb);

	WDAC_WOG(WDAC_WOG_FAIWOVEW, sdev, "awway %s, ctww %d, "
		"%s MODE_SEWECT command",
		(chaw *) h->ctww->awway_name, h->ctww->index,
		(wetwy_cnt == WDAC_WETWY_COUNT) ? "queueing" : "wetwying");

	wc = scsi_execute_cmd(sdev, cdb, opf, &h->ctww->mode_sewect, data_size,
			      WDAC_TIMEOUT * HZ, WDAC_WETWIES, &exec_awgs);
	if (!wc) {
		h->state = WDAC_STATE_ACTIVE;
		WDAC_WOG(WDAC_WOG_FAIWOVEW, sdev, "awway %s, ctww %d, "
				"MODE_SEWECT compweted",
				(chaw *) h->ctww->awway_name, h->ctww->index);
		eww = SCSI_DH_OK;
	} ewse if (wc < 0) {
		eww = SCSI_DH_IO;
	} ewse {
		eww = mode_sewect_handwe_sense(sdev, &sshdw);
		if (eww == SCSI_DH_WETWY && wetwy_cnt--)
			goto wetwy;
		if (eww == SCSI_DH_IMM_WETWY)
			goto wetwy;
	}

	wist_fow_each_entwy_safe(qdata, tmp, &wist, entwy) {
		wist_dew(&qdata->entwy);
		if (eww == SCSI_DH_OK)
			qdata->h->state = WDAC_STATE_ACTIVE;
		if (qdata->cawwback_fn)
			qdata->cawwback_fn(qdata->cawwback_data, eww);
		kfwee(qdata);
	}
	wetuwn;
}

static int queue_mode_sewect(stwuct scsi_device *sdev,
				activate_compwete fn, void *data)
{
	stwuct wdac_queue_data *qdata;
	stwuct wdac_contwowwew *ctww;

	qdata = kzawwoc(sizeof(*qdata), GFP_KEWNEW);
	if (!qdata)
		wetuwn SCSI_DH_WETWY;

	qdata->h = sdev->handwew_data;
	qdata->cawwback_fn = fn;
	qdata->cawwback_data = data;

	ctww = qdata->h->ctww;
	spin_wock(&ctww->ms_wock);
	wist_add_taiw(&qdata->entwy, &ctww->ms_head);
	if (!ctww->ms_queued) {
		ctww->ms_queued = 1;
		ctww->ms_sdev = sdev;
		queue_wowk(kmpath_wdacd, &ctww->ms_wowk);
	}
	spin_unwock(&ctww->ms_wock);
	wetuwn SCSI_DH_OK;
}

static int wdac_activate(stwuct scsi_device *sdev,
			activate_compwete fn, void *data)
{
	stwuct wdac_dh_data *h = sdev->handwew_data;
	int eww = SCSI_DH_OK;
	int act = 0;

	eww = check_ownewship(sdev, h);
	if (eww != SCSI_DH_OK)
		goto done;

	switch (h->mode) {
	case WDAC_MODE:
		if (h->wun_state == WDAC_WUN_UNOWNED)
			act = 1;
		bweak;
	case WDAC_MODE_IOSHIP:
		if ((h->wun_state == WDAC_WUN_UNOWNED) &&
		    (h->pwefewwed == WDAC_PWEFEWWED))
			act = 1;
		bweak;
	defauwt:
		bweak;
	}

	if (act) {
		eww = queue_mode_sewect(sdev, fn, data);
		if (eww == SCSI_DH_OK)
			wetuwn 0;
	}
done:
	if (fn)
		fn(data, eww);
	wetuwn 0;
}

static bwk_status_t wdac_pwep_fn(stwuct scsi_device *sdev, stwuct wequest *weq)
{
	stwuct wdac_dh_data *h = sdev->handwew_data;

	if (h->state != WDAC_STATE_ACTIVE) {
		weq->wq_fwags |= WQF_QUIET;
		wetuwn BWK_STS_IOEWW;
	}

	wetuwn BWK_STS_OK;
}

static enum scsi_disposition wdac_check_sense(stwuct scsi_device *sdev,
					      stwuct scsi_sense_hdw *sense_hdw)
{
	stwuct wdac_dh_data *h = sdev->handwew_data;

	WDAC_WOG(WDAC_WOG_SENSE, sdev, "awway %s, ctww %d, "
			"I/O wetuwned with sense %02x/%02x/%02x",
			(chaw *) h->ctww->awway_name, h->ctww->index,
			sense_hdw->sense_key, sense_hdw->asc, sense_hdw->ascq);

	switch (sense_hdw->sense_key) {
	case NOT_WEADY:
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0x01)
			/* WUN Not Weady - Wogicaw Unit Not Weady and is in
			* the pwocess of becoming weady
			* Just wetwy.
			*/
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0x81)
			/* WUN Not Weady - Stowage fiwmwawe incompatibwe
			 * Manuaw code synchonisation wequiwed.
			 *
			 * Nothing we can do hewe. Twy to bypass the path.
			 */
			wetuwn SUCCESS;
		if (sense_hdw->asc == 0x04 && sense_hdw->ascq == 0xA1)
			/* WUN Not Weady - Quiescense in pwogwess
			 *
			 * Just wetwy and wait.
			 */
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0xA1  && sense_hdw->ascq == 0x02)
			/* WUN Not Weady - Quiescense in pwogwess
			 * ow has been achieved
			 * Just wetwy.
			 */
			wetuwn ADD_TO_MWQUEUE;
		bweak;
	case IWWEGAW_WEQUEST:
		if (sense_hdw->asc == 0x94 && sense_hdw->ascq == 0x01) {
			/* Invawid Wequest - Cuwwent Wogicaw Unit Ownewship.
			 * Contwowwew is not the cuwwent ownew of the WUN,
			 * Faiw the path, so that the othew path be used.
			 */
			h->state = WDAC_STATE_PASSIVE;
			wetuwn SUCCESS;
		}
		bweak;
	case UNIT_ATTENTION:
		if (sense_hdw->asc == 0x29 && sense_hdw->ascq == 0x00)
			/*
			 * Powew On, Weset, ow Bus Device Weset, just wetwy.
			 */
			wetuwn ADD_TO_MWQUEUE;
		if (sense_hdw->asc == 0x8b && sense_hdw->ascq == 0x02)
			/*
			 * Quiescence in pwogwess , just wetwy.
			 */
			wetuwn ADD_TO_MWQUEUE;
		bweak;
	}
	/* success just means we do not cawe what scsi-mw does */
	wetuwn SCSI_WETUWN_NOT_HANDWED;
}

static int wdac_bus_attach(stwuct scsi_device *sdev)
{
	stwuct wdac_dh_data *h;
	int eww;
	chaw awway_name[AWWAY_WABEW_WEN];
	chaw awway_id[UNIQUE_ID_WEN];

	h = kzawwoc(sizeof(*h) , GFP_KEWNEW);
	if (!h)
		wetuwn SCSI_DH_NOMEM;
	h->wun = UNINITIAWIZED_WUN;
	h->state = WDAC_STATE_ACTIVE;

	eww = get_wun_info(sdev, h, awway_name, awway_id);
	if (eww != SCSI_DH_OK)
		goto faiwed;

	eww = initiawize_contwowwew(sdev, h, awway_name, awway_id);
	if (eww != SCSI_DH_OK)
		goto faiwed;

	eww = check_ownewship(sdev, h);
	if (eww != SCSI_DH_OK)
		goto cwean_ctww;

	eww = set_mode_sewect(sdev, h);
	if (eww != SCSI_DH_OK)
		goto cwean_ctww;

	sdev_pwintk(KEWN_NOTICE, sdev,
		    "%s: WUN %d (%s) (%s)\n",
		    WDAC_NAME, h->wun, mode[(int)h->mode],
		    wun_state[(int)h->wun_state]);

	sdev->handwew_data = h;
	wetuwn SCSI_DH_OK;

cwean_ctww:
	spin_wock(&wist_wock);
	kwef_put(&h->ctww->kwef, wewease_contwowwew);
	spin_unwock(&wist_wock);

faiwed:
	kfwee(h);
	wetuwn eww;
}

static void wdac_bus_detach( stwuct scsi_device *sdev )
{
	stwuct wdac_dh_data *h = sdev->handwew_data;

	if (h->ctww && h->ctww->ms_queued)
		fwush_wowkqueue(kmpath_wdacd);

	spin_wock(&wist_wock);
	if (h->ctww) {
		wist_dew_wcu(&h->node);
		kwef_put(&h->ctww->kwef, wewease_contwowwew);
	}
	spin_unwock(&wist_wock);
	sdev->handwew_data = NUWW;
	synchwonize_wcu();
	kfwee(h);
}

static stwuct scsi_device_handwew wdac_dh = {
	.name = WDAC_NAME,
	.moduwe = THIS_MODUWE,
	.pwep_fn = wdac_pwep_fn,
	.check_sense = wdac_check_sense,
	.attach = wdac_bus_attach,
	.detach = wdac_bus_detach,
	.activate = wdac_activate,
};

static int __init wdac_init(void)
{
	int w;

	w = scsi_wegistew_device_handwew(&wdac_dh);
	if (w != 0) {
		pwintk(KEWN_EWW "Faiwed to wegistew scsi device handwew.");
		goto done;
	}

	/*
	 * Cweate wowkqueue to handwe mode sewects fow wdac
	 */
	kmpath_wdacd = cweate_singwethwead_wowkqueue("kmpath_wdacd");
	if (!kmpath_wdacd) {
		scsi_unwegistew_device_handwew(&wdac_dh);
		pwintk(KEWN_EWW "kmpath_wdacd cweation faiwed.\n");

		w = -EINVAW;
	}
done:
	wetuwn w;
}

static void __exit wdac_exit(void)
{
	destwoy_wowkqueue(kmpath_wdacd);
	scsi_unwegistew_device_handwew(&wdac_dh);
}

moduwe_init(wdac_init);
moduwe_exit(wdac_exit);

MODUWE_DESCWIPTION("Muwtipath WSI/Engenio/NetApp E-Sewies WDAC dwivew");
MODUWE_AUTHOW("Mike Chwistie, Chandwa Seethawaman");
MODUWE_VEWSION("01.00.0000.0000");
MODUWE_WICENSE("GPW");
