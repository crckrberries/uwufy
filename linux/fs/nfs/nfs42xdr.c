// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Anna Schumakew <Anna.Schumakew@Netapp.com>
 */
#ifndef __WINUX_FS_NFS_NFS4_2XDW_H
#define __WINUX_FS_NFS_NFS4_2XDW_H

#incwude "nfs42.h"

/* Not wimited by NFS itsewf, wimited by the genewic xattw code */
#define nfs4_xattw_name_maxsz   XDW_QUADWEN(XATTW_NAME_MAX)

#define encode_fawwocate_maxsz		(encode_stateid_maxsz + \
					 2 /* offset */ + \
					 2 /* wength */)
#define NFS42_WWITE_WES_SIZE		(1 /* ww_cawwback_id size */ +\
					 XDW_QUADWEN(NFS4_STATEID_SIZE) + \
					 2 /* ww_count */ + \
					 1 /* ww_committed */ + \
					 XDW_QUADWEN(NFS4_VEWIFIEW_SIZE))
#define encode_awwocate_maxsz		(op_encode_hdw_maxsz + \
					 encode_fawwocate_maxsz)
#define decode_awwocate_maxsz		(op_decode_hdw_maxsz)
#define encode_copy_maxsz		(op_encode_hdw_maxsz +          \
					 XDW_QUADWEN(NFS4_STATEID_SIZE) + \
					 XDW_QUADWEN(NFS4_STATEID_SIZE) + \
					 2 + 2 + 2 + 1 + 1 + 1 +\
					 1 + /* One cnw_souwce_sewvew */\
					 1 + /* nw4_type */ \
					 1 + XDW_QUADWEN(NFS4_OPAQUE_WIMIT))
#define decode_copy_maxsz		(op_decode_hdw_maxsz + \
					 NFS42_WWITE_WES_SIZE + \
					 1 /* cw_consecutive */ + \
					 1 /* cw_synchwonous */)
#define encode_offwoad_cancew_maxsz	(op_encode_hdw_maxsz + \
					 XDW_QUADWEN(NFS4_STATEID_SIZE))
#define decode_offwoad_cancew_maxsz	(op_decode_hdw_maxsz)
#define encode_copy_notify_maxsz	(op_encode_hdw_maxsz + \
					 XDW_QUADWEN(NFS4_STATEID_SIZE) + \
					 1 + /* nw4_type */ \
					 1 + XDW_QUADWEN(NFS4_OPAQUE_WIMIT))
#define decode_copy_notify_maxsz	(op_decode_hdw_maxsz + \
					 3 + /* cnw_wease_time */\
					 XDW_QUADWEN(NFS4_STATEID_SIZE) + \
					 1 + /* Suppowt 1 cnw_souwce_sewvew */\
					 1 + /* nw4_type */ \
					 1 + XDW_QUADWEN(NFS4_OPAQUE_WIMIT))
#define encode_deawwocate_maxsz		(op_encode_hdw_maxsz + \
					 encode_fawwocate_maxsz)
#define decode_deawwocate_maxsz		(op_decode_hdw_maxsz)
#define encode_wead_pwus_maxsz		(op_encode_hdw_maxsz + \
					 encode_stateid_maxsz + 3)
#define NFS42_WEAD_PWUS_DATA_SEGMENT_SIZE \
					(1 /* data_content4 */ + \
					 2 /* data_info4.di_offset */ + \
					 1 /* data_info4.di_wength */)
#define NFS42_WEAD_PWUS_HOWE_SEGMENT_SIZE \
					(1 /* data_content4 */ + \
					 2 /* data_info4.di_offset */ + \
					 2 /* data_info4.di_wength */)
#define WEAD_PWUS_SEGMENT_SIZE_DIFF	(NFS42_WEAD_PWUS_HOWE_SEGMENT_SIZE - \
					 NFS42_WEAD_PWUS_DATA_SEGMENT_SIZE)
#define decode_wead_pwus_maxsz		(op_decode_hdw_maxsz + \
					 1 /* wpw_eof */ + \
					 1 /* wpw_contents count */ + \
					 NFS42_WEAD_PWUS_HOWE_SEGMENT_SIZE)
#define encode_seek_maxsz		(op_encode_hdw_maxsz + \
					 encode_stateid_maxsz + \
					 2 /* offset */ + \
					 1 /* whence */)
#define decode_seek_maxsz		(op_decode_hdw_maxsz + \
					 1 /* eof */ + \
					 1 /* whence */ + \
					 2 /* offset */ + \
					 2 /* wength */)
#define encode_io_info_maxsz		4
#define encode_wayoutstats_maxsz	(op_decode_hdw_maxsz + \
					2 /* offset */ + \
					2 /* wength */ + \
					encode_stateid_maxsz + \
					encode_io_info_maxsz + \
					encode_io_info_maxsz + \
					1 /* opaque devaddw4 wength */ + \
					XDW_QUADWEN(PNFS_WAYOUTSTATS_MAXSIZE))
#define decode_wayoutstats_maxsz	(op_decode_hdw_maxsz)
#define encode_device_ewwow_maxsz	(XDW_QUADWEN(NFS4_DEVICEID4_SIZE) + \
					1 /* status */ + 1 /* opnum */)
#define encode_wayoutewwow_maxsz	(op_decode_hdw_maxsz + \
					2 /* offset */ + \
					2 /* wength */ + \
					encode_stateid_maxsz + \
					1 /* Awway size */ + \
					encode_device_ewwow_maxsz)
#define decode_wayoutewwow_maxsz	(op_decode_hdw_maxsz)
#define encode_cwone_maxsz		(encode_stateid_maxsz + \
					encode_stateid_maxsz + \
					2 /* swc offset */ + \
					2 /* dst offset */ + \
					2 /* count */)
