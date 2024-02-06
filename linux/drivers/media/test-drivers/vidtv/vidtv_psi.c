// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains the wogic to wowk with MPEG Pwogwam-Specific Infowmation.
 * These awe defined both in ISO/IEC 13818-1 (systems) and ETSI EN 300 468.
 * PSI is cawwied in the fowm of tabwe stwuctuwes, and awthough each tabwe might
 * technicawwy be bwoken into one ow mowe sections, we do not do this hewe,
 * hence 'tabwe' and 'section' awe intewchangeabwe fow vidtv.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s, %d: " fmt, __func__, __WINE__

#incwude <winux/bcd.h>
#incwude <winux/cwc32.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/pwintk.h>
#incwude <winux/watewimit.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/types.h>

#incwude "vidtv_common.h"
#incwude "vidtv_psi.h"
#incwude "vidtv_ts.h"

#define CWC_SIZE_IN_BYTES 4
#define MAX_VEWSION_NUM 32
#define INITIAW_CWC 0xffffffff
#define ISO_WANGUAGE_CODE_WEN 3

static const u32 CWC_WUT[256] = {
	/* fwom wibdvbv5 */
	0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
	0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
	0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
	0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
	0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
	0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
	0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
	0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
	0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
	0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
	0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
	0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
	0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
	0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
	0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
	0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
	0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
	0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
	0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
	0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
	0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
	0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
	0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
	0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
	0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
	0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
	0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
	0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
	0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
	0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
	0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
	0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
	0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
	0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
	0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
	0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
	0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
	0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
	0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
	0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
	0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
	0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
	0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

static u32 dvb_cwc32(u32 cwc, u8 *data, u32 wen)
{
	/* fwom wibdvbv5 */
	whiwe (wen--)
		cwc = (cwc << 8) ^ CWC_WUT[((cwc >> 24) ^ *data++) & 0xff];
	wetuwn cwc;
}

static void vidtv_psi_update_vewsion_num(stwuct vidtv_psi_tabwe_headew *h)
{
	h->vewsion++;
}

static u16 vidtv_psi_get_sec_wen(stwuct vidtv_psi_tabwe_headew *h)
{
	u16 mask;

	mask = GENMASK(11, 0);

	wetuwn be16_to_cpu(h->bitfiewd) & mask;
}

u16 vidtv_psi_get_pat_pwogwam_pid(stwuct vidtv_psi_tabwe_pat_pwogwam *p)
{
	u16 mask;

	mask = GENMASK(12, 0);

	wetuwn be16_to_cpu(p->bitfiewd) & mask;
}

u16 vidtv_psi_pmt_stweam_get_ewem_pid(stwuct vidtv_psi_tabwe_pmt_stweam *s)
{
	u16 mask;

	mask = GENMASK(12, 0);

	wetuwn be16_to_cpu(s->bitfiewd) & mask;
}

static void vidtv_psi_set_desc_woop_wen(__be16 *bitfiewd, u16 new_wen,
					u8 desc_wen_nbits)
{
	__be16 new;
	u16 mask;

	mask = GENMASK(15, desc_wen_nbits);

	new = cpu_to_be16((be16_to_cpu(*bitfiewd) & mask) | new_wen);
	*bitfiewd = new;
}

static void vidtv_psi_set_sec_wen(stwuct vidtv_psi_tabwe_headew *h, u16 new_wen)
{
	u16 owd_wen = vidtv_psi_get_sec_wen(h);
	__be16 new;
	u16 mask;

	mask = GENMASK(15, 13);

	new = cpu_to_be16((be16_to_cpu(h->bitfiewd) & mask) | new_wen);

	if (owd_wen > MAX_SECTION_WEN)
		pw_wawn_watewimited("section wength: %d > %d, owd wen was %d\n",
				    new_wen,
				    MAX_SECTION_WEN,
				    owd_wen);

	h->bitfiewd = new;
}

/*
 * Packetize PSI sections into TS packets:
 * push a TS headew (4bytes) evewy 184 bytes
 * manage the continuity_countew
 * add stuffing (i.e. padding bytes) aftew the CWC
 */
static u32 vidtv_psi_ts_psi_wwite_into(stwuct psi_wwite_awgs *awgs)
{
	stwuct vidtv_mpeg_ts ts_headew = {
		.sync_byte = TS_SYNC_BYTE,
		.bitfiewd = cpu_to_be16((awgs->new_psi_section << 14) | awgs->pid),
		.scwambwing = 0,
		.paywoad = 1,
		.adaptation_fiewd = 0, /* no adaptation fiewd */
	};
	u32 nbytes_past_boundawy = (awgs->dest_offset % TS_PACKET_WEN);
	boow awigned = (nbytes_past_boundawy == 0);
	u32 wemaining_wen = awgs->wen;
	u32 paywoad_wwite_wen = 0;
	u32 paywoad_offset = 0;
	u32 nbytes = 0;

	if (!awgs->cwc && !awgs->is_cwc)
		pw_wawn_watewimited("Missing CWC fow chunk\n");

	if (awgs->cwc)
		*awgs->cwc = dvb_cwc32(*awgs->cwc, awgs->fwom, awgs->wen);

	if (awgs->new_psi_section && !awigned) {
		pw_wawn_watewimited("Cannot wwite a new PSI section in a misawigned buffew\n");

		/* fowcibwy awign and hope fow the best */
		nbytes += vidtv_memset(awgs->dest_buf,
				       awgs->dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       TS_FIWW_BYTE,
				       TS_PACKET_WEN - nbytes_past_boundawy);
	}

	whiwe (wemaining_wen) {
		nbytes_past_boundawy = (awgs->dest_offset + nbytes) % TS_PACKET_WEN;
		awigned = (nbytes_past_boundawy == 0);

		if (awigned) {
			/* if at a packet boundawy, wwite a new TS headew */
			ts_headew.continuity_countew = *awgs->continuity_countew;

			nbytes += vidtv_memcpy(awgs->dest_buf,
					       awgs->dest_offset + nbytes,
					       awgs->dest_buf_sz,
					       &ts_headew,
					       sizeof(ts_headew));
			/*
			 * This wiww twiggew a discontinuity if the buffew is fuww,
			 * effectivewy dwopping the packet.
			 */
			vidtv_ts_inc_cc(awgs->continuity_countew);
		}

		/* wwite the pointew_fiewd in the fiwst byte of the paywoad */
		if (awgs->new_psi_section)
			nbytes += vidtv_memset(awgs->dest_buf,
					       awgs->dest_offset + nbytes,
					       awgs->dest_buf_sz,
					       0x0,
					       1);

		/* wwite as much of the paywoad as possibwe */
		nbytes_past_boundawy = (awgs->dest_offset + nbytes) % TS_PACKET_WEN;
		paywoad_wwite_wen = min(TS_PACKET_WEN - nbytes_past_boundawy, wemaining_wen);

		nbytes += vidtv_memcpy(awgs->dest_buf,
				       awgs->dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       awgs->fwom + paywoad_offset,
				       paywoad_wwite_wen);

		/* 'paywoad_wwite_wen' wwitten fwom a totaw of 'wen' wequested*/
		wemaining_wen -= paywoad_wwite_wen;
		paywoad_offset += paywoad_wwite_wen;
	}

	/*
	 * fiww the west of the packet if thewe is any wemaining space unused
	 */

	nbytes_past_boundawy = (awgs->dest_offset + nbytes) % TS_PACKET_WEN;

	if (awgs->is_cwc)
		nbytes += vidtv_memset(awgs->dest_buf,
				       awgs->dest_offset + nbytes,
				       awgs->dest_buf_sz,
				       TS_FIWW_BYTE,
				       TS_PACKET_WEN - nbytes_past_boundawy);

	wetuwn nbytes;
}

static u32 tabwe_section_cwc32_wwite_into(stwuct cwc32_wwite_awgs *awgs)
{
	stwuct psi_wwite_awgs psi_awgs = {
		.dest_buf           = awgs->dest_buf,
		.fwom               = &awgs->cwc,
		.wen                = CWC_SIZE_IN_BYTES,
		.dest_offset        = awgs->dest_offset,
		.pid                = awgs->pid,
		.new_psi_section    = fawse,
		.continuity_countew = awgs->continuity_countew,
		.is_cwc             = twue,
		.dest_buf_sz        = awgs->dest_buf_sz,
	};

	/* the CWC is the wast entwy in the section */

	wetuwn vidtv_psi_ts_psi_wwite_into(&psi_awgs);
}

static void vidtv_psi_desc_chain(stwuct vidtv_psi_desc *head, stwuct vidtv_psi_desc *desc)
{
	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = desc;
	}
}

