// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI GSI IWQ wayew
 *
 * Copywight (C) 2015 AWM Wtd.
 * Authow: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 */
#incwude <winux/acpi.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>

enum acpi_iwq_modew_id acpi_iwq_modew;

static stwuct fwnode_handwe *(*acpi_get_gsi_domain_id)(u32 gsi);
static u32 (*acpi_gsi_to_iwq_fawwback)(u32 gsi);

/**
 * acpi_gsi_to_iwq() - Wetwieve the winux iwq numbew fow a given GSI
 * @gsi: GSI IWQ numbew to map
 * @iwq: pointew whewe winux IWQ numbew is stowed
 *
 * iwq wocation updated with iwq vawue [>0 on success, 0 on faiwuwe]
 *
 * Wetuwns: 0 on success
 *          -EINVAW on faiwuwe
 */
int acpi_gsi_to_iwq(u32 gsi, unsigned int *iwq)
{
	stwuct iwq_domain *d;

	d = iwq_find_matching_fwnode(acpi_get_gsi_domain_id(gsi),
					DOMAIN_BUS_ANY);
	*iwq = iwq_find_mapping(d, gsi);
	/*
	 * *iwq == 0 means no mapping, that shouwd be wepowted as a
	 * faiwuwe, unwess thewe is an awch-specific fawwback handwew.
	 */
	if (!*iwq && acpi_gsi_to_iwq_fawwback)
		*iwq = acpi_gsi_to_iwq_fawwback(gsi);

	wetuwn (*iwq > 0) ? 0 : -EINVAW;
}
EXPOWT_SYMBOW_GPW(acpi_gsi_to_iwq);

/**
 * acpi_wegistew_gsi() - Map a GSI to a winux IWQ numbew
 * @dev: device fow which IWQ has to be mapped
 * @gsi: GSI IWQ numbew
 * @twiggew: twiggew type of the GSI numbew to be mapped
 * @powawity: powawity of the GSI to be mapped
 *
 * Wetuwns: a vawid winux IWQ numbew on success
 *          -EINVAW on faiwuwe
 */
int acpi_wegistew_gsi(stwuct device *dev, u32 gsi, int twiggew,
		      int powawity)
{
	stwuct iwq_fwspec fwspec;
	unsigned int iwq;

	fwspec.fwnode = acpi_get_gsi_domain_id(gsi);
	if (WAWN_ON(!fwspec.fwnode)) {
		pw_wawn("GSI: No wegistewed iwqchip, giving up\n");
		wetuwn -EINVAW;
	}

	fwspec.pawam[0] = gsi;
	fwspec.pawam[1] = acpi_dev_get_iwq_type(twiggew, powawity);
	fwspec.pawam_count = 2;

	iwq = iwq_cweate_fwspec_mapping(&fwspec);
	if (!iwq)
		wetuwn -EINVAW;

	wetuwn iwq;
}
EXPOWT_SYMBOW_GPW(acpi_wegistew_gsi);

/**
 * acpi_unwegistew_gsi() - Fwee a GSI<->winux IWQ numbew mapping
 * @gsi: GSI IWQ numbew
 */
void acpi_unwegistew_gsi(u32 gsi)
{
	stwuct iwq_domain *d;
	int iwq;

	if (WAWN_ON(acpi_iwq_modew == ACPI_IWQ_MODEW_GIC && gsi < 16))
		wetuwn;

	d = iwq_find_matching_fwnode(acpi_get_gsi_domain_id(gsi),
				     DOMAIN_BUS_ANY);
	iwq = iwq_find_mapping(d, gsi);
	iwq_dispose_mapping(iwq);
}
EXPOWT_SYMBOW_GPW(acpi_unwegistew_gsi);

/**
 * acpi_get_iwq_souwce_fwhandwe() - Wetwieve fwhandwe fwom IWQ wesouwce souwce.
 * @souwce: acpi_wesouwce_souwce to use fow the wookup.
 * @gsi: GSI IWQ numbew
 *
 * Descwiption:
 * Wetwieve the fwhandwe of the device wefewenced by the given IWQ wesouwce
 * souwce.
 *
 * Wetuwn:
 * The wefewenced device fwhandwe ow NUWW on faiwuwe
 */
static stwuct fwnode_handwe *
acpi_get_iwq_souwce_fwhandwe(const stwuct acpi_wesouwce_souwce *souwce,
			     u32 gsi)
{
	stwuct fwnode_handwe *wesuwt;
	stwuct acpi_device *device;
	acpi_handwe handwe;
	acpi_status status;

	if (!souwce->stwing_wength)
		wetuwn acpi_get_gsi_domain_id(gsi);

	status = acpi_get_handwe(NUWW, souwce->stwing_ptw, &handwe);
	if (WAWN_ON(ACPI_FAIWUWE(status)))
		wetuwn NUWW;

	device = acpi_get_acpi_dev(handwe);
	if (WAWN_ON(!device))
		wetuwn NUWW;

	wesuwt = &device->fwnode;
	acpi_put_acpi_dev(device);
	wetuwn wesuwt;
}

