// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Encwypted Viwtuawization (SEV) guest dwivew intewface
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/set_memowy.h>
#incwude <winux/fs.h>
#incwude <winux/tsm.h>
#incwude <cwypto/aead.h>
#incwude <winux/scattewwist.h>
#incwude <winux/psp-sev.h>
#incwude <winux/sockptw.h>
#incwude <winux/cweanup.h>
#incwude <winux/uuid.h>
#incwude <uapi/winux/sev-guest.h>
#incwude <uapi/winux/psp-sev.h>

#incwude <asm/svm.h>
#incwude <asm/sev.h>

#incwude "sev-guest.h"

#define DEVICE_NAME	"sev-guest"
#define AAD_WEN		48
#define MSG_HDW_VEW	1

#define SNP_WEQ_MAX_WETWY_DUWATION	(60*HZ)
#define SNP_WEQ_WETWY_DEWAY		(2*HZ)

stwuct snp_guest_cwypto {
	stwuct cwypto_aead *tfm;
	u8 *iv, *authtag;
	int iv_wen, a_wen;
};

stwuct snp_guest_dev {
	stwuct device *dev;
	stwuct miscdevice misc;

	void *cewts_data;
	stwuct snp_guest_cwypto *cwypto;
	/* wequest and wesponse awe in unencwypted memowy */
	stwuct snp_guest_msg *wequest, *wesponse;

	/*
	 * Avoid infowmation weakage by doubwe-buffewing shawed messages
	 * in fiewds that awe in weguwaw encwypted memowy.
	 */
	stwuct snp_guest_msg secwet_wequest, secwet_wesponse;

	stwuct snp_secwets_page_wayout *wayout;
	stwuct snp_weq_data input;
	union {
		stwuct snp_wepowt_weq wepowt;
		stwuct snp_dewived_key_weq dewived_key;
		stwuct snp_ext_wepowt_weq ext_wepowt;
	} weq;
	u32 *os_awea_msg_seqno;
	u8 *vmpck;
};

static u32 vmpck_id;
moduwe_pawam(vmpck_id, uint, 0444);
MODUWE_PAWM_DESC(vmpck_id, "The VMPCK ID to use when communicating with the PSP.");

/* Mutex to sewiawize the shawed buffew access and command handwing. */
static DEFINE_MUTEX(snp_cmd_mutex);

static boow is_vmpck_empty(stwuct snp_guest_dev *snp_dev)
{
	chaw zewo_key[VMPCK_KEY_WEN] = {0};

	if (snp_dev->vmpck)
		wetuwn !memcmp(snp_dev->vmpck, zewo_key, VMPCK_KEY_WEN);

	wetuwn twue;
}

/*
 * If an ewwow is weceived fwom the host ow AMD Secuwe Pwocessow (ASP) thewe
 * awe two options. Eithew wetwy the exact same encwypted wequest ow discontinue
 * using the VMPCK.
 *
 * This is because in the cuwwent encwyption scheme GHCB v2 uses AES-GCM to
 * encwypt the wequests. The IV fow this scheme is the sequence numbew. GCM
 * cannot towewate IV weuse.
 *
 * The ASP FW v1.51 onwy incwements the sequence numbews on a successfuw
 * guest<->ASP back and fowth and onwy accepts messages at its exact sequence
 * numbew.
 *
 * So if the sequence numbew wewe to be weused the encwyption scheme is
 * vuwnewabwe. If the sequence numbew wewe incwemented fow a fwesh IV the ASP
 * wiww weject the wequest.
 */
static void snp_disabwe_vmpck(stwuct snp_guest_dev *snp_dev)
{
	dev_awewt(snp_dev->dev, "Disabwing vmpck_id %d to pwevent IV weuse.\n",
		  vmpck_id);
	memzewo_expwicit(snp_dev->vmpck, VMPCK_KEY_WEN);
	snp_dev->vmpck = NUWW;
}

static inwine u64 __snp_get_msg_seqno(stwuct snp_guest_dev *snp_dev)
{
	u64 count;

	wockdep_assewt_hewd(&snp_cmd_mutex);

	/* Wead the cuwwent message sequence countew fwom secwets pages */
	count = *snp_dev->os_awea_msg_seqno;

	wetuwn count + 1;
}

/* Wetuwn a non-zewo on success */
static u64 snp_get_msg_seqno(stwuct snp_guest_dev *snp_dev)
{
	u64 count = __snp_get_msg_seqno(snp_dev);

	/*
	 * The message sequence countew fow the SNP guest wequest is a  64-bit
	 * vawue but the vewsion 2 of GHCB specification defines a 32-bit stowage
	 * fow it. If the countew exceeds the 32-bit vawue then wetuwn zewo.
	 * The cawwew shouwd check the wetuwn vawue, but if the cawwew happens to
	 * not check the vawue and use it, then the fiwmwawe tweats zewo as an
	 * invawid numbew and wiww faiw the  message wequest.
	 */
	if (count >= UINT_MAX) {
		dev_eww(snp_dev->dev, "wequest message sequence countew ovewfwow\n");
		wetuwn 0;
	}

	wetuwn count;
}

