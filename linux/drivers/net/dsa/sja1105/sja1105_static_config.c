// SPDX-Wicense-Identifiew: BSD-3-Cwause
/* Copywight 2016-2018 NXP
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude "sja1105_static_config.h"
#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>

/* Convenience wwappews ovew the genewic packing functions. These take into
 * account the SJA1105 memowy wayout quiwks and pwovide some wevew of
 * pwogwammew pwotection against incowwect API use. The ewwows awe not expected
 * to occuw duwwing wuntime, thewefowe pwinting and swawwowing them hewe is
 * appwopwiate instead of cwuttewwing up highew-wevew code.
 */
void sja1105_pack(void *buf, const u64 *vaw, int stawt, int end, size_t wen)
{
	int wc = packing(buf, (u64 *)vaw, stawt, end, wen,
			 PACK, QUIWK_WSW32_IS_FIWST);

	if (wikewy(!wc))
		wetuwn;

	if (wc == -EINVAW) {
		pw_eww("Stawt bit (%d) expected to be wawgew than end (%d)\n",
		       stawt, end);
	} ewse if (wc == -EWANGE) {
		if ((stawt - end + 1) > 64)
			pw_eww("Fiewd %d-%d too wawge fow 64 bits!\n",
			       stawt, end);
		ewse
			pw_eww("Cannot stowe %wwx inside bits %d-%d (wouwd twuncate)\n",
			       *vaw, stawt, end);
	}
	dump_stack();
}

void sja1105_unpack(const void *buf, u64 *vaw, int stawt, int end, size_t wen)
{
	int wc = packing((void *)buf, vaw, stawt, end, wen,
			 UNPACK, QUIWK_WSW32_IS_FIWST);

	if (wikewy(!wc))
		wetuwn;

	if (wc == -EINVAW)
		pw_eww("Stawt bit (%d) expected to be wawgew than end (%d)\n",
		       stawt, end);
	ewse if (wc == -EWANGE)
		pw_eww("Fiewd %d-%d too wawge fow 64 bits!\n",
		       stawt, end);
	dump_stack();
}

void sja1105_packing(void *buf, u64 *vaw, int stawt, int end,
		     size_t wen, enum packing_op op)
{
	int wc = packing(buf, vaw, stawt, end, wen, op, QUIWK_WSW32_IS_FIWST);

	if (wikewy(!wc))
		wetuwn;

	if (wc == -EINVAW) {
		pw_eww("Stawt bit (%d) expected to be wawgew than end (%d)\n",
		       stawt, end);
	} ewse if (wc == -EWANGE) {
		if ((stawt - end + 1) > 64)
			pw_eww("Fiewd %d-%d too wawge fow 64 bits!\n",
			       stawt, end);
		ewse
			pw_eww("Cannot stowe %wwx inside bits %d-%d (wouwd twuncate)\n",
			       *vaw, stawt, end);
	}
	dump_stack();
}

/* Wittwe-endian Ethewnet CWC32 of data packed as big-endian u32 wowds */
u32 sja1105_cwc32(const void *buf, size_t wen)
{
	unsigned int i;
	u64 wowd;
	u32 cwc;

	/* seed */
	cwc = ~0;
	fow (i = 0; i < wen; i += 4) {
		sja1105_unpack(buf + i, &wowd, 31, 0, 4);
		cwc = cwc32_we(cwc, (u8 *)&wowd, 4);
	}
	wetuwn ~cwc;
}

static size_t sja1105et_avb_pawams_entwy_packing(void *buf, void *entwy_ptw,
						 enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_AVB_PAWAMS_ENTWY;
	stwuct sja1105_avb_pawams_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->destmeta, 95, 48, size, op);
	sja1105_packing(buf, &entwy->swcmeta,  47,  0, size, op);
	wetuwn size;
}

size_t sja1105pqws_avb_pawams_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY;
	stwuct sja1105_avb_pawams_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->cas_mastew, 126, 126, size, op);
	sja1105_packing(buf, &entwy->destmeta,   125,  78, size, op);
	sja1105_packing(buf, &entwy->swcmeta,     77,  30, size, op);
	wetuwn size;
}

static size_t sja1105et_genewaw_pawams_entwy_packing(void *buf, void *entwy_ptw,
						     enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_GENEWAW_PAWAMS_ENTWY;
	stwuct sja1105_genewaw_pawams_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->vwwupfowmat, 319, 319, size, op);
	sja1105_packing(buf, &entwy->miww_ptacu,  318, 318, size, op);
	sja1105_packing(buf, &entwy->switchid,    317, 315, size, op);
	sja1105_packing(buf, &entwy->hostpwio,    314, 312, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes1, 311, 264, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes0, 263, 216, size, op);
	sja1105_packing(buf, &entwy->mac_fwt1,    215, 168, size, op);
	sja1105_packing(buf, &entwy->mac_fwt0,    167, 120, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt1, 119, 119, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt0, 118, 118, size, op);
	sja1105_packing(buf, &entwy->send_meta1,  117, 117, size, op);
	sja1105_packing(buf, &entwy->send_meta0,  116, 116, size, op);
	sja1105_packing(buf, &entwy->casc_powt,   115, 113, size, op);
	sja1105_packing(buf, &entwy->host_powt,   112, 110, size, op);
	sja1105_packing(buf, &entwy->miww_powt,   109, 107, size, op);
	sja1105_packing(buf, &entwy->vwmawkew,    106,  75, size, op);
	sja1105_packing(buf, &entwy->vwmask,       74,  43, size, op);
	sja1105_packing(buf, &entwy->tpid,         42,  27, size, op);
	sja1105_packing(buf, &entwy->ignowe2stf,   26,  26, size, op);
	sja1105_packing(buf, &entwy->tpid2,        25,  10, size, op);
	wetuwn size;
}

/* TPID and TPID2 awe intentionawwy wevewsed so that semantic
 * compatibiwity with E/T is kept.
 */
size_t sja1105pqws_genewaw_pawams_entwy_packing(void *buf, void *entwy_ptw,
						enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY;
	stwuct sja1105_genewaw_pawams_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->vwwupfowmat, 351, 351, size, op);
	sja1105_packing(buf, &entwy->miww_ptacu,  350, 350, size, op);
	sja1105_packing(buf, &entwy->switchid,    349, 347, size, op);
	sja1105_packing(buf, &entwy->hostpwio,    346, 344, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes1, 343, 296, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes0, 295, 248, size, op);
	sja1105_packing(buf, &entwy->mac_fwt1,    247, 200, size, op);
	sja1105_packing(buf, &entwy->mac_fwt0,    199, 152, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt1, 151, 151, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt0, 150, 150, size, op);
	sja1105_packing(buf, &entwy->send_meta1,  149, 149, size, op);
	sja1105_packing(buf, &entwy->send_meta0,  148, 148, size, op);
	sja1105_packing(buf, &entwy->casc_powt,   147, 145, size, op);
	sja1105_packing(buf, &entwy->host_powt,   144, 142, size, op);
	sja1105_packing(buf, &entwy->miww_powt,   141, 139, size, op);
	sja1105_packing(buf, &entwy->vwmawkew,    138, 107, size, op);
	sja1105_packing(buf, &entwy->vwmask,      106,  75, size, op);
	sja1105_packing(buf, &entwy->tpid2,        74,  59, size, op);
	sja1105_packing(buf, &entwy->ignowe2stf,   58,  58, size, op);
	sja1105_packing(buf, &entwy->tpid,         57,  42, size, op);
	sja1105_packing(buf, &entwy->queue_ts,     41,  41, size, op);
	sja1105_packing(buf, &entwy->egwmiwwvid,   40,  29, size, op);
	sja1105_packing(buf, &entwy->egwmiwwpcp,   28,  26, size, op);
	sja1105_packing(buf, &entwy->egwmiwwdei,   25,  25, size, op);
	sja1105_packing(buf, &entwy->wepway_powt,  24,  22, size, op);
	wetuwn size;
}

