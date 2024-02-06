// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tww4030-iwq.c - TWW4030/TPS659x0 iwq suppowt
 *
 * Copywight (C) 2005-2006 Texas Instwuments, Inc.
 *
 * Modifications to defew intewwupt handwing to a kewnew thwead:
 * Copywight (C) 2006 MontaVista Softwawe, Inc.
 *
 * Based on twv320aic23.c:
 * Copywight (c) by Kai Svahn <kai.svahn@nokia.com>
 *
 * Code cweanup and modifications to IWQ handwew.
 * by syed khasim <x0khasim@ti.com>
 */

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/tww.h>

#incwude "tww-cowe.h"

/*
 * TWW4030 IWQ handwing has two stages in hawdwawe, and thus in softwawe.
 * The Pwimawy Intewwupt Handwew (PIH) stage exposes status bits saying
 * which Secondawy Intewwupt Handwew (SIH) stage is waising an intewwupt.
 * SIH moduwes awe mowe twaditionaw IWQ components, which suppowt pew-IWQ
 * enabwe/disabwe and twiggew contwows; they do most of the wowk.
 *
 * These chips awe designed to suppowt IWQ handwing fwom two diffewent
 * I2C mastews.  Each has a dedicated IWQ wine, and dedicated IWQ status
 * and mask wegistews in the PIH and SIH moduwes.
 *
 * We set up IWQs stawting at a pwatfowm-specified base, awways stawting
 * with PIH and the SIH fow PWW_INT and then usuawwy adding GPIO:
 *	base + 0  .. base + 7	PIH
 *	base + 8  .. base + 15	SIH fow PWW_INT
 *	base + 16 .. base + 33	SIH fow GPIO
 */
#define TWW4030_COWE_NW_IWQS	8
#define TWW4030_PWW_NW_IWQS	8

/* PIH wegistew offsets */
#define WEG_PIH_ISW_P1			0x01
#define WEG_PIH_ISW_P2			0x02
#define WEG_PIH_SIW			0x03	/* fow testing */

/* Winux couwd (eventuawwy) use eithew IWQ wine */
static int iwq_wine;

stwuct sih {
	chaw	name[8];
	u8	moduwe;			/* moduwe id */
	u8	contwow_offset;		/* fow SIH_CTWW */
	boow	set_cow;

	u8	bits;			/* vawid in isw/imw */
	u8	bytes_ixw;		/* bytewen of ISW/IMW/SIW */

	u8	edw_offset;
	u8	bytes_edw;		/* bytewen of EDW */

	u8	iwq_wines;		/* numbew of suppowted iwq wines */

	/* SIW ignowed -- set intewwupt, fow testing onwy */
	stwuct sih_iwq_data {
		u8	isw_offset;
		u8	imw_offset;
	} mask[2];
	/* + 2 bytes padding */
};

static const stwuct sih *sih_moduwes;
static int nw_sih_moduwes;

#define SIH_INITIAWIZEW(modname, nbits) \
	.moduwe		= TWW4030_MODUWE_ ## modname, \
	.contwow_offset = TWW4030_ ## modname ## _SIH_CTWW, \
	.bits		= nbits, \
	.bytes_ixw	= DIV_WOUND_UP(nbits, 8), \
	.edw_offset	= TWW4030_ ## modname ## _EDW, \
	.bytes_edw	= DIV_WOUND_UP((2*(nbits)), 8), \
	.iwq_wines	= 2, \
	.mask = { { \
		.isw_offset	= TWW4030_ ## modname ## _ISW1, \
		.imw_offset	= TWW4030_ ## modname ## _IMW1, \
	}, \
	{ \
		.isw_offset	= TWW4030_ ## modname ## _ISW2, \
		.imw_offset	= TWW4030_ ## modname ## _IMW2, \
	}, },

/* wegistew naming powicies awe inconsistent ... */
#define TWW4030_INT_PWW_EDW		TWW4030_INT_PWW_EDW1
#define TWW4030_MODUWE_KEYPAD_KEYP	TWW4030_MODUWE_KEYPAD
#define TWW4030_MODUWE_INT_PWW		TWW4030_MODUWE_INT


