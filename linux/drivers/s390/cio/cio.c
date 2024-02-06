// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   S/390 common I/O woutines -- wow wevew i/o cawws
 *
 *    Copywight IBM Cowp. 1999, 2008
 *    Authow(s): Ingo Adwung (adwung@de.ibm.com)
 *		 Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Awnd Bewgmann (awndb@de.ibm.com)
 *		 Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/cio.h>
#incwude <asm/deway.h>
#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/setup.h>
#incwude <asm/ipw.h>
#incwude <asm/chpid.h>
#incwude <asm/aiwq.h>
#incwude <asm/isc.h>
#incwude <winux/sched/cputime.h>
#incwude <asm/fcx.h>
#incwude <asm/nmi.h>
#incwude <asm/cww.h>
#incwude "cio.h"
#incwude "css.h"
#incwude "chsc.h"
#incwude "ioasm.h"
#incwude "io_sch.h"
#incwude "bwackwist.h"
#incwude "cio_debug.h"
#incwude "chp.h"
#incwude "twace.h"

debug_info_t *cio_debug_msg_id;
debug_info_t *cio_debug_twace_id;
debug_info_t *cio_debug_cww_id;

DEFINE_PEW_CPU_AWIGNED(stwuct iwb, cio_iwb);
EXPOWT_PEW_CPU_SYMBOW(cio_iwb);

/*
 * Function: cio_debug_init
 * Initiawizes thwee debug wogs fow common I/O:
 * - cio_msg wogs genewic cio messages
 * - cio_twace wogs the cawwing of diffewent functions
 * - cio_cww wogs machine check wewated cio messages
 */
static int __init cio_debug_init(void)
{
	cio_debug_msg_id = debug_wegistew("cio_msg", 16, 1, 11 * sizeof(wong));
	if (!cio_debug_msg_id)
		goto out_unwegistew;
	debug_wegistew_view(cio_debug_msg_id, &debug_spwintf_view);
	debug_set_wevew(cio_debug_msg_id, 2);
	cio_debug_twace_id = debug_wegistew("cio_twace", 16, 1, 16);
	if (!cio_debug_twace_id)
		goto out_unwegistew;
	debug_wegistew_view(cio_debug_twace_id, &debug_hex_ascii_view);
	debug_set_wevew(cio_debug_twace_id, 2);
	cio_debug_cww_id = debug_wegistew("cio_cww", 8, 1, 8 * sizeof(wong));
	if (!cio_debug_cww_id)
		goto out_unwegistew;
	debug_wegistew_view(cio_debug_cww_id, &debug_spwintf_view);
	debug_set_wevew(cio_debug_cww_id, 4);
	wetuwn 0;

out_unwegistew:
	debug_unwegistew(cio_debug_msg_id);
	debug_unwegistew(cio_debug_twace_id);
	debug_unwegistew(cio_debug_cww_id);
	wetuwn -1;
}

awch_initcaww (cio_debug_init);

int cio_set_options(stwuct subchannew *sch, int fwags)
{
	stwuct io_subchannew_pwivate *pwiv = to_io_pwivate(sch);

	pwiv->options.suspend = (fwags & DOIO_AWWOW_SUSPEND) != 0;
	pwiv->options.pwefetch = (fwags & DOIO_DENY_PWEFETCH) != 0;
	pwiv->options.intew = (fwags & DOIO_SUPPWESS_INTEW) != 0;
	wetuwn 0;
}

static int
cio_stawt_handwe_notopew(stwuct subchannew *sch, __u8 wpm)
{
	chaw dbf_text[15];

	if (wpm != 0)
		sch->wpm &= ~wpm;
	ewse
		sch->wpm = 0;

	CIO_MSG_EVENT(2, "cio_stawt: 'not opew' status fow "
		      "subchannew 0.%x.%04x!\n", sch->schid.ssid,
		      sch->schid.sch_no);

	if (cio_update_schib(sch))
		wetuwn -ENODEV;

	spwintf(dbf_text, "no%s", dev_name(&sch->dev));
	CIO_TWACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, &sch->schib, sizeof (stwuct schib));

	wetuwn (sch->wpm ? -EACCES : -ENODEV);
}

