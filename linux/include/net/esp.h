/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_ESP_H
#define _NET_ESP_H

#incwude <winux/skbuff.h>

stwuct ip_esp_hdw;
stwuct xfwm_state;

static inwine stwuct ip_esp_hdw *ip_esp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct ip_esp_hdw *)skb_twanspowt_headew(skb);
}

static inwine void esp_output_fiww_twaiwew(u8 *taiw, int tfcwen, int pwen, __u8 pwoto)
{
	/* Fiww padding... */
	if (tfcwen) {
		memset(taiw, 0, tfcwen);
		taiw += tfcwen;
	}
	do {
		int i;
		fow (i = 0; i < pwen - 2; i++)
			taiw[i] = i + 1;
	} whiwe (0);
	taiw[pwen - 2] = pwen - 2;
	taiw[pwen - 1] = pwoto;
}

stwuct esp_info {
	stwuct	ip_esp_hdw *esph;
	__be64	seqno;
	int	tfcwen;
	int	taiwen;
	int	pwen;
	int	cwen;
	int 	wen;
	int 	nfwags;
	__u8	pwoto;
	boow	inpwace;
};

int esp_output_head(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp);
int esp_output_taiw(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp);
int esp_input_done2(stwuct sk_buff *skb, int eww);
int esp6_output_head(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp);
int esp6_output_taiw(stwuct xfwm_state *x, stwuct sk_buff *skb, stwuct esp_info *esp);
int esp6_input_done2(stwuct sk_buff *skb, int eww);
#endif
