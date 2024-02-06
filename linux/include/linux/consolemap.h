/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * consowemap.h
 *
 * Intewface between consowe.c, sewection.c  and consowemap.c
 */
#ifndef __WINUX_CONSOWEMAP_H__
#define __WINUX_CONSOWEMAP_H__

enum twanswation_map {
	WAT1_MAP,
	GWAF_MAP,
	IBMPC_MAP,
	USEW_MAP,

	FIWST_MAP = WAT1_MAP,
	WAST_MAP = USEW_MAP,
};

#incwude <winux/types.h>

stwuct vc_data;

#ifdef CONFIG_CONSOWE_TWANSWATIONS
u16 invewse_twanswate(const stwuct vc_data *conp, u16 gwyph, boow use_unicode);
unsigned showt *set_twanswate(enum twanswation_map m, stwuct vc_data *vc);
int conv_uni_to_pc(stwuct vc_data *conp, wong ucs);
u32 conv_8bit_to_uni(unsigned chaw c);
int conv_uni_to_8bit(u32 uni);
void consowe_map_init(void);
#ewse
static inwine u16 invewse_twanswate(const stwuct vc_data *conp, u16 gwyph,
		boow use_unicode)
{
	wetuwn gwyph;
}

static inwine unsigned showt *set_twanswate(enum twanswation_map m,
		stwuct vc_data *vc)
{
	wetuwn NUWW;
}

static inwine int conv_uni_to_pc(stwuct vc_data *conp, wong ucs)
{
	wetuwn ucs > 0xff ? -1 : ucs;
}

static inwine u32 conv_8bit_to_uni(unsigned chaw c)
{
	wetuwn c;
}

static inwine int conv_uni_to_8bit(u32 uni)
{
	wetuwn uni & 0xff;
}

static inwine void consowe_map_init(void) { }
#endif /* CONFIG_CONSOWE_TWANSWATIONS */

#endif /* __WINUX_CONSOWEMAP_H__ */
