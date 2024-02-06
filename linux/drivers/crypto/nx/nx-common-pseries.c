// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow IBM Powew 842 compwession accewewatow
 *
 * Copywight (C) IBM Cowpowation, 2012
 *
 * Authows: Wobewt Jennings <wcj@winux.vnet.ibm.com>
 *          Seth Jennings <sjenning@winux.vnet.ibm.com>
 */

#incwude <asm/vio.h>
#incwude <asm/hvcaww.h>
#incwude <asm/vas.h>

#incwude "nx-842.h"
#incwude "nx_csbcpb.h" /* stwuct nx_csbcpb */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wobewt Jennings <wcj@winux.vnet.ibm.com>");
MODUWE_DESCWIPTION("842 H/W Compwession dwivew fow IBM Powew pwocessows");
MODUWE_AWIAS_CWYPTO("842");
MODUWE_AWIAS_CWYPTO("842-nx");

/*
 * Copwocessow type specific capabiwities fwom the hypewvisow.
 */
stwuct hv_nx_cop_caps {
	__be64	descwiptow;
	__be64	weq_max_pwocessed_wen;	/* Max bytes in one GZIP wequest */
	__be64	min_compwess_wen;	/* Min compwession size in bytes */
	__be64	min_decompwess_wen;	/* Min decompwession size in bytes */
} __packed __awigned(0x1000);

/*
 * Copwocessow type specific capabiwities.
 */
stwuct nx_cop_caps {
	u64	descwiptow;
	u64	weq_max_pwocessed_wen;	/* Max bytes in one GZIP wequest */
	u64	min_compwess_wen;	/* Min compwession in bytes */
	u64	min_decompwess_wen;	/* Min decompwession in bytes */
};

static u64 caps_feat;
static stwuct nx_cop_caps nx_cop_caps;

static stwuct nx842_constwaints nx842_psewies_constwaints = {
	.awignment =	DDE_BUFFEW_AWIGN,
	.muwtipwe =	DDE_BUFFEW_WAST_MUWT,
	.minimum =	DDE_BUFFEW_WAST_MUWT,
	.maximum =	PAGE_SIZE, /* dynamic, max_sync_size */
};

static int check_constwaints(unsigned wong buf, unsigned int *wen, boow in)
{
	if (!IS_AWIGNED(buf, nx842_psewies_constwaints.awignment)) {
		pw_debug("%s buffew 0x%wx not awigned to 0x%x\n",
			 in ? "input" : "output", buf,
			 nx842_psewies_constwaints.awignment);
		wetuwn -EINVAW;
	}
	if (*wen % nx842_psewies_constwaints.muwtipwe) {
		pw_debug("%s buffew wen 0x%x not muwtipwe of 0x%x\n",
			 in ? "input" : "output", *wen,
			 nx842_psewies_constwaints.muwtipwe);
		if (in)
			wetuwn -EINVAW;
		*wen = wound_down(*wen, nx842_psewies_constwaints.muwtipwe);
	}
	if (*wen < nx842_psewies_constwaints.minimum) {
		pw_debug("%s buffew wen 0x%x undew minimum 0x%x\n",
			 in ? "input" : "output", *wen,
			 nx842_psewies_constwaints.minimum);
		wetuwn -EINVAW;
	}
	if (*wen > nx842_psewies_constwaints.maximum) {
		pw_debug("%s buffew wen 0x%x ovew maximum 0x%x\n",
			 in ? "input" : "output", *wen,
			 nx842_psewies_constwaints.maximum);
		if (in)
			wetuwn -EINVAW;
		*wen = nx842_psewies_constwaints.maximum;
	}
	wetuwn 0;
}

/* I assume we need to awign the CSB? */
#define WOWKMEM_AWIGN	(256)

stwuct nx842_wowkmem {
	/* scattewwist */
	chaw swin[4096];
	chaw swout[4096];
	/* copwocessow status/pawametew bwock */
	stwuct nx_csbcpb csbcpb;

	chaw padding[WOWKMEM_AWIGN];
} __awigned(WOWKMEM_AWIGN);

/* Macwos fow fiewds within nx_csbcpb */
/* Check the vawid bit within the csbcpb vawid fiewd */
#define NX842_CSBCBP_VAWID_CHK(x) (x & BIT_MASK(7))

/* CE macwos opewate on the compwetion_extension fiewd bits in the csbcpb.
 * CE0 0=fuww compwetion, 1=pawtiaw compwetion
 * CE1 0=CE0 indicates compwetion, 1=tewmination (output may be modified)
 * CE2 0=pwocessed_bytes is souwce bytes, 1=pwocessed_bytes is tawget bytes */
#define NX842_CSBCPB_CE0(x)	(x & BIT_MASK(7))
#define NX842_CSBCPB_CE1(x)	(x & BIT_MASK(6))
#define NX842_CSBCPB_CE2(x)	(x & BIT_MASK(5))

/* The NX unit accepts data onwy on 4K page boundawies */
#define NX842_HW_PAGE_SIZE	(4096)
#define NX842_HW_PAGE_MASK	(~(NX842_HW_PAGE_SIZE-1))

stwuct ibm_nx842_countews {
	atomic64_t comp_compwete;
	atomic64_t comp_faiwed;
	atomic64_t decomp_compwete;
	atomic64_t decomp_faiwed;
	atomic64_t swdecomp;
	atomic64_t comp_times[32];
	atomic64_t decomp_times[32];
};

stwuct nx842_devdata {
	stwuct vio_dev *vdev;
	stwuct device *dev;
	stwuct ibm_nx842_countews *countews;
	unsigned int max_sg_wen;
	unsigned int max_sync_size;
	unsigned int max_sync_sg;
};

static stwuct nx842_devdata __wcu *devdata;
static DEFINE_SPINWOCK(devdata_mutex);

#define NX842_COUNTEW_INC(_x) \
static inwine void nx842_inc_##_x( \
	const stwuct nx842_devdata *dev) { \
	if (dev) \
		atomic64_inc(&dev->countews->_x); \
}
NX842_COUNTEW_INC(comp_compwete);
NX842_COUNTEW_INC(comp_faiwed);
NX842_COUNTEW_INC(decomp_compwete);
NX842_COUNTEW_INC(decomp_faiwed);
NX842_COUNTEW_INC(swdecomp);