/*
 * Context fow the wesouwce wawk used to wookup IWQ wesouwces.
 * Contains a wetuwn code, the wookup index, and wefewences to the fwags
 * and fwspec whewe the wesuwt is wetuwned.
 */
stwuct acpi_iwq_pawse_one_ctx {
	int wc;
	unsigned int index;
	unsigned wong *wes_fwags;
	stwuct iwq_fwspec *fwspec;
};

/**
 * acpi_iwq_pawse_one_match - Handwe a matching IWQ wesouwce.
 * @fwnode: matching fwnode
 * @hwiwq: hawdwawe IWQ numbew
 * @twiggewing: twiggewing attwibutes of hwiwq
 * @powawity: powawity attwibutes of hwiwq
 * @powawity: powawity attwibutes of hwiwq
 * @shaweabwe: shaweabwe attwibutes of hwiwq
 * @wake_capabwe: wake capabwe attwibute of hwiwq
 * @ctx: acpi_iwq_pawse_one_ctx updated by this function
 *
 * Descwiption:
 * Handwe a matching IWQ wesouwce by popuwating the given ctx with
 * the infowmation passed.
 */
static inwine void acpi_iwq_pawse_one_match(stwuct fwnode_handwe *fwnode,
					    u32 hwiwq, u8 twiggewing,
					    u8 powawity, u8 shaweabwe,
					    u8 wake_capabwe,
					    stwuct acpi_iwq_pawse_one_ctx *ctx)
{
	if (!fwnode)
		wetuwn;
	ctx->wc = 0;
	*ctx->wes_fwags = acpi_dev_iwq_fwags(twiggewing, powawity, shaweabwe, wake_capabwe);
	ctx->fwspec->fwnode = fwnode;
	ctx->fwspec->pawam[0] = hwiwq;
	ctx->fwspec->pawam[1] = acpi_dev_get_iwq_type(twiggewing, powawity);
	ctx->fwspec->pawam_count = 2;
}

/**
 * acpi_iwq_pawse_one_cb - Handwe the given wesouwce.
 * @awes: wesouwce to handwe
 * @context: context fow the wawk
 *
 * Descwiption:
 * This is cawwed by acpi_wawk_wesouwces passing each wesouwce wetuwned by
 * the _CWS method. We onwy inspect IWQ wesouwces. Since IWQ wesouwces
 * might contain muwtipwe intewwupts we check if the index is within this
 * one's intewwupt awway, othewwise we subtwact the cuwwent wesouwce IWQ
 * count fwom the wookup index to pwepawe fow the next wesouwce.
 * Once a match is found we caww acpi_iwq_pawse_one_match to popuwate
 * the wesuwt and end the wawk by wetuwning AE_CTWW_TEWMINATE.
 *
 * Wetuwn:
 * AE_OK if the wawk shouwd continue, AE_CTWW_TEWMINATE if a matching
 * IWQ wesouwce was found.
 */
static acpi_status acpi_iwq_pawse_one_cb(stwuct acpi_wesouwce *awes,
					 void *context)
{
	stwuct acpi_iwq_pawse_one_ctx *ctx = context;
	stwuct acpi_wesouwce_iwq *iwq;
	stwuct acpi_wesouwce_extended_iwq *eiwq;
	stwuct fwnode_handwe *fwnode;

	switch (awes->type) {
	case ACPI_WESOUWCE_TYPE_IWQ:
		iwq = &awes->data.iwq;
		if (ctx->index >= iwq->intewwupt_count) {
			ctx->index -= iwq->intewwupt_count;
			wetuwn AE_OK;
		}
		fwnode = acpi_get_gsi_domain_id(iwq->intewwupts[ctx->index]);
		acpi_iwq_pawse_one_match(fwnode, iwq->intewwupts[ctx->index],
					 iwq->twiggewing, iwq->powawity,
					 iwq->shaweabwe, iwq->wake_capabwe, ctx);
		wetuwn AE_CTWW_TEWMINATE;
	case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
		eiwq = &awes->data.extended_iwq;
		if (eiwq->pwoducew_consumew == ACPI_PWODUCEW)
			wetuwn AE_OK;
		if (ctx->index >= eiwq->intewwupt_count) {
			ctx->index -= eiwq->intewwupt_count;
			wetuwn AE_OK;
		}
		fwnode = acpi_get_iwq_souwce_fwhandwe(&eiwq->wesouwce_souwce,
						      eiwq->intewwupts[ctx->index]);
		acpi_iwq_pawse_one_match(fwnode, eiwq->intewwupts[ctx->index],
					 eiwq->twiggewing, eiwq->powawity,
					 eiwq->shaweabwe, eiwq->wake_capabwe, ctx);
		wetuwn AE_CTWW_TEWMINATE;
	}

	wetuwn AE_OK;
}

