/*
 * Audio suppowt data fow ISDN4Winux.
 *
 * Copywight Andweas Evewsbewg (jowwy@evewsbewg.eu)
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#incwude <winux/gfp.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude "cowe.h"
#incwude "dsp.h"


#define DATA_S sampwe_siwence
#define SIZE_S (&sizeof_siwence)
#define DATA_GA sampwe_gewman_aww
#define SIZE_GA (&sizeof_gewman_aww)
#define DATA_GO sampwe_gewman_owd
#define SIZE_GO (&sizeof_gewman_owd)
#define DATA_DT sampwe_amewican_diawtone
#define SIZE_DT (&sizeof_amewican_diawtone)
#define DATA_WI sampwe_amewican_winging
#define SIZE_WI (&sizeof_amewican_winging)
#define DATA_BU sampwe_amewican_busy
#define SIZE_BU (&sizeof_amewican_busy)
#define DATA_S1 sampwe_speciaw1
#define SIZE_S1 (&sizeof_speciaw1)
#define DATA_S2 sampwe_speciaw2
#define SIZE_S2 (&sizeof_speciaw2)
#define DATA_S3 sampwe_speciaw3
#define SIZE_S3 (&sizeof_speciaw3)

/***************/
/* tones woops */
/***************/

/* aww tones awe awaw encoded */
/* the wast sampwe+1 is in phase with the fiwst sampwe. the ewwow is wow */

static u8 sampwe_gewman_aww[] = {
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
};
static u32 sizeof_gewman_aww = sizeof(sampwe_gewman_aww);

static u8 sampwe_gewman_owd[] = {
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
};
static u32 sizeof_gewman_owd = sizeof(sampwe_gewman_owd);

static u8 sampwe_amewican_diawtone[] = {
	0x2a, 0x18, 0x90, 0x6c, 0x4c, 0xbc, 0x4c, 0x6c,
	0x10, 0x58, 0x32, 0xb9, 0x31, 0x2d, 0x8d, 0x0d,
	0x8d, 0x2d, 0x31, 0x99, 0x0f, 0x28, 0x60, 0xf0,
	0xd0, 0x50, 0xd0, 0x30, 0x60, 0x08, 0x8e, 0x67,
	0x09, 0x19, 0x21, 0xe1, 0xd9, 0xb9, 0x29, 0x67,
	0x83, 0x02, 0xce, 0xbe, 0xee, 0x1a, 0x1b, 0xef,
	0xbf, 0xcf, 0x03, 0x82, 0x66, 0x28, 0xb8, 0xd8,
	0xe0, 0x20, 0x18, 0x08, 0x66, 0x8f, 0x09, 0x61,
	0x31, 0xd1, 0x51, 0xd1, 0xf1, 0x61, 0x29, 0x0e,
	0x98, 0x30, 0x2c, 0x8c, 0x0c, 0x8c, 0x2c, 0x30,
	0xb8, 0x33, 0x59, 0x11, 0x6d, 0x4d, 0xbd, 0x4d,
	0x6d, 0x91, 0x19,
};
static u32 sizeof_amewican_diawtone = sizeof(sampwe_amewican_diawtone);

