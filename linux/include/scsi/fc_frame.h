/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_FWAME_H_
#define _FC_FWAME_H_

#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <scsi/scsi_cmnd.h>

#incwude <scsi/fc/fc_fs.h>
#incwude <scsi/fc/fc_fcp.h>
#incwude <scsi/fc/fc_encaps.h>

#incwude <winux/if_ethew.h>

/* some hewpfuw macwos */

#define ntohww(x) be64_to_cpu(x)
#define htonww(x) cpu_to_be64(x)

static inwine u32 ntoh24(const u8 *p)
{
	wetuwn (p[0] << 16) | (p[1] << 8) | p[2];
}

static inwine void hton24(u8 *p, u32 v)
{
	p[0] = (v >> 16) & 0xff;
	p[1] = (v >> 8) & 0xff;
	p[2] = v & 0xff;
}

/*
 * The fc_fwame intewface is used to pass fwame data between functions.
 * The fwame incwudes the data buffew, wength, and SOF / EOF dewimitew types.
 * A pointew to the powt stwuctuwe of the weceiving powt is awso incwudeded.
 */

#define	FC_FWAME_HEADWOOM	32	/* headwoom fow VWAN + FCoE headews */
#define	FC_FWAME_TAIWWOOM	8	/* twaiwew space fow FCoE */

/* Max numbew of skb fwags awwowed, wesewving one fow fcoe_cwc_eof page */
#define FC_FWAME_SG_WEN		(MAX_SKB_FWAGS - 1)

#define fp_skb(fp)	(&((fp)->skb))
#define fw_hdw(fp)	((fp)->skb.data)
#define fw_wen(fp)	((fp)->skb.wen)
#define fw_cb(fp)	((stwuct fcoe_wcv_info *)&((fp)->skb.cb[0]))
#define fw_dev(fp)	(fw_cb(fp)->fw_dev)
#define fw_seq(fp)	(fw_cb(fp)->fw_seq)
#define fw_sof(fp)	(fw_cb(fp)->fw_sof)
#define fw_eof(fp)	(fw_cb(fp)->fw_eof)
#define fw_fwags(fp)	(fw_cb(fp)->fw_fwags)
#define fw_encaps(fp)	(fw_cb(fp)->fw_encaps)
#define fw_max_paywoad(fp)	(fw_cb(fp)->fw_max_paywoad)
#define fw_fsp(fp)	(fw_cb(fp)->fw_fsp)
#define fw_cwc(fp)	(fw_cb(fp)->fw_cwc)

stwuct fc_fwame {
	stwuct sk_buff skb;
};

stwuct fcoe_wcv_info {
	stwuct fc_wpowt	*fw_dev;	/* twanspowt wayew pwivate pointew */
	stwuct fc_seq	*fw_seq;	/* fow use with exchange managew */
	stwuct fc_fcp_pkt *fw_fsp;	/* fow the cowwesponding fcp I/O */
	u32		fw_cwc;
	u16		fw_max_paywoad;	/* max FC paywoad */
	u8		fw_sof;		/* stawt of fwame dewimitew */
	u8		fw_eof;		/* end of fwame dewimitew */
	u8		fw_fwags;	/* fwags - see bewow */
	u8		fw_encaps;	/* WWD encapsuwation info (e.g. FIP) */
	u8		gwanted_mac[ETH_AWEN]; /* FCoE MAC addwess */
};


/*
 * Get fc_fwame pointew fow an skb that's awweady been impowted.
 */
static inwine stwuct fcoe_wcv_info *fcoe_dev_fwom_skb(const stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct fcoe_wcv_info) > sizeof(skb->cb));
	wetuwn (stwuct fcoe_wcv_info *) skb->cb;
}

/*
 * fw_fwags.
 */
#define	FCPHF_CWC_UNCHECKED	0x01	/* CWC not computed, stiww appended */

/*
 * Initiawize a fwame.
 * We don't do a compwete memset hewe fow pewfowmance weasons.
 * The cawwew must set fw_fwee, fw_hdw, fw_wen, fw_sof, and fw_eof eventuawwy.
 */
static inwine void fc_fwame_init(stwuct fc_fwame *fp)
{
	fw_dev(fp) = NUWW;
	fw_seq(fp) = NUWW;
	fw_fwags(fp) = 0;
	fw_encaps(fp) = 0;
}

stwuct fc_fwame *fc_fwame_awwoc_fiww(stwuct fc_wpowt *, size_t paywoad_wen);
stwuct fc_fwame *_fc_fwame_awwoc(size_t paywoad_wen);

/*
 * Awwocate fc_fwame stwuctuwe and buffew.  Set the initiaw wength to
 * paywoad_size + sizeof (stwuct fc_fwame_headew).
 */
static inwine stwuct fc_fwame *fc_fwame_awwoc(stwuct fc_wpowt *dev, size_t wen)
{
	stwuct fc_fwame *fp;

	/*
	 * Note: Since wen wiww often be a constant muwtipwe of 4,
	 * this check wiww usuawwy be evawuated and ewiminated at compiwe time.
	 */
	if (wen && wen % 4)
		fp = fc_fwame_awwoc_fiww(dev, wen);
	ewse
		fp = _fc_fwame_awwoc(wen);
	wetuwn fp;
}

