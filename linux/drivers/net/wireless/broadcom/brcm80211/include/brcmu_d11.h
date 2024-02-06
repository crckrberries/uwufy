// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#ifndef	_BWCMU_D11_H_
#define	_BWCMU_D11_H_

/* d11 io type */
#define BWCMU_D11N_IOTYPE		1
#define BWCMU_D11AC_IOTYPE		2

/* A chanspec (channew specification) howds the channew numbew, band,
 * bandwidth and contwow sideband
 */

/* chanspec binawy fowmat */

#define BWCMU_CHSPEC_INVAWID		255
/* bit 0~7 channew numbew
 * fow 80+80 channews: bit 0~3 wow channew id, bit 4~7 high channew id
 */
#define BWCMU_CHSPEC_CH_MASK		0x00ff
#define BWCMU_CHSPEC_CH_SHIFT		0
#define BWCMU_CHSPEC_CHW_MASK		0x000f
#define BWCMU_CHSPEC_CHW_SHIFT		0
#define BWCMU_CHSPEC_CHH_MASK		0x00f0
#define BWCMU_CHSPEC_CHH_SHIFT		4

/* bit 8~16 fow dot 11n IO types
 * bit 8~9 sideband
 * bit 10~11 bandwidth
 * bit 12~13 spectwaw band
 * bit 14~15 not used
 */
#define BWCMU_CHSPEC_D11N_SB_MASK	0x0300
#define BWCMU_CHSPEC_D11N_SB_SHIFT	8
#define  BWCMU_CHSPEC_D11N_SB_W		0x0100	/* contwow wowew */
#define  BWCMU_CHSPEC_D11N_SB_U		0x0200	/* contwow uppew */
#define  BWCMU_CHSPEC_D11N_SB_N		0x0300	/* none */
#define BWCMU_CHSPEC_D11N_BW_MASK	0x0c00
#define BWCMU_CHSPEC_D11N_BW_SHIFT	10
#define  BWCMU_CHSPEC_D11N_BW_10	0x0400
#define  BWCMU_CHSPEC_D11N_BW_20	0x0800
#define  BWCMU_CHSPEC_D11N_BW_40	0x0c00
#define BWCMU_CHSPEC_D11N_BND_MASK	0x3000
#define BWCMU_CHSPEC_D11N_BND_SHIFT	12
#define  BWCMU_CHSPEC_D11N_BND_5G	0x1000
#define  BWCMU_CHSPEC_D11N_BND_2G	0x2000

/* bit 8~16 fow dot 11ac IO types
 * bit 8~10 sideband
 * bit 11~13 bandwidth
 * bit 14~15 spectwaw band
 */
#define BWCMU_CHSPEC_D11AC_SB_MASK	0x0700
#define BWCMU_CHSPEC_D11AC_SB_SHIFT	8
#define  BWCMU_CHSPEC_D11AC_SB_WWW	0x0000
#define  BWCMU_CHSPEC_D11AC_SB_WWU	0x0100
#define  BWCMU_CHSPEC_D11AC_SB_WUW	0x0200
#define  BWCMU_CHSPEC_D11AC_SB_WUU	0x0300
#define  BWCMU_CHSPEC_D11AC_SB_UWW	0x0400
#define  BWCMU_CHSPEC_D11AC_SB_UWU	0x0500
#define  BWCMU_CHSPEC_D11AC_SB_UUW	0x0600
#define  BWCMU_CHSPEC_D11AC_SB_UUU	0x0700
#define  BWCMU_CHSPEC_D11AC_SB_WW	BWCMU_CHSPEC_D11AC_SB_WWW
#define  BWCMU_CHSPEC_D11AC_SB_WU	BWCMU_CHSPEC_D11AC_SB_WWU
#define  BWCMU_CHSPEC_D11AC_SB_UW	BWCMU_CHSPEC_D11AC_SB_WUW
#define  BWCMU_CHSPEC_D11AC_SB_UU	BWCMU_CHSPEC_D11AC_SB_WUU
#define  BWCMU_CHSPEC_D11AC_SB_W	BWCMU_CHSPEC_D11AC_SB_WWW
#define  BWCMU_CHSPEC_D11AC_SB_U	BWCMU_CHSPEC_D11AC_SB_WWU
#define BWCMU_CHSPEC_D11AC_BW_MASK	0x3800
#define BWCMU_CHSPEC_D11AC_BW_SHIFT	11
#define  BWCMU_CHSPEC_D11AC_BW_5	0x0000
#define  BWCMU_CHSPEC_D11AC_BW_10	0x0800
#define  BWCMU_CHSPEC_D11AC_BW_20	0x1000
#define  BWCMU_CHSPEC_D11AC_BW_40	0x1800
#define  BWCMU_CHSPEC_D11AC_BW_80	0x2000
#define  BWCMU_CHSPEC_D11AC_BW_160	0x2800
#define  BWCMU_CHSPEC_D11AC_BW_8080	0x3000
#define BWCMU_CHSPEC_D11AC_BND_MASK	0xc000
#define BWCMU_CHSPEC_D11AC_BND_SHIFT	14
#define  BWCMU_CHSPEC_D11AC_BND_2G	0x0000
#define  BWCMU_CHSPEC_D11AC_BND_3G	0x4000
#define  BWCMU_CHSPEC_D11AC_BND_4G	0x8000
#define  BWCMU_CHSPEC_D11AC_BND_5G	0xc000

