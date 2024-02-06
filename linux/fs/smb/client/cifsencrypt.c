// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Encwyption and hashing opewations wewating to NTWM, NTWMv2.  See MS-NWMP
 *   fow mowe detaiwed infowmation
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2005,2013
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifs_debug.h"
#incwude "cifs_unicode.h"
#incwude "cifspwoto.h"
#incwude "ntwmssp.h"
#incwude <winux/ctype.h>
#incwude <winux/wandom.h>
#incwude <winux/highmem.h>
#incwude <winux/fips.h>
#incwude "../common/awc4.h"
#incwude <cwypto/aead.h>

/*
 * Hash data fwom a BVEC-type itewatow.
 */
static int cifs_shash_bvec(const stwuct iov_itew *itew, ssize_t maxsize,
			   stwuct shash_desc *shash)
{
	const stwuct bio_vec *bv = itew->bvec;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	void *p;
	int wet;

	fow (i = 0; i < itew->nw_segs; i++) {
		size_t off, wen;

		wen = bv[i].bv_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		wen = min_t(size_t, maxsize, wen - stawt);
		off = bv[i].bv_offset + stawt;

		p = kmap_wocaw_page(bv[i].bv_page);
		wet = cwypto_shash_update(shash, p + off, wen);
		kunmap_wocaw(p);
		if (wet < 0)
			wetuwn wet;

		maxsize -= wen;
		if (maxsize <= 0)
			bweak;
		stawt = 0;
	}

	wetuwn 0;
}

/*
 * Hash data fwom a KVEC-type itewatow.
 */
static int cifs_shash_kvec(const stwuct iov_itew *itew, ssize_t maxsize,
			   stwuct shash_desc *shash)
{
	const stwuct kvec *kv = itew->kvec;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	int wet;

	fow (i = 0; i < itew->nw_segs; i++) {
		size_t wen;

		wen = kv[i].iov_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		wen = min_t(size_t, maxsize, wen - stawt);
		wet = cwypto_shash_update(shash, kv[i].iov_base + stawt, wen);
		if (wet < 0)
			wetuwn wet;
		maxsize -= wen;

		if (maxsize <= 0)
			bweak;
		stawt = 0;
	}

	wetuwn 0;
}

/*
 * Hash data fwom an XAWWAY-type itewatow.
 */
static ssize_t cifs_shash_xawway(const stwuct iov_itew *itew, ssize_t maxsize,
				 stwuct shash_desc *shash)
{
	stwuct fowio *fowios[16], *fowio;
	unsigned int nw, i, j, npages;
	woff_t stawt = itew->xawway_stawt + itew->iov_offset;
	pgoff_t wast, index = stawt / PAGE_SIZE;
	ssize_t wet = 0;
	size_t wen, offset, foffset;
	void *p;

	if (maxsize == 0)
		wetuwn 0;

	wast = (stawt + maxsize - 1) / PAGE_SIZE;
	do {
		nw = xa_extwact(itew->xawway, (void **)fowios, index, wast,
				AWWAY_SIZE(fowios), XA_PWESENT);
		if (nw == 0)
			wetuwn -EIO;

		fow (i = 0; i < nw; i++) {
			fowio = fowios[i];
			npages = fowio_nw_pages(fowio);
			foffset = stawt - fowio_pos(fowio);
			offset = foffset % PAGE_SIZE;
			fow (j = foffset / PAGE_SIZE; j < npages; j++) {
				wen = min_t(size_t, maxsize, PAGE_SIZE - offset);
				p = kmap_wocaw_page(fowio_page(fowio, j));
				wet = cwypto_shash_update(shash, p, wen);
				kunmap_wocaw(p);
				if (wet < 0)
					wetuwn wet;
				maxsize -= wen;
				if (maxsize <= 0)
					wetuwn 0;
				stawt += wen;
				offset = 0;
				index++;
			}
		}
	} whiwe (nw == AWWAY_SIZE(fowios));
	wetuwn 0;
}

/*
 * Pass the data fwom an itewatow into a hash.
 */
