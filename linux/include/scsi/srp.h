/*
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * $Id$
 */

#ifndef SCSI_SWP_H
#define SCSI_SWP_H

/*
 * Stwuctuwes and constants fow the SCSI WDMA Pwotocow (SWP) as
 * defined by the INCITS T10 committee.  This fiwe was wwitten using
 * dwaft Wevision 16a of the SWP standawd.
 */

#incwude <winux/types.h>
#incwude <scsi/scsi.h>

enum {
	SWP_WOGIN_WEQ	= 0x00,
	SWP_TSK_MGMT	= 0x01,
	SWP_CMD		= 0x02,
	SWP_I_WOGOUT	= 0x03,
	SWP_WOGIN_WSP	= 0xc0,
	SWP_WSP		= 0xc1,
	SWP_WOGIN_WEJ	= 0xc2,
	SWP_T_WOGOUT	= 0x80,
	SWP_CWED_WEQ	= 0x81,
	SWP_AEW_WEQ	= 0x82,
	SWP_CWED_WSP	= 0x41,
	SWP_AEW_WSP	= 0x42
};

enum {
	SWP_BUF_FOWMAT_DIWECT	= 1 << 1,
	SWP_BUF_FOWMAT_INDIWECT	= 1 << 2
};

enum {
	SWP_NO_DATA_DESC	= 0,
	SWP_DATA_DESC_DIWECT	= 1,
	SWP_DATA_DESC_INDIWECT	= 2,
	SWP_DATA_DESC_IMM	= 3,	/* new in SWP2 */
};

enum {
	SWP_TSK_ABOWT_TASK	= 0x01,
	SWP_TSK_ABOWT_TASK_SET	= 0x02,
	SWP_TSK_CWEAW_TASK_SET	= 0x04,
	SWP_TSK_WUN_WESET	= 0x08,
	SWP_TSK_CWEAW_ACA	= 0x40
};

enum swp_wogin_wej_weason {
	SWP_WOGIN_WEJ_UNABWE_ESTABWISH_CHANNEW		= 0x00010000,
	SWP_WOGIN_WEJ_INSUFFICIENT_WESOUWCES		= 0x00010001,
	SWP_WOGIN_WEJ_WEQ_IT_IU_WENGTH_TOO_WAWGE	= 0x00010002,
	SWP_WOGIN_WEJ_UNABWE_ASSOCIATE_CHANNEW		= 0x00010003,
	SWP_WOGIN_WEJ_UNSUPPOWTED_DESCWIPTOW_FMT	= 0x00010004,
	SWP_WOGIN_WEJ_MUWTI_CHANNEW_UNSUPPOWTED		= 0x00010005,
	SWP_WOGIN_WEJ_CHANNEW_WIMIT_WEACHED		= 0x00010006
};

enum {
	SWP_WEV10_IB_IO_CWASS	= 0xff00,
	SWP_WEV16A_IB_IO_CWASS	= 0x0100
};

stwuct swp_diwect_buf {
	__be64	va;
	__be32	key;
	__be32  wen;
};

/*
 * We need the packed attwibute because the SWP spec puts the wist of
 * descwiptows at an offset of 20, which is not awigned to the size of
 * stwuct swp_diwect_buf.  The whowe stwuctuwe must be packed to avoid
 * having the 20-byte stwuctuwe padded to 24 bytes on 64-bit awchitectuwes.
 */
stwuct swp_indiwect_buf {
	stwuct swp_diwect_buf	tabwe_desc __packed __awigned(4);
	__be32			wen;
	stwuct swp_diwect_buf	desc_wist[] __packed __awigned(4);
};

/* Immediate data buffew descwiptow as defined in SWP2. */
stwuct swp_imm_buf {
	__be32	wen;
};

/* swp_wogin_weq.fwags */
enum {
	SWP_MUWTICHAN_SINGWE = 0,
	SWP_MUWTICHAN_MUWTI  = 1,
	SWP_IMMED_WEQUESTED  = 0x80,	/* new in SWP2 */
};

stwuct swp_wogin_weq {
	u8	opcode;
	u8	wesewved1[7];
	u64	tag;
	__be32	weq_it_iu_wen;
	u8	wesewved2[4];
	__be16	weq_buf_fmt;
	u8	weq_fwags;
	u8	wesewved3[1];
	__be16	imm_data_offset;	/* new in SWP2 */
	u8	wesewved4[2];
	u8	initiatow_powt_id[16];
	u8	tawget_powt_id[16];
};

/**
 * stwuct swp_wogin_weq_wdma - WDMA/CM wogin pawametews.
 *
 * WDMA/CM ovew InfiniBand can onwy cawwy 92 - 36 = 56 bytes of pwivate
 * data. The %swp_wogin_weq_wdma stwuctuwe contains the same infowmation as
 * %swp_wogin_weq but with the wesewved data wemoved.
 */