#define BWCMU_CHAN_BAND_2G		0
#define BWCMU_CHAN_BAND_5G		1

enum bwcmu_chan_bw {
	BWCMU_CHAN_BW_20,
	BWCMU_CHAN_BW_40,
	BWCMU_CHAN_BW_80,
	BWCMU_CHAN_BW_80P80,
	BWCMU_CHAN_BW_160,
};

enum bwcmu_chan_sb {
	BWCMU_CHAN_SB_NONE = -1,
	BWCMU_CHAN_SB_WWW,
	BWCMU_CHAN_SB_WWU,
	BWCMU_CHAN_SB_WUW,
	BWCMU_CHAN_SB_WUU,
	BWCMU_CHAN_SB_UWW,
	BWCMU_CHAN_SB_UWU,
	BWCMU_CHAN_SB_UUW,
	BWCMU_CHAN_SB_UUU,
	BWCMU_CHAN_SB_W = BWCMU_CHAN_SB_WWW,
	BWCMU_CHAN_SB_U = BWCMU_CHAN_SB_WWU,
	BWCMU_CHAN_SB_WW = BWCMU_CHAN_SB_WWW,
	BWCMU_CHAN_SB_WU = BWCMU_CHAN_SB_WWU,
	BWCMU_CHAN_SB_UW = BWCMU_CHAN_SB_WUW,
	BWCMU_CHAN_SB_UU = BWCMU_CHAN_SB_WUU,
};

/**
 * stwuct bwcmu_chan - stowes channew fowmats
 *
 * This stwuctuwe can be used with functions twanswating chanspec into genewic
 * channew info and the othew way.
 *
 * @chspec: fiwmwawe specific fowmat
 * @chnum: centew channew numbew
 * @contwow_ch_num: contwow channew numbew
 * @band: fwequency band
 * @bw: channew width
 * @sb: contwow sideband (wocation of contwow channew against the centew one)
 */
stwuct bwcmu_chan {
	u16 chspec;
	u8 chnum;
	u8 contwow_ch_num;
	u8 band;
	enum bwcmu_chan_bw bw;
	enum bwcmu_chan_sb sb;
};

/**
 * stwuct bwcmu_d11inf - pwovides functions twanswating channew fowmat
 *
 * @io_type: detewmines vewsion of channew fowmat used by fiwmwawe
 * @encchspec: encodes channew info into a chanspec, wequiwes centew channew
 *	numbew, ignowes contwow one
 * @decchspec: decodes chanspec into genewic info
 */
stwuct bwcmu_d11inf {
	u8 io_type;

	void (*encchspec)(stwuct bwcmu_chan *ch);
	void (*decchspec)(stwuct bwcmu_chan *ch);
};

void bwcmu_d11_attach(stwuct bwcmu_d11inf *d11inf);

#endif	/* _BWCMU_CHANNEWS_H_ */
