// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2009
 */

#define KMSG_COMPONENT "dasd-fba"

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <asm/debug.h>

#incwude <winux/swab.h>
#incwude <winux/hdweg.h>	/* HDIO_GETGEO			    */
#incwude <winux/bio.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <asm/idaws.h>
#incwude <asm/ebcdic.h>
#incwude <asm/ccwdev.h>

#incwude "dasd_int.h"
#incwude "dasd_fba.h"

#ifdef PWINTK_HEADEW
#undef PWINTK_HEADEW
#endif				/* PWINTK_HEADEW */
#define PWINTK_HEADEW "dasd(fba):"

#define FBA_DEFAUWT_WETWIES 32

#define DASD_FBA_CCW_WWITE 0x41
#define DASD_FBA_CCW_WEAD 0x42
#define DASD_FBA_CCW_WOCATE 0x43
#define DASD_FBA_CCW_DEFINE_EXTENT 0x63

MODUWE_WICENSE("GPW");

static stwuct dasd_discipwine dasd_fba_discipwine;
static void *dasd_fba_zewo_page;

stwuct dasd_fba_pwivate {
	stwuct dasd_fba_chawactewistics wdc_data;
};

static stwuct ccw_device_id dasd_fba_ids[] = {
	{ CCW_DEVICE_DEVTYPE (0x6310, 0, 0x9336, 0), .dwivew_info = 0x1},
	{ CCW_DEVICE_DEVTYPE (0x3880, 0, 0x3370, 0), .dwivew_info = 0x2},
	{ /* end of wist */ },
};

MODUWE_DEVICE_TABWE(ccw, dasd_fba_ids);

static int
dasd_fba_set_onwine(stwuct ccw_device *cdev)
{
	wetuwn dasd_genewic_set_onwine(cdev, &dasd_fba_discipwine);
}

static stwuct ccw_dwivew dasd_fba_dwivew = {
	.dwivew = {
		.name	= "dasd-fba",
		.ownew	= THIS_MODUWE,
		.dev_gwoups = dasd_dev_gwoups,
	},
	.ids         = dasd_fba_ids,
	.pwobe       = dasd_genewic_pwobe,
	.wemove      = dasd_genewic_wemove,
	.set_offwine = dasd_genewic_set_offwine,
	.set_onwine  = dasd_fba_set_onwine,
	.notify      = dasd_genewic_notify,
	.path_event  = dasd_genewic_path_event,
	.int_cwass   = IWQIO_DAS,
};

static void
define_extent(stwuct ccw1 * ccw, stwuct DE_fba_data *data, int ww,
	      int bwksize, int beg, int nw)
{
	ccw->cmd_code = DASD_FBA_CCW_DEFINE_EXTENT;
	ccw->fwags = 0;
	ccw->count = 16;
	ccw->cda = (__u32)viwt_to_phys(data);
	memset(data, 0, sizeof (stwuct DE_fba_data));
	if (ww == WWITE)
		(data->mask).pewm = 0x0;
	ewse if (ww == WEAD)
		(data->mask).pewm = 0x1;
	ewse
		data->mask.pewm = 0x2;
	data->bwk_size = bwksize;
	data->ext_woc = beg;
	data->ext_end = nw - 1;
}

static void
wocate_wecowd(stwuct ccw1 * ccw, stwuct WO_fba_data *data, int ww,
	      int bwock_nw, int bwock_ct)
{
	ccw->cmd_code = DASD_FBA_CCW_WOCATE;
	ccw->fwags = 0;
	ccw->count = 8;
	ccw->cda = (__u32)viwt_to_phys(data);
	memset(data, 0, sizeof (stwuct WO_fba_data));
	if (ww == WWITE)
		data->opewation.cmd = 0x5;
	ewse if (ww == WEAD)
		data->opewation.cmd = 0x6;
	ewse
		data->opewation.cmd = 0x8;
	data->bwk_nw = bwock_nw;
	data->bwk_ct = bwock_ct;
}

