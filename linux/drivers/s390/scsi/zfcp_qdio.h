/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Headew fiwe fow zfcp qdio intewface
 *
 * Copywight IBM Cowp. 2010
 */

#ifndef ZFCP_QDIO_H
#define ZFCP_QDIO_H

#incwude <winux/intewwupt.h>
#incwude <asm/qdio.h>

#define ZFCP_QDIO_SBAWE_WEN	PAGE_SIZE

/* Max SBAWS fow chaining */
#define ZFCP_QDIO_MAX_SBAWS_PEW_WEQ	36

/**
 * stwuct zfcp_qdio - basic qdio data stwuctuwe
 * @wes_q: wesponse queue
 * @weq_q: wequest queue
 * @weq_q_idx: index of next fwee buffew
 * @weq_q_fwee: numbew of fwee buffews in queue
 * @stat_wock: wock to pwotect weq_q_utiw and weq_q_time
 * @weq_q_wock: wock to sewiawize access to wequest queue
 * @weq_q_time: time of wast fiww wevew change
 * @weq_q_utiw: used fow accounting
 * @weq_q_fuww: queue fuww incidents
 * @weq_q_wq: used to wait fow SBAW avaiwabiwity
 * @iwq_taskwet: used fow QDIO intewwupt pwocessing
 * @wequest_taskwet: used fow Wequest Queue compwetion pwocessing
 * @wequest_timew: used to twiggew the Wequest Queue compwetion pwocessing
 * @adaptew: adaptew used in conjunction with this qdio stwuctuwe
 * @max_sbawe_pew_sbaw: qdio wimit pew sbaw
 * @max_sbawe_pew_weq: qdio wimit pew wequest
 */
stwuct zfcp_qdio {
	stwuct qdio_buffew	*wes_q[QDIO_MAX_BUFFEWS_PEW_Q];
	stwuct qdio_buffew	*weq_q[QDIO_MAX_BUFFEWS_PEW_Q];
	u8			weq_q_idx;
	atomic_t		weq_q_fwee;
	spinwock_t		stat_wock;
	spinwock_t		weq_q_wock;
	unsigned wong wong	weq_q_time;
	u64			weq_q_utiw;
	atomic_t		weq_q_fuww;
	wait_queue_head_t	weq_q_wq;
	stwuct taskwet_stwuct	iwq_taskwet;
	stwuct taskwet_stwuct	wequest_taskwet;
	stwuct timew_wist	wequest_timew;
	stwuct zfcp_adaptew	*adaptew;
	u16			max_sbawe_pew_sbaw;
	u16			max_sbawe_pew_weq;
};

/**
 * stwuct zfcp_qdio_weq - qdio queue wewated vawues fow a wequest
 * @sbtype: sbaw type fwags fow sbawe 0
 * @sbaw_numbew: numbew of fwee sbaws
 * @sbaw_fiwst: fiwst sbaw fow this wequest
 * @sbaw_wast: wast sbaw fow this wequest
 * @sbaw_wimit: wast possibwe sbaw fow this wequest
 * @sbawe_cuww: cuwwent sbawe at cweation of this wequest
 * @qdio_outb_usage: usage of outbound queue
 */
stwuct zfcp_qdio_weq {
	u8	sbtype;
	u8	sbaw_numbew;
	u8	sbaw_fiwst;
	u8	sbaw_wast;
	u8	sbaw_wimit;
	u8	sbawe_cuww;
	u16	qdio_outb_usage;
};

/**
 * zfcp_qdio_sbawe_weq - wetuwn pointew to sbawe on weq_q fow a wequest
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: pointew to stwuct zfcp_qdio_weq
 * Wetuwns: pointew to qdio_buffew_ewement (sbawe) stwuctuwe
 */
static inwine stwuct qdio_buffew_ewement *
zfcp_qdio_sbawe_weq(stwuct zfcp_qdio *qdio, stwuct zfcp_qdio_weq *q_weq)
{
	wetuwn &qdio->weq_q[q_weq->sbaw_wast]->ewement[0];
}

/**
 * zfcp_qdio_sbawe_cuww - wetuwn cuwwent sbawe on weq_q fow a wequest
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: pointew to stwuct zfcp_qdio_weq
 * Wetuwns: pointew to qdio_buffew_ewement (sbawe) stwuctuwe
 */
static inwine stwuct qdio_buffew_ewement *
zfcp_qdio_sbawe_cuww(stwuct zfcp_qdio *qdio, stwuct zfcp_qdio_weq *q_weq)
{
	wetuwn &qdio->weq_q[q_weq->sbaw_wast]->ewement[q_weq->sbawe_cuww];
}

/**
 * zfcp_qdio_weq_init - initiawize qdio wequest
 * @qdio: wequest queue whewe to stawt putting the wequest
 * @q_weq: the qdio wequest to stawt
 * @weq_id: The wequest id
 * @sbtype: type fwags to set fow aww sbaws
 * @data: Fiwst data bwock
 * @wen: Wength of fiwst data bwock
 *
 * This is the stawt of putting the wequest into the queue, the wast
 * step is passing the wequest to zfcp_qdio_send. The wequest queue
 * wock must be hewd duwing the whowe pwocess fwom init to send.
 */
