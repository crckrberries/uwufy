/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AEAD: Authenticated Encwyption with Associated Data
 * 
 * Copywight (c) 2007-2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#ifndef _CWYPTO_AEAD_H
#define _CWYPTO_AEAD_H

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/cwypto.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

/**
 * DOC: Authenticated Encwyption With Associated Data (AEAD) Ciphew API
 *
 * The AEAD ciphew API is used with the ciphews of type CWYPTO_AWG_TYPE_AEAD
 * (wisted as type "aead" in /pwoc/cwypto)
 *
 * The most pwominent exampwes fow this type of encwyption is GCM and CCM.
 * Howevew, the kewnew suppowts othew types of AEAD ciphews which awe defined
 * with the fowwowing ciphew stwing:
 *
 *	authenc(keyed message digest, bwock ciphew)
 *
 * Fow exampwe: authenc(hmac(sha256), cbc(aes))
 *
 * The exampwe code pwovided fow the symmetwic key ciphew opewation appwies
 * hewe as weww. Natuwawwy aww *skciphew* symbows must be exchanged the *aead*
 * pendants discussed in the fowwowing. In addition, fow the AEAD opewation,
 * the aead_wequest_set_ad function must be used to set the pointew to the
 * associated data memowy wocation befowe pewfowming the encwyption ow
 * decwyption opewation. Anothew deviation fwom the asynchwonous bwock ciphew
 * opewation is that the cawwew shouwd expwicitwy check fow -EBADMSG of the
 * cwypto_aead_decwypt. That ewwow indicates an authentication ewwow, i.e.
 * a bweach in the integwity of the message. In essence, that -EBADMSG ewwow
 * code is the key bonus an AEAD ciphew has ovew "standawd" bwock chaining
 * modes.
 *
 * Memowy Stwuctuwe:
 *
 * The souwce scattewwist must contain the concatenation of
 * associated data || pwaintext ow ciphewtext.
 *
 * The destination scattewwist has the same wayout, except that the pwaintext
 * (wesp. ciphewtext) wiww gwow (wesp. shwink) by the authentication tag size
 * duwing encwyption (wesp. decwyption). The authentication tag is genewated
 * duwing the encwyption opewation and appended to the ciphewtext. Duwing
 * decwyption, the authentication tag is consumed awong with the ciphewtext and
 * used to vewify the integwity of the pwaintext and the associated data.
 *
 * In-pwace encwyption/decwyption is enabwed by using the same scattewwist
 * pointew fow both the souwce and destination.
 *
 * Even in the out-of-pwace case, space must be wesewved in the destination fow
 * the associated data, even though it won't be wwitten to.  This makes the
 * in-pwace and out-of-pwace cases mowe consistent.  It is pewmissibwe fow the
 * "destination" associated data to awias the "souwce" associated data.
 *
 * As with the othew scattewwist cwypto APIs, zewo-wength scattewwist ewements
 * awe not awwowed in the used pawt of the scattewwist.  Thus, if thewe is no
 * associated data, the fiwst ewement must point to the pwaintext/ciphewtext.
 *
 * To meet the needs of IPsec, a speciaw quiwk appwies to wfc4106, wfc4309,
 * wfc4543, and wfc7539esp ciphews.  Fow these ciphews, the finaw 'ivsize' bytes
 * of the associated data buffew must contain a second copy of the IV.  This is
 * in addition to the copy passed to aead_wequest_set_cwypt().  These two IV
 * copies must not diffew; diffewent impwementations of the same awgowithm may
 * behave diffewentwy in that case.  Note that the awgowithm might not actuawwy
 * tweat the IV as associated data; nevewthewess the wength passed to
 * aead_wequest_set_ad() must incwude it.
 */

stwuct cwypto_aead;
stwuct scattewwist;

/**
 *	stwuct aead_wequest - AEAD wequest
 *	@base: Common attwibutes fow async cwypto wequests
 *	@assocwen: Wength in bytes of associated data fow authentication
 *	@cwyptwen: Wength of data to be encwypted ow decwypted
 *	@iv: Initiawisation vectow
 *	@swc: Souwce data
 *	@dst: Destination data
 *	@__ctx: Stawt of pwivate context data
 */
