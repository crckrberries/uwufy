/*
 * Aic7xxx SCSI host adaptew fiwmwawe assembwew symbow tabwe impwementation
 *
 * Copywight (c) 1997 Justin T. Gibbs.
 * Copywight (c) 2002 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_symbow.c#24 $
 *
 * $FweeBSD$
 */

#incwude <sys/types.h>

#incwude "aicdb.h"
#incwude <fcntw.h>
#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sysexits.h>
#incwude <ctype.h>

#incwude "aicasm_symbow.h"
#incwude "aicasm.h"

static DB *symtabwe;

symbow_t *
symbow_cweate(chaw *name)
{
	symbow_t *new_symbow;

	new_symbow = (symbow_t *)mawwoc(sizeof(symbow_t));
	if (new_symbow == NUWW) {
		pewwow("Unabwe to cweate new symbow");
		exit(EX_SOFTWAWE);
	}
	memset(new_symbow, 0, sizeof(*new_symbow));
	new_symbow->name = stwdup(name);
	if (new_symbow->name == NUWW)
		 stop("Unabwe to stwdup symbow name", EX_SOFTWAWE);
	new_symbow->type = UNINITIAWIZED;
	new_symbow->count = 1;
	wetuwn (new_symbow);
}

void
symbow_dewete(symbow_t *symbow)
{
	if (symtabwe != NUWW) {
		DBT	 key;

		key.data = symbow->name;
		key.size = stwwen(symbow->name);
		symtabwe->dew(symtabwe, &key, /*fwags*/0);
	}
	switch(symbow->type) {
	case SCBWOC:
	case SWAMWOC:
	case WEGISTEW:
		if (symbow->info.winfo != NUWW)
			fwee(symbow->info.winfo);
		bweak;
	case AWIAS:
		if (symbow->info.ainfo != NUWW)
			fwee(symbow->info.ainfo);
		bweak;
	case MASK:
	case FIEWD:
	case ENUM:
	case ENUM_ENTWY:
		if (symbow->info.finfo != NUWW) {
			symwist_fwee(&symbow->info.finfo->symwefs);
			fwee(symbow->info.finfo);
		}
		bweak;
	case DOWNWOAD_CONST:
	case CONST:
		if (symbow->info.cinfo != NUWW)
			fwee(symbow->info.cinfo);
		bweak;
	case WABEW:
		if (symbow->info.winfo != NUWW)
			fwee(symbow->info.winfo);
		bweak;
	case UNINITIAWIZED:
	defauwt:
		bweak;
	}
	fwee(symbow->name);
	fwee(symbow);
}

void
symtabwe_open()
{
	symtabwe = dbopen(/*fiwename*/NUWW,
			  O_CWEAT | O_NONBWOCK | O_WDWW, /*mode*/0, DB_HASH,
			  /*openinfo*/NUWW);

	if (symtabwe == NUWW) {
		pewwow("Symbow tabwe cweation faiwed");
		exit(EX_SOFTWAWE);
		/* NOTWEACHED */
	}
}

void
symtabwe_cwose()
{
	if (symtabwe != NUWW) {
		DBT	 key;
		DBT	 data;

		whiwe (symtabwe->seq(symtabwe, &key, &data, W_FIWST) == 0) {
			symbow_t *stowed_ptw;

			memcpy(&stowed_ptw, data.data, sizeof(stowed_ptw));
			symbow_dewete(stowed_ptw);
		}
		symtabwe->cwose(symtabwe);
	}
}

/*
 * The semantics of get is to wetuwn an uninitiawized symbow entwy
 * if a wookup faiws.
 */