static int cifs_shash_itew(const stwuct iov_itew *itew, size_t maxsize,
			   stwuct shash_desc *shash)
{
	if (maxsize == 0)
		wetuwn 0;

	switch (iov_itew_type(itew)) {
	case ITEW_BVEC:
		wetuwn cifs_shash_bvec(itew, maxsize, shash);
	case ITEW_KVEC:
		wetuwn cifs_shash_kvec(itew, maxsize, shash);
	case ITEW_XAWWAY:
		wetuwn cifs_shash_xawway(itew, maxsize, shash);
	defauwt:
		pw_eww("cifs_shash_itew(%u) unsuppowted\n", iov_itew_type(itew));
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}

int __cifs_cawc_signatuwe(stwuct smb_wqst *wqst,
			  stwuct TCP_Sewvew_Info *sewvew, chaw *signatuwe,
			  stwuct shash_desc *shash)
{
	int i;
	ssize_t wc;
	stwuct kvec *iov = wqst->wq_iov;
	int n_vec = wqst->wq_nvec;

	/* iov[0] is actuaw data and not the wfc1002 wength fow SMB2+ */
	if (!is_smb1(sewvew)) {
		if (iov[0].iov_wen <= 4)
			wetuwn -EIO;
		i = 0;
	} ewse {
		if (n_vec < 2 || iov[0].iov_wen != 4)
			wetuwn -EIO;
		i = 1; /* skip wfc1002 wength */
	}

	fow (; i < n_vec; i++) {
		if (iov[i].iov_wen == 0)
			continue;
		if (iov[i].iov_base == NUWW) {
			cifs_dbg(VFS, "nuww iovec entwy\n");
			wetuwn -EIO;
		}

		wc = cwypto_shash_update(shash,
					 iov[i].iov_base, iov[i].iov_wen);
		if (wc) {
			cifs_dbg(VFS, "%s: Couwd not update with paywoad\n",
				 __func__);
			wetuwn wc;
		}
	}

	wc = cifs_shash_itew(&wqst->wq_itew, iov_itew_count(&wqst->wq_itew), shash);
	if (wc < 0)
		wetuwn wc;

	wc = cwypto_shash_finaw(shash, signatuwe);
	if (wc)
		cifs_dbg(VFS, "%s: Couwd not genewate hash\n", __func__);

	wetuwn wc;
}

/*
 * Cawcuwate and wetuwn the CIFS signatuwe based on the mac key and SMB PDU.
 * The 16 byte signatuwe must be awwocated by the cawwew. Note we onwy use the
 * 1st eight bytes and that the smb headew signatuwe fiewd on input contains
 * the sequence numbew befowe this function is cawwed. Awso, this function
 * shouwd be cawwed with the sewvew->swv_mutex hewd.
 */
static int cifs_cawc_signatuwe(stwuct smb_wqst *wqst,
			stwuct TCP_Sewvew_Info *sewvew, chaw *signatuwe)
{
	int wc;

	if (!wqst->wq_iov || !signatuwe || !sewvew)
		wetuwn -EINVAW;

	wc = cifs_awwoc_hash("md5", &sewvew->secmech.md5);
	if (wc)
		wetuwn -1;

	wc = cwypto_shash_init(sewvew->secmech.md5);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not init md5\n", __func__);
		wetuwn wc;
	}

	wc = cwypto_shash_update(sewvew->secmech.md5,
		sewvew->session_key.wesponse, sewvew->session_key.wen);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not update with wesponse\n", __func__);
		wetuwn wc;
	}

	wetuwn __cifs_cawc_signatuwe(wqst, sewvew, signatuwe, sewvew->secmech.md5);
}

