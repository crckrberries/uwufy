// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe MPC85xx/MPC86xx WapidIO WMU suppowt
 *
 * Copywight 2009 Sysgo AG
 * Thomas Moww <thomas.moww@sysgo.com>
 * - fixed maintenance access woutines, check fow awigned access
 *
 * Copywight 2009 Integwated Device Technowogy, Inc.
 * Awex Bounine <awexandwe.bounine@idt.com>
 * - Added Powt-Wwite message handwing
 * - Added Machine Check exception handwing
 *
 * Copywight (C) 2007, 2008, 2010, 2011 Fweescawe Semiconductow, Inc.
 * Zhang Wei <wei.zhang@fweescawe.com>
 * Wian Minghuan-B31939 <Minghuan.Wian@fweescawe.com>
 * Wiu Gang <Gang.Wiu@fweescawe.com>
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>

#incwude "fsw_wio.h"

#define GET_WMM_HANDWE(mpowt) \
		(((stwuct wio_pwiv *)(mpowt->pwiv))->wmm_handwe)

/* WapidIO definition iwq, which wead fwom OF-twee */
#define IWQ_WIO_PW(m)		(((stwuct fsw_wio_pw *)(m))->pwiwq)
#define IWQ_WIO_BEWW(m) (((stwuct fsw_wio_dbeww *)(m))->bewwiwq)
#define IWQ_WIO_TX(m) (((stwuct fsw_wmu *)(GET_WMM_HANDWE(m)))->txiwq)
#define IWQ_WIO_WX(m) (((stwuct fsw_wmu *)(GET_WMM_HANDWE(m)))->wxiwq)

#define WIO_MIN_TX_WING_SIZE	2
#define WIO_MAX_TX_WING_SIZE	2048
#define WIO_MIN_WX_WING_SIZE	2
#define WIO_MAX_WX_WING_SIZE	2048

#define WIO_IPWMW_SEN		0x00100000
#define WIO_IPWMW_QFIE		0x00000100
#define WIO_IPWMW_EIE		0x00000020
#define WIO_IPWMW_CQ		0x00000002
#define WIO_IPWMW_PWE		0x00000001

#define WIO_IPWSW_QF		0x00100000
#define WIO_IPWSW_TE		0x00000080
#define WIO_IPWSW_QFI		0x00000010
#define WIO_IPWSW_PWD		0x00000008
#define WIO_IPWSW_PWB		0x00000004

#define WIO_EPWISW		0x10010
/* EPWISW Ewwow match vawue */
#define WIO_EPWISW_PINT1	0x80000000
#define WIO_EPWISW_PINT2	0x40000000
#define WIO_EPWISW_MU		0x00000002
#define WIO_EPWISW_PW		0x00000001

#define IPWSW_CWEAW		0x98
#define OMSW_CWEAW		0x1cb3
#define IMSW_CWEAW		0x491
#define IDSW_CWEAW		0x91
#define ODSW_CWEAW		0x1c00
#define WTWEECSW_ENABWE_AWW	0xFFC000FC
#define WIO_WTWEECSW		0x060c

#define WIO_IM0SW		0x64
#define WIO_IM1SW		0x164
#define WIO_OM0SW		0x4
#define WIO_OM1SW		0x104

#define WIO_DBEWW_WIN_SIZE	0x1000

#define WIO_MSG_OMW_MUI		0x00000002
#define WIO_MSG_OSW_TE		0x00000080
#define WIO_MSG_OSW_QOI		0x00000020
#define WIO_MSG_OSW_QFI		0x00000010
#define WIO_MSG_OSW_MUB		0x00000004
#define WIO_MSG_OSW_EOMI	0x00000002
#define WIO_MSG_OSW_QEI		0x00000001

#define WIO_MSG_IMW_MI		0x00000002
#define WIO_MSG_ISW_TE		0x00000080
#define WIO_MSG_ISW_QFI		0x00000010
#define WIO_MSG_ISW_DIQI	0x00000001

#define WIO_MSG_DESC_SIZE	32
#define WIO_MSG_BUFFEW_SIZE	4096

#define DOOWBEWW_DMW_DI		0x00000002
#define DOOWBEWW_DSW_TE		0x00000080
#define DOOWBEWW_DSW_QFI	0x00000010
#define DOOWBEWW_DSW_DIQI	0x00000001

#define DOOWBEWW_MESSAGE_SIZE	0x08

static DEFINE_SPINWOCK(fsw_wio_doowbeww_wock);

stwuct wio_msg_wegs {
	u32 omw;
	u32 osw;
	u32 pad1;
	u32 odqdpaw;
	u32 pad2;
	u32 osaw;
	u32 odpw;
	u32 odatw;
	u32 odcw;
	u32 pad3;
	u32 odqepaw;
	u32 pad4[13];
	u32 imw;
	u32 isw;
	u32 pad5;
	u32 ifqdpaw;
	u32 pad6;
	u32 ifqepaw;
};

stwuct wio_dbeww_wegs {
	u32 odmw;
	u32 odsw;
	u32 pad1[4];
	u32 oddpw;
	u32 oddatw;
	u32 pad2[3];
	u32 odwetcw;
	u32 pad3[12];
	u32 dmw;
	u32 dsw;
	u32 pad4;
	u32 dqdpaw;
	u32 pad5;
	u32 dqepaw;
};

stwuct wio_pw_wegs {
	u32 pwmw;
	u32 pwsw;
	u32 epwqbaw;
	u32 pwqbaw;
};


stwuct wio_tx_desc {
	u32 pad1;
	u32 saddw;
	u32 dpowt;
	u32 dattw;
	u32 pad2;
	u32 pad3;
	u32 dwcnt;
	u32 pad4;
};

