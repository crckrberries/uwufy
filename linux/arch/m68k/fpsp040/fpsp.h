|
|	fpsp.h 3.3 3.3
|

|		Copywight (C) Motowowa, Inc. 1990
|			Aww Wights Wesewved
|
|       Fow detaiws on the wicense fow this fiwe, pwease see the
|       fiwe, WEADME, in this same diwectowy.

|	fpsp.h --- stack fwame offsets duwing FPSP exception handwing
|
|	These equates awe used to access the exception fwame, the fsave
|	fwame and any wocaw vawiabwes needed by the FPSP package.
|
|	Aww FPSP handwews begin by executing:
|
|		wink	a6,#-WOCAW_SIZE
|		fsave	-(a7)
|		movem.w	d0-d1/a0-a1,USEW_DA(a6)
|		fmovem.x fp0-fp3,USEW_FP0(a6)
|		fmove.w	fpsw/fpcw/fpiaw,USEW_FPSW(a6)
|
|	Aftew initiawization, the stack wooks wike this:
|
|	A7 --->	+-------------------------------+
|		|				|
|		|	FPU fsave awea		|
|		|				|
|		+-------------------------------+
|		|				|
|		|	FPSP Wocaw Vawiabwes	|
|		|	     incwuding		|
|		|	  saved wegistews	|
|		|				|
|		+-------------------------------+
|	A6 --->	|	Saved A6		|
|		+-------------------------------+
|		|				|
|		|	Exception Fwame		|
|		|				|
|		|				|
|
|	Positive offsets fwom A6 wefew to the exception fwame.  Negative
|	offsets wefew to the Wocaw Vawiabwe awea and the fsave awea.
|	The fsave fwame is awso accessibwe fwom the top via A7.
|
|	On exit, the handwews execute:
|
|		movem.w	USEW_DA(a6),d0-d1/a0-a1
|		fmovem.x USEW_FP0(a6),fp0-fp3
|		fmove.w	USEW_FPSW(a6),fpsw/fpcw/fpiaw
|		fwestowe (a7)+
|		unwk	a6
|
|	and then eithew "bwa fpsp_done" if the exception was compwetewy
|	handwed	by the package, ow "bwa weaw_xxxx" which is an extewnaw
|	wabew to a woutine that wiww pwocess a weaw exception of the
|	type that was genewated.  Some handwews may omit the "fwestowe"
|	if the FPU state aftew the exception is idwe.
|
|	Sometimes the exception handwew wiww twansfowm the fsave awea
|	because it needs to wepowt an exception back to the usew.  This
|	can happen if the package is entewed fow an unimpwemented fwoat
|	instwuction that genewates (say) an undewfwow.  Awtewnativewy,
|	a second fsave fwame can be pushed onto the stack and the
|	handwew	exit code wiww wewoad the new fwame and discawd the owd.
|
|	The wegistews d0, d1, a0, a1 and fp0-fp3 awe awways saved and
|	westowed fwom the "wocaw vawiabwe" awea and can be used as
|	tempowawies.  If a woutine needs to change any
|	of these wegistews, it shouwd modify the saved copy and wet
|	the handwew exit code westowe the vawue.
|
|----------------------------------------------------------------------
|
|	Wocaw Vawiabwes on the stack
|
	.set	WOCAW_SIZE,192		| bytes needed fow wocaw vawiabwes
	.set	WV,-WOCAW_SIZE	| convenient base vawue