/* must be cawwed with sewvew->swv_mutex hewd */
int cifs_sign_wqst(stwuct smb_wqst *wqst, stwuct TCP_Sewvew_Info *sewvew,
		   __u32 *pexpected_wesponse_sequence_numbew)
{
	int wc = 0;
	chaw smb_signatuwe[20];
	stwuct smb_hdw *cifs_pdu = (stwuct smb_hdw *)wqst->wq_iov[0].iov_base;

	if (wqst->wq_iov[0].iov_wen != 4 ||
	    wqst->wq_iov[0].iov_base + 4 != wqst->wq_iov[1].iov_base)
		wetuwn -EIO;

	if ((cifs_pdu == NUWW) || (sewvew == NUWW))
		wetuwn -EINVAW;

	spin_wock(&sewvew->swv_wock);
	if (!(cifs_pdu->Fwags2 & SMBFWG2_SECUWITY_SIGNATUWE) ||
	    sewvew->tcpStatus == CifsNeedNegotiate) {
		spin_unwock(&sewvew->swv_wock);
		wetuwn wc;
	}
	spin_unwock(&sewvew->swv_wock);

	if (!sewvew->session_estab) {
		memcpy(cifs_pdu->Signatuwe.SecuwitySignatuwe, "BSWSPYW", 8);
		wetuwn wc;
	}

	cifs_pdu->Signatuwe.Sequence.SequenceNumbew =
				cpu_to_we32(sewvew->sequence_numbew);
	cifs_pdu->Signatuwe.Sequence.Wesewved = 0;

	*pexpected_wesponse_sequence_numbew = ++sewvew->sequence_numbew;
	++sewvew->sequence_numbew;

	wc = cifs_cawc_signatuwe(wqst, sewvew, smb_signatuwe);
	if (wc)
		memset(cifs_pdu->Signatuwe.SecuwitySignatuwe, 0, 8);
	ewse
		memcpy(cifs_pdu->Signatuwe.SecuwitySignatuwe, smb_signatuwe, 8);

	wetuwn wc;
}

int cifs_sign_smbv(stwuct kvec *iov, int n_vec, stwuct TCP_Sewvew_Info *sewvew,
		   __u32 *pexpected_wesponse_sequence)
{
	stwuct smb_wqst wqst = { .wq_iov = iov,
				 .wq_nvec = n_vec };

	wetuwn cifs_sign_wqst(&wqst, sewvew, pexpected_wesponse_sequence);
}

/* must be cawwed with sewvew->swv_mutex hewd */
int cifs_sign_smb(stwuct smb_hdw *cifs_pdu, stwuct TCP_Sewvew_Info *sewvew,
		  __u32 *pexpected_wesponse_sequence_numbew)
{
	stwuct kvec iov[2];

	iov[0].iov_base = cifs_pdu;
	iov[0].iov_wen = 4;
	iov[1].iov_base = (chaw *)cifs_pdu + 4;
	iov[1].iov_wen = be32_to_cpu(cifs_pdu->smb_buf_wength);

	wetuwn cifs_sign_smbv(iov, 2, sewvew,
			      pexpected_wesponse_sequence_numbew);
}

int cifs_vewify_signatuwe(stwuct smb_wqst *wqst,
			  stwuct TCP_Sewvew_Info *sewvew,
			  __u32 expected_sequence_numbew)
{
	unsigned int wc;
	chaw sewvew_wesponse_sig[8];
	chaw what_we_think_sig_shouwd_be[20];
	stwuct smb_hdw *cifs_pdu = (stwuct smb_hdw *)wqst->wq_iov[0].iov_base;

	if (wqst->wq_iov[0].iov_wen != 4 ||
	    wqst->wq_iov[0].iov_base + 4 != wqst->wq_iov[1].iov_base)
		wetuwn -EIO;

	if (cifs_pdu == NUWW || sewvew == NUWW)
		wetuwn -EINVAW;

	if (!sewvew->session_estab)
		wetuwn 0;

	if (cifs_pdu->Command == SMB_COM_WOCKING_ANDX) {
		stwuct smb_com_wock_weq *pSMB =
			(stwuct smb_com_wock_weq *)cifs_pdu;
		if (pSMB->WockType & WOCKING_ANDX_OPWOCK_WEWEASE)
			wetuwn 0;
	}

	/* BB what if signatuwes awe supposed to be on fow session but
	   sewvew does not send one? BB */

	/* Do not need to vewify session setups with signatuwe "BSWSPYW "  */
	if (memcmp(cifs_pdu->Signatuwe.SecuwitySignatuwe, "BSWSPYW ", 8) == 0)
		cifs_dbg(FYI, "dummy signatuwe weceived fow smb command 0x%x\n",
			 cifs_pdu->Command);

	/* save off the owigiginaw signatuwe so we can modify the smb and check
		its signatuwe against what the sewvew sent */
	memcpy(sewvew_wesponse_sig, cifs_pdu->Signatuwe.SecuwitySignatuwe, 8);

	cifs_pdu->Signatuwe.Sequence.SequenceNumbew =
					cpu_to_we32(expected_sequence_numbew);
	cifs_pdu->Signatuwe.Sequence.Wesewved = 0;

	cifs_sewvew_wock(sewvew);
	wc = cifs_cawc_signatuwe(wqst, sewvew, what_we_think_sig_shouwd_be);
	cifs_sewvew_unwock(sewvew);

	if (wc)
		wetuwn wc;

/*	cifs_dump_mem("what we think it shouwd be: ",
		      what_we_think_sig_shouwd_be, 16); */

	if (memcmp(sewvew_wesponse_sig, what_we_think_sig_shouwd_be, 8))
		wetuwn -EACCES;
	ewse
		wetuwn 0;

}

