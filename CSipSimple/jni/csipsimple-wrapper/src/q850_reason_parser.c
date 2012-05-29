/**
 * Copyright (C) 2010 Regis Montoya (aka r3gis - www.r3gis.fr)
 * This file is part of pjsip_android.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "pjsua_jni_addons.h"


/**
 * Utility from freeswitch to extract code from q.850 cause
 */
int lookup_q850_cause(const char *cause) {
	// Taken from http://wiki.freeswitch.org/wiki/Hangup_causes
	if (pj_ansi_stricmp(cause, "cause=1") == 0) {
		return 404;
	} else if (pj_ansi_stricmp(cause, "cause=2") == 0) {
		return 404;
	} else if (pj_ansi_stricmp(cause, "cause=3") == 0) {
		return 404;
	} else if (pj_ansi_stricmp(cause, "cause=17") == 0) {
		return 486;
	} else if (pj_ansi_stricmp(cause, "cause=18") == 0) {
		return 408;
	} else if (pj_ansi_stricmp(cause, "cause=19") == 0) {
		return 480;
	} else if (pj_ansi_stricmp(cause, "cause=20") == 0) {
		return 480;
	} else if (pj_ansi_stricmp(cause, "cause=21") == 0) {
		return 603;
	} else if (pj_ansi_stricmp(cause, "cause=22") == 0) {
		return 410;
	} else if (pj_ansi_stricmp(cause, "cause=23") == 0) {
		return 410;
	} else if (pj_ansi_stricmp(cause, "cause=25") == 0) {
		return 483;
	} else if (pj_ansi_stricmp(cause, "cause=27") == 0) {
		return 502;
	} else if (pj_ansi_stricmp(cause, "cause=28") == 0) {
		return 484;
	} else if (pj_ansi_stricmp(cause, "cause=29") == 0) {
		return 501;
	} else if (pj_ansi_stricmp(cause, "cause=31") == 0) {
		return 480;
	} else if (pj_ansi_stricmp(cause, "cause=34") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=38") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=41") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=42") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=44") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=52") == 0) {
		return 403;
	} else if (pj_ansi_stricmp(cause, "cause=54") == 0) {
		return 403;
	} else if (pj_ansi_stricmp(cause, "cause=57") == 0) {
		return 403;
	} else if (pj_ansi_stricmp(cause, "cause=58") == 0) {
		return 503;
	} else if (pj_ansi_stricmp(cause, "cause=65") == 0) {
		return 488;
	} else if (pj_ansi_stricmp(cause, "cause=69") == 0) {
		return 501;
	} else if (pj_ansi_stricmp(cause, "cause=79") == 0) {
		return 501;
	} else if (pj_ansi_stricmp(cause, "cause=88") == 0) {
		return 488;
	} else if (pj_ansi_stricmp(cause, "cause=102") == 0) {
		return 504;
	} else if (pj_ansi_stricmp(cause, "cause=487") == 0) {
		return 487;
	} else {
		return 0;
	}
}

/**
 * Get Q.850 reason code from pjsip_event
 */
int get_q850_reason_code(pjsip_event *e) {
	int cause = 0;
	const pj_str_t HDR = { "Reason", 6 };
	pj_bool_t is_q850 = PJ_FALSE;

	if (e->body.tsx_state.type == PJSIP_EVENT_RX_MSG) {

		pjsip_generic_string_hdr *hdr =
				(pjsip_generic_string_hdr*) pjsip_msg_find_hdr_by_name(
						e->body.tsx_state.src.rdata->msg_info.msg, &HDR, NULL);

		// TODO : check if the header should not be parsed here? -- I don't see how it could work without parsing.

		if (hdr) {
			char *token = strtok(hdr->hvalue.ptr, ";");
			while (token != NULL) {
				if (!is_q850 && pj_ansi_stricmp(token, "Q.850") == 0) {
					is_q850 = PJ_TRUE;
				} else if (cause == 0) {
					cause = lookup_q850_cause(token);
				}
				token = strtok(NULL, ";");
			}
		}
	}

	return (is_q850) ? cause : 0;
}


/**
 * Get event status code of an event. Including Q.850 processing
 */
PJ_DECL(int) get_event_status_code(pjsip_event *e) {
	if (!e || e->type != PJSIP_EVENT_TSX_STATE) {
		return 0;
	}

	int retval = get_q850_reason_code(e);
	if (retval > 0) {
		return retval;
	} else {
		return e->body.tsx_state.tsx->status_code;
	}
}