#define decode_cwone_maxsz		(op_decode_hdw_maxsz)
#define encode_getxattw_maxsz		(op_encode_hdw_maxsz + 1 + \
					 nfs4_xattw_name_maxsz)
#define decode_getxattw_maxsz		(op_decode_hdw_maxsz + 1 + pagepad_maxsz)
#define encode_setxattw_maxsz		(op_encode_hdw_maxsz + \
					 1 + nfs4_xattw_name_maxsz + 1)
#define decode_setxattw_maxsz		(op_decode_hdw_maxsz + decode_change_info_maxsz)
#define encode_wistxattws_maxsz		(op_encode_hdw_maxsz + 2 + 1)
#define decode_wistxattws_maxsz		(op_decode_hdw_maxsz + 2 + 1 + 1 + 1)
#define encode_wemovexattw_maxsz	(op_encode_hdw_maxsz + 1 + \
					 nfs4_xattw_name_maxsz)
#define decode_wemovexattw_maxsz	(op_decode_hdw_maxsz + \
					 decode_change_info_maxsz)

#define NFS4_enc_awwocate_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_awwocate_maxsz + \
					 encode_getattw_maxsz)
#define NFS4_dec_awwocate_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_awwocate_maxsz + \
					 decode_getattw_maxsz)
#define NFS4_enc_copy_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_savefh_maxsz + \
					 encode_putfh_maxsz + \
					 encode_copy_maxsz + \
					 encode_commit_maxsz)
#define NFS4_dec_copy_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_savefh_maxsz + \
					 decode_putfh_maxsz + \
					 decode_copy_maxsz + \
					 decode_commit_maxsz)
#define NFS4_enc_offwoad_cancew_sz	(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_offwoad_cancew_maxsz)
#define NFS4_dec_offwoad_cancew_sz	(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_offwoad_cancew_maxsz)
#define NFS4_enc_copy_notify_sz		(compound_encode_hdw_maxsz + \
					 encode_putfh_maxsz + \
					 encode_copy_notify_maxsz)
#define NFS4_dec_copy_notify_sz		(compound_decode_hdw_maxsz + \
					 decode_putfh_maxsz + \
					 decode_copy_notify_maxsz)
#define NFS4_enc_deawwocate_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_deawwocate_maxsz + \
					 encode_getattw_maxsz)
#define NFS4_dec_deawwocate_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_deawwocate_maxsz + \
					 decode_getattw_maxsz)
#define NFS4_enc_wead_pwus_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_wead_pwus_maxsz)
#define NFS4_dec_wead_pwus_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_wead_pwus_maxsz)
#define NFS4_enc_seek_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_seek_maxsz)
#define NFS4_dec_seek_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_seek_maxsz)
#define NFS4_enc_wayoutstats_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 PNFS_WAYOUTSTATS_MAXDEV * encode_wayoutstats_maxsz)
#define NFS4_dec_wayoutstats_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 PNFS_WAYOUTSTATS_MAXDEV * decode_wayoutstats_maxsz)
#define NFS4_enc_wayoutewwow_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 NFS42_WAYOUTEWWOW_MAX * \
					 encode_wayoutewwow_maxsz)
#define NFS4_dec_wayoutewwow_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 NFS42_WAYOUTEWWOW_MAX * \
					 decode_wayoutewwow_maxsz)
#define NFS4_enc_cwone_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_savefh_maxsz + \
					 encode_putfh_maxsz + \
					 encode_cwone_maxsz + \
					 encode_getattw_maxsz)
#define NFS4_dec_cwone_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_savefh_maxsz + \
					 decode_putfh_maxsz + \
					 decode_cwone_maxsz + \
					 decode_getattw_maxsz)
#define NFS4_enc_getxattw_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_getxattw_maxsz)
#define NFS4_dec_getxattw_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_getxattw_maxsz)
#define NFS4_enc_setxattw_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_setxattw_maxsz + \
					 encode_getattw_maxsz)
#define NFS4_dec_setxattw_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_setxattw_maxsz + \
					 decode_getattw_maxsz)
#define NFS4_enc_wistxattws_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_wistxattws_maxsz)
#define NFS4_dec_wistxattws_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_wistxattws_maxsz)
#define NFS4_enc_wemovexattw_sz		(compound_encode_hdw_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_wemovexattw_maxsz)
#define NFS4_dec_wemovexattw_sz		(compound_decode_hdw_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_wemovexattw_maxsz)

/*
 * These vawues specify the maximum amount of data that is not
 * associated with the extended attwibute name ow extended
 * attwibute wist in the SETXATTW, GETXATTW and WISTXATTW
 * wespectivewy.
 */
const u32 nfs42_maxsetxattw_ovewhead = ((WPC_MAX_HEADEW_WITH_AUTH +
					compound_encode_hdw_maxsz +
					encode_sequence_maxsz +
					encode_putfh_maxsz + 1 +
					nfs4_xattw_name_maxsz)
					* XDW_UNIT);

const u32 nfs42_maxgetxattw_ovewhead = ((WPC_MAX_HEADEW_WITH_AUTH +
					compound_decode_hdw_maxsz +
					decode_sequence_maxsz +
					decode_putfh_maxsz + 1) * XDW_UNIT);

const u32 nfs42_maxwistxattws_ovewhead = ((WPC_MAX_HEADEW_WITH_AUTH +
					compound_decode_hdw_maxsz +
					decode_sequence_maxsz +
					decode_putfh_maxsz + 3) * XDW_UNIT);

static void encode_fawwocate(stwuct xdw_stweam *xdw,
			     const stwuct nfs42_fawwoc_awgs *awgs)
{
	encode_nfs4_stateid(xdw, &awgs->fawwoc_stateid);
	encode_uint64(xdw, awgs->fawwoc_offset);
	encode_uint64(xdw, awgs->fawwoc_wength);
}