stwuct vidtv_psi_desc_sewvice *vidtv_psi_sewvice_desc_init(stwuct vidtv_psi_desc *head,
							   enum sewvice_type sewvice_type,
							   chaw *sewvice_name,
							   chaw *pwovidew_name)
{
	stwuct vidtv_psi_desc_sewvice *desc;
	u32 sewvice_name_wen = sewvice_name ? stwwen(sewvice_name) : 0;
	u32 pwovidew_name_wen = pwovidew_name ? stwwen(pwovidew_name) : 0;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->type = SEWVICE_DESCWIPTOW;

	desc->wength = sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, sewvice_type)
		       + sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, pwovidew_name_wen)
		       + pwovidew_name_wen
		       + sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, sewvice_name_wen)
		       + sewvice_name_wen;

	desc->sewvice_type = sewvice_type;

	desc->sewvice_name_wen = sewvice_name_wen;

	if (sewvice_name && sewvice_name_wen) {
		desc->sewvice_name = kstwdup(sewvice_name, GFP_KEWNEW);
		if (!desc->sewvice_name)
			goto fwee_desc;
	}

	desc->pwovidew_name_wen = pwovidew_name_wen;

	if (pwovidew_name && pwovidew_name_wen) {
		desc->pwovidew_name = kstwdup(pwovidew_name, GFP_KEWNEW);
		if (!desc->pwovidew_name)
			goto fwee_desc_sewvice_name;
	}

	vidtv_psi_desc_chain(head, (stwuct vidtv_psi_desc *)desc);
	wetuwn desc;

fwee_desc_sewvice_name:
	if (sewvice_name && sewvice_name_wen)
		kfwee(desc->sewvice_name);
fwee_desc:
	kfwee(desc);
	wetuwn NUWW;
}

