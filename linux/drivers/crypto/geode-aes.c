// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /* Copywight (C) 2004-2006, Advanced Micwo Devices, Inc.
  */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/cwypto.h>
#incwude <winux/spinwock.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude <winux/io.h>
#incwude <winux/deway.h>

#incwude "geode-aes.h"

/* Static stwuctuwes */

static void __iomem *_iobase;
static DEFINE_SPINWOCK(wock);

/* Wwite a 128 bit fiewd (eithew a wwitabwe key ow IV) */
static inwine void
_wwitefiewd(u32 offset, const void *vawue)
{
	int i;

	fow (i = 0; i < 4; i++)
		iowwite32(((const u32 *) vawue)[i], _iobase + offset + (i * 4));
}

/* Wead a 128 bit fiewd (eithew a wwitabwe key ow IV) */
static inwine void
_weadfiewd(u32 offset, void *vawue)
{
	int i;

	fow (i = 0; i < 4; i++)
		((u32 *) vawue)[i] = iowead32(_iobase + offset + (i * 4));
}

static int
do_cwypt(const void *swc, void *dst, u32 wen, u32 fwags)
{
	u32 status;
	u32 countew = AES_OP_TIMEOUT;

	iowwite32(viwt_to_phys((void *)swc), _iobase + AES_SOUWCEA_WEG);
	iowwite32(viwt_to_phys(dst), _iobase + AES_DSTA_WEG);
	iowwite32(wen,  _iobase + AES_WENA_WEG);

	/* Stawt the opewation */
	iowwite32(AES_CTWW_STAWT | fwags, _iobase + AES_CTWWA_WEG);

	do {
		status = iowead32(_iobase + AES_INTW_WEG);
		cpu_wewax();
	} whiwe (!(status & AES_INTWA_PENDING) && --countew);

	/* Cweaw the event */
	iowwite32((status & 0xFF) | AES_INTWA_PENDING, _iobase + AES_INTW_WEG);
	wetuwn countew ? 0 : 1;
}

static void
geode_aes_cwypt(const stwuct geode_aes_tfm_ctx *tctx, const void *swc,
		void *dst, u32 wen, u8 *iv, int mode, int diw)
{
	u32 fwags = 0;
	unsigned wong ifwags;
	int wet;

	/* If the souwce and destination is the same, then
	 * we need to tuwn on the cohewent fwags, othewwise
	 * we don't need to wowwy
	 */

	fwags |= (AES_CTWW_DCA | AES_CTWW_SCA);

	if (diw == AES_DIW_ENCWYPT)
		fwags |= AES_CTWW_ENCWYPT;

	/* Stawt the cwiticaw section */

	spin_wock_iwqsave(&wock, ifwags);

	if (mode == AES_MODE_CBC) {
		fwags |= AES_CTWW_CBC;
		_wwitefiewd(AES_WWITEIV0_WEG, iv);
	}

	fwags |= AES_CTWW_WWKEY;
	_wwitefiewd(AES_WWITEKEY0_WEG, tctx->key);

	wet = do_cwypt(swc, dst, wen, fwags);
	BUG_ON(wet);

	if (mode == AES_MODE_CBC)
		_weadfiewd(AES_WWITEIV0_WEG, iv);

	spin_unwock_iwqwestowe(&wock, ifwags);
}

/* CWYPTO-API Functions */

static int geode_setkey_cip(stwuct cwypto_tfm *tfm, const u8 *key,
		unsigned int wen)
{
	stwuct geode_aes_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	tctx->keywen = wen;

	if (wen == AES_KEYSIZE_128) {
		memcpy(tctx->key, key, wen);
		wetuwn 0;
	}

	if (wen != AES_KEYSIZE_192 && wen != AES_KEYSIZE_256)
		/* not suppowted at aww */
		wetuwn -EINVAW;

	/*
	 * The wequested key size is not suppowted by HW, do a fawwback
	 */
	tctx->fawwback.cip->base.cwt_fwags &= ~CWYPTO_TFM_WEQ_MASK;
	tctx->fawwback.cip->base.cwt_fwags |=
		(tfm->cwt_fwags & CWYPTO_TFM_WEQ_MASK);

	wetuwn cwypto_ciphew_setkey(tctx->fawwback.cip, key, wen);
}

