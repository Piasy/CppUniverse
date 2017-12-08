package com.github.piasy.cpp_universe;

import android.util.Log;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Piasy{github.com/Piasy} on 03/12/2017.
 */

public class AndroidWindowManagerCallback extends WindowManagerCallback {

    private static final String TAG = "WindowManagerCallback";

    private final List<String> mUsers = new ArrayList<>();
    private int mFcIndex = 0;

    @Override
    public void onWindowAdded(final Window window) {
        Log.d(TAG, "onWindowAdded " + window);
        mUsers.add(window.getUid());
    }

    @Override
    public void onError(final int error) {
        Log.d(TAG, "onError " + error);
    }

    public String nextFc() {
        mFcIndex = (mFcIndex + 1) % mUsers.size();
        return mUsers.get(mFcIndex);
    }
}