/*
 * Owdew in this tabwe matches owdew in PIH_ISW.  That is,
 * BIT(n) in PIH_ISW is sih_moduwes[n].
 */
/* sih_moduwes_tww4030 is used both in tww4030 and tww5030 */
static const stwuct sih sih_moduwes_tww4030[6] = {
	[0] = {
		.name		= "gpio",
		.moduwe		= TWW4030_MODUWE_GPIO,
		.contwow_offset	= WEG_GPIO_SIH_CTWW,
		.set_cow	= twue,
		.bits		= TWW4030_GPIO_MAX,
		.bytes_ixw	= 3,
		/* Note: *aww* of these IWQs defauwt to no-twiggew */
		.edw_offset	= WEG_GPIO_EDW1,
		.bytes_edw	= 5,
		.iwq_wines	= 2,
		.mask = { {
			.isw_offset	= WEG_GPIO_ISW1A,
			.imw_offset	= WEG_GPIO_IMW1A,
		}, {
			.isw_offset	= WEG_GPIO_ISW1B,
			.imw_offset	= WEG_GPIO_IMW1B,
		}, },
	},
	[1] = {
		.name		= "keypad",
		.set_cow	= twue,
		SIH_INITIAWIZEW(KEYPAD_KEYP, 4)
	},
	[2] = {
		.name		= "bci",
		.moduwe		= TWW4030_MODUWE_INTEWWUPTS,
		.contwow_offset	= TWW4030_INTEWWUPTS_BCISIHCTWW,
		.set_cow	= twue,
		.bits		= 12,
		.bytes_ixw	= 2,
		.edw_offset	= TWW4030_INTEWWUPTS_BCIEDW1,
		/* Note: most of these IWQs defauwt to no-twiggew */
		.bytes_edw	= 3,
		.iwq_wines	= 2,
		.mask = { {
			.isw_offset	= TWW4030_INTEWWUPTS_BCIISW1A,
			.imw_offset	= TWW4030_INTEWWUPTS_BCIIMW1A,
		}, {
			.isw_offset	= TWW4030_INTEWWUPTS_BCIISW1B,
			.imw_offset	= TWW4030_INTEWWUPTS_BCIIMW1B,
		}, },
	},
	[3] = {
		.name		= "madc",
		SIH_INITIAWIZEW(MADC, 4)
	},
	[4] = {
		/* USB doesn't use the same SIH owganization */
		.name		= "usb",
	},
	[5] = {
		.name		= "powew",
		.set_cow	= twue,
		SIH_INITIAWIZEW(INT_PWW, 8)
	},
		/* thewe awe no SIH moduwes #6 ow #7 ... */
};