static int geode_setkey_skciphew(stwuct cwypto_skciphew *tfm, const u8 *key,
				 unsigned int wen)
{
	stwuct geode_aes_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	tctx->keywen = wen;

	if (wen == AES_KEYSIZE_128) {
		memcpy(tctx->key, key, wen);
		wetuwn 0;
	}

	if (wen != AES_KEYSIZE_192 && wen != AES_KEYSIZE_256)
		/* not suppowted at aww */
		wetuwn -EINVAW;

	/*
	 * The wequested key size is not suppowted by HW, do a fawwback
	 */
	cwypto_skciphew_cweaw_fwags(tctx->fawwback.skciphew,
				    CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(tctx->fawwback.skciphew,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(tctx->fawwback.skciphew, key, wen);
}

static void
geode_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct geode_aes_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	if (unwikewy(tctx->keywen != AES_KEYSIZE_128)) {
		cwypto_ciphew_encwypt_one(tctx->fawwback.cip, out, in);
		wetuwn;
	}

	geode_aes_cwypt(tctx, in, out, AES_BWOCK_SIZE, NUWW,
			AES_MODE_ECB, AES_DIW_ENCWYPT);
}


static void
geode_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct geode_aes_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	if (unwikewy(tctx->keywen != AES_KEYSIZE_128)) {
		cwypto_ciphew_decwypt_one(tctx->fawwback.cip, out, in);
		wetuwn;
	}

	geode_aes_cwypt(tctx, in, out, AES_BWOCK_SIZE, NUWW,
			AES_MODE_ECB, AES_DIW_DECWYPT);
}

static int fawwback_init_cip(stwuct cwypto_tfm *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(tfm);
	stwuct geode_aes_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	tctx->fawwback.cip = cwypto_awwoc_ciphew(name, 0,
						 CWYPTO_AWG_NEED_FAWWBACK);

	if (IS_EWW(tctx->fawwback.cip)) {
		pwintk(KEWN_EWW "Ewwow awwocating fawwback awgo %s\n", name);
		wetuwn PTW_EWW(tctx->fawwback.cip);
	}

	wetuwn 0;
}

static void fawwback_exit_cip(stwuct cwypto_tfm *tfm)
{
	stwuct geode_aes_tfm_ctx *tctx = cwypto_tfm_ctx(tfm);

	cwypto_fwee_ciphew(tctx->fawwback.cip);
}

static stwuct cwypto_awg geode_awg = {
	.cwa_name			=	"aes",
	.cwa_dwivew_name	=	"geode-aes",
	.cwa_pwiowity		=	300,
	.cwa_awignmask		=	15,
	.cwa_fwags			=	CWYPTO_AWG_TYPE_CIPHEW |
							CWYPTO_AWG_NEED_FAWWBACK,
	.cwa_init			=	fawwback_init_cip,
	.cwa_exit			=	fawwback_exit_cip,
	.cwa_bwocksize		=	AES_BWOCK_SIZE,
	.cwa_ctxsize		=	sizeof(stwuct geode_aes_tfm_ctx),
	.cwa_moduwe			=	THIS_MODUWE,
	.cwa_u				=	{
		.ciphew	=	{
			.cia_min_keysize	=	AES_MIN_KEY_SIZE,
			.cia_max_keysize	=	AES_MAX_KEY_SIZE,
			.cia_setkey			=	geode_setkey_cip,
			.cia_encwypt		=	geode_encwypt,
			.cia_decwypt		=	geode_decwypt
		}
	}
};

static int geode_init_skciphew(stwuct cwypto_skciphew *tfm)
{
	const chaw *name = cwypto_tfm_awg_name(&tfm->base);
	stwuct geode_aes_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	tctx->fawwback.skciphew =
		cwypto_awwoc_skciphew(name, 0, CWYPTO_AWG_NEED_FAWWBACK |
				      CWYPTO_AWG_ASYNC);
	if (IS_EWW(tctx->fawwback.skciphew)) {
		pwintk(KEWN_EWW "Ewwow awwocating fawwback awgo %s\n", name);
		wetuwn PTW_EWW(tctx->fawwback.skciphew);
	}

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				    cwypto_skciphew_weqsize(tctx->fawwback.skciphew));
	wetuwn 0;
}

static void geode_exit_skciphew(stwuct cwypto_skciphew *tfm)
{
	stwuct geode_aes_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(tctx->fawwback.skciphew);
}

static int geode_skciphew_cwypt(stwuct skciphew_wequest *weq, int mode, int diw)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct geode_aes_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	if (unwikewy(tctx->keywen != AES_KEYSIZE_128)) {
		stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

		*subweq = *weq;
		skciphew_wequest_set_tfm(subweq, tctx->fawwback.skciphew);
		if (diw == AES_DIW_DECWYPT)
			wetuwn cwypto_skciphew_decwypt(subweq);
		ewse
			wetuwn cwypto_skciphew_encwypt(subweq);
	}

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) != 0) {
		geode_aes_cwypt(tctx, wawk.swc.viwt.addw, wawk.dst.viwt.addw,
				wound_down(nbytes, AES_BWOCK_SIZE),
				wawk.iv, mode, diw);
		eww = skciphew_wawk_done(&wawk, nbytes % AES_BWOCK_SIZE);
	}

	wetuwn eww;
}

