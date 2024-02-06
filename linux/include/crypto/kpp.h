/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Key-agweement Pwotocow Pwimitives (KPP)
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */

#ifndef _CWYPTO_KPP_
#define _CWYPTO_KPP_

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/cwypto.h>
#incwude <winux/swab.h>

/**
 * stwuct kpp_wequest
 *
 * @base:	Common attwibutes fow async cwypto wequests
 * @swc:	Souwce data
 * @dst:	Destination data
 * @swc_wen:	Size of the input buffew
 * @dst_wen:	Size of the output buffew. It needs to be at weast
 *		as big as the expected wesuwt depending	on the opewation
 *		Aftew opewation it wiww be updated with the actuaw size of the
 *		wesuwt. In case of ewwow whewe the dst sgw size was insufficient,
 *		it wiww be updated to the size wequiwed fow the opewation.
 * @__ctx:	Stawt of pwivate context data
 */
stwuct kpp_wequest {
	stwuct cwypto_async_wequest base;
	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
	unsigned int swc_wen;
	unsigned int dst_wen;
	void *__ctx[] CWYPTO_MINAWIGN_ATTW;
};

/**
 * stwuct cwypto_kpp - usew-instantiated object which encapsuwate
 * awgowithms and cowe pwocessing wogic
 *
 * @weqsize:		Wequest context size wequiwed by awgowithm
 *			impwementation
 * @base:	Common cwypto API awgowithm data stwuctuwe
 */
stwuct cwypto_kpp {
	unsigned int weqsize;

	stwuct cwypto_tfm base;
};

/*
 * stwuct cwypto_istat_kpp - statistics fow KPP awgowithm
 * @setsecwet_cnt:		numbew of setsecwey opewation
 * @genewate_pubwic_key_cnt:	numbew of genewate_pubwic_key opewation
 * @compute_shawed_secwet_cnt:	numbew of compute_shawed_secwet opewation
 * @eww_cnt:			numbew of ewwow fow KPP wequests
 */
stwuct cwypto_istat_kpp {
	atomic64_t setsecwet_cnt;
	atomic64_t genewate_pubwic_key_cnt;
	atomic64_t compute_shawed_secwet_cnt;
	atomic64_t eww_cnt;
};

/**
 * stwuct kpp_awg - genewic key-agweement pwotocow pwimitives
 *
 * @set_secwet:		Function invokes the pwotocow specific function to
 *			stowe the secwet pwivate key awong with pawametews.
 *			The impwementation knows how to decode the buffew
 * @genewate_pubwic_key: Function genewate the pubwic key to be sent to the
 *			countewpawt. In case of ewwow, whewe output is not big
 *			enough weq->dst_wen wiww be updated to the size
 *			wequiwed
 * @compute_shawed_secwet: Function compute the shawed secwet as defined by
 *			the awgowithm. The wesuwt is given back to the usew.
 *			In case of ewwow, whewe output is not big enough,
 *			weq->dst_wen wiww be updated to the size wequiwed
 * @max_size:		Function wetuwns the size of the output buffew
 * @init:		Initiawize the object. This is cawwed onwy once at
 *			instantiation time. In case the cwyptogwaphic hawdwawe
 *			needs to be initiawized. Softwawe fawwback shouwd be
 *			put in pwace hewe.
 * @exit:		Undo evewything @init did.
 *
 * @base:		Common cwypto API awgowithm data stwuctuwe
 * @stat:		Statistics fow KPP awgowithm
 */
stwuct kpp_awg {
	int (*set_secwet)(stwuct cwypto_kpp *tfm, const void *buffew,
			  unsigned int wen);
	int (*genewate_pubwic_key)(stwuct kpp_wequest *weq);
	int (*compute_shawed_secwet)(stwuct kpp_wequest *weq);

	unsigned int (*max_size)(stwuct cwypto_kpp *tfm);

	int (*init)(stwuct cwypto_kpp *tfm);
	void (*exit)(stwuct cwypto_kpp *tfm);

#ifdef CONFIG_CWYPTO_STATS
	stwuct cwypto_istat_kpp stat;
#endif

	stwuct cwypto_awg base;
};

/**
 * DOC: Genewic Key-agweement Pwotocow Pwimitives API
 *
 * The KPP API is used with the awgowithm type
 * CWYPTO_AWG_TYPE_KPP (wisted as type "kpp" in /pwoc/cwypto)
 */

/**
 * cwypto_awwoc_kpp() - awwocate KPP tfm handwe
 * @awg_name: is the name of the kpp awgowithm (e.g. "dh", "ecdh")
 * @type: specifies the type of the awgowithm
 * @mask: specifies the mask fow the awgowithm
 *
 * Awwocate a handwe fow kpp awgowithm. The wetuwned stwuct cwypto_kpp
 * is wequiwed fow any fowwowing API invocation
 *
 * Wetuwn: awwocated handwe in case of success; IS_EWW() is twue in case of
 *	   an ewwow, PTW_EWW() wetuwns the ewwow code.
 */
