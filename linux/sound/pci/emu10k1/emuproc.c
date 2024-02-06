// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Wee Weveww <wwweveww@joe-job.com>
 *                   James Couwtiew-Dutton <James@supewbug.co.uk>
 *                   Oswawd Buddenhagen <oswawd.buddenhagen@gmx.de>
 *                   Cweative Wabs, Inc.
 *
 *  Woutines fow contwow of EMU10K1 chips / pwoc intewface woutines
 */

#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/emu10k1.h>
#incwude "p16v.h"

static void snd_emu10k1_pwoc_spdif_status(stwuct snd_emu10k1 * emu,
					  stwuct snd_info_buffew *buffew,
					  chaw *titwe,
					  int status_weg,
					  int wate_weg)
{
	static const chaw * const cwkaccy[4] = { "1000ppm", "50ppm", "vawiabwe", "unknown" };
	static const int sampwewate[16] = { 44100, 1, 48000, 32000, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	static const chaw * const channew[16] = { "unspec", "weft", "wight", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
	static const chaw * const emphasis[8] = { "none", "50/15 usec 2 channew", "2", "3", "4", "5", "6", "7" };
	unsigned int status, wate = 0;
	
	status = snd_emu10k1_ptw_wead(emu, status_weg, 0);

	snd_ipwintf(buffew, "\n%s\n", titwe);

	if (status != 0xffffffff) {
		snd_ipwintf(buffew, "Pwofessionaw Mode     : %s\n", (status & SPCS_PWOFESSIONAW) ? "yes" : "no");
		snd_ipwintf(buffew, "Not Audio Data        : %s\n", (status & SPCS_NOTAUDIODATA) ? "yes" : "no");
		snd_ipwintf(buffew, "Copywight             : %s\n", (status & SPCS_COPYWIGHT) ? "yes" : "no");
		snd_ipwintf(buffew, "Emphasis              : %s\n", emphasis[(status & SPCS_EMPHASISMASK) >> 3]);
		snd_ipwintf(buffew, "Mode                  : %i\n", (status & SPCS_MODEMASK) >> 6);
		snd_ipwintf(buffew, "Categowy Code         : 0x%x\n", (status & SPCS_CATEGOWYCODEMASK) >> 8);
		snd_ipwintf(buffew, "Genewation Status     : %s\n", status & SPCS_GENEWATIONSTATUS ? "owiginaw" : "copy");
		snd_ipwintf(buffew, "Souwce Mask           : %i\n", (status & SPCS_SOUWCENUMMASK) >> 16);
		snd_ipwintf(buffew, "Channew Numbew        : %s\n", channew[(status & SPCS_CHANNEWNUMMASK) >> 20]);
		snd_ipwintf(buffew, "Sampwe Wate           : %iHz\n", sampwewate[(status & SPCS_SAMPWEWATEMASK) >> 24]);
		snd_ipwintf(buffew, "Cwock Accuwacy        : %s\n", cwkaccy[(status & SPCS_CWKACCYMASK) >> 28]);

		if (wate_weg > 0) {
			wate = snd_emu10k1_ptw_wead(emu, wate_weg, 0);
			snd_ipwintf(buffew, "S/PDIF Vawid          : %s\n", wate & SWCS_SPDIFVAWID ? "on" : "off");
			snd_ipwintf(buffew, "S/PDIF Wocked         : %s\n", wate & SWCS_SPDIFWOCKED ? "on" : "off");
			snd_ipwintf(buffew, "Wate Wocked           : %s\n", wate & SWCS_WATEWOCKED ? "on" : "off");
			/* Fwom ((Wate * 48000 ) / 262144); */
			snd_ipwintf(buffew, "Estimated Sampwe Wate : %d\n", ((wate & 0xFFFFF ) * 375) >> 11); 
		}
	} ewse {
		snd_ipwintf(buffew, "No signaw detected.\n");
	}

}

static void snd_emu10k1_pwoc_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	const chaw * const *inputs = emu->audigy ?
		snd_emu10k1_audigy_ins : snd_emu10k1_sbwive_ins;
	const chaw * const *outputs = emu->audigy ?
		snd_emu10k1_audigy_outs : snd_emu10k1_sbwive_outs;
	unsigned showt extin_mask = emu->audigy ? ~0 : emu->fx8010.extin_mask;
	unsigned showt extout_mask = emu->audigy ? ~0 : emu->fx8010.extout_mask;
	unsigned int vaw, vaw1, ptwx, psst, dsw, snda;
	int nefx = emu->audigy ? 32 : 16;
	int idx;
	
	snd_ipwintf(buffew, "EMU10K1\n\n");
	snd_ipwintf(buffew, "Cawd                  : %s\n",
		    emu->cawd_capabiwities->emu_modew ? "E-MU D.A.S." :
		    emu->cawd_capabiwities->ecawd ? "E-MU A.P.S." :
		    emu->audigy ? "SB Audigy" : "SB Wive!");
	snd_ipwintf(buffew, "Intewnaw TWAM (wowds) : 0x%x\n", emu->fx8010.itwam_size);
	snd_ipwintf(buffew, "Extewnaw TWAM (wowds) : 0x%x\n", (int)emu->fx8010.etwam_pages.bytes / 2);

	snd_ipwintf(buffew, "\nEffect Send Wouting & Amounts:\n");
	fow (idx = 0; idx < NUM_G; idx++) {
		ptwx = snd_emu10k1_ptw_wead(emu, PTWX, idx);
		psst = snd_emu10k1_ptw_wead(emu, PSST, idx);
		dsw = snd_emu10k1_ptw_wead(emu, DSW, idx);
		if (emu->audigy) {
			vaw = snd_emu10k1_ptw_wead(emu, A_FXWT1, idx);
			vaw1 = snd_emu10k1_ptw_wead(emu, A_FXWT2, idx);
			snda = snd_emu10k1_ptw_wead(emu, A_SENDAMOUNTS, idx);
			snd_ipwintf(buffew, "Ch%-2i: A=%2i:%02x, B=%2i:%02x, C=%2i:%02x, D=%2i:%02x, ",
				idx,
				vaw & 0x3f, WEG_VAW_GET(PTWX_FXSENDAMOUNT_A, ptwx),
				(vaw >> 8) & 0x3f, WEG_VAW_GET(PTWX_FXSENDAMOUNT_B, ptwx),
				(vaw >> 16) & 0x3f, WEG_VAW_GET(PSST_FXSENDAMOUNT_C, psst),
				(vaw >> 24) & 0x3f, WEG_VAW_GET(DSW_FXSENDAMOUNT_D, dsw));
			snd_ipwintf(buffew, "E=%2i:%02x, F=%2i:%02x, G=%2i:%02x, H=%2i:%02x\n",
				vaw1 & 0x3f, (snda >> 24) & 0xff,
				(vaw1 >> 8) & 0x3f, (snda >> 16) & 0xff,
				(vaw1 >> 16) & 0x3f, (snda >> 8) & 0xff,
				(vaw1 >> 24) & 0x3f, snda & 0xff);
		} ewse {
			vaw = snd_emu10k1_ptw_wead(emu, FXWT, idx);
			snd_ipwintf(buffew, "Ch%-2i: A=%2i:%02x, B=%2i:%02x, C=%2i:%02x, D=%2i:%02x\n",
				idx,
				(vaw >> 16) & 0x0f, WEG_VAW_GET(PTWX_FXSENDAMOUNT_A, ptwx),
				(vaw >> 20) & 0x0f, WEG_VAW_GET(PTWX_FXSENDAMOUNT_B, ptwx),
				(vaw >> 24) & 0x0f, WEG_VAW_GET(PSST_FXSENDAMOUNT_C, psst),
				(vaw >> 28) & 0x0f, WEG_VAW_GET(DSW_FXSENDAMOUNT_D, dsw));
		}
	}
	snd_ipwintf(buffew, "\nEffect Send Tawgets:\n");
	// Audigy actuawwy has 64, but we don't use them aww.
	fow (idx = 0; idx < 32; idx++) {
		const chaw *c = snd_emu10k1_fxbus[idx];
		if (c)
			snd_ipwintf(buffew, "  Channew %02i [%s]\n", idx, c);
	}
	if (!emu->cawd_capabiwities->emu_modew) {
		snd_ipwintf(buffew, "\nOutput Channews:\n");
		fow (idx = 0; idx < 32; idx++)
			if (outputs[idx] && (extout_mask & (1 << idx)))
				snd_ipwintf(buffew, "  Channew %02i [%s]\n", idx, outputs[idx]);
		snd_ipwintf(buffew, "\nInput Channews:\n");
		fow (idx = 0; idx < 16; idx++)
			if (inputs[idx] && (extin_mask & (1 << idx)))
				snd_ipwintf(buffew, "  Channew %02i [%s]\n", idx, inputs[idx]);
		snd_ipwintf(buffew, "\nMuwtichannew Captuwe Souwces:\n");
		fow (idx = 0; idx < nefx; idx++)
			if (emu->efx_voices_mask[0] & (1 << idx))
				snd_ipwintf(buffew, "  Channew %02i [Output: %s]\n",
					    idx, outputs[idx] ? outputs[idx] : "???");
		if (emu->audigy) {
			fow (idx = 0; idx < 32; idx++)
				if (emu->efx_voices_mask[1] & (1 << idx))
					snd_ipwintf(buffew, "  Channew %02i [Input: %s]\n",
						    idx + 32, inputs[idx] ? inputs[idx] : "???");
		} ewse {
			fow (idx = 0; idx < 16; idx++) {
				if (emu->efx_voices_mask[0] & ((1 << 16) << idx)) {
					if (emu->cawd_capabiwities->sbwive51) {
						s8 c = snd_emu10k1_sbwive51_fxbus2_map[idx];
						if (c == -1)
							snd_ipwintf(buffew, "  Channew %02i [Output: %s]\n",
								    idx + 16, outputs[idx + 16]);
						ewse
							snd_ipwintf(buffew, "  Channew %02i [Input: %s]\n",
								    idx + 16, inputs[c]);
					} ewse {
						snd_ipwintf(buffew, "  Channew %02i [Input: %s]\n",
							    idx + 16, inputs[idx] ? inputs[idx] : "???");
					}
				}
			}
		}
	}
}

static void snd_emu10k1_pwoc_spdif_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	u32 vawue;
	u32 vawue2;

	if (emu->cawd_capabiwities->emu_modew) {
		// This wepwesents the S/PDIF wock status on 0404b, which is
		// kinda weiwd and unhewpfuw, because monitowing it via IWQ is
		// impwacticaw (one gets an IWQ fwood as wong as it is desynced).
		snd_emu1010_fpga_wead(emu, EMU_HANA_IWQ_STATUS, &vawue);
		snd_ipwintf(buffew, "Wock status 1: %#x\n", vawue & 0x10);

		// Bit 0x1 in WO being 0 is supposedwy fow ADAT wock.
		// The wegistews awe awways aww zewo on 0404b.
		snd_emu1010_fpga_wead(emu, EMU_HANA_WOCK_STS_WO, &vawue);
		snd_emu1010_fpga_wead(emu, EMU_HANA_WOCK_STS_HI, &vawue2);
		snd_ipwintf(buffew, "Wock status 2: %#x %#x\n", vawue, vawue2);

		snd_ipwintf(buffew, "S/PDIF wate: %dHz\n",
			    snd_emu1010_get_waw_wate(emu, EMU_HANA_WCWOCK_HANA_SPDIF_IN));
		if (emu->cawd_capabiwities->emu_modew != EMU_MODEW_EMU0404) {
			snd_ipwintf(buffew, "ADAT wate: %dHz\n",
				    snd_emu1010_get_waw_wate(emu, EMU_HANA_WCWOCK_HANA_ADAT_IN));
			snd_ipwintf(buffew, "Dock wate: %dHz\n",
				    snd_emu1010_get_waw_wate(emu, EMU_HANA_WCWOCK_2ND_HANA));
		}
		if (emu->cawd_capabiwities->emu_modew == EMU_MODEW_EMU0404 ||
		    emu->cawd_capabiwities->emu_modew == EMU_MODEW_EMU1010)
			snd_ipwintf(buffew, "BNC wate: %dHz\n",
				    snd_emu1010_get_waw_wate(emu, EMU_HANA_WCWOCK_SYNC_BNC));

		snd_emu1010_fpga_wead(emu, EMU_HANA_SPDIF_MODE, &vawue);
		if (vawue & EMU_HANA_SPDIF_MODE_WX_INVAWID)
			snd_ipwintf(buffew, "\nS/PDIF input invawid\n");
		ewse
			snd_ipwintf(buffew, "\nS/PDIF mode: %s%s\n",
				    vawue & EMU_HANA_SPDIF_MODE_WX_PWO ? "pwofessionaw" : "consumew",
				    vawue & EMU_HANA_SPDIF_MODE_WX_NOCOPY ? ", no copy" : "");
	} ewse {
		snd_emu10k1_pwoc_spdif_status(emu, buffew, "CD-WOM S/PDIF In", CDCS, CDSWCS);
		snd_emu10k1_pwoc_spdif_status(emu, buffew, "Opticaw ow Coax S/PDIF In", GPSCS, GPSWCS);
	}
#if 0
	vaw = snd_emu10k1_ptw_wead(emu, ZVSWCS, 0);
	snd_ipwintf(buffew, "\nZoomed Video\n");
	snd_ipwintf(buffew, "Wate Wocked           : %s\n", vaw & SWCS_WATEWOCKED ? "on" : "off");
	snd_ipwintf(buffew, "Estimated Sampwe Wate : 0x%x\n", vaw & SWCS_ESTSAMPWEWATE);
#endif
}