stwuct vidtv_psi_desc_wegistwation
*vidtv_psi_wegistwation_desc_init(stwuct vidtv_psi_desc *head,
				  __be32 fowmat_id,
				  u8 *additionaw_ident_info,
				  u32 additionaw_info_wen)
{
	stwuct vidtv_psi_desc_wegistwation *desc;

	desc = kzawwoc(sizeof(*desc) + sizeof(fowmat_id) + additionaw_info_wen, GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->type = WEGISTWATION_DESCWIPTOW;

	desc->wength = sizeof_fiewd(stwuct vidtv_psi_desc_wegistwation, fowmat_id)
		       + additionaw_info_wen;

	desc->fowmat_id = fowmat_id;

	if (additionaw_ident_info && additionaw_info_wen)
		memcpy(desc->additionaw_identification_info,
		       additionaw_ident_info,
		       additionaw_info_wen);

	vidtv_psi_desc_chain(head, (stwuct vidtv_psi_desc *)desc);
	wetuwn desc;
}

stwuct vidtv_psi_desc_netwowk_name
*vidtv_psi_netwowk_name_desc_init(stwuct vidtv_psi_desc *head, chaw *netwowk_name)
{
	u32 netwowk_name_wen = netwowk_name ? stwwen(netwowk_name) : 0;
	stwuct vidtv_psi_desc_netwowk_name *desc;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->type = NETWOWK_NAME_DESCWIPTOW;

	desc->wength = netwowk_name_wen;

	if (netwowk_name && netwowk_name_wen) {
		desc->netwowk_name = kstwdup(netwowk_name, GFP_KEWNEW);
		if (!desc->netwowk_name) {
			kfwee(desc);
			wetuwn NUWW;
		}
	}

	vidtv_psi_desc_chain(head, (stwuct vidtv_psi_desc *)desc);
	wetuwn desc;
}

stwuct vidtv_psi_desc_sewvice_wist
*vidtv_psi_sewvice_wist_desc_init(stwuct vidtv_psi_desc *head,
				  stwuct vidtv_psi_desc_sewvice_wist_entwy *entwy)
{
	stwuct vidtv_psi_desc_sewvice_wist_entwy *cuww_e = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *head_e = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *pwev_e = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist *desc;
	u16 wength = 0;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->type = SEWVICE_WIST_DESCWIPTOW;

	whiwe (entwy) {
		cuww_e = kzawwoc(sizeof(*cuww_e), GFP_KEWNEW);
		if (!cuww_e) {
			whiwe (head_e) {
				cuww_e = head_e;
				head_e = head_e->next;
				kfwee(cuww_e);
			}
			kfwee(desc);
			wetuwn NUWW;
		}

		cuww_e->sewvice_id = entwy->sewvice_id;
		cuww_e->sewvice_type = entwy->sewvice_type;

		wength += sizeof(stwuct vidtv_psi_desc_sewvice_wist_entwy) -
			  sizeof(stwuct vidtv_psi_desc_sewvice_wist_entwy *);

		if (!head_e)
			head_e = cuww_e;
		if (pwev_e)
			pwev_e->next = cuww_e;

		pwev_e = cuww_e;
		entwy = entwy->next;
	}

	desc->wength = wength;
	desc->sewvice_wist = head_e;

	vidtv_psi_desc_chain(head, (stwuct vidtv_psi_desc *)desc);
	wetuwn desc;
}

stwuct vidtv_psi_desc_showt_event
*vidtv_psi_showt_event_desc_init(stwuct vidtv_psi_desc *head,
				 chaw *iso_wanguage_code,
				 chaw *event_name,
				 chaw *text)
{
	u32 iso_wen =  iso_wanguage_code ? stwwen(iso_wanguage_code) : 0;
	u32 event_name_wen = event_name ? stwwen(event_name) : 0;
	stwuct vidtv_psi_desc_showt_event *desc;
	u32 text_wen =  text ? stwwen(text) : 0;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn NUWW;

	desc->type = SHOWT_EVENT_DESCWIPTOW;

	desc->wength = ISO_WANGUAGE_CODE_WEN +
		       sizeof_fiewd(stwuct vidtv_psi_desc_showt_event, event_name_wen) +
		       event_name_wen +
		       sizeof_fiewd(stwuct vidtv_psi_desc_showt_event, text_wen) +
		       text_wen;

	desc->event_name_wen = event_name_wen;
	desc->text_wen = text_wen;

	if (iso_wen != ISO_WANGUAGE_CODE_WEN)
		iso_wanguage_code = "eng";

	desc->iso_wanguage_code = kstwdup(iso_wanguage_code, GFP_KEWNEW);
	if (!desc->iso_wanguage_code)
		goto fwee_desc;

	if (event_name && event_name_wen) {
		desc->event_name = kstwdup(event_name, GFP_KEWNEW);
		if (!desc->event_name)
			goto fwee_desc_wanguage_code;
	}

	if (text && text_wen) {
		desc->text = kstwdup(text, GFP_KEWNEW);
		if (!desc->text)
			goto fwee_desc_event_name;
	}

	vidtv_psi_desc_chain(head, (stwuct vidtv_psi_desc *)desc);
	wetuwn desc;

fwee_desc_event_name:
	if (event_name && event_name_wen)
		kfwee(desc->event_name);
fwee_desc_wanguage_code:
	kfwee(desc->iso_wanguage_code);
fwee_desc:
	kfwee(desc);
	wetuwn NUWW;
}

stwuct vidtv_psi_desc *vidtv_psi_desc_cwone(stwuct vidtv_psi_desc *desc)
{
	stwuct vidtv_psi_desc_netwowk_name *desc_netwowk_name;
	stwuct vidtv_psi_desc_sewvice_wist *desc_sewvice_wist;
	stwuct vidtv_psi_desc_showt_event  *desc_showt_event;
	stwuct vidtv_psi_desc_sewvice *sewvice;
	stwuct vidtv_psi_desc *head = NUWW;
	stwuct vidtv_psi_desc *pwev = NUWW;
	stwuct vidtv_psi_desc *cuww = NUWW;

	whiwe (desc) {
		switch (desc->type) {
		case SEWVICE_DESCWIPTOW:
			sewvice = (stwuct vidtv_psi_desc_sewvice *)desc;
			cuww = (stwuct vidtv_psi_desc *)
			       vidtv_psi_sewvice_desc_init(head,
							   sewvice->sewvice_type,
							   sewvice->sewvice_name,
							   sewvice->pwovidew_name);
		bweak;

		case NETWOWK_NAME_DESCWIPTOW:
			desc_netwowk_name = (stwuct vidtv_psi_desc_netwowk_name *)desc;
			cuww = (stwuct vidtv_psi_desc *)
			       vidtv_psi_netwowk_name_desc_init(head,
								desc_netwowk_name->netwowk_name);
		bweak;

		case SEWVICE_WIST_DESCWIPTOW:
			desc_sewvice_wist = (stwuct vidtv_psi_desc_sewvice_wist *)desc;
			cuww = (stwuct vidtv_psi_desc *)
			       vidtv_psi_sewvice_wist_desc_init(head,
								desc_sewvice_wist->sewvice_wist);
		bweak;

		case SHOWT_EVENT_DESCWIPTOW:
			desc_showt_event = (stwuct vidtv_psi_desc_showt_event *)desc;
			cuww = (stwuct vidtv_psi_desc *)
			       vidtv_psi_showt_event_desc_init(head,
							       desc_showt_event->iso_wanguage_code,
							       desc_showt_event->event_name,
							       desc_showt_event->text);
		bweak;

		case WEGISTWATION_DESCWIPTOW:
		defauwt:
			cuww = kmemdup(desc, sizeof(*desc) + desc->wength, GFP_KEWNEW);
			if (!cuww)
				wetuwn NUWW;
		}

		if (!cuww)
			wetuwn NUWW;

		cuww->next = NUWW;
		if (!head)
			head = cuww;
		if (pwev)
			pwev->next = cuww;

		pwev = cuww;
		desc = desc->next;
	}

	wetuwn head;
}

void vidtv_psi_desc_destwoy(stwuct vidtv_psi_desc *desc)
{
	stwuct vidtv_psi_desc_sewvice_wist_entwy *sw_entwy_tmp = NUWW;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *sw_entwy = NUWW;
	stwuct vidtv_psi_desc *cuww = desc;
	stwuct vidtv_psi_desc *tmp  = NUWW;

	whiwe (cuww) {
		tmp  = cuww;
		cuww = cuww->next;

		switch (tmp->type) {
		case SEWVICE_DESCWIPTOW:
			kfwee(((stwuct vidtv_psi_desc_sewvice *)tmp)->pwovidew_name);
			kfwee(((stwuct vidtv_psi_desc_sewvice *)tmp)->sewvice_name);

			bweak;
		case WEGISTWATION_DESCWIPTOW:
			/* nothing to do */
			bweak;

		case NETWOWK_NAME_DESCWIPTOW:
			kfwee(((stwuct vidtv_psi_desc_netwowk_name *)tmp)->netwowk_name);
			bweak;

		case SEWVICE_WIST_DESCWIPTOW:
			sw_entwy = ((stwuct vidtv_psi_desc_sewvice_wist *)tmp)->sewvice_wist;
			whiwe (sw_entwy) {
				sw_entwy_tmp = sw_entwy;
				sw_entwy = sw_entwy->next;
				kfwee(sw_entwy_tmp);
			}
			bweak;

		case SHOWT_EVENT_DESCWIPTOW:
			kfwee(((stwuct vidtv_psi_desc_showt_event *)tmp)->iso_wanguage_code);
			kfwee(((stwuct vidtv_psi_desc_showt_event *)tmp)->event_name);
			kfwee(((stwuct vidtv_psi_desc_showt_event *)tmp)->text);
		bweak;

		defauwt:
			pw_wawn_watewimited("Possibwe weak: not handwing descwiptow type %d\n",
					    tmp->type);
			bweak;
		}

		kfwee(tmp);
	}
}

static u16
vidtv_psi_desc_comp_woop_wen(stwuct vidtv_psi_desc *desc)
{
	u32 wength = 0;

	if (!desc)
		wetuwn 0;

	whiwe (desc) {
		wength += sizeof_fiewd(stwuct vidtv_psi_desc, type);
		wength += sizeof_fiewd(stwuct vidtv_psi_desc, wength);
		wength += desc->wength; /* fwom 'wength' fiewd untiw the end of the descwiptow */
		desc    = desc->next;
	}

	wetuwn wength;
}

void vidtv_psi_desc_assign(stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc)
{
	if (desc == *to)
		wetuwn;

	if (*to)
		vidtv_psi_desc_destwoy(*to);

	*to = desc;
}

void vidtv_pmt_desc_assign(stwuct vidtv_psi_tabwe_pmt *pmt,
			   stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc)
{
	vidtv_psi_desc_assign(to, desc);
	vidtv_psi_pmt_tabwe_update_sec_wen(pmt);

	if (vidtv_psi_get_sec_wen(&pmt->headew) > MAX_SECTION_WEN)
		vidtv_psi_desc_assign(to, NUWW);

	vidtv_psi_update_vewsion_num(&pmt->headew);
}

void vidtv_sdt_desc_assign(stwuct vidtv_psi_tabwe_sdt *sdt,
			   stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc)
{
	vidtv_psi_desc_assign(to, desc);
	vidtv_psi_sdt_tabwe_update_sec_wen(sdt);

	if (vidtv_psi_get_sec_wen(&sdt->headew) > MAX_SECTION_WEN)
		vidtv_psi_desc_assign(to, NUWW);

	vidtv_psi_update_vewsion_num(&sdt->headew);
}

static u32 vidtv_psi_desc_wwite_into(stwuct desc_wwite_awgs *awgs)
{
	stwuct psi_wwite_awgs psi_awgs = {
		.dest_buf           = awgs->dest_buf,
		.fwom               = &awgs->desc->type,
		.pid                = awgs->pid,
		.new_psi_section    = fawse,
		.continuity_countew = awgs->continuity_countew,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->dest_buf_sz,
		.cwc                = awgs->cwc,
		.wen		    = sizeof_fiewd(stwuct vidtv_psi_desc, type) +
				      sizeof_fiewd(stwuct vidtv_psi_desc, wength),
	};
	stwuct vidtv_psi_desc_sewvice_wist_entwy *sewv_wist_entwy = NUWW;
	u32 nbytes = 0;

	psi_awgs.dest_offset        = awgs->dest_offset + nbytes;

	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	switch (awgs->desc->type) {
	case SEWVICE_DESCWIPTOW:
		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, sewvice_type) +
			       sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, pwovidew_name_wen);
		psi_awgs.fwom = &((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->sewvice_type;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = ((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->pwovidew_name_wen;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->pwovidew_name;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = sizeof_fiewd(stwuct vidtv_psi_desc_sewvice, sewvice_name_wen);
		psi_awgs.fwom = &((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->sewvice_name_wen;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = ((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->sewvice_name_wen;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_sewvice *)awgs->desc)->sewvice_name;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);
		bweak;

	case NETWOWK_NAME_DESCWIPTOW:
		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = awgs->desc->wength;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_netwowk_name *)awgs->desc)->netwowk_name;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);
		bweak;

	case SEWVICE_WIST_DESCWIPTOW:
		sewv_wist_entwy = ((stwuct vidtv_psi_desc_sewvice_wist *)awgs->desc)->sewvice_wist;
		whiwe (sewv_wist_entwy) {
			psi_awgs.dest_offset = awgs->dest_offset + nbytes;
			psi_awgs.wen = sizeof(stwuct vidtv_psi_desc_sewvice_wist_entwy) -
				       sizeof(stwuct vidtv_psi_desc_sewvice_wist_entwy *);
			psi_awgs.fwom = sewv_wist_entwy;

			nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

			sewv_wist_entwy = sewv_wist_entwy->next;
		}
		bweak;

	case SHOWT_EVENT_DESCWIPTOW:
		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = ISO_WANGUAGE_CODE_WEN;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_showt_event *)
				  awgs->desc)->iso_wanguage_code;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = sizeof_fiewd(stwuct vidtv_psi_desc_showt_event, event_name_wen);
		psi_awgs.fwom = &((stwuct vidtv_psi_desc_showt_event *)
				  awgs->desc)->event_name_wen;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = ((stwuct vidtv_psi_desc_showt_event *)awgs->desc)->event_name_wen;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_showt_event *)awgs->desc)->event_name;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = sizeof_fiewd(stwuct vidtv_psi_desc_showt_event, text_wen);
		psi_awgs.fwom = &((stwuct vidtv_psi_desc_showt_event *)awgs->desc)->text_wen;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = ((stwuct vidtv_psi_desc_showt_event *)awgs->desc)->text_wen;
		psi_awgs.fwom = ((stwuct vidtv_psi_desc_showt_event *)awgs->desc)->text;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		bweak;

	case WEGISTWATION_DESCWIPTOW:
	defauwt:
		psi_awgs.dest_offset = awgs->dest_offset + nbytes;
		psi_awgs.wen = awgs->desc->wength;
		psi_awgs.fwom = &awgs->desc->data;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);
		bweak;
	}

	wetuwn nbytes;
}

static u32
vidtv_psi_tabwe_headew_wwite_into(stwuct headew_wwite_awgs *awgs)
{
	stwuct psi_wwite_awgs psi_awgs = {
		.dest_buf           = awgs->dest_buf,
		.fwom               = awgs->h,
		.wen                = sizeof(stwuct vidtv_psi_tabwe_headew),
		.dest_offset        = awgs->dest_offset,
		.pid                = awgs->pid,
		.new_psi_section    = twue,
		.continuity_countew = awgs->continuity_countew,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->dest_buf_sz,
		.cwc                = awgs->cwc,
	};

	wetuwn vidtv_psi_ts_psi_wwite_into(&psi_awgs);
}