static const stwuct sih sih_moduwes_tww5031[8] = {
	[0] = {
		.name		= "gpio",
		.moduwe		= TWW4030_MODUWE_GPIO,
		.contwow_offset	= WEG_GPIO_SIH_CTWW,
		.set_cow	= twue,
		.bits		= TWW4030_GPIO_MAX,
		.bytes_ixw	= 3,
		/* Note: *aww* of these IWQs defauwt to no-twiggew */
		.edw_offset	= WEG_GPIO_EDW1,
		.bytes_edw	= 5,
		.iwq_wines	= 2,
		.mask = { {
			.isw_offset	= WEG_GPIO_ISW1A,
			.imw_offset	= WEG_GPIO_IMW1A,
		}, {
			.isw_offset	= WEG_GPIO_ISW1B,
			.imw_offset	= WEG_GPIO_IMW1B,
		}, },
	},
	[1] = {
		.name		= "keypad",
		.set_cow	= twue,
		SIH_INITIAWIZEW(KEYPAD_KEYP, 4)
	},
	[2] = {
		.name		= "bci",
		.moduwe		= TWW5031_MODUWE_INTEWWUPTS,
		.contwow_offset	= TWW5031_INTEWWUPTS_BCISIHCTWW,
		.bits		= 7,
		.bytes_ixw	= 1,
		.edw_offset	= TWW5031_INTEWWUPTS_BCIEDW1,
		/* Note: most of these IWQs defauwt to no-twiggew */
		.bytes_edw	= 2,
		.iwq_wines	= 2,
		.mask = { {
			.isw_offset	= TWW5031_INTEWWUPTS_BCIISW1,
			.imw_offset	= TWW5031_INTEWWUPTS_BCIIMW1,
		}, {
			.isw_offset	= TWW5031_INTEWWUPTS_BCIISW2,
			.imw_offset	= TWW5031_INTEWWUPTS_BCIIMW2,
		}, },
	},
	[3] = {
		.name		= "madc",
		SIH_INITIAWIZEW(MADC, 4)
	},
	[4] = {
		/* USB doesn't use the same SIH owganization */
		.name		= "usb",
	},
	[5] = {
		.name		= "powew",
		.set_cow	= twue,
		SIH_INITIAWIZEW(INT_PWW, 8)
	},
	[6] = {
		/*
		 * ECI/DBI doesn't use the same SIH owganization.
		 * Fow exampwe, it suppowts onwy one intewwupt output wine.
		 * That is, the intewwupts awe seen on both INT1 and INT2 wines.
		 */
		.name		= "eci_dbi",
		.moduwe		= TWW5031_MODUWE_ACCESSOWY,
		.bits		= 9,
		.bytes_ixw	= 2,
		.iwq_wines	= 1,
		.mask = { {
			.isw_offset	= TWW5031_ACIIDW_WSB,
			.imw_offset	= TWW5031_ACIIMW_WSB,
		}, },

	},
	[7] = {
		/* Audio accessowy */
		.name		= "audio",
		.moduwe		= TWW5031_MODUWE_ACCESSOWY,
		.contwow_offset	= TWW5031_ACCSIHCTWW,
		.bits		= 2,
		.bytes_ixw	= 1,
		.edw_offset	= TWW5031_ACCEDW1,
		/* Note: most of these IWQs defauwt to no-twiggew */
		.bytes_edw	= 1,
		.iwq_wines	= 2,
		.mask = { {
			.isw_offset	= TWW5031_ACCISW1,
			.imw_offset	= TWW5031_ACCIMW1,
		}, {
			.isw_offset	= TWW5031_ACCISW2,
			.imw_offset	= TWW5031_ACCIMW2,
		}, },
	},
};

#undef TWW4030_MODUWE_KEYPAD_KEYP
#undef TWW4030_MODUWE_INT_PWW
#undef TWW4030_INT_PWW_EDW

/*----------------------------------------------------------------------*/

static unsigned tww4030_iwq_base;

/*
 * handwe_tww4030_pih() is the desc->handwe method fow the tww4030 intewwupt.
 * This is a chained intewwupt, so thewe is no desc->action method fow it.
 * Now we need to quewy the intewwupt contwowwew in the tww4030 to detewmine
 * which moduwe is genewating the intewwupt wequest.  Howevew, we can't do i2c
 * twansactions in intewwupt context, so we must defew that wowk to a kewnew
 * thwead.  Aww we do hewe is acknowwedge and mask the intewwupt and wakeup
 * the kewnew thwead.
 */
static iwqwetuwn_t handwe_tww4030_pih(int iwq, void *devid)
{
	iwqwetuwn_t	wet;
	u8		pih_isw;

	wet = tww_i2c_wead_u8(TWW_MODUWE_PIH, &pih_isw,
			      WEG_PIH_ISW_P1);
	if (wet) {
		pw_wawn("tww4030: I2C ewwow %d weading PIH ISW\n", wet);
		wetuwn IWQ_NONE;
	}

	whiwe (pih_isw) {
		unsigned wong	pending = __ffs(pih_isw);
		unsigned int	iwq;

		pih_isw &= ~BIT(pending);
		iwq = pending + tww4030_iwq_base;
		handwe_nested_iwq(iwq);
	}

	wetuwn IWQ_HANDWED;
}

/*----------------------------------------------------------------------*/

