/*global require*/
'use strict';
var a = {};
a.a = a;

[new (require('.'))('LOG4CXX'), new (require('.')._)('LOG4CXX')].map(function (log) {
  log.fatal('Log level:', log.getLevel());

  log.trace()
  .debug('Hello World!')
  .info('Hello World!')
  .warn('Hello World!')
  .error('Hello World!')
  .fatal('Hello World!')

  .info()
  .info(undefined)
  .info(null)
  .info('')
  .info([])
  .info({})
  .info(0)
  .info(false)

  .info(undefined, null, '', [], {}, 0, false, true, 'Hello World!', {Name: 'LOG4CXX', No: 1}, [1,2,3,4])
  .info(undefined, null, '', [], {}, 0, false, true, 'Hello World!', a, [null,undefined,true,a])
  .info(log, log.info);
});
