/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pubwic Key Encwyption
 *
 * Copywight (c) 2015, Intew Cowpowation
 * Authows: Tadeusz Stwuk <tadeusz.stwuk@intew.com>
 */
#ifndef _CWYPTO_AKCIPHEW_H
#define _CWYPTO_AKCIPHEW_H

#incwude <winux/atomic.h>
#incwude <winux/cwypto.h>

/**
 * stwuct akciphew_wequest - pubwic key wequest
 *
 * @base:	Common attwibutes fow async cwypto wequests
 * @swc:	Souwce data
 *		Fow vewify op this is signatuwe + digest, in that case
 *		totaw size of @swc is @swc_wen + @dst_wen.
 * @dst:	Destination data (Shouwd be NUWW fow vewify op)
 * @swc_wen:	Size of the input buffew
 *		Fow vewify op it's size of signatuwe pawt of @swc, this pawt
 *		is supposed to be opewated by ciphew.
 * @dst_wen:	Size of @dst buffew (fow aww ops except vewify).
 *		It needs to be at weast	as big as the expected wesuwt
 *		depending on the opewation.
 *		Aftew opewation it wiww be updated with the actuaw size of the
 *		wesuwt.
 *		In case of ewwow whewe the dst sgw size was insufficient,
 *		it wiww be updated to the size wequiwed fow the opewation.
 *		Fow vewify op this is size of digest pawt in @swc.
 * @__ctx:	Stawt of pwivate context data
 */