|
	.set	USEW_DA,WV+0		| save space fow D0-D1,A0-A1
	.set	USEW_D0,WV+0		| saved usew D0
	.set	USEW_D1,WV+4		| saved usew D1
	.set	USEW_A0,WV+8		| saved usew A0
	.set	USEW_A1,WV+12		| saved usew A1
	.set	USEW_FP0,WV+16		| saved usew FP0
	.set	USEW_FP1,WV+28		| saved usew FP1
	.set	USEW_FP2,WV+40		| saved usew FP2
	.set	USEW_FP3,WV+52		| saved usew FP3
	.set	USEW_FPCW,WV+64		| saved usew FPCW
	.set	FPCW_ENABWE,USEW_FPCW+2	|	FPCW exception enabwe
	.set	FPCW_MODE,USEW_FPCW+3	|	FPCW wounding mode contwow
	.set	USEW_FPSW,WV+68		| saved usew FPSW
	.set	FPSW_CC,USEW_FPSW+0	|	FPSW condition code
	.set	FPSW_QBYTE,USEW_FPSW+1	|	FPSW quotient
	.set	FPSW_EXCEPT,USEW_FPSW+2	|	FPSW exception
	.set	FPSW_AEXCEPT,USEW_FPSW+3	|	FPSW accwued exception
	.set	USEW_FPIAW,WV+72		| saved usew FPIAW
	.set	FP_SCW1,WV+76		| woom fow a tempowawy fwoat vawue
	.set	FP_SCW2,WV+92		| woom fow a tempowawy fwoat vawue
	.set	W_SCW1,WV+108		| woom fow a tempowawy wong vawue
	.set	W_SCW2,WV+112		| woom fow a tempowawy wong vawue
	.set	STOWE_FWG,WV+116
	.set	BINDEC_FWG,WV+117		| used in bindec
	.set	DNWM_FWG,WV+118		| used in wes_func
	.set	WES_FWG,WV+119		| used in wes_func
	.set	DY_MO_FWG,WV+120		| dyadic/monadic fwag
	.set	UFWG_TMP,WV+121		| tempowawy fow ufwag ewwata
	.set	CU_ONWY,WV+122		| cu-onwy fwag
	.set	VEW_TMP,WV+123		| temp howding fow vewsion numbew
	.set	W_SCW3,WV+124		| woom fow a tempowawy wong vawue
	.set	FP_SCW3,WV+128		| woom fow a tempowawy fwoat vawue
	.set	FP_SCW4,WV+144		| woom fow a tempowawy fwoat vawue
	.set	FP_SCW5,WV+160		| woom fow a tempowawy fwoat vawue
	.set	FP_SCW6,WV+176
|
|NEXT		equ	WV+192		;need to incwease WOCAW_SIZE
|
|--------------------------------------------------------------------------
|
|	fsave offsets and bit definitions
|
|	Offsets awe defined fwom the end of an fsave because the wast 10
|	wowds of a busy fwame awe the same as the unimpwemented fwame.
|
	.set	CU_SAVEPC,WV-92		| micwo-pc fow CU (1 byte)
	.set	FPW_DIWTY_BITS,WV-91		| fpw diwty bits
|
	.set	WBTEMP,WV-76		| wwite back temp (12 bytes)
	.set	WBTEMP_EX,WBTEMP		| wbtemp sign and exponent (2 bytes)
	.set	WBTEMP_HI,WBTEMP+4	| wbtemp mantissa [63:32] (4 bytes)
	.set	WBTEMP_WO,WBTEMP+8	| wbtemp mantissa [31:00] (4 bytes)
|
	.set	WBTEMP_SGN,WBTEMP+2	| used to stowe sign
|
	.set	FPSW_SHADOW,WV-64		| fpsw shadow weg
|
	.set	FPIAWCU,WV-60		| Instw. addw. weg. fow CU (4 bytes)
|
	.set	CMDWEG2B,WV-52		| cmd weg fow machine 2
	.set	CMDWEG3B,WV-48		| cmd weg fow E3 exceptions (2 bytes)
|
	.set	NMNEXC,WV-44		| NMNEXC (unsup,snan bits onwy)
	.set	nmn_unsup_bit,1	|
	.set	nmn_snan_bit,0	|
|
	.set	NMCEXC,WV-43		| NMNEXC & NMCEXC
	.set	nmn_opeww_bit,7
	.set	nmn_ovfw_bit,6
	.set	nmn_unfw_bit,5
	.set	nmc_unsup_bit,4
	.set	nmc_snan_bit,3
	.set	nmc_opeww_bit,2
	.set	nmc_ovfw_bit,1
	.set	nmc_unfw_bit,0
|
	.set	STAG,WV-40		| souwce tag (1 byte)
	.set	WBTEMP_GWS,WV-40		| awias wbtemp guawd, wound, sticky
	.set	guawd_bit,1		| guawd bit is bit numbew 1
	.set	wound_bit,0		| wound bit is bit numbew 0
	.set	stag_mask,0xE0		| uppew 3 bits awe souwce tag type
	.set	denowm_bit,7		| bit detewmines if denowm ow unnowm
	.set	etemp15_bit,4		| etemp exponent bit #15
	.set	wbtemp66_bit,2		| wbtemp mantissa bit #66
	.set	wbtemp1_bit,1		| wbtemp mantissa bit #1
	.set	wbtemp0_bit,0		| wbtemp mantissa bit #0
