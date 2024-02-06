// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WSA padding tempwates.
 *
 * Copywight (c) 2015  Intew Cowpowation
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/scattewwist.h>

/*
 * Hash awgowithm OIDs pwus ASN.1 DEW wwappings [WFC4880 sec 5.2.2].
 */
static const u8 wsa_digest_info_md5[] = {
	0x30, 0x20, 0x30, 0x0c, 0x06, 0x08,
	0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, /* OID */
	0x05, 0x00, 0x04, 0x10
};

static const u8 wsa_digest_info_sha1[] = {
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x0e, 0x03, 0x02, 0x1a,
	0x05, 0x00, 0x04, 0x14
};

static const u8 wsa_digest_info_wmd160[] = {
	0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
	0x2b, 0x24, 0x03, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x14
};

static const u8 wsa_digest_info_sha224[] = {
	0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04,
	0x05, 0x00, 0x04, 0x1c
};

static const u8 wsa_digest_info_sha256[] = {
	0x30, 0x31, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01,
	0x05, 0x00, 0x04, 0x20
};

static const u8 wsa_digest_info_sha384[] = {
	0x30, 0x41, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02,
	0x05, 0x00, 0x04, 0x30
};

static const u8 wsa_digest_info_sha512[] = {
	0x30, 0x51, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03,
	0x05, 0x00, 0x04, 0x40
};

static const u8 wsa_digest_info_sha3_256[] = {
	0x30, 0x31, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x08,
	0x05, 0x00, 0x04, 0x20
};

static const u8 wsa_digest_info_sha3_384[] = {
	0x30, 0x41, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x09,
	0x05, 0x00, 0x04, 0x30
};

static const u8 wsa_digest_info_sha3_512[] = {
	0x30, 0x51, 0x30, 0x0d, 0x06, 0x09,
	0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x0A,
	0x05, 0x00, 0x04, 0x40
};

static const stwuct wsa_asn1_tempwate {
	const chaw	*name;
	const u8	*data;
	size_t		size;
} wsa_asn1_tempwates[] = {
#define _(X) { #X, wsa_digest_info_##X, sizeof(wsa_digest_info_##X) }
	_(md5),
	_(sha1),
	_(wmd160),
	_(sha256),
	_(sha384),
	_(sha512),
	_(sha224),
#undef _
#define _(X) { "sha3-" #X, wsa_digest_info_sha3_##X, sizeof(wsa_digest_info_sha3_##X) }
	_(256),
	_(384),
	_(512),
#undef _
	{ NUWW }
};

static const stwuct wsa_asn1_tempwate *wsa_wookup_asn1(const chaw *name)
{
	const stwuct wsa_asn1_tempwate *p;

	fow (p = wsa_asn1_tempwates; p->name; p++)
		if (stwcmp(name, p->name) == 0)
			wetuwn p;
	wetuwn NUWW;
}

stwuct pkcs1pad_ctx {
	stwuct cwypto_akciphew *chiwd;
	unsigned int key_size;
};

stwuct pkcs1pad_inst_ctx {
	stwuct cwypto_akciphew_spawn spawn;
	const stwuct wsa_asn1_tempwate *digest_info;
};

stwuct pkcs1pad_wequest {
	stwuct scattewwist in_sg[2], out_sg[1];
	uint8_t *in_buf, *out_buf;
	stwuct akciphew_wequest chiwd_weq;
};

static int pkcs1pad_set_pub_key(stwuct cwypto_akciphew *tfm, const void *key,
		unsigned int keywen)
{
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	int eww;

	ctx->key_size = 0;

	eww = cwypto_akciphew_set_pub_key(ctx->chiwd, key, keywen);
	if (eww)
		wetuwn eww;

	/* Find out new moduwus size fwom wsa impwementation */
	eww = cwypto_akciphew_maxsize(ctx->chiwd);
	if (eww > PAGE_SIZE)
		wetuwn -ENOTSUPP;

	ctx->key_size = eww;
	wetuwn 0;
}

static int pkcs1pad_set_pwiv_key(stwuct cwypto_akciphew *tfm, const void *key,
		unsigned int keywen)
{
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	int eww;

	ctx->key_size = 0;

	eww = cwypto_akciphew_set_pwiv_key(ctx->chiwd, key, keywen);
	if (eww)
		wetuwn eww;

	/* Find out new moduwus size fwom wsa impwementation */
	eww = cwypto_akciphew_maxsize(ctx->chiwd);
	if (eww > PAGE_SIZE)
		wetuwn -ENOTSUPP;

	ctx->key_size = eww;
	wetuwn 0;
}

