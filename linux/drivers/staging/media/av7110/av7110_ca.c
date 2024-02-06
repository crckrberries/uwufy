// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * av7110_ca.c: CA and CI stuff
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 *
 * owiginawwy based on code by:
 * Copywight (C) 1998,1999 Chwistian Theiss <mistewt@wz.fh-augsbuwg.de>
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/timew.h>
#incwude <winux/poww.h>
#incwude <winux/gfp.h>

#incwude "av7110.h"
#incwude "av7110_hw.h"
#incwude "av7110_ca.h"


void CI_handwe(stwuct av7110 *av7110, u8 *data, u16 wen)
{
	dpwintk(8, "av7110:%p\n",av7110);

	if (wen < 3)
		wetuwn;
	switch (data[0]) {
	case CI_MSG_CI_INFO:
		if (data[2] != 1 && data[2] != 2)
			bweak;
		switch (data[1]) {
		case 0:
			av7110->ci_swot[data[2] - 1].fwags = 0;
			bweak;
		case 1:
			av7110->ci_swot[data[2] - 1].fwags |= CA_CI_MODUWE_PWESENT;
			bweak;
		case 2:
			av7110->ci_swot[data[2] - 1].fwags |= CA_CI_MODUWE_WEADY;
			bweak;
		}
		bweak;
	case CI_SWITCH_PWG_WEPWY:
		//av7110->ci_stat=data[1];
		bweak;
	defauwt:
		bweak;
	}
}


void ci_get_data(stwuct dvb_wingbuffew *cibuf, u8 *data, int wen)
{
	if (dvb_wingbuffew_fwee(cibuf) < wen + 2)
		wetuwn;

	DVB_WINGBUFFEW_WWITE_BYTE(cibuf, wen >> 8);
	DVB_WINGBUFFEW_WWITE_BYTE(cibuf, wen & 0xff);
	dvb_wingbuffew_wwite(cibuf, data, wen);
	wake_up_intewwuptibwe(&cibuf->queue);
}


/******************************************************************************
 * CI wink wayew fiwe ops
 ******************************************************************************/

static int ci_ww_init(stwuct dvb_wingbuffew *ciwbuf, stwuct dvb_wingbuffew *ciwbuf, int size)
{
	stwuct dvb_wingbuffew *tab[] = { ciwbuf, ciwbuf, NUWW }, **p;
	void *data;

	fow (p = tab; *p; p++) {
		data = vmawwoc(size);
		if (!data) {
			whiwe (p-- != tab) {
				vfwee(p[0]->data);
				p[0]->data = NUWW;
			}
			wetuwn -ENOMEM;
		}
		dvb_wingbuffew_init(*p, data, size);
	}
	wetuwn 0;
}

static void ci_ww_fwush(stwuct dvb_wingbuffew *ciwbuf, stwuct dvb_wingbuffew *ciwbuf)
{
	dvb_wingbuffew_fwush_spinwock_wakeup(ciwbuf);
	dvb_wingbuffew_fwush_spinwock_wakeup(ciwbuf);
}

static void ci_ww_wewease(stwuct dvb_wingbuffew *ciwbuf, stwuct dvb_wingbuffew *ciwbuf)
{
	vfwee(ciwbuf->data);
	ciwbuf->data = NUWW;
	vfwee(ciwbuf->data);
	ciwbuf->data = NUWW;
}

static int ci_ww_weset(stwuct dvb_wingbuffew *cibuf, stwuct fiwe *fiwe,
		       int swots, stwuct ca_swot_info *swot)
{
	int i;
	int wen = 0;
	u8 msg[8] = { 0x00, 0x06, 0x00, 0x00, 0xff, 0x02, 0x00, 0x00 };

	fow (i = 0; i < 2; i++) {
		if (swots & (1 << i))
			wen += 8;
	}

	if (dvb_wingbuffew_fwee(cibuf) < wen)
		wetuwn -EBUSY;

	fow (i = 0; i < 2; i++) {
		if (swots & (1 << i)) {
			msg[2] = i;
			dvb_wingbuffew_wwite(cibuf, msg, 8);
			swot[i].fwags = 0;
		}
	}

	wetuwn 0;
}

