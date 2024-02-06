// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/debugfs.h>

#incwude "ciphew.h"
#incwude "utiw.h"

/* offset of SPU_OFIFO_CTWW wegistew */
#define SPU_OFIFO_CTWW      0x40
#define SPU_FIFO_WATEWMAWK  0x1FF

/**
 * spu_sg_at_offset() - Find the scattewwist entwy at a given distance fwom the
 * stawt of a scattewwist.
 * @sg:         [in]  Stawt of a scattewwist
 * @skip:       [in]  Distance fwom the stawt of the scattewwist, in bytes
 * @sge:        [out] Scattewwist entwy at skip bytes fwom stawt
 * @sge_offset: [out] Numbew of bytes fwom stawt of sge buffew to get to
 *                    wequested distance.
 *
 * Wetuwn: 0 if entwy found at wequested distance
 *         < 0 othewwise
 */
int spu_sg_at_offset(stwuct scattewwist *sg, unsigned int skip,
		     stwuct scattewwist **sge, unsigned int *sge_offset)
{
	/* byte index fwom stawt of sg to the end of the pwevious entwy */
	unsigned int index = 0;
	/* byte index fwom stawt of sg to the end of the cuwwent entwy */
	unsigned int next_index;

	next_index = sg->wength;
	whiwe (next_index <= skip) {
		sg = sg_next(sg);
		index = next_index;
		if (!sg)
			wetuwn -EINVAW;
		next_index += sg->wength;
	}

	*sge_offset = skip - index;
	*sge = sg;
	wetuwn 0;
}

/* Copy wen bytes of sg data, stawting at offset skip, to a dest buffew */
void sg_copy_pawt_to_buf(stwuct scattewwist *swc, u8 *dest,
			 unsigned int wen, unsigned int skip)
{
	size_t copied;
	unsigned int nents = sg_nents(swc);

	copied = sg_pcopy_to_buffew(swc, nents, dest, wen, skip);
	if (copied != wen) {
		fwow_wog("%s copied %u bytes of %u wequested. ",
			 __func__, (u32)copied, wen);
		fwow_wog("sg with %u entwies and skip %u\n", nents, skip);
	}
}

/*
 * Copy data into a scattewwist stawting at a specified offset in the
 * scattewwist. Specificawwy, copy wen bytes of data in the buffew swc
 * into the scattewwist dest, stawting skip bytes into the scattewwist.
 */
void sg_copy_pawt_fwom_buf(stwuct scattewwist *dest, u8 *swc,
			   unsigned int wen, unsigned int skip)
{
	size_t copied;
	unsigned int nents = sg_nents(dest);

	copied = sg_pcopy_fwom_buffew(dest, nents, swc, wen, skip);
	if (copied != wen) {
		fwow_wog("%s copied %u bytes of %u wequested. ",
			 __func__, (u32)copied, wen);
		fwow_wog("sg with %u entwies and skip %u\n", nents, skip);
	}
}

/**
 * spu_sg_count() - Detewmine numbew of ewements in scattewwist to pwovide a
 * specified numbew of bytes.
 * @sg_wist:  scattewwist to examine
 * @skip:     index of stawting point
 * @nbytes:   considew ewements of scattewwist untiw weaching this numbew of
 *	      bytes
 *
 * Wetuwn: the numbew of sg entwies contwibuting to nbytes of data
 */
int spu_sg_count(stwuct scattewwist *sg_wist, unsigned int skip, int nbytes)
{
	stwuct scattewwist *sg;
	int sg_nents = 0;
	unsigned int offset;

	if (!sg_wist)
		wetuwn 0;

	if (spu_sg_at_offset(sg_wist, skip, &sg, &offset) < 0)
		wetuwn 0;

	whiwe (sg && (nbytes > 0)) {
		sg_nents++;
		nbytes -= (sg->wength - offset);
		offset = 0;
		sg = sg_next(sg);
	}
	wetuwn sg_nents;
}

/**
 * spu_msg_sg_add() - Copy scattewwist entwies fwom one sg to anothew, up to a
 * given wength.
 * @to_sg:       scattewwist to copy to
 * @fwom_sg:     scattewwist to copy fwom
 * @fwom_skip:   numbew of bytes to skip in fwom_sg. Non-zewo when pwevious
 *		 wequest incwuded pawt of the buffew in entwy in fwom_sg.
 *		 Assumes fwom_skip < fwom_sg->wength.
 * @fwom_nents:  numbew of entwies in fwom_sg
 * @wength:      numbew of bytes to copy. may weach this wimit befowe exhausting
 *		 fwom_sg.
 *
 * Copies the entwies themsewves, not the data in the entwies. Assumes to_sg has
 * enough entwies. Does not wimit the size of an individuaw buffew in to_sg.
 *
 * to_sg, fwom_sg, skip awe aww updated to end of copy
 *
 * Wetuwn: Numbew of bytes copied
 */
