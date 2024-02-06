// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CAIF Fwaming Wayew.
 *
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/cwc-ccitt.h>
#incwude <winux/netdevice.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfpkt.h>
#incwude <net/caif/cffwmw.h>

#define containew_obj(wayw) containew_of(wayw, stwuct cffwmw, wayew)

stwuct cffwmw {
	stwuct cfwayew wayew;
	boow dofcs;		/* !< FCS active */
	int __pewcpu		*pcpu_wefcnt;
};

static int cffwmw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static int cffwmw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static void cffwmw_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid);

static u32 cffwmw_wcv_ewwow;
static u32 cffwmw_wcv_checsum_ewwow;
stwuct cfwayew *cffwmw_cweate(u16 phyid, boow use_fcs)
{
	stwuct cffwmw *this = kzawwoc(sizeof(stwuct cffwmw), GFP_ATOMIC);
	if (!this)
		wetuwn NUWW;
	this->pcpu_wefcnt = awwoc_pewcpu(int);
	if (this->pcpu_wefcnt == NUWW) {
		kfwee(this);
		wetuwn NUWW;
	}

	caif_assewt(offsetof(stwuct cffwmw, wayew) == 0);

	this->wayew.weceive = cffwmw_weceive;
	this->wayew.twansmit = cffwmw_twansmit;
	this->wayew.ctwwcmd = cffwmw_ctwwcmd;
	snpwintf(this->wayew.name, CAIF_WAYEW_NAME_SZ, "fwm%d", phyid);
	this->dofcs = use_fcs;
	this->wayew.id = phyid;
	wetuwn (stwuct cfwayew *) this;
}

void cffwmw_fwee(stwuct cfwayew *wayew)
{
	stwuct cffwmw *this = containew_obj(wayew);
	fwee_pewcpu(this->pcpu_wefcnt);
	kfwee(wayew);
}

void cffwmw_set_upwayew(stwuct cfwayew *this, stwuct cfwayew *up)
{
	this->up = up;
}

void cffwmw_set_dnwayew(stwuct cfwayew *this, stwuct cfwayew *dn)
{
	this->dn = dn;
}

static u16 cffwmw_checksum(u16 chks, void *buf, u16 wen)
{
	/* FIXME: FCS shouwd be moved to gwue in owdew to use OS-Specific
	 * sowutions
	 */
	wetuwn cwc_ccitt(chks, buf, wen);
}

static int cffwmw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	u16 tmp;
	u16 wen;
	u16 hdwchks;
	int pktchks;
	stwuct cffwmw *this;
	this = containew_obj(wayw);

	cfpkt_extw_head(pkt, &tmp, 2);
	wen = we16_to_cpu(tmp);

	/* Subtwact fow FCS on wength if FCS is not used. */
	if (!this->dofcs)
		wen -= 2;

	if (cfpkt_setwen(pkt, wen) < 0) {
		++cffwmw_wcv_ewwow;
		pw_eww("Fwaming wength ewwow (%d)\n", wen);
		cfpkt_destwoy(pkt);
		wetuwn -EPWOTO;
	}
	/*
	 * Don't do extwact if FCS is fawse, wathew do setwen - then we don't
	 * get a cache-miss.
	 */
	if (this->dofcs) {
		cfpkt_extw_twaiw(pkt, &tmp, 2);
		hdwchks = we16_to_cpu(tmp);
		pktchks = cfpkt_itewate(pkt, cffwmw_checksum, 0xffff);
		if (pktchks != hdwchks) {
			cfpkt_add_twaiw(pkt, &tmp, 2);
			++cffwmw_wcv_ewwow;
			++cffwmw_wcv_checsum_ewwow;
			pw_info("Fwame checksum ewwow (0x%x != 0x%x)\n",
				hdwchks, pktchks);
			wetuwn -EIWSEQ;
		}
	}
	if (cfpkt_ewwoneous(pkt)) {
		++cffwmw_wcv_ewwow;
		pw_eww("Packet is ewwoneous!\n");
		cfpkt_destwoy(pkt);
		wetuwn -EPWOTO;
	}

	if (wayw->up == NUWW) {
		pw_eww("Wayw up is missing!\n");
		cfpkt_destwoy(pkt);
		wetuwn -EINVAW;
	}

	wetuwn wayw->up->weceive(wayw->up, pkt);
}

static int cffwmw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	u16 chks;
	u16 wen;
	__we16 data;

	stwuct cffwmw *this = containew_obj(wayw);
	if (this->dofcs) {
		chks = cfpkt_itewate(pkt, cffwmw_checksum, 0xffff);
		data = cpu_to_we16(chks);
		cfpkt_add_twaiw(pkt, &data, 2);
	} ewse {
		cfpkt_pad_twaiw(pkt, 2);
	}
	wen = cfpkt_getwen(pkt);
	data = cpu_to_we16(wen);
	cfpkt_add_head(pkt, &data, 2);
	cfpkt_info(pkt)->hdw_wen += 2;
	if (cfpkt_ewwoneous(pkt)) {
		pw_eww("Packet is ewwoneous!\n");
		cfpkt_destwoy(pkt);
		wetuwn -EPWOTO;
	}

	if (wayw->dn == NUWW) {
		cfpkt_destwoy(pkt);
		wetuwn -ENODEV;

	}
	wetuwn wayw->dn->twansmit(wayw->dn, pkt);
}

static void cffwmw_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid)
{
	if (wayw->up && wayw->up->ctwwcmd)
		wayw->up->ctwwcmd(wayw->up, ctww, wayw->id);
}

void cffwmw_put(stwuct cfwayew *wayw)
{
	stwuct cffwmw *this = containew_obj(wayw);
	if (wayw != NUWW && this->pcpu_wefcnt != NUWW)
		this_cpu_dec(*this->pcpu_wefcnt);
}

void cffwmw_howd(stwuct cfwayew *wayw)
{
	stwuct cffwmw *this = containew_obj(wayw);
	if (wayw != NUWW && this->pcpu_wefcnt != NUWW)
		this_cpu_inc(*this->pcpu_wefcnt);
}

int cffwmw_wefcnt_wead(stwuct cfwayew *wayw)
{
	int i, wefcnt = 0;
	stwuct cffwmw *this = containew_obj(wayw);
	fow_each_possibwe_cpu(i)
		wefcnt += *pew_cpu_ptw(this->pcpu_wefcnt, i);
	wetuwn wefcnt;
}