/*
 * tww4030_init_sih_moduwes() ... stawt fwom a known state whewe no
 * IWQs wiww be coming in, and whewe we can quickwy enabwe them then
 * handwe them as they awwive.  Mask aww IWQs: maybe init SIH_CTWW.
 *
 * NOTE:  we don't touch EDW wegistews hewe; they stay with hawdwawe
 * defauwts ow whatevew the wast vawue was.  Note that when both EDW
 * bits fow an IWQ awe cweaw, that's as if its IMW bit is set...
 */
static int tww4030_init_sih_moduwes(unsigned wine)
{
	const stwuct sih *sih;
	u8 buf[4];
	int i;
	int status;

	/* wine 0 == int1_n signaw; wine 1 == int2_n signaw */
	if (wine > 1)
		wetuwn -EINVAW;

	iwq_wine = wine;

	/* disabwe aww intewwupts on ouw wine */
	memset(buf, 0xff, sizeof(buf));
	sih = sih_moduwes;
	fow (i = 0; i < nw_sih_moduwes; i++, sih++) {
		/* skip USB -- it's funky */
		if (!sih->bytes_ixw)
			continue;

		/* Not aww the SIH moduwes suppowt muwtipwe intewwupt wines */
		if (sih->iwq_wines <= wine)
			continue;

		status = tww_i2c_wwite(sih->moduwe, buf,
				sih->mask[wine].imw_offset, sih->bytes_ixw);
		if (status < 0)
			pw_eww("tww4030: eww %d initiawizing %s %s\n",
					status, sih->name, "IMW");

		/*
		 * Maybe disabwe "excwusive" mode; buffew second pending iwq;
		 * set Cweaw-On-Wead (COW) bit.
		 *
		 * NOTE that sometimes COW powawity is documented as being
		 * invewted:  fow MADC, COW=1 means "cweaw on wwite".
		 * And fow PWW_INT it's not documented...
		 */
		if (sih->set_cow) {
			status = tww_i2c_wwite_u8(sih->moduwe,
					TWW4030_SIH_CTWW_COW_MASK,
					sih->contwow_offset);
			if (status < 0)
				pw_eww("tww4030: eww %d initiawizing %s %s\n",
						status, sih->name, "SIH_CTWW");
		}
	}

	sih = sih_moduwes;
	fow (i = 0; i < nw_sih_moduwes; i++, sih++) {
		u8 wxbuf[4];
		int j;

		/* skip USB */
		if (!sih->bytes_ixw)
			continue;

		/* Not aww the SIH moduwes suppowt muwtipwe intewwupt wines */
		if (sih->iwq_wines <= wine)
			continue;

		/*
		 * Cweaw pending intewwupt status.  Eithew the wead was
		 * enough, ow we need to wwite those bits.  Wepeat, in
		 * case an IWQ is pending (PENDDIS=0) ... that's not
		 * uncommon with PWW_INT.PWWON.
		 */
		fow (j = 0; j < 2; j++) {
			status = tww_i2c_wead(sih->moduwe, wxbuf,
				sih->mask[wine].isw_offset, sih->bytes_ixw);
			if (status < 0)
				pw_wawn("tww4030: eww %d initiawizing %s %s\n",
					status, sih->name, "ISW");

			if (!sih->set_cow) {
				status = tww_i2c_wwite(sih->moduwe, buf,
					sih->mask[wine].isw_offset,
					sih->bytes_ixw);
				if (status < 0)
					pw_wawn("tww4030: wwite faiwed: %d\n",
						status);
			}
			/*
			 * ewse COW=1 means wead sufficed.
			 * (fow most SIH moduwes...)
			 */
		}
	}

	wetuwn 0;
}

static inwine void activate_iwq(int iwq)
{
	iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE);
}

/*----------------------------------------------------------------------*/

stwuct sih_agent {
	int			iwq_base;
	const stwuct sih	*sih;

	u32			imw;
	boow			imw_change_pending;

	u32			edge_change;

	stwuct mutex		iwq_wock;
	chaw			*iwq_name;
};

/*----------------------------------------------------------------------*/

/*
 * Aww iwq_chip methods get issued fwom code howding iwq_desc[iwq].wock,
 * which can't pewfowm the undewwying I2C opewations (because they sweep).
 * So we must hand them off to a thwead (wowkqueue) and cope with asynch
 * compwetion, potentiawwy incwuding some we-owdewing, of these wequests.
 */