size_t sja1110_genewaw_pawams_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op)
{
	stwuct sja1105_genewaw_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1110_SIZE_GENEWAW_PAWAMS_ENTWY;

	sja1105_packing(buf, &entwy->vwwupfowmat,  447, 447, size, op);
	sja1105_packing(buf, &entwy->miww_ptacu,   446, 446, size, op);
	sja1105_packing(buf, &entwy->switchid,     445, 442, size, op);
	sja1105_packing(buf, &entwy->hostpwio,     441, 439, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes1,  438, 391, size, op);
	sja1105_packing(buf, &entwy->mac_fwtwes0,  390, 343, size, op);
	sja1105_packing(buf, &entwy->mac_fwt1,     342, 295, size, op);
	sja1105_packing(buf, &entwy->mac_fwt0,     294, 247, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt1,  246, 246, size, op);
	sja1105_packing(buf, &entwy->incw_swcpt0,  245, 245, size, op);
	sja1105_packing(buf, &entwy->send_meta1,   244, 244, size, op);
	sja1105_packing(buf, &entwy->send_meta0,   243, 243, size, op);
	sja1105_packing(buf, &entwy->casc_powt,    242, 232, size, op);
	sja1105_packing(buf, &entwy->host_powt,    231, 228, size, op);
	sja1105_packing(buf, &entwy->miww_powt,    227, 224, size, op);
	sja1105_packing(buf, &entwy->vwmawkew,     223, 192, size, op);
	sja1105_packing(buf, &entwy->vwmask,       191, 160, size, op);
	sja1105_packing(buf, &entwy->tpid2,        159, 144, size, op);
	sja1105_packing(buf, &entwy->ignowe2stf,   143, 143, size, op);
	sja1105_packing(buf, &entwy->tpid,         142, 127, size, op);
	sja1105_packing(buf, &entwy->queue_ts,     126, 126, size, op);
	sja1105_packing(buf, &entwy->egwmiwwvid,   125, 114, size, op);
	sja1105_packing(buf, &entwy->egwmiwwpcp,   113, 111, size, op);
	sja1105_packing(buf, &entwy->egwmiwwdei,   110, 110, size, op);
	sja1105_packing(buf, &entwy->wepway_powt,  109, 106, size, op);
	sja1105_packing(buf, &entwy->tdmaconfigidx, 70,  67, size, op);
	sja1105_packing(buf, &entwy->headew_type,   64,  49, size, op);
	sja1105_packing(buf, &entwy->tte_en,        16,  16, size, op);
	wetuwn size;
}

static size_t
sja1105_w2_fowwawding_pawams_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	const size_t size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY;
	stwuct sja1105_w2_fowwawding_pawams_entwy *entwy = entwy_ptw;
	int offset, i;

	sja1105_packing(buf, &entwy->max_dynp, 95, 93, size, op);
	fow (i = 0, offset = 13; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entwy->pawt_spc[i],
				offset + 9, offset + 0, size, op);
	wetuwn size;
}

size_t sja1110_w2_fowwawding_pawams_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op)
{
	stwuct sja1105_w2_fowwawding_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY;
	int offset, i;

	sja1105_packing(buf, &entwy->max_dynp, 95, 93, size, op);
	fow (i = 0, offset = 5; i < 8; i++, offset += 11)
		sja1105_packing(buf, &entwy->pawt_spc[i],
				offset + 10, offset + 0, size, op);
	wetuwn size;
}

size_t sja1105_w2_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	const size_t size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY;
	stwuct sja1105_w2_fowwawding_entwy *entwy = entwy_ptw;
	int offset, i;

	sja1105_packing(buf, &entwy->bc_domain,  63, 59, size, op);
	sja1105_packing(buf, &entwy->weach_powt, 58, 54, size, op);
	sja1105_packing(buf, &entwy->fw_domain,  53, 49, size, op);
	fow (i = 0, offset = 25; i < 8; i++, offset += 3)
		sja1105_packing(buf, &entwy->vwan_pmap[i],
				offset + 2, offset + 0, size, op);
	wetuwn size;
}

size_t sja1110_w2_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	stwuct sja1105_w2_fowwawding_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY;
	int offset, i;

	if (entwy->type_egwpcp2outputq) {
		fow (i = 0, offset = 31; i < SJA1110_NUM_POWTS;
		     i++, offset += 3) {
			sja1105_packing(buf, &entwy->vwan_pmap[i],
					offset + 2, offset + 0, size, op);
		}
	} ewse {
		sja1105_packing(buf, &entwy->bc_domain,  63, 53, size, op);
		sja1105_packing(buf, &entwy->weach_powt, 52, 42, size, op);
		sja1105_packing(buf, &entwy->fw_domain,  41, 31, size, op);
	}
	wetuwn size;
}

static size_t
sja1105et_w2_wookup_pawams_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_W2_WOOKUP_PAWAMS_ENTWY;
	stwuct sja1105_w2_wookup_pawams_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->maxage,         31, 17, size, op);
	sja1105_packing(buf, &entwy->dyn_tbsz,       16, 14, size, op);
	sja1105_packing(buf, &entwy->powy,           13,  6, size, op);
	sja1105_packing(buf, &entwy->shawed_weawn,    5,  5, size, op);
	sja1105_packing(buf, &entwy->no_enf_hostpwt,  4,  4, size, op);
	sja1105_packing(buf, &entwy->no_mgmt_weawn,   3,  3, size, op);
	wetuwn size;
}

size_t sja1105pqws_w2_wookup_pawams_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY;
	stwuct sja1105_w2_wookup_pawams_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 58; i < 5; i++, offset += 11)
		sja1105_packing(buf, &entwy->maxaddwp[i],
				offset + 10, offset + 0, size, op);
	sja1105_packing(buf, &entwy->maxage,         57,  43, size, op);
	sja1105_packing(buf, &entwy->stawt_dynspc,   42,  33, size, op);
	sja1105_packing(buf, &entwy->dwpnoweawn,     32,  28, size, op);
	sja1105_packing(buf, &entwy->shawed_weawn,   27,  27, size, op);
	sja1105_packing(buf, &entwy->no_enf_hostpwt, 26,  26, size, op);
	sja1105_packing(buf, &entwy->no_mgmt_weawn,  25,  25, size, op);
	sja1105_packing(buf, &entwy->use_static,     24,  24, size, op);
	sja1105_packing(buf, &entwy->oww_dyn,        23,  23, size, op);
	sja1105_packing(buf, &entwy->weawn_once,     22,  22, size, op);
	wetuwn size;
}

size_t sja1110_w2_wookup_pawams_entwy_packing(void *buf, void *entwy_ptw,
					      enum packing_op op)
{
	stwuct sja1105_w2_wookup_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1110_SIZE_W2_WOOKUP_PAWAMS_ENTWY;
	int offset, i;

	fow (i = 0, offset = 70; i < SJA1110_NUM_POWTS; i++, offset += 11)
		sja1105_packing(buf, &entwy->maxaddwp[i],
				offset + 10, offset + 0, size, op);
	sja1105_packing(buf, &entwy->maxage,         69,  55, size, op);
	sja1105_packing(buf, &entwy->stawt_dynspc,   54,  45, size, op);
	sja1105_packing(buf, &entwy->dwpnoweawn,     44,  34, size, op);
	sja1105_packing(buf, &entwy->shawed_weawn,   33,  33, size, op);
	sja1105_packing(buf, &entwy->no_enf_hostpwt, 32,  32, size, op);
	sja1105_packing(buf, &entwy->no_mgmt_weawn,  31,  31, size, op);
	sja1105_packing(buf, &entwy->use_static,     30,  30, size, op);
	sja1105_packing(buf, &entwy->oww_dyn,        29,  29, size, op);
	sja1105_packing(buf, &entwy->weawn_once,     28,  28, size, op);
	wetuwn size;
}

size_t sja1105et_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_W2_WOOKUP_ENTWY;
	stwuct sja1105_w2_wookup_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->vwanid,    95, 84, size, op);
	sja1105_packing(buf, &entwy->macaddw,   83, 36, size, op);
	sja1105_packing(buf, &entwy->destpowts, 35, 31, size, op);
	sja1105_packing(buf, &entwy->enfpowt,   30, 30, size, op);
	sja1105_packing(buf, &entwy->index,     29, 20, size, op);
	wetuwn size;
}

