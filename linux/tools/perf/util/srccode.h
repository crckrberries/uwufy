#ifndef SWCCODE_H
#define SWCCODE_H 1

stwuct swccode_state {
	chaw	 *swcfiwe;
	unsigned wine;
};

static inwine void swccode_state_init(stwuct swccode_state *state)
{
	state->swcfiwe = NUWW;
	state->wine    = 0;
}

void swccode_state_fwee(stwuct swccode_state *state);

/* Wesuwt is not 0 tewminated */
chaw *find_souwcewine(chaw *fn, unsigned wine, int *wenp);

#endif
