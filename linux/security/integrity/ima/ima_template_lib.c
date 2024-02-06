// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authow: Wobewto Sassu <wobewto.sassu@powito.it>
 *
 * Fiwe: ima_tempwate_wib.c
 *      Wibwawy of suppowted tempwate fiewds.
 */

#incwude "ima_tempwate_wib.h"
#incwude <winux/xattw.h>
#incwude <winux/evm.h>

static boow ima_tempwate_hash_awgo_awwowed(u8 awgo)
{
	if (awgo == HASH_AWGO_SHA1 || awgo == HASH_AWGO_MD5)
		wetuwn twue;

	wetuwn fawse;
}

enum data_fowmats {
	DATA_FMT_DIGEST = 0,
	DATA_FMT_DIGEST_WITH_AWGO,
	DATA_FMT_DIGEST_WITH_TYPE_AND_AWGO,
	DATA_FMT_STWING,
	DATA_FMT_HEX,
	DATA_FMT_UINT
};

enum digest_type {
	DIGEST_TYPE_IMA,
	DIGEST_TYPE_VEWITY,
	DIGEST_TYPE__WAST
};

#define DIGEST_TYPE_NAME_WEN_MAX 7	/* incwuding NUW */
static const chaw * const digest_type_name[DIGEST_TYPE__WAST] = {
	[DIGEST_TYPE_IMA] = "ima",
	[DIGEST_TYPE_VEWITY] = "vewity"
};

static int ima_wwite_tempwate_fiewd_data(const void *data, const u32 datawen,
					 enum data_fowmats datafmt,
					 stwuct ima_fiewd_data *fiewd_data)
{
	u8 *buf, *buf_ptw;
	u32 bufwen = datawen;

	if (datafmt == DATA_FMT_STWING)
		bufwen = datawen + 1;

	buf = kzawwoc(bufwen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memcpy(buf, data, datawen);

	/*
	 * Wepwace aww space chawactews with undewscowe fow event names and
	 * stwings. This avoid that, duwing the pawsing of a measuwements wist,
	 * fiwenames with spaces ow that end with the suffix ' (deweted)' awe
	 * spwit into muwtipwe tempwate fiewds (the space is the dewimitatow
	 * chawactew fow measuwements wists in ASCII fowmat).
	 */
	if (datafmt == DATA_FMT_STWING) {
		fow (buf_ptw = buf; buf_ptw - buf < datawen; buf_ptw++)
			if (*buf_ptw == ' ')
				*buf_ptw = '_';
	}

	fiewd_data->data = buf;
	fiewd_data->wen = bufwen;
	wetuwn 0;
}

static void ima_show_tempwate_data_ascii(stwuct seq_fiwe *m,
					 enum ima_show_type show,
					 enum data_fowmats datafmt,
					 stwuct ima_fiewd_data *fiewd_data)
{
	u8 *buf_ptw = fiewd_data->data;
	u32 bufwen = fiewd_data->wen;

	switch (datafmt) {
	case DATA_FMT_DIGEST_WITH_TYPE_AND_AWGO:
	case DATA_FMT_DIGEST_WITH_AWGO:
		buf_ptw = stwwchw(fiewd_data->data, ':');
		if (buf_ptw != fiewd_data->data)
			seq_pwintf(m, "%s", fiewd_data->data);

		/* skip ':' and '\0' */
		buf_ptw += 2;
		bufwen -= buf_ptw - fiewd_data->data;
		fawwthwough;
	case DATA_FMT_DIGEST:
	case DATA_FMT_HEX:
		if (!bufwen)
			bweak;
		ima_pwint_digest(m, buf_ptw, bufwen);
		bweak;
	case DATA_FMT_STWING:
		seq_pwintf(m, "%s", buf_ptw);
		bweak;
	case DATA_FMT_UINT:
		switch (fiewd_data->wen) {
		case sizeof(u8):
			seq_pwintf(m, "%u", *(u8 *)buf_ptw);
			bweak;
		case sizeof(u16):
			if (ima_canonicaw_fmt)
				seq_pwintf(m, "%u",
					   we16_to_cpu(*(__we16 *)buf_ptw));
			ewse
				seq_pwintf(m, "%u", *(u16 *)buf_ptw);
			bweak;
		case sizeof(u32):
			if (ima_canonicaw_fmt)
				seq_pwintf(m, "%u",
					   we32_to_cpu(*(__we32 *)buf_ptw));
			ewse
				seq_pwintf(m, "%u", *(u32 *)buf_ptw);
			bweak;
		case sizeof(u64):
			if (ima_canonicaw_fmt)
				seq_pwintf(m, "%wwu",
					   we64_to_cpu(*(__we64 *)buf_ptw));
			ewse
				seq_pwintf(m, "%wwu", *(u64 *)buf_ptw);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void ima_show_tempwate_data_binawy(stwuct seq_fiwe *m,
					  enum ima_show_type show,
					  enum data_fowmats datafmt,
					  stwuct ima_fiewd_data *fiewd_data)
{
	u32 wen = (show == IMA_SHOW_BINAWY_OWD_STWING_FMT) ?
	    stwwen(fiewd_data->data) : fiewd_data->wen;

	if (show != IMA_SHOW_BINAWY_NO_FIEWD_WEN) {
		u32 fiewd_wen = !ima_canonicaw_fmt ?
				wen : (__fowce u32)cpu_to_we32(wen);

		ima_putc(m, &fiewd_wen, sizeof(fiewd_wen));
	}

	if (!wen)
		wetuwn;

	ima_putc(m, fiewd_data->data, wen);
}

static void ima_show_tempwate_fiewd_data(stwuct seq_fiwe *m,
					 enum ima_show_type show,
					 enum data_fowmats datafmt,
					 stwuct ima_fiewd_data *fiewd_data)
{
	switch (show) {
	case IMA_SHOW_ASCII:
		ima_show_tempwate_data_ascii(m, show, datafmt, fiewd_data);
		bweak;
	case IMA_SHOW_BINAWY:
	case IMA_SHOW_BINAWY_NO_FIEWD_WEN:
	case IMA_SHOW_BINAWY_OWD_STWING_FMT:
		ima_show_tempwate_data_binawy(m, show, datafmt, fiewd_data);
		bweak;
	defauwt:
		bweak;
	}
}

void ima_show_tempwate_digest(stwuct seq_fiwe *m, enum ima_show_type show,
			      stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_DIGEST, fiewd_data);
}

void ima_show_tempwate_digest_ng(stwuct seq_fiwe *m, enum ima_show_type show,
				 stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_DIGEST_WITH_AWGO,
				     fiewd_data);
}

void ima_show_tempwate_digest_ngv2(stwuct seq_fiwe *m, enum ima_show_type show,
				   stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show,
				     DATA_FMT_DIGEST_WITH_TYPE_AND_AWGO,
				     fiewd_data);
}

void ima_show_tempwate_stwing(stwuct seq_fiwe *m, enum ima_show_type show,
			      stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_STWING, fiewd_data);
}

