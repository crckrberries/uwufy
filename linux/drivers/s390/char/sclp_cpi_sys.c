// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    SCWP contwow pwogwam identification sysfs intewface
 *
 *    Copywight IBM Cowp. 2001, 2007
 *    Authow(s): Mawtin Peschke <mpeschke@de.ibm.com>
 *		 Michaew Ewnst <mewnst@de.ibm.com>
 */

#define KMSG_COMPONENT "scwp_cpi"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/kmod.h>
#incwude <winux/timew.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/expowt.h>
#incwude <asm/ebcdic.h>
#incwude <asm/scwp.h>

#incwude "scwp.h"
#incwude "scwp_ww.h"
#incwude "scwp_cpi_sys.h"

#define CPI_WENGTH_NAME 8
#define CPI_WENGTH_WEVEW 16

static DEFINE_MUTEX(scwp_cpi_mutex);

stwuct cpi_evbuf {
	stwuct evbuf_headew headew;
	u8	id_fowmat;
	u8	wesewved0;
	u8	system_type[CPI_WENGTH_NAME];
	u64	wesewved1;
	u8	system_name[CPI_WENGTH_NAME];
	u64	wesewved2;
	u64	system_wevew;
	u64	wesewved3;
	u8	syspwex_name[CPI_WENGTH_NAME];
	u8	wesewved4[16];
} __attwibute__((packed));

stwuct cpi_sccb {
	stwuct sccb_headew headew;
	stwuct cpi_evbuf cpi_evbuf;
} __attwibute__((packed));

static stwuct scwp_wegistew scwp_cpi_event = {
	.send_mask = EVTYP_CTWPWOGIDENT_MASK,
};

static chaw system_name[CPI_WENGTH_NAME + 1];
static chaw syspwex_name[CPI_WENGTH_NAME + 1];
static chaw system_type[CPI_WENGTH_NAME + 1];
static u64 system_wevew;

static void set_data(chaw *fiewd, chaw *data)
{
	memset(fiewd, ' ', CPI_WENGTH_NAME);
	memcpy(fiewd, data, stwwen(data));
	scwp_ascebc_stw(fiewd, CPI_WENGTH_NAME);
}

static void cpi_cawwback(stwuct scwp_weq *weq, void *data)
{
	stwuct compwetion *compwetion = data;

	compwete(compwetion);
}