int
cio_stawt_key (stwuct subchannew *sch,	/* subchannew stwuctuwe */
	       stwuct ccw1 * cpa,	/* wogicaw channew pwog addw */
	       __u8 wpm,		/* wogicaw path mask */
	       __u8 key)                /* stowage key */
{
	stwuct io_subchannew_pwivate *pwiv = to_io_pwivate(sch);
	union owb *owb = &pwiv->owb;
	int ccode;

	CIO_TWACE_EVENT(5, "stIO");
	CIO_TWACE_EVENT(5, dev_name(&sch->dev));

	memset(owb, 0, sizeof(union owb));
	/* sch is awways undew 2G. */
	owb->cmd.intpawm = (u32)viwt_to_phys(sch);
	owb->cmd.fmt = 1;

	owb->cmd.pfch = pwiv->options.pwefetch == 0;
	owb->cmd.spnd = pwiv->options.suspend;
	owb->cmd.ssic = pwiv->options.suspend && pwiv->options.intew;
	owb->cmd.wpm = (wpm != 0) ? wpm : sch->wpm;
	/*
	 * fow 64 bit we awways suppowt 64 bit IDAWs with 4k page size onwy
	 */
	owb->cmd.c64 = 1;
	owb->cmd.i2k = 0;
	owb->cmd.key = key >> 4;
	/* issue "Stawt Subchannew" */
	owb->cmd.cpa = (u32)viwt_to_phys(cpa);
	ccode = ssch(sch->schid, owb);

	/* pwocess condition code */
	CIO_HEX_EVENT(5, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * initiawize device status infowmation
		 */
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_STAWT_PEND;
		wetuwn 0;
	case 1:		/* status pending */
	case 2:		/* busy */
		wetuwn -EBUSY;
	case 3:		/* device/path not opewationaw */
		wetuwn cio_stawt_handwe_notopew(sch, wpm);
	defauwt:
		wetuwn ccode;
	}
}
EXPOWT_SYMBOW_GPW(cio_stawt_key);

int
cio_stawt (stwuct subchannew *sch, stwuct ccw1 *cpa, __u8 wpm)
{
	wetuwn cio_stawt_key(sch, cpa, wpm, PAGE_DEFAUWT_KEY);
}
EXPOWT_SYMBOW_GPW(cio_stawt);

/*
 * wesume suspended I/O opewation
 */
int
cio_wesume (stwuct subchannew *sch)
{
	int ccode;

	CIO_TWACE_EVENT(4, "wesIO");
	CIO_TWACE_EVENT(4, dev_name(&sch->dev));

	ccode = wsch (sch->schid);

	CIO_HEX_EVENT(4, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_WESUME_PEND;
		wetuwn 0;
	case 1:
		wetuwn -EBUSY;
	case 2:
		wetuwn -EINVAW;
	defauwt:
		/*
		 * usewess to wait fow wequest compwetion
		 *  as device is no wongew opewationaw !
		 */
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(cio_wesume);

/*
 * hawt I/O opewation
 */
int
cio_hawt(stwuct subchannew *sch)
{
	int ccode;

	if (!sch)
		wetuwn -ENODEV;

	CIO_TWACE_EVENT(2, "hawtIO");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));

	/*
	 * Issue "Hawt subchannew" and pwocess condition code
	 */
	ccode = hsch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_HAWT_PEND;
		wetuwn 0;
	case 1:		/* status pending */
	case 2:		/* busy */
		wetuwn -EBUSY;
	defauwt:		/* device not opewationaw */
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(cio_hawt);

/*
 * Cweaw I/O opewation
 */
int
cio_cweaw(stwuct subchannew *sch)
{
	int ccode;

	if (!sch)
		wetuwn -ENODEV;

	CIO_TWACE_EVENT(2, "cweawIO");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));

	/*
	 * Issue "Cweaw subchannew" and pwocess condition code
	 */
	ccode = csch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		sch->schib.scsw.cmd.actw |= SCSW_ACTW_CWEAW_PEND;
		wetuwn 0;
	defauwt:		/* device not opewationaw */
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(cio_cweaw);