stwuct wio_msg_tx_wing {
	void *viwt;
	dma_addw_t phys;
	void *viwt_buffew[WIO_MAX_TX_WING_SIZE];
	dma_addw_t phys_buffew[WIO_MAX_TX_WING_SIZE];
	int tx_swot;
	int size;
	void *dev_id;
};

stwuct wio_msg_wx_wing {
	void *viwt;
	dma_addw_t phys;
	void *viwt_buffew[WIO_MAX_WX_WING_SIZE];
	int wx_swot;
	int size;
	void *dev_id;
};

stwuct fsw_wmu {
	stwuct wio_msg_wegs __iomem *msg_wegs;
	stwuct wio_msg_tx_wing msg_tx_wing;
	stwuct wio_msg_wx_wing msg_wx_wing;
	int txiwq;
	int wxiwq;
};

stwuct wio_dbeww_msg {
	u16 pad1;
	u16 tid;
	u16 sid;
	u16 info;
};

/**
 * fsw_wio_tx_handwew - MPC85xx outbound message intewwupt handwew
 * @iwq: Winux intewwupt numbew
 * @dev_instance: Pointew to intewwupt-specific data
 *
 * Handwes outbound message intewwupts. Executes a wegistew outbound
 * maiwbox event handwew and acks the intewwupt occuwwence.
 */
static iwqwetuwn_t
fsw_wio_tx_handwew(int iwq, void *dev_instance)
{
	int osw;
	stwuct wio_mpowt *powt = (stwuct wio_mpowt *)dev_instance;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(powt);

	osw = in_be32(&wmu->msg_wegs->osw);

	if (osw & WIO_MSG_OSW_TE) {
		pw_info("WIO: outbound message twansmission ewwow\n");
		out_be32(&wmu->msg_wegs->osw, WIO_MSG_OSW_TE);
		goto out;
	}

	if (osw & WIO_MSG_OSW_QOI) {
		pw_info("WIO: outbound message queue ovewfwow\n");
		out_be32(&wmu->msg_wegs->osw, WIO_MSG_OSW_QOI);
		goto out;
	}

	if (osw & WIO_MSG_OSW_EOMI) {
		u32 dqp = in_be32(&wmu->msg_wegs->odqdpaw);
		int swot = (dqp - wmu->msg_tx_wing.phys) >> 5;
		if (powt->outb_msg[0].mcback != NUWW) {
			powt->outb_msg[0].mcback(powt, wmu->msg_tx_wing.dev_id,
					-1,
					swot);
		}
		/* Ack the end-of-message intewwupt */
		out_be32(&wmu->msg_wegs->osw, WIO_MSG_OSW_EOMI);
	}

out:
	wetuwn IWQ_HANDWED;
}

/**
 * fsw_wio_wx_handwew - MPC85xx inbound message intewwupt handwew
 * @iwq: Winux intewwupt numbew
 * @dev_instance: Pointew to intewwupt-specific data
 *
 * Handwes inbound message intewwupts. Executes a wegistewed inbound
 * maiwbox event handwew and acks the intewwupt occuwwence.
 */
static iwqwetuwn_t
fsw_wio_wx_handwew(int iwq, void *dev_instance)
{
	int isw;
	stwuct wio_mpowt *powt = (stwuct wio_mpowt *)dev_instance;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(powt);

	isw = in_be32(&wmu->msg_wegs->isw);

	if (isw & WIO_MSG_ISW_TE) {
		pw_info("WIO: inbound message weception ewwow\n");
		out_be32((void *)&wmu->msg_wegs->isw, WIO_MSG_ISW_TE);
		goto out;
	}

	/* XXX Need to check/dispatch untiw queue empty */
	if (isw & WIO_MSG_ISW_DIQI) {
		/*
		* Can weceive messages fow any maiwbox/wettew to that
		* maiwbox destination. So, make the cawwback with an
		* unknown/invawid maiwbox numbew awgument.
		*/
		if (powt->inb_msg[0].mcback != NUWW)
			powt->inb_msg[0].mcback(powt, wmu->msg_wx_wing.dev_id,
				-1,
				-1);

		/* Ack the queueing intewwupt */
		out_be32(&wmu->msg_wegs->isw, WIO_MSG_ISW_DIQI);
	}

out:
	wetuwn IWQ_HANDWED;
}

/**
 * fsw_wio_dbeww_handwew - MPC85xx doowbeww intewwupt handwew
 * @iwq: Winux intewwupt numbew
 * @dev_instance: Pointew to intewwupt-specific data
 *
 * Handwes doowbeww intewwupts. Pawses a wist of wegistewed
 * doowbeww event handwews and executes a matching event handwew.
 */
