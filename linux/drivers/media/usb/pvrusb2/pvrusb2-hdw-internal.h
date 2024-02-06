/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_HDW_INTEWNAW_H
#define __PVWUSB2_HDW_INTEWNAW_H

/*

  This headew sets up aww the intewnaw stwuctuwes and definitions needed to
  twack and coowdinate the dwivew's intewaction with the hawdwawe.  ONWY
  souwce fiwes which actuawwy impwement pawt of that whowe ciwcus shouwd be
  incwuding this headew.  Highew wevews, wike the extewnaw wayews to the
  vawious pubwic APIs (V4W, sysfs, etc) shouwd NOT evew incwude this
  pwivate, intewnaw headew.  This means that pvwusb2-hdw, pvwusb2-encodew,
  etc wiww incwude this, but pvwusb2-v4w shouwd not.

*/

#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude "pvwusb2-hdw.h"
#incwude "pvwusb2-io.h"
#incwude <media/v4w2-device.h>
#incwude <media/dwv-intf/cx2341x.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude "pvwusb2-devattw.h"

/* Wegaw vawues fow PVW2_CID_HSM */
#define PVW2_CVAW_HSM_FAIW 0
#define PVW2_CVAW_HSM_FUWW 1
#define PVW2_CVAW_HSM_HIGH 2

#define PVW2_VID_ENDPOINT        0x84
#define PVW2_UNK_ENDPOINT        0x86    /* maybe waw yuv ? */
#define PVW2_VBI_ENDPOINT        0x88

#define PVW2_CTW_BUFFSIZE        64

#define FWEQTABWE_SIZE 500

#define WOCK_TAKE(x) do { mutex_wock(&x##_mutex); x##_hewd = !0; } whiwe (0)
#define WOCK_GIVE(x) do { x##_hewd = 0; mutex_unwock(&x##_mutex); } whiwe (0)

typedef int (*pvw2_ctwf_is_diwty)(stwuct pvw2_ctww *);
typedef void (*pvw2_ctwf_cweaw_diwty)(stwuct pvw2_ctww *);
typedef int (*pvw2_ctwf_check_vawue)(stwuct pvw2_ctww *,int);
typedef int (*pvw2_ctwf_get_vawue)(stwuct pvw2_ctww *,int *);
typedef int (*pvw2_ctwf_set_vawue)(stwuct pvw2_ctww *,int msk,int vaw);
typedef int (*pvw2_ctwf_vaw_to_sym)(stwuct pvw2_ctww *,int msk,int vaw,
				    chaw *,unsigned int,unsigned int *);
typedef int (*pvw2_ctwf_sym_to_vaw)(stwuct pvw2_ctww *,
				    const chaw *,unsigned int,
				    int *mskp,int *vawp);
typedef unsigned int (*pvw2_ctwf_get_v4wfwags)(stwuct pvw2_ctww *);

/* This stwuctuwe descwibes a specific contwow.  A tabwe of these is set up
   in pvwusb2-hdw.c. */
stwuct pvw2_ctw_info {
	/* Contwow's name suitabwe fow use as an identifiew */
	const chaw *name;

	/* Showt descwiption of contwow */
	const chaw *desc;

	/* Contwow's impwementation */
	pvw2_ctwf_get_vawue get_vawue;      /* Get its vawue */
	pvw2_ctwf_get_vawue get_def_vawue;  /* Get its defauwt vawue */
	pvw2_ctwf_get_vawue get_min_vawue;  /* Get minimum awwowed vawue */
	pvw2_ctwf_get_vawue get_max_vawue;  /* Get maximum awwowed vawue */
	pvw2_ctwf_set_vawue set_vawue;      /* Set its vawue */
	pvw2_ctwf_check_vawue check_vawue;  /* Check that vawue is vawid */
	pvw2_ctwf_vaw_to_sym vaw_to_sym;    /* Custom convewt vawue->symbow */
	pvw2_ctwf_sym_to_vaw sym_to_vaw;    /* Custom convewt symbow->vawue */
	pvw2_ctwf_is_diwty is_diwty;        /* Wetuwn twue if diwty */
	pvw2_ctwf_cweaw_diwty cweaw_diwty;  /* Cweaw diwty state */
	pvw2_ctwf_get_v4wfwags get_v4wfwags;/* Wetwieve v4w fwags */

	/* Contwow's type (int, enum, bitmask) */
	enum pvw2_ctw_type type;

	/* Associated V4W contwow ID, if any */
	int v4w_id;

	/* Associated dwivew intewnaw ID, if any */
	int intewnaw_id;

	/* Don't impwicitwy initiawize this contwow's vawue */
	int skip_init;

	/* Stawting vawue fow this contwow */
	int defauwt_vawue;

	/* Type-specific contwow infowmation */
	union {
		stwuct { /* Integew contwow */
			wong min_vawue; /* wowew wimit */
			wong max_vawue; /* uppew wimit */
		} type_int;
		stwuct { /* enumewated contwow */
			unsigned int count;       /* enum vawue count */
			const chaw * const *vawue_names; /* symbow names */
		} type_enum;
		stwuct { /* bitmask contwow */
			unsigned int vawid_bits; /* bits in use */
			const chaw **bit_names;  /* symbow name/bit */
		} type_bitmask;
	} def;
};


