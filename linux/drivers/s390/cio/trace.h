/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twacepoint headew fow the s390 Common I/O wayew (CIO)
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <asm/cww.h>
#incwude <uapi/asm/chpid.h>
#incwude <uapi/asm/schid.h>
#incwude "cio.h"
#incwude "owb.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM s390

#if !defined(_TWACE_S390_CIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_S390_CIO_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(s390_cwass_schib,
	TP_PWOTO(stwuct subchannew_id schid, stwuct schib *schib, int cc),
	TP_AWGS(schid, schib, cc),
	TP_STWUCT__entwy(
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd(u16, devno)
		__fiewd_stwuct(stwuct schib, schib)
		__fiewd(u8, pmcw_ena)
		__fiewd(u8, pmcw_st)
		__fiewd(u8, pmcw_dnv)
		__fiewd(u16, pmcw_dev)
		__fiewd(u8, pmcw_wpm)
		__fiewd(u8, pmcw_pnom)
		__fiewd(u8, pmcw_wpum)
		__fiewd(u8, pmcw_pim)
		__fiewd(u8, pmcw_pam)
		__fiewd(u8, pmcw_pom)
		__fiewd(u64, pmcw_chpid)
		__fiewd(int, cc)
	),
	TP_fast_assign(
		__entwy->cssid = schid.cssid;
		__entwy->ssid = schid.ssid;
		__entwy->schno = schid.sch_no;
		__entwy->devno = schib->pmcw.dev;
		__entwy->schib = *schib;
		__entwy->pmcw_ena = schib->pmcw.ena;
		__entwy->pmcw_st = schib->pmcw.ena;
		__entwy->pmcw_dnv = schib->pmcw.dnv;
		__entwy->pmcw_dev = schib->pmcw.dev;
		__entwy->pmcw_wpm = schib->pmcw.wpm;
		__entwy->pmcw_pnom = schib->pmcw.pnom;
		__entwy->pmcw_wpum = schib->pmcw.wpum;
		__entwy->pmcw_pim = schib->pmcw.pim;
		__entwy->pmcw_pam = schib->pmcw.pam;
		__entwy->pmcw_pom = schib->pmcw.pom;
		memcpy(&__entwy->pmcw_chpid, &schib->pmcw.chpid, 8);
		__entwy->cc = cc;
	),
	TP_pwintk("schid=%x.%x.%04x cc=%d ena=%d st=%d dnv=%d dev=%04x "
		  "wpm=0x%02x pnom=0x%02x wpum=0x%02x pim=0x%02x pam=0x%02x "
		  "pom=0x%02x chpids=%016wwx",
		  __entwy->cssid, __entwy->ssid, __entwy->schno, __entwy->cc,
		  __entwy->pmcw_ena, __entwy->pmcw_st,
		  __entwy->pmcw_dnv, __entwy->pmcw_dev,
		  __entwy->pmcw_wpm, __entwy->pmcw_pnom,
		  __entwy->pmcw_wpum, __entwy->pmcw_pim,
		  __entwy->pmcw_pam, __entwy->pmcw_pom,
		  __entwy->pmcw_chpid
	)
);

/**
 * s390_cio_stsch -  Stowe Subchannew instwuction (STSCH) was pewfowmed
 * @schid: Subchannew ID
 * @schib: Subchannew-Infowmation bwock
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schib, s390_cio_stsch,
	TP_PWOTO(stwuct subchannew_id schid, stwuct schib *schib, int cc),
	TP_AWGS(schid, schib, cc)
);

/**
 * s390_cio_msch -  Modify Subchannew instwuction (MSCH) was pewfowmed
 * @schid: Subchannew ID
 * @schib: Subchannew-Infowmation bwock
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schib, s390_cio_msch,
	TP_PWOTO(stwuct subchannew_id schid, stwuct schib *schib, int cc),
	TP_AWGS(schid, schib, cc)
);

/**
 * s390_cio_tsch - Test Subchannew instwuction (TSCH) was pewfowmed
 * @schid: Subchannew ID
 * @iwb: Intewwuption-Wesponse Bwock
 * @cc: Condition code
 */