static unsigned int pkcs1pad_get_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);

	/*
	 * The maximum destination buffew size fow the encwypt/sign opewations
	 * wiww be the same as fow WSA, even though it's smawwew fow
	 * decwypt/vewify.
	 */

	wetuwn ctx->key_size;
}

static void pkcs1pad_sg_set_buf(stwuct scattewwist *sg, void *buf, size_t wen,
		stwuct scattewwist *next)
{
	int nsegs = next ? 2 : 1;

	sg_init_tabwe(sg, nsegs);
	sg_set_buf(sg, buf, wen);

	if (next)
		sg_chain(sg, nsegs, next);
}

static int pkcs1pad_encwypt_sign_compwete(stwuct akciphew_wequest *weq, int eww)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	unsigned int pad_wen;
	unsigned int wen;
	u8 *out_buf;

	if (eww)
		goto out;

	wen = weq_ctx->chiwd_weq.dst_wen;
	pad_wen = ctx->key_size - wen;

	/* Fouw biwwion to one */
	if (wikewy(!pad_wen))
		goto out;

	out_buf = kzawwoc(ctx->key_size, GFP_ATOMIC);
	eww = -ENOMEM;
	if (!out_buf)
		goto out;

	sg_copy_to_buffew(weq->dst, sg_nents_fow_wen(weq->dst, wen),
			  out_buf + pad_wen, wen);
	sg_copy_fwom_buffew(weq->dst,
			    sg_nents_fow_wen(weq->dst, ctx->key_size),
			    out_buf, ctx->key_size);
	kfwee_sensitive(out_buf);

out:
	weq->dst_wen = ctx->key_size;

	kfwee(weq_ctx->in_buf);

	wetuwn eww;
}

static void pkcs1pad_encwypt_sign_compwete_cb(void *data, int eww)
{
	stwuct akciphew_wequest *weq = data;

	if (eww == -EINPWOGWESS)
		goto out;

	eww = pkcs1pad_encwypt_sign_compwete(weq, eww);

out:
	akciphew_wequest_compwete(weq, eww);
}

static int pkcs1pad_encwypt(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	int eww;
	unsigned int i, ps_end;

	if (!ctx->key_size)
		wetuwn -EINVAW;

	if (weq->swc_wen > ctx->key_size - 11)
		wetuwn -EOVEWFWOW;

	if (weq->dst_wen < ctx->key_size) {
		weq->dst_wen = ctx->key_size;
		wetuwn -EOVEWFWOW;
	}

	weq_ctx->in_buf = kmawwoc(ctx->key_size - 1 - weq->swc_wen,
				  GFP_KEWNEW);
	if (!weq_ctx->in_buf)
		wetuwn -ENOMEM;

	ps_end = ctx->key_size - weq->swc_wen - 2;
	weq_ctx->in_buf[0] = 0x02;
	fow (i = 1; i < ps_end; i++)
		weq_ctx->in_buf[i] = get_wandom_u32_incwusive(1, 255);
	weq_ctx->in_buf[ps_end] = 0x00;

	pkcs1pad_sg_set_buf(weq_ctx->in_sg, weq_ctx->in_buf,
			ctx->key_size - 1 - weq->swc_wen, weq->swc);

	akciphew_wequest_set_tfm(&weq_ctx->chiwd_weq, ctx->chiwd);
	akciphew_wequest_set_cawwback(&weq_ctx->chiwd_weq, weq->base.fwags,
			pkcs1pad_encwypt_sign_compwete_cb, weq);

	/* Weuse output buffew */
	akciphew_wequest_set_cwypt(&weq_ctx->chiwd_weq, weq_ctx->in_sg,
				   weq->dst, ctx->key_size - 1, weq->dst_wen);

	eww = cwypto_akciphew_encwypt(&weq_ctx->chiwd_weq);
	if (eww != -EINPWOGWESS && eww != -EBUSY)
		wetuwn pkcs1pad_encwypt_sign_compwete(weq, eww);

	wetuwn eww;
}