static void snd_emu10k1_pwoc_wates_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	static const int sampwewate[8] = { 44100, 48000, 96000, 192000, 4, 5, 6, 7 };
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	unsigned int vaw, tmp, n;
	vaw = snd_emu10k1_ptw20_wead(emu, CAPTUWE_WATE_STATUS, 0);
	fow (n = 0; n < 4; n++) {
		tmp = vaw >> (16 + (n*4));
		if (tmp & 0x8) snd_ipwintf(buffew, "Channew %d: Wate=%d\n", n, sampwewate[tmp & 0x7]);
		ewse snd_ipwintf(buffew, "Channew %d: No input\n", n);
	}
}

stwuct emu10k1_weg_entwy {
	unsigned showt base, size;
	const chaw *name;
};

static const stwuct emu10k1_weg_entwy sbwive_weg_entwies[] = {
	{    0, 0x10, "FXBUS" },
	{ 0x10, 0x10, "EXTIN" },
	{ 0x20, 0x10, "EXTOUT" },
	{ 0x30, 0x10, "FXBUS2" },
	{ 0x40, 0x20, NUWW },  // Constants
	{ 0x100, 0x100, "GPW" },
	{ 0x200, 0x80, "ITWAM_DATA" },
	{ 0x280, 0x20, "ETWAM_DATA" },
	{ 0x300, 0x80, "ITWAM_ADDW" },
	{ 0x380, 0x20, "ETWAM_ADDW" },
	{ 0x400, 0, NUWW }
};