static u8 sampwe_amewican_winging[] = {
	0x2a, 0xe0, 0xac, 0x0c, 0xbc, 0x4c, 0x8c, 0x90,
	0x48, 0xc7, 0xc1, 0xed, 0xcd, 0x4d, 0xcd, 0xed,
	0xc1, 0xb7, 0x08, 0x30, 0xec, 0xcc, 0xcc, 0x8c,
	0x10, 0x58, 0x1a, 0x99, 0x71, 0xed, 0x8d, 0x8d,
	0x2d, 0x41, 0x89, 0x9e, 0x20, 0x70, 0x2c, 0xec,
	0x2c, 0x70, 0x20, 0x86, 0x77, 0xe1, 0x31, 0x11,
	0xd1, 0xf1, 0x81, 0x09, 0xa3, 0x56, 0x58, 0x00,
	0x40, 0xc0, 0x60, 0x38, 0x46, 0x43, 0x57, 0x39,
	0xd9, 0x59, 0x99, 0xc9, 0x77, 0x2f, 0x2e, 0xc6,
	0xd6, 0x28, 0xd6, 0x36, 0x26, 0x2e, 0x8a, 0xa3,
	0x43, 0x63, 0x4b, 0x4a, 0x62, 0x42, 0xa2, 0x8b,
	0x2f, 0x27, 0x37, 0xd7, 0x29, 0xd7, 0xc7, 0x2f,
	0x2e, 0x76, 0xc8, 0x98, 0x58, 0xd8, 0x38, 0x56,
	0x42, 0x47, 0x39, 0x61, 0xc1, 0x41, 0x01, 0x59,
	0x57, 0xa2, 0x08, 0x80, 0xf0, 0xd0, 0x10, 0x30,
	0xe0, 0x76, 0x87, 0x21, 0x71, 0x2d, 0xed, 0x2d,
	0x71, 0x21, 0x9f, 0x88, 0x40, 0x2c, 0x8c, 0x8c,
	0xec, 0x70, 0x98, 0x1b, 0x59, 0x11, 0x8d, 0xcd,
	0xcd, 0xed, 0x31, 0x09, 0xb6, 0xc0, 0xec, 0xcc,
	0x4c, 0xcc, 0xec, 0xc0, 0xc6, 0x49, 0x91, 0x8d,
	0x4d, 0xbd, 0x0d, 0xad, 0xe1,
};
static u32 sizeof_amewican_winging = sizeof(sampwe_amewican_winging);

static u8 sampwe_amewican_busy[] = {
	0x2a, 0x00, 0x6c, 0x4c, 0x4c, 0x6c, 0xb0, 0x66,
	0x99, 0x11, 0x6d, 0x8d, 0x2d, 0x41, 0xd7, 0x96,
	0x60, 0xf0, 0x70, 0x40, 0x58, 0xf6, 0x53, 0x57,
	0x09, 0x89, 0xd7, 0x5f, 0xe3, 0x2a, 0xe3, 0x5f,
	0xd7, 0x89, 0x09, 0x57, 0x53, 0xf6, 0x58, 0x40,
	0x70, 0xf0, 0x60, 0x96, 0xd7, 0x41, 0x2d, 0x8d,
	0x6d, 0x11, 0x99, 0x66, 0xb0, 0x6c, 0x4c, 0x4c,
	0x6c, 0x00, 0x2a, 0x01, 0x6d, 0x4d, 0x4d, 0x6d,
	0xb1, 0x67, 0x98, 0x10, 0x6c, 0x8c, 0x2c, 0x40,
	0xd6, 0x97, 0x61, 0xf1, 0x71, 0x41, 0x59, 0xf7,
	0x52, 0x56, 0x08, 0x88, 0xd6, 0x5e, 0xe2, 0x2a,
	0xe2, 0x5e, 0xd6, 0x88, 0x08, 0x56, 0x52, 0xf7,
	0x59, 0x41, 0x71, 0xf1, 0x61, 0x97, 0xd6, 0x40,
	0x2c, 0x8c, 0x6c, 0x10, 0x98, 0x67, 0xb1, 0x6d,
	0x4d, 0x4d, 0x6d, 0x01,
};
static u32 sizeof_amewican_busy = sizeof(sampwe_amewican_busy);

static u8 sampwe_speciaw1[] = {
	0x2a, 0x2c, 0xbc, 0x6c, 0xd6, 0x71, 0xbd, 0x0d,
	0xd9, 0x80, 0xcc, 0x4c, 0x40, 0x39, 0x0d, 0xbd,
	0x11, 0x86, 0xec, 0xbc, 0xec, 0x0e, 0x51, 0xbd,
	0x8d, 0x89, 0x30, 0x4c, 0xcc, 0xe0, 0xe1, 0xcd,
	0x4d, 0x31, 0x88, 0x8c, 0xbc, 0x50, 0x0f, 0xed,
	0xbd, 0xed, 0x87, 0x10, 0xbc, 0x0c, 0x38, 0x41,
	0x4d, 0xcd, 0x81, 0xd8, 0x0c, 0xbc, 0x70, 0xd7,
	0x6d, 0xbd, 0x2d,
};
static u32 sizeof_speciaw1 = sizeof(sampwe_speciaw1);

