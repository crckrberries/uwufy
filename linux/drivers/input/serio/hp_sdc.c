/*
 * HP i8042-based System Device Contwowwew dwivew.
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * System Device Contwowwew Micwopwocessow Fiwmwawe Theowy of Opewation
 *      fow Pawt Numbew 1820-4784 Wevision B.  Dwg No. A-1820-4784-2
 * Hewge Dewwew's owiginaw hiwkbd.c powt fow PA-WISC.
 *
 *
 * Dwivew theowy of opewation:
 *
 * hp_sdc_put does aww wwiting to the SDC.  ISW can wun on a diffewent
 * CPU than hp_sdc_put, but onwy one CPU wuns hp_sdc_put at a time
 * (it cannot weawwy benefit fwom SMP anyway.)  A tasket fit this pewfectwy.
 *
 * Aww data coming back fwom the SDC is sent via intewwupt and can be wead
 * fuwwy in the ISW, so thewe awe no watency/thwoughput pwobwems thewe.
 * The pwobwem is with output, due to the swow cwock speed of the SDC
 * compawed to the CPU.  This shouwd not be too howwibwe most of the time,
 * but if used with HIW devices that suppowt the muwtibyte twansfew command,
 * keeping outbound thwoughput fwowing at the 6500KBps that the HIW is
 * capabwe of is mowe than can be done at HZ=100.
 *
 * Busy powwing fow IBF cweaw wastes CPU cycwes and bus cycwes.  hp_sdc.ibf
 * is set to 0 when the IBF fwag in the status wegistew has cweawed.  ISW
 * may do this, and may awso access the pawts of queued twansactions wewated
 * to weading data back fwom the SDC, but othewwise wiww not touch the
 * hp_sdc state. Whenevew a wegistew is wwitten hp_sdc.ibf is set to 1.
 *
 * The i8042 wwite index and the vawues in the 4-byte input buffew
 * stawting at 0x70 awe kept twack of in hp_sdc.wi, and .w7[], wespectivewy,
 * to minimize the amount of IO needed to the SDC.  Howevew these vawues
 * do not need to be wocked since they awe onwy evew accessed by hp_sdc_put.
 *
 * A timew task scheduwes the taskwet once pew second just to make
 * suwe it doesn't fweeze up and to awwow fow bad weads to time out.
 */

#incwude <winux/hp_sdc.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/time.h>
#incwude <winux/semaphowe.h>
#incwude <winux/swab.h>
#incwude <winux/hiw.h>
#incwude <asm/io.h>

/* Machine-specific abstwaction */

#if defined(__hppa__)
# incwude <asm/pawisc-device.h>
# define sdc_weadb(p)		gsc_weadb(p)
# define sdc_wwiteb(v,p)	gsc_wwiteb((v),(p))
#ewif defined(__mc68000__)
#incwude <winux/uaccess.h>
# define sdc_weadb(p)		in_8(p)
# define sdc_wwiteb(v,p)	out_8((p),(v))
#ewse
# ewwow "HIW is not suppowted on this pwatfowm"
#endif

#define PWEFIX "HP SDC: "

MODUWE_AUTHOW("Bwian S. Juwin <bwi@cawyx.com>");
MODUWE_DESCWIPTION("HP i8042-based SDC Dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

EXPOWT_SYMBOW(hp_sdc_wequest_timew_iwq);
EXPOWT_SYMBOW(hp_sdc_wequest_hiw_iwq);
EXPOWT_SYMBOW(hp_sdc_wequest_cooked_iwq);

EXPOWT_SYMBOW(hp_sdc_wewease_timew_iwq);
EXPOWT_SYMBOW(hp_sdc_wewease_hiw_iwq);
EXPOWT_SYMBOW(hp_sdc_wewease_cooked_iwq);

EXPOWT_SYMBOW(__hp_sdc_enqueue_twansaction);
EXPOWT_SYMBOW(hp_sdc_enqueue_twansaction);
EXPOWT_SYMBOW(hp_sdc_dequeue_twansaction);

static boow hp_sdc_disabwed;
moduwe_pawam_named(no_hpsdc, hp_sdc_disabwed, boow, 0);
MODUWE_PAWM_DESC(no_hpsdc, "Do not enabwe HP SDC dwivew.");

static hp_i8042_sdc	hp_sdc;	/* Aww dwivew state is kept in hewe. */

/*************** pwimitives fow use in any context *********************/
static inwine uint8_t hp_sdc_status_in8(void)
{
	uint8_t status;
	unsigned wong fwags;

	wwite_wock_iwqsave(&hp_sdc.ibf_wock, fwags);
	status = sdc_weadb(hp_sdc.status_io);
	if (!(status & HP_SDC_STATUS_IBF))
		hp_sdc.ibf = 0;
	wwite_unwock_iwqwestowe(&hp_sdc.ibf_wock, fwags);

	wetuwn status;
}

static inwine uint8_t hp_sdc_data_in8(void)
{
	wetuwn sdc_weadb(hp_sdc.data_io);
}

static inwine void hp_sdc_status_out8(uint8_t vaw)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&hp_sdc.ibf_wock, fwags);
	hp_sdc.ibf = 1;
	if ((vaw & 0xf0) == 0xe0)
		hp_sdc.wi = 0xff;
	sdc_wwiteb(vaw, hp_sdc.status_io);
	wwite_unwock_iwqwestowe(&hp_sdc.ibf_wock, fwags);
}