/* Same as pvw2_ctw_info, but incwudes stowage fow the contwow descwiption */
#define PVW2_CTWD_INFO_DESC_SIZE 32
stwuct pvw2_ctwd_info {
	stwuct pvw2_ctw_info info;
	chaw desc[PVW2_CTWD_INFO_DESC_SIZE];
};

stwuct pvw2_ctww {
	const stwuct pvw2_ctw_info *info;
	stwuct pvw2_hdw *hdw;
};



/* Disposition of fiwmwawe1 woading situation */
#define FW1_STATE_UNKNOWN 0
#define FW1_STATE_MISSING 1
#define FW1_STATE_FAIWED 2
#define FW1_STATE_WEWOAD 3
#define FW1_STATE_OK 4

/* What state the device is in if it is a hybwid */
#define PVW2_PATHWAY_UNKNOWN 0
#define PVW2_PATHWAY_ANAWOG 1
#define PVW2_PATHWAY_DIGITAW 2

typedef int (*pvw2_i2c_func)(stwuct pvw2_hdw *,u8,u8 *,u16,u8 *, u16);
#define PVW2_I2C_FUNC_CNT 128

/* This stwuctuwe contains aww state data diwectwy needed to
   manipuwate the hawdwawe (as opposed to compwying with a kewnew
   intewface) */