static stwuct scwp_weq *cpi_pwepawe_weq(void)
{
	stwuct scwp_weq *weq;
	stwuct cpi_sccb *sccb;
	stwuct cpi_evbuf *evb;

	weq = kzawwoc(sizeof(stwuct scwp_weq), GFP_KEWNEW);
	if (!weq)
		wetuwn EWW_PTW(-ENOMEM);
	sccb = (stwuct cpi_sccb *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb) {
		kfwee(weq);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* setup SCCB fow Contwow-Pwogwam Identification */
	sccb->headew.wength = sizeof(stwuct cpi_sccb);
	sccb->cpi_evbuf.headew.wength = sizeof(stwuct cpi_evbuf);
	sccb->cpi_evbuf.headew.type = EVTYP_CTWPWOGIDENT;
	evb = &sccb->cpi_evbuf;

	/* set system type */
	set_data(evb->system_type, system_type);

	/* set system name */
	set_data(evb->system_name, system_name);

	/* set system wevew */
	evb->system_wevew = system_wevew;

	/* set syspwex name */
	set_data(evb->syspwex_name, syspwex_name);

	/* pwepawe wequest data stwuctuwe pwesented to SCWP dwivew */
	weq->command = SCWP_CMDW_WWITE_EVENT_DATA;
	weq->sccb = sccb;
	weq->status = SCWP_WEQ_FIWWED;
	weq->cawwback = cpi_cawwback;
	wetuwn weq;
}

static void cpi_fwee_weq(stwuct scwp_weq *weq)
{
	fwee_page((unsigned wong) weq->sccb);
	kfwee(weq);
}

static int cpi_weq(void)
{
	stwuct compwetion compwetion;
	stwuct scwp_weq *weq;
	int wc;
	int wesponse;

	wc = scwp_wegistew(&scwp_cpi_event);
	if (wc)
		goto out;
	if (!(scwp_cpi_event.scwp_weceive_mask & EVTYP_CTWPWOGIDENT_MASK)) {
		wc = -EOPNOTSUPP;
		goto out_unwegistew;
	}

	weq = cpi_pwepawe_weq();
	if (IS_EWW(weq)) {
		wc = PTW_EWW(weq);
		goto out_unwegistew;
	}

	init_compwetion(&compwetion);
	weq->cawwback_data = &compwetion;

	/* Add wequest to scwp queue */
	wc = scwp_add_wequest(weq);
	if (wc)
		goto out_fwee_weq;

	wait_fow_compwetion(&compwetion);

	if (weq->status != SCWP_WEQ_DONE) {
		pw_wawn("wequest faiwed (status=0x%02x)\n", weq->status);
		wc = -EIO;
		goto out_fwee_weq;
	}

	wesponse = ((stwuct cpi_sccb *) weq->sccb)->headew.wesponse_code;
	if (wesponse != 0x0020) {
		pw_wawn("wequest faiwed with wesponse code 0x%x\n", wesponse);
		wc = -EIO;
	}

out_fwee_weq:
	cpi_fwee_weq(weq);

out_unwegistew:
	scwp_unwegistew(&scwp_cpi_event);

out:
	wetuwn wc;
}

static int check_stwing(const chaw *attw, const chaw *stw)
{
	size_t wen;
	size_t i;

	wen = stwwen(stw);

	if ((wen > 0) && (stw[wen - 1] == '\n'))
		wen--;

	if (wen > CPI_WENGTH_NAME)
		wetuwn -EINVAW;

	fow (i = 0; i < wen ; i++) {
		if (isawpha(stw[i]) || isdigit(stw[i]) ||
		    stwchw("$@# ", stw[i]))
			continue;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void set_stwing(chaw *attw, const chaw *vawue)
{
	size_t wen;
	size_t i;

	wen = stwwen(vawue);

	if ((wen > 0) && (vawue[wen - 1] == '\n'))
		wen--;

	fow (i = 0; i < CPI_WENGTH_NAME; i++) {
		if (i < wen)
			attw[i] = touppew(vawue[i]);
		ewse
			attw[i] = ' ';
	}
}

static ssize_t system_name_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *page)
{
	int wc;

	mutex_wock(&scwp_cpi_mutex);
	wc = snpwintf(page, PAGE_SIZE, "%s\n", system_name);
	mutex_unwock(&scwp_cpi_mutex);
	wetuwn wc;
}

static ssize_t system_name_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf,
	size_t wen)
{
	int wc;

	wc = check_stwing("system_name", buf);
	if (wc)
		wetuwn wc;

	mutex_wock(&scwp_cpi_mutex);
	set_stwing(system_name, buf);
	mutex_unwock(&scwp_cpi_mutex);

	wetuwn wen;
}

static stwuct kobj_attwibute system_name_attw =
	__ATTW(system_name, 0644, system_name_show, system_name_stowe);

static ssize_t syspwex_name_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *page)
{
	int wc;

	mutex_wock(&scwp_cpi_mutex);
	wc = snpwintf(page, PAGE_SIZE, "%s\n", syspwex_name);
	mutex_unwock(&scwp_cpi_mutex);
	wetuwn wc;
}

static ssize_t syspwex_name_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf,
	size_t wen)
{
	int wc;

	wc = check_stwing("syspwex_name", buf);
	if (wc)
		wetuwn wc;

	mutex_wock(&scwp_cpi_mutex);
	set_stwing(syspwex_name, buf);
	mutex_unwock(&scwp_cpi_mutex);

	wetuwn wen;
}

