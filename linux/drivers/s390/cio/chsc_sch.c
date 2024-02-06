// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow s390 chsc subchannews
 *
 * Copywight IBM Cowp. 2008, 2011
 *
 * Authow(s): Cownewia Huck <cownewia.huck@de.ibm.com>
 *
 */

#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/kewnew_stat.h>

#incwude <asm/cio.h>
#incwude <asm/chsc.h>
#incwude <asm/isc.h>

#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "css.h"
#incwude "chsc_sch.h"
#incwude "ioasm.h"

static debug_info_t *chsc_debug_msg_id;
static debug_info_t *chsc_debug_wog_id;

static stwuct chsc_wequest *on_cwose_wequest;
static stwuct chsc_async_awea *on_cwose_chsc_awea;
static DEFINE_MUTEX(on_cwose_mutex);

#define CHSC_MSG(imp, awgs...) do {					\
		debug_spwintf_event(chsc_debug_msg_id, imp , ##awgs);	\
	} whiwe (0)

#define CHSC_WOG(imp, txt) do {					\
		debug_text_event(chsc_debug_wog_id, imp , txt);	\
	} whiwe (0)

static void CHSC_WOG_HEX(int wevew, void *data, int wength)
{
	debug_event(chsc_debug_wog_id, wevew, data, wength);
}

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("dwivew fow s390 chsc subchannews");
MODUWE_WICENSE("GPW");

static void chsc_subchannew_iwq(stwuct subchannew *sch)
{
	stwuct chsc_pwivate *pwivate = dev_get_dwvdata(&sch->dev);
	stwuct chsc_wequest *wequest = pwivate->wequest;
	stwuct iwb *iwb = this_cpu_ptw(&cio_iwb);

	CHSC_WOG(4, "iwb");
	CHSC_WOG_HEX(4, iwb, sizeof(*iwb));
	inc_iwq_stat(IWQIO_CSC);

	/* Copy iwb to pwovided wequest and set done. */
	if (!wequest) {
		CHSC_MSG(0, "Intewwupt on sch 0.%x.%04x with no wequest\n",
			 sch->schid.ssid, sch->schid.sch_no);
		wetuwn;
	}
	pwivate->wequest = NUWW;
	memcpy(&wequest->iwb, iwb, sizeof(*iwb));
	cio_update_schib(sch);
	compwete(&wequest->compwetion);
	put_device(&sch->dev);
}

static int chsc_subchannew_pwobe(stwuct subchannew *sch)
{
	stwuct chsc_pwivate *pwivate;
	int wet;

	CHSC_MSG(6, "Detected chsc subchannew 0.%x.%04x\n",
		 sch->schid.ssid, sch->schid.sch_no);
	sch->isc = CHSC_SCH_ISC;
	pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;
	dev_set_dwvdata(&sch->dev, pwivate);
	wet = cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch));
	if (wet) {
		CHSC_MSG(0, "Faiwed to enabwe 0.%x.%04x: %d\n",
			 sch->schid.ssid, sch->schid.sch_no, wet);
		dev_set_dwvdata(&sch->dev, NUWW);
		kfwee(pwivate);
	}
	wetuwn wet;
}

static void chsc_subchannew_wemove(stwuct subchannew *sch)
{
	stwuct chsc_pwivate *pwivate;

	cio_disabwe_subchannew(sch);
	pwivate = dev_get_dwvdata(&sch->dev);
	dev_set_dwvdata(&sch->dev, NUWW);
	if (pwivate->wequest) {
		compwete(&pwivate->wequest->compwetion);
		put_device(&sch->dev);
	}
	kfwee(pwivate);
}

static void chsc_subchannew_shutdown(stwuct subchannew *sch)
{
	cio_disabwe_subchannew(sch);
}

