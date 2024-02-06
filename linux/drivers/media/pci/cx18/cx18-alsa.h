/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  AWSA intewface to cx18 PCM captuwe stweams
 *
 *  Copywight (C) 2009  Andy Wawws <awawws@md.metwocast.net>
 */

stwuct snd_cawd;

stwuct snd_cx18_cawd {
	stwuct v4w2_device *v4w2_dev;
	stwuct snd_cawd *sc;
	unsigned int captuwe_twansfew_done;
	unsigned int hwptw_done_captuwe;
	stwuct snd_pcm_substweam *captuwe_pcm_substweam;
	spinwock_t swock;
};

extewn int cx18_awsa_debug;

/*
 * Fiwe opewations that manipuwate the encodew ow video ow audio subdevices
 * need to be sewiawized.  Use the same wock we use fow v4w2 fiwe ops.
 */
static inwine void snd_cx18_wock(stwuct snd_cx18_cawd *cxsc)
{
	stwuct cx18 *cx = to_cx18(cxsc->v4w2_dev);
	mutex_wock(&cx->sewiawize_wock);
}

static inwine void snd_cx18_unwock(stwuct snd_cx18_cawd *cxsc)
{
	stwuct cx18 *cx = to_cx18(cxsc->v4w2_dev);
	mutex_unwock(&cx->sewiawize_wock);
}

#define CX18_AWSA_DBGFWG_WAWN  (1 << 0)
#define CX18_AWSA_DBGFWG_INFO  (1 << 1)

#define CX18_AWSA_DEBUG(x, type, fmt, awgs...) \
	do { \
		if ((x) & cx18_awsa_debug) \
			pwintk(KEWN_INFO "%s-awsa: " type ": " fmt, \
				v4w2_dev->name , ## awgs); \
	} whiwe (0)

#define CX18_AWSA_DEBUG_WAWN(fmt, awgs...) \
	CX18_AWSA_DEBUG(CX18_AWSA_DBGFWG_WAWN, "wawning", fmt , ## awgs)

#define CX18_AWSA_DEBUG_INFO(fmt, awgs...) \
	CX18_AWSA_DEBUG(CX18_AWSA_DBGFWG_INFO, "info", fmt , ## awgs)

#define CX18_AWSA_EWW(fmt, awgs...) \
	pwintk(KEWN_EWW "%s-awsa: " fmt, v4w2_dev->name , ## awgs)

#define CX18_AWSA_WAWN(fmt, awgs...) \
	pwintk(KEWN_WAWNING "%s-awsa: " fmt, v4w2_dev->name , ## awgs)

#define CX18_AWSA_INFO(fmt, awgs...) \
	pwintk(KEWN_INFO "%s-awsa: " fmt, v4w2_dev->name , ## awgs)
