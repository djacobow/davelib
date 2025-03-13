# Dave's c++ Library

## What is it

A collection of routines that I find generally useful.

## Logger

It is a simple singleton logger module in c++. It allows for multiple
subscribers, each of which can do their own thing with the messages,
such as print to console, or a file, in a format of their choosing.

Several built-in formats exist, but this can be extended.

A default Initializer is also provided that sets up one console output
with minimal detail and one file output with json formatting and all
detail.

### Why?

There are many logger libraries out there, including some sophisticated
ones. I like to use simple things that I understand and can extend,
and this is particularly useful in embedded contexts, so I wrote this.

## Others

### Error

There is also a simple "`Error`" library, including an optional-like
`ValueOr<T>` type, and macros to make it easy to use.
### Async

A thread-safe queue and a thread pool class.

### Util

String, time, hex printing, and other utilities

### Event

A simple event dispatcher