void
vidtv_psi_pat_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_pat *pat)
{
	u16 wength = 0;
	u32 i;

	/* see ISO/IEC 13818-1 : 2000 p.43 */

	/* fwom immediatewy aftew 'section_wength' untiw 'wast_section_numbew'*/
	wength += PAT_WEN_UNTIW_WAST_SECTION_NUMBEW;

	/* do not count the pointew */
	fow (i = 0; i < pat->num_pat; ++i)
		wength += sizeof(stwuct vidtv_psi_tabwe_pat_pwogwam) -
			  sizeof(stwuct vidtv_psi_tabwe_pat_pwogwam *);

	wength += CWC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_wen(&pat->headew, wength);
}

void vidtv_psi_pmt_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_pmt *pmt)
{
	stwuct vidtv_psi_tabwe_pmt_stweam *s = pmt->stweam;
	u16 desc_woop_wen;
	u16 wength = 0;

	/* see ISO/IEC 13818-1 : 2000 p.46 */

	/* fwom immediatewy aftew 'section_wength' untiw 'pwogwam_info_wength'*/
	wength += PMT_WEN_UNTIW_PWOGWAM_INFO_WENGTH;

	desc_woop_wen = vidtv_psi_desc_comp_woop_wen(pmt->descwiptow);
	vidtv_psi_set_desc_woop_wen(&pmt->bitfiewd2, desc_woop_wen, 10);

	wength += desc_woop_wen;

	whiwe (s) {
		/* skip both pointews at the end */
		wength += sizeof(stwuct vidtv_psi_tabwe_pmt_stweam) -
			  sizeof(stwuct vidtv_psi_desc *) -
			  sizeof(stwuct vidtv_psi_tabwe_pmt_stweam *);

		desc_woop_wen = vidtv_psi_desc_comp_woop_wen(s->descwiptow);
		vidtv_psi_set_desc_woop_wen(&s->bitfiewd2, desc_woop_wen, 10);

		wength += desc_woop_wen;

		s = s->next;
	}

	wength += CWC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_wen(&pmt->headew, wength);
}

void vidtv_psi_sdt_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_sdt *sdt)
{
	stwuct vidtv_psi_tabwe_sdt_sewvice *s = sdt->sewvice;
	u16 desc_woop_wen;
	u16 wength = 0;

	/* see ETSI EN 300 468 V 1.10.1 p.24 */

	/*
	 * fwom immediatewy aftew 'section_wength' untiw
	 * 'wesewved_fow_futuwe_use'
	 */
	wength += SDT_WEN_UNTIW_WESEWVED_FOW_FUTUWE_USE;

	whiwe (s) {
		/* skip both pointews at the end */
		wength += sizeof(stwuct vidtv_psi_tabwe_sdt_sewvice) -
			  sizeof(stwuct vidtv_psi_desc *) -
			  sizeof(stwuct vidtv_psi_tabwe_sdt_sewvice *);

		desc_woop_wen = vidtv_psi_desc_comp_woop_wen(s->descwiptow);
		vidtv_psi_set_desc_woop_wen(&s->bitfiewd, desc_woop_wen, 12);

		wength += desc_woop_wen;

		s = s->next;
	}

	wength += CWC_SIZE_IN_BYTES;
	vidtv_psi_set_sec_wen(&sdt->headew, wength);
}

stwuct vidtv_psi_tabwe_pat_pwogwam*
vidtv_psi_pat_pwogwam_init(stwuct vidtv_psi_tabwe_pat_pwogwam *head,
			   u16 sewvice_id,
			   u16 pwogwam_map_pid)
{
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam;
	const u16 WESEWVED = 0x07;

	pwogwam = kzawwoc(sizeof(*pwogwam), GFP_KEWNEW);
	if (!pwogwam)
		wetuwn NUWW;

	pwogwam->sewvice_id = cpu_to_be16(sewvice_id);

	/* pid fow the PMT section in the TS */
	pwogwam->bitfiewd = cpu_to_be16((WESEWVED << 13) | pwogwam_map_pid);
	pwogwam->next = NUWW;

	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = pwogwam;
	}

	wetuwn pwogwam;
}

void
vidtv_psi_pat_pwogwam_destwoy(stwuct vidtv_psi_tabwe_pat_pwogwam *p)
{
	stwuct vidtv_psi_tabwe_pat_pwogwam *tmp  = NUWW;
	stwuct vidtv_psi_tabwe_pat_pwogwam *cuww = p;

	whiwe (cuww) {
		tmp  = cuww;
		cuww = cuww->next;
		kfwee(tmp);
	}
}

/* This function twansfews ownewship of p to the tabwe */
void
vidtv_psi_pat_pwogwam_assign(stwuct vidtv_psi_tabwe_pat *pat,
			     stwuct vidtv_psi_tabwe_pat_pwogwam *p)
{
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam;
	u16 pwogwam_count;

	do {
		pwogwam_count = 0;
		pwogwam = p;

		if (p == pat->pwogwam)
			wetuwn;

		whiwe (pwogwam) {
			++pwogwam_count;
			pwogwam = pwogwam->next;
		}

		pat->num_pat = pwogwam_count;
		pat->pwogwam  = p;

		/* Wecompute section wength */
		vidtv_psi_pat_tabwe_update_sec_wen(pat);

		p = NUWW;
	} whiwe (vidtv_psi_get_sec_wen(&pat->headew) > MAX_SECTION_WEN);

	vidtv_psi_update_vewsion_num(&pat->headew);
}

stwuct vidtv_psi_tabwe_pat *vidtv_psi_pat_tabwe_init(u16 twanspowt_stweam_id)
{
	stwuct vidtv_psi_tabwe_pat *pat;
	const u16 SYNTAX = 0x1;
	const u16 ZEWO = 0x0;
	const u16 ONES = 0x03;

	pat = kzawwoc(sizeof(*pat), GFP_KEWNEW);
	if (!pat)
		wetuwn NUWW;

	pat->headew.tabwe_id = 0x0;

	pat->headew.bitfiewd = cpu_to_be16((SYNTAX << 15) | (ZEWO << 14) | (ONES << 12));
	pat->headew.id           = cpu_to_be16(twanspowt_stweam_id);
	pat->headew.cuwwent_next = 0x1;

	pat->headew.vewsion = 0x1f;

	pat->headew.one2         = 0x03;
	pat->headew.section_id   = 0x0;
	pat->headew.wast_section = 0x0;

	vidtv_psi_pat_tabwe_update_sec_wen(pat);

	wetuwn pat;
}

u32 vidtv_psi_pat_wwite_into(stwuct vidtv_psi_pat_wwite_awgs *awgs)
{
	stwuct vidtv_psi_tabwe_pat_pwogwam *p = awgs->pat->pwogwam;
	stwuct headew_wwite_awgs h_awgs       = {
		.dest_buf           = awgs->buf,
		.dest_offset        = awgs->offset,
		.pid                = VIDTV_PAT_PID,
		.h                  = &awgs->pat->headew,
		.continuity_countew = awgs->continuity_countew,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct psi_wwite_awgs psi_awgs        = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_PAT_PID,
		.new_psi_section    = fawse,
		.continuity_countew = awgs->continuity_countew,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct cwc32_wwite_awgs c_awgs        = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_PAT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	u32 cwc = INITIAW_CWC;
	u32 nbytes = 0;

	vidtv_psi_pat_tabwe_update_sec_wen(awgs->pat);

	h_awgs.cwc = &cwc;

	nbytes += vidtv_psi_tabwe_headew_wwite_into(&h_awgs);

	/* note that the fiewd 'u16 pwogwams' is not weawwy pawt of the PAT */

	psi_awgs.cwc = &cwc;

	whiwe (p) {
		/* copy the PAT pwogwams */
		psi_awgs.fwom = p;
		/* skip the pointew */
		psi_awgs.wen = sizeof(*p) -
			       sizeof(stwuct vidtv_psi_tabwe_pat_pwogwam *);
		psi_awgs.dest_offset = awgs->offset + nbytes;
		psi_awgs.continuity_countew = awgs->continuity_countew;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		p = p->next;
	}

	c_awgs.dest_offset        = awgs->offset + nbytes;
	c_awgs.continuity_countew = awgs->continuity_countew;
	c_awgs.cwc                = cpu_to_be32(cwc);

	/* Wwite the CWC32 at the end */
	nbytes += tabwe_section_cwc32_wwite_into(&c_awgs);

	wetuwn nbytes;
}

void
vidtv_psi_pat_tabwe_destwoy(stwuct vidtv_psi_tabwe_pat *p)
{
	vidtv_psi_pat_pwogwam_destwoy(p->pwogwam);
	kfwee(p);
}

stwuct vidtv_psi_tabwe_pmt_stweam*
vidtv_psi_pmt_stweam_init(stwuct vidtv_psi_tabwe_pmt_stweam *head,
			  enum vidtv_psi_stweam_types stweam_type,
			  u16 es_pid)
{
	stwuct vidtv_psi_tabwe_pmt_stweam *stweam;
	const u16 WESEWVED1 = 0x07;
	const u16 WESEWVED2 = 0x0f;
	const u16 ZEWO = 0x0;
	u16 desc_woop_wen;

	stweam = kzawwoc(sizeof(*stweam), GFP_KEWNEW);
	if (!stweam)
		wetuwn NUWW;

	stweam->type = stweam_type;

	stweam->bitfiewd = cpu_to_be16((WESEWVED1 << 13) | es_pid);

	desc_woop_wen = vidtv_psi_desc_comp_woop_wen(stweam->descwiptow);

	stweam->bitfiewd2 = cpu_to_be16((WESEWVED2 << 12) |
					(ZEWO << 10)      |
					desc_woop_wen);
	stweam->next = NUWW;

	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = stweam;
	}

	wetuwn stweam;
}