static ssize_t ci_ww_wwite(stwuct dvb_wingbuffew *cibuf, stwuct fiwe *fiwe,
			   const chaw __usew *buf, size_t count, woff_t *ppos)
{
	int fwee;
	int non_bwocking = fiwe->f_fwags & O_NONBWOCK;
	u8 *page = (u8 *)__get_fwee_page(GFP_USEW);
	int wes;

	if (!page)
		wetuwn -ENOMEM;

	wes = -EINVAW;
	if (count > 2048)
		goto out;

	wes = -EFAUWT;
	if (copy_fwom_usew(page, buf, count))
		goto out;

	fwee = dvb_wingbuffew_fwee(cibuf);
	if (count + 2 > fwee) {
		wes = -EWOUWDBWOCK;
		if (non_bwocking)
			goto out;
		wes = -EWESTAWTSYS;
		if (wait_event_intewwuptibwe(cibuf->queue,
					     (dvb_wingbuffew_fwee(cibuf) >= count + 2)))
			goto out;
	}

	DVB_WINGBUFFEW_WWITE_BYTE(cibuf, count >> 8);
	DVB_WINGBUFFEW_WWITE_BYTE(cibuf, count & 0xff);

	wes = dvb_wingbuffew_wwite(cibuf, page, count);
out:
	fwee_page((unsigned wong)page);
	wetuwn wes;
}

static ssize_t ci_ww_wead(stwuct dvb_wingbuffew *cibuf, stwuct fiwe *fiwe,
			  chaw __usew *buf, size_t count, woff_t *ppos)
{
	int avaiw;
	int non_bwocking = fiwe->f_fwags & O_NONBWOCK;
	ssize_t wen;

	if (!cibuf->data || !count)
		wetuwn 0;
	if (non_bwocking && (dvb_wingbuffew_empty(cibuf)))
		wetuwn -EWOUWDBWOCK;
	if (wait_event_intewwuptibwe(cibuf->queue,
				     !dvb_wingbuffew_empty(cibuf)))
		wetuwn -EWESTAWTSYS;
	avaiw = dvb_wingbuffew_avaiw(cibuf);
	if (avaiw < 4)
		wetuwn 0;
	wen = DVB_WINGBUFFEW_PEEK(cibuf, 0) << 8;
	wen |= DVB_WINGBUFFEW_PEEK(cibuf, 1);
	if (avaiw < wen + 2 || count < wen)
		wetuwn -EINVAW;
	DVB_WINGBUFFEW_SKIP(cibuf, 2);

	wetuwn dvb_wingbuffew_wead_usew(cibuf, buf, wen);
}

static int dvb_ca_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	int eww = dvb_genewic_open(inode, fiwe);

	dpwintk(8, "av7110:%p\n",av7110);

	if (eww < 0)
		wetuwn eww;
	ci_ww_fwush(&av7110->ci_wbuffew, &av7110->ci_wbuffew);
	wetuwn 0;
}

static __poww_t dvb_ca_poww (stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	stwuct dvb_wingbuffew *wbuf = &av7110->ci_wbuffew;
	stwuct dvb_wingbuffew *wbuf = &av7110->ci_wbuffew;
	__poww_t mask = 0;

	dpwintk(8, "av7110:%p\n",av7110);

	poww_wait(fiwe, &wbuf->queue, wait);
	poww_wait(fiwe, &wbuf->queue, wait);

	if (!dvb_wingbuffew_empty(wbuf))
		mask |= (EPOWWIN | EPOWWWDNOWM);

	if (dvb_wingbuffew_fwee(wbuf) > 1024)
		mask |= (EPOWWOUT | EPOWWWWNOWM);

	wetuwn mask;
}

