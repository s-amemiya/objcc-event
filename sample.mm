
#import <Foundation/Foundation.h>

#include <iostream>
#include "Event.hpp"

using namespace std;

@interface MyClass : NSObject
@property (nonatomic, readonly) Event<>& arg0Event;
@property (nonatomic, readonly) Event<NSString *>& arg1Event;
@property (nonatomic, readonly) Event<int, int>& arg2Event;
- (void)doSomething;
@end

@implementation MyClass

@synthesize arg0Event = _arg0Event;
@synthesize arg1Event = _arg1Event;
@synthesize arg2Event = _arg2Event;

- (void)doSomething
{
	/* Do something. */

	// Raise events.
	_arg0Event();
	_arg1Event(@"abc");
	_arg2Event(1, 2);
}

@end

int main()
{
	MyClass *mc = [[MyClass alloc] init];
	
	// Set events.
	[mc arg0Event] += ^{ cout << "arg0Event." << endl; };
	[mc arg1Event] += ^(NSString * line) { cout << [line cStringUsingEncoding:NSUTF8StringEncoding] << endl; };
	[mc arg2Event] += ^(int x, int y) { cout << x + y << endl; };

	[mc doSomething];
	
	return 0;
}
