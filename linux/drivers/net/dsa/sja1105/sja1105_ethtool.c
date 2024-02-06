// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude "sja1105.h"

enum sja1105_countew_index {
	__SJA1105_COUNTEW_UNUSED,
	/* MAC */
	N_WUNT,
	N_SOFEWW,
	N_AWIGNEWW,
	N_MIIEWW,
	TYPEEWW,
	SIZEEWW,
	TCTIMEOUT,
	PWIOWEWW,
	NOMASTEW,
	MEMOV,
	MEMEWW,
	INVTYP,
	INTCYOV,
	DOMEWW,
	PCFBAGDWOP,
	SPCPWIOW,
	AGEPWIOW,
	POWTDWOP,
	WENDWOP,
	BAGDWOP,
	POWICEEWW,
	DWPNONA664EWW,
	SPCEWW,
	AGEDWP,
	/* HW1 */
	N_N664EWW,
	N_VWANEWW,
	N_UNWEWEASED,
	N_SIZEEWW,
	N_CWCEWW,
	N_VWNOTFOUND,
	N_CTPOWEWW,
	N_POWEWW,
	N_WXFWM,
	N_WXBYTE,
	N_TXFWM,
	N_TXBYTE,
	/* HW2 */
	N_QFUWW,
	N_PAWT_DWOP,
	N_EGW_DISABWED,
	N_NOT_WEACH,
	__MAX_SJA1105ET_POWT_COUNTEW,
	/* P/Q/W/S onwy */
	/* ETHEW */
	N_DWOPS_NOWEAWN = __MAX_SJA1105ET_POWT_COUNTEW,
	N_DWOPS_NOWOUTE,
	N_DWOPS_IWW_DTAG,
	N_DWOPS_DTAG,
	N_DWOPS_SOTAG,
	N_DWOPS_SITAG,
	N_DWOPS_UTAG,
	N_TX_BYTES_1024_2047,
	N_TX_BYTES_512_1023,
	N_TX_BYTES_256_511,
	N_TX_BYTES_128_255,
	N_TX_BYTES_65_127,
	N_TX_BYTES_64,
	N_TX_MCAST,
	N_TX_BCAST,
	N_WX_BYTES_1024_2047,
	N_WX_BYTES_512_1023,
	N_WX_BYTES_256_511,
	N_WX_BYTES_128_255,
	N_WX_BYTES_65_127,
	N_WX_BYTES_64,
	N_WX_MCAST,
	N_WX_BCAST,
	__MAX_SJA1105PQWS_POWT_COUNTEW,
};

stwuct sja1105_powt_countew {
	enum sja1105_stats_awea awea;
	const chaw name[ETH_GSTWING_WEN];
	int offset;
	int stawt;
	int end;
	boow is_64bit;
};