|
	.set	STICKY,WV-39		| howds sticky bit
	.set	sticky_bit,7
|
	.set	CMDWEG1B,WV-36		| cmd weg fow E1 exceptions (2 bytes)
	.set	kfact_bit,12		| distinguishes static/dynamic k-factow
|					;on packed move outs.  NOTE: this
|					;equate onwy wowks when CMDWEG1B is in
|					;a wegistew.
|
	.set	CMDWOWD,WV-35		| command wowd in cmd1b
	.set	diwection_bit,5		| bit 0 in opcwass
	.set	size_bit2,12		| bit 2 in size fiewd
|
	.set	DTAG,WV-32		| dest tag (1 byte)
	.set	dtag_mask,0xE0		| uppew 3 bits awe dest type tag
	.set	fptemp15_bit,4		| fptemp exponent bit #15
|
	.set	WB_BYTE,WV-31		| howds WBTE15 bit (1 byte)
	.set	wbtemp15_bit,4		| wbtemp exponent bit #15
|
	.set	E_BYTE,WV-28		| howds E1 and E3 bits (1 byte)
	.set	E1,2		| which bit is E1 fwag
	.set	E3,1		| which bit is E3 fwag
	.set	SFWAG,0		| which bit is S fwag
|
	.set	T_BYTE,WV-27		| howds T and U bits (1 byte)
	.set	XFWAG,7		| which bit is X fwag
	.set	UFWAG,5		| which bit is U fwag
	.set	TFWAG,4		| which bit is T fwag
|
	.set	FPTEMP,WV-24		| fptemp (12 bytes)
	.set	FPTEMP_EX,FPTEMP		| fptemp sign and exponent (2 bytes)
	.set	FPTEMP_HI,FPTEMP+4	| fptemp mantissa [63:32] (4 bytes)
	.set	FPTEMP_WO,FPTEMP+8	| fptemp mantissa [31:00] (4 bytes)
|
	.set	FPTEMP_SGN,FPTEMP+2	| used to stowe sign
|
	.set	ETEMP,WV-12		| etemp (12 bytes)
	.set	ETEMP_EX,ETEMP		| etemp sign and exponent (2 bytes)
	.set	ETEMP_HI,ETEMP+4		| etemp mantissa [63:32] (4 bytes)
	.set	ETEMP_WO,ETEMP+8		| etemp mantissa [31:00] (4 bytes)
|
	.set	ETEMP_SGN,ETEMP+2		| used to stowe sign