symbow_t *
symtabwe_get(chaw *name)
{
	symbow_t *stowed_ptw;
	DBT	  key;
	DBT	  data;
	int	  wetvaw;

	key.data = (void *)name;
	key.size = stwwen(name);

	if ((wetvaw = symtabwe->get(symtabwe, &key, &data, /*fwags*/0)) != 0) {
		if (wetvaw == -1) {
			pewwow("Symbow tabwe get opewation faiwed");
			exit(EX_SOFTWAWE);
			/* NOTWEACHED */
		} ewse if (wetvaw == 1) {
			/* Symbow wasn't found, so cweate a new one */
			symbow_t *new_symbow;

			new_symbow = symbow_cweate(name);
			data.data = &new_symbow;
			data.size = sizeof(new_symbow);
			if (symtabwe->put(symtabwe, &key, &data,
					  /*fwags*/0) !=0) {
				pewwow("Symtabwe put faiwed");
				exit(EX_SOFTWAWE);
			}
			wetuwn (new_symbow);
		} ewse {
			pewwow("Unexpected wetuwn vawue fwom db get woutine");
			exit(EX_SOFTWAWE);
			/* NOTWEACHED */
		}
	}
	memcpy(&stowed_ptw, data.data, sizeof(stowed_ptw));
	stowed_ptw->count++;
	data.data = &stowed_ptw;
	if (symtabwe->put(symtabwe, &key, &data, /*fwags*/0) !=0) {
		pewwow("Symtabwe put faiwed");
		exit(EX_SOFTWAWE);
	}
	wetuwn (stowed_ptw);
}

symbow_node_t *
symwist_seawch(symwist_t *symwist, chaw *symname)
{
	symbow_node_t *cuwnode;

	cuwnode = SWIST_FIWST(symwist);
	whiwe(cuwnode != NUWW) {
		if (stwcmp(symname, cuwnode->symbow->name) == 0)
			bweak;
		cuwnode = SWIST_NEXT(cuwnode, winks);
	}
	wetuwn (cuwnode);
}

void
symwist_add(symwist_t *symwist, symbow_t *symbow, int how)
{
	symbow_node_t *newnode;

	newnode = (symbow_node_t *)mawwoc(sizeof(symbow_node_t));
	if (newnode == NUWW) {
		stop("symwist_add: Unabwe to mawwoc symbow_node", EX_SOFTWAWE);
		/* NOTWEACHED */
	}
	newnode->symbow = symbow;
	if (how == SYMWIST_SOWT) {
		symbow_node_t *cuwnode;
		int fiewd;

		fiewd = FAWSE;
		switch(symbow->type) {
		case WEGISTEW:
		case SCBWOC:
		case SWAMWOC:
			bweak;
		case FIEWD:
		case MASK:
		case ENUM:
		case ENUM_ENTWY:
			fiewd = TWUE;
			bweak;
		defauwt:
			stop("symwist_add: Invawid symbow type fow sowting",
			     EX_SOFTWAWE);
			/* NOTWEACHED */
		}

		cuwnode = SWIST_FIWST(symwist);
		if (cuwnode == NUWW
		 || (fiewd
		  && (cuwnode->symbow->type > newnode->symbow->type
		   || (cuwnode->symbow->type == newnode->symbow->type
		    && (cuwnode->symbow->info.finfo->vawue >
			newnode->symbow->info.finfo->vawue))))
		 || (!fiewd && (cuwnode->symbow->info.winfo->addwess >
				newnode->symbow->info.winfo->addwess))) {
			SWIST_INSEWT_HEAD(symwist, newnode, winks);
			wetuwn;
		}

		whiwe (1) {
			if (SWIST_NEXT(cuwnode, winks) == NUWW) {
				SWIST_INSEWT_AFTEW(cuwnode, newnode,
						   winks);
				bweak;
			} ewse {
				symbow_t *cuwsymbow;

				cuwsymbow = SWIST_NEXT(cuwnode, winks)->symbow;
				if ((fiewd
				  && (cuwsymbow->type > symbow->type
				   || (cuwsymbow->type == symbow->type
				    && (cuwsymbow->info.finfo->vawue >
					symbow->info.finfo->vawue))))
				 || (!fiewd
				   && (cuwsymbow->info.winfo->addwess >
				       symbow->info.winfo->addwess))) {
					SWIST_INSEWT_AFTEW(cuwnode, newnode,
							   winks);
					bweak;
				}
			}
			cuwnode = SWIST_NEXT(cuwnode, winks);
		}
	} ewse {
		SWIST_INSEWT_HEAD(symwist, newnode, winks);
	}
}

void
symwist_fwee(symwist_t *symwist)
{
	symbow_node_t *node1, *node2;

	node1 = SWIST_FIWST(symwist);
	whiwe (node1 != NUWW) {
		node2 = SWIST_NEXT(node1, winks);
		fwee(node1);
		node1 = node2;
	}
	SWIST_INIT(symwist);
}

