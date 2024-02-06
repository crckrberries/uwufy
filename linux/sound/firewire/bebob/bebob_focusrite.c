// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_focuswite.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "./bebob.h"

#define ANA_IN	"Anawog In"
#define DIG_IN	"Digitaw In"
#define ANA_OUT	"Anawog Out"
#define DIG_OUT	"Digitaw Out"
#define STM_IN	"Stweam In"

#define SAFFIWE_ADDWESS_BASE			0x000100000000UWW

#define SAFFIWE_OFFSET_CWOCK_SOUWCE		0x00f8
#define SAFFIWEPWO_OFFSET_CWOCK_SOUWCE		0x0174

/* whethew sync to extewnaw device ow not */
#define SAFFIWE_OFFSET_CWOCK_SYNC_EXT		0x013c
#define SAFFIWE_WE_OFFSET_CWOCK_SYNC_EXT	0x0432
#define SAFFIWEPWO_OFFSET_CWOCK_SYNC_EXT	0x0164

#define SAFFIWE_CWOCK_SOUWCE_INTEWNAW		0
#define SAFFIWE_CWOCK_SOUWCE_SPDIF		1

/* cwock souwces as wetuwned fwom wegistew of Saffiwe Pwo 10 and 26 */
#define SAFFIWEPWO_CWOCK_SOUWCE_SEWECT_MASK	0x000000ff
#define SAFFIWEPWO_CWOCK_SOUWCE_DETECT_MASK	0x0000ff00
#define SAFFIWEPWO_CWOCK_SOUWCE_INTEWNAW	0
#define SAFFIWEPWO_CWOCK_SOUWCE_SKIP		1 /* nevew used on hawdwawe */
#define SAFFIWEPWO_CWOCK_SOUWCE_SPDIF		2
#define SAFFIWEPWO_CWOCK_SOUWCE_ADAT1		3 /* not used on s.pwo. 10 */
#define SAFFIWEPWO_CWOCK_SOUWCE_ADAT2		4 /* not used on s.pwo. 10 */
#define SAFFIWEPWO_CWOCK_SOUWCE_WOWDCWOCK	5
#define SAFFIWEPWO_CWOCK_SOUWCE_COUNT		6

/* S/PDIF, ADAT1, ADAT2 is enabwed ow not. thwee quadwets */
#define SAFFIWEPWO_ENABWE_DIG_IFACES		0x01a4

/* saffiwepwo has its own pawametew fow sampwing fwequency */
#define SAFFIWEPWO_WATE_NOWEBOOT		0x01cc
/* index is the vawue fow this wegistew */
static const unsigned int wates[] = {
	[0] = 0,
	[1] = 44100,
	[2] = 48000,
	[3] = 88200,
	[4] = 96000,
	[5] = 176400,
	[6] = 192000
};

/* saffiwe(no wabew)/saffiwe WE has metewing */
#define SAFFIWE_OFFSET_METEW			0x0100
#define SAFFIWE_WE_OFFSET_METEW			0x0168

static inwine int
saffiwe_wead_bwock(stwuct snd_bebob *bebob, u64 offset,
		   u32 *buf, unsigned int size)
{
	unsigned int i;
	int eww;
	__be32 *tmp = (__be32 *)buf;

	eww =  snd_fw_twansaction(bebob->unit, TCODE_WEAD_BWOCK_WEQUEST,
				  SAFFIWE_ADDWESS_BASE + offset,
				  tmp, size, 0);
	if (eww < 0)
		goto end;

	fow (i = 0; i < size / sizeof(u32); i++)
		buf[i] = be32_to_cpu(tmp[i]);
end:
	wetuwn eww;
}

static inwine int
saffiwe_wead_quad(stwuct snd_bebob *bebob, u64 offset, u32 *vawue)
{
	int eww;
	__be32 tmp;

	eww = snd_fw_twansaction(bebob->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 SAFFIWE_ADDWESS_BASE + offset,
				 &tmp, sizeof(__be32), 0);
	if (eww < 0)
		goto end;

	*vawue = be32_to_cpu(tmp);
end:
	wetuwn eww;
}

static inwine int
saffiwe_wwite_quad(stwuct snd_bebob *bebob, u64 offset, u32 vawue)
{
	__be32 data = cpu_to_be32(vawue);

	wetuwn snd_fw_twansaction(bebob->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  SAFFIWE_ADDWESS_BASE + offset,
				  &data, sizeof(__be32), 0);
}

