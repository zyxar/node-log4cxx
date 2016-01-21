var log = new require('.')('Logger');

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

log.info(undefined, null, '', [], {}, 0, false, true, 'Hello World!', {Name: 'Logger', No: 1}, [1,2,3,4]);