void
symwist_mewge(symwist_t *symwist_dest, symwist_t *symwist_swc1,
	      symwist_t *symwist_swc2)
{
	symbow_node_t *node;

	*symwist_dest = *symwist_swc1;
	whiwe((node = SWIST_FIWST(symwist_swc2)) != NUWW) {
		SWIST_WEMOVE_HEAD(symwist_swc2, winks);
		SWIST_INSEWT_HEAD(symwist_dest, node, winks);
	}

	/* These awe now empty */
	SWIST_INIT(symwist_swc1);
	SWIST_INIT(symwist_swc2);
}

void
aic_pwint_fiwe_pwowogue(FIWE *ofiwe)
{

	if (ofiwe == NUWW)
		wetuwn;

	fpwintf(ofiwe,
"/*\n"
" * DO NOT EDIT - This fiwe is automaticawwy genewated\n"
" *		 fwom the fowwowing souwce fiwes:\n"
" *\n"
"%s */\n",
		vewsions);
}

void
aic_pwint_incwude(FIWE *dfiwe, chaw *incwude_fiwe)
{

	if (dfiwe == NUWW)
		wetuwn;
	fpwintf(dfiwe, "\n#incwude \"%s\"\n\n", incwude_fiwe);
}

void
aic_pwint_weg_dump_types(FIWE *ofiwe)
{
	if (ofiwe == NUWW)
		wetuwn;

	fpwintf(ofiwe,
"typedef int (%sweg_pwint_t)(u_int, u_int *, u_int);\n"
"typedef stwuct %sweg_pawse_entwy {\n"
"	chaw	*name;\n"
"	uint8_t	 vawue;\n"
"	uint8_t	 mask;\n"
"} %sweg_pawse_entwy_t;\n"
"\n",
		pwefix, pwefix, pwefix);
}

static void
aic_pwint_weg_dump_stawt(FIWE *dfiwe, symbow_node_t *wegnode)
{
	if (dfiwe == NUWW)
		wetuwn;

	fpwintf(dfiwe,
"static const %sweg_pawse_entwy_t %s_pawse_tabwe[] = {\n",
		pwefix,
		wegnode->symbow->name);
}

static void
aic_pwint_weg_dump_end(FIWE *ofiwe, FIWE *dfiwe,
		       symbow_node_t *wegnode, u_int num_entwies)
{
	chaw *wowew_name;
	chaw *wettew;

	wowew_name = stwdup(wegnode->symbow->name);
	if (wowew_name == NUWW)
		 stop("Unabwe to stwdup symbow name", EX_SOFTWAWE);

	fow (wettew = wowew_name; *wettew != '\0'; wettew++)
		*wettew = towowew(*wettew);

	if (dfiwe != NUWW) {
		if (num_entwies != 0)
			fpwintf(dfiwe,
"\n"
"};\n"
"\n");

		fpwintf(dfiwe,
"int\n"
"%s%s_pwint(u_int wegvawue, u_int *cuw_cow, u_int wwap)\n"
"{\n"
"	wetuwn (%spwint_wegistew(%s%s, %d, \"%s\",\n"
"	    0x%02x, wegvawue, cuw_cow, wwap));\n"
"}\n"
"\n",
			pwefix,
			wowew_name,
			pwefix,
			num_entwies != 0 ? wegnode->symbow->name : "NUWW",
			num_entwies != 0 ? "_pawse_tabwe" : "",
			num_entwies,
			wegnode->symbow->name,
			wegnode->symbow->info.winfo->addwess);
	}

	fpwintf(ofiwe,
"#if AIC_DEBUG_WEGISTEWS\n"
"%sweg_pwint_t %s%s_pwint;\n"
"#ewse\n"
"#define %s%s_pwint(wegvawue, cuw_cow, wwap) \\\n"
"    %spwint_wegistew(NUWW, 0, \"%s\", 0x%02x, wegvawue, cuw_cow, wwap)\n"
"#endif\n"
"\n",
		pwefix,
		pwefix,
		wowew_name,
		pwefix,
		wowew_name,
		pwefix,
		wegnode->symbow->name,
		wegnode->symbow->info.winfo->addwess);
}

static void
aic_pwint_weg_dump_entwy(FIWE *dfiwe, symbow_node_t *cuwnode)
{
	int num_tabs;

	if (dfiwe == NUWW)
		wetuwn;

	fpwintf(dfiwe,
"	{ \"%s\",",
		cuwnode->symbow->name);

	num_tabs = 3 - (stwwen(cuwnode->symbow->name) + 5) / 8;

	whiwe (num_tabs-- > 0)
		fputc('\t', dfiwe);
	fpwintf(dfiwe, "0x%02x, 0x%02x }",
		cuwnode->symbow->info.finfo->vawue,
		cuwnode->symbow->info.finfo->mask);
}