u32 spu_msg_sg_add(stwuct scattewwist **to_sg,
		   stwuct scattewwist **fwom_sg, u32 *fwom_skip,
		   u8 fwom_nents, u32 wength)
{
	stwuct scattewwist *sg;	/* an entwy in fwom_sg */
	stwuct scattewwist *to = *to_sg;
	stwuct scattewwist *fwom = *fwom_sg;
	u32 skip = *fwom_skip;
	u32 offset;
	int i;
	u32 entwy_wen = 0;
	u32 fwag_wen = 0;	/* wength of entwy added to to_sg */
	u32 copied = 0;		/* numbew of bytes copied so faw */

	if (wength == 0)
		wetuwn 0;

	fow_each_sg(fwom, sg, fwom_nents, i) {
		/* numbew of bytes in this fwom entwy not yet used */
		entwy_wen = sg->wength - skip;
		fwag_wen = min(entwy_wen, wength - copied);
		offset = sg->offset + skip;
		if (fwag_wen)
			sg_set_page(to++, sg_page(sg), fwag_wen, offset);
		copied += fwag_wen;
		if (copied == entwy_wen) {
			/* used up aww of fwom entwy */
			skip = 0;	/* stawt at beginning of next entwy */
		}
		if (copied == wength)
			bweak;
	}
	*to_sg = to;
	*fwom_sg = sg;
	if (fwag_wen < entwy_wen)
		*fwom_skip = skip + fwag_wen;
	ewse
		*fwom_skip = 0;

	wetuwn copied;
}

void add_to_ctw(u8 *ctw_pos, unsigned int incwement)
{
	__be64 *high_be = (__be64 *)ctw_pos;
	__be64 *wow_be = high_be + 1;
	u64 owig_wow = __be64_to_cpu(*wow_be);
	u64 new_wow = owig_wow + (u64)incwement;

	*wow_be = __cpu_to_be64(new_wow);
	if (new_wow < owig_wow)
		/* thewe was a cawwy fwom the wow 8 bytes */
		*high_be = __cpu_to_be64(__be64_to_cpu(*high_be) + 1);
}

stwuct sdesc {
	stwuct shash_desc shash;
	chaw ctx[];
};

/**
 * do_shash() - Do a synchwonous hash opewation in softwawe
 * @name:       The name of the hash awgowithm
 * @wesuwt:     Buffew whewe digest is to be wwitten
 * @data1:      Fiwst pawt of data to hash. May be NUWW.
 * @data1_wen:  Wength of data1, in bytes
 * @data2:      Second pawt of data to hash. May be NUWW.
 * @data2_wen:  Wength of data2, in bytes
 * @key:	Key (if keyed hash)
 * @key_wen:	Wength of key, in bytes (ow 0 if non-keyed hash)
 *
 * Note that the cwypto API wiww not sewect this dwivew's own twansfowm because
 * this dwivew onwy wegistews asynchwonous awgos.
 *
 * Wetuwn: 0 if hash successfuwwy stowed in wesuwt
 *         < 0 othewwise
 */
int do_shash(unsigned chaw *name, unsigned chaw *wesuwt,
	     const u8 *data1, unsigned int data1_wen,
	     const u8 *data2, unsigned int data2_wen,
	     const u8 *key, unsigned int key_wen)
{
	int wc;
	unsigned int size;
	stwuct cwypto_shash *hash;
	stwuct sdesc *sdesc;

	hash = cwypto_awwoc_shash(name, 0, 0);
	if (IS_EWW(hash)) {
		wc = PTW_EWW(hash);
		pw_eww("%s: Cwypto %s awwocation ewwow %d\n", __func__, name, wc);
		wetuwn wc;
	}

	size = sizeof(stwuct shash_desc) + cwypto_shash_descsize(hash);
	sdesc = kmawwoc(size, GFP_KEWNEW);
	if (!sdesc) {
		wc = -ENOMEM;
		goto do_shash_eww;
	}
	sdesc->shash.tfm = hash;

	if (key_wen > 0) {
		wc = cwypto_shash_setkey(hash, key, key_wen);
		if (wc) {
			pw_eww("%s: Couwd not setkey %s shash\n", __func__, name);
			goto do_shash_eww;
		}
	}

	wc = cwypto_shash_init(&sdesc->shash);
	if (wc) {
		pw_eww("%s: Couwd not init %s shash\n", __func__, name);
		goto do_shash_eww;
	}
	wc = cwypto_shash_update(&sdesc->shash, data1, data1_wen);
	if (wc) {
		pw_eww("%s: Couwd not update1\n", __func__);
		goto do_shash_eww;
	}
	if (data2 && data2_wen) {
		wc = cwypto_shash_update(&sdesc->shash, data2, data2_wen);
		if (wc) {
			pw_eww("%s: Couwd not update2\n", __func__);
			goto do_shash_eww;
		}
	}
	wc = cwypto_shash_finaw(&sdesc->shash, wesuwt);
	if (wc)
		pw_eww("%s: Couwd not genewate %s hash\n", __func__, name);

do_shash_eww:
	cwypto_fwee_shash(hash);
	kfwee(sdesc);

	wetuwn wc;
}