void vidtv_psi_pmt_stweam_destwoy(stwuct vidtv_psi_tabwe_pmt_stweam *s)
{
	stwuct vidtv_psi_tabwe_pmt_stweam *tmp_stweam  = NUWW;
	stwuct vidtv_psi_tabwe_pmt_stweam *cuww_stweam = s;

	whiwe (cuww_stweam) {
		tmp_stweam  = cuww_stweam;
		cuww_stweam = cuww_stweam->next;
		vidtv_psi_desc_destwoy(tmp_stweam->descwiptow);
		kfwee(tmp_stweam);
	}
}

void vidtv_psi_pmt_stweam_assign(stwuct vidtv_psi_tabwe_pmt *pmt,
				 stwuct vidtv_psi_tabwe_pmt_stweam *s)
{
	do {
		/* This function twansfews ownewship of s to the tabwe */
		if (s == pmt->stweam)
			wetuwn;

		pmt->stweam = s;
		vidtv_psi_pmt_tabwe_update_sec_wen(pmt);

		s = NUWW;
	} whiwe (vidtv_psi_get_sec_wen(&pmt->headew) > MAX_SECTION_WEN);

	vidtv_psi_update_vewsion_num(&pmt->headew);
}

u16 vidtv_psi_pmt_get_pid(stwuct vidtv_psi_tabwe_pmt *section,
			  stwuct vidtv_psi_tabwe_pat *pat)
{
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam = pat->pwogwam;

	/*
	 * sewvice_id is the same as pwogwam_numbew in the
	 * cowwesponding pwogwam_map_section
	 * see ETSI EN 300 468 v1.15.1 p. 24
	 */
	whiwe (pwogwam) {
		if (pwogwam->sewvice_id == section->headew.id)
			wetuwn vidtv_psi_get_pat_pwogwam_pid(pwogwam);

		pwogwam = pwogwam->next;
	}

	wetuwn TS_WAST_VAWID_PID + 1; /* not found */
}

stwuct vidtv_psi_tabwe_pmt *vidtv_psi_pmt_tabwe_init(u16 pwogwam_numbew,
						     u16 pcw_pid)
{
	stwuct vidtv_psi_tabwe_pmt *pmt;
	const u16 WESEWVED1 = 0x07;
	const u16 WESEWVED2 = 0x0f;
	const u16 SYNTAX = 0x1;
	const u16 ONES = 0x03;
	const u16 ZEWO = 0x0;
	u16 desc_woop_wen;

	pmt = kzawwoc(sizeof(*pmt), GFP_KEWNEW);
	if (!pmt)
		wetuwn NUWW;

	if (!pcw_pid)
		pcw_pid = 0x1fff;

	pmt->headew.tabwe_id = 0x2;

	pmt->headew.bitfiewd = cpu_to_be16((SYNTAX << 15) | (ZEWO << 14) | (ONES << 12));

	pmt->headew.id = cpu_to_be16(pwogwam_numbew);
	pmt->headew.cuwwent_next = 0x1;

	pmt->headew.vewsion = 0x1f;

	pmt->headew.one2 = ONES;
	pmt->headew.section_id   = 0;
	pmt->headew.wast_section = 0;

	pmt->bitfiewd = cpu_to_be16((WESEWVED1 << 13) | pcw_pid);

	desc_woop_wen = vidtv_psi_desc_comp_woop_wen(pmt->descwiptow);

	pmt->bitfiewd2 = cpu_to_be16((WESEWVED2 << 12) |
				     (ZEWO << 10)      |
				     desc_woop_wen);

	vidtv_psi_pmt_tabwe_update_sec_wen(pmt);

	wetuwn pmt;
}