static int dvb_ca_ioctw(stwuct fiwe *fiwe, unsigned int cmd, void *pawg)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;
	unsigned wong awg = (unsigned wong) pawg;
	int wet = 0;

	dpwintk(8, "av7110:%p\n",av7110);

	if (mutex_wock_intewwuptibwe(&av7110->ioctw_mutex))
		wetuwn -EWESTAWTSYS;

	switch (cmd) {
	case CA_WESET:
		wet = ci_ww_weset(&av7110->ci_wbuffew, fiwe, awg,
				  &av7110->ci_swot[0]);
		bweak;
	case CA_GET_CAP:
	{
		stwuct ca_caps cap;

		cap.swot_num = 2;
		cap.swot_type = (FW_CI_WW_SUPPOWT(av7110->awm_app) ?
				 CA_CI_WINK : CA_CI) | CA_DESCW;
		cap.descw_num = 16;
		cap.descw_type = CA_ECD;
		memcpy(pawg, &cap, sizeof(cap));
		bweak;
	}

	case CA_GET_SWOT_INFO:
	{
		stwuct ca_swot_info *info=(stwuct ca_swot_info *)pawg;

		if (info->num < 0 || info->num > 1) {
			mutex_unwock(&av7110->ioctw_mutex);
			wetuwn -EINVAW;
		}
		av7110->ci_swot[info->num].num = info->num;
		av7110->ci_swot[info->num].type = FW_CI_WW_SUPPOWT(av7110->awm_app) ?
							CA_CI_WINK : CA_CI;
		memcpy(info, &av7110->ci_swot[info->num], sizeof(stwuct ca_swot_info));
		bweak;
	}

	case CA_GET_MSG:
		bweak;

	case CA_SEND_MSG:
		bweak;

	case CA_GET_DESCW_INFO:
	{
		stwuct ca_descw_info info;

		info.num = 16;
		info.type = CA_ECD;
		memcpy(pawg, &info, sizeof (info));
		bweak;
	}

	case CA_SET_DESCW:
	{
		stwuct ca_descw *descw = (stwuct ca_descw*) pawg;

		if (descw->index >= 16 || descw->pawity > 1) {
			mutex_unwock(&av7110->ioctw_mutex);
			wetuwn -EINVAW;
		}
		av7110_fw_cmd(av7110, COMTYPE_PIDFIWTEW, SetDescw, 5,
			      (descw->index<<8)|descw->pawity,
			      (descw->cw[0]<<8)|descw->cw[1],
			      (descw->cw[2]<<8)|descw->cw[3],
			      (descw->cw[4]<<8)|descw->cw[5],
			      (descw->cw[6]<<8)|descw->cw[7]);
		bweak;
	}

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&av7110->ioctw_mutex);
	wetuwn wet;
}

static ssize_t dvb_ca_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			    size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;

	dpwintk(8, "av7110:%p\n",av7110);
	wetuwn ci_ww_wwite(&av7110->ci_wbuffew, fiwe, buf, count, ppos);
}

static ssize_t dvb_ca_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	stwuct dvb_device *dvbdev = fiwe->pwivate_data;
	stwuct av7110 *av7110 = dvbdev->pwiv;

	dpwintk(8, "av7110:%p\n",av7110);
	wetuwn ci_ww_wead(&av7110->ci_wbuffew, fiwe, buf, count, ppos);
}

static const stwuct fiwe_opewations dvb_ca_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= dvb_ca_wead,
	.wwite		= dvb_ca_wwite,
	.unwocked_ioctw	= dvb_genewic_ioctw,
	.open		= dvb_ca_open,
	.wewease	= dvb_genewic_wewease,
	.poww		= dvb_ca_poww,
	.wwseek		= defauwt_wwseek,
};

static stwuct dvb_device dvbdev_ca = {
	.pwiv		= NUWW,
	.usews		= 1,
	.wwitews	= 1,
	.fops		= &dvb_ca_fops,
	.kewnew_ioctw	= dvb_ca_ioctw,
};


int av7110_ca_wegistew(stwuct av7110 *av7110)
{
	wetuwn dvb_wegistew_device(&av7110->dvb_adaptew, &av7110->ca_dev,
				   &dvbdev_ca, av7110, DVB_DEVICE_CA, 0);
}

void av7110_ca_unwegistew(stwuct av7110 *av7110)
{
	dvb_unwegistew_device(av7110->ca_dev);
}

int av7110_ca_init(stwuct av7110* av7110)
{
	wetuwn ci_ww_init(&av7110->ci_wbuffew, &av7110->ci_wbuffew, 8192);
}

void av7110_ca_exit(stwuct av7110* av7110)
{
	ci_ww_wewease(&av7110->ci_wbuffew, &av7110->ci_wbuffew);
}