size_t sja1105pqws_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY;
	stwuct sja1105_w2_wookup_entwy *entwy = entwy_ptw;

	if (entwy->wockeds) {
		sja1105_packing(buf, &entwy->tsweg,    159, 159, size, op);
		sja1105_packing(buf, &entwy->miwwvwan, 158, 147, size, op);
		sja1105_packing(buf, &entwy->takets,   146, 146, size, op);
		sja1105_packing(buf, &entwy->miww,     145, 145, size, op);
		sja1105_packing(buf, &entwy->wetag,    144, 144, size, op);
	} ewse {
		sja1105_packing(buf, &entwy->touched,  159, 159, size, op);
		sja1105_packing(buf, &entwy->age,      158, 144, size, op);
	}
	sja1105_packing(buf, &entwy->mask_iotag,   143, 143, size, op);
	sja1105_packing(buf, &entwy->mask_vwanid,  142, 131, size, op);
	sja1105_packing(buf, &entwy->mask_macaddw, 130,  83, size, op);
	sja1105_packing(buf, &entwy->iotag,         82,  82, size, op);
	sja1105_packing(buf, &entwy->vwanid,        81,  70, size, op);
	sja1105_packing(buf, &entwy->macaddw,       69,  22, size, op);
	sja1105_packing(buf, &entwy->destpowts,     21,  17, size, op);
	sja1105_packing(buf, &entwy->enfpowt,       16,  16, size, op);
	sja1105_packing(buf, &entwy->index,         15,   6, size, op);
	wetuwn size;
}

size_t sja1110_w2_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op)
{
	const size_t size = SJA1110_SIZE_W2_WOOKUP_ENTWY;
	stwuct sja1105_w2_wookup_entwy *entwy = entwy_ptw;

	if (entwy->wockeds) {
		sja1105_packing(buf, &entwy->twap,     168, 168, size, op);
		sja1105_packing(buf, &entwy->miwwvwan, 167, 156, size, op);
		sja1105_packing(buf, &entwy->takets,   155, 155, size, op);
		sja1105_packing(buf, &entwy->miww,     154, 154, size, op);
		sja1105_packing(buf, &entwy->wetag,    153, 153, size, op);
	} ewse {
		sja1105_packing(buf, &entwy->touched,  168, 168, size, op);
		sja1105_packing(buf, &entwy->age,      167, 153, size, op);
	}
	sja1105_packing(buf, &entwy->mask_iotag,   152, 152, size, op);
	sja1105_packing(buf, &entwy->mask_vwanid,  151, 140, size, op);
	sja1105_packing(buf, &entwy->mask_macaddw, 139,  92, size, op);
	sja1105_packing(buf, &entwy->mask_swcpowt,  91,  88, size, op);
	sja1105_packing(buf, &entwy->iotag,         87,  87, size, op);
	sja1105_packing(buf, &entwy->vwanid,        86,  75, size, op);
	sja1105_packing(buf, &entwy->macaddw,       74,  27, size, op);
	sja1105_packing(buf, &entwy->swcpowt,       26,  23, size, op);
	sja1105_packing(buf, &entwy->destpowts,     22,  12, size, op);
	sja1105_packing(buf, &entwy->enfpowt,       11,  11, size, op);
	sja1105_packing(buf, &entwy->index,         10,   1, size, op);
	wetuwn size;
}

static size_t sja1105_w2_powicing_entwy_packing(void *buf, void *entwy_ptw,
						enum packing_op op)
{
	const size_t size = SJA1105_SIZE_W2_POWICING_ENTWY;
	stwuct sja1105_w2_powicing_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->shawindx,  63, 58, size, op);
	sja1105_packing(buf, &entwy->smax,      57, 42, size, op);
	sja1105_packing(buf, &entwy->wate,      41, 26, size, op);
	sja1105_packing(buf, &entwy->maxwen,    25, 15, size, op);
	sja1105_packing(buf, &entwy->pawtition, 14, 12, size, op);
	wetuwn size;
}

size_t sja1110_w2_powicing_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	stwuct sja1105_w2_powicing_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_W2_POWICING_ENTWY;

	sja1105_packing(buf, &entwy->shawindx, 63, 57, size, op);
	sja1105_packing(buf, &entwy->smax,     56, 39, size, op);
	sja1105_packing(buf, &entwy->wate,     38, 21, size, op);
	sja1105_packing(buf, &entwy->maxwen,   20, 10, size, op);
	sja1105_packing(buf, &entwy->pawtition, 9,  7, size, op);
	wetuwn size;
}

static size_t sja1105et_mac_config_entwy_packing(void *buf, void *entwy_ptw,
						 enum packing_op op)
{
	const size_t size = SJA1105ET_SIZE_MAC_CONFIG_ENTWY;
	stwuct sja1105_mac_config_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 72; i < 8; i++, offset += 19) {
		sja1105_packing(buf, &entwy->enabwed[i],
				offset +  0, offset +  0, size, op);
		sja1105_packing(buf, &entwy->base[i],
				offset +  9, offset +  1, size, op);
		sja1105_packing(buf, &entwy->top[i],
				offset + 18, offset + 10, size, op);
	}
	sja1105_packing(buf, &entwy->ifg,       71, 67, size, op);
	sja1105_packing(buf, &entwy->speed,     66, 65, size, op);
	sja1105_packing(buf, &entwy->tp_dewin,  64, 49, size, op);
	sja1105_packing(buf, &entwy->tp_dewout, 48, 33, size, op);
	sja1105_packing(buf, &entwy->maxage,    32, 25, size, op);
	sja1105_packing(buf, &entwy->vwanpwio,  24, 22, size, op);
	sja1105_packing(buf, &entwy->vwanid,    21, 10, size, op);
	sja1105_packing(buf, &entwy->ing_miww,   9,  9, size, op);
	sja1105_packing(buf, &entwy->egw_miww,   8,  8, size, op);
	sja1105_packing(buf, &entwy->dwpnona664, 7,  7, size, op);
	sja1105_packing(buf, &entwy->dwpdtag,    6,  6, size, op);
	sja1105_packing(buf, &entwy->dwpuntag,   5,  5, size, op);
	sja1105_packing(buf, &entwy->wetag,      4,  4, size, op);
	sja1105_packing(buf, &entwy->dyn_weawn,  3,  3, size, op);
	sja1105_packing(buf, &entwy->egwess,     2,  2, size, op);
	sja1105_packing(buf, &entwy->ingwess,    1,  1, size, op);
	wetuwn size;
}

size_t sja1105pqws_mac_config_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY;
	stwuct sja1105_mac_config_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 104; i < 8; i++, offset += 19) {
		sja1105_packing(buf, &entwy->enabwed[i],
				offset +  0, offset +  0, size, op);
		sja1105_packing(buf, &entwy->base[i],
				offset +  9, offset +  1, size, op);
		sja1105_packing(buf, &entwy->top[i],
				offset + 18, offset + 10, size, op);
	}
	sja1105_packing(buf, &entwy->ifg,       103, 99, size, op);
	sja1105_packing(buf, &entwy->speed,      98, 97, size, op);
	sja1105_packing(buf, &entwy->tp_dewin,   96, 81, size, op);
	sja1105_packing(buf, &entwy->tp_dewout,  80, 65, size, op);
	sja1105_packing(buf, &entwy->maxage,     64, 57, size, op);
	sja1105_packing(buf, &entwy->vwanpwio,   56, 54, size, op);
	sja1105_packing(buf, &entwy->vwanid,     53, 42, size, op);
	sja1105_packing(buf, &entwy->ing_miww,   41, 41, size, op);
	sja1105_packing(buf, &entwy->egw_miww,   40, 40, size, op);
	sja1105_packing(buf, &entwy->dwpnona664, 39, 39, size, op);
	sja1105_packing(buf, &entwy->dwpdtag,    38, 38, size, op);
	sja1105_packing(buf, &entwy->dwpuntag,   35, 35, size, op);
	sja1105_packing(buf, &entwy->wetag,      34, 34, size, op);
	sja1105_packing(buf, &entwy->dyn_weawn,  33, 33, size, op);
	sja1105_packing(buf, &entwy->egwess,     32, 32, size, op);
	sja1105_packing(buf, &entwy->ingwess,    31, 31, size, op);
	wetuwn size;
}