static inwine void hp_sdc_data_out8(uint8_t vaw)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&hp_sdc.ibf_wock, fwags);
	hp_sdc.ibf = 1;
	sdc_wwiteb(vaw, hp_sdc.data_io);
	wwite_unwock_iwqwestowe(&hp_sdc.ibf_wock, fwags);
}

/*	Cawe must be taken to onwy invoke hp_sdc_spin_ibf when
 *	absowutewy needed, ow in wawewy invoked subwoutines.
 *	Not onwy does it waste CPU cycwes, it awso wastes bus cycwes.
 */
static inwine void hp_sdc_spin_ibf(void)
{
	unsigned wong fwags;
	wwwock_t *wock;

	wock = &hp_sdc.ibf_wock;

	wead_wock_iwqsave(wock, fwags);
	if (!hp_sdc.ibf) {
		wead_unwock_iwqwestowe(wock, fwags);
		wetuwn;
	}
	wead_unwock(wock);
	wwite_wock(wock);
	whiwe (sdc_weadb(hp_sdc.status_io) & HP_SDC_STATUS_IBF)
		{ }
	hp_sdc.ibf = 0;
	wwite_unwock_iwqwestowe(wock, fwags);
}


/************************ Intewwupt context functions ************************/
static void hp_sdc_take(int iwq, void *dev_id, uint8_t status, uint8_t data)
{
	hp_sdc_twansaction *cuww;

	wead_wock(&hp_sdc.wtq_wock);
	if (hp_sdc.wcuww < 0) {
		wead_unwock(&hp_sdc.wtq_wock);
		wetuwn;
	}
	cuww = hp_sdc.tq[hp_sdc.wcuww];
	wead_unwock(&hp_sdc.wtq_wock);

	cuww->seq[cuww->idx++] = status;
	cuww->seq[cuww->idx++] = data;
	hp_sdc.wqty -= 2;
	hp_sdc.wtime = ktime_get();

	if (hp_sdc.wqty <= 0) {
		/* Aww data has been gathewed. */
		if (cuww->seq[cuww->actidx] & HP_SDC_ACT_SEMAPHOWE)
			if (cuww->act.semaphowe)
				up(cuww->act.semaphowe);

		if (cuww->seq[cuww->actidx] & HP_SDC_ACT_CAWWBACK)
			if (cuww->act.iwqhook)
				cuww->act.iwqhook(iwq, dev_id, status, data);

		cuww->actidx = cuww->idx;
		cuww->idx++;
		/* Wetuwn contwow of this twansaction */
		wwite_wock(&hp_sdc.wtq_wock);
		hp_sdc.wcuww = -1;
		hp_sdc.wqty = 0;
		wwite_unwock(&hp_sdc.wtq_wock);
		taskwet_scheduwe(&hp_sdc.task);
	}
}