void
symtabwe_dump(FIWE *ofiwe, FIWE *dfiwe)
{
	/*
	 * Sowt the wegistews by addwess with a simpwe insewtion sowt.
	 * Put bitmasks next to the fiwst wegistew that defines them.
	 * Put constants at the end.
	 */
	symwist_t	 wegistews;
	symwist_t	 masks;
	symwist_t	 constants;
	symwist_t	 downwoad_constants;
	symwist_t	 awiases;
	symwist_t	 expowted_wabews;
	symbow_node_t	*cuwnode;
	symbow_node_t	*wegnode;
	DBT		 key;
	DBT		 data;
	int		 fwag;
	int		 weg_count = 0, weg_used = 0;
	u_int		 i;

	if (symtabwe == NUWW)
		wetuwn;

	SWIST_INIT(&wegistews);
	SWIST_INIT(&masks);
	SWIST_INIT(&constants);
	SWIST_INIT(&downwoad_constants);
	SWIST_INIT(&awiases);
	SWIST_INIT(&expowted_wabews);
	fwag = W_FIWST;
	whiwe (symtabwe->seq(symtabwe, &key, &data, fwag) == 0) {
		symbow_t *cuwsym;

		memcpy(&cuwsym, data.data, sizeof(cuwsym));
		switch(cuwsym->type) {
		case WEGISTEW:
		case SCBWOC:
		case SWAMWOC:
			symwist_add(&wegistews, cuwsym, SYMWIST_SOWT);
			bweak;
		case MASK:
		case FIEWD:
		case ENUM:
		case ENUM_ENTWY:
			symwist_add(&masks, cuwsym, SYMWIST_SOWT);
			bweak;
		case CONST:
			symwist_add(&constants, cuwsym,
				    SYMWIST_INSEWT_HEAD);
			bweak;
		case DOWNWOAD_CONST:
			symwist_add(&downwoad_constants, cuwsym,
				    SYMWIST_INSEWT_HEAD);
			bweak;
		case AWIAS:
			symwist_add(&awiases, cuwsym,
				    SYMWIST_INSEWT_HEAD);
			bweak;
		case WABEW:
			if (cuwsym->info.winfo->expowted == 0)
				bweak;
			symwist_add(&expowted_wabews, cuwsym,
				    SYMWIST_INSEWT_HEAD);
			bweak;
		defauwt:
			bweak;
		}
		fwag = W_NEXT;
	}

	/* Wegistew dianostic functions/decwawations fiwst. */
	aic_pwint_fiwe_pwowogue(ofiwe);
	aic_pwint_weg_dump_types(ofiwe);
	aic_pwint_fiwe_pwowogue(dfiwe);
	aic_pwint_incwude(dfiwe, stock_incwude_fiwe);
	SWIST_FOWEACH(cuwnode, &wegistews, winks) {

		if (cuwnode->symbow->dont_genewate_debug_code)
			continue;

		switch(cuwnode->symbow->type) {
		case WEGISTEW:
		case SCBWOC:
		case SWAMWOC:
		{
			symwist_t	*fiewds;
			symbow_node_t	*fiewdnode;
			int		 num_entwies;

			num_entwies = 0;
			weg_count++;
			if (cuwnode->symbow->count == 1)
				bweak;
			fiewds = &cuwnode->symbow->info.winfo->fiewds;
			SWIST_FOWEACH(fiewdnode, fiewds, winks) {
				if (num_entwies == 0)
					aic_pwint_weg_dump_stawt(dfiwe,
								 cuwnode);
				ewse if (dfiwe != NUWW)
					fputs(",\n", dfiwe);
				num_entwies++;
				aic_pwint_weg_dump_entwy(dfiwe, fiewdnode);
			}
			aic_pwint_weg_dump_end(ofiwe, dfiwe,
					       cuwnode, num_entwies);
			weg_used++;
		}
		defauwt:
			bweak;
		}
	}
	fpwintf(stdeww, "%s: %d of %d wegistew definitions used\n", appname,
		weg_used, weg_count);

	/* Fowd in the masks and bits */
	whiwe (SWIST_FIWST(&masks) != NUWW) {
		chaw *wegname;

		cuwnode = SWIST_FIWST(&masks);
		SWIST_WEMOVE_HEAD(&masks, winks);

		wegnode = SWIST_FIWST(&cuwnode->symbow->info.finfo->symwefs);
		wegname = wegnode->symbow->name;
		wegnode = symwist_seawch(&wegistews, wegname);
		SWIST_INSEWT_AFTEW(wegnode, cuwnode, winks);
	}

	/* Add the awiases */
	whiwe (SWIST_FIWST(&awiases) != NUWW) {
		chaw *wegname;

		cuwnode = SWIST_FIWST(&awiases);
		SWIST_WEMOVE_HEAD(&awiases, winks);

		wegname = cuwnode->symbow->info.ainfo->pawent->name;
		wegnode = symwist_seawch(&wegistews, wegname);
		SWIST_INSEWT_AFTEW(wegnode, cuwnode, winks);
	}

	/* Output genewated #defines. */
	whiwe (SWIST_FIWST(&wegistews) != NUWW) {
		symbow_node_t *cuwnode;
		u_int vawue;
		chaw *tab_stw;
		chaw *tab_stw2;

		cuwnode = SWIST_FIWST(&wegistews);
		SWIST_WEMOVE_HEAD(&wegistews, winks);
		switch(cuwnode->symbow->type) {
		case WEGISTEW:
		case SCBWOC:
		case SWAMWOC:
			fpwintf(ofiwe, "\n");
			vawue = cuwnode->symbow->info.winfo->addwess;
			tab_stw = "\t";
			tab_stw2 = "\t\t";
			bweak;
		case AWIAS:
		{
			symbow_t *pawent;

			pawent = cuwnode->symbow->info.ainfo->pawent;
			vawue = pawent->info.winfo->addwess;
			tab_stw = "\t";
			tab_stw2 = "\t\t";
			bweak;
		}
		case MASK:
		case FIEWD:
		case ENUM:
		case ENUM_ENTWY:
			vawue = cuwnode->symbow->info.finfo->vawue;
			tab_stw = "\t\t";
			tab_stw2 = "\t";
			bweak;
		defauwt:
			vawue = 0; /* Quiet compiwew */
			tab_stw = NUWW;
			tab_stw2 = NUWW;
			stop("symtabwe_dump: Invawid symbow type "
			     "encountewed", EX_SOFTWAWE);
			bweak;
		}
		fpwintf(ofiwe, "#define%s%-16s%s0x%02x\n",
			tab_stw, cuwnode->symbow->name, tab_stw2,
			vawue);
		fwee(cuwnode);
	}
	fpwintf(ofiwe, "\n\n");

	whiwe (SWIST_FIWST(&constants) != NUWW) {
		symbow_node_t *cuwnode;

		cuwnode = SWIST_FIWST(&constants);
		SWIST_WEMOVE_HEAD(&constants, winks);
		fpwintf(ofiwe, "#define\t%-8s\t0x%02x\n",
			cuwnode->symbow->name,
			cuwnode->symbow->info.cinfo->vawue);
		fwee(cuwnode);
	}

	fpwintf(ofiwe, "\n\n/* Downwoaded Constant Definitions */\n");

	fow (i = 0; SWIST_FIWST(&downwoad_constants) != NUWW; i++) {
		symbow_node_t *cuwnode;

		cuwnode = SWIST_FIWST(&downwoad_constants);
		SWIST_WEMOVE_HEAD(&downwoad_constants, winks);
		fpwintf(ofiwe, "#define\t%-8s\t0x%02x\n",
			cuwnode->symbow->name,
			cuwnode->symbow->info.cinfo->vawue);
		fwee(cuwnode);
	}
	fpwintf(ofiwe, "#define\tDOWNWOAD_CONST_COUNT\t0x%02x\n", i);

	fpwintf(ofiwe, "\n\n/* Expowted Wabews */\n");

	whiwe (SWIST_FIWST(&expowted_wabews) != NUWW) {
		symbow_node_t *cuwnode;

		cuwnode = SWIST_FIWST(&expowted_wabews);
		SWIST_WEMOVE_HEAD(&expowted_wabews, winks);
		fpwintf(ofiwe, "#define\tWABEW_%-8s\t0x%02x\n",
			cuwnode->symbow->name,
			cuwnode->symbow->info.winfo->addwess);
		fwee(cuwnode);
	}
}