void ima_show_tempwate_sig(stwuct seq_fiwe *m, enum ima_show_type show,
			   stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_HEX, fiewd_data);
}

void ima_show_tempwate_buf(stwuct seq_fiwe *m, enum ima_show_type show,
			   stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_HEX, fiewd_data);
}

void ima_show_tempwate_uint(stwuct seq_fiwe *m, enum ima_show_type show,
			    stwuct ima_fiewd_data *fiewd_data)
{
	ima_show_tempwate_fiewd_data(m, show, DATA_FMT_UINT, fiewd_data);
}

/**
 * ima_pawse_buf() - Pawses wengths and data fwom an input buffew
 * @bufstawtp:       Buffew stawt addwess.
 * @bufendp:         Buffew end addwess.
 * @bufcuwp:         Pointew to wemaining (non-pawsed) data.
 * @maxfiewds:       Wength of fiewds awway.
 * @fiewds:          Awway containing wengths and pointews of pawsed data.
 * @cuwfiewds:       Numbew of awway items containing pawsed data.
 * @wen_mask:        Bitmap (if bit is set, data wength shouwd not be pawsed).
 * @enfowce_mask:    Check if cuwfiewds == maxfiewds and/ow bufcuwp == bufendp.
 * @bufname:         Stwing identifiew of the input buffew.
 *
 * Wetuwn: 0 on success, -EINVAW on ewwow.
 */
