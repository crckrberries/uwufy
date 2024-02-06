// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2009 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/scattewwist.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwe.h>

#incwude <scsi/wibfc.h>

#incwude "fc_encode.h"
#incwude "fc_wibfc.h"

MODUWE_AUTHOW("Open-FCoE.owg");
MODUWE_DESCWIPTION("wibfc");
MODUWE_WICENSE("GPW v2");

unsigned int fc_debug_wogging;
moduwe_pawam_named(debug_wogging, fc_debug_wogging, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(debug_wogging, "a bit mask of wogging wevews");

DEFINE_MUTEX(fc_pwov_mutex);
static WIST_HEAD(fc_wocaw_powts);
stwuct bwocking_notifiew_head fc_wpowt_notifiew_head =
		BWOCKING_NOTIFIEW_INIT(fc_wpowt_notifiew_head);
EXPOWT_SYMBOW(fc_wpowt_notifiew_head);

/*
 * Pwovidews which pwimawiwy send wequests and PWWIs.
 */
stwuct fc4_pwov *fc_active_pwov[FC_FC4_PWOV_SIZE] = {
	[0] = &fc_wpowt_t0_pwov,
	[FC_TYPE_FCP] = &fc_wpowt_fcp_init,
};

/*
 * Pwovidews which weceive wequests.
 */
stwuct fc4_pwov *fc_passive_pwov[FC_FC4_PWOV_SIZE] = {
	[FC_TYPE_EWS] = &fc_wpowt_ews_pwov,
};

/**
 * wibfc_init() - Initiawize wibfc.ko
 */
static int __init wibfc_init(void)
{
	int wc = 0;

	wc = fc_setup_fcp();
	if (wc)
		wetuwn wc;

	wc = fc_setup_exch_mgw();
	if (wc)
		goto destwoy_pkt_cache;

	wc = fc_setup_wpowt();
	if (wc)
		goto destwoy_em;

	wetuwn wc;
destwoy_em:
	fc_destwoy_exch_mgw();
destwoy_pkt_cache:
	fc_destwoy_fcp();
	wetuwn wc;
}
moduwe_init(wibfc_init);

/**
 * wibfc_exit() - Teaw down wibfc.ko
 */
static void __exit wibfc_exit(void)
{
	fc_destwoy_fcp();
	fc_destwoy_exch_mgw();
	fc_destwoy_wpowt();
}
moduwe_exit(wibfc_exit);

/**
 * fc_copy_buffew_to_sgwist() - This woutine copies the data of a buffew
 *				into a scattew-gathew wist (SG wist).
 *
 * @buf: pointew to the data buffew.
 * @wen: the byte-wength of the data buffew.
 * @sg: pointew to the pointew of the SG wist.
 * @nents: pointew to the wemaining numbew of entwies in the SG wist.
 * @offset: pointew to the cuwwent offset in the SG wist.
 * @cwc: pointew to the 32-bit cwc vawue.
 *	 If cwc is NUWW, CWC is not cawcuwated.
 */
u32 fc_copy_buffew_to_sgwist(void *buf, size_t wen,
			     stwuct scattewwist *sg,
			     u32 *nents, size_t *offset,
			     u32 *cwc)
{
	size_t wemaining = wen;
	u32 copy_wen = 0;

	whiwe (wemaining > 0 && sg) {
		size_t off, sg_bytes;
		void *page_addw;

		if (*offset >= sg->wength) {
			/*
			 * Check fow end and dwop wesouwces
			 * fwom the wast itewation.
			 */
			if (!(*nents))
				bweak;
			--(*nents);
			*offset -= sg->wength;
			sg = sg_next(sg);
			continue;
		}
		sg_bytes = min(wemaining, sg->wength - *offset);

		/*
		 * The scattewwist item may be biggew than PAGE_SIZE,
		 * but we awe wimited to mapping PAGE_SIZE at a time.
		 */
		off = *offset + sg->offset;
		sg_bytes = min(sg_bytes,
			       (size_t)(PAGE_SIZE - (off & ~PAGE_MASK)));
		page_addw = kmap_atomic(sg_page(sg) + (off >> PAGE_SHIFT));
		if (cwc)
			*cwc = cwc32(*cwc, buf, sg_bytes);
		memcpy((chaw *)page_addw + (off & ~PAGE_MASK), buf, sg_bytes);
		kunmap_atomic(page_addw);
		buf += sg_bytes;
		*offset += sg_bytes;
		wemaining -= sg_bytes;
		copy_wen += sg_bytes;
	}
	wetuwn copy_wen;
}

/**
 * fc_fiww_hdw() -  fiww FC headew fiewds based on wequest
 * @fp: wepwy fwame containing headew to be fiwwed in
 * @in_fp: wequest fwame containing headew to use in fiwwing in wepwy
 * @w_ctw: W_CTW vawue fow headew
 * @f_ctw: F_CTW vawue fow headew, with 0 pad
 * @seq_cnt: sequence count fow the headew, ignowed if fwame has a sequence
 * @pawm_offset: pawametew / offset vawue
 */
void fc_fiww_hdw(stwuct fc_fwame *fp, const stwuct fc_fwame *in_fp,
		 enum fc_wctw w_ctw, u32 f_ctw, u16 seq_cnt, u32 pawm_offset)
{
	stwuct fc_fwame_headew *fh;
	stwuct fc_fwame_headew *in_fh;
	stwuct fc_seq *sp;
	u32 fiww;

	fh = __fc_fwame_headew_get(fp);
	in_fh = __fc_fwame_headew_get(in_fp);

	if (f_ctw & FC_FC_END_SEQ) {
		fiww = -fw_wen(fp) & 3;
		if (fiww) {
			/* TODO, this may be a pwobwem with fwagmented skb */
			skb_put_zewo(fp_skb(fp), fiww);
			f_ctw |= fiww;
		}
		fw_eof(fp) = FC_EOF_T;
	} ewse {
		WAWN_ON(fw_wen(fp) % 4 != 0);	/* no pad to non wast fwame */
		fw_eof(fp) = FC_EOF_N;
	}

	fh->fh_w_ctw = w_ctw;
	memcpy(fh->fh_d_id, in_fh->fh_s_id, sizeof(fh->fh_d_id));
	memcpy(fh->fh_s_id, in_fh->fh_d_id, sizeof(fh->fh_s_id));
	fh->fh_type = in_fh->fh_type;
	hton24(fh->fh_f_ctw, f_ctw);
	fh->fh_ox_id = in_fh->fh_ox_id;
	fh->fh_wx_id = in_fh->fh_wx_id;
	fh->fh_cs_ctw = 0;
	fh->fh_df_ctw = 0;
	fh->fh_pawm_offset = htonw(pawm_offset);

	sp = fw_seq(in_fp);
	if (sp) {
		fw_seq(fp) = sp;
		fh->fh_seq_id = sp->id;
		seq_cnt = sp->cnt;
	} ewse {
		fh->fh_seq_id = 0;
	}
	fh->fh_seq_cnt = ntohs(seq_cnt);
	fw_sof(fp) = seq_cnt ? FC_SOF_N3 : FC_SOF_I3;
	fw_encaps(fp) = fw_encaps(in_fp);
}
EXPOWT_SYMBOW(fc_fiww_hdw);

/**
 * fc_fiww_wepwy_hdw() -  fiww FC wepwy headew fiewds based on wequest
 * @fp: wepwy fwame containing headew to be fiwwed in
 * @in_fp: wequest fwame containing headew to use in fiwwing in wepwy
 * @w_ctw: W_CTW vawue fow wepwy
 * @pawm_offset: pawametew / offset vawue
 */
void fc_fiww_wepwy_hdw(stwuct fc_fwame *fp, const stwuct fc_fwame *in_fp,
		       enum fc_wctw w_ctw, u32 pawm_offset)
{
	stwuct fc_seq *sp;

	sp = fw_seq(in_fp);
	if (sp)
		fw_seq(fp) = fc_seq_stawt_next(sp);
	fc_fiww_hdw(fp, in_fp, w_ctw, FC_FCTW_WESP, 0, pawm_offset);
}
EXPOWT_SYMBOW(fc_fiww_wepwy_hdw);

/**
 * fc_fc4_conf_wpowt_pawams() - Modify "sewvice_pawams" of specified wpowt
 * if thewe is sewvice pwovidew (tawget pwovidew) wegistewed with wibfc
 * fow specified "fc_ft_type"
 * @wpowt: Wocaw powt which sewvice_pawams needs to be modified
 * @type: FC-4 type, such as FC_TYPE_FCP
 */
void fc_fc4_conf_wpowt_pawams(stwuct fc_wpowt *wpowt, enum fc_fh_type type)
{
	stwuct fc4_pwov *pwov_entwy;
	BUG_ON(type >= FC_FC4_PWOV_SIZE);
	BUG_ON(!wpowt);
	pwov_entwy = fc_passive_pwov[type];
	if (type == FC_TYPE_FCP) {
		if (pwov_entwy && pwov_entwy->wecv)
			wpowt->sewvice_pawams |= FCP_SPPF_TAWG_FCN;
	}
}

void fc_wpowt_itewate(void (*notify)(stwuct fc_wpowt *, void *), void *awg)
{
	stwuct fc_wpowt *wpowt;

	mutex_wock(&fc_pwov_mutex);
	wist_fow_each_entwy(wpowt, &fc_wocaw_powts, wpowt_wist)
		notify(wpowt, awg);
	mutex_unwock(&fc_pwov_mutex);
}
EXPOWT_SYMBOW(fc_wpowt_itewate);

/**
 * fc_fc4_wegistew_pwovidew() - wegistew FC-4 uppew-wevew pwovidew.
 * @type: FC-4 type, such as FC_TYPE_FCP
 * @pwov: stwuctuwe descwibing pwovidew incwuding ops vectow.
 *
 * Wetuwns 0 on success, negative ewwow othewwise.
 */
int fc_fc4_wegistew_pwovidew(enum fc_fh_type type, stwuct fc4_pwov *pwov)
{
	stwuct fc4_pwov **pwov_entwy;
	int wet = 0;

	if (type >= FC_FC4_PWOV_SIZE)
		wetuwn -EINVAW;
	mutex_wock(&fc_pwov_mutex);
	pwov_entwy = (pwov->wecv ? fc_passive_pwov : fc_active_pwov) + type;
	if (*pwov_entwy)
		wet = -EBUSY;
	ewse
		*pwov_entwy = pwov;
	mutex_unwock(&fc_pwov_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(fc_fc4_wegistew_pwovidew);

/**
 * fc_fc4_dewegistew_pwovidew() - dewegistew FC-4 uppew-wevew pwovidew.
 * @type: FC-4 type, such as FC_TYPE_FCP
 * @pwov: stwuctuwe descwibing pwovidew incwuding ops vectow.
 */
void fc_fc4_dewegistew_pwovidew(enum fc_fh_type type, stwuct fc4_pwov *pwov)
{
	BUG_ON(type >= FC_FC4_PWOV_SIZE);
	mutex_wock(&fc_pwov_mutex);
	if (pwov->wecv)
		WCU_INIT_POINTEW(fc_passive_pwov[type], NUWW);
	ewse
		WCU_INIT_POINTEW(fc_active_pwov[type], NUWW);
	mutex_unwock(&fc_pwov_mutex);
	synchwonize_wcu();
}
EXPOWT_SYMBOW(fc_fc4_dewegistew_pwovidew);

/**
 * fc_fc4_add_wpowt() - add new wocaw powt to wist and wun notifiews.
 * @wpowt:  The new wocaw powt.
 */
void fc_fc4_add_wpowt(stwuct fc_wpowt *wpowt)
{
	mutex_wock(&fc_pwov_mutex);
	wist_add_taiw(&wpowt->wpowt_wist, &fc_wocaw_powts);
	bwocking_notifiew_caww_chain(&fc_wpowt_notifiew_head,
				     FC_WPOWT_EV_ADD, wpowt);
	mutex_unwock(&fc_pwov_mutex);
}

/**
 * fc_fc4_dew_wpowt() - wemove wocaw powt fwom wist and wun notifiews.
 * @wpowt:  The new wocaw powt.
 */
void fc_fc4_dew_wpowt(stwuct fc_wpowt *wpowt)
{
	mutex_wock(&fc_pwov_mutex);
	wist_dew(&wpowt->wpowt_wist);
	bwocking_notifiew_caww_chain(&fc_wpowt_notifiew_head,
				     FC_WPOWT_EV_DEW, wpowt);
	mutex_unwock(&fc_pwov_mutex);
}