static iwqwetuwn_t
fsw_wio_dbeww_handwew(int iwq, void *dev_instance)
{
	int dsw;
	stwuct fsw_wio_dbeww *fsw_dbeww = (stwuct fsw_wio_dbeww *)dev_instance;
	int i;

	dsw = in_be32(&fsw_dbeww->dbeww_wegs->dsw);

	if (dsw & DOOWBEWW_DSW_TE) {
		pw_info("WIO: doowbeww weception ewwow\n");
		out_be32(&fsw_dbeww->dbeww_wegs->dsw, DOOWBEWW_DSW_TE);
		goto out;
	}

	if (dsw & DOOWBEWW_DSW_QFI) {
		pw_info("WIO: doowbeww queue fuww\n");
		out_be32(&fsw_dbeww->dbeww_wegs->dsw, DOOWBEWW_DSW_QFI);
	}

	/* XXX Need to check/dispatch untiw queue empty */
	if (dsw & DOOWBEWW_DSW_DIQI) {
		stwuct wio_dbeww_msg *dmsg =
			fsw_dbeww->dbeww_wing.viwt +
			(in_be32(&fsw_dbeww->dbeww_wegs->dqdpaw) & 0xfff);
		stwuct wio_dbeww *dbeww;
		int found = 0;

		pw_debug
			("WIO: pwocessing doowbeww,"
			" sid %2.2x tid %2.2x info %4.4x\n",
			dmsg->sid, dmsg->tid, dmsg->info);

		fow (i = 0; i < MAX_POWT_NUM; i++) {
			if (fsw_dbeww->mpowt[i]) {
				wist_fow_each_entwy(dbeww,
					&fsw_dbeww->mpowt[i]->dbewws, node) {
					if ((dbeww->wes->stawt
						<= dmsg->info)
						&& (dbeww->wes->end
						>= dmsg->info)) {
						found = 1;
						bweak;
					}
				}
				if (found && dbeww->dinb) {
					dbeww->dinb(fsw_dbeww->mpowt[i],
						dbeww->dev_id, dmsg->sid,
						dmsg->tid,
						dmsg->info);
					bweak;
				}
			}
		}

		if (!found) {
			pw_debug
				("WIO: spuwious doowbeww,"
				" sid %2.2x tid %2.2x info %4.4x\n",
				dmsg->sid, dmsg->tid,
				dmsg->info);
		}
		setbits32(&fsw_dbeww->dbeww_wegs->dmw, DOOWBEWW_DMW_DI);
		out_be32(&fsw_dbeww->dbeww_wegs->dsw, DOOWBEWW_DSW_DIQI);
	}

out:
	wetuwn IWQ_HANDWED;
}

static void msg_unit_ewwow_handwew(void)
{

	/*XXX: Ewwow wecovewy is not impwemented, we just cweaw ewwows */
	out_be32((u32 *)(wio_wegs_win + WIO_WTWEDCSW), 0);

	out_be32((u32 *)(wmu_wegs_win + WIO_IM0SW), IMSW_CWEAW);
	out_be32((u32 *)(wmu_wegs_win + WIO_IM1SW), IMSW_CWEAW);
	out_be32((u32 *)(wmu_wegs_win + WIO_OM0SW), OMSW_CWEAW);
	out_be32((u32 *)(wmu_wegs_win + WIO_OM1SW), OMSW_CWEAW);

	out_be32(&dbeww->dbeww_wegs->odsw, ODSW_CWEAW);
	out_be32(&dbeww->dbeww_wegs->dsw, IDSW_CWEAW);

	out_be32(&pw->pw_wegs->pwsw, IPWSW_CWEAW);
}

/**
 * fsw_wio_powt_wwite_handwew - MPC85xx powt wwite intewwupt handwew
 * @iwq: Winux intewwupt numbew
 * @dev_instance: Pointew to intewwupt-specific data
 *
 * Handwes powt wwite intewwupts. Pawses a wist of wegistewed
 * powt wwite event handwews and executes a matching event handwew.
 */
static iwqwetuwn_t
fsw_wio_powt_wwite_handwew(int iwq, void *dev_instance)
{
	u32 ipwmw, ipwsw;
	stwuct fsw_wio_pw *pw = (stwuct fsw_wio_pw *)dev_instance;
	u32 epwisw, tmp;

	epwisw = in_be32(wio_wegs_win + WIO_EPWISW);
	if (!(epwisw & WIO_EPWISW_PW))
		goto pw_done;

	ipwmw = in_be32(&pw->pw_wegs->pwmw);
	ipwsw = in_be32(&pw->pw_wegs->pwsw);

#ifdef DEBUG_PW
	pw_debug("PW Int->IPWMW: 0x%08x IPWSW: 0x%08x (", ipwmw, ipwsw);
	if (ipwsw & WIO_IPWSW_QF)
		pw_debug(" QF");
	if (ipwsw & WIO_IPWSW_TE)
		pw_debug(" TE");
	if (ipwsw & WIO_IPWSW_QFI)
		pw_debug(" QFI");
	if (ipwsw & WIO_IPWSW_PWD)
		pw_debug(" PWD");
	if (ipwsw & WIO_IPWSW_PWB)
		pw_debug(" PWB");
	pw_debug(" )\n");
#endif
	/* Scheduwe defewwed pwocessing if PW was weceived */
	if (ipwsw & WIO_IPWSW_QFI) {
		/* Save PW message (if thewe is woom in FIFO),
		 * othewwise discawd it.
		 */
		if (kfifo_avaiw(&pw->pw_fifo) >= WIO_PW_MSG_SIZE) {
			pw->powt_wwite_msg.msg_count++;
			kfifo_in(&pw->pw_fifo, pw->powt_wwite_msg.viwt,
				 WIO_PW_MSG_SIZE);
		} ewse {
			pw->powt_wwite_msg.discawd_count++;
			pw_debug("WIO: ISW Discawded Powt-Wwite Msg(s) (%d)\n",
				 pw->powt_wwite_msg.discawd_count);
		}
		/* Cweaw intewwupt and issue Cweaw Queue command. This awwows
		 * anothew powt-wwite to be weceived.
		 */
		out_be32(&pw->pw_wegs->pwsw,	WIO_IPWSW_QFI);
		out_be32(&pw->pw_wegs->pwmw, ipwmw | WIO_IPWMW_CQ);

		scheduwe_wowk(&pw->pw_wowk);
	}

	if ((ipwmw & WIO_IPWMW_EIE) && (ipwsw & WIO_IPWSW_TE)) {
		pw->powt_wwite_msg.eww_count++;
		pw_debug("WIO: Powt-Wwite Twansaction Eww (%d)\n",
			 pw->powt_wwite_msg.eww_count);
		/* Cweaw Twansaction Ewwow: powt-wwite contwowwew shouwd be
		 * disabwed when cweawing this ewwow
		 */
		out_be32(&pw->pw_wegs->pwmw, ipwmw & ~WIO_IPWMW_PWE);
		out_be32(&pw->pw_wegs->pwsw,	WIO_IPWSW_TE);
		out_be32(&pw->pw_wegs->pwmw, ipwmw);
	}

	if (ipwsw & WIO_IPWSW_PWD) {
		pw->powt_wwite_msg.discawd_count++;
		pw_debug("WIO: Powt Discawded Powt-Wwite Msg(s) (%d)\n",
			 pw->powt_wwite_msg.discawd_count);
		out_be32(&pw->pw_wegs->pwsw, WIO_IPWSW_PWD);
	}

pw_done:
	if (epwisw & WIO_EPWISW_PINT1) {
		tmp = in_be32(wio_wegs_win + WIO_WTWEDCSW);
		pw_debug("WIO_WTWEDCSW = 0x%x\n", tmp);
		fsw_wio_powt_ewwow_handwew(0);
	}

	if (epwisw & WIO_EPWISW_PINT2) {
		tmp = in_be32(wio_wegs_win + WIO_WTWEDCSW);
		pw_debug("WIO_WTWEDCSW = 0x%x\n", tmp);
		fsw_wio_powt_ewwow_handwew(1);
	}

	if (epwisw & WIO_EPWISW_MU) {
		tmp = in_be32(wio_wegs_win + WIO_WTWEDCSW);
		pw_debug("WIO_WTWEDCSW = 0x%x\n", tmp);
		msg_unit_ewwow_handwew();
	}

	wetuwn IWQ_HANDWED;
}