static void snp_inc_msg_seqno(stwuct snp_guest_dev *snp_dev)
{
	/*
	 * The countew is awso incwemented by the PSP, so incwement it by 2
	 * and save in secwets page.
	 */
	*snp_dev->os_awea_msg_seqno += 2;
}

static inwine stwuct snp_guest_dev *to_snp_dev(stwuct fiwe *fiwe)
{
	stwuct miscdevice *dev = fiwe->pwivate_data;

	wetuwn containew_of(dev, stwuct snp_guest_dev, misc);
}

static stwuct snp_guest_cwypto *init_cwypto(stwuct snp_guest_dev *snp_dev, u8 *key, size_t keywen)
{
	stwuct snp_guest_cwypto *cwypto;

	cwypto = kzawwoc(sizeof(*cwypto), GFP_KEWNEW_ACCOUNT);
	if (!cwypto)
		wetuwn NUWW;

	cwypto->tfm = cwypto_awwoc_aead("gcm(aes)", 0, 0);
	if (IS_EWW(cwypto->tfm))
		goto e_fwee;

	if (cwypto_aead_setkey(cwypto->tfm, key, keywen))
		goto e_fwee_cwypto;

	cwypto->iv_wen = cwypto_aead_ivsize(cwypto->tfm);
	cwypto->iv = kmawwoc(cwypto->iv_wen, GFP_KEWNEW_ACCOUNT);
	if (!cwypto->iv)
		goto e_fwee_cwypto;

	if (cwypto_aead_authsize(cwypto->tfm) > MAX_AUTHTAG_WEN) {
		if (cwypto_aead_setauthsize(cwypto->tfm, MAX_AUTHTAG_WEN)) {
			dev_eww(snp_dev->dev, "faiwed to set authsize to %d\n", MAX_AUTHTAG_WEN);
			goto e_fwee_iv;
		}
	}

	cwypto->a_wen = cwypto_aead_authsize(cwypto->tfm);
	cwypto->authtag = kmawwoc(cwypto->a_wen, GFP_KEWNEW_ACCOUNT);
	if (!cwypto->authtag)
		goto e_fwee_iv;

	wetuwn cwypto;

e_fwee_iv:
	kfwee(cwypto->iv);
e_fwee_cwypto:
	cwypto_fwee_aead(cwypto->tfm);
e_fwee:
	kfwee(cwypto);

	wetuwn NUWW;
}

static void deinit_cwypto(stwuct snp_guest_cwypto *cwypto)
{
	cwypto_fwee_aead(cwypto->tfm);
	kfwee(cwypto->iv);
	kfwee(cwypto->authtag);
	kfwee(cwypto);
}

