/**
 * Copyright (C) 2010 Regis Montoya (aka r3gis - www.r3gis.fr)
 * This file is part of CSipSimple.
 *
 *  CSipSimple is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  CSipSimple is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CSipSimple.  If not, see <http://www.gnu.org/licenses/>.
 */
package com.csipsimple.utils;

import android.content.Context;
import android.media.AudioManager;

public class PhoneUtils {

	// State of the Phone's audio modes
	// Each state can move to the other states, but within the state only
	// certain
	// transitions for AudioManager.setMode() are allowed.
	public static final int AUDIO_IDLE = 0;
	/** audio behaviour at phone idle */
	public static final int AUDIO_RINGING = 1;
	/** audio behaviour while ringing */
	public static final int AUDIO_OFFHOOK = 2;
	/** audio behaviour while in call. */
	private static final String THIS_FILE = "PhoneUtils";
	private static int sAudioBehaviourState = AUDIO_IDLE;

	public static boolean isSpeakerOn(Context context) {
		AudioManager audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
		return audioManager.isSpeakerphoneOn();
	}

	public static void turnOnSpeaker(Context context, boolean flag) {
		AudioManager audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
		if(Compatibility.isCompatible(5)) {
			audioManager.setSpeakerphoneOn(flag);
		}else {
			audioManager.setRouting(AudioManager.MODE_IN_CALL, flag?AudioManager.ROUTE_SPEAKER:AudioManager.ROUTE_EARPIECE, AudioManager.ROUTE_ALL);
			audioManager.setSpeakerphoneOn(flag);
		}
	}

	// Audio mode management for all api versions
/*
	// static method to set the audio control state.
	public static void setAudioControlState(int newState) {
		sAudioBehaviourState = newState;
	}


	public static void setAudioMode(Context ctx, int mode) {

		AudioManager aManager = (AudioManager) ctx.getSystemService(Context.AUDIO_SERVICE);
		
		// decide whether or not to ignore the audio setting
		
		boolean ignore = false;

		switch (sAudioBehaviourState) {
		case AUDIO_RINGING:
			ignore = ((mode == AudioManager.MODE_NORMAL) || (mode == AudioManager.MODE_IN_CALL));
			break;
		case AUDIO_OFFHOOK:
			ignore = ((mode == AudioManager.MODE_NORMAL) || (mode == AudioManager.MODE_RINGTONE));
			break;
		case AUDIO_IDLE:
		default:
			ignore = (mode == AudioManager.MODE_IN_CALL);
			break;
		}

		if (!ignore) {
			Log.d(THIS_FILE, "PhoneUtils.setAudioMode(), >> " + sAudioBehaviourState + " SWITCHING " + mode );
			aManager.setMode(mode);
			
			aManager.setRouting(mode, (mode == AudioManager.MODE_NORMAL) ? AudioManager.ROUTE_SPEAKER : AudioManager.ROUTE_EARPIECE, AudioManager.ROUTE_ALL);
			aManager.setSpeakerphoneOn(mode == AudioManager.MODE_NORMAL || mode == AudioManager.MODE_RINGTONE);
		}else {
			Log.d(THIS_FILE, "PhoneUtils.setAudioMode(), >> " + sAudioBehaviourState + " IGNORING "+mode);
		}
	}
	*/
	
}