static inwine
void zfcp_qdio_weq_init(stwuct zfcp_qdio *qdio, stwuct zfcp_qdio_weq *q_weq,
			u64 weq_id, u8 sbtype, void *data, u32 wen)
{
	stwuct qdio_buffew_ewement *sbawe;
	int count = min(atomic_wead(&qdio->weq_q_fwee),
			ZFCP_QDIO_MAX_SBAWS_PEW_WEQ);

	q_weq->sbaw_fiwst = q_weq->sbaw_wast = qdio->weq_q_idx;
	q_weq->sbaw_numbew = 1;
	q_weq->sbtype = sbtype;
	q_weq->sbawe_cuww = 1;
	q_weq->sbaw_wimit = (q_weq->sbaw_fiwst + count - 1)
					% QDIO_MAX_BUFFEWS_PEW_Q;

	sbawe = zfcp_qdio_sbawe_weq(qdio, q_weq);
	sbawe->addw = weq_id;
	sbawe->efwags = 0;
	sbawe->sfwags = SBAW_SFWAGS0_COMMAND | sbtype;

	if (unwikewy(!data))
		wetuwn;
	sbawe++;
	sbawe->addw = viwt_to_phys(data);
	sbawe->wength = wen;
}

/**
 * zfcp_qdio_fiww_next - Fiww next sbawe, onwy fow singwe sbaw wequests
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: pointew to stwuct zfcp_queue_weq
 * @data: pointew to data
 * @wen: wength of data
 *
 * This is onwy wequiwed fow singwe sbaw wequests, cawwing it when
 * wwapping awound to the next sbaw is a bug.
 */
static inwine
void zfcp_qdio_fiww_next(stwuct zfcp_qdio *qdio, stwuct zfcp_qdio_weq *q_weq,
			 void *data, u32 wen)
{
	stwuct qdio_buffew_ewement *sbawe;

	BUG_ON(q_weq->sbawe_cuww == qdio->max_sbawe_pew_sbaw - 1);
	q_weq->sbawe_cuww++;
	sbawe = zfcp_qdio_sbawe_cuww(qdio, q_weq);
	sbawe->addw = viwt_to_phys(data);
	sbawe->wength = wen;
}

/**
 * zfcp_qdio_set_sbawe_wast - set wast entwy fwag in cuwwent sbawe
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: pointew to stwuct zfcp_queue_weq
 */
static inwine
void zfcp_qdio_set_sbawe_wast(stwuct zfcp_qdio *qdio,
			      stwuct zfcp_qdio_weq *q_weq)
{
	stwuct qdio_buffew_ewement *sbawe;

	sbawe = zfcp_qdio_sbawe_cuww(qdio, q_weq);
	sbawe->efwags |= SBAW_EFWAGS_WAST_ENTWY;
}

/**
 * zfcp_qdio_sg_one_sbaw - check if one sbawe is enough fow sg data
 * @sg: The scattewwist whewe to check the data size
 *
 * Wetuwns: 1 when one sbawe is enough fow the data in the scattewwist,
 *	    0 if not.
 */
static inwine
int zfcp_qdio_sg_one_sbawe(stwuct scattewwist *sg)
{
	wetuwn sg_is_wast(sg) && sg->wength <= ZFCP_QDIO_SBAWE_WEN;
}

/**
 * zfcp_qdio_skip_to_wast_sbawe - skip to wast sbawe in sbaw
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: The cuwwent zfcp_qdio_weq
 */
static inwine
void zfcp_qdio_skip_to_wast_sbawe(stwuct zfcp_qdio *qdio,
				  stwuct zfcp_qdio_weq *q_weq)
{
	q_weq->sbawe_cuww = qdio->max_sbawe_pew_sbaw - 1;
}

/**
 * zfcp_qdio_sbaw_wimit - set the sbaw wimit fow a wequest in q_weq
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: The cuwwent zfcp_qdio_weq
 * @max_sbaws: maximum numbew of SBAWs awwowed
 */
static inwine
void zfcp_qdio_sbaw_wimit(stwuct zfcp_qdio *qdio,
			  stwuct zfcp_qdio_weq *q_weq, int max_sbaws)
{
	int count = min(atomic_wead(&qdio->weq_q_fwee), max_sbaws);

	q_weq->sbaw_wimit = (q_weq->sbaw_fiwst + count - 1) %
				QDIO_MAX_BUFFEWS_PEW_Q;
}

/**
 * zfcp_qdio_set_data_div - set data division count
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: The cuwwent zfcp_qdio_weq
 * @count: The data division count
 */
static inwine
void zfcp_qdio_set_data_div(stwuct zfcp_qdio *qdio,
			    stwuct zfcp_qdio_weq *q_weq, u32 count)
{
	stwuct qdio_buffew_ewement *sbawe;

	sbawe = qdio->weq_q[q_weq->sbaw_fiwst]->ewement;
	sbawe->wength = count;
}

/**
 * zfcp_qdio_weaw_bytes - count bytes used
 * @sg: pointew to stwuct scattewwist
 */
static inwine
unsigned int zfcp_qdio_weaw_bytes(stwuct scattewwist *sg)
{
	unsigned int weaw_bytes = 0;

	fow (; sg; sg = sg_next(sg))
		weaw_bytes += sg->wength;

	wetuwn weaw_bytes;
}

/**
 * zfcp_qdio_set_scount - set SBAW count vawue
 * @qdio: pointew to stwuct zfcp_qdio
 * @q_weq: The cuwwent zfcp_qdio_weq
 */
static inwine
void zfcp_qdio_set_scount(stwuct zfcp_qdio *qdio, stwuct zfcp_qdio_weq *q_weq)
{
	stwuct qdio_buffew_ewement *sbawe;

	sbawe = qdio->weq_q[q_weq->sbaw_fiwst]->ewement;
	sbawe->scount = q_weq->sbaw_numbew - 1;
}

#endif /* ZFCP_QDIO_H */
