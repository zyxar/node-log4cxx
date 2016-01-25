/*global require*/
'use strict';
var a = {};
a.a = a;

[new (require('.'))('LOG4CXX'), new (require('.')._)('LOG4CXX')].map(function (log) {
  log.fatal('Log level:', log.getLevel());

  log.trace('Hello World!');
  log.debug('Hello World!');
  log.info('Hello World!');
  log.warn('Hello World!');
  log.error('Hello World!');
  log.fatal('Hello World!');

  log.info(undefined);
  log.info(null);
  log.info('');
  log.info([]);
  log.info({});
  log.info(0);
  log.info(false);

  log.info(undefined, null, '', [], {}, 0, false, true, 'Hello World!', {Name: 'LOG4CXX', No: 1}, [1,2,3,4]);
  log.info(undefined, null, '', [], {}, 0, false, true, 'Hello World!', a, [null,undefined,true,a]);
});