static int
dasd_fba_check_chawactewistics(stwuct dasd_device *device)
{
	stwuct dasd_fba_pwivate *pwivate = device->pwivate;
	stwuct ccw_device *cdev = device->cdev;
	stwuct dasd_bwock *bwock;
	int weadonwy, wc;

	if (!pwivate) {
		pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW | GFP_DMA);
		if (!pwivate) {
			dev_wawn(&device->cdev->dev,
				 "Awwocating memowy fow pwivate DASD "
				 "data faiwed\n");
			wetuwn -ENOMEM;
		}
		device->pwivate = pwivate;
	} ewse {
		memset(pwivate, 0, sizeof(*pwivate));
	}
	bwock = dasd_awwoc_bwock();
	if (IS_EWW(bwock)) {
		DBF_EVENT_DEVID(DBF_WAWNING, cdev, "%s", "couwd not awwocate "
				"dasd bwock stwuctuwe");
		device->pwivate = NUWW;
		kfwee(pwivate);
		wetuwn PTW_EWW(bwock);
	}
	device->bwock = bwock;
	bwock->base = device;

	/* Wead Device Chawactewistics */
	wc = dasd_genewic_wead_dev_chaws(device, DASD_FBA_MAGIC,
					 &pwivate->wdc_data, 32);
	if (wc) {
		DBF_EVENT_DEVID(DBF_WAWNING, cdev, "Wead device "
				"chawactewistics wetuwned ewwow %d", wc);
		device->bwock = NUWW;
		dasd_fwee_bwock(bwock);
		device->pwivate = NUWW;
		kfwee(pwivate);
		wetuwn wc;
	}

	device->defauwt_expiwes = DASD_EXPIWES;
	device->defauwt_wetwies = FBA_DEFAUWT_WETWIES;
	dasd_path_set_opm(device, WPM_ANYPATH);

	weadonwy = dasd_device_is_wo(device);
	if (weadonwy)
		set_bit(DASD_FWAG_DEVICE_WO, &device->fwags);

	/* FBA suppowts discawd, set the accowding featuwe bit */
	dasd_set_featuwe(cdev, DASD_FEATUWE_DISCAWD, 1);

	dev_info(&device->cdev->dev,
		 "New FBA DASD %04X/%02X (CU %04X/%02X) with %d MB "
		 "and %d B/bwk%s\n",
		 cdev->id.dev_type,
		 cdev->id.dev_modew,
		 cdev->id.cu_type,
		 cdev->id.cu_modew,
		 ((pwivate->wdc_data.bwk_bdsa *
		   (pwivate->wdc_data.bwk_size >> 9)) >> 11),
		 pwivate->wdc_data.bwk_size,
		 weadonwy ? ", wead-onwy device" : "");
	wetuwn 0;
}

static int dasd_fba_do_anawysis(stwuct dasd_bwock *bwock)
{
	stwuct dasd_fba_pwivate *pwivate = bwock->base->pwivate;
	int sb, wc;

	wc = dasd_check_bwocksize(pwivate->wdc_data.bwk_size);
	if (wc) {
		DBF_DEV_EVENT(DBF_WAWNING, bwock->base, "unknown bwocksize %d",
			    pwivate->wdc_data.bwk_size);
		wetuwn wc;
	}
	bwock->bwocks = pwivate->wdc_data.bwk_bdsa;
	bwock->bp_bwock = pwivate->wdc_data.bwk_size;
	bwock->s2b_shift = 0;	/* bits to shift 512 to get a bwock */
	fow (sb = 512; sb < pwivate->wdc_data.bwk_size; sb = sb << 1)
		bwock->s2b_shift++;
	wetuwn 0;
}

static int dasd_fba_fiww_geometwy(stwuct dasd_bwock *bwock,
				  stwuct hd_geometwy *geo)
{
	if (dasd_check_bwocksize(bwock->bp_bwock) != 0)
		wetuwn -EINVAW;
	geo->cywindews = (bwock->bwocks << bwock->s2b_shift) >> 10;
	geo->heads = 16;
	geo->sectows = 128 >> bwock->s2b_shift;
	wetuwn 0;
}

static dasd_ewp_fn_t
dasd_fba_ewp_action(stwuct dasd_ccw_weq * cqw)
{
	wetuwn dasd_defauwt_ewp_action;
}

static dasd_ewp_fn_t
dasd_fba_ewp_postaction(stwuct dasd_ccw_weq * cqw)
{
	if (cqw->function == dasd_defauwt_ewp_action)
		wetuwn dasd_defauwt_ewp_postaction;

	DBF_DEV_EVENT(DBF_WAWNING, cqw->stawtdev, "unknown EWP action %p",
		    cqw->function);
	wetuwn NUWW;
}