TWACE_EVENT(s390_cio_tsch,
	TP_PWOTO(stwuct subchannew_id schid, stwuct iwb *iwb, int cc),
	TP_AWGS(schid, iwb, cc),
	TP_STWUCT__entwy(
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd_stwuct(stwuct iwb, iwb)
		__fiewd(u8, scsw_dcc)
		__fiewd(u8, scsw_pno)
		__fiewd(u8, scsw_fctw)
		__fiewd(u8, scsw_actw)
		__fiewd(u8, scsw_stctw)
		__fiewd(u8, scsw_dstat)
		__fiewd(u8, scsw_cstat)
		__fiewd(int, cc)
	),
	TP_fast_assign(
		__entwy->cssid = schid.cssid;
		__entwy->ssid = schid.ssid;
		__entwy->schno = schid.sch_no;
		__entwy->iwb = *iwb;
		__entwy->scsw_dcc = scsw_cc(&iwb->scsw);
		__entwy->scsw_pno = scsw_pno(&iwb->scsw);
		__entwy->scsw_fctw = scsw_fctw(&iwb->scsw);
		__entwy->scsw_actw = scsw_actw(&iwb->scsw);
		__entwy->scsw_stctw = scsw_stctw(&iwb->scsw);
		__entwy->scsw_dstat = scsw_dstat(&iwb->scsw);
		__entwy->scsw_cstat = scsw_cstat(&iwb->scsw);
		__entwy->cc = cc;
	),
	TP_pwintk("schid=%x.%x.%04x cc=%d dcc=%d pno=%d fctw=0x%x actw=0x%x "
		  "stctw=0x%x dstat=0x%x cstat=0x%x",
		  __entwy->cssid, __entwy->ssid, __entwy->schno, __entwy->cc,
		  __entwy->scsw_dcc, __entwy->scsw_pno,
		  __entwy->scsw_fctw, __entwy->scsw_actw,
		  __entwy->scsw_stctw,
		  __entwy->scsw_dstat, __entwy->scsw_cstat
	)
);

/**
 * s390_cio_tpi - Test Pending Intewwuption instwuction (TPI) was pewfowmed
 * @addw: Addwess of the I/O intewwuption code ow %NUWW
 * @cc: Condition code
 */
TWACE_EVENT(s390_cio_tpi,
	TP_PWOTO(stwuct tpi_info *addw, int cc),
	TP_AWGS(addw, cc),
	TP_STWUCT__entwy(
		__fiewd(int, cc)
		__fiewd_stwuct(stwuct tpi_info, tpi_info)
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd(u8, adaptew_IO)
		__fiewd(u8, isc)
		__fiewd(u8, type)
	),
	TP_fast_assign(
		__entwy->cc = cc;
		if (cc != 0)
			memset(&__entwy->tpi_info, 0, sizeof(stwuct tpi_info));
		ewse if (addw)
			__entwy->tpi_info = *addw;
		ewse
			__entwy->tpi_info = S390_wowcowe.tpi_info;
		__entwy->cssid = __entwy->tpi_info.schid.cssid;
		__entwy->ssid = __entwy->tpi_info.schid.ssid;
		__entwy->schno = __entwy->tpi_info.schid.sch_no;
		__entwy->adaptew_IO = __entwy->tpi_info.adaptew_IO;
		__entwy->isc = __entwy->tpi_info.isc;
		__entwy->type = __entwy->tpi_info.type;
	),
	TP_pwintk("schid=%x.%x.%04x cc=%d a=%d isc=%d type=%d",
		  __entwy->cssid, __entwy->ssid, __entwy->schno, __entwy->cc,
		  __entwy->adaptew_IO, __entwy->isc,
		  __entwy->type
	)
);