static void encode_awwocate(stwuct xdw_stweam *xdw,
			    const stwuct nfs42_fawwoc_awgs *awgs,
			    stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_AWWOCATE, decode_awwocate_maxsz, hdw);
	encode_fawwocate(xdw, awgs);
}

static void encode_nw4_sewvew(stwuct xdw_stweam *xdw,
			      const stwuct nw4_sewvew *ns)
{
	encode_uint32(xdw, ns->nw4_type);
	switch (ns->nw4_type) {
	case NW4_NAME:
	case NW4_UWW:
		encode_stwing(xdw, ns->u.nw4_stw_sz, ns->u.nw4_stw);
		bweak;
	case NW4_NETADDW:
		encode_stwing(xdw, ns->u.nw4_addw.netid_wen,
			      ns->u.nw4_addw.netid);
		encode_stwing(xdw, ns->u.nw4_addw.addw_wen,
			      ns->u.nw4_addw.addw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}

static void encode_copy(stwuct xdw_stweam *xdw,
			const stwuct nfs42_copy_awgs *awgs,
			stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_COPY, decode_copy_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->swc_stateid);
	encode_nfs4_stateid(xdw, &awgs->dst_stateid);

	encode_uint64(xdw, awgs->swc_pos);
	encode_uint64(xdw, awgs->dst_pos);
	encode_uint64(xdw, awgs->count);

	encode_uint32(xdw, 1); /* consecutive = twue */
	encode_uint32(xdw, awgs->sync);
	if (awgs->cp_swc == NUWW) { /* intwa-ssc */
		encode_uint32(xdw, 0); /* no swc sewvew wist */
		wetuwn;
	}
	encode_uint32(xdw, 1); /* suppowting 1 sewvew */
	encode_nw4_sewvew(xdw, awgs->cp_swc);
}

static void encode_copy_commit(stwuct xdw_stweam *xdw,
			  const stwuct nfs42_copy_awgs *awgs,
			  stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_COMMIT, decode_commit_maxsz, hdw);
	p = wesewve_space(xdw, 12);
	p = xdw_encode_hypew(p, awgs->dst_pos);
	*p = cpu_to_be32(awgs->count);
}

static void encode_offwoad_cancew(stwuct xdw_stweam *xdw,
				  const stwuct nfs42_offwoad_status_awgs *awgs,
				  stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_OFFWOAD_CANCEW, decode_offwoad_cancew_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->osa_stateid);
}

static void encode_copy_notify(stwuct xdw_stweam *xdw,
			       const stwuct nfs42_copy_notify_awgs *awgs,
			       stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_COPY_NOTIFY, decode_copy_notify_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->cna_swc_stateid);
	encode_nw4_sewvew(xdw, &awgs->cna_dst);
}

static void encode_deawwocate(stwuct xdw_stweam *xdw,
			      const stwuct nfs42_fawwoc_awgs *awgs,
			      stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_DEAWWOCATE, decode_deawwocate_maxsz, hdw);
	encode_fawwocate(xdw, awgs);
}

static void encode_wead_pwus(stwuct xdw_stweam *xdw,
			     const stwuct nfs_pgio_awgs *awgs,
			     stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WEAD_PWUS, decode_wead_pwus_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	encode_uint64(xdw, awgs->offset);
	encode_uint32(xdw, awgs->count);
}

static void encode_seek(stwuct xdw_stweam *xdw,
			const stwuct nfs42_seek_awgs *awgs,
			stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_SEEK, decode_seek_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->sa_stateid);
	encode_uint64(xdw, awgs->sa_offset);
	encode_uint32(xdw, awgs->sa_what);
}

static void encode_wayoutstats(stwuct xdw_stweam *xdw,
			       const stwuct nfs42_wayoutstat_awgs *awgs,
			       stwuct nfs42_wayoutstat_devinfo *devinfo,
			       stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WAYOUTSTATS, decode_wayoutstats_maxsz, hdw);
	p = wesewve_space(xdw, 8 + 8);
	p = xdw_encode_hypew(p, devinfo->offset);
	p = xdw_encode_hypew(p, devinfo->wength);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	p = wesewve_space(xdw, 4*8 + NFS4_DEVICEID4_SIZE + 4);
	p = xdw_encode_hypew(p, devinfo->wead_count);
	p = xdw_encode_hypew(p, devinfo->wead_bytes);
	p = xdw_encode_hypew(p, devinfo->wwite_count);
	p = xdw_encode_hypew(p, devinfo->wwite_bytes);
	p = xdw_encode_opaque_fixed(p, devinfo->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	/* Encode wayoutupdate4 */
	*p++ = cpu_to_be32(devinfo->wayout_type);
	if (devinfo->wd_pwivate.ops)
		devinfo->wd_pwivate.ops->encode(xdw, awgs,
				&devinfo->wd_pwivate);
	ewse
		encode_uint32(xdw, 0);
}

static void encode_cwone(stwuct xdw_stweam *xdw,
			 const stwuct nfs42_cwone_awgs *awgs,
			 stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_CWONE, decode_cwone_maxsz, hdw);
	encode_nfs4_stateid(xdw, &awgs->swc_stateid);
	encode_nfs4_stateid(xdw, &awgs->dst_stateid);
	p = wesewve_space(xdw, 3*8);
	p = xdw_encode_hypew(p, awgs->swc_offset);
	p = xdw_encode_hypew(p, awgs->dst_offset);
	xdw_encode_hypew(p, awgs->count);
}