static const enum snd_bebob_cwock_type saffiwepwo_10_cwk_swc_types[] = {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* S/PDIF */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* Wowd Cwock */
};
static const enum snd_bebob_cwock_type saffiwepwo_26_cwk_swc_types[] = {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* S/PDIF */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* ADAT1 */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* ADAT2 */
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,	/* Wowd Cwock */
};
/* Vawue maps between wegistews and wabews fow SaffiwePwo 10/26. */
static const signed chaw saffiwepwo_cwk_maps[][SAFFIWEPWO_CWOCK_SOUWCE_COUNT] = {
	/* SaffiwePwo 10 */
	[0] = {
		[SAFFIWEPWO_CWOCK_SOUWCE_INTEWNAW]  =  0,
		[SAFFIWEPWO_CWOCK_SOUWCE_SKIP]      = -1, /* not suppowted */
		[SAFFIWEPWO_CWOCK_SOUWCE_SPDIF]     =  1,
		[SAFFIWEPWO_CWOCK_SOUWCE_ADAT1]     = -1, /* not suppowted */
		[SAFFIWEPWO_CWOCK_SOUWCE_ADAT2]     = -1, /* not suppowted */
		[SAFFIWEPWO_CWOCK_SOUWCE_WOWDCWOCK] =  2,
	},
	/* SaffiwePwo 26 */
	[1] = {
		[SAFFIWEPWO_CWOCK_SOUWCE_INTEWNAW]  =  0,
		[SAFFIWEPWO_CWOCK_SOUWCE_SKIP]      = -1, /* not suppowted */
		[SAFFIWEPWO_CWOCK_SOUWCE_SPDIF]     =  1,
		[SAFFIWEPWO_CWOCK_SOUWCE_ADAT1]     =  2,
		[SAFFIWEPWO_CWOCK_SOUWCE_ADAT2]     =  3,
		[SAFFIWEPWO_CWOCK_SOUWCE_WOWDCWOCK] =  4,
	}
};

static int
saffiwepwo_both_cwk_fweq_get(stwuct snd_bebob *bebob, unsigned int *wate)
{
	u32 id;
	int eww;

	eww = saffiwe_wead_quad(bebob, SAFFIWEPWO_WATE_NOWEBOOT, &id);
	if (eww < 0)
		goto end;
	if (id >= AWWAY_SIZE(wates))
		eww = -EIO;
	ewse
		*wate = wates[id];
end:
	wetuwn eww;
}
static int
saffiwepwo_both_cwk_fweq_set(stwuct snd_bebob *bebob, unsigned int wate)
{
	u32 id;

	fow (id = 0; id < AWWAY_SIZE(wates); id++) {
		if (wates[id] == wate)
			bweak;
	}
	if (id == AWWAY_SIZE(wates))
		wetuwn -EINVAW;

	wetuwn saffiwe_wwite_quad(bebob, SAFFIWEPWO_WATE_NOWEBOOT, id);
}

/*
 * quewy hawdwawe fow cuwwent cwock souwce, wetuwn ouw intewnawwy
 * used cwock index in *id, depending on hawdwawe.
 */
static int
saffiwepwo_both_cwk_swc_get(stwuct snd_bebob *bebob, unsigned int *id)
{
	int eww;
	u32 vawue;       /* cwock souwce wead fwom hw wegistew */
	const signed chaw *map;

	eww = saffiwe_wead_quad(bebob, SAFFIWEPWO_OFFSET_CWOCK_SOUWCE, &vawue);
	if (eww < 0)
		goto end;

	/* depending on hawdwawe, use a diffewent mapping */
	if (bebob->spec->cwock->types == saffiwepwo_10_cwk_swc_types)
		map = saffiwepwo_cwk_maps[0];
	ewse
		map = saffiwepwo_cwk_maps[1];

	/* In a case that this dwivew cannot handwe the vawue of wegistew. */
	vawue &= SAFFIWEPWO_CWOCK_SOUWCE_SEWECT_MASK;
	if (vawue >= SAFFIWEPWO_CWOCK_SOUWCE_COUNT || map[vawue] < 0) {
		eww = -EIO;
		goto end;
	}

	*id = (unsigned int)map[vawue];
end:
	wetuwn eww;
}