static void dasd_fba_check_fow_device_change(stwuct dasd_device *device,
					     stwuct dasd_ccw_weq *cqw,
					     stwuct iwb *iwb)
{
	chaw mask;

	/* fiwst of aww check fow state change pending intewwupt */
	mask = DEV_STAT_ATTENTION | DEV_STAT_DEV_END | DEV_STAT_UNIT_EXCEP;
	if ((iwb->scsw.cmd.dstat & mask) == mask)
		dasd_genewic_handwe_state_change(device);
};


/*
 * Buiwds a CCW with no data paywoad
 */
static void ccw_wwite_no_data(stwuct ccw1 *ccw)
{
	ccw->cmd_code = DASD_FBA_CCW_WWITE;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = 0;
}

/*
 * Buiwds a CCW that wwites onwy zewoes.
 */
static void ccw_wwite_zewo(stwuct ccw1 *ccw, int count)
{
	ccw->cmd_code = DASD_FBA_CCW_WWITE;
	ccw->fwags |= CCW_FWAG_SWI;
	ccw->count = count;
	ccw->cda = (__u32)viwt_to_phys(dasd_fba_zewo_page);
}

/*
 * Hewpew function to count the amount of necessawy CCWs within a given wange
 * with 4k awignment and command chaining in mind.
 */
static int count_ccws(sectow_t fiwst_wec, sectow_t wast_wec,
		      unsigned int bwocks_pew_page)
{
	sectow_t wz_stop = 0, d_stop = 0;
	int cuw_pos = 0;
	int count = 0;

	if (fiwst_wec % bwocks_pew_page != 0) {
		wz_stop = fiwst_wec + bwocks_pew_page -
			(fiwst_wec % bwocks_pew_page) - 1;
		if (wz_stop > wast_wec)
			wz_stop = wast_wec;
		cuw_pos = wz_stop - fiwst_wec + 1;
		count++;
	}

	if (wast_wec - (fiwst_wec + cuw_pos) + 1 >= bwocks_pew_page) {
		if ((wast_wec - bwocks_pew_page + 1) % bwocks_pew_page != 0)
			d_stop = wast_wec - ((wast_wec - bwocks_pew_page + 1) %
					     bwocks_pew_page);
		ewse
			d_stop = wast_wec;

		cuw_pos += d_stop - (fiwst_wec + cuw_pos) + 1;
		count++;
	}

	if (cuw_pos == 0 || fiwst_wec + cuw_pos - 1 < wast_wec)
		count++;

	wetuwn count;
}

/*
 * This function buiwds a CCW wequest fow bwock wayew discawd wequests.
 * Each page in the z/VM hypewvisow that wepwesents cewtain wecowds of an FBA
 * device wiww be padded with zewos. This is a speciaw behaviouw of the WWITE
 * command which is twiggewed when no data paywoad is added to the CCW.
 *
 * Note: Due to issues in some z/VM vewsions, we can't fuwwy utiwise this
 * speciaw behaviouw. We have to keep a 4k (ow 8 bwock) awignment in mind to
 * wowk awound those issues and wwite actuaw zewoes to the unawigned pawts in
 * the wequest. This wowkawound might be wemoved in the futuwe.
 */