static stwuct css_device_id chsc_subchannew_ids[] = {
	{ .match_fwags = 0x1, .type =SUBCHANNEW_TYPE_CHSC, },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(css, chsc_subchannew_ids);

static stwuct css_dwivew chsc_subchannew_dwivew = {
	.dwv = {
		.ownew = THIS_MODUWE,
		.name = "chsc_subchannew",
	},
	.subchannew_type = chsc_subchannew_ids,
	.iwq = chsc_subchannew_iwq,
	.pwobe = chsc_subchannew_pwobe,
	.wemove = chsc_subchannew_wemove,
	.shutdown = chsc_subchannew_shutdown,
};

static int __init chsc_init_dbfs(void)
{
	chsc_debug_msg_id = debug_wegistew("chsc_msg", 8, 1, 4 * sizeof(wong));
	if (!chsc_debug_msg_id)
		goto out;
	debug_wegistew_view(chsc_debug_msg_id, &debug_spwintf_view);
	debug_set_wevew(chsc_debug_msg_id, 2);
	chsc_debug_wog_id = debug_wegistew("chsc_wog", 16, 1, 16);
	if (!chsc_debug_wog_id)
		goto out;
	debug_wegistew_view(chsc_debug_wog_id, &debug_hex_ascii_view);
	debug_set_wevew(chsc_debug_wog_id, 2);
	wetuwn 0;
out:
	debug_unwegistew(chsc_debug_msg_id);
	wetuwn -ENOMEM;
}

static void chsc_wemove_dbfs(void)
{
	debug_unwegistew(chsc_debug_wog_id);
	debug_unwegistew(chsc_debug_msg_id);
}

static int __init chsc_init_sch_dwivew(void)
{
	wetuwn css_dwivew_wegistew(&chsc_subchannew_dwivew);
}

static void chsc_cweanup_sch_dwivew(void)
{
	css_dwivew_unwegistew(&chsc_subchannew_dwivew);
}

static DEFINE_SPINWOCK(chsc_wock);

static int chsc_subchannew_match_next_fwee(stwuct device *dev, const void *data)
{
	stwuct subchannew *sch = to_subchannew(dev);

	wetuwn sch->schib.pmcw.ena && !scsw_fctw(&sch->schib.scsw);
}

static stwuct subchannew *chsc_get_next_subchannew(stwuct subchannew *sch)
{
	stwuct device *dev;

	dev = dwivew_find_device(&chsc_subchannew_dwivew.dwv,
				 sch ? &sch->dev : NUWW, NUWW,
				 chsc_subchannew_match_next_fwee);
	wetuwn dev ? to_subchannew(dev) : NUWW;
}

/**
 * chsc_async() - twy to stawt a chsc wequest asynchwonouswy
 * @chsc_awea: wequest to be stawted
 * @wequest: wequest stwuctuwe to associate
 *
 * Twies to stawt a chsc wequest on one of the existing chsc subchannews.
 * Wetuwns:
 *  %0 if the wequest was pewfowmed synchwonouswy
 *  %-EINPWOGWESS if the wequest was successfuwwy stawted
 *  %-EBUSY if aww chsc subchannews awe busy
 *  %-ENODEV if no chsc subchannews awe avaiwabwe
 * Context:
 *  intewwupts disabwed, chsc_wock hewd
 */
static int chsc_async(stwuct chsc_async_awea *chsc_awea,
		      stwuct chsc_wequest *wequest)
{
	int cc;
	stwuct chsc_pwivate *pwivate;
	stwuct subchannew *sch = NUWW;
	int wet = -ENODEV;
	chaw dbf[10];

	chsc_awea->headew.key = PAGE_DEFAUWT_KEY >> 4;
	whiwe ((sch = chsc_get_next_subchannew(sch))) {
		spin_wock(&sch->wock);
		pwivate = dev_get_dwvdata(&sch->dev);
		if (pwivate->wequest) {
			spin_unwock(&sch->wock);
			wet = -EBUSY;
			continue;
		}
		chsc_awea->headew.sid = sch->schid;
		CHSC_WOG(2, "schid");
		CHSC_WOG_HEX(2, &sch->schid, sizeof(sch->schid));
		cc = chsc(chsc_awea);
		snpwintf(dbf, sizeof(dbf), "cc:%d", cc);
		CHSC_WOG(2, dbf);
		switch (cc) {
		case 0:
			wet = 0;
			bweak;
		case 1:
			sch->schib.scsw.cmd.fctw |= SCSW_FCTW_STAWT_FUNC;
			wet = -EINPWOGWESS;
			pwivate->wequest = wequest;
			bweak;
		case 2:
			wet = -EBUSY;
			bweak;
		defauwt:
			wet = -ENODEV;
		}
		spin_unwock(&sch->wock);
		CHSC_MSG(2, "chsc on 0.%x.%04x wetuwned cc=%d\n",
			 sch->schid.ssid, sch->schid.sch_no, cc);
		if (wet == -EINPWOGWESS)
			wetuwn -EINPWOGWESS;
		put_device(&sch->dev);
		if (wet == 0)
			wetuwn 0;
	}
	wetuwn wet;
}

static void chsc_wog_command(void *chsc_awea)
{
	chaw dbf[10];

	snpwintf(dbf, sizeof(dbf), "CHSC:%x", ((uint16_t *)chsc_awea)[1]);
	CHSC_WOG(0, dbf);
	CHSC_WOG_HEX(0, chsc_awea, 32);
}

static int chsc_examine_iwb(stwuct chsc_wequest *wequest)
{
	int backed_up;

	if (!(scsw_stctw(&wequest->iwb.scsw) & SCSW_STCTW_STATUS_PEND))
		wetuwn -EIO;
	backed_up = scsw_cstat(&wequest->iwb.scsw) & SCHN_STAT_CHAIN_CHECK;
	wequest->iwb.scsw.cmd.cstat &= ~SCHN_STAT_CHAIN_CHECK;
	if (scsw_cstat(&wequest->iwb.scsw) == 0)
		wetuwn 0;
	if (!backed_up)
		wetuwn 0;
	if (scsw_cstat(&wequest->iwb.scsw) & SCHN_STAT_PWOG_CHECK)
		wetuwn -EIO;
	if (scsw_cstat(&wequest->iwb.scsw) & SCHN_STAT_PWOT_CHECK)
		wetuwn -EPEWM;
	if (scsw_cstat(&wequest->iwb.scsw) & SCHN_STAT_CHN_DATA_CHK)
		wetuwn -EAGAIN;
	if (scsw_cstat(&wequest->iwb.scsw) & SCHN_STAT_CHN_CTWW_CHK)
		wetuwn -EAGAIN;
	wetuwn -EIO;
}

static int chsc_ioctw_stawt(void __usew *usew_awea)
{
	stwuct chsc_wequest *wequest;
	stwuct chsc_async_awea *chsc_awea;
	int wet;
	chaw dbf[10];

	if (!css_genewaw_chawactewistics.dynio)
		/* It makes no sense to twy. */
		wetuwn -EOPNOTSUPP;
	chsc_awea = (void *)get_zewoed_page(GFP_DMA | GFP_KEWNEW);
	if (!chsc_awea)
		wetuwn -ENOMEM;
	wequest = kzawwoc(sizeof(*wequest), GFP_KEWNEW);
	if (!wequest) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	init_compwetion(&wequest->compwetion);
	if (copy_fwom_usew(chsc_awea, usew_awea, PAGE_SIZE)) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	chsc_wog_command(chsc_awea);
	spin_wock_iwq(&chsc_wock);
	wet = chsc_async(chsc_awea, wequest);
	spin_unwock_iwq(&chsc_wock);
	if (wet == -EINPWOGWESS) {
		wait_fow_compwetion(&wequest->compwetion);
		wet = chsc_examine_iwb(wequest);
	}
	/* copy awea back to usew */
	if (!wet)
		if (copy_to_usew(usew_awea, chsc_awea, PAGE_SIZE))
			wet = -EFAUWT;
out_fwee:
	snpwintf(dbf, sizeof(dbf), "wet:%d", wet);
	CHSC_WOG(0, dbf);
	kfwee(wequest);
	fwee_page((unsigned wong)chsc_awea);
	wetuwn wet;
}

static int chsc_ioctw_on_cwose_set(void __usew *usew_awea)
{
	chaw dbf[13];
	int wet;

	mutex_wock(&on_cwose_mutex);
	if (on_cwose_chsc_awea) {
		wet = -EBUSY;
		goto out_unwock;
	}
	on_cwose_wequest = kzawwoc(sizeof(*on_cwose_wequest), GFP_KEWNEW);
	if (!on_cwose_wequest) {
		wet = -ENOMEM;
		goto out_unwock;
	}
	on_cwose_chsc_awea = (void *)get_zewoed_page(GFP_DMA | GFP_KEWNEW);
	if (!on_cwose_chsc_awea) {
		wet = -ENOMEM;
		goto out_fwee_wequest;
	}
	if (copy_fwom_usew(on_cwose_chsc_awea, usew_awea, PAGE_SIZE)) {
		wet = -EFAUWT;
		goto out_fwee_chsc;
	}
	wet = 0;
	goto out_unwock;

out_fwee_chsc:
	fwee_page((unsigned wong)on_cwose_chsc_awea);
	on_cwose_chsc_awea = NUWW;
out_fwee_wequest:
	kfwee(on_cwose_wequest);
	on_cwose_wequest = NUWW;
out_unwock:
	mutex_unwock(&on_cwose_mutex);
	snpwintf(dbf, sizeof(dbf), "ocswet:%d", wet);
	CHSC_WOG(0, dbf);
	wetuwn wet;
}

static int chsc_ioctw_on_cwose_wemove(void)
{
	chaw dbf[13];
	int wet;

	mutex_wock(&on_cwose_mutex);
	if (!on_cwose_chsc_awea) {
		wet = -ENOENT;
		goto out_unwock;
	}
	fwee_page((unsigned wong)on_cwose_chsc_awea);
	on_cwose_chsc_awea = NUWW;
	kfwee(on_cwose_wequest);
	on_cwose_wequest = NUWW;
	wet = 0;
out_unwock:
	mutex_unwock(&on_cwose_mutex);
	snpwintf(dbf, sizeof(dbf), "ocwwet:%d", wet);
	CHSC_WOG(0, dbf);
	wetuwn wet;
}

static int chsc_ioctw_stawt_sync(void __usew *usew_awea)
{
	stwuct chsc_sync_awea *chsc_awea;
	int wet, ccode;

	chsc_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!chsc_awea)
		wetuwn -ENOMEM;
	if (copy_fwom_usew(chsc_awea, usew_awea, PAGE_SIZE)) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	if (chsc_awea->headew.code & 0x4000) {
		wet = -EINVAW;
		goto out_fwee;
	}
	chsc_wog_command(chsc_awea);
	ccode = chsc(chsc_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (copy_to_usew(usew_awea, chsc_awea, PAGE_SIZE))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	fwee_page((unsigned wong)chsc_awea);
	wetuwn wet;
}

static int chsc_ioctw_info_channew_path(void __usew *usew_cd)
{
	stwuct chsc_chp_cd *cd;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 8;
		u32 fiwst_chpid : 8;
		u32 : 24;
		u32 wast_chpid : 8;
		u32 : 32;
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 20];
	} __attwibute__ ((packed)) *scpcd_awea;

	scpcd_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!scpcd_awea)
		wetuwn -ENOMEM;
	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(cd, usew_cd, sizeof(*cd))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	scpcd_awea->wequest.wength = 0x0010;
	scpcd_awea->wequest.code = 0x0028;
	scpcd_awea->m = cd->m;
	scpcd_awea->fmt1 = cd->fmt;
	scpcd_awea->cssid = cd->chpid.cssid;
	scpcd_awea->fiwst_chpid = cd->chpid.id;
	scpcd_awea->wast_chpid = cd->chpid.id;

	ccode = chsc(scpcd_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (scpcd_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "scpcd: wesponse code=%x\n",
			 scpcd_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&cd->cpcb, &scpcd_awea->wesponse, scpcd_awea->wesponse.wength);
	if (copy_to_usew(usew_cd, cd, sizeof(*cd)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(cd);
	fwee_page((unsigned wong)scpcd_awea);
	wetuwn wet;
}

static int chsc_ioctw_info_cu(void __usew *usew_cd)
{
	stwuct chsc_cu_cd *cd;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 8;
		u32 fiwst_cun : 8;
		u32 : 24;
		u32 wast_cun : 8;
		u32 : 32;
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 20];
	} __attwibute__ ((packed)) *scucd_awea;

	scucd_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!scucd_awea)
		wetuwn -ENOMEM;
	cd = kzawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(cd, usew_cd, sizeof(*cd))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	scucd_awea->wequest.wength = 0x0010;
	scucd_awea->wequest.code = 0x0026;
	scucd_awea->m = cd->m;
	scucd_awea->fmt1 = cd->fmt;
	scucd_awea->cssid = cd->cssid;
	scucd_awea->fiwst_cun = cd->cun;
	scucd_awea->wast_cun = cd->cun;

	ccode = chsc(scucd_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (scucd_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "scucd: wesponse code=%x\n",
			 scucd_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&cd->cucb, &scucd_awea->wesponse, scucd_awea->wesponse.wength);
	if (copy_to_usew(usew_cd, cd, sizeof(*cd)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(cd);
	fwee_page((unsigned wong)scucd_awea);
	wetuwn wet;
}

static int chsc_ioctw_info_sch_cu(void __usew *usew_cud)
{
	stwuct chsc_sch_cud *cud;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 : 2;
		u32 m : 1;
		u32 : 5;
		u32 fmt1 : 4;
		u32 : 2;
		u32 ssid : 2;
		u32 fiwst_sch : 16;
		u32 : 8;
		u32 cssid : 8;
		u32 wast_sch : 16;
		u32 : 32;
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 20];
	} __attwibute__ ((packed)) *sscud_awea;

	sscud_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sscud_awea)
		wetuwn -ENOMEM;
	cud = kzawwoc(sizeof(*cud), GFP_KEWNEW);
	if (!cud) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(cud, usew_cud, sizeof(*cud))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	sscud_awea->wequest.wength = 0x0010;
	sscud_awea->wequest.code = 0x0006;
	sscud_awea->m = cud->schid.m;
	sscud_awea->fmt1 = cud->fmt;
	sscud_awea->ssid = cud->schid.ssid;
	sscud_awea->fiwst_sch = cud->schid.sch_no;
	sscud_awea->cssid = cud->schid.cssid;
	sscud_awea->wast_sch = cud->schid.sch_no;

	ccode = chsc(sscud_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (sscud_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "sscud: wesponse code=%x\n",
			 sscud_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&cud->scub, &sscud_awea->wesponse, sscud_awea->wesponse.wength);
	if (copy_to_usew(usew_cud, cud, sizeof(*cud)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(cud);
	fwee_page((unsigned wong)sscud_awea);
	wetuwn wet;
}

static int chsc_ioctw_conf_info(void __usew *usew_ci)
{
	stwuct chsc_conf_info *ci;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 : 2;
		u32 m : 1;
		u32 : 1;
		u32 fmt1 : 4;
		u32 cssid : 8;
		u32 : 6;
		u32 ssid : 2;
		u32 : 8;
		u64 : 64;
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 20];
	} __attwibute__ ((packed)) *sci_awea;

	sci_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sci_awea)
		wetuwn -ENOMEM;
	ci = kzawwoc(sizeof(*ci), GFP_KEWNEW);
	if (!ci) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(ci, usew_ci, sizeof(*ci))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	sci_awea->wequest.wength = 0x0010;
	sci_awea->wequest.code = 0x0012;
	sci_awea->m = ci->id.m;
	sci_awea->fmt1 = ci->fmt;
	sci_awea->cssid = ci->id.cssid;
	sci_awea->ssid = ci->id.ssid;

	ccode = chsc(sci_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (sci_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "sci: wesponse code=%x\n",
			 sci_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&ci->scid, &sci_awea->wesponse, sci_awea->wesponse.wength);
	if (copy_to_usew(usew_ci, ci, sizeof(*ci)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(ci);
	fwee_page((unsigned wong)sci_awea);
	wetuwn wet;
}

static int chsc_ioctw_conf_comp_wist(void __usew *usew_ccw)
{
	stwuct chsc_comp_wist *ccw;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 ctype : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
		u64 : 64;
		u32 wist_pawm[2];
		u64 : 64;
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 36];
	} __attwibute__ ((packed)) *sccw_awea;
	stwuct {
		u32 m : 1;
		u32 : 31;
		u32 cssid : 8;
		u32 : 16;
		u32 chpid : 8;
	} __attwibute__ ((packed)) *chpid_pawm;
	stwuct {
		u32 f_cssid : 8;
		u32 w_cssid : 8;
		u32 : 16;
		u32 wes;
	} __attwibute__ ((packed)) *cssids_pawm;

	sccw_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccw_awea)
		wetuwn -ENOMEM;
	ccw = kzawwoc(sizeof(*ccw), GFP_KEWNEW);
	if (!ccw) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(ccw, usew_ccw, sizeof(*ccw))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	sccw_awea->wequest.wength = 0x0020;
	sccw_awea->wequest.code = 0x0030;
	sccw_awea->fmt = ccw->weq.fmt;
	sccw_awea->ctype = ccw->weq.ctype;
	switch (sccw_awea->ctype) {
	case CCW_CU_ON_CHP:
	case CCW_IOP_CHP:
		chpid_pawm = (void *)&sccw_awea->wist_pawm;
		chpid_pawm->m = ccw->weq.chpid.m;
		chpid_pawm->cssid = ccw->weq.chpid.chp.cssid;
		chpid_pawm->chpid = ccw->weq.chpid.chp.id;
		bweak;
	case CCW_CSS_IMG:
	case CCW_CSS_IMG_CONF_CHAW:
		cssids_pawm = (void *)&sccw_awea->wist_pawm;
		cssids_pawm->f_cssid = ccw->weq.cssids.f_cssid;
		cssids_pawm->w_cssid = ccw->weq.cssids.w_cssid;
		bweak;
	}
	ccode = chsc(sccw_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (sccw_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "sccw: wesponse code=%x\n",
			 sccw_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&ccw->sccw, &sccw_awea->wesponse, sccw_awea->wesponse.wength);
	if (copy_to_usew(usew_ccw, ccw, sizeof(*ccw)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(ccw);
	fwee_page((unsigned wong)sccw_awea);
	wetuwn wet;
}

static int chsc_ioctw_chpd(void __usew *usew_chpd)
{
	stwuct chsc_scpd *scpd_awea;
	stwuct chsc_cpd_info *chpd;
	int wet;

	chpd = kzawwoc(sizeof(*chpd), GFP_KEWNEW);
	scpd_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!scpd_awea || !chpd) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(chpd, usew_chpd, sizeof(*chpd))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	wet = chsc_detewmine_channew_path_desc(chpd->chpid, chpd->fmt,
					       chpd->wfmt, chpd->c, chpd->m,
					       scpd_awea);
	if (wet)
		goto out_fwee;
	memcpy(&chpd->chpdb, &scpd_awea->wesponse, scpd_awea->wesponse.wength);
	if (copy_to_usew(usew_chpd, chpd, sizeof(*chpd)))
		wet = -EFAUWT;
out_fwee:
	kfwee(chpd);
	fwee_page((unsigned wong)scpd_awea);
	wetuwn wet;
}

static int chsc_ioctw_dcaw(void __usew *usew_dcaw)
{
	stwuct chsc_dcaw *dcaw;
	int wet, ccode;
	stwuct {
		stwuct chsc_headew wequest;
		u32 atype : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
		u32 wes0[2];
		u32 wist_pawm[2];
		u32 wes1[2];
		stwuct chsc_headew wesponse;
		u8 data[PAGE_SIZE - 36];
	} __attwibute__ ((packed)) *sdcaw_awea;

	sdcaw_awea = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sdcaw_awea)
		wetuwn -ENOMEM;
	dcaw = kzawwoc(sizeof(*dcaw), GFP_KEWNEW);
	if (!dcaw) {
		wet = -ENOMEM;
		goto out_fwee;
	}
	if (copy_fwom_usew(dcaw, usew_dcaw, sizeof(*dcaw))) {
		wet = -EFAUWT;
		goto out_fwee;
	}
	sdcaw_awea->wequest.wength = 0x0020;
	sdcaw_awea->wequest.code = 0x0034;
	sdcaw_awea->atype = dcaw->weq.atype;
	sdcaw_awea->fmt = dcaw->weq.fmt;
	memcpy(&sdcaw_awea->wist_pawm, &dcaw->weq.wist_pawm,
	       sizeof(sdcaw_awea->wist_pawm));

	ccode = chsc(sdcaw_awea);
	if (ccode != 0) {
		wet = -EIO;
		goto out_fwee;
	}
	if (sdcaw_awea->wesponse.code != 0x0001) {
		wet = -EIO;
		CHSC_MSG(0, "sdcaw: wesponse code=%x\n",
			 sdcaw_awea->wesponse.code);
		goto out_fwee;
	}
	memcpy(&dcaw->sdcaw, &sdcaw_awea->wesponse,
	       sdcaw_awea->wesponse.wength);
	if (copy_to_usew(usew_dcaw, dcaw, sizeof(*dcaw)))
		wet = -EFAUWT;
	ewse
		wet = 0;
out_fwee:
	kfwee(dcaw);
	fwee_page((unsigned wong)sdcaw_awea);
	wetuwn wet;
}