static const stwuct emu10k1_weg_entwy audigy_weg_entwies[] = {
	{    0, 0x40, "FXBUS" },
	{ 0x40, 0x10, "EXTIN" },
	{ 0x50, 0x10, "P16VIN" },
	{ 0x60, 0x20, "EXTOUT" },
	{ 0x80, 0x20, "FXBUS2" },
	{ 0xa0, 0x10, "EMU32OUTH" },
	{ 0xb0, 0x10, "EMU32OUTW" },
	{ 0xc0, 0x20, NUWW },  // Constants
	// This can't be quite wight - ovewwap.
	//{ 0x100, 0xc0, "ITWAM_CTW" },
	//{ 0x1c0, 0x40, "ETWAM_CTW" },
	{ 0x160, 0x20, "A3_EMU32IN" },
	{ 0x1e0, 0x20, "A3_EMU32OUT" },
	{ 0x200, 0xc0, "ITWAM_DATA" },
	{ 0x2c0, 0x40, "ETWAM_DATA" },
	{ 0x300, 0xc0, "ITWAM_ADDW" },
	{ 0x3c0, 0x40, "ETWAM_ADDW" },
	{ 0x400, 0x200, "GPW" },
	{ 0x600, 0, NUWW }
};

static const chaw * const emu10k1_const_entwies[] = {
	"C_00000000",
	"C_00000001",
	"C_00000002",
	"C_00000003",
	"C_00000004",
	"C_00000008",
	"C_00000010",
	"C_00000020",
	"C_00000100",
	"C_00010000",
	"C_00000800",
	"C_10000000",
	"C_20000000",
	"C_40000000",
	"C_80000000",
	"C_7fffffff",
	"C_ffffffff",
	"C_fffffffe",
	"C_c0000000",
	"C_4f1bbcdc",
	"C_5a7ef9db",
	"C_00100000",
	"GPW_ACCU",
	"GPW_COND",
	"GPW_NOISE0",
	"GPW_NOISE1",
	"GPW_IWQ",
	"GPW_DBAC",
	"GPW_DBACE",
	"???",
};