stwuct akciphew_wequest {
	stwuct cwypto_async_wequest base;
	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
	unsigned int swc_wen;
	unsigned int dst_wen;
	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

/**
 * stwuct cwypto_akciphew - usew-instantiated objects which encapsuwate
 * awgowithms and cowe pwocessing wogic
 *
 * @weqsize:	Wequest context size wequiwed by awgowithm impwementation
 * @base:	Common cwypto API awgowithm data stwuctuwe
 */
stwuct cwypto_akciphew {
	unsigned int weqsize;

	stwuct cwypto_tfm base;
};

/*
 * stwuct cwypto_istat_akciphew - statistics fow akciphew awgowithm
 * @encwypt_cnt:	numbew of encwypt wequests
 * @encwypt_twen:	totaw data size handwed by encwypt wequests
 * @decwypt_cnt:	numbew of decwypt wequests
 * @decwypt_twen:	totaw data size handwed by decwypt wequests
 * @vewify_cnt:		numbew of vewify opewation
 * @sign_cnt:		numbew of sign wequests
 * @eww_cnt:		numbew of ewwow fow akciphew wequests
 */
stwuct cwypto_istat_akciphew {
	atomic64_t encwypt_cnt;
	atomic64_t encwypt_twen;
	atomic64_t decwypt_cnt;
	atomic64_t decwypt_twen;
	atomic64_t vewify_cnt;
	atomic64_t sign_cnt;
	atomic64_t eww_cnt;
};

/**
 * stwuct akciphew_awg - genewic pubwic key awgowithm
 *
 * @sign:	Function pewfowms a sign opewation as defined by pubwic key
 *		awgowithm. In case of ewwow, whewe the dst_wen was insufficient,
 *		the weq->dst_wen wiww be updated to the size wequiwed fow the
 *		opewation
 * @vewify:	Function pewfowms a compwete vewify opewation as defined by
 *		pubwic key awgowithm, wetuwning vewification status. Wequiwes
 *		digest vawue as input pawametew.
 * @encwypt:	Function pewfowms an encwypt opewation as defined by pubwic key
 *		awgowithm. In case of ewwow, whewe the dst_wen was insufficient,
 *		the weq->dst_wen wiww be updated to the size wequiwed fow the
 *		opewation
 * @decwypt:	Function pewfowms a decwypt opewation as defined by pubwic key
 *		awgowithm. In case of ewwow, whewe the dst_wen was insufficient,
 *		the weq->dst_wen wiww be updated to the size wequiwed fow the
 *		opewation
 * @set_pub_key: Function invokes the awgowithm specific set pubwic key
 *		function, which knows how to decode and intewpwet
 *		the BEW encoded pubwic key and pawametews
 * @set_pwiv_key: Function invokes the awgowithm specific set pwivate key
 *		function, which knows how to decode and intewpwet
 *		the BEW encoded pwivate key and pawametews
 * @max_size:	Function wetuwns dest buffew size wequiwed fow a given key.
 * @init:	Initiawize the cwyptogwaphic twansfowmation object.
 *		This function is used to initiawize the cwyptogwaphic
 *		twansfowmation object. This function is cawwed onwy once at
 *		the instantiation time, wight aftew the twansfowmation context
 *		was awwocated. In case the cwyptogwaphic hawdwawe has some
 *		speciaw wequiwements which need to be handwed by softwawe, this
 *		function shaww check fow the pwecise wequiwement of the
 *		twansfowmation and put any softwawe fawwbacks in pwace.
 * @exit:	Deinitiawize the cwyptogwaphic twansfowmation object. This is a
 *		countewpawt to @init, used to wemove vawious changes set in
 *		@init.
 * @stat:	Statistics fow akciphew awgowithm
 *
 * @base:	Common cwypto API awgowithm data stwuctuwe
 */
stwuct akciphew_awg {
	int (*sign)(stwuct akciphew_wequest *weq);
	int (*vewify)(stwuct akciphew_wequest *weq);
	int (*encwypt)(stwuct akciphew_wequest *weq);
	int (*decwypt)(stwuct akciphew_wequest *weq);
	int (*set_pub_key)(stwuct cwypto_akciphew *tfm, const void *key,
			   unsigned int keywen);
	int (*set_pwiv_key)(stwuct cwypto_akciphew *tfm, const void *key,
			    unsigned int keywen);
	unsigned int (*max_size)(stwuct cwypto_akciphew *tfm);
	int (*init)(stwuct cwypto_akciphew *tfm);
	void (*exit)(stwuct cwypto_akciphew *tfm);

#ifdef CONFIG_CWYPTO_STATS
	stwuct cwypto_istat_akciphew stat;
#endif

	stwuct cwypto_awg base;
};

/**
 * DOC: Genewic Pubwic Key API
 *
 * The Pubwic Key API is used with the awgowithms of type
 * CWYPTO_AWG_TYPE_AKCIPHEW (wisted as type "akciphew" in /pwoc/cwypto)
 */

/**
 * cwypto_awwoc_akciphew() - awwocate AKCIPHEW tfm handwe
 * @awg_name: is the cwa_name / name ow cwa_dwivew_name / dwivew name of the
 *	      pubwic key awgowithm e.g. "wsa"
 * @type: specifies the type of the awgowithm
 * @mask: specifies the mask fow the awgowithm
 *
 * Awwocate a handwe fow pubwic key awgowithm. The wetuwned stwuct
 * cwypto_akciphew is the handwe that is wequiwed fow any subsequent
 * API invocation fow the pubwic key opewations.
 *
 * Wetuwn: awwocated handwe in case of success; IS_EWW() is twue in case
 *	   of an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_akciphew *cwypto_awwoc_akciphew(const chaw *awg_name, u32 type,
					      u32 mask);

static inwine stwuct cwypto_tfm *cwypto_akciphew_tfm(
	stwuct cwypto_akciphew *tfm)
{
	wetuwn &tfm->base;
}

static inwine stwuct akciphew_awg *__cwypto_akciphew_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct akciphew_awg, base);
}

static inwine stwuct cwypto_akciphew *__cwypto_akciphew_tfm(
	stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_akciphew, base);
}

static inwine stwuct akciphew_awg *cwypto_akciphew_awg(
	stwuct cwypto_akciphew *tfm)
{
	wetuwn __cwypto_akciphew_awg(cwypto_akciphew_tfm(tfm)->__cwt_awg);
}

static inwine unsigned int cwypto_akciphew_weqsize(stwuct cwypto_akciphew *tfm)
{
	wetuwn tfm->weqsize;
}

static inwine void akciphew_wequest_set_tfm(stwuct akciphew_wequest *weq,
					    stwuct cwypto_akciphew *tfm)
{
	weq->base.tfm = cwypto_akciphew_tfm(tfm);
}

static inwine stwuct cwypto_akciphew *cwypto_akciphew_weqtfm(
	stwuct akciphew_wequest *weq)
{
	wetuwn __cwypto_akciphew_tfm(weq->base.tfm);
}

/**
 * cwypto_fwee_akciphew() - fwee AKCIPHEW tfm handwe
 *
 * @tfm: AKCIPHEW tfm handwe awwocated with cwypto_awwoc_akciphew()
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_akciphew(stwuct cwypto_akciphew *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_akciphew_tfm(tfm));
}

/**
 * akciphew_wequest_awwoc() - awwocates pubwic key wequest
 *
 * @tfm:	AKCIPHEW tfm handwe awwocated with cwypto_awwoc_akciphew()
 * @gfp:	awwocation fwags
 *
 * Wetuwn: awwocated handwe in case of success ow NUWW in case of an ewwow.
 */
static inwine stwuct akciphew_wequest *akciphew_wequest_awwoc(
	stwuct cwypto_akciphew *tfm, gfp_t gfp)
{
	stwuct akciphew_wequest *weq;

	weq = kmawwoc(sizeof(*weq) + cwypto_akciphew_weqsize(tfm), gfp);
	if (wikewy(weq))
		akciphew_wequest_set_tfm(weq, tfm);

	wetuwn weq;
}

/**
 * akciphew_wequest_fwee() - zewoize and fwee pubwic key wequest
 *
 * @weq:	wequest to fwee
 */
static inwine void akciphew_wequest_fwee(stwuct akciphew_wequest *weq)
{
	kfwee_sensitive(weq);
}

/**
 * akciphew_wequest_set_cawwback() - Sets an asynchwonous cawwback.
 *
 * Cawwback wiww be cawwed when an asynchwonous opewation on a given
 * wequest is finished.
 *
 * @weq:	wequest that the cawwback wiww be set fow
 * @fwgs:	specify fow instance if the opewation may backwog
 * @cmpw:	cawwback which wiww be cawwed
 * @data:	pwivate data used by the cawwew
 */
static inwine void akciphew_wequest_set_cawwback(stwuct akciphew_wequest *weq,
						 u32 fwgs,
						 cwypto_compwetion_t cmpw,
						 void *data)
{
	weq->base.compwete = cmpw;
	weq->base.data = data;
	weq->base.fwags = fwgs;
}

/**
 * akciphew_wequest_set_cwypt() - Sets wequest pawametews
 *
 * Sets pawametews wequiwed by cwypto opewation
 *
 * @weq:	pubwic key wequest
 * @swc:	ptw to input scattew wist
 * @dst:	ptw to output scattew wist ow NUWW fow vewify op
 * @swc_wen:	size of the swc input scattew wist to be pwocessed
 * @dst_wen:	size of the dst output scattew wist ow size of signatuwe
 *		powtion in @swc fow vewify op
 */
static inwine void akciphew_wequest_set_cwypt(stwuct akciphew_wequest *weq,
					      stwuct scattewwist *swc,
					      stwuct scattewwist *dst,
					      unsigned int swc_wen,
					      unsigned int dst_wen)
{
	weq->swc = swc;
	weq->dst = dst;
	weq->swc_wen = swc_wen;
	weq->dst_wen = dst_wen;
}

/**
 * cwypto_akciphew_maxsize() - Get wen fow output buffew
 *
 * Function wetuwns the dest buffew size wequiwed fow a given key.
 * Function assumes that the key is awweady set in the twansfowmation. If this
 * function is cawwed without a setkey ow with a faiwed setkey, you wiww end up
 * in a NUWW dewefewence.
 *
 * @tfm:	AKCIPHEW tfm handwe awwocated with cwypto_awwoc_akciphew()
 */
static inwine unsigned int cwypto_akciphew_maxsize(stwuct cwypto_akciphew *tfm)
{
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	wetuwn awg->max_size(tfm);
}

static inwine stwuct cwypto_istat_akciphew *akciphew_get_stat(
	stwuct akciphew_awg *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

static inwine int cwypto_akciphew_ewwstat(stwuct akciphew_awg *awg, int eww)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww && eww != -EINPWOGWESS && eww != -EBUSY)
		atomic64_inc(&akciphew_get_stat(awg)->eww_cnt);

	wetuwn eww;
}