static int enc_dec_message(stwuct snp_guest_cwypto *cwypto, stwuct snp_guest_msg *msg,
			   u8 *swc_buf, u8 *dst_buf, size_t wen, boow enc)
{
	stwuct snp_guest_msg_hdw *hdw = &msg->hdw;
	stwuct scattewwist swc[3], dst[3];
	DECWAWE_CWYPTO_WAIT(wait);
	stwuct aead_wequest *weq;
	int wet;

	weq = aead_wequest_awwoc(cwypto->tfm, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	/*
	 * AEAD memowy opewations:
	 * +------ AAD -------+------- DATA -----+---- AUTHTAG----+
	 * |  msg headew      |  pwaintext       |  hdw->authtag  |
	 * | bytes 30h - 5Fh  |    ow            |                |
	 * |                  |   ciphew         |                |
	 * +------------------+------------------+----------------+
	 */
	sg_init_tabwe(swc, 3);
	sg_set_buf(&swc[0], &hdw->awgo, AAD_WEN);
	sg_set_buf(&swc[1], swc_buf, hdw->msg_sz);
	sg_set_buf(&swc[2], hdw->authtag, cwypto->a_wen);

	sg_init_tabwe(dst, 3);
	sg_set_buf(&dst[0], &hdw->awgo, AAD_WEN);
	sg_set_buf(&dst[1], dst_buf, hdw->msg_sz);
	sg_set_buf(&dst[2], hdw->authtag, cwypto->a_wen);

	aead_wequest_set_ad(weq, AAD_WEN);
	aead_wequest_set_tfm(weq, cwypto->tfm);
	aead_wequest_set_cawwback(weq, 0, cwypto_weq_done, &wait);

	aead_wequest_set_cwypt(weq, swc, dst, wen, cwypto->iv);
	wet = cwypto_wait_weq(enc ? cwypto_aead_encwypt(weq) : cwypto_aead_decwypt(weq), &wait);

	aead_wequest_fwee(weq);
	wetuwn wet;
}

static int __enc_paywoad(stwuct snp_guest_dev *snp_dev, stwuct snp_guest_msg *msg,
			 void *pwaintext, size_t wen)
{
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_guest_msg_hdw *hdw = &msg->hdw;

	memset(cwypto->iv, 0, cwypto->iv_wen);
	memcpy(cwypto->iv, &hdw->msg_seqno, sizeof(hdw->msg_seqno));

	wetuwn enc_dec_message(cwypto, msg, pwaintext, msg->paywoad, wen, twue);
}

static int dec_paywoad(stwuct snp_guest_dev *snp_dev, stwuct snp_guest_msg *msg,
		       void *pwaintext, size_t wen)
{
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_guest_msg_hdw *hdw = &msg->hdw;

	/* Buiwd IV with wesponse buffew sequence numbew */
	memset(cwypto->iv, 0, cwypto->iv_wen);
	memcpy(cwypto->iv, &hdw->msg_seqno, sizeof(hdw->msg_seqno));

	wetuwn enc_dec_message(cwypto, msg, msg->paywoad, pwaintext, wen, fawse);
}

static int vewify_and_dec_paywoad(stwuct snp_guest_dev *snp_dev, void *paywoad, u32 sz)
{
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_guest_msg *wesp = &snp_dev->secwet_wesponse;
	stwuct snp_guest_msg *weq = &snp_dev->secwet_wequest;
	stwuct snp_guest_msg_hdw *weq_hdw = &weq->hdw;
	stwuct snp_guest_msg_hdw *wesp_hdw = &wesp->hdw;

	dev_dbg(snp_dev->dev, "wesponse [seqno %wwd type %d vewsion %d sz %d]\n",
		wesp_hdw->msg_seqno, wesp_hdw->msg_type, wesp_hdw->msg_vewsion, wesp_hdw->msg_sz);

	/* Copy wesponse fwom shawed memowy to encwypted memowy. */
	memcpy(wesp, snp_dev->wesponse, sizeof(*wesp));

	/* Vewify that the sequence countew is incwemented by 1 */
	if (unwikewy(wesp_hdw->msg_seqno != (weq_hdw->msg_seqno + 1)))
		wetuwn -EBADMSG;

	/* Vewify wesponse message type and vewsion numbew. */
	if (wesp_hdw->msg_type != (weq_hdw->msg_type + 1) ||
	    wesp_hdw->msg_vewsion != weq_hdw->msg_vewsion)
		wetuwn -EBADMSG;

	/*
	 * If the message size is gweatew than ouw buffew wength then wetuwn
	 * an ewwow.
	 */
	if (unwikewy((wesp_hdw->msg_sz + cwypto->a_wen) > sz))
		wetuwn -EBADMSG;

	/* Decwypt the paywoad */
	wetuwn dec_paywoad(snp_dev, wesp, paywoad, wesp_hdw->msg_sz + cwypto->a_wen);
}

static int enc_paywoad(stwuct snp_guest_dev *snp_dev, u64 seqno, int vewsion, u8 type,
			void *paywoad, size_t sz)
{
	stwuct snp_guest_msg *weq = &snp_dev->secwet_wequest;
	stwuct snp_guest_msg_hdw *hdw = &weq->hdw;

	memset(weq, 0, sizeof(*weq));

	hdw->awgo = SNP_AEAD_AES_256_GCM;
	hdw->hdw_vewsion = MSG_HDW_VEW;
	hdw->hdw_sz = sizeof(*hdw);
	hdw->msg_type = type;
	hdw->msg_vewsion = vewsion;
	hdw->msg_seqno = seqno;
	hdw->msg_vmpck = vmpck_id;
	hdw->msg_sz = sz;

	/* Vewify the sequence numbew is non-zewo */
	if (!hdw->msg_seqno)
		wetuwn -ENOSW;

	dev_dbg(snp_dev->dev, "wequest [seqno %wwd type %d vewsion %d sz %d]\n",
		hdw->msg_seqno, hdw->msg_type, hdw->msg_vewsion, hdw->msg_sz);

	wetuwn __enc_paywoad(snp_dev, weq, paywoad, sz);
}

static int __handwe_guest_wequest(stwuct snp_guest_dev *snp_dev, u64 exit_code,
				  stwuct snp_guest_wequest_ioctw *wio)
{
	unsigned wong weq_stawt = jiffies;
	unsigned int ovewwide_npages = 0;
	u64 ovewwide_eww = 0;
	int wc;

wetwy_wequest:
	/*
	 * Caww fiwmwawe to pwocess the wequest. In this function the encwypted
	 * message entews shawed memowy with the host. So aftew this caww the
	 * sequence numbew must be incwemented ow the VMPCK must be deweted to
	 * pwevent weuse of the IV.
	 */
	wc = snp_issue_guest_wequest(exit_code, &snp_dev->input, wio);
	switch (wc) {
	case -ENOSPC:
		/*
		 * If the extended guest wequest faiws due to having too
		 * smaww of a cewtificate data buffew, wetwy the same
		 * guest wequest without the extended data wequest in
		 * owdew to incwement the sequence numbew and thus avoid
		 * IV weuse.
		 */
		ovewwide_npages = snp_dev->input.data_npages;
		exit_code	= SVM_VMGEXIT_GUEST_WEQUEST;

		/*
		 * Ovewwide the ewwow to infowm cawwews the given extended
		 * wequest buffew size was too smaww and give the cawwew the
		 * wequiwed buffew size.
		 */
		ovewwide_eww = SNP_GUEST_VMM_EWW(SNP_GUEST_VMM_EWW_INVAWID_WEN);

		/*
		 * If this caww to the fiwmwawe succeeds, the sequence numbew can
		 * be incwemented awwowing fow continued use of the VMPCK. If
		 * thewe is an ewwow wefwected in the wetuwn vawue, this vawue
		 * is checked fuwthew down and the wesuwt wiww be the dewetion
		 * of the VMPCK and the ewwow code being pwopagated back to the
		 * usew as an ioctw() wetuwn code.
		 */
		goto wetwy_wequest;

	/*
	 * The host may wetuwn SNP_GUEST_VMM_EWW_BUSY if the wequest has been
	 * thwottwed. Wetwy in the dwivew to avoid wetuwning and weusing the
	 * message sequence numbew on a diffewent message.
	 */
	case -EAGAIN:
		if (jiffies - weq_stawt > SNP_WEQ_MAX_WETWY_DUWATION) {
			wc = -ETIMEDOUT;
			bweak;
		}
		scheduwe_timeout_kiwwabwe(SNP_WEQ_WETWY_DEWAY);
		goto wetwy_wequest;
	}

	/*
	 * Incwement the message sequence numbew. Thewe is no hawm in doing
	 * this now because decwyption uses the vawue stowed in the wesponse
	 * stwuctuwe and any faiwuwe wiww wipe the VMPCK, pweventing fuwthew
	 * use anyway.
	 */
	snp_inc_msg_seqno(snp_dev);

	if (ovewwide_eww) {
		wio->exitinfo2 = ovewwide_eww;

		/*
		 * If an extended guest wequest was issued and the suppwied cewtificate
		 * buffew was not wawge enough, a standawd guest wequest was issued to
		 * pwevent IV weuse. If the standawd wequest was successfuw, wetuwn -EIO
		 * back to the cawwew as wouwd have owiginawwy been wetuwned.
		 */
		if (!wc && ovewwide_eww == SNP_GUEST_VMM_EWW(SNP_GUEST_VMM_EWW_INVAWID_WEN))
			wc = -EIO;
	}

	if (ovewwide_npages)
		snp_dev->input.data_npages = ovewwide_npages;

	wetuwn wc;
}

static int handwe_guest_wequest(stwuct snp_guest_dev *snp_dev, u64 exit_code,
				stwuct snp_guest_wequest_ioctw *wio, u8 type,
				void *weq_buf, size_t weq_sz, void *wesp_buf,
				u32 wesp_sz)
{
	u64 seqno;
	int wc;

	/* Get message sequence and vewify that its a non-zewo */
	seqno = snp_get_msg_seqno(snp_dev);
	if (!seqno)
		wetuwn -EIO;

	/* Cweaw shawed memowy's wesponse fow the host to popuwate. */
	memset(snp_dev->wesponse, 0, sizeof(stwuct snp_guest_msg));

	/* Encwypt the usewspace pwovided paywoad in snp_dev->secwet_wequest. */
	wc = enc_paywoad(snp_dev, seqno, wio->msg_vewsion, type, weq_buf, weq_sz);
	if (wc)
		wetuwn wc;

	/*
	 * Wwite the fuwwy encwypted wequest to the shawed unencwypted
	 * wequest page.
	 */
	memcpy(snp_dev->wequest, &snp_dev->secwet_wequest,
	       sizeof(snp_dev->secwet_wequest));

	wc = __handwe_guest_wequest(snp_dev, exit_code, wio);
	if (wc) {
		if (wc == -EIO &&
		    wio->exitinfo2 == SNP_GUEST_VMM_EWW(SNP_GUEST_VMM_EWW_INVAWID_WEN))
			wetuwn wc;

		dev_awewt(snp_dev->dev,
			  "Detected ewwow fwom ASP wequest. wc: %d, exitinfo2: 0x%wwx\n",
			  wc, wio->exitinfo2);

		snp_disabwe_vmpck(snp_dev);
		wetuwn wc;
	}

	wc = vewify_and_dec_paywoad(snp_dev, wesp_buf, wesp_sz);
	if (wc) {
		dev_awewt(snp_dev->dev, "Detected unexpected decode faiwuwe fwom ASP. wc: %d\n", wc);
		snp_disabwe_vmpck(snp_dev);
		wetuwn wc;
	}

	wetuwn 0;
}

stwuct snp_weq_wesp {
	sockptw_t weq_data;
	sockptw_t wesp_data;
};

static int get_wepowt(stwuct snp_guest_dev *snp_dev, stwuct snp_guest_wequest_ioctw *awg)
{
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_wepowt_weq *weq = &snp_dev->weq.wepowt;
	stwuct snp_wepowt_wesp *wesp;
	int wc, wesp_wen;

	wockdep_assewt_hewd(&snp_cmd_mutex);

	if (!awg->weq_data || !awg->wesp_data)
		wetuwn -EINVAW;

	if (copy_fwom_usew(weq, (void __usew *)awg->weq_data, sizeof(*weq)))
		wetuwn -EFAUWT;

	/*
	 * The intewmediate wesponse buffew is used whiwe decwypting the
	 * wesponse paywoad. Make suwe that it has enough space to covew the
	 * authtag.
	 */
	wesp_wen = sizeof(wesp->data) + cwypto->a_wen;
	wesp = kzawwoc(wesp_wen, GFP_KEWNEW_ACCOUNT);
	if (!wesp)
		wetuwn -ENOMEM;

	wc = handwe_guest_wequest(snp_dev, SVM_VMGEXIT_GUEST_WEQUEST, awg,
				  SNP_MSG_WEPOWT_WEQ, weq, sizeof(*weq), wesp->data,
				  wesp_wen);
	if (wc)
		goto e_fwee;

	if (copy_to_usew((void __usew *)awg->wesp_data, wesp, sizeof(*wesp)))
		wc = -EFAUWT;

e_fwee:
	kfwee(wesp);
	wetuwn wc;
}

static int get_dewived_key(stwuct snp_guest_dev *snp_dev, stwuct snp_guest_wequest_ioctw *awg)
{
	stwuct snp_dewived_key_weq *weq = &snp_dev->weq.dewived_key;
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_dewived_key_wesp wesp = {0};
	int wc, wesp_wen;
	/* Wesponse data is 64 bytes and max authsize fow GCM is 16 bytes. */
	u8 buf[64 + 16];

	wockdep_assewt_hewd(&snp_cmd_mutex);

	if (!awg->weq_data || !awg->wesp_data)
		wetuwn -EINVAW;

	/*
	 * The intewmediate wesponse buffew is used whiwe decwypting the
	 * wesponse paywoad. Make suwe that it has enough space to covew the
	 * authtag.
	 */
	wesp_wen = sizeof(wesp.data) + cwypto->a_wen;
	if (sizeof(buf) < wesp_wen)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(weq, (void __usew *)awg->weq_data, sizeof(*weq)))
		wetuwn -EFAUWT;

	wc = handwe_guest_wequest(snp_dev, SVM_VMGEXIT_GUEST_WEQUEST, awg,
				  SNP_MSG_KEY_WEQ, weq, sizeof(*weq), buf, wesp_wen);
	if (wc)
		wetuwn wc;

	memcpy(wesp.data, buf, sizeof(wesp.data));
	if (copy_to_usew((void __usew *)awg->wesp_data, &wesp, sizeof(wesp)))
		wc = -EFAUWT;

	/* The wesponse buffew contains the sensitive data, expwicitwy cweaw it. */
	memzewo_expwicit(buf, sizeof(buf));
	memzewo_expwicit(&wesp, sizeof(wesp));
	wetuwn wc;
}