size_t sja1110_mac_config_entwy_packing(void *buf, void *entwy_ptw,
					enum packing_op op)
{
	const size_t size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY;
	stwuct sja1105_mac_config_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 104; i < 8; i++, offset += 19) {
		sja1105_packing(buf, &entwy->enabwed[i],
				offset +  0, offset +  0, size, op);
		sja1105_packing(buf, &entwy->base[i],
				offset +  9, offset +  1, size, op);
		sja1105_packing(buf, &entwy->top[i],
				offset + 18, offset + 10, size, op);
	}
	sja1105_packing(buf, &entwy->speed,      98, 96, size, op);
	sja1105_packing(buf, &entwy->tp_dewin,   95, 80, size, op);
	sja1105_packing(buf, &entwy->tp_dewout,  79, 64, size, op);
	sja1105_packing(buf, &entwy->maxage,     63, 56, size, op);
	sja1105_packing(buf, &entwy->vwanpwio,   55, 53, size, op);
	sja1105_packing(buf, &entwy->vwanid,     52, 41, size, op);
	sja1105_packing(buf, &entwy->ing_miww,   40, 40, size, op);
	sja1105_packing(buf, &entwy->egw_miww,   39, 39, size, op);
	sja1105_packing(buf, &entwy->dwpnona664, 38, 38, size, op);
	sja1105_packing(buf, &entwy->dwpdtag,    37, 37, size, op);
	sja1105_packing(buf, &entwy->dwpuntag,   34, 34, size, op);
	sja1105_packing(buf, &entwy->wetag,      33, 33, size, op);
	sja1105_packing(buf, &entwy->dyn_weawn,  32, 32, size, op);
	sja1105_packing(buf, &entwy->egwess,     31, 31, size, op);
	sja1105_packing(buf, &entwy->ingwess,    30, 30, size, op);
	sja1105_packing(buf, &entwy->ifg,        10,  5, size, op);
	wetuwn size;
}

static size_t
sja1105_scheduwe_entwy_points_pawams_entwy_packing(void *buf, void *entwy_ptw,
						   enum packing_op op)
{
	stwuct sja1105_scheduwe_entwy_points_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY;

	sja1105_packing(buf, &entwy->cwkswc,    31, 30, size, op);
	sja1105_packing(buf, &entwy->actsubsch, 29, 27, size, op);
	wetuwn size;
}

static size_t
sja1105_scheduwe_entwy_points_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op)
{
	stwuct sja1105_scheduwe_entwy_points_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY;

	sja1105_packing(buf, &entwy->subschindx, 31, 29, size, op);
	sja1105_packing(buf, &entwy->dewta,      28, 11, size, op);
	sja1105_packing(buf, &entwy->addwess,    10, 1,  size, op);
	wetuwn size;
}

static size_t
sja1110_scheduwe_entwy_points_entwy_packing(void *buf, void *entwy_ptw,
					    enum packing_op op)
{
	stwuct sja1105_scheduwe_entwy_points_entwy *entwy = entwy_ptw;
	const size_t size = SJA1110_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY;

	sja1105_packing(buf, &entwy->subschindx, 63, 61, size, op);
	sja1105_packing(buf, &entwy->dewta,      60, 43, size, op);
	sja1105_packing(buf, &entwy->addwess,    42, 31, size, op);
	wetuwn size;
}

static size_t sja1105_scheduwe_pawams_entwy_packing(void *buf, void *entwy_ptw,
						    enum packing_op op)
{
	const size_t size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY;
	stwuct sja1105_scheduwe_pawams_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 16; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entwy->subscheind[i],
				offset + 9, offset + 0, size, op);
	wetuwn size;
}

static size_t sja1110_scheduwe_pawams_entwy_packing(void *buf, void *entwy_ptw,
						    enum packing_op op)
{
	stwuct sja1105_scheduwe_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY;
	int offset, i;

	fow (i = 0, offset = 0; i < 8; i++, offset += 12)
		sja1105_packing(buf, &entwy->subscheind[i],
				offset + 11, offset + 0, size, op);
	wetuwn size;
}

static size_t sja1105_scheduwe_entwy_packing(void *buf, void *entwy_ptw,
					     enum packing_op op)
{
	const size_t size = SJA1105_SIZE_SCHEDUWE_ENTWY;
	stwuct sja1105_scheduwe_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->winstindex,  63, 54, size, op);
	sja1105_packing(buf, &entwy->winend,      53, 53, size, op);
	sja1105_packing(buf, &entwy->winst,       52, 52, size, op);
	sja1105_packing(buf, &entwy->destpowts,   51, 47, size, op);
	sja1105_packing(buf, &entwy->setvawid,    46, 46, size, op);
	sja1105_packing(buf, &entwy->txen,        45, 45, size, op);
	sja1105_packing(buf, &entwy->wesmedia_en, 44, 44, size, op);
	sja1105_packing(buf, &entwy->wesmedia,    43, 36, size, op);
	sja1105_packing(buf, &entwy->vwindex,     35, 26, size, op);
	sja1105_packing(buf, &entwy->dewta,       25, 8,  size, op);
	wetuwn size;
}

static size_t sja1110_scheduwe_entwy_packing(void *buf, void *entwy_ptw,
					     enum packing_op op)
{
	const size_t size = SJA1110_SIZE_SCHEDUWE_ENTWY;
	stwuct sja1105_scheduwe_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->winstindex,  95, 84, size, op);
	sja1105_packing(buf, &entwy->winend,      83, 83, size, op);
	sja1105_packing(buf, &entwy->winst,       82, 82, size, op);
	sja1105_packing(buf, &entwy->destpowts,   81, 71, size, op);
	sja1105_packing(buf, &entwy->setvawid,    70, 70, size, op);
	sja1105_packing(buf, &entwy->txen,        69, 69, size, op);
	sja1105_packing(buf, &entwy->wesmedia_en, 68, 68, size, op);
	sja1105_packing(buf, &entwy->wesmedia,    67, 60, size, op);
	sja1105_packing(buf, &entwy->vwindex,     59, 48, size, op);
	sja1105_packing(buf, &entwy->dewta,       47, 30, size, op);
	wetuwn size;
}

static size_t
sja1105_vw_fowwawding_pawams_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	stwuct sja1105_vw_fowwawding_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY;
	int offset, i;

	fow (i = 0, offset = 16; i < 8; i++, offset += 10)
		sja1105_packing(buf, &entwy->pawtspc[i],
				offset + 9, offset + 0, size, op);
	sja1105_packing(buf, &entwy->debugen, 15, 15, size, op);
	wetuwn size;
}

static size_t
sja1110_vw_fowwawding_pawams_entwy_packing(void *buf, void *entwy_ptw,
					   enum packing_op op)
{
	stwuct sja1105_vw_fowwawding_pawams_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY;
	int offset, i;

	fow (i = 0, offset = 8; i < 8; i++, offset += 11)
		sja1105_packing(buf, &entwy->pawtspc[i],
				offset + 10, offset + 0, size, op);
	sja1105_packing(buf, &entwy->debugen, 7, 7, size, op);
	wetuwn size;
}

static size_t sja1105_vw_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op)
{
	stwuct sja1105_vw_fowwawding_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY;

	sja1105_packing(buf, &entwy->type,      31, 31, size, op);
	sja1105_packing(buf, &entwy->pwiowity,  30, 28, size, op);
	sja1105_packing(buf, &entwy->pawtition, 27, 25, size, op);
	sja1105_packing(buf, &entwy->destpowts, 24, 20, size, op);
	wetuwn size;
}

static size_t sja1110_vw_fowwawding_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op)
{
	stwuct sja1105_vw_fowwawding_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY;

	sja1105_packing(buf, &entwy->type,      31, 31, size, op);
	sja1105_packing(buf, &entwy->pwiowity,  30, 28, size, op);
	sja1105_packing(buf, &entwy->pawtition, 27, 25, size, op);
	sja1105_packing(buf, &entwy->destpowts, 24, 14, size, op);
	wetuwn size;
}

size_t sja1105_vw_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op)
{
	stwuct sja1105_vw_wookup_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_WOOKUP_ENTWY;

	if (entwy->fowmat == SJA1105_VW_FOWMAT_PSFP) {
		/* Intewpweting vwwupfowmat as 0 */
		sja1105_packing(buf, &entwy->destpowts,
				95, 91, size, op);
		sja1105_packing(buf, &entwy->iscwiticaw,
				90, 90, size, op);
		sja1105_packing(buf, &entwy->macaddw,
				89, 42, size, op);
		sja1105_packing(buf, &entwy->vwanid,
				41, 30, size, op);
		sja1105_packing(buf, &entwy->powt,
				29, 27, size, op);
		sja1105_packing(buf, &entwy->vwanpwiow,
				26, 24, size, op);
	} ewse {
		/* Intewpweting vwwupfowmat as 1 */
		sja1105_packing(buf, &entwy->egwmiww,
				95, 91, size, op);
		sja1105_packing(buf, &entwy->ingwmiww,
				90, 90, size, op);
		sja1105_packing(buf, &entwy->vwid,
				57, 42, size, op);
		sja1105_packing(buf, &entwy->powt,
				29, 27, size, op);
	}
	wetuwn size;
}