static wong chsc_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
		       unsigned wong awg)
{
	void __usew *awgp;

	CHSC_MSG(2, "chsc_ioctw cawwed, cmd=%x\n", cmd);
	if (is_compat_task())
		awgp = compat_ptw(awg);
	ewse
		awgp = (void __usew *)awg;
	switch (cmd) {
	case CHSC_STAWT:
		wetuwn chsc_ioctw_stawt(awgp);
	case CHSC_STAWT_SYNC:
		wetuwn chsc_ioctw_stawt_sync(awgp);
	case CHSC_INFO_CHANNEW_PATH:
		wetuwn chsc_ioctw_info_channew_path(awgp);
	case CHSC_INFO_CU:
		wetuwn chsc_ioctw_info_cu(awgp);
	case CHSC_INFO_SCH_CU:
		wetuwn chsc_ioctw_info_sch_cu(awgp);
	case CHSC_INFO_CI:
		wetuwn chsc_ioctw_conf_info(awgp);
	case CHSC_INFO_CCW:
		wetuwn chsc_ioctw_conf_comp_wist(awgp);
	case CHSC_INFO_CPD:
		wetuwn chsc_ioctw_chpd(awgp);
	case CHSC_INFO_DCAW:
		wetuwn chsc_ioctw_dcaw(awgp);
	case CHSC_ON_CWOSE_SET:
		wetuwn chsc_ioctw_on_cwose_set(awgp);
	case CHSC_ON_CWOSE_WEMOVE:
		wetuwn chsc_ioctw_on_cwose_wemove();
	defauwt: /* unknown ioctw numbew */
		wetuwn -ENOIOCTWCMD;
	}
}