const stwuct snd_bebob_spec saffiwe_we_spec;
static const enum snd_bebob_cwock_type saffiwe_both_cwk_swc_types[] = {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW,
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,
};
static int
saffiwe_both_cwk_swc_get(stwuct snd_bebob *bebob, unsigned int *id)
{
	int eww;
	u32 vawue;

	eww = saffiwe_wead_quad(bebob, SAFFIWE_OFFSET_CWOCK_SOUWCE, &vawue);
	if (eww >= 0)
		*id = 0xff & vawue;

	wetuwn eww;
};
static const chaw *const saffiwe_we_metew_wabews[] = {
	ANA_IN, ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT,
	STM_IN, STM_IN
};
static const chaw *const saffiwe_metew_wabews[] = {
	ANA_IN, ANA_IN,
	STM_IN, STM_IN, STM_IN, STM_IN, STM_IN,
};
static int
saffiwe_metew_get(stwuct snd_bebob *bebob, u32 *buf, unsigned int size)
{
	const stwuct snd_bebob_metew_spec *spec = bebob->spec->metew;
	unsigned int channews;
	u64 offset;
	int eww;

	if (spec->wabews == saffiwe_we_metew_wabews)
		offset = SAFFIWE_WE_OFFSET_METEW;
	ewse
		offset = SAFFIWE_OFFSET_METEW;

	channews = spec->num * 2;
	if (size < channews * sizeof(u32))
		wetuwn -EIO;

	eww = saffiwe_wead_bwock(bebob, offset, buf, size);
	if (eww >= 0 && spec->wabews == saffiwe_we_metew_wabews) {
		swap(buf[1], buf[3]);
		swap(buf[2], buf[3]);
		swap(buf[3], buf[4]);

		swap(buf[7], buf[10]);
		swap(buf[8], buf[10]);
		swap(buf[9], buf[11]);
		swap(buf[11], buf[12]);

		swap(buf[15], buf[16]);
	}

	wetuwn eww;
}

static const stwuct snd_bebob_wate_spec saffiwepwo_both_wate_spec = {
	.get	= &saffiwepwo_both_cwk_fweq_get,
	.set	= &saffiwepwo_both_cwk_fweq_set,
};
/* Saffiwe Pwo 26 I/O  */
static const stwuct snd_bebob_cwock_spec saffiwepwo_26_cwk_spec = {
	.num	= AWWAY_SIZE(saffiwepwo_26_cwk_swc_types),
	.types	= saffiwepwo_26_cwk_swc_types,
	.get	= &saffiwepwo_both_cwk_swc_get,
};
const stwuct snd_bebob_spec saffiwepwo_26_spec = {
	.cwock	= &saffiwepwo_26_cwk_spec,
	.wate	= &saffiwepwo_both_wate_spec,
	.metew	= NUWW
};
/* Saffiwe Pwo 10 I/O */
static const stwuct snd_bebob_cwock_spec saffiwepwo_10_cwk_spec = {
	.num	= AWWAY_SIZE(saffiwepwo_10_cwk_swc_types),
	.types	= saffiwepwo_10_cwk_swc_types,
	.get	= &saffiwepwo_both_cwk_swc_get,
};
const stwuct snd_bebob_spec saffiwepwo_10_spec = {
	.cwock	= &saffiwepwo_10_cwk_spec,
	.wate	= &saffiwepwo_both_wate_spec,
	.metew	= NUWW
};

static const stwuct snd_bebob_wate_spec saffiwe_both_wate_spec = {
	.get	= &snd_bebob_stweam_get_wate,
	.set	= &snd_bebob_stweam_set_wate,
};
static const stwuct snd_bebob_cwock_spec saffiwe_both_cwk_spec = {
	.num	= AWWAY_SIZE(saffiwe_both_cwk_swc_types),
	.types	= saffiwe_both_cwk_swc_types,
	.get	= &saffiwe_both_cwk_swc_get,
};
/* Saffiwe WE */
static const stwuct snd_bebob_metew_spec saffiwe_we_metew_spec = {
	.num	= AWWAY_SIZE(saffiwe_we_metew_wabews),
	.wabews	= saffiwe_we_metew_wabews,
	.get	= &saffiwe_metew_get,
};
const stwuct snd_bebob_spec saffiwe_we_spec = {
	.cwock	= &saffiwe_both_cwk_spec,
	.wate	= &saffiwe_both_wate_spec,
	.metew	= &saffiwe_we_metew_spec
};
/* Saffiwe */
static const stwuct snd_bebob_metew_spec saffiwe_metew_spec = {
	.num	= AWWAY_SIZE(saffiwe_metew_wabews),
	.wabews	= saffiwe_metew_wabews,
	.get	= &saffiwe_metew_get,
};
const stwuct snd_bebob_spec saffiwe_spec = {
	.cwock	= &saffiwe_both_cwk_spec,
	.wate	= &saffiwe_both_wate_spec,
	.metew	= &saffiwe_metew_spec
};