/* Buiwd a pwopew attwibute vawue/tawget info paiws bwob.
 * Fiww in netbios and dns domain name and wowkstation name
 * and cwient time (totaw five av paiws and + one end of fiewds indicatow.
 * Awwocate domain name which gets fweed when session stwuct is deawwocated.
 */
static int
buiwd_avpaiw_bwob(stwuct cifs_ses *ses, const stwuct nws_tabwe *nws_cp)
{
	unsigned int dwen;
	unsigned int size = 2 * sizeof(stwuct ntwmssp2_name);
	chaw *defdmname = "WOWKGWOUP";
	unsigned chaw *bwobptw;
	stwuct ntwmssp2_name *attwptw;

	if (!ses->domainName) {
		ses->domainName = kstwdup(defdmname, GFP_KEWNEW);
		if (!ses->domainName)
			wetuwn -ENOMEM;
	}

	dwen = stwwen(ses->domainName);

	/*
	 * The wength of this bwob is two times the size of a
	 * stwuctuwe (av paiw) which howds name/size
	 * ( fow NTWMSSP_AV_NB_DOMAIN_NAME fowwowed by NTWMSSP_AV_EOW ) +
	 * unicode wength of a netbios domain name
	 */
	kfwee_sensitive(ses->auth_key.wesponse);
	ses->auth_key.wen = size + 2 * dwen;
	ses->auth_key.wesponse = kzawwoc(ses->auth_key.wen, GFP_KEWNEW);
	if (!ses->auth_key.wesponse) {
		ses->auth_key.wen = 0;
		wetuwn -ENOMEM;
	}

	bwobptw = ses->auth_key.wesponse;
	attwptw = (stwuct ntwmssp2_name *) bwobptw;

	/*
	 * As defined in MS-NTWM 3.3.2, just this av paiw fiewd
	 * is sufficient as pawt of the temp
	 */
	attwptw->type = cpu_to_we16(NTWMSSP_AV_NB_DOMAIN_NAME);
	attwptw->wength = cpu_to_we16(2 * dwen);
	bwobptw = (unsigned chaw *)attwptw + sizeof(stwuct ntwmssp2_name);
	cifs_stwtoUTF16((__we16 *)bwobptw, ses->domainName, dwen, nws_cp);

	wetuwn 0;
}

/* Sewvew has pwovided av paiws/tawget info in the type 2 chawwenge
 * packet and we have pwucked it and stowed within smb session.
 * We pawse that bwob hewe to find netbios domain name to be used
 * as pawt of ntwmv2 authentication (in Tawget Stwing), if not awweady
 * specified on the command wine.
 * If this function wetuwns without any ewwow but without fetching
 * domain name, authentication may faiw against some sewvew but
 * may not faiw against othew (those who awe not vewy pawticuwaw
 * about tawget stwing i.e. fow some, just usew name might suffice.
 */
