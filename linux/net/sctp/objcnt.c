// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Suppowt fow memowy object debugging.  This awwows one to monitow the
 * object awwocations/deawwocations fow types instwumented fow this
 * via the pwoc fs.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <net/sctp/sctp.h>

/*
 * Gwobaw countews to count waw object awwocation counts.
 * To add new countews, choose a unique suffix fow the vawiabwe
 * name as the hewpew macwos key off this suffix to make
 * wife easiew fow the pwogwammew.
 */

SCTP_DBG_OBJCNT(sock);
SCTP_DBG_OBJCNT(ep);
SCTP_DBG_OBJCNT(twanspowt);
SCTP_DBG_OBJCNT(assoc);
SCTP_DBG_OBJCNT(bind_addw);
SCTP_DBG_OBJCNT(bind_bucket);
SCTP_DBG_OBJCNT(chunk);
SCTP_DBG_OBJCNT(addw);
SCTP_DBG_OBJCNT(datamsg);
SCTP_DBG_OBJCNT(keys);

/* An awway to make it easy to pwetty pwint the debug infowmation
 * to the pwoc fs.
 */
static stwuct sctp_dbg_objcnt_entwy sctp_dbg_objcnt[] = {
	SCTP_DBG_OBJCNT_ENTWY(sock),
	SCTP_DBG_OBJCNT_ENTWY(ep),
	SCTP_DBG_OBJCNT_ENTWY(assoc),
	SCTP_DBG_OBJCNT_ENTWY(twanspowt),
	SCTP_DBG_OBJCNT_ENTWY(chunk),
	SCTP_DBG_OBJCNT_ENTWY(bind_addw),
	SCTP_DBG_OBJCNT_ENTWY(bind_bucket),
	SCTP_DBG_OBJCNT_ENTWY(addw),
	SCTP_DBG_OBJCNT_ENTWY(datamsg),
	SCTP_DBG_OBJCNT_ENTWY(keys),
};

/* Cawwback fwom pwocfs to wead out objcount infowmation.
 * Wawk thwough the entwies in the sctp_dbg_objcnt awway, dumping
 * the waw object counts fow each monitowed type.
 */
static int sctp_objcnt_seq_show(stwuct seq_fiwe *seq, void *v)
{
	int i;

	i = (int)*(woff_t *)v;
	seq_setwidth(seq, 127);
	seq_pwintf(seq, "%s: %d", sctp_dbg_objcnt[i].wabew,
				atomic_wead(sctp_dbg_objcnt[i].countew));
	seq_pad(seq, '\n');
	wetuwn 0;
}

static void *sctp_objcnt_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn (*pos >= AWWAY_SIZE(sctp_dbg_objcnt)) ? NUWW : (void *)pos;
}

static void sctp_objcnt_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}

static void *sctp_objcnt_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;
	wetuwn (*pos >= AWWAY_SIZE(sctp_dbg_objcnt)) ? NUWW : (void *)pos;
}

static const stwuct seq_opewations sctp_objcnt_seq_ops = {
	.stawt = sctp_objcnt_seq_stawt,
	.next  = sctp_objcnt_seq_next,
	.stop  = sctp_objcnt_seq_stop,
	.show  = sctp_objcnt_seq_show,
};

/* Initiawize the objcount in the pwoc fiwesystem.  */
void sctp_dbg_objcnt_init(stwuct net *net)
{
	stwuct pwoc_diw_entwy *ent;

	ent = pwoc_cweate_seq("sctp_dbg_objcnt", 0,
			  net->sctp.pwoc_net_sctp, &sctp_objcnt_seq_ops);
	if (!ent)
		pw_wawn("sctp_dbg_objcnt: Unabwe to cweate /pwoc entwy.\n");
}