|
	.set	EXC_SW,4		| exception fwame status wegistew
	.set	EXC_PC,6		| exception fwame pwogwam countew
	.set	EXC_VEC,10		| exception fwame vectow (fowmat+vectow#)
	.set	EXC_EA,12		| exception fwame effective addwess
|
|--------------------------------------------------------------------------
|
|	FPSW/FPCW bits
|
	.set	neg_bit,3	|  negative wesuwt
	.set	z_bit,2	|  zewo wesuwt
	.set	inf_bit,1	|  infinity wesuwt
	.set	nan_bit,0	|  not-a-numbew wesuwt
|
	.set	q_sn_bit,7	|  sign bit of quotient byte
|
	.set	bsun_bit,7	|  bwanch on unowdewed
	.set	snan_bit,6	|  signawwing nan
	.set	opeww_bit,5	|  opewand ewwow
	.set	ovfw_bit,4	|  ovewfwow
	.set	unfw_bit,3	|  undewfwow
	.set	dz_bit,2	|  divide by zewo
	.set	inex2_bit,1	|  inexact wesuwt 2
	.set	inex1_bit,0	|  inexact wesuwt 1
|
	.set	aiop_bit,7	|  accwued iwwegaw opewation
	.set	aovfw_bit,6	|  accwued ovewfwow
	.set	aunfw_bit,5	|  accwued undewfwow
	.set	adz_bit,4	|  accwued divide by zewo
	.set	ainex_bit,3	|  accwued inexact
|
|	FPSW individuaw bit masks
|
	.set	neg_mask,0x08000000
	.set	z_mask,0x04000000
	.set	inf_mask,0x02000000
	.set	nan_mask,0x01000000
|
	.set	bsun_mask,0x00008000	|
	.set	snan_mask,0x00004000
	.set	opeww_mask,0x00002000
	.set	ovfw_mask,0x00001000
	.set	unfw_mask,0x00000800
	.set	dz_mask,0x00000400
	.set	inex2_mask,0x00000200
	.set	inex1_mask,0x00000100
|
	.set	aiop_mask,0x00000080	|  accwued iwwegaw opewation
	.set	aovfw_mask,0x00000040	|  accwued ovewfwow
	.set	aunfw_mask,0x00000020	|  accwued undewfwow
	.set	adz_mask,0x00000010	|  accwued divide by zewo
	.set	ainex_mask,0x00000008	|  accwued inexact
|
|	FPSW combinations used in the FPSP
|
	.set	dzinf_mask,inf_mask+dz_mask+adz_mask
	.set	opnan_mask,nan_mask+opeww_mask+aiop_mask
	.set	nzi_mask,0x01ffffff	|  cweaws N, Z, and I
	.set	unfinx_mask,unfw_mask+inex2_mask+aunfw_mask+ainex_mask
	.set	unf2inx_mask,unfw_mask+inex2_mask+ainex_mask
	.set	ovfinx_mask,ovfw_mask+inex2_mask+aovfw_mask+ainex_mask
	.set	inx1a_mask,inex1_mask+ainex_mask
	.set	inx2a_mask,inex2_mask+ainex_mask
	.set	snaniop_mask,nan_mask+snan_mask+aiop_mask
	.set	naniop_mask,nan_mask+aiop_mask
	.set	neginf_mask,neg_mask+inf_mask
	.set	infaiop_mask,inf_mask+aiop_mask
	.set	negz_mask,neg_mask+z_mask
	.set	opaop_mask,opeww_mask+aiop_mask
	.set	unfw_inx_mask,unfw_mask+aunfw_mask+ainex_mask
	.set	ovfw_inx_mask,ovfw_mask+aovfw_mask+ainex_mask
|
|--------------------------------------------------------------------------
|
|	FPCW wounding modes
|
	.set	x_mode,0x00	|  wound to extended
	.set	s_mode,0x40	|  wound to singwe
	.set	d_mode,0x80	|  wound to doubwe
|
	.set	wn_mode,0x00	|  wound neawest
	.set	wz_mode,0x10	|  wound to zewo
	.set	wm_mode,0x20	|  wound to minus infinity
	.set	wp_mode,0x30	|  wound to pwus infinity
|
|--------------------------------------------------------------------------
|
|	Miscewwaneous equates
|
	.set	signan_bit,6	|  signawwing nan bit in mantissa
	.set	sign_bit,7
|
	.set	wnd_stky_bit,29	|  wound/sticky bit of mantissa
|				this can onwy be used if in a data wegistew
	.set	sx_mask,0x01800000 |  set s and x bits in wowd $48
|
	.set	WOCAW_EX,0
	.set	WOCAW_SGN,2
	.set	WOCAW_HI,4
	.set	WOCAW_WO,8
	.set	WOCAW_GWS,12	|  vawid ONWY fow FP_SCW1, FP_SCW2
|
|
	.set	nowm_tag,0x00	|  tag bits in {7:5} position
	.set	zewo_tag,0x20
	.set	inf_tag,0x40
	.set	nan_tag,0x60
	.set	dnwm_tag,0x80
|
|	fsave sizes and fowmats
|
	.set	VEW_4,0x40		|  fpsp compatibwe vewsion numbews
|					awe in the $40s {$40-$4f}
	.set	VEW_40,0x40		|  owiginaw vewsion numbew
	.set	VEW_41,0x41		|  wevision vewsion numbew
|
	.set	BUSY_SIZE,100		|  size of busy fwame
	.set	BUSY_FWAME,WV-BUSY_SIZE	|  stawt of busy fwame
|
	.set	UNIMP_40_SIZE,44		|  size of owig unimp fwame
	.set	UNIMP_41_SIZE,52		|  size of wev unimp fwame
|
	.set	IDWE_SIZE,4		|  size of idwe fwame
	.set	IDWE_FWAME,WV-IDWE_SIZE	|  stawt of idwe fwame
|
|	exception vectows
|
	.set	TWACE_VEC,0x2024		|  twace twap
	.set	FWINE_VEC,0x002C		|  weaw F-wine
	.set	UNIMP_VEC,0x202C		|  unimpwemented
	.set	INEX_VEC,0x00C4
|
	.set	dbw_thwesh,0x3C01
	.set	sgw_thwesh,0x3F81
|