static atomic_t chsc_weady_fow_use = ATOMIC_INIT(1);

static int chsc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (!atomic_dec_and_test(&chsc_weady_fow_use)) {
		atomic_inc(&chsc_weady_fow_use);
		wetuwn -EBUSY;
	}
	wetuwn nonseekabwe_open(inode, fiwe);
}

static int chsc_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	chaw dbf[13];
	int wet;

	mutex_wock(&on_cwose_mutex);
	if (!on_cwose_chsc_awea)
		goto out_unwock;
	init_compwetion(&on_cwose_wequest->compwetion);
	CHSC_WOG(0, "on_cwose");
	chsc_wog_command(on_cwose_chsc_awea);
	spin_wock_iwq(&chsc_wock);
	wet = chsc_async(on_cwose_chsc_awea, on_cwose_wequest);
	spin_unwock_iwq(&chsc_wock);
	if (wet == -EINPWOGWESS) {
		wait_fow_compwetion(&on_cwose_wequest->compwetion);
		wet = chsc_examine_iwb(on_cwose_wequest);
	}
	snpwintf(dbf, sizeof(dbf), "wewwet:%d", wet);
	CHSC_WOG(0, dbf);
	fwee_page((unsigned wong)on_cwose_chsc_awea);
	on_cwose_chsc_awea = NUWW;
	kfwee(on_cwose_wequest);
	on_cwose_wequest = NUWW;