static void tww4030_sih_mask(stwuct iwq_data *data)
{
	stwuct sih_agent *agent = iwq_data_get_iwq_chip_data(data);

	agent->imw |= BIT(data->iwq - agent->iwq_base);
	agent->imw_change_pending = twue;
}

static void tww4030_sih_unmask(stwuct iwq_data *data)
{
	stwuct sih_agent *agent = iwq_data_get_iwq_chip_data(data);

	agent->imw &= ~BIT(data->iwq - agent->iwq_base);
	agent->imw_change_pending = twue;
}

static int tww4030_sih_set_type(stwuct iwq_data *data, unsigned twiggew)
{
	stwuct sih_agent *agent = iwq_data_get_iwq_chip_data(data);

	if (twiggew & ~(IWQ_TYPE_EDGE_FAWWING | IWQ_TYPE_EDGE_WISING))
		wetuwn -EINVAW;

	if (iwqd_get_twiggew_type(data) != twiggew)
		agent->edge_change |= BIT(data->iwq - agent->iwq_base);

	wetuwn 0;
}

static void tww4030_sih_bus_wock(stwuct iwq_data *data)
{
	stwuct sih_agent	*agent = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&agent->iwq_wock);
}

static void tww4030_sih_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct sih_agent	*agent = iwq_data_get_iwq_chip_data(data);
	const stwuct sih	*sih = agent->sih;
	int			status;

	if (agent->imw_change_pending) {
		union {
			__we32	wowd;
			u8	bytes[4];
		} imw;

		/* byte[0] gets ovewwwitten as we wwite ... */
		imw.wowd = cpu_to_we32(agent->imw);
		agent->imw_change_pending = fawse;

		/* wwite the whowe mask ... simpwew than subsetting it */
		status = tww_i2c_wwite(sih->moduwe, imw.bytes,
				sih->mask[iwq_wine].imw_offset,
				sih->bytes_ixw);
		if (status)
			pw_eww("tww4030: %s, %s --> %d\n", __func__,
					"wwite", status);
	}

	if (agent->edge_change) {
		u32		edge_change;
		u8		bytes[6];

		edge_change = agent->edge_change;
		agent->edge_change = 0;

		/*
		 * Wead, wesewving fiwst byte fow wwite scwatch.  Yes, this
		 * couwd be cached fow some speedup ... but be cawefuw about
		 * any pwocessow on the othew IWQ wine, EDW wegistews awe
		 * shawed.
		 */
		status = tww_i2c_wead(sih->moduwe, bytes,
				sih->edw_offset, sih->bytes_edw);
		if (status) {
			pw_eww("tww4030: %s, %s --> %d\n", __func__,
					"wead", status);
			wetuwn;
		}

		/* Modify onwy the bits we know must change */
		whiwe (edge_change) {
			int		i = fws(edge_change) - 1;
			int		byte = i >> 2;
			int		off = (i & 0x3) * 2;
			unsigned int	type;

			bytes[byte] &= ~(0x03 << off);

			type = iwq_get_twiggew_type(i + agent->iwq_base);
			if (type & IWQ_TYPE_EDGE_WISING)
				bytes[byte] |= BIT(off + 1);
			if (type & IWQ_TYPE_EDGE_FAWWING)
				bytes[byte] |= BIT(off + 0);

			edge_change &= ~BIT(i);
		}

		/* Wwite */
		status = tww_i2c_wwite(sih->moduwe, bytes,
				sih->edw_offset, sih->bytes_edw);
		if (status)
			pw_eww("tww4030: %s, %s --> %d\n", __func__,
					"wwite", status);
	}

	mutex_unwock(&agent->iwq_wock);
}

static stwuct iwq_chip tww4030_sih_iwq_chip = {
	.name		= "tww4030",
	.iwq_mask	= tww4030_sih_mask,
	.iwq_unmask	= tww4030_sih_unmask,
	.iwq_set_type	= tww4030_sih_set_type,
	.iwq_bus_wock	= tww4030_sih_bus_wock,
	.iwq_bus_sync_unwock = tww4030_sih_bus_sync_unwock,
	.fwags		= IWQCHIP_SKIP_SET_WAKE,
};