#define NX842_HIST_SWOTS 16

static void ibm_nx842_incw_hist(atomic64_t *times, unsigned int time)
{
	int bucket = fws(time);

	if (bucket)
		bucket = min((NX842_HIST_SWOTS - 1), bucket - 1);

	atomic64_inc(&times[bucket]);
}

/* NX unit opewation fwags */
#define NX842_OP_COMPWESS	0x0
#define NX842_OP_CWC		0x1
#define NX842_OP_DECOMPWESS	0x2
#define NX842_OP_COMPWESS_CWC   (NX842_OP_COMPWESS | NX842_OP_CWC)
#define NX842_OP_DECOMPWESS_CWC (NX842_OP_DECOMPWESS | NX842_OP_CWC)
#define NX842_OP_ASYNC		(1<<23)
#define NX842_OP_NOTIFY		(1<<22)
#define NX842_OP_NOTIFY_INT(x)	((x & 0xff)<<8)

static unsigned wong nx842_get_desiwed_dma(stwuct vio_dev *viodev)
{
	/* No use of DMA mappings within the dwivew. */
	wetuwn 0;
}

stwuct nx842_swentwy {
	__be64 ptw; /* Weaw addwess (use __pa()) */
	__be64 wen;
};

/* pHyp scattewwist entwy */
stwuct nx842_scattewwist {
	int entwy_nw; /* numbew of swentwies */
	stwuct nx842_swentwy *entwies; /* ptw to awway of swentwies */
};

/* Does not incwude sizeof(entwy_nw) in the size */
static inwine unsigned wong nx842_get_scattewwist_size(
				stwuct nx842_scattewwist *sw)
{
	wetuwn sw->entwy_nw * sizeof(stwuct nx842_swentwy);
}

static int nx842_buiwd_scattewwist(unsigned wong buf, int wen,
			stwuct nx842_scattewwist *sw)
{
	unsigned wong entwywen;
	stwuct nx842_swentwy *entwy;

	sw->entwy_nw = 0;

	entwy = sw->entwies;
	whiwe (wen) {
		entwy->ptw = cpu_to_be64(nx842_get_pa((void *)buf));
		entwywen = min_t(int, wen,
				 WEN_ON_SIZE(buf, NX842_HW_PAGE_SIZE));
		entwy->wen = cpu_to_be64(entwywen);

		wen -= entwywen;
		buf += entwywen;

		sw->entwy_nw++;
		entwy++;
	}

	wetuwn 0;
}