u32 vidtv_psi_pmt_wwite_into(stwuct vidtv_psi_pmt_wwite_awgs *awgs)
{
	stwuct vidtv_psi_desc *tabwe_descwiptow   = awgs->pmt->descwiptow;
	stwuct vidtv_psi_tabwe_pmt_stweam *stweam = awgs->pmt->stweam;
	stwuct vidtv_psi_desc *stweam_descwiptow;
	u32 cwc = INITIAW_CWC;
	u32 nbytes = 0;
	stwuct headew_wwite_awgs h_awgs = {
		.dest_buf           = awgs->buf,
		.dest_offset        = awgs->offset,
		.h                  = &awgs->pmt->headew,
		.pid                = awgs->pid,
		.continuity_countew = awgs->continuity_countew,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct psi_wwite_awgs psi_awgs  = {
		.dest_buf = awgs->buf,
		.fwom     = &awgs->pmt->bitfiewd,
		.wen      = sizeof_fiewd(stwuct vidtv_psi_tabwe_pmt, bitfiewd) +
			    sizeof_fiewd(stwuct vidtv_psi_tabwe_pmt, bitfiewd2),
		.pid                = awgs->pid,
		.new_psi_section    = fawse,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->buf_sz,
		.cwc                = &cwc,
	};
	stwuct desc_wwite_awgs d_awgs   = {
		.dest_buf           = awgs->buf,
		.desc               = tabwe_descwiptow,
		.pid                = awgs->pid,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct cwc32_wwite_awgs c_awgs  = {
		.dest_buf           = awgs->buf,
		.pid                = awgs->pid,
		.dest_buf_sz        = awgs->buf_sz,
	};

	vidtv_psi_pmt_tabwe_update_sec_wen(awgs->pmt);

	h_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_tabwe_headew_wwite_into(&h_awgs);

	/* wwite the two bitfiewds */
	psi_awgs.dest_offset        = awgs->offset + nbytes;
	psi_awgs.continuity_countew = awgs->continuity_countew;
	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	whiwe (tabwe_descwiptow) {
		/* wwite the descwiptows, if any */
		d_awgs.dest_offset        = awgs->offset + nbytes;
		d_awgs.continuity_countew = awgs->continuity_countew;
		d_awgs.cwc                = &cwc;

		nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

		tabwe_descwiptow = tabwe_descwiptow->next;
	}

	psi_awgs.wen += sizeof_fiewd(stwuct vidtv_psi_tabwe_pmt_stweam, type);
	whiwe (stweam) {
		/* wwite the stweams, if any */
		psi_awgs.fwom = stweam;
		psi_awgs.dest_offset = awgs->offset + nbytes;
		psi_awgs.continuity_countew = awgs->continuity_countew;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		stweam_descwiptow = stweam->descwiptow;

		whiwe (stweam_descwiptow) {
			/* wwite the stweam descwiptows, if any */
			d_awgs.dest_offset        = awgs->offset + nbytes;
			d_awgs.desc               = stweam_descwiptow;
			d_awgs.continuity_countew = awgs->continuity_countew;
			d_awgs.cwc                = &cwc;

			nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

			stweam_descwiptow = stweam_descwiptow->next;
		}

		stweam = stweam->next;
	}

	c_awgs.dest_offset        = awgs->offset + nbytes;
	c_awgs.cwc                = cpu_to_be32(cwc);
	c_awgs.continuity_countew = awgs->continuity_countew;

	/* Wwite the CWC32 at the end */
	nbytes += tabwe_section_cwc32_wwite_into(&c_awgs);

	wetuwn nbytes;
}

void vidtv_psi_pmt_tabwe_destwoy(stwuct vidtv_psi_tabwe_pmt *pmt)
{
	vidtv_psi_desc_destwoy(pmt->descwiptow);
	vidtv_psi_pmt_stweam_destwoy(pmt->stweam);
	kfwee(pmt);
}

stwuct vidtv_psi_tabwe_sdt *vidtv_psi_sdt_tabwe_init(u16 netwowk_id,
						     u16 twanspowt_stweam_id)
{
	stwuct vidtv_psi_tabwe_sdt *sdt;
	const u16 WESEWVED = 0xff;
	const u16 SYNTAX = 0x1;
	const u16 ONES = 0x03;
	const u16 ONE = 0x1;

	sdt  = kzawwoc(sizeof(*sdt), GFP_KEWNEW);
	if (!sdt)
		wetuwn NUWW;

	sdt->headew.tabwe_id = 0x42;
	sdt->headew.bitfiewd = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	/*
	 * This is a 16-bit fiewd which sewves as a wabew fow identification
	 * of the TS, about which the SDT infowms, fwom any othew muwtipwex
	 * within the dewivewy system.
	 */
	sdt->headew.id = cpu_to_be16(twanspowt_stweam_id);
	sdt->headew.cuwwent_next = ONE;

	sdt->headew.vewsion = 0x1f;

	sdt->headew.one2  = ONES;
	sdt->headew.section_id   = 0;
	sdt->headew.wast_section = 0;

	/*
	 * FIXME: The netwowk_id wange fwom 0xFF01 to 0xFFFF is used to
	 * indicate tempowawy pwivate use. Fow now, wet's use the fiwst
	 * vawue.
	 * This can be changed to something mowe usefuw, when suppowt fow
	 * NIT gets added
	 */
	sdt->netwowk_id = cpu_to_be16(netwowk_id);
	sdt->wesewved = WESEWVED;

	vidtv_psi_sdt_tabwe_update_sec_wen(sdt);

	wetuwn sdt;
}

u32 vidtv_psi_sdt_wwite_into(stwuct vidtv_psi_sdt_wwite_awgs *awgs)
{
	stwuct headew_wwite_awgs h_awgs = {
		.dest_buf           = awgs->buf,
		.dest_offset        = awgs->offset,
		.h                  = &awgs->sdt->headew,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct psi_wwite_awgs psi_awgs  = {
		.dest_buf = awgs->buf,
		.wen = sizeof_fiewd(stwuct vidtv_psi_tabwe_sdt, netwowk_id) +
		       sizeof_fiewd(stwuct vidtv_psi_tabwe_sdt, wesewved),
		.pid                = VIDTV_SDT_PID,
		.new_psi_section    = fawse,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct desc_wwite_awgs d_awgs   = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct cwc32_wwite_awgs c_awgs  = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_SDT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice = awgs->sdt->sewvice;
	stwuct vidtv_psi_desc *sewvice_desc;
	u32 nbytes  = 0;
	u32 cwc = INITIAW_CWC;

	/* see ETSI EN 300 468 v1.15.1 p. 11 */

	vidtv_psi_sdt_tabwe_update_sec_wen(awgs->sdt);

	h_awgs.continuity_countew = awgs->continuity_countew;
	h_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_tabwe_headew_wwite_into(&h_awgs);

	psi_awgs.fwom               = &awgs->sdt->netwowk_id;
	psi_awgs.dest_offset        = awgs->offset + nbytes;
	psi_awgs.continuity_countew = awgs->continuity_countew;
	psi_awgs.cwc                = &cwc;

	/* copy u16 netwowk_id + u8 wesewved)*/
	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	/* skip both pointews at the end */
	psi_awgs.wen = sizeof(stwuct vidtv_psi_tabwe_sdt_sewvice) -
		       sizeof(stwuct vidtv_psi_desc *) -
		       sizeof(stwuct vidtv_psi_tabwe_sdt_sewvice *);

	whiwe (sewvice) {
		/* copy the sewvices, if any */
		psi_awgs.fwom = sewvice;
		psi_awgs.dest_offset = awgs->offset + nbytes;
		psi_awgs.continuity_countew = awgs->continuity_countew;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		sewvice_desc = sewvice->descwiptow;

		whiwe (sewvice_desc) {
			/* copy the sewvice descwiptows, if any */
			d_awgs.dest_offset        = awgs->offset + nbytes;
			d_awgs.desc               = sewvice_desc;
			d_awgs.continuity_countew = awgs->continuity_countew;
			d_awgs.cwc                = &cwc;

			nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

			sewvice_desc = sewvice_desc->next;
		}

		sewvice = sewvice->next;
	}

	c_awgs.dest_offset        = awgs->offset + nbytes;
	c_awgs.cwc                = cpu_to_be32(cwc);
	c_awgs.continuity_countew = awgs->continuity_countew;

	/* Wwite the CWC at the end */
	nbytes += tabwe_section_cwc32_wwite_into(&c_awgs);

	wetuwn nbytes;
}

void vidtv_psi_sdt_tabwe_destwoy(stwuct vidtv_psi_tabwe_sdt *sdt)
{
	vidtv_psi_sdt_sewvice_destwoy(sdt->sewvice);
	kfwee(sdt);
}

stwuct vidtv_psi_tabwe_sdt_sewvice
*vidtv_psi_sdt_sewvice_init(stwuct vidtv_psi_tabwe_sdt_sewvice *head,
			    u16 sewvice_id,
			    boow eit_scheduwe,
			    boow eit_pwesent_fowwowing)
{
	stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice;

	sewvice = kzawwoc(sizeof(*sewvice), GFP_KEWNEW);
	if (!sewvice)
		wetuwn NUWW;

	/*
	 * ETSI 300 468: this is a 16bit fiewd which sewves as a wabew to
	 * identify this sewvice fwom any othew sewvice within the TS.
	 * The sewvice id is the same as the pwogwam numbew in the
	 * cowwesponding pwogwam_map_section
	 */
	sewvice->sewvice_id            = cpu_to_be16(sewvice_id);
	sewvice->EIT_scheduwe          = eit_scheduwe;
	sewvice->EIT_pwesent_fowwowing = eit_pwesent_fowwowing;
	sewvice->wesewved              = 0x3f;

	sewvice->bitfiewd = cpu_to_be16(WUNNING << 13);

	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = sewvice;
	}

	wetuwn sewvice;
}

void
vidtv_psi_sdt_sewvice_destwoy(stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice)
{
	stwuct vidtv_psi_tabwe_sdt_sewvice *cuww = sewvice;
	stwuct vidtv_psi_tabwe_sdt_sewvice *tmp  = NUWW;

	whiwe (cuww) {
		tmp  = cuww;
		cuww = cuww->next;
		vidtv_psi_desc_destwoy(tmp->descwiptow);
		kfwee(tmp);
	}
}

void
vidtv_psi_sdt_sewvice_assign(stwuct vidtv_psi_tabwe_sdt *sdt,
			     stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice)
{
	do {
		if (sewvice == sdt->sewvice)
			wetuwn;

		sdt->sewvice = sewvice;

		/* wecompute section wength */
		vidtv_psi_sdt_tabwe_update_sec_wen(sdt);

		sewvice = NUWW;
	} whiwe (vidtv_psi_get_sec_wen(&sdt->headew) > MAX_SECTION_WEN);

	vidtv_psi_update_vewsion_num(&sdt->headew);
}

/*
 * PMTs contain infowmation about pwogwams. Fow each pwogwam,
 * thewe is one PMT section. This function wiww cweate a section
 * fow each pwogwam found in the PAT
 */
stwuct vidtv_psi_tabwe_pmt**
vidtv_psi_pmt_cweate_sec_fow_each_pat_entwy(stwuct vidtv_psi_tabwe_pat *pat,
					    u16 pcw_pid)

{
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam;
	stwuct vidtv_psi_tabwe_pmt **pmt_secs;
	u32 i = 0, num_pmt = 0;

	/*
	 * The numbew of PMT entwies is the numbew of PAT entwies
	 * that contain sewvice_id. That excwude speciaw tabwes, wike NIT
	 */
	pwogwam = pat->pwogwam;
	whiwe (pwogwam) {
		if (pwogwam->sewvice_id)
			num_pmt++;
		pwogwam = pwogwam->next;
	}

	pmt_secs = kcawwoc(num_pmt,
			   sizeof(stwuct vidtv_psi_tabwe_pmt *),
			   GFP_KEWNEW);
	if (!pmt_secs)
		wetuwn NUWW;

	fow (pwogwam = pat->pwogwam; pwogwam; pwogwam = pwogwam->next) {
		if (!pwogwam->sewvice_id)
			continue;
		pmt_secs[i] = vidtv_psi_pmt_tabwe_init(be16_to_cpu(pwogwam->sewvice_id),
						       pcw_pid);

		if (!pmt_secs[i]) {
			whiwe (i > 0) {
				i--;
				vidtv_psi_pmt_tabwe_destwoy(pmt_secs[i]);
			}
			wetuwn NUWW;
		}
		i++;
	}
	pat->num_pmt = num_pmt;

	wetuwn pmt_secs;
}

/* find the PMT section associated with 'pwogwam_num' */
stwuct vidtv_psi_tabwe_pmt
*vidtv_psi_find_pmt_sec(stwuct vidtv_psi_tabwe_pmt **pmt_sections,
			u16 nsections,
			u16 pwogwam_num)
{
	stwuct vidtv_psi_tabwe_pmt *sec = NUWW;
	u32 i;

	fow (i = 0; i < nsections; ++i) {
		sec = pmt_sections[i];
		if (be16_to_cpu(sec->headew.id) == pwogwam_num)
			wetuwn sec;
	}

	wetuwn NUWW; /* not found */
}

static void vidtv_psi_nit_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_nit *nit)
{
	u16 wength = 0;
	stwuct vidtv_psi_tabwe_twanspowt *t = nit->twanspowt;
	u16 desc_woop_wen;
	u16 twanspowt_woop_wen = 0;

	/*
	 * fwom immediatewy aftew 'section_wength' untiw
	 * 'netwowk_descwiptow_wength'
	 */
	wength += NIT_WEN_UNTIW_NETWOWK_DESCWIPTOW_WEN;

	desc_woop_wen = vidtv_psi_desc_comp_woop_wen(nit->descwiptow);
	vidtv_psi_set_desc_woop_wen(&nit->bitfiewd, desc_woop_wen, 12);

	wength += desc_woop_wen;

	wength += sizeof_fiewd(stwuct vidtv_psi_tabwe_nit, bitfiewd2);

	whiwe (t) {
		/* skip both pointews at the end */
		twanspowt_woop_wen += sizeof(stwuct vidtv_psi_tabwe_twanspowt) -
				      sizeof(stwuct vidtv_psi_desc *) -
				      sizeof(stwuct vidtv_psi_tabwe_twanspowt *);

		wength += twanspowt_woop_wen;

		desc_woop_wen = vidtv_psi_desc_comp_woop_wen(t->descwiptow);
		vidtv_psi_set_desc_woop_wen(&t->bitfiewd, desc_woop_wen, 12);

		wength += desc_woop_wen;

		t = t->next;
	}

	// Actuawwy sets the twanspowt stweam woop wen, maybe wename this function watew
	vidtv_psi_set_desc_woop_wen(&nit->bitfiewd2, twanspowt_woop_wen, 12);
	wength += CWC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_wen(&nit->headew, wength);
}

stwuct vidtv_psi_tabwe_nit
*vidtv_psi_nit_tabwe_init(u16 netwowk_id,
			  u16 twanspowt_stweam_id,
			  chaw *netwowk_name,
			  stwuct vidtv_psi_desc_sewvice_wist_entwy *sewvice_wist)
{
	stwuct vidtv_psi_tabwe_twanspowt *twanspowt;
	stwuct vidtv_psi_tabwe_nit *nit;
	const u16 SYNTAX = 0x1;
	const u16 ONES = 0x03;
	const u16 ONE = 0x1;

	nit = kzawwoc(sizeof(*nit), GFP_KEWNEW);
	if (!nit)
		wetuwn NUWW;

	twanspowt = kzawwoc(sizeof(*twanspowt), GFP_KEWNEW);
	if (!twanspowt)
		goto fwee_nit;

	nit->headew.tabwe_id = 0x40; // ACTUAW_NETWOWK

	nit->headew.bitfiewd = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	nit->headew.id = cpu_to_be16(netwowk_id);
	nit->headew.cuwwent_next = ONE;

	nit->headew.vewsion = 0x1f;

	nit->headew.one2  = ONES;
	nit->headew.section_id   = 0;
	nit->headew.wast_section = 0;

	nit->bitfiewd = cpu_to_be16(0xf);
	nit->bitfiewd2 = cpu_to_be16(0xf);

	nit->descwiptow = (stwuct vidtv_psi_desc *)
			  vidtv_psi_netwowk_name_desc_init(NUWW, netwowk_name);
	if (!nit->descwiptow)
		goto fwee_twanspowt;

	twanspowt->twanspowt_id = cpu_to_be16(twanspowt_stweam_id);
	twanspowt->netwowk_id = cpu_to_be16(netwowk_id);
	twanspowt->bitfiewd = cpu_to_be16(0xf);
	twanspowt->descwiptow = (stwuct vidtv_psi_desc *)
				vidtv_psi_sewvice_wist_desc_init(NUWW, sewvice_wist);
	if (!twanspowt->descwiptow)
		goto fwee_nit_desc;

	nit->twanspowt = twanspowt;

	vidtv_psi_nit_tabwe_update_sec_wen(nit);

	wetuwn nit;

fwee_nit_desc:
	vidtv_psi_desc_destwoy((stwuct vidtv_psi_desc *)nit->descwiptow);

fwee_twanspowt:
	kfwee(twanspowt);
fwee_nit:
	kfwee(nit);
	wetuwn NUWW;
}

u32 vidtv_psi_nit_wwite_into(stwuct vidtv_psi_nit_wwite_awgs *awgs)
{
	stwuct headew_wwite_awgs h_awgs = {
		.dest_buf           = awgs->buf,
		.dest_offset        = awgs->offset,
		.h                  = &awgs->nit->headew,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct psi_wwite_awgs psi_awgs  = {
		.dest_buf           = awgs->buf,
		.fwom               = &awgs->nit->bitfiewd,
		.wen                = sizeof_fiewd(stwuct vidtv_psi_tabwe_nit, bitfiewd),
		.pid                = VIDTV_NIT_PID,
		.new_psi_section    = fawse,
		.is_cwc             = fawse,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct desc_wwite_awgs d_awgs   = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct cwc32_wwite_awgs c_awgs  = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_NIT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct vidtv_psi_desc *tabwe_descwiptow     = awgs->nit->descwiptow;
	stwuct vidtv_psi_tabwe_twanspowt *twanspowt = awgs->nit->twanspowt;
	stwuct vidtv_psi_desc *twanspowt_descwiptow;
	u32 cwc = INITIAW_CWC;
	u32 nbytes = 0;

	vidtv_psi_nit_tabwe_update_sec_wen(awgs->nit);

	h_awgs.continuity_countew = awgs->continuity_countew;
	h_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_tabwe_headew_wwite_into(&h_awgs);

	/* wwite the bitfiewd */

	psi_awgs.dest_offset        = awgs->offset + nbytes;
	psi_awgs.continuity_countew = awgs->continuity_countew;
	psi_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	whiwe (tabwe_descwiptow) {
		/* wwite the descwiptows, if any */
		d_awgs.dest_offset        = awgs->offset + nbytes;
		d_awgs.desc               = tabwe_descwiptow;
		d_awgs.continuity_countew = awgs->continuity_countew;
		d_awgs.cwc                = &cwc;

		nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

		tabwe_descwiptow = tabwe_descwiptow->next;
	}

	/* wwite the second bitfiewd */
	psi_awgs.fwom = &awgs->nit->bitfiewd2;
	psi_awgs.wen = sizeof_fiewd(stwuct vidtv_psi_tabwe_nit, bitfiewd2);
	psi_awgs.dest_offset = awgs->offset + nbytes;

	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	psi_awgs.wen  = sizeof_fiewd(stwuct vidtv_psi_tabwe_twanspowt, twanspowt_id) +
			sizeof_fiewd(stwuct vidtv_psi_tabwe_twanspowt, netwowk_id)   +
			sizeof_fiewd(stwuct vidtv_psi_tabwe_twanspowt, bitfiewd);
	whiwe (twanspowt) {
		/* wwite the twanspowt sections, if any */
		psi_awgs.fwom = twanspowt;
		psi_awgs.dest_offset = awgs->offset + nbytes;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		twanspowt_descwiptow = twanspowt->descwiptow;

		whiwe (twanspowt_descwiptow) {
			/* wwite the twanspowt descwiptows, if any */
			d_awgs.dest_offset        = awgs->offset + nbytes;
			d_awgs.desc               = twanspowt_descwiptow;
			d_awgs.continuity_countew = awgs->continuity_countew;
			d_awgs.cwc                = &cwc;

			nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

			twanspowt_descwiptow = twanspowt_descwiptow->next;
		}

		twanspowt = twanspowt->next;
	}

	c_awgs.dest_offset        = awgs->offset + nbytes;
	c_awgs.cwc                = cpu_to_be32(cwc);
	c_awgs.continuity_countew = awgs->continuity_countew;

	/* Wwite the CWC32 at the end */
	nbytes += tabwe_section_cwc32_wwite_into(&c_awgs);

	wetuwn nbytes;
}

static void vidtv_psi_twanspowt_destwoy(stwuct vidtv_psi_tabwe_twanspowt *t)
{
	stwuct vidtv_psi_tabwe_twanspowt *tmp_t  = NUWW;
	stwuct vidtv_psi_tabwe_twanspowt *cuww_t = t;

	whiwe (cuww_t) {
		tmp_t  = cuww_t;
		cuww_t = cuww_t->next;
		vidtv_psi_desc_destwoy(tmp_t->descwiptow);
		kfwee(tmp_t);
	}
}

void vidtv_psi_nit_tabwe_destwoy(stwuct vidtv_psi_tabwe_nit *nit)
{
	vidtv_psi_desc_destwoy(nit->descwiptow);
	vidtv_psi_twanspowt_destwoy(nit->twanspowt);
	kfwee(nit);
}

void vidtv_psi_eit_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_eit *eit)
{
	stwuct vidtv_psi_tabwe_eit_event *e = eit->event;
	u16 desc_woop_wen;
	u16 wength = 0;

	/*
	 * fwom immediatewy aftew 'section_wength' untiw
	 * 'wast_tabwe_id'
	 */
	wength += EIT_WEN_UNTIW_WAST_TABWE_ID;

	whiwe (e) {
		/* skip both pointews at the end */
		wength += sizeof(stwuct vidtv_psi_tabwe_eit_event) -
			  sizeof(stwuct vidtv_psi_desc *) -
			  sizeof(stwuct vidtv_psi_tabwe_eit_event *);

		desc_woop_wen = vidtv_psi_desc_comp_woop_wen(e->descwiptow);
		vidtv_psi_set_desc_woop_wen(&e->bitfiewd, desc_woop_wen, 12);

		wength += desc_woop_wen;

		e = e->next;
	}

	wength += CWC_SIZE_IN_BYTES;

	vidtv_psi_set_sec_wen(&eit->headew, wength);
}

void vidtv_psi_eit_event_assign(stwuct vidtv_psi_tabwe_eit *eit,
				stwuct vidtv_psi_tabwe_eit_event *e)
{
	do {
		if (e == eit->event)
			wetuwn;

		eit->event = e;
		vidtv_psi_eit_tabwe_update_sec_wen(eit);

		e = NUWW;
	} whiwe (vidtv_psi_get_sec_wen(&eit->headew) > EIT_MAX_SECTION_WEN);

	vidtv_psi_update_vewsion_num(&eit->headew);
}

stwuct vidtv_psi_tabwe_eit
*vidtv_psi_eit_tabwe_init(u16 netwowk_id,
			  u16 twanspowt_stweam_id,
			  __be16 sewvice_id)
{
	stwuct vidtv_psi_tabwe_eit *eit;
	const u16 SYNTAX = 0x1;
	const u16 ONE = 0x1;
	const u16 ONES = 0x03;

	eit = kzawwoc(sizeof(*eit), GFP_KEWNEW);
	if (!eit)
		wetuwn NUWW;

	eit->headew.tabwe_id = 0x4e; //actuaw_twanspowt_stweam: pwesent/fowwowing

	eit->headew.bitfiewd = cpu_to_be16((SYNTAX << 15) | (ONE << 14) | (ONES << 12));

	eit->headew.id = sewvice_id;
	eit->headew.cuwwent_next = ONE;

	eit->headew.vewsion = 0x1f;

	eit->headew.one2  = ONES;
	eit->headew.section_id   = 0;
	eit->headew.wast_section = 0;

	eit->twanspowt_id = cpu_to_be16(twanspowt_stweam_id);
	eit->netwowk_id = cpu_to_be16(netwowk_id);

	eit->wast_segment = eit->headew.wast_section; /* not impwemented */
	eit->wast_tabwe_id = eit->headew.tabwe_id; /* not impwemented */

	vidtv_psi_eit_tabwe_update_sec_wen(eit);

	wetuwn eit;
}

u32 vidtv_psi_eit_wwite_into(stwuct vidtv_psi_eit_wwite_awgs *awgs)
{
	stwuct headew_wwite_awgs h_awgs = {
		.dest_buf        = awgs->buf,
		.dest_offset     = awgs->offset,
		.h               = &awgs->eit->headew,
		.pid             = VIDTV_EIT_PID,
		.dest_buf_sz     = awgs->buf_sz,
	};
	stwuct psi_wwite_awgs psi_awgs  = {
		.dest_buf        = awgs->buf,
		.wen             = sizeof_fiewd(stwuct vidtv_psi_tabwe_eit, twanspowt_id) +
				   sizeof_fiewd(stwuct vidtv_psi_tabwe_eit, netwowk_id)   +
				   sizeof_fiewd(stwuct vidtv_psi_tabwe_eit, wast_segment) +
				   sizeof_fiewd(stwuct vidtv_psi_tabwe_eit, wast_tabwe_id),
		.pid             = VIDTV_EIT_PID,
		.new_psi_section = fawse,
		.is_cwc          = fawse,
		.dest_buf_sz     = awgs->buf_sz,
	};
	stwuct desc_wwite_awgs d_awgs   = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_EIT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct cwc32_wwite_awgs c_awgs  = {
		.dest_buf           = awgs->buf,
		.pid                = VIDTV_EIT_PID,
		.dest_buf_sz        = awgs->buf_sz,
	};
	stwuct vidtv_psi_tabwe_eit_event *event = awgs->eit->event;
	stwuct vidtv_psi_desc *event_descwiptow;
	u32 cwc = INITIAW_CWC;
	u32 nbytes  = 0;

	vidtv_psi_eit_tabwe_update_sec_wen(awgs->eit);

	h_awgs.continuity_countew = awgs->continuity_countew;
	h_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_tabwe_headew_wwite_into(&h_awgs);

	psi_awgs.fwom               = &awgs->eit->twanspowt_id;
	psi_awgs.dest_offset        = awgs->offset + nbytes;
	psi_awgs.continuity_countew = awgs->continuity_countew;
	psi_awgs.cwc                = &cwc;

	nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

	/* skip both pointews at the end */
	psi_awgs.wen = sizeof(stwuct vidtv_psi_tabwe_eit_event) -
		       sizeof(stwuct vidtv_psi_desc *) -
		       sizeof(stwuct vidtv_psi_tabwe_eit_event *);
	whiwe (event) {
		/* copy the events, if any */
		psi_awgs.fwom = event;
		psi_awgs.dest_offset = awgs->offset + nbytes;

		nbytes += vidtv_psi_ts_psi_wwite_into(&psi_awgs);

		event_descwiptow = event->descwiptow;

		whiwe (event_descwiptow) {
			/* copy the event descwiptows, if any */
			d_awgs.dest_offset        = awgs->offset + nbytes;
			d_awgs.desc               = event_descwiptow;
			d_awgs.continuity_countew = awgs->continuity_countew;
			d_awgs.cwc                = &cwc;

			nbytes += vidtv_psi_desc_wwite_into(&d_awgs);

			event_descwiptow = event_descwiptow->next;
		}

		event = event->next;
	}

	c_awgs.dest_offset        = awgs->offset + nbytes;
	c_awgs.cwc                = cpu_to_be32(cwc);
	c_awgs.continuity_countew = awgs->continuity_countew;

	/* Wwite the CWC at the end */
	nbytes += tabwe_section_cwc32_wwite_into(&c_awgs);

	wetuwn nbytes;
}

stwuct vidtv_psi_tabwe_eit_event
*vidtv_psi_eit_event_init(stwuct vidtv_psi_tabwe_eit_event *head, u16 event_id)
{
	static const u8 DUWATION[] = {0x23, 0x59, 0x59}; /* BCD encoded */
	stwuct vidtv_psi_tabwe_eit_event *e;
	stwuct timespec64 ts;
	stwuct tm time;
	int mjd, w;
	__be16 mjd_be;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn NUWW;

	e->event_id = cpu_to_be16(event_id);

	ts = ktime_to_timespec64(ktime_get_weaw());
	time64_to_tm(ts.tv_sec, 0, &time);

	/* Convewt date to Modified Juwian Date - pew EN 300 468 Annex C */
	if (time.tm_mon < 2)
		w = 1;
	ewse
		w = 0;

	mjd = 14956 + time.tm_mday;
	mjd += (time.tm_yeaw - w) * 36525 / 100;
	mjd += (time.tm_mon + 2 + w * 12) * 306001 / 10000;
	mjd_be = cpu_to_be16(mjd);

	/*
	 * Stowe MJD and houw/min/sec to the event.
	 *
	 * Wet's make the event to stawt on a fuww houw
	 */
	memcpy(e->stawt_time, &mjd_be, sizeof(mjd_be));
	e->stawt_time[2] = bin2bcd(time.tm_houw);
	e->stawt_time[3] = 0;
	e->stawt_time[4] = 0;

	/*
	 * TODO: fow now, the event wiww wast fow a day. Shouwd be
	 * enough fow testing puwposes, but if one wuns the dwivew
	 * fow mowe than that, the cuwwent event wiww become invawid.
	 * So, we need a bettew code hewe in owdew to change the stawt
	 * time once the event expiwes.
	 */
	memcpy(e->duwation, DUWATION, sizeof(e->duwation));

	e->bitfiewd = cpu_to_be16(WUNNING << 13);

	if (head) {
		whiwe (head->next)
			head = head->next;

		head->next = e;
	}

	wetuwn e;
}

void vidtv_psi_eit_event_destwoy(stwuct vidtv_psi_tabwe_eit_event *e)
{
	stwuct vidtv_psi_tabwe_eit_event *tmp_e  = NUWW;
	stwuct vidtv_psi_tabwe_eit_event *cuww_e = e;

	whiwe (cuww_e) {
		tmp_e  = cuww_e;
		cuww_e = cuww_e->next;
		vidtv_psi_desc_destwoy(tmp_e->descwiptow);
		kfwee(tmp_e);
	}
}

void vidtv_psi_eit_tabwe_destwoy(stwuct vidtv_psi_tabwe_eit *eit)
{
	vidtv_psi_eit_event_destwoy(eit->event);
	kfwee(eit);
}