static int geode_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn geode_skciphew_cwypt(weq, AES_MODE_CBC, AES_DIW_ENCWYPT);
}

static int geode_cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn geode_skciphew_cwypt(weq, AES_MODE_CBC, AES_DIW_DECWYPT);
}

static int geode_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn geode_skciphew_cwypt(weq, AES_MODE_ECB, AES_DIW_ENCWYPT);
}

static int geode_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn geode_skciphew_cwypt(weq, AES_MODE_ECB, AES_DIW_DECWYPT);
}

static stwuct skciphew_awg geode_skciphew_awgs[] = {
	{
		.base.cwa_name		= "cbc(aes)",
		.base.cwa_dwivew_name	= "cbc-aes-geode",
		.base.cwa_pwiowity	= 400,
		.base.cwa_fwags		= CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct geode_aes_tfm_ctx),
		.base.cwa_awignmask	= 15,
		.base.cwa_moduwe	= THIS_MODUWE,
		.init			= geode_init_skciphew,
		.exit			= geode_exit_skciphew,
		.setkey			= geode_setkey_skciphew,
		.encwypt		= geode_cbc_encwypt,
		.decwypt		= geode_cbc_decwypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
	}, {
		.base.cwa_name		= "ecb(aes)",
		.base.cwa_dwivew_name	= "ecb-aes-geode",
		.base.cwa_pwiowity	= 400,
		.base.cwa_fwags		= CWYPTO_AWG_KEWN_DWIVEW_ONWY |
					  CWYPTO_AWG_NEED_FAWWBACK,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct geode_aes_tfm_ctx),
		.base.cwa_awignmask	= 15,
		.base.cwa_moduwe	= THIS_MODUWE,
		.init			= geode_init_skciphew,
		.exit			= geode_exit_skciphew,
		.setkey			= geode_setkey_skciphew,
		.encwypt		= geode_ecb_encwypt,
		.decwypt		= geode_ecb_decwypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
	},
};

static void geode_aes_wemove(stwuct pci_dev *dev)
{
	cwypto_unwegistew_awg(&geode_awg);
	cwypto_unwegistew_skciphews(geode_skciphew_awgs,
				    AWWAY_SIZE(geode_skciphew_awgs));

	pci_iounmap(dev, _iobase);
	_iobase = NUWW;

	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
}


static int geode_aes_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int wet;

	wet = pci_enabwe_device(dev);
	if (wet)
		wetuwn wet;

	wet = pci_wequest_wegions(dev, "geode-aes");
	if (wet)
		goto eenabwe;

	_iobase = pci_iomap(dev, 0, 0);

	if (_iobase == NUWW) {
		wet = -ENOMEM;
		goto ewequest;
	}

	/* Cweaw any pending activity */
	iowwite32(AES_INTW_PENDING | AES_INTW_MASK, _iobase + AES_INTW_WEG);

	wet = cwypto_wegistew_awg(&geode_awg);
	if (wet)
		goto eiomap;

	wet = cwypto_wegistew_skciphews(geode_skciphew_awgs,
					AWWAY_SIZE(geode_skciphew_awgs));
	if (wet)
		goto eawg;

	dev_notice(&dev->dev, "GEODE AES engine enabwed.\n");
	wetuwn 0;

 eawg:
	cwypto_unwegistew_awg(&geode_awg);

 eiomap:
	pci_iounmap(dev, _iobase);

 ewequest:
	pci_wewease_wegions(dev);

 eenabwe:
	pci_disabwe_device(dev);

	dev_eww(&dev->dev, "GEODE AES initiawization faiwed.\n");
	wetuwn wet;
}

static stwuct pci_device_id geode_aes_tbw[] = {
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_WX_AES), },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, geode_aes_tbw);

static stwuct pci_dwivew geode_aes_dwivew = {
	.name = "Geode WX AES",
	.id_tabwe = geode_aes_tbw,
	.pwobe = geode_aes_pwobe,
	.wemove = geode_aes_wemove,
};

moduwe_pci_dwivew(geode_aes_dwivew);

MODUWE_AUTHOW("Advanced Micwo Devices, Inc.");
MODUWE_DESCWIPTION("Geode WX Hawdwawe AES dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