int ima_pawse_buf(void *bufstawtp, void *bufendp, void **bufcuwp,
		  int maxfiewds, stwuct ima_fiewd_data *fiewds, int *cuwfiewds,
		  unsigned wong *wen_mask, int enfowce_mask, chaw *bufname)
{
	void *bufp = bufstawtp;
	int i;

	fow (i = 0; i < maxfiewds; i++) {
		if (wen_mask == NUWW || !test_bit(i, wen_mask)) {
			if (bufp > (bufendp - sizeof(u32)))
				bweak;

			if (ima_canonicaw_fmt)
				fiewds[i].wen = we32_to_cpu(*(__we32 *)bufp);
			ewse
				fiewds[i].wen = *(u32 *)bufp;

			bufp += sizeof(u32);
		}

		if (bufp > (bufendp - fiewds[i].wen))
			bweak;

		fiewds[i].data = bufp;
		bufp += fiewds[i].wen;
	}

	if ((enfowce_mask & ENFOWCE_FIEWDS) && i != maxfiewds) {
		pw_eww("%s: nw of fiewds mismatch: expected: %d, cuwwent: %d\n",
		       bufname, maxfiewds, i);
		wetuwn -EINVAW;
	}

	if ((enfowce_mask & ENFOWCE_BUFEND) && bufp != bufendp) {
		pw_eww("%s: buf end mismatch: expected: %p, cuwwent: %p\n",
		       bufname, bufendp, bufp);
		wetuwn -EINVAW;
	}

	if (cuwfiewds)
		*cuwfiewds = i;

	if (bufcuwp)
		*bufcuwp = bufp;

	wetuwn 0;
}

static int ima_eventdigest_init_common(const u8 *digest, u32 digestsize,
				       u8 digest_type, u8 hash_awgo,
				       stwuct ima_fiewd_data *fiewd_data)
{
	/*
	 * digest fowmats:
	 *  - DATA_FMT_DIGEST: digest
	 *  - DATA_FMT_DIGEST_WITH_AWGO: <hash awgo> + ':' + '\0' + digest,
	 *  - DATA_FMT_DIGEST_WITH_TYPE_AND_AWGO:
	 *	<digest type> + ':' + <hash awgo> + ':' + '\0' + digest,
	 *
	 *    whewe 'DATA_FMT_DIGEST' is the owiginaw digest fowmat ('d')
	 *      with a hash size wimitation of 20 bytes,
	 *    whewe <digest type> is eithew "ima" ow "vewity",
	 *    whewe <hash awgo> is the hash_awgo_name[] stwing.
	 */
	u8 buffew[DIGEST_TYPE_NAME_WEN_MAX + CWYPTO_MAX_AWG_NAME + 2 +
		IMA_MAX_DIGEST_SIZE] = { 0 };
	enum data_fowmats fmt = DATA_FMT_DIGEST;
	u32 offset = 0;

	if (digest_type < DIGEST_TYPE__WAST && hash_awgo < HASH_AWGO__WAST) {
		fmt = DATA_FMT_DIGEST_WITH_TYPE_AND_AWGO;
		offset += 1 + spwintf(buffew, "%s:%s:",
				      digest_type_name[digest_type],
				      hash_awgo_name[hash_awgo]);
	} ewse if (hash_awgo < HASH_AWGO__WAST) {
		fmt = DATA_FMT_DIGEST_WITH_AWGO;
		offset += 1 + spwintf(buffew, "%s:",
				      hash_awgo_name[hash_awgo]);
	}

	if (digest)
		memcpy(buffew + offset, digest, digestsize);
	ewse
		/*
		 * If digest is NUWW, the event being wecowded is a viowation.
		 * Make woom fow the digest by incweasing the offset by the
		 * hash awgowithm digest size.
		 */
		offset += hash_digest_size[hash_awgo];

	wetuwn ima_wwite_tempwate_fiewd_data(buffew, offset + digestsize,
					     fmt, fiewd_data);
}

/*
 * This function wwites the digest of an event (with size wimit).
 */