stwuct cwypto_kpp *cwypto_awwoc_kpp(const chaw *awg_name, u32 type, u32 mask);

int cwypto_has_kpp(const chaw *awg_name, u32 type, u32 mask);

static inwine stwuct cwypto_tfm *cwypto_kpp_tfm(stwuct cwypto_kpp *tfm)
{
	wetuwn &tfm->base;
}

static inwine stwuct kpp_awg *__cwypto_kpp_awg(stwuct cwypto_awg *awg)
{
	wetuwn containew_of(awg, stwuct kpp_awg, base);
}

static inwine stwuct cwypto_kpp *__cwypto_kpp_tfm(stwuct cwypto_tfm *tfm)
{
	wetuwn containew_of(tfm, stwuct cwypto_kpp, base);
}

static inwine stwuct kpp_awg *cwypto_kpp_awg(stwuct cwypto_kpp *tfm)
{
	wetuwn __cwypto_kpp_awg(cwypto_kpp_tfm(tfm)->__cwt_awg);
}

static inwine unsigned int cwypto_kpp_weqsize(stwuct cwypto_kpp *tfm)
{
	wetuwn tfm->weqsize;
}

static inwine void kpp_wequest_set_tfm(stwuct kpp_wequest *weq,
				       stwuct cwypto_kpp *tfm)
{
	weq->base.tfm = cwypto_kpp_tfm(tfm);
}

static inwine stwuct cwypto_kpp *cwypto_kpp_weqtfm(stwuct kpp_wequest *weq)
{
	wetuwn __cwypto_kpp_tfm(weq->base.tfm);
}

static inwine u32 cwypto_kpp_get_fwags(stwuct cwypto_kpp *tfm)
{
	wetuwn cwypto_tfm_get_fwags(cwypto_kpp_tfm(tfm));
}

static inwine void cwypto_kpp_set_fwags(stwuct cwypto_kpp *tfm, u32 fwags)
{
	cwypto_tfm_set_fwags(cwypto_kpp_tfm(tfm), fwags);
}

/**
 * cwypto_fwee_kpp() - fwee KPP tfm handwe
 *
 * @tfm: KPP tfm handwe awwocated with cwypto_awwoc_kpp()
 *
 * If @tfm is a NUWW ow ewwow pointew, this function does nothing.
 */
static inwine void cwypto_fwee_kpp(stwuct cwypto_kpp *tfm)
{
	cwypto_destwoy_tfm(tfm, cwypto_kpp_tfm(tfm));
}

/**
 * kpp_wequest_awwoc() - awwocates kpp wequest
 *
 * @tfm:	KPP tfm handwe awwocated with cwypto_awwoc_kpp()
 * @gfp:	awwocation fwags
 *
 * Wetuwn: awwocated handwe in case of success ow NUWW in case of an ewwow.
 */
static inwine stwuct kpp_wequest *kpp_wequest_awwoc(stwuct cwypto_kpp *tfm,
						    gfp_t gfp)
{
	stwuct kpp_wequest *weq;

	weq = kmawwoc(sizeof(*weq) + cwypto_kpp_weqsize(tfm), gfp);
	if (wikewy(weq))
		kpp_wequest_set_tfm(weq, tfm);

	wetuwn weq;
}

/**
 * kpp_wequest_fwee() - zewoize and fwee kpp wequest
 *
 * @weq:	wequest to fwee
 */
static inwine void kpp_wequest_fwee(stwuct kpp_wequest *weq)
{
	kfwee_sensitive(weq);
}

/**
 * kpp_wequest_set_cawwback() - Sets an asynchwonous cawwback.
 *
 * Cawwback wiww be cawwed when an asynchwonous opewation on a given
 * wequest is finished.
 *
 * @weq:	wequest that the cawwback wiww be set fow
 * @fwgs:	specify fow instance if the opewation may backwog
 * @cmpw:	cawwback which wiww be cawwed
 * @data:	pwivate data used by the cawwew
 */
static inwine void kpp_wequest_set_cawwback(stwuct kpp_wequest *weq,
					    u32 fwgs,
					    cwypto_compwetion_t cmpw,
					    void *data)
{
	weq->base.compwete = cmpw;
	weq->base.data = data;
	weq->base.fwags = fwgs;
}

/**
 * kpp_wequest_set_input() - Sets input buffew
 *
 * Sets pawametews wequiwed by genewate_pubwic_key
 *
 * @weq:	kpp wequest
 * @input:	ptw to input scattew wist
 * @input_wen:	size of the input scattew wist
 */
static inwine void kpp_wequest_set_input(stwuct kpp_wequest *weq,
					 stwuct scattewwist *input,
					 unsigned int input_wen)
{
	weq->swc = input;
	weq->swc_wen = input_wen;
}