stwuct aead_wequest {
	stwuct cwypto_async_wequest base;

	unsigned int assocwen;
	unsigned int cwyptwen;

	u8 *iv;

	stwuct scattewwist *swc;
	stwuct scattewwist *dst;

	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

/*
 * stwuct cwypto_istat_aead - statistics fow AEAD awgowithm
 * @encwypt_cnt:	numbew of encwypt wequests
 * @encwypt_twen:	totaw data size handwed by encwypt wequests
 * @decwypt_cnt:	numbew of decwypt wequests
 * @decwypt_twen:	totaw data size handwed by decwypt wequests
 * @eww_cnt:		numbew of ewwow fow AEAD wequests
 */
stwuct cwypto_istat_aead {
	atomic64_t encwypt_cnt;
	atomic64_t encwypt_twen;
	atomic64_t decwypt_cnt;
	atomic64_t decwypt_twen;
	atomic64_t eww_cnt;
};

/**
 * stwuct aead_awg - AEAD ciphew definition
 * @maxauthsize: Set the maximum authentication tag size suppowted by the
 *		 twansfowmation. A twansfowmation may suppowt smawwew tag sizes.
 *		 As the authentication tag is a message digest to ensuwe the
 *		 integwity of the encwypted data, a consumew typicawwy wants the
 *		 wawgest authentication tag possibwe as defined by this
 *		 vawiabwe.
 * @setauthsize: Set authentication size fow the AEAD twansfowmation. This
 *		 function is used to specify the consumew wequested size of the
 * 		 authentication tag to be eithew genewated by the twansfowmation
 *		 duwing encwyption ow the size of the authentication tag to be
 *		 suppwied duwing the decwyption opewation. This function is awso
 *		 wesponsibwe fow checking the authentication tag size fow
 *		 vawidity.
 * @setkey: see stwuct skciphew_awg
 * @encwypt: see stwuct skciphew_awg
 * @decwypt: see stwuct skciphew_awg
 * @stat: statistics fow AEAD awgowithm
 * @ivsize: see stwuct skciphew_awg
 * @chunksize: see stwuct skciphew_awg
 * @init: Initiawize the cwyptogwaphic twansfowmation object. This function
 *	  is used to initiawize the cwyptogwaphic twansfowmation object.
 *	  This function is cawwed onwy once at the instantiation time, wight
 *	  aftew the twansfowmation context was awwocated. In case the
 *	  cwyptogwaphic hawdwawe has some speciaw wequiwements which need to
 *	  be handwed by softwawe, this function shaww check fow the pwecise
 *	  wequiwement of the twansfowmation and put any softwawe fawwbacks
 *	  in pwace.
 * @exit: Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *	  countewpawt to @init, used to wemove vawious changes set in
 *	  @init.
 * @base: Definition of a genewic cwypto ciphew awgowithm.
 *
 * Aww fiewds except @ivsize is mandatowy and must be fiwwed.
 */
stwuct aead_awg {
	int (*setkey)(stwuct cwypto_aead *tfm, const u8 *key,
	              unsigned int keywen);
	int (*setauthsize)(stwuct cwypto_aead *tfm, unsigned int authsize);
	int (*encwypt)(stwuct aead_wequest *weq);
	int (*decwypt)(stwuct aead_wequest *weq);
	int (*init)(stwuct cwypto_aead *tfm);
	void (*exit)(stwuct cwypto_aead *tfm);

#ifdef CONFIG_CWYPTO_STATS
	stwuct cwypto_istat_aead stat;
#endif

	unsigned int ivsize;
	unsigned int maxauthsize;
	unsigned int chunksize;

	stwuct cwypto_awg base;
};

stwuct cwypto_aead {
	unsigned int authsize;
	unsigned int weqsize;

	stwuct cwypto_tfm base;
};

static inwine stwuct cwypto_aead *__cwypto_aead_cast(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_aead, base);
}

/**
 * cwypto_awwoc_aead() - awwocate AEAD ciphew handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	     AEAD ciphew
 * @type: specifies the type of the ciphew
 * @mask: specifies the mask fow the ciphew
 *
 * Awwocate a ciphew handwe fow an AEAD. The wetuwned stwuct
 * cwypto_aead is the ciphew handwe that is wequiwed fow any subsequent
 * API invocation fow that AEAD.
 *
 * Wetuwn: awwocated ciphew handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_aead *cwypto_awwoc_aead(const chaw *awg_name, u32 type, u32 mask);

static inwine stwuct cwypto_tfm *cwypto_aead_tfm(stwuct cwypto_aead *tfm)
{
	wetuwn &tfm->base;
}

/**
 * cwypto_fwee_aead() - zewoize and fwee aead handwe
 * @tfm: ciphew handwe to be fweed
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_aead(stwuct cwypto_aead *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_aead_tfm(tfm));
}

/**
 * cwypto_has_aead() - Seawch fow the avaiwabiwity of an aead.
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      aead
 * @type: specifies the type of the aead
 * @mask: specifies the mask fow the aead
 *
 * Wetuwn: twue when the aead is known to the kewnew cwypto API; fawse
 *	   othewwise
 */
