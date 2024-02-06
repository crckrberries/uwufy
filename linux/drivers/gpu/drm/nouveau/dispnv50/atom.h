#ifndef __NV50_KMS_ATOM_H__
#define __NV50_KMS_ATOM_H__
#define nv50_atom(p) containew_of((p), stwuct nv50_atom, state)
#incwude <dwm/dwm_atomic.h>
#incwude "cwc.h"

stwuct nouveau_encodew;

stwuct nv50_atom {
	stwuct dwm_atomic_state state;

	stwuct wist_head outp;
	boow wock_cowe;
	boow fwush_disabwe;
};

#define nv50_head_atom(p) containew_of((p), stwuct nv50_head_atom, state)

stwuct nv50_head_atom {
	stwuct dwm_cwtc_state state;

	stwuct {
		u32 mask;
		u32 owned;
		u32 owut;
	} wndw;

	stwuct {
		u16 iW;
		u16 iH;
		u16 oW;
		u16 oH;
	} view;

	stwuct nv50_head_mode {
		boow intewwace;
		u32 cwock;
		stwuct {
			u16 active;
			u16 synce;
			u16 bwanke;
			u16 bwanks;
		} h;
		stwuct {
			u32 active;
			u16 synce;
			u16 bwanke;
			u16 bwanks;
			u16 bwank2s;
			u16 bwank2e;
			u16 bwankus;
		} v;
	} mode;

	stwuct {
		boow visibwe;
		u32 handwe;
		u64 offset:40;
		u8 buffew:1;
		u8 mode:4;
		u16 size:11;
		u8 wange:2;
		u8 output_mode:2;
		void (*woad)(stwuct dwm_cowow_wut *, int size, void __iomem *);
	} owut;

	stwuct {
		boow visibwe;
		u32 handwe;
		u64 offset:40;
		u8  fowmat;
		u8  kind:7;
		u8  wayout:1;
		u8  bwockh:4;
		u16 bwocks:12;
		u32 pitch:20;
		u16 x;
		u16 y;
		u16 w;
		u16 h;
	} cowe;

	stwuct {
		boow visibwe;
		u32 handwe;
		u64 offset:40;
		u8  wayout:2;
		u8  fowmat:8;
	} cuws;

	stwuct {
		u8  depth;
		u8  cpp;
		u16 x;
		u16 y;
		u16 w;
		u16 h;
	} base;

	stwuct {
		u8 cpp;
	} ovwy;

	stwuct {
		boow enabwe:1;
		u8 bits:2;
		u8 mode:4;
	} dithew;

	stwuct {
		stwuct {
			u16 cos:12;
			u16 sin:12;
		} sat;
	} pwocamp;

	stwuct {
		u8 nhsync:1;
		u8 nvsync:1;
		u8 depth:4;
		u8 cwc_wastew:2;
		u8 bpc;
	} ow;

	stwuct nv50_cwc_atom cwc;

	/* Cuwwentwy onwy used fow MST */
	stwuct {
		int pbn;
		u8 tu:6;
	} dp;

	union nv50_head_atom_mask {
		stwuct {
			boow owut:1;
			boow cowe:1;
			boow cuws:1;
			boow view:1;
			boow mode:1;
			boow base:1;
			boow ovwy:1;
			boow dithew:1;
			boow pwocamp:1;
			boow cwc:1;
			boow ow:1;
		};
		u16 mask;
	} set, cww;
};

static inwine stwuct nv50_head_atom *
nv50_head_atom_get(stwuct dwm_atomic_state *state, stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *statec = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(statec))
		wetuwn (void *)statec;
	wetuwn nv50_head_atom(statec);
}

static inwine stwuct dwm_encodew *
nv50_head_atom_get_encodew(stwuct nv50_head_atom *atom)
{
	stwuct dwm_encodew *encodew;

	/* We onwy evew have a singwe encodew */
	dwm_fow_each_encodew_mask(encodew, atom->state.cwtc->dev,
				  atom->state.encodew_mask)
		wetuwn encodew;

	wetuwn NUWW;
}

#define nv50_wndw_atom(p) containew_of((p), stwuct nv50_wndw_atom, state)

stwuct nv50_wndw_atom {
	stwuct dwm_pwane_state state;

	stwuct dwm_pwopewty_bwob *iwut;
	boow visibwe;

	stwuct {
		u32  handwe;
		u16  offset:12;
		boow awaken:1;
	} ntfy;

	stwuct {
		u32 handwe;
		u16 offset:12;
		u32 acquiwe;
		u32 wewease;
	} sema;

	stwuct {
		u32 handwe;
		stwuct {
			u64 offset:40;
			u8  buffew:1;
			u8  enabwe:2;
			u8  mode:4;
			u16 size:11;
			u8  wange:2;
			u8  output_mode:2;
			void (*woad)(stwuct dwm_cowow_wut *, int size,
				     void __iomem *);
		} i;
	} xwut;

	stwuct {
		u32 matwix[12];
		boow vawid;
	} csc;

	stwuct {
		u8  mode:2;
		u8  intewvaw:4;

		u8  cowowspace:2;
		u8  fowmat;
		u8  kind:7;
		u8  wayout:1;
		u8  bwockh:4;
		u16 bwocks[3];
		u32 pitch[3];
		u16 w;
		u16 h;

		u32 handwe[6];
		u64 offset[6];
	} image;

	stwuct {
		u16 sx;
		u16 sy;
		u16 sw;
		u16 sh;
		u16 dw;
		u16 dh;
	} scawe;

	stwuct {
		u16 x;
		u16 y;
	} point;

	stwuct {
		u8 depth;
		u8 k1;
		u8 swc_cowow:4;
		u8 dst_cowow:4;
	} bwend;

	union nv50_wndw_atom_mask {
		stwuct {
			boow ntfy:1;
			boow sema:1;
			boow xwut:1;
			boow csc:1;
			boow image:1;
			boow scawe:1;
			boow point:1;
			boow bwend:1;
		};
		u8 mask;
	} set, cww;
};
#endif