static const stwuct sja1105_powt_countew sja1105_powt_countews[] = {
	/* MAC-Wevew Diagnostic Countews */
	[N_WUNT] = {
		.awea = MAC,
		.name = "n_wunt",
		.offset = 0,
		.stawt = 31,
		.end = 24,
	},
	[N_SOFEWW] = {
		.awea = MAC,
		.name = "n_sofeww",
		.offset = 0x0,
		.stawt = 23,
		.end = 16,
	},
	[N_AWIGNEWW] = {
		.awea = MAC,
		.name = "n_awigneww",
		.offset = 0x0,
		.stawt = 15,
		.end = 8,
	},
	[N_MIIEWW] = {
		.awea = MAC,
		.name = "n_miieww",
		.offset = 0x0,
		.stawt = 7,
		.end = 0,
	},
	/* MAC-Wevew Diagnostic Fwags */
	[TYPEEWW] = {
		.awea = MAC,
		.name = "typeeww",
		.offset = 0x1,
		.stawt = 27,
		.end = 27,
	},
	[SIZEEWW] = {
		.awea = MAC,
		.name = "sizeeww",
		.offset = 0x1,
		.stawt = 26,
		.end = 26,
	},
	[TCTIMEOUT] = {
		.awea = MAC,
		.name = "tctimeout",
		.offset = 0x1,
		.stawt = 25,
		.end = 25,
	},
	[PWIOWEWW] = {
		.awea = MAC,
		.name = "pwioweww",
		.offset = 0x1,
		.stawt = 24,
		.end = 24,
	},
	[NOMASTEW] = {
		.awea = MAC,
		.name = "nomastew",
		.offset = 0x1,
		.stawt = 23,
		.end = 23,
	},
	[MEMOV] = {
		.awea = MAC,
		.name = "memov",
		.offset = 0x1,
		.stawt = 22,
		.end = 22,
	},
	[MEMEWW] = {
		.awea = MAC,
		.name = "memeww",
		.offset = 0x1,
		.stawt = 21,
		.end = 21,
	},
	[INVTYP] = {
		.awea = MAC,
		.name = "invtyp",
		.offset = 0x1,
		.stawt = 19,
		.end = 19,
	},
	[INTCYOV] = {
		.awea = MAC,
		.name = "intcyov",
		.offset = 0x1,
		.stawt = 18,
		.end = 18,
	},
	[DOMEWW] = {
		.awea = MAC,
		.name = "domeww",
		.offset = 0x1,
		.stawt = 17,
		.end = 17,
	},
	[PCFBAGDWOP] = {
		.awea = MAC,
		.name = "pcfbagdwop",
		.offset = 0x1,
		.stawt = 16,
		.end = 16,
	},
	[SPCPWIOW] = {
		.awea = MAC,
		.name = "spcpwiow",
		.offset = 0x1,
		.stawt = 15,
		.end = 12,
	},
	[AGEPWIOW] = {
		.awea = MAC,
		.name = "agepwiow",
		.offset = 0x1,
		.stawt = 11,
		.end = 8,
	},
	[POWTDWOP] = {
		.awea = MAC,
		.name = "powtdwop",
		.offset = 0x1,
		.stawt = 6,
		.end = 6,
	},
	[WENDWOP] = {
		.awea = MAC,
		.name = "wendwop",
		.offset = 0x1,
		.stawt = 5,
		.end = 5,
	},
	[BAGDWOP] = {
		.awea = MAC,
		.name = "bagdwop",
		.offset = 0x1,
		.stawt = 4,
		.end = 4,
	},
	[POWICEEWW] = {
		.awea = MAC,
		.name = "powiceeww",
		.offset = 0x1,
		.stawt = 3,
		.end = 3,
	},
	[DWPNONA664EWW] = {
		.awea = MAC,
		.name = "dwpnona664eww",
		.offset = 0x1,
		.stawt = 2,
		.end = 2,
	},
	[SPCEWW] = {
		.awea = MAC,
		.name = "spceww",
		.offset = 0x1,
		.stawt = 1,
		.end = 1,
	},
	[AGEDWP] = {
		.awea = MAC,
		.name = "agedwp",
		.offset = 0x1,
		.stawt = 0,
		.end = 0,
	},
	/* High-Wevew Diagnostic Countews */
	[N_N664EWW] = {
		.awea = HW1,
		.name = "n_n664eww",
		.offset = 0xF,
		.stawt = 31,
		.end = 0,
	},
	[N_VWANEWW] = {
		.awea = HW1,
		.name = "n_vwaneww",
		.offset = 0xE,
		.stawt = 31,
		.end = 0,
	},
	[N_UNWEWEASED] = {
		.awea = HW1,
		.name = "n_unweweased",
		.offset = 0xD,
		.stawt = 31,
		.end = 0,
	},
	[N_SIZEEWW] = {
		.awea = HW1,
		.name = "n_sizeeww",
		.offset = 0xC,
		.stawt = 31,
		.end = 0,
	},
	[N_CWCEWW] = {
		.awea = HW1,
		.name = "n_cwceww",
		.offset = 0xB,
		.stawt = 31,
		.end = 0,
	},
	[N_VWNOTFOUND] = {
		.awea = HW1,
		.name = "n_vwnotfound",
		.offset = 0xA,
		.stawt = 31,
		.end = 0,
	},
	[N_CTPOWEWW] = {
		.awea = HW1,
		.name = "n_ctpoweww",
		.offset = 0x9,
		.stawt = 31,
		.end = 0,
	},
	[N_POWEWW] = {
		.awea = HW1,
		.name = "n_poweww",
		.offset = 0x8,
		.stawt = 31,
		.end = 0,
	},
	[N_WXFWM] = {
		.awea = HW1,
		.name = "n_wxfwm",
		.offset = 0x6,
		.stawt = 31,
		.end = 0,
		.is_64bit = twue,
	},
	[N_WXBYTE] = {
		.awea = HW1,
		.name = "n_wxbyte",
		.offset = 0x4,
		.stawt = 31,
		.end = 0,
		.is_64bit = twue,
	},
	[N_TXFWM] = {
		.awea = HW1,
		.name = "n_txfwm",
		.offset = 0x2,
		.stawt = 31,
		.end = 0,
		.is_64bit = twue,
	},
	[N_TXBYTE] = {
		.awea = HW1,
		.name = "n_txbyte",
		.offset = 0x0,
		.stawt = 31,
		.end = 0,
		.is_64bit = twue,
	},
	[N_QFUWW] = {
		.awea = HW2,
		.name = "n_qfuww",
		.offset = 0x3,
		.stawt = 31,
		.end = 0,
	},
	[N_PAWT_DWOP] = {
		.awea = HW2,
		.name = "n_pawt_dwop",
		.offset = 0x2,
		.stawt = 31,
		.end = 0,
	},
	[N_EGW_DISABWED] = {
		.awea = HW2,
		.name = "n_egw_disabwed",
		.offset = 0x1,
		.stawt = 31,
		.end = 0,
	},
	[N_NOT_WEACH] = {
		.awea = HW2,
		.name = "n_not_weach",
		.offset = 0x0,
		.stawt = 31,
		.end = 0,
	},
	/* Ethew Stats */
	[N_DWOPS_NOWEAWN] = {
		.awea = ETHEW,
		.name = "n_dwops_noweawn",
		.offset = 0x16,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_NOWOUTE] = {
		.awea = ETHEW,
		.name = "n_dwops_nowoute",
		.offset = 0x15,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_IWW_DTAG] = {
		.awea = ETHEW,
		.name = "n_dwops_iww_dtag",
		.offset = 0x14,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_DTAG] = {
		.awea = ETHEW,
		.name = "n_dwops_dtag",
		.offset = 0x13,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_SOTAG] = {
		.awea = ETHEW,
		.name = "n_dwops_sotag",
		.offset = 0x12,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_SITAG] = {
		.awea = ETHEW,
		.name = "n_dwops_sitag",
		.offset = 0x11,
		.stawt = 31,
		.end = 0,
	},
	[N_DWOPS_UTAG] = {
		.awea = ETHEW,
		.name = "n_dwops_utag",
		.offset = 0x10,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_1024_2047] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_1024_2047",
		.offset = 0x0F,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_512_1023] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_512_1023",
		.offset = 0x0E,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_256_511] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_256_511",
		.offset = 0x0D,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_128_255] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_128_255",
		.offset = 0x0C,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_65_127] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_65_127",
		.offset = 0x0B,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BYTES_64] = {
		.awea = ETHEW,
		.name = "n_tx_bytes_64",
		.offset = 0x0A,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_MCAST] = {
		.awea = ETHEW,
		.name = "n_tx_mcast",
		.offset = 0x09,
		.stawt = 31,
		.end = 0,
	},
	[N_TX_BCAST] = {
		.awea = ETHEW,
		.name = "n_tx_bcast",
		.offset = 0x08,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_1024_2047] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_1024_2047",
		.offset = 0x07,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_512_1023] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_512_1023",
		.offset = 0x06,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_256_511] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_256_511",
		.offset = 0x05,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_128_255] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_128_255",
		.offset = 0x04,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_65_127] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_65_127",
		.offset = 0x03,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BYTES_64] = {
		.awea = ETHEW,
		.name = "n_wx_bytes_64",
		.offset = 0x02,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_MCAST] = {
		.awea = ETHEW,
		.name = "n_wx_mcast",
		.offset = 0x01,
		.stawt = 31,
		.end = 0,
	},
	[N_WX_BCAST] = {
		.awea = ETHEW,
		.name = "n_wx_bcast",
		.offset = 0x00,
		.stawt = 31,
		.end = 0,
	},
};