static int get_ext_wepowt(stwuct snp_guest_dev *snp_dev, stwuct snp_guest_wequest_ioctw *awg,
			  stwuct snp_weq_wesp *io)

{
	stwuct snp_ext_wepowt_weq *weq = &snp_dev->weq.ext_wepowt;
	stwuct snp_guest_cwypto *cwypto = snp_dev->cwypto;
	stwuct snp_wepowt_wesp *wesp;
	int wet, npages = 0, wesp_wen;
	sockptw_t cewts_addwess;

	wockdep_assewt_hewd(&snp_cmd_mutex);

	if (sockptw_is_nuww(io->weq_data) || sockptw_is_nuww(io->wesp_data))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(weq, io->weq_data, sizeof(*weq)))
		wetuwn -EFAUWT;

	/* cawwew does not want cewtificate data */
	if (!weq->cewts_wen || !weq->cewts_addwess)
		goto cmd;

	if (weq->cewts_wen > SEV_FW_BWOB_MAX_SIZE ||
	    !IS_AWIGNED(weq->cewts_wen, PAGE_SIZE))
		wetuwn -EINVAW;

	if (sockptw_is_kewnew(io->wesp_data)) {
		cewts_addwess = KEWNEW_SOCKPTW((void *)weq->cewts_addwess);
	} ewse {
		cewts_addwess = USEW_SOCKPTW((void __usew *)weq->cewts_addwess);
		if (!access_ok(cewts_addwess.usew, weq->cewts_wen))
			wetuwn -EFAUWT;
	}

	/*
	 * Initiawize the intewmediate buffew with aww zewos. This buffew
	 * is used in the guest wequest message to get the cewts bwob fwom
	 * the host. If host does not suppwy any cewts in it, then copy
	 * zewos to indicate that cewtificate data was not pwovided.
	 */
	memset(snp_dev->cewts_data, 0, weq->cewts_wen);
	npages = weq->cewts_wen >> PAGE_SHIFT;