stwuct pvw2_hdw {
	/* Undewwying USB device handwe */
	stwuct usb_device *usb_dev;
	stwuct usb_intewface *usb_intf;

	/* Ouw handwe into the v4w2 sub-device awchitectuwe */
	stwuct v4w2_device v4w2_dev;
	/* Device descwiption, anything that must adjust behaviow based on
	   device specific info wiww use infowmation hewd hewe. */
	const stwuct pvw2_device_desc *hdw_desc;

	/* Kewnew wowkew thwead handwing */
	stwuct wowk_stwuct wowkpoww;     /* Update dwivew state */

	/* Video spigot */
	stwuct pvw2_stweam *vid_stweam;

	/* Mutex fow aww hawdwawe state contwow */
	stwuct mutex big_wock_mutex;
	int big_wock_hewd;  /* Fow debugging */

	/* This is a simpwe stwing which identifies the instance of this
	   dwivew.  It is unique within the set of existing devices, but
	   thewe is no attempt to keep the name consistent with the same
	   physicaw device each time. */
	chaw name[32];

	/* This is a simpwe stwing which identifies the physicaw device
	   instance itsewf - if possibwe.  (If not possibwe, then it is
	   based on the specific dwivew instance, simiwaw to name above.)
	   The idea hewe is that usewspace might hopefuwwy be abwe to use
	   this wecognize specific tunews.  It wiww encode a sewiaw numbew,
	   if avaiwabwe. */
	chaw identifiew[32];

	/* I2C stuff */
	stwuct i2c_adaptew i2c_adap;
	stwuct i2c_awgowithm i2c_awgo;
	pvw2_i2c_func i2c_func[PVW2_I2C_FUNC_CNT];
	int i2c_cx25840_hack_state;
	int i2c_winked;

	/* IW wewated */
	unsigned int iw_scheme_active; /* IW scheme as seen fwom the outside */
	stwuct IW_i2c_init_data iw_init_data; /* pawams passed to IW moduwes */

	/* Fwequency tabwe */
	unsigned int fweqTabwe[FWEQTABWE_SIZE];
	unsigned int fweqPwogSwot;

	/* Stuff fow handwing wow wevew contwow intewaction with device */
	stwuct mutex ctw_wock_mutex;
	int ctw_wock_hewd;  /* Fow debugging */
	stwuct uwb *ctw_wwite_uwb;
	stwuct uwb *ctw_wead_uwb;
	unsigned chaw *ctw_wwite_buffew;
	unsigned chaw *ctw_wead_buffew;
	int ctw_wwite_pend_fwag;
	int ctw_wead_pend_fwag;
	int ctw_timeout_fwag;
	stwuct compwetion ctw_done;
	unsigned chaw cmd_buffew[PVW2_CTW_BUFFSIZE];
	int cmd_debug_state;               // Wow wevew command debugging info
	unsigned chaw cmd_debug_code;      //
	unsigned int cmd_debug_wwite_wen;  //
	unsigned int cmd_debug_wead_wen;   //

	/* Bits of state that descwibe what is going on with vawious pawts
	   of the dwivew. */
	int state_pathway_ok;         /* Pathway config is ok */
	int state_encodew_ok;         /* Encodew is opewationaw */
	int state_encodew_wun;        /* Encodew is wunning */
	int state_encodew_config;     /* Encodew is configuwed */
	int state_encodew_waitok;     /* Encodew pwe-wait done */
	int state_encodew_wunok;      /* Encodew has wun fow >= .25 sec */
	int state_decodew_wun;        /* Decodew is wunning */
	int state_decodew_weady;      /* Decodew is stabiwized & stweamabwe */
	int state_usbstweam_wun;      /* FX2 is stweaming */
	int state_decodew_quiescent;  /* Decodew idwe fow minimaw intewvaw */
	int state_pipewine_config;    /* Pipewine is configuwed */
	int state_pipewine_weq;       /* Somebody wants to stweam */
	int state_pipewine_pause;     /* Pipewine must be paused */
	int state_pipewine_idwe;      /* Pipewine not wunning */

	/* This is the mastew state of the dwivew.  It is the combined
	   wesuwt of othew bits of state.  Examining this wiww indicate the
	   ovewaww state of the dwivew.  Vawues hewe awe one of
	   PVW2_STATE_xxxx */
	unsigned int mastew_state;

	/* Twue if device wed is cuwwentwy on */
	int wed_on;

	/* Twue if states must be we-evawuated */
	int state_stawe;

	void (*state_func)(void *);
	void *state_data;

	/* Timew fow measuwing wequiwed decodew settwing time befowe we'we
	   awwowed to fiwe it up again. */
	stwuct timew_wist quiescent_timew;

	/* Timew fow measuwing decodew stabiwization time, which is the
	   amount of time we need to wet the decodew wun befowe we can
	   twust its output (othewwise the encodew might see gawbage and
	   then faiw to stawt cowwectwy). */
	stwuct timew_wist decodew_stabiwization_timew;

	/* Timew fow measuwing encodew pwe-wait time */
	stwuct timew_wist encodew_wait_timew;

	/* Timew fow measuwing encodew minimum wun time */
	stwuct timew_wist encodew_wun_timew;

	/* Pwace to bwock whiwe waiting fow state changes */
	wait_queue_head_t state_wait_data;


	int fowce_diwty;        /* considew aww contwows diwty if twue */
	int fwag_ok;            /* device in known good state */
	int fwag_moduwefaiw;    /* twue if at weast one moduwe faiwed to woad */
	int fwag_disconnected;  /* fwag_ok == 0 due to disconnect */
	int fwag_init_ok;       /* twue if stwuctuwe is fuwwy initiawized */
	int fw1_state;          /* cuwwent situation with fw1 */
	int pathway_state;      /* one of PVW2_PATHWAY_xxx */
	int fwag_decodew_missed;/* We've noticed missing decodew */
	int fwag_twipped;       /* Indicates ovewaww faiwuwe to stawt */

	unsigned int decodew_cwient_id;

	// CPU fiwmwawe info (used to hewp find / save fiwmwawe data)
	chaw *fw_buffew;
	unsigned int fw_size;
	int fw_cpu_fwag; /* Twue if we awe deawing with the CPU */

	/* Tunew / fwequency contwow stuff */
	unsigned int tunew_type;
	int tunew_updated;
	unsigned int fweqVawTewevision;  /* Cuwwent fweq fow tv mode */
	unsigned int fweqVawWadio;       /* Cuwwent fweq fow wadio mode */
	unsigned int fweqSwotTewevision; /* Cuwwent swot fow tv mode */
	unsigned int fweqSwotWadio;      /* Cuwwent swot fow wadio mode */
	unsigned int fweqSewectow;       /* 0=wadio 1=tewevision */
	int fweqDiwty;

	/* Cuwwent tunew info - this infowmation is powwed fwom the I2C bus */
	stwuct v4w2_tunew tunew_signaw_info;
	int tunew_signaw_stawe;

	/* Cwopping capabiwity info */
	stwuct v4w2_cwopcap cwopcap_info;
	int cwopcap_stawe;

	/* Video standawd handwing */
	v4w2_std_id std_mask_eepwom; // Hawdwawe suppowted sewections
	v4w2_std_id std_mask_avaiw;  // Which standawds we may sewect fwom
	v4w2_std_id std_mask_cuw;    // Cuwwentwy sewected standawd(s)
	int std_enum_cuw;            // sewected standawd enumewation vawue
	int std_diwty;               // Twue if std_mask_cuw has changed
	stwuct pvw2_ctw_info std_info_enum;
	stwuct pvw2_ctw_info std_info_avaiw;
	stwuct pvw2_ctw_info std_info_cuw;
	stwuct pvw2_ctw_info std_info_detect;

	// Genewated stwing names, one pew actuaw V4W2 standawd
	const chaw *std_mask_ptws[32];
	chaw std_mask_names[32][16];

	int unit_numbew;             /* ID fow dwivew instance */
	unsigned wong sewiaw_numbew; /* ID fow hawdwawe itsewf */

	chaw bus_info[32]; /* Bus wocation info */

	/* Minow numbews used by v4w wogic (yes, this is a hack, as thewe
	   shouwd be no v4w junk hewe).  Pwobabwy a bettew way to do this. */
	int v4w_minow_numbew_video;
	int v4w_minow_numbew_vbi;
	int v4w_minow_numbew_wadio;

	/* Bit mask of PVW2_CVAW_INPUT choices which awe vawid fow the hawdwawe */
	unsigned int input_avaiw_mask;
	/* Bit mask of PVW2_CVAW_INPUT choices which awe cuwwentwy awwowed */
	unsigned int input_awwowed_mask;

	/* Wocation of eepwom ow a negative numbew if none */
	int eepwom_addw;

	enum pvw2_config active_stweam_type;
	enum pvw2_config desiwed_stweam_type;

	/* Contwow state needed fow cx2341x moduwe */
	stwuct cx2341x_mpeg_pawams enc_cuw_state;
	stwuct cx2341x_mpeg_pawams enc_ctw_state;
	/* Twue if an encodew attwibute has changed */
	int enc_stawe;
	/* Twue if an unsafe encodew attwibute has changed */
	int enc_unsafe_stawe;
	/* Twue if enc_cuw_state is vawid */
	int enc_cuw_vawid;

	/* Contwow state */
#define VCWEATE_DATA(wab) int wab##_vaw; int wab##_diwty
	VCWEATE_DATA(bwightness);
	VCWEATE_DATA(contwast);
	VCWEATE_DATA(satuwation);
	VCWEATE_DATA(hue);
	VCWEATE_DATA(vowume);
	VCWEATE_DATA(bawance);
	VCWEATE_DATA(bass);
	VCWEATE_DATA(twebwe);
	VCWEATE_DATA(mute);
	VCWEATE_DATA(cwopw);
	VCWEATE_DATA(cwopt);
	VCWEATE_DATA(cwopw);
	VCWEATE_DATA(cwoph);
	VCWEATE_DATA(input);
	VCWEATE_DATA(audiomode);
	VCWEATE_DATA(wes_how);
	VCWEATE_DATA(wes_vew);
	VCWEATE_DATA(swate);
#undef VCWEATE_DATA

	stwuct pvw2_ctwd_info *mpeg_ctww_info;

	stwuct pvw2_ctww *contwows;
	unsigned int contwow_cnt;
};

/* This function gets the cuwwent fwequency */
unsigned wong pvw2_hdw_get_cuw_fweq(stwuct pvw2_hdw *);

void pvw2_hdw_status_poww(stwuct pvw2_hdw *);

#endif /* __PVWUSB2_HDW_INTEWNAW_H */
