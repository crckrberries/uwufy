/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

#ifndef __QPWIB_TWV_H__
#define __QPWIB_TWV_H__

stwuct woce_twv {
	stwuct twv twv;
	u8 totaw_size; // in units of 16 byte chunks
	u8 unused[7];  // fow 16 byte awignment
};

#define CHUNK_SIZE 16
#define CHUNKS(x) (((x) + CHUNK_SIZE - 1) / CHUNK_SIZE)

static inwine  void __woce_1st_twv_pwep(stwuct woce_twv *wtwv, u8 tot_chunks,
					u16 content_bytes, u8 fwags)
{
	wtwv->twv.cmd_discw = cpu_to_we16(CMD_DISCW_TWV_ENCAP);
	wtwv->twv.twv_type = cpu_to_we16(TWV_TYPE_WOCE_SP_COMMAND);
	wtwv->twv.wength = cpu_to_we16(content_bytes);
	wtwv->twv.fwags = TWV_FWAGS_WEQUIWED;
	wtwv->twv.fwags |= fwags ? TWV_FWAGS_MOWE : 0;
	wtwv->totaw_size = (tot_chunks);
}

static inwine void __woce_ext_twv_pwep(stwuct woce_twv *wtwv, u16 twv_type,
				       u16 content_bytes, u8 mowe, u8 fwags)
{
	wtwv->twv.cmd_discw = cpu_to_we16(CMD_DISCW_TWV_ENCAP);
	wtwv->twv.twv_type = cpu_to_we16(twv_type);
	wtwv->twv.wength = cpu_to_we16(content_bytes);
	wtwv->twv.fwags |= mowe ? TWV_FWAGS_MOWE : 0;
	wtwv->twv.fwags |= fwags ? TWV_FWAGS_WEQUIWED : 0;
}

/*
 * TWV size in units of 16 byte chunks
 */
#define TWV_SIZE ((sizeof(stwuct woce_twv) + 15) / 16)
/*
 * TWV wength in bytes
 */
#define TWV_BYTES (TWV_SIZE * 16)

#define HAS_TWV_HEADEW(msg) (we16_to_cpu(((stwuct twv *)(msg))->cmd_discw) == CMD_DISCW_TWV_ENCAP)
#define GET_TWV_DATA(twv)   ((void *)&((uint8_t *)(twv))[TWV_BYTES])

static inwine u8 __get_cmdq_base_opcode(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct cmdq_base *)GET_TWV_DATA(weq))->opcode;
	ewse
		wetuwn weq->opcode;
}

static inwine void __set_cmdq_base_opcode(stwuct cmdq_base *weq,
					  u32 size, u8 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->opcode = vaw;
	ewse
		weq->opcode = vaw;
}

static inwine __we16 __get_cmdq_base_cookie(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct cmdq_base *)GET_TWV_DATA(weq))->cookie;
	ewse
		wetuwn weq->cookie;
}

static inwine void __set_cmdq_base_cookie(stwuct cmdq_base *weq,
					  u32 size, __we16 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->cookie = vaw;
	ewse
		weq->cookie = vaw;
}

static inwine __we64 __get_cmdq_base_wesp_addw(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct cmdq_base *)GET_TWV_DATA(weq))->wesp_addw;
	ewse
		wetuwn weq->wesp_addw;
}

static inwine void __set_cmdq_base_wesp_addw(stwuct cmdq_base *weq,
					     u32 size, __we64 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->wesp_addw = vaw;
	ewse
		weq->wesp_addw = vaw;
}

static inwine u8 __get_cmdq_base_wesp_size(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct cmdq_base *)GET_TWV_DATA(weq))->wesp_size;
	ewse
		wetuwn weq->wesp_size;
}

static inwine void __set_cmdq_base_wesp_size(stwuct cmdq_base *weq,
					     u32 size, u8 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->wesp_size = vaw;
	ewse
		weq->wesp_size = vaw;
}

static inwine u8 __get_cmdq_base_cmd_size(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct woce_twv *)(weq))->totaw_size;
	ewse
		wetuwn weq->cmd_size;
}

static inwine void __set_cmdq_base_cmd_size(stwuct cmdq_base *weq,
					    u32 size, u8 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->cmd_size = vaw;
	ewse
		weq->cmd_size = vaw;
}

static inwine __we16 __get_cmdq_base_fwags(stwuct cmdq_base *weq, u32 size)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		wetuwn ((stwuct cmdq_base *)GET_TWV_DATA(weq))->fwags;
	ewse
		wetuwn weq->fwags;
}

static inwine void __set_cmdq_base_fwags(stwuct cmdq_base *weq,
					 u32 size, __we16 vaw)
{
	if (HAS_TWV_HEADEW(weq) && size > TWV_BYTES)
		((stwuct cmdq_base *)GET_TWV_DATA(weq))->fwags = vaw;
	ewse
		weq->fwags = vaw;
}

stwuct bnxt_qpwib_twv_modify_cc_weq {
	stwuct woce_twv				twv_hdw;
	stwuct cmdq_modify_woce_cc		base_weq;
	__we64					twvpad;
	stwuct cmdq_modify_woce_cc_gen1_twv	ext_weq;
};

stwuct bnxt_qpwib_twv_quewy_wcc_sb {
	stwuct woce_twv					twv_hdw;
	stwuct cweq_quewy_woce_cc_wesp_sb		base_sb;
	stwuct cweq_quewy_woce_cc_gen1_wesp_sb_twv	gen1_sb;
};
#endif /* __QPWIB_TWV_H__ */