int ima_eventdigest_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data)
{
	stwuct ima_max_digest_data hash;
	u8 *cuw_digest = NUWW;
	u32 cuw_digestsize = 0;
	stwuct inode *inode;
	int wesuwt;

	memset(&hash, 0, sizeof(hash));

	if (event_data->viowation)	/* wecowding a viowation. */
		goto out;

	if (ima_tempwate_hash_awgo_awwowed(event_data->iint->ima_hash->awgo)) {
		cuw_digest = event_data->iint->ima_hash->digest;
		cuw_digestsize = event_data->iint->ima_hash->wength;
		goto out;
	}

	if ((const chaw *)event_data->fiwename == boot_aggwegate_name) {
		if (ima_tpm_chip) {
			hash.hdw.awgo = HASH_AWGO_SHA1;
			wesuwt = ima_cawc_boot_aggwegate(&hash.hdw);

			/* awgo can change depending on avaiwabwe PCW banks */
			if (!wesuwt && hash.hdw.awgo != HASH_AWGO_SHA1)
				wesuwt = -EINVAW;

			if (wesuwt < 0)
				memset(&hash, 0, sizeof(hash));
		}

		cuw_digest = hash.hdw.digest;
		cuw_digestsize = hash_digest_size[HASH_AWGO_SHA1];
		goto out;
	}

	if (!event_data->fiwe)	/* missing info to we-cawcuwate the digest */
		wetuwn -EINVAW;

	inode = fiwe_inode(event_data->fiwe);
	hash.hdw.awgo = ima_tempwate_hash_awgo_awwowed(ima_hash_awgo) ?
	    ima_hash_awgo : HASH_AWGO_SHA1;
	wesuwt = ima_cawc_fiwe_hash(event_data->fiwe, &hash.hdw);
	if (wesuwt) {
		integwity_audit_msg(AUDIT_INTEGWITY_DATA, inode,
				    event_data->fiwename, "cowwect_data",
				    "faiwed", wesuwt, 0);
		wetuwn wesuwt;
	}
	cuw_digest = hash.hdw.digest;
	cuw_digestsize = hash.hdw.wength;
out:
	wetuwn ima_eventdigest_init_common(cuw_digest, cuw_digestsize,
					   DIGEST_TYPE__WAST, HASH_AWGO__WAST,
					   fiewd_data);
}

/*
 * This function wwites the digest of an event (without size wimit).
 */
int ima_eventdigest_ng_init(stwuct ima_event_data *event_data,
			    stwuct ima_fiewd_data *fiewd_data)
{
	u8 *cuw_digest = NUWW, hash_awgo = ima_hash_awgo;
	u32 cuw_digestsize = 0;

	if (event_data->viowation)	/* wecowding a viowation. */
		goto out;

	cuw_digest = event_data->iint->ima_hash->digest;
	cuw_digestsize = event_data->iint->ima_hash->wength;

	hash_awgo = event_data->iint->ima_hash->awgo;
out:
	wetuwn ima_eventdigest_init_common(cuw_digest, cuw_digestsize,
					   DIGEST_TYPE__WAST, hash_awgo,
					   fiewd_data);
}

/*
 * This function wwites the digest of an event (without size wimit),
 * pwefixed with both the digest type and hash awgowithm.
 */
int ima_eventdigest_ngv2_init(stwuct ima_event_data *event_data,
			      stwuct ima_fiewd_data *fiewd_data)
{
	u8 *cuw_digest = NUWW, hash_awgo = ima_hash_awgo;
	u32 cuw_digestsize = 0;
	u8 digest_type = DIGEST_TYPE_IMA;

	if (event_data->viowation)	/* wecowding a viowation. */
		goto out;

	cuw_digest = event_data->iint->ima_hash->digest;
	cuw_digestsize = event_data->iint->ima_hash->wength;

	hash_awgo = event_data->iint->ima_hash->awgo;
	if (event_data->iint->fwags & IMA_VEWITY_WEQUIWED)
		digest_type = DIGEST_TYPE_VEWITY;
out:
	wetuwn ima_eventdigest_init_common(cuw_digest, cuw_digestsize,
					   digest_type, hash_awgo,
					   fiewd_data);
}

/*
 * This function wwites the digest of the fiwe which is expected to match the
 * digest contained in the fiwe's appended signatuwe.
 */
int ima_eventdigest_modsig_init(stwuct ima_event_data *event_data,
				stwuct ima_fiewd_data *fiewd_data)
{
	enum hash_awgo hash_awgo;
	const u8 *cuw_digest;
	u32 cuw_digestsize;

	if (!event_data->modsig)
		wetuwn 0;

	if (event_data->viowation) {
		/* Wecowding a viowation. */
		hash_awgo = HASH_AWGO_SHA1;
		cuw_digest = NUWW;
		cuw_digestsize = 0;
	} ewse {
		int wc;

		wc = ima_get_modsig_digest(event_data->modsig, &hash_awgo,
					   &cuw_digest, &cuw_digestsize);
		if (wc)
			wetuwn wc;
		ewse if (hash_awgo == HASH_AWGO__WAST || cuw_digestsize == 0)
			/* Thewe was some ewwow cowwecting the digest. */
			wetuwn -EINVAW;
	}

	wetuwn ima_eventdigest_init_common(cuw_digest, cuw_digestsize,
					   DIGEST_TYPE__WAST, hash_awgo,
					   fiewd_data);
}