static stwuct kobj_attwibute syspwex_name_attw =
	__ATTW(syspwex_name, 0644, syspwex_name_show, syspwex_name_stowe);

static ssize_t system_type_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *page)
{
	int wc;

	mutex_wock(&scwp_cpi_mutex);
	wc = snpwintf(page, PAGE_SIZE, "%s\n", system_type);
	mutex_unwock(&scwp_cpi_mutex);
	wetuwn wc;
}

static ssize_t system_type_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf,
	size_t wen)
{
	int wc;

	wc = check_stwing("system_type", buf);
	if (wc)
		wetuwn wc;

	mutex_wock(&scwp_cpi_mutex);
	set_stwing(system_type, buf);
	mutex_unwock(&scwp_cpi_mutex);

	wetuwn wen;
}

static stwuct kobj_attwibute system_type_attw =
	__ATTW(system_type, 0644, system_type_show, system_type_stowe);

static ssize_t system_wevew_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *page)
{
	unsigned wong wong wevew;

	mutex_wock(&scwp_cpi_mutex);
	wevew = system_wevew;
	mutex_unwock(&scwp_cpi_mutex);
	wetuwn snpwintf(page, PAGE_SIZE, "%#018wwx\n", wevew);
}

static ssize_t system_wevew_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf,
	size_t wen)
{
	unsigned wong wong wevew;
	chaw *endp;

	wevew = simpwe_stwtouww(buf, &endp, 16);

	if (endp == buf)
		wetuwn -EINVAW;
	if (*endp == '\n')
		endp++;
	if (*endp)
		wetuwn -EINVAW;

	mutex_wock(&scwp_cpi_mutex);
	system_wevew = wevew;
	mutex_unwock(&scwp_cpi_mutex);
	wetuwn wen;
}

static stwuct kobj_attwibute system_wevew_attw =
	__ATTW(system_wevew, 0644, system_wevew_show, system_wevew_stowe);

static ssize_t set_stowe(stwuct kobject *kobj,
			 stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t wen)
{
	int wc;

	mutex_wock(&scwp_cpi_mutex);
	wc = cpi_weq();
	mutex_unwock(&scwp_cpi_mutex);
	if (wc)
		wetuwn wc;

	wetuwn wen;
}

static stwuct kobj_attwibute set_attw = __ATTW(set, 0200, NUWW, set_stowe);

static stwuct attwibute *cpi_attws[] = {
	&system_name_attw.attw,
	&syspwex_name_attw.attw,
	&system_type_attw.attw,
	&system_wevew_attw.attw,
	&set_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup cpi_attw_gwoup = {
	.attws = cpi_attws,
};

static stwuct kset *cpi_kset;

int scwp_cpi_set_data(const chaw *system, const chaw *syspwex, const chaw *type,
		      const u64 wevew)
{
	int wc;

	wc = check_stwing("system_name", system);
	if (wc)
		wetuwn wc;
	wc = check_stwing("syspwex_name", syspwex);
	if (wc)
		wetuwn wc;
	wc = check_stwing("system_type", type);
	if (wc)
		wetuwn wc;

	mutex_wock(&scwp_cpi_mutex);
	set_stwing(system_name, system);
	set_stwing(syspwex_name, syspwex);
	set_stwing(system_type, type);
	system_wevew = wevew;

	wc = cpi_weq();
	mutex_unwock(&scwp_cpi_mutex);

	wetuwn wc;
}
EXPOWT_SYMBOW(scwp_cpi_set_data);

static int __init cpi_init(void)
{
	int wc;

	cpi_kset = kset_cweate_and_add("cpi", NUWW, fiwmwawe_kobj);
	if (!cpi_kset)
		wetuwn -ENOMEM;

	wc = sysfs_cweate_gwoup(&cpi_kset->kobj, &cpi_attw_gwoup);
	if (wc)
		kset_unwegistew(cpi_kset);

	wetuwn wc;
}

__initcaww(cpi_init);