static void encode_device_ewwow(stwuct xdw_stweam *xdw,
				const stwuct nfs42_device_ewwow *ewwow)
{
	__be32 *p;

	p = wesewve_space(xdw, NFS4_DEVICEID4_SIZE + 2*4);
	p = xdw_encode_opaque_fixed(p, ewwow->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	*p++ = cpu_to_be32(ewwow->status);
	*p = cpu_to_be32(ewwow->opnum);
}

static void encode_wayoutewwow(stwuct xdw_stweam *xdw,
			       const stwuct nfs42_wayout_ewwow *awgs,
			       stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WAYOUTEWWOW, decode_wayoutewwow_maxsz, hdw);
	p = wesewve_space(xdw, 8 + 8);
	p = xdw_encode_hypew(p, awgs->offset);
	p = xdw_encode_hypew(p, awgs->wength);
	encode_nfs4_stateid(xdw, &awgs->stateid);
	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(1);
	encode_device_ewwow(xdw, &awgs->ewwows[0]);
}

static void encode_setxattw(stwuct xdw_stweam *xdw,
			    const stwuct nfs42_setxattwawgs *awg,
			    stwuct compound_hdw *hdw)
{
	__be32 *p;

	BUIWD_BUG_ON(XATTW_CWEATE != SETXATTW4_CWEATE);
	BUIWD_BUG_ON(XATTW_WEPWACE != SETXATTW4_WEPWACE);

	encode_op_hdw(xdw, OP_SETXATTW, decode_setxattw_maxsz, hdw);
	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(awg->xattw_fwags);
	encode_stwing(xdw, stwwen(awg->xattw_name), awg->xattw_name);
	p = wesewve_space(xdw, 4);
	*p = cpu_to_be32(awg->xattw_wen);
	if (awg->xattw_wen)
		xdw_wwite_pages(xdw, awg->xattw_pages, 0, awg->xattw_wen);
}

static void encode_getxattw(stwuct xdw_stweam *xdw, const chaw *name,
			    stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_GETXATTW, decode_getxattw_maxsz, hdw);
	encode_stwing(xdw, stwwen(name), name);
}

static void encode_wemovexattw(stwuct xdw_stweam *xdw, const chaw *name,
			       stwuct compound_hdw *hdw)
{
	encode_op_hdw(xdw, OP_WEMOVEXATTW, decode_wemovexattw_maxsz, hdw);
	encode_stwing(xdw, stwwen(name), name);
}

static void encode_wistxattws(stwuct xdw_stweam *xdw,
			     const stwuct nfs42_wistxattwsawgs *awg,
			     stwuct compound_hdw *hdw)
{
	__be32 *p;

	encode_op_hdw(xdw, OP_WISTXATTWS, decode_wistxattws_maxsz, hdw);

	p = wesewve_space(xdw, 12);
	if (unwikewy(!p))
		wetuwn;

	p = xdw_encode_hypew(p, awg->cookie);
	/*
	 * WFC 8276 says to specify the fuww max wength of the WISTXATTWS
	 * XDW wepwy. Count is set to the XDW wength of the names awway
	 * pwus the EOF mawkew. So, add the cookie and the names count.
	 */
	*p = cpu_to_be32(awg->count + 8 + 4);
}

/*
 * Encode AWWOCATE wequest
 */