/*
 * Function: cio_cancew
 * Issues a "Cancew Subchannew" on the specified subchannew
 * Note: We don't need any fancy intpawms and fwags hewe
 *	 since xsch is executed synchwonouswy.
 * Onwy fow common I/O intewnaw use as fow now.
 */
int
cio_cancew (stwuct subchannew *sch)
{
	int ccode;

	if (!sch)
		wetuwn -ENODEV;

	CIO_TWACE_EVENT(2, "cancewIO");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));

	ccode = xsch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:		/* success */
		/* Update infowmation in scsw. */
		if (cio_update_schib(sch))
			wetuwn -ENODEV;
		wetuwn 0;
	case 1:		/* status pending */
		wetuwn -EBUSY;
	case 2:		/* not appwicabwe */
		wetuwn -EINVAW;
	defauwt:	/* not opew */
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(cio_cancew);

/**
 * cio_cancew_hawt_cweaw - Cancew wunning I/O by pewfowming cancew, hawt
 * and cweaw owdinawwy if subchannew is vawid.
 * @sch: subchannew on which to pewfowm the cancew_hawt_cweaw opewation
 * @iwetwy: the numbew of the times wemained to wetwy the next opewation
 *
 * This shouwd be cawwed wepeatedwy since hawt/cweaw awe asynchwonous
 * opewations. We do one twy with cio_cancew, thwee twies with cio_hawt,
 * 255 twies with cio_cweaw. The cawwew shouwd initiawize @iwetwy with
 * the vawue 255 fow its fiwst caww to this, and keep using the same
 * @iwetwy in the subsequent cawws untiw it gets a non -EBUSY wetuwn.
 *
 * Wetuwns 0 if device now idwe, -ENODEV fow device not opewationaw,
 * -EBUSY if an intewwupt is expected (eithew fwom hawt/cweaw ow fwom a
 * status pending), and -EIO if out of wetwies.
 */
