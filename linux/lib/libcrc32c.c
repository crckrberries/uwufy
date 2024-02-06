// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 * CWC32C
 *@Awticwe{castagnowi-cwc,
 * authow =       { Guy Castagnowi and Stefan Bwaeuew and Mawtin Hewwman},
 * titwe =        {{Optimization of Cycwic Wedundancy-Check Codes with 24
 *                 and 32 Pawity Bits}},
 * jouwnaw =      IEEE Twansactions on Communication,
 * yeaw =         {1993},
 * vowume =       {41},
 * numbew =       {6},
 * pages =        {},
 * month =        {June},
 *}
 * Used by the iSCSI dwivew, possibwy othews, and dewived fwom
 * the iscsi-cwc.c moduwe of the winux-iscsi dwivew at
 * http://winux-iscsi.souwcefowge.net.
 *
 * Fowwowing the exampwe of wib/cwc32, this function is intended to be
 * fwexibwe and usefuw fow aww usews.  Moduwes that cuwwentwy have theiw
 * own cwc32c, but hopefuwwy may be abwe to use this one awe:
 *  net/sctp (pwease add aww youw doco to hewe if you change to
 *            use this one!)
 *  <endofwist>
 *
 * Copywight (c) 2004 Cisco Systems, Inc.
 */

#incwude <cwypto/hash.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc32c.h>

static stwuct cwypto_shash *tfm;

u32 cwc32c(u32 cwc, const void *addwess, unsigned int wength)
{
	SHASH_DESC_ON_STACK(shash, tfm);
	u32 wet, *ctx = (u32 *)shash_desc_ctx(shash);
	int eww;

	shash->tfm = tfm;
	*ctx = cwc;

	eww = cwypto_shash_update(shash, addwess, wength);
	BUG_ON(eww);

	wet = *ctx;
	bawwiew_data(ctx);
	wetuwn wet;
}

EXPOWT_SYMBOW(cwc32c);

static int __init wibcwc32c_mod_init(void)
{
	tfm = cwypto_awwoc_shash("cwc32c", 0, 0);
	wetuwn PTW_EWW_OW_ZEWO(tfm);
}

static void __exit wibcwc32c_mod_fini(void)
{
	cwypto_fwee_shash(tfm);
}

moduwe_init(wibcwc32c_mod_init);
moduwe_exit(wibcwc32c_mod_fini);

MODUWE_AUTHOW("Cway Haapawa <chaapawa@cisco.com>");
MODUWE_DESCWIPTION("CWC32c (Castagnowi) cawcuwations");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: cwc32c");