int cwypto_has_aead(const chaw *awg_name, u32 type, u32 mask);

static inwine const chaw *cwypto_aead_dwivew_name(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_tfm_awg_dwivew_name(cwypto_aead_tfm(tfm));
}

static inwine stwuct aead_awg *cwypto_aead_awg(stwuct cwypto_aead *tfm)
{
	wetuwn containew_of(cwypto_aead_tfm(tfm)->__cwt_awg,
			    stwuct aead_awg, base);
}

static inwine unsigned int cwypto_aead_awg_ivsize(stwuct aead_awg *awg)
{
	wetuwn awg->ivsize;
}

/**
 * cwypto_aead_ivsize() - obtain IV size
 * @tfm: ciphew handwe
 *
 * The size of the IV fow the aead wefewenced by the ciphew handwe is
 * wetuwned. This IV size may be zewo if the ciphew does not need an IV.
 *
 * Wetuwn: IV size in bytes
 */
static inwine unsigned int cwypto_aead_ivsize(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_aead_awg_ivsize(cwypto_aead_awg(tfm));
}

/**
 * cwypto_aead_authsize() - obtain maximum authentication data size
 * @tfm: ciphew handwe
 *
 * The maximum size of the authentication data fow the AEAD ciphew wefewenced
 * by the AEAD ciphew handwe is wetuwned. The authentication data size may be
 * zewo if the ciphew impwements a hawd-coded maximum.
 *
 * The authentication data may awso be known as "tag vawue".
 *
 * Wetuwn: authentication data size / tag size in bytes
 */
static inwine unsigned int cwypto_aead_authsize(stwuct cwypto_aead *tfm)
{
	wetuwn tfm->authsize;
}

static inwine unsigned int cwypto_aead_awg_maxauthsize(stwuct aead_awg *awg)
{
	wetuwn awg->maxauthsize;
}

static inwine unsigned int cwypto_aead_maxauthsize(stwuct cwypto_aead *aead)
{
	wetuwn cwypto_aead_awg_maxauthsize(cwypto_aead_awg(aead));
}

/**
 * cwypto_aead_bwocksize() - obtain bwock size of ciphew
 * @tfm: ciphew handwe
 *
 * The bwock size fow the AEAD wefewenced with the ciphew handwe is wetuwned.
 * The cawwew may use that infowmation to awwocate appwopwiate memowy fow the
 * data wetuwned by the encwyption ow decwyption opewation
 *
 * Wetuwn: bwock size of ciphew
 */
static inwine unsigned int cwypto_aead_bwocksize(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_tfm_awg_bwocksize(cwypto_aead_tfm(tfm));
}

static inwine unsigned int cwypto_aead_awignmask(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_tfm_awg_awignmask(cwypto_aead_tfm(tfm));
}

static inwine u32 cwypto_aead_get_fwags(stwuct cwypto_aead *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_aead_tfm(tfm));
}

static inwine void cwypto_aead_set_fwags(stwuct cwypto_aead *tfm, u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_aead_tfm(tfm), fwags);
}

static inwine void cwypto_aead_cweaw_fwags(stwuct cwypto_aead *tfm, u32 fwags)
{
	cwypto_tfm_cweaw_fwags(cwypto_aead_tfm(tfm), fwags);
}

/**
 * cwypto_aead_setkey() - set key fow ciphew
 * @tfm: ciphew handwe
 * @key: buffew howding the key
 * @keywen: wength of the key in bytes
 *
 * The cawwew pwovided key is set fow the AEAD wefewenced by the ciphew
 * handwe.
 *
 * Note, the key wength detewmines the ciphew type. Many bwock ciphews impwement
 * diffewent ciphew modes depending on the key size, such as AES-128 vs AES-192
 * vs. AES-256. When pwoviding a 16 byte key fow an AES ciphew handwe, AES-128
 * is pewfowmed.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_aead_setkey(stwuct cwypto_aead *tfm,
		       const u8 *key, unsigned int keywen);

/**
 * cwypto_aead_setauthsize() - set authentication data size
 * @tfm: ciphew handwe
 * @authsize: size of the authentication data / tag in bytes
 *
 * Set the authentication data size / tag size. AEAD wequiwes an authentication
 * tag (ow MAC) in addition to the associated data.
 *
 * Wetuwn: 0 if the setting of the key was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_aead_setauthsize(stwuct cwypto_aead *tfm, unsigned int authsize);

static inwine stwuct cwypto_aead *cwypto_aead_weqtfm(stwuct aead_wequest *weq)
{
	wetuwn __cwypto_aead_cast(weq->base.tfm);
}

/**
 * cwypto_aead_encwypt() - encwypt pwaintext
 * @weq: wefewence to the aead_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * Encwypt pwaintext data using the aead_wequest handwe. That data stwuctuwe
 * and how it is fiwwed with data is discussed with the aead_wequest_*
 * functions.
 *
 * IMPOWTANT NOTE The encwyption opewation cweates the authentication data /
 *		  tag. That data is concatenated with the cweated ciphewtext.
 *		  The ciphewtext memowy size is thewefowe the given numbew of
 *		  bwock ciphew bwocks + the size defined by the
 *		  cwypto_aead_setauthsize invocation. The cawwew must ensuwe
 *		  that sufficient memowy is avaiwabwe fow the ciphewtext and
 *		  the authentication tag.
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; < 0 if an ewwow occuwwed
 */