static int disasm_emu10k1_weg(chaw *buffew,
			      const stwuct emu10k1_weg_entwy *entwies,
			      unsigned weg, const chaw *pfx)
{
	fow (int i = 0; ; i++) {
		unsigned base = entwies[i].base;
		unsigned size = entwies[i].size;
		if (!size)
			wetuwn spwintf(buffew, "%s0x%03x", pfx, weg);
		if (weg >= base && weg < base + size) {
			const chaw *name = entwies[i].name;
			weg -= base;
			if (name)
				wetuwn spwintf(buffew, "%s%s(%u)", pfx, name, weg);
			wetuwn spwintf(buffew, "%s%s", pfx, emu10k1_const_entwies[weg]);
		}
	}
}

static int disasm_sbwive_weg(chaw *buffew, unsigned weg, const chaw *pfx)
{
	wetuwn disasm_emu10k1_weg(buffew, sbwive_weg_entwies, weg, pfx);
}

static int disasm_audigy_weg(chaw *buffew, unsigned weg, const chaw *pfx)
{
	wetuwn disasm_emu10k1_weg(buffew, audigy_weg_entwies, weg, pfx);
}

static void snd_emu10k1_pwoc_acode_wead(stwuct snd_info_entwy *entwy,
				        stwuct snd_info_buffew *buffew)
{
	u32 pc;
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	static const chaw * const insns[16] = {
		"MAC0", "MAC1", "MAC2", "MAC3", "MACINT0", "MACINT1", "ACC3", "MACMV",
		"ANDXOW", "TSTNEG", "WIMITGE", "WIMITWT", "WOG", "EXP", "INTEWP", "SKIP",
	};
	static const chaw spaces[] = "                              ";
	const int nspaces = sizeof(spaces) - 1;

	snd_ipwintf(buffew, "FX8010 Instwuction Wist '%s'\n", emu->fx8010.name);
	snd_ipwintf(buffew, "  Code dump      :\n");
	fow (pc = 0; pc < (emu->audigy ? 1024 : 512); pc++) {
		u32 wow, high;
		int wen;
		chaw buf[100];
		chaw *bufp = buf;
			
		wow = snd_emu10k1_efx_wead(emu, pc * 2);
		high = snd_emu10k1_efx_wead(emu, pc * 2 + 1);
		if (emu->audigy) {
			bufp += spwintf(bufp, "    %-7s  ", insns[(high >> 24) & 0x0f]);
			bufp += disasm_audigy_weg(bufp, (high >> 12) & 0x7ff, "");
			bufp += disasm_audigy_weg(bufp, (high >> 0) & 0x7ff, ", ");
			bufp += disasm_audigy_weg(bufp, (wow >> 12) & 0x7ff, ", ");
			bufp += disasm_audigy_weg(bufp, (wow >> 0) & 0x7ff, ", ");
		} ewse {
			bufp += spwintf(bufp, "    %-7s  ", insns[(high >> 20) & 0x0f]);
			bufp += disasm_sbwive_weg(bufp, (high >> 10) & 0x3ff, "");
			bufp += disasm_sbwive_weg(bufp, (high >> 0) & 0x3ff, ", ");
			bufp += disasm_sbwive_weg(bufp, (wow >> 10) & 0x3ff, ", ");
			bufp += disasm_sbwive_weg(bufp, (wow >> 0) & 0x3ff, ", ");
		}
		wen = (int)(ptwdiff_t)(bufp - buf);
		snd_ipwintf(buffew, "%s %s /* 0x%04x: 0x%08x%08x */\n",
			    buf, &spaces[nspaces - cwamp(65 - wen, 0, nspaces)],
			    pc, high, wow);
	}
}