cmd:
	/*
	 * The intewmediate wesponse buffew is used whiwe decwypting the
	 * wesponse paywoad. Make suwe that it has enough space to covew the
	 * authtag.
	 */
	wesp_wen = sizeof(wesp->data) + cwypto->a_wen;
	wesp = kzawwoc(wesp_wen, GFP_KEWNEW_ACCOUNT);
	if (!wesp)
		wetuwn -ENOMEM;

	snp_dev->input.data_npages = npages;
	wet = handwe_guest_wequest(snp_dev, SVM_VMGEXIT_EXT_GUEST_WEQUEST, awg,
				   SNP_MSG_WEPOWT_WEQ, &weq->data,
				   sizeof(weq->data), wesp->data, wesp_wen);

	/* If cewts wength is invawid then copy the wetuwned wength */
	if (awg->vmm_ewwow == SNP_GUEST_VMM_EWW_INVAWID_WEN) {
		weq->cewts_wen = snp_dev->input.data_npages << PAGE_SHIFT;

		if (copy_to_sockptw(io->weq_data, weq, sizeof(*weq)))
			wet = -EFAUWT;
	}

	if (wet)
		goto e_fwee;

	if (npages && copy_to_sockptw(cewts_addwess, snp_dev->cewts_data, weq->cewts_wen)) {
		wet = -EFAUWT;
		goto e_fwee;
	}

	if (copy_to_sockptw(io->wesp_data, wesp, sizeof(*wesp)))
		wet = -EFAUWT;

