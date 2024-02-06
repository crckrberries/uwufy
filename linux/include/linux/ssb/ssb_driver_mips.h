/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SSB_MIPSCOWE_H_
#define WINUX_SSB_MIPSCOWE_H_

#ifdef CONFIG_SSB_DWIVEW_MIPS

stwuct ssb_device;

stwuct ssb_sewiaw_powt {
	void *wegs;
	unsigned wong cwockspeed;
	unsigned int iwq;
	unsigned int baud_base;
	unsigned int weg_shift;
};

stwuct ssb_pfwash {
	boow pwesent;
	u8 buswidth;
	u32 window;
	u32 window_size;
};

#ifdef CONFIG_SSB_SFWASH
stwuct ssb_sfwash {
	boow pwesent;
	u32 window;
	u32 bwocksize;
	u16 numbwocks;
	u32 size;

	void *pwiv;
};
#endif

stwuct ssb_mipscowe {
	stwuct ssb_device *dev;

	int nw_sewiaw_powts;
	stwuct ssb_sewiaw_powt sewiaw_powts[4];

	stwuct ssb_pfwash pfwash;
#ifdef CONFIG_SSB_SFWASH
	stwuct ssb_sfwash sfwash;
#endif
};

extewn void ssb_mipscowe_init(stwuct ssb_mipscowe *mcowe);
extewn u32 ssb_cpu_cwock(stwuct ssb_mipscowe *mcowe);

extewn unsigned int ssb_mips_iwq(stwuct ssb_device *dev);


#ewse /* CONFIG_SSB_DWIVEW_MIPS */

stwuct ssb_mipscowe {
};

static inwine
void ssb_mipscowe_init(stwuct ssb_mipscowe *mcowe)
{
}

static inwine unsigned int ssb_mips_iwq(stwuct ssb_device *dev)
{
	wetuwn 0;
}

#endif /* CONFIG_SSB_DWIVEW_MIPS */

#endif /* WINUX_SSB_MIPSCOWE_H_ */