/**
 * cwypto_akciphew_encwypt() - Invoke pubwic key encwypt opewation
 *
 * Function invokes the specific pubwic key encwypt opewation fow a given
 * pubwic key awgowithm
 *
 * @weq:	asymmetwic key wequest
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_akciphew_encwypt(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_akciphew *istat = akciphew_get_stat(awg);

		atomic64_inc(&istat->encwypt_cnt);
		atomic64_add(weq->swc_wen, &istat->encwypt_twen);
	}

	wetuwn cwypto_akciphew_ewwstat(awg, awg->encwypt(weq));
}

/**
 * cwypto_akciphew_decwypt() - Invoke pubwic key decwypt opewation
 *
 * Function invokes the specific pubwic key decwypt opewation fow a given
 * pubwic key awgowithm
 *
 * @weq:	asymmetwic key wequest
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_akciphew_decwypt(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS)) {
		stwuct cwypto_istat_akciphew *istat = akciphew_get_stat(awg);

		atomic64_inc(&istat->decwypt_cnt);
		atomic64_add(weq->swc_wen, &istat->decwypt_twen);
	}

	wetuwn cwypto_akciphew_ewwstat(awg, awg->decwypt(weq));
}

/**
 * cwypto_akciphew_sync_encwypt() - Invoke pubwic key encwypt opewation
 *
 * Function invokes the specific pubwic key encwypt opewation fow a given
 * pubwic key awgowithm
 *
 * @tfm:	AKCIPHEW tfm handwe awwocated with cwypto_awwoc_akciphew()
 * @swc:	souwce buffew
 * @swen:	souwce wength
 * @dst:	destination obuffew
 * @dwen:	destination wength
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
int cwypto_akciphew_sync_encwypt(stwuct cwypto_akciphew *tfm,
				 const void *swc, unsigned int swen,
				 void *dst, unsigned int dwen);

/**
 * cwypto_akciphew_sync_decwypt() - Invoke pubwic key decwypt opewation
 *
 * Function invokes the specific pubwic key decwypt opewation fow a given
 * pubwic key awgowithm
 *
 * @tfm:	AKCIPHEW tfm handwe awwocated with cwypto_awwoc_akciphew()
 * @swc:	souwce buffew
 * @swen:	souwce wength
 * @dst:	destination obuffew
 * @dwen:	destination wength
 *
 * Wetuwn: Output wength on success; ewwow code in case of ewwow
 */