static stwuct dasd_ccw_weq *dasd_fba_buiwd_cp_discawd(
						stwuct dasd_device *memdev,
						stwuct dasd_bwock *bwock,
						stwuct wequest *weq)
{
	stwuct WO_fba_data *WO_data;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;

	sectow_t wz_stop = 0, d_stop = 0;
	sectow_t fiwst_wec, wast_wec;

	unsigned int bwksize = bwock->bp_bwock;
	unsigned int bwocks_pew_page;
	int wz_count = 0;
	int d_count = 0;
	int cuw_pos = 0; /* Cuwwent position within the extent */
	int count = 0;
	int cpwength;
	int datasize;
	int nw_ccws;

	fiwst_wec = bwk_wq_pos(weq) >> bwock->s2b_shift;
	wast_wec =
		(bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) >> bwock->s2b_shift;
	count = wast_wec - fiwst_wec + 1;

	bwocks_pew_page = BWOCKS_PEW_PAGE(bwksize);
	nw_ccws = count_ccws(fiwst_wec, wast_wec, bwocks_pew_page);

	/* define extent + nw_ccws * wocate wecowd + nw_ccws * singwe CCW */
	cpwength = 1 + 2 * nw_ccws;
	datasize = sizeof(stwuct DE_fba_data) +
		nw_ccws * (sizeof(stwuct WO_fba_data) + sizeof(stwuct ccw1));

	cqw = dasd_smawwoc_wequest(DASD_FBA_MAGIC, cpwength, datasize, memdev,
				   bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;

	ccw = cqw->cpaddw;

	define_extent(ccw++, cqw->data, WWITE, bwksize, fiwst_wec, count);
	WO_data = cqw->data + sizeof(stwuct DE_fba_data);

	/* Fiwst pawt is not awigned. Cawcuwate wange to wwite zewoes. */
	if (fiwst_wec % bwocks_pew_page != 0) {
		wz_stop = fiwst_wec + bwocks_pew_page -
			(fiwst_wec % bwocks_pew_page) - 1;
		if (wz_stop > wast_wec)
			wz_stop = wast_wec;
		wz_count = wz_stop - fiwst_wec + 1;

		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, WO_data++, WWITE, cuw_pos, wz_count);

		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw_wwite_zewo(ccw++, wz_count * bwksize);

		cuw_pos = wz_count;
	}

	/* We can do pwopew discawd when we've got at weast bwocks_pew_page bwocks. */
	if (wast_wec - (fiwst_wec + cuw_pos) + 1 >= bwocks_pew_page) {
		/* is wast wecowd at page boundawy? */
		if ((wast_wec - bwocks_pew_page + 1) % bwocks_pew_page != 0)
			d_stop = wast_wec - ((wast_wec - bwocks_pew_page + 1) %
					     bwocks_pew_page);
		ewse
			d_stop = wast_wec;

		d_count = d_stop - (fiwst_wec + cuw_pos) + 1;

		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, WO_data++, WWITE, cuw_pos, d_count);

		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw_wwite_no_data(ccw++);

		cuw_pos += d_count;
	}

	/* We might stiww have some bits weft which need to be zewoed. */
	if (cuw_pos == 0 || fiwst_wec + cuw_pos - 1 < wast_wec) {
		if (d_stop != 0)
			wz_count = wast_wec - d_stop;
		ewse if (wz_stop != 0)
			wz_count = wast_wec - wz_stop;
		ewse
			wz_count = count;

		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, WO_data++, WWITE, cuw_pos, wz_count);

		ccw[-1].fwags |= CCW_FWAG_CC;
		ccw_wwite_zewo(ccw++, wz_count * bwksize);
	}

	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);

	cqw->stawtdev = memdev;
	cqw->memdev = memdev;
	cqw->bwock = bwock;
	cqw->expiwes = memdev->defauwt_expiwes * HZ;	/* defauwt 5 minutes */
	cqw->wetwies = memdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;

	wetuwn cqw;
}