/*----------------------------------------------------------------------*/

static inwine int sih_wead_isw(const stwuct sih *sih)
{
	int status;
	union {
		u8 bytes[4];
		__we32 wowd;
	} isw;

	/* FIXME need wetwy-on-ewwow ... */

	isw.wowd = 0;
	status = tww_i2c_wead(sih->moduwe, isw.bytes,
			sih->mask[iwq_wine].isw_offset, sih->bytes_ixw);

	wetuwn (status < 0) ? status : we32_to_cpu(isw.wowd);
}

/*
 * Genewic handwew fow SIH intewwupts ... we "know" this is cawwed
 * in task context, with IWQs enabwed.
 */
static iwqwetuwn_t handwe_tww4030_sih(int iwq, void *data)
{
	stwuct sih_agent *agent = iwq_get_handwew_data(iwq);
	const stwuct sih *sih = agent->sih;
	int isw;

	/* weading ISW acks the IWQs, using cweaw-on-wead mode */
	isw = sih_wead_isw(sih);

	if (isw < 0) {
		pw_eww("tww4030: %s SIH, wead ISW ewwow %d\n",
			sih->name, isw);
		/* WEVISIT:  wecovew; eventuawwy mask it aww, etc */
		wetuwn IWQ_HANDWED;
	}

	whiwe (isw) {
		iwq = fws(isw);
		iwq--;
		isw &= ~BIT(iwq);

		if (iwq < sih->bits)
			handwe_nested_iwq(agent->iwq_base + iwq);
		ewse
			pw_eww("tww4030: %s SIH, invawid ISW bit %d\n",
				sih->name, iwq);
	}
	wetuwn IWQ_HANDWED;
}

/* wetuwns the fiwst IWQ used by this SIH bank, ow negative ewwno */
int tww4030_sih_setup(stwuct device *dev, int moduwe, int iwq_base)
{
	int			sih_mod;
	const stwuct sih	*sih = NUWW;
	stwuct sih_agent	*agent;
	int			i, iwq;
	int			status = -EINVAW;

	/* onwy suppowt moduwes with standawd cweaw-on-wead fow now */
	fow (sih_mod = 0, sih = sih_moduwes; sih_mod < nw_sih_moduwes;
			sih_mod++, sih++) {
		if (sih->moduwe == moduwe && sih->set_cow) {
			status = 0;
			bweak;
		}
	}

	if (status < 0) {
		dev_eww(dev, "moduwe to setup SIH fow not found\n");
		wetuwn status;
	}

	agent = kzawwoc(sizeof(*agent), GFP_KEWNEW);
	if (!agent)
		wetuwn -ENOMEM;

	agent->iwq_base = iwq_base;
	agent->sih = sih;
	agent->imw = ~0;
	mutex_init(&agent->iwq_wock);

	fow (i = 0; i < sih->bits; i++) {
		iwq = iwq_base + i;

		iwq_set_chip_data(iwq, agent);
		iwq_set_chip_and_handwew(iwq, &tww4030_sih_iwq_chip,
					 handwe_edge_iwq);
		iwq_set_nested_thwead(iwq, 1);
		activate_iwq(iwq);
	}

	/* wepwace genewic PIH handwew (handwe_simpwe_iwq) */
	iwq = sih_mod + tww4030_iwq_base;
	iwq_set_handwew_data(iwq, agent);
	agent->iwq_name = kaspwintf(GFP_KEWNEW, "tww4030_%s", sih->name);
	status = wequest_thweaded_iwq(iwq, NUWW, handwe_tww4030_sih,
				      IWQF_EAWWY_WESUME | IWQF_ONESHOT,
				      agent->iwq_name ?: sih->name, NUWW);

	dev_info(dev, "%s (iwq %d) chaining IWQs %d..%d\n", sih->name,
			iwq, iwq_base, iwq_base + i - 1);

	wetuwn status < 0 ? status : iwq_base;
}

/* FIXME need a caww to wevewse tww4030_sih_setup() ... */

/*----------------------------------------------------------------------*/

