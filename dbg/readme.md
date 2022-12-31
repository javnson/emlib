# DBG module

## 1 Abstract

The DBG (debug) module gives you a tool kit for debugging. 

##  2 Components



| Sub-module Name   | Description                                                  |
| ----------------- | :----------------------------------------------------------- |
| debug_framework   | This component provided a series of tools for runtime check and compile-time check. You may use these code to protect your code. And all the check item has an unique option, and the macro `_emlib_debug` is the master switch. |
| blink_led         | This component provided a object for you to implement a breathing LED.<br />You may call the component to ensure if your device is running normally.<br />In the future the module will support more and more LED routine, and you may treat the component as an lamp signal. |
| console_log       | **This components is still constructing.**<br />This components give user an useful method to show your debug information. |
| constant_variable | **This components is still constructing.**<br />Generally, you will met the situation that at the beginning some figures are designed as a constant, but in the latterly days these figures are variant, and will be changed in the running time. At that case, some projects will recode some important code, but the constant_variable will help you realize the goal without recode. |