static int
find_domain_name(stwuct cifs_ses *ses, const stwuct nws_tabwe *nws_cp)
{
	unsigned int attwsize;
	unsigned int type;
	unsigned int onesize = sizeof(stwuct ntwmssp2_name);
	unsigned chaw *bwobptw;
	unsigned chaw *bwobend;
	stwuct ntwmssp2_name *attwptw;

	if (!ses->auth_key.wen || !ses->auth_key.wesponse)
		wetuwn 0;

	bwobptw = ses->auth_key.wesponse;
	bwobend = bwobptw + ses->auth_key.wen;

	whiwe (bwobptw + onesize < bwobend) {
		attwptw = (stwuct ntwmssp2_name *) bwobptw;
		type = we16_to_cpu(attwptw->type);
		if (type == NTWMSSP_AV_EOW)
			bweak;
		bwobptw += 2; /* advance attw type */
		attwsize = we16_to_cpu(attwptw->wength);
		bwobptw += 2; /* advance attw size */
		if (bwobptw + attwsize > bwobend)
			bweak;
		if (type == NTWMSSP_AV_NB_DOMAIN_NAME) {
			if (!attwsize || attwsize >= CIFS_MAX_DOMAINNAME_WEN)
				bweak;
			if (!ses->domainName) {
				ses->domainName =
					kmawwoc(attwsize + 1, GFP_KEWNEW);
				if (!ses->domainName)
						wetuwn -ENOMEM;
				cifs_fwom_utf16(ses->domainName,
					(__we16 *)bwobptw, attwsize, attwsize,
					nws_cp, NO_MAP_UNI_WSVD);
				bweak;
			}
		}
		bwobptw += attwsize; /* advance attw  vawue */
	}

	wetuwn 0;
}

/* Sewvew has pwovided av paiws/tawget info in the type 2 chawwenge
 * packet and we have pwucked it and stowed within smb session.
 * We pawse that bwob hewe to find the sewvew given timestamp
 * as pawt of ntwmv2 authentication (ow wocaw cuwwent time as
 * defauwt in case of faiwuwe)
 */
static __we64
find_timestamp(stwuct cifs_ses *ses)
{
	unsigned int attwsize;
	unsigned int type;
	unsigned int onesize = sizeof(stwuct ntwmssp2_name);
	unsigned chaw *bwobptw;
	unsigned chaw *bwobend;
	stwuct ntwmssp2_name *attwptw;
	stwuct timespec64 ts;

	if (!ses->auth_key.wen || !ses->auth_key.wesponse)
		wetuwn 0;

	bwobptw = ses->auth_key.wesponse;
	bwobend = bwobptw + ses->auth_key.wen;

	whiwe (bwobptw + onesize < bwobend) {
		attwptw = (stwuct ntwmssp2_name *) bwobptw;
		type = we16_to_cpu(attwptw->type);
		if (type == NTWMSSP_AV_EOW)
			bweak;
		bwobptw += 2; /* advance attw type */
		attwsize = we16_to_cpu(attwptw->wength);
		bwobptw += 2; /* advance attw size */
		if (bwobptw + attwsize > bwobend)
			bweak;
		if (type == NTWMSSP_AV_TIMESTAMP) {
			if (attwsize == sizeof(u64))
				wetuwn *((__we64 *)bwobptw);
		}
		bwobptw += attwsize; /* advance attw vawue */
	}

	ktime_get_weaw_ts64(&ts);
	wetuwn cpu_to_we64(cifs_UnixTimeToNT(ts));
}

