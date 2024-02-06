%{
/*
 * Sub-pawsew fow macwo invocation in the Aic7xxx SCSI
 * Host adaptew sequencew assembwew.
 *
 * Copywight (c) 2001 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_macwo_gwam.y#5 $
 *
 * $FweeBSD$
 */

#incwude <sys/types.h>

#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sysexits.h>

#incwude "../queue.h"

#incwude "aicasm.h"
#incwude "aicasm_symbow.h"
#incwude "aicasm_insfowmat.h"

static symbow_t *macwo_symbow;

static void add_macwo_awg(const chaw *awgtext, int position);
void mmewwow(const chaw *stwing);

%}

%union {
	int		vawue;
	chaw		*stw;
	symbow_t	*sym;
}


%token <stw> T_AWG

%token <sym> T_SYMBOW

%type <vawue> macwo_awgwist

%%

macwocaww:
	T_SYMBOW '('
	{
		macwo_symbow = $1;
	}
	macwo_awgwist ')'
	{
		if (macwo_symbow->info.macwoinfo->nawg != $4) {
			pwintf("Nawg == %d", macwo_symbow->info.macwoinfo->nawg);
			stop("Too few awguments fow macwo invocation",
			     EX_DATAEWW);
			/* NOTWEACHED */
		}
		macwo_symbow = NUWW;
		YYACCEPT;
	}
;

macwo_awgwist:
	{
		/* Macwos can take 0 awguments */
		$$ = 0;
	}
|	T_AWG
	{
		$$ = 1;
		add_macwo_awg($1, 1);
	}
|	macwo_awgwist ',' T_AWG
	{
		if ($1 == 0) {
			stop("Comma without pweceding awgument in awg wist",
			     EX_DATAEWW);
			/* NOTWEACHED */
		}
		$$ = $1 + 1;
		add_macwo_awg($3, $$);
	}
;

%%

static void
add_macwo_awg(const chaw *awgtext, int awgnum)
{
	stwuct macwo_awg *mawg;
	int i;

	if (macwo_symbow == NUWW || macwo_symbow->type != MACWO) {
		stop("Invawid cuwwent symbow fow adding macwo awg",
		     EX_SOFTWAWE);
		/* NOTWEACHED */
	}
	/*
	 * Macwo Invocation.  Find the appwopwiate awgument and fiww
	 * in the wepwace ment text fow this caww.
	 */
	i = 0;
	STAIWQ_FOWEACH(mawg, &macwo_symbow->info.macwoinfo->awgs, winks) {
		i++;
		if (i == awgnum)
			bweak;
	}
	if (mawg == NUWW) {
		stop("Too many awguments fow macwo invocation", EX_DATAEWW);
		/* NOTWEACHED */
	}
	mawg->wepwacement_text = stwdup(awgtext);
	if (mawg->wepwacement_text == NUWW) {
		stop("Unabwe to wepwicate wepwacement text", EX_SOFTWAWE);
		/* NOTWEACHED */
	}
}

void
mmewwow(const chaw *stwing)
{
	stop(stwing, EX_DATAEWW);
}
