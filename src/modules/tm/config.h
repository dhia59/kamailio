/*
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** TM :: Runtime configuration variables.
 * @file
 * @ingroup tm
 */


#ifndef _TM_CONFIG_H
#define _TM_CONFIG_H

/* this is where table size is defined now -- sort of
   ugly, core should not be bothered by TM table size,
   but on the other, core's stateless forwarding should
   have consistent branch generation with stateful mode
   and needs to calculate branch/hash, for which table size
   is needed
*/
#include "../../core/hash_func.h"

#include "../../core/cfg/cfg.h"
#include "../../core/str.h"

/* maximum length of locally generated acknowledgment */
#define MAX_ACK_LEN 1024

/* FINAL_RESPONSE_TIMER ... tells how long should the transaction engine
   wait if no final response comes back*/
#define FR_TIME_OUT 30000	   /* ms */
#define INV_FR_TIME_OUT 120000 /* ms */

/*! \brief final response timers to be used for serial forwarding */
#define INV_FR_TIME_OUT_NEXT 30000 /* ms */

/* WAIT timer ... tells how long state should persist in memory after
   a transaction was finalized*/
#define WT_TIME_OUT 5000 /* ms */

/* retransmission timers */
#define RETR_T1 500	 /* ms */
#define RETR_T2 4000 /* ms */

/* maximum total lifetime for an INVITE or non-INVITE transaction
 * Note: after this time the transaction will not be deleted
 *  immediately, but forced to go in the wait state or in wait for ack state
 *  and then wait state, so it will still be alive for either WT_TIME_OUT in
 *  the non-inv or "silent" inv. case and for FR_TIME_OUT + WT_TIME_OUT for an
 *  invite transaction (for which  we must wait for the neg. reply ack)*/
#define MAX_INV_LIFETIME 180000	  /* ms, rfc min. C-timer value */
#define MAX_NONINV_LIFETIME 32000 /* ms, rfc timer F value */

/* when first reply is sent, this additional space is allocated so that
   one does not have to reallocate share memory when the message is
   replaced by a subsequent, longer message
*/
#define REPLY_OVERBUFFER_LEN 160
#define TAG_OVERBUFFER_LEN 32

/* dimensions of FIFO server */
#define MAX_METHOD 64
#define MAX_HEADER 1024
#define MAX_BODY 1024
#define MAX_DST 512
#define MAX_FROM 512

/* messages generated by server */
#define CANCELING "canceling"
#define CANCEL_DONE "ok -- no more pending branches"
#define CANCELED "Request canceled"

/* execute event_route[tm:local-request] for hop-by-hop CANCEL */
#define TM_EVLREQ_CANCEL_HBH 1

/* to-tag separator for stateful processing */
#define TM_TAG_SEPARATOR '-'

/* FIFO substitution character */
#define SUBST_CHAR '!'

struct cfg_group_tm
{
	char *tm_auto_inv_100_r;
	char *default_reason;
	str ac_extra_hdrs;
	int ruri_matching;
	int via1_matching;
	int callid_matching;
	int callid_cseq_matching;
	unsigned int fr_timeout;
	unsigned int fr_inv_timeout;
	unsigned int fr_inv_timeout_next;
	unsigned int wait_timeout;
	unsigned int rt_t1_timeout_ms;
	unsigned int rt_t2_timeout_ms;
	unsigned int tm_max_inv_lifetime;
	unsigned int tm_max_noninv_lifetime;
	int noisy_ctimer;
	int tm_auto_inv_100;
	int tm_unix_tx_timeout;
	int restart_fr_on_each_reply;
	int pass_provisional_replies;
	int tm_aggregate_auth;
	int unmatched_cancel;
	int default_code;
	int reparse_invite;
	int tm_blst_503;
	int tm_blst_503_default;
	int tm_blst_503_min;
	int tm_blst_503_max;
	unsigned int tm_blst_methods_add;
	unsigned int tm_blst_methods_lookup;
	unsigned int cancel_b_flags;
	int reparse_on_dns_failover;
	int disable_6xx;
	int local_ack_mode;
	int local_cancel_reason;
	int e2e_cancel_reason;
	unsigned int relay_100;
	int enable_uac_fr;
};

extern struct cfg_group_tm default_tm_cfg;
extern void *tm_cfg;
extern cfg_def_t tm_cfg_def[];

#endif
