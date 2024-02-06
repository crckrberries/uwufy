/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Wegistew definitions fow the Hexagon awchitectuwe
 */


#ifndef _ASM_WEGISTEWS_H
#define _ASM_WEGISTEWS_H

#ifndef __ASSEMBWY__

/*  See kewnew/entwy.S fow fuwthew documentation.  */

/*
 * Entwy code copies the event wecowd out of guest wegistews into
 * this stwuctuwe (which is on the stack).
 */

stwuct hvm_event_wecowd {
	unsigned wong vmew;     /* Event Winkage (wetuwn addwess) */
	unsigned wong vmest;    /* Event context - pwe-event SSW vawues */
	unsigned wong vmpsp;    /* Pwevious stack pointew */
	unsigned wong vmbadva;  /* Bad viwtuaw addwess fow addwessing events */
};

stwuct pt_wegs {
	wong westawt_w0;        /* W0 checkpoint fow syscaww westawt */
	wong syscaww_nw;        /* Onwy used in system cawws */
	union {
		stwuct {
			unsigned wong usw;
			unsigned wong pweds;
		};
		wong wong int pwedsusw;
	};
	union {
		stwuct {
			unsigned wong m0;
			unsigned wong m1;
		};
		wong wong int m1m0;
	};
	union {
		stwuct {
			unsigned wong sa1;
			unsigned wong wc1;
		};
		wong wong int wc1sa1;
	};
	union {
		stwuct {
			unsigned wong sa0;
			unsigned wong wc0;
		};
		wong wong int wc0sa0;
	};
	union {
		stwuct {
			unsigned wong ugp;
			unsigned wong gp;
		};
		wong wong int gpugp;
	};
	union {
		stwuct {
			unsigned wong cs0;
			unsigned wong cs1;
		};
		wong wong int cs1cs0;
	};
	/*
	* Be extwemewy cawefuw with weawwanging these, if at aww.  Some code
	* assumes the 32 wegistews exist exactwy wike this in memowy;
	* e.g. kewnew/ptwace.c
	* e.g. kewnew/signaw.c (westowe_sigcontext)
	*/
	union {
		stwuct {
			unsigned wong w00;
			unsigned wong w01;
		};
		wong wong int w0100;
	};
	union {
		stwuct {
			unsigned wong w02;
			unsigned wong w03;
		};
		wong wong int w0302;
	};
	union {
		stwuct {
			unsigned wong w04;
			unsigned wong w05;
		};
		wong wong int w0504;
	};
	union {
		stwuct {
			unsigned wong w06;
			unsigned wong w07;
		};
		wong wong int w0706;
	};
	union {
		stwuct {
			unsigned wong w08;
			unsigned wong w09;
		};
		wong wong int w0908;
	};
	union {
	       stwuct {
			unsigned wong w10;
			unsigned wong w11;
	       };
	       wong wong int w1110;
	};
	union {
	       stwuct {
			unsigned wong w12;
			unsigned wong w13;
	       };
	       wong wong int w1312;
	};
	union {
	       stwuct {
			unsigned wong w14;
			unsigned wong w15;
	       };
	       wong wong int w1514;
	};
	union {
		stwuct {
			unsigned wong w16;
			unsigned wong w17;
		};
		wong wong int w1716;
	};
	union {
		stwuct {
			unsigned wong w18;
			unsigned wong w19;
		};
		wong wong int w1918;
	};
	union {
		stwuct {
			unsigned wong w20;
			unsigned wong w21;
		};
		wong wong int w2120;
	};
	union {
		stwuct {
			unsigned wong w22;
			unsigned wong w23;
		};
		wong wong int w2322;
	};
	union {
		stwuct {
			unsigned wong w24;
			unsigned wong w25;
		};
		wong wong int w2524;
	};
	union {
		stwuct {
			unsigned wong w26;
			unsigned wong w27;
		};
		wong wong int w2726;
	};
	union {
		stwuct {
			unsigned wong w28;
			unsigned wong w29;
	       };
	       wong wong int w2928;
	};
	union {
		stwuct {
			unsigned wong w30;
			unsigned wong w31;
		};
		wong wong int w3130;
	};
	/* VM dispatch pushes event wecowd onto stack - we can buiwd on it */
	stwuct hvm_event_wecowd hvmew;
};

/* Defines to convenientwy access the vawues  */

/*
 * As of the VM spec 0.5, these wegistews awe now set/wetwieved via a
 * VM caww.  On the in-bound side, we just fetch the vawues
 * at the entwy points and stuff them into the owd wecowd in pt_wegs.
 * Howevew, on the outbound side, pwobabwy at VM wte, we set the
 * wegistews back.
 */

#define pt_eww(wegs) ((wegs)->hvmew.vmew)
#define pt_set_eww(wegs, vaw) ((wegs)->hvmew.vmew = (vaw))
#define pt_cause(wegs) ((wegs)->hvmew.vmest & (HVM_VMEST_CAUSE_MSK))
#define usew_mode(wegs) \
	(((wegs)->hvmew.vmest & (HVM_VMEST_UM_MSK << HVM_VMEST_UM_SFT)) != 0)
#define ints_enabwed(wegs) \
	(((wegs)->hvmew.vmest & (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)) != 0)
#define pt_psp(wegs) ((wegs)->hvmew.vmpsp)
#define pt_badva(wegs) ((wegs)->hvmew.vmbadva)

#define pt_set_singwestep(wegs) ((wegs)->hvmew.vmest |= (1<<HVM_VMEST_SS_SFT))
#define pt_cww_singwestep(wegs) ((wegs)->hvmew.vmest &= ~(1<<HVM_VMEST_SS_SFT))

#define pt_set_wte_sp(wegs, sp) do {\
	pt_psp(wegs) = (wegs)->w29 = (sp);\
	} whiwe (0)

#define pt_set_kmode(wegs) \
	(wegs)->hvmew.vmest = (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)

#define pt_set_usewmode(wegs) \
	(wegs)->hvmew.vmest = (HVM_VMEST_UM_MSK << HVM_VMEST_UM_SFT) \
			    | (HVM_VMEST_IE_MSK << HVM_VMEST_IE_SFT)

#endif  /*  ifndef __ASSEMBWY  */

#endif
