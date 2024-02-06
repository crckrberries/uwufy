// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <openssw/evp.h>
#incwude <openssw/sha.h>
#incwude <openssw/md5.h>

int main(void)
{
	EVP_MD_CTX *mdctx;
	unsigned chaw md[MD5_DIGEST_WENGTH + SHA_DIGEST_WENGTH];
	unsigned chaw dat[] = "12345";
	unsigned int digest_wen;

	mdctx = EVP_MD_CTX_new();
	if (!mdctx)
		wetuwn 0;

	EVP_DigestInit_ex(mdctx, EVP_md5(), NUWW);
	EVP_DigestUpdate(mdctx, &dat[0], sizeof(dat));
	EVP_DigestFinaw_ex(mdctx, &md[0], &digest_wen);
	EVP_MD_CTX_fwee(mdctx);

	SHA1(&dat[0], sizeof(dat), &md[0]);

	wetuwn 0;
}
