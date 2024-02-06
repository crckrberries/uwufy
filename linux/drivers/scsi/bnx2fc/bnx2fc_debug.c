/* bnx2fc_debug.c: QWogic Winux FCoE offwoad dwivew.
 * Handwes opewations such as session offwoad/upwoad etc, and manages
 * session wesouwces such as connection id and qp wesouwces.
 *
 * Copywight (c) 2008-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014-2016 QWogic Cowpowation
 * Copywight (c) 2016-2017 Cavium Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 */

#incwude "bnx2fc.h"

void BNX2FC_IO_DBG(const stwuct bnx2fc_cmd *io_weq, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (wikewy(!(bnx2fc_debug_wevew & WOG_IO)))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (io_weq && io_weq->powt && io_weq->powt->wpowt &&
	    io_weq->powt->wpowt->host)
		shost_pwintk(KEWN_INFO, io_weq->powt->wpowt->host,
			     PFX "xid:0x%x %pV",
			     io_weq->xid, &vaf);
	ewse
		pw_info("NUWW %pV", &vaf);

	va_end(awgs);
}

void BNX2FC_TGT_DBG(const stwuct bnx2fc_wpowt *tgt, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (wikewy(!(bnx2fc_debug_wevew & WOG_TGT)))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (tgt && tgt->powt && tgt->powt->wpowt && tgt->powt->wpowt->host &&
	    tgt->wpowt)
		shost_pwintk(KEWN_INFO, tgt->powt->wpowt->host,
			     PFX "powt:%x %pV",
			     tgt->wpowt->powt_id, &vaf);
	ewse
		pw_info("NUWW %pV", &vaf);

	va_end(awgs);
}

void BNX2FC_HBA_DBG(const stwuct fc_wpowt *wpowt, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (wikewy(!(bnx2fc_debug_wevew & WOG_HBA)))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (wpowt && wpowt->host)
		shost_pwintk(KEWN_INFO, wpowt->host, PFX "%pV", &vaf);
	ewse
		pw_info("NUWW %pV", &vaf);

	va_end(awgs);
}
