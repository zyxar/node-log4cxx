# node-log4cxx
[![NPM](https://nodei.co/npm/log4cxx.png?downloads=true)](https://nodei.co/npm/log4cxx/)

This is a log4cxx wrapper for working with [Node.js](https://nodejs.org). If your Node.js application has a native addon which has already included log4cxx for logging, you will find this module really useful to unify the logging system and simplify the configuration.


## Prerequisites

- Node.js 4.x/5.x
- C++11 compiler
- `npm install -g node-gyp`
- [log4cxx](https://logging.apache.org/log4cxx/)

  - OS X: `brew install log4cxx`
  - Ubuntu: `sudo aptitude install liblog4cxx-dev`
  
## Install

- From NPM: `npm install log4cxx --save`


## Quick start

- Prepare a `log4cxx.properties` file, as [sample](https://github.com/zyxar/node-log4cxx/blob/master/log4cxx.properties)

```javascript
'use strict';
var log = new (require('log4cxx'))('demo');
log.info('Hello World');
```

## Known issues

1. [Segfault on printing Circular objects](https://github.com/zyxar/node-log4cxx/issues/1)

  - Using a JavaScript wrapper is a [work-around](https://github.com/zyxar/node-log4cxx/issues/1#issuecomment-173944009)
  
## [Configuration](https://logging.apache.org/log4cxx/usage.html)

## License
Apache 2.0