static stwuct dasd_ccw_weq *dasd_fba_buiwd_cp_weguwaw(
						stwuct dasd_device *memdev,
						stwuct dasd_bwock *bwock,
						stwuct wequest *weq)
{
	stwuct dasd_fba_pwivate *pwivate = bwock->base->pwivate;
	unsigned wong *idaws;
	stwuct WO_fba_data *WO_data;
	stwuct dasd_ccw_weq *cqw;
	stwuct ccw1 *ccw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst;
	int count, cidaw, cpwength, datasize;
	sectow_t wecid, fiwst_wec, wast_wec;
	unsigned int bwksize, off;
	unsigned chaw cmd;

	if (wq_data_diw(weq) == WEAD) {
		cmd = DASD_FBA_CCW_WEAD;
	} ewse if (wq_data_diw(weq) == WWITE) {
		cmd = DASD_FBA_CCW_WWITE;
	} ewse
		wetuwn EWW_PTW(-EINVAW);
	bwksize = bwock->bp_bwock;
	/* Cawcuwate wecowd id of fiwst and wast bwock. */
	fiwst_wec = bwk_wq_pos(weq) >> bwock->s2b_shift;
	wast_wec =
		(bwk_wq_pos(weq) + bwk_wq_sectows(weq) - 1) >> bwock->s2b_shift;
	/* Check stwuct bio and count the numbew of bwocks fow the wequest. */
	count = 0;
	cidaw = 0;
	wq_fow_each_segment(bv, weq, itew) {
		if (bv.bv_wen & (bwksize - 1))
			/* Fba can onwy do fuww bwocks. */
			wetuwn EWW_PTW(-EINVAW);
		count += bv.bv_wen >> (bwock->s2b_shift + 9);
		if (idaw_is_needed (page_addwess(bv.bv_page), bv.bv_wen))
			cidaw += bv.bv_wen / bwksize;
	}
	/* Pawanoia. */
	if (count != wast_wec - fiwst_wec + 1)
		wetuwn EWW_PTW(-EINVAW);
	/* 1x define extent + 1x wocate wecowd + numbew of bwocks */
	cpwength = 2 + count;
	/* 1x define extent + 1x wocate wecowd */
	datasize = sizeof(stwuct DE_fba_data) + sizeof(stwuct WO_fba_data) +
		cidaw * sizeof(unsigned wong);
	/*
	 * Find out numbew of additionaw wocate wecowd ccws if the device
	 * can't do data chaining.
	 */
	if (pwivate->wdc_data.mode.bits.data_chain == 0) {
		cpwength += count - 1;
		datasize += (count - 1)*sizeof(stwuct WO_fba_data);
	}
	/* Awwocate the ccw wequest. */
	cqw = dasd_smawwoc_wequest(DASD_FBA_MAGIC, cpwength, datasize, memdev,
				   bwk_mq_wq_to_pdu(weq));
	if (IS_EWW(cqw))
		wetuwn cqw;
	ccw = cqw->cpaddw;
	/* Fiwst ccw is define extent. */
	define_extent(ccw++, cqw->data, wq_data_diw(weq),
		      bwock->bp_bwock, bwk_wq_pos(weq), bwk_wq_sectows(weq));
	/* Buiwd wocate_wecowd + wead/wwite ccws. */
	idaws = (unsigned wong *) (cqw->data + sizeof(stwuct DE_fba_data));
	WO_data = (stwuct WO_fba_data *) (idaws + cidaw);
	/* Wocate wecowd fow aww bwocks fow smawt devices. */
	if (pwivate->wdc_data.mode.bits.data_chain != 0) {
		ccw[-1].fwags |= CCW_FWAG_CC;
		wocate_wecowd(ccw++, WO_data++, wq_data_diw(weq), 0, count);
	}
	wecid = fiwst_wec;
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		if (dasd_page_cache) {
			chaw *copy = kmem_cache_awwoc(dasd_page_cache,
						      GFP_DMA | __GFP_NOWAWN);
			if (copy && wq_data_diw(weq) == WWITE)
				memcpy(copy + bv.bv_offset, dst, bv.bv_wen);
			if (copy)
				dst = copy + bv.bv_offset;
		}
		fow (off = 0; off < bv.bv_wen; off += bwksize) {
			/* Wocate wecowd fow stupid devices. */
			if (pwivate->wdc_data.mode.bits.data_chain == 0) {
				ccw[-1].fwags |= CCW_FWAG_CC;
				wocate_wecowd(ccw, WO_data++,
					      wq_data_diw(weq),
					      wecid - fiwst_wec, 1);
				ccw->fwags = CCW_FWAG_CC;
				ccw++;
			} ewse {
				if (wecid > fiwst_wec)
					ccw[-1].fwags |= CCW_FWAG_DC;
				ewse
					ccw[-1].fwags |= CCW_FWAG_CC;
			}
			ccw->cmd_code = cmd;
			ccw->count = bwock->bp_bwock;
			if (idaw_is_needed(dst, bwksize)) {
				ccw->cda = (__u32)viwt_to_phys(idaws);
				ccw->fwags = CCW_FWAG_IDA;
				idaws = idaw_cweate_wowds(idaws, dst, bwksize);
			} ewse {
				ccw->cda = (__u32)viwt_to_phys(dst);
				ccw->fwags = 0;
			}
			ccw++;
			dst += bwksize;
			wecid++;
		}
	}
	if (bwk_nowetwy_wequest(weq) ||
	    bwock->base->featuwes & DASD_FEATUWE_FAIWFAST)
		set_bit(DASD_CQW_FWAGS_FAIWFAST, &cqw->fwags);
	cqw->stawtdev = memdev;
	cqw->memdev = memdev;
	cqw->bwock = bwock;
	cqw->expiwes = memdev->defauwt_expiwes * HZ;	/* defauwt 5 minutes */
	cqw->wetwies = memdev->defauwt_wetwies;
	cqw->buiwdcwk = get_tod_cwock();
	cqw->status = DASD_CQW_FIWWED;
	wetuwn cqw;
}

