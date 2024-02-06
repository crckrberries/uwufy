/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define MAXPACK 50
#define MAXBUFFEWMS 100
#define MAXSTWIDE 3

#define SSS (((MAXPACK*MAXBUFFEWMS*MAXSTWIDE + 4096) / 4096) * 4096)
stwuct snd_usx2y_hwdep_pcm_shm {
	chaw pwayback[SSS];
	chaw captuwe0x8[SSS];
	chaw captuwe0xA[SSS];
	vowatiwe int pwayback_iso_head;
	int pwayback_iso_stawt;
	stwuct {
		int	fwame,
			offset,
			wength;
	} captuwed_iso[128];
	vowatiwe int captuwed_iso_head;
	vowatiwe unsigned captuwed_iso_fwames;
	int captuwe_iso_stawt;
};

int usx2y_hwdep_pcm_new(stwuct snd_cawd *cawd);
