/*
 * Copyright (C) 2006 Voice Sistem SRL
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

/*!
 * \file
 * \brief Kamailio presence module :: Core
 * \ingroup presence
 */


#ifndef PA_MOD_H
#define PA_MOD_H

#include "../../core/parser/msg_parser.h"
#include "../../modules/tm/tm_load.h"
#include "../../modules/sl/sl.h"
#include "../../lib/srdb1/db.h"
#include "../../core/parser/parse_from.h"
#include "../../core/utils/sruid.h"
#include "event_list.h"
#include "hash.h"

/* DB modes */

/** subscriptions are stored only in memory */
#define NO_DB 0
/** subscriptions are written in memory and in DB synchronously and read only from memory */
#define WRITE_THROUGH 1
/** subscriptions are stored in memory and periodically updated in DB */
#define WRITE_BACK 2
/** subscriptions are stored only in database */
#define DB_ONLY 3

#define NO_UPDATE_TYPE -1
#define UPDATED_TYPE 1

#define PS_PCACHE_NONE 0
#define PS_PCACHE_HYBRID 1
#define PS_PCACHE_RECORD 2

/** TM bind */
extern struct tm_binds _pres_tmb;

extern sl_api_t _pres_slb;

/* DB module bind */
extern db_func_t pa_dbf;
extern db1_con_t *pa_db;

/* PRESENCE database */
extern str pres_db_url;
extern str presentity_table;
extern str active_watchers_table;
extern str watchers_table;

extern int pres_counter;
extern int pres_pid;
extern unsigned int pres_startup_time;
extern int pres_expires_offset;
extern int pres_cseq_offset;
extern str pres_server_address;
extern uint32_t pres_min_expires;
extern int pres_min_expires_action;
extern uint32_t pres_max_expires;
extern int pres_subs_dbmode;
extern int publ_cache_mode;
extern int pres_sphere_enable;
extern int pres_timeout_rm_subs;
extern int pres_send_fast_notify;
extern int shtable_size;
extern shtable_t subs_htable;

extern int pres_fetch_rows;

extern int pres_waitn_time;
extern int pres_notifier_poll_rate;
extern int pres_notifier_processes;
extern int pres_force_delete;
extern int pres_startup_mode;
extern str pres_xavp_cfg;
extern int pres_retrieve_order;
extern str pres_retrieve_order_by;
extern int pres_enable_dmq;
extern int pres_subs_respond_200;

extern int phtable_size;
extern phtable_t *pres_htable;

extern sruid_t pres_sruid;

extern db_locking_t pres_db_table_lock;

int update_watchers_status(str *pres_uri, pres_ev_t *ev, str *rules_doc);
int pres_auth_status(struct sip_msg *msg, str watcher_uri, str presentity_uri);
int _api_pres_refresh_watchers(str *pres, str *event, int type);

typedef int (*sip_uri_match_f)(str *s1, str *s2);
extern sip_uri_match_f presence_sip_uri_match;

int pv_get_subscription(
		struct sip_msg *msg, pv_param_t *param, pv_value_t *res);
int pv_parse_subscription_name(pv_spec_p sp, str *in);

#endif /* PA_MOD_H */