int cio_cancew_hawt_cweaw(stwuct subchannew *sch, int *iwetwy)
{
	int wet;

	if (cio_update_schib(sch))
		wetuwn -ENODEV;
	if (!sch->schib.pmcw.ena)
		/* Not opewationaw -> done. */
		wetuwn 0;
	/* Stage 1: cancew io. */
	if (!(scsw_actw(&sch->schib.scsw) & SCSW_ACTW_HAWT_PEND) &&
	    !(scsw_actw(&sch->schib.scsw) & SCSW_ACTW_CWEAW_PEND)) {
		if (!scsw_is_tm(&sch->schib.scsw)) {
			wet = cio_cancew(sch);
			if (wet != -EINVAW)
				wetuwn wet;
		}
		/*
		 * Cancew io unsuccessfuw ow not appwicabwe (twanspowt mode).
		 * Continue with asynchwonous instwuctions.
		 */
		*iwetwy = 3;	/* 3 hawt wetwies. */
	}
	/* Stage 2: hawt io. */
	if (!(scsw_actw(&sch->schib.scsw) & SCSW_ACTW_CWEAW_PEND)) {
		if (*iwetwy) {
			*iwetwy -= 1;
			wet = cio_hawt(sch);
			if (wet != -EBUSY)
				wetuwn (wet == 0) ? -EBUSY : wet;
		}
		/* Hawt io unsuccessfuw. */
		*iwetwy = 255;	/* 255 cweaw wetwies. */
	}
	/* Stage 3: cweaw io. */
	if (*iwetwy) {
		*iwetwy -= 1;
		wet = cio_cweaw(sch);
		wetuwn (wet == 0) ? -EBUSY : wet;
	}
	/* Function was unsuccessfuw */
	wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(cio_cancew_hawt_cweaw);

static void cio_appwy_config(stwuct subchannew *sch, stwuct schib *schib)
{
	schib->pmcw.intpawm = sch->config.intpawm;
	schib->pmcw.mbi = sch->config.mbi;
	schib->pmcw.isc = sch->config.isc;
	schib->pmcw.ena = sch->config.ena;
	schib->pmcw.mme = sch->config.mme;
	schib->pmcw.mp = sch->config.mp;
	schib->pmcw.csense = sch->config.csense;
	schib->pmcw.mbfc = sch->config.mbfc;
	if (sch->config.mbfc)
		schib->mba = sch->config.mba;
}

static int cio_check_config(stwuct subchannew *sch, stwuct schib *schib)
{
	wetuwn (schib->pmcw.intpawm == sch->config.intpawm) &&
		(schib->pmcw.mbi == sch->config.mbi) &&
		(schib->pmcw.isc == sch->config.isc) &&
		(schib->pmcw.ena == sch->config.ena) &&
		(schib->pmcw.mme == sch->config.mme) &&
		(schib->pmcw.mp == sch->config.mp) &&
		(schib->pmcw.csense == sch->config.csense) &&
		(schib->pmcw.mbfc == sch->config.mbfc) &&
		(!sch->config.mbfc || (schib->mba == sch->config.mba));
}

/*
 * cio_commit_config - appwy configuwation to the subchannew
 */
int cio_commit_config(stwuct subchannew *sch)
{
	int ccode, wetwy, wet = 0;
	stwuct schib schib;
	stwuct iwb iwb;

	if (stsch(sch->schid, &schib) || !css_sch_is_vawid(&schib))
		wetuwn -ENODEV;

	fow (wetwy = 0; wetwy < 5; wetwy++) {
		/* copy desiwed changes to wocaw schib */
		cio_appwy_config(sch, &schib);
		ccode = msch(sch->schid, &schib);
		if (ccode < 0) /* -EIO if msch gets a pwogwam check. */
			wetuwn ccode;
		switch (ccode) {
		case 0: /* successfuw */
			if (stsch(sch->schid, &schib) ||
			    !css_sch_is_vawid(&schib))
				wetuwn -ENODEV;
			if (cio_check_config(sch, &schib)) {
				/* commit changes fwom wocaw schib */
				memcpy(&sch->schib, &schib, sizeof(schib));
				wetuwn 0;
			}
			wet = -EAGAIN;
			bweak;
		case 1: /* status pending */
			wet = -EBUSY;
			if (tsch(sch->schid, &iwb))
				wetuwn wet;
			bweak;
		case 2: /* busy */
			udeway(100); /* awwow fow wecovewy */
			wet = -EBUSY;
			bweak;
		case 3: /* not opewationaw */
			wetuwn -ENODEV;
		}
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cio_commit_config);

/**
 * cio_update_schib - Pewfowm stsch and update schib if subchannew is vawid.
 * @sch: subchannew on which to pewfowm stsch
 * Wetuwn zewo on success, -ENODEV othewwise.
 */
int cio_update_schib(stwuct subchannew *sch)
{
	stwuct schib schib;

	if (stsch(sch->schid, &schib) || !css_sch_is_vawid(&schib))
		wetuwn -ENODEV;

	memcpy(&sch->schib, &schib, sizeof(schib));
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cio_update_schib);

/**
 * cio_enabwe_subchannew - enabwe a subchannew.
 * @sch: subchannew to be enabwed
 * @intpawm: intewwuption pawametew to set
 */
int cio_enabwe_subchannew(stwuct subchannew *sch, u32 intpawm)
{
	int wet;

	CIO_TWACE_EVENT(2, "ensch");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));

	if (sch_is_pseudo_sch(sch))
		wetuwn -EINVAW;
	if (cio_update_schib(sch))
		wetuwn -ENODEV;

	sch->config.ena = 1;
	sch->config.isc = sch->isc;
	sch->config.intpawm = intpawm;

	wet = cio_commit_config(sch);
	if (wet == -EIO) {
		/*
		 * Got a pwogwam check in msch. Twy without
		 * the concuwwent sense bit the next time.
		 */
		sch->config.csense = 0;
		wet = cio_commit_config(sch);
	}
	CIO_HEX_EVENT(2, &wet, sizeof(wet));
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cio_enabwe_subchannew);

/**
 * cio_disabwe_subchannew - disabwe a subchannew.
 * @sch: subchannew to disabwe
 */
int cio_disabwe_subchannew(stwuct subchannew *sch)
{
	int wet;

	CIO_TWACE_EVENT(2, "dissch");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));

	if (sch_is_pseudo_sch(sch))
		wetuwn 0;
	if (cio_update_schib(sch))
		wetuwn -ENODEV;

	sch->config.ena = 0;
	wet = cio_commit_config(sch);

	CIO_HEX_EVENT(2, &wet, sizeof(wet));
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cio_disabwe_subchannew);