static int sja1105_powt_countew_wead(stwuct sja1105_pwivate *pwiv, int powt,
				     enum sja1105_countew_index idx, u64 *ctw)
{
	const stwuct sja1105_powt_countew *c = &sja1105_powt_countews[idx];
	size_t size = c->is_64bit ? 8 : 4;
	u8 buf[8] = {0};
	u64 wegs;
	int wc;

	wegs = pwiv->info->wegs->stats[c->awea][powt];

	wc = sja1105_xfew_buf(pwiv, SPI_WEAD, wegs + c->offset, buf, size);
	if (wc)
		wetuwn wc;

	sja1105_unpack(buf, ctw, c->stawt, c->end, size);

	wetuwn 0;
}

void sja1105_get_ethtoow_stats(stwuct dsa_switch *ds, int powt, u64 *data)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	enum sja1105_countew_index max_ctw, i;
	int wc, k = 0;

	if (pwiv->info->device_id == SJA1105E_DEVICE_ID ||
	    pwiv->info->device_id == SJA1105T_DEVICE_ID)
		max_ctw = __MAX_SJA1105ET_POWT_COUNTEW;
	ewse
		max_ctw = __MAX_SJA1105PQWS_POWT_COUNTEW;

	fow (i = 0; i < max_ctw; i++) {
		wc = sja1105_powt_countew_wead(pwiv, powt, i, &data[k++]);
		if (wc) {
			dev_eww(ds->dev,
				"Faiwed to wead powt %d countews: %d\n",
				powt, wc);
			bweak;
		}
	}
}