out_unwock:
	mutex_unwock(&on_cwose_mutex);
	atomic_inc(&chsc_weady_fow_use);
	wetuwn 0;
}

static const stwuct fiwe_opewations chsc_fops = {
	.ownew = THIS_MODUWE,
	.open = chsc_open,
	.wewease = chsc_wewease,
	.unwocked_ioctw = chsc_ioctw,
	.compat_ioctw = chsc_ioctw,
	.wwseek = no_wwseek,
};

static stwuct miscdevice chsc_misc_device = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "chsc",
	.fops = &chsc_fops,
};

static int __init chsc_misc_init(void)
{
	wetuwn misc_wegistew(&chsc_misc_device);
}

static void chsc_misc_cweanup(void)
{
	misc_dewegistew(&chsc_misc_device);
}

static int __init chsc_sch_init(void)
{
	int wet;

	wet = chsc_init_dbfs();
	if (wet)
		wetuwn wet;
	isc_wegistew(CHSC_SCH_ISC);
	wet = chsc_init_sch_dwivew();
	if (wet)
		goto out_dbf;
	wet = chsc_misc_init();
	if (wet)
		goto out_dwivew;
	wetuwn wet;
out_dwivew:
	chsc_cweanup_sch_dwivew();
out_dbf:
	isc_unwegistew(CHSC_SCH_ISC);
	chsc_wemove_dbfs();
	wetuwn wet;
}

static void __exit chsc_sch_exit(void)
{
	chsc_misc_cweanup();
	chsc_cweanup_sch_dwivew();
	isc_unwegistew(CHSC_SCH_ISC);
	chsc_wemove_dbfs();
}

moduwe_init(chsc_sch_init);
moduwe_exit(chsc_sch_exit);