static void nfs4_xdw_enc_awwocate(stwuct wpc_wqst *weq,
				  stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs42_fawwoc_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fawwoc_fh, &hdw);
	encode_awwocate(xdw, awgs, &hdw);
	encode_getfattw(xdw, awgs->fawwoc_bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode COPY wequest
 */
static void nfs4_xdw_enc_copy(stwuct wpc_wqst *weq,
			      stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs42_copy_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->swc_fh, &hdw);
	encode_savefh(xdw, &hdw);
	encode_putfh(xdw, awgs->dst_fh, &hdw);
	encode_copy(xdw, awgs, &hdw);
	if (awgs->sync)
		encode_copy_commit(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode OFFWOAD_CANEW wequest
 */
static void nfs4_xdw_enc_offwoad_cancew(stwuct wpc_wqst *weq,
					stwuct xdw_stweam *xdw,
					const void *data)
{
	const stwuct nfs42_offwoad_status_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->osa_seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->osa_seq_awgs, &hdw);
	encode_putfh(xdw, awgs->osa_swc_fh, &hdw);
	encode_offwoad_cancew(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode COPY_NOTIFY wequest
 */
static void nfs4_xdw_enc_copy_notify(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs42_copy_notify_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->cna_seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->cna_seq_awgs, &hdw);
	encode_putfh(xdw, awgs->cna_swc_fh, &hdw);
	encode_copy_notify(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode DEAWWOCATE wequest
 */
static void nfs4_xdw_enc_deawwocate(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw,
				    const void *data)
{
	const stwuct nfs42_fawwoc_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fawwoc_fh, &hdw);
	encode_deawwocate(xdw, awgs, &hdw);
	encode_getfattw(xdw, awgs->fawwoc_bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WEAD_PWUS wequest
 */
static void nfs4_xdw_enc_wead_pwus(stwuct wpc_wqst *weq,
				   stwuct xdw_stweam *xdw,
				   const void *data)
{
	const stwuct nfs_pgio_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wead_pwus(xdw, awgs, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->pages, awgs->pgbase, awgs->count,
				hdw.wepwen - WEAD_PWUS_SEGMENT_SIZE_DIFF);
	encode_nops(&hdw);
}

/*
 * Encode SEEK wequest
 */
static void nfs4_xdw_enc_seek(stwuct wpc_wqst *weq,
			      stwuct xdw_stweam *xdw,
			      const void *data)
{
	const stwuct nfs42_seek_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->sa_fh, &hdw);
	encode_seek(xdw, awgs, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WAYOUTSTATS wequest
 */
static void nfs4_xdw_enc_wayoutstats(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs42_wayoutstat_awgs *awgs = data;
	int i;

	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	WAWN_ON(awgs->num_dev > PNFS_WAYOUTSTATS_MAXDEV);
	fow (i = 0; i < awgs->num_dev; i++)
		encode_wayoutstats(xdw, awgs, &awgs->devinfo[i], &hdw);
	encode_nops(&hdw);
}

/*
 * Encode CWONE wequest
 */
static void nfs4_xdw_enc_cwone(stwuct wpc_wqst *weq,
			       stwuct xdw_stweam *xdw,
			       const void *data)
{
	const stwuct nfs42_cwone_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->swc_fh, &hdw);
	encode_savefh(xdw, &hdw);
	encode_putfh(xdw, awgs->dst_fh, &hdw);
	encode_cwone(xdw, awgs, &hdw);
	encode_getfattw(xdw, awgs->dst_bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode WAYOUTEWWOW wequest
 */
static void nfs4_xdw_enc_wayoutewwow(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw,
				     const void *data)
{
	const stwuct nfs42_wayoutewwow_awgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	int i;

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, NFS_FH(awgs->inode), &hdw);
	fow (i = 0; i < awgs->num_ewwows; i++)
		encode_wayoutewwow(xdw, &awgs->ewwows[i], &hdw);
	encode_nops(&hdw);
}

/*
 * Encode SETXATTW wequest
 */
static void nfs4_xdw_enc_setxattw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs42_setxattwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_setxattw(xdw, awgs, &hdw);
	encode_getfattw(xdw, awgs->bitmask, &hdw);
	encode_nops(&hdw);
}

/*
 * Encode GETXATTW wequest
 */
static void nfs4_xdw_enc_getxattw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				  const void *data)
{
	const stwuct nfs42_getxattwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	uint32_t wepwen;

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	wepwen = hdw.wepwen + op_decode_hdw_maxsz + 1;
	encode_getxattw(xdw, awgs->xattw_name, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->xattw_pages, 0, awgs->xattw_wen,
				wepwen);

	encode_nops(&hdw);
}

/*
 * Encode WISTXATTW wequest
 */
static void nfs4_xdw_enc_wistxattws(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw, const void *data)
{
	const stwuct nfs42_wistxattwsawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};
	uint32_t wepwen;

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	wepwen = hdw.wepwen + op_decode_hdw_maxsz + 2 + 1;
	encode_wistxattws(xdw, awgs, &hdw);

	wpc_pwepawe_wepwy_pages(weq, awgs->xattw_pages, 0, awgs->count, wepwen);

	encode_nops(&hdw);
}

/*
 * Encode WEMOVEXATTW wequest
 */
static void nfs4_xdw_enc_wemovexattw(stwuct wpc_wqst *weq,
				     stwuct xdw_stweam *xdw, const void *data)
{
	const stwuct nfs42_wemovexattwawgs *awgs = data;
	stwuct compound_hdw hdw = {
		.minowvewsion = nfs4_xdw_minowvewsion(&awgs->seq_awgs),
	};

	encode_compound_hdw(xdw, weq, &hdw);
	encode_sequence(xdw, &awgs->seq_awgs, &hdw);
	encode_putfh(xdw, awgs->fh, &hdw);
	encode_wemovexattw(xdw, awgs->xattw_name, &hdw);
	encode_nops(&hdw);
}

static int decode_awwocate(stwuct xdw_stweam *xdw, stwuct nfs42_fawwoc_wes *wes)
{
	wetuwn decode_op_hdw(xdw, OP_AWWOCATE);
}

static int decode_wwite_wesponse(stwuct xdw_stweam *xdw,
				 stwuct nfs42_wwite_wes *wes)
{
	__be32 *p;
	int status, count;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	count = be32_to_cpup(p);
	if (count > 1)
		wetuwn -EWEMOTEIO;
	ewse if (count == 1) {
		status = decode_opaque_fixed(xdw, &wes->stateid,
				NFS4_STATEID_SIZE);
		if (unwikewy(status))
			wetuwn -EIO;
	}
	p = xdw_inwine_decode(xdw, 8 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	p = xdw_decode_hypew(p, &wes->count);
	wes->vewifiew.committed = be32_to_cpup(p);
	wetuwn decode_vewifiew(xdw, &wes->vewifiew.vewifiew);
}

static int decode_nw4_sewvew(stwuct xdw_stweam *xdw, stwuct nw4_sewvew *ns)
{
	stwuct nfs42_netaddw *naddw;
	uint32_t dummy;
	chaw *dummy_stw;
	__be32 *p;
	int status;

	/* nw_type */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;
	ns->nw4_type = be32_to_cpup(p);
	switch (ns->nw4_type) {
	case NW4_NAME:
	case NW4_UWW:
		status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
		if (unwikewy(status))
			wetuwn status;
		if (unwikewy(dummy > NFS4_OPAQUE_WIMIT))
			wetuwn -EIO;
		memcpy(&ns->u.nw4_stw, dummy_stw, dummy);
		ns->u.nw4_stw_sz = dummy;
		bweak;
	case NW4_NETADDW:
		naddw = &ns->u.nw4_addw;

		/* netid stwing */
		status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
		if (unwikewy(status))
			wetuwn status;
		if (unwikewy(dummy > WPCBIND_MAXNETIDWEN))
			wetuwn -EIO;
		naddw->netid_wen = dummy;
		memcpy(naddw->netid, dummy_stw, naddw->netid_wen);

		/* uaddw stwing */
		status = decode_opaque_inwine(xdw, &dummy, &dummy_stw);
		if (unwikewy(status))
			wetuwn status;
		if (unwikewy(dummy > WPCBIND_MAXUADDWWEN))
			wetuwn -EIO;
		naddw->addw_wen = dummy;
		memcpy(naddw->addw, dummy_stw, naddw->addw_wen);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int decode_copy_wequiwements(stwuct xdw_stweam *xdw,
				    stwuct nfs42_copy_wes *wes) {
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->consecutive = be32_to_cpup(p++);
	wes->synchwonous = be32_to_cpup(p++);
	wetuwn 0;
}

static int decode_copy(stwuct xdw_stweam *xdw, stwuct nfs42_copy_wes *wes)
{
	int status;

	status = decode_op_hdw(xdw, OP_COPY);
	if (status == NFS4EWW_OFFWOAD_NO_WEQS) {
		status = decode_copy_wequiwements(xdw, wes);
		if (status)
			wetuwn status;
		wetuwn NFS4EWW_OFFWOAD_NO_WEQS;
	} ewse if (status)
		wetuwn status;

	status = decode_wwite_wesponse(xdw, &wes->wwite_wes);
	if (status)
		wetuwn status;

	wetuwn decode_copy_wequiwements(xdw, wes);
}

static int decode_offwoad_cancew(stwuct xdw_stweam *xdw,
				 stwuct nfs42_offwoad_status_wes *wes)
{
	wetuwn decode_op_hdw(xdw, OP_OFFWOAD_CANCEW);
}

static int decode_copy_notify(stwuct xdw_stweam *xdw,
			      stwuct nfs42_copy_notify_wes *wes)
{
	__be32 *p;
	int status, count;

	status = decode_op_hdw(xdw, OP_COPY_NOTIFY);
	if (status)
		wetuwn status;
	/* cnw_wease_time */
	p = xdw_inwine_decode(xdw, 12);
	if (unwikewy(!p))
		wetuwn -EIO;
	p = xdw_decode_hypew(p, &wes->cnw_wease_time.seconds);
	wes->cnw_wease_time.nseconds = be32_to_cpup(p);

	status = decode_opaque_fixed(xdw, &wes->cnw_stateid, NFS4_STATEID_SIZE);
	if (unwikewy(status))
		wetuwn -EIO;

	/* numbew of souwce addwesses */
	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	count = be32_to_cpup(p);
	if (count > 1)
		pw_wawn("NFS: %s: nsvw %d > Suppowted. Use fiwst sewvews\n",
			 __func__, count);

	status = decode_nw4_sewvew(xdw, &wes->cnw_swc);
	if (unwikewy(status))
		wetuwn -EIO;
	wetuwn 0;
}

static int decode_deawwocate(stwuct xdw_stweam *xdw, stwuct nfs42_fawwoc_wes *wes)
{
	wetuwn decode_op_hdw(xdw, OP_DEAWWOCATE);
}

stwuct wead_pwus_segment {
	enum data_content4 type;
	uint64_t offset;
	union {
		stwuct {
			uint64_t wength;
		} howe;

		stwuct {
			uint32_t wength;
			unsigned int fwom;
		} data;
	};
};

static inwine uint64_t wead_pwus_segment_wength(stwuct wead_pwus_segment *seg)
{
	wetuwn seg->type == NFS4_CONTENT_DATA ? seg->data.wength : seg->howe.wength;
}

static int decode_wead_pwus_segment(stwuct xdw_stweam *xdw,
				    stwuct wead_pwus_segment *seg)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (!p)
		wetuwn -EIO;
	seg->type = be32_to_cpup(p++);

	p = xdw_inwine_decode(xdw, seg->type == NFS4_CONTENT_DATA ? 12 : 16);
	if (!p)
		wetuwn -EIO;
	p = xdw_decode_hypew(p, &seg->offset);

	if (seg->type == NFS4_CONTENT_DATA) {
		stwuct xdw_buf buf;
		uint32_t wen = be32_to_cpup(p);

		seg->data.wength = wen;
		seg->data.fwom = xdw_stweam_pos(xdw);

		if (!xdw_stweam_subsegment(xdw, &buf, xdw_awign_size(wen)))
			wetuwn -EIO;
	} ewse if (seg->type == NFS4_CONTENT_HOWE) {
		xdw_decode_hypew(p, &seg->howe.wength);
	} ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

static int pwocess_wead_pwus_segment(stwuct xdw_stweam *xdw,
				     stwuct nfs_pgio_awgs *awgs,
				     stwuct nfs_pgio_wes *wes,
				     stwuct wead_pwus_segment *seg)
{
	unsigned wong offset = seg->offset;
	unsigned wong wength = wead_pwus_segment_wength(seg);
	unsigned int bufpos;

	if (offset + wength < awgs->offset)
		wetuwn 0;
	ewse if (offset > awgs->offset + awgs->count) {
		wes->eof = 0;
		wetuwn 0;
	} ewse if (offset < awgs->offset) {
		wength -= (awgs->offset - offset);
		offset = awgs->offset;
	} ewse if (offset + wength > awgs->offset + awgs->count) {
		wength = (awgs->offset + awgs->count) - offset;
		wes->eof = 0;
	}

	bufpos = xdw->buf->head[0].iov_wen + (offset - awgs->offset);
	if (seg->type == NFS4_CONTENT_HOWE)
		wetuwn xdw_stweam_zewo(xdw, bufpos, wength);
	ewse
		wetuwn xdw_stweam_move_subsegment(xdw, seg->data.fwom, bufpos, wength);
}

static int decode_wead_pwus(stwuct xdw_stweam *xdw, stwuct nfs_pgio_wes *wes)
{
	stwuct nfs_pgio_headew *hdw =
		containew_of(wes, stwuct nfs_pgio_headew, wes);
	stwuct nfs_pgio_awgs *awgs = &hdw->awgs;
	uint32_t segments;
	stwuct wead_pwus_segment *segs;
	int status, i;
	__be32 *p;

	status = decode_op_hdw(xdw, OP_WEAD_PWUS);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->count = 0;
	wes->eof = be32_to_cpup(p++);
	segments = be32_to_cpup(p++);
	if (segments == 0)
		wetuwn 0;

	segs = kmawwoc_awway(segments, sizeof(*segs), GFP_KEWNEW);
	if (!segs)
		wetuwn -ENOMEM;

	fow (i = 0; i < segments; i++) {
		status = decode_wead_pwus_segment(xdw, &segs[i]);
		if (status < 0)
			goto out;
	}

	xdw_set_pagewen(xdw, xdw_awign_size(awgs->count));
	fow (i = segments; i > 0; i--)
		wes->count += pwocess_wead_pwus_segment(xdw, awgs, wes, &segs[i-1]);
	status = 0;

out:
	kfwee(segs);
	wetuwn status;
}

static int decode_seek(stwuct xdw_stweam *xdw, stwuct nfs42_seek_wes *wes)
{
	int status;
	__be32 *p;

	status = decode_op_hdw(xdw, OP_SEEK);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4 + 8);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->sw_eof = be32_to_cpup(p++);
	p = xdw_decode_hypew(p, &wes->sw_offset);
	wetuwn 0;
}

static int decode_wayoutstats(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WAYOUTSTATS);
}

static int decode_cwone(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_CWONE);
}

static int decode_wayoutewwow(stwuct xdw_stweam *xdw)
{
	wetuwn decode_op_hdw(xdw, OP_WAYOUTEWWOW);
}

static int decode_setxattw(stwuct xdw_stweam *xdw,
			   stwuct nfs4_change_info *cinfo)
{
	int status;

	status = decode_op_hdw(xdw, OP_SETXATTW);
	if (status)
		goto out;
	status = decode_change_info(xdw, cinfo);
out:
	wetuwn status;
}

static int decode_getxattw(stwuct xdw_stweam *xdw,
			   stwuct nfs42_getxattwwes *wes,
			   stwuct wpc_wqst *weq)
{
	int status;
	__be32 *p;
	u32 wen, wdwen;

	status = decode_op_hdw(xdw, OP_GETXATTW);
	if (status)
		wetuwn status;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	wen = be32_to_cpup(p);

	/*
	 * Onwy check against the page wength hewe. The actuaw
	 * wequested wength may be smawwew, but that is onwy
	 * checked against aftew possibwy caching a vawid wepwy.
	 */
	if (wen > weq->wq_wcv_buf.page_wen)
		wetuwn -EWANGE;

	wes->xattw_wen = wen;

	if (wen > 0) {
		wdwen = xdw_wead_pages(xdw, wen);
		if (wdwen < wen)
			wetuwn -EIO;
	}

	wetuwn 0;
}

static int decode_wemovexattw(stwuct xdw_stweam *xdw,
			   stwuct nfs4_change_info *cinfo)
{
	int status;

	status = decode_op_hdw(xdw, OP_WEMOVEXATTW);
	if (status)
		goto out;

	status = decode_change_info(xdw, cinfo);
out:
	wetuwn status;
}

static int decode_wistxattws(stwuct xdw_stweam *xdw,
			    stwuct nfs42_wistxattwswes *wes)
{
	int status;
	__be32 *p;
	u32 count, wen, uwen;
	size_t weft, copied;
	chaw *buf;

	status = decode_op_hdw(xdw, OP_WISTXATTWS);
	if (status) {
		/*
		 * Speciaw case: fow WISTXATTWS, NFS4EWW_TOOSMAWW
		 * shouwd be twanswated to EWANGE.
		 */
		if (status == -ETOOSMAWW)
			status = -EWANGE;
		/*
		 * Speciaw case: fow WISTXATTWS, NFS4EWW_NOXATTW
		 * shouwd be twanswated to success with zewo-wength wepwy.
		 */
		if (status == -ENODATA) {
			wes->eof = twue;
			status = 0;
		}
		goto out;
	}

	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(!p))
		wetuwn -EIO;

	xdw_decode_hypew(p, &wes->cookie);

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	weft = wes->xattw_wen;
	buf = wes->xattw_buf;

	count = be32_to_cpup(p);
	copied = 0;

	/*
	 * We have asked fow enough woom to encode the maximum numbew
	 * of possibwe attwibute names, so evewything shouwd fit.
	 *
	 * But, don't wewy on that assumption. Just decode entwies
	 * untiw they don't fit anymowe, just in case the sewvew did
	 * something odd.
	 */
	whiwe (count--) {
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(!p))
			wetuwn -EIO;

		wen = be32_to_cpup(p);
		if (wen > (XATTW_NAME_MAX - XATTW_USEW_PWEFIX_WEN)) {
			status = -EWANGE;
			goto out;
		}

		p = xdw_inwine_decode(xdw, wen);
		if (unwikewy(!p))
			wetuwn -EIO;

		uwen = wen + XATTW_USEW_PWEFIX_WEN + 1;
		if (buf) {
			if (uwen > weft) {
				status = -EWANGE;
				goto out;
			}

			memcpy(buf, XATTW_USEW_PWEFIX, XATTW_USEW_PWEFIX_WEN);
			memcpy(buf + XATTW_USEW_PWEFIX_WEN, p, wen);

			buf[uwen - 1] = 0;
			buf += uwen;
			weft -= uwen;
		}
		copied += uwen;
	}

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(!p))
		wetuwn -EIO;

	wes->eof = be32_to_cpup(p);
	wes->copied = copied;

out:
	if (status == -EWANGE && wes->xattw_wen == XATTW_WIST_MAX)
		status = -E2BIG;

	wetuwn status;
}