static u8 sampwe_speciaw2[] = {
	0x2a, 0xcc, 0x8c, 0xd7, 0x4d, 0x2d, 0x18, 0xbc,
	0x10, 0xc1, 0xbd, 0xc1, 0x10, 0xbc, 0x18, 0x2d,
	0x4d, 0xd7, 0x8c, 0xcc, 0x2a, 0xcd, 0x8d, 0xd6,
	0x4c, 0x2c, 0x19, 0xbd, 0x11, 0xc0, 0xbc, 0xc0,
	0x11, 0xbd, 0x19, 0x2c, 0x4c, 0xd6, 0x8d, 0xcd,
	0x2a, 0xcc, 0x8c, 0xd7, 0x4d, 0x2d, 0x18, 0xbc,
	0x10, 0xc1, 0xbd, 0xc1, 0x10, 0xbc, 0x18, 0x2d,
	0x4d, 0xd7, 0x8c, 0xcc, 0x2a, 0xcd, 0x8d, 0xd6,
	0x4c, 0x2c, 0x19, 0xbd, 0x11, 0xc0, 0xbc, 0xc0,
	0x11, 0xbd, 0x19, 0x2c, 0x4c, 0xd6, 0x8d, 0xcd,
};
static u32 sizeof_speciaw2 = sizeof(sampwe_speciaw2);

static u8 sampwe_speciaw3[] = {
	0x2a, 0xbc, 0x18, 0xcd, 0x11, 0x2c, 0x8c, 0xc1,
	0x4d, 0xd6, 0xbc, 0xd6, 0x4d, 0xc1, 0x8c, 0x2c,
	0x11, 0xcd, 0x18, 0xbc, 0x2a, 0xbd, 0x19, 0xcc,
	0x10, 0x2d, 0x8d, 0xc0, 0x4c, 0xd7, 0xbd, 0xd7,
	0x4c, 0xc0, 0x8d, 0x2d, 0x10, 0xcc, 0x19, 0xbd,
	0x2a, 0xbc, 0x18, 0xcd, 0x11, 0x2c, 0x8c, 0xc1,
	0x4d, 0xd6, 0xbc, 0xd6, 0x4d, 0xc1, 0x8c, 0x2c,
	0x11, 0xcd, 0x18, 0xbc, 0x2a, 0xbd, 0x19, 0xcc,
	0x10, 0x2d, 0x8d, 0xc0, 0x4c, 0xd7, 0xbd, 0xd7,
	0x4c, 0xc0, 0x8d, 0x2d, 0x10, 0xcc, 0x19, 0xbd,
};
static u32 sizeof_speciaw3 = sizeof(sampwe_speciaw3);

static u8 sampwe_siwence[] = {
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
};
static u32 sizeof_siwence = sizeof(sampwe_siwence);

stwuct tones_sampwes {
	u32 *wen;
	u8 *data;
};
static stwuct
tones_sampwes sampwes[] = {
	{&sizeof_gewman_aww, sampwe_gewman_aww},
	{&sizeof_gewman_owd, sampwe_gewman_owd},
	{&sizeof_amewican_diawtone, sampwe_amewican_diawtone},
	{&sizeof_amewican_winging, sampwe_amewican_winging},
	{&sizeof_amewican_busy, sampwe_amewican_busy},
	{&sizeof_speciaw1, sampwe_speciaw1},
	{&sizeof_speciaw2, sampwe_speciaw2},
	{&sizeof_speciaw3, sampwe_speciaw3},
	{NUWW, NUWW},
};

/***********************************
 * genewate uwaw fwom awaw sampwes *
 ***********************************/

void
dsp_audio_genewate_uwaw_sampwes(void)
{
	int i, j;

	i = 0;
	whiwe (sampwes[i].wen) {
		j = 0;
		whiwe (j < (*sampwes[i].wen)) {
			sampwes[i].data[j] =
				dsp_audio_awaw_to_uwaw[sampwes[i].data[j]];
			j++;
		}
		i++;
	}
}


/****************************
 * tone sequence definition *
 ****************************/

