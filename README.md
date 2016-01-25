# node-log4cxx
[![NPM](https://nodei.co/npm/log4cxx.png?downloads=true)](https://nodei.co/npm/log4cxx/)

[![Build Status](https://api.travis-ci.org/zyxar/node-log4cxx.svg?branch=master)](https://travis-ci.org/zyxar/node-log4cxx)

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


## Brief introduction

This module exports a `Logger` function as object constructor, as well as `Logger._`. Internally, `Logger` uses `Logger._` to accompany with `liblog4cxx`. However, `Logger` is better for formatting objects, whilst `Logger._` is better in efficiency. BTW, `Logger._` is almost the same as `log4cxx@0.0.2` module.

Read liblog4cxx usage for [configuration](https://logging.apache.org/log4cxx/usage.html) details.
See [test.js](https://github.com/zyxar/node-log4cxx/blob/master/test.js) for sample code.

### Quick start

- Prepare a `log4cxx.properties` file, as [sample](https://github.com/zyxar/node-log4cxx/blob/master/log4cxx.properties)

```javascript
'use strict';
var log = new (require('log4cxx'))('demo');
log.info('Hello World');
```

## License
Apache 2.0