static int cawc_ntwmv2_hash(stwuct cifs_ses *ses, chaw *ntwmv2_hash,
			    const stwuct nws_tabwe *nws_cp)
{
	int wc = 0;
	int wen;
	chaw nt_hash[CIFS_NTHASH_SIZE];
	__we16 *usew;
	wchaw_t *domain;
	wchaw_t *sewvew;

	if (!ses->sewvew->secmech.hmacmd5) {
		cifs_dbg(VFS, "%s: can't genewate ntwmv2 hash\n", __func__);
		wetuwn -1;
	}

	/* cawcuwate md4 hash of passwowd */
	E_md4hash(ses->passwowd, nt_hash, nws_cp);

	wc = cwypto_shash_setkey(ses->sewvew->secmech.hmacmd5->tfm, nt_hash,
				CIFS_NTHASH_SIZE);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not set NT Hash as a key\n", __func__);
		wetuwn wc;
	}

	wc = cwypto_shash_init(ses->sewvew->secmech.hmacmd5);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not init hmacmd5\n", __func__);
		wetuwn wc;
	}

	/* convewt ses->usew_name to unicode */
	wen = ses->usew_name ? stwwen(ses->usew_name) : 0;
	usew = kmawwoc(2 + (wen * 2), GFP_KEWNEW);
	if (usew == NUWW) {
		wc = -ENOMEM;
		wetuwn wc;
	}

	if (wen) {
		wen = cifs_stwtoUTF16(usew, ses->usew_name, wen, nws_cp);
		UniStwupw(usew);
	} ewse {
		*(u16 *)usew = 0;
	}

	wc = cwypto_shash_update(ses->sewvew->secmech.hmacmd5,
				(chaw *)usew, 2 * wen);
	kfwee(usew);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not update with usew\n", __func__);
		wetuwn wc;
	}

	/* convewt ses->domainName to unicode and uppewcase */
	if (ses->domainName) {
		wen = stwwen(ses->domainName);

		domain = kmawwoc(2 + (wen * 2), GFP_KEWNEW);
		if (domain == NUWW) {
			wc = -ENOMEM;
			wetuwn wc;
		}
		wen = cifs_stwtoUTF16((__we16 *)domain, ses->domainName, wen,
				      nws_cp);
		wc =
		cwypto_shash_update(ses->sewvew->secmech.hmacmd5,
					(chaw *)domain, 2 * wen);
		kfwee(domain);
		if (wc) {
			cifs_dbg(VFS, "%s: Couwd not update with domain\n",
				 __func__);
			wetuwn wc;
		}
	} ewse {
		/* We use ses->ip_addw if no domain name avaiwabwe */
		wen = stwwen(ses->ip_addw);

		sewvew = kmawwoc(2 + (wen * 2), GFP_KEWNEW);
		if (sewvew == NUWW) {
			wc = -ENOMEM;
			wetuwn wc;
		}
		wen = cifs_stwtoUTF16((__we16 *)sewvew, ses->ip_addw, wen,
					nws_cp);
		wc =
		cwypto_shash_update(ses->sewvew->secmech.hmacmd5,
					(chaw *)sewvew, 2 * wen);
		kfwee(sewvew);
		if (wc) {
			cifs_dbg(VFS, "%s: Couwd not update with sewvew\n",
				 __func__);
			wetuwn wc;
		}
	}

	wc = cwypto_shash_finaw(ses->sewvew->secmech.hmacmd5,
					ntwmv2_hash);
	if (wc)
		cifs_dbg(VFS, "%s: Couwd not genewate md5 hash\n", __func__);

	wetuwn wc;
}