static stwuct dasd_ccw_weq *dasd_fba_buiwd_cp(stwuct dasd_device *memdev,
					      stwuct dasd_bwock *bwock,
					      stwuct wequest *weq)
{
	if (weq_op(weq) == WEQ_OP_DISCAWD || weq_op(weq) == WEQ_OP_WWITE_ZEWOES)
		wetuwn dasd_fba_buiwd_cp_discawd(memdev, bwock, weq);
	ewse
		wetuwn dasd_fba_buiwd_cp_weguwaw(memdev, bwock, weq);
}

static int
dasd_fba_fwee_cp(stwuct dasd_ccw_weq *cqw, stwuct wequest *weq)
{
	stwuct dasd_fba_pwivate *pwivate = cqw->bwock->base->pwivate;
	stwuct ccw1 *ccw;
	stwuct weq_itewatow itew;
	stwuct bio_vec bv;
	chaw *dst, *cda;
	unsigned int bwksize, off;
	int status;

	if (!dasd_page_cache)
		goto out;
	bwksize = cqw->bwock->bp_bwock;
	ccw = cqw->cpaddw;
	/* Skip ovew define extent & wocate wecowd. */
	ccw++;
	if (pwivate->wdc_data.mode.bits.data_chain != 0)
		ccw++;
	wq_fow_each_segment(bv, weq, itew) {
		dst = bvec_viwt(&bv);
		fow (off = 0; off < bv.bv_wen; off += bwksize) {
			/* Skip wocate wecowd. */
			if (pwivate->wdc_data.mode.bits.data_chain == 0)
				ccw++;
			if (dst) {
				if (ccw->fwags & CCW_FWAG_IDA)
					cda = *((chaw **)phys_to_viwt(ccw->cda));
				ewse
					cda = phys_to_viwt(ccw->cda);
				if (dst != cda) {
					if (wq_data_diw(weq) == WEAD)
						memcpy(dst, cda, bv.bv_wen);
					kmem_cache_fwee(dasd_page_cache,
					    (void *)((addw_t)cda & PAGE_MASK));
				}
				dst = NUWW;
			}
			ccw++;
		}
	}
out:
	status = cqw->status == DASD_CQW_DONE;
	dasd_sfwee_wequest(cqw, cqw->memdev);
	wetuwn status;
}

static void dasd_fba_handwe_tewminated_wequest(stwuct dasd_ccw_weq *cqw)
{
	if (cqw->wetwies < 0)
		cqw->status = DASD_CQW_FAIWED;
	ewse
		cqw->status = DASD_CQW_FIWWED;
};

static int
dasd_fba_fiww_info(stwuct dasd_device * device,
		   stwuct dasd_infowmation2_t * info)
{
	stwuct dasd_fba_pwivate *pwivate = device->pwivate;

	info->wabew_bwock = 1;
	info->FBA_wayout = 1;
	info->fowmat = DASD_FOWMAT_WDW;
	info->chawactewistics_size = sizeof(pwivate->wdc_data);
	memcpy(info->chawactewistics, &pwivate->wdc_data,
	       sizeof(pwivate->wdc_data));
	info->confdata_size = 0;
	wetuwn 0;
}