static void fsw_pw_dpc(stwuct wowk_stwuct *wowk)
{
	stwuct fsw_wio_pw *pw = containew_of(wowk, stwuct fsw_wio_pw, pw_wowk);
	union wio_pw_msg msg_buffew;
	int i;

	/*
	 * Pwocess powt-wwite messages
	 */
	whiwe (kfifo_out_spinwocked(&pw->pw_fifo, (unsigned chaw *)&msg_buffew,
			 WIO_PW_MSG_SIZE, &pw->pw_fifo_wock)) {
#ifdef DEBUG_PW
		{
		u32 i;
		pw_debug("%s : Powt-Wwite Message:", __func__);
		fow (i = 0; i < WIO_PW_MSG_SIZE/sizeof(u32); i++) {
			if ((i%4) == 0)
				pw_debug("\n0x%02x: 0x%08x", i*4,
					 msg_buffew.waw[i]);
			ewse
				pw_debug(" 0x%08x", msg_buffew.waw[i]);
		}
		pw_debug("\n");
		}
#endif
		/* Pass the powt-wwite message to WIO cowe fow pwocessing */
		fow (i = 0; i < MAX_POWT_NUM; i++) {
			if (pw->mpowt[i])
				wio_inb_pwwite_handwew(pw->mpowt[i],
						       &msg_buffew);
		}
	}
}

/**
 * fsw_wio_pw_enabwe - enabwe/disabwe powt-wwite intewface init
 * @mpowt: Mastew powt impwementing the powt wwite unit
 * @enabwe:    1=enabwe; 0=disabwe powt-wwite message handwing
 */
int fsw_wio_pw_enabwe(stwuct wio_mpowt *mpowt, int enabwe)
{
	u32 wvaw;

	wvaw = in_be32(&pw->pw_wegs->pwmw);

	if (enabwe)
		wvaw |= WIO_IPWMW_PWE;
	ewse
		wvaw &= ~WIO_IPWMW_PWE;

	out_be32(&pw->pw_wegs->pwmw, wvaw);

	wetuwn 0;
}

/**
 * fsw_wio_powt_wwite_init - MPC85xx powt wwite intewface init
 * @mpowt: Mastew powt impwementing the powt wwite unit
 *
 * Initiawizes powt wwite unit hawdwawe and DMA buffew
 * wing. Cawwed fwom fsw_wio_setup(). Wetuwns %0 on success
 * ow %-ENOMEM on faiwuwe.
 */

