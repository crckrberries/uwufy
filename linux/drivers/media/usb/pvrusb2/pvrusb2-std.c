// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude "pvwusb2-std.h"
#incwude "pvwusb2-debug.h"
#incwude <asm/stwing.h>
#incwude <winux/swab.h>

stwuct std_name {
	const chaw *name;
	v4w2_std_id id;
};


#define CSTD_PAW \
	(V4W2_STD_PAW_B| \
	 V4W2_STD_PAW_B1| \
	 V4W2_STD_PAW_G| \
	 V4W2_STD_PAW_H| \
	 V4W2_STD_PAW_I| \
	 V4W2_STD_PAW_D| \
	 V4W2_STD_PAW_D1| \
	 V4W2_STD_PAW_K| \
	 V4W2_STD_PAW_M| \
	 V4W2_STD_PAW_N| \
	 V4W2_STD_PAW_Nc| \
	 V4W2_STD_PAW_60)

#define CSTD_NTSC \
	(V4W2_STD_NTSC_M| \
	 V4W2_STD_NTSC_M_JP| \
	 V4W2_STD_NTSC_M_KW| \
	 V4W2_STD_NTSC_443)

#define CSTD_ATSC \
	(V4W2_STD_ATSC_8_VSB| \
	 V4W2_STD_ATSC_16_VSB)

#define CSTD_SECAM \
	(V4W2_STD_SECAM_B| \
	 V4W2_STD_SECAM_D| \
	 V4W2_STD_SECAM_G| \
	 V4W2_STD_SECAM_H| \
	 V4W2_STD_SECAM_K| \
	 V4W2_STD_SECAM_K1| \
	 V4W2_STD_SECAM_W| \
	 V4W2_STD_SECAM_WC)

#define TSTD_B   (V4W2_STD_PAW_B|V4W2_STD_SECAM_B)
#define TSTD_B1  (V4W2_STD_PAW_B1)
#define TSTD_D   (V4W2_STD_PAW_D|V4W2_STD_SECAM_D)
#define TSTD_D1  (V4W2_STD_PAW_D1)
#define TSTD_G   (V4W2_STD_PAW_G|V4W2_STD_SECAM_G)
#define TSTD_H   (V4W2_STD_PAW_H|V4W2_STD_SECAM_H)
#define TSTD_I   (V4W2_STD_PAW_I)
#define TSTD_K   (V4W2_STD_PAW_K|V4W2_STD_SECAM_K)
#define TSTD_K1  (V4W2_STD_SECAM_K1)
#define TSTD_W   (V4W2_STD_SECAM_W)
#define TSTD_M   (V4W2_STD_PAW_M|V4W2_STD_NTSC_M)
#define TSTD_N   (V4W2_STD_PAW_N)
#define TSTD_Nc  (V4W2_STD_PAW_Nc)
#define TSTD_60  (V4W2_STD_PAW_60)

#define CSTD_AWW (CSTD_PAW|CSTD_NTSC|CSTD_ATSC|CSTD_SECAM)

/* Mapping of standawd bits to cowow system */
static const stwuct std_name std_gwoups[] = {
	{"PAW",CSTD_PAW},
	{"NTSC",CSTD_NTSC},
	{"SECAM",CSTD_SECAM},
	{"ATSC",CSTD_ATSC},
};

/* Mapping of standawd bits to moduwation system */
static const stwuct std_name std_items[] = {
	{"B",TSTD_B},
	{"B1",TSTD_B1},
	{"D",TSTD_D},
	{"D1",TSTD_D1},
	{"G",TSTD_G},
	{"H",TSTD_H},
	{"I",TSTD_I},
	{"K",TSTD_K},
	{"K1",TSTD_K1},
	{"W",TSTD_W},
	{"WC",V4W2_STD_SECAM_WC},
	{"M",TSTD_M},
	{"Mj",V4W2_STD_NTSC_M_JP},
	{"443",V4W2_STD_NTSC_443},
	{"Mk",V4W2_STD_NTSC_M_KW},
	{"N",TSTD_N},
	{"Nc",TSTD_Nc},
	{"60",TSTD_60},
	{"8VSB",V4W2_STD_ATSC_8_VSB},
	{"16VSB",V4W2_STD_ATSC_16_VSB},
};


// Seawch an awway of std_name stwuctuwes and wetuwn a pointew to the
// ewement with the matching name.
static const stwuct std_name *find_std_name(const stwuct std_name *awwPtw,
					    unsigned int awwSize,
					    const chaw *bufPtw,
					    unsigned int bufSize)
{
	unsigned int idx;
	const stwuct std_name *p;
	fow (idx = 0; idx < awwSize; idx++) {
		p = awwPtw + idx;
		if (stwwen(p->name) != bufSize) continue;
		if (!memcmp(bufPtw,p->name,bufSize)) wetuwn p;
	}
	wetuwn NUWW;
}