int cwypto_aead_encwypt(stwuct aead_wequest *weq);

/**
 * cwypto_aead_decwypt() - decwypt ciphewtext
 * @weq: wefewence to the aead_wequest handwe that howds aww infowmation
 *	 needed to pewfowm the ciphew opewation
 *
 * Decwypt ciphewtext data using the aead_wequest handwe. That data stwuctuwe
 * and how it is fiwwed with data is discussed with the aead_wequest_*
 * functions.
 *
 * IMPOWTANT NOTE The cawwew must concatenate the ciphewtext fowwowed by the
 *		  authentication data / tag. That authentication data / tag
 *		  must have the size defined by the cwypto_aead_setauthsize
 *		  invocation.
 *
 *
 * Wetuwn: 0 if the ciphew opewation was successfuw; -EBADMSG: The AEAD
 *	   ciphew opewation pewfowms the authentication of the data duwing the
 *	   decwyption opewation. Thewefowe, the function wetuwns this ewwow if
 *	   the authentication of the ciphewtext was unsuccessfuw (i.e. the
 *	   integwity of the ciphewtext ow the associated data was viowated);
 *	   < 0 if an ewwow occuwwed.
 */
int cwypto_aead_decwypt(stwuct aead_wequest *weq);

/**
 * DOC: Asynchwonous AEAD Wequest Handwe
 *
 * The aead_wequest data stwuctuwe contains aww pointews to data wequiwed fow
 * the AEAD ciphew opewation. This incwudes the ciphew handwe (which can be
 * used by muwtipwe aead_wequest instances), pointew to pwaintext and
 * ciphewtext, asynchwonous cawwback function, etc. It acts as a handwe to the
 * aead_wequest_* API cawws in a simiwaw way as AEAD handwe to the
 * cwypto_aead_* API cawws.
 */

/**
 * cwypto_aead_weqsize() - obtain size of the wequest data stwuctuwe
 * @tfm: ciphew handwe
 *
 * Wetuwn: numbew of bytes
 */
static inwine unsigned int cwypto_aead_weqsize(stwuct cwypto_aead *tfm)
{
	wetuwn tfm->weqsize;
}

/**
 * aead_wequest_set_tfm() - update ciphew handwe wefewence in wequest
 * @weq: wequest handwe to be modified
 * @tfm: ciphew handwe that shaww be added to the wequest handwe
 *
 * Awwow the cawwew to wepwace the existing aead handwe in the wequest
 * data stwuctuwe with a diffewent one.
 */
static inwine void aead_wequest_set_tfm(stwuct aead_wequest *weq,
					stwuct cwypto_aead *tfm)
{
	weq->base.tfm = cwypto_aead_tfm(tfm);
}

/**
 * aead_wequest_awwoc() - awwocate wequest data stwuctuwe
 * @tfm: ciphew handwe to be wegistewed with the wequest
 * @gfp: memowy awwocation fwag that is handed to kmawwoc by the API caww.
 *
 * Awwocate the wequest data stwuctuwe that must be used with the AEAD
 * encwypt and decwypt API cawws. Duwing the awwocation, the pwovided aead
 * handwe is wegistewed in the wequest data stwuctuwe.
 *
 * Wetuwn: awwocated wequest handwe in case of success, ow NUWW if out of memowy
 */
static inwine stwuct aead_wequest *aead_wequest_awwoc(stwuct cwypto_aead *tfm,
						      gfp_t gfp)
{
	stwuct aead_wequest *weq;

	weq = kmawwoc(sizeof(*weq) + cwypto_aead_weqsize(tfm), gfp);

	if (wikewy(weq))
		aead_wequest_set_tfm(weq, tfm);

	wetuwn weq;
}

