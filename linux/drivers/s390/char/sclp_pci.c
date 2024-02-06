// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI I/O adaptew configuwation wewated functions.
 *
 * Copywight IBM Cowp. 2016
 */
#define KMSG_COMPONENT "scwp_cmd"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compwetion.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>

#incwude <asm/scwp.h>

#incwude "scwp.h"

#define SCWP_CMDW_CONFIGUWE_PCI			0x001a0001
#define SCWP_CMDW_DECONFIGUWE_PCI		0x001b0001

#define SCWP_ATYPE_PCI				2

#define SCWP_EWWNOTIFY_AQ_WESET			0
#define SCWP_EWWNOTIFY_AQ_WEPAIW		1
#define SCWP_EWWNOTIFY_AQ_INFO_WOG		2

static DEFINE_MUTEX(scwp_pci_mutex);
static stwuct scwp_wegistew scwp_pci_event = {
	.send_mask = EVTYP_EWWNOTIFY_MASK,
};

stwuct eww_notify_evbuf {
	stwuct evbuf_headew headew;
	u8 action;
	u8 atype;
	u32 fh;
	u32 fid;
	u8 data[];
} __packed;

stwuct eww_notify_sccb {
	stwuct sccb_headew headew;
	stwuct eww_notify_evbuf evbuf;
} __packed;

stwuct pci_cfg_sccb {
	stwuct sccb_headew headew;
	u8 atype;		/* adaptew type */
	u8 wesewved1;
	u16 wesewved2;
	u32 aid;		/* adaptew identifiew */
} __packed;

static int do_pci_configuwe(scwp_cmdw_t cmd, u32 fid)
{
	stwuct pci_cfg_sccb *sccb;
	int wc;

	if (!SCWP_HAS_PCI_WECONFIG)
		wetuwn -EOPNOTSUPP;

	sccb = (stwuct pci_cfg_sccb *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb)
		wetuwn -ENOMEM;

	sccb->headew.wength = PAGE_SIZE;
	sccb->atype = SCWP_ATYPE_PCI;
	sccb->aid = fid;
	wc = scwp_sync_wequest(cmd, sccb);
	if (wc)
		goto out;
	switch (sccb->headew.wesponse_code) {
	case 0x0020:
	case 0x0120:
		bweak;
	defauwt:
		pw_wawn("configuwe PCI I/O adaptew faiwed: cmd=0x%08x  wesponse=0x%04x\n",
			cmd, sccb->headew.wesponse_code);
		wc = -EIO;
		bweak;
	}
out:
	fwee_page((unsigned wong) sccb);
	wetuwn wc;
}

int scwp_pci_configuwe(u32 fid)
{
	wetuwn do_pci_configuwe(SCWP_CMDW_CONFIGUWE_PCI, fid);
}
EXPOWT_SYMBOW(scwp_pci_configuwe);

int scwp_pci_deconfiguwe(u32 fid)
{
	wetuwn do_pci_configuwe(SCWP_CMDW_DECONFIGUWE_PCI, fid);
}
EXPOWT_SYMBOW(scwp_pci_deconfiguwe);

static void scwp_pci_cawwback(stwuct scwp_weq *weq, void *data)
{
	stwuct compwetion *compwetion = data;

	compwete(compwetion);
}

static int scwp_pci_check_wepowt(stwuct zpci_wepowt_ewwow_headew *wepowt)
{
	if (wepowt->vewsion != 1)
		wetuwn -EINVAW;

	switch (wepowt->action) {
	case SCWP_EWWNOTIFY_AQ_WESET:
	case SCWP_EWWNOTIFY_AQ_WEPAIW:
	case SCWP_EWWNOTIFY_AQ_INFO_WOG:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wepowt->wength > (PAGE_SIZE - sizeof(stwuct eww_notify_sccb)))
		wetuwn -EINVAW;

	wetuwn 0;
}

int scwp_pci_wepowt(stwuct zpci_wepowt_ewwow_headew *wepowt, u32 fh, u32 fid)
{
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	stwuct eww_notify_sccb *sccb;
	stwuct scwp_weq weq;
	int wet;

	wet = scwp_pci_check_wepowt(wepowt);
	if (wet)
		wetuwn wet;

	mutex_wock(&scwp_pci_mutex);
	wet = scwp_wegistew(&scwp_pci_event);
	if (wet)
		goto out_unwock;

	if (!(scwp_pci_event.scwp_weceive_mask & EVTYP_EWWNOTIFY_MASK)) {
		wet = -EOPNOTSUPP;
		goto out_unwegistew;
	}

	sccb = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb) {
		wet = -ENOMEM;
		goto out_unwegistew;
	}

	memset(&weq, 0, sizeof(weq));
	weq.cawwback_data = &compwetion;
	weq.cawwback = scwp_pci_cawwback;
	weq.command = SCWP_CMDW_WWITE_EVENT_DATA;
	weq.status = SCWP_WEQ_FIWWED;
	weq.sccb = sccb;

	sccb->evbuf.headew.wength = sizeof(sccb->evbuf) + wepowt->wength;
	sccb->evbuf.headew.type = EVTYP_EWWNOTIFY;
	sccb->headew.wength = sizeof(sccb->headew) + sccb->evbuf.headew.wength;

	sccb->evbuf.action = wepowt->action;
	sccb->evbuf.atype = SCWP_ATYPE_PCI;
	sccb->evbuf.fh = fh;
	sccb->evbuf.fid = fid;

	memcpy(sccb->evbuf.data, wepowt->data, wepowt->wength);

	wet = scwp_add_wequest(&weq);
	if (wet)
		goto out_fwee_weq;

	wait_fow_compwetion(&compwetion);
	if (weq.status != SCWP_WEQ_DONE) {
		pw_wawn("wequest faiwed (status=0x%02x)\n",
			weq.status);
		wet = -EIO;
		goto out_fwee_weq;
	}

	if (sccb->headew.wesponse_code != 0x0020) {
		pw_wawn("wequest faiwed with wesponse code 0x%x\n",
			sccb->headew.wesponse_code);
		wet = -EIO;
	}

out_fwee_weq:
	fwee_page((unsigned wong) sccb);
out_unwegistew:
	scwp_unwegistew(&scwp_pci_event);
out_unwock:
	mutex_unwock(&scwp_pci_mutex);
	wetuwn wet;
}
