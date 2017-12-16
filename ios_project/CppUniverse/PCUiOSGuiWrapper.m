//
/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Piasy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
//


#import "PCUiOSGuiWrapper.h"
#import "UIView+NSString.h"

static const int32_t kMatchParentSize = 10000;

CGFloat getSize(CGFloat full, int32_t size) {
    return full * size / kMatchParentSize;
}

@implementation PCUiOSGuiWrapper {
    NSArray<UIColor*>* _colors;
    UIView* _container;
    CGFloat _containerWidth;
    CGFloat _containerHeight;
}

- (instancetype)initWithContainer:(UIView*)container {
    self = [super init];
    if (self) {
        _colors =
            [NSArray arrayWithObjects:[UIColor redColor], [UIColor greenColor],
                                      [UIColor blueColor], nil];
        _container = container;
        _containerWidth = _container.bounds.size.width;
        _containerHeight = _container.bounds.size.height;
    }
    return self;
}

- (void)clearView {
    [[_container subviews]
        makeObjectsPerformSelector:@selector(removeFromSuperview)];
}

- (void)createView:(nonnull PCUWindow*)window {
    NSLog(@"createView %@", window);
    dispatch_async(dispatch_get_main_queue(), ^{
        UILabel* label = [[UILabel alloc]
            initWithFrame:CGRectMake(getSize(_containerWidth, window.left),
                                     getSize(_containerHeight, window.top),
                                     getSize(_containerWidth, window.width),
                                     getSize(_containerHeight, window.height))];
        label.text = window.uid;
        label.textAlignment = NSTextAlignmentCenter;
        label.backgroundColor =
            _colors[_container.subviews.count % _colors.count];
        label.uid = window.uid;

        [_container addSubview:label];
    });
}

- (void)swapView:(nonnull PCUWindow*)alice bob:(nonnull PCUWindow*)bob {
    int aliceView = -1;
    int bobView = -1;
    int index = 0;
    for (UIView* child in _container.subviews) {
        if ([child.uid isEqualToString:alice.uid]) {
            aliceView = index;
        } else if ([child.uid isEqualToString:bob.uid]) {
            bobView = index;
        }
        index++;
    }

    if (aliceView == -1 || bobView == -1 || aliceView == bobView) {
        return;
    }

    NSMutableArray* children =
        [[NSMutableArray alloc] initWithCapacity:_container.subviews.count];
    index = 0;
    for (int i = 0; i < MIN(aliceView, bobView); i++) {
        children[index] = _container.subviews[i];
        index++;
    }

    children[index] = _container.subviews[MAX(aliceView, bobView)];
    index++;

    for (int i = MIN(aliceView, bobView) + 1; i < MAX(aliceView, bobView);
         i++) {
        children[index] = _container.subviews[i];
        index++;
    }

    children[index] = _container.subviews[MIN(aliceView, bobView)];
    index++;

    for (int i = MAX(aliceView, bobView) + 1; i < _container.subviews.count;
         i++) {
        children[index] = _container.subviews[i];
        index++;
    }

    [self applyWindowSize:_container.subviews[aliceView] window:bob];
    [self applyWindowSize:_container.subviews[bobView] window:alice];

    for (UIView* child in children) {
        [_container bringSubviewToFront:child];
    }
}

- (void)applyWindowSize:(UIView*)view window:(PCUWindow*)window {
    view.frame = CGRectMake(getSize(_containerWidth, window.left),
                            getSize(_containerHeight, window.top),
                            getSize(_containerWidth, window.width),
                            getSize(_containerHeight, window.height));
}

@end