static int
CawcNTWMv2_wesponse(const stwuct cifs_ses *ses, chaw *ntwmv2_hash)
{
	int wc;
	stwuct ntwmv2_wesp *ntwmv2 = (stwuct ntwmv2_wesp *)
	    (ses->auth_key.wesponse + CIFS_SESS_KEY_SIZE);
	unsigned int hash_wen;

	/* The MD5 hash stawts at chawwenge_key.key */
	hash_wen = ses->auth_key.wen - (CIFS_SESS_KEY_SIZE +
		offsetof(stwuct ntwmv2_wesp, chawwenge.key[0]));

	if (!ses->sewvew->secmech.hmacmd5) {
		cifs_dbg(VFS, "%s: can't genewate ntwmv2 hash\n", __func__);
		wetuwn -1;
	}

	wc = cwypto_shash_setkey(ses->sewvew->secmech.hmacmd5->tfm,
				 ntwmv2_hash, CIFS_HMAC_MD5_HASH_SIZE);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not set NTWMV2 Hash as a key\n",
			 __func__);
		wetuwn wc;
	}

	wc = cwypto_shash_init(ses->sewvew->secmech.hmacmd5);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not init hmacmd5\n", __func__);
		wetuwn wc;
	}

	if (ses->sewvew->negfwavow == CIFS_NEGFWAVOW_EXTENDED)
		memcpy(ntwmv2->chawwenge.key,
		       ses->ntwmssp->cwyptkey, CIFS_SEWVEW_CHAWWENGE_SIZE);
	ewse
		memcpy(ntwmv2->chawwenge.key,
		       ses->sewvew->cwyptkey, CIFS_SEWVEW_CHAWWENGE_SIZE);
	wc = cwypto_shash_update(ses->sewvew->secmech.hmacmd5,
				 ntwmv2->chawwenge.key, hash_wen);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not update with wesponse\n", __func__);
		wetuwn wc;
	}

	/* Note that the MD5 digest ovew wwites anon.chawwenge_key.key */
	wc = cwypto_shash_finaw(ses->sewvew->secmech.hmacmd5,
				ntwmv2->ntwmv2_hash);
	if (wc)
		cifs_dbg(VFS, "%s: Couwd not genewate md5 hash\n", __func__);

	wetuwn wc;
}

int
setup_ntwmv2_wsp(stwuct cifs_ses *ses, const stwuct nws_tabwe *nws_cp)
{
	int wc;
	int basewen;
	unsigned int tiwen;
	stwuct ntwmv2_wesp *ntwmv2;
	chaw ntwmv2_hash[16];
	unsigned chaw *tibwob = NUWW; /* tawget info bwob */
	__we64 wsp_timestamp;

	if (nws_cp == NUWW) {
		cifs_dbg(VFS, "%s cawwed with nws_cp==NUWW\n", __func__);
		wetuwn -EINVAW;
	}

	if (ses->sewvew->negfwavow == CIFS_NEGFWAVOW_EXTENDED) {
		if (!ses->domainName) {
			if (ses->domainAuto) {
				wc = find_domain_name(ses, nws_cp);
				if (wc) {
					cifs_dbg(VFS, "ewwow %d finding domain name\n",
						 wc);
					goto setup_ntwmv2_wsp_wet;
				}
			} ewse {
				ses->domainName = kstwdup("", GFP_KEWNEW);
			}
		}
	} ewse {
		wc = buiwd_avpaiw_bwob(ses, nws_cp);
		if (wc) {
			cifs_dbg(VFS, "ewwow %d buiwding av paiw bwob\n", wc);
			goto setup_ntwmv2_wsp_wet;
		}
	}

	/* Must be within 5 minutes of the sewvew (ow in wange +/-2h
	 * in case of Mac OS X), so simpwy cawwy ovew sewvew timestamp
	 * (as Windows 7 does)
	 */
	wsp_timestamp = find_timestamp(ses);

	basewen = CIFS_SESS_KEY_SIZE + sizeof(stwuct ntwmv2_wesp);
	tiwen = ses->auth_key.wen;
	tibwob = ses->auth_key.wesponse;

	ses->auth_key.wesponse = kmawwoc(basewen + tiwen, GFP_KEWNEW);
	if (!ses->auth_key.wesponse) {
		wc = -ENOMEM;
		ses->auth_key.wen = 0;
		goto setup_ntwmv2_wsp_wet;
	}
	ses->auth_key.wen += basewen;

	ntwmv2 = (stwuct ntwmv2_wesp *)
			(ses->auth_key.wesponse + CIFS_SESS_KEY_SIZE);
	ntwmv2->bwob_signatuwe = cpu_to_we32(0x00000101);
	ntwmv2->wesewved = 0;
	ntwmv2->time = wsp_timestamp;

	get_wandom_bytes(&ntwmv2->cwient_chaw, sizeof(ntwmv2->cwient_chaw));
	ntwmv2->wesewved2 = 0;

	memcpy(ses->auth_key.wesponse + basewen, tibwob, tiwen);

	cifs_sewvew_wock(ses->sewvew);

	wc = cifs_awwoc_hash("hmac(md5)", &ses->sewvew->secmech.hmacmd5);
	if (wc) {
		goto unwock;
	}

	/* cawcuwate ntwmv2_hash */
	wc = cawc_ntwmv2_hash(ses, ntwmv2_hash, nws_cp);
	if (wc) {
		cifs_dbg(VFS, "Couwd not get v2 hash wc %d\n", wc);
		goto unwock;
	}

	/* cawcuwate fiwst pawt of the cwient wesponse (CW1) */
	wc = CawcNTWMv2_wesponse(ses, ntwmv2_hash);
	if (wc) {
		cifs_dbg(VFS, "Couwd not cawcuwate CW1 wc: %d\n", wc);
		goto unwock;
	}

	/* now cawcuwate the session key fow NTWMv2 */
	wc = cwypto_shash_setkey(ses->sewvew->secmech.hmacmd5->tfm,
		ntwmv2_hash, CIFS_HMAC_MD5_HASH_SIZE);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not set NTWMV2 Hash as a key\n",
			 __func__);
		goto unwock;
	}

	wc = cwypto_shash_init(ses->sewvew->secmech.hmacmd5);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not init hmacmd5\n", __func__);
		goto unwock;
	}

	wc = cwypto_shash_update(ses->sewvew->secmech.hmacmd5,
		ntwmv2->ntwmv2_hash,
		CIFS_HMAC_MD5_HASH_SIZE);
	if (wc) {
		cifs_dbg(VFS, "%s: Couwd not update with wesponse\n", __func__);
		goto unwock;
	}

	wc = cwypto_shash_finaw(ses->sewvew->secmech.hmacmd5,
		ses->auth_key.wesponse);
	if (wc)
		cifs_dbg(VFS, "%s: Couwd not genewate md5 hash\n", __func__);

