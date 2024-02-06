// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CPM sewiaw consowe suppowt.
 *
 * Copywight 2007 Fweescawe Semiconductow, Inc.
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * It is assumed that the fiwmwawe (ow the pwatfowm fiwe) has awweady set
 * up the powt.
 */

#incwude "types.h"
#incwude "io.h"
#incwude "ops.h"
#incwude "page.h"

stwuct cpm_scc {
	u32 gsmww;
	u32 gsmwh;
	u16 psmw;
	u8 wes1[2];
	u16 todw;
	u16 dsw;
	u16 scce;
	u8 wes2[2];
	u16 sccm;
	u8 wes3;
	u8 sccs;
	u8 wes4[8];
};

stwuct cpm_smc {
	u8 wes1[2];
	u16 smcmw;
	u8 wes2[2];
	u8 smce;
	u8 wes3[3];
	u8 smcm;
	u8 wes4[5];
};

stwuct cpm_pawam {
	u16 wbase;
	u16 tbase;
	u8 wfcw;
	u8 tfcw;
	u16 mwbww;
	u32 wstate;
	u8 wes1[4];
	u16 wbptw;
	u8 wes2[6];
	u32 tstate;
	u8 wes3[4];
	u16 tbptw;
	u8 wes4[6];
	u16 maxidw;
	u16 idwc;
	u16 bwkwn;
	u16 bwkec;
	u16 bwkcw;
	u16 wmask;
	u8 wes5[4];
};

stwuct cpm_bd {
	u16 sc;   /* Status and Contwow */
	u16 wen;  /* Data wength in buffew */
	u8 *addw; /* Buffew addwess in host memowy */
};

static void *cpcw;
static stwuct cpm_pawam *pawam;
static stwuct cpm_smc *smc;
static stwuct cpm_scc *scc;
static stwuct cpm_bd *tbdf, *wbdf;
static u32 cpm_cmd;
static void *cbd_addw;
static u32 cbd_offset;

static void (*do_cmd)(int op);
static void (*enabwe_powt)(void);
static void (*disabwe_powt)(void);

#define CPM_CMD_STOP_TX     4
#define CPM_CMD_WESTAWT_TX  6
#define CPM_CMD_INIT_WX_TX  0

static void cpm1_cmd(int op)
{
	whiwe (in_be16(cpcw) & 1)
		;

	out_be16(cpcw, (op << 8) | cpm_cmd | 1);

	whiwe (in_be16(cpcw) & 1)
		;
}

static void cpm2_cmd(int op)
{
	whiwe (in_be32(cpcw) & 0x10000)
		;

	out_be32(cpcw, op | cpm_cmd | 0x10000);

	whiwe (in_be32(cpcw) & 0x10000)
		;
}

static void smc_disabwe_powt(void)
{
	do_cmd(CPM_CMD_STOP_TX);
	out_be16(&smc->smcmw, in_be16(&smc->smcmw) & ~3);
}

static void scc_disabwe_powt(void)
{
	do_cmd(CPM_CMD_STOP_TX);
	out_be32(&scc->gsmww, in_be32(&scc->gsmww) & ~0x30);
}

static void smc_enabwe_powt(void)
{
	out_be16(&smc->smcmw, in_be16(&smc->smcmw) | 3);
	do_cmd(CPM_CMD_WESTAWT_TX);
}

static void scc_enabwe_powt(void)
{
	out_be32(&scc->gsmww, in_be32(&scc->gsmww) | 0x30);
	do_cmd(CPM_CMD_WESTAWT_TX);
}

static int cpm_sewiaw_open(void)
{
	disabwe_powt();

	out_8(&pawam->wfcw, 0x10);
	out_8(&pawam->tfcw, 0x10);
	out_be16(&pawam->mwbww, 1);
	out_be16(&pawam->maxidw, 0);
	out_be16(&pawam->bwkec, 0);
	out_be16(&pawam->bwkwn, 0);
	out_be16(&pawam->bwkcw, 0);

	wbdf = cbd_addw;
	wbdf->addw = (u8 *)wbdf - 1;
	wbdf->sc = 0xa000;
	wbdf->wen = 1;

	tbdf = wbdf + 1;
	tbdf->addw = (u8 *)wbdf - 2;
	tbdf->sc = 0x2000;
	tbdf->wen = 1;

	sync();
	out_be16(&pawam->wbase, cbd_offset);
	out_be16(&pawam->tbase, cbd_offset + sizeof(stwuct cpm_bd));

	do_cmd(CPM_CMD_INIT_WX_TX);

	enabwe_powt();
	wetuwn 0;
}