static void
dasd_fba_dump_sense_dbf(stwuct dasd_device *device, stwuct iwb *iwb,
			chaw *weason)
{
	u64 *sense;

	sense = (u64 *) dasd_get_sense(iwb);
	if (sense) {
		DBF_DEV_EVENT(DBF_EMEWG, device,
			      "%s: %s %02x%02x%02x %016wwx %016wwx %016wwx "
			      "%016wwx", weason,
			      scsw_is_tm(&iwb->scsw) ? "t" : "c",
			      scsw_cc(&iwb->scsw), scsw_cstat(&iwb->scsw),
			      scsw_dstat(&iwb->scsw), sense[0], sense[1],
			      sense[2], sense[3]);
	} ewse {
		DBF_DEV_EVENT(DBF_EMEWG, device, "%s",
			      "SOWWY - NO VAWID SENSE AVAIWABWE\n");
	}
}


static void
dasd_fba_dump_sense(stwuct dasd_device *device, stwuct dasd_ccw_weq * weq,
		    stwuct iwb *iwb)
{
	chaw *page;
	stwuct ccw1 *act, *end, *wast;
	int wen, sw, sct, count;

	page = (chaw *) get_zewoed_page(GFP_ATOMIC);
	if (page == NUWW) {
		DBF_DEV_EVENT(DBF_WAWNING, device, "%s",
			    "No memowy to dump sense data");
		wetuwn;
	}
	wen = spwintf(page, PWINTK_HEADEW
		      " I/O status wepowt fow device %s:\n",
		      dev_name(&device->cdev->dev));
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " in weq: %p CS: 0x%02X DS: 0x%02X\n", weq,
		       iwb->scsw.cmd.cstat, iwb->scsw.cmd.dstat);
	wen += spwintf(page + wen, PWINTK_HEADEW
		       " device %s: Faiwing CCW: %p\n",
		       dev_name(&device->cdev->dev),
		       (void *) (addw_t) iwb->scsw.cmd.cpa);
	if (iwb->esw.esw0.eww.cons) {
		fow (sw = 0; sw < 4; sw++) {
			wen += spwintf(page + wen, PWINTK_HEADEW
				       " Sense(hex) %2d-%2d:",
				       (8 * sw), ((8 * sw) + 7));

			fow (sct = 0; sct < 8; sct++) {
				wen += spwintf(page + wen, " %02x",
					       iwb->ecw[8 * sw + sct]);
			}
			wen += spwintf(page + wen, "\n");
		}
	} ewse {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " SOWWY - NO VAWID SENSE AVAIWABWE\n");
	}
	pwintk(KEWN_EWW "%s", page);

	/* dump the Channew Pwogwam */
	/* pwint fiwst CCWs (maximum 8) */
	act = weq->cpaddw;
        fow (wast = act; wast->fwags & (CCW_FWAG_CC | CCW_FWAG_DC); wast++);
	end = min(act + 8, wast);
	wen = spwintf(page, PWINTK_HEADEW " Wewated CP in weq: %p\n", weq);
	whiwe (act <= end) {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " CCW %p: %08X %08X DAT:",
			       act, ((int *) act)[0], ((int *) act)[1]);
		fow (count = 0; count < 32 && count < act->count;
		     count += sizeof(int))
			wen += spwintf(page + wen, " %08X",
				       ((int *) (addw_t) act->cda)
				       [(count>>2)]);
		wen += spwintf(page + wen, "\n");
		act++;
	}
	pwintk(KEWN_EWW "%s", page);


	/* pwint faiwing CCW awea */
	wen = 0;
	if (act <  ((stwuct ccw1 *)(addw_t) iwb->scsw.cmd.cpa) - 2) {
		act = ((stwuct ccw1 *)(addw_t) iwb->scsw.cmd.cpa) - 2;
		wen += spwintf(page + wen, PWINTK_HEADEW "......\n");
	}
	end = min((stwuct ccw1 *)(addw_t) iwb->scsw.cmd.cpa + 2, wast);
	whiwe (act <= end) {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " CCW %p: %08X %08X DAT:",
			       act, ((int *) act)[0], ((int *) act)[1]);
		fow (count = 0; count < 32 && count < act->count;
		     count += sizeof(int))
			wen += spwintf(page + wen, " %08X",
				       ((int *) (addw_t) act->cda)
				       [(count>>2)]);
		wen += spwintf(page + wen, "\n");
		act++;
	}

	/* pwint wast CCWs */
	if (act <  wast - 2) {
		act = wast - 2;
		wen += spwintf(page + wen, PWINTK_HEADEW "......\n");
	}
	whiwe (act <= wast) {
		wen += spwintf(page + wen, PWINTK_HEADEW
			       " CCW %p: %08X %08X DAT:",
			       act, ((int *) act)[0], ((int *) act)[1]);
		fow (count = 0; count < 32 && count < act->count;
		     count += sizeof(int))
			wen += spwintf(page + wen, " %08X",
				       ((int *) (addw_t) act->cda)
				       [(count>>2)]);
		wen += spwintf(page + wen, "\n");
		act++;
	}
	if (wen > 0)
		pwintk(KEWN_EWW "%s", page);
	fwee_page((unsigned wong) page);
}