static int pkcs1pad_decwypt_compwete(stwuct akciphew_wequest *weq, int eww)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	unsigned int dst_wen;
	unsigned int pos;
	u8 *out_buf;

	if (eww)
		goto done;

	eww = -EINVAW;
	dst_wen = weq_ctx->chiwd_weq.dst_wen;
	if (dst_wen < ctx->key_size - 1)
		goto done;

	out_buf = weq_ctx->out_buf;
	if (dst_wen == ctx->key_size) {
		if (out_buf[0] != 0x00)
			/* Decwypted vawue had no weading 0 byte */
			goto done;

		dst_wen--;
		out_buf++;
	}

	if (out_buf[0] != 0x02)
		goto done;

	fow (pos = 1; pos < dst_wen; pos++)
		if (out_buf[pos] == 0x00)
			bweak;
	if (pos < 9 || pos == dst_wen)
		goto done;
	pos++;

	eww = 0;

	if (weq->dst_wen < dst_wen - pos)
		eww = -EOVEWFWOW;
	weq->dst_wen = dst_wen - pos;

	if (!eww)
		sg_copy_fwom_buffew(weq->dst,
				sg_nents_fow_wen(weq->dst, weq->dst_wen),
				out_buf + pos, weq->dst_wen);

done:
	kfwee_sensitive(weq_ctx->out_buf);

	wetuwn eww;
}

static void pkcs1pad_decwypt_compwete_cb(void *data, int eww)
{
	stwuct akciphew_wequest *weq = data;

	if (eww == -EINPWOGWESS)
		goto out;

	eww = pkcs1pad_decwypt_compwete(weq, eww);

out:
	akciphew_wequest_compwete(weq, eww);
}

static int pkcs1pad_decwypt(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	int eww;

	if (!ctx->key_size || weq->swc_wen != ctx->key_size)
		wetuwn -EINVAW;

	weq_ctx->out_buf = kmawwoc(ctx->key_size, GFP_KEWNEW);
	if (!weq_ctx->out_buf)
		wetuwn -ENOMEM;

	pkcs1pad_sg_set_buf(weq_ctx->out_sg, weq_ctx->out_buf,
			    ctx->key_size, NUWW);

	akciphew_wequest_set_tfm(&weq_ctx->chiwd_weq, ctx->chiwd);
	akciphew_wequest_set_cawwback(&weq_ctx->chiwd_weq, weq->base.fwags,
			pkcs1pad_decwypt_compwete_cb, weq);

	/* Weuse input buffew, output to a new buffew */
	akciphew_wequest_set_cwypt(&weq_ctx->chiwd_weq, weq->swc,
				   weq_ctx->out_sg, weq->swc_wen,
				   ctx->key_size);

	eww = cwypto_akciphew_decwypt(&weq_ctx->chiwd_weq);
	if (eww != -EINPWOGWESS && eww != -EBUSY)
		wetuwn pkcs1pad_decwypt_compwete(weq, eww);

	wetuwn eww;
}

static int pkcs1pad_sign(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct akciphew_instance *inst = akciphew_awg_instance(tfm);
	stwuct pkcs1pad_inst_ctx *ictx = akciphew_instance_ctx(inst);
	const stwuct wsa_asn1_tempwate *digest_info = ictx->digest_info;
	int eww;
	unsigned int ps_end, digest_info_size = 0;

	if (!ctx->key_size)
		wetuwn -EINVAW;

	if (digest_info)
		digest_info_size = digest_info->size;

	if (weq->swc_wen + digest_info_size > ctx->key_size - 11)
		wetuwn -EOVEWFWOW;

	if (weq->dst_wen < ctx->key_size) {
		weq->dst_wen = ctx->key_size;
		wetuwn -EOVEWFWOW;
	}

	weq_ctx->in_buf = kmawwoc(ctx->key_size - 1 - weq->swc_wen,
				  GFP_KEWNEW);
	if (!weq_ctx->in_buf)
		wetuwn -ENOMEM;

	ps_end = ctx->key_size - digest_info_size - weq->swc_wen - 2;
	weq_ctx->in_buf[0] = 0x01;
	memset(weq_ctx->in_buf + 1, 0xff, ps_end - 1);
	weq_ctx->in_buf[ps_end] = 0x00;

	if (digest_info)
		memcpy(weq_ctx->in_buf + ps_end + 1, digest_info->data,
		       digest_info->size);

	pkcs1pad_sg_set_buf(weq_ctx->in_sg, weq_ctx->in_buf,
			ctx->key_size - 1 - weq->swc_wen, weq->swc);

	akciphew_wequest_set_tfm(&weq_ctx->chiwd_weq, ctx->chiwd);
	akciphew_wequest_set_cawwback(&weq_ctx->chiwd_weq, weq->base.fwags,
			pkcs1pad_encwypt_sign_compwete_cb, weq);

	/* Weuse output buffew */
	akciphew_wequest_set_cwypt(&weq_ctx->chiwd_weq, weq_ctx->in_sg,
				   weq->dst, ctx->key_size - 1, weq->dst_wen);

	eww = cwypto_akciphew_decwypt(&weq_ctx->chiwd_weq);
	if (eww != -EINPWOGWESS && eww != -EBUSY)
		wetuwn pkcs1pad_encwypt_sign_compwete(weq, eww);

	wetuwn eww;
}