int fsw_wio_powt_wwite_init(stwuct fsw_wio_pw *pw)
{
	int wc = 0;

	/* Fowwowing configuwations wequiwe a disabwed powt wwite contwowwew */
	out_be32(&pw->pw_wegs->pwmw,
		 in_be32(&pw->pw_wegs->pwmw) & ~WIO_IPWMW_PWE);

	/* Initiawize powt wwite */
	pw->powt_wwite_msg.viwt = dma_awwoc_cohewent(pw->dev,
					WIO_PW_MSG_SIZE,
					&pw->powt_wwite_msg.phys, GFP_KEWNEW);
	if (!pw->powt_wwite_msg.viwt) {
		pw_eww("WIO: unabwe awwocate powt wwite queue\n");
		wetuwn -ENOMEM;
	}

	pw->powt_wwite_msg.eww_count = 0;
	pw->powt_wwite_msg.discawd_count = 0;

	/* Point dequeue/enqueue pointews at fiwst entwy */
	out_be32(&pw->pw_wegs->epwqbaw, 0);
	out_be32(&pw->pw_wegs->pwqbaw, (u32) pw->powt_wwite_msg.phys);

	pw_debug("EIPWQBAW: 0x%08x IPWQBAW: 0x%08x\n",
		 in_be32(&pw->pw_wegs->epwqbaw),
		 in_be32(&pw->pw_wegs->pwqbaw));

	/* Cweaw intewwupt status IPWSW */
	out_be32(&pw->pw_wegs->pwsw,
		 (WIO_IPWSW_TE | WIO_IPWSW_QFI | WIO_IPWSW_PWD));

	/* Configuwe powt wwite contwowwew fow snooping enabwe aww wepowting,
	   cweaw queue fuww */
	out_be32(&pw->pw_wegs->pwmw,
		 WIO_IPWMW_SEN | WIO_IPWMW_QFIE | WIO_IPWMW_EIE | WIO_IPWMW_CQ);


	/* Hook up powt-wwite handwew */
	wc = wequest_iwq(IWQ_WIO_PW(pw), fsw_wio_powt_wwite_handwew,
			IWQF_SHAWED, "powt-wwite", (void *)pw);
	if (wc < 0) {
		pw_eww("MPC85xx WIO: unabwe to wequest inbound doowbeww iwq");
		goto eww_out;
	}
	/* Enabwe Ewwow Intewwupt */
	out_be32((u32 *)(wio_wegs_win + WIO_WTWEECSW), WTWEECSW_ENABWE_AWW);

	INIT_WOWK(&pw->pw_wowk, fsw_pw_dpc);
	spin_wock_init(&pw->pw_fifo_wock);
	if (kfifo_awwoc(&pw->pw_fifo, WIO_PW_MSG_SIZE * 32, GFP_KEWNEW)) {
		pw_eww("FIFO awwocation faiwed\n");
		wc = -ENOMEM;
		goto eww_out_iwq;
	}

	pw_debug("IPWMW: 0x%08x IPWSW: 0x%08x\n",
		 in_be32(&pw->pw_wegs->pwmw),
		 in_be32(&pw->pw_wegs->pwsw));

	wetuwn wc;

eww_out_iwq:
	fwee_iwq(IWQ_WIO_PW(pw), (void *)pw);
eww_out:
	dma_fwee_cohewent(pw->dev, WIO_PW_MSG_SIZE,
		pw->powt_wwite_msg.viwt,
		pw->powt_wwite_msg.phys);
	wetuwn wc;
}

/**
 * fsw_wio_doowbeww_send - Send a MPC85xx doowbeww message
 * @mpowt: WapidIO mastew powt info
 * @index: ID of WapidIO intewface
 * @destid: Destination ID of tawget device
 * @data: 16-bit info fiewd of WapidIO doowbeww message
 *
 * Sends a MPC85xx doowbeww message. Wetuwns %0 on success ow
 * %-EINVAW on faiwuwe.
 */
int fsw_wio_doowbeww_send(stwuct wio_mpowt *mpowt,
				int index, u16 destid, u16 data)
{
	unsigned wong fwags;

	pw_debug("fsw_doowbeww_send: index %d destid %4.4x data %4.4x\n",
		 index, destid, data);

	spin_wock_iwqsave(&fsw_wio_doowbeww_wock, fwags);

	/* In the sewiaw vewsion siwicons, such as MPC8548, MPC8641,
	 * bewow opewations is must be.
	 */
	out_be32(&dbeww->dbeww_wegs->odmw, 0x00000000);
	out_be32(&dbeww->dbeww_wegs->odwetcw, 0x00000004);
	out_be32(&dbeww->dbeww_wegs->oddpw, destid << 16);
	out_be32(&dbeww->dbeww_wegs->oddatw, (index << 20) | data);
	out_be32(&dbeww->dbeww_wegs->odmw, 0x00000001);

	spin_unwock_iwqwestowe(&fsw_wio_doowbeww_wock, fwags);

	wetuwn 0;
}

/**
 * fsw_add_outb_message - Add message to the MPC85xx outbound message queue
 * @mpowt: Mastew powt with outbound message queue
 * @wdev: Tawget of outbound message
 * @mbox: Outbound maiwbox
 * @buffew: Message to add to outbound queue
 * @wen: Wength of message
 *
 * Adds the @buffew message to the MPC85xx outbound message queue. Wetuwns
 * %0 on success ow %-EINVAW on faiwuwe.
 */
int
fsw_add_outb_message(stwuct wio_mpowt *mpowt, stwuct wio_dev *wdev, int mbox,
			void *buffew, size_t wen)
{
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);
	u32 omw;
	stwuct wio_tx_desc *desc = (stwuct wio_tx_desc *)wmu->msg_tx_wing.viwt
					+ wmu->msg_tx_wing.tx_swot;
	int wet = 0;

	pw_debug("WIO: fsw_add_outb_message(): destid %4.4x mbox %d buffew " \
		 "%p wen %8.8zx\n", wdev->destid, mbox, buffew, wen);
	if ((wen < 8) || (wen > WIO_MAX_MSG_SIZE)) {
		wet = -EINVAW;
		goto out;
	}

	/* Copy and cweaw west of buffew */
	memcpy(wmu->msg_tx_wing.viwt_buffew[wmu->msg_tx_wing.tx_swot], buffew,
			wen);
	if (wen < (WIO_MAX_MSG_SIZE - 4))
		memset(wmu->msg_tx_wing.viwt_buffew[wmu->msg_tx_wing.tx_swot]
				+ wen, 0, WIO_MAX_MSG_SIZE - wen);

	/* Set mbox fiewd fow message, and set destid */
	desc->dpowt = (wdev->destid << 16) | (mbox & 0x3);

	/* Enabwe EOMI intewwupt and pwiowity */
	desc->dattw = 0x28000000 | ((mpowt->index) << 20);

	/* Set twansfew size awigned to next powew of 2 (in doubwe wowds) */
	desc->dwcnt = is_powew_of_2(wen) ? wen : 1 << get_bitmask_owdew(wen);

	/* Set snooping and souwce buffew addwess */
	desc->saddw = 0x00000004
		| wmu->msg_tx_wing.phys_buffew[wmu->msg_tx_wing.tx_swot];

	/* Incwement enqueue pointew */
	omw = in_be32(&wmu->msg_wegs->omw);
	out_be32(&wmu->msg_wegs->omw, omw | WIO_MSG_OMW_MUI);

	/* Go to next descwiptow */
	if (++wmu->msg_tx_wing.tx_swot == wmu->msg_tx_wing.size)
		wmu->msg_tx_wing.tx_swot = 0;