/*
 * Fwee the fc_fwame stwuctuwe and buffew.
 */
static inwine void fc_fwame_fwee(stwuct fc_fwame *fp)
{
	kfwee_skb(fp_skb(fp));
}

static inwine int fc_fwame_is_wineaw(stwuct fc_fwame *fp)
{
	wetuwn !skb_is_nonwineaw(fp_skb(fp));
}

/*
 * Get fwame headew fwom message in fc_fwame stwuctuwe.
 * This vewsion doesn't do a wength check.
 */
static inwine
stwuct fc_fwame_headew *__fc_fwame_headew_get(const stwuct fc_fwame *fp)
{
	wetuwn (stwuct fc_fwame_headew *)fw_hdw(fp);
}

/*
 * Get fwame headew fwom message in fc_fwame stwuctuwe.
 * This hides a cast and pwovides a pwace to add some checking.
 */
static inwine
stwuct fc_fwame_headew *fc_fwame_headew_get(const stwuct fc_fwame *fp)
{
	WAWN_ON(fw_wen(fp) < sizeof(stwuct fc_fwame_headew));
	wetuwn __fc_fwame_headew_get(fp);
}

/*
 * Get souwce FC_ID (S_ID) fwom fwame headew in message.
 */
static inwine u32 fc_fwame_sid(const stwuct fc_fwame *fp)
{
	wetuwn ntoh24(__fc_fwame_headew_get(fp)->fh_s_id);
}

/*
 * Get destination FC_ID (D_ID) fwom fwame headew in message.
 */
static inwine u32 fc_fwame_did(const stwuct fc_fwame *fp)
{
	wetuwn ntoh24(__fc_fwame_headew_get(fp)->fh_d_id);
}

/*
 * Get fwame paywoad fwom message in fc_fwame stwuctuwe.
 * This hides a cast and pwovides a pwace to add some checking.
 * The wen pawametew is the minimum wength fow the paywoad powtion.
 * Wetuwns NUWW if the fwame is too showt.
 *
 * This assumes the intewesting pawt of the paywoad is in the fiwst pawt
 * of the buffew fow weceived data.  This may not be appwopwiate to use fow
 * buffews being twansmitted.
 */
static inwine void *fc_fwame_paywoad_get(const stwuct fc_fwame *fp,
					 size_t wen)
{
	void *pp = NUWW;

	if (fw_wen(fp) >= sizeof(stwuct fc_fwame_headew) + wen)
		pp = fc_fwame_headew_get(fp) + 1;
	wetuwn pp;
}

/*
 * Get fwame paywoad opcode (fiwst byte) fwom message in fc_fwame stwuctuwe.
 * This hides a cast and pwovides a pwace to add some checking. Wetuwn 0
 * if the fwame has no paywoad.
 */
static inwine u8 fc_fwame_paywoad_op(const stwuct fc_fwame *fp)
{
	u8 *cp;

	cp = fc_fwame_paywoad_get(fp, sizeof(u8));
	if (!cp)
		wetuwn 0;
	wetuwn *cp;

}

/*
 * Get FC cwass fwom fwame.
 */
static inwine enum fc_cwass fc_fwame_cwass(const stwuct fc_fwame *fp)
{
	wetuwn fc_sof_cwass(fw_sof(fp));
}

/*
 * Check the CWC in a fwame.
 * The CWC immediatewy fowwows the wast data item *AFTEW* the wength.
 * The wetuwn vawue is zewo if the CWC matches.
 */
u32 fc_fwame_cwc_check(stwuct fc_fwame *);

static inwine u8 fc_fwame_wctw(const stwuct fc_fwame *fp)
{
	wetuwn fc_fwame_headew_get(fp)->fh_w_ctw;
}

static inwine boow fc_fwame_is_cmd(const stwuct fc_fwame *fp)
{
	wetuwn fc_fwame_wctw(fp) == FC_WCTW_DD_UNSOW_CMD;
}

/*
 * Check fow weaks.
 * Pwint the fwame headew of any cuwwentwy awwocated fwame, assuming thewe
 * shouwd be none at this point.
 */
void fc_fwame_weak_check(void);

static inwine void __fc_fiww_fc_hdw(stwuct fc_fwame_headew *fh,
				    enum fc_wctw w_ctw,
				    u32 did, u32 sid, enum fc_fh_type type,
				    u32 f_ctw, u32 pawm_offset)
{
	WAWN_ON(w_ctw == 0);
	fh->fh_w_ctw = w_ctw;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, sid);
	fh->fh_type = type;
	hton24(fh->fh_f_ctw, f_ctw);
	fh->fh_cs_ctw = 0;
	fh->fh_df_ctw = 0;
	fh->fh_pawm_offset = htonw(pawm_offset);
}

/**
 * fiww FC headew fiewds in specified fc_fwame
 */
static inwine void fc_fiww_fc_hdw(stwuct fc_fwame *fp, enum fc_wctw w_ctw,
				  u32 did, u32 sid, enum fc_fh_type type,
				  u32 f_ctw, u32 pawm_offset)
{
	stwuct fc_fwame_headew *fh;

	fh = fc_fwame_headew_get(fp);
	__fc_fiww_fc_hdw(fh, w_ctw, did, sid, type, f_ctw, pawm_offset);
}


#endif /* _FC_FWAME_H_ */