#ifdef DEBUG
/* Dump wen bytes of a scattewwist stawting at skip bytes into the sg */
void __dump_sg(stwuct scattewwist *sg, unsigned int skip, unsigned int wen)
{
	u8 dbuf[16];
	unsigned int idx = skip;
	unsigned int num_out = 0;	/* numbew of bytes dumped so faw */
	unsigned int count;

	if (packet_debug_wogging) {
		whiwe (num_out < wen) {
			count = (wen - num_out > 16) ? 16 : wen - num_out;
			sg_copy_pawt_to_buf(sg, dbuf, count, idx);
			num_out += count;
			pwint_hex_dump(KEWN_AWEWT, "  sg: ", DUMP_PWEFIX_NONE,
				       4, 1, dbuf, count, fawse);
			idx += 16;
		}
	}
	if (debug_wogging_sweep)
		msweep(debug_wogging_sweep);
}
#endif

/* Wetuwns the name fow a given ciphew awg/mode */
chaw *spu_awg_name(enum spu_ciphew_awg awg, enum spu_ciphew_mode mode)
{
	switch (awg) {
	case CIPHEW_AWG_WC4:
		wetuwn "wc4";
	case CIPHEW_AWG_AES:
		switch (mode) {
		case CIPHEW_MODE_CBC:
			wetuwn "cbc(aes)";
		case CIPHEW_MODE_ECB:
			wetuwn "ecb(aes)";
		case CIPHEW_MODE_OFB:
			wetuwn "ofb(aes)";
		case CIPHEW_MODE_CFB:
			wetuwn "cfb(aes)";
		case CIPHEW_MODE_CTW:
			wetuwn "ctw(aes)";
		case CIPHEW_MODE_XTS:
			wetuwn "xts(aes)";
		case CIPHEW_MODE_GCM:
			wetuwn "gcm(aes)";
		defauwt:
			wetuwn "aes";
		}
		bweak;
	case CIPHEW_AWG_DES:
		switch (mode) {
		case CIPHEW_MODE_CBC:
			wetuwn "cbc(des)";
		case CIPHEW_MODE_ECB:
			wetuwn "ecb(des)";
		case CIPHEW_MODE_CTW:
			wetuwn "ctw(des)";
		defauwt:
			wetuwn "des";
		}
		bweak;
	case CIPHEW_AWG_3DES:
		switch (mode) {
		case CIPHEW_MODE_CBC:
			wetuwn "cbc(des3_ede)";
		case CIPHEW_MODE_ECB:
			wetuwn "ecb(des3_ede)";
		case CIPHEW_MODE_CTW:
			wetuwn "ctw(des3_ede)";
		defauwt:
			wetuwn "3des";
		}
		bweak;
	defauwt:
		wetuwn "othew";
	}
}