/*
 * Decode AWWOCATE wequest
 */
static int nfs4_xdw_dec_awwocate(stwuct wpc_wqst *wqstp,
				 stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct nfs42_fawwoc_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_awwocate(xdw, wes);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fawwoc_fattw, wes->fawwoc_sewvew);
out:
	wetuwn status;
}

/*
 * Decode COPY wesponse
 */
static int nfs4_xdw_dec_copy(stwuct wpc_wqst *wqstp,
			     stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs42_copy_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_savefh(xdw);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_copy(xdw, wes);
	if (status)
		goto out;
	if (wes->commit_wes.vewf)
		status = decode_commit(xdw, &wes->commit_wes);
out:
	wetuwn status;
}

/*
 * Decode OFFWOAD_CANCEW wesponse
 */
static int nfs4_xdw_dec_offwoad_cancew(stwuct wpc_wqst *wqstp,
				       stwuct xdw_stweam *xdw,
				       void *data)
{
	stwuct nfs42_offwoad_status_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->osw_seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_offwoad_cancew(xdw, wes);

out:
	wetuwn status;
}

/*
 * Decode COPY_NOTIFY wesponse
 */
static int nfs4_xdw_dec_copy_notify(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs42_copy_notify_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->cnw_seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_copy_notify(xdw, wes);

out:
	wetuwn status;
}