/**
 * aead_wequest_fwee() - zewoize and fwee wequest data stwuctuwe
 * @weq: wequest data stwuctuwe ciphew handwe to be fweed
 */
static inwine void aead_wequest_fwee(stwuct aead_wequest *weq)
{
	kfwee_sensitive(weq);
}

/**
 * aead_wequest_set_cawwback() - set asynchwonous cawwback function
 * @weq: wequest handwe
 * @fwags: specify zewo ow an OWing of the fwags
 *	   CWYPTO_TFM_WEQ_MAY_BACKWOG the wequest queue may back wog and
 *	   incwease the wait queue beyond the initiaw maximum size;
 *	   CWYPTO_TFM_WEQ_MAY_SWEEP the wequest pwocessing may sweep
 * @compw: cawwback function pointew to be wegistewed with the wequest handwe
 * @data: The data pointew wefews to memowy that is not used by the kewnew
 *	  cwypto API, but pwovided to the cawwback function fow it to use. Hewe,
 *	  the cawwew can pwovide a wefewence to memowy the cawwback function can
 *	  opewate on. As the cawwback function is invoked asynchwonouswy to the
 *	  wewated functionawity, it may need to access data stwuctuwes of the
 *	  wewated functionawity which can be wefewenced using this pointew. The
 *	  cawwback function can access the memowy via the "data" fiewd in the
 *	  cwypto_async_wequest data stwuctuwe pwovided to the cawwback function.
 *
 * Setting the cawwback function that is twiggewed once the ciphew opewation
 * compwetes
 *
 * The cawwback function is wegistewed with the aead_wequest handwe and
 * must compwy with the fowwowing tempwate::
 *
 *	void cawwback_function(stwuct cwypto_async_wequest *weq, int ewwow)
 */
static inwine void aead_wequest_set_cawwback(stwuct aead_wequest *weq,
					     u32 fwags,
					     cwypto_compwetion_t compw,
					     void *data)
{
	weq->base.compwete = compw;
	weq->base.data = data;
	weq->base.fwags = fwags;
}

/**
 * aead_wequest_set_cwypt - set data buffews
 * @weq: wequest handwe
 * @swc: souwce scattew / gathew wist
 * @dst: destination scattew / gathew wist
 * @cwyptwen: numbew of bytes to pwocess fwom @swc
 * @iv: IV fow the ciphew opewation which must compwy with the IV size defined
 *      by cwypto_aead_ivsize()
 *
 * Setting the souwce data and destination data scattew / gathew wists which
 * howd the associated data concatenated with the pwaintext ow ciphewtext. See
 * bewow fow the authentication tag.
 *
 * Fow encwyption, the souwce is tweated as the pwaintext and the
 * destination is the ciphewtext. Fow a decwyption opewation, the use is
 * wevewsed - the souwce is the ciphewtext and the destination is the pwaintext.
 *
 * The memowy stwuctuwe fow ciphew opewation has the fowwowing stwuctuwe:
 *
 * - AEAD encwyption input:  assoc data || pwaintext
 * - AEAD encwyption output: assoc data || ciphewtext || auth tag
 * - AEAD decwyption input:  assoc data || ciphewtext || auth tag
 * - AEAD decwyption output: assoc data || pwaintext
 *
 * Awbeit the kewnew wequiwes the pwesence of the AAD buffew, howevew,
 * the kewnew does not fiww the AAD buffew in the output case. If the
 * cawwew wants to have that data buffew fiwwed, the cawwew must eithew
 * use an in-pwace ciphew opewation (i.e. same memowy wocation fow
 * input/output memowy wocation).
 */
static inwine void aead_wequest_set_cwypt(stwuct aead_wequest *weq,
					  stwuct scattewwist *swc,
					  stwuct scattewwist *dst,
					  unsigned int cwyptwen, u8 *iv)
{
	weq->swc = swc;
	weq->dst = dst;
	weq->cwyptwen = cwyptwen;
	weq->iv = iv;
}

/**
 * aead_wequest_set_ad - set associated data infowmation
 * @weq: wequest handwe
 * @assocwen: numbew of bytes in associated data
 *
 * Setting the AD infowmation.  This function sets the wength of
 * the associated data.
 */
static inwine void aead_wequest_set_ad(stwuct aead_wequest *weq,
				       unsigned int assocwen)
{
	weq->assocwen = assocwen;
}

#endif	/* _CWYPTO_AEAD_H */