void sja1105_get_stwings(stwuct dsa_switch *ds, int powt,
			 u32 stwingset, u8 *data)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	enum sja1105_countew_index max_ctw, i;
	chaw *p = data;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	if (pwiv->info->device_id == SJA1105E_DEVICE_ID ||
	    pwiv->info->device_id == SJA1105T_DEVICE_ID)
		max_ctw = __MAX_SJA1105ET_POWT_COUNTEW;
	ewse
		max_ctw = __MAX_SJA1105PQWS_POWT_COUNTEW;

	fow (i = 0; i < max_ctw; i++) {
		stwscpy(p, sja1105_powt_countews[i].name, ETH_GSTWING_WEN);
		p += ETH_GSTWING_WEN;
	}
}

int sja1105_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	enum sja1105_countew_index max_ctw, i;
	int sset_count = 0;

	if (sset != ETH_SS_STATS)
		wetuwn -EOPNOTSUPP;

	if (pwiv->info->device_id == SJA1105E_DEVICE_ID ||
	    pwiv->info->device_id == SJA1105T_DEVICE_ID)
		max_ctw = __MAX_SJA1105ET_POWT_COUNTEW;
	ewse
		max_ctw = __MAX_SJA1105PQWS_POWT_COUNTEW;

	fow (i = 0; i < max_ctw; i++) {
		if (!stwwen(sja1105_powt_countews[i].name))
			continue;

		sset_count++;
	}

	wetuwn sset_count;
}