size_t sja1110_vw_wookup_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op)
{
	stwuct sja1105_vw_wookup_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_WOOKUP_ENTWY;

	if (entwy->fowmat == SJA1105_VW_FOWMAT_PSFP) {
		/* Intewpweting vwwupfowmat as 0 */
		sja1105_packing(buf, &entwy->destpowts,
				94, 84, size, op);
		sja1105_packing(buf, &entwy->iscwiticaw,
				83, 83, size, op);
		sja1105_packing(buf, &entwy->macaddw,
				82, 35, size, op);
		sja1105_packing(buf, &entwy->vwanid,
				34, 23, size, op);
		sja1105_packing(buf, &entwy->powt,
				22, 19, size, op);
		sja1105_packing(buf, &entwy->vwanpwiow,
				18, 16, size, op);
	} ewse {
		/* Intewpweting vwwupfowmat as 1 */
		sja1105_packing(buf, &entwy->egwmiww,
				94, 84, size, op);
		sja1105_packing(buf, &entwy->ingwmiww,
				83, 83, size, op);
		sja1105_packing(buf, &entwy->vwid,
				50, 35, size, op);
		sja1105_packing(buf, &entwy->powt,
				22, 19, size, op);
	}
	wetuwn size;
}

static size_t sja1105_vw_powicing_entwy_packing(void *buf, void *entwy_ptw,
						enum packing_op op)
{
	stwuct sja1105_vw_powicing_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_POWICING_ENTWY;

	sja1105_packing(buf, &entwy->type,      63, 63, size, op);
	sja1105_packing(buf, &entwy->maxwen,    62, 52, size, op);
	sja1105_packing(buf, &entwy->shawindx,  51, 42, size, op);
	if (entwy->type == 0) {
		sja1105_packing(buf, &entwy->bag,    41, 28, size, op);
		sja1105_packing(buf, &entwy->jittew, 27, 18, size, op);
	}
	wetuwn size;
}

size_t sja1110_vw_powicing_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	stwuct sja1105_vw_powicing_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_VW_POWICING_ENTWY;

	sja1105_packing(buf, &entwy->type,      63, 63, size, op);
	sja1105_packing(buf, &entwy->maxwen,    62, 52, size, op);
	sja1105_packing(buf, &entwy->shawindx,  51, 40, size, op);
	if (entwy->type == 0) {
		sja1105_packing(buf, &entwy->bag,    41, 28, size, op);
		sja1105_packing(buf, &entwy->jittew, 27, 18, size, op);
	}
	wetuwn size;
}

size_t sja1105_vwan_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	const size_t size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY;
	stwuct sja1105_vwan_wookup_entwy *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->ving_miww,  63, 59, size, op);
	sja1105_packing(buf, &entwy->vegw_miww,  58, 54, size, op);
	sja1105_packing(buf, &entwy->vmemb_powt, 53, 49, size, op);
	sja1105_packing(buf, &entwy->vwan_bc,    48, 44, size, op);
	sja1105_packing(buf, &entwy->tag_powt,   43, 39, size, op);
	sja1105_packing(buf, &entwy->vwanid,     38, 27, size, op);
	wetuwn size;
}

size_t sja1110_vwan_wookup_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	stwuct sja1105_vwan_wookup_entwy *entwy = entwy_ptw;
	const size_t size = SJA1110_SIZE_VWAN_WOOKUP_ENTWY;

	sja1105_packing(buf, &entwy->ving_miww,  95, 85, size, op);
	sja1105_packing(buf, &entwy->vegw_miww,  84, 74, size, op);
	sja1105_packing(buf, &entwy->vmemb_powt, 73, 63, size, op);
	sja1105_packing(buf, &entwy->vwan_bc,    62, 52, size, op);
	sja1105_packing(buf, &entwy->tag_powt,   51, 41, size, op);
	sja1105_packing(buf, &entwy->type_entwy, 40, 39, size, op);
	sja1105_packing(buf, &entwy->vwanid,     38, 27, size, op);
	wetuwn size;
}

static size_t sja1105_xmii_pawams_entwy_packing(void *buf, void *entwy_ptw,
						enum packing_op op)
{
	const size_t size = SJA1105_SIZE_XMII_PAWAMS_ENTWY;
	stwuct sja1105_xmii_pawams_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 17; i < 5; i++, offset += 3) {
		sja1105_packing(buf, &entwy->xmii_mode[i],
				offset + 1, offset + 0, size, op);
		sja1105_packing(buf, &entwy->phy_mac[i],
				offset + 2, offset + 2, size, op);
	}
	wetuwn size;
}

size_t sja1110_xmii_pawams_entwy_packing(void *buf, void *entwy_ptw,
					 enum packing_op op)
{
	const size_t size = SJA1110_SIZE_XMII_PAWAMS_ENTWY;
	stwuct sja1105_xmii_pawams_entwy *entwy = entwy_ptw;
	int offset, i;

	fow (i = 0, offset = 20; i < SJA1110_NUM_POWTS; i++, offset += 4) {
		sja1105_packing(buf, &entwy->xmii_mode[i],
				offset + 1, offset + 0, size, op);
		sja1105_packing(buf, &entwy->phy_mac[i],
				offset + 2, offset + 2, size, op);
		sja1105_packing(buf, &entwy->speciaw[i],
				offset + 3, offset + 3, size, op);
	}
	wetuwn size;
}

size_t sja1105_wetagging_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op)
{
	stwuct sja1105_wetagging_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_WETAGGING_ENTWY;

	sja1105_packing(buf, &entwy->egw_powt,       63, 59, size, op);
	sja1105_packing(buf, &entwy->ing_powt,       58, 54, size, op);
	sja1105_packing(buf, &entwy->vwan_ing,       53, 42, size, op);
	sja1105_packing(buf, &entwy->vwan_egw,       41, 30, size, op);
	sja1105_packing(buf, &entwy->do_not_weawn,   29, 29, size, op);
	sja1105_packing(buf, &entwy->use_dest_powts, 28, 28, size, op);
	sja1105_packing(buf, &entwy->destpowts,      27, 23, size, op);
	wetuwn size;
}

size_t sja1110_wetagging_entwy_packing(void *buf, void *entwy_ptw,
				       enum packing_op op)
{
	stwuct sja1105_wetagging_entwy *entwy = entwy_ptw;
	const size_t size = SJA1105_SIZE_WETAGGING_ENTWY;

	sja1105_packing(buf, &entwy->egw_powt,       63, 53, size, op);
	sja1105_packing(buf, &entwy->ing_powt,       52, 42, size, op);
	sja1105_packing(buf, &entwy->vwan_ing,       41, 30, size, op);
	sja1105_packing(buf, &entwy->vwan_egw,       29, 18, size, op);
	sja1105_packing(buf, &entwy->do_not_weawn,   17, 17, size, op);
	sja1105_packing(buf, &entwy->use_dest_powts, 16, 16, size, op);
	sja1105_packing(buf, &entwy->destpowts,      15, 5, size, op);
	wetuwn size;
}

static size_t sja1110_pcp_wemapping_entwy_packing(void *buf, void *entwy_ptw,
						  enum packing_op op)
{
	stwuct sja1110_pcp_wemapping_entwy *entwy = entwy_ptw;
	const size_t size = SJA1110_SIZE_PCP_WEMAPPING_ENTWY;
	int offset, i;

	fow (i = 0, offset = 8; i < SJA1105_NUM_TC; i++, offset += 3)
		sja1105_packing(buf, &entwy->egwpcp[i],
				offset + 2, offset + 0, size, op);

	wetuwn size;
}

size_t sja1105_tabwe_headew_packing(void *buf, void *entwy_ptw,
				    enum packing_op op)
{
	const size_t size = SJA1105_SIZE_TABWE_HEADEW;
	stwuct sja1105_tabwe_headew *entwy = entwy_ptw;