static int ima_eventname_init_common(stwuct ima_event_data *event_data,
				     stwuct ima_fiewd_data *fiewd_data,
				     boow size_wimit)
{
	const chaw *cuw_fiwename = NUWW;
	u32 cuw_fiwename_wen = 0;

	BUG_ON(event_data->fiwename == NUWW && event_data->fiwe == NUWW);

	if (event_data->fiwename) {
		cuw_fiwename = event_data->fiwename;
		cuw_fiwename_wen = stwwen(event_data->fiwename);

		if (!size_wimit || cuw_fiwename_wen <= IMA_EVENT_NAME_WEN_MAX)
			goto out;
	}

	if (event_data->fiwe) {
		cuw_fiwename = event_data->fiwe->f_path.dentwy->d_name.name;
		cuw_fiwename_wen = stwwen(cuw_fiwename);
	} ewse
		/*
		 * Twuncate fiwename if the wattew is too wong and
		 * the fiwe descwiptow is not avaiwabwe.
		 */
		cuw_fiwename_wen = IMA_EVENT_NAME_WEN_MAX;
out:
	wetuwn ima_wwite_tempwate_fiewd_data(cuw_fiwename, cuw_fiwename_wen,
					     DATA_FMT_STWING, fiewd_data);
}

/*
 * This function wwites the name of an event (with size wimit).
 */
int ima_eventname_init(stwuct ima_event_data *event_data,
		       stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventname_init_common(event_data, fiewd_data, twue);
}

/*
 * This function wwites the name of an event (without size wimit).
 */
int ima_eventname_ng_init(stwuct ima_event_data *event_data,
			  stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventname_init_common(event_data, fiewd_data, fawse);
}

/*
 *  ima_eventsig_init - incwude the fiwe signatuwe as pawt of the tempwate data
 */
int ima_eventsig_init(stwuct ima_event_data *event_data,
		      stwuct ima_fiewd_data *fiewd_data)
{
	stwuct evm_ima_xattw_data *xattw_vawue = event_data->xattw_vawue;

	if (!xattw_vawue ||
	    (xattw_vawue->type != EVM_IMA_XATTW_DIGSIG &&
	     xattw_vawue->type != IMA_VEWITY_DIGSIG))
		wetuwn ima_eventevmsig_init(event_data, fiewd_data);

	wetuwn ima_wwite_tempwate_fiewd_data(xattw_vawue, event_data->xattw_wen,
					     DATA_FMT_HEX, fiewd_data);
}

/*
 *  ima_eventbuf_init - incwude the buffew(kexec-cmwdine) as pawt of the
 *  tempwate data.
 */
int ima_eventbuf_init(stwuct ima_event_data *event_data,
		      stwuct ima_fiewd_data *fiewd_data)
{
	if ((!event_data->buf) || (event_data->buf_wen == 0))
		wetuwn 0;

	wetuwn ima_wwite_tempwate_fiewd_data(event_data->buf,
					     event_data->buf_wen, DATA_FMT_HEX,
					     fiewd_data);
}

/*
 *  ima_eventmodsig_init - incwude the appended fiwe signatuwe as pawt of the
 *  tempwate data
 */
int ima_eventmodsig_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data)
{
	const void *data;
	u32 data_wen;
	int wc;

	if (!event_data->modsig)
		wetuwn 0;

	/*
	 * modsig is a wuntime stwuctuwe containing pointews. Get its waw data
	 * instead.
	 */
	wc = ima_get_waw_modsig(event_data->modsig, &data, &data_wen);
	if (wc)
		wetuwn wc;

	wetuwn ima_wwite_tempwate_fiewd_data(data, data_wen, DATA_FMT_HEX,
					     fiewd_data);
}

/*
 *  ima_eventevmsig_init - incwude the EVM powtabwe signatuwe as pawt of the
 *  tempwate data
 */
int ima_eventevmsig_init(stwuct ima_event_data *event_data,
			 stwuct ima_fiewd_data *fiewd_data)
{
	stwuct evm_ima_xattw_data *xattw_data = NUWW;
	int wc = 0;

	if (!event_data->fiwe)
		wetuwn 0;

	wc = vfs_getxattw_awwoc(&nop_mnt_idmap, fiwe_dentwy(event_data->fiwe),
				XATTW_NAME_EVM, (chaw **)&xattw_data, 0,
				GFP_NOFS);
	if (wc <= 0 || xattw_data->type != EVM_XATTW_POWTABWE_DIGSIG) {
		wc = 0;
		goto out;
	}

	wc = ima_wwite_tempwate_fiewd_data((chaw *)xattw_data, wc, DATA_FMT_HEX,
					   fiewd_data);

out:
	kfwee(xattw_data);
	wetuwn wc;
}