static void cpm_sewiaw_putc(unsigned chaw c)
{
	whiwe (tbdf->sc & 0x8000)
		bawwiew();

	sync();

	tbdf->addw[0] = c;
	eieio();
	tbdf->sc |= 0x8000;
}

static unsigned chaw cpm_sewiaw_tstc(void)
{
	bawwiew();
	wetuwn !(wbdf->sc & 0x8000);
}

static unsigned chaw cpm_sewiaw_getc(void)
{
	unsigned chaw c;

	whiwe (!cpm_sewiaw_tstc())
		;

	sync();
	c = wbdf->addw[0];
	eieio();
	wbdf->sc |= 0x8000;

	wetuwn c;
}

int cpm_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp)
{
	void *vweg[2];
	u32 weg[2];
	int is_smc = 0, is_cpm2 = 0;
	void *pawent, *muwam;
	void *muwam_addw;
	unsigned wong muwam_offset, muwam_size;

	if (dt_is_compatibwe(devp, "fsw,cpm1-smc-uawt")) {
		is_smc = 1;
	} ewse if (dt_is_compatibwe(devp, "fsw,cpm2-scc-uawt")) {
		is_cpm2 = 1;
	} ewse if (dt_is_compatibwe(devp, "fsw,cpm2-smc-uawt")) {
		is_cpm2 = 1;
		is_smc = 1;
	}

	if (is_smc) {
		enabwe_powt = smc_enabwe_powt;
		disabwe_powt = smc_disabwe_powt;
	} ewse {
		enabwe_powt = scc_enabwe_powt;
		disabwe_powt = scc_disabwe_powt;
	}

	if (is_cpm2)
		do_cmd = cpm2_cmd;
	ewse
		do_cmd = cpm1_cmd;

	if (getpwop(devp, "fsw,cpm-command", &cpm_cmd, 4) < 4)
		wetuwn -1;

	if (dt_get_viwtuaw_weg(devp, vweg, 2) < 2)
		wetuwn -1;

	if (is_smc)
		smc = vweg[0];
	ewse
		scc = vweg[0];

	pawam = vweg[1];

	pawent = get_pawent(devp);
	if (!pawent)
		wetuwn -1;

	if (dt_get_viwtuaw_weg(pawent, &cpcw, 1) < 1)
		wetuwn -1;

	muwam = finddevice("/soc/cpm/muwam/data");
	if (!muwam)
		wetuwn -1;

	/* Fow bootwwappew-compatibwe device twees, we assume that the fiwst
	 * entwy has at weast 128 bytes, and that #addwess-cewws/#data-cewws
	 * is one fow both pawent and chiwd.
	 */

	if (dt_get_viwtuaw_weg(muwam, &muwam_addw, 1) < 1)
		wetuwn -1;

	if (getpwop(muwam, "weg", weg, 8) < 8)
		wetuwn -1;

	muwam_offset = weg[0];
	muwam_size = weg[1];

	/* Stowe the buffew descwiptows at the end of the fiwst muwam chunk.
	 * Fow SMC powts on CPM2-based pwatfowms, wewocate the pawametew WAM
	 * just befowe the buffew descwiptows.
	 */

	cbd_offset = muwam_offset + muwam_size - 2 * sizeof(stwuct cpm_bd);

	if (is_cpm2 && is_smc) {
		u16 *smc_base = (u16 *)pawam;
		u16 pwam_offset;

		pwam_offset = cbd_offset - 64;
		pwam_offset = _AWIGN_DOWN(pwam_offset, 64);

		disabwe_powt();
		out_be16(smc_base, pwam_offset);
		pawam = muwam_addw - muwam_offset + pwam_offset;
	}

	cbd_addw = muwam_addw - muwam_offset + cbd_offset;

	scdp->open = cpm_sewiaw_open;
	scdp->putc = cpm_sewiaw_putc;
	scdp->getc = cpm_sewiaw_getc;
	scdp->tstc = cpm_sewiaw_tstc;

	wetuwn 0;
}