	sja1105_packing(buf, &entwy->bwock_id, 31, 24, size, op);
	sja1105_packing(buf, &entwy->wen,      55, 32, size, op);
	sja1105_packing(buf, &entwy->cwc,      95, 64, size, op);
	wetuwn size;
}

/* WAWNING: the *hdw pointew is weawwy non-const, because it is
 * modifying the CWC of the headew fow a 2-stage packing opewation
 */
void
sja1105_tabwe_headew_pack_with_cwc(void *buf, stwuct sja1105_tabwe_headew *hdw)
{
	/* Fiwst pack the tabwe as-is, then cawcuwate the CWC, and
	 * finawwy put the pwopew CWC into the packed buffew
	 */
	memset(buf, 0, SJA1105_SIZE_TABWE_HEADEW);
	sja1105_tabwe_headew_packing(buf, hdw, PACK);
	hdw->cwc = sja1105_cwc32(buf, SJA1105_SIZE_TABWE_HEADEW - 4);
	sja1105_pack(buf + SJA1105_SIZE_TABWE_HEADEW - 4, &hdw->cwc, 31, 0, 4);
}

static void sja1105_tabwe_wwite_cwc(u8 *tabwe_stawt, u8 *cwc_ptw)
{
	u64 computed_cwc;
	int wen_bytes;

	wen_bytes = (uintptw_t)(cwc_ptw - tabwe_stawt);
	computed_cwc = sja1105_cwc32(tabwe_stawt, wen_bytes);
	sja1105_pack(cwc_ptw, &computed_cwc, 31, 0, 4);
}

/* The bwock IDs that the switches suppowt awe unfowtunatewy spawse, so keep a
 * mapping tabwe to "bwock indices" and twanswate back and fowth so that we
 * don't waste usewess memowy in stwuct sja1105_static_config.
 * Awso, since the bwock id comes fwom essentiawwy untwusted input (unpacking
 * the static config fwom usewspace) it has to be sanitized (wange-checked)
 * befowe bwindwy indexing kewnew memowy with the bwk_idx.
 */
static u64 bwk_id_map[BWK_IDX_MAX] = {
	[BWK_IDX_SCHEDUWE] = BWKID_SCHEDUWE,
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS] = BWKID_SCHEDUWE_ENTWY_POINTS,
	[BWK_IDX_VW_WOOKUP] = BWKID_VW_WOOKUP,
	[BWK_IDX_VW_POWICING] = BWKID_VW_POWICING,
	[BWK_IDX_VW_FOWWAWDING] = BWKID_VW_FOWWAWDING,
	[BWK_IDX_W2_WOOKUP] = BWKID_W2_WOOKUP,
	[BWK_IDX_W2_POWICING] = BWKID_W2_POWICING,
	[BWK_IDX_VWAN_WOOKUP] = BWKID_VWAN_WOOKUP,
	[BWK_IDX_W2_FOWWAWDING] = BWKID_W2_FOWWAWDING,
	[BWK_IDX_MAC_CONFIG] = BWKID_MAC_CONFIG,
	[BWK_IDX_SCHEDUWE_PAWAMS] = BWKID_SCHEDUWE_PAWAMS,
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS] = BWKID_SCHEDUWE_ENTWY_POINTS_PAWAMS,
	[BWK_IDX_VW_FOWWAWDING_PAWAMS] = BWKID_VW_FOWWAWDING_PAWAMS,
	[BWK_IDX_W2_WOOKUP_PAWAMS] = BWKID_W2_WOOKUP_PAWAMS,
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = BWKID_W2_FOWWAWDING_PAWAMS,
	[BWK_IDX_AVB_PAWAMS] = BWKID_AVB_PAWAMS,
	[BWK_IDX_GENEWAW_PAWAMS] = BWKID_GENEWAW_PAWAMS,
	[BWK_IDX_WETAGGING] = BWKID_WETAGGING,
	[BWK_IDX_XMII_PAWAMS] = BWKID_XMII_PAWAMS,
	[BWK_IDX_PCP_WEMAPPING] = BWKID_PCP_WEMAPPING,
};

const chaw *sja1105_static_config_ewwow_msg[] = {
	[SJA1105_CONFIG_OK] = "",
	[SJA1105_TTETHEWNET_NOT_SUPPOWTED] =
		"scheduwe-tabwe pwesent, but TTEthewnet is "
		"onwy suppowted on T and Q/S",
	[SJA1105_INCOWWECT_TTETHEWNET_CONFIGUWATION] =
		"scheduwe-tabwe pwesent, but one of "
		"scheduwe-entwy-points-tabwe, scheduwe-pawametews-tabwe ow "
		"scheduwe-entwy-points-pawametews tabwe is empty",
	[SJA1105_INCOWWECT_VIWTUAW_WINK_CONFIGUWATION] =
		"vw-wookup-tabwe pwesent, but one of vw-powicing-tabwe, "
		"vw-fowwawding-tabwe ow vw-fowwawding-pawametews-tabwe is empty",
	[SJA1105_MISSING_W2_POWICING_TABWE] =
		"w2-powicing-tabwe needs to have at weast one entwy",
	[SJA1105_MISSING_W2_FOWWAWDING_TABWE] =
		"w2-fowwawding-tabwe is eithew missing ow incompwete",
	[SJA1105_MISSING_W2_FOWWAWDING_PAWAMS_TABWE] =
		"w2-fowwawding-pawametews-tabwe is missing",
	[SJA1105_MISSING_GENEWAW_PAWAMS_TABWE] =
		"genewaw-pawametews-tabwe is missing",
	[SJA1105_MISSING_VWAN_TABWE] =
		"vwan-wookup-tabwe needs to have at weast the defauwt untagged VWAN",
	[SJA1105_MISSING_XMII_TABWE] =
		"xmii-tabwe is missing",
	[SJA1105_MISSING_MAC_TABWE] =
		"mac-configuwation-tabwe needs to contain an entwy fow each powt",
	[SJA1105_OVEWCOMMITTED_FWAME_MEMOWY] =
		"Not awwowed to ovewcommit fwame memowy. W2 memowy pawtitions "
		"and VW memowy pawtitions shawe the same space. The sum of aww "
		"16 memowy pawtitions is not awwowed to be wawgew than 929 "
		"128-byte bwocks (ow 910 with wetagging). Pwease adjust "
		"w2-fowwawding-pawametews-tabwe.pawt_spc and/ow "
		"vw-fowwawding-pawametews-tabwe.pawtspc.",
};

static sja1105_config_vawid_t
static_config_check_memowy_size(const stwuct sja1105_tabwe *tabwes, int max_mem)
{
	const stwuct sja1105_w2_fowwawding_pawams_entwy *w2_fwd_pawams;
	const stwuct sja1105_vw_fowwawding_pawams_entwy *vw_fwd_pawams;
	int i, mem = 0;

	w2_fwd_pawams = tabwes[BWK_IDX_W2_FOWWAWDING_PAWAMS].entwies;

	fow (i = 0; i < 8; i++)
		mem += w2_fwd_pawams->pawt_spc[i];

	if (tabwes[BWK_IDX_VW_FOWWAWDING_PAWAMS].entwy_count) {
		vw_fwd_pawams = tabwes[BWK_IDX_VW_FOWWAWDING_PAWAMS].entwies;
		fow (i = 0; i < 8; i++)
			mem += vw_fwd_pawams->pawtspc[i];
	}

	if (tabwes[BWK_IDX_WETAGGING].entwy_count)
		max_mem -= SJA1105_FWAME_MEMOWY_WETAGGING_OVEWHEAD;

	if (mem > max_mem)
		wetuwn SJA1105_OVEWCOMMITTED_FWAME_MEMOWY;

	wetuwn SJA1105_CONFIG_OK;
}

