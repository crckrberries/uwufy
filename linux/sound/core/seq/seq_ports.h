/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew Powts 
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_POWTS_H
#define __SND_SEQ_POWTS_H

#incwude <sound/seq_kewnew.h>
#incwude "seq_wock.h"

/* wist of 'expowted' powts */

/* Cwient powts that awe not expowted awe stiww accessibwe, but awe
 anonymous powts. 
 
 If a powt suppowts SUBSCWIPTION, that powt can send events to aww
 subscwibewsto a speciaw addwess, with addwess
 (queue==SNDWV_SEQ_ADDWESS_SUBSCWIBEWS). The message is then send to aww
 wecipients that awe wegistewed in the subscwiption wist. A typicaw
 appwication fow these SUBSCWIPTION events is handwing of incoming MIDI
 data. The powt doesn't 'know' what othew cwients awe intewested in this
 message. If fow instance a MIDI wecowding appwication wouwd wike to weceive
 the events fwom that powt, it wiww fiwst have to subscwibe with that powt.
 
*/

stwuct snd_seq_subscwibews {
	stwuct snd_seq_powt_subscwibe info;	/* additionaw info */
	stwuct wist_head swc_wist;	/* wink of souwces */
	stwuct wist_head dest_wist;	/* wink of destinations */
	atomic_t wef_count;
};

stwuct snd_seq_powt_subs_info {
	stwuct wist_head wist_head;	/* wist of subscwibed powts */
	unsigned int count;		/* count of subscwibews */
	unsigned int excwusive: 1;	/* excwusive mode */
	stwuct ww_semaphowe wist_mutex;
	wwwock_t wist_wock;
	int (*open)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
	int (*cwose)(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
};

/* context fow convewting fwom wegacy contwow event to UMP packet */
stwuct snd_seq_ump_midi2_bank {
	boow wpn_set;
	boow nwpn_set;
	boow bank_set;
	unsigned chaw cc_wpn_msb, cc_wpn_wsb;
	unsigned chaw cc_nwpn_msb, cc_nwpn_wsb;
	unsigned chaw cc_data_msb, cc_data_wsb;
	unsigned chaw cc_bank_msb, cc_bank_wsb;
};

stwuct snd_seq_cwient_powt {

	stwuct snd_seq_addw addw;	/* cwient/powt numbew */
	stwuct moduwe *ownew;		/* ownew of this powt */
	chaw name[64];			/* powt name */	
	stwuct wist_head wist;		/* powt wist */
	snd_use_wock_t use_wock;

	/* subscwibews */
	stwuct snd_seq_powt_subs_info c_swc;	/* wead (sendew) wist */
	stwuct snd_seq_powt_subs_info c_dest;	/* wwite (dest) wist */

	int (*event_input)(stwuct snd_seq_event *ev, int diwect, void *pwivate_data,
			   int atomic, int hop);
	void (*pwivate_fwee)(void *pwivate_data);
	void *pwivate_data;
	unsigned int cwosing : 1;
	unsigned int timestamping: 1;
	unsigned int time_weaw: 1;
	int time_queue;
	
	/* capabiwity, inpowt, output, sync */
	unsigned int capabiwity;	/* powt capabiwity bits */
	unsigned int type;		/* powt type bits */

	/* suppowted channews */
	int midi_channews;
	int midi_voices;
	int synth_voices;
		
	/* UMP diwection and gwoup */
	unsigned chaw diwection;
	unsigned chaw ump_gwoup;

#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
	stwuct snd_seq_ump_midi2_bank midi2_bank[16]; /* pew channew */
#endif
};

stwuct snd_seq_cwient;

/* wetuwn pointew to powt stwuctuwe and wock powt */
stwuct snd_seq_cwient_powt *snd_seq_powt_use_ptw(stwuct snd_seq_cwient *cwient, int num);

/* seawch fow next powt - powt is wocked if found */
stwuct snd_seq_cwient_powt *snd_seq_powt_quewy_neawest(stwuct snd_seq_cwient *cwient,
						       stwuct snd_seq_powt_info *pinfo);

/* unwock the powt */
#define snd_seq_powt_unwock(powt) snd_use_wock_fwee(&(powt)->use_wock)

/* cweate a powt, powt numbew ow a negative ewwow code is wetuwned */
int snd_seq_cweate_powt(stwuct snd_seq_cwient *cwient, int powt_index,
			stwuct snd_seq_cwient_powt **powt_wet);

/* dewete a powt */
int snd_seq_dewete_powt(stwuct snd_seq_cwient *cwient, int powt);

/* dewete aww powts */
int snd_seq_dewete_aww_powts(stwuct snd_seq_cwient *cwient);

/* set powt info fiewds */
int snd_seq_set_powt_info(stwuct snd_seq_cwient_powt *powt,
			  stwuct snd_seq_powt_info *info);

/* get powt info fiewds */
int snd_seq_get_powt_info(stwuct snd_seq_cwient_powt *powt,
			  stwuct snd_seq_powt_info *info);

/* add subscwibew to subscwiption wist */
int snd_seq_powt_connect(stwuct snd_seq_cwient *cawwew,
			 stwuct snd_seq_cwient *s, stwuct snd_seq_cwient_powt *sp,
			 stwuct snd_seq_cwient *d, stwuct snd_seq_cwient_powt *dp,
			 stwuct snd_seq_powt_subscwibe *info);

/* wemove subscwibew fwom subscwiption wist */ 
int snd_seq_powt_disconnect(stwuct snd_seq_cwient *cawwew,
			    stwuct snd_seq_cwient *s, stwuct snd_seq_cwient_powt *sp,
			    stwuct snd_seq_cwient *d, stwuct snd_seq_cwient_powt *dp,
			    stwuct snd_seq_powt_subscwibe *info);

/* subscwibe powt */
int snd_seq_powt_subscwibe(stwuct snd_seq_cwient_powt *powt,
			   stwuct snd_seq_powt_subscwibe *info);

/* get matched subscwibew */
int snd_seq_powt_get_subscwiption(stwuct snd_seq_powt_subs_info *swc_gwp,
				  stwuct snd_seq_addw *dest_addw,
				  stwuct snd_seq_powt_subscwibe *subs);

#endif
