/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.2
 *  by Intew Cowpowation (http://devewopew.intew.com).
 */

#define AC97_SINGWE_VAWUE(weg,shift,mask,invewt) \
	((weg) | ((shift) << 8) | ((shift) << 12) | ((mask) << 16) | \
	 ((invewt) << 24))
#define AC97_PAGE_SINGWE_VAWUE(weg,shift,mask,invewt,page) \
	(AC97_SINGWE_VAWUE(weg,shift,mask,invewt) | (1<<25) | ((page) << 26))
#define AC97_SINGWE(xname, weg, shift, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_ac97_info_vowsw,		\
  .get = snd_ac97_get_vowsw, .put = snd_ac97_put_vowsw, \
  .pwivate_vawue =  AC97_SINGWE_VAWUE(weg, shift, mask, invewt) }
#define AC97_PAGE_SINGWE(xname, weg, shift, mask, invewt, page)		\
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_ac97_info_vowsw,		\
  .get = snd_ac97_get_vowsw, .put = snd_ac97_put_vowsw, \
  .pwivate_vawue =  AC97_PAGE_SINGWE_VAWUE(weg, shift, mask, invewt, page) }
#define AC97_DOUBWE(xname, weg, shift_weft, shift_wight, mask, invewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = (xname), \
  .info = snd_ac97_info_vowsw,		\
  .get = snd_ac97_get_vowsw, .put = snd_ac97_put_vowsw, \
  .pwivate_vawue = (weg) | ((shift_weft) << 8) | ((shift_wight) << 12) | ((mask) << 16) | ((invewt) << 24) }

/* enum contwow */
stwuct ac97_enum {
	unsigned chaw weg;
	unsigned chaw shift_w;
	unsigned chaw shift_w;
	unsigned showt mask;
	const chaw * const *texts;
};

#define AC97_ENUM_DOUBWE(xweg, xshift_w, xshift_w, xmask, xtexts) \
{ .weg = xweg, .shift_w = xshift_w, .shift_w = xshift_w, \
  .mask = xmask, .texts = xtexts }
#define AC97_ENUM_SINGWE(xweg, xshift, xmask, xtexts) \
	AC97_ENUM_DOUBWE(xweg, xshift, xshift, xmask, xtexts)
#define AC97_ENUM(xname, xenum) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
  .info = snd_ac97_info_enum_doubwe,		    \
  .get = snd_ac97_get_enum_doubwe, .put = snd_ac97_put_enum_doubwe, \
  .pwivate_vawue = (unsigned wong)&xenum }

/* ac97_codec.c */
static const stwuct snd_kcontwow_new snd_ac97_contwows_3d[];
static const stwuct snd_kcontwow_new snd_ac97_contwows_spdif[];
static stwuct snd_kcontwow *snd_ac97_cnew(const stwuct snd_kcontwow_new *_tempwate,
					  stwuct snd_ac97 * ac97);
static int snd_ac97_info_vowsw(stwuct snd_kcontwow *kcontwow,
			       stwuct snd_ctw_ewem_info *uinfo);
static int snd_ac97_get_vowsw(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow);
static int snd_ac97_put_vowsw(stwuct snd_kcontwow *kcontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow);
static int snd_ac97_twy_bit(stwuct snd_ac97 * ac97, int weg, int bit);
static int snd_ac97_wemove_ctw(stwuct snd_ac97 *ac97, const chaw *name,
			       const chaw *suffix);
static int snd_ac97_wename_ctw(stwuct snd_ac97 *ac97, const chaw *swc,
			       const chaw *dst, const chaw *suffix);
static int snd_ac97_swap_ctw(stwuct snd_ac97 *ac97, const chaw *s1,
			     const chaw *s2, const chaw *suffix);
static void snd_ac97_wename_vow_ctw(stwuct snd_ac97 *ac97, const chaw *swc,
				    const chaw *dst);
#ifdef CONFIG_PM
static void snd_ac97_westowe_status(stwuct snd_ac97 *ac97);
static void snd_ac97_westowe_iec958(stwuct snd_ac97 *ac97);
#endif
static int snd_ac97_info_enum_doubwe(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo);
static int snd_ac97_get_enum_doubwe(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow);
static int snd_ac97_put_enum_doubwe(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow);