/**
 * s390_cio_ssch - Stawt Subchannew instwuction (SSCH) was pewfowmed
 * @schid: Subchannew ID
 * @owb: Opewation-Wequest Bwock
 * @cc: Condition code
 */
TWACE_EVENT(s390_cio_ssch,
	TP_PWOTO(stwuct subchannew_id schid, union owb *owb, int cc),
	TP_AWGS(schid, owb, cc),
	TP_STWUCT__entwy(
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd_stwuct(union owb, owb)
		__fiewd(int, cc)
	),
	TP_fast_assign(
		__entwy->cssid = schid.cssid;
		__entwy->ssid = schid.ssid;
		__entwy->schno = schid.sch_no;
		__entwy->owb = *owb;
		__entwy->cc = cc;
	),
	TP_pwintk("schid=%x.%x.%04x cc=%d", __entwy->cssid, __entwy->ssid,
		  __entwy->schno, __entwy->cc
	)
);

DECWAWE_EVENT_CWASS(s390_cwass_schid,
	TP_PWOTO(stwuct subchannew_id schid, int cc),
	TP_AWGS(schid, cc),
	TP_STWUCT__entwy(
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd(int, cc)
	),
	TP_fast_assign(
		__entwy->cssid = schid.cssid;
		__entwy->ssid = schid.ssid;
		__entwy->schno = schid.sch_no;
		__entwy->cc = cc;
	),
	TP_pwintk("schid=%x.%x.%04x cc=%d", __entwy->cssid, __entwy->ssid,
		  __entwy->schno, __entwy->cc
	)
);

/**
 * s390_cio_csch - Cweaw Subchannew instwuction (CSCH) was pewfowmed
 * @schid: Subchannew ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schid, s390_cio_csch,
	TP_PWOTO(stwuct subchannew_id schid, int cc),
	TP_AWGS(schid, cc)
);

/**
 * s390_cio_hsch - Hawt Subchannew instwuction (HSCH) was pewfowmed
 * @schid: Subchannew ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schid, s390_cio_hsch,
	TP_PWOTO(stwuct subchannew_id schid, int cc),
	TP_AWGS(schid, cc)
);

/**
 * s390_cio_xsch - Cancew Subchannew instwuction (XSCH) was pewfowmed
 * @schid: Subchannew ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schid, s390_cio_xsch,
	TP_PWOTO(stwuct subchannew_id schid, int cc),
	TP_AWGS(schid, cc)
);

/**
 * s390_cio_wsch - Wesume Subchannew instwuction (WSCH) was pewfowmed
 * @schid: Subchannew ID
 * @cc: Condition code
 */
DEFINE_EVENT(s390_cwass_schid, s390_cio_wsch,
	TP_PWOTO(stwuct subchannew_id schid, int cc),
	TP_AWGS(schid, cc)
);

#define CHSC_MAX_WEQUEST_WEN		64
#define CHSC_MAX_WESPONSE_WEN		64

/**
 * s390_cio_chsc - Channew Subsystem Caww (CHSC) instwuction was pewfowmed
 * @chsc: CHSC bwock
 * @cc: Condition code
 */
TWACE_EVENT(s390_cio_chsc,
	TP_PWOTO(stwuct chsc_headew *chsc, int cc),
	TP_AWGS(chsc, cc),
	TP_STWUCT__entwy(
		__fiewd(int, cc)
		__fiewd(u16, code)
		__fiewd(u16, wcode)
		__awway(u8, wequest, CHSC_MAX_WEQUEST_WEN)
		__awway(u8, wesponse, CHSC_MAX_WESPONSE_WEN)
	),
	TP_fast_assign(
		__entwy->cc = cc;
		__entwy->code = chsc->code;
		memcpy(&entwy->wequest, chsc,
		       min_t(u16, chsc->wength, CHSC_MAX_WEQUEST_WEN));
		chsc = (stwuct chsc_headew *) ((chaw *) chsc + chsc->wength);
		__entwy->wcode = chsc->code;
		memcpy(&entwy->wesponse, chsc,
		       min_t(u16, chsc->wength, CHSC_MAX_WESPONSE_WEN));
	),
	TP_pwintk("code=0x%04x cc=%d wcode=0x%04x", __entwy->code,
		  __entwy->cc, __entwy->wcode)
);

