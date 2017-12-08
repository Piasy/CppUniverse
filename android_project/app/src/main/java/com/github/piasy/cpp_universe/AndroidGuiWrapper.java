package com.github.piasy.cpp_universe;

import android.graphics.Color;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

/**
 * Created by Piasy{github.com/Piasy} on 03/12/2017.
 */

public class AndroidGuiWrapper extends GuiWrapper {
    private static final int[] COLORS = new int[] {
            Color.RED, Color.GREEN, Color.BLUE
    };

    private final FrameLayout mContainer;
    private final Handler mUiHandler;

    private int mContainerWidth;
    private int mContainerHeight;

    public AndroidGuiWrapper(final FrameLayout container) {
        mContainer = container;
        mUiHandler = new Handler(Looper.getMainLooper());
    }

    @Override
    public void createView(final Window window) {
        mUiHandler.post(() -> doCreateView(window));
    }

    @Override
    public void swapView(final Window alice, final Window bob) {
        int aliceView = -1;
        int bobView = -1;
        final int size = mContainer.getChildCount();
        for (int i = 0; i < size; i++) {
            if (mContainer.getChildAt(i).getTag() instanceof String) {
                if (TextUtils.equals(alice.getUid(), (String) mContainer.getChildAt(i).getTag())) {
                    aliceView = i;
                } else if (TextUtils.equals(bob.getUid(),
                        (String) mContainer.getChildAt(i).getTag())) {
                    bobView = i;
                }
            }
        }

        if (aliceView == -1 || bobView == -1 || aliceView == bobView) {
            return;
        }

        int n = mContainer.getChildCount();
        View[] children = new View[n];
        int index = 0;

        for (int i = 0; i < Math.min(aliceView, bobView); i++) {
            children[index] = mContainer.getChildAt(i);
            index++;
        }

        children[index] = mContainer.getChildAt(Math.max(aliceView, bobView));
        index++;

        for (int i = Math.min(aliceView, bobView) + 1; i < Math.max(aliceView, bobView); i++) {
            children[index] = mContainer.getChildAt(i);
            index++;
        }

        children[index] = mContainer.getChildAt(Math.min(aliceView, bobView));
        index++;

        for (int i = Math.max(aliceView, bobView) + 1; i < n; i++) {
            children[index] = mContainer.getChildAt(i);
            index++;
        }

        applyWindowSize(mContainer.getChildAt(aliceView), bob);
        applyWindowSize(mContainer.getChildAt(bobView), alice);

        for (View child : children) {
            child.bringToFront();
        }
    }

    @Override
    public void clearView() {
        mContainer.removeAllViews();
    }

    private void doCreateView(final Window window) {
        if (mContainerWidth == 0) {
            mContainerWidth = mContainer.getWidth();
            mContainerHeight = mContainer.getHeight();
        }

        TextView textView = new TextView(mContainer.getContext());

        textView.setText(window.getUid());
        textView.setGravity(Gravity.CENTER);
        textView.setBackgroundColor(COLORS[mContainer.getChildCount() % COLORS.length]);

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                WindowExt.absoluteSize(mContainerWidth, window.getWidth()),
                WindowExt.absoluteSize(mContainerHeight, window.getHeight()));
        params.leftMargin = WindowExt.absoluteSize(mContainerWidth, window.getLeft());
        params.topMargin = WindowExt.absoluteSize(mContainerHeight, window.getTop());
        mContainer.addView(textView, params);

        textView.setTag(window.getUid());
    }

    private void applyWindowSize(View view, Window window) {
        FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) view.getLayoutParams();
        params.width = WindowExt.absoluteSize(mContainerWidth, window.getWidth());
        params.height = WindowExt.absoluteSize(mContainerHeight, window.getHeight());
        params.leftMargin = WindowExt.absoluteSize(mContainerWidth, window.getLeft());
        params.topMargin = WindowExt.absoluteSize(mContainerHeight, window.getTop());
        view.setLayoutParams(params);
    }
}