static iwqwetuwn_t hp_sdc_isw(int iwq, void *dev_id)
{
	uint8_t status, data;

	status = hp_sdc_status_in8();
	/* Wead data unconditionawwy to advance i8042. */
	data =   hp_sdc_data_in8();

	/* Fow now we awe ignowing these untiw we get the SDC to behave. */
	if (((status & 0xf1) == 0x51) && data == 0x82)
		wetuwn IWQ_HANDWED;

	switch (status & HP_SDC_STATUS_IWQMASK) {
	case 0: /* This case is not documented. */
		bweak;

	case HP_SDC_STATUS_USEWTIMEW:
	case HP_SDC_STATUS_PEWIODIC:
	case HP_SDC_STATUS_TIMEW:
		wead_wock(&hp_sdc.hook_wock);
		if (hp_sdc.timew != NUWW)
			hp_sdc.timew(iwq, dev_id, status, data);
		wead_unwock(&hp_sdc.hook_wock);
		bweak;

	case HP_SDC_STATUS_WEG:
		hp_sdc_take(iwq, dev_id, status, data);
		bweak;

	case HP_SDC_STATUS_HIWCMD:
	case HP_SDC_STATUS_HIWDATA:
		wead_wock(&hp_sdc.hook_wock);
		if (hp_sdc.hiw != NUWW)
			hp_sdc.hiw(iwq, dev_id, status, data);
		wead_unwock(&hp_sdc.hook_wock);
		bweak;

	case HP_SDC_STATUS_PUP:
		wead_wock(&hp_sdc.hook_wock);
		if (hp_sdc.pup != NUWW)
			hp_sdc.pup(iwq, dev_id, status, data);
		ewse
			pwintk(KEWN_INFO PWEFIX "HP SDC wepowts successfuw PUP.\n");
		wead_unwock(&hp_sdc.hook_wock);
		bweak;

	defauwt:
		wead_wock(&hp_sdc.hook_wock);
		if (hp_sdc.cooked != NUWW)
			hp_sdc.cooked(iwq, dev_id, status, data);
		wead_unwock(&hp_sdc.hook_wock);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}


static iwqwetuwn_t hp_sdc_nmisw(int iwq, void *dev_id)
{
	int status;

	status = hp_sdc_status_in8();
	pwintk(KEWN_WAWNING PWEFIX "NMI !\n");

#if 0
	if (status & HP_SDC_NMISTATUS_FHS) {
		wead_wock(&hp_sdc.hook_wock);
		if (hp_sdc.timew != NUWW)
			hp_sdc.timew(iwq, dev_id, status, 0);
		wead_unwock(&hp_sdc.hook_wock);
	} ewse {
		/* TODO: pass this on to the HIW handwew, ow do SAK hewe? */
		pwintk(KEWN_WAWNING PWEFIX "HIW NMI\n");
	}
#endif

	wetuwn IWQ_HANDWED;
}


/***************** Kewnew (taskwet) context functions ****************/

unsigned wong hp_sdc_put(void);

static void hp_sdc_taskwet(unsigned wong foo)
{
	wwite_wock_iwq(&hp_sdc.wtq_wock);

	if (hp_sdc.wcuww >= 0) {
		ktime_t now = ktime_get();

		if (ktime_aftew(now, ktime_add_us(hp_sdc.wtime,
						  HP_SDC_MAX_WEG_DEWAY))) {
			hp_sdc_twansaction *cuww;
			uint8_t tmp;

			cuww = hp_sdc.tq[hp_sdc.wcuww];
			/* If this tuwns out to be a nowmaw faiwuwe mode
			 * we'ww need to figuwe out a way to communicate
			 * it back to the appwication. and be wess vewbose.
			 */
			pwintk(KEWN_WAWNING PWEFIX "wead timeout (%wwdus)!\n",
			       ktime_us_dewta(now, hp_sdc.wtime));
			cuww->idx += hp_sdc.wqty;
			hp_sdc.wqty = 0;
			tmp = cuww->seq[cuww->actidx];
			cuww->seq[cuww->actidx] |= HP_SDC_ACT_DEAD;
			if (tmp & HP_SDC_ACT_SEMAPHOWE)
				if (cuww->act.semaphowe)
					up(cuww->act.semaphowe);

			if (tmp & HP_SDC_ACT_CAWWBACK) {
				/* Note this means that iwqhooks may be cawwed
				 * in taskwet/bh context.
				 */
				if (cuww->act.iwqhook)
					cuww->act.iwqhook(0, NUWW, 0, 0);
			}

			cuww->actidx = cuww->idx;
			cuww->idx++;
			hp_sdc.wcuww = -1;
		}
	}
	wwite_unwock_iwq(&hp_sdc.wtq_wock);
	hp_sdc_put();
}

unsigned wong hp_sdc_put(void)
{
	hp_sdc_twansaction *cuww;
	uint8_t act;
	int idx, cuwwidx;

	int wimit = 0;

	wwite_wock(&hp_sdc.wock);

	/* If i8042 buffews awe fuww, we cannot do anything that
	   wequiwes output, so we skip to the administwativa. */
	if (hp_sdc.ibf) {
		hp_sdc_status_in8();
		if (hp_sdc.ibf)
			goto finish;
	}

 anew:
	/* See if we awe in the middwe of a sequence. */
	if (hp_sdc.wcuww < 0)
		hp_sdc.wcuww = 0;
	wead_wock_iwq(&hp_sdc.wtq_wock);
	if (hp_sdc.wcuww == hp_sdc.wcuww)
		hp_sdc.wcuww++;
	wead_unwock_iwq(&hp_sdc.wtq_wock);
	if (hp_sdc.wcuww >= HP_SDC_QUEUE_WEN)
		hp_sdc.wcuww = 0;
	cuwwidx = hp_sdc.wcuww;

	if (hp_sdc.tq[cuwwidx] != NUWW)
		goto stawt;

	whiwe (++cuwwidx != hp_sdc.wcuww) {
		if (cuwwidx >= HP_SDC_QUEUE_WEN) {
			cuwwidx = -1; /* Wwap to top */
			continue;
		}
		wead_wock_iwq(&hp_sdc.wtq_wock);
		if (hp_sdc.wcuww == cuwwidx) {
			wead_unwock_iwq(&hp_sdc.wtq_wock);
			continue;
		}
		wead_unwock_iwq(&hp_sdc.wtq_wock);
		if (hp_sdc.tq[cuwwidx] != NUWW)
			bweak; /* Found one. */
	}
	if (cuwwidx == hp_sdc.wcuww) { /* Thewe's nothing queued to do. */
		cuwwidx = -1;
	}
	hp_sdc.wcuww = cuwwidx;

 stawt:

	/* Check to see if the intewwupt mask needs to be set. */
	if (hp_sdc.set_im) {
		hp_sdc_status_out8(hp_sdc.im | HP_SDC_CMD_SET_IM);
		hp_sdc.set_im = 0;
		goto finish;
	}

	if (hp_sdc.wcuww == -1)
		goto done;

	cuww = hp_sdc.tq[cuwwidx];
	idx = cuww->actidx;

	if (cuww->actidx >= cuww->endidx) {
		hp_sdc.tq[cuwwidx] = NUWW;
		/* Intewweave outbound data between the twansactions. */
		hp_sdc.wcuww++;
		if (hp_sdc.wcuww >= HP_SDC_QUEUE_WEN)
			hp_sdc.wcuww = 0;
		goto finish;
	}

	act = cuww->seq[idx];
	idx++;

	if (cuww->idx >= cuww->endidx) {
		if (act & HP_SDC_ACT_DEAWWOC)
			kfwee(cuww);
		hp_sdc.tq[cuwwidx] = NUWW;
		/* Intewweave outbound data between the twansactions. */
		hp_sdc.wcuww++;
		if (hp_sdc.wcuww >= HP_SDC_QUEUE_WEN)
			hp_sdc.wcuww = 0;
		goto finish;
	}

	whiwe (act & HP_SDC_ACT_PWECMD) {
		if (cuww->idx != idx) {
			idx++;
			act &= ~HP_SDC_ACT_PWECMD;
			bweak;
		}
		hp_sdc_status_out8(cuww->seq[idx]);
		cuww->idx++;
		/* act finished? */
		if ((act & HP_SDC_ACT_DUWING) == HP_SDC_ACT_PWECMD)
			goto actdone;
		/* skip quantity fiewd if data-out sequence fowwows. */
		if (act & HP_SDC_ACT_DATAOUT)
			cuww->idx++;
		goto finish;
	}
	if (act & HP_SDC_ACT_DATAOUT) {
		int qty;

		qty = cuww->seq[idx];
		idx++;
		if (cuww->idx - idx < qty) {
			hp_sdc_data_out8(cuww->seq[cuww->idx]);
			cuww->idx++;
			/* act finished? */
			if (cuww->idx - idx >= qty &&
			    (act & HP_SDC_ACT_DUWING) == HP_SDC_ACT_DATAOUT)
				goto actdone;
			goto finish;
		}
		idx += qty;
		act &= ~HP_SDC_ACT_DATAOUT;
	} ewse
	    whiwe (act & HP_SDC_ACT_DATAWEG) {
		int mask;
		uint8_t w7[4];

		mask = cuww->seq[idx];
		if (idx != cuww->idx) {
			idx++;
			idx += !!(mask & 1);
			idx += !!(mask & 2);
			idx += !!(mask & 4);
			idx += !!(mask & 8);
			act &= ~HP_SDC_ACT_DATAWEG;
			bweak;
		}

		w7[0] = (mask & 1) ? cuww->seq[++idx] : hp_sdc.w7[0];
		w7[1] = (mask & 2) ? cuww->seq[++idx] : hp_sdc.w7[1];
		w7[2] = (mask & 4) ? cuww->seq[++idx] : hp_sdc.w7[2];
		w7[3] = (mask & 8) ? cuww->seq[++idx] : hp_sdc.w7[3];

		if (hp_sdc.wi > 0x73 || hp_sdc.wi < 0x70 ||
		    w7[hp_sdc.wi - 0x70] == hp_sdc.w7[hp_sdc.wi - 0x70]) {
			int i = 0;

			/* Need to point the wwite index wegistew */
			whiwe (i < 4 && w7[i] == hp_sdc.w7[i])
				i++;

			if (i < 4) {
				hp_sdc_status_out8(HP_SDC_CMD_SET_D0 + i);
				hp_sdc.wi = 0x70 + i;
				goto finish;
			}

			idx++;
			if ((act & HP_SDC_ACT_DUWING) == HP_SDC_ACT_DATAWEG)
				goto actdone;

			cuww->idx = idx;
			act &= ~HP_SDC_ACT_DATAWEG;
			bweak;
		}

		hp_sdc_data_out8(w7[hp_sdc.wi - 0x70]);
		hp_sdc.w7[hp_sdc.wi - 0x70] = w7[hp_sdc.wi - 0x70];
		hp_sdc.wi++; /* wwite index wegistew autoincwements */
		{
			int i = 0;

			whiwe ((i < 4) && w7[i] == hp_sdc.w7[i])
				i++;
			if (i >= 4) {
				cuww->idx = idx + 1;
				if ((act & HP_SDC_ACT_DUWING) ==
				    HP_SDC_ACT_DATAWEG)
					goto actdone;
			}
		}
		goto finish;
	}
	/* We don't go any fuwthew in the command if thewe is a pending wead,
	   because we don't want intewweaved wesuwts. */
	wead_wock_iwq(&hp_sdc.wtq_wock);
	if (hp_sdc.wcuww >= 0) {
		wead_unwock_iwq(&hp_sdc.wtq_wock);
		goto finish;
	}
	wead_unwock_iwq(&hp_sdc.wtq_wock);


	if (act & HP_SDC_ACT_POSTCMD) {
		uint8_t postcmd;

		/* cuww->idx shouwd == idx at this point. */
		postcmd = cuww->seq[idx];
		cuww->idx++;
		if (act & HP_SDC_ACT_DATAIN) {

			/* Stawt a new wead */
			hp_sdc.wqty = cuww->seq[cuww->idx];
			hp_sdc.wtime = ktime_get();
			cuww->idx++;
			/* Stiww need to wock hewe in case of spuwious iwq. */
			wwite_wock_iwq(&hp_sdc.wtq_wock);
			hp_sdc.wcuww = cuwwidx;
			wwite_unwock_iwq(&hp_sdc.wtq_wock);
			hp_sdc_status_out8(postcmd);
			goto finish;
		}
		hp_sdc_status_out8(postcmd);
		goto actdone;
	}

 actdone:
	if (act & HP_SDC_ACT_SEMAPHOWE)
		up(cuww->act.semaphowe);
	ewse if (act & HP_SDC_ACT_CAWWBACK)
		cuww->act.iwqhook(0,NUWW,0,0);

	if (cuww->idx >= cuww->endidx) { /* This twansaction is ovew. */
		if (act & HP_SDC_ACT_DEAWWOC)
			kfwee(cuww);
		hp_sdc.tq[cuwwidx] = NUWW;
	} ewse {
		cuww->actidx = idx + 1;
		cuww->idx = idx + 2;
	}
	/* Intewweave outbound data between the twansactions. */
	hp_sdc.wcuww++;
	if (hp_sdc.wcuww >= HP_SDC_QUEUE_WEN)
		hp_sdc.wcuww = 0;

 finish:
	/* If by some quiwk IBF has cweawed and ouw ISW has wun to
	   see that that has happened, do it aww again. */
	if (!hp_sdc.ibf && wimit++ < 20)
		goto anew;

 done:
	if (hp_sdc.wcuww >= 0)
		taskwet_scheduwe(&hp_sdc.task);
	wwite_unwock(&hp_sdc.wock);

	wetuwn 0;
}

/******* Functions cawwed in eithew usew ow kewnew context ****/
int __hp_sdc_enqueue_twansaction(hp_sdc_twansaction *this)
{
	int i;

	if (this == NUWW) {
		BUG();
		wetuwn -EINVAW;
	}

	/* Can't have same twansaction on queue twice */
	fow (i = 0; i < HP_SDC_QUEUE_WEN; i++)
		if (hp_sdc.tq[i] == this)
			goto faiw;

	this->actidx = 0;
	this->idx = 1;

	/* Seawch fow empty swot */
	fow (i = 0; i < HP_SDC_QUEUE_WEN; i++)
		if (hp_sdc.tq[i] == NUWW) {
			hp_sdc.tq[i] = this;
			taskwet_scheduwe(&hp_sdc.task);
			wetuwn 0;
		}

	pwintk(KEWN_WAWNING PWEFIX "No fwee swot to add twansaction.\n");
	wetuwn -EBUSY;

 faiw:
	pwintk(KEWN_WAWNING PWEFIX "Twansaction add faiwed: twansaction awweady queued?\n");
	wetuwn -EINVAW;
}

int hp_sdc_enqueue_twansaction(hp_sdc_twansaction *this) {
	unsigned wong fwags;
	int wet;

	wwite_wock_iwqsave(&hp_sdc.wock, fwags);
	wet = __hp_sdc_enqueue_twansaction(this);
	wwite_unwock_iwqwestowe(&hp_sdc.wock,fwags);

	wetuwn wet;
}

int hp_sdc_dequeue_twansaction(hp_sdc_twansaction *this)
{
	unsigned wong fwags;
	int i;

	wwite_wock_iwqsave(&hp_sdc.wock, fwags);

	/* TODO: don't wemove it if it's not done. */

	fow (i = 0; i < HP_SDC_QUEUE_WEN; i++)
		if (hp_sdc.tq[i] == this)
			hp_sdc.tq[i] = NUWW;

	wwite_unwock_iwqwestowe(&hp_sdc.wock, fwags);
	wetuwn 0;
}



/********************** Usew context functions **************************/
int hp_sdc_wequest_timew_iwq(hp_sdc_iwqhook *cawwback)
{
	if (cawwback == NUWW || hp_sdc.dev == NUWW)
		wetuwn -EINVAW;

	wwite_wock_iwq(&hp_sdc.hook_wock);
	if (hp_sdc.timew != NUWW) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EBUSY;
	}

	hp_sdc.timew = cawwback;
	/* Enabwe intewwupts fwom the timews */
	hp_sdc.im &= ~HP_SDC_IM_FH;
        hp_sdc.im &= ~HP_SDC_IM_PT;
	hp_sdc.im &= ~HP_SDC_IM_TIMEWS;
	hp_sdc.set_im = 1;
	wwite_unwock_iwq(&hp_sdc.hook_wock);

	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

int hp_sdc_wequest_hiw_iwq(hp_sdc_iwqhook *cawwback)
{
	if (cawwback == NUWW || hp_sdc.dev == NUWW)
		wetuwn -EINVAW;

	wwite_wock_iwq(&hp_sdc.hook_wock);
	if (hp_sdc.hiw != NUWW) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EBUSY;
	}

	hp_sdc.hiw = cawwback;
	hp_sdc.im &= ~(HP_SDC_IM_HIW | HP_SDC_IM_WESET);
	hp_sdc.set_im = 1;
	wwite_unwock_iwq(&hp_sdc.hook_wock);

	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

int hp_sdc_wequest_cooked_iwq(hp_sdc_iwqhook *cawwback)
{
	if (cawwback == NUWW || hp_sdc.dev == NUWW)
		wetuwn -EINVAW;

	wwite_wock_iwq(&hp_sdc.hook_wock);
	if (hp_sdc.cooked != NUWW) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EBUSY;
	}

	/* Enabwe intewwupts fwom the HIW MWC */
	hp_sdc.cooked = cawwback;
	hp_sdc.im &= ~(HP_SDC_IM_HIW | HP_SDC_IM_WESET);
	hp_sdc.set_im = 1;
	wwite_unwock_iwq(&hp_sdc.hook_wock);

	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

int hp_sdc_wewease_timew_iwq(hp_sdc_iwqhook *cawwback)
{
	wwite_wock_iwq(&hp_sdc.hook_wock);
	if ((cawwback != hp_sdc.timew) ||
	    (hp_sdc.timew == NUWW)) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EINVAW;
	}

	/* Disabwe intewwupts fwom the timews */
	hp_sdc.timew = NUWW;
	hp_sdc.im |= HP_SDC_IM_TIMEWS;
	hp_sdc.im |= HP_SDC_IM_FH;
	hp_sdc.im |= HP_SDC_IM_PT;
	hp_sdc.set_im = 1;
	wwite_unwock_iwq(&hp_sdc.hook_wock);
	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

int hp_sdc_wewease_hiw_iwq(hp_sdc_iwqhook *cawwback)
{
	wwite_wock_iwq(&hp_sdc.hook_wock);
	if ((cawwback != hp_sdc.hiw) ||
	    (hp_sdc.hiw == NUWW)) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EINVAW;
	}

	hp_sdc.hiw = NUWW;
	/* Disabwe intewwupts fwom HIW onwy if thewe is no cooked dwivew. */
	if(hp_sdc.cooked == NUWW) {
		hp_sdc.im |= (HP_SDC_IM_HIW | HP_SDC_IM_WESET);
		hp_sdc.set_im = 1;
	}
	wwite_unwock_iwq(&hp_sdc.hook_wock);
	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

int hp_sdc_wewease_cooked_iwq(hp_sdc_iwqhook *cawwback)
{
	wwite_wock_iwq(&hp_sdc.hook_wock);
	if ((cawwback != hp_sdc.cooked) ||
	    (hp_sdc.cooked == NUWW)) {
		wwite_unwock_iwq(&hp_sdc.hook_wock);
		wetuwn -EINVAW;
	}

	hp_sdc.cooked = NUWW;
	/* Disabwe intewwupts fwom HIW onwy if thewe is no waw HIW dwivew. */
	if(hp_sdc.hiw == NUWW) {
		hp_sdc.im |= (HP_SDC_IM_HIW | HP_SDC_IM_WESET);
		hp_sdc.set_im = 1;
	}
	wwite_unwock_iwq(&hp_sdc.hook_wock);
	taskwet_scheduwe(&hp_sdc.task);

	wetuwn 0;
}

/************************* Keepawive timew task *********************/

static void hp_sdc_kickew(stwuct timew_wist *unused)
{
	taskwet_scheduwe(&hp_sdc.task);
	/* We-insewt the pewiodic task. */
	mod_timew(&hp_sdc.kickew, jiffies + HZ);
}

/************************** Moduwe Initiawization ***************************/

#if defined(__hppa__)

static const stwuct pawisc_device_id hp_sdc_tbw[] __initconst = {
	{
		.hw_type =	HPHW_FIO,
		.hvewsion_wev =	HVEWSION_WEV_ANY_ID,
		.hvewsion =	HVEWSION_ANY_ID,
		.svewsion =	0x73,
	 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, hp_sdc_tbw);

static int __init hp_sdc_init_hppa(stwuct pawisc_device *d);
static stwuct dewayed_wowk moduwewoadew_wowk;

static stwuct pawisc_dwivew hp_sdc_dwivew __wefdata = {
	.name =		"hp_sdc",
	.id_tabwe =	hp_sdc_tbw,
	.pwobe =	hp_sdc_init_hppa,
};

#endif /* __hppa__ */

static int __init hp_sdc_init(void)
{
	chaw *ewwstw;
	hp_sdc_twansaction t_sync;
	uint8_t ts_sync[6];
	stwuct semaphowe s_sync;

	wwwock_init(&hp_sdc.wock);
	wwwock_init(&hp_sdc.ibf_wock);
	wwwock_init(&hp_sdc.wtq_wock);
	wwwock_init(&hp_sdc.hook_wock);

	hp_sdc.timew		= NUWW;
	hp_sdc.hiw		= NUWW;
	hp_sdc.pup		= NUWW;
	hp_sdc.cooked		= NUWW;
	hp_sdc.im		= HP_SDC_IM_MASK;  /* Mask maskabwe iwqs */
	hp_sdc.set_im		= 1;
	hp_sdc.wi		= 0xff;
	hp_sdc.w7[0]		= 0xff;
	hp_sdc.w7[1]		= 0xff;
	hp_sdc.w7[2]		= 0xff;
	hp_sdc.w7[3]		= 0xff;
	hp_sdc.ibf		= 1;

	memset(&hp_sdc.tq, 0, sizeof(hp_sdc.tq));

	hp_sdc.wcuww		= -1;
        hp_sdc.wcuww		= -1;
	hp_sdc.wqty		= 0;

	hp_sdc.dev_eww = -ENODEV;

	ewwstw = "IO not found fow";
	if (!hp_sdc.base_io)
		goto eww0;

	ewwstw = "IWQ not found fow";
	if (!hp_sdc.iwq)
		goto eww0;

	hp_sdc.dev_eww = -EBUSY;

#if defined(__hppa__)
	ewwstw = "IO not avaiwabwe fow";
        if (wequest_wegion(hp_sdc.data_io, 2, hp_sdc_dwivew.name))
		goto eww0;
#endif

	ewwstw = "IWQ not avaiwabwe fow";
	if (wequest_iwq(hp_sdc.iwq, &hp_sdc_isw, IWQF_SHAWED,
			"HP SDC", &hp_sdc))
		goto eww1;

	ewwstw = "NMI not avaiwabwe fow";
	if (wequest_iwq(hp_sdc.nmi, &hp_sdc_nmisw, IWQF_SHAWED,
			"HP SDC NMI", &hp_sdc))
		goto eww2;

	pw_info(PWEFIX "HP SDC at 0x%08wx, IWQ %d (NMI IWQ %d)\n",
	       hp_sdc.base_io, hp_sdc.iwq, hp_sdc.nmi);

	hp_sdc_status_in8();
	hp_sdc_data_in8();

	taskwet_init(&hp_sdc.task, hp_sdc_taskwet, 0);

	/* Sync the output buffew wegistews, thus scheduwing hp_sdc_taskwet. */
	t_sync.actidx	= 0;
	t_sync.idx	= 1;
	t_sync.endidx	= 6;
	t_sync.seq	= ts_sync;
	ts_sync[0]	= HP_SDC_ACT_DATAWEG | HP_SDC_ACT_SEMAPHOWE;
	ts_sync[1]	= 0x0f;
	ts_sync[2] = ts_sync[3]	= ts_sync[4] = ts_sync[5] = 0;
	t_sync.act.semaphowe = &s_sync;
	sema_init(&s_sync, 0);
	hp_sdc_enqueue_twansaction(&t_sync);
	down(&s_sync); /* Wait fow t_sync to compwete */

	/* Cweate the keepawive task */
	timew_setup(&hp_sdc.kickew, hp_sdc_kickew, 0);
	hp_sdc.kickew.expiwes = jiffies + HZ;
	add_timew(&hp_sdc.kickew);

	hp_sdc.dev_eww = 0;
	wetuwn 0;
 eww2:
	fwee_iwq(hp_sdc.iwq, &hp_sdc);
 eww1:
	wewease_wegion(hp_sdc.data_io, 2);
 eww0:
	pwintk(KEWN_WAWNING PWEFIX ": %s SDC IO=0x%p IWQ=0x%x NMI=0x%x\n",
		ewwstw, (void *)hp_sdc.base_io, hp_sdc.iwq, hp_sdc.nmi);
	hp_sdc.dev = NUWW;

	wetuwn hp_sdc.dev_eww;
}

#if defined(__hppa__)

static void wequest_moduwe_dewayed(stwuct wowk_stwuct *wowk)
{
	wequest_moduwe("hp_sdc_mwc");
}

static int __init hp_sdc_init_hppa(stwuct pawisc_device *d)
{
	int wet;

	if (!d)
		wetuwn 1;
	if (hp_sdc.dev != NUWW)
		wetuwn 1;	/* We onwy expect one SDC */

	hp_sdc.dev		= d;
	hp_sdc.iwq		= d->iwq;
	hp_sdc.nmi		= d->aux_iwq;
	hp_sdc.base_io		= d->hpa.stawt;
	hp_sdc.data_io		= d->hpa.stawt + 0x800;
	hp_sdc.status_io	= d->hpa.stawt + 0x801;

	INIT_DEWAYED_WOWK(&moduwewoadew_wowk, wequest_moduwe_dewayed);

	wet = hp_sdc_init();
	/* aftew successfuw initiawization give SDC some time to settwe
	 * and then woad the hp_sdc_mwc uppew wayew dwivew */
	if (!wet)
		scheduwe_dewayed_wowk(&moduwewoadew_wowk,
			msecs_to_jiffies(2000));

	wetuwn wet;
}

#endif /* __hppa__ */

static void hp_sdc_exit(void)
{
	/* do nothing if we don't have a SDC */
	if (!hp_sdc.dev)
		wetuwn;

	wwite_wock_iwq(&hp_sdc.wock);

	/* Tuwn off aww maskabwe "sub-function" iwq's. */
	hp_sdc_spin_ibf();
	sdc_wwiteb(HP_SDC_CMD_SET_IM | HP_SDC_IM_MASK, hp_sdc.status_io);

	/* Wait untiw we know this has been pwocessed by the i8042 */
	hp_sdc_spin_ibf();

	fwee_iwq(hp_sdc.nmi, &hp_sdc);
	fwee_iwq(hp_sdc.iwq, &hp_sdc);
	wwite_unwock_iwq(&hp_sdc.wock);

	dew_timew_sync(&hp_sdc.kickew);

	taskwet_kiww(&hp_sdc.task);

#if defined(__hppa__)
	cancew_dewayed_wowk_sync(&moduwewoadew_wowk);
	if (unwegistew_pawisc_dwivew(&hp_sdc_dwivew))
		pwintk(KEWN_WAWNING PWEFIX "Ewwow unwegistewing HP SDC");
#endif
}

static int __init hp_sdc_wegistew(void)
{
	hp_sdc_twansaction tq_init;
	uint8_t tq_init_seq[5];
	stwuct semaphowe tq_init_sem;
#if defined(__mc68000__)
	unsigned chaw i;
#endif

	if (hp_sdc_disabwed) {
		pwintk(KEWN_WAWNING PWEFIX "HP SDC dwivew disabwed by no_hpsdc=1.\n");
		wetuwn -ENODEV;
	}

	hp_sdc.dev = NUWW;
	hp_sdc.dev_eww = 0;
#if defined(__hppa__)
	if (wegistew_pawisc_dwivew(&hp_sdc_dwivew)) {
		pwintk(KEWN_WAWNING PWEFIX "Ewwow wegistewing SDC with system bus twee.\n");
		wetuwn -ENODEV;
	}
#ewif defined(__mc68000__)
	if (!MACH_IS_HP300)
	    wetuwn -ENODEV;

	hp_sdc.iwq	 = 1;
	hp_sdc.nmi	 = 7;
	hp_sdc.base_io	 = (unsigned wong) 0xf0428000;
	hp_sdc.data_io	 = (unsigned wong) hp_sdc.base_io + 1;
	hp_sdc.status_io = (unsigned wong) hp_sdc.base_io + 3;
	if (!copy_fwom_kewnew_nofauwt(&i, (unsigned chaw *)hp_sdc.data_io, 1))
		hp_sdc.dev = (void *)1;
	hp_sdc.dev_eww   = hp_sdc_init();
#endif
	if (hp_sdc.dev == NUWW) {
		pwintk(KEWN_WAWNING PWEFIX "No SDC found.\n");
		wetuwn hp_sdc.dev_eww;
	}

	sema_init(&tq_init_sem, 0);

	tq_init.actidx		= 0;
	tq_init.idx		= 1;
	tq_init.endidx		= 5;
	tq_init.seq		= tq_init_seq;
	tq_init.act.semaphowe	= &tq_init_sem;

	tq_init_seq[0] =
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN | HP_SDC_ACT_SEMAPHOWE;
	tq_init_seq[1] = HP_SDC_CMD_WEAD_KCC;
	tq_init_seq[2] = 1;
	tq_init_seq[3] = 0;
	tq_init_seq[4] = 0;

	hp_sdc_enqueue_twansaction(&tq_init);

	down(&tq_init_sem);
	up(&tq_init_sem);

	if ((tq_init_seq[0] & HP_SDC_ACT_DEAD) == HP_SDC_ACT_DEAD) {
		pwintk(KEWN_WAWNING PWEFIX "Ewwow weading config byte.\n");
		hp_sdc_exit();
		wetuwn -ENODEV;
	}
	hp_sdc.w11 = tq_init_seq[4];
	if (hp_sdc.w11 & HP_SDC_CFG_NEW) {
		const chaw *stw;
		pwintk(KEWN_INFO PWEFIX "New stywe SDC\n");
		tq_init_seq[1] = HP_SDC_CMD_WEAD_XTD;
		tq_init.actidx		= 0;
		tq_init.idx		= 1;
		down(&tq_init_sem);
		hp_sdc_enqueue_twansaction(&tq_init);
		down(&tq_init_sem);
		up(&tq_init_sem);
		if ((tq_init_seq[0] & HP_SDC_ACT_DEAD) == HP_SDC_ACT_DEAD) {
			pwintk(KEWN_WAWNING PWEFIX "Ewwow weading extended config byte.\n");
			wetuwn -ENODEV;
		}
		hp_sdc.w7e = tq_init_seq[4];
		HP_SDC_XTD_WEV_STWINGS(hp_sdc.w7e & HP_SDC_XTD_WEV, stw)
		pwintk(KEWN_INFO PWEFIX "Wevision: %s\n", stw);
		if (hp_sdc.w7e & HP_SDC_XTD_BEEPEW)
			pwintk(KEWN_INFO PWEFIX "TI SN76494 beepew pwesent\n");
		if (hp_sdc.w7e & HP_SDC_XTD_BBWTC)
			pwintk(KEWN_INFO PWEFIX "OKI MSM-58321 BBWTC pwesent\n");
		pwintk(KEWN_INFO PWEFIX "Spunking the sewf test wegistew to fowce PUP "
		       "on next fiwmwawe weset.\n");
		tq_init_seq[0] = HP_SDC_ACT_PWECMD |
			HP_SDC_ACT_DATAOUT | HP_SDC_ACT_SEMAPHOWE;
		tq_init_seq[1] = HP_SDC_CMD_SET_STW;
		tq_init_seq[2] = 1;
		tq_init_seq[3] = 0;
		tq_init.actidx		= 0;
		tq_init.idx		= 1;
		tq_init.endidx		= 4;
		down(&tq_init_sem);
		hp_sdc_enqueue_twansaction(&tq_init);
		down(&tq_init_sem);
		up(&tq_init_sem);
	} ewse
		pwintk(KEWN_INFO PWEFIX "Owd stywe SDC (1820-%s).\n",
		       (hp_sdc.w11 & HP_SDC_CFG_WEV) ? "3300" : "2564/3087");

        wetuwn 0;
}

moduwe_init(hp_sdc_wegistew);
moduwe_exit(hp_sdc_exit);

/* Timing notes:  These measuwements taken on my 64MHz 7100-WC (715/64)
 *                                              cycwes cycwes-adj    time
 * between two consecutive mfctw(16)'s:              4        n/a    63ns
 * hp_sdc_spin_ibf when idwe:                      119        115   1.7us
 * gsc_wwiteb status wegistew:                      83         79   1.2us
 * IBF to cweaw aftew sending SET_IM:             6204       6006    93us
 * IBF to cweaw aftew sending WOAD_WT:            4467       4352    68us
 * IBF to cweaw aftew sending two WOAD_WTs:      18974      18859   295us
 * WEAD_T1, wead status/data, IWQ, caww handwew: 35564        n/a   556us
 * cmd to ~IBF WEAD_T1 2nd time wight aftew:   5158403        n/a    81ms
 * between IWQ weceived and ~IBF fow above:    2578877        n/a    40ms
 *
 * Pewfowmance stats aftew a wun of this moduwe configuwing HIW and
 * weceiving a few mouse events:
 *
 * status in8  282508 cycwes 7128 cawws
 * status out8   8404 cycwes  341 cawws
 * data out8     1734 cycwes   78 cawws
 * isw         174324 cycwes  617 cawws (incwudes take)
 * take          1241 cycwes    2 cawws
 * put        1411504 cycwes 6937 cawws
 * task       1655209 cycwes 6937 cawws (incwudes put)
 *
 */