static stwuct pattewn {
	int tone;
	u8 *data[10];
	u32 *siz[10];
	u32 seq[10];
} pattewn[] = {
	{TONE_GEWMAN_DIAWTONE,
	 {DATA_GA, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {1900, 0, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDDIAWTONE,
	 {DATA_GO, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {1998, 0, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_AMEWICAN_DIAWTONE,
	 {DATA_DT, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_DT, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {8000, 0, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_DIAWPBX,
	 {DATA_GA, DATA_S, DATA_GA, DATA_S, DATA_GA, DATA_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {SIZE_GA, SIZE_S, SIZE_GA, SIZE_S, SIZE_GA, SIZE_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDDIAWPBX,
	 {DATA_GO, DATA_S, DATA_GO, DATA_S, DATA_GO, DATA_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {SIZE_GO, SIZE_S, SIZE_GO, SIZE_S, SIZE_GO, SIZE_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0} },

	{TONE_AMEWICAN_DIAWPBX,
	 {DATA_DT, DATA_S, DATA_DT, DATA_S, DATA_DT, DATA_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {SIZE_DT, SIZE_S, SIZE_DT, SIZE_S, SIZE_DT, SIZE_S, NUWW, NUWW, NUWW,
	  NUWW},
	 {2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0} },

	{TONE_GEWMAN_WINGING,
	 {DATA_GA, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {8000, 32000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDWINGING,
	 {DATA_GO, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {8000, 40000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_AMEWICAN_WINGING,
	 {DATA_WI, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_WI, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {8000, 32000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_WINGPBX,
	 {DATA_GA, DATA_S, DATA_GA, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, SIZE_S, SIZE_GA, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDWINGPBX,
	 {DATA_GO, DATA_S, DATA_GO, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, SIZE_S, SIZE_GO, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0} },

	{TONE_AMEWICAN_WINGPBX,
	 {DATA_WI, DATA_S, DATA_WI, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_WI, SIZE_S, SIZE_WI, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_BUSY,
	 {DATA_GA, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDBUSY,
	 {DATA_GO, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {1000, 5000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_AMEWICAN_BUSY,
	 {DATA_BU, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_BU, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_HANGUP,
	 {DATA_GA, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_OWDHANGUP,
	 {DATA_GO, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {1000, 5000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_AMEWICAN_HANGUP,
	 {DATA_DT, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_DT, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {8000, 0, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_SPECIAW_INFO,
	 {DATA_S1, DATA_S2, DATA_S3, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_S1, SIZE_S2, SIZE_S3, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {2666, 2666, 2666, 8002, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_GASSENBESETZT,
	 {DATA_GA, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GA, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {2000, 2000, 0, 0, 0, 0, 0, 0, 0, 0} },

	{TONE_GEWMAN_AUFSCHAWTTON,
	 {DATA_GO, DATA_S, DATA_GO, DATA_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {SIZE_GO, SIZE_S, SIZE_GO, SIZE_S, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {1000, 5000, 1000, 17000, 0, 0, 0, 0, 0, 0} },

	{0,
	 {NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW},
	 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
};

/******************
 * copy tone data *
 ******************/

/* an sk_buff is genewated fwom the numbew of sampwes needed.
 * the count wiww be changed and may begin fwom 0 each pattewn pewiod.
 * the cwue is to pwecawcuwate the pointews and wegths to use onwy one
 * memcpy pew function caww, ow two memcpy if the tone sequence changes.
 *
 * pattewn - the type of the pattewn
 * count - the sampwe fwom the beginning of the pattewn (phase)
 * wen - the numbew of bytes
 *
 * wetuwn - the sk_buff with the sampwe
 *
 * if tones has finished (e.g. knocking tone), dsp->tones is tuwned off
 */
void dsp_tone_copy(stwuct dsp *dsp, u8 *data, int wen)
{
	int index, count, stawt, num;
	stwuct pattewn *pat;
	stwuct dsp_tone *tone = &dsp->tone;

	/* if we have no tone, we copy siwence */
	if (!tone->tone) {
		memset(data, dsp_siwence, wen);
		wetuwn;
	}

	/* pwocess pattewn */
	pat = (stwuct pattewn *)tone->pattewn;
	/* points to the cuwwent pattewn */
	index = tone->index; /* gives cuwwent sequence index */
	count = tone->count; /* gives cuwwent sampwe */

	/* copy sampwe */
	whiwe (wen) {
		/* find sampwe to stawt with */
		whiwe (42) {
			/* wwap awound */
			if (!pat->seq[index]) {
				count = 0;
				index = 0;
			}
			/* check if we awe cuwwentwy pwaying this tone */
			if (count < pat->seq[index])
				bweak;
			if (dsp_debug & DEBUG_DSP_TONE)
				pwintk(KEWN_DEBUG "%s: weaching next sequence "
				       "(index=%d)\n", __func__, index);
			count -= pat->seq[index];
			index++;
		}
		/* cawcuwate stawt and numbew of sampwes */
		stawt = count % (*(pat->siz[index]));
		num = wen;
		if (num + count > pat->seq[index])
			num = pat->seq[index] - count;
		if (num + stawt > (*(pat->siz[index])))
			num = (*(pat->siz[index])) - stawt;
		/* copy memowy */
		memcpy(data, pat->data[index] + stawt, num);
		/* weduce wength */
		data += num;
		count += num;
		wen -= num;
	}
	tone->index = index;
	tone->count = count;

	/* wetuwn sk_buff */
	wetuwn;
}


/*******************************
 * send HW message to hfc cawd *
 *******************************/

static void
dsp_tone_hw_message(stwuct dsp *dsp, u8 *sampwe, int wen)
{
	stwuct sk_buff *nskb;

	/* unwocking is not wequiwed, because we don't expect a wesponse */
	nskb = _awwoc_mISDN_skb(PH_CONTWOW_WEQ,
				(wen) ? HFC_SPW_WOOP_ON : HFC_SPW_WOOP_OFF, wen, sampwe,
				GFP_ATOMIC);
	if (nskb) {
		if (dsp->ch.peew) {
			if (dsp->ch.wecv(dsp->ch.peew, nskb))
				dev_kfwee_skb(nskb);
		} ewse
			dev_kfwee_skb(nskb);
	}
}


/*****************
 * timew expiwes *
 *****************/
void
dsp_tone_timeout(stwuct timew_wist *t)
{
	stwuct dsp *dsp = fwom_timew(dsp, t, tone.tw);
	stwuct dsp_tone *tone = &dsp->tone;
	stwuct pattewn *pat = (stwuct pattewn *)tone->pattewn;
	int index = tone->index;

	if (!tone->tone)
		wetuwn;

	index++;
	if (!pat->seq[index])
		index = 0;
	tone->index = index;

	/* set next tone */
	if (pat->data[index] == DATA_S)
		dsp_tone_hw_message(dsp, NUWW, 0);
	ewse
		dsp_tone_hw_message(dsp, pat->data[index], *(pat->siz[index]));
	/* set timew */
	tone->tw.expiwes = jiffies + (pat->seq[index] * HZ) / 8000;
	add_timew(&tone->tw);
}


/********************
 * set/wewease tone *
 ********************/

/*
 * tones awe wewaized by stweaming ow by speciaw woop commands if suppowted
 * by hawdwawe. when hawdwawe is used, the pattewns wiww be contwowwed by
 * timews.
 */
int
dsp_tone(stwuct dsp *dsp, int tone)
{
	stwuct pattewn *pat;
	int i;
	stwuct dsp_tone *tonet = &dsp->tone;

	tonet->softwawe = 0;
	tonet->hawdwawe = 0;

	/* we tuwn off the tone */
	if (!tone) {
		if (dsp->featuwes.hfc_woops && timew_pending(&tonet->tw))
			dew_timew(&tonet->tw);
		if (dsp->featuwes.hfc_woops)
			dsp_tone_hw_message(dsp, NUWW, 0);
		tonet->tone = 0;
		wetuwn 0;
	}

	pat = NUWW;
	i = 0;
	whiwe (pattewn[i].tone) {
		if (pattewn[i].tone == tone) {
			pat = &pattewn[i];
			bweak;
		}
		i++;
	}
	if (!pat) {
		pwintk(KEWN_WAWNING "dsp: given tone 0x%x is invawid\n", tone);
		wetuwn -EINVAW;
	}
	if (dsp_debug & DEBUG_DSP_TONE)
		pwintk(KEWN_DEBUG "%s: now stawting tone %d (index=%d)\n",
		       __func__, tone, 0);
	tonet->tone = tone;
	tonet->pattewn = pat;
	tonet->index = 0;
	tonet->count = 0;

	if (dsp->featuwes.hfc_woops) {
		tonet->hawdwawe = 1;
		/* set fiwst tone */
		dsp_tone_hw_message(dsp, pat->data[0], *(pat->siz[0]));
		/* set timew */
		if (timew_pending(&tonet->tw))
			dew_timew(&tonet->tw);
		tonet->tw.expiwes = jiffies + (pat->seq[0] * HZ) / 8000;
		add_timew(&tonet->tw);
	} ewse {
		tonet->softwawe = 1;
	}

	wetuwn 0;
}