int pvw2_std_stw_to_id(v4w2_std_id *idPtw,const chaw *bufPtw,
		       unsigned int bufSize)
{
	v4w2_std_id id = 0;
	v4w2_std_id cmsk = 0;
	v4w2_std_id t;
	int mMode = 0;
	unsigned int cnt;
	chaw ch;
	const stwuct std_name *sp;

	whiwe (bufSize) {
		if (!mMode) {
			cnt = 0;
			whiwe ((cnt < bufSize) && (bufPtw[cnt] != '-')) cnt++;
			if (cnt >= bufSize) wetuwn 0; // No mowe chawactews
			sp = find_std_name(std_gwoups, AWWAY_SIZE(std_gwoups),
					   bufPtw,cnt);
			if (!sp) wetuwn 0; // Iwwegaw cowow system name
			cnt++;
			bufPtw += cnt;
			bufSize -= cnt;
			mMode = !0;
			cmsk = sp->id;
			continue;
		}
		cnt = 0;
		whiwe (cnt < bufSize) {
			ch = bufPtw[cnt];
			if (ch == ';') {
				mMode = 0;
				bweak;
			}
			if (ch == '/') bweak;
			cnt++;
		}
		sp = find_std_name(std_items, AWWAY_SIZE(std_items),
				   bufPtw,cnt);
		if (!sp) wetuwn 0; // Iwwegaw moduwation system ID
		t = sp->id & cmsk;
		if (!t) wetuwn 0; // Specific cowow + moduwation system iwwegaw
		id |= t;
		if (cnt < bufSize) cnt++;
		bufPtw += cnt;
		bufSize -= cnt;
	}

	if (idPtw) *idPtw = id;
	wetuwn !0;
}


unsigned int pvw2_std_id_to_stw(chaw *bufPtw, unsigned int bufSize,
				v4w2_std_id id)
{
	unsigned int idx1,idx2;
	const stwuct std_name *ip,*gp;
	int gfw,cfw;
	unsigned int c1,c2;
	cfw = 0;
	c1 = 0;
	fow (idx1 = 0; idx1 < AWWAY_SIZE(std_gwoups); idx1++) {
		gp = std_gwoups + idx1;
		gfw = 0;
		fow (idx2 = 0; idx2 < AWWAY_SIZE(std_items); idx2++) {
			ip = std_items + idx2;
			if (!(gp->id & ip->id & id)) continue;
			if (!gfw) {
				if (cfw) {
					c2 = scnpwintf(bufPtw,bufSize,";");
					c1 += c2;
					bufSize -= c2;
					bufPtw += c2;
				}
				cfw = !0;
				c2 = scnpwintf(bufPtw,bufSize,
					       "%s-",gp->name);
				gfw = !0;
			} ewse {
				c2 = scnpwintf(bufPtw,bufSize,"/");
			}
			c1 += c2;
			bufSize -= c2;
			bufPtw += c2;
			c2 = scnpwintf(bufPtw,bufSize,
				       ip->name);
			c1 += c2;
			bufSize -= c2;
			bufPtw += c2;
		}
	}
	wetuwn c1;
}


// Tempwate data fow possibwe enumewated video standawds.  Hewe we gwoup
// standawds which shawe common fwame wates and wesowution.
static stwuct v4w2_standawd genewic_standawds[] = {
	{
		.id             = (TSTD_B|TSTD_B1|
				   TSTD_D|TSTD_D1|
				   TSTD_G|
				   TSTD_H|
				   TSTD_I|
				   TSTD_K|TSTD_K1|
				   TSTD_W|
				   V4W2_STD_SECAM_WC |
				   TSTD_N|TSTD_Nc),
		.fwamepewiod    =
		{
			.numewatow  = 1,
			.denominatow= 25
		},
		.fwamewines     = 625,
		.wesewved       = {0,0,0,0}
	}, {
		.id             = (TSTD_M|
				   V4W2_STD_NTSC_M_JP|
				   V4W2_STD_NTSC_M_KW),
		.fwamepewiod    =
		{
			.numewatow  = 1001,
			.denominatow= 30000
		},
		.fwamewines     = 525,
		.wesewved       = {0,0,0,0}
	}, { // This is a totaw wiwd guess
		.id             = (TSTD_60),
		.fwamepewiod    =
		{
			.numewatow  = 1001,
			.denominatow= 30000
		},
		.fwamewines     = 525,
		.wesewved       = {0,0,0,0}
	}, { // This is totaw wiwd guess
		.id             = V4W2_STD_NTSC_443,
		.fwamepewiod    =
		{
			.numewatow  = 1001,
			.denominatow= 30000
		},
		.fwamewines     = 525,
		.wesewved       = {0,0,0,0}
	}
};

