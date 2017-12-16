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


#import "PCUiOSWindowManagerCallback.h"

@implementation PCUiOSWindowManagerCallback {
    NSMutableArray* _users;
    int32_t _fcIndex;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _users = [[NSMutableArray alloc] init];
        _fcIndex = 0;
    }
    return self;
}

- (void)onError:(int32_t)error {
    NSLog(@"onError %d", error);
}

- (void)onWindowAdded:(nonnull PCUWindow*)window {
    [_users insertObject:window.uid atIndex:_users.count];
}

- (NSString*)nextFc {
    _fcIndex = (_fcIndex + 1) % _users.count;
    return [_users objectAtIndex:_fcIndex];
}

@end