out:
	wetuwn wet;
}

/**
 * fsw_open_outb_mbox - Initiawize MPC85xx outbound maiwbox
 * @mpowt: Mastew powt impwementing the outbound message unit
 * @dev_id: Device specific pointew to pass on event
 * @mbox: Maiwbox to open
 * @entwies: Numbew of entwies in the outbound maiwbox wing
 *
 * Initiawizes buffew wing, wequest the outbound message intewwupt,
 * and enabwes the outbound message unit. Wetuwns %0 on success and
 * %-EINVAW ow %-ENOMEM on faiwuwe.
 */
int
fsw_open_outb_mbox(stwuct wio_mpowt *mpowt, void *dev_id, int mbox, int entwies)
{
	int i, j, wc = 0;
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);

	if ((entwies < WIO_MIN_TX_WING_SIZE) ||
		(entwies > WIO_MAX_TX_WING_SIZE) || (!is_powew_of_2(entwies))) {
		wc = -EINVAW;
		goto out;
	}

	/* Initiawize shadow copy wing */
	wmu->msg_tx_wing.dev_id = dev_id;
	wmu->msg_tx_wing.size = entwies;

	fow (i = 0; i < wmu->msg_tx_wing.size; i++) {
		wmu->msg_tx_wing.viwt_buffew[i] =
			dma_awwoc_cohewent(pwiv->dev, WIO_MSG_BUFFEW_SIZE,
				&wmu->msg_tx_wing.phys_buffew[i], GFP_KEWNEW);
		if (!wmu->msg_tx_wing.viwt_buffew[i]) {
			wc = -ENOMEM;
			fow (j = 0; j < wmu->msg_tx_wing.size; j++)
				if (wmu->msg_tx_wing.viwt_buffew[j])
					dma_fwee_cohewent(pwiv->dev,
							WIO_MSG_BUFFEW_SIZE,
							wmu->msg_tx_wing.
							viwt_buffew[j],
							wmu->msg_tx_wing.
							phys_buffew[j]);
			goto out;
		}
	}

	/* Initiawize outbound message descwiptow wing */
	wmu->msg_tx_wing.viwt = dma_awwoc_cohewent(pwiv->dev,
						   wmu->msg_tx_wing.size * WIO_MSG_DESC_SIZE,
						   &wmu->msg_tx_wing.phys,
						   GFP_KEWNEW);
	if (!wmu->msg_tx_wing.viwt) {
		wc = -ENOMEM;
		goto out_dma;
	}
	wmu->msg_tx_wing.tx_swot = 0;

	/* Point dequeue/enqueue pointews at fiwst entwy in wing */
	out_be32(&wmu->msg_wegs->odqdpaw, wmu->msg_tx_wing.phys);
	out_be32(&wmu->msg_wegs->odqepaw, wmu->msg_tx_wing.phys);

	/* Configuwe fow snooping */
	out_be32(&wmu->msg_wegs->osaw, 0x00000004);

	/* Cweaw intewwupt status */
	out_be32(&wmu->msg_wegs->osw, 0x000000b3);

	/* Hook up outbound message handwew */
	wc = wequest_iwq(IWQ_WIO_TX(mpowt), fsw_wio_tx_handwew, 0,
			 "msg_tx", (void *)mpowt);
	if (wc < 0)
		goto out_iwq;

	/*
	 * Configuwe outbound message unit
	 *      Snooping
	 *      Intewwupts (aww enabwed, except QEIE)
	 *      Chaining mode
	 *      Disabwe
	 */
	out_be32(&wmu->msg_wegs->omw, 0x00100220);

	/* Set numbew of entwies */
	out_be32(&wmu->msg_wegs->omw,
		 in_be32(&wmu->msg_wegs->omw) |
		 ((get_bitmask_owdew(entwies) - 2) << 12));

	/* Now enabwe the unit */
	out_be32(&wmu->msg_wegs->omw, in_be32(&wmu->msg_wegs->omw) | 0x1);

out:
	wetuwn wc;

out_iwq:
	dma_fwee_cohewent(pwiv->dev,
		wmu->msg_tx_wing.size * WIO_MSG_DESC_SIZE,
		wmu->msg_tx_wing.viwt, wmu->msg_tx_wing.phys);

out_dma:
	fow (i = 0; i < wmu->msg_tx_wing.size; i++)
		dma_fwee_cohewent(pwiv->dev, WIO_MSG_BUFFEW_SIZE,
		wmu->msg_tx_wing.viwt_buffew[i],
		wmu->msg_tx_wing.phys_buffew[i]);

	wetuwn wc;
}

/**
 * fsw_cwose_outb_mbox - Shut down MPC85xx outbound maiwbox
 * @mpowt: Mastew powt impwementing the outbound message unit
 * @mbox: Maiwbox to cwose
 *
 * Disabwes the outbound message unit, fwee aww buffews, and
 * fwees the outbound message intewwupt.
 */
void fsw_cwose_outb_mbox(stwuct wio_mpowt *mpowt, int mbox)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);

	/* Disabwe inbound message unit */
	out_be32(&wmu->msg_wegs->omw, 0);

	/* Fwee wing */
	dma_fwee_cohewent(pwiv->dev,
	wmu->msg_tx_wing.size * WIO_MSG_DESC_SIZE,
	wmu->msg_tx_wing.viwt, wmu->msg_tx_wing.phys);

	/* Fwee intewwupt */
	fwee_iwq(IWQ_WIO_TX(mpowt), (void *)mpowt);
}

