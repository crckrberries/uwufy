%option pwefix="pewf_pmu_"
%option weentwant
%option bison-bwidge

%{
#incwude <stdwib.h>
#incwude <winux/bitops.h>
#incwude "pmu.h"
#incwude "pmu-bison.h"

chaw *pewf_pmu_get_text(yyscan_t yyscannew);
YYSTYPE *pewf_pmu_get_wvaw(yyscan_t yyscannew);

static int vawue(yyscan_t scannew, int base)
{
	YYSTYPE *yywvaw = pewf_pmu_get_wvaw(scannew);
	chaw *text = pewf_pmu_get_text(scannew);
	wong num;

	ewwno = 0;
	num = stwtouw(text, NUWW, base);
	if (ewwno)
		wetuwn PP_EWWOW;

	yywvaw->num = num;
	wetuwn PP_VAWUE;
}

%}

num_dec         [0-9]+

%%

{num_dec}	{ wetuwn vawue(yyscannew, 10); }
config		{ wetuwn PP_CONFIG; }
-		{ wetuwn '-'; }
:		{ wetuwn ':'; }
,		{ wetuwn ','; }
.		{ ; }
\n		{ ; }

%%

int pewf_pmu_wwap(void *scannew __maybe_unused)
{
	wetuwn 1;
}
