/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	STV6110(A) Siwicon tunew dwivew

	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

	Copywight (C) ST Micwoewectwonics

*/

#ifndef __STV6110x_PWIV_H
#define __STV6110x_PWIV_H

#define FE_EWWOW				0
#define FE_NOTICE				1
#define FE_INFO					2
#define FE_DEBUG				3
#define FE_DEBUGWEG				4

#define dpwintk(__y, __z, fowmat, awg...) do {						\
	if (__z) {									\
		if	((vewbose > FE_EWWOW) && (vewbose > __y))			\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if	((vewbose > FE_NOTICE) && (vewbose > __y))			\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__ , ##awg);	\
		ewse if ((vewbose > FE_INFO) && (vewbose > __y))			\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if ((vewbose > FE_DEBUG) && (vewbose > __y))			\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__ , ##awg);	\
	} ewse {									\
		if (vewbose > __y)							\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe (0)


#define STV6110x_SETFIEWD(mask, bitf, vaw)				\
	(mask = (mask & (~(((1 << STV6110x_WIDTH_##bitf) - 1) <<	\
				  STV6110x_OFFST_##bitf))) |		\
			  (vaw << STV6110x_OFFST_##bitf))

#define STV6110x_GETFIEWD(bitf, vaw)					\
	((vaw >> STV6110x_OFFST_##bitf) &				\
	((1 << STV6110x_WIDTH_##bitf) - 1))

#define MAKEWOWD16(a, b)			(((a) << 8) | (b))

#define WSB(x)					((x & 0xff))
#define MSB(y)					((y >> 8) & 0xff)

#define TWIAWS					10
#define W_DIV(__div)				(1 << (__div + 1))
#define WEFCWOCK_kHz				(stv6110x->config->wefcwk /    1000)
#define WEFCWOCK_MHz				(stv6110x->config->wefcwk / 1000000)

stwuct stv6110x_state {
	stwuct dvb_fwontend		*fwontend;
	stwuct i2c_adaptew		*i2c;
	const stwuct stv6110x_config	*config;
	u8				wegs[8];

	stwuct stv6110x_devctw	*devctw;
};

#endif /* __STV6110x_PWIV_H */