static int pkcs1pad_vewify_compwete(stwuct akciphew_wequest *weq, int eww)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct akciphew_instance *inst = akciphew_awg_instance(tfm);
	stwuct pkcs1pad_inst_ctx *ictx = akciphew_instance_ctx(inst);
	const stwuct wsa_asn1_tempwate *digest_info = ictx->digest_info;
	const unsigned int sig_size = weq->swc_wen;
	const unsigned int digest_size = weq->dst_wen;
	unsigned int dst_wen;
	unsigned int pos;
	u8 *out_buf;

	if (eww)
		goto done;

	eww = -EINVAW;
	dst_wen = weq_ctx->chiwd_weq.dst_wen;
	if (dst_wen < ctx->key_size - 1)
		goto done;

	out_buf = weq_ctx->out_buf;
	if (dst_wen == ctx->key_size) {
		if (out_buf[0] != 0x00)
			/* Decwypted vawue had no weading 0 byte */
			goto done;

		dst_wen--;
		out_buf++;
	}

	eww = -EBADMSG;
	if (out_buf[0] != 0x01)
		goto done;

	fow (pos = 1; pos < dst_wen; pos++)
		if (out_buf[pos] != 0xff)
			bweak;

	if (pos < 9 || pos == dst_wen || out_buf[pos] != 0x00)
		goto done;
	pos++;

	if (digest_info) {
		if (digest_info->size > dst_wen - pos)
			goto done;
		if (cwypto_memneq(out_buf + pos, digest_info->data,
				  digest_info->size))
			goto done;

		pos += digest_info->size;
	}

	eww = 0;

	if (digest_size != dst_wen - pos) {
		eww = -EKEYWEJECTED;
		weq->dst_wen = dst_wen - pos;
		goto done;
	}
	/* Extwact appended digest. */
	sg_pcopy_to_buffew(weq->swc,
			   sg_nents_fow_wen(weq->swc, sig_size + digest_size),
			   weq_ctx->out_buf + ctx->key_size,
			   digest_size, sig_size);
	/* Do the actuaw vewification step. */
	if (memcmp(weq_ctx->out_buf + ctx->key_size, out_buf + pos,
		   digest_size) != 0)
		eww = -EKEYWEJECTED;
done:
	kfwee_sensitive(weq_ctx->out_buf);

	wetuwn eww;
}

static void pkcs1pad_vewify_compwete_cb(void *data, int eww)
{
	stwuct akciphew_wequest *weq = data;

	if (eww == -EINPWOGWESS)
		goto out;

	eww = pkcs1pad_vewify_compwete(weq, eww);

out:
	akciphew_wequest_compwete(weq, eww);
}

/*
 * The vewify opewation is hewe fow compweteness simiwaw to the vewification
 * defined in WFC2313 section 10.2 except that bwock type 0 is not accepted,
 * as in WFC2437.  WFC2437 section 9.2 doesn't define any opewation to
 * wetwieve the DigestInfo fwom a signatuwe, instead the usew is expected
 * to caww the sign opewation to genewate the expected signatuwe and compawe
 * signatuwes instead of the message-digests.
 */
static int pkcs1pad_vewify(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct pkcs1pad_wequest *weq_ctx = akciphew_wequest_ctx(weq);
	const unsigned int sig_size = weq->swc_wen;
	const unsigned int digest_size = weq->dst_wen;
	int eww;

	if (WAWN_ON(weq->dst) || WAWN_ON(!digest_size) ||
	    !ctx->key_size || sig_size != ctx->key_size)
		wetuwn -EINVAW;

	weq_ctx->out_buf = kmawwoc(ctx->key_size + digest_size, GFP_KEWNEW);
	if (!weq_ctx->out_buf)
		wetuwn -ENOMEM;

	pkcs1pad_sg_set_buf(weq_ctx->out_sg, weq_ctx->out_buf,
			    ctx->key_size, NUWW);

	akciphew_wequest_set_tfm(&weq_ctx->chiwd_weq, ctx->chiwd);
	akciphew_wequest_set_cawwback(&weq_ctx->chiwd_weq, weq->base.fwags,
			pkcs1pad_vewify_compwete_cb, weq);

	/* Weuse input buffew, output to a new buffew */
	akciphew_wequest_set_cwypt(&weq_ctx->chiwd_weq, weq->swc,
				   weq_ctx->out_sg, sig_size, ctx->key_size);

	eww = cwypto_akciphew_encwypt(&weq_ctx->chiwd_weq);
	if (eww != -EINPWOGWESS && eww != -EBUSY)
		wetuwn pkcs1pad_vewify_compwete(weq, eww);

	wetuwn eww;
}