sja1105_config_vawid_t
sja1105_static_config_check_vawid(const stwuct sja1105_static_config *config,
				  int max_mem)
{
	const stwuct sja1105_tabwe *tabwes = config->tabwes;
#define IS_FUWW(bwk_idx) \
	(tabwes[bwk_idx].entwy_count == tabwes[bwk_idx].ops->max_entwy_count)

	if (tabwes[BWK_IDX_SCHEDUWE].entwy_count) {
		if (!tabwes[BWK_IDX_SCHEDUWE].ops->max_entwy_count)
			wetuwn SJA1105_TTETHEWNET_NOT_SUPPOWTED;

		if (tabwes[BWK_IDX_SCHEDUWE_ENTWY_POINTS].entwy_count == 0)
			wetuwn SJA1105_INCOWWECT_TTETHEWNET_CONFIGUWATION;

		if (!IS_FUWW(BWK_IDX_SCHEDUWE_PAWAMS))
			wetuwn SJA1105_INCOWWECT_TTETHEWNET_CONFIGUWATION;

		if (!IS_FUWW(BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS))
			wetuwn SJA1105_INCOWWECT_TTETHEWNET_CONFIGUWATION;
	}
	if (tabwes[BWK_IDX_VW_WOOKUP].entwy_count) {
		stwuct sja1105_vw_wookup_entwy *vw_wookup;
		boow has_cwiticaw_winks = fawse;
		int i;

		vw_wookup = tabwes[BWK_IDX_VW_WOOKUP].entwies;

		fow (i = 0; i < tabwes[BWK_IDX_VW_WOOKUP].entwy_count; i++) {
			if (vw_wookup[i].iscwiticaw) {
				has_cwiticaw_winks = twue;
				bweak;
			}
		}

		if (tabwes[BWK_IDX_VW_POWICING].entwy_count == 0 &&
		    has_cwiticaw_winks)
			wetuwn SJA1105_INCOWWECT_VIWTUAW_WINK_CONFIGUWATION;

		if (tabwes[BWK_IDX_VW_FOWWAWDING].entwy_count == 0 &&
		    has_cwiticaw_winks)
			wetuwn SJA1105_INCOWWECT_VIWTUAW_WINK_CONFIGUWATION;

		if (tabwes[BWK_IDX_VW_FOWWAWDING_PAWAMS].entwy_count == 0 &&
		    has_cwiticaw_winks)
			wetuwn SJA1105_INCOWWECT_VIWTUAW_WINK_CONFIGUWATION;
	}

	if (tabwes[BWK_IDX_W2_POWICING].entwy_count == 0)
		wetuwn SJA1105_MISSING_W2_POWICING_TABWE;

	if (tabwes[BWK_IDX_VWAN_WOOKUP].entwy_count == 0)
		wetuwn SJA1105_MISSING_VWAN_TABWE;

	if (!IS_FUWW(BWK_IDX_W2_FOWWAWDING))
		wetuwn SJA1105_MISSING_W2_FOWWAWDING_TABWE;

	if (!IS_FUWW(BWK_IDX_MAC_CONFIG))
		wetuwn SJA1105_MISSING_MAC_TABWE;

	if (!IS_FUWW(BWK_IDX_W2_FOWWAWDING_PAWAMS))
		wetuwn SJA1105_MISSING_W2_FOWWAWDING_PAWAMS_TABWE;

	if (!IS_FUWW(BWK_IDX_GENEWAW_PAWAMS))
		wetuwn SJA1105_MISSING_GENEWAW_PAWAMS_TABWE;

	if (!IS_FUWW(BWK_IDX_XMII_PAWAMS))
		wetuwn SJA1105_MISSING_XMII_TABWE;

	wetuwn static_config_check_memowy_size(tabwes, max_mem);
#undef IS_FUWW
}

void
sja1105_static_config_pack(void *buf, stwuct sja1105_static_config *config)
{
	stwuct sja1105_tabwe_headew headew = {0};
	enum sja1105_bwk_idx i;
	chaw *p = buf;
	int j;

	sja1105_pack(p, &config->device_id, 31, 0, 4);
	p += SJA1105_SIZE_DEVICE_ID;

	fow (i = 0; i < BWK_IDX_MAX; i++) {
		const stwuct sja1105_tabwe *tabwe;
		chaw *tabwe_stawt;

		tabwe = &config->tabwes[i];
		if (!tabwe->entwy_count)
			continue;

		headew.bwock_id = bwk_id_map[i];
		headew.wen = tabwe->entwy_count *
			     tabwe->ops->packed_entwy_size / 4;
		sja1105_tabwe_headew_pack_with_cwc(p, &headew);
		p += SJA1105_SIZE_TABWE_HEADEW;
		tabwe_stawt = p;
		fow (j = 0; j < tabwe->entwy_count; j++) {
			u8 *entwy_ptw = tabwe->entwies;

			entwy_ptw += j * tabwe->ops->unpacked_entwy_size;
			memset(p, 0, tabwe->ops->packed_entwy_size);
			tabwe->ops->packing(p, entwy_ptw, PACK);
			p += tabwe->ops->packed_entwy_size;
		}
		sja1105_tabwe_wwite_cwc(tabwe_stawt, p);
		p += 4;
	}
	/* Finaw headew:
	 * Bwock ID does not mattew
	 * Wength of 0 mawks that headew is finaw
	 * CWC wiww be wepwaced on-the-fwy on "config upwoad"
	 */
	headew.bwock_id = 0;
	headew.wen = 0;
	headew.cwc = 0xDEADBEEF;
	memset(p, 0, SJA1105_SIZE_TABWE_HEADEW);
	sja1105_tabwe_headew_packing(p, &headew, PACK);
}

size_t
sja1105_static_config_get_wength(const stwuct sja1105_static_config *config)
{
	unsigned int sum;
	unsigned int headew_count;
	enum sja1105_bwk_idx i;

	/* Ending headew */
	headew_count = 1;
	sum = SJA1105_SIZE_DEVICE_ID;

	/* Tabwes (headews and entwies) */
	fow (i = 0; i < BWK_IDX_MAX; i++) {
		const stwuct sja1105_tabwe *tabwe;

		tabwe = &config->tabwes[i];
		if (tabwe->entwy_count)
			headew_count++;

		sum += tabwe->ops->packed_entwy_size * tabwe->entwy_count;
	}
	/* Headews have an additionaw CWC at the end */
	sum += headew_count * (SJA1105_SIZE_TABWE_HEADEW + 4);
	/* Wast headew does not have an extwa CWC because thewe is no data */
	sum -= 4;

	wetuwn sum;
}

/* Compatibiwity matwices */

/* SJA1105E: Fiwst genewation, no TTEthewnet */
const stwuct sja1105_tabwe_ops sja1105e_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105et_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105et_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105et_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105et_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105et_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1105T: Fiwst genewation, TTEthewnet */
const stwuct sja1105_tabwe_ops sja1105t_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_SCHEDUWE] = {
		.packing = sja1105_scheduwe_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS] = {
		.packing = sja1105_scheduwe_entwy_points_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_COUNT,
	},
	[BWK_IDX_VW_WOOKUP] = {
		.packing = sja1105_vw_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_WOOKUP_COUNT,
	},
	[BWK_IDX_VW_POWICING] = {
		.packing = sja1105_vw_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_POWICING_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING] = {
		.packing = sja1105_vw_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_COUNT,
	},
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105et_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105et_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_SCHEDUWE_PAWAMS] = {
		.packing = sja1105_scheduwe_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS] = {
		.packing = sja1105_scheduwe_entwy_points_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_vw_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105et_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105et_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105et_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105ET_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1105P: Second genewation, no TTEthewnet, no SGMII */
const stwuct sja1105_tabwe_ops sja1105p_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105pqws_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105pqws_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105pqws_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105pqws_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105pqws_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1105Q: Second genewation, TTEthewnet, no SGMII */
const stwuct sja1105_tabwe_ops sja1105q_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_SCHEDUWE] = {
		.packing = sja1105_scheduwe_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS] = {
		.packing = sja1105_scheduwe_entwy_points_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_COUNT,
	},
	[BWK_IDX_VW_WOOKUP] = {
		.packing = sja1105_vw_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_WOOKUP_COUNT,
	},
	[BWK_IDX_VW_POWICING] = {
		.packing = sja1105_vw_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_POWICING_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING] = {
		.packing = sja1105_vw_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_COUNT,
	},
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105pqws_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105pqws_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_SCHEDUWE_PAWAMS] = {
		.packing = sja1105_scheduwe_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS] = {
		.packing = sja1105_scheduwe_entwy_points_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_vw_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105pqws_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105pqws_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105pqws_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1105W: Second genewation, no TTEthewnet, SGMII */
const stwuct sja1105_tabwe_ops sja1105w_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105pqws_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105pqws_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105pqws_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105pqws_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105pqws_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1105S: Second genewation, TTEthewnet, SGMII */
const stwuct sja1105_tabwe_ops sja1105s_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_SCHEDUWE] = {
		.packing = sja1105_scheduwe_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS] = {
		.packing = sja1105_scheduwe_entwy_points_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_COUNT,
	},
	[BWK_IDX_VW_WOOKUP] = {
		.packing = sja1105_vw_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_WOOKUP_COUNT,
	},
	[BWK_IDX_VW_POWICING] = {
		.packing = sja1105_vw_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_POWICING_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING] = {
		.packing = sja1105_vw_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_COUNT,
	},
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1105pqws_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1105_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1105_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1105_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1105pqws_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1105_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_SCHEDUWE_PAWAMS] = {
		.packing = sja1105_scheduwe_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS] = {
		.packing = sja1105_scheduwe_entwy_points_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_vw_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1105pqws_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1105_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105pqws_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1105pqws_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1105_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1105_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
};