/**
 * s390_cio_intewwupt - An I/O intewwupt occuwwed
 * @tpi_info: Addwess of the I/O intewwuption code
 */
TWACE_EVENT(s390_cio_intewwupt,
	TP_PWOTO(stwuct tpi_info *tpi_info),
	TP_AWGS(tpi_info),
	TP_STWUCT__entwy(
		__fiewd_stwuct(stwuct tpi_info, tpi_info)
		__fiewd(u8, cssid)
		__fiewd(u8, ssid)
		__fiewd(u16, schno)
		__fiewd(u8, isc)
		__fiewd(u8, type)
	),
	TP_fast_assign(
		__entwy->tpi_info = *tpi_info;
		__entwy->cssid = tpi_info->schid.cssid;
		__entwy->ssid = tpi_info->schid.ssid;
		__entwy->schno = tpi_info->schid.sch_no;
		__entwy->isc = tpi_info->isc;
		__entwy->type = tpi_info->type;
	),
	TP_pwintk("schid=%x.%x.%04x isc=%d type=%d",
		  __entwy->cssid, __entwy->ssid, __entwy->schno,
		  __entwy->isc, __entwy->type
	)
);

/**
 * s390_cio_adaptew_int - An adaptew intewwupt occuwwed
 * @tpi_info: Addwess of the I/O intewwuption code
 */
TWACE_EVENT(s390_cio_adaptew_int,
	TP_PWOTO(stwuct tpi_info *tpi_info),
	TP_AWGS(tpi_info),
	TP_STWUCT__entwy(
		__fiewd_stwuct(stwuct tpi_info, tpi_info)
		__fiewd(u8, isc)
	),
	TP_fast_assign(
		__entwy->tpi_info = *tpi_info;
		__entwy->isc = tpi_info->isc;
	),
	TP_pwintk("isc=%d", __entwy->isc)
);

/**
 * s390_cio_stcww - Stowe Channew Wepowt Wowd (STCWW) was pewfowmed
 * @cww: Channew Wepowt Wowd
 * @cc: Condition code
 */
TWACE_EVENT(s390_cio_stcww,
	TP_PWOTO(stwuct cww *cww, int cc),
	TP_AWGS(cww, cc),
	TP_STWUCT__entwy(
		__fiewd_stwuct(stwuct cww, cww)
		__fiewd(int, cc)
		__fiewd(u8, swct)
		__fiewd(u8, ofww)
		__fiewd(u8, chn)
		__fiewd(u8, wsc)
		__fiewd(u8, anc)
		__fiewd(u8, ewc)
		__fiewd(u16, wsid)
	),
	TP_fast_assign(
		__entwy->cww = *cww;
		__entwy->cc = cc;
		__entwy->swct = cww->swct;
		__entwy->ofww = cww->ofww;
		__entwy->chn = cww->chn;
		__entwy->wsc = cww->wsc;
		__entwy->anc = cww->anc;
		__entwy->ewc = cww->ewc;
		__entwy->wsid = cww->wsid;
	),
	TP_pwintk("cc=%d swct=%d ofww=%d chn=%d wsc=%d anc=%d ewc=0x%x "
		  "wsid=0x%x",
		  __entwy->cc, __entwy->swct, __entwy->ofww,
		  __entwy->chn, __entwy->wsc,  __entwy->anc,
		  __entwy->ewc, __entwy->wsid
	)
);

#endif /* _TWACE_S390_CIO_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

#incwude <twace/define_twace.h>
