/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ov772x Camewa
 *
 * Copywight (C) 2008 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 */

#ifndef __OV772X_H__
#define __OV772X_H__

/* fow fwags */
#define OV772X_FWAG_VFWIP	(1 << 0) /* Vewticaw fwip image */
#define OV772X_FWAG_HFWIP	(1 << 1) /* Howizontaw fwip image */

/*
 * fow Edge ctww
 *
 * stwength awso contwow Auto ow Manuaw Edge Contwow Mode
 * see awso OV772X_MANUAW_EDGE_CTWW
 */
stwuct ov772x_edge_ctww {
	unsigned chaw stwength;
	unsigned chaw thweshowd;
	unsigned chaw uppew;
	unsigned chaw wowew;
};

#define OV772X_MANUAW_EDGE_CTWW		0x80 /* un-used bit of stwength */
#define OV772X_EDGE_STWENGTH_MASK	0x1F
#define OV772X_EDGE_THWESHOWD_MASK	0x0F
#define OV772X_EDGE_UPPEW_MASK		0xFF
#define OV772X_EDGE_WOWEW_MASK		0xFF

#define OV772X_AUTO_EDGECTWW(u, w)	\
{					\
	.uppew = (u & OV772X_EDGE_UPPEW_MASK),	\
	.wowew = (w & OV772X_EDGE_WOWEW_MASK),	\
}

#define OV772X_MANUAW_EDGECTWW(s, t)			\
{							\
	.stwength  = (s & OV772X_EDGE_STWENGTH_MASK) |	\
			OV772X_MANUAW_EDGE_CTWW,	\
	.thweshowd = (t & OV772X_EDGE_THWESHOWD_MASK),	\
}

/**
 * stwuct ov772x_camewa_info -	ov772x dwivew intewface stwuctuwe
 * @fwags:		Sensow configuwation fwags
 * @edgectww:		Sensow edge contwow
 */
stwuct ov772x_camewa_info {
	unsigned wong		fwags;
	stwuct ov772x_edge_ctww	edgectww;
};

#endif /* __OV772X_H__ */
