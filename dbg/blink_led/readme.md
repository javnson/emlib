# blink_led component

## 1. General

This component has two ways for user to implement the blink led. 

The first is using macro, without any objects. You may only defines a series of macros and just call one function, and then you will get the blinking led. How simple it is. The only disadvantage is you have only one led, and you can't implement any more.

Another is to using an object. You may not only defines a series of macros and also define objects, initialize the objects, call the main call-back function based on the object. The disadvantage is the object is too large to use. 

## 