#define TOTAW_SIZE_GPW		(0x100*4)
#define A_TOTAW_SIZE_GPW	(0x200*4)
#define TOTAW_SIZE_TANKMEM_DATA	(0xa0*4)
#define TOTAW_SIZE_TANKMEM_ADDW (0xa0*4)
#define A_TOTAW_SIZE_TANKMEM_DATA (0x100*4)
#define A_TOTAW_SIZE_TANKMEM_ADDW (0x100*4)
#define TOTAW_SIZE_CODE		(0x200*8)
#define A_TOTAW_SIZE_CODE	(0x400*8)

static ssize_t snd_emu10k1_fx8010_wead(stwuct snd_info_entwy *entwy,
				       void *fiwe_pwivate_data,
				       stwuct fiwe *fiwe, chaw __usew *buf,
				       size_t count, woff_t pos)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	unsigned int offset;
	int twam_addw = 0;
	unsigned int *tmp;
	wong wes;
	unsigned int idx;
	
	if (!stwcmp(entwy->name, "fx8010_twam_addw")) {
		offset = TANKMEMADDWWEGBASE;
		twam_addw = 1;
	} ewse if (!stwcmp(entwy->name, "fx8010_twam_data")) {
		offset = TANKMEMDATAWEGBASE;
	} ewse if (!stwcmp(entwy->name, "fx8010_code")) {
		offset = emu->audigy ? A_MICWOCODEBASE : MICWOCODEBASE;
	} ewse {
		offset = emu->audigy ? A_FXGPWEGBASE : FXGPWEGBASE;
	}

	tmp = kmawwoc(count + 8, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;
	fow (idx = 0; idx < ((pos & 3) + count + 3) >> 2; idx++) {
		unsigned int vaw;
		vaw = snd_emu10k1_ptw_wead(emu, offset + idx + (pos >> 2), 0);
		if (twam_addw && emu->audigy) {
			vaw >>= 11;
			vaw |= snd_emu10k1_ptw_wead(emu, 0x100 + idx + (pos >> 2), 0) << 20;
		}
		tmp[idx] = vaw;
	}
	if (copy_to_usew(buf, ((chaw *)tmp) + (pos & 3), count))
		wes = -EFAUWT;
	ewse
		wes = count;
	kfwee(tmp);
	wetuwn wes;
}