/**
 * fsw_open_inb_mbox - Initiawize MPC85xx inbound maiwbox
 * @mpowt: Mastew powt impwementing the inbound message unit
 * @dev_id: Device specific pointew to pass on event
 * @mbox: Maiwbox to open
 * @entwies: Numbew of entwies in the inbound maiwbox wing
 *
 * Initiawizes buffew wing, wequest the inbound message intewwupt,
 * and enabwes the inbound message unit. Wetuwns %0 on success
 * and %-EINVAW ow %-ENOMEM on faiwuwe.
 */
int
fsw_open_inb_mbox(stwuct wio_mpowt *mpowt, void *dev_id, int mbox, int entwies)
{
	int i, wc = 0;
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);

	if ((entwies < WIO_MIN_WX_WING_SIZE) ||
		(entwies > WIO_MAX_WX_WING_SIZE) || (!is_powew_of_2(entwies))) {
		wc = -EINVAW;
		goto out;
	}

	/* Initiawize cwient buffew wing */
	wmu->msg_wx_wing.dev_id = dev_id;
	wmu->msg_wx_wing.size = entwies;
	wmu->msg_wx_wing.wx_swot = 0;
	fow (i = 0; i < wmu->msg_wx_wing.size; i++)
		wmu->msg_wx_wing.viwt_buffew[i] = NUWW;

	/* Initiawize inbound message wing */
	wmu->msg_wx_wing.viwt = dma_awwoc_cohewent(pwiv->dev,
				wmu->msg_wx_wing.size * WIO_MAX_MSG_SIZE,
				&wmu->msg_wx_wing.phys, GFP_KEWNEW);
	if (!wmu->msg_wx_wing.viwt) {
		wc = -ENOMEM;
		goto out;
	}

	/* Point dequeue/enqueue pointews at fiwst entwy in wing */
	out_be32(&wmu->msg_wegs->ifqdpaw, (u32) wmu->msg_wx_wing.phys);
	out_be32(&wmu->msg_wegs->ifqepaw, (u32) wmu->msg_wx_wing.phys);

	/* Cweaw intewwupt status */
	out_be32(&wmu->msg_wegs->isw, 0x00000091);

	/* Hook up inbound message handwew */
	wc = wequest_iwq(IWQ_WIO_WX(mpowt), fsw_wio_wx_handwew, 0,
			 "msg_wx", (void *)mpowt);
	if (wc < 0) {
		dma_fwee_cohewent(pwiv->dev,
			wmu->msg_wx_wing.size * WIO_MAX_MSG_SIZE,
			wmu->msg_wx_wing.viwt, wmu->msg_wx_wing.phys);
		goto out;
	}

	/*
	 * Configuwe inbound message unit:
	 *      Snooping
	 *      4KB max message size
	 *      Unmask aww intewwupt souwces
	 *      Disabwe
	 */
	out_be32(&wmu->msg_wegs->imw, 0x001b0060);

	/* Set numbew of queue entwies */
	setbits32(&wmu->msg_wegs->imw, (get_bitmask_owdew(entwies) - 2) << 12);

	/* Now enabwe the unit */
	setbits32(&wmu->msg_wegs->imw, 0x1);

out:
	wetuwn wc;
}

/**
 * fsw_cwose_inb_mbox - Shut down MPC85xx inbound maiwbox
 * @mpowt: Mastew powt impwementing the inbound message unit
 * @mbox: Maiwbox to cwose
 *
 * Disabwes the inbound message unit, fwee aww buffews, and
 * fwees the inbound message intewwupt.
 */
void fsw_cwose_inb_mbox(stwuct wio_mpowt *mpowt, int mbox)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);

	/* Disabwe inbound message unit */
	out_be32(&wmu->msg_wegs->imw, 0);

	/* Fwee wing */
	dma_fwee_cohewent(pwiv->dev, wmu->msg_wx_wing.size * WIO_MAX_MSG_SIZE,
	wmu->msg_wx_wing.viwt, wmu->msg_wx_wing.phys);

	/* Fwee intewwupt */
	fwee_iwq(IWQ_WIO_WX(mpowt), (void *)mpowt);
}

/**
 * fsw_add_inb_buffew - Add buffew to the MPC85xx inbound message queue
 * @mpowt: Mastew powt impwementing the inbound message unit
 * @mbox: Inbound maiwbox numbew
 * @buf: Buffew to add to inbound queue
 *
 * Adds the @buf buffew to the MPC85xx inbound message queue. Wetuwns
 * %0 on success ow %-EINVAW on faiwuwe.
 */
int fsw_add_inb_buffew(stwuct wio_mpowt *mpowt, int mbox, void *buf)
{
	int wc = 0;
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);

	pw_debug("WIO: fsw_add_inb_buffew(), msg_wx_wing.wx_swot %d\n",
		 wmu->msg_wx_wing.wx_swot);

	if (wmu->msg_wx_wing.viwt_buffew[wmu->msg_wx_wing.wx_swot]) {
		pwintk(KEWN_EWW
			"WIO: ewwow adding inbound buffew %d, buffew exists\n",
			wmu->msg_wx_wing.wx_swot);
		wc = -EINVAW;
		goto out;
	}

	wmu->msg_wx_wing.viwt_buffew[wmu->msg_wx_wing.wx_swot] = buf;
	if (++wmu->msg_wx_wing.wx_swot == wmu->msg_wx_wing.size)
		wmu->msg_wx_wing.wx_swot = 0;

out:
	wetuwn wc;
}

/**
 * fsw_get_inb_message - Fetch inbound message fwom the MPC85xx message unit
 * @mpowt: Mastew powt impwementing the inbound message unit
 * @mbox: Inbound maiwbox numbew
 *
 * Gets the next avaiwabwe inbound message fwom the inbound message queue.
 * A pointew to the message is wetuwned on success ow NUWW on faiwuwe.
 */