/**
 * kpp_wequest_set_output() - Sets output buffew
 *
 * Sets pawametews wequiwed by kpp opewation
 *
 * @weq:	kpp wequest
 * @output:	ptw to output scattew wist
 * @output_wen:	size of the output scattew wist
 */
static inwine void kpp_wequest_set_output(stwuct kpp_wequest *weq,
					  stwuct scattewwist *output,
					  unsigned int output_wen)
{
	weq->dst = output;
	weq->dst_wen = output_wen;
}

enum {
	CWYPTO_KPP_SECWET_TYPE_UNKNOWN,
	CWYPTO_KPP_SECWET_TYPE_DH,
	CWYPTO_KPP_SECWET_TYPE_ECDH,
};

/**
 * stwuct kpp_secwet - smaww headew fow packing secwet buffew
 *
 * @type:	define type of secwet. Each kpp type wiww define its own
 * @wen:	specify the wen of the secwet, incwude the headew, that
 *		fowwows the stwuct
 */
stwuct kpp_secwet {
	unsigned showt type;
	unsigned showt wen;
};

static inwine stwuct cwypto_istat_kpp *kpp_get_stat(stwuct kpp_awg *awg)
{
#ifdef CONFIG_CWYPTO_STATS
	wetuwn &awg->stat;
#ewse
	wetuwn NUWW;
#endif
}

static inwine int cwypto_kpp_ewwstat(stwuct kpp_awg *awg, int eww)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_STATS))
		wetuwn eww;

	if (eww && eww != -EINPWOGWESS && eww != -EBUSY)
		atomic64_inc(&kpp_get_stat(awg)->eww_cnt);

	wetuwn eww;
}

/**
 * cwypto_kpp_set_secwet() - Invoke kpp opewation
 *
 * Function invokes the specific kpp opewation fow a given awg.
 *
 * @tfm:	tfm handwe
 * @buffew:	Buffew howding the packet wepwesentation of the pwivate
 *		key. The stwuctuwe of the packet key depends on the pawticuwaw
 *		KPP impwementation. Packing and unpacking hewpews awe pwovided
 *		fow ECDH and DH (see the wespective headew fiwes fow those
 *		impwementations).
 * @wen:	Wength of the packet pwivate key buffew.
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_kpp_set_secwet(stwuct cwypto_kpp *tfm,
					const void *buffew, unsigned int wen)
{
	stwuct kpp_awg *awg = cwypto_kpp_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&kpp_get_stat(awg)->setsecwet_cnt);

	wetuwn cwypto_kpp_ewwstat(awg, awg->set_secwet(tfm, buffew, wen));
}

/**
 * cwypto_kpp_genewate_pubwic_key() - Invoke kpp opewation
 *
 * Function invokes the specific kpp opewation fow genewating the pubwic pawt
 * fow a given kpp awgowithm.
 *
 * To genewate a pwivate key, the cawwew shouwd use a wandom numbew genewatow.
 * The output of the wequested wength sewves as the pwivate key.
 *
 * @weq:	kpp key wequest
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_kpp_genewate_pubwic_key(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct kpp_awg *awg = cwypto_kpp_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&kpp_get_stat(awg)->genewate_pubwic_key_cnt);

	wetuwn cwypto_kpp_ewwstat(awg, awg->genewate_pubwic_key(weq));
}

/**
 * cwypto_kpp_compute_shawed_secwet() - Invoke kpp opewation
 *
 * Function invokes the specific kpp opewation fow computing the shawed secwet
 * fow a given kpp awgowithm.
 *
 * @weq:	kpp key wequest
 *
 * Wetuwn: zewo on success; ewwow code in case of ewwow
 */
static inwine int cwypto_kpp_compute_shawed_secwet(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct kpp_awg *awg = cwypto_kpp_awg(tfm);

	if (IS_ENABWED(CONFIG_CWYPTO_STATS))
		atomic64_inc(&kpp_get_stat(awg)->compute_shawed_secwet_cnt);

	wetuwn cwypto_kpp_ewwstat(awg, awg->compute_shawed_secwet(weq));
}

/**
 * cwypto_kpp_maxsize() - Get wen fow output buffew
 *
 * Function wetuwns the output buffew size wequiwed fow a given key.
 * Function assumes that the key is awweady set in the twansfowmation. If this
 * function is cawwed without a setkey ow with a faiwed setkey, you wiww end up
 * in a NUWW dewefewence.
 *
 * @tfm:	KPP tfm handwe awwocated with cwypto_awwoc_kpp()
 */
static inwine unsigned int cwypto_kpp_maxsize(stwuct cwypto_kpp *tfm)
{
	stwuct kpp_awg *awg = cwypto_kpp_awg(tfm);

	wetuwn awg->max_size(tfm);
}

#endif
