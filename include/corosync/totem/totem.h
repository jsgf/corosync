/*
 * Copyright (c) 2005 MontaVista Software, Inc.
 * Copyright (c) 2006-2009 Red Hat, Inc.
 *
 * Author: Steven Dake (sdake@redhat.com)
 *
 * All rights reserved.
 *
 * This software licensed under BSD license, the text of which follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the MontaVista Software, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TOTEM_H_DEFINED
#define TOTEM_H_DEFINED
#include "totemip.h"

#ifndef MESSAGE_SIZE_MAX
#define MESSAGE_SIZE_MAX	1024*1024 /* (1MB) */
#endif /* MESSAGE_SIZE_MAX */

#ifndef MESSAGE_QUEUE_MAX
#define MESSAGE_QUEUE_MAX MESSAGE_SIZE_MAX / totem_config->net_mtu
#endif /* MESSAGE_QUEUE_MAX */

#define PROCESSOR_COUNT_MAX	384
#define FRAME_SIZE_MAX		9000
#define TRANSMITS_ALLOWED	16
#define SEND_THREADS_MAX	16
#define INTERFACE_MAX		2

struct totem_interface {
	struct totem_ip_address bindnet;
	struct totem_ip_address boundto;
	struct totem_ip_address mcast_addr;
	uint16_t ip_port;
};

struct totem_logging_configuration {
        void (*log_printf) (
                int subsys,
                const char *function_name,
                const char *file_name,
                int file_line,
                unsigned int level,
		unsigned int tag,
                const char *format,
                ...) __attribute__((format(printf, 7, 8)));

	int log_level_security;
	int log_level_error;
	int log_level_warning;
	int log_level_notice;
	int log_level_debug;
	int log_subsys_id;
};

enum { TOTEM_PRIVATE_KEY_LEN = 128 };
enum { TOTEM_RRP_MODE_BYTES = 64 };

struct totem_config {
	int version;

	/*
	 * network
	 */
	struct totem_interface *interfaces;
	unsigned int interface_count;
	unsigned int node_id;

	/*
	 * key information
	 */
	unsigned char private_key[TOTEM_PRIVATE_KEY_LEN];

	unsigned int private_key_len;

	/*
	 * Totem configuration parameters
	 */
	unsigned int token_timeout;

	unsigned int token_retransmit_timeout;

	unsigned int token_hold_timeout;

	unsigned int token_retransmits_before_loss_const;

	unsigned int join_timeout;

	unsigned int send_join_timeout;

	unsigned int consensus_timeout;

	unsigned int merge_timeout;

	unsigned int downcheck_timeout;

	unsigned int fail_to_recv_const;

	unsigned int seqno_unchanged_const;

	unsigned int rrp_token_expired_timeout;

	unsigned int rrp_problem_count_timeout;

	unsigned int rrp_problem_count_threshold;

	char rrp_mode[TOTEM_RRP_MODE_BYTES];

	struct totem_logging_configuration totem_logging_configuration;

	void (*log_rec) (
		int subsysid,
		const char *function_name,
		const char *file_name,
		int file_line,
		unsigned int rec_ident,
		...);

	unsigned int secauth;

	unsigned int net_mtu;

	unsigned int threads;

	unsigned int heartbeat_failures_allowed;

	unsigned int max_network_delay;

	unsigned int window_size;

	unsigned int max_messages;

	const char *vsf_type;

	enum { TOTEM_CRYPTO_SOBER=0, TOTEM_CRYPTO_NSS } crypto_type;
	enum { TOTEM_CRYPTO_ACCEPT_OLD=0, TOTEM_CRYPTO_ACCEPT_NEW } crypto_accept;

	int crypto_crypt_type;
	int crypto_sign_type;
};

#define TOTEM_CONFIGURATION_TYPE
enum totem_configuration_type {
	TOTEM_CONFIGURATION_REGULAR,
	TOTEM_CONFIGURATION_TRANSITIONAL
};

#define TOTEM_CALLBACK_TOKEN_TYPE
enum totem_callback_token_type {
	TOTEM_CALLBACK_TOKEN_RECEIVED = 1,
	TOTEM_CALLBACK_TOKEN_SENT = 2
};

#define MEMB_RING_ID
struct memb_ring_id {
	struct totem_ip_address rep;
	unsigned long long seq;
} __attribute__((packed));


#endif /* TOTEM_H_DEFINED */