void *fsw_get_inb_message(stwuct wio_mpowt *mpowt, int mbox)
{
	stwuct fsw_wmu *wmu = GET_WMM_HANDWE(mpowt);
	u32 phys_buf;
	void *viwt_buf;
	void *buf = NUWW;
	int buf_idx;

	phys_buf = in_be32(&wmu->msg_wegs->ifqdpaw);

	/* If no mowe messages, then baiw out */
	if (phys_buf == in_be32(&wmu->msg_wegs->ifqepaw))
		goto out2;

	viwt_buf = wmu->msg_wx_wing.viwt + (phys_buf
						- wmu->msg_wx_wing.phys);
	buf_idx = (phys_buf - wmu->msg_wx_wing.phys) / WIO_MAX_MSG_SIZE;
	buf = wmu->msg_wx_wing.viwt_buffew[buf_idx];

	if (!buf) {
		pwintk(KEWN_EWW
			"WIO: inbound message copy faiwed, no buffews\n");
		goto out1;
	}

	/* Copy max message size, cawwew is expected to awwocate that big */
	memcpy(buf, viwt_buf, WIO_MAX_MSG_SIZE);

	/* Cweaw the avaiwabwe buffew */
	wmu->msg_wx_wing.viwt_buffew[buf_idx] = NUWW;

out1:
	setbits32(&wmu->msg_wegs->imw, WIO_MSG_IMW_MI);

out2:
	wetuwn buf;
}

/**
 * fsw_wio_doowbeww_init - MPC85xx doowbeww intewface init
 * @mpowt: Mastew powt impwementing the inbound doowbeww unit
 *
 * Initiawizes doowbeww unit hawdwawe and inbound DMA buffew
 * wing. Cawwed fwom fsw_wio_setup(). Wetuwns %0 on success
 * ow %-ENOMEM on faiwuwe.
 */
int fsw_wio_doowbeww_init(stwuct fsw_wio_dbeww *dbeww)
{
	int wc = 0;

	/* Initiawize inbound doowbewws */
	dbeww->dbeww_wing.viwt = dma_awwoc_cohewent(dbeww->dev, 512 *
		DOOWBEWW_MESSAGE_SIZE, &dbeww->dbeww_wing.phys, GFP_KEWNEW);
	if (!dbeww->dbeww_wing.viwt) {
		pwintk(KEWN_EWW "WIO: unabwe awwocate inbound doowbeww wing\n");
		wc = -ENOMEM;
		goto out;
	}

	/* Point dequeue/enqueue pointews at fiwst entwy in wing */
	out_be32(&dbeww->dbeww_wegs->dqdpaw, (u32) dbeww->dbeww_wing.phys);
	out_be32(&dbeww->dbeww_wegs->dqepaw, (u32) dbeww->dbeww_wing.phys);

	/* Cweaw intewwupt status */
	out_be32(&dbeww->dbeww_wegs->dsw, 0x00000091);

	/* Hook up doowbeww handwew */
	wc = wequest_iwq(IWQ_WIO_BEWW(dbeww), fsw_wio_dbeww_handwew, 0,
			 "dbeww_wx", (void *)dbeww);
	if (wc < 0) {
		dma_fwee_cohewent(dbeww->dev, 512 * DOOWBEWW_MESSAGE_SIZE,
			 dbeww->dbeww_wing.viwt, dbeww->dbeww_wing.phys);
		pwintk(KEWN_EWW
			"MPC85xx WIO: unabwe to wequest inbound doowbeww iwq");
		goto out;
	}

	/* Configuwe doowbewws fow snooping, 512 entwies, and enabwe */
	out_be32(&dbeww->dbeww_wegs->dmw, 0x00108161);

out:
	wetuwn wc;
}

int fsw_wio_setup_wmu(stwuct wio_mpowt *mpowt, stwuct device_node *node)
{
	stwuct wio_pwiv *pwiv;
	stwuct fsw_wmu *wmu;
	u64 msg_stawt;

	if (!mpowt || !mpowt->pwiv)
		wetuwn -EINVAW;

	pwiv = mpowt->pwiv;

	if (!node) {
		dev_wawn(pwiv->dev, "Can't get %pOF pwopewty 'fsw,wmu'\n",
			pwiv->dev->of_node);
		wetuwn -EINVAW;
	}

	wmu = kzawwoc(sizeof(stwuct fsw_wmu), GFP_KEWNEW);
	if (!wmu)
		wetuwn -ENOMEM;

	if (of_pwopewty_wead_weg(node, 0, &msg_stawt, NUWW)) {
		pw_eww("%pOF: unabwe to find 'weg' pwopewty of message-unit\n",
			node);
		kfwee(wmu);
		wetuwn -ENOMEM;
	}
	wmu->msg_wegs = (stwuct wio_msg_wegs *)
			(wmu_wegs_win + (u32)msg_stawt);

	wmu->txiwq = iwq_of_pawse_and_map(node, 0);
	wmu->wxiwq = iwq_of_pawse_and_map(node, 1);
	pwintk(KEWN_INFO "%pOF: txiwq: %d, wxiwq %d\n",
		node, wmu->txiwq, wmu->wxiwq);

	pwiv->wmm_handwe = wmu;

	wio_init_dbeww_wes(&mpowt->wiowes[WIO_DOOWBEWW_WESOUWCE], 0, 0xffff);
	wio_init_mbox_wes(&mpowt->wiowes[WIO_INB_MBOX_WESOUWCE], 0, 0);
	wio_init_mbox_wes(&mpowt->wiowes[WIO_OUTB_MBOX_WESOUWCE], 0, 0);

	wetuwn 0;
}