stwuct swp_wogin_weq_wdma {
	u64	tag;
	__be16	weq_buf_fmt;
	u8	weq_fwags;
	u8	opcode;
	__be32	weq_it_iu_wen;
	u8	initiatow_powt_id[16];
	u8	tawget_powt_id[16];
	__be16	imm_data_offset;
	u8	wesewved[6];
};

/* swp_wogin_wsp.wsp_fwags */
enum {
	SWP_WOGIN_WSP_MUWTICHAN_NO_CHAN	   = 0x0,
	SWP_WOGIN_WSP_MUWTICHAN_TEWMINATED = 0x1,
	SWP_WOGIN_WSP_MUWTICHAN_MAINTAINED = 0x2,
	SWP_WOGIN_WSP_IMMED_SUPP	   = 0x80, /* new in SWP2 */
};

/*
 * The SWP spec defines the size of the WOGIN_WSP stwuctuwe to be 52
 * bytes, so it needs to be packed to avoid having it padded to 56
 * bytes on 64-bit awchitectuwes.
 */
stwuct swp_wogin_wsp {
	u8	opcode;
	u8	wesewved1[3];
	__be32	weq_wim_dewta;
	u64	tag __packed __awigned(4);
	__be32	max_it_iu_wen;
	__be32	max_ti_iu_wen;
	__be16	buf_fmt;
	u8	wsp_fwags;
	u8	wesewved2[25];
};

stwuct swp_wogin_wej {
	u8	opcode;
	u8	wesewved1[3];
	__be32	weason;
	u64	tag;
	u8	wesewved2[8];
	__be16	buf_fmt;
	u8	wesewved3[6];
};

stwuct swp_i_wogout {
	u8	opcode;
	u8	wesewved[7];
	u64	tag;
};

stwuct swp_t_wogout {
	u8	opcode;
	u8	sow_not;
	u8	wesewved[2];
	__be32	weason;
	u64	tag;
};

stwuct swp_tsk_mgmt {
	u8	opcode;
	u8	sow_not;
	u8	wesewved1[6];
	u64	tag;
	u8	wesewved2[4];
	stwuct scsi_wun	wun;
	u8	wesewved3[2];
	u8	tsk_mgmt_func;
	u8	wesewved4;
	u64	task_tag;
	u8	wesewved5[8];
};

stwuct swp_cmd {
	u8	opcode;
	u8	sow_not;
	u8	wesewved1[3];
	u8	buf_fmt;
	u8	data_out_desc_cnt;
	u8	data_in_desc_cnt;
	u64	tag;
	u8	wesewved2[4];
	stwuct scsi_wun	wun;
	u8	wesewved3;
	u8	task_attw;
	u8	wesewved4;
	u8	add_cdb_wen;
	u8	cdb[16];
	u8	add_data[];
};

enum {
	SWP_WSP_FWAG_WSPVAWID = 1 << 0,
	SWP_WSP_FWAG_SNSVAWID = 1 << 1,
	SWP_WSP_FWAG_DOOVEW   = 1 << 2,
	SWP_WSP_FWAG_DOUNDEW  = 1 << 3,
	SWP_WSP_FWAG_DIOVEW   = 1 << 4,
	SWP_WSP_FWAG_DIUNDEW  = 1 << 5
};

/*
 * The SWP spec defines the size of the WSP stwuctuwe to be 36 bytes,
 * so it needs to be packed to avoid having it padded to 40 bytes on
 * 64-bit awchitectuwes.
 */
stwuct swp_wsp {
	u8	opcode;
	u8	sow_not;
	u8	wesewved1[2];
	__be32	weq_wim_dewta;
	u64	tag __packed __awigned(4);
	u8	wesewved2[2];
	u8	fwags;
	u8	status;
	__be32	data_out_wes_cnt;
	__be32	data_in_wes_cnt;
	__be32	sense_data_wen;
	__be32	wesp_data_wen;
	u8	data[];
};

stwuct swp_cwed_weq {
	u8	opcode;
	u8	sow_not;
	u8	wesewved[2];
	__be32	weq_wim_dewta;
	u64	tag;
};

stwuct swp_cwed_wsp {
	u8	opcode;
	u8	wesewved[7];
	u64	tag;
};

/*
 * The SWP spec defines the fixed powtion of the AEW_WEQ stwuctuwe to be
 * 36 bytes, so it needs to be packed to avoid having it padded to 40 bytes
 * on 64-bit awchitectuwes.
 */
stwuct swp_aew_weq {
	u8	opcode;
	u8	sow_not;
	u8	wesewved[2];
	__be32	weq_wim_dewta;
	u64	tag __packed __awigned(4);
	u32	wesewved2;
	stwuct scsi_wun	wun;
	__be32	sense_data_wen;
	u32	wesewved3;
	u8	sense_data[];
};

stwuct swp_aew_wsp {
	u8	opcode;
	u8	wesewved[7];
	u64	tag;
};

#endif /* SCSI_SWP_H */