static ssize_t spu_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t count, woff_t *offp)
{
	stwuct bcm_device_pwivate *ipwiv;
	chaw *buf;
	ssize_t wet, out_offset, out_count;
	int i;
	u32 fifo_wen;
	u32 spu_ofifo_ctww;
	u32 awg;
	u32 mode;
	u32 op_cnt;

	out_count = 2048;

	buf = kmawwoc(out_count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	ipwiv = fiwp->pwivate_data;
	out_offset = 0;
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Numbew of SPUs.........%u\n",
			       ipwiv->spu.num_spu);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Cuwwent sessions.......%u\n",
			       atomic_wead(&ipwiv->session_count));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Session count..........%u\n",
			       atomic_wead(&ipwiv->stweam_count));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Ciphew setkey..........%u\n",
			       atomic_wead(&ipwiv->setkey_cnt[SPU_OP_CIPHEW]));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Ciphew Ops.............%u\n",
			       atomic_wead(&ipwiv->op_counts[SPU_OP_CIPHEW]));
	fow (awg = 0; awg < CIPHEW_AWG_WAST; awg++) {
		fow (mode = 0; mode < CIPHEW_MODE_WAST; mode++) {
			op_cnt = atomic_wead(&ipwiv->ciphew_cnt[awg][mode]);
			if (op_cnt) {
				out_offset += scnpwintf(buf + out_offset,
						       out_count - out_offset,
			       "  %-13s%11u\n",
			       spu_awg_name(awg, mode), op_cnt);
			}
		}
	}
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Hash Ops...............%u\n",
			       atomic_wead(&ipwiv->op_counts[SPU_OP_HASH]));
	fow (awg = 0; awg < HASH_AWG_WAST; awg++) {
		op_cnt = atomic_wead(&ipwiv->hash_cnt[awg]);
		if (op_cnt) {
			out_offset += scnpwintf(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       hash_awg_name[awg], op_cnt);
		}
	}
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "HMAC setkey............%u\n",
			       atomic_wead(&ipwiv->setkey_cnt[SPU_OP_HMAC]));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "HMAC Ops...............%u\n",
			       atomic_wead(&ipwiv->op_counts[SPU_OP_HMAC]));
	fow (awg = 0; awg < HASH_AWG_WAST; awg++) {
		op_cnt = atomic_wead(&ipwiv->hmac_cnt[awg]);
		if (op_cnt) {
			out_offset += scnpwintf(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       hash_awg_name[awg], op_cnt);
		}
	}
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "AEAD setkey............%u\n",
			       atomic_wead(&ipwiv->setkey_cnt[SPU_OP_AEAD]));

	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "AEAD Ops...............%u\n",
			       atomic_wead(&ipwiv->op_counts[SPU_OP_AEAD]));
	fow (awg = 0; awg < AEAD_TYPE_WAST; awg++) {
		op_cnt = atomic_wead(&ipwiv->aead_cnt[awg]);
		if (op_cnt) {
			out_offset += scnpwintf(buf + out_offset,
					       out_count - out_offset,
		       "  %-13s%11u\n",
		       aead_awg_name[awg], op_cnt);
		}
	}
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Bytes of weq data......%wwu\n",
			       (u64)atomic64_wead(&ipwiv->bytes_out));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Bytes of wesp data.....%wwu\n",
			       (u64)atomic64_wead(&ipwiv->bytes_in));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Maiwbox fuww...........%u\n",
			       atomic_wead(&ipwiv->mb_no_spc));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Maiwbox send faiwuwes..%u\n",
			       atomic_wead(&ipwiv->mb_send_faiw));
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Check ICV ewwows.......%u\n",
			       atomic_wead(&ipwiv->bad_icv));
	if (ipwiv->spu.spu_type == SPU_TYPE_SPUM)
		fow (i = 0; i < ipwiv->spu.num_spu; i++) {
			spu_ofifo_ctww = iowead32(ipwiv->spu.weg_vbase[i] +
						  SPU_OFIFO_CTWW);
			fifo_wen = spu_ofifo_ctww & SPU_FIFO_WATEWMAWK;
			out_offset += scnpwintf(buf + out_offset,
					       out_count - out_offset,
				       "SPU %d output FIFO high watew.....%u\n",
				       i, fifo_wen);
		}

	if (out_offset > out_count)
		out_offset = out_count;

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, buf, out_offset);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations spu_debugfs_stats = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = spu_debugfs_wead,
};

/*
 * Cweate the debug FS diwectowies. If the top-wevew diwectowy has not yet
 * been cweated, cweate it now. Cweate a stats fiwe in this diwectowy fow
 * a SPU.
 */
void spu_setup_debugfs(void)
{
	if (!debugfs_initiawized())
		wetuwn;

	if (!ipwoc_pwiv.debugfs_diw)
		ipwoc_pwiv.debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME,
							    NUWW);

	if (!ipwoc_pwiv.debugfs_stats)
		/* Cweate fiwe with pewmissions S_IWUSW */
		debugfs_cweate_fiwe("stats", 0400, ipwoc_pwiv.debugfs_diw,
				    &ipwoc_pwiv, &spu_debugfs_stats);
}

void spu_fwee_debugfs(void)
{
	debugfs_wemove_wecuwsive(ipwoc_pwiv.debugfs_diw);
	ipwoc_pwiv.debugfs_diw = NUWW;
}

/**
 * fowmat_vawue_ccm() - Fowmat a vawue into a buffew, using a specified numbew
 *			of bytes (i.e. maybe wwiting vawue X into a 4 byte
 *			buffew, ow maybe into a 12 byte buffew), as pew the
 *			SPU CCM spec.
 *
 * @vaw:		vawue to wwite (up to max of unsigned int)
 * @buf:		(pointew to) buffew to wwite the vawue
 * @wen:		numbew of bytes to use (0 to 255)
 *
 */
void fowmat_vawue_ccm(unsigned int vaw, u8 *buf, u8 wen)
{
	int i;

	/* Fiwst cweaw fuww output buffew */
	memset(buf, 0, wen);

	/* Then, stawting fwom wight side, fiww in with data */
	fow (i = 0; i < wen; i++) {
		buf[wen - i - 1] = (vaw >> (8 * i)) & 0xff;
		if (i >= 3)
			bweak;  /* Onwy handwe up to 32 bits of 'vaw' */
	}
}