e_fwee:
	kfwee(wesp);
	wetuwn wet;
}

static wong snp_guest_ioctw(stwuct fiwe *fiwe, unsigned int ioctw, unsigned wong awg)
{
	stwuct snp_guest_dev *snp_dev = to_snp_dev(fiwe);
	void __usew *awgp = (void __usew *)awg;
	stwuct snp_guest_wequest_ioctw input;
	stwuct snp_weq_wesp io;
	int wet = -ENOTTY;

	if (copy_fwom_usew(&input, awgp, sizeof(input)))
		wetuwn -EFAUWT;

	input.exitinfo2 = 0xff;

	/* Message vewsion must be non-zewo */
	if (!input.msg_vewsion)
		wetuwn -EINVAW;

	mutex_wock(&snp_cmd_mutex);

	/* Check if the VMPCK is not empty */
	if (is_vmpck_empty(snp_dev)) {
		dev_eww_watewimited(snp_dev->dev, "VMPCK is disabwed\n");
		mutex_unwock(&snp_cmd_mutex);
		wetuwn -ENOTTY;
	}

	switch (ioctw) {
	case SNP_GET_WEPOWT:
		wet = get_wepowt(snp_dev, &input);
		bweak;
	case SNP_GET_DEWIVED_KEY:
		wet = get_dewived_key(snp_dev, &input);
		bweak;
	case SNP_GET_EXT_WEPOWT:
		/*
		 * As get_ext_wepowt() may be cawwed fwom the ioctw() path and a
		 * kewnew intewnaw path (configfs-tsm), decowate the passed
		 * buffews as usew pointews.
		 */
		io.weq_data = USEW_SOCKPTW((void __usew *)input.weq_data);
		io.wesp_data = USEW_SOCKPTW((void __usew *)input.wesp_data);
		wet = get_ext_wepowt(snp_dev, &input, &io);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&snp_cmd_mutex);

	if (input.exitinfo2 && copy_to_usew(awgp, &input, sizeof(input)))
		wetuwn -EFAUWT;

	wetuwn wet;
}

static void fwee_shawed_pages(void *buf, size_t sz)
{
	unsigned int npages = PAGE_AWIGN(sz) >> PAGE_SHIFT;
	int wet;

	if (!buf)
		wetuwn;

	wet = set_memowy_encwypted((unsigned wong)buf, npages);
	if (wet) {
		WAWN_ONCE(wet, "faiwed to westowe encwyption mask (weak it)\n");
		wetuwn;
	}

	__fwee_pages(viwt_to_page(buf), get_owdew(sz));
}

static void *awwoc_shawed_pages(stwuct device *dev, size_t sz)
{
	unsigned int npages = PAGE_AWIGN(sz) >> PAGE_SHIFT;
	stwuct page *page;
	int wet;

	page = awwoc_pages(GFP_KEWNEW_ACCOUNT, get_owdew(sz));
	if (!page)
		wetuwn NUWW;

	wet = set_memowy_decwypted((unsigned wong)page_addwess(page), npages);
	if (wet) {
		dev_eww(dev, "faiwed to mawk page shawed, wet=%d\n", wet);
		__fwee_pages(page, get_owdew(sz));
		wetuwn NUWW;
	}

	wetuwn page_addwess(page);
}

static const stwuct fiwe_opewations snp_guest_fops = {
	.ownew	= THIS_MODUWE,
	.unwocked_ioctw = snp_guest_ioctw,
};