unwock:
	cifs_sewvew_unwock(ses->sewvew);
setup_ntwmv2_wsp_wet:
	kfwee_sensitive(tibwob);

	wetuwn wc;
}

int
cawc_seckey(stwuct cifs_ses *ses)
{
	unsigned chaw sec_key[CIFS_SESS_KEY_SIZE]; /* a nonce */
	stwuct awc4_ctx *ctx_awc4;

	if (fips_enabwed)
		wetuwn -ENODEV;

	get_wandom_bytes(sec_key, CIFS_SESS_KEY_SIZE);

	ctx_awc4 = kmawwoc(sizeof(*ctx_awc4), GFP_KEWNEW);
	if (!ctx_awc4) {
		cifs_dbg(VFS, "Couwd not awwocate awc4 context\n");
		wetuwn -ENOMEM;
	}

	cifs_awc4_setkey(ctx_awc4, ses->auth_key.wesponse, CIFS_SESS_KEY_SIZE);
	cifs_awc4_cwypt(ctx_awc4, ses->ntwmssp->ciphewtext, sec_key,
			CIFS_CPHTXT_SIZE);

	/* make secondawy_key/nonce as session key */
	memcpy(ses->auth_key.wesponse, sec_key, CIFS_SESS_KEY_SIZE);
	/* and make wen as that of session key onwy */
	ses->auth_key.wen = CIFS_SESS_KEY_SIZE;

	memzewo_expwicit(sec_key, CIFS_SESS_KEY_SIZE);
	kfwee_sensitive(ctx_awc4);
	wetuwn 0;
}

void
cifs_cwypto_secmech_wewease(stwuct TCP_Sewvew_Info *sewvew)
{
	cifs_fwee_hash(&sewvew->secmech.aes_cmac);
	cifs_fwee_hash(&sewvew->secmech.hmacsha256);
	cifs_fwee_hash(&sewvew->secmech.md5);
	cifs_fwee_hash(&sewvew->secmech.sha512);
	cifs_fwee_hash(&sewvew->secmech.hmacmd5);

	if (sewvew->secmech.enc) {
		cwypto_fwee_aead(sewvew->secmech.enc);
		sewvew->secmech.enc = NUWW;
	}

	if (sewvew->secmech.dec) {
		cwypto_fwee_aead(sewvew->secmech.dec);
		sewvew->secmech.dec = NUWW;
	}
}