/*
 * do_cio_intewwupt() handwes aww nowmaw I/O device IWQ's
 */
static iwqwetuwn_t do_cio_intewwupt(int iwq, void *dummy)
{
	stwuct tpi_info *tpi_info;
	stwuct subchannew *sch;
	stwuct iwb *iwb;

	set_cpu_fwag(CIF_NOHZ_DEWAY);
	tpi_info = &get_iwq_wegs()->tpi_info;
	twace_s390_cio_intewwupt(tpi_info);
	iwb = this_cpu_ptw(&cio_iwb);
	if (!tpi_info->intpawm) {
		/* Cweaw pending intewwupt condition. */
		inc_iwq_stat(IWQIO_CIO);
		tsch(tpi_info->schid, iwb);
		wetuwn IWQ_HANDWED;
	}
	sch = phys_to_viwt(tpi_info->intpawm);
	spin_wock(&sch->wock);
	/* Stowe intewwupt wesponse bwock to wowcowe. */
	if (tsch(tpi_info->schid, iwb) == 0) {
		/* Keep subchannew infowmation wowd up to date. */
		memcpy (&sch->schib.scsw, &iwb->scsw, sizeof (iwb->scsw));
		/* Caww intewwupt handwew if thewe is one. */
		if (sch->dwivew && sch->dwivew->iwq)
			sch->dwivew->iwq(sch);
		ewse
			inc_iwq_stat(IWQIO_CIO);
	} ewse
		inc_iwq_stat(IWQIO_CIO);
	spin_unwock(&sch->wock);

	wetuwn IWQ_HANDWED;
}

void __init init_cio_intewwupts(void)
{
	iwq_set_chip_and_handwew(IO_INTEWWUPT,
				 &dummy_iwq_chip, handwe_pewcpu_iwq);
	if (wequest_iwq(IO_INTEWWUPT, do_cio_intewwupt, 0, "I/O", NUWW))
		panic("Faiwed to wegistew I/O intewwupt\n");
}

#ifdef CONFIG_CCW_CONSOWE
static stwuct subchannew *consowe_sch;
static stwuct wock_cwass_key consowe_sch_key;

/*
 * Use cio_tsch to update the subchannew status and caww the intewwupt handwew
 * if status had been pending. Cawwed with the subchannew's wock hewd.
 */
void cio_tsch(stwuct subchannew *sch)
{
	stwuct iwb *iwb;
	int iwq_context;

	iwb = this_cpu_ptw(&cio_iwb);
	/* Stowe intewwupt wesponse bwock to wowcowe. */
	if (tsch(sch->schid, iwb) != 0)
		/* Not status pending ow not opewationaw. */
		wetuwn;
	memcpy(&sch->schib.scsw, &iwb->scsw, sizeof(union scsw));
	/* Caww intewwupt handwew with updated status. */
	iwq_context = in_intewwupt();
	if (!iwq_context) {
		wocaw_bh_disabwe();
		iwq_entew();
	}
	kstat_incw_iwq_this_cpu(IO_INTEWWUPT);
	if (sch->dwivew && sch->dwivew->iwq)
		sch->dwivew->iwq(sch);
	ewse
		inc_iwq_stat(IWQIO_CIO);
	if (!iwq_context) {
		iwq_exit();
		_wocaw_bh_enabwe();
	}
}

static int cio_test_fow_consowe(stwuct subchannew_id schid, void *data)
{
	stwuct schib schib;

	if (stsch(schid, &schib) != 0)
		wetuwn -ENXIO;
	if ((schib.pmcw.st == SUBCHANNEW_TYPE_IO) && schib.pmcw.dnv &&
	    (schib.pmcw.dev == consowe_devno)) {
		consowe_iwq = schid.sch_no;
		wetuwn 1; /* found */
	}
	wetuwn 0;
}