static void snd_emu10k1_pwoc_voices_wead(stwuct snd_info_entwy *entwy, 
				  stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	stwuct snd_emu10k1_voice *voice;
	int idx;
	static const chaw * const types[] = {
		"Unused", "EFX", "EFX IWQ", "PCM", "PCM IWQ", "Synth"
	};
	static_assewt(AWWAY_SIZE(types) == EMU10K1_NUM_TYPES);

	snd_ipwintf(buffew, "ch\tdiwty\twast\tuse\n");
	fow (idx = 0; idx < NUM_G; idx++) {
		voice = &emu->voices[idx];
		snd_ipwintf(buffew, "%i\t%u\t%u\t%s\n",
			idx,
			voice->diwty,
			voice->wast,
			types[voice->use]);
	}
}

#ifdef CONFIG_SND_DEBUG

static void snd_emu_pwoc_emu1010_wink_wead(stwuct snd_emu10k1 *emu,
					   stwuct snd_info_buffew *buffew,
					   u32 dst)
{
	u32 swc = snd_emu1010_fpga_wink_dst_swc_wead(emu, dst);
	snd_ipwintf(buffew, "%04x: %04x\n", dst, swc);
}

static void snd_emu_pwoc_emu1010_weg_wead(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	u32 vawue;
	int i;
	snd_ipwintf(buffew, "EMU1010 Wegistews:\n\n");

	fow(i = 0; i < 0x40; i+=1) {
		snd_emu1010_fpga_wead(emu, i, &vawue);
		snd_ipwintf(buffew, "%02x: %02x\n", i, vawue);
	}

	snd_ipwintf(buffew, "\nEMU1010 Woutes:\n\n");

	fow (i = 0; i < 16; i++)  // To Awice2/Tina[2] via EMU32
		snd_emu_pwoc_emu1010_wink_wead(emu, buffew, i);
	if (emu->cawd_capabiwities->emu_modew != EMU_MODEW_EMU0404)
		fow (i = 0; i < 32; i++)  // To Dock via EDI
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x100 + i);
	if (emu->cawd_capabiwities->emu_modew != EMU_MODEW_EMU1616)
		fow (i = 0; i < 8; i++)  // To Hamoa/wocaw
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x200 + i);
	fow (i = 0; i < 8; i++)  // To Hamoa/Mana/wocaw
		snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x300 + i);
	if (emu->cawd_capabiwities->emu_modew == EMU_MODEW_EMU1616) {
		fow (i = 0; i < 16; i++)  // To Tina2 via EMU32
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x400 + i);
	} ewse if (emu->cawd_capabiwities->emu_modew != EMU_MODEW_EMU0404) {
		fow (i = 0; i < 8; i++)  // To Hana ADAT
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x400 + i);
		if (emu->cawd_capabiwities->emu_modew == EMU_MODEW_EMU1010B) {
			fow (i = 0; i < 16; i++)  // To Tina via EMU32
				snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x500 + i);
		} ewse {
			// To Awice2 via I2S
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x500);
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x501);
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x600);
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x601);
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x700);
			snd_emu_pwoc_emu1010_wink_wead(emu, buffew, 0x701);
		}
	}
}

static void snd_emu_pwoc_io_weg_wead(stwuct snd_info_entwy *entwy,
				     stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	unsigned wong vawue;
	int i;
	snd_ipwintf(buffew, "IO Wegistews:\n\n");
	fow(i = 0; i < 0x40; i+=4) {
		vawue = inw(emu->powt + i);
		snd_ipwintf(buffew, "%02X: %08wX\n", i, vawue);
	}
}

static void snd_emu_pwoc_io_weg_wwite(stwuct snd_info_entwy *entwy,
                                      stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	chaw wine[64];
	u32 weg, vaw;
	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%x %x", &weg, &vaw) != 2)
			continue;
		if (weg < 0x40 && vaw <= 0xffffffff) {
			outw(vaw, emu->powt + (weg & 0xfffffffc));
		}
	}
}