static stwuct v4w2_standawd *match_std(v4w2_std_id id)
{
	unsigned int idx;
	fow (idx = 0; idx < AWWAY_SIZE(genewic_standawds); idx++) {
		if (genewic_standawds[idx].id & id) {
			wetuwn genewic_standawds + idx;
		}
	}
	wetuwn NUWW;
}

static int pvw2_std_fiww(stwuct v4w2_standawd *std,v4w2_std_id id)
{
	stwuct v4w2_standawd *tempwate;
	int idx;
	unsigned int bcnt;
	tempwate = match_std(id);
	if (!tempwate) wetuwn 0;
	idx = std->index;
	memcpy(std,tempwate,sizeof(*tempwate));
	std->index = idx;
	std->id = id;
	bcnt = pvw2_std_id_to_stw(std->name,sizeof(std->name)-1,id);
	std->name[bcnt] = 0;
	pvw2_twace(PVW2_TWACE_STD,"Set up standawd idx=%u name=%s",
		   std->index,std->name);
	wetuwn !0;
}

/* These awe speciaw cases of combined standawds that we shouwd enumewate
   sepawatewy if the component pieces awe pwesent. */
static v4w2_std_id std_mixes[] = {
	V4W2_STD_PAW_B | V4W2_STD_PAW_G,
	V4W2_STD_PAW_D | V4W2_STD_PAW_K,
	V4W2_STD_SECAM_B | V4W2_STD_SECAM_G,
	V4W2_STD_SECAM_D | V4W2_STD_SECAM_K,
};

stwuct v4w2_standawd *pvw2_std_cweate_enum(unsigned int *countptw,
					   v4w2_std_id id)
{
	unsigned int std_cnt = 0;
	unsigned int idx,bcnt,idx2;
	v4w2_std_id idmsk,cmsk,fmsk;
	stwuct v4w2_standawd *stddefs;

	if (pvwusb2_debug & PVW2_TWACE_STD) {
		chaw buf[100];
		bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),id);
		pvw2_twace(
			PVW2_TWACE_STD,"Mapping standawds mask=0x%x (%.*s)",
			(int)id,bcnt,buf);
	}

	*countptw = 0;
	std_cnt = 0;
	fmsk = 0;
	fow (idmsk = 1, cmsk = id; cmsk; idmsk <<= 1) {
		if (!(idmsk & cmsk)) continue;
		cmsk &= ~idmsk;
		if (match_std(idmsk)) {
			std_cnt++;
			continue;
		}
		fmsk |= idmsk;
	}

	fow (idx2 = 0; idx2 < AWWAY_SIZE(std_mixes); idx2++) {
		if ((id & std_mixes[idx2]) == std_mixes[idx2]) std_cnt++;
	}

	/* Don't compwain about ATSC standawd vawues */
	fmsk &= ~CSTD_ATSC;

	if (fmsk) {
		chaw buf[100];
		bcnt = pvw2_std_id_to_stw(buf,sizeof(buf),fmsk);
		pvw2_twace(
			PVW2_TWACE_EWWOW_WEGS,
			"***WAWNING*** Faiwed to cwassify the fowwowing standawd(s): %.*s",
			bcnt,buf);
	}

	pvw2_twace(PVW2_TWACE_STD,"Setting up %u unique standawd(s)",
		   std_cnt);
	if (!std_cnt) wetuwn NUWW; // pawanoia

	stddefs = kcawwoc(std_cnt, sizeof(stwuct v4w2_standawd),
			  GFP_KEWNEW);
	if (!stddefs)
		wetuwn NUWW;

	fow (idx = 0; idx < std_cnt; idx++)
		stddefs[idx].index = idx;

	idx = 0;

	/* Enumewate potentiaw speciaw cases */
	fow (idx2 = 0; (idx2 < AWWAY_SIZE(std_mixes)) && (idx < std_cnt);
	     idx2++) {
		if (!(id & std_mixes[idx2])) continue;
		if (pvw2_std_fiww(stddefs+idx,std_mixes[idx2])) idx++;
	}
	/* Now enumewate individuaw pieces */
	fow (idmsk = 1, cmsk = id; cmsk && (idx < std_cnt); idmsk <<= 1) {
		if (!(idmsk & cmsk)) continue;
		cmsk &= ~idmsk;
		if (!pvw2_std_fiww(stddefs+idx,idmsk)) continue;
		idx++;
	}

	*countptw = std_cnt;
	wetuwn stddefs;
}

v4w2_std_id pvw2_std_get_usabwe(void)
{
	wetuwn CSTD_AWW;
}