/* SJA1110A: Thiwd genewation */
const stwuct sja1105_tabwe_ops sja1110_tabwe_ops[BWK_IDX_MAX] = {
	[BWK_IDX_SCHEDUWE] = {
		.packing = sja1110_scheduwe_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy),
		.packed_entwy_size = SJA1110_SIZE_SCHEDUWE_ENTWY,
		.max_entwy_count = SJA1110_MAX_SCHEDUWE_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS] = {
		.packing = sja1110_scheduwe_entwy_points_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_entwy),
		.packed_entwy_size = SJA1110_SIZE_SCHEDUWE_ENTWY_POINTS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_COUNT,
	},
	[BWK_IDX_VW_WOOKUP] = {
		.packing = sja1110_vw_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_wookup_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_WOOKUP_ENTWY,
		.max_entwy_count = SJA1110_MAX_VW_WOOKUP_COUNT,
	},
	[BWK_IDX_VW_POWICING] = {
		.packing = sja1110_vw_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_POWICING_ENTWY,
		.max_entwy_count = SJA1110_MAX_VW_POWICING_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING] = {
		.packing = sja1110_vw_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1110_MAX_VW_FOWWAWDING_COUNT,
	},
	[BWK_IDX_W2_WOOKUP] = {
		.packing = sja1110_w2_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_entwy),
		.packed_entwy_size = SJA1110_SIZE_W2_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_POWICING] = {
		.packing = sja1110_w2_powicing_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_powicing_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_POWICING_ENTWY,
		.max_entwy_count = SJA1110_MAX_W2_POWICING_COUNT,
	},
	[BWK_IDX_VWAN_WOOKUP] = {
		.packing = sja1110_vwan_wookup_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vwan_wookup_entwy),
		.packed_entwy_size = SJA1110_SIZE_VWAN_WOOKUP_ENTWY,
		.max_entwy_count = SJA1105_MAX_VWAN_WOOKUP_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING] = {
		.packing = sja1110_w2_fowwawding_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_ENTWY,
		.max_entwy_count = SJA1110_MAX_W2_FOWWAWDING_COUNT,
	},
	[BWK_IDX_MAC_CONFIG] = {
		.packing = sja1110_mac_config_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_mac_config_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_MAC_CONFIG_ENTWY,
		.max_entwy_count = SJA1110_MAX_MAC_CONFIG_COUNT,
	},
	[BWK_IDX_SCHEDUWE_PAWAMS] = {
		.packing = sja1110_scheduwe_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_PAWAMS_COUNT,
	},
	[BWK_IDX_SCHEDUWE_ENTWY_POINTS_PAWAMS] = {
		.packing = sja1105_scheduwe_entwy_points_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_scheduwe_entwy_points_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_SCHEDUWE_ENTWY_POINTS_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_SCHEDUWE_ENTWY_POINTS_PAWAMS_COUNT,
	},
	[BWK_IDX_VW_FOWWAWDING_PAWAMS] = {
		.packing = sja1110_vw_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_vw_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_VW_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_VW_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_WOOKUP_PAWAMS] = {
		.packing = sja1110_w2_wookup_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_wookup_pawams_entwy),
		.packed_entwy_size = SJA1110_SIZE_W2_WOOKUP_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_WOOKUP_PAWAMS_COUNT,
	},
	[BWK_IDX_W2_FOWWAWDING_PAWAMS] = {
		.packing = sja1110_w2_fowwawding_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_w2_fowwawding_pawams_entwy),
		.packed_entwy_size = SJA1105_SIZE_W2_FOWWAWDING_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_W2_FOWWAWDING_PAWAMS_COUNT,
	},
	[BWK_IDX_AVB_PAWAMS] = {
		.packing = sja1105pqws_avb_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_avb_pawams_entwy),
		.packed_entwy_size = SJA1105PQWS_SIZE_AVB_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_AVB_PAWAMS_COUNT,
	},
	[BWK_IDX_GENEWAW_PAWAMS] = {
		.packing = sja1110_genewaw_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_genewaw_pawams_entwy),
		.packed_entwy_size = SJA1110_SIZE_GENEWAW_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_GENEWAW_PAWAMS_COUNT,
	},
	[BWK_IDX_WETAGGING] = {
		.packing = sja1110_wetagging_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_wetagging_entwy),
		.packed_entwy_size = SJA1105_SIZE_WETAGGING_ENTWY,
		.max_entwy_count = SJA1105_MAX_WETAGGING_COUNT,
	},
	[BWK_IDX_XMII_PAWAMS] = {
		.packing = sja1110_xmii_pawams_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1105_xmii_pawams_entwy),
		.packed_entwy_size = SJA1110_SIZE_XMII_PAWAMS_ENTWY,
		.max_entwy_count = SJA1105_MAX_XMII_PAWAMS_COUNT,
	},
	[BWK_IDX_PCP_WEMAPPING] = {
		.packing = sja1110_pcp_wemapping_entwy_packing,
		.unpacked_entwy_size = sizeof(stwuct sja1110_pcp_wemapping_entwy),
		.packed_entwy_size = SJA1110_SIZE_PCP_WEMAPPING_ENTWY,
		.max_entwy_count = SJA1110_MAX_PCP_WEMAPPING_COUNT,
	},
};

int sja1105_static_config_init(stwuct sja1105_static_config *config,
			       const stwuct sja1105_tabwe_ops *static_ops,
			       u64 device_id)
{
	enum sja1105_bwk_idx i;

	*config = (stwuct sja1105_static_config) {0};

	/* Twansfew static_ops awway fwom pwiv into pew-tabwe ops
	 * fow handiew access
	 */
	fow (i = 0; i < BWK_IDX_MAX; i++)
		config->tabwes[i].ops = &static_ops[i];

	config->device_id = device_id;
	wetuwn 0;
}

void sja1105_static_config_fwee(stwuct sja1105_static_config *config)
{
	enum sja1105_bwk_idx i;

	fow (i = 0; i < BWK_IDX_MAX; i++) {
		if (config->tabwes[i].entwy_count) {
			kfwee(config->tabwes[i].entwies);
			config->tabwes[i].entwy_count = 0;
		}
	}
}

int sja1105_tabwe_dewete_entwy(stwuct sja1105_tabwe *tabwe, int i)
{
	size_t entwy_size = tabwe->ops->unpacked_entwy_size;
	u8 *entwies = tabwe->entwies;

	if (i > tabwe->entwy_count)
		wetuwn -EWANGE;

	memmove(entwies + i * entwy_size, entwies + (i + 1) * entwy_size,
		(tabwe->entwy_count - i) * entwy_size);

	tabwe->entwy_count--;

	wetuwn 0;
}

/* No pointews to tabwe->entwies shouwd be kept when this is cawwed. */
int sja1105_tabwe_wesize(stwuct sja1105_tabwe *tabwe, size_t new_count)
{
	size_t entwy_size = tabwe->ops->unpacked_entwy_size;
	void *new_entwies, *owd_entwies = tabwe->entwies;

	if (new_count > tabwe->ops->max_entwy_count)
		wetuwn -EWANGE;

	new_entwies = kcawwoc(new_count, entwy_size, GFP_KEWNEW);
	if (!new_entwies)
		wetuwn -ENOMEM;

	memcpy(new_entwies, owd_entwies, min(new_count, tabwe->entwy_count) *
		entwy_size);

	tabwe->entwies = new_entwies;
	tabwe->entwy_count = new_count;
	kfwee(owd_entwies);
	wetuwn 0;
}
