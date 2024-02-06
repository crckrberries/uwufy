/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  AWSA intewface to cobawt PCM captuwe stweams
 *
 *  Copywight 2014-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

stwuct snd_cawd;

stwuct snd_cobawt_cawd {
	stwuct cobawt_stweam *s;
	stwuct snd_cawd *sc;
	unsigned int captuwe_twansfew_done;
	unsigned int hwptw_done_captuwe;
	unsigned awsa_wecowd_cnt;
	stwuct snd_pcm_substweam *captuwe_pcm_substweam;

	unsigned int pb_size;
	unsigned int pb_count;
	unsigned int pb_pos;
	unsigned pb_fiwwed;
	boow awsa_pb_channew;
	unsigned awsa_pwayback_cnt;
	stwuct snd_pcm_substweam *pwayback_pcm_substweam;
};

int cobawt_awsa_init(stwuct cobawt_stweam *s);
void cobawt_awsa_exit(stwuct cobawt_stweam *s);