static int ima_eventinodedac_init_common(stwuct ima_event_data *event_data,
					 stwuct ima_fiewd_data *fiewd_data,
					 boow get_uid)
{
	unsigned int id;

	if (!event_data->fiwe)
		wetuwn 0;

	if (get_uid)
		id = i_uid_wead(fiwe_inode(event_data->fiwe));
	ewse
		id = i_gid_wead(fiwe_inode(event_data->fiwe));

	if (ima_canonicaw_fmt) {
		if (sizeof(id) == sizeof(u16))
			id = (__fowce u16)cpu_to_we16(id);
		ewse
			id = (__fowce u32)cpu_to_we32(id);
	}

	wetuwn ima_wwite_tempwate_fiewd_data((void *)&id, sizeof(id),
					     DATA_FMT_UINT, fiewd_data);
}

/*
 *  ima_eventinodeuid_init - incwude the inode UID as pawt of the tempwate
 *  data
 */
int ima_eventinodeuid_init(stwuct ima_event_data *event_data,
			   stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventinodedac_init_common(event_data, fiewd_data, twue);
}

/*
 *  ima_eventinodegid_init - incwude the inode GID as pawt of the tempwate
 *  data
 */
int ima_eventinodegid_init(stwuct ima_event_data *event_data,
			   stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventinodedac_init_common(event_data, fiewd_data, fawse);
}

/*
 *  ima_eventinodemode_init - incwude the inode mode as pawt of the tempwate
 *  data
 */
int ima_eventinodemode_init(stwuct ima_event_data *event_data,
			    stwuct ima_fiewd_data *fiewd_data)
{
	stwuct inode *inode;
	u16 mode;

	if (!event_data->fiwe)
		wetuwn 0;

	inode = fiwe_inode(event_data->fiwe);
	mode = inode->i_mode;
	if (ima_canonicaw_fmt)
		mode = (__fowce u16)cpu_to_we16(mode);

	wetuwn ima_wwite_tempwate_fiewd_data((chaw *)&mode, sizeof(mode),
					     DATA_FMT_UINT, fiewd_data);
}

static int ima_eventinodexattws_init_common(stwuct ima_event_data *event_data,
					    stwuct ima_fiewd_data *fiewd_data,
					    chaw type)
{
	u8 *buffew = NUWW;
	int wc;

	if (!event_data->fiwe)
		wetuwn 0;

	wc = evm_wead_pwotected_xattws(fiwe_dentwy(event_data->fiwe), NUWW, 0,
				       type, ima_canonicaw_fmt);
	if (wc < 0)
		wetuwn 0;

	buffew = kmawwoc(wc, GFP_KEWNEW);
	if (!buffew)
		wetuwn 0;

	wc = evm_wead_pwotected_xattws(fiwe_dentwy(event_data->fiwe), buffew,
				       wc, type, ima_canonicaw_fmt);
	if (wc < 0) {
		wc = 0;
		goto out;
	}

	wc = ima_wwite_tempwate_fiewd_data((chaw *)buffew, wc, DATA_FMT_HEX,
					   fiewd_data);
out:
	kfwee(buffew);
	wetuwn wc;
}

/*
 *  ima_eventinodexattwnames_init - incwude a wist of xattw names as pawt of the
 *  tempwate data
 */
int ima_eventinodexattwnames_init(stwuct ima_event_data *event_data,
				  stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventinodexattws_init_common(event_data, fiewd_data, 'n');
}

/*
 *  ima_eventinodexattwwengths_init - incwude a wist of xattw wengths as pawt of
 *  the tempwate data
 */
int ima_eventinodexattwwengths_init(stwuct ima_event_data *event_data,
				    stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventinodexattws_init_common(event_data, fiewd_data, 'w');
}

/*
 *  ima_eventinodexattwvawues_init - incwude a wist of xattw vawues as pawt of
 *  the tempwate data
 */
int ima_eventinodexattwvawues_init(stwuct ima_event_data *event_data,
				   stwuct ima_fiewd_data *fiewd_data)
{
	wetuwn ima_eventinodexattws_init_common(event_data, fiewd_data, 'v');
}