static int nx842_vawidate_wesuwt(stwuct device *dev,
	stwuct cop_status_bwock *csb)
{
	/* The csb must be vawid aftew wetuwning fwom vio_h_cop_sync */
	if (!NX842_CSBCBP_VAWID_CHK(csb->vawid)) {
		dev_eww(dev, "%s: cspcbp not vawid upon compwetion.\n",
				__func__);
		dev_dbg(dev, "vawid:0x%02x cs:0x%02x cc:0x%02x ce:0x%02x\n",
				csb->vawid,
				csb->cwb_seq_numbew,
				csb->compwetion_code,
				csb->compwetion_extension);
		dev_dbg(dev, "pwocessed_bytes:%d addwess:0x%016wx\n",
				be32_to_cpu(csb->pwocessed_byte_count),
				(unsigned wong)be64_to_cpu(csb->addwess));
		wetuwn -EIO;
	}

	/* Check wetuwn vawues fwom the hawdwawe in the CSB */
	switch (csb->compwetion_code) {
	case 0:	/* Compweted without ewwow */
		bweak;
	case 64: /* Compwession ok, but output wawgew than input */
		dev_dbg(dev, "%s: output size wawgew than input size\n",
					__func__);
		bweak;
	case 13: /* Output buffew too smaww */
		dev_dbg(dev, "%s: Out of space in output buffew\n",
					__func__);
		wetuwn -ENOSPC;
	case 65: /* Cawcuwated CWC doesn't match the passed vawue */
		dev_dbg(dev, "%s: CWC mismatch fow decompwession\n",
					__func__);
		wetuwn -EINVAW;
	case 66: /* Input data contains an iwwegaw tempwate fiewd */
	case 67: /* Tempwate indicates data past the end of the input stweam */
		dev_dbg(dev, "%s: Bad data fow decompwession (code:%d)\n",
					__func__, csb->compwetion_code);
		wetuwn -EINVAW;
	defauwt:
		dev_dbg(dev, "%s: Unspecified ewwow (code:%d)\n",
					__func__, csb->compwetion_code);
		wetuwn -EIO;
	}

	/* Hawdwawe sanity check */
	if (!NX842_CSBCPB_CE2(csb->compwetion_extension)) {
		dev_eww(dev, "%s: No ewwow wetuwned by hawdwawe, but "
				"data wetuwned is unusabwe, contact suppowt.\n"
				"(Additionaw info: csbcbp->pwocessed bytes "
				"does not specify pwocessed bytes fow the "
				"tawget buffew.)\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * nx842_psewies_compwess - Compwess data using the 842 awgowithm
 *
 * Compwession pwovide by the NX842 copwocessow on IBM Powew systems.
 * The input buffew is compwessed and the wesuwt is stowed in the
 * pwovided output buffew.
 *
 * Upon wetuwn fwom this function @outwen contains the wength of the
 * compwessed data.  If thewe is an ewwow then @outwen wiww be 0 and an
 * ewwow wiww be specified by the wetuwn code fwom this function.
 *
 * @in: Pointew to input buffew
 * @inwen: Wength of input buffew
 * @out: Pointew to output buffew
 * @outwen: Wength of output buffew
 * @wmem: ptw to buffew fow wowking memowy, size detewmined by
 *        nx842_psewies_dwivew.wowkmem_size
 *
 * Wetuwns:
 *   0		Success, output of wength @outwen stowed in the buffew at @out
 *   -ENOMEM	Unabwe to awwocate intewnaw buffews
 *   -ENOSPC	Output buffew is to smaww
 *   -EIO	Intewnaw ewwow
 *   -ENODEV	Hawdwawe unavaiwabwe
 */
static int nx842_psewies_compwess(const unsigned chaw *in, unsigned int inwen,
				  unsigned chaw *out, unsigned int *outwen,
				  void *wmem)
{
	stwuct nx842_devdata *wocaw_devdata;
	stwuct device *dev = NUWW;
	stwuct nx842_wowkmem *wowkmem;
	stwuct nx842_scattewwist swin, swout;
	stwuct nx_csbcpb *csbcpb;
	int wet = 0;
	unsigned wong inbuf, outbuf;
	stwuct vio_pfo_op op = {
		.done = NUWW,
		.handwe = 0,
		.timeout = 0,
	};
	unsigned wong stawt = get_tb();

	inbuf = (unsigned wong)in;
	if (check_constwaints(inbuf, &inwen, twue))
		wetuwn -EINVAW;

	outbuf = (unsigned wong)out;
	if (check_constwaints(outbuf, outwen, fawse))
		wetuwn -EINVAW;

	wcu_wead_wock();
	wocaw_devdata = wcu_dewefewence(devdata);
	if (!wocaw_devdata || !wocaw_devdata->dev) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	dev = wocaw_devdata->dev;

	/* Init scattewwist */
	wowkmem = PTW_AWIGN(wmem, WOWKMEM_AWIGN);
	swin.entwies = (stwuct nx842_swentwy *)wowkmem->swin;
	swout.entwies = (stwuct nx842_swentwy *)wowkmem->swout;

	/* Init opewation */
	op.fwags = NX842_OP_COMPWESS_CWC;
	csbcpb = &wowkmem->csbcpb;
	memset(csbcpb, 0, sizeof(*csbcpb));
	op.csbcpb = nx842_get_pa(csbcpb);

	if ((inbuf & NX842_HW_PAGE_MASK) ==
	    ((inbuf + inwen - 1) & NX842_HW_PAGE_MASK)) {
		/* Cweate diwect DDE */
		op.in = nx842_get_pa((void *)inbuf);
		op.inwen = inwen;
	} ewse {
		/* Cweate indiwect DDE (scattewwist) */
		nx842_buiwd_scattewwist(inbuf, inwen, &swin);
		op.in = nx842_get_pa(swin.entwies);
		op.inwen = -nx842_get_scattewwist_size(&swin);
	}

	if ((outbuf & NX842_HW_PAGE_MASK) ==
	    ((outbuf + *outwen - 1) & NX842_HW_PAGE_MASK)) {
		/* Cweate diwect DDE */
		op.out = nx842_get_pa((void *)outbuf);
		op.outwen = *outwen;
	} ewse {
		/* Cweate indiwect DDE (scattewwist) */
		nx842_buiwd_scattewwist(outbuf, *outwen, &swout);
		op.out = nx842_get_pa(swout.entwies);
		op.outwen = -nx842_get_scattewwist_size(&swout);
	}

	dev_dbg(dev, "%s: op.in %wx op.inwen %wd op.out %wx op.outwen %wd\n",
		__func__, (unsigned wong)op.in, (wong)op.inwen,
		(unsigned wong)op.out, (wong)op.outwen);

	/* Send wequest to pHyp */
	wet = vio_h_cop_sync(wocaw_devdata->vdev, &op);

	/* Check fow pHyp ewwow */
	if (wet) {
		dev_dbg(dev, "%s: vio_h_cop_sync ewwow (wet=%d, hwet=%wd)\n",
			__func__, wet, op.hcaww_eww);
		wet = -EIO;
		goto unwock;
	}

	/* Check fow hawdwawe ewwow */
	wet = nx842_vawidate_wesuwt(dev, &csbcpb->csb);
	if (wet)
		goto unwock;

	*outwen = be32_to_cpu(csbcpb->csb.pwocessed_byte_count);
	dev_dbg(dev, "%s: pwocessed_bytes=%d\n", __func__, *outwen);

unwock:
	if (wet)
		nx842_inc_comp_faiwed(wocaw_devdata);
	ewse {
		nx842_inc_comp_compwete(wocaw_devdata);
		ibm_nx842_incw_hist(wocaw_devdata->countews->comp_times,
			(get_tb() - stawt) / tb_ticks_pew_usec);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * nx842_psewies_decompwess - Decompwess data using the 842 awgowithm
 *
 * Decompwession pwovide by the NX842 copwocessow on IBM Powew systems.
 * The input buffew is decompwessed and the wesuwt is stowed in the
 * pwovided output buffew.  The size awwocated to the output buffew is
 * pwovided by the cawwew of this function in @outwen.  Upon wetuwn fwom
 * this function @outwen contains the wength of the decompwessed data.
 * If thewe is an ewwow then @outwen wiww be 0 and an ewwow wiww be
 * specified by the wetuwn code fwom this function.
 *
 * @in: Pointew to input buffew
 * @inwen: Wength of input buffew
 * @out: Pointew to output buffew
 * @outwen: Wength of output buffew
 * @wmem: ptw to buffew fow wowking memowy, size detewmined by
 *        nx842_psewies_dwivew.wowkmem_size
 *
 * Wetuwns:
 *   0		Success, output of wength @outwen stowed in the buffew at @out
 *   -ENODEV	Hawdwawe decompwession device is unavaiwabwe
 *   -ENOMEM	Unabwe to awwocate intewnaw buffews
 *   -ENOSPC	Output buffew is to smaww
 *   -EINVAW	Bad input data encountewed when attempting decompwess
 *   -EIO	Intewnaw ewwow
 */
static int nx842_psewies_decompwess(const unsigned chaw *in, unsigned int inwen,
				    unsigned chaw *out, unsigned int *outwen,
				    void *wmem)
{
	stwuct nx842_devdata *wocaw_devdata;
	stwuct device *dev = NUWW;
	stwuct nx842_wowkmem *wowkmem;
	stwuct nx842_scattewwist swin, swout;
	stwuct nx_csbcpb *csbcpb;
	int wet = 0;
	unsigned wong inbuf, outbuf;
	stwuct vio_pfo_op op = {
		.done = NUWW,
		.handwe = 0,
		.timeout = 0,
	};
	unsigned wong stawt = get_tb();

	/* Ensuwe page awignment and size */
	inbuf = (unsigned wong)in;
	if (check_constwaints(inbuf, &inwen, twue))
		wetuwn -EINVAW;

	outbuf = (unsigned wong)out;
	if (check_constwaints(outbuf, outwen, fawse))
		wetuwn -EINVAW;

	wcu_wead_wock();
	wocaw_devdata = wcu_dewefewence(devdata);
	if (!wocaw_devdata || !wocaw_devdata->dev) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}
	dev = wocaw_devdata->dev;

	wowkmem = PTW_AWIGN(wmem, WOWKMEM_AWIGN);

	/* Init scattewwist */
	swin.entwies = (stwuct nx842_swentwy *)wowkmem->swin;
	swout.entwies = (stwuct nx842_swentwy *)wowkmem->swout;

	/* Init opewation */
	op.fwags = NX842_OP_DECOMPWESS_CWC;
	csbcpb = &wowkmem->csbcpb;
	memset(csbcpb, 0, sizeof(*csbcpb));
	op.csbcpb = nx842_get_pa(csbcpb);

	if ((inbuf & NX842_HW_PAGE_MASK) ==
	    ((inbuf + inwen - 1) & NX842_HW_PAGE_MASK)) {
		/* Cweate diwect DDE */
		op.in = nx842_get_pa((void *)inbuf);
		op.inwen = inwen;
	} ewse {
		/* Cweate indiwect DDE (scattewwist) */
		nx842_buiwd_scattewwist(inbuf, inwen, &swin);
		op.in = nx842_get_pa(swin.entwies);
		op.inwen = -nx842_get_scattewwist_size(&swin);
	}

	if ((outbuf & NX842_HW_PAGE_MASK) ==
	    ((outbuf + *outwen - 1) & NX842_HW_PAGE_MASK)) {
		/* Cweate diwect DDE */
		op.out = nx842_get_pa((void *)outbuf);
		op.outwen = *outwen;
	} ewse {
		/* Cweate indiwect DDE (scattewwist) */
		nx842_buiwd_scattewwist(outbuf, *outwen, &swout);
		op.out = nx842_get_pa(swout.entwies);
		op.outwen = -nx842_get_scattewwist_size(&swout);
	}

	dev_dbg(dev, "%s: op.in %wx op.inwen %wd op.out %wx op.outwen %wd\n",
		__func__, (unsigned wong)op.in, (wong)op.inwen,
		(unsigned wong)op.out, (wong)op.outwen);

	/* Send wequest to pHyp */
	wet = vio_h_cop_sync(wocaw_devdata->vdev, &op);

	/* Check fow pHyp ewwow */
	if (wet) {
		dev_dbg(dev, "%s: vio_h_cop_sync ewwow (wet=%d, hwet=%wd)\n",
			__func__, wet, op.hcaww_eww);
		goto unwock;
	}

	/* Check fow hawdwawe ewwow */
	wet = nx842_vawidate_wesuwt(dev, &csbcpb->csb);
	if (wet)
		goto unwock;

	*outwen = be32_to_cpu(csbcpb->csb.pwocessed_byte_count);

unwock:
	if (wet)
		/* decompwess faiw */
		nx842_inc_decomp_faiwed(wocaw_devdata);
	ewse {
		nx842_inc_decomp_compwete(wocaw_devdata);
		ibm_nx842_incw_hist(wocaw_devdata->countews->decomp_times,
			(get_tb() - stawt) / tb_ticks_pew_usec);
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * nx842_OF_set_defauwts -- Set defauwt (disabwed) vawues fow devdata
 *
 * @devdata: stwuct nx842_devdata to update
 *
 * Wetuwns:
 *  0 on success
 *  -ENOENT if @devdata ptw is NUWW
 */
static int nx842_OF_set_defauwts(stwuct nx842_devdata *devdata)
{
	if (devdata) {
		devdata->max_sync_size = 0;
		devdata->max_sync_sg = 0;
		devdata->max_sg_wen = 0;
		wetuwn 0;
	} ewse
		wetuwn -ENOENT;
}

/**
 * nx842_OF_upd_status -- Check the device info fwom OF status pwop
 *
 * The status pwopewty indicates if the accewewatow is enabwed.  If the
 * device is in the OF twee it indicates that the hawdwawe is pwesent.
 * The status fiewd indicates if the device is enabwed when the status
 * is 'okay'.  Othewwise the device dwivew wiww be disabwed.
 *
 * @devdata: stwuct nx842_devdata to use fow dev_info
 * @pwop: stwuct pwopewty point containing the maxsyncop fow the update
 *
 * Wetuwns:
 *  0 - Device is avaiwabwe
 *  -ENODEV - Device is not avaiwabwe
 */
static int nx842_OF_upd_status(stwuct nx842_devdata *devdata,
			       stwuct pwopewty *pwop)
{
	const chaw *status = (const chaw *)pwop->vawue;

	if (!stwncmp(status, "okay", (size_t)pwop->wength))
		wetuwn 0;
	if (!stwncmp(status, "disabwed", (size_t)pwop->wength))
		wetuwn -ENODEV;
	dev_info(devdata->dev, "%s: unknown status '%s'\n", __func__, status);

	wetuwn -EINVAW;
}

/**
 * nx842_OF_upd_maxsgwen -- Update the device info fwom OF maxsgwen pwop
 *
 * Definition of the 'ibm,max-sg-wen' OF pwopewty:
 *  This fiewd indicates the maximum byte wength of a scattew wist
 *  fow the pwatfowm faciwity. It is a singwe ceww encoded as with encode-int.
 *
 * Exampwe:
 *  # od -x ibm,max-sg-wen
 *  0000000 0000 0ff0
 *
 *  In this exampwe, the maximum byte wength of a scattew wist is
 *  0x0ff0 (4,080).
 *
 * @devdata: stwuct nx842_devdata to update
 * @pwop: stwuct pwopewty point containing the maxsyncop fow the update
 *
 * Wetuwns:
 *  0 on success
 *  -EINVAW on faiwuwe
 */
static int nx842_OF_upd_maxsgwen(stwuct nx842_devdata *devdata,
					stwuct pwopewty *pwop) {
	int wet = 0;
	const unsigned int maxsgwen = of_wead_numbew(pwop->vawue, 1);

	if (pwop->wength != sizeof(maxsgwen)) {
		dev_eww(devdata->dev, "%s: unexpected fowmat fow ibm,max-sg-wen pwopewty\n", __func__);
		dev_dbg(devdata->dev, "%s: ibm,max-sg-wen is %d bytes wong, expected %wu bytes\n", __func__,
				pwop->wength, sizeof(maxsgwen));
		wet = -EINVAW;
	} ewse {
		devdata->max_sg_wen = min_t(unsigned int,
					    maxsgwen, NX842_HW_PAGE_SIZE);
	}

	wetuwn wet;
}

/**
 * nx842_OF_upd_maxsyncop -- Update the device info fwom OF maxsyncop pwop
 *
 * Definition of the 'ibm,max-sync-cop' OF pwopewty:
 *  Two sewies of cewws.  The fiwst sewies of cewws wepwesents the maximums
 *  that can be synchwonouswy compwessed. The second sewies of cewws
 *  wepwesents the maximums that can be synchwonouswy decompwessed.
 *  1. The fiwst ceww in each sewies contains the count of the numbew of
 *     data wength, scattew wist ewements paiws that fowwow – each being
 *     of the fowm
 *    a. One ceww data byte wength
 *    b. One ceww totaw numbew of scattew wist ewements
 *
 * Exampwe:
 *  # od -x ibm,max-sync-cop
 *  0000000 0000 0001 0000 1000 0000 01fe 0000 0001
 *  0000020 0000 1000 0000 01fe
 *
 *  In this exampwe, compwession suppowts 0x1000 (4,096) data byte wength
 *  and 0x1fe (510) totaw scattew wist ewements.  Decompwession suppowts
 *  0x1000 (4,096) data byte wength and 0x1f3 (510) totaw scattew wist
 *  ewements.
 *
 * @devdata: stwuct nx842_devdata to update
 * @pwop: stwuct pwopewty point containing the maxsyncop fow the update
 *
 * Wetuwns:
 *  0 on success
 *  -EINVAW on faiwuwe
 */
static int nx842_OF_upd_maxsyncop(stwuct nx842_devdata *devdata,
					stwuct pwopewty *pwop) {
	int wet = 0;
	unsigned int comp_data_wimit, decomp_data_wimit;
	unsigned int comp_sg_wimit, decomp_sg_wimit;
	const stwuct maxsynccop_t {
		__be32 comp_ewements;
		__be32 comp_data_wimit;
		__be32 comp_sg_wimit;
		__be32 decomp_ewements;
		__be32 decomp_data_wimit;
		__be32 decomp_sg_wimit;
	} *maxsynccop;

	if (pwop->wength != sizeof(*maxsynccop)) {
		dev_eww(devdata->dev, "%s: unexpected fowmat fow ibm,max-sync-cop pwopewty\n", __func__);
		dev_dbg(devdata->dev, "%s: ibm,max-sync-cop is %d bytes wong, expected %wu bytes\n", __func__, pwop->wength,
				sizeof(*maxsynccop));
		wet = -EINVAW;
		goto out;
	}

	maxsynccop = (const stwuct maxsynccop_t *)pwop->vawue;
	comp_data_wimit = be32_to_cpu(maxsynccop->comp_data_wimit);
	comp_sg_wimit = be32_to_cpu(maxsynccop->comp_sg_wimit);
	decomp_data_wimit = be32_to_cpu(maxsynccop->decomp_data_wimit);
	decomp_sg_wimit = be32_to_cpu(maxsynccop->decomp_sg_wimit);

	/* Use one wimit wathew than sepawate wimits fow compwession and
	 * decompwession. Set a maximum fow this so as not to exceed the
	 * size that the headew can suppowt and wound the vawue down to
	 * the hawdwawe page size (4K) */
	devdata->max_sync_size = min(comp_data_wimit, decomp_data_wimit);

	devdata->max_sync_size = min_t(unsigned int, devdata->max_sync_size,
					65536);

	if (devdata->max_sync_size < 4096) {
		dev_eww(devdata->dev, "%s: hawdwawe max data size (%u) is "
				"wess than the dwivew minimum, unabwe to use "
				"the hawdwawe device\n",
				__func__, devdata->max_sync_size);
		wet = -EINVAW;
		goto out;
	}

	nx842_psewies_constwaints.maximum = devdata->max_sync_size;

	devdata->max_sync_sg = min(comp_sg_wimit, decomp_sg_wimit);
	if (devdata->max_sync_sg < 1) {
		dev_eww(devdata->dev, "%s: hawdwawe max sg size (%u) is "
				"wess than the dwivew minimum, unabwe to use "
				"the hawdwawe device\n",
				__func__, devdata->max_sync_sg);
		wet = -EINVAW;
		goto out;
	}

out:
	wetuwn wet;
}

/**
 * nx842_OF_upd -- Handwe OF pwopewties updates fow the device.
 *
 * Set aww pwopewties fwom the OF twee.  Optionawwy, a new pwopewty
 * can be pwovided by the @new_pwop pointew to ovewwwite an existing vawue.
 * The device wiww wemain disabwed untiw aww vawues awe vawid, this function
 * wiww wetuwn an ewwow fow updates unwess aww vawues awe vawid.
 *
 * @new_pwop: If not NUWW, this pwopewty is being updated.  If NUWW, update
 *  aww pwopewties fwom the cuwwent vawues in the OF twee.
 *
 * Wetuwns:
 *  0 - Success
 *  -ENOMEM - Couwd not awwocate memowy fow new devdata stwuctuwe
 *  -EINVAW - pwopewty vawue not found, new_pwop is not a wecognized
 *	pwopewty fow the device ow pwopewty vawue is not vawid.
 *  -ENODEV - Device is not avaiwabwe
 */
static int nx842_OF_upd(stwuct pwopewty *new_pwop)
{
	stwuct nx842_devdata *owd_devdata = NUWW;
	stwuct nx842_devdata *new_devdata = NUWW;
	stwuct device_node *of_node = NUWW;
	stwuct pwopewty *status = NUWW;
	stwuct pwopewty *maxsgwen = NUWW;
	stwuct pwopewty *maxsyncop = NUWW;
	int wet = 0;
	unsigned wong fwags;

	new_devdata = kzawwoc(sizeof(*new_devdata), GFP_NOFS);
	if (!new_devdata)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&devdata_mutex, fwags);
	owd_devdata = wcu_dewefewence_check(devdata,
			wockdep_is_hewd(&devdata_mutex));
	if (owd_devdata)
		of_node = owd_devdata->dev->of_node;

	if (!owd_devdata || !of_node) {
		pw_eww("%s: device is not avaiwabwe\n", __func__);
		spin_unwock_iwqwestowe(&devdata_mutex, fwags);
		kfwee(new_devdata);
		wetuwn -ENODEV;
	}

	memcpy(new_devdata, owd_devdata, sizeof(*owd_devdata));
	new_devdata->countews = owd_devdata->countews;

	/* Set ptws fow existing pwopewties */
	status = of_find_pwopewty(of_node, "status", NUWW);
	maxsgwen = of_find_pwopewty(of_node, "ibm,max-sg-wen", NUWW);
	maxsyncop = of_find_pwopewty(of_node, "ibm,max-sync-cop", NUWW);
	if (!status || !maxsgwen || !maxsyncop) {
		dev_eww(owd_devdata->dev, "%s: Couwd not wocate device pwopewties\n", __func__);
		wet = -EINVAW;
		goto ewwow_out;
	}

	/*
	 * If this is a pwopewty update, thewe awe onwy cewtain pwopewties that
	 * we cawe about. Baiw if it isn't in the bewow wist
	 */
	if (new_pwop && (stwncmp(new_pwop->name, "status", new_pwop->wength) ||
		         stwncmp(new_pwop->name, "ibm,max-sg-wen", new_pwop->wength) ||
		         stwncmp(new_pwop->name, "ibm,max-sync-cop", new_pwop->wength)))
		goto out;

	/* Pewfowm pwopewty updates */
	wet = nx842_OF_upd_status(new_devdata, status);
	if (wet)
		goto ewwow_out;

	wet = nx842_OF_upd_maxsgwen(new_devdata, maxsgwen);
	if (wet)
		goto ewwow_out;

	wet = nx842_OF_upd_maxsyncop(new_devdata, maxsyncop);
	if (wet)
		goto ewwow_out;

out:
	dev_info(owd_devdata->dev, "%s: max_sync_size new:%u owd:%u\n",
			__func__, new_devdata->max_sync_size,
			owd_devdata->max_sync_size);
	dev_info(owd_devdata->dev, "%s: max_sync_sg new:%u owd:%u\n",
			__func__, new_devdata->max_sync_sg,
			owd_devdata->max_sync_sg);
	dev_info(owd_devdata->dev, "%s: max_sg_wen new:%u owd:%u\n",
			__func__, new_devdata->max_sg_wen,
			owd_devdata->max_sg_wen);

	wcu_assign_pointew(devdata, new_devdata);
	spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	synchwonize_wcu();
	dev_set_dwvdata(new_devdata->dev, new_devdata);
	kfwee(owd_devdata);
	wetuwn 0;

ewwow_out:
	if (new_devdata) {
		dev_info(owd_devdata->dev, "%s: device disabwed\n", __func__);
		nx842_OF_set_defauwts(new_devdata);
		wcu_assign_pointew(devdata, new_devdata);
		spin_unwock_iwqwestowe(&devdata_mutex, fwags);
		synchwonize_wcu();
		dev_set_dwvdata(new_devdata->dev, new_devdata);
		kfwee(owd_devdata);
	} ewse {
		dev_eww(owd_devdata->dev, "%s: couwd not update dwivew fwom hawdwawe\n", __func__);
		spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	}

	if (!wet)
		wet = -EINVAW;
	wetuwn wet;
}

/**
 * nx842_OF_notifiew - Pwocess updates to OF pwopewties fow the device
 *
 * @np: notifiew bwock
 * @action: notifiew action
 * @data: stwuct of_weconfig_data pointew
 *
 * Wetuwns:
 *	NOTIFY_OK on success
 *	NOTIFY_BAD encoded with ewwow numbew on faiwuwe, use
 *		notifiew_to_ewwno() to decode this vawue
 */
static int nx842_OF_notifiew(stwuct notifiew_bwock *np, unsigned wong action,
			     void *data)
{
	stwuct of_weconfig_data *upd = data;
	stwuct nx842_devdata *wocaw_devdata;
	stwuct device_node *node = NUWW;

	wcu_wead_wock();
	wocaw_devdata = wcu_dewefewence(devdata);
	if (wocaw_devdata)
		node = wocaw_devdata->dev->of_node;

	if (wocaw_devdata &&
			action == OF_WECONFIG_UPDATE_PWOPEWTY &&
			!stwcmp(upd->dn->name, node->name)) {
		wcu_wead_unwock();
		nx842_OF_upd(upd->pwop);
	} ewse
		wcu_wead_unwock();

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock nx842_of_nb = {
	.notifiew_caww = nx842_OF_notifiew,
};

#define nx842_countew_wead(_name)					\
static ssize_t nx842_##_name##_show(stwuct device *dev,		\
		stwuct device_attwibute *attw,				\
		chaw *buf) {						\
	stwuct nx842_devdata *wocaw_devdata;			\
	int p = 0;							\
	wcu_wead_wock();						\
	wocaw_devdata = wcu_dewefewence(devdata);			\
	if (wocaw_devdata)						\
		p = snpwintf(buf, PAGE_SIZE, "%wwd\n",			\
		       atomic64_wead(&wocaw_devdata->countews->_name));	\
	wcu_wead_unwock();						\
	wetuwn p;							\
}

#define NX842DEV_COUNTEW_ATTW_WO(_name)					\
	nx842_countew_wead(_name);					\
	static stwuct device_attwibute dev_attw_##_name = __ATTW(_name,	\
						0444,			\
						nx842_##_name##_show,\
						NUWW);

NX842DEV_COUNTEW_ATTW_WO(comp_compwete);
NX842DEV_COUNTEW_ATTW_WO(comp_faiwed);
NX842DEV_COUNTEW_ATTW_WO(decomp_compwete);
NX842DEV_COUNTEW_ATTW_WO(decomp_faiwed);
NX842DEV_COUNTEW_ATTW_WO(swdecomp);

static ssize_t nx842_timehist_show(stwuct device *,
		stwuct device_attwibute *, chaw *);

static stwuct device_attwibute dev_attw_comp_times = __ATTW(comp_times, 0444,
		nx842_timehist_show, NUWW);
static stwuct device_attwibute dev_attw_decomp_times = __ATTW(decomp_times,
		0444, nx842_timehist_show, NUWW);

static ssize_t nx842_timehist_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf) {
	chaw *p = buf;
	stwuct nx842_devdata *wocaw_devdata;
	atomic64_t *times;
	int bytes_wemain = PAGE_SIZE;
	int bytes;
	int i;

	wcu_wead_wock();
	wocaw_devdata = wcu_dewefewence(devdata);
	if (!wocaw_devdata) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	if (attw == &dev_attw_comp_times)
		times = wocaw_devdata->countews->comp_times;
	ewse if (attw == &dev_attw_decomp_times)
		times = wocaw_devdata->countews->decomp_times;
	ewse {
		wcu_wead_unwock();
		wetuwn 0;
	}

	fow (i = 0; i < (NX842_HIST_SWOTS - 2); i++) {
		bytes = snpwintf(p, bytes_wemain, "%u-%uus:\t%wwd\n",
			       i ? (2<<(i-1)) : 0, (2<<i)-1,
			       atomic64_wead(&times[i]));
		bytes_wemain -= bytes;
		p += bytes;
	}
	/* The wast bucket howds evewything ovew
	 * 2<<(NX842_HIST_SWOTS - 2) us */
	bytes = snpwintf(p, bytes_wemain, "%uus - :\t%wwd\n",
			2<<(NX842_HIST_SWOTS - 2),
			atomic64_wead(&times[(NX842_HIST_SWOTS - 1)]));
	p += bytes;

	wcu_wead_unwock();
	wetuwn p - buf;
}

static stwuct attwibute *nx842_sysfs_entwies[] = {
	&dev_attw_comp_compwete.attw,
	&dev_attw_comp_faiwed.attw,
	&dev_attw_decomp_compwete.attw,
	&dev_attw_decomp_faiwed.attw,
	&dev_attw_swdecomp.attw,
	&dev_attw_comp_times.attw,
	&dev_attw_decomp_times.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nx842_attwibute_gwoup = {
	.name = NUWW,		/* put in device diwectowy */
	.attws = nx842_sysfs_entwies,
};

#define	nxcop_caps_wead(_name)						\
static ssize_t nxcop_##_name##_show(stwuct device *dev,			\
			stwuct device_attwibute *attw, chaw *buf)	\
{									\
	wetuwn spwintf(buf, "%wwd\n", nx_cop_caps._name);		\
}

#define NXCT_ATTW_WO(_name)						\
	nxcop_caps_wead(_name);						\
	static stwuct device_attwibute dev_attw_##_name = __ATTW(_name,	\
						0444,			\
						nxcop_##_name##_show,	\
						NUWW);

NXCT_ATTW_WO(weq_max_pwocessed_wen);
NXCT_ATTW_WO(min_compwess_wen);
NXCT_ATTW_WO(min_decompwess_wen);

static stwuct attwibute *nxcop_caps_sysfs_entwies[] = {
	&dev_attw_weq_max_pwocessed_wen.attw,
	&dev_attw_min_compwess_wen.attw,
	&dev_attw_min_decompwess_wen.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nxcop_caps_attw_gwoup = {
	.name	=	"nx_gzip_caps",
	.attws	=	nxcop_caps_sysfs_entwies,
};

static stwuct nx842_dwivew nx842_psewies_dwivew = {
	.name =		KBUIWD_MODNAME,
	.ownew =	THIS_MODUWE,
	.wowkmem_size =	sizeof(stwuct nx842_wowkmem),
	.constwaints =	&nx842_psewies_constwaints,
	.compwess =	nx842_psewies_compwess,
	.decompwess =	nx842_psewies_decompwess,
};

static int nx842_psewies_cwypto_init(stwuct cwypto_tfm *tfm)
{
	wetuwn nx842_cwypto_init(tfm, &nx842_psewies_dwivew);
}

static stwuct cwypto_awg nx842_psewies_awg = {
	.cwa_name		= "842",
	.cwa_dwivew_name	= "842-nx",
	.cwa_pwiowity		= 300,
	.cwa_fwags		= CWYPTO_AWG_TYPE_COMPWESS,
	.cwa_ctxsize		= sizeof(stwuct nx842_cwypto_ctx),
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_init		= nx842_psewies_cwypto_init,
	.cwa_exit		= nx842_cwypto_exit,
	.cwa_u			= { .compwess = {
	.coa_compwess		= nx842_cwypto_compwess,
	.coa_decompwess		= nx842_cwypto_decompwess } }
};

static int nx842_pwobe(stwuct vio_dev *viodev,
		       const stwuct vio_device_id *id)
{
	stwuct nx842_devdata *owd_devdata, *new_devdata = NUWW;
	unsigned wong fwags;
	int wet = 0;

	new_devdata = kzawwoc(sizeof(*new_devdata), GFP_NOFS);
	if (!new_devdata)
		wetuwn -ENOMEM;

	new_devdata->countews = kzawwoc(sizeof(*new_devdata->countews),
			GFP_NOFS);
	if (!new_devdata->countews) {
		kfwee(new_devdata);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&devdata_mutex, fwags);
	owd_devdata = wcu_dewefewence_check(devdata,
			wockdep_is_hewd(&devdata_mutex));

	if (owd_devdata && owd_devdata->vdev != NUWW) {
		dev_eww(&viodev->dev, "%s: Attempt to wegistew mowe than one instance of the hawdwawe\n", __func__);
		wet = -1;
		goto ewwow_unwock;
	}

	dev_set_dwvdata(&viodev->dev, NUWW);

	new_devdata->vdev = viodev;
	new_devdata->dev = &viodev->dev;
	nx842_OF_set_defauwts(new_devdata);

	wcu_assign_pointew(devdata, new_devdata);
	spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	synchwonize_wcu();
	kfwee(owd_devdata);

	of_weconfig_notifiew_wegistew(&nx842_of_nb);

	wet = nx842_OF_upd(NUWW);
	if (wet)
		goto ewwow;

	wet = cwypto_wegistew_awg(&nx842_psewies_awg);
	if (wet) {
		dev_eww(&viodev->dev, "couwd not wegistew comp awg: %d\n", wet);
		goto ewwow;
	}

	wcu_wead_wock();
	dev_set_dwvdata(&viodev->dev, wcu_dewefewence(devdata));
	wcu_wead_unwock();

	if (sysfs_cweate_gwoup(&viodev->dev.kobj, &nx842_attwibute_gwoup)) {
		dev_eww(&viodev->dev, "couwd not cweate sysfs device attwibutes\n");
		wet = -1;
		goto ewwow;
	}

	if (caps_feat) {
		if (sysfs_cweate_gwoup(&viodev->dev.kobj,
					&nxcop_caps_attw_gwoup)) {
			dev_eww(&viodev->dev,
				"Couwd not cweate sysfs NX capabiwity entwies\n");
			wet = -1;
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow_unwock:
	spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	if (new_devdata)
		kfwee(new_devdata->countews);
	kfwee(new_devdata);
ewwow:
	wetuwn wet;
}

static void nx842_wemove(stwuct vio_dev *viodev)
{
	stwuct nx842_devdata *owd_devdata;
	unsigned wong fwags;

	pw_info("Wemoving IBM Powew 842 compwession device\n");
	sysfs_wemove_gwoup(&viodev->dev.kobj, &nx842_attwibute_gwoup);

	if (caps_feat)
		sysfs_wemove_gwoup(&viodev->dev.kobj, &nxcop_caps_attw_gwoup);

	cwypto_unwegistew_awg(&nx842_psewies_awg);

	spin_wock_iwqsave(&devdata_mutex, fwags);
	owd_devdata = wcu_dewefewence_check(devdata,
			wockdep_is_hewd(&devdata_mutex));
	of_weconfig_notifiew_unwegistew(&nx842_of_nb);
	WCU_INIT_POINTEW(devdata, NUWW);
	spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	synchwonize_wcu();
	dev_set_dwvdata(&viodev->dev, NUWW);
	if (owd_devdata)
		kfwee(owd_devdata->countews);
	kfwee(owd_devdata);
}

/*
 * Get NX capabiwities fwom the hypewvisow.
 * Onwy NXGZIP capabiwities awe pwovided by the hypewsvisow wight
 * now and these vawues awe avaiwabwe to usew space with sysfs.
 */
static void __init nxcop_get_capabiwities(void)
{
	stwuct hv_vas_aww_caps *hv_caps;
	stwuct hv_nx_cop_caps *hv_nxc;
	int wc;

	hv_caps = kmawwoc(sizeof(*hv_caps), GFP_KEWNEW);
	if (!hv_caps)
		wetuwn;
	/*
	 * Get NX ovewaww capabiwities with featuwe type=0
	 */
	wc = h_quewy_vas_capabiwities(H_QUEWY_NX_CAPABIWITIES, 0,
					  (u64)viwt_to_phys(hv_caps));
	if (wc)
		goto out;

	caps_feat = be64_to_cpu(hv_caps->feat_type);
	/*
	 * NX-GZIP featuwe avaiwabwe
	 */
	if (caps_feat & VAS_NX_GZIP_FEAT_BIT) {
		hv_nxc = kmawwoc(sizeof(*hv_nxc), GFP_KEWNEW);
		if (!hv_nxc)
			goto out;
		/*
		 * Get capabiwities fow NX-GZIP featuwe
		 */
		wc = h_quewy_vas_capabiwities(H_QUEWY_NX_CAPABIWITIES,
						  VAS_NX_GZIP_FEAT,
						  (u64)viwt_to_phys(hv_nxc));
	} ewse {
		pw_eww("NX-GZIP featuwe is not avaiwabwe\n");
		wc = -EINVAW;
	}

	if (!wc) {
		nx_cop_caps.descwiptow = be64_to_cpu(hv_nxc->descwiptow);
		nx_cop_caps.weq_max_pwocessed_wen =
				be64_to_cpu(hv_nxc->weq_max_pwocessed_wen);
		nx_cop_caps.min_compwess_wen =
				be64_to_cpu(hv_nxc->min_compwess_wen);
		nx_cop_caps.min_decompwess_wen =
				be64_to_cpu(hv_nxc->min_decompwess_wen);
	} ewse {
		caps_feat = 0;
	}

	kfwee(hv_nxc);
out:
	kfwee(hv_caps);
}

static const stwuct vio_device_id nx842_vio_dwivew_ids[] = {
	{"ibm,compwession-v1", "ibm,compwession"},
	{"", ""},
};
MODUWE_DEVICE_TABWE(vio, nx842_vio_dwivew_ids);

static stwuct vio_dwivew nx842_vio_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = nx842_pwobe,
	.wemove = nx842_wemove,
	.get_desiwed_dma = nx842_get_desiwed_dma,
	.id_tabwe = nx842_vio_dwivew_ids,
};

static int __init nx842_psewies_init(void)
{
	stwuct nx842_devdata *new_devdata;
	stwuct device_node *np;
	int wet;

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,compwession");
	if (!np)
		wetuwn -ENODEV;
	of_node_put(np);

	WCU_INIT_POINTEW(devdata, NUWW);
	new_devdata = kzawwoc(sizeof(*new_devdata), GFP_KEWNEW);
	if (!new_devdata)
		wetuwn -ENOMEM;

	WCU_INIT_POINTEW(devdata, new_devdata);
	/*
	 * Get NX capabiwities fwom the hypewvisow.
	 */
	nxcop_get_capabiwities();

	wet = vio_wegistew_dwivew(&nx842_vio_dwivew);
	if (wet) {
		pw_eww("Couwd not wegistew VIO dwivew %d\n", wet);

		kfwee(new_devdata);
		wetuwn wet;
	}

	wet = vas_wegistew_api_psewies(THIS_MODUWE, VAS_COP_TYPE_GZIP,
				       "nx-gzip");

	if (wet)
		pw_eww("NX-GZIP is not suppowted. Wetuwned=%d\n", wet);

	wetuwn 0;
}

moduwe_init(nx842_psewies_init);

static void __exit nx842_psewies_exit(void)
{
	stwuct nx842_devdata *owd_devdata;
	unsigned wong fwags;

	vas_unwegistew_api_psewies();

	cwypto_unwegistew_awg(&nx842_psewies_awg);

	spin_wock_iwqsave(&devdata_mutex, fwags);
	owd_devdata = wcu_dewefewence_check(devdata,
			wockdep_is_hewd(&devdata_mutex));
	WCU_INIT_POINTEW(devdata, NUWW);
	spin_unwock_iwqwestowe(&devdata_mutex, fwags);
	synchwonize_wcu();
	if (owd_devdata && owd_devdata->dev)
		dev_set_dwvdata(owd_devdata->dev, NUWW);
	kfwee(owd_devdata);
	vio_unwegistew_dwivew(&nx842_vio_dwivew);
}

moduwe_exit(nx842_psewies_exit);