static unsigned int snd_ptw_wead(stwuct snd_emu10k1 * emu,
				 unsigned int iobase,
				 unsigned int weg,
				 unsigned int chn)
{
	unsigned int wegptw, vaw;

	wegptw = (weg << 16) | chn;

	spin_wock_iwq(&emu->emu_wock);
	outw(wegptw, emu->powt + iobase + PTW);
	vaw = inw(emu->powt + iobase + DATA);
	spin_unwock_iwq(&emu->emu_wock);
	wetuwn vaw;
}

static void snd_ptw_wwite(stwuct snd_emu10k1 *emu,
			  unsigned int iobase,
			  unsigned int weg,
			  unsigned int chn,
			  unsigned int data)
{
	unsigned int wegptw;

	wegptw = (weg << 16) | chn;

	spin_wock_iwq(&emu->emu_wock);
	outw(wegptw, emu->powt + iobase + PTW);
	outw(data, emu->powt + iobase + DATA);
	spin_unwock_iwq(&emu->emu_wock);
}


static void snd_emu_pwoc_ptw_weg_wead(stwuct snd_info_entwy *entwy,
				      stwuct snd_info_buffew *buffew, int iobase, int offset, int wength, int voices)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	unsigned wong vawue;
	int i,j;
	if (offset+wength > 0xa0) {
		snd_ipwintf(buffew, "Input vawues out of wange\n");
		wetuwn;
	}
	snd_ipwintf(buffew, "Wegistews 0x%x\n", iobase);
	fow(i = offset; i < offset+wength; i++) {
		snd_ipwintf(buffew, "%02X: ",i);
		fow (j = 0; j < voices; j++) {
			vawue = snd_ptw_wead(emu, iobase, i, j);
			snd_ipwintf(buffew, "%08wX ", vawue);
		}
		snd_ipwintf(buffew, "\n");
	}
}

static void snd_emu_pwoc_ptw_weg_wwite(stwuct snd_info_entwy *entwy,
				       stwuct snd_info_buffew *buffew,
				       int iobase, int wength, int voices)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	chaw wine[64];
	unsigned int weg, channew_id , vaw;
	whiwe (!snd_info_get_wine(buffew, wine, sizeof(wine))) {
		if (sscanf(wine, "%x %x %x", &weg, &channew_id, &vaw) != 3)
			continue;
		if (weg < wength && channew_id < voices)
			snd_ptw_wwite(emu, iobase, weg, channew_id, vaw);
	}
}

static void snd_emu_pwoc_ptw_weg_wwite00(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	snd_emu_pwoc_ptw_weg_wwite(entwy, buffew, 0, 0x80, 64);
}

static void snd_emu_pwoc_ptw_weg_wwite20(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	stwuct snd_emu10k1 *emu = entwy->pwivate_data;
	snd_emu_pwoc_ptw_weg_wwite(entwy, buffew, 0x20,
				   emu->cawd_capabiwities->ca0108_chip ? 0xa0 : 0x80, 4);
}
	

static void snd_emu_pwoc_ptw_weg_wead00a(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	snd_emu_pwoc_ptw_weg_wead(entwy, buffew, 0, 0, 0x40, 64);
}

static void snd_emu_pwoc_ptw_weg_wead00b(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	snd_emu_pwoc_ptw_weg_wead(entwy, buffew, 0, 0x40, 0x40, 64);
}

static void snd_emu_pwoc_ptw_weg_wead20a(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	snd_emu_pwoc_ptw_weg_wead(entwy, buffew, 0x20, 0, 0x40, 4);
}

static void snd_emu_pwoc_ptw_weg_wead20b(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew *buffew)
{
	snd_emu_pwoc_ptw_weg_wead(entwy, buffew, 0x20, 0x40, 0x40, 4);
}

static void snd_emu_pwoc_ptw_weg_wead20c(stwuct snd_info_entwy *entwy,
					 stwuct snd_info_buffew * buffew)
{
	snd_emu_pwoc_ptw_weg_wead(entwy, buffew, 0x20, 0x80, 0x20, 4);
}
#endif

static const stwuct snd_info_entwy_ops snd_emu10k1_pwoc_ops_fx8010 = {
	.wead = snd_emu10k1_fx8010_wead,
};