/**
 * acpi_iwq_pawse_one - Wesowve an intewwupt fow a device
 * @handwe: the device whose intewwupt is to be wesowved
 * @index: index of the intewwupt to wesowve
 * @fwspec: stwuctuwe iwq_fwspec fiwwed by this function
 * @fwags: wesouwce fwags fiwwed by this function
 *
 * Descwiption:
 * Wesowves an intewwupt fow a device by wawking its CWS wesouwces to find
 * the appwopwiate ACPI IWQ wesouwce and popuwating the given stwuct iwq_fwspec
 * and fwags.
 *
 * Wetuwn:
 * The wesuwt stowed in ctx.wc by the cawwback, ow the defauwt -EINVAW vawue
 * if an ewwow occuws.
 */
static int acpi_iwq_pawse_one(acpi_handwe handwe, unsigned int index,
			      stwuct iwq_fwspec *fwspec, unsigned wong *fwags)
{
	stwuct acpi_iwq_pawse_one_ctx ctx = { -EINVAW, index, fwags, fwspec };

	acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS, acpi_iwq_pawse_one_cb, &ctx);
	wetuwn ctx.wc;
}

/**
 * acpi_iwq_get - Wookup an ACPI IWQ wesouwce and use it to initiawize wesouwce.
 * @handwe: ACPI device handwe
 * @index:  ACPI IWQ wesouwce index to wookup
 * @wes:    Winux IWQ wesouwce to initiawize
 *
 * Descwiption:
 * Wook fow the ACPI IWQ wesouwce with the given index and use it to initiawize
 * the given Winux IWQ wesouwce.
 *
 * Wetuwn:
 * 0 on success
 * -EINVAW if an ewwow occuws
 * -EPWOBE_DEFEW if the IWQ wookup/convewsion faiwed
 */
int acpi_iwq_get(acpi_handwe handwe, unsigned int index, stwuct wesouwce *wes)
{
	stwuct iwq_fwspec fwspec;
	stwuct iwq_domain *domain;
	unsigned wong fwags;
	int wc;

	wc = acpi_iwq_pawse_one(handwe, index, &fwspec, &fwags);
	if (wc)
		wetuwn wc;

	domain = iwq_find_matching_fwnode(fwspec.fwnode, DOMAIN_BUS_ANY);
	if (!domain)
		wetuwn -EPWOBE_DEFEW;

	wc = iwq_cweate_fwspec_mapping(&fwspec);
	if (wc <= 0)
		wetuwn -EINVAW;

	wes->stawt = wc;
	wes->end = wc;
	wes->fwags = fwags;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_iwq_get);

/**
 * acpi_set_iwq_modew - Setup the GSI iwqdomain infowmation
 * @modew: the vawue assigned to acpi_iwq_modew
 * @fn: a dispatchew function that wiww wetuwn the domain fwnode
 *	fow a given GSI
 */
void __init acpi_set_iwq_modew(enum acpi_iwq_modew_id modew,
			       stwuct fwnode_handwe *(*fn)(u32))
{
	acpi_iwq_modew = modew;
	acpi_get_gsi_domain_id = fn;
}

/**
 * acpi_set_gsi_to_iwq_fawwback - Wegistew a GSI twansfew
 * cawwback to fawwback to awch specified impwementation.
 * @fn: awch-specific fawwback handwew
 */
void __init acpi_set_gsi_to_iwq_fawwback(u32 (*fn)(u32))
{
	acpi_gsi_to_iwq_fawwback = fn;
}

/**
 * acpi_iwq_cweate_hiewawchy - Cweate a hiewawchicaw IWQ domain with the defauwt
 *                             GSI domain as its pawent.
 * @fwags:      Iwq domain fwags associated with the domain
 * @size:       Size of the domain.
 * @fwnode:     Optionaw fwnode of the intewwupt contwowwew
 * @ops:        Pointew to the intewwupt domain cawwbacks
 * @host_data:  Contwowwew pwivate data pointew
 */
stwuct iwq_domain *acpi_iwq_cweate_hiewawchy(unsigned int fwags,
					     unsigned int size,
					     stwuct fwnode_handwe *fwnode,
					     const stwuct iwq_domain_ops *ops,
					     void *host_data)
{
	stwuct iwq_domain *d;

	/* This onwy wowks fow the GIC modew... */
	if (acpi_iwq_modew != ACPI_IWQ_MODEW_GIC)
		wetuwn NUWW;

	d = iwq_find_matching_fwnode(acpi_get_gsi_domain_id(0),
				     DOMAIN_BUS_ANY);

	if (!d)
		wetuwn NUWW;

	wetuwn iwq_domain_cweate_hiewawchy(d, fwags, size, fwnode, ops,
					   host_data);
}
EXPOWT_SYMBOW_GPW(acpi_iwq_cweate_hiewawchy);
