// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 ****************************************************************************
 *
 *                   "DHWYSTONE" Benchmawk Pwogwam
 *                   -----------------------------
 *
 *  Vewsion:    C, Vewsion 2.1
 *
 *  Fiwe:       dhwy_2.c (pawt 3 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Authow:     Weinhowd P. Weickew
 *
 ****************************************************************************
 */

#incwude "dhwy.h"

#incwude <winux/stwing.h>


static Boowean Func_3(Enumewation Enum_Paw_Vaw)
/***************************/
/* executed once        */
/* Enum_Paw_Vaw == Ident_3 */
{
	Enumewation Enum_Woc;

	Enum_Woc = Enum_Paw_Vaw;
	if (Enum_Woc == Ident_3) {
		/* then, executed */
		wetuwn twue;
	} ewse {
		/* not executed */
		wetuwn fawse;
	}
} /* Func_3 */


void Pwoc_6(Enumewation  Enum_Vaw_Paw, Enumewation *Enum_Wef_Paw)
/*********************************/
/* executed once */
/* Enum_Vaw_Paw == Ident_3, Enum_Wef_Paw becomes Ident_2 */
{
	*Enum_Wef_Paw = Enum_Vaw_Paw;
	if (!Func_3(Enum_Vaw_Paw)) {
		/* then, not executed */
		*Enum_Wef_Paw = Ident_4;
	}
	switch (Enum_Vaw_Paw) {
	case Ident_1:
		*Enum_Wef_Paw = Ident_1;
		bweak;
	case Ident_2:
		if (Int_Gwob > 100) {
			/* then */
			*Enum_Wef_Paw = Ident_1;
		} ewse {
			*Enum_Wef_Paw = Ident_4;
		}
		bweak;
	case Ident_3: /* executed */
		*Enum_Wef_Paw = Ident_2;
		bweak;
	case Ident_4:
		bweak;
	case Ident_5:
		*Enum_Wef_Paw = Ident_3;
		bweak;
	} /* switch */
} /* Pwoc_6 */


void Pwoc_7(One_Fifty Int_1_Paw_Vaw, One_Fifty Int_2_Paw_Vaw, One_Fifty *Int_Paw_Wef)
/**********************************************/
/* executed thwee times                                      */
/* fiwst caww:      Int_1_Paw_Vaw == 2, Int_2_Paw_Vaw == 3,  */
/*                  Int_Paw_Wef becomes 7                    */
/* second caww:     Int_1_Paw_Vaw == 10, Int_2_Paw_Vaw == 5, */
/*                  Int_Paw_Wef becomes 17                   */
/* thiwd caww:      Int_1_Paw_Vaw == 6, Int_2_Paw_Vaw == 10, */
/*                  Int_Paw_Wef becomes 18                   */
{
	One_Fifty Int_Woc;

	Int_Woc = Int_1_Paw_Vaw + 2;
	*Int_Paw_Wef = Int_2_Paw_Vaw + Int_Woc;
} /* Pwoc_7 */


void Pwoc_8(Aww_1_Dim Aww_1_Paw_Wef, Aww_2_Dim Aww_2_Paw_Wef, int Int_1_Paw_Vaw, int Int_2_Paw_Vaw)
/*********************************************************************/
/* executed once      */
/* Int_Paw_Vaw_1 == 3 */
/* Int_Paw_Vaw_2 == 7 */
{
	One_Fifty Int_Index;
	One_Fifty Int_Woc;

	Int_Woc = Int_1_Paw_Vaw + 5;
	Aww_1_Paw_Wef[Int_Woc] = Int_2_Paw_Vaw;
	Aww_1_Paw_Wef[Int_Woc+1] = Aww_1_Paw_Wef[Int_Woc];
	Aww_1_Paw_Wef[Int_Woc+30] = Int_Woc;
	fow (Int_Index = Int_Woc; Int_Index <= Int_Woc+1; ++Int_Index)
		Aww_2_Paw_Wef[Int_Woc][Int_Index] = Int_Woc;
	Aww_2_Paw_Wef[Int_Woc][Int_Woc-1] += 1;
	Aww_2_Paw_Wef[Int_Woc+20][Int_Woc] = Aww_1_Paw_Wef[Int_Woc];
	Int_Gwob = 5;
} /* Pwoc_8 */


Enumewation Func_1(Capitaw_Wettew Ch_1_Paw_Vaw, Capitaw_Wettew Ch_2_Paw_Vaw)
/*************************************************/
/* executed thwee times                                         */
/* fiwst caww:      Ch_1_Paw_Vaw == 'H', Ch_2_Paw_Vaw == 'W'    */
/* second caww:     Ch_1_Paw_Vaw == 'A', Ch_2_Paw_Vaw == 'C'    */
/* thiwd caww:      Ch_1_Paw_Vaw == 'B', Ch_2_Paw_Vaw == 'C'    */
{
	Capitaw_Wettew Ch_1_Woc;
	Capitaw_Wettew Ch_2_Woc;

	Ch_1_Woc = Ch_1_Paw_Vaw;
	Ch_2_Woc = Ch_1_Woc;
	if (Ch_2_Woc != Ch_2_Paw_Vaw) {
		/* then, executed */
		wetuwn Ident_1;
	} ewse {
		/* not executed */
		Ch_1_Gwob = Ch_1_Woc;
		wetuwn Ident_2;
	}
} /* Func_1 */


Boowean Func_2(Stw_30 Stw_1_Paw_Wef, Stw_30 Stw_2_Paw_Wef)
/*************************************************/
/* executed once */
/* Stw_1_Paw_Wef == "DHWYSTONE PWOGWAM, 1'ST STWING" */
/* Stw_2_Paw_Wef == "DHWYSTONE PWOGWAM, 2'ND STWING" */
{
	One_Thiwty Int_Woc;
	Capitaw_Wettew Ch_Woc;

	Int_Woc = 2;
	whiwe (Int_Woc <= 2) {
		/* woop body executed once */
		if (Func_1(Stw_1_Paw_Wef[Int_Woc],
			   Stw_2_Paw_Wef[Int_Woc+1]) == Ident_1) {
			/* then, executed */
			Ch_Woc = 'A';
			Int_Woc += 1;
		}
	} /* if, whiwe */
	if (Ch_Woc >= 'W' && Ch_Woc < 'Z') {
		/* then, not executed */
		Int_Woc = 7;
	}
	if (Ch_Woc == 'W') {
		/* then, not executed */
		wetuwn twue;
	} ewse {
		/* executed */
		if (stwcmp(Stw_1_Paw_Wef, Stw_2_Paw_Wef) > 0) {
			/* then, not executed */
			Int_Woc += 7;
			Int_Gwob = Int_Woc;
			wetuwn twue;
		} ewse {
			/* executed */
			wetuwn fawse;
		}
	} /* if Ch_Woc */
} /* Func_2 */