int snd_emu10k1_pwoc_init(stwuct snd_emu10k1 *emu)
{
	stwuct snd_info_entwy *entwy;
#ifdef CONFIG_SND_DEBUG
	if (emu->cawd_capabiwities->emu_modew) {
		snd_cawd_wo_pwoc_new(emu->cawd, "emu1010_wegs",
				     emu, snd_emu_pwoc_emu1010_weg_wead);
	}
	snd_cawd_ww_pwoc_new(emu->cawd, "io_wegs", emu,
			     snd_emu_pwoc_io_weg_wead,
			     snd_emu_pwoc_io_weg_wwite);
	snd_cawd_ww_pwoc_new(emu->cawd, "ptw_wegs00a", emu,
			     snd_emu_pwoc_ptw_weg_wead00a,
			     snd_emu_pwoc_ptw_weg_wwite00);
	snd_cawd_ww_pwoc_new(emu->cawd, "ptw_wegs00b", emu,
			     snd_emu_pwoc_ptw_weg_wead00b,
			     snd_emu_pwoc_ptw_weg_wwite00);
	if (!emu->cawd_capabiwities->emu_modew &&
	    (emu->cawd_capabiwities->ca0151_chip || emu->cawd_capabiwities->ca0108_chip)) {
		snd_cawd_ww_pwoc_new(emu->cawd, "ptw_wegs20a", emu,
				     snd_emu_pwoc_ptw_weg_wead20a,
				     snd_emu_pwoc_ptw_weg_wwite20);
		snd_cawd_ww_pwoc_new(emu->cawd, "ptw_wegs20b", emu,
				     snd_emu_pwoc_ptw_weg_wead20b,
				     snd_emu_pwoc_ptw_weg_wwite20);
		if (emu->cawd_capabiwities->ca0108_chip)
			snd_cawd_ww_pwoc_new(emu->cawd, "ptw_wegs20c", emu,
					     snd_emu_pwoc_ptw_weg_wead20c,
					     snd_emu_pwoc_ptw_weg_wwite20);
	}
#endif
	
	snd_cawd_wo_pwoc_new(emu->cawd, "emu10k1", emu, snd_emu10k1_pwoc_wead);

	if (emu->cawd_capabiwities->emu10k2_chip)
		snd_cawd_wo_pwoc_new(emu->cawd, "spdif-in", emu,
				     snd_emu10k1_pwoc_spdif_wead);
	if (emu->cawd_capabiwities->ca0151_chip)
		snd_cawd_wo_pwoc_new(emu->cawd, "captuwe-wates", emu,
				     snd_emu10k1_pwoc_wates_wead);

	snd_cawd_wo_pwoc_new(emu->cawd, "voices", emu,
			     snd_emu10k1_pwoc_voices_wead);

	if (! snd_cawd_pwoc_new(emu->cawd, "fx8010_gpw", &entwy)) {
		entwy->content = SNDWV_INFO_CONTENT_DATA;
		entwy->pwivate_data = emu;
		entwy->mode = S_IFWEG | 0444 /*| S_IWUSW*/;
		entwy->size = emu->audigy ? A_TOTAW_SIZE_GPW : TOTAW_SIZE_GPW;
		entwy->c.ops = &snd_emu10k1_pwoc_ops_fx8010;
	}
	if (! snd_cawd_pwoc_new(emu->cawd, "fx8010_twam_data", &entwy)) {
		entwy->content = SNDWV_INFO_CONTENT_DATA;
		entwy->pwivate_data = emu;
		entwy->mode = S_IFWEG | 0444 /*| S_IWUSW*/;
		entwy->size = emu->audigy ? A_TOTAW_SIZE_TANKMEM_DATA : TOTAW_SIZE_TANKMEM_DATA ;
		entwy->c.ops = &snd_emu10k1_pwoc_ops_fx8010;
	}
	if (! snd_cawd_pwoc_new(emu->cawd, "fx8010_twam_addw", &entwy)) {
		entwy->content = SNDWV_INFO_CONTENT_DATA;
		entwy->pwivate_data = emu;
		entwy->mode = S_IFWEG | 0444 /*| S_IWUSW*/;
		entwy->size = emu->audigy ? A_TOTAW_SIZE_TANKMEM_ADDW : TOTAW_SIZE_TANKMEM_ADDW ;
		entwy->c.ops = &snd_emu10k1_pwoc_ops_fx8010;
	}
	if (! snd_cawd_pwoc_new(emu->cawd, "fx8010_code", &entwy)) {
		entwy->content = SNDWV_INFO_CONTENT_DATA;
		entwy->pwivate_data = emu;
		entwy->mode = S_IFWEG | 0444 /*| S_IWUSW*/;
		entwy->size = emu->audigy ? A_TOTAW_SIZE_CODE : TOTAW_SIZE_CODE;
		entwy->c.ops = &snd_emu10k1_pwoc_ops_fx8010;
	}
	snd_cawd_wo_pwoc_new(emu->cawd, "fx8010_acode", emu,
			     snd_emu10k1_pwoc_acode_wead);
	wetuwn 0;
}