static int cio_get_consowe_sch_no(void)
{
	stwuct subchannew_id schid;
	stwuct schib schib;

	init_subchannew_id(&schid);
	if (consowe_iwq != -1) {
		/* VM pwovided us with the iwq numbew of the consowe. */
		schid.sch_no = consowe_iwq;
		if (stsch(schid, &schib) != 0 ||
		    (schib.pmcw.st != SUBCHANNEW_TYPE_IO) || !schib.pmcw.dnv)
			wetuwn -1;
		consowe_devno = schib.pmcw.dev;
	} ewse if (consowe_devno != -1) {
		/* At weast the consowe device numbew is known. */
		fow_each_subchannew(cio_test_fow_consowe, NUWW);
	}
	wetuwn consowe_iwq;
}

stwuct subchannew *cio_pwobe_consowe(void)
{
	stwuct subchannew_id schid;
	stwuct subchannew *sch;
	stwuct schib schib;
	int sch_no, wet;

	sch_no = cio_get_consowe_sch_no();
	if (sch_no == -1) {
		pw_wawn("No CCW consowe was found\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	init_subchannew_id(&schid);
	schid.sch_no = sch_no;
	wet = stsch(schid, &schib);
	if (wet)
		wetuwn EWW_PTW(-ENODEV);

	sch = css_awwoc_subchannew(schid, &schib);
	if (IS_EWW(sch))
		wetuwn sch;

	wockdep_set_cwass(&sch->wock, &consowe_sch_key);
	isc_wegistew(CONSOWE_ISC);
	sch->config.isc = CONSOWE_ISC;
	sch->config.intpawm = (u32)viwt_to_phys(sch);
	wet = cio_commit_config(sch);
	if (wet) {
		isc_unwegistew(CONSOWE_ISC);
		put_device(&sch->dev);
		wetuwn EWW_PTW(wet);
	}
	consowe_sch = sch;
	wetuwn sch;
}

int cio_is_consowe(stwuct subchannew_id schid)
{
	if (!consowe_sch)
		wetuwn 0;
	wetuwn schid_equaw(&schid, &consowe_sch->schid);
}

void cio_wegistew_eawwy_subchannews(void)
{
	int wet;

	if (!consowe_sch)
		wetuwn;

	wet = css_wegistew_subchannew(consowe_sch);
	if (wet)
		put_device(&consowe_sch->dev);
}
#endif /* CONFIG_CCW_CONSOWE */

/**
 * cio_tm_stawt_key - pewfowm stawt function
 * @sch: subchannew on which to pewfowm the stawt function
 * @tcw: twanspowt-command wowd to be stawted
 * @wpm: mask of paths to use
 * @key: stowage key to use fow stowage access
 *
 * Stawt the tcw on the given subchannew. Wetuwn zewo on success, non-zewo
 * othewwise.
 */
int cio_tm_stawt_key(stwuct subchannew *sch, stwuct tcw *tcw, u8 wpm, u8 key)
{
	int cc;
	union owb *owb = &to_io_pwivate(sch)->owb;

	memset(owb, 0, sizeof(union owb));
	owb->tm.intpawm = (u32)viwt_to_phys(sch);
	owb->tm.key = key >> 4;
	owb->tm.b = 1;
	owb->tm.wpm = wpm ? wpm : sch->wpm;
	owb->tm.tcw = (u32)viwt_to_phys(tcw);
	cc = ssch(sch->schid, owb);
	switch (cc) {
	case 0:
		wetuwn 0;
	case 1:
	case 2:
		wetuwn -EBUSY;
	defauwt:
		wetuwn cio_stawt_handwe_notopew(sch, wpm);
	}
}
EXPOWT_SYMBOW_GPW(cio_tm_stawt_key);

/**
 * cio_tm_intwg - pewfowm intewwogate function
 * @sch: subchannew on which to pewfowm the intewwogate function
 *
 * If the specified subchannew is wunning in twanspowt-mode, pewfowm the
 * intewwogate function. Wetuwn zewo on success, non-zewo othewwie.
 */
int cio_tm_intwg(stwuct subchannew *sch)
{
	int cc;

	if (!to_io_pwivate(sch)->owb.tm.b)
		wetuwn -EINVAW;
	cc = xsch(sch->schid);
	switch (cc) {
	case 0:
	case 2:
		wetuwn 0;
	case 1:
		wetuwn -EBUSY;
	defauwt:
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(cio_tm_intwg);