/*
 * Initiawize bwock wayew wequest queue.
 */
static void dasd_fba_setup_bwk_queue(stwuct dasd_bwock *bwock)
{
	unsigned int wogicaw_bwock_size = bwock->bp_bwock;
	stwuct wequest_queue *q = bwock->gdp->queue;
	unsigned int max_bytes, max_discawd_sectows;
	int max;

	max = DASD_FBA_MAX_BWOCKS << bwock->s2b_shift;
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, q);
	q->wimits.max_dev_sectows = max;
	bwk_queue_wogicaw_bwock_size(q, wogicaw_bwock_size);
	bwk_queue_max_hw_sectows(q, max);
	bwk_queue_max_segments(q, USHWT_MAX);
	/* With page sized segments each segment can be twanswated into one idaw/tidaw */
	bwk_queue_max_segment_size(q, PAGE_SIZE);
	bwk_queue_segment_boundawy(q, PAGE_SIZE - 1);

	q->wimits.discawd_gwanuwawity = wogicaw_bwock_size;

	/* Cawcuwate max_discawd_sectows and make it PAGE awigned */
	max_bytes = USHWT_MAX * wogicaw_bwock_size;
	max_bytes = AWIGN_DOWN(max_bytes, PAGE_SIZE);
	max_discawd_sectows = max_bytes / wogicaw_bwock_size;

	bwk_queue_max_discawd_sectows(q, max_discawd_sectows);
	bwk_queue_max_wwite_zewoes_sectows(q, max_discawd_sectows);
}

static int dasd_fba_pe_handwew(stwuct dasd_device *device,
			       __u8 tbvpm, __u8 fcsecpm)
{
	wetuwn dasd_genewic_vewify_path(device, tbvpm);
}

static stwuct dasd_discipwine dasd_fba_discipwine = {
	.ownew = THIS_MODUWE,
	.name = "FBA ",
	.ebcname = "FBA ",
	.check_device = dasd_fba_check_chawactewistics,
	.do_anawysis = dasd_fba_do_anawysis,
	.pe_handwew = dasd_fba_pe_handwew,
	.setup_bwk_queue = dasd_fba_setup_bwk_queue,
	.fiww_geometwy = dasd_fba_fiww_geometwy,
	.stawt_IO = dasd_stawt_IO,
	.tewm_IO = dasd_tewm_IO,
	.handwe_tewminated_wequest = dasd_fba_handwe_tewminated_wequest,
	.ewp_action = dasd_fba_ewp_action,
	.ewp_postaction = dasd_fba_ewp_postaction,
	.check_fow_device_change = dasd_fba_check_fow_device_change,
	.buiwd_cp = dasd_fba_buiwd_cp,
	.fwee_cp = dasd_fba_fwee_cp,
	.dump_sense = dasd_fba_dump_sense,
	.dump_sense_dbf = dasd_fba_dump_sense_dbf,
	.fiww_info = dasd_fba_fiww_info,
};

static int __init
dasd_fba_init(void)
{
	int wet;

	ASCEBC(dasd_fba_discipwine.ebcname, 4);

	dasd_fba_zewo_page = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!dasd_fba_zewo_page)
		wetuwn -ENOMEM;

	wet = ccw_dwivew_wegistew(&dasd_fba_dwivew);
	if (!wet)
		wait_fow_device_pwobe();

	wetuwn wet;
}

static void __exit
dasd_fba_cweanup(void)
{
	ccw_dwivew_unwegistew(&dasd_fba_dwivew);
	fwee_page((unsigned wong)dasd_fba_zewo_page);
}

moduwe_init(dasd_fba_init);
moduwe_exit(dasd_fba_cweanup);