int cwypto_akciphew_sync_decwypt(stwuct cwypto_akciphew *tfm,
				 const void *swc, unsigned int swen,
				 void *dst, unsigned int dwen);

/**
 * cwypto_akciphew_sign() - Invoke pubwic key sign opewation
 *
 * Function invokes the specific pubwic key sign opewation fow a given
 * pubwic key awgowithm
 *
 * @weq:	asymmetwic key wequest
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_akciphew_sign(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&akciphew_get_stat(awg)->sign_cnt);

	wetuwn cwypto_akciphew_ewwstat(awg, awg->sign(weq));
}

/**
 * cwypto_akciphew_vewify() - Invoke pubwic key signatuwe vewification
 *
 * Function invokes the specific pubwic key signatuwe vewification opewation
 * fow a given pubwic key awgowithm.
 *
 * @weq:	asymmetwic key wequest
 *
 * Note: weq->dst shouwd be NUWW, weq->swc shouwd point to SG of size
 * (weq->swc_size + weq->dst_size), containing signatuwe (of weq->swc_size
 * wength) with appended digest (of weq->dst_size wength).
 *
 * Wetuwn: zewo on vewification success; ewwow code in case of ewwow.
 */
static inwine int cwypto_akciphew_vewify(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&akciphew_get_stat(awg)->vewify_cnt);

	wetuwn cwypto_akciphew_ewwstat(awg, awg->vewify(weq));
}

/**
 * cwypto_akciphew_set_pub_key() - Invoke set pubwic key opewation
 *
 * Function invokes the awgowithm specific set key function, which knows
 * how to decode and intewpwet the encoded key and pawametews
 *
 * @tfm:	tfm handwe
 * @key:	BEW encoded pubwic key, awgo OID, pawamwen, BEW encoded
 *		pawametews
 * @keywen:	wength of the key (not incwuding othew data)
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_akciphew_set_pub_key(stwuct cwypto_akciphew *tfm,
					      const void *key,
					      unsigned int keywen)
{
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	wetuwn awg->set_pub_key(tfm, key, keywen);
}

/**
 * cwypto_akciphew_set_pwiv_key() - Invoke set pwivate key opewation
 *
 * Function invokes the awgowithm specific set key function, which knows
 * how to decode and intewpwet the encoded key and pawametews
 *
 * @tfm:	tfm handwe
 * @key:	BEW encoded pwivate key, awgo OID, pawamwen, BEW encoded
 *		pawametews
 * @keywen:	wength of the key (not incwuding othew data)
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_akciphew_set_pwiv_key(stwuct cwypto_akciphew *tfm,
					       const void *key,
					       unsigned int keywen)
{
	stwuct akciphew_awg *awg = cwypto_akciphew_awg(tfm);

	wetuwn awg->set_pwiv_key(tfm, key, keywen);
}
#endif
