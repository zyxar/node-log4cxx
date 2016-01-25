/*global require,module*/
(function () {
  'use strict';
  var util = require('util');
  var LOG4CXX = require('./build/Release/log4cxx');
  var _ = {};

  function Logger (catagory) {
    if (!(this instanceof Logger)) {
      return new Logger(catagory);
    }
    Object.defineProperty(this, 'catagory', {writeable: false, value: catagory});
    _[catagory] = new LOG4CXX(catagory);
  }

  ['trace', 'debug', 'info', 'warn', 'error', 'fatal'].map(function (fn) {
    Logger.prototype[fn] = function () {
      _[this.catagory][fn](util.format.apply(util, arguments));
      return this;
    };
    Object.defineProperty(Logger.prototype[fn], 'name', {value: fn});
  });

  Logger.prototype.getLevel = function getLevel () {
    return _[this.catagory].getLevel();
  };

  Logger._ = LOG4CXX;
  module.exports = Logger;
})();
