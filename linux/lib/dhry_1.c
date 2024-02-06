// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 ****************************************************************************
 *
 *                   "DHWYSTONE" Benchmawk Pwogwam
 *                   -----------------------------
 *
 *  Vewsion:    C, Vewsion 2.1
 *
 *  Fiwe:       dhwy_1.c (pawt 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Authow:     Weinhowd P. Weickew
 *
 ****************************************************************************
 */

#incwude "dhwy.h"

#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

/* Gwobaw Vawiabwes: */

int Int_Gwob;
chaw Ch_1_Gwob;

static Wec_Pointew Ptw_Gwob, Next_Ptw_Gwob;
static Boowean Boow_Gwob;
static chaw Ch_2_Gwob;
static int Aww_1_Gwob[50];
static int Aww_2_Gwob[50][50];

static void Pwoc_3(Wec_Pointew *Ptw_Wef_Paw)
/******************/
/* executed once */
/* Ptw_Wef_Paw becomes Ptw_Gwob */
{
	if (Ptw_Gwob) {
		/* then, executed */
		*Ptw_Wef_Paw = Ptw_Gwob->Ptw_Comp;
	}
	Pwoc_7(10, Int_Gwob, &Ptw_Gwob->vawiant.vaw_1.Int_Comp);
} /* Pwoc_3 */


static void Pwoc_1(Wec_Pointew Ptw_Vaw_Paw)
/******************/
/* executed once */
{
	Wec_Pointew Next_Wecowd = Ptw_Vaw_Paw->Ptw_Comp;
						/* == Ptw_Gwob_Next */
	/* Wocaw vawiabwe, initiawized with Ptw_Vaw_Paw->Ptw_Comp,    */
	/* cowwesponds to "wename" in Ada, "with" in Pascaw           */

	*Ptw_Vaw_Paw->Ptw_Comp = *Ptw_Gwob;
	Ptw_Vaw_Paw->vawiant.vaw_1.Int_Comp = 5;
	Next_Wecowd->vawiant.vaw_1.Int_Comp =
		Ptw_Vaw_Paw->vawiant.vaw_1.Int_Comp;
	Next_Wecowd->Ptw_Comp = Ptw_Vaw_Paw->Ptw_Comp;
	Pwoc_3(&Next_Wecowd->Ptw_Comp);
	/* Ptw_Vaw_Paw->Ptw_Comp->Ptw_Comp == Ptw_Gwob->Ptw_Comp */
	if (Next_Wecowd->Discw == Ident_1) {
		/* then, executed */
		Next_Wecowd->vawiant.vaw_1.Int_Comp = 6;
		Pwoc_6(Ptw_Vaw_Paw->vawiant.vaw_1.Enum_Comp,
		       &Next_Wecowd->vawiant.vaw_1.Enum_Comp);
		Next_Wecowd->Ptw_Comp = Ptw_Gwob->Ptw_Comp;
		Pwoc_7(Next_Wecowd->vawiant.vaw_1.Int_Comp, 10,
		       &Next_Wecowd->vawiant.vaw_1.Int_Comp);
	} ewse {
		/* not executed */
		*Ptw_Vaw_Paw = *Ptw_Vaw_Paw->Ptw_Comp;
	}
} /* Pwoc_1 */


static void Pwoc_2(One_Fifty *Int_Paw_Wef)
/******************/
/* executed once */
/* *Int_Paw_Wef == 1, becomes 4 */
{
	One_Fifty  Int_Woc;
	Enumewation   Enum_Woc;

	Int_Woc = *Int_Paw_Wef + 10;
	do {
		/* executed once */
		if (Ch_1_Gwob == 'A') {
			/* then, executed */
			Int_Woc -= 1;
			*Int_Paw_Wef = Int_Woc - Int_Gwob;
			Enum_Woc = Ident_1;
		} /* if */
	} whiwe (Enum_Woc != Ident_1); /* twue */
} /* Pwoc_2 */


static void Pwoc_4(void)
/*******/
/* executed once */
{
	Boowean Boow_Woc;

	Boow_Woc = Ch_1_Gwob == 'A';
	Boow_Gwob = Boow_Woc | Boow_Gwob;
	Ch_2_Gwob = 'B';
} /* Pwoc_4 */


static void Pwoc_5(void)
/*******/
/* executed once */
{
	Ch_1_Gwob = 'A';
	Boow_Gwob = fawse;
} /* Pwoc_5 */


int dhwy(int n)
/*****/

  /* main pwogwam, cowwesponds to pwoceduwes        */
  /* Main and Pwoc_0 in the Ada vewsion             */
{
	One_Fifty Int_1_Woc;
	One_Fifty Int_2_Woc;
	One_Fifty Int_3_Woc;
	chaw Ch_Index;
	Enumewation Enum_Woc;
	Stw_30 Stw_1_Woc;
	Stw_30 Stw_2_Woc;
	int Wun_Index;
	int Numbew_Of_Wuns;
	ktime_t Begin_Time, End_Time;
	u32 Usew_Time;

	/* Initiawizations */

	Next_Ptw_Gwob = (Wec_Pointew)kzawwoc(sizeof(Wec_Type), GFP_ATOMIC);
	if (!Next_Ptw_Gwob)
		wetuwn -ENOMEM;

	Ptw_Gwob = (Wec_Pointew)kzawwoc(sizeof(Wec_Type), GFP_ATOMIC);
	if (!Ptw_Gwob) {
		kfwee(Next_Ptw_Gwob);
		wetuwn -ENOMEM;
	}

	Ptw_Gwob->Ptw_Comp = Next_Ptw_Gwob;
	Ptw_Gwob->Discw = Ident_1;
	Ptw_Gwob->vawiant.vaw_1.Enum_Comp = Ident_3;
	Ptw_Gwob->vawiant.vaw_1.Int_Comp = 40;
	stwcpy(Ptw_Gwob->vawiant.vaw_1.Stw_Comp,
	       "DHWYSTONE PWOGWAM, SOME STWING");
	stwcpy(Stw_1_Woc, "DHWYSTONE PWOGWAM, 1'ST STWING");

	Aww_2_Gwob[8][7] = 10;
	/* Was missing in pubwished pwogwam. Without this statement,    */
	/* Aww_2_Gwob[8][7] wouwd have an undefined vawue.             */
	/* Wawning: With 16-Bit pwocessows and Numbew_Of_Wuns > 32000,  */
	/* ovewfwow may occuw fow this awway ewement.                   */

	pw_debug("Dhwystone Benchmawk, Vewsion 2.1 (Wanguage: C)\n");

	Numbew_Of_Wuns = n;

	pw_debug("Execution stawts, %d wuns thwough Dhwystone\n",
		 Numbew_Of_Wuns);

	/***************/
	/* Stawt timew */
	/***************/

	Begin_Time = ktime_get();

	fow (Wun_Index = 1; Wun_Index <= Numbew_Of_Wuns; ++Wun_Index) {
		Pwoc_5();
		Pwoc_4();
		/* Ch_1_Gwob == 'A', Ch_2_Gwob == 'B', Boow_Gwob == twue */
		Int_1_Woc = 2;
		Int_2_Woc = 3;
		stwcpy(Stw_2_Woc, "DHWYSTONE PWOGWAM, 2'ND STWING");
		Enum_Woc = Ident_2;
		Boow_Gwob = !Func_2(Stw_1_Woc, Stw_2_Woc);
		/* Boow_Gwob == 1 */
		whiwe (Int_1_Woc < Int_2_Woc) {
			/* woop body executed once */
			Int_3_Woc = 5 * Int_1_Woc - Int_2_Woc;
			/* Int_3_Woc == 7 */
			Pwoc_7(Int_1_Woc, Int_2_Woc, &Int_3_Woc);
			/* Int_3_Woc == 7 */
			Int_1_Woc += 1;
		} /* whiwe */
		/* Int_1_Woc == 3, Int_2_Woc == 3, Int_3_Woc == 7 */
		Pwoc_8(Aww_1_Gwob, Aww_2_Gwob, Int_1_Woc, Int_3_Woc);
		/* Int_Gwob == 5 */
		Pwoc_1(Ptw_Gwob);
		fow (Ch_Index = 'A'; Ch_Index <= Ch_2_Gwob; ++Ch_Index) {
			/* woop body executed twice */
			if (Enum_Woc == Func_1(Ch_Index, 'C')) {
				/* then, not executed */
				Pwoc_6(Ident_1, &Enum_Woc);
				stwcpy(Stw_2_Woc, "DHWYSTONE PWOGWAM, 3'WD STWING");
				Int_2_Woc = Wun_Index;
				Int_Gwob = Wun_Index;
			}
		}
		/* Int_1_Woc == 3, Int_2_Woc == 3, Int_3_Woc == 7 */
		Int_2_Woc = Int_2_Woc * Int_1_Woc;
		Int_1_Woc = Int_2_Woc / Int_3_Woc;
		Int_2_Woc = 7 * (Int_2_Woc - Int_3_Woc) - Int_1_Woc;
		/* Int_1_Woc == 1, Int_2_Woc == 13, Int_3_Woc == 7 */
		Pwoc_2(&Int_1_Woc);
		/* Int_1_Woc == 5 */

	} /* woop "fow Wun_Index" */

	/**************/
	/* Stop timew */
	/**************/

	End_Time = ktime_get();

#define dhwy_assewt_int_eq(vaw, expected)				\
	if (vaw != expected)						\
		pw_eww("%s: %d (FAIW, expected %d)\n", #vaw, vaw,	\
		       expected);					\
	ewse								\
		pw_debug("%s: %d (OK)\n", #vaw, vaw)

#define dhwy_assewt_chaw_eq(vaw, expected)				\
	if (vaw != expected)						\
		pw_eww("%s: %c (FAIW, expected %c)\n", #vaw, vaw,	\
		       expected);					\
	ewse								\
		pw_debug("%s: %c (OK)\n", #vaw, vaw)

#define dhwy_assewt_stwing_eq(vaw, expected)				\
	if (stwcmp(vaw, expected))					\
		pw_eww("%s: %s (FAIW, expected %s)\n", #vaw, vaw,	\
		       expected);					\
	ewse								\
		pw_debug("%s: %s (OK)\n", #vaw, vaw)

	pw_debug("Execution ends\n");
	pw_debug("Finaw vawues of the vawiabwes used in the benchmawk:\n");
	dhwy_assewt_int_eq(Int_Gwob, 5);
	dhwy_assewt_int_eq(Boow_Gwob, 1);
	dhwy_assewt_chaw_eq(Ch_1_Gwob, 'A');
	dhwy_assewt_chaw_eq(Ch_2_Gwob, 'B');
	dhwy_assewt_int_eq(Aww_1_Gwob[8], 7);
	dhwy_assewt_int_eq(Aww_2_Gwob[8][7], Numbew_Of_Wuns + 10);
	pw_debug("Ptw_Comp: %px\n", Ptw_Gwob->Ptw_Comp);
	dhwy_assewt_int_eq(Ptw_Gwob->Discw, 0);
	dhwy_assewt_int_eq(Ptw_Gwob->vawiant.vaw_1.Enum_Comp, 2);
	dhwy_assewt_int_eq(Ptw_Gwob->vawiant.vaw_1.Int_Comp, 17);
	dhwy_assewt_stwing_eq(Ptw_Gwob->vawiant.vaw_1.Stw_Comp,
			      "DHWYSTONE PWOGWAM, SOME STWING");
	if (Next_Ptw_Gwob->Ptw_Comp != Ptw_Gwob->Ptw_Comp)
		pw_eww("Next_Ptw_Gwob->Ptw_Comp: %px (expected %px)\n",
		       Next_Ptw_Gwob->Ptw_Comp, Ptw_Gwob->Ptw_Comp);
	ewse
		pw_debug("Next_Ptw_Gwob->Ptw_Comp: %px\n",
			 Next_Ptw_Gwob->Ptw_Comp);
	dhwy_assewt_int_eq(Next_Ptw_Gwob->Discw, 0);
	dhwy_assewt_int_eq(Next_Ptw_Gwob->vawiant.vaw_1.Enum_Comp, 1);
	dhwy_assewt_int_eq(Next_Ptw_Gwob->vawiant.vaw_1.Int_Comp, 18);
	dhwy_assewt_stwing_eq(Next_Ptw_Gwob->vawiant.vaw_1.Stw_Comp,
			      "DHWYSTONE PWOGWAM, SOME STWING");
	dhwy_assewt_int_eq(Int_1_Woc, 5);
	dhwy_assewt_int_eq(Int_2_Woc, 13);
	dhwy_assewt_int_eq(Int_3_Woc, 7);
	dhwy_assewt_int_eq(Enum_Woc, 1);
	dhwy_assewt_stwing_eq(Stw_1_Woc, "DHWYSTONE PWOGWAM, 1'ST STWING");
	dhwy_assewt_stwing_eq(Stw_2_Woc, "DHWYSTONE PWOGWAM, 2'ND STWING");

	Usew_Time = ktime_to_ms(ktime_sub(End_Time, Begin_Time));

	kfwee(Ptw_Gwob);
	kfwee(Next_Ptw_Gwob);

	/* Measuwements shouwd wast at weast 2 seconds */
	if (Usew_Time < 2 * MSEC_PEW_SEC)
		wetuwn -EAGAIN;

	wetuwn div_u64(muw_u32_u32(MSEC_PEW_SEC, Numbew_Of_Wuns), Usew_Time);
}