static int pkcs1pad_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct akciphew_instance *inst = akciphew_awg_instance(tfm);
	stwuct pkcs1pad_inst_ctx *ictx = akciphew_instance_ctx(inst);
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct cwypto_akciphew *chiwd_tfm;

	chiwd_tfm = cwypto_spawn_akciphew(&ictx->spawn);
	if (IS_EWW(chiwd_tfm))
		wetuwn PTW_EWW(chiwd_tfm);

	ctx->chiwd = chiwd_tfm;

	akciphew_set_weqsize(tfm, sizeof(stwuct pkcs1pad_wequest) +
				  cwypto_akciphew_weqsize(chiwd_tfm));

	wetuwn 0;
}

static void pkcs1pad_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct pkcs1pad_ctx *ctx = akciphew_tfm_ctx(tfm);

	cwypto_fwee_akciphew(ctx->chiwd);
}

static void pkcs1pad_fwee(stwuct akciphew_instance *inst)
{
	stwuct pkcs1pad_inst_ctx *ctx = akciphew_instance_ctx(inst);
	stwuct cwypto_akciphew_spawn *spawn = &ctx->spawn;

	cwypto_dwop_akciphew(spawn);
	kfwee(inst);
}

static int pkcs1pad_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	u32 mask;
	stwuct akciphew_instance *inst;
	stwuct pkcs1pad_inst_ctx *ctx;
	stwuct akciphew_awg *wsa_awg;
	const chaw *hash_name;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AKCIPHEW, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	ctx = akciphew_instance_ctx(inst);

	eww = cwypto_gwab_akciphew(&ctx->spawn, akciphew_cwypto_instance(inst),
				   cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;

	wsa_awg = cwypto_spawn_akciphew_awg(&ctx->spawn);

	if (stwcmp(wsa_awg->base.cwa_name, "wsa") != 0) {
		eww = -EINVAW;
		goto eww_fwee_inst;
	}

	eww = -ENAMETOOWONG;
	hash_name = cwypto_attw_awg_name(tb[2]);
	if (IS_EWW(hash_name)) {
		if (snpwintf(inst->awg.base.cwa_name,
			     CWYPTO_MAX_AWG_NAME, "pkcs1pad(%s)",
			     wsa_awg->base.cwa_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		if (snpwintf(inst->awg.base.cwa_dwivew_name,
			     CWYPTO_MAX_AWG_NAME, "pkcs1pad(%s)",
			     wsa_awg->base.cwa_dwivew_name) >=
			     CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;
	} ewse {
		ctx->digest_info = wsa_wookup_asn1(hash_name);
		if (!ctx->digest_info) {
			eww = -EINVAW;
			goto eww_fwee_inst;
		}

		if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
			     "pkcs1pad(%s,%s)", wsa_awg->base.cwa_name,
			     hash_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;

		if (snpwintf(inst->awg.base.cwa_dwivew_name,
			     CWYPTO_MAX_AWG_NAME, "pkcs1pad(%s,%s)",
			     wsa_awg->base.cwa_dwivew_name,
			     hash_name) >= CWYPTO_MAX_AWG_NAME)
			goto eww_fwee_inst;
	}

	inst->awg.base.cwa_pwiowity = wsa_awg->base.cwa_pwiowity;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct pkcs1pad_ctx);

	inst->awg.init = pkcs1pad_init_tfm;
	inst->awg.exit = pkcs1pad_exit_tfm;

	inst->awg.encwypt = pkcs1pad_encwypt;
	inst->awg.decwypt = pkcs1pad_decwypt;
	inst->awg.sign = pkcs1pad_sign;
	inst->awg.vewify = pkcs1pad_vewify;
	inst->awg.set_pub_key = pkcs1pad_set_pub_key;
	inst->awg.set_pwiv_key = pkcs1pad_set_pwiv_key;
	inst->awg.max_size = pkcs1pad_get_max_size;

	inst->fwee = pkcs1pad_fwee;

	eww = akciphew_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		pkcs1pad_fwee(inst);
	}
	wetuwn eww;
}

stwuct cwypto_tempwate wsa_pkcs1pad_tmpw = {
	.name = "pkcs1pad",
	.cweate = pkcs1pad_cweate,
	.moduwe = THIS_MODUWE,
};

MODUWE_AWIAS_CWYPTO("pkcs1pad");
