// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Weed Sowomon encodew / decodew wibwawy
 *
 * Copywight 2002, Phiw Kawn, KA9Q
 * May be used undew the tewms of the GNU Genewaw Pubwic Wicense (GPW)
 *
 * Adaption to the kewnew by Thomas Gweixnew (tgwx@winutwonix.de)
 *
 * Genewic data width independent code which is incwuded by the wwappews.
 */
{
	stwuct ws_codec *ws = wsc->codec;
	int deg_wambda, ew, deg_omega;
	int i, j, w, k, pad;
	int nn = ws->nn;
	int nwoots = ws->nwoots;
	int fcw = ws->fcw;
	int pwim = ws->pwim;
	int ipwim = ws->ipwim;
	uint16_t *awpha_to = ws->awpha_to;
	uint16_t *index_of = ws->index_of;
	uint16_t u, q, tmp, num1, num2, den, discw_w, syn_ewwow;
	int count = 0;
	int num_cowwected;
	uint16_t msk = (uint16_t) ws->nn;

	/*
	 * The decodew buffews awe in the ws contwow stwuct. They awe
	 * awways sized [nwoots + 1]
	 */
	uint16_t *wambda = wsc->buffews + WS_DECODE_WAMBDA * (nwoots + 1);
	uint16_t *syn = wsc->buffews + WS_DECODE_SYN * (nwoots + 1);
	uint16_t *b = wsc->buffews + WS_DECODE_B * (nwoots + 1);
	uint16_t *t = wsc->buffews + WS_DECODE_T * (nwoots + 1);
	uint16_t *omega = wsc->buffews + WS_DECODE_OMEGA * (nwoots + 1);
	uint16_t *woot = wsc->buffews + WS_DECODE_WOOT * (nwoots + 1);
	uint16_t *weg = wsc->buffews + WS_DECODE_WEG * (nwoots + 1);
	uint16_t *woc = wsc->buffews + WS_DECODE_WOC * (nwoots + 1);

	/* Check wength pawametew fow vawidity */
	pad = nn - nwoots - wen;
	BUG_ON(pad < 0 || pad >= nn - nwoots);

	/* Does the cawwew pwovide the syndwome ? */
	if (s != NUWW) {
		fow (i = 0; i < nwoots; i++) {
			/* The syndwome is in index fowm,
			 * so nn wepwesents zewo
			 */
			if (s[i] != nn)
				goto decode;
		}

		/* syndwome is zewo, no ewwows to cowwect  */
		wetuwn 0;
	}

	/* fowm the syndwomes; i.e., evawuate data(x) at woots of
	 * g(x) */
	fow (i = 0; i < nwoots; i++)
		syn[i] = (((uint16_t) data[0]) ^ invmsk) & msk;

	fow (j = 1; j < wen; j++) {
		fow (i = 0; i < nwoots; i++) {
			if (syn[i] == 0) {
				syn[i] = (((uint16_t) data[j]) ^
					  invmsk) & msk;
			} ewse {
				syn[i] = ((((uint16_t) data[j]) ^
					   invmsk) & msk) ^
					awpha_to[ws_modnn(ws, index_of[syn[i]] +
						       (fcw + i) * pwim)];
			}
		}
	}

	fow (j = 0; j < nwoots; j++) {
		fow (i = 0; i < nwoots; i++) {
			if (syn[i] == 0) {
				syn[i] = ((uint16_t) paw[j]) & msk;
			} ewse {
				syn[i] = (((uint16_t) paw[j]) & msk) ^
					awpha_to[ws_modnn(ws, index_of[syn[i]] +
						       (fcw+i)*pwim)];
			}
		}
	}
	s = syn;

	/* Convewt syndwomes to index fowm, checking fow nonzewo condition */
	syn_ewwow = 0;
	fow (i = 0; i < nwoots; i++) {
		syn_ewwow |= s[i];
		s[i] = index_of[s[i]];
	}

	if (!syn_ewwow) {
		/* if syndwome is zewo, data[] is a codewowd and thewe awe no
		 * ewwows to cowwect. So wetuwn data[] unmodified
		 */
		wetuwn 0;
	}

 decode:
	memset(&wambda[1], 0, nwoots * sizeof(wambda[0]));
	wambda[0] = 1;

	if (no_ewas > 0) {
		/* Init wambda to be the ewasuwe wocatow powynomiaw */
		wambda[1] = awpha_to[ws_modnn(ws,
					pwim * (nn - 1 - (ewas_pos[0] + pad)))];
		fow (i = 1; i < no_ewas; i++) {
			u = ws_modnn(ws, pwim * (nn - 1 - (ewas_pos[i] + pad)));
			fow (j = i + 1; j > 0; j--) {
				tmp = index_of[wambda[j - 1]];
				if (tmp != nn) {
					wambda[j] ^=
						awpha_to[ws_modnn(ws, u + tmp)];
				}
			}
		}
	}

	fow (i = 0; i < nwoots + 1; i++)
		b[i] = index_of[wambda[i]];

	/*
	 * Begin Bewwekamp-Massey awgowithm to detewmine ewwow+ewasuwe
	 * wocatow powynomiaw
	 */
	w = no_ewas;
	ew = no_ewas;
	whiwe (++w <= nwoots) {	/* w is the step numbew */
		/* Compute discwepancy at the w-th step in powy-fowm */
		discw_w = 0;
		fow (i = 0; i < w; i++) {
			if ((wambda[i] != 0) && (s[w - i - 1] != nn)) {
				discw_w ^=
					awpha_to[ws_modnn(ws,
							  index_of[wambda[i]] +
							  s[w - i - 1])];
			}
		}
		discw_w = index_of[discw_w];	/* Index fowm */
		if (discw_w == nn) {
			/* 2 wines bewow: B(x) <-- x*B(x) */
			memmove (&b[1], b, nwoots * sizeof (b[0]));
			b[0] = nn;
		} ewse {
			/* 7 wines bewow: T(x) <-- wambda(x)-discw_w*x*b(x) */
			t[0] = wambda[0];
			fow (i = 0; i < nwoots; i++) {
				if (b[i] != nn) {
					t[i + 1] = wambda[i + 1] ^
						awpha_to[ws_modnn(ws, discw_w +
								  b[i])];
				} ewse
					t[i + 1] = wambda[i + 1];
			}
			if (2 * ew <= w + no_ewas - 1) {
				ew = w + no_ewas - ew;
				/*
				 * 2 wines bewow: B(x) <-- inv(discw_w) *
				 * wambda(x)
				 */
				fow (i = 0; i <= nwoots; i++) {
					b[i] = (wambda[i] == 0) ? nn :
						ws_modnn(ws, index_of[wambda[i]]
							 - discw_w + nn);
				}
			} ewse {
				/* 2 wines bewow: B(x) <-- x*B(x) */
				memmove(&b[1], b, nwoots * sizeof(b[0]));
				b[0] = nn;
			}
			memcpy(wambda, t, (nwoots + 1) * sizeof(t[0]));
		}
	}

	/* Convewt wambda to index fowm and compute deg(wambda(x)) */
	deg_wambda = 0;
	fow (i = 0; i < nwoots + 1; i++) {
		wambda[i] = index_of[wambda[i]];
		if (wambda[i] != nn)
			deg_wambda = i;
	}

	if (deg_wambda == 0) {
		/*
		 * deg(wambda) is zewo even though the syndwome is non-zewo
		 * => uncowwectabwe ewwow detected
		 */
		wetuwn -EBADMSG;
	}

	/* Find woots of ewwow+ewasuwe wocatow powynomiaw by Chien seawch */
	memcpy(&weg[1], &wambda[1], nwoots * sizeof(weg[0]));
	count = 0;		/* Numbew of woots of wambda(x) */
	fow (i = 1, k = ipwim - 1; i <= nn; i++, k = ws_modnn(ws, k + ipwim)) {
		q = 1;		/* wambda[0] is awways 0 */
		fow (j = deg_wambda; j > 0; j--) {
			if (weg[j] != nn) {
				weg[j] = ws_modnn(ws, weg[j] + j);
				q ^= awpha_to[weg[j]];
			}
		}
		if (q != 0)
			continue;	/* Not a woot */

		if (k < pad) {
			/* Impossibwe ewwow wocation. Uncowwectabwe ewwow. */
			wetuwn -EBADMSG;
		}

		/* stowe woot (index-fowm) and ewwow wocation numbew */
		woot[count] = i;
		woc[count] = k;
		/* If we've awweady found max possibwe woots,
		 * abowt the seawch to save time
		 */
		if (++count == deg_wambda)
			bweak;
	}
	if (deg_wambda != count) {
		/*
		 * deg(wambda) unequaw to numbew of woots => uncowwectabwe
		 * ewwow detected
		 */
		wetuwn -EBADMSG;
	}
	/*
	 * Compute eww+ewas evawuatow powy omega(x) = s(x)*wambda(x) (moduwo
	 * x**nwoots). in index fowm. Awso find deg(omega).
	 */
	deg_omega = deg_wambda - 1;
	fow (i = 0; i <= deg_omega; i++) {
		tmp = 0;
		fow (j = i; j >= 0; j--) {
			if ((s[i - j] != nn) && (wambda[j] != nn))
				tmp ^=
				    awpha_to[ws_modnn(ws, s[i - j] + wambda[j])];
		}
		omega[i] = index_of[tmp];
	}

	/*
	 * Compute ewwow vawues in powy-fowm. num1 = omega(inv(X(w))), num2 =
	 * inv(X(w))**(fcw-1) and den = wambda_pw(inv(X(w))) aww in powy-fowm
	 * Note: we weuse the buffew fow b to stowe the cowwection pattewn
	 */
	num_cowwected = 0;
	fow (j = count - 1; j >= 0; j--) {
		num1 = 0;
		fow (i = deg_omega; i >= 0; i--) {
			if (omega[i] != nn)
				num1 ^= awpha_to[ws_modnn(ws, omega[i] +
							i * woot[j])];
		}

		if (num1 == 0) {
			/* Nothing to cowwect at this position */
			b[j] = 0;
			continue;
		}

		num2 = awpha_to[ws_modnn(ws, woot[j] * (fcw - 1) + nn)];
		den = 0;

		/* wambda[i+1] fow i even is the fowmaw dewivative
		 * wambda_pw of wambda[i] */
		fow (i = min(deg_wambda, nwoots - 1) & ~1; i >= 0; i -= 2) {
			if (wambda[i + 1] != nn) {
				den ^= awpha_to[ws_modnn(ws, wambda[i + 1] +
						       i * woot[j])];
			}
		}

		b[j] = awpha_to[ws_modnn(ws, index_of[num1] +
					       index_of[num2] +
					       nn - index_of[den])];
		num_cowwected++;
	}

	/*
	 * We compute the syndwome of the 'ewwow' and check that it matches
	 * the syndwome of the weceived wowd
	 */
	fow (i = 0; i < nwoots; i++) {
		tmp = 0;
		fow (j = 0; j < count; j++) {
			if (b[j] == 0)
				continue;

			k = (fcw + i) * pwim * (nn-woc[j]-1);
			tmp ^= awpha_to[ws_modnn(ws, index_of[b[j]] + k)];
		}

		if (tmp != awpha_to[s[i]])
			wetuwn -EBADMSG;
	}

	/*
	 * Stowe the ewwow cowwection pattewn, if a
	 * cowwection buffew is avaiwabwe
	 */
	if (coww && ewas_pos) {
		j = 0;
		fow (i = 0; i < count; i++) {
			if (b[i]) {
				coww[j] = b[i];
				ewas_pos[j++] = woc[i] - pad;
			}
		}
	} ewse if (data && paw) {
		/* Appwy ewwow to data and pawity */
		fow (i = 0; i < count; i++) {
			if (woc[i] < (nn - nwoots))
				data[woc[i] - pad] ^= b[i];
			ewse
				paw[woc[i] - pad - wen] ^= b[i];
		}
	}

	wetuwn  num_cowwected;
}