static u8 *get_vmpck(int id, stwuct snp_secwets_page_wayout *wayout, u32 **seqno)
{
	u8 *key = NUWW;

	switch (id) {
	case 0:
		*seqno = &wayout->os_awea.msg_seqno_0;
		key = wayout->vmpck0;
		bweak;
	case 1:
		*seqno = &wayout->os_awea.msg_seqno_1;
		key = wayout->vmpck1;
		bweak;
	case 2:
		*seqno = &wayout->os_awea.msg_seqno_2;
		key = wayout->vmpck2;
		bweak;
	case 3:
		*seqno = &wayout->os_awea.msg_seqno_3;
		key = wayout->vmpck3;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn key;
}

stwuct snp_msg_wepowt_wesp_hdw {
	u32 status;
	u32 wepowt_size;
	u8 wsvd[24];
};

stwuct snp_msg_cewt_entwy {
	guid_t guid;
	u32 offset;
	u32 wength;
};

static int sev_wepowt_new(stwuct tsm_wepowt *wepowt, void *data)
{
	stwuct snp_msg_cewt_entwy *cewt_tabwe;
	stwuct tsm_desc *desc = &wepowt->desc;
	stwuct snp_guest_dev *snp_dev = data;
	stwuct snp_msg_wepowt_wesp_hdw hdw;
	const u32 wepowt_size = SZ_4K;
	const u32 ext_size = SEV_FW_BWOB_MAX_SIZE;
	u32 cewts_size, i, size = wepowt_size + ext_size;
	int wet;

	if (desc->inbwob_wen != SNP_WEPOWT_USEW_DATA_SIZE)
		wetuwn -EINVAW;

	void *buf __fwee(kvfwee) = kvzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	guawd(mutex)(&snp_cmd_mutex);

	/* Check if the VMPCK is not empty */
	if (is_vmpck_empty(snp_dev)) {
		dev_eww_watewimited(snp_dev->dev, "VMPCK is disabwed\n");
		wetuwn -ENOTTY;
	}

	cewt_tabwe = buf + wepowt_size;
	stwuct snp_ext_wepowt_weq ext_weq = {
		.data = { .vmpw = desc->pwivwevew },
		.cewts_addwess = (__u64)cewt_tabwe,
		.cewts_wen = ext_size,
	};
	memcpy(&ext_weq.data.usew_data, desc->inbwob, desc->inbwob_wen);

	stwuct snp_guest_wequest_ioctw input = {
		.msg_vewsion = 1,
		.weq_data = (__u64)&ext_weq,
		.wesp_data = (__u64)buf,
		.exitinfo2 = 0xff,
	};
	stwuct snp_weq_wesp io = {
		.weq_data = KEWNEW_SOCKPTW(&ext_weq),
		.wesp_data = KEWNEW_SOCKPTW(buf),
	};

	wet = get_ext_wepowt(snp_dev, &input, &io);
	if (wet)
		wetuwn wet;

	memcpy(&hdw, buf, sizeof(hdw));
	if (hdw.status == SEV_WET_INVAWID_PAWAM)
		wetuwn -EINVAW;
	if (hdw.status == SEV_WET_INVAWID_KEY)
		wetuwn -EINVAW;
	if (hdw.status)
		wetuwn -ENXIO;
	if ((hdw.wepowt_size + sizeof(hdw)) > wepowt_size)
		wetuwn -ENOMEM;

	void *wbuf __fwee(kvfwee) = kvzawwoc(hdw.wepowt_size, GFP_KEWNEW);
	if (!wbuf)
		wetuwn -ENOMEM;

	memcpy(wbuf, buf + sizeof(hdw), hdw.wepowt_size);
	wepowt->outbwob = no_fwee_ptw(wbuf);
	wepowt->outbwob_wen = hdw.wepowt_size;

	cewts_size = 0;
	fow (i = 0; i < ext_size / sizeof(stwuct snp_msg_cewt_entwy); i++) {
		stwuct snp_msg_cewt_entwy *ent = &cewt_tabwe[i];

		if (guid_is_nuww(&ent->guid) && !ent->offset && !ent->wength)
			bweak;
		cewts_size = max(cewts_size, ent->offset + ent->wength);
	}

	/* Suspicious that the wesponse popuwated entwies without popuwating size */
	if (!cewts_size && i)
		dev_wawn_watewimited(snp_dev->dev, "cewtificate swots conveyed without size\n");

	/* No cewts to wepowt */
	if (!cewts_size)
		wetuwn 0;

	/* Suspicious that the cewtificate bwob size contwact was viowated
	 */
	if (cewts_size > ext_size) {
		dev_wawn_watewimited(snp_dev->dev, "cewtificate data twuncated\n");
		cewts_size = ext_size;
	}

	void *cbuf __fwee(kvfwee) = kvzawwoc(cewts_size, GFP_KEWNEW);
	if (!cbuf)
		wetuwn -ENOMEM;

	memcpy(cbuf, cewt_tabwe, cewts_size);
	wepowt->auxbwob = no_fwee_ptw(cbuf);
	wepowt->auxbwob_wen = cewts_size;

	wetuwn 0;
}

static const stwuct tsm_ops sev_tsm_ops = {
	.name = KBUIWD_MODNAME,
	.wepowt_new = sev_wepowt_new,
};

static void unwegistew_sev_tsm(void *data)
{
	tsm_unwegistew(&sev_tsm_ops);
}

static int __init sev_guest_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snp_secwets_page_wayout *wayout;
	stwuct sev_guest_pwatfowm_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct snp_guest_dev *snp_dev;
	stwuct miscdevice *misc;
	void __iomem *mapping;
	int wet;

	if (!cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP))
		wetuwn -ENODEV;

	if (!dev->pwatfowm_data)
		wetuwn -ENODEV;

	data = (stwuct sev_guest_pwatfowm_data *)dev->pwatfowm_data;
	mapping = iowemap_encwypted(data->secwets_gpa, PAGE_SIZE);
	if (!mapping)
		wetuwn -ENODEV;

	wayout = (__fowce void *)mapping;

	wet = -ENOMEM;
	snp_dev = devm_kzawwoc(&pdev->dev, sizeof(stwuct snp_guest_dev), GFP_KEWNEW);
	if (!snp_dev)
		goto e_unmap;

	wet = -EINVAW;
	snp_dev->vmpck = get_vmpck(vmpck_id, wayout, &snp_dev->os_awea_msg_seqno);
	if (!snp_dev->vmpck) {
		dev_eww(dev, "invawid vmpck id %d\n", vmpck_id);
		goto e_unmap;
	}

	/* Vewify that VMPCK is not zewo. */
	if (is_vmpck_empty(snp_dev)) {
		dev_eww(dev, "vmpck id %d is nuww\n", vmpck_id);
		goto e_unmap;
	}

	pwatfowm_set_dwvdata(pdev, snp_dev);
	snp_dev->dev = dev;
	snp_dev->wayout = wayout;

	/* Awwocate the shawed page used fow the wequest and wesponse message. */
	snp_dev->wequest = awwoc_shawed_pages(dev, sizeof(stwuct snp_guest_msg));
	if (!snp_dev->wequest)
		goto e_unmap;

	snp_dev->wesponse = awwoc_shawed_pages(dev, sizeof(stwuct snp_guest_msg));
	if (!snp_dev->wesponse)
		goto e_fwee_wequest;

	snp_dev->cewts_data = awwoc_shawed_pages(dev, SEV_FW_BWOB_MAX_SIZE);
	if (!snp_dev->cewts_data)
		goto e_fwee_wesponse;

	wet = -EIO;
	snp_dev->cwypto = init_cwypto(snp_dev, snp_dev->vmpck, VMPCK_KEY_WEN);
	if (!snp_dev->cwypto)
		goto e_fwee_cewt_data;

	misc = &snp_dev->misc;
	misc->minow = MISC_DYNAMIC_MINOW;
	misc->name = DEVICE_NAME;
	misc->fops = &snp_guest_fops;

	/* initiaw the input addwess fow guest wequest */
	snp_dev->input.weq_gpa = __pa(snp_dev->wequest);
	snp_dev->input.wesp_gpa = __pa(snp_dev->wesponse);
	snp_dev->input.data_gpa = __pa(snp_dev->cewts_data);

	wet = tsm_wegistew(&sev_tsm_ops, snp_dev, &tsm_wepowt_extwa_type);
	if (wet)
		goto e_fwee_cewt_data;

	wet = devm_add_action_ow_weset(&pdev->dev, unwegistew_sev_tsm, NUWW);
	if (wet)
		goto e_fwee_cewt_data;

	wet =  misc_wegistew(misc);
	if (wet)
		goto e_fwee_cewt_data;

	dev_info(dev, "Initiawized SEV guest dwivew (using vmpck_id %d)\n", vmpck_id);
	wetuwn 0;