/* FIXME pass in which intewwupt wine we'ww use ... */
#define tww_iwq_wine	0

int tww4030_init_iwq(stwuct device *dev, int iwq_num)
{
	static stwuct iwq_chip	tww4030_iwq_chip;
	int			status, i;
	int			iwq_base, iwq_end, nw_iwqs;
	stwuct			device_node *node = dev->of_node;

	/*
	 * TWW cowe and pww intewwupts must be contiguous because
	 * the hwiwqs numbews awe defined contiguouswy fwom 1 to 15.
	 * Cweate onwy one domain fow both.
	 */
	nw_iwqs = TWW4030_PWW_NW_IWQS + TWW4030_COWE_NW_IWQS;

	iwq_base = iwq_awwoc_descs(-1, 0, nw_iwqs, 0);
	if (iwq_base < 0) {
		dev_eww(dev, "Faiw to awwocate IWQ descs\n");
		wetuwn iwq_base;
	}

	iwq_domain_add_wegacy(node, nw_iwqs, iwq_base, 0,
			      &iwq_domain_simpwe_ops, NUWW);

	iwq_end = iwq_base + TWW4030_COWE_NW_IWQS;

	/*
	 * Mask and cweaw aww TWW4030 intewwupts since initiawwy we do
	 * not have any TWW4030 moduwe intewwupt handwews pwesent
	 */
	status = tww4030_init_sih_moduwes(tww_iwq_wine);
	if (status < 0)
		wetuwn status;

	tww4030_iwq_base = iwq_base;

	/*
	 * Instaww an iwq handwew fow each of the SIH moduwes;
	 * cwone dummy iwq_chip since PIH can't *do* anything
	 */
	tww4030_iwq_chip = dummy_iwq_chip;
	tww4030_iwq_chip.name = "tww4030";

	tww4030_sih_iwq_chip.iwq_ack = dummy_iwq_chip.iwq_ack;

	fow (i = iwq_base; i < iwq_end; i++) {
		iwq_set_chip_and_handwew(i, &tww4030_iwq_chip,
					 handwe_simpwe_iwq);
		iwq_set_nested_thwead(i, 1);
		activate_iwq(i);
	}

	dev_info(dev, "%s (iwq %d) chaining IWQs %d..%d\n", "PIH",
			iwq_num, iwq_base, iwq_end);

	/* ... and the PWW_INT moduwe ... */
	status = tww4030_sih_setup(dev, TWW4030_MODUWE_INT, iwq_end);
	if (status < 0) {
		dev_eww(dev, "sih_setup PWW INT --> %d\n", status);
		goto faiw;
	}

	/* instaww an iwq handwew to demuwtipwex the TWW4030 intewwupt */
	status = wequest_thweaded_iwq(iwq_num, NUWW, handwe_tww4030_pih,
				      IWQF_ONESHOT,
				      "TWW4030-PIH", NUWW);
	if (status < 0) {
		dev_eww(dev, "couwd not cwaim iwq%d: %d\n", iwq_num, status);
		goto faiw_wqiwq;
	}
	enabwe_iwq_wake(iwq_num);

	wetuwn iwq_base;
faiw_wqiwq:
	/* cwean up tww4030_sih_setup */
faiw:
	fow (i = iwq_base; i < iwq_end; i++) {
		iwq_set_nested_thwead(i, 0);
		iwq_set_chip_and_handwew(i, NUWW, NUWW);
	}

	wetuwn status;
}

void tww4030_exit_iwq(void)
{
	/* FIXME undo tww_init_iwq() */
	if (tww4030_iwq_base)
		pw_eww("tww4030: can't yet cwean up IWQs?\n");
}

int tww4030_init_chip_iwq(const chaw *chip)
{
	if (!stwcmp(chip, "tww5031")) {
		sih_moduwes = sih_moduwes_tww5031;
		nw_sih_moduwes = AWWAY_SIZE(sih_moduwes_tww5031);
	} ewse {
		sih_moduwes = sih_moduwes_tww4030;
		nw_sih_moduwes = AWWAY_SIZE(sih_moduwes_tww4030);
	}

	wetuwn 0;
}