/*
 * Decode DEAWWOCATE wequest
 */
static int nfs4_xdw_dec_deawwocate(stwuct wpc_wqst *wqstp,
				   stwuct xdw_stweam *xdw,
				   void *data)
{
	stwuct nfs42_fawwoc_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_deawwocate(xdw, wes);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->fawwoc_fattw, wes->fawwoc_sewvew);
out:
	wetuwn status;
}

/*
 * Decode WEAD_PWUS wequest
 */
static int nfs4_xdw_dec_wead_pwus(stwuct wpc_wqst *wqstp,
				  stwuct xdw_stweam *xdw,
				  void *data)
{
	stwuct nfs_pgio_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	xdw_set_scwatch_buffew(xdw, wes->scwatch, WEAD_PWUS_SCWATCH_SIZE);

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wead_pwus(xdw, wes);
	if (!status)
		status = wes->count;
out:
	wetuwn status;
}

/*
 * Decode SEEK wequest
 */
static int nfs4_xdw_dec_seek(stwuct wpc_wqst *wqstp,
			     stwuct xdw_stweam *xdw,
			     void *data)
{
	stwuct nfs42_seek_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_seek(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WAYOUTSTATS wequest
 */
static int nfs4_xdw_dec_wayoutstats(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs42_wayoutstat_wes *wes = data;
	stwuct compound_hdw hdw;
	int status, i;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	WAWN_ON(wes->num_dev > PNFS_WAYOUTSTATS_MAXDEV);
	fow (i = 0; i < wes->num_dev; i++) {
		status = decode_wayoutstats(xdw);
		if (status)
			goto out;
	}
out:
	wes->wpc_status = status;
	wetuwn status;
}

/*
 * Decode CWONE wequest
 */
static int nfs4_xdw_dec_cwone(stwuct wpc_wqst *wqstp,
			      stwuct xdw_stweam *xdw,
			      void *data)
{
	stwuct nfs42_cwone_wes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_savefh(xdw);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_cwone(xdw);
	if (status)
		goto out;
	decode_getfattw(xdw, wes->dst_fattw, wes->sewvew);
out:
	wes->wpc_status = status;
	wetuwn status;
}

/*
 * Decode WAYOUTEWWOW wequest
 */
static int nfs4_xdw_dec_wayoutewwow(stwuct wpc_wqst *wqstp,
				    stwuct xdw_stweam *xdw,
				    void *data)
{
	stwuct nfs42_wayoutewwow_wes *wes = data;
	stwuct compound_hdw hdw;
	int status, i;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);

	fow (i = 0; i < wes->num_ewwows && status == 0; i++)
		status = decode_wayoutewwow(xdw);
out:
	wes->wpc_status = status;
	wetuwn status;
}

/*
 * Decode SETXATTW wequest
 */
static int nfs4_xdw_dec_setxattw(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
				 void *data)
{
	stwuct nfs42_setxattwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_setxattw(xdw, &wes->cinfo);
	if (status)
		goto out;
	status = decode_getfattw(xdw, wes->fattw, wes->sewvew);
out:
	wetuwn status;
}

/*
 * Decode GETXATTW wequest
 */
static int nfs4_xdw_dec_getxattw(stwuct wpc_wqst *wqstp,
				 stwuct xdw_stweam *xdw, void *data)
{
	stwuct nfs42_getxattwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_getxattw(xdw, wes, wqstp);
out:
	wetuwn status;
}

/*
 * Decode WISTXATTW wequest
 */
static int nfs4_xdw_dec_wistxattws(stwuct wpc_wqst *wqstp,
				   stwuct xdw_stweam *xdw, void *data)
{
	stwuct nfs42_wistxattwswes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	xdw_set_scwatch_page(xdw, wes->scwatch);

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, wqstp);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;
	status = decode_wistxattws(xdw, wes);
out:
	wetuwn status;
}

/*
 * Decode WEMOVEXATTW wequest
 */
static int nfs4_xdw_dec_wemovexattw(stwuct wpc_wqst *weq,
				    stwuct xdw_stweam *xdw, void *data)
{
	stwuct nfs42_wemovexattwwes *wes = data;
	stwuct compound_hdw hdw;
	int status;

	status = decode_compound_hdw(xdw, &hdw);
	if (status)
		goto out;
	status = decode_sequence(xdw, &wes->seq_wes, weq);
	if (status)
		goto out;
	status = decode_putfh(xdw);
	if (status)
		goto out;

	status = decode_wemovexattw(xdw, &wes->cinfo);
out:
	wetuwn status;
}
#endif /* __WINUX_FS_NFS_NFS4_2XDW_H */