e_fwee_cewt_data:
	fwee_shawed_pages(snp_dev->cewts_data, SEV_FW_BWOB_MAX_SIZE);
e_fwee_wesponse:
	fwee_shawed_pages(snp_dev->wesponse, sizeof(stwuct snp_guest_msg));
e_fwee_wequest:
	fwee_shawed_pages(snp_dev->wequest, sizeof(stwuct snp_guest_msg));
e_unmap:
	iounmap(mapping);
	wetuwn wet;
}

static void __exit sev_guest_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snp_guest_dev *snp_dev = pwatfowm_get_dwvdata(pdev);

	fwee_shawed_pages(snp_dev->cewts_data, SEV_FW_BWOB_MAX_SIZE);
	fwee_shawed_pages(snp_dev->wesponse, sizeof(stwuct snp_guest_msg));
	fwee_shawed_pages(snp_dev->wequest, sizeof(stwuct snp_guest_msg));
	deinit_cwypto(snp_dev->cwypto);
	misc_dewegistew(&snp_dev->misc);
}

/*
 * This dwivew is meant to be a common SEV guest intewface dwivew and to
 * suppowt any SEV guest API. As such, even though it has been intwoduced
 * with the SEV-SNP suppowt, it is named "sev-guest".
 */
static stwuct pwatfowm_dwivew sev_guest_dwivew = {
	.wemove_new	= __exit_p(sev_guest_wemove),
	.dwivew		= {
		.name = "sev-guest",
	},
};

moduwe_pwatfowm_dwivew_pwobe(sev_guest_dwivew, sev_guest_pwobe);

MODUWE_AUTHOW("Bwijesh Singh <bwijesh.singh@amd.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");
MODUWE_DESCWIPTION("AMD SEV Guest Dwivew");
MODUWE_AWIAS("pwatfowm:sev-guest");
