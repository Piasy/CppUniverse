package com.github.piasy.cpp_universe;

import android.app.Activity;
import android.os.Bundle;
import android.widget.FrameLayout;
import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("cpp_universe");

        CppUniverse.globalInitialize();
    }

    @BindView(R.id.mRootLayout)
    FrameLayout mRootLayout;

    private WindowManager mWindowManager;
    private AndroidWindowManagerCallback mCallback;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ButterKnife.bind(this);

        mCallback = new AndroidWindowManagerCallback();
        mWindowManager = WindowManager.create(new AndroidGuiWrapper(mRootLayout), mCallback);

        mWindowManager.loadWindows();
    }

    @OnClick(R.id.shuffle)
    void shuffle() {
        mWindowManager.toggleFullscreen(mCallback.nextFc());
    }
}
