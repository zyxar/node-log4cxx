(function () {
  'use strict';
  var util = require('util');
  var LOG4CXX = require('./build/Release/addon');
  var logs = {};

  function Logger (catagory) {
    if (!(this instanceof Logger)) {
      return new Logger(catagory);
    }
    Object.defineProperty(this, 'catagory', {writeable: false, value: catagory});
    logs[catagory] = new LOG4CXX(catagory);
  }

  ['trace', 'debug', 'info', 'warn', 'error', 'fatal'].map(function (fn) {
    Logger.prototype[fn] = function () {
      return logs[this.catagory][fn](util.format.apply(util, arguments));
    };
  });

  Logger.prototype.getLevel = function () {
    return logs[this.catagory].getLevel();
  };

  Logger._ = LOG4CXX;
  module.exports = Logger;